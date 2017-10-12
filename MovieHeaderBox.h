#ifndef MOVIEHEADERBOX_H
#define MOVIEHEADERBOX_H

#include "BaseBox.h"

class MovieHeaderBox : public BaseBox
{
public:
    MovieHeaderBox(uint32_t type, uint32_t size);
    ~MovieHeaderBox();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // MOVIEHEADERBOX_H
