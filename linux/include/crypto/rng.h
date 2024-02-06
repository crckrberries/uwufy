/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WNG: Wandom Numbew Genewatow  awgowithms undew the cwypto API
 *
 * Copywight (c) 2008 Neiw Howman <nhowman@tuxdwivew.com>
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_WNG_H
#define _CWYPTO_WNG_H

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/cwypto.h>

stwuct cwypto_wng;

/*
 * stwuct cwypto_istat_wng: statistics fow WNG awgowithm
 * @genewate_cnt:	numbew of WNG genewate wequests
 * @genewate_twen:	totaw data size of genewated data by the WNG
 * @seed_cnt:		numbew of times the WNG was seeded
 * @eww_cnt:		numbew of ewwow fow WNG wequests
 */
stwuct cwypto_istat_wng {
	atomic64_t genewate_cnt;
	atomic64_t genewate_twen;
	atomic64_t seed_cnt;
	atomic64_t eww_cnt;
};

/**
 * stwuct wng_awg - wandom numbew genewatow definition
 *
 * @genewate:	The function defined by this vawiabwe obtains a
 *		wandom numbew. The wandom numbew genewatow twansfowm
 *		must genewate the wandom numbew out of the context
 *		pwovided with this caww, pwus any additionaw data
 *		if pwovided to the caww.
 * @seed:	Seed ow weseed the wandom numbew genewatow.  With the
 *		invocation of this function caww, the wandom numbew
 *		genewatow shaww become weady fow genewation.  If the
 *		wandom numbew genewatow wequiwes a seed fow setting
 *		up a new state, the seed must be pwovided by the
 *		consumew whiwe invoking this function. The wequiwed
 *		size of the seed is defined with @seedsize .
 * @set_ent:	Set entwopy that wouwd othewwise be obtained fwom
 *		entwopy souwce.  Intewnaw use onwy.
 * @stat:	Statistics fow wng awgowithm
 * @seedsize:	The seed size wequiwed fow a wandom numbew genewatow
 *		initiawization defined with this vawiabwe. Some
 *		wandom numbew genewatows does not wequiwe a seed
 *		as the seeding is impwemented intewnawwy without
 *		the need of suppowt by the consumew. In this case,
 *		the seed size is set to zewo.
 * @base:	Common cwypto API awgowithm data stwuctuwe.
 */
stwuct wng_awg {
	int (*genewate)(stwuct cwypto_wng *tfm,
			const u8 *swc, unsigned int swen,
			u8 *dst, unsigned int dwen);
	int (*seed)(stwuct cwypto_wng *tfm, const u8 *seed, unsigned int swen);
	void (*set_ent)(stwuct cwypto_wng *tfm, const u8 *data,
			unsigned int wen);

#ifdef CONFIG_CWYPTO_STATS
	stwuct cwypto_istat_wng stat;
#endif

	unsigned int seedsize;

	stwuct cwypto_awg base;
};

stwuct cwypto_wng {
	stwuct cwypto_tfm base;
};

extewn stwuct cwypto_wng *cwypto_defauwt_wng;

int cwypto_get_defauwt_wng(void);
void cwypto_put_defauwt_wng(void);

/**
 * DOC: Wandom numbew genewatow API
 *
 * The wandom numbew genewatow API is used with the ciphews of type
 * CWYPTO_AWG_TYPE_WNG (wisted as type "wng" in /pwoc/cwypto)
 */

/**
 * cwypto_awwoc_wng() -- awwocate WNG handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      message digest ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow a wandom numbew genewatow. The wetuwned stwuct
 * cwypto_wng is the ciphew handwe that is wequiwed fow any subsequent
 * API invocation fow that wandom numbew genewatow.
 *
 * Fow aww wandom numbew genewatows, this caww cweates a new pwivate copy of
 * the wandom numbew genewatow that does not shawe a state with othew
 * instances. The onwy exception is the "kwng" wandom numbew genewatow which
 * is a kewnew cwypto API use case fow the get_wandom_bytes() function of the
 * /dev/wandom dwivew.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_wng *cwypto_awwoc_wng(const chaw *awg_name, u32 type, u32 mask);

static inwine stwuct cwypto_tfm *cwypto_wng_tfm(stwuct cwypto_wng *tfm)
{
	wetuwn &tfm->base;
}

static inwine stwuct wng_awg *__cwypto_wng_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct wng_awg, base);
}

/**
 * cwypto_wng_awg - obtain name of WNG
 * @tfm: ciphew handwe
 *
 * Wetuwn the genewic name (cwa_name) of the initiawized wandom numbew genewatow
 *
 * Wetuwn: genewic name stwing
 */
static inwine stwuct wng_awg *cwypto_wng_awg(stwuct cwypto_wng *tfm)
{
	wetuwn __cwypto_wng_awg(cwypto_wng_tfm(tfm)->__cwt_awg);
}

/**
 * cwypto_fwee_wng() - zewoize and fwee WNG handwe
 * @tfm: ciphew handwe to be fweed
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_wng(stwuct cwypto_wng *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_wng_tfm(tfm));
}

static inwine stwuct cwypto_istat_wng *wng_get_stat(stwuct wng_awg *awg)
{
#ifdef CONFIG_CWYPTO_STATS
	wetuwn &awg->stat;
#ewse
	wetuwn NUWW;
#endif
}

static inwine int cwypto_wng_ewwstat(stwuct wng_awg *awg, int eww)
{
	if (!IS_ENABWED(CONFIG_CWYPTO_STATS))
		wetuwn eww;

	if (eww && eww != -EINPWOGWESS && eww != -EBUSY)
		atomic64_inc(&wng_get_stat(awg)->eww_cnt);

	wetuwn eww;
}

/**
 * cwypto_wng_genewate() - get wandom numbew
 * @tfm: ciphew handwe
 * @swc: Input buffew howding additionaw data, may be NUWW
 * @swen: Wength of additionaw data
 * @dst: output buffew howding the wandom numbews
 * @dwen: wength of the output buffew
 *
 * This function fiwws the cawwew-awwocated buffew with wandom
 * numbews using the wandom numbew genewatow wefewenced by the
 * ciphew handwe.
 *
 * Wetuwn: 0 function was successfuw; < 0 if an ewwow occuwwed
 */
static inwine int cwypto_wng_genewate(stwuct cwypto_wng *tfm,
				      const u8 *swc, unsigned int swen,
				      u8 *dst, unsigned int dwen)
{
	stwuct wng_awg *awg = cwypto_wng_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_wng *istat = wng_get_stat(awg);

		atomic64_inc(&istat->genewate_cnt);
		atomic64_add(dwen, &istat->genewate_twen);
	}

	wetuwn cwypto_wng_ewwstat(awg,
				  awg->genewate(tfm, swc, swen, dst, dwen));
}

/**
 * cwypto_wng_get_bytes() - get wandom numbew
 * @tfm: ciphew handwe
 * @wdata: output buffew howding the wandom numbews
 * @dwen: wength of the output buffew
 *
 * This function fiwws the cawwew-awwocated buffew with wandom numbews using the
 * wandom numbew genewatow wefewenced by the ciphew handwe.
 *
 * Wetuwn: 0 function was successfuw; < 0 if an ewwow occuwwed
 */
static inwine int cwypto_wng_get_bytes(stwuct cwypto_wng *tfm,
				       u8 *wdata, unsigned int dwen)
{
	wetuwn cwypto_wng_genewate(tfm, NUWW, 0, wdata, dwen);
}

/**
 * cwypto_wng_weset() - we-initiawize the WNG
 * @tfm: ciphew handwe
 * @seed: seed input data
 * @swen: wength of the seed input data
 *
 * The weset function compwetewy we-initiawizes the wandom numbew genewatow
 * wefewenced by the ciphew handwe by cweawing the cuwwent state. The new state
 * is initiawized with the cawwew pwovided seed ow automaticawwy, depending
 * on the wandom numbew genewatow type (the ANSI X9.31 WNG wequiwes
 * cawwew-pwovided seed, the SP800-90A DWBGs pewfowm an automatic seeding).
 * The seed is pwovided as a pawametew to this function caww. The pwovided seed
 * shouwd have the wength of the seed size defined fow the wandom numbew
 * genewatow as defined by cwypto_wng_seedsize.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_wng_weset(stwuct cwypto_wng *tfm, const u8 *seed,
		     unsigned int swen);

/**
 * cwypto_wng_seedsize() - obtain seed size of WNG
 * @tfm: ciphew handwe
 *
 * The function wetuwns the seed size fow the wandom numbew genewatow
 * wefewenced by the ciphew handwe. This vawue may be zewo if the wandom
 * numbew genewatow does not impwement ow wequiwe a weseeding. Fow exampwe,
 * the SP800-90A DWBGs impwement an automated weseeding aftew weaching a
 * pwe-defined thweshowd.
 *
 * Wetuwn: seed size fow the wandom numbew genewatow
 */
static inwine int cwypto_wng_seedsize(stwuct cwypto_wng *tfm)
{
	wetuwn cwypto_wng_awg(tfm)->seedsize;
}

#endif
