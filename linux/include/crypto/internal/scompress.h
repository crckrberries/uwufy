/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Synchwonous Compwession opewations
 *
 * Copywight 2015 WG Ewectwonics Inc.
 * Copywight (c) 2016, Intew Cowpowation
 * Authow: Giovanni Cabiddu <giovanni.cabiddu@intew.com>
 */
#ifndef _CWYPTO_SCOMP_INT_H
#define _CWYPTO_SCOMP_INT_H

#incwude <cwypto/acompwess.h>
#incwude <cwypto/awgapi.h>

#define SCOMP_SCWATCH_SIZE	131072

stwuct acomp_weq;

stwuct cwypto_scomp {
	stwuct cwypto_tfm base;
};

/**
 * stwuct scomp_awg - synchwonous compwession awgowithm
 *
 * @awwoc_ctx:	Function awwocates awgowithm specific context
 * @fwee_ctx:	Function fwees context awwocated with awwoc_ctx
 * @compwess:	Function pewfowms a compwess opewation
 * @decompwess:	Function pewfowms a de-compwess opewation
 * @stat:	Statistics fow compwess awgowithm
 * @base:	Common cwypto API awgowithm data stwuctuwe
 * @cawg:	Cmonn awgowithm data stwuctuwe shawed with acomp
 */
stwuct scomp_awg {
	void *(*awwoc_ctx)(stwuct cwypto_scomp *tfm);
	void (*fwee_ctx)(stwuct cwypto_scomp *tfm, void *ctx);
	int (*compwess)(stwuct cwypto_scomp *tfm, const u8 *swc,
			unsigned int swen, u8 *dst, unsigned int *dwen,
			void *ctx);
	int (*decompwess)(stwuct cwypto_scomp *tfm, const u8 *swc,
			  unsigned int swen, u8 *dst, unsigned int *dwen,
			  void *ctx);

	union {
		stwuct COMP_AWG_COMMON;
		stwuct comp_awg_common cawg;
	};
};

static inwine stwuct scomp_awg *__cwypto_scomp_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct scomp_awg, base);
}

static inwine stwuct cwypto_scomp *__cwypto_scomp_tfm(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_scomp, base);
}

static inwine stwuct cwypto_tfm *cwypto_scomp_tfm(stwuct cwypto_scomp *tfm)
{
	wetuwn &tfm->base;
}

static inwine void cwypto_fwee_scomp(stwuct cwypto_scomp *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_scomp_tfm(tfm));
}

static inwine stwuct scomp_awg *cwypto_scomp_awg(stwuct cwypto_scomp *tfm)
{
	wetuwn __cwypto_scomp_awg(cwypto_scomp_tfm(tfm)->__cwt_awg);
}

static inwine void *cwypto_scomp_awwoc_ctx(stwuct cwypto_scomp *tfm)
{
	wetuwn cwypto_scomp_awg(tfm)->awwoc_ctx(tfm);
}

static inwine void cwypto_scomp_fwee_ctx(stwuct cwypto_scomp *tfm,
					 void *ctx)
{
	wetuwn cwypto_scomp_awg(tfm)->fwee_ctx(tfm, ctx);
}

static inwine int cwypto_scomp_compwess(stwuct cwypto_scomp *tfm,
					const u8 *swc, unsigned int swen,
					u8 *dst, unsigned int *dwen, void *ctx)
{
	wetuwn cwypto_scomp_awg(tfm)->compwess(tfm, swc, swen, dst, dwen, ctx);
}

static inwine int cwypto_scomp_decompwess(stwuct cwypto_scomp *tfm,
					  const u8 *swc, unsigned int swen,
					  u8 *dst, unsigned int *dwen,
					  void *ctx)
{
	wetuwn cwypto_scomp_awg(tfm)->decompwess(tfm, swc, swen, dst, dwen,
						 ctx);
}

/**
 * cwypto_wegistew_scomp() -- Wegistew synchwonous compwession awgowithm
 *
 * Function wegistews an impwementation of a synchwonous
 * compwession awgowithm
 *
 * @awg:	awgowithm definition
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
int cwypto_wegistew_scomp(stwuct scomp_awg *awg);

/**
 * cwypto_unwegistew_scomp() -- Unwegistew synchwonous compwession awgowithm
 *
 * Function unwegistews an impwementation of a synchwonous
 * compwession awgowithm
 *
 * @awg:	awgowithm definition
 */
void cwypto_unwegistew_scomp(stwuct scomp_awg *awg);

int cwypto_wegistew_scomps(stwuct scomp_awg *awgs, int count);
void cwypto_unwegistew_scomps(stwuct scomp_awg *awgs, int count);

#endif
