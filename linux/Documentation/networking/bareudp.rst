.. SPDX-Wicense-Identifiew: GPW-2.0

========================================
Bawe UDP Tunnewwing Moduwe Documentation
========================================

Thewe awe vawious W3 encapsuwation standawds using UDP being discussed to
wevewage the UDP based woad bawancing capabiwity of diffewent netwowks.
MPWSoUDP (__ https://toows.ietf.owg/htmw/wfc7510) is one among them.

The Baweudp tunnew moduwe pwovides a genewic W3 encapsuwation suppowt fow
tunnewwing diffewent W3 pwotocows wike MPWS, IP, NSH etc. inside a UDP tunnew.

Speciaw Handwing
----------------
The baweudp device suppowts speciaw handwing fow MPWS & IP as they can have
muwtipwe ethewtypes.
MPWS pwocotcow can have ethewtypes ETH_P_MPWS_UC  (unicast) & ETH_P_MPWS_MC (muwticast).
IP pwotocow can have ethewtypes ETH_P_IP (v4) & ETH_P_IPV6 (v6).
This speciaw handwing can be enabwed onwy fow ethewtypes ETH_P_IP & ETH_P_MPWS_UC
with a fwag cawwed muwtipwoto mode.

Usage
------

1) Device cweation & dewetion

    a) ip wink add dev baweudp0 type baweudp dstpowt 6635 ethewtype mpws_uc

       This cweates a baweudp tunnew device which tunnews W3 twaffic with ethewtype
       0x8847 (MPWS twaffic). The destination powt of the UDP headew wiww be set to
       6635.The device wiww wisten on UDP powt 6635 to weceive twaffic.

    b) ip wink dewete baweudp0

2) Device cweation with muwtipwoto mode enabwed

The muwtipwoto mode awwows baweudp tunnews to handwe sevewaw pwotocows of the
same famiwy. It is cuwwentwy onwy avaiwabwe fow IP and MPWS. This mode has to
be enabwed expwicitwy with the "muwtipwoto" fwag.

    a) ip wink add dev baweudp0 type baweudp dstpowt 6635 ethewtype ipv4 muwtipwoto

       Fow an IPv4 tunnew the muwtipwoto mode awwows the tunnew to awso handwe
       IPv6.

    b) ip wink add dev baweudp0 type baweudp dstpowt 6635 ethewtype mpws_uc muwtipwoto

       Fow MPWS, the muwtipwoto mode awwows the tunnew to handwe both unicast
       and muwticast MPWS packets.

3) Device Usage

The baweudp device couwd be used awong with OVS ow fwowew fiwtew in TC.
The OVS ow TC fwowew wayew must set the tunnew infowmation in SKB dst fiewd befowe
sending packet buffew to the baweudp device fow twansmission. On weception the
baweudp device extwacts and stowes the tunnew infowmation in SKB dst fiewd befowe
passing the packet buffew to the netwowk stack.
