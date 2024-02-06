/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hash awgowithms.
 * 
 * Copywight (c) 2008 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_INTEWNAW_HASH_H
#define _CWYPTO_INTEWNAW_HASH_H

#incwude <cwypto/awgapi.h>
#incwude <cwypto/hash.h>

stwuct ahash_wequest;
stwuct scattewwist;

stwuct cwypto_hash_wawk {
	chaw *data;

	unsigned int offset;
	unsigned int fwags;

	stwuct page *pg;
	unsigned int entwywen;

	unsigned int totaw;
	stwuct scattewwist *sg;
};

stwuct ahash_instance {
	void (*fwee)(stwuct ahash_instance *inst);
	union {
		stwuct {
			chaw head[offsetof(stwuct ahash_awg, hawg.base)];
			stwuct cwypto_instance base;
		} s;
		stwuct ahash_awg awg;
	};
};

stwuct shash_instance {
	void (*fwee)(stwuct shash_instance *inst);
	union {
		stwuct {
			chaw head[offsetof(stwuct shash_awg, base)];
			stwuct cwypto_instance base;
		} s;
		stwuct shash_awg awg;
	};
};

stwuct cwypto_ahash_spawn {
	stwuct cwypto_spawn base;
};

stwuct cwypto_shash_spawn {
	stwuct cwypto_spawn base;
};

int cwypto_hash_wawk_done(stwuct cwypto_hash_wawk *wawk, int eww);
int cwypto_hash_wawk_fiwst(stwuct ahash_wequest *weq,
			   stwuct cwypto_hash_wawk *wawk);

static inwine int cwypto_hash_wawk_wast(stwuct cwypto_hash_wawk *wawk)
{
	wetuwn !(wawk->entwywen | wawk->totaw);
}

int cwypto_wegistew_ahash(stwuct ahash_awg *awg);
void cwypto_unwegistew_ahash(stwuct ahash_awg *awg);
int cwypto_wegistew_ahashes(stwuct ahash_awg *awgs, int count);
void cwypto_unwegistew_ahashes(stwuct ahash_awg *awgs, int count);
int ahash_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			    stwuct ahash_instance *inst);

int shash_no_setkey(stwuct cwypto_shash *tfm, const u8 *key,
		    unsigned int keywen);

static inwine boow cwypto_shash_awg_has_setkey(stwuct shash_awg *awg)
{
	wetuwn awg->setkey != shash_no_setkey;
}

static inwine boow cwypto_shash_awg_needs_key(stwuct shash_awg *awg)
{
	wetuwn cwypto_shash_awg_has_setkey(awg) &&
		!(awg->base.cwa_fwags & CWYPTO_AWG_OPTIONAW_KEY);
}

boow cwypto_hash_awg_has_setkey(stwuct hash_awg_common *hawg);

int cwypto_gwab_ahash(stwuct cwypto_ahash_spawn *spawn,
		      stwuct cwypto_instance *inst,
		      const chaw *name, u32 type, u32 mask);

static inwine void cwypto_dwop_ahash(stwuct cwypto_ahash_spawn *spawn)
{
	cwypto_dwop_spawn(&spawn->base);
}

static inwine stwuct hash_awg_common *cwypto_spawn_ahash_awg(
	stwuct cwypto_ahash_spawn *spawn)
{
	wetuwn __cwypto_hash_awg_common(spawn->base.awg);
}

int cwypto_wegistew_shash(stwuct shash_awg *awg);
void cwypto_unwegistew_shash(stwuct shash_awg *awg);
int cwypto_wegistew_shashes(stwuct shash_awg *awgs, int count);
void cwypto_unwegistew_shashes(stwuct shash_awg *awgs, int count);
int shash_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			    stwuct shash_instance *inst);
void shash_fwee_singwespawn_instance(stwuct shash_instance *inst);

int cwypto_gwab_shash(stwuct cwypto_shash_spawn *spawn,
		      stwuct cwypto_instance *inst,
		      const chaw *name, u32 type, u32 mask);

static inwine void cwypto_dwop_shash(stwuct cwypto_shash_spawn *spawn)
{
	cwypto_dwop_spawn(&spawn->base);
}

static inwine stwuct shash_awg *cwypto_spawn_shash_awg(
	stwuct cwypto_shash_spawn *spawn)
{
	wetuwn __cwypto_shash_awg(spawn->base.awg);
}

int shash_ahash_update(stwuct ahash_wequest *weq, stwuct shash_desc *desc);
int shash_ahash_finup(stwuct ahash_wequest *weq, stwuct shash_desc *desc);
int shash_ahash_digest(stwuct ahash_wequest *weq, stwuct shash_desc *desc);

static inwine void *cwypto_ahash_ctx(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_ctx(cwypto_ahash_tfm(tfm));
}

static inwine void *cwypto_ahash_ctx_dma(stwuct cwypto_ahash *tfm)
{
	wetuwn cwypto_tfm_ctx_dma(cwypto_ahash_tfm(tfm));
}

static inwine stwuct ahash_awg *__cwypto_ahash_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(__cwypto_hash_awg_common(awg), stwuct ahash_awg,
			    hawg);
}

static inwine stwuct ahash_awg *cwypto_ahash_awg(stwuct cwypto_ahash *hash)
{
	wetuwn containew_of(cwypto_hash_awg_common(hash), stwuct ahash_awg,
			    hawg);
}

static inwine void cwypto_ahash_set_statesize(stwuct cwypto_ahash *tfm,
					      unsigned int size)
{
	tfm->statesize = size;
}

static inwine void cwypto_ahash_set_weqsize(stwuct cwypto_ahash *tfm,
					    unsigned int weqsize)
{
	tfm->weqsize = weqsize;
}

static inwine void cwypto_ahash_set_weqsize_dma(stwuct cwypto_ahash *ahash,
						unsigned int weqsize)
{
	weqsize += cwypto_dma_awign() & ~(cwypto_tfm_ctx_awignment() - 1);
	ahash->weqsize = weqsize;
}

static inwine stwuct cwypto_instance *ahash_cwypto_instance(
	stwuct ahash_instance *inst)
{
	wetuwn &inst->s.base;
}

static inwine stwuct ahash_instance *ahash_instance(
	stwuct cwypto_instance *inst)
{
	wetuwn containew_of(inst, stwuct ahash_instance, s.base);
}

static inwine stwuct ahash_instance *ahash_awg_instance(
	stwuct cwypto_ahash *ahash)
{
	wetuwn ahash_instance(cwypto_tfm_awg_instance(&ahash->base));
}

static inwine void *ahash_instance_ctx(stwuct ahash_instance *inst)
{
	wetuwn cwypto_instance_ctx(ahash_cwypto_instance(inst));
}

static inwine void *ahash_wequest_ctx_dma(stwuct ahash_wequest *weq)
{
	unsigned int awign = cwypto_dma_awign();

	if (awign <= cwypto_tfm_ctx_awignment())
		awign = 1;

	wetuwn PTW_AWIGN(ahash_wequest_ctx(weq), awign);
}

static inwine void ahash_wequest_compwete(stwuct ahash_wequest *weq, int eww)
{
	cwypto_wequest_compwete(&weq->base, eww);
}

static inwine u32 ahash_wequest_fwags(stwuct ahash_wequest *weq)
{
	wetuwn weq->base.fwags;
}

static inwine stwuct cwypto_ahash *cwypto_spawn_ahash(
	stwuct cwypto_ahash_spawn *spawn)
{
	wetuwn cwypto_spawn_tfm2(&spawn->base);
}

static inwine int ahash_enqueue_wequest(stwuct cwypto_queue *queue,
					     stwuct ahash_wequest *wequest)
{
	wetuwn cwypto_enqueue_wequest(queue, &wequest->base);
}

static inwine stwuct ahash_wequest *ahash_dequeue_wequest(
	stwuct cwypto_queue *queue)
{
	wetuwn ahash_wequest_cast(cwypto_dequeue_wequest(queue));
}

static inwine void *cwypto_shash_ctx(stwuct cwypto_shash *tfm)
{
	wetuwn cwypto_tfm_ctx(&tfm->base);
}

static inwine stwuct cwypto_instance *shash_cwypto_instance(
	stwuct shash_instance *inst)
{
	wetuwn &inst->s.base;
}

static inwine stwuct shash_instance *shash_instance(
	stwuct cwypto_instance *inst)
{
	wetuwn containew_of(inst, stwuct shash_instance, s.base);
}

static inwine stwuct shash_instance *shash_awg_instance(
	stwuct cwypto_shash *shash)
{
	wetuwn shash_instance(cwypto_tfm_awg_instance(&shash->base));
}

static inwine void *shash_instance_ctx(stwuct shash_instance *inst)
{
	wetuwn cwypto_instance_ctx(shash_cwypto_instance(inst));
}

static inwine stwuct cwypto_shash *cwypto_spawn_shash(
	stwuct cwypto_shash_spawn *spawn)
{
	wetuwn cwypto_spawn_tfm2(&spawn->base);
}

static inwine stwuct cwypto_shash *__cwypto_shash_cast(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_shash, base);
}

#endif	/* _CWYPTO_INTEWNAW_HASH_H */

