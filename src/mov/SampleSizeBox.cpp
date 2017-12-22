#include "SampleSizeBox.h"

SampleSizeBox::SampleSizeBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

int SampleSizeBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    io->Read8(); //version
    io->Read24(); //flags

    Stream* s = parser->streams[parser->stream_num-1];

    if(this->type == FOURCC_stsz)
    {
        s->default_sample_size = io->Read32();
        s->stsz_count = io->Read32();
        if(s->default_sample_size == 0)
        {
            s->stsz_data = new uint32_t[s->stsz_count];
            for(int i=0;i<s->stsz_count;i++)
            {
                s->stsz_data[i] = io->Read32();
            }
        }
    }
    else
    {
        s->default_sample_size = 0;
        io->Read24();
        uint8_t filed_size = io->Read8();
        s->stsz_count = io->Read32();
        uint32_t count = s->stsz_count;
        if(filed_size == 4)
            count = count/2;
        else if(filed_size == 16)
            count = count*2;

        for(int i=0;i<count;i++)
        {
            s->stsz_data[i] = io->Read32();
        }

    }
    return 0;
}

