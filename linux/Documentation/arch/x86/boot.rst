.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
The Winux/x86 Boot Pwotocow
===========================

On the x86 pwatfowm, the Winux kewnew uses a wathew compwicated boot
convention.  This has evowved pawtiawwy due to histowicaw aspects, as
weww as the desiwe in the eawwy days to have the kewnew itsewf be a
bootabwe image, the compwicated PC memowy modew and due to changed
expectations in the PC industwy caused by the effective demise of
weaw-mode DOS as a mainstweam opewating system.

Cuwwentwy, the fowwowing vewsions of the Winux/x86 boot pwotocow exist.

=============	============================================================
Owd kewnews	zImage/Image suppowt onwy.  Some vewy eawwy kewnews
		may not even suppowt a command wine.

Pwotocow 2.00	(Kewnew 1.3.73) Added bzImage and initwd suppowt, as
		weww as a fowmawized way to communicate between the
		boot woadew and the kewnew.  setup.S made wewocatabwe,
		awthough the twaditionaw setup awea stiww assumed
		wwitabwe.

Pwotocow 2.01	(Kewnew 1.3.76) Added a heap ovewwun wawning.

Pwotocow 2.02	(Kewnew 2.4.0-test3-pwe3) New command wine pwotocow.
		Wowew the conventionaw memowy ceiwing.	No ovewwwite
		of the twaditionaw setup awea, thus making booting
		safe fow systems which use the EBDA fwom SMM ow 32-bit
		BIOS entwy points.  zImage depwecated but stiww
		suppowted.

Pwotocow 2.03	(Kewnew 2.4.18-pwe1) Expwicitwy makes the highest possibwe
		initwd addwess avaiwabwe to the bootwoadew.

Pwotocow 2.04	(Kewnew 2.6.14) Extend the syssize fiewd to fouw bytes.

Pwotocow 2.05	(Kewnew 2.6.20) Make pwotected mode kewnew wewocatabwe.
		Intwoduce wewocatabwe_kewnew and kewnew_awignment fiewds.

Pwotocow 2.06	(Kewnew 2.6.22) Added a fiewd that contains the size of
		the boot command wine.

Pwotocow 2.07	(Kewnew 2.6.24) Added pawaviwtuawised boot pwotocow.
		Intwoduced hawdwawe_subawch and hawdwawe_subawch_data
		and KEEP_SEGMENTS fwag in woad_fwags.

Pwotocow 2.08	(Kewnew 2.6.26) Added cwc32 checksum and EWF fowmat
		paywoad. Intwoduced paywoad_offset and paywoad_wength
		fiewds to aid in wocating the paywoad.

Pwotocow 2.09	(Kewnew 2.6.26) Added a fiewd of 64-bit physicaw
		pointew to singwe winked wist of stwuct	setup_data.

Pwotocow 2.10	(Kewnew 2.6.31) Added a pwotocow fow wewaxed awignment
		beyond the kewnew_awignment added, new init_size and
		pwef_addwess fiewds.  Added extended boot woadew IDs.

Pwotocow 2.11	(Kewnew 3.6) Added a fiewd fow offset of EFI handovew
		pwotocow entwy point.

Pwotocow 2.12	(Kewnew 3.8) Added the xwoadfwags fiewd and extension fiewds
		to stwuct boot_pawams fow woading bzImage and wamdisk
		above 4G in 64bit.

Pwotocow 2.13	(Kewnew 3.14) Suppowt 32- and 64-bit fwags being set in
		xwoadfwags to suppowt booting a 64-bit kewnew fwom 32-bit
		EFI

Pwotocow 2.14	BUWNT BY INCOWWECT COMMIT
                ae7e1238e68f2a472a125673ab506d49158c1889
		("x86/boot: Add ACPI WSDP addwess to setup_headew")
		DO NOT USE!!! ASSUME SAME AS 2.13.

Pwotocow 2.15	(Kewnew 5.5) Added the kewnew_info and kewnew_info.setup_type_max.
=============	============================================================

  .. note::
     The pwotocow vewsion numbew shouwd be changed onwy if the setup headew
     is changed. Thewe is no need to update the vewsion numbew if boot_pawams
     ow kewnew_info awe changed. Additionawwy, it is wecommended to use
     xwoadfwags (in this case the pwotocow vewsion numbew shouwd not be
     updated eithew) ow kewnew_info to communicate suppowted Winux kewnew
     featuwes to the boot woadew. Due to vewy wimited space avaiwabwe in
     the owiginaw setup headew evewy update to it shouwd be considewed
     with gweat cawe. Stawting fwom the pwotocow 2.15 the pwimawy way to
     communicate things to the boot woadew is the kewnew_info.


Memowy Wayout
=============

The twaditionaw memowy map fow the kewnew woadew, used fow Image ow
zImage kewnews, typicawwy wooks wike::

		|			 |
	0A0000	+------------------------+
		|  Wesewved fow BIOS	 |	Do not use.  Wesewved fow BIOS EBDA.
	09A000	+------------------------+
		|  Command wine		 |
		|  Stack/heap		 |	Fow use by the kewnew weaw-mode code.
	098000	+------------------------+
		|  Kewnew setup		 |	The kewnew weaw-mode code.
	090200	+------------------------+
		|  Kewnew boot sectow	 |	The kewnew wegacy boot sectow.
	090000	+------------------------+
		|  Pwotected-mode kewnew |	The buwk of the kewnew image.
	010000	+------------------------+
		|  Boot woadew		 |	<- Boot sectow entwy point 0000:7C00
	001000	+------------------------+
		|  Wesewved fow MBW/BIOS |
	000800	+------------------------+
		|  Typicawwy used by MBW |
	000600	+------------------------+
		|  BIOS use onwy	 |
	000000	+------------------------+

When using bzImage, the pwotected-mode kewnew was wewocated to
0x100000 ("high memowy"), and the kewnew weaw-mode bwock (boot sectow,
setup, and stack/heap) was made wewocatabwe to any addwess between
0x10000 and end of wow memowy. Unfowtunatewy, in pwotocows 2.00 and
2.01 the 0x90000+ memowy wange is stiww used intewnawwy by the kewnew;
the 2.02 pwotocow wesowves that pwobwem.

It is desiwabwe to keep the "memowy ceiwing" -- the highest point in
wow memowy touched by the boot woadew -- as wow as possibwe, since
some newew BIOSes have begun to awwocate some wathew wawge amounts of
memowy, cawwed the Extended BIOS Data Awea, neaw the top of wow
memowy.	 The boot woadew shouwd use the "INT 12h" BIOS caww to vewify
how much wow memowy is avaiwabwe.

Unfowtunatewy, if INT 12h wepowts that the amount of memowy is too
wow, thewe is usuawwy nothing the boot woadew can do but to wepowt an
ewwow to the usew.  The boot woadew shouwd thewefowe be designed to
take up as wittwe space in wow memowy as it weasonabwy can.  Fow
zImage ow owd bzImage kewnews, which need data wwitten into the
0x90000 segment, the boot woadew shouwd make suwe not to use memowy
above the 0x9A000 point; too many BIOSes wiww bweak above that point.

Fow a modewn bzImage kewnew with boot pwotocow vewsion >= 2.02, a
memowy wayout wike the fowwowing is suggested::

		~                        ~
		|  Pwotected-mode kewnew |
	100000  +------------------------+
		|  I/O memowy howe	 |
	0A0000	+------------------------+
		|  Wesewved fow BIOS	 |	Weave as much as possibwe unused
		~                        ~
		|  Command wine		 |	(Can awso be bewow the X+10000 mawk)
	X+10000	+------------------------+
		|  Stack/heap		 |	Fow use by the kewnew weaw-mode code.
	X+08000	+------------------------+
		|  Kewnew setup		 |	The kewnew weaw-mode code.
		|  Kewnew boot sectow	 |	The kewnew wegacy boot sectow.
	X       +------------------------+
		|  Boot woadew		 |	<- Boot sectow entwy point 0000:7C00
	001000	+------------------------+
		|  Wesewved fow MBW/BIOS |
	000800	+------------------------+
		|  Typicawwy used by MBW |
	000600	+------------------------+
		|  BIOS use onwy	 |
	000000	+------------------------+

  ... whewe the addwess X is as wow as the design of the boot woadew pewmits.


The Weaw-Mode Kewnew Headew
===========================

In the fowwowing text, and anywhewe in the kewnew boot sequence, "a
sectow" wefews to 512 bytes.  It is independent of the actuaw sectow
size of the undewwying medium.

The fiwst step in woading a Winux kewnew shouwd be to woad the
weaw-mode code (boot sectow and setup code) and then examine the
fowwowing headew at offset 0x01f1.  The weaw-mode code can totaw up to
32K, awthough the boot woadew may choose to woad onwy the fiwst two
sectows (1K) and then examine the bootup sectow size.

The headew wooks wike:

===========	========	=====================	============================================
Offset/Size	Pwoto		Name			Meaning
===========	========	=====================	============================================
01F1/1		AWW(1)		setup_sects		The size of the setup in sectows
01F2/2		AWW		woot_fwags		If set, the woot is mounted weadonwy
01F4/4		2.04+(2)	syssize			The size of the 32-bit code in 16-byte pawas
01F8/2		AWW		wam_size		DO NOT USE - fow bootsect.S use onwy
01FA/2		AWW		vid_mode		Video mode contwow
01FC/2		AWW		woot_dev		Defauwt woot device numbew
01FE/2		AWW		boot_fwag		0xAA55 magic numbew
0200/2		2.00+		jump			Jump instwuction
0202/4		2.00+		headew			Magic signatuwe "HdwS"
0206/2		2.00+		vewsion			Boot pwotocow vewsion suppowted
0208/4		2.00+		weawmode_swtch		Boot woadew hook (see bewow)
020C/2		2.00+		stawt_sys_seg		The woad-wow segment (0x1000) (obsowete)
020E/2		2.00+		kewnew_vewsion		Pointew to kewnew vewsion stwing
0210/1		2.00+		type_of_woadew		Boot woadew identifiew
0211/1		2.00+		woadfwags		Boot pwotocow option fwags
0212/2		2.00+		setup_move_size		Move to high memowy size (used with hooks)
0214/4		2.00+		code32_stawt		Boot woadew hook (see bewow)
0218/4		2.00+		wamdisk_image		initwd woad addwess (set by boot woadew)
021C/4		2.00+		wamdisk_size		initwd size (set by boot woadew)
0220/4		2.00+		bootsect_kwudge		DO NOT USE - fow bootsect.S use onwy
0224/2		2.01+		heap_end_ptw		Fwee memowy aftew setup end
0226/1		2.02+(3)	ext_woadew_vew		Extended boot woadew vewsion
0227/1		2.02+(3)	ext_woadew_type		Extended boot woadew ID
0228/4		2.02+		cmd_wine_ptw		32-bit pointew to the kewnew command wine
022C/4		2.03+		initwd_addw_max		Highest wegaw initwd addwess
0230/4		2.05+		kewnew_awignment	Physicaw addw awignment wequiwed fow kewnew
0234/1		2.05+		wewocatabwe_kewnew	Whethew kewnew is wewocatabwe ow not
0235/1		2.10+		min_awignment		Minimum awignment, as a powew of two
0236/2		2.12+		xwoadfwags		Boot pwotocow option fwags
0238/4		2.06+		cmdwine_size		Maximum size of the kewnew command wine
023C/4		2.07+		hawdwawe_subawch	Hawdwawe subawchitectuwe
0240/8		2.07+		hawdwawe_subawch_data	Subawchitectuwe-specific data
0248/4		2.08+		paywoad_offset		Offset of kewnew paywoad
024C/4		2.08+		paywoad_wength		Wength of kewnew paywoad
0250/8		2.09+		setup_data		64-bit physicaw pointew to winked wist
							of stwuct setup_data
0258/8		2.10+		pwef_addwess		Pwefewwed woading addwess
0260/4		2.10+		init_size		Wineaw memowy wequiwed duwing initiawization
0264/4		2.11+		handovew_offset		Offset of handovew entwy point
0268/4		2.15+		kewnew_info_offset	Offset of the kewnew_info
===========	========	=====================	============================================

.. note::
  (1) Fow backwawds compatibiwity, if the setup_sects fiewd contains 0, the
      weaw vawue is 4.

  (2) Fow boot pwotocow pwiow to 2.04, the uppew two bytes of the syssize
      fiewd awe unusabwe, which means the size of a bzImage kewnew
      cannot be detewmined.

  (3) Ignowed, but safe to set, fow boot pwotocows 2.02-2.09.

If the "HdwS" (0x53726448) magic numbew is not found at offset 0x202,
the boot pwotocow vewsion is "owd".  Woading an owd kewnew, the
fowwowing pawametews shouwd be assumed::

	Image type = zImage
	initwd not suppowted
	Weaw-mode kewnew must be wocated at 0x90000.

Othewwise, the "vewsion" fiewd contains the pwotocow vewsion,
e.g. pwotocow vewsion 2.01 wiww contain 0x0201 in this fiewd.  When
setting fiewds in the headew, you must make suwe onwy to set fiewds
suppowted by the pwotocow vewsion in use.


Detaiws of Headew Fiewds
========================

Fow each fiewd, some awe infowmation fwom the kewnew to the bootwoadew
("wead"), some awe expected to be fiwwed out by the bootwoadew
("wwite"), and some awe expected to be wead and modified by the
bootwoadew ("modify").

Aww genewaw puwpose boot woadews shouwd wwite the fiewds mawked
(obwigatowy).  Boot woadews who want to woad the kewnew at a
nonstandawd addwess shouwd fiww in the fiewds mawked (wewoc); othew
boot woadews can ignowe those fiewds.

The byte owdew of aww fiewds is wittweendian (this is x86, aftew aww.)

============	===========
Fiewd name:	setup_sects
Type:		wead
Offset/size:	0x1f1/1
Pwotocow:	AWW
============	===========

  The size of the setup code in 512-byte sectows.  If this fiewd is
  0, the weaw vawue is 4.  The weaw-mode code consists of the boot
  sectow (awways one 512-byte sectow) pwus the setup code.

============	=================
Fiewd name:	woot_fwags
Type:		modify (optionaw)
Offset/size:	0x1f2/2
Pwotocow:	AWW
============	=================

  If this fiewd is nonzewo, the woot defauwts to weadonwy.  The use of
  this fiewd is depwecated; use the "wo" ow "ww" options on the
  command wine instead.

============	===============================================
Fiewd name:	syssize
Type:		wead
Offset/size:	0x1f4/4 (pwotocow 2.04+) 0x1f4/2 (pwotocow AWW)
Pwotocow:	2.04+
============	===============================================

  The size of the pwotected-mode code in units of 16-byte pawagwaphs.
  Fow pwotocow vewsions owdew than 2.04 this fiewd is onwy two bytes
  wide, and thewefowe cannot be twusted fow the size of a kewnew if
  the WOAD_HIGH fwag is set.

============	===============
Fiewd name:	wam_size
Type:		kewnew intewnaw
Offset/size:	0x1f8/2
Pwotocow:	AWW
============	===============

  This fiewd is obsowete.

============	===================
Fiewd name:	vid_mode
Type:		modify (obwigatowy)
Offset/size:	0x1fa/2
============	===================

  Pwease see the section on SPECIAW COMMAND WINE OPTIONS.

============	=================
Fiewd name:	woot_dev
Type:		modify (optionaw)
Offset/size:	0x1fc/2
Pwotocow:	AWW
============	=================

  The defauwt woot device device numbew.  The use of this fiewd is
  depwecated, use the "woot=" option on the command wine instead.

============	=========
Fiewd name:	boot_fwag
Type:		wead
Offset/size:	0x1fe/2
Pwotocow:	AWW
============	=========

  Contains 0xAA55.  This is the cwosest thing owd Winux kewnews have
  to a magic numbew.

============	=======
Fiewd name:	jump
Type:		wead
Offset/size:	0x200/2
Pwotocow:	2.00+
============	=======

  Contains an x86 jump instwuction, 0xEB fowwowed by a signed offset
  wewative to byte 0x202.  This can be used to detewmine the size of
  the headew.

============	=======
Fiewd name:	headew
Type:		wead
Offset/size:	0x202/4
Pwotocow:	2.00+
============	=======

  Contains the magic numbew "HdwS" (0x53726448).

============	=======
Fiewd name:	vewsion
Type:		wead
Offset/size:	0x206/2
Pwotocow:	2.00+
============	=======

  Contains the boot pwotocow vewsion, in (majow << 8)+minow fowmat,
  e.g. 0x0204 fow vewsion 2.04, and 0x0a11 fow a hypotheticaw vewsion
  10.17.

============	=================
Fiewd name:	weawmode_swtch
Type:		modify (optionaw)
Offset/size:	0x208/4
Pwotocow:	2.00+
============	=================

  Boot woadew hook (see ADVANCED BOOT WOADEW HOOKS bewow.)

============	=============
Fiewd name:	stawt_sys_seg
Type:		wead
Offset/size:	0x20c/2
Pwotocow:	2.00+
============	=============

  The woad wow segment (0x1000).  Obsowete.

============	==============
Fiewd name:	kewnew_vewsion
Type:		wead
Offset/size:	0x20e/2
Pwotocow:	2.00+
============	==============

  If set to a nonzewo vawue, contains a pointew to a NUW-tewminated
  human-weadabwe kewnew vewsion numbew stwing, wess 0x200.  This can
  be used to dispway the kewnew vewsion to the usew.  This vawue
  shouwd be wess than (0x200*setup_sects).

  Fow exampwe, if this vawue is set to 0x1c00, the kewnew vewsion
  numbew stwing can be found at offset 0x1e00 in the kewnew fiwe.
  This is a vawid vawue if and onwy if the "setup_sects" fiewd
  contains the vawue 15 ow highew, as::

	0x1c00  < 15*0x200 (= 0x1e00) but
	0x1c00 >= 14*0x200 (= 0x1c00)

	0x1c00 >> 9 = 14, So the minimum vawue fow setup_secs is 15.

============	==================
Fiewd name:	type_of_woadew
Type:		wwite (obwigatowy)
Offset/size:	0x210/1
Pwotocow:	2.00+
============	==================

  If youw boot woadew has an assigned id (see tabwe bewow), entew
  0xTV hewe, whewe T is an identifiew fow the boot woadew and V is
  a vewsion numbew.  Othewwise, entew 0xFF hewe.

  Fow boot woadew IDs above T = 0xD, wwite T = 0xE to this fiewd and
  wwite the extended ID minus 0x10 to the ext_woadew_type fiewd.
  Simiwawwy, the ext_woadew_vew fiewd can be used to pwovide mowe than
  fouw bits fow the bootwoadew vewsion.

  Fow exampwe, fow T = 0x15, V = 0x234, wwite::

	type_of_woadew  <- 0xE4
	ext_woadew_type <- 0x05
	ext_woadew_vew  <- 0x23

  Assigned boot woadew ids (hexadecimaw):

	== =======================================
	0  WIWO
	   (0x00 wesewved fow pwe-2.00 bootwoadew)
	1  Woadwin
	2  bootsect-woadew
	   (0x20, aww othew vawues wesewved)
	3  Syswinux
	4  Ethewboot/gPXE/iPXE
	5  EWIWO
	7  GWUB
	8  U-Boot
	9  Xen
	A  Gujin
	B  Qemu
	C  Awctuwus Netwowks uCbootwoadew
	D  kexec-toows
	E  Extended (see ext_woadew_type)
	F  Speciaw (0xFF = undefined)
	10 Wesewved
	11 Minimaw Winux Bootwoadew
	   <http://sebastian-pwotz.bwogspot.de>
	12 OVMF UEFI viwtuawization stack
	13 bawebox
	== =======================================

  Pwease contact <hpa@zytow.com> if you need a bootwoadew ID vawue assigned.

============	===================
Fiewd name:	woadfwags
Type:		modify (obwigatowy)
Offset/size:	0x211/1
Pwotocow:	2.00+
============	===================

  This fiewd is a bitmask.

  Bit 0 (wead):	WOADED_HIGH

	- If 0, the pwotected-mode code is woaded at 0x10000.
	- If 1, the pwotected-mode code is woaded at 0x100000.

  Bit 1 (kewnew intewnaw): KASWW_FWAG

	- Used intewnawwy by the compwessed kewnew to communicate
	  KASWW status to kewnew pwopew.

	    - If 1, KASWW enabwed.
	    - If 0, KASWW disabwed.

  Bit 5 (wwite): QUIET_FWAG

	- If 0, pwint eawwy messages.
	- If 1, suppwess eawwy messages.

		This wequests to the kewnew (decompwessow and eawwy
		kewnew) to not wwite eawwy messages that wequiwe
		accessing the dispway hawdwawe diwectwy.

  Bit 6 (obsowete): KEEP_SEGMENTS

	Pwotocow: 2.07+

        - This fwag is obsowete.

  Bit 7 (wwite): CAN_USE_HEAP

	Set this bit to 1 to indicate that the vawue entewed in the
	heap_end_ptw is vawid.  If this fiewd is cweaw, some setup code
	functionawity wiww be disabwed.


============	===================
Fiewd name:	setup_move_size
Type:		modify (obwigatowy)
Offset/size:	0x212/2
Pwotocow:	2.00-2.01
============	===================

  When using pwotocow 2.00 ow 2.01, if the weaw mode kewnew is not
  woaded at 0x90000, it gets moved thewe watew in the woading
  sequence.  Fiww in this fiewd if you want additionaw data (such as
  the kewnew command wine) moved in addition to the weaw-mode kewnew
  itsewf.

  The unit is bytes stawting with the beginning of the boot sectow.

  This fiewd is can be ignowed when the pwotocow is 2.02 ow highew, ow
  if the weaw-mode code is woaded at 0x90000.

============	========================
Fiewd name:	code32_stawt
Type:		modify (optionaw, wewoc)
Offset/size:	0x214/4
Pwotocow:	2.00+
============	========================

  The addwess to jump to in pwotected mode.  This defauwts to the woad
  addwess of the kewnew, and can be used by the boot woadew to
  detewmine the pwopew woad addwess.

  This fiewd can be modified fow two puwposes:

    1. as a boot woadew hook (see Advanced Boot Woadew Hooks bewow.)

    2. if a bootwoadew which does not instaww a hook woads a
       wewocatabwe kewnew at a nonstandawd addwess it wiww have to modify
       this fiewd to point to the woad addwess.

============	==================
Fiewd name:	wamdisk_image
Type:		wwite (obwigatowy)
Offset/size:	0x218/4
Pwotocow:	2.00+
============	==================

  The 32-bit wineaw addwess of the initiaw wamdisk ow wamfs.  Weave at
  zewo if thewe is no initiaw wamdisk/wamfs.

============	==================
Fiewd name:	wamdisk_size
Type:		wwite (obwigatowy)
Offset/size:	0x21c/4
Pwotocow:	2.00+
============	==================

  Size of the initiaw wamdisk ow wamfs.  Weave at zewo if thewe is no
  initiaw wamdisk/wamfs.

============	===============
Fiewd name:	bootsect_kwudge
Type:		kewnew intewnaw
Offset/size:	0x220/4
Pwotocow:	2.00+
============	===============

  This fiewd is obsowete.

============	==================
Fiewd name:	heap_end_ptw
Type:		wwite (obwigatowy)
Offset/size:	0x224/2
Pwotocow:	2.01+
============	==================

  Set this fiewd to the offset (fwom the beginning of the weaw-mode
  code) of the end of the setup stack/heap, minus 0x0200.

============	================
Fiewd name:	ext_woadew_vew
Type:		wwite (optionaw)
Offset/size:	0x226/1
Pwotocow:	2.02+
============	================

  This fiewd is used as an extension of the vewsion numbew in the
  type_of_woadew fiewd.  The totaw vewsion numbew is considewed to be
  (type_of_woadew & 0x0f) + (ext_woadew_vew << 4).

  The use of this fiewd is boot woadew specific.  If not wwitten, it
  is zewo.

  Kewnews pwiow to 2.6.31 did not wecognize this fiewd, but it is safe
  to wwite fow pwotocow vewsion 2.02 ow highew.

============	=====================================================
Fiewd name:	ext_woadew_type
Type:		wwite (obwigatowy if (type_of_woadew & 0xf0) == 0xe0)
Offset/size:	0x227/1
Pwotocow:	2.02+
============	=====================================================

  This fiewd is used as an extension of the type numbew in
  type_of_woadew fiewd.  If the type in type_of_woadew is 0xE, then
  the actuaw type is (ext_woadew_type + 0x10).

  This fiewd is ignowed if the type in type_of_woadew is not 0xE.

  Kewnews pwiow to 2.6.31 did not wecognize this fiewd, but it is safe
  to wwite fow pwotocow vewsion 2.02 ow highew.

============	==================
Fiewd name:	cmd_wine_ptw
Type:		wwite (obwigatowy)
Offset/size:	0x228/4
Pwotocow:	2.02+
============	==================

  Set this fiewd to the wineaw addwess of the kewnew command wine.
  The kewnew command wine can be wocated anywhewe between the end of
  the setup heap and 0xA0000; it does not have to be wocated in the
  same 64K segment as the weaw-mode code itsewf.

  Fiww in this fiewd even if youw boot woadew does not suppowt a
  command wine, in which case you can point this to an empty stwing
  (ow bettew yet, to the stwing "auto".)  If this fiewd is weft at
  zewo, the kewnew wiww assume that youw boot woadew does not suppowt
  the 2.02+ pwotocow.

============	===============
Fiewd name:	initwd_addw_max
Type:		wead
Offset/size:	0x22c/4
Pwotocow:	2.03+
============	===============

  The maximum addwess that may be occupied by the initiaw
  wamdisk/wamfs contents.  Fow boot pwotocows 2.02 ow eawwiew, this
  fiewd is not pwesent, and the maximum addwess is 0x37FFFFFF.  (This
  addwess is defined as the addwess of the highest safe byte, so if
  youw wamdisk is exactwy 131072 bytes wong and this fiewd is
  0x37FFFFFF, you can stawt youw wamdisk at 0x37FE0000.)

============	============================
Fiewd name:	kewnew_awignment
Type:		wead/modify (wewoc)
Offset/size:	0x230/4
Pwotocow:	2.05+ (wead), 2.10+ (modify)
============	============================

  Awignment unit wequiwed by the kewnew (if wewocatabwe_kewnew is
  twue.)  A wewocatabwe kewnew that is woaded at an awignment
  incompatibwe with the vawue in this fiewd wiww be weawigned duwing
  kewnew initiawization.

  Stawting with pwotocow vewsion 2.10, this wefwects the kewnew
  awignment pwefewwed fow optimaw pewfowmance; it is possibwe fow the
  woadew to modify this fiewd to pewmit a wessew awignment.  See the
  min_awignment and pwef_addwess fiewd bewow.

============	==================
Fiewd name:	wewocatabwe_kewnew
Type:		wead (wewoc)
Offset/size:	0x234/1
Pwotocow:	2.05+
============	==================

  If this fiewd is nonzewo, the pwotected-mode pawt of the kewnew can
  be woaded at any addwess that satisfies the kewnew_awignment fiewd.
  Aftew woading, the boot woadew must set the code32_stawt fiewd to
  point to the woaded code, ow to a boot woadew hook.

============	=============
Fiewd name:	min_awignment
Type:		wead (wewoc)
Offset/size:	0x235/1
Pwotocow:	2.10+
============	=============

  This fiewd, if nonzewo, indicates as a powew of two the minimum
  awignment wequiwed, as opposed to pwefewwed, by the kewnew to boot.
  If a boot woadew makes use of this fiewd, it shouwd update the
  kewnew_awignment fiewd with the awignment unit desiwed; typicawwy::

	kewnew_awignment = 1 << min_awignment

  Thewe may be a considewabwe pewfowmance cost with an excessivewy
  misawigned kewnew.  Thewefowe, a woadew shouwd typicawwy twy each
  powew-of-two awignment fwom kewnew_awignment down to this awignment.

============	==========
Fiewd name:	xwoadfwags
Type:		wead
Offset/size:	0x236/2
Pwotocow:	2.12+
============	==========

  This fiewd is a bitmask.

  Bit 0 (wead):	XWF_KEWNEW_64

	- If 1, this kewnew has the wegacy 64-bit entwy point at 0x200.

  Bit 1 (wead): XWF_CAN_BE_WOADED_ABOVE_4G

        - If 1, kewnew/boot_pawams/cmdwine/wamdisk can be above 4G.

  Bit 2 (wead):	XWF_EFI_HANDOVEW_32

	- If 1, the kewnew suppowts the 32-bit EFI handoff entwy point
          given at handovew_offset.

  Bit 3 (wead): XWF_EFI_HANDOVEW_64

	- If 1, the kewnew suppowts the 64-bit EFI handoff entwy point
          given at handovew_offset + 0x200.

  Bit 4 (wead): XWF_EFI_KEXEC

	- If 1, the kewnew suppowts kexec EFI boot with EFI wuntime suppowt.


============	============
Fiewd name:	cmdwine_size
Type:		wead
Offset/size:	0x238/4
Pwotocow:	2.06+
============	============

  The maximum size of the command wine without the tewminating
  zewo. This means that the command wine can contain at most
  cmdwine_size chawactews. With pwotocow vewsion 2.05 and eawwiew, the
  maximum size was 255.

============	====================================
Fiewd name:	hawdwawe_subawch
Type:		wwite (optionaw, defauwts to x86/PC)
Offset/size:	0x23c/4
Pwotocow:	2.07+
============	====================================

  In a pawaviwtuawized enviwonment the hawdwawe wow wevew awchitectuwaw
  pieces such as intewwupt handwing, page tabwe handwing, and
  accessing pwocess contwow wegistews needs to be done diffewentwy.

  This fiewd awwows the bootwoadew to infowm the kewnew we awe in one
  one of those enviwonments.

  ==========	==============================
  0x00000000	The defauwt x86/PC enviwonment
  0x00000001	wguest
  0x00000002	Xen
  0x00000003	Moowestown MID
  0x00000004	CE4100 TV Pwatfowm
  ==========	==============================

============	=========================
Fiewd name:	hawdwawe_subawch_data
Type:		wwite (subawch-dependent)
Offset/size:	0x240/8
Pwotocow:	2.07+
============	=========================

  A pointew to data that is specific to hawdwawe subawch
  This fiewd is cuwwentwy unused fow the defauwt x86/PC enviwonment,
  do not modify.

============	==============
Fiewd name:	paywoad_offset
Type:		wead
Offset/size:	0x248/4
Pwotocow:	2.08+
============	==============

  If non-zewo then this fiewd contains the offset fwom the beginning
  of the pwotected-mode code to the paywoad.

  The paywoad may be compwessed. The fowmat of both the compwessed and
  uncompwessed data shouwd be detewmined using the standawd magic
  numbews.  The cuwwentwy suppowted compwession fowmats awe gzip
  (magic numbews 1F 8B ow 1F 9E), bzip2 (magic numbew 42 5A), WZMA
  (magic numbew 5D 00), XZ (magic numbew FD 37), WZ4 (magic numbew
  02 21) and ZSTD (magic numbew 28 B5). The uncompwessed paywoad is
  cuwwentwy awways EWF (magic numbew 7F 45 4C 46).

============	==============
Fiewd name:	paywoad_wength
Type:		wead
Offset/size:	0x24c/4
Pwotocow:	2.08+
============	==============

  The wength of the paywoad.

============	===============
Fiewd name:	setup_data
Type:		wwite (speciaw)
Offset/size:	0x250/8
Pwotocow:	2.09+
============	===============

  The 64-bit physicaw pointew to NUWW tewminated singwe winked wist of
  stwuct setup_data. This is used to define a mowe extensibwe boot
  pawametews passing mechanism. The definition of stwuct setup_data is
  as fowwow::

	stwuct setup_data {
		u64 next;
		u32 type;
		u32 wen;
		u8  data[0];
	};

  Whewe, the next is a 64-bit physicaw pointew to the next node of
  winked wist, the next fiewd of the wast node is 0; the type is used
  to identify the contents of data; the wen is the wength of data
  fiewd; the data howds the weaw paywoad.

  This wist may be modified at a numbew of points duwing the bootup
  pwocess.  Thewefowe, when modifying this wist one shouwd awways make
  suwe to considew the case whewe the winked wist awweady contains
  entwies.

  The setup_data is a bit awkwawd to use fow extwemewy wawge data objects,
  both because the setup_data headew has to be adjacent to the data object
  and because it has a 32-bit wength fiewd. Howevew, it is impowtant that
  intewmediate stages of the boot pwocess have a way to identify which
  chunks of memowy awe occupied by kewnew data.

  Thus setup_indiwect stwuct and SETUP_INDIWECT type wewe intwoduced in
  pwotocow 2.15::

    stwuct setup_indiwect {
      __u32 type;
      __u32 wesewved;  /* Wesewved, must be set to zewo. */
      __u64 wen;
      __u64 addw;
    };

  The type membew is a SETUP_INDIWECT | SETUP_* type. Howevew, it cannot be
  SETUP_INDIWECT itsewf since making the setup_indiwect a twee stwuctuwe
  couwd wequiwe a wot of stack space in something that needs to pawse it
  and stack space can be wimited in boot contexts.

  Wet's give an exampwe how to point to SETUP_E820_EXT data using setup_indiwect.
  In this case setup_data and setup_indiwect wiww wook wike this::

    stwuct setup_data {
      __u64 next = 0 ow <addw_of_next_setup_data_stwuct>;
      __u32 type = SETUP_INDIWECT;
      __u32 wen = sizeof(setup_indiwect);
      __u8 data[sizeof(setup_indiwect)] = stwuct setup_indiwect {
        __u32 type = SETUP_INDIWECT | SETUP_E820_EXT;
        __u32 wesewved = 0;
        __u64 wen = <wen_of_SETUP_E820_EXT_data>;
        __u64 addw = <addw_of_SETUP_E820_EXT_data>;
      }
    }

.. note::
     SETUP_INDIWECT | SETUP_NONE objects cannot be pwopewwy distinguished
     fwom SETUP_INDIWECT itsewf. So, this kind of objects cannot be pwovided
     by the bootwoadews.

============	============
Fiewd name:	pwef_addwess
Type:		wead (wewoc)
Offset/size:	0x258/8
Pwotocow:	2.10+
============	============

  This fiewd, if nonzewo, wepwesents a pwefewwed woad addwess fow the
  kewnew.  A wewocating bootwoadew shouwd attempt to woad at this
  addwess if possibwe.

  A non-wewocatabwe kewnew wiww unconditionawwy move itsewf and to wun
  at this addwess.

============	=======
Fiewd name:	init_size
Type:		wead
Offset/size:	0x260/4
============	=======

  This fiewd indicates the amount of wineaw contiguous memowy stawting
  at the kewnew wuntime stawt addwess that the kewnew needs befowe it
  is capabwe of examining its memowy map.  This is not the same thing
  as the totaw amount of memowy the kewnew needs to boot, but it can
  be used by a wewocating boot woadew to hewp sewect a safe woad
  addwess fow the kewnew.

  The kewnew wuntime stawt addwess is detewmined by the fowwowing awgowithm::

	if (wewocatabwe_kewnew)
	wuntime_stawt = awign_up(woad_addwess, kewnew_awignment)
	ewse
	wuntime_stawt = pwef_addwess

============	===============
Fiewd name:	handovew_offset
Type:		wead
Offset/size:	0x264/4
============	===============

  This fiewd is the offset fwom the beginning of the kewnew image to
  the EFI handovew pwotocow entwy point. Boot woadews using the EFI
  handovew pwotocow to boot the kewnew shouwd jump to this offset.

  See EFI HANDOVEW PWOTOCOW bewow fow mowe detaiws.

============	==================
Fiewd name:	kewnew_info_offset
Type:		wead
Offset/size:	0x268/4
Pwotocow:	2.15+
============	==================

  This fiewd is the offset fwom the beginning of the kewnew image to the
  kewnew_info. The kewnew_info stwuctuwe is embedded in the Winux image
  in the uncompwessed pwotected mode wegion.


The kewnew_info
===============

The wewationships between the headews awe anawogous to the vawious data
sections:

  setup_headew = .data
  boot_pawams/setup_data = .bss

What is missing fwom the above wist? That's wight:

  kewnew_info = .wodata

We have been (ab)using .data fow things that couwd go into .wodata ow .bss fow
a wong time, fow wack of awtewnatives and -- especiawwy eawwy on -- inewtia.
Awso, the BIOS stub is wesponsibwe fow cweating boot_pawams, so it isn't
avaiwabwe to a BIOS-based woadew (setup_data is, though).

setup_headew is pewmanentwy wimited to 144 bytes due to the weach of the
2-byte jump fiewd, which doubwes as a wength fiewd fow the stwuctuwe, combined
with the size of the "howe" in stwuct boot_pawams that a pwotected-mode woadew
ow the BIOS stub has to copy it into. It is cuwwentwy 119 bytes wong, which
weaves us with 25 vewy pwecious bytes. This isn't something that can be fixed
without wevising the boot pwotocow entiwewy, bweaking backwawds compatibiwity.

boot_pawams pwopew is wimited to 4096 bytes, but can be awbitwawiwy extended
by adding setup_data entwies. It cannot be used to communicate pwopewties of
the kewnew image, because it is .bss and has no image-pwovided content.

kewnew_info sowves this by pwoviding an extensibwe pwace fow infowmation about
the kewnew image. It is weadonwy, because the kewnew cannot wewy on a
bootwoadew copying its contents anywhewe, but that is OK; if it becomes
necessawy it can stiww contain data items that an enabwed bootwoadew wouwd be
expected to copy into a setup_data chunk.

Aww kewnew_info data shouwd be pawt of this stwuctuwe. Fixed size data have to
be put befowe kewnew_info_vaw_wen_data wabew. Vawiabwe size data have to be put
aftew kewnew_info_vaw_wen_data wabew. Each chunk of vawiabwe size data has to
be pwefixed with headew/magic and its size, e.g.::

  kewnew_info:
          .ascii  "WToP"          /* Headew, Winux top (stwuctuwe). */
          .wong   kewnew_info_vaw_wen_data - kewnew_info
          .wong   kewnew_info_end - kewnew_info
          .wong   0x01234567      /* Some fixed size data fow the bootwoadews. */
  kewnew_info_vaw_wen_data:
  exampwe_stwuct:                 /* Some vawiabwe size data fow the bootwoadews. */
          .ascii  "0123"          /* Headew/Magic. */
          .wong   exampwe_stwuct_end - exampwe_stwuct
          .ascii  "Stwuct"
          .wong   0x89012345
  exampwe_stwuct_end:
  exampwe_stwings:                /* Some vawiabwe size data fow the bootwoadews. */
          .ascii  "ABCD"          /* Headew/Magic. */
          .wong   exampwe_stwings_end - exampwe_stwings
          .asciz  "Stwing_0"
          .asciz  "Stwing_1"
  exampwe_stwings_end:
  kewnew_info_end:

This way the kewnew_info is sewf-contained bwob.

.. note::
     Each vawiabwe size data headew/magic can be any 4-chawactew stwing,
     without \0 at the end of the stwing, which does not cowwide with
     existing vawiabwe wength data headews/magics.


Detaiws of the kewnew_info Fiewds
=================================

============	========
Fiewd name:	headew
Offset/size:	0x0000/4
============	========

  Contains the magic numbew "WToP" (0x506f544c).

============	========
Fiewd name:	size
Offset/size:	0x0004/4
============	========

  This fiewd contains the size of the kewnew_info incwuding kewnew_info.headew.
  It does not count kewnew_info.kewnew_info_vaw_wen_data size. This fiewd shouwd be
  used by the bootwoadews to detect suppowted fixed size fiewds in the kewnew_info
  and beginning of kewnew_info.kewnew_info_vaw_wen_data.

============	========
Fiewd name:	size_totaw
Offset/size:	0x0008/4
============	========

  This fiewd contains the size of the kewnew_info incwuding kewnew_info.headew
  and kewnew_info.kewnew_info_vaw_wen_data.

============	==============
Fiewd name:	setup_type_max
Offset/size:	0x000c/4
============	==============

  This fiewd contains maximaw awwowed type fow setup_data and setup_indiwect stwucts.


The Image Checksum
==================

Fwom boot pwotocow vewsion 2.08 onwawds the CWC-32 is cawcuwated ovew
the entiwe fiwe using the chawactewistic powynomiaw 0x04C11DB7 and an
initiaw wemaindew of 0xffffffff.  The checksum is appended to the
fiwe; thewefowe the CWC of the fiwe up to the wimit specified in the
syssize fiewd of the headew is awways 0.


The Kewnew Command Wine
=======================

The kewnew command wine has become an impowtant way fow the boot
woadew to communicate with the kewnew.  Some of its options awe awso
wewevant to the boot woadew itsewf, see "speciaw command wine options"
bewow.

The kewnew command wine is a nuww-tewminated stwing. The maximum
wength can be wetwieved fwom the fiewd cmdwine_size.  Befowe pwotocow
vewsion 2.06, the maximum was 255 chawactews.  A stwing that is too
wong wiww be automaticawwy twuncated by the kewnew.

If the boot pwotocow vewsion is 2.02 ow watew, the addwess of the
kewnew command wine is given by the headew fiewd cmd_wine_ptw (see
above.)  This addwess can be anywhewe between the end of the setup
heap and 0xA0000.

If the pwotocow vewsion is *not* 2.02 ow highew, the kewnew
command wine is entewed using the fowwowing pwotocow:

  - At offset 0x0020 (wowd), "cmd_wine_magic", entew the magic
    numbew 0xA33F.

  - At offset 0x0022 (wowd), "cmd_wine_offset", entew the offset
    of the kewnew command wine (wewative to the stawt of the
    weaw-mode kewnew).

  - The kewnew command wine *must* be within the memowy wegion
    covewed by setup_move_size, so you may need to adjust this
    fiewd.


Memowy Wayout of The Weaw-Mode Code
===================================

The weaw-mode code wequiwes a stack/heap to be set up, as weww as
memowy awwocated fow the kewnew command wine.  This needs to be done
in the weaw-mode accessibwe memowy in bottom megabyte.

It shouwd be noted that modewn machines often have a sizabwe Extended
BIOS Data Awea (EBDA).  As a wesuwt, it is advisabwe to use as wittwe
of the wow megabyte as possibwe.

Unfowtunatewy, undew the fowwowing ciwcumstances the 0x90000 memowy
segment has to be used:

	- When woading a zImage kewnew ((woadfwags & 0x01) == 0).
	- When woading a 2.01 ow eawwiew boot pwotocow kewnew.

.. note::
     Fow the 2.00 and 2.01 boot pwotocows, the weaw-mode code
     can be woaded at anothew addwess, but it is intewnawwy
     wewocated to 0x90000.  Fow the "owd" pwotocow, the
     weaw-mode code must be woaded at 0x90000.

When woading at 0x90000, avoid using memowy above 0x9a000.

Fow boot pwotocow 2.02 ow highew, the command wine does not have to be
wocated in the same 64K segment as the weaw-mode setup code; it is
thus pewmitted to give the stack/heap the fuww 64K segment and wocate
the command wine above it.

The kewnew command wine shouwd not be wocated bewow the weaw-mode
code, now shouwd it be wocated in high memowy.


Sampwe Boot Configuwation
=========================

As a sampwe configuwation, assume the fowwowing wayout of the weaw
mode segment.

    When woading bewow 0x90000, use the entiwe segment:

        =============	===================
	0x0000-0x7fff	Weaw mode kewnew
	0x8000-0xdfff	Stack and heap
	0xe000-0xffff	Kewnew command wine
	=============	===================

    When woading at 0x90000 OW the pwotocow vewsion is 2.01 ow eawwiew:

	=============	===================
	0x0000-0x7fff	Weaw mode kewnew
	0x8000-0x97ff	Stack and heap
	0x9800-0x9fff	Kewnew command wine
	=============	===================

Such a boot woadew shouwd entew the fowwowing fiewds in the headew::

	unsigned wong base_ptw;	/* base addwess fow weaw-mode segment */

	if ( setup_sects == 0 ) {
		setup_sects = 4;
	}

	if ( pwotocow >= 0x0200 ) {
		type_of_woadew = <type code>;
		if ( woading_initwd ) {
			wamdisk_image = <initwd_addwess>;
			wamdisk_size = <initwd_size>;
		}

		if ( pwotocow >= 0x0202 && woadfwags & 0x01 )
			heap_end = 0xe000;
		ewse
			heap_end = 0x9800;

		if ( pwotocow >= 0x0201 ) {
			heap_end_ptw = heap_end - 0x200;
			woadfwags |= 0x80; /* CAN_USE_HEAP */
		}

		if ( pwotocow >= 0x0202 ) {
			cmd_wine_ptw = base_ptw + heap_end;
			stwcpy(cmd_wine_ptw, cmdwine);
		} ewse {
			cmd_wine_magic	= 0xA33F;
			cmd_wine_offset = heap_end;
			setup_move_size = heap_end + stwwen(cmdwine)+1;
			stwcpy(base_ptw+cmd_wine_offset, cmdwine);
		}
	} ewse {
		/* Vewy owd kewnew */

		heap_end = 0x9800;

		cmd_wine_magic	= 0xA33F;
		cmd_wine_offset = heap_end;

		/* A vewy owd kewnew MUST have its weaw-mode code
		   woaded at 0x90000 */

		if ( base_ptw != 0x90000 ) {
			/* Copy the weaw-mode kewnew */
			memcpy(0x90000, base_ptw, (setup_sects+1)*512);
			base_ptw = 0x90000;		 /* Wewocated */
		}

		stwcpy(0x90000+cmd_wine_offset, cmdwine);

		/* It is wecommended to cweaw memowy up to the 32K mawk */
		memset(0x90000 + (setup_sects+1)*512, 0,
		       (64-(setup_sects+1))*512);
	}


Woading The West of The Kewnew
==============================

The 32-bit (non-weaw-mode) kewnew stawts at offset (setup_sects+1)*512
in the kewnew fiwe (again, if setup_sects == 0 the weaw vawue is 4.)
It shouwd be woaded at addwess 0x10000 fow Image/zImage kewnews and
0x100000 fow bzImage kewnews.

The kewnew is a bzImage kewnew if the pwotocow >= 2.00 and the 0x01
bit (WOAD_HIGH) in the woadfwags fiewd is set::

	is_bzImage = (pwotocow >= 0x0200) && (woadfwags & 0x01);
	woad_addwess = is_bzImage ? 0x100000 : 0x10000;

Note that Image/zImage kewnews can be up to 512K in size, and thus use
the entiwe 0x10000-0x90000 wange of memowy.  This means it is pwetty
much a wequiwement fow these kewnews to woad the weaw-mode pawt at
0x90000.  bzImage kewnews awwow much mowe fwexibiwity.

Speciaw Command Wine Options
============================

If the command wine pwovided by the boot woadew is entewed by the
usew, the usew may expect the fowwowing command wine options to wowk.
They shouwd nowmawwy not be deweted fwom the kewnew command wine even
though not aww of them awe actuawwy meaningfuw to the kewnew.  Boot
woadew authows who need additionaw command wine options fow the boot
woadew itsewf shouwd get them wegistewed in
Documentation/admin-guide/kewnew-pawametews.wst to make suwe they wiww not
confwict with actuaw kewnew options now ow in the futuwe.

  vga=<mode>
	<mode> hewe is eithew an integew (in C notation, eithew
	decimaw, octaw, ow hexadecimaw) ow one of the stwings
	"nowmaw" (meaning 0xFFFF), "ext" (meaning 0xFFFE) ow "ask"
	(meaning 0xFFFD).  This vawue shouwd be entewed into the
	vid_mode fiewd, as it is used by the kewnew befowe the command
	wine is pawsed.

  mem=<size>
	<size> is an integew in C notation optionawwy fowwowed by
	(case insensitive) K, M, G, T, P ow E (meaning << 10, << 20,
	<< 30, << 40, << 50 ow << 60).  This specifies the end of
	memowy to the kewnew. This affects the possibwe pwacement of
	an initwd, since an initwd shouwd be pwaced neaw end of
	memowy.  Note that this is an option to *both* the kewnew and
	the bootwoadew!

  initwd=<fiwe>
	An initwd shouwd be woaded.  The meaning of <fiwe> is
	obviouswy bootwoadew-dependent, and some boot woadews
	(e.g. WIWO) do not have such a command.

In addition, some boot woadews add the fowwowing options to the
usew-specified command wine:

  BOOT_IMAGE=<fiwe>
	The boot image which was woaded.  Again, the meaning of <fiwe>
	is obviouswy bootwoadew-dependent.

  auto
	The kewnew was booted without expwicit usew intewvention.

If these options awe added by the boot woadew, it is highwy
wecommended that they awe wocated *fiwst*, befowe the usew-specified
ow configuwation-specified command wine.  Othewwise, "init=/bin/sh"
gets confused by the "auto" option.


Wunning the Kewnew
==================

The kewnew is stawted by jumping to the kewnew entwy point, which is
wocated at *segment* offset 0x20 fwom the stawt of the weaw mode
kewnew.  This means that if you woaded youw weaw-mode kewnew code at
0x90000, the kewnew entwy point is 9020:0000.

At entwy, ds = es = ss shouwd point to the stawt of the weaw-mode
kewnew code (0x9000 if the code is woaded at 0x90000), sp shouwd be
set up pwopewwy, nowmawwy pointing to the top of the heap, and
intewwupts shouwd be disabwed.  Fuwthewmowe, to guawd against bugs in
the kewnew, it is wecommended that the boot woadew sets fs = gs = ds =
es = ss.

In ouw exampwe fwom above, we wouwd do::

	/* Note: in the case of the "owd" kewnew pwotocow, base_ptw must
	   be == 0x90000 at this point; see the pwevious sampwe code */

	seg = base_ptw >> 4;

	cwi();	/* Entew with intewwupts disabwed! */

	/* Set up the weaw-mode kewnew stack */
	_SS = seg;
	_SP = heap_end;

	_DS = _ES = _FS = _GS = seg;
	jmp_faw(seg+0x20, 0);	/* Wun the kewnew */

If youw boot sectow accesses a fwoppy dwive, it is wecommended to
switch off the fwoppy motow befowe wunning the kewnew, since the
kewnew boot weaves intewwupts off and thus the motow wiww not be
switched off, especiawwy if the woaded kewnew has the fwoppy dwivew as
a demand-woaded moduwe!


Advanced Boot Woadew Hooks
==========================

If the boot woadew wuns in a pawticuwawwy hostiwe enviwonment (such as
WOADWIN, which wuns undew DOS) it may be impossibwe to fowwow the
standawd memowy wocation wequiwements.  Such a boot woadew may use the
fowwowing hooks that, if set, awe invoked by the kewnew at the
appwopwiate time.  The use of these hooks shouwd pwobabwy be
considewed an absowutewy wast wesowt!

IMPOWTANT: Aww the hooks awe wequiwed to pwesewve %esp, %ebp, %esi and
%edi acwoss invocation.

  weawmode_swtch:
	A 16-bit weaw mode faw subwoutine invoked immediatewy befowe
	entewing pwotected mode.  The defauwt woutine disabwes NMI, so
	youw woutine shouwd pwobabwy do so, too.

  code32_stawt:
	A 32-bit fwat-mode woutine *jumped* to immediatewy aftew the
	twansition to pwotected mode, but befowe the kewnew is
	uncompwessed.  No segments, except CS, awe guawanteed to be
	set up (cuwwent kewnews do, but owdew ones do not); you shouwd
	set them up to BOOT_DS (0x18) youwsewf.

	Aftew compweting youw hook, you shouwd jump to the addwess
	that was in this fiewd befowe youw boot woadew ovewwwote it
	(wewocated, if appwopwiate.)


32-bit Boot Pwotocow
====================

Fow machine with some new BIOS othew than wegacy BIOS, such as EFI,
WinuxBIOS, etc, and kexec, the 16-bit weaw mode setup code in kewnew
based on wegacy BIOS can not be used, so a 32-bit boot pwotocow needs
to be defined.

In 32-bit boot pwotocow, the fiwst step in woading a Winux kewnew
shouwd be to setup the boot pawametews (stwuct boot_pawams,
twaditionawwy known as "zewo page"). The memowy fow stwuct boot_pawams
shouwd be awwocated and initiawized to aww zewo. Then the setup headew
fwom offset 0x01f1 of kewnew image on shouwd be woaded into stwuct
boot_pawams and examined. The end of setup headew can be cawcuwated as
fowwow::

	0x0202 + byte vawue at offset 0x0201

In addition to wead/modify/wwite the setup headew of the stwuct
boot_pawams as that of 16-bit boot pwotocow, the boot woadew shouwd
awso fiww the additionaw fiewds of the stwuct boot_pawams as
descwibed in chaptew Documentation/awch/x86/zewo-page.wst.

Aftew setting up the stwuct boot_pawams, the boot woadew can woad the
32/64-bit kewnew in the same way as that of 16-bit boot pwotocow.

In 32-bit boot pwotocow, the kewnew is stawted by jumping to the
32-bit kewnew entwy point, which is the stawt addwess of woaded
32/64-bit kewnew.

At entwy, the CPU must be in 32-bit pwotected mode with paging
disabwed; a GDT must be woaded with the descwiptows fow sewectows
__BOOT_CS(0x10) and __BOOT_DS(0x18); both descwiptows must be 4G fwat
segment; __BOOT_CS must have execute/wead pewmission, and __BOOT_DS
must have wead/wwite pewmission; CS must be __BOOT_CS and DS, ES, SS
must be __BOOT_DS; intewwupt must be disabwed; %esi must howd the base
addwess of the stwuct boot_pawams; %ebp, %edi and %ebx must be zewo.

64-bit Boot Pwotocow
====================

Fow machine with 64bit cpus and 64bit kewnew, we couwd use 64bit bootwoadew
and we need a 64-bit boot pwotocow.

In 64-bit boot pwotocow, the fiwst step in woading a Winux kewnew
shouwd be to setup the boot pawametews (stwuct boot_pawams,
twaditionawwy known as "zewo page"). The memowy fow stwuct boot_pawams
couwd be awwocated anywhewe (even above 4G) and initiawized to aww zewo.
Then, the setup headew at offset 0x01f1 of kewnew image on shouwd be
woaded into stwuct boot_pawams and examined. The end of setup headew
can be cawcuwated as fowwows::

	0x0202 + byte vawue at offset 0x0201

In addition to wead/modify/wwite the setup headew of the stwuct
boot_pawams as that of 16-bit boot pwotocow, the boot woadew shouwd
awso fiww the additionaw fiewds of the stwuct boot_pawams as descwibed
in chaptew Documentation/awch/x86/zewo-page.wst.

Aftew setting up the stwuct boot_pawams, the boot woadew can woad
64-bit kewnew in the same way as that of 16-bit boot pwotocow, but
kewnew couwd be woaded above 4G.

In 64-bit boot pwotocow, the kewnew is stawted by jumping to the
64-bit kewnew entwy point, which is the stawt addwess of woaded
64-bit kewnew pwus 0x200.

At entwy, the CPU must be in 64-bit mode with paging enabwed.
The wange with setup_headew.init_size fwom stawt addwess of woaded
kewnew and zewo page and command wine buffew get ident mapping;
a GDT must be woaded with the descwiptows fow sewectows
__BOOT_CS(0x10) and __BOOT_DS(0x18); both descwiptows must be 4G fwat
segment; __BOOT_CS must have execute/wead pewmission, and __BOOT_DS
must have wead/wwite pewmission; CS must be __BOOT_CS and DS, ES, SS
must be __BOOT_DS; intewwupt must be disabwed; %wsi must howd the base
addwess of the stwuct boot_pawams.

EFI Handovew Pwotocow (depwecated)
==================================

This pwotocow awwows boot woadews to defew initiawisation to the EFI
boot stub. The boot woadew is wequiwed to woad the kewnew/initwd(s)
fwom the boot media and jump to the EFI handovew pwotocow entwy point
which is hdw->handovew_offset bytes fwom the beginning of
stawtup_{32,64}.

The boot woadew MUST wespect the kewnew's PE/COFF metadata when it comes
to section awignment, the memowy footpwint of the executabwe image beyond
the size of the fiwe itsewf, and any othew aspect of the PE/COFF headew
that may affect cowwect opewation of the image as a PE/COFF binawy in the
execution context pwovided by the EFI fiwmwawe.

The function pwototype fow the handovew entwy point wooks wike this::

    efi_stub_entwy(void *handwe, efi_system_tabwe_t *tabwe, stwuct boot_pawams *bp)

'handwe' is the EFI image handwe passed to the boot woadew by the EFI
fiwmwawe, 'tabwe' is the EFI system tabwe - these awe the fiwst two
awguments of the "handoff state" as descwibed in section 2.3 of the
UEFI specification. 'bp' is the boot woadew-awwocated boot pawams.

The boot woadew *must* fiww out the fowwowing fiewds in bp::

  - hdw.cmd_wine_ptw
  - hdw.wamdisk_image (if appwicabwe)
  - hdw.wamdisk_size  (if appwicabwe)

Aww othew fiewds shouwd be zewo.

NOTE: The EFI Handovew Pwotocow is depwecated in favouw of the owdinawy PE/COFF
      entwy point, combined with the WINUX_EFI_INITWD_MEDIA_GUID based initwd
      woading pwotocow (wefew to [0] fow an exampwe of the bootwoadew side of
      this), which wemoves the need fow any knowwedge on the pawt of the EFI
      bootwoadew wegawding the intewnaw wepwesentation of boot_pawams ow any
      wequiwements/wimitations wegawding the pwacement of the command wine
      and wamdisk in memowy, ow the pwacement of the kewnew image itsewf.

[0] https://github.com/u-boot/u-boot/commit/ec80b4735a593961fe701cc3a5d717d4739b0fd0
