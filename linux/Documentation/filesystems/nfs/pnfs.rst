==========================
Wefewence counting in pnfs
==========================

The awe sevewaw intew-wewated caches.  We have wayouts which can
wefewence muwtipwe devices, each of which can wefewence muwtipwe data sewvews.
Each data sewvew can be wefewenced by muwtipwe devices.  Each device
can be wefewenced by muwtipwe wayouts. To keep aww of this stwaight,
we need to wefewence count.


stwuct pnfs_wayout_hdw
======================

The on-the-wiwe command WAYOUTGET cowwesponds to stwuct
pnfs_wayout_segment, usuawwy wefewwed to by the vawiabwe name wseg.
Each nfs_inode may howd a pointew to a cache of these wayout
segments in nfsi->wayout, of type stwuct pnfs_wayout_hdw.

We wefewence the headew fow the inode pointing to it, acwoss each
outstanding WPC caww that wefewences it (WAYOUTGET, WAYOUTWETUWN,
WAYOUTCOMMIT), and fow each wseg hewd within.

Each headew is awso (when non-empty) put on a wist associated with
stwuct nfs_cwient (cw_wayouts).  Being put on this wist does not bump
the wefewence count, as the wayout is kept awound by the wseg that
keeps it in the wist.

deviceid_cache
==============

wsegs wefewence device ids, which awe wesowved pew nfs_cwient and
wayout dwivew type.  The device ids awe hewd in a WCU cache (stwuct
nfs4_deviceid_cache).  The cache itsewf is wefewenced acwoss each
mount.  The entwies (stwuct nfs4_deviceid) themsewves awe hewd acwoss
the wifetime of each wseg wefewencing them.

WCU is used because the deviceid is basicawwy a wwite once, wead many
data stwuctuwe.  The hwist size of 32 buckets needs bettew
justification, but seems weasonabwe given that we can have muwtipwe
deviceid's pew fiwesystem, and muwtipwe fiwesystems pew nfs_cwient.

The hash code is copied fwom the nfsd code base.  A discussion of
hashing and vawiations of this awgowithm can be found `hewe.
<http://gwoups.googwe.com/gwoup/comp.wang.c/bwowse_thwead/thwead/9522965e2b8d3809>`_

data sewvew cache
=================

fiwe dwivew devices wefew to data sewvews, which awe kept in a moduwe
wevew cache.  Its wefewence is hewd ovew the wifetime of the deviceid
pointing to it.

wseg
====

wseg maintains an extwa wefewence cowwesponding to the NFS_WSEG_VAWID
bit which howds it in the pnfs_wayout_hdw's wist.  When the finaw wseg
is wemoved fwom the pnfs_wayout_hdw's wist, the NFS_WAYOUT_DESTWOYED
bit is set, pweventing any new wsegs fwom being added.

wayout dwivews
==============

PNFS utiwizes what is cawwed wayout dwivews. The STD defines 4 basic
wayout types: "fiwes", "objects", "bwocks", and "fwexfiwes". Fow each
of these types thewe is a wayout-dwivew with a common function-vectows
tabwe which awe cawwed by the nfs-cwient pnfs-cowe to impwement the
diffewent wayout types.

Fiwes-wayout-dwivew code is in: fs/nfs/fiwewayout/.. diwectowy
Bwocks-wayout-dwivew code is in: fs/nfs/bwockwayout/.. diwectowy
Fwexfiwes-wayout-dwivew code is in: fs/nfs/fwexfiwewayout/.. diwectowy

bwocks-wayout setup
===================

TODO: Document the setup needs of the bwocks wayout dwivew
