#include "ItemPropertyContainerBox.h"

ItemPropertyContainerBox::ItemPropertyContainerBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

ItemPropertyContainerBox::~ItemPropertyContainerBox()
{
    propertis.clear();
}

int ItemPropertyContainerBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    int index = 0;
    while(index < this->size-8)
    {
        BaseBox* box = parser->ReadBox(start_pos + index);
        parser->AddBox(this, box);
        propertis.push_back(box);
        index += box->size;
        parser->io->SetPos(start_pos + index);
    }

    return 0;
}
