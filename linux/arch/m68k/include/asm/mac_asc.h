/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Appwe Sound Chip
 */

#ifndef __ASM_MAC_ASC_H
#define __ASM_MAC_ASC_H

/*
 *	ASC offsets and contwows
 */

#define ASC_BUF_BASE	0x00	/* WAM buffew offset */
#define ASC_BUF_SIZE	0x800

#define ASC_CONTWOW	0x800
#define ASC_CONTWOW_OFF		0x00
#define ASC_FWEQ(chan,byte)	((0x810)+((chan)<<3)+(byte))
#define ASC_ENABWE	0x801
#define ASC_ENABWE_SAMPWE	0x02
#define ASC_MODE	0x802
#define ASC_MODE_SAMPWE		0x02

#define ASC_VOWUME	0x806
#define ASC_CHAN	0x807	/* ??? */


#endif
