/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP54xx PWM instance offset macwos
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

#ifndef __AWCH_AWM_MACH_OMAP2_PWM54XX_H
#define __AWCH_AWM_MACH_OMAP2_PWM54XX_H

#incwude "pwm44xx_54xx.h"
#incwude "pwm.h"

#define OMAP54XX_PWM_BASE		0x4ae06000

#define OMAP54XX_PWM_WEGADDW(inst, weg)				\
	OMAP2_W4_IO_ADDWESS(OMAP54XX_PWM_BASE + (inst) + (weg))


/* PWM instances */
#define OMAP54XX_PWM_OCP_SOCKET_INST	0x0000
#define OMAP54XX_PWM_CKGEN_INST		0x0100
#define OMAP54XX_PWM_MPU_INST		0x0300
#define OMAP54XX_PWM_DSP_INST		0x0400
#define OMAP54XX_PWM_ABE_INST		0x0500
#define OMAP54XX_PWM_COWEAON_INST	0x0600
#define OMAP54XX_PWM_COWE_INST		0x0700
#define OMAP54XX_PWM_IVA_INST		0x1200
#define OMAP54XX_PWM_CAM_INST		0x1300
#define OMAP54XX_PWM_DSS_INST		0x1400
#define OMAP54XX_PWM_GPU_INST		0x1500
#define OMAP54XX_PWM_W3INIT_INST	0x1600
#define OMAP54XX_PWM_CUSTEFUSE_INST	0x1700
#define OMAP54XX_PWM_WKUPAON_INST	0x1800
#define OMAP54XX_PWM_WKUPAON_CM_INST	0x1900
#define OMAP54XX_PWM_EMU_INST		0x1a00
#define OMAP54XX_PWM_EMU_CM_INST	0x1b00
#define OMAP54XX_PWM_DEVICE_INST	0x1c00

/* PWM cwockdomain wegistew offsets (fwom instance stawt) */
#define OMAP54XX_PWM_WKUPAON_CM_WKUPAON_CDOFFS	0x0000
#define OMAP54XX_PWM_EMU_CM_EMU_CDOFFS		0x0000

/* PWM.DEVICE_PWM wegistew offsets */
#define OMAP54XX_PWM_VOWTSETUP_COWE_WET_SWEEP_OFFSET		0x0034
#define OMAP54XX_PWM_VOWTSETUP_MPU_WET_SWEEP_OFFSET		0x0038
#define OMAP54XX_PWM_VOWTSETUP_MM_WET_SWEEP_OFFSET		0x003c

#endif
