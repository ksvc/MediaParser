#include "ItemInfoBox.h"

ItemInfoBox::ItemInfoBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{
    entry_count = 0;
}

int ItemInfoBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint8_t version = io->Read8();
    io->Read24(); //flags

    int index = 4;
    if(version == 0)
    {
        entry_count = io->Read16();
        index += 2;
    }
    else
    {
        entry_count = io->Read32();
        index += 4;
    }

    for(int i=0;i<entry_count;i++)
    {
        uint32_t size = io->Read32();
        uint32_t type = io->Read32();

        BaseBox* box = NULL;
        box = new BaseBox(type, size);
        box->SetPosition(start_pos+index);
        box->Parse(parser, start_pos+index+8);
        parser->AddBox(this, box);
        index += box->size;
        io->SetPos(start_pos + index);
    }

    return 0;
}

string ItemInfoBox::GetDescription()
{
    char tmp[128];
    sprintf(tmp, "item count = %d\n", entry_count);
    return tmp;
}
