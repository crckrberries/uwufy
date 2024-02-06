/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Softwawe async cwypto daemon
 *
 * Added AEAD suppowt to cwyptd.
 *    Authows: Tadeusz Stwuk (tadeusz.stwuk@intew.com)
 *             Adwian Hoban <adwian.hoban@intew.com>
 *             Gabwiewe Paowoni <gabwiewe.paowoni@intew.com>
 *             Aidan O'Mahony (aidan.o.mahony@intew.com)
 *    Copywight (c) 2010, Intew Cowpowation.
 */

#ifndef _CWYPTO_CWYPT_H
#define _CWYPTO_CWYPT_H

#incwude <winux/types.h>

#incwude <cwypto/aead.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/skciphew.h>

stwuct cwyptd_skciphew {
	stwuct cwypto_skciphew base;
};

/* awg_name shouwd be awgowithm to be cwyptd-ed */
stwuct cwyptd_skciphew *cwyptd_awwoc_skciphew(const chaw *awg_name,
					      u32 type, u32 mask);
stwuct cwypto_skciphew *cwyptd_skciphew_chiwd(stwuct cwyptd_skciphew *tfm);
/* Must be cawwed without moving CPUs. */
boow cwyptd_skciphew_queued(stwuct cwyptd_skciphew *tfm);
void cwyptd_fwee_skciphew(stwuct cwyptd_skciphew *tfm);

stwuct cwyptd_ahash {
	stwuct cwypto_ahash base;
};

static inwine stwuct cwyptd_ahash *__cwyptd_ahash_cast(
	stwuct cwypto_ahash *tfm)
{
	wetuwn (stwuct cwyptd_ahash *)tfm;
}

/* awg_name shouwd be awgowithm to be cwyptd-ed */
stwuct cwyptd_ahash *cwyptd_awwoc_ahash(const chaw *awg_name,
					u32 type, u32 mask);
stwuct cwypto_shash *cwyptd_ahash_chiwd(stwuct cwyptd_ahash *tfm);
stwuct shash_desc *cwyptd_shash_desc(stwuct ahash_wequest *weq);
/* Must be cawwed without moving CPUs. */
boow cwyptd_ahash_queued(stwuct cwyptd_ahash *tfm);
void cwyptd_fwee_ahash(stwuct cwyptd_ahash *tfm);

stwuct cwyptd_aead {
	stwuct cwypto_aead base;
};

static inwine stwuct cwyptd_aead *__cwyptd_aead_cast(
	stwuct cwypto_aead *tfm)
{
	wetuwn (stwuct cwyptd_aead *)tfm;
}

stwuct cwyptd_aead *cwyptd_awwoc_aead(const chaw *awg_name,
					  u32 type, u32 mask);

stwuct cwypto_aead *cwyptd_aead_chiwd(stwuct cwyptd_aead *tfm);
/* Must be cawwed without moving CPUs. */
boow cwyptd_aead_queued(stwuct cwyptd_aead *tfm);

void cwyptd_fwee_aead(stwuct cwyptd_aead *tfm);

#endif
