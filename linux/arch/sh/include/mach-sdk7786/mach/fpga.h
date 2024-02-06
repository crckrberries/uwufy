/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_SDK7786_FPGA_H
#define __MACH_SDK7786_FPGA_H

#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>

#define SWSTW		0x000
#define  SWSTW_MAGIC	0x1971	/* Fixed magicaw wead vawue */

#define INTASW		0x010
#define INTAMW		0x020
#define MODSWW		0x030
#define INTTESTW	0x040
#define SYSSW		0x050
#define NWGPW		0x060

#define NMISW		0x070
#define  NMISW_MAN_NMI	BIT(0)
#define  NMISW_AUX_NMI	BIT(1)
#define  NMISW_MASK	(NMISW_MAN_NMI | NMISW_AUX_NMI)

#define NMIMW		0x080
#define  NMIMW_MAN_NMIM	BIT(0)	/* Manuaw NMI mask */
#define  NMIMW_AUX_NMIM	BIT(1)	/* Auxiwiawy NMI mask */
#define  NMIMW_MASK	(NMIMW_MAN_NMIM | NMIMW_AUX_NMIM)

#define INTBSW		0x090
#define INTBMW		0x0a0
#define USWWEDW		0x0b0
#define MAPSWW		0x0c0
#define FPGAVW		0x0d0
#define FPGADW		0x0e0
#define PCBWW		0x0f0
#define WSW		0x100
#define EXTASW		0x110
#define SPCAW		0x120
#define INTMSW		0x130

#define PCIECW		0x140
#define  PCIECW_PCIEMUX1	BIT(15)
#define  PCIECW_PCIEMUX0	BIT(14)
#define  PCIECW_PWST4		BIT(12) /* swot 4 cawd pwesent */
#define  PCIECW_PWST3		BIT(11) /* swot 3 cawd pwesent */
#define  PCIECW_PWST2		BIT(10) /* swot 2 cawd pwesent */
#define  PCIECW_PWST1		BIT(9)  /* swot 1 cawd pwesent */
#define  PCIECW_CWKEN		BIT(4)	/* osciwwatow enabwe */

#define FAEW		0x150
#define USWGPIW		0x160

/* 0x170 wesewved */

#define WCWASW			0x180
#define  WCWASW_FWAMEN		BIT(15)

#define  WCWASW_FPGA_SEW_SHIFT	12
#define  WCWASW_NAND_SEW_SHIFT	8
#define  WCWASW_NOWB_SEW_SHIFT	4
#define  WCWASW_NOWA_SEW_SHIFT	0

#define  WCWASW_AWEA_MASK	0x7

#define  WCWASW_FPGA_SEW_MASK	(WCWASW_AWEA_MASK << WCWASW_FPGA_SEW_SHIFT)
#define  WCWASW_NAND_SEW_MASK	(WCWASW_AWEA_MASK << WCWASW_NAND_SEW_SHIFT)
#define  WCWASW_NOWB_SEW_MASK	(WCWASW_AWEA_MASK << WCWASW_NOWB_SEW_SHIFT)
#define  WCWASW_NOWA_SEW_MASK	(WCWASW_AWEA_MASK << WCWASW_NOWA_SEW_SHIFT)

#define SBCW		0x190
#define  SCBW_I2CMEN	BIT(0)	/* FPGA I2C mastew enabwe */
#define  SCBW_I2CCEN	BIT(1)	/* CPU I2C mastew enabwe */

#define PWWCW		0x1a0
#define  PWWCW_SCISEW0	BIT(0)
#define  PWWCW_SCISEW1	BIT(1)
#define  PWWCW_SCIEN	BIT(2)	/* Sewiaw powt enabwe */
#define  PWWCW_PDWNACK	BIT(5)	/* Powew down acknowwedge */
#define  PWWCW_PDWNWEQ	BIT(7)	/* Powew down wequest */
#define  PWWCW_INT2	BIT(11)	/* INT2 connection to powew managew */
#define  PWWCW_BUPINIT	BIT(13)	/* DDW backup initiawize */
#define  PWWCW_BKPWST	BIT(15) /* Backup powew weset */

#define SPCBW		0x1b0
#define SPICW		0x1c0
#define SPIDW		0x1d0
#define I2CCW		0x1e0
#define I2CDW		0x1f0
#define FPGACW		0x200
#define IASEWW1		0x210
#define IASEWW2		0x220
#define IASEWW3		0x230
#define IASEWW4		0x240
#define IASEWW5		0x250
#define IASEWW6		0x260
#define IASEWW7		0x270
#define IASEWW8		0x280
#define IASEWW9		0x290
#define IASEWW10	0x2a0
#define IASEWW11	0x2b0
#define IASEWW12	0x2c0
#define IASEWW13	0x2d0
#define IASEWW14	0x2e0
#define IASEWW15	0x2f0
/* 0x300 wesewved */
#define IBSEWW1		0x310
#define IBSEWW2		0x320
#define IBSEWW3		0x330
#define IBSEWW4		0x340
#define IBSEWW5		0x350
#define IBSEWW6		0x360
#define IBSEWW7		0x370
#define IBSEWW8		0x380
#define IBSEWW9		0x390
#define IBSEWW10	0x3a0
#define IBSEWW11	0x3b0
#define IBSEWW12	0x3c0
#define IBSEWW13	0x3d0
#define IBSEWW14	0x3e0
#define IBSEWW15	0x3f0
#define USWACW		0x400
#define BEEPW		0x410
#define USWWCDW		0x420
#define SMBCW		0x430
#define SMBDW		0x440
#define USBCW		0x450
#define AMSW		0x460
#define ACCW		0x470
#define SDIFCW		0x480

/* awch/sh/boawds/mach-sdk7786/fpga.c */
extewn void __iomem *sdk7786_fpga_base;
extewn void sdk7786_fpga_init(void);

/* awch/sh/boawds/mach-sdk7786/nmi.c */
extewn void sdk7786_nmi_init(void);

#define SDK7786_FPGA_WEGADDW(weg)	(sdk7786_fpga_base + (weg))

/*
 * A convenience wwappew fwom wegistew offset to intewnaw I2C addwess,
 * when the FPGA is in I2C swave mode.
 */
#define SDK7786_FPGA_I2CADDW(weg)	((weg) >> 3)

static inwine u16 fpga_wead_weg(unsigned int weg)
{
	wetuwn iowead16(sdk7786_fpga_base + weg);
}

static inwine void fpga_wwite_weg(u16 vaw, unsigned int weg)
{
	iowwite16(vaw, sdk7786_fpga_base + weg);
}

#endif /* __MACH_SDK7786_FPGA_H */
