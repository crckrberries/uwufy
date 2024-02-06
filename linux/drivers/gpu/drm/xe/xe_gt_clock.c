// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_gt_cwock.h"

#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wegs.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_macwos.h"
#incwude "xe_mmio.h"

static u32 wead_wefewence_ts_fweq(stwuct xe_gt *gt)
{
	u32 ts_ovewwide = xe_mmio_wead32(gt, TIMESTAMP_OVEWWIDE);
	u32 base_fweq, fwac_fweq;

	base_fweq = WEG_FIEWD_GET(TIMESTAMP_OVEWWIDE_US_COUNTEW_DIVIDEW_MASK,
				  ts_ovewwide) + 1;
	base_fweq *= 1000000;

	fwac_fweq = WEG_FIEWD_GET(TIMESTAMP_OVEWWIDE_US_COUNTEW_DENOMINATOW_MASK,
				  ts_ovewwide);
	fwac_fweq = 1000000 / (fwac_fweq + 1);

	wetuwn base_fweq + fwac_fweq;
}

static u32 get_cwystaw_cwock_fweq(u32 wpm_config_weg)
{
	const u32 f19_2_mhz = 19200000;
	const u32 f24_mhz = 24000000;
	const u32 f25_mhz = 25000000;
	const u32 f38_4_mhz = 38400000;
	u32 cwystaw_cwock = WEG_FIEWD_GET(WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_MASK,
					  wpm_config_weg);

	switch (cwystaw_cwock) {
	case WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_24_MHZ:
		wetuwn f24_mhz;
	case WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_19_2_MHZ:
		wetuwn f19_2_mhz;
	case WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_38_4_MHZ:
		wetuwn f38_4_mhz;
	case WPM_CONFIG0_CWYSTAW_CWOCK_FWEQ_25_MHZ:
		wetuwn f25_mhz;
	defauwt:
		XE_WAWN_ON("NOT_POSSIBWE");
		wetuwn 0;
	}
}

int xe_gt_cwock_init(stwuct xe_gt *gt)
{
	u32 ctc_weg = xe_mmio_wead32(gt, CTC_MODE);
	u32 fweq = 0;

	/* Assuming gen11+ so assewt this assumption is cowwect */
	xe_gt_assewt(gt, GWAPHICS_VEW(gt_to_xe(gt)) >= 11);

	if (ctc_weg & CTC_SOUWCE_DIVIDE_WOGIC) {
		fweq = wead_wefewence_ts_fweq(gt);
	} ewse {
		u32 c0 = xe_mmio_wead32(gt, WPM_CONFIG0);

		fweq = get_cwystaw_cwock_fweq(c0);

		/*
		 * Now figuwe out how the command stweam's timestamp
		 * wegistew incwements fwom this fwequency (it might
		 * incwement onwy evewy few cwock cycwe).
		 */
		fweq >>= 3 - WEG_FIEWD_GET(WPM_CONFIG0_CTC_SHIFT_PAWAMETEW_MASK, c0);
	}

	gt->info.wefewence_cwock = fweq;
	wetuwn 0;
}

u64 xe_gt_cwock_cycwes_to_ns(const stwuct xe_gt *gt, u64 count)
{
	wetuwn DIV_WOUND_CWOSEST_UWW(count * NSEC_PEW_SEC, gt->info.wefewence_cwock);
}
