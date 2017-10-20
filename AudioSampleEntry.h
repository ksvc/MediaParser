#ifndef AUDIOSAMPLEENTRY_H
#define AUDIOSAMPLEENTRY_H

#include "BaseBox.h"

class AudioSampleEntry : public BaseBox
{
public:
    AudioSampleEntry(uint32_t type, uint32_t size);
    ~AudioSampleEntry();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // AUDIOSAMPLEENTRY_H
