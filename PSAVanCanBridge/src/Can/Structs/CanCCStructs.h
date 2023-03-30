
// CANCCStructs.h
#pragma once

#ifndef _CANCCStructs_h
    #define _CANCCStructs_h

#include "../AbstractCanMessageSender.h"
#include "../../Helpers/PacketGenerator.h"

const uint16_t CAN_CC_INTERVAL = 1000;

// CANID: 1A8
const uint16_t CAN_CC = 0x1A8;

// Read right to left in documentation
typedef struct {
        uint8_t setting_status              : 1; // bit 0
        uint8_t unit_of_speed               : 1; // bit 1
        uint8_t activate_function           : 1; // bit 2
        uint8_t status_of_selected_function : 3; // bit 3-5
        uint8_t selected_function           : 2; // bit 6-7
    } CanCCByte1Struct;

// Read left to right in documentation
struct CanCCStruct {
    uint8_t CruiseControlMode;
    uint8_t CruiseControlSpeed1;
    uint8_t CruiseControlSpeed2;
    uint8_t Field4;
    uint8_t Field5;
    uint8_t TripOnCMB1;
    uint8_t TripOnCMB2;
    uint8_t TripOnCMB3;
};

union CanCCPacket {
    CanCCStruct data;
    uint8_t CanCCPacket[sizeof(CanCCStruct)];
};

class CanCCPacketSender
{
    AbstractCanMessageSender * canMessageSender;

    public:
    CanCCPacketSender(AbstractCanMessageSender * object)
    {
        canMessageSender = object;
    }
void SendData(
    uint8_t cruiseControlMode,
    uint8_t cruiseControlSpeed1,
    uint8_t cruiseControlSpeed2,
    uint8_t tripOnCMB1,
    uint8_t tripOnCMB2,
    uint8_t tripOnCMB3
    )
    
  {
    PacketGenerator<CanCCPacket> generator;
    generator.packet.data.CruiseControlMode = cruiseControlMode;
    generator.packet.data.CruiseControlSpeed1 = cruiseControlSpeed1;
    generator.packet.data.CruiseControlSpeed2 = cruiseControlSpeed2;
    generator.packet.data.TripOnCMB1 = tripOnCMB1;
    generator.packet.data.TripOnCMB2 = tripOnCMB2;
    generator.packet.data.TripOnCMB3 = tripOnCMB3;

    unsigned char *serializedPacket = generator.GetSerializedPacket();
    canMessageSender->SendMessage(CAN_CC, 0, sizeof(CanCCPacket), serializedPacket);
  }
};
#endif
