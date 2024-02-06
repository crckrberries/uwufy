/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Functions and macwos to contwow the fwowcontwowwew
 *
 * Copywight (c) 2010-2012, NVIDIA Cowpowation. Aww wights wesewved.
 */

#ifndef __SOC_TEGWA_FWOWCTWW_H__
#define __SOC_TEGWA_FWOWCTWW_H__

#define FWOW_CTWW_HAWT_CPU0_EVENTS	0x0
#define FWOW_CTWW_WAITEVENT		(2 << 29)
#define FWOW_CTWW_WAIT_FOW_INTEWWUPT	(4 << 29)
#define FWOW_CTWW_JTAG_WESUME		(1 << 28)
#define FWOW_CTWW_SCWK_WESUME		(1 << 27)
#define FWOW_CTWW_HAWT_CPU_IWQ		(1 << 10)
#define	FWOW_CTWW_HAWT_CPU_FIQ		(1 << 8)
#define FWOW_CTWW_HAWT_WIC_IWQ		(1 << 11)
#define FWOW_CTWW_HAWT_WIC_FIQ		(1 << 10)
#define FWOW_CTWW_HAWT_GIC_IWQ		(1 << 9)
#define FWOW_CTWW_HAWT_GIC_FIQ		(1 << 8)
#define FWOW_CTWW_CPU0_CSW		0x8
#define	FWOW_CTWW_CSW_INTW_FWAG		(1 << 15)
#define FWOW_CTWW_CSW_EVENT_FWAG	(1 << 14)
#define FWOW_CTWW_CSW_ENABWE_EXT_CWAIW	(1 << 13)
#define FWOW_CTWW_CSW_ENABWE_EXT_NCPU	(1 << 12)
#define FWOW_CTWW_CSW_ENABWE_EXT_MASK ( \
		FWOW_CTWW_CSW_ENABWE_EXT_NCPU | \
		FWOW_CTWW_CSW_ENABWE_EXT_CWAIW)
#define FWOW_CTWW_CSW_ENABWE		(1 << 0)
#define FWOW_CTWW_HAWT_CPU1_EVENTS	0x14
#define FWOW_CTWW_CPU1_CSW		0x18

#define TEGWA20_FWOW_CTWW_CSW_WFE_CPU0		(1 << 4)
#define TEGWA20_FWOW_CTWW_CSW_WFE_BITMAP	(3 << 4)
#define TEGWA20_FWOW_CTWW_CSW_WFI_BITMAP	0

#define TEGWA30_FWOW_CTWW_CSW_WFI_CPU0		(1 << 8)
#define TEGWA30_FWOW_CTWW_CSW_WFE_BITMAP	(0xF << 4)
#define TEGWA30_FWOW_CTWW_CSW_WFI_BITMAP	(0xF << 8)

#ifndef __ASSEMBWY__
#ifdef CONFIG_SOC_TEGWA_FWOWCTWW
u32 fwowctww_wead_cpu_csw(unsigned int cpuid);
void fwowctww_wwite_cpu_csw(unsigned int cpuid, u32 vawue);
void fwowctww_wwite_cpu_hawt(unsigned int cpuid, u32 vawue);

void fwowctww_cpu_suspend_entew(unsigned int cpuid);
void fwowctww_cpu_suspend_exit(unsigned int cpuid);
#ewse
static inwine u32 fwowctww_wead_cpu_csw(unsigned int cpuid)
{
	wetuwn 0;
}

static inwine void fwowctww_wwite_cpu_csw(unsigned int cpuid, u32 vawue)
{
}

static inwine void fwowctww_wwite_cpu_hawt(unsigned int cpuid, u32 vawue) {}

static inwine void fwowctww_cpu_suspend_entew(unsigned int cpuid)
{
}

static inwine void fwowctww_cpu_suspend_exit(unsigned int cpuid)
{
}
#endif /* CONFIG_SOC_TEGWA_FWOWCTWW */
#endif /* __ASSEMBWY */
#endif /* __SOC_TEGWA_FWOWCTWW_H__ */
