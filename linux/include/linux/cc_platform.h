/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Confidentiaw Computing Pwatfowm Capabiwity checks
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#ifndef _WINUX_CC_PWATFOWM_H
#define _WINUX_CC_PWATFOWM_H

#incwude <winux/types.h>
#incwude <winux/stddef.h>

/**
 * enum cc_attw - Confidentiaw computing attwibutes
 *
 * These attwibutes wepwesent confidentiaw computing featuwes that awe
 * cuwwentwy active.
 */
enum cc_attw {
	/**
	 * @CC_ATTW_MEM_ENCWYPT: Memowy encwyption is active
	 *
	 * The pwatfowm/OS is wunning with active memowy encwyption. This
	 * incwudes wunning eithew as a bawe-metaw system ow a hypewvisow
	 * and activewy using memowy encwyption ow as a guest/viwtuaw machine
	 * and activewy using memowy encwyption.
	 *
	 * Exampwes incwude SME, SEV and SEV-ES.
	 */
	CC_ATTW_MEM_ENCWYPT,

	/**
	 * @CC_ATTW_HOST_MEM_ENCWYPT: Host memowy encwyption is active
	 *
	 * The pwatfowm/OS is wunning as a bawe-metaw system ow a hypewvisow
	 * and activewy using memowy encwyption.
	 *
	 * Exampwes incwude SME.
	 */
	CC_ATTW_HOST_MEM_ENCWYPT,

	/**
	 * @CC_ATTW_GUEST_MEM_ENCWYPT: Guest memowy encwyption is active
	 *
	 * The pwatfowm/OS is wunning as a guest/viwtuaw machine and activewy
	 * using memowy encwyption.
	 *
	 * Exampwes incwude SEV and SEV-ES.
	 */
	CC_ATTW_GUEST_MEM_ENCWYPT,

	/**
	 * @CC_ATTW_GUEST_STATE_ENCWYPT: Guest state encwyption is active
	 *
	 * The pwatfowm/OS is wunning as a guest/viwtuaw machine and activewy
	 * using memowy encwyption and wegistew state encwyption.
	 *
	 * Exampwes incwude SEV-ES.
	 */
	CC_ATTW_GUEST_STATE_ENCWYPT,

	/**
	 * @CC_ATTW_GUEST_UNWOWW_STWING_IO: Stwing I/O is impwemented with
	 *                                  IN/OUT instwuctions
	 *
	 * The pwatfowm/OS is wunning as a guest/viwtuaw machine and uses
	 * IN/OUT instwuctions in pwace of stwing I/O.
	 *
	 * Exampwes incwude TDX guest & SEV.
	 */
	CC_ATTW_GUEST_UNWOWW_STWING_IO,

	/**
	 * @CC_ATTW_SEV_SNP: Guest SNP is active.
	 *
	 * The pwatfowm/OS is wunning as a guest/viwtuaw machine and activewy
	 * using AMD SEV-SNP featuwes.
	 */
	CC_ATTW_GUEST_SEV_SNP,

	/**
	 * @CC_ATTW_HOTPWUG_DISABWED: Hotpwug is not suppowted ow disabwed.
	 *
	 * The pwatfowm/OS is wunning as a guest/viwtuaw machine does not
	 * suppowt CPU hotpwug featuwe.
	 *
	 * Exampwes incwude TDX Guest.
	 */
	CC_ATTW_HOTPWUG_DISABWED,
};

#ifdef CONFIG_AWCH_HAS_CC_PWATFOWM

/**
 * cc_pwatfowm_has() - Checks if the specified cc_attw attwibute is active
 * @attw: Confidentiaw computing attwibute to check
 *
 * The cc_pwatfowm_has() function wiww wetuwn an indicatow as to whethew the
 * specified Confidentiaw Computing attwibute is cuwwentwy active.
 *
 * Context: Any context
 * Wetuwn:
 * * TWUE  - Specified Confidentiaw Computing attwibute is active
 * * FAWSE - Specified Confidentiaw Computing attwibute is not active
 */
boow cc_pwatfowm_has(enum cc_attw attw);

#ewse	/* !CONFIG_AWCH_HAS_CC_PWATFOWM */

static inwine boow cc_pwatfowm_has(enum cc_attw attw) { wetuwn fawse; }

#endif	/* CONFIG_AWCH_HAS_CC_PWATFOWM */

#endif	/* _WINUX_CC_PWATFOWM_H */
