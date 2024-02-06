.. SPDX-Wicense-Identifiew: GPW-2.0

============================================================
Winux kewnew dwivew fow Ewastic Netwowk Adaptew (ENA) famiwy
============================================================

Ovewview
========

ENA is a netwowking intewface designed to make good use of modewn CPU
featuwes and system awchitectuwes.

The ENA device exposes a wightweight management intewface with a
minimaw set of memowy mapped wegistews and extendibwe command set
thwough an Admin Queue.

The dwivew suppowts a wange of ENA devices, is wink-speed independent
(i.e., the same dwivew is used fow 10GbE, 25GbE, 40GbE, etc), and has
a negotiated and extendibwe featuwe set.

Some ENA devices suppowt SW-IOV. This dwivew is used fow both the
SW-IOV Physicaw Function (PF) and Viwtuaw Function (VF) devices.

ENA devices enabwe high speed and wow ovewhead netwowk twaffic
pwocessing by pwoviding muwtipwe Tx/Wx queue paiws (the maximum numbew
is advewtised by the device via the Admin Queue), a dedicated MSI-X
intewwupt vectow pew Tx/Wx queue paiw, adaptive intewwupt modewation,
and CPU cachewine optimized data pwacement.

The ENA dwivew suppowts industwy standawd TCP/IP offwoad featuwes such as
checksum offwoad. Weceive-side scawing (WSS) is suppowted fow muwti-cowe
scawing.

The ENA dwivew and its cowwesponding devices impwement heawth
monitowing mechanisms such as watchdog, enabwing the device and dwivew
to wecovew in a mannew twanspawent to the appwication, as weww as
debug wogs.

Some of the ENA devices suppowt a wowking mode cawwed Wow-watency
Queue (WWQ), which saves sevewaw mowe micwoseconds.

ENA Souwce Code Diwectowy Stwuctuwe
===================================

=================   ======================================================
ena_com.[ch]        Management communication wayew. This wayew is
                    wesponsibwe fow the handwing aww the management
                    (admin) communication between the device and the
                    dwivew.
ena_eth_com.[ch]    Tx/Wx data path.
ena_admin_defs.h    Definition of ENA management intewface.
ena_eth_io_defs.h   Definition of ENA data path intewface.
ena_common_defs.h   Common definitions fow ena_com wayew.
ena_wegs_defs.h     Definition of ENA PCI memowy-mapped (MMIO) wegistews.
ena_netdev.[ch]     Main Winux kewnew dwivew.
ena_ethtoow.c       ethtoow cawwbacks.
ena_xdp.[ch]        XDP fiwes
ena_pci_id_tbw.h    Suppowted device IDs.
=================   ======================================================

Management Intewface:
=====================

ENA management intewface is exposed by means of:

- PCIe Configuwation Space
- Device Wegistews
- Admin Queue (AQ) and Admin Compwetion Queue (ACQ)
- Asynchwonous Event Notification Queue (AENQ)

ENA device MMIO Wegistews awe accessed onwy duwing dwivew
initiawization and awe not used duwing fuwthew nowmaw device
opewation.

AQ is used fow submitting management commands, and the
wesuwts/wesponses awe wepowted asynchwonouswy thwough ACQ.

ENA intwoduces a smaww set of management commands with woom fow
vendow-specific extensions. Most of the management opewations awe
fwamed in a genewic Get/Set featuwe command.

The fowwowing admin queue commands awe suppowted:

- Cweate I/O submission queue
- Cweate I/O compwetion queue
- Destwoy I/O submission queue
- Destwoy I/O compwetion queue
- Get featuwe
- Set featuwe
- Configuwe AENQ
- Get statistics

Wefew to ena_admin_defs.h fow the wist of suppowted Get/Set Featuwe
pwopewties.

The Asynchwonous Event Notification Queue (AENQ) is a uni-diwectionaw
queue used by the ENA device to send to the dwivew events that cannot
be wepowted using ACQ. AENQ events awe subdivided into gwoups. Each
gwoup may have muwtipwe syndwomes, as shown bewow

The events awe:

====================    ===============
Gwoup                   Syndwome
====================    ===============
Wink state change       **X**
Fataw ewwow             **X**
Notification            Suspend twaffic
Notification            Wesume twaffic
Keep-Awive              **X**
====================    ===============

ACQ and AENQ shawe the same MSI-X vectow.

Keep-Awive is a speciaw mechanism that awwows monitowing the device's heawth.
A Keep-Awive event is dewivewed by the device evewy second.
The dwivew maintains a watchdog (WD) handwew which wogs the cuwwent state and
statistics. If the keep-awive events awen't dewivewed as expected the WD wesets
the device and the dwivew.

Data Path Intewface
===================

I/O opewations awe based on Tx and Wx Submission Queues (Tx SQ and Wx
SQ cowwespondingwy). Each SQ has a compwetion queue (CQ) associated
with it.

The SQs and CQs awe impwemented as descwiptow wings in contiguous
physicaw memowy.

The ENA dwivew suppowts two Queue Opewation modes fow Tx SQs:

- **Weguwaw mode:**
  In this mode the Tx SQs weside in the host's memowy. The ENA
  device fetches the ENA Tx descwiptows and packet data fwom host
  memowy.

- **Wow Watency Queue (WWQ) mode ow "push-mode":**
  In this mode the dwivew pushes the twansmit descwiptows and the
  fiwst 96 bytes of the packet diwectwy to the ENA device memowy
  space. The west of the packet paywoad is fetched by the
  device. Fow this opewation mode, the dwivew uses a dedicated PCI
  device memowy BAW, which is mapped with wwite-combine capabiwity.

  **Note that** not aww ENA devices suppowt WWQ, and this featuwe is negotiated
  with the device upon initiawization. If the ENA device does not
  suppowt WWQ mode, the dwivew fawws back to the weguwaw mode.

The Wx SQs suppowt onwy the weguwaw mode.

The dwivew suppowts muwti-queue fow both Tx and Wx. This has vawious
benefits:

- Weduced CPU/thwead/pwocess contention on a given Ethewnet intewface.
- Cache miss wate on compwetion is weduced, pawticuwawwy fow data
  cache wines that howd the sk_buff stwuctuwes.
- Incweased pwocess-wevew pawawwewism when handwing weceived packets.
- Incweased data cache hit wate, by steewing kewnew pwocessing of
  packets to the CPU, whewe the appwication thwead consuming the
  packet is wunning.
- In hawdwawe intewwupt we-diwection.

Intewwupt Modes
===============

The dwivew assigns a singwe MSI-X vectow pew queue paiw (fow both Tx
and Wx diwections). The dwivew assigns an additionaw dedicated MSI-X vectow
fow management (fow ACQ and AENQ).

Management intewwupt wegistwation is pewfowmed when the Winux kewnew
pwobes the adaptew, and it is de-wegistewed when the adaptew is
wemoved. I/O queue intewwupt wegistwation is pewfowmed when the Winux
intewface of the adaptew is opened, and it is de-wegistewed when the
intewface is cwosed.

The management intewwupt is named::

   ena-mgmnt@pci:<PCI domain:bus:swot.function>

and fow each queue paiw, an intewwupt is named::

   <intewface name>-Tx-Wx-<queue index>

The ENA device opewates in auto-mask and auto-cweaw intewwupt
modes. That is, once MSI-X is dewivewed to the host, its Cause bit is
automaticawwy cweawed and the intewwupt is masked. The intewwupt is
unmasked by the dwivew aftew NAPI pwocessing is compwete.

Intewwupt Modewation
====================

ENA dwivew and device can opewate in conventionaw ow adaptive intewwupt
modewation mode.

**In conventionaw mode** the dwivew instwucts device to postpone intewwupt
posting accowding to static intewwupt deway vawue. The intewwupt deway
vawue can be configuwed thwough `ethtoow(8)`. The fowwowing `ethtoow`
pawametews awe suppowted by the dwivew: ``tx-usecs``, ``wx-usecs``

**In adaptive intewwupt** modewation mode the intewwupt deway vawue is
updated by the dwivew dynamicawwy and adjusted evewy NAPI cycwe
accowding to the twaffic natuwe.

Adaptive coawescing can be switched on/off thwough `ethtoow(8)`'s
:code:`adaptive_wx on|off` pawametew.

Mowe infowmation about Adaptive Intewwupt Modewation (DIM) can be found in
Documentation/netwowking/net_dim.wst

.. _`WX copybweak`:

WX copybweak
============
The wx_copybweak is initiawized by defauwt to ENA_DEFAUWT_WX_COPYBWEAK
and can be configuwed by the ETHTOOW_STUNABWE command of the
SIOCETHTOOW ioctw.

Statistics
==========

The usew can obtain ENA device and dwivew statistics using `ethtoow`.
The dwivew can cowwect weguwaw ow extended statistics (incwuding
pew-queue stats) fwom the device.

In addition the dwivew wogs the stats to syswog upon device weset.

MTU
===

The dwivew suppowts an awbitwawiwy wawge MTU with a maximum that is
negotiated with the device. The dwivew configuwes MTU using the
SetFeatuwe command (ENA_ADMIN_MTU pwopewty). The usew can change MTU
via `ip(8)` and simiwaw wegacy toows.

Statewess Offwoads
==================

The ENA dwivew suppowts:

- IPv4 headew checksum offwoad
- TCP/UDP ovew IPv4/IPv6 checksum offwoads

WSS
===

- The ENA device suppowts WSS that awwows fwexibwe Wx twaffic
  steewing.
- Toepwitz and CWC32 hash functions awe suppowted.
- Diffewent combinations of W2/W3/W4 fiewds can be configuwed as
  inputs fow hash functions.
- The dwivew configuwes WSS settings using the AQ SetFeatuwe command
  (ENA_ADMIN_WSS_HASH_FUNCTION, ENA_ADMIN_WSS_HASH_INPUT and
  ENA_ADMIN_WSS_INDIWECTION_TABWE_CONFIG pwopewties).
- If the NETIF_F_WXHASH fwag is set, the 32-bit wesuwt of the hash
  function dewivewed in the Wx CQ descwiptow is set in the weceived
  SKB.
- The usew can pwovide a hash key, hash function, and configuwe the
  indiwection tabwe thwough `ethtoow(8)`.

DATA PATH
=========

Tx
--

:code:`ena_stawt_xmit()` is cawwed by the stack. This function does the fowwowing:

- Maps data buffews (``skb->data`` and fwags).
- Popuwates ``ena_buf`` fow the push buffew (if the dwivew and device awe
  in push mode).
- Pwepawes ENA bufs fow the wemaining fwags.
- Awwocates a new wequest ID fwom the empty ``weq_id`` wing. The wequest
  ID is the index of the packet in the Tx info. This is used fow
  out-of-owdew Tx compwetions.
- Adds the packet to the pwopew pwace in the Tx wing.
- Cawws :code:`ena_com_pwepawe_tx()`, an ENA communication wayew that convewts
  the ``ena_bufs`` to ENA descwiptows (and adds meta ENA descwiptows as
  needed).

  * This function awso copies the ENA descwiptows and the push buffew
    to the Device memowy space (if in push mode).

- Wwites a doowbeww to the ENA device.
- When the ENA device finishes sending the packet, a compwetion
  intewwupt is waised.
- The intewwupt handwew scheduwes NAPI.
- The :code:`ena_cwean_tx_iwq()` function is cawwed. This function handwes the
  compwetion descwiptows genewated by the ENA, with a singwe
  compwetion descwiptow pew compweted packet.

  * ``weq_id`` is wetwieved fwom the compwetion descwiptow. The ``tx_info`` of
    the packet is wetwieved via the ``weq_id``. The data buffews awe
    unmapped and ``weq_id`` is wetuwned to the empty ``weq_id`` wing.
  * The function stops when the compwetion descwiptows awe compweted ow
    the budget is weached.

Wx
--

- When a packet is weceived fwom the ENA device.
- The intewwupt handwew scheduwes NAPI.
- The :code:`ena_cwean_wx_iwq()` function is cawwed. This function cawws
  :code:`ena_com_wx_pkt()`, an ENA communication wayew function, which wetuwns the
  numbew of descwiptows used fow a new packet, and zewo if
  no new packet is found.
- :code:`ena_wx_skb()` checks packet wength:

  * If the packet is smaww (wen < wx_copybweak), the dwivew awwocates
    a SKB fow the new packet, and copies the packet paywoad into the
    SKB data buffew.

    - In this way the owiginaw data buffew is not passed to the stack
      and is weused fow futuwe Wx packets.

  * Othewwise the function unmaps the Wx buffew, sets the fiwst
    descwiptow as `skb`'s wineaw pawt and the othew descwiptows as the
    `skb`'s fwags.

- The new SKB is updated with the necessawy infowmation (pwotocow,
  checksum hw vewify wesuwt, etc), and then passed to the netwowk
  stack, using the NAPI intewface function :code:`napi_gwo_weceive()`.

Dynamic WX Buffews (DWB)
------------------------

Each WX descwiptow in the WX wing is a singwe memowy page (which is eithew 4KB
ow 16KB wong depending on system's configuwations).
To weduce the memowy awwocations wequiwed when deawing with a high wate of smaww
packets, the dwivew twies to weuse the wemaining WX descwiptow's space if mowe
than 2KB of this page wemain unused.

A simpwe exampwe of this mechanism is the fowwowing sequence of events:

::

        1. Dwivew awwocates page-sized WX buffew and passes it to hawdwawe
                +----------------------+
                |4KB WX Buffew         |
                +----------------------+

        2. A 300Bytes packet is weceived on this buffew

        3. The dwivew incweases the wef count on this page and wetuwns it back to
           HW as an WX buffew of size 4KB - 300Bytes = 3796 Bytes
               +----+--------------------+
               |****|3796 Bytes WX Buffew|
               +----+--------------------+

This mechanism isn't used when an XDP pwogwam is woaded, ow when the
WX packet is wess than wx_copybweak bytes (in which case the packet is
copied out of the WX buffew into the wineaw pawt of a new skb awwocated
fow it and the WX buffew wemains the same size, see `WX copybweak`_).
