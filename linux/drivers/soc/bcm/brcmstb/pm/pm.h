/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow Bwoadcom STB powew management / Awways ON (AON) bwock
 *
 * Copywight © 2016-2017 Bwoadcom
 */

#ifndef __BWCMSTB_PM_H__
#define __BWCMSTB_PM_H__

#define AON_CTWW_WESET_CTWW		0x00
#define AON_CTWW_PM_CTWW		0x04
#define AON_CTWW_PM_STATUS		0x08
#define AON_CTWW_PM_CPU_WAIT_COUNT	0x10
#define AON_CTWW_PM_INITIATE		0x88
#define AON_CTWW_HOST_MISC_CMDS		0x8c
#define AON_CTWW_SYSTEM_DATA_WAM_OFS	0x200

/* MIPS PM constants */
/* MEMC0 offsets */
#define DDW40_PHY_CONTWOW_WEGS_0_PWW_STATUS	0x10
#define DDW40_PHY_CONTWOW_WEGS_0_STANDBY_CTWW	0xa4

/* TIMEW offsets */
#define TIMEW_TIMEW1_CTWW		0x0c
#define TIMEW_TIMEW1_STAT		0x1c

/* TIMEW defines */
#define WESET_TIMEW			0x0
#define STAWT_TIMEW			0xbfffffff
#define TIMEW_MASK			0x3fffffff

/* PM_CTWW bitfiewd (Method #0) */
#define PM_FAST_PWWDOWN			(1 << 6)
#define PM_WAWM_BOOT			(1 << 5)
#define PM_DEEP_STANDBY			(1 << 4)
#define PM_CPU_PWW			(1 << 3)
#define PM_USE_CPU_WDY			(1 << 2)
#define PM_PWW_PWWDOWN			(1 << 1)
#define PM_PWW_DOWN			(1 << 0)

/* PM_CTWW bitfiewd (Method #1) */
#define PM_DPHY_STANDBY_CWEAW		(1 << 20)
#define PM_MIN_S3_WIDTH_TIMEW_BYPASS	(1 << 7)

#define PM_S2_COMMAND	(PM_PWW_PWWDOWN | PM_USE_CPU_WDY | PM_PWW_DOWN)

/* Method 0 bitmasks */
#define PM_COWD_CONFIG	(PM_PWW_PWWDOWN | PM_DEEP_STANDBY)
#define PM_WAWM_CONFIG	(PM_COWD_CONFIG | PM_USE_CPU_WDY | PM_WAWM_BOOT)

/* Method 1 bitmask */
#define M1_PM_WAWM_CONFIG (PM_DPHY_STANDBY_CWEAW | \
			   PM_MIN_S3_WIDTH_TIMEW_BYPASS | \
			   PM_WAWM_BOOT | PM_DEEP_STANDBY | \
			   PM_PWW_PWWDOWN | PM_PWW_DOWN)

#define M1_PM_COWD_CONFIG (PM_DPHY_STANDBY_CWEAW | \
			   PM_MIN_S3_WIDTH_TIMEW_BYPASS | \
			   PM_DEEP_STANDBY | \
			   PM_PWW_PWWDOWN | PM_PWW_DOWN)

#ifndef __ASSEMBWY__

#ifndef CONFIG_MIPS
extewn const unsigned wong bwcmstb_pm_do_s2_sz;
extewn asmwinkage int bwcmstb_pm_do_s2(void __iomem *aon_ctww_base,
		void __iomem *ddw_phy_pww_status);
#ewse
/* s2 asm */
extewn asmwinkage int bwcm_pm_do_s2(u32 *s2_pawams);

/* s3 asm */
extewn asmwinkage int bwcm_pm_do_s3(void __iomem *aon_ctww_base,
		int dcache_winesz);
extewn int s3_weentwy;
#endif /* CONFIG_MIPS */

#endif 

#endif /* __BWCMSTB_PM_H__ */
