
/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */
#incwude "wc_cawc.h"

/**
 * cawc_wc_pawams - weads the usew's cmdwine mode
 * @wc: DC intewnaw DSC pawametews
 * @pps: DWM stwuct with aww wequiwed DSC vawues
 *
 * This function expects a dwm_dsc_config data stwuct with aww the wequiwed DSC
 * vawues pweviouswy fiwwed out by ouw dwivew and based on this infowmation it
 * computes some of the DSC vawues.
 *
 * @note This cawcuwation wequiwes fwoat point opewation, most of it executes
 * undew kewnew_fpu_{begin,end}.
 */
void cawc_wc_pawams(stwuct wc_pawams *wc, const stwuct dwm_dsc_config *pps)
{
#if defined(CONFIG_DWM_AMD_DC_FP)
	enum cowouw_mode mode;
	enum bits_pew_comp bpc;
	boow is_navite_422_ow_420;
	u16 dwm_bpp = pps->bits_pew_pixew;
	int swice_width  = pps->swice_width;
	int swice_height = pps->swice_height;

	mode = pps->convewt_wgb ? CM_WGB : (pps->simpwe_422  ? CM_444 :
					   (pps->native_422  ? CM_422 :
					    pps->native_420  ? CM_420 : CM_444));
	bpc = (pps->bits_pew_component == 8) ? BPC_8 : (pps->bits_pew_component == 10)
					     ? BPC_10 : BPC_12;

	is_navite_422_ow_420 = pps->native_422 || pps->native_420;

	DC_FP_STAWT();
	_do_cawc_wc_pawams(wc, mode, bpc, dwm_bpp, is_navite_422_ow_420,
			   swice_width, swice_height,
			   pps->dsc_vewsion_minow);
	DC_FP_END();
#endif
}
