#include <stdlib.h>
#include "Mp4Parser.h"
#include "BaseBox.h"
#include "DefaultContainerBox.h"
#include "MovieHeaderBox.h"
#include "TrackBox.h"
#include "TrackHeaderBox.h"
#include "MediaHeaderBox.h"
#include "HandlerRefBox.h"
#include "SampleDescBox.h"
#include "TimeToSampleBox.h"
#include "SyncSampleBox.h"
#include "CompositionOffsetBox.h"
#include "ChunkOffsetBox.h"
#include "SampleToChunkBox.h"

#include <stdio.h>
#include <QtGlobal>

mp4Parser::mp4Parser()
{
    io = new FileReader();
    dummy = new BaseBox(0, 0);
    memset(debugInfo, 0, 4096);

    stream_num = 0;
    memset(streams, 0, sizeof(Stream*)*MAX_STREAM_COUNT);

    duration = 0;
    timescale = 1;
    width = 0;
    height = 0;
}

mp4Parser::~mp4Parser()
{
    if(io != NULL)
    {
        delete io;
        io = NULL;
    }
    if(dummy != NULL)
    {
        DestroyBox(dummy);
    }
    for(int i=0;i<this->stream_num;i++)
    {
        DeleteStream(this->streams[i]);
        this->streams[i] = NULL;
    }
}

BaseBox* mp4Parser::AllocBox(uint32_t type, uint32_t size)
{
    BaseBox* box = NULL;
    switch(type)
    {
    case FOURCC_moov:
    case FOURCC_mdia:
    case FOURCC_minf:
    case FOURCC_stbl:
    case FOURCC_udta:
        box = new DefaultContainerBox(type, size);
        break;
    case FOURCC_mvhd:
        box = new MovieHeaderBox(type, size);
        break;
    case FOURCC_trak:
        box = new TrackBox(type, size);
        break;
    case FOURCC_tkhd:
        box = new TrackHeaderBox(type, size);
        break;
    case FOURCC_mdhd:
        box = new MediaHeaderBox(type, size);
        break;
    case FOURCC_hdlr:
        box = new HandlerRefBox(type, size);
        break;
    case FOURCC_stsd:
        box = new SampleDescBox(type, size);
        break;
    case FOURCC_stts:
        box = new TimeToSampleBox(type, size);
        break;
    case FOURCC_stss:
        box = new SyncSampleBox(type, size);
        break;
    case FOURCC_ctts:
        box = new CompositionOffsetBox(type, size);
        break;
    case FOURCC_stco:
    case FOURCC_co64:
        box = new ChunkOffsetBox(type, size);
        break;
    case FOURCC_stsc:
        box = new SampleToChunkBox(type, size);
        break;
    default:
        box = new BaseBox(type, size);
        break;
    }

    return box;
}

BaseBox* mp4Parser::ReadBox(uint32_t start_pos)
{
    uint32_t size = io->Read32();
    uint32_t type = io->Read32();
    BaseBox* box = AllocBox(type, size);

    box->Parse(this, start_pos+8);

    return box;
}

void mp4Parser::AddBox(BaseBox* root, BaseBox* new_box)
{
    if(root == NULL || new_box == NULL)
            return;

    root->AddChild(new_box);
}

void mp4Parser::DestroyBox(BaseBox* root)
{
    if(root->childs)
    {
        DestroyBox(root->childs);
    }
    if(root->next)
    {
        DestroyBox(root->next);
    }

    delete root;
}

BaseBox* mp4Parser::GetParseResult()
{
    return dummy;
}

Stream* mp4Parser::AddStream()
{
    Stream* s = new Stream;
    memset(s, 0, sizeof(Stream));
    s->index = this->stream_num;
    this->streams[this->stream_num] = s;
    this->stream_num++;
    return s;
}

void mp4Parser::DeleteStream(Stream* s)
{
    if(!s)
        return;

    if(s->handler)
        delete s->handler;
    if(s->stts_data)
        delete[] s->stts_data;
    if(s->stss_data)
        delete[] s->stss_data;
    if(s->ctts_data)
        delete[] s->ctts_data;
    if(s->stco_data)
        delete[] s->stco_data;
    if(s->stsc_data)
        delete[] s->stsc_data;

    delete s;
}

int mp4Parser::Parse(const char* filename)
{
    int ret = io->Open(filename);
    if(ret != 0)
    {
        return -1;
    }

    uint32_t cur_pos = 0;
    int file_size = io->GetLength();
    if(file_size <= 0)
    {
        return -1;
    }

    while(cur_pos < file_size)
    {
        BaseBox* box = ReadBox(cur_pos);
        this->dummy->AddChild(box);
        cur_pos += box->size;
        io->SetPos(cur_pos);
    }
    return 0;
}
