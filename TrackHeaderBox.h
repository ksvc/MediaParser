#ifndef TRACKHEADERBOX_H
#define TRACKHEADERBOX_H

#include "BaseBox.h"

class TrackHeaderBox : public BaseBox
{
public:
    TrackHeaderBox(uint32_t type, uint32_t size);
    ~TrackHeaderBox();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // TRACKHEADERBOX_H
