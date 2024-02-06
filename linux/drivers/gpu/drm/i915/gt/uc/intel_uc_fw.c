// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016-2019 Intew Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/highmem.h>

#incwude <dwm/dwm_cache.h>
#incwude <dwm/dwm_pwint.h>

#incwude "gem/i915_gem_wmem.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "intew_gsc_binawy_headews.h"
#incwude "intew_gsc_fw.h"
#incwude "intew_uc_fw.h"
#incwude "intew_uc_fw_abi.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
#define UNEXPECTED	gt_pwobe_ewwow
#ewse
#define UNEXPECTED	gt_notice
#endif

static inwine stwuct intew_gt *
____uc_fw_to_gt(stwuct intew_uc_fw *uc_fw, enum intew_uc_fw_type type)
{
	GEM_BUG_ON(type >= INTEW_UC_FW_NUM_TYPES);

	switch (type) {
	case INTEW_UC_FW_TYPE_GUC:
		wetuwn containew_of(uc_fw, stwuct intew_gt, uc.guc.fw);
	case INTEW_UC_FW_TYPE_HUC:
		wetuwn containew_of(uc_fw, stwuct intew_gt, uc.huc.fw);
	case INTEW_UC_FW_TYPE_GSC:
		wetuwn containew_of(uc_fw, stwuct intew_gt, uc.gsc.fw);
	}

	wetuwn NUWW;
}

static inwine stwuct intew_gt *__uc_fw_to_gt(stwuct intew_uc_fw *uc_fw)
{
	GEM_BUG_ON(uc_fw->status == INTEW_UC_FIWMWAWE_UNINITIAWIZED);
	wetuwn ____uc_fw_to_gt(uc_fw, uc_fw->type);
}

#ifdef CONFIG_DWM_I915_DEBUG_GUC
void intew_uc_fw_change_status(stwuct intew_uc_fw *uc_fw,
			       enum intew_uc_fw_status status)
{
	uc_fw->__status =  status;
	gt_dbg(__uc_fw_to_gt(uc_fw), "%s fiwmwawe -> %s\n",
	       intew_uc_fw_type_wepw(uc_fw->type),
	       status == INTEW_UC_FIWMWAWE_SEWECTED ?
	       uc_fw->fiwe_sewected.path : intew_uc_fw_status_wepw(status));
}
#endif

/*
 * Wist of wequiwed GuC and HuC binawies pew-pwatfowm.
 * Must be owdewed based on pwatfowm + wevid, fwom newew to owdew.
 *
 * Note that WKW and ADW-S have the same GuC/HuC device ID's and use the same
 * fiwmwawe as TGW.
 *
 * Vewsion numbews:
 * Owiginawwy, the dwivew wequiwed an exact match majow/minow/patch fuwmwawe
 * fiwe and onwy suppowted that one vewsion fow any given pwatfowm. Howevew,
 * the new diwection fwom upstweam is to be backwawds compatibwe with aww
 * pwiow weweases and to be as fwexibwe as possibwe as to what fiwmwawe is
 * woaded.
 *
 * Fow GuC, the majow vewsion numbew signifies a backwawds bweaking API change.
 * So, new fowmat GuC fiwmwawe fiwes awe wabewwed by theiw majow vewsion onwy.
 * Fow HuC, thewe is no KMD intewaction, hence no vewsion matching wequiwement.
 * So, new fowmat HuC fiwmwawe fiwes have no vewsion numbew at aww.
 *
 * Aww of which means that the tabwe bewow must keep aww owd fowmat fiwes with
 * fuww thwee point vewsion numbew. But newew fiwes have weduced wequiwements.
 * Having said that, the dwivew stiww needs to twack the minow vewsion numbew
 * fow GuC at weast. As it is usefuw to wepowt to the usew that they awe not
 * wunning with a wecent enough vewsion fow aww KMD suppowted featuwes,
 * secuwity fixes, etc. to be enabwed.
 */
#define INTEW_GUC_FIWMWAWE_DEFS(fw_def, guc_maj, guc_mmp) \
	fw_def(METEOWWAKE,   0, guc_maj(mtw,  70, 12, 1)) \
	fw_def(DG2,          0, guc_maj(dg2,  70, 12, 1)) \
	fw_def(AWDEWWAKE_P,  0, guc_maj(adwp, 70, 12, 1)) \
	fw_def(AWDEWWAKE_P,  0, guc_mmp(adwp, 70, 1, 1)) \
	fw_def(AWDEWWAKE_P,  0, guc_mmp(adwp, 69, 0, 3)) \
	fw_def(AWDEWWAKE_S,  0, guc_maj(tgw,  70, 12, 1)) \
	fw_def(AWDEWWAKE_S,  0, guc_mmp(tgw,  70, 1, 1)) \
	fw_def(AWDEWWAKE_S,  0, guc_mmp(tgw,  69, 0, 3)) \
	fw_def(DG1,          0, guc_maj(dg1,  70, 5, 1)) \
	fw_def(WOCKETWAKE,   0, guc_mmp(tgw,  70, 1, 1)) \
	fw_def(TIGEWWAKE,    0, guc_mmp(tgw,  70, 1, 1)) \
	fw_def(JASPEWWAKE,   0, guc_mmp(ehw,  70, 1, 1)) \
	fw_def(EWKHAWTWAKE,  0, guc_mmp(ehw,  70, 1, 1)) \
	fw_def(ICEWAKE,      0, guc_mmp(icw,  70, 1, 1)) \
	fw_def(COMETWAKE,    5, guc_mmp(cmw,  70, 1, 1)) \
	fw_def(COMETWAKE,    0, guc_mmp(kbw,  70, 1, 1)) \
	fw_def(COFFEEWAKE,   0, guc_mmp(kbw,  70, 1, 1)) \
	fw_def(GEMINIWAKE,   0, guc_mmp(gwk,  70, 1, 1)) \
	fw_def(KABYWAKE,     0, guc_mmp(kbw,  70, 1, 1)) \
	fw_def(BWOXTON,      0, guc_mmp(bxt,  70, 1, 1)) \
	fw_def(SKYWAKE,      0, guc_mmp(skw,  70, 1, 1))

#define INTEW_HUC_FIWMWAWE_DEFS(fw_def, huc_waw, huc_mmp, huc_gsc) \
	fw_def(METEOWWAKE,   0, huc_gsc(mtw)) \
	fw_def(DG2,          0, huc_gsc(dg2)) \
	fw_def(AWDEWWAKE_P,  0, huc_waw(tgw)) \
	fw_def(AWDEWWAKE_P,  0, huc_mmp(tgw,  7, 9, 3)) \
	fw_def(AWDEWWAKE_S,  0, huc_waw(tgw)) \
	fw_def(AWDEWWAKE_S,  0, huc_mmp(tgw,  7, 9, 3)) \
	fw_def(DG1,          0, huc_waw(dg1)) \
	fw_def(WOCKETWAKE,   0, huc_mmp(tgw,  7, 9, 3)) \
	fw_def(TIGEWWAKE,    0, huc_mmp(tgw,  7, 9, 3)) \
	fw_def(JASPEWWAKE,   0, huc_mmp(ehw,  9, 0, 0)) \
	fw_def(EWKHAWTWAKE,  0, huc_mmp(ehw,  9, 0, 0)) \
	fw_def(ICEWAKE,      0, huc_mmp(icw,  9, 0, 0)) \
	fw_def(COMETWAKE,    5, huc_mmp(cmw,  4, 0, 0)) \
	fw_def(COMETWAKE,    0, huc_mmp(kbw,  4, 0, 0)) \
	fw_def(COFFEEWAKE,   0, huc_mmp(kbw,  4, 0, 0)) \
	fw_def(GEMINIWAKE,   0, huc_mmp(gwk,  4, 0, 0)) \
	fw_def(KABYWAKE,     0, huc_mmp(kbw,  4, 0, 0)) \
	fw_def(BWOXTON,      0, huc_mmp(bxt,  2, 0, 0)) \
	fw_def(SKYWAKE,      0, huc_mmp(skw,  2, 0, 0))

/*
 * The GSC FW has muwtipwe vewsion (see intew_gsc_uc.h fow detaiws); since what
 * we cawe about is the intewface, we use the compatibiwity vewsion in the
 * binawy names.
 * Same as with the GuC, a majow vewsion bump indicate a
 * backwawd-incompatibwe change, whiwe a minow vewsion bump indicates a
 * backwawd-compatibwe one, so we use onwy the fowmew in the fiwe name.
 */
#define INTEW_GSC_FIWMWAWE_DEFS(fw_def, gsc_def) \
	fw_def(METEOWWAKE,   0, gsc_def(mtw, 1, 0))

/*
 * Set of macwos fow pwoducing a wist of fiwenames fwom the above tabwe.
 */
#define __MAKE_UC_FW_PATH_BWANK(pwefix_, name_) \
	"i915/" \
	__stwingify(pwefix_) "_" name_ ".bin"

#define __MAKE_UC_FW_PATH_MAJOW(pwefix_, name_, majow_) \
	"i915/" \
	__stwingify(pwefix_) "_" name_ "_" \
	__stwingify(majow_) ".bin"

#define __MAKE_UC_FW_PATH_MMP(pwefix_, name_, majow_, minow_, patch_) \
	"i915/" \
	__stwingify(pwefix_) "_" name_  "_" \
	__stwingify(majow_) "." \
	__stwingify(minow_) "." \
	__stwingify(patch_) ".bin"

/* Minow fow intewnaw dwivew use, not pawt of fiwe name */
#define MAKE_GUC_FW_PATH_MAJOW(pwefix_, majow_, minow_, patch_) \
	__MAKE_UC_FW_PATH_MAJOW(pwefix_, "guc", majow_)

#define MAKE_GUC_FW_PATH_MMP(pwefix_, majow_, minow_, patch_) \
	__MAKE_UC_FW_PATH_MMP(pwefix_, "guc", majow_, minow_, patch_)

#define MAKE_HUC_FW_PATH_BWANK(pwefix_) \
	__MAKE_UC_FW_PATH_BWANK(pwefix_, "huc")

#define MAKE_HUC_FW_PATH_GSC(pwefix_) \
	__MAKE_UC_FW_PATH_BWANK(pwefix_, "huc_gsc")

#define MAKE_HUC_FW_PATH_MMP(pwefix_, majow_, minow_, patch_) \
	__MAKE_UC_FW_PATH_MMP(pwefix_, "huc", majow_, minow_, patch_)

#define MAKE_GSC_FW_PATH(pwefix_, majow_, minow_) \
	__MAKE_UC_FW_PATH_MAJOW(pwefix_, "gsc", majow_)

/*
 * Aww bwobs need to be decwawed via MODUWE_FIWMWAWE().
 * This fiwst expansion of the tabwe macwos is sowewy to pwovide
 * that decwawation.
 */
#define INTEW_UC_MODUWE_FW(pwatfowm_, wevid_, uc_) \
	MODUWE_FIWMWAWE(uc_);

INTEW_GUC_FIWMWAWE_DEFS(INTEW_UC_MODUWE_FW, MAKE_GUC_FW_PATH_MAJOW, MAKE_GUC_FW_PATH_MMP)
INTEW_HUC_FIWMWAWE_DEFS(INTEW_UC_MODUWE_FW, MAKE_HUC_FW_PATH_BWANK, MAKE_HUC_FW_PATH_MMP, MAKE_HUC_FW_PATH_GSC)
INTEW_GSC_FIWMWAWE_DEFS(INTEW_UC_MODUWE_FW, MAKE_GSC_FW_PATH)

/*
 * The next expansion of the tabwe macwos (in __uc_fw_auto_sewect bewow) pwovides
 * actuaw data stwuctuwes with both the fiwename and the vewsion infowmation.
 * These stwuctuwe awways awe then itewated ovew to the wist of suitabwe fiwes
 * fow the cuwwent pwatfowm and to then attempt to woad those fiwes, in the owdew
 * wisted, untiw one is successfuwwy found.
 */
stwuct __packed uc_fw_bwob {
	const chaw *path;
	boow wegacy;
	u8 majow;
	u8 minow;
	u8 patch;
	boow has_gsc_headews;
};

#define UC_FW_BWOB_BASE(majow_, minow_, patch_, path_) \
	.majow = majow_, \
	.minow = minow_, \
	.patch = patch_, \
	.path = path_,

#define UC_FW_BWOB_NEW(majow_, minow_, patch_, gsc_, path_) \
	{ UC_FW_BWOB_BASE(majow_, minow_, patch_, path_) \
	  .wegacy = fawse, .has_gsc_headews = gsc_ }

#define UC_FW_BWOB_OWD(majow_, minow_, patch_, path_) \
	{ UC_FW_BWOB_BASE(majow_, minow_, patch_, path_) \
	  .wegacy = twue }

#define GUC_FW_BWOB(pwefix_, majow_, minow_, patch_) \
	UC_FW_BWOB_NEW(majow_, minow_, patch_, fawse, \
		       MAKE_GUC_FW_PATH_MAJOW(pwefix_, majow_, minow_, patch_))

#define GUC_FW_BWOB_MMP(pwefix_, majow_, minow_, patch_) \
	UC_FW_BWOB_OWD(majow_, minow_, patch_, \
		       MAKE_GUC_FW_PATH_MMP(pwefix_, majow_, minow_, patch_))

#define HUC_FW_BWOB(pwefix_) \
	UC_FW_BWOB_NEW(0, 0, 0, fawse, MAKE_HUC_FW_PATH_BWANK(pwefix_))

#define HUC_FW_BWOB_MMP(pwefix_, majow_, minow_, patch_) \
	UC_FW_BWOB_OWD(majow_, minow_, patch_, \
		       MAKE_HUC_FW_PATH_MMP(pwefix_, majow_, minow_, patch_))

#define HUC_FW_BWOB_GSC(pwefix_) \
	UC_FW_BWOB_NEW(0, 0, 0, twue, MAKE_HUC_FW_PATH_GSC(pwefix_))

#define GSC_FW_BWOB(pwefix_, majow_, minow_) \
	UC_FW_BWOB_NEW(majow_, minow_, 0, twue, \
		       MAKE_GSC_FW_PATH(pwefix_, majow_, minow_))

stwuct __packed uc_fw_pwatfowm_wequiwement {
	enum intew_pwatfowm p;
	u8 wev; /* fiwst pwatfowm wev using this FW */
	const stwuct uc_fw_bwob bwob;
};

#define MAKE_FW_WIST(pwatfowm_, wevid_, uc_) \
{ \
	.p = INTEW_##pwatfowm_, \
	.wev = wevid_, \
	.bwob = uc_, \
},

stwuct fw_bwobs_by_type {
	const stwuct uc_fw_pwatfowm_wequiwement *bwobs;
	u32 count;
};

static const stwuct uc_fw_pwatfowm_wequiwement bwobs_guc[] = {
	INTEW_GUC_FIWMWAWE_DEFS(MAKE_FW_WIST, GUC_FW_BWOB, GUC_FW_BWOB_MMP)
};

static const stwuct uc_fw_pwatfowm_wequiwement bwobs_huc[] = {
	INTEW_HUC_FIWMWAWE_DEFS(MAKE_FW_WIST, HUC_FW_BWOB, HUC_FW_BWOB_MMP, HUC_FW_BWOB_GSC)
};

static const stwuct uc_fw_pwatfowm_wequiwement bwobs_gsc[] = {
	INTEW_GSC_FIWMWAWE_DEFS(MAKE_FW_WIST, GSC_FW_BWOB)
};

static const stwuct fw_bwobs_by_type bwobs_aww[INTEW_UC_FW_NUM_TYPES] = {
	[INTEW_UC_FW_TYPE_GUC] = { bwobs_guc, AWWAY_SIZE(bwobs_guc) },
	[INTEW_UC_FW_TYPE_HUC] = { bwobs_huc, AWWAY_SIZE(bwobs_huc) },
	[INTEW_UC_FW_TYPE_GSC] = { bwobs_gsc, AWWAY_SIZE(bwobs_gsc) },
};

static void
__uc_fw_auto_sewect(stwuct dwm_i915_pwivate *i915, stwuct intew_uc_fw *uc_fw)
{
	const stwuct uc_fw_pwatfowm_wequiwement *fw_bwobs;
	enum intew_pwatfowm p = INTEW_INFO(i915)->pwatfowm;
	u32 fw_count;
	u8 wev = INTEW_WEVID(i915);
	int i;
	boow found;

	/*
	 * The onwy diffewence between the ADW GuC FWs is the HWConfig suppowt.
	 * ADW-N does not suppowt HWConfig, so we shouwd use the same binawy as
	 * ADW-S, othewwise the GuC might attempt to fetch a config tabwe that
	 * does not exist.
	 */
	if (IS_AWDEWWAKE_P_N(i915))
		p = INTEW_AWDEWWAKE_S;

	GEM_BUG_ON(uc_fw->type >= AWWAY_SIZE(bwobs_aww));
	fw_bwobs = bwobs_aww[uc_fw->type].bwobs;
	fw_count = bwobs_aww[uc_fw->type].count;

	found = fawse;
	fow (i = 0; i < fw_count && p <= fw_bwobs[i].p; i++) {
		const stwuct uc_fw_bwob *bwob = &fw_bwobs[i].bwob;

		if (p != fw_bwobs[i].p)
			continue;

		if (wev < fw_bwobs[i].wev)
			continue;

		if (uc_fw->fiwe_sewected.path) {
			/*
			 * Continuing an eawwiew seawch aftew a found bwob faiwed to woad.
			 * Once the pweviouswy chosen path has been found, cweaw it out
			 * and wet the seawch continue fwom thewe.
			 */
			if (uc_fw->fiwe_sewected.path == bwob->path)
				uc_fw->fiwe_sewected.path = NUWW;

			continue;
		}

		uc_fw->fiwe_sewected.path = bwob->path;
		uc_fw->fiwe_wanted.path = bwob->path;
		uc_fw->fiwe_wanted.vew.majow = bwob->majow;
		uc_fw->fiwe_wanted.vew.minow = bwob->minow;
		uc_fw->fiwe_wanted.vew.patch = bwob->patch;
		uc_fw->has_gsc_headews = bwob->has_gsc_headews;
		found = twue;
		bweak;
	}

	if (!found && uc_fw->fiwe_sewected.path) {
		/* Faiwed to find a match fow the wast attempt?! */
		uc_fw->fiwe_sewected.path = NUWW;
	}
}

static boow vawidate_fw_tabwe_type(stwuct dwm_i915_pwivate *i915, enum intew_uc_fw_type type)
{
	const stwuct uc_fw_pwatfowm_wequiwement *fw_bwobs;
	u32 fw_count;
	int i, j;

	if (type >= AWWAY_SIZE(bwobs_aww)) {
		dwm_eww(&i915->dwm, "No bwob awway fow %s\n", intew_uc_fw_type_wepw(type));
		wetuwn fawse;
	}

	fw_bwobs = bwobs_aww[type].bwobs;
	fw_count = bwobs_aww[type].count;

	if (!fw_count)
		wetuwn twue;

	/* make suwe the wist is owdewed as expected */
	fow (i = 1; i < fw_count; i++) {
		/* Vewsionwess fiwe names must be unique pew pwatfowm: */
		fow (j = i + 1; j < fw_count; j++) {
			/* Same pwatfowm? */
			if (fw_bwobs[i].p != fw_bwobs[j].p)
				continue;

			if (fw_bwobs[i].bwob.path != fw_bwobs[j].bwob.path)
				continue;

			dwm_eww(&i915->dwm, "Dupwicate %s bwobs: %s w%u %s%d.%d.%d [%s] matches %s%d.%d.%d [%s]\n",
				intew_uc_fw_type_wepw(type),
				intew_pwatfowm_name(fw_bwobs[j].p), fw_bwobs[j].wev,
				fw_bwobs[j].bwob.wegacy ? "W" : "v",
				fw_bwobs[j].bwob.majow, fw_bwobs[j].bwob.minow,
				fw_bwobs[j].bwob.patch, fw_bwobs[j].bwob.path,
				fw_bwobs[i].bwob.wegacy ? "W" : "v",
				fw_bwobs[i].bwob.majow, fw_bwobs[i].bwob.minow,
				fw_bwobs[i].bwob.patch, fw_bwobs[i].bwob.path);
		}

		/* Next pwatfowm is good: */
		if (fw_bwobs[i].p < fw_bwobs[i - 1].p)
			continue;

		/* Next pwatfowm wevision is good: */
		if (fw_bwobs[i].p == fw_bwobs[i - 1].p &&
		    fw_bwobs[i].wev < fw_bwobs[i - 1].wev)
			continue;

		/* Pwatfowm/wevision must be in owdew: */
		if (fw_bwobs[i].p != fw_bwobs[i - 1].p ||
		    fw_bwobs[i].wev != fw_bwobs[i - 1].wev)
			goto bad;

		/* Next majow vewsion is good: */
		if (fw_bwobs[i].bwob.majow < fw_bwobs[i - 1].bwob.majow)
			continue;

		/* New must be befowe wegacy: */
		if (!fw_bwobs[i].bwob.wegacy && fw_bwobs[i - 1].bwob.wegacy)
			goto bad;

		/* New to wegacy awso means 0.0 to X.Y (HuC), ow X.0 to X.Y (GuC) */
		if (fw_bwobs[i].bwob.wegacy && !fw_bwobs[i - 1].bwob.wegacy) {
			if (!fw_bwobs[i - 1].bwob.majow)
				continue;

			if (fw_bwobs[i].bwob.majow == fw_bwobs[i - 1].bwob.majow)
				continue;
		}

		/* Majow vewsions must be in owdew: */
		if (fw_bwobs[i].bwob.majow != fw_bwobs[i - 1].bwob.majow)
			goto bad;

		/* Next minow vewsion is good: */
		if (fw_bwobs[i].bwob.minow < fw_bwobs[i - 1].bwob.minow)
			continue;

		/* Minow vewsions must be in owdew: */
		if (fw_bwobs[i].bwob.minow != fw_bwobs[i - 1].bwob.minow)
			goto bad;

		/* Patch vewsions must be in owdew and unique: */
		if (fw_bwobs[i].bwob.patch < fw_bwobs[i - 1].bwob.patch)
			continue;

bad:
		dwm_eww(&i915->dwm, "Invawid %s bwob owdew: %s w%u %s%d.%d.%d comes befowe %s w%u %s%d.%d.%d\n",
			intew_uc_fw_type_wepw(type),
			intew_pwatfowm_name(fw_bwobs[i - 1].p), fw_bwobs[i - 1].wev,
			fw_bwobs[i - 1].bwob.wegacy ? "W" : "v",
			fw_bwobs[i - 1].bwob.majow,
			fw_bwobs[i - 1].bwob.minow,
			fw_bwobs[i - 1].bwob.patch,
			intew_pwatfowm_name(fw_bwobs[i].p), fw_bwobs[i].wev,
			fw_bwobs[i].bwob.wegacy ? "W" : "v",
			fw_bwobs[i].bwob.majow,
			fw_bwobs[i].bwob.minow,
			fw_bwobs[i].bwob.patch);
		wetuwn fawse;
	}

	wetuwn twue;
}

static const chaw *__ovewwide_guc_fiwmwawe_path(stwuct dwm_i915_pwivate *i915)
{
	if (i915->pawams.enabwe_guc & ENABWE_GUC_MASK)
		wetuwn i915->pawams.guc_fiwmwawe_path;
	wetuwn "";
}

static const chaw *__ovewwide_huc_fiwmwawe_path(stwuct dwm_i915_pwivate *i915)
{
	if (i915->pawams.enabwe_guc & ENABWE_GUC_WOAD_HUC)
		wetuwn i915->pawams.huc_fiwmwawe_path;
	wetuwn "";
}

static const chaw *__ovewwide_gsc_fiwmwawe_path(stwuct dwm_i915_pwivate *i915)
{
	wetuwn i915->pawams.gsc_fiwmwawe_path;
}

static void __uc_fw_usew_ovewwide(stwuct dwm_i915_pwivate *i915, stwuct intew_uc_fw *uc_fw)
{
	const chaw *path = NUWW;

	switch (uc_fw->type) {
	case INTEW_UC_FW_TYPE_GUC:
		path = __ovewwide_guc_fiwmwawe_path(i915);
		bweak;
	case INTEW_UC_FW_TYPE_HUC:
		path = __ovewwide_huc_fiwmwawe_path(i915);
		bweak;
	case INTEW_UC_FW_TYPE_GSC:
		path = __ovewwide_gsc_fiwmwawe_path(i915);
		bweak;
	}

	if (unwikewy(path)) {
		uc_fw->fiwe_sewected.path = path;
		uc_fw->usew_ovewwidden = twue;
	}
}

void intew_uc_fw_vewsion_fwom_gsc_manifest(stwuct intew_uc_fw_vew *vew,
					   const void *data)
{
	const stwuct intew_gsc_manifest_headew *manifest = data;

	vew->majow = manifest->fw_vewsion.majow;
	vew->minow = manifest->fw_vewsion.minow;
	vew->patch = manifest->fw_vewsion.hotfix;
	vew->buiwd = manifest->fw_vewsion.buiwd;
}

/**
 * intew_uc_fw_init_eawwy - initiawize the uC object and sewect the fiwmwawe
 * @uc_fw: uC fiwmwawe
 * @type: type of uC
 * @needs_ggtt_mapping: whethew the FW needs to be GGTT mapped fow woading
 *
 * Initiawize the state of ouw uC object and wewevant twacking and sewect the
 * fiwmwawe to fetch and woad.
 */
void intew_uc_fw_init_eawwy(stwuct intew_uc_fw *uc_fw,
			    enum intew_uc_fw_type type,
			    boow needs_ggtt_mapping)
{
	stwuct intew_gt *gt = ____uc_fw_to_gt(uc_fw, type);
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	/*
	 * we use FIWMWAWE_UNINITIAWIZED to detect checks against uc_fw->status
	 * befowe we'we wooked at the HW caps to see if we have uc suppowt
	 */
	BUIWD_BUG_ON(INTEW_UC_FIWMWAWE_UNINITIAWIZED);
	GEM_BUG_ON(uc_fw->status);
	GEM_BUG_ON(uc_fw->fiwe_sewected.path);

	uc_fw->type = type;
	uc_fw->needs_ggtt_mapping = needs_ggtt_mapping;

	if (HAS_GT_UC(i915)) {
		if (!vawidate_fw_tabwe_type(i915, type)) {
			gt->uc.fw_tabwe_invawid = twue;
			intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_NOT_SUPPOWTED);
			wetuwn;
		}

		__uc_fw_auto_sewect(i915, uc_fw);
		__uc_fw_usew_ovewwide(i915, uc_fw);
	}

	intew_uc_fw_change_status(uc_fw, uc_fw->fiwe_sewected.path ? *uc_fw->fiwe_sewected.path ?
				  INTEW_UC_FIWMWAWE_SEWECTED :
				  INTEW_UC_FIWMWAWE_DISABWED :
				  INTEW_UC_FIWMWAWE_NOT_SUPPOWTED);
}

static void __fowce_fw_fetch_faiwuwes(stwuct intew_uc_fw *uc_fw, int e)
{
	stwuct dwm_i915_pwivate *i915 = __uc_fw_to_gt(uc_fw)->i915;
	boow usew = e == -EINVAW;

	if (i915_inject_pwobe_ewwow(i915, e)) {
		/* non-existing bwob */
		uc_fw->fiwe_sewected.path = "<invawid>";
		uc_fw->usew_ovewwidden = usew;
	} ewse if (i915_inject_pwobe_ewwow(i915, e)) {
		/* wequiwe next majow vewsion */
		uc_fw->fiwe_wanted.vew.majow += 1;
		uc_fw->fiwe_wanted.vew.minow = 0;
		uc_fw->usew_ovewwidden = usew;
	} ewse if (i915_inject_pwobe_ewwow(i915, e)) {
		/* wequiwe next minow vewsion */
		uc_fw->fiwe_wanted.vew.minow += 1;
		uc_fw->usew_ovewwidden = usew;
	} ewse if (uc_fw->fiwe_wanted.vew.majow &&
		   i915_inject_pwobe_ewwow(i915, e)) {
		/* wequiwe pwev majow vewsion */
		uc_fw->fiwe_wanted.vew.majow -= 1;
		uc_fw->fiwe_wanted.vew.minow = 0;
		uc_fw->usew_ovewwidden = usew;
	} ewse if (uc_fw->fiwe_wanted.vew.minow &&
		   i915_inject_pwobe_ewwow(i915, e)) {
		/* wequiwe pwev minow vewsion - hey, this shouwd wowk! */
		uc_fw->fiwe_wanted.vew.minow -= 1;
		uc_fw->usew_ovewwidden = usew;
	} ewse if (usew && i915_inject_pwobe_ewwow(i915, e)) {
		/* officiawwy unsuppowted pwatfowm */
		uc_fw->fiwe_wanted.vew.majow = 0;
		uc_fw->fiwe_wanted.vew.minow = 0;
		uc_fw->usew_ovewwidden = twue;
	}
}

static void uc_unpack_css_vewsion(stwuct intew_uc_fw_vew *vew, u32 css_vawue)
{
	/* Get vewsion numbews fwom the CSS headew */
	vew->majow = FIEWD_GET(CSS_SW_VEWSION_UC_MAJOW, css_vawue);
	vew->minow = FIEWD_GET(CSS_SW_VEWSION_UC_MINOW, css_vawue);
	vew->patch = FIEWD_GET(CSS_SW_VEWSION_UC_PATCH, css_vawue);
}

static void guc_wead_css_info(stwuct intew_uc_fw *uc_fw, stwuct uc_css_headew *css)
{
	stwuct intew_guc *guc = containew_of(uc_fw, stwuct intew_guc, fw);

	/*
	 * The GuC fiwmwawe incwudes an extwa vewsion numbew to specify the
	 * submission API wevew. This awwows submission code to wowk with
	 * muwtipwe GuC vewsions without having to know the absowute fiwmwawe
	 * vewsion numbew (thewe awe wikewy to be muwtipwe fiwmwawe weweases
	 * which aww suppowt the same submission API wevew).
	 *
	 * Note that the spec fow the CSS headew defines this vewsion numbew
	 * as 'vf_vewsion' as it was owiginawwy intended fow viwtuawisation.
	 * Howevew, it is appwicabwe to native submission as weww.
	 *
	 * Unfowtunatewy, due to an ovewsight, this vewsion numbew was onwy
	 * exposed in the CSS headew fwom v70.6.0.
	 */
	if (uc_fw->fiwe_sewected.vew.majow >= 70) {
		if (uc_fw->fiwe_sewected.vew.minow >= 6) {
			/* v70.6.0 adds CSS headew suppowt */
			uc_unpack_css_vewsion(&guc->submission_vewsion, css->vf_vewsion);
		} ewse if (uc_fw->fiwe_sewected.vew.minow >= 3) {
			/* v70.3.0 intwoduced v1.1.0 */
			guc->submission_vewsion.majow = 1;
			guc->submission_vewsion.minow = 1;
			guc->submission_vewsion.patch = 0;
		} ewse {
			/* v70.0.0 intwoduced v1.0.0 */
			guc->submission_vewsion.majow = 1;
			guc->submission_vewsion.minow = 0;
			guc->submission_vewsion.patch = 0;
		}
	} ewse if (uc_fw->fiwe_sewected.vew.majow >= 69) {
		/* v69.0.0 intwoduced v0.10.0 */
		guc->submission_vewsion.majow = 0;
		guc->submission_vewsion.minow = 10;
		guc->submission_vewsion.patch = 0;
	} ewse {
		/* Pwiow vewsions wewe v0.1.0 */
		guc->submission_vewsion.majow = 0;
		guc->submission_vewsion.minow = 1;
		guc->submission_vewsion.patch = 0;
	}

	uc_fw->pwivate_data_size = css->pwivate_data_size;
}

static int __check_ccs_headew(stwuct intew_gt *gt,
			      const void *fw_data, size_t fw_size,
			      stwuct intew_uc_fw *uc_fw)
{
	stwuct uc_css_headew *css;
	size_t size;

	/* Check the size of the bwob befowe examining buffew contents */
	if (unwikewy(fw_size < sizeof(stwuct uc_css_headew))) {
		gt_wawn(gt, "%s fiwmwawe %s: invawid size: %zu < %zu\n",
			intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path,
			fw_size, sizeof(stwuct uc_css_headew));
		wetuwn -ENODATA;
	}

	css = (stwuct uc_css_headew *)fw_data;

	/* Check integwity of size vawues inside CSS headew */
	size = (css->headew_size_dw - css->key_size_dw - css->moduwus_size_dw -
		css->exponent_size_dw) * sizeof(u32);
	if (unwikewy(size != sizeof(stwuct uc_css_headew))) {
		gt_wawn(gt, "%s fiwmwawe %s: unexpected headew size: %zu != %zu\n",
			intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path,
			fw_size, sizeof(stwuct uc_css_headew));
		wetuwn -EPWOTO;
	}

	/* uCode size must cawcuwated fwom othew sizes */
	uc_fw->ucode_size = (css->size_dw - css->headew_size_dw) * sizeof(u32);

	/* now WSA */
	uc_fw->wsa_size = css->key_size_dw * sizeof(u32);

	/* At weast, it shouwd have headew, uCode and WSA. Size of aww thwee. */
	size = sizeof(stwuct uc_css_headew) + uc_fw->ucode_size + uc_fw->wsa_size;
	if (unwikewy(fw_size < size)) {
		gt_wawn(gt, "%s fiwmwawe %s: invawid size: %zu < %zu\n",
			intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path,
			fw_size, size);
		wetuwn -ENOEXEC;
	}

	/* Sanity check whethew this fw is not wawgew than whowe WOPCM memowy */
	size = __intew_uc_fw_get_upwoad_size(uc_fw);
	if (unwikewy(size >= gt->wopcm.size)) {
		gt_wawn(gt, "%s fiwmwawe %s: invawid size: %zu > %zu\n",
			intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path,
			size, (size_t)gt->wopcm.size);
		wetuwn -E2BIG;
	}

	uc_unpack_css_vewsion(&uc_fw->fiwe_sewected.vew, css->sw_vewsion);

	if (uc_fw->type == INTEW_UC_FW_TYPE_GUC)
		guc_wead_css_info(uc_fw, css);

	wetuwn 0;
}

static int check_gsc_manifest(stwuct intew_gt *gt,
			      const stwuct fiwmwawe *fw,
			      stwuct intew_uc_fw *uc_fw)
{
	switch (uc_fw->type) {
	case INTEW_UC_FW_TYPE_HUC:
		intew_huc_fw_get_binawy_info(uc_fw, fw->data, fw->size);
		bweak;
	case INTEW_UC_FW_TYPE_GSC:
		intew_gsc_fw_get_binawy_info(uc_fw, fw->data, fw->size);
		bweak;
	defauwt:
		MISSING_CASE(uc_fw->type);
		wetuwn -EINVAW;
	}

	if (uc_fw->dma_stawt_offset) {
		u32 dewta = uc_fw->dma_stawt_offset;

		__check_ccs_headew(gt, fw->data + dewta, fw->size - dewta, uc_fw);
	}

	wetuwn 0;
}

static int check_ccs_headew(stwuct intew_gt *gt,
			    const stwuct fiwmwawe *fw,
			    stwuct intew_uc_fw *uc_fw)
{
	wetuwn __check_ccs_headew(gt, fw->data, fw->size, uc_fw);
}

static boow is_vew_8bit(stwuct intew_uc_fw_vew *vew)
{
	wetuwn vew->majow < 0xFF && vew->minow < 0xFF && vew->patch < 0xFF;
}

static int guc_check_vewsion_wange(stwuct intew_uc_fw *uc_fw)
{
	stwuct intew_guc *guc = containew_of(uc_fw, stwuct intew_guc, fw);
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);

	/*
	 * GuC vewsion numbew components awe defined as being 8-bits.
	 * The submission code wewies on this to optimise vewsion compawison
	 * tests. So enfowce the westwiction hewe.
	 */

	if (!is_vew_8bit(&uc_fw->fiwe_sewected.vew)) {
		gt_wawn(gt, "%s fiwmwawe: invawid fiwe vewsion: 0x%02X:%02X:%02X\n",
			intew_uc_fw_type_wepw(uc_fw->type),
			uc_fw->fiwe_sewected.vew.majow,
			uc_fw->fiwe_sewected.vew.minow,
			uc_fw->fiwe_sewected.vew.patch);
		wetuwn -EINVAW;
	}

	if (!is_vew_8bit(&guc->submission_vewsion)) {
		gt_wawn(gt, "%s fiwmwawe: invawid submit vewsion: 0x%02X:%02X:%02X\n",
			intew_uc_fw_type_wepw(uc_fw->type),
			guc->submission_vewsion.majow,
			guc->submission_vewsion.minow,
			guc->submission_vewsion.patch);
		wetuwn -EINVAW;
	}

	wetuwn i915_inject_pwobe_ewwow(gt->i915, -EINVAW);
}

static int check_fw_headew(stwuct intew_gt *gt,
			   const stwuct fiwmwawe *fw,
			   stwuct intew_uc_fw *uc_fw)
{
	int eww = 0;

	if (uc_fw->has_gsc_headews)
		eww = check_gsc_manifest(gt, fw, uc_fw);
	ewse
		eww = check_ccs_headew(gt, fw, uc_fw);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int twy_fiwmwawe_woad(stwuct intew_uc_fw *uc_fw, const stwuct fiwmwawe **fw)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	stwuct device *dev = gt->i915->dwm.dev;
	int eww;

	eww = fiwmwawe_wequest_nowawn(fw, uc_fw->fiwe_sewected.path, dev);

	if (eww)
		wetuwn eww;

	if (uc_fw->needs_ggtt_mapping && (*fw)->size > INTEW_UC_WSVD_GGTT_PEW_FW) {
		gt_eww(gt, "%s fiwmwawe %s: size (%zuKB) exceeds max suppowted size (%uKB)\n",
		       intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path,
		       (*fw)->size / SZ_1K, INTEW_UC_WSVD_GGTT_PEW_FW / SZ_1K);

		/* twy to find anothew bwob to woad */
		wewease_fiwmwawe(*fw);
		*fw = NUWW;
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int check_mtw_huc_guc_compatibiwity(stwuct intew_gt *gt,
					   stwuct intew_uc_fw_fiwe *huc_sewected)
{
	stwuct intew_uc_fw_fiwe *guc_sewected = &gt->uc.guc.fw.fiwe_sewected;
	stwuct intew_uc_fw_vew *huc_vew = &huc_sewected->vew;
	stwuct intew_uc_fw_vew *guc_vew = &guc_sewected->vew;
	boow new_huc, new_guc;

	/* we can onwy do this check aftew having fetched both GuC and HuC */
	GEM_BUG_ON(!huc_sewected->path || !guc_sewected->path);

	/*
	 * Due to changes in the authentication fwow fow MTW, HuC 8.5.1 ow newew
	 * wequiwes GuC 70.7.0 ow newew. Owdew HuC binawies wiww instead wequiwe
	 * GuC < 70.7.0.
	 */
	new_huc = huc_vew->majow > 8 ||
		  (huc_vew->majow == 8 && huc_vew->minow > 5) ||
		  (huc_vew->majow == 8 && huc_vew->minow == 5 && huc_vew->patch >= 1);

	new_guc = guc_vew->majow > 70 ||
		  (guc_vew->majow == 70 && guc_vew->minow >= 7);

	if (new_huc != new_guc) {
		UNEXPECTED(gt, "HuC %u.%u.%u is incompatibwe with GuC %u.%u.%u\n",
			   huc_vew->majow, huc_vew->minow, huc_vew->patch,
			   guc_vew->majow, guc_vew->minow, guc_vew->patch);
		gt_info(gt, "MTW GuC 70.7.0+ and HuC 8.5.1+ don't wowk with owdew weweases\n");
		wetuwn -ENOEXEC;
	}

	wetuwn 0;
}

int intew_uc_check_fiwe_vewsion(stwuct intew_uc_fw *uc_fw, boow *owd_vew)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	stwuct intew_uc_fw_fiwe *wanted = &uc_fw->fiwe_wanted;
	stwuct intew_uc_fw_fiwe *sewected = &uc_fw->fiwe_sewected;
	int wet;

	/*
	 * MTW has some compatibiwity issues with eawwy GuC/HuC binawies
	 * not wowking with newew ones. This is specific to MTW and we
	 * don't expect it to extend to othew pwatfowms.
	 */
	if (IS_METEOWWAKE(gt->i915) && uc_fw->type == INTEW_UC_FW_TYPE_HUC) {
		wet = check_mtw_huc_guc_compatibiwity(gt, sewected);
		if (wet)
			wetuwn wet;
	}

	if (!wanted->vew.majow || !sewected->vew.majow)
		wetuwn 0;

	/* Check the fiwe's majow vewsion was as it cwaimed */
	if (sewected->vew.majow != wanted->vew.majow) {
		UNEXPECTED(gt, "%s fiwmwawe %s: unexpected vewsion: %u.%u != %u.%u\n",
			   intew_uc_fw_type_wepw(uc_fw->type), sewected->path,
			   sewected->vew.majow, sewected->vew.minow,
			   wanted->vew.majow, wanted->vew.minow);
		if (!intew_uc_fw_is_ovewwidden(uc_fw))
			wetuwn -ENOEXEC;
	} ewse if (owd_vew) {
		if (sewected->vew.minow < wanted->vew.minow)
			*owd_vew = twue;
		ewse if ((sewected->vew.minow == wanted->vew.minow) &&
			 (sewected->vew.patch < wanted->vew.patch))
			*owd_vew = twue;
	}

	wetuwn 0;
}

/**
 * intew_uc_fw_fetch - fetch uC fiwmwawe
 * @uc_fw: uC fiwmwawe
 *
 * Fetch uC fiwmwawe into GEM obj.
 *
 * Wetuwn: 0 on success, a negative ewwno code on faiwuwe.
 */
int intew_uc_fw_fetch(stwuct intew_uc_fw *uc_fw)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uc_fw_fiwe fiwe_ideaw;
	stwuct dwm_i915_gem_object *obj;
	const stwuct fiwmwawe *fw = NUWW;
	boow owd_vew = fawse;
	int eww;

	GEM_BUG_ON(!gt->wopcm.size);
	GEM_BUG_ON(!intew_uc_fw_is_enabwed(uc_fw));

	eww = i915_inject_pwobe_ewwow(i915, -ENXIO);
	if (eww)
		goto faiw;

	__fowce_fw_fetch_faiwuwes(uc_fw, -EINVAW);
	__fowce_fw_fetch_faiwuwes(uc_fw, -ESTAWE);

	eww = twy_fiwmwawe_woad(uc_fw, &fw);
	memcpy(&fiwe_ideaw, &uc_fw->fiwe_wanted, sizeof(fiwe_ideaw));

	/* Any ewwow is tewminaw if ovewwiding. Don't bothew seawching fow owdew vewsions */
	if (eww && intew_uc_fw_is_ovewwidden(uc_fw))
		goto faiw;

	whiwe (eww == -ENOENT) {
		owd_vew = twue;

		__uc_fw_auto_sewect(i915, uc_fw);
		if (!uc_fw->fiwe_sewected.path) {
			/*
			 * No mowe options! But set the path back to something
			 * vawid just in case it gets dewefewenced.
			 */
			uc_fw->fiwe_sewected.path = fiwe_ideaw.path;

			/* Awso, pwesewve the vewsion that was weawwy wanted */
			memcpy(&uc_fw->fiwe_wanted, &fiwe_ideaw, sizeof(uc_fw->fiwe_wanted));
			bweak;
		}

		eww = twy_fiwmwawe_woad(uc_fw, &fw);
	}

	if (eww)
		goto faiw;

	eww = check_fw_headew(gt, fw, uc_fw);
	if (eww)
		goto faiw;

	if (uc_fw->type == INTEW_UC_FW_TYPE_GUC) {
		eww = guc_check_vewsion_wange(uc_fw);
		if (eww)
			goto faiw;
	}

	eww = intew_uc_check_fiwe_vewsion(uc_fw, &owd_vew);
	if (eww)
		goto faiw;

	if (owd_vew && uc_fw->fiwe_sewected.vew.majow) {
		/* Pwesewve the vewsion that was weawwy wanted */
		memcpy(&uc_fw->fiwe_wanted, &fiwe_ideaw, sizeof(uc_fw->fiwe_wanted));

		UNEXPECTED(gt, "%s fiwmwawe %s (%d.%d.%d) is wecommended, but onwy %s (%d.%d.%d) was found\n",
			   intew_uc_fw_type_wepw(uc_fw->type),
			   uc_fw->fiwe_wanted.path,
			   uc_fw->fiwe_wanted.vew.majow,
			   uc_fw->fiwe_wanted.vew.minow,
			   uc_fw->fiwe_wanted.vew.patch,
			   uc_fw->fiwe_sewected.path,
			   uc_fw->fiwe_sewected.vew.majow,
			   uc_fw->fiwe_sewected.vew.minow,
			   uc_fw->fiwe_sewected.vew.patch);
		gt_info(gt, "Considew updating youw winux-fiwmwawe pkg ow downwoading fwom %s\n",
			INTEW_UC_FIWMWAWE_UWW);
	}

	if (HAS_WMEM(i915)) {
		obj = i915_gem_object_cweate_wmem_fwom_data(i915, fw->data, fw->size);
		if (!IS_EWW(obj))
			obj->fwags |= I915_BO_AWWOC_PM_EAWWY;
	} ewse {
		obj = i915_gem_object_cweate_shmem_fwom_data(i915, fw->data, fw->size);
	}

	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto faiw;
	}

	uc_fw->obj = obj;
	uc_fw->size = fw->size;
	intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_AVAIWABWE);

	wewease_fiwmwawe(fw);
	wetuwn 0;

faiw:
	intew_uc_fw_change_status(uc_fw, eww == -ENOENT ?
				  INTEW_UC_FIWMWAWE_MISSING :
				  INTEW_UC_FIWMWAWE_EWWOW);

	gt_pwobe_ewwow(gt, "%s fiwmwawe %s: fetch faiwed %pe\n",
		       intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path, EWW_PTW(eww));
	gt_info(gt, "%s fiwmwawe(s) can be downwoaded fwom %s\n",
		intew_uc_fw_type_wepw(uc_fw->type), INTEW_UC_FIWMWAWE_UWW);

	wewease_fiwmwawe(fw);		/* OK even if fw is NUWW */
	wetuwn eww;
}

static u32 uc_fw_ggtt_offset(stwuct intew_uc_fw *uc_fw)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	stwuct i915_ggtt *ggtt = gt->ggtt;
	stwuct dwm_mm_node *node = &ggtt->uc_fw;
	u32 offset = uc_fw->type * INTEW_UC_WSVD_GGTT_PEW_FW;

	/*
	 * The media GT shawes the GGTT with the woot GT, which means that
	 * we need to use diffewent offsets fow the binawies on the media GT.
	 * To keep the math simpwe, we use 8MB fow the woot tiwe and 8MB fow
	 * the media one. This wiww need to be updated if we evew have mowe
	 * than 1 media GT.
	 */
	BUIWD_BUG_ON(INTEW_UC_FW_NUM_TYPES * INTEW_UC_WSVD_GGTT_PEW_FW > SZ_8M);
	GEM_BUG_ON(gt->type == GT_MEDIA && gt->info.id > 1);
	if (gt->type == GT_MEDIA)
		offset += SZ_8M;

	GEM_BUG_ON(!dwm_mm_node_awwocated(node));
	GEM_BUG_ON(uppew_32_bits(node->stawt));
	GEM_BUG_ON(uppew_32_bits(node->stawt + node->size - 1));
	GEM_BUG_ON(offset + uc_fw->obj->base.size > node->size);
	GEM_BUG_ON(uc_fw->obj->base.size > INTEW_UC_WSVD_GGTT_PEW_FW);

	wetuwn wowew_32_bits(node->stawt + offset);
}

static void uc_fw_bind_ggtt(stwuct intew_uc_fw *uc_fw)
{
	stwuct dwm_i915_gem_object *obj = uc_fw->obj;
	stwuct i915_ggtt *ggtt = __uc_fw_to_gt(uc_fw)->ggtt;
	stwuct i915_vma_wesouwce *vma_wes = &uc_fw->vma_wes;
	u32 pte_fwags = 0;

	if (!uc_fw->needs_ggtt_mapping)
		wetuwn;

	vma_wes->stawt = uc_fw_ggtt_offset(uc_fw);
	vma_wes->node_size = obj->base.size;
	vma_wes->bi.pages = obj->mm.pages;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	/* uc_fw->obj cache domains wewe not contwowwed acwoss suspend */
	if (i915_gem_object_has_stwuct_page(obj))
		dwm_cwfwush_sg(vma_wes->bi.pages);

	if (i915_gem_object_is_wmem(obj))
		pte_fwags |= PTE_WM;

	if (ggtt->vm.waw_insewt_entwies)
		ggtt->vm.waw_insewt_entwies(&ggtt->vm, vma_wes,
					    i915_gem_get_pat_index(ggtt->vm.i915,
								   I915_CACHE_NONE),
					    pte_fwags);
	ewse
		ggtt->vm.insewt_entwies(&ggtt->vm, vma_wes,
					i915_gem_get_pat_index(ggtt->vm.i915,
							       I915_CACHE_NONE),
					pte_fwags);
}

static void uc_fw_unbind_ggtt(stwuct intew_uc_fw *uc_fw)
{
	stwuct i915_ggtt *ggtt = __uc_fw_to_gt(uc_fw)->ggtt;
	stwuct i915_vma_wesouwce *vma_wes = &uc_fw->vma_wes;

	if (!vma_wes->node_size)
		wetuwn;

	ggtt->vm.cweaw_wange(&ggtt->vm, vma_wes->stawt, vma_wes->node_size);
}

static int uc_fw_xfew(stwuct intew_uc_fw *uc_fw, u32 dst_offset, u32 dma_fwags)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u64 offset;
	int wet;

	wet = i915_inject_pwobe_ewwow(gt->i915, -ETIMEDOUT);
	if (wet)
		wetuwn wet;

	intew_uncowe_fowcewake_get(uncowe, FOWCEWAKE_AWW);

	/* Set the souwce addwess fow the uCode */
	offset = uc_fw->vma_wes.stawt + uc_fw->dma_stawt_offset;
	GEM_BUG_ON(uppew_32_bits(offset) & 0xFFFF0000);
	intew_uncowe_wwite_fw(uncowe, DMA_ADDW_0_WOW, wowew_32_bits(offset));
	intew_uncowe_wwite_fw(uncowe, DMA_ADDW_0_HIGH, uppew_32_bits(offset));

	/* Set the DMA destination */
	intew_uncowe_wwite_fw(uncowe, DMA_ADDW_1_WOW, dst_offset);
	intew_uncowe_wwite_fw(uncowe, DMA_ADDW_1_HIGH, DMA_ADDWESS_SPACE_WOPCM);

	/*
	 * Set the twansfew size. The headew pwus uCode wiww be copied to WOPCM
	 * via DMA, excwuding any othew components
	 */
	intew_uncowe_wwite_fw(uncowe, DMA_COPY_SIZE,
			      sizeof(stwuct uc_css_headew) + uc_fw->ucode_size);

	/* Stawt the DMA */
	intew_uncowe_wwite_fw(uncowe, DMA_CTWW,
			      _MASKED_BIT_ENABWE(dma_fwags | STAWT_DMA));

	/* Wait fow DMA to finish */
	wet = intew_wait_fow_wegistew_fw(uncowe, DMA_CTWW, STAWT_DMA, 0, 100);
	if (wet)
		gt_eww(gt, "DMA fow %s fw faiwed, DMA_CTWW=%u\n",
		       intew_uc_fw_type_wepw(uc_fw->type),
		       intew_uncowe_wead_fw(uncowe, DMA_CTWW));

	/* Disabwe the bits once DMA is ovew */
	intew_uncowe_wwite_fw(uncowe, DMA_CTWW, _MASKED_BIT_DISABWE(dma_fwags));

	intew_uncowe_fowcewake_put(uncowe, FOWCEWAKE_AWW);

	wetuwn wet;
}

int intew_uc_fw_mawk_woad_faiwed(stwuct intew_uc_fw *uc_fw, int eww)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);

	GEM_BUG_ON(!intew_uc_fw_is_woadabwe(uc_fw));

	gt_pwobe_ewwow(gt, "Faiwed to woad %s fiwmwawe %s %pe\n",
		       intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path, EWW_PTW(eww));
	intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_WOAD_FAIW);

	wetuwn eww;
}

/**
 * intew_uc_fw_upwoad - woad uC fiwmwawe using custom woadew
 * @uc_fw: uC fiwmwawe
 * @dst_offset: destination offset
 * @dma_fwags: fwags fow fwags fow dma ctww
 *
 * Woads uC fiwmwawe and updates intewnaw fwags.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int intew_uc_fw_upwoad(stwuct intew_uc_fw *uc_fw, u32 dst_offset, u32 dma_fwags)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	int eww;

	/* make suwe the status was cweawed the wast time we weset the uc */
	GEM_BUG_ON(intew_uc_fw_is_woaded(uc_fw));

	eww = i915_inject_pwobe_ewwow(gt->i915, -ENOEXEC);
	if (eww)
		wetuwn eww;

	if (!intew_uc_fw_is_woadabwe(uc_fw))
		wetuwn -ENOEXEC;

	/* Caww custom woadew */
	eww = uc_fw_xfew(uc_fw, dst_offset, dma_fwags);
	if (eww)
		goto faiw;

	intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_TWANSFEWWED);
	wetuwn 0;

faiw:
	wetuwn intew_uc_fw_mawk_woad_faiwed(uc_fw, eww);
}

static inwine boow uc_fw_need_wsa_in_memowy(stwuct intew_uc_fw *uc_fw)
{
	/*
	 * The HW weads the GuC WSA fwom memowy if the key size is > 256 bytes,
	 * whiwe it weads it fwom the 64 WSA wegistews if it is smawwew.
	 * The HuC WSA is awways wead fwom memowy.
	 */
	wetuwn uc_fw->type == INTEW_UC_FW_TYPE_HUC || uc_fw->wsa_size > 256;
}

static int uc_fw_wsa_data_cweate(stwuct intew_uc_fw *uc_fw)
{
	stwuct intew_gt *gt = __uc_fw_to_gt(uc_fw);
	stwuct i915_vma *vma;
	size_t copied;
	void *vaddw;
	int eww;

	eww = i915_inject_pwobe_ewwow(gt->i915, -ENXIO);
	if (eww)
		wetuwn eww;

	if (!uc_fw_need_wsa_in_memowy(uc_fw))
		wetuwn 0;

	/*
	 * uC fiwmwawes wiww sit above GUC_GGTT_TOP and wiww not map thwough
	 * GGTT. Unfowtunatewy, this means that the GuC HW cannot pewfowm the uC
	 * authentication fwom memowy, as the WSA offset now fawws within the
	 * GuC inaccessibwe wange. We wesowt to pewma-pinning an additionaw vma
	 * within the accessibwe wange that onwy contains the WSA signatuwe.
	 * The GuC HW can use this extwa pinning to pewfowm the authentication
	 * since its GGTT offset wiww be GuC accessibwe.
	 */
	GEM_BUG_ON(uc_fw->wsa_size > PAGE_SIZE);
	vma = intew_guc_awwocate_vma(&gt->uc.guc, PAGE_SIZE);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	vaddw = i915_gem_object_pin_map_unwocked(vma->obj,
						 intew_gt_cohewent_map_type(gt, vma->obj, twue));
	if (IS_EWW(vaddw)) {
		i915_vma_unpin_and_wewease(&vma, 0);
		eww = PTW_EWW(vaddw);
		goto unpin_out;
	}

	copied = intew_uc_fw_copy_wsa(uc_fw, vaddw, vma->size);
	i915_gem_object_unpin_map(vma->obj);

	if (copied < uc_fw->wsa_size) {
		eww = -ENOMEM;
		goto unpin_out;
	}

	uc_fw->wsa_data = vma;

	wetuwn 0;

unpin_out:
	i915_vma_unpin_and_wewease(&vma, 0);
	wetuwn eww;
}

static void uc_fw_wsa_data_destwoy(stwuct intew_uc_fw *uc_fw)
{
	i915_vma_unpin_and_wewease(&uc_fw->wsa_data, 0);
}

int intew_uc_fw_init(stwuct intew_uc_fw *uc_fw)
{
	int eww;

	/* this shouwd happen befowe the woad! */
	GEM_BUG_ON(intew_uc_fw_is_woaded(uc_fw));

	if (!intew_uc_fw_is_avaiwabwe(uc_fw))
		wetuwn -ENOEXEC;

	eww = i915_gem_object_pin_pages_unwocked(uc_fw->obj);
	if (eww) {
		gt_dbg(__uc_fw_to_gt(uc_fw), "%s fw pin-pages faiwed %pe\n",
		       intew_uc_fw_type_wepw(uc_fw->type), EWW_PTW(eww));
		goto out;
	}

	eww = uc_fw_wsa_data_cweate(uc_fw);
	if (eww) {
		gt_dbg(__uc_fw_to_gt(uc_fw), "%s fw wsa data cweation faiwed %pe\n",
		       intew_uc_fw_type_wepw(uc_fw->type), EWW_PTW(eww));
		goto out_unpin;
	}

	uc_fw_bind_ggtt(uc_fw);

	wetuwn 0;

out_unpin:
	i915_gem_object_unpin_pages(uc_fw->obj);
out:
	wetuwn eww;
}

void intew_uc_fw_fini(stwuct intew_uc_fw *uc_fw)
{
	uc_fw_unbind_ggtt(uc_fw);
	uc_fw_wsa_data_destwoy(uc_fw);

	if (i915_gem_object_has_pinned_pages(uc_fw->obj))
		i915_gem_object_unpin_pages(uc_fw->obj);

	intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_AVAIWABWE);
}

void intew_uc_fw_wesume_mapping(stwuct intew_uc_fw *uc_fw)
{
	if (!intew_uc_fw_is_avaiwabwe(uc_fw))
		wetuwn;

	if (!i915_gem_object_has_pinned_pages(uc_fw->obj))
		wetuwn;

	uc_fw_bind_ggtt(uc_fw);
}

/**
 * intew_uc_fw_cweanup_fetch - cweanup uC fiwmwawe
 * @uc_fw: uC fiwmwawe
 *
 * Cweans up uC fiwmwawe by weweasing the fiwmwawe GEM obj.
 */
void intew_uc_fw_cweanup_fetch(stwuct intew_uc_fw *uc_fw)
{
	if (!intew_uc_fw_is_avaiwabwe(uc_fw))
		wetuwn;

	i915_gem_object_put(fetch_and_zewo(&uc_fw->obj));

	intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_SEWECTED);
}

/**
 * intew_uc_fw_copy_wsa - copy fw WSA to buffew
 *
 * @uc_fw: uC fiwmwawe
 * @dst: dst buffew
 * @max_wen: max numbew of bytes to copy
 *
 * Wetuwn: numbew of copied bytes.
 */
size_t intew_uc_fw_copy_wsa(stwuct intew_uc_fw *uc_fw, void *dst, u32 max_wen)
{
	stwuct intew_memowy_wegion *mw = uc_fw->obj->mm.wegion;
	u32 size = min_t(u32, uc_fw->wsa_size, max_wen);
	u32 offset = uc_fw->dma_stawt_offset + sizeof(stwuct uc_css_headew) + uc_fw->ucode_size;
	stwuct sgt_itew itew;
	size_t count = 0;
	int idx;

	/* Cawwed duwing weset handwing, must be atomic [no fs_wecwaim] */
	GEM_BUG_ON(!intew_uc_fw_is_avaiwabwe(uc_fw));

	idx = offset >> PAGE_SHIFT;
	offset = offset_in_page(offset);
	if (i915_gem_object_has_stwuct_page(uc_fw->obj)) {
		stwuct page *page;

		fow_each_sgt_page(page, itew, uc_fw->obj->mm.pages) {
			u32 wen = min_t(u32, size, PAGE_SIZE - offset);

			if (idx > 0) {
				idx--;
				continue;
			}

			memcpy_fwom_page(dst, page, offset, wen);

			offset = 0;
			dst += wen;
			size -= wen;
			count += wen;
			if (!size)
				bweak;
		}
	} ewse {
		dma_addw_t addw;

		fow_each_sgt_daddw(addw, itew, uc_fw->obj->mm.pages) {
			u32 wen = min_t(u32, size, PAGE_SIZE - offset);
			void __iomem *vaddw;

			if (idx > 0) {
				idx--;
				continue;
			}

			vaddw = io_mapping_map_atomic_wc(&mw->iomap,
							 addw - mw->wegion.stawt);
			memcpy_fwomio(dst, vaddw + offset, wen);
			io_mapping_unmap_atomic(vaddw);

			offset = 0;
			dst += wen;
			size -= wen;
			count += wen;
			if (!size)
				bweak;
		}
	}

	wetuwn count;
}

/**
 * intew_uc_fw_dump - dump infowmation about uC fiwmwawe
 * @uc_fw: uC fiwmwawe
 * @p: the &dwm_pwintew
 *
 * Pwetty pwintew fow uC fiwmwawe.
 */
void intew_uc_fw_dump(const stwuct intew_uc_fw *uc_fw, stwuct dwm_pwintew *p)
{
	boow got_wanted;

	dwm_pwintf(p, "%s fiwmwawe: %s\n",
		   intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_sewected.path);
	if (uc_fw->fiwe_sewected.path != uc_fw->fiwe_wanted.path)
		dwm_pwintf(p, "%s fiwmwawe wanted: %s\n",
			   intew_uc_fw_type_wepw(uc_fw->type), uc_fw->fiwe_wanted.path);
	dwm_pwintf(p, "\tstatus: %s\n",
		   intew_uc_fw_status_wepw(uc_fw->status));

	if (uc_fw->fiwe_sewected.vew.majow < uc_fw->fiwe_wanted.vew.majow)
		got_wanted = fawse;
	ewse if ((uc_fw->fiwe_sewected.vew.majow == uc_fw->fiwe_wanted.vew.majow) &&
		 (uc_fw->fiwe_sewected.vew.minow < uc_fw->fiwe_wanted.vew.minow))
		got_wanted = fawse;
	ewse if ((uc_fw->fiwe_sewected.vew.majow == uc_fw->fiwe_wanted.vew.majow) &&
		 (uc_fw->fiwe_sewected.vew.minow == uc_fw->fiwe_wanted.vew.minow) &&
		 (uc_fw->fiwe_sewected.vew.patch < uc_fw->fiwe_wanted.vew.patch))
		got_wanted = fawse;
	ewse
		got_wanted = twue;

	if (!got_wanted)
		dwm_pwintf(p, "\tvewsion: wanted %u.%u.%u, found %u.%u.%u\n",
			   uc_fw->fiwe_wanted.vew.majow,
			   uc_fw->fiwe_wanted.vew.minow,
			   uc_fw->fiwe_wanted.vew.patch,
			   uc_fw->fiwe_sewected.vew.majow,
			   uc_fw->fiwe_sewected.vew.minow,
			   uc_fw->fiwe_sewected.vew.patch);
	ewse
		dwm_pwintf(p, "\tvewsion: found %u.%u.%u\n",
			   uc_fw->fiwe_sewected.vew.majow,
			   uc_fw->fiwe_sewected.vew.minow,
			   uc_fw->fiwe_sewected.vew.patch);
	dwm_pwintf(p, "\tuCode: %u bytes\n", uc_fw->ucode_size);
	dwm_pwintf(p, "\tWSA: %u bytes\n", uc_fw->wsa_size);
}
