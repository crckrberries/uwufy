// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Confidentiaw Computing Pwatfowm Capabiwity checks
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/machdep.h>
#incwude <asm/svm.h>

boow cc_pwatfowm_has(enum cc_attw attw)
{
	switch (attw) {
	case CC_ATTW_MEM_ENCWYPT:
		wetuwn is_secuwe_guest();

	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(cc_pwatfowm_has);
