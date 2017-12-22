#ifndef ITEMPROPERTYASSOCIATIONBOX_H
#define ITEMPROPERTYASSOCIATIONBOX_H

#include "BaseBox.h"
#include <vector>
#include <map>

typedef struct ItemPropertyAssociationIndex
{
    bool essential;
    uint16_t index;
}ItemPropertyAssociationIndex;

typedef struct ItemPropertyAssociationEntry
{
    uint32_t item_id;
    uint8_t entry_count;
    ItemPropertyAssociationIndex* entries;
}ItemPropertyAssociationEntry;

class ItemPropertyAssociationBox : public BaseBox
{
public:
    ItemPropertyAssociationBox(uint32_t type, uint32_t size);
    ~ItemPropertyAssociationBox();

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();

private:
    int item_count;
    ItemPropertyAssociationEntry* entries;
};

#endif // ITEMPROPERTYASSOCIATIONBOX_H
