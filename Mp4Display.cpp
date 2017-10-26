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
        Stream* s = parser->streams[i];
        if(s->type == HANDLER_VIDEO)
        {
            info.sprintf("stream %d:%s\n"
                         "tkhd_width = %d\n"
                         "tkhd_height=%d\n"
                         "language = %s\n"
                         "handler = %s\n"
                         "width = %d\n"
                         "height = %d\n"
                         "codec = %s\n",
                         i, getHandlerType(s->type),
                         s->tkhd_width,
                         s->tkhd_height,
                         s->language,
                         s->handler,
                         s->width,
                         s->height,
                         s->codec_name);
        }
        if(s->type == HANDLER_AUDIO)
        {
            info.sprintf("stream %d:%s\n"
                         "language = %s\n"
                         "handler = %s\n"
                         "channel_count = %d\n"
                         "sample_size = %d\n"
                         "sample_rate = %d\n"
                         "codec = %s\n",
                         i, getHandlerType(s->type),
                         s->language,
                         s->handler,
                         s->channel_count,
                         s->sample_size,
                         s->sample_rate,
                         s->codec_name);
        }
        edit->append(info);
        if(s->stts_count > 0)
        {
            info.sprintf("stts_count = %d", s->stts_count);
            edit->append(info);
            for(int j=0;j<s->stts_count;j++)
            {
                info.sprintf("sample_count = %d, delta = %d", s->stts_data[j].sample_count, s->stts_data[j].sample_delta);
                edit->append(info);
            }
        }
        info.sprintf("sync frame count = %d\n"
                     "ctts count = %d\n",
                     s->stss_count,
                     s->ctts_count);
        edit->append(info);
        edit->append("\n");
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
