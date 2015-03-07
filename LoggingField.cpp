/*************************************************************************
File encoding: UTF-8.
*************************************************************************/

#include "LoggingField.h"

int LoggingField::msgBufferSize() const
{
    return m_msgBufferSize;
}

void LoggingField::setMsgBufferSize(const int size)
{
    if(size >= 1)
    {
        if(size != m_msgBufferSize)
        {
            if(size >= m_messagesBuffer.size()) //сброс сообщений в текстовое поле, в случае уменьшения размера буфера,
                                                //в т.ч. на случай, если после уменьшения размера сообщения поступать не будут
            {
                this->append(m_messagesBuffer.join("\n"));
                m_messagesBuffer.clear();
            }
            m_msgBufferSize = size;
        }
    }
}

void LoggingField::addMessage(const bool errorMsg, const QString &text)
{
    if(m_messagesBuffer.size() >= m_msgBufferSize)
    {
        this->append(m_messagesBuffer.join("\n"));
        m_messagesBuffer.clear();
    }

    if(errorMsg)
    {
        m_messagesBuffer.append("<font color=red>"   + text + "</font>");
    }
    else
    {
        m_messagesBuffer.append("<font color=black>" + text + "</font>");
    }
}

LoggingField::LoggingField(QWidget *parent) : QTextEdit(parent){}
LoggingField::~LoggingField(){}
