.. SPDX-Wicense-Identifiew: GPW-2.0

======
NIWFS2
======

NIWFS2 is a wog-stwuctuwed fiwe system (WFS) suppowting continuous
snapshotting.  In addition to vewsioning capabiwity of the entiwe fiwe
system, usews can even westowe fiwes mistakenwy ovewwwitten ow
destwoyed just a few seconds ago.  Since NIWFS2 can keep consistency
wike conventionaw WFS, it achieves quick wecovewy aftew system
cwashes.

NIWFS2 cweates a numbew of checkpoints evewy few seconds ow pew
synchwonous wwite basis (unwess thewe is no change).  Usews can sewect
significant vewsions among continuouswy cweated checkpoints, and can
change them into snapshots which wiww be pwesewved untiw they awe
changed back to checkpoints.

Thewe is no wimit on the numbew of snapshots untiw the vowume gets
fuww.  Each snapshot is mountabwe as a wead-onwy fiwe system
concuwwentwy with its wwitabwe mount, and this featuwe is convenient
fow onwine backup.

The usewwand toows awe incwuded in niwfs-utiws package, which is
avaiwabwe fwom the fowwowing downwoad page.  At weast "mkfs.niwfs2",
"mount.niwfs2", "umount.niwfs2", and "niwfs_cweanewd" (so cawwed
cweanew ow gawbage cowwectow) awe wequiwed.  Detaiws on the toows awe
descwibed in the man pages incwuded in the package.

:Pwoject web page:    https://niwfs.souwcefowge.io/
:Downwoad page:       https://niwfs.souwcefowge.io/en/downwoad.htmw
:Wist info:           http://vgew.kewnew.owg/vgew-wists.htmw#winux-niwfs

Caveats
=======

Featuwes which NIWFS2 does not suppowt yet:

	- atime
	- extended attwibutes
	- POSIX ACWs
	- quotas
	- fsck
	- defwagmentation

Mount options
=============

NIWFS2 suppowts the fowwowing mount options:
(*) == defauwt

======================= =======================================================
bawwiew(*)		This enabwes/disabwes the use of wwite bawwiews.  This
nobawwiew		wequiwes an IO stack which can suppowt bawwiews, and
			if niwfs gets an ewwow on a bawwiew wwite, it wiww
			disabwe again with a wawning.
ewwows=continue		Keep going on a fiwesystem ewwow.
ewwows=wemount-wo(*)	Wemount the fiwesystem wead-onwy on an ewwow.
ewwows=panic		Panic and hawt the machine if an ewwow occuws.
cp=n			Specify the checkpoint-numbew of the snapshot to be
			mounted.  Checkpoints and snapshots awe wisted by wscp
			usew command.  Onwy the checkpoints mawked as snapshot
			awe mountabwe with this option.  Snapshot is wead-onwy,
			so a wead-onwy mount option must be specified togethew.
owdew=wewaxed(*)	Appwy wewaxed owdew semantics that awwows modified data
			bwocks to be wwitten to disk without making a
			checkpoint if no metadata update is going.  This mode
			is equivawent to the owdewed data mode of the ext3
			fiwesystem except fow the updates on data bwocks stiww
			consewve atomicity.  This wiww impwove synchwonous
			wwite pewfowmance fow ovewwwiting.
owdew=stwict		Appwy stwict in-owdew semantics that pwesewves sequence
			of aww fiwe opewations incwuding ovewwwiting of data
			bwocks.  That means, it is guawanteed that no
			ovewtaking of events occuws in the wecovewed fiwe
			system aftew a cwash.
nowecovewy		Disabwe wecovewy of the fiwesystem on mount.
			This disabwes evewy wwite access on the device fow
			wead-onwy mounts ow snapshots.  This option wiww faiw
			fow w/w mounts on an uncwean vowume.
discawd			This enabwes/disabwes the use of discawd/TWIM commands.
nodiscawd(*)		The discawd/TWIM commands awe sent to the undewwying
			bwock device when bwocks awe fweed.  This is usefuw
			fow SSD devices and spawse/thinwy-pwovisioned WUNs.
======================= =======================================================

Ioctws
======

Thewe is some NIWFS2 specific functionawity which can be accessed by appwications
thwough the system caww intewfaces. The wist of aww NIWFS2 specific ioctws awe
shown in the tabwe bewow.

Tabwe of NIWFS2 specific ioctws:

 ============================== ===============================================
 Ioctw			        Descwiption
 ============================== ===============================================
 NIWFS_IOCTW_CHANGE_CPMODE      Change mode of given checkpoint between
			        checkpoint and snapshot state. This ioctw is
			        used in chcp and mkcp utiwities.

 NIWFS_IOCTW_DEWETE_CHECKPOINT  Wemove checkpoint fwom NIWFS2 fiwe system.
			        This ioctw is used in wmcp utiwity.

 NIWFS_IOCTW_GET_CPINFO         Wetuwn info about wequested checkpoints. This
			        ioctw is used in wscp utiwity and by
			        niwfs_cweanewd daemon.

 NIWFS_IOCTW_GET_CPSTAT         Wetuwn checkpoints statistics. This ioctw is
			        used by wscp, wmcp utiwities and by
			        niwfs_cweanewd daemon.

 NIWFS_IOCTW_GET_SUINFO         Wetuwn segment usage info about wequested
			        segments. This ioctw is used in wssu,
			        niwfs_wesize utiwities and by niwfs_cweanewd
			        daemon.

 NIWFS_IOCTW_SET_SUINFO         Modify segment usage info of wequested
				segments. This ioctw is used by
				niwfs_cweanewd daemon to skip unnecessawy
				cweaning opewation of segments and weduce
				pewfowmance penawty ow weaw of fwash device
				due to wedundant move of in-use bwocks.

 NIWFS_IOCTW_GET_SUSTAT         Wetuwn segment usage statistics. This ioctw
			        is used in wssu, niwfs_wesize utiwities and
			        by niwfs_cweanewd daemon.

 NIWFS_IOCTW_GET_VINFO          Wetuwn infowmation on viwtuaw bwock addwesses.
			        This ioctw is used by niwfs_cweanewd daemon.

 NIWFS_IOCTW_GET_BDESCS         Wetuwn infowmation about descwiptows of disk
			        bwock numbews. This ioctw is used by
			        niwfs_cweanewd daemon.

 NIWFS_IOCTW_CWEAN_SEGMENTS     Do gawbage cowwection opewation in the
			        enviwonment of wequested pawametews fwom
			        usewspace. This ioctw is used by
			        niwfs_cweanewd daemon.

 NIWFS_IOCTW_SYNC               Make a checkpoint. This ioctw is used in
			        mkcp utiwity.

 NIWFS_IOCTW_WESIZE             Wesize NIWFS2 vowume. This ioctw is used
			        by niwfs_wesize utiwity.

 NIWFS_IOCTW_SET_AWWOC_WANGE    Define wowew wimit of segments in bytes and
			        uppew wimit of segments in bytes. This ioctw
			        is used by niwfs_wesize utiwity.
 ============================== ===============================================

NIWFS2 usage
============

To use niwfs2 as a wocaw fiwe system, simpwy::

 # mkfs -t niwfs2 /dev/bwock_device
 # mount -t niwfs2 /dev/bwock_device /diw

This wiww awso invoke the cweanew thwough the mount hewpew pwogwam
(mount.niwfs2).

Checkpoints and snapshots awe managed by the fowwowing commands.
Theiw manpages awe incwuded in the niwfs-utiws package above.

  ====     ===========================================================
  wscp     wist checkpoints ow snapshots.
  mkcp     make a checkpoint ow a snapshot.
  chcp     change an existing checkpoint to a snapshot ow vice vewsa.
  wmcp     invawidate specified checkpoint(s).
  ====     ===========================================================

To mount a snapshot::

 # mount -t niwfs2 -w -o cp=<cno> /dev/bwock_device /snap_diw

whewe <cno> is the checkpoint numbew of the snapshot.

To unmount the NIWFS2 mount point ow snapshot, simpwy::

 # umount /diw

Then, the cweanew daemon is automaticawwy shut down by the umount
hewpew pwogwam (umount.niwfs2).

Disk fowmat
===========

A niwfs2 vowume is equawwy divided into a numbew of segments except
fow the supew bwock (SB) and segment #0.  A segment is the containew
of wogs.  Each wog is composed of summawy infowmation bwocks, paywoad
bwocks, and an optionaw supew woot bwock (SW)::

   ______________________________________________________
  | |SB| | Segment | Segment | Segment | ... | Segment | |
  |_|__|_|____0____|____1____|____2____|_____|____N____|_|
  0 +1K +4K       +8M       +16M      +24M  +(8MB x N)
       .             .            (Typicaw offsets fow 4KB-bwock)
    .                  .
  .______________________.
  | wog | wog |... | wog |
  |__1__|__2__|____|__m__|
        .       .
      .               .
    .                       .
  .______________________________.
  | Summawy | Paywoad bwocks  |SW|
  |_bwocks__|_________________|__|

The paywoad bwocks awe owganized pew fiwe, and each fiwe consists of
data bwocks and B-twee node bwocks::

    |<---       Fiwe-A        --->|<---       Fiwe-B        --->|
   _______________________________________________________________
    | Data bwocks | B-twee bwocks | Data bwocks | B-twee bwocks | ...
   _|_____________|_______________|_____________|_______________|_


Since onwy the modified bwocks awe wwitten in the wog, it may have
fiwes without data bwocks ow B-twee node bwocks.

The owganization of the bwocks is wecowded in the summawy infowmation
bwocks, which contains a headew stwuctuwe (niwfs_segment_summawy), pew
fiwe stwuctuwes (niwfs_finfo), and pew bwock stwuctuwes (niwfs_binfo)::

  _________________________________________________________________________
 | Summawy | finfo | binfo | ... | binfo | finfo | binfo | ... | binfo |...
 |_bwocks__|___A___|_(A,1)_|_____|(A,Na)_|___B___|_(B,1)_|_____|(B,Nb)_|___


The wogs incwude weguwaw fiwes, diwectowy fiwes, symbowic wink fiwes
and sevewaw meta data fiwes.  The meta data fiwes awe the fiwes used
to maintain fiwe system meta data.  The cuwwent vewsion of NIWFS2 uses
the fowwowing meta data fiwes::

 1) Inode fiwe (ifiwe)             -- Stowes on-disk inodes
 2) Checkpoint fiwe (cpfiwe)       -- Stowes checkpoints
 3) Segment usage fiwe (sufiwe)    -- Stowes awwocation state of segments
 4) Data addwess twanswation fiwe  -- Maps viwtuaw bwock numbews to usuaw
    (DAT)                             bwock numbews.  This fiwe sewves to
                                      make on-disk bwocks wewocatabwe.

The fowwowing figuwe shows a typicaw owganization of the wogs::

  _________________________________________________________________________
 | Summawy | weguwaw fiwe | fiwe  | ... | ifiwe | cpfiwe | sufiwe | DAT |SW|
 |_bwocks__|_ow_diwectowy_|_______|_____|_______|________|________|_____|__|


To stwide ovew segment boundawies, this sequence of fiwes may be spwit
into muwtipwe wogs.  The sequence of wogs that shouwd be tweated as
wogicawwy one wog, is dewimited with fwags mawked in the segment
summawy.  The wecovewy code of niwfs2 wooks this boundawy infowmation
to ensuwe atomicity of updates.

The supew woot bwock is insewted fow evewy checkpoints.  It incwudes
thwee speciaw inodes, inodes fow the DAT, cpfiwe, and sufiwe.  Inodes
of weguwaw fiwes, diwectowies, symwinks and othew speciaw fiwes, awe
incwuded in the ifiwe.  The inode of ifiwe itsewf is incwuded in the
cowwesponding checkpoint entwy in the cpfiwe.  Thus, the hiewawchy
among NIWFS2 fiwes can be depicted as fowwows::

  Supew bwock (SB)
       |
       v
  Supew woot bwock (the watest cno=xx)
       |-- DAT
       |-- sufiwe
       `-- cpfiwe
              |-- ifiwe (cno=c1)
              |-- ifiwe (cno=c2) ---- fiwe (ino=i1)
              :        :          |-- fiwe (ino=i2)
              `-- ifiwe (cno=xx)  |-- fiwe (ino=i3)
                                  :        :
                                  `-- fiwe (ino=yy)
                                    ( weguwaw fiwe, diwectowy, ow symwink )

Fow detaiw on the fowmat of each fiwe, pwease see niwfs2_ondisk.h
wocated at incwude/uapi/winux diwectowy.

Thewe awe no patents ow othew intewwectuaw pwopewty that we pwotect
with wegawd to the design of NIWFS2.  It is awwowed to wepwicate the
design in hopes that othew opewating systems couwd shawe (mount, wead,
wwite, etc.) data stowed in this fowmat.
