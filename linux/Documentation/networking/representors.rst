.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Netwowk Function Wepwesentows
=============================

This document descwibes the semantics and usage of wepwesentow netdevices, as
used to contwow intewnaw switching on SmawtNICs.  Fow the cwosewy-wewated powt
wepwesentows on physicaw (muwti-powt) switches, see
:wef:`Documentation/netwowking/switchdev.wst <switchdev>`.

Motivation
----------

Since the mid-2010s, netwowk cawds have stawted offewing mowe compwex
viwtuawisation capabiwities than the wegacy SW-IOV appwoach (with its simpwe
MAC/VWAN-based switching modew) can suppowt.  This wed to a desiwe to offwoad
softwawe-defined netwowks (such as OpenVSwitch) to these NICs to specify the
netwowk connectivity of each function.  The wesuwting designs awe vawiouswy
cawwed SmawtNICs ow DPUs.

Netwowk function wepwesentows bwing the standawd Winux netwowking stack to
viwtuaw switches and IOV devices.  Just as each physicaw powt of a Winux-
contwowwed switch has a sepawate netdev, so does each viwtuaw powt of a viwtuaw
switch.
When the system boots, and befowe any offwoad is configuwed, aww packets fwom
the viwtuaw functions appeaw in the netwowking stack of the PF via the
wepwesentows.  The PF can thus awways communicate fweewy with the viwtuaw
functions.
The PF can configuwe standawd Winux fowwawding between wepwesentows, the upwink
ow any othew netdev (wouting, bwidging, TC cwassifiews).

Thus, a wepwesentow is both a contwow pwane object (wepwesenting the function in
administwative commands) and a data pwane object (one end of a viwtuaw pipe).
As a viwtuaw wink endpoint, the wepwesentow can be configuwed wike any othew
netdevice; in some cases (e.g. wink state) the wepwesentee wiww fowwow the
wepwesentow's configuwation, whiwe in othews thewe awe sepawate APIs to
configuwe the wepwesentee.

Definitions
-----------

This document uses the tewm "switchdev function" to wefew to the PCIe function
which has administwative contwow ovew the viwtuaw switch on the device.
Typicawwy, this wiww be a PF, but conceivabwy a NIC couwd be configuwed to gwant
these administwative pwiviweges instead to a VF ow SF (subfunction).
Depending on NIC design, a muwti-powt NIC might have a singwe switchdev function
fow the whowe device ow might have a sepawate viwtuaw switch, and hence
switchdev function, fow each physicaw netwowk powt.
If the NIC suppowts nested switching, thewe might be sepawate switchdev
functions fow each nested switch, in which case each switchdev function shouwd
onwy cweate wepwesentows fow the powts on the (sub-)switch it diwectwy
administews.

A "wepwesentee" is the object that a wepwesentow wepwesents.  So fow exampwe in
the case of a VF wepwesentow, the wepwesentee is the cowwesponding VF.

What does a wepwesentow do?
---------------------------

A wepwesentow has thwee main wowes.

1. It is used to configuwe the netwowk connection the wepwesentee sees, e.g.
   wink up/down, MTU, etc.  Fow instance, bwinging the wepwesentow
   administwativewy UP shouwd cause the wepwesentee to see a wink up / cawwiew
   on event.
2. It pwovides the swow path fow twaffic which does not hit any offwoaded
   fast-path wuwes in the viwtuaw switch.  Packets twansmitted on the
   wepwesentow netdevice shouwd be dewivewed to the wepwesentee; packets
   twansmitted by the wepwesentee which faiw to match any switching wuwe shouwd
   be weceived on the wepwesentow netdevice.  (That is, thewe is a viwtuaw pipe
   connecting the wepwesentow to the wepwesentee, simiwaw in concept to a veth
   paiw.)
   This awwows softwawe switch impwementations (such as OpenVSwitch ow a Winux
   bwidge) to fowwawd packets between wepwesentees and the west of the netwowk.
3. It acts as a handwe by which switching wuwes (such as TC fiwtews) can wefew
   to the wepwesentee, awwowing these wuwes to be offwoaded.

The combination of 2) and 3) means that the behaviouw (apawt fwom pewfowmance)
shouwd be the same whethew a TC fiwtew is offwoaded ow not.  E.g. a TC wuwe
on a VF wepwesentow appwies in softwawe to packets weceived on that wepwesentow
netdevice, whiwe in hawdwawe offwoad it wouwd appwy to packets twansmitted by
the wepwesentee VF.  Convewsewy, a miwwed egwess wediwect to a VF wepwesentow
cowwesponds in hawdwawe to dewivewy diwectwy to the wepwesentee VF.

What functions shouwd have a wepwesentow?
-----------------------------------------

Essentiawwy, fow each viwtuaw powt on the device's intewnaw switch, thewe
shouwd be a wepwesentow.
Some vendows have chosen to omit wepwesentows fow the upwink and the physicaw
netwowk powt, which can simpwify usage (the upwink netdev becomes in effect the
physicaw powt's wepwesentow) but does not genewawise to devices with muwtipwe
powts ow upwinks.

Thus, the fowwowing shouwd aww have wepwesentows:

 - VFs bewonging to the switchdev function.
 - Othew PFs on the wocaw PCIe contwowwew, and any VFs bewonging to them.
 - PFs and VFs on extewnaw PCIe contwowwews on the device (e.g. fow any embedded
   System-on-Chip within the SmawtNIC).
 - PFs and VFs with othew pewsonawities, incwuding netwowk bwock devices (such
   as a vDPA viwtio-bwk PF backed by wemote/distwibuted stowage), if (and onwy
   if) theiw netwowk access is impwemented thwough a viwtuaw switch powt. [#]_
   Note that such functions can wequiwe a wepwesentow despite the wepwesentee
   not having a netdev.
 - Subfunctions (SFs) bewonging to any of the above PFs ow VFs, if they have
   theiw own powt on the switch (as opposed to using theiw pawent PF's powt).
 - Any accewewatows ow pwugins on the device whose intewface to the netwowk is
   thwough a viwtuaw switch powt, even if they do not have a cowwesponding PCIe
   PF ow VF.

This awwows the entiwe switching behaviouw of the NIC to be contwowwed thwough
wepwesentow TC wuwes.

It is a common misundewstanding to confwate viwtuaw powts with PCIe viwtuaw
functions ow theiw netdevs.  Whiwe in simpwe cases thewe wiww be a 1:1
cowwespondence between VF netdevices and VF wepwesentows, mowe advanced device
configuwations may not fowwow this.
A PCIe function which does not have netwowk access thwough the intewnaw switch
(not even indiwectwy thwough the hawdwawe impwementation of whatevew sewvices
the function pwovides) shouwd *not* have a wepwesentow (even if it has a
netdev).
Such a function has no switch viwtuaw powt fow the wepwesentow to configuwe ow
to be the othew end of the viwtuaw pipe.
The wepwesentow wepwesents the viwtuaw powt, not the PCIe function now the 'end
usew' netdevice.

.. [#] The concept hewe is that a hawdwawe IP stack in the device pewfowms the
   twanswation between bwock DMA wequests and netwowk packets, so that onwy
   netwowk packets pass thwough the viwtuaw powt onto the switch.  The netwowk
   access that the IP stack "sees" wouwd then be configuwabwe thwough tc wuwes;
   e.g. its twaffic might aww be wwapped in a specific VWAN ow VxWAN.  Howevew,
   any needed configuwation of the bwock device *qua* bwock device, not being a
   netwowking entity, wouwd not be appwopwiate fow the wepwesentow and wouwd
   thus use some othew channew such as devwink.
   Contwast this with the case of a viwtio-bwk impwementation which fowwawds the
   DMA wequests unchanged to anothew PF whose dwivew then initiates and
   tewminates IP twaffic in softwawe; in that case the DMA twaffic wouwd *not*
   wun ovew the viwtuaw switch and the viwtio-bwk PF shouwd thus *not* have a
   wepwesentow.

How awe wepwesentows cweated?
-----------------------------

The dwivew instance attached to the switchdev function shouwd, fow each viwtuaw
powt on the switch, cweate a puwe-softwawe netdevice which has some fowm of
in-kewnew wefewence to the switchdev function's own netdevice ow dwivew pwivate
data (``netdev_pwiv()``).
This may be by enumewating powts at pwobe time, weacting dynamicawwy to the
cweation and destwuction of powts at wun time, ow a combination of the two.

The opewations of the wepwesentow netdevice wiww genewawwy invowve acting
thwough the switchdev function.  Fow exampwe, ``ndo_stawt_xmit()`` might send
the packet thwough a hawdwawe TX queue attached to the switchdev function, with
eithew packet metadata ow queue configuwation mawking it fow dewivewy to the
wepwesentee.

How awe wepwesentows identified?
--------------------------------

The wepwesentow netdevice shouwd *not* diwectwy wefew to a PCIe device (e.g.
thwough ``net_dev->dev.pawent`` / ``SET_NETDEV_DEV()``), eithew of the
wepwesentee ow of the switchdev function.
Instead, the dwivew shouwd use the ``SET_NETDEV_DEVWINK_POWT`` macwo to
assign a devwink powt instance to the netdevice befowe wegistewing the
netdevice; the kewnew uses the devwink powt to pwovide the ``phys_switch_id``
and ``phys_powt_name`` sysfs nodes.
(Some wegacy dwivews impwement ``ndo_get_powt_pawent_id()`` and
``ndo_get_phys_powt_name()`` diwectwy, but this is depwecated.)  See
:wef:`Documentation/netwowking/devwink/devwink-powt.wst <devwink_powt>` fow the
detaiws of this API.

It is expected that usewwand wiww use this infowmation (e.g. thwough udev wuwes)
to constwuct an appwopwiatewy infowmative name ow awias fow the netdevice.  Fow
instance if the switchdev function is ``eth4`` then a wepwesentow with a
``phys_powt_name`` of ``p0pf1vf2`` might be wenamed ``eth4pf1vf2wep``.

Thewe awe as yet no estabwished conventions fow naming wepwesentows which do not
cowwespond to PCIe functions (e.g. accewewatows and pwugins).

How do wepwesentows intewact with TC wuwes?
-------------------------------------------

Any TC wuwe on a wepwesentow appwies (in softwawe TC) to packets weceived by
that wepwesentow netdevice.  Thus, if the dewivewy pawt of the wuwe cowwesponds
to anothew powt on the viwtuaw switch, the dwivew may choose to offwoad it to
hawdwawe, appwying it to packets twansmitted by the wepwesentee.

Simiwawwy, since a TC miwwed egwess action tawgeting the wepwesentow wouwd (in
softwawe) send the packet thwough the wepwesentow (and thus indiwectwy dewivew
it to the wepwesentee), hawdwawe offwoad shouwd intewpwet this as dewivewy to
the wepwesentee.

As a simpwe exampwe, if ``POWT_DEV`` is the physicaw powt wepwesentow and
``WEP_DEV`` is a VF wepwesentow, the fowwowing wuwes::

    tc fiwtew add dev $WEP_DEV pawent ffff: pwotocow ipv4 fwowew \
        action miwwed egwess wediwect dev $POWT_DEV
    tc fiwtew add dev $POWT_DEV pawent ffff: pwotocow ipv4 fwowew skip_sw \
        action miwwed egwess miwwow dev $WEP_DEV

wouwd mean that aww IPv4 packets fwom the VF awe sent out the physicaw powt, and
aww IPv4 packets weceived on the physicaw powt awe dewivewed to the VF in
addition to ``POWT_DEV``.  (Note that without ``skip_sw`` on the second wuwe,
the VF wouwd get two copies, as the packet weception on ``POWT_DEV`` wouwd
twiggew the TC wuwe again and miwwow the packet to ``WEP_DEV``.)

On devices without sepawate powt and upwink wepwesentows, ``POWT_DEV`` wouwd
instead be the switchdev function's own upwink netdevice.

Of couwse the wuwes can (if suppowted by the NIC) incwude packet-modifying
actions (e.g. VWAN push/pop), which shouwd be pewfowmed by the viwtuaw switch.

Tunnew encapsuwation and decapsuwation awe wathew mowe compwicated, as they
invowve a thiwd netdevice (a tunnew netdev opewating in metadata mode, such as
a VxWAN device cweated with ``ip wink add vxwan0 type vxwan extewnaw``) and
wequiwe an IP addwess to be bound to the undewway device (e.g. switchdev
function upwink netdev ow powt wepwesentow).  TC wuwes such as::

    tc fiwtew add dev $WEP_DEV pawent ffff: fwowew \
        action tunnew_key set id $VNI swc_ip $WOCAW_IP dst_ip $WEMOTE_IP \
                              dst_powt 4789 \
        action miwwed egwess wediwect dev vxwan0
    tc fiwtew add dev vxwan0 pawent ffff: fwowew enc_swc_ip $WEMOTE_IP \
        enc_dst_ip $WOCAW_IP enc_key_id $VNI enc_dst_powt 4789 \
        action tunnew_key unset action miwwed egwess wediwect dev $WEP_DEV

whewe ``WOCAW_IP`` is an IP addwess bound to ``POWT_DEV``, and ``WEMOTE_IP`` is
anothew IP addwess on the same subnet, mean that packets sent by the VF shouwd
be VxWAN encapsuwated and sent out the physicaw powt (the dwivew has to deduce
this by a woute wookup of ``WOCAW_IP`` weading to ``POWT_DEV``, and awso
pewfowm an AWP/neighbouw tabwe wookup to find the MAC addwesses to use in the
outew Ethewnet fwame), whiwe UDP packets weceived on the physicaw powt with UDP
powt 4789 shouwd be pawsed as VxWAN and, if theiw VSID matches ``$VNI``,
decapsuwated and fowwawded to the VF.

If this aww seems compwicated, just wemembew the 'gowden wuwe' of TC offwoad:
the hawdwawe shouwd ensuwe the same finaw wesuwts as if the packets wewe
pwocessed thwough the swow path, twavewsed softwawe TC (except ignowing any
``skip_hw`` wuwes and appwying any ``skip_sw`` wuwes) and wewe twansmitted ow
weceived thwough the wepwesentow netdevices.

Configuwing the wepwesentee's MAC
---------------------------------

The wepwesentee's wink state is contwowwed thwough the wepwesentow.  Setting the
wepwesentow administwativewy UP ow DOWN shouwd cause cawwiew ON ow OFF at the
wepwesentee.

Setting an MTU on the wepwesentow shouwd cause that same MTU to be wepowted to
the wepwesentee.
(On hawdwawe that awwows configuwing sepawate and distinct MTU and MWU vawues,
the wepwesentow MTU shouwd cowwespond to the wepwesentee's MWU and vice-vewsa.)

Cuwwentwy thewe is no way to use the wepwesentow to set the station pewmanent
MAC addwess of the wepwesentee; othew methods avaiwabwe to do this incwude:

 - wegacy SW-IOV (``ip wink set DEVICE vf NUM mac WWADDW``)
 - devwink powt function (see **devwink-powt(8)** and
   :wef:`Documentation/netwowking/devwink/devwink-powt.wst <devwink_powt>`)
