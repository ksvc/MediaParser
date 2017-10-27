#ifndef SAMPLETOCHUNKBOX_H
#define SAMPLETOCHUNKBOX_H

#include "BaseBox.h"

class SampleToChunkBox : public BaseBox
{
public:
    SampleToChunkBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // SAMPLETOCHUNKBOX_H
