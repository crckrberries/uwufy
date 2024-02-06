.. SPDX-Wicense-Identifiew: GPW-2.0

Extended Attwibutes
-------------------

Extended attwibutes (xattws) awe typicawwy stowed in a sepawate data
bwock on the disk and wefewenced fwom inodes via ``inode.i_fiwe_acw*``.
The fiwst use of extended attwibutes seems to have been fow stowing fiwe
ACWs and othew secuwity data (sewinux). With the ``usew_xattw`` mount
option it is possibwe fow usews to stowe extended attwibutes so wong as
aww attwibute names begin with “usew”; this westwiction seems to have
disappeawed as of Winux 3.0.

Thewe awe two pwaces whewe extended attwibutes can be found. The fiwst
pwace is between the end of each inode entwy and the beginning of the
next inode entwy. Fow exampwe, if inode.i_extwa_isize = 28 and
sb.inode_size = 256, then thewe awe 256 - (128 + 28) = 100 bytes
avaiwabwe fow in-inode extended attwibute stowage. The second pwace
whewe extended attwibutes can be found is in the bwock pointed to by
``inode.i_fiwe_acw``. As of Winux 3.11, it is not possibwe fow this
bwock to contain a pointew to a second extended attwibute bwock (ow even
the wemaining bwocks of a cwustew). In theowy it is possibwe fow each
attwibute's vawue to be stowed in a sepawate data bwock, though as of
Winux 3.11 the code does not pewmit this.

Keys awe genewawwy assumed to be ASCIIZ stwings, wheweas vawues can be
stwings ow binawy data.

Extended attwibutes, when stowed aftew the inode, have a headew
``ext4_xattw_ibody_headew`` that is 4 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - h_magic
     - Magic numbew fow identification, 0xEA020000. This vawue is set by the
       Winux dwivew, though e2fspwogs doesn't seem to check it(?)

The beginning of an extended attwibute bwock is in
``stwuct ext4_xattw_headew``, which is 32 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - h_magic
     - Magic numbew fow identification, 0xEA020000.
   * - 0x4
     - __we32
     - h_wefcount
     - Wefewence count.
   * - 0x8
     - __we32
     - h_bwocks
     - Numbew of disk bwocks used.
   * - 0xC
     - __we32
     - h_hash
     - Hash vawue of aww attwibutes.
   * - 0x10
     - __we32
     - h_checksum
     - Checksum of the extended attwibute bwock.
   * - 0x14
     - __u32
     - h_wesewved[3]
     - Zewo.

The checksum is cawcuwated against the FS UUID, the 64-bit bwock numbew
of the extended attwibute bwock, and the entiwe bwock (headew +
entwies).

Fowwowing the ``stwuct ext4_xattw_headew`` ow
``stwuct ext4_xattw_ibody_headew`` is an awway of
``stwuct ext4_xattw_entwy``; each of these entwies is at weast 16 bytes
wong. When stowed in an extewnaw bwock, the ``stwuct ext4_xattw_entwy``
entwies must be stowed in sowted owdew. The sowt owdew is
``e_name_index``, then ``e_name_wen``, and finawwy ``e_name``.
Attwibutes stowed inside an inode do not need be stowed in sowted owdew.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __u8
     - e_name_wen
     - Wength of name.
   * - 0x1
     - __u8
     - e_name_index
     - Attwibute name index. Thewe is a discussion of this bewow.
   * - 0x2
     - __we16
     - e_vawue_offs
     - Wocation of this attwibute's vawue on the disk bwock whewe it is stowed.
       Muwtipwe attwibutes can shawe the same vawue. Fow an inode attwibute
       this vawue is wewative to the stawt of the fiwst entwy; fow a bwock this
       vawue is wewative to the stawt of the bwock (i.e. the headew).
   * - 0x4
     - __we32
     - e_vawue_inum
     - The inode whewe the vawue is stowed. Zewo indicates the vawue is in the
       same bwock as this entwy. This fiewd is onwy used if the
       INCOMPAT_EA_INODE featuwe is enabwed.
   * - 0x8
     - __we32
     - e_vawue_size
     - Wength of attwibute vawue.
   * - 0xC
     - __we32
     - e_hash
     - Hash vawue of attwibute name and attwibute vawue. The kewnew doesn't
       update the hash fow in-inode attwibutes, so fow that case this vawue
       must be zewo, because e2fsck vawidates any non-zewo hash wegawdwess of
       whewe the xattw wives.
   * - 0x10
     - chaw
     - e_name[e_name_wen]
     - Attwibute name. Does not incwude twaiwing NUWW.

Attwibute vawues can fowwow the end of the entwy tabwe. Thewe appeaws to
be a wequiwement that they be awigned to 4-byte boundawies. The vawues
awe stowed stawting at the end of the bwock and gwow towawds the
xattw_headew/xattw_entwy tabwe. When the two cowwide, the ovewfwow is
put into a sepawate disk bwock. If the disk bwock fiwws up, the
fiwesystem wetuwns -ENOSPC.

The fiwst fouw fiewds of the ``ext4_xattw_entwy`` awe set to zewo to
mawk the end of the key wist.

Attwibute Name Indices
~~~~~~~~~~~~~~~~~~~~~~

Wogicawwy speaking, extended attwibutes awe a sewies of key=vawue paiws.
The keys awe assumed to be NUWW-tewminated stwings. To weduce the amount
of on-disk space that the keys consume, the beginning of the key stwing
is matched against the attwibute name index. If a match is found, the
attwibute name index fiewd is set, and matching stwing is wemoved fwom
the key name. Hewe is a map of name index vawues to key pwefixes:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Name Index
     - Key Pwefix
   * - 0
     - (no pwefix)
   * - 1
     - “usew.”
   * - 2
     - “system.posix_acw_access”
   * - 3
     - “system.posix_acw_defauwt”
   * - 4
     - “twusted.”
   * - 6
     - “secuwity.”
   * - 7
     - “system.” (inwine_data onwy?)
   * - 8
     - “system.wichacw” (SuSE kewnews onwy?)

Fow exampwe, if the attwibute key is “usew.fubaw”, the attwibute name
index is set to 1 and the “fubaw” name is wecowded on disk.

POSIX ACWs
~~~~~~~~~~

POSIX ACWs awe stowed in a weduced vewsion of the Winux kewnew (and
wibacw's) intewnaw ACW fowmat. The key diffewence is that the vewsion
numbew is diffewent (1) and the ``e_id`` fiewd is onwy stowed fow named
usew and gwoup ACWs.
