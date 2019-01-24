/// \file
/// \brief A structure that holds all statistical data returned by RakNet.
///
/// This file is part of RakNet Copyright 2003 Kevin Jenkins.
///
/// Usage of RakNet is subject to the appropriate license agreement.
/// Creative Commons Licensees are subject to the
/// license found at
/// http://creativecommons.org/licenses/by-nc/2.5/
/// Single application licensees are subject to the license found at
/// http://www.rakkarsoft.com/SingleApplicationLicense.html
/// Custom license users are subject to the terms therein.
/// GPL license users are subject to the GNU General Public
/// License as published by the Free
/// Software Foundation; either version 2 of the License, or (at your
/// option) any later version.

#ifndef __RAK_NET_REMOTE_SYSTEM_H
#define __RAK_NET_REMOTE_SYSTEM_H

#include "Export.h"
#include "NetworkTypes.h"
#include "ReliabilityLayer.h"
#include "BitStream.h"
#include "RPCMap.h"

/// \brief Network Statisics Usage
///
/// Store Statistics information related to network usage
/// \internal
/// \brief Holds the clock differences between systems, along with the ping
struct PingAndClockDifferential
{
    unsigned short pingTime;
    RakNetTime clockDifferential;
};

/// \internal
/// \brief All the information representing a connected system system
struct RAK_DLL_EXPORT RemoteSystemStruct
{
    bool isActive; // Is this structure in use?
    PlayerID playerId;  /// The remote system associated with this reliability layer
    PlayerID myExternalPlayerId;  /// Your own IP, as reported by the remote system
    ReliabilityLayer reliabilityLayer;  /// The reliability layer associated with this player
    bool weInitiatedTheConnection; /// True if we started this connection via Connect.  False if someone else connected to us.
    PingAndClockDifferential pingAndClockDifferential[PING_TIMES_ARRAY_SIZE];  /// last x ping times and calculated clock differentials with it
    int pingAndClockDifferentialWriteIndex;  /// The index we are writing into the pingAndClockDifferential circular buffer
    unsigned short lowestPing; ///The lowest ping value encountered
    RakNetTime nextPingTime;  /// When to next ping this player
    RakNetTime lastReliableSend; /// When did the last reliable send occur.  Reliable sends must occur at least once every timeoutTime/2 units to notice disconnects
    RakNet::BitStream staticData; /// static data.  This cannot be a pointer because it might be accessed in another thread.
    RakNetTime connectionTime; /// connection time, if active.
    unsigned char AESKey[16]; /// Security key.
    bool setAESKey; /// true if security is enabled.
    RPCMap rpcMap; /// Mapping of RPC calls to single byte integers to save transmission bandwidth.
    enum ConnectMode
    {
        NO_ACTION, DISCONNECT_ASAP, DISCONNECT_ASAP_SILENTLY, DISCONNECT_ON_NO_ACK, REQUESTED_CONNECTION, HANDLING_CONNECTION_REQUEST, UNVERIFIED_SENDER, SET_ENCRYPTION_ON_MULTIPLE_16_BYTE_PACKET, CONNECTED
    } connectMode;
    unsigned char m_byteAuthTableIndex;
    unsigned char m_byteAuthType;
    bool m_bIsLogon;
};
#endif
