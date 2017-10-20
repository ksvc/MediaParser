#ifndef VISUALSAMPLEENTRY_H
#define VISUALSAMPLEENTRY_H

#include "BaseBox.h"

class VisualSampleEntry : public BaseBox
{
public:
    VisualSampleEntry(uint32_t type, uint32_t size);
    ~VisualSampleEntry();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // VISUALSAMPLEENTRY_H
