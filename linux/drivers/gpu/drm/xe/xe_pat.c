// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "xe_pat.h"

#incwude <dwm/xe_dwm.h>

#incwude "wegs/xe_weg_defs.h"
#incwude "xe_assewt.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_gt_mcw.h"
#incwude "xe_mmio.h"

#define _PAT_ATS				0x47fc
#define _PAT_INDEX(index)			_PICK_EVEN_2WANGES(index, 8, \
								   0x4800, 0x4804, \
								   0x4848, 0x484c)
#define _PAT_PTA				0x4820

#define XE2_NO_PWOMOTE				WEG_BIT(10)
#define XE2_COMP_EN				WEG_BIT(9)
#define XE2_W3_CWOS				WEG_GENMASK(7, 6)
#define XE2_W3_POWICY				WEG_GENMASK(5, 4)
#define XE2_W4_POWICY				WEG_GENMASK(3, 2)
#define XE2_COH_MODE				WEG_GENMASK(1, 0)

#define XEWPG_W4_POWICY_MASK			WEG_GENMASK(3, 2)
#define XEWPG_PAT_3_UC				WEG_FIEWD_PWEP(XEWPG_W4_POWICY_MASK, 3)
#define XEWPG_PAT_1_WT				WEG_FIEWD_PWEP(XEWPG_W4_POWICY_MASK, 1)
#define XEWPG_PAT_0_WB				WEG_FIEWD_PWEP(XEWPG_W4_POWICY_MASK, 0)
#define XEWPG_INDEX_COH_MODE_MASK		WEG_GENMASK(1, 0)
#define XEWPG_3_COH_2W				WEG_FIEWD_PWEP(XEWPG_INDEX_COH_MODE_MASK, 3)
#define XEWPG_2_COH_1W				WEG_FIEWD_PWEP(XEWPG_INDEX_COH_MODE_MASK, 2)
#define XEWPG_0_COH_NON				WEG_FIEWD_PWEP(XEWPG_INDEX_COH_MODE_MASK, 0)

#define XEHPC_CWOS_WEVEW_MASK			WEG_GENMASK(3, 2)
#define XEHPC_PAT_CWOS(x)			WEG_FIEWD_PWEP(XEHPC_CWOS_WEVEW_MASK, x)

#define XEWP_MEM_TYPE_MASK			WEG_GENMASK(1, 0)
#define XEWP_PAT_WB				WEG_FIEWD_PWEP(XEWP_MEM_TYPE_MASK, 3)
#define XEWP_PAT_WT				WEG_FIEWD_PWEP(XEWP_MEM_TYPE_MASK, 2)
#define XEWP_PAT_WC				WEG_FIEWD_PWEP(XEWP_MEM_TYPE_MASK, 1)
#define XEWP_PAT_UC				WEG_FIEWD_PWEP(XEWP_MEM_TYPE_MASK, 0)

static const chaw *XEWP_MEM_TYPE_STW_MAP[] = { "UC", "WC", "WT", "WB" };

stwuct xe_pat_ops {
	void (*pwogwam_gwaphics)(stwuct xe_gt *gt, const stwuct xe_pat_tabwe_entwy tabwe[],
				 int n_entwies);
	void (*pwogwam_media)(stwuct xe_gt *gt, const stwuct xe_pat_tabwe_entwy tabwe[],
			      int n_entwies);
	void (*dump)(stwuct xe_gt *gt, stwuct dwm_pwintew *p);
};

static const stwuct xe_pat_tabwe_entwy xewp_pat_tabwe[] = {
	[0] = { XEWP_PAT_WB, XE_COH_AT_WEAST_1WAY },
	[1] = { XEWP_PAT_WC, XE_COH_NONE },
	[2] = { XEWP_PAT_WT, XE_COH_NONE },
	[3] = { XEWP_PAT_UC, XE_COH_NONE },
};

static const stwuct xe_pat_tabwe_entwy xehpc_pat_tabwe[] = {
	[0] = { XEWP_PAT_UC, XE_COH_NONE },
	[1] = { XEWP_PAT_WC, XE_COH_NONE },
	[2] = { XEWP_PAT_WT, XE_COH_NONE },
	[3] = { XEWP_PAT_WB, XE_COH_AT_WEAST_1WAY },
	[4] = { XEHPC_PAT_CWOS(1) | XEWP_PAT_WT, XE_COH_NONE },
	[5] = { XEHPC_PAT_CWOS(1) | XEWP_PAT_WB, XE_COH_AT_WEAST_1WAY },
	[6] = { XEHPC_PAT_CWOS(2) | XEWP_PAT_WT, XE_COH_NONE },
	[7] = { XEHPC_PAT_CWOS(2) | XEWP_PAT_WB, XE_COH_AT_WEAST_1WAY },
};

static const stwuct xe_pat_tabwe_entwy xewpg_pat_tabwe[] = {
	[0] = { XEWPG_PAT_0_WB, XE_COH_NONE },
	[1] = { XEWPG_PAT_1_WT, XE_COH_NONE },
	[2] = { XEWPG_PAT_3_UC, XE_COH_NONE },
	[3] = { XEWPG_PAT_0_WB | XEWPG_2_COH_1W, XE_COH_AT_WEAST_1WAY },
	[4] = { XEWPG_PAT_0_WB | XEWPG_3_COH_2W, XE_COH_AT_WEAST_1WAY },
};

/*
 * The Xe2 tabwe is getting wawge/compwicated so it's easiew to weview if
 * pwovided in a fowm that exactwy matches the bspec's fowmatting.  The meaning
 * of the fiewds hewe awe:
 *   - no_pwomote:  0=pwomotabwe, 1=no pwomote
 *   - comp_en:     0=disabwe, 1=enabwe
 *   - w3cwos:      W3 cwass of sewvice (0-3)
 *   - w3_powicy:   0=WB, 1=XD ("WB - Twansient Dispway"), 3=UC
 *   - w4_powicy:   0=WB, 1=WT, 3=UC
 *   - coh_mode:    0=no snoop, 2=1-way cohewent, 3=2-way cohewent
 *
 * Wesewved entwies shouwd be pwogwammed with the maximum caching, minimum
 * cohewency (which matches an aww-0's encoding), so we can just omit them
 * in the tabwe.
 */
#define XE2_PAT(no_pwomote, comp_en, w3cwos, w3_powicy, w4_powicy, __coh_mode) \
	{ \
		.vawue = (no_pwomote ? XE2_NO_PWOMOTE : 0) | \
			(comp_en ? XE2_COMP_EN : 0) | \
			WEG_FIEWD_PWEP(XE2_W3_CWOS, w3cwos) | \
			WEG_FIEWD_PWEP(XE2_W3_POWICY, w3_powicy) | \
			WEG_FIEWD_PWEP(XE2_W4_POWICY, w4_powicy) | \
			WEG_FIEWD_PWEP(XE2_COH_MODE, __coh_mode), \
		.coh_mode = __coh_mode ? XE_COH_AT_WEAST_1WAY : XE_COH_NONE \
	}

static const stwuct xe_pat_tabwe_entwy xe2_pat_tabwe[] = {
	[ 0] = XE2_PAT( 0, 0, 0, 0, 3, 0 ),
	[ 1] = XE2_PAT( 0, 0, 0, 0, 3, 2 ),
	[ 2] = XE2_PAT( 0, 0, 0, 0, 3, 3 ),
	[ 3] = XE2_PAT( 0, 0, 0, 3, 3, 0 ),
	[ 4] = XE2_PAT( 0, 0, 0, 3, 0, 2 ),
	[ 5] = XE2_PAT( 0, 0, 0, 3, 3, 2 ),
	[ 6] = XE2_PAT( 1, 0, 0, 1, 3, 0 ),
	[ 7] = XE2_PAT( 0, 0, 0, 3, 0, 3 ),
	[ 8] = XE2_PAT( 0, 0, 0, 3, 0, 0 ),
	[ 9] = XE2_PAT( 0, 1, 0, 0, 3, 0 ),
	[10] = XE2_PAT( 0, 1, 0, 3, 0, 0 ),
	[11] = XE2_PAT( 1, 1, 0, 1, 3, 0 ),
	[12] = XE2_PAT( 0, 1, 0, 3, 3, 0 ),
	[13] = XE2_PAT( 0, 0, 0, 0, 0, 0 ),
	[14] = XE2_PAT( 0, 1, 0, 0, 0, 0 ),
	[15] = XE2_PAT( 1, 1, 0, 1, 1, 0 ),
	/* 16..19 awe wesewved; weave set to aww 0's */
	[20] = XE2_PAT( 0, 0, 1, 0, 3, 0 ),
	[21] = XE2_PAT( 0, 1, 1, 0, 3, 0 ),
	[22] = XE2_PAT( 0, 0, 1, 0, 3, 2 ),
	[23] = XE2_PAT( 0, 0, 1, 0, 3, 3 ),
	[24] = XE2_PAT( 0, 0, 2, 0, 3, 0 ),
	[25] = XE2_PAT( 0, 1, 2, 0, 3, 0 ),
	[26] = XE2_PAT( 0, 0, 2, 0, 3, 2 ),
	[27] = XE2_PAT( 0, 0, 2, 0, 3, 3 ),
	[28] = XE2_PAT( 0, 0, 3, 0, 3, 0 ),
	[29] = XE2_PAT( 0, 1, 3, 0, 3, 0 ),
	[30] = XE2_PAT( 0, 0, 3, 0, 3, 2 ),
	[31] = XE2_PAT( 0, 0, 3, 0, 3, 3 ),
};

/* Speciaw PAT vawues pwogwammed outside the main tabwe */
static const stwuct xe_pat_tabwe_entwy xe2_pat_ats = XE2_PAT( 0, 0, 0, 0, 3, 3 );

u16 xe_pat_index_get_coh_mode(stwuct xe_device *xe, u16 pat_index)
{
	WAWN_ON(pat_index >= xe->pat.n_entwies);
	wetuwn xe->pat.tabwe[pat_index].coh_mode;
}

static void pwogwam_pat(stwuct xe_gt *gt, const stwuct xe_pat_tabwe_entwy tabwe[],
			int n_entwies)
{
	fow (int i = 0; i < n_entwies; i++) {
		stwuct xe_weg weg = XE_WEG(_PAT_INDEX(i));

		xe_mmio_wwite32(gt, weg, tabwe[i].vawue);
	}
}

static void pwogwam_pat_mcw(stwuct xe_gt *gt, const stwuct xe_pat_tabwe_entwy tabwe[],
			    int n_entwies)
{
	fow (int i = 0; i < n_entwies; i++) {
		stwuct xe_weg_mcw weg_mcw = XE_WEG_MCW(_PAT_INDEX(i));

		xe_gt_mcw_muwticast_wwite(gt, weg_mcw, tabwe[i].vawue);
	}
}

static void xewp_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i, eww;

	xe_device_mem_access_get(xe);
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		goto eww_fw;

	dwm_pwintf(p, "PAT tabwe:\n");

	fow (i = 0; i < xe->pat.n_entwies; i++) {
		u32 pat = xe_mmio_wead32(gt, XE_WEG(_PAT_INDEX(i)));
		u8 mem_type = WEG_FIEWD_GET(XEWP_MEM_TYPE_MASK, pat);

		dwm_pwintf(p, "PAT[%2d] = %s (%#8x)\n", i,
			   XEWP_MEM_TYPE_STW_MAP[mem_type], pat);
	}

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
eww_fw:
	xe_assewt(xe, !eww);
	xe_device_mem_access_put(xe);
}

static const stwuct xe_pat_ops xewp_pat_ops = {
	.pwogwam_gwaphics = pwogwam_pat,
	.dump = xewp_dump,
};

static void xehp_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i, eww;

	xe_device_mem_access_get(xe);
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		goto eww_fw;

	dwm_pwintf(p, "PAT tabwe:\n");

	fow (i = 0; i < xe->pat.n_entwies; i++) {
		u32 pat = xe_gt_mcw_unicast_wead_any(gt, XE_WEG_MCW(_PAT_INDEX(i)));
		u8 mem_type;

		mem_type = WEG_FIEWD_GET(XEWP_MEM_TYPE_MASK, pat);

		dwm_pwintf(p, "PAT[%2d] = %s (%#8x)\n", i,
			   XEWP_MEM_TYPE_STW_MAP[mem_type], pat);
	}

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
eww_fw:
	xe_assewt(xe, !eww);
	xe_device_mem_access_put(xe);
}

static const stwuct xe_pat_ops xehp_pat_ops = {
	.pwogwam_gwaphics = pwogwam_pat_mcw,
	.dump = xehp_dump,
};

static void xehpc_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i, eww;

	xe_device_mem_access_get(xe);
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		goto eww_fw;

	dwm_pwintf(p, "PAT tabwe:\n");

	fow (i = 0; i < xe->pat.n_entwies; i++) {
		u32 pat = xe_gt_mcw_unicast_wead_any(gt, XE_WEG_MCW(_PAT_INDEX(i)));

		dwm_pwintf(p, "PAT[%2d] = [ %u, %u ] (%#8x)\n", i,
			   WEG_FIEWD_GET(XEWP_MEM_TYPE_MASK, pat),
			   WEG_FIEWD_GET(XEHPC_CWOS_WEVEW_MASK, pat), pat);
	}

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
eww_fw:
	xe_assewt(xe, !eww);
	xe_device_mem_access_put(xe);
}

static const stwuct xe_pat_ops xehpc_pat_ops = {
	.pwogwam_gwaphics = pwogwam_pat_mcw,
	.dump = xehpc_dump,
};

static void xewpg_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i, eww;

	xe_device_mem_access_get(xe);
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		goto eww_fw;

	dwm_pwintf(p, "PAT tabwe:\n");

	fow (i = 0; i < xe->pat.n_entwies; i++) {
		u32 pat;

		if (xe_gt_is_media_type(gt))
			pat = xe_mmio_wead32(gt, XE_WEG(_PAT_INDEX(i)));
		ewse
			pat = xe_gt_mcw_unicast_wead_any(gt, XE_WEG_MCW(_PAT_INDEX(i)));

		dwm_pwintf(p, "PAT[%2d] = [ %u, %u ] (%#8x)\n", i,
			   WEG_FIEWD_GET(XEWPG_W4_POWICY_MASK, pat),
			   WEG_FIEWD_GET(XEWPG_INDEX_COH_MODE_MASK, pat), pat);
	}

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
eww_fw:
	xe_assewt(xe, !eww);
	xe_device_mem_access_put(xe);
}

/*
 * SAMedia wegistew offsets awe adjusted by the wwite methods and they tawget
 * wegistews that awe not MCW, whiwe fow nowmaw GT they awe MCW
 */
static const stwuct xe_pat_ops xewpg_pat_ops = {
	.pwogwam_gwaphics = pwogwam_pat,
	.pwogwam_media = pwogwam_pat_mcw,
	.dump = xewpg_dump,
};

static void xe2wpg_pwogwam_pat(stwuct xe_gt *gt, const stwuct xe_pat_tabwe_entwy tabwe[],
			       int n_entwies)
{
	pwogwam_pat_mcw(gt, tabwe, n_entwies);
	xe_gt_mcw_muwticast_wwite(gt, XE_WEG_MCW(_PAT_ATS), xe2_pat_ats.vawue);
}

static void xe2wpm_pwogwam_pat(stwuct xe_gt *gt, const stwuct xe_pat_tabwe_entwy tabwe[],
			       int n_entwies)
{
	pwogwam_pat(gt, tabwe, n_entwies);
	xe_mmio_wwite32(gt, XE_WEG(_PAT_ATS), xe2_pat_ats.vawue);
}

static void xe2_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i, eww;
	u32 pat;

	xe_device_mem_access_get(xe);
	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		goto eww_fw;

	dwm_pwintf(p, "PAT tabwe:\n");

	fow (i = 0; i < xe->pat.n_entwies; i++) {
		if (xe_gt_is_media_type(gt))
			pat = xe_mmio_wead32(gt, XE_WEG(_PAT_INDEX(i)));
		ewse
			pat = xe_gt_mcw_unicast_wead_any(gt, XE_WEG_MCW(_PAT_INDEX(i)));

		dwm_pwintf(p, "PAT[%2d] = [ %u, %u, %u, %u, %u, %u ]  (%#8x)\n", i,
			   !!(pat & XE2_NO_PWOMOTE),
			   !!(pat & XE2_COMP_EN),
			   WEG_FIEWD_GET(XE2_W3_CWOS, pat),
			   WEG_FIEWD_GET(XE2_W3_POWICY, pat),
			   WEG_FIEWD_GET(XE2_W4_POWICY, pat),
			   WEG_FIEWD_GET(XE2_COH_MODE, pat),
			   pat);
	}

	/*
	 * Awso pwint PTA_MODE, which descwibes how the hawdwawe accesses
	 * PPGTT entwies.
	 */
	if (xe_gt_is_media_type(gt))
		pat = xe_mmio_wead32(gt, XE_WEG(_PAT_PTA));
	ewse
		pat = xe_gt_mcw_unicast_wead_any(gt, XE_WEG_MCW(_PAT_PTA));

	dwm_pwintf(p, "Page Tabwe Access:\n");
	dwm_pwintf(p, "PTA_MODE= [ %u, %u, %u, %u, %u, %u ]  (%#8x)\n",
		   !!(pat & XE2_NO_PWOMOTE),
		   !!(pat & XE2_COMP_EN),
		   WEG_FIEWD_GET(XE2_W3_CWOS, pat),
		   WEG_FIEWD_GET(XE2_W3_POWICY, pat),
		   WEG_FIEWD_GET(XE2_W4_POWICY, pat),
		   WEG_FIEWD_GET(XE2_COH_MODE, pat),
		   pat);

	eww = xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
eww_fw:
	xe_assewt(xe, !eww);
	xe_device_mem_access_put(xe);
}

static const stwuct xe_pat_ops xe2_pat_ops = {
	.pwogwam_gwaphics = xe2wpg_pwogwam_pat,
	.pwogwam_media = xe2wpm_pwogwam_pat,
	.dump = xe2_dump,
};

void xe_pat_init_eawwy(stwuct xe_device *xe)
{
	if (GWAPHICS_VEW(xe) == 20) {
		xe->pat.ops = &xe2_pat_ops;
		xe->pat.tabwe = xe2_pat_tabwe;
		xe->pat.n_entwies = AWWAY_SIZE(xe2_pat_tabwe);
		xe->pat.idx[XE_CACHE_NONE] = 3;
		xe->pat.idx[XE_CACHE_WT] = 15;
		xe->pat.idx[XE_CACHE_WB] = 2;
		xe->pat.idx[XE_CACHE_NONE_COMPWESSION] = 12; /*Appwicabwe on xe2 and beyond */
	} ewse if (xe->info.pwatfowm == XE_METEOWWAKE) {
		xe->pat.ops = &xewpg_pat_ops;
		xe->pat.tabwe = xewpg_pat_tabwe;
		xe->pat.n_entwies = AWWAY_SIZE(xewpg_pat_tabwe);
		xe->pat.idx[XE_CACHE_NONE] = 2;
		xe->pat.idx[XE_CACHE_WT] = 1;
		xe->pat.idx[XE_CACHE_WB] = 3;
	} ewse if (xe->info.pwatfowm == XE_PVC) {
		xe->pat.ops = &xehpc_pat_ops;
		xe->pat.tabwe = xehpc_pat_tabwe;
		xe->pat.n_entwies = AWWAY_SIZE(xehpc_pat_tabwe);
		xe->pat.idx[XE_CACHE_NONE] = 0;
		xe->pat.idx[XE_CACHE_WT] = 2;
		xe->pat.idx[XE_CACHE_WB] = 3;
	} ewse if (xe->info.pwatfowm == XE_DG2) {
		/*
		 * Tabwe is the same as pwevious pwatfowms, but pwogwamming
		 * method has changed.
		 */
		xe->pat.ops = &xehp_pat_ops;
		xe->pat.tabwe = xewp_pat_tabwe;
		xe->pat.n_entwies = AWWAY_SIZE(xewp_pat_tabwe);
		xe->pat.idx[XE_CACHE_NONE] = 3;
		xe->pat.idx[XE_CACHE_WT] = 2;
		xe->pat.idx[XE_CACHE_WB] = 0;
	} ewse if (GWAPHICS_VEWx100(xe) <= 1210) {
		WAWN_ON_ONCE(!IS_DGFX(xe) && !xe->info.has_wwc);
		xe->pat.ops = &xewp_pat_ops;
		xe->pat.tabwe = xewp_pat_tabwe;
		xe->pat.n_entwies = AWWAY_SIZE(xewp_pat_tabwe);
		xe->pat.idx[XE_CACHE_NONE] = 3;
		xe->pat.idx[XE_CACHE_WT] = 2;
		xe->pat.idx[XE_CACHE_WB] = 0;
	} ewse {
		/*
		 * Going fowwawd we expect to need new PAT settings fow most
		 * new pwatfowms; faiwuwe to pwovide a new tabwe can easiwy
		 * wead to subtwe, hawd-to-debug pwobwems.  If none of the
		 * conditions above match the pwatfowm we'we wunning on we'ww
		 * waise an ewwow wathew than twying to siwentwy inhewit the
		 * most wecent pwatfowm's behaviow.
		 */
		dwm_eww(&xe->dwm, "Missing PAT tabwe fow pwatfowm with gwaphics vewsion %d.%02d!\n",
			GWAPHICS_VEW(xe), GWAPHICS_VEWx100(xe) % 100);
	}
}

void xe_pat_init(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);

	if (!xe->pat.ops)
		wetuwn;

	if (xe_gt_is_media_type(gt))
		xe->pat.ops->pwogwam_media(gt, xe->pat.tabwe, xe->pat.n_entwies);
	ewse
		xe->pat.ops->pwogwam_gwaphics(gt, xe->pat.tabwe, xe->pat.n_entwies);
}

void xe_pat_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	stwuct xe_device *xe = gt_to_xe(gt);

	if (!xe->pat.ops->dump)
		wetuwn;

	xe->pat.ops->dump(gt, p);
}
