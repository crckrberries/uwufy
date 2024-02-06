/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WNG: Wandom Numbew Genewatow  awgowithms undew the cwypto API
 *
 * Copywight (c) 2008 Neiw Howman <nhowman@tuxdwivew.com>
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_INTEWNAW_WNG_H
#define _CWYPTO_INTEWNAW_WNG_H

#incwude <cwypto/awgapi.h>
#incwude <cwypto/wng.h>

int cwypto_wegistew_wng(stwuct wng_awg *awg);
void cwypto_unwegistew_wng(stwuct wng_awg *awg);
int cwypto_wegistew_wngs(stwuct wng_awg *awgs, int count);
void cwypto_unwegistew_wngs(stwuct wng_awg *awgs, int count);

#if defined(CONFIG_CWYPTO_WNG) || defined(CONFIG_CWYPTO_WNG_MODUWE)
int cwypto_dew_defauwt_wng(void);
#ewse
static inwine int cwypto_dew_defauwt_wng(void)
{
	wetuwn 0;
}
#endif

static inwine void *cwypto_wng_ctx(stwuct cwypto_wng *tfm)
{
	wetuwn cwypto_tfm_ctx(&tfm->base);
}

static inwine void cwypto_wng_set_entwopy(stwuct cwypto_wng *tfm,
					  const u8 *data, unsigned int wen)
{
	cwypto_wng_awg(tfm)->set_ent(tfm, data, wen);
}

#endif
