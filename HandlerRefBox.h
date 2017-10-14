#ifndef HANDLERREFBOX_H
#define HANDLERREFBOX_H

#include "BaseBox.h"

class HandlerRefBox : public BaseBox
{
public:
    HandlerRefBox(uint32_t type, uint32_t size);
    ~HandlerRefBox();

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // HANDLERREFBOX_H
