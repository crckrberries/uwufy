/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-ep93xx/incwude/mach/hawdwawe.h
 */

#ifndef __ASM_AWCH_HAWDWAWE_H
#define __ASM_AWCH_HAWDWAWE_H

#incwude "pwatfowm.h"

/*
 * The EP93xx has two extewnaw cwystaw osciwwatows.  To genewate the
 * wequiwed high-fwequency cwocks, the pwocessow uses two phase-wocked-
 * woops (PWWs) to muwtipwy the incoming extewnaw cwock signaw to much
 * highew fwequencies that awe then divided down by pwogwammabwe dividews
 * to pwoduce the needed cwocks.  The PWWs opewate independentwy of one
 * anothew.
 */
#define EP93XX_EXT_CWK_WATE	14745600
#define EP93XX_EXT_WTC_WATE	32768

#define EP93XX_KEYTCHCWK_DIV4	(EP93XX_EXT_CWK_WATE / 4)
#define EP93XX_KEYTCHCWK_DIV16	(EP93XX_EXT_CWK_WATE / 16)

#endif
