#include "musicdownloadrecordconfigmanager.h"

MusicDownloadRecordConfigManager::MusicDownloadRecordConfigManager(MusicObject::Record type, QObject *parent)
    : TTKAbstractXml(parent),
      m_type(type)
{

}

void MusicDownloadRecordConfigManager::readBuffer(MusicSongList &items)
{
    const QDomNodeList &nodeList = m_document->elementsByTagName("value");
    for(int i = 0; i < nodeList.count(); ++i)
    {
        MusicSong record;
        record.setName(nodeList.at(i).toElement().attribute("name"));
        record.setSizeStr(nodeList.at(i).toElement().attribute("size"));
        record.setAddTimeStr(nodeList.at(i).toElement().attribute("time"));
        record.setPath(nodeList.at(i).toElement().text());
        items << record;
    }
}

void MusicDownloadRecordConfigManager::writeBuffer(const MusicSongList &items)
{
    if(!toFile(mappingFilePathFromEnum()))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot(APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "record");

    for(const MusicSong &record : qAsConst(items))
    {
        writeDomMutilElementText(recordDom, "value", {{"name", record.name()},
                                                      {"size", record.sizeStr()},
                                                      {"time", record.addTimeStr()}}, record.path());
    }

    QTextStream out(m_file);
    m_document->save(out, 4);
}

QString MusicDownloadRecordConfigManager::mappingFilePathFromEnum() const
{
    switch(m_type)
    {
        case MusicObject::Record::NormalDownload: return NORMAL_DOWN_PATH_FULL;
        case MusicObject::Record::CloudDownload: return CLOUD_DOWN_PATH_FULL;
        case MusicObject::Record::CloudUpload: return CLOUD_UP_PATH_FULL;
        default: return QString();
    }
}
