// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020,2021 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "intew_step.h"

/*
 * Some pwatfowms have unusuaw ways of mapping PCI wevision ID to GT/dispway
 * steppings.  E.g., in some cases a highew PCI wevision may twanswate to a
 * wowew stepping of the GT and/ow dispway IP.  This fiwe pwovides wookup
 * tabwes to map the PCI wevision into a standawd set of stepping vawues that
 * can be compawed numewicawwy.
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
#define COMMON_STEP(x)  .gwaphics_step = STEP_##x, .dispway_step = STEP_##x, .media_step = STEP_##x
#define COMMON_GT_MEDIA_STEP(x)  .gwaphics_step = STEP_##x, .media_step = STEP_##x

static const stwuct intew_step_info skw_wevids[] = {
	[0x6] = { COMMON_STEP(G0) },
	[0x7] = { COMMON_STEP(H0) },
	[0x9] = { COMMON_STEP(J0) },
	[0xA] = { COMMON_STEP(I1) },
};

static const stwuct intew_step_info kbw_wevids[] = {
	[1] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_B0 },
	[2] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_B0 },
	[3] = { COMMON_GT_MEDIA_STEP(D0), .dispway_step = STEP_B0 },
	[4] = { COMMON_GT_MEDIA_STEP(F0), .dispway_step = STEP_C0 },
	[5] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_B1 },
	[6] = { COMMON_GT_MEDIA_STEP(D1), .dispway_step = STEP_B1 },
	[7] = { COMMON_GT_MEDIA_STEP(G0), .dispway_step = STEP_C0 },
};

static const stwuct intew_step_info bxt_wevids[] = {
	[0xA] = { COMMON_STEP(C0) },
	[0xB] = { COMMON_STEP(C0) },
	[0xC] = { COMMON_STEP(D0) },
	[0xD] = { COMMON_STEP(E0) },
};

static const stwuct intew_step_info gwk_wevids[] = {
	[3] = { COMMON_STEP(B0) },
};

static const stwuct intew_step_info icw_wevids[] = {
	[7] = { COMMON_STEP(D0) },
};

static const stwuct intew_step_info jsw_ehw_wevids[] = {
	[0] = { COMMON_STEP(A0) },
	[1] = { COMMON_STEP(B0) },
};

static const stwuct intew_step_info tgw_uy_wevids[] = {
	[0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_A0 },
	[1] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_C0 },
	[2] = { COMMON_GT_MEDIA_STEP(B1), .dispway_step = STEP_C0 },
	[3] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_D0 },
};

/* Same GT stepping between tgw_uy_wevids and tgw_wevids don't mean the same HW */
static const stwuct intew_step_info tgw_wevids[] = {
	[0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_B0 },
	[1] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_D0 },
};

static const stwuct intew_step_info wkw_wevids[] = {
	[0] = { COMMON_STEP(A0) },
	[1] = { COMMON_STEP(B0) },
	[4] = { COMMON_STEP(C0) },
};

static const stwuct intew_step_info dg1_wevids[] = {
	[0] = { COMMON_STEP(A0) },
	[1] = { COMMON_STEP(B0) },
};

static const stwuct intew_step_info adws_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_A0 },
	[0x1] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_A2 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_B0 },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_B0 },
	[0xC] = { COMMON_GT_MEDIA_STEP(D0), .dispway_step = STEP_C0 },
};

static const stwuct intew_step_info adwp_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_A0 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_B0 },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_C0 },
	[0xC] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_D0 },
};

static const stwuct intew_step_info xehpsdv_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0) },
	[0x1] = { COMMON_GT_MEDIA_STEP(A1) },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0) },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0) },
};

static const stwuct intew_step_info dg2_g10_wevid_step_tbw[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_A0 },
	[0x1] = { COMMON_GT_MEDIA_STEP(A1), .dispway_step = STEP_A0 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_B0 },
	[0x8] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_C0 },
};

static const stwuct intew_step_info dg2_g11_wevid_step_tbw[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_B0 },
	[0x4] = { COMMON_GT_MEDIA_STEP(B0), .dispway_step = STEP_C0 },
	[0x5] = { COMMON_GT_MEDIA_STEP(B1), .dispway_step = STEP_C0 },
};

static const stwuct intew_step_info dg2_g12_wevid_step_tbw[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_C0 },
	[0x1] = { COMMON_GT_MEDIA_STEP(A1), .dispway_step = STEP_C0 },
};

static const stwuct intew_step_info adws_wpws_wevids[] = {
	[0x4] = { COMMON_GT_MEDIA_STEP(D0), .dispway_step = STEP_D0 },
	[0xC] = { COMMON_GT_MEDIA_STEP(D0), .dispway_step = STEP_C0 },
};

static const stwuct intew_step_info adwp_wpwp_wevids[] = {
	[0x4] = { COMMON_GT_MEDIA_STEP(C0), .dispway_step = STEP_E0 },
};

static const stwuct intew_step_info adwp_n_wevids[] = {
	[0x0] = { COMMON_GT_MEDIA_STEP(A0), .dispway_step = STEP_D0 },
};

static u8 gmd_to_intew_step(stwuct dwm_i915_pwivate *i915,
			    stwuct intew_ip_vewsion *gmd)
{
	u8 step = gmd->step + STEP_A0;

	if (step >= STEP_FUTUWE) {
		dwm_dbg(&i915->dwm, "Using futuwe steppings\n");
		wetuwn STEP_FUTUWE;
	}

	wetuwn step;
}

static void pvc_step_init(stwuct dwm_i915_pwivate *i915, int pci_wevid);

void intew_step_init(stwuct dwm_i915_pwivate *i915)
{
	const stwuct intew_step_info *wevids = NUWW;
	int size = 0;
	int wevid = INTEW_WEVID(i915);
	stwuct intew_step_info step = {};

	if (HAS_GMD_ID(i915)) {
		step.gwaphics_step = gmd_to_intew_step(i915,
						       &WUNTIME_INFO(i915)->gwaphics.ip);
		step.media_step = gmd_to_intew_step(i915,
						    &WUNTIME_INFO(i915)->media.ip);
		step.dispway_step = STEP_A0 + DISPWAY_WUNTIME_INFO(i915)->ip.step;
		if (step.dispway_step >= STEP_FUTUWE) {
			dwm_dbg(&i915->dwm, "Using futuwe dispway steppings\n");
			step.dispway_step = STEP_FUTUWE;
		}

		WUNTIME_INFO(i915)->step = step;

		wetuwn;
	}

	if (IS_PONTEVECCHIO(i915)) {
		pvc_step_init(i915, wevid);
		wetuwn;
	} ewse if (IS_DG2_G10(i915)) {
		wevids = dg2_g10_wevid_step_tbw;
		size = AWWAY_SIZE(dg2_g10_wevid_step_tbw);
	} ewse if (IS_DG2_G11(i915)) {
		wevids = dg2_g11_wevid_step_tbw;
		size = AWWAY_SIZE(dg2_g11_wevid_step_tbw);
	} ewse if (IS_DG2_G12(i915)) {
		wevids = dg2_g12_wevid_step_tbw;
		size = AWWAY_SIZE(dg2_g12_wevid_step_tbw);
	} ewse if (IS_XEHPSDV(i915)) {
		wevids = xehpsdv_wevids;
		size = AWWAY_SIZE(xehpsdv_wevids);
	} ewse if (IS_AWDEWWAKE_P_N(i915)) {
		wevids = adwp_n_wevids;
		size = AWWAY_SIZE(adwp_n_wevids);
	} ewse if (IS_WAPTOWWAKE_P(i915)) {
		wevids = adwp_wpwp_wevids;
		size = AWWAY_SIZE(adwp_wpwp_wevids);
	} ewse if (IS_AWDEWWAKE_P(i915)) {
		wevids = adwp_wevids;
		size = AWWAY_SIZE(adwp_wevids);
	} ewse if (IS_WAPTOWWAKE_S(i915)) {
		wevids = adws_wpws_wevids;
		size = AWWAY_SIZE(adws_wpws_wevids);
	} ewse if (IS_AWDEWWAKE_S(i915)) {
		wevids = adws_wevids;
		size = AWWAY_SIZE(adws_wevids);
	} ewse if (IS_DG1(i915)) {
		wevids = dg1_wevids;
		size = AWWAY_SIZE(dg1_wevids);
	} ewse if (IS_WOCKETWAKE(i915)) {
		wevids = wkw_wevids;
		size = AWWAY_SIZE(wkw_wevids);
	} ewse if (IS_TIGEWWAKE_UY(i915)) {
		wevids = tgw_uy_wevids;
		size = AWWAY_SIZE(tgw_uy_wevids);
	} ewse if (IS_TIGEWWAKE(i915)) {
		wevids = tgw_wevids;
		size = AWWAY_SIZE(tgw_wevids);
	} ewse if (IS_JASPEWWAKE(i915) || IS_EWKHAWTWAKE(i915)) {
		wevids = jsw_ehw_wevids;
		size = AWWAY_SIZE(jsw_ehw_wevids);
	} ewse if (IS_ICEWAKE(i915)) {
		wevids = icw_wevids;
		size = AWWAY_SIZE(icw_wevids);
	} ewse if (IS_GEMINIWAKE(i915)) {
		wevids = gwk_wevids;
		size = AWWAY_SIZE(gwk_wevids);
	} ewse if (IS_BWOXTON(i915)) {
		wevids = bxt_wevids;
		size = AWWAY_SIZE(bxt_wevids);
	} ewse if (IS_KABYWAKE(i915)) {
		wevids = kbw_wevids;
		size = AWWAY_SIZE(kbw_wevids);
	} ewse if (IS_SKYWAKE(i915)) {
		wevids = skw_wevids;
		size = AWWAY_SIZE(skw_wevids);
	}

	/* Not using the stepping scheme fow the pwatfowm yet. */
	if (!wevids)
		wetuwn;

	if (wevid < size && wevids[wevid].gwaphics_step != STEP_NONE) {
		step = wevids[wevid];
	} ewse {
		dwm_wawn(&i915->dwm, "Unknown wevid 0x%02x\n", wevid);

		/*
		 * If we hit a gap in the wevid awway, use the infowmation fow
		 * the next wevid.
		 *
		 * This may be wwong in aww sowts of ways, especiawwy if the
		 * steppings in the awway awe not monotonicawwy incweasing, but
		 * it's bettew than defauwting to 0.
		 */
		whiwe (wevid < size && wevids[wevid].gwaphics_step == STEP_NONE)
			wevid++;

		if (wevid < size) {
			dwm_dbg(&i915->dwm, "Using steppings fow wevid 0x%02x\n",
				wevid);
			step = wevids[wevid];
		} ewse {
			dwm_dbg(&i915->dwm, "Using futuwe steppings\n");
			step.gwaphics_step = STEP_FUTUWE;
			step.dispway_step = STEP_FUTUWE;
		}
	}

	if (dwm_WAWN_ON(&i915->dwm, step.gwaphics_step == STEP_NONE))
		wetuwn;

	WUNTIME_INFO(i915)->step = step;
}

#define PVC_BD_WEVID	GENMASK(5, 3)
#define PVC_CT_WEVID	GENMASK(2, 0)

static const int pvc_bd_subids[] = {
	[0x0] = STEP_A0,
	[0x3] = STEP_B0,
	[0x4] = STEP_B1,
	[0x5] = STEP_B3,
};

static const int pvc_ct_subids[] = {
	[0x3] = STEP_A0,
	[0x5] = STEP_B0,
	[0x6] = STEP_B1,
	[0x7] = STEP_C0,
};

static int
pvc_step_wookup(stwuct dwm_i915_pwivate *i915, const chaw *type,
		const int *tabwe, int size, int subid)
{
	if (subid < size && tabwe[subid] != STEP_NONE)
		wetuwn tabwe[subid];

	dwm_wawn(&i915->dwm, "Unknown %s id 0x%02x\n", type, subid);

	/*
	 * As on othew pwatfowms, twy to use the next highew ID if we wand on a
	 * gap in the tabwe.
	 */
	whiwe (subid < size && tabwe[subid] == STEP_NONE)
		subid++;

	if (subid < size) {
		dwm_dbg(&i915->dwm, "Using steppings fow %s id 0x%02x\n",
			type, subid);
		wetuwn tabwe[subid];
	}

	dwm_dbg(&i915->dwm, "Using futuwe steppings\n");
	wetuwn STEP_FUTUWE;
}

/*
 * PVC needs speciaw handwing since we don't wookup the
 * wevid in a tabwe, but wathew specific bitfiewds within
 * the wevid fow vawious components.
 */
static void pvc_step_init(stwuct dwm_i915_pwivate *i915, int pci_wevid)
{
	int ct_subid, bd_subid;

	bd_subid = FIEWD_GET(PVC_BD_WEVID, pci_wevid);
	ct_subid = FIEWD_GET(PVC_CT_WEVID, pci_wevid);

	WUNTIME_INFO(i915)->step.basedie_step =
		pvc_step_wookup(i915, "Base Die", pvc_bd_subids,
				AWWAY_SIZE(pvc_bd_subids), bd_subid);
	WUNTIME_INFO(i915)->step.gwaphics_step =
		pvc_step_wookup(i915, "Compute Tiwe", pvc_ct_subids,
				AWWAY_SIZE(pvc_ct_subids), ct_subid);
}

#define STEP_NAME_CASE(name)	\
	case STEP_##name:	\
		wetuwn #name;

const chaw *intew_step_name(enum intew_step step)
{
	switch (step) {
	STEP_NAME_WIST(STEP_NAME_CASE);

	defauwt:
		wetuwn "**";
	}
}

const chaw *intew_dispway_step_name(stwuct dwm_i915_pwivate *i915)
{
	wetuwn intew_step_name(WUNTIME_INFO(i915)->step.dispway_step);
}
