#ifndef ITEMPROPERTYCONTAINERBOX_H
#define ITEMPROPERTYCONTAINERBOX_H

#include "BaseBox.h"
#include <vector>

class ItemPropertyContainerBox : public BaseBox
{
public:
    ItemPropertyContainerBox(uint32_t type, uint32_t size);
    ~ItemPropertyContainerBox();

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);

private:
    vector<BaseBox*> propertis;
};

#endif // ITEMPROPERTYCONTAINERBOX_H
