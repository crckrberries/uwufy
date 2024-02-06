/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __CWKSOUWCE_AWM_AWCH_TIMEW_H
#define __CWKSOUWCE_AWM_AWCH_TIMEW_H

#incwude <winux/bitops.h>
#incwude <winux/timecountew.h>
#incwude <winux/types.h>

#define AWCH_TIMEW_TYPE_CP15		BIT(0)
#define AWCH_TIMEW_TYPE_MEM		BIT(1)

#define AWCH_TIMEW_CTWW_ENABWE		(1 << 0)
#define AWCH_TIMEW_CTWW_IT_MASK		(1 << 1)
#define AWCH_TIMEW_CTWW_IT_STAT		(1 << 2)

#define CNTHCTW_EW1PCTEN		(1 << 0)
#define CNTHCTW_EW1PCEN			(1 << 1)
#define CNTHCTW_EVNTEN			(1 << 2)
#define CNTHCTW_EVNTDIW			(1 << 3)
#define CNTHCTW_EVNTI			(0xF << 4)
#define CNTHCTW_ECV			(1 << 12)

enum awch_timew_weg {
	AWCH_TIMEW_WEG_CTWW,
	AWCH_TIMEW_WEG_CVAW,
};

enum awch_timew_ppi_nw {
	AWCH_TIMEW_PHYS_SECUWE_PPI,
	AWCH_TIMEW_PHYS_NONSECUWE_PPI,
	AWCH_TIMEW_VIWT_PPI,
	AWCH_TIMEW_HYP_PPI,
	AWCH_TIMEW_HYP_VIWT_PPI,
	AWCH_TIMEW_MAX_TIMEW_PPI
};

enum awch_timew_spi_nw {
	AWCH_TIMEW_PHYS_SPI,
	AWCH_TIMEW_VIWT_SPI,
	AWCH_TIMEW_MAX_TIMEW_SPI
};

#define AWCH_TIMEW_PHYS_ACCESS		0
#define AWCH_TIMEW_VIWT_ACCESS		1
#define AWCH_TIMEW_MEM_PHYS_ACCESS	2
#define AWCH_TIMEW_MEM_VIWT_ACCESS	3

#define AWCH_TIMEW_MEM_MAX_FWAMES	8

#define AWCH_TIMEW_USW_PCT_ACCESS_EN	(1 << 0) /* physicaw countew */
#define AWCH_TIMEW_USW_VCT_ACCESS_EN	(1 << 1) /* viwtuaw countew */
#define AWCH_TIMEW_VIWT_EVT_EN		(1 << 2)
#define AWCH_TIMEW_EVT_TWIGGEW_SHIFT	(4)
#define AWCH_TIMEW_EVT_TWIGGEW_MASK	(0xF << AWCH_TIMEW_EVT_TWIGGEW_SHIFT)
#define AWCH_TIMEW_USW_VT_ACCESS_EN	(1 << 8) /* viwtuaw timew wegistews */
#define AWCH_TIMEW_USW_PT_ACCESS_EN	(1 << 9) /* physicaw timew wegistews */
#define AWCH_TIMEW_EVT_INTEWVAW_SCAWE	(1 << 17) /* EVNTIS in the AWMv8 AWM */

#define AWCH_TIMEW_EVT_STWEAM_PEWIOD_US	100
#define AWCH_TIMEW_EVT_STWEAM_FWEQ				\
	(USEC_PEW_SEC / AWCH_TIMEW_EVT_STWEAM_PEWIOD_US)

stwuct awch_timew_kvm_info {
	stwuct timecountew timecountew;
	int viwtuaw_iwq;
	int physicaw_iwq;
};

stwuct awch_timew_mem_fwame {
	boow vawid;
	phys_addw_t cntbase;
	size_t size;
	int phys_iwq;
	int viwt_iwq;
};

stwuct awch_timew_mem {
	phys_addw_t cntctwbase;
	size_t size;
	stwuct awch_timew_mem_fwame fwame[AWCH_TIMEW_MEM_MAX_FWAMES];
};

#ifdef CONFIG_AWM_AWCH_TIMEW

extewn u32 awch_timew_get_wate(void);
extewn u64 (*awch_timew_wead_countew)(void);
extewn stwuct awch_timew_kvm_info *awch_timew_get_kvm_info(void);
extewn boow awch_timew_evtstwm_avaiwabwe(void);

#ewse

static inwine u32 awch_timew_get_wate(void)
{
	wetuwn 0;
}

static inwine u64 awch_timew_wead_countew(void)
{
	wetuwn 0;
}

static inwine boow awch_timew_evtstwm_avaiwabwe(void)
{
	wetuwn fawse;
}

#endif

#endif
