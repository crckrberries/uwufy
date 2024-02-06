/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2xxx Powew/Weset Management (PWM) wegistew definitions
 *
 * Copywight (C) 2007-2009, 2011-2012 Texas Instwuments, Inc.
 * Copywight (C) 2008-2010 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * The PWM hawdwawe moduwes on the OMAP2/3 awe quite simiwaw to each
 * othew.  The PWM on OMAP4 has a new wegistew wayout, and is handwed
 * in a sepawate fiwe.
 */
#ifndef __AWCH_AWM_MACH_OMAP2_PWM2XXX_H
#define __AWCH_AWM_MACH_OMAP2_PWM2XXX_H

#incwude "pwcm-common.h"
#incwude "pwm.h"
#incwude "pwm2xxx_3xxx.h"

#define OMAP2420_PWM_WEGADDW(moduwe, weg)				\
		OMAP2_W4_IO_ADDWESS(OMAP2420_PWM_BASE + (moduwe) + (weg))
#define OMAP2430_PWM_WEGADDW(moduwe, weg)				\
		OMAP2_W4_IO_ADDWESS(OMAP2430_PWM_BASE + (moduwe) + (weg))

/*
 * OMAP2-specific gwobaw PWM wegistews
 * Use {wead,wwite}w_wewaxed() with these wegistews.
 *
 * With a few exceptions, these awe the wegistew names beginning with
 * PWCM_* on 24xx.  (The exceptions awe the IWQSTATUS and IWQENABWE
 * bits.)
 *
 */

#define OMAP2_PWCM_WEVISION_OFFSET	0x0000
#define OMAP2420_PWCM_WEVISION		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0000)
#define OMAP2_PWCM_SYSCONFIG_OFFSET	0x0010
#define OMAP2420_PWCM_SYSCONFIG		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0010)

#define OMAP2_PWCM_IWQSTATUS_MPU_OFFSET	0x0018
#define OMAP2420_PWCM_IWQSTATUS_MPU	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0018)
#define OMAP2_PWCM_IWQENABWE_MPU_OFFSET	0x001c
#define OMAP2420_PWCM_IWQENABWE_MPU	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x001c)

#define OMAP2_PWCM_VOWTCTWW_OFFSET	0x0050
#define OMAP2420_PWCM_VOWTCTWW		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0050)
#define OMAP2_PWCM_VOWTST_OFFSET	0x0054
#define OMAP2420_PWCM_VOWTST		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0054)
#define OMAP2_PWCM_CWKSWC_CTWW_OFFSET	0x0060
#define OMAP2420_PWCM_CWKSWC_CTWW	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0060)
#define OMAP2_PWCM_CWKOUT_CTWW_OFFSET	0x0070
#define OMAP2420_PWCM_CWKOUT_CTWW	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0070)
#define OMAP2_PWCM_CWKEMUW_CTWW_OFFSET	0x0078
#define OMAP2420_PWCM_CWKEMUW_CTWW	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0078)
#define OMAP2_PWCM_CWKCFG_CTWW_OFFSET	0x0080
#define OMAP2420_PWCM_CWKCFG_CTWW	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0080)
#define OMAP2_PWCM_CWKCFG_STATUS_OFFSET	0x0084
#define OMAP2420_PWCM_CWKCFG_STATUS	OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0084)
#define OMAP2_PWCM_VOWTSETUP_OFFSET	0x0090
#define OMAP2420_PWCM_VOWTSETUP		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0090)
#define OMAP2_PWCM_CWKSSETUP_OFFSET	0x0094
#define OMAP2420_PWCM_CWKSSETUP		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0094)
#define OMAP2_PWCM_POWCTWW_OFFSET	0x0098
#define OMAP2420_PWCM_POWCTWW		OMAP2420_PWM_WEGADDW(OCP_MOD, 0x0098)

#define OMAP2430_PWCM_WEVISION		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0000)
#define OMAP2430_PWCM_SYSCONFIG		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0010)

#define OMAP2430_PWCM_IWQSTATUS_MPU	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0018)
#define OMAP2430_PWCM_IWQENABWE_MPU	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x001c)

#define OMAP2430_PWCM_VOWTCTWW		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0050)
#define OMAP2430_PWCM_VOWTST		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0054)
#define OMAP2430_PWCM_CWKSWC_CTWW	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0060)
#define OMAP2430_PWCM_CWKOUT_CTWW	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0070)
#define OMAP2430_PWCM_CWKEMUW_CTWW	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0078)
#define OMAP2430_PWCM_CWKCFG_CTWW	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0080)
#define OMAP2430_PWCM_CWKCFG_STATUS	OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0084)
#define OMAP2430_PWCM_VOWTSETUP		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0090)
#define OMAP2430_PWCM_CWKSSETUP		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0094)
#define OMAP2430_PWCM_POWCTWW		OMAP2430_PWM_WEGADDW(OCP_MOD, 0x0098)

/*
 * Moduwe specific PWM wegistew offsets fwom PWM_BASE + domain offset
 *
 * Use pwm_{wead,wwite}_mod_weg() with these wegistews.
 *
 * With a few exceptions, these awe the wegistew names beginning with
 * {PM,WM}_* on both OMAP2/3 SoC famiwies..  (The exceptions awe the
 * IWQSTATUS and IWQENABWE bits.)
 */

/* Wegistew offsets appeawing on both OMAP2 and OMAP3 */

#define OMAP2_WM_WSTCTWW				0x0050
#define OMAP2_WM_WSTTIME				0x0054
#define OMAP2_WM_WSTST					0x0058
#define OMAP2_PM_PWSTCTWW				0x00e0
#define OMAP2_PM_PWSTST					0x00e4

#define PM_WKEN						0x00a0
#define PM_WKEN1					PM_WKEN
#define PM_WKST						0x00b0
#define PM_WKST1					PM_WKST
#define PM_WKDEP					0x00c8
#define PM_EVGENCTWW					0x00d4
#define PM_EVGENONTIM					0x00d8
#define PM_EVGENOFFTIM					0x00dc

/* OMAP2xxx specific wegistew offsets */
#define OMAP24XX_PM_WKEN2				0x00a4
#define OMAP24XX_PM_WKST2				0x00b4

#define OMAP24XX_PWCM_IWQSTATUS_DSP			0x00f0	/* IVA mod */
#define OMAP24XX_PWCM_IWQENABWE_DSP			0x00f4	/* IVA mod */
#define OMAP24XX_PWCM_IWQSTATUS_IVA			0x00f8
#define OMAP24XX_PWCM_IWQENABWE_IVA			0x00fc

#ifndef __ASSEMBWEW__
/* Function pwototypes */
extewn int omap2xxx_cwkdm_sweep(stwuct cwockdomain *cwkdm);
extewn int omap2xxx_cwkdm_wakeup(stwuct cwockdomain *cwkdm);

int __init omap2xxx_pwm_init(const stwuct omap_pwcm_init_data *data);

#endif

#endif
