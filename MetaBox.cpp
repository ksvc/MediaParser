#include "MetaBox.h"

MetaBox::MetaBox(uint32_t type, uint32_t size)
    :BaseBox(type, size)
{

}

int MetaBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    FileReader* io = parser->io;
    io->SetPos(start_pos);

    io->Read8(); //version
    io->Read24(); //flag

//    int index = 4;
//    while(index < this->size-8-4)
//    {
//        BaseBox* box = parser->ReadBox(start_pos + index);
//        parser->AddBox(this, box);
//        index += box->size;
//        parser->io->SetPos(start_pos + index);
//    }

    return 0;
}
