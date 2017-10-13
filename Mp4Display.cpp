#include "Mp4Display.h"

mp4Display::mp4Display()
{

}

void mp4Display::Display(QTreeWidget* tree, QTextEdit* edit, mp4Parser* parser)
{
    tree->clear();
    QTreeWidgetItem *root = new QTreeWidgetItem(QStringList("mp4"));
    tree->addTopLevelItem(root);
    root->setExpanded(true);

    BaseBox* mp4 = parser->GetParseResult();
    if(mp4 == NULL)
        return;
    ShowBox(root, mp4->childs);

    QString info;
    info.sprintf("duration = %.02f\n", (float)parser->duration/parser->timescale);
    edit->setText(info);

    for(int i=0;i<parser->stream_num;i++)
    {
        info.sprintf("stream %d:\nwidth = %d\nheight=%d\n", i, parser->streams[i].tkhd_width, parser->streams[i].tkhd_height);
        edit->append(info);
    }

}

void mp4Display::ShowBox(QTreeWidgetItem* treeItem, BaseBox* box)
{
    if(box == NULL)
        return;

    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(box->name));
    treeItem->addChild(item);

    if(box->childs != NULL)
    {
        ShowBox(item, box->childs);
    }
    if(box->next != NULL)
    {
        ShowBox(treeItem, box->next);
    }
}
