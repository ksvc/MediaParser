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
    int width;
    int height;
    int channel_count;
    int sample_size;
    int sample_rate;
    char language[4];
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
public:
    FileReader* io;
    BaseBox* dummy;
    int stream_num;
    Stream streams[MAX_STREAM_COUNT];
};

#endif // MP4PARSER_H
