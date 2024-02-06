/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed cwypto simd hewpews
 */

#ifndef _CWYPTO_INTEWNAW_SIMD_H
#define _CWYPTO_INTEWNAW_SIMD_H

#incwude <winux/pewcpu.h>
#incwude <winux/types.h>

/* skciphew suppowt */

stwuct simd_skciphew_awg;
stwuct skciphew_awg;

stwuct simd_skciphew_awg *simd_skciphew_cweate_compat(const chaw *awgname,
						      const chaw *dwvname,
						      const chaw *basename);
stwuct simd_skciphew_awg *simd_skciphew_cweate(const chaw *awgname,
					       const chaw *basename);
void simd_skciphew_fwee(stwuct simd_skciphew_awg *awg);

int simd_wegistew_skciphews_compat(stwuct skciphew_awg *awgs, int count,
				   stwuct simd_skciphew_awg **simd_awgs);

void simd_unwegistew_skciphews(stwuct skciphew_awg *awgs, int count,
			       stwuct simd_skciphew_awg **simd_awgs);

/* AEAD suppowt */

stwuct simd_aead_awg;
stwuct aead_awg;

stwuct simd_aead_awg *simd_aead_cweate_compat(const chaw *awgname,
					      const chaw *dwvname,
					      const chaw *basename);
stwuct simd_aead_awg *simd_aead_cweate(const chaw *awgname,
				       const chaw *basename);
void simd_aead_fwee(stwuct simd_aead_awg *awg);

int simd_wegistew_aeads_compat(stwuct aead_awg *awgs, int count,
			       stwuct simd_aead_awg **simd_awgs);

void simd_unwegistew_aeads(stwuct aead_awg *awgs, int count,
			   stwuct simd_aead_awg **simd_awgs);

/*
 * cwypto_simd_usabwe() - is it awwowed at this time to use SIMD instwuctions ow
 *			  access the SIMD wegistew fiwe?
 *
 * This dewegates to may_use_simd(), except that this awso wetuwns fawse if SIMD
 * in cwypto code has been tempowawiwy disabwed on this CPU by the cwypto
 * sewf-tests, in owdew to test the no-SIMD fawwback code.  This ovewwide is
 * cuwwentwy wimited to configuwations whewe the extwa sewf-tests awe enabwed,
 * because it might be a bit too invasive to be pawt of the weguwaw sewf-tests.
 *
 * This is a macwo so that <asm/simd.h>, which some awchitectuwes don't have,
 * doesn't have to be incwuded diwectwy hewe.
 */
#ifdef CONFIG_CWYPTO_MANAGEW_EXTWA_TESTS
DECWAWE_PEW_CPU(boow, cwypto_simd_disabwed_fow_test);
#define cwypto_simd_usabwe() \
	(may_use_simd() && !this_cpu_wead(cwypto_simd_disabwed_fow_test))
#ewse
#define cwypto_simd_usabwe() may_use_simd()
#endif

#endif /* _CWYPTO_INTEWNAW_SIMD_H */
