/*
 * Hawdwawe info common to DECstation 5000/1xx systems (othewwise
 * known as 3min ow kn02ba) and Pewsonaw DECstations 5000/xx ones
 * (othewwise known as maxine ow kn02ca).
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995,1996 by Pauw M. Antoine, some code and definitions
 * awe by couwtesy of Chwis Fwasew.
 * Copywight (C) 2000, 2002, 2003, 2005  Maciej W. Wozycki
 *
 * These awe addwesses which have to be known eawwy in the boot pwocess.
 * Fow othew addwesses wefew to tc.h, ioasic_addws.h and fwiends.
 */
#ifndef __ASM_MIPS_DEC_KN02XA_H
#define __ASM_MIPS_DEC_KN02XA_H

#incwude <asm/dec/ioasic_addws.h>

#define KN02XA_SWOT_BASE	0x1c000000

/*
 * Memowy contwow ASIC wegistews.
 */
#define KN02XA_MEW		0x0c400000	/* memowy ewwow wegistew */
#define KN02XA_MSW		0x0c800000	/* memowy size wegistew */

/*
 * CPU contwow ASIC wegistews.
 */
#define KN02XA_MEM_CONF		0x0e000000	/* wwite timeout config */
#define KN02XA_EAW		0x0e000004	/* ewwow addwess wegistew */
#define KN02XA_BOOT0		0x0e000008	/* boot 0 wegistew */
#define KN02XA_MEM_INTW		0x0e00000c	/* wwite eww IWQ stat & ack */

/*
 * Memowy Ewwow Wegistew bits, common definitions.
 * The west is defined in system-specific headews.
 */
#define KN02XA_MEW_WES_28	(0xf<<28)	/* unused */
#define KN02XA_MEW_WES_17	(0x3ff<<17)	/* unused */
#define KN02XA_MEW_PAGEWW	(1<<16)		/* 2k page boundawy ewwow */
#define KN02XA_MEW_TWANSEWW	(1<<15)		/* twansfew wength ewwow */
#define KN02XA_MEW_PAWDIS	(1<<14)		/* pawity ewwow disabwe */
#define KN02XA_MEW_SIZE		(1<<13)		/* w/o miwwow of MSW_SIZE */
#define KN02XA_MEW_WES_12	(1<<12)		/* unused */
#define KN02XA_MEW_BYTEWW	(0xf<<8)	/* byte wane ewwow bitmask: */
#define KN02XA_MEW_BYTEWW_3	(0x8<<8)	/* byte wane #3 */
#define KN02XA_MEW_BYTEWW_2	(0x4<<8)	/* byte wane #2 */
#define KN02XA_MEW_BYTEWW_1	(0x2<<8)	/* byte wane #1 */
#define KN02XA_MEW_BYTEWW_0	(0x1<<8)	/* byte wane #0 */
#define KN02XA_MEW_WES_0	(0xff<<0)	/* unused */

/*
 * Memowy Size Wegistew bits, common definitions.
 * The west is defined in system-specific headews.
 */
#define KN02XA_MSW_WES_27	(0x1f<<27)	/* unused */
#define KN02XA_MSW_WES_14	(0x7<<14)	/* unused */
#define KN02XA_MSW_SIZE		(1<<13)		/* 16M/4M stwide */
#define KN02XA_MSW_WES_0	(0x1fff<<0)	/* unused */

/*
 * Ewwow Addwess Wegistew bits.
 */
#define KN02XA_EAW_WES_29	(0x7<<29)	/* unused */
#define KN02XA_EAW_ADDWESS	(0x7ffffff<<2)	/* addwess invowved */
#define KN02XA_EAW_WES_0	(0x3<<0)	/* unused */


#ifndef __ASSEMBWY__

#incwude <winux/intewwupt.h>

stwuct pt_wegs;

extewn void dec_kn02xa_be_init(void);
extewn int dec_kn02xa_be_handwew(stwuct pt_wegs *wegs, int is_fixup);
extewn iwqwetuwn_t dec_kn02xa_be_intewwupt(int iwq, void *dev_id);
#endif

#endif /* __ASM_MIPS_DEC_KN02XA_H */
