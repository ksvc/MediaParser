#ifndef COMPOSITIONOFFSETBOX_H
#define COMPOSITIONOFFSETBOX_H

#include "BaseBox.h"

class CompositionOffsetBox : public BaseBox
{
public:
    CompositionOffsetBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // COMPOSITIONOFFSETBOX_H
