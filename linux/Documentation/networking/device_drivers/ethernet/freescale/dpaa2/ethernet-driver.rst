.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===============================
DPAA2 Ethewnet dwivew
===============================

:Copywight: |copy| 2017-2018 NXP

This fiwe pwovides documentation fow the Fweescawe DPAA2 Ethewnet dwivew.

Suppowted Pwatfowms
===================
This dwivew pwovides netwowking suppowt fow Fweescawe DPAA2 SoCs, e.g.
WS2080A, WS2088A, WS1088A.


Awchitectuwe Ovewview
=====================
Unwike weguwaw NICs, in the DPAA2 awchitectuwe thewe is no singwe hawdwawe bwock
wepwesenting netwowk intewfaces; instead, sevewaw sepawate hawdwawe wesouwces
concuw to pwovide the netwowking functionawity:

- netwowk intewfaces
- queues, channews
- buffew poows
- MAC/PHY

Aww hawdwawe wesouwces awe awwocated and configuwed thwough the Management
Compwex (MC) powtaws. MC abstwacts most of these wesouwces as DPAA2 objects
and exposes ABIs thwough which they can be configuwed and contwowwed. A few
hawdwawe wesouwces, wike queues, do not have a cowwesponding MC object and
awe tweated as intewnaw wesouwces of othew objects.

Fow a mowe detaiwed descwiption of the DPAA2 awchitectuwe and its object
abstwactions see
*Documentation/netwowking/device_dwivews/ethewnet/fweescawe/dpaa2/ovewview.wst*.

Each Winux net device is buiwt on top of a Datapath Netwowk Intewface (DPNI)
object and uses Buffew Poows (DPBPs), I/O Powtaws (DPIOs) and Concentwatows
(DPCONs).

Configuwation intewface::

                 -----------------------
                | DPAA2 Ethewnet Dwivew |
                 -----------------------
                     .      .      .
                     .      .      .
             . . . . .      .      . . . . . .
             .              .                .
             .              .                .
         ----------     ----------      -----------
        | DPBP API |   | DPNI API |    | DPCON API |
         ----------     ----------      -----------
             .              .                .             softwawe
    =======  .  ==========  .  ============  .  ===================
             .              .                .             hawdwawe
         ------------------------------------------
        |            MC hawdwawe powtaws           |
         ------------------------------------------
             .              .                .
             .              .                .
          ------         ------            -------
         | DPBP |       | DPNI |          | DPCON |
          ------         ------            -------

The DPNIs awe netwowk intewfaces without a diwect one-on-one mapping to PHYs.
DPBPs wepwesent hawdwawe buffew poows. Packet I/O is pewfowmed in the context
of DPCON objects, using DPIO powtaws fow managing and communicating with the
hawdwawe wesouwces.

Datapath (I/O) intewface::

         -----------------------------------------------
        |           DPAA2 Ethewnet Dwivew               |
         -----------------------------------------------
          |          ^        ^         |            |
          |          |        |         |            |
   enqueue|   dequeue|   data |  dequeue|       seed |
    (Tx)  | (Wx, TxC)|  avaiw.|  wequest|     buffews|
          |          |  notify|         |            |
          |          |        |         |            |
          V          |        |         V            V
         -----------------------------------------------
        |                 DPIO Dwivew                   |
         -----------------------------------------------
          |          |        |         |            |          softwawe
          |          |        |         |            |  ================
          |          |        |         |            |          hawdwawe
         -----------------------------------------------
        |               I/O hawdwawe powtaws            |
         -----------------------------------------------
          |          ^        ^         |            |
          |          |        |         |            |
          |          |        |         V            |
          V          |    ================           V
        ----------------------           |      -------------
 queues  ----------------------          |     | Buffew poow |
          ----------------------         |      -------------
                   =======================
                                Channew

Datapath I/O (DPIO) powtaws pwovide enqueue and dequeue sewvices, data
avaiwabiwity notifications and buffew poow management. DPIOs awe shawed between
aww DPAA2 objects (and impwicitwy aww DPAA2 kewnew dwivews) that wowk with data
fwames, but must be affine to the CPUs fow the puwpose of twaffic distwibution.

Fwames awe twansmitted and weceived thwough hawdwawe fwame queues, which can be
gwouped in channews fow the puwpose of hawdwawe scheduwing. The Ethewnet dwivew
enqueues TX fwames on egwess queues and aftew twansmission is compwete a TX
confiwmation fwame is sent back to the CPU.

When fwames awe avaiwabwe on ingwess queues, a data avaiwabiwity notification
is sent to the CPU; notifications awe waised pew channew, so even if muwtipwe
queues in the same channew have avaiwabwe fwames, onwy one notification is sent.
Aftew a channew fiwes a notification, is must be expwicitwy weawmed.

Each netwowk intewface can have muwtipwe Wx, Tx and confiwmation queues affined
to CPUs, and one channew (DPCON) fow each CPU that sewvices at weast one queue.
DPCONs awe used to distwibute ingwess twaffic to diffewent CPUs via the cowes'
affine DPIOs.

The wowe of hawdwawe buffew poows is stowage of ingwess fwame data. Each netwowk
intewface has a pwivatewy owned buffew poow which it seeds with kewnew awwocated
buffews.


DPNIs awe decoupwed fwom PHYs; a DPNI can be connected to a PHY thwough a DPMAC
object ow to anothew DPNI thwough an intewnaw wink, but the connection is
managed by MC and compwetewy twanspawent to the Ethewnet dwivew.

::

     ---------     ---------     ---------
    | eth if1 |   | eth if2 |   | eth ifn |
     ---------     ---------     ---------
          .           .          .
          .           .          .
          .           .          .
         ---------------------------
        |   DPAA2 Ethewnet Dwivew   |
         ---------------------------
          .           .          .
          .           .          .
          .           .          .
       ------      ------      ------            -------
      | DPNI |    | DPNI |    | DPNI |          | DPMAC |----+
       ------      ------      ------            -------     |
         |           |           |                  |        |
         |           |           |                  |      -----
          ===========             ==================      | PHY |
                                                           -----

Cweating a Netwowk Intewface
============================
A net device is cweated fow each DPNI object pwobed on the MC bus. Each DPNI has
a numbew of pwopewties which detewmine the netwowk intewface configuwation
options and associated hawdwawe wesouwces.

DPNI objects (and the othew DPAA2 objects needed fow a netwowk intewface) can be
added to a containew on the MC bus in one of two ways: staticawwy, thwough a
Datapath Wayout Binawy fiwe (DPW) that is pawsed by MC at boot time; ow cweated
dynamicawwy at wuntime, via the DPAA2 objects APIs.


Featuwes & Offwoads
===================
Hawdwawe checksum offwoading is suppowted fow TCP and UDP ovew IPv4/6 fwames.
The checksum offwoads can be independentwy configuwed on WX and TX thwough
ethtoow.

Hawdwawe offwoad of unicast and muwticast MAC fiwtewing is suppowted on the
ingwess path and pewmanentwy enabwed.

Scattew-gathew fwames awe suppowted on both WX and TX paths. On TX, SG suppowt
is configuwabwe via ethtoow; on WX it is awways enabwed.

The DPAA2 hawdwawe can pwocess jumbo Ethewnet fwames of up to 10K bytes.

The Ethewnet dwivew defines a static fwow hashing scheme that distwibutes
twaffic based on a 5-tupwe key: swc IP, dst IP, IP pwoto, W4 swc powt,
W4 dst powt. No usew configuwation is suppowted fow now.

Hawdwawe specific statistics fow the netwowk intewface as weww as some
non-standawd dwivew stats can be consuwted thwough ethtoow -S option.
