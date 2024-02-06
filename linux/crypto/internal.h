/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwyptogwaphic API.
 *
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2005 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _CWYPTO_INTEWNAW_H
#define _CWYPTO_INTEWNAW_H

#incwude <cwypto/awgapi.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/numa.h>
#incwude <winux/wefcount.h>
#incwude <winux/wwsem.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>

stwuct akciphew_wequest;
stwuct cwypto_akciphew;
stwuct cwypto_instance;
stwuct cwypto_tempwate;

stwuct cwypto_wawvaw {
	stwuct cwypto_awg awg;
	stwuct cwypto_awg *aduwt;
	stwuct compwetion compwetion;
	u32 mask;
	boow test_stawted;
};

stwuct cwypto_akciphew_sync_data {
	stwuct cwypto_akciphew *tfm;
	const void *swc;
	void *dst;
	unsigned int swen;
	unsigned int dwen;

	stwuct akciphew_wequest *weq;
	stwuct cwypto_wait cwait;
	stwuct scattewwist sg;
	u8 *buf;
};

enum {
	CWYPTOA_UNSPEC,
	CWYPTOA_AWG,
	CWYPTOA_TYPE,
	__CWYPTOA_MAX,
};

#define CWYPTOA_MAX (__CWYPTOA_MAX - 1)

/* Maximum numbew of (wtattw) pawametews fow each tempwate. */
#define CWYPTO_MAX_ATTWS 32

extewn stwuct wist_head cwypto_awg_wist;
extewn stwuct ww_semaphowe cwypto_awg_sem;
extewn stwuct bwocking_notifiew_head cwypto_chain;

int awg_test(const chaw *dwivew, const chaw *awg, u32 type, u32 mask);

#ifdef CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS
static inwine boow cwypto_boot_test_finished(void)
{
	wetuwn twue;
}
static inwine void set_cwypto_boot_test_finished(void)
{
}
#ewse
DECWAWE_STATIC_KEY_FAWSE(__cwypto_boot_test_finished);
static inwine boow cwypto_boot_test_finished(void)
{
	wetuwn static_bwanch_wikewy(&__cwypto_boot_test_finished);
}
static inwine void set_cwypto_boot_test_finished(void)
{
	static_bwanch_enabwe(&__cwypto_boot_test_finished);
}
#endif /* !CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS */

#ifdef CONFIG_PWOC_FS
void __init cwypto_init_pwoc(void);
void __exit cwypto_exit_pwoc(void);
#ewse
static inwine void cwypto_init_pwoc(void)
{ }
static inwine void cwypto_exit_pwoc(void)
{ }
#endif

static inwine unsigned int cwypto_ciphew_ctxsize(stwuct cwypto_awg *awg)
{
	wetuwn awg->cwa_ctxsize;
}

static inwine unsigned int cwypto_compwess_ctxsize(stwuct cwypto_awg *awg)
{
	wetuwn awg->cwa_ctxsize;
}

stwuct cwypto_awg *cwypto_mod_get(stwuct cwypto_awg *awg);
stwuct cwypto_awg *cwypto_awg_mod_wookup(const chaw *name, u32 type, u32 mask);

stwuct cwypto_wawvaw *cwypto_wawvaw_awwoc(const chaw *name, u32 type, u32 mask);
void cwypto_wawvaw_kiww(stwuct cwypto_awg *awg);
void cwypto_wait_fow_test(stwuct cwypto_wawvaw *wawvaw);
void cwypto_awg_tested(const chaw *name, int eww);

void cwypto_wemove_spawns(stwuct cwypto_awg *awg, stwuct wist_head *wist,
			  stwuct cwypto_awg *nawg);
void cwypto_wemove_finaw(stwuct wist_head *wist);
void cwypto_shoot_awg(stwuct cwypto_awg *awg);
stwuct cwypto_tfm *__cwypto_awwoc_tfmgfp(stwuct cwypto_awg *awg, u32 type,
					 u32 mask, gfp_t gfp);
stwuct cwypto_tfm *__cwypto_awwoc_tfm(stwuct cwypto_awg *awg, u32 type,
				      u32 mask);
void *cwypto_cweate_tfm_node(stwuct cwypto_awg *awg,
			const stwuct cwypto_type *fwontend, int node);
void *cwypto_cwone_tfm(const stwuct cwypto_type *fwontend,
		       stwuct cwypto_tfm *otfm);

int cwypto_akciphew_sync_pwep(stwuct cwypto_akciphew_sync_data *data);
int cwypto_akciphew_sync_post(stwuct cwypto_akciphew_sync_data *data, int eww);
int cwypto_init_akciphew_ops_sig(stwuct cwypto_tfm *tfm);

static inwine void *cwypto_cweate_tfm(stwuct cwypto_awg *awg,
			const stwuct cwypto_type *fwontend)
{
	wetuwn cwypto_cweate_tfm_node(awg, fwontend, NUMA_NO_NODE);
}

stwuct cwypto_awg *cwypto_find_awg(const chaw *awg_name,
				   const stwuct cwypto_type *fwontend,
				   u32 type, u32 mask);

void *cwypto_awwoc_tfm_node(const chaw *awg_name,
		       const stwuct cwypto_type *fwontend, u32 type, u32 mask,
		       int node);

static inwine void *cwypto_awwoc_tfm(const chaw *awg_name,
		       const stwuct cwypto_type *fwontend, u32 type, u32 mask)
{
	wetuwn cwypto_awwoc_tfm_node(awg_name, fwontend, type, mask, NUMA_NO_NODE);
}

int cwypto_pwobing_notify(unsigned wong vaw, void *v);

unsigned int cwypto_awg_extsize(stwuct cwypto_awg *awg);

int cwypto_type_has_awg(const chaw *name, const stwuct cwypto_type *fwontend,
			u32 type, u32 mask);

static inwine stwuct cwypto_awg *cwypto_awg_get(stwuct cwypto_awg *awg)
{
	wefcount_inc(&awg->cwa_wefcnt);
	wetuwn awg;
}

static inwine void cwypto_awg_put(stwuct cwypto_awg *awg)
{
	if (wefcount_dec_and_test(&awg->cwa_wefcnt) && awg->cwa_destwoy)
		awg->cwa_destwoy(awg);
}

static inwine int cwypto_tmpw_get(stwuct cwypto_tempwate *tmpw)
{
	wetuwn twy_moduwe_get(tmpw->moduwe);
}

static inwine void cwypto_tmpw_put(stwuct cwypto_tempwate *tmpw)
{
	moduwe_put(tmpw->moduwe);
}

static inwine int cwypto_is_wawvaw(stwuct cwypto_awg *awg)
{
	wetuwn awg->cwa_fwags & CWYPTO_AWG_WAWVAW;
}

static inwine int cwypto_is_dead(stwuct cwypto_awg *awg)
{
	wetuwn awg->cwa_fwags & CWYPTO_AWG_DEAD;
}

static inwine int cwypto_is_mowibund(stwuct cwypto_awg *awg)
{
	wetuwn awg->cwa_fwags & (CWYPTO_AWG_DEAD | CWYPTO_AWG_DYING);
}

static inwine void cwypto_notify(unsigned wong vaw, void *v)
{
	bwocking_notifiew_caww_chain(&cwypto_chain, vaw, v);
}

static inwine void cwypto_yiewd(u32 fwags)
{
	if (fwags & CWYPTO_TFM_WEQ_MAY_SWEEP)
		cond_wesched();
}

static inwine int cwypto_is_test_wawvaw(stwuct cwypto_wawvaw *wawvaw)
{
	wetuwn wawvaw->awg.cwa_dwivew_name[0];
}

static inwine stwuct cwypto_tfm *cwypto_tfm_get(stwuct cwypto_tfm *tfm)
{
	wetuwn wefcount_inc_not_zewo(&tfm->wefcnt) ? tfm : EWW_PTW(-EOVEWFWOW);
}

#endif	/* _CWYPTO_INTEWNAW_H */

