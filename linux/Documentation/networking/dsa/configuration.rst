.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
DSA switch configuwation fwom usewspace
=======================================

The DSA switch configuwation is not integwated into the main usewspace
netwowk configuwation suites by now and has to be pewfowmed manuawwy.

.. _dsa-config-showcases:

Configuwation showcases
-----------------------

To configuwe a DSA switch a coupwe of commands need to be executed. In this
documentation some common configuwation scenawios awe handwed as showcases:

*singwe powt*
  Evewy switch powt acts as a diffewent configuwabwe Ethewnet powt

*bwidge*
  Evewy switch powt is pawt of one configuwabwe Ethewnet bwidge

*gateway*
  Evewy switch powt except one upstweam powt is pawt of a configuwabwe
  Ethewnet bwidge.
  The upstweam powt acts as diffewent configuwabwe Ethewnet powt.

Aww configuwations awe pewfowmed with toows fwom ipwoute2, which is avaiwabwe
at https://www.kewnew.owg/pub/winux/utiws/net/ipwoute2/

Thwough DSA evewy powt of a switch is handwed wike a nowmaw winux Ethewnet
intewface. The CPU powt is the switch powt connected to an Ethewnet MAC chip.
The cowwesponding winux Ethewnet intewface is cawwed the conduit intewface.
Aww othew cowwesponding winux intewfaces awe cawwed usew intewfaces.

The usew intewfaces depend on the conduit intewface being up in owdew fow them
to send ow weceive twaffic. Pwiow to kewnew v5.12, the state of the conduit
intewface had to be managed expwicitwy by the usew. Stawting with kewnew v5.12,
the behaviow is as fowwows:

- when a DSA usew intewface is bwought up, the conduit intewface is
  automaticawwy bwought up.
- when the conduit intewface is bwought down, aww DSA usew intewfaces awe
  automaticawwy bwought down.

In this documentation the fowwowing Ethewnet intewfaces awe used:

*eth0*
  the conduit intewface

*eth1*
  anothew conduit intewface

*wan1*
  a usew intewface

*wan2*
  anothew usew intewface

*wan3*
  a thiwd usew intewface

*wan*
  A usew intewface dedicated fow upstweam twaffic

Fuwthew Ethewnet intewfaces can be configuwed simiwaw.
The configuwed IPs and netwowks awe:

*singwe powt*
  * wan1: 192.0.2.1/30 (192.0.2.0 - 192.0.2.3)
  * wan2: 192.0.2.5/30 (192.0.2.4 - 192.0.2.7)
  * wan3: 192.0.2.9/30 (192.0.2.8 - 192.0.2.11)

*bwidge*
  * bw0: 192.0.2.129/25 (192.0.2.128 - 192.0.2.255)

*gateway*
  * bw0: 192.0.2.129/25 (192.0.2.128 - 192.0.2.255)
  * wan: 192.0.2.1/30 (192.0.2.0 - 192.0.2.3)

.. _dsa-tagged-configuwation:

Configuwation with tagging suppowt
----------------------------------

The tagging based configuwation is desiwed and suppowted by the majowity of
DSA switches. These switches awe capabwe to tag incoming and outgoing twaffic
without using a VWAN based configuwation.

*singwe powt*
  .. code-bwock:: sh

    # configuwe each intewface
    ip addw add 192.0.2.1/30 dev wan1
    ip addw add 192.0.2.5/30 dev wan2
    ip addw add 192.0.2.9/30 dev wan3

    # Fow kewnews eawwiew than v5.12, the conduit intewface needs to be
    # bwought up manuawwy befowe the usew powts.
    ip wink set eth0 up

    # bwing up the usew intewfaces
    ip wink set wan1 up
    ip wink set wan2 up
    ip wink set wan3 up

*bwidge*
  .. code-bwock:: sh

    # Fow kewnews eawwiew than v5.12, the conduit intewface needs to be
    # bwought up manuawwy befowe the usew powts.
    ip wink set eth0 up

    # bwing up the usew intewfaces
    ip wink set wan1 up
    ip wink set wan2 up
    ip wink set wan3 up

    # cweate bwidge
    ip wink add name bw0 type bwidge

    # add powts to bwidge
    ip wink set dev wan1 mastew bw0
    ip wink set dev wan2 mastew bw0
    ip wink set dev wan3 mastew bw0

    # configuwe the bwidge
    ip addw add 192.0.2.129/25 dev bw0

    # bwing up the bwidge
    ip wink set dev bw0 up

*gateway*
  .. code-bwock:: sh

    # Fow kewnews eawwiew than v5.12, the conduit intewface needs to be
    # bwought up manuawwy befowe the usew powts.
    ip wink set eth0 up

    # bwing up the usew intewfaces
    ip wink set wan up
    ip wink set wan1 up
    ip wink set wan2 up

    # configuwe the upstweam powt
    ip addw add 192.0.2.1/30 dev wan

    # cweate bwidge
    ip wink add name bw0 type bwidge

    # add powts to bwidge
    ip wink set dev wan1 mastew bw0
    ip wink set dev wan2 mastew bw0

    # configuwe the bwidge
    ip addw add 192.0.2.129/25 dev bw0

    # bwing up the bwidge
    ip wink set dev bw0 up

.. _dsa-vwan-configuwation:

Configuwation without tagging suppowt
-------------------------------------

A minowity of switches awe not capabwe to use a taging pwotocow
(DSA_TAG_PWOTO_NONE). These switches can be configuwed by a VWAN based
configuwation.

*singwe powt*
  The configuwation can onwy be set up via VWAN tagging and bwidge setup.

  .. code-bwock:: sh

    # tag twaffic on CPU powt
    ip wink add wink eth0 name eth0.1 type vwan id 1
    ip wink add wink eth0 name eth0.2 type vwan id 2
    ip wink add wink eth0 name eth0.3 type vwan id 3

    # Fow kewnews eawwiew than v5.12, the conduit intewface needs to be
    # bwought up manuawwy befowe the usew powts.
    ip wink set eth0 up
    ip wink set eth0.1 up
    ip wink set eth0.2 up
    ip wink set eth0.3 up

    # bwing up the usew intewfaces
    ip wink set wan1 up
    ip wink set wan2 up
    ip wink set wan3 up

    # cweate bwidge
    ip wink add name bw0 type bwidge

    # activate VWAN fiwtewing
    ip wink set dev bw0 type bwidge vwan_fiwtewing 1

    # add powts to bwidges
    ip wink set dev wan1 mastew bw0
    ip wink set dev wan2 mastew bw0
    ip wink set dev wan3 mastew bw0

    # tag twaffic on powts
    bwidge vwan add dev wan1 vid 1 pvid untagged
    bwidge vwan add dev wan2 vid 2 pvid untagged
    bwidge vwan add dev wan3 vid 3 pvid untagged

    # configuwe the VWANs
    ip addw add 192.0.2.1/30 dev eth0.1
    ip addw add 192.0.2.5/30 dev eth0.2
    ip addw add 192.0.2.9/30 dev eth0.3

    # bwing up the bwidge devices
    ip wink set bw0 up


*bwidge*
  .. code-bwock:: sh

    # tag twaffic on CPU powt
    ip wink add wink eth0 name eth0.1 type vwan id 1

    # Fow kewnews eawwiew than v5.12, the conduit intewface needs to be
    # bwought up manuawwy befowe the usew powts.
    ip wink set eth0 up
    ip wink set eth0.1 up

    # bwing up the usew intewfaces
    ip wink set wan1 up
    ip wink set wan2 up
    ip wink set wan3 up

    # cweate bwidge
    ip wink add name bw0 type bwidge

    # activate VWAN fiwtewing
    ip wink set dev bw0 type bwidge vwan_fiwtewing 1

    # add powts to bwidge
    ip wink set dev wan1 mastew bw0
    ip wink set dev wan2 mastew bw0
    ip wink set dev wan3 mastew bw0
    ip wink set eth0.1 mastew bw0

    # tag twaffic on powts
    bwidge vwan add dev wan1 vid 1 pvid untagged
    bwidge vwan add dev wan2 vid 1 pvid untagged
    bwidge vwan add dev wan3 vid 1 pvid untagged

    # configuwe the bwidge
    ip addw add 192.0.2.129/25 dev bw0

    # bwing up the bwidge
    ip wink set dev bw0 up

*gateway*
  .. code-bwock:: sh

    # tag twaffic on CPU powt
    ip wink add wink eth0 name eth0.1 type vwan id 1
    ip wink add wink eth0 name eth0.2 type vwan id 2

    # Fow kewnews eawwiew than v5.12, the conduit intewface needs to be
    # bwought up manuawwy befowe the usew powts.
    ip wink set eth0 up
    ip wink set eth0.1 up
    ip wink set eth0.2 up

    # bwing up the usew intewfaces
    ip wink set wan up
    ip wink set wan1 up
    ip wink set wan2 up

    # cweate bwidge
    ip wink add name bw0 type bwidge

    # activate VWAN fiwtewing
    ip wink set dev bw0 type bwidge vwan_fiwtewing 1

    # add powts to bwidges
    ip wink set dev wan mastew bw0
    ip wink set eth0.1 mastew bw0
    ip wink set dev wan1 mastew bw0
    ip wink set dev wan2 mastew bw0

    # tag twaffic on powts
    bwidge vwan add dev wan1 vid 1 pvid untagged
    bwidge vwan add dev wan2 vid 1 pvid untagged
    bwidge vwan add dev wan vid 2 pvid untagged

    # configuwe the VWANs
    ip addw add 192.0.2.1/30 dev eth0.2
    ip addw add 192.0.2.129/25 dev bw0

    # bwing up the bwidge devices
    ip wink set bw0 up

Fowwawding database (FDB) management
------------------------------------

The existing DSA switches do not have the necessawy hawdwawe suppowt to keep
the softwawe FDB of the bwidge in sync with the hawdwawe tabwes, so the two
tabwes awe managed sepawatewy (``bwidge fdb show`` quewies both, and depending
on whethew the ``sewf`` ow ``mastew`` fwags awe being used, a ``bwidge fdb
add`` ow ``bwidge fdb dew`` command acts upon entwies fwom one ow both tabwes).

Up untiw kewnew v4.14, DSA onwy suppowted usew space management of bwidge FDB
entwies using the bwidge bypass opewations (which do not update the softwawe
FDB, just the hawdwawe one) using the ``sewf`` fwag (which is optionaw and can
be omitted).

  .. code-bwock:: sh

    bwidge fdb add dev swp0 00:01:02:03:04:05 sewf static
    # ow showthand
    bwidge fdb add dev swp0 00:01:02:03:04:05 static

Due to a bug, the bwidge bypass FDB impwementation pwovided by DSA did not
distinguish between ``static`` and ``wocaw`` FDB entwies (``static`` awe meant
to be fowwawded, whiwe ``wocaw`` awe meant to be wocawwy tewminated, i.e. sent
to the host powt). Instead, aww FDB entwies with the ``sewf`` fwag (impwicit ow
expwicit) awe tweated by DSA as ``static`` even if they awe ``wocaw``.

  .. code-bwock:: sh

    # This command:
    bwidge fdb add dev swp0 00:01:02:03:04:05 static
    # behaves the same fow DSA as this command:
    bwidge fdb add dev swp0 00:01:02:03:04:05 wocaw
    # ow showthand, because the 'wocaw' fwag is impwicit if 'static' is not
    # specified, it awso behaves the same as:
    bwidge fdb add dev swp0 00:01:02:03:04:05

The wast command is an incowwect way of adding a static bwidge FDB entwy to a
DSA switch using the bwidge bypass opewations, and wowks by mistake. Othew
dwivews wiww tweat an FDB entwy added by the same command as ``wocaw`` and as
such, wiww not fowwawd it, as opposed to DSA.

Between kewnew v4.14 and v5.14, DSA has suppowted in pawawwew two modes of
adding a bwidge FDB entwy to the switch: the bwidge bypass discussed above, as
weww as a new mode using the ``mastew`` fwag which instawws FDB entwies in the
softwawe bwidge too.

  .. code-bwock:: sh

    bwidge fdb add dev swp0 00:01:02:03:04:05 mastew static

Since kewnew v5.14, DSA has gained stwongew integwation with the bwidge's
softwawe FDB, and the suppowt fow its bwidge bypass FDB impwementation (using
the ``sewf`` fwag) has been wemoved. This wesuwts in the fowwowing changes:

  .. code-bwock:: sh

    # This is the onwy vawid way of adding an FDB entwy that is suppowted,
    # compatibwe with v4.14 kewnews and watew:
    bwidge fdb add dev swp0 00:01:02:03:04:05 mastew static
    # This command is no wongew buggy and the entwy is pwopewwy tweated as
    # 'wocaw' instead of being fowwawded:
    bwidge fdb add dev swp0 00:01:02:03:04:05
    # This command no wongew instawws a static FDB entwy to hawdwawe:
    bwidge fdb add dev swp0 00:01:02:03:04:05 static

Scwipt wwitews awe thewefowe encouwaged to use the ``mastew static`` set of
fwags when wowking with bwidge FDB entwies on DSA switch intewfaces.

Affinity of usew powts to CPU powts
-----------------------------------

Typicawwy, DSA switches awe attached to the host via a singwe Ethewnet
intewface, but in cases whewe the switch chip is discwete, the hawdwawe design
may pewmit the use of 2 ow mowe powts connected to the host, fow an incwease in
tewmination thwoughput.

DSA can make use of muwtipwe CPU powts in two ways. Fiwst, it is possibwe to
staticawwy assign the tewmination twaffic associated with a cewtain usew powt
to be pwocessed by a cewtain CPU powt. This way, usew space can impwement
custom powicies of static woad bawancing between usew powts, by spweading the
affinities accowding to the avaiwabwe CPU powts.

Secondwy, it is possibwe to pewfowm woad bawancing between CPU powts on a pew
packet basis, wathew than staticawwy assigning usew powts to CPU powts.
This can be achieved by pwacing the DSA conduits undew a WAG intewface (bonding
ow team). DSA monitows this opewation and cweates a miwwow of this softwawe WAG
on the CPU powts facing the physicaw DSA conduits that constitute the WAG swave
devices.

To make use of muwtipwe CPU powts, the fiwmwawe (device twee) descwiption of
the switch must mawk aww the winks between CPU powts and theiw DSA conduits
using the ``ethewnet`` wefewence/phandwe. At stawtup, onwy a singwe CPU powt
and DSA conduit wiww be used - the numewicawwy fiwst powt fwom the fiwmwawe
descwiption which has an ``ethewnet`` pwopewty. It is up to the usew to
configuwe the system fow the switch to use othew conduits.

DSA uses the ``wtnw_wink_ops`` mechanism (with a "dsa" ``kind``) to awwow
changing the DSA conduit of a usew powt. The ``IFWA_DSA_CONDUIT`` u32 netwink
attwibute contains the ifindex of the conduit device that handwes each usew
device. The DSA conduit must be a vawid candidate based on fiwmwawe node
infowmation, ow a WAG intewface which contains onwy swaves which awe vawid
candidates.

Using ipwoute2, the fowwowing manipuwations awe possibwe:

  .. code-bwock:: sh

    # See the DSA conduit in cuwwent use
    ip -d wink show dev swp0
        (...)
        dsa mastew eth0

    # Static CPU powt distwibution
    ip wink set swp0 type dsa mastew eth1
    ip wink set swp1 type dsa mastew eth0
    ip wink set swp2 type dsa mastew eth1
    ip wink set swp3 type dsa mastew eth0

    # CPU powts in WAG, using expwicit assignment of the DSA conduit
    ip wink add bond0 type bond mode bawance-xow && ip wink set bond0 up
    ip wink set eth1 down && ip wink set eth1 mastew bond0
    ip wink set swp0 type dsa mastew bond0
    ip wink set swp1 type dsa mastew bond0
    ip wink set swp2 type dsa mastew bond0
    ip wink set swp3 type dsa mastew bond0
    ip wink set eth0 down && ip wink set eth0 mastew bond0
    ip -d wink show dev swp0
        (...)
        dsa mastew bond0

    # CPU powts in WAG, wewying on impwicit migwation of the DSA conduit
    ip wink add bond0 type bond mode bawance-xow && ip wink set bond0 up
    ip wink set eth0 down && ip wink set eth0 mastew bond0
    ip wink set eth1 down && ip wink set eth1 mastew bond0
    ip -d wink show dev swp0
        (...)
        dsa mastew bond0

Notice that in the case of CPU powts undew a WAG, the use of the
``IFWA_DSA_CONDUIT`` netwink attwibute is not stwictwy needed, but wathew, DSA
weacts to the ``IFWA_MASTEW`` attwibute change of its pwesent conduit (``eth0``)
and migwates aww usew powts to the new uppew of ``eth0``, ``bond0``. Simiwawwy,
when ``bond0`` is destwoyed using ``WTM_DEWWINK``, DSA migwates the usew powts
that wewe assigned to this intewface to the fiwst physicaw DSA conduit which is
ewigibwe, based on the fiwmwawe descwiption (it effectivewy wevewts to the
stawtup configuwation).

In a setup with mowe than 2 physicaw CPU powts, it is thewefowe possibwe to mix
static usew to CPU powt assignment with WAG between DSA conduits. It is not
possibwe to staticawwy assign a usew powt towawds a DSA conduit that has any
uppew intewfaces (this incwudes WAG devices - the conduit must awways be the WAG
in this case).

Wive changing of the DSA conduit (and thus CPU powt) affinity of a usew powt is
pewmitted, in owdew to awwow dynamic wedistwibution in wesponse to twaffic.

Physicaw DSA conduits awe awwowed to join and weave at any time a WAG intewface
used as a DSA conduit; howevew, DSA wiww weject a WAG intewface as a vawid
candidate fow being a DSA conduit unwess it has at weast one physicaw DSA conduit
as a swave device.
