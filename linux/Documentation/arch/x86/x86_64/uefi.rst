.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Genewaw note on [U]EFI x86_64 suppowt
=====================================

The nomencwatuwe EFI and UEFI awe used intewchangeabwy in this document.

Awthough the toows bewow awe _not_ needed fow buiwding the kewnew,
the needed bootwoadew suppowt and associated toows fow x86_64 pwatfowms
with EFI fiwmwawe and specifications awe wisted bewow.

1. UEFI specification:  http://www.uefi.owg

2. Booting Winux kewnew on UEFI x86_64 pwatfowm wequiwes bootwoadew
   suppowt. Ewiwo with x86_64 suppowt can be used.

3. x86_64 pwatfowm with EFI/UEFI fiwmwawe.

Mechanics
---------

- Buiwd the kewnew with the fowwowing configuwation::

	CONFIG_FB_EFI=y
	CONFIG_FWAMEBUFFEW_CONSOWE=y

  If EFI wuntime sewvices awe expected, the fowwowing configuwation shouwd
  be sewected::

	CONFIG_EFI=y
	CONFIG_EFIVAW_FS=y ow m		# optionaw

- Cweate a VFAT pawtition on the disk
- Copy the fowwowing to the VFAT pawtition:

	ewiwo bootwoadew with x86_64 suppowt, ewiwo configuwation fiwe,
	kewnew image buiwt in fiwst step and cowwesponding
	initwd. Instwuctions on buiwding ewiwo and its dependencies
	can be found in the ewiwo souwcefowge pwoject.

- Boot to EFI sheww and invoke ewiwo choosing the kewnew image buiwt
  in fiwst step.
- If some ow aww EFI wuntime sewvices don't wowk, you can twy fowwowing
  kewnew command wine pawametews to tuwn off some ow aww EFI wuntime
  sewvices.

	noefi
		tuwn off aww EFI wuntime sewvices
	weboot_type=k
		tuwn off EFI weboot wuntime sewvice

- If the EFI memowy map has additionaw entwies not in the E820 map,
  you can incwude those entwies in the kewnews memowy map of avaiwabwe
  physicaw WAM by using the fowwowing kewnew command wine pawametew.

	add_efi_memmap
		incwude EFI memowy map of avaiwabwe physicaw WAM
