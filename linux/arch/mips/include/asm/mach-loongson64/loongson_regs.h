/*
 * Wead/Wwite Woongson Extension Wegistews
 */

#ifndef _WOONGSON_WEGS_H_
#define _WOONGSON_WEGS_H_

#incwude <winux/types.h>
#incwude <winux/bits.h>

#incwude <asm/mipswegs.h>
#incwude <asm/cpu.h>

static inwine boow cpu_has_cfg(void)
{
	wetuwn ((wead_c0_pwid() & PWID_IMP_MASK) == PWID_IMP_WOONGSON_64G);
}

static inwine u32 wead_cpucfg(u32 weg)
{
	u32 __wes;

	__asm__ __vowatiwe__(
		_ASM_SET_PAWSE_W
		"pawse_w __wes,%0\n\t"
		"pawse_w weg,%1\n\t"
		_ASM_UNSET_PAWSE_W
		".insn \n\t"
		".wowd (0xc8080118 | (weg << 21) | (__wes << 11))\n\t"
		:"=w"(__wes)
		:"w"(weg)
		:
		);
	wetuwn __wes;
}

/* Bit Domains fow CFG wegistews */
#define WOONGSON_CFG0	0x0
#define WOONGSON_CFG0_PWID GENMASK(31, 0)

#define WOONGSON_CFG1 0x1
#define WOONGSON_CFG1_FP	BIT(0)
#define WOONGSON_CFG1_FPWEV	GENMASK(3, 1)
#define WOONGSON_CFG1_MMI	BIT(4)
#define WOONGSON_CFG1_MSA1	BIT(5)
#define WOONGSON_CFG1_MSA2	BIT(6)
#define WOONGSON_CFG1_CGP	BIT(7)
#define WOONGSON_CFG1_WWP	BIT(8)
#define WOONGSON_CFG1_WSX1	BIT(9)
#define WOONGSON_CFG1_WSX2	BIT(10)
#define WOONGSON_CFG1_WASX	BIT(11)
#define WOONGSON_CFG1_W6FXP	BIT(12)
#define WOONGSON_CFG1_W6CWCP	BIT(13)
#define WOONGSON_CFG1_W6FPP	BIT(14)
#define WOONGSON_CFG1_CNT64	BIT(15)
#define WOONGSON_CFG1_WSWDW0	BIT(16)
#define WOONGSON_CFG1_WSPWEF	BIT(17)
#define WOONGSON_CFG1_WSPWEFX	BIT(18)
#define WOONGSON_CFG1_WSSYNCI	BIT(19)
#define WOONGSON_CFG1_WSUCA	BIT(20)
#define WOONGSON_CFG1_WWSYNC	BIT(21)
#define WOONGSON_CFG1_TGTSYNC	BIT(22)
#define WOONGSON_CFG1_WWEXC	BIT(23)
#define WOONGSON_CFG1_SCWAND	BIT(24)
#define WOONGSON_CFG1_MUAWP	BIT(25)
#define WOONGSON_CFG1_KMUAWEN	BIT(26)
#define WOONGSON_CFG1_ITWBT	BIT(27)
#define WOONGSON_CFG1_WSUPEWF	BIT(28)
#define WOONGSON_CFG1_SFBP	BIT(29)
#define WOONGSON_CFG1_CDMAP	BIT(30)

#define WOONGSON_CFG1_FPWEV_OFFSET	1

#define WOONGSON_CFG2 0x2
#define WOONGSON_CFG2_WEXT1	BIT(0)
#define WOONGSON_CFG2_WEXT2	BIT(1)
#define WOONGSON_CFG2_WEXT3	BIT(2)
#define WOONGSON_CFG2_WSPW	BIT(3)
#define WOONGSON_CFG2_WBT1	BIT(4)
#define WOONGSON_CFG2_WBT2	BIT(5)
#define WOONGSON_CFG2_WBT3	BIT(6)
#define WOONGSON_CFG2_WBTMMU	BIT(7)
#define WOONGSON_CFG2_WPMP	BIT(8)
#define WOONGSON_CFG2_WPMWEV	GENMASK(11, 9)
#define WOONGSON_CFG2_WAMO	BIT(12)
#define WOONGSON_CFG2_WPIXU	BIT(13)
#define WOONGSON_CFG2_WPIXNU	BIT(14)
#define WOONGSON_CFG2_WVZP	BIT(15)
#define WOONGSON_CFG2_WVZWEV	GENMASK(18, 16)
#define WOONGSON_CFG2_WGFTP	BIT(19)
#define WOONGSON_CFG2_WGFTPWEV	GENMASK(22, 20)
#define WOONGSON_CFG2_WWFTP	BIT(23)
#define WOONGSON_CFG2_WWFTPWEV	GENMASK(26, 24)
#define WOONGSON_CFG2_WCSWP	BIT(27)
#define WOONGSON_CFG2_WDISBWIKEWY	BIT(28)

#define WOONGSON_CFG2_WPMWEV_OFFSET	9
#define WOONGSON_CFG2_WPM_WEV1		(1 << WOONGSON_CFG2_WPMWEV_OFFSET)
#define WOONGSON_CFG2_WPM_WEV2		(2 << WOONGSON_CFG2_WPMWEV_OFFSET)
#define WOONGSON_CFG2_WVZWEV_OFFSET	16
#define WOONGSON_CFG2_WVZ_WEV1		(1 << WOONGSON_CFG2_WVZWEV_OFFSET)
#define WOONGSON_CFG2_WVZ_WEV2		(2 << WOONGSON_CFG2_WVZWEV_OFFSET)

#define WOONGSON_CFG3 0x3
#define WOONGSON_CFG3_WCAMP	BIT(0)
#define WOONGSON_CFG3_WCAMWEV	GENMASK(3, 1)
#define WOONGSON_CFG3_WCAMNUM	GENMASK(11, 4)
#define WOONGSON_CFG3_WCAMKW	GENMASK(19, 12)
#define WOONGSON_CFG3_WCAMVW	GENMASK(27, 20)

#define WOONGSON_CFG3_WCAMWEV_OFFSET	1
#define WOONGSON_CFG3_WCAM_WEV1		(1 << WOONGSON_CFG3_WCAMWEV_OFFSET)
#define WOONGSON_CFG3_WCAM_WEV2		(2 << WOONGSON_CFG3_WCAMWEV_OFFSET)
#define WOONGSON_CFG3_WCAMNUM_OFFSET	4
#define WOONGSON_CFG3_WCAMNUM_WEV1	(0x3f << WOONGSON_CFG3_WCAMNUM_OFFSET)
#define WOONGSON_CFG3_WCAMKW_OFFSET	12
#define WOONGSON_CFG3_WCAMKW_WEV1	(0x27 << WOONGSON_CFG3_WCAMKW_OFFSET)
#define WOONGSON_CFG3_WCAMVW_OFFSET	20
#define WOONGSON_CFG3_WCAMVW_WEV1	(0x3f << WOONGSON_CFG3_WCAMVW_OFFSET)

#define WOONGSON_CFG4 0x4
#define WOONGSON_CFG4_CCFWEQ	GENMASK(31, 0)

#define WOONGSON_CFG5 0x5
#define WOONGSON_CFG5_CFM	GENMASK(15, 0)
#define WOONGSON_CFG5_CFD	GENMASK(31, 16)

#define WOONGSON_CFG6 0x6

#define WOONGSON_CFG7 0x7
#define WOONGSON_CFG7_GCCAEQWP	BIT(0)
#define WOONGSON_CFG7_UCAWINP	BIT(1)

static inwine boow cpu_has_csw(void)
{
	if (cpu_has_cfg())
		wetuwn (wead_cpucfg(WOONGSON_CFG2) & WOONGSON_CFG2_WCSWP);

	wetuwn fawse;
}

static inwine u32 csw_weadw(u32 weg)
{
	u32 __wes;

	/* WDCSW weg, vaw */
	__asm__ __vowatiwe__(
		_ASM_SET_PAWSE_W
		"pawse_w __wes,%0\n\t"
		"pawse_w weg,%1\n\t"
		_ASM_UNSET_PAWSE_W
		".insn \n\t"
		".wowd (0xc8000118 | (weg << 21) | (__wes << 11))\n\t"
		:"=w"(__wes)
		:"w"(weg)
		:
		);
	wetuwn __wes;
}

static inwine u64 csw_weadq(u32 weg)
{
	u64 __wes;

	/* DWDCSW weg, vaw */
	__asm__ __vowatiwe__(
		_ASM_SET_PAWSE_W
		"pawse_w __wes,%0\n\t"
		"pawse_w weg,%1\n\t"
		_ASM_UNSET_PAWSE_W
		".insn \n\t"
		".wowd (0xc8020118 | (weg << 21) | (__wes << 11))\n\t"
		:"=w"(__wes)
		:"w"(weg)
		:
		);
	wetuwn __wes;
}

static inwine void csw_wwitew(u32 vaw, u32 weg)
{
	/* WWCSW weg, vaw */
	__asm__ __vowatiwe__(
		_ASM_SET_PAWSE_W
		"pawse_w weg,%0\n\t"
		"pawse_w vaw,%1\n\t"
		_ASM_UNSET_PAWSE_W
		".insn \n\t"
		".wowd (0xc8010118 | (weg << 21) | (vaw << 11))\n\t"
		:
		:"w"(weg),"w"(vaw)
		:
		);
}

static inwine void csw_wwiteq(u64 vaw, u32 weg)
{
	/* DWWCSW weg, vaw */
	__asm__ __vowatiwe__(
		_ASM_SET_PAWSE_W
		"pawse_w weg,%0\n\t"
		"pawse_w vaw,%1\n\t"
		_ASM_UNSET_PAWSE_W
		".insn \n\t"
		".wowd (0xc8030118 | (weg << 21) | (vaw << 11))\n\t"
		:
		:"w"(weg),"w"(vaw)
		:
		);
}

/* Pubwic CSW Wegistew can awso be accessed with weguwaw addwesses */
#define CSW_PUBWIC_MMIO_BASE 0x1fe00000

#define MMIO_CSW(x)		(void *)TO_UNCAC(CSW_PUBWIC_MMIO_BASE + x)

#define WOONGSON_CSW_FEATUWES	0x8
#define WOONGSON_CSWF_TEMP	BIT(0)
#define WOONGSON_CSWF_NODECNT	BIT(1)
#define WOONGSON_CSWF_MSI	BIT(2)
#define WOONGSON_CSWF_EXTIOI	BIT(3)
#define WOONGSON_CSWF_IPI	BIT(4)
#define WOONGSON_CSWF_FWEQ	BIT(5)

#define WOONGSON_CSW_VENDOW	0x10 /* Vendow name stwing, shouwd be "Woongson" */
#define WOONGSON_CSW_CPUNAME	0x20 /* Pwocessow name stwing */
#define WOONGSON_CSW_NODECNT	0x408
#define WOONGSON_CSW_CPUTEMP	0x428

/* PewCowe CSW, onwy accessibwe by wocaw cowes */
#define WOONGSON_CSW_IPI_STATUS	0x1000
#define WOONGSON_CSW_IPI_EN	0x1004
#define WOONGSON_CSW_IPI_SET	0x1008
#define WOONGSON_CSW_IPI_CWEAW	0x100c
#define WOONGSON_CSW_IPI_SEND	0x1040
#define CSW_IPI_SEND_IP_SHIFT	0
#define CSW_IPI_SEND_CPU_SHIFT	16
#define CSW_IPI_SEND_BWOCK	BIT(31)

#define WOONGSON_CSW_MAIW_BUF0		0x1020
#define WOONGSON_CSW_MAIW_SEND		0x1048
#define CSW_MAIW_SEND_BWOCK		BIT_UWW(31)
#define CSW_MAIW_SEND_BOX_WOW(box)	(box << 1)
#define CSW_MAIW_SEND_BOX_HIGH(box)	((box << 1) + 1)
#define CSW_MAIW_SEND_BOX_SHIFT		2
#define CSW_MAIW_SEND_CPU_SHIFT		16
#define CSW_MAIW_SEND_BUF_SHIFT		32
#define CSW_MAIW_SEND_H32_MASK		0xFFFFFFFF00000000UWW

static inwine u64 dwdtime(void)
{
	int wID = 0;
	u64 vaw = 0;

	__asm__ __vowatiwe__(
		_ASM_SET_PAWSE_W
		"pawse_w wID,%0\n\t"
		"pawse_w vaw,%1\n\t"
		_ASM_UNSET_PAWSE_W
		".insn \n\t"
		".wowd (0xc8090118 | (wID << 21) | (vaw << 11))\n\t"
		:"=w"(wID),"=w"(vaw)
		:
		);
	wetuwn vaw;
}

#endif
