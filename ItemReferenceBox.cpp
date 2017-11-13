#include "ItemReferenceBox.h"
#include "SingleItemTypeReferenceBox.h"

ItemReferenceBox::ItemReferenceBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

int ItemReferenceBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint8_t version = io->Read8();
    io->Read24(); //flags

    int index = 4;
    while(index < this->size-8-4)
    {
        uint32_t size = io->Read32();
        uint32_t type = io->Read32();

        SingleItemTypeReferenceBox* box = new SingleItemTypeReferenceBox(type, size);
        if(version == 0)
        {
            box->setLargeItemId(false);
        }
        else if(version == 1)
        {
            box->setLargeItemId(true);
        }
        box->SetPosition(start_pos+index);
        box->Parse(parser, start_pos + index + 8);
        parser->AddBox(this, box);

        index += box->size;
        parser->io->SetPos(start_pos + index);
    }

    return 0;
}

string ItemReferenceBox::GetDescription()
{
    return "";
}
