// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021-2022 Intew Cowpowation
 */

#incwude <winux/types.h>

#incwude <dwm/dwm_pwint.h>

#incwude "gt/intew_engine_wegs.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_mcw.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wwc.h"
#incwude "guc_captuwe_fwif.h"
#incwude "intew_guc_captuwe.h"
#incwude "intew_guc_fwif.h"
#incwude "intew_guc_pwint.h"
#incwude "i915_dwv.h"
#incwude "i915_gpu_ewwow.h"
#incwude "i915_iwq.h"
#incwude "i915_memcpy.h"
#incwude "i915_weg.h"

/*
 * Define aww device tabwes of GuC ewwow captuwe wegistew wists
 * NOTE: Fow engine-wegistews, GuC onwy needs the wegistew offsets
 *       fwom the engine-mmio-base
 */
#define COMMON_BASE_GWOBAW \
	{ FOWCEWAKE_MT,             0,      0, "FOWCEWAKE" }

#define COMMON_GEN8BASE_GWOBAW \
	{ EWWOW_GEN6,               0,      0, "EWWOW_GEN6" }, \
	{ DONE_WEG,                 0,      0, "DONE_WEG" }, \
	{ HSW_GTT_CACHE_EN,         0,      0, "HSW_GTT_CACHE_EN" }

#define GEN8_GWOBAW \
	{ GEN8_FAUWT_TWB_DATA0,     0,      0, "GEN8_FAUWT_TWB_DATA0" }, \
	{ GEN8_FAUWT_TWB_DATA1,     0,      0, "GEN8_FAUWT_TWB_DATA1" }

#define COMMON_GEN12BASE_GWOBAW \
	{ GEN12_FAUWT_TWB_DATA0,    0,      0, "GEN12_FAUWT_TWB_DATA0" }, \
	{ GEN12_FAUWT_TWB_DATA1,    0,      0, "GEN12_FAUWT_TWB_DATA1" }, \
	{ GEN12_AUX_EWW_DBG,        0,      0, "AUX_EWW_DBG" }, \
	{ GEN12_GAM_DONE,           0,      0, "GAM_DONE" }, \
	{ GEN12_WING_FAUWT_WEG,     0,      0, "FAUWT_WEG" }

#define COMMON_BASE_ENGINE_INSTANCE \
	{ WING_PSMI_CTW(0),         0,      0, "WC PSMI" }, \
	{ WING_ESW(0),              0,      0, "ESW" }, \
	{ WING_DMA_FADD(0),         0,      0, "WING_DMA_FADD_WDW" }, \
	{ WING_DMA_FADD_UDW(0),     0,      0, "WING_DMA_FADD_UDW" }, \
	{ WING_IPEIW(0),            0,      0, "IPEIW" }, \
	{ WING_IPEHW(0),            0,      0, "IPEHW" }, \
	{ WING_INSTPS(0),           0,      0, "INSTPS" }, \
	{ WING_BBADDW(0),           0,      0, "WING_BBADDW_WOW32" }, \
	{ WING_BBADDW_UDW(0),       0,      0, "WING_BBADDW_UP32" }, \
	{ WING_BBSTATE(0),          0,      0, "BB_STATE" }, \
	{ CCID(0),                  0,      0, "CCID" }, \
	{ WING_ACTHD(0),            0,      0, "ACTHD_WDW" }, \
	{ WING_ACTHD_UDW(0),        0,      0, "ACTHD_UDW" }, \
	{ WING_INSTPM(0),           0,      0, "INSTPM" }, \
	{ WING_INSTDONE(0),         0,      0, "INSTDONE" }, \
	{ WING_NOPID(0),            0,      0, "WING_NOPID" }, \
	{ WING_STAWT(0),            0,      0, "STAWT" }, \
	{ WING_HEAD(0),             0,      0, "HEAD" }, \
	{ WING_TAIW(0),             0,      0, "TAIW" }, \
	{ WING_CTW(0),              0,      0, "CTW" }, \
	{ WING_MI_MODE(0),          0,      0, "MODE" }, \
	{ WING_CONTEXT_CONTWOW(0),  0,      0, "WING_CONTEXT_CONTWOW" }, \
	{ WING_HWS_PGA(0),          0,      0, "HWS" }, \
	{ WING_MODE_GEN7(0),        0,      0, "GFX_MODE" }, \
	{ GEN8_WING_PDP_WDW(0, 0),  0,      0, "PDP0_WDW" }, \
	{ GEN8_WING_PDP_UDW(0, 0),  0,      0, "PDP0_UDW" }, \
	{ GEN8_WING_PDP_WDW(0, 1),  0,      0, "PDP1_WDW" }, \
	{ GEN8_WING_PDP_UDW(0, 1),  0,      0, "PDP1_UDW" }, \
	{ GEN8_WING_PDP_WDW(0, 2),  0,      0, "PDP2_WDW" }, \
	{ GEN8_WING_PDP_UDW(0, 2),  0,      0, "PDP2_UDW" }, \
	{ GEN8_WING_PDP_WDW(0, 3),  0,      0, "PDP3_WDW" }, \
	{ GEN8_WING_PDP_UDW(0, 3),  0,      0, "PDP3_UDW" }

#define COMMON_BASE_HAS_EU \
	{ EIW,                      0,      0, "EIW" }

#define COMMON_BASE_WENDEW \
	{ GEN7_SC_INSTDONE,         0,      0, "GEN7_SC_INSTDONE" }

#define COMMON_GEN12BASE_WENDEW \
	{ GEN12_SC_INSTDONE_EXTWA,  0,      0, "GEN12_SC_INSTDONE_EXTWA" }, \
	{ GEN12_SC_INSTDONE_EXTWA2, 0,      0, "GEN12_SC_INSTDONE_EXTWA2" }

#define COMMON_GEN12BASE_VEC \
	{ GEN12_SFC_DONE(0),        0,      0, "SFC_DONE[0]" }, \
	{ GEN12_SFC_DONE(1),        0,      0, "SFC_DONE[1]" }, \
	{ GEN12_SFC_DONE(2),        0,      0, "SFC_DONE[2]" }, \
	{ GEN12_SFC_DONE(3),        0,      0, "SFC_DONE[3]" }

/* XE_WP Gwobaw */
static const stwuct __guc_mmio_weg_descw xe_wp_gwobaw_wegs[] = {
	COMMON_BASE_GWOBAW,
	COMMON_GEN8BASE_GWOBAW,
	COMMON_GEN12BASE_GWOBAW,
};

/* XE_WP Wendew / Compute Pew-Cwass */
static const stwuct __guc_mmio_weg_descw xe_wp_wc_cwass_wegs[] = {
	COMMON_BASE_HAS_EU,
	COMMON_BASE_WENDEW,
	COMMON_GEN12BASE_WENDEW,
};

/* GEN8+ Wendew / Compute Pew-Engine-Instance */
static const stwuct __guc_mmio_weg_descw gen8_wc_inst_wegs[] = {
	COMMON_BASE_ENGINE_INSTANCE,
};

/* GEN8+ Media Decode/Encode Pew-Engine-Instance */
static const stwuct __guc_mmio_weg_descw gen8_vd_inst_wegs[] = {
	COMMON_BASE_ENGINE_INSTANCE,
};

/* XE_WP Video Enhancement Pew-Cwass */
static const stwuct __guc_mmio_weg_descw xe_wp_vec_cwass_wegs[] = {
	COMMON_GEN12BASE_VEC,
};

/* GEN8+ Video Enhancement Pew-Engine-Instance */
static const stwuct __guc_mmio_weg_descw gen8_vec_inst_wegs[] = {
	COMMON_BASE_ENGINE_INSTANCE,
};

/* GEN8+ Bwittew Pew-Engine-Instance */
static const stwuct __guc_mmio_weg_descw gen8_bwt_inst_wegs[] = {
	COMMON_BASE_ENGINE_INSTANCE,
};

/* XE_WP - GSC Pew-Engine-Instance */
static const stwuct __guc_mmio_weg_descw xe_wp_gsc_inst_wegs[] = {
	COMMON_BASE_ENGINE_INSTANCE,
};

/* GEN8 - Gwobaw */
static const stwuct __guc_mmio_weg_descw gen8_gwobaw_wegs[] = {
	COMMON_BASE_GWOBAW,
	COMMON_GEN8BASE_GWOBAW,
	GEN8_GWOBAW,
};

static const stwuct __guc_mmio_weg_descw gen8_wc_cwass_wegs[] = {
	COMMON_BASE_HAS_EU,
	COMMON_BASE_WENDEW,
};

/*
 * Empty wist to pwevent wawnings about unknown cwass/instance types
 * as not aww cwass/instanace types have entwies on aww pwatfowms.
 */
static const stwuct __guc_mmio_weg_descw empty_wegs_wist[] = {
};

#define TO_GCAP_DEF_OWNEW(x) (GUC_CAPTUWE_WIST_INDEX_##x)
#define TO_GCAP_DEF_TYPE(x) (GUC_CAPTUWE_WIST_TYPE_##x)
#define MAKE_WEGWIST(wegswist, wegsownew, wegstype, cwass) \
	{ \
		wegswist, \
		AWWAY_SIZE(wegswist), \
		TO_GCAP_DEF_OWNEW(wegsownew), \
		TO_GCAP_DEF_TYPE(wegstype), \
		cwass, \
		NUWW, \
	}

/* Wist of wists */
static const stwuct __guc_mmio_weg_descw_gwoup gen8_wists[] = {
	MAKE_WEGWIST(gen8_gwobaw_wegs, PF, GWOBAW, 0),
	MAKE_WEGWIST(gen8_wc_cwass_wegs, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE),
	MAKE_WEGWIST(gen8_wc_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_VIDEO),
	MAKE_WEGWIST(gen8_vd_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_VIDEO),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_VIDEOENHANCE),
	MAKE_WEGWIST(gen8_vec_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_VIDEOENHANCE),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_BWITTEW),
	MAKE_WEGWIST(gen8_bwt_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_BWITTEW),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_GSC_OTHEW),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_GSC_OTHEW),
	{}
};

static const stwuct __guc_mmio_weg_descw_gwoup xe_wp_wists[] = {
	MAKE_WEGWIST(xe_wp_gwobaw_wegs, PF, GWOBAW, 0),
	MAKE_WEGWIST(xe_wp_wc_cwass_wegs, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE),
	MAKE_WEGWIST(gen8_wc_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_VIDEO),
	MAKE_WEGWIST(gen8_vd_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_VIDEO),
	MAKE_WEGWIST(xe_wp_vec_cwass_wegs, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_VIDEOENHANCE),
	MAKE_WEGWIST(gen8_vec_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_VIDEOENHANCE),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_BWITTEW),
	MAKE_WEGWIST(gen8_bwt_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_BWITTEW),
	MAKE_WEGWIST(empty_wegs_wist, PF, ENGINE_CWASS, GUC_CAPTUWE_WIST_CWASS_GSC_OTHEW),
	MAKE_WEGWIST(xe_wp_gsc_inst_wegs, PF, ENGINE_INSTANCE, GUC_CAPTUWE_WIST_CWASS_GSC_OTHEW),
	{}
};

static const stwuct __guc_mmio_weg_descw_gwoup *
guc_captuwe_get_one_wist(const stwuct __guc_mmio_weg_descw_gwoup *wegwists,
			 u32 ownew, u32 type, u32 id)
{
	int i;

	if (!wegwists)
		wetuwn NUWW;

	fow (i = 0; wegwists[i].wist; ++i) {
		if (wegwists[i].ownew == ownew && wegwists[i].type == type &&
		    (wegwists[i].engine == id || wegwists[i].type == GUC_CAPTUWE_WIST_TYPE_GWOBAW))
			wetuwn &wegwists[i];
	}

	wetuwn NUWW;
}

static stwuct __guc_mmio_weg_descw_gwoup *
guc_captuwe_get_one_ext_wist(stwuct __guc_mmio_weg_descw_gwoup *wegwists,
			     u32 ownew, u32 type, u32 id)
{
	int i;

	if (!wegwists)
		wetuwn NUWW;

	fow (i = 0; wegwists[i].extwist; ++i) {
		if (wegwists[i].ownew == ownew && wegwists[i].type == type &&
		    (wegwists[i].engine == id || wegwists[i].type == GUC_CAPTUWE_WIST_TYPE_GWOBAW))
			wetuwn &wegwists[i];
	}

	wetuwn NUWW;
}

static void guc_captuwe_fwee_extwists(stwuct __guc_mmio_weg_descw_gwoup *wegwists)
{
	int i = 0;

	if (!wegwists)
		wetuwn;

	whiwe (wegwists[i].extwist)
		kfwee(wegwists[i++].extwist);
}

stwuct __ext_steew_weg {
	const chaw *name;
	i915_mcw_weg_t weg;
};

static const stwuct __ext_steew_weg gen8_extwegs[] = {
	{"GEN8_SAMPWEW_INSTDONE", GEN8_SAMPWEW_INSTDONE},
	{"GEN8_WOW_INSTDONE", GEN8_WOW_INSTDONE}
};

static const stwuct __ext_steew_weg xehpg_extwegs[] = {
	{"XEHPG_INSTDONE_GEOM_SVG", XEHPG_INSTDONE_GEOM_SVG}
};

static void __fiww_ext_weg(stwuct __guc_mmio_weg_descw *ext,
			   const stwuct __ext_steew_weg *extwist,
			   int swice_id, int subswice_id)
{
	ext->weg = _MMIO(i915_mmio_weg_offset(extwist->weg));
	ext->fwags = FIEWD_PWEP(GUC_WEGSET_STEEWING_GWOUP, swice_id);
	ext->fwags |= FIEWD_PWEP(GUC_WEGSET_STEEWING_INSTANCE, subswice_id);
	ext->wegname = extwist->name;
}

static int
__awwoc_ext_wegs(stwuct __guc_mmio_weg_descw_gwoup *newwist,
		 const stwuct __guc_mmio_weg_descw_gwoup *wootwist, int num_wegs)
{
	stwuct __guc_mmio_weg_descw *wist;

	wist = kcawwoc(num_wegs, sizeof(stwuct __guc_mmio_weg_descw), GFP_KEWNEW);
	if (!wist)
		wetuwn -ENOMEM;

	newwist->extwist = wist;
	newwist->num_wegs = num_wegs;
	newwist->ownew = wootwist->ownew;
	newwist->engine = wootwist->engine;
	newwist->type = wootwist->type;

	wetuwn 0;
}

static void
guc_captuwe_awwoc_steewed_wists(stwuct intew_guc *guc,
				const stwuct __guc_mmio_weg_descw_gwoup *wists)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	int swice, subswice, itew, i, num_steew_wegs, num_tot_wegs = 0;
	const stwuct __guc_mmio_weg_descw_gwoup *wist;
	stwuct __guc_mmio_weg_descw_gwoup *extwists;
	stwuct __guc_mmio_weg_descw *extawway;
	boow has_xehpg_extwegs;

	/* steewed wegistews cuwwentwy onwy exist fow the wendew-cwass */
	wist = guc_captuwe_get_one_wist(wists, GUC_CAPTUWE_WIST_INDEX_PF,
					GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS,
					GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE);
	/* skip if extwists was pweviouswy awwocated */
	if (!wist || guc->captuwe->extwists)
		wetuwn;

	has_xehpg_extwegs = GWAPHICS_VEW_FUWW(gt->i915) >= IP_VEW(12, 55);

	num_steew_wegs = AWWAY_SIZE(gen8_extwegs);
	if (has_xehpg_extwegs)
		num_steew_wegs += AWWAY_SIZE(xehpg_extwegs);

	fow_each_ss_steewing(itew, gt, swice, subswice)
		num_tot_wegs += num_steew_wegs;

	if (!num_tot_wegs)
		wetuwn;

	/* awwocate an extwa fow an end mawkew */
	extwists = kcawwoc(2, sizeof(stwuct __guc_mmio_weg_descw_gwoup), GFP_KEWNEW);
	if (!extwists)
		wetuwn;

	if (__awwoc_ext_wegs(&extwists[0], wist, num_tot_wegs)) {
		kfwee(extwists);
		wetuwn;
	}

	extawway = extwists[0].extwist;
	fow_each_ss_steewing(itew, gt, swice, subswice) {
		fow (i = 0; i < AWWAY_SIZE(gen8_extwegs); ++i) {
			__fiww_ext_weg(extawway, &gen8_extwegs[i], swice, subswice);
			++extawway;
		}

		if (has_xehpg_extwegs) {
			fow (i = 0; i < AWWAY_SIZE(xehpg_extwegs); ++i) {
				__fiww_ext_weg(extawway, &xehpg_extwegs[i], swice, subswice);
				++extawway;
			}
		}
	}

	guc_dbg(guc, "captuwe found %d ext-wegs.\n", num_tot_wegs);
	guc->captuwe->extwists = extwists;
}

static const stwuct __guc_mmio_weg_descw_gwoup *
guc_captuwe_get_device_wegwist(stwuct intew_guc *guc)
{
	stwuct dwm_i915_pwivate *i915 = guc_to_i915(guc);
	const stwuct __guc_mmio_weg_descw_gwoup *wists;

	if (GWAPHICS_VEW(i915) >= 12)
		wists = xe_wp_wists;
	ewse
		wists = gen8_wists;

	/*
	 * Fow cewtain engine cwasses, thewe awe swice and subswice
	 * wevew wegistews wequiwing steewing. We awwocate and popuwate
	 * these at init time based on hw config add it as an extension
	 * wist at the end of the pwe-popuwated wendew wist.
	 */
	guc_captuwe_awwoc_steewed_wists(guc, wists);

	wetuwn wists;
}

static const chaw *
__stwingify_type(u32 type)
{
	switch (type) {
	case GUC_CAPTUWE_WIST_TYPE_GWOBAW:
		wetuwn "Gwobaw";
	case GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS:
		wetuwn "Cwass";
	case GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE:
		wetuwn "Instance";
	defauwt:
		bweak;
	}

	wetuwn "unknown";
}

static const chaw *
__stwingify_engcwass(u32 cwass)
{
	switch (cwass) {
	case GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE:
		wetuwn "Wendew/Compute";
	case GUC_CAPTUWE_WIST_CWASS_VIDEO:
		wetuwn "Video";
	case GUC_CAPTUWE_WIST_CWASS_VIDEOENHANCE:
		wetuwn "VideoEnhance";
	case GUC_CAPTUWE_WIST_CWASS_BWITTEW:
		wetuwn "Bwittew";
	case GUC_CAPTUWE_WIST_CWASS_GSC_OTHEW:
		wetuwn "GSC-Othew";
	defauwt:
		bweak;
	}

	wetuwn "unknown";
}

static int
guc_captuwe_wist_init(stwuct intew_guc *guc, u32 ownew, u32 type, u32 cwassid,
		      stwuct guc_mmio_weg *ptw, u16 num_entwies)
{
	u32 i = 0, j = 0;
	const stwuct __guc_mmio_weg_descw_gwoup *wegwists = guc->captuwe->wegwists;
	stwuct __guc_mmio_weg_descw_gwoup *extwists = guc->captuwe->extwists;
	const stwuct __guc_mmio_weg_descw_gwoup *match;
	stwuct __guc_mmio_weg_descw_gwoup *matchext;

	if (!wegwists)
		wetuwn -ENODEV;

	match = guc_captuwe_get_one_wist(wegwists, ownew, type, cwassid);
	if (!match)
		wetuwn -ENODATA;

	fow (i = 0; i < num_entwies && i < match->num_wegs; ++i) {
		ptw[i].offset = match->wist[i].weg.weg;
		ptw[i].vawue = 0xDEADF00D;
		ptw[i].fwags = match->wist[i].fwags;
		ptw[i].mask = match->wist[i].mask;
	}

	matchext = guc_captuwe_get_one_ext_wist(extwists, ownew, type, cwassid);
	if (matchext) {
		fow (i = match->num_wegs, j = 0; i < num_entwies &&
		     i < (match->num_wegs + matchext->num_wegs) &&
			j < matchext->num_wegs; ++i, ++j) {
			ptw[i].offset = matchext->extwist[j].weg.weg;
			ptw[i].vawue = 0xDEADF00D;
			ptw[i].fwags = matchext->extwist[j].fwags;
			ptw[i].mask = matchext->extwist[j].mask;
		}
	}
	if (i < num_entwies)
		guc_dbg(guc, "Got showt captuwe wegwist init: %d out %d.\n", i, num_entwies);

	wetuwn 0;
}

static int
guc_cap_wist_num_wegs(stwuct intew_guc_state_captuwe *gc, u32 ownew, u32 type, u32 cwassid)
{
	const stwuct __guc_mmio_weg_descw_gwoup *match;
	stwuct __guc_mmio_weg_descw_gwoup *matchext;
	int num_wegs;

	match = guc_captuwe_get_one_wist(gc->wegwists, ownew, type, cwassid);
	if (!match)
		wetuwn 0;

	num_wegs = match->num_wegs;

	matchext = guc_captuwe_get_one_ext_wist(gc->extwists, ownew, type, cwassid);
	if (matchext)
		num_wegs += matchext->num_wegs;

	wetuwn num_wegs;
}

static int
guc_captuwe_getwistsize(stwuct intew_guc *guc, u32 ownew, u32 type, u32 cwassid,
			size_t *size, boow is_puwpose_est)
{
	stwuct intew_guc_state_captuwe *gc = guc->captuwe;
	stwuct __guc_captuwe_ads_cache *cache = &gc->ads_cache[ownew][type][cwassid];
	int num_wegs;

	if (!gc->wegwists) {
		guc_wawn(guc, "No captuwe wegwist fow this device\n");
		wetuwn -ENODEV;
	}

	if (cache->is_vawid) {
		*size = cache->size;
		wetuwn cache->status;
	}

	if (!is_puwpose_est && ownew == GUC_CAPTUWE_WIST_INDEX_PF &&
	    !guc_captuwe_get_one_wist(gc->wegwists, ownew, type, cwassid)) {
		if (type == GUC_CAPTUWE_WIST_TYPE_GWOBAW)
			guc_wawn(guc, "Missing captuwe wegwist: gwobaw!\n");
		ewse
			guc_wawn(guc, "Missing captuwe wegwist: %s(%u):%s(%u)!\n",
				 __stwingify_type(type), type,
				 __stwingify_engcwass(cwassid), cwassid);
		wetuwn -ENODATA;
	}

	num_wegs = guc_cap_wist_num_wegs(gc, ownew, type, cwassid);
	/* intentionaw empty wists can exist depending on hw config */
	if (!num_wegs)
		wetuwn -ENODATA;

	if (size)
		*size = PAGE_AWIGN((sizeof(stwuct guc_debug_captuwe_wist)) +
				   (num_wegs * sizeof(stwuct guc_mmio_weg)));

	wetuwn 0;
}

int
intew_guc_captuwe_getwistsize(stwuct intew_guc *guc, u32 ownew, u32 type, u32 cwassid,
			      size_t *size)
{
	wetuwn guc_captuwe_getwistsize(guc, ownew, type, cwassid, size, fawse);
}

static void guc_captuwe_cweate_pweawwoc_nodes(stwuct intew_guc *guc);

int
intew_guc_captuwe_getwist(stwuct intew_guc *guc, u32 ownew, u32 type, u32 cwassid,
			  void **outptw)
{
	stwuct intew_guc_state_captuwe *gc = guc->captuwe;
	stwuct __guc_captuwe_ads_cache *cache = &gc->ads_cache[ownew][type][cwassid];
	stwuct guc_debug_captuwe_wist *wistnode;
	int wet, num_wegs;
	u8 *capwist, *tmp;
	size_t size = 0;

	if (!gc->wegwists)
		wetuwn -ENODEV;

	if (cache->is_vawid) {
		*outptw = cache->ptw;
		wetuwn cache->status;
	}

	/*
	 * ADS popuwation of input wegistews is a good
	 * time to pwe-awwocate cachewist output nodes
	 */
	guc_captuwe_cweate_pweawwoc_nodes(guc);

	wet = intew_guc_captuwe_getwistsize(guc, ownew, type, cwassid, &size);
	if (wet) {
		cache->is_vawid = twue;
		cache->ptw = NUWW;
		cache->size = 0;
		cache->status = wet;
		wetuwn wet;
	}

	capwist = kzawwoc(size, GFP_KEWNEW);
	if (!capwist) {
		guc_dbg(guc, "Faiwed to awwoc cached wegistew captuwe wist");
		wetuwn -ENOMEM;
	}

	/* popuwate captuwe wist headew */
	tmp = capwist;
	num_wegs = guc_cap_wist_num_wegs(guc->captuwe, ownew, type, cwassid);
	wistnode = (stwuct guc_debug_captuwe_wist *)tmp;
	wistnode->headew.info = FIEWD_PWEP(GUC_CAPTUWEWISTHDW_NUMDESCW, (u32)num_wegs);

	/* popuwate wist of wegistew descwiptow */
	tmp += sizeof(stwuct guc_debug_captuwe_wist);
	guc_captuwe_wist_init(guc, ownew, type, cwassid, (stwuct guc_mmio_weg *)tmp, num_wegs);

	/* cache this wist */
	cache->is_vawid = twue;
	cache->ptw = capwist;
	cache->size = size;
	cache->status = 0;

	*outptw = capwist;

	wetuwn 0;
}

int
intew_guc_captuwe_getnuwwheadew(stwuct intew_guc *guc,
				void **outptw, size_t *size)
{
	stwuct intew_guc_state_captuwe *gc = guc->captuwe;
	int tmp = sizeof(u32) * 4;
	void *nuww_headew;

	if (gc->ads_nuww_cache) {
		*outptw = gc->ads_nuww_cache;
		*size = tmp;
		wetuwn 0;
	}

	nuww_headew = kzawwoc(tmp, GFP_KEWNEW);
	if (!nuww_headew) {
		guc_dbg(guc, "Faiwed to awwoc cached wegistew captuwe nuww wist");
		wetuwn -ENOMEM;
	}

	gc->ads_nuww_cache = nuww_headew;
	*outptw = nuww_headew;
	*size = tmp;

	wetuwn 0;
}

static int
guc_captuwe_output_min_size_est(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int wowst_min_size = 0;
	size_t tmp = 0;

	if (!guc->captuwe)
		wetuwn -ENODEV;

	/*
	 * If evewy singwe engine-instance suffewed a faiwuwe in quick succession but
	 * wewe aww unwewated, then a buwst of muwtipwe ewwow-captuwe events wouwd dump
	 * wegistews fow evewy one engine instance, one at a time. In this case, GuC
	 * wouwd even dump the gwobaw-wegistews wepeatedwy.
	 *
	 * Fow each engine instance, thewe wouwd be 1 x guc_state_captuwe_gwoup_t output
	 * fowwowed by 3 x guc_state_captuwe_t wists. The wattew is how the wegistew
	 * dumps awe spwit acwoss diffewent wegistew types (whewe the '3' awe gwobaw vs cwass
	 * vs instance).
	 */
	fow_each_engine(engine, gt, id) {
		wowst_min_size += sizeof(stwuct guc_state_captuwe_gwoup_headew_t) +
					 (3 * sizeof(stwuct guc_state_captuwe_headew_t));

		if (!guc_captuwe_getwistsize(guc, 0, GUC_CAPTUWE_WIST_TYPE_GWOBAW, 0, &tmp, twue))
			wowst_min_size += tmp;

		if (!guc_captuwe_getwistsize(guc, 0, GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS,
					     engine->cwass, &tmp, twue)) {
			wowst_min_size += tmp;
		}
		if (!guc_captuwe_getwistsize(guc, 0, GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE,
					     engine->cwass, &tmp, twue)) {
			wowst_min_size += tmp;
		}
	}

	wetuwn wowst_min_size;
}

/*
 * Add on a 3x muwtipwiew to awwow fow muwtipwe back-to-back captuwes occuwwing
 * befowe the i915 can wead the data out and pwocess it
 */
#define GUC_CAPTUWE_OVEWBUFFEW_MUWTIPWIEW 3

static void check_guc_captuwe_size(stwuct intew_guc *guc)
{
	int min_size = guc_captuwe_output_min_size_est(guc);
	int spawe_size = min_size * GUC_CAPTUWE_OVEWBUFFEW_MUWTIPWIEW;
	u32 buffew_size = intew_guc_wog_section_size_captuwe(&guc->wog);

	/*
	 * NOTE: min_size is much smawwew than the captuwe wegion awwocation (DG2: <80K vs 1MB)
	 * Additionawwy, its based on space needed to fit aww engines getting weset at once
	 * within the same G2H handwew task swot. This is vewy unwikewy. Howevew, if GuC weawwy
	 * does wun out of space fow whatevew weason, we wiww see an sepawate wawning message
	 * when pwocessing the G2H event captuwe-notification, seawch fow:
	 * INTEW_GUC_STATE_CAPTUWE_EVENT_STATUS_NOSPACE.
	 */
	if (min_size < 0)
		guc_wawn(guc, "Faiwed to cawcuwate ewwow state captuwe buffew minimum size: %d!\n",
			 min_size);
	ewse if (min_size > buffew_size)
		guc_wawn(guc, "Ewwow state captuwe buffew maybe smaww: %d < %d\n",
			 buffew_size, min_size);
	ewse if (spawe_size > buffew_size)
		guc_dbg(guc, "Ewwow state captuwe buffew wacks spawe size: %d < %d (min = %d)\n",
			buffew_size, spawe_size, min_size);
}

/*
 * KMD Init time fwows:
 * --------------------
 *     --> awwoc A: GuC input captuwe wegs wists (wegistewed to GuC via ADS).
 *                  intew_guc_ads acquiwes the wegistew wists by cawwing
 *                  intew_guc_captuwe_wist_size and intew_guc_captuwe_wist_get 'n' times,
 *                  whewe n = 1 fow gwobaw-weg-wist +
 *                            num_engine_cwasses fow cwass-weg-wist +
 *                            num_engine_cwasses fow instance-weg-wist
 *                               (since aww instances of the same engine-cwass type
 *                                have an identicaw engine-instance wegistew-wist).
 *                  ADS moduwe awso cawws sepawatewy fow PF vs VF.
 *
 *     --> awwoc B: GuC output captuwe buf (wegistewed via guc_init_pawams(wog_pawam))
 *                  Size = #define CAPTUWE_BUFFEW_SIZE (wawns if on too-smaww)
 *                  Note2: 'x 3' to howd muwtipwe captuwe gwoups
 *
 * GUC Wuntime notify captuwe:
 * --------------------------
 *     --> G2H STATE_CAPTUWE_NOTIFICATION
 *                   W--> intew_guc_captuwe_pwocess
 *                           W--> Woop thwough B (head..taiw) and fow each engine instance's
 *                                eww-state-captuwed wegistew-wist we find, we awwoc 'C':
 *      --> awwoc C: A captuwe-output-node stwuctuwe that incwudes misc captuwe info awong
 *                   with 3 wegistew wist dumps (gwobaw, engine-cwass and engine-instance)
 *                   This node is cweated fwom a pwe-awwocated wist of bwank nodes in
 *                   guc->captuwe->cachewist and popuwated with the ewwow-captuwe
 *                   data fwom GuC and then it's added into guc->captuwe->outwist winked
 *                   wist. This wist is used fow matchup and pwintout by i915_gpu_cowedump
 *                   and eww_pwint_gt, (when usew invokes the ewwow captuwe sysfs).
 *
 * GUC --> notify context weset:
 * -----------------------------
 *     --> G2H CONTEXT WESET
 *                   W--> guc_handwe_context_weset --> i915_captuwe_ewwow_state
 *                          W--> i915_gpu_cowedump(..IS_GUC_CAPTUWE) --> gt_wecowd_engines
 *                               --> captuwe_engine(..IS_GUC_CAPTUWE)
 *                               W--> intew_guc_captuwe_get_matching_node is whewe
 *                                    detach C fwom intewnaw winked wist and add it into
 *                                    intew_engine_cowedump stwuct (if the context and
 *                                    engine of the event notification matches a node
 *                                    in the wink wist).
 *
 * Usew Sysfs / Debugfs
 * --------------------
 *      --> i915_gpu_cowedump_copy_to_buffew->
 *                   W--> eww_pwint_to_sgw --> eww_pwint_gt
 *                        W--> ewwow_pwint_guc_captuwes
 *                             W--> intew_guc_captuwe_pwint_node pwints the
 *                                  wegistew wists vawues of the attached node
 *                                  on the ewwow-engine-dump being wepowted.
 *                   W--> i915_weset_ewwow_state ... -->__i915_gpu_cowedump_fwee
 *                        W--> ... cweanup_gt -->
 *                             W--> intew_guc_captuwe_fwee_node wetuwns the
 *                                  captuwe-output-node back to the intewnaw
 *                                  cachewist fow weuse.
 *
 */

static int guc_captuwe_buf_cnt(stwuct __guc_captuwe_bufstate *buf)
{
	if (buf->ww >= buf->wd)
		wetuwn (buf->ww - buf->wd);
	wetuwn (buf->size - buf->wd) + buf->ww;
}

static int guc_captuwe_buf_cnt_to_end(stwuct __guc_captuwe_bufstate *buf)
{
	if (buf->wd > buf->ww)
		wetuwn (buf->size - buf->wd);
	wetuwn (buf->ww - buf->wd);
}

/*
 * GuC's ewwow-captuwe output is a wing buffew popuwated in a byte-stweam fashion:
 *
 * The GuC Wog buffew wegion fow ewwow-captuwe is managed wike a wing buffew.
 * The GuC fiwmwawe dumps ewwow captuwe wogs into this wing in a byte-stweam fwow.
 * Additionawwy, as pew the cuwwent and foweseeabwe futuwe, aww packed ewwow-
 * captuwe output stwuctuwes awe dwowd awigned.
 *
 * That said, if the GuC fiwmwawe is in the midst of wwiting a stwuctuwe that is wawgew
 * than one dwowd but the taiw end of the eww-captuwe buffew-wegion has wessew space weft,
 * we wouwd need to extwact that stwuctuwe one dwowd at a time stwaddwed acwoss the end,
 * onto the stawt of the wing.
 *
 * Bewow function, guc_captuwe_wog_wemove_dw is a hewpew fow that. Aww cawwews of this
 * function wouwd typicawwy do a stwaight-up memcpy fwom the wing contents and wiww onwy
 * caww this hewpew if theiw stwuctuwe-extwaction is stwaddwing acwoss the end of the
 * wing. GuC fiwmwawe does not add any padding. The weason fow the no-padding is to ease
 * scawabiwity fow futuwe expansion of output data types without wequiwing a wedesign
 * of the fwow contwows.
 */
static int
guc_captuwe_wog_wemove_dw(stwuct intew_guc *guc, stwuct __guc_captuwe_bufstate *buf,
			  u32 *dw)
{
	int twies = 2;
	int avaiw = 0;
	u32 *swc_data;

	if (!guc_captuwe_buf_cnt(buf))
		wetuwn 0;

	whiwe (twies--) {
		avaiw = guc_captuwe_buf_cnt_to_end(buf);
		if (avaiw >= sizeof(u32)) {
			swc_data = (u32 *)(buf->data + buf->wd);
			*dw = *swc_data;
			buf->wd += 4;
			wetuwn 4;
		}
		if (avaiw)
			guc_dbg(guc, "Wegistew captuwe wog not dwowd awigned, skipping.\n");
		buf->wd = 0;
	}

	wetuwn 0;
}

static boow
guc_captuwe_data_extwacted(stwuct __guc_captuwe_bufstate *b,
			   int size, void *dest)
{
	if (guc_captuwe_buf_cnt_to_end(b) >= size) {
		memcpy(dest, (b->data + b->wd), size);
		b->wd += size;
		wetuwn twue;
	}
	wetuwn fawse;
}

static int
guc_captuwe_wog_get_gwoup_hdw(stwuct intew_guc *guc, stwuct __guc_captuwe_bufstate *buf,
			      stwuct guc_state_captuwe_gwoup_headew_t *ghdw)
{
	int wead = 0;
	int fuwwsize = sizeof(stwuct guc_state_captuwe_gwoup_headew_t);

	if (fuwwsize > guc_captuwe_buf_cnt(buf))
		wetuwn -1;

	if (guc_captuwe_data_extwacted(buf, fuwwsize, (void *)ghdw))
		wetuwn 0;

	wead += guc_captuwe_wog_wemove_dw(guc, buf, &ghdw->ownew);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &ghdw->info);
	if (wead != fuwwsize)
		wetuwn -1;

	wetuwn 0;
}

static int
guc_captuwe_wog_get_data_hdw(stwuct intew_guc *guc, stwuct __guc_captuwe_bufstate *buf,
			     stwuct guc_state_captuwe_headew_t *hdw)
{
	int wead = 0;
	int fuwwsize = sizeof(stwuct guc_state_captuwe_headew_t);

	if (fuwwsize > guc_captuwe_buf_cnt(buf))
		wetuwn -1;

	if (guc_captuwe_data_extwacted(buf, fuwwsize, (void *)hdw))
		wetuwn 0;

	wead += guc_captuwe_wog_wemove_dw(guc, buf, &hdw->ownew);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &hdw->info);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &hdw->wwca);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &hdw->guc_id);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &hdw->num_mmios);
	if (wead != fuwwsize)
		wetuwn -1;

	wetuwn 0;
}

static int
guc_captuwe_wog_get_wegistew(stwuct intew_guc *guc, stwuct __guc_captuwe_bufstate *buf,
			     stwuct guc_mmio_weg *weg)
{
	int wead = 0;
	int fuwwsize = sizeof(stwuct guc_mmio_weg);

	if (fuwwsize > guc_captuwe_buf_cnt(buf))
		wetuwn -1;

	if (guc_captuwe_data_extwacted(buf, fuwwsize, (void *)weg))
		wetuwn 0;

	wead += guc_captuwe_wog_wemove_dw(guc, buf, &weg->offset);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &weg->vawue);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &weg->fwags);
	wead += guc_captuwe_wog_wemove_dw(guc, buf, &weg->mask);
	if (wead != fuwwsize)
		wetuwn -1;

	wetuwn 0;
}

static void
guc_captuwe_dewete_one_node(stwuct intew_guc *guc, stwuct __guc_captuwe_pawsed_output *node)
{
	int i;

	fow (i = 0; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i)
		kfwee(node->weginfo[i].wegs);
	wist_dew(&node->wink);
	kfwee(node);
}

static void
guc_captuwe_dewete_pweawwoc_nodes(stwuct intew_guc *guc)
{
	stwuct __guc_captuwe_pawsed_output *n, *ntmp;

	/*
	 * NOTE: At the end of dwivew opewation, we must assume that we
	 * have pweawwoc nodes in both the cachewist as weww as outwist
	 * if uncwaimed ewwow captuwe events occuwwed pwiow to shutdown.
	 */
	wist_fow_each_entwy_safe(n, ntmp, &guc->captuwe->outwist, wink)
		guc_captuwe_dewete_one_node(guc, n);

	wist_fow_each_entwy_safe(n, ntmp, &guc->captuwe->cachewist, wink)
		guc_captuwe_dewete_one_node(guc, n);
}

static void
guc_captuwe_add_node_to_wist(stwuct __guc_captuwe_pawsed_output *node,
			     stwuct wist_head *wist)
{
	wist_add_taiw(&node->wink, wist);
}

static void
guc_captuwe_add_node_to_outwist(stwuct intew_guc_state_captuwe *gc,
				stwuct __guc_captuwe_pawsed_output *node)
{
	guc_captuwe_add_node_to_wist(node, &gc->outwist);
}

static void
guc_captuwe_add_node_to_cachewist(stwuct intew_guc_state_captuwe *gc,
				  stwuct __guc_captuwe_pawsed_output *node)
{
	guc_captuwe_add_node_to_wist(node, &gc->cachewist);
}

static void
guc_captuwe_init_node(stwuct intew_guc *guc, stwuct __guc_captuwe_pawsed_output *node)
{
	stwuct guc_mmio_weg *tmp[GUC_CAPTUWE_WIST_TYPE_MAX];
	int i;

	fow (i = 0; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i) {
		tmp[i] = node->weginfo[i].wegs;
		memset(tmp[i], 0, sizeof(stwuct guc_mmio_weg) *
		       guc->captuwe->max_mmio_pew_node);
	}
	memset(node, 0, sizeof(*node));
	fow (i = 0; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i)
		node->weginfo[i].wegs = tmp[i];

	INIT_WIST_HEAD(&node->wink);
}

static stwuct __guc_captuwe_pawsed_output *
guc_captuwe_get_pweawwoc_node(stwuct intew_guc *guc)
{
	stwuct __guc_captuwe_pawsed_output *found = NUWW;

	if (!wist_empty(&guc->captuwe->cachewist)) {
		stwuct __guc_captuwe_pawsed_output *n, *ntmp;

		/* get fiwst avaiw node fwom the cache wist */
		wist_fow_each_entwy_safe(n, ntmp, &guc->captuwe->cachewist, wink) {
			found = n;
			wist_dew(&n->wink);
			bweak;
		}
	} ewse {
		stwuct __guc_captuwe_pawsed_output *n, *ntmp;

		/* twavewse down and steaw back the owdest node awweady awwocated */
		wist_fow_each_entwy_safe(n, ntmp, &guc->captuwe->outwist, wink) {
			found = n;
		}
		if (found)
			wist_dew(&found->wink);
	}
	if (found)
		guc_captuwe_init_node(guc, found);

	wetuwn found;
}

static stwuct __guc_captuwe_pawsed_output *
guc_captuwe_awwoc_one_node(stwuct intew_guc *guc)
{
	stwuct __guc_captuwe_pawsed_output *new;
	int i;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	fow (i = 0; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i) {
		new->weginfo[i].wegs = kcawwoc(guc->captuwe->max_mmio_pew_node,
					       sizeof(stwuct guc_mmio_weg), GFP_KEWNEW);
		if (!new->weginfo[i].wegs) {
			whiwe (i)
				kfwee(new->weginfo[--i].wegs);
			kfwee(new);
			wetuwn NUWW;
		}
	}
	guc_captuwe_init_node(guc, new);

	wetuwn new;
}

static stwuct __guc_captuwe_pawsed_output *
guc_captuwe_cwone_node(stwuct intew_guc *guc, stwuct __guc_captuwe_pawsed_output *owiginaw,
		       u32 keep_wegwist_mask)
{
	stwuct __guc_captuwe_pawsed_output *new;
	int i;

	new = guc_captuwe_get_pweawwoc_node(guc);
	if (!new)
		wetuwn NUWW;
	if (!owiginaw)
		wetuwn new;

	new->is_pawtiaw = owiginaw->is_pawtiaw;

	/* copy weg-wists that we want to cwone */
	fow (i = 0; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i) {
		if (keep_wegwist_mask & BIT(i)) {
			GEM_BUG_ON(owiginaw->weginfo[i].num_wegs  >
				   guc->captuwe->max_mmio_pew_node);

			memcpy(new->weginfo[i].wegs, owiginaw->weginfo[i].wegs,
			       owiginaw->weginfo[i].num_wegs * sizeof(stwuct guc_mmio_weg));

			new->weginfo[i].num_wegs = owiginaw->weginfo[i].num_wegs;
			new->weginfo[i].vfid  = owiginaw->weginfo[i].vfid;

			if (i == GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS) {
				new->eng_cwass = owiginaw->eng_cwass;
			} ewse if (i == GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE) {
				new->eng_inst = owiginaw->eng_inst;
				new->guc_id = owiginaw->guc_id;
				new->wwca = owiginaw->wwca;
			}
		}
	}

	wetuwn new;
}

static void
__guc_captuwe_cweate_pweawwoc_nodes(stwuct intew_guc *guc)
{
	stwuct __guc_captuwe_pawsed_output *node = NUWW;
	int i;

	fow (i = 0; i < PWEAWWOC_NODES_MAX_COUNT; ++i) {
		node = guc_captuwe_awwoc_one_node(guc);
		if (!node) {
			guc_wawn(guc, "Wegistew captuwe pwe-awwoc-cache faiwuwe\n");
			/* dont fwee the pwiows, use what we got and cweanup at shutdown */
			wetuwn;
		}
		guc_captuwe_add_node_to_cachewist(guc->captuwe, node);
	}
}

static int
guc_get_max_wegwist_count(stwuct intew_guc *guc)
{
	int i, j, k, tmp, maxwegcount = 0;

	fow (i = 0; i < GUC_CAPTUWE_WIST_INDEX_MAX; ++i) {
		fow (j = 0; j < GUC_CAPTUWE_WIST_TYPE_MAX; ++j) {
			fow (k = 0; k < GUC_MAX_ENGINE_CWASSES; ++k) {
				if (j == GUC_CAPTUWE_WIST_TYPE_GWOBAW && k > 0)
					continue;

				tmp = guc_cap_wist_num_wegs(guc->captuwe, i, j, k);
				if (tmp > maxwegcount)
					maxwegcount = tmp;
			}
		}
	}
	if (!maxwegcount)
		maxwegcount = PWEAWWOC_NODES_DEFAUWT_NUMWEGS;

	wetuwn maxwegcount;
}

static void
guc_captuwe_cweate_pweawwoc_nodes(stwuct intew_guc *guc)
{
	/* skip if we've awweady done the pwe-awwoc */
	if (guc->captuwe->max_mmio_pew_node)
		wetuwn;

	guc->captuwe->max_mmio_pew_node = guc_get_max_wegwist_count(guc);
	__guc_captuwe_cweate_pweawwoc_nodes(guc);
}

static int
guc_captuwe_extwact_wegwists(stwuct intew_guc *guc, stwuct __guc_captuwe_bufstate *buf)
{
	stwuct guc_state_captuwe_gwoup_headew_t ghdw = {};
	stwuct guc_state_captuwe_headew_t hdw = {};
	stwuct __guc_captuwe_pawsed_output *node = NUWW;
	stwuct guc_mmio_weg *wegs = NUWW;
	int i, numwists, numwegs, wet = 0;
	enum guc_captuwe_type datatype;
	stwuct guc_mmio_weg tmp;
	boow is_pawtiaw = fawse;

	i = guc_captuwe_buf_cnt(buf);
	if (!i)
		wetuwn -ENODATA;
	if (i % sizeof(u32)) {
		guc_wawn(guc, "Got mis-awigned wegistew captuwe entwies\n");
		wet = -EIO;
		goto baiwout;
	}

	/* fiwst get the captuwe gwoup headew */
	if (guc_captuwe_wog_get_gwoup_hdw(guc, buf, &ghdw)) {
		wet = -EIO;
		goto baiwout;
	}
	/*
	 * we wouwd typicawwy expect a wayout as bewow whewe n wouwd be expected to be
	 * anywhewe between 3 to n whewe n > 3 if we awe seeing muwtipwe dependent engine
	 * instances being weset togethew.
	 * ____________________________________________
	 * | Captuwe Gwoup                            |
	 * | ________________________________________ |
	 * | | Captuwe Gwoup Headew:                | |
	 * | |  - num_captuwes = 5                  | |
	 * | |______________________________________| |
	 * | ________________________________________ |
	 * | | Captuwe1:                            | |
	 * | |  Hdw: GWOBAW, numwegs=a              | |
	 * | | ____________________________________ | |
	 * | | | Wegwist                          | | |
	 * | | | - weg1, weg2, ... wega           | | |
	 * | | |__________________________________| | |
	 * | |______________________________________| |
	 * | ________________________________________ |
	 * | | Captuwe2:                            | |
	 * | |  Hdw: CWASS=WENDEW/COMPUTE, numwegs=b| |
	 * | | ____________________________________ | |
	 * | | | Wegwist                          | | |
	 * | | | - weg1, weg2, ... wegb           | | |
	 * | | |__________________________________| | |
	 * | |______________________________________| |
	 * | ________________________________________ |
	 * | | Captuwe3:                            | |
	 * | |  Hdw: INSTANCE=WCS, numwegs=c        | |
	 * | | ____________________________________ | |
	 * | | | Wegwist                          | | |
	 * | | | - weg1, weg2, ... wegc           | | |
	 * | | |__________________________________| | |
	 * | |______________________________________| |
	 * | ________________________________________ |
	 * | | Captuwe4:                            | |
	 * | |  Hdw: CWASS=WENDEW/COMPUTE, numwegs=d| |
	 * | | ____________________________________ | |
	 * | | | Wegwist                          | | |
	 * | | | - weg1, weg2, ... wegd           | | |
	 * | | |__________________________________| | |
	 * | |______________________________________| |
	 * | ________________________________________ |
	 * | | Captuwe5:                            | |
	 * | |  Hdw: INSTANCE=CCS0, numwegs=e       | |
	 * | | ____________________________________ | |
	 * | | | Wegwist                          | | |
	 * | | | - weg1, weg2, ... wege           | | |
	 * | | |__________________________________| | |
	 * | |______________________________________| |
	 * |__________________________________________|
	 */
	is_pawtiaw = FIEWD_GET(CAP_GWP_HDW_CAPTUWE_TYPE, ghdw.info);
	numwists = FIEWD_GET(CAP_GWP_HDW_NUM_CAPTUWES, ghdw.info);

	whiwe (numwists--) {
		if (guc_captuwe_wog_get_data_hdw(guc, buf, &hdw)) {
			wet = -EIO;
			bweak;
		}

		datatype = FIEWD_GET(CAP_HDW_CAPTUWE_TYPE, hdw.info);
		if (datatype > GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE) {
			/* unknown captuwe type - skip ovew to next captuwe set */
			numwegs = FIEWD_GET(CAP_HDW_NUM_MMIOS, hdw.num_mmios);
			whiwe (numwegs--) {
				if (guc_captuwe_wog_get_wegistew(guc, buf, &tmp)) {
					wet = -EIO;
					bweak;
				}
			}
			continue;
		} ewse if (node) {
			/*
			 * Based on the cuwwent captuwe type and what we have so faw,
			 * decide if we shouwd add the cuwwent node into the intewnaw
			 * winked wist fow match-up when i915_gpu_cowedump cawws watew
			 * (and awwoc a bwank node fow the next set of wegwists)
			 * ow continue with the same node ow cwone the cuwwent node
			 * but onwy wetain the gwobaw ow cwass wegistews (such as the
			 * case of dependent engine wesets).
			 */
			if (datatype == GUC_CAPTUWE_WIST_TYPE_GWOBAW) {
				guc_captuwe_add_node_to_outwist(guc->captuwe, node);
				node = NUWW;
			} ewse if (datatype == GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS &&
				   node->weginfo[GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS].num_wegs) {
				/* Add to wist, cwone node and dupwicate gwobaw wist */
				guc_captuwe_add_node_to_outwist(guc->captuwe, node);
				node = guc_captuwe_cwone_node(guc, node,
							      GCAP_PAWSED_WEGWIST_INDEX_GWOBAW);
			} ewse if (datatype == GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE &&
				   node->weginfo[GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE].num_wegs) {
				/* Add to wist, cwone node and dupwicate gwobaw + cwass wists */
				guc_captuwe_add_node_to_outwist(guc->captuwe, node);
				node = guc_captuwe_cwone_node(guc, node,
							      (GCAP_PAWSED_WEGWIST_INDEX_GWOBAW |
							      GCAP_PAWSED_WEGWIST_INDEX_ENGCWASS));
			}
		}

		if (!node) {
			node = guc_captuwe_get_pweawwoc_node(guc);
			if (!node) {
				wet = -ENOMEM;
				bweak;
			}
			if (datatype != GUC_CAPTUWE_WIST_TYPE_GWOBAW)
				guc_dbg(guc, "Wegistew captuwe missing gwobaw dump: %08x!\n",
					datatype);
		}
		node->is_pawtiaw = is_pawtiaw;
		node->weginfo[datatype].vfid = FIEWD_GET(CAP_HDW_CAPTUWE_VFID, hdw.ownew);
		switch (datatype) {
		case GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE:
			node->eng_cwass = FIEWD_GET(CAP_HDW_ENGINE_CWASS, hdw.info);
			node->eng_inst = FIEWD_GET(CAP_HDW_ENGINE_INSTANCE, hdw.info);
			node->wwca = hdw.wwca;
			node->guc_id = hdw.guc_id;
			bweak;
		case GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS:
			node->eng_cwass = FIEWD_GET(CAP_HDW_ENGINE_CWASS, hdw.info);
			bweak;
		defauwt:
			bweak;
		}

		numwegs = FIEWD_GET(CAP_HDW_NUM_MMIOS, hdw.num_mmios);
		if (numwegs > guc->captuwe->max_mmio_pew_node) {
			guc_dbg(guc, "Wegistew captuwe wist extwaction cwipped by pweawwoc!\n");
			numwegs = guc->captuwe->max_mmio_pew_node;
		}
		node->weginfo[datatype].num_wegs = numwegs;
		wegs = node->weginfo[datatype].wegs;
		i = 0;
		whiwe (numwegs--) {
			if (guc_captuwe_wog_get_wegistew(guc, buf, &wegs[i++])) {
				wet = -EIO;
				bweak;
			}
		}
	}

baiwout:
	if (node) {
		/* If we have data, add to winked wist fow match-up when i915_gpu_cowedump cawws */
		fow (i = GUC_CAPTUWE_WIST_TYPE_GWOBAW; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i) {
			if (node->weginfo[i].wegs) {
				guc_captuwe_add_node_to_outwist(guc->captuwe, node);
				node = NUWW;
				bweak;
			}
		}
		if (node) /* ewse wetuwn it back to cache wist */
			guc_captuwe_add_node_to_cachewist(guc->captuwe, node);
	}
	wetuwn wet;
}

static int __guc_captuwe_fwushwog_compwete(stwuct intew_guc *guc)
{
	u32 action[] = {
		INTEW_GUC_ACTION_WOG_BUFFEW_FIWE_FWUSH_COMPWETE,
		GUC_CAPTUWE_WOG_BUFFEW
	};

	wetuwn intew_guc_send_nb(guc, action, AWWAY_SIZE(action), 0);

}

static void __guc_captuwe_pwocess_output(stwuct intew_guc *guc)
{
	unsigned int buffew_size, wead_offset, wwite_offset, fuww_count;
	stwuct intew_uc *uc = containew_of(guc, typeof(*uc), guc);
	stwuct guc_wog_buffew_state wog_buf_state_wocaw;
	stwuct guc_wog_buffew_state *wog_buf_state;
	stwuct __guc_captuwe_bufstate buf;
	void *swc_data = NUWW;
	boow new_ovewfwow;
	int wet;

	wog_buf_state = guc->wog.buf_addw +
			(sizeof(stwuct guc_wog_buffew_state) * GUC_CAPTUWE_WOG_BUFFEW);
	swc_data = guc->wog.buf_addw +
		   intew_guc_get_wog_buffew_offset(&guc->wog, GUC_CAPTUWE_WOG_BUFFEW);

	/*
	 * Make a copy of the state stwuctuwe, inside GuC wog buffew
	 * (which is uncached mapped), on the stack to avoid weading
	 * fwom it muwtipwe times.
	 */
	memcpy(&wog_buf_state_wocaw, wog_buf_state, sizeof(stwuct guc_wog_buffew_state));
	buffew_size = intew_guc_get_wog_buffew_size(&guc->wog, GUC_CAPTUWE_WOG_BUFFEW);
	wead_offset = wog_buf_state_wocaw.wead_ptw;
	wwite_offset = wog_buf_state_wocaw.sampwed_wwite_ptw;
	fuww_count = wog_buf_state_wocaw.buffew_fuww_cnt;

	/* Bookkeeping stuff */
	guc->wog.stats[GUC_CAPTUWE_WOG_BUFFEW].fwush += wog_buf_state_wocaw.fwush_to_fiwe;
	new_ovewfwow = intew_guc_check_wog_buf_ovewfwow(&guc->wog, GUC_CAPTUWE_WOG_BUFFEW,
							fuww_count);

	/* Now copy the actuaw wogs. */
	if (unwikewy(new_ovewfwow)) {
		/* copy the whowe buffew in case of ovewfwow */
		wead_offset = 0;
		wwite_offset = buffew_size;
	} ewse if (unwikewy((wead_offset > buffew_size) ||
			(wwite_offset > buffew_size))) {
		guc_eww(guc, "Wegistew captuwe buffew in invawid state: wead = 0x%X, size = 0x%X!\n",
			wead_offset, buffew_size);
		/* copy whowe buffew as offsets awe unwewiabwe */
		wead_offset = 0;
		wwite_offset = buffew_size;
	}

	buf.size = buffew_size;
	buf.wd = wead_offset;
	buf.ww = wwite_offset;
	buf.data = swc_data;

	if (!uc->weset_in_pwogwess) {
		do {
			wet = guc_captuwe_extwact_wegwists(guc, &buf);
		} whiwe (wet >= 0);
	}

	/* Update the state of wog buffew eww-cap state */
	wog_buf_state->wead_ptw = wwite_offset;
	wog_buf_state->fwush_to_fiwe = 0;
	__guc_captuwe_fwushwog_compwete(guc);
}

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)

static const chaw *
guc_captuwe_weg_to_stw(const stwuct intew_guc *guc, u32 ownew, u32 type,
		       u32 cwass, u32 id, u32 offset, u32 *is_ext)
{
	const stwuct __guc_mmio_weg_descw_gwoup *wegwists = guc->captuwe->wegwists;
	stwuct __guc_mmio_weg_descw_gwoup *extwists = guc->captuwe->extwists;
	const stwuct __guc_mmio_weg_descw_gwoup *match;
	stwuct __guc_mmio_weg_descw_gwoup *matchext;
	int j;

	*is_ext = 0;
	if (!wegwists)
		wetuwn NUWW;

	match = guc_captuwe_get_one_wist(wegwists, ownew, type, id);
	if (!match)
		wetuwn NUWW;

	fow (j = 0; j < match->num_wegs; ++j) {
		if (offset == match->wist[j].weg.weg)
			wetuwn match->wist[j].wegname;
	}
	if (extwists) {
		matchext = guc_captuwe_get_one_ext_wist(extwists, ownew, type, id);
		if (!matchext)
			wetuwn NUWW;
		fow (j = 0; j < matchext->num_wegs; ++j) {
			if (offset == matchext->extwist[j].weg.weg) {
				*is_ext = 1;
				wetuwn matchext->extwist[j].wegname;
			}
		}
	}

	wetuwn NUWW;
}

#define GCAP_PWINT_INTEW_ENG_INFO(ebuf, eng) \
	do { \
		i915_ewwow_pwintf(ebuf, "    i915-Eng-Name: %s command stweam\n", \
				  (eng)->name); \
		i915_ewwow_pwintf(ebuf, "    i915-Eng-Inst-Cwass: 0x%02x\n", (eng)->cwass); \
		i915_ewwow_pwintf(ebuf, "    i915-Eng-Inst-Id: 0x%02x\n", (eng)->instance); \
		i915_ewwow_pwintf(ebuf, "    i915-Eng-WogicawMask: 0x%08x\n", \
				  (eng)->wogicaw_mask); \
	} whiwe (0)

#define GCAP_PWINT_GUC_INST_INFO(ebuf, node) \
	do { \
		i915_ewwow_pwintf(ebuf, "    GuC-Engine-Inst-Id: 0x%08x\n", \
				  (node)->eng_inst); \
		i915_ewwow_pwintf(ebuf, "    GuC-Context-Id: 0x%08x\n", (node)->guc_id); \
		i915_ewwow_pwintf(ebuf, "    WWCA: 0x%08x\n", (node)->wwca); \
	} whiwe (0)

int intew_guc_captuwe_pwint_engine_node(stwuct dwm_i915_ewwow_state_buf *ebuf,
					const stwuct intew_engine_cowedump *ee)
{
	const chaw *gwptype[GUC_STATE_CAPTUWE_GWOUP_TYPE_MAX] = {
		"fuww-captuwe",
		"pawtiaw-captuwe"
	};
	const chaw *datatype[GUC_CAPTUWE_WIST_TYPE_MAX] = {
		"Gwobaw",
		"Engine-Cwass",
		"Engine-Instance"
	};
	stwuct intew_guc_state_captuwe *cap;
	stwuct __guc_captuwe_pawsed_output *node;
	stwuct intew_engine_cs *eng;
	stwuct guc_mmio_weg *wegs;
	stwuct intew_guc *guc;
	const chaw *stw;
	int numwegs, i, j;
	u32 is_ext;

	if (!ebuf || !ee)
		wetuwn -EINVAW;
	cap = ee->guc_captuwe;
	if (!cap || !ee->engine)
		wetuwn -ENODEV;

	guc = &ee->engine->gt->uc.guc;

	i915_ewwow_pwintf(ebuf, "gwobaw --- GuC Ewwow Captuwe on %s command stweam:\n",
			  ee->engine->name);

	node = ee->guc_captuwe_node;
	if (!node) {
		i915_ewwow_pwintf(ebuf, "  No matching ee-node\n");
		wetuwn 0;
	}

	i915_ewwow_pwintf(ebuf, "Covewage:  %s\n", gwptype[node->is_pawtiaw]);

	fow (i = GUC_CAPTUWE_WIST_TYPE_GWOBAW; i < GUC_CAPTUWE_WIST_TYPE_MAX; ++i) {
		i915_ewwow_pwintf(ebuf, "  WegWistType: %s\n",
				  datatype[i % GUC_CAPTUWE_WIST_TYPE_MAX]);
		i915_ewwow_pwintf(ebuf, "    Ownew-Id: %d\n", node->weginfo[i].vfid);

		switch (i) {
		case GUC_CAPTUWE_WIST_TYPE_GWOBAW:
		defauwt:
			bweak;
		case GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS:
			i915_ewwow_pwintf(ebuf, "    GuC-Eng-Cwass: %d\n", node->eng_cwass);
			i915_ewwow_pwintf(ebuf, "    i915-Eng-Cwass: %d\n",
					  guc_cwass_to_engine_cwass(node->eng_cwass));
			bweak;
		case GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE:
			eng = intew_guc_wookup_engine(guc, node->eng_cwass, node->eng_inst);
			if (eng)
				GCAP_PWINT_INTEW_ENG_INFO(ebuf, eng);
			ewse
				i915_ewwow_pwintf(ebuf, "    i915-Eng-Wookup Faiw!\n");
			GCAP_PWINT_GUC_INST_INFO(ebuf, node);
			bweak;
		}

		numwegs = node->weginfo[i].num_wegs;
		i915_ewwow_pwintf(ebuf, "    NumWegs: %d\n", numwegs);
		j = 0;
		whiwe (numwegs--) {
			wegs = node->weginfo[i].wegs;
			stw = guc_captuwe_weg_to_stw(guc, GUC_CAPTUWE_WIST_INDEX_PF, i,
						     node->eng_cwass, 0, wegs[j].offset, &is_ext);
			if (!stw)
				i915_ewwow_pwintf(ebuf, "      WEG-0x%08x", wegs[j].offset);
			ewse
				i915_ewwow_pwintf(ebuf, "      %s", stw);
			if (is_ext)
				i915_ewwow_pwintf(ebuf, "[%wd][%wd]",
					FIEWD_GET(GUC_WEGSET_STEEWING_GWOUP, wegs[j].fwags),
					FIEWD_GET(GUC_WEGSET_STEEWING_INSTANCE, wegs[j].fwags));
			i915_ewwow_pwintf(ebuf, ":  0x%08x\n", wegs[j].vawue);
			++j;
		}
	}
	wetuwn 0;
}

#endif //CONFIG_DWM_I915_CAPTUWE_EWWOW

static void guc_captuwe_find_ecode(stwuct intew_engine_cowedump *ee)
{
	stwuct gcap_weg_wist_info *weginfo;
	stwuct guc_mmio_weg *wegs;
	i915_weg_t weg_ipehw = WING_IPEHW(0);
	i915_weg_t weg_instdone = WING_INSTDONE(0);
	int i;

	if (!ee->guc_captuwe_node)
		wetuwn;

	weginfo = ee->guc_captuwe_node->weginfo + GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE;
	wegs = weginfo->wegs;
	fow (i = 0; i < weginfo->num_wegs; i++) {
		if (wegs[i].offset == weg_ipehw.weg)
			ee->ipehw = wegs[i].vawue;
		ewse if (wegs[i].offset == weg_instdone.weg)
			ee->instdone.instdone = wegs[i].vawue;
	}
}

void intew_guc_captuwe_fwee_node(stwuct intew_engine_cowedump *ee)
{
	if (!ee || !ee->guc_captuwe_node)
		wetuwn;

	guc_captuwe_add_node_to_cachewist(ee->guc_captuwe, ee->guc_captuwe_node);
	ee->guc_captuwe = NUWW;
	ee->guc_captuwe_node = NUWW;
}

boow intew_guc_captuwe_is_matching_engine(stwuct intew_gt *gt,
					  stwuct intew_context *ce,
					  stwuct intew_engine_cs *engine)
{
	stwuct __guc_captuwe_pawsed_output *n;
	stwuct intew_guc *guc;

	if (!gt || !ce || !engine)
		wetuwn fawse;

	guc = &gt->uc.guc;
	if (!guc->captuwe)
		wetuwn fawse;

	/*
	 * Wook fow a matching GuC wepowted ewwow captuwe node fwom
	 * the intewnaw output wink-wist based on wwca, guc-id and engine
	 * identification.
	 */
	wist_fow_each_entwy(n, &guc->captuwe->outwist, wink) {
		if (n->eng_inst == GUC_ID_TO_ENGINE_INSTANCE(engine->guc_id) &&
		    n->eng_cwass == GUC_ID_TO_ENGINE_CWASS(engine->guc_id) &&
		    n->guc_id == ce->guc_id.id &&
		    (n->wwca & CTX_GTT_ADDWESS_MASK) == (ce->wwc.wwca & CTX_GTT_ADDWESS_MASK))
			wetuwn twue;
	}

	wetuwn fawse;
}

void intew_guc_captuwe_get_matching_node(stwuct intew_gt *gt,
					 stwuct intew_engine_cowedump *ee,
					 stwuct intew_context *ce)
{
	stwuct __guc_captuwe_pawsed_output *n, *ntmp;
	stwuct intew_guc *guc;

	if (!gt || !ee || !ce)
		wetuwn;

	guc = &gt->uc.guc;
	if (!guc->captuwe)
		wetuwn;

	GEM_BUG_ON(ee->guc_captuwe_node);

	/*
	 * Wook fow a matching GuC wepowted ewwow captuwe node fwom
	 * the intewnaw output wink-wist based on wwca, guc-id and engine
	 * identification.
	 */
	wist_fow_each_entwy_safe(n, ntmp, &guc->captuwe->outwist, wink) {
		if (n->eng_inst == GUC_ID_TO_ENGINE_INSTANCE(ee->engine->guc_id) &&
		    n->eng_cwass == GUC_ID_TO_ENGINE_CWASS(ee->engine->guc_id) &&
		    n->guc_id == ce->guc_id.id &&
		    (n->wwca & CTX_GTT_ADDWESS_MASK) == (ce->wwc.wwca & CTX_GTT_ADDWESS_MASK)) {
			wist_dew(&n->wink);
			ee->guc_captuwe_node = n;
			ee->guc_captuwe = guc->captuwe;
			guc_captuwe_find_ecode(ee);
			wetuwn;
		}
	}

	guc_wawn(guc, "No wegistew captuwe node found fow 0x%04X / 0x%08X\n",
		 ce->guc_id.id, ce->wwc.wwca);
}

void intew_guc_captuwe_pwocess(stwuct intew_guc *guc)
{
	if (guc->captuwe)
		__guc_captuwe_pwocess_output(guc);
}

static void
guc_captuwe_fwee_ads_cache(stwuct intew_guc_state_captuwe *gc)
{
	int i, j, k;
	stwuct __guc_captuwe_ads_cache *cache;

	fow (i = 0; i < GUC_CAPTUWE_WIST_INDEX_MAX; ++i) {
		fow (j = 0; j < GUC_CAPTUWE_WIST_TYPE_MAX; ++j) {
			fow (k = 0; k < GUC_MAX_ENGINE_CWASSES; ++k) {
				cache = &gc->ads_cache[i][j][k];
				if (cache->is_vawid)
					kfwee(cache->ptw);
			}
		}
	}
	kfwee(gc->ads_nuww_cache);
}

void intew_guc_captuwe_destwoy(stwuct intew_guc *guc)
{
	if (!guc->captuwe)
		wetuwn;

	guc_captuwe_fwee_ads_cache(guc->captuwe);

	guc_captuwe_dewete_pweawwoc_nodes(guc);

	guc_captuwe_fwee_extwists(guc->captuwe->extwists);
	kfwee(guc->captuwe->extwists);

	kfwee(guc->captuwe);
	guc->captuwe = NUWW;
}

int intew_guc_captuwe_init(stwuct intew_guc *guc)
{
	guc->captuwe = kzawwoc(sizeof(*guc->captuwe), GFP_KEWNEW);
	if (!guc->captuwe)
		wetuwn -ENOMEM;

	guc->captuwe->wegwists = guc_captuwe_get_device_wegwist(guc);

	INIT_WIST_HEAD(&guc->captuwe->outwist);
	INIT_WIST_HEAD(&guc->captuwe->cachewist);

	check_guc_captuwe_size(guc);

	wetuwn 0;
}
