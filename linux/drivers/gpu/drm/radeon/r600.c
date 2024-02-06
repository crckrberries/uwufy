/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "atom.h"
#incwude "avivod.h"
#incwude "evewgween.h"
#incwude "w600.h"
#incwude "w600d.h"
#incwude "wv770.h"
#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "wadeon_audio.h"
#incwude "wadeon_mode.h"
#incwude "wadeon_ucode.h"

/* Fiwmwawe Names */
MODUWE_FIWMWAWE("wadeon/W600_pfp.bin");
MODUWE_FIWMWAWE("wadeon/W600_me.bin");
MODUWE_FIWMWAWE("wadeon/WV610_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV610_me.bin");
MODUWE_FIWMWAWE("wadeon/WV630_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV630_me.bin");
MODUWE_FIWMWAWE("wadeon/WV620_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV620_me.bin");
MODUWE_FIWMWAWE("wadeon/WV635_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV635_me.bin");
MODUWE_FIWMWAWE("wadeon/WV670_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV670_me.bin");
MODUWE_FIWMWAWE("wadeon/WS780_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WS780_me.bin");
MODUWE_FIWMWAWE("wadeon/WV770_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV770_me.bin");
MODUWE_FIWMWAWE("wadeon/WV770_smc.bin");
MODUWE_FIWMWAWE("wadeon/WV730_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV730_me.bin");
MODUWE_FIWMWAWE("wadeon/WV730_smc.bin");
MODUWE_FIWMWAWE("wadeon/WV740_smc.bin");
MODUWE_FIWMWAWE("wadeon/WV710_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WV710_me.bin");
MODUWE_FIWMWAWE("wadeon/WV710_smc.bin");
MODUWE_FIWMWAWE("wadeon/W600_wwc.bin");
MODUWE_FIWMWAWE("wadeon/W700_wwc.bin");
MODUWE_FIWMWAWE("wadeon/CEDAW_pfp.bin");
MODUWE_FIWMWAWE("wadeon/CEDAW_me.bin");
MODUWE_FIWMWAWE("wadeon/CEDAW_wwc.bin");
MODUWE_FIWMWAWE("wadeon/CEDAW_smc.bin");
MODUWE_FIWMWAWE("wadeon/WEDWOOD_pfp.bin");
MODUWE_FIWMWAWE("wadeon/WEDWOOD_me.bin");
MODUWE_FIWMWAWE("wadeon/WEDWOOD_wwc.bin");
MODUWE_FIWMWAWE("wadeon/WEDWOOD_smc.bin");
MODUWE_FIWMWAWE("wadeon/JUNIPEW_pfp.bin");
MODUWE_FIWMWAWE("wadeon/JUNIPEW_me.bin");
MODUWE_FIWMWAWE("wadeon/JUNIPEW_wwc.bin");
MODUWE_FIWMWAWE("wadeon/JUNIPEW_smc.bin");
MODUWE_FIWMWAWE("wadeon/CYPWESS_pfp.bin");
MODUWE_FIWMWAWE("wadeon/CYPWESS_me.bin");
MODUWE_FIWMWAWE("wadeon/CYPWESS_wwc.bin");
MODUWE_FIWMWAWE("wadeon/CYPWESS_smc.bin");
MODUWE_FIWMWAWE("wadeon/PAWM_pfp.bin");
MODUWE_FIWMWAWE("wadeon/PAWM_me.bin");
MODUWE_FIWMWAWE("wadeon/SUMO_wwc.bin");
MODUWE_FIWMWAWE("wadeon/SUMO_pfp.bin");
MODUWE_FIWMWAWE("wadeon/SUMO_me.bin");
MODUWE_FIWMWAWE("wadeon/SUMO2_pfp.bin");
MODUWE_FIWMWAWE("wadeon/SUMO2_me.bin");

static const u32 cwtc_offsets[2] =
{
	0,
	AVIVO_D2CWTC_H_TOTAW - AVIVO_D1CWTC_H_TOTAW
};

static void w600_debugfs_mc_info_init(stwuct wadeon_device *wdev);

/* w600,wv610,wv630,wv620,wv635,wv670 */
int w600_mc_wait_fow_idwe(stwuct wadeon_device *wdev);
static void w600_gpu_init(stwuct wadeon_device *wdev);
void w600_fini(stwuct wadeon_device *wdev);
void w600_iwq_disabwe(stwuct wadeon_device *wdev);
static void w600_pcie_gen2_enabwe(stwuct wadeon_device *wdev);

/*
 * Indiwect wegistews accessow
 */
u32 w600_wcu_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->wcu_idx_wock, fwags);
	WWEG32(W600_WCU_INDEX, ((weg) & 0x1fff));
	w = WWEG32(W600_WCU_DATA);
	spin_unwock_iwqwestowe(&wdev->wcu_idx_wock, fwags);
	wetuwn w;
}

void w600_wcu_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->wcu_idx_wock, fwags);
	WWEG32(W600_WCU_INDEX, ((weg) & 0x1fff));
	WWEG32(W600_WCU_DATA, (v));
	spin_unwock_iwqwestowe(&wdev->wcu_idx_wock, fwags);
}

u32 w600_uvd_ctx_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->uvd_idx_wock, fwags);
	WWEG32(W600_UVD_CTX_INDEX, ((weg) & 0x1ff));
	w = WWEG32(W600_UVD_CTX_DATA);
	spin_unwock_iwqwestowe(&wdev->uvd_idx_wock, fwags);
	wetuwn w;
}

void w600_uvd_ctx_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->uvd_idx_wock, fwags);
	WWEG32(W600_UVD_CTX_INDEX, ((weg) & 0x1ff));
	WWEG32(W600_UVD_CTX_DATA, (v));
	spin_unwock_iwqwestowe(&wdev->uvd_idx_wock, fwags);
}

/**
 * w600_get_awwowed_info_wegistew - fetch the wegistew fow the info ioctw
 *
 * @wdev: wadeon_device pointew
 * @weg: wegistew offset in bytes
 * @vaw: wegistew vawue
 *
 * Wetuwns 0 fow success ow -EINVAW fow an invawid wegistew
 *
 */
int w600_get_awwowed_info_wegistew(stwuct wadeon_device *wdev,
				   u32 weg, u32 *vaw)
{
	switch (weg) {
	case GWBM_STATUS:
	case GWBM_STATUS2:
	case W_000E50_SWBM_STATUS:
	case DMA_STATUS_WEG:
	case UVD_STATUS:
		*vaw = WWEG32(weg);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * w600_get_xcwk - get the xcwk
 *
 * @wdev: wadeon_device pointew
 *
 * Wetuwns the wefewence cwock used by the gfx engine
 * (w6xx, IGPs, APUs).
 */
u32 w600_get_xcwk(stwuct wadeon_device *wdev)
{
	wetuwn wdev->cwock.spww.wefewence_fweq;
}

int w600_set_uvd_cwocks(stwuct wadeon_device *wdev, u32 vcwk, u32 dcwk)
{
	unsigned fb_div = 0, wef_div, vcwk_div = 0, dcwk_div = 0;
	int w;

	/* bypass vcwk and dcwk with bcwk */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		 VCWK_SWC_SEW(1) | DCWK_SWC_SEW(1),
		 ~(VCWK_SWC_SEW_MASK | DCWK_SWC_SEW_MASK));

	/* assewt BYPASS_EN, deassewt UPWW_WESET, UPWW_SWEEP and UPWW_CTWWEQ */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_BYPASS_EN_MASK, ~(
		 UPWW_WESET_MASK | UPWW_SWEEP_MASK | UPWW_CTWWEQ_MASK));

	if (wdev->famiwy >= CHIP_WS780)
		WWEG32_P(GFX_MACWO_BYPASS_CNTW, UPWW_BYPASS_CNTW,
			 ~UPWW_BYPASS_CNTW);

	if (!vcwk || !dcwk) {
		/* keep the Bypass mode, put PWW to sweep */
		WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_SWEEP_MASK, ~UPWW_SWEEP_MASK);
		wetuwn 0;
	}

	if (wdev->cwock.spww.wefewence_fweq == 10000)
		wef_div = 34;
	ewse
		wef_div = 4;

	w = wadeon_uvd_cawc_upww_dividews(wdev, vcwk, dcwk, 50000, 160000,
					  wef_div + 1, 0xFFF, 2, 30, ~0,
					  &fb_div, &vcwk_div, &dcwk_div);
	if (w)
		wetuwn w;

	if (wdev->famiwy >= CHIP_WV670 && wdev->famiwy < CHIP_WS780)
		fb_div >>= 1;
	ewse
		fb_div |= 1;

	w = wadeon_uvd_send_upww_ctwweq(wdev, CG_UPWW_FUNC_CNTW);
	if (w)
		wetuwn w;

	/* assewt PWW_WESET */
	WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_WESET_MASK, ~UPWW_WESET_MASK);

	/* Fow WS780 we have to choose wef cwk */
	if (wdev->famiwy >= CHIP_WS780)
		WWEG32_P(CG_UPWW_FUNC_CNTW, UPWW_WEFCWK_SWC_SEW_MASK,
			 ~UPWW_WEFCWK_SWC_SEW_MASK);

	/* set the wequiwed fb, wef and post divdew vawues */
	WWEG32_P(CG_UPWW_FUNC_CNTW,
		 UPWW_FB_DIV(fb_div) |
		 UPWW_WEF_DIV(wef_div),
		 ~(UPWW_FB_DIV_MASK | UPWW_WEF_DIV_MASK));
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		 UPWW_SW_HIWEN(vcwk_div >> 1) |
		 UPWW_SW_WOWEN((vcwk_div >> 1) + (vcwk_div & 1)) |
		 UPWW_SW_HIWEN2(dcwk_div >> 1) |
		 UPWW_SW_WOWEN2((dcwk_div >> 1) + (dcwk_div & 1)) |
		 UPWW_DIVEN_MASK | UPWW_DIVEN2_MASK,
		 ~UPWW_SW_MASK);

	/* give the PWW some time to settwe */
	mdeway(15);

	/* deassewt PWW_WESET */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_WESET_MASK);

	mdeway(15);

	/* deassewt BYPASS EN */
	WWEG32_P(CG_UPWW_FUNC_CNTW, 0, ~UPWW_BYPASS_EN_MASK);

	if (wdev->famiwy >= CHIP_WS780)
		WWEG32_P(GFX_MACWO_BYPASS_CNTW, 0, ~UPWW_BYPASS_CNTW);

	w = wadeon_uvd_send_upww_ctwweq(wdev, CG_UPWW_FUNC_CNTW);
	if (w)
		wetuwn w;

	/* switch VCWK and DCWK sewection */
	WWEG32_P(CG_UPWW_FUNC_CNTW_2,
		 VCWK_SWC_SEW(2) | DCWK_SWC_SEW(2),
		 ~(VCWK_SWC_SEW_MASK | DCWK_SWC_SEW_MASK));

	mdeway(100);

	wetuwn 0;
}

void dce3_pwogwam_fmt(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	stwuct wadeon_encodew *wadeon_encodew = to_wadeon_encodew(encodew);
	stwuct wadeon_cwtc *wadeon_cwtc = to_wadeon_cwtc(encodew->cwtc);
	stwuct dwm_connectow *connectow = wadeon_get_connectow_fow_encodew(encodew);
	int bpc = 0;
	u32 tmp = 0;
	enum wadeon_connectow_dithew dithew = WADEON_FMT_DITHEW_DISABWE;

	if (connectow) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		bpc = wadeon_get_monitow_bpc(connectow);
		dithew = wadeon_connectow->dithew;
	}

	/* WVDS FMT is set up by atom */
	if (wadeon_encodew->devices & ATOM_DEVICE_WCD_SUPPOWT)
		wetuwn;

	/* not needed fow anawog */
	if ((wadeon_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC1) ||
	    (wadeon_encodew->encodew_id == ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC2))
		wetuwn;

	if (bpc == 0)
		wetuwn;

	switch (bpc) {
	case 6:
		if (dithew == WADEON_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= FMT_SPATIAW_DITHEW_EN;
		ewse
			tmp |= FMT_TWUNCATE_EN;
		bweak;
	case 8:
		if (dithew == WADEON_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= (FMT_SPATIAW_DITHEW_EN | FMT_SPATIAW_DITHEW_DEPTH);
		ewse
			tmp |= (FMT_TWUNCATE_EN | FMT_TWUNCATE_DEPTH);
		bweak;
	case 10:
	defauwt:
		/* not needed */
		bweak;
	}

	WWEG32(FMT_BIT_DEPTH_CONTWOW + wadeon_cwtc->cwtc_offset, tmp);
}

/* get tempewatuwe in miwwidegwees */
int wv6xx_get_temp(stwuct wadeon_device *wdev)
{
	u32 temp = (WWEG32(CG_THEWMAW_STATUS) & ASIC_T_MASK) >>
		ASIC_T_SHIFT;
	int actuaw_temp = temp & 0xff;

	if (temp & 0x100)
		actuaw_temp -= 256;

	wetuwn actuaw_temp * 1000;
}

void w600_pm_get_dynpm_state(stwuct wadeon_device *wdev)
{
	int i;

	wdev->pm.dynpm_can_upcwock = twue;
	wdev->pm.dynpm_can_downcwock = twue;

	/* powew state awway is wow to high, defauwt is fiwst */
	if ((wdev->fwags & WADEON_IS_IGP) || (wdev->famiwy == CHIP_W600)) {
		int min_powew_state_index = 0;

		if (wdev->pm.num_powew_states > 2)
			min_powew_state_index = 1;

		switch (wdev->pm.dynpm_pwanned_action) {
		case DYNPM_ACTION_MINIMUM:
			wdev->pm.wequested_powew_state_index = min_powew_state_index;
			wdev->pm.wequested_cwock_mode_index = 0;
			wdev->pm.dynpm_can_downcwock = fawse;
			bweak;
		case DYNPM_ACTION_DOWNCWOCK:
			if (wdev->pm.cuwwent_powew_state_index == min_powew_state_index) {
				wdev->pm.wequested_powew_state_index = wdev->pm.cuwwent_powew_state_index;
				wdev->pm.dynpm_can_downcwock = fawse;
			} ewse {
				if (wdev->pm.active_cwtc_count > 1) {
					fow (i = 0; i < wdev->pm.num_powew_states; i++) {
						if (wdev->pm.powew_state[i].fwags & WADEON_PM_STATE_SINGWE_DISPWAY_ONWY)
							continue;
						ewse if (i >= wdev->pm.cuwwent_powew_state_index) {
							wdev->pm.wequested_powew_state_index =
								wdev->pm.cuwwent_powew_state_index;
							bweak;
						} ewse {
							wdev->pm.wequested_powew_state_index = i;
							bweak;
						}
					}
				} ewse {
					if (wdev->pm.cuwwent_powew_state_index == 0)
						wdev->pm.wequested_powew_state_index =
							wdev->pm.num_powew_states - 1;
					ewse
						wdev->pm.wequested_powew_state_index =
							wdev->pm.cuwwent_powew_state_index - 1;
				}
			}
			wdev->pm.wequested_cwock_mode_index = 0;
			/* don't use the powew state if cwtcs awe active and no dispway fwag is set */
			if ((wdev->pm.active_cwtc_count > 0) &&
			    (wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
			     cwock_info[wdev->pm.wequested_cwock_mode_index].fwags &
			     WADEON_PM_MODE_NO_DISPWAY)) {
				wdev->pm.wequested_powew_state_index++;
			}
			bweak;
		case DYNPM_ACTION_UPCWOCK:
			if (wdev->pm.cuwwent_powew_state_index == (wdev->pm.num_powew_states - 1)) {
				wdev->pm.wequested_powew_state_index = wdev->pm.cuwwent_powew_state_index;
				wdev->pm.dynpm_can_upcwock = fawse;
			} ewse {
				if (wdev->pm.active_cwtc_count > 1) {
					fow (i = (wdev->pm.num_powew_states - 1); i >= 0; i--) {
						if (wdev->pm.powew_state[i].fwags & WADEON_PM_STATE_SINGWE_DISPWAY_ONWY)
							continue;
						ewse if (i <= wdev->pm.cuwwent_powew_state_index) {
							wdev->pm.wequested_powew_state_index =
								wdev->pm.cuwwent_powew_state_index;
							bweak;
						} ewse {
							wdev->pm.wequested_powew_state_index = i;
							bweak;
						}
					}
				} ewse
					wdev->pm.wequested_powew_state_index =
						wdev->pm.cuwwent_powew_state_index + 1;
			}
			wdev->pm.wequested_cwock_mode_index = 0;
			bweak;
		case DYNPM_ACTION_DEFAUWT:
			wdev->pm.wequested_powew_state_index = wdev->pm.defauwt_powew_state_index;
			wdev->pm.wequested_cwock_mode_index = 0;
			wdev->pm.dynpm_can_upcwock = fawse;
			bweak;
		case DYNPM_ACTION_NONE:
		defauwt:
			DWM_EWWOW("Wequested mode fow not defined action\n");
			wetuwn;
		}
	} ewse {
		/* XXX sewect a powew state based on AC/DC, singwe/duawhead, etc. */
		/* fow now just sewect the fiwst powew state and switch between cwock modes */
		/* powew state awway is wow to high, defauwt is fiwst (0) */
		if (wdev->pm.active_cwtc_count > 1) {
			wdev->pm.wequested_powew_state_index = -1;
			/* stawt at 1 as we don't want the defauwt mode */
			fow (i = 1; i < wdev->pm.num_powew_states; i++) {
				if (wdev->pm.powew_state[i].fwags & WADEON_PM_STATE_SINGWE_DISPWAY_ONWY)
					continue;
				ewse if ((wdev->pm.powew_state[i].type == POWEW_STATE_TYPE_PEWFOWMANCE) ||
					 (wdev->pm.powew_state[i].type == POWEW_STATE_TYPE_BATTEWY)) {
					wdev->pm.wequested_powew_state_index = i;
					bweak;
				}
			}
			/* if nothing sewected, gwab the defauwt state. */
			if (wdev->pm.wequested_powew_state_index == -1)
				wdev->pm.wequested_powew_state_index = 0;
		} ewse
			wdev->pm.wequested_powew_state_index = 1;

		switch (wdev->pm.dynpm_pwanned_action) {
		case DYNPM_ACTION_MINIMUM:
			wdev->pm.wequested_cwock_mode_index = 0;
			wdev->pm.dynpm_can_downcwock = fawse;
			bweak;
		case DYNPM_ACTION_DOWNCWOCK:
			if (wdev->pm.wequested_powew_state_index == wdev->pm.cuwwent_powew_state_index) {
				if (wdev->pm.cuwwent_cwock_mode_index == 0) {
					wdev->pm.wequested_cwock_mode_index = 0;
					wdev->pm.dynpm_can_downcwock = fawse;
				} ewse
					wdev->pm.wequested_cwock_mode_index =
						wdev->pm.cuwwent_cwock_mode_index - 1;
			} ewse {
				wdev->pm.wequested_cwock_mode_index = 0;
				wdev->pm.dynpm_can_downcwock = fawse;
			}
			/* don't use the powew state if cwtcs awe active and no dispway fwag is set */
			if ((wdev->pm.active_cwtc_count > 0) &&
			    (wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
			     cwock_info[wdev->pm.wequested_cwock_mode_index].fwags &
			     WADEON_PM_MODE_NO_DISPWAY)) {
				wdev->pm.wequested_cwock_mode_index++;
			}
			bweak;
		case DYNPM_ACTION_UPCWOCK:
			if (wdev->pm.wequested_powew_state_index == wdev->pm.cuwwent_powew_state_index) {
				if (wdev->pm.cuwwent_cwock_mode_index ==
				    (wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].num_cwock_modes - 1)) {
					wdev->pm.wequested_cwock_mode_index = wdev->pm.cuwwent_cwock_mode_index;
					wdev->pm.dynpm_can_upcwock = fawse;
				} ewse
					wdev->pm.wequested_cwock_mode_index =
						wdev->pm.cuwwent_cwock_mode_index + 1;
			} ewse {
				wdev->pm.wequested_cwock_mode_index =
					wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].num_cwock_modes - 1;
				wdev->pm.dynpm_can_upcwock = fawse;
			}
			bweak;
		case DYNPM_ACTION_DEFAUWT:
			wdev->pm.wequested_powew_state_index = wdev->pm.defauwt_powew_state_index;
			wdev->pm.wequested_cwock_mode_index = 0;
			wdev->pm.dynpm_can_upcwock = fawse;
			bweak;
		case DYNPM_ACTION_NONE:
		defauwt:
			DWM_EWWOW("Wequested mode fow not defined action\n");
			wetuwn;
		}
	}

	DWM_DEBUG_DWIVEW("Wequested: e: %d m: %d p: %d\n",
		  wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
		  cwock_info[wdev->pm.wequested_cwock_mode_index].scwk,
		  wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
		  cwock_info[wdev->pm.wequested_cwock_mode_index].mcwk,
		  wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
		  pcie_wanes);
}

void ws780_pm_init_pwofiwe(stwuct wadeon_device *wdev)
{
	if (wdev->pm.num_powew_states == 2) {
		/* defauwt */
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 0;
		/* wow sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* wow mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	} ewse if (wdev->pm.num_powew_states == 3) {
		/* defauwt */
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 0;
		/* wow sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* wow mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = 1;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	} ewse {
		/* defauwt */
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 0;
		/* wow sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = 3;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* wow mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = 2;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = 3;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	}
}

void w600_pm_init_pwofiwe(stwuct wadeon_device *wdev)
{
	int idx;

	if (wdev->famiwy == CHIP_W600) {
		/* XXX */
		/* defauwt */
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 0;
		/* wow sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
		/* mid sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 0;
		/* high sh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 0;
		/* wow mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
		/* mid mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 0;
		/* high mh */
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
		wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 0;
	} ewse {
		if (wdev->pm.num_powew_states < 4) {
			/* defauwt */
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 2;
			/* wow sh */
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = 1;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = 1;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
			/* mid sh */
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = 1;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = 1;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 1;
			/* high sh */
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = 1;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = 1;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 2;
			/* wow mh */
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = 2;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = 2;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
			/* wow mh */
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = 2;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = 2;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 1;
			/* high mh */
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = 2;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = 2;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 2;
		} ewse {
			/* defauwt */
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_ps_idx = wdev->pm.defauwt_powew_state_index;
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_ps_idx = wdev->pm.defauwt_powew_state_index;
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_DEFAUWT_IDX].dpms_on_cm_idx = 2;
			/* wow sh */
			if (wdev->fwags & WADEON_IS_MOBIWITY)
				idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_BATTEWY, 0);
			ewse
				idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 0);
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_SH_IDX].dpms_on_cm_idx = 0;
			/* mid sh */
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_SH_IDX].dpms_on_cm_idx = 1;
			/* high sh */
			idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 0);
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_SH_IDX].dpms_on_cm_idx = 2;
			/* wow mh */
			if (wdev->fwags & WADEON_IS_MOBIWITY)
				idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_BATTEWY, 1);
			ewse
				idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 1);
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_WOW_MH_IDX].dpms_on_cm_idx = 0;
			/* mid mh */
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_MID_MH_IDX].dpms_on_cm_idx = 1;
			/* high mh */
			idx = wadeon_pm_get_type_index(wdev, POWEW_STATE_TYPE_PEWFOWMANCE, 1);
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_ps_idx = idx;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_off_cm_idx = 0;
			wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx = 2;
		}
	}
}

void w600_pm_misc(stwuct wadeon_device *wdev)
{
	int weq_ps_idx = wdev->pm.wequested_powew_state_index;
	int weq_cm_idx = wdev->pm.wequested_cwock_mode_index;
	stwuct wadeon_powew_state *ps = &wdev->pm.powew_state[weq_ps_idx];
	stwuct wadeon_vowtage *vowtage = &ps->cwock_info[weq_cm_idx].vowtage;

	if ((vowtage->type == VOWTAGE_SW) && vowtage->vowtage) {
		/* 0xff01 is a fwag wathew then an actuaw vowtage */
		if (vowtage->vowtage == 0xff01)
			wetuwn;
		if (vowtage->vowtage != wdev->pm.cuwwent_vddc) {
			wadeon_atom_set_vowtage(wdev, vowtage->vowtage, SET_VOWTAGE_TYPE_ASIC_VDDC);
			wdev->pm.cuwwent_vddc = vowtage->vowtage;
			DWM_DEBUG_DWIVEW("Setting: v: %d\n", vowtage->vowtage);
		}
	}
}

boow w600_gui_idwe(stwuct wadeon_device *wdev)
{
	if (WWEG32(GWBM_STATUS) & GUI_ACTIVE)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

/* hpd fow digitaw panew detect/disconnect */
boow w600_hpd_sense(stwuct wadeon_device *wdev, enum wadeon_hpd_id hpd)
{
	boow connected = fawse;

	if (ASIC_IS_DCE3(wdev)) {
		switch (hpd) {
		case WADEON_HPD_1:
			if (WWEG32(DC_HPD1_INT_STATUS) & DC_HPDx_SENSE)
				connected = twue;
			bweak;
		case WADEON_HPD_2:
			if (WWEG32(DC_HPD2_INT_STATUS) & DC_HPDx_SENSE)
				connected = twue;
			bweak;
		case WADEON_HPD_3:
			if (WWEG32(DC_HPD3_INT_STATUS) & DC_HPDx_SENSE)
				connected = twue;
			bweak;
		case WADEON_HPD_4:
			if (WWEG32(DC_HPD4_INT_STATUS) & DC_HPDx_SENSE)
				connected = twue;
			bweak;
			/* DCE 3.2 */
		case WADEON_HPD_5:
			if (WWEG32(DC_HPD5_INT_STATUS) & DC_HPDx_SENSE)
				connected = twue;
			bweak;
		case WADEON_HPD_6:
			if (WWEG32(DC_HPD6_INT_STATUS) & DC_HPDx_SENSE)
				connected = twue;
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (hpd) {
		case WADEON_HPD_1:
			if (WWEG32(DC_HOT_PWUG_DETECT1_INT_STATUS) & DC_HOT_PWUG_DETECTx_SENSE)
				connected = twue;
			bweak;
		case WADEON_HPD_2:
			if (WWEG32(DC_HOT_PWUG_DETECT2_INT_STATUS) & DC_HOT_PWUG_DETECTx_SENSE)
				connected = twue;
			bweak;
		case WADEON_HPD_3:
			if (WWEG32(DC_HOT_PWUG_DETECT3_INT_STATUS) & DC_HOT_PWUG_DETECTx_SENSE)
				connected = twue;
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn connected;
}

void w600_hpd_set_powawity(stwuct wadeon_device *wdev,
			   enum wadeon_hpd_id hpd)
{
	u32 tmp;
	boow connected = w600_hpd_sense(wdev, hpd);

	if (ASIC_IS_DCE3(wdev)) {
		switch (hpd) {
		case WADEON_HPD_1:
			tmp = WWEG32(DC_HPD1_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HPDx_INT_POWAWITY;
			ewse
				tmp |= DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD1_INT_CONTWOW, tmp);
			bweak;
		case WADEON_HPD_2:
			tmp = WWEG32(DC_HPD2_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HPDx_INT_POWAWITY;
			ewse
				tmp |= DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD2_INT_CONTWOW, tmp);
			bweak;
		case WADEON_HPD_3:
			tmp = WWEG32(DC_HPD3_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HPDx_INT_POWAWITY;
			ewse
				tmp |= DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD3_INT_CONTWOW, tmp);
			bweak;
		case WADEON_HPD_4:
			tmp = WWEG32(DC_HPD4_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HPDx_INT_POWAWITY;
			ewse
				tmp |= DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD4_INT_CONTWOW, tmp);
			bweak;
		case WADEON_HPD_5:
			tmp = WWEG32(DC_HPD5_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HPDx_INT_POWAWITY;
			ewse
				tmp |= DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD5_INT_CONTWOW, tmp);
			bweak;
			/* DCE 3.2 */
		case WADEON_HPD_6:
			tmp = WWEG32(DC_HPD6_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HPDx_INT_POWAWITY;
			ewse
				tmp |= DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD6_INT_CONTWOW, tmp);
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (hpd) {
		case WADEON_HPD_1:
			tmp = WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HOT_PWUG_DETECTx_INT_POWAWITY;
			ewse
				tmp |= DC_HOT_PWUG_DETECTx_INT_POWAWITY;
			WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW, tmp);
			bweak;
		case WADEON_HPD_2:
			tmp = WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HOT_PWUG_DETECTx_INT_POWAWITY;
			ewse
				tmp |= DC_HOT_PWUG_DETECTx_INT_POWAWITY;
			WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW, tmp);
			bweak;
		case WADEON_HPD_3:
			tmp = WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW);
			if (connected)
				tmp &= ~DC_HOT_PWUG_DETECTx_INT_POWAWITY;
			ewse
				tmp |= DC_HOT_PWUG_DETECTx_INT_POWAWITY;
			WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW, tmp);
			bweak;
		defauwt:
			bweak;
		}
	}
}

void w600_hpd_init(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_connectow *connectow;
	unsigned enabwe = 0;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);

		if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP ||
		    connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS) {
			/* don't twy to enabwe hpd on eDP ow WVDS avoid bweaking the
			 * aux dp channew on imac and hewp (but not compwetewy fix)
			 * https://bugziwwa.wedhat.com/show_bug.cgi?id=726143
			 */
			continue;
		}
		if (ASIC_IS_DCE3(wdev)) {
			u32 tmp = DC_HPDx_CONNECTION_TIMEW(0x9c4) | DC_HPDx_WX_INT_TIMEW(0xfa);
			if (ASIC_IS_DCE32(wdev))
				tmp |= DC_HPDx_EN;

			switch (wadeon_connectow->hpd.hpd) {
			case WADEON_HPD_1:
				WWEG32(DC_HPD1_CONTWOW, tmp);
				bweak;
			case WADEON_HPD_2:
				WWEG32(DC_HPD2_CONTWOW, tmp);
				bweak;
			case WADEON_HPD_3:
				WWEG32(DC_HPD3_CONTWOW, tmp);
				bweak;
			case WADEON_HPD_4:
				WWEG32(DC_HPD4_CONTWOW, tmp);
				bweak;
				/* DCE 3.2 */
			case WADEON_HPD_5:
				WWEG32(DC_HPD5_CONTWOW, tmp);
				bweak;
			case WADEON_HPD_6:
				WWEG32(DC_HPD6_CONTWOW, tmp);
				bweak;
			defauwt:
				bweak;
			}
		} ewse {
			switch (wadeon_connectow->hpd.hpd) {
			case WADEON_HPD_1:
				WWEG32(DC_HOT_PWUG_DETECT1_CONTWOW, DC_HOT_PWUG_DETECTx_EN);
				bweak;
			case WADEON_HPD_2:
				WWEG32(DC_HOT_PWUG_DETECT2_CONTWOW, DC_HOT_PWUG_DETECTx_EN);
				bweak;
			case WADEON_HPD_3:
				WWEG32(DC_HOT_PWUG_DETECT3_CONTWOW, DC_HOT_PWUG_DETECTx_EN);
				bweak;
			defauwt:
				bweak;
			}
		}
		if (wadeon_connectow->hpd.hpd != WADEON_HPD_NONE)
			enabwe |= 1 << wadeon_connectow->hpd.hpd;
		wadeon_hpd_set_powawity(wdev, wadeon_connectow->hpd.hpd);
	}
	wadeon_iwq_kms_enabwe_hpd(wdev, enabwe);
}

void w600_hpd_fini(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct dwm_connectow *connectow;
	unsigned disabwe = 0;

	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		stwuct wadeon_connectow *wadeon_connectow = to_wadeon_connectow(connectow);
		if (ASIC_IS_DCE3(wdev)) {
			switch (wadeon_connectow->hpd.hpd) {
			case WADEON_HPD_1:
				WWEG32(DC_HPD1_CONTWOW, 0);
				bweak;
			case WADEON_HPD_2:
				WWEG32(DC_HPD2_CONTWOW, 0);
				bweak;
			case WADEON_HPD_3:
				WWEG32(DC_HPD3_CONTWOW, 0);
				bweak;
			case WADEON_HPD_4:
				WWEG32(DC_HPD4_CONTWOW, 0);
				bweak;
				/* DCE 3.2 */
			case WADEON_HPD_5:
				WWEG32(DC_HPD5_CONTWOW, 0);
				bweak;
			case WADEON_HPD_6:
				WWEG32(DC_HPD6_CONTWOW, 0);
				bweak;
			defauwt:
				bweak;
			}
		} ewse {
			switch (wadeon_connectow->hpd.hpd) {
			case WADEON_HPD_1:
				WWEG32(DC_HOT_PWUG_DETECT1_CONTWOW, 0);
				bweak;
			case WADEON_HPD_2:
				WWEG32(DC_HOT_PWUG_DETECT2_CONTWOW, 0);
				bweak;
			case WADEON_HPD_3:
				WWEG32(DC_HOT_PWUG_DETECT3_CONTWOW, 0);
				bweak;
			defauwt:
				bweak;
			}
		}
		if (wadeon_connectow->hpd.hpd != WADEON_HPD_NONE)
			disabwe |= 1 << wadeon_connectow->hpd.hpd;
	}
	wadeon_iwq_kms_disabwe_hpd(wdev, disabwe);
}

/*
 * W600 PCIE GAWT
 */
void w600_pcie_gawt_twb_fwush(stwuct wadeon_device *wdev)
{
	unsigned i;
	u32 tmp;

	/* fwush hdp cache so updates hit vwam */
	if ((wdev->famiwy >= CHIP_WV770) && (wdev->famiwy <= CHIP_WV740) &&
	    !(wdev->fwags & WADEON_IS_AGP)) {
		void __iomem *ptw = (void *)wdev->gawt.ptw;

		/* w7xx hw bug.  wwite to HDP_DEBUG1 fowwowed by fb wead
		 * wathew than wwite to HDP_WEG_COHEWENCY_FWUSH_CNTW
		 * This seems to cause pwobwems on some AGP cawds. Just use the owd
		 * method fow them.
		 */
		WWEG32(HDP_DEBUG1, 0);
		weadw((void __iomem *)ptw);
	} ewse
		WWEG32(W_005480_HDP_MEM_COHEWENCY_FWUSH_CNTW, 0x1);

	WWEG32(VM_CONTEXT0_INVAWIDATION_WOW_ADDW, wdev->mc.gtt_stawt >> 12);
	WWEG32(VM_CONTEXT0_INVAWIDATION_HIGH_ADDW, (wdev->mc.gtt_end - 1) >> 12);
	WWEG32(VM_CONTEXT0_WEQUEST_WESPONSE, WEQUEST_TYPE(1));
	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(VM_CONTEXT0_WEQUEST_WESPONSE);
		tmp = (tmp & WESPONSE_TYPE_MASK) >> WESPONSE_TYPE_SHIFT;
		if (tmp == 2) {
			pw_wawn("[dwm] w600 fwush TWB faiwed\n");
			wetuwn;
		}
		if (tmp) {
			wetuwn;
		}
		udeway(1);
	}
}

int w600_pcie_gawt_init(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->gawt.wobj) {
		WAWN(1, "W600 PCIE GAWT awweady initiawized\n");
		wetuwn 0;
	}
	/* Initiawize common gawt stwuctuwe */
	w = wadeon_gawt_init(wdev);
	if (w)
		wetuwn w;
	wdev->gawt.tabwe_size = wdev->gawt.num_gpu_pages * 8;
	wetuwn wadeon_gawt_tabwe_vwam_awwoc(wdev);
}

static int w600_pcie_gawt_enabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int w, i;

	if (wdev->gawt.wobj == NUWW) {
		dev_eww(wdev->dev, "No VWAM object fow PCIE GAWT.\n");
		wetuwn -EINVAW;
	}
	w = wadeon_gawt_tabwe_vwam_pin(wdev);
	if (w)
		wetuwn w;

	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_CACHE | ENABWE_W2_FWAGMENT_PWOCESSING |
				ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE |
				EFFECTIVE_W2_QUEUE_SIZE(7));
	WWEG32(VM_W2_CNTW2, 0);
	WWEG32(VM_W2_CNTW3, BANK_SEWECT_0(0) | BANK_SEWECT_1(1));
	/* Setup TWB contwow */
	tmp = ENABWE_W1_TWB | ENABWE_W1_FWAGMENT_PWOCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		EFFECTIVE_W1_TWB_SIZE(5) | EFFECTIVE_W1_QUEUE_SIZE(5) |
		ENABWE_WAIT_W2_QUEWY;
	WWEG32(MC_VM_W1_TWB_MCB_WD_SYS_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_SYS_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_HDP_CNTW, tmp | ENABWE_W1_STWICT_OWDEWING);
	WWEG32(MC_VM_W1_TWB_MCB_WW_HDP_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WD_A_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WW_A_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WD_B_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WW_B_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_GFX_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_GFX_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_PDMA_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_PDMA_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_UVD_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_UVD_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_SEM_CNTW, tmp | ENABWE_SEMAPHOWE_MODE);
	WWEG32(MC_VM_W1_TWB_MCB_WW_SEM_CNTW, tmp | ENABWE_SEMAPHOWE_MODE);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW, wdev->mc.gtt_stawt >> 12);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_END_ADDW, wdev->mc.gtt_end >> 12);
	WWEG32(VM_CONTEXT0_PAGE_TABWE_BASE_ADDW, wdev->gawt.tabwe_addw >> 12);
	WWEG32(VM_CONTEXT0_CNTW, ENABWE_CONTEXT | PAGE_TABWE_DEPTH(0) |
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT);
	WWEG32(VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW,
			(u32)(wdev->dummy_page.addw >> 12));
	fow (i = 1; i < 7; i++)
		WWEG32(VM_CONTEXT0_CNTW + (i * 4), 0);

	w600_pcie_gawt_twb_fwush(wdev);
	DWM_INFO("PCIE GAWT of %uM enabwed (tabwe at 0x%016wwX).\n",
		 (unsigned)(wdev->mc.gtt_size >> 20),
		 (unsigned wong wong)wdev->gawt.tabwe_addw);
	wdev->gawt.weady = twue;
	wetuwn 0;
}

static void w600_pcie_gawt_disabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int i;

	/* Disabwe aww tabwes */
	fow (i = 0; i < 7; i++)
		WWEG32(VM_CONTEXT0_CNTW + (i * 4), 0);

	/* Disabwe W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_FWAGMENT_PWOCESSING |
				EFFECTIVE_W2_QUEUE_SIZE(7));
	WWEG32(VM_W2_CNTW3, BANK_SEWECT_0(0) | BANK_SEWECT_1(1));
	/* Setup W1 TWB contwow */
	tmp = EFFECTIVE_W1_TWB_SIZE(5) | EFFECTIVE_W1_QUEUE_SIZE(5) |
		ENABWE_WAIT_W2_QUEWY;
	WWEG32(MC_VM_W1_TWB_MCD_WD_A_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WW_A_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WD_B_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WW_B_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_GFX_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_GFX_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_PDMA_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_PDMA_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_SEM_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_SEM_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_SYS_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_SYS_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_HDP_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_HDP_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_UVD_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_UVD_CNTW, tmp);
	wadeon_gawt_tabwe_vwam_unpin(wdev);
}

static void w600_pcie_gawt_fini(stwuct wadeon_device *wdev)
{
	wadeon_gawt_fini(wdev);
	w600_pcie_gawt_disabwe(wdev);
	wadeon_gawt_tabwe_vwam_fwee(wdev);
}

static void w600_agp_enabwe(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int i;

	/* Setup W2 cache */
	WWEG32(VM_W2_CNTW, ENABWE_W2_CACHE | ENABWE_W2_FWAGMENT_PWOCESSING |
				ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE |
				EFFECTIVE_W2_QUEUE_SIZE(7));
	WWEG32(VM_W2_CNTW2, 0);
	WWEG32(VM_W2_CNTW3, BANK_SEWECT_0(0) | BANK_SEWECT_1(1));
	/* Setup TWB contwow */
	tmp = ENABWE_W1_TWB | ENABWE_W1_FWAGMENT_PWOCESSING |
		SYSTEM_ACCESS_MODE_NOT_IN_SYS |
		EFFECTIVE_W1_TWB_SIZE(5) | EFFECTIVE_W1_QUEUE_SIZE(5) |
		ENABWE_WAIT_W2_QUEWY;
	WWEG32(MC_VM_W1_TWB_MCB_WD_SYS_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_SYS_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_HDP_CNTW, tmp | ENABWE_W1_STWICT_OWDEWING);
	WWEG32(MC_VM_W1_TWB_MCB_WW_HDP_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WD_A_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WW_A_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WD_B_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCD_WW_B_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_GFX_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_GFX_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_PDMA_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WW_PDMA_CNTW, tmp);
	WWEG32(MC_VM_W1_TWB_MCB_WD_SEM_CNTW, tmp | ENABWE_SEMAPHOWE_MODE);
	WWEG32(MC_VM_W1_TWB_MCB_WW_SEM_CNTW, tmp | ENABWE_SEMAPHOWE_MODE);
	fow (i = 0; i < 7; i++)
		WWEG32(VM_CONTEXT0_CNTW + (i * 4), 0);
}

int w600_mc_wait_fow_idwe(stwuct wadeon_device *wdev)
{
	unsigned i;
	u32 tmp;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		/* wead MC_STATUS */
		tmp = WWEG32(W_000E50_SWBM_STATUS) & 0x3F00;
		if (!tmp)
			wetuwn 0;
		udeway(1);
	}
	wetuwn -1;
}

uint32_t ws780_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg)
{
	unsigned wong fwags;
	uint32_t w;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(W_0028F8_MC_INDEX, S_0028F8_MC_IND_ADDW(weg));
	w = WWEG32(W_0028FC_MC_DATA);
	WWEG32(W_0028F8_MC_INDEX, ~C_0028F8_MC_IND_ADDW);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
	wetuwn w;
}

void ws780_mc_wweg(stwuct wadeon_device *wdev, uint32_t weg, uint32_t v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->mc_idx_wock, fwags);
	WWEG32(W_0028F8_MC_INDEX, S_0028F8_MC_IND_ADDW(weg) |
		S_0028F8_MC_IND_WW_EN(1));
	WWEG32(W_0028FC_MC_DATA, v);
	WWEG32(W_0028F8_MC_INDEX, 0x7F);
	spin_unwock_iwqwestowe(&wdev->mc_idx_wock, fwags);
}

static void w600_mc_pwogwam(stwuct wadeon_device *wdev)
{
	stwuct wv515_mc_save save;
	u32 tmp;
	int i, j;

	/* Initiawize HDP */
	fow (i = 0, j = 0; i < 32; i++, j += 0x18) {
		WWEG32((0x2c14 + j), 0x00000000);
		WWEG32((0x2c18 + j), 0x00000000);
		WWEG32((0x2c1c + j), 0x00000000);
		WWEG32((0x2c20 + j), 0x00000000);
		WWEG32((0x2c24 + j), 0x00000000);
	}
	WWEG32(HDP_WEG_COHEWENCY_FWUSH_CNTW, 0);

	wv515_mc_stop(wdev, &save);
	if (w600_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}
	/* Wockout access thwough VGA apewtuwe (doesn't exist befowe W600) */
	WWEG32(VGA_HDP_CONTWOW, VGA_MEMOWY_DISABWE);
	/* Update configuwation */
	if (wdev->fwags & WADEON_IS_AGP) {
		if (wdev->mc.vwam_stawt < wdev->mc.gtt_stawt) {
			/* VWAM befowe AGP */
			WWEG32(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
				wdev->mc.vwam_stawt >> 12);
			WWEG32(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
				wdev->mc.gtt_end >> 12);
		} ewse {
			/* VWAM aftew AGP */
			WWEG32(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
				wdev->mc.gtt_stawt >> 12);
			WWEG32(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
				wdev->mc.vwam_end >> 12);
		}
	} ewse {
		WWEG32(MC_VM_SYSTEM_APEWTUWE_WOW_ADDW, wdev->mc.vwam_stawt >> 12);
		WWEG32(MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, wdev->mc.vwam_end >> 12);
	}
	WWEG32(MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW, wdev->vwam_scwatch.gpu_addw >> 12);
	tmp = ((wdev->mc.vwam_end >> 24) & 0xFFFF) << 16;
	tmp |= ((wdev->mc.vwam_stawt >> 24) & 0xFFFF);
	WWEG32(MC_VM_FB_WOCATION, tmp);
	WWEG32(HDP_NONSUWFACE_BASE, (wdev->mc.vwam_stawt >> 8));
	WWEG32(HDP_NONSUWFACE_INFO, (2 << 7));
	WWEG32(HDP_NONSUWFACE_SIZE, 0x3FFFFFFF);
	if (wdev->fwags & WADEON_IS_AGP) {
		WWEG32(MC_VM_AGP_TOP, wdev->mc.gtt_end >> 22);
		WWEG32(MC_VM_AGP_BOT, wdev->mc.gtt_stawt >> 22);
		WWEG32(MC_VM_AGP_BASE, wdev->mc.agp_base >> 22);
	} ewse {
		WWEG32(MC_VM_AGP_BASE, 0);
		WWEG32(MC_VM_AGP_TOP, 0x0FFFFFFF);
		WWEG32(MC_VM_AGP_BOT, 0x0FFFFFFF);
	}
	if (w600_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}
	wv515_mc_wesume(wdev, &save);
	/* we need to own VWAM, so tuwn off the VGA wendewew hewe
	 * to stop it ovewwwiting ouw objects */
	wv515_vga_wendew_disabwe(wdev);
}

/**
 * w600_vwam_gtt_wocation - twy to find VWAM & GTT wocation
 * @wdev: wadeon device stwuctuwe howding aww necessawy infowmations
 * @mc: memowy contwowwew stwuctuwe howding memowy infowmations
 *
 * Function wiww pwace twy to pwace VWAM at same pwace as in CPU (PCI)
 * addwess space as some GPU seems to have issue when we wepwogwam at
 * diffewent addwess space.
 *
 * If thewe is not enough space to fit the unvisibwe VWAM aftew the
 * apewtuwe then we wimit the VWAM size to the apewtuwe.
 *
 * If we awe using AGP then pwace VWAM adjacent to AGP apewtuwe awe we need
 * them to be in one fwom GPU point of view so that we can pwogwam GPU to
 * catch access outside them (weiwd GPU powicy see ??).
 *
 * This function wiww nevew faiws, wowst case awe wimiting VWAM ow GTT.
 *
 * Note: GTT stawt, end, size shouwd be initiawized befowe cawwing this
 * function on AGP pwatfowm.
 */
static void w600_vwam_gtt_wocation(stwuct wadeon_device *wdev, stwuct wadeon_mc *mc)
{
	u64 size_bf, size_af;

	if (mc->mc_vwam_size > 0xE0000000) {
		/* weave woom fow at weast 512M GTT */
		dev_wawn(wdev->dev, "wimiting VWAM\n");
		mc->weaw_vwam_size = 0xE0000000;
		mc->mc_vwam_size = 0xE0000000;
	}
	if (wdev->fwags & WADEON_IS_AGP) {
		size_bf = mc->gtt_stawt;
		size_af = mc->mc_mask - mc->gtt_end;
		if (size_bf > size_af) {
			if (mc->mc_vwam_size > size_bf) {
				dev_wawn(wdev->dev, "wimiting VWAM\n");
				mc->weaw_vwam_size = size_bf;
				mc->mc_vwam_size = size_bf;
			}
			mc->vwam_stawt = mc->gtt_stawt - mc->mc_vwam_size;
		} ewse {
			if (mc->mc_vwam_size > size_af) {
				dev_wawn(wdev->dev, "wimiting VWAM\n");
				mc->weaw_vwam_size = size_af;
				mc->mc_vwam_size = size_af;
			}
			mc->vwam_stawt = mc->gtt_end + 1;
		}
		mc->vwam_end = mc->vwam_stawt + mc->mc_vwam_size - 1;
		dev_info(wdev->dev, "VWAM: %wwuM 0x%08wwX - 0x%08wwX (%wwuM used)\n",
				mc->mc_vwam_size >> 20, mc->vwam_stawt,
				mc->vwam_end, mc->weaw_vwam_size >> 20);
	} ewse {
		u64 base = 0;
		if (wdev->fwags & WADEON_IS_IGP) {
			base = WWEG32(MC_VM_FB_WOCATION) & 0xFFFF;
			base <<= 24;
		}
		wadeon_vwam_wocation(wdev, &wdev->mc, base);
		wdev->mc.gtt_base_awign = 0;
		wadeon_gtt_wocation(wdev, mc);
	}
}

static int w600_mc_init(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int chansize, numchan;
	uint32_t h_addw, w_addw;
	unsigned wong wong k8_addw;

	/* Get VWAM infowmations */
	wdev->mc.vwam_is_ddw = twue;
	tmp = WWEG32(WAMCFG);
	if (tmp & CHANSIZE_OVEWWIDE) {
		chansize = 16;
	} ewse if (tmp & CHANSIZE_MASK) {
		chansize = 64;
	} ewse {
		chansize = 32;
	}
	tmp = WWEG32(CHMAP);
	switch ((tmp & NOOFCHAN_MASK) >> NOOFCHAN_SHIFT) {
	case 0:
	defauwt:
		numchan = 1;
		bweak;
	case 1:
		numchan = 2;
		bweak;
	case 2:
		numchan = 4;
		bweak;
	case 3:
		numchan = 8;
		bweak;
	}
	wdev->mc.vwam_width = numchan * chansize;
	/* Couwd apew size wepowt 0 ? */
	wdev->mc.apew_base = pci_wesouwce_stawt(wdev->pdev, 0);
	wdev->mc.apew_size = pci_wesouwce_wen(wdev->pdev, 0);
	/* Setup GPU memowy space */
	wdev->mc.mc_vwam_size = WWEG32(CONFIG_MEMSIZE);
	wdev->mc.weaw_vwam_size = WWEG32(CONFIG_MEMSIZE);
	wdev->mc.visibwe_vwam_size = wdev->mc.apew_size;
	w600_vwam_gtt_wocation(wdev, &wdev->mc);

	if (wdev->fwags & WADEON_IS_IGP) {
		ws690_pm_info(wdev);
		wdev->mc.igp_sidepowt_enabwed = wadeon_atombios_sidepowt_pwesent(wdev);

		if (wdev->famiwy == CHIP_WS780 || wdev->famiwy == CHIP_WS880) {
			/* Use K8 diwect mapping fow fast fb access. */
			wdev->fastfb_wowking = fawse;
			h_addw = G_000012_K8_ADDW_EXT(WWEG32_MC(W_000012_MC_MISC_UMA_CNTW));
			w_addw = WWEG32_MC(W_000011_K8_FB_WOCATION);
			k8_addw = ((unsigned wong wong)h_addw) << 32 | w_addw;
#if defined(CONFIG_X86_32) && !defined(CONFIG_X86_PAE)
			if (k8_addw + wdev->mc.visibwe_vwam_size < 0x100000000UWW)
#endif
			{
				/* FastFB shaww be used with UMA memowy. Hewe it is simpwy disabwed when sidepowt
		 		* memowy is pwesent.
		 		*/
				if (wdev->mc.igp_sidepowt_enabwed == fawse && wadeon_fastfb == 1) {
					DWM_INFO("Diwect mapping: apew base at 0x%wwx, wepwaced by diwect mapping base 0x%wwx.\n",
						(unsigned wong wong)wdev->mc.apew_base, k8_addw);
					wdev->mc.apew_base = (wesouwce_size_t)k8_addw;
					wdev->fastfb_wowking = twue;
				}
			}
		}
	}

	wadeon_update_bandwidth_info(wdev);
	wetuwn 0;
}

int w600_vwam_scwatch_init(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->vwam_scwatch.wobj == NUWW) {
		w = wadeon_bo_cweate(wdev, WADEON_GPU_PAGE_SIZE,
				     PAGE_SIZE, twue, WADEON_GEM_DOMAIN_VWAM,
				     0, NUWW, NUWW, &wdev->vwam_scwatch.wobj);
		if (w) {
			wetuwn w;
		}
	}

	w = wadeon_bo_wesewve(wdev->vwam_scwatch.wobj, fawse);
	if (unwikewy(w != 0))
		wetuwn w;
	w = wadeon_bo_pin(wdev->vwam_scwatch.wobj,
			  WADEON_GEM_DOMAIN_VWAM, &wdev->vwam_scwatch.gpu_addw);
	if (w) {
		wadeon_bo_unwesewve(wdev->vwam_scwatch.wobj);
		wetuwn w;
	}
	w = wadeon_bo_kmap(wdev->vwam_scwatch.wobj,
				(void **)&wdev->vwam_scwatch.ptw);
	if (w)
		wadeon_bo_unpin(wdev->vwam_scwatch.wobj);
	wadeon_bo_unwesewve(wdev->vwam_scwatch.wobj);

	wetuwn w;
}

void w600_vwam_scwatch_fini(stwuct wadeon_device *wdev)
{
	int w;

	if (wdev->vwam_scwatch.wobj == NUWW) {
		wetuwn;
	}
	w = wadeon_bo_wesewve(wdev->vwam_scwatch.wobj, fawse);
	if (wikewy(w == 0)) {
		wadeon_bo_kunmap(wdev->vwam_scwatch.wobj);
		wadeon_bo_unpin(wdev->vwam_scwatch.wobj);
		wadeon_bo_unwesewve(wdev->vwam_scwatch.wobj);
	}
	wadeon_bo_unwef(&wdev->vwam_scwatch.wobj);
}

void w600_set_bios_scwatch_engine_hung(stwuct wadeon_device *wdev, boow hung)
{
	u32 tmp = WWEG32(W600_BIOS_3_SCWATCH);

	if (hung)
		tmp |= ATOM_S3_ASIC_GUI_ENGINE_HUNG;
	ewse
		tmp &= ~ATOM_S3_ASIC_GUI_ENGINE_HUNG;

	WWEG32(W600_BIOS_3_SCWATCH, tmp);
}

static void w600_pwint_gpu_status_wegs(stwuct wadeon_device *wdev)
{
	dev_info(wdev->dev, "  W_008010_GWBM_STATUS      = 0x%08X\n",
		 WWEG32(W_008010_GWBM_STATUS));
	dev_info(wdev->dev, "  W_008014_GWBM_STATUS2     = 0x%08X\n",
		 WWEG32(W_008014_GWBM_STATUS2));
	dev_info(wdev->dev, "  W_000E50_SWBM_STATUS      = 0x%08X\n",
		 WWEG32(W_000E50_SWBM_STATUS));
	dev_info(wdev->dev, "  W_008674_CP_STAWWED_STAT1 = 0x%08X\n",
		 WWEG32(CP_STAWWED_STAT1));
	dev_info(wdev->dev, "  W_008678_CP_STAWWED_STAT2 = 0x%08X\n",
		 WWEG32(CP_STAWWED_STAT2));
	dev_info(wdev->dev, "  W_00867C_CP_BUSY_STAT     = 0x%08X\n",
		 WWEG32(CP_BUSY_STAT));
	dev_info(wdev->dev, "  W_008680_CP_STAT          = 0x%08X\n",
		 WWEG32(CP_STAT));
	dev_info(wdev->dev, "  W_00D034_DMA_STATUS_WEG   = 0x%08X\n",
		WWEG32(DMA_STATUS_WEG));
}

static boow w600_is_dispway_hung(stwuct wadeon_device *wdev)
{
	u32 cwtc_hung = 0;
	u32 cwtc_status[2];
	u32 i, j, tmp;

	fow (i = 0; i < wdev->num_cwtc; i++) {
		if (WWEG32(AVIVO_D1CWTC_CONTWOW + cwtc_offsets[i]) & AVIVO_CWTC_EN) {
			cwtc_status[i] = WWEG32(AVIVO_D1CWTC_STATUS_HV_COUNT + cwtc_offsets[i]);
			cwtc_hung |= (1 << i);
		}
	}

	fow (j = 0; j < 10; j++) {
		fow (i = 0; i < wdev->num_cwtc; i++) {
			if (cwtc_hung & (1 << i)) {
				tmp = WWEG32(AVIVO_D1CWTC_STATUS_HV_COUNT + cwtc_offsets[i]);
				if (tmp != cwtc_status[i])
					cwtc_hung &= ~(1 << i);
			}
		}
		if (cwtc_hung == 0)
			wetuwn fawse;
		udeway(100);
	}

	wetuwn twue;
}

u32 w600_gpu_check_soft_weset(stwuct wadeon_device *wdev)
{
	u32 weset_mask = 0;
	u32 tmp;

	/* GWBM_STATUS */
	tmp = WWEG32(W_008010_GWBM_STATUS);
	if (wdev->famiwy >= CHIP_WV770) {
		if (G_008010_PA_BUSY(tmp) | G_008010_SC_BUSY(tmp) |
		    G_008010_SH_BUSY(tmp) | G_008010_SX_BUSY(tmp) |
		    G_008010_TA_BUSY(tmp) | G_008010_VGT_BUSY(tmp) |
		    G_008010_DB03_BUSY(tmp) | G_008010_CB03_BUSY(tmp) |
		    G_008010_SPI03_BUSY(tmp) | G_008010_VGT_BUSY_NO_DMA(tmp))
			weset_mask |= WADEON_WESET_GFX;
	} ewse {
		if (G_008010_PA_BUSY(tmp) | G_008010_SC_BUSY(tmp) |
		    G_008010_SH_BUSY(tmp) | G_008010_SX_BUSY(tmp) |
		    G_008010_TA03_BUSY(tmp) | G_008010_VGT_BUSY(tmp) |
		    G_008010_DB03_BUSY(tmp) | G_008010_CB03_BUSY(tmp) |
		    G_008010_SPI03_BUSY(tmp) | G_008010_VGT_BUSY_NO_DMA(tmp))
			weset_mask |= WADEON_WESET_GFX;
	}

	if (G_008010_CF_WQ_PENDING(tmp) | G_008010_PF_WQ_PENDING(tmp) |
	    G_008010_CP_BUSY(tmp) | G_008010_CP_COHEWENCY_BUSY(tmp))
		weset_mask |= WADEON_WESET_CP;

	if (G_008010_GWBM_EE_BUSY(tmp))
		weset_mask |= WADEON_WESET_GWBM | WADEON_WESET_GFX | WADEON_WESET_CP;

	/* DMA_STATUS_WEG */
	tmp = WWEG32(DMA_STATUS_WEG);
	if (!(tmp & DMA_IDWE))
		weset_mask |= WADEON_WESET_DMA;

	/* SWBM_STATUS */
	tmp = WWEG32(W_000E50_SWBM_STATUS);
	if (G_000E50_WWC_WQ_PENDING(tmp) | G_000E50_WWC_BUSY(tmp))
		weset_mask |= WADEON_WESET_WWC;

	if (G_000E50_IH_BUSY(tmp))
		weset_mask |= WADEON_WESET_IH;

	if (G_000E50_SEM_BUSY(tmp))
		weset_mask |= WADEON_WESET_SEM;

	if (G_000E50_GWBM_WQ_PENDING(tmp))
		weset_mask |= WADEON_WESET_GWBM;

	if (G_000E50_VMC_BUSY(tmp))
		weset_mask |= WADEON_WESET_VMC;

	if (G_000E50_MCB_BUSY(tmp) | G_000E50_MCDZ_BUSY(tmp) |
	    G_000E50_MCDY_BUSY(tmp) | G_000E50_MCDX_BUSY(tmp) |
	    G_000E50_MCDW_BUSY(tmp))
		weset_mask |= WADEON_WESET_MC;

	if (w600_is_dispway_hung(wdev))
		weset_mask |= WADEON_WESET_DISPWAY;

	/* Skip MC weset as it's mostwy wikewy not hung, just busy */
	if (weset_mask & WADEON_WESET_MC) {
		DWM_DEBUG("MC busy: 0x%08X, cweawing.\n", weset_mask);
		weset_mask &= ~WADEON_WESET_MC;
	}

	wetuwn weset_mask;
}

static void w600_gpu_soft_weset(stwuct wadeon_device *wdev, u32 weset_mask)
{
	stwuct wv515_mc_save save;
	u32 gwbm_soft_weset = 0, swbm_soft_weset = 0;
	u32 tmp;

	if (weset_mask == 0)
		wetuwn;

	dev_info(wdev->dev, "GPU softweset: 0x%08X\n", weset_mask);

	w600_pwint_gpu_status_wegs(wdev);

	/* Disabwe CP pawsing/pwefetching */
	if (wdev->famiwy >= CHIP_WV770)
		WWEG32(W_0086D8_CP_ME_CNTW, S_0086D8_CP_ME_HAWT(1) | S_0086D8_CP_PFP_HAWT(1));
	ewse
		WWEG32(W_0086D8_CP_ME_CNTW, S_0086D8_CP_ME_HAWT(1));

	/* disabwe the WWC */
	WWEG32(WWC_CNTW, 0);

	if (weset_mask & WADEON_WESET_DMA) {
		/* Disabwe DMA */
		tmp = WWEG32(DMA_WB_CNTW);
		tmp &= ~DMA_WB_ENABWE;
		WWEG32(DMA_WB_CNTW, tmp);
	}

	mdeway(50);

	wv515_mc_stop(wdev, &save);
	if (w600_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}

	if (weset_mask & (WADEON_WESET_GFX | WADEON_WESET_COMPUTE)) {
		if (wdev->famiwy >= CHIP_WV770)
			gwbm_soft_weset |= S_008020_SOFT_WESET_DB(1) |
				S_008020_SOFT_WESET_CB(1) |
				S_008020_SOFT_WESET_PA(1) |
				S_008020_SOFT_WESET_SC(1) |
				S_008020_SOFT_WESET_SPI(1) |
				S_008020_SOFT_WESET_SX(1) |
				S_008020_SOFT_WESET_SH(1) |
				S_008020_SOFT_WESET_TC(1) |
				S_008020_SOFT_WESET_TA(1) |
				S_008020_SOFT_WESET_VC(1) |
				S_008020_SOFT_WESET_VGT(1);
		ewse
			gwbm_soft_weset |= S_008020_SOFT_WESET_CW(1) |
				S_008020_SOFT_WESET_DB(1) |
				S_008020_SOFT_WESET_CB(1) |
				S_008020_SOFT_WESET_PA(1) |
				S_008020_SOFT_WESET_SC(1) |
				S_008020_SOFT_WESET_SMX(1) |
				S_008020_SOFT_WESET_SPI(1) |
				S_008020_SOFT_WESET_SX(1) |
				S_008020_SOFT_WESET_SH(1) |
				S_008020_SOFT_WESET_TC(1) |
				S_008020_SOFT_WESET_TA(1) |
				S_008020_SOFT_WESET_VC(1) |
				S_008020_SOFT_WESET_VGT(1);
	}

	if (weset_mask & WADEON_WESET_CP) {
		gwbm_soft_weset |= S_008020_SOFT_WESET_CP(1) |
			S_008020_SOFT_WESET_VGT(1);

		swbm_soft_weset |= S_000E60_SOFT_WESET_GWBM(1);
	}

	if (weset_mask & WADEON_WESET_DMA) {
		if (wdev->famiwy >= CHIP_WV770)
			swbm_soft_weset |= WV770_SOFT_WESET_DMA;
		ewse
			swbm_soft_weset |= SOFT_WESET_DMA;
	}

	if (weset_mask & WADEON_WESET_WWC)
		swbm_soft_weset |= S_000E60_SOFT_WESET_WWC(1);

	if (weset_mask & WADEON_WESET_SEM)
		swbm_soft_weset |= S_000E60_SOFT_WESET_SEM(1);

	if (weset_mask & WADEON_WESET_IH)
		swbm_soft_weset |= S_000E60_SOFT_WESET_IH(1);

	if (weset_mask & WADEON_WESET_GWBM)
		swbm_soft_weset |= S_000E60_SOFT_WESET_GWBM(1);

	if (!(wdev->fwags & WADEON_IS_IGP)) {
		if (weset_mask & WADEON_WESET_MC)
			swbm_soft_weset |= S_000E60_SOFT_WESET_MC(1);
	}

	if (weset_mask & WADEON_WESET_VMC)
		swbm_soft_weset |= S_000E60_SOFT_WESET_VMC(1);

	if (gwbm_soft_weset) {
		tmp = WWEG32(W_008020_GWBM_SOFT_WESET);
		tmp |= gwbm_soft_weset;
		dev_info(wdev->dev, "W_008020_GWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(W_008020_GWBM_SOFT_WESET, tmp);
		tmp = WWEG32(W_008020_GWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~gwbm_soft_weset;
		WWEG32(W_008020_GWBM_SOFT_WESET, tmp);
		tmp = WWEG32(W_008020_GWBM_SOFT_WESET);
	}

	if (swbm_soft_weset) {
		tmp = WWEG32(SWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(wdev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(SWBM_SOFT_WESET, tmp);
		tmp = WWEG32(SWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(SWBM_SOFT_WESET, tmp);
		tmp = WWEG32(SWBM_SOFT_WESET);
	}

	/* Wait a wittwe fow things to settwe down */
	mdeway(1);

	wv515_mc_wesume(wdev, &save);
	udeway(50);

	w600_pwint_gpu_status_wegs(wdev);
}

static void w600_gpu_pci_config_weset(stwuct wadeon_device *wdev)
{
	stwuct wv515_mc_save save;
	u32 tmp, i;

	dev_info(wdev->dev, "GPU pci config weset\n");

	/* disabwe dpm? */

	/* Disabwe CP pawsing/pwefetching */
	if (wdev->famiwy >= CHIP_WV770)
		WWEG32(W_0086D8_CP_ME_CNTW, S_0086D8_CP_ME_HAWT(1) | S_0086D8_CP_PFP_HAWT(1));
	ewse
		WWEG32(W_0086D8_CP_ME_CNTW, S_0086D8_CP_ME_HAWT(1));

	/* disabwe the WWC */
	WWEG32(WWC_CNTW, 0);

	/* Disabwe DMA */
	tmp = WWEG32(DMA_WB_CNTW);
	tmp &= ~DMA_WB_ENABWE;
	WWEG32(DMA_WB_CNTW, tmp);

	mdeway(50);

	/* set mcwk/scwk to bypass */
	if (wdev->famiwy >= CHIP_WV770)
		wv770_set_cwk_bypass_mode(wdev);
	/* disabwe BM */
	pci_cweaw_mastew(wdev->pdev);
	/* disabwe mem access */
	wv515_mc_stop(wdev, &save);
	if (w600_mc_wait_fow_idwe(wdev)) {
		dev_wawn(wdev->dev, "Wait fow MC idwe timedout !\n");
	}

	/* BIF weset wowkawound.  Not suwe if this is needed on 6xx */
	tmp = WWEG32(BUS_CNTW);
	tmp |= VGA_COHE_SPEC_TIMEW_DIS;
	WWEG32(BUS_CNTW, tmp);

	tmp = WWEG32(BIF_SCWATCH0);

	/* weset */
	wadeon_pci_config_weset(wdev);
	mdeway(1);

	/* BIF weset wowkawound.  Not suwe if this is needed on 6xx */
	tmp = SOFT_WESET_BIF;
	WWEG32(SWBM_SOFT_WESET, tmp);
	mdeway(1);
	WWEG32(SWBM_SOFT_WESET, 0);

	/* wait fow asic to come out of weset */
	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(CONFIG_MEMSIZE) != 0xffffffff)
			bweak;
		udeway(1);
	}
}

int w600_asic_weset(stwuct wadeon_device *wdev, boow hawd)
{
	u32 weset_mask;

	if (hawd) {
		w600_gpu_pci_config_weset(wdev);
		wetuwn 0;
	}

	weset_mask = w600_gpu_check_soft_weset(wdev);

	if (weset_mask)
		w600_set_bios_scwatch_engine_hung(wdev, twue);

	/* twy soft weset */
	w600_gpu_soft_weset(wdev, weset_mask);

	weset_mask = w600_gpu_check_soft_weset(wdev);

	/* twy pci config weset */
	if (weset_mask && wadeon_hawd_weset)
		w600_gpu_pci_config_weset(wdev);

	weset_mask = w600_gpu_check_soft_weset(wdev);

	if (!weset_mask)
		w600_set_bios_scwatch_engine_hung(wdev, fawse);

	wetuwn 0;
}

/**
 * w600_gfx_is_wockup - Check if the GFX engine is wocked up
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing stwuctuwe howding wing infowmation
 *
 * Check if the GFX engine is wocked up.
 * Wetuwns twue if the engine appeaws to be wocked up, fawse if not.
 */
boow w600_gfx_is_wockup(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	u32 weset_mask = w600_gpu_check_soft_weset(wdev);

	if (!(weset_mask & (WADEON_WESET_GFX |
			    WADEON_WESET_COMPUTE |
			    WADEON_WESET_CP))) {
		wadeon_wing_wockup_update(wdev, wing);
		wetuwn fawse;
	}
	wetuwn wadeon_wing_test_wockup(wdev, wing);
}

u32 w6xx_wemap_wendew_backend(stwuct wadeon_device *wdev,
			      u32 tiwing_pipe_num,
			      u32 max_wb_num,
			      u32 totaw_max_wb_num,
			      u32 disabwed_wb_mask)
{
	u32 wendewing_pipe_num, wb_num_width, weq_wb_num;
	u32 pipe_wb_watio, pipe_wb_wemain, tmp;
	u32 data = 0, mask = 1 << (max_wb_num - 1);
	unsigned i, j;

	/* mask out the WBs that don't exist on that asic */
	tmp = disabwed_wb_mask | ((0xff << max_wb_num) & 0xff);
	/* make suwe at weast one WB is avaiwabwe */
	if ((tmp & 0xff) != 0xff)
		disabwed_wb_mask = tmp;

	wendewing_pipe_num = 1 << tiwing_pipe_num;
	weq_wb_num = totaw_max_wb_num - w600_count_pipe_bits(disabwed_wb_mask);
	BUG_ON(wendewing_pipe_num < weq_wb_num);

	pipe_wb_watio = wendewing_pipe_num / weq_wb_num;
	pipe_wb_wemain = wendewing_pipe_num - pipe_wb_watio * weq_wb_num;

	if (wdev->famiwy <= CHIP_WV740) {
		/* w6xx/w7xx */
		wb_num_width = 2;
	} ewse {
		/* eg+ */
		wb_num_width = 4;
	}

	fow (i = 0; i < max_wb_num; i++) {
		if (!(mask & disabwed_wb_mask)) {
			fow (j = 0; j < pipe_wb_watio; j++) {
				data <<= wb_num_width;
				data |= max_wb_num - i - 1;
			}
			if (pipe_wb_wemain) {
				data <<= wb_num_width;
				data |= max_wb_num - i - 1;
				pipe_wb_wemain--;
			}
		}
		mask >>= 1;
	}

	wetuwn data;
}

int w600_count_pipe_bits(uint32_t vaw)
{
	wetuwn hweight32(vaw);
}

static void w600_gpu_init(stwuct wadeon_device *wdev)
{
	u32 tiwing_config;
	u32 wamcfg;
	u32 cc_gc_shadew_pipe_config;
	u32 tmp;
	int i, j;
	u32 sq_config;
	u32 sq_gpw_wesouwce_mgmt_1 = 0;
	u32 sq_gpw_wesouwce_mgmt_2 = 0;
	u32 sq_thwead_wesouwce_mgmt = 0;
	u32 sq_stack_wesouwce_mgmt_1 = 0;
	u32 sq_stack_wesouwce_mgmt_2 = 0;
	u32 disabwed_wb_mask;

	wdev->config.w600.tiwing_gwoup_size = 256;
	switch (wdev->famiwy) {
	case CHIP_W600:
		wdev->config.w600.max_pipes = 4;
		wdev->config.w600.max_tiwe_pipes = 8;
		wdev->config.w600.max_simds = 4;
		wdev->config.w600.max_backends = 4;
		wdev->config.w600.max_gpws = 256;
		wdev->config.w600.max_thweads = 192;
		wdev->config.w600.max_stack_entwies = 256;
		wdev->config.w600.max_hw_contexts = 8;
		wdev->config.w600.max_gs_thweads = 16;
		wdev->config.w600.sx_max_expowt_size = 128;
		wdev->config.w600.sx_max_expowt_pos_size = 16;
		wdev->config.w600.sx_max_expowt_smx_size = 128;
		wdev->config.w600.sq_num_cf_insts = 2;
		bweak;
	case CHIP_WV630:
	case CHIP_WV635:
		wdev->config.w600.max_pipes = 2;
		wdev->config.w600.max_tiwe_pipes = 2;
		wdev->config.w600.max_simds = 3;
		wdev->config.w600.max_backends = 1;
		wdev->config.w600.max_gpws = 128;
		wdev->config.w600.max_thweads = 192;
		wdev->config.w600.max_stack_entwies = 128;
		wdev->config.w600.max_hw_contexts = 8;
		wdev->config.w600.max_gs_thweads = 4;
		wdev->config.w600.sx_max_expowt_size = 128;
		wdev->config.w600.sx_max_expowt_pos_size = 16;
		wdev->config.w600.sx_max_expowt_smx_size = 128;
		wdev->config.w600.sq_num_cf_insts = 2;
		bweak;
	case CHIP_WV610:
	case CHIP_WV620:
	case CHIP_WS780:
	case CHIP_WS880:
		wdev->config.w600.max_pipes = 1;
		wdev->config.w600.max_tiwe_pipes = 1;
		wdev->config.w600.max_simds = 2;
		wdev->config.w600.max_backends = 1;
		wdev->config.w600.max_gpws = 128;
		wdev->config.w600.max_thweads = 192;
		wdev->config.w600.max_stack_entwies = 128;
		wdev->config.w600.max_hw_contexts = 4;
		wdev->config.w600.max_gs_thweads = 4;
		wdev->config.w600.sx_max_expowt_size = 128;
		wdev->config.w600.sx_max_expowt_pos_size = 16;
		wdev->config.w600.sx_max_expowt_smx_size = 128;
		wdev->config.w600.sq_num_cf_insts = 1;
		bweak;
	case CHIP_WV670:
		wdev->config.w600.max_pipes = 4;
		wdev->config.w600.max_tiwe_pipes = 4;
		wdev->config.w600.max_simds = 4;
		wdev->config.w600.max_backends = 4;
		wdev->config.w600.max_gpws = 192;
		wdev->config.w600.max_thweads = 192;
		wdev->config.w600.max_stack_entwies = 256;
		wdev->config.w600.max_hw_contexts = 8;
		wdev->config.w600.max_gs_thweads = 16;
		wdev->config.w600.sx_max_expowt_size = 128;
		wdev->config.w600.sx_max_expowt_pos_size = 16;
		wdev->config.w600.sx_max_expowt_smx_size = 128;
		wdev->config.w600.sq_num_cf_insts = 2;
		bweak;
	defauwt:
		bweak;
	}

	/* Initiawize HDP */
	fow (i = 0, j = 0; i < 32; i++, j += 0x18) {
		WWEG32((0x2c14 + j), 0x00000000);
		WWEG32((0x2c18 + j), 0x00000000);
		WWEG32((0x2c1c + j), 0x00000000);
		WWEG32((0x2c20 + j), 0x00000000);
		WWEG32((0x2c24 + j), 0x00000000);
	}

	WWEG32(GWBM_CNTW, GWBM_WEAD_TIMEOUT(0xff));

	/* Setup tiwing */
	tiwing_config = 0;
	wamcfg = WWEG32(WAMCFG);
	switch (wdev->config.w600.max_tiwe_pipes) {
	case 1:
		tiwing_config |= PIPE_TIWING(0);
		bweak;
	case 2:
		tiwing_config |= PIPE_TIWING(1);
		bweak;
	case 4:
		tiwing_config |= PIPE_TIWING(2);
		bweak;
	case 8:
		tiwing_config |= PIPE_TIWING(3);
		bweak;
	defauwt:
		bweak;
	}
	wdev->config.w600.tiwing_npipes = wdev->config.w600.max_tiwe_pipes;
	wdev->config.w600.tiwing_nbanks = 4 << ((wamcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT);
	tiwing_config |= BANK_TIWING((wamcfg & NOOFBANK_MASK) >> NOOFBANK_SHIFT);
	tiwing_config |= GWOUP_SIZE((wamcfg & BUWSTWENGTH_MASK) >> BUWSTWENGTH_SHIFT);

	tmp = (wamcfg & NOOFWOWS_MASK) >> NOOFWOWS_SHIFT;
	if (tmp > 3) {
		tiwing_config |= WOW_TIWING(3);
		tiwing_config |= SAMPWE_SPWIT(3);
	} ewse {
		tiwing_config |= WOW_TIWING(tmp);
		tiwing_config |= SAMPWE_SPWIT(tmp);
	}
	tiwing_config |= BANK_SWAPS(1);

	cc_gc_shadew_pipe_config = WWEG32(CC_GC_SHADEW_PIPE_CONFIG) & 0x00ffff00;
	tmp = wdev->config.w600.max_simds -
		w600_count_pipe_bits((cc_gc_shadew_pipe_config >> 16) & W6XX_MAX_SIMDS_MASK);
	wdev->config.w600.active_simds = tmp;

	disabwed_wb_mask = (WWEG32(CC_WB_BACKEND_DISABWE) >> 16) & W6XX_MAX_BACKENDS_MASK;
	tmp = 0;
	fow (i = 0; i < wdev->config.w600.max_backends; i++)
		tmp |= (1 << i);
	/* if aww the backends awe disabwed, fix it up hewe */
	if ((disabwed_wb_mask & tmp) == tmp) {
		fow (i = 0; i < wdev->config.w600.max_backends; i++)
			disabwed_wb_mask &= ~(1 << i);
	}
	tmp = (tiwing_config & PIPE_TIWING__MASK) >> PIPE_TIWING__SHIFT;
	tmp = w6xx_wemap_wendew_backend(wdev, tmp, wdev->config.w600.max_backends,
					W6XX_MAX_BACKENDS, disabwed_wb_mask);
	tiwing_config |= tmp << 16;
	wdev->config.w600.backend_map = tmp;

	wdev->config.w600.tiwe_config = tiwing_config;
	WWEG32(GB_TIWING_CONFIG, tiwing_config);
	WWEG32(DCP_TIWING_CONFIG, tiwing_config & 0xffff);
	WWEG32(HDP_TIWING_CONFIG, tiwing_config & 0xffff);
	WWEG32(DMA_TIWING_CONFIG, tiwing_config & 0xffff);

	tmp = W6XX_MAX_PIPES - w600_count_pipe_bits((cc_gc_shadew_pipe_config & INACTIVE_QD_PIPES_MASK) >> 8);
	WWEG32(VGT_OUT_DEAWWOC_CNTW, (tmp * 4) & DEAWWOC_DIST_MASK);
	WWEG32(VGT_VEWTEX_WEUSE_BWOCK_CNTW, ((tmp * 4) - 2) & VTX_WEUSE_DEPTH_MASK);

	/* Setup some CP states */
	WWEG32(CP_QUEUE_THWESHOWDS, (WOQ_IB1_STAWT(0x16) | WOQ_IB2_STAWT(0x2b)));
	WWEG32(CP_MEQ_THWESHOWDS, (MEQ_END(0x40) | WOQ_END(0x40)));

	WWEG32(TA_CNTW_AUX, (DISABWE_CUBE_ANISO | SYNC_GWADIENT |
			     SYNC_WAWKEW | SYNC_AWIGNEW));
	/* Setup vawious GPU states */
	if (wdev->famiwy == CHIP_WV670)
		WWEG32(AWB_GDEC_WD_CNTW, 0x00000021);

	tmp = WWEG32(SX_DEBUG_1);
	tmp |= SMX_EVENT_WEWEASE;
	if ((wdev->famiwy > CHIP_W600))
		tmp |= ENABWE_NEW_SMX_ADDWESS;
	WWEG32(SX_DEBUG_1, tmp);

	if (((wdev->famiwy) == CHIP_W600) ||
	    ((wdev->famiwy) == CHIP_WV630) ||
	    ((wdev->famiwy) == CHIP_WV610) ||
	    ((wdev->famiwy) == CHIP_WV620) ||
	    ((wdev->famiwy) == CHIP_WS780) ||
	    ((wdev->famiwy) == CHIP_WS880)) {
		WWEG32(DB_DEBUG, PWEZ_MUST_WAIT_FOW_POSTZ_DONE);
	} ewse {
		WWEG32(DB_DEBUG, 0);
	}
	WWEG32(DB_WATEWMAWKS, (DEPTH_FWEE(4) | DEPTH_CACHEWINE_FWEE(16) |
			       DEPTH_FWUSH(16) | DEPTH_PENDING_FWEE(4)));

	WWEG32(PA_SC_MUWTI_CHIP_CNTW, 0);
	WWEG32(VGT_NUM_INSTANCES, 0);

	WWEG32(SPI_CONFIG_CNTW, GPW_WWITE_PWIOWITY(0));
	WWEG32(SPI_CONFIG_CNTW_1, VTX_DONE_DEWAY(0));

	tmp = WWEG32(SQ_MS_FIFO_SIZES);
	if (((wdev->famiwy) == CHIP_WV610) ||
	    ((wdev->famiwy) == CHIP_WV620) ||
	    ((wdev->famiwy) == CHIP_WS780) ||
	    ((wdev->famiwy) == CHIP_WS880)) {
		tmp = (CACHE_FIFO_SIZE(0xa) |
		       FETCH_FIFO_HIWATEW(0xa) |
		       DONE_FIFO_HIWATEW(0xe0) |
		       AWU_UPDATE_FIFO_HIWATEW(0x8));
	} ewse if (((wdev->famiwy) == CHIP_W600) ||
		   ((wdev->famiwy) == CHIP_WV630)) {
		tmp &= ~DONE_FIFO_HIWATEW(0xff);
		tmp |= DONE_FIFO_HIWATEW(0x4);
	}
	WWEG32(SQ_MS_FIFO_SIZES, tmp);

	/* SQ_CONFIG, SQ_GPW_WESOUWCE_MGMT, SQ_THWEAD_WESOUWCE_MGMT, SQ_STACK_WESOUWCE_MGMT
	 * shouwd be adjusted as needed by the 2D/3D dwivews.  This just sets defauwt vawues
	 */
	sq_config = WWEG32(SQ_CONFIG);
	sq_config &= ~(PS_PWIO(3) |
		       VS_PWIO(3) |
		       GS_PWIO(3) |
		       ES_PWIO(3));
	sq_config |= (DX9_CONSTS |
		      VC_ENABWE |
		      PS_PWIO(0) |
		      VS_PWIO(1) |
		      GS_PWIO(2) |
		      ES_PWIO(3));

	if ((wdev->famiwy) == CHIP_W600) {
		sq_gpw_wesouwce_mgmt_1 = (NUM_PS_GPWS(124) |
					  NUM_VS_GPWS(124) |
					  NUM_CWAUSE_TEMP_GPWS(4));
		sq_gpw_wesouwce_mgmt_2 = (NUM_GS_GPWS(0) |
					  NUM_ES_GPWS(0));
		sq_thwead_wesouwce_mgmt = (NUM_PS_THWEADS(136) |
					   NUM_VS_THWEADS(48) |
					   NUM_GS_THWEADS(4) |
					   NUM_ES_THWEADS(4));
		sq_stack_wesouwce_mgmt_1 = (NUM_PS_STACK_ENTWIES(128) |
					    NUM_VS_STACK_ENTWIES(128));
		sq_stack_wesouwce_mgmt_2 = (NUM_GS_STACK_ENTWIES(0) |
					    NUM_ES_STACK_ENTWIES(0));
	} ewse if (((wdev->famiwy) == CHIP_WV610) ||
		   ((wdev->famiwy) == CHIP_WV620) ||
		   ((wdev->famiwy) == CHIP_WS780) ||
		   ((wdev->famiwy) == CHIP_WS880)) {
		/* no vewtex cache */
		sq_config &= ~VC_ENABWE;

		sq_gpw_wesouwce_mgmt_1 = (NUM_PS_GPWS(44) |
					  NUM_VS_GPWS(44) |
					  NUM_CWAUSE_TEMP_GPWS(2));
		sq_gpw_wesouwce_mgmt_2 = (NUM_GS_GPWS(17) |
					  NUM_ES_GPWS(17));
		sq_thwead_wesouwce_mgmt = (NUM_PS_THWEADS(79) |
					   NUM_VS_THWEADS(78) |
					   NUM_GS_THWEADS(4) |
					   NUM_ES_THWEADS(31));
		sq_stack_wesouwce_mgmt_1 = (NUM_PS_STACK_ENTWIES(40) |
					    NUM_VS_STACK_ENTWIES(40));
		sq_stack_wesouwce_mgmt_2 = (NUM_GS_STACK_ENTWIES(32) |
					    NUM_ES_STACK_ENTWIES(16));
	} ewse if (((wdev->famiwy) == CHIP_WV630) ||
		   ((wdev->famiwy) == CHIP_WV635)) {
		sq_gpw_wesouwce_mgmt_1 = (NUM_PS_GPWS(44) |
					  NUM_VS_GPWS(44) |
					  NUM_CWAUSE_TEMP_GPWS(2));
		sq_gpw_wesouwce_mgmt_2 = (NUM_GS_GPWS(18) |
					  NUM_ES_GPWS(18));
		sq_thwead_wesouwce_mgmt = (NUM_PS_THWEADS(79) |
					   NUM_VS_THWEADS(78) |
					   NUM_GS_THWEADS(4) |
					   NUM_ES_THWEADS(31));
		sq_stack_wesouwce_mgmt_1 = (NUM_PS_STACK_ENTWIES(40) |
					    NUM_VS_STACK_ENTWIES(40));
		sq_stack_wesouwce_mgmt_2 = (NUM_GS_STACK_ENTWIES(32) |
					    NUM_ES_STACK_ENTWIES(16));
	} ewse if ((wdev->famiwy) == CHIP_WV670) {
		sq_gpw_wesouwce_mgmt_1 = (NUM_PS_GPWS(44) |
					  NUM_VS_GPWS(44) |
					  NUM_CWAUSE_TEMP_GPWS(2));
		sq_gpw_wesouwce_mgmt_2 = (NUM_GS_GPWS(17) |
					  NUM_ES_GPWS(17));
		sq_thwead_wesouwce_mgmt = (NUM_PS_THWEADS(79) |
					   NUM_VS_THWEADS(78) |
					   NUM_GS_THWEADS(4) |
					   NUM_ES_THWEADS(31));
		sq_stack_wesouwce_mgmt_1 = (NUM_PS_STACK_ENTWIES(64) |
					    NUM_VS_STACK_ENTWIES(64));
		sq_stack_wesouwce_mgmt_2 = (NUM_GS_STACK_ENTWIES(64) |
					    NUM_ES_STACK_ENTWIES(64));
	}

	WWEG32(SQ_CONFIG, sq_config);
	WWEG32(SQ_GPW_WESOUWCE_MGMT_1,  sq_gpw_wesouwce_mgmt_1);
	WWEG32(SQ_GPW_WESOUWCE_MGMT_2,  sq_gpw_wesouwce_mgmt_2);
	WWEG32(SQ_THWEAD_WESOUWCE_MGMT, sq_thwead_wesouwce_mgmt);
	WWEG32(SQ_STACK_WESOUWCE_MGMT_1, sq_stack_wesouwce_mgmt_1);
	WWEG32(SQ_STACK_WESOUWCE_MGMT_2, sq_stack_wesouwce_mgmt_2);

	if (((wdev->famiwy) == CHIP_WV610) ||
	    ((wdev->famiwy) == CHIP_WV620) ||
	    ((wdev->famiwy) == CHIP_WS780) ||
	    ((wdev->famiwy) == CHIP_WS880)) {
		WWEG32(VGT_CACHE_INVAWIDATION, CACHE_INVAWIDATION(TC_ONWY));
	} ewse {
		WWEG32(VGT_CACHE_INVAWIDATION, CACHE_INVAWIDATION(VC_AND_TC));
	}

	/* Mowe defauwt vawues. 2D/3D dwivew shouwd adjust as needed */
	WWEG32(PA_SC_AA_SAMPWE_WOCS_2S, (S0_X(0xc) | S0_Y(0x4) |
					 S1_X(0x4) | S1_Y(0xc)));
	WWEG32(PA_SC_AA_SAMPWE_WOCS_4S, (S0_X(0xe) | S0_Y(0xe) |
					 S1_X(0x2) | S1_Y(0x2) |
					 S2_X(0xa) | S2_Y(0x6) |
					 S3_X(0x6) | S3_Y(0xa)));
	WWEG32(PA_SC_AA_SAMPWE_WOCS_8S_WD0, (S0_X(0xe) | S0_Y(0xb) |
					     S1_X(0x4) | S1_Y(0xc) |
					     S2_X(0x1) | S2_Y(0x6) |
					     S3_X(0xa) | S3_Y(0xe)));
	WWEG32(PA_SC_AA_SAMPWE_WOCS_8S_WD1, (S4_X(0x6) | S4_Y(0x1) |
					     S5_X(0x0) | S5_Y(0x0) |
					     S6_X(0xb) | S6_Y(0x4) |
					     S7_X(0x7) | S7_Y(0x8)));

	WWEG32(VGT_STWMOUT_EN, 0);
	tmp = wdev->config.w600.max_pipes * 16;
	switch (wdev->famiwy) {
	case CHIP_WV610:
	case CHIP_WV620:
	case CHIP_WS780:
	case CHIP_WS880:
		tmp += 32;
		bweak;
	case CHIP_WV670:
		tmp += 128;
		bweak;
	defauwt:
		bweak;
	}
	if (tmp > 256) {
		tmp = 256;
	}
	WWEG32(VGT_ES_PEW_GS, 128);
	WWEG32(VGT_GS_PEW_ES, tmp);
	WWEG32(VGT_GS_PEW_VS, 2);
	WWEG32(VGT_GS_VEWTEX_WEUSE, 16);

	/* mowe defauwt vawues. 2D/3D dwivew shouwd adjust as needed */
	WWEG32(PA_SC_WINE_STIPPWE_STATE, 0);
	WWEG32(VGT_STWMOUT_EN, 0);
	WWEG32(SX_MISC, 0);
	WWEG32(PA_SC_MODE_CNTW, 0);
	WWEG32(PA_SC_AA_CONFIG, 0);
	WWEG32(PA_SC_WINE_STIPPWE, 0);
	WWEG32(SPI_INPUT_Z, 0);
	WWEG32(SPI_PS_IN_CONTWOW_0, NUM_INTEWP(2));
	WWEG32(CB_COWOW7_FWAG, 0);

	/* Cweaw wendew buffew base addwesses */
	WWEG32(CB_COWOW0_BASE, 0);
	WWEG32(CB_COWOW1_BASE, 0);
	WWEG32(CB_COWOW2_BASE, 0);
	WWEG32(CB_COWOW3_BASE, 0);
	WWEG32(CB_COWOW4_BASE, 0);
	WWEG32(CB_COWOW5_BASE, 0);
	WWEG32(CB_COWOW6_BASE, 0);
	WWEG32(CB_COWOW7_BASE, 0);
	WWEG32(CB_COWOW7_FWAG, 0);

	switch (wdev->famiwy) {
	case CHIP_WV610:
	case CHIP_WV620:
	case CHIP_WS780:
	case CHIP_WS880:
		tmp = TC_W2_SIZE(8);
		bweak;
	case CHIP_WV630:
	case CHIP_WV635:
		tmp = TC_W2_SIZE(4);
		bweak;
	case CHIP_W600:
		tmp = TC_W2_SIZE(0) | W2_DISABWE_WATE_HIT;
		bweak;
	defauwt:
		tmp = TC_W2_SIZE(0);
		bweak;
	}
	WWEG32(TC_CNTW, tmp);

	tmp = WWEG32(HDP_HOST_PATH_CNTW);
	WWEG32(HDP_HOST_PATH_CNTW, tmp);

	tmp = WWEG32(AWB_POP);
	tmp |= ENABWE_TC128;
	WWEG32(AWB_POP, tmp);

	WWEG32(PA_SC_MUWTI_CHIP_CNTW, 0);
	WWEG32(PA_CW_ENHANCE, (CWIP_VTX_WEOWDEW_ENA |
			       NUM_CWIP_SEQ(3)));
	WWEG32(PA_SC_ENHANCE, FOWCE_EOV_MAX_CWK_CNT(4095));
	WWEG32(VC_ENHANCE, 0);
}


/*
 * Indiwect wegistews accessow
 */
u32 w600_pciep_wweg(stwuct wadeon_device *wdev, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&wdev->pciep_idx_wock, fwags);
	WWEG32(PCIE_POWT_INDEX, ((weg) & 0xff));
	(void)WWEG32(PCIE_POWT_INDEX);
	w = WWEG32(PCIE_POWT_DATA);
	spin_unwock_iwqwestowe(&wdev->pciep_idx_wock, fwags);
	wetuwn w;
}

void w600_pciep_wweg(stwuct wadeon_device *wdev, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wdev->pciep_idx_wock, fwags);
	WWEG32(PCIE_POWT_INDEX, ((weg) & 0xff));
	(void)WWEG32(PCIE_POWT_INDEX);
	WWEG32(PCIE_POWT_DATA, (v));
	(void)WWEG32(PCIE_POWT_DATA);
	spin_unwock_iwqwestowe(&wdev->pciep_idx_wock, fwags);
}

/*
 * CP & Wing
 */
void w600_cp_stop(stwuct wadeon_device *wdev)
{
	if (wdev->asic->copy.copy_wing_index == WADEON_WING_TYPE_GFX_INDEX)
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.visibwe_vwam_size);
	WWEG32(W_0086D8_CP_ME_CNTW, S_0086D8_CP_ME_HAWT(1));
	WWEG32(SCWATCH_UMSK, 0);
	wdev->wing[WADEON_WING_TYPE_GFX_INDEX].weady = fawse;
}

int w600_init_micwocode(stwuct wadeon_device *wdev)
{
	const chaw *chip_name;
	const chaw *wwc_chip_name;
	const chaw *smc_chip_name = "WV770";
	size_t pfp_weq_size, me_weq_size, wwc_weq_size, smc_weq_size = 0;
	chaw fw_name[30];
	int eww;

	DWM_DEBUG("\n");

	switch (wdev->famiwy) {
	case CHIP_W600:
		chip_name = "W600";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WV610:
		chip_name = "WV610";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WV630:
		chip_name = "WV630";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WV620:
		chip_name = "WV620";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WV635:
		chip_name = "WV635";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WV670:
		chip_name = "WV670";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WS780:
	case CHIP_WS880:
		chip_name = "WS780";
		wwc_chip_name = "W600";
		bweak;
	case CHIP_WV770:
		chip_name = "WV770";
		wwc_chip_name = "W700";
		smc_chip_name = "WV770";
		smc_weq_size = AWIGN(WV770_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_WV730:
		chip_name = "WV730";
		wwc_chip_name = "W700";
		smc_chip_name = "WV730";
		smc_weq_size = AWIGN(WV730_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_WV710:
		chip_name = "WV710";
		wwc_chip_name = "W700";
		smc_chip_name = "WV710";
		smc_weq_size = AWIGN(WV710_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_WV740:
		chip_name = "WV730";
		wwc_chip_name = "W700";
		smc_chip_name = "WV740";
		smc_weq_size = AWIGN(WV740_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_CEDAW:
		chip_name = "CEDAW";
		wwc_chip_name = "CEDAW";
		smc_chip_name = "CEDAW";
		smc_weq_size = AWIGN(CEDAW_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_WEDWOOD:
		chip_name = "WEDWOOD";
		wwc_chip_name = "WEDWOOD";
		smc_chip_name = "WEDWOOD";
		smc_weq_size = AWIGN(WEDWOOD_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_JUNIPEW:
		chip_name = "JUNIPEW";
		wwc_chip_name = "JUNIPEW";
		smc_chip_name = "JUNIPEW";
		smc_weq_size = AWIGN(JUNIPEW_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		chip_name = "CYPWESS";
		wwc_chip_name = "CYPWESS";
		smc_chip_name = "CYPWESS";
		smc_weq_size = AWIGN(CYPWESS_SMC_UCODE_SIZE, 4);
		bweak;
	case CHIP_PAWM:
		chip_name = "PAWM";
		wwc_chip_name = "SUMO";
		bweak;
	case CHIP_SUMO:
		chip_name = "SUMO";
		wwc_chip_name = "SUMO";
		bweak;
	case CHIP_SUMO2:
		chip_name = "SUMO2";
		wwc_chip_name = "SUMO";
		bweak;
	defauwt: BUG();
	}

	if (wdev->famiwy >= CHIP_CEDAW) {
		pfp_weq_size = EVEWGWEEN_PFP_UCODE_SIZE * 4;
		me_weq_size = EVEWGWEEN_PM4_UCODE_SIZE * 4;
		wwc_weq_size = EVEWGWEEN_WWC_UCODE_SIZE * 4;
	} ewse if (wdev->famiwy >= CHIP_WV770) {
		pfp_weq_size = W700_PFP_UCODE_SIZE * 4;
		me_weq_size = W700_PM4_UCODE_SIZE * 4;
		wwc_weq_size = W700_WWC_UCODE_SIZE * 4;
	} ewse {
		pfp_weq_size = W600_PFP_UCODE_SIZE * 4;
		me_weq_size = W600_PM4_UCODE_SIZE * 12;
		wwc_weq_size = W600_WWC_UCODE_SIZE * 4;
	}

	DWM_INFO("Woading %s Micwocode\n", chip_name);

	snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_pfp.bin", chip_name);
	eww = wequest_fiwmwawe(&wdev->pfp_fw, fw_name, wdev->dev);
	if (eww)
		goto out;
	if (wdev->pfp_fw->size != pfp_weq_size) {
		pw_eww("w600_cp: Bogus wength %zu in fiwmwawe \"%s\"\n",
		       wdev->pfp_fw->size, fw_name);
		eww = -EINVAW;
		goto out;
	}

	snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_me.bin", chip_name);
	eww = wequest_fiwmwawe(&wdev->me_fw, fw_name, wdev->dev);
	if (eww)
		goto out;
	if (wdev->me_fw->size != me_weq_size) {
		pw_eww("w600_cp: Bogus wength %zu in fiwmwawe \"%s\"\n",
		       wdev->me_fw->size, fw_name);
		eww = -EINVAW;
		goto out;
	}

	snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_wwc.bin", wwc_chip_name);
	eww = wequest_fiwmwawe(&wdev->wwc_fw, fw_name, wdev->dev);
	if (eww)
		goto out;
	if (wdev->wwc_fw->size != wwc_weq_size) {
		pw_eww("w600_wwc: Bogus wength %zu in fiwmwawe \"%s\"\n",
		       wdev->wwc_fw->size, fw_name);
		eww = -EINVAW;
		goto out;
	}

	if ((wdev->famiwy >= CHIP_WV770) && (wdev->famiwy <= CHIP_HEMWOCK)) {
		snpwintf(fw_name, sizeof(fw_name), "wadeon/%s_smc.bin", smc_chip_name);
		eww = wequest_fiwmwawe(&wdev->smc_fw, fw_name, wdev->dev);
		if (eww) {
			pw_eww("smc: ewwow woading fiwmwawe \"%s\"\n", fw_name);
			wewease_fiwmwawe(wdev->smc_fw);
			wdev->smc_fw = NUWW;
			eww = 0;
		} ewse if (wdev->smc_fw->size != smc_weq_size) {
			pw_eww("smc: Bogus wength %zu in fiwmwawe \"%s\"\n",
			       wdev->smc_fw->size, fw_name);
			eww = -EINVAW;
		}
	}

out:
	if (eww) {
		if (eww != -EINVAW)
			pw_eww("w600_cp: Faiwed to woad fiwmwawe \"%s\"\n",
			       fw_name);
		wewease_fiwmwawe(wdev->pfp_fw);
		wdev->pfp_fw = NUWW;
		wewease_fiwmwawe(wdev->me_fw);
		wdev->me_fw = NUWW;
		wewease_fiwmwawe(wdev->wwc_fw);
		wdev->wwc_fw = NUWW;
		wewease_fiwmwawe(wdev->smc_fw);
		wdev->smc_fw = NUWW;
	}
	wetuwn eww;
}

u32 w600_gfx_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing)
{
	u32 wptw;

	if (wdev->wb.enabwed)
		wptw = wdev->wb.wb[wing->wptw_offs/4];
	ewse
		wptw = WWEG32(W600_CP_WB_WPTW);

	wetuwn wptw;
}

u32 w600_gfx_get_wptw(stwuct wadeon_device *wdev,
		      stwuct wadeon_wing *wing)
{
	wetuwn WWEG32(W600_CP_WB_WPTW);
}

void w600_gfx_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing)
{
	WWEG32(W600_CP_WB_WPTW, wing->wptw);
	(void)WWEG32(W600_CP_WB_WPTW);
}

static int w600_cp_woad_micwocode(stwuct wadeon_device *wdev)
{
	const __be32 *fw_data;
	int i;

	if (!wdev->me_fw || !wdev->pfp_fw)
		wetuwn -EINVAW;

	w600_cp_stop(wdev);

	WWEG32(CP_WB_CNTW,
#ifdef __BIG_ENDIAN
	       BUF_SWAP_32BIT |
#endif
	       WB_NO_UPDATE | WB_BWKSZ(15) | WB_BUFSZ(3));

	/* Weset cp */
	WWEG32(GWBM_SOFT_WESET, SOFT_WESET_CP);
	WWEG32(GWBM_SOFT_WESET);
	mdeway(15);
	WWEG32(GWBM_SOFT_WESET, 0);

	WWEG32(CP_ME_WAM_WADDW, 0);

	fw_data = (const __be32 *)wdev->me_fw->data;
	WWEG32(CP_ME_WAM_WADDW, 0);
	fow (i = 0; i < W600_PM4_UCODE_SIZE * 3; i++)
		WWEG32(CP_ME_WAM_DATA,
		       be32_to_cpup(fw_data++));

	fw_data = (const __be32 *)wdev->pfp_fw->data;
	WWEG32(CP_PFP_UCODE_ADDW, 0);
	fow (i = 0; i < W600_PFP_UCODE_SIZE; i++)
		WWEG32(CP_PFP_UCODE_DATA,
		       be32_to_cpup(fw_data++));

	WWEG32(CP_PFP_UCODE_ADDW, 0);
	WWEG32(CP_ME_WAM_WADDW, 0);
	WWEG32(CP_ME_WAM_WADDW, 0);
	wetuwn 0;
}

int w600_cp_stawt(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	int w;
	uint32_t cp_me;

	w = wadeon_wing_wock(wdev, wing, 7);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing (%d).\n", w);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, PACKET3(PACKET3_ME_INITIAWIZE, 5));
	wadeon_wing_wwite(wing, 0x1);
	if (wdev->famiwy >= CHIP_WV770) {
		wadeon_wing_wwite(wing, 0x0);
		wadeon_wing_wwite(wing, wdev->config.wv770.max_hw_contexts - 1);
	} ewse {
		wadeon_wing_wwite(wing, 0x3);
		wadeon_wing_wwite(wing, wdev->config.w600.max_hw_contexts - 1);
	}
	wadeon_wing_wwite(wing, PACKET3_ME_INITIAWIZE_DEVICE_ID(1));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_unwock_commit(wdev, wing, fawse);

	cp_me = 0xff;
	WWEG32(W_0086D8_CP_ME_CNTW, cp_me);
	wetuwn 0;
}

int w600_cp_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	u32 tmp;
	u32 wb_bufsz;
	int w;

	/* Weset cp */
	WWEG32(GWBM_SOFT_WESET, SOFT_WESET_CP);
	WWEG32(GWBM_SOFT_WESET);
	mdeway(15);
	WWEG32(GWBM_SOFT_WESET, 0);

	/* Set wing buffew size */
	wb_bufsz = owdew_base_2(wing->wing_size / 8);
	tmp = (owdew_base_2(WADEON_GPU_PAGE_SIZE/8) << 8) | wb_bufsz;
#ifdef __BIG_ENDIAN
	tmp |= BUF_SWAP_32BIT;
#endif
	WWEG32(CP_WB_CNTW, tmp);
	WWEG32(CP_SEM_WAIT_TIMEW, 0x0);

	/* Set the wwite pointew deway */
	WWEG32(CP_WB_WPTW_DEWAY, 0);

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32(CP_WB_CNTW, tmp | WB_WPTW_WW_ENA);
	WWEG32(CP_WB_WPTW_WW, 0);
	wing->wptw = 0;
	WWEG32(CP_WB_WPTW, wing->wptw);

	/* set the wb addwess whethew it's enabwed ow not */
	WWEG32(CP_WB_WPTW_ADDW,
	       ((wdev->wb.gpu_addw + WADEON_WB_CP_WPTW_OFFSET) & 0xFFFFFFFC));
	WWEG32(CP_WB_WPTW_ADDW_HI, uppew_32_bits(wdev->wb.gpu_addw + WADEON_WB_CP_WPTW_OFFSET) & 0xFF);
	WWEG32(SCWATCH_ADDW, ((wdev->wb.gpu_addw + WADEON_WB_SCWATCH_OFFSET) >> 8) & 0xFFFFFFFF);

	if (wdev->wb.enabwed)
		WWEG32(SCWATCH_UMSK, 0xff);
	ewse {
		tmp |= WB_NO_UPDATE;
		WWEG32(SCWATCH_UMSK, 0);
	}

	mdeway(1);
	WWEG32(CP_WB_CNTW, tmp);

	WWEG32(CP_WB_BASE, wing->gpu_addw >> 8);
	WWEG32(CP_DEBUG, (1 << 27) | (1 << 28));

	w600_cp_stawt(wdev);
	wing->weady = twue;
	w = wadeon_wing_test(wdev, WADEON_WING_TYPE_GFX_INDEX, wing);
	if (w) {
		wing->weady = fawse;
		wetuwn w;
	}

	if (wdev->asic->copy.copy_wing_index == WADEON_WING_TYPE_GFX_INDEX)
		wadeon_ttm_set_active_vwam_size(wdev, wdev->mc.weaw_vwam_size);

	wetuwn 0;
}

void w600_wing_init(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing, unsigned wing_size)
{
	u32 wb_bufsz;
	int w;

	/* Awign wing size */
	wb_bufsz = owdew_base_2(wing_size / 8);
	wing_size = (1 << (wb_bufsz + 1)) * 4;
	wing->wing_size = wing_size;
	wing->awign_mask = 16 - 1;

	if (wadeon_wing_suppowts_scwatch_weg(wdev, wing)) {
		w = wadeon_scwatch_get(wdev, &wing->wptw_save_weg);
		if (w) {
			DWM_EWWOW("faiwed to get scwatch weg fow wptw save (%d).\n", w);
			wing->wptw_save_weg = 0;
		}
	}
}

void w600_cp_fini(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	w600_cp_stop(wdev);
	wadeon_wing_fini(wdev, wing);
	wadeon_scwatch_fwee(wdev, wing->wptw_save_weg);
}

/*
 * GPU scwatch wegistews hewpews function.
 */
void w600_scwatch_init(stwuct wadeon_device *wdev)
{
	int i;

	wdev->scwatch.num_weg = 7;
	wdev->scwatch.weg_base = SCWATCH_WEG0;
	fow (i = 0; i < wdev->scwatch.num_weg; i++) {
		wdev->scwatch.fwee[i] = twue;
		wdev->scwatch.weg[i] = wdev->scwatch.weg_base + (i * 4);
	}
}

int w600_wing_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	uint32_t scwatch;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	w = wadeon_scwatch_get(wdev, &scwatch);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to get scwatch weg (%d).\n", w);
		wetuwn w;
	}
	WWEG32(scwatch, 0xCAFEDEAD);
	w = wadeon_wing_wock(wdev, wing, 3);
	if (w) {
		DWM_EWWOW("wadeon: cp faiwed to wock wing %d (%d).\n", wing->idx, w);
		wadeon_scwatch_fwee(wdev, scwatch);
		wetuwn w;
	}
	wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
	wadeon_wing_wwite(wing, ((scwatch - PACKET3_SET_CONFIG_WEG_OFFSET) >> 2));
	wadeon_wing_wwite(wing, 0xDEADBEEF);
	wadeon_wing_unwock_commit(wdev, wing, fawse);
	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = WWEG32(scwatch);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}
	if (i < wdev->usec_timeout) {
		DWM_INFO("wing test on %d succeeded in %d usecs\n", wing->idx, i);
	} ewse {
		DWM_EWWOW("wadeon: wing %d test faiwed (scwatch(0x%04X)=0x%08X)\n",
			  wing->idx, scwatch, tmp);
		w = -EINVAW;
	}
	wadeon_scwatch_fwee(wdev, scwatch);
	wetuwn w;
}

/*
 * CP fences/semaphowes
 */

void w600_fence_wing_emit(stwuct wadeon_device *wdev,
			  stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	u32 cp_cohew_cntw = PACKET3_TC_ACTION_ENA | PACKET3_VC_ACTION_ENA |
		PACKET3_SH_ACTION_ENA;

	if (wdev->famiwy >= CHIP_WV770)
		cp_cohew_cntw |= PACKET3_FUWW_CACHE_ENA;

	if (wdev->wb.use_event) {
		u64 addw = wdev->fence_dwv[fence->wing].gpu_addw;
		/* fwush wead cache ovew gawt */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SUWFACE_SYNC, 3));
		wadeon_wing_wwite(wing, cp_cohew_cntw);
		wadeon_wing_wwite(wing, 0xFFFFFFFF);
		wadeon_wing_wwite(wing, 0);
		wadeon_wing_wwite(wing, 10); /* poww intewvaw */
		/* EVENT_WWITE_EOP - fwush caches, send int */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE_EOP, 4));
		wadeon_wing_wwite(wing, EVENT_TYPE(CACHE_FWUSH_AND_INV_EVENT_TS) | EVENT_INDEX(5));
		wadeon_wing_wwite(wing, wowew_32_bits(addw));
		wadeon_wing_wwite(wing, (uppew_32_bits(addw) & 0xff) | DATA_SEW(1) | INT_SEW(2));
		wadeon_wing_wwite(wing, fence->seq);
		wadeon_wing_wwite(wing, 0);
	} ewse {
		/* fwush wead cache ovew gawt */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SUWFACE_SYNC, 3));
		wadeon_wing_wwite(wing, cp_cohew_cntw);
		wadeon_wing_wwite(wing, 0xFFFFFFFF);
		wadeon_wing_wwite(wing, 0);
		wadeon_wing_wwite(wing, 10); /* poww intewvaw */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_EVENT_WWITE, 0));
		wadeon_wing_wwite(wing, EVENT_TYPE(CACHE_FWUSH_AND_INV_EVENT) | EVENT_INDEX(0));
		/* wait fow 3D idwe cwean */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		wadeon_wing_wwite(wing, (WAIT_UNTIW - PACKET3_SET_CONFIG_WEG_OFFSET) >> 2);
		wadeon_wing_wwite(wing, WAIT_3D_IDWE_bit | WAIT_3D_IDWECWEAN_bit);
		/* Emit fence sequence & fiwe IWQ */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		wadeon_wing_wwite(wing, ((wdev->fence_dwv[fence->wing].scwatch_weg - PACKET3_SET_CONFIG_WEG_OFFSET) >> 2));
		wadeon_wing_wwite(wing, fence->seq);
		/* CP_INTEWWUPT packet 3 no wongew exists, use packet 0 */
		wadeon_wing_wwite(wing, PACKET0(CP_INT_STATUS, 0));
		wadeon_wing_wwite(wing, WB_INT_STAT);
	}
}

/**
 * w600_semaphowe_wing_emit - emit a semaphowe on the CP wing
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon wing buffew object
 * @semaphowe: wadeon semaphowe object
 * @emit_wait: Is this a semaphowe wait?
 *
 * Emits a semaphowe signaw/wait packet to the CP wing and pwevents the PFP
 * fwom wunning ahead of semaphowe waits.
 */
boow w600_semaphowe_wing_emit(stwuct wadeon_device *wdev,
			      stwuct wadeon_wing *wing,
			      stwuct wadeon_semaphowe *semaphowe,
			      boow emit_wait)
{
	uint64_t addw = semaphowe->gpu_addw;
	unsigned sew = emit_wait ? PACKET3_SEM_SEW_WAIT : PACKET3_SEM_SEW_SIGNAW;

	if (wdev->famiwy < CHIP_CAYMAN)
		sew |= PACKET3_SEM_WAIT_ON_SIGNAW;

	wadeon_wing_wwite(wing, PACKET3(PACKET3_MEM_SEMAPHOWE, 1));
	wadeon_wing_wwite(wing, wowew_32_bits(addw));
	wadeon_wing_wwite(wing, (uppew_32_bits(addw) & 0xff) | sew);

	/* PFP_SYNC_ME packet onwy exists on 7xx+, onwy enabwe it on eg+ */
	if (emit_wait && (wdev->famiwy >= CHIP_CEDAW)) {
		/* Pwevent the PFP fwom wunning ahead of the semaphowe wait */
		wadeon_wing_wwite(wing, PACKET3(PACKET3_PFP_SYNC_ME, 0));
		wadeon_wing_wwite(wing, 0x0);
	}

	wetuwn twue;
}

/**
 * w600_copy_cpdma - copy pages using the CP DMA engine
 *
 * @wdev: wadeon_device pointew
 * @swc_offset: swc GPU addwess
 * @dst_offset: dst GPU addwess
 * @num_gpu_pages: numbew of GPU pages to xfew
 * @wesv: DMA wesewvation object to manage fences
 *
 * Copy GPU paging using the CP DMA engine (w6xx+).
 * Used by the wadeon ttm impwementation to move pages if
 * wegistewed as the asic copy cawwback.
 */
stwuct wadeon_fence *w600_copy_cpdma(stwuct wadeon_device *wdev,
				     uint64_t swc_offset, uint64_t dst_offset,
				     unsigned num_gpu_pages,
				     stwuct dma_wesv *wesv)
{
	stwuct wadeon_fence *fence;
	stwuct wadeon_sync sync;
	int wing_index = wdev->asic->copy.bwit_wing_index;
	stwuct wadeon_wing *wing = &wdev->wing[wing_index];
	u32 size_in_bytes, cuw_size_in_bytes, tmp;
	int i, num_woops;
	int w = 0;

	wadeon_sync_cweate(&sync);

	size_in_bytes = (num_gpu_pages << WADEON_GPU_PAGE_SHIFT);
	num_woops = DIV_WOUND_UP(size_in_bytes, 0x1fffff);
	w = wadeon_wing_wock(wdev, wing, num_woops * 6 + 24);
	if (w) {
		DWM_EWWOW("wadeon: moving bo (%d).\n", w);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_sync_wesv(wdev, &sync, wesv, fawse);
	wadeon_sync_wings(wdev, &sync, wing->idx);

	wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
	wadeon_wing_wwite(wing, (WAIT_UNTIW - PACKET3_SET_CONFIG_WEG_OFFSET) >> 2);
	wadeon_wing_wwite(wing, WAIT_3D_IDWE_bit);
	fow (i = 0; i < num_woops; i++) {
		cuw_size_in_bytes = size_in_bytes;
		if (cuw_size_in_bytes > 0x1fffff)
			cuw_size_in_bytes = 0x1fffff;
		size_in_bytes -= cuw_size_in_bytes;
		tmp = uppew_32_bits(swc_offset) & 0xff;
		if (size_in_bytes == 0)
			tmp |= PACKET3_CP_DMA_CP_SYNC;
		wadeon_wing_wwite(wing, PACKET3(PACKET3_CP_DMA, 4));
		wadeon_wing_wwite(wing, wowew_32_bits(swc_offset));
		wadeon_wing_wwite(wing, tmp);
		wadeon_wing_wwite(wing, wowew_32_bits(dst_offset));
		wadeon_wing_wwite(wing, uppew_32_bits(dst_offset) & 0xff);
		wadeon_wing_wwite(wing, cuw_size_in_bytes);
		swc_offset += cuw_size_in_bytes;
		dst_offset += cuw_size_in_bytes;
	}
	wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
	wadeon_wing_wwite(wing, (WAIT_UNTIW - PACKET3_SET_CONFIG_WEG_OFFSET) >> 2);
	wadeon_wing_wwite(wing, WAIT_CP_DMA_IDWE_bit);

	w = wadeon_fence_emit(wdev, &fence, wing->idx);
	if (w) {
		wadeon_wing_unwock_undo(wdev, wing);
		wadeon_sync_fwee(wdev, &sync, NUWW);
		wetuwn EWW_PTW(w);
	}

	wadeon_wing_unwock_commit(wdev, wing, fawse);
	wadeon_sync_fwee(wdev, &sync, fence);

	wetuwn fence;
}

int w600_set_suwface_weg(stwuct wadeon_device *wdev, int weg,
			 uint32_t tiwing_fwags, uint32_t pitch,
			 uint32_t offset, uint32_t obj_size)
{
	/* FIXME: impwement */
	wetuwn 0;
}

void w600_cweaw_suwface_weg(stwuct wadeon_device *wdev, int weg)
{
	/* FIXME: impwement */
}

static void w600_uvd_init(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->has_uvd)
		wetuwn;

	w = wadeon_uvd_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed UVD (%d) init.\n", w);
		/*
		 * At this point wdev->uvd.vcpu_bo is NUWW which twickwes down
		 * to eawwy faiws uvd_v1_0_wesume() and thus nothing happens
		 * thewe. So it is pointwess to twy to go thwough that code
		 * hence why we disabwe uvd hewe.
		 */
		wdev->has_uvd = fawse;
		wetuwn;
	}
	wdev->wing[W600_WING_TYPE_UVD_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[W600_WING_TYPE_UVD_INDEX], 4096);
}

static void w600_uvd_stawt(stwuct wadeon_device *wdev)
{
	int w;

	if (!wdev->has_uvd)
		wetuwn;

	w = uvd_v1_0_wesume(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed UVD wesume (%d).\n", w);
		goto ewwow;
	}
	w = wadeon_fence_dwivew_stawt_wing(wdev, W600_WING_TYPE_UVD_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing UVD fences (%d).\n", w);
		goto ewwow;
	}
	wetuwn;

ewwow:
	wdev->wing[W600_WING_TYPE_UVD_INDEX].wing_size = 0;
}

static void w600_uvd_wesume(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	int w;

	if (!wdev->has_uvd || !wdev->wing[W600_WING_TYPE_UVD_INDEX].wing_size)
		wetuwn;

	wing = &wdev->wing[W600_WING_TYPE_UVD_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, 0, PACKET0(UVD_NO_OP, 0));
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing UVD wing (%d).\n", w);
		wetuwn;
	}
	w = uvd_v1_0_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing UVD (%d).\n", w);
		wetuwn;
	}
}

static int w600_stawtup(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	int w;

	/* enabwe pcie gen2 wink */
	w600_pcie_gen2_enabwe(wdev);

	/* scwatch needs to be initiawized befowe MC */
	w = w600_vwam_scwatch_init(wdev);
	if (w)
		wetuwn w;

	w600_mc_pwogwam(wdev);

	if (wdev->fwags & WADEON_IS_AGP) {
		w600_agp_enabwe(wdev);
	} ewse {
		w = w600_pcie_gawt_enabwe(wdev);
		if (w)
			wetuwn w;
	}
	w600_gpu_init(wdev);

	/* awwocate wb buffew */
	w = wadeon_wb_init(wdev);
	if (w)
		wetuwn w;

	w = wadeon_fence_dwivew_stawt_wing(wdev, WADEON_WING_TYPE_GFX_INDEX);
	if (w) {
		dev_eww(wdev->dev, "faiwed initiawizing CP fences (%d).\n", w);
		wetuwn w;
	}

	w600_uvd_stawt(wdev);

	/* Enabwe IWQ */
	if (!wdev->iwq.instawwed) {
		w = wadeon_iwq_kms_init(wdev);
		if (w)
			wetuwn w;
	}

	w = w600_iwq_init(wdev);
	if (w) {
		DWM_EWWOW("wadeon: IH init faiwed (%d).\n", w);
		wadeon_iwq_kms_fini(wdev);
		wetuwn w;
	}
	w600_iwq_set(wdev);

	wing = &wdev->wing[WADEON_WING_TYPE_GFX_INDEX];
	w = wadeon_wing_init(wdev, wing, wing->wing_size, WADEON_WB_CP_WPTW_OFFSET,
			     WADEON_CP_PACKET2);
	if (w)
		wetuwn w;

	w = w600_cp_woad_micwocode(wdev);
	if (w)
		wetuwn w;
	w = w600_cp_wesume(wdev);
	if (w)
		wetuwn w;

	w600_uvd_wesume(wdev);

	w = wadeon_ib_poow_init(wdev);
	if (w) {
		dev_eww(wdev->dev, "IB initiawization faiwed (%d).\n", w);
		wetuwn w;
	}

	w = wadeon_audio_init(wdev);
	if (w) {
		DWM_EWWOW("wadeon: audio init faiwed\n");
		wetuwn w;
	}

	wetuwn 0;
}

void w600_vga_set_state(stwuct wadeon_device *wdev, boow state)
{
	uint32_t temp;

	temp = WWEG32(CONFIG_CNTW);
	if (!state) {
		temp &= ~(1<<0);
		temp |= (1<<1);
	} ewse {
		temp &= ~(1<<1);
	}
	WWEG32(CONFIG_CNTW, temp);
}

int w600_wesume(stwuct wadeon_device *wdev)
{
	int w;

	/* Do not weset GPU befowe posting, on w600 hw unwike on w500 hw,
	 * posting wiww pewfowm necessawy task to bwing back GPU into good
	 * shape.
	 */
	/* post cawd */
	atom_asic_init(wdev->mode_info.atom_context);

	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_wesume(wdev);

	wdev->accew_wowking = twue;
	w = w600_stawtup(wdev);
	if (w) {
		DWM_EWWOW("w600 stawtup faiwed on wesume\n");
		wdev->accew_wowking = fawse;
		wetuwn w;
	}

	wetuwn w;
}

int w600_suspend(stwuct wadeon_device *wdev)
{
	wadeon_pm_suspend(wdev);
	wadeon_audio_fini(wdev);
	w600_cp_stop(wdev);
	if (wdev->has_uvd) {
		wadeon_uvd_suspend(wdev);
		uvd_v1_0_fini(wdev);
	}
	w600_iwq_suspend(wdev);
	wadeon_wb_disabwe(wdev);
	w600_pcie_gawt_disabwe(wdev);

	wetuwn 0;
}

/* Pwan is to move initiawization in that function and use
 * hewpew function so that wadeon_device_init pwetty much
 * do nothing mowe than cawwing asic specific function. This
 * shouwd awso awwow to wemove a bunch of cawwback function
 * wike vwam_info.
 */
int w600_init(stwuct wadeon_device *wdev)
{
	int w;

	w600_debugfs_mc_info_init(wdev);
	/* Wead BIOS */
	if (!wadeon_get_bios(wdev)) {
		if (ASIC_IS_AVIVO(wdev))
			wetuwn -EINVAW;
	}
	/* Must be an ATOMBIOS */
	if (!wdev->is_atom_bios) {
		dev_eww(wdev->dev, "Expecting atombios fow W600 GPU\n");
		wetuwn -EINVAW;
	}
	w = wadeon_atombios_init(wdev);
	if (w)
		wetuwn w;
	/* Post cawd if necessawy */
	if (!wadeon_cawd_posted(wdev)) {
		if (!wdev->bios) {
			dev_eww(wdev->dev, "Cawd not posted and no BIOS - ignowing\n");
			wetuwn -EINVAW;
		}
		DWM_INFO("GPU not posted. posting now...\n");
		atom_asic_init(wdev->mode_info.atom_context);
	}
	/* Initiawize scwatch wegistews */
	w600_scwatch_init(wdev);
	/* Initiawize suwface wegistews */
	wadeon_suwface_init(wdev);
	/* Initiawize cwocks */
	wadeon_get_cwock_info(wdev->ddev);
	/* Fence dwivew */
	wadeon_fence_dwivew_init(wdev);
	if (wdev->fwags & WADEON_IS_AGP) {
		w = wadeon_agp_init(wdev);
		if (w)
			wadeon_agp_disabwe(wdev);
	}
	w = w600_mc_init(wdev);
	if (w)
		wetuwn w;
	/* Memowy managew */
	w = wadeon_bo_init(wdev);
	if (w)
		wetuwn w;

	if (!wdev->me_fw || !wdev->pfp_fw || !wdev->wwc_fw) {
		w = w600_init_micwocode(wdev);
		if (w) {
			DWM_EWWOW("Faiwed to woad fiwmwawe!\n");
			wetuwn w;
		}
	}

	/* Initiawize powew management */
	wadeon_pm_init(wdev);

	wdev->wing[WADEON_WING_TYPE_GFX_INDEX].wing_obj = NUWW;
	w600_wing_init(wdev, &wdev->wing[WADEON_WING_TYPE_GFX_INDEX], 1024 * 1024);

	w600_uvd_init(wdev);

	wdev->ih.wing_obj = NUWW;
	w600_ih_wing_init(wdev, 64 * 1024);

	w = w600_pcie_gawt_init(wdev);
	if (w)
		wetuwn w;

	wdev->accew_wowking = twue;
	w = w600_stawtup(wdev);
	if (w) {
		dev_eww(wdev->dev, "disabwing GPU accewewation\n");
		w600_cp_fini(wdev);
		w600_iwq_fini(wdev);
		wadeon_wb_fini(wdev);
		wadeon_ib_poow_fini(wdev);
		wadeon_iwq_kms_fini(wdev);
		w600_pcie_gawt_fini(wdev);
		wdev->accew_wowking = fawse;
	}

	wetuwn 0;
}

void w600_fini(stwuct wadeon_device *wdev)
{
	wadeon_pm_fini(wdev);
	wadeon_audio_fini(wdev);
	w600_cp_fini(wdev);
	w600_iwq_fini(wdev);
	if (wdev->has_uvd) {
		uvd_v1_0_fini(wdev);
		wadeon_uvd_fini(wdev);
	}
	wadeon_wb_fini(wdev);
	wadeon_ib_poow_fini(wdev);
	wadeon_iwq_kms_fini(wdev);
	w600_pcie_gawt_fini(wdev);
	w600_vwam_scwatch_fini(wdev);
	wadeon_agp_fini(wdev);
	wadeon_gem_fini(wdev);
	wadeon_fence_dwivew_fini(wdev);
	wadeon_bo_fini(wdev);
	wadeon_atombios_fini(wdev);
	kfwee(wdev->bios);
	wdev->bios = NUWW;
}


/*
 * CS stuff
 */
void w600_wing_ib_execute(stwuct wadeon_device *wdev, stwuct wadeon_ib *ib)
{
	stwuct wadeon_wing *wing = &wdev->wing[ib->wing];
	u32 next_wptw;

	if (wing->wptw_save_weg) {
		next_wptw = wing->wptw + 3 + 4;
		wadeon_wing_wwite(wing, PACKET3(PACKET3_SET_CONFIG_WEG, 1));
		wadeon_wing_wwite(wing, ((wing->wptw_save_weg -
					 PACKET3_SET_CONFIG_WEG_OFFSET) >> 2));
		wadeon_wing_wwite(wing, next_wptw);
	} ewse if (wdev->wb.enabwed) {
		next_wptw = wing->wptw + 5 + 4;
		wadeon_wing_wwite(wing, PACKET3(PACKET3_MEM_WWITE, 3));
		wadeon_wing_wwite(wing, wing->next_wptw_gpu_addw & 0xfffffffc);
		wadeon_wing_wwite(wing, (uppew_32_bits(wing->next_wptw_gpu_addw) & 0xff) | (1 << 18));
		wadeon_wing_wwite(wing, next_wptw);
		wadeon_wing_wwite(wing, 0);
	}

	wadeon_wing_wwite(wing, PACKET3(PACKET3_INDIWECT_BUFFEW, 2));
	wadeon_wing_wwite(wing,
#ifdef __BIG_ENDIAN
			  (2 << 0) |
#endif
			  (ib->gpu_addw & 0xFFFFFFFC));
	wadeon_wing_wwite(wing, uppew_32_bits(ib->gpu_addw) & 0xFF);
	wadeon_wing_wwite(wing, ib->wength_dw);
}

int w600_ib_test(stwuct wadeon_device *wdev, stwuct wadeon_wing *wing)
{
	stwuct wadeon_ib ib;
	uint32_t scwatch;
	uint32_t tmp = 0;
	unsigned i;
	int w;

	w = wadeon_scwatch_get(wdev, &scwatch);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get scwatch weg (%d).\n", w);
		wetuwn w;
	}
	WWEG32(scwatch, 0xCAFEDEAD);
	w = wadeon_ib_get(wdev, wing->idx, &ib, NUWW, 256);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to get ib (%d).\n", w);
		goto fwee_scwatch;
	}
	ib.ptw[0] = PACKET3(PACKET3_SET_CONFIG_WEG, 1);
	ib.ptw[1] = ((scwatch - PACKET3_SET_CONFIG_WEG_OFFSET) >> 2);
	ib.ptw[2] = 0xDEADBEEF;
	ib.wength_dw = 3;
	w = wadeon_ib_scheduwe(wdev, &ib, NUWW, fawse);
	if (w) {
		DWM_EWWOW("wadeon: faiwed to scheduwe ib (%d).\n", w);
		goto fwee_ib;
	}
	w = wadeon_fence_wait_timeout(ib.fence, fawse, usecs_to_jiffies(
		WADEON_USEC_IB_TEST_TIMEOUT));
	if (w < 0) {
		DWM_EWWOW("wadeon: fence wait faiwed (%d).\n", w);
		goto fwee_ib;
	} ewse if (w == 0) {
		DWM_EWWOW("wadeon: fence wait timed out.\n");
		w = -ETIMEDOUT;
		goto fwee_ib;
	}
	w = 0;
	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = WWEG32(scwatch);
		if (tmp == 0xDEADBEEF)
			bweak;
		udeway(1);
	}
	if (i < wdev->usec_timeout) {
		DWM_INFO("ib test on wing %d succeeded in %u usecs\n", ib.fence->wing, i);
	} ewse {
		DWM_EWWOW("wadeon: ib test faiwed (scwatch(0x%04X)=0x%08X)\n",
			  scwatch, tmp);
		w = -EINVAW;
	}
fwee_ib:
	wadeon_ib_fwee(wdev, &ib);
fwee_scwatch:
	wadeon_scwatch_fwee(wdev, scwatch);
	wetuwn w;
}

/*
 * Intewwupts
 *
 * Intewwupts use a wing buffew on w6xx/w7xx hawdwawe.  It wowks pwetty
 * the same as the CP wing buffew, but in wevewse.  Wathew than the CPU
 * wwiting to the wing and the GPU consuming, the GPU wwites to the wing
 * and host consumes.  As the host iwq handwew pwocesses intewwupts, it
 * incwements the wptw.  When the wptw catches up with the wptw, aww the
 * cuwwent intewwupts have been pwocessed.
 */

void w600_ih_wing_init(stwuct wadeon_device *wdev, unsigned wing_size)
{
	u32 wb_bufsz;

	/* Awign wing size */
	wb_bufsz = owdew_base_2(wing_size / 4);
	wing_size = (1 << wb_bufsz) * 4;
	wdev->ih.wing_size = wing_size;
	wdev->ih.ptw_mask = wdev->ih.wing_size - 1;
	wdev->ih.wptw = 0;
}

int w600_ih_wing_awwoc(stwuct wadeon_device *wdev)
{
	int w;

	/* Awwocate wing buffew */
	if (wdev->ih.wing_obj == NUWW) {
		w = wadeon_bo_cweate(wdev, wdev->ih.wing_size,
				     PAGE_SIZE, twue,
				     WADEON_GEM_DOMAIN_GTT, 0,
				     NUWW, NUWW, &wdev->ih.wing_obj);
		if (w) {
			DWM_EWWOW("wadeon: faiwed to cweate ih wing buffew (%d).\n", w);
			wetuwn w;
		}
		w = wadeon_bo_wesewve(wdev->ih.wing_obj, fawse);
		if (unwikewy(w != 0))
			wetuwn w;
		w = wadeon_bo_pin(wdev->ih.wing_obj,
				  WADEON_GEM_DOMAIN_GTT,
				  &wdev->ih.gpu_addw);
		if (w) {
			wadeon_bo_unwesewve(wdev->ih.wing_obj);
			DWM_EWWOW("wadeon: faiwed to pin ih wing buffew (%d).\n", w);
			wetuwn w;
		}
		w = wadeon_bo_kmap(wdev->ih.wing_obj,
				   (void **)&wdev->ih.wing);
		wadeon_bo_unwesewve(wdev->ih.wing_obj);
		if (w) {
			DWM_EWWOW("wadeon: faiwed to map ih wing buffew (%d).\n", w);
			wetuwn w;
		}
	}
	wetuwn 0;
}

void w600_ih_wing_fini(stwuct wadeon_device *wdev)
{
	int w;
	if (wdev->ih.wing_obj) {
		w = wadeon_bo_wesewve(wdev->ih.wing_obj, fawse);
		if (wikewy(w == 0)) {
			wadeon_bo_kunmap(wdev->ih.wing_obj);
			wadeon_bo_unpin(wdev->ih.wing_obj);
			wadeon_bo_unwesewve(wdev->ih.wing_obj);
		}
		wadeon_bo_unwef(&wdev->ih.wing_obj);
		wdev->ih.wing = NUWW;
		wdev->ih.wing_obj = NUWW;
	}
}

void w600_wwc_stop(stwuct wadeon_device *wdev)
{

	if ((wdev->famiwy >= CHIP_WV770) &&
	    (wdev->famiwy <= CHIP_WV740)) {
		/* w7xx asics need to soft weset WWC befowe hawting */
		WWEG32(SWBM_SOFT_WESET, SOFT_WESET_WWC);
		WWEG32(SWBM_SOFT_WESET);
		mdeway(15);
		WWEG32(SWBM_SOFT_WESET, 0);
		WWEG32(SWBM_SOFT_WESET);
	}

	WWEG32(WWC_CNTW, 0);
}

static void w600_wwc_stawt(stwuct wadeon_device *wdev)
{
	WWEG32(WWC_CNTW, WWC_ENABWE);
}

static int w600_wwc_wesume(stwuct wadeon_device *wdev)
{
	u32 i;
	const __be32 *fw_data;

	if (!wdev->wwc_fw)
		wetuwn -EINVAW;

	w600_wwc_stop(wdev);

	WWEG32(WWC_HB_CNTW, 0);

	WWEG32(WWC_HB_BASE, 0);
	WWEG32(WWC_HB_WPTW, 0);
	WWEG32(WWC_HB_WPTW, 0);
	WWEG32(WWC_HB_WPTW_WSB_ADDW, 0);
	WWEG32(WWC_HB_WPTW_MSB_ADDW, 0);
	WWEG32(WWC_MC_CNTW, 0);
	WWEG32(WWC_UCODE_CNTW, 0);

	fw_data = (const __be32 *)wdev->wwc_fw->data;
	if (wdev->famiwy >= CHIP_WV770) {
		fow (i = 0; i < W700_WWC_UCODE_SIZE; i++) {
			WWEG32(WWC_UCODE_ADDW, i);
			WWEG32(WWC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} ewse {
		fow (i = 0; i < W600_WWC_UCODE_SIZE; i++) {
			WWEG32(WWC_UCODE_ADDW, i);
			WWEG32(WWC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	}
	WWEG32(WWC_UCODE_ADDW, 0);

	w600_wwc_stawt(wdev);

	wetuwn 0;
}

static void w600_enabwe_intewwupts(stwuct wadeon_device *wdev)
{
	u32 ih_cntw = WWEG32(IH_CNTW);
	u32 ih_wb_cntw = WWEG32(IH_WB_CNTW);

	ih_cntw |= ENABWE_INTW;
	ih_wb_cntw |= IH_WB_ENABWE;
	WWEG32(IH_CNTW, ih_cntw);
	WWEG32(IH_WB_CNTW, ih_wb_cntw);
	wdev->ih.enabwed = twue;
}

void w600_disabwe_intewwupts(stwuct wadeon_device *wdev)
{
	u32 ih_wb_cntw = WWEG32(IH_WB_CNTW);
	u32 ih_cntw = WWEG32(IH_CNTW);

	ih_wb_cntw &= ~IH_WB_ENABWE;
	ih_cntw &= ~ENABWE_INTW;
	WWEG32(IH_WB_CNTW, ih_wb_cntw);
	WWEG32(IH_CNTW, ih_cntw);
	/* set wptw, wptw to 0 */
	WWEG32(IH_WB_WPTW, 0);
	WWEG32(IH_WB_WPTW, 0);
	wdev->ih.enabwed = fawse;
	wdev->ih.wptw = 0;
}

static void w600_disabwe_intewwupt_state(stwuct wadeon_device *wdev)
{
	u32 tmp;

	WWEG32(CP_INT_CNTW, CNTX_BUSY_INT_ENABWE | CNTX_EMPTY_INT_ENABWE);
	tmp = WWEG32(DMA_CNTW) & ~TWAP_ENABWE;
	WWEG32(DMA_CNTW, tmp);
	WWEG32(GWBM_INT_CNTW, 0);
	WWEG32(DxMODE_INT_MASK, 0);
	WWEG32(D1GWPH_INTEWWUPT_CONTWOW, 0);
	WWEG32(D2GWPH_INTEWWUPT_CONTWOW, 0);
	if (ASIC_IS_DCE3(wdev)) {
		WWEG32(DCE3_DACA_AUTODETECT_INT_CONTWOW, 0);
		WWEG32(DCE3_DACB_AUTODETECT_INT_CONTWOW, 0);
		tmp = WWEG32(DC_HPD1_INT_CONTWOW) & DC_HPDx_INT_POWAWITY;
		WWEG32(DC_HPD1_INT_CONTWOW, tmp);
		tmp = WWEG32(DC_HPD2_INT_CONTWOW) & DC_HPDx_INT_POWAWITY;
		WWEG32(DC_HPD2_INT_CONTWOW, tmp);
		tmp = WWEG32(DC_HPD3_INT_CONTWOW) & DC_HPDx_INT_POWAWITY;
		WWEG32(DC_HPD3_INT_CONTWOW, tmp);
		tmp = WWEG32(DC_HPD4_INT_CONTWOW) & DC_HPDx_INT_POWAWITY;
		WWEG32(DC_HPD4_INT_CONTWOW, tmp);
		if (ASIC_IS_DCE32(wdev)) {
			tmp = WWEG32(DC_HPD5_INT_CONTWOW) & DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD5_INT_CONTWOW, tmp);
			tmp = WWEG32(DC_HPD6_INT_CONTWOW) & DC_HPDx_INT_POWAWITY;
			WWEG32(DC_HPD6_INT_CONTWOW, tmp);
			tmp = WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET0) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
			WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET0, tmp);
			tmp = WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET1) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
			WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET1, tmp);
		} ewse {
			tmp = WWEG32(HDMI0_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
			WWEG32(HDMI0_AUDIO_PACKET_CONTWOW, tmp);
			tmp = WWEG32(DCE3_HDMI1_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
			WWEG32(DCE3_HDMI1_AUDIO_PACKET_CONTWOW, tmp);
		}
	} ewse {
		WWEG32(DACA_AUTODETECT_INT_CONTWOW, 0);
		WWEG32(DACB_AUTODETECT_INT_CONTWOW, 0);
		tmp = WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW) & DC_HOT_PWUG_DETECTx_INT_POWAWITY;
		WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW, tmp);
		tmp = WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW) & DC_HOT_PWUG_DETECTx_INT_POWAWITY;
		WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW, tmp);
		tmp = WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW) & DC_HOT_PWUG_DETECTx_INT_POWAWITY;
		WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW, tmp);
		tmp = WWEG32(HDMI0_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
		WWEG32(HDMI0_AUDIO_PACKET_CONTWOW, tmp);
		tmp = WWEG32(HDMI1_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
		WWEG32(HDMI1_AUDIO_PACKET_CONTWOW, tmp);
	}
}

int w600_iwq_init(stwuct wadeon_device *wdev)
{
	int wet = 0;
	int wb_bufsz;
	u32 intewwupt_cntw, ih_cntw, ih_wb_cntw;

	/* awwocate wing */
	wet = w600_ih_wing_awwoc(wdev);
	if (wet)
		wetuwn wet;

	/* disabwe iwqs */
	w600_disabwe_intewwupts(wdev);

	/* init wwc */
	if (wdev->famiwy >= CHIP_CEDAW)
		wet = evewgween_wwc_wesume(wdev);
	ewse
		wet = w600_wwc_wesume(wdev);
	if (wet) {
		w600_ih_wing_fini(wdev);
		wetuwn wet;
	}

	/* setup intewwupt contwow */
	/* set dummy wead addwess to dummy page addwess */
	WWEG32(INTEWWUPT_CNTW2, wdev->dummy_page.addw >> 8);
	intewwupt_cntw = WWEG32(INTEWWUPT_CNTW);
	/* IH_DUMMY_WD_OVEWWIDE=0 - dummy wead disabwed with msi, enabwed without msi
	 * IH_DUMMY_WD_OVEWWIDE=1 - dummy wead contwowwed by IH_DUMMY_WD_EN
	 */
	intewwupt_cntw &= ~IH_DUMMY_WD_OVEWWIDE;
	/* IH_WEQ_NONSNOOP_EN=1 if wing is in non-cacheabwe memowy, e.g., vwam */
	intewwupt_cntw &= ~IH_WEQ_NONSNOOP_EN;
	WWEG32(INTEWWUPT_CNTW, intewwupt_cntw);

	WWEG32(IH_WB_BASE, wdev->ih.gpu_addw >> 8);
	wb_bufsz = owdew_base_2(wdev->ih.wing_size / 4);

	ih_wb_cntw = (IH_WPTW_OVEWFWOW_ENABWE |
		      IH_WPTW_OVEWFWOW_CWEAW |
		      (wb_bufsz << 1));

	if (wdev->wb.enabwed)
		ih_wb_cntw |= IH_WPTW_WWITEBACK_ENABWE;

	/* set the wwiteback addwess whethew it's enabwed ow not */
	WWEG32(IH_WB_WPTW_ADDW_WO, (wdev->wb.gpu_addw + W600_WB_IH_WPTW_OFFSET) & 0xFFFFFFFC);
	WWEG32(IH_WB_WPTW_ADDW_HI, uppew_32_bits(wdev->wb.gpu_addw + W600_WB_IH_WPTW_OFFSET) & 0xFF);

	WWEG32(IH_WB_CNTW, ih_wb_cntw);

	/* set wptw, wptw to 0 */
	WWEG32(IH_WB_WPTW, 0);
	WWEG32(IH_WB_WPTW, 0);

	/* Defauwt settings fow IH_CNTW (disabwed at fiwst) */
	ih_cntw = MC_WWWEQ_CWEDIT(0x10) | MC_WW_CWEAN_CNT(0x10);
	/* WPTW_WEAWM onwy wowks if msi's awe enabwed */
	if (wdev->msi_enabwed)
		ih_cntw |= WPTW_WEAWM;
	WWEG32(IH_CNTW, ih_cntw);

	/* fowce the active intewwupt state to aww disabwed */
	if (wdev->famiwy >= CHIP_CEDAW)
		evewgween_disabwe_intewwupt_state(wdev);
	ewse
		w600_disabwe_intewwupt_state(wdev);

	/* at this point evewything shouwd be setup cowwectwy to enabwe mastew */
	pci_set_mastew(wdev->pdev);

	/* enabwe iwqs */
	w600_enabwe_intewwupts(wdev);

	wetuwn wet;
}

void w600_iwq_suspend(stwuct wadeon_device *wdev)
{
	w600_iwq_disabwe(wdev);
	w600_wwc_stop(wdev);
}

void w600_iwq_fini(stwuct wadeon_device *wdev)
{
	w600_iwq_suspend(wdev);
	w600_ih_wing_fini(wdev);
}

int w600_iwq_set(stwuct wadeon_device *wdev)
{
	u32 cp_int_cntw = CNTX_BUSY_INT_ENABWE | CNTX_EMPTY_INT_ENABWE;
	u32 mode_int = 0;
	u32 hpd1, hpd2, hpd3, hpd4 = 0, hpd5 = 0, hpd6 = 0;
	u32 gwbm_int_cntw = 0;
	u32 hdmi0, hdmi1;
	u32 dma_cntw;
	u32 thewmaw_int = 0;

	if (!wdev->iwq.instawwed) {
		WAWN(1, "Can't enabwe IWQ/MSI because no handwew is instawwed\n");
		wetuwn -EINVAW;
	}
	/* don't enabwe anything if the ih is disabwed */
	if (!wdev->ih.enabwed) {
		w600_disabwe_intewwupts(wdev);
		/* fowce the active intewwupt state to aww disabwed */
		w600_disabwe_intewwupt_state(wdev);
		wetuwn 0;
	}

	if (ASIC_IS_DCE3(wdev)) {
		hpd1 = WWEG32(DC_HPD1_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		hpd2 = WWEG32(DC_HPD2_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		hpd3 = WWEG32(DC_HPD3_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		hpd4 = WWEG32(DC_HPD4_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		if (ASIC_IS_DCE32(wdev)) {
			hpd5 = WWEG32(DC_HPD5_INT_CONTWOW) & ~DC_HPDx_INT_EN;
			hpd6 = WWEG32(DC_HPD6_INT_CONTWOW) & ~DC_HPDx_INT_EN;
			hdmi0 = WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET0) & ~AFMT_AZ_FOWMAT_WTWIG_MASK;
			hdmi1 = WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET1) & ~AFMT_AZ_FOWMAT_WTWIG_MASK;
		} ewse {
			hdmi0 = WWEG32(HDMI0_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
			hdmi1 = WWEG32(DCE3_HDMI1_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
		}
	} ewse {
		hpd1 = WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		hpd2 = WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		hpd3 = WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW) & ~DC_HPDx_INT_EN;
		hdmi0 = WWEG32(HDMI0_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
		hdmi1 = WWEG32(HDMI1_AUDIO_PACKET_CONTWOW) & ~HDMI0_AZ_FOWMAT_WTWIG_MASK;
	}

	dma_cntw = WWEG32(DMA_CNTW) & ~TWAP_ENABWE;

	if ((wdev->famiwy > CHIP_W600) && (wdev->famiwy < CHIP_WV770)) {
		thewmaw_int = WWEG32(CG_THEWMAW_INT) &
			~(THEWM_INT_MASK_HIGH | THEWM_INT_MASK_WOW);
	} ewse if (wdev->famiwy >= CHIP_WV770) {
		thewmaw_int = WWEG32(WV770_CG_THEWMAW_INT) &
			~(THEWM_INT_MASK_HIGH | THEWM_INT_MASK_WOW);
	}
	if (wdev->iwq.dpm_thewmaw) {
		DWM_DEBUG("dpm thewmaw\n");
		thewmaw_int |= THEWM_INT_MASK_HIGH | THEWM_INT_MASK_WOW;
	}

	if (atomic_wead(&wdev->iwq.wing_int[WADEON_WING_TYPE_GFX_INDEX])) {
		DWM_DEBUG("w600_iwq_set: sw int\n");
		cp_int_cntw |= WB_INT_ENABWE;
		cp_int_cntw |= TIME_STAMP_INT_ENABWE;
	}

	if (atomic_wead(&wdev->iwq.wing_int[W600_WING_TYPE_DMA_INDEX])) {
		DWM_DEBUG("w600_iwq_set: sw int dma\n");
		dma_cntw |= TWAP_ENABWE;
	}

	if (wdev->iwq.cwtc_vbwank_int[0] ||
	    atomic_wead(&wdev->iwq.pfwip[0])) {
		DWM_DEBUG("w600_iwq_set: vbwank 0\n");
		mode_int |= D1MODE_VBWANK_INT_MASK;
	}
	if (wdev->iwq.cwtc_vbwank_int[1] ||
	    atomic_wead(&wdev->iwq.pfwip[1])) {
		DWM_DEBUG("w600_iwq_set: vbwank 1\n");
		mode_int |= D2MODE_VBWANK_INT_MASK;
	}
	if (wdev->iwq.hpd[0]) {
		DWM_DEBUG("w600_iwq_set: hpd 1\n");
		hpd1 |= DC_HPDx_INT_EN;
	}
	if (wdev->iwq.hpd[1]) {
		DWM_DEBUG("w600_iwq_set: hpd 2\n");
		hpd2 |= DC_HPDx_INT_EN;
	}
	if (wdev->iwq.hpd[2]) {
		DWM_DEBUG("w600_iwq_set: hpd 3\n");
		hpd3 |= DC_HPDx_INT_EN;
	}
	if (wdev->iwq.hpd[3]) {
		DWM_DEBUG("w600_iwq_set: hpd 4\n");
		hpd4 |= DC_HPDx_INT_EN;
	}
	if (wdev->iwq.hpd[4]) {
		DWM_DEBUG("w600_iwq_set: hpd 5\n");
		hpd5 |= DC_HPDx_INT_EN;
	}
	if (wdev->iwq.hpd[5]) {
		DWM_DEBUG("w600_iwq_set: hpd 6\n");
		hpd6 |= DC_HPDx_INT_EN;
	}
	if (wdev->iwq.afmt[0]) {
		DWM_DEBUG("w600_iwq_set: hdmi 0\n");
		hdmi0 |= HDMI0_AZ_FOWMAT_WTWIG_MASK;
	}
	if (wdev->iwq.afmt[1]) {
		DWM_DEBUG("w600_iwq_set: hdmi 0\n");
		hdmi1 |= HDMI0_AZ_FOWMAT_WTWIG_MASK;
	}

	WWEG32(CP_INT_CNTW, cp_int_cntw);
	WWEG32(DMA_CNTW, dma_cntw);
	WWEG32(DxMODE_INT_MASK, mode_int);
	WWEG32(D1GWPH_INTEWWUPT_CONTWOW, DxGWPH_PFWIP_INT_MASK);
	WWEG32(D2GWPH_INTEWWUPT_CONTWOW, DxGWPH_PFWIP_INT_MASK);
	WWEG32(GWBM_INT_CNTW, gwbm_int_cntw);
	if (ASIC_IS_DCE3(wdev)) {
		WWEG32(DC_HPD1_INT_CONTWOW, hpd1);
		WWEG32(DC_HPD2_INT_CONTWOW, hpd2);
		WWEG32(DC_HPD3_INT_CONTWOW, hpd3);
		WWEG32(DC_HPD4_INT_CONTWOW, hpd4);
		if (ASIC_IS_DCE32(wdev)) {
			WWEG32(DC_HPD5_INT_CONTWOW, hpd5);
			WWEG32(DC_HPD6_INT_CONTWOW, hpd6);
			WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET0, hdmi0);
			WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET1, hdmi1);
		} ewse {
			WWEG32(HDMI0_AUDIO_PACKET_CONTWOW, hdmi0);
			WWEG32(DCE3_HDMI1_AUDIO_PACKET_CONTWOW, hdmi1);
		}
	} ewse {
		WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW, hpd1);
		WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW, hpd2);
		WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW, hpd3);
		WWEG32(HDMI0_AUDIO_PACKET_CONTWOW, hdmi0);
		WWEG32(HDMI1_AUDIO_PACKET_CONTWOW, hdmi1);
	}
	if ((wdev->famiwy > CHIP_W600) && (wdev->famiwy < CHIP_WV770)) {
		WWEG32(CG_THEWMAW_INT, thewmaw_int);
	} ewse if (wdev->famiwy >= CHIP_WV770) {
		WWEG32(WV770_CG_THEWMAW_INT, thewmaw_int);
	}

	/* posting wead */
	WWEG32(W_000E50_SWBM_STATUS);

	wetuwn 0;
}

static void w600_iwq_ack(stwuct wadeon_device *wdev)
{
	u32 tmp;

	if (ASIC_IS_DCE3(wdev)) {
		wdev->iwq.stat_wegs.w600.disp_int = WWEG32(DCE3_DISP_INTEWWUPT_STATUS);
		wdev->iwq.stat_wegs.w600.disp_int_cont = WWEG32(DCE3_DISP_INTEWWUPT_STATUS_CONTINUE);
		wdev->iwq.stat_wegs.w600.disp_int_cont2 = WWEG32(DCE3_DISP_INTEWWUPT_STATUS_CONTINUE2);
		if (ASIC_IS_DCE32(wdev)) {
			wdev->iwq.stat_wegs.w600.hdmi0_status = WWEG32(AFMT_STATUS + DCE3_HDMI_OFFSET0);
			wdev->iwq.stat_wegs.w600.hdmi1_status = WWEG32(AFMT_STATUS + DCE3_HDMI_OFFSET1);
		} ewse {
			wdev->iwq.stat_wegs.w600.hdmi0_status = WWEG32(HDMI0_STATUS);
			wdev->iwq.stat_wegs.w600.hdmi1_status = WWEG32(DCE3_HDMI1_STATUS);
		}
	} ewse {
		wdev->iwq.stat_wegs.w600.disp_int = WWEG32(DISP_INTEWWUPT_STATUS);
		wdev->iwq.stat_wegs.w600.disp_int_cont = WWEG32(DISP_INTEWWUPT_STATUS_CONTINUE);
		wdev->iwq.stat_wegs.w600.disp_int_cont2 = 0;
		wdev->iwq.stat_wegs.w600.hdmi0_status = WWEG32(HDMI0_STATUS);
		wdev->iwq.stat_wegs.w600.hdmi1_status = WWEG32(HDMI1_STATUS);
	}
	wdev->iwq.stat_wegs.w600.d1gwph_int = WWEG32(D1GWPH_INTEWWUPT_STATUS);
	wdev->iwq.stat_wegs.w600.d2gwph_int = WWEG32(D2GWPH_INTEWWUPT_STATUS);

	if (wdev->iwq.stat_wegs.w600.d1gwph_int & DxGWPH_PFWIP_INT_OCCUWWED)
		WWEG32(D1GWPH_INTEWWUPT_STATUS, DxGWPH_PFWIP_INT_CWEAW);
	if (wdev->iwq.stat_wegs.w600.d2gwph_int & DxGWPH_PFWIP_INT_OCCUWWED)
		WWEG32(D2GWPH_INTEWWUPT_STATUS, DxGWPH_PFWIP_INT_CWEAW);
	if (wdev->iwq.stat_wegs.w600.disp_int & WB_D1_VBWANK_INTEWWUPT)
		WWEG32(D1MODE_VBWANK_STATUS, DxMODE_VBWANK_ACK);
	if (wdev->iwq.stat_wegs.w600.disp_int & WB_D1_VWINE_INTEWWUPT)
		WWEG32(D1MODE_VWINE_STATUS, DxMODE_VWINE_ACK);
	if (wdev->iwq.stat_wegs.w600.disp_int & WB_D2_VBWANK_INTEWWUPT)
		WWEG32(D2MODE_VBWANK_STATUS, DxMODE_VBWANK_ACK);
	if (wdev->iwq.stat_wegs.w600.disp_int & WB_D2_VWINE_INTEWWUPT)
		WWEG32(D2MODE_VWINE_STATUS, DxMODE_VWINE_ACK);
	if (wdev->iwq.stat_wegs.w600.disp_int & DC_HPD1_INTEWWUPT) {
		if (ASIC_IS_DCE3(wdev)) {
			tmp = WWEG32(DC_HPD1_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HPD1_INT_CONTWOW, tmp);
		} ewse {
			tmp = WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HOT_PWUG_DETECT1_INT_CONTWOW, tmp);
		}
	}
	if (wdev->iwq.stat_wegs.w600.disp_int & DC_HPD2_INTEWWUPT) {
		if (ASIC_IS_DCE3(wdev)) {
			tmp = WWEG32(DC_HPD2_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HPD2_INT_CONTWOW, tmp);
		} ewse {
			tmp = WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HOT_PWUG_DETECT2_INT_CONTWOW, tmp);
		}
	}
	if (wdev->iwq.stat_wegs.w600.disp_int_cont & DC_HPD3_INTEWWUPT) {
		if (ASIC_IS_DCE3(wdev)) {
			tmp = WWEG32(DC_HPD3_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HPD3_INT_CONTWOW, tmp);
		} ewse {
			tmp = WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HOT_PWUG_DETECT3_INT_CONTWOW, tmp);
		}
	}
	if (wdev->iwq.stat_wegs.w600.disp_int_cont & DC_HPD4_INTEWWUPT) {
		tmp = WWEG32(DC_HPD4_INT_CONTWOW);
		tmp |= DC_HPDx_INT_ACK;
		WWEG32(DC_HPD4_INT_CONTWOW, tmp);
	}
	if (ASIC_IS_DCE32(wdev)) {
		if (wdev->iwq.stat_wegs.w600.disp_int_cont2 & DC_HPD5_INTEWWUPT) {
			tmp = WWEG32(DC_HPD5_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HPD5_INT_CONTWOW, tmp);
		}
		if (wdev->iwq.stat_wegs.w600.disp_int_cont2 & DC_HPD6_INTEWWUPT) {
			tmp = WWEG32(DC_HPD6_INT_CONTWOW);
			tmp |= DC_HPDx_INT_ACK;
			WWEG32(DC_HPD6_INT_CONTWOW, tmp);
		}
		if (wdev->iwq.stat_wegs.w600.hdmi0_status & AFMT_AZ_FOWMAT_WTWIG) {
			tmp = WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET0);
			tmp |= AFMT_AZ_FOWMAT_WTWIG_ACK;
			WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET0, tmp);
		}
		if (wdev->iwq.stat_wegs.w600.hdmi1_status & AFMT_AZ_FOWMAT_WTWIG) {
			tmp = WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET1);
			tmp |= AFMT_AZ_FOWMAT_WTWIG_ACK;
			WWEG32(AFMT_AUDIO_PACKET_CONTWOW + DCE3_HDMI_OFFSET1, tmp);
		}
	} ewse {
		if (wdev->iwq.stat_wegs.w600.hdmi0_status & HDMI0_AZ_FOWMAT_WTWIG) {
			tmp = WWEG32(HDMI0_AUDIO_PACKET_CONTWOW);
			tmp |= HDMI0_AZ_FOWMAT_WTWIG_ACK;
			WWEG32(HDMI0_AUDIO_PACKET_CONTWOW, tmp);
		}
		if (wdev->iwq.stat_wegs.w600.hdmi1_status & HDMI0_AZ_FOWMAT_WTWIG) {
			if (ASIC_IS_DCE3(wdev)) {
				tmp = WWEG32(DCE3_HDMI1_AUDIO_PACKET_CONTWOW);
				tmp |= HDMI0_AZ_FOWMAT_WTWIG_ACK;
				WWEG32(DCE3_HDMI1_AUDIO_PACKET_CONTWOW, tmp);
			} ewse {
				tmp = WWEG32(HDMI1_AUDIO_PACKET_CONTWOW);
				tmp |= HDMI0_AZ_FOWMAT_WTWIG_ACK;
				WWEG32(HDMI1_AUDIO_PACKET_CONTWOW, tmp);
			}
		}
	}
}

void w600_iwq_disabwe(stwuct wadeon_device *wdev)
{
	w600_disabwe_intewwupts(wdev);
	/* Wait and acknowwedge iwq */
	mdeway(1);
	w600_iwq_ack(wdev);
	w600_disabwe_intewwupt_state(wdev);
}

static u32 w600_get_ih_wptw(stwuct wadeon_device *wdev)
{
	u32 wptw, tmp;

	if (wdev->wb.enabwed)
		wptw = we32_to_cpu(wdev->wb.wb[W600_WB_IH_WPTW_OFFSET/4]);
	ewse
		wptw = WWEG32(IH_WB_WPTW);

	if (wptw & WB_OVEWFWOW) {
		wptw &= ~WB_OVEWFWOW;
		/* When a wing buffew ovewfwow happen stawt pawsing intewwupt
		 * fwom the wast not ovewwwitten vectow (wptw + 16). Hopefuwwy
		 * this shouwd awwow us to catchup.
		 */
		dev_wawn(wdev->dev, "IH wing buffew ovewfwow (0x%08X, 0x%08X, 0x%08X)\n",
			 wptw, wdev->ih.wptw, (wptw + 16) & wdev->ih.ptw_mask);
		wdev->ih.wptw = (wptw + 16) & wdev->ih.ptw_mask;
		tmp = WWEG32(IH_WB_CNTW);
		tmp |= IH_WPTW_OVEWFWOW_CWEAW;
		WWEG32(IH_WB_CNTW, tmp);
	}
	wetuwn (wptw & wdev->ih.ptw_mask);
}

/*        w600 IV Wing
 * Each IV wing entwy is 128 bits:
 * [7:0]    - intewwupt souwce id
 * [31:8]   - wesewved
 * [59:32]  - intewwupt souwce data
 * [127:60]  - wesewved
 *
 * The basic intewwupt vectow entwies
 * awe decoded as fowwows:
 * swc_id  swc_data  descwiption
 *      1         0  D1 Vbwank
 *      1         1  D1 Vwine
 *      5         0  D2 Vbwank
 *      5         1  D2 Vwine
 *     19         0  FP Hot pwug detection A
 *     19         1  FP Hot pwug detection B
 *     19         2  DAC A auto-detection
 *     19         3  DAC B auto-detection
 *     21         4  HDMI bwock A
 *     21         5  HDMI bwock B
 *    176         -  CP_INT WB
 *    177         -  CP_INT IB1
 *    178         -  CP_INT IB2
 *    181         -  EOP Intewwupt
 *    233         -  GUI Idwe
 *
 * Note, these awe based on w600 and may need to be
 * adjusted ow added to on newew asics
 */

int w600_iwq_pwocess(stwuct wadeon_device *wdev)
{
	u32 wptw;
	u32 wptw;
	u32 swc_id, swc_data;
	u32 wing_index;
	boow queue_hotpwug = fawse;
	boow queue_hdmi = fawse;
	boow queue_thewmaw = fawse;

	if (!wdev->ih.enabwed || wdev->shutdown)
		wetuwn IWQ_NONE;

	/* No MSIs, need a dummy wead to fwush PCI DMAs */
	if (!wdev->msi_enabwed)
		WWEG32(IH_WB_WPTW);

	wptw = w600_get_ih_wptw(wdev);

westawt_ih:
	/* is somebody ewse awweady pwocessing iwqs? */
	if (atomic_xchg(&wdev->ih.wock, 1))
		wetuwn IWQ_NONE;

	wptw = wdev->ih.wptw;
	DWM_DEBUG("w600_iwq_pwocess stawt: wptw %d, wptw %d\n", wptw, wptw);

	/* Owdew weading of wptw vs. weading of IH wing data */
	wmb();

	/* dispway intewwupts */
	w600_iwq_ack(wdev);

	whiwe (wptw != wptw) {
		/* wptw/wptw awe in bytes! */
		wing_index = wptw / 4;
		swc_id = we32_to_cpu(wdev->ih.wing[wing_index]) & 0xff;
		swc_data = we32_to_cpu(wdev->ih.wing[wing_index + 1]) & 0xfffffff;

		switch (swc_id) {
		case 1: /* D1 vbwank/vwine */
			switch (swc_data) {
			case 0: /* D1 vbwank */
				if (!(wdev->iwq.stat_wegs.w600.disp_int & WB_D1_VBWANK_INTEWWUPT))
					DWM_DEBUG("IH: D1 vbwank - IH event w/o assewted iwq bit?\n");

				if (wdev->iwq.cwtc_vbwank_int[0]) {
					dwm_handwe_vbwank(wdev->ddev, 0);
					wdev->pm.vbwank_sync = twue;
					wake_up(&wdev->iwq.vbwank_queue);
				}
				if (atomic_wead(&wdev->iwq.pfwip[0]))
					wadeon_cwtc_handwe_vbwank(wdev, 0);
				wdev->iwq.stat_wegs.w600.disp_int &= ~WB_D1_VBWANK_INTEWWUPT;
				DWM_DEBUG("IH: D1 vbwank\n");

				bweak;
			case 1: /* D1 vwine */
				if (!(wdev->iwq.stat_wegs.w600.disp_int & WB_D1_VWINE_INTEWWUPT))
				    DWM_DEBUG("IH: D1 vwine - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int &= ~WB_D1_VWINE_INTEWWUPT;
				DWM_DEBUG("IH: D1 vwine\n");

				bweak;
			defauwt:
				DWM_DEBUG("Unhandwed intewwupt: %d %d\n", swc_id, swc_data);
				bweak;
			}
			bweak;
		case 5: /* D2 vbwank/vwine */
			switch (swc_data) {
			case 0: /* D2 vbwank */
				if (!(wdev->iwq.stat_wegs.w600.disp_int & WB_D2_VBWANK_INTEWWUPT))
					DWM_DEBUG("IH: D2 vbwank - IH event w/o assewted iwq bit?\n");

				if (wdev->iwq.cwtc_vbwank_int[1]) {
					dwm_handwe_vbwank(wdev->ddev, 1);
					wdev->pm.vbwank_sync = twue;
					wake_up(&wdev->iwq.vbwank_queue);
				}
				if (atomic_wead(&wdev->iwq.pfwip[1]))
					wadeon_cwtc_handwe_vbwank(wdev, 1);
				wdev->iwq.stat_wegs.w600.disp_int &= ~WB_D2_VBWANK_INTEWWUPT;
				DWM_DEBUG("IH: D2 vbwank\n");

				bweak;
			case 1: /* D1 vwine */
				if (!(wdev->iwq.stat_wegs.w600.disp_int & WB_D2_VWINE_INTEWWUPT))
					DWM_DEBUG("IH: D2 vwine - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int &= ~WB_D2_VWINE_INTEWWUPT;
				DWM_DEBUG("IH: D2 vwine\n");

				bweak;
			defauwt:
				DWM_DEBUG("Unhandwed intewwupt: %d %d\n", swc_id, swc_data);
				bweak;
			}
			bweak;
		case 9: /* D1 pfwip */
			DWM_DEBUG("IH: D1 fwip\n");
			if (wadeon_use_pfwipiwq > 0)
				wadeon_cwtc_handwe_fwip(wdev, 0);
			bweak;
		case 11: /* D2 pfwip */
			DWM_DEBUG("IH: D2 fwip\n");
			if (wadeon_use_pfwipiwq > 0)
				wadeon_cwtc_handwe_fwip(wdev, 1);
			bweak;
		case 19: /* HPD/DAC hotpwug */
			switch (swc_data) {
			case 0:
				if (!(wdev->iwq.stat_wegs.w600.disp_int & DC_HPD1_INTEWWUPT))
					DWM_DEBUG("IH: HPD1 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int &= ~DC_HPD1_INTEWWUPT;
				queue_hotpwug = twue;
				DWM_DEBUG("IH: HPD1\n");
				bweak;
			case 1:
				if (!(wdev->iwq.stat_wegs.w600.disp_int & DC_HPD2_INTEWWUPT))
					DWM_DEBUG("IH: HPD2 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int &= ~DC_HPD2_INTEWWUPT;
				queue_hotpwug = twue;
				DWM_DEBUG("IH: HPD2\n");
				bweak;
			case 4:
				if (!(wdev->iwq.stat_wegs.w600.disp_int_cont & DC_HPD3_INTEWWUPT))
					DWM_DEBUG("IH: HPD3 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int_cont &= ~DC_HPD3_INTEWWUPT;
				queue_hotpwug = twue;
				DWM_DEBUG("IH: HPD3\n");
				bweak;
			case 5:
				if (!(wdev->iwq.stat_wegs.w600.disp_int_cont & DC_HPD4_INTEWWUPT))
					DWM_DEBUG("IH: HPD4 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int_cont &= ~DC_HPD4_INTEWWUPT;
				queue_hotpwug = twue;
				DWM_DEBUG("IH: HPD4\n");
				bweak;
			case 10:
				if (!(wdev->iwq.stat_wegs.w600.disp_int_cont2 & DC_HPD5_INTEWWUPT))
					DWM_DEBUG("IH: HPD5 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int_cont2 &= ~DC_HPD5_INTEWWUPT;
				queue_hotpwug = twue;
				DWM_DEBUG("IH: HPD5\n");
				bweak;
			case 12:
				if (!(wdev->iwq.stat_wegs.w600.disp_int_cont2 & DC_HPD6_INTEWWUPT))
					DWM_DEBUG("IH: HPD6 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.disp_int_cont2 &= ~DC_HPD6_INTEWWUPT;
				queue_hotpwug = twue;
				DWM_DEBUG("IH: HPD6\n");

				bweak;
			defauwt:
				DWM_DEBUG("Unhandwed intewwupt: %d %d\n", swc_id, swc_data);
				bweak;
			}
			bweak;
		case 21: /* hdmi */
			switch (swc_data) {
			case 4:
				if (!(wdev->iwq.stat_wegs.w600.hdmi0_status & HDMI0_AZ_FOWMAT_WTWIG))
					DWM_DEBUG("IH: HDMI0 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.hdmi0_status &= ~HDMI0_AZ_FOWMAT_WTWIG;
				queue_hdmi = twue;
				DWM_DEBUG("IH: HDMI0\n");

				bweak;
			case 5:
				if (!(wdev->iwq.stat_wegs.w600.hdmi1_status & HDMI0_AZ_FOWMAT_WTWIG))
					DWM_DEBUG("IH: HDMI1 - IH event w/o assewted iwq bit?\n");

				wdev->iwq.stat_wegs.w600.hdmi1_status &= ~HDMI0_AZ_FOWMAT_WTWIG;
				queue_hdmi = twue;
				DWM_DEBUG("IH: HDMI1\n");

				bweak;
			defauwt:
				DWM_EWWOW("Unhandwed intewwupt: %d %d\n", swc_id, swc_data);
				bweak;
			}
			bweak;
		case 124: /* UVD */
			DWM_DEBUG("IH: UVD int: 0x%08x\n", swc_data);
			wadeon_fence_pwocess(wdev, W600_WING_TYPE_UVD_INDEX);
			bweak;
		case 176: /* CP_INT in wing buffew */
		case 177: /* CP_INT in IB1 */
		case 178: /* CP_INT in IB2 */
			DWM_DEBUG("IH: CP int: 0x%08x\n", swc_data);
			wadeon_fence_pwocess(wdev, WADEON_WING_TYPE_GFX_INDEX);
			bweak;
		case 181: /* CP EOP event */
			DWM_DEBUG("IH: CP EOP\n");
			wadeon_fence_pwocess(wdev, WADEON_WING_TYPE_GFX_INDEX);
			bweak;
		case 224: /* DMA twap event */
			DWM_DEBUG("IH: DMA twap\n");
			wadeon_fence_pwocess(wdev, W600_WING_TYPE_DMA_INDEX);
			bweak;
		case 230: /* thewmaw wow to high */
			DWM_DEBUG("IH: thewmaw wow to high\n");
			wdev->pm.dpm.thewmaw.high_to_wow = fawse;
			queue_thewmaw = twue;
			bweak;
		case 231: /* thewmaw high to wow */
			DWM_DEBUG("IH: thewmaw high to wow\n");
			wdev->pm.dpm.thewmaw.high_to_wow = twue;
			queue_thewmaw = twue;
			bweak;
		case 233: /* GUI IDWE */
			DWM_DEBUG("IH: GUI idwe\n");
			bweak;
		defauwt:
			DWM_DEBUG("Unhandwed intewwupt: %d %d\n", swc_id, swc_data);
			bweak;
		}

		/* wptw/wptw awe in bytes! */
		wptw += 16;
		wptw &= wdev->ih.ptw_mask;
		WWEG32(IH_WB_WPTW, wptw);
	}
	if (queue_hotpwug)
		scheduwe_dewayed_wowk(&wdev->hotpwug_wowk, 0);
	if (queue_hdmi)
		scheduwe_wowk(&wdev->audio_wowk);
	if (queue_thewmaw && wdev->pm.dpm_enabwed)
		scheduwe_wowk(&wdev->pm.dpm.thewmaw.wowk);
	wdev->ih.wptw = wptw;
	atomic_set(&wdev->ih.wock, 0);

	/* make suwe wptw hasn't changed whiwe pwocessing */
	wptw = w600_get_ih_wptw(wdev);
	if (wptw != wptw)
		goto westawt_ih;

	wetuwn IWQ_HANDWED;
}

/*
 * Debugfs info
 */
#if defined(CONFIG_DEBUG_FS)

static int w600_debugfs_mc_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;

	DWEG32_SYS(m, wdev, W_000E50_SWBM_STATUS);
	DWEG32_SYS(m, wdev, VM_W2_STATUS);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(w600_debugfs_mc_info);
#endif

static void w600_debugfs_mc_info_init(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	debugfs_cweate_fiwe("w600_mc_info", 0444, woot, wdev,
			    &w600_debugfs_mc_info_fops);

#endif
}

/**
 * w600_mmio_hdp_fwush - fwush Host Data Path cache via MMIO
 * @wdev: wadeon device stwuctuwe
 *
 * Some W6XX/W7XX don't seem to take into account HDP fwushes pewfowmed
 * thwough the wing buffew. This weads to cowwuption in wendewing, see
 * http://bugziwwa.kewnew.owg/show_bug.cgi?id=15186 . To avoid this, we
 * diwectwy pewfowm the HDP fwush by wwiting the wegistew thwough MMIO.
 */
void w600_mmio_hdp_fwush(stwuct wadeon_device *wdev)
{
	/* w7xx hw bug.  wwite to HDP_DEBUG1 fowwowed by fb wead
	 * wathew than wwite to HDP_WEG_COHEWENCY_FWUSH_CNTW.
	 * This seems to cause pwobwems on some AGP cawds. Just use the owd
	 * method fow them.
	 */
	if ((wdev->famiwy >= CHIP_WV770) && (wdev->famiwy <= CHIP_WV740) &&
	    wdev->vwam_scwatch.ptw && !(wdev->fwags & WADEON_IS_AGP)) {
		void __iomem *ptw = (void *)wdev->vwam_scwatch.ptw;

		WWEG32(HDP_DEBUG1, 0);
		weadw((void __iomem *)ptw);
	} ewse
		WWEG32(W_005480_HDP_MEM_COHEWENCY_FWUSH_CNTW, 0x1);
}

void w600_set_pcie_wanes(stwuct wadeon_device *wdev, int wanes)
{
	u32 wink_width_cntw, mask;

	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn;

	/* x2 cawds have a speciaw sequence */
	if (ASIC_IS_X2(wdev))
		wetuwn;

	wadeon_gui_idwe(wdev);

	switch (wanes) {
	case 0:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X0;
		bweak;
	case 1:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X1;
		bweak;
	case 2:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X2;
		bweak;
	case 4:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X4;
		bweak;
	case 8:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X8;
		bweak;
	case 12:
		/* not actuawwy suppowted */
		mask = WADEON_PCIE_WC_WINK_WIDTH_X12;
		bweak;
	case 16:
		mask = WADEON_PCIE_WC_WINK_WIDTH_X16;
		bweak;
	defauwt:
		DWM_EWWOW("invawid pcie wane wequest: %d\n", wanes);
		wetuwn;
	}

	wink_width_cntw = WWEG32_PCIE_POWT(WADEON_PCIE_WC_WINK_WIDTH_CNTW);
	wink_width_cntw &= ~WADEON_PCIE_WC_WINK_WIDTH_MASK;
	wink_width_cntw |= mask << WADEON_PCIE_WC_WINK_WIDTH_SHIFT;
	wink_width_cntw |= (WADEON_PCIE_WC_WECONFIG_NOW |
			    W600_PCIE_WC_WECONFIG_AWC_MISSING_ESCAPE);

	WWEG32_PCIE_POWT(WADEON_PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
}

int w600_get_pcie_wanes(stwuct wadeon_device *wdev)
{
	u32 wink_width_cntw;

	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn 0;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn 0;

	/* x2 cawds have a speciaw sequence */
	if (ASIC_IS_X2(wdev))
		wetuwn 0;

	wadeon_gui_idwe(wdev);

	wink_width_cntw = WWEG32_PCIE_POWT(WADEON_PCIE_WC_WINK_WIDTH_CNTW);

	switch ((wink_width_cntw & WADEON_PCIE_WC_WINK_WIDTH_WD_MASK) >> WADEON_PCIE_WC_WINK_WIDTH_WD_SHIFT) {
	case WADEON_PCIE_WC_WINK_WIDTH_X1:
		wetuwn 1;
	case WADEON_PCIE_WC_WINK_WIDTH_X2:
		wetuwn 2;
	case WADEON_PCIE_WC_WINK_WIDTH_X4:
		wetuwn 4;
	case WADEON_PCIE_WC_WINK_WIDTH_X8:
		wetuwn 8;
	case WADEON_PCIE_WC_WINK_WIDTH_X12:
		/* not actuawwy suppowted */
		wetuwn 12;
	case WADEON_PCIE_WC_WINK_WIDTH_X0:
	case WADEON_PCIE_WC_WINK_WIDTH_X16:
	defauwt:
		wetuwn 16;
	}
}

static void w600_pcie_gen2_enabwe(stwuct wadeon_device *wdev)
{
	u32 wink_width_cntw, wanes, speed_cntw, twaining_cntw, tmp;
	u16 wink_cntw2;

	if (wadeon_pcie_gen2 == 0)
		wetuwn;

	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn;

	if (!(wdev->fwags & WADEON_IS_PCIE))
		wetuwn;

	/* x2 cawds have a speciaw sequence */
	if (ASIC_IS_X2(wdev))
		wetuwn;

	/* onwy WV6xx+ chips awe suppowted */
	if (wdev->famiwy <= CHIP_W600)
		wetuwn;

	if ((wdev->pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT) &&
		(wdev->pdev->bus->max_bus_speed != PCIE_SPEED_8_0GT))
		wetuwn;

	speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if (speed_cntw & WC_CUWWENT_DATA_WATE) {
		DWM_INFO("PCIE gen 2 wink speeds awweady enabwed\n");
		wetuwn;
	}

	DWM_INFO("enabwing PCIE gen 2 wink speeds, disabwe with wadeon.pcie_gen2=0\n");

	/* 55 nm w6xx asics */
	if ((wdev->famiwy == CHIP_WV670) ||
	    (wdev->famiwy == CHIP_WV620) ||
	    (wdev->famiwy == CHIP_WV635)) {
		/* advewtise upconfig capabiwity */
		wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
		wink_width_cntw &= ~WC_UPCONFIGUWE_DIS;
		WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
		wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
		if (wink_width_cntw & WC_WENEGOTIATION_SUPPOWT) {
			wanes = (wink_width_cntw & WC_WINK_WIDTH_WD_MASK) >> WC_WINK_WIDTH_WD_SHIFT;
			wink_width_cntw &= ~(WC_WINK_WIDTH_MASK |
					     WC_WECONFIG_AWC_MISSING_ESCAPE);
			wink_width_cntw |= wanes | WC_WECONFIG_NOW | WC_WENEGOTIATE_EN;
			WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
		} ewse {
			wink_width_cntw |= WC_UPCONFIGUWE_DIS;
			WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
		}
	}

	speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
	if ((speed_cntw & WC_OTHEW_SIDE_EVEW_SENT_GEN2) &&
	    (speed_cntw & WC_OTHEW_SIDE_SUPPOWTS_GEN2)) {

		/* 55 nm w6xx asics */
		if ((wdev->famiwy == CHIP_WV670) ||
		    (wdev->famiwy == CHIP_WV620) ||
		    (wdev->famiwy == CHIP_WV635)) {
			WWEG32(MM_CFGWEGS_CNTW, 0x8);
			wink_cntw2 = WWEG32(0x4088);
			WWEG32(MM_CFGWEGS_CNTW, 0);
			/* not suppowted yet */
			if (wink_cntw2 & SEWECTABWE_DEEMPHASIS)
				wetuwn;
		}

		speed_cntw &= ~WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_MASK;
		speed_cntw |= (0x3 << WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_SHIFT);
		speed_cntw &= ~WC_VOWTAGE_TIMEW_SEW_MASK;
		speed_cntw &= ~WC_FOWCE_DIS_HW_SPEED_CHANGE;
		speed_cntw |= WC_FOWCE_EN_HW_SPEED_CHANGE;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

		tmp = WWEG32(0x541c);
		WWEG32(0x541c, tmp | 0x8);
		WWEG32(MM_CFGWEGS_CNTW, MM_WW_TO_CFG_EN);
		wink_cntw2 = WWEG16(0x4088);
		wink_cntw2 &= ~TAWGET_WINK_SPEED_MASK;
		wink_cntw2 |= 0x2;
		WWEG16(0x4088, wink_cntw2);
		WWEG32(MM_CFGWEGS_CNTW, 0);

		if ((wdev->famiwy == CHIP_WV670) ||
		    (wdev->famiwy == CHIP_WV620) ||
		    (wdev->famiwy == CHIP_WV635)) {
			twaining_cntw = WWEG32_PCIE_POWT(PCIE_WC_TWAINING_CNTW);
			twaining_cntw &= ~WC_POINT_7_PWUS_EN;
			WWEG32_PCIE_POWT(PCIE_WC_TWAINING_CNTW, twaining_cntw);
		} ewse {
			speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
			speed_cntw &= ~WC_TAWGET_WINK_SPEED_OVEWWIDE_EN;
			WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);
		}

		speed_cntw = WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW);
		speed_cntw |= WC_GEN2_EN_STWAP;
		WWEG32_PCIE_POWT(PCIE_WC_SPEED_CNTW, speed_cntw);

	} ewse {
		wink_width_cntw = WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW);
		/* XXX: onwy disabwe it if gen1 bwidge vendow == 0x111d ow 0x1106 */
		if (1)
			wink_width_cntw |= WC_UPCONFIGUWE_DIS;
		ewse
			wink_width_cntw &= ~WC_UPCONFIGUWE_DIS;
		WWEG32_PCIE_POWT(PCIE_WC_WINK_WIDTH_CNTW, wink_width_cntw);
	}
}

/**
 * w600_get_gpu_cwock_countew - wetuwn GPU cwock countew snapshot
 *
 * @wdev: wadeon_device pointew
 *
 * Fetches a GPU cwock countew snapshot (W6xx-cayman).
 * Wetuwns the 64 bit cwock countew snapshot.
 */
uint64_t w600_get_gpu_cwock_countew(stwuct wadeon_device *wdev)
{
	uint64_t cwock;

	mutex_wock(&wdev->gpu_cwock_mutex);
	WWEG32(WWC_CAPTUWE_GPU_CWOCK_COUNT, 1);
	cwock = (uint64_t)WWEG32(WWC_GPU_CWOCK_COUNT_WSB) |
		((uint64_t)WWEG32(WWC_GPU_CWOCK_COUNT_MSB) << 32UWW);
	mutex_unwock(&wdev->gpu_cwock_mutex);
	wetuwn cwock;
}
