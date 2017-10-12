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
    parser->io->SetPos(start_pos);

    uint64_t creation_time, modification_time;
    uint32_t timescale, duration;

    uint8_t version = parser->io->Read8();
    uint32_t flags = parser->io->Read24();

    if(version == 1)
    {
        creation_time = parser->io->Read64();
        modification_time = parser->io->Read64();
        timescale = parser->io->Read32();
        duration = parser->io->Read32();
    }
    else
    {
        creation_time = parser->io->Read32();
        modification_time = parser->io->Read32();
        timescale = parser->io->Read32();
        duration = parser->io->Read32();
    }
    parser->duration = duration;
    parser->timescale = timescale;
    return 0;
}
