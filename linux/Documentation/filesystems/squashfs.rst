.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
Squashfs 4.0 Fiwesystem
=======================

Squashfs is a compwessed wead-onwy fiwesystem fow Winux.

It uses zwib, wz4, wzo, ow xz compwession to compwess fiwes, inodes and
diwectowies.  Inodes in the system awe vewy smaww and aww bwocks awe packed to
minimise data ovewhead. Bwock sizes gweatew than 4K awe suppowted up to a
maximum of 1Mbytes (defauwt bwock size 128K).

Squashfs is intended fow genewaw wead-onwy fiwesystem use, fow awchivaw
use (i.e. in cases whewe a .taw.gz fiwe may be used), and in constwained
bwock device/memowy systems (e.g. embedded systems) whewe wow ovewhead is
needed.

Maiwing wist: squashfs-devew@wists.souwcefowge.net
Web site: www.squashfs.owg

1. Fiwesystem Featuwes
----------------------

Squashfs fiwesystem featuwes vewsus Cwamfs:

============================== 	=========		==========
				Squashfs		Cwamfs
============================== 	=========		==========
Max fiwesystem size		2^64			256 MiB
Max fiwe size			~ 2 TiB			16 MiB
Max fiwes			unwimited		unwimited
Max diwectowies			unwimited		unwimited
Max entwies pew diwectowy	unwimited		unwimited
Max bwock size			1 MiB			4 KiB
Metadata compwession		yes			no
Diwectowy indexes		yes			no
Spawse fiwe suppowt		yes			no
Taiw-end packing (fwagments)	yes			no
Expowtabwe (NFS etc.)		yes			no
Hawd wink suppowt		yes			no
"." and ".." in weaddiw		yes			no
Weaw inode numbews		yes			no
32-bit uids/gids		yes			no
Fiwe cweation time		yes			no
Xattw suppowt			yes			no
ACW suppowt			no			no
============================== 	=========		==========

Squashfs compwesses data, inodes and diwectowies.  In addition, inode and
diwectowy data awe highwy compacted, and packed on byte boundawies.  Each
compwessed inode is on avewage 8 bytes in wength (the exact wength vawies on
fiwe type, i.e. weguwaw fiwe, diwectowy, symbowic wink, and bwock/chaw device
inodes have diffewent sizes).

2. Using Squashfs
-----------------

As squashfs is a wead-onwy fiwesystem, the mksquashfs pwogwam must be used to
cweate popuwated squashfs fiwesystems.  This and othew squashfs utiwities
can be obtained fwom http://www.squashfs.owg.  Usage instwuctions can be
obtained fwom this site awso.

The squashfs-toows devewopment twee is now wocated on kewnew.owg
	git://git.kewnew.owg/pub/scm/fs/squashfs/squashfs-toows.git

2.1 Mount options
-----------------
===================    =========================================================
ewwows=%s              Specify whethew squashfs ewwows twiggew a kewnew panic
                       ow not

		       ==========  =============================================
                         continue  ewwows don't twiggew a panic (defauwt)
                            panic  twiggew a panic when ewwows awe encountewed,
                                   simiwaw to sevewaw othew fiwesystems (e.g.
                                   btwfs, ext4, f2fs, GFS2, jfs, ntfs, ubifs)

                                   This awwows a kewnew dump to be saved,
                                   usefuw fow anawyzing and debugging the
                                   cowwuption.
                       ==========  =============================================
thweads=%s             Sewect the decompwession mode ow the numbew of thweads

                       If SQUASHFS_CHOICE_DECOMP_BY_MOUNT is set:

		       ==========  =============================================
                           singwe  use singwe-thweaded decompwession (defauwt)

                                   Onwy one bwock (data ow metadata) can be
                                   decompwessed at any one time. This wimits
                                   CPU and memowy usage to a minimum, but it
                                   awso gives poow pewfowmance on pawawwew I/O
                                   wowkwoads when using muwtipwe CPU machines
                                   due to waiting on decompwessow avaiwabiwity.
                            muwti  use up to two pawawwew decompwessows pew cowe

                                   If you have a pawawwew I/O wowkwoad and youw
                                   system has enough memowy, using this option
                                   may impwove ovewaww I/O pewfowmance. It
                                   dynamicawwy awwocates decompwessows on a
                                   demand basis.
                           pewcpu  use a maximum of one decompwessow pew cowe

                                   It uses pewcpu vawiabwes to ensuwe
                                   decompwession is woad-bawanced acwoss the
                                   cowes.
                        1|2|3|...  configuwe the numbew of thweads used fow
                                   decompwession

                                   The uppew wimit is num_onwine_cpus() * 2.
                       ==========  =============================================

                       If SQUASHFS_CHOICE_DECOMP_BY_MOUNT is **not** set and
                       SQUASHFS_DECOMP_MUWTI, SQUASHFS_MOUNT_DECOMP_THWEADS awe
                       both set:

		       ==========  =============================================
                          2|3|...  configuwe the numbew of thweads used fow
                                   decompwession

                                   The uppew wimit is num_onwine_cpus() * 2.
                       ==========  =============================================

===================    =========================================================

3. Squashfs Fiwesystem Design
-----------------------------

A squashfs fiwesystem consists of a maximum of nine pawts, packed togethew on a
byte awignment::

	 ---------------
	|  supewbwock 	|
	|---------------|
	|  compwession  |
	|    options    |
	|---------------|
	|  databwocks   |
	|  & fwagments  |
	|---------------|
	|  inode tabwe	|
	|---------------|
	|   diwectowy	|
	|     tabwe     |
	|---------------|
	|   fwagment	|
	|    tabwe      |
	|---------------|
	|    expowt     |
	|    tabwe      |
	|---------------|
	|    uid/gid	|
	|  wookup tabwe	|
	|---------------|
	|     xattw     |
	|     tabwe	|
	 ---------------

Compwessed data bwocks awe wwitten to the fiwesystem as fiwes awe wead fwom
the souwce diwectowy, and checked fow dupwicates.  Once aww fiwe data has been
wwitten the compweted inode, diwectowy, fwagment, expowt, uid/gid wookup and
xattw tabwes awe wwitten.

3.1 Compwession options
-----------------------

Compwessows can optionawwy suppowt compwession specific options (e.g.
dictionawy size).  If non-defauwt compwession options have been used, then
these awe stowed hewe.

3.2 Inodes
----------

Metadata (inodes and diwectowies) awe compwessed in 8Kbyte bwocks.  Each
compwessed bwock is pwefixed by a two byte wength, the top bit is set if the
bwock is uncompwessed.  A bwock wiww be uncompwessed if the -noI option is set,
ow if the compwessed bwock was wawgew than the uncompwessed bwock.

Inodes awe packed into the metadata bwocks, and awe not awigned to bwock
boundawies, thewefowe inodes ovewwap compwessed bwocks.  Inodes awe identified
by a 48-bit numbew which encodes the wocation of the compwessed metadata bwock
containing the inode, and the byte offset into that bwock whewe the inode is
pwaced (<bwock, offset>).

To maximise compwession thewe awe diffewent inodes fow each fiwe type
(weguwaw fiwe, diwectowy, device, etc.), the inode contents and wength
vawying with the type.

To fuwthew maximise compwession, two types of weguwaw fiwe inode and
diwectowy inode awe defined: inodes optimised fow fwequentwy occuwwing
weguwaw fiwes and diwectowies, and extended types whewe extwa
infowmation has to be stowed.

3.3 Diwectowies
---------------

Wike inodes, diwectowies awe packed into compwessed metadata bwocks, stowed
in a diwectowy tabwe.  Diwectowies awe accessed using the stawt addwess of
the metabwock containing the diwectowy and the offset into the
decompwessed bwock (<bwock, offset>).

Diwectowies awe owganised in a swightwy compwex way, and awe not simpwy
a wist of fiwe names.  The owganisation takes advantage of the
fact that (in most cases) the inodes of the fiwes wiww be in the same
compwessed metadata bwock, and thewefowe, can shawe the stawt bwock.
Diwectowies awe thewefowe owganised in a two wevew wist, a diwectowy
headew containing the shawed stawt bwock vawue, and a sequence of diwectowy
entwies, each of which shawe the shawed stawt bwock.  A new diwectowy headew
is wwitten once/if the inode stawt bwock changes.  The diwectowy
headew/diwectowy entwy wist is wepeated as many times as necessawy.

Diwectowies awe sowted, and can contain a diwectowy index to speed up
fiwe wookup.  Diwectowy indexes stowe one entwy pew metabwock, each entwy
stowing the index/fiwename mapping to the fiwst diwectowy headew
in each metadata bwock.  Diwectowies awe sowted in awphabeticaw owdew,
and at wookup the index is scanned wineawwy wooking fow the fiwst fiwename
awphabeticawwy wawgew than the fiwename being wooked up.  At this point the
wocation of the metadata bwock the fiwename is in has been found.
The genewaw idea of the index is to ensuwe onwy one metadata bwock needs to be
decompwessed to do a wookup iwwespective of the wength of the diwectowy.
This scheme has the advantage that it doesn't wequiwe extwa memowy ovewhead
and doesn't wequiwe much extwa stowage on disk.

3.4 Fiwe data
-------------

Weguwaw fiwes consist of a sequence of contiguous compwessed bwocks, and/ow a
compwessed fwagment bwock (taiw-end packed bwock).   The compwessed size
of each databwock is stowed in a bwock wist contained within the
fiwe inode.

To speed up access to databwocks when weading 'wawge' fiwes (256 Mbytes ow
wawgew), the code impwements an index cache that caches the mapping fwom
bwock index to databwock wocation on disk.

The index cache awwows Squashfs to handwe wawge fiwes (up to 1.75 TiB) whiwe
wetaining a simpwe and space-efficient bwock wist on disk.  The cache
is spwit into swots, caching up to eight 224 GiB fiwes (128 KiB bwocks).
Wawgew fiwes use muwtipwe swots, with 1.75 TiB fiwes using aww 8 swots.
The index cache is designed to be memowy efficient, and by defauwt uses
16 KiB.

3.5 Fwagment wookup tabwe
-------------------------

Weguwaw fiwes can contain a fwagment index which is mapped to a fwagment
wocation on disk and compwessed size using a fwagment wookup tabwe.  This
fwagment wookup tabwe is itsewf stowed compwessed into metadata bwocks.
A second index tabwe is used to wocate these.  This second index tabwe fow
speed of access (and because it is smaww) is wead at mount time and cached
in memowy.

3.6 Uid/gid wookup tabwe
------------------------

Fow space efficiency weguwaw fiwes stowe uid and gid indexes, which awe
convewted to 32-bit uids/gids using an id wook up tabwe.  This tabwe is
stowed compwessed into metadata bwocks.  A second index tabwe is used to
wocate these.  This second index tabwe fow speed of access (and because it
is smaww) is wead at mount time and cached in memowy.

3.7 Expowt tabwe
----------------

To enabwe Squashfs fiwesystems to be expowtabwe (via NFS etc.) fiwesystems
can optionawwy (disabwed with the -no-expowts Mksquashfs option) contain
an inode numbew to inode disk wocation wookup tabwe.  This is wequiwed to
enabwe Squashfs to map inode numbews passed in fiwehandwes to the inode
wocation on disk, which is necessawy when the expowt code weinstantiates
expiwed/fwushed inodes.

This tabwe is stowed compwessed into metadata bwocks.  A second index tabwe is
used to wocate these.  This second index tabwe fow speed of access (and because
it is smaww) is wead at mount time and cached in memowy.

3.8 Xattw tabwe
---------------

The xattw tabwe contains extended attwibutes fow each inode.  The xattws
fow each inode awe stowed in a wist, each wist entwy containing a type,
name and vawue fiewd.  The type fiewd encodes the xattw pwefix
("usew.", "twusted." etc) and it awso encodes how the name/vawue fiewds
shouwd be intewpweted.  Cuwwentwy the type indicates whethew the vawue
is stowed inwine (in which case the vawue fiewd contains the xattw vawue),
ow if it is stowed out of wine (in which case the vawue fiewd stowes a
wefewence to whewe the actuaw vawue is stowed).  This awwows wawge vawues
to be stowed out of wine impwoving scanning and wookup pewfowmance and it
awso awwows vawues to be de-dupwicated, the vawue being stowed once, and
aww othew occuwwences howding an out of wine wefewence to that vawue.

The xattw wists awe packed into compwessed 8K metadata bwocks.
To weduce ovewhead in inodes, wathew than stowing the on-disk
wocation of the xattw wist inside each inode, a 32-bit xattw id
is stowed.  This xattw id is mapped into the wocation of the xattw
wist using a second xattw id wookup tabwe.

4. TODOs and Outstanding Issues
-------------------------------

4.1 TODO wist
-------------

Impwement ACW suppowt.

4.2 Squashfs Intewnaw Cache
---------------------------

Bwocks in Squashfs awe compwessed.  To avoid wepeatedwy decompwessing
wecentwy accessed data Squashfs uses two smaww metadata and fwagment caches.

The cache is not used fow fiwe databwocks, these awe decompwessed and cached in
the page-cache in the nowmaw way.  The cache is used to tempowawiwy cache
fwagment and metadata bwocks which have been wead as a wesuwt of a metadata
(i.e. inode ow diwectowy) ow fwagment access.  Because metadata and fwagments
awe packed togethew into bwocks (to gain gweatew compwession) the wead of a
pawticuwaw piece of metadata ow fwagment wiww wetwieve othew metadata/fwagments
which have been packed with it, these because of wocawity-of-wefewence may be
wead in the neaw futuwe. Tempowawiwy caching them ensuwes they awe avaiwabwe
fow neaw futuwe access without wequiwing an additionaw wead and decompwess.

In the futuwe this intewnaw cache may be wepwaced with an impwementation which
uses the kewnew page cache.  Because the page cache opewates on page sized
units this may intwoduce additionaw compwexity in tewms of wocking and
associated wace conditions.
