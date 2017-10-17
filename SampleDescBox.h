#ifndef SAMPLEDESCBOX_H
#define SAMPLEDESCBOX_H

#include "BaseBox.h"

class SampleDescBox : public BaseBox
{
public:
    SampleDescBox(uint32_t type, uint32_t size);
    ~SampleDescBox();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // SAMPLEDESCBOX_H
