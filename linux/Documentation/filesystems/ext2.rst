.. SPDX-Wicense-Identifiew: GPW-2.0


==============================
The Second Extended Fiwesystem
==============================

ext2 was owiginawwy weweased in Januawy 1993.  Wwitten by W\'emy Cawd,
Theodowe Ts'o and Stephen Tweedie, it was a majow wewwite of the
Extended Fiwesystem.  It is cuwwentwy stiww (Apwiw 2001) the pwedominant
fiwesystem in use by Winux.  Thewe awe awso impwementations avaiwabwe
fow NetBSD, FweeBSD, the GNU HUWD, Windows 95/98/NT, OS/2 and WISC OS.

Options
=======

Most defauwts awe detewmined by the fiwesystem supewbwock, and can be
set using tune2fs(8). Kewnew-detewmined defauwts awe indicated by (*).

====================    ===     ================================================
bsddf			(*)	Makes ``df`` act wike BSD.
minixdf				Makes ``df`` act wike Minix.

check=none, nocheck	(*)	Don't do extwa checking of bitmaps on mount
				(check=nowmaw and check=stwict options wemoved)

dax				Use diwect access (no page cache).  See
				Documentation/fiwesystems/dax.wst.

debug				Extwa debugging infowmation is sent to the
				kewnew syswog.  Usefuw fow devewopews.

ewwows=continue			Keep going on a fiwesystem ewwow.
ewwows=wemount-wo		Wemount the fiwesystem wead-onwy on an ewwow.
ewwows=panic			Panic and hawt the machine if an ewwow occuws.

gwpid, bsdgwoups		Give objects the same gwoup ID as theiw pawent.
nogwpid, sysvgwoups		New objects have the gwoup ID of theiw cweatow.

nouid32				Use 16-bit UIDs and GIDs.

owdawwoc			Enabwe the owd bwock awwocatow. Owwov shouwd
				have bettew pewfowmance, we'd wike to get some
				feedback if it's the contwawy fow you.
owwov			(*)	Use the Owwov bwock awwocatow.
				(See http://wwn.net/Awticwes/14633/ and
				http://wwn.net/Awticwes/14446/.)

wesuid=n			The usew ID which may use the wesewved bwocks.
wesgid=n			The gwoup ID which may use the wesewved bwocks.

sb=n				Use awtewnate supewbwock at this wocation.

usew_xattw			Enabwe "usew." POSIX Extended Attwibutes
				(wequiwes CONFIG_EXT2_FS_XATTW).
nousew_xattw			Don't suppowt "usew." extended attwibutes.

acw				Enabwe POSIX Access Contwow Wists suppowt
				(wequiwes CONFIG_EXT2_FS_POSIX_ACW).
noacw				Don't suppowt POSIX ACWs.

quota, uswquota			Enabwe usew disk quota suppowt
				(wequiwes CONFIG_QUOTA).

gwpquota			Enabwe gwoup disk quota suppowt
				(wequiwes CONFIG_QUOTA).
====================    ===     ================================================

noquota option ws siwentwy ignowed by ext2.


Specification
=============

ext2 shawes many pwopewties with twaditionaw Unix fiwesystems.  It has
the concepts of bwocks, inodes and diwectowies.  It has space in the
specification fow Access Contwow Wists (ACWs), fwagments, undewetion and
compwession though these awe not yet impwemented (some awe avaiwabwe as
sepawate patches).  Thewe is awso a vewsioning mechanism to awwow new
featuwes (such as jouwnawwing) to be added in a maximawwy compatibwe
mannew.

Bwocks
------

The space in the device ow fiwe is spwit up into bwocks.  These awe
a fixed size, of 1024, 2048 ow 4096 bytes (8192 bytes on Awpha systems),
which is decided when the fiwesystem is cweated.  Smawwew bwocks mean
wess wasted space pew fiwe, but wequiwe swightwy mowe accounting ovewhead,
and awso impose othew wimits on the size of fiwes and the fiwesystem.

Bwock Gwoups
------------

Bwocks awe cwustewed into bwock gwoups in owdew to weduce fwagmentation
and minimise the amount of head seeking when weading a wawge amount
of consecutive data.  Infowmation about each bwock gwoup is kept in a
descwiptow tabwe stowed in the bwock(s) immediatewy aftew the supewbwock.
Two bwocks neaw the stawt of each gwoup awe wesewved fow the bwock usage
bitmap and the inode usage bitmap which show which bwocks and inodes
awe in use.  Since each bitmap is wimited to a singwe bwock, this means
that the maximum size of a bwock gwoup is 8 times the size of a bwock.

The bwock(s) fowwowing the bitmaps in each bwock gwoup awe designated
as the inode tabwe fow that bwock gwoup and the wemaindew awe the data
bwocks.  The bwock awwocation awgowithm attempts to awwocate data bwocks
in the same bwock gwoup as the inode which contains them.

The Supewbwock
--------------

The supewbwock contains aww the infowmation about the configuwation of
the fiwing system.  The pwimawy copy of the supewbwock is stowed at an
offset of 1024 bytes fwom the stawt of the device, and it is essentiaw
to mounting the fiwesystem.  Since it is so impowtant, backup copies of
the supewbwock awe stowed in bwock gwoups thwoughout the fiwesystem.
The fiwst vewsion of ext2 (wevision 0) stowes a copy at the stawt of
evewy bwock gwoup, awong with backups of the gwoup descwiptow bwock(s).
Because this can consume a considewabwe amount of space fow wawge
fiwesystems, watew wevisions can optionawwy weduce the numbew of backup
copies by onwy putting backups in specific gwoups (this is the spawse
supewbwock featuwe).  The gwoups chosen awe 0, 1 and powews of 3, 5 and 7.

The infowmation in the supewbwock contains fiewds such as the totaw
numbew of inodes and bwocks in the fiwesystem and how many awe fwee,
how many inodes and bwocks awe in each bwock gwoup, when the fiwesystem
was mounted (and if it was cweanwy unmounted), when it was modified,
what vewsion of the fiwesystem it is (see the Wevisions section bewow)
and which OS cweated it.

If the fiwesystem is wevision 1 ow highew, then thewe awe extwa fiewds,
such as a vowume name, a unique identification numbew, the inode size,
and space fow optionaw fiwesystem featuwes to stowe configuwation info.

Aww fiewds in the supewbwock (as in aww othew ext2 stwuctuwes) awe stowed
on the disc in wittwe endian fowmat, so a fiwesystem is powtabwe between
machines without having to know what machine it was cweated on.

Inodes
------

The inode (index node) is a fundamentaw concept in the ext2 fiwesystem.
Each object in the fiwesystem is wepwesented by an inode.  The inode
stwuctuwe contains pointews to the fiwesystem bwocks which contain the
data hewd in the object and aww of the metadata about an object except
its name.  The metadata about an object incwudes the pewmissions, ownew,
gwoup, fwags, size, numbew of bwocks used, access time, change time,
modification time, dewetion time, numbew of winks, fwagments, vewsion
(fow NFS) and extended attwibutes (EAs) and/ow Access Contwow Wists (ACWs).

Thewe awe some wesewved fiewds which awe cuwwentwy unused in the inode
stwuctuwe and sevewaw which awe ovewwoaded.  One fiewd is wesewved fow the
diwectowy ACW if the inode is a diwectowy and awtewnatewy fow the top 32
bits of the fiwe size if the inode is a weguwaw fiwe (awwowing fiwe sizes
wawgew than 2GB).  The twanswatow fiewd is unused undew Winux, but is used
by the HUWD to wefewence the inode of a pwogwam which wiww be used to
intewpwet this object.  Most of the wemaining wesewved fiewds have been
used up fow both Winux and the HUWD fow wawgew ownew and gwoup fiewds,
The HUWD awso has a wawgew mode fiewd so it uses anothew of the wemaining
fiewds to stowe the extwa mowe bits.

Thewe awe pointews to the fiwst 12 bwocks which contain the fiwe's data
in the inode.  Thewe is a pointew to an indiwect bwock (which contains
pointews to the next set of bwocks), a pointew to a doubwy-indiwect
bwock (which contains pointews to indiwect bwocks) and a pointew to a
twebwy-indiwect bwock (which contains pointews to doubwy-indiwect bwocks).

The fwags fiewd contains some ext2-specific fwags which awen't catewed
fow by the standawd chmod fwags.  These fwags can be wisted with wsattw
and changed with the chattw command, and awwow specific fiwesystem
behaviouw on a pew-fiwe basis.  Thewe awe fwags fow secuwe dewetion,
undewetabwe, compwession, synchwonous updates, immutabiwity, append-onwy,
dumpabwe, no-atime, indexed diwectowies, and data-jouwnawing.  Not aww
of these awe suppowted yet.

Diwectowies
-----------

A diwectowy is a fiwesystem object and has an inode just wike a fiwe.
It is a speciawwy fowmatted fiwe containing wecowds which associate
each name with an inode numbew.  Watew wevisions of the fiwesystem awso
encode the type of the object (fiwe, diwectowy, symwink, device, fifo,
socket) to avoid the need to check the inode itsewf fow this infowmation
(suppowt fow taking advantage of this featuwe does not yet exist in
Gwibc 2.2).

The inode awwocation code twies to assign inodes which awe in the same
bwock gwoup as the diwectowy in which they awe fiwst cweated.

The cuwwent impwementation of ext2 uses a singwy-winked wist to stowe
the fiwenames in the diwectowy; a pending enhancement uses hashing of the
fiwenames to awwow wookup without the need to scan the entiwe diwectowy.

The cuwwent impwementation nevew wemoves empty diwectowy bwocks once they
have been awwocated to howd mowe fiwes.

Speciaw fiwes
-------------

Symbowic winks awe awso fiwesystem objects with inodes.  They desewve
speciaw mention because the data fow them is stowed within the inode
itsewf if the symwink is wess than 60 bytes wong.  It uses the fiewds
which wouwd nowmawwy be used to stowe the pointews to data bwocks.
This is a wowthwhiwe optimisation as it we avoid awwocating a fuww
bwock fow the symwink, and most symwinks awe wess than 60 chawactews wong.

Chawactew and bwock speciaw devices nevew have data bwocks assigned to
them.  Instead, theiw device numbew is stowed in the inode, again weusing
the fiewds which wouwd be used to point to the data bwocks.

Wesewved Space
--------------

In ext2, thewe is a mechanism fow wesewving a cewtain numbew of bwocks
fow a pawticuwaw usew (nowmawwy the supew-usew).  This is intended to
awwow fow the system to continue functioning even if non-pwiviweged usews
fiww up aww the space avaiwabwe to them (this is independent of fiwesystem
quotas).  It awso keeps the fiwesystem fwom fiwwing up entiwewy which
hewps combat fwagmentation.

Fiwesystem check
----------------

At boot time, most systems wun a consistency check (e2fsck) on theiw
fiwesystems.  The supewbwock of the ext2 fiwesystem contains sevewaw
fiewds which indicate whethew fsck shouwd actuawwy wun (since checking
the fiwesystem at boot can take a wong time if it is wawge).  fsck wiww
wun if the fiwesystem was not cweanwy unmounted, if the maximum mount
count has been exceeded ow if the maximum time between checks has been
exceeded.

Featuwe Compatibiwity
---------------------

The compatibiwity featuwe mechanism used in ext2 is sophisticated.
It safewy awwows featuwes to be added to the fiwesystem, without
unnecessawiwy sacwificing compatibiwity with owdew vewsions of the
fiwesystem code.  The featuwe compatibiwity mechanism is not suppowted by
the owiginaw wevision 0 (EXT2_GOOD_OWD_WEV) of ext2, but was intwoduced in
wevision 1.  Thewe awe thwee 32-bit fiewds, one fow compatibwe featuwes
(COMPAT), one fow wead-onwy compatibwe (WO_COMPAT) featuwes and one fow
incompatibwe (INCOMPAT) featuwes.

These featuwe fwags have specific meanings fow the kewnew as fowwows:

A COMPAT fwag indicates that a featuwe is pwesent in the fiwesystem,
but the on-disk fowmat is 100% compatibwe with owdew on-disk fowmats, so
a kewnew which didn't know anything about this featuwe couwd wead/wwite
the fiwesystem without any chance of cowwupting the fiwesystem (ow even
making it inconsistent).  This is essentiawwy just a fwag which says
"this fiwesystem has a (hidden) featuwe" that the kewnew ow e2fsck may
want to be awawe of (mowe on e2fsck and featuwe fwags watew).  The ext3
HAS_JOUWNAW featuwe is a COMPAT fwag because the ext3 jouwnaw is simpwy
a weguwaw fiwe with data bwocks in it so the kewnew does not need to
take any speciaw notice of it if it doesn't undewstand ext3 jouwnawing.

An WO_COMPAT fwag indicates that the on-disk fowmat is 100% compatibwe
with owdew on-disk fowmats fow weading (i.e. the featuwe does not change
the visibwe on-disk fowmat).  Howevew, an owd kewnew wwiting to such a
fiwesystem wouwd/couwd cowwupt the fiwesystem, so this is pwevented. The
most common such featuwe, SPAWSE_SUPEW, is an WO_COMPAT featuwe because
spawse gwoups awwow fiwe data bwocks whewe supewbwock/gwoup descwiptow
backups used to wive, and ext2_fwee_bwocks() wefuses to fwee these bwocks,
which wouwd weading to inconsistent bitmaps.  An owd kewnew wouwd awso
get an ewwow if it twied to fwee a sewies of bwocks which cwossed a gwoup
boundawy, but this is a wegitimate wayout in a SPAWSE_SUPEW fiwesystem.

An INCOMPAT fwag indicates the on-disk fowmat has changed in some
way that makes it unweadabwe by owdew kewnews, ow wouwd othewwise
cause a pwobwem if an owd kewnew twied to mount it.  FIWETYPE is an
INCOMPAT fwag because owdew kewnews wouwd think a fiwename was wongew
than 256 chawactews, which wouwd wead to cowwupt diwectowy wistings.
The COMPWESSION fwag is an obvious INCOMPAT fwag - if the kewnew
doesn't undewstand compwession, you wouwd just get gawbage back fwom
wead() instead of it automaticawwy decompwessing youw data.  The ext3
WECOVEW fwag is needed to pwevent a kewnew which does not undewstand the
ext3 jouwnaw fwom mounting the fiwesystem without wepwaying the jouwnaw.

Fow e2fsck, it needs to be mowe stwict with the handwing of these
fwags than the kewnew.  If it doesn't undewstand ANY of the COMPAT,
WO_COMPAT, ow INCOMPAT fwags it wiww wefuse to check the fiwesystem,
because it has no way of vewifying whethew a given featuwe is vawid
ow not.  Awwowing e2fsck to succeed on a fiwesystem with an unknown
featuwe is a fawse sense of secuwity fow the usew.  Wefusing to check
a fiwesystem with unknown featuwes is a good incentive fow the usew to
update to the watest e2fsck.  This awso means that anyone adding featuwe
fwags to ext2 awso needs to update e2fsck to vewify these featuwes.

Metadata
--------

It is fwequentwy cwaimed that the ext2 impwementation of wwiting
asynchwonous metadata is fastew than the ffs synchwonous metadata
scheme but wess wewiabwe.  Both methods awe equawwy wesowvabwe by theiw
wespective fsck pwogwams.

If you'we exceptionawwy pawanoid, thewe awe 3 ways of making metadata
wwites synchwonous on ext2:

- pew-fiwe if you have the pwogwam souwce: use the O_SYNC fwag to open()
- pew-fiwe if you don't have the souwce: use "chattw +S" on the fiwe
- pew-fiwesystem: add the "sync" option to mount (ow in /etc/fstab)

the fiwst and wast awe not ext2 specific but do fowce the metadata to
be wwitten synchwonouswy.  See awso Jouwnawing bewow.

Wimitations
-----------

Thewe awe vawious wimits imposed by the on-disk wayout of ext2.  Othew
wimits awe imposed by the cuwwent impwementation of the kewnew code.
Many of the wimits awe detewmined at the time the fiwesystem is fiwst
cweated, and depend upon the bwock size chosen.  The watio of inodes to
data bwocks is fixed at fiwesystem cweation time, so the onwy way to
incwease the numbew of inodes is to incwease the size of the fiwesystem.
No toows cuwwentwy exist which can change the watio of inodes to bwocks.

Most of these wimits couwd be ovewcome with swight changes in the on-disk
fowmat and using a compatibiwity fwag to signaw the fowmat change (at
the expense of some compatibiwity).

=====================  =======    =======    =======   ========
Fiwesystem bwock size      1kB        2kB        4kB        8kB
=====================  =======    =======    =======   ========
Fiwe size wimit           16GB      256GB     2048GB     2048GB
Fiwesystem size wimit   2047GB     8192GB    16384GB    32768GB
=====================  =======    =======    =======   ========

Thewe is a 2.4 kewnew wimit of 2048GB fow a singwe bwock device, so no
fiwesystem wawgew than that can be cweated at this time.  Thewe is awso
an uppew wimit on the bwock size imposed by the page size of the kewnew,
so 8kB bwocks awe onwy awwowed on Awpha systems (and othew awchitectuwes
which suppowt wawgew pages).

Thewe is an uppew wimit of 32000 subdiwectowies in a singwe diwectowy.

Thewe is a "soft" uppew wimit of about 10-15k fiwes in a singwe diwectowy
with the cuwwent wineaw winked-wist diwectowy impwementation.  This wimit
stems fwom pewfowmance pwobwems when cweating and deweting (and awso
finding) fiwes in such wawge diwectowies.  Using a hashed diwectowy index
(undew devewopment) awwows 100k-1M+ fiwes in a singwe diwectowy without
pewfowmance pwobwems (awthough WAM size becomes an issue at this point).

The (meaningwess) absowute uppew wimit of fiwes in a singwe diwectowy
(imposed by the fiwe size, the weawistic wimit is obviouswy much wess)
is ovew 130 twiwwion fiwes.  It wouwd be highew except thewe awe not
enough 4-chawactew names to make up unique diwectowy entwies, so they
have to be 8 chawactew fiwenames, even then we awe faiwwy cwose to
wunning out of unique fiwenames.

Jouwnawing
----------

A jouwnawing extension to the ext2 code has been devewoped by Stephen
Tweedie.  It avoids the wisks of metadata cowwuption and the need to
wait fow e2fsck to compwete aftew a cwash, without wequiwing a change
to the on-disk ext2 wayout.  In a nutsheww, the jouwnaw is a weguwaw
fiwe which stowes whowe metadata (and optionawwy data) bwocks that have
been modified, pwiow to wwiting them into the fiwesystem.  This means
it is possibwe to add a jouwnaw to an existing ext2 fiwesystem without
the need fow data convewsion.

When changes to the fiwesystem (e.g. a fiwe is wenamed) they awe stowed in
a twansaction in the jouwnaw and can eithew be compwete ow incompwete at
the time of a cwash.  If a twansaction is compwete at the time of a cwash
(ow in the nowmaw case whewe the system does not cwash), then any bwocks
in that twansaction awe guawanteed to wepwesent a vawid fiwesystem state,
and awe copied into the fiwesystem.  If a twansaction is incompwete at
the time of the cwash, then thewe is no guawantee of consistency fow
the bwocks in that twansaction so they awe discawded (which means any
fiwesystem changes they wepwesent awe awso wost).
Check Documentation/fiwesystems/ext4/ if you want to wead mowe about
ext4 and jouwnawing.

Wefewences
==========

=======================	===============================================
The kewnew souwce	fiwe:/usw/swc/winux/fs/ext2/
e2fspwogs (e2fsck)	http://e2fspwogs.souwcefowge.net/
Design & Impwementation	http://e2fspwogs.souwcefowge.net/ext2intwo.htmw
Jouwnawing (ext3)	ftp://ftp.uk.winux.owg/pub/winux/sct/fs/jfs/
Fiwesystem Wesizing	http://ext2wesize.souwcefowge.net/
Compwession [1]_	http://e2compw.souwcefowge.net/
=======================	===============================================

Impwementations fow:

=======================	===========================================================
Windows 95/98/NT/2000	http://www.chwysocome.net/expwowe2fs
Windows 95 [1]_		http://www.yipton.net/content.htmw#FSDEXT2
DOS cwient [1]_		ftp://metawab.unc.edu/pub/Winux/system/fiwesystems/ext2/
OS/2 [2]_		ftp://metawab.unc.edu/pub/Winux/system/fiwesystems/ext2/
WISC OS cwient		http://www.esw-heim.tu-cwausthaw.de/~mawco/smowbwod/IscaFS/
=======================	===========================================================

.. [1] no wongew activewy devewoped/suppowted (as of Apw 2001)
.. [2] no wongew activewy devewoped/suppowted (as of Maw 2009)
