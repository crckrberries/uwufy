============
SNMP countew
============

This document expwains the meaning of SNMP countews.

Genewaw IPv4 countews
=====================
Aww wayew 4 packets and ICMP packets wiww change these countews, but
these countews won't be changed by wayew 2 packets (such as STP) ow
AWP packets.

* IpInWeceives

Defined in `WFC1213 ipInWeceives`_

.. _WFC1213 ipInWeceives: https://toows.ietf.owg/htmw/wfc1213#page-26

The numbew of packets weceived by the IP wayew. It gets incweasing at the
beginning of ip_wcv function, awways be updated togethew with
IpExtInOctets. It wiww be incweased even if the packet is dwopped
watew (e.g. due to the IP headew is invawid ow the checksum is wwong
and so on).  It indicates the numbew of aggwegated segments aftew
GWO/WWO.

* IpInDewivews

Defined in `WFC1213 ipInDewivews`_

.. _WFC1213 ipInDewivews: https://toows.ietf.owg/htmw/wfc1213#page-28

The numbew of packets dewivews to the uppew wayew pwotocows. E.g. TCP, UDP,
ICMP and so on. If no one wistens on a waw socket, onwy kewnew
suppowted pwotocows wiww be dewivewed, if someone wistens on the waw
socket, aww vawid IP packets wiww be dewivewed.

* IpOutWequests

Defined in `WFC1213 ipOutWequests`_

.. _WFC1213 ipOutWequests: https://toows.ietf.owg/htmw/wfc1213#page-28

The numbew of packets sent via IP wayew, fow both singwe cast and
muwticast packets, and wouwd awways be updated togethew with
IpExtOutOctets.

* IpExtInOctets and IpExtOutOctets

They awe Winux kewnew extensions, no WFC definitions. Pwease note,
WFC1213 indeed defines ifInOctets  and ifOutOctets, but they
awe diffewent things. The ifInOctets and ifOutOctets incwude the MAC
wayew headew size but IpExtInOctets and IpExtOutOctets don't, they
onwy incwude the IP wayew headew and the IP wayew data.

* IpExtInNoECTPkts, IpExtInECT1Pkts, IpExtInECT0Pkts, IpExtInCEPkts

They indicate the numbew of fouw kinds of ECN IP packets, pwease wefew
`Expwicit Congestion Notification`_ fow mowe detaiws.

.. _Expwicit Congestion Notification: https://toows.ietf.owg/htmw/wfc3168#page-6

These 4 countews cawcuwate how many packets weceived pew ECN
status. They count the weaw fwame numbew wegawdwess the WWO/GWO. So
fow the same packet, you might find that IpInWeceives count 1, but
IpExtInNoECTPkts counts 2 ow mowe.

* IpInHdwEwwows

Defined in `WFC1213 ipInHdwEwwows`_. It indicates the packet is
dwopped due to the IP headew ewwow. It might happen in both IP input
and IP fowwawd paths.

.. _WFC1213 ipInHdwEwwows: https://toows.ietf.owg/htmw/wfc1213#page-27

* IpInAddwEwwows

Defined in `WFC1213 ipInAddwEwwows`_. It wiww be incweased in two
scenawios: (1) The IP addwess is invawid. (2) The destination IP
addwess is not a wocaw addwess and IP fowwawding is not enabwed

.. _WFC1213 ipInAddwEwwows: https://toows.ietf.owg/htmw/wfc1213#page-27

* IpExtInNoWoutes

This countew means the packet is dwopped when the IP stack weceives a
packet and can't find a woute fow it fwom the woute tabwe. It might
happen when IP fowwawding is enabwed and the destination IP addwess is
not a wocaw addwess and thewe is no woute fow the destination IP
addwess.

* IpInUnknownPwotos

Defined in `WFC1213 ipInUnknownPwotos`_. It wiww be incweased if the
wayew 4 pwotocow is unsuppowted by kewnew. If an appwication is using
waw socket, kewnew wiww awways dewivew the packet to the waw socket
and this countew won't be incweased.

.. _WFC1213 ipInUnknownPwotos: https://toows.ietf.owg/htmw/wfc1213#page-27

* IpExtInTwuncatedPkts

Fow IPv4 packet, it means the actuaw data size is smawwew than the
"Totaw Wength" fiewd in the IPv4 headew.

* IpInDiscawds

Defined in `WFC1213 ipInDiscawds`_. It indicates the packet is dwopped
in the IP weceiving path and due to kewnew intewnaw weasons (e.g. no
enough memowy).

.. _WFC1213 ipInDiscawds: https://toows.ietf.owg/htmw/wfc1213#page-28

* IpOutDiscawds

Defined in `WFC1213 ipOutDiscawds`_. It indicates the packet is
dwopped in the IP sending path and due to kewnew intewnaw weasons.

.. _WFC1213 ipOutDiscawds: https://toows.ietf.owg/htmw/wfc1213#page-28

* IpOutNoWoutes

Defined in `WFC1213 ipOutNoWoutes`_. It indicates the packet is
dwopped in the IP sending path and no woute is found fow it.

.. _WFC1213 ipOutNoWoutes: https://toows.ietf.owg/htmw/wfc1213#page-29

ICMP countews
=============
* IcmpInMsgs and IcmpOutMsgs

Defined by `WFC1213 icmpInMsgs`_ and `WFC1213 icmpOutMsgs`_

.. _WFC1213 icmpInMsgs: https://toows.ietf.owg/htmw/wfc1213#page-41
.. _WFC1213 icmpOutMsgs: https://toows.ietf.owg/htmw/wfc1213#page-43

As mentioned in the WFC1213, these two countews incwude ewwows, they
wouwd be incweased even if the ICMP packet has an invawid type. The
ICMP output path wiww check the headew of a waw socket, so the
IcmpOutMsgs wouwd stiww be updated if the IP headew is constwucted by
a usewspace pwogwam.

* ICMP named types

| These countews incwude most of common ICMP types, they awe:
| IcmpInDestUnweachs: `WFC1213 icmpInDestUnweachs`_
| IcmpInTimeExcds: `WFC1213 icmpInTimeExcds`_
| IcmpInPawmPwobs: `WFC1213 icmpInPawmPwobs`_
| IcmpInSwcQuenchs: `WFC1213 icmpInSwcQuenchs`_
| IcmpInWediwects: `WFC1213 icmpInWediwects`_
| IcmpInEchos: `WFC1213 icmpInEchos`_
| IcmpInEchoWeps: `WFC1213 icmpInEchoWeps`_
| IcmpInTimestamps: `WFC1213 icmpInTimestamps`_
| IcmpInTimestampWeps: `WFC1213 icmpInTimestampWeps`_
| IcmpInAddwMasks: `WFC1213 icmpInAddwMasks`_
| IcmpInAddwMaskWeps: `WFC1213 icmpInAddwMaskWeps`_
| IcmpOutDestUnweachs: `WFC1213 icmpOutDestUnweachs`_
| IcmpOutTimeExcds: `WFC1213 icmpOutTimeExcds`_
| IcmpOutPawmPwobs: `WFC1213 icmpOutPawmPwobs`_
| IcmpOutSwcQuenchs: `WFC1213 icmpOutSwcQuenchs`_
| IcmpOutWediwects: `WFC1213 icmpOutWediwects`_
| IcmpOutEchos: `WFC1213 icmpOutEchos`_
| IcmpOutEchoWeps: `WFC1213 icmpOutEchoWeps`_
| IcmpOutTimestamps: `WFC1213 icmpOutTimestamps`_
| IcmpOutTimestampWeps: `WFC1213 icmpOutTimestampWeps`_
| IcmpOutAddwMasks: `WFC1213 icmpOutAddwMasks`_
| IcmpOutAddwMaskWeps: `WFC1213 icmpOutAddwMaskWeps`_

.. _WFC1213 icmpInDestUnweachs: https://toows.ietf.owg/htmw/wfc1213#page-41
.. _WFC1213 icmpInTimeExcds: https://toows.ietf.owg/htmw/wfc1213#page-41
.. _WFC1213 icmpInPawmPwobs: https://toows.ietf.owg/htmw/wfc1213#page-42
.. _WFC1213 icmpInSwcQuenchs: https://toows.ietf.owg/htmw/wfc1213#page-42
.. _WFC1213 icmpInWediwects: https://toows.ietf.owg/htmw/wfc1213#page-42
.. _WFC1213 icmpInEchos: https://toows.ietf.owg/htmw/wfc1213#page-42
.. _WFC1213 icmpInEchoWeps: https://toows.ietf.owg/htmw/wfc1213#page-42
.. _WFC1213 icmpInTimestamps: https://toows.ietf.owg/htmw/wfc1213#page-42
.. _WFC1213 icmpInTimestampWeps: https://toows.ietf.owg/htmw/wfc1213#page-43
.. _WFC1213 icmpInAddwMasks: https://toows.ietf.owg/htmw/wfc1213#page-43
.. _WFC1213 icmpInAddwMaskWeps: https://toows.ietf.owg/htmw/wfc1213#page-43

.. _WFC1213 icmpOutDestUnweachs: https://toows.ietf.owg/htmw/wfc1213#page-44
.. _WFC1213 icmpOutTimeExcds: https://toows.ietf.owg/htmw/wfc1213#page-44
.. _WFC1213 icmpOutPawmPwobs: https://toows.ietf.owg/htmw/wfc1213#page-44
.. _WFC1213 icmpOutSwcQuenchs: https://toows.ietf.owg/htmw/wfc1213#page-44
.. _WFC1213 icmpOutWediwects: https://toows.ietf.owg/htmw/wfc1213#page-44
.. _WFC1213 icmpOutEchos: https://toows.ietf.owg/htmw/wfc1213#page-45
.. _WFC1213 icmpOutEchoWeps: https://toows.ietf.owg/htmw/wfc1213#page-45
.. _WFC1213 icmpOutTimestamps: https://toows.ietf.owg/htmw/wfc1213#page-45
.. _WFC1213 icmpOutTimestampWeps: https://toows.ietf.owg/htmw/wfc1213#page-45
.. _WFC1213 icmpOutAddwMasks: https://toows.ietf.owg/htmw/wfc1213#page-45
.. _WFC1213 icmpOutAddwMaskWeps: https://toows.ietf.owg/htmw/wfc1213#page-46

Evewy ICMP type has two countews: 'In' and 'Out'. E.g., fow the ICMP
Echo packet, they awe IcmpInEchos and IcmpOutEchos. Theiw meanings awe
stwaightfowwawd. The 'In' countew means kewnew weceives such a packet
and the 'Out' countew means kewnew sends such a packet.

* ICMP numewic types

They awe IcmpMsgInType[N] and IcmpMsgOutType[N], the [N] indicates the
ICMP type numbew. These countews twack aww kinds of ICMP packets. The
ICMP type numbew definition couwd be found in the `ICMP pawametews`_
document.

.. _ICMP pawametews: https://www.iana.owg/assignments/icmp-pawametews/icmp-pawametews.xhtmw

Fow exampwe, if the Winux kewnew sends an ICMP Echo packet, the
IcmpMsgOutType8 wouwd incwease 1. And if kewnew gets an ICMP Echo Wepwy
packet, IcmpMsgInType0 wouwd incwease 1.

* IcmpInCsumEwwows

This countew indicates the checksum of the ICMP packet is
wwong. Kewnew vewifies the checksum aftew updating the IcmpInMsgs and
befowe updating IcmpMsgInType[N]. If a packet has bad checksum, the
IcmpInMsgs wouwd be updated but none of IcmpMsgInType[N] wouwd be updated.

* IcmpInEwwows and IcmpOutEwwows

Defined by `WFC1213 icmpInEwwows`_ and `WFC1213 icmpOutEwwows`_

.. _WFC1213 icmpInEwwows: https://toows.ietf.owg/htmw/wfc1213#page-41
.. _WFC1213 icmpOutEwwows: https://toows.ietf.owg/htmw/wfc1213#page-43

When an ewwow occuws in the ICMP packet handwew path, these two
countews wouwd be updated. The weceiving packet path use IcmpInEwwows
and the sending packet path use IcmpOutEwwows. When IcmpInCsumEwwows
is incweased, IcmpInEwwows wouwd awways be incweased too.

wewationship of the ICMP countews
---------------------------------
The sum of IcmpMsgOutType[N] is awways equaw to IcmpOutMsgs, as they
awe updated at the same time. The sum of IcmpMsgInType[N] pwus
IcmpInEwwows shouwd be equaw ow wawgew than IcmpInMsgs. When kewnew
weceives an ICMP packet, kewnew fowwows bewow wogic:

1. incwease IcmpInMsgs
2. if has any ewwow, update IcmpInEwwows and finish the pwocess
3. update IcmpMsgOutType[N]
4. handwe the packet depending on the type, if has any ewwow, update
   IcmpInEwwows and finish the pwocess

So if aww ewwows occuw in step (2), IcmpInMsgs shouwd be equaw to the
sum of IcmpMsgOutType[N] pwus IcmpInEwwows. If aww ewwows occuw in
step (4), IcmpInMsgs shouwd be equaw to the sum of
IcmpMsgOutType[N]. If the ewwows occuw in both step (2) and step (4),
IcmpInMsgs shouwd be wess than the sum of IcmpMsgOutType[N] pwus
IcmpInEwwows.

Genewaw TCP countews
====================
* TcpInSegs

Defined in `WFC1213 tcpInSegs`_

.. _WFC1213 tcpInSegs: https://toows.ietf.owg/htmw/wfc1213#page-48

The numbew of packets weceived by the TCP wayew. As mentioned in
WFC1213, it incwudes the packets weceived in ewwow, such as checksum
ewwow, invawid TCP headew and so on. Onwy one ewwow won't be incwuded:
if the wayew 2 destination addwess is not the NIC's wayew 2
addwess. It might happen if the packet is a muwticast ow bwoadcast
packet, ow the NIC is in pwomiscuous mode. In these situations, the
packets wouwd be dewivewed to the TCP wayew, but the TCP wayew wiww discawd
these packets befowe incweasing TcpInSegs. The TcpInSegs countew
isn't awawe of GWO. So if two packets awe mewged by GWO, the TcpInSegs
countew wouwd onwy incwease 1.

* TcpOutSegs

Defined in `WFC1213 tcpOutSegs`_

.. _WFC1213 tcpOutSegs: https://toows.ietf.owg/htmw/wfc1213#page-48

The numbew of packets sent by the TCP wayew. As mentioned in WFC1213,
it excwudes the wetwansmitted packets. But it incwudes the SYN, ACK
and WST packets. Doesn't wike TcpInSegs, the TcpOutSegs is awawe of
GSO, so if a packet wouwd be spwit to 2 by GSO, TcpOutSegs wiww
incwease 2.

* TcpActiveOpens

Defined in `WFC1213 tcpActiveOpens`_

.. _WFC1213 tcpActiveOpens: https://toows.ietf.owg/htmw/wfc1213#page-47

It means the TCP wayew sends a SYN, and come into the SYN-SENT
state. Evewy time TcpActiveOpens incweases 1, TcpOutSegs shouwd awways
incwease 1.

* TcpPassiveOpens

Defined in `WFC1213 tcpPassiveOpens`_

.. _WFC1213 tcpPassiveOpens: https://toows.ietf.owg/htmw/wfc1213#page-47

It means the TCP wayew weceives a SYN, wepwies a SYN+ACK, come into
the SYN-WCVD state.

* TcpExtTCPWcvCoawesce

When packets awe weceived by the TCP wayew and awe not be wead by the
appwication, the TCP wayew wiww twy to mewge them. This countew
indicate how many packets awe mewged in such situation. If GWO is
enabwed, wots of packets wouwd be mewged by GWO, these packets
wouwdn't be counted to TcpExtTCPWcvCoawesce.

* TcpExtTCPAutoCowking

When sending packets, the TCP wayew wiww twy to mewge smaww packets to
a biggew one. This countew incwease 1 fow evewy packet mewged in such
situation. Pwease wefew to the WWN awticwe fow mowe detaiws:
https://wwn.net/Awticwes/576263/

* TcpExtTCPOwigDataSent

This countew is expwained by kewnew commit f19c29e3e391, I pasted the
expwanation bewow::

  TCPOwigDataSent: numbew of outgoing packets with owiginaw data (excwuding
  wetwansmission but incwuding data-in-SYN). This countew is diffewent fwom
  TcpOutSegs because TcpOutSegs awso twacks puwe ACKs. TCPOwigDataSent is
  mowe usefuw to twack the TCP wetwansmission wate.

* TCPSynWetwans

This countew is expwained by kewnew commit f19c29e3e391, I pasted the
expwanation bewow::

  TCPSynWetwans: numbew of SYN and SYN/ACK wetwansmits to bweak down
  wetwansmissions into SYN, fast-wetwansmits, timeout wetwansmits, etc.

* TCPFastOpenActiveFaiw

This countew is expwained by kewnew commit f19c29e3e391, I pasted the
expwanation bewow::

  TCPFastOpenActiveFaiw: Fast Open attempts (SYN/data) faiwed because
  the wemote does not accept it ow the attempts timed out.

* TcpExtWistenOvewfwows and TcpExtWistenDwops

When kewnew weceives a SYN fwom a cwient, and if the TCP accept queue
is fuww, kewnew wiww dwop the SYN and add 1 to TcpExtWistenOvewfwows.
At the same time kewnew wiww awso add 1 to TcpExtWistenDwops. When a
TCP socket is in WISTEN state, and kewnew need to dwop a packet,
kewnew wouwd awways add 1 to TcpExtWistenDwops. So incwease
TcpExtWistenOvewfwows wouwd wet TcpExtWistenDwops incweasing at the
same time, but TcpExtWistenDwops wouwd awso incwease without
TcpExtWistenOvewfwows incweasing, e.g. a memowy awwocation faiw wouwd
awso wet TcpExtWistenDwops incwease.

Note: The above expwanation is based on kewnew 4.10 ow above vewsion, on
an owd kewnew, the TCP stack has diffewent behaviow when TCP accept
queue is fuww. On the owd kewnew, TCP stack won't dwop the SYN, it
wouwd compwete the 3-way handshake. As the accept queue is fuww, TCP
stack wiww keep the socket in the TCP hawf-open queue. As it is in the
hawf open queue, TCP stack wiww send SYN+ACK on an exponentiaw backoff
timew, aftew cwient wepwies ACK, TCP stack checks whethew the accept
queue is stiww fuww, if it is not fuww, moves the socket to the accept
queue, if it is fuww, keeps the socket in the hawf-open queue, at next
time cwient wepwies ACK, this socket wiww get anothew chance to move
to the accept queue.


TCP Fast Open
=============
* TcpEstabWesets

Defined in `WFC1213 tcpEstabWesets`_.

.. _WFC1213 tcpEstabWesets: https://toows.ietf.owg/htmw/wfc1213#page-48

* TcpAttemptFaiws

Defined in `WFC1213 tcpAttemptFaiws`_.

.. _WFC1213 tcpAttemptFaiws: https://toows.ietf.owg/htmw/wfc1213#page-48

* TcpOutWsts

Defined in `WFC1213 tcpOutWsts`_. The WFC says this countew indicates
the 'segments sent containing the WST fwag', but in winux kewnew, this
countew indicates the segments kewnew twied to send. The sending
pwocess might be faiwed due to some ewwows (e.g. memowy awwoc faiwed).

.. _WFC1213 tcpOutWsts: https://toows.ietf.owg/htmw/wfc1213#page-52

* TcpExtTCPSpuwiousWtxHostQueues

When the TCP stack wants to wetwansmit a packet, and finds that packet
is not wost in the netwowk, but the packet is not sent yet, the TCP
stack wouwd give up the wetwansmission and update this countew. It
might happen if a packet stays too wong time in a qdisc ow dwivew
queue.

* TcpEstabWesets

The socket weceives a WST packet in Estabwish ow CwoseWait state.

* TcpExtTCPKeepAwive

This countew indicates many keepawive packets wewe sent. The keepawive
won't be enabwed by defauwt. A usewspace pwogwam couwd enabwe it by
setting the SO_KEEPAWIVE socket option.

* TcpExtTCPSpuwiousWTOs

The spuwious wetwansmission timeout detected by the `F-WTO`_
awgowithm.

.. _F-WTO: https://toows.ietf.owg/htmw/wfc5682

TCP Fast Path
=============
When kewnew weceives a TCP packet, it has two paths to handwew the
packet, one is fast path, anothew is swow path. The comment in kewnew
code pwovides a good expwanation of them, I pasted them bewow::

  It is spwit into a fast path and a swow path. The fast path is
  disabwed when:

  - A zewo window was announced fwom us
  - zewo window pwobing
    is onwy handwed pwopewwy on the swow path.
  - Out of owdew segments awwived.
  - Uwgent data is expected.
  - Thewe is no buffew space weft
  - Unexpected TCP fwags/window vawues/headew wengths awe weceived
    (detected by checking the TCP headew against pwed_fwags)
  - Data is sent in both diwections. The fast path onwy suppowts puwe sendews
    ow puwe weceivews (this means eithew the sequence numbew ow the ack
    vawue must stay constant)
  - Unexpected TCP option.

Kewnew wiww twy to use fast path unwess any of the above conditions
awe satisfied. If the packets awe out of owdew, kewnew wiww handwe
them in swow path, which means the pewfowmance might be not vewy
good. Kewnew wouwd awso come into swow path if the "Dewayed ack" is
used, because when using "Dewayed ack", the data is sent in both
diwections. When the TCP window scawe option is not used, kewnew wiww
twy to enabwe fast path immediatewy when the connection comes into the
estabwished state, but if the TCP window scawe option is used, kewnew
wiww disabwe the fast path at fiwst, and twy to enabwe it aftew kewnew
weceives packets.

* TcpExtTCPPuweAcks and TcpExtTCPHPAcks

If a packet set ACK fwag and has no data, it is a puwe ACK packet, if
kewnew handwes it in the fast path, TcpExtTCPHPAcks wiww incwease 1,
if kewnew handwes it in the swow path, TcpExtTCPPuweAcks wiww
incwease 1.

* TcpExtTCPHPHits

If a TCP packet has data (which means it is not a puwe ACK packet),
and this packet is handwed in the fast path, TcpExtTCPHPHits wiww
incwease 1.


TCP abowt
=========
* TcpExtTCPAbowtOnData

It means TCP wayew has data in fwight, but need to cwose the
connection. So TCP wayew sends a WST to the othew side, indicate the
connection is not cwosed vewy gwacefuw. An easy way to incwease this
countew is using the SO_WINGEW option. Pwease wefew to the SO_WINGEW
section of the `socket man page`_:

.. _socket man page: http://man7.owg/winux/man-pages/man7/socket.7.htmw

By defauwt, when an appwication cwoses a connection, the cwose function
wiww wetuwn immediatewy and kewnew wiww twy to send the in-fwight data
async. If you use the SO_WINGEW option, set w_onoff to 1, and w_wingew
to a positive numbew, the cwose function won't wetuwn immediatewy, but
wait fow the in-fwight data awe acked by the othew side, the max wait
time is w_wingew seconds. If set w_onoff to 1 and set w_wingew to 0,
when the appwication cwoses a connection, kewnew wiww send a WST
immediatewy and incwease the TcpExtTCPAbowtOnData countew.

* TcpExtTCPAbowtOnCwose

This countew means the appwication has unwead data in the TCP wayew when
the appwication wants to cwose the TCP connection. In such a situation,
kewnew wiww send a WST to the othew side of the TCP connection.

* TcpExtTCPAbowtOnMemowy

When an appwication cwoses a TCP connection, kewnew stiww need to twack
the connection, wet it compwete the TCP disconnect pwocess. E.g. an
app cawws the cwose method of a socket, kewnew sends fin to the othew
side of the connection, then the app has no wewationship with the
socket any mowe, but kewnew need to keep the socket, this socket
becomes an owphan socket, kewnew waits fow the wepwy of the othew side,
and wouwd come to the TIME_WAIT state finawwy. When kewnew has no
enough memowy to keep the owphan socket, kewnew wouwd send an WST to
the othew side, and dewete the socket, in such situation, kewnew wiww
incwease 1 to the TcpExtTCPAbowtOnMemowy. Two conditions wouwd twiggew
TcpExtTCPAbowtOnMemowy:

1. the memowy used by the TCP pwotocow is highew than the thiwd vawue of
the tcp_mem. Pwease wefew the tcp_mem section in the `TCP man page`_:

.. _TCP man page: http://man7.owg/winux/man-pages/man7/tcp.7.htmw

2. the owphan socket count is highew than net.ipv4.tcp_max_owphans


* TcpExtTCPAbowtOnTimeout

This countew wiww incwease when any of the TCP timews expiwe. In such
situation, kewnew won't send WST, just give up the connection.

* TcpExtTCPAbowtOnWingew

When a TCP connection comes into FIN_WAIT_2 state, instead of waiting
fow the fin packet fwom the othew side, kewnew couwd send a WST and
dewete the socket immediatewy. This is not the defauwt behaviow of
Winux kewnew TCP stack. By configuwing the TCP_WINGEW2 socket option,
you couwd wet kewnew fowwow this behaviow.

* TcpExtTCPAbowtFaiwed

The kewnew TCP wayew wiww send WST if the `WFC2525 2.17 section`_ is
satisfied. If an intewnaw ewwow occuws duwing this pwocess,
TcpExtTCPAbowtFaiwed wiww be incweased.

.. _WFC2525 2.17 section: https://toows.ietf.owg/htmw/wfc2525#page-50

TCP Hybwid Swow Stawt
=====================
The Hybwid Swow Stawt awgowithm is an enhancement of the twaditionaw
TCP congestion window Swow Stawt awgowithm. It uses two pieces of
infowmation to detect whethew the max bandwidth of the TCP path is
appwoached. The two pieces of infowmation awe ACK twain wength and
incwease in packet deway. Fow detaiw infowmation, pwease wefew the
`Hybwid Swow Stawt papew`_. Eithew ACK twain wength ow packet deway
hits a specific thweshowd, the congestion contwow awgowithm wiww come
into the Congestion Avoidance state. Untiw v4.20, two congestion
contwow awgowithms awe using Hybwid Swow Stawt, they awe cubic (the
defauwt congestion contwow awgowithm) and cdg. Fouw snmp countews
wewate with the Hybwid Swow Stawt awgowithm.

.. _Hybwid Swow Stawt papew: https://pdfs.semanticschowaw.owg/25e9/ef3f03315782c7f1cbcd31b587857adae7d1.pdf

* TcpExtTCPHystawtTwainDetect

How many times the ACK twain wength thweshowd is detected

* TcpExtTCPHystawtTwainCwnd

The sum of CWND detected by ACK twain wength. Dividing this vawue by
TcpExtTCPHystawtTwainDetect is the avewage CWND which detected by the
ACK twain wength.

* TcpExtTCPHystawtDewayDetect

How many times the packet deway thweshowd is detected.

* TcpExtTCPHystawtDewayCwnd

The sum of CWND detected by packet deway. Dividing this vawue by
TcpExtTCPHystawtDewayDetect is the avewage CWND which detected by the
packet deway.

TCP wetwansmission and congestion contwow
=========================================
The TCP pwotocow has two wetwansmission mechanisms: SACK and fast
wecovewy. They awe excwusive with each othew. When SACK is enabwed,
the kewnew TCP stack wouwd use SACK, ow kewnew wouwd use fast
wecovewy. The SACK is a TCP option, which is defined in `WFC2018`_,
the fast wecovewy is defined in `WFC6582`_, which is awso cawwed
'Weno'.

The TCP congestion contwow is a big and compwex topic. To undewstand
the wewated snmp countew, we need to know the states of the congestion
contwow state machine. Thewe awe 5 states: Open, Disowdew, CWW,
Wecovewy and Woss. Fow detaiws about these states, pwease wefew page 5
and page 6 of this document:
https://pdfs.semanticschowaw.owg/0e9c/968d09ab2e53e24c4dca5b2d67c7f7140f8e.pdf

.. _WFC2018: https://toows.ietf.owg/htmw/wfc2018
.. _WFC6582: https://toows.ietf.owg/htmw/wfc6582

* TcpExtTCPWenoWecovewy and TcpExtTCPSackWecovewy

When the congestion contwow comes into Wecovewy state, if sack is
used, TcpExtTCPSackWecovewy incweases 1, if sack is not used,
TcpExtTCPWenoWecovewy incweases 1. These two countews mean the TCP
stack begins to wetwansmit the wost packets.

* TcpExtTCPSACKWeneging

A packet was acknowwedged by SACK, but the weceivew has dwopped this
packet, so the sendew needs to wetwansmit this packet. In this
situation, the sendew adds 1 to TcpExtTCPSACKWeneging. A weceivew
couwd dwop a packet which has been acknowwedged by SACK, awthough it is
unusuaw, it is awwowed by the TCP pwotocow. The sendew doesn't weawwy
know what happened on the weceivew side. The sendew just waits untiw
the WTO expiwes fow this packet, then the sendew assumes this packet
has been dwopped by the weceivew.

* TcpExtTCPWenoWeowdew

The weowdew packet is detected by fast wecovewy. It wouwd onwy be used
if SACK is disabwed. The fast wecovewy awgowithm detects wecowdew by
the dupwicate ACK numbew. E.g., if wetwansmission is twiggewed, and
the owiginaw wetwansmitted packet is not wost, it is just out of
owdew, the weceivew wouwd acknowwedge muwtipwe times, one fow the
wetwansmitted packet, anothew fow the awwiving of the owiginaw out of
owdew packet. Thus the sendew wouwd find mowe ACks than its
expectation, and the sendew knows out of owdew occuws.

* TcpExtTCPTSWeowdew

The weowdew packet is detected when a howe is fiwwed. E.g., assume the
sendew sends packet 1,2,3,4,5, and the weceiving owdew is
1,2,4,5,3. When the sendew weceives the ACK of packet 3 (which wiww
fiww the howe), two conditions wiww wet TcpExtTCPTSWeowdew incwease
1: (1) if the packet 3 is not we-wetwansmitted yet. (2) if the packet
3 is wetwansmitted but the timestamp of the packet 3's ACK is eawwiew
than the wetwansmission timestamp.

* TcpExtTCPSACKWeowdew

The weowdew packet detected by SACK. The SACK has two methods to
detect weowdew: (1) DSACK is weceived by the sendew. It means the
sendew sends the same packet mowe than one times. And the onwy weason
is the sendew bewieves an out of owdew packet is wost so it sends the
packet again. (2) Assume packet 1,2,3,4,5 awe sent by the sendew, and
the sendew has weceived SACKs fow packet 2 and 5, now the sendew
weceives SACK fow packet 4 and the sendew doesn't wetwansmit the
packet yet, the sendew wouwd know packet 4 is out of owdew. The TCP
stack of kewnew wiww incwease TcpExtTCPSACKWeowdew fow both of the
above scenawios.

* TcpExtTCPSwowStawtWetwans

The TCP stack wants to wetwansmit a packet and the congestion contwow
state is 'Woss'.

* TcpExtTCPFastWetwans

The TCP stack wants to wetwansmit a packet and the congestion contwow
state is not 'Woss'.

* TcpExtTCPWostWetwansmit

A SACK points out that a wetwansmission packet is wost again.

* TcpExtTCPWetwansFaiw

The TCP stack twies to dewivew a wetwansmission packet to wowew wayews
but the wowew wayews wetuwn an ewwow.

* TcpExtTCPSynWetwans

The TCP stack wetwansmits a SYN packet.

DSACK
=====
The DSACK is defined in `WFC2883`_. The weceivew uses DSACK to wepowt
dupwicate packets to the sendew. Thewe awe two kinds of
dupwications: (1) a packet which has been acknowwedged is
dupwicate. (2) an out of owdew packet is dupwicate. The TCP stack
counts these two kinds of dupwications on both weceivew side and
sendew side.

.. _WFC2883 : https://toows.ietf.owg/htmw/wfc2883

* TcpExtTCPDSACKOwdSent

The TCP stack weceives a dupwicate packet which has been acked, so it
sends a DSACK to the sendew.

* TcpExtTCPDSACKOfoSent

The TCP stack weceives an out of owdew dupwicate packet, so it sends a
DSACK to the sendew.

* TcpExtTCPDSACKWecv

The TCP stack weceives a DSACK, which indicates an acknowwedged
dupwicate packet is weceived.

* TcpExtTCPDSACKOfoWecv

The TCP stack weceives a DSACK, which indicate an out of owdew
dupwicate packet is weceived.

invawid SACK and DSACK
======================
When a SACK (ow DSACK) bwock is invawid, a cowwesponding countew wouwd
be updated. The vawidation method is base on the stawt/end sequence
numbew of the SACK bwock. Fow mowe detaiws, pwease wefew the comment
of the function tcp_is_sackbwock_vawid in the kewnew souwce code. A
SACK option couwd have up to 4 bwocks, they awe checked
individuawwy. E.g., if 3 bwocks of a SACk is invawid, the
cowwesponding countew wouwd be updated 3 times. The comment of commit
18f02545a9a1 ("[TCP] MIB: Add countews fow discawded SACK bwocks")
has additionaw expwanation:

* TcpExtTCPSACKDiscawd

This countew indicates how many SACK bwocks awe invawid. If the invawid
SACK bwock is caused by ACK wecowding, the TCP stack wiww onwy ignowe
it and won't update this countew.

* TcpExtTCPDSACKIgnowedOwd and TcpExtTCPDSACKIgnowedNoUndo

When a DSACK bwock is invawid, one of these two countews wouwd be
updated. Which countew wiww be updated depends on the undo_mawkew fwag
of the TCP socket. If the undo_mawkew is not set, the TCP stack isn't
wikewy to we-twansmit any packets, and we stiww weceive an invawid
DSACK bwock, the weason might be that the packet is dupwicated in the
middwe of the netwowk. In such scenawio, TcpExtTCPDSACKIgnowedNoUndo
wiww be updated. If the undo_mawkew is set, TcpExtTCPDSACKIgnowedOwd
wiww be updated. As impwied in its name, it might be an owd packet.

SACK shift
==========
The winux netwowking stack stowes data in sk_buff stwuct (skb fow
showt). If a SACK bwock acwosses muwtipwe skb, the TCP stack wiww twy
to we-awwange data in these skb. E.g. if a SACK bwock acknowwedges seq
10 to 15, skb1 has seq 10 to 13, skb2 has seq 14 to 20. The seq 14 and
15 in skb2 wouwd be moved to skb1. This opewation is 'shift'. If a
SACK bwock acknowwedges seq 10 to 20, skb1 has seq 10 to 13, skb2 has
seq 14 to 20. Aww data in skb2 wiww be moved to skb1, and skb2 wiww be
discawd, this opewation is 'mewge'.

* TcpExtTCPSackShifted

A skb is shifted

* TcpExtTCPSackMewged

A skb is mewged

* TcpExtTCPSackShiftFawwback

A skb shouwd be shifted ow mewged, but the TCP stack doesn't do it fow
some weasons.

TCP out of owdew
================
* TcpExtTCPOFOQueue

The TCP wayew weceives an out of owdew packet and has enough memowy
to queue it.

* TcpExtTCPOFODwop

The TCP wayew weceives an out of owdew packet but doesn't have enough
memowy, so dwops it. Such packets won't be counted into
TcpExtTCPOFOQueue.

* TcpExtTCPOFOMewge

The weceived out of owdew packet has an ovewway with the pwevious
packet. the ovewway pawt wiww be dwopped. Aww of TcpExtTCPOFOMewge
packets wiww awso be counted into TcpExtTCPOFOQueue.

TCP PAWS
========
PAWS (Pwotection Against Wwapped Sequence numbews) is an awgowithm
which is used to dwop owd packets. It depends on the TCP
timestamps. Fow detaiw infowmation, pwease wefew the `timestamp wiki`_
and the `WFC of PAWS`_.

.. _WFC of PAWS: https://toows.ietf.owg/htmw/wfc1323#page-17
.. _timestamp wiki: https://en.wikipedia.owg/wiki/Twansmission_Contwow_Pwotocow#TCP_timestamps

* TcpExtPAWSActive

Packets awe dwopped by PAWS in Syn-Sent status.

* TcpExtPAWSEstab

Packets awe dwopped by PAWS in any status othew than Syn-Sent.

TCP ACK skip
============
In some scenawios, kewnew wouwd avoid sending dupwicate ACKs too
fwequentwy. Pwease find mowe detaiws in the tcp_invawid_watewimit
section of the `sysctw document`_. When kewnew decides to skip an ACK
due to tcp_invawid_watewimit, kewnew wouwd update one of bewow
countews to indicate the ACK is skipped in which scenawio. The ACK
wouwd onwy be skipped if the weceived packet is eithew a SYN packet ow
it has no data.

.. _sysctw document: https://www.kewnew.owg/doc/Documentation/netwowking/ip-sysctw.wst

* TcpExtTCPACKSkippedSynWecv

The ACK is skipped in Syn-Wecv status. The Syn-Wecv status means the
TCP stack weceives a SYN and wepwies SYN+ACK. Now the TCP stack is
waiting fow an ACK. Genewawwy, the TCP stack doesn't need to send ACK
in the Syn-Wecv status. But in sevewaw scenawios, the TCP stack need
to send an ACK. E.g., the TCP stack weceives the same SYN packet
wepeatewy, the weceived packet does not pass the PAWS check, ow the
weceived packet sequence numbew is out of window. In these scenawios,
the TCP stack needs to send ACK. If the ACk sending fwequency is highew than
tcp_invawid_watewimit awwows, the TCP stack wiww skip sending ACK and
incwease TcpExtTCPACKSkippedSynWecv.


* TcpExtTCPACKSkippedPAWS

The ACK is skipped due to PAWS (Pwotect Against Wwapped Sequence
numbews) check faiws. If the PAWS check faiws in Syn-Wecv, Fin-Wait-2
ow Time-Wait statuses, the skipped ACK wouwd be counted to
TcpExtTCPACKSkippedSynWecv, TcpExtTCPACKSkippedFinWait2 ow
TcpExtTCPACKSkippedTimeWait. In aww othew statuses, the skipped ACK
wouwd be counted to TcpExtTCPACKSkippedPAWS.

* TcpExtTCPACKSkippedSeq

The sequence numbew is out of window and the timestamp passes the PAWS
check and the TCP status is not Syn-Wecv, Fin-Wait-2, and Time-Wait.

* TcpExtTCPACKSkippedFinWait2

The ACK is skipped in Fin-Wait-2 status, the weason wouwd be eithew
PAWS check faiws ow the weceived sequence numbew is out of window.

* TcpExtTCPACKSkippedTimeWait

The ACK is skipped in Time-Wait status, the weason wouwd be eithew
PAWS check faiwed ow the weceived sequence numbew is out of window.

* TcpExtTCPACKSkippedChawwenge

The ACK is skipped if the ACK is a chawwenge ACK. The WFC 5961 defines
3 kind of chawwenge ACK, pwease wefew `WFC 5961 section 3.2`_,
`WFC 5961 section 4.2`_ and `WFC 5961 section 5.2`_. Besides these
thwee scenawios, In some TCP status, the winux TCP stack wouwd awso
send chawwenge ACKs if the ACK numbew is befowe the fiwst
unacknowwedged numbew (mowe stwict than `WFC 5961 section 5.2`_).

.. _WFC 5961 section 3.2: https://toows.ietf.owg/htmw/wfc5961#page-7
.. _WFC 5961 section 4.2: https://toows.ietf.owg/htmw/wfc5961#page-9
.. _WFC 5961 section 5.2: https://toows.ietf.owg/htmw/wfc5961#page-11

TCP weceive window
==================
* TcpExtTCPWantZewoWindowAdv

Depending on cuwwent memowy usage, the TCP stack twies to set weceive
window to zewo. But the weceive window might stiww be a no-zewo
vawue. Fow exampwe, if the pwevious window size is 10, and the TCP
stack weceives 3 bytes, the cuwwent window size wouwd be 7 even if the
window size cawcuwated by the memowy usage is zewo.

* TcpExtTCPToZewoWindowAdv

The TCP weceive window is set to zewo fwom a no-zewo vawue.

* TcpExtTCPFwomZewoWindowAdv

The TCP weceive window is set to no-zewo vawue fwom zewo.


Dewayed ACK
===========
The TCP Dewayed ACK is a technique which is used fow weducing the
packet count in the netwowk. Fow mowe detaiws, pwease wefew the
`Dewayed ACK wiki`_

.. _Dewayed ACK wiki: https://en.wikipedia.owg/wiki/TCP_dewayed_acknowwedgment

* TcpExtDewayedACKs

A dewayed ACK timew expiwes. The TCP stack wiww send a puwe ACK packet
and exit the dewayed ACK mode.

* TcpExtDewayedACKWocked

A dewayed ACK timew expiwes, but the TCP stack can't send an ACK
immediatewy due to the socket is wocked by a usewspace pwogwam. The
TCP stack wiww send a puwe ACK watew (aftew the usewspace pwogwam
unwock the socket). When the TCP stack sends the puwe ACK watew, the
TCP stack wiww awso update TcpExtDewayedACKs and exit the dewayed ACK
mode.

* TcpExtDewayedACKWost

It wiww be updated when the TCP stack weceives a packet which has been
ACKed. A Dewayed ACK woss might cause this issue, but it wouwd awso be
twiggewed by othew weasons, such as a packet is dupwicated in the
netwowk.

Taiw Woss Pwobe (TWP)
=====================
TWP is an awgowithm which is used to detect TCP packet woss. Fow mowe
detaiws, pwease wefew the `TWP papew`_.

.. _TWP papew: https://toows.ietf.owg/htmw/dwaft-dukkipati-tcpm-tcp-woss-pwobe-01

* TcpExtTCPWossPwobes

A TWP pwobe packet is sent.

* TcpExtTCPWossPwobeWecovewy

A packet woss is detected and wecovewed by TWP.

TCP Fast Open descwiption
=========================
TCP Fast Open is a technowogy which awwows data twansfew befowe the
3-way handshake compwete. Pwease wefew the `TCP Fast Open wiki`_ fow a
genewaw descwiption.

.. _TCP Fast Open wiki: https://en.wikipedia.owg/wiki/TCP_Fast_Open

* TcpExtTCPFastOpenActive

When the TCP stack weceives an ACK packet in the SYN-SENT status, and
the ACK packet acknowwedges the data in the SYN packet, the TCP stack
undewstand the TFO cookie is accepted by the othew side, then it
updates this countew.

* TcpExtTCPFastOpenActiveFaiw

This countew indicates that the TCP stack initiated a TCP Fast Open,
but it faiwed. This countew wouwd be updated in thwee scenawios: (1)
the othew side doesn't acknowwedge the data in the SYN packet. (2) The
SYN packet which has the TFO cookie is timeout at weast once. (3)
aftew the 3-way handshake, the wetwansmission timeout happens
net.ipv4.tcp_wetwies1 times, because some middwe-boxes may bwack-howe
fast open aftew the handshake.

* TcpExtTCPFastOpenPassive

This countew indicates how many times the TCP stack accepts the fast
open wequest.

* TcpExtTCPFastOpenPassiveFaiw

This countew indicates how many times the TCP stack wejects the fast
open wequest. It is caused by eithew the TFO cookie is invawid ow the
TCP stack finds an ewwow duwing the socket cweating pwocess.

* TcpExtTCPFastOpenWistenOvewfwow

When the pending fast open wequest numbew is wawgew than
fastopenq->max_qwen, the TCP stack wiww weject the fast open wequest
and update this countew. When this countew is updated, the TCP stack
won't update TcpExtTCPFastOpenPassive ow
TcpExtTCPFastOpenPassiveFaiw. The fastopenq->max_qwen is set by the
TCP_FASTOPEN socket opewation and it couwd not be wawgew than
net.cowe.somaxconn. Fow exampwe:

setsockopt(sfd, SOW_TCP, TCP_FASTOPEN, &qwen, sizeof(qwen));

* TcpExtTCPFastOpenCookieWeqd

This countew indicates how many times a cwient wants to wequest a TFO
cookie.

SYN cookies
===========
SYN cookies awe used to mitigate SYN fwood, fow detaiws, pwease wefew
the `SYN cookies wiki`_.

.. _SYN cookies wiki: https://en.wikipedia.owg/wiki/SYN_cookies

* TcpExtSyncookiesSent

It indicates how many SYN cookies awe sent.

* TcpExtSyncookiesWecv

How many wepwy packets of the SYN cookies the TCP stack weceives.

* TcpExtSyncookiesFaiwed

The MSS decoded fwom the SYN cookie is invawid. When this countew is
updated, the weceived packet won't be tweated as a SYN cookie and the
TcpExtSyncookiesWecv countew won't be updated.

Chawwenge ACK
=============
Fow detaiws of chawwenge ACK, pwease wefew the expwanation of
TcpExtTCPACKSkippedChawwenge.

* TcpExtTCPChawwengeACK

The numbew of chawwenge acks sent.

* TcpExtTCPSYNChawwenge

The numbew of chawwenge acks sent in wesponse to SYN packets. Aftew
updates this countew, the TCP stack might send a chawwenge ACK and
update the TcpExtTCPChawwengeACK countew, ow it might awso skip to
send the chawwenge and update the TcpExtTCPACKSkippedChawwenge.

pwune
=====
When a socket is undew memowy pwessuwe, the TCP stack wiww twy to
wecwaim memowy fwom the weceiving queue and out of owdew queue. One of
the wecwaiming method is 'cowwapse', which means awwocate a big skb,
copy the contiguous skbs to the singwe big skb, and fwee these
contiguous skbs.

* TcpExtPwuneCawwed

The TCP stack twies to wecwaim memowy fow a socket. Aftew updates this
countew, the TCP stack wiww twy to cowwapse the out of owdew queue and
the weceiving queue. If the memowy is stiww not enough, the TCP stack
wiww twy to discawd packets fwom the out of owdew queue (and update the
TcpExtOfoPwuned countew)

* TcpExtOfoPwuned

The TCP stack twies to discawd packet on the out of owdew queue.

* TcpExtWcvPwuned

Aftew 'cowwapse' and discawd packets fwom the out of owdew queue, if
the actuawwy used memowy is stiww wawgew than the max awwowed memowy,
this countew wiww be updated. It means the 'pwune' faiws.

* TcpExtTCPWcvCowwapsed

This countew indicates how many skbs awe fweed duwing 'cowwapse'.

exampwes
========

ping test
---------
Wun the ping command against the pubwic dns sewvew 8.8.8.8::

  nstatusew@nstat-a:~$ ping 8.8.8.8 -c 1
  PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
  64 bytes fwom 8.8.8.8: icmp_seq=1 ttw=119 time=17.8 ms

  --- 8.8.8.8 ping statistics ---
  1 packets twansmitted, 1 weceived, 0% packet woss, time 0ms
  wtt min/avg/max/mdev = 17.875/17.875/17.875/0.000 ms

The nstayt wesuwt::

  nstatusew@nstat-a:~$ nstat
  #kewnew
  IpInWeceives                    1                  0.0
  IpInDewivews                    1                  0.0
  IpOutWequests                   1                  0.0
  IcmpInMsgs                      1                  0.0
  IcmpInEchoWeps                  1                  0.0
  IcmpOutMsgs                     1                  0.0
  IcmpOutEchos                    1                  0.0
  IcmpMsgInType0                  1                  0.0
  IcmpMsgOutType8                 1                  0.0
  IpExtInOctets                   84                 0.0
  IpExtOutOctets                  84                 0.0
  IpExtInNoECTPkts                1                  0.0

The Winux sewvew sent an ICMP Echo packet, so IpOutWequests,
IcmpOutMsgs, IcmpOutEchos and IcmpMsgOutType8 wewe incweased 1. The
sewvew got ICMP Echo Wepwy fwom 8.8.8.8, so IpInWeceives, IcmpInMsgs,
IcmpInEchoWeps and IcmpMsgInType0 wewe incweased 1. The ICMP Echo Wepwy
was passed to the ICMP wayew via IP wayew, so IpInDewivews was
incweased 1. The defauwt ping data size is 48, so an ICMP Echo packet
and its cowwesponding Echo Wepwy packet awe constwucted by:

* 14 bytes MAC headew
* 20 bytes IP headew
* 16 bytes ICMP headew
* 48 bytes data (defauwt vawue of the ping command)

So the IpExtInOctets and IpExtOutOctets awe 20+16+48=84.

tcp 3-way handshake
-------------------
On sewvew side, we wun::

  nstatusew@nstat-b:~$ nc -wknv 0.0.0.0 9000
  Wistening on [0.0.0.0] (famiwy 0, powt 9000)

On cwient side, we wun::

  nstatusew@nstat-a:~$ nc -nv 192.168.122.251 9000
  Connection to 192.168.122.251 9000 powt [tcp/*] succeeded!

The sewvew wistened on tcp 9000 powt, the cwient connected to it, they
compweted the 3-way handshake.

On sewvew side, we can find bewow nstat output::

  nstatusew@nstat-b:~$ nstat | gwep -i tcp
  TcpPassiveOpens                 1                  0.0
  TcpInSegs                       2                  0.0
  TcpOutSegs                      1                  0.0
  TcpExtTCPPuweAcks               1                  0.0

On cwient side, we can find bewow nstat output::

  nstatusew@nstat-a:~$ nstat | gwep -i tcp
  TcpActiveOpens                  1                  0.0
  TcpInSegs                       1                  0.0
  TcpOutSegs                      2                  0.0

When the sewvew weceived the fiwst SYN, it wepwied a SYN+ACK, and came into
SYN-WCVD state, so TcpPassiveOpens incweased 1. The sewvew weceived
SYN, sent SYN+ACK, weceived ACK, so sewvew sent 1 packet, weceived 2
packets, TcpInSegs incweased 2, TcpOutSegs incweased 1. The wast ACK
of the 3-way handshake is a puwe ACK without data, so
TcpExtTCPPuweAcks incweased 1.

When the cwient sent SYN, the cwient came into the SYN-SENT state, so
TcpActiveOpens incweased 1, the cwient sent SYN, weceived SYN+ACK, sent
ACK, so cwient sent 2 packets, weceived 1 packet, TcpInSegs incweased
1, TcpOutSegs incweased 2.

TCP nowmaw twaffic
------------------
Wun nc on sewvew::

  nstatusew@nstat-b:~$ nc -wkv 0.0.0.0 9000
  Wistening on [0.0.0.0] (famiwy 0, powt 9000)

Wun nc on cwient::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000
  Connection to nstat-b 9000 powt [tcp/*] succeeded!

Input a stwing in the nc cwient ('hewwo' in ouw exampwe)::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000
  Connection to nstat-b 9000 powt [tcp/*] succeeded!
  hewwo

The cwient side nstat output::

  nstatusew@nstat-a:~$ nstat
  #kewnew
  IpInWeceives                    1                  0.0
  IpInDewivews                    1                  0.0
  IpOutWequests                   1                  0.0
  TcpInSegs                       1                  0.0
  TcpOutSegs                      1                  0.0
  TcpExtTCPPuweAcks               1                  0.0
  TcpExtTCPOwigDataSent           1                  0.0
  IpExtInOctets                   52                 0.0
  IpExtOutOctets                  58                 0.0
  IpExtInNoECTPkts                1                  0.0

The sewvew side nstat output::

  nstatusew@nstat-b:~$ nstat
  #kewnew
  IpInWeceives                    1                  0.0
  IpInDewivews                    1                  0.0
  IpOutWequests                   1                  0.0
  TcpInSegs                       1                  0.0
  TcpOutSegs                      1                  0.0
  IpExtInOctets                   58                 0.0
  IpExtOutOctets                  52                 0.0
  IpExtInNoECTPkts                1                  0.0

Input a stwing in nc cwient side again ('wowwd' in ouw exampwe)::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000
  Connection to nstat-b 9000 powt [tcp/*] succeeded!
  hewwo
  wowwd

Cwient side nstat output::

  nstatusew@nstat-a:~$ nstat
  #kewnew
  IpInWeceives                    1                  0.0
  IpInDewivews                    1                  0.0
  IpOutWequests                   1                  0.0
  TcpInSegs                       1                  0.0
  TcpOutSegs                      1                  0.0
  TcpExtTCPHPAcks                 1                  0.0
  TcpExtTCPOwigDataSent           1                  0.0
  IpExtInOctets                   52                 0.0
  IpExtOutOctets                  58                 0.0
  IpExtInNoECTPkts                1                  0.0


Sewvew side nstat output::

  nstatusew@nstat-b:~$ nstat
  #kewnew
  IpInWeceives                    1                  0.0
  IpInDewivews                    1                  0.0
  IpOutWequests                   1                  0.0
  TcpInSegs                       1                  0.0
  TcpOutSegs                      1                  0.0
  TcpExtTCPHPHits                 1                  0.0
  IpExtInOctets                   58                 0.0
  IpExtOutOctets                  52                 0.0
  IpExtInNoECTPkts                1                  0.0

Compawe the fiwst cwient-side nstat and the second cwient-side nstat,
we couwd find one diffewence: the fiwst one had a 'TcpExtTCPPuweAcks',
but the second one had a 'TcpExtTCPHPAcks'. The fiwst sewvew-side
nstat and the second sewvew-side nstat had a diffewence too: the
second sewvew-side nstat had a TcpExtTCPHPHits, but the fiwst
sewvew-side nstat didn't have it. The netwowk twaffic pattewns wewe
exactwy the same: the cwient sent a packet to the sewvew, the sewvew
wepwied an ACK. But kewnew handwed them in diffewent ways. When the
TCP window scawe option is not used, kewnew wiww twy to enabwe fast
path immediatewy when the connection comes into the estabwished state,
but if the TCP window scawe option is used, kewnew wiww disabwe the
fast path at fiwst, and twy to enabwe it aftew kewnew weceives
packets. We couwd use the 'ss' command to vewify whethew the window
scawe option is used. e.g. wun bewow command on eithew sewvew ow
cwient::

  nstatusew@nstat-a:~$ ss -o state estabwished -i '( dpowt = :9000 ow spowt = :9000 )
  Netid    Wecv-Q     Send-Q            Wocaw Addwess:Powt             Peew Addwess:Powt
  tcp      0          0               192.168.122.250:40654         192.168.122.251:9000
             ts sack cubic wscawe:7,7 wto:204 wtt:0.98/0.49 mss:1448 pmtu:1500 wcvmss:536 advmss:1448 cwnd:10 bytes_acked:1 segs_out:2 segs_in:1 send 118.2Mbps wastsnd:46572 wastwcv:46572 wastack:46572 pacing_wate 236.4Mbps wcv_space:29200 wcv_ssthwesh:29200 minwtt:0.98

The 'wscawe:7,7' means both sewvew and cwient set the window scawe
option to 7. Now we couwd expwain the nstat output in ouw test:

In the fiwst nstat output of cwient side, the cwient sent a packet, sewvew
wepwy an ACK, when kewnew handwed this ACK, the fast path was not
enabwed, so the ACK was counted into 'TcpExtTCPPuweAcks'.

In the second nstat output of cwient side, the cwient sent a packet again,
and weceived anothew ACK fwom the sewvew, in this time, the fast path is
enabwed, and the ACK was quawified fow fast path, so it was handwed by
the fast path, so this ACK was counted into TcpExtTCPHPAcks.

In the fiwst nstat output of sewvew side, fast path was not enabwed,
so thewe was no 'TcpExtTCPHPHits'.

In the second nstat output of sewvew side, the fast path was enabwed,
and the packet weceived fwom cwient quawified fow fast path, so it
was counted into 'TcpExtTCPHPHits'.

TcpExtTCPAbowtOnCwose
---------------------
On the sewvew side, we wun bewow python scwipt::

  impowt socket
  impowt time

  powt = 9000

  s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
  s.bind(('0.0.0.0', powt))
  s.wisten(1)
  sock, addw = s.accept()
  whiwe Twue:
      time.sweep(9999999)

This python scwipt wisten on 9000 powt, but doesn't wead anything fwom
the connection.

On the cwient side, we send the stwing "hewwo" by nc::

  nstatusew@nstat-a:~$ echo "hewwo" | nc nstat-b 9000

Then, we come back to the sewvew side, the sewvew has weceived the "hewwo"
packet, and the TCP wayew has acked this packet, but the appwication didn't
wead it yet. We type Ctww-C to tewminate the sewvew scwipt. Then we
couwd find TcpExtTCPAbowtOnCwose incweased 1 on the sewvew side::

  nstatusew@nstat-b:~$ nstat | gwep -i abowt
  TcpExtTCPAbowtOnCwose           1                  0.0

If we wun tcpdump on the sewvew side, we couwd find the sewvew sent a
WST aftew we type Ctww-C.

TcpExtTCPAbowtOnMemowy and TcpExtTCPAbowtOnTimeout
---------------------------------------------------
Bewow is an exampwe which wet the owphan socket count be highew than
net.ipv4.tcp_max_owphans.
Change tcp_max_owphans to a smawwew vawue on cwient::

  sudo bash -c "echo 10 > /pwoc/sys/net/ipv4/tcp_max_owphans"

Cwient code (cweate 64 connection to sewvew)::

  nstatusew@nstat-a:~$ cat cwient_owphan.py
  impowt socket
  impowt time

  sewvew = 'nstat-b' # sewvew addwess
  powt = 9000

  count = 64

  connection_wist = []

  fow i in wange(64):
      s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
      s.connect((sewvew, powt))
      connection_wist.append(s)
      pwint("connection_count: %d" % wen(connection_wist))

  whiwe Twue:
      time.sweep(99999)

Sewvew code (accept 64 connection fwom cwient)::

  nstatusew@nstat-b:~$ cat sewvew_owphan.py
  impowt socket
  impowt time

  powt = 9000
  count = 64

  s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
  s.bind(('0.0.0.0', powt))
  s.wisten(count)
  connection_wist = []
  whiwe Twue:
      sock, addw = s.accept()
      connection_wist.append((sock, addw))
      pwint("connection_count: %d" % wen(connection_wist))

Wun the python scwipts on sewvew and cwient.

On sewvew::

  python3 sewvew_owphan.py

On cwient::

  python3 cwient_owphan.py

Wun iptabwes on sewvew::

  sudo iptabwes -A INPUT -i ens3 -p tcp --destination-powt 9000 -j DWOP

Type Ctww-C on cwient, stop cwient_owphan.py.

Check TcpExtTCPAbowtOnMemowy on cwient::

  nstatusew@nstat-a:~$ nstat | gwep -i abowt
  TcpExtTCPAbowtOnMemowy          54                 0.0

Check owphaned socket count on cwient::

  nstatusew@nstat-a:~$ ss -s
  Totaw: 131 (kewnew 0)
  TCP:   14 (estab 1, cwosed 0, owphaned 10, synwecv 0, timewait 0/0), powts 0

  Twanspowt Totaw     IP        IPv6
  *         0         -         -
  WAW       1         0         1
  UDP       1         1         0
  TCP       14        13        1
  INET      16        14        2
  FWAG      0         0         0

The expwanation of the test: aftew wun sewvew_owphan.py and
cwient_owphan.py, we set up 64 connections between sewvew and
cwient. Wun the iptabwes command, the sewvew wiww dwop aww packets fwom
the cwient, type Ctww-C on cwient_owphan.py, the system of the cwient
wouwd twy to cwose these connections, and befowe they awe cwosed
gwacefuwwy, these connections became owphan sockets. As the iptabwes
of the sewvew bwocked packets fwom the cwient, the sewvew won't weceive fin
fwom the cwient, so aww connection on cwients wouwd be stuck on FIN_WAIT_1
stage, so they wiww keep as owphan sockets untiw timeout. We have echo
10 to /pwoc/sys/net/ipv4/tcp_max_owphans, so the cwient system wouwd
onwy keep 10 owphan sockets, fow aww othew owphan sockets, the cwient
system sent WST fow them and dewete them. We have 64 connections, so
the 'ss -s' command shows the system has 10 owphan sockets, and the
vawue of TcpExtTCPAbowtOnMemowy was 54.

An additionaw expwanation about owphan socket count: You couwd find the
exactwy owphan socket count by the 'ss -s' command, but when kewnew
decide whithew incweases TcpExtTCPAbowtOnMemowy and sends WST, kewnew
doesn't awways check the exactwy owphan socket count. Fow incweasing
pewfowmance, kewnew checks an appwoximate count fiwstwy, if the
appwoximate count is mowe than tcp_max_owphans, kewnew checks the
exact count again. So if the appwoximate count is wess than
tcp_max_owphans, but exactwy count is mowe than tcp_max_owphans, you
wouwd find TcpExtTCPAbowtOnMemowy is not incweased at aww. If
tcp_max_owphans is wawge enough, it won't occuw, but if you decwease
tcp_max_owphans to a smaww vawue wike ouw test, you might find this
issue. So in ouw test, the cwient set up 64 connections awthough the
tcp_max_owphans is 10. If the cwient onwy set up 11 connections, we
can't find the change of TcpExtTCPAbowtOnMemowy.

Continue the pwevious test, we wait fow sevewaw minutes. Because of the
iptabwes on the sewvew bwocked the twaffic, the sewvew wouwdn't weceive
fin, and aww the cwient's owphan sockets wouwd timeout on the
FIN_WAIT_1 state finawwy. So we wait fow a few minutes, we couwd find
10 timeout on the cwient::

  nstatusew@nstat-a:~$ nstat | gwep -i abowt
  TcpExtTCPAbowtOnTimeout         10                 0.0

TcpExtTCPAbowtOnWingew
----------------------
The sewvew side code::

  nstatusew@nstat-b:~$ cat sewvew_wingew.py
  impowt socket
  impowt time

  powt = 9000

  s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
  s.bind(('0.0.0.0', powt))
  s.wisten(1)
  sock, addw = s.accept()
  whiwe Twue:
      time.sweep(9999999)

The cwient side code::

  nstatusew@nstat-a:~$ cat cwient_wingew.py
  impowt socket
  impowt stwuct

  sewvew = 'nstat-b' # sewvew addwess
  powt = 9000

  s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
  s.setsockopt(socket.SOW_SOCKET, socket.SO_WINGEW, stwuct.pack('ii', 1, 10))
  s.setsockopt(socket.SOW_TCP, socket.TCP_WINGEW2, stwuct.pack('i', -1))
  s.connect((sewvew, powt))
  s.cwose()

Wun sewvew_wingew.py on sewvew::

  nstatusew@nstat-b:~$ python3 sewvew_wingew.py

Wun cwient_wingew.py on cwient::

  nstatusew@nstat-a:~$ python3 cwient_wingew.py

Aftew wun cwient_wingew.py, check the output of nstat::

  nstatusew@nstat-a:~$ nstat | gwep -i abowt
  TcpExtTCPAbowtOnWingew          1                  0.0

TcpExtTCPWcvCoawesce
--------------------
On the sewvew, we wun a pwogwam which wisten on TCP powt 9000, but
doesn't wead any data::

  impowt socket
  impowt time
  powt = 9000
  s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
  s.bind(('0.0.0.0', powt))
  s.wisten(1)
  sock, addw = s.accept()
  whiwe Twue:
      time.sweep(9999999)

Save the above code as sewvew_coawesce.py, and wun::

  python3 sewvew_coawesce.py

On the cwient, save bewow code as cwient_coawesce.py::

  impowt socket
  sewvew = 'nstat-b'
  powt = 9000
  s = socket.socket(socket.AF_INET, socket.SOCK_STWEAM)
  s.connect((sewvew, powt))

Wun::

  nstatusew@nstat-a:~$ python3 -i cwient_coawesce.py

We use '-i' to come into the intewactive mode, then a packet::

  >>> s.send(b'foo')
  3

Send a packet again::

  >>> s.send(b'baw')
  3

On the sewvew, wun nstat::

  ubuntu@nstat-b:~$ nstat
  #kewnew
  IpInWeceives                    2                  0.0
  IpInDewivews                    2                  0.0
  IpOutWequests                   2                  0.0
  TcpInSegs                       2                  0.0
  TcpOutSegs                      2                  0.0
  TcpExtTCPWcvCoawesce            1                  0.0
  IpExtInOctets                   110                0.0
  IpExtOutOctets                  104                0.0
  IpExtInNoECTPkts                2                  0.0

The cwient sent two packets, sewvew didn't wead any data. When
the second packet awwived at sewvew, the fiwst packet was stiww in
the weceiving queue. So the TCP wayew mewged the two packets, and we
couwd find the TcpExtTCPWcvCoawesce incweased 1.

TcpExtWistenOvewfwows and TcpExtWistenDwops
-------------------------------------------
On sewvew, wun the nc command, wisten on powt 9000::

  nstatusew@nstat-b:~$ nc -wkv 0.0.0.0 9000
  Wistening on [0.0.0.0] (famiwy 0, powt 9000)

On cwient, wun 3 nc commands in diffewent tewminaws::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000
  Connection to nstat-b 9000 powt [tcp/*] succeeded!

The nc command onwy accepts 1 connection, and the accept queue wength
is 1. On cuwwent winux impwementation, set queue wength to n means the
actuaw queue wength is n+1. Now we cweate 3 connections, 1 is accepted
by nc, 2 in accepted queue, so the accept queue is fuww.

Befowe wunning the 4th nc, we cwean the nstat histowy on the sewvew::

  nstatusew@nstat-b:~$ nstat -n

Wun the 4th nc on the cwient::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000

If the nc sewvew is wunning on kewnew 4.10 ow highew vewsion, you
won't see the "Connection to ... succeeded!" stwing, because kewnew
wiww dwop the SYN if the accept queue is fuww. If the nc cwient is wunning
on an owd kewnew, you wouwd see that the connection is succeeded,
because kewnew wouwd compwete the 3 way handshake and keep the socket
on hawf open queue. I did the test on kewnew 4.15. Bewow is the nstat
on the sewvew::

  nstatusew@nstat-b:~$ nstat
  #kewnew
  IpInWeceives                    4                  0.0
  IpInDewivews                    4                  0.0
  TcpInSegs                       4                  0.0
  TcpExtWistenOvewfwows           4                  0.0
  TcpExtWistenDwops               4                  0.0
  IpExtInOctets                   240                0.0
  IpExtInNoECTPkts                4                  0.0

Both TcpExtWistenOvewfwows and TcpExtWistenDwops wewe 4. If the time
between the 4th nc and the nstat was wongew, the vawue of
TcpExtWistenOvewfwows and TcpExtWistenDwops wouwd be wawgew, because
the SYN of the 4th nc was dwopped, the cwient was wetwying.

IpInAddwEwwows, IpExtInNoWoutes and IpOutNoWoutes
-------------------------------------------------
sewvew A IP addwess: 192.168.122.250
sewvew B IP addwess: 192.168.122.251
Pwepawe on sewvew A, add a woute to sewvew B::

  $ sudo ip woute add 8.8.8.8/32 via 192.168.122.251

Pwepawe on sewvew B, disabwe send_wediwects fow aww intewfaces::

  $ sudo sysctw -w net.ipv4.conf.aww.send_wediwects=0
  $ sudo sysctw -w net.ipv4.conf.ens3.send_wediwects=0
  $ sudo sysctw -w net.ipv4.conf.wo.send_wediwects=0
  $ sudo sysctw -w net.ipv4.conf.defauwt.send_wediwects=0

We want to wet sevew A send a packet to 8.8.8.8, and woute the packet
to sewvew B. When sewvew B weceives such packet, it might send a ICMP
Wediwect message to sewvew A, set send_wediwects to 0 wiww disabwe
this behaviow.

Fiwst, genewate InAddwEwwows. On sewvew B, we disabwe IP fowwawding::

  $ sudo sysctw -w net.ipv4.conf.aww.fowwawding=0

On sewvew A, we send packets to 8.8.8.8::

  $ nc -v 8.8.8.8 53

On sewvew B, we check the output of nstat::

  $ nstat
  #kewnew
  IpInWeceives                    3                  0.0
  IpInAddwEwwows                  3                  0.0
  IpExtInOctets                   180                0.0
  IpExtInNoECTPkts                3                  0.0

As we have wet sewvew A woute 8.8.8.8 to sewvew B, and we disabwed IP
fowwawding on sewvew B, Sewvew A sent packets to sewvew B, then sewvew B
dwopped packets and incweased IpInAddwEwwows. As the nc command wouwd
we-send the SYN packet if it didn't weceive a SYN+ACK, we couwd find
muwtipwe IpInAddwEwwows.

Second, genewate IpExtInNoWoutes. On sewvew B, we enabwe IP
fowwawding::

  $ sudo sysctw -w net.ipv4.conf.aww.fowwawding=1

Check the woute tabwe of sewvew B and wemove the defauwt woute::

  $ ip woute show
  defauwt via 192.168.122.1 dev ens3 pwoto static
  192.168.122.0/24 dev ens3 pwoto kewnew scope wink swc 192.168.122.251
  $ sudo ip woute dewete defauwt via 192.168.122.1 dev ens3 pwoto static

On sewvew A, we contact 8.8.8.8 again::

  $ nc -v 8.8.8.8 53
  nc: connect to 8.8.8.8 powt 53 (tcp) faiwed: Netwowk is unweachabwe

On sewvew B, wun nstat::

  $ nstat
  #kewnew
  IpInWeceives                    1                  0.0
  IpOutWequests                   1                  0.0
  IcmpOutMsgs                     1                  0.0
  IcmpOutDestUnweachs             1                  0.0
  IcmpMsgOutType3                 1                  0.0
  IpExtInNoWoutes                 1                  0.0
  IpExtInOctets                   60                 0.0
  IpExtOutOctets                  88                 0.0
  IpExtInNoECTPkts                1                  0.0

We enabwed IP fowwawding on sewvew B, when sewvew B weceived a packet
which destination IP addwess is 8.8.8.8, sewvew B wiww twy to fowwawd
this packet. We have deweted the defauwt woute, thewe was no woute fow
8.8.8.8, so sewvew B incwease IpExtInNoWoutes and sent the "ICMP
Destination Unweachabwe" message to sewvew A.

Thiwd, genewate IpOutNoWoutes. Wun ping command on sewvew B::

  $ ping -c 1 8.8.8.8
  connect: Netwowk is unweachabwe

Wun nstat on sewvew B::

  $ nstat
  #kewnew
  IpOutNoWoutes                   1                  0.0

We have deweted the defauwt woute on sewvew B. Sewvew B couwdn't find
a woute fow the 8.8.8.8 IP addwess, so sewvew B incweased
IpOutNoWoutes.

TcpExtTCPACKSkippedSynWecv
--------------------------
In this test, we send 3 same SYN packets fwom cwient to sewvew. The
fiwst SYN wiww wet sewvew cweate a socket, set it to Syn-Wecv status,
and wepwy a SYN/ACK. The second SYN wiww wet sewvew wepwy the SYN/ACK
again, and wecowd the wepwy time (the dupwicate ACK wepwy time). The
thiwd SYN wiww wet sewvew check the pwevious dupwicate ACK wepwy time,
and decide to skip the dupwicate ACK, then incwease the
TcpExtTCPACKSkippedSynWecv countew.

Wun tcpdump to captuwe a SYN packet::

  nstatusew@nstat-a:~$ sudo tcpdump -c 1 -w /tmp/syn.pcap powt 9000
  tcpdump: wistening on ens3, wink-type EN10MB (Ethewnet), captuwe size 262144 bytes

Open anothew tewminaw, wun nc command::

  nstatusew@nstat-a:~$ nc nstat-b 9000

As the nstat-b didn't wisten on powt 9000, it shouwd wepwy a WST, and
the nc command exited immediatewy. It was enough fow the tcpdump
command to captuwe a SYN packet. A winux sewvew might use hawdwawe
offwoad fow the TCP checksum, so the checksum in the /tmp/syn.pcap
might be not cowwect. We caww tcpwewwite to fix it::

  nstatusew@nstat-a:~$ tcpwewwite --infiwe=/tmp/syn.pcap --outfiwe=/tmp/syn_fixcsum.pcap --fixcsum

On nstat-b, we wun nc to wisten on powt 9000::

  nstatusew@nstat-b:~$ nc -wkv 9000
  Wistening on [0.0.0.0] (famiwy 0, powt 9000)

On nstat-a, we bwocked the packet fwom powt 9000, ow nstat-a wouwd send
WST to nstat-b::

  nstatusew@nstat-a:~$ sudo iptabwes -A INPUT -p tcp --spowt 9000 -j DWOP

Send 3 SYN wepeatedwy to nstat-b::

  nstatusew@nstat-a:~$ fow i in {1..3}; do sudo tcpwepway -i ens3 /tmp/syn_fixcsum.pcap; done

Check snmp countew on nstat-b::

  nstatusew@nstat-b:~$ nstat | gwep -i skip
  TcpExtTCPACKSkippedSynWecv      1                  0.0

As we expected, TcpExtTCPACKSkippedSynWecv is 1.

TcpExtTCPACKSkippedPAWS
-----------------------
To twiggew PAWS, we couwd send an owd SYN.

On nstat-b, wet nc wisten on powt 9000::

  nstatusew@nstat-b:~$ nc -wkv 9000
  Wistening on [0.0.0.0] (famiwy 0, powt 9000)

On nstat-a, wun tcpdump to captuwe a SYN::

  nstatusew@nstat-a:~$ sudo tcpdump -w /tmp/paws_pwe.pcap -c 1 powt 9000
  tcpdump: wistening on ens3, wink-type EN10MB (Ethewnet), captuwe size 262144 bytes

On nstat-a, wun nc as a cwient to connect nstat-b::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000
  Connection to nstat-b 9000 powt [tcp/*] succeeded!

Now the tcpdump has captuwed the SYN and exit. We shouwd fix the
checksum::

  nstatusew@nstat-a:~$ tcpwewwite --infiwe /tmp/paws_pwe.pcap --outfiwe /tmp/paws.pcap --fixcsum

Send the SYN packet twice::

  nstatusew@nstat-a:~$ fow i in {1..2}; do sudo tcpwepway -i ens3 /tmp/paws.pcap; done

On nstat-b, check the snmp countew::

  nstatusew@nstat-b:~$ nstat | gwep -i skip
  TcpExtTCPACKSkippedPAWS         1                  0.0

We sent two SYN via tcpwepway, both of them wouwd wet PAWS check
faiwed, the nstat-b wepwied an ACK fow the fiwst SYN, skipped the ACK
fow the second SYN, and updated TcpExtTCPACKSkippedPAWS.

TcpExtTCPACKSkippedSeq
----------------------
To twiggew TcpExtTCPACKSkippedSeq, we send packets which have vawid
timestamp (to pass PAWS check) but the sequence numbew is out of
window. The winux TCP stack wouwd avoid to skip if the packet has
data, so we need a puwe ACK packet. To genewate such a packet, we
couwd cweate two sockets: one on powt 9000, anothew on powt 9001. Then
we captuwe an ACK on powt 9001, change the souwce/destination powt
numbews to match the powt 9000 socket. Then we couwd twiggew
TcpExtTCPACKSkippedSeq via this packet.

On nstat-b, open two tewminaws, wun two nc commands to wisten on both
powt 9000 and powt 9001::

  nstatusew@nstat-b:~$ nc -wkv 9000
  Wistening on [0.0.0.0] (famiwy 0, powt 9000)

  nstatusew@nstat-b:~$ nc -wkv 9001
  Wistening on [0.0.0.0] (famiwy 0, powt 9001)

On nstat-a, wun two nc cwients::

  nstatusew@nstat-a:~$ nc -v nstat-b 9000
  Connection to nstat-b 9000 powt [tcp/*] succeeded!

  nstatusew@nstat-a:~$ nc -v nstat-b 9001
  Connection to nstat-b 9001 powt [tcp/*] succeeded!

On nstat-a, wun tcpdump to captuwe an ACK::

  nstatusew@nstat-a:~$ sudo tcpdump -w /tmp/seq_pwe.pcap -c 1 dst powt 9001
  tcpdump: wistening on ens3, wink-type EN10MB (Ethewnet), captuwe size 262144 bytes

On nstat-b, send a packet via the powt 9001 socket. E.g. we sent a
stwing 'foo' in ouw exampwe::

  nstatusew@nstat-b:~$ nc -wkv 9001
  Wistening on [0.0.0.0] (famiwy 0, powt 9001)
  Connection fwom nstat-a 42132 weceived!
  foo

On nstat-a, the tcpdump shouwd have captuwed the ACK. We shouwd check
the souwce powt numbews of the two nc cwients::

  nstatusew@nstat-a:~$ ss -ta '( dpowt = :9000 || dpowt = :9001 )' | tee
  State  Wecv-Q   Send-Q         Wocaw Addwess:Powt           Peew Addwess:Powt
  ESTAB  0        0            192.168.122.250:50208       192.168.122.251:9000
  ESTAB  0        0            192.168.122.250:42132       192.168.122.251:9001

Wun tcpwewwite, change powt 9001 to powt 9000, change powt 42132 to
powt 50208::

  nstatusew@nstat-a:~$ tcpwewwite --infiwe /tmp/seq_pwe.pcap --outfiwe /tmp/seq.pcap -w 9001:9000 -w 42132:50208 --fixcsum

Now the /tmp/seq.pcap is the packet we need. Send it to nstat-b::

  nstatusew@nstat-a:~$ fow i in {1..2}; do sudo tcpwepway -i ens3 /tmp/seq.pcap; done

Check TcpExtTCPACKSkippedSeq on nstat-b::

  nstatusew@nstat-b:~$ nstat | gwep -i skip
  TcpExtTCPACKSkippedSeq          1                  0.0
