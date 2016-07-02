#include "WAV.h"
#include "extends.h"
#include "stream.h"


static void load_wav_buffer(Sound *sound)
{
    unsigned int size;

    for(size=0; size<BUFFER_SIZE && sound->data_size; size++, sound->data_size--)
        sound->buffer[size] = sound->get_byte( sound->source );

    sound->buffer_size=size;
}


Sound* load_WAV(char *source, char (*get_byte)(char *source))
{
    Sound         *sound=new(Sound);
    unsigned int   source_size;
    unsigned int   source_subchunk_size;
    unsigned short source_format;
    unsigned short source_num_channels;
    unsigned int   source_byte_rate;
    unsigned short source_block_align;
    unsigned short source_bits_per_sample;


    if(!stream_next("RIFF", source, get_byte))
    {
        printf("\nERROR file is not WAVE");
        return 0;
    }

    source_size=stream_get_uint(source, get_byte);

    if(!stream_next("WAVEfmt ", source, get_byte))
    {
        printf("\nERROR file is not WAVE");
        return 0;
    }

    source_subchunk_size   = stream_get_uint(source, get_byte);
    source_format          = stream_get_ushort(source, get_byte);
    source_num_channels    = stream_get_ushort(source, get_byte);
    sound->frequency       = stream_get_uint(source, get_byte);
    source_byte_rate       = stream_get_uint(source, get_byte);
    source_block_align     = stream_get_ushort(source, get_byte);
    source_bits_per_sample = stream_get_ushort(source, get_byte);

    while(!stream_next("data", source, get_byte))
    {
        source_subchunk_size=stream_get_uint(source, get_byte);
        stream_skip(source_subchunk_size, source, get_byte);
    }

    sound->data_size   = stream_get_uint(source, get_byte);
    sound->get_byte    = get_byte;
    sound->source      = source;
    sound->format      = AL_FORMAT_STEREO16;
    sound->load_buffer = load_wav_buffer;

    ALuint         buffers[NUM_BUFFERS];

    alGenBuffers(NUM_BUFFERS, buffers);
    alGenSources(1, &sound->sound_source);

    load_wav_buffer(sound);
    alBufferData(buffers[0], sound->format, sound->buffer, sound->buffer_size, sound->frequency);

    load_wav_buffer(sound);
    alBufferData(buffers[1], sound->format, sound->buffer, sound->buffer_size, sound->frequency);

    alSourceQueueBuffers(sound->sound_source, NUM_BUFFERS, buffers);

    return sound;
}
