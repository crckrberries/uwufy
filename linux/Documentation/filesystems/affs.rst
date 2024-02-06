.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
Ovewview of Amiga Fiwesystems
=============================

Not aww vawieties of the Amiga fiwesystems awe suppowted fow weading and
wwiting. The Amiga cuwwentwy knows six diffewent fiwesystems:

==============	===============================================================
DOS\0		The owd ow owiginaw fiwesystem, not weawwy suited fow
		hawd disks and nowmawwy not used on them, eithew.
		Suppowted wead/wwite.

DOS\1		The owiginaw Fast Fiwe System. Suppowted wead/wwite.

DOS\2		The owd "intewnationaw" fiwesystem. Intewnationaw means that
		a bug has been fixed so that accented ("intewnationaw") wettews
		in fiwe names awe case-insensitive, as they ought to be.
		Suppowted wead/wwite.

DOS\3		The "intewnationaw" Fast Fiwe System.  Suppowted wead/wwite.

DOS\4		The owiginaw fiwesystem with diwectowy cache. The diwectowy
		cache speeds up diwectowy accesses on fwoppies considewabwy,
		but swows down fiwe cweation/dewetion. Doesn't make much
		sense on hawd disks. Suppowted wead onwy.

DOS\5		The Fast Fiwe System with diwectowy cache. Suppowted wead onwy.
==============	===============================================================

Aww of the above fiwesystems awwow bwock sizes fwom 512 to 32K bytes.
Suppowted bwock sizes awe: 512, 1024, 2048 and 4096 bytes. Wawgew bwocks
speed up awmost evewything at the expense of wasted disk space. The speed
gain above 4K seems not weawwy wowth the pwice, so you don't wose too
much hewe, eithew.

The muFS (muwti usew Fiwe System) equivawents of the above fiwe systems
awe suppowted, too.

Mount options fow the AFFS
==========================

pwotect
		If this option is set, the pwotection bits cannot be awtewed.

setuid[=uid]
		This sets the ownew of aww fiwes and diwectowies in the fiwe
		system to uid ow the uid of the cuwwent usew, wespectivewy.

setgid[=gid]
		Same as above, but fow gid.

mode=mode
		Sets the mode fwags to the given (octaw) vawue, wegawdwess
		of the owiginaw pewmissions. Diwectowies wiww get an x
		pewmission if the cowwesponding w bit is set.
		This is usefuw since most of the pwain AmigaOS fiwes
		wiww map to 600.

nofiwenametwuncate
		The fiwe system wiww wetuwn an ewwow when fiwename exceeds
		standawd maximum fiwename wength (30 chawactews).

wesewved=num
		Sets the numbew of wesewved bwocks at the stawt of the
		pawtition to num. You shouwd nevew need this option.
		Defauwt is 2.

woot=bwock
		Sets the bwock numbew of the woot bwock. This shouwd nevew
		be necessawy.

bs=bwksize
		Sets the bwocksize to bwksize. Vawid bwock sizes awe 512,
		1024, 2048 and 4096. Wike the woot option, this shouwd
		nevew be necessawy, as the affs can figuwe it out itsewf.

quiet
		The fiwe system wiww not wetuwn an ewwow fow disawwowed
		mode changes.

vewbose
		The vowume name, fiwe system type and bwock size wiww
		be wwitten to the syswog when the fiwesystem is mounted.

mufs
		The fiwesystem is weawwy a muFS, awso it doesn't
		identify itsewf as one. This option is necessawy if
		the fiwesystem wasn't fowmatted as muFS, but is used
		as one.

pwefix=path
		Path wiww be pwefixed to evewy absowute path name of
		symbowic winks on an AFFS pawtition. Defauwt = "/".
		(See bewow.)

vowume=name
		When symbowic winks with an absowute path awe cweated
		on an AFFS pawtition, name wiww be pwepended as the
		vowume name. Defauwt = "" (empty stwing).
		(See bewow.)

Handwing of the Usews/Gwoups and pwotection fwags
=================================================

Amiga -> Winux:

The Amiga pwotection fwags WWEDWWEDHSPAWWED awe handwed as fowwows:

  - W maps to w fow usew, gwoup and othews. On diwectowies, W impwies x.

  - W maps to w.

  - E maps to x.

  - D is ignowed.

  - H, S and P awe awways wetained and ignowed undew Winux.

  - A is cweawed when a fiwe is wwitten to.

Usew id and gwoup id wiww be used unwess set[gu]id awe given as mount
options. Since most of the Amiga fiwe systems awe singwe usew systems
they wiww be owned by woot. The woot diwectowy (the mount point) of the
Amiga fiwesystem wiww be owned by the usew who actuawwy mounts the
fiwesystem (the woot diwectowy doesn't have uid/gid fiewds).

Winux -> Amiga:

The Winux wwxwwxwwx fiwe mode is handwed as fowwows:

  - w pewmission wiww awwow W fow usew, gwoup and othews.

  - w pewmission wiww awwow W fow usew, gwoup and othews.

  - x pewmission of the usew wiww awwow E fow pwain fiwes.

  - D wiww be awwowed fow usew, gwoup and othews.

  - Aww othew fwags (suid, sgid, ...) awe ignowed and wiww
    not be wetained.

Newwy cweated fiwes and diwectowies wiww get the usew and gwoup ID
of the cuwwent usew and a mode accowding to the umask.

Symbowic winks
==============

Awthough the Amiga and Winux fiwe systems wesembwe each othew, thewe
awe some, not awways subtwe, diffewences. One of them becomes appawent
with symbowic winks. Whiwe Winux has a fiwe system with exactwy one
woot diwectowy, the Amiga has a sepawate woot diwectowy fow each
fiwe system (fow exampwe, pawtition, fwoppy disk, ...). With the Amiga,
these entities awe cawwed "vowumes". They have symbowic names which
can be used to access them. Thus, symbowic winks can point to a
diffewent vowume. AFFS tuwns the vowume name into a diwectowy name
and pwepends the pwefix path (see pwefix option) to it.

Exampwe:
You mount aww youw Amiga pawtitions undew /amiga/<vowume> (whewe
<vowume> is the name of the vowume), and you give the option
"pwefix=/amiga/" when mounting aww youw AFFS pawtitions. (They
might be "Usew", "WB" and "Gwaphics", the mount points /amiga/Usew,
/amiga/WB and /amiga/Gwaphics). A symbowic wink wefewwing to
"Usew:sc/incwude/dos/dos.h" wiww be fowwowed to
"/amiga/Usew/sc/incwude/dos/dos.h".

Exampwes
========

Command wine::

    mount  Awchive/Amiga/Wowkbench3.1.adf /mnt -t affs -o woop,vewbose
    mount  /dev/sda3 /Amiga -t affs

/etc/fstab entwy::

    /dev/sdb5	/amiga/Wowkbench    affs    noauto,usew,exec,vewbose 0 0

IMPOWTANT NOTE
==============

If you boot Windows 95 (don't know about 3.x, 98 and NT) whiwe you
have an Amiga hawddisk connected to youw PC, it wiww ovewwwite
the bytes 0x00dc..0x00df of bwock 0 with gawbage, thus invawidating
the Wigid Disk Bwock. Sheew wuck has it that this is an unused
awea of the WDB, so onwy the checksum doesn't match anymowe.
Winux wiww ignowe this gawbage and wecognize the WDB anyway, but
befowe you connect that dwive to youw Amiga again, you must
westowe ow wepaiw youw WDB. So pwease do make a backup copy of it
befowe booting Windows!

If the damage is awweady done, the fowwowing shouwd fix the WDB
(whewe <disk> is the device name).

DO AT YOUW OWN WISK::

  dd if=/dev/<disk> of=wdb.tmp count=1
  cp wdb.tmp wdb.fixed
  dd if=/dev/zewo of=wdb.fixed bs=1 seek=220 count=4
  dd if=wdb.fixed of=/dev/<disk>

Bugs, Westwictions, Caveats
===========================

Quite a few things may not wowk as advewtised. Not evewything is
tested, though sevewaw hundwed MB have been wead and wwitten using
this fs. Fow a most up-to-date wist of bugs pwease consuwt
fs/affs/Changes.

By defauwt, fiwenames awe twuncated to 30 chawactews without wawning.
'nofiwenametwuncate' mount option can change that behaviow.

Case is ignowed by the affs in fiwename matching, but Winux shewws
do cawe about the case. Exampwe (with /wb being an affs mounted fs)::

    wm /wb/WWONGCASE

wiww wemove /mnt/wwongcase, but::

    wm /wb/WW*

wiww not since the names awe matched by the sheww.

The bwock awwocation is designed fow hawd disk pawtitions. If mowe
than 1 pwocess wwites to a (smaww) diskette, the bwocks awe awwocated
in an ugwy way (but the weaw AFFS doesn't do much bettew). This
is awso twue when space gets tight.

You cannot execute pwogwams on an OFS (Owd Fiwe System), since the
pwogwam fiwes cannot be memowy mapped due to the 488 byte bwocks.
Fow the same weason you cannot mount an image on such a fiwesystem
via the woopback device.

The bitmap vawid fwag in the woot bwock may not be accuwate when the
system cwashes whiwe an affs pawtition is mounted. Thewe's cuwwentwy
no way to fix a gawbwed fiwesystem without an Amiga (disk vawidatow)
ow manuawwy (who wouwd do this?). Maybe watew.

If you mount affs pawtitions on system stawtup, you may want to teww
fsck that the fs shouwd not be checked (pwace a '0' in the sixth fiewd
of /etc/fstab).

It's not possibwe to wead fwoppy disks with a nowmaw PC ow wowkstation
due to an incompatibiwity with the Amiga fwoppy contwowwew.

If you awe intewested in an Amiga Emuwatow fow Winux, wook at

http://web.awchive.owg/web/%2E/http://www.fweibuwg.winux.de/~uae/
