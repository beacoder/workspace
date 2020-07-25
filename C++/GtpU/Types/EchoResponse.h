#ifndef GTPU_TYPES_ECHORESPONSE_H
#define GTPU_TYPES_ECHORESPONSE_H

#include "Interfaces/IMessage.h"

class EchoResponse : public IMessage
{
public:
    EchoResponse();

private:
    //-----------Begin IMessage-------------------
    IMessage::MessageType getMessageType() const override;
    void serialize(std::vector<char>& data) override;
    void unserialize(std::vector<char>& data) override;
    //-----------End IMessage---------------------
}

#endif // GTPU_TYPES_ECHORESPONSE_H
