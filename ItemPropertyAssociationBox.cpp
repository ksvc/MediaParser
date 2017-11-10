#include "ItemPropertyAssociationBox.h"

ItemPropertyAssociationBox::ItemPropertyAssociationBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

ItemPropertyAssociationBox::~ItemPropertyAssociationBox()
{
    if(entries != NULL && item_count > 0)
    {
        for(int i=0;i<item_count;i++)
        {
            if(entries[i].entries != NULL)
                delete[] entries[i].entries;
        }
        delete[] entries;
    }
}

int ItemPropertyAssociationBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint8_t version = io->Read8();
    uint16_t flags = io->Read24();

    item_count = io->Read32();
    this->entries = new ItemPropertyAssociationEntry[item_count];
    for(int i=0;i<item_count;i++)
    {
        uint32_t item_id = 0;
        if(version < 1)
            item_id = io->Read16();
        else
            item_id = io->Read32();
        entries[i].item_id = item_id;

        uint8_t entry_count = io->Read8();
        entries[i].entry_count = entry_count;
        entries[i].entries = new ItemPropertyAssociationIndex[entry_count];
        for(int j=0;j<entry_count;j++)
        {
            if(flags & 1)
            {
                uint16_t tmp = io->Read16();
                entries[i].entries[j].essential = (tmp>>15);
                entries[i].entries[j].index = (tmp&0x7ffff);
            }
            else
            {
                uint8_t tmp = io->Read8();
                entries[i].entries[j].essential = tmp>>7;
                entries[i].entries[j].index = tmp&0x7f;
            }
        }
    }

    return 0;
}

string ItemPropertyAssociationBox::GetDescription()
{
    char tmp[4096] = {0};
    sprintf(tmp, "item_count = %d\n", item_count);
    for(int i=0;i<item_count;i++)
    {
        ItemPropertyAssociationEntry* entry = &entries[i];
        sprintf(tmp,
                "%s"
                "id = %d, index = ",
                tmp, entry->item_id);
        for(int j=0;j<entry->entry_count;j++)
        {
            sprintf(tmp, "%s%d ", tmp, entry->entries[j].index);
        }
        sprintf(tmp, "%s\n", tmp);

    }
    return tmp;
}
