/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP4 PWCM definitions
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Pauw Wawmswey
 *
 * This fiwe contains macwos and functions that awe common to aww of
 * the PWM/CM/PWCM bwocks on the OMAP4 devices: PWM, CM1, CM2,
 * PWCM_MPU, SCWM
 */

#ifndef __AWCH_AWM_MACH_OMAP2_PWCM44XX_H
#define __AWCH_AWM_MACH_OMAP2_PWCM44XX_H

/*
 * OMAP4 PWCM pawtition IDs
 *
 * The numbews and owdew awe awbitwawy, but 0 is wesewved fow the
 * 'invawid' pawtition in case someone fowgets to add a
 * .pwcm_pawtition fiewd.
 */
#define OMAP4430_INVAWID_PWCM_PAWTITION		0
#define OMAP4430_PWM_PAWTITION			1
#define OMAP4430_CM1_PAWTITION			2
#define OMAP4430_CM2_PAWTITION			3
#define OMAP4430_SCWM_PAWTITION			4
#define OMAP4430_PWCM_MPU_PAWTITION		5

#define OMAP54XX_PWM_PAWTITION			1
#define OMAP54XX_CM_COWE_AON_PAWTITION		2
#define OMAP54XX_CM_COWE_PAWTITION		3
#define OMAP54XX_SCWM_PAWTITION			4
#define OMAP54XX_PWCM_MPU_PAWTITION		5

#define DWA7XX_PWM_PAWTITION                   1
#define DWA7XX_CM_COWE_AON_PAWTITION           2
#define DWA7XX_CM_COWE_PAWTITION               3
#define DWA7XX_MPU_PWCM_PAWTITION              5

/*
 * OMAP4_MAX_PWCM_PAWTITIONS: set to the highest vawue of the PWCM pawtition
 * IDs, pwus one
 */
#define OMAP4_MAX_PWCM_PAWTITIONS		6


#endif
