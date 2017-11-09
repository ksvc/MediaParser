#include "ItemLocationBox.h"

ItemLocationBox::ItemLocationBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{
    offset_size = 0;
    length_size = 0;
    base_offset_size = 0;
    index_size = 0;

    item_count = 0;
    item_entries = NULL;
}

ItemLocationBox::~ItemLocationBox()
{
    if(item_entries != NULL && item_count > 0)
    {
        for(int i=0;i<item_count;i++)
        {
            if(item_entries[i].extents != NULL)
                delete[] item_entries[i].extents;
        }
    }
    delete[] item_entries;
}

int ItemLocationBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint8_t version = io->Read8();
    io->Read24(); //flags

    uint8_t tmp = io->Read8();
    offset_size = (tmp>>4);
    length_size = (tmp&0x0f);

    tmp = io->Read8();
    base_offset_size = (tmp>>4);
    index_size = (tmp&0x0f);

    if(version < 2)
        item_count = io->Read16();
    else if(version == 2)
        item_count = io->Read32();
    else
        return -1;
    if(item_count <= 0)
        return -1;
    item_entries = new ItemLocationEntry[item_count];
    for(int i=0;i<item_count;i++)
    {
        if(version < 2)
            item_entries[i].item_id = io->Read16();
        else if(version == 2)
            item_entries[i].item_id = io->Read32();

        if(version == 1 || version == 2)
        {
            int16_t tmp = io->Read16();
            item_entries[i].construction_method = (tmp&0x000f);
        }

        item_entries[i].data_reference_index = io->Read16();
        if(item_entries[i].construction_method == 4)
            item_entries[i].base_offset = io->Read32();
        else if(item_entries[i].construction_method == 8)
            item_entries[i].base_offset = io->Read64();

        item_entries[i].extent_count = io->Read16();
        if(item_entries->extent_count <= 0)
            return -1;
        item_entries[i].extents = new ItemExtent[item_entries[i].extent_count];
        for(int j=0;j<item_entries[i].extent_count;j++)
        {
            if((version == 1 || version == 2) && index_size > 0)
            {
                if(index_size == 4)
                    item_entries[i].extents[j].extend_index = io->Read32();
                else if(index_size == 8)
                    item_entries[i].extents[j].extend_index = io->Read64();
            }
            if(offset_size == 4)
                item_entries[i].extents[j].extend_offset = io->Read32();
            else if(offset_size == 8)
                item_entries[i].extents[j].extend_offset = io->Read64();

            if(length_size == 4)
                item_entries[i].extents[j].extend_length = io->Read32();
            else if(length_size == 8)
                item_entries[i].extents[j].extend_length = io->Read64();
        }
    }
    return 0;
}

string ItemLocationBox::GetDescription()
{
    char tmp[1024];
    sprintf(tmp,
            "offsest_size = %d\n"
            "length_size = %d\n"
            "base_offset_size = %d\n"
            "index_size = %d\n"
            "item_count = %d\n",
            offset_size,
            length_size,
            base_offset_size,
            index_size,
            item_count);
    return tmp;
}
