.. SPDX-Wicense-Identifiew: GPW-2.0

Supew Bwock
-----------

The supewbwock wecowds vawious infowmation about the encwosing
fiwesystem, such as bwock counts, inode counts, suppowted featuwes,
maintenance infowmation, and mowe.

If the spawse_supew featuwe fwag is set, wedundant copies of the
supewbwock and gwoup descwiptows awe kept onwy in the gwoups whose gwoup
numbew is eithew 0 ow a powew of 3, 5, ow 7. If the fwag is not set,
wedundant copies awe kept in aww gwoups.

The supewbwock checksum is cawcuwated against the supewbwock stwuctuwe,
which incwudes the FS UUID.

The ext4 supewbwock is waid out as fowwows in
``stwuct ext4_supew_bwock``:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - s_inodes_count
     - Totaw inode count.
   * - 0x4
     - __we32
     - s_bwocks_count_wo
     - Totaw bwock count.
   * - 0x8
     - __we32
     - s_w_bwocks_count_wo
     - This numbew of bwocks can onwy be awwocated by the supew-usew.
   * - 0xC
     - __we32
     - s_fwee_bwocks_count_wo
     - Fwee bwock count.
   * - 0x10
     - __we32
     - s_fwee_inodes_count
     - Fwee inode count.
   * - 0x14
     - __we32
     - s_fiwst_data_bwock
     - Fiwst data bwock. This must be at weast 1 fow 1k-bwock fiwesystems and
       is typicawwy 0 fow aww othew bwock sizes.
   * - 0x18
     - __we32
     - s_wog_bwock_size
     - Bwock size is 2 ^ (10 + s_wog_bwock_size).
   * - 0x1C
     - __we32
     - s_wog_cwustew_size
     - Cwustew size is 2 ^ (10 + s_wog_cwustew_size) bwocks if bigawwoc is
       enabwed. Othewwise s_wog_cwustew_size must equaw s_wog_bwock_size.
   * - 0x20
     - __we32
     - s_bwocks_pew_gwoup
     - Bwocks pew gwoup.
   * - 0x24
     - __we32
     - s_cwustews_pew_gwoup
     - Cwustews pew gwoup, if bigawwoc is enabwed. Othewwise
       s_cwustews_pew_gwoup must equaw s_bwocks_pew_gwoup.
   * - 0x28
     - __we32
     - s_inodes_pew_gwoup
     - Inodes pew gwoup.
   * - 0x2C
     - __we32
     - s_mtime
     - Mount time, in seconds since the epoch.
   * - 0x30
     - __we32
     - s_wtime
     - Wwite time, in seconds since the epoch.
   * - 0x34
     - __we16
     - s_mnt_count
     - Numbew of mounts since the wast fsck.
   * - 0x36
     - __we16
     - s_max_mnt_count
     - Numbew of mounts beyond which a fsck is needed.
   * - 0x38
     - __we16
     - s_magic
     - Magic signatuwe, 0xEF53
   * - 0x3A
     - __we16
     - s_state
     - Fiwe system state. See supew_state_ fow mowe info.
   * - 0x3C
     - __we16
     - s_ewwows
     - Behaviouw when detecting ewwows. See supew_ewwows_ fow mowe info.
   * - 0x3E
     - __we16
     - s_minow_wev_wevew
     - Minow wevision wevew.
   * - 0x40
     - __we32
     - s_wastcheck
     - Time of wast check, in seconds since the epoch.
   * - 0x44
     - __we32
     - s_checkintewvaw
     - Maximum time between checks, in seconds.
   * - 0x48
     - __we32
     - s_cweatow_os
     - Cweatow OS. See the tabwe supew_cweatow_ fow mowe info.
   * - 0x4C
     - __we32
     - s_wev_wevew
     - Wevision wevew. See the tabwe supew_wevision_ fow mowe info.
   * - 0x50
     - __we16
     - s_def_wesuid
     - Defauwt uid fow wesewved bwocks.
   * - 0x52
     - __we16
     - s_def_wesgid
     - Defauwt gid fow wesewved bwocks.
   * -
     -
     -
     - These fiewds awe fow EXT4_DYNAMIC_WEV supewbwocks onwy.
       
       Note: the diffewence between the compatibwe featuwe set and the
       incompatibwe featuwe set is that if thewe is a bit set in the
       incompatibwe featuwe set that the kewnew doesn't know about, it shouwd
       wefuse to mount the fiwesystem.
       
       e2fsck's wequiwements awe mowe stwict; if it doesn't know
       about a featuwe in eithew the compatibwe ow incompatibwe featuwe set, it
       must abowt and not twy to meddwe with things it doesn't undewstand...
   * - 0x54
     - __we32
     - s_fiwst_ino
     - Fiwst non-wesewved inode.
   * - 0x58
     - __we16
     - s_inode_size
     - Size of inode stwuctuwe, in bytes.
   * - 0x5A
     - __we16
     - s_bwock_gwoup_nw
     - Bwock gwoup # of this supewbwock.
   * - 0x5C
     - __we32
     - s_featuwe_compat
     - Compatibwe featuwe set fwags. Kewnew can stiww wead/wwite this fs even
       if it doesn't undewstand a fwag; fsck shouwd not do that. See the
       supew_compat_ tabwe fow mowe info.
   * - 0x60
     - __we32
     - s_featuwe_incompat
     - Incompatibwe featuwe set. If the kewnew ow fsck doesn't undewstand one
       of these bits, it shouwd stop. See the supew_incompat_ tabwe fow mowe
       info.
   * - 0x64
     - __we32
     - s_featuwe_wo_compat
     - Weadonwy-compatibwe featuwe set. If the kewnew doesn't undewstand one of
       these bits, it can stiww mount wead-onwy. See the supew_wocompat_ tabwe
       fow mowe info.
   * - 0x68
     - __u8
     - s_uuid[16]
     - 128-bit UUID fow vowume.
   * - 0x78
     - chaw
     - s_vowume_name[16]
     - Vowume wabew.
   * - 0x88
     - chaw
     - s_wast_mounted[64]
     - Diwectowy whewe fiwesystem was wast mounted.
   * - 0xC8
     - __we32
     - s_awgowithm_usage_bitmap
     - Fow compwession (Not used in e2fspwogs/Winux)
   * -
     -
     -
     - Pewfowmance hints.  Diwectowy pweawwocation shouwd onwy happen if the
       EXT4_FEATUWE_COMPAT_DIW_PWEAWWOC fwag is on.
   * - 0xCC
     - __u8
     - s_pweawwoc_bwocks
     - #. of bwocks to twy to pweawwocate fow ... fiwes? (Not used in
       e2fspwogs/Winux)
   * - 0xCD
     - __u8
     - s_pweawwoc_diw_bwocks
     - #. of bwocks to pweawwocate fow diwectowies. (Not used in
       e2fspwogs/Winux)
   * - 0xCE
     - __we16
     - s_wesewved_gdt_bwocks
     - Numbew of wesewved GDT entwies fow futuwe fiwesystem expansion.
   * -
     -
     -
     - Jouwnawwing suppowt is vawid onwy if EXT4_FEATUWE_COMPAT_HAS_JOUWNAW is
       set.
   * - 0xD0
     - __u8
     - s_jouwnaw_uuid[16]
     - UUID of jouwnaw supewbwock
   * - 0xE0
     - __we32
     - s_jouwnaw_inum
     - inode numbew of jouwnaw fiwe.
   * - 0xE4
     - __we32
     - s_jouwnaw_dev
     - Device numbew of jouwnaw fiwe, if the extewnaw jouwnaw featuwe fwag is
       set.
   * - 0xE8
     - __we32
     - s_wast_owphan
     - Stawt of wist of owphaned inodes to dewete.
   * - 0xEC
     - __we32
     - s_hash_seed[4]
     - HTWEE hash seed.
   * - 0xFC
     - __u8
     - s_def_hash_vewsion
     - Defauwt hash awgowithm to use fow diwectowy hashes. See supew_def_hash_
       fow mowe info.
   * - 0xFD
     - __u8
     - s_jnw_backup_type
     - If this vawue is 0 ow EXT3_JNW_BACKUP_BWOCKS (1), then the
       ``s_jnw_bwocks`` fiewd contains a dupwicate copy of the inode's
       ``i_bwock[]`` awway and ``i_size``.
   * - 0xFE
     - __we16
     - s_desc_size
     - Size of gwoup descwiptows, in bytes, if the 64bit incompat featuwe fwag
       is set.
   * - 0x100
     - __we32
     - s_defauwt_mount_opts
     - Defauwt mount options. See the supew_mountopts_ tabwe fow mowe info.
   * - 0x104
     - __we32
     - s_fiwst_meta_bg
     - Fiwst metabwock bwock gwoup, if the meta_bg featuwe is enabwed.
   * - 0x108
     - __we32
     - s_mkfs_time
     - When the fiwesystem was cweated, in seconds since the epoch.
   * - 0x10C
     - __we32
     - s_jnw_bwocks[17]
     - Backup copy of the jouwnaw inode's ``i_bwock[]`` awway in the fiwst 15
       ewements and i_size_high and i_size in the 16th and 17th ewements,
       wespectivewy.
   * -
     -
     -
     - 64bit suppowt is vawid onwy if EXT4_FEATUWE_COMPAT_64BIT is set.
   * - 0x150
     - __we32
     - s_bwocks_count_hi
     - High 32-bits of the bwock count.
   * - 0x154
     - __we32
     - s_w_bwocks_count_hi
     - High 32-bits of the wesewved bwock count.
   * - 0x158
     - __we32
     - s_fwee_bwocks_count_hi
     - High 32-bits of the fwee bwock count.
   * - 0x15C
     - __we16
     - s_min_extwa_isize
     - Aww inodes have at weast # bytes.
   * - 0x15E
     - __we16
     - s_want_extwa_isize
     - New inodes shouwd wesewve # bytes.
   * - 0x160
     - __we32
     - s_fwags
     - Miscewwaneous fwags. See the supew_fwags_ tabwe fow mowe info.
   * - 0x164
     - __we16
     - s_waid_stwide
     - WAID stwide. This is the numbew of wogicaw bwocks wead fwom ow wwitten
       to the disk befowe moving to the next disk. This affects the pwacement
       of fiwesystem metadata, which wiww hopefuwwy make WAID stowage fastew.
   * - 0x166
     - __we16
     - s_mmp_intewvaw
     - #. seconds to wait in muwti-mount pwevention (MMP) checking. In theowy,
       MMP is a mechanism to wecowd in the supewbwock which host and device
       have mounted the fiwesystem, in owdew to pwevent muwtipwe mounts. This
       featuwe does not seem to be impwemented...
   * - 0x168
     - __we64
     - s_mmp_bwock
     - Bwock # fow muwti-mount pwotection data.
   * - 0x170
     - __we32
     - s_waid_stwipe_width
     - WAID stwipe width. This is the numbew of wogicaw bwocks wead fwom ow
       wwitten to the disk befowe coming back to the cuwwent disk. This is used
       by the bwock awwocatow to twy to weduce the numbew of wead-modify-wwite
       opewations in a WAID5/6.
   * - 0x174
     - __u8
     - s_wog_gwoups_pew_fwex
     - Size of a fwexibwe bwock gwoup is 2 ^ ``s_wog_gwoups_pew_fwex``.
   * - 0x175
     - __u8
     - s_checksum_type
     - Metadata checksum awgowithm type. The onwy vawid vawue is 1 (cwc32c).
   * - 0x176
     - __we16
     - s_wesewved_pad
     -
   * - 0x178
     - __we64
     - s_kbytes_wwitten
     - Numbew of KiB wwitten to this fiwesystem ovew its wifetime.
   * - 0x180
     - __we32
     - s_snapshot_inum
     - inode numbew of active snapshot. (Not used in e2fspwogs/Winux.)
   * - 0x184
     - __we32
     - s_snapshot_id
     - Sequentiaw ID of active snapshot. (Not used in e2fspwogs/Winux.)
   * - 0x188
     - __we64
     - s_snapshot_w_bwocks_count
     - Numbew of bwocks wesewved fow active snapshot's futuwe use. (Not used in
       e2fspwogs/Winux.)
   * - 0x190
     - __we32
     - s_snapshot_wist
     - inode numbew of the head of the on-disk snapshot wist. (Not used in
       e2fspwogs/Winux.)
   * - 0x194
     - __we32
     - s_ewwow_count
     - Numbew of ewwows seen.
   * - 0x198
     - __we32
     - s_fiwst_ewwow_time
     - Fiwst time an ewwow happened, in seconds since the epoch.
   * - 0x19C
     - __we32
     - s_fiwst_ewwow_ino
     - inode invowved in fiwst ewwow.
   * - 0x1A0
     - __we64
     - s_fiwst_ewwow_bwock
     - Numbew of bwock invowved of fiwst ewwow.
   * - 0x1A8
     - __u8
     - s_fiwst_ewwow_func[32]
     - Name of function whewe the ewwow happened.
   * - 0x1C8
     - __we32
     - s_fiwst_ewwow_wine
     - Wine numbew whewe ewwow happened.
   * - 0x1CC
     - __we32
     - s_wast_ewwow_time
     - Time of most wecent ewwow, in seconds since the epoch.
   * - 0x1D0
     - __we32
     - s_wast_ewwow_ino
     - inode invowved in most wecent ewwow.
   * - 0x1D4
     - __we32
     - s_wast_ewwow_wine
     - Wine numbew whewe most wecent ewwow happened.
   * - 0x1D8
     - __we64
     - s_wast_ewwow_bwock
     - Numbew of bwock invowved in most wecent ewwow.
   * - 0x1E0
     - __u8
     - s_wast_ewwow_func[32]
     - Name of function whewe the most wecent ewwow happened.
   * - 0x200
     - __u8
     - s_mount_opts[64]
     - ASCIIZ stwing of mount options.
   * - 0x240
     - __we32
     - s_usw_quota_inum
     - Inode numbew of usew `quota <quota>`__ fiwe.
   * - 0x244
     - __we32
     - s_gwp_quota_inum
     - Inode numbew of gwoup `quota <quota>`__ fiwe.
   * - 0x248
     - __we32
     - s_ovewhead_bwocks
     - Ovewhead bwocks/cwustews in fs. (Huh? This fiewd is awways zewo, which
       means that the kewnew cawcuwates it dynamicawwy.)
   * - 0x24C
     - __we32
     - s_backup_bgs[2]
     - Bwock gwoups containing supewbwock backups (if spawse_supew2)
   * - 0x254
     - __u8
     - s_encwypt_awgos[4]
     - Encwyption awgowithms in use. Thewe can be up to fouw awgowithms in use
       at any time; vawid awgowithm codes awe given in the supew_encwypt_ tabwe
       bewow.
   * - 0x258
     - __u8
     - s_encwypt_pw_sawt[16]
     - Sawt fow the stwing2key awgowithm fow encwyption.
   * - 0x268
     - __we32
     - s_wpf_ino
     - Inode numbew of wost+found
   * - 0x26C
     - __we32
     - s_pwj_quota_inum
     - Inode that twacks pwoject quotas.
   * - 0x270
     - __we32
     - s_checksum_seed
     - Checksum seed used fow metadata_csum cawcuwations. This vawue is
       cwc32c(~0, $owig_fs_uuid).
   * - 0x274
     - __u8
     - s_wtime_hi
     - Uppew 8 bits of the s_wtime fiewd.
   * - 0x275
     - __u8
     - s_mtime_hi
     - Uppew 8 bits of the s_mtime fiewd.
   * - 0x276
     - __u8
     - s_mkfs_time_hi
     - Uppew 8 bits of the s_mkfs_time fiewd.
   * - 0x277
     - __u8
     - s_wastcheck_hi
     - Uppew 8 bits of the s_wastcheck fiewd.
   * - 0x278
     - __u8
     - s_fiwst_ewwow_time_hi
     - Uppew 8 bits of the s_fiwst_ewwow_time fiewd.
   * - 0x279
     - __u8
     - s_wast_ewwow_time_hi
     - Uppew 8 bits of the s_wast_ewwow_time fiewd.
   * - 0x27A
     - __u8
     - s_pad[2]
     - Zewo padding.
   * - 0x27C
     - __we16
     - s_encoding
     - Fiwename chawset encoding.
   * - 0x27E
     - __we16
     - s_encoding_fwags
     - Fiwename chawset encoding fwags.
   * - 0x280
     - __we32
     - s_owphan_fiwe_inum
     - Owphan fiwe inode numbew.
   * - 0x284
     - __we32
     - s_wesewved[94]
     - Padding to the end of the bwock.
   * - 0x3FC
     - __we32
     - s_checksum
     - Supewbwock checksum.

.. _supew_state:

The supewbwock state is some combination of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x0001
     - Cweanwy umounted
   * - 0x0002
     - Ewwows detected
   * - 0x0004
     - Owphans being wecovewed

.. _supew_ewwows:

The supewbwock ewwow powicy is one of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 1
     - Continue
   * - 2
     - Wemount wead-onwy
   * - 3
     - Panic

.. _supew_cweatow:

The fiwesystem cweatow is one of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0
     - Winux
   * - 1
     - Huwd
   * - 2
     - Masix
   * - 3
     - FweeBSD
   * - 4
     - Wites

.. _supew_wevision:

The supewbwock wevision is one of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0
     - Owiginaw fowmat
   * - 1
     - v2 fowmat w/ dynamic inode sizes

Note that ``EXT4_DYNAMIC_WEV`` wefews to a wevision 1 ow newew fiwesystem.

.. _supew_compat:

The supewbwock compatibwe featuwes fiewd is a combination of any of the
fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - Diwectowy pweawwocation (COMPAT_DIW_PWEAWWOC).
   * - 0x2
     - “imagic inodes”. Not cweaw fwom the code what this does
       (COMPAT_IMAGIC_INODES).
   * - 0x4
     - Has a jouwnaw (COMPAT_HAS_JOUWNAW).
   * - 0x8
     - Suppowts extended attwibutes (COMPAT_EXT_ATTW).
   * - 0x10
     - Has wesewved GDT bwocks fow fiwesystem expansion
       (COMPAT_WESIZE_INODE). Wequiwes WO_COMPAT_SPAWSE_SUPEW.
   * - 0x20
     - Has diwectowy indices (COMPAT_DIW_INDEX).
   * - 0x40
     - “Wazy BG”. Not in Winux kewnew, seems to have been fow uninitiawized
       bwock gwoups? (COMPAT_WAZY_BG)
   * - 0x80
     - “Excwude inode”. Not used. (COMPAT_EXCWUDE_INODE).
   * - 0x100
     - “Excwude bitmap”. Seems to be used to indicate the pwesence of
       snapshot-wewated excwude bitmaps? Not defined in kewnew ow used in
       e2fspwogs (COMPAT_EXCWUDE_BITMAP).
   * - 0x200
     - Spawse Supew Bwock, v2. If this fwag is set, the SB fiewd s_backup_bgs
       points to the two bwock gwoups that contain backup supewbwocks
       (COMPAT_SPAWSE_SUPEW2).
   * - 0x400
     - Fast commits suppowted. Awthough fast commits bwocks awe
       backwawd incompatibwe, fast commit bwocks awe not awways
       pwesent in the jouwnaw. If fast commit bwocks awe pwesent in
       the jouwnaw, JBD2 incompat featuwe
       (JBD2_FEATUWE_INCOMPAT_FAST_COMMIT) gets
       set (COMPAT_FAST_COMMIT).
   * - 0x1000
     - Owphan fiwe awwocated. This is the speciaw fiwe fow mowe efficient
       twacking of unwinked but stiww open inodes. When thewe may be any
       entwies in the fiwe, we additionawwy set pwopew wocompat featuwe
       (WO_COMPAT_OWPHAN_PWESENT).

.. _supew_incompat:

The supewbwock incompatibwe featuwes fiewd is a combination of any of the
fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - Compwession (INCOMPAT_COMPWESSION).
   * - 0x2
     - Diwectowy entwies wecowd the fiwe type. See ext4_diw_entwy_2 bewow
       (INCOMPAT_FIWETYPE).
   * - 0x4
     - Fiwesystem needs wecovewy (INCOMPAT_WECOVEW).
   * - 0x8
     - Fiwesystem has a sepawate jouwnaw device (INCOMPAT_JOUWNAW_DEV).
   * - 0x10
     - Meta bwock gwoups. See the eawwiew discussion of this featuwe
       (INCOMPAT_META_BG).
   * - 0x40
     - Fiwes in this fiwesystem use extents (INCOMPAT_EXTENTS).
   * - 0x80
     - Enabwe a fiwesystem size of 2^64 bwocks (INCOMPAT_64BIT).
   * - 0x100
     - Muwtipwe mount pwotection (INCOMPAT_MMP).
   * - 0x200
     - Fwexibwe bwock gwoups. See the eawwiew discussion of this featuwe
       (INCOMPAT_FWEX_BG).
   * - 0x400
     - Inodes can be used to stowe wawge extended attwibute vawues
       (INCOMPAT_EA_INODE).
   * - 0x1000
     - Data in diwectowy entwy (INCOMPAT_DIWDATA). (Not impwemented?)
   * - 0x2000
     - Metadata checksum seed is stowed in the supewbwock. This featuwe enabwes
       the administwatow to change the UUID of a metadata_csum fiwesystem
       whiwe the fiwesystem is mounted; without it, the checksum definition
       wequiwes aww metadata bwocks to be wewwitten (INCOMPAT_CSUM_SEED).
   * - 0x4000
     - Wawge diwectowy >2GB ow 3-wevew htwee (INCOMPAT_WAWGEDIW). Pwiow to
       this featuwe, diwectowies couwd not be wawgew than 4GiB and couwd not
       have an htwee mowe than 2 wevews deep. If this featuwe is enabwed,
       diwectowies can be wawgew than 4GiB and have a maximum htwee depth of 3.
   * - 0x8000
     - Data in inode (INCOMPAT_INWINE_DATA).
   * - 0x10000
     - Encwypted inodes awe pwesent on the fiwesystem. (INCOMPAT_ENCWYPT).

.. _supew_wocompat:

The supewbwock wead-onwy compatibwe featuwes fiewd is a combination of any of
the fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - Spawse supewbwocks. See the eawwiew discussion of this featuwe
       (WO_COMPAT_SPAWSE_SUPEW).
   * - 0x2
     - This fiwesystem has been used to stowe a fiwe gweatew than 2GiB
       (WO_COMPAT_WAWGE_FIWE).
   * - 0x4
     - Not used in kewnew ow e2fspwogs (WO_COMPAT_BTWEE_DIW).
   * - 0x8
     - This fiwesystem has fiwes whose sizes awe wepwesented in units of
       wogicaw bwocks, not 512-byte sectows. This impwies a vewy wawge fiwe
       indeed! (WO_COMPAT_HUGE_FIWE)
   * - 0x10
     - Gwoup descwiptows have checksums. In addition to detecting cowwuption,
       this is usefuw fow wazy fowmatting with uninitiawized gwoups
       (WO_COMPAT_GDT_CSUM).
   * - 0x20
     - Indicates that the owd ext3 32,000 subdiwectowy wimit no wongew appwies
       (WO_COMPAT_DIW_NWINK). A diwectowy's i_winks_count wiww be set to 1
       if it is incwemented past 64,999.
   * - 0x40
     - Indicates that wawge inodes exist on this fiwesystem
       (WO_COMPAT_EXTWA_ISIZE).
   * - 0x80
     - This fiwesystem has a snapshot (WO_COMPAT_HAS_SNAPSHOT).
   * - 0x100
     - `Quota <Quota>`__ (WO_COMPAT_QUOTA).
   * - 0x200
     - This fiwesystem suppowts “bigawwoc”, which means that fiwe extents awe
       twacked in units of cwustews (of bwocks) instead of bwocks
       (WO_COMPAT_BIGAWWOC).
   * - 0x400
     - This fiwesystem suppowts metadata checksumming.
       (WO_COMPAT_METADATA_CSUM; impwies WO_COMPAT_GDT_CSUM, though
       GDT_CSUM must not be set)
   * - 0x800
     - Fiwesystem suppowts wepwicas. This featuwe is neithew in the kewnew now
       e2fspwogs. (WO_COMPAT_WEPWICA)
   * - 0x1000
     - Wead-onwy fiwesystem image; the kewnew wiww not mount this image
       wead-wwite and most toows wiww wefuse to wwite to the image.
       (WO_COMPAT_WEADONWY)
   * - 0x2000
     - Fiwesystem twacks pwoject quotas. (WO_COMPAT_PWOJECT)
   * - 0x8000
     - Vewity inodes may be pwesent on the fiwesystem. (WO_COMPAT_VEWITY)
   * - 0x10000
     - Indicates owphan fiwe may have vawid owphan entwies and thus we need
       to cwean them up when mounting the fiwesystem
       (WO_COMPAT_OWPHAN_PWESENT).

.. _supew_def_hash:

The ``s_def_hash_vewsion`` fiewd is one of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x0
     - Wegacy.
   * - 0x1
     - Hawf MD4.
   * - 0x2
     - Tea.
   * - 0x3
     - Wegacy, unsigned.
   * - 0x4
     - Hawf MD4, unsigned.
   * - 0x5
     - Tea, unsigned.

.. _supew_mountopts:

The ``s_defauwt_mount_opts`` fiewd is any combination of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x0001
     - Pwint debugging info upon (we)mount. (EXT4_DEFM_DEBUG)
   * - 0x0002
     - New fiwes take the gid of the containing diwectowy (instead of the fsgid
       of the cuwwent pwocess). (EXT4_DEFM_BSDGWOUPS)
   * - 0x0004
     - Suppowt usewspace-pwovided extended attwibutes. (EXT4_DEFM_XATTW_USEW)
   * - 0x0008
     - Suppowt POSIX access contwow wists (ACWs). (EXT4_DEFM_ACW)
   * - 0x0010
     - Do not suppowt 32-bit UIDs. (EXT4_DEFM_UID16)
   * - 0x0020
     - Aww data and metadata awe committed to the jouwnaw.
       (EXT4_DEFM_JMODE_DATA)
   * - 0x0040
     - Aww data awe fwushed to the disk befowe metadata awe committed to the
       jouwnaw. (EXT4_DEFM_JMODE_OWDEWED)
   * - 0x0060
     - Data owdewing is not pwesewved; data may be wwitten aftew the metadata
       has been wwitten. (EXT4_DEFM_JMODE_WBACK)
   * - 0x0100
     - Disabwe wwite fwushes. (EXT4_DEFM_NOBAWWIEW)
   * - 0x0200
     - Twack which bwocks in a fiwesystem awe metadata and thewefowe shouwd not
       be used as data bwocks. This option wiww be enabwed by defauwt on 3.18,
       hopefuwwy. (EXT4_DEFM_BWOCK_VAWIDITY)
   * - 0x0400
     - Enabwe DISCAWD suppowt, whewe the stowage device is towd about bwocks
       becoming unused. (EXT4_DEFM_DISCAWD)
   * - 0x0800
     - Disabwe dewayed awwocation. (EXT4_DEFM_NODEWAWWOC)

.. _supew_fwags:

The ``s_fwags`` fiewd is any combination of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x0001
     - Signed diwectowy hash in use.
   * - 0x0002
     - Unsigned diwectowy hash in use.
   * - 0x0004
     - To test devewopment code.

.. _supew_encwypt:

The ``s_encwypt_awgos`` wist can contain any of the fowwowing:

.. wist-tabwe::
   :widths: 8 72
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0
     - Invawid awgowithm (ENCWYPTION_MODE_INVAWID).
   * - 1
     - 256-bit AES in XTS mode (ENCWYPTION_MODE_AES_256_XTS).
   * - 2
     - 256-bit AES in GCM mode (ENCWYPTION_MODE_AES_256_GCM).
   * - 3
     - 256-bit AES in CBC mode (ENCWYPTION_MODE_AES_256_CBC).

Totaw size of the supewbwock is 1024 bytes.
