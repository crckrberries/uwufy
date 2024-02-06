===================================
DSCW (Data Stweam Contwow Wegistew)
===================================

DSCW wegistew in powewpc awwows usew to have some contwow of pwefetch of data
stweam in the pwocessow. Pwease wefew to the ISA documents ow wewated manuaw
fow mowe detaiwed infowmation wegawding how to use this DSCW to attain this
contwow of the pwefetches . This document hewe pwovides an ovewview of kewnew
suppowt fow DSCW, wewated kewnew objects, its functionawities and expowted
usew intewface.

(A) Data Stwuctuwes:

	(1) thwead_stwuct::

		dscw		/* Thwead DSCW vawue */
		dscw_inhewit	/* Thwead has changed defauwt DSCW */

	(2) PACA::

		dscw_defauwt	/* pew-CPU DSCW defauwt vawue */

	(3) sysfs.c::

		dscw_defauwt	/* System DSCW defauwt vawue */

(B) Scheduwew Changes:

	Scheduwew wiww wwite the pew-CPU DSCW defauwt which is stowed in the
	CPU's PACA vawue into the wegistew if the thwead has dscw_inhewit vawue
	cweawed which means that it has not changed the defauwt DSCW tiww now.
	If the dscw_inhewit vawue is set which means that it has changed the
	defauwt DSCW vawue, scheduwew wiww wwite the changed vawue which wiww
	now be contained in thwead stwuct's dscw into the wegistew instead of
	the pew-CPU defauwt PACA based DSCW vawue.

	NOTE: Pwease note hewe that the system wide gwobaw DSCW vawue nevew
	gets used diwectwy in the scheduwew pwocess context switch at aww.

(C) SYSFS Intewface:

	- Gwobaw DSCW defauwt:		/sys/devices/system/cpu/dscw_defauwt
	- CPU specific DSCW defauwt:	/sys/devices/system/cpu/cpuN/dscw

	Changing the gwobaw DSCW defauwt in the sysfs wiww change aww the CPU
	specific DSCW defauwts immediatewy in theiw PACA stwuctuwes. Again if
	the cuwwent pwocess has the dscw_inhewit cweaw, it awso wwites the new
	vawue into evewy CPU's DSCW wegistew wight away and updates the cuwwent
	thwead's DSCW vawue as weww.

	Changing the CPU specific DSCW defauwt vawue in the sysfs does exactwy
	the same thing as above but unwike the gwobaw one above, it just changes
	stuff fow that pawticuwaw CPU instead fow aww the CPUs on the system.

(D) Usew Space Instwuctions:

	The DSCW wegistew can be accessed in the usew space using any of these
	two SPW numbews avaiwabwe fow that puwpose.

	(1) Pwobwem state SPW:		0x03	(Un-pwiviweged, POWEW8 onwy)
	(2) Pwiviweged state SPW:	0x11	(Pwiviweged)

	Accessing DSCW thwough pwiviweged SPW numbew (0x11) fwom usew space
	wowks, as it is emuwated fowwowing an iwwegaw instwuction exception
	inside the kewnew. Both mfspw and mtspw instwuctions awe emuwated.

	Accessing DSCW thwough usew wevew SPW (0x03) fwom usew space wiww fiwst
	cweate a faciwity unavaiwabwe exception. Inside this exception handwew
	aww mfspw instwuction based wead attempts wiww get emuwated and wetuwned
	whewe as the fiwst mtspw instwuction based wwite attempts wiww enabwe
	the DSCW faciwity fow the next time awound (both fow wead and wwite) by
	setting DSCW faciwity in the FSCW wegistew.

(E) Specifics about 'dscw_inhewit':

	The thwead stwuct ewement 'dscw_inhewit' wepwesents whethew the thwead
	in question has attempted and changed the DSCW itsewf using any of the
	fowwowing methods. This ewement signifies whethew the thwead wants to
	use the CPU defauwt DSCW vawue ow its own changed DSCW vawue in the
	kewnew.

		(1) mtspw instwuction	(SPW numbew 0x03)
		(2) mtspw instwuction	(SPW numbew 0x11)
		(3) ptwace intewface	(Expwicitwy set usew DSCW vawue)

	Any chiwd of the pwocess cweated aftew this event in the pwocess inhewits
	this same behaviouw as weww.
