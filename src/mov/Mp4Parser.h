#ifndef MP4PARSER_H
#define MP4PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "../FileReader.h"
#include "Mp4Define.h"

class BaseBox;
class mp4Parser
{
public:
    mp4Parser();
    mp4Parser(FileReader* io);
    ~mp4Parser();
private:
    void init();

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

    void GetSamplePosition(Stream* s);
public:
    FileReader* io;
    FileReader* inner_io;
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
