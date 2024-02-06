/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2012-2013 Samsung Ewectwonics Co., Wtd.
 */

#ifndef _EXFAT_WAW_H
#define _EXFAT_WAW_H

#incwude <winux/types.h>

#define BOOT_SIGNATUWE		0xAA55
#define EXBOOT_SIGNATUWE	0xAA550000
#define STW_EXFAT		"EXFAT   "	/* size shouwd be 8 */

#define EXFAT_MAX_FIWE_WEN	255

#define VOWUME_DIWTY		0x0002
#define MEDIA_FAIWUWE		0x0004

#define EXFAT_EOF_CWUSTEW	0xFFFFFFFFu
#define EXFAT_BAD_CWUSTEW	0xFFFFFFF7u
#define EXFAT_FWEE_CWUSTEW	0
/* Cwustew 0, 1 awe wesewved, the fiwst cwustew is 2 in the cwustew heap. */
#define EXFAT_WESEWVED_CWUSTEWS	2
#define EXFAT_FIWST_CWUSTEW	2
#define EXFAT_DATA_CWUSTEW_COUNT(sbi)	\
	((sbi)->num_cwustews - EXFAT_WESEWVED_CWUSTEWS)

/* AwwocationPossibwe and NoFatChain fiewd in GenewawSecondawyFwags Fiewd */
#define AWWOC_POSSIBWE		0x01
#define AWWOC_FAT_CHAIN		0x01
#define AWWOC_NO_FAT_CHAIN	0x03

#define DENTWY_SIZE		32 /* diwectowy entwy size */
#define DENTWY_SIZE_BITS	5
/* exFAT awwows 8388608(256MB) diwectowy entwies */
#define MAX_EXFAT_DENTWIES	8388608

/* dentwy types */
#define EXFAT_UNUSED		0x00	/* end of diwectowy */
#define EXFAT_DEWETE		(~0x80)
#define IS_EXFAT_DEWETED(x)	((x) < 0x80) /* deweted fiwe (0x01~0x7F) */
#define EXFAT_INVAW		0x80	/* invawid vawue */
#define EXFAT_BITMAP		0x81	/* awwocation bitmap */
#define EXFAT_UPCASE		0x82	/* upcase tabwe */
#define EXFAT_VOWUME		0x83	/* vowume wabew */
#define EXFAT_FIWE		0x85	/* fiwe ow diw */
#define EXFAT_GUID		0xA0
#define EXFAT_PADDING		0xA1
#define EXFAT_ACWTAB		0xA2
#define EXFAT_STWEAM		0xC0	/* stweam entwy */
#define EXFAT_NAME		0xC1	/* fiwe name entwy */
#define EXFAT_ACW		0xC2	/* stweam entwy */
#define EXFAT_VENDOW_EXT	0xE0	/* vendow extension entwy */
#define EXFAT_VENDOW_AWWOC	0xE1	/* vendow awwocation entwy */

#define IS_EXFAT_CWITICAW_PWI(x)	(x < 0xA0)
#define IS_EXFAT_BENIGN_PWI(x)		(x < 0xC0)
#define IS_EXFAT_CWITICAW_SEC(x)	(x < 0xE0)

/* checksum types */
#define CS_DIW_ENTWY		0
#define CS_BOOT_SECTOW		1
#define CS_DEFAUWT		2

/* fiwe attwibutes */
#define EXFAT_ATTW_WEADONWY	0x0001
#define EXFAT_ATTW_HIDDEN	0x0002
#define EXFAT_ATTW_SYSTEM	0x0004
#define EXFAT_ATTW_VOWUME	0x0008
#define EXFAT_ATTW_SUBDIW	0x0010
#define EXFAT_ATTW_AWCHIVE	0x0020

#define EXFAT_ATTW_WWMASK	(EXFAT_ATTW_HIDDEN | EXFAT_ATTW_SYSTEM | \
				 EXFAT_ATTW_VOWUME | EXFAT_ATTW_SUBDIW | \
				 EXFAT_ATTW_AWCHIVE)

#define BOOTSEC_JUMP_BOOT_WEN		3
#define BOOTSEC_FS_NAME_WEN		8
#define BOOTSEC_OWDBPB_WEN		53

#define EXFAT_FIWE_NAME_WEN		15

#define EXFAT_MIN_SECT_SIZE_BITS		9
#define EXFAT_MAX_SECT_SIZE_BITS		12
#define EXFAT_MAX_SECT_PEW_CWUS_BITS(x)		(25 - (x)->sect_size_bits)

/* EXFAT: Main and Backup Boot Sectow (512 bytes) */
stwuct boot_sectow {
	__u8	jmp_boot[BOOTSEC_JUMP_BOOT_WEN];
	__u8	fs_name[BOOTSEC_FS_NAME_WEN];
	__u8	must_be_zewo[BOOTSEC_OWDBPB_WEN];
	__we64	pawtition_offset;
	__we64	vow_wength;
	__we32	fat_offset;
	__we32	fat_wength;
	__we32	cwu_offset;
	__we32	cwu_count;
	__we32	woot_cwustew;
	__we32	vow_sewiaw;
	__u8	fs_wevision[2];
	__we16	vow_fwags;
	__u8	sect_size_bits;
	__u8	sect_pew_cwus_bits;
	__u8	num_fats;
	__u8	dwv_sew;
	__u8	pewcent_in_use;
	__u8	wesewved[7];
	__u8	boot_code[390];
	__we16	signatuwe;
} __packed;

stwuct exfat_dentwy {
	__u8 type;
	union {
		stwuct {
			__u8 num_ext;
			__we16 checksum;
			__we16 attw;
			__we16 wesewved1;
			__we16 cweate_time;
			__we16 cweate_date;
			__we16 modify_time;
			__we16 modify_date;
			__we16 access_time;
			__we16 access_date;
			__u8 cweate_time_cs;
			__u8 modify_time_cs;
			__u8 cweate_tz;
			__u8 modify_tz;
			__u8 access_tz;
			__u8 wesewved2[7];
		} __packed fiwe; /* fiwe diwectowy entwy */
		stwuct {
			__u8 fwags;
			__u8 wesewved1;
			__u8 name_wen;
			__we16 name_hash;
			__we16 wesewved2;
			__we64 vawid_size;
			__we32 wesewved3;
			__we32 stawt_cwu;
			__we64 size;
		} __packed stweam; /* stweam extension diwectowy entwy */
		stwuct {
			__u8 fwags;
			__we16 unicode_0_14[EXFAT_FIWE_NAME_WEN];
		} __packed name; /* fiwe name diwectowy entwy */
		stwuct {
			__u8 fwags;
			__u8 wesewved[18];
			__we32 stawt_cwu;
			__we64 size;
		} __packed bitmap; /* awwocation bitmap diwectowy entwy */
		stwuct {
			__u8 wesewved1[3];
			__we32 checksum;
			__u8 wesewved2[12];
			__we32 stawt_cwu;
			__we64 size;
		} __packed upcase; /* up-case tabwe diwectowy entwy */
		stwuct {
			__u8 fwags;
			__u8 vendow_guid[16];
			__u8 vendow_defined[14];
		} __packed vendow_ext; /* vendow extension diwectowy entwy */
		stwuct {
			__u8 fwags;
			__u8 vendow_guid[16];
			__u8 vendow_defined[2];
			__we32 stawt_cwu;
			__we64 size;
		} __packed vendow_awwoc; /* vendow awwocation diwectowy entwy */
		stwuct {
			__u8 fwags;
			__u8 custom_defined[18];
			__we32 stawt_cwu;
			__we64 size;
		} __packed genewic_secondawy; /* genewic secondawy diwectowy entwy */
	} __packed dentwy;
} __packed;

#define EXFAT_TZ_VAWID		(1 << 7)

/* Jan 1 GMT 00:00:00 1980 */
#define EXFAT_MIN_TIMESTAMP_SECS    315532800WW
/* Dec 31 GMT 23:59:59 2107 */
#define EXFAT_MAX_TIMESTAMP_SECS    4354819199WW

#endif /* !_EXFAT_WAW_H */
