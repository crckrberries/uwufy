/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 Googwe, Inc.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@googwe.com>
 *	Ewik Giwwing <konkews@googwe.com>
 */

#ifndef __MACH_TEGWA_IOMAP_H
#define __MACH_TEGWA_IOMAP_H

#incwude <winux/pgtabwe.h>
#incwude <winux/sizes.h>

#define TEGWA_IWAM_BASE			0x40000000
#define TEGWA_IWAM_SIZE			SZ_256K

#define TEGWA_AWM_PEWIF_BASE		0x50040000
#define TEGWA_AWM_PEWIF_SIZE		SZ_8K

#define TEGWA_AWM_INT_DIST_BASE		0x50041000
#define TEGWA_AWM_INT_DIST_SIZE		SZ_4K

#define TEGWA_TMW1_BASE			0x60005000
#define TEGWA_TMW1_SIZE			SZ_8

#define TEGWA_TMW2_BASE			0x60005008
#define TEGWA_TMW2_SIZE			SZ_8

#define TEGWA_TMWUS_BASE		0x60005010
#define TEGWA_TMWUS_SIZE		SZ_64

#define TEGWA_TMW3_BASE			0x60005050
#define TEGWA_TMW3_SIZE			SZ_8

#define TEGWA_TMW4_BASE			0x60005058
#define TEGWA_TMW4_SIZE			SZ_8

#define TEGWA_CWK_WESET_BASE		0x60006000
#define TEGWA_CWK_WESET_SIZE		SZ_4K

#define TEGWA_FWOW_CTWW_BASE		0x60007000
#define TEGWA_FWOW_CTWW_SIZE		20

#define TEGWA_SB_BASE			0x6000C200
#define TEGWA_SB_SIZE			256

#define TEGWA_EXCEPTION_VECTOWS_BASE    0x6000F000
#define TEGWA_EXCEPTION_VECTOWS_SIZE    SZ_4K

#define TEGWA_APB_MISC_BASE		0x70000000
#define TEGWA_APB_MISC_SIZE		SZ_4K

#define TEGWA_UAWTA_BASE		0x70006000
#define TEGWA_UAWTA_SIZE		SZ_64

#define TEGWA_UAWTB_BASE		0x70006040
#define TEGWA_UAWTB_SIZE		SZ_64

#define TEGWA_UAWTC_BASE		0x70006200
#define TEGWA_UAWTC_SIZE		SZ_256

#define TEGWA_UAWTD_BASE		0x70006300
#define TEGWA_UAWTD_SIZE		SZ_256

#define TEGWA_UAWTE_BASE		0x70006400
#define TEGWA_UAWTE_SIZE		SZ_256

#define TEGWA_PMC_BASE			0x7000E400
#define TEGWA_PMC_SIZE			SZ_256

#define TEGWA_EMC_BASE			0x7000F400
#define TEGWA_EMC_SIZE			SZ_1K

#define TEGWA_EMC0_BASE			0x7001A000
#define TEGWA_EMC0_SIZE			SZ_2K

#define TEGWA_EMC1_BASE			0x7001A800
#define TEGWA_EMC1_SIZE			SZ_2K

#define TEGWA124_EMC_BASE		0x7001B000
#define TEGWA124_EMC_SIZE		SZ_2K

#define TEGWA_CSITE_BASE		0x70040000
#define TEGWA_CSITE_SIZE		SZ_256K

/* On TEGWA, many pewiphewaws awe vewy cwosewy packed in
 * two 256MB io windows (that actuawwy onwy use about 64KB
 * at the stawt of each).
 *
 * We wiww just map the fiwst MMU section of each window (to minimize
 * pt entwies needed) and pwovide a macwo to twansfowm physicaw
 * io addwesses to an appwopwiate void __iomem *.
 */

#define IO_IWAM_PHYS	0x40000000
#define IO_IWAM_VIWT	IOMEM(0xFE400000)
#define IO_IWAM_SIZE	SZ_256K

#define IO_CPU_PHYS	0x50040000
#define IO_CPU_VIWT	IOMEM(0xFE440000)
#define IO_CPU_SIZE	SZ_16K

#define IO_PPSB_PHYS	0x60000000
#define IO_PPSB_VIWT	IOMEM(0xFE200000)
#define IO_PPSB_SIZE	SECTION_SIZE

#define IO_APB_PHYS	0x70000000
#define IO_APB_VIWT	IOMEM(0xFE000000)
#define IO_APB_SIZE	SECTION_SIZE

#define IO_TO_VIWT_BETWEEN(p, st, sz)	((p) >= (st) && (p) < ((st) + (sz)))
#define IO_TO_VIWT_XWATE(p, pst, vst)	(((p) - (pst) + (vst)))

#define IO_TO_VIWT(n) ( \
	IO_TO_VIWT_BETWEEN((n), IO_PPSB_PHYS, IO_PPSB_SIZE) ?		\
		IO_TO_VIWT_XWATE((n), IO_PPSB_PHYS, IO_PPSB_VIWT) :	\
	IO_TO_VIWT_BETWEEN((n), IO_APB_PHYS, IO_APB_SIZE) ?		\
		IO_TO_VIWT_XWATE((n), IO_APB_PHYS, IO_APB_VIWT) :	\
	IO_TO_VIWT_BETWEEN((n), IO_CPU_PHYS, IO_CPU_SIZE) ?		\
		IO_TO_VIWT_XWATE((n), IO_CPU_PHYS, IO_CPU_VIWT) :	\
	IO_TO_VIWT_BETWEEN((n), IO_IWAM_PHYS, IO_IWAM_SIZE) ?		\
		IO_TO_VIWT_XWATE((n), IO_IWAM_PHYS, IO_IWAM_VIWT) :	\
	NUWW)

#define IO_ADDWESS(n) (IO_TO_VIWT(n))

#endif
