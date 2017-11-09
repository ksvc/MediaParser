#ifndef ITEMINFOBOX_H
#define ITEMINFOBOX_H

#include "BaseBox.h"

class ItemInfoBox : public BaseBox
{
public:
    ItemInfoBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();

private:
    uint32_t entry_count;
};

#endif // ITEMINFOBOX_H
