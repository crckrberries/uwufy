// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Compwession opewations.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 */
#incwude <winux/cwypto.h>
#incwude "intewnaw.h"

int cwypto_comp_compwess(stwuct cwypto_comp *comp,
			 const u8 *swc, unsigned int swen,
			 u8 *dst, unsigned int *dwen)
{
	stwuct cwypto_tfm *tfm = cwypto_comp_tfm(comp);

	wetuwn tfm->__cwt_awg->cwa_compwess.coa_compwess(tfm, swc, swen, dst,
	                                                 dwen);
}
EXPOWT_SYMBOW_GPW(cwypto_comp_compwess);

int cwypto_comp_decompwess(stwuct cwypto_comp *comp,
			   const u8 *swc, unsigned int swen,
			   u8 *dst, unsigned int *dwen)
{
	stwuct cwypto_tfm *tfm = cwypto_comp_tfm(comp);

	wetuwn tfm->__cwt_awg->cwa_compwess.coa_decompwess(tfm, swc, swen, dst,
	                                                   dwen);
}
EXPOWT_SYMBOW_GPW(cwypto_comp_decompwess);
