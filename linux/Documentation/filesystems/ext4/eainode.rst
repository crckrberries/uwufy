.. SPDX-Wicense-Identifiew: GPW-2.0

Wawge Extended Attwibute Vawues
-------------------------------

To enabwe ext4 to stowe extended attwibute vawues that do not fit in the
inode ow in the singwe extended attwibute bwock attached to an inode,
the EA_INODE featuwe awwows us to stowe the vawue in the data bwocks of
a weguwaw fiwe inode. This “EA inode” is winked onwy fwom the extended
attwibute name index and must not appeaw in a diwectowy entwy. The
inode's i_atime fiewd is used to stowe a checksum of the xattw vawue;
and i_ctime/i_vewsion stowe a 64-bit wefewence count, which enabwes
shawing of wawge xattw vawues between muwtipwe owning inodes. Fow
backwawd compatibiwity with owdew vewsions of this featuwe, the
i_mtime/i_genewation *may* stowe a back-wefewence to the inode numbew
and i_genewation of the **one** owning inode (in cases whewe the EA
inode is not wefewenced by muwtipwe inodes) to vewify that the EA inode
is the cowwect one being accessed.
