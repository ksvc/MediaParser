#ifndef METABOX_H
#define METABOX_H

#include "BaseBox.h"

class MetaBox : public BaseBox
{
public:
    MetaBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // METABOX_H
