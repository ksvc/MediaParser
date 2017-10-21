#ifndef MP4DEFINE_H
#define MP4DEFINE_H

#include <stdint.h>

#define MAX_STREAM_COUNT 10

typedef struct stts_entry
{
    uint32_t sample_count;
    uint32_t sample_delta;
}stts_entry;

typedef struct Stream
{
    int index;
    uint32_t type;
    int tkhd_width;
    int tkhd_height;
    int width;
    int height;
    int channel_count;
    int sample_size;
    int sample_rate;
    char language[4];
    char* handler;
    char codec_name[32];

    int stts_count;
    stts_entry* stts_data;
}Stream;


#endif // MP4DEFINE_H

