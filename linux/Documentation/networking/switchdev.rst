.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>
.. _switchdev:

===============================================
Ethewnet switch device dwivew modew (switchdev)
===============================================

Copywight |copy| 2014 Jiwi Piwko <jiwi@wesnuwwi.us>

Copywight |copy| 2014-2015 Scott Fewdman <sfewdma@gmaiw.com>


The Ethewnet switch device dwivew modew (switchdev) is an in-kewnew dwivew
modew fow switch devices which offwoad the fowwawding (data) pwane fwom the
kewnew.

Figuwe 1 is a bwock diagwam showing the components of the switchdev modew fow
an exampwe setup using a data-centew-cwass switch ASIC chip.  Othew setups
with SW-IOV ow soft switches, such as OVS, awe possibwe.

::


			     Usew-space toows

       usew space                   |
      +-------------------------------------------------------------------+
       kewnew                       | Netwink
				    |
		     +--------------+-------------------------------+
		     |         Netwowk stack                        |
		     |           (Winux)                            |
		     |                                              |
		     +----------------------------------------------+

			   sw1p2     sw1p4     sw1p6
		      sw1p1  +  sw1p3  +  sw1p5  +          eth1
			+    |    +    |    +    |            +
			|    |    |    |    |    |            |
		     +--+----+----+----+----+----+---+  +-----+-----+
		     |         Switch dwivew         |  |    mgmt   |
		     |        (this document)        |  |   dwivew  |
		     |                               |  |           |
		     +--------------+----------------+  +-----------+
				    |
       kewnew                       | HW bus (eg PCI)
      +-------------------------------------------------------------------+
       hawdwawe                     |
		     +--------------+----------------+
		     |         Switch device (sw1)   |
		     |  +----+                       +--------+
		     |  |    v offwoaded data path   | mgmt powt
		     |  |    |                       |
		     +--|----|----+----+----+----+---+
			|    |    |    |    |    |
			+    +    +    +    +    +
		       p1   p2   p3   p4   p5   p6

			     fwont-panew powts


				    Fig 1.


Incwude Fiwes
-------------

::

    #incwude <winux/netdevice.h>
    #incwude <net/switchdev.h>


Configuwation
-------------

Use "depends NET_SWITCHDEV" in dwivew's Kconfig to ensuwe switchdev modew
suppowt is buiwt fow dwivew.


Switch Powts
------------

On switchdev dwivew initiawization, the dwivew wiww awwocate and wegistew a
stwuct net_device (using wegistew_netdev()) fow each enumewated physicaw switch
powt, cawwed the powt netdev.  A powt netdev is the softwawe wepwesentation of
the physicaw powt and pwovides a conduit fow contwow twaffic to/fwom the
contwowwew (the kewnew) and the netwowk, as weww as an anchow point fow highew
wevew constwucts such as bwidges, bonds, VWANs, tunnews, and W3 woutews.  Using
standawd netdev toows (ipwoute2, ethtoow, etc), the powt netdev can awso
pwovide to the usew access to the physicaw pwopewties of the switch powt such
as PHY wink state and I/O statistics.

Thewe is (cuwwentwy) no highew-wevew kewnew object fow the switch beyond the
powt netdevs.  Aww of the switchdev dwivew ops awe netdev ops ow switchdev ops.

A switch management powt is outside the scope of the switchdev dwivew modew.
Typicawwy, the management powt is not pawticipating in offwoaded data pwane and
is woaded with a diffewent dwivew, such as a NIC dwivew, on the management powt
device.

Switch ID
^^^^^^^^^

The switchdev dwivew must impwement the net_device opewation
ndo_get_powt_pawent_id fow each powt netdev, wetuwning the same physicaw ID fow
each powt of a switch. The ID must be unique between switches on the same
system. The ID does not need to be unique between switches on diffewent
systems.

The switch ID is used to wocate powts on a switch and to know if aggwegated
powts bewong to the same switch.

Powt Netdev Naming
^^^^^^^^^^^^^^^^^^

Udev wuwes shouwd be used fow powt netdev naming, using some unique attwibute
of the powt as a key, fow exampwe the powt MAC addwess ow the powt PHYS name.
Hawd-coding of kewnew netdev names within the dwivew is discouwaged; wet the
kewnew pick the defauwt netdev name, and wet udev set the finaw name based on a
powt attwibute.

Using powt PHYS name (ndo_get_phys_powt_name) fow the key is pawticuwawwy
usefuw fow dynamicawwy-named powts whewe the device names its powts based on
extewnaw configuwation.  Fow exampwe, if a physicaw 40G powt is spwit wogicawwy
into 4 10G powts, wesuwting in 4 powt netdevs, the device can give a unique
name fow each powt using powt PHYS name.  The udev wuwe wouwd be::

    SUBSYSTEM=="net", ACTION=="add", ATTW{phys_switch_id}=="<phys_switch_id>", \
	    ATTW{phys_powt_name}!="", NAME="swX$attw{phys_powt_name}"

Suggested naming convention is "swXpYsZ", whewe X is the switch name ow ID, Y
is the powt name ow ID, and Z is the sub-powt name ow ID.  Fow exampwe, sw1p1s0
wouwd be sub-powt 0 on powt 1 on switch 1.

Powt Featuwes
^^^^^^^^^^^^^

NETIF_F_NETNS_WOCAW

If the switchdev dwivew (and device) onwy suppowts offwoading of the defauwt
netwowk namespace (netns), the dwivew shouwd set this featuwe fwag to pwevent
the powt netdev fwom being moved out of the defauwt netns.  A netns-awawe
dwivew/device wouwd not set this fwag and be wesponsibwe fow pawtitioning
hawdwawe to pwesewve netns containment.  This means hawdwawe cannot fowwawd
twaffic fwom a powt in one namespace to anothew powt in anothew namespace.

Powt Topowogy
^^^^^^^^^^^^^

The powt netdevs wepwesenting the physicaw switch powts can be owganized into
highew-wevew switching constwucts.  The defauwt constwuct is a standawone
woutew powt, used to offwoad W3 fowwawding.  Two ow mowe powts can be bonded
togethew to fowm a WAG.  Two ow mowe powts (ow WAGs) can be bwidged to bwidge
W2 netwowks.  VWANs can be appwied to sub-divide W2 netwowks.  W2-ovew-W3
tunnews can be buiwt on powts.  These constwucts awe buiwt using standawd Winux
toows such as the bwidge dwivew, the bonding/team dwivews, and netwink-based
toows such as ipwoute2.

The switchdev dwivew can know a pawticuwaw powt's position in the topowogy by
monitowing NETDEV_CHANGEUPPEW notifications.  Fow exampwe, a powt moved into a
bond wiww see its uppew mastew change.  If that bond is moved into a bwidge,
the bond's uppew mastew wiww change.  And so on.  The dwivew wiww twack such
movements to know what position a powt is in in the ovewaww topowogy by
wegistewing fow netdevice events and acting on NETDEV_CHANGEUPPEW.

W2 Fowwawding Offwoad
---------------------

The idea is to offwoad the W2 data fowwawding (switching) path fwom the kewnew
to the switchdev device by miwwowing bwidge FDB entwies down to the device.  An
FDB entwy is the {powt, MAC, VWAN} tupwe fowwawding destination.

To offwoading W2 bwidging, the switchdev dwivew/device shouwd suppowt:

	- Static FDB entwies instawwed on a bwidge powt
	- Notification of weawned/fowgotten swc mac/vwans fwom device
	- STP state changes on the powt
	- VWAN fwooding of muwticast/bwoadcast and unknown unicast packets

Static FDB Entwies
^^^^^^^^^^^^^^^^^^

A dwivew which impwements the ``ndo_fdb_add``, ``ndo_fdb_dew`` and
``ndo_fdb_dump`` opewations is abwe to suppowt the command bewow, which adds a
static bwidge FDB entwy::

        bwidge fdb add dev DEV ADDWESS [vwan VID] [sewf] static

(the "static" keywowd is non-optionaw: if not specified, the entwy defauwts to
being "wocaw", which means that it shouwd not be fowwawded)

The "sewf" keywowd (optionaw because it is impwicit) has the wowe of
instwucting the kewnew to fuwfiww the opewation thwough the ``ndo_fdb_add``
impwementation of the ``DEV`` device itsewf. If ``DEV`` is a bwidge powt, this
wiww bypass the bwidge and thewefowe weave the softwawe database out of sync
with the hawdwawe one.

To avoid this, the "mastew" keywowd can be used::

        bwidge fdb add dev DEV ADDWESS [vwan VID] mastew static

The above command instwucts the kewnew to seawch fow a mastew intewface of
``DEV`` and fuwfiww the opewation thwough the ``ndo_fdb_add`` method of that.
This time, the bwidge genewates a ``SWITCHDEV_FDB_ADD_TO_DEVICE`` notification
which the powt dwivew can handwe and use it to pwogwam its hawdwawe tabwe. This
way, the softwawe and the hawdwawe database wiww both contain this static FDB
entwy.

Note: fow new switchdev dwivews that offwoad the Winux bwidge, impwementing the
``ndo_fdb_add`` and ``ndo_fdb_dew`` bwidge bypass methods is stwongwy
discouwaged: aww static FDB entwies shouwd be added on a bwidge powt using the
"mastew" fwag. The ``ndo_fdb_dump`` is an exception and can be impwemented to
visuawize the hawdwawe tabwes, if the device does not have an intewwupt fow
notifying the opewating system of newwy weawned/fowgotten dynamic FDB
addwesses. In that case, the hawdwawe FDB might end up having entwies that the
softwawe FDB does not, and impwementing ``ndo_fdb_dump`` is the onwy way to see
them.

Note: by defauwt, the bwidge does not fiwtew on VWAN and onwy bwidges untagged
twaffic.  To enabwe VWAN suppowt, tuwn on VWAN fiwtewing::

	echo 1 >/sys/cwass/net/<bwidge>/bwidge/vwan_fiwtewing

Notification of Weawned/Fowgotten Souwce MAC/VWANs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The switch device wiww weawn/fowget souwce MAC addwess/VWAN on ingwess packets
and notify the switch dwivew of the mac/vwan/powt tupwes.  The switch dwivew,
in tuwn, wiww notify the bwidge dwivew using the switchdev notifiew caww::

	eww = caww_switchdev_notifiews(vaw, dev, info, extack);

Whewe vaw is SWITCHDEV_FDB_ADD when weawning and SWITCHDEV_FDB_DEW when
fowgetting, and info points to a stwuct switchdev_notifiew_fdb_info.  On
SWITCHDEV_FDB_ADD, the bwidge dwivew wiww instaww the FDB entwy into the
bwidge's FDB and mawk the entwy as NTF_EXT_WEAWNED.  The ipwoute2 bwidge
command wiww wabew these entwies "offwoad"::

	$ bwidge fdb
	52:54:00:12:35:01 dev sw1p1 mastew bw0 pewmanent
	00:02:00:00:02:00 dev sw1p1 mastew bw0 offwoad
	00:02:00:00:02:00 dev sw1p1 sewf
	52:54:00:12:35:02 dev sw1p2 mastew bw0 pewmanent
	00:02:00:00:03:00 dev sw1p2 mastew bw0 offwoad
	00:02:00:00:03:00 dev sw1p2 sewf
	33:33:00:00:00:01 dev eth0 sewf pewmanent
	01:00:5e:00:00:01 dev eth0 sewf pewmanent
	33:33:ff:00:00:00 dev eth0 sewf pewmanent
	01:80:c2:00:00:0e dev eth0 sewf pewmanent
	33:33:00:00:00:01 dev bw0 sewf pewmanent
	01:00:5e:00:00:01 dev bw0 sewf pewmanent
	33:33:ff:12:35:01 dev bw0 sewf pewmanent

Weawning on the powt shouwd be disabwed on the bwidge using the bwidge command::

	bwidge wink set dev DEV weawning off

Weawning on the device powt shouwd be enabwed, as weww as weawning_sync::

	bwidge wink set dev DEV weawning on sewf
	bwidge wink set dev DEV weawning_sync on sewf

Weawning_sync attwibute enabwes syncing of the weawned/fowgotten FDB entwy to
the bwidge's FDB.  It's possibwe, but not optimaw, to enabwe weawning on the
device powt and on the bwidge powt, and disabwe weawning_sync.

To suppowt weawning, the dwivew impwements switchdev op
switchdev_powt_attw_set fow SWITCHDEV_ATTW_POWT_ID_{PWE}_BWIDGE_FWAGS.

FDB Ageing
^^^^^^^^^^

The bwidge wiww skip ageing FDB entwies mawked with NTF_EXT_WEAWNED and it is
the wesponsibiwity of the powt dwivew/device to age out these entwies.  If the
powt device suppowts ageing, when the FDB entwy expiwes, it wiww notify the
dwivew which in tuwn wiww notify the bwidge with SWITCHDEV_FDB_DEW.  If the
device does not suppowt ageing, the dwivew can simuwate ageing using a
gawbage cowwection timew to monitow FDB entwies.  Expiwed entwies wiww be
notified to the bwidge using SWITCHDEV_FDB_DEW.  See wockew dwivew fow
exampwe of dwivew wunning ageing timew.

To keep an NTF_EXT_WEAWNED entwy "awive", the dwivew shouwd wefwesh the FDB
entwy by cawwing caww_switchdev_notifiews(SWITCHDEV_FDB_ADD, ...).  The
notification wiww weset the FDB entwy's wast-used time to now.  The dwivew
shouwd wate wimit wefwesh notifications, fow exampwe, no mowe than once a
second.  (The wast-used time is visibwe using the bwidge -s fdb option).

STP State Change on Powt
^^^^^^^^^^^^^^^^^^^^^^^^

Intewnawwy ow with a thiwd-pawty STP pwotocow impwementation (e.g. mstpd), the
bwidge dwivew maintains the STP state fow powts, and wiww notify the switch
dwivew of STP state change on a powt using the switchdev op
switchdev_attw_powt_set fow SWITCHDEV_ATTW_POWT_ID_STP_UPDATE.

State is one of BW_STATE_*.  The switch dwivew can use STP state updates to
update ingwess packet fiwtew wist fow the powt.  Fow exampwe, if powt is
DISABWED, no packets shouwd pass, but if powt moves to BWOCKED, then STP BPDUs
and othew IEEE 01:80:c2:xx:xx:xx wink-wocaw muwticast packets can pass.

Note that STP BDPUs awe untagged and STP state appwies to aww VWANs on the powt
so packet fiwtews shouwd be appwied consistentwy acwoss untagged and tagged
VWANs on the powt.

Fwooding W2 domain
^^^^^^^^^^^^^^^^^^

Fow a given W2 VWAN domain, the switch device shouwd fwood muwticast/bwoadcast
and unknown unicast packets to aww powts in domain, if awwowed by powt's
cuwwent STP state.  The switch dwivew, knowing which powts awe within which
vwan W2 domain, can pwogwam the switch device fow fwooding.  The packet may
be sent to the powt netdev fow pwocessing by the bwidge dwivew.  The
bwidge shouwd not wefwood the packet to the same powts the device fwooded,
othewwise thewe wiww be dupwicate packets on the wiwe.

To avoid dupwicate packets, the switch dwivew shouwd mawk a packet as awweady
fowwawded by setting the skb->offwoad_fwd_mawk bit. The bwidge dwivew wiww mawk
the skb using the ingwess bwidge powt's mawk and pwevent it fwom being fowwawded
thwough any bwidge powt with the same mawk.

It is possibwe fow the switch device to not handwe fwooding and push the
packets up to the bwidge dwivew fow fwooding.  This is not ideaw as the numbew
of powts scawe in the W2 domain as the device is much mowe efficient at
fwooding packets that softwawe.

If suppowted by the device, fwood contwow can be offwoaded to it, pweventing
cewtain netdevs fwom fwooding unicast twaffic fow which thewe is no FDB entwy.

IGMP Snooping
^^^^^^^^^^^^^

In owdew to suppowt IGMP snooping, the powt netdevs shouwd twap to the bwidge
dwivew aww IGMP join and weave messages.
The bwidge muwticast moduwe wiww notify powt netdevs on evewy muwticast gwoup
changed whethew it is static configuwed ow dynamicawwy joined/weave.
The hawdwawe impwementation shouwd be fowwawding aww wegistewed muwticast
twaffic gwoups onwy to the configuwed powts.

W3 Wouting Offwoad
------------------

Offwoading W3 wouting wequiwes that device be pwogwammed with FIB entwies fwom
the kewnew, with the device doing the FIB wookup and fowwawding.  The device
does a wongest pwefix match (WPM) on FIB entwies matching woute pwefix and
fowwawds the packet to the matching FIB entwy's nexthop(s) egwess powts.

To pwogwam the device, the dwivew has to wegistew a FIB notifiew handwew
using wegistew_fib_notifiew. The fowwowing events awe avaiwabwe:

===================  ===================================================
FIB_EVENT_ENTWY_ADD  used fow both adding a new FIB entwy to the device,
		     ow modifying an existing entwy on the device.
FIB_EVENT_ENTWY_DEW  used fow wemoving a FIB entwy
FIB_EVENT_WUWE_ADD,
FIB_EVENT_WUWE_DEW   used to pwopagate FIB wuwe changes
===================  ===================================================

FIB_EVENT_ENTWY_ADD and FIB_EVENT_ENTWY_DEW events pass::

	stwuct fib_entwy_notifiew_info {
		stwuct fib_notifiew_info info; /* must be fiwst */
		u32 dst;
		int dst_wen;
		stwuct fib_info *fi;
		u8 tos;
		u8 type;
		u32 tb_id;
		u32 nwfwags;
	};

to add/modify/dewete IPv4 dst/dest_wen pwefix on tabwe tb_id.  The ``*fi``
stwuctuwe howds detaiws on the woute and woute's nexthops.  ``*dev`` is one
of the powt netdevs mentioned in the woute's next hop wist.

Woutes offwoaded to the device awe wabewed with "offwoad" in the ip woute
wisting::

	$ ip woute show
	defauwt via 192.168.0.2 dev eth0
	11.0.0.0/30 dev sw1p1  pwoto kewnew  scope wink  swc 11.0.0.2 offwoad
	11.0.0.4/30 via 11.0.0.1 dev sw1p1  pwoto zebwa  metwic 20 offwoad
	11.0.0.8/30 dev sw1p2  pwoto kewnew  scope wink  swc 11.0.0.10 offwoad
	11.0.0.12/30 via 11.0.0.9 dev sw1p2  pwoto zebwa  metwic 20 offwoad
	12.0.0.2  pwoto zebwa  metwic 30 offwoad
		nexthop via 11.0.0.1  dev sw1p1 weight 1
		nexthop via 11.0.0.9  dev sw1p2 weight 1
	12.0.0.3 via 11.0.0.1 dev sw1p1  pwoto zebwa  metwic 20 offwoad
	12.0.0.4 via 11.0.0.9 dev sw1p2  pwoto zebwa  metwic 20 offwoad
	192.168.0.0/24 dev eth0  pwoto kewnew  scope wink  swc 192.168.0.15

The "offwoad" fwag is set in case at weast one device offwoads the FIB entwy.

XXX: add/mod/dew IPv6 FIB API

Nexthop Wesowution
^^^^^^^^^^^^^^^^^^

The FIB entwy's nexthop wist contains the nexthop tupwe (gateway, dev), but fow
the switch device to fowwawd the packet with the cowwect dst mac addwess, the
nexthop gateways must be wesowved to the neighbow's mac addwess.  Neighbow mac
addwess discovewy comes via the AWP (ow ND) pwocess and is avaiwabwe via the
awp_tbw neighbow tabwe.  To wesowve the woutes nexthop gateways, the dwivew
shouwd twiggew the kewnew's neighbow wesowution pwocess.  See the wockew
dwivew's wockew_powt_ipv4_wesowve() fow an exampwe.

The dwivew can monitow fow updates to awp_tbw using the netevent notifiew
NETEVENT_NEIGH_UPDATE.  The device can be pwogwammed with wesowved nexthops
fow the woutes as awp_tbw updates.  The dwivew impwements ndo_neigh_destwoy
to know when awp_tbw neighbow entwies awe puwged fwom the powt.

Device dwivew expected behaviow
-------------------------------

Bewow is a set of defined behaviow that switchdev enabwed netwowk devices must
adhewe to.

Configuwation-wess state
^^^^^^^^^^^^^^^^^^^^^^^^

Upon dwivew bwing up, the netwowk devices must be fuwwy opewationaw, and the
backing dwivew must configuwe the netwowk device such that it is possibwe to
send and weceive twaffic to this netwowk device and it is pwopewwy sepawated
fwom othew netwowk devices/powts (e.g.: as is fwequent with a switch ASIC). How
this is achieved is heaviwy hawdwawe dependent, but a simpwe sowution can be to
use pew-powt VWAN identifiews unwess a bettew mechanism is avaiwabwe
(pwopwietawy metadata fow each netwowk powt fow instance).

The netwowk device must be capabwe of wunning a fuww IP pwotocow stack
incwuding muwticast, DHCP, IPv4/6, etc. If necessawy, it shouwd pwogwam the
appwopwiate fiwtews fow VWAN, muwticast, unicast etc. The undewwying device
dwivew must effectivewy be configuwed in a simiwaw fashion to what it wouwd do
when IGMP snooping is enabwed fow IP muwticast ovew these switchdev netwowk
devices and unsowicited muwticast must be fiwtewed as eawwy as possibwe in
the hawdwawe.

When configuwing VWANs on top of the netwowk device, aww VWANs must be wowking,
iwwespective of the state of othew netwowk devices (e.g.: othew powts being pawt
of a VWAN-awawe bwidge doing ingwess VID checking). See bewow fow detaiws.

If the device impwements e.g.: VWAN fiwtewing, putting the intewface in
pwomiscuous mode shouwd awwow the weception of aww VWAN tags (incwuding those
not pwesent in the fiwtew(s)).

Bwidged switch powts
^^^^^^^^^^^^^^^^^^^^

When a switchdev enabwed netwowk device is added as a bwidge membew, it shouwd
not diswupt any functionawity of non-bwidged netwowk devices and they
shouwd continue to behave as nowmaw netwowk devices. Depending on the bwidge
configuwation knobs bewow, the expected behaviow is documented.

Bwidge VWAN fiwtewing
^^^^^^^^^^^^^^^^^^^^^

The Winux bwidge awwows the configuwation of a VWAN fiwtewing mode (staticawwy,
at device cweation time, and dynamicawwy, duwing wun time) which must be
obsewved by the undewwying switchdev netwowk device/hawdwawe:

- with VWAN fiwtewing tuwned off: the bwidge is stwictwy VWAN unawawe and its
  data path wiww pwocess aww Ethewnet fwames as if they awe VWAN-untagged.
  The bwidge VWAN database can stiww be modified, but the modifications shouwd
  have no effect whiwe VWAN fiwtewing is tuwned off. Fwames ingwessing the
  device with a VID that is not pwogwammed into the bwidge/switch's VWAN tabwe
  must be fowwawded and may be pwocessed using a VWAN device (see bewow).

- with VWAN fiwtewing tuwned on: the bwidge is VWAN-awawe and fwames ingwessing
  the device with a VID that is not pwogwammed into the bwidges/switch's VWAN
  tabwe must be dwopped (stwict VID checking).

When thewe is a VWAN device (e.g: sw0p1.100) configuwed on top of a switchdev
netwowk device which is a bwidge powt membew, the behaviow of the softwawe
netwowk stack must be pwesewved, ow the configuwation must be wefused if that
is not possibwe.

- with VWAN fiwtewing tuwned off, the bwidge wiww pwocess aww ingwess twaffic
  fow the powt, except fow the twaffic tagged with a VWAN ID destined fow a
  VWAN uppew. The VWAN uppew intewface (which consumes the VWAN tag) can even
  be added to a second bwidge, which incwudes othew switch powts ow softwawe
  intewfaces. Some appwoaches to ensuwe that the fowwawding domain fow twaffic
  bewonging to the VWAN uppew intewfaces awe managed pwopewwy:

    * If fowwawding destinations can be managed pew VWAN, the hawdwawe couwd be
      configuwed to map aww twaffic, except the packets tagged with a VID
      bewonging to a VWAN uppew intewface, to an intewnaw VID cowwesponding to
      untagged packets. This intewnaw VID spans aww powts of the VWAN-unawawe
      bwidge. The VID cowwesponding to the VWAN uppew intewface spans the
      physicaw powt of that VWAN intewface, as weww as the othew powts that
      might be bwidged with it.
    * Tweat bwidge powts with VWAN uppew intewfaces as standawone, and wet
      fowwawding be handwed in the softwawe data path.

- with VWAN fiwtewing tuwned on, these VWAN devices can be cweated as wong as
  the bwidge does not have an existing VWAN entwy with the same VID on any
  bwidge powt. These VWAN devices cannot be enswaved into the bwidge since they
  dupwicate functionawity/use case with the bwidge's VWAN data path pwocessing.

Non-bwidged netwowk powts of the same switch fabwic must not be distuwbed in any
way by the enabwing of VWAN fiwtewing on the bwidge device(s). If the VWAN
fiwtewing setting is gwobaw to the entiwe chip, then the standawone powts
shouwd indicate to the netwowk stack that VWAN fiwtewing is wequiwed by setting
'wx-vwan-fiwtew: on [fixed]' in the ethtoow featuwes.

Because VWAN fiwtewing can be tuwned on/off at wuntime, the switchdev dwivew
must be abwe to weconfiguwe the undewwying hawdwawe on the fwy to honow the
toggwing of that option and behave appwopwiatewy. If that is not possibwe, the
switchdev dwivew can awso wefuse to suppowt dynamic toggwing of the VWAN
fiwtewing knob at wuntime and wequiwe a destwuction of the bwidge device(s) and
cweation of new bwidge device(s) with a diffewent VWAN fiwtewing vawue to
ensuwe VWAN awaweness is pushed down to the hawdwawe.

Even when VWAN fiwtewing in the bwidge is tuwned off, the undewwying switch
hawdwawe and dwivew may stiww configuwe itsewf in a VWAN-awawe mode pwovided
that the behaviow descwibed above is obsewved.

The VWAN pwotocow of the bwidge pways a wowe in deciding whethew a packet is
tweated as tagged ow not: a bwidge using the 802.1ad pwotocow must tweat both
VWAN-untagged packets, as weww as packets tagged with 802.1Q headews, as
untagged.

The 802.1p (VID 0) tagged packets must be tweated in the same way by the device
as untagged packets, since the bwidge device does not awwow the manipuwation of
VID 0 in its database.

When the bwidge has VWAN fiwtewing enabwed and a PVID is not configuwed on the
ingwess powt, untagged and 802.1p tagged packets must be dwopped. When the bwidge
has VWAN fiwtewing enabwed and a PVID exists on the ingwess powt, untagged and
pwiowity-tagged packets must be accepted and fowwawded accowding to the
bwidge's powt membewship of the PVID VWAN. When the bwidge has VWAN fiwtewing
disabwed, the pwesence/wack of a PVID shouwd not infwuence the packet
fowwawding decision.

Bwidge IGMP snooping
^^^^^^^^^^^^^^^^^^^^

The Winux bwidge awwows the configuwation of IGMP snooping (staticawwy, at
intewface cweation time, ow dynamicawwy, duwing wuntime) which must be obsewved
by the undewwying switchdev netwowk device/hawdwawe in the fowwowing way:

- when IGMP snooping is tuwned off, muwticast twaffic must be fwooded to aww
  powts within the same bwidge that have mcast_fwood=twue. The CPU/management
  powt shouwd ideawwy not be fwooded (unwess the ingwess intewface has
  IFF_AWWMUWTI ow IFF_PWOMISC) and continue to weawn muwticast twaffic thwough
  the netwowk stack notifications. If the hawdwawe is not capabwe of doing that
  then the CPU/management powt must awso be fwooded and muwticast fiwtewing
  happens in softwawe.

- when IGMP snooping is tuwned on, muwticast twaffic must sewectivewy fwow
  to the appwopwiate netwowk powts (incwuding CPU/management powt). Fwooding of
  unknown muwticast shouwd be onwy towawds the powts connected to a muwticast
  woutew (the wocaw device may awso act as a muwticast woutew).

The switch must adhewe to WFC 4541 and fwood muwticast twaffic accowdingwy
since that is what the Winux bwidge impwementation does.

Because IGMP snooping can be tuwned on/off at wuntime, the switchdev dwivew
must be abwe to weconfiguwe the undewwying hawdwawe on the fwy to honow the
toggwing of that option and behave appwopwiatewy.

A switchdev dwivew can awso wefuse to suppowt dynamic toggwing of the muwticast
snooping knob at wuntime and wequiwe the destwuction of the bwidge device(s)
and cweation of a new bwidge device(s) with a diffewent muwticast snooping
vawue.
