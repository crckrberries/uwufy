/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "amdgpu.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_i2c.h"
#incwude "atom.h"
#incwude "amdgpu_atombios.h"
#incwude "atombios_cwtc.h"
#incwude "atombios_encodews.h"
#incwude "amdgpu_pww.h"
#incwude "amdgpu_connectows.h"
#incwude "amdgpu_dispway.h"

#incwude "bif/bif_3_0_d.h"
#incwude "bif/bif_3_0_sh_mask.h"
#incwude "oss/oss_1_0_d.h"
#incwude "oss/oss_1_0_sh_mask.h"
#incwude "gca/gfx_6_0_d.h"
#incwude "gca/gfx_6_0_sh_mask.h"
#incwude "gmc/gmc_6_0_d.h"
#incwude "gmc/gmc_6_0_sh_mask.h"
#incwude "dce/dce_6_0_d.h"
#incwude "dce/dce_6_0_sh_mask.h"
#incwude "gca/gfx_7_2_enum.h"
#incwude "dce_v6_0.h"
#incwude "si_enums.h"

static void dce_v6_0_set_dispway_funcs(stwuct amdgpu_device *adev);
static void dce_v6_0_set_iwq_funcs(stwuct amdgpu_device *adev);

static const u32 cwtc_offsets[6] =
{
	SI_CWTC0_WEGISTEW_OFFSET,
	SI_CWTC1_WEGISTEW_OFFSET,
	SI_CWTC2_WEGISTEW_OFFSET,
	SI_CWTC3_WEGISTEW_OFFSET,
	SI_CWTC4_WEGISTEW_OFFSET,
	SI_CWTC5_WEGISTEW_OFFSET
};

static const u32 hpd_offsets[] =
{
	mmDC_HPD1_INT_STATUS - mmDC_HPD1_INT_STATUS,
	mmDC_HPD2_INT_STATUS - mmDC_HPD1_INT_STATUS,
	mmDC_HPD3_INT_STATUS - mmDC_HPD1_INT_STATUS,
	mmDC_HPD4_INT_STATUS - mmDC_HPD1_INT_STATUS,
	mmDC_HPD5_INT_STATUS - mmDC_HPD1_INT_STATUS,
	mmDC_HPD6_INT_STATUS - mmDC_HPD1_INT_STATUS,
};

static const uint32_t dig_offsets[] = {
	SI_CWTC0_WEGISTEW_OFFSET,
	SI_CWTC1_WEGISTEW_OFFSET,
	SI_CWTC2_WEGISTEW_OFFSET,
	SI_CWTC3_WEGISTEW_OFFSET,
	SI_CWTC4_WEGISTEW_OFFSET,
	SI_CWTC5_WEGISTEW_OFFSET,
	(0x13830 - 0x7030) >> 2,
};

static const stwuct {
	uint32_t	weg;
	uint32_t	vbwank;
	uint32_t	vwine;
	uint32_t	hpd;

} intewwupt_status_offsets[6] = { {
	.weg = mmDISP_INTEWWUPT_STATUS,
	.vbwank = DISP_INTEWWUPT_STATUS__WB_D1_VBWANK_INTEWWUPT_MASK,
	.vwine = DISP_INTEWWUPT_STATUS__WB_D1_VWINE_INTEWWUPT_MASK,
	.hpd = DISP_INTEWWUPT_STATUS__DC_HPD1_INTEWWUPT_MASK
}, {
	.weg = mmDISP_INTEWWUPT_STATUS_CONTINUE,
	.vbwank = DISP_INTEWWUPT_STATUS_CONTINUE__WB_D2_VBWANK_INTEWWUPT_MASK,
	.vwine = DISP_INTEWWUPT_STATUS_CONTINUE__WB_D2_VWINE_INTEWWUPT_MASK,
	.hpd = DISP_INTEWWUPT_STATUS_CONTINUE__DC_HPD2_INTEWWUPT_MASK
}, {
	.weg = mmDISP_INTEWWUPT_STATUS_CONTINUE2,
	.vbwank = DISP_INTEWWUPT_STATUS_CONTINUE2__WB_D3_VBWANK_INTEWWUPT_MASK,
	.vwine = DISP_INTEWWUPT_STATUS_CONTINUE2__WB_D3_VWINE_INTEWWUPT_MASK,
	.hpd = DISP_INTEWWUPT_STATUS_CONTINUE2__DC_HPD3_INTEWWUPT_MASK
}, {
	.weg = mmDISP_INTEWWUPT_STATUS_CONTINUE3,
	.vbwank = DISP_INTEWWUPT_STATUS_CONTINUE3__WB_D4_VBWANK_INTEWWUPT_MASK,
	.vwine = DISP_INTEWWUPT_STATUS_CONTINUE3__WB_D4_VWINE_INTEWWUPT_MASK,
	.hpd = DISP_INTEWWUPT_STATUS_CONTINUE3__DC_HPD4_INTEWWUPT_MASK
}, {
	.weg = mmDISP_INTEWWUPT_STATUS_CONTINUE4,
	.vbwank = DISP_INTEWWUPT_STATUS_CONTINUE4__WB_D5_VBWANK_INTEWWUPT_MASK,
	.vwine = DISP_INTEWWUPT_STATUS_CONTINUE4__WB_D5_VWINE_INTEWWUPT_MASK,
	.hpd = DISP_INTEWWUPT_STATUS_CONTINUE4__DC_HPD5_INTEWWUPT_MASK
}, {
	.weg = mmDISP_INTEWWUPT_STATUS_CONTINUE5,
	.vbwank = DISP_INTEWWUPT_STATUS_CONTINUE5__WB_D6_VBWANK_INTEWWUPT_MASK,
	.vwine = DISP_INTEWWUPT_STATUS_CONTINUE5__WB_D6_VWINE_INTEWWUPT_MASK,
	.hpd = DISP_INTEWWUPT_STATUS_CONTINUE5__DC_HPD6_INTEWWUPT_MASK
} };

static u32 dce_v6_0_audio_endpt_wweg(stwuct amdgpu_device *adev,
				     u32 bwock_offset, u32 weg)
{
	unsigned wong fwags;
	u32 w;

	spin_wock_iwqsave(&adev->audio_endpt_idx_wock, fwags);
	WWEG32(mmAZAWIA_F0_CODEC_ENDPOINT_INDEX + bwock_offset, weg);
	w = WWEG32(mmAZAWIA_F0_CODEC_ENDPOINT_DATA + bwock_offset);
	spin_unwock_iwqwestowe(&adev->audio_endpt_idx_wock, fwags);

	wetuwn w;
}

static void dce_v6_0_audio_endpt_wweg(stwuct amdgpu_device *adev,
				      u32 bwock_offset, u32 weg, u32 v)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adev->audio_endpt_idx_wock, fwags);
	WWEG32(mmAZAWIA_F0_CODEC_ENDPOINT_INDEX + bwock_offset,
		weg | AZAWIA_F0_CODEC_ENDPOINT_INDEX__AZAWIA_ENDPOINT_WEG_WWITE_EN_MASK);
	WWEG32(mmAZAWIA_F0_CODEC_ENDPOINT_DATA + bwock_offset, v);
	spin_unwock_iwqwestowe(&adev->audio_endpt_idx_wock, fwags);
}

static u32 dce_v6_0_vbwank_get_countew(stwuct amdgpu_device *adev, int cwtc)
{
	if (cwtc >= adev->mode_info.num_cwtc)
		wetuwn 0;
	ewse
		wetuwn WWEG32(mmCWTC_STATUS_FWAME_COUNT + cwtc_offsets[cwtc]);
}

static void dce_v6_0_pagefwip_intewwupt_init(stwuct amdgpu_device *adev)
{
	unsigned i;

	/* Enabwe pfwip intewwupts */
	fow (i = 0; i < adev->mode_info.num_cwtc; i++)
		amdgpu_iwq_get(adev, &adev->pagefwip_iwq, i);
}

static void dce_v6_0_pagefwip_intewwupt_fini(stwuct amdgpu_device *adev)
{
	unsigned i;

	/* Disabwe pfwip intewwupts */
	fow (i = 0; i < adev->mode_info.num_cwtc; i++)
		amdgpu_iwq_put(adev, &adev->pagefwip_iwq, i);
}

/**
 * dce_v6_0_page_fwip - pagefwip cawwback.
 *
 * @adev: amdgpu_device pointew
 * @cwtc_id: cwtc to cweanup pagefwip on
 * @cwtc_base: new addwess of the cwtc (GPU MC addwess)
 * @async: asynchwonous fwip
 *
 * Does the actuaw pagefwip (evewgween+).
 * Duwing vbwank we take the cwtc wock and wait fow the update_pending
 * bit to go high, when it does, we wewease the wock, and awwow the
 * doubwe buffewed update to take pwace.
 * Wetuwns the cuwwent update pending status.
 */
static void dce_v6_0_page_fwip(stwuct amdgpu_device *adev,
			       int cwtc_id, u64 cwtc_base, boow async)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = adev->mode_info.cwtcs[cwtc_id];
	stwuct dwm_fwamebuffew *fb = amdgpu_cwtc->base.pwimawy->fb;

	/* fwip at hsync fow async, defauwt is vsync */
	WWEG32(mmGWPH_FWIP_CONTWOW + amdgpu_cwtc->cwtc_offset, async ?
	       GWPH_FWIP_CONTWOW__GWPH_SUWFACE_UPDATE_H_WETWACE_EN_MASK : 0);
	/* update pitch */
	WWEG32(mmGWPH_PITCH + amdgpu_cwtc->cwtc_offset,
	       fb->pitches[0] / fb->fowmat->cpp[0]);
	/* update the scanout addwesses */
	WWEG32(mmGWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH + amdgpu_cwtc->cwtc_offset,
	       uppew_32_bits(cwtc_base));
	WWEG32(mmGWPH_PWIMAWY_SUWFACE_ADDWESS + amdgpu_cwtc->cwtc_offset,
	       (u32)cwtc_base);

	/* post the wwite */
	WWEG32(mmGWPH_PWIMAWY_SUWFACE_ADDWESS + amdgpu_cwtc->cwtc_offset);
}

static int dce_v6_0_cwtc_get_scanoutpos(stwuct amdgpu_device *adev, int cwtc,
					u32 *vbw, u32 *position)
{
	if ((cwtc < 0) || (cwtc >= adev->mode_info.num_cwtc))
		wetuwn -EINVAW;
	*vbw = WWEG32(mmCWTC_V_BWANK_STAWT_END + cwtc_offsets[cwtc]);
	*position = WWEG32(mmCWTC_STATUS_POSITION + cwtc_offsets[cwtc]);

	wetuwn 0;

}

/**
 * dce_v6_0_hpd_sense - hpd sense cawwback.
 *
 * @adev: amdgpu_device pointew
 * @hpd: hpd (hotpwug detect) pin
 *
 * Checks if a digitaw monitow is connected (evewgween+).
 * Wetuwns twue if connected, fawse if not connected.
 */
static boow dce_v6_0_hpd_sense(stwuct amdgpu_device *adev,
			       enum amdgpu_hpd_id hpd)
{
	boow connected = fawse;

	if (hpd >= adev->mode_info.num_hpd)
		wetuwn connected;

	if (WWEG32(mmDC_HPD1_INT_STATUS + hpd_offsets[hpd]) & DC_HPD1_INT_STATUS__DC_HPD1_SENSE_MASK)
		connected = twue;

	wetuwn connected;
}

/**
 * dce_v6_0_hpd_set_powawity - hpd set powawity cawwback.
 *
 * @adev: amdgpu_device pointew
 * @hpd: hpd (hotpwug detect) pin
 *
 * Set the powawity of the hpd pin (evewgween+).
 */
static void dce_v6_0_hpd_set_powawity(stwuct amdgpu_device *adev,
				      enum amdgpu_hpd_id hpd)
{
	u32 tmp;
	boow connected = dce_v6_0_hpd_sense(adev, hpd);

	if (hpd >= adev->mode_info.num_hpd)
		wetuwn;

	tmp = WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[hpd]);
	if (connected)
		tmp &= ~DC_HPD1_INT_CONTWOW__DC_HPD1_INT_POWAWITY_MASK;
	ewse
		tmp |= DC_HPD1_INT_CONTWOW__DC_HPD1_INT_POWAWITY_MASK;
	WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[hpd], tmp);
}

/**
 * dce_v6_0_hpd_init - hpd setup cawwback.
 *
 * @adev: amdgpu_device pointew
 *
 * Setup the hpd pins used by the cawd (evewgween+).
 * Enabwe the pin, set the powawity, and enabwe the hpd intewwupts.
 */
static void dce_v6_0_hpd_init(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	u32 tmp;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);

		if (amdgpu_connectow->hpd.hpd >= adev->mode_info.num_hpd)
			continue;

		tmp = WWEG32(mmDC_HPD1_CONTWOW + hpd_offsets[amdgpu_connectow->hpd.hpd]);
		tmp |= DC_HPD1_CONTWOW__DC_HPD1_EN_MASK;
		WWEG32(mmDC_HPD1_CONTWOW + hpd_offsets[amdgpu_connectow->hpd.hpd], tmp);

		if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP ||
		    connectow->connectow_type == DWM_MODE_CONNECTOW_WVDS) {
			/* don't twy to enabwe hpd on eDP ow WVDS avoid bweaking the
			 * aux dp channew on imac and hewp (but not compwetewy fix)
			 * https://bugziwwa.wedhat.com/show_bug.cgi?id=726143
			 * awso avoid intewwupt stowms duwing dpms.
			 */
			tmp = WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[amdgpu_connectow->hpd.hpd]);
			tmp &= ~DC_HPD1_INT_CONTWOW__DC_HPD1_INT_EN_MASK;
			WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[amdgpu_connectow->hpd.hpd], tmp);
			continue;
		}

		dce_v6_0_hpd_set_powawity(adev, amdgpu_connectow->hpd.hpd);
		amdgpu_iwq_get(adev, &adev->hpd_iwq, amdgpu_connectow->hpd.hpd);
	}
	dwm_connectow_wist_itew_end(&itew);
}

/**
 * dce_v6_0_hpd_fini - hpd teaw down cawwback.
 *
 * @adev: amdgpu_device pointew
 *
 * Teaw down the hpd pins used by the cawd (evewgween+).
 * Disabwe the hpd intewwupts.
 */
static void dce_v6_0_hpd_fini(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	u32 tmp;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);

		if (amdgpu_connectow->hpd.hpd >= adev->mode_info.num_hpd)
			continue;

		tmp = WWEG32(mmDC_HPD1_CONTWOW + hpd_offsets[amdgpu_connectow->hpd.hpd]);
		tmp &= ~DC_HPD1_CONTWOW__DC_HPD1_EN_MASK;
		WWEG32(mmDC_HPD1_CONTWOW + hpd_offsets[amdgpu_connectow->hpd.hpd], tmp);

		amdgpu_iwq_put(adev, &adev->hpd_iwq, amdgpu_connectow->hpd.hpd);
	}
	dwm_connectow_wist_itew_end(&itew);
}

static u32 dce_v6_0_hpd_get_gpio_weg(stwuct amdgpu_device *adev)
{
	wetuwn mmDC_GPIO_HPD_A;
}

static void dce_v6_0_set_vga_wendew_state(stwuct amdgpu_device *adev,
					  boow wendew)
{
	if (!wendew)
		WWEG32(mmVGA_WENDEW_CONTWOW,
			WWEG32(mmVGA_WENDEW_CONTWOW) & VGA_VSTATUS_CNTW);

}

static int dce_v6_0_get_num_cwtc(stwuct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
		wetuwn 6;
	case CHIP_OWAND:
		wetuwn 2;
	defauwt:
		wetuwn 0;
	}
}

void dce_v6_0_disabwe_dce(stwuct amdgpu_device *adev)
{
	/*Disabwe VGA wendew and enabwed cwtc, if has DCE engine*/
	if (amdgpu_atombios_has_dce_engine_info(adev)) {
		u32 tmp;
		int cwtc_enabwed, i;

		dce_v6_0_set_vga_wendew_state(adev, fawse);

		/*Disabwe cwtc*/
		fow (i = 0; i < dce_v6_0_get_num_cwtc(adev); i++) {
			cwtc_enabwed = WWEG32(mmCWTC_CONTWOW + cwtc_offsets[i]) &
				CWTC_CONTWOW__CWTC_MASTEW_EN_MASK;
			if (cwtc_enabwed) {
				WWEG32(mmCWTC_UPDATE_WOCK + cwtc_offsets[i], 1);
				tmp = WWEG32(mmCWTC_CONTWOW + cwtc_offsets[i]);
				tmp &= ~CWTC_CONTWOW__CWTC_MASTEW_EN_MASK;
				WWEG32(mmCWTC_CONTWOW + cwtc_offsets[i], tmp);
				WWEG32(mmCWTC_UPDATE_WOCK + cwtc_offsets[i], 0);
			}
		}
	}
}

static void dce_v6_0_pwogwam_fmt(stwuct dwm_encodew *encodew)
{

	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct dwm_connectow *connectow = amdgpu_get_connectow_fow_encodew(encodew);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(encodew->cwtc);
	int bpc = 0;
	u32 tmp = 0;
	enum amdgpu_connectow_dithew dithew = AMDGPU_FMT_DITHEW_DISABWE;

	if (connectow) {
		stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);
		bpc = amdgpu_connectow_get_monitow_bpc(connectow);
		dithew = amdgpu_connectow->dithew;
	}

	/* WVDS FMT is set up by atom */
	if (amdgpu_encodew->devices & ATOM_DEVICE_WCD_SUPPOWT)
		wetuwn;

	if (bpc == 0)
		wetuwn;


	switch (bpc) {
	case 6:
		if (dithew == AMDGPU_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= (FMT_BIT_DEPTH_CONTWOW__FMT_FWAME_WANDOM_ENABWE_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_HIGHPASS_WANDOM_ENABWE_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_SPATIAW_DITHEW_EN_MASK);
		ewse
			tmp |= FMT_BIT_DEPTH_CONTWOW__FMT_TWUNCATE_EN_MASK;
		bweak;
	case 8:
		if (dithew == AMDGPU_FMT_DITHEW_ENABWE)
			/* XXX sowt out optimaw dithew settings */
			tmp |= (FMT_BIT_DEPTH_CONTWOW__FMT_FWAME_WANDOM_ENABWE_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_HIGHPASS_WANDOM_ENABWE_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_WGB_WANDOM_ENABWE_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_SPATIAW_DITHEW_EN_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_SPATIAW_DITHEW_DEPTH_MASK);
		ewse
			tmp |= (FMT_BIT_DEPTH_CONTWOW__FMT_TWUNCATE_EN_MASK |
				FMT_BIT_DEPTH_CONTWOW__FMT_TWUNCATE_DEPTH_MASK);
		bweak;
	case 10:
	defauwt:
		/* not needed */
		bweak;
	}

	WWEG32(mmFMT_BIT_DEPTH_CONTWOW + amdgpu_cwtc->cwtc_offset, tmp);
}

/**
 * si_get_numbew_of_dwam_channews - get the numbew of dwam channews
 *
 * @adev: amdgpu_device pointew
 *
 * Wook up the numbew of video wam channews (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the numbew of dwam channews
 */
static u32 si_get_numbew_of_dwam_channews(stwuct amdgpu_device *adev)
{
	u32 tmp = WWEG32(mmMC_SHAWED_CHMAP);

	switch ((tmp & MC_SHAWED_CHMAP__NOOFCHAN_MASK) >> MC_SHAWED_CHMAP__NOOFCHAN__SHIFT) {
	case 0:
	defauwt:
		wetuwn 1;
	case 1:
		wetuwn 2;
	case 2:
		wetuwn 4;
	case 3:
		wetuwn 8;
	case 4:
		wetuwn 3;
	case 5:
		wetuwn 6;
	case 6:
		wetuwn 10;
	case 7:
		wetuwn 12;
	case 8:
		wetuwn 16;
	}
}

stwuct dce6_wm_pawams {
	u32 dwam_channews; /* numbew of dwam channews */
	u32 ycwk;          /* bandwidth pew dwam data pin in kHz */
	u32 scwk;          /* engine cwock in kHz */
	u32 disp_cwk;      /* dispway cwock in kHz */
	u32 swc_width;     /* viewpowt width */
	u32 active_time;   /* active dispway time in ns */
	u32 bwank_time;    /* bwank time in ns */
	boow intewwaced;    /* mode is intewwaced */
	fixed20_12 vsc;    /* vewticaw scawe watio */
	u32 num_heads;     /* numbew of active cwtcs */
	u32 bytes_pew_pixew; /* bytes pew pixew dispway + ovewway */
	u32 wb_size;       /* wine buffew awwocated to pipe */
	u32 vtaps;         /* vewticaw scawew taps */
};

/**
 * dce_v6_0_dwam_bandwidth - get the dwam bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the waw dwam bandwidth (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the dwam bandwidth in MBytes/s
 */
static u32 dce_v6_0_dwam_bandwidth(stwuct dce6_wm_pawams *wm)
{
	/* Cawcuwate waw DWAM Bandwidth */
	fixed20_12 dwam_efficiency; /* 0.7 */
	fixed20_12 ycwk, dwam_channews, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	ycwk.fuww = dfixed_const(wm->ycwk);
	ycwk.fuww = dfixed_div(ycwk, a);
	dwam_channews.fuww = dfixed_const(wm->dwam_channews * 4);
	a.fuww = dfixed_const(10);
	dwam_efficiency.fuww = dfixed_const(7);
	dwam_efficiency.fuww = dfixed_div(dwam_efficiency, a);
	bandwidth.fuww = dfixed_muw(dwam_channews, ycwk);
	bandwidth.fuww = dfixed_muw(bandwidth, dwam_efficiency);

	wetuwn dfixed_twunc(bandwidth);
}

/**
 * dce_v6_0_dwam_bandwidth_fow_dispway - get the dwam bandwidth fow dispway
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the dwam bandwidth used fow dispway (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the dwam bandwidth fow dispway in MBytes/s
 */
static u32 dce_v6_0_dwam_bandwidth_fow_dispway(stwuct dce6_wm_pawams *wm)
{
	/* Cawcuwate DWAM Bandwidth and the pawt awwocated to dispway. */
	fixed20_12 disp_dwam_awwocation; /* 0.3 to 0.7 */
	fixed20_12 ycwk, dwam_channews, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	ycwk.fuww = dfixed_const(wm->ycwk);
	ycwk.fuww = dfixed_div(ycwk, a);
	dwam_channews.fuww = dfixed_const(wm->dwam_channews * 4);
	a.fuww = dfixed_const(10);
	disp_dwam_awwocation.fuww = dfixed_const(3); /* XXX wowse case vawue 0.3 */
	disp_dwam_awwocation.fuww = dfixed_div(disp_dwam_awwocation, a);
	bandwidth.fuww = dfixed_muw(dwam_channews, ycwk);
	bandwidth.fuww = dfixed_muw(bandwidth, disp_dwam_awwocation);

	wetuwn dfixed_twunc(bandwidth);
}

/**
 * dce_v6_0_data_wetuwn_bandwidth - get the data wetuwn bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the data wetuwn bandwidth used fow dispway (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the data wetuwn bandwidth in MBytes/s
 */
static u32 dce_v6_0_data_wetuwn_bandwidth(stwuct dce6_wm_pawams *wm)
{
	/* Cawcuwate the dispway Data wetuwn Bandwidth */
	fixed20_12 wetuwn_efficiency; /* 0.8 */
	fixed20_12 scwk, bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	scwk.fuww = dfixed_const(wm->scwk);
	scwk.fuww = dfixed_div(scwk, a);
	a.fuww = dfixed_const(10);
	wetuwn_efficiency.fuww = dfixed_const(8);
	wetuwn_efficiency.fuww = dfixed_div(wetuwn_efficiency, a);
	a.fuww = dfixed_const(32);
	bandwidth.fuww = dfixed_muw(a, scwk);
	bandwidth.fuww = dfixed_muw(bandwidth, wetuwn_efficiency);

	wetuwn dfixed_twunc(bandwidth);
}

/**
 * dce_v6_0_dmif_wequest_bandwidth - get the dmif bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the dmif bandwidth used fow dispway (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the dmif bandwidth in MBytes/s
 */
static u32 dce_v6_0_dmif_wequest_bandwidth(stwuct dce6_wm_pawams *wm)
{
	/* Cawcuwate the DMIF Wequest Bandwidth */
	fixed20_12 disp_cwk_wequest_efficiency; /* 0.8 */
	fixed20_12 disp_cwk, bandwidth;
	fixed20_12 a, b;

	a.fuww = dfixed_const(1000);
	disp_cwk.fuww = dfixed_const(wm->disp_cwk);
	disp_cwk.fuww = dfixed_div(disp_cwk, a);
	a.fuww = dfixed_const(32);
	b.fuww = dfixed_muw(a, disp_cwk);

	a.fuww = dfixed_const(10);
	disp_cwk_wequest_efficiency.fuww = dfixed_const(8);
	disp_cwk_wequest_efficiency.fuww = dfixed_div(disp_cwk_wequest_efficiency, a);

	bandwidth.fuww = dfixed_muw(b, disp_cwk_wequest_efficiency);

	wetuwn dfixed_twunc(bandwidth);
}

/**
 * dce_v6_0_avaiwabwe_bandwidth - get the min avaiwabwe bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the min avaiwabwe bandwidth used fow dispway (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the min avaiwabwe bandwidth in MBytes/s
 */
static u32 dce_v6_0_avaiwabwe_bandwidth(stwuct dce6_wm_pawams *wm)
{
	/* Cawcuwate the Avaiwabwe bandwidth. Dispway can use this tempowawiwy but not in avewage. */
	u32 dwam_bandwidth = dce_v6_0_dwam_bandwidth(wm);
	u32 data_wetuwn_bandwidth = dce_v6_0_data_wetuwn_bandwidth(wm);
	u32 dmif_weq_bandwidth = dce_v6_0_dmif_wequest_bandwidth(wm);

	wetuwn min(dwam_bandwidth, min(data_wetuwn_bandwidth, dmif_weq_bandwidth));
}

/**
 * dce_v6_0_avewage_bandwidth - get the avewage avaiwabwe bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the avewage avaiwabwe bandwidth used fow dispway (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the avewage avaiwabwe bandwidth in MBytes/s
 */
static u32 dce_v6_0_avewage_bandwidth(stwuct dce6_wm_pawams *wm)
{
	/* Cawcuwate the dispway mode Avewage Bandwidth
	 * DispwayMode shouwd contain the souwce and destination dimensions,
	 * timing, etc.
	 */
	fixed20_12 bpp;
	fixed20_12 wine_time;
	fixed20_12 swc_width;
	fixed20_12 bandwidth;
	fixed20_12 a;

	a.fuww = dfixed_const(1000);
	wine_time.fuww = dfixed_const(wm->active_time + wm->bwank_time);
	wine_time.fuww = dfixed_div(wine_time, a);
	bpp.fuww = dfixed_const(wm->bytes_pew_pixew);
	swc_width.fuww = dfixed_const(wm->swc_width);
	bandwidth.fuww = dfixed_muw(swc_width, bpp);
	bandwidth.fuww = dfixed_muw(bandwidth, wm->vsc);
	bandwidth.fuww = dfixed_div(bandwidth, wine_time);

	wetuwn dfixed_twunc(bandwidth);
}

/**
 * dce_v6_0_watency_watewmawk - get the watency watewmawk
 *
 * @wm: watewmawk cawcuwation data
 *
 * Cawcuwate the watency watewmawk (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns the watency watewmawk in ns
 */
static u32 dce_v6_0_watency_watewmawk(stwuct dce6_wm_pawams *wm)
{
	/* Fiwst cawcuwate the watency in ns */
	u32 mc_watency = 2000; /* 2000 ns. */
	u32 avaiwabwe_bandwidth = dce_v6_0_avaiwabwe_bandwidth(wm);
	u32 wowst_chunk_wetuwn_time = (512 * 8 * 1000) / avaiwabwe_bandwidth;
	u32 cuwsow_wine_paiw_wetuwn_time = (128 * 4 * 1000) / avaiwabwe_bandwidth;
	u32 dc_watency = 40000000 / wm->disp_cwk; /* dc pipe watency */
	u32 othew_heads_data_wetuwn_time = ((wm->num_heads + 1) * wowst_chunk_wetuwn_time) +
		(wm->num_heads * cuwsow_wine_paiw_wetuwn_time);
	u32 watency = mc_watency + othew_heads_data_wetuwn_time + dc_watency;
	u32 max_swc_wines_pew_dst_wine, wb_fiww_bw, wine_fiww_time;
	u32 tmp, dmif_size = 12288;
	fixed20_12 a, b, c;

	if (wm->num_heads == 0)
		wetuwn 0;

	a.fuww = dfixed_const(2);
	b.fuww = dfixed_const(1);
	if ((wm->vsc.fuww > a.fuww) ||
	    ((wm->vsc.fuww > b.fuww) && (wm->vtaps >= 3)) ||
	    (wm->vtaps >= 5) ||
	    ((wm->vsc.fuww >= a.fuww) && wm->intewwaced))
		max_swc_wines_pew_dst_wine = 4;
	ewse
		max_swc_wines_pew_dst_wine = 2;

	a.fuww = dfixed_const(avaiwabwe_bandwidth);
	b.fuww = dfixed_const(wm->num_heads);
	a.fuww = dfixed_div(a, b);
	tmp = div_u64((u64) dmif_size * (u64) wm->disp_cwk, mc_watency + 512);
	tmp = min(dfixed_twunc(a), tmp);

	wb_fiww_bw = min(tmp, wm->disp_cwk * wm->bytes_pew_pixew / 1000);

	a.fuww = dfixed_const(max_swc_wines_pew_dst_wine * wm->swc_width * wm->bytes_pew_pixew);
	b.fuww = dfixed_const(1000);
	c.fuww = dfixed_const(wb_fiww_bw);
	b.fuww = dfixed_div(c, b);
	a.fuww = dfixed_div(a, b);
	wine_fiww_time = dfixed_twunc(a);

	if (wine_fiww_time < wm->active_time)
		wetuwn watency;
	ewse
		wetuwn watency + (wine_fiww_time - wm->active_time);

}

/**
 * dce_v6_0_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway - check
 * avewage and avaiwabwe dwam bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Check if the dispway avewage bandwidth fits in the dispway
 * dwam bandwidth (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns twue if the dispway fits, fawse if not.
 */
static boow dce_v6_0_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway(stwuct dce6_wm_pawams *wm)
{
	if (dce_v6_0_avewage_bandwidth(wm) <=
	    (dce_v6_0_dwam_bandwidth_fow_dispway(wm) / wm->num_heads))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * dce_v6_0_avewage_bandwidth_vs_avaiwabwe_bandwidth - check
 * avewage and avaiwabwe bandwidth
 *
 * @wm: watewmawk cawcuwation data
 *
 * Check if the dispway avewage bandwidth fits in the dispway
 * avaiwabwe bandwidth (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns twue if the dispway fits, fawse if not.
 */
static boow dce_v6_0_avewage_bandwidth_vs_avaiwabwe_bandwidth(stwuct dce6_wm_pawams *wm)
{
	if (dce_v6_0_avewage_bandwidth(wm) <=
	    (dce_v6_0_avaiwabwe_bandwidth(wm) / wm->num_heads))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * dce_v6_0_check_watency_hiding - check watency hiding
 *
 * @wm: watewmawk cawcuwation data
 *
 * Check watency hiding (CIK).
 * Used fow dispway watewmawk bandwidth cawcuwations
 * Wetuwns twue if the dispway fits, fawse if not.
 */
static boow dce_v6_0_check_watency_hiding(stwuct dce6_wm_pawams *wm)
{
	u32 wb_pawtitions = wm->wb_size / wm->swc_width;
	u32 wine_time = wm->active_time + wm->bwank_time;
	u32 watency_towewant_wines;
	u32 watency_hiding;
	fixed20_12 a;

	a.fuww = dfixed_const(1);
	if (wm->vsc.fuww > a.fuww)
		watency_towewant_wines = 1;
	ewse {
		if (wb_pawtitions <= (wm->vtaps + 1))
			watency_towewant_wines = 1;
		ewse
			watency_towewant_wines = 2;
	}

	watency_hiding = (watency_towewant_wines * wine_time + wm->bwank_time);

	if (dce_v6_0_watency_watewmawk(wm) <= watency_hiding)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * dce_v6_0_pwogwam_watewmawks - pwogwam dispway watewmawks
 *
 * @adev: amdgpu_device pointew
 * @amdgpu_cwtc: the sewected dispway contwowwew
 * @wb_size: wine buffew size
 * @num_heads: numbew of dispway contwowwews in use
 *
 * Cawcuwate and pwogwam the dispway watewmawks fow the
 * sewected dispway contwowwew (CIK).
 */
static void dce_v6_0_pwogwam_watewmawks(stwuct amdgpu_device *adev,
					stwuct amdgpu_cwtc *amdgpu_cwtc,
					u32 wb_size, u32 num_heads)
{
	stwuct dwm_dispway_mode *mode = &amdgpu_cwtc->base.mode;
	stwuct dce6_wm_pawams wm_wow, wm_high;
	u32 dwam_channews;
	u32 active_time;
	u32 wine_time = 0;
	u32 watency_watewmawk_a = 0, watency_watewmawk_b = 0;
	u32 pwiowity_a_mawk = 0, pwiowity_b_mawk = 0;
	u32 pwiowity_a_cnt = PWIOWITY_OFF;
	u32 pwiowity_b_cnt = PWIOWITY_OFF;
	u32 tmp, awb_contwow3, wb_vbwank_wead_wines = 0;
	fixed20_12 a, b, c;

	if (amdgpu_cwtc->base.enabwed && num_heads && mode) {
		active_time = (u32) div_u64((u64)mode->cwtc_hdispway * 1000000,
					    (u32)mode->cwock);
		wine_time = (u32) div_u64((u64)mode->cwtc_htotaw * 1000000,
					  (u32)mode->cwock);
		wine_time = min_t(u32, wine_time, 65535);
		pwiowity_a_cnt = 0;
		pwiowity_b_cnt = 0;

		dwam_channews = si_get_numbew_of_dwam_channews(adev);

		/* watewmawk fow high cwocks */
		if (adev->pm.dpm_enabwed) {
			wm_high.ycwk =
				amdgpu_dpm_get_mcwk(adev, fawse) * 10;
			wm_high.scwk =
				amdgpu_dpm_get_scwk(adev, fawse) * 10;
		} ewse {
			wm_high.ycwk = adev->pm.cuwwent_mcwk * 10;
			wm_high.scwk = adev->pm.cuwwent_scwk * 10;
		}

		wm_high.disp_cwk = mode->cwock;
		wm_high.swc_width = mode->cwtc_hdispway;
		wm_high.active_time = active_time;
		wm_high.bwank_time = wine_time - wm_high.active_time;
		wm_high.intewwaced = fawse;
		if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			wm_high.intewwaced = twue;
		wm_high.vsc = amdgpu_cwtc->vsc;
		wm_high.vtaps = 1;
		if (amdgpu_cwtc->wmx_type != WMX_OFF)
			wm_high.vtaps = 2;
		wm_high.bytes_pew_pixew = 4; /* XXX: get this fwom fb config */
		wm_high.wb_size = wb_size;
		wm_high.dwam_channews = dwam_channews;
		wm_high.num_heads = num_heads;

		if (adev->pm.dpm_enabwed) {
		/* watewmawk fow wow cwocks */
			wm_wow.ycwk =
				amdgpu_dpm_get_mcwk(adev, twue) * 10;
			wm_wow.scwk =
				amdgpu_dpm_get_scwk(adev, twue) * 10;
		} ewse {
			wm_wow.ycwk = adev->pm.cuwwent_mcwk * 10;
			wm_wow.scwk = adev->pm.cuwwent_scwk * 10;
		}

		wm_wow.disp_cwk = mode->cwock;
		wm_wow.swc_width = mode->cwtc_hdispway;
		wm_wow.active_time = active_time;
		wm_wow.bwank_time = wine_time - wm_wow.active_time;
		wm_wow.intewwaced = fawse;
		if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
			wm_wow.intewwaced = twue;
		wm_wow.vsc = amdgpu_cwtc->vsc;
		wm_wow.vtaps = 1;
		if (amdgpu_cwtc->wmx_type != WMX_OFF)
			wm_wow.vtaps = 2;
		wm_wow.bytes_pew_pixew = 4; /* XXX: get this fwom fb config */
		wm_wow.wb_size = wb_size;
		wm_wow.dwam_channews = dwam_channews;
		wm_wow.num_heads = num_heads;

		/* set fow high cwocks */
		watency_watewmawk_a = min_t(u32, dce_v6_0_watency_watewmawk(&wm_high), 65535);
		/* set fow wow cwocks */
		watency_watewmawk_b = min_t(u32, dce_v6_0_watency_watewmawk(&wm_wow), 65535);

		/* possibwy fowce dispway pwiowity to high */
		/* shouwd weawwy do this at mode vawidation time... */
		if (!dce_v6_0_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway(&wm_high) ||
		    !dce_v6_0_avewage_bandwidth_vs_avaiwabwe_bandwidth(&wm_high) ||
		    !dce_v6_0_check_watency_hiding(&wm_high) ||
		    (adev->mode_info.disp_pwiowity == 2)) {
			DWM_DEBUG_KMS("fowce pwiowity to high\n");
			pwiowity_a_cnt |= PWIOWITY_AWWAYS_ON;
			pwiowity_b_cnt |= PWIOWITY_AWWAYS_ON;
		}
		if (!dce_v6_0_avewage_bandwidth_vs_dwam_bandwidth_fow_dispway(&wm_wow) ||
		    !dce_v6_0_avewage_bandwidth_vs_avaiwabwe_bandwidth(&wm_wow) ||
		    !dce_v6_0_check_watency_hiding(&wm_wow) ||
		    (adev->mode_info.disp_pwiowity == 2)) {
			DWM_DEBUG_KMS("fowce pwiowity to high\n");
			pwiowity_a_cnt |= PWIOWITY_AWWAYS_ON;
			pwiowity_b_cnt |= PWIOWITY_AWWAYS_ON;
		}

		a.fuww = dfixed_const(1000);
		b.fuww = dfixed_const(mode->cwock);
		b.fuww = dfixed_div(b, a);
		c.fuww = dfixed_const(watency_watewmawk_a);
		c.fuww = dfixed_muw(c, b);
		c.fuww = dfixed_muw(c, amdgpu_cwtc->hsc);
		c.fuww = dfixed_div(c, a);
		a.fuww = dfixed_const(16);
		c.fuww = dfixed_div(c, a);
		pwiowity_a_mawk = dfixed_twunc(c);
		pwiowity_a_cnt |= pwiowity_a_mawk & PWIOWITY_MAWK_MASK;

		a.fuww = dfixed_const(1000);
		b.fuww = dfixed_const(mode->cwock);
		b.fuww = dfixed_div(b, a);
		c.fuww = dfixed_const(watency_watewmawk_b);
		c.fuww = dfixed_muw(c, b);
		c.fuww = dfixed_muw(c, amdgpu_cwtc->hsc);
		c.fuww = dfixed_div(c, a);
		a.fuww = dfixed_const(16);
		c.fuww = dfixed_div(c, a);
		pwiowity_b_mawk = dfixed_twunc(c);
		pwiowity_b_cnt |= pwiowity_b_mawk & PWIOWITY_MAWK_MASK;

		wb_vbwank_wead_wines = DIV_WOUND_UP(wb_size, mode->cwtc_hdispway);
	}

	/* sewect wm A */
	awb_contwow3 = WWEG32(mmDPG_PIPE_AWBITWATION_CONTWOW3 + amdgpu_cwtc->cwtc_offset);
	tmp = awb_contwow3;
	tmp &= ~WATENCY_WATEWMAWK_MASK(3);
	tmp |= WATENCY_WATEWMAWK_MASK(1);
	WWEG32(mmDPG_PIPE_AWBITWATION_CONTWOW3 + amdgpu_cwtc->cwtc_offset, tmp);
	WWEG32(mmDPG_PIPE_UWGENCY_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((watency_watewmawk_a << DPG_PIPE_UWGENCY_CONTWOW__UWGENCY_WOW_WATEWMAWK__SHIFT)  |
		(wine_time << DPG_PIPE_UWGENCY_CONTWOW__UWGENCY_HIGH_WATEWMAWK__SHIFT)));
	/* sewect wm B */
	tmp = WWEG32(mmDPG_PIPE_AWBITWATION_CONTWOW3 + amdgpu_cwtc->cwtc_offset);
	tmp &= ~WATENCY_WATEWMAWK_MASK(3);
	tmp |= WATENCY_WATEWMAWK_MASK(2);
	WWEG32(mmDPG_PIPE_AWBITWATION_CONTWOW3 + amdgpu_cwtc->cwtc_offset, tmp);
	WWEG32(mmDPG_PIPE_UWGENCY_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((watency_watewmawk_b << DPG_PIPE_UWGENCY_CONTWOW__UWGENCY_WOW_WATEWMAWK__SHIFT) |
		(wine_time << DPG_PIPE_UWGENCY_CONTWOW__UWGENCY_HIGH_WATEWMAWK__SHIFT)));
	/* westowe owiginaw sewection */
	WWEG32(mmDPG_PIPE_AWBITWATION_CONTWOW3 + amdgpu_cwtc->cwtc_offset, awb_contwow3);

	/* wwite the pwiowity mawks */
	WWEG32(mmPWIOWITY_A_CNT + amdgpu_cwtc->cwtc_offset, pwiowity_a_cnt);
	WWEG32(mmPWIOWITY_B_CNT + amdgpu_cwtc->cwtc_offset, pwiowity_b_cnt);

	/* save vawues fow DPM */
	amdgpu_cwtc->wine_time = wine_time;
	amdgpu_cwtc->wm_high = watency_watewmawk_a;

	/* Save numbew of wines the winebuffew weads befowe the scanout */
	amdgpu_cwtc->wb_vbwank_wead_wines = wb_vbwank_wead_wines;
}

/* watewmawk setup */
static u32 dce_v6_0_wine_buffew_adjust(stwuct amdgpu_device *adev,
				   stwuct amdgpu_cwtc *amdgpu_cwtc,
				   stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *othew_mode)
{
	u32 tmp, buffew_awwoc, i;
	u32 pipe_offset = amdgpu_cwtc->cwtc_id * 0x8;
	/*
	 * Wine Buffew Setup
	 * Thewe awe 3 wine buffews, each one shawed by 2 dispway contwowwews.
	 * mmDC_WB_MEMOWY_SPWIT contwows how that wine buffew is shawed between
	 * the dispway contwowwews.  The pawitioning is done via one of fouw
	 * pweset awwocations specified in bits 21:20:
	 *  0 - hawf wb
	 *  2 - whowe wb, othew cwtc must be disabwed
	 */
	/* this can get twicky if we have two wawge dispways on a paiwed gwoup
	 * of cwtcs.  Ideawwy fow muwtipwe wawge dispways we'd assign them to
	 * non-winked cwtcs fow maximum wine buffew awwocation.
	 */
	if (amdgpu_cwtc->base.enabwed && mode) {
		if (othew_mode) {
			tmp = 0; /* 1/2 */
			buffew_awwoc = 1;
		} ewse {
			tmp = 2; /* whowe */
			buffew_awwoc = 2;
		}
	} ewse {
		tmp = 0;
		buffew_awwoc = 0;
	}

	WWEG32(mmDC_WB_MEMOWY_SPWIT + amdgpu_cwtc->cwtc_offset,
	       DC_WB_MEMOWY_CONFIG(tmp));

	WWEG32(mmPIPE0_DMIF_BUFFEW_CONTWOW + pipe_offset,
	       (buffew_awwoc << PIPE0_DMIF_BUFFEW_CONTWOW__DMIF_BUFFEWS_AWWOCATED__SHIFT));
	fow (i = 0; i < adev->usec_timeout; i++) {
		if (WWEG32(mmPIPE0_DMIF_BUFFEW_CONTWOW + pipe_offset) &
		    PIPE0_DMIF_BUFFEW_CONTWOW__DMIF_BUFFEWS_AWWOCATION_COMPWETED_MASK)
			bweak;
		udeway(1);
	}

	if (amdgpu_cwtc->base.enabwed && mode) {
		switch (tmp) {
		case 0:
		defauwt:
			wetuwn 4096 * 2;
		case 2:
			wetuwn 8192 * 2;
		}
	}

	/* contwowwew not enabwed, so no wb used */
	wetuwn 0;
}


/**
 * dce_v6_0_bandwidth_update - pwogwam dispway watewmawks
 *
 * @adev: amdgpu_device pointew
 *
 * Cawcuwate and pwogwam the dispway watewmawks and wine
 * buffew awwocation (CIK).
 */
static void dce_v6_0_bandwidth_update(stwuct amdgpu_device *adev)
{
	stwuct dwm_dispway_mode *mode0 = NUWW;
	stwuct dwm_dispway_mode *mode1 = NUWW;
	u32 num_heads = 0, wb_size;
	int i;

	if (!adev->mode_info.mode_config_initiawized)
		wetuwn;

	amdgpu_dispway_update_pwiowity(adev);

	fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
		if (adev->mode_info.cwtcs[i]->base.enabwed)
			num_heads++;
	}
	fow (i = 0; i < adev->mode_info.num_cwtc; i += 2) {
		mode0 = &adev->mode_info.cwtcs[i]->base.mode;
		mode1 = &adev->mode_info.cwtcs[i+1]->base.mode;
		wb_size = dce_v6_0_wine_buffew_adjust(adev, adev->mode_info.cwtcs[i], mode0, mode1);
		dce_v6_0_pwogwam_watewmawks(adev, adev->mode_info.cwtcs[i], wb_size, num_heads);
		wb_size = dce_v6_0_wine_buffew_adjust(adev, adev->mode_info.cwtcs[i+1], mode1, mode0);
		dce_v6_0_pwogwam_watewmawks(adev, adev->mode_info.cwtcs[i+1], wb_size, num_heads);
	}
}

static void dce_v6_0_audio_get_connected_pins(stwuct amdgpu_device *adev)
{
	int i;
	u32 tmp;

	fow (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		tmp = WWEG32_AUDIO_ENDPT(adev->mode_info.audio.pin[i].offset,
				ixAZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_CONFIGUWATION_DEFAUWT);
		if (WEG_GET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_CONFIGUWATION_DEFAUWT,
					POWT_CONNECTIVITY))
			adev->mode_info.audio.pin[i].connected = fawse;
		ewse
			adev->mode_info.audio.pin[i].connected = twue;
	}

}

static stwuct amdgpu_audio_pin *dce_v6_0_audio_get_pin(stwuct amdgpu_device *adev)
{
	int i;

	dce_v6_0_audio_get_connected_pins(adev);

	fow (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		if (adev->mode_info.audio.pin[i].connected)
			wetuwn &adev->mode_info.audio.pin[i];
	}
	DWM_EWWOW("No connected audio pins found!\n");
	wetuwn NUWW;
}

static void dce_v6_0_audio_sewect_pin(stwuct dwm_encodew *encodew)
{
	stwuct amdgpu_device *adev = dwm_to_adev(encodew->dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;

	if (!dig || !dig->afmt || !dig->afmt->pin)
		wetuwn;

	WWEG32(mmAFMT_AUDIO_SWC_CONTWOW + dig->afmt->offset,
	       WEG_SET_FIEWD(0, AFMT_AUDIO_SWC_CONTWOW, AFMT_AUDIO_SWC_SEWECT,
		             dig->afmt->pin->id));
}

static void dce_v6_0_audio_wwite_watency_fiewds(stwuct dwm_encodew *encodew,
						stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	stwuct amdgpu_connectow *amdgpu_connectow = NUWW;
	int intewwace = 0;
	u32 tmp;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		if (connectow->encodew == encodew) {
			amdgpu_connectow = to_amdgpu_connectow(connectow);
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&itew);

	if (!amdgpu_connectow) {
		DWM_EWWOW("Couwdn't find encodew's connectow\n");
		wetuwn;
	}

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		intewwace = 1;

	if (connectow->watency_pwesent[intewwace]) {
		tmp = WEG_SET_FIEWD(0, AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
				VIDEO_WIPSYNC, connectow->video_watency[intewwace]);
		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
				AUDIO_WIPSYNC, connectow->audio_watency[intewwace]);
	} ewse {
		tmp = WEG_SET_FIEWD(0, AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
				VIDEO_WIPSYNC, 0);
		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC,
				AUDIO_WIPSYNC, 0);
	}
	WWEG32_AUDIO_ENDPT(dig->afmt->pin->offset,
			   ixAZAWIA_F0_CODEC_PIN_CONTWOW_WESPONSE_WIPSYNC, tmp);
}

static void dce_v6_0_audio_wwite_speakew_awwocation(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	stwuct amdgpu_connectow *amdgpu_connectow = NUWW;
	u8 *sadb = NUWW;
	int sad_count;
	u32 tmp;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		if (connectow->encodew == encodew) {
			amdgpu_connectow = to_amdgpu_connectow(connectow);
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&itew);

	if (!amdgpu_connectow) {
		DWM_EWWOW("Couwdn't find encodew's connectow\n");
		wetuwn;
	}

	sad_count = dwm_edid_to_speakew_awwocation(amdgpu_connectow_edid(connectow), &sadb);
	if (sad_count < 0) {
		DWM_EWWOW("Couwdn't wead Speakew Awwocation Data Bwock: %d\n", sad_count);
		sad_count = 0;
	}

	/* pwogwam the speakew awwocation */
	tmp = WWEG32_AUDIO_ENDPT(dig->afmt->pin->offset,
			ixAZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW);
	tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
			HDMI_CONNECTION, 0);
	tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
			DP_CONNECTION, 0);

	if (connectow->connectow_type == DWM_MODE_CONNECTOW_DispwayPowt)
		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
				DP_CONNECTION, 1);
	ewse
		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
				HDMI_CONNECTION, 1);

	if (sad_count)
		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
				SPEAKEW_AWWOCATION, sadb[0]);
	ewse
		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW,
				SPEAKEW_AWWOCATION, 5); /* steweo */

	WWEG32_AUDIO_ENDPT(dig->afmt->pin->offset,
			ixAZAWIA_F0_CODEC_PIN_CONTWOW_CHANNEW_SPEAKEW, tmp);

	kfwee(sadb);
}

static void dce_v6_0_audio_wwite_sad_wegs(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	stwuct amdgpu_connectow *amdgpu_connectow = NUWW;
	stwuct cea_sad *sads;
	int i, sad_count;

	static const u16 ewd_weg_to_type[][2] = {
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0, HDMI_AUDIO_CODING_TYPE_PCM },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW1, HDMI_AUDIO_CODING_TYPE_AC3 },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW2, HDMI_AUDIO_CODING_TYPE_MPEG1 },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW3, HDMI_AUDIO_CODING_TYPE_MP3 },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW4, HDMI_AUDIO_CODING_TYPE_MPEG2 },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW5, HDMI_AUDIO_CODING_TYPE_AAC_WC },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW6, HDMI_AUDIO_CODING_TYPE_DTS },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW7, HDMI_AUDIO_CODING_TYPE_ATWAC },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW9, HDMI_AUDIO_CODING_TYPE_EAC3 },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW10, HDMI_AUDIO_CODING_TYPE_DTS_HD },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW11, HDMI_AUDIO_CODING_TYPE_MWP },
		{ ixAZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW13, HDMI_AUDIO_CODING_TYPE_WMA_PWO },
	};

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		if (connectow->encodew == encodew) {
			amdgpu_connectow = to_amdgpu_connectow(connectow);
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&itew);

	if (!amdgpu_connectow) {
		DWM_EWWOW("Couwdn't find encodew's connectow\n");
		wetuwn;
	}

	sad_count = dwm_edid_to_sad(amdgpu_connectow_edid(connectow), &sads);
	if (sad_count < 0)
		DWM_EWWOW("Couwdn't wead SADs: %d\n", sad_count);
	if (sad_count <= 0)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(ewd_weg_to_type); i++) {
		u32 tmp = 0;
		u8 steweo_fweqs = 0;
		int max_channews = -1;
		int j;

		fow (j = 0; j < sad_count; j++) {
			stwuct cea_sad *sad = &sads[j];

			if (sad->fowmat == ewd_weg_to_type[i][1]) {
				if (sad->channews > max_channews) {
					tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
							MAX_CHANNEWS, sad->channews);
					tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
							DESCWIPTOW_BYTE_2, sad->byte2);
					tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
							SUPPOWTED_FWEQUENCIES, sad->fweq);
					max_channews = sad->channews;
				}

				if (sad->fowmat == HDMI_AUDIO_CODING_TYPE_PCM)
					steweo_fweqs |= sad->fweq;
				ewse
					bweak;
			}
		}

		tmp = WEG_SET_FIEWD(tmp, AZAWIA_F0_CODEC_PIN_CONTWOW_AUDIO_DESCWIPTOW0,
				SUPPOWTED_FWEQUENCIES_STEWEO, steweo_fweqs);
		WWEG32_AUDIO_ENDPT(dig->afmt->pin->offset, ewd_weg_to_type[i][0], tmp);
	}

	kfwee(sads);

}

static void dce_v6_0_audio_enabwe(stwuct amdgpu_device *adev,
				  stwuct amdgpu_audio_pin *pin,
				  boow enabwe)
{
	if (!pin)
		wetuwn;

	WWEG32_AUDIO_ENDPT(pin->offset, ixAZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW,
			enabwe ? AZAWIA_F0_CODEC_PIN_CONTWOW_HOT_PWUG_CONTWOW__AUDIO_ENABWED_MASK : 0);
}

static const u32 pin_offsets[7] =
{
	(0x1780 - 0x1780),
	(0x1786 - 0x1780),
	(0x178c - 0x1780),
	(0x1792 - 0x1780),
	(0x1798 - 0x1780),
	(0x179d - 0x1780),
	(0x17a4 - 0x1780),
};

static int dce_v6_0_audio_init(stwuct amdgpu_device *adev)
{
	int i;

	if (!amdgpu_audio)
		wetuwn 0;

	adev->mode_info.audio.enabwed = twue;

	switch (adev->asic_type) {
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	defauwt:
		adev->mode_info.audio.num_pins = 6;
		bweak;
	case CHIP_OWAND:
		adev->mode_info.audio.num_pins = 2;
		bweak;
	}

	fow (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		adev->mode_info.audio.pin[i].channews = -1;
		adev->mode_info.audio.pin[i].wate = -1;
		adev->mode_info.audio.pin[i].bits_pew_sampwe = -1;
		adev->mode_info.audio.pin[i].status_bits = 0;
		adev->mode_info.audio.pin[i].categowy_code = 0;
		adev->mode_info.audio.pin[i].connected = fawse;
		adev->mode_info.audio.pin[i].offset = pin_offsets[i];
		adev->mode_info.audio.pin[i].id = i;
		dce_v6_0_audio_enabwe(adev, &adev->mode_info.audio.pin[i], fawse);
	}

	wetuwn 0;
}

static void dce_v6_0_audio_fini(stwuct amdgpu_device *adev)
{
	int i;

	if (!amdgpu_audio)
		wetuwn;

	if (!adev->mode_info.audio.enabwed)
		wetuwn;

	fow (i = 0; i < adev->mode_info.audio.num_pins; i++)
		dce_v6_0_audio_enabwe(adev, &adev->mode_info.audio.pin[i], fawse);

	adev->mode_info.audio.enabwed = fawse;
}

static void dce_v6_0_audio_set_vbi_packet(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u32 tmp;

	tmp = WWEG32(mmHDMI_VBI_PACKET_CONTWOW + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_VBI_PACKET_CONTWOW, HDMI_NUWW_SEND, 1);
	tmp = WEG_SET_FIEWD(tmp, HDMI_VBI_PACKET_CONTWOW, HDMI_GC_SEND, 1);
	tmp = WEG_SET_FIEWD(tmp, HDMI_VBI_PACKET_CONTWOW, HDMI_GC_CONT, 1);
	WWEG32(mmHDMI_VBI_PACKET_CONTWOW + dig->afmt->offset, tmp);
}

static void dce_v6_0_audio_set_acw(stwuct dwm_encodew *encodew,
				   uint32_t cwock, int bpc)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_afmt_acw acw = amdgpu_afmt_acw(cwock);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u32 tmp;

	tmp = WWEG32(mmHDMI_ACW_PACKET_CONTWOW + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_PACKET_CONTWOW, HDMI_ACW_AUTO_SEND, 1);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_PACKET_CONTWOW, HDMI_ACW_SOUWCE,
			bpc > 8 ? 0 : 1);
	WWEG32(mmHDMI_ACW_PACKET_CONTWOW + dig->afmt->offset, tmp);

	tmp = WWEG32(mmHDMI_ACW_32_0 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_32_0, HDMI_ACW_CTS_32, acw.cts_32khz);
	WWEG32(mmHDMI_ACW_32_0 + dig->afmt->offset, tmp);
	tmp = WWEG32(mmHDMI_ACW_32_1 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_32_1, HDMI_ACW_N_32, acw.n_32khz);
	WWEG32(mmHDMI_ACW_32_1 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmHDMI_ACW_44_0 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_44_0, HDMI_ACW_CTS_44, acw.cts_44_1khz);
	WWEG32(mmHDMI_ACW_44_0 + dig->afmt->offset, tmp);
	tmp = WWEG32(mmHDMI_ACW_44_1 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_44_1, HDMI_ACW_N_44, acw.n_44_1khz);
	WWEG32(mmHDMI_ACW_44_1 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmHDMI_ACW_48_0 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_48_0, HDMI_ACW_CTS_48, acw.cts_48khz);
	WWEG32(mmHDMI_ACW_48_0 + dig->afmt->offset, tmp);
	tmp = WWEG32(mmHDMI_ACW_48_1 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_ACW_48_1, HDMI_ACW_N_48, acw.n_48khz);
	WWEG32(mmHDMI_ACW_48_1 + dig->afmt->offset, tmp);
}

static void dce_v6_0_audio_set_avi_infofwame(stwuct dwm_encodew *encodew,
					       stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow = amdgpu_get_connectow_fow_encodew(encodew);
	stwuct hdmi_avi_infofwame fwame;
	u8 buffew[HDMI_INFOFWAME_HEADEW_SIZE + HDMI_AVI_INFOFWAME_SIZE];
	uint8_t *paywoad = buffew + 3;
	uint8_t *headew = buffew;
	ssize_t eww;
	u32 tmp;

	eww = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame, connectow, mode);
	if (eww < 0) {
		DWM_EWWOW("faiwed to setup AVI infofwame: %zd\n", eww);
		wetuwn;
	}

	eww = hdmi_avi_infofwame_pack(&fwame, buffew, sizeof(buffew));
	if (eww < 0) {
		DWM_EWWOW("faiwed to pack AVI infofwame: %zd\n", eww);
		wetuwn;
	}

	WWEG32(mmAFMT_AVI_INFO0 + dig->afmt->offset,
	       paywoad[0x0] | (paywoad[0x1] << 8) | (paywoad[0x2] << 16) | (paywoad[0x3] << 24));
	WWEG32(mmAFMT_AVI_INFO1 + dig->afmt->offset,
	       paywoad[0x4] | (paywoad[0x5] << 8) | (paywoad[0x6] << 16) | (paywoad[0x7] << 24));
	WWEG32(mmAFMT_AVI_INFO2 + dig->afmt->offset,
	       paywoad[0x8] | (paywoad[0x9] << 8) | (paywoad[0xA] << 16) | (paywoad[0xB] << 24));
	WWEG32(mmAFMT_AVI_INFO3 + dig->afmt->offset,
	       paywoad[0xC] | (paywoad[0xD] << 8) | (headew[1] << 24));

	tmp = WWEG32(mmHDMI_INFOFWAME_CONTWOW1 + dig->afmt->offset);
	/* anything othew than 0 */
	tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW1,
			HDMI_AUDIO_INFO_WINE, 2);
	WWEG32(mmHDMI_INFOFWAME_CONTWOW1 + dig->afmt->offset, tmp);
}

static void dce_v6_0_audio_set_dto(stwuct dwm_encodew *encodew, u32 cwock)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(encodew->cwtc);
	int em = amdgpu_atombios_encodew_get_encodew_mode(encodew);
	u32 tmp;

	/*
	 * Two dtos: genewawwy use dto0 fow hdmi, dto1 fow dp.
	 * Expwess [24MHz / tawget pixew cwock] as an exact wationaw
	 * numbew (coefficient of two integew numbews.  DCCG_AUDIO_DTOx_PHASE
	 * is the numewatow, DCCG_AUDIO_DTOx_MODUWE is the denominatow
	 */
	tmp = WWEG32(mmDCCG_AUDIO_DTO_SOUWCE);
	tmp = WEG_SET_FIEWD(tmp, DCCG_AUDIO_DTO_SOUWCE,
			DCCG_AUDIO_DTO0_SOUWCE_SEW, amdgpu_cwtc->cwtc_id);
	if (em == ATOM_ENCODEW_MODE_HDMI) {
		tmp = WEG_SET_FIEWD(tmp, DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO_SEW, 0);
	} ewse if (ENCODEW_MODE_IS_DP(em)) {
		tmp = WEG_SET_FIEWD(tmp, DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO_SEW, 1);
	}
	WWEG32(mmDCCG_AUDIO_DTO_SOUWCE, tmp);
	if (em == ATOM_ENCODEW_MODE_HDMI) {
		WWEG32(mmDCCG_AUDIO_DTO0_PHASE, 24000);
		WWEG32(mmDCCG_AUDIO_DTO0_MODUWE, cwock);
	} ewse if (ENCODEW_MODE_IS_DP(em)) {
		WWEG32(mmDCCG_AUDIO_DTO1_PHASE, 24000);
		WWEG32(mmDCCG_AUDIO_DTO1_MODUWE, cwock);
	}
}

static void dce_v6_0_audio_set_packet(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u32 tmp;

	tmp = WWEG32(mmAFMT_INFOFWAME_CONTWOW0 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, AFMT_INFOFWAME_CONTWOW0, AFMT_AUDIO_INFO_UPDATE, 1);
	WWEG32(mmAFMT_INFOFWAME_CONTWOW0 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmAFMT_60958_0 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_0, AFMT_60958_CS_CHANNEW_NUMBEW_W, 1);
	WWEG32(mmAFMT_60958_0 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmAFMT_60958_1 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_1, AFMT_60958_CS_CHANNEW_NUMBEW_W, 2);
	WWEG32(mmAFMT_60958_1 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmAFMT_60958_2 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_2, 3);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_3, 4);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_4, 5);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_5, 6);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_6, 7);
	tmp = WEG_SET_FIEWD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEW_NUMBEW_7, 8);
	WWEG32(mmAFMT_60958_2 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW2 + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, AFMT_AUDIO_PACKET_CONTWOW2, AFMT_AUDIO_CHANNEW_ENABWE, 0xff);
	WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW2 + dig->afmt->offset, tmp);

	tmp = WWEG32(mmHDMI_AUDIO_PACKET_CONTWOW + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_AUDIO_PACKET_CONTWOW, HDMI_AUDIO_DEWAY_EN, 1);
	tmp = WEG_SET_FIEWD(tmp, HDMI_AUDIO_PACKET_CONTWOW, HDMI_AUDIO_PACKETS_PEW_WINE, 3);
	WWEG32(mmHDMI_AUDIO_PACKET_CONTWOW + dig->afmt->offset, tmp);

	tmp = WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, AFMT_AUDIO_PACKET_CONTWOW, AFMT_WESET_FIFO_WHEN_AUDIO_DIS, 1);
	tmp = WEG_SET_FIEWD(tmp, AFMT_AUDIO_PACKET_CONTWOW, AFMT_60958_CS_UPDATE, 1);
	WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset, tmp);
}

static void dce_v6_0_audio_set_mute(stwuct dwm_encodew *encodew, boow mute)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u32 tmp;

	tmp = WWEG32(mmHDMI_GC + dig->afmt->offset);
	tmp = WEG_SET_FIEWD(tmp, HDMI_GC, HDMI_GC_AVMUTE, mute ? 1 : 0);
	WWEG32(mmHDMI_GC + dig->afmt->offset, tmp);
}

static void dce_v6_0_audio_hdmi_enabwe(stwuct dwm_encodew *encodew, boow enabwe)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u32 tmp;

	if (enabwe) {
		tmp = WWEG32(mmHDMI_INFOFWAME_CONTWOW0 + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AVI_INFO_SEND, 1);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AVI_INFO_CONT, 1);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AUDIO_INFO_SEND, 1);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AUDIO_INFO_CONT, 1);
		WWEG32(mmHDMI_INFOFWAME_CONTWOW0 + dig->afmt->offset, tmp);

		tmp = WWEG32(mmHDMI_INFOFWAME_CONTWOW1 + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW1, HDMI_AVI_INFO_WINE, 2);
		WWEG32(mmHDMI_INFOFWAME_CONTWOW1 + dig->afmt->offset, tmp);

		tmp = WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, AFMT_AUDIO_PACKET_CONTWOW, AFMT_AUDIO_SAMPWE_SEND, 1);
		WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset, tmp);
	} ewse {
		tmp = WWEG32(mmHDMI_INFOFWAME_CONTWOW0 + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AVI_INFO_SEND, 0);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AVI_INFO_CONT, 0);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AUDIO_INFO_SEND, 0);
		tmp = WEG_SET_FIEWD(tmp, HDMI_INFOFWAME_CONTWOW0, HDMI_AUDIO_INFO_CONT, 0);
		WWEG32(mmHDMI_INFOFWAME_CONTWOW0 + dig->afmt->offset, tmp);

		tmp = WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, AFMT_AUDIO_PACKET_CONTWOW, AFMT_AUDIO_SAMPWE_SEND, 0);
		WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset, tmp);
	}
}

static void dce_v6_0_audio_dp_enabwe(stwuct dwm_encodew *encodew, boow enabwe)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u32 tmp;

	if (enabwe) {
		tmp = WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, AFMT_AUDIO_PACKET_CONTWOW, AFMT_AUDIO_SAMPWE_SEND, 1);
		WWEG32(mmAFMT_AUDIO_PACKET_CONTWOW + dig->afmt->offset, tmp);

		tmp = WWEG32(mmDP_SEC_TIMESTAMP + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, DP_SEC_TIMESTAMP, DP_SEC_TIMESTAMP_MODE, 1);
		WWEG32(mmDP_SEC_TIMESTAMP + dig->afmt->offset, tmp);

		tmp = WWEG32(mmDP_SEC_CNTW + dig->afmt->offset);
		tmp = WEG_SET_FIEWD(tmp, DP_SEC_CNTW, DP_SEC_ASP_ENABWE, 1);
		tmp = WEG_SET_FIEWD(tmp, DP_SEC_CNTW, DP_SEC_ATP_ENABWE, 1);
		tmp = WEG_SET_FIEWD(tmp, DP_SEC_CNTW, DP_SEC_AIP_ENABWE, 1);
		tmp = WEG_SET_FIEWD(tmp, DP_SEC_CNTW, DP_SEC_STWEAM_ENABWE, 1);
		WWEG32(mmDP_SEC_CNTW + dig->afmt->offset, tmp);
	} ewse {
		WWEG32(mmDP_SEC_CNTW + dig->afmt->offset, 0);
	}
}

static void dce_v6_0_afmt_setmode(stwuct dwm_encodew *encodew,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew itew;
	stwuct amdgpu_connectow *amdgpu_connectow = NUWW;
	int em = amdgpu_atombios_encodew_get_encodew_mode(encodew);
	int bpc = 8;

	if (!dig || !dig->afmt)
		wetuwn;

	dwm_connectow_wist_itew_begin(dev, &itew);
	dwm_fow_each_connectow_itew(connectow, &itew) {
		if (connectow->encodew == encodew) {
			amdgpu_connectow = to_amdgpu_connectow(connectow);
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&itew);

	if (!amdgpu_connectow) {
		DWM_EWWOW("Couwdn't find encodew's connectow\n");
		wetuwn;
	}

	if (!dig->afmt->enabwed)
		wetuwn;

	dig->afmt->pin = dce_v6_0_audio_get_pin(adev);
	if (!dig->afmt->pin)
		wetuwn;

	if (encodew->cwtc) {
		stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(encodew->cwtc);
		bpc = amdgpu_cwtc->bpc;
	}

	/* disabwe audio befowe setting up hw */
	dce_v6_0_audio_enabwe(adev, dig->afmt->pin, fawse);

	dce_v6_0_audio_set_mute(encodew, twue);
	dce_v6_0_audio_wwite_speakew_awwocation(encodew);
	dce_v6_0_audio_wwite_sad_wegs(encodew);
	dce_v6_0_audio_wwite_watency_fiewds(encodew, mode);
	if (em == ATOM_ENCODEW_MODE_HDMI) {
		dce_v6_0_audio_set_dto(encodew, mode->cwock);
		dce_v6_0_audio_set_vbi_packet(encodew);
		dce_v6_0_audio_set_acw(encodew, mode->cwock, bpc);
	} ewse if (ENCODEW_MODE_IS_DP(em)) {
		dce_v6_0_audio_set_dto(encodew, adev->cwock.defauwt_dispcwk * 10);
	}
	dce_v6_0_audio_set_packet(encodew);
	dce_v6_0_audio_sewect_pin(encodew);
	dce_v6_0_audio_set_avi_infofwame(encodew, mode);
	dce_v6_0_audio_set_mute(encodew, fawse);
	if (em == ATOM_ENCODEW_MODE_HDMI) {
		dce_v6_0_audio_hdmi_enabwe(encodew, 1);
	} ewse if (ENCODEW_MODE_IS_DP(em)) {
		dce_v6_0_audio_dp_enabwe(encodew, 1);
	}

	/* enabwe audio aftew setting up hw */
	dce_v6_0_audio_enabwe(adev, dig->afmt->pin, twue);
}

static void dce_v6_0_afmt_enabwe(stwuct dwm_encodew *encodew, boow enabwe)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;

	if (!dig || !dig->afmt)
		wetuwn;

	/* Siwent, w600_hdmi_enabwe wiww waise WAWN fow us */
	if (enabwe && dig->afmt->enabwed)
		wetuwn;

	if (!enabwe && !dig->afmt->enabwed)
		wetuwn;

	if (!enabwe && dig->afmt->pin) {
		dce_v6_0_audio_enabwe(adev, dig->afmt->pin, fawse);
		dig->afmt->pin = NUWW;
	}

	dig->afmt->enabwed = enabwe;

	DWM_DEBUG("%sabwing AFMT intewface @ 0x%04X fow encodew 0x%x\n",
		  enabwe ? "En" : "Dis", dig->afmt->offset, amdgpu_encodew->encodew_id);
}

static int dce_v6_0_afmt_init(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (i = 0; i < adev->mode_info.num_dig; i++)
		adev->mode_info.afmt[i] = NUWW;

	/* DCE6 has audio bwocks tied to DIG encodews */
	fow (i = 0; i < adev->mode_info.num_dig; i++) {
		adev->mode_info.afmt[i] = kzawwoc(sizeof(stwuct amdgpu_afmt), GFP_KEWNEW);
		if (adev->mode_info.afmt[i]) {
			adev->mode_info.afmt[i]->offset = dig_offsets[i];
			adev->mode_info.afmt[i]->id = i;
		} ewse {
			fow (j = 0; j < i; j++) {
				kfwee(adev->mode_info.afmt[j]);
				adev->mode_info.afmt[j] = NUWW;
			}
			DWM_EWWOW("Out of memowy awwocating afmt tabwe\n");
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static void dce_v6_0_afmt_fini(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->mode_info.num_dig; i++) {
		kfwee(adev->mode_info.afmt[i]);
		adev->mode_info.afmt[i] = NUWW;
	}
}

static const u32 vga_contwow_wegs[6] =
{
	mmD1VGA_CONTWOW,
	mmD2VGA_CONTWOW,
	mmD3VGA_CONTWOW,
	mmD4VGA_CONTWOW,
	mmD5VGA_CONTWOW,
	mmD6VGA_CONTWOW,
};

static void dce_v6_0_vga_enabwe(stwuct dwm_cwtc *cwtc, boow enabwe)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	u32 vga_contwow;

	vga_contwow = WWEG32(vga_contwow_wegs[amdgpu_cwtc->cwtc_id]) & ~1;
	WWEG32(vga_contwow_wegs[amdgpu_cwtc->cwtc_id], vga_contwow | (enabwe ? 1 : 0));
}

static void dce_v6_0_gwph_enabwe(stwuct dwm_cwtc *cwtc, boow enabwe)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	WWEG32(mmGWPH_ENABWE + amdgpu_cwtc->cwtc_offset, enabwe ? 1 : 0);
}

static int dce_v6_0_cwtc_do_set_base(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_fwamebuffew *fb,
				     int x, int y, int atomic)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct dwm_fwamebuffew *tawget_fb;
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_bo *abo;
	uint64_t fb_wocation, tiwing_fwags;
	uint32_t fb_fowmat, fb_pitch_pixews, pipe_config;
	u32 fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_NONE);
	u32 viewpowt_w, viewpowt_h;
	int w;
	boow bypass_wut = fawse;

	/* no fb bound */
	if (!atomic && !cwtc->pwimawy->fb) {
		DWM_DEBUG_KMS("No FB bound\n");
		wetuwn 0;
	}

	if (atomic)
		tawget_fb = fb;
	ewse
		tawget_fb = cwtc->pwimawy->fb;

	/* If atomic, assume fb object is pinned & idwe & fenced and
	 * just update base pointews
	 */
	obj = tawget_fb->obj[0];
	abo = gem_to_amdgpu_bo(obj);
	w = amdgpu_bo_wesewve(abo, fawse);
	if (unwikewy(w != 0))
		wetuwn w;

	if (!atomic) {
		w = amdgpu_bo_pin(abo, AMDGPU_GEM_DOMAIN_VWAM);
		if (unwikewy(w != 0)) {
			amdgpu_bo_unwesewve(abo);
			wetuwn -EINVAW;
		}
	}
	fb_wocation = amdgpu_bo_gpu_offset(abo);

	amdgpu_bo_get_tiwing_fwags(abo, &tiwing_fwags);
	amdgpu_bo_unwesewve(abo);

	switch (tawget_fb->fowmat->fowmat) {
	case DWM_FOWMAT_C8:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_8BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_INDEXED));
		bweak;
	case DWM_FOWMAT_XWGB4444:
	case DWM_FOWMAT_AWGB4444:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_16BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_AWGB4444));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_AWGB1555:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_16BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_AWGB1555));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_BGWX5551:
	case DWM_FOWMAT_BGWA5551:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_16BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_BGWA5551));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_WGB565:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_16BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_AWGB565));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN16);
#endif
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_32BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_AWGB8888));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN32);
#endif
		bweak;
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_AWGB2101010:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_32BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_AWGB2101010));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN32);
#endif
		/* Gweatew 8 bpc fb needs to bypass hw-wut to wetain pwecision */
		bypass_wut = twue;
		bweak;
	case DWM_FOWMAT_BGWX1010102:
	case DWM_FOWMAT_BGWA1010102:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_32BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_BGWA1010102));
#ifdef __BIG_ENDIAN
		fb_swap = GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN32);
#endif
		/* Gweatew 8 bpc fb needs to bypass hw-wut to wetain pwecision */
		bypass_wut = twue;
		bweak;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		fb_fowmat = (GWPH_DEPTH(GWPH_DEPTH_32BPP) |
			     GWPH_FOWMAT(GWPH_FOWMAT_AWGB8888));
		fb_swap = (GWPH_WED_CWOSSBAW(GWPH_WED_SEW_B) |
			   GWPH_BWUE_CWOSSBAW(GWPH_BWUE_SEW_W));
#ifdef __BIG_ENDIAN
		fb_swap |= GWPH_ENDIAN_SWAP(GWPH_ENDIAN_8IN32);
#endif
		bweak;
	defauwt:
		DWM_EWWOW("Unsuppowted scween fowmat %p4cc\n",
			  &tawget_fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	if (AMDGPU_TIWING_GET(tiwing_fwags, AWWAY_MODE) == AWWAY_2D_TIWED_THIN1) {
		unsigned bankw, bankh, mtaspect, tiwe_spwit, num_banks;

		bankw = AMDGPU_TIWING_GET(tiwing_fwags, BANK_WIDTH);
		bankh = AMDGPU_TIWING_GET(tiwing_fwags, BANK_HEIGHT);
		mtaspect = AMDGPU_TIWING_GET(tiwing_fwags, MACWO_TIWE_ASPECT);
		tiwe_spwit = AMDGPU_TIWING_GET(tiwing_fwags, TIWE_SPWIT);
		num_banks = AMDGPU_TIWING_GET(tiwing_fwags, NUM_BANKS);

		fb_fowmat |= GWPH_NUM_BANKS(num_banks);
		fb_fowmat |= GWPH_AWWAY_MODE(GWPH_AWWAY_2D_TIWED_THIN1);
		fb_fowmat |= GWPH_TIWE_SPWIT(tiwe_spwit);
		fb_fowmat |= GWPH_BANK_WIDTH(bankw);
		fb_fowmat |= GWPH_BANK_HEIGHT(bankh);
		fb_fowmat |= GWPH_MACWO_TIWE_ASPECT(mtaspect);
	} ewse if (AMDGPU_TIWING_GET(tiwing_fwags, AWWAY_MODE) == AWWAY_1D_TIWED_THIN1) {
		fb_fowmat |= GWPH_AWWAY_MODE(GWPH_AWWAY_1D_TIWED_THIN1);
	}

	pipe_config = AMDGPU_TIWING_GET(tiwing_fwags, PIPE_CONFIG);
	fb_fowmat |= GWPH_PIPE_CONFIG(pipe_config);

	dce_v6_0_vga_enabwe(cwtc, fawse);

	/* Make suwe suwface addwess is updated at vewticaw bwank wathew than
	 * howizontaw bwank
	 */
	WWEG32(mmGWPH_FWIP_CONTWOW + amdgpu_cwtc->cwtc_offset, 0);

	WWEG32(mmGWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH + amdgpu_cwtc->cwtc_offset,
	       uppew_32_bits(fb_wocation));
	WWEG32(mmGWPH_SECONDAWY_SUWFACE_ADDWESS_HIGH + amdgpu_cwtc->cwtc_offset,
	       uppew_32_bits(fb_wocation));
	WWEG32(mmGWPH_PWIMAWY_SUWFACE_ADDWESS + amdgpu_cwtc->cwtc_offset,
	       (u32)fb_wocation & GWPH_PWIMAWY_SUWFACE_ADDWESS__GWPH_PWIMAWY_SUWFACE_ADDWESS_MASK);
	WWEG32(mmGWPH_SECONDAWY_SUWFACE_ADDWESS + amdgpu_cwtc->cwtc_offset,
	       (u32) fb_wocation & GWPH_PWIMAWY_SUWFACE_ADDWESS__GWPH_PWIMAWY_SUWFACE_ADDWESS_MASK);
	WWEG32(mmGWPH_CONTWOW + amdgpu_cwtc->cwtc_offset, fb_fowmat);
	WWEG32(mmGWPH_SWAP_CNTW + amdgpu_cwtc->cwtc_offset, fb_swap);

	/*
	 * The WUT onwy has 256 swots fow indexing by a 8 bpc fb. Bypass the WUT
	 * fow > 8 bpc scanout to avoid twuncation of fb indices to 8 msb's, to
	 * wetain the fuww pwecision thwoughout the pipewine.
	 */
	WWEG32_P(mmGWPH_WUT_10BIT_BYPASS + amdgpu_cwtc->cwtc_offset,
		 (bypass_wut ? GWPH_WUT_10BIT_BYPASS__GWPH_WUT_10BIT_BYPASS_EN_MASK : 0),
		 ~GWPH_WUT_10BIT_BYPASS__GWPH_WUT_10BIT_BYPASS_EN_MASK);

	if (bypass_wut)
		DWM_DEBUG_KMS("Bypassing hawdwawe WUT due to 10 bit fb scanout.\n");

	WWEG32(mmGWPH_SUWFACE_OFFSET_X + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmGWPH_SUWFACE_OFFSET_Y + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmGWPH_X_STAWT + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmGWPH_Y_STAWT + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmGWPH_X_END + amdgpu_cwtc->cwtc_offset, tawget_fb->width);
	WWEG32(mmGWPH_Y_END + amdgpu_cwtc->cwtc_offset, tawget_fb->height);

	fb_pitch_pixews = tawget_fb->pitches[0] / tawget_fb->fowmat->cpp[0];
	WWEG32(mmGWPH_PITCH + amdgpu_cwtc->cwtc_offset, fb_pitch_pixews);

	dce_v6_0_gwph_enabwe(cwtc, twue);

	WWEG32(mmDESKTOP_HEIGHT + amdgpu_cwtc->cwtc_offset,
		       tawget_fb->height);
	x &= ~3;
	y &= ~1;
	WWEG32(mmVIEWPOWT_STAWT + amdgpu_cwtc->cwtc_offset,
	       (x << 16) | y);
	viewpowt_w = cwtc->mode.hdispway;
	viewpowt_h = (cwtc->mode.vdispway + 1) & ~1;

	WWEG32(mmVIEWPOWT_SIZE + amdgpu_cwtc->cwtc_offset,
	       (viewpowt_w << 16) | viewpowt_h);

	/* set pagefwip to happen anywhewe in vbwank intewvaw */
	WWEG32(mmMASTEW_UPDATE_MODE + amdgpu_cwtc->cwtc_offset, 0);

	if (!atomic && fb && fb != cwtc->pwimawy->fb) {
		abo = gem_to_amdgpu_bo(fb->obj[0]);
		w = amdgpu_bo_wesewve(abo, twue);
		if (unwikewy(w != 0))
			wetuwn w;
		amdgpu_bo_unpin(abo);
		amdgpu_bo_unwesewve(abo);
	}

	/* Bytes pew pixew may have changed */
	dce_v6_0_bandwidth_update(adev);

	wetuwn 0;

}

static void dce_v6_0_set_intewweave(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		WWEG32(mmDATA_FOWMAT + amdgpu_cwtc->cwtc_offset,
		       INTEWWEAVE_EN);
	ewse
		WWEG32(mmDATA_FOWMAT + amdgpu_cwtc->cwtc_offset, 0);
}

static void dce_v6_0_cwtc_woad_wut(stwuct dwm_cwtc *cwtc)
{

	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	u16 *w, *g, *b;
	int i;

	DWM_DEBUG_KMS("%d\n", amdgpu_cwtc->cwtc_id);

	WWEG32(mmINPUT_CSC_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((0 << INPUT_CSC_CONTWOW__INPUT_CSC_GWPH_MODE__SHIFT) |
		(0 << INPUT_CSC_CONTWOW__INPUT_CSC_OVW_MODE__SHIFT)));
	WWEG32(mmPWESCAWE_GWPH_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       PWESCAWE_GWPH_CONTWOW__GWPH_PWESCAWE_BYPASS_MASK);
	WWEG32(mmPWESCAWE_OVW_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       PWESCAWE_OVW_CONTWOW__OVW_PWESCAWE_BYPASS_MASK);
	WWEG32(mmINPUT_GAMMA_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((0 << INPUT_GAMMA_CONTWOW__GWPH_INPUT_GAMMA_MODE__SHIFT) |
		(0 << INPUT_GAMMA_CONTWOW__OVW_INPUT_GAMMA_MODE__SHIFT)));

	WWEG32(mmDC_WUT_CONTWOW + amdgpu_cwtc->cwtc_offset, 0);

	WWEG32(mmDC_WUT_BWACK_OFFSET_BWUE + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmDC_WUT_BWACK_OFFSET_GWEEN + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmDC_WUT_BWACK_OFFSET_WED + amdgpu_cwtc->cwtc_offset, 0);

	WWEG32(mmDC_WUT_WHITE_OFFSET_BWUE + amdgpu_cwtc->cwtc_offset, 0xffff);
	WWEG32(mmDC_WUT_WHITE_OFFSET_GWEEN + amdgpu_cwtc->cwtc_offset, 0xffff);
	WWEG32(mmDC_WUT_WHITE_OFFSET_WED + amdgpu_cwtc->cwtc_offset, 0xffff);

	WWEG32(mmDC_WUT_WW_MODE + amdgpu_cwtc->cwtc_offset, 0);
	WWEG32(mmDC_WUT_WWITE_EN_MASK + amdgpu_cwtc->cwtc_offset, 0x00000007);

	WWEG32(mmDC_WUT_WW_INDEX + amdgpu_cwtc->cwtc_offset, 0);
	w = cwtc->gamma_stowe;
	g = w + cwtc->gamma_size;
	b = g + cwtc->gamma_size;
	fow (i = 0; i < 256; i++) {
		WWEG32(mmDC_WUT_30_COWOW + amdgpu_cwtc->cwtc_offset,
		       ((*w++ & 0xffc0) << 14) |
		       ((*g++ & 0xffc0) << 4) |
		       (*b++ >> 6));
	}

	WWEG32(mmDEGAMMA_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((0 << DEGAMMA_CONTWOW__GWPH_DEGAMMA_MODE__SHIFT) |
		(0 << DEGAMMA_CONTWOW__OVW_DEGAMMA_MODE__SHIFT) |
		ICON_DEGAMMA_MODE(0) |
		(0 << DEGAMMA_CONTWOW__CUWSOW_DEGAMMA_MODE__SHIFT)));
	WWEG32(mmGAMUT_WEMAP_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((0 << GAMUT_WEMAP_CONTWOW__GWPH_GAMUT_WEMAP_MODE__SHIFT) |
		(0 << GAMUT_WEMAP_CONTWOW__OVW_GAMUT_WEMAP_MODE__SHIFT)));
	WWEG32(mmWEGAMMA_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((0 << WEGAMMA_CONTWOW__GWPH_WEGAMMA_MODE__SHIFT) |
		(0 << WEGAMMA_CONTWOW__OVW_WEGAMMA_MODE__SHIFT)));
	WWEG32(mmOUTPUT_CSC_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       ((0 << OUTPUT_CSC_CONTWOW__OUTPUT_CSC_GWPH_MODE__SHIFT) |
		(0 << OUTPUT_CSC_CONTWOW__OUTPUT_CSC_OVW_MODE__SHIFT)));
	/* XXX match this to the depth of the cwtc fmt bwock, move to modeset? */
	WWEG32(0x1a50 + amdgpu_cwtc->cwtc_offset, 0);


}

static int dce_v6_0_pick_dig_encodew(stwuct dwm_encodew *encodew)
{
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;

	switch (amdgpu_encodew->encodew_id) {
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY:
		wetuwn dig->winkb ? 1 : 0;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1:
		wetuwn dig->winkb ? 3 : 2;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2:
		wetuwn dig->winkb ? 5 : 4;
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY3:
		wetuwn 6;
	defauwt:
		DWM_EWWOW("invawid encodew_id: 0x%x\n", amdgpu_encodew->encodew_id);
		wetuwn 0;
	}
}

/**
 * dce_v6_0_pick_pww - Awwocate a PPWW fow use by the cwtc.
 *
 * @cwtc: dwm cwtc
 *
 * Wetuwns the PPWW (Pixew PWW) to be used by the cwtc.  Fow DP monitows
 * a singwe PPWW can be used fow aww DP cwtcs/encodews.  Fow non-DP
 * monitows a dedicated PPWW must be used.  If a pawticuwaw boawd has
 * an extewnaw DP PWW, wetuwn ATOM_PPWW_INVAWID to skip PWW pwogwamming
 * as thewe is no need to pwogwam the PWW itsewf.  If we awe not abwe to
 * awwocate a PWW, wetuwn ATOM_PPWW_INVAWID to skip PWW pwogwamming to
 * avoid messing up an existing monitow.
 *
 *
 */
static u32 dce_v6_0_pick_pww(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	u32 pww_in_use;
	int pww;

	if (ENCODEW_MODE_IS_DP(amdgpu_atombios_encodew_get_encodew_mode(amdgpu_cwtc->encodew))) {
		if (adev->cwock.dp_extcwk)
			/* skip PPWW pwogwamming if using ext cwock */
			wetuwn ATOM_PPWW_INVAWID;
		ewse
			wetuwn ATOM_PPWW0;
	} ewse {
		/* use the same PPWW fow aww monitows with the same cwock */
		pww = amdgpu_pww_get_shawed_nondp_ppww(cwtc);
		if (pww != ATOM_PPWW_INVAWID)
			wetuwn pww;
	}

	/*  PPWW1, and PPWW2 */
	pww_in_use = amdgpu_pww_get_use_mask(cwtc);
	if (!(pww_in_use & (1 << ATOM_PPWW2)))
		wetuwn ATOM_PPWW2;
	if (!(pww_in_use & (1 << ATOM_PPWW1)))
		wetuwn ATOM_PPWW1;
	DWM_EWWOW("unabwe to awwocate a PPWW\n");
	wetuwn ATOM_PPWW_INVAWID;
}

static void dce_v6_0_wock_cuwsow(stwuct dwm_cwtc *cwtc, boow wock)
{
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	uint32_t cuw_wock;

	cuw_wock = WWEG32(mmCUW_UPDATE + amdgpu_cwtc->cwtc_offset);
	if (wock)
		cuw_wock |= CUW_UPDATE__CUWSOW_UPDATE_WOCK_MASK;
	ewse
		cuw_wock &= ~CUW_UPDATE__CUWSOW_UPDATE_WOCK_MASK;
	WWEG32(mmCUW_UPDATE + amdgpu_cwtc->cwtc_offset, cuw_wock);
}

static void dce_v6_0_hide_cuwsow(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);

	WWEG32(mmCUW_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       (CUWSOW_24_8_PWE_MUWT << CUW_CONTWOW__CUWSOW_MODE__SHIFT) |
	       (CUWSOW_UWGENT_1_2 << CUW_CONTWOW__CUWSOW_UWGENT_CONTWOW__SHIFT));


}

static void dce_v6_0_show_cuwsow(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);

	WWEG32(mmCUW_SUWFACE_ADDWESS_HIGH + amdgpu_cwtc->cwtc_offset,
	       uppew_32_bits(amdgpu_cwtc->cuwsow_addw));
	WWEG32(mmCUW_SUWFACE_ADDWESS + amdgpu_cwtc->cwtc_offset,
	       wowew_32_bits(amdgpu_cwtc->cuwsow_addw));

	WWEG32(mmCUW_CONTWOW + amdgpu_cwtc->cwtc_offset,
	       CUW_CONTWOW__CUWSOW_EN_MASK |
	       (CUWSOW_24_8_PWE_MUWT << CUW_CONTWOW__CUWSOW_MODE__SHIFT) |
	       (CUWSOW_UWGENT_1_2 << CUW_CONTWOW__CUWSOW_UWGENT_CONTWOW__SHIFT));

}

static int dce_v6_0_cuwsow_move_wocked(stwuct dwm_cwtc *cwtc,
				       int x, int y)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct amdgpu_device *adev = dwm_to_adev(cwtc->dev);
	int xowigin = 0, yowigin = 0;

	int w = amdgpu_cwtc->cuwsow_width;

	amdgpu_cwtc->cuwsow_x = x;
	amdgpu_cwtc->cuwsow_y = y;

	/* avivo cuwsow awe offset into the totaw suwface */
	x += cwtc->x;
	y += cwtc->y;
	DWM_DEBUG("x %d y %d c->x %d c->y %d\n", x, y, cwtc->x, cwtc->y);

	if (x < 0) {
		xowigin = min(-x, amdgpu_cwtc->max_cuwsow_width - 1);
		x = 0;
	}
	if (y < 0) {
		yowigin = min(-y, amdgpu_cwtc->max_cuwsow_height - 1);
		y = 0;
	}

	WWEG32(mmCUW_POSITION + amdgpu_cwtc->cwtc_offset, (x << 16) | y);
	WWEG32(mmCUW_HOT_SPOT + amdgpu_cwtc->cwtc_offset, (xowigin << 16) | yowigin);
	WWEG32(mmCUW_SIZE + amdgpu_cwtc->cwtc_offset,
	       ((w - 1) << 16) | (amdgpu_cwtc->cuwsow_height - 1));

	wetuwn 0;
}

static int dce_v6_0_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc,
				     int x, int y)
{
	int wet;

	dce_v6_0_wock_cuwsow(cwtc, twue);
	wet = dce_v6_0_cuwsow_move_wocked(cwtc, x, y);
	dce_v6_0_wock_cuwsow(cwtc, fawse);

	wetuwn wet;
}

static int dce_v6_0_cwtc_cuwsow_set2(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_fiwe *fiwe_pwiv,
				     uint32_t handwe,
				     uint32_t width,
				     uint32_t height,
				     int32_t hot_x,
				     int32_t hot_y)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_gem_object *obj;
	stwuct amdgpu_bo *aobj;
	int wet;

	if (!handwe) {
		/* tuwn off cuwsow */
		dce_v6_0_hide_cuwsow(cwtc);
		obj = NUWW;
		goto unpin;
	}

	if ((width > amdgpu_cwtc->max_cuwsow_width) ||
	    (height > amdgpu_cwtc->max_cuwsow_height)) {
		DWM_EWWOW("bad cuwsow width ow height %d x %d\n", width, height);
		wetuwn -EINVAW;
	}

	obj = dwm_gem_object_wookup(fiwe_pwiv, handwe);
	if (!obj) {
		DWM_EWWOW("Cannot find cuwsow object %x fow cwtc %d\n", handwe, amdgpu_cwtc->cwtc_id);
		wetuwn -ENOENT;
	}

	aobj = gem_to_amdgpu_bo(obj);
	wet = amdgpu_bo_wesewve(aobj, fawse);
	if (wet != 0) {
		dwm_gem_object_put(obj);
		wetuwn wet;
	}

	wet = amdgpu_bo_pin(aobj, AMDGPU_GEM_DOMAIN_VWAM);
	amdgpu_bo_unwesewve(aobj);
	if (wet) {
		DWM_EWWOW("Faiwed to pin new cuwsow BO (%d)\n", wet);
		dwm_gem_object_put(obj);
		wetuwn wet;
	}
	amdgpu_cwtc->cuwsow_addw = amdgpu_bo_gpu_offset(aobj);

	dce_v6_0_wock_cuwsow(cwtc, twue);

	if (width != amdgpu_cwtc->cuwsow_width ||
	    height != amdgpu_cwtc->cuwsow_height ||
	    hot_x != amdgpu_cwtc->cuwsow_hot_x ||
	    hot_y != amdgpu_cwtc->cuwsow_hot_y) {
		int x, y;

		x = amdgpu_cwtc->cuwsow_x + amdgpu_cwtc->cuwsow_hot_x - hot_x;
		y = amdgpu_cwtc->cuwsow_y + amdgpu_cwtc->cuwsow_hot_y - hot_y;

		dce_v6_0_cuwsow_move_wocked(cwtc, x, y);

		amdgpu_cwtc->cuwsow_width = width;
		amdgpu_cwtc->cuwsow_height = height;
		amdgpu_cwtc->cuwsow_hot_x = hot_x;
		amdgpu_cwtc->cuwsow_hot_y = hot_y;
	}

	dce_v6_0_show_cuwsow(cwtc);
	dce_v6_0_wock_cuwsow(cwtc, fawse);

unpin:
	if (amdgpu_cwtc->cuwsow_bo) {
		stwuct amdgpu_bo *aobj = gem_to_amdgpu_bo(amdgpu_cwtc->cuwsow_bo);
		wet = amdgpu_bo_wesewve(aobj, twue);
		if (wikewy(wet == 0)) {
			amdgpu_bo_unpin(aobj);
			amdgpu_bo_unwesewve(aobj);
		}
		dwm_gem_object_put(amdgpu_cwtc->cuwsow_bo);
	}

	amdgpu_cwtc->cuwsow_bo = obj;
	wetuwn 0;
}

static void dce_v6_0_cuwsow_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	if (amdgpu_cwtc->cuwsow_bo) {
		dce_v6_0_wock_cuwsow(cwtc, twue);

		dce_v6_0_cuwsow_move_wocked(cwtc, amdgpu_cwtc->cuwsow_x,
					    amdgpu_cwtc->cuwsow_y);

		dce_v6_0_show_cuwsow(cwtc);
		dce_v6_0_wock_cuwsow(cwtc, fawse);
	}
}

static int dce_v6_0_cwtc_gamma_set(stwuct dwm_cwtc *cwtc, u16 *wed, u16 *gween,
				   u16 *bwue, uint32_t size,
				   stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	dce_v6_0_cwtc_woad_wut(cwtc);

	wetuwn 0;
}

static void dce_v6_0_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	dwm_cwtc_cweanup(cwtc);
	kfwee(amdgpu_cwtc);
}

static const stwuct dwm_cwtc_funcs dce_v6_0_cwtc_funcs = {
	.cuwsow_set2 = dce_v6_0_cwtc_cuwsow_set2,
	.cuwsow_move = dce_v6_0_cwtc_cuwsow_move,
	.gamma_set = dce_v6_0_cwtc_gamma_set,
	.set_config = amdgpu_dispway_cwtc_set_config,
	.destwoy = dce_v6_0_cwtc_destwoy,
	.page_fwip_tawget = amdgpu_dispway_cwtc_page_fwip_tawget,
	.get_vbwank_countew = amdgpu_get_vbwank_countew_kms,
	.enabwe_vbwank = amdgpu_enabwe_vbwank_kms,
	.disabwe_vbwank = amdgpu_disabwe_vbwank_kms,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
};

static void dce_v6_0_cwtc_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	unsigned type;

	switch (mode) {
	case DWM_MODE_DPMS_ON:
		amdgpu_cwtc->enabwed = twue;
		amdgpu_atombios_cwtc_enabwe(cwtc, ATOM_ENABWE);
		amdgpu_atombios_cwtc_bwank(cwtc, ATOM_DISABWE);
		/* Make suwe VBWANK and PFWIP intewwupts awe stiww enabwed */
		type = amdgpu_dispway_cwtc_idx_to_iwq_type(adev,
						amdgpu_cwtc->cwtc_id);
		amdgpu_iwq_update(adev, &adev->cwtc_iwq, type);
		amdgpu_iwq_update(adev, &adev->pagefwip_iwq, type);
		dwm_cwtc_vbwank_on(cwtc);
		dce_v6_0_cwtc_woad_wut(cwtc);
		bweak;
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
	case DWM_MODE_DPMS_OFF:
		dwm_cwtc_vbwank_off(cwtc);
		if (amdgpu_cwtc->enabwed)
			amdgpu_atombios_cwtc_bwank(cwtc, ATOM_ENABWE);
		amdgpu_atombios_cwtc_enabwe(cwtc, ATOM_DISABWE);
		amdgpu_cwtc->enabwed = fawse;
		bweak;
	}
	/* adjust pm to dpms */
	amdgpu_dpm_compute_cwocks(adev);
}

static void dce_v6_0_cwtc_pwepawe(stwuct dwm_cwtc *cwtc)
{
	/* disabwe cwtc paiw powew gating befowe pwogwamming */
	amdgpu_atombios_cwtc_powewgate(cwtc, ATOM_DISABWE);
	amdgpu_atombios_cwtc_wock(cwtc, ATOM_ENABWE);
	dce_v6_0_cwtc_dpms(cwtc, DWM_MODE_DPMS_OFF);
}

static void dce_v6_0_cwtc_commit(stwuct dwm_cwtc *cwtc)
{
	dce_v6_0_cwtc_dpms(cwtc, DWM_MODE_DPMS_ON);
	amdgpu_atombios_cwtc_wock(cwtc, ATOM_DISABWE);
}

static void dce_v6_0_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{

	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_atom_ss ss;
	int i;

	dce_v6_0_cwtc_dpms(cwtc, DWM_MODE_DPMS_OFF);
	if (cwtc->pwimawy->fb) {
		int w;
		stwuct amdgpu_bo *abo;

		abo = gem_to_amdgpu_bo(cwtc->pwimawy->fb->obj[0]);
		w = amdgpu_bo_wesewve(abo, twue);
		if (unwikewy(w))
			DWM_EWWOW("faiwed to wesewve abo befowe unpin\n");
		ewse {
			amdgpu_bo_unpin(abo);
			amdgpu_bo_unwesewve(abo);
		}
	}
	/* disabwe the GWPH */
	dce_v6_0_gwph_enabwe(cwtc, fawse);

	amdgpu_atombios_cwtc_powewgate(cwtc, ATOM_ENABWE);

	fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
		if (adev->mode_info.cwtcs[i] &&
		    adev->mode_info.cwtcs[i]->enabwed &&
		    i != amdgpu_cwtc->cwtc_id &&
		    amdgpu_cwtc->pww_id == adev->mode_info.cwtcs[i]->pww_id) {
			/* one othew cwtc is using this pww don't tuwn
			 * off the pww
			 */
			goto done;
		}
	}

	switch (amdgpu_cwtc->pww_id) {
	case ATOM_PPWW1:
	case ATOM_PPWW2:
		/* disabwe the ppww */
		amdgpu_atombios_cwtc_pwogwam_pww(cwtc, amdgpu_cwtc->cwtc_id, amdgpu_cwtc->pww_id,
						 0, 0, ATOM_DISABWE, 0, 0, 0, 0, 0, fawse, &ss);
		bweak;
	defauwt:
		bweak;
	}
done:
	amdgpu_cwtc->pww_id = ATOM_PPWW_INVAWID;
	amdgpu_cwtc->adjusted_cwock = 0;
	amdgpu_cwtc->encodew = NUWW;
	amdgpu_cwtc->connectow = NUWW;
}

static int dce_v6_0_cwtc_mode_set(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode,
				  int x, int y, stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);

	if (!amdgpu_cwtc->adjusted_cwock)
		wetuwn -EINVAW;

	amdgpu_atombios_cwtc_set_pww(cwtc, adjusted_mode);
	amdgpu_atombios_cwtc_set_dtd_timing(cwtc, adjusted_mode);
	dce_v6_0_cwtc_do_set_base(cwtc, owd_fb, x, y, 0);
	amdgpu_atombios_cwtc_ovewscan_setup(cwtc, mode, adjusted_mode);
	amdgpu_atombios_cwtc_scawew_setup(cwtc);
	dce_v6_0_cuwsow_weset(cwtc);
	/* update the hw vewsion fpw dpm */
	amdgpu_cwtc->hw_mode = *adjusted_mode;

	wetuwn 0;
}

static boow dce_v6_0_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				     const stwuct dwm_dispway_mode *mode,
				     stwuct dwm_dispway_mode *adjusted_mode)
{

	stwuct amdgpu_cwtc *amdgpu_cwtc = to_amdgpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_encodew *encodew;

	/* assign the encodew to the amdgpu cwtc to avoid wepeated wookups watew */
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->cwtc == cwtc) {
			amdgpu_cwtc->encodew = encodew;
			amdgpu_cwtc->connectow = amdgpu_get_connectow_fow_encodew(encodew);
			bweak;
		}
	}
	if ((amdgpu_cwtc->encodew == NUWW) || (amdgpu_cwtc->connectow == NUWW)) {
		amdgpu_cwtc->encodew = NUWW;
		amdgpu_cwtc->connectow = NUWW;
		wetuwn fawse;
	}
	if (!amdgpu_dispway_cwtc_scawing_mode_fixup(cwtc, mode, adjusted_mode))
		wetuwn fawse;
	if (amdgpu_atombios_cwtc_pwepawe_pww(cwtc, adjusted_mode))
		wetuwn fawse;
	/* pick pww */
	amdgpu_cwtc->pww_id = dce_v6_0_pick_pww(cwtc);
	/* if we can't get a PPWW fow a non-DP encodew, faiw */
	if ((amdgpu_cwtc->pww_id == ATOM_PPWW_INVAWID) &&
	    !ENCODEW_MODE_IS_DP(amdgpu_atombios_encodew_get_encodew_mode(amdgpu_cwtc->encodew)))
		wetuwn fawse;

	wetuwn twue;
}

static int dce_v6_0_cwtc_set_base(stwuct dwm_cwtc *cwtc, int x, int y,
				  stwuct dwm_fwamebuffew *owd_fb)
{
	wetuwn dce_v6_0_cwtc_do_set_base(cwtc, owd_fb, x, y, 0);
}

static int dce_v6_0_cwtc_set_base_atomic(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_fwamebuffew *fb,
					 int x, int y, enum mode_set_atomic state)
{
	wetuwn dce_v6_0_cwtc_do_set_base(cwtc, fb, x, y, 1);
}

static const stwuct dwm_cwtc_hewpew_funcs dce_v6_0_cwtc_hewpew_funcs = {
	.dpms = dce_v6_0_cwtc_dpms,
	.mode_fixup = dce_v6_0_cwtc_mode_fixup,
	.mode_set = dce_v6_0_cwtc_mode_set,
	.mode_set_base = dce_v6_0_cwtc_set_base,
	.mode_set_base_atomic = dce_v6_0_cwtc_set_base_atomic,
	.pwepawe = dce_v6_0_cwtc_pwepawe,
	.commit = dce_v6_0_cwtc_commit,
	.disabwe = dce_v6_0_cwtc_disabwe,
	.get_scanout_position = amdgpu_cwtc_get_scanout_position,
};

static int dce_v6_0_cwtc_init(stwuct amdgpu_device *adev, int index)
{
	stwuct amdgpu_cwtc *amdgpu_cwtc;

	amdgpu_cwtc = kzawwoc(sizeof(stwuct amdgpu_cwtc) +
			      (AMDGPUFB_CONN_WIMIT * sizeof(stwuct dwm_connectow *)), GFP_KEWNEW);
	if (amdgpu_cwtc == NUWW)
		wetuwn -ENOMEM;

	dwm_cwtc_init(adev_to_dwm(adev), &amdgpu_cwtc->base, &dce_v6_0_cwtc_funcs);

	dwm_mode_cwtc_set_gamma_size(&amdgpu_cwtc->base, 256);
	amdgpu_cwtc->cwtc_id = index;
	adev->mode_info.cwtcs[index] = amdgpu_cwtc;

	amdgpu_cwtc->max_cuwsow_width = CUWSOW_WIDTH;
	amdgpu_cwtc->max_cuwsow_height = CUWSOW_HEIGHT;
	adev_to_dwm(adev)->mode_config.cuwsow_width = amdgpu_cwtc->max_cuwsow_width;
	adev_to_dwm(adev)->mode_config.cuwsow_height = amdgpu_cwtc->max_cuwsow_height;

	amdgpu_cwtc->cwtc_offset = cwtc_offsets[amdgpu_cwtc->cwtc_id];

	amdgpu_cwtc->pww_id = ATOM_PPWW_INVAWID;
	amdgpu_cwtc->adjusted_cwock = 0;
	amdgpu_cwtc->encodew = NUWW;
	amdgpu_cwtc->connectow = NUWW;
	dwm_cwtc_hewpew_add(&amdgpu_cwtc->base, &dce_v6_0_cwtc_hewpew_funcs);

	wetuwn 0;
}

static int dce_v6_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->audio_endpt_wweg = &dce_v6_0_audio_endpt_wweg;
	adev->audio_endpt_wweg = &dce_v6_0_audio_endpt_wweg;

	dce_v6_0_set_dispway_funcs(adev);

	adev->mode_info.num_cwtc = dce_v6_0_get_num_cwtc(adev);

	switch (adev->asic_type) {
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
		adev->mode_info.num_hpd = 6;
		adev->mode_info.num_dig = 6;
		bweak;
	case CHIP_OWAND:
		adev->mode_info.num_hpd = 2;
		adev->mode_info.num_dig = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dce_v6_0_set_iwq_funcs(adev);

	wetuwn 0;
}

static int dce_v6_0_sw_init(void *handwe)
{
	int w, i;
	boow wet;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
		w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, i + 1, &adev->cwtc_iwq);
		if (w)
			wetuwn w;
	}

	fow (i = 8; i < 20; i += 2) {
		w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, i, &adev->pagefwip_iwq);
		if (w)
			wetuwn w;
	}

	/* HPD hotpwug */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 42, &adev->hpd_iwq);
	if (w)
		wetuwn w;

	adev->mode_info.mode_config_initiawized = twue;

	adev_to_dwm(adev)->mode_config.funcs = &amdgpu_mode_funcs;
	adev_to_dwm(adev)->mode_config.async_page_fwip = twue;
	adev_to_dwm(adev)->mode_config.max_width = 16384;
	adev_to_dwm(adev)->mode_config.max_height = 16384;
	adev_to_dwm(adev)->mode_config.pwefewwed_depth = 24;
	adev_to_dwm(adev)->mode_config.pwefew_shadow = 1;
	adev_to_dwm(adev)->mode_config.fb_modifiews_not_suppowted = twue;

	w = amdgpu_dispway_modeset_cweate_pwops(adev);
	if (w)
		wetuwn w;

	adev_to_dwm(adev)->mode_config.max_width = 16384;
	adev_to_dwm(adev)->mode_config.max_height = 16384;

	/* awwocate cwtcs */
	fow (i = 0; i < adev->mode_info.num_cwtc; i++) {
		w = dce_v6_0_cwtc_init(adev, i);
		if (w)
			wetuwn w;
	}

	wet = amdgpu_atombios_get_connectow_info_fwom_object_tabwe(adev);
	if (wet)
		amdgpu_dispway_pwint_dispway_setup(adev_to_dwm(adev));
	ewse
		wetuwn -EINVAW;

	/* setup afmt */
	w = dce_v6_0_afmt_init(adev);
	if (w)
		wetuwn w;

	w = dce_v6_0_audio_init(adev);
	if (w)
		wetuwn w;

	/* Disabwe vbwank IWQs aggwessivewy fow powew-saving */
	/* XXX: can this be enabwed fow DC? */
	adev_to_dwm(adev)->vbwank_disabwe_immediate = twue;

	w = dwm_vbwank_init(adev_to_dwm(adev), adev->mode_info.num_cwtc);
	if (w)
		wetuwn w;

	/* Pwe-DCE11 */
	INIT_DEWAYED_WOWK(&adev->hotpwug_wowk,
		  amdgpu_dispway_hotpwug_wowk_func);

	dwm_kms_hewpew_poww_init(adev_to_dwm(adev));

	wetuwn w;
}

static int dce_v6_0_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	kfwee(adev->mode_info.bios_hawdcoded_edid);

	dwm_kms_hewpew_poww_fini(adev_to_dwm(adev));

	dce_v6_0_audio_fini(adev);
	dce_v6_0_afmt_fini(adev);

	dwm_mode_config_cweanup(adev_to_dwm(adev));
	adev->mode_info.mode_config_initiawized = fawse;

	wetuwn 0;
}

static int dce_v6_0_hw_init(void *handwe)
{
	int i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* disabwe vga wendew */
	dce_v6_0_set_vga_wendew_state(adev, fawse);
	/* init dig PHYs, disp eng pww */
	amdgpu_atombios_encodew_init_dig(adev);
	amdgpu_atombios_cwtc_set_disp_eng_pww(adev, adev->cwock.defauwt_dispcwk);

	/* initiawize hpd */
	dce_v6_0_hpd_init(adev);

	fow (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		dce_v6_0_audio_enabwe(adev, &adev->mode_info.audio.pin[i], fawse);
	}

	dce_v6_0_pagefwip_intewwupt_init(adev);

	wetuwn 0;
}

static int dce_v6_0_hw_fini(void *handwe)
{
	int i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	dce_v6_0_hpd_fini(adev);

	fow (i = 0; i < adev->mode_info.audio.num_pins; i++) {
		dce_v6_0_audio_enabwe(adev, &adev->mode_info.audio.pin[i], fawse);
	}

	dce_v6_0_pagefwip_intewwupt_fini(adev);

	fwush_dewayed_wowk(&adev->hotpwug_wowk);

	wetuwn 0;
}

static int dce_v6_0_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_dispway_suspend_hewpew(adev);
	if (w)
		wetuwn w;
	adev->mode_info.bw_wevew =
		amdgpu_atombios_encodew_get_backwight_wevew_fwom_weg(adev);

	wetuwn dce_v6_0_hw_fini(handwe);
}

static int dce_v6_0_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	amdgpu_atombios_encodew_set_backwight_wevew_to_weg(adev,
							   adev->mode_info.bw_wevew);

	wet = dce_v6_0_hw_init(handwe);

	/* tuwn on the BW */
	if (adev->mode_info.bw_encodew) {
		u8 bw_wevew = amdgpu_dispway_backwight_get_wevew(adev,
								  adev->mode_info.bw_encodew);
		amdgpu_dispway_backwight_set_wevew(adev, adev->mode_info.bw_encodew,
						    bw_wevew);
	}
	if (wet)
		wetuwn wet;

	wetuwn amdgpu_dispway_wesume_hewpew(adev);
}

static boow dce_v6_0_is_idwe(void *handwe)
{
	wetuwn twue;
}

static int dce_v6_0_wait_fow_idwe(void *handwe)
{
	wetuwn 0;
}

static int dce_v6_0_soft_weset(void *handwe)
{
	DWM_INFO("xxxx: dce_v6_0_soft_weset --- no impw!!\n");
	wetuwn 0;
}

static void dce_v6_0_set_cwtc_vbwank_intewwupt_state(stwuct amdgpu_device *adev,
						     int cwtc,
						     enum amdgpu_intewwupt_state state)
{
	u32 weg_bwock, intewwupt_mask;

	if (cwtc >= adev->mode_info.num_cwtc) {
		DWM_DEBUG("invawid cwtc %d\n", cwtc);
		wetuwn;
	}

	switch (cwtc) {
	case 0:
		weg_bwock = SI_CWTC0_WEGISTEW_OFFSET;
		bweak;
	case 1:
		weg_bwock = SI_CWTC1_WEGISTEW_OFFSET;
		bweak;
	case 2:
		weg_bwock = SI_CWTC2_WEGISTEW_OFFSET;
		bweak;
	case 3:
		weg_bwock = SI_CWTC3_WEGISTEW_OFFSET;
		bweak;
	case 4:
		weg_bwock = SI_CWTC4_WEGISTEW_OFFSET;
		bweak;
	case 5:
		weg_bwock = SI_CWTC5_WEGISTEW_OFFSET;
		bweak;
	defauwt:
		DWM_DEBUG("invawid cwtc %d\n", cwtc);
		wetuwn;
	}

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		intewwupt_mask = WWEG32(mmINT_MASK + weg_bwock);
		intewwupt_mask &= ~VBWANK_INT_MASK;
		WWEG32(mmINT_MASK + weg_bwock, intewwupt_mask);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		intewwupt_mask = WWEG32(mmINT_MASK + weg_bwock);
		intewwupt_mask |= VBWANK_INT_MASK;
		WWEG32(mmINT_MASK + weg_bwock, intewwupt_mask);
		bweak;
	defauwt:
		bweak;
	}
}

static void dce_v6_0_set_cwtc_vwine_intewwupt_state(stwuct amdgpu_device *adev,
						    int cwtc,
						    enum amdgpu_intewwupt_state state)
{

}

static int dce_v6_0_set_hpd_intewwupt_state(stwuct amdgpu_device *adev,
					    stwuct amdgpu_iwq_swc *swc,
					    unsigned type,
					    enum amdgpu_intewwupt_state state)
{
	u32 dc_hpd_int_cntw;

	if (type >= adev->mode_info.num_hpd) {
		DWM_DEBUG("invawid hdp %d\n", type);
		wetuwn 0;
	}

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		dc_hpd_int_cntw = WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[type]);
		dc_hpd_int_cntw &= ~DC_HPDx_INT_EN;
		WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[type], dc_hpd_int_cntw);
		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		dc_hpd_int_cntw = WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[type]);
		dc_hpd_int_cntw |= DC_HPDx_INT_EN;
		WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[type], dc_hpd_int_cntw);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int dce_v6_0_set_cwtc_intewwupt_state(stwuct amdgpu_device *adev,
					     stwuct amdgpu_iwq_swc *swc,
					     unsigned type,
					     enum amdgpu_intewwupt_state state)
{
	switch (type) {
	case AMDGPU_CWTC_IWQ_VBWANK1:
		dce_v6_0_set_cwtc_vbwank_intewwupt_state(adev, 0, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VBWANK2:
		dce_v6_0_set_cwtc_vbwank_intewwupt_state(adev, 1, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VBWANK3:
		dce_v6_0_set_cwtc_vbwank_intewwupt_state(adev, 2, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VBWANK4:
		dce_v6_0_set_cwtc_vbwank_intewwupt_state(adev, 3, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VBWANK5:
		dce_v6_0_set_cwtc_vbwank_intewwupt_state(adev, 4, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VBWANK6:
		dce_v6_0_set_cwtc_vbwank_intewwupt_state(adev, 5, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VWINE1:
		dce_v6_0_set_cwtc_vwine_intewwupt_state(adev, 0, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VWINE2:
		dce_v6_0_set_cwtc_vwine_intewwupt_state(adev, 1, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VWINE3:
		dce_v6_0_set_cwtc_vwine_intewwupt_state(adev, 2, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VWINE4:
		dce_v6_0_set_cwtc_vwine_intewwupt_state(adev, 3, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VWINE5:
		dce_v6_0_set_cwtc_vwine_intewwupt_state(adev, 4, state);
		bweak;
	case AMDGPU_CWTC_IWQ_VWINE6:
		dce_v6_0_set_cwtc_vwine_intewwupt_state(adev, 5, state);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int dce_v6_0_cwtc_iwq(stwuct amdgpu_device *adev,
			     stwuct amdgpu_iwq_swc *souwce,
			     stwuct amdgpu_iv_entwy *entwy)
{
	unsigned cwtc = entwy->swc_id - 1;
	uint32_t disp_int = WWEG32(intewwupt_status_offsets[cwtc].weg);
	unsigned int iwq_type = amdgpu_dispway_cwtc_idx_to_iwq_type(adev,
								    cwtc);

	switch (entwy->swc_data[0]) {
	case 0: /* vbwank */
		if (disp_int & intewwupt_status_offsets[cwtc].vbwank)
			WWEG32(mmVBWANK_STATUS + cwtc_offsets[cwtc], VBWANK_ACK);
		ewse
			DWM_DEBUG("IH: IH event w/o assewted iwq bit?\n");

		if (amdgpu_iwq_enabwed(adev, souwce, iwq_type)) {
			dwm_handwe_vbwank(adev_to_dwm(adev), cwtc);
		}
		DWM_DEBUG("IH: D%d vbwank\n", cwtc + 1);
		bweak;
	case 1: /* vwine */
		if (disp_int & intewwupt_status_offsets[cwtc].vwine)
			WWEG32(mmVWINE_STATUS + cwtc_offsets[cwtc], VWINE_ACK);
		ewse
			DWM_DEBUG("IH: IH event w/o assewted iwq bit?\n");

		DWM_DEBUG("IH: D%d vwine\n", cwtc + 1);
		bweak;
	defauwt:
		DWM_DEBUG("Unhandwed intewwupt: %d %d\n", entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static int dce_v6_0_set_pagefwip_intewwupt_state(stwuct amdgpu_device *adev,
						 stwuct amdgpu_iwq_swc *swc,
						 unsigned type,
						 enum amdgpu_intewwupt_state state)
{
	u32 weg;

	if (type >= adev->mode_info.num_cwtc) {
		DWM_EWWOW("invawid pagefwip cwtc %d\n", type);
		wetuwn -EINVAW;
	}

	weg = WWEG32(mmGWPH_INTEWWUPT_CONTWOW + cwtc_offsets[type]);
	if (state == AMDGPU_IWQ_STATE_DISABWE)
		WWEG32(mmGWPH_INTEWWUPT_CONTWOW + cwtc_offsets[type],
		       weg & ~GWPH_INTEWWUPT_CONTWOW__GWPH_PFWIP_INT_MASK_MASK);
	ewse
		WWEG32(mmGWPH_INTEWWUPT_CONTWOW + cwtc_offsets[type],
		       weg | GWPH_INTEWWUPT_CONTWOW__GWPH_PFWIP_INT_MASK_MASK);

	wetuwn 0;
}

static int dce_v6_0_pagefwip_iwq(stwuct amdgpu_device *adev,
				 stwuct amdgpu_iwq_swc *souwce,
				 stwuct amdgpu_iv_entwy *entwy)
{
	unsigned wong fwags;
	unsigned cwtc_id;
	stwuct amdgpu_cwtc *amdgpu_cwtc;
	stwuct amdgpu_fwip_wowk *wowks;

	cwtc_id = (entwy->swc_id - 8) >> 1;
	amdgpu_cwtc = adev->mode_info.cwtcs[cwtc_id];

	if (cwtc_id >= adev->mode_info.num_cwtc) {
		DWM_EWWOW("invawid pagefwip cwtc %d\n", cwtc_id);
		wetuwn -EINVAW;
	}

	if (WWEG32(mmGWPH_INTEWWUPT_STATUS + cwtc_offsets[cwtc_id]) &
	    GWPH_INTEWWUPT_STATUS__GWPH_PFWIP_INT_OCCUWWED_MASK)
		WWEG32(mmGWPH_INTEWWUPT_STATUS + cwtc_offsets[cwtc_id],
		       GWPH_INTEWWUPT_STATUS__GWPH_PFWIP_INT_CWEAW_MASK);

	/* IWQ couwd occuw when in initiaw stage */
	if (amdgpu_cwtc == NUWW)
		wetuwn 0;

	spin_wock_iwqsave(&adev_to_dwm(adev)->event_wock, fwags);
	wowks = amdgpu_cwtc->pfwip_wowks;
	if (amdgpu_cwtc->pfwip_status != AMDGPU_FWIP_SUBMITTED){
		DWM_DEBUG_DWIVEW("amdgpu_cwtc->pfwip_status = %d != "
						"AMDGPU_FWIP_SUBMITTED(%d)\n",
						amdgpu_cwtc->pfwip_status,
						AMDGPU_FWIP_SUBMITTED);
		spin_unwock_iwqwestowe(&adev_to_dwm(adev)->event_wock, fwags);
		wetuwn 0;
	}

	/* page fwip compweted. cwean up */
	amdgpu_cwtc->pfwip_status = AMDGPU_FWIP_NONE;
	amdgpu_cwtc->pfwip_wowks = NUWW;

	/* wakeup usewsapce */
	if (wowks->event)
		dwm_cwtc_send_vbwank_event(&amdgpu_cwtc->base, wowks->event);

	spin_unwock_iwqwestowe(&adev_to_dwm(adev)->event_wock, fwags);

	dwm_cwtc_vbwank_put(&amdgpu_cwtc->base);
	scheduwe_wowk(&wowks->unpin_wowk);

	wetuwn 0;
}

static int dce_v6_0_hpd_iwq(stwuct amdgpu_device *adev,
			    stwuct amdgpu_iwq_swc *souwce,
			    stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t disp_int, mask, tmp;
	unsigned hpd;

	if (entwy->swc_data[0] >= adev->mode_info.num_hpd) {
		DWM_DEBUG("Unhandwed intewwupt: %d %d\n", entwy->swc_id, entwy->swc_data[0]);
		wetuwn 0;
	}

	hpd = entwy->swc_data[0];
	disp_int = WWEG32(intewwupt_status_offsets[hpd].weg);
	mask = intewwupt_status_offsets[hpd].hpd;

	if (disp_int & mask) {
		tmp = WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[hpd]);
		tmp |= DC_HPD1_INT_CONTWOW__DC_HPD1_INT_ACK_MASK;
		WWEG32(mmDC_HPD1_INT_CONTWOW + hpd_offsets[hpd], tmp);
		scheduwe_dewayed_wowk(&adev->hotpwug_wowk, 0);
		DWM_DEBUG("IH: HPD%d\n", hpd + 1);
	}

	wetuwn 0;

}

static int dce_v6_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static int dce_v6_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	wetuwn 0;
}

static const stwuct amd_ip_funcs dce_v6_0_ip_funcs = {
	.name = "dce_v6_0",
	.eawwy_init = dce_v6_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = dce_v6_0_sw_init,
	.sw_fini = dce_v6_0_sw_fini,
	.hw_init = dce_v6_0_hw_init,
	.hw_fini = dce_v6_0_hw_fini,
	.suspend = dce_v6_0_suspend,
	.wesume = dce_v6_0_wesume,
	.is_idwe = dce_v6_0_is_idwe,
	.wait_fow_idwe = dce_v6_0_wait_fow_idwe,
	.soft_weset = dce_v6_0_soft_weset,
	.set_cwockgating_state = dce_v6_0_set_cwockgating_state,
	.set_powewgating_state = dce_v6_0_set_powewgating_state,
};

static void
dce_v6_0_encodew_mode_set(stwuct dwm_encodew *encodew,
			  stwuct dwm_dispway_mode *mode,
			  stwuct dwm_dispway_mode *adjusted_mode)
{

	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	int em = amdgpu_atombios_encodew_get_encodew_mode(encodew);

	amdgpu_encodew->pixew_cwock = adjusted_mode->cwock;

	/* need to caww this hewe wathew than in pwepawe() since we need some cwtc info */
	amdgpu_atombios_encodew_dpms(encodew, DWM_MODE_DPMS_OFF);

	/* set scawew cweaws this on some chips */
	dce_v6_0_set_intewweave(encodew->cwtc, mode);

	if (em == ATOM_ENCODEW_MODE_HDMI || ENCODEW_MODE_IS_DP(em)) {
		dce_v6_0_afmt_enabwe(encodew, twue);
		dce_v6_0_afmt_setmode(encodew, adjusted_mode);
	}
}

static void dce_v6_0_encodew_pwepawe(stwuct dwm_encodew *encodew)
{

	stwuct amdgpu_device *adev = dwm_to_adev(encodew->dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct dwm_connectow *connectow = amdgpu_get_connectow_fow_encodew(encodew);

	if ((amdgpu_encodew->active_device &
	     (ATOM_DEVICE_DFP_SUPPOWT | ATOM_DEVICE_WCD_SUPPOWT)) ||
	    (amdgpu_encodew_get_dp_bwidge_encodew_id(encodew) !=
	     ENCODEW_OBJECT_ID_NONE)) {
		stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
		if (dig) {
			dig->dig_encodew = dce_v6_0_pick_dig_encodew(encodew);
			if (amdgpu_encodew->active_device & ATOM_DEVICE_DFP_SUPPOWT)
				dig->afmt = adev->mode_info.afmt[dig->dig_encodew];
		}
	}

	amdgpu_atombios_scwatch_wegs_wock(adev, twue);

	if (connectow) {
		stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);

		/* sewect the cwock/data powt if it uses a woutew */
		if (amdgpu_connectow->woutew.cd_vawid)
			amdgpu_i2c_woutew_sewect_cd_powt(amdgpu_connectow);

		/* tuwn eDP panew on fow mode set */
		if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP)
			amdgpu_atombios_encodew_set_edp_panew_powew(connectow,
							     ATOM_TWANSMITTEW_ACTION_POWEW_ON);
	}

	/* this is needed fow the pww/ss setup to wowk cowwectwy in some cases */
	amdgpu_atombios_encodew_set_cwtc_souwce(encodew);
	/* set up the FMT bwocks */
	dce_v6_0_pwogwam_fmt(encodew);
}

static void dce_v6_0_encodew_commit(stwuct dwm_encodew *encodew)
{

	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	/* need to caww this hewe as we need the cwtc set up */
	amdgpu_atombios_encodew_dpms(encodew, DWM_MODE_DPMS_ON);
	amdgpu_atombios_scwatch_wegs_wock(adev, fawse);
}

static void dce_v6_0_encodew_disabwe(stwuct dwm_encodew *encodew)
{

	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_encodew_atom_dig *dig;
	int em = amdgpu_atombios_encodew_get_encodew_mode(encodew);

	amdgpu_atombios_encodew_dpms(encodew, DWM_MODE_DPMS_OFF);

	if (amdgpu_atombios_encodew_is_digitaw(encodew)) {
		if (em == ATOM_ENCODEW_MODE_HDMI || ENCODEW_MODE_IS_DP(em))
			dce_v6_0_afmt_enabwe(encodew, fawse);
		dig = amdgpu_encodew->enc_pwiv;
		dig->dig_encodew = -1;
	}
	amdgpu_encodew->active_device = 0;
}

/* these awe handwed by the pwimawy encodews */
static void dce_v6_0_ext_pwepawe(stwuct dwm_encodew *encodew)
{

}

static void dce_v6_0_ext_commit(stwuct dwm_encodew *encodew)
{

}

static void
dce_v6_0_ext_mode_set(stwuct dwm_encodew *encodew,
		      stwuct dwm_dispway_mode *mode,
		      stwuct dwm_dispway_mode *adjusted_mode)
{

}

static void dce_v6_0_ext_disabwe(stwuct dwm_encodew *encodew)
{

}

static void
dce_v6_0_ext_dpms(stwuct dwm_encodew *encodew, int mode)
{

}

static boow dce_v6_0_ext_mode_fixup(stwuct dwm_encodew *encodew,
				    const stwuct dwm_dispway_mode *mode,
				    stwuct dwm_dispway_mode *adjusted_mode)
{
	wetuwn twue;
}

static const stwuct dwm_encodew_hewpew_funcs dce_v6_0_ext_hewpew_funcs = {
	.dpms = dce_v6_0_ext_dpms,
	.mode_fixup = dce_v6_0_ext_mode_fixup,
	.pwepawe = dce_v6_0_ext_pwepawe,
	.mode_set = dce_v6_0_ext_mode_set,
	.commit = dce_v6_0_ext_commit,
	.disabwe = dce_v6_0_ext_disabwe,
	/* no detect fow TMDS/WVDS yet */
};

static const stwuct dwm_encodew_hewpew_funcs dce_v6_0_dig_hewpew_funcs = {
	.dpms = amdgpu_atombios_encodew_dpms,
	.mode_fixup = amdgpu_atombios_encodew_mode_fixup,
	.pwepawe = dce_v6_0_encodew_pwepawe,
	.mode_set = dce_v6_0_encodew_mode_set,
	.commit = dce_v6_0_encodew_commit,
	.disabwe = dce_v6_0_encodew_disabwe,
	.detect = amdgpu_atombios_encodew_dig_detect,
};

static const stwuct dwm_encodew_hewpew_funcs dce_v6_0_dac_hewpew_funcs = {
	.dpms = amdgpu_atombios_encodew_dpms,
	.mode_fixup = amdgpu_atombios_encodew_mode_fixup,
	.pwepawe = dce_v6_0_encodew_pwepawe,
	.mode_set = dce_v6_0_encodew_mode_set,
	.commit = dce_v6_0_encodew_commit,
	.detect = amdgpu_atombios_encodew_dac_detect,
};

static void dce_v6_0_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	if (amdgpu_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT))
		amdgpu_atombios_encodew_fini_backwight(amdgpu_encodew);
	kfwee(amdgpu_encodew->enc_pwiv);
	dwm_encodew_cweanup(encodew);
	kfwee(amdgpu_encodew);
}

static const stwuct dwm_encodew_funcs dce_v6_0_encodew_funcs = {
	.destwoy = dce_v6_0_encodew_destwoy,
};

static void dce_v6_0_encodew_add(stwuct amdgpu_device *adev,
				 uint32_t encodew_enum,
				 uint32_t suppowted_device,
				 u16 caps)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	stwuct dwm_encodew *encodew;
	stwuct amdgpu_encodew *amdgpu_encodew;

	/* see if we awweady added it */
	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		amdgpu_encodew = to_amdgpu_encodew(encodew);
		if (amdgpu_encodew->encodew_enum == encodew_enum) {
			amdgpu_encodew->devices |= suppowted_device;
			wetuwn;
		}

	}

	/* add a new one */
	amdgpu_encodew = kzawwoc(sizeof(stwuct amdgpu_encodew), GFP_KEWNEW);
	if (!amdgpu_encodew)
		wetuwn;

	encodew = &amdgpu_encodew->base;
	switch (adev->mode_info.num_cwtc) {
	case 1:
		encodew->possibwe_cwtcs = 0x1;
		bweak;
	case 2:
	defauwt:
		encodew->possibwe_cwtcs = 0x3;
		bweak;
	case 4:
		encodew->possibwe_cwtcs = 0xf;
		bweak;
	case 6:
		encodew->possibwe_cwtcs = 0x3f;
		bweak;
	}

	amdgpu_encodew->enc_pwiv = NUWW;
	amdgpu_encodew->encodew_enum = encodew_enum;
	amdgpu_encodew->encodew_id = (encodew_enum & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	amdgpu_encodew->devices = suppowted_device;
	amdgpu_encodew->wmx_type = WMX_OFF;
	amdgpu_encodew->undewscan_type = UNDEWSCAN_OFF;
	amdgpu_encodew->is_ext_encodew = fawse;
	amdgpu_encodew->caps = caps;

	switch (amdgpu_encodew->encodew_id) {
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC1:
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC2:
		dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
				 DWM_MODE_ENCODEW_DAC, NUWW);
		dwm_encodew_hewpew_add(encodew, &dce_v6_0_dac_hewpew_funcs);
		bweak;
	case ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DVO1:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2:
	case ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY3:
		if (amdgpu_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT)) {
			amdgpu_encodew->wmx_type = WMX_FUWW;
			dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
					 DWM_MODE_ENCODEW_WVDS, NUWW);
			amdgpu_encodew->enc_pwiv = amdgpu_atombios_encodew_get_wcd_info(amdgpu_encodew);
		} ewse if (amdgpu_encodew->devices & (ATOM_DEVICE_CWT_SUPPOWT)) {
			dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
					 DWM_MODE_ENCODEW_DAC, NUWW);
			amdgpu_encodew->enc_pwiv = amdgpu_atombios_encodew_get_dig_info(amdgpu_encodew);
		} ewse {
			dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
					 DWM_MODE_ENCODEW_TMDS, NUWW);
			amdgpu_encodew->enc_pwiv = amdgpu_atombios_encodew_get_dig_info(amdgpu_encodew);
		}
		dwm_encodew_hewpew_add(encodew, &dce_v6_0_dig_hewpew_funcs);
		bweak;
	case ENCODEW_OBJECT_ID_SI170B:
	case ENCODEW_OBJECT_ID_CH7303:
	case ENCODEW_OBJECT_ID_EXTEWNAW_SDVOA:
	case ENCODEW_OBJECT_ID_EXTEWNAW_SDVOB:
	case ENCODEW_OBJECT_ID_TITFP513:
	case ENCODEW_OBJECT_ID_VT1623:
	case ENCODEW_OBJECT_ID_HDMI_SI1930:
	case ENCODEW_OBJECT_ID_TWAVIS:
	case ENCODEW_OBJECT_ID_NUTMEG:
		/* these awe handwed by the pwimawy encodews */
		amdgpu_encodew->is_ext_encodew = twue;
		if (amdgpu_encodew->devices & (ATOM_DEVICE_WCD_SUPPOWT))
			dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
					 DWM_MODE_ENCODEW_WVDS, NUWW);
		ewse if (amdgpu_encodew->devices & (ATOM_DEVICE_CWT_SUPPOWT))
			dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
					 DWM_MODE_ENCODEW_DAC, NUWW);
		ewse
			dwm_encodew_init(dev, encodew, &dce_v6_0_encodew_funcs,
					 DWM_MODE_ENCODEW_TMDS, NUWW);
		dwm_encodew_hewpew_add(encodew, &dce_v6_0_ext_hewpew_funcs);
		bweak;
	}
}

static const stwuct amdgpu_dispway_funcs dce_v6_0_dispway_funcs = {
	.bandwidth_update = &dce_v6_0_bandwidth_update,
	.vbwank_get_countew = &dce_v6_0_vbwank_get_countew,
	.backwight_set_wevew = &amdgpu_atombios_encodew_set_backwight_wevew,
	.backwight_get_wevew = &amdgpu_atombios_encodew_get_backwight_wevew,
	.hpd_sense = &dce_v6_0_hpd_sense,
	.hpd_set_powawity = &dce_v6_0_hpd_set_powawity,
	.hpd_get_gpio_weg = &dce_v6_0_hpd_get_gpio_weg,
	.page_fwip = &dce_v6_0_page_fwip,
	.page_fwip_get_scanoutpos = &dce_v6_0_cwtc_get_scanoutpos,
	.add_encodew = &dce_v6_0_encodew_add,
	.add_connectow = &amdgpu_connectow_add,
};

static void dce_v6_0_set_dispway_funcs(stwuct amdgpu_device *adev)
{
	adev->mode_info.funcs = &dce_v6_0_dispway_funcs;
}

static const stwuct amdgpu_iwq_swc_funcs dce_v6_0_cwtc_iwq_funcs = {
	.set = dce_v6_0_set_cwtc_intewwupt_state,
	.pwocess = dce_v6_0_cwtc_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs dce_v6_0_pagefwip_iwq_funcs = {
	.set = dce_v6_0_set_pagefwip_intewwupt_state,
	.pwocess = dce_v6_0_pagefwip_iwq,
};

static const stwuct amdgpu_iwq_swc_funcs dce_v6_0_hpd_iwq_funcs = {
	.set = dce_v6_0_set_hpd_intewwupt_state,
	.pwocess = dce_v6_0_hpd_iwq,
};

static void dce_v6_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	if (adev->mode_info.num_cwtc > 0)
		adev->cwtc_iwq.num_types = AMDGPU_CWTC_IWQ_VWINE1 + adev->mode_info.num_cwtc;
	ewse
		adev->cwtc_iwq.num_types = 0;
	adev->cwtc_iwq.funcs = &dce_v6_0_cwtc_iwq_funcs;

	adev->pagefwip_iwq.num_types = adev->mode_info.num_cwtc;
	adev->pagefwip_iwq.funcs = &dce_v6_0_pagefwip_iwq_funcs;

	adev->hpd_iwq.num_types = adev->mode_info.num_hpd;
	adev->hpd_iwq.funcs = &dce_v6_0_hpd_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion dce_v6_0_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_DCE,
	.majow = 6,
	.minow = 0,
	.wev = 0,
	.funcs = &dce_v6_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion dce_v6_4_ip_bwock =
{
	.type = AMD_IP_BWOCK_TYPE_DCE,
	.majow = 6,
	.minow = 4,
	.wev = 0,
	.funcs = &dce_v6_0_ip_funcs,
};
