#include "MovieHeaderBox.h"
#include "Mp4Parser.h"

MovieHeaderBox::MovieHeaderBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

MovieHeaderBox::~MovieHeaderBox()
{

}

int MovieHeaderBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    uint64_t creation_time, modification_time;
    uint32_t timescale, duration;

    uint8_t version = io->Read8();
    uint32_t flags = io->Read24();

    if(version == 1)
    {
        creation_time = io->Read64();
        modification_time = io->Read64();
        timescale = io->Read32();
        duration = io->Read32();
    }
    else
    {
        creation_time = io->Read32();
        modification_time = io->Read32();
        timescale = io->Read32();
        duration = io->Read32();
    }
    parser->duration = duration;
    parser->timescale = timescale;
    return 0;
}
