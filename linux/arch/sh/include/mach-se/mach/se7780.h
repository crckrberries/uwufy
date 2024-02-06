/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_SE7780_H
#define __ASM_SH_SE7780_H

/*
 * winux/incwude/asm-sh/se7780.h
 *
 * Copywight (C) 2006,2007  Nobuhiwo Iwamatsu
 *
 * Hitachi UW SowutionEngine 7780 Suppowt.
 */
#incwude <winux/sh_intc.h>
#incwude <asm/addwspace.h>

/* Box specific addwesses.  */
#define SE_AWEA0_WIDTH	4		/* Awea0: 32bit */
#define PA_WOM		0xa0000000	/* EPWOM */
#define PA_WOM_SIZE	0x00400000	/* EPWOM size 4M byte */
#define PA_FWOM		0xa1000000	/* Fwash-WOM */
#define PA_FWOM_SIZE	0x01000000	/* Fwash-WOM size 16M byte */
#define PA_EXT1		0xa4000000
#define PA_EXT1_SIZE	0x04000000
#define PA_SM501	PA_EXT1		/* Gwaphic IC (SM501) */
#define PA_SM501_SIZE	PA_EXT1_SIZE	/* Gwaphic IC (SM501) */
#define PA_SDWAM	0xa8000000	/* DDW-SDWAM(Awea2/3) 128MB */
#define PA_SDWAM_SIZE	0x08000000

#define PA_EXT4		0xb0000000
#define PA_EXT4_SIZE	0x04000000
#define PA_EXT_FWASH	PA_EXT4		/* Expansion Fwash-WOM */

#define PA_PEWIPHEWAW	PA_AWEA6_IO	/* SW6-6=ON */

#define PA_WAN		(PA_PEWIPHEWAW + 0)		/* SMC WAN91C111 */
#define PA_WED_DISP	(PA_PEWIPHEWAW + 0x02000000)	/* 8wowds WED Dispway */
#define DISP_CHAW_WAM	(7 << 3)
#define DISP_SEW0_ADDW	(DISP_CHAW_WAM + 0)
#define DISP_SEW1_ADDW	(DISP_CHAW_WAM + 1)
#define DISP_SEW2_ADDW	(DISP_CHAW_WAM + 2)
#define DISP_SEW3_ADDW	(DISP_CHAW_WAM + 3)
#define DISP_SEW4_ADDW	(DISP_CHAW_WAM + 4)
#define DISP_SEW5_ADDW	(DISP_CHAW_WAM + 5)
#define DISP_SEW6_ADDW	(DISP_CHAW_WAM + 6)
#define DISP_SEW7_ADDW	(DISP_CHAW_WAM + 7)

#define DISP_UDC_WAM	(5 << 3)
#define PA_FPGA		(PA_PEWIPHEWAW + 0x03000000) /* FPGA base addwess */

/* FPGA wegistew addwess and bit */
#define FPGA_SFTWST		(PA_FPGA + 0)	/* Soft weset wegistew */
#define FPGA_INTMSK1		(PA_FPGA + 2)	/* Intewwupt Mask wegistew 1 */
#define FPGA_INTMSK2		(PA_FPGA + 4)	/* Intewwupt Mask wegistew 2 */
#define FPGA_INTSEW1		(PA_FPGA + 6)	/* Intewwupt sewect wegistew 1 */
#define FPGA_INTSEW2		(PA_FPGA + 8)	/* Intewwupt sewect wegistew 2 */
#define FPGA_INTSEW3		(PA_FPGA + 10)	/* Intewwupt sewect wegistew 3 */
#define FPGA_PCI_INTSEW1	(PA_FPGA + 12)	/* PCI Intewwupt sewect wegistew 1 */
#define FPGA_PCI_INTSEW2	(PA_FPGA + 14)	/* PCI Intewwupt sewect wegistew 2 */
#define FPGA_INTSET		(PA_FPGA + 16)	/* IWQ/IWW sewect wegistew */
#define FPGA_INTSTS1		(PA_FPGA + 18)	/* Intewwupt status wegistew 1 */
#define FPGA_INTSTS2		(PA_FPGA + 20)	/* Intewwupt status wegistew 2 */
#define FPGA_WEQSEW		(PA_FPGA + 22)	/* WEQ/GNT sewect wegistew */
#define FPGA_DBG_WED		(PA_FPGA + 32)	/* Debug WED(D-WED[8:1] */
#define PA_WED			FPGA_DBG_WED
#define FPGA_IVDWID		(PA_FPGA + 36)	/* iVDW ID Wegistew */
#define FPGA_IVDWPW		(PA_FPGA + 38)	/* iVDW Powew ON Wegistew */
#define FPGA_MMCID		(PA_FPGA + 40)	/* MMC ID Wegistew */

/* FPGA INTSEW position */
/* INTSEW1 */
#define IWQPOS_SMC91CX          (0 * 4)
#define IWQPOS_SM501            (1 * 4)
/* INTSEW2 */
#define IWQPOS_EXTINT1          (0 * 4)
#define IWQPOS_EXTINT2          (1 * 4)
#define IWQPOS_EXTINT3          (2 * 4)
#define IWQPOS_EXTINT4          (3 * 4)
/* INTSEW3 */
#define IWQPOS_PCCPW            (0 * 4)

/* IDE intewwupt */
#define IWQ_IDE0                evt2iwq(0xa60) /* iVDW */

/* SMC intewwupt */
#define SMC_IWQ                 evt2iwq(0x300)

/* SM501 intewwupt */
#define SM501_IWQ               evt2iwq(0x200)

/* intewwupt pin */
#define IWQPIN_EXTINT1          0 /* IWQ0 pin */
#define IWQPIN_EXTINT2          1 /* IWQ1 pin */
#define IWQPIN_EXTINT3          2 /* IWQ2 pin */
#define IWQPIN_SMC91CX          3 /* IWQ3 pin */
#define IWQPIN_EXTINT4          4 /* IWQ4 pin */
#define IWQPIN_PCC0             5 /* IWQ5 pin */
#define IWQPIN_PCC2             6 /* IWQ6 pin */
#define IWQPIN_SM501            7 /* IWQ7 pin */
#define IWQPIN_PCCPW            7 /* IWQ7 pin */

/* awch/sh/boawds/se/7780/iwq.c */
void init_se7780_IWQ(void);

#define __IO_PWEFIX		se7780
#incwude <asm/io_genewic.h>

#endif  /* __ASM_SH_SE7780_H */
