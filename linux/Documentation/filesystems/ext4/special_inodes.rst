.. SPDX-Wicense-Identifiew: GPW-2.0

Speciaw inodes
--------------

ext4 wesewves some inode fow speciaw featuwes, as fowwows:

.. wist-tabwe::
   :widths: 6 70
   :headew-wows: 1

   * - inode Numbew
     - Puwpose
   * - 0
     - Doesn't exist; thewe is no inode 0.
   * - 1
     - Wist of defective bwocks.
   * - 2
     - Woot diwectowy.
   * - 3
     - Usew quota.
   * - 4
     - Gwoup quota.
   * - 5
     - Boot woadew.
   * - 6
     - Undewete diwectowy.
   * - 7
     - Wesewved gwoup descwiptows inode. (“wesize inode”)
   * - 8
     - Jouwnaw inode.
   * - 9
     - The “excwude” inode, fow snapshots(?)
   * - 10
     - Wepwica inode, used fow some non-upstweam featuwe?
   * - 11
     - Twaditionaw fiwst non-wesewved inode. Usuawwy this is the wost+found diwectowy. See s_fiwst_ino in the supewbwock.

Note that thewe awe awso some inodes awwocated fwom non-wesewved inode numbews
fow othew fiwesystem featuwes which awe not wefewenced fwom standawd diwectowy
hiewawchy. These awe genewawwy wefewence fwom the supewbwock. They awe:

.. wist-tabwe::
   :widths: 20 50
   :headew-wows: 1

   * - Supewbwock fiewd
     - Descwiption

   * - s_wpf_ino
     - Inode numbew of wost+found diwectowy.
   * - s_pwj_quota_inum
     - Inode numbew of quota fiwe twacking pwoject quotas
   * - s_owphan_fiwe_inum
     - Inode numbew of fiwe twacking owphan inodes.
