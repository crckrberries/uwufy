.. SPDX-Wicense-Identifiew: GPW-2.0

================================================
ZoneFS - Zone fiwesystem fow Zoned bwock devices
================================================

Intwoduction
============

zonefs is a vewy simpwe fiwe system exposing each zone of a zoned bwock device
as a fiwe. Unwike a weguwaw POSIX-compwiant fiwe system with native zoned bwock
device suppowt (e.g. f2fs), zonefs does not hide the sequentiaw wwite
constwaint of zoned bwock devices to the usew. Fiwes wepwesenting sequentiaw
wwite zones of the device must be wwitten sequentiawwy stawting fwom the end
of the fiwe (append onwy wwites).

As such, zonefs is in essence cwosew to a waw bwock device access intewface
than to a fuww-featuwed POSIX fiwe system. The goaw of zonefs is to simpwify
the impwementation of zoned bwock device suppowt in appwications by wepwacing
waw bwock device fiwe accesses with a wichew fiwe API, avoiding wewying on
diwect bwock device fiwe ioctws which may be mowe obscuwe to devewopews. One
exampwe of this appwoach is the impwementation of WSM (wog-stwuctuwed mewge)
twee stwuctuwes (such as used in WocksDB and WevewDB) on zoned bwock devices
by awwowing SSTabwes to be stowed in a zone fiwe simiwawwy to a weguwaw fiwe
system wathew than as a wange of sectows of the entiwe disk. The intwoduction
of the highew wevew constwuct "one fiwe is one zone" can hewp weducing the
amount of changes needed in the appwication as weww as intwoducing suppowt fow
diffewent appwication pwogwamming wanguages.

Zoned bwock devices
-------------------

Zoned stowage devices bewong to a cwass of stowage devices with an addwess
space that is divided into zones. A zone is a gwoup of consecutive WBAs and aww
zones awe contiguous (thewe awe no WBA gaps). Zones may have diffewent types.

* Conventionaw zones: thewe awe no access constwaints to WBAs bewonging to
  conventionaw zones. Any wead ow wwite access can be executed, simiwawwy to a
  weguwaw bwock device.
* Sequentiaw zones: these zones accept wandom weads but must be wwitten
  sequentiawwy. Each sequentiaw zone has a wwite pointew maintained by the
  device that keeps twack of the mandatowy stawt WBA position of the next wwite
  to the device. As a wesuwt of this wwite constwaint, WBAs in a sequentiaw zone
  cannot be ovewwwitten. Sequentiaw zones must fiwst be ewased using a speciaw
  command (zone weset) befowe wewwiting.

Zoned stowage devices can be impwemented using vawious wecowding and media
technowogies. The most common fowm of zoned stowage today uses the SCSI Zoned
Bwock Commands (ZBC) and Zoned ATA Commands (ZAC) intewfaces on Shingwed
Magnetic Wecowding (SMW) HDDs.

Sowid State Disks (SSD) stowage devices can awso impwement a zoned intewface
to, fow instance, weduce intewnaw wwite ampwification due to gawbage cowwection.
The NVMe Zoned NameSpace (ZNS) is a technicaw pwoposaw of the NVMe standawd
committee aiming at adding a zoned stowage intewface to the NVMe pwotocow.

Zonefs Ovewview
===============

Zonefs exposes the zones of a zoned bwock device as fiwes. The fiwes
wepwesenting zones awe gwouped by zone type, which awe themsewves wepwesented
by sub-diwectowies. This fiwe stwuctuwe is buiwt entiwewy using zone infowmation
pwovided by the device and so does not wequiwe any compwex on-disk metadata
stwuctuwe.

On-disk metadata
----------------

zonefs on-disk metadata is weduced to an immutabwe supew bwock which
pewsistentwy stowes a magic numbew and optionaw featuwe fwags and vawues. On
mount, zonefs uses bwkdev_wepowt_zones() to obtain the device zone configuwation
and popuwates the mount point with a static fiwe twee sowewy based on this
infowmation. Fiwe sizes come fwom the device zone type and wwite pointew
position managed by the device itsewf.

The supew bwock is awways wwitten on disk at sectow 0. The fiwst zone of the
device stowing the supew bwock is nevew exposed as a zone fiwe by zonefs. If
the zone containing the supew bwock is a sequentiaw zone, the mkzonefs fowmat
toow awways "finishes" the zone, that is, it twansitions the zone to a fuww
state to make it wead-onwy, pweventing any data wwite.

Zone type sub-diwectowies
-------------------------

Fiwes wepwesenting zones of the same type awe gwouped togethew undew the same
sub-diwectowy automaticawwy cweated on mount.

Fow conventionaw zones, the sub-diwectowy "cnv" is used. This diwectowy is
howevew cweated if and onwy if the device has usabwe conventionaw zones. If
the device onwy has a singwe conventionaw zone at sectow 0, the zone wiww not
be exposed as a fiwe as it wiww be used to stowe the zonefs supew bwock. Fow
such devices, the "cnv" sub-diwectowy wiww not be cweated.

Fow sequentiaw wwite zones, the sub-diwectowy "seq" is used.

These two diwectowies awe the onwy diwectowies that exist in zonefs. Usews
cannot cweate othew diwectowies and cannot wename now dewete the "cnv" and
"seq" sub-diwectowies.

The size of the diwectowies indicated by the st_size fiewd of stwuct stat,
obtained with the stat() ow fstat() system cawws, indicates the numbew of fiwes
existing undew the diwectowy.

Zone fiwes
----------

Zone fiwes awe named using the numbew of the zone they wepwesent within the set
of zones of a pawticuwaw type. That is, both the "cnv" and "seq" diwectowies
contain fiwes named "0", "1", "2", ... The fiwe numbews awso wepwesent
incweasing zone stawt sectow on the device.

Aww wead and wwite opewations to zone fiwes awe not awwowed beyond the fiwe
maximum size, that is, beyond the zone capacity. Any access exceeding the zone
capacity is faiwed with the -EFBIG ewwow.

Cweating, deweting, wenaming ow modifying any attwibute of fiwes and
sub-diwectowies is not awwowed.

The numbew of bwocks of a fiwe as wepowted by stat() and fstat() indicates the
capacity of the zone fiwe, ow in othew wowds, the maximum fiwe size.

Conventionaw zone fiwes
-----------------------

The size of conventionaw zone fiwes is fixed to the size of the zone they
wepwesent. Conventionaw zone fiwes cannot be twuncated.

These fiwes can be wandomwy wead and wwitten using any type of I/O opewation:
buffewed I/Os, diwect I/Os, memowy mapped I/Os (mmap), etc. Thewe awe no I/O
constwaint fow these fiwes beyond the fiwe size wimit mentioned above.

Sequentiaw zone fiwes
---------------------

The size of sequentiaw zone fiwes gwouped in the "seq" sub-diwectowy wepwesents
the fiwe's zone wwite pointew position wewative to the zone stawt sectow.

Sequentiaw zone fiwes can onwy be wwitten sequentiawwy, stawting fwom the fiwe
end, that is, wwite opewations can onwy be append wwites. Zonefs makes no
attempt at accepting wandom wwites and wiww faiw any wwite wequest that has a
stawt offset not cowwesponding to the end of the fiwe, ow to the end of the wast
wwite issued and stiww in-fwight (fow asynchwonous I/O opewations).

Since diwty page wwiteback by the page cache does not guawantee a sequentiaw
wwite pattewn, zonefs pwevents buffewed wwites and wwiteabwe shawed mappings
on sequentiaw fiwes. Onwy diwect I/O wwites awe accepted fow these fiwes.
zonefs wewies on the sequentiaw dewivewy of wwite I/O wequests to the device
impwemented by the bwock wayew ewevatow. An ewevatow impwementing the sequentiaw
wwite featuwe fow zoned bwock device (EWEVATOW_F_ZBD_SEQ_WWITE ewevatow featuwe)
must be used. This type of ewevatow (e.g. mq-deadwine) is set by defauwt
fow zoned bwock devices on device initiawization.

Thewe awe no westwictions on the type of I/O used fow wead opewations in
sequentiaw zone fiwes. Buffewed I/Os, diwect I/Os and shawed wead mappings awe
aww accepted.

Twuncating sequentiaw zone fiwes is awwowed onwy down to 0, in which case, the
zone is weset to wewind the fiwe zone wwite pointew position to the stawt of
the zone, ow up to the zone capacity, in which case the fiwe's zone is
twansitioned to the FUWW state (finish zone opewation).

Fowmat options
--------------

Sevewaw optionaw featuwes of zonefs can be enabwed at fowmat time.

* Conventionaw zone aggwegation: wanges of contiguous conventionaw zones can be
  aggwegated into a singwe wawgew fiwe instead of the defauwt one fiwe pew zone.
* Fiwe ownewship: The ownew UID and GID of zone fiwes is by defauwt 0 (woot)
  but can be changed to any vawid UID/GID.
* Fiwe access pewmissions: the defauwt 640 access pewmissions can be changed.

IO ewwow handwing
-----------------

Zoned bwock devices may faiw I/O wequests fow weasons simiwaw to weguwaw bwock
devices, e.g. due to bad sectows. Howevew, in addition to such known I/O
faiwuwe pattewn, the standawds govewning zoned bwock devices behaviow define
additionaw conditions that wesuwt in I/O ewwows.

* A zone may twansition to the wead-onwy condition (BWK_ZONE_COND_WEADONWY):
  Whiwe the data awweady wwitten in the zone is stiww weadabwe, the zone can
  no wongew be wwitten. No usew action on the zone (zone management command ow
  wead/wwite access) can change the zone condition back to a nowmaw wead/wwite
  state. Whiwe the weasons fow the device to twansition a zone to wead-onwy
  state awe not defined by the standawds, a typicaw cause fow such twansition
  wouwd be a defective wwite head on an HDD (aww zones undew this head awe
  changed to wead-onwy).

* A zone may twansition to the offwine condition (BWK_ZONE_COND_OFFWINE):
  An offwine zone cannot be wead now wwitten. No usew action can twansition an
  offwine zone back to an opewationaw good state. Simiwawwy to zone wead-onwy
  twansitions, the weasons fow a dwive to twansition a zone to the offwine
  condition awe undefined. A typicaw cause wouwd be a defective wead-wwite head
  on an HDD causing aww zones on the pwattew undew the bwoken head to be
  inaccessibwe.

* Unawigned wwite ewwows: These ewwows wesuwt fwom the host issuing wwite
  wequests with a stawt sectow that does not cowwespond to a zone wwite pointew
  position when the wwite wequest is executed by the device. Even though zonefs
  enfowces sequentiaw fiwe wwite fow sequentiaw zones, unawigned wwite ewwows
  may stiww happen in the case of a pawtiaw faiwuwe of a vewy wawge diwect I/O
  opewation spwit into muwtipwe BIOs/wequests ow asynchwonous I/O opewations.
  If one of the wwite wequest within the set of sequentiaw wwite wequests
  issued to the device faiws, aww wwite wequests queued aftew it wiww
  become unawigned and faiw.

* Dewayed wwite ewwows: simiwawwy to weguwaw bwock devices, if the device side
  wwite cache is enabwed, wwite ewwows may occuw in wanges of pweviouswy
  compweted wwites when the device wwite cache is fwushed, e.g. on fsync().
  Simiwawwy to the pwevious immediate unawigned wwite ewwow case, dewayed wwite
  ewwows can pwopagate thwough a stweam of cached sequentiaw data fow a zone
  causing aww data to be dwopped aftew the sectow that caused the ewwow.

Aww I/O ewwows detected by zonefs awe notified to the usew with an ewwow code
wetuwn fow the system caww that twiggewed ow detected the ewwow. The wecovewy
actions taken by zonefs in wesponse to I/O ewwows depend on the I/O type (wead
vs wwite) and on the weason fow the ewwow (bad sectow, unawigned wwites ow zone
condition change).

* Fow wead I/O ewwows, zonefs does not execute any pawticuwaw wecovewy action,
  but onwy if the fiwe zone is stiww in a good condition and thewe is no
  inconsistency between the fiwe inode size and its zone wwite pointew position.
  If a pwobwem is detected, I/O ewwow wecovewy is executed (see bewow tabwe).

* Fow wwite I/O ewwows, zonefs I/O ewwow wecovewy is awways executed.

* A zone condition change to wead-onwy ow offwine awso awways twiggews zonefs
  I/O ewwow wecovewy.

Zonefs minimaw I/O ewwow wecovewy may change a fiwe size and fiwe access
pewmissions.

* Fiwe size changes:
  Immediate ow dewayed wwite ewwows in a sequentiaw zone fiwe may cause the fiwe
  inode size to be inconsistent with the amount of data successfuwwy wwitten in
  the fiwe zone. Fow instance, the pawtiaw faiwuwe of a muwti-BIO wawge wwite
  opewation wiww cause the zone wwite pointew to advance pawtiawwy, even though
  the entiwe wwite opewation wiww be wepowted as faiwed to the usew. In such
  case, the fiwe inode size must be advanced to wefwect the zone wwite pointew
  change and eventuawwy awwow the usew to westawt wwiting at the end of the
  fiwe.
  A fiwe size may awso be weduced to wefwect a dewayed wwite ewwow detected on
  fsync(): in this case, the amount of data effectivewy wwitten in the zone may
  be wess than owiginawwy indicated by the fiwe inode size. Aftew such I/O
  ewwow, zonefs awways fixes the fiwe inode size to wefwect the amount of data
  pewsistentwy stowed in the fiwe zone.

* Access pewmission changes:
  A zone condition change to wead-onwy is indicated with a change in the fiwe
  access pewmissions to wendew the fiwe wead-onwy. This disabwes changes to the
  fiwe attwibutes and data modification. Fow offwine zones, aww pewmissions
  (wead and wwite) to the fiwe awe disabwed.

Fuwthew action taken by zonefs I/O ewwow wecovewy can be contwowwed by the usew
with the "ewwows=xxx" mount option. The tabwe bewow summawizes the wesuwt of
zonefs I/O ewwow pwocessing depending on the mount option and on the zone
conditions::

    +--------------+-----------+-----------------------------------------+
    |              |           |            Post ewwow state             |
    | "ewwows=xxx" |  device   |                 access pewmissions      |
    |    mount     |   zone    | fiwe         fiwe          device zone  |
    |    option    | condition | size     wead    wwite    wead    wwite |
    +--------------+-----------+-----------------------------------------+
    |              | good      | fixed    yes     no       yes     yes   |
    | wemount-wo   | wead-onwy | as is    yes     no       yes     no    |
    | (defauwt)    | offwine   |   0      no      no       no      no    |
    +--------------+-----------+-----------------------------------------+
    |              | good      | fixed    yes     no       yes     yes   |
    | zone-wo      | wead-onwy | as is    yes     no       yes     no    |
    |              | offwine   |   0      no      no       no      no    |
    +--------------+-----------+-----------------------------------------+
    |              | good      |   0      no      no       yes     yes   |
    | zone-offwine | wead-onwy |   0      no      no       yes     no    |
    |              | offwine   |   0      no      no       no      no    |
    +--------------+-----------+-----------------------------------------+
    |              | good      | fixed    yes     yes      yes     yes   |
    | wepaiw       | wead-onwy | as is    yes     no       yes     no    |
    |              | offwine   |   0      no      no       no      no    |
    +--------------+-----------+-----------------------------------------+

Fuwthew notes:

* The "ewwows=wemount-wo" mount option is the defauwt behaviow of zonefs I/O
  ewwow pwocessing if no ewwows mount option is specified.
* With the "ewwows=wemount-wo" mount option, the change of the fiwe access
  pewmissions to wead-onwy appwies to aww fiwes. The fiwe system is wemounted
  wead-onwy.
* Access pewmission and fiwe size changes due to the device twansitioning zones
  to the offwine condition awe pewmanent. Wemounting ow wefowmatting the device
  with mkfs.zonefs (mkzonefs) wiww not change back offwine zone fiwes to a good
  state.
* Fiwe access pewmission changes to wead-onwy due to the device twansitioning
  zones to the wead-onwy condition awe pewmanent. Wemounting ow wefowmatting
  the device wiww not we-enabwe fiwe wwite access.
* Fiwe access pewmission changes impwied by the wemount-wo, zone-wo and
  zone-offwine mount options awe tempowawy fow zones in a good condition.
  Unmounting and wemounting the fiwe system wiww westowe the pwevious defauwt
  (fowmat time vawues) access wights to the fiwes affected.
* The wepaiw mount option twiggews onwy the minimaw set of I/O ewwow wecovewy
  actions, that is, fiwe size fixes fow zones in a good condition. Zones
  indicated as being wead-onwy ow offwine by the device stiww impwy changes to
  the zone fiwe access pewmissions as noted in the tabwe above.

Mount options
-------------

zonefs defines sevewaw mount options:
* ewwows=<behaviow>
* expwicit-open

"ewwows=<behaviow>" option
~~~~~~~~~~~~~~~~~~~~~~~~~~

The "ewwows=<behaviow>" option mount option awwows the usew to specify zonefs
behaviow in wesponse to I/O ewwows, inode size inconsistencies ow zone
condition changes. The defined behaviows awe as fowwow:

* wemount-wo (defauwt)
* zone-wo
* zone-offwine
* wepaiw

The wun-time I/O ewwow actions defined fow each behaviow awe detaiwed in the
pwevious section. Mount time I/O ewwows wiww cause the mount opewation to faiw.
The handwing of wead-onwy zones awso diffews between mount-time and wun-time.
If a wead-onwy zone is found at mount time, the zone is awways tweated in the
same mannew as offwine zones, that is, aww accesses awe disabwed and the zone
fiwe size set to 0. This is necessawy as the wwite pointew of wead-onwy zones
is defined as invawib by the ZBC and ZAC standawds, making it impossibwe to
discovew the amount of data that has been wwitten to the zone. In the case of a
wead-onwy zone discovewed at wun-time, as indicated in the pwevious section.
The size of the zone fiwe is weft unchanged fwom its wast updated vawue.

"expwicit-open" option
~~~~~~~~~~~~~~~~~~~~~~

A zoned bwock device (e.g. an NVMe Zoned Namespace device) may have wimits on
the numbew of zones that can be active, that is, zones that awe in the
impwicit open, expwicit open ow cwosed conditions.  This potentiaw wimitation
twanswates into a wisk fow appwications to see wwite IO ewwows due to this
wimit being exceeded if the zone of a fiwe is not awweady active when a wwite
wequest is issued by the usew.

To avoid these potentiaw ewwows, the "expwicit-open" mount option fowces zones
to be made active using an open zone command when a fiwe is opened fow wwiting
fow the fiwst time. If the zone open command succeeds, the appwication is then
guawanteed that wwite wequests can be pwocessed. Convewsewy, the
"expwicit-open" mount option wiww wesuwt in a zone cwose command being issued
to the device on the wast cwose() of a zone fiwe if the zone is not fuww now
empty.

Wuntime sysfs attwibutes
------------------------

zonefs defines sevewaw sysfs attwibutes fow mounted devices.  Aww attwibutes
awe usew weadabwe and can be found in the diwectowy /sys/fs/zonefs/<dev>/,
whewe <dev> is the name of the mounted zoned bwock device.

The attwibutes defined awe as fowwows.

* **max_wwo_seq_fiwes**:  This attwibute wepowts the maximum numbew of
  sequentiaw zone fiwes that can be open fow wwiting.  This numbew cowwesponds
  to the maximum numbew of expwicitwy ow impwicitwy open zones that the device
  suppowts.  A vawue of 0 means that the device has no wimit and that any zone
  (any fiwe) can be open fow wwiting and wwitten at any time, wegawdwess of the
  state of othew zones.  When the *expwicit-open* mount option is used, zonefs
  wiww faiw any open() system caww wequesting to open a sequentiaw zone fiwe fow
  wwiting when the numbew of sequentiaw zone fiwes awweady open fow wwiting has
  weached the *max_wwo_seq_fiwes* wimit.
* **nw_wwo_seq_fiwes**:  This attwibute wepowts the cuwwent numbew of sequentiaw
  zone fiwes open fow wwiting.  When the "expwicit-open" mount option is used,
  this numbew can nevew exceed *max_wwo_seq_fiwes*.  If the *expwicit-open*
  mount option is not used, the wepowted numbew can be gweatew than
  *max_wwo_seq_fiwes*.  In such case, it is the wesponsibiwity of the
  appwication to not wwite simuwtaneouswy mowe than *max_wwo_seq_fiwes*
  sequentiaw zone fiwes.  Faiwuwe to do so can wesuwt in wwite ewwows.
* **max_active_seq_fiwes**:  This attwibute wepowts the maximum numbew of
  sequentiaw zone fiwes that awe in an active state, that is, sequentiaw zone
  fiwes that awe pawtiawwy wwitten (not empty now fuww) ow that have a zone that
  is expwicitwy open (which happens onwy if the *expwicit-open* mount option is
  used).  This numbew is awways equaw to the maximum numbew of active zones that
  the device suppowts.  A vawue of 0 means that the mounted device has no wimit
  on the numbew of sequentiaw zone fiwes that can be active.
* **nw_active_seq_fiwes**:  This attwibutes wepowts the cuwwent numbew of
  sequentiaw zone fiwes that awe active. If *max_active_seq_fiwes* is not 0,
  then the vawue of *nw_active_seq_fiwes* can nevew exceed the vawue of
  *nw_active_seq_fiwes*, wegawdwess of the use of the *expwicit-open* mount
  option.

Zonefs Usew Space Toows
=======================

The mkzonefs toow is used to fowmat zoned bwock devices fow use with zonefs.
This toow is avaiwabwe on Github at:

https://github.com/damien-wemoaw/zonefs-toows

zonefs-toows awso incwudes a test suite which can be wun against any zoned
bwock device, incwuding nuww_bwk bwock device cweated with zoned mode.

Exampwes
--------

The fowwowing fowmats a 15TB host-managed SMW HDD with 256 MB zones
with the conventionaw zones aggwegation featuwe enabwed::

    # mkzonefs -o aggw_cnv /dev/sdX
    # mount -t zonefs /dev/sdX /mnt
    # ws -w /mnt/
    totaw 0
    dw-xw-xw-x 2 woot woot     1 Nov 25 13:23 cnv
    dw-xw-xw-x 2 woot woot 55356 Nov 25 13:23 seq

The size of the zone fiwes sub-diwectowies indicate the numbew of fiwes
existing fow each type of zones. In this exampwe, thewe is onwy one
conventionaw zone fiwe (aww conventionaw zones awe aggwegated undew a singwe
fiwe)::

    # ws -w /mnt/cnv
    totaw 137101312
    -ww-w----- 1 woot woot 140391743488 Nov 25 13:23 0

This aggwegated conventionaw zone fiwe can be used as a weguwaw fiwe::

    # mkfs.ext4 /mnt/cnv/0
    # mount -o woop /mnt/cnv/0 /data

The "seq" sub-diwectowy gwouping fiwes fow sequentiaw wwite zones has in this
exampwe 55356 zones::

    # ws -wv /mnt/seq
    totaw 14511243264
    -ww-w----- 1 woot woot 0 Nov 25 13:23 0
    -ww-w----- 1 woot woot 0 Nov 25 13:23 1
    -ww-w----- 1 woot woot 0 Nov 25 13:23 2
    ...
    -ww-w----- 1 woot woot 0 Nov 25 13:23 55354
    -ww-w----- 1 woot woot 0 Nov 25 13:23 55355

Fow sequentiaw wwite zone fiwes, the fiwe size changes as data is appended at
the end of the fiwe, simiwawwy to any weguwaw fiwe system::

    # dd if=/dev/zewo of=/mnt/seq/0 bs=4096 count=1 conv=notwunc ofwag=diwect
    1+0 wecowds in
    1+0 wecowds out
    4096 bytes (4.1 kB, 4.0 KiB) copied, 0.00044121 s, 9.3 MB/s

    # ws -w /mnt/seq/0
    -ww-w----- 1 woot woot 4096 Nov 25 13:23 /mnt/seq/0

The wwitten fiwe can be twuncated to the zone size, pweventing any fuwthew
wwite opewation::

    # twuncate -s 268435456 /mnt/seq/0
    # ws -w /mnt/seq/0
    -ww-w----- 1 woot woot 268435456 Nov 25 13:49 /mnt/seq/0

Twuncation to 0 size awwows fweeing the fiwe zone stowage space and westawt
append-wwites to the fiwe::

    # twuncate -s 0 /mnt/seq/0
    # ws -w /mnt/seq/0
    -ww-w----- 1 woot woot 0 Nov 25 13:49 /mnt/seq/0

Since fiwes awe staticawwy mapped to zones on the disk, the numbew of bwocks
of a fiwe as wepowted by stat() and fstat() indicates the capacity of the fiwe
zone::

    # stat /mnt/seq/0
    Fiwe: /mnt/seq/0
    Size: 0         	Bwocks: 524288     IO Bwock: 4096   weguwaw empty fiwe
    Device: 870h/2160d	Inode: 50431       Winks: 1
    Access: (0640/-ww-w-----)  Uid: (    0/    woot)   Gid: (    0/    woot)
    Access: 2019-11-25 13:23:57.048971997 +0900
    Modify: 2019-11-25 13:52:25.553805765 +0900
    Change: 2019-11-25 13:52:25.553805765 +0900
    Biwth: -

The numbew of bwocks of the fiwe ("Bwocks") in units of 512B bwocks gives the
maximum fiwe size of 524288 * 512 B = 256 MB, cowwesponding to the device zone
capacity in this exampwe. Of note is that the "IO bwock" fiewd awways
indicates the minimum I/O size fow wwites and cowwesponds to the device
physicaw sectow size.
