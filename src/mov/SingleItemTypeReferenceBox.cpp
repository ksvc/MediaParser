#include "SingleItemTypeReferenceBox.h"

SingleItemTypeReferenceBox::SingleItemTypeReferenceBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

SingleItemTypeReferenceBox::~SingleItemTypeReferenceBox()
{

}

int SingleItemTypeReferenceBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    if(bLargeItemId)
        from_item_ID = io->Read32();
    else
        from_item_ID = io->Read16();

    reference_count = io->Read16();
    for(int i=0;i<reference_count;i++)
    {
        uint32_t item = 0;
        if(bLargeItemId)
            item = io->Read32();
        else
            item = io->Read16();
        to_item_IDs.push_back(item);
    }
    return 0;
}

string SingleItemTypeReferenceBox::GetDescription()
{
    char tmp[4096];
    sprintf(tmp, "From item id = %d\n", from_item_ID);
    for(int i=0;i<reference_count;i++)
    {
        sprintf(tmp, "%sto item id = %d\n", tmp, to_item_IDs[i]);
    }
    return tmp;
}
