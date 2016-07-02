#include "Sound.h"
#include "extends.h"
#include <windows.h>


SoundSystem* init_sound_system()
{
    SoundSystem *sound_system;
    ALCdevice   *device;
    ALCcontext  *context;

    device=alcOpenDevice(0);
    if(!device)
    {
        printf("\nerror creating device");
        return 0;
    }

    context=alcCreateContext(device, 0);
    alcMakeContextCurrent(context);

    sound_system=new(SoundSystem);
    sound_system->context = context;
    sound_system->device  = device;

    return sound_system;
}


void free_sound_system(SoundSystem *sound_system)
{
    alcDestroyContext(sound_system->context);
    alcCloseDevice(sound_system->device);
    free(sound_system);
}


void sound_play(Sound *sound)
{
    alSourcePlay(sound->sound_source);

    ALuint buffer;
    ALuint val;

    while(1)
    {
        Sleep(1);
        alGetSourcei(sound->sound_source, AL_BUFFERS_PROCESSED, &val);

        if(val<=0)
            continue;

        alSourceUnqueueBuffers(sound->sound_source, 1, &buffer);

        sound->load_buffer(sound);
        alBufferData(buffer, sound->format, sound->buffer, sound->buffer_size, sound->frequency);

        alSourceQueueBuffers(sound->sound_source, 1, &buffer);

        alGetSourcei(sound->sound_source, AL_SOURCE_STATE, &val);
        if(val != AL_PLAYING)
            alSourcePlay(sound->sound_source);
    }
}
