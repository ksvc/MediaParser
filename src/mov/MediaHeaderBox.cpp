#include "MediaHeaderBox.h"

MediaHeaderBox::MediaHeaderBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

MediaHeaderBox::~MediaHeaderBox()
{

}

static void make_language_iso639(uint16_t lang, char language[4])
{
    language[3] = 0;
    language[2] = (lang & 0x001f) + 0x60;
    lang >>= 5;
    language[1] = (lang & 0x001f) + 0x60;
    lang >>= 5;
    language[0] = (lang & 0x001f) + 0x60;
}


int MediaHeaderBox::Parse(class mp4Parser* parser, uint32_t start_pos)
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

    uint16_t language = io->Read16();
    make_language_iso639(language, parser->streams[parser->stream_num-1]->language);
    return 0;
}
