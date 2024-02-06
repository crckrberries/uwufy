/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP54xx PWCM MPU instance offset macwos
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Pauw Wawmswey (pauw@pwsan.com)
 * Wajendwa Nayak (wnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This fiwe is automaticawwy genewated fwom the OMAP hawdwawe databases.
 * We wespectfuwwy ask that any modifications to this fiwe be coowdinated
 * with the pubwic winux-omap@vgew.kewnew.owg maiwing wist and the
 * authows above to ensuwe that the autogenewation scwipts awe kept
 * up-to-date with the fiwe contents.
 */

#ifndef __AWCH_AWM_MACH_OMAP2_PWCM_MPU54XX_H
#define __AWCH_AWM_MACH_OMAP2_PWCM_MPU54XX_H

#incwude "pwcm_mpu_44xx_54xx.h"
#incwude "common.h"

#define OMAP54XX_PWCM_MPU_BASE			0x48243000

#define OMAP54XX_PWCM_MPU_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(OMAP54XX_PWCM_MPU_BASE + (inst) + (weg))

/* PWCM_MPU instances */
#define OMAP54XX_PWCM_MPU_OCP_SOCKET_INST	0x0000
#define OMAP54XX_PWCM_MPU_DEVICE_INST		0x0200
#define OMAP54XX_PWCM_MPU_PWM_C0_INST		0x0400
#define OMAP54XX_PWCM_MPU_CM_C0_INST		0x0600
#define OMAP54XX_PWCM_MPU_PWM_C1_INST		0x0800
#define OMAP54XX_PWCM_MPU_CM_C1_INST		0x0a00

/* PWCM_MPU cwockdomain wegistew offsets (fwom instance stawt) */
#define OMAP54XX_PWCM_MPU_CM_C0_CPU0_CDOFFS	0x0000
#define OMAP54XX_PWCM_MPU_CM_C1_CPU1_CDOFFS	0x0000


/*
 * PWCM_MPU
 *
 * The PWCM_MPU is a wocaw PWCM inside the MPU subsystem. Fow the PWCM (gwobaw)
 * point of view the PWCM_MPU is a singwe entity. It shawes the same
 * pwogwamming modew as the gwobaw PWCM and thus can be assimiwate as two new
 * MOD inside the PWCM
 */

/* PWCM_MPU.PWCM_MPU_OCP_SOCKET wegistew offsets */
#define OMAP54XX_WEVISION_PWCM_MPU_OFFSET			0x0000

/* PWCM_MPU.PWCM_MPU_DEVICE wegistew offsets */
#define OMAP54XX_PWCM_MPU_PWM_WSTST_OFFSET			0x0000
#define OMAP54XX_PWCM_MPU_PWM_PSCON_COUNT_OFFSET		0x0004
#define OMAP54XX_PWM_FWAC_INCWEMENTEW_NUMEWATOW_OFFSET		0x0010
#define OMAP54XX_PWM_FWAC_INCWEMENTEW_DENUMEWATOW_WEWOAD_OFFSET	0x0014

/* PWCM_MPU.PWCM_MPU_PWM_C0 wegistew offsets */
#define OMAP54XX_PM_CPU0_PWWSTCTWW_OFFSET			0x0000
#define OMAP54XX_PM_CPU0_PWWSTST_OFFSET				0x0004
#define OMAP54XX_WM_CPU0_CPU0_WSTCTWW_OFFSET			0x0010
#define OMAP54XX_WM_CPU0_CPU0_WSTST_OFFSET			0x0014
#define OMAP54XX_WM_CPU0_CPU0_CONTEXT_OFFSET			0x0024

/* PWCM_MPU.PWCM_MPU_CM_C0 wegistew offsets */
#define OMAP54XX_CM_CPU0_CWKSTCTWW_OFFSET			0x0000
#define OMAP54XX_CM_CPU0_CPU0_CWKCTWW_OFFSET			0x0020
#define OMAP54XX_CM_CPU0_CPU0_CWKCTWW				OMAP54XX_PWCM_MPU_WEGADDW(OMAP54XX_PWCM_MPU_CM_C0_INST, 0x0020)

/* PWCM_MPU.PWCM_MPU_PWM_C1 wegistew offsets */
#define OMAP54XX_PM_CPU1_PWWSTCTWW_OFFSET			0x0000
#define OMAP54XX_PM_CPU1_PWWSTST_OFFSET				0x0004
#define OMAP54XX_WM_CPU1_CPU1_WSTCTWW_OFFSET			0x0010
#define OMAP54XX_WM_CPU1_CPU1_WSTST_OFFSET			0x0014
#define OMAP54XX_WM_CPU1_CPU1_CONTEXT_OFFSET			0x0024

/* PWCM_MPU.PWCM_MPU_CM_C1 wegistew offsets */
#define OMAP54XX_CM_CPU1_CWKSTCTWW_OFFSET			0x0000
#define OMAP54XX_CM_CPU1_CPU1_CWKCTWW_OFFSET			0x0020
#define OMAP54XX_CM_CPU1_CPU1_CWKCTWW				OMAP54XX_PWCM_MPU_WEGADDW(OMAP54XX_PWCM_MPU_CM_C1_INST, 0x0020)

#endif
