#include "VGCriptor.h"
#include "ui_VGCriptor.h"
#include "aes.h"
#include <strings.h>
#include <QDir>

VGCriptor::VGCriptor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VGCriptor)
{
    ui->setupUi(this);

    testEncrypt();


}



int VGCriptor::a_fileencrypt2file(const char* SourceFileNamePtr,unsigned char *KeyPtr,char * EncryptedFileNamePtr) {

    unsigned char input[ALGO_BUFFER_SIZE],
    output[ALGO_BUFFER_SIZE],
    key[ALGO_BLOCK_SIZE],
    iv[ALGO_BLOCK_SIZE],
    algo[3],
    algo_ver[3];

    char FN[255], FDestName[255];
    //char *StrPtr, *StrEndPtr;
    FILE *FSource, *FDest;
    int  I, rem;
    size_t Count;
    //bool isCrypt = true;

    memset(&algo,0, 3);
    memset(&algo_ver,0, 3);
    memset(&iv,0, ALGO_BLOCK_SIZE);
    memset(&FN,0, 255);
    memset(&FDestName,0, 255);
    memset(&key,0, ALGO_BLOCK_SIZE);

    if ((FSource = fopen(SourceFileNamePtr, "rb")) == NULL) {
        return 1;   //encrypt error, bad file
    };


    sprintf(FDestName, "%s.%s", SourceFileNamePtr, "enc");
    //open output file
    if ((FDest = fopen(FDestName, "wb")) == NULL) {
        return 1;   //decrypt error, write file error
    };


    // write header to destfile
    fwrite(&ALGO, 1, 3, FDest);
    fwrite(&ALGO_VERSION, 1, 3, FDest);


    uint8_t randonData[ALGO_BLOCK_SIZE];
    for (int i = 0; i < ALGO_BLOCK_SIZE; i++){
        randonData[i] = rand();
    }

   //int error = SecRandomCopyBytes(kSecRandomDefault, ALGO_BLOCK_SIZE, randonData);

  //  if(error != noErr){
  //      qDebug() << "Faild to get random ! \n";
        //NSLog(@"Faild to get random ! \n");

 //   }


    printf("randonData content: \n");
    for (int i = 0; i < ALGO_BLOCK_SIZE; i++){
        printf("%x ", randonData[i]);
    }

    fwrite(randonData, 1, ALGO_BLOCK_SIZE, FDest);


    /*
    void* randonData = malloc(ALGO_BLOCK_SIZE);
    size_t ret2 = fwrite(randonData, 1, ALGO_BLOCK_SIZE, FDest);
    free(randonData);
    */


    //create key



    for (I = 20; I < 36; I++){
        key[I-20] = KeyPtr[I];
    }



    while (!feof(FSource)) {
        memset(&input,0, ALGO_BUFFER_SIZE);
        Count = fread(&input, 1, ALGO_BUFFER_SIZE, FSource);
        memset(&output,0, ALGO_BUFFER_SIZE);

        if (Count < ALGO_BUFFER_SIZE) {
            rem = ALGO_BLOCK_SIZE - (Count % ALGO_BLOCK_SIZE);

            for (size_t i = Count; i < (Count + rem); i++) {
                input[i] = rem;
            }
        }

        else
            rem = 0;




        AES128_CBC_encrypt_buffer(&output[0], &input[0], ALGO_BUFFER_SIZE, &key[0], randonData);

        fwrite(&output, 1, Count + rem, FDest);
    }

    fclose(FSource);
    fclose(FDest);
    memcpy(EncryptedFileNamePtr, &FDestName[0], 255);
    return 0; //decrypt OK

}

QString VGCriptor::encrypt(QString filename, QString guid)
{
     QByteArray fnameBA = filename.toLatin1();
     const char *SourceFileNamePtr = fnameBA.data();

      QByteArray keyBA = guid.toLatin1();

    unsigned char* KeyPtr = (unsigned char*)keyBA.data();

        //char *SourceFileNamePtr = "/Users/admin/common/Cypher/file.txt";
       //unsigned char KeyPtr[] = "qwer1234asdf1234qwer1234qwer1234";
        //char *SourceFileNamePtr = "/private/var/tmp/tracer/file.txt";
       char EncryptedFileNamePtr[255];
      // [self a_fileencrypt2file:SourceFileNamePtr andPassword:KeyPtr andEncryptedFile:EncryptedFileNamePtr];

       a_fileencrypt2file(SourceFileNamePtr, KeyPtr,EncryptedFileNamePtr);

       QString encryptedFile = QString(EncryptedFileNamePtr);//[NSString stringWithUTF8String:EncryptedFileNamePtr];

       return encryptedFile;


}

void VGCriptor::testEncrypt()
{

    QString path = QString("%1/Desktop/encrypt/test.txt").arg(QDir::homePath());
    QString guid = "qwer1234asdf1234qwer1234qwer1234";

    encrypt(path,guid);

    int x = 0;

}


VGCriptor::~VGCriptor()
{
    delete ui;
}

bool VGCriptor::encryptAndMoveFile(QString filePathIn, QMap<QString, QString> headerWithDataTypeDic, QString guid, QString uuid, QString url)
{
    return NULL;
}

QByteArray VGCriptor::getJsonHeader(QString origFileName, QMap<QString, QString> headerWithDataTypeDic, QString guid, QString uuid)
{

    return NULL;



}

void VGCriptor::testJson(){

     QJsonObject json;

     //add additional map

    QMap<QString, QString> additionalMap;
    additionalMap.insert("addkey", "addvalue");
    additionalMap.insert("addkey33", "addvalu33e");
    QMapIterator<QString, QString> iterAdd(additionalMap);

    while (iterAdd.hasNext()) {
        iterAdd.next();
        json.insert(iterAdd.key(), iterAdd.value());
    }

     //add main map

    QMap<QString, QString> mainMap;
    mainMap.insert("mykey", "myvalue");
    mainMap.insert("myke1y", "myvalue1");
    QMapIterator<QString, QString> iter(mainMap);

    while (iter.hasNext()) {
        iter.next();
        json.insert(iter.key(), iter.value());
    }

    QJsonDocument jsonDoc(json);
    QByteArray jsonBytes = jsonDoc.toJson();
    jsonBytes.replace("\n", "");
    jsonBytes.replace(" ", "");

    qDebug() << jsonBytes;
}
