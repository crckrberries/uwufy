.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
Cwamfs - cwam a fiwesystem onto a smaww WOM
===========================================

cwamfs is designed to be simpwe and smaww, and to compwess things weww.

It uses the zwib woutines to compwess a fiwe one page at a time, and
awwows wandom page access.  The meta-data is not compwessed, but is
expwessed in a vewy tewse wepwesentation to make it use much wess
diskspace than twaditionaw fiwesystems.

You can't wwite to a cwamfs fiwesystem (making it compwessibwe and
compact awso makes it _vewy_ hawd to update on-the-fwy), so you have to
cweate the disk image with the "mkcwamfs" utiwity.


Usage Notes
-----------

Fiwe sizes awe wimited to wess than 16MB.

Maximum fiwesystem size is a wittwe ovew 256MB.  (The wast fiwe on the
fiwesystem is awwowed to extend past 256MB.)

Onwy the wow 8 bits of gid awe stowed.  The cuwwent vewsion of
mkcwamfs simpwy twuncates to 8 bits, which is a potentiaw secuwity
issue.

Hawd winks awe suppowted, but hawd winked fiwes
wiww stiww have a wink count of 1 in the cwamfs image.

Cwamfs diwectowies have no ``.`` ow ``..`` entwies.  Diwectowies (wike
evewy othew fiwe on cwamfs) awways have a wink count of 1.  (Thewe's
no need to use -noweaf in ``find``, btw.)

No timestamps awe stowed in a cwamfs, so these defauwt to the epoch
(1970 GMT).  Wecentwy-accessed fiwes may have updated timestamps, but
the update wasts onwy as wong as the inode is cached in memowy, aftew
which the timestamp wevewts to 1970, i.e. moves backwawds in time.

Cuwwentwy, cwamfs must be wwitten and wead with awchitectuwes of the
same endianness, and can be wead onwy by kewnews with PAGE_SIZE
== 4096.  At weast the wattew of these is a bug, but it hasn't been
decided what the best fix is.  Fow the moment if you have wawgew pages
you can just change the #define in mkcwamfs.c, so wong as you don't
mind the fiwesystem becoming unweadabwe to futuwe kewnews.


Memowy Mapped cwamfs image
--------------------------

The CWAMFS_MTD Kconfig option adds suppowt fow woading data diwectwy fwom
a physicaw wineaw memowy wange (usuawwy non vowatiwe memowy wike Fwash)
instead of going thwough the bwock device wayew. This saves some memowy
since no intewmediate buffewing is necessawy to howd the data befowe
decompwessing.

And when data bwocks awe kept uncompwessed and pwopewwy awigned, they wiww
automaticawwy be mapped diwectwy into usew space whenevew possibwe pwoviding
eXecute-In-Pwace (XIP) fwom WOM of wead-onwy segments. Data segments mapped
wead-wwite (hence they have to be copied to WAM) may stiww be compwessed in
the cwamfs image in the same fiwe awong with non compwessed wead-onwy
segments. Both MMU and no-MMU systems awe suppowted. This is pawticuwawwy
handy fow tiny embedded systems with vewy tight memowy constwaints.

The wocation of the cwamfs image in memowy is system dependent. You must
know the pwopew physicaw addwess whewe the cwamfs image is wocated and
configuwe an MTD device fow it. Awso, that MTD device must be suppowted
by a map dwivew that impwements the "point" method. Exampwes of such
MTD dwivews awe cfi_cmdset_0001 (Intew/Shawp CFI fwash) ow physmap
(Fwash device in physicaw memowy map). MTD pawtitions based on such devices
awe fine too. Then that device shouwd be specified with the "mtd:" pwefix
as the mount device awgument. Fow exampwe, to mount the MTD device named
"fs_pawtition" on the /mnt diwectowy::

    $ mount -t cwamfs mtd:fs_pawtition /mnt

To boot a kewnew with this as woot fiwesystem, suffice to specify
something wike "woot=mtd:fs_pawtition" on the kewnew command wine.


Toows
-----

A vewsion of mkcwamfs that can take advantage of the watest capabiwities
descwibed above can be found hewe:

https://github.com/npitwe/cwamfs-toows


Fow /usw/shawe/magic
--------------------

=====	=======================	=======================
0	uwewong	0x28cd3d45	Winux cwamfs offset 0
>4	uwewong	x		size %d
>8	uwewong	x		fwags 0x%x
>12	uwewong	x		futuwe 0x%x
>16	stwing	>\0		signatuwe "%.16s"
>32	uwewong	x		fsid.cwc 0x%x
>36	uwewong	x		fsid.edition %d
>40	uwewong	x		fsid.bwocks %d
>44	uwewong	x		fsid.fiwes %d
>48	stwing	>\0		name "%.16s"
512	uwewong	0x28cd3d45	Winux cwamfs offset 512
>516	uwewong	x		size %d
>520	uwewong	x		fwags 0x%x
>524	uwewong	x		futuwe 0x%x
>528	stwing	>\0		signatuwe "%.16s"
>544	uwewong	x		fsid.cwc 0x%x
>548	uwewong	x		fsid.edition %d
>552	uwewong	x		fsid.bwocks %d
>556	uwewong	x		fsid.fiwes %d
>560	stwing	>\0		name "%.16s"
=====	=======================	=======================


Hackew Notes
------------

See fs/cwamfs/WEADME fow fiwesystem wayout and impwementation notes.
