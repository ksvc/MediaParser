#include "SampleDescBox.h"

SampleDescBox::SampleDescBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

SampleDescBox::~SampleDescBox()
{

}

int SampleDescBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    io->Read8(); //version
    io->Read24(); //flags

    Stream* s = parser->streams[parser->stream_num-1];
    uint32_t entry_count = io->Read32();
    int index = 8;
    for(int i=0;i<entry_count;i++)
    {
        BaseBox* box = NULL;
        if(s->type == HANDLER_VIDEO)
        {
            box = parser->ReadBox(start_pos + index);
        }
        else if(s->type == HANDLER_AUDIO)
        {
            box = parser->ReadBox(start_pos + index);
        }
        else
        {
            box = parser->ReadBox(start_pos + index);
        }
        parser->AddBox(this, box);
        index += box->size;
        io->SetPos(start_pos + index);
    }
    return 0;
}
