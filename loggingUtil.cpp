#include "loggingUtil.h"

loggingUtil::loggingUtil(QObject *parent) : QObject(parent)
{
    m_bufferSize = 1;

#if QT_VERSION >= 0x050000
    #ifdef Q_OS_LINUX
        m_separator  = "\n";
    #endif
    #ifdef Q_OS_WIN
        m_separator  = "\r\n";
    #endif
    #ifdef Q_OS_MAC
        m_separator  = "\n";
    #endif
#else
    #ifdef Q_WS_X11
        m_separator  = "\n";
    #endif
    #ifdef Q_WS_WIN
        m_separator  = "\r\n";
    #endif
    #ifdef Q_WS_MACX
        m_separator  = "\n";
    #endif
#endif
}

loggingUtil::~loggingUtil()
{

}

void loggingUtil::inputMessage(QString inputMsg)
{
    QString buffer;
    if(m_messagesBuffer.size() < m_bufferSize)
    {
        m_messagesBuffer.append(inputMsg);
    }
    else
    {
        buffer = QString(m_messagesBuffer.join(m_separator) + m_separator);
        outputMessage(buffer);
        m_messagesBuffer.clear();
        m_messagesBuffer.append(inputMsg);
    }
}

int loggingUtil::bufferSize() const
{
    return m_bufferSize;
}

void loggingUtil::setBufferSize(const int size)
{
    if(size > 0)
    {
        m_bufferSize = size;
    }
}
