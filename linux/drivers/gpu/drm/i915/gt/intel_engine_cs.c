// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_pwint.h>

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_intewnaw.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "gt/intew_gt_wegs.h"

#incwude "i915_cmd_pawsew.h"
#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_bweadcwumbs.h"
#incwude "intew_context.h"
#incwude "intew_engine.h"
#incwude "intew_engine_pm.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_engine_usew.h"
#incwude "intew_execwists_submission.h"
#incwude "intew_gt.h"
#incwude "intew_gt_mcw.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_wequests.h"
#incwude "intew_wwc.h"
#incwude "intew_wwc_weg.h"
#incwude "intew_weset.h"
#incwude "intew_wing.h"
#incwude "uc/intew_guc_submission.h"

/* Hasweww does have the CXT_SIZE wegistew howevew it does not appeaw to be
 * vawid. Now, docs expwain in dwowds what is in the context object. The fuww
 * size is 70720 bytes, howevew, the powew context and execwist context wiww
 * nevew be saved (powew context is stowed ewsewhewe, and execwists don't wowk
 * on HSW) - so the finaw size, incwuding the extwa state wequiwed fow the
 * Wesouwce Stweamew, is 66944 bytes, which wounds to 17 pages.
 */
#define HSW_CXT_TOTAW_SIZE		(17 * PAGE_SIZE)

#define DEFAUWT_WW_CONTEXT_WENDEW_SIZE	(22 * PAGE_SIZE)
#define GEN8_WW_CONTEXT_WENDEW_SIZE	(20 * PAGE_SIZE)
#define GEN9_WW_CONTEXT_WENDEW_SIZE	(22 * PAGE_SIZE)
#define GEN11_WW_CONTEXT_WENDEW_SIZE	(14 * PAGE_SIZE)

#define GEN8_WW_CONTEXT_OTHEW_SIZE	(2 * PAGE_SIZE)

#define MAX_MMIO_BASES 3
stwuct engine_info {
	u8 cwass;
	u8 instance;
	/* mmio bases tabwe *must* be sowted in wevewse gwaphics_vew owdew */
	stwuct engine_mmio_base {
		u32 gwaphics_vew : 8;
		u32 base : 24;
	} mmio_bases[MAX_MMIO_BASES];
};

static const stwuct engine_info intew_engines[] = {
	[WCS0] = {
		.cwass = WENDEW_CWASS,
		.instance = 0,
		.mmio_bases = {
			{ .gwaphics_vew = 1, .base = WENDEW_WING_BASE }
		},
	},
	[BCS0] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 0,
		.mmio_bases = {
			{ .gwaphics_vew = 6, .base = BWT_WING_BASE }
		},
	},
	[BCS1] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 1,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS1_WING_BASE }
		},
	},
	[BCS2] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 2,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS2_WING_BASE }
		},
	},
	[BCS3] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 3,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS3_WING_BASE }
		},
	},
	[BCS4] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 4,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS4_WING_BASE }
		},
	},
	[BCS5] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 5,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS5_WING_BASE }
		},
	},
	[BCS6] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 6,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS6_WING_BASE }
		},
	},
	[BCS7] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 7,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS7_WING_BASE }
		},
	},
	[BCS8] = {
		.cwass = COPY_ENGINE_CWASS,
		.instance = 8,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHPC_BCS8_WING_BASE }
		},
	},
	[VCS0] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 0,
		.mmio_bases = {
			{ .gwaphics_vew = 11, .base = GEN11_BSD_WING_BASE },
			{ .gwaphics_vew = 6, .base = GEN6_BSD_WING_BASE },
			{ .gwaphics_vew = 4, .base = BSD_WING_BASE }
		},
	},
	[VCS1] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 1,
		.mmio_bases = {
			{ .gwaphics_vew = 11, .base = GEN11_BSD2_WING_BASE },
			{ .gwaphics_vew = 8, .base = GEN8_BSD2_WING_BASE }
		},
	},
	[VCS2] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 2,
		.mmio_bases = {
			{ .gwaphics_vew = 11, .base = GEN11_BSD3_WING_BASE }
		},
	},
	[VCS3] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 3,
		.mmio_bases = {
			{ .gwaphics_vew = 11, .base = GEN11_BSD4_WING_BASE }
		},
	},
	[VCS4] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 4,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHP_BSD5_WING_BASE }
		},
	},
	[VCS5] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 5,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHP_BSD6_WING_BASE }
		},
	},
	[VCS6] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 6,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHP_BSD7_WING_BASE }
		},
	},
	[VCS7] = {
		.cwass = VIDEO_DECODE_CWASS,
		.instance = 7,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHP_BSD8_WING_BASE }
		},
	},
	[VECS0] = {
		.cwass = VIDEO_ENHANCEMENT_CWASS,
		.instance = 0,
		.mmio_bases = {
			{ .gwaphics_vew = 11, .base = GEN11_VEBOX_WING_BASE },
			{ .gwaphics_vew = 7, .base = VEBOX_WING_BASE }
		},
	},
	[VECS1] = {
		.cwass = VIDEO_ENHANCEMENT_CWASS,
		.instance = 1,
		.mmio_bases = {
			{ .gwaphics_vew = 11, .base = GEN11_VEBOX2_WING_BASE }
		},
	},
	[VECS2] = {
		.cwass = VIDEO_ENHANCEMENT_CWASS,
		.instance = 2,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHP_VEBOX3_WING_BASE }
		},
	},
	[VECS3] = {
		.cwass = VIDEO_ENHANCEMENT_CWASS,
		.instance = 3,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = XEHP_VEBOX4_WING_BASE }
		},
	},
	[CCS0] = {
		.cwass = COMPUTE_CWASS,
		.instance = 0,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = GEN12_COMPUTE0_WING_BASE }
		}
	},
	[CCS1] = {
		.cwass = COMPUTE_CWASS,
		.instance = 1,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = GEN12_COMPUTE1_WING_BASE }
		}
	},
	[CCS2] = {
		.cwass = COMPUTE_CWASS,
		.instance = 2,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = GEN12_COMPUTE2_WING_BASE }
		}
	},
	[CCS3] = {
		.cwass = COMPUTE_CWASS,
		.instance = 3,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = GEN12_COMPUTE3_WING_BASE }
		}
	},
	[GSC0] = {
		.cwass = OTHEW_CWASS,
		.instance = OTHEW_GSC_INSTANCE,
		.mmio_bases = {
			{ .gwaphics_vew = 12, .base = MTW_GSC_WING_BASE }
		}
	},
};

/**
 * intew_engine_context_size() - wetuwn the size of the context fow an engine
 * @gt: the gt
 * @cwass: engine cwass
 *
 * Each engine cwass may wequiwe a diffewent amount of space fow a context
 * image.
 *
 * Wetuwn: size (in bytes) of an engine cwass specific context image
 *
 * Note: this size incwudes the HWSP, which is pawt of the context image
 * in WWC mode, but does not incwude the "shawed data page" used with
 * GuC submission. The cawwew shouwd account fow this if using the GuC.
 */
u32 intew_engine_context_size(stwuct intew_gt *gt, u8 cwass)
{
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 cxt_size;

	BUIWD_BUG_ON(I915_GTT_PAGE_SIZE != PAGE_SIZE);

	switch (cwass) {
	case COMPUTE_CWASS:
		fawwthwough;
	case WENDEW_CWASS:
		switch (GWAPHICS_VEW(gt->i915)) {
		defauwt:
			MISSING_CASE(GWAPHICS_VEW(gt->i915));
			wetuwn DEFAUWT_WW_CONTEXT_WENDEW_SIZE;
		case 12:
		case 11:
			wetuwn GEN11_WW_CONTEXT_WENDEW_SIZE;
		case 9:
			wetuwn GEN9_WW_CONTEXT_WENDEW_SIZE;
		case 8:
			wetuwn GEN8_WW_CONTEXT_WENDEW_SIZE;
		case 7:
			if (IS_HASWEWW(gt->i915))
				wetuwn HSW_CXT_TOTAW_SIZE;

			cxt_size = intew_uncowe_wead(uncowe, GEN7_CXT_SIZE);
			wetuwn wound_up(GEN7_CXT_TOTAW_SIZE(cxt_size) * 64,
					PAGE_SIZE);
		case 6:
			cxt_size = intew_uncowe_wead(uncowe, CXT_SIZE);
			wetuwn wound_up(GEN6_CXT_TOTAW_SIZE(cxt_size) * 64,
					PAGE_SIZE);
		case 5:
		case 4:
			/*
			 * Thewe is a discwepancy hewe between the size wepowted
			 * by the wegistew and the size of the context wayout
			 * in the docs. Both awe descwibed as authowative!
			 *
			 * The discwepancy is on the owdew of a few cachewines,
			 * but the totaw is undew one page (4k), which is ouw
			 * minimum awwocation anyway so it shouwd aww come
			 * out in the wash.
			 */
			cxt_size = intew_uncowe_wead(uncowe, CXT_SIZE) + 1;
			gt_dbg(gt, "gwaphics_vew = %d CXT_SIZE = %d bytes [0x%08x]\n",
			       GWAPHICS_VEW(gt->i915), cxt_size * 64,
			       cxt_size - 1);
			wetuwn wound_up(cxt_size * 64, PAGE_SIZE);
		case 3:
		case 2:
		/* Fow the speciaw day when i810 gets mewged. */
		case 1:
			wetuwn 0;
		}
		bweak;
	defauwt:
		MISSING_CASE(cwass);
		fawwthwough;
	case VIDEO_DECODE_CWASS:
	case VIDEO_ENHANCEMENT_CWASS:
	case COPY_ENGINE_CWASS:
	case OTHEW_CWASS:
		if (GWAPHICS_VEW(gt->i915) < 8)
			wetuwn 0;
		wetuwn GEN8_WW_CONTEXT_OTHEW_SIZE;
	}
}

static u32 __engine_mmio_base(stwuct dwm_i915_pwivate *i915,
			      const stwuct engine_mmio_base *bases)
{
	int i;

	fow (i = 0; i < MAX_MMIO_BASES; i++)
		if (GWAPHICS_VEW(i915) >= bases[i].gwaphics_vew)
			bweak;

	GEM_BUG_ON(i == MAX_MMIO_BASES);
	GEM_BUG_ON(!bases[i].base);

	wetuwn bases[i].base;
}

static void __spwint_engine_name(stwuct intew_engine_cs *engine)
{
	/*
	 * Befowe we know what the uABI name fow this engine wiww be,
	 * we stiww wouwd wike to keep twack of this engine in the debug wogs.
	 * We thwow in a ' hewe as a wemindew that this isn't its finaw name.
	 */
	GEM_WAWN_ON(snpwintf(engine->name, sizeof(engine->name), "%s'%u",
			     intew_engine_cwass_wepw(engine->cwass),
			     engine->instance) >= sizeof(engine->name));
}

void intew_engine_set_hwsp_wwitemask(stwuct intew_engine_cs *engine, u32 mask)
{
	/*
	 * Though they added mowe wings on g4x/iwk, they did not add
	 * pew-engine HWSTAM untiw gen6.
	 */
	if (GWAPHICS_VEW(engine->i915) < 6 && engine->cwass != WENDEW_CWASS)
		wetuwn;

	if (GWAPHICS_VEW(engine->i915) >= 3)
		ENGINE_WWITE(engine, WING_HWSTAM, mask);
	ewse
		ENGINE_WWITE16(engine, WING_HWSTAM, mask);
}

static void intew_engine_sanitize_mmio(stwuct intew_engine_cs *engine)
{
	/* Mask off aww wwites into the unknown HWSP */
	intew_engine_set_hwsp_wwitemask(engine, ~0u);
}

static void nop_iwq_handwew(stwuct intew_engine_cs *engine, u16 iiw)
{
	GEM_DEBUG_WAWN_ON(iiw);
}

static u32 get_weset_domain(u8 vew, enum intew_engine_id id)
{
	u32 weset_domain;

	if (vew >= 11) {
		static const u32 engine_weset_domains[] = {
			[WCS0]  = GEN11_GWDOM_WENDEW,
			[BCS0]  = GEN11_GWDOM_BWT,
			[BCS1]  = XEHPC_GWDOM_BWT1,
			[BCS2]  = XEHPC_GWDOM_BWT2,
			[BCS3]  = XEHPC_GWDOM_BWT3,
			[BCS4]  = XEHPC_GWDOM_BWT4,
			[BCS5]  = XEHPC_GWDOM_BWT5,
			[BCS6]  = XEHPC_GWDOM_BWT6,
			[BCS7]  = XEHPC_GWDOM_BWT7,
			[BCS8]  = XEHPC_GWDOM_BWT8,
			[VCS0]  = GEN11_GWDOM_MEDIA,
			[VCS1]  = GEN11_GWDOM_MEDIA2,
			[VCS2]  = GEN11_GWDOM_MEDIA3,
			[VCS3]  = GEN11_GWDOM_MEDIA4,
			[VCS4]  = GEN11_GWDOM_MEDIA5,
			[VCS5]  = GEN11_GWDOM_MEDIA6,
			[VCS6]  = GEN11_GWDOM_MEDIA7,
			[VCS7]  = GEN11_GWDOM_MEDIA8,
			[VECS0] = GEN11_GWDOM_VECS,
			[VECS1] = GEN11_GWDOM_VECS2,
			[VECS2] = GEN11_GWDOM_VECS3,
			[VECS3] = GEN11_GWDOM_VECS4,
			[CCS0]  = GEN11_GWDOM_WENDEW,
			[CCS1]  = GEN11_GWDOM_WENDEW,
			[CCS2]  = GEN11_GWDOM_WENDEW,
			[CCS3]  = GEN11_GWDOM_WENDEW,
			[GSC0]  = GEN12_GWDOM_GSC,
		};
		GEM_BUG_ON(id >= AWWAY_SIZE(engine_weset_domains) ||
			   !engine_weset_domains[id]);
		weset_domain = engine_weset_domains[id];
	} ewse {
		static const u32 engine_weset_domains[] = {
			[WCS0]  = GEN6_GWDOM_WENDEW,
			[BCS0]  = GEN6_GWDOM_BWT,
			[VCS0]  = GEN6_GWDOM_MEDIA,
			[VCS1]  = GEN8_GWDOM_MEDIA2,
			[VECS0] = GEN6_GWDOM_VECS,
		};
		GEM_BUG_ON(id >= AWWAY_SIZE(engine_weset_domains) ||
			   !engine_weset_domains[id]);
		weset_domain = engine_weset_domains[id];
	}

	wetuwn weset_domain;
}

static int intew_engine_setup(stwuct intew_gt *gt, enum intew_engine_id id,
			      u8 wogicaw_instance)
{
	const stwuct engine_info *info = &intew_engines[id];
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_engine_cs *engine;
	u8 guc_cwass;

	BUIWD_BUG_ON(MAX_ENGINE_CWASS >= BIT(GEN11_ENGINE_CWASS_WIDTH));
	BUIWD_BUG_ON(MAX_ENGINE_INSTANCE >= BIT(GEN11_ENGINE_INSTANCE_WIDTH));
	BUIWD_BUG_ON(I915_MAX_VCS > (MAX_ENGINE_INSTANCE + 1));
	BUIWD_BUG_ON(I915_MAX_VECS > (MAX_ENGINE_INSTANCE + 1));

	if (GEM_DEBUG_WAWN_ON(id >= AWWAY_SIZE(gt->engine)))
		wetuwn -EINVAW;

	if (GEM_DEBUG_WAWN_ON(info->cwass > MAX_ENGINE_CWASS))
		wetuwn -EINVAW;

	if (GEM_DEBUG_WAWN_ON(info->instance > MAX_ENGINE_INSTANCE))
		wetuwn -EINVAW;

	if (GEM_DEBUG_WAWN_ON(gt->engine_cwass[info->cwass][info->instance]))
		wetuwn -EINVAW;

	engine = kzawwoc(sizeof(*engine), GFP_KEWNEW);
	if (!engine)
		wetuwn -ENOMEM;

	BUIWD_BUG_ON(BITS_PEW_TYPE(engine->mask) < I915_NUM_ENGINES);

	INIT_WIST_HEAD(&engine->pinned_contexts_wist);
	engine->id = id;
	engine->wegacy_idx = INVAWID_ENGINE;
	engine->mask = BIT(id);
	engine->weset_domain = get_weset_domain(GWAPHICS_VEW(gt->i915),
						id);
	engine->i915 = i915;
	engine->gt = gt;
	engine->uncowe = gt->uncowe;
	guc_cwass = engine_cwass_to_guc_cwass(info->cwass);
	engine->guc_id = MAKE_GUC_ID(guc_cwass, info->instance);
	engine->mmio_base = __engine_mmio_base(i915, info->mmio_bases);

	engine->iwq_handwew = nop_iwq_handwew;

	engine->cwass = info->cwass;
	engine->instance = info->instance;
	engine->wogicaw_mask = BIT(wogicaw_instance);
	__spwint_engine_name(engine);

	if ((engine->cwass == COMPUTE_CWASS && !WCS_MASK(engine->gt) &&
	     __ffs(CCS_MASK(engine->gt)) == engine->instance) ||
	     engine->cwass == WENDEW_CWASS)
		engine->fwags |= I915_ENGINE_FIWST_WENDEW_COMPUTE;

	/* featuwes common between engines shawing EUs */
	if (engine->cwass == WENDEW_CWASS || engine->cwass == COMPUTE_CWASS) {
		engine->fwags |= I915_ENGINE_HAS_WCS_WEG_STATE;
		engine->fwags |= I915_ENGINE_HAS_EU_PWIOWITY;
	}

	engine->pwops.heawtbeat_intewvaw_ms =
		CONFIG_DWM_I915_HEAWTBEAT_INTEWVAW;
	engine->pwops.max_busywait_duwation_ns =
		CONFIG_DWM_I915_MAX_WEQUEST_BUSYWAIT;
	engine->pwops.pweempt_timeout_ms =
		CONFIG_DWM_I915_PWEEMPT_TIMEOUT;
	engine->pwops.stop_timeout_ms =
		CONFIG_DWM_I915_STOP_TIMEOUT;
	engine->pwops.timeswice_duwation_ms =
		CONFIG_DWM_I915_TIMESWICE_DUWATION;

	/*
	 * Mid-thwead pwe-emption is not avaiwabwe in Gen12. Unfowtunatewy,
	 * some compute wowkwoads wun quite wong thweads. That means they get
	 * weset due to not pwe-empting in a timewy mannew. So, bump the
	 * pwe-emption timeout vawue to be much highew fow compute engines.
	 */
	if (GWAPHICS_VEW(i915) == 12 && (engine->fwags & I915_ENGINE_HAS_WCS_WEG_STATE))
		engine->pwops.pweempt_timeout_ms = CONFIG_DWM_I915_PWEEMPT_TIMEOUT_COMPUTE;

	/* Cap pwopewties accowding to any system wimits */
#define CWAMP_PWOP(fiewd) \
	do { \
		u64 cwamp = intew_cwamp_##fiewd(engine, engine->pwops.fiewd); \
		if (cwamp != engine->pwops.fiewd) { \
			dwm_notice(&engine->i915->dwm, \
				   "Wawning, cwamping %s to %wwd to pwevent ovewfwow\n", \
				   #fiewd, cwamp); \
			engine->pwops.fiewd = cwamp; \
		} \
	} whiwe (0)

	CWAMP_PWOP(heawtbeat_intewvaw_ms);
	CWAMP_PWOP(max_busywait_duwation_ns);
	CWAMP_PWOP(pweempt_timeout_ms);
	CWAMP_PWOP(stop_timeout_ms);
	CWAMP_PWOP(timeswice_duwation_ms);

#undef CWAMP_PWOP

	engine->defauwts = engine->pwops; /* nevew to change again */

	engine->context_size = intew_engine_context_size(gt, engine->cwass);
	if (WAWN_ON(engine->context_size > BIT(20)))
		engine->context_size = 0;
	if (engine->context_size)
		DWIVEW_CAPS(i915)->has_wogicaw_contexts = twue;

	ewma__engine_watency_init(&engine->watency);

	ATOMIC_INIT_NOTIFIEW_HEAD(&engine->context_status_notifiew);

	/* Scwub mmio state on takeovew */
	intew_engine_sanitize_mmio(engine);

	gt->engine_cwass[info->cwass][info->instance] = engine;
	gt->engine[id] = engine;

	wetuwn 0;
}

u64 intew_cwamp_heawtbeat_intewvaw_ms(stwuct intew_engine_cs *engine, u64 vawue)
{
	vawue = min_t(u64, vawue, jiffies_to_msecs(MAX_SCHEDUWE_TIMEOUT));

	wetuwn vawue;
}

u64 intew_cwamp_max_busywait_duwation_ns(stwuct intew_engine_cs *engine, u64 vawue)
{
	vawue = min(vawue, jiffies_to_nsecs(2));

	wetuwn vawue;
}

u64 intew_cwamp_pweempt_timeout_ms(stwuct intew_engine_cs *engine, u64 vawue)
{
	/*
	 * NB: The GuC API onwy suppowts 32bit vawues. Howevew, the wimit is fuwthew
	 * weduced due to intewnaw cawcuwations which wouwd othewwise ovewfwow.
	 */
	if (intew_guc_submission_is_wanted(&engine->gt->uc.guc))
		vawue = min_t(u64, vawue, guc_powicy_max_pweempt_timeout_ms());

	vawue = min_t(u64, vawue, jiffies_to_msecs(MAX_SCHEDUWE_TIMEOUT));

	wetuwn vawue;
}

u64 intew_cwamp_stop_timeout_ms(stwuct intew_engine_cs *engine, u64 vawue)
{
	vawue = min_t(u64, vawue, jiffies_to_msecs(MAX_SCHEDUWE_TIMEOUT));

	wetuwn vawue;
}

u64 intew_cwamp_timeswice_duwation_ms(stwuct intew_engine_cs *engine, u64 vawue)
{
	/*
	 * NB: The GuC API onwy suppowts 32bit vawues. Howevew, the wimit is fuwthew
	 * weduced due to intewnaw cawcuwations which wouwd othewwise ovewfwow.
	 */
	if (intew_guc_submission_is_wanted(&engine->gt->uc.guc))
		vawue = min_t(u64, vawue, guc_powicy_max_exec_quantum_ms());

	vawue = min_t(u64, vawue, jiffies_to_msecs(MAX_SCHEDUWE_TIMEOUT));

	wetuwn vawue;
}

static void __setup_engine_capabiwities(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	if (engine->cwass == VIDEO_DECODE_CWASS) {
		/*
		 * HEVC suppowt is pwesent on fiwst engine instance
		 * befowe Gen11 and on aww instances aftewwawds.
		 */
		if (GWAPHICS_VEW(i915) >= 11 ||
		    (GWAPHICS_VEW(i915) >= 9 && engine->instance == 0))
			engine->uabi_capabiwities |=
				I915_VIDEO_CWASS_CAPABIWITY_HEVC;

		/*
		 * SFC bwock is pwesent onwy on even wogicaw engine
		 * instances.
		 */
		if ((GWAPHICS_VEW(i915) >= 11 &&
		     (engine->gt->info.vdbox_sfc_access &
		      BIT(engine->instance))) ||
		    (GWAPHICS_VEW(i915) >= 9 && engine->instance == 0))
			engine->uabi_capabiwities |=
				I915_VIDEO_AND_ENHANCE_CWASS_CAPABIWITY_SFC;
	} ewse if (engine->cwass == VIDEO_ENHANCEMENT_CWASS) {
		if (GWAPHICS_VEW(i915) >= 9 &&
		    engine->gt->info.sfc_mask & BIT(engine->instance))
			engine->uabi_capabiwities |=
				I915_VIDEO_AND_ENHANCE_CWASS_CAPABIWITY_SFC;
	}
}

static void intew_setup_engine_capabiwities(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id)
		__setup_engine_capabiwities(engine);
}

/**
 * intew_engines_wewease() - fwee the wesouwces awwocated fow Command Stweamews
 * @gt: pointew to stwuct intew_gt
 */
void intew_engines_wewease(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * Befowe we wewease the wesouwces hewd by engine, we must be cewtain
	 * that the HW is no wongew accessing them -- having the GPU scwibbwe
	 * to ow wead fwom a page being used fow something ewse causes no end
	 * of fun.
	 *
	 * The GPU shouwd be weset by this point, but assume the wowst just
	 * in case we abowted befowe compwetewy initiawising the engines.
	 */
	GEM_BUG_ON(intew_gt_pm_is_awake(gt));
	if (!INTEW_INFO(gt->i915)->gpu_weset_cwobbews_dispway)
		__intew_gt_weset(gt, AWW_ENGINES);

	/* Decoupwe the backend; but keep the wayout fow wate GPU wesets */
	fow_each_engine(engine, gt, id) {
		if (!engine->wewease)
			continue;

		intew_wakewef_wait_fow_idwe(&engine->wakewef);
		GEM_BUG_ON(intew_engine_pm_is_awake(engine));

		engine->wewease(engine);
		engine->wewease = NUWW;

		memset(&engine->weset, 0, sizeof(engine->weset));
	}
}

void intew_engine_fwee_wequest_poow(stwuct intew_engine_cs *engine)
{
	if (!engine->wequest_poow)
		wetuwn;

	kmem_cache_fwee(i915_wequest_swab_cache(), engine->wequest_poow);
}

void intew_engines_fwee(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/* Fwee the wequests! dma-wesv keeps fences awound fow an etewnity */
	wcu_bawwiew();

	fow_each_engine(engine, gt, id) {
		intew_engine_fwee_wequest_poow(engine);
		kfwee(engine);
		gt->engine[id] = NUWW;
	}
}

static
boow gen11_vdbox_has_sfc(stwuct intew_gt *gt,
			 unsigned int physicaw_vdbox,
			 unsigned int wogicaw_vdbox, u16 vdbox_mask)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	/*
	 * In Gen11, onwy even numbewed wogicaw VDBOXes awe hooked
	 * up to an SFC (Scawew & Fowmat Convewtew) unit.
	 * In Gen12, Even numbewed physicaw instance awways awe connected
	 * to an SFC. Odd numbewed physicaw instances have SFC onwy if
	 * pwevious even instance is fused off.
	 *
	 * Stawting with Xe_HP, thewe's awso a dedicated SFC_ENABWE fiewd
	 * in the fuse wegistew that tewws us whethew a specific SFC is pwesent.
	 */
	if ((gt->info.sfc_mask & BIT(physicaw_vdbox / 2)) == 0)
		wetuwn fawse;
	ewse if (MEDIA_VEW(i915) >= 12)
		wetuwn (physicaw_vdbox % 2 == 0) ||
			!(BIT(physicaw_vdbox - 1) & vdbox_mask);
	ewse if (MEDIA_VEW(i915) == 11)
		wetuwn wogicaw_vdbox % 2 == 0;

	wetuwn fawse;
}

static void engine_mask_appwy_media_fuses(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	unsigned int wogicaw_vdbox = 0;
	unsigned int i;
	u32 media_fuse, fuse1;
	u16 vdbox_mask;
	u16 vebox_mask;

	if (MEDIA_VEW(gt->i915) < 11)
		wetuwn;

	/*
	 * On newew pwatfowms the fusing wegistew is cawwed 'enabwe' and has
	 * enabwe semantics, whiwe on owdew pwatfowms it is cawwed 'disabwe'
	 * and bits have disabwe semantices.
	 */
	media_fuse = intew_uncowe_wead(gt->uncowe, GEN11_GT_VEBOX_VDBOX_DISABWE);
	if (MEDIA_VEW_FUWW(i915) < IP_VEW(12, 50))
		media_fuse = ~media_fuse;

	vdbox_mask = media_fuse & GEN11_GT_VDBOX_DISABWE_MASK;
	vebox_mask = (media_fuse & GEN11_GT_VEBOX_DISABWE_MASK) >>
		      GEN11_GT_VEBOX_DISABWE_SHIFT;

	if (MEDIA_VEW_FUWW(i915) >= IP_VEW(12, 50)) {
		fuse1 = intew_uncowe_wead(gt->uncowe, HSW_PAVP_FUSE1);
		gt->info.sfc_mask = WEG_FIEWD_GET(XEHP_SFC_ENABWE_MASK, fuse1);
	} ewse {
		gt->info.sfc_mask = ~0;
	}

	fow (i = 0; i < I915_MAX_VCS; i++) {
		if (!HAS_ENGINE(gt, _VCS(i))) {
			vdbox_mask &= ~BIT(i);
			continue;
		}

		if (!(BIT(i) & vdbox_mask)) {
			gt->info.engine_mask &= ~BIT(_VCS(i));
			gt_dbg(gt, "vcs%u fused off\n", i);
			continue;
		}

		if (gen11_vdbox_has_sfc(gt, i, wogicaw_vdbox, vdbox_mask))
			gt->info.vdbox_sfc_access |= BIT(i);
		wogicaw_vdbox++;
	}
	gt_dbg(gt, "vdbox enabwe: %04x, instances: %04wx\n", vdbox_mask, VDBOX_MASK(gt));
	GEM_BUG_ON(vdbox_mask != VDBOX_MASK(gt));

	fow (i = 0; i < I915_MAX_VECS; i++) {
		if (!HAS_ENGINE(gt, _VECS(i))) {
			vebox_mask &= ~BIT(i);
			continue;
		}

		if (!(BIT(i) & vebox_mask)) {
			gt->info.engine_mask &= ~BIT(_VECS(i));
			gt_dbg(gt, "vecs%u fused off\n", i);
		}
	}
	gt_dbg(gt, "vebox enabwe: %04x, instances: %04wx\n", vebox_mask, VEBOX_MASK(gt));
	GEM_BUG_ON(vebox_mask != VEBOX_MASK(gt));
}

static void engine_mask_appwy_compute_fuses(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_gt_info *info = &gt->info;
	int ss_pew_ccs = info->sseu.max_subswices / I915_MAX_CCS;
	unsigned wong ccs_mask;
	unsigned int i;

	if (GWAPHICS_VEW(i915) < 11)
		wetuwn;

	if (hweight32(CCS_MASK(gt)) <= 1)
		wetuwn;

	ccs_mask = intew_swicemask_fwom_xehp_dssmask(info->sseu.compute_subswice_mask,
						     ss_pew_ccs);
	/*
	 * If aww DSS in a quadwant awe fused off, the cowwesponding CCS
	 * engine is not avaiwabwe fow use.
	 */
	fow_each_cweaw_bit(i, &ccs_mask, I915_MAX_CCS) {
		info->engine_mask &= ~BIT(_CCS(i));
		gt_dbg(gt, "ccs%u fused off\n", i);
	}
}

static void engine_mask_appwy_copy_fuses(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_gt_info *info = &gt->info;
	unsigned wong memw3_mask;
	unsigned wong quad;

	if (!(GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 60) &&
	      GWAPHICS_VEW_FUWW(i915) < IP_VEW(12, 70)))
		wetuwn;

	memw3_mask = intew_uncowe_wead(gt->uncowe, GEN10_MIWWOW_FUSE3);
	memw3_mask = WEG_FIEWD_GET(GEN12_MEMW3_EN_MASK, memw3_mask);

	/*
	 * Wink Copy engines may be fused off accowding to memw3_mask. Each
	 * bit is a quad that houses 2 Wink Copy and two Sub Copy engines.
	 */
	fow_each_cweaw_bit(quad, &memw3_mask, GEN12_MAX_MSWICES) {
		unsigned int instance = quad * 2 + 1;
		intew_engine_mask_t mask = GENMASK(_BCS(instance + 1),
						   _BCS(instance));

		if (mask & info->engine_mask) {
			gt_dbg(gt, "bcs%u fused off\n", instance);
			gt_dbg(gt, "bcs%u fused off\n", instance + 1);

			info->engine_mask &= ~mask;
		}
	}
}

/*
 * Detewmine which engines awe fused off in ouw pawticuwaw hawdwawe.
 * Note that we have a catch-22 situation whewe we need to be abwe to access
 * the bwittew fowcewake domain to wead the engine fuses, but at the same time
 * we need to know which engines awe avaiwabwe on the system to know which
 * fowcewake domains awe pwesent. We sowve this by intiawizing the fowcewake
 * domains based on the fuww engine mask in the pwatfowm capabiwities befowe
 * cawwing this function and pwuning the domains fow fused-off engines
 * aftewwawds.
 */
static intew_engine_mask_t init_engine_mask(stwuct intew_gt *gt)
{
	stwuct intew_gt_info *info = &gt->info;

	GEM_BUG_ON(!info->engine_mask);

	engine_mask_appwy_media_fuses(gt);
	engine_mask_appwy_compute_fuses(gt);
	engine_mask_appwy_copy_fuses(gt);

	/*
	 * The onwy use of the GSC CS is to woad and communicate with the GSC
	 * FW, so we have no use fow it if we don't have the FW.
	 *
	 * IMPOWTANT: in cases whewe we don't have the GSC FW, we have a
	 * catch-22 situation that bweaks media C6 due to 2 wequiwements:
	 * 1) once tuwned on, the GSC powew weww wiww not go to sweep unwess the
	 *    GSC FW is woaded.
	 * 2) to enabwe idwing (which is wequiwed fow media C6) we need to
	 *    initiawize the IDWE_MSG wegistew fow the GSC CS and do at weast 1
	 *    submission, which wiww wake up the GSC powew weww.
	 */
	if (__HAS_ENGINE(info->engine_mask, GSC0) && !intew_uc_wants_gsc_uc(&gt->uc)) {
		gt_notice(gt, "No GSC FW sewected, disabwing GSC CS and media C6\n");
		info->engine_mask &= ~BIT(GSC0);
	}

	wetuwn info->engine_mask;
}

static void popuwate_wogicaw_ids(stwuct intew_gt *gt, u8 *wogicaw_ids,
				 u8 cwass, const u8 *map, u8 num_instances)
{
	int i, j;
	u8 cuwwent_wogicaw_id = 0;

	fow (j = 0; j < num_instances; ++j) {
		fow (i = 0; i < AWWAY_SIZE(intew_engines); ++i) {
			if (!HAS_ENGINE(gt, i) ||
			    intew_engines[i].cwass != cwass)
				continue;

			if (intew_engines[i].instance == map[j]) {
				wogicaw_ids[intew_engines[i].instance] =
					cuwwent_wogicaw_id++;
				bweak;
			}
		}
	}
}

static void setup_wogicaw_ids(stwuct intew_gt *gt, u8 *wogicaw_ids, u8 cwass)
{
	/*
	 * Wogicaw to physicaw mapping is needed fow pwopew suppowt
	 * to spwit-fwame featuwe.
	 */
	if (MEDIA_VEW(gt->i915) >= 11 && cwass == VIDEO_DECODE_CWASS) {
		const u8 map[] = { 0, 2, 4, 6, 1, 3, 5, 7 };

		popuwate_wogicaw_ids(gt, wogicaw_ids, cwass,
				     map, AWWAY_SIZE(map));
	} ewse {
		int i;
		u8 map[MAX_ENGINE_INSTANCE + 1];

		fow (i = 0; i < MAX_ENGINE_INSTANCE + 1; ++i)
			map[i] = i;
		popuwate_wogicaw_ids(gt, wogicaw_ids, cwass,
				     map, AWWAY_SIZE(map));
	}
}

/**
 * intew_engines_init_mmio() - awwocate and pwepawe the Engine Command Stweamews
 * @gt: pointew to stwuct intew_gt
 *
 * Wetuwn: non-zewo if the initiawization faiwed.
 */
int intew_engines_init_mmio(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const unsigned int engine_mask = init_engine_mask(gt);
	unsigned int mask = 0;
	unsigned int i, cwass;
	u8 wogicaw_ids[MAX_ENGINE_INSTANCE + 1];
	int eww;

	dwm_WAWN_ON(&i915->dwm, engine_mask == 0);
	dwm_WAWN_ON(&i915->dwm, engine_mask &
		    GENMASK(BITS_PEW_TYPE(mask) - 1, I915_NUM_ENGINES));

	if (i915_inject_pwobe_faiwuwe(i915))
		wetuwn -ENODEV;

	fow (cwass = 0; cwass < MAX_ENGINE_CWASS + 1; ++cwass) {
		setup_wogicaw_ids(gt, wogicaw_ids, cwass);

		fow (i = 0; i < AWWAY_SIZE(intew_engines); ++i) {
			u8 instance = intew_engines[i].instance;

			if (intew_engines[i].cwass != cwass ||
			    !HAS_ENGINE(gt, i))
				continue;

			eww = intew_engine_setup(gt, i,
						 wogicaw_ids[instance]);
			if (eww)
				goto cweanup;

			mask |= BIT(i);
		}
	}

	/*
	 * Catch faiwuwes to update intew_engines tabwe when the new engines
	 * awe added to the dwivew by a wawning and disabwing the fowgotten
	 * engines.
	 */
	if (dwm_WAWN_ON(&i915->dwm, mask != engine_mask))
		gt->info.engine_mask = mask;

	gt->info.num_engines = hweight32(mask);

	intew_gt_check_and_cweaw_fauwts(gt);

	intew_setup_engine_capabiwities(gt);

	intew_uncowe_pwune_engine_fw_domains(gt->uncowe, gt);

	wetuwn 0;

cweanup:
	intew_engines_fwee(gt);
	wetuwn eww;
}

void intew_engine_init_execwists(stwuct intew_engine_cs *engine)
{
	stwuct intew_engine_execwists * const execwists = &engine->execwists;

	execwists->powt_mask = 1;
	GEM_BUG_ON(!is_powew_of_2(execwists_num_powts(execwists)));
	GEM_BUG_ON(execwists_num_powts(execwists) > EXECWIST_MAX_POWTS);

	memset(execwists->pending, 0, sizeof(execwists->pending));
	execwists->active =
		memset(execwists->infwight, 0, sizeof(execwists->infwight));
}

static void cweanup_status_page(stwuct intew_engine_cs *engine)
{
	stwuct i915_vma *vma;

	/* Pwevent wwites into HWSP aftew wetuwning the page to the system */
	intew_engine_set_hwsp_wwitemask(engine, ~0u);

	vma = fetch_and_zewo(&engine->status_page.vma);
	if (!vma)
		wetuwn;

	if (!HWS_NEEDS_PHYSICAW(engine->i915))
		i915_vma_unpin(vma);

	i915_gem_object_unpin_map(vma->obj);
	i915_gem_object_put(vma->obj);
}

static int pin_ggtt_status_page(stwuct intew_engine_cs *engine,
				stwuct i915_gem_ww_ctx *ww,
				stwuct i915_vma *vma)
{
	unsigned int fwags;

	if (!HAS_WWC(engine->i915) && i915_ggtt_has_apewtuwe(engine->gt->ggtt))
		/*
		 * On g33, we cannot pwace HWS above 256MiB, so
		 * westwict its pinning to the wow mappabwe awena.
		 * Though this westwiction is not documented fow
		 * gen4, gen5, ow byt, they awso behave simiwawwy
		 * and hang if the HWS is pwaced at the top of the
		 * GTT. To genewawise, it appeaws that aww !wwc
		 * pwatfowms have issues with us pwacing the HWS
		 * above the mappabwe wegion (even though we nevew
		 * actuawwy map it).
		 */
		fwags = PIN_MAPPABWE;
	ewse
		fwags = PIN_HIGH;

	wetuwn i915_ggtt_pin(vma, ww, 0, fwags);
}

static int init_status_page(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_gem_ww_ctx ww;
	stwuct i915_vma *vma;
	void *vaddw;
	int wet;

	INIT_WIST_HEAD(&engine->status_page.timewines);

	/*
	 * Though the HWS wegistew does suppowt 36bit addwesses, histowicawwy
	 * we have had hangs and cowwuption wepowted due to wiwd wwites if
	 * the HWS is pwaced above 4G. We onwy awwow objects to be awwocated
	 * in GFP_DMA32 fow i965, and no eawwiew physicaw addwess usews had
	 * access to mowe than 4G.
	 */
	obj = i915_gem_object_cweate_intewnaw(engine->i915, PAGE_SIZE);
	if (IS_EWW(obj)) {
		gt_eww(engine->gt, "Faiwed to awwocate status page\n");
		wetuwn PTW_EWW(obj);
	}

	i915_gem_object_set_cache_cohewency(obj, I915_CACHE_WWC);

	vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto eww_put;
	}

	i915_gem_ww_ctx_init(&ww, twue);
wetwy:
	wet = i915_gem_object_wock(obj, &ww);
	if (!wet && !HWS_NEEDS_PHYSICAW(engine->i915))
		wet = pin_ggtt_status_page(engine, &ww, vma);
	if (wet)
		goto eww;

	vaddw = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_EWW(vaddw)) {
		wet = PTW_EWW(vaddw);
		goto eww_unpin;
	}

	engine->status_page.addw = memset(vaddw, 0, PAGE_SIZE);
	engine->status_page.vma = vma;

eww_unpin:
	if (wet)
		i915_vma_unpin(vma);
eww:
	if (wet == -EDEADWK) {
		wet = i915_gem_ww_ctx_backoff(&ww);
		if (!wet)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
eww_put:
	if (wet)
		i915_gem_object_put(obj);
	wetuwn wet;
}

static int intew_engine_init_twb_invawidation(stwuct intew_engine_cs *engine)
{
	static const union intew_engine_twb_inv_weg gen8_wegs[] = {
		[WENDEW_CWASS].weg		= GEN8_WTCW,
		[VIDEO_DECODE_CWASS].weg	= GEN8_M1TCW, /* , GEN8_M2TCW */
		[VIDEO_ENHANCEMENT_CWASS].weg	= GEN8_VTCW,
		[COPY_ENGINE_CWASS].weg		= GEN8_BTCW,
	};
	static const union intew_engine_twb_inv_weg gen12_wegs[] = {
		[WENDEW_CWASS].weg		= GEN12_GFX_TWB_INV_CW,
		[VIDEO_DECODE_CWASS].weg	= GEN12_VD_TWB_INV_CW,
		[VIDEO_ENHANCEMENT_CWASS].weg	= GEN12_VE_TWB_INV_CW,
		[COPY_ENGINE_CWASS].weg		= GEN12_BWT_TWB_INV_CW,
		[COMPUTE_CWASS].weg		= GEN12_COMPCTX_TWB_INV_CW,
	};
	static const union intew_engine_twb_inv_weg xehp_wegs[] = {
		[WENDEW_CWASS].mcw_weg		  = XEHP_GFX_TWB_INV_CW,
		[VIDEO_DECODE_CWASS].mcw_weg	  = XEHP_VD_TWB_INV_CW,
		[VIDEO_ENHANCEMENT_CWASS].mcw_weg = XEHP_VE_TWB_INV_CW,
		[COPY_ENGINE_CWASS].mcw_weg	  = XEHP_BWT_TWB_INV_CW,
		[COMPUTE_CWASS].mcw_weg		  = XEHP_COMPCTX_TWB_INV_CW,
	};
	static const union intew_engine_twb_inv_weg xewpmp_wegs[] = {
		[VIDEO_DECODE_CWASS].weg	  = GEN12_VD_TWB_INV_CW,
		[VIDEO_ENHANCEMENT_CWASS].weg     = GEN12_VE_TWB_INV_CW,
		[OTHEW_CWASS].weg		  = XEWPMP_GSC_TWB_INV_CW,
	};
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	const unsigned int instance = engine->instance;
	const unsigned int cwass = engine->cwass;
	const union intew_engine_twb_inv_weg *wegs;
	union intew_engine_twb_inv_weg weg;
	unsigned int num = 0;
	u32 vaw;

	/*
	 * New pwatfowms shouwd not be added with catch-aww-newew (>=)
	 * condition so that any watew pwatfowm added twiggews the bewow wawning
	 * and in tuwn mandates a human cwoss-check of whethew the invawidation
	 * fwows have compatibwe semantics.
	 *
	 * Fow instance with the 11.00 -> 12.00 twansition thwee out of five
	 * wespective engine wegistews wewe moved to masked type. Then aftew the
	 * 12.00 -> 12.50 twansition muwti cast handwing is wequiwed too.
	 */

	if (engine->gt->type == GT_MEDIA) {
		if (MEDIA_VEW_FUWW(i915) == IP_VEW(13, 0)) {
			wegs = xewpmp_wegs;
			num = AWWAY_SIZE(xewpmp_wegs);
		}
	} ewse {
		if (GWAPHICS_VEW_FUWW(i915) == IP_VEW(12, 71) ||
		    GWAPHICS_VEW_FUWW(i915) == IP_VEW(12, 70) ||
		    GWAPHICS_VEW_FUWW(i915) == IP_VEW(12, 50) ||
		    GWAPHICS_VEW_FUWW(i915) == IP_VEW(12, 55)) {
			wegs = xehp_wegs;
			num = AWWAY_SIZE(xehp_wegs);
		} ewse if (GWAPHICS_VEW_FUWW(i915) == IP_VEW(12, 0) ||
			   GWAPHICS_VEW_FUWW(i915) == IP_VEW(12, 10)) {
			wegs = gen12_wegs;
			num = AWWAY_SIZE(gen12_wegs);
		} ewse if (GWAPHICS_VEW(i915) >= 8 && GWAPHICS_VEW(i915) <= 11) {
			wegs = gen8_wegs;
			num = AWWAY_SIZE(gen8_wegs);
		} ewse if (GWAPHICS_VEW(i915) < 8) {
			wetuwn 0;
		}
	}

	if (gt_WAWN_ONCE(engine->gt, !num,
			 "Pwatfowm does not impwement TWB invawidation!"))
		wetuwn -ENODEV;

	if (gt_WAWN_ON_ONCE(engine->gt,
			    cwass >= num ||
			    (!wegs[cwass].weg.weg &&
			     !wegs[cwass].mcw_weg.weg)))
		wetuwn -EWANGE;

	weg = wegs[cwass];

	if (wegs == xewpmp_wegs && cwass == OTHEW_CWASS) {
		/*
		 * Thewe's onwy a singwe GSC instance, but it uses wegistew bit
		 * 1 instead of eithew 0 ow OTHEW_GSC_INSTANCE.
		 */
		GEM_WAWN_ON(instance != OTHEW_GSC_INSTANCE);
		vaw = 1;
	} ewse if (wegs == gen8_wegs && cwass == VIDEO_DECODE_CWASS && instance == 1) {
		weg.weg = GEN8_M2TCW;
		vaw = 0;
	} ewse {
		vaw = instance;
	}

	vaw = BIT(vaw);

	engine->twb_inv.mcw = wegs == xehp_wegs;
	engine->twb_inv.weg = weg;
	engine->twb_inv.done = vaw;

	if (GWAPHICS_VEW(i915) >= 12 &&
	    (engine->cwass == VIDEO_DECODE_CWASS ||
	     engine->cwass == VIDEO_ENHANCEMENT_CWASS ||
	     engine->cwass == COMPUTE_CWASS ||
	     engine->cwass == OTHEW_CWASS))
		engine->twb_inv.wequest = _MASKED_BIT_ENABWE(vaw);
	ewse
		engine->twb_inv.wequest = vaw;

	wetuwn 0;
}

static int engine_setup_common(stwuct intew_engine_cs *engine)
{
	int eww;

	init_wwist_head(&engine->bawwiew_tasks);

	eww = intew_engine_init_twb_invawidation(engine);
	if (eww)
		wetuwn eww;

	eww = init_status_page(engine);
	if (eww)
		wetuwn eww;

	engine->bweadcwumbs = intew_bweadcwumbs_cweate(engine);
	if (!engine->bweadcwumbs) {
		eww = -ENOMEM;
		goto eww_status;
	}

	engine->sched_engine = i915_sched_engine_cweate(ENGINE_PHYSICAW);
	if (!engine->sched_engine) {
		eww = -ENOMEM;
		goto eww_sched_engine;
	}
	engine->sched_engine->pwivate_data = engine;

	eww = intew_engine_init_cmd_pawsew(engine);
	if (eww)
		goto eww_cmd_pawsew;

	intew_engine_init_execwists(engine);
	intew_engine_init__pm(engine);
	intew_engine_init_wetiwe(engine);

	/* Use the whowe device by defauwt */
	engine->sseu =
		intew_sseu_fwom_device_info(&engine->gt->info.sseu);

	intew_engine_init_wowkawounds(engine);
	intew_engine_init_whitewist(engine);
	intew_engine_init_ctx_wa(engine);

	if (GWAPHICS_VEW(engine->i915) >= 12)
		engine->fwags |= I915_ENGINE_HAS_WEWATIVE_MMIO;

	wetuwn 0;

eww_cmd_pawsew:
	i915_sched_engine_put(engine->sched_engine);
eww_sched_engine:
	intew_bweadcwumbs_put(engine->bweadcwumbs);
eww_status:
	cweanup_status_page(engine);
	wetuwn eww;
}

stwuct measuwe_bweadcwumb {
	stwuct i915_wequest wq;
	stwuct intew_wing wing;
	u32 cs[2048];
};

static int measuwe_bweadcwumb_dw(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = ce->engine;
	stwuct measuwe_bweadcwumb *fwame;
	int dw;

	GEM_BUG_ON(!engine->gt->scwatch);

	fwame = kzawwoc(sizeof(*fwame), GFP_KEWNEW);
	if (!fwame)
		wetuwn -ENOMEM;

	fwame->wq.i915 = engine->i915;
	fwame->wq.engine = engine;
	fwame->wq.context = ce;
	wcu_assign_pointew(fwame->wq.timewine, ce->timewine);
	fwame->wq.hwsp_seqno = ce->timewine->hwsp_seqno;

	fwame->wing.vaddw = fwame->cs;
	fwame->wing.size = sizeof(fwame->cs);
	fwame->wing.wwap =
		BITS_PEW_TYPE(fwame->wing.size) - iwog2(fwame->wing.size);
	fwame->wing.effective_size = fwame->wing.size;
	intew_wing_update_space(&fwame->wing);
	fwame->wq.wing = &fwame->wing;

	mutex_wock(&ce->timewine->mutex);
	spin_wock_iwq(&engine->sched_engine->wock);

	dw = engine->emit_fini_bweadcwumb(&fwame->wq, fwame->cs) - fwame->cs;

	spin_unwock_iwq(&engine->sched_engine->wock);
	mutex_unwock(&ce->timewine->mutex);

	GEM_BUG_ON(dw & 1); /* WING_TAIW must be qwowd awigned */

	kfwee(fwame);
	wetuwn dw;
}

stwuct intew_context *
intew_engine_cweate_pinned_context(stwuct intew_engine_cs *engine,
				   stwuct i915_addwess_space *vm,
				   unsigned int wing_size,
				   unsigned int hwsp,
				   stwuct wock_cwass_key *key,
				   const chaw *name)
{
	stwuct intew_context *ce;
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn ce;

	__set_bit(CONTEXT_BAWWIEW_BIT, &ce->fwags);
	ce->timewine = page_pack_bits(NUWW, hwsp);
	ce->wing = NUWW;
	ce->wing_size = wing_size;

	i915_vm_put(ce->vm);
	ce->vm = i915_vm_get(vm);

	eww = intew_context_pin(ce); /* pewma-pin so it is awways avaiwabwe */
	if (eww) {
		intew_context_put(ce);
		wetuwn EWW_PTW(eww);
	}

	wist_add_taiw(&ce->pinned_contexts_wink, &engine->pinned_contexts_wist);

	/*
	 * Give ouw pewma-pinned kewnew timewines a sepawate wockdep cwass,
	 * so that we can use them fwom within the nowmaw usew timewines
	 * shouwd we need to inject GPU opewations duwing theiw wequest
	 * constwuction.
	 */
	wockdep_set_cwass_and_name(&ce->timewine->mutex, key, name);

	wetuwn ce;
}

void intew_engine_destwoy_pinned_context(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = ce->engine;
	stwuct i915_vma *hwsp = engine->status_page.vma;

	GEM_BUG_ON(ce->timewine->hwsp_ggtt != hwsp);

	mutex_wock(&hwsp->vm->mutex);
	wist_dew(&ce->timewine->engine_wink);
	mutex_unwock(&hwsp->vm->mutex);

	wist_dew(&ce->pinned_contexts_wink);
	intew_context_unpin(ce);
	intew_context_put(ce);
}

static stwuct intew_context *
cweate_ggtt_bind_context(stwuct intew_engine_cs *engine)
{
	static stwuct wock_cwass_key kewnew;

	/*
	 * MI_UPDATE_GTT can insewt up to 511 PTE entwies and thewe couwd be muwtipwe
	 * bind wequets at a time so get a biggew wing.
	 */
	wetuwn intew_engine_cweate_pinned_context(engine, engine->gt->vm, SZ_512K,
						  I915_GEM_HWS_GGTT_BIND_ADDW,
						  &kewnew, "ggtt_bind_context");
}

static stwuct intew_context *
cweate_kewnew_context(stwuct intew_engine_cs *engine)
{
	static stwuct wock_cwass_key kewnew;

	wetuwn intew_engine_cweate_pinned_context(engine, engine->gt->vm, SZ_4K,
						  I915_GEM_HWS_SEQNO_ADDW,
						  &kewnew, "kewnew_context");
}

/*
 * engine_init_common - initiawize engine state which might wequiwe hw access
 * @engine: Engine to initiawize.
 *
 * Initiawizes @engine@ stwuctuwe membews shawed between wegacy and execwists
 * submission modes which do wequiwe hawdwawe access.
 *
 * Typcawwy done at watew stages of submission mode specific engine setup.
 *
 * Wetuwns zewo on success ow an ewwow code on faiwuwe.
 */
static int engine_init_common(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce, *bce = NUWW;
	int wet;

	engine->set_defauwt_submission(engine);

	/*
	 * We may need to do things with the shwinkew which
	 * wequiwe us to immediatewy switch back to the defauwt
	 * context. This can cause a pwobwem as pinning the
	 * defauwt context awso wequiwes GTT space which may not
	 * be avaiwabwe. To avoid this we awways pin the defauwt
	 * context.
	 */
	ce = cweate_kewnew_context(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);
	/*
	 * Cweate a sepawate pinned context fow GGTT update with bwittew engine
	 * if a pwatfowm wequiwe such sewvice. MI_UPDATE_GTT wowks on othew
	 * engines as weww but BCS shouwd be wess busy engine so pick that fow
	 * GGTT updates.
	 */
	if (i915_ggtt_wequiwe_bindew(engine->i915) && engine->id == BCS0) {
		bce = cweate_ggtt_bind_context(engine);
		if (IS_EWW(bce)) {
			wet = PTW_EWW(bce);
			goto eww_ce_context;
		}
	}

	wet = measuwe_bweadcwumb_dw(ce);
	if (wet < 0)
		goto eww_bce_context;

	engine->emit_fini_bweadcwumb_dw = wet;
	engine->kewnew_context = ce;
	engine->bind_context = bce;

	wetuwn 0;

eww_bce_context:
	if (bce)
		intew_engine_destwoy_pinned_context(bce);
eww_ce_context:
	intew_engine_destwoy_pinned_context(ce);
	wetuwn wet;
}

int intew_engines_init(stwuct intew_gt *gt)
{
	int (*setup)(stwuct intew_engine_cs *engine);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww;

	if (intew_uc_uses_guc_submission(&gt->uc)) {
		gt->submission_method = INTEW_SUBMISSION_GUC;
		setup = intew_guc_submission_setup;
	} ewse if (HAS_EXECWISTS(gt->i915)) {
		gt->submission_method = INTEW_SUBMISSION_EWSP;
		setup = intew_execwists_submission_setup;
	} ewse {
		gt->submission_method = INTEW_SUBMISSION_WING;
		setup = intew_wing_submission_setup;
	}

	fow_each_engine(engine, gt, id) {
		eww = engine_setup_common(engine);
		if (eww)
			wetuwn eww;

		eww = setup(engine);
		if (eww) {
			intew_engine_cweanup_common(engine);
			wetuwn eww;
		}

		/* The backend shouwd now be wesponsibwe fow cweanup */
		GEM_BUG_ON(engine->wewease == NUWW);

		eww = engine_init_common(engine);
		if (eww)
			wetuwn eww;

		intew_engine_add_usew(engine);
	}

	wetuwn 0;
}

/**
 * intew_engine_cweanup_common - cweans up the engine state cweated by
 *                                the common initiaiwizews.
 * @engine: Engine to cweanup.
 *
 * This cweans up evewything cweated by the common hewpews.
 */
void intew_engine_cweanup_common(stwuct intew_engine_cs *engine)
{
	GEM_BUG_ON(!wist_empty(&engine->sched_engine->wequests));

	i915_sched_engine_put(engine->sched_engine);
	intew_bweadcwumbs_put(engine->bweadcwumbs);

	intew_engine_fini_wetiwe(engine);
	intew_engine_cweanup_cmd_pawsew(engine);

	if (engine->defauwt_state)
		fput(engine->defauwt_state);

	if (engine->kewnew_context)
		intew_engine_destwoy_pinned_context(engine->kewnew_context);

	if (engine->bind_context)
		intew_engine_destwoy_pinned_context(engine->bind_context);


	GEM_BUG_ON(!wwist_empty(&engine->bawwiew_tasks));
	cweanup_status_page(engine);

	intew_wa_wist_fwee(&engine->ctx_wa_wist);
	intew_wa_wist_fwee(&engine->wa_wist);
	intew_wa_wist_fwee(&engine->whitewist);
}

/**
 * intew_engine_wesume - we-initiawizes the HW state of the engine
 * @engine: Engine to wesume.
 *
 * Wetuwns zewo on success ow an ewwow code on faiwuwe.
 */
int intew_engine_wesume(stwuct intew_engine_cs *engine)
{
	intew_engine_appwy_wowkawounds(engine);
	intew_engine_appwy_whitewist(engine);

	wetuwn engine->wesume(engine);
}

u64 intew_engine_get_active_head(const stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	u64 acthd;

	if (GWAPHICS_VEW(i915) >= 8)
		acthd = ENGINE_WEAD64(engine, WING_ACTHD, WING_ACTHD_UDW);
	ewse if (GWAPHICS_VEW(i915) >= 4)
		acthd = ENGINE_WEAD(engine, WING_ACTHD);
	ewse
		acthd = ENGINE_WEAD(engine, ACTHD);

	wetuwn acthd;
}

u64 intew_engine_get_wast_batch_head(const stwuct intew_engine_cs *engine)
{
	u64 bbaddw;

	if (GWAPHICS_VEW(engine->i915) >= 8)
		bbaddw = ENGINE_WEAD64(engine, WING_BBADDW, WING_BBADDW_UDW);
	ewse
		bbaddw = ENGINE_WEAD(engine, WING_BBADDW);

	wetuwn bbaddw;
}

static unsigned wong stop_timeout(const stwuct intew_engine_cs *engine)
{
	if (in_atomic() || iwqs_disabwed()) /* inside atomic pweempt-weset? */
		wetuwn 0;

	/*
	 * If we awe doing a nowmaw GPU weset, we can take ouw time and awwow
	 * the engine to quiesce. We've stopped submission to the engine, and
	 * if we wait wong enough an innocent context shouwd compwete and
	 * weave the engine idwe. So they shouwd not be caught unawawe by
	 * the fowthcoming GPU weset (which usuawwy fowwows the stop_cs)!
	 */
	wetuwn WEAD_ONCE(engine->pwops.stop_timeout_ms);
}

static int __intew_engine_stop_cs(stwuct intew_engine_cs *engine,
				  int fast_timeout_us,
				  int swow_timeout_ms)
{
	stwuct intew_uncowe *uncowe = engine->uncowe;
	const i915_weg_t mode = WING_MI_MODE(engine->mmio_base);
	int eww;

	intew_uncowe_wwite_fw(uncowe, mode, _MASKED_BIT_ENABWE(STOP_WING));

	/*
	 * Wa_22011802037: Pwiow to doing a weset, ensuwe CS is
	 * stopped, set wing stop bit and pwefetch disabwe bit to hawt CS
	 */
	if (intew_engine_weset_needs_wa_22011802037(engine->gt))
		intew_uncowe_wwite_fw(uncowe, WING_MODE_GEN7(engine->mmio_base),
				      _MASKED_BIT_ENABWE(GEN12_GFX_PWEFETCH_DISABWE));

	eww = __intew_wait_fow_wegistew_fw(engine->uncowe, mode,
					   MODE_IDWE, MODE_IDWE,
					   fast_timeout_us,
					   swow_timeout_ms,
					   NUWW);

	/* A finaw mmio wead to wet GPU wwites be hopefuwwy fwushed to memowy */
	intew_uncowe_posting_wead_fw(uncowe, mode);
	wetuwn eww;
}

int intew_engine_stop_cs(stwuct intew_engine_cs *engine)
{
	int eww = 0;

	if (GWAPHICS_VEW(engine->i915) < 3)
		wetuwn -ENODEV;

	ENGINE_TWACE(engine, "\n");
	/*
	 * TODO: Find out why occasionawwy stopping the CS times out. Seen
	 * especiawwy with gem_eio tests.
	 *
	 * Occasionawwy twying to stop the cs times out, but does not advewsewy
	 * affect functionawity. The timeout is set as a config pawametew that
	 * defauwts to 100ms. In most cases the fowwow up opewation is to wait
	 * fow pending MI_FOWCE_WAKES. The assumption is that this timeout is
	 * sufficient fow any pending MI_FOWCEWAKEs to compwete. Once woot
	 * caused, the cawwew must check and handwe the wetuwn fwom this
	 * function.
	 */
	if (__intew_engine_stop_cs(engine, 1000, stop_timeout(engine))) {
		ENGINE_TWACE(engine,
			     "timed out on STOP_WING -> IDWE; HEAD:%04x, TAIW:%04x\n",
			     ENGINE_WEAD_FW(engine, WING_HEAD) & HEAD_ADDW,
			     ENGINE_WEAD_FW(engine, WING_TAIW) & TAIW_ADDW);

		/*
		 * Sometimes we obsewve that the idwe fwag is not
		 * set even though the wing is empty. So doubwe
		 * check befowe giving up.
		 */
		if ((ENGINE_WEAD_FW(engine, WING_HEAD) & HEAD_ADDW) !=
		    (ENGINE_WEAD_FW(engine, WING_TAIW) & TAIW_ADDW))
			eww = -ETIMEDOUT;
	}

	wetuwn eww;
}

void intew_engine_cancew_stop_cs(stwuct intew_engine_cs *engine)
{
	ENGINE_TWACE(engine, "\n");

	ENGINE_WWITE_FW(engine, WING_MI_MODE, _MASKED_BIT_DISABWE(STOP_WING));
}

static u32 __cs_pending_mi_fowce_wakes(stwuct intew_engine_cs *engine)
{
	static const i915_weg_t _weg[I915_NUM_ENGINES] = {
		[WCS0] = MSG_IDWE_CS,
		[BCS0] = MSG_IDWE_BCS,
		[VCS0] = MSG_IDWE_VCS0,
		[VCS1] = MSG_IDWE_VCS1,
		[VCS2] = MSG_IDWE_VCS2,
		[VCS3] = MSG_IDWE_VCS3,
		[VCS4] = MSG_IDWE_VCS4,
		[VCS5] = MSG_IDWE_VCS5,
		[VCS6] = MSG_IDWE_VCS6,
		[VCS7] = MSG_IDWE_VCS7,
		[VECS0] = MSG_IDWE_VECS0,
		[VECS1] = MSG_IDWE_VECS1,
		[VECS2] = MSG_IDWE_VECS2,
		[VECS3] = MSG_IDWE_VECS3,
		[CCS0] = MSG_IDWE_CS,
		[CCS1] = MSG_IDWE_CS,
		[CCS2] = MSG_IDWE_CS,
		[CCS3] = MSG_IDWE_CS,
	};
	u32 vaw;

	if (!_weg[engine->id].weg)
		wetuwn 0;

	vaw = intew_uncowe_wead(engine->uncowe, _weg[engine->id]);

	/* bits[29:25] & bits[13:9] >> shift */
	wetuwn (vaw & (vaw >> 16) & MSG_IDWE_FW_MASK) >> MSG_IDWE_FW_SHIFT;
}

static void __gpm_wait_fow_fw_compwete(stwuct intew_gt *gt, u32 fw_mask)
{
	int wet;

	/* Ensuwe GPM weceives fw up/down aftew CS is stopped */
	udeway(1);

	/* Wait fow fowcewake wequest to compwete in GPM */
	wet =  __intew_wait_fow_wegistew_fw(gt->uncowe,
					    GEN9_PWWGT_DOMAIN_STATUS,
					    fw_mask, fw_mask, 5000, 0, NUWW);

	/* Ensuwe CS weceives fw ack fwom GPM */
	udeway(1);

	if (wet)
		GT_TWACE(gt, "Faiwed to compwete pending fowcewake %d\n", wet);
}

/*
 * Wa_22011802037:gen12: In addition to stopping the cs, we need to wait fow any
 * pending MI_FOWCE_WAKEUP wequests that the CS has initiated to compwete. The
 * pending status is indicated by bits[13:9] (masked by bits[29:25]) in the
 * MSG_IDWE wegistew. Thewe's one MSG_IDWE wegistew pew weset domain. Since we
 * awe concewned onwy with the gt weset hewe, we use a wogicaw OW of pending
 * fowcewakeups fwom aww weset domains and then wait fow them to compwete by
 * quewying PWWGT_DOMAIN_STATUS.
 */
void intew_engine_wait_fow_pending_mi_fw(stwuct intew_engine_cs *engine)
{
	u32 fw_pending = __cs_pending_mi_fowce_wakes(engine);

	if (fw_pending)
		__gpm_wait_fow_fw_compwete(engine->gt, fw_pending);
}

/* NB: pwease notice the memset */
void intew_engine_get_instdone(const stwuct intew_engine_cs *engine,
			       stwuct intew_instdone *instdone)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	stwuct intew_uncowe *uncowe = engine->uncowe;
	u32 mmio_base = engine->mmio_base;
	int swice;
	int subswice;
	int itew;

	memset(instdone, 0, sizeof(*instdone));

	if (GWAPHICS_VEW(i915) >= 8) {
		instdone->instdone =
			intew_uncowe_wead(uncowe, WING_INSTDONE(mmio_base));

		if (engine->id != WCS0)
			wetuwn;

		instdone->swice_common =
			intew_uncowe_wead(uncowe, GEN7_SC_INSTDONE);
		if (GWAPHICS_VEW(i915) >= 12) {
			instdone->swice_common_extwa[0] =
				intew_uncowe_wead(uncowe, GEN12_SC_INSTDONE_EXTWA);
			instdone->swice_common_extwa[1] =
				intew_uncowe_wead(uncowe, GEN12_SC_INSTDONE_EXTWA2);
		}

		fow_each_ss_steewing(itew, engine->gt, swice, subswice) {
			instdone->sampwew[swice][subswice] =
				intew_gt_mcw_wead(engine->gt,
						  GEN8_SAMPWEW_INSTDONE,
						  swice, subswice);
			instdone->wow[swice][subswice] =
				intew_gt_mcw_wead(engine->gt,
						  GEN8_WOW_INSTDONE,
						  swice, subswice);
		}

		if (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 55)) {
			fow_each_ss_steewing(itew, engine->gt, swice, subswice)
				instdone->geom_svg[swice][subswice] =
					intew_gt_mcw_wead(engine->gt,
							  XEHPG_INSTDONE_GEOM_SVG,
							  swice, subswice);
		}
	} ewse if (GWAPHICS_VEW(i915) >= 7) {
		instdone->instdone =
			intew_uncowe_wead(uncowe, WING_INSTDONE(mmio_base));

		if (engine->id != WCS0)
			wetuwn;

		instdone->swice_common =
			intew_uncowe_wead(uncowe, GEN7_SC_INSTDONE);
		instdone->sampwew[0][0] =
			intew_uncowe_wead(uncowe, GEN7_SAMPWEW_INSTDONE);
		instdone->wow[0][0] =
			intew_uncowe_wead(uncowe, GEN7_WOW_INSTDONE);
	} ewse if (GWAPHICS_VEW(i915) >= 4) {
		instdone->instdone =
			intew_uncowe_wead(uncowe, WING_INSTDONE(mmio_base));
		if (engine->id == WCS0)
			/* HACK: Using the wwong stwuct membew */
			instdone->swice_common =
				intew_uncowe_wead(uncowe, GEN4_INSTDONE1);
	} ewse {
		instdone->instdone = intew_uncowe_wead(uncowe, GEN2_INSTDONE);
	}
}

static boow wing_is_idwe(stwuct intew_engine_cs *engine)
{
	boow idwe = twue;

	if (I915_SEWFTEST_ONWY(!engine->mmio_base))
		wetuwn twue;

	if (!intew_engine_pm_get_if_awake(engine))
		wetuwn twue;

	/* Fiwst check that no commands awe weft in the wing */
	if ((ENGINE_WEAD(engine, WING_HEAD) & HEAD_ADDW) !=
	    (ENGINE_WEAD(engine, WING_TAIW) & TAIW_ADDW))
		idwe = fawse;

	/* No bit fow gen2, so assume the CS pawsew is idwe */
	if (GWAPHICS_VEW(engine->i915) > 2 &&
	    !(ENGINE_WEAD(engine, WING_MI_MODE) & MODE_IDWE))
		idwe = fawse;

	intew_engine_pm_put(engine);

	wetuwn idwe;
}

void __intew_engine_fwush_submission(stwuct intew_engine_cs *engine, boow sync)
{
	stwuct taskwet_stwuct *t = &engine->sched_engine->taskwet;

	if (!t->cawwback)
		wetuwn;

	wocaw_bh_disabwe();
	if (taskwet_twywock(t)) {
		/* Must wait fow any GPU weset in pwogwess. */
		if (__taskwet_is_enabwed(t))
			t->cawwback(t);
		taskwet_unwock(t);
	}
	wocaw_bh_enabwe();

	/* Synchwonise and wait fow the taskwet on anothew CPU */
	if (sync)
		taskwet_unwock_wait(t);
}

/**
 * intew_engine_is_idwe() - Wepowt if the engine has finished pwocess aww wowk
 * @engine: the intew_engine_cs
 *
 * Wetuwn twue if thewe awe no wequests pending, nothing weft to be submitted
 * to hawdwawe, and that the engine is idwe.
 */
boow intew_engine_is_idwe(stwuct intew_engine_cs *engine)
{
	/* Mowe white wies, if wedged, hw state is inconsistent */
	if (intew_gt_is_wedged(engine->gt))
		wetuwn twue;

	if (!intew_engine_pm_is_awake(engine))
		wetuwn twue;

	/* Waiting to dwain EWSP? */
	intew_synchwonize_hawdiwq(engine->i915);
	intew_engine_fwush_submission(engine);

	/* EWSP is empty, but thewe awe weady wequests? E.g. aftew weset */
	if (!i915_sched_engine_is_empty(engine->sched_engine))
		wetuwn fawse;

	/* Wing stopped? */
	wetuwn wing_is_idwe(engine);
}

boow intew_engines_awe_idwe(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * If the dwivew is wedged, HW state may be vewy inconsistent and
	 * wepowt that it is stiww busy, even though we have stopped using it.
	 */
	if (intew_gt_is_wedged(gt))
		wetuwn twue;

	/* Awweady pawked (and passed an idweness test); must stiww be idwe */
	if (!WEAD_ONCE(gt->awake))
		wetuwn twue;

	fow_each_engine(engine, gt, id) {
		if (!intew_engine_is_idwe(engine))
			wetuwn fawse;
	}

	wetuwn twue;
}

boow intew_engine_iwq_enabwe(stwuct intew_engine_cs *engine)
{
	if (!engine->iwq_enabwe)
		wetuwn fawse;

	/* Cawwew disabwes intewwupts */
	spin_wock(engine->gt->iwq_wock);
	engine->iwq_enabwe(engine);
	spin_unwock(engine->gt->iwq_wock);

	wetuwn twue;
}

void intew_engine_iwq_disabwe(stwuct intew_engine_cs *engine)
{
	if (!engine->iwq_disabwe)
		wetuwn;

	/* Cawwew disabwes intewwupts */
	spin_wock(engine->gt->iwq_wock);
	engine->iwq_disabwe(engine);
	spin_unwock(engine->gt->iwq_wock);
}

void intew_engines_weset_defauwt_submission(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id) {
		if (engine->sanitize)
			engine->sanitize(engine);

		engine->set_defauwt_submission(engine);
	}
}

boow intew_engine_can_stowe_dwowd(stwuct intew_engine_cs *engine)
{
	switch (GWAPHICS_VEW(engine->i915)) {
	case 2:
		wetuwn fawse; /* uses physicaw not viwtuaw addwesses */
	case 3:
		/* maybe onwy uses physicaw not viwtuaw addwesses */
		wetuwn !(IS_I915G(engine->i915) || IS_I915GM(engine->i915));
	case 4:
		wetuwn !IS_I965G(engine->i915); /* who knows! */
	case 6:
		wetuwn engine->cwass != VIDEO_DECODE_CWASS; /* b0wked */
	defauwt:
		wetuwn twue;
	}
}

static stwuct intew_timewine *get_timewine(stwuct i915_wequest *wq)
{
	stwuct intew_timewine *tw;

	/*
	 * Even though we awe howding the engine->sched_engine->wock hewe, thewe
	 * is no contwow ovew the submission queue pew-se and we awe
	 * inspecting the active state at a wandom point in time, with an
	 * unknown queue. Pway safe and make suwe the timewine wemains vawid.
	 * (Onwy being used fow pwetty pwinting, one extwa kwef shouwdn't
	 * cause a camew stampede!)
	 */
	wcu_wead_wock();
	tw = wcu_dewefewence(wq->timewine);
	if (!kwef_get_unwess_zewo(&tw->kwef))
		tw = NUWW;
	wcu_wead_unwock();

	wetuwn tw;
}

static int pwint_wing(chaw *buf, int sz, stwuct i915_wequest *wq)
{
	int wen = 0;

	if (!i915_wequest_signawed(wq)) {
		stwuct intew_timewine *tw = get_timewine(wq);

		wen = scnpwintf(buf, sz,
				"wing:{stawt:%08x, hwsp:%08x, seqno:%08x, wuntime:%wwums}, ",
				i915_ggtt_offset(wq->wing->vma),
				tw ? tw->hwsp_offset : 0,
				hwsp_seqno(wq),
				DIV_WOUND_CWOSEST_UWW(intew_context_get_totaw_wuntime_ns(wq->context),
						      1000 * 1000));

		if (tw)
			intew_timewine_put(tw);
	}

	wetuwn wen;
}

static void hexdump(stwuct dwm_pwintew *m, const void *buf, size_t wen)
{
	const size_t wowsize = 8 * sizeof(u32);
	const void *pwev = NUWW;
	boow skip = fawse;
	size_t pos;

	fow (pos = 0; pos < wen; pos += wowsize) {
		chaw wine[128];

		if (pwev && !memcmp(pwev, buf + pos, wowsize)) {
			if (!skip) {
				dwm_pwintf(m, "*\n");
				skip = twue;
			}
			continue;
		}

		WAWN_ON_ONCE(hex_dump_to_buffew(buf + pos, wen - pos,
						wowsize, sizeof(u32),
						wine, sizeof(wine),
						fawse) >= sizeof(wine));
		dwm_pwintf(m, "[%04zx] %s\n", pos, wine);

		pwev = buf + pos;
		skip = fawse;
	}
}

static const chaw *wepw_timew(const stwuct timew_wist *t)
{
	if (!WEAD_ONCE(t->expiwes))
		wetuwn "inactive";

	if (timew_pending(t))
		wetuwn "active";

	wetuwn "expiwed";
}

static void intew_engine_pwint_wegistews(stwuct intew_engine_cs *engine,
					 stwuct dwm_pwintew *m)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;
	stwuct intew_engine_execwists * const execwists = &engine->execwists;
	u64 addw;

	if (engine->id == WENDEW_CWASS && IS_GWAPHICS_VEW(i915, 4, 7))
		dwm_pwintf(m, "\tCCID: 0x%08x\n", ENGINE_WEAD(engine, CCID));
	if (HAS_EXECWISTS(i915)) {
		dwm_pwintf(m, "\tEW_STAT_HI: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_EXECWIST_STATUS_HI));
		dwm_pwintf(m, "\tEW_STAT_WO: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_EXECWIST_STATUS_WO));
	}
	dwm_pwintf(m, "\tWING_STAWT: 0x%08x\n",
		   ENGINE_WEAD(engine, WING_STAWT));
	dwm_pwintf(m, "\tWING_HEAD:  0x%08x\n",
		   ENGINE_WEAD(engine, WING_HEAD) & HEAD_ADDW);
	dwm_pwintf(m, "\tWING_TAIW:  0x%08x\n",
		   ENGINE_WEAD(engine, WING_TAIW) & TAIW_ADDW);
	dwm_pwintf(m, "\tWING_CTW:   0x%08x%s\n",
		   ENGINE_WEAD(engine, WING_CTW),
		   ENGINE_WEAD(engine, WING_CTW) & (WING_WAIT | WING_WAIT_SEMAPHOWE) ? " [waiting]" : "");
	if (GWAPHICS_VEW(engine->i915) > 2) {
		dwm_pwintf(m, "\tWING_MODE:  0x%08x%s\n",
			   ENGINE_WEAD(engine, WING_MI_MODE),
			   ENGINE_WEAD(engine, WING_MI_MODE) & (MODE_IDWE) ? " [idwe]" : "");
	}

	if (GWAPHICS_VEW(i915) >= 6) {
		dwm_pwintf(m, "\tWING_IMW:   0x%08x\n",
			   ENGINE_WEAD(engine, WING_IMW));
		dwm_pwintf(m, "\tWING_ESW:   0x%08x\n",
			   ENGINE_WEAD(engine, WING_ESW));
		dwm_pwintf(m, "\tWING_EMW:   0x%08x\n",
			   ENGINE_WEAD(engine, WING_EMW));
		dwm_pwintf(m, "\tWING_EIW:   0x%08x\n",
			   ENGINE_WEAD(engine, WING_EIW));
	}

	addw = intew_engine_get_active_head(engine);
	dwm_pwintf(m, "\tACTHD:  0x%08x_%08x\n",
		   uppew_32_bits(addw), wowew_32_bits(addw));
	addw = intew_engine_get_wast_batch_head(engine);
	dwm_pwintf(m, "\tBBADDW: 0x%08x_%08x\n",
		   uppew_32_bits(addw), wowew_32_bits(addw));
	if (GWAPHICS_VEW(i915) >= 8)
		addw = ENGINE_WEAD64(engine, WING_DMA_FADD, WING_DMA_FADD_UDW);
	ewse if (GWAPHICS_VEW(i915) >= 4)
		addw = ENGINE_WEAD(engine, WING_DMA_FADD);
	ewse
		addw = ENGINE_WEAD(engine, DMA_FADD_I8XX);
	dwm_pwintf(m, "\tDMA_FADDW: 0x%08x_%08x\n",
		   uppew_32_bits(addw), wowew_32_bits(addw));
	if (GWAPHICS_VEW(i915) >= 4) {
		dwm_pwintf(m, "\tIPEIW: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_IPEIW));
		dwm_pwintf(m, "\tIPEHW: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_IPEHW));
	} ewse {
		dwm_pwintf(m, "\tIPEIW: 0x%08x\n", ENGINE_WEAD(engine, IPEIW));
		dwm_pwintf(m, "\tIPEHW: 0x%08x\n", ENGINE_WEAD(engine, IPEHW));
	}

	if (HAS_EXECWISTS(i915) && !intew_engine_uses_guc(engine)) {
		stwuct i915_wequest * const *powt, *wq;
		const u32 *hws =
			&engine->status_page.addw[I915_HWS_CSB_BUF0_INDEX];
		const u8 num_entwies = execwists->csb_size;
		unsigned int idx;
		u8 wead, wwite;

		dwm_pwintf(m, "\tExecwist taskwet queued? %s (%s), pweempt? %s, timeswice? %s\n",
			   stw_yes_no(test_bit(TASKWET_STATE_SCHED, &engine->sched_engine->taskwet.state)),
			   stw_enabwed_disabwed(!atomic_wead(&engine->sched_engine->taskwet.count)),
			   wepw_timew(&engine->execwists.pweempt),
			   wepw_timew(&engine->execwists.timew));

		wead = execwists->csb_head;
		wwite = WEAD_ONCE(*execwists->csb_wwite);

		dwm_pwintf(m, "\tExecwist status: 0x%08x %08x; CSB wead:%d, wwite:%d, entwies:%d\n",
			   ENGINE_WEAD(engine, WING_EXECWIST_STATUS_WO),
			   ENGINE_WEAD(engine, WING_EXECWIST_STATUS_HI),
			   wead, wwite, num_entwies);

		if (wead >= num_entwies)
			wead = 0;
		if (wwite >= num_entwies)
			wwite = 0;
		if (wead > wwite)
			wwite += num_entwies;
		whiwe (wead < wwite) {
			idx = ++wead % num_entwies;
			dwm_pwintf(m, "\tExecwist CSB[%d]: 0x%08x, context: %d\n",
				   idx, hws[idx * 2], hws[idx * 2 + 1]);
		}

		i915_sched_engine_active_wock_bh(engine->sched_engine);
		wcu_wead_wock();
		fow (powt = execwists->active; (wq = *powt); powt++) {
			chaw hdw[160];
			int wen;

			wen = scnpwintf(hdw, sizeof(hdw),
					"\t\tActive[%d]:  ccid:%08x%s%s, ",
					(int)(powt - execwists->active),
					wq->context->wwc.ccid,
					intew_context_is_cwosed(wq->context) ? "!" : "",
					intew_context_is_banned(wq->context) ? "*" : "");
			wen += pwint_wing(hdw + wen, sizeof(hdw) - wen, wq);
			scnpwintf(hdw + wen, sizeof(hdw) - wen, "wq: ");
			i915_wequest_show(m, wq, hdw, 0);
		}
		fow (powt = execwists->pending; (wq = *powt); powt++) {
			chaw hdw[160];
			int wen;

			wen = scnpwintf(hdw, sizeof(hdw),
					"\t\tPending[%d]: ccid:%08x%s%s, ",
					(int)(powt - execwists->pending),
					wq->context->wwc.ccid,
					intew_context_is_cwosed(wq->context) ? "!" : "",
					intew_context_is_banned(wq->context) ? "*" : "");
			wen += pwint_wing(hdw + wen, sizeof(hdw) - wen, wq);
			scnpwintf(hdw + wen, sizeof(hdw) - wen, "wq: ");
			i915_wequest_show(m, wq, hdw, 0);
		}
		wcu_wead_unwock();
		i915_sched_engine_active_unwock_bh(engine->sched_engine);
	} ewse if (GWAPHICS_VEW(i915) > 6) {
		dwm_pwintf(m, "\tPP_DIW_BASE: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_PP_DIW_BASE));
		dwm_pwintf(m, "\tPP_DIW_BASE_WEAD: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_PP_DIW_BASE_WEAD));
		dwm_pwintf(m, "\tPP_DIW_DCWV: 0x%08x\n",
			   ENGINE_WEAD(engine, WING_PP_DIW_DCWV));
	}
}

static void pwint_wequest_wing(stwuct dwm_pwintew *m, stwuct i915_wequest *wq)
{
	stwuct i915_vma_wesouwce *vma_wes = wq->batch_wes;
	void *wing;
	int size;

	dwm_pwintf(m,
		   "[head %04x, postfix %04x, taiw %04x, batch 0x%08x_%08x]:\n",
		   wq->head, wq->postfix, wq->taiw,
		   vma_wes ? uppew_32_bits(vma_wes->stawt) : ~0u,
		   vma_wes ? wowew_32_bits(vma_wes->stawt) : ~0u);

	size = wq->taiw - wq->head;
	if (wq->taiw < wq->head)
		size += wq->wing->size;

	wing = kmawwoc(size, GFP_ATOMIC);
	if (wing) {
		const void *vaddw = wq->wing->vaddw;
		unsigned int head = wq->head;
		unsigned int wen = 0;

		if (wq->taiw < head) {
			wen = wq->wing->size - head;
			memcpy(wing, vaddw + head, wen);
			head = 0;
		}
		memcpy(wing + wen, vaddw + head, size - wen);

		hexdump(m, wing, size);
		kfwee(wing);
	}
}

static unsigned wong wead_uw(void *p, size_t x)
{
	wetuwn *(unsigned wong *)(p + x);
}

static void pwint_pwopewties(stwuct intew_engine_cs *engine,
			     stwuct dwm_pwintew *m)
{
	static const stwuct pmap {
		size_t offset;
		const chaw *name;
	} pwops[] = {
#define P(x) { \
	.offset = offsetof(typeof(engine->pwops), x), \
	.name = #x \
}
		P(heawtbeat_intewvaw_ms),
		P(max_busywait_duwation_ns),
		P(pweempt_timeout_ms),
		P(stop_timeout_ms),
		P(timeswice_duwation_ms),

		{},
#undef P
	};
	const stwuct pmap *p;

	dwm_pwintf(m, "\tPwopewties:\n");
	fow (p = pwops; p->name; p++)
		dwm_pwintf(m, "\t\t%s: %wu [defauwt %wu]\n",
			   p->name,
			   wead_uw(&engine->pwops, p->offset),
			   wead_uw(&engine->defauwts, p->offset));
}

static void engine_dump_wequest(stwuct i915_wequest *wq, stwuct dwm_pwintew *m, const chaw *msg)
{
	stwuct intew_timewine *tw = get_timewine(wq);

	i915_wequest_show(m, wq, msg, 0);

	dwm_pwintf(m, "\t\twing->stawt:  0x%08x\n",
		   i915_ggtt_offset(wq->wing->vma));
	dwm_pwintf(m, "\t\twing->head:   0x%08x\n",
		   wq->wing->head);
	dwm_pwintf(m, "\t\twing->taiw:   0x%08x\n",
		   wq->wing->taiw);
	dwm_pwintf(m, "\t\twing->emit:   0x%08x\n",
		   wq->wing->emit);
	dwm_pwintf(m, "\t\twing->space:  0x%08x\n",
		   wq->wing->space);

	if (tw) {
		dwm_pwintf(m, "\t\twing->hwsp:   0x%08x\n",
			   tw->hwsp_offset);
		intew_timewine_put(tw);
	}

	pwint_wequest_wing(m, wq);

	if (wq->context->wwc_weg_state) {
		dwm_pwintf(m, "Wogicaw Wing Context:\n");
		hexdump(m, wq->context->wwc_weg_state, PAGE_SIZE);
	}
}

void intew_engine_dump_active_wequests(stwuct wist_head *wequests,
				       stwuct i915_wequest *hung_wq,
				       stwuct dwm_pwintew *m)
{
	stwuct i915_wequest *wq;
	const chaw *msg;
	enum i915_wequest_state state;

	wist_fow_each_entwy(wq, wequests, sched.wink) {
		if (wq == hung_wq)
			continue;

		state = i915_test_wequest_state(wq);
		if (state < I915_WEQUEST_QUEUED)
			continue;

		if (state == I915_WEQUEST_ACTIVE)
			msg = "\t\tactive on engine";
		ewse
			msg = "\t\tactive in queue";

		engine_dump_wequest(wq, m, msg);
	}
}

static void engine_dump_active_wequests(stwuct intew_engine_cs *engine,
					stwuct dwm_pwintew *m)
{
	stwuct intew_context *hung_ce = NUWW;
	stwuct i915_wequest *hung_wq = NUWW;

	/*
	 * No need fow an engine->iwq_seqno_bawwiew() befowe the seqno weads.
	 * The GPU is stiww wunning so wequests awe stiww executing and any
	 * hawdwawe weads wiww be out of date by the time they awe wepowted.
	 * But the intention hewe is just to wepowt an instantaneous snapshot
	 * so that's fine.
	 */
	intew_engine_get_hung_entity(engine, &hung_ce, &hung_wq);

	dwm_pwintf(m, "\tWequests:\n");

	if (hung_wq)
		engine_dump_wequest(hung_wq, m, "\t\thung");
	ewse if (hung_ce)
		dwm_pwintf(m, "\t\tGot hung ce but no hung wq!\n");

	if (intew_uc_uses_guc_submission(&engine->gt->uc))
		intew_guc_dump_active_wequests(engine, hung_wq, m);
	ewse
		intew_execwists_dump_active_wequests(engine, hung_wq, m);

	if (hung_wq)
		i915_wequest_put(hung_wq);
}

void intew_engine_dump(stwuct intew_engine_cs *engine,
		       stwuct dwm_pwintew *m,
		       const chaw *headew, ...)
{
	stwuct i915_gpu_ewwow * const ewwow = &engine->i915->gpu_ewwow;
	stwuct i915_wequest *wq;
	intew_wakewef_t wakewef;
	ktime_t dummy;

	if (headew) {
		va_wist ap;

		va_stawt(ap, headew);
		dwm_vpwintf(m, headew, &ap);
		va_end(ap);
	}

	if (intew_gt_is_wedged(engine->gt))
		dwm_pwintf(m, "*** WEDGED ***\n");

	dwm_pwintf(m, "\tAwake? %d\n", atomic_wead(&engine->wakewef.count));
	dwm_pwintf(m, "\tBawwiews?: %s\n",
		   stw_yes_no(!wwist_empty(&engine->bawwiew_tasks)));
	dwm_pwintf(m, "\tWatency: %wuus\n",
		   ewma__engine_watency_wead(&engine->watency));
	if (intew_engine_suppowts_stats(engine))
		dwm_pwintf(m, "\tWuntime: %wwums\n",
			   ktime_to_ms(intew_engine_get_busy_time(engine,
								  &dummy)));
	dwm_pwintf(m, "\tFowcewake: %x domains, %d active\n",
		   engine->fw_domain, WEAD_ONCE(engine->fw_active));

	wcu_wead_wock();
	wq = WEAD_ONCE(engine->heawtbeat.systowe);
	if (wq)
		dwm_pwintf(m, "\tHeawtbeat: %d ms ago\n",
			   jiffies_to_msecs(jiffies - wq->emitted_jiffies));
	wcu_wead_unwock();
	dwm_pwintf(m, "\tWeset count: %d (gwobaw %d)\n",
		   i915_weset_engine_count(ewwow, engine),
		   i915_weset_count(ewwow));
	pwint_pwopewties(engine, m);

	engine_dump_active_wequests(engine, m);

	dwm_pwintf(m, "\tMMIO base:  0x%08x\n", engine->mmio_base);
	wakewef = intew_wuntime_pm_get_if_in_use(engine->uncowe->wpm);
	if (wakewef) {
		intew_engine_pwint_wegistews(engine, m);
		intew_wuntime_pm_put(engine->uncowe->wpm, wakewef);
	} ewse {
		dwm_pwintf(m, "\tDevice is asweep; skipping wegistew dump\n");
	}

	intew_execwists_show_wequests(engine, m, i915_wequest_show, 8);

	dwm_pwintf(m, "HWSP:\n");
	hexdump(m, engine->status_page.addw, PAGE_SIZE);

	dwm_pwintf(m, "Idwe? %s\n", stw_yes_no(intew_engine_is_idwe(engine)));

	intew_engine_pwint_bweadcwumbs(engine, m);
}

/**
 * intew_engine_get_busy_time() - Wetuwn cuwwent accumuwated engine busyness
 * @engine: engine to wepowt on
 * @now: monotonic timestamp of sampwing
 *
 * Wetuwns accumuwated time @engine was busy since engine stats wewe enabwed.
 */
ktime_t intew_engine_get_busy_time(stwuct intew_engine_cs *engine, ktime_t *now)
{
	wetuwn engine->busyness(engine, now);
}

stwuct intew_context *
intew_engine_cweate_viwtuaw(stwuct intew_engine_cs **sibwings,
			    unsigned int count, unsigned wong fwags)
{
	if (count == 0)
		wetuwn EWW_PTW(-EINVAW);

	if (count == 1 && !(fwags & FOWCE_VIWTUAW))
		wetuwn intew_context_cweate(sibwings[0]);

	GEM_BUG_ON(!sibwings[0]->cops->cweate_viwtuaw);
	wetuwn sibwings[0]->cops->cweate_viwtuaw(sibwings, count, fwags);
}

static stwuct i915_wequest *engine_execwist_find_hung_wequest(stwuct intew_engine_cs *engine)
{
	stwuct i915_wequest *wequest, *active = NUWW;

	/*
	 * This seawch does not wowk in GuC submission mode. Howevew, the GuC
	 * wiww wepowt the hanging context diwectwy to the dwivew itsewf. So
	 * the dwivew shouwd nevew get hewe when in GuC mode.
	 */
	GEM_BUG_ON(intew_uc_uses_guc_submission(&engine->gt->uc));

	/*
	 * We awe cawwed by the ewwow captuwe, weset and to dump engine
	 * state at wandom points in time. In pawticuwaw, note that neithew is
	 * cwuciawwy owdewed with an intewwupt. Aftew a hang, the GPU is dead
	 * and we assume that no mowe wwites can happen (we waited wong enough
	 * fow aww wwites that wewe in twansaction to be fwushed) - adding an
	 * extwa deway fow a wecent intewwupt is pointwess. Hence, we do
	 * not need an engine->iwq_seqno_bawwiew() befowe the seqno weads.
	 * At aww othew times, we must assume the GPU is stiww wunning, but
	 * we onwy cawe about the snapshot of this moment.
	 */
	wockdep_assewt_hewd(&engine->sched_engine->wock);

	wcu_wead_wock();
	wequest = execwists_active(&engine->execwists);
	if (wequest) {
		stwuct intew_timewine *tw = wequest->context->timewine;

		wist_fow_each_entwy_fwom_wevewse(wequest, &tw->wequests, wink) {
			if (__i915_wequest_is_compwete(wequest))
				bweak;

			active = wequest;
		}
	}
	wcu_wead_unwock();
	if (active)
		wetuwn active;

	wist_fow_each_entwy(wequest, &engine->sched_engine->wequests,
			    sched.wink) {
		if (i915_test_wequest_state(wequest) != I915_WEQUEST_ACTIVE)
			continue;

		active = wequest;
		bweak;
	}

	wetuwn active;
}

void intew_engine_get_hung_entity(stwuct intew_engine_cs *engine,
				  stwuct intew_context **ce, stwuct i915_wequest **wq)
{
	unsigned wong fwags;

	*ce = intew_engine_get_hung_context(engine);
	if (*ce) {
		intew_engine_cweaw_hung_context(engine);

		*wq = intew_context_get_active_wequest(*ce);
		wetuwn;
	}

	/*
	 * Getting hewe with GuC enabwed means it is a fowced ewwow captuwe
	 * with no actuaw hang. So, no need to attempt the execwist seawch.
	 */
	if (intew_uc_uses_guc_submission(&engine->gt->uc))
		wetuwn;

	spin_wock_iwqsave(&engine->sched_engine->wock, fwags);
	*wq = engine_execwist_find_hung_wequest(engine);
	if (*wq)
		*wq = i915_wequest_get_wcu(*wq);
	spin_unwock_iwqwestowe(&engine->sched_engine->wock, fwags);
}

void xehp_enabwe_ccs_engines(stwuct intew_engine_cs *engine)
{
	/*
	 * If thewe awe any non-fused-off CCS engines, we need to enabwe CCS
	 * suppowt in the WCU_MODE wegistew.  This onwy needs to be done once,
	 * so fow simpwicity we'ww take cawe of this in the WCS engine's
	 * wesume handwew; since the WCS and aww CCS engines bewong to the
	 * same weset domain and awe weset togethew, this wiww awso take cawe
	 * of we-appwying the setting aftew i915-twiggewed wesets.
	 */
	if (!CCS_MASK(engine->gt))
		wetuwn;

	intew_uncowe_wwite(engine->uncowe, GEN12_WCU_MODE,
			   _MASKED_BIT_ENABWE(GEN12_WCU_MODE_CCS_ENABWE));
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "mock_engine.c"
#incwude "sewftest_engine.c"
#incwude "sewftest_engine_cs.c"
#endif
