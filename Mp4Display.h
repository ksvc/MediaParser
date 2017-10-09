#ifndef MP4DISPLAY_H
#define MP4DISPLAY_H

#include <qtreewidget.h>
#include <QtGlobal>
#include "Mp4Parser.h"
#include "BaseBox.h"

class mp4Display
{
public:
    mp4Display();

public:
    void Display(QTreeWidget* tree, mp4Parser* parser);

private:
    void ShowBox(QTreeWidgetItem* treeItem, BaseBox* box);
};

#endif // MP4DISPLAY_H
