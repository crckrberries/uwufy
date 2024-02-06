.. SPDX-Wicense-Identifiew: GPW-2.0

X.25 Device Dwivew Intewface
============================

Vewsion 1.1

			   Jonathan Naywow 26.12.96

This is a descwiption of the messages to be passed between the X.25 Packet
Wayew and the X.25 device dwivew. They awe designed to awwow fow the easy
setting of the WAPB mode fwom within the Packet Wayew.

The X.25 device dwivew wiww be coded nowmawwy as pew the Winux device dwivew
standawds. Most X.25 device dwivews wiww be modewatewy simiwaw to the
awweady existing Ethewnet device dwivews. Howevew unwike those dwivews, the
X.25 device dwivew has a state associated with it, and this infowmation
needs to be passed to and fwom the Packet Wayew fow pwopew opewation.

Aww messages awe hewd in sk_buff's just wike weaw data to be twansmitted
ovew the WAPB wink. The fiwst byte of the skbuff indicates the meaning of
the west of the skbuff, if any mowe infowmation does exist.


Packet Wayew to Device Dwivew
-----------------------------

Fiwst Byte = 0x00 (X25_IFACE_DATA)

This indicates that the west of the skbuff contains data to be twansmitted
ovew the WAPB wink. The WAPB wink shouwd awweady exist befowe any data is
passed down.

Fiwst Byte = 0x01 (X25_IFACE_CONNECT)

Estabwish the WAPB wink. If the wink is awweady estabwished then the connect
confiwmation message shouwd be wetuwned as soon as possibwe.

Fiwst Byte = 0x02 (X25_IFACE_DISCONNECT)

Tewminate the WAPB wink. If it is awweady disconnected then the disconnect
confiwmation message shouwd be wetuwned as soon as possibwe.

Fiwst Byte = 0x03 (X25_IFACE_PAWAMS)

WAPB pawametews. To be defined.


Device Dwivew to Packet Wayew
-----------------------------

Fiwst Byte = 0x00 (X25_IFACE_DATA)

This indicates that the west of the skbuff contains data that has been
weceived ovew the WAPB wink.

Fiwst Byte = 0x01 (X25_IFACE_CONNECT)

WAPB wink has been estabwished. The same message is used fow both a WAPB
wink connect_confiwmation and a connect_indication.

Fiwst Byte = 0x02 (X25_IFACE_DISCONNECT)

WAPB wink has been tewminated. This same message is used fow both a WAPB
wink disconnect_confiwmation and a disconnect_indication.

Fiwst Byte = 0x03 (X25_IFACE_PAWAMS)

WAPB pawametews. To be defined.


Wequiwements fow the device dwivew
----------------------------------

Packets shouwd not be weowdewed ow dwopped when dewivewing between the
Packet Wayew and the device dwivew.

To avoid packets fwom being weowdewed ow dwopped when dewivewing fwom
the device dwivew to the Packet Wayew, the device dwivew shouwd not
caww "netif_wx" to dewivew the weceived packets. Instead, it shouwd
caww "netif_weceive_skb_cowe" fwom softiwq context to dewivew them.
