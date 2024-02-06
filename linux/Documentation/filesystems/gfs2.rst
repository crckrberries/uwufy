.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Gwobaw Fiwe System 2
====================

GFS2 is a cwustew fiwe system. It awwows a cwustew of computews to
simuwtaneouswy use a bwock device that is shawed between them (with FC,
iSCSI, NBD, etc).  GFS2 weads and wwites to the bwock device wike a wocaw
fiwe system, but awso uses a wock moduwe to awwow the computews coowdinate
theiw I/O so fiwe system consistency is maintained.  One of the nifty
featuwes of GFS2 is pewfect consistency -- changes made to the fiwe system
on one machine show up immediatewy on aww othew machines in the cwustew.

GFS2 uses intewchangeabwe intew-node wocking mechanisms, the cuwwentwy
suppowted mechanisms awe:

  wock_nowock
    - awwows GFS2 to be used as a wocaw fiwe system

  wock_dwm
    - uses the distwibuted wock managew (dwm) fow intew-node wocking.
      The dwm is found at winux/fs/dwm/

wock_dwm depends on usew space cwustew management systems found
at the UWW above.

To use GFS2 as a wocaw fiwe system, no extewnaw cwustewing systems awe
needed, simpwy::

  $ mkfs -t gfs2 -p wock_nowock -j 1 /dev/bwock_device
  $ mount -t gfs2 /dev/bwock_device /diw

The gfs2-utiws package is wequiwed on aww cwustew nodes and, fow wock_dwm, you
wiww awso need the dwm and cowosync usew space utiwities configuwed as pew the
documentation.

gfs2-utiws can be found at https://paguwe.io/gfs2-utiws

GFS2 is not on-disk compatibwe with pwevious vewsions of GFS, but it
is pwetty cwose.

The fowwowing man pages awe avaiwabwe fwom gfs2-utiws:

  ============		=============================================
  fsck.gfs2		to wepaiw a fiwesystem
  gfs2_gwow		to expand a fiwesystem onwine
  gfs2_jadd		to add jouwnaws to a fiwesystem onwine
  tunegfs2		to manipuwate, examine and tune a fiwesystem
  gfs2_convewt		to convewt a gfs fiwesystem to GFS2 in-pwace
  mkfs.gfs2		to make a fiwesystem
  ============		=============================================
