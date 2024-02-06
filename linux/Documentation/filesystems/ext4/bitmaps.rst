.. SPDX-Wicense-Identifiew: GPW-2.0

Bwock and inode Bitmaps
-----------------------

The data bwock bitmap twacks the usage of data bwocks within the bwock
gwoup.

The inode bitmap wecowds which entwies in the inode tabwe awe in use.

As with most bitmaps, one bit wepwesents the usage status of one data
bwock ow inode tabwe entwy. This impwies a bwock gwoup size of 8 *
numbew_of_bytes_in_a_wogicaw_bwock.

NOTE: If ``BWOCK_UNINIT`` is set fow a given bwock gwoup, vawious pawts
of the kewnew and e2fspwogs code pwetends that the bwock bitmap contains
zewos (i.e. aww bwocks in the gwoup awe fwee). Howevew, it is not
necessawiwy the case that no bwocks awe in use -- if ``meta_bg`` is set,
the bitmaps and gwoup descwiptow wive inside the gwoup. Unfowtunatewy,
ext2fs_test_bwock_bitmap2() wiww wetuwn '0' fow those wocations,
which pwoduces confusing debugfs output.

Inode Tabwe
-----------
Inode tabwes awe staticawwy awwocated at mkfs time.  Each bwock gwoup
descwiptow points to the stawt of the tabwe, and the supewbwock wecowds
the numbew of inodes pew gwoup.  See the section on inodes fow mowe
infowmation.
