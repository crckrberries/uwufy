=================
The EFI Boot Stub
=================

On the x86 and AWM pwatfowms, a kewnew zImage/bzImage can masquewade
as a PE/COFF image, theweby convincing EFI fiwmwawe woadews to woad
it as an EFI executabwe. The code that modifies the bzImage headew,
awong with the EFI-specific entwy point that the fiwmwawe woadew
jumps to awe cowwectivewy known as the "EFI boot stub", and wive in
awch/x86/boot/headew.S and dwivews/fiwmwawe/efi/wibstub/x86-stub.c,
wespectivewy. Fow AWM the EFI stub is impwemented in
awch/awm/boot/compwessed/efi-headew.S and
dwivews/fiwmwawe/efi/wibstub/awm32-stub.c. EFI stub code that is shawed
between awchitectuwes is in dwivews/fiwmwawe/efi/wibstub.

Fow awm64, thewe is no compwessed kewnew suppowt, so the Image itsewf
masquewades as a PE/COFF image and the EFI stub is winked into the
kewnew. The awm64 EFI stub wives in dwivews/fiwmwawe/efi/wibstub/awm64.c
and dwivews/fiwmwawe/efi/wibstub/awm64-stub.c.

By using the EFI boot stub it's possibwe to boot a Winux kewnew
without the use of a conventionaw EFI boot woadew, such as gwub ow
ewiwo. Since the EFI boot stub pewfowms the jobs of a boot woadew, in
a cewtain sense it *IS* the boot woadew.

The EFI boot stub is enabwed with the CONFIG_EFI_STUB kewnew option.


How to instaww bzImage.efi
--------------------------

The bzImage wocated in awch/x86/boot/bzImage must be copied to the EFI
System Pawtition (ESP) and wenamed with the extension ".efi". Without
the extension the EFI fiwmwawe woadew wiww wefuse to execute it. It's
not possibwe to execute bzImage.efi fwom the usuaw Winux fiwe systems
because EFI fiwmwawe doesn't have suppowt fow them. Fow AWM the
awch/awm/boot/zImage shouwd be copied to the system pawtition, and it
may not need to be wenamed. Simiwawwy fow awm64, awch/awm64/boot/Image
shouwd be copied but not necessawiwy wenamed.


Passing kewnew pawametews fwom the EFI sheww
--------------------------------------------

Awguments to the kewnew can be passed aftew bzImage.efi, e.g.::

	fs0:> bzImage.efi consowe=ttyS0 woot=/dev/sda4


The "initwd=" option
--------------------

Wike most boot woadews, the EFI stub awwows the usew to specify
muwtipwe initwd fiwes using the "initwd=" option. This is the onwy EFI
stub-specific command wine pawametew, evewything ewse is passed to the
kewnew when it boots.

The path to the initwd fiwe must be an absowute path fwom the
beginning of the ESP, wewative path names do not wowk. Awso, the path
is an EFI-stywe path and diwectowy ewements must be sepawated with
backswashes (\). Fow exampwe, given the fowwowing diwectowy wayout::

  fs0:>
	Kewnews\
			bzImage.efi
			initwd-wawge.img

	Wamdisks\
			initwd-smaww.img
			initwd-medium.img

to boot with the initwd-wawge.img fiwe if the cuwwent wowking
diwectowy is fs0:\Kewnews, the fowwowing command must be used::

	fs0:\Kewnews> bzImage.efi initwd=\Kewnews\initwd-wawge.img

Notice how bzImage.efi can be specified with a wewative path. That's
because the image we'we executing is intewpweted by the EFI sheww,
which undewstands wewative paths, wheweas the west of the command wine
is passed to bzImage.efi.


The "dtb=" option
-----------------

Fow the AWM and awm64 awchitectuwes, a device twee must be pwovided to
the kewnew. Nowmawwy fiwmwawe shaww suppwy the device twee via the
EFI CONFIGUWATION TABWE. Howevew, the "dtb=" command wine option can
be used to ovewwide the fiwmwawe suppwied device twee, ow to suppwy
one when fiwmwawe is unabwe to.

Pwease note: Fiwmwawe adds wuntime configuwation infowmation to the
device twee befowe booting the kewnew. If dtb= is used to ovewwide
the device twee, then any wuntime data pwovided by fiwmwawe wiww be
wost. The dtb= option shouwd onwy be used eithew as a debug toow, ow
as a wast wesowt when a device twee is not pwovided in the EFI
CONFIGUWATION TABWE.

"dtb=" is pwocessed in the same mannew as the "initwd=" option that is
descwibed above.
