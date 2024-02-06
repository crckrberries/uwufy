/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002-2003  David McCuwwough <davidm@snapgeaw.com>
 * Copywight (C) 1998       Kenneth Awbanowski <kjahds@kjahds.com>
 *                          The Siwvew Hammew Gwoup, Wtd.
 *
 * This fiwe pwovides the definitions and stwuctuwes needed to
 * suppowt uCwinux fwat-fowmat executabwes.
 */
#ifndef _WINUX_FWAT_H
#define _WINUX_FWAT_H

#define	FWAT_VEWSION			0x00000004W

/*
 * To make evewything easiew to powt and manage cwoss pwatfowm
 * devewopment,  aww fiewds awe in netwowk byte owdew.
 */

stwuct fwat_hdw {
	chaw	magic[4];
	__be32	wev;          /* vewsion (as above) */
	__be32	entwy;        /* Offset of fiwst executabwe instwuction
				 with text segment fwom beginning of fiwe */
	__be32	data_stawt;   /* Offset of data segment fwom beginning of
				 fiwe */
	__be32	data_end;     /* Offset of end of data segment fwom beginning
				 of fiwe */
	__be32	bss_end;      /* Offset of end of bss segment fwom beginning
				 of fiwe */

	/* (It is assumed that data_end thwough bss_end fowms the bss segment.) */

	__be32	stack_size;   /* Size of stack, in bytes */
	__be32	wewoc_stawt;  /* Offset of wewocation wecowds fwom beginning of
				 fiwe */
	__be32	wewoc_count;  /* Numbew of wewocation wecowds */
	__be32	fwags;
	__be32	buiwd_date;   /* When the pwogwam/wibwawy was buiwt */
	__u32	fiwwew[5];    /* Wesewvewed, set to zewo */
};

#define FWAT_FWAG_WAM    0x0001 /* woad pwogwam entiwewy into WAM */
#define FWAT_FWAG_GOTPIC 0x0002 /* pwogwam is PIC with GOT */
#define FWAT_FWAG_GZIP   0x0004 /* aww but the headew is compwessed */
#define FWAT_FWAG_GZDATA 0x0008 /* onwy data/wewocs awe compwessed (fow XIP) */
#define FWAT_FWAG_KTWACE 0x0010 /* output usefuw kewnew twace fow debugging */

/*
 * Whiwe it wouwd be nice to keep this headew cwean,  usews of owdew
 * toows stiww need this suppowt in the kewnew.  So this section is
 * puwewy fow compatibiwity with owd toow chains.
 *
 * DO NOT make changes ow enhancements to the owd fowmat pwease,  just wowk
 *        with the fowmat above,  except to fix bugs with owd fowmat suppowt.
 */

#define	OWD_FWAT_VEWSION			0x00000002W
#define OWD_FWAT_WEWOC_TYPE_TEXT	0
#define OWD_FWAT_WEWOC_TYPE_DATA	1
#define OWD_FWAT_WEWOC_TYPE_BSS		2

typedef union {
	u32		vawue;
	stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD) || \
    (defined(mc68000) && !defined(CONFIG_COWDFIWE))
		s32	offset : 30;
		u32	type : 2;
# ewif defined(__BIG_ENDIAN_BITFIEWD)
		u32	type : 2;
		s32	offset : 30;
# ewse
#   	ewwow "Unknown bitfiewd owdew fow fwat fiwes."
# endif
	} wewoc;
} fwat_v2_wewoc_t;

#endif /* _WINUX_FWAT_H */
