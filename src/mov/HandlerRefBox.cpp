#include "HandlerRefBox.h"
#include <memory.h>

HandlerRefBox::HandlerRefBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

HandlerRefBox::~HandlerRefBox()
{

}

int HandlerRefBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
	FileReader* io = parser->io;
	io->SetPos(start_pos);

	Stream* s = NULL;
	if (parser->stream_num > 0)
		s = parser->streams[parser->stream_num - 1];
    
    io->Read8(); //version
    io->Read24(); //flags
    io->Read32(); //pre_define

    uint32_t type = io->Read32();
	if (s)
		s->type = type;

    io->Skip(12);

    int name_len = this->size - 24;
    if(name_len > 0)
    {
        char* name = new char[name_len+1];
        memset(name, 0, name_len+1);
        io->ReadBuffer(name, name_len);
		if (s)
			s->handler = name;
    }
    return 0;
}
