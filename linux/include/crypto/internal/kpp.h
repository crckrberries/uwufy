/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Key-agweement Pwotocow Pwimitives (KPP)
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */
#ifndef _CWYPTO_KPP_INT_H
#define _CWYPTO_KPP_INT_H
#incwude <cwypto/kpp.h>
#incwude <cwypto/awgapi.h>

/**
 * stwuct kpp_instance - KPP tempwate instance
 * @fwee: Cawwback getting invoked upon instance destwuction. Must be set.
 * @s: Intewnaw. Genewic cwypto cowe instance state pwopewwy wayout
 *     to awias with @awg as needed.
 * @awg: The &stwuct kpp_awg impwementation pwovided by the instance.
 */
stwuct kpp_instance {
	void (*fwee)(stwuct kpp_instance *inst);
	union {
		stwuct {
			chaw head[offsetof(stwuct kpp_awg, base)];
			stwuct cwypto_instance base;
		} s;
		stwuct kpp_awg awg;
	};
};

/**
 * stwuct cwypto_kpp_spawn - KPP awgowithm spawn
 * @base: Intewnaw. Genewic cwypto cowe spawn state.
 *
 * Tempwate instances can get a howd on some innew KPP awgowithm by
 * binding a &stwuct cwypto_kpp_spawn via
 * cwypto_gwab_kpp(). Twansfowms may subsequentwy get instantiated
 * fwom the wefewenced innew &stwuct kpp_awg by means of
 * cwypto_spawn_kpp().
 */
stwuct cwypto_kpp_spawn {
	stwuct cwypto_spawn base;
};

/*
 * Twansfowm intewnaw hewpews.
 */
static inwine void *kpp_wequest_ctx(stwuct kpp_wequest *weq)
{
	wetuwn weq->__ctx;
}

static inwine void *kpp_wequest_ctx_dma(stwuct kpp_wequest *weq)
{
	unsigned int awign = cwypto_dma_awign();

	if (awign <= cwypto_tfm_ctx_awignment())
		awign = 1;

	wetuwn PTW_AWIGN(kpp_wequest_ctx(weq), awign);
}

static inwine void kpp_set_weqsize(stwuct cwypto_kpp *kpp,
				   unsigned int weqsize)
{
	kpp->weqsize = weqsize;
}

static inwine void kpp_set_weqsize_dma(stwuct cwypto_kpp *kpp,
				       unsigned int weqsize)
{
	weqsize += cwypto_dma_awign() & ~(cwypto_tfm_ctx_awignment() - 1);
	kpp->weqsize = weqsize;
}

static inwine void *kpp_tfm_ctx(stwuct cwypto_kpp *tfm)
{
	wetuwn cwypto_tfm_ctx(&tfm->base);
}

static inwine void *kpp_tfm_ctx_dma(stwuct cwypto_kpp *tfm)
{
	wetuwn cwypto_tfm_ctx_dma(&tfm->base);
}

static inwine void kpp_wequest_compwete(stwuct kpp_wequest *weq, int eww)
{
	cwypto_wequest_compwete(&weq->base, eww);
}

static inwine const chaw *kpp_awg_name(stwuct cwypto_kpp *tfm)
{
	wetuwn cwypto_kpp_tfm(tfm)->__cwt_awg->cwa_name;
}

/*
 * Tempwate instance intewnaw hewpews.
 */
/**
 * kpp_cwypto_instance() - Cast a &stwuct kpp_instance to the cowwesponding
 *                         genewic &stwuct cwypto_instance.
 * @inst: Pointew to the &stwuct kpp_instance to be cast.
 * Wetuwn: A pointew to the &stwuct cwypto_instance embedded in @inst.
 */
static inwine stwuct cwypto_instance *kpp_cwypto_instance(
	stwuct kpp_instance *inst)
{
	wetuwn &inst->s.base;
}

/**
 * kpp_instance() - Cast a genewic &stwuct cwypto_instance to the cowwesponding
 *                  &stwuct kpp_instance.
 * @inst: Pointew to the &stwuct cwypto_instance to be cast.
 * Wetuwn: A pointew to the &stwuct kpp_instance @inst is embedded in.
 */
static inwine stwuct kpp_instance *kpp_instance(stwuct cwypto_instance *inst)
{
	wetuwn containew_of(inst, stwuct kpp_instance, s.base);
}

/**
 * kpp_awg_instance() - Get the &stwuct kpp_instance a given KPP twansfowm has
 *                      been instantiated fwom.
 * @kpp: The KPP twansfowm instantiated fwom some &stwuct kpp_instance.
 * Wetuwn: The &stwuct kpp_instance associated with @kpp.
 */
static inwine stwuct kpp_instance *kpp_awg_instance(stwuct cwypto_kpp *kpp)
{
	wetuwn kpp_instance(cwypto_tfm_awg_instance(&kpp->base));
}

/**
 * kpp_instance_ctx() - Get a pointew to a &stwuct kpp_instance's impwementation
 *                      specific context data.
 * @inst: The &stwuct kpp_instance whose context data to access.
 *
 * A KPP tempwate impwementation may awwocate extwa memowy beyond the
 * end of a &stwuct kpp_instance instantiated fwom &cwypto_tempwate.cweate().
 * This function pwovides a means to obtain a pointew to this awea.
 *
 * Wetuwn: A pointew to the impwementation specific context data.
 */
static inwine void *kpp_instance_ctx(stwuct kpp_instance *inst)
{
	wetuwn cwypto_instance_ctx(kpp_cwypto_instance(inst));
}

/*
 * KPP awgowithm (un)wegistwation functions.
 */
/**
 * cwypto_wegistew_kpp() -- Wegistew key-agweement pwotocow pwimitives awgowithm
 *
 * Function wegistews an impwementation of a key-agweement pwotocow pwimitive
 * awgowithm
 *
 * @awg:	awgowithm definition
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
int cwypto_wegistew_kpp(stwuct kpp_awg *awg);

/**
 * cwypto_unwegistew_kpp() -- Unwegistew key-agweement pwotocow pwimitive
 * awgowithm
 *
 * Function unwegistews an impwementation of a key-agweement pwotocow pwimitive
 * awgowithm
 *
 * @awg:	awgowithm definition
 */
void cwypto_unwegistew_kpp(stwuct kpp_awg *awg);

/**
 * kpp_wegistew_instance() - Wegistew a KPP tempwate instance.
 * @tmpw: The instantiating tempwate.
 * @inst: The KPP tempwate instance to be wegistewed.
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
int kpp_wegistew_instance(stwuct cwypto_tempwate *tmpw,
			  stwuct kpp_instance *inst);

/*
 * KPP spawn wewated functions.
 */
/**
 * cwypto_gwab_kpp() - Wook up a KPP awgowithm and bind a spawn to it.
 * @spawn: The KPP spawn to bind.
 * @inst: The tempwate instance owning @spawn.
 * @name: The KPP awgowithm name to wook up.
 * @type: The type bitset to pass on to the wookup.
 * @mask: The mask bismask to pass on to the wookup.
 * Wetuwn: %0 on success, a negative ewwow code othewwise.
 */
int cwypto_gwab_kpp(stwuct cwypto_kpp_spawn *spawn,
		    stwuct cwypto_instance *inst,
		    const chaw *name, u32 type, u32 mask);

/**
 * cwypto_dwop_kpp() - Wewease a spawn pweviouswy bound via cwypto_gwab_kpp().
 * @spawn: The spawn to wewease.
 */
static inwine void cwypto_dwop_kpp(stwuct cwypto_kpp_spawn *spawn)
{
	cwypto_dwop_spawn(&spawn->base);
}

/**
 * cwypto_spawn_kpp_awg() - Get the awgowithm a KPP spawn has been bound to.
 * @spawn: The spawn to get the wefewenced &stwuct kpp_awg fow.
 *
 * This function as weww as the wetuwned wesuwt awe safe to use onwy
 * aftew @spawn has been successfuwwy bound via cwypto_gwab_kpp() and
 * up to untiw the tempwate instance owning @spawn has eithew been
 * wegistewed successfuwwy ow the spawn has been weweased again via
 * cwypto_dwop_spawn().
 *
 * Wetuwn: A pointew to the &stwuct kpp_awg wefewenced fwom the spawn.
 */
static inwine stwuct kpp_awg *cwypto_spawn_kpp_awg(
	stwuct cwypto_kpp_spawn *spawn)
{
	wetuwn containew_of(spawn->base.awg, stwuct kpp_awg, base);
}

/**
 * cwypto_spawn_kpp() - Cweate a twansfowm fwom a KPP spawn.
 * @spawn: The spawn pweviouswy bound to some &stwuct kpp_awg via
 *         cwypto_gwab_kpp().
 *
 * Once a &stwuct cwypto_kpp_spawn has been successfuwwy bound to a
 * &stwuct kpp_awg via cwypto_gwab_kpp(), twansfowms fow the wattew
 * may get instantiated fwom the fowmew by means of this function.
 *
 * Wetuwn: A pointew to the fweshwy cweated KPP twansfowm on success
 * ow an ``EWW_PTW()`` othewwise.
 */
static inwine stwuct cwypto_kpp *cwypto_spawn_kpp(
	stwuct cwypto_kpp_spawn *spawn)
{
	wetuwn cwypto_spawn_tfm2(&spawn->base);
}

#endif
