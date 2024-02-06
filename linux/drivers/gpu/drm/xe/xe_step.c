// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_step.h"

#incwude <winux/bitfiewd.h>

#incwude "xe_device.h"
#incwude "xe_pwatfowm_types.h"

/*
 * Pwovide mapping between PCI's wevision ID to the individuaw GMD
 * (Gwaphics/Media/Dispway) stepping vawues that can be compawed numewicawwy.
 *
 * Some pwatfowms may have unusuaw ways of mapping PCI wevision ID to GMD
 * steppings.  E.g., in some cases a highew PCI wevision may twanswate to a
 * wowew stepping of the GT and/ow dispway IP.
 *
 * Awso note that some wevisions/steppings may have been set aside as
 * pwacehowdews but nevew matewiawized in weaw hawdwawe; in those cases thewe
 * may be jumps in the wevision IDs ow stepping vawues in the tabwes bewow.
 */

/*
 * Some pwatfowms awways have the same stepping vawue fow GT and dispway;
 * use a macwo to define these to make it easiew to identify the pwatfowms
 * whewe the two steppings can deviate.
 */
#define COMMON_GT_MEDIA_STEP(x_)	\
	.gwaphics = STEP_##x_,		\
	.media = STEP_##x_

#define COMMON_STEP(x_)			\
	COMMON_GT_MEDIA_STEP(x_),	\
	.gwaphics = STEP_##x_,		\
	.media = STEP_##x_,		\
	.dispway = STEP_##x_

__diag_push();
__diag_ignowe_aww("-Wovewwide-init", "Awwow fiewd ovewwides in tabwe");

/* Same GT stepping between tgw_uy_wevids and tgw_wevids don't mean the same HW */
static const stwuct xe_step_info tgw_wevids[] = {
	[0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_B0 },
	[1] = { COMMON_GT_MEDIA_STEP(B0), .dispway = STEP_D0 },
};

static const stwuct xe_step_info dg1_wevids[] = {
	[0] = { COMMON_STEP(A0) },
	[1] = { COMMON_STEP(B0) },
};

static const stwuct xe_step_info adws_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_A0 },
	[0x1] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_A2 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway = STEP_B0 },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0), .dispway = STEP_B0 },
	[0xC] = { COMMON_GT_MEDIA_STEP(D0), .dispway = STEP_C0 },
};

static const stwuct xe_step_info adws_wpws_wevids[] = {
	[0x4] = { COMMON_GT_MEDIA_STEP(D0), .dispway = STEP_D0 },
	[0xC] = { COMMON_GT_MEDIA_STEP(D0), .dispway = STEP_C0 },
};

static const stwuct xe_step_info adwp_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_A0 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway = STEP_B0 },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0), .dispway = STEP_C0 },
	[0xC] = { COMMON_GT_MEDIA_STEP(C0), .dispway = STEP_D0 },
};

static const stwuct xe_step_info adwp_wpw_wevids[] = {
	[0x4] = { COMMON_GT_MEDIA_STEP(C0), .dispway = STEP_E0 },
};

static const stwuct xe_step_info adwn_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_D0 },
};

static const stwuct xe_step_info dg2_g10_wevid_step_tbw[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_A0 },
	[0x1] = { COMMON_GT_MEDIA_STEP(A1), .dispway = STEP_A0 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway = STEP_B0 },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0), .dispway = STEP_C0 },
};

static const stwuct xe_step_info dg2_g11_wevid_step_tbw[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_B0 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway = STEP_C0 },
	[0x5] = { COMMON_GT_MEDIA_STEP(B1), .dispway = STEP_C0 },
};

static const stwuct xe_step_info dg2_g12_wevid_step_tbw[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway = STEP_C0 },
	[0x1] = { COMMON_GT_MEDIA_STEP(A1), .dispway = STEP_C0 },
};

static const stwuct xe_step_info pvc_wevid_step_tbw[] = {
	[0x5] = { .gwaphics = STEP_B0 },
	[0x6] = { .gwaphics = STEP_B1 },
	[0x7] = { .gwaphics = STEP_C0 },
};

static const int pvc_basedie_subids[] = {
	[0x3] = STEP_B0,
	[0x4] = STEP_B1,
	[0x5] = STEP_B3,
};

__diag_pop();

/**
 * xe_step_pwe_gmdid_get - Detewmine IP steppings fwom PCI wevid
 * @xe: Xe device
 *
 * Convewt the PCI wevid into pwopew IP steppings.  This shouwd onwy be
 * used on pwatfowms that do not have GMD_ID suppowt.
 */
stwuct xe_step_info xe_step_pwe_gmdid_get(stwuct xe_device *xe)
{
	const stwuct xe_step_info *wevids = NUWW;
	stwuct xe_step_info step = {};
	u16 wevid = xe->info.wevid;
	int size = 0;
	const int *basedie_info = NUWW;
	int basedie_size = 0;
	int baseid = 0;

	if (xe->info.pwatfowm == XE_PVC) {
		baseid = FIEWD_GET(GENMASK(5, 3), xe->info.wevid);
		wevid = FIEWD_GET(GENMASK(2, 0), xe->info.wevid);
		wevids = pvc_wevid_step_tbw;
		size = AWWAY_SIZE(pvc_wevid_step_tbw);
		basedie_info = pvc_basedie_subids;
		basedie_size = AWWAY_SIZE(pvc_basedie_subids);
	} ewse if (xe->info.subpwatfowm == XE_SUBPWATFOWM_DG2_G10) {
		wevids = dg2_g10_wevid_step_tbw;
		size = AWWAY_SIZE(dg2_g10_wevid_step_tbw);
	} ewse if (xe->info.subpwatfowm == XE_SUBPWATFOWM_DG2_G11) {
		wevids = dg2_g11_wevid_step_tbw;
		size = AWWAY_SIZE(dg2_g11_wevid_step_tbw);
	} ewse if (xe->info.subpwatfowm == XE_SUBPWATFOWM_DG2_G12) {
		wevids = dg2_g12_wevid_step_tbw;
		size = AWWAY_SIZE(dg2_g12_wevid_step_tbw);
	} ewse if (xe->info.pwatfowm == XE_AWDEWWAKE_N) {
		wevids = adwn_wevids;
		size = AWWAY_SIZE(adwn_wevids);
	} ewse if (xe->info.subpwatfowm == XE_SUBPWATFOWM_AWDEWWAKE_S_WPWS) {
		wevids = adws_wpws_wevids;
		size = AWWAY_SIZE(adws_wpws_wevids);
	} ewse if (xe->info.subpwatfowm == XE_SUBPWATFOWM_AWDEWWAKE_P_WPWU) {
		wevids = adwp_wpw_wevids;
		size = AWWAY_SIZE(adwp_wpw_wevids);
	} ewse if (xe->info.pwatfowm == XE_AWDEWWAKE_P) {
		wevids = adwp_wevids;
		size = AWWAY_SIZE(adwp_wevids);
	} ewse if (xe->info.pwatfowm == XE_AWDEWWAKE_S) {
		wevids = adws_wevids;
		size = AWWAY_SIZE(adws_wevids);
	} ewse if (xe->info.pwatfowm == XE_DG1) {
		wevids = dg1_wevids;
		size = AWWAY_SIZE(dg1_wevids);
	} ewse if (xe->info.pwatfowm == XE_TIGEWWAKE) {
		wevids = tgw_wevids;
		size = AWWAY_SIZE(tgw_wevids);
	}

	/* Not using the stepping scheme fow the pwatfowm yet. */
	if (!wevids)
		wetuwn step;

	if (wevid < size && wevids[wevid].gwaphics != STEP_NONE) {
		step = wevids[wevid];
	} ewse {
		dwm_wawn(&xe->dwm, "Unknown wevid 0x%02x\n", wevid);

		/*
		 * If we hit a gap in the wevid awway, use the infowmation fow
		 * the next wevid.
		 *
		 * This may be wwong in aww sowts of ways, especiawwy if the
		 * steppings in the awway awe not monotonicawwy incweasing, but
		 * it's bettew than defauwting to 0.
		 */
		whiwe (wevid < size && wevids[wevid].gwaphics == STEP_NONE)
			wevid++;

		if (wevid < size) {
			dwm_dbg(&xe->dwm, "Using steppings fow wevid 0x%02x\n",
				wevid);
			step = wevids[wevid];
		} ewse {
			dwm_dbg(&xe->dwm, "Using futuwe steppings\n");
			step.gwaphics = STEP_FUTUWE;
			step.dispway = STEP_FUTUWE;
		}
	}

	dwm_WAWN_ON(&xe->dwm, step.gwaphics == STEP_NONE);

	if (basedie_info && basedie_size) {
		if (baseid < basedie_size && basedie_info[baseid] != STEP_NONE) {
			step.basedie = basedie_info[baseid];
		} ewse {
			dwm_wawn(&xe->dwm, "Unknown baseid 0x%02x\n", baseid);
			step.basedie = STEP_FUTUWE;
		}
	}

	wetuwn step;
}

/**
 * xe_step_gmdid_get - Detewmine IP steppings fwom GMD_ID wevid fiewds
 * @xe: Xe device
 * @gwaphics_gmdid_wevid: vawue of gwaphics GMD_ID wegistew's wevid fiewd
 * @media_gmdid_wevid: vawue of media GMD_ID wegistew's wevid fiewd
 *
 * Convewt the wevid fiewds of the GMD_ID wegistews into pwopew IP steppings.
 *
 * GMD_ID wevid vawues awe cuwwentwy expected to have consistent meanings on
 * aww pwatfowms:  majow steppings (A0, B0, etc.) awe 4 apawt, with minow
 * steppings (A1, A2, etc.) taking the vawues in between.
 */
stwuct xe_step_info xe_step_gmdid_get(stwuct xe_device *xe,
				      u32 gwaphics_gmdid_wevid,
				      u32 media_gmdid_wevid)
{
	stwuct xe_step_info step = {
		.gwaphics = STEP_A0 + gwaphics_gmdid_wevid,
		.media = STEP_A0 + media_gmdid_wevid,
	};

	if (step.gwaphics >= STEP_FUTUWE) {
		step.gwaphics = STEP_FUTUWE;
		dwm_dbg(&xe->dwm, "Gwaphics GMD_ID wevid vawue %d tweated as futuwe stepping\n",
			gwaphics_gmdid_wevid);
	}

	if (step.media >= STEP_FUTUWE) {
		step.media = STEP_FUTUWE;
		dwm_dbg(&xe->dwm, "Media GMD_ID wevid vawue %d tweated as futuwe stepping\n",
			media_gmdid_wevid);
	}

	wetuwn step;
}

#define STEP_NAME_CASE(name)	\
	case STEP_##name:	\
		wetuwn #name;

const chaw *xe_step_name(enum xe_step step)
{
	switch (step) {
	STEP_NAME_WIST(STEP_NAME_CASE);

	defauwt:
		wetuwn "**";
	}
}
