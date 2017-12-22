#ifndef MP4DISPLAY_H
#define MP4DISPLAY_H

#include <QTreeWidget>
#include <QTextEdit>
#include <QtGlobal>
#include "mov/Mp4Parser.h"
#include "mov/BaseBox.h"

class mp4Display
{
public:
    mp4Display();

public:
    void Display(QTreeWidget* tree, QTextEdit* edit, mp4Parser* parser);

private:
    void ShowBox(QTreeWidgetItem* treeItem, BaseBox* box);
};

#endif // MP4DISPLAY_H
