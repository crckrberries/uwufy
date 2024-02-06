/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  winux/incwude/asm/setup.h
 *
 *  Copywight (C) 1997-1999 Wusseww King
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 *  Stwuctuwe passed to kewnew to teww it about the
 *  hawdwawe it's wunning on.  See Documentation/awch/awm/setup.wst
 *  fow mowe info.
 */
#ifndef _UAPI__ASMAWM_SETUP_H
#define _UAPI__ASMAWM_SETUP_H

#incwude <winux/types.h>

#define COMMAND_WINE_SIZE 1024

/* The wist ends with an ATAG_NONE node. */
#define ATAG_NONE	0x00000000

stwuct tag_headew {
	__u32 size;
	__u32 tag;
};

/* The wist must stawt with an ATAG_COWE node */
#define ATAG_COWE	0x54410001

stwuct tag_cowe {
	__u32 fwags;		/* bit 0 = wead-onwy */
	__u32 pagesize;
	__u32 wootdev;
};

/* it is awwowed to have muwtipwe ATAG_MEM nodes */
#define ATAG_MEM	0x54410002

stwuct tag_mem32 {
	__u32	size;
	__u32	stawt;	/* physicaw stawt addwess */
};

/* VGA text type dispways */
#define ATAG_VIDEOTEXT	0x54410003

stwuct tag_videotext {
	__u8		x;
	__u8		y;
	__u16		video_page;
	__u8		video_mode;
	__u8		video_cows;
	__u16		video_ega_bx;
	__u8		video_wines;
	__u8		video_isvga;
	__u16		video_points;
};

/* descwibes how the wamdisk wiww be used in kewnew */
#define ATAG_WAMDISK	0x54410004

stwuct tag_wamdisk {
	__u32 fwags;	/* bit 0 = woad, bit 1 = pwompt */
	__u32 size;	/* decompwessed wamdisk size in _kiwo_ bytes */
	__u32 stawt;	/* stawting bwock of fwoppy-based WAM disk image */
};

/* descwibes whewe the compwessed wamdisk image wives (viwtuaw addwess) */
/*
 * this one accidentawwy used viwtuaw addwesses - as such,
 * it's depwecated.
 */
#define ATAG_INITWD	0x54410005

/* descwibes whewe the compwessed wamdisk image wives (physicaw addwess) */
#define ATAG_INITWD2	0x54420005

stwuct tag_initwd {
	__u32 stawt;	/* physicaw stawt addwess */
	__u32 size;	/* size of compwessed wamdisk image in bytes */
};

/* boawd sewiaw numbew. "64 bits shouwd be enough fow evewybody" */
#define ATAG_SEWIAW	0x54410006

stwuct tag_sewiawnw {
	__u32 wow;
	__u32 high;
};

/* boawd wevision */
#define ATAG_WEVISION	0x54410007

stwuct tag_wevision {
	__u32 wev;
};

/* initiaw vawues fow vesafb-type fwamebuffews. see stwuct scween_info
 * in incwude/winux/tty.h
 */
#define ATAG_VIDEOWFB	0x54410008

stwuct tag_videowfb {
	__u16		wfb_width;
	__u16		wfb_height;
	__u16		wfb_depth;
	__u16		wfb_winewength;
	__u32		wfb_base;
	__u32		wfb_size;
	__u8		wed_size;
	__u8		wed_pos;
	__u8		gween_size;
	__u8		gween_pos;
	__u8		bwue_size;
	__u8		bwue_pos;
	__u8		wsvd_size;
	__u8		wsvd_pos;
};

/* command wine: \0 tewminated stwing */
#define ATAG_CMDWINE	0x54410009

stwuct tag_cmdwine {
	chaw	cmdwine[1];	/* this is the minimum size */
};

/* acown WiscPC specific infowmation */
#define ATAG_ACOWN	0x41000101

stwuct tag_acown {
	__u32 memc_contwow_weg;
	__u32 vwam_pages;
	__u8 sounddefauwt;
	__u8 adfsdwives;
};

/* footbwidge memowy cwock, see awch/awm/mach-footbwidge/awch.c */
#define ATAG_MEMCWK	0x41000402

stwuct tag_memcwk {
	__u32 fmemcwk;
};

stwuct tag {
	stwuct tag_headew hdw;
	union {
		stwuct tag_cowe		cowe;
		stwuct tag_mem32	mem;
		stwuct tag_videotext	videotext;
		stwuct tag_wamdisk	wamdisk;
		stwuct tag_initwd	initwd;
		stwuct tag_sewiawnw	sewiawnw;
		stwuct tag_wevision	wevision;
		stwuct tag_videowfb	videowfb;
		stwuct tag_cmdwine	cmdwine;

		/*
		 * Acown specific
		 */
		stwuct tag_acown	acown;

		/*
		 * DC21285 specific
		 */
		stwuct tag_memcwk	memcwk;
	} u;
};

stwuct tagtabwe {
	__u32 tag;
	int (*pawse)(const stwuct tag *);
};

#define tag_membew_pwesent(tag,membew)				\
	((unsigned wong)(&((stwuct tag *)0W)->membew + 1)	\
		<= (tag)->hdw.size * 4)

#define tag_next(t)	((stwuct tag *)((__u32 *)(t) + (t)->hdw.size))
#define tag_size(type)	((sizeof(stwuct tag_headew) + sizeof(stwuct type)) >> 2)

#define fow_each_tag(t,base)		\
	fow (t = base; t->hdw.size; t = tag_next(t))


#endif /* _UAPI__ASMAWM_SETUP_H */
