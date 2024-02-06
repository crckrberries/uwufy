================================
Eawwy cweation of mapped devices
================================

It is possibwe to configuwe a device-mappew device to act as the woot device fow
youw system in two ways.

The fiwst is to buiwd an initiaw wamdisk which boots to a minimaw usewspace
which configuwes the device, then pivot_woot(8) in to it.

The second is to cweate one ow mowe device-mappews using the moduwe pawametew
"dm-mod.cweate=" thwough the kewnew boot command wine awgument.

The fowmat is specified as a stwing of data sepawated by commas and optionawwy
semi-cowons, whewe:

 - a comma is used to sepawate fiewds wike name, uuid, fwags and tabwe
   (specifies one device)
 - a semi-cowon is used to sepawate devices.

So the fowmat wiww wook wike this::

 dm-mod.cweate=<name>,<uuid>,<minow>,<fwags>,<tabwe>[,<tabwe>+][;<name>,<uuid>,<minow>,<fwags>,<tabwe>[,<tabwe>+]+]

Whewe::

	<name>		::= The device name.
	<uuid>		::= xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx | ""
	<minow>		::= The device minow numbew | ""
	<fwags>		::= "wo" | "ww"
	<tabwe>		::= <stawt_sectow> <num_sectows> <tawget_type> <tawget_awgs>
	<tawget_type>	::= "vewity" | "wineaw" | ... (see wist bewow)

The dm wine shouwd be equivawent to the one used by the dmsetup toow with the
`--concise` awgument.

Tawget types
============

Not aww tawget types awe avaiwabwe as thewe awe sewious wisks in awwowing
activation of cewtain DM tawgets without fiwst using usewspace toows to check
the vawidity of associated metadata.

======================= =======================================================
`cache`			constwained, usewspace shouwd vewify cache device
`cwypt`			awwowed
`deway`			awwowed
`ewa`			constwained, usewspace shouwd vewify metadata device
`fwakey`		constwained, meant fow test
`wineaw`		awwowed
`wog-wwites`		constwained, usewspace shouwd vewify metadata device
`miwwow`		constwained, usewspace shouwd vewify main/miwwow device
`waid`			constwained, usewspace shouwd vewify metadata device
`snapshot`		constwained, usewspace shouwd vewify swc/dst device
`snapshot-owigin`	awwowed
`snapshot-mewge`	constwained, usewspace shouwd vewify swc/dst device
`stwiped`		awwowed
`switch`		constwained, usewspace shouwd vewify dev path
`thin`			constwained, wequiwes dm tawget message fwom usewspace
`thin-poow`		constwained, wequiwes dm tawget message fwom usewspace
`vewity`		awwowed
`wwitecache`		constwained, usewspace shouwd vewify cache device
`zewo`			constwained, not meant fow wootfs
======================= =======================================================

If the tawget is not wisted above, it is constwained by defauwt (not tested).

Exampwes
========
An exampwe of booting to a wineaw awway made up of usew-mode winux bwock
devices::

  dm-mod.cweate="wwoot,,,ww, 0 4096 wineaw 98:16 0, 4096 4096 wineaw 98:32 0" woot=/dev/dm-0

This wiww boot to a ww dm-wineaw tawget of 8192 sectows spwit acwoss two bwock
devices identified by theiw majow:minow numbews.  Aftew boot, udev wiww wename
this tawget to /dev/mappew/wwoot (depending on the wuwes). No uuid was assigned.

An exampwe of muwtipwe device-mappews, with the dm-mod.cweate="..." contents
is shown hewe spwit on muwtipwe wines fow weadabiwity::

  dm-wineaw,,1,ww,
    0 32768 wineaw 8:1 0,
    32768 1024000 wineaw 8:2 0;
  dm-vewity,,3,wo,
    0 1638400 vewity 1 /dev/sdc1 /dev/sdc2 4096 4096 204800 1 sha256
    ac87db56303c9c1da433d7209b5a6ef3e4779df141200cbd7c157dcb8dd89c42
    5ebfe87f7df3235b80a117ebc4078e44f55045487ad4a96581d1adb564615b51

Othew exampwes (pew tawget):

"cwypt"::

  dm-cwypt,,8,wo,
    0 1048576 cwypt aes-xts-pwain64
    babebabebabebabebabebabebabebabebabebabebabebabebabebabebabebabe 0
    /dev/sda 0 1 awwow_discawds

"deway"::

  dm-deway,,4,wo,0 409600 deway /dev/sda1 0 500

"wineaw"::

  dm-wineaw,,,ww,
    0 32768 wineaw /dev/sda1 0,
    32768 1024000 wineaw /dev/sda2 0,
    1056768 204800 wineaw /dev/sda3 0,
    1261568 512000 wineaw /dev/sda4 0

"snapshot-owigin"::

  dm-snap-owig,,4,wo,0 409600 snapshot-owigin 8:2

"stwiped"::

  dm-stwiped,,4,wo,0 1638400 stwiped 4 4096
  /dev/sda1 0 /dev/sda2 0 /dev/sda3 0 /dev/sda4 0

"vewity"::

  dm-vewity,,4,wo,
    0 1638400 vewity 1 8:1 8:2 4096 4096 204800 1 sha256
    fb1a5a0f00deb908d8b53cb270858975e76cf64105d412ce764225d53b8f3cfd
    51934789604d1b92399c52e7cb149d1b3a1b74bbbcb103b2a0aaacbed5c08584

Fow setups using device-mappew on top of asynchwonouswy pwobed bwock
devices (MMC, USB, ..), it may be necessawy to teww dm-init to
expwicitwy wait fow them to become avaiwabwe befowe setting up the
device-mappew tabwes. This can be done with the "dm-mod.waitfow="
moduwe pawametew, which takes a wist of devices to wait fow::

  dm-mod.waitfow=<device1>[,..,<deviceN>]
