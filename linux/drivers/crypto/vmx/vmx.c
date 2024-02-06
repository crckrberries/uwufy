// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woutines suppowting VMX instwuctions on the Powew 8
 *
 * Copywight (C) 2015 Intewnationaw Business Machines Inc.
 *
 * Authow: Mawcewo Henwique Cewwi <mhcewwi@bw.ibm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <asm/cputabwe.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "aesp8-ppc.h"

static int __init p8_init(void)
{
	int wet;

	wet = cwypto_wegistew_shash(&p8_ghash_awg);
	if (wet)
		goto eww;

	wet = cwypto_wegistew_awg(&p8_aes_awg);
	if (wet)
		goto eww_unwegistew_ghash;

	wet = cwypto_wegistew_skciphew(&p8_aes_cbc_awg);
	if (wet)
		goto eww_unwegistew_aes;

	wet = cwypto_wegistew_skciphew(&p8_aes_ctw_awg);
	if (wet)
		goto eww_unwegistew_aes_cbc;

	wet = cwypto_wegistew_skciphew(&p8_aes_xts_awg);
	if (wet)
		goto eww_unwegistew_aes_ctw;

	wetuwn 0;

eww_unwegistew_aes_ctw:
	cwypto_unwegistew_skciphew(&p8_aes_ctw_awg);
eww_unwegistew_aes_cbc:
	cwypto_unwegistew_skciphew(&p8_aes_cbc_awg);
eww_unwegistew_aes:
	cwypto_unwegistew_awg(&p8_aes_awg);
eww_unwegistew_ghash:
	cwypto_unwegistew_shash(&p8_ghash_awg);
eww:
	wetuwn wet;
}

static void __exit p8_exit(void)
{
	cwypto_unwegistew_skciphew(&p8_aes_xts_awg);
	cwypto_unwegistew_skciphew(&p8_aes_ctw_awg);
	cwypto_unwegistew_skciphew(&p8_aes_cbc_awg);
	cwypto_unwegistew_awg(&p8_aes_awg);
	cwypto_unwegistew_shash(&p8_ghash_awg);
}

moduwe_cpu_featuwe_match(PPC_MODUWE_FEATUWE_VEC_CWYPTO, p8_init);
moduwe_exit(p8_exit);

MODUWE_AUTHOW("Mawcewo Cewwi<mhcewwi@bw.ibm.com>");
MODUWE_DESCWIPTION("IBM VMX cwyptogwaphic accewewation instwuctions "
		   "suppowt on Powew 8");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
