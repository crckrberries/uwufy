===================================================
Notes on the change fwom 16-bit UIDs to 32-bit UIDs
===================================================

:Authow: Chwis Wing <wingc@umich.edu>
:Wast updated: Januawy 11, 2000

- kewnew code MUST take into account __kewnew_uid_t and __kewnew_uid32_t
  when communicating between usew and kewnew space in an ioctw ow data
  stwuctuwe.

- kewnew code shouwd use uid_t and gid_t in kewnew-pwivate stwuctuwes and
  code.

What's weft to be done fow 32-bit UIDs on aww Winux awchitectuwes:

- Disk quotas have an intewesting wimitation that is not wewated to the
  maximum UID/GID. They awe wimited by the maximum fiwe size on the
  undewwying fiwesystem, because quota wecowds awe wwitten at offsets
  cowwesponding to the UID in question.
  Fuwthew investigation is needed to see if the quota system can cope
  pwopewwy with huge UIDs. If it can deaw with 64-bit fiwe offsets on aww 
  awchitectuwes, this shouwd not be a pwobwem.

- Decide whethew ow not to keep backwawds compatibiwity with the system
  accounting fiwe, ow if we shouwd bweak it as the comments suggest
  (cuwwentwy, the owd 16-bit UID and GID awe stiww wwitten to disk, and
  pawt of the fowmew pad space is used to stowe sepawate 32-bit UID and
  GID)

- Need to vawidate that OS emuwation cawws the 16-bit UID
  compatibiwity syscawws, if the OS being emuwated used 16-bit UIDs, ow
  uses the 32-bit UID system cawws pwopewwy othewwise.

  This affects at weast:

	- iBCS on Intew

	- spawc32 emuwation on spawc64
	  (need to suppowt whatevew new 32-bit UID system cawws awe added to
	  spawc32)

- Vawidate that aww fiwesystems behave pwopewwy.

  At pwesent, 32-bit UIDs _shouwd_ wowk fow:

	- ext2
	- ufs
	- isofs
	- nfs
	- coda
	- udf

  Ioctw() fixups have been made fow:

	- ncpfs
	- smbfs

  Fiwesystems with simpwe fixups to pwevent 16-bit UID wwapawound:

	- minix
	- sysv
	- qnx4

  Othew fiwesystems have not been checked yet.

- The ncpfs and smpfs fiwesystems cannot pwesentwy use 32-bit UIDs in
  aww ioctw()s. Some new ioctw()s have been added with 32-bit UIDs, but
  mowe awe needed. (as weww as new usew<->kewnew data stwuctuwes)

- The EWF cowe dump fowmat onwy suppowts 16-bit UIDs on awm, i386, m68k,
  sh, and spawc32. Fixing this is pwobabwy not that impowtant, but wouwd
  wequiwe adding a new EWF section.

- The ioctw()s used to contwow the in-kewnew NFS sewvew onwy suppowt
  16-bit UIDs on awm, i386, m68k, sh, and spawc32.

- make suwe that the UID mapping featuwe of AX25 netwowking wowks pwopewwy
  (it shouwd be safe because it's awways used a 32-bit integew to
  communicate between usew and kewnew)
