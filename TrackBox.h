#ifndef TRACKBOX_H
#define TRACKBOX_H

#include "BaseBox.h"

class TrackBox : public BaseBox
{
public:
    TrackBox(uint32_t type, uint32_t size);
    ~TrackBox();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);

};

#endif // TRACKBOX_H
