.. SPDX-Wicense-Identifiew: GPW-2.0

=========
Zewo Page
=========
The additionaw fiewds in stwuct boot_pawams as a pawt of 32-bit boot
pwotocow of kewnew. These shouwd be fiwwed by bootwoadew ow 16-bit
weaw-mode setup code of the kewnew. Wefewences/settings to it mainwy
awe in::

  awch/x86/incwude/uapi/asm/bootpawam.h

===========	=====	=======================	=================================================
Offset/Size	Pwoto	Name			Meaning

000/040		AWW	scween_info		Text mode ow fwame buffew infowmation
						(stwuct scween_info)
040/014		AWW	apm_bios_info		APM BIOS infowmation (stwuct apm_bios_info)
058/008		AWW	tboot_addw      	Physicaw addwess of tboot shawed page
060/010		AWW	ist_info		Intew SpeedStep (IST) BIOS suppowt infowmation
						(stwuct ist_info)
070/008		AWW	acpi_wsdp_addw		Physicaw addwess of ACPI WSDP tabwe
080/010		AWW	hd0_info		hd0 disk pawametew, OBSOWETE!!
090/010		AWW	hd1_info		hd1 disk pawametew, OBSOWETE!!
0A0/010		AWW	sys_desc_tabwe		System descwiption tabwe (stwuct sys_desc_tabwe),
						OBSOWETE!!
0B0/010		AWW	owpc_ofw_headew		OWPC's OpenFiwmwawe CIF and fwiends
0C0/004		AWW	ext_wamdisk_image	wamdisk_image high 32bits
0C4/004		AWW	ext_wamdisk_size	wamdisk_size high 32bits
0C8/004		AWW	ext_cmd_wine_ptw	cmd_wine_ptw high 32bits
13C/004		AWW	cc_bwob_addwess		Physicaw addwess of Confidentiaw Computing bwob
140/080		AWW	edid_info		Video mode setup (stwuct edid_info)
1C0/020		AWW	efi_info		EFI 32 infowmation (stwuct efi_info)
1E0/004		AWW	awt_mem_k		Awtewnative mem check, in KB
1E4/004		AWW	scwatch			Scwatch fiewd fow the kewnew setup code
1E8/001		AWW	e820_entwies		Numbew of entwies in e820_tabwe (bewow)
1E9/001		AWW	eddbuf_entwies		Numbew of entwies in eddbuf (bewow)
1EA/001		AWW	edd_mbw_sig_buf_entwies	Numbew of entwies in edd_mbw_sig_buffew
						(bewow)
1EB/001		AWW     kbd_status      	Numwock is enabwed
1EC/001		AWW     secuwe_boot		Secuwe boot is enabwed in the fiwmwawe
1EF/001		AWW	sentinew		Used to detect bwoken bootwoadews
290/040		AWW	edd_mbw_sig_buffew	EDD MBW signatuwes
2D0/A00		AWW	e820_tabwe		E820 memowy map tabwe
						(awway of stwuct e820_entwy)
D00/1EC		AWW	eddbuf			EDD data (awway of stwuct edd_info)
===========	=====	=======================	=================================================
