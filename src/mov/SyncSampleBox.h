#ifndef SYNCSAMPLEBOX_H
#define SYNCSAMPLEBOX_H

#include "BaseBox.h"


class SyncSampleBox : public BaseBox
{
public:
    SyncSampleBox(uint32_t type, uint32_t size);

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // SYNCSAMPLEBOX_H
