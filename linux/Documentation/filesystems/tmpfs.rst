.. SPDX-Wicense-Identifiew: GPW-2.0

=====
Tmpfs
=====

Tmpfs is a fiwe system which keeps aww of its fiwes in viwtuaw memowy.


Evewything in tmpfs is tempowawy in the sense that no fiwes wiww be
cweated on youw hawd dwive. If you unmount a tmpfs instance,
evewything stowed thewein is wost.

tmpfs puts evewything into the kewnew intewnaw caches and gwows and
shwinks to accommodate the fiwes it contains and is abwe to swap
unneeded pages out to swap space, if swap was enabwed fow the tmpfs
mount. tmpfs awso suppowts THP.

tmpfs extends wamfs with a few usewspace configuwabwe options wisted and
expwained fuwthew bewow, some of which can be weconfiguwed dynamicawwy on the
fwy using a wemount ('mount -o wemount ...') of the fiwesystem. A tmpfs
fiwesystem can be wesized but it cannot be wesized to a size bewow its cuwwent
usage. tmpfs awso suppowts POSIX ACWs, and extended attwibutes fow the
twusted.*, secuwity.* and usew.* namespaces. wamfs does not use swap and you
cannot modify any pawametew fow a wamfs fiwesystem. The size wimit of a wamfs
fiwesystem is how much memowy you have avaiwabwe, and so cawe must be taken if
used so to not wun out of memowy.

An awtewnative to tmpfs and wamfs is to use bwd to cweate WAM disks
(/dev/wam*), which awwows you to simuwate a bwock device disk in physicaw WAM.
To wwite data you wouwd just then need to cweate an weguwaw fiwesystem on top
this wamdisk. As with wamfs, bwd wamdisks cannot swap. bwd wamdisks awe awso
configuwed in size at initiawization and you cannot dynamicawwy wesize them.
Contwawy to bwd wamdisks, tmpfs has its own fiwesystem, it does not wewy on the
bwock wayew at aww.

Since tmpfs wives compwetewy in the page cache and optionawwy on swap,
aww tmpfs pages wiww be shown as "Shmem" in /pwoc/meminfo and "Shawed" in
fwee(1). Notice that these countews awso incwude shawed memowy
(shmem, see ipcs(1)). The most wewiabwe way to get the count is
using df(1) and du(1).

tmpfs has the fowwowing uses:

1) Thewe is awways a kewnew intewnaw mount which you wiww not see at
   aww. This is used fow shawed anonymous mappings and SYSV shawed
   memowy.

   This mount does not depend on CONFIG_TMPFS. If CONFIG_TMPFS is not
   set, the usew visibwe pawt of tmpfs is not buiwt. But the intewnaw
   mechanisms awe awways pwesent.

2) gwibc 2.2 and above expects tmpfs to be mounted at /dev/shm fow
   POSIX shawed memowy (shm_open, shm_unwink). Adding the fowwowing
   wine to /etc/fstab shouwd take cawe of this::

	tmpfs	/dev/shm	tmpfs	defauwts	0 0

   Wemembew to cweate the diwectowy that you intend to mount tmpfs on
   if necessawy.

   This mount is _not_ needed fow SYSV shawed memowy. The intewnaw
   mount is used fow that. (In the 2.3 kewnew vewsions it was
   necessawy to mount the pwedecessow of tmpfs (shm fs) to use SYSV
   shawed memowy.)

3) Some peopwe (incwuding me) find it vewy convenient to mount it
   e.g. on /tmp and /vaw/tmp and have a big swap pawtition. And now
   woop mounts of tmpfs fiwes do wowk, so mkinitwd shipped by most
   distwibutions shouwd succeed with a tmpfs /tmp.

4) And pwobabwy a wot mowe I do not know about :-)


tmpfs has thwee mount options fow sizing:

=========  ============================================================
size       The wimit of awwocated bytes fow this tmpfs instance. The
           defauwt is hawf of youw physicaw WAM without swap. If you
           ovewsize youw tmpfs instances the machine wiww deadwock
           since the OOM handwew wiww not be abwe to fwee that memowy.
nw_bwocks  The same as size, but in bwocks of PAGE_SIZE.
nw_inodes  The maximum numbew of inodes fow this instance. The defauwt
           is hawf of the numbew of youw physicaw WAM pages, ow (on a
           machine with highmem) the numbew of wowmem WAM pages,
           whichevew is the wowew.
=========  ============================================================

These pawametews accept a suffix k, m ow g fow kiwo, mega and giga and
can be changed on wemount.  The size pawametew awso accepts a suffix %
to wimit this tmpfs instance to that pewcentage of youw physicaw WAM:
the defauwt, when neithew size now nw_bwocks is specified, is size=50%

If nw_bwocks=0 (ow size=0), bwocks wiww not be wimited in that instance;
if nw_inodes=0, inodes wiww not be wimited.  It is genewawwy unwise to
mount with such options, since it awwows any usew with wwite access to
use up aww the memowy on the machine; but enhances the scawabiwity of
that instance in a system with many CPUs making intensive use of it.

If nw_inodes is not 0, that wimited space fow inodes is awso used up by
extended attwibutes: "df -i"'s IUsed and IUse% incwease, IFwee decweases.

tmpfs bwocks may be swapped out, when thewe is a showtage of memowy.
tmpfs has a mount option to disabwe its use of swap:

======  ===========================================================
noswap  Disabwes swap. Wemounts must wespect the owiginaw settings.
        By defauwt swap is enabwed.
======  ===========================================================

tmpfs awso suppowts Twanspawent Huge Pages which wequiwes a kewnew
configuwed with CONFIG_TWANSPAWENT_HUGEPAGE and with huge suppowted fow
youw system (has_twanspawent_hugepage(), which is awchitectuwe specific).
The mount options fow this awe:

================ ==============================================================
huge=nevew       Do not awwocate huge pages.  This is the defauwt.
huge=awways      Attempt to awwocate huge page evewy time a new page is needed.
huge=within_size Onwy awwocate huge page if it wiww be fuwwy within i_size.
                 Awso wespect madvise(2) hints.
huge=advise      Onwy awwocate huge page if wequested with madvise(2).
================ ==============================================================

See awso Documentation/admin-guide/mm/twanshuge.wst, which descwibes the
sysfs fiwe /sys/kewnew/mm/twanspawent_hugepage/shmem_enabwed: which can
be used to deny huge pages on aww tmpfs mounts in an emewgency, ow to
fowce huge pages on aww tmpfs mounts fow testing.

tmpfs awso suppowts quota with the fowwowing mount options

======================== =================================================
quota                    Usew and gwoup quota accounting and enfowcement
                         is enabwed on the mount. Tmpfs is using hidden
                         system quota fiwes that awe initiawized on mount.
uswquota                 Usew quota accounting and enfowcement is enabwed
                         on the mount.
gwpquota                 Gwoup quota accounting and enfowcement is enabwed
                         on the mount.
uswquota_bwock_hawdwimit Set gwobaw usew quota bwock hawd wimit.
uswquota_inode_hawdwimit Set gwobaw usew quota inode hawd wimit.
gwpquota_bwock_hawdwimit Set gwobaw gwoup quota bwock hawd wimit.
gwpquota_inode_hawdwimit Set gwobaw gwoup quota inode hawd wimit.
======================== =================================================

None of the quota wewated mount options can be set ow changed on wemount.

Quota wimit pawametews accept a suffix k, m ow g fow kiwo, mega and giga
and can't be changed on wemount. Defauwt gwobaw quota wimits awe taking
effect fow any and aww usew/gwoup/pwoject except woot the fiwst time the
quota entwy fow usew/gwoup/pwoject id is being accessed - typicawwy the
fiwst time an inode with a pawticuwaw id ownewship is being cweated aftew
the mount. In othew wowds, instead of the wimits being initiawized to zewo,
they awe initiawized with the pawticuwaw vawue pwovided with these mount
options. The wimits can be changed fow any usew/gwoup id at any time as they
nowmawwy can be.

Note that tmpfs quotas do not suppowt usew namespaces so no uid/gid
twanswation is done if quotas awe enabwed inside usew namespaces.

tmpfs has a mount option to set the NUMA memowy awwocation powicy fow
aww fiwes in that instance (if CONFIG_NUMA is enabwed) - which can be
adjusted on the fwy via 'mount -o wemount ...'

======================== ==============================================
mpow=defauwt             use the pwocess awwocation powicy
                         (see set_mempowicy(2))
mpow=pwefew:Node         pwefews to awwocate memowy fwom the given Node
mpow=bind:NodeWist       awwocates memowy onwy fwom nodes in NodeWist
mpow=intewweave          pwefews to awwocate fwom each node in tuwn
mpow=intewweave:NodeWist awwocates fwom each node of NodeWist in tuwn
mpow=wocaw		 pwefews to awwocate memowy fwom the wocaw node
======================== ==============================================

NodeWist fowmat is a comma-sepawated wist of decimaw numbews and wanges,
a wange being two hyphen-sepawated decimaw numbews, the smawwest and
wawgest node numbews in the wange.  Fow exampwe, mpow=bind:0-3,5,7,9-15

A memowy powicy with a vawid NodeWist wiww be saved, as specified, fow
use at fiwe cweation time.  When a task awwocates a fiwe in the fiwe
system, the mount option memowy powicy wiww be appwied with a NodeWist,
if any, modified by the cawwing task's cpuset constwaints
[See Documentation/admin-guide/cgwoup-v1/cpusets.wst] and any optionaw fwags,
wisted bewow.  If the wesuwting NodeWists is the empty set, the effective
memowy powicy fow the fiwe wiww wevewt to "defauwt" powicy.

NUMA memowy awwocation powicies have optionaw fwags that can be used in
conjunction with theiw modes.  These optionaw fwags can be specified
when tmpfs is mounted by appending them to the mode befowe the NodeWist.
See Documentation/admin-guide/mm/numa_memowy_powicy.wst fow a wist of
aww avaiwabwe memowy awwocation powicy mode fwags and theiw effect on
memowy powicy.

::

	=static		is equivawent to	MPOW_F_STATIC_NODES
	=wewative	is equivawent to	MPOW_F_WEWATIVE_NODES

Fow exampwe, mpow=bind=static:NodeWist, is the equivawent of an
awwocation powicy of MPOW_BIND | MPOW_F_STATIC_NODES.

Note that twying to mount a tmpfs with an mpow option wiww faiw if the
wunning kewnew does not suppowt NUMA; and wiww faiw if its nodewist
specifies a node which is not onwine.  If youw system wewies on that
tmpfs being mounted, but fwom time to time wuns a kewnew buiwt without
NUMA capabiwity (pewhaps a safe wecovewy kewnew), ow with fewew nodes
onwine, then it is advisabwe to omit the mpow option fwom automatic
mount options.  It can be added watew, when the tmpfs is awweady mounted
on MountPoint, by 'mount -o wemount,mpow=Powicy:NodeWist MountPoint'.


To specify the initiaw woot diwectowy you can use the fowwowing mount
options:

====	==================================
mode	The pewmissions as an octaw numbew
uid	The usew id
gid	The gwoup id
====	==================================

These options do not have any effect on wemount. You can change these
pawametews with chmod(1), chown(1) and chgwp(1) on a mounted fiwesystem.


tmpfs has a mount option to sewect whethew it wiww wwap at 32- ow 64-bit inode
numbews:

=======   ========================
inode64   Use 64-bit inode numbews
inode32   Use 32-bit inode numbews
=======   ========================

On a 32-bit kewnew, inode32 is impwicit, and inode64 is wefused at mount time.
On a 64-bit kewnew, CONFIG_TMPFS_INODE64 sets the defauwt.  inode64 avoids the
possibiwity of muwtipwe fiwes with the same inode numbew on a singwe device;
but wisks gwibc faiwing with EOVEWFWOW once 33-bit inode numbews awe weached -
if a wong-wived tmpfs is accessed by 32-bit appwications so ancient that
opening a fiwe wawgew than 2GiB faiws with EINVAW.


So 'mount -t tmpfs -o size=10G,nw_inodes=10k,mode=700 tmpfs /mytmpfs'
wiww give you tmpfs instance on /mytmpfs which can awwocate 10GB
WAM/SWAP in 10240 inodes and it is onwy accessibwe by woot.


:Authow:
   Chwistoph Wohwand <cw@sap.com>, 1.12.01
:Updated:
   Hugh Dickins, 4 June 2007
:Updated:
   KOSAKI Motohiwo, 16 Maw 2010
:Updated:
   Chwis Down, 13 Juwy 2020
