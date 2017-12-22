#ifndef MP4DEFINE_H
#define MP4DEFINE_H

#include <stdint.h>

#define MAX_STREAM_COUNT 10

typedef struct stts_entry
{
    uint32_t sample_count;
    uint32_t sample_delta;
}stts_entry;

typedef struct ctts_entry
{
    uint32_t sample_count;
    int32_t sample_offset;
}ctts_entry;

typedef struct stsc_entry
{
    uint32_t first_chunk;
    uint32_t samples_per_chunk;
    uint32_t sample_description_index;
}stsc_entry;

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

    uint32_t stss_count;
    uint32_t* stss_data;

    uint32_t ctts_count;
    ctts_entry* ctts_data;

    uint32_t stco_count;
    uint64_t* stco_data;

    uint32_t stsc_count;
    stsc_entry* stsc_data;

    uint32_t default_sample_size;
    uint32_t stsz_count;
    uint32_t* stsz_data;

    uint64_t* sample_position;
}Stream;


#endif // MP4DEFINE_H

