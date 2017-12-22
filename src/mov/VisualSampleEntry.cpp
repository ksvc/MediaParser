#include "VisualSampleEntry.h"

VisualSampleEntry::VisualSampleEntry(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

VisualSampleEntry::~VisualSampleEntry()
{

}

int VisualSampleEntry::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    io->Skip(6);
    io->Read16(); //data_reference_index

    io->Skip(16);

    Stream* s = parser->streams[parser->stream_num-1];
    s->width = io->Read16();
    s->height = io->Read16();
    io->Read32(); //horizresolution
    io->Read32(); //vertresolution
    io->Read32(); //reserved
    io->Read16(); //frame_count

    int len = io->Read8();
    if(len > 31)
        len = 31;
    io->ReadBuffer(s->codec_name, len);
    io->Skip(31-len);

    io->Read16();//depth
    io->Read16();//pre_define

    //below other box
    BaseBox* box = parser->ReadBox(io->GetPos());
    parser->AddBox(this, box);
    return 0;
}
