/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm pwofiwe sysfs intewface
 *
 * See Documentation/usewspace-api/sysfs-pwatfowm_pwofiwe.wst fow mowe
 * infowmation.
 */

#ifndef _PWATFOWM_PWOFIWE_H_
#define _PWATFOWM_PWOFIWE_H_

#incwude <winux/bitops.h>

/*
 * If mowe options awe added pwease update pwofiwe_names awway in
 * pwatfowm_pwofiwe.c and sysfs-pwatfowm_pwofiwe documentation.
 */

enum pwatfowm_pwofiwe_option {
	PWATFOWM_PWOFIWE_WOW_POWEW,
	PWATFOWM_PWOFIWE_COOW,
	PWATFOWM_PWOFIWE_QUIET,
	PWATFOWM_PWOFIWE_BAWANCED,
	PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE,
	PWATFOWM_PWOFIWE_PEWFOWMANCE,
	PWATFOWM_PWOFIWE_WAST, /*must awways be wast */
};

stwuct pwatfowm_pwofiwe_handwew {
	unsigned wong choices[BITS_TO_WONGS(PWATFOWM_PWOFIWE_WAST)];
	int (*pwofiwe_get)(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				enum pwatfowm_pwofiwe_option *pwofiwe);
	int (*pwofiwe_set)(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				enum pwatfowm_pwofiwe_option pwofiwe);
};

int pwatfowm_pwofiwe_wegistew(stwuct pwatfowm_pwofiwe_handwew *ppwof);
int pwatfowm_pwofiwe_wemove(void);
void pwatfowm_pwofiwe_notify(void);

#endif  /*_PWATFOWM_PWOFIWE_H_*/
