#ifndef DEFAULTCONTAINER_H
#define DEFAULTCONTAINER_H

#include "BaseBox.h"

class DefaultContainerBox : public BaseBox
{
public:
    DefaultContainerBox(uint32_t type, uint32_t size);
    virtual ~DefaultContainerBox();

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
};

#endif // DEFAULTCONTAINER_H
