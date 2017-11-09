#include "PrimaryItemBox.h"

PrimaryItemBox::PrimaryItemBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{
    item_id = 0;
}

int PrimaryItemBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint8_t version = io->Read8();
    io->Read24(); //flags
    if(version == 0)
    {
        item_id = io->Read16();
    }
    else
    {
        item_id = io->Read32();
    }
	return 0;
}

string PrimaryItemBox::GetDescription()
{
    char tmp[128];
    sprintf(tmp, "primary item = %d\n", item_id);
    return tmp;
}
