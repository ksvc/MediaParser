#include "TrackHeaderBox.h"
#include "Mp4Parser.h"

TrackHeaderBox::TrackHeaderBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

TrackHeaderBox::~TrackHeaderBox()
{

}

int TrackHeaderBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint64_t creation_time, modification_time;
    uint32_t timescale, duration;
    uint32_t track_id;

    uint8_t version = io->Read8();
    uint32_t flags = io->Read24();

    if(version == 1)
    {
        creation_time = io->Read64();
        modification_time = io->Read64();
        track_id = io->Read32();
        io->Skip(4);
        duration = io->Read64();
    }
    else
    {
        creation_time = io->Read32();
        modification_time = io->Read32();
        track_id = io->Read32();
        io->Skip(4);
        duration = io->Read32();
    }
    io->Skip(8);
    io->Read16();//layer
    io->Read16();//alternate_group
    io->Read16();//volume
    io->Skip(2);

    for(int i=0;i<9;i++)
    {
        io->Read32();//matrix
    }

    Stream* stream = &parser->streams[parser->stream_num-1];
    stream->tkhd_width = io->Read32()>>16;
    stream->tkhd_height = io->Read32()>>16;

    return 0;
}
