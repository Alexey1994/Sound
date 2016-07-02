#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "../lib/AL/al.h"
#include "../lib/AL/alc.h"


#define NUM_BUFFERS 2
#define BUFFER_SIZE 16384


typedef struct
{
    char          *source;
    char         (*get_byte)(char *source);
    char           buffer[BUFFER_SIZE];
    unsigned int   data_size;
    unsigned int   buffer_size;
    unsigned int   sound_source;
    unsigned int   format;
    unsigned int   frequency;
    void         (*load_buffer)(struct Sound *sound);
}
Sound;

typedef struct
{
    ALCdevice  *device;
    ALCcontext *context;
}
SoundSystem;

SoundSystem* init_sound_system();
void free_sound_system(SoundSystem *sound);

void sound_play(Sound *sound);

#endif // SOUND_H_INCLUDED
