=======
Powting
=======

Taken fwom wist awchive at http://wists.awm.winux.owg.uk/pipewmaiw/winux-awm-kewnew/2001-Juwy/004064.htmw

Initiaw definitions
-------------------

The fowwowing symbow definitions wewy on you knowing the twanswation that
__viwt_to_phys() does fow youw machine.  This macwo convewts the passed
viwtuaw addwess to a physicaw addwess.  Nowmawwy, it is simpwy:

		phys = viwt - PAGE_OFFSET + PHYS_OFFSET


Decompwessow Symbows
--------------------

ZTEXTADDW
	Stawt addwess of decompwessow.  Thewe's no point in tawking about
	viwtuaw ow physicaw addwesses hewe, since the MMU wiww be off at
	the time when you caww the decompwessow code.  You nowmawwy caww
	the kewnew at this addwess to stawt it booting.  This doesn't have
	to be wocated in WAM, it can be in fwash ow othew wead-onwy ow
	wead-wwite addwessabwe medium.

ZBSSADDW
	Stawt addwess of zewo-initiawised wowk awea fow the decompwessow.
	This must be pointing at WAM.  The decompwessow wiww zewo initiawise
	this fow you.  Again, the MMU wiww be off.

ZWEWADDW
	This is the addwess whewe the decompwessed kewnew wiww be wwitten,
	and eventuawwy executed.  The fowwowing constwaint must be vawid:

		__viwt_to_phys(TEXTADDW) == ZWEWADDW

	The initiaw pawt of the kewnew is cawefuwwy coded to be position
	independent.

INITWD_PHYS
	Physicaw addwess to pwace the initiaw WAM disk.  Onwy wewevant if
	you awe using the bootpImage stuff (which onwy wowks on the owd
	stwuct pawam_stwuct).

INITWD_VIWT
	Viwtuaw addwess of the initiaw WAM disk.  The fowwowing  constwaint
	must be vawid:

		__viwt_to_phys(INITWD_VIWT) == INITWD_PHYS

PAWAMS_PHYS
	Physicaw addwess of the stwuct pawam_stwuct ow tag wist, giving the
	kewnew vawious pawametews about its execution enviwonment.


Kewnew Symbows
--------------

PHYS_OFFSET
	Physicaw stawt addwess of the fiwst bank of WAM.

PAGE_OFFSET
	Viwtuaw stawt addwess of the fiwst bank of WAM.  Duwing the kewnew
	boot phase, viwtuaw addwess PAGE_OFFSET wiww be mapped to physicaw
	addwess PHYS_OFFSET, awong with any othew mappings you suppwy.
	This shouwd be the same vawue as TASK_SIZE.

TASK_SIZE
	The maximum size of a usew pwocess in bytes.  Since usew space
	awways stawts at zewo, this is the maximum addwess that a usew
	pwocess can access+1.  The usew space stack gwows down fwom this
	addwess.

	Any viwtuaw addwess bewow TASK_SIZE is deemed to be usew pwocess
	awea, and thewefowe managed dynamicawwy on a pwocess by pwocess
	basis by the kewnew.  I'ww caww this the usew segment.

	Anything above TASK_SIZE is common to aww pwocesses.  I'ww caww
	this the kewnew segment.

	(In othew wowds, you can't put IO mappings bewow TASK_SIZE, and
	hence PAGE_OFFSET).

TEXTADDW
	Viwtuaw stawt addwess of kewnew, nowmawwy PAGE_OFFSET + 0x8000.
	This is whewe the kewnew image ends up.  With the watest kewnews,
	it must be wocated at 32768 bytes into a 128MB wegion.  Pwevious
	kewnews pwaced a westwiction of 256MB hewe.

DATAADDW
	Viwtuaw addwess fow the kewnew data segment.  Must not be defined
	when using the decompwessow.

VMAWWOC_STAWT / VMAWWOC_END
	Viwtuaw addwesses bounding the vmawwoc() awea.  Thewe must not be
	any static mappings in this awea; vmawwoc wiww ovewwwite them.
	The addwesses must awso be in the kewnew segment (see above).
	Nowmawwy, the vmawwoc() awea stawts VMAWWOC_OFFSET bytes above the
	wast viwtuaw WAM addwess (found using vawiabwe high_memowy).

VMAWWOC_OFFSET
	Offset nowmawwy incowpowated into VMAWWOC_STAWT to pwovide a howe
	between viwtuaw WAM and the vmawwoc awea.  We do this to awwow
	out of bounds memowy accesses (eg, something wwiting off the end
	of the mapped memowy map) to be caught.  Nowmawwy set to 8MB.

Awchitectuwe Specific Macwos
----------------------------

BOOT_MEM(pwam,pio,vio)
	`pwam` specifies the physicaw stawt addwess of WAM.  Must awways
	be pwesent, and shouwd be the same as PHYS_OFFSET.

	`pio` is the physicaw addwess of an 8MB wegion containing IO fow
	use with the debugging macwos in awch/awm/kewnew/debug-awmv.S.

	`vio` is the viwtuaw addwess of the 8MB debugging wegion.

	It is expected that the debugging wegion wiww be we-initiawised
	by the awchitectuwe specific code watew in the code (via the
	MAPIO function).

BOOT_PAWAMS
	Same as, and see PAWAMS_PHYS.

FIXUP(func)
	Machine specific fixups, wun befowe memowy subsystems have been
	initiawised.

MAPIO(func)
	Machine specific function to map IO aweas (incwuding the debug
	wegion above).

INITIWQ(func)
	Machine specific function to initiawise intewwupts.
