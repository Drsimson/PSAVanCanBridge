// CANCCMessageHandler.h
#pragma once

#ifndef _CANCCMessageHandler_h
    #define _CANCCMessageHandler_h

#include "../AbstractCanMessageSender.h"
#include "../Handlers/CanMessageHandlerBase.h"
#include "../Structs/CanCCStructs.h"

class CanCCMessageHandler : public CanMessageHandlerBase 
{
    CanCCPacketSender* CCSender;

    uint8_t _cruiseControlMode;
    uint8_t _cruiseControlSpeed1;
    uint8_t _cruiseControlSpeed2;
    uint8_t _tripOnCMB1;
    uint8_t _tripOnCMB2;
    uint8_t _tripOnCMB3;

    virtual void InternalProcess() override 
    {
       CCSender->SendData(_cruiseControlMode, _cruiseControlSpeed1, _cruiseControlSpeed2, _tripOnCMB1, _tripOnCMB2, _tripOnCMB3);
    }

    public:
    CanCCMessageHandler(AbstractCanMessageSender * object) : CanMessageHandlerBase(object, CAN_CC_INTERVAL)
   {
       CCSender = new CanCCPacketSender(object);
   }
    void SetData
    (
    uint8_t cruiseControlMode,
    uint8_t cruiseControlSpeed1,
    uint8_t cruiseControlSpeed2,
    uint8_t tripOnCMB1,
    uint8_t tripOnCMB2,
    uint8_t tripOnCMB3
    )
   {
    _cruiseControlMode = cruiseControlMode;
    _cruiseControlSpeed1 = cruiseControlSpeed1;
    _cruiseControlSpeed2 = cruiseControlSpeed2;
    _tripOnCMB1 = tripOnCMB1;
    _tripOnCMB2 = tripOnCMB2;
    _tripOnCMB3 = tripOnCMB3;
    //CCSender->SetData(ccStruct.CruiseControlMode, ccStruct.CruiseControlSpeed1, ccStruct.CruiseControlSpeed2);
   }
};
#endif