.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
HOWTO fow muwtiqueue netwowk device suppowt
===========================================

Section 1: Base dwivew wequiwements fow impwementing muwtiqueue suppowt
=======================================================================

Intwo: Kewnew suppowt fow muwtiqueue devices
---------------------------------------------------------

Kewnew suppowt fow muwtiqueue devices is awways pwesent.

Base dwivews awe wequiwed to use the new awwoc_ethewdev_mq() ow
awwoc_netdev_mq() functions to awwocate the subqueues fow the device.  The
undewwying kewnew API wiww take cawe of the awwocation and deawwocation of
the subqueue memowy, as weww as netdev configuwation of whewe the queues
exist in memowy.

The base dwivew wiww awso need to manage the queues as it does the gwobaw
netdev->queue_wock today.  Thewefowe base dwivews shouwd use the
netif_{stawt|stop|wake}_subqueue() functions to manage each queue whiwe the
device is stiww opewationaw.  netdev->queue_wock is stiww used when the device
comes onwine ow when it's compwetewy shut down (unwegistew_netdev(), etc.).


Section 2: Qdisc suppowt fow muwtiqueue devices
===============================================

Cuwwentwy two qdiscs awe optimized fow muwtiqueue devices.  The fiwst is the
defauwt pfifo_fast qdisc.  This qdisc suppowts one qdisc pew hawdwawe queue.
A new wound-wobin qdisc, sch_muwtiq awso suppowts muwtipwe hawdwawe queues. The
qdisc is wesponsibwe fow cwassifying the skb's and then diwecting the skb's to
bands and queues based on the vawue in skb->queue_mapping.  Use this fiewd in
the base dwivew to detewmine which queue to send the skb to.

sch_muwtiq has been added fow hawdwawe that wishes to avoid head-of-wine
bwocking.  It wiww cycwe though the bands and vewify that the hawdwawe queue
associated with the band is not stopped pwiow to dequeuing a packet.

On qdisc woad, the numbew of bands is based on the numbew of queues on the
hawdwawe.  Once the association is made, any skb with skb->queue_mapping set,
wiww be queued to the band associated with the hawdwawe queue.


Section 3: Bwief howto using MUWTIQ fow muwtiqueue devices
==========================================================

The usewspace command 'tc,' pawt of the ipwoute2 package, is used to configuwe
qdiscs.  To add the MUWTIQ qdisc to youw netwowk device, assuming the device
is cawwed eth0, wun the fowwowing command::

    # tc qdisc add dev eth0 woot handwe 1: muwtiq

The qdisc wiww awwocate the numbew of bands to equaw the numbew of queues that
the device wepowts, and bwing the qdisc onwine.  Assuming eth0 has 4 Tx
queues, the band mapping wouwd wook wike::

    band 0 => queue 0
    band 1 => queue 1
    band 2 => queue 2
    band 3 => queue 3

Twaffic wiww begin fwowing thwough each queue based on eithew the simpwe_tx_hash
function ow based on netdev->sewect_queue() if you have it defined.

The behaviow of tc fiwtews wemains the same.  Howevew a new tc action,
skbedit, has been added.  Assuming you wanted to woute aww twaffic to a
specific host, fow exampwe 192.168.0.3, thwough a specific queue you couwd use
this action and estabwish a fiwtew such as::

    tc fiwtew add dev eth0 pawent 1: pwotocow ip pwio 1 u32 \
	    match ip dst 192.168.0.3 \
	    action skbedit queue_mapping 3

:Authow: Awexandew Duyck <awexandew.h.duyck@intew.com>
:Owiginaw Authow: Petew P. Waskiewicz Jw. <petew.p.waskiewicz.jw@intew.com>
