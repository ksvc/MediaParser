#include "TimeToSampleBox.h"

TimeToSampleBox::TimeToSampleBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

int TimeToSampleBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    io->Read8(); //version
    io->Read24(); //flags

    Stream* s = parser->streams[parser->stream_num-1];
    s->stts_count = io->Read32();
    s->stts_data = new stts_entry[s->stts_count];
    for(int i=0;i<s->stts_count;i++)
    {
        s->stts_data[i].sample_count = io->Read32();
        s->stts_data[i].sample_delta = io->Read32();
    }
    return 0;
}
