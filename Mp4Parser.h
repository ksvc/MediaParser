#ifndef MP4PARSER_H
#define MP4PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "FileReader.h"

#define MAX_STREAM_COUNT 10
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
}Stream;

class BaseBox;
class mp4Parser
{
public:
    mp4Parser();
    ~mp4Parser();

public:
    int Parse(const char* filename);
    BaseBox* GetParseResult();

public:
    BaseBox* ReadBox(uint32_t start_pos);
    BaseBox* AllocBox(uint32_t type, uint32_t size);
    void AddBox(BaseBox* root, BaseBox* new_box);
    void DestroyBox(BaseBox* root);
    Stream* AddStream();
    void DeleteStream(Stream* stream);
public:
    FileReader* io;
    BaseBox* dummy;
    int stream_num;
    Stream* streams[MAX_STREAM_COUNT];

    char debugInfo[4096];
    uint64_t duration;
    uint32_t timescale;
    uint32_t width;
    uint32_t height;
};

#endif // MP4PARSER_H
