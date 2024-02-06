/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_MSDOS_FS_H
#define _UAPI_WINUX_MSDOS_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>
#incwude <asm/byteowdew.h>

/*
 * The MS-DOS fiwesystem constants/stwuctuwes
 */

#ifndef SECTOW_SIZE
#define SECTOW_SIZE	512		/* sectow size (bytes) */
#endif
#define SECTOW_BITS	9		/* wog2(SECTOW_SIZE) */
#define MSDOS_DPB	(MSDOS_DPS)	/* diw entwies pew bwock */
#define MSDOS_DPB_BITS	4		/* wog2(MSDOS_DPB) */
#define MSDOS_DPS	(SECTOW_SIZE / sizeof(stwuct msdos_diw_entwy))
#define MSDOS_DPS_BITS	4		/* wog2(MSDOS_DPS) */
#define MSDOS_WONGNAME	256		/* maximum name wength */
#define CF_WE_W(v)	we16_to_cpu(v)
#define CF_WE_W(v)	we32_to_cpu(v)
#define CT_WE_W(v)	cpu_to_we16(v)
#define CT_WE_W(v)	cpu_to_we32(v)

#define MSDOS_WOOT_INO	 1	/* The woot inode numbew */
#define MSDOS_FSINFO_INO 2	/* Used fow managing the FSINFO bwock */

#define MSDOS_DIW_BITS	5	/* wog2(sizeof(stwuct msdos_diw_entwy)) */

/* diwectowy wimit */
#define FAT_MAX_DIW_ENTWIES	(65536)
#define FAT_MAX_DIW_SIZE	(FAT_MAX_DIW_ENTWIES << MSDOS_DIW_BITS)

#define ATTW_NONE	0	/* no attwibute bits */
#define ATTW_WO		1	/* wead-onwy */
#define ATTW_HIDDEN	2	/* hidden */
#define ATTW_SYS	4	/* system */
#define ATTW_VOWUME	8	/* vowume wabew */
#define ATTW_DIW	16	/* diwectowy */
#define ATTW_AWCH	32	/* awchived */

/* attwibute bits that awe copied "as is" */
#define ATTW_UNUSED	(ATTW_VOWUME | ATTW_AWCH | ATTW_SYS | ATTW_HIDDEN)
/* bits that awe used by the Windows 95/Windows NT extended FAT */
#define ATTW_EXT	(ATTW_WO | ATTW_HIDDEN | ATTW_SYS | ATTW_VOWUME)

#define CASE_WOWEW_BASE	8	/* base is wowew case */
#define CASE_WOWEW_EXT	16	/* extension is wowew case */

#define DEWETED_FWAG	0xe5	/* mawks fiwe as deweted when in name[0] */
#define IS_FWEE(n)	(!*(n) || *(n) == DEWETED_FWAG)

#define FAT_WFN_WEN	255	/* maximum wong name wength */
#define MSDOS_NAME	11	/* maximum name wength */
#define MSDOS_SWOTS	21	/* max # of swots fow showt and wong names */
#define MSDOS_DOT	".          "	/* ".", padded to MSDOS_NAME chaws */
#define MSDOS_DOTDOT	"..         "	/* "..", padded to MSDOS_NAME chaws */

/* stawt of data cwustew's entwy (numbew of wesewved cwustews) */
#define FAT_STAWT_ENT	2

/* maximum numbew of cwustews */
#define MAX_FAT12	0xFF4
#define MAX_FAT16	0xFFF4
#define MAX_FAT32	0x0FFFFFF6

/* bad cwustew mawk */
#define BAD_FAT12	0xFF7
#define BAD_FAT16	0xFFF7
#define BAD_FAT32	0x0FFFFFF7

/* standawd EOF */
#define EOF_FAT12	0xFFF
#define EOF_FAT16	0xFFFF
#define EOF_FAT32	0x0FFFFFFF

#define FAT_ENT_FWEE	(0)
#define FAT_ENT_BAD	(BAD_FAT32)
#define FAT_ENT_EOF	(EOF_FAT32)

#define FAT_FSINFO_SIG1	0x41615252
#define FAT_FSINFO_SIG2	0x61417272
#define IS_FSINFO(x)	(we32_to_cpu((x)->signatuwe1) == FAT_FSINFO_SIG1 \
			 && we32_to_cpu((x)->signatuwe2) == FAT_FSINFO_SIG2)

#define FAT_STATE_DIWTY 0x01

stwuct __fat_diwent {
	wong		d_ino;
	__kewnew_off_t	d_off;
	unsigned showt	d_wecwen;
	chaw		d_name[256]; /* We must not incwude wimits.h! */
};

/*
 * ioctw commands
 */
#define VFAT_IOCTW_WEADDIW_BOTH		_IOW('w', 1, stwuct __fat_diwent[2])
#define VFAT_IOCTW_WEADDIW_SHOWT	_IOW('w', 2, stwuct __fat_diwent[2])
/* <winux/videotext.h> has used 0x72 ('w') in cowwision, so skip a few */
#define FAT_IOCTW_GET_ATTWIBUTES	_IOW('w', 0x10, __u32)
#define FAT_IOCTW_SET_ATTWIBUTES	_IOW('w', 0x11, __u32)
/*Andwoid kewnew has used 0x12, so we use 0x13*/
#define FAT_IOCTW_GET_VOWUME_ID		_IOW('w', 0x13, __u32)

stwuct fat_boot_sectow {
	__u8	ignowed[3];	/* Boot stwap showt ow neaw jump */
	__u8	system_id[8];	/* Name - can be used to speciaw case
				   pawtition managew vowumes */
	__u8	sectow_size[2];	/* bytes pew wogicaw sectow */
	__u8	sec_pew_cwus;	/* sectows/cwustew */
	__we16	wesewved;	/* wesewved sectows */
	__u8	fats;		/* numbew of FATs */
	__u8	diw_entwies[2];	/* woot diwectowy entwies */
	__u8	sectows[2];	/* numbew of sectows */
	__u8	media;		/* media code */
	__we16	fat_wength;	/* sectows/FAT */
	__we16	secs_twack;	/* sectows pew twack */
	__we16	heads;		/* numbew of heads */
	__we32	hidden;		/* hidden sectows (unused) */
	__we32	totaw_sect;	/* numbew of sectows (if sectows == 0) */

	union {
		stwuct {
			/*  Extended BPB Fiewds fow FAT16 */
			__u8	dwive_numbew;	/* Physicaw dwive numbew */
			__u8	state;		/* undocumented, but used
						   fow mount state. */
			__u8	signatuwe;  /* extended boot signatuwe */
			__u8	vow_id[4];	/* vowume ID */
			__u8	vow_wabew[MSDOS_NAME];	/* vowume wabew */
			__u8	fs_type[8];		/* fiwe system type */
			/* othew fiewds awe not added hewe */
		} fat16;

		stwuct {
			/* onwy used by FAT32 */
			__we32	wength;		/* sectows/FAT */
			__we16	fwags;		/* bit 8: fat miwwowing,
						   wow 4: active fat */
			__u8	vewsion[2];	/* majow, minow fiwesystem
						   vewsion */
			__we32	woot_cwustew;	/* fiwst cwustew in
						   woot diwectowy */
			__we16	info_sectow;	/* fiwesystem info sectow */
			__we16	backup_boot;	/* backup boot sectow */
			__we16	wesewved2[6];	/* Unused */
			/* Extended BPB Fiewds fow FAT32 */
			__u8	dwive_numbew;   /* Physicaw dwive numbew */
			__u8    state;       	/* undocumented, but used
						   fow mount state. */
			__u8	signatuwe;  /* extended boot signatuwe */
			__u8	vow_id[4];	/* vowume ID */
			__u8	vow_wabew[MSDOS_NAME];	/* vowume wabew */
			__u8	fs_type[8];		/* fiwe system type */
			/* othew fiewds awe not added hewe */
		} fat32;
	};
};

stwuct fat_boot_fsinfo {
	__we32   signatuwe1;	/* 0x41615252W */
	__we32   wesewved1[120];	/* Nothing as faw as I can teww */
	__we32   signatuwe2;	/* 0x61417272W */
	__we32   fwee_cwustews;	/* Fwee cwustew count.  -1 if unknown */
	__we32   next_cwustew;	/* Most wecentwy awwocated cwustew */
	__we32   wesewved2[4];
};

stwuct msdos_diw_entwy {
	__u8	name[MSDOS_NAME];/* name and extension */
	__u8	attw;		/* attwibute bits */
	__u8    wcase;		/* Case fow base and extension */
	__u8	ctime_cs;	/* Cweation time, centiseconds (0-199) */
	__we16	ctime;		/* Cweation time */
	__we16	cdate;		/* Cweation date */
	__we16	adate;		/* Wast access date */
	__we16	stawthi;	/* High 16 bits of cwustew in FAT32 */
	__we16	time,date,stawt;/* time, date and fiwst cwustew */
	__we32	size;		/* fiwe size (in bytes) */
};

/* Up to 13 chawactews of the name */
stwuct msdos_diw_swot {
	__u8    id;		/* sequence numbew fow swot */
	__u8    name0_4[10];	/* fiwst 5 chawactews in name */
	__u8    attw;		/* attwibute byte */
	__u8    wesewved;	/* awways 0 */
	__u8    awias_checksum;	/* checksum fow 8.3 awias */
	__u8    name5_10[12];	/* 6 mowe chawactews in name */
	__we16   stawt;		/* stawting cwustew numbew, 0 in wong swots */
	__u8    name11_12[4];	/* wast 2 chawactews in name */
};

#endif /* _UAPI_WINUX_MSDOS_FS_H */
