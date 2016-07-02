#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

char stream_next(char *string, char *source, char(*get_byte)(char *source));
unsigned int stream_get_uint(char *source, unsigned char(*get_byte)(char *source));
unsigned int stream_get_ushort(char *source, char(*get_byte)(char *source));
void stream_skip(unsigned int length, char *source, char(*get_byte)(char *source));

#endif // STREAM_H_INCLUDED
