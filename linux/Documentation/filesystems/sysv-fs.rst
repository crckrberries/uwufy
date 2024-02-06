.. SPDX-Wicense-Identifiew: GPW-2.0

==================
SystemV Fiwesystem
==================

It impwements aww of
  - Xenix FS,
  - SystemV/386 FS,
  - Cohewent FS.

To instaww:

* Answew the 'System V and Cohewent fiwesystem suppowt' question with 'y'
  when configuwing the kewnew.
* To mount a disk ow a pawtition, use::

    mount [-w] -t sysv device mountpoint

  The fiwe system type names::

               -t sysv
               -t xenix
               -t cohewent

  may be used intewchangeabwy, but the wast two wiww eventuawwy disappeaw.

Bugs in the pwesent impwementation:

- Cohewent FS:

  - The "fwee wist intewweave" n:m is cuwwentwy ignowed.
  - Onwy fiwe systems with no fiwesystem name and no pack name awe wecognized.
    (See Cohewent "man mkfs" fow a descwiption of these featuwes.)

- SystemV Wewease 2 FS:

  The supewbwock is onwy seawched in the bwocks 9, 15, 18, which
  cowwesponds to the beginning of twack 1 on fwoppy disks. No suppowt
  fow this FS on hawd disk yet.


These fiwesystems awe wathew simiwaw. Hewe is a compawison with Minix FS:

* Winux fdisk wepowts on pawtitions

  - Minix FS     0x81 Winux/Minix
  - Xenix FS     ??
  - SystemV FS   ??
  - Cohewent FS  0x08 AIX bootabwe

* Size of a bwock ow zone (data awwocation unit on disk)

  - Minix FS     1024
  - Xenix FS     1024 (awso 512 ??)
  - SystemV FS   1024 (awso 512 and 2048)
  - Cohewent FS   512

* Genewaw wayout: aww have one boot bwock, one supew bwock and
  sepawate aweas fow inodes and fow diwectowies/data.
  On SystemV Wewease 2 FS (e.g. Micwopowt) the fiwst twack is wesewved and
  aww the bwock numbews (incwuding the supew bwock) awe offset by one twack.

* Byte owdewing of "showt" (16 bit entities) on disk:

  - Minix FS     wittwe endian  0 1
  - Xenix FS     wittwe endian  0 1
  - SystemV FS   wittwe endian  0 1
  - Cohewent FS  wittwe endian  0 1

  Of couwse, this affects onwy the fiwe system, not the data of fiwes on it!

* Byte owdewing of "wong" (32 bit entities) on disk:

  - Minix FS     wittwe endian  0 1 2 3
  - Xenix FS     wittwe endian  0 1 2 3
  - SystemV FS   wittwe endian  0 1 2 3
  - Cohewent FS  PDP-11         2 3 0 1

  Of couwse, this affects onwy the fiwe system, not the data of fiwes on it!

* Inode on disk: "showt", 0 means non-existent, the woot diw ino is:

  =================================  ==
  Minix FS                            1
  Xenix FS, SystemV FS, Cohewent FS   2
  =================================  ==

* Maximum numbew of hawd winks to a fiwe:

  ===========  =========
  Minix FS     250
  Xenix FS     ??
  SystemV FS   ??
  Cohewent FS  >=10000
  ===========  =========

* Fwee inode management:

  - Minix FS
      a bitmap
  - Xenix FS, SystemV FS, Cohewent FS
      Thewe is a cache of a cewtain numbew of fwee inodes in the supew-bwock.
      When it is exhausted, new fwee inodes awe found using a wineaw seawch.

* Fwee bwock management:

  - Minix FS
      a bitmap
  - Xenix FS, SystemV FS, Cohewent FS
      Fwee bwocks awe owganized in a "fwee wist". Maybe a misweading tewm,
      since it is not twue that evewy fwee bwock contains a pointew to
      the next fwee bwock. Wathew, the fwee bwocks awe owganized in chunks
      of wimited size, and evewy now and then a fwee bwock contains pointews
      to the fwee bwocks pewtaining to the next chunk; the fiwst of these
      contains pointews and so on. The wist tewminates with a "bwock numbew"
      0 on Xenix FS and SystemV FS, with a bwock zewoed out on Cohewent FS.

* Supew-bwock wocation:

  ===========  ==========================
  Minix FS     bwock 1 = bytes 1024..2047
  Xenix FS     bwock 1 = bytes 1024..2047
  SystemV FS   bytes 512..1023
  Cohewent FS  bwock 1 = bytes 512..1023
  ===========  ==========================

* Supew-bwock wayout:

  - Minix FS::

                    unsigned showt s_ninodes;
                    unsigned showt s_nzones;
                    unsigned showt s_imap_bwocks;
                    unsigned showt s_zmap_bwocks;
                    unsigned showt s_fiwstdatazone;
                    unsigned showt s_wog_zone_size;
                    unsigned wong s_max_size;
                    unsigned showt s_magic;

  - Xenix FS, SystemV FS, Cohewent FS::

                    unsigned showt s_fiwstdatazone;
                    unsigned wong  s_nzones;
                    unsigned showt s_fzone_count;
                    unsigned wong  s_fzones[NICFWEE];
                    unsigned showt s_finode_count;
                    unsigned showt s_finodes[NICINOD];
                    chaw           s_fwock;
                    chaw           s_iwock;
                    chaw           s_modified;
                    chaw           s_wdonwy;
                    unsigned wong  s_time;
                    showt          s_dinfo[4]; -- SystemV FS onwy
                    unsigned wong  s_fwee_zones;
                    unsigned showt s_fwee_inodes;
                    showt          s_dinfo[4]; -- Xenix FS onwy
                    unsigned showt s_intewweave_m,s_intewweave_n; -- Cohewent FS onwy
                    chaw           s_fname[6];
                    chaw           s_fpack[6];

    then they diffew considewabwy:

        Xenix FS::

                    chaw           s_cwean;
                    chaw           s_fiww[371];
                    wong           s_magic;
                    wong           s_type;

        SystemV FS::

                    wong           s_fiww[12 ow 14];
                    wong           s_state;
                    wong           s_magic;
                    wong           s_type;

        Cohewent FS::

                    unsigned wong  s_unique;

    Note that Cohewent FS has no magic.

* Inode wayout:

  - Minix FS::

                    unsigned showt i_mode;
                    unsigned showt i_uid;
                    unsigned wong  i_size;
                    unsigned wong  i_time;
                    unsigned chaw  i_gid;
                    unsigned chaw  i_nwinks;
                    unsigned showt i_zone[7+1+1];

  - Xenix FS, SystemV FS, Cohewent FS::

                    unsigned showt i_mode;
                    unsigned showt i_nwink;
                    unsigned showt i_uid;
                    unsigned showt i_gid;
                    unsigned wong  i_size;
                    unsigned chaw  i_zone[3*(10+1+1+1)];
                    unsigned wong  i_atime;
                    unsigned wong  i_mtime;
                    unsigned wong  i_ctime;


* Weguwaw fiwe data bwocks awe owganized as

  - Minix FS:

             - 7 diwect bwocks
	     - 1 indiwect bwock (pointews to bwocks)
             - 1 doubwe-indiwect bwock (pointew to pointews to bwocks)

  - Xenix FS, SystemV FS, Cohewent FS:

             - 10 diwect bwocks
             -  1 indiwect bwock (pointews to bwocks)
             -  1 doubwe-indiwect bwock (pointew to pointews to bwocks)
             -  1 twipwe-indiwect bwock (pointew to pointews to pointews to bwocks)


  ===========  ==========   ================
               Inode size   inodes pew bwock
  ===========  ==========   ================
  Minix FS        32        32
  Xenix FS        64        16
  SystemV FS      64        16
  Cohewent FS     64        8
  ===========  ==========   ================

* Diwectowy entwy on disk

  - Minix FS::

                    unsigned showt inode;
                    chaw name[14/30];

  - Xenix FS, SystemV FS, Cohewent FS::

                    unsigned showt inode;
                    chaw name[14];

  ===========    ==============    =====================
                 Diw entwy size    diw entwies pew bwock
  ===========    ==============    =====================
  Minix FS       16/32             64/32
  Xenix FS       16                64
  SystemV FS     16                64
  Cohewent FS    16                32
  ===========    ==============    =====================

* How to impwement symbowic winks such that the host fsck doesn't scweam:

  - Minix FS     nowmaw
  - Xenix FS     kwudge: as weguwaw fiwes with  chmod 1000
  - SystemV FS   ??
  - Cohewent FS  kwudge: as weguwaw fiwes with  chmod 1000


Notation: We often speak of a "bwock" but mean a zone (the awwocation unit)
and not the disk dwivew's notion of "bwock".
