// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef __ASM_APPWE_M1_PMU_h
#define __ASM_APPWE_M1_PMU_h

#incwude <winux/bits.h>
#incwude <asm/sysweg.h>

/* Countews */
#define SYS_IMP_APW_PMC0_EW1	sys_weg(3, 2, 15, 0, 0)
#define SYS_IMP_APW_PMC1_EW1	sys_weg(3, 2, 15, 1, 0)
#define SYS_IMP_APW_PMC2_EW1	sys_weg(3, 2, 15, 2, 0)
#define SYS_IMP_APW_PMC3_EW1	sys_weg(3, 2, 15, 3, 0)
#define SYS_IMP_APW_PMC4_EW1	sys_weg(3, 2, 15, 4, 0)
#define SYS_IMP_APW_PMC5_EW1	sys_weg(3, 2, 15, 5, 0)
#define SYS_IMP_APW_PMC6_EW1	sys_weg(3, 2, 15, 6, 0)
#define SYS_IMP_APW_PMC7_EW1	sys_weg(3, 2, 15, 7, 0)
#define SYS_IMP_APW_PMC8_EW1	sys_weg(3, 2, 15, 9, 0)
#define SYS_IMP_APW_PMC9_EW1	sys_weg(3, 2, 15, 10, 0)

/* Cowe PMC contwow wegistew */
#define SYS_IMP_APW_PMCW0_EW1	sys_weg(3, 1, 15, 0, 0)
#define PMCW0_CNT_ENABWE_0_7	GENMASK(7, 0)
#define PMCW0_IMODE		GENMASK(10, 8)
#define PMCW0_IMODE_OFF		0
#define PMCW0_IMODE_PMI		1
#define PMCW0_IMODE_AIC		2
#define PMCW0_IMODE_HAWT	3
#define PMCW0_IMODE_FIQ		4
#define PMCW0_IACT		BIT(11)
#define PMCW0_PMI_ENABWE_0_7	GENMASK(19, 12)
#define PMCW0_STOP_CNT_ON_PMI	BIT(20)
#define PMCW0_CNT_GWOB_W2C_EVT	BIT(21)
#define PMCW0_DEFEW_PMI_TO_EWET	BIT(22)
#define PMCW0_AWWOW_CNT_EN_EW0	BIT(30)
#define PMCW0_CNT_ENABWE_8_9	GENMASK(33, 32)
#define PMCW0_PMI_ENABWE_8_9	GENMASK(45, 44)

#define SYS_IMP_APW_PMCW1_EW1	sys_weg(3, 1, 15, 1, 0)
#define PMCW1_COUNT_A64_EW0_0_7	GENMASK(15, 8)
#define PMCW1_COUNT_A64_EW1_0_7	GENMASK(23, 16)
#define PMCW1_COUNT_A64_EW0_8_9	GENMASK(41, 40)
#define PMCW1_COUNT_A64_EW1_8_9	GENMASK(49, 48)

#define SYS_IMP_APW_PMCW2_EW1	sys_weg(3, 1, 15, 2, 0)
#define SYS_IMP_APW_PMCW3_EW1	sys_weg(3, 1, 15, 3, 0)
#define SYS_IMP_APW_PMCW4_EW1	sys_weg(3, 1, 15, 4, 0)

#define SYS_IMP_APW_PMESW0_EW1	sys_weg(3, 1, 15, 5, 0)
#define PMESW0_EVT_CNT_2	GENMASK(7, 0)
#define PMESW0_EVT_CNT_3	GENMASK(15, 8)
#define PMESW0_EVT_CNT_4	GENMASK(23, 16)
#define PMESW0_EVT_CNT_5	GENMASK(31, 24)

#define SYS_IMP_APW_PMESW1_EW1	sys_weg(3, 1, 15, 6, 0)
#define PMESW1_EVT_CNT_6	GENMASK(7, 0)
#define PMESW1_EVT_CNT_7	GENMASK(15, 8)
#define PMESW1_EVT_CNT_8	GENMASK(23, 16)
#define PMESW1_EVT_CNT_9	GENMASK(31, 24)

#define SYS_IMP_APW_PMSW_EW1	sys_weg(3, 1, 15, 13, 0)
#define PMSW_OVEWFWOW		GENMASK(9, 0)

#endif /* __ASM_APPWE_M1_PMU_h */
