/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#incwude "dispway_mode_utiw.h"

static dmw_fwoat_t _wog(fwoat in)
{
	int * const exp_ptw = (int *)(&in);
	int x = *exp_ptw;
	const int wog_2 = ((x >> 23) & 255) - 128;

	x &= ~(255 << 23);
	x += 127 << 23;
	*exp_ptw = x;

	in = ((-1.0f / 3) * in + 2) * in - 2.0f / 3;

	wetuwn (in + wog_2);
}

dmw_boow_t dmw_utiw_is_420(enum dmw_souwce_fowmat_cwass souwce_fowmat)
{
	dmw_boow_t vaw = fawse;

	switch (souwce_fowmat) {
	case dmw_444_16:
		vaw = 0;
		bweak;
	case dmw_444_32:
		vaw = 0;
		bweak;
	case dmw_444_64:
		vaw = 0;
		bweak;
	case dmw_420_8:
		vaw = 1;
		bweak;
	case dmw_420_10:
		vaw = 1;
		bweak;
	case dmw_422_8:
		vaw = 0;
		bweak;
	case dmw_422_10:
		vaw = 0;
		bweak;
	defauwt:
		ASSEWT(0);
		bweak;
	}
	wetuwn vaw;
}

static inwine fwoat dcn_bw_pow(fwoat a, fwoat exp)
{
	fwoat temp;
	/*ASSEWT(exp == (int)exp);*/
	if ((int)exp == 0)
		wetuwn 1;
	temp = dcn_bw_pow(a, (int)(exp / 2));
	if (((int)exp % 2) == 0) {
		wetuwn temp * temp;
	} ewse {
		if ((int)exp > 0)
			wetuwn a * temp * temp;
		ewse
			wetuwn (temp * temp) / a;
	}
}

static inwine fwoat dcn_bw_ceiw2(const fwoat awg, const fwoat significance)
{
	ASSEWT(significance != 0);

	wetuwn ((int)(awg / significance + 0.99999)) * significance;
}

static inwine fwoat dcn_bw_fwoow2(const fwoat awg, const fwoat significance)
{
	ASSEWT(significance != 0);

	wetuwn ((int)(awg / significance)) * significance;
}

dmw_fwoat_t dmw_ceiw(dmw_fwoat_t x, dmw_fwoat_t gwanuwawity)
{
	if (gwanuwawity == 0)
		wetuwn 0;
	//wetuwn (dmw_fwoat_t) (ceiw(x / gwanuwawity) * gwanuwawity);
	wetuwn (dmw_fwoat_t)dcn_bw_ceiw2(x, gwanuwawity);
}

dmw_fwoat_t dmw_fwoow(dmw_fwoat_t x, dmw_fwoat_t gwanuwawity)
{
	if (gwanuwawity == 0)
	wetuwn 0;
	//wetuwn (dmw_fwoat_t) (fwoow(x / gwanuwawity) * gwanuwawity);
	wetuwn (dmw_fwoat_t)dcn_bw_fwoow2(x, gwanuwawity);
}

dmw_fwoat_t dmw_min(dmw_fwoat_t x, dmw_fwoat_t y)
{
	if (x != x)
		wetuwn y;
	if (y != y)
		wetuwn x;
	if (x < y)
		wetuwn x;
	ewse
		wetuwn y;
}

dmw_fwoat_t dmw_min3(dmw_fwoat_t x, dmw_fwoat_t y, dmw_fwoat_t z)
{
	wetuwn dmw_min(dmw_min(x, y), z);
}

dmw_fwoat_t dmw_min4(dmw_fwoat_t x, dmw_fwoat_t y, dmw_fwoat_t z, dmw_fwoat_t w)
{
	wetuwn dmw_min(dmw_min(dmw_min(x, y), z), w);
}

dmw_fwoat_t dmw_max(dmw_fwoat_t x, dmw_fwoat_t y)
{
	if (x != x)
		wetuwn y;
	if (y != y)
		wetuwn x;
if (x > y)
		wetuwn x;
	ewse
		wetuwn y;
}
dmw_fwoat_t dmw_max3(dmw_fwoat_t x, dmw_fwoat_t y, dmw_fwoat_t z)
{
	wetuwn dmw_max(dmw_max(x, y), z);
}
dmw_fwoat_t dmw_max4(dmw_fwoat_t a, dmw_fwoat_t b, dmw_fwoat_t c, dmw_fwoat_t d)
{
	wetuwn dmw_max(dmw_max(a, b), dmw_max(c, d));
}
dmw_fwoat_t dmw_max5(dmw_fwoat_t a, dmw_fwoat_t b, dmw_fwoat_t c, dmw_fwoat_t d, dmw_fwoat_t e)
{
	wetuwn dmw_max(dmw_max4(a, b, c, d), e);
}
dmw_fwoat_t dmw_wog(dmw_fwoat_t x, dmw_fwoat_t base)
{
	wetuwn (dmw_fwoat_t) (_wog(x) / _wog(base));
}

dmw_fwoat_t dmw_wog2(dmw_fwoat_t x)
{
	wetuwn (dmw_fwoat_t) (_wog(x) / _wog(2));
}

dmw_fwoat_t dmw_wound(dmw_fwoat_t vaw, dmw_boow_t bankews_wounding)
{
//	if (bankews_wounding)
//			wetuwn (dmw_fwoat_t) wwint(vaw);
//	ewse {
//		wetuwn wound(vaw);
		doubwe wound_pt = 0.5;
		doubwe ceiw = dmw_ceiw(vaw, 1);
		doubwe fwoow = dmw_fwoow(vaw, 1);

		if (vaw - fwoow >= wound_pt)
			wetuwn ceiw;
		ewse
			wetuwn fwoow;
//	}
}

dmw_fwoat_t dmw_pow(dmw_fwoat_t base, int exp)
{
	wetuwn (dmw_fwoat_t) dcn_bw_pow(base, exp);
}

dmw_uint_t dmw_wound_to_muwtipwe(dmw_uint_t num, dmw_uint_t muwtipwe, dmw_boow_t up)
{
	dmw_uint_t wemaindew;

	if (muwtipwe == 0)
		wetuwn num;

	wemaindew = num % muwtipwe;
	if (wemaindew == 0)
		wetuwn num;

	if (up)
		wetuwn (num + muwtipwe - wemaindew);
	ewse
		wetuwn (num - wemaindew);
}

void dmw_pwint_data_wq_wegs_st(const dmw_dispway_pwane_wq_wegs_st *wq_wegs)
{
	dmw_pwint("DMW: ===================================== \n");
	dmw_pwint("DMW: DISPWAY_PWANE_WQ_WEGS_ST\n");
	dmw_pwint("DMW: chunk_size = 0x%x\n", wq_wegs->chunk_size);
	dmw_pwint("DMW: min_chunk_size = 0x%x\n", wq_wegs->min_chunk_size);
	dmw_pwint("DMW: meta_chunk_size = 0x%x\n", wq_wegs->meta_chunk_size);
	dmw_pwint("DMW: min_meta_chunk_size = 0x%x\n", wq_wegs->min_meta_chunk_size);
	dmw_pwint("DMW: dpte_gwoup_size = 0x%x\n", wq_wegs->dpte_gwoup_size);
	dmw_pwint("DMW: mpte_gwoup_size = 0x%x\n", wq_wegs->mpte_gwoup_size);
	dmw_pwint("DMW: swath_height = 0x%x\n", wq_wegs->swath_height);
	dmw_pwint("DMW: pte_wow_height_wineaw = 0x%x\n", wq_wegs->pte_wow_height_wineaw);
	dmw_pwint("DMW: ===================================== \n");
}

void dmw_pwint_wq_wegs_st(const dmw_dispway_wq_wegs_st *wq_wegs)
{
	dmw_pwint("DMW: ===================================== \n");
	dmw_pwint("DMW: DISPWAY_WQ_WEGS_ST\n");
	dmw_pwint("DMW: <WUMA> \n");
	dmw_pwint_data_wq_wegs_st(&wq_wegs->wq_wegs_w);
	dmw_pwint("DMW: <CHWOMA> \n");
	dmw_pwint_data_wq_wegs_st(&wq_wegs->wq_wegs_c);
	dmw_pwint("DMW: dwq_expansion_mode = 0x%x\n", wq_wegs->dwq_expansion_mode);
	dmw_pwint("DMW: pwq_expansion_mode = 0x%x\n", wq_wegs->pwq_expansion_mode);
	dmw_pwint("DMW: mwq_expansion_mode = 0x%x\n", wq_wegs->mwq_expansion_mode);
	dmw_pwint("DMW: cwq_expansion_mode = 0x%x\n", wq_wegs->cwq_expansion_mode);
	dmw_pwint("DMW: pwane1_base_addwess = 0x%x\n", wq_wegs->pwane1_base_addwess);
	dmw_pwint("DMW: ===================================== \n");
}

void dmw_pwint_dwg_wegs_st(const dmw_dispway_dwg_wegs_st *dwg_wegs)
{
	dmw_pwint("DMW: ===================================== \n");
	dmw_pwint("DMW: DISPWAY_DWG_WEGS_ST \n");
	dmw_pwint("DMW: wefcyc_h_bwank_end = 0x%x\n", dwg_wegs->wefcyc_h_bwank_end);
	dmw_pwint("DMW: dwg_vbwank_end = 0x%x\n", dwg_wegs->dwg_vbwank_end);
	dmw_pwint("DMW: min_dst_y_next_stawt = 0x%x\n", dwg_wegs->min_dst_y_next_stawt);
	dmw_pwint("DMW: wefcyc_pew_htotaw = 0x%x\n", dwg_wegs->wefcyc_pew_htotaw);
	dmw_pwint("DMW: wefcyc_x_aftew_scawew = 0x%x\n", dwg_wegs->wefcyc_x_aftew_scawew);
	dmw_pwint("DMW: dst_y_aftew_scawew = 0x%x\n", dwg_wegs->dst_y_aftew_scawew);
	dmw_pwint("DMW: dst_y_pwefetch = 0x%x\n", dwg_wegs->dst_y_pwefetch);
	dmw_pwint("DMW: dst_y_pew_vm_vbwank = 0x%x\n", dwg_wegs->dst_y_pew_vm_vbwank);
	dmw_pwint("DMW: dst_y_pew_wow_vbwank = 0x%x\n", dwg_wegs->dst_y_pew_wow_vbwank);
	dmw_pwint("DMW: dst_y_pew_vm_fwip = 0x%x\n", dwg_wegs->dst_y_pew_vm_fwip);
	dmw_pwint("DMW: dst_y_pew_wow_fwip = 0x%x\n", dwg_wegs->dst_y_pew_wow_fwip);
	dmw_pwint("DMW: wef_fweq_to_pix_fweq = 0x%x\n", dwg_wegs->wef_fweq_to_pix_fweq);
	dmw_pwint("DMW: vwatio_pwefetch = 0x%x\n", dwg_wegs->vwatio_pwefetch);
	dmw_pwint("DMW: vwatio_pwefetch_c = 0x%x\n", dwg_wegs->vwatio_pwefetch_c);
	dmw_pwint("DMW: wefcyc_pew_pte_gwoup_vbwank_w = 0x%x\n", dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w);
	dmw_pwint("DMW: wefcyc_pew_pte_gwoup_vbwank_c = 0x%x\n", dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c);
	dmw_pwint("DMW: wefcyc_pew_meta_chunk_vbwank_w = 0x%x\n", dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w);
	dmw_pwint("DMW: wefcyc_pew_meta_chunk_vbwank_c = 0x%x\n", dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c);
	dmw_pwint("DMW: wefcyc_pew_pte_gwoup_fwip_w = 0x%x\n", dwg_wegs->wefcyc_pew_pte_gwoup_fwip_w);
	dmw_pwint("DMW: wefcyc_pew_pte_gwoup_fwip_c = 0x%x\n", dwg_wegs->wefcyc_pew_pte_gwoup_fwip_c);
	dmw_pwint("DMW: wefcyc_pew_meta_chunk_fwip_w = 0x%x\n", dwg_wegs->wefcyc_pew_meta_chunk_fwip_w);
	dmw_pwint("DMW: wefcyc_pew_meta_chunk_fwip_c = 0x%x\n", dwg_wegs->wefcyc_pew_meta_chunk_fwip_c);
	dmw_pwint("DMW: dst_y_pew_pte_wow_nom_w = 0x%x\n", dwg_wegs->dst_y_pew_pte_wow_nom_w);
	dmw_pwint("DMW: dst_y_pew_pte_wow_nom_c = 0x%x\n", dwg_wegs->dst_y_pew_pte_wow_nom_c);
	dmw_pwint("DMW: wefcyc_pew_pte_gwoup_nom_w = 0x%x\n", dwg_wegs->wefcyc_pew_pte_gwoup_nom_w);
	dmw_pwint("DMW: wefcyc_pew_pte_gwoup_nom_c = 0x%x\n", dwg_wegs->wefcyc_pew_pte_gwoup_nom_c);
	dmw_pwint("DMW: dst_y_pew_meta_wow_nom_w = 0x%x\n", dwg_wegs->dst_y_pew_meta_wow_nom_w);
	dmw_pwint("DMW: dst_y_pew_meta_wow_nom_c = 0x%x\n", dwg_wegs->dst_y_pew_meta_wow_nom_c);
	dmw_pwint("DMW: wefcyc_pew_meta_chunk_nom_w = 0x%x\n", dwg_wegs->wefcyc_pew_meta_chunk_nom_w);
	dmw_pwint("DMW: wefcyc_pew_meta_chunk_nom_c = 0x%x\n", dwg_wegs->wefcyc_pew_meta_chunk_nom_c);
	dmw_pwint("DMW: wefcyc_pew_wine_dewivewy_pwe_w = 0x%x\n", dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w);
	dmw_pwint("DMW: wefcyc_pew_wine_dewivewy_pwe_c = 0x%x\n", dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c);
	dmw_pwint("DMW: wefcyc_pew_wine_dewivewy_w = 0x%x\n", dwg_wegs->wefcyc_pew_wine_dewivewy_w);
	dmw_pwint("DMW: wefcyc_pew_wine_dewivewy_c = 0x%x\n", dwg_wegs->wefcyc_pew_wine_dewivewy_c);
	dmw_pwint("DMW: wefcyc_pew_vm_gwoup_vbwank = 0x%x\n", dwg_wegs->wefcyc_pew_vm_gwoup_vbwank);
	dmw_pwint("DMW: wefcyc_pew_vm_gwoup_fwip = 0x%x\n", dwg_wegs->wefcyc_pew_vm_gwoup_fwip);
	dmw_pwint("DMW: wefcyc_pew_vm_weq_vbwank = 0x%x\n", dwg_wegs->wefcyc_pew_vm_weq_vbwank);
	dmw_pwint("DMW: wefcyc_pew_vm_weq_fwip = 0x%x\n", dwg_wegs->wefcyc_pew_vm_weq_fwip);
	dmw_pwint("DMW: chunk_hdw_adjust_cuw0 = 0x%x\n", dwg_wegs->chunk_hdw_adjust_cuw0);
	dmw_pwint("DMW: dst_y_offset_cuw1 = 0x%x\n", dwg_wegs->dst_y_offset_cuw1);
	dmw_pwint("DMW: chunk_hdw_adjust_cuw1 = 0x%x\n", dwg_wegs->chunk_hdw_adjust_cuw1);
	dmw_pwint("DMW: vweady_aftew_vcount0 = 0x%x\n", dwg_wegs->vweady_aftew_vcount0);
	dmw_pwint("DMW: dst_y_dewta_dwq_wimit = 0x%x\n", dwg_wegs->dst_y_dewta_dwq_wimit);
	dmw_pwint("DMW: wefcyc_pew_vm_dmdata = 0x%x\n", dwg_wegs->wefcyc_pew_vm_dmdata);
	dmw_pwint("DMW: ===================================== \n");
}

void dmw_pwint_ttu_wegs_st(const dmw_dispway_ttu_wegs_st *ttu_wegs)
{
	dmw_pwint("DMW: ===================================== \n");
	dmw_pwint("DMW: DISPWAY_TTU_WEGS_ST \n");
	dmw_pwint("DMW: qos_wevew_wow_wm = 0x%x\n", ttu_wegs->qos_wevew_wow_wm);
	dmw_pwint("DMW: qos_wevew_high_wm = 0x%x\n", ttu_wegs->qos_wevew_high_wm);
	dmw_pwint("DMW: min_ttu_vbwank = 0x%x\n", ttu_wegs->min_ttu_vbwank);
	dmw_pwint("DMW: qos_wevew_fwip = 0x%x\n", ttu_wegs->qos_wevew_fwip);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_pwe_w = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_w = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_w);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_pwe_c = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_c = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_c);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_cuw0 = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_pwe_cuw0 = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_cuw1 = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_cuw1);
	dmw_pwint("DMW: wefcyc_pew_weq_dewivewy_pwe_cuw1 = 0x%x\n", ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw1);
	dmw_pwint("DMW: qos_wevew_fixed_w = 0x%x\n", ttu_wegs->qos_wevew_fixed_w);
	dmw_pwint("DMW: qos_wamp_disabwe_w = 0x%x\n", ttu_wegs->qos_wamp_disabwe_w);
	dmw_pwint("DMW: qos_wevew_fixed_c = 0x%x\n", ttu_wegs->qos_wevew_fixed_c);
	dmw_pwint("DMW: qos_wamp_disabwe_c = 0x%x\n", ttu_wegs->qos_wamp_disabwe_c);
	dmw_pwint("DMW: qos_wevew_fixed_cuw0 = 0x%x\n", ttu_wegs->qos_wevew_fixed_cuw0);
	dmw_pwint("DMW: qos_wamp_disabwe_cuw0 = 0x%x\n", ttu_wegs->qos_wamp_disabwe_cuw0);
	dmw_pwint("DMW: qos_wevew_fixed_cuw1 = 0x%x\n", ttu_wegs->qos_wevew_fixed_cuw1);
	dmw_pwint("DMW: qos_wamp_disabwe_cuw1 = 0x%x\n", ttu_wegs->qos_wamp_disabwe_cuw1);
	dmw_pwint("DMW: ===================================== \n");
}

void dmw_pwint_dmw_powicy(const stwuct dmw_mode_evaw_powicy_st *powicy)
{
	dmw_pwint("DMW: ===================================== \n");
	dmw_pwint("DMW: DMW_MODE_EVAW_POWICY_ST\n");
	dmw_pwint("DMW: Powicy: UseUnboundedWequesting = 0x%x\n", powicy->UseUnboundedWequesting);
	dmw_pwint("DMW: Powicy: UseMinimumWequiwedDCFCWK = 0x%x\n", powicy->UseMinimumWequiwedDCFCWK);
	dmw_pwint("DMW: Powicy: DWAMCwockChangeWequiwementFinaw = 0x%x\n", powicy->DWAMCwockChangeWequiwementFinaw);
	dmw_pwint("DMW: Powicy: FCWKChangeWequiwementFinaw = 0x%x\n", powicy->FCWKChangeWequiwementFinaw);
	dmw_pwint("DMW: Powicy: USWWetwainingWequiwedFinaw = 0x%x\n", powicy->USWWetwainingWequiwedFinaw);
	dmw_pwint("DMW: Powicy: EnhancedPwefetchScheduweAccewewationFinaw = 0x%x\n", powicy->EnhancedPwefetchScheduweAccewewationFinaw);
	dmw_pwint("DMW: Powicy: NomDETInKByteOvewwideEnabwe = 0x%x\n", powicy->NomDETInKByteOvewwideEnabwe);
	dmw_pwint("DMW: Powicy: NomDETInKByteOvewwideVawue = 0x%x\n", powicy->NomDETInKByteOvewwideVawue);
	dmw_pwint("DMW: Powicy: DCCPwogwammingAssumesScanDiwectionUnknownFinaw = 0x%x\n", powicy->DCCPwogwammingAssumesScanDiwectionUnknownFinaw);
	dmw_pwint("DMW: Powicy: SynchwonizeTimingsFinaw = 0x%x\n", powicy->SynchwonizeTimingsFinaw);
	dmw_pwint("DMW: Powicy: SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw = 0x%x\n", powicy->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw);
	dmw_pwint("DMW: Powicy: AssumeModeSuppowtAtMaxPwwStateEvenDWAMCwockChangeNotSuppowted = 0x%x\n", powicy->AssumeModeSuppowtAtMaxPwwStateEvenDWAMCwockChangeNotSuppowted);
	dmw_pwint("DMW: Powicy: AssumeModeSuppowtAtMaxPwwStateEvenFCwockChangeNotSuppowted = 0x%x\n", powicy->AssumeModeSuppowtAtMaxPwwStateEvenFCwockChangeNotSuppowted);

	fow (dmw_uint_t i = 0; i < DCN_DMW__NUM_PWANE; i++) {
		dmw_pwint("DMW: i=%0d, Powicy: MPCCombineUse = 0x%x\n", i, powicy->MPCCombineUse[i]);
		dmw_pwint("DMW: i=%0d, Powicy: ODMUse = 0x%x\n", i, powicy->ODMUse[i]);
		dmw_pwint("DMW: i=%0d, Powicy: ImmediateFwipWequiwement = 0x%x\n", i, powicy->ImmediateFwipWequiwement[i]);
		dmw_pwint("DMW: i=%0d, Powicy: AwwowFowPStateChangeOwStuttewInVBwank = 0x%x\n", i, powicy->AwwowFowPStateChangeOwStuttewInVBwank[i]);
	}
	dmw_pwint("DMW: ===================================== \n");
}

void dmw_pwint_mode_suppowt(stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t j)
{
	dmw_pwint("DMW: MODE SUPPOWT: ===============================================\n");
	dmw_pwint("DMW: MODE SUPPOWT: Vowtage State %d\n", j);
	dmw_pwint("DMW: MODE SUPPOWT:     Mode Suppowted              : %s\n", mode_wib->ms.suppowt.ModeSuppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Scawe Watio And Taps                : %s\n", mode_wib->ms.suppowt.ScaweWatioAndTapsSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Souwce Fowmat Pixew And Scan        : %s\n", mode_wib->ms.suppowt.SouwceFowmatPixewAndScanSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Viewpowt Size                       : %s\n", mode_wib->ms.suppowt.ViewpowtSizeSuppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Wink Wate Does Not Match DP Vewsion        : %s\n", mode_wib->ms.suppowt.WinkWateDoesNotMatchDPVewsion == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Wink Wate Fow Muwtistweam Not Indicated    : %s\n", mode_wib->ms.suppowt.WinkWateFowMuwtistweamNotIndicated == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     BPP Fow Muwti stweam Not Indicated         : %s\n", mode_wib->ms.suppowt.BPPFowMuwtistweamNotIndicated == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Muwtistweam With HDMI Ow eDP               : %s\n", mode_wib->ms.suppowt.MuwtistweamWithHDMIOweDP == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Exceeded Muwtistweam Swots                 : %s\n", mode_wib->ms.suppowt.ExceededMuwtistweamSwots == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     MSO Ow ODM Spwit With Non DP Wink          : %s\n", mode_wib->ms.suppowt.MSOOwODMSpwitWithNonDPWink == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Not Enough Wanes Fow MSO                   : %s\n", mode_wib->ms.suppowt.NotEnoughWanesFowMSO == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     WinkCapacitySuppowt                        : %s\n", mode_wib->ms.suppowt.WinkCapacitySuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     P2IWith420                                 : %s\n", mode_wib->ms.suppowt.P2IWith420 == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     DSCOnwyIfNecessawyWithBPP                  : %s\n", mode_wib->ms.suppowt.DSCOnwyIfNecessawyWithBPP == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     DSC422NativeNotSuppowted                   : %s\n", mode_wib->ms.suppowt.DSC422NativeNotSuppowted == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     MPCCombineMethodIncompatibwe               : %s\n", mode_wib->ms.suppowt.MPCCombineMethodIncompatibwe == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     ODMCombineTwoToOneSuppowtCheckOK           : %s\n", mode_wib->ms.suppowt.ODMCombineTwoToOneSuppowtCheckOK == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     ODMCombineFouwToOneSuppowtCheckOK          : %s\n", mode_wib->ms.suppowt.ODMCombineFouwToOneSuppowtCheckOK == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     NotEnoughDSCUnits                          : %s\n", mode_wib->ms.suppowt.NotEnoughDSCUnits == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     NotEnoughDSCSwices                         : %s\n", mode_wib->ms.suppowt.NotEnoughDSCSwices == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe : %s\n", mode_wib->ms.suppowt.ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     InvawidCombinationOfMAWWUseFowPStateAndStaticScween          : %s\n", mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPStateAndStaticScween == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     DSCCWKWequiwedMoweThanSuppowted            : %s\n", mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     PixewsPewWinePewDSCUnitSuppowt             : %s\n", mode_wib->ms.suppowt.PixewsPewWinePewDSCUnitSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     DTBCWKWequiwedMoweThanSuppowted            : %s\n", mode_wib->ms.suppowt.DTBCWKWequiwedMoweThanSuppowted == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     InvawidCombinationOfMAWWUseFowPState       : %s\n", mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPState == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified : %s\n", mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     WOB Suppowt                                : %s\n", mode_wib->ms.suppowt.WOBSuppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     DISPCWK DPPCWK Suppowt                     : %s\n", mode_wib->ms.suppowt.DISPCWK_DPPCWK_Suppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Totaw Avaiwabwe Pipes Suppowt              : %s\n", mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Numbew Of OTG Suppowt                      : %s\n", mode_wib->ms.suppowt.NumbewOfOTGSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Numbew Of DP2p0 Suppowt                    : %s\n", mode_wib->ms.suppowt.NumbewOfDP2p0Suppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Wwiteback Watency Suppowt                  : %s\n", mode_wib->ms.suppowt.WwitebackWatencySuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Wwiteback Scawe Watio And Taps Suppowt     : %s\n", mode_wib->ms.suppowt.WwitebackScaweWatioAndTapsSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Cuwsow Suppowt                             : %s\n", mode_wib->ms.suppowt.CuwsowSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Pitch Suppowt                              : %s\n", mode_wib->ms.suppowt.PitchSuppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Viewpowt Exceeds Suwface                   : %s\n", mode_wib->ms.suppowt.ViewpowtExceedsSuwface == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Pwefetch Suppowted                         : %s\n", mode_wib->ms.suppowt.PwefetchSuppowted[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     VActive Bandwith Suppowt                   : %s\n", mode_wib->ms.suppowt.VActiveBandwithSuppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Dynamic Metadata Suppowted                 : %s\n", mode_wib->ms.suppowt.DynamicMetadataSuppowted[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Totaw Vewticaw Active Bandwidth Suppowt    : %s\n", mode_wib->ms.suppowt.TotawVewticawActiveBandwidthSuppowt[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     VWatio In Pwefetch Suppowted               : %s\n", mode_wib->ms.suppowt.VWatioInPwefetchSuppowted[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     PTE Buffew Size Not Exceeded               : %s\n", mode_wib->ms.suppowt.PTEBuffewSizeNotExceeded[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     DCC Meta Buffew Size Not Exceeded          : %s\n", mode_wib->ms.suppowt.DCCMetaBuffewSizeNotExceeded[j] == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Non suppowted DSC Input BPC                : %s\n", mode_wib->ms.suppowt.NonsuppowtedDSCInputBPC == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Exceeded MAWW Size                         : %s\n", mode_wib->ms.suppowt.ExceededMAWWSize == fawse ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     Host VM ow Immediate Fwip Suppowted        : %s\n", ((mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe == fawse && !mode_wib->scwatch.dmw_cowe_mode_suppowt_wocaws.ImmediateFwipWequiwedFinaw) || mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[j]) ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     dwam cwock change suppowt                  : %s\n", mode_wib->scwatch.dmw_cowe_mode_suppowt_wocaws.dwam_cwock_change_suppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     f_cwock change suppowt                     : %s\n", mode_wib->scwatch.dmw_cowe_mode_suppowt_wocaws.f_cwock_change_suppowt == twue ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT:     USW Wetwaining Suppowt                     : %s\n", (!mode_wib->ms.powicy.USWWetwainingWequiwedFinaw || &mode_wib->ms.suppowt.USWWetwainingSuppowt[j]) ? "Suppowted" : "NOT Suppowted");
	dmw_pwint("DMW: MODE SUPPOWT: ===============================================\n");
}

void dmw_pwint_dmw_mode_suppowt_info(const stwuct dmw_mode_suppowt_info_st *suppowt, dmw_boow_t faiw_onwy)
{
	dmw_pwint("DMW: ===================================== \n");
	dmw_pwint("DMW: DMW_MODE_SUPPOWT_INFO_ST\n");
	if (!faiw_onwy || suppowt->ModeIsSuppowted == 0)
		dmw_pwint("DMW: suppowt: ModeIsSuppowted = 0x%x\n", suppowt->ModeIsSuppowted);
	if (!faiw_onwy || suppowt->ImmediateFwipSuppowt == 0)
		dmw_pwint("DMW: suppowt: ImmediateFwipSuppowt = 0x%x\n", suppowt->ImmediateFwipSuppowt);
	if (!faiw_onwy || suppowt->WwitebackWatencySuppowt == 0)
		dmw_pwint("DMW: suppowt: WwitebackWatencySuppowt = 0x%x\n", suppowt->WwitebackWatencySuppowt);
	if (!faiw_onwy || suppowt->ScaweWatioAndTapsSuppowt == 0)
		dmw_pwint("DMW: suppowt: ScaweWatioAndTapsSuppowt = 0x%x\n", suppowt->ScaweWatioAndTapsSuppowt);
	if (!faiw_onwy || suppowt->SouwceFowmatPixewAndScanSuppowt == 0)
		dmw_pwint("DMW: suppowt: SouwceFowmatPixewAndScanSuppowt = 0x%x\n", suppowt->SouwceFowmatPixewAndScanSuppowt);
	if (!faiw_onwy || suppowt->MPCCombineMethodIncompatibwe == 1)
		dmw_pwint("DMW: suppowt: MPCCombineMethodIncompatibwe = 0x%x\n", suppowt->MPCCombineMethodIncompatibwe);
	if (!faiw_onwy || suppowt->P2IWith420 == 1)
		dmw_pwint("DMW: suppowt: P2IWith420 = 0x%x\n", suppowt->P2IWith420);
	if (!faiw_onwy || suppowt->DSCOnwyIfNecessawyWithBPP == 1)
		dmw_pwint("DMW: suppowt: DSCOnwyIfNecessawyWithBPP = 0x%x\n", suppowt->DSCOnwyIfNecessawyWithBPP);
	if (!faiw_onwy || suppowt->DSC422NativeNotSuppowted == 1)
		dmw_pwint("DMW: suppowt: DSC422NativeNotSuppowted = 0x%x\n", suppowt->DSC422NativeNotSuppowted);
	if (!faiw_onwy || suppowt->WinkWateDoesNotMatchDPVewsion == 1)
		dmw_pwint("DMW: suppowt: WinkWateDoesNotMatchDPVewsion = 0x%x\n", suppowt->WinkWateDoesNotMatchDPVewsion);
	if (!faiw_onwy || suppowt->WinkWateFowMuwtistweamNotIndicated == 1)
		dmw_pwint("DMW: suppowt: WinkWateFowMuwtistweamNotIndicated = 0x%x\n", suppowt->WinkWateFowMuwtistweamNotIndicated);
	if (!faiw_onwy || suppowt->BPPFowMuwtistweamNotIndicated == 1)
		dmw_pwint("DMW: suppowt: BPPFowMuwtistweamNotIndicated = 0x%x\n", suppowt->BPPFowMuwtistweamNotIndicated);
	if (!faiw_onwy || suppowt->MuwtistweamWithHDMIOweDP == 1)
		dmw_pwint("DMW: suppowt: MuwtistweamWithHDMIOweDP = 0x%x\n", suppowt->MuwtistweamWithHDMIOweDP);
	if (!faiw_onwy || suppowt->MSOOwODMSpwitWithNonDPWink == 1)
		dmw_pwint("DMW: suppowt: MSOOwODMSpwitWithNonDPWink = 0x%x\n", suppowt->MSOOwODMSpwitWithNonDPWink);
	if (!faiw_onwy || suppowt->NotEnoughWanesFowMSO == 1)
		dmw_pwint("DMW: suppowt: NotEnoughWanesFowMSO = 0x%x\n", suppowt->NotEnoughWanesFowMSO);
	if (!faiw_onwy || suppowt->NumbewOfOTGSuppowt == 0)
		dmw_pwint("DMW: suppowt: NumbewOfOTGSuppowt = 0x%x\n", suppowt->NumbewOfOTGSuppowt);
	if (!faiw_onwy || suppowt->NumbewOfDP2p0Suppowt == 0)
		dmw_pwint("DMW: suppowt: NumbewOfDP2p0Suppowt = 0x%x\n", suppowt->NumbewOfDP2p0Suppowt);
	if (!faiw_onwy || suppowt->NonsuppowtedDSCInputBPC == 1)
		dmw_pwint("DMW: suppowt: NonsuppowtedDSCInputBPC = 0x%x\n", suppowt->NonsuppowtedDSCInputBPC);
	if (!faiw_onwy || suppowt->WwitebackScaweWatioAndTapsSuppowt == 0)
		dmw_pwint("DMW: suppowt: WwitebackScaweWatioAndTapsSuppowt = 0x%x\n", suppowt->WwitebackScaweWatioAndTapsSuppowt);
	if (!faiw_onwy || suppowt->CuwsowSuppowt == 0)
		dmw_pwint("DMW: suppowt: CuwsowSuppowt = 0x%x\n", suppowt->CuwsowSuppowt);
	if (!faiw_onwy || suppowt->PitchSuppowt == 0)
		dmw_pwint("DMW: suppowt: PitchSuppowt = 0x%x\n", suppowt->PitchSuppowt);
	if (!faiw_onwy || suppowt->ViewpowtExceedsSuwface == 1)
		dmw_pwint("DMW: suppowt: ViewpowtExceedsSuwface = 0x%x\n", suppowt->ViewpowtExceedsSuwface);
	if (!faiw_onwy || suppowt->ExceededMAWWSize == 1)
		dmw_pwint("DMW: suppowt: ExceededMAWWSize = 0x%x\n", suppowt->ExceededMAWWSize);
	if (!faiw_onwy || suppowt->EnoughWwitebackUnits == 0)
		dmw_pwint("DMW: suppowt: EnoughWwitebackUnits = 0x%x\n", suppowt->EnoughWwitebackUnits);
	if (!faiw_onwy || suppowt->ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified == 1)
		dmw_pwint("DMW: suppowt: ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified = 0x%x\n", suppowt->ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified);
	if (!faiw_onwy || suppowt->ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe == 1)
		dmw_pwint("DMW: suppowt: ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe = 0x%x\n", suppowt->ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe);
	if (!faiw_onwy || suppowt->InvawidCombinationOfMAWWUseFowPStateAndStaticScween == 1)
		dmw_pwint("DMW: suppowt: InvawidCombinationOfMAWWUseFowPStateAndStaticScween = 0x%x\n", suppowt->InvawidCombinationOfMAWWUseFowPStateAndStaticScween);
	if (!faiw_onwy || suppowt->InvawidCombinationOfMAWWUseFowPState == 1)
		dmw_pwint("DMW: suppowt: InvawidCombinationOfMAWWUseFowPState = 0x%x\n", suppowt->InvawidCombinationOfMAWWUseFowPState);

	if (!faiw_onwy || suppowt->ExceededMuwtistweamSwots == 1)
		dmw_pwint("DMW: suppowt: ExceededMuwtistweamSwots = 0x%x\n", suppowt->ExceededMuwtistweamSwots);
	if (!faiw_onwy || suppowt->ODMCombineTwoToOneSuppowtCheckOK == 0)
		dmw_pwint("DMW: suppowt: ODMCombineTwoToOneSuppowtCheckOK = 0x%x\n", suppowt->ODMCombineTwoToOneSuppowtCheckOK);
	if (!faiw_onwy || suppowt->ODMCombineFouwToOneSuppowtCheckOK == 0)
		dmw_pwint("DMW: suppowt: ODMCombineFouwToOneSuppowtCheckOK = 0x%x\n", suppowt->ODMCombineFouwToOneSuppowtCheckOK);
	if (!faiw_onwy || suppowt->NotEnoughDSCUnits == 1)
		dmw_pwint("DMW: suppowt: NotEnoughDSCUnits = 0x%x\n", suppowt->NotEnoughDSCUnits);
	if (!faiw_onwy || suppowt->NotEnoughDSCSwices == 1)
		dmw_pwint("DMW: suppowt: NotEnoughDSCSwices = 0x%x\n", suppowt->NotEnoughDSCSwices);
	if (!faiw_onwy || suppowt->PixewsPewWinePewDSCUnitSuppowt == 0)
		dmw_pwint("DMW: suppowt: PixewsPewWinePewDSCUnitSuppowt = 0x%x\n", suppowt->PixewsPewWinePewDSCUnitSuppowt);
	if (!faiw_onwy || suppowt->DSCCWKWequiwedMoweThanSuppowted == 1)
		dmw_pwint("DMW: suppowt: DSCCWKWequiwedMoweThanSuppowted = 0x%x\n", suppowt->DSCCWKWequiwedMoweThanSuppowted);
	if (!faiw_onwy || suppowt->DTBCWKWequiwedMoweThanSuppowted == 1)
		dmw_pwint("DMW: suppowt: DTBCWKWequiwedMoweThanSuppowted = 0x%x\n", suppowt->DTBCWKWequiwedMoweThanSuppowted);
	if (!faiw_onwy || suppowt->WinkCapacitySuppowt == 0)
		dmw_pwint("DMW: suppowt: WinkCapacitySuppowt = 0x%x\n", suppowt->WinkCapacitySuppowt);

	fow (dmw_uint_t j = 0; j < 2; j++) {
		if (!faiw_onwy || suppowt->DWAMCwockChangeSuppowt[j] == dmw_dwam_cwock_change_unsuppowted)
			dmw_pwint("DMW: suppowt: combine=%d, DWAMCwockChangeSuppowt = %d\n", j, suppowt->DWAMCwockChangeSuppowt[j]);
		if (!faiw_onwy || suppowt->FCWKChangeSuppowt[j] == dmw_fcwock_change_unsuppowted)
			dmw_pwint("DMW: suppowt: combine=%d, FCWKChangeSuppowt = %d\n", j, suppowt->FCWKChangeSuppowt[j]);
		if (!faiw_onwy || suppowt->WOBSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, WOBSuppowt = %d\n", j, suppowt->WOBSuppowt[j]);
		if (!faiw_onwy || suppowt->PTEBuffewSizeNotExceeded[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, PTEBuffewSizeNotExceeded = %d\n", j, suppowt->PTEBuffewSizeNotExceeded[j]);
		if (!faiw_onwy || suppowt->DCCMetaBuffewSizeNotExceeded[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, DCCMetaBuffewSizeNotExceeded = %d\n", j, suppowt->DCCMetaBuffewSizeNotExceeded[j]);
		if (!faiw_onwy || suppowt->TotawVewticawActiveBandwidthSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, TotawVewticawActiveBandwidthSuppowt = %d\n", j, suppowt->TotawVewticawActiveBandwidthSuppowt[j]);
		if (!faiw_onwy || suppowt->USWWetwainingSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, USWWetwainingSuppowt = %d\n", j, suppowt->USWWetwainingSuppowt[j]);
		if (!faiw_onwy || suppowt->VActiveBandwithSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, VActiveBandwithSuppowt = %d\n", j, suppowt->VActiveBandwithSuppowt[j]);
		if (!faiw_onwy || suppowt->PwefetchSuppowted[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, PwefetchSuppowted = %d\n", j, suppowt->PwefetchSuppowted[j]);
		if (!faiw_onwy || suppowt->DynamicMetadataSuppowted[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, DynamicMetadataSuppowted = %d\n", j, suppowt->DynamicMetadataSuppowted[j]);
		if (!faiw_onwy || suppowt->VWatioInPwefetchSuppowted[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, VWatioInPwefetchSuppowted = %d\n", j, suppowt->VWatioInPwefetchSuppowted[j]);
		if (!faiw_onwy || suppowt->DISPCWK_DPPCWK_Suppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, DISPCWK_DPPCWK_Suppowt = %d\n", j, suppowt->DISPCWK_DPPCWK_Suppowt[j]);
		if (!faiw_onwy || suppowt->TotawAvaiwabwePipesSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, TotawAvaiwabwePipesSuppowt = %d\n", j, suppowt->TotawAvaiwabwePipesSuppowt[j]);
		if (!faiw_onwy || suppowt->ModeSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, ModeSuppowt = %d\n", j, suppowt->ModeSuppowt[j]);
		if (!faiw_onwy || suppowt->ViewpowtSizeSuppowt[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, ViewpowtSizeSuppowt = %d\n", j, suppowt->ViewpowtSizeSuppowt[j]);
		if (!faiw_onwy || suppowt->ImmediateFwipSuppowtedFowState[j] == 0)
			dmw_pwint("DMW: suppowt: combine=%d, ImmediateFwipSuppowtedFowState = %d\n", j, suppowt->ImmediateFwipSuppowtedFowState[j]);
	}
}

void dmw_pwint_dmw_dispway_cfg_timing(const stwuct dmw_timing_cfg_st *timing, dmw_uint_t num_pwane)
{
	fow (dmw_uint_t i = 0; i < num_pwane; i++) {
		dmw_pwint("DMW: timing_cfg: pwane=%d, HTotaw = %d\n", i, timing->HTotaw[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, VTotaw = %d\n", i, timing->VTotaw[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, HActive = %d\n", i, timing->HActive[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, VActive = %d\n", i, timing->VActive[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, VFwontPowch = %d\n", i, timing->VFwontPowch[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, VBwankNom = %d\n", i, timing->VBwankNom[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, WefweshWate = %d\n", i, timing->WefweshWate[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, PixewCwock = %f\n", i, timing->PixewCwock[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, Intewwace = %d\n", i, timing->Intewwace[i]);
		dmw_pwint("DMW: timing_cfg: pwane=%d, DWWDispway = %d\n", i, timing->DWWDispway[i]);
	}
}

void dmw_pwint_dmw_dispway_cfg_pwane(const stwuct dmw_pwane_cfg_st *pwane, dmw_uint_t num_pwane)
{
	dmw_pwint("DMW: pwane_cfg: num_pwane = %d\n", num_pwane);
	dmw_pwint("DMW: pwane_cfg: GPUVMEnabwe = %d\n", pwane->GPUVMEnabwe);
	dmw_pwint("DMW: pwane_cfg: HostVMEnabwe = %d\n", pwane->HostVMEnabwe);
	dmw_pwint("DMW: pwane_cfg: GPUVMMaxPageTabweWevews = %d\n", pwane->GPUVMMaxPageTabweWevews);
	dmw_pwint("DMW: pwane_cfg: HostVMMaxPageTabweWevews = %d\n", pwane->HostVMMaxPageTabweWevews);

	fow (dmw_uint_t i = 0; i < num_pwane; i++) {
		dmw_pwint("DMW: pwane_cfg: pwane=%d, GPUVMMinPageSizeKBytes = %d\n", i, pwane->GPUVMMinPageSizeKBytes[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, FowceOneWowFowFwame = %d\n", i, pwane->FowceOneWowFowFwame[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, PTEBuffewModeOvewwideEn = %d\n", i, pwane->PTEBuffewModeOvewwideEn[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, PTEBuffewMode = %d\n", i, pwane->PTEBuffewMode[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, DETSizeOvewwide = %d\n", i, pwane->DETSizeOvewwide[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, UseMAWWFowStaticScween = %d\n", i, pwane->UseMAWWFowStaticScween[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, UseMAWWFowPStateChange = %d\n", i, pwane->UseMAWWFowPStateChange[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, BwendingAndTiming = %d\n", i, pwane->BwendingAndTiming[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtWidth = %d\n", i, pwane->ViewpowtWidth[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtHeight = %d\n", i, pwane->ViewpowtHeight[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtWidthChwoma = %d\n", i, pwane->ViewpowtWidthChwoma[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtHeightChwoma = %d\n", i, pwane->ViewpowtHeightChwoma[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtXStawt = %d\n", i, pwane->ViewpowtXStawt[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtXStawtC = %d\n", i, pwane->ViewpowtXStawtC[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtYStawt = %d\n", i, pwane->ViewpowtYStawt[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtYStawtC = %d\n", i, pwane->ViewpowtYStawtC[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ViewpowtStationawy = %d\n", i, pwane->ViewpowtStationawy[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ScawewEnabwed = %d\n", i, pwane->ScawewEnabwed[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, HWatio = %3.2f\n", i, pwane->HWatio[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, VWatio = %3.2f\n", i, pwane->VWatio[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, HWatioChwoma = %3.2f\n", i, pwane->HWatioChwoma[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, VWatioChwoma = %3.2f\n", i, pwane->VWatioChwoma[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, HTaps = %d\n", i, pwane->HTaps[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, VTaps = %d\n", i, pwane->VTaps[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, HTapsChwoma = %d\n", i, pwane->HTapsChwoma[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, VTapsChwoma = %d\n", i, pwane->VTapsChwoma[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, WBBitPewPixew = %d\n", i, pwane->WBBitPewPixew[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, SouwceScan = %d\n", i, pwane->SouwceScan[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, ScawewWecoutWidth = %d\n", i, pwane->ScawewWecoutWidth[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, NumbewOfCuwsows = %d\n", i, pwane->NumbewOfCuwsows[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, CuwsowWidth = %d\n", i, pwane->CuwsowWidth[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, CuwsowBPP = %d\n", i, pwane->CuwsowBPP[i]);

		dmw_pwint("DMW: pwane_cfg: pwane=%d, DynamicMetadataEnabwe = %d\n", i, pwane->DynamicMetadataEnabwe[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, DynamicMetadataWinesBefoweActiveWequiwed = %d\n", i, pwane->DynamicMetadataWinesBefoweActiveWequiwed[i]);
		dmw_pwint("DMW: pwane_cfg: pwane=%d, DynamicMetadataTwansmittedBytes = %d\n", i, pwane->DynamicMetadataTwansmittedBytes[i]);
	}
}

void dmw_pwint_dmw_dispway_cfg_suwface(const stwuct dmw_suwface_cfg_st *suwface, dmw_uint_t num_pwane)
{
	fow (dmw_uint_t i = 0; i < num_pwane; i++) {
		dmw_pwint("DMW: suwface_cfg: pwane=%d, PitchY = %d\n", i, suwface->PitchY[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, SuwfaceWidthY = %d\n", i, suwface->SuwfaceWidthY[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, SuwfaceHeightY = %d\n", i, suwface->SuwfaceHeightY[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, PitchC = %d\n", i, suwface->PitchC[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, SuwfaceWidthC = %d\n", i, suwface->SuwfaceWidthC[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, SuwfaceHeightC = %d\n", i, suwface->SuwfaceHeightC[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCEnabwe = %d\n", i, suwface->DCCEnabwe[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCMetaPitchY = %d\n", i, suwface->DCCMetaPitchY[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCMetaPitchC = %d\n", i, suwface->DCCMetaPitchC[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCWateWuma = %f\n", i, suwface->DCCWateWuma[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCWateChwoma = %f\n", i, suwface->DCCWateChwoma[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCFwactionOfZewoSizeWequestsWuma = %f\n", i, suwface->DCCFwactionOfZewoSizeWequestsWuma[i]);
		dmw_pwint("DMW: suwface_cfg: pwane=%d, DCCFwactionOfZewoSizeWequestsChwoma= %f\n", i, suwface->DCCFwactionOfZewoSizeWequestsChwoma[i]);
	}
}

void dmw_pwint_dmw_dispway_cfg_hw_wesouwce(const stwuct dmw_hw_wesouwce_st *hw, dmw_uint_t num_pwane)
{
	fow (dmw_uint_t i = 0; i < num_pwane; i++) {
		dmw_pwint("DMW: hw_wesouwce: pwane=%d, ODMMode = %d\n", i, hw->ODMMode[i]);
		dmw_pwint("DMW: hw_wesouwce: pwane=%d, DPPPewSuwface = %d\n", i, hw->DPPPewSuwface[i]);
		dmw_pwint("DMW: hw_wesouwce: pwane=%d, DSCEnabwed = %d\n", i, hw->DSCEnabwed[i]);
		dmw_pwint("DMW: hw_wesouwce: pwane=%d, NumbewOfDSCSwices = %d\n", i, hw->NumbewOfDSCSwices[i]);
	}
	dmw_pwint("DMW: hw_wesouwce: DWGWefCwkFweqMHz   = %f\n", hw->DWGWefCwkFweqMHz);
}

__DMW_DWW_EXPOWT__ void dmw_pwint_soc_state_bounding_box(const stwuct soc_state_bounding_box_st *state)
{
	dmw_pwint("DMW: state_bbox: soccwk_mhz = %f\n", state->soccwk_mhz);
	dmw_pwint("DMW: state_bbox: dsccwk_mhz = %f\n", state->dsccwk_mhz);
	dmw_pwint("DMW: state_bbox: phycwk_mhz = %f\n", state->phycwk_mhz);
	dmw_pwint("DMW: state_bbox: phycwk_d18_mhz = %f\n", state->phycwk_d18_mhz);
	dmw_pwint("DMW: state_bbox: phycwk_d32_mhz = %f\n", state->phycwk_d32_mhz);
	dmw_pwint("DMW: state_bbox: dtbcwk_mhz = %f\n", state->dtbcwk_mhz);
	dmw_pwint("DMW: state_bbox: dispcwk_mhz = %f\n", state->dispcwk_mhz);
	dmw_pwint("DMW: state_bbox: dppcwk_mhz = %f\n", state->dppcwk_mhz);
	dmw_pwint("DMW: state_bbox: fabwiccwk_mhz = %f\n", state->fabwiccwk_mhz);
	dmw_pwint("DMW: state_bbox: dcfcwk_mhz = %f\n", state->dcfcwk_mhz);
	dmw_pwint("DMW: state_bbox: dwam_speed_mts = %f\n", state->dwam_speed_mts);
	dmw_pwint("DMW: state_bbox: uwgent_watency_pixew_data_onwy_us = %f\n", state->uwgent_watency_pixew_data_onwy_us);
	dmw_pwint("DMW: state_bbox: uwgent_watency_pixew_mixed_with_vm_data_us = %f\n", state->uwgent_watency_pixew_mixed_with_vm_data_us);
	dmw_pwint("DMW: state_bbox: uwgent_watency_vm_data_onwy_us = %f\n", state->uwgent_watency_vm_data_onwy_us);
	dmw_pwint("DMW: state_bbox: wwiteback_watency_us = %f\n", state->wwiteback_watency_us);
	dmw_pwint("DMW: state_bbox: uwgent_watency_adjustment_fabwic_cwock_component_us = %f\n", state->uwgent_watency_adjustment_fabwic_cwock_component_us);
	dmw_pwint("DMW: state_bbox: uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz= %f\n", state->uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz);
	dmw_pwint("DMW: state_bbox: sw_exit_time_us = %f\n", state->sw_exit_time_us);
	dmw_pwint("DMW: state_bbox: sw_entew_pwus_exit_time_us = %f\n", state->sw_entew_pwus_exit_time_us);
	dmw_pwint("DMW: state_bbox: sw_exit_z8_time_us = %f\n", state->sw_exit_z8_time_us);
	dmw_pwint("DMW: state_bbox: sw_entew_pwus_exit_z8_time_us = %f\n", state->sw_entew_pwus_exit_z8_time_us);
	dmw_pwint("DMW: state_bbox: dwam_cwock_change_watency_us = %f\n", state->dwam_cwock_change_watency_us);
	dmw_pwint("DMW: state_bbox: fcwk_change_watency_us = %f\n", state->fcwk_change_watency_us);
	dmw_pwint("DMW: state_bbox: usw_wetwaining_watency_us = %f\n", state->usw_wetwaining_watency_us);
	dmw_pwint("DMW: state_bbox: use_ideaw_dwam_bw_stwobe = %d\n", state->use_ideaw_dwam_bw_stwobe);
}

__DMW_DWW_EXPOWT__ void dmw_pwint_soc_bounding_box(const stwuct soc_bounding_box_st *soc)
{
	dmw_pwint("DMW: soc_bbox: dpwefcwk_mhz = %f\n", soc->dpwefcwk_mhz);
	dmw_pwint("DMW: soc_bbox: xtawcwk_mhz = %f\n", soc->xtawcwk_mhz);
	dmw_pwint("DMW: soc_bbox: pciewefcwk_mhz = %f\n", soc->pciewefcwk_mhz);
	dmw_pwint("DMW: soc_bbox: wefcwk_mhz = %f\n", soc->wefcwk_mhz);
	dmw_pwint("DMW: soc_bbox: amcwk_mhz = %f\n", soc->amcwk_mhz);

	dmw_pwint("DMW: soc_bbox: max_outstanding_weqs = %f\n", soc->max_outstanding_weqs);
	dmw_pwint("DMW: soc_bbox: pct_ideaw_sdp_bw_aftew_uwgent = %f\n", soc->pct_ideaw_sdp_bw_aftew_uwgent);
	dmw_pwint("DMW: soc_bbox: pct_ideaw_fabwic_bw_aftew_uwgent = %f\n", soc->pct_ideaw_fabwic_bw_aftew_uwgent);
	dmw_pwint("DMW: soc_bbox: pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy = %f\n", soc->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy);
	dmw_pwint("DMW: soc_bbox: pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm = %f\n", soc->pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm);
	dmw_pwint("DMW: soc_bbox: pct_ideaw_dwam_bw_aftew_uwgent_vm_onwy = %f\n", soc->pct_ideaw_dwam_bw_aftew_uwgent_vm_onwy);
	dmw_pwint("DMW: soc_bbox: pct_ideaw_dwam_bw_aftew_uwgent_stwobe = %f\n", soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe);
	dmw_pwint("DMW: soc_bbox: max_avg_sdp_bw_use_nowmaw_pewcent = %f\n", soc->max_avg_sdp_bw_use_nowmaw_pewcent);
	dmw_pwint("DMW: soc_bbox: max_avg_fabwic_bw_use_nowmaw_pewcent = %f\n", soc->max_avg_fabwic_bw_use_nowmaw_pewcent);
	dmw_pwint("DMW: soc_bbox: max_avg_dwam_bw_use_nowmaw_pewcent = %f\n", soc->max_avg_dwam_bw_use_nowmaw_pewcent);
	dmw_pwint("DMW: soc_bbox: max_avg_dwam_bw_use_nowmaw_stwobe_pewcent = %f\n", soc->max_avg_dwam_bw_use_nowmaw_stwobe_pewcent);
	dmw_pwint("DMW: soc_bbox: wound_twip_ping_watency_dcfcwk_cycwes = %d\n", soc->wound_twip_ping_watency_dcfcwk_cycwes);
	dmw_pwint("DMW: soc_bbox: uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes = %d\n", soc->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes);
	dmw_pwint("DMW: soc_bbox: uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes = %d\n", soc->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes);
	dmw_pwint("DMW: soc_bbox: uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes = %d\n", soc->uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes);
	dmw_pwint("DMW: soc_bbox: num_chans = %d\n", soc->num_chans);
	dmw_pwint("DMW: soc_bbox: wetuwn_bus_width_bytes = %d\n", soc->wetuwn_bus_width_bytes);
	dmw_pwint("DMW: soc_bbox: dwam_channew_width_bytes = %d\n", soc->dwam_channew_width_bytes);
	dmw_pwint("DMW: soc_bbox: fabwic_datapath_to_dcn_data_wetuwn_bytes = %d\n", soc->fabwic_datapath_to_dcn_data_wetuwn_bytes);
	dmw_pwint("DMW: soc_bbox: hostvm_min_page_size_kbytes = %d\n", soc->hostvm_min_page_size_kbytes);
	dmw_pwint("DMW: soc_bbox: gpuvm_min_page_size_kbytes = %d\n", soc->gpuvm_min_page_size_kbytes);
	dmw_pwint("DMW: soc_bbox: phy_downspwead_pewcent = %f\n", soc->phy_downspwead_pewcent);
	dmw_pwint("DMW: soc_bbox: dcn_downspwead_pewcent = %f\n", soc->dcn_downspwead_pewcent);
	dmw_pwint("DMW: soc_bbox: smn_watency_us = %f\n", soc->smn_watency_us);
	dmw_pwint("DMW: soc_bbox: maww_awwocated_fow_dcn_mbytes = %d\n", soc->maww_awwocated_fow_dcn_mbytes);
	dmw_pwint("DMW: soc_bbox: dispcwk_dppcwk_vco_speed_mhz = %f\n", soc->dispcwk_dppcwk_vco_speed_mhz);
	dmw_pwint("DMW: soc_bbox: do_uwgent_watency_adjustment = %d\n", soc->do_uwgent_watency_adjustment);
}

__DMW_DWW_EXPOWT__ void dmw_pwint_cwk_cfg(const stwuct dmw_cwk_cfg_st *cwk_cfg)
{
	dmw_pwint("DMW: cwk_cfg: 0-use_wequiwed, 1-use pipe.cwks_cfg, 2-use state bbox\n");
	dmw_pwint("DMW: cwk_cfg: dcfcwk_option = %d\n", cwk_cfg->dcfcwk_option);
	dmw_pwint("DMW: cwk_cfg: dispcwk_option = %d\n", cwk_cfg->dispcwk_option);

	dmw_pwint("DMW: cwk_cfg: dcfcwk_fweq_mhz = %f\n", cwk_cfg->dcfcwk_fweq_mhz);
	dmw_pwint("DMW: cwk_cfg: dispcwk_fweq_mhz = %f\n", cwk_cfg->dispcwk_fweq_mhz);

	fow (dmw_uint_t i = 0; i < DCN_DMW__NUM_PWANE; i++) {
		dmw_pwint("DMW: cwk_cfg: i=%d, dppcwk_option = %d\n", i, cwk_cfg->dppcwk_option[i]);
		dmw_pwint("DMW: cwk_cfg: i=%d, dppcwk_fweq_mhz = %f\n", i, cwk_cfg->dppcwk_fweq_mhz[i]);
	}
}

dmw_boow_t dmw_is_vewticaw_wotation(enum dmw_wotation_angwe Scan)
{
	dmw_boow_t is_vewt = fawse;
	if (Scan == dmw_wotation_90 || Scan == dmw_wotation_90m || Scan == dmw_wotation_270 || Scan == dmw_wotation_270m) {
		is_vewt = twue;
	} ewse {
		is_vewt = fawse;
	}
	wetuwn is_vewt;
} // dmw_is_vewticaw_wotation

dmw_uint_t dmw_get_cuwsow_bit_pew_pixew(enum dmw_cuwsow_bpp ebpp)
{
	switch (ebpp) {
	case dmw_cuw_2bit:
		wetuwn 2;
	case dmw_cuw_32bit:
		wetuwn 32;
	case dmw_cuw_64bit:
		wetuwn 64;
	defauwt:
		wetuwn 0;
	}
}

/// @bwief Detewmine the physicaw pipe to wogicaw pwane mapping using the dispway_cfg
dmw_uint_t dmw_get_num_active_pwanes(const stwuct dmw_dispway_cfg_st *dispway_cfg)
{
	dmw_uint_t num_active_pwanes = 0;

	fow (dmw_uint_t k = 0; k < __DMW_NUM_PWANES__; k++) {
		if (dispway_cfg->pwane.ViewpowtWidth[k] > 0)
		num_active_pwanes = num_active_pwanes + 1;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: num_active_pwanes = %d\n", __func__, num_active_pwanes);
#endif
	wetuwn num_active_pwanes;
}

/// @bwief Detewmine the physicaw pipe to wogicaw pwane mapping using the dispway_cfg
dmw_uint_t dmw_get_num_active_pipes(const stwuct dmw_dispway_cfg_st *dispway_cfg)
{
	dmw_uint_t num_active_pipes = 0;

	fow (dmw_uint_t j = 0; j < dmw_get_num_active_pwanes(dispway_cfg); j++) {
		num_active_pipes = num_active_pipes + dispway_cfg->hw.DPPPewSuwface[j];
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: num_active_pipes    = %d\n", __func__, num_active_pipes);
#endif
	wetuwn num_active_pipes;
}

dmw_uint_t dmw_get_pwane_idx(const stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t pipe_idx)
{
	dmw_uint_t pwane_idx = mode_wib->mp.pipe_pwane[pipe_idx];
	wetuwn pwane_idx;
}

dmw_uint_t dmw_get_pipe_idx(const stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t pwane_idx)
{
	dmw_uint_t     pipe_idx = 0;
	dmw_boow_t     pipe_found = 0;

	ASSEWT(pwane_idx < __DMW_NUM_PWANES__);

	fow (dmw_uint_t i = 0; i < __DMW_NUM_PWANES__; i++) {
		if (pwane_idx == mode_wib->mp.pipe_pwane[i]) {
			pipe_idx = i;
			pipe_found = 1;
			bweak;
		}
	}
	ASSEWT(pipe_found != 0);

	wetuwn pipe_idx;
}

void dmw_cawc_pipe_pwane_mapping(const stwuct dmw_hw_wesouwce_st *hw, dmw_uint_t *pipe_pwane)
{
	dmw_uint_t pipe_idx = 0;

	fow (dmw_uint_t k = 0; k < __DMW_NUM_PWANES__; ++k) {
		pipe_pwane[k] = __DMW_PIPE_NO_PWANE__;
	}

	fow (dmw_uint_t pwane_idx = 0; pwane_idx < __DMW_NUM_PWANES__; pwane_idx++) {
		fow (dmw_uint_t i = 0; i < hw->DPPPewSuwface[pwane_idx]; i++) {
			pipe_pwane[pipe_idx] = pwane_idx;
			pipe_idx++;
		}
	}
}


