#include <stdlib.h>
#include "Mp4Parser.h"
#include "BaseBox.h"
#include "DefaultContainerBox.h"

#include <stdio.h>
#include <QtGlobal>

mp4Parser::mp4Parser()
{
    io = new FileReader();
    dummy = new BaseBox(0, 0);
}

mp4Parser::~mp4Parser()
{
    if(io != NULL)
    {
        delete io;
        io = NULL;
    }
    if(dummy != NULL)
    {
        DestroyBox(dummy);
    }
}

BaseBox* mp4Parser::AllocBox(uint32_t type, uint32_t size)
{
    switch(type)
    {
    case FOURCC_moov:
    case FOURCC_trak:
    case FOURCC_mdia:
    case FOURCC_minf:
    case FOURCC_stbl:
        return new DefaultContainerBox(type, size);
        break;
    default:
        return new BaseBox(type, size);
    }

    return NULL;
}

BaseBox* mp4Parser::ReadBox(uint32_t start_pos)
{
    uint32_t size = io->Read32();
    uint32_t type = io->Read32();
    BaseBox* box = AllocBox(type, size);

    box->Parse(this, start_pos+8);

    return box;
}

void mp4Parser::AddBox(BaseBox* root, BaseBox* new_box)
{
    if(root == NULL || new_box == NULL)
            return;

    root->AddChild(new_box);
}

void mp4Parser::DestroyBox(BaseBox* root)
{
    if(root->childs)
    {
        DestroyBox(root->childs);
    }
    if(root->next)
    {
        DestroyBox(root->next);
    }

    delete root;
}

BaseBox* mp4Parser::GetParseResult()
{
    return dummy;
}

int mp4Parser::Parse(const char* filename)
{
    int ret = io->Open(filename);
    if(ret != 0)
    {
        return -1;
    }

    uint32_t cur_pos = 0;
    int file_size = io->GetLength();
    while(cur_pos < file_size)
    {
        BaseBox* box = ReadBox(cur_pos);
        this->dummy->AddChild(box);
        cur_pos += box->size;
        io->SetPos(cur_pos);
    }
    return 0;
}
