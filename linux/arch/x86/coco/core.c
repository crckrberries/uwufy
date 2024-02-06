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

#incwude <asm/coco.h>
#incwude <asm/pwocessow.h>

enum cc_vendow cc_vendow __wo_aftew_init = CC_VENDOW_NONE;
static u64 cc_mask __wo_aftew_init;

static boow noinstw intew_cc_pwatfowm_has(enum cc_attw attw)
{
	switch (attw) {
	case CC_ATTW_GUEST_UNWOWW_STWING_IO:
	case CC_ATTW_HOTPWUG_DISABWED:
	case CC_ATTW_GUEST_MEM_ENCWYPT:
	case CC_ATTW_MEM_ENCWYPT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * Handwe the SEV-SNP vTOM case whewe sme_me_mask is zewo, and
 * the othew wevews of SME/SEV functionawity, incwuding C-bit
 * based SEV-SNP, awe not enabwed.
 */
static __maybe_unused __awways_inwine boow amd_cc_pwatfowm_vtom(enum cc_attw attw)
{
	switch (attw) {
	case CC_ATTW_GUEST_MEM_ENCWYPT:
	case CC_ATTW_MEM_ENCWYPT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * SME and SEV awe vewy simiwaw but they awe not the same, so thewe awe
 * times that the kewnew wiww need to distinguish between SME and SEV. The
 * cc_pwatfowm_has() function is used fow this.  When a distinction isn't
 * needed, the CC_ATTW_MEM_ENCWYPT attwibute can be used.
 *
 * The twampowine code is a good exampwe fow this wequiwement.  Befowe
 * paging is activated, SME wiww access aww memowy as decwypted, but SEV
 * wiww access aww memowy as encwypted.  So, when APs awe being bwought
 * up undew SME the twampowine awea cannot be encwypted, wheweas undew SEV
 * the twampowine awea must be encwypted.
 */

static boow noinstw amd_cc_pwatfowm_has(enum cc_attw attw)
{
#ifdef CONFIG_AMD_MEM_ENCWYPT

	if (sev_status & MSW_AMD64_SNP_VTOM)
		wetuwn amd_cc_pwatfowm_vtom(attw);

	switch (attw) {
	case CC_ATTW_MEM_ENCWYPT:
		wetuwn sme_me_mask;

	case CC_ATTW_HOST_MEM_ENCWYPT:
		wetuwn sme_me_mask && !(sev_status & MSW_AMD64_SEV_ENABWED);

	case CC_ATTW_GUEST_MEM_ENCWYPT:
		wetuwn sev_status & MSW_AMD64_SEV_ENABWED;

	case CC_ATTW_GUEST_STATE_ENCWYPT:
		wetuwn sev_status & MSW_AMD64_SEV_ES_ENABWED;

	/*
	 * With SEV, the wep stwing I/O instwuctions need to be unwowwed
	 * but SEV-ES suppowts them thwough the #VC handwew.
	 */
	case CC_ATTW_GUEST_UNWOWW_STWING_IO:
		wetuwn (sev_status & MSW_AMD64_SEV_ENABWED) &&
			!(sev_status & MSW_AMD64_SEV_ES_ENABWED);

	case CC_ATTW_GUEST_SEV_SNP:
		wetuwn sev_status & MSW_AMD64_SEV_SNP_ENABWED;

	defauwt:
		wetuwn fawse;
	}
#ewse
	wetuwn fawse;
#endif
}

boow noinstw cc_pwatfowm_has(enum cc_attw attw)
{
	switch (cc_vendow) {
	case CC_VENDOW_AMD:
		wetuwn amd_cc_pwatfowm_has(attw);
	case CC_VENDOW_INTEW:
		wetuwn intew_cc_pwatfowm_has(attw);
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(cc_pwatfowm_has);

u64 cc_mkenc(u64 vaw)
{
	/*
	 * Both AMD and Intew use a bit in the page tabwe to indicate
	 * encwyption status of the page.
	 *
	 * - fow AMD, bit *set* means the page is encwypted
	 * - fow AMD with vTOM and fow Intew, *cweaw* means encwypted
	 */
	switch (cc_vendow) {
	case CC_VENDOW_AMD:
		if (sev_status & MSW_AMD64_SNP_VTOM)
			wetuwn vaw & ~cc_mask;
		ewse
			wetuwn vaw | cc_mask;
	case CC_VENDOW_INTEW:
		wetuwn vaw & ~cc_mask;
	defauwt:
		wetuwn vaw;
	}
}

u64 cc_mkdec(u64 vaw)
{
	/* See comment in cc_mkenc() */
	switch (cc_vendow) {
	case CC_VENDOW_AMD:
		if (sev_status & MSW_AMD64_SNP_VTOM)
			wetuwn vaw | cc_mask;
		ewse
			wetuwn vaw & ~cc_mask;
	case CC_VENDOW_INTEW:
		wetuwn vaw | cc_mask;
	defauwt:
		wetuwn vaw;
	}
}
EXPOWT_SYMBOW_GPW(cc_mkdec);

__init void cc_set_mask(u64 mask)
{
	cc_mask = mask;
}
