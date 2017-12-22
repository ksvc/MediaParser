#ifndef ITEMLOCATIONBOX_H
#define ITEMLOCATIONBOX_H

#include "BaseBox.h"

typedef struct ItemExtent
{
    uint64_t extend_index;
    uint64_t extend_offset;
    uint64_t extend_length;
}ItemExtent;

typedef struct ItemLocationEntry{
    uint32_t item_id;
    uint8_t construction_method;
    uint16_t data_reference_index;
    uint64_t base_offset;
    uint16_t extent_count;
    ItemExtent* extents;
}ItemLocationEntry;

class ItemLocationBox : public BaseBox
{
public:
    ItemLocationBox(uint32_t type, uint32_t size);
    virtual ~ItemLocationBox();

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();

private:
    uint8_t offset_size;
    uint8_t length_size;
    uint8_t base_offset_size;
    uint8_t index_size;

    uint32_t item_count;
    ItemLocationEntry* item_entries;
};

#endif // ITEMLOCATIONBOX_H
