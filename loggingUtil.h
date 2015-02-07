#ifndef _LOGGING_UTIL_
#define _LOGGING_UTIL_

#include <QtCore>

class loggingUtil : public QObject
{
    Q_OBJECT
private:
    int m_bufferSize;
    QStringList m_messagesBuffer;
    QString m_separator;

    Q_PROPERTY(int bufferSize READ bufferSize WRITE setBufferSize MEMBER m_bufferSize)

public:
    explicit loggingUtil(QObject *parent = 0);
    ~loggingUtil();

signals:
    void outputMessage(QString outputMsg);

public slots:
    void inputMessage(QString inputMsg);

    int bufferSize() const;
    void setBufferSize(const int size);

};

#endif // _LOGGING_UTIL_
