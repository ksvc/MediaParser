#ifndef SINGLEITEMTYPEREFERENCEBOX_H
#define SINGLEITEMTYPEREFERENCEBOX_H

#include "BaseBox.h"
#include <vector>

class SingleItemTypeReferenceBox : public BaseBox
{
public:
    SingleItemTypeReferenceBox(uint32_t type, uint32_t size);
    ~SingleItemTypeReferenceBox();

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();

    void setLargeItemId(bool bLargeItemId){this->bLargeItemId = bLargeItemId;};
private:
    bool bLargeItemId;

    uint32_t from_item_ID;
    uint16_t reference_count;
    vector<uint32_t> to_item_IDs;
};

#endif // SINGLEITEMTYPEREFERENCEBOX_H
