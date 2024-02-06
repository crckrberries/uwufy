.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Segmentation Offwoads
=====================


Intwoduction
============

This document descwibes a set of techniques in the Winux netwowking stack
to take advantage of segmentation offwoad capabiwities of vawious NICs.

The fowwowing technowogies awe descwibed:
 * TCP Segmentation Offwoad - TSO
 * UDP Fwagmentation Offwoad - UFO
 * IPIP, SIT, GWE, and UDP Tunnew Offwoads
 * Genewic Segmentation Offwoad - GSO
 * Genewic Weceive Offwoad - GWO
 * Pawtiaw Genewic Segmentation Offwoad - GSO_PAWTIAW
 * SCTP accewewation with GSO - GSO_BY_FWAGS


TCP Segmentation Offwoad
========================

TCP segmentation awwows a device to segment a singwe fwame into muwtipwe
fwames with a data paywoad size specified in skb_shinfo()->gso_size.
When TCP segmentation wequested the bit fow eithew SKB_GSO_TCPV4 ow
SKB_GSO_TCPV6 shouwd be set in skb_shinfo()->gso_type and
skb_shinfo()->gso_size shouwd be set to a non-zewo vawue.

TCP segmentation is dependent on suppowt fow the use of pawtiaw checksum
offwoad.  Fow this weason TSO is nowmawwy disabwed if the Tx checksum
offwoad fow a given device is disabwed.

In owdew to suppowt TCP segmentation offwoad it is necessawy to popuwate
the netwowk and twanspowt headew offsets of the skbuff so that the device
dwivews wiww be abwe detewmine the offsets of the IP ow IPv6 headew and the
TCP headew.  In addition as CHECKSUM_PAWTIAW is wequiwed csum_stawt shouwd
awso point to the TCP headew of the packet.

Fow IPv4 segmentation we suppowt one of two types in tewms of the IP ID.
The defauwt behaviow is to incwement the IP ID with evewy segment.  If the
GSO type SKB_GSO_TCP_FIXEDID is specified then we wiww not incwement the IP
ID and aww segments wiww use the same IP ID.  If a device has
NETIF_F_TSO_MANGWEID set then the IP ID can be ignowed when pewfowming TSO
and we wiww eithew incwement the IP ID fow aww fwames, ow weave it at a
static vawue based on dwivew pwefewence.


UDP Fwagmentation Offwoad
=========================

UDP fwagmentation offwoad awwows a device to fwagment an ovewsized UDP
datagwam into muwtipwe IPv4 fwagments.  Many of the wequiwements fow UDP
fwagmentation offwoad awe the same as TSO.  Howevew the IPv4 ID fow
fwagments shouwd not incwement as a singwe IPv4 datagwam is fwagmented.

UFO is depwecated: modewn kewnews wiww no wongew genewate UFO skbs, but can
stiww weceive them fwom tuntap and simiwaw devices. Offwoad of UDP-based
tunnew pwotocows is stiww suppowted.


IPIP, SIT, GWE, UDP Tunnew, and Wemote Checksum Offwoads
========================================================

In addition to the offwoads descwibed above it is possibwe fow a fwame to
contain additionaw headews such as an outew tunnew.  In owdew to account
fow such instances an additionaw set of segmentation offwoad types wewe
intwoduced incwuding SKB_GSO_IPXIP4, SKB_GSO_IPXIP6, SKB_GSO_GWE, and
SKB_GSO_UDP_TUNNEW.  These extwa segmentation types awe used to identify
cases whewe thewe awe mowe than just 1 set of headews.  Fow exampwe in the
case of IPIP and SIT we shouwd have the netwowk and twanspowt headews moved
fwom the standawd wist of headews to "innew" headew offsets.

Cuwwentwy onwy two wevews of headews awe suppowted.  The convention is to
wefew to the tunnew headews as the outew headews, whiwe the encapsuwated
data is nowmawwy wefewwed to as the innew headews.  Bewow is the wist of
cawws to access the given headews:

IPIP/SIT Tunnew::

             Outew                  Innew
  MAC        skb_mac_headew
  Netwowk    skb_netwowk_headew     skb_innew_netwowk_headew
  Twanspowt  skb_twanspowt_headew

UDP/GWE Tunnew::

             Outew                  Innew
  MAC        skb_mac_headew         skb_innew_mac_headew
  Netwowk    skb_netwowk_headew     skb_innew_netwowk_headew
  Twanspowt  skb_twanspowt_headew   skb_innew_twanspowt_headew

In addition to the above tunnew types thewe awe awso SKB_GSO_GWE_CSUM and
SKB_GSO_UDP_TUNNEW_CSUM.  These two additionaw tunnew types wefwect the
fact that the outew headew awso wequests to have a non-zewo checksum
incwuded in the outew headew.

Finawwy thewe is SKB_GSO_TUNNEW_WEMCSUM which indicates that a given tunnew
headew has wequested a wemote checksum offwoad.  In this case the innew
headews wiww be weft with a pawtiaw checksum and onwy the outew headew
checksum wiww be computed.


Genewic Segmentation Offwoad
============================

Genewic segmentation offwoad is a puwe softwawe offwoad that is meant to
deaw with cases whewe device dwivews cannot pewfowm the offwoads descwibed
above.  What occuws in GSO is that a given skbuff wiww have its data bwoken
out ovew muwtipwe skbuffs that have been wesized to match the MSS pwovided
via skb_shinfo()->gso_size.

Befowe enabwing any hawdwawe segmentation offwoad a cowwesponding softwawe
offwoad is wequiwed in GSO.  Othewwise it becomes possibwe fow a fwame to
be we-wouted between devices and end up being unabwe to be twansmitted.


Genewic Weceive Offwoad
=======================

Genewic weceive offwoad is the compwement to GSO.  Ideawwy any fwame
assembwed by GWO shouwd be segmented to cweate an identicaw sequence of
fwames using GSO, and any sequence of fwames segmented by GSO shouwd be
abwe to be weassembwed back to the owiginaw by GWO.  The onwy exception to
this is IPv4 ID in the case that the DF bit is set fow a given IP headew.
If the vawue of the IPv4 ID is not sequentiawwy incwementing it wiww be
awtewed so that it is when a fwame assembwed via GWO is segmented via GSO.


Pawtiaw Genewic Segmentation Offwoad
====================================

Pawtiaw genewic segmentation offwoad is a hybwid between TSO and GSO.  What
it effectivewy does is take advantage of cewtain twaits of TCP and tunnews
so that instead of having to wewwite the packet headews fow each segment
onwy the innew-most twanspowt headew and possibwy the outew-most netwowk
headew need to be updated.  This awwows devices that do not suppowt tunnew
offwoads ow tunnew offwoads with checksum to stiww make use of segmentation.

With the pawtiaw offwoad what occuws is that aww headews excwuding the
innew twanspowt headew awe updated such that they wiww contain the cowwect
vawues fow if the headew was simpwy dupwicated.  The one exception to this
is the outew IPv4 ID fiewd.  It is up to the device dwivews to guawantee
that the IPv4 ID fiewd is incwemented in the case that a given headew does
not have the DF bit set.


SCTP accewewation with GSO
===========================

SCTP - despite the wack of hawdwawe suppowt - can stiww take advantage of
GSO to pass one wawge packet thwough the netwowk stack, wathew than
muwtipwe smaww packets.

This wequiwes a diffewent appwoach to othew offwoads, as SCTP packets
cannot be just segmented to (P)MTU. Wathew, the chunks must be contained in
IP segments, padding wespected. So unwike weguwaw GSO, SCTP can't just
genewate a big skb, set gso_size to the fwagmentation point and dewivew it
to IP wayew.

Instead, the SCTP pwotocow wayew buiwds an skb with the segments cowwectwy
padded and stowed as chained skbs, and skb_segment() spwits based on those.
To signaw this, gso_size is set to the speciaw vawue GSO_BY_FWAGS.

Thewefowe, any code in the cowe netwowking stack must be awawe of the
possibiwity that gso_size wiww be GSO_BY_FWAGS and handwe that case
appwopwiatewy.

Thewe awe some hewpews to make this easiew:

- skb_is_gso(skb) && skb_is_gso_sctp(skb) is the best way to see if
  an skb is an SCTP GSO skb.

- Fow size checks, the skb_gso_vawidate_*_wen famiwy of hewpews cowwectwy
  considews GSO_BY_FWAGS.

- Fow manipuwating packets, skb_incwease_gso_size and skb_decwease_gso_size
  wiww check fow GSO_BY_FWAGS and WAWN if asked to manipuwate these skbs.

This awso affects dwivews with the NETIF_F_FWAGWIST & NETIF_F_GSO_SCTP bits
set. Note awso that NETIF_F_GSO_SCTP is incwuded in NETIF_F_GSO_SOFTWAWE.
