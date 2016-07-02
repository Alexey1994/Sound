#include <stdio.h>
#include <stdlib.h>
#include "WAV.h"
void load_wav_buffer(Sound *sound);

int main()
{
    struct SoundSystem *sound_system=init_sound_system();
    FILE               *f=fopen("a.wav", "rb");
    Sound              *sound=load_WAV(f, fgetc);

    sound_play(sound);

    free_sound_system(sound_system);
    return 0;
}
