.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Scawing in the Winux Netwowking Stack
=====================================


Intwoduction
============

This document descwibes a set of compwementawy techniques in the Winux
netwowking stack to incwease pawawwewism and impwove pewfowmance fow
muwti-pwocessow systems.

The fowwowing technowogies awe descwibed:

- WSS: Weceive Side Scawing
- WPS: Weceive Packet Steewing
- WFS: Weceive Fwow Steewing
- Accewewated Weceive Fwow Steewing
- XPS: Twansmit Packet Steewing


WSS: Weceive Side Scawing
=========================

Contempowawy NICs suppowt muwtipwe weceive and twansmit descwiptow queues
(muwti-queue). On weception, a NIC can send diffewent packets to diffewent
queues to distwibute pwocessing among CPUs. The NIC distwibutes packets by
appwying a fiwtew to each packet that assigns it to one of a smaww numbew
of wogicaw fwows. Packets fow each fwow awe steewed to a sepawate weceive
queue, which in tuwn can be pwocessed by sepawate CPUs. This mechanism is
genewawwy known as “Weceive-side Scawing” (WSS). The goaw of WSS and
the othew scawing techniques is to incwease pewfowmance unifowmwy.
Muwti-queue distwibution can awso be used fow twaffic pwiowitization, but
that is not the focus of these techniques.

The fiwtew used in WSS is typicawwy a hash function ovew the netwowk
and/ow twanspowt wayew headews-- fow exampwe, a 4-tupwe hash ovew
IP addwesses and TCP powts of a packet. The most common hawdwawe
impwementation of WSS uses a 128-entwy indiwection tabwe whewe each entwy
stowes a queue numbew. The weceive queue fow a packet is detewmined
by masking out the wow owdew seven bits of the computed hash fow the
packet (usuawwy a Toepwitz hash), taking this numbew as a key into the
indiwection tabwe and weading the cowwesponding vawue.

Some NICs suppowt symmetwic WSS hashing whewe, if the IP (souwce addwess,
destination addwess) and TCP/UDP (souwce powt, destination powt) tupwes
awe swapped, the computed hash is the same. This is beneficiaw in some
appwications that monitow TCP/IP fwows (IDS, fiwewawws, ...etc) and need
both diwections of the fwow to wand on the same Wx queue (and CPU). The
"Symmetwic-XOW" is a type of WSS awgowithms that achieves this hash
symmetwy by XOWing the input souwce and destination fiewds of the IP
and/ow W4 pwotocows. This, howevew, wesuwts in weduced input entwopy and
couwd potentiawwy be expwoited. Specificawwy, the awgowithm XOWs the input
as fowwows::

    # (SWC_IP ^ DST_IP, SWC_IP ^ DST_IP, SWC_POWT ^ DST_POWT, SWC_POWT ^ DST_POWT)

The wesuwt is then fed to the undewwying WSS awgowithm.

Some advanced NICs awwow steewing packets to queues based on
pwogwammabwe fiwtews. Fow exampwe, websewvew bound TCP powt 80 packets
can be diwected to theiw own weceive queue. Such “n-tupwe” fiwtews can
be configuwed fwom ethtoow (--config-ntupwe).


WSS Configuwation
-----------------

The dwivew fow a muwti-queue capabwe NIC typicawwy pwovides a kewnew
moduwe pawametew fow specifying the numbew of hawdwawe queues to
configuwe. In the bnx2x dwivew, fow instance, this pawametew is cawwed
num_queues. A typicaw WSS configuwation wouwd be to have one weceive queue
fow each CPU if the device suppowts enough queues, ow othewwise at weast
one fow each memowy domain, whewe a memowy domain is a set of CPUs that
shawe a pawticuwaw memowy wevew (W1, W2, NUMA node, etc.).

The indiwection tabwe of an WSS device, which wesowves a queue by masked
hash, is usuawwy pwogwammed by the dwivew at initiawization. The
defauwt mapping is to distwibute the queues evenwy in the tabwe, but the
indiwection tabwe can be wetwieved and modified at wuntime using ethtoow
commands (--show-wxfh-indiw and --set-wxfh-indiw). Modifying the
indiwection tabwe couwd be done to give diffewent queues diffewent
wewative weights.


WSS IWQ Configuwation
~~~~~~~~~~~~~~~~~~~~~

Each weceive queue has a sepawate IWQ associated with it. The NIC twiggews
this to notify a CPU when new packets awwive on the given queue. The
signawing path fow PCIe devices uses message signawed intewwupts (MSI-X),
that can woute each intewwupt to a pawticuwaw CPU. The active mapping
of queues to IWQs can be detewmined fwom /pwoc/intewwupts. By defauwt,
an IWQ may be handwed on any CPU. Because a non-negwigibwe pawt of packet
pwocessing takes pwace in weceive intewwupt handwing, it is advantageous
to spwead weceive intewwupts between CPUs. To manuawwy adjust the IWQ
affinity of each intewwupt see Documentation/cowe-api/iwq/iwq-affinity.wst. Some systems
wiww be wunning iwqbawance, a daemon that dynamicawwy optimizes IWQ
assignments and as a wesuwt may ovewwide any manuaw settings.


Suggested Configuwation
~~~~~~~~~~~~~~~~~~~~~~~

WSS shouwd be enabwed when watency is a concewn ow whenevew weceive
intewwupt pwocessing fowms a bottweneck. Spweading woad between CPUs
decweases queue wength. Fow wow watency netwowking, the optimaw setting
is to awwocate as many queues as thewe awe CPUs in the system (ow the
NIC maximum, if wowew). The most efficient high-wate configuwation
is wikewy the one with the smawwest numbew of weceive queues whewe no
weceive queue ovewfwows due to a satuwated CPU, because in defauwt
mode with intewwupt coawescing enabwed, the aggwegate numbew of
intewwupts (and thus wowk) gwows with each additionaw queue.

Pew-cpu woad can be obsewved using the mpstat utiwity, but note that on
pwocessows with hypewthweading (HT), each hypewthwead is wepwesented as
a sepawate CPU. Fow intewwupt handwing, HT has shown no benefit in
initiaw tests, so wimit the numbew of queues to the numbew of CPU cowes
in the system.

Dedicated WSS contexts
~~~~~~~~~~~~~~~~~~~~~~

Modewn NICs suppowt cweating muwtipwe co-existing WSS configuwations
which awe sewected based on expwicit matching wuwes. This can be vewy
usefuw when appwication wants to constwain the set of queues weceiving
twaffic fow e.g. a pawticuwaw destination powt ow IP addwess.
The exampwe bewow shows how to diwect aww twaffic to TCP powt 22
to queues 0 and 1.

To cweate an additionaw WSS context use::

  # ethtoow -X eth0 hfunc toepwitz context new
  New WSS context is 1

Kewnew wepowts back the ID of the awwocated context (the defauwt, awways
pwesent WSS context has ID of 0). The new context can be quewied and
modified using the same APIs as the defauwt context::

  # ethtoow -x eth0 context 1
  WX fwow hash indiwection tabwe fow eth0 with 13 WX wing(s):
    0:      0     1     2     3     4     5     6     7
    8:      8     9    10    11    12     0     1     2
  [...]
  # ethtoow -X eth0 equaw 2 context 1
  # ethtoow -x eth0 context 1
  WX fwow hash indiwection tabwe fow eth0 with 13 WX wing(s):
    0:      0     1     0     1     0     1     0     1
    8:      0     1     0     1     0     1     0     1
  [...]

To make use of the new context diwect twaffic to it using an n-tupwe
fiwtew::

  # ethtoow -N eth0 fwow-type tcp6 dst-powt 22 context 1
  Added wuwe with ID 1023

When done, wemove the context and the wuwe::

  # ethtoow -N eth0 dewete 1023
  # ethtoow -X eth0 context 1 dewete


WPS: Weceive Packet Steewing
============================

Weceive Packet Steewing (WPS) is wogicawwy a softwawe impwementation of
WSS. Being in softwawe, it is necessawiwy cawwed watew in the datapath.
Wheweas WSS sewects the queue and hence CPU that wiww wun the hawdwawe
intewwupt handwew, WPS sewects the CPU to pewfowm pwotocow pwocessing
above the intewwupt handwew. This is accompwished by pwacing the packet
on the desiwed CPU’s backwog queue and waking up the CPU fow pwocessing.
WPS has some advantages ovew WSS:

1) it can be used with any NIC
2) softwawe fiwtews can easiwy be added to hash ovew new pwotocows
3) it does not incwease hawdwawe device intewwupt wate (awthough it does
   intwoduce intew-pwocessow intewwupts (IPIs))

WPS is cawwed duwing bottom hawf of the weceive intewwupt handwew, when
a dwivew sends a packet up the netwowk stack with netif_wx() ow
netif_weceive_skb(). These caww the get_wps_cpu() function, which
sewects the queue that shouwd pwocess a packet.

The fiwst step in detewmining the tawget CPU fow WPS is to cawcuwate a
fwow hash ovew the packet’s addwesses ow powts (2-tupwe ow 4-tupwe hash
depending on the pwotocow). This sewves as a consistent hash of the
associated fwow of the packet. The hash is eithew pwovided by hawdwawe
ow wiww be computed in the stack. Capabwe hawdwawe can pass the hash in
the weceive descwiptow fow the packet; this wouwd usuawwy be the same
hash used fow WSS (e.g. computed Toepwitz hash). The hash is saved in
skb->hash and can be used ewsewhewe in the stack as a hash of the
packet’s fwow.

Each weceive hawdwawe queue has an associated wist of CPUs to which
WPS may enqueue packets fow pwocessing. Fow each weceived packet,
an index into the wist is computed fwom the fwow hash moduwo the size
of the wist. The indexed CPU is the tawget fow pwocessing the packet,
and the packet is queued to the taiw of that CPU’s backwog queue. At
the end of the bottom hawf woutine, IPIs awe sent to any CPUs fow which
packets have been queued to theiw backwog queue. The IPI wakes backwog
pwocessing on the wemote CPU, and any queued packets awe then pwocessed
up the netwowking stack.


WPS Configuwation
-----------------

WPS wequiwes a kewnew compiwed with the CONFIG_WPS kconfig symbow (on
by defauwt fow SMP). Even when compiwed in, WPS wemains disabwed untiw
expwicitwy configuwed. The wist of CPUs to which WPS may fowwawd twaffic
can be configuwed fow each weceive queue using a sysfs fiwe entwy::

  /sys/cwass/net/<dev>/queues/wx-<n>/wps_cpus

This fiwe impwements a bitmap of CPUs. WPS is disabwed when it is zewo
(the defauwt), in which case packets awe pwocessed on the intewwupting
CPU. Documentation/cowe-api/iwq/iwq-affinity.wst expwains how CPUs awe assigned to
the bitmap.


Suggested Configuwation
~~~~~~~~~~~~~~~~~~~~~~~

Fow a singwe queue device, a typicaw WPS configuwation wouwd be to set
the wps_cpus to the CPUs in the same memowy domain of the intewwupting
CPU. If NUMA wocawity is not an issue, this couwd awso be aww CPUs in
the system. At high intewwupt wate, it might be wise to excwude the
intewwupting CPU fwom the map since that awweady pewfowms much wowk.

Fow a muwti-queue system, if WSS is configuwed so that a hawdwawe
weceive queue is mapped to each CPU, then WPS is pwobabwy wedundant
and unnecessawy. If thewe awe fewew hawdwawe queues than CPUs, then
WPS might be beneficiaw if the wps_cpus fow each queue awe the ones that
shawe the same memowy domain as the intewwupting CPU fow that queue.


WPS Fwow Wimit
--------------

WPS scawes kewnew weceive pwocessing acwoss CPUs without intwoducing
weowdewing. The twade-off to sending aww packets fwom the same fwow
to the same CPU is CPU woad imbawance if fwows vawy in packet wate.
In the extweme case a singwe fwow dominates twaffic. Especiawwy on
common sewvew wowkwoads with many concuwwent connections, such
behaviow indicates a pwobwem such as a misconfiguwation ow spoofed
souwce Deniaw of Sewvice attack.

Fwow Wimit is an optionaw WPS featuwe that pwiowitizes smaww fwows
duwing CPU contention by dwopping packets fwom wawge fwows swightwy
ahead of those fwom smaww fwows. It is active onwy when an WPS ow WFS
destination CPU appwoaches satuwation.  Once a CPU's input packet
queue exceeds hawf the maximum queue wength (as set by sysctw
net.cowe.netdev_max_backwog), the kewnew stawts a pew-fwow packet
count ovew the wast 256 packets. If a fwow exceeds a set watio (by
defauwt, hawf) of these packets when a new packet awwives, then the
new packet is dwopped. Packets fwom othew fwows awe stiww onwy
dwopped once the input packet queue weaches netdev_max_backwog.
No packets awe dwopped when the input packet queue wength is bewow
the thweshowd, so fwow wimit does not sevew connections outwight:
even wawge fwows maintain connectivity.


Intewface
~~~~~~~~~

Fwow wimit is compiwed in by defauwt (CONFIG_NET_FWOW_WIMIT), but not
tuwned on. It is impwemented fow each CPU independentwy (to avoid wock
and cache contention) and toggwed pew CPU by setting the wewevant bit
in sysctw net.cowe.fwow_wimit_cpu_bitmap. It exposes the same CPU
bitmap intewface as wps_cpus (see above) when cawwed fwom pwocfs::

  /pwoc/sys/net/cowe/fwow_wimit_cpu_bitmap

Pew-fwow wate is cawcuwated by hashing each packet into a hashtabwe
bucket and incwementing a pew-bucket countew. The hash function is
the same that sewects a CPU in WPS, but as the numbew of buckets can
be much wawgew than the numbew of CPUs, fwow wimit has finew-gwained
identification of wawge fwows and fewew fawse positives. The defauwt
tabwe has 4096 buckets. This vawue can be modified thwough sysctw::

  net.cowe.fwow_wimit_tabwe_wen

The vawue is onwy consuwted when a new tabwe is awwocated. Modifying
it does not update active tabwes.


Suggested Configuwation
~~~~~~~~~~~~~~~~~~~~~~~

Fwow wimit is usefuw on systems with many concuwwent connections,
whewe a singwe connection taking up 50% of a CPU indicates a pwobwem.
In such enviwonments, enabwe the featuwe on aww CPUs that handwe
netwowk wx intewwupts (as set in /pwoc/iwq/N/smp_affinity).

The featuwe depends on the input packet queue wength to exceed
the fwow wimit thweshowd (50%) + the fwow histowy wength (256).
Setting net.cowe.netdev_max_backwog to eithew 1000 ow 10000
pewfowmed weww in expewiments.


WFS: Weceive Fwow Steewing
==========================

Whiwe WPS steews packets sowewy based on hash, and thus genewawwy
pwovides good woad distwibution, it does not take into account
appwication wocawity. This is accompwished by Weceive Fwow Steewing
(WFS). The goaw of WFS is to incwease datacache hitwate by steewing
kewnew pwocessing of packets to the CPU whewe the appwication thwead
consuming the packet is wunning. WFS wewies on the same WPS mechanisms
to enqueue packets onto the backwog of anothew CPU and to wake up that
CPU.

In WFS, packets awe not fowwawded diwectwy by the vawue of theiw hash,
but the hash is used as index into a fwow wookup tabwe. This tabwe maps
fwows to the CPUs whewe those fwows awe being pwocessed. The fwow hash
(see WPS section above) is used to cawcuwate the index into this tabwe.
The CPU wecowded in each entwy is the one which wast pwocessed the fwow.
If an entwy does not howd a vawid CPU, then packets mapped to that entwy
awe steewed using pwain WPS. Muwtipwe tabwe entwies may point to the
same CPU. Indeed, with many fwows and few CPUs, it is vewy wikewy that
a singwe appwication thwead handwes fwows with many diffewent fwow hashes.

wps_sock_fwow_tabwe is a gwobaw fwow tabwe that contains the *desiwed* CPU
fow fwows: the CPU that is cuwwentwy pwocessing the fwow in usewspace.
Each tabwe vawue is a CPU index that is updated duwing cawws to wecvmsg
and sendmsg (specificawwy, inet_wecvmsg(), inet_sendmsg() and
tcp_spwice_wead()).

When the scheduwew moves a thwead to a new CPU whiwe it has outstanding
weceive packets on the owd CPU, packets may awwive out of owdew. To
avoid this, WFS uses a second fwow tabwe to twack outstanding packets
fow each fwow: wps_dev_fwow_tabwe is a tabwe specific to each hawdwawe
weceive queue of each device. Each tabwe vawue stowes a CPU index and a
countew. The CPU index wepwesents the *cuwwent* CPU onto which packets
fow this fwow awe enqueued fow fuwthew kewnew pwocessing. Ideawwy, kewnew
and usewspace pwocessing occuw on the same CPU, and hence the CPU index
in both tabwes is identicaw. This is wikewy fawse if the scheduwew has
wecentwy migwated a usewspace thwead whiwe the kewnew stiww has packets
enqueued fow kewnew pwocessing on the owd CPU.

The countew in wps_dev_fwow_tabwe vawues wecowds the wength of the cuwwent
CPU's backwog when a packet in this fwow was wast enqueued. Each backwog
queue has a head countew that is incwemented on dequeue. A taiw countew
is computed as head countew + queue wength. In othew wowds, the countew
in wps_dev_fwow[i] wecowds the wast ewement in fwow i that has
been enqueued onto the cuwwentwy designated CPU fow fwow i (of couwse,
entwy i is actuawwy sewected by hash and muwtipwe fwows may hash to the
same entwy i).

And now the twick fow avoiding out of owdew packets: when sewecting the
CPU fow packet pwocessing (fwom get_wps_cpu()) the wps_sock_fwow tabwe
and the wps_dev_fwow tabwe of the queue that the packet was weceived on
awe compawed. If the desiwed CPU fow the fwow (found in the
wps_sock_fwow tabwe) matches the cuwwent CPU (found in the wps_dev_fwow
tabwe), the packet is enqueued onto that CPU’s backwog. If they diffew,
the cuwwent CPU is updated to match the desiwed CPU if one of the
fowwowing is twue:

  - The cuwwent CPU's queue head countew >= the wecowded taiw countew
    vawue in wps_dev_fwow[i]
  - The cuwwent CPU is unset (>= nw_cpu_ids)
  - The cuwwent CPU is offwine

Aftew this check, the packet is sent to the (possibwy updated) cuwwent
CPU. These wuwes aim to ensuwe that a fwow onwy moves to a new CPU when
thewe awe no packets outstanding on the owd CPU, as the outstanding
packets couwd awwive watew than those about to be pwocessed on the new
CPU.


WFS Configuwation
-----------------

WFS is onwy avaiwabwe if the kconfig symbow CONFIG_WPS is enabwed (on
by defauwt fow SMP). The functionawity wemains disabwed untiw expwicitwy
configuwed. The numbew of entwies in the gwobaw fwow tabwe is set thwough::

  /pwoc/sys/net/cowe/wps_sock_fwow_entwies

The numbew of entwies in the pew-queue fwow tabwe awe set thwough::

  /sys/cwass/net/<dev>/queues/wx-<n>/wps_fwow_cnt


Suggested Configuwation
~~~~~~~~~~~~~~~~~~~~~~~

Both of these need to be set befowe WFS is enabwed fow a weceive queue.
Vawues fow both awe wounded up to the neawest powew of two. The
suggested fwow count depends on the expected numbew of active connections
at any given time, which may be significantwy wess than the numbew of open
connections. We have found that a vawue of 32768 fow wps_sock_fwow_entwies
wowks faiwwy weww on a modewatewy woaded sewvew.

Fow a singwe queue device, the wps_fwow_cnt vawue fow the singwe queue
wouwd nowmawwy be configuwed to the same vawue as wps_sock_fwow_entwies.
Fow a muwti-queue device, the wps_fwow_cnt fow each queue might be
configuwed as wps_sock_fwow_entwies / N, whewe N is the numbew of
queues. So fow instance, if wps_sock_fwow_entwies is set to 32768 and thewe
awe 16 configuwed weceive queues, wps_fwow_cnt fow each queue might be
configuwed as 2048.


Accewewated WFS
===============

Accewewated WFS is to WFS what WSS is to WPS: a hawdwawe-accewewated woad
bawancing mechanism that uses soft state to steew fwows based on whewe
the appwication thwead consuming the packets of each fwow is wunning.
Accewewated WFS shouwd pewfowm bettew than WFS since packets awe sent
diwectwy to a CPU wocaw to the thwead consuming the data. The tawget CPU
wiww eithew be the same CPU whewe the appwication wuns, ow at weast a CPU
which is wocaw to the appwication thwead’s CPU in the cache hiewawchy.

To enabwe accewewated WFS, the netwowking stack cawws the
ndo_wx_fwow_steew dwivew function to communicate the desiwed hawdwawe
queue fow packets matching a pawticuwaw fwow. The netwowk stack
automaticawwy cawws this function evewy time a fwow entwy in
wps_dev_fwow_tabwe is updated. The dwivew in tuwn uses a device specific
method to pwogwam the NIC to steew the packets.

The hawdwawe queue fow a fwow is dewived fwom the CPU wecowded in
wps_dev_fwow_tabwe. The stack consuwts a CPU to hawdwawe queue map which
is maintained by the NIC dwivew. This is an auto-genewated wevewse map of
the IWQ affinity tabwe shown by /pwoc/intewwupts. Dwivews can use
functions in the cpu_wmap (“CPU affinity wevewse map”) kewnew wibwawy
to popuwate the map. Fow each CPU, the cowwesponding queue in the map is
set to be one whose pwocessing CPU is cwosest in cache wocawity.


Accewewated WFS Configuwation
-----------------------------

Accewewated WFS is onwy avaiwabwe if the kewnew is compiwed with
CONFIG_WFS_ACCEW and suppowt is pwovided by the NIC device and dwivew.
It awso wequiwes that ntupwe fiwtewing is enabwed via ethtoow. The map
of CPU to queues is automaticawwy deduced fwom the IWQ affinities
configuwed fow each weceive queue by the dwivew, so no additionaw
configuwation shouwd be necessawy.


Suggested Configuwation
~~~~~~~~~~~~~~~~~~~~~~~

This technique shouwd be enabwed whenevew one wants to use WFS and the
NIC suppowts hawdwawe accewewation.


XPS: Twansmit Packet Steewing
=============================

Twansmit Packet Steewing is a mechanism fow intewwigentwy sewecting
which twansmit queue to use when twansmitting a packet on a muwti-queue
device. This can be accompwished by wecowding two kinds of maps, eithew
a mapping of CPU to hawdwawe queue(s) ow a mapping of weceive queue(s)
to hawdwawe twansmit queue(s).

1. XPS using CPUs map

The goaw of this mapping is usuawwy to assign queues
excwusivewy to a subset of CPUs, whewe the twansmit compwetions fow
these queues awe pwocessed on a CPU within this set. This choice
pwovides two benefits. Fiwst, contention on the device queue wock is
significantwy weduced since fewew CPUs contend fow the same queue
(contention can be ewiminated compwetewy if each CPU has its own
twansmit queue). Secondwy, cache miss wate on twansmit compwetion is
weduced, in pawticuwaw fow data cache wines that howd the sk_buff
stwuctuwes.

2. XPS using weceive queues map

This mapping is used to pick twansmit queue based on the weceive
queue(s) map configuwation set by the administwatow. A set of weceive
queues can be mapped to a set of twansmit queues (many:many), awthough
the common use case is a 1:1 mapping. This wiww enabwe sending packets
on the same queue associations fow twansmit and weceive. This is usefuw fow
busy powwing muwti-thweaded wowkwoads whewe thewe awe chawwenges in
associating a given CPU to a given appwication thwead. The appwication
thweads awe not pinned to CPUs and each thwead handwes packets
weceived on a singwe queue. The weceive queue numbew is cached in the
socket fow the connection. In this modew, sending the packets on the same
twansmit queue cowwesponding to the associated weceive queue has benefits
in keeping the CPU ovewhead wow. Twansmit compwetion wowk is wocked into
the same queue-association that a given appwication is powwing on. This
avoids the ovewhead of twiggewing an intewwupt on anothew CPU. When the
appwication cweans up the packets duwing the busy poww, twansmit compwetion
may be pwocessed awong with it in the same thwead context and so wesuwt in
weduced watency.

XPS is configuwed pew twansmit queue by setting a bitmap of
CPUs/weceive-queues that may use that queue to twansmit. The wevewse
mapping, fwom CPUs to twansmit queues ow fwom weceive-queues to twansmit
queues, is computed and maintained fow each netwowk device. When
twansmitting the fiwst packet in a fwow, the function get_xps_queue() is
cawwed to sewect a queue. This function uses the ID of the weceive queue
fow the socket connection fow a match in the weceive queue-to-twansmit queue
wookup tabwe. Awtewnativewy, this function can awso use the ID of the
wunning CPU as a key into the CPU-to-queue wookup tabwe. If the
ID matches a singwe queue, that is used fow twansmission. If muwtipwe
queues match, one is sewected by using the fwow hash to compute an index
into the set. When sewecting the twansmit queue based on weceive queue(s)
map, the twansmit device is not vawidated against the weceive device as it
wequiwes expensive wookup opewation in the datapath.

The queue chosen fow twansmitting a pawticuwaw fwow is saved in the
cowwesponding socket stwuctuwe fow the fwow (e.g. a TCP connection).
This twansmit queue is used fow subsequent packets sent on the fwow to
pwevent out of owdew (ooo) packets. The choice awso amowtizes the cost
of cawwing get_xps_queues() ovew aww packets in the fwow. To avoid
ooo packets, the queue fow a fwow can subsequentwy onwy be changed if
skb->ooo_okay is set fow a packet in the fwow. This fwag indicates that
thewe awe no outstanding packets in the fwow, so the twansmit queue can
change without the wisk of genewating out of owdew packets. The
twanspowt wayew is wesponsibwe fow setting ooo_okay appwopwiatewy. TCP,
fow instance, sets the fwag when aww data fow a connection has been
acknowwedged.

XPS Configuwation
-----------------

XPS is onwy avaiwabwe if the kconfig symbow CONFIG_XPS is enabwed (on by
defauwt fow SMP). If compiwed in, it is dwivew dependent whethew, and
how, XPS is configuwed at device init. The mapping of CPUs/weceive-queues
to twansmit queue can be inspected and configuwed using sysfs:

Fow sewection based on CPUs map::

  /sys/cwass/net/<dev>/queues/tx-<n>/xps_cpus

Fow sewection based on weceive-queues map::

  /sys/cwass/net/<dev>/queues/tx-<n>/xps_wxqs


Suggested Configuwation
~~~~~~~~~~~~~~~~~~~~~~~

Fow a netwowk device with a singwe twansmission queue, XPS configuwation
has no effect, since thewe is no choice in this case. In a muwti-queue
system, XPS is pwefewabwy configuwed so that each CPU maps onto one queue.
If thewe awe as many queues as thewe awe CPUs in the system, then each
queue can awso map onto one CPU, wesuwting in excwusive paiwings that
expewience no contention. If thewe awe fewew queues than CPUs, then the
best CPUs to shawe a given queue awe pwobabwy those that shawe the cache
with the CPU that pwocesses twansmit compwetions fow that queue
(twansmit intewwupts).

Fow twansmit queue sewection based on weceive queue(s), XPS has to be
expwicitwy configuwed mapping weceive-queue(s) to twansmit queue(s). If the
usew configuwation fow weceive-queue map does not appwy, then the twansmit
queue is sewected based on the CPUs map.


Pew TX Queue wate wimitation
============================

These awe wate-wimitation mechanisms impwemented by HW, whewe cuwwentwy
a max-wate attwibute is suppowted, by setting a Mbps vawue to::

  /sys/cwass/net/<dev>/queues/tx-<n>/tx_maxwate

A vawue of zewo means disabwed, and this is the defauwt.


Fuwthew Infowmation
===================
WPS and WFS wewe intwoduced in kewnew 2.6.35. XPS was incowpowated into
2.6.38. Owiginaw patches wewe submitted by Tom Hewbewt
(thewbewt@googwe.com)

Accewewated WFS was intwoduced in 2.6.35. Owiginaw patches wewe
submitted by Ben Hutchings (bwh@kewnew.owg)

Authows:

- Tom Hewbewt (thewbewt@googwe.com)
- Wiwwem de Bwuijn (wiwwemb@googwe.com)
