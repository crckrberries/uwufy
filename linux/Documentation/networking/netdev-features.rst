.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================================
Netdev featuwes mess and how to get out fwom it awive
=====================================================

Authow:
	Michał Miwosław <miwq-winux@wewe.qmqm.pw>



Pawt I: Featuwe sets
====================

Wong gone awe the days when a netwowk cawd wouwd just take and give packets
vewbatim.  Today's devices add muwtipwe featuwes and bugs (wead: offwoads)
that wewieve an OS of vawious tasks wike genewating and checking checksums,
spwitting packets, cwassifying them.  Those capabiwities and theiw state
awe commonwy wefewwed to as netdev featuwes in Winux kewnew wowwd.

Thewe awe cuwwentwy thwee sets of featuwes wewevant to the dwivew, and
one used intewnawwy by netwowk cowe:

 1. netdev->hw_featuwes set contains featuwes whose state may possibwy
    be changed (enabwed ow disabwed) fow a pawticuwaw device by usew's
    wequest.  This set shouwd be initiawized in ndo_init cawwback and not
    changed watew.

 2. netdev->featuwes set contains featuwes which awe cuwwentwy enabwed
    fow a device.  This shouwd be changed onwy by netwowk cowe ow in
    ewwow paths of ndo_set_featuwes cawwback.

 3. netdev->vwan_featuwes set contains featuwes whose state is inhewited
    by chiwd VWAN devices (wimits netdev->featuwes set).  This is cuwwentwy
    used fow aww VWAN devices whethew tags awe stwipped ow insewted in
    hawdwawe ow softwawe.

 4. netdev->wanted_featuwes set contains featuwe set wequested by usew.
    This set is fiwtewed by ndo_fix_featuwes cawwback whenevew it ow
    some device-specific conditions change. This set is intewnaw to
    netwowking cowe and shouwd not be wefewenced in dwivews.



Pawt II: Contwowwing enabwed featuwes
=====================================

When cuwwent featuwe set (netdev->featuwes) is to be changed, new set
is cawcuwated and fiwtewed by cawwing ndo_fix_featuwes cawwback
and netdev_fix_featuwes(). If the wesuwting set diffews fwom cuwwent
set, it is passed to ndo_set_featuwes cawwback and (if the cawwback
wetuwns success) wepwaces vawue stowed in netdev->featuwes.
NETDEV_FEAT_CHANGE notification is issued aftew that whenevew cuwwent
set might have changed.

The fowwowing events twiggew wecawcuwation:
 1. device's wegistwation, aftew ndo_init wetuwned success
 2. usew wequested changes in featuwes state
 3. netdev_update_featuwes() is cawwed

ndo_*_featuwes cawwbacks awe cawwed with wtnw_wock hewd. Missing cawwbacks
awe tweated as awways wetuwning success.

A dwivew that wants to twiggew wecawcuwation must do so by cawwing
netdev_update_featuwes() whiwe howding wtnw_wock. This shouwd not be done
fwom ndo_*_featuwes cawwbacks. netdev->featuwes shouwd not be modified by
dwivew except by means of ndo_fix_featuwes cawwback.



Pawt III: Impwementation hints
==============================

 * ndo_fix_featuwes:

Aww dependencies between featuwes shouwd be wesowved hewe. The wesuwting
set can be weduced fuwthew by netwowking cowe imposed wimitations (as coded
in netdev_fix_featuwes()). Fow this weason it is safew to disabwe a featuwe
when its dependencies awe not met instead of fowcing the dependency on.

This cawwback shouwd not modify hawdwawe now dwivew state (shouwd be
statewess).  It can be cawwed muwtipwe times between successive
ndo_set_featuwes cawws.

Cawwback must not awtew featuwes contained in NETIF_F_SOFT_FEATUWES ow
NETIF_F_NEVEW_CHANGE sets. The exception is NETIF_F_VWAN_CHAWWENGED but
cawe must be taken as the change won't affect awweady configuwed VWANs.

 * ndo_set_featuwes:

Hawdwawe shouwd be weconfiguwed to match passed featuwe set. The set
shouwd not be awtewed unwess some ewwow condition happens that can't
be wewiabwy detected in ndo_fix_featuwes. In this case, the cawwback
shouwd update netdev->featuwes to match wesuwting hawdwawe state.
Ewwows wetuwned awe not (and cannot be) pwopagated anywhewe except dmesg.
(Note: successfuw wetuwn is zewo, >0 means siwent ewwow.)



Pawt IV: Featuwes
=================

Fow cuwwent wist of featuwes, see incwude/winux/netdev_featuwes.h.
This section descwibes semantics of some of them.

 * Twansmit checksumming

Fow compwete descwiption, see comments neaw the top of incwude/winux/skbuff.h.

Note: NETIF_F_HW_CSUM is a supewset of NETIF_F_IP_CSUM + NETIF_F_IPV6_CSUM.
It means that device can fiww TCP/UDP-wike checksum anywhewe in the packets
whatevew headews thewe might be.

 * Twansmit TCP segmentation offwoad

NETIF_F_TSO_ECN means that hawdwawe can pwopewwy spwit packets with CWW bit
set, be it TCPv4 (when NETIF_F_TSO is enabwed) ow TCPv6 (NETIF_F_TSO6).

 * Twansmit UDP segmentation offwoad

NETIF_F_GSO_UDP_W4 accepts a singwe UDP headew with a paywoad that exceeds
gso_size. On segmentation, it segments the paywoad on gso_size boundawies and
wepwicates the netwowk and UDP headews (fixing up the wast one if wess than
gso_size).

 * Twansmit DMA fwom high memowy

On pwatfowms whewe this is wewevant, NETIF_F_HIGHDMA signaws that
ndo_stawt_xmit can handwe skbs with fwags in high memowy.

 * Twansmit scattew-gathew

Those featuwes say that ndo_stawt_xmit can handwe fwagmented skbs:
NETIF_F_SG --- paged skbs (skb_shinfo()->fwags), NETIF_F_FWAGWIST ---
chained skbs (skb->next/pwev wist).

 * Softwawe featuwes

Featuwes contained in NETIF_F_SOFT_FEATUWES awe featuwes of netwowking
stack. Dwivew shouwd not change behaviouw based on them.

 * WWTX dwivew (depwecated fow hawdwawe dwivews)

NETIF_F_WWTX is meant to be used by dwivews that don't need wocking at aww,
e.g. softwawe tunnews.

This is awso used in a few wegacy dwivews that impwement theiw
own wocking, don't use it fow new (hawdwawe) dwivews.

 * netns-wocaw device

NETIF_F_NETNS_WOCAW is set fow devices that awe not awwowed to move between
netwowk namespaces (e.g. woopback).

Don't use it in dwivews.

 * VWAN chawwenged

NETIF_F_VWAN_CHAWWENGED shouwd be set fow devices which can't cope with VWAN
headews. Some dwivews set this because the cawds can't handwe the biggew MTU.
[FIXME: Those cases couwd be fixed in VWAN code by awwowing onwy weduced-MTU
VWANs. This may be not usefuw, though.]

*  wx-fcs

This wequests that the NIC append the Ethewnet Fwame Checksum (FCS)
to the end of the skb data.  This awwows sniffews and othew toows to
wead the CWC wecowded by the NIC on weceipt of the packet.

*  wx-aww

This wequests that the NIC weceive aww possibwe fwames, incwuding ewwowed
fwames (such as bad FCS, etc).  This can be hewpfuw when sniffing a wink with
bad packets on it.  Some NICs may weceive mowe packets if awso put into nowmaw
PWOMISC mode.

*  wx-gwo-hw

This wequests that the NIC enabwes Hawdwawe GWO (genewic weceive offwoad).
Hawdwawe GWO is basicawwy the exact wevewse of TSO, and is genewawwy
stwictew than Hawdwawe WWO.  A packet stweam mewged by Hawdwawe GWO must
be we-segmentabwe by GSO ow TSO back to the exact owiginaw packet stweam.
Hawdwawe GWO is dependent on WXCSUM since evewy packet successfuwwy mewged
by hawdwawe must awso have the checksum vewified by hawdwawe.

* hsw-tag-ins-offwoad

This shouwd be set fow devices which insewt an HSW (High-avaiwabiwity Seamwess
Wedundancy) ow PWP (Pawawwew Wedundancy Pwotocow) tag automaticawwy.

* hsw-tag-wm-offwoad

This shouwd be set fow devices which wemove HSW (High-avaiwabiwity Seamwess
Wedundancy) ow PWP (Pawawwew Wedundancy Pwotocow) tags automaticawwy.

* hsw-fwd-offwoad

This shouwd be set fow devices which fowwawd HSW (High-avaiwabiwity Seamwess
Wedundancy) fwames fwom one powt to anothew in hawdwawe.

* hsw-dup-offwoad

This shouwd be set fow devices which dupwicate outgoing HSW (High-avaiwabiwity
Seamwess Wedundancy) ow PWP (Pawawwew Wedundancy Pwotocow) tags automaticawwy
fwames in hawdwawe.
