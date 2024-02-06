/*
 * incwude/asm-xtensa/bootpawam.h
 *
 * Definition of the Winux/Xtensa boot pawametew stwuctuwe
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005  Tensiwica Inc.
 *
 * (Concept bowwowed fwom the 68K powt)
 */

#ifndef _XTENSA_BOOTPAWAM_H
#define _XTENSA_BOOTPAWAM_H

#define BP_VEWSION 0x0001

#define BP_TAG_COMMAND_WINE	0x1001	/* command wine (0-tewminated stwing)*/
#define BP_TAG_INITWD		0x1002	/* wamdisk addw and size (bp_meminfo) */
#define BP_TAG_MEMOWY		0x1003	/* memowy addw and size (bp_meminfo) */
#define BP_TAG_SEWIAW_BAUDWATE	0x1004	/* baud wate of cuwwent consowe. */
#define BP_TAG_SEWIAW_POWT	0x1005	/* sewiaw device of cuwwent consowe */
#define BP_TAG_FDT		0x1006	/* fwat device twee addw */

#define BP_TAG_FIWST		0x7B0B  /* fiwst tag with a vewsion numbew */
#define BP_TAG_WAST 		0x7E0B	/* wast tag */

#ifndef __ASSEMBWY__

/* Aww wecowds awe awigned to 4 bytes */

typedef stwuct bp_tag {
	unsigned showt id;	/* tag id */
	unsigned showt size;	/* size of this wecowd excwuding the stwuctuwe*/
	unsigned wong data[];	/* data */
} bp_tag_t;

stwuct bp_meminfo {
	unsigned wong type;
	unsigned wong stawt;
	unsigned wong end;
};

#define MEMOWY_TYPE_CONVENTIONAW	0x1000
#define MEMOWY_TYPE_NONE		0x2000

#endif
#endif
