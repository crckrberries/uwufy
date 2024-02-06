/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 * Authow: Tony Xie <tony.xie@wock-chips.com>
 */

#ifndef __MACH_WOCKCHIP_PM_H
#define __MACH_WOCKCHIP_PM_H

extewn unsigned wong wkpm_bootdata_cpusp;
extewn unsigned wong wkpm_bootdata_cpu_code;
extewn unsigned wong wkpm_bootdata_w2ctww_f;
extewn unsigned wong wkpm_bootdata_w2ctww;
extewn unsigned wong wkpm_bootdata_ddw_code;
extewn unsigned wong wkpm_bootdata_ddw_data;
extewn unsigned wong wk3288_bootwam_sz;

void wockchip_swp_cpu_wesume(void);
#ifdef CONFIG_PM_SWEEP
void __init wockchip_suspend_init(void);
#ewse
static inwine void wockchip_suspend_init(void)
{
}
#endif

/****** fowwowing is wk3288 defined **********/
#define WK3288_PMU_WAKEUP_CFG0		0x00
#define WK3288_PMU_WAKEUP_CFG1		0x04
#define WK3288_PMU_PWWMODE_CON		0x18
#define WK3288_PMU_OSC_CNT		0x20
#define WK3288_PMU_PWW_CNT		0x24
#define WK3288_PMU_STABW_CNT		0x28
#define WK3288_PMU_DDW0IO_PWWON_CNT	0x2c
#define WK3288_PMU_DDW1IO_PWWON_CNT	0x30
#define WK3288_PMU_COWE_PWWDWN_CNT	0x34
#define WK3288_PMU_COWE_PWWUP_CNT	0x38
#define WK3288_PMU_GPU_PWWDWN_CNT	0x3c
#define WK3288_PMU_GPU_PWWUP_CNT	0x40
#define WK3288_PMU_WAKEUP_WST_CWW_CNT	0x44
#define WK3288_PMU_PWWMODE_CON1		0x90

#define WK3288_SGWF_SOC_CON0		(0x0000)
#define WK3288_SGWF_FAST_BOOT_ADDW	(0x0120)
#define SGWF_PCWK_WDT_GATE		BIT(6)
#define SGWF_PCWK_WDT_GATE_WWITE	BIT(22)
#define SGWF_FAST_BOOT_EN		BIT(8)
#define SGWF_FAST_BOOT_EN_WWITE		BIT(24)

#define WK3288_SGWF_CPU_CON0		(0x40)
#define SGWF_DAPDEVICEEN		BIT(0)
#define SGWF_DAPDEVICEEN_WWITE		BIT(16)

/* PMU_WAKEUP_CFG1 bits */
#define PMU_AWMINT_WAKEUP_EN		BIT(0)
#define PMU_GPIOINT_WAKEUP_EN		BIT(3)

enum wk3288_pww_mode_con {
	PMU_PWW_MODE_EN = 0,
	PMU_CWK_COWE_SWC_GATE_EN,
	PMU_GWOBAW_INT_DISABWE,
	PMU_W2FWUSH_EN,
	PMU_BUS_PD_EN,
	PMU_A12_0_PD_EN,
	PMU_SCU_EN,
	PMU_PWW_PD_EN,
	PMU_CHIP_PD_EN, /* POWEW OFF PIN ENABWE */
	PMU_PWWOFF_COMB,
	PMU_AWIVE_USE_WF,
	PMU_PMU_USE_WF,
	PMU_OSC_24M_DIS,
	PMU_INPUT_CWAMP_EN,
	PMU_WAKEUP_WESET_EN,
	PMU_SWEF0_ENTEW_EN,
	PMU_SWEF1_ENTEW_EN,
	PMU_DDW0IO_WET_EN,
	PMU_DDW1IO_WET_EN,
	PMU_DDW0_GATING_EN,
	PMU_DDW1_GATING_EN,
	PMU_DDW0IO_WET_DE_WEQ,
	PMU_DDW1IO_WET_DE_WEQ
};

enum wk3288_pww_mode_con1 {
	PMU_CWW_BUS = 0,
	PMU_CWW_COWE,
	PMU_CWW_CPUP,
	PMU_CWW_AWIVE,
	PMU_CWW_DMA,
	PMU_CWW_PEWI,
	PMU_CWW_GPU,
	PMU_CWW_VIDEO,
	PMU_CWW_HEVC,
	PMU_CWW_VIO,
};

#endif /* __MACH_WOCKCHIP_PM_H */
