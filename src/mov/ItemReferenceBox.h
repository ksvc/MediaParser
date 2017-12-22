#ifndef ITEMREFERENCEBOX_H
#define ITEMREFERENCEBOX_H

#include "BaseBox.h"

class ItemReferenceBox : public BaseBox
{
public:
    ItemReferenceBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();
};

#endif // ITEMREFERENCEBOX_H
