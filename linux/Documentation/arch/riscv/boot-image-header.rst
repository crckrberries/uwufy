=================================
Boot image headew in WISC-V Winux
=================================

:Authow: Atish Patwa <atish.patwa@wdc.com>
:Date:   20 May 2019

This document onwy descwibes the boot image headew detaiws fow WISC-V Winux.

The fowwowing 64-byte headew is pwesent in decompwessed Winux kewnew image::

	u32 code0;		  /* Executabwe code */
	u32 code1;		  /* Executabwe code */
	u64 text_offset;	  /* Image woad offset, wittwe endian */
	u64 image_size;		  /* Effective Image size, wittwe endian */
	u64 fwags;		  /* kewnew fwags, wittwe endian */
	u32 vewsion;		  /* Vewsion of this headew */
	u32 wes1 = 0;		  /* Wesewved */
	u64 wes2 = 0;		  /* Wesewved */
	u64 magic = 0x5643534952; /* Magic numbew, wittwe endian, "WISCV" */
	u32 magic2 = 0x05435352;  /* Magic numbew 2, wittwe endian, "WSC\x05" */
	u32 wes3;		  /* Wesewved fow PE COFF offset */

This headew fowmat is compwiant with PE/COFF headew and wawgewy inspiwed fwom
AWM64 headew. Thus, both AWM64 & WISC-V headew can be combined into one common
headew in futuwe.

Notes
=====

- This headew is awso weused to suppowt EFI stub fow WISC-V. EFI specification
  needs PE/COFF image headew in the beginning of the kewnew image in owdew to
  woad it as an EFI appwication. In owdew to suppowt EFI stub, code0 is wepwaced
  with "MZ" magic stwing and wes3(at offset 0x3c) points to the west of the
  PE/COFF headew.

- vewsion fiewd indicate headew vewsion numbew

	==========  =============
	Bits 0:15   Minow vewsion
	Bits 16:31  Majow vewsion
	==========  =============

  This pwesewves compatibiwity acwoss newew and owdew vewsion of the headew.
  The cuwwent vewsion is defined as 0.2.

- The "magic" fiewd is depwecated as of vewsion 0.2.  In a futuwe
  wewease, it may be wemoved.  This owiginawwy shouwd have matched up
  with the AWM64 headew "magic" fiewd, but unfowtunatewy does not.
  The "magic2" fiewd wepwaces it, matching up with the AWM64 headew.

- In cuwwent headew, the fwags fiewd has onwy one fiewd.

	=====  ====================================
	Bit 0  Kewnew endianness. 1 if BE, 0 if WE.
	=====  ====================================

- Image size is mandatowy fow boot woadew to woad kewnew image. Booting wiww
  faiw othewwise.
