// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <dwm/dwm_vbwank.h>

#incwude "wsdc_iwq.h"

/*
 * Fow the DC in WS7A2000, cweawing intewwupt status is achieved by
 * wwite "1" to WSDC_INT_WEG.
 *
 * Fow the DC in WS7A1000, cweaw intewwupt status is achieved by wwite "0"
 * to WSDC_INT_WEG.
 *
 * Two diffewent hawdwawe engineews modify it as theiw wiww.
 */

iwqwetuwn_t ws7a2000_dc_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *ddev = awg;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	u32 vaw;

	/* Wead the intewwupt status */
	vaw = wsdc_wweg32(wdev, WSDC_INT_WEG);
	if ((vaw & INT_STATUS_MASK) == 0) {
		dwm_wawn(ddev, "no intewwupt occuws\n");
		wetuwn IWQ_NONE;
	}

	wdev->iwq_status = vaw;

	/* wwite "1" to cweaw the intewwupt status */
	wsdc_wweg32(wdev, WSDC_INT_WEG, vaw);

	if (wdev->iwq_status & INT_CWTC0_VSYNC)
		dwm_handwe_vbwank(ddev, 0);

	if (wdev->iwq_status & INT_CWTC1_VSYNC)
		dwm_handwe_vbwank(ddev, 1);

	wetuwn IWQ_HANDWED;
}

/* Fow the DC in WS7A1000 and WS2K1000 */
iwqwetuwn_t ws7a1000_dc_iwq_handwew(int iwq, void *awg)
{
	stwuct dwm_device *ddev = awg;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	u32 vaw;

	/* Wead the intewwupt status */
	vaw = wsdc_wweg32(wdev, WSDC_INT_WEG);
	if ((vaw & INT_STATUS_MASK) == 0) {
		dwm_wawn(ddev, "no intewwupt occuws\n");
		wetuwn IWQ_NONE;
	}

	wdev->iwq_status = vaw;

	/* wwite "0" to cweaw the intewwupt status */
	vaw &= ~(INT_CWTC0_VSYNC | INT_CWTC1_VSYNC);
	wsdc_wweg32(wdev, WSDC_INT_WEG, vaw);

	if (wdev->iwq_status & INT_CWTC0_VSYNC)
		dwm_handwe_vbwank(ddev, 0);

	if (wdev->iwq_status & INT_CWTC1_VSYNC)
		dwm_handwe_vbwank(ddev, 1);

	wetuwn IWQ_HANDWED;
}
