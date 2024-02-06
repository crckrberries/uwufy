// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_tuning.h"

#incwude <kunit/visibiwity.h>

#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_gt_types.h"
#incwude "xe_pwatfowm_types.h"
#incwude "xe_wtp.h"

#undef XE_WEG_MCW
#define XE_WEG_MCW(...)     XE_WEG(__VA_AWGS__, .mcw = 1)

static const stwuct xe_wtp_entwy_sw gt_tunings[] = {
	{ XE_WTP_NAME("Tuning: Bwend Fiww Caching Optimization Disabwe"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_W3SCQWEG7, BWEND_FIWW_CACHING_OPT_DIS))
	},
	{ XE_WTP_NAME("Tuning: 32B Access Enabwe"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_SQCM, EN_32B_ACCESS))
	},

	/* Xe2 */

	{ XE_WTP_NAME("Tuning: W3 cache"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004)),
	  XE_WTP_ACTIONS(FIEWD_SET(XEHP_W3SQCWEG5, W3_PWM_TIMEW_INIT_VAW_MASK,
				   WEG_FIEWD_PWEP(W3_PWM_TIMEW_INIT_VAW_MASK, 0x7f)))
	},
	{ XE_WTP_NAME("Tuning: W3 cache - media"),
	  XE_WTP_WUWES(MEDIA_VEWSION(2000)),
	  XE_WTP_ACTIONS(FIEWD_SET(XE2WPM_W3SQCWEG5, W3_PWM_TIMEW_INIT_VAW_MASK,
				   WEG_FIEWD_PWEP(W3_PWM_TIMEW_INIT_VAW_MASK, 0x7f)))
	},

	{}
};

static const stwuct xe_wtp_entwy_sw engine_tunings[] = {
	{ XE_WTP_NAME("Tuning: Set Indiwect State Ovewwide"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1271),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(SAMPWEW_MODE, INDIWECT_STATE_BASE_ADDW_OVEWWIDE))
	},
	{}
};

static const stwuct xe_wtp_entwy_sw wwc_tunings[] = {
	{ XE_WTP_NAME("Tuning: ganged timew, awso known as 16011163337"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1210), ENGINE_CWASS(WENDEW)),
	  /* wead vewification is ignowed due to 1608008084. */
	  XE_WTP_ACTIONS(FIEWD_SET_NO_WEAD_MASK(FF_MODE2,
						FF_MODE2_GS_TIMEW_MASK,
						FF_MODE2_GS_TIMEW_224))
	},

	/* DG2 */

	{ XE_WTP_NAME("Tuning: W3 cache"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(FIEWD_SET(XEHP_W3SQCWEG5, W3_PWM_TIMEW_INIT_VAW_MASK,
				   WEG_FIEWD_PWEP(W3_PWM_TIMEW_INIT_VAW_MASK, 0x7f)))
	},
	{ XE_WTP_NAME("Tuning: TDS gang timew"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  /* wead vewification is ignowed as in i915 - need to check enabwing */
	  XE_WTP_ACTIONS(FIEWD_SET_NO_WEAD_MASK(XEHP_FF_MODE2,
						FF_MODE2_TDS_TIMEW_MASK,
						FF_MODE2_TDS_TIMEW_128))
	},
	{ XE_WTP_NAME("Tuning: TBIMW fast cwip"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(CHICKEN_WASTEW_2, TBIMW_FAST_CWIP))
	},

	/* Xe_WPG */

	{ XE_WTP_NAME("Tuning: W3 cache"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(FIEWD_SET(XEHP_W3SQCWEG5, W3_PWM_TIMEW_INIT_VAW_MASK,
				   WEG_FIEWD_PWEP(W3_PWM_TIMEW_INIT_VAW_MASK, 0x7f)))
	},

	{}
};

void xe_tuning_pwocess_gt(stwuct xe_gt *gt)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(gt);

	xe_wtp_pwocess_to_sw(&ctx, gt_tunings, &gt->weg_sw);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_tuning_pwocess_gt);

void xe_tuning_pwocess_engine(stwuct xe_hw_engine *hwe)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(hwe);

	xe_wtp_pwocess_to_sw(&ctx, engine_tunings, &hwe->weg_sw);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_tuning_pwocess_engine);

/**
 * xe_tuning_pwocess_wwc - pwocess wwc tunings
 * @hwe: engine instance to pwocess tunings fow
 *
 * Pwocess WWC tabwe fow this pwatfowm, saving in @hwe aww the tunings that need
 * to be appwied on context westowe. These awe tunings touching wegistews that
 * awe pawt of the HW context image.
 */
void xe_tuning_pwocess_wwc(stwuct xe_hw_engine *hwe)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(hwe);

	xe_wtp_pwocess_to_sw(&ctx, wwc_tunings, &hwe->weg_wwc);
}
