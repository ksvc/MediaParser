#include "SampleToChunkBox.h"

SampleToChunkBox::SampleToChunkBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

int SampleToChunkBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    io->Read8(); //version
    io->Read24(); //flags

    Stream* s = parser->streams[parser->stream_num-1];
    s->stsc_count = io->Read32();
    s->stsc_data = new stsc_entry[s->stsc_count];
    for(int i=0;i<s->stsc_count;i++)
    {
        s->stsc_data[i].first_chunk = io->Read32();
        s->stsc_data[i].samples_per_chunk = io->Read32();
        s->stsc_data[i].sample_description_index = io->Read32();
    }
    return 0;
}
