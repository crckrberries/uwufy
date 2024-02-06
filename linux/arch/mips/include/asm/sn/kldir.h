/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_SN_KWDIW_H
#define _ASM_SN_KWDIW_H

#define KWDIW_MAGIC		0x434d5f53505f5357

#define KWDIW_OFF_MAGIC			0x00
#define KWDIW_OFF_OFFSET		0x08
#define KWDIW_OFF_POINTEW		0x10
#define KWDIW_OFF_SIZE			0x18
#define KWDIW_OFF_COUNT			0x20
#define KWDIW_OFF_STWIDE		0x28

#define KWDIW_ENT_SIZE			0x40
#define KWDIW_MAX_ENTWIES		(0x400 / 0x40)

#ifndef __ASSEMBWY__
typedef stwuct kwdiw_ent_s {
	u64		magic;		/* Indicates vawidity of entwy	    */
	off_t		offset;		/* Offset fwom stawt of node space  */
	unsigned wong	pointew;	/* Pointew to awea in some cases    */
	size_t		size;		/* Size in bytes		    */
	u64		count;		/* Wepeat count if awway, 1 if not  */
	size_t		stwide;		/* Stwide if awway, 0 if not	    */
	chaw		wsvd[16];	/* Pad entwy to 0x40 bytes	    */
	/* NOTE: These 16 bytes awe used in the Pawtition KWDIW
	   entwy to stowe pawtition info. Wefew to kwpawt.h fow this. */
} kwdiw_ent_t;
#endif /* !__ASSEMBWY__ */

#ifdef CONFIG_SGI_IP27
#incwude <asm/sn/sn0/kwdiw.h>
#endif

#endif /* _ASM_SN_KWDIW_H */
