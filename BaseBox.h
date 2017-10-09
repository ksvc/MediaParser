#ifndef BASEBOX_H
#define BASEBOX_H

#include <stdint.h>
#include "FourCC.h"

class BaseBox
{
public:
    BaseBox(uint32_t type, uint32_t size);
    virtual ~BaseBox();

public:
    void AddChild(BaseBox* child);

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);

public:
    uint32_t size;
    uint32_t type;
    char name[5];

    BaseBox* childs;
    BaseBox* next;
};

#endif // BASEBOX_H
