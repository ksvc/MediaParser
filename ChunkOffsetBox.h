#ifndef CHUNKOFFSETBOX_H
#define CHUNKOFFSETBOX_H

#include "BaseBox.h"

class ChunkOffsetBox : public BaseBox
{
public:
    ChunkOffsetBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // CHUNKOFFSETBOX_H
