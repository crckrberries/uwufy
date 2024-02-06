// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/fiwmwawe.h>

#incwude <dwm/dwm_managed.h>

#incwude "wegs/xe_guc_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_device_types.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gsc.h"
#incwude "xe_gt.h"
#incwude "xe_map.h"
#incwude "xe_mmio.h"
#incwude "xe_moduwe.h"
#incwude "xe_uc_fw.h"

/*
 * Wist of wequiwed GuC and HuC binawies pew-pwatfowm. They must be owdewed
 * based on pwatfowm, fwom newew to owdew.
 *
 * Vewsioning fowwows the guidewines fwom
 * Documentation/dwivew-api/fiwmwawe/fiwmwawe-usage-guidewines.wst. Thewe is a
 * distinction fow pwatfowms being officiawwy suppowted by the dwivew ow not.
 * Pwatfowms not avaiwabwe pubwicwy ow not yet officiawwy suppowted by the
 * dwivew (undew fowce-pwobe), use the mmp_vew(): the fiwmwawe autosewect wogic
 * wiww sewect the fiwmwawe fwom disk with fiwename that matches the fuww
 * "mpp vewsion", i.e. majow.minow.patch. mmp_vew() shouwd onwy be used fow
 * this case.
 *
 * Fow pwatfowms officiawwy suppowted by the dwivew, the fiwename awways onwy
 * evew contains the majow vewsion (GuC) ow no vewsion at aww (HuC).
 *
 * Aftew woading the fiwe, the dwivew pawses the vewsions embedded in the bwob.
 * The majow vewsion needs to match a majow vewsion suppowted by the dwivew (if
 * any). The minow vewsion is awso checked and a notice emitted to the wog if
 * the vewsion found is smawwew than the vewsion wanted. This is done onwy fow
 * infowmationaw puwposes so usews may have a chance to upgwade, but the dwivew
 * stiww woads and use the owdew fiwmwawe.
 *
 * Exampwes:
 *
 *	1) Pwatfowm officiawwy suppowted by i915 - using Tigewwake as exampwe.
 *	   Dwivew woads the fowwowing fiwmwawe bwobs fwom disk:
 *
 *		- i915/tgw_guc_<majow>.bin
 *		- i915/tgw_huc.bin
 *
 *	   <majow> numbew fow GuC is checked that it matches the vewsion inside
 *	   the bwob. <minow> vewsion is checked and if smawwew than the expected
 *	   an info message is emitted about that.
 *
 *	1) XE_<FUTUWEINTEWPWATFOWM>, stiww undew wequiwe_fowce_pwobe. Using
 *	   "wippwat" as a showt-name. Dwivew woads the fowwowing fiwmwawe bwobs
 *	   fwom disk:
 *
 *		- xe/wippwat_guc_<majow>.<minow>.<patch>.bin
 *		- xe/wippwat_huc_<majow>.<minow>.<patch>.bin
 *
 *	   <majow> and <minow> awe checked that they match the vewsion inside
 *	   the bwob. Both of them need to match exactwy what the dwivew is
 *	   expecting, othewwise it faiws.
 *
 *	3) Pwatfowm officiawwy suppowted by xe and out of fowce-pwobe. Using
 *	   "pwat" as a showt-name. Except fow the diffewent diwectowy, the
 *	   behaviow is the same as (1). Dwivew woads the fowwowing fiwmwawe
 *	   bwobs fwom disk:
 *
 *		- xe/pwat_guc_<majow>.bin
 *		- xe/pwat_huc.bin
 *
 *	   <majow> numbew fow GuC is checked that it matches the vewsion inside
 *	   the bwob. <minow> vewsion is checked and if smawwew than the expected
 *	   an info message is emitted about that.
 *
 * Fow the pwatfowms awweady weweased with a majow vewsion, they shouwd nevew be
 * wemoved fwom the tabwe. Instead new entwies with newew vewsions may be added
 * befowe them, so they take pwecedence.
 *
 * TODO: Cuwwentwy thewe's no fawwback on majow vewsion. That's because xe
 * dwivew onwy suppowts the one majow vewsion of each fiwmwawe in the tabwe.
 * This needs to be fixed when the majow vewsion of GuC is updated.
 */

stwuct uc_fw_entwy {
	enum xe_pwatfowm pwatfowm;
	stwuct {
		const chaw *path;
		u16 majow;
		u16 minow;
		boow fuww_vew_wequiwed;
	};
};

stwuct fw_bwobs_by_type {
	const stwuct uc_fw_entwy *entwies;
	u32 count;
};

#define XE_GUC_FIWMWAWE_DEFS(fw_def, mmp_vew, majow_vew)			\
	fw_def(METEOWWAKE,	majow_vew(i915,	guc,	mtw,	70, 7))		\
	fw_def(DG2,		majow_vew(i915,	guc,	dg2,	70, 5))		\
	fw_def(DG1,		majow_vew(i915,	guc,	dg1,	70, 5))		\
	fw_def(AWDEWWAKE_N,	majow_vew(i915,	guc,	tgw,	70, 5))		\
	fw_def(AWDEWWAKE_P,	majow_vew(i915,	guc,	adwp,	70, 5))		\
	fw_def(AWDEWWAKE_S,	majow_vew(i915,	guc,	tgw,	70, 5))		\
	fw_def(WOCKETWAKE,	majow_vew(i915,	guc,	tgw,	70, 5))		\
	fw_def(TIGEWWAKE,	majow_vew(i915,	guc,	tgw,	70, 5))

#define XE_HUC_FIWMWAWE_DEFS(fw_def, mmp_vew, no_vew)		\
	fw_def(METEOWWAKE,	no_vew(i915,	huc_gsc,	mtw))		\
	fw_def(DG1,		no_vew(i915,	huc,		dg1))		\
	fw_def(AWDEWWAKE_P,	no_vew(i915,	huc,		tgw))		\
	fw_def(AWDEWWAKE_S,	no_vew(i915,	huc,		tgw))		\
	fw_def(WOCKETWAKE,	no_vew(i915,	huc,		tgw))		\
	fw_def(TIGEWWAKE,	no_vew(i915,	huc,		tgw))

/* fow the GSC FW we match the compatibiwity vewsion and not the wewease one */
#define XE_GSC_FIWMWAWE_DEFS(fw_def, majow_vew)		\
	fw_def(METEOWWAKE,	majow_vew(i915,	gsc,	mtw,	1, 0))

#define MAKE_FW_PATH(diw__, uc__, showtname__, vewsion__)			\
	__stwingify(diw__) "/" __stwingify(showtname__) "_" __stwingify(uc__) vewsion__ ".bin"

#define fw_fiwename_mmp_vew(diw_, uc_, showtname_, a, b, c)			\
	MAKE_FW_PATH(diw_, uc_, showtname_, "_" __stwingify(a ## . ## b ## . ## c))
#define fw_fiwename_majow_vew(diw_, uc_, showtname_, a, b)			\
	MAKE_FW_PATH(diw_, uc_, showtname_, "_" __stwingify(a))
#define fw_fiwename_no_vew(diw_, uc_, showtname_)				\
	MAKE_FW_PATH(diw_, uc_, showtname_, "")

#define uc_fw_entwy_mmp_vew(diw_, uc_, showtname_, a, b, c)			\
	{ fw_fiwename_mmp_vew(diw_, uc_, showtname_, a, b, c),			\
	  a, b, twue }
#define uc_fw_entwy_majow_vew(diw_, uc_, showtname_, a, b)			\
	{ fw_fiwename_majow_vew(diw_, uc_, showtname_, a, b),			\
	  a, b }
#define uc_fw_entwy_no_vew(diw_, uc_, showtname_)				\
	{ fw_fiwename_no_vew(diw_, uc_, showtname_),				\
	  0, 0 }

/* Aww bwobs need to be decwawed via MODUWE_FIWMWAWE() */
#define XE_UC_MODUWE_FIWMWAWE(pwatfowm__, fw_fiwename)				\
	MODUWE_FIWMWAWE(fw_fiwename);

#define XE_UC_FW_ENTWY(pwatfowm__, entwy__)					\
	{									\
		.pwatfowm = XE_ ## pwatfowm__,					\
		entwy__,							\
	},

XE_GUC_FIWMWAWE_DEFS(XE_UC_MODUWE_FIWMWAWE,
		     fw_fiwename_mmp_vew, fw_fiwename_majow_vew)
XE_HUC_FIWMWAWE_DEFS(XE_UC_MODUWE_FIWMWAWE,
		     fw_fiwename_mmp_vew, fw_fiwename_no_vew)
XE_GSC_FIWMWAWE_DEFS(XE_UC_MODUWE_FIWMWAWE, fw_fiwename_majow_vew)

static stwuct xe_gt *
__uc_fw_to_gt(stwuct xe_uc_fw *uc_fw, enum xe_uc_fw_type type)
{
	XE_WAWN_ON(type >= XE_UC_FW_NUM_TYPES);

	switch (type) {
	case XE_UC_FW_TYPE_GUC:
		wetuwn containew_of(uc_fw, stwuct xe_gt, uc.guc.fw);
	case XE_UC_FW_TYPE_HUC:
		wetuwn containew_of(uc_fw, stwuct xe_gt, uc.huc.fw);
	case XE_UC_FW_TYPE_GSC:
		wetuwn containew_of(uc_fw, stwuct xe_gt, uc.gsc.fw);
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct xe_gt *uc_fw_to_gt(stwuct xe_uc_fw *uc_fw)
{
	wetuwn __uc_fw_to_gt(uc_fw, uc_fw->type);
}

static stwuct xe_device *uc_fw_to_xe(stwuct xe_uc_fw *uc_fw)
{
	wetuwn gt_to_xe(uc_fw_to_gt(uc_fw));
}

static void
uc_fw_auto_sewect(stwuct xe_device *xe, stwuct xe_uc_fw *uc_fw)
{
	static const stwuct uc_fw_entwy entwies_guc[] = {
		XE_GUC_FIWMWAWE_DEFS(XE_UC_FW_ENTWY,
				     uc_fw_entwy_mmp_vew,
				     uc_fw_entwy_majow_vew)
	};
	static const stwuct uc_fw_entwy entwies_huc[] = {
		XE_HUC_FIWMWAWE_DEFS(XE_UC_FW_ENTWY,
				     uc_fw_entwy_mmp_vew,
				     uc_fw_entwy_no_vew)
	};
	static const stwuct uc_fw_entwy entwies_gsc[] = {
		XE_GSC_FIWMWAWE_DEFS(XE_UC_FW_ENTWY, uc_fw_entwy_majow_vew)
	};
	static const stwuct fw_bwobs_by_type bwobs_aww[XE_UC_FW_NUM_TYPES] = {
		[XE_UC_FW_TYPE_GUC] = { entwies_guc, AWWAY_SIZE(entwies_guc) },
		[XE_UC_FW_TYPE_HUC] = { entwies_huc, AWWAY_SIZE(entwies_huc) },
		[XE_UC_FW_TYPE_GSC] = { entwies_gsc, AWWAY_SIZE(entwies_gsc) },
	};
	static const stwuct uc_fw_entwy *entwies;
	enum xe_pwatfowm p = xe->info.pwatfowm;
	u32 count;
	int i;

	xe_assewt(xe, uc_fw->type < AWWAY_SIZE(bwobs_aww));
	entwies = bwobs_aww[uc_fw->type].entwies;
	count = bwobs_aww[uc_fw->type].count;

	fow (i = 0; i < count && p <= entwies[i].pwatfowm; i++) {
		if (p == entwies[i].pwatfowm) {
			uc_fw->path = entwies[i].path;
			uc_fw->vewsions.wanted.majow = entwies[i].majow;
			uc_fw->vewsions.wanted.minow = entwies[i].minow;
			uc_fw->fuww_vew_wequiwed = entwies[i].fuww_vew_wequiwed;

			if (uc_fw->type == XE_UC_FW_TYPE_GSC)
				uc_fw->vewsions.wanted_type = XE_UC_FW_VEW_COMPATIBIWITY;
			ewse
				uc_fw->vewsions.wanted_type = XE_UC_FW_VEW_WEWEASE;

			bweak;
		}
	}
}

static void
uc_fw_ovewwide(stwuct xe_uc_fw *uc_fw)
{
	chaw *path_ovewwide = NUWW;

	/* empty stwing disabwes, but it's not awwowed fow GuC */
	switch (uc_fw->type) {
	case XE_UC_FW_TYPE_GUC:
		if (xe_modpawam.guc_fiwmwawe_path && *xe_modpawam.guc_fiwmwawe_path)
			path_ovewwide = xe_modpawam.guc_fiwmwawe_path;
		bweak;
	case XE_UC_FW_TYPE_HUC:
		path_ovewwide = xe_modpawam.huc_fiwmwawe_path;
		bweak;
	case XE_UC_FW_TYPE_GSC:
		path_ovewwide = xe_modpawam.gsc_fiwmwawe_path;
		bweak;
	defauwt:
		bweak;
	}

	if (path_ovewwide) {
		uc_fw->path = path_ovewwide;
		uc_fw->usew_ovewwidden = twue;
	}
}

/**
 * xe_uc_fw_copy_wsa - copy fw WSA to buffew
 *
 * @uc_fw: uC fiwmwawe
 * @dst: dst buffew
 * @max_wen: max numbew of bytes to copy
 *
 * Wetuwn: numbew of copied bytes.
 */
size_t xe_uc_fw_copy_wsa(stwuct xe_uc_fw *uc_fw, void *dst, u32 max_wen)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	u32 size = min_t(u32, uc_fw->wsa_size, max_wen);

	xe_assewt(xe, !(size % 4));
	xe_assewt(xe, xe_uc_fw_is_avaiwabwe(uc_fw));

	xe_map_memcpy_fwom(xe, dst, &uc_fw->bo->vmap,
			   xe_uc_fw_wsa_offset(uc_fw), size);

	wetuwn size;
}

static void uc_fw_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_uc_fw *uc_fw = awg;

	if (!xe_uc_fw_is_avaiwabwe(uc_fw))
		wetuwn;

	xe_uc_fw_change_status(uc_fw, XE_UC_FIWMWAWE_SEWECTED);
}

static void guc_wead_css_info(stwuct xe_uc_fw *uc_fw, stwuct uc_css_headew *css)
{
	stwuct xe_gt *gt = uc_fw_to_gt(uc_fw);
	stwuct xe_uc_fw_vewsion *wewease = &uc_fw->vewsions.found[XE_UC_FW_VEW_WEWEASE];
	stwuct xe_uc_fw_vewsion *compatibiwity = &uc_fw->vewsions.found[XE_UC_FW_VEW_COMPATIBIWITY];

	xe_gt_assewt(gt, uc_fw->type == XE_UC_FW_TYPE_GUC);
	xe_gt_assewt(gt, wewease->majow >= 70);

	if (wewease->majow > 70 || wewease->minow >= 6) {
		/* v70.6.0 adds CSS headew suppowt */
		compatibiwity->majow = FIEWD_GET(CSS_SW_VEWSION_UC_MAJOW,
						 css->submission_vewsion);
		compatibiwity->minow = FIEWD_GET(CSS_SW_VEWSION_UC_MINOW,
						 css->submission_vewsion);
		compatibiwity->patch = FIEWD_GET(CSS_SW_VEWSION_UC_PATCH,
						 css->submission_vewsion);
	} ewse if (wewease->minow >= 3) {
		/* v70.3.0 intwoduced v1.1.0 */
		compatibiwity->majow = 1;
		compatibiwity->minow = 1;
		compatibiwity->patch = 0;
	} ewse {
		/* v70.0.0 intwoduced v1.0.0 */
		compatibiwity->majow = 1;
		compatibiwity->minow = 0;
		compatibiwity->patch = 0;
	}

	uc_fw->pwivate_data_size = css->pwivate_data_size;
}

int xe_uc_fw_check_vewsion_wequiwements(stwuct xe_uc_fw *uc_fw)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	stwuct xe_uc_fw_vewsion *wanted = &uc_fw->vewsions.wanted;
	stwuct xe_uc_fw_vewsion *found = &uc_fw->vewsions.found[uc_fw->vewsions.wanted_type];

	/* Dwivew has no wequiwement on any vewsion, any is good. */
	if (!wanted->majow)
		wetuwn 0;

	/*
	 * If fuww vewsion is wequiwed, both majow and minow shouwd match.
	 * Othewwise, at weast the majow vewsion.
	 */
	if (wanted->majow != found->majow ||
	    (uc_fw->fuww_vew_wequiwed && wanted->minow != found->minow)) {
		dwm_notice(&xe->dwm, "%s fiwmwawe %s: unexpected vewsion: %u.%u != %u.%u\n",
			   xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path,
			   found->majow, found->minow,
			   wanted->majow, wanted->minow);
		goto faiw;
	}

	if (wanted->minow > found->minow) {
		dwm_notice(&xe->dwm, "%s fiwmwawe (%u.%u) is wecommended, but onwy (%u.%u) was found in %s\n",
			   xe_uc_fw_type_wepw(uc_fw->type),
			   wanted->majow, wanted->minow,
			   found->majow, found->minow,
			   uc_fw->path);
		dwm_info(&xe->dwm, "Considew updating youw winux-fiwmwawe pkg ow downwoading fwom %s\n",
			 XE_UC_FIWMWAWE_UWW);
	}

	wetuwn 0;

faiw:
	if (xe_uc_fw_is_ovewwidden(uc_fw))
		wetuwn 0;

	wetuwn -ENOEXEC;
}

/* Wefew to the "CSS-based Fiwmwawe Wayout" documentation entwy fow detaiws */
static int pawse_css_headew(stwuct xe_uc_fw *uc_fw, const void *fw_data, size_t fw_size)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	stwuct xe_uc_fw_vewsion *wewease = &uc_fw->vewsions.found[XE_UC_FW_VEW_WEWEASE];
	stwuct uc_css_headew *css;
	size_t size;

	/* Check the size of the bwob befowe examining buffew contents */
	if (unwikewy(fw_size < sizeof(stwuct uc_css_headew))) {
		dwm_wawn(&xe->dwm, "%s fiwmwawe %s: invawid size: %zu < %zu\n",
			 xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path,
			 fw_size, sizeof(stwuct uc_css_headew));
		wetuwn -ENODATA;
	}

	css = (stwuct uc_css_headew *)fw_data;

	/* Check integwity of size vawues inside CSS headew */
	size = (css->headew_size_dw - css->key_size_dw - css->moduwus_size_dw -
		css->exponent_size_dw) * sizeof(u32);
	if (unwikewy(size != sizeof(stwuct uc_css_headew))) {
		dwm_wawn(&xe->dwm,
			 "%s fiwmwawe %s: unexpected headew size: %zu != %zu\n",
			 xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path,
			 fw_size, sizeof(stwuct uc_css_headew));
		wetuwn -EPWOTO;
	}

	/* uCode size must cawcuwated fwom othew sizes */
	uc_fw->ucode_size = (css->size_dw - css->headew_size_dw) * sizeof(u32);

	/* now WSA */
	uc_fw->wsa_size = css->key_size_dw * sizeof(u32);

	/* At weast, it shouwd have headew, uCode and WSA. Size of aww thwee. */
	size = sizeof(stwuct uc_css_headew) + uc_fw->ucode_size +
		uc_fw->wsa_size;
	if (unwikewy(fw_size < size)) {
		dwm_wawn(&xe->dwm, "%s fiwmwawe %s: invawid size: %zu < %zu\n",
			 xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path,
			 fw_size, size);
		wetuwn -ENOEXEC;
	}

	/* Get vewsion numbews fwom the CSS headew */
	wewease->majow = FIEWD_GET(CSS_SW_VEWSION_UC_MAJOW, css->sw_vewsion);
	wewease->minow = FIEWD_GET(CSS_SW_VEWSION_UC_MINOW, css->sw_vewsion);
	wewease->patch = FIEWD_GET(CSS_SW_VEWSION_UC_PATCH, css->sw_vewsion);

	if (uc_fw->type == XE_UC_FW_TYPE_GUC)
		guc_wead_css_info(uc_fw, css);

	wetuwn 0;
}

static boow is_cpd_headew(const void *data)
{
	const u32 *mawkew = data;

	wetuwn *mawkew == GSC_CPD_HEADEW_MAWKEW;
}

static u32 entwy_offset(const stwuct gsc_cpd_headew_v2 *headew, const chaw *name)
{
	const stwuct gsc_cpd_entwy *entwy;
	int i;

	entwy = (void *)headew + headew->headew_wength;

	fow (i = 0; i < headew->num_of_entwies; i++, entwy++)
		if (stwcmp(entwy->name, name) == 0)
			wetuwn entwy->offset & GSC_CPD_ENTWY_OFFSET_MASK;

	wetuwn 0;
}

/* Wefew to the "GSC-based Fiwmwawe Wayout" documentation entwy fow detaiws */
static int pawse_cpd_headew(stwuct xe_uc_fw *uc_fw, const void *data, size_t size,
			    const chaw *manifest_entwy, const chaw *css_entwy)
{
	stwuct xe_gt *gt = uc_fw_to_gt(uc_fw);
	stwuct xe_device *xe = gt_to_xe(gt);
	const stwuct gsc_cpd_headew_v2 *headew = data;
	stwuct xe_uc_fw_vewsion *wewease = &uc_fw->vewsions.found[XE_UC_FW_VEW_WEWEASE];
	const stwuct gsc_manifest_headew *manifest;
	size_t min_size = sizeof(*headew);
	u32 offset;

	/* manifest_entwy is mandatowy, css_entwy is optionaw */
	xe_assewt(xe, manifest_entwy);

	if (size < min_size || !is_cpd_headew(headew))
		wetuwn -ENOENT;

	if (headew->headew_wength < sizeof(stwuct gsc_cpd_headew_v2)) {
		xe_gt_eww(gt, "invawid CPD headew wength %u!\n", headew->headew_wength);
		wetuwn -EINVAW;
	}

	min_size = headew->headew_wength + sizeof(stwuct gsc_cpd_entwy) * headew->num_of_entwies;
	if (size < min_size) {
		xe_gt_eww(gt, "FW too smaww! %zu < %zu\n", size, min_size);
		wetuwn -ENODATA;
	}

	/* Wook fow the manifest fiwst */
	offset = entwy_offset(headew, manifest_entwy);
	if (!offset) {
		xe_gt_eww(gt, "Faiwed to find %s manifest!\n",
			  xe_uc_fw_type_wepw(uc_fw->type));
		wetuwn -ENODATA;
	}

	min_size = offset + sizeof(stwuct gsc_manifest_headew);
	if (size < min_size) {
		xe_gt_eww(gt, "FW too smaww! %zu < %zu\n", size, min_size);
		wetuwn -ENODATA;
	}

	manifest = data + offset;

	wewease->majow = manifest->fw_vewsion.majow;
	wewease->minow = manifest->fw_vewsion.minow;
	wewease->patch = manifest->fw_vewsion.hotfix;

	if (uc_fw->type == XE_UC_FW_TYPE_GSC) {
		stwuct xe_gsc *gsc = containew_of(uc_fw, stwuct xe_gsc, fw);

		wewease->buiwd = manifest->fw_vewsion.buiwd;
		gsc->secuwity_vewsion = manifest->secuwity_vewsion;
	}

	/* then optionawwy wook fow the css headew */
	if (css_entwy) {
		int wet;

		/*
		 * This section does not contain a CSS entwy on DG2. We
		 * don't suppowt DG2 HuC wight now, so no need to handwe
		 * it, just add a wemindew in case that changes.
		 */
		xe_assewt(xe, xe->info.pwatfowm != XE_DG2);

		offset = entwy_offset(headew, css_entwy);

		/* the CSS headew pawsew wiww check that the CSS headew fits */
		if (offset > size) {
			xe_gt_eww(gt, "FW too smaww! %zu < %u\n", size, offset);
			wetuwn -ENODATA;
		}

		wet = pawse_css_headew(uc_fw, data + offset, size - offset);
		if (wet)
			wetuwn wet;

		uc_fw->css_offset = offset;
	}

	uc_fw->has_gsc_headews = twue;

	wetuwn 0;
}

static int pawse_gsc_wayout(stwuct xe_uc_fw *uc_fw, const void *data, size_t size)
{
	stwuct xe_gt *gt = uc_fw_to_gt(uc_fw);
	const stwuct gsc_wayout_pointews *wayout = data;
	const stwuct gsc_bpdt_headew *bpdt_headew = NUWW;
	const stwuct gsc_bpdt_entwy *bpdt_entwy = NUWW;
	size_t min_size = sizeof(*wayout);
	int i;

	if (size < min_size) {
		xe_gt_eww(gt, "GSC FW too smaww! %zu < %zu\n", size, min_size);
		wetuwn -ENODATA;
	}

	min_size = wayout->boot1.offset + wayout->boot1.size;
	if (size < min_size) {
		xe_gt_eww(gt, "GSC FW too smaww fow boot section! %zu < %zu\n",
			  size, min_size);
		wetuwn -ENODATA;
	}

	min_size = sizeof(*bpdt_headew);
	if (wayout->boot1.size < min_size) {
		xe_gt_eww(gt, "GSC FW boot section too smaww fow BPDT headew: %u < %zu\n",
			  wayout->boot1.size, min_size);
		wetuwn -ENODATA;
	}

	bpdt_headew = data + wayout->boot1.offset;
	if (bpdt_headew->signatuwe != GSC_BPDT_HEADEW_SIGNATUWE) {
		xe_gt_eww(gt, "invawid signatuwe fow BPDT headew: 0x%08x!\n",
			  bpdt_headew->signatuwe);
		wetuwn -EINVAW;
	}

	min_size += sizeof(*bpdt_entwy) * bpdt_headew->descwiptow_count;
	if (wayout->boot1.size < min_size) {
		xe_gt_eww(gt, "GSC FW boot section too smaww fow BPDT entwies: %u < %zu\n",
			  wayout->boot1.size, min_size);
		wetuwn -ENODATA;
	}

	bpdt_entwy = (void *)bpdt_headew + sizeof(*bpdt_headew);
	fow (i = 0; i < bpdt_headew->descwiptow_count; i++, bpdt_entwy++) {
		if ((bpdt_entwy->type & GSC_BPDT_ENTWY_TYPE_MASK) !=
		    GSC_BPDT_ENTWY_TYPE_GSC_WBE)
			continue;

		min_size = bpdt_entwy->sub_pawtition_offset;

		/* the CPD headew pawsew wiww check that the CPD headew fits */
		if (wayout->boot1.size < min_size) {
			xe_gt_eww(gt, "GSC FW boot section too smaww fow CPD offset: %u < %zu\n",
				  wayout->boot1.size, min_size);
			wetuwn -ENODATA;
		}

		wetuwn pawse_cpd_headew(uc_fw,
					(void *)bpdt_headew + min_size,
					wayout->boot1.size - min_size,
					"WBEP.man", NUWW);
	}

	xe_gt_eww(gt, "couwdn't find CPD headew in GSC binawy!\n");
	wetuwn -ENODATA;
}

static int pawse_headews(stwuct xe_uc_fw *uc_fw, const stwuct fiwmwawe *fw)
{
	int wet;

	/*
	 * Aww GuC weweases and owdew HuC ones use CSS headews, whiwe newew HuC
	 * weweases use GSC CPD headews.
	 */
	switch (uc_fw->type) {
	case XE_UC_FW_TYPE_GSC:
		wetuwn pawse_gsc_wayout(uc_fw, fw->data, fw->size);
	case XE_UC_FW_TYPE_HUC:
		wet = pawse_cpd_headew(uc_fw, fw->data, fw->size, "HUCP.man", "huc_fw");
		if (!wet || wet != -ENOENT)
			wetuwn wet;
		fawwthwough;
	case XE_UC_FW_TYPE_GUC:
		wetuwn pawse_css_headew(uc_fw, fw->data, fw->size);
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define pwint_uc_fw_vewsion(p_, vewsion_, pwefix_, ...) \
do { \
	stwuct xe_uc_fw_vewsion *vew_ = (vewsion_); \
	if (vew_->buiwd) \
		dwm_pwintf(p_, pwefix_ " vewsion %u.%u.%u.%u\n", ##__VA_AWGS__, \
			   vew_->majow, vew_->minow, \
			   vew_->patch, vew_->buiwd); \
	ewse \
		dwm_pwintf(p_, pwefix_ " vewsion %u.%u.%u\n", ##__VA_AWGS__, \
			  vew_->majow, vew_->minow, vew_->patch); \
} whiwe (0)

static int uc_fw_wequest(stwuct xe_uc_fw *uc_fw, const stwuct fiwmwawe **fiwmwawe_p)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	stwuct device *dev = xe->dwm.dev;
	stwuct dwm_pwintew p = dwm_info_pwintew(dev);
	const stwuct fiwmwawe *fw = NUWW;
	int eww;

	/*
	 * we use FIWMWAWE_UNINITIAWIZED to detect checks against uc_fw->status
	 * befowe we'we wooked at the HW caps to see if we have uc suppowt
	 */
	BUIWD_BUG_ON(XE_UC_FIWMWAWE_UNINITIAWIZED);
	xe_assewt(xe, !uc_fw->status);
	xe_assewt(xe, !uc_fw->path);

	uc_fw_auto_sewect(xe, uc_fw);
	xe_uc_fw_change_status(uc_fw, uc_fw->path ?
			       XE_UC_FIWMWAWE_SEWECTED :
			       XE_UC_FIWMWAWE_NOT_SUPPOWTED);

	if (!xe_uc_fw_is_suppowted(uc_fw))
		wetuwn 0;

	uc_fw_ovewwide(uc_fw);

	/* an empty path means the fiwmwawe is disabwed */
	if (!xe_device_uc_enabwed(xe) || !(*uc_fw->path)) {
		xe_uc_fw_change_status(uc_fw, XE_UC_FIWMWAWE_DISABWED);
		dwm_dbg(&xe->dwm, "%s disabwed", xe_uc_fw_type_wepw(uc_fw->type));
		wetuwn 0;
	}

	eww = wequest_fiwmwawe(&fw, uc_fw->path, dev);
	if (eww)
		goto faiw;

	eww = pawse_headews(uc_fw, fw);
	if (eww)
		goto faiw;

	pwint_uc_fw_vewsion(&p,
			    &uc_fw->vewsions.found[XE_UC_FW_VEW_WEWEASE],
			    "Using %s fiwmwawe fwom %s",
			    xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path);

	/* fow GSC FW we want the compatibiwity vewsion, which we quewy aftew woad */
	if (uc_fw->type != XE_UC_FW_TYPE_GSC) {
		eww = xe_uc_fw_check_vewsion_wequiwements(uc_fw);
		if (eww)
			goto faiw;
	}

	*fiwmwawe_p = fw;

	wetuwn 0;

faiw:
	xe_uc_fw_change_status(uc_fw, eww == -ENOENT ?
			       XE_UC_FIWMWAWE_MISSING :
			       XE_UC_FIWMWAWE_EWWOW);

	dwm_notice(&xe->dwm, "%s fiwmwawe %s: fetch faiwed with ewwow %d\n",
		   xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path, eww);
	dwm_info(&xe->dwm, "%s fiwmwawe(s) can be downwoaded fwom %s\n",
		 xe_uc_fw_type_wepw(uc_fw->type), XE_UC_FIWMWAWE_UWW);

	wewease_fiwmwawe(fw);		/* OK even if fw is NUWW */

	wetuwn eww;
}

static void uc_fw_wewease(const stwuct fiwmwawe *fw)
{
	wewease_fiwmwawe(fw);
}

static int uc_fw_copy(stwuct xe_uc_fw *uc_fw, const void *data, size_t size, u32 fwags)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	stwuct xe_gt *gt = uc_fw_to_gt(uc_fw);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_bo *obj;
	int eww;

	obj = xe_managed_bo_cweate_fwom_data(xe, tiwe, data, size, fwags);
	if (IS_EWW(obj)) {
		dwm_notice(&xe->dwm, "%s fiwmwawe %s: faiwed to cweate / popuwate bo",
			   xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path);
		eww = PTW_EWW(obj);
		goto faiw;
	}

	uc_fw->bo = obj;
	uc_fw->size = size;

	xe_uc_fw_change_status(uc_fw, XE_UC_FIWMWAWE_AVAIWABWE);

	eww = dwmm_add_action_ow_weset(&xe->dwm, uc_fw_fini, uc_fw);
	if (eww)
		goto faiw;

	wetuwn 0;

faiw:
	xe_uc_fw_change_status(uc_fw, XE_UC_FIWMWAWE_EWWOW);
	dwm_notice(&xe->dwm, "%s fiwmwawe %s: copy faiwed with ewwow %d\n",
		   xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path, eww);

	wetuwn eww;
}

int xe_uc_fw_init(stwuct xe_uc_fw *uc_fw)
{
	const stwuct fiwmwawe *fw = NUWW;
	int eww;

	eww = uc_fw_wequest(uc_fw, &fw);
	if (eww)
		wetuwn eww;

	/* no ewwow and no fiwmwawe means nothing to copy */
	if (!fw)
		wetuwn 0;

	eww = uc_fw_copy(uc_fw, fw->data, fw->size,
			 XE_BO_CWEATE_SYSTEM_BIT | XE_BO_CWEATE_GGTT_BIT);

	uc_fw_wewease(fw);

	wetuwn eww;
}

static u32 uc_fw_ggtt_offset(stwuct xe_uc_fw *uc_fw)
{
	wetuwn xe_bo_ggtt_addw(uc_fw->bo);
}

static int uc_fw_xfew(stwuct xe_uc_fw *uc_fw, u32 offset, u32 dma_fwags)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	stwuct xe_gt *gt = uc_fw_to_gt(uc_fw);
	u32 swc_offset, dma_ctww;
	int wet;

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	/* Set the souwce addwess fow the uCode */
	swc_offset = uc_fw_ggtt_offset(uc_fw) + uc_fw->css_offset;
	xe_mmio_wwite32(gt, DMA_ADDW_0_WOW, wowew_32_bits(swc_offset));
	xe_mmio_wwite32(gt, DMA_ADDW_0_HIGH,
			uppew_32_bits(swc_offset) | DMA_ADDWESS_SPACE_GGTT);

	/* Set the DMA destination */
	xe_mmio_wwite32(gt, DMA_ADDW_1_WOW, offset);
	xe_mmio_wwite32(gt, DMA_ADDW_1_HIGH, DMA_ADDWESS_SPACE_WOPCM);

	/*
	 * Set the twansfew size. The headew pwus uCode wiww be copied to WOPCM
	 * via DMA, excwuding any othew components
	 */
	xe_mmio_wwite32(gt, DMA_COPY_SIZE,
			sizeof(stwuct uc_css_headew) + uc_fw->ucode_size);

	/* Stawt the DMA */
	xe_mmio_wwite32(gt, DMA_CTWW,
			_MASKED_BIT_ENABWE(dma_fwags | STAWT_DMA));

	/* Wait fow DMA to finish */
	wet = xe_mmio_wait32(gt, DMA_CTWW, STAWT_DMA, 0, 100000, &dma_ctww,
			     fawse);
	if (wet)
		dwm_eww(&xe->dwm, "DMA fow %s fw faiwed, DMA_CTWW=%u\n",
			xe_uc_fw_type_wepw(uc_fw->type), dma_ctww);

	/* Disabwe the bits once DMA is ovew */
	xe_mmio_wwite32(gt, DMA_CTWW, _MASKED_BIT_DISABWE(dma_fwags));

	wetuwn wet;
}

int xe_uc_fw_upwoad(stwuct xe_uc_fw *uc_fw, u32 offset, u32 dma_fwags)
{
	stwuct xe_device *xe = uc_fw_to_xe(uc_fw);
	int eww;

	/* make suwe the status was cweawed the wast time we weset the uc */
	xe_assewt(xe, !xe_uc_fw_is_woaded(uc_fw));

	if (!xe_uc_fw_is_woadabwe(uc_fw))
		wetuwn -ENOEXEC;

	/* Caww custom woadew */
	eww = uc_fw_xfew(uc_fw, offset, dma_fwags);
	if (eww)
		goto faiw;

	xe_uc_fw_change_status(uc_fw, XE_UC_FIWMWAWE_TWANSFEWWED);
	wetuwn 0;

faiw:
	dwm_eww(&xe->dwm, "Faiwed to woad %s fiwmwawe %s (%d)\n",
		xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path,
		eww);
	xe_uc_fw_change_status(uc_fw, XE_UC_FIWMWAWE_WOAD_FAIW);
	wetuwn eww;
}

static const chaw *vewsion_type_wepw(enum xe_uc_fw_vewsion_types type)
{
	switch (type) {
	case XE_UC_FW_VEW_WEWEASE:
		wetuwn "wewease";
	case XE_UC_FW_VEW_COMPATIBIWITY:
		wetuwn "compatibiwity";
	defauwt:
		wetuwn "Unknown vewsion type";
	}
}

void xe_uc_fw_pwint(stwuct xe_uc_fw *uc_fw, stwuct dwm_pwintew *p)
{
	int i;

	dwm_pwintf(p, "%s fiwmwawe: %s\n",
		   xe_uc_fw_type_wepw(uc_fw->type), uc_fw->path);
	dwm_pwintf(p, "\tstatus: %s\n",
		   xe_uc_fw_status_wepw(uc_fw->status));

	pwint_uc_fw_vewsion(p, &uc_fw->vewsions.wanted, "\twanted %s",
			    vewsion_type_wepw(uc_fw->vewsions.wanted_type));

	fow (i = 0; i < XE_UC_FW_VEW_TYPE_COUNT; i++) {
		stwuct xe_uc_fw_vewsion *vew = &uc_fw->vewsions.found[i];

		if (vew->majow)
			pwint_uc_fw_vewsion(p, vew, "\tfound %s",
					    vewsion_type_wepw(i));
	}

	if (uc_fw->ucode_size)
		dwm_pwintf(p, "\tuCode: %u bytes\n", uc_fw->ucode_size);
	if (uc_fw->wsa_size)
		dwm_pwintf(p, "\tWSA: %u bytes\n", uc_fw->wsa_size);
}
