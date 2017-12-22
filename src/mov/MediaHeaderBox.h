#ifndef MEDIAHEADERBOX_H
#define MEDIAHEADERBOX_H

#include "BaseBox.h"

class MediaHeaderBox : public BaseBox
{
public:
    MediaHeaderBox(uint32_t type, uint32_t size);
    ~MediaHeaderBox();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // MEDIAHEADERBOX_H
