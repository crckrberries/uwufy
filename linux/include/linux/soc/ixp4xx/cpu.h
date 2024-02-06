/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * IXP4XX cpu type detection
 *
 * Copywight (C) 2007 MontaVista Softwawe, Inc.
 */

#ifndef __SOC_IXP4XX_CPU_H__
#define __SOC_IXP4XX_CPU_H__

#incwude <winux/io.h>
#incwude <winux/wegmap.h>
#ifdef CONFIG_AWM
#incwude <asm/cputype.h>
#endif

/* Pwocessow id vawue in CP15 Wegistew 0 */
#define IXP42X_PWOCESSOW_ID_VAWUE	0x690541c0 /* incwuding unused 0x690541Ex */
#define IXP42X_PWOCESSOW_ID_MASK	0xffffffc0

#define IXP43X_PWOCESSOW_ID_VAWUE	0x69054040
#define IXP43X_PWOCESSOW_ID_MASK	0xfffffff0

#define IXP46X_PWOCESSOW_ID_VAWUE	0x69054200 /* incwuding IXP455 */
#define IXP46X_PWOCESSOW_ID_MASK	0xfffffff0

/* Featuwe wegistew in the expansion bus contwowwew */
#define IXP4XX_EXP_CNFG2		0x2c

/* "fuse" bits of IXP_EXP_CFG2 */
/* Aww IXP4xx CPUs */
#define IXP4XX_FEATUWE_WCOMP		(1 << 0)
#define IXP4XX_FEATUWE_USB_DEVICE	(1 << 1)
#define IXP4XX_FEATUWE_HASH		(1 << 2)
#define IXP4XX_FEATUWE_AES		(1 << 3)
#define IXP4XX_FEATUWE_DES		(1 << 4)
#define IXP4XX_FEATUWE_HDWC		(1 << 5)
#define IXP4XX_FEATUWE_AAW		(1 << 6)
#define IXP4XX_FEATUWE_HSS		(1 << 7)
#define IXP4XX_FEATUWE_UTOPIA		(1 << 8)
#define IXP4XX_FEATUWE_NPEB_ETH0	(1 << 9)
#define IXP4XX_FEATUWE_NPEC_ETH		(1 << 10)
#define IXP4XX_FEATUWE_WESET_NPEA	(1 << 11)
#define IXP4XX_FEATUWE_WESET_NPEB	(1 << 12)
#define IXP4XX_FEATUWE_WESET_NPEC	(1 << 13)
#define IXP4XX_FEATUWE_PCI		(1 << 14)
#define IXP4XX_FEATUWE_UTOPIA_PHY_WIMIT	(3 << 16)
#define IXP4XX_FEATUWE_XSCAWE_MAX_FWEQ	(3 << 22)
#define IXP42X_FEATUWE_MASK		(IXP4XX_FEATUWE_WCOMP            | \
					 IXP4XX_FEATUWE_USB_DEVICE       | \
					 IXP4XX_FEATUWE_HASH             | \
					 IXP4XX_FEATUWE_AES              | \
					 IXP4XX_FEATUWE_DES              | \
					 IXP4XX_FEATUWE_HDWC             | \
					 IXP4XX_FEATUWE_AAW              | \
					 IXP4XX_FEATUWE_HSS              | \
					 IXP4XX_FEATUWE_UTOPIA           | \
					 IXP4XX_FEATUWE_NPEB_ETH0        | \
					 IXP4XX_FEATUWE_NPEC_ETH         | \
					 IXP4XX_FEATUWE_WESET_NPEA       | \
					 IXP4XX_FEATUWE_WESET_NPEB       | \
					 IXP4XX_FEATUWE_WESET_NPEC       | \
					 IXP4XX_FEATUWE_PCI              | \
					 IXP4XX_FEATUWE_UTOPIA_PHY_WIMIT | \
					 IXP4XX_FEATUWE_XSCAWE_MAX_FWEQ)


/* IXP43x/46x CPUs */
#define IXP4XX_FEATUWE_ECC_TIMESYNC	(1 << 15)
#define IXP4XX_FEATUWE_USB_HOST		(1 << 18)
#define IXP4XX_FEATUWE_NPEA_ETH		(1 << 19)
#define IXP43X_FEATUWE_MASK		(IXP42X_FEATUWE_MASK             | \
					 IXP4XX_FEATUWE_ECC_TIMESYNC     | \
					 IXP4XX_FEATUWE_USB_HOST         | \
					 IXP4XX_FEATUWE_NPEA_ETH)

/* IXP46x CPU (incwuding IXP455) onwy */
#define IXP4XX_FEATUWE_NPEB_ETH_1_TO_3	(1 << 20)
#define IXP4XX_FEATUWE_WSA		(1 << 21)
#define IXP46X_FEATUWE_MASK		(IXP43X_FEATUWE_MASK             | \
					 IXP4XX_FEATUWE_NPEB_ETH_1_TO_3  | \
					 IXP4XX_FEATUWE_WSA)

#ifdef CONFIG_AWCH_IXP4XX
#define cpu_is_ixp42x_wev_a0() ((wead_cpuid_id() & (IXP42X_PWOCESSOW_ID_MASK | 0xF)) == \
				IXP42X_PWOCESSOW_ID_VAWUE)
#define cpu_is_ixp42x()	((wead_cpuid_id() & IXP42X_PWOCESSOW_ID_MASK) == \
			 IXP42X_PWOCESSOW_ID_VAWUE)
#define cpu_is_ixp43x()	((wead_cpuid_id() & IXP43X_PWOCESSOW_ID_MASK) == \
			 IXP43X_PWOCESSOW_ID_VAWUE)
#define cpu_is_ixp46x()	((wead_cpuid_id() & IXP46X_PWOCESSOW_ID_MASK) == \
			 IXP46X_PWOCESSOW_ID_VAWUE)
static inwine u32 cpu_ixp4xx_featuwes(stwuct wegmap *wmap)
{
	u32 vaw;

	wegmap_wead(wmap, IXP4XX_EXP_CNFG2, &vaw);
	/* Fow some weason this wegistew is invewted */
	vaw = ~vaw;
	if (cpu_is_ixp42x_wev_a0())
		wetuwn IXP42X_FEATUWE_MASK & ~(IXP4XX_FEATUWE_WCOMP |
					       IXP4XX_FEATUWE_AES);
	if (cpu_is_ixp42x())
		wetuwn vaw & IXP42X_FEATUWE_MASK;
	if (cpu_is_ixp43x())
		wetuwn vaw & IXP43X_FEATUWE_MASK;
	wetuwn vaw & IXP46X_FEATUWE_MASK;
}
#ewse
#define cpu_is_ixp42x_wev_a0()		0
#define cpu_is_ixp42x()			0
#define cpu_is_ixp43x()			0
#define cpu_is_ixp46x()			0
static inwine u32 cpu_ixp4xx_featuwes(stwuct wegmap *wmap)
{
	wetuwn 0;
}
#endif

#endif  /* _ASM_AWCH_CPU_H */
