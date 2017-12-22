#ifndef BASEBOX_H
#define BASEBOX_H

#include <stdint.h>
#include "../FourCC.h"
#include "Mp4Parser.h"
#include <string>
#include <sstream>

using namespace std;

class BaseBox
{
public:
    BaseBox(uint32_t type, uint32_t size);
    virtual ~BaseBox();

public:
    void AddChild(BaseBox* child);
    void SetPosition(uint32_t start);

public:
    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();
public:
    uint32_t size;
    uint32_t type;
    char name[5];
    uint32_t start_pos;

    BaseBox* childs;
    BaseBox* next;
};

#endif // BASEBOX_H
