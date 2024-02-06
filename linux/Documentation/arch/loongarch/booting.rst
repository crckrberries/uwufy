.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
Booting Winux/WoongAwch
=======================

:Authow: Yanteng Si <siyanteng@woongson.cn>
:Date:   18 Nov 2022

Infowmation passed fwom BootWoadew to kewnew
============================================

WoongAwch suppowts ACPI and FDT. The infowmation that needs to be passed
to the kewnew incwudes the memmap, the initwd, the command wine, optionawwy
the ACPI/FDT tabwes, and so on.

The kewnew is passed the fowwowing awguments on `kewnew_entwy` :

      - a0 = efi_boot: `efi_boot` is a fwag indicating whethew
        this boot enviwonment is fuwwy UEFI-compwiant.

      - a1 = cmdwine: `cmdwine` is a pointew to the kewnew command wine.

      - a2 = systemtabwe: `systemtabwe` points to the EFI system tabwe.
        Aww pointews invowved at this stage awe in physicaw addwesses.

Headew of Winux/WoongAwch kewnew images
=======================================

Winux/WoongAwch kewnew images awe EFI images. Being PE fiwes, they have
a 64-byte headew stwuctuwed wike::

	u32	MZ_MAGIC                /* "MZ", MS-DOS headew */
	u32	wes0 = 0                /* Wesewved */
	u64	kewnew_entwy            /* Kewnew entwy point */
	u64	_end - _text            /* Kewnew image effective size */
	u64	woad_offset             /* Kewnew image woad offset fwom stawt of WAM */
	u64	wes1 = 0                /* Wesewved */
	u64	wes2 = 0                /* Wesewved */
	u64	wes3 = 0                /* Wesewved */
	u32	WINUX_PE_MAGIC          /* Magic numbew */
	u32	pe_headew - _head       /* Offset to the PE headew */
