/*************************************************************************
File encoding: UTF-8.
*************************************************************************/

#ifndef LOGGINGFIELD_H
#define LOGGINGFIELD_H

#include <QtCore>
#include <QtWidgets>
#include <QtGui>

class LoggingField : public QTextEdit
{
    Q_OBJECT

private:
    QStringList m_messagesBuffer;
    int m_msgBufferSize;
    Q_PROPERTY(int msgBufferSize READ msgBufferSize WRITE setMsgBufferSize MEMBER m_msgBufferSize)

public:
    explicit LoggingField(QWidget *parent = 0);
    ~LoggingField();

public slots:
    void addMessage(const bool errorMsg = false, const QString &text = QString());
    int msgBufferSize() const;
    void setMsgBufferSize(const int size);
};

#endif // LOGGINGFIELD_H
