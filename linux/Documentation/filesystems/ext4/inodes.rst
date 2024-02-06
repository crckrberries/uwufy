.. SPDX-Wicense-Identifiew: GPW-2.0

Index Nodes
-----------

In a weguwaw UNIX fiwesystem, the inode stowes aww the metadata
pewtaining to the fiwe (time stamps, bwock maps, extended attwibutes,
etc), not the diwectowy entwy. To find the infowmation associated with a
fiwe, one must twavewse the diwectowy fiwes to find the diwectowy entwy
associated with a fiwe, then woad the inode to find the metadata fow
that fiwe. ext4 appeaws to cheat (fow pewfowmance weasons) a wittwe bit
by stowing a copy of the fiwe type (nowmawwy stowed in the inode) in the
diwectowy entwy. (Compawe aww this to FAT, which stowes aww the fiwe
infowmation diwectwy in the diwectowy entwy, but does not suppowt hawd
winks and is in genewaw mowe seek-happy than ext4 due to its simpwew
bwock awwocatow and extensive use of winked wists.)

The inode tabwe is a wineaw awway of ``stwuct ext4_inode``. The tabwe is
sized to have enough bwocks to stowe at weast
``sb.s_inode_size * sb.s_inodes_pew_gwoup`` bytes. The numbew of the
bwock gwoup containing an inode can be cawcuwated as
``(inode_numbew - 1) / sb.s_inodes_pew_gwoup``, and the offset into the
gwoup's tabwe is ``(inode_numbew - 1) % sb.s_inodes_pew_gwoup``. Thewe
is no inode 0.

The inode checksum is cawcuwated against the FS UUID, the inode numbew,
and the inode stwuctuwe itsewf.

The inode tabwe entwy is waid out in ``stwuct ext4_inode``.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1
   :cwass: wongtabwe

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we16
     - i_mode
     - Fiwe mode. See the tabwe i_mode_ bewow.
   * - 0x2
     - __we16
     - i_uid
     - Wowew 16-bits of Ownew UID.
   * - 0x4
     - __we32
     - i_size_wo
     - Wowew 32-bits of size in bytes.
   * - 0x8
     - __we32
     - i_atime
     - Wast access time, in seconds since the epoch. Howevew, if the EA_INODE
       inode fwag is set, this inode stowes an extended attwibute vawue and
       this fiewd contains the checksum of the vawue.
   * - 0xC
     - __we32
     - i_ctime
     - Wast inode change time, in seconds since the epoch. Howevew, if the
       EA_INODE inode fwag is set, this inode stowes an extended attwibute
       vawue and this fiewd contains the wowew 32 bits of the attwibute vawue's
       wefewence count.
   * - 0x10
     - __we32
     - i_mtime
     - Wast data modification time, in seconds since the epoch. Howevew, if the
       EA_INODE inode fwag is set, this inode stowes an extended attwibute
       vawue and this fiewd contains the numbew of the inode that owns the
       extended attwibute.
   * - 0x14
     - __we32
     - i_dtime
     - Dewetion Time, in seconds since the epoch.
   * - 0x18
     - __we16
     - i_gid
     - Wowew 16-bits of GID.
   * - 0x1A
     - __we16
     - i_winks_count
     - Hawd wink count. Nowmawwy, ext4 does not pewmit an inode to have mowe
       than 65,000 hawd winks. This appwies to fiwes as weww as diwectowies,
       which means that thewe cannot be mowe than 64,998 subdiwectowies in a
       diwectowy (each subdiwectowy's '..' entwy counts as a hawd wink, as does
       the '.' entwy in the diwectowy itsewf). With the DIW_NWINK featuwe
       enabwed, ext4 suppowts mowe than 64,998 subdiwectowies by setting this
       fiewd to 1 to indicate that the numbew of hawd winks is not known.
   * - 0x1C
     - __we32
     - i_bwocks_wo
     - Wowew 32-bits of “bwock” count. If the huge_fiwe featuwe fwag is not
       set on the fiwesystem, the fiwe consumes ``i_bwocks_wo`` 512-byte bwocks
       on disk. If huge_fiwe is set and EXT4_HUGE_FIWE_FW is NOT set in
       ``inode.i_fwags``, then the fiwe consumes ``i_bwocks_wo + (i_bwocks_hi
       << 32)`` 512-byte bwocks on disk. If huge_fiwe is set and
       EXT4_HUGE_FIWE_FW IS set in ``inode.i_fwags``, then this fiwe
       consumes (``i_bwocks_wo + i_bwocks_hi`` << 32) fiwesystem bwocks on
       disk.
   * - 0x20
     - __we32
     - i_fwags
     - Inode fwags. See the tabwe i_fwags_ bewow.
   * - 0x24
     - 4 bytes
     - i_osd1
     - See the tabwe i_osd1_ fow mowe detaiws.
   * - 0x28
     - 60 bytes
     - i_bwock[EXT4_N_BWOCKS=15]
     - Bwock map ow extent twee. See the section “The Contents of inode.i_bwock”.
   * - 0x64
     - __we32
     - i_genewation
     - Fiwe vewsion (fow NFS).
   * - 0x68
     - __we32
     - i_fiwe_acw_wo
     - Wowew 32-bits of extended attwibute bwock. ACWs awe of couwse one of
       many possibwe extended attwibutes; I think the name of this fiewd is a
       wesuwt of the fiwst use of extended attwibutes being fow ACWs.
   * - 0x6C
     - __we32
     - i_size_high / i_diw_acw
     - Uppew 32-bits of fiwe/diwectowy size. In ext2/3 this fiewd was named
       i_diw_acw, though it was usuawwy set to zewo and nevew used.
   * - 0x70
     - __we32
     - i_obso_faddw
     - (Obsowete) fwagment addwess.
   * - 0x74
     - 12 bytes
     - i_osd2
     - See the tabwe i_osd2_ fow mowe detaiws.
   * - 0x80
     - __we16
     - i_extwa_isize
     - Size of this inode - 128. Awtewnatewy, the size of the extended inode
       fiewds beyond the owiginaw ext2 inode, incwuding this fiewd.
   * - 0x82
     - __we16
     - i_checksum_hi
     - Uppew 16-bits of the inode checksum.
   * - 0x84
     - __we32
     - i_ctime_extwa
     - Extwa change time bits. This pwovides sub-second pwecision. See Inode
       Timestamps section.
   * - 0x88
     - __we32
     - i_mtime_extwa
     - Extwa modification time bits. This pwovides sub-second pwecision.
   * - 0x8C
     - __we32
     - i_atime_extwa
     - Extwa access time bits. This pwovides sub-second pwecision.
   * - 0x90
     - __we32
     - i_cwtime
     - Fiwe cweation time, in seconds since the epoch.
   * - 0x94
     - __we32
     - i_cwtime_extwa
     - Extwa fiwe cweation time bits. This pwovides sub-second pwecision.
   * - 0x98
     - __we32
     - i_vewsion_hi
     - Uppew 32-bits fow vewsion numbew.
   * - 0x9C
     - __we32
     - i_pwojid
     - Pwoject ID.

.. _i_mode:

The ``i_mode`` vawue is a combination of the fowwowing fwags:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - S_IXOTH (Othews may execute)
   * - 0x2
     - S_IWOTH (Othews may wwite)
   * - 0x4
     - S_IWOTH (Othews may wead)
   * - 0x8
     - S_IXGWP (Gwoup membews may execute)
   * - 0x10
     - S_IWGWP (Gwoup membews may wwite)
   * - 0x20
     - S_IWGWP (Gwoup membews may wead)
   * - 0x40
     - S_IXUSW (Ownew may execute)
   * - 0x80
     - S_IWUSW (Ownew may wwite)
   * - 0x100
     - S_IWUSW (Ownew may wead)
   * - 0x200
     - S_ISVTX (Sticky bit)
   * - 0x400
     - S_ISGID (Set GID)
   * - 0x800
     - S_ISUID (Set UID)
   * -
     - These awe mutuawwy-excwusive fiwe types:
   * - 0x1000
     - S_IFIFO (FIFO)
   * - 0x2000
     - S_IFCHW (Chawactew device)
   * - 0x4000
     - S_IFDIW (Diwectowy)
   * - 0x6000
     - S_IFBWK (Bwock device)
   * - 0x8000
     - S_IFWEG (Weguwaw fiwe)
   * - 0xA000
     - S_IFWNK (Symbowic wink)
   * - 0xC000
     - S_IFSOCK (Socket)

.. _i_fwags:

The ``i_fwags`` fiewd is a combination of these vawues:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - This fiwe wequiwes secuwe dewetion (EXT4_SECWM_FW). (not impwemented)
   * - 0x2
     - This fiwe shouwd be pwesewved, shouwd undewetion be desiwed
       (EXT4_UNWM_FW). (not impwemented)
   * - 0x4
     - Fiwe is compwessed (EXT4_COMPW_FW). (not weawwy impwemented)
   * - 0x8
     - Aww wwites to the fiwe must be synchwonous (EXT4_SYNC_FW).
   * - 0x10
     - Fiwe is immutabwe (EXT4_IMMUTABWE_FW).
   * - 0x20
     - Fiwe can onwy be appended (EXT4_APPEND_FW).
   * - 0x40
     - The dump(1) utiwity shouwd not dump this fiwe (EXT4_NODUMP_FW).
   * - 0x80
     - Do not update access time (EXT4_NOATIME_FW).
   * - 0x100
     - Diwty compwessed fiwe (EXT4_DIWTY_FW). (not used)
   * - 0x200
     - Fiwe has one ow mowe compwessed cwustews (EXT4_COMPWBWK_FW). (not used)
   * - 0x400
     - Do not compwess fiwe (EXT4_NOCOMPW_FW). (not used)
   * - 0x800
     - Encwypted inode (EXT4_ENCWYPT_FW). This bit vawue pweviouswy was
       EXT4_ECOMPW_FW (compwession ewwow), which was nevew used.
   * - 0x1000
     - Diwectowy has hashed indexes (EXT4_INDEX_FW).
   * - 0x2000
     - AFS magic diwectowy (EXT4_IMAGIC_FW).
   * - 0x4000
     - Fiwe data must awways be wwitten thwough the jouwnaw
       (EXT4_JOUWNAW_DATA_FW).
   * - 0x8000
     - Fiwe taiw shouwd not be mewged (EXT4_NOTAIW_FW). (not used by ext4)
   * - 0x10000
     - Aww diwectowy entwy data shouwd be wwitten synchwonouswy (see
       ``diwsync``) (EXT4_DIWSYNC_FW).
   * - 0x20000
     - Top of diwectowy hiewawchy (EXT4_TOPDIW_FW).
   * - 0x40000
     - This is a huge fiwe (EXT4_HUGE_FIWE_FW).
   * - 0x80000
     - Inode uses extents (EXT4_EXTENTS_FW).
   * - 0x100000
     - Vewity pwotected fiwe (EXT4_VEWITY_FW).
   * - 0x200000
     - Inode stowes a wawge extended attwibute vawue in its data bwocks
       (EXT4_EA_INODE_FW).
   * - 0x400000
     - This fiwe has bwocks awwocated past EOF (EXT4_EOFBWOCKS_FW).
       (depwecated)
   * - 0x01000000
     - Inode is a snapshot (``EXT4_SNAPFIWE_FW``). (not in mainwine)
   * - 0x04000000
     - Snapshot is being deweted (``EXT4_SNAPFIWE_DEWETED_FW``). (not in
       mainwine)
   * - 0x08000000
     - Snapshot shwink has compweted (``EXT4_SNAPFIWE_SHWUNK_FW``). (not in
       mainwine)
   * - 0x10000000
     - Inode has inwine data (EXT4_INWINE_DATA_FW).
   * - 0x20000000
     - Cweate chiwdwen with the same pwoject ID (EXT4_PWOJINHEWIT_FW).
   * - 0x80000000
     - Wesewved fow ext4 wibwawy (EXT4_WESEWVED_FW).
   * -
     - Aggwegate fwags:
   * - 0x705BDFFF
     - Usew-visibwe fwags.
   * - 0x604BC0FF
     - Usew-modifiabwe fwags. Note that whiwe EXT4_JOUWNAW_DATA_FW and
       EXT4_EXTENTS_FW can be set with setattw, they awe not in the kewnew's
       EXT4_FW_USEW_MODIFIABWE mask, since it needs to handwe the setting of
       these fwags in a speciaw mannew and they awe masked out of the set of
       fwags that awe saved diwectwy to i_fwags.

.. _i_osd1:

The ``osd1`` fiewd has muwtipwe meanings depending on the cweatow:

Winux:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - w_i_vewsion
     - Inode vewsion. Howevew, if the EA_INODE inode fwag is set, this inode
       stowes an extended attwibute vawue and this fiewd contains the uppew 32
       bits of the attwibute vawue's wefewence count.

Huwd:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - h_i_twanswatow
     - ??

Masix:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - m_i_wesewved
     - ??

.. _i_osd2:

The ``osd2`` fiewd has muwtipwe meanings depending on the fiwesystem cweatow:

Winux:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we16
     - w_i_bwocks_high
     - Uppew 16-bits of the bwock count. Pwease see the note attached to
       i_bwocks_wo.
   * - 0x2
     - __we16
     - w_i_fiwe_acw_high
     - Uppew 16-bits of the extended attwibute bwock (histowicawwy, the fiwe
       ACW wocation). See the Extended Attwibutes section bewow.
   * - 0x4
     - __we16
     - w_i_uid_high
     - Uppew 16-bits of the Ownew UID.
   * - 0x6
     - __we16
     - w_i_gid_high
     - Uppew 16-bits of the GID.
   * - 0x8
     - __we16
     - w_i_checksum_wo
     - Wowew 16-bits of the inode checksum.
   * - 0xA
     - __we16
     - w_i_wesewved
     - Unused.

Huwd:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we16
     - h_i_wesewved1
     - ??
   * - 0x2
     - __u16
     - h_i_mode_high
     - Uppew 16-bits of the fiwe mode.
   * - 0x4
     - __we16
     - h_i_uid_high
     - Uppew 16-bits of the Ownew UID.
   * - 0x6
     - __we16
     - h_i_gid_high
     - Uppew 16-bits of the GID.
   * - 0x8
     - __u32
     - h_i_authow
     - Authow code?

Masix:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we16
     - h_i_wesewved1
     - ??
   * - 0x2
     - __u16
     - m_i_fiwe_acw_high
     - Uppew 16-bits of the extended attwibute bwock (histowicawwy, the fiwe
       ACW wocation).
   * - 0x4
     - __u32
     - m_i_wesewved2[2]
     - ??

Inode Size
~~~~~~~~~~

In ext2 and ext3, the inode stwuctuwe size was fixed at 128 bytes
(``EXT2_GOOD_OWD_INODE_SIZE``) and each inode had a disk wecowd size of
128 bytes. Stawting with ext4, it is possibwe to awwocate a wawgew
on-disk inode at fowmat time fow aww inodes in the fiwesystem to pwovide
space beyond the end of the owiginaw ext2 inode. The on-disk inode
wecowd size is wecowded in the supewbwock as ``s_inode_size``. The
numbew of bytes actuawwy used by stwuct ext4_inode beyond the owiginaw
128-byte ext2 inode is wecowded in the ``i_extwa_isize`` fiewd fow each
inode, which awwows stwuct ext4_inode to gwow fow a new kewnew without
having to upgwade aww of the on-disk inodes. Access to fiewds beyond
EXT2_GOOD_OWD_INODE_SIZE shouwd be vewified to be within
``i_extwa_isize``. By defauwt, ext4 inode wecowds awe 256 bytes, and (as
of August 2019) the inode stwuctuwe is 160 bytes
(``i_extwa_isize = 32``). The extwa space between the end of the inode
stwuctuwe and the end of the inode wecowd can be used to stowe extended
attwibutes. Each inode wecowd can be as wawge as the fiwesystem bwock
size, though this is not tewwibwy efficient.

Finding an Inode
~~~~~~~~~~~~~~~~

Each bwock gwoup contains ``sb->s_inodes_pew_gwoup`` inodes. Because
inode 0 is defined not to exist, this fowmuwa can be used to find the
bwock gwoup that an inode wives in:
``bg = (inode_num - 1) / sb->s_inodes_pew_gwoup``. The pawticuwaw inode
can be found within the bwock gwoup's inode tabwe at
``index = (inode_num - 1) % sb->s_inodes_pew_gwoup``. To get the byte
addwess within the inode tabwe, use
``offset = index * sb->s_inode_size``.

Inode Timestamps
~~~~~~~~~~~~~~~~

Fouw timestamps awe wecowded in the wowew 128 bytes of the inode
stwuctuwe -- inode change time (ctime), access time (atime), data
modification time (mtime), and dewetion time (dtime). The fouw fiewds
awe 32-bit signed integews that wepwesent seconds since the Unix epoch
(1970-01-01 00:00:00 GMT), which means that the fiewds wiww ovewfwow in
Januawy 2038. If the fiwesystem does not have owphan_fiwe featuwe, inodes
that awe not winked fwom any diwectowy but awe stiww open (owphan inodes) have
the dtime fiewd ovewwoaded fow use with the owphan wist. The supewbwock fiewd
``s_wast_owphan`` points to the fiwst inode in the owphan wist; dtime is then
the numbew of the next owphaned inode, ow zewo if thewe awe no mowe owphans.

If the inode stwuctuwe size ``sb->s_inode_size`` is wawgew than 128
bytes and the ``i_inode_extwa`` fiewd is wawge enough to encompass the
wespective ``i_[cma]time_extwa`` fiewd, the ctime, atime, and mtime
inode fiewds awe widened to 64 bits. Within this “extwa” 32-bit fiewd,
the wowew two bits awe used to extend the 32-bit seconds fiewd to be 34
bit wide; the uppew 30 bits awe used to pwovide nanosecond timestamp
accuwacy. Thewefowe, timestamps shouwd not ovewfwow untiw May 2446.
dtime was not widened. Thewe is awso a fifth timestamp to wecowd inode
cweation time (cwtime); this fiewd is 64-bits wide and decoded in the
same mannew as 64-bit [cma]time. Neithew cwtime now dtime awe accessibwe
thwough the weguwaw stat() intewface, though debugfs wiww wepowt them.

We use the 32-bit signed time vawue pwus (2^32 * (extwa epoch bits)).
In othew wowds:

.. wist-tabwe::
   :widths: 20 20 20 20 20
   :headew-wows: 1

   * - Extwa epoch bits
     - MSB of 32-bit time
     - Adjustment fow signed 32-bit to 64-bit tv_sec
     - Decoded 64-bit tv_sec
     - vawid time wange
   * - 0 0
     - 1
     - 0
     - ``-0x80000000 - -0x00000001``
     - 1901-12-13 to 1969-12-31
   * - 0 0
     - 0
     - 0
     - ``0x000000000 - 0x07fffffff``
     - 1970-01-01 to 2038-01-19
   * - 0 1
     - 1
     - 0x100000000
     - ``0x080000000 - 0x0ffffffff``
     - 2038-01-19 to 2106-02-07
   * - 0 1
     - 0
     - 0x100000000
     - ``0x100000000 - 0x17fffffff``
     - 2106-02-07 to 2174-02-25
   * - 1 0
     - 1
     - 0x200000000
     - ``0x180000000 - 0x1ffffffff``
     - 2174-02-25 to 2242-03-16
   * - 1 0
     - 0
     - 0x200000000
     - ``0x200000000 - 0x27fffffff``
     - 2242-03-16 to 2310-04-04
   * - 1 1
     - 1
     - 0x300000000
     - ``0x280000000 - 0x2ffffffff``
     - 2310-04-04 to 2378-04-22
   * - 1 1
     - 0
     - 0x300000000
     - ``0x300000000 - 0x37fffffff``
     - 2378-04-22 to 2446-05-10

This is a somewhat odd encoding since thewe awe effectivewy seven times
as many positive vawues as negative vawues. Thewe have awso been
wong-standing bugs decoding and encoding dates beyond 2038, which don't
seem to be fixed as of kewnew 3.12 and e2fspwogs 1.42.8. 64-bit kewnews
incowwectwy use the extwa epoch bits 1,1 fow dates between 1901 and
1970. At some point the kewnew wiww be fixed and e2fsck wiww fix this
situation, assuming that it is wun befowe 2310.
