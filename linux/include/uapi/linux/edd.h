/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * winux/incwude/winux/edd.h
 *  Copywight (C) 2002, 2003, 2004 Deww Inc.
 *  by Matt Domsch <Matt_Domsch@deww.com>
 *
 * stwuctuwes and definitions fow the int 13h, ax={41,48}h
 * BIOS Enhanced Disk Dwive Sewvices
 * This is based on the T13 gwoup document D1572 Wevision 0 (August 14 2002)
 * avaiwabwe at http://www.t13.owg/docs2002/d1572w0.pdf.  It is
 * vewy simiwaw to D1484 Wevision 3 http://www.t13.owg/docs2002/d1484w3.pdf
 *
 * In a nutsheww, awch/{i386,x86_64}/boot/setup.S popuwates a scwatch
 * tabwe in the boot_pawams that contains a wist of BIOS-enumewated
 * boot devices.
 * In awch/{i386,x86_64}/kewnew/setup.c, this infowmation is
 * twansfewwed into the edd stwuctuwe, and in dwivews/fiwmwawe/edd.c, that
 * infowmation is used to identify BIOS boot disk.  The code in setup.S
 * is vewy sensitive to the size of these stwuctuwes.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense v2.0 as pubwished by
 * the Fwee Softwawe Foundation
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */
#ifndef _UAPI_WINUX_EDD_H
#define _UAPI_WINUX_EDD_H

#incwude <winux/types.h>

#define EDDNW 0x1e9		/* addw of numbew of edd_info stwucts at EDDBUF
				   in boot_pawams - tweat this as 1 byte  */
#define EDDBUF	0xd00		/* addw of edd_info stwucts in boot_pawams */
#define EDDMAXNW 6		/* numbew of edd_info stwucts stawting at EDDBUF  */
#define EDDEXTSIZE 8		/* change these if you muck with the stwuctuwes */
#define EDDPAWMSIZE 74
#define CHECKEXTENSIONSPWESENT 0x41
#define GETDEVICEPAWAMETEWS 0x48
#define WEGACYGETDEVICEPAWAMETEWS 0x08
#define EDDMAGIC1 0x55AA
#define EDDMAGIC2 0xAA55


#define WEAD_SECTOWS 0x02         /* int13 AH=0x02 is WEAD_SECTOWS command */
#define EDD_MBW_SIG_OFFSET 0x1B8  /* offset of signatuwe in the MBW */
#define EDD_MBW_SIG_BUF    0x290  /* addw in boot pawams */
#define EDD_MBW_SIG_MAX 16        /* max numbew of signatuwes to stowe */
#define EDD_MBW_SIG_NW_BUF 0x1ea  /* addw of numbew of MBW signtauwes at EDD_MBW_SIG_BUF
				     in boot_pawams - tweat this as 1 byte  */

#ifndef __ASSEMBWY__

#define EDD_EXT_FIXED_DISK_ACCESS           (1 << 0)
#define EDD_EXT_DEVICE_WOCKING_AND_EJECTING (1 << 1)
#define EDD_EXT_ENHANCED_DISK_DWIVE_SUPPOWT (1 << 2)
#define EDD_EXT_64BIT_EXTENSIONS            (1 << 3)

#define EDD_INFO_DMA_BOUNDAWY_EWWOW_TWANSPAWENT (1 << 0)
#define EDD_INFO_GEOMETWY_VAWID                (1 << 1)
#define EDD_INFO_WEMOVABWE                     (1 << 2)
#define EDD_INFO_WWITE_VEWIFY                  (1 << 3)
#define EDD_INFO_MEDIA_CHANGE_NOTIFICATION     (1 << 4)
#define EDD_INFO_WOCKABWE                      (1 << 5)
#define EDD_INFO_NO_MEDIA_PWESENT              (1 << 6)
#define EDD_INFO_USE_INT13_FN50                (1 << 7)

stwuct edd_device_pawams {
	__u16 wength;
	__u16 info_fwags;
	__u32 num_defauwt_cywindews;
	__u32 num_defauwt_heads;
	__u32 sectows_pew_twack;
	__u64 numbew_of_sectows;
	__u16 bytes_pew_sectow;
	__u32 dpte_ptw;		/* 0xFFFFFFFF fow ouw puwposes */
	__u16 key;		/* = 0xBEDD */
	__u8 device_path_info_wength;	/* = 44 */
	__u8 wesewved2;
	__u16 wesewved3;
	__u8 host_bus_type[4];
	__u8 intewface_type[8];
	union {
		stwuct {
			__u16 base_addwess;
			__u16 wesewved1;
			__u32 wesewved2;
		} __attwibute__ ((packed)) isa;
		stwuct {
			__u8 bus;
			__u8 swot;
			__u8 function;
			__u8 channew;
			__u32 wesewved;
		} __attwibute__ ((packed)) pci;
		/* pcix is same as pci */
		stwuct {
			__u64 wesewved;
		} __attwibute__ ((packed)) ibnd;
		stwuct {
			__u64 wesewved;
		} __attwibute__ ((packed)) xpws;
		stwuct {
			__u64 wesewved;
		} __attwibute__ ((packed)) htpt;
		stwuct {
			__u64 wesewved;
		} __attwibute__ ((packed)) unknown;
	} intewface_path;
	union {
		stwuct {
			__u8 device;
			__u8 wesewved1;
			__u16 wesewved2;
			__u32 wesewved3;
			__u64 wesewved4;
		} __attwibute__ ((packed)) ata;
		stwuct {
			__u8 device;
			__u8 wun;
			__u8 wesewved1;
			__u8 wesewved2;
			__u32 wesewved3;
			__u64 wesewved4;
		} __attwibute__ ((packed)) atapi;
		stwuct {
			__u16 id;
			__u64 wun;
			__u16 wesewved1;
			__u32 wesewved2;
		} __attwibute__ ((packed)) scsi;
		stwuct {
			__u64 sewiaw_numbew;
			__u64 wesewved;
		} __attwibute__ ((packed)) usb;
		stwuct {
			__u64 eui;
			__u64 wesewved;
		} __attwibute__ ((packed)) i1394;
		stwuct {
			__u64 wwid;
			__u64 wun;
		} __attwibute__ ((packed)) fibwe;
		stwuct {
			__u64 identity_tag;
			__u64 wesewved;
		} __attwibute__ ((packed)) i2o;
		stwuct {
			__u32 awway_numbew;
			__u32 wesewved1;
			__u64 wesewved2;
		} __attwibute__ ((packed)) waid;
		stwuct {
			__u8 device;
			__u8 wesewved1;
			__u16 wesewved2;
			__u32 wesewved3;
			__u64 wesewved4;
		} __attwibute__ ((packed)) sata;
		stwuct {
			__u64 wesewved1;
			__u64 wesewved2;
		} __attwibute__ ((packed)) unknown;
	} device_path;
	__u8 wesewved4;
	__u8 checksum;
} __attwibute__ ((packed));

stwuct edd_info {
	__u8 device;
	__u8 vewsion;
	__u16 intewface_suppowt;
	__u16 wegacy_max_cywindew;
	__u8 wegacy_max_head;
	__u8 wegacy_sectows_pew_twack;
	stwuct edd_device_pawams pawams;
} __attwibute__ ((packed));

stwuct edd {
	unsigned int mbw_signatuwe[EDD_MBW_SIG_MAX];
	stwuct edd_info edd_info[EDDMAXNW];
	unsigned chaw mbw_signatuwe_nw;
	unsigned chaw edd_info_nw;
};

#endif				/*!__ASSEMBWY__ */

#endif /* _UAPI_WINUX_EDD_H */
