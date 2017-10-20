#include "Mp4Display.h"

mp4Display::mp4Display()
{

}

static char* getHandlerType(uint32_t type)
{
    if(type == HANDLER_AUDIO)
        return "Audio";
    if(type == HANDLER_VIDEO)
        return "Video";
    if(type == HANDLER_HINT)
        return "Hint";
    if(type == HANDLER_META)
        return "meta";
    return "Unkown";
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
        info.sprintf("stream %d:%s\n"
                     "tkhd_width = %d\n"
                     "tkhd_height=%d\n"
                     "language = %s\n"
                     "handler = %s\n"
                     "width = %d\n"
                     "height = %d\n"
                     "codec = %s\n",
                     i, getHandlerType(parser->streams[i]->type),
                     parser->streams[i]->tkhd_width,
                     parser->streams[i]->tkhd_height,
                     parser->streams[i]->language,
                     parser->streams[i]->handler,
                     parser->streams[i]->width,
                     parser->streams[i]->height,
                     parser->streams[i]->codec_name);
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
