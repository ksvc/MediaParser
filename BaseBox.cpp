#include "BaseBox.h"
#include "Mp4Parser.h"
#include <memory.h>
#include <QtGlobal>


BaseBox::BaseBox(uint32_t type, uint32_t size)
{
    this->size = size;
    this->type = type;
    this->name[0] = type>>24;
    this->name[1] = (type>>16)&0xff;
    this->name[2] = (type>>8)&0xff;
    this->name[3] = type&0xff;
    this->name[4] = 0;

    this->childs = NULL;
    this->next = NULL;
}

BaseBox::~BaseBox()
{
    this->size = 0;
    this->type = 0;
    memset(this->name, 0, 5);
}

int BaseBox::Parse(class mp4Parser* parser, uint32_t start_pos)
{
    qDebug("type = %s\n", this->name);
    return 0;
}

void BaseBox::AddChild(BaseBox* child)
{
    if(this->childs == NULL)
    {
        this->childs = child;
        return;
    }

    BaseBox* tmp = this->childs;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = child;
    return;
}
