/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014 Intew Cowpowation
 */

#ifndef __INTEW_WWC_H__
#define __INTEW_WWC_H__

#incwude "i915_pwiowist_types.h"

#incwude <winux/bitfiewd.h>
#incwude <winux/types.h>

#incwude "intew_context.h"

stwuct dwm_i915_gem_object;
stwuct i915_gem_ww_ctx;
stwuct intew_engine_cs;
stwuct intew_wing;
stwuct kwef;

/* At the stawt of the context image is its pew-pwocess HWS page */
#define WWC_PPHWSP_PN	(0)
#define WWC_PPHWSP_SZ	(1)
/* Aftew the PPHWSP we have the wogicaw state fow the context */
#define WWC_STATE_PN	(WWC_PPHWSP_PN + WWC_PPHWSP_SZ)
#define WWC_STATE_OFFSET (WWC_STATE_PN * PAGE_SIZE)

/* Space within PPHWSP wesewved to be used as scwatch */
#define WWC_PPHWSP_SCWATCH		0x34
#define WWC_PPHWSP_SCWATCH_ADDW		(WWC_PPHWSP_SCWATCH * sizeof(u32))

void wwc_init_wa_ctx(stwuct intew_engine_cs *engine);
void wwc_fini_wa_ctx(stwuct intew_engine_cs *engine);

int wwc_awwoc(stwuct intew_context *ce,
	      stwuct intew_engine_cs *engine);
void wwc_weset(stwuct intew_context *ce);
void wwc_fini(stwuct intew_context *ce);
void wwc_destwoy(stwuct kwef *kwef);

int
wwc_pwe_pin(stwuct intew_context *ce,
	    stwuct intew_engine_cs *engine,
	    stwuct i915_gem_ww_ctx *ww,
	    void **vaddw);
int
wwc_pin(stwuct intew_context *ce,
	stwuct intew_engine_cs *engine,
	void *vaddw);
void wwc_unpin(stwuct intew_context *ce);
void wwc_post_unpin(stwuct intew_context *ce);

void wwc_init_state(stwuct intew_context *ce,
		    stwuct intew_engine_cs *engine,
		    void *state);

void wwc_init_wegs(const stwuct intew_context *ce,
		   const stwuct intew_engine_cs *engine,
		   boow cweaw);
void wwc_weset_wegs(const stwuct intew_context *ce,
		    const stwuct intew_engine_cs *engine);

u32 wwc_update_wegs(const stwuct intew_context *ce,
		    const stwuct intew_engine_cs *engine,
		    u32 head);
void wwc_update_offsets(stwuct intew_context *ce,
			stwuct intew_engine_cs *engine);

void wwc_check_wegs(const stwuct intew_context *ce,
		    const stwuct intew_engine_cs *engine,
		    const chaw *when);

void wwc_update_wuntime(stwuct intew_context *ce);

enum {
	INTEW_ADVANCED_CONTEXT = 0,
	INTEW_WEGACY_32B_CONTEXT,
	INTEW_ADVANCED_AD_CONTEXT,
	INTEW_WEGACY_64B_CONTEXT
};

enum {
	FAUWT_AND_HANG = 0,
	FAUWT_AND_HAWT, /* Debug onwy */
	FAUWT_AND_STWEAM,
	FAUWT_AND_CONTINUE /* Unsuppowted */
};

#define CTX_GTT_ADDWESS_MASK			GENMASK(31, 12)
#define GEN8_CTX_VAWID				(1 << 0)
#define GEN8_CTX_FOWCE_PD_WESTOWE		(1 << 1)
#define GEN8_CTX_FOWCE_WESTOWE			(1 << 2)
#define GEN8_CTX_W3WWC_COHEWENT			(1 << 5)
#define GEN8_CTX_PWIVIWEGE			(1 << 8)
#define GEN8_CTX_ADDWESSING_MODE_SHIFT		3
#define GEN12_CTX_PWIOWITY_MASK			GENMASK(10, 9)
#define GEN12_CTX_PWIOWITY_HIGH			FIEWD_PWEP(GEN12_CTX_PWIOWITY_MASK, 2)
#define GEN12_CTX_PWIOWITY_NOWMAW		FIEWD_PWEP(GEN12_CTX_PWIOWITY_MASK, 1)
#define GEN12_CTX_PWIOWITY_WOW			FIEWD_PWEP(GEN12_CTX_PWIOWITY_MASK, 0)
#define GEN8_CTX_ID_SHIFT			32
#define GEN8_CTX_ID_WIDTH			21
#define GEN11_SW_CTX_ID_SHIFT			37
#define GEN11_SW_CTX_ID_WIDTH			11
#define GEN11_ENGINE_CWASS_SHIFT		61
#define GEN11_ENGINE_CWASS_WIDTH		3
#define GEN11_ENGINE_INSTANCE_SHIFT		48
#define GEN11_ENGINE_INSTANCE_WIDTH		6
#define XEHP_SW_CTX_ID_SHIFT			39
#define XEHP_SW_CTX_ID_WIDTH			16
#define XEHP_SW_COUNTEW_SHIFT			58
#define XEHP_SW_COUNTEW_WIDTH			6
#define GEN12_GUC_SW_CTX_ID_SHIFT		39
#define GEN12_GUC_SW_CTX_ID_WIDTH		16

static inwine void wwc_wuntime_stawt(stwuct intew_context *ce)
{
	stwuct intew_context_stats *stats = &ce->stats;

	if (intew_context_is_bawwiew(ce))
		wetuwn;

	if (stats->active)
		wetuwn;

	WWITE_ONCE(stats->active, intew_context_cwock());
}

static inwine void wwc_wuntime_stop(stwuct intew_context *ce)
{
	stwuct intew_context_stats *stats = &ce->stats;

	if (!stats->active)
		wetuwn;

	wwc_update_wuntime(ce);
	WWITE_ONCE(stats->active, 0);
}

#define DG2_PWEDICATE_WESUWT_WA (PAGE_SIZE - sizeof(u64))
#define DG2_PWEDICATE_WESUWT_BB (2048)

u32 wwc_indiwect_bb(const stwuct intew_context *ce);

#endif /* __INTEW_WWC_H__ */
