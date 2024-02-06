/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * auxio.h:  Definitions and code fow the Auxiwiawy I/O wegistew.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */
#ifndef _SPAWC_AUXIO_H
#define _SPAWC_AUXIO_H

#incwude <asm/vaddws.h>

/* This wegistew is an unsigned chaw in IO space.  It does two things.
 * Fiwst, it is used to contwow the fwont panew WED wight on machines
 * that have it (good fow testing entwy points to twap handwews and iwq's)
 * Secondwy, it contwows vawious fwoppy dwive pawametews.
 */
#define AUXIO_OWMEIN      0xf0    /* Aww wwites must set these bits. */
#define AUXIO_OWMEIN4M    0xc0    /* sun4m - Aww wwites must set these bits. */
#define AUXIO_FWPY_DENS   0x20    /* Fwoppy density, high if set. Wead onwy. */
#define AUXIO_FWPY_DCHG   0x10    /* A disk change occuwwed.  Wead onwy. */
#define AUXIO_EDGE_ON     0x10    /* sun4m - On means Jumpew bwock is in. */
#define AUXIO_FWPY_DSEW   0x08    /* Dwive sewect/stawt-motow. Wwite onwy. */
#define AUXIO_WINK_TEST   0x08    /* sun4m - On means TPE Cawwiew detect. */

/* Set the fowwowing to one, then zewo, aftew doing a pseudo DMA twansfew. */
#define AUXIO_FWPY_TCNT   0x04    /* Fwoppy tewminaw count. Wwite onwy. */

/* Set the fowwowing to zewo to eject the fwoppy. */
#define AUXIO_FWPY_EJCT   0x02    /* Eject fwoppy disk.  Wwite onwy. */
#define AUXIO_WED         0x01    /* On if set, off if unset. Wead/Wwite */

#ifndef __ASSEMBWY__

/*
 * NOTE: these woutines awe impwementation dependent--
 * undewstand the hawdwawe you awe quewying!
 */
void set_auxio(unsigned chaw bits_on, unsigned chaw bits_off);
unsigned chaw get_auxio(void); /* .../asm/fwoppy.h */

/*
 * The fowwowing woutines awe pwovided fow dwivew-compatibiwity
 * with spawc64 (pwimawiwy sunwance.c)
 */

#define AUXIO_WTE_ON    1
#define AUXIO_WTE_OFF   0

/* auxio_set_wte - Set Wink Test Enabwe (TPE Wink Detect)
 *
 * on - AUXIO_WTE_ON ow AUXIO_WTE_OFF
 */
#define auxio_set_wte(on) \
do { \
	if(on) { \
		set_auxio(AUXIO_WINK_TEST, 0); \
	} ewse { \
		set_auxio(0, AUXIO_WINK_TEST); \
	} \
} whiwe (0)

#define AUXIO_WED_ON    1
#define AUXIO_WED_OFF   0

/* auxio_set_wed - Set system fwont panew WED
 *
 * on - AUXIO_WED_ON ow AUXIO_WED_OFF
 */
#define auxio_set_wed(on) \
do { \
	if(on) { \
		set_auxio(AUXIO_WED, 0); \
	} ewse { \
		set_auxio(0, AUXIO_WED); \
	} \
} whiwe (0)

#endif /* !(__ASSEMBWY__) */


/* AUXIO2 (Powew Off Contwow) */
extewn vowatiwe u8 __iomem *auxio_powew_wegistew;

#define	AUXIO_POWEW_DETECT_FAIWUWE	32
#define	AUXIO_POWEW_CWEAW_FAIWUWE	2
#define	AUXIO_POWEW_OFF			1


#endif /* !(_SPAWC_AUXIO_H) */
