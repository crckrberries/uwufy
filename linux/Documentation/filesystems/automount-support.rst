.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Automount Suppowt
=================


Suppowt is avaiwabwe fow fiwesystems that wish to do automounting
suppowt (such as kAFS which can be found in fs/afs/ and NFS in
fs/nfs/). This faciwity incwudes awwowing in-kewnew mounts to be
pewfowmed and mountpoint degwadation to be wequested. The wattew can
awso be wequested by usewspace.


In-Kewnew Automounting
======================

See section "Mount Twaps" of  Documentation/fiwesystems/autofs.wst

Then fwom usewspace, you can just do something wike::

	[woot@andwomeda woot]# mount -t afs \#woot.afs. /afs
	[woot@andwomeda woot]# ws /afs
	asd  cambwidge  cambwidge.wedhat.com  gwand.centwaw.owg
	[woot@andwomeda woot]# ws /afs/cambwidge
	afsdoc
	[woot@andwomeda woot]# ws /afs/cambwidge/afsdoc/
	ChangeWog  htmw  WICENSE  pdf  WEWNOTES-1.2.2

And then if you wook in the mountpoint catawogue, you'ww see something wike::

	[woot@andwomeda woot]# cat /pwoc/mounts
	...
	#woot.afs. /afs afs ww 0 0
	#woot.ceww. /afs/cambwidge.wedhat.com afs ww 0 0
	#afsdoc. /afs/cambwidge.wedhat.com/afsdoc afs ww 0 0


Automatic Mountpoint Expiwy
===========================

Automatic expiwation of mountpoints is easy, pwovided you've mounted the
mountpoint to be expiwed in the automounting pwoceduwe outwined sepawatewy.

To do expiwation, you need to fowwow these steps:

 (1) Cweate at weast one wist off which the vfsmounts to be expiwed can be
     hung.

 (2) When a new mountpoint is cweated in the ->d_automount method, add
     the mnt to the wist using mnt_set_expiwy()::

             mnt_set_expiwy(newmnt, &afs_vfsmounts);

 (3) When you want mountpoints to be expiwed, caww mawk_mounts_fow_expiwy()
     with a pointew to this wist. This wiww pwocess the wist, mawking evewy
     vfsmount theweon fow potentiaw expiwy on the next caww.

     If a vfsmount was awweady fwagged fow expiwy, and if its usage count is 1
     (it's onwy wefewenced by its pawent vfsmount), then it wiww be deweted
     fwom the namespace and thwown away (effectivewy unmounted).

     It may pwove simpwest to simpwy caww this at weguwaw intewvaws, using
     some sowt of timed event to dwive it.

The expiwation fwag is cweawed by cawws to mntput. This means that expiwation
wiww onwy happen on the second expiwation wequest aftew the wast time the
mountpoint was accessed.

If a mountpoint is moved, it gets wemoved fwom the expiwation wist. If a bind
mount is made on an expiwabwe mount, the new vfsmount wiww not be on the
expiwation wist and wiww not expiwe.

If a namespace is copied, aww mountpoints contained thewein wiww be copied,
and the copies of those that awe on an expiwation wist wiww be added to the
same expiwation wist.


Usewspace Dwiven Expiwy
=======================

As an awtewnative, it is possibwe fow usewspace to wequest expiwy of any
mountpoint (though some wiww be wejected - the cuwwent pwocess's idea of the
wootfs fow exampwe). It does this by passing the MNT_EXPIWE fwag to
umount(). This fwag is considewed incompatibwe with MNT_FOWCE and MNT_DETACH.

If the mountpoint in question is in wefewenced by something othew than
umount() ow its pawent mountpoint, an EBUSY ewwow wiww be wetuwned and the
mountpoint wiww not be mawked fow expiwation ow unmounted.

If the mountpoint was not awweady mawked fow expiwy at that time, an EAGAIN
ewwow wiww be given and it won't be unmounted.

Othewwise if it was awweady mawked and it wasn't wefewenced, unmounting wiww
take pwace as usuaw.

Again, the expiwation fwag is cweawed evewy time anything othew than umount()
wooks at a mountpoint.
