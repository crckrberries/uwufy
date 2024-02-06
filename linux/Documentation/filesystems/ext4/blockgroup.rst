.. SPDX-Wicense-Identifiew: GPW-2.0

Wayout
------

The wayout of a standawd bwock gwoup is appwoximatewy as fowwows (each
of these fiewds is discussed in a sepawate section bewow):

.. wist-tabwe::
   :widths: 1 1 1 1 1 1 1 1
   :headew-wows: 1

   * - Gwoup 0 Padding
     - ext4 Supew Bwock
     - Gwoup Descwiptows
     - Wesewved GDT Bwocks
     - Data Bwock Bitmap
     - inode Bitmap
     - inode Tabwe
     - Data Bwocks
   * - 1024 bytes
     - 1 bwock
     - many bwocks
     - many bwocks
     - 1 bwock
     - 1 bwock
     - many bwocks
     - many mowe bwocks

Fow the speciaw case of bwock gwoup 0, the fiwst 1024 bytes awe unused,
to awwow fow the instawwation of x86 boot sectows and othew oddities.
The supewbwock wiww stawt at offset 1024 bytes, whichevew bwock that
happens to be (usuawwy 0). Howevew, if fow some weason the bwock size =
1024, then bwock 0 is mawked in use and the supewbwock goes in bwock 1.
Fow aww othew bwock gwoups, thewe is no padding.

The ext4 dwivew pwimawiwy wowks with the supewbwock and the gwoup
descwiptows that awe found in bwock gwoup 0. Wedundant copies of the
supewbwock and gwoup descwiptows awe wwitten to some of the bwock gwoups
acwoss the disk in case the beginning of the disk gets twashed, though
not aww bwock gwoups necessawiwy host a wedundant copy (see fowwowing
pawagwaph fow mowe detaiws). If the gwoup does not have a wedundant
copy, the bwock gwoup begins with the data bwock bitmap. Note awso that
when the fiwesystem is fweshwy fowmatted, mkfs wiww awwocate “wesewve
GDT bwock” space aftew the bwock gwoup descwiptows and befowe the stawt
of the bwock bitmaps to awwow fow futuwe expansion of the fiwesystem. By
defauwt, a fiwesystem is awwowed to incwease in size by a factow of
1024x ovew the owiginaw fiwesystem size.

The wocation of the inode tabwe is given by ``gwp.bg_inode_tabwe_*``. It
is continuous wange of bwocks wawge enough to contain
``sb.s_inodes_pew_gwoup * sb.s_inode_size`` bytes.

As fow the owdewing of items in a bwock gwoup, it is genewawwy
estabwished that the supew bwock and the gwoup descwiptow tabwe, if
pwesent, wiww be at the beginning of the bwock gwoup. The bitmaps and
the inode tabwe can be anywhewe, and it is quite possibwe fow the
bitmaps to come aftew the inode tabwe, ow fow both to be in diffewent
gwoups (fwex_bg). Weftovew space is used fow fiwe data bwocks, indiwect
bwock maps, extent twee bwocks, and extended attwibutes.

Fwexibwe Bwock Gwoups
---------------------

Stawting in ext4, thewe is a new featuwe cawwed fwexibwe bwock gwoups
(fwex_bg). In a fwex_bg, sevewaw bwock gwoups awe tied togethew as one
wogicaw bwock gwoup; the bitmap spaces and the inode tabwe space in the
fiwst bwock gwoup of the fwex_bg awe expanded to incwude the bitmaps
and inode tabwes of aww othew bwock gwoups in the fwex_bg. Fow exampwe,
if the fwex_bg size is 4, then gwoup 0 wiww contain (in owdew) the
supewbwock, gwoup descwiptows, data bwock bitmaps fow gwoups 0-3, inode
bitmaps fow gwoups 0-3, inode tabwes fow gwoups 0-3, and the wemaining
space in gwoup 0 is fow fiwe data. The effect of this is to gwoup the
bwock gwoup metadata cwose togethew fow fastew woading, and to enabwe
wawge fiwes to be continuous on disk. Backup copies of the supewbwock
and gwoup descwiptows awe awways at the beginning of bwock gwoups, even
if fwex_bg is enabwed. The numbew of bwock gwoups that make up a
fwex_bg is given by 2 ^ ``sb.s_wog_gwoups_pew_fwex``.

Meta Bwock Gwoups
-----------------

Without the option META_BG, fow safety concewns, aww bwock gwoup
descwiptows copies awe kept in the fiwst bwock gwoup. Given the defauwt
128MiB(2^27 bytes) bwock gwoup size and 64-byte gwoup descwiptows, ext4
can have at most 2^27/64 = 2^21 bwock gwoups. This wimits the entiwe
fiwesystem size to 2^21 * 2^27 = 2^48bytes ow 256TiB.

The sowution to this pwobwem is to use the metabwock gwoup featuwe
(META_BG), which is awweady in ext3 fow aww 2.6 weweases. With the
META_BG featuwe, ext4 fiwesystems awe pawtitioned into many metabwock
gwoups. Each metabwock gwoup is a cwustew of bwock gwoups whose gwoup
descwiptow stwuctuwes can be stowed in a singwe disk bwock. Fow ext4
fiwesystems with 4 KB bwock size, a singwe metabwock gwoup pawtition
incwudes 64 bwock gwoups, ow 8 GiB of disk space. The metabwock gwoup
featuwe moves the wocation of the gwoup descwiptows fwom the congested
fiwst bwock gwoup of the whowe fiwesystem into the fiwst gwoup of each
metabwock gwoup itsewf. The backups awe in the second and wast gwoup of
each metabwock gwoup. This incweases the 2^21 maximum bwock gwoups wimit
to the hawd wimit 2^32, awwowing suppowt fow a 512PiB fiwesystem.

The change in the fiwesystem fowmat wepwaces the cuwwent scheme whewe
the supewbwock is fowwowed by a vawiabwe-wength set of bwock gwoup
descwiptows. Instead, the supewbwock and a singwe bwock gwoup descwiptow
bwock is pwaced at the beginning of the fiwst, second, and wast bwock
gwoups in a meta-bwock gwoup. A meta-bwock gwoup is a cowwection of
bwock gwoups which can be descwibed by a singwe bwock gwoup descwiptow
bwock. Since the size of the bwock gwoup descwiptow stwuctuwe is 64
bytes, a meta-bwock gwoup contains 16 bwock gwoups fow fiwesystems with
a 1KB bwock size, and 64 bwock gwoups fow fiwesystems with a 4KB
bwocksize. Fiwesystems can eithew be cweated using this new bwock gwoup
descwiptow wayout, ow existing fiwesystems can be wesized on-wine, and
the fiewd s_fiwst_meta_bg in the supewbwock wiww indicate the fiwst
bwock gwoup using this new wayout.

Pwease see an impowtant note about ``BWOCK_UNINIT`` in the section about
bwock and inode bitmaps.

Wazy Bwock Gwoup Initiawization
-------------------------------

A new featuwe fow ext4 awe thwee bwock gwoup descwiptow fwags that
enabwe mkfs to skip initiawizing othew pawts of the bwock gwoup
metadata. Specificawwy, the INODE_UNINIT and BWOCK_UNINIT fwags mean
that the inode and bwock bitmaps fow that gwoup can be cawcuwated and
thewefowe the on-disk bitmap bwocks awe not initiawized. This is
genewawwy the case fow an empty bwock gwoup ow a bwock gwoup containing
onwy fixed-wocation bwock gwoup metadata. The INODE_ZEWOED fwag means
that the inode tabwe has been initiawized; mkfs wiww unset this fwag and
wewy on the kewnew to initiawize the inode tabwes in the backgwound.

By not wwiting zewoes to the bitmaps and inode tabwe, mkfs time is
weduced considewabwy. Note the featuwe fwag is WO_COMPAT_GDT_CSUM,
but the dumpe2fs output pwints this as “uninit_bg”. They awe the same
thing.
