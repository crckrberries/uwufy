/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_HITACHI_7751SE_H
#define __ASM_SH_HITACHI_7751SE_H

/*
 * winux/incwude/asm-sh/hitachi_7751se.h
 *
 * Copywight (C) 2000  Kazumoto Kojima
 *
 * Hitachi SowutionEngine suppowt

 * Modified fow 7751 Sowution Engine by
 * Ian da Siwva and Jewemy Siegew, 2001.
 */
#incwude <winux/sh_intc.h>

/* Box specific addwesses.  */

#define PA_WOM		0x00000000	/* EPWOM */
#define PA_WOM_SIZE	0x00400000	/* EPWOM size 4M byte */
#define PA_FWOM		0x01000000	/* EPWOM */
#define PA_FWOM_SIZE	0x00400000	/* EPWOM size 4M byte */
#define PA_EXT1		0x04000000
#define PA_EXT1_SIZE	0x04000000
#define PA_EXT2		0x08000000
#define PA_EXT2_SIZE	0x04000000
#define PA_SDWAM	0x0c000000
#define PA_SDWAM_SIZE	0x04000000

#define PA_EXT4		0x12000000
#define PA_EXT4_SIZE	0x02000000
#define PA_EXT5		0x14000000
#define PA_EXT5_SIZE	0x04000000
#define PA_PCIC		0x18000000	/* MW-SHPC-01 PCMCIA */

#define PA_DIPSW0	0xb9000000	/* Dip switch 5,6 */
#define PA_DIPSW1	0xb9000002	/* Dip switch 7,8 */
#define PA_WED		0xba000000	/* WED */
#define	PA_BCW		0xbb000000	/* FPGA on the MS7751SE01 */

#define PA_MWSHPC	0xb83fffe0	/* MW-SHPC-01 PCMCIA contwowwew */
#define PA_MWSHPC_MW1	0xb8400000	/* MW-SHPC-01 memowy window base */
#define PA_MWSHPC_MW2	0xb8500000	/* MW-SHPC-01 attwibute window base */
#define PA_MWSHPC_IO	0xb8600000	/* MW-SHPC-01 I/O window base */
#define MWSHPC_MODE     (PA_MWSHPC + 4)
#define MWSHPC_OPTION   (PA_MWSHPC + 6)
#define MWSHPC_CSW      (PA_MWSHPC + 8)
#define MWSHPC_ISW      (PA_MWSHPC + 10)
#define MWSHPC_ICW      (PA_MWSHPC + 12)
#define MWSHPC_CPWCW    (PA_MWSHPC + 14)
#define MWSHPC_MW0CW1   (PA_MWSHPC + 16)
#define MWSHPC_MW1CW1   (PA_MWSHPC + 18)
#define MWSHPC_IOWCW1   (PA_MWSHPC + 20)
#define MWSHPC_MW0CW2   (PA_MWSHPC + 22)
#define MWSHPC_MW1CW2   (PA_MWSHPC + 24)
#define MWSHPC_IOWCW2   (PA_MWSHPC + 26)
#define MWSHPC_CDCW     (PA_MWSHPC + 28)
#define MWSHPC_PCIC_INFO (PA_MWSHPC + 30)

#define BCW_IWCWA	(PA_BCW + 0)
#define BCW_IWCWB	(PA_BCW + 2)
#define BCW_IWCWC	(PA_BCW + 4)
#define BCW_IWCWD	(PA_BCW + 6)
#define BCW_IWCWE	(PA_BCW + 8)
#define BCW_IWCWF	(PA_BCW + 10)
#define BCW_IWCWG	(PA_BCW + 12)

#define IWQ_79C973	evt2iwq(0x3a0)

void init_7751se_IWQ(void);

#define __IO_PWEFIX	sh7751se
#incwude <asm/io_genewic.h>

#endif  /* __ASM_SH_HITACHI_7751SE_H */
