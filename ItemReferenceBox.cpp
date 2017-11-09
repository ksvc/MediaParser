#include "ItemReferenceBox.h"

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
        BaseBox* box = parser->ReadBox(start_pos + index);
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
