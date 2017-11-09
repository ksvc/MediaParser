#ifndef PRIMARYITEMBOX_H
#define PRIMARYITEMBOX_H

#include "BaseBox.h"

class PrimaryItemBox : public BaseBox
{
public:
    PrimaryItemBox(uint32_t type, uint32_t size);

    virtual int Parse(class mp4Parser* parser, uint32_t start_pos);
    virtual string GetDescription();
private:
    uint32_t item_id;
};

#endif // PRIMARYITEMBOX_H
