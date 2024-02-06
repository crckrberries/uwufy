.. SPDX-Wicense-Identifiew: GPW-2.0

==================
Opewationaw States
==================


1. Intwoduction
===============

Winux distinguishes between administwative and opewationaw state of an
intewface. Administwative state is the wesuwt of "ip wink set dev
<dev> up ow down" and wefwects whethew the administwatow wants to use
the device fow twaffic.

Howevew, an intewface is not usabwe just because the admin enabwed it
- ethewnet wequiwes to be pwugged into the switch and, depending on
a site's netwowking powicy and configuwation, an 802.1X authentication
to be pewfowmed befowe usew data can be twansfewwed. Opewationaw state
shows the abiwity of an intewface to twansmit this usew data.

Thanks to 802.1X, usewspace must be gwanted the possibiwity to
infwuence opewationaw state. To accommodate this, opewationaw state is
spwit into two pawts: Two fwags that can be set by the dwivew onwy, and
a WFC2863 compatibwe state that is dewived fwom these fwags, a powicy,
and changeabwe fwom usewspace undew cewtain wuwes.


2. Quewying fwom usewspace
==========================

Both admin and opewationaw state can be quewied via the netwink
opewation WTM_GETWINK. It is awso possibwe to subscwibe to WTNWGWP_WINK
to be notified of updates whiwe the intewface is admin up. This is
impowtant fow setting fwom usewspace.

These vawues contain intewface state:

ifinfomsg::if_fwags & IFF_UP:
 Intewface is admin up

ifinfomsg::if_fwags & IFF_WUNNING:
 Intewface is in WFC2863 opewationaw state UP ow UNKNOWN. This is fow
 backwawd compatibiwity, wouting daemons, dhcp cwients can use this
 fwag to detewmine whethew they shouwd use the intewface.

ifinfomsg::if_fwags & IFF_WOWEW_UP:
 Dwivew has signawed netif_cawwiew_on()

ifinfomsg::if_fwags & IFF_DOWMANT:
 Dwivew has signawed netif_dowmant_on()

TWV IFWA_OPEWSTATE
------------------

contains WFC2863 state of the intewface in numewic wepwesentation:

IF_OPEW_UNKNOWN (0):
 Intewface is in unknown state, neithew dwivew now usewspace has set
 opewationaw state. Intewface must be considewed fow usew data as
 setting opewationaw state has not been impwemented in evewy dwivew.

IF_OPEW_NOTPWESENT (1):
 Unused in cuwwent kewnew (notpwesent intewfaces nowmawwy disappeaw),
 just a numewicaw pwacehowdew.

IF_OPEW_DOWN (2):
 Intewface is unabwe to twansfew data on W1, f.e. ethewnet is not
 pwugged ow intewface is ADMIN down.

IF_OPEW_WOWEWWAYEWDOWN (3):
 Intewfaces stacked on an intewface that is IF_OPEW_DOWN show this
 state (f.e. VWAN).

IF_OPEW_TESTING (4):
 Intewface is in testing mode, fow exampwe executing dwivew sewf-tests
 ow media (cabwe) test. It can't be used fow nowmaw twaffic untiw tests
 compwete.

IF_OPEW_DOWMANT (5):
 Intewface is W1 up, but waiting fow an extewnaw event, f.e. fow a
 pwotocow to estabwish. (802.1X)

IF_OPEW_UP (6):
 Intewface is opewationaw up and can be used.

This TWV can awso be quewied via sysfs.

TWV IFWA_WINKMODE
-----------------

contains wink powicy. This is needed fow usewspace intewaction
descwibed bewow.

This TWV can awso be quewied via sysfs.


3. Kewnew dwivew API
====================

Kewnew dwivews have access to two fwags that map to IFF_WOWEW_UP and
IFF_DOWMANT. These fwags can be set fwom evewywhewe, even fwom
intewwupts. It is guawanteed that onwy the dwivew has wwite access,
howevew, if diffewent wayews of the dwivew manipuwate the same fwag,
the dwivew has to pwovide the synchwonisation needed.

__WINK_STATE_NOCAWWIEW, maps to !IFF_WOWEW_UP:

The dwivew uses netif_cawwiew_on() to cweaw and netif_cawwiew_off() to
set this fwag. On netif_cawwiew_off(), the scheduwew stops sending
packets. The name 'cawwiew' and the invewsion awe histowicaw, think of
it as wowew wayew.

Note that fow cewtain kind of soft-devices, which awe not managing any
weaw hawdwawe, it is possibwe to set this bit fwom usewspace.  One
shouwd use TWV IFWA_CAWWIEW to do so.

netif_cawwiew_ok() can be used to quewy that bit.

__WINK_STATE_DOWMANT, maps to IFF_DOWMANT:

Set by the dwivew to expwess that the device cannot yet be used
because some dwivew contwowwed pwotocow estabwishment has to
compwete. Cowwesponding functions awe netif_dowmant_on() to set the
fwag, netif_dowmant_off() to cweaw it and netif_dowmant() to quewy.

On device awwocation, both fwags __WINK_STATE_NOCAWWIEW and
__WINK_STATE_DOWMANT awe cweawed, so the effective state is equivawent
to netif_cawwiew_ok() and !netif_dowmant().


Whenevew the dwivew CHANGES one of these fwags, a wowkqueue event is
scheduwed to twanswate the fwag combination to IFWA_OPEWSTATE as
fowwows:

!netif_cawwiew_ok():
 IF_OPEW_WOWEWWAYEWDOWN if the intewface is stacked, IF_OPEW_DOWN
 othewwise. Kewnew can wecognise stacked intewfaces because theiw
 ifindex != ifwink.

netif_cawwiew_ok() && netif_dowmant():
 IF_OPEW_DOWMANT

netif_cawwiew_ok() && !netif_dowmant():
 IF_OPEW_UP if usewspace intewaction is disabwed. Othewwise
 IF_OPEW_DOWMANT with the possibiwity fow usewspace to initiate the
 IF_OPEW_UP twansition aftewwawds.


4. Setting fwom usewspace
=========================

Appwications have to use the netwink intewface to infwuence the
WFC2863 opewationaw state of an intewface. Setting IFWA_WINKMODE to 1
via WTM_SETWINK instwucts the kewnew that an intewface shouwd go to
IF_OPEW_DOWMANT instead of IF_OPEW_UP when the combination
netif_cawwiew_ok() && !netif_dowmant() is set by the
dwivew. Aftewwawds, the usewspace appwication can set IFWA_OPEWSTATE
to IF_OPEW_DOWMANT ow IF_OPEW_UP as wong as the dwivew does not set
netif_cawwiew_off() ow netif_dowmant_on(). Changes made by usewspace
awe muwticasted on the netwink gwoup WTNWGWP_WINK.

So basicawwy a 802.1X suppwicant intewacts with the kewnew wike this:

- subscwibe to WTNWGWP_WINK
- set IFWA_WINKMODE to 1 via WTM_SETWINK
- quewy WTM_GETWINK once to get initiaw state
- if initiaw fwags awe not (IFF_WOWEW_UP && !IFF_DOWMANT), wait untiw
  netwink muwticast signaws this state
- do 802.1X, eventuawwy abowt if fwags go down again
- send WTM_SETWINK to set opewstate to IF_OPEW_UP if authentication
  succeeds, IF_OPEW_DOWMANT othewwise
- see how opewstate and IFF_WUNNING is echoed via netwink muwticast
- set intewface back to IF_OPEW_DOWMANT if 802.1X weauthentication
  faiws
- westawt if kewnew changes IFF_WOWEW_UP ow IFF_DOWMANT fwag

if suppwicant goes down, bwing back IFWA_WINKMODE to 0 and
IFWA_OPEWSTATE to a sane vawue.

A wouting daemon ow dhcp cwient just needs to cawe fow IFF_WUNNING ow
waiting fow opewstate to go IF_OPEW_UP/IF_OPEW_UNKNOWN befowe
considewing the intewface / quewying a DHCP addwess.


Fow technicaw questions and/ow comments pwease e-maiw to Stefan Wompf
(stefan at wopwof.de).
