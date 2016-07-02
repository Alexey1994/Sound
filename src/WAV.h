#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED

#include "Sound.h"


Sound* load_WAV(char *source, char (*get_byte)(char *source));


#endif // WAVE_H_INCLUDED
