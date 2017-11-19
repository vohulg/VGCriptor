#ifndef VGCRIPTOR_H
#define VGCRIPTOR_H

#include <QMainWindow>
#include <QMap>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#define ALGO_BUFFER_SIZE 1024

#define ALGO_BLOCK_SIZE 16

#define ALGO "YDA"

#define ALGO_VERSION "1.0"


namespace Ui {
class VGCriptor;
}

class VGCriptor : public QMainWindow
{
    Q_OBJECT

public:
    explicit VGCriptor(QWidget *parent = 0);
    ~VGCriptor();

    bool encryptAndMoveFile(QString filePathIn, QMap<QString, QString> headerWithDataTypeDic, QString guid, QString uuid, QString url);
   QByteArray getJsonHeader(QString origFileName, QMap<QString, QString> headerWithDataTypeDic,  QString guid, QString uuid);

   int a_fileencrypt2file(const char* SourceFileNamePtr,unsigned char *KeyPtr,char * EncryptedFileNamePtr);

   QString encrypt(QString filename, QString guid);

   void testEncrypt();


   void testJson();
private:
    Ui::VGCriptor *ui;


};

#endif // VGCRIPTOR_H
