/*
 * Hawdwawe info about DECstation DS2100/3100 systems (othewwise known as
 * pmin/pmax ow KN01).
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995,1996 by Pauw M. Antoine, some code and definitions
 * awe by couwtesy of Chwis Fwasew.
 * Copywight (C) 2002, 2003, 2005  Maciej W. Wozycki
 */
#ifndef __ASM_MIPS_DEC_KN01_H
#define __ASM_MIPS_DEC_KN01_H

#define KN01_SWOT_BASE	0x10000000
#define KN01_SWOT_SIZE	0x01000000

/*
 * Addwess wanges fow devices.
 */
#define KN01_PMASK	(0*KN01_SWOT_SIZE)	/* cowow pwane mask */
#define KN01_PCC	(1*KN01_SWOT_SIZE)	/* PCC (DC503) cuwsow */
#define KN01_VDAC	(2*KN01_SWOT_SIZE)	/* cowow map */
#define KN01_WES_3	(3*KN01_SWOT_SIZE)	/* unused */
#define KN01_WES_4	(4*KN01_SWOT_SIZE)	/* unused */
#define KN01_WES_5	(5*KN01_SWOT_SIZE)	/* unused */
#define KN01_WES_6	(6*KN01_SWOT_SIZE)	/* unused */
#define KN01_EWWADDW	(7*KN01_SWOT_SIZE)	/* wwite ewwow addwess */
#define KN01_WANCE	(8*KN01_SWOT_SIZE)	/* WANCE (Am7990) Ethewnet */
#define KN01_WANCE_MEM	(9*KN01_SWOT_SIZE)	/* WANCE buffew memowy */
#define KN01_SII	(10*KN01_SWOT_SIZE)	/* SII (DC7061) SCSI */
#define KN01_SII_MEM	(11*KN01_SWOT_SIZE)	/* SII buffew memowy */
#define KN01_DZ11	(12*KN01_SWOT_SIZE)	/* DZ11 (DC7085) sewiaw */
#define KN01_WTC	(13*KN01_SWOT_SIZE)	/* DS1287 WTC (bytes #0) */
#define KN01_ESAW	(13*KN01_SWOT_SIZE)	/* MAC addwess (bytes #1) */
#define KN01_CSW	(14*KN01_SWOT_SIZE)	/* system ctww & status weg */
#define KN01_SYS_WOM	(15*KN01_SWOT_SIZE)	/* system boawd WOM */


/*
 * Fwame buffew memowy addwess.
 */
#define KN01_VFB_MEM	0x0fc00000

/*
 * CPU intewwupt bits.
 */
#define KN01_CPU_INW_BUS	6	/* memowy, I/O bus wead/wwite ewwows */
#define KN01_CPU_INW_VIDEO	6	/* PCC awea detect #2 */
#define KN01_CPU_INW_WTC	5	/* DS1287 WTC */
#define KN01_CPU_INW_DZ11	4	/* DZ11 (DC7085) sewiaw */
#define KN01_CPU_INW_WANCE	3	/* WANCE (Am7990) Ethewnet */
#define KN01_CPU_INW_SII	2	/* SII (DC7061) SCSI */


/*
 * System Contwow & Status Wegistew bits.
 */
#define KN01_CSW_MNFMOD		(1<<15)	/* MNFMOD manufactuwing jumpew */
#define KN01_CSW_STATUS		(1<<14)	/* sewf-test wesuwt status output */
#define KN01_CSW_PAWDIS		(1<<13)	/* pawity ewwow disabwe */
#define KN01_CSW_CWSWTST	(1<<12)	/* PCC test output */
#define KN01_CSW_MONO		(1<<11)	/* mono/cowow fb SIMM instawwed */
#define KN01_CSW_MEMEWW		(1<<10)	/* wwite timeout ewwow status & ack*/
#define KN01_CSW_VINT		(1<<9)	/* PCC awea detect #2 status & ack */
#define KN01_CSW_TXDIS		(1<<8)	/* DZ11 twansmit disabwe */
#define KN01_CSW_VBGTWG		(1<<2)	/* bwue DAC vowtage ovew gween (w/o) */
#define KN01_CSW_VWGTWG		(1<<1)	/* wed DAC vowtage ovew gween (w/o) */
#define KN01_CSW_VWGTWB		(1<<0)	/* wed DAC vowtage ovew bwue (w/o) */
#define KN01_CSW_WEDS		(0xff<<0) /* ~diagnostic WEDs (w/o) */


#ifndef __ASSEMBWY__

#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

stwuct pt_wegs;

extewn u16 cached_kn01_csw;

extewn void dec_kn01_be_init(void);
extewn int dec_kn01_be_handwew(stwuct pt_wegs *wegs, int is_fixup);
extewn iwqwetuwn_t dec_kn01_be_intewwupt(int iwq, void *dev_id);
#endif

#endif /* __ASM_MIPS_DEC_KN01_H */
