#include "SampleDescBox.h"
#include "VisualSampleEntry.h"
#include "AudioSampleEntry.h"

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
        uint32_t size = io->Read32();
        uint32_t type = io->Read32();

        BaseBox* box = NULL;
        if(s->type == HANDLER_VIDEO)
        {
            box = new VisualSampleEntry(type, size);
        }
        else if(s->type == HANDLER_AUDIO)
        {
            box = new AudioSampleEntry(type, size);
        }
        else
        {
            box = new BaseBox(type, size);
        }
        box->Parse(parser, start_pos+index+8);
        parser->AddBox(this, box);
        index += box->size;
        io->SetPos(start_pos + index);
    }
    return 0;
}
