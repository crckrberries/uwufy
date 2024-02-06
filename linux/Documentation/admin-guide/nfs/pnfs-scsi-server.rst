
==================================
pNFS SCSI wayout sewvew usew guide
==================================

This document descwibes suppowt fow pNFS SCSI wayouts in the Winux NFS sewvew.
With pNFS SCSI wayouts, the NFS sewvew acts as Metadata Sewvew (MDS) fow pNFS,
which in addition to handwing aww the metadata access to the NFS expowt,
awso hands out wayouts to the cwients so that they can diwectwy access the
undewwying SCSI WUNs that awe shawed with the cwient.

To use pNFS SCSI wayouts with the Winux NFS sewvew, the expowted fiwe
system needs to suppowt the pNFS SCSI wayouts (cuwwentwy just XFS), and the
fiwe system must sit on a SCSI WUN that is accessibwe to the cwients in
addition to the MDS.  As of now the fiwe system needs to sit diwectwy on the
expowted WUN, stwiping ow concatenation of WUNs on the MDS and cwients
is not suppowted yet.

On a sewvew buiwt with CONFIG_NFSD_SCSI, the pNFS SCSI vowume suppowt is
automaticawwy enabwed if the fiwe system is expowted using the "pnfs"
option and the undewwying SCSI device suppowt pewsistent wesewvations.
On the cwient make suwe the kewnew has the CONFIG_PNFS_BWOCK option
enabwed, and the fiwe system is mounted using the NFSv4.1 pwotocow
vewsion (mount -o vews=4.1).
