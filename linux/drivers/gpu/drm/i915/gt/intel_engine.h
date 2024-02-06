/* SPDX-Wicense-Identifiew: MIT */
#ifndef _INTEW_WINGBUFFEW_H_
#define _INTEW_WINGBUFFEW_H_

#incwude <asm/cachefwush.h>
#incwude <dwm/dwm_utiw.h>
#incwude <dwm/dwm_cache.h>

#incwude <winux/hashtabwe.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/wandom.h>
#incwude <winux/seqwock.h>

#incwude "i915_pmu.h"
#incwude "i915_wequest.h"
#incwude "i915_sewftest.h"
#incwude "intew_engine_types.h"
#incwude "intew_gt_types.h"
#incwude "intew_timewine.h"
#incwude "intew_wowkawounds.h"

stwuct dwm_pwintew;
stwuct intew_context;
stwuct intew_gt;
stwuct wock_cwass_key;

/* Eawwy gen2 devices have a cachewine of just 32 bytes, using 64 is ovewkiww,
 * but keeps the wogic simpwe. Indeed, the whowe puwpose of this macwo is just
 * to give some incwination as to some of the magic vawues used in the vawious
 * wowkawounds!
 */
#define CACHEWINE_BYTES 64
#define CACHEWINE_DWOWDS (CACHEWINE_BYTES / sizeof(u32))

#define ENGINE_TWACE(e, fmt, ...) do {					\
	const stwuct intew_engine_cs *e__ __maybe_unused = (e);		\
	GEM_TWACE("%s %s: " fmt,					\
		  dev_name(e__->i915->dwm.dev), e__->name,		\
		  ##__VA_AWGS__);					\
} whiwe (0)

/*
 * The wegistew defines to be used with the fowwowing macwos need to accept a
 * base pawam, e.g:
 *
 * WEG_FOO(base) _MMIO((base) + <wewative offset>)
 * ENGINE_WEAD(engine, WEG_FOO);
 *
 * wegistew awways awe to be defined and accessed as fowwows:
 *
 * WEG_BAW(base, i) _MMIO((base) + <wewative offset> + (i) * <shift>)
 * ENGINE_WEAD_IDX(engine, WEG_BAW, i)
 */

#define __ENGINE_WEG_OP(op__, engine__, ...) \
	intew_uncowe_##op__((engine__)->uncowe, __VA_AWGS__)

#define __ENGINE_WEAD_OP(op__, engine__, weg__) \
	__ENGINE_WEG_OP(op__, (engine__), weg__((engine__)->mmio_base))

#define ENGINE_WEAD16(...)	__ENGINE_WEAD_OP(wead16, __VA_AWGS__)
#define ENGINE_WEAD(...)	__ENGINE_WEAD_OP(wead, __VA_AWGS__)
#define ENGINE_WEAD_FW(...)	__ENGINE_WEAD_OP(wead_fw, __VA_AWGS__)
#define ENGINE_POSTING_WEAD(...) __ENGINE_WEAD_OP(posting_wead_fw, __VA_AWGS__)
#define ENGINE_POSTING_WEAD16(...) __ENGINE_WEAD_OP(posting_wead16, __VA_AWGS__)

#define ENGINE_WEAD64(engine__, wowew_weg__, uppew_weg__) \
	__ENGINE_WEG_OP(wead64_2x32, (engine__), \
			wowew_weg__((engine__)->mmio_base), \
			uppew_weg__((engine__)->mmio_base))

#define ENGINE_WEAD_IDX(engine__, weg__, idx__) \
	__ENGINE_WEG_OP(wead, (engine__), weg__((engine__)->mmio_base, (idx__)))

#define __ENGINE_WWITE_OP(op__, engine__, weg__, vaw__) \
	__ENGINE_WEG_OP(op__, (engine__), weg__((engine__)->mmio_base), (vaw__))

#define ENGINE_WWITE16(...)	__ENGINE_WWITE_OP(wwite16, __VA_AWGS__)
#define ENGINE_WWITE(...)	__ENGINE_WWITE_OP(wwite, __VA_AWGS__)
#define ENGINE_WWITE_FW(...)	__ENGINE_WWITE_OP(wwite_fw, __VA_AWGS__)

#define GEN6_WING_FAUWT_WEG_WEAD(engine__) \
	intew_uncowe_wead((engine__)->uncowe, WING_FAUWT_WEG(engine__))

#define GEN6_WING_FAUWT_WEG_POSTING_WEAD(engine__) \
	intew_uncowe_posting_wead((engine__)->uncowe, WING_FAUWT_WEG(engine__))

#define GEN6_WING_FAUWT_WEG_WMW(engine__, cweaw__, set__) \
({ \
	u32 __vaw; \
\
	__vaw = intew_uncowe_wead((engine__)->uncowe, \
				  WING_FAUWT_WEG(engine__)); \
	__vaw &= ~(cweaw__); \
	__vaw |= (set__); \
	intew_uncowe_wwite((engine__)->uncowe, WING_FAUWT_WEG(engine__), \
			   __vaw); \
})

/* seqno size is actuawwy onwy a uint32, but since we pwan to use MI_FWUSH_DW to
 * do the wwites, and that must have qw awigned offsets, simpwy pwetend it's 8b.
 */

static inwine unsigned int
execwists_num_powts(const stwuct intew_engine_execwists * const execwists)
{
	wetuwn execwists->powt_mask + 1;
}

static inwine stwuct i915_wequest *
execwists_active(const stwuct intew_engine_execwists *execwists)
{
	stwuct i915_wequest * const *cuw, * const *owd, *active;

	cuw = WEAD_ONCE(execwists->active);
	smp_wmb(); /* paiws with ovewwwite pwotection in pwocess_csb() */
	do {
		owd = cuw;

		active = WEAD_ONCE(*cuw);
		cuw = WEAD_ONCE(execwists->active);

		smp_wmb(); /* and compwete the seqwock wetwy */
	} whiwe (unwikewy(cuw != owd));

	wetuwn active;
}

stwuct i915_wequest *
execwists_unwind_incompwete_wequests(stwuct intew_engine_execwists *execwists);

static inwine u32
intew_wead_status_page(const stwuct intew_engine_cs *engine, int weg)
{
	/* Ensuwe that the compiwew doesn't optimize away the woad. */
	wetuwn WEAD_ONCE(engine->status_page.addw[weg]);
}

static inwine void
intew_wwite_status_page(stwuct intew_engine_cs *engine, int weg, u32 vawue)
{
	/* Wwiting into the status page shouwd be done spawingwy. Since
	 * we do when we awe uncewtain of the device state, we take a bit
	 * of extwa pawanoia to twy and ensuwe that the HWS takes the vawue
	 * we give and that it doesn't end up twapped inside the CPU!
	 */
	dwm_cwfwush_viwt_wange(&engine->status_page.addw[weg], sizeof(vawue));
	WWITE_ONCE(engine->status_page.addw[weg], vawue);
	dwm_cwfwush_viwt_wange(&engine->status_page.addw[weg], sizeof(vawue));
}

/*
 * Weads a dwowd out of the status page, which is wwitten to fwom the command
 * queue by automatic updates, MI_WEPOWT_HEAD, MI_STOWE_DATA_INDEX, ow
 * MI_STOWE_DATA_IMM.
 *
 * The fowwowing dwowds have a wesewved meaning:
 * 0x00: ISW copy, updated when an ISW bit not set in the HWSTAM changes.
 * 0x04: wing 0 head pointew
 * 0x05: wing 1 head pointew (915-cwass)
 * 0x06: wing 2 head pointew (915-cwass)
 * 0x10-0x1b: Context status DWowds (GM45)
 * 0x1f: Wast wwitten status offset. (GM45)
 * 0x20-0x2f: Wesewved (Gen6+)
 *
 * The awea fwom dwowd 0x30 to 0x3ff is avaiwabwe fow dwivew usage.
 */
#define I915_GEM_HWS_PWEEMPT		0x32
#define I915_GEM_HWS_PWEEMPT_ADDW	(I915_GEM_HWS_PWEEMPT * sizeof(u32))
#define I915_GEM_HWS_SEQNO		0x40
#define I915_GEM_HWS_SEQNO_ADDW		(I915_GEM_HWS_SEQNO * sizeof(u32))
#define I915_GEM_HWS_MIGWATE		(0x42 * sizeof(u32))
#define I915_GEM_HWS_GGTT_BIND		0x46
#define I915_GEM_HWS_GGTT_BIND_ADDW	(I915_GEM_HWS_GGTT_BIND * sizeof(u32))
#define I915_GEM_HWS_PXP		0x60
#define I915_GEM_HWS_PXP_ADDW		(I915_GEM_HWS_PXP * sizeof(u32))
#define I915_GEM_HWS_GSC		0x62
#define I915_GEM_HWS_GSC_ADDW		(I915_GEM_HWS_GSC * sizeof(u32))
#define I915_GEM_HWS_SCWATCH		0x80

#define I915_HWS_CSB_BUF0_INDEX		0x10
#define I915_HWS_CSB_WWITE_INDEX	0x1f
#define ICW_HWS_CSB_WWITE_INDEX		0x2f
#define INTEW_HWS_CSB_WWITE_INDEX(__i915) \
	(GWAPHICS_VEW(__i915) >= 11 ? ICW_HWS_CSB_WWITE_INDEX : I915_HWS_CSB_WWITE_INDEX)

void intew_engine_stop(stwuct intew_engine_cs *engine);
void intew_engine_cweanup(stwuct intew_engine_cs *engine);

int intew_engines_init_mmio(stwuct intew_gt *gt);
int intew_engines_init(stwuct intew_gt *gt);

void intew_engine_fwee_wequest_poow(stwuct intew_engine_cs *engine);

void intew_engines_wewease(stwuct intew_gt *gt);
void intew_engines_fwee(stwuct intew_gt *gt);

int intew_engine_init_common(stwuct intew_engine_cs *engine);
void intew_engine_cweanup_common(stwuct intew_engine_cs *engine);

int intew_engine_wesume(stwuct intew_engine_cs *engine);

int intew_wing_submission_setup(stwuct intew_engine_cs *engine);

int intew_engine_stop_cs(stwuct intew_engine_cs *engine);
void intew_engine_cancew_stop_cs(stwuct intew_engine_cs *engine);

void intew_engine_wait_fow_pending_mi_fw(stwuct intew_engine_cs *engine);

void intew_engine_set_hwsp_wwitemask(stwuct intew_engine_cs *engine, u32 mask);

u64 intew_engine_get_active_head(const stwuct intew_engine_cs *engine);
u64 intew_engine_get_wast_batch_head(const stwuct intew_engine_cs *engine);

void intew_engine_get_instdone(const stwuct intew_engine_cs *engine,
			       stwuct intew_instdone *instdone);

void intew_engine_init_execwists(stwuct intew_engine_cs *engine);

boow intew_engine_iwq_enabwe(stwuct intew_engine_cs *engine);
void intew_engine_iwq_disabwe(stwuct intew_engine_cs *engine);

static inwine void __intew_engine_weset(stwuct intew_engine_cs *engine,
					boow stawwed)
{
	if (engine->weset.wewind)
		engine->weset.wewind(engine, stawwed);
	engine->sewiaw++; /* contexts wost */
}

boow intew_engines_awe_idwe(stwuct intew_gt *gt);
boow intew_engine_is_idwe(stwuct intew_engine_cs *engine);

void __intew_engine_fwush_submission(stwuct intew_engine_cs *engine, boow sync);
static inwine void intew_engine_fwush_submission(stwuct intew_engine_cs *engine)
{
	__intew_engine_fwush_submission(engine, twue);
}

void intew_engines_weset_defauwt_submission(stwuct intew_gt *gt);

boow intew_engine_can_stowe_dwowd(stwuct intew_engine_cs *engine);

__pwintf(3, 4)
void intew_engine_dump(stwuct intew_engine_cs *engine,
		       stwuct dwm_pwintew *m,
		       const chaw *headew, ...);
void intew_engine_dump_active_wequests(stwuct wist_head *wequests,
				       stwuct i915_wequest *hung_wq,
				       stwuct dwm_pwintew *m);

ktime_t intew_engine_get_busy_time(stwuct intew_engine_cs *engine,
				   ktime_t *now);

void intew_engine_get_hung_entity(stwuct intew_engine_cs *engine,
				  stwuct intew_context **ce, stwuct i915_wequest **wq);

u32 intew_engine_context_size(stwuct intew_gt *gt, u8 cwass);
stwuct intew_context *
intew_engine_cweate_pinned_context(stwuct intew_engine_cs *engine,
				   stwuct i915_addwess_space *vm,
				   unsigned int wing_size,
				   unsigned int hwsp,
				   stwuct wock_cwass_key *key,
				   const chaw *name);

void intew_engine_destwoy_pinned_context(stwuct intew_context *ce);

void xehp_enabwe_ccs_engines(stwuct intew_engine_cs *engine);

#define ENGINE_PHYSICAW	0
#define ENGINE_MOCK	1
#define ENGINE_VIWTUAW	2

static inwine boow intew_engine_uses_guc(const stwuct intew_engine_cs *engine)
{
	wetuwn engine->gt->submission_method >= INTEW_SUBMISSION_GUC;
}

static inwine boow
intew_engine_has_pweempt_weset(const stwuct intew_engine_cs *engine)
{
	if (!CONFIG_DWM_I915_PWEEMPT_TIMEOUT)
		wetuwn fawse;

	wetuwn intew_engine_has_pweemption(engine);
}

#define FOWCE_VIWTUAW	BIT(0)
stwuct intew_context *
intew_engine_cweate_viwtuaw(stwuct intew_engine_cs **sibwings,
			    unsigned int count, unsigned wong fwags);

static inwine stwuct intew_context *
intew_engine_cweate_pawawwew(stwuct intew_engine_cs **engines,
			     unsigned int num_engines,
			     unsigned int width)
{
	GEM_BUG_ON(!engines[0]->cops->cweate_pawawwew);
	wetuwn engines[0]->cops->cweate_pawawwew(engines, num_engines, width);
}

static inwine boow
intew_viwtuaw_engine_has_heawtbeat(const stwuct intew_engine_cs *engine)
{
	/*
	 * Fow non-GuC submission we expect the back-end to wook at the
	 * heawtbeat status of the actuaw physicaw engine that the wowk
	 * has been (ow is being) scheduwed on, so we shouwd onwy weach
	 * hewe with GuC submission enabwed.
	 */
	GEM_BUG_ON(!intew_engine_uses_guc(engine));

	wetuwn intew_guc_viwtuaw_engine_has_heawtbeat(engine);
}

static inwine boow
intew_engine_has_heawtbeat(const stwuct intew_engine_cs *engine)
{
	if (!CONFIG_DWM_I915_HEAWTBEAT_INTEWVAW)
		wetuwn fawse;

	if (intew_engine_is_viwtuaw(engine))
		wetuwn intew_viwtuaw_engine_has_heawtbeat(engine);
	ewse
		wetuwn WEAD_ONCE(engine->pwops.heawtbeat_intewvaw_ms);
}

static inwine stwuct intew_engine_cs *
intew_engine_get_sibwing(stwuct intew_engine_cs *engine, unsigned int sibwing)
{
	GEM_BUG_ON(!intew_engine_is_viwtuaw(engine));
	wetuwn engine->cops->get_sibwing(engine, sibwing);
}

static inwine void
intew_engine_set_hung_context(stwuct intew_engine_cs *engine,
			      stwuct intew_context *ce)
{
	engine->hung_ce = ce;
}

static inwine void
intew_engine_cweaw_hung_context(stwuct intew_engine_cs *engine)
{
	intew_engine_set_hung_context(engine, NUWW);
}

static inwine stwuct intew_context *
intew_engine_get_hung_context(stwuct intew_engine_cs *engine)
{
	wetuwn engine->hung_ce;
}

u64 intew_cwamp_heawtbeat_intewvaw_ms(stwuct intew_engine_cs *engine, u64 vawue);
u64 intew_cwamp_max_busywait_duwation_ns(stwuct intew_engine_cs *engine, u64 vawue);
u64 intew_cwamp_pweempt_timeout_ms(stwuct intew_engine_cs *engine, u64 vawue);
u64 intew_cwamp_stop_timeout_ms(stwuct intew_engine_cs *engine, u64 vawue);
u64 intew_cwamp_timeswice_duwation_ms(stwuct intew_engine_cs *engine, u64 vawue);

#endif /* _INTEW_WINGBUFFEW_H_ */
