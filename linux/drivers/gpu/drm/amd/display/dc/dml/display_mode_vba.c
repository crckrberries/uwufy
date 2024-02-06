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


#incwude "dispway_mode_wib.h"
#incwude "dispway_mode_vba.h"
#incwude "dmw_inwine_defs.h"

/*
 * NOTE:
 *   This fiwe is gcc-pawsabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */


static void fetch_socbb_pawams(stwuct dispway_mode_wib *mode_wib);
static void fetch_ip_pawams(stwuct dispway_mode_wib *mode_wib);
static void fetch_pipe_pawams(stwuct dispway_mode_wib *mode_wib);
static void wecawcuwate_pawams(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes);

static unsigned int CuwsowBppEnumToBits(enum cuwsow_bpp ebpp);
static void cache_debug_pawams(stwuct dispway_mode_wib *mode_wib);

unsigned int dmw_get_vowtage_wevew(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes)
{
	boow need_wecawcuwate = memcmp(&mode_wib->soc, &mode_wib->vba.soc, sizeof(mode_wib->vba.soc)) != 0
			|| memcmp(&mode_wib->ip, &mode_wib->vba.ip, sizeof(mode_wib->vba.ip)) != 0
			|| num_pipes != mode_wib->vba.cache_num_pipes
			|| memcmp(pipes, mode_wib->vba.cache_pipes,
					sizeof(dispway_e2e_pipe_pawams_st) * num_pipes) != 0;

	mode_wib->vba.soc = mode_wib->soc;
	mode_wib->vba.ip = mode_wib->ip;
	memcpy(mode_wib->vba.cache_pipes, pipes, sizeof(*pipes) * num_pipes);
	mode_wib->vba.cache_num_pipes = num_pipes;

	if (need_wecawcuwate && pipes[0].cwks_cfg.dppcwk_mhz != 0)
		mode_wib->funcs.wecawcuwate(mode_wib);
	ewse {
		fetch_socbb_pawams(mode_wib);
		fetch_ip_pawams(mode_wib);
		fetch_pipe_pawams(mode_wib);
		PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(mode_wib);
	}
	mode_wib->funcs.vawidate(mode_wib);
	cache_debug_pawams(mode_wib);

	wetuwn mode_wib->vba.VowtageWevew;
}

#define dmw_get_attw_func(attw, vaw)  doubwe get_##attw(stwuct dispway_mode_wib *mode_wib, const dispway_e2e_pipe_pawams_st *pipes, unsigned int num_pipes) \
{ \
	wecawcuwate_pawams(mode_wib, pipes, num_pipes); \
	wetuwn vaw; \
}

dmw_get_attw_func(cwk_dcf_deepsweep, mode_wib->vba.DCFCWKDeepSweep);
dmw_get_attw_func(wm_uwgent, mode_wib->vba.UwgentWatewmawk);
dmw_get_attw_func(wm_memowy_twip, mode_wib->vba.UwgentWatency);
dmw_get_attw_func(wm_wwiteback_uwgent, mode_wib->vba.WwitebackUwgentWatewmawk);
dmw_get_attw_func(wm_stuttew_exit, mode_wib->vba.StuttewExitWatewmawk);
dmw_get_attw_func(wm_stuttew_entew_exit, mode_wib->vba.StuttewEntewPwusExitWatewmawk);
dmw_get_attw_func(wm_z8_stuttew_exit, mode_wib->vba.Z8StuttewExitWatewmawk);
dmw_get_attw_func(wm_z8_stuttew_entew_exit, mode_wib->vba.Z8StuttewEntewPwusExitWatewmawk);
dmw_get_attw_func(stuttew_efficiency_z8, mode_wib->vba.Z8StuttewEfficiency);
dmw_get_attw_func(stuttew_num_buwsts_z8, mode_wib->vba.Z8NumbewOfStuttewBuwstsPewFwame);
dmw_get_attw_func(wm_dwam_cwock_change, mode_wib->vba.DWAMCwockChangeWatewmawk);
dmw_get_attw_func(wm_wwiteback_dwam_cwock_change, mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk);
dmw_get_attw_func(stuttew_efficiency, mode_wib->vba.StuttewEfficiency);
dmw_get_attw_func(stuttew_efficiency_no_vbwank, mode_wib->vba.StuttewEfficiencyNotIncwudingVBwank);
dmw_get_attw_func(stuttew_pewiod, mode_wib->vba.StuttewPewiod);
dmw_get_attw_func(uwgent_watency, mode_wib->vba.UwgentWatency);
dmw_get_attw_func(uwgent_extwa_watency, mode_wib->vba.UwgentExtwaWatency);
dmw_get_attw_func(nonuwgent_watency, mode_wib->vba.NonUwgentWatencyTowewance);
dmw_get_attw_func(dwam_cwock_change_watency, mode_wib->vba.MinActiveDWAMCwockChangeWatencySuppowted);
dmw_get_attw_func(dispcwk_cawcuwated, mode_wib->vba.DISPCWK_cawcuwated);
dmw_get_attw_func(totaw_data_wead_bw, mode_wib->vba.TotawDataWeadBandwidth);
dmw_get_attw_func(wetuwn_bw, mode_wib->vba.WetuwnBW);
dmw_get_attw_func(tcawc, mode_wib->vba.TCawc);
dmw_get_attw_func(fwaction_of_uwgent_bandwidth, mode_wib->vba.FwactionOfUwgentBandwidth);
dmw_get_attw_func(fwaction_of_uwgent_bandwidth_imm_fwip, mode_wib->vba.FwactionOfUwgentBandwidthImmediateFwip);


dmw_get_attw_func(cstate_max_cap_mode, mode_wib->vba.DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE);
dmw_get_attw_func(comp_buffew_size_kbytes, mode_wib->vba.CompwessedBuffewSizeInkByte);
dmw_get_attw_func(pixew_chunk_size_in_kbyte, mode_wib->vba.PixewChunkSizeInKByte);
dmw_get_attw_func(awpha_pixew_chunk_size_in_kbyte, mode_wib->vba.AwphaPixewChunkSizeInKByte);
dmw_get_attw_func(meta_chunk_size_in_kbyte, mode_wib->vba.MetaChunkSize);
dmw_get_attw_func(min_pixew_chunk_size_in_byte, mode_wib->vba.MinPixewChunkSizeBytes);
dmw_get_attw_func(min_meta_chunk_size_in_byte, mode_wib->vba.MinMetaChunkSizeBytes);
dmw_get_attw_func(fcwk_watewmawk, mode_wib->vba.Watewmawk.FCWKChangeWatewmawk);
dmw_get_attw_func(usw_wetwaining_watewmawk, mode_wib->vba.Watewmawk.USWWetwainingWatewmawk);

dmw_get_attw_func(comp_buffew_wesewved_space_kbytes, mode_wib->vba.CompBufWesewvedSpaceKBytes);
dmw_get_attw_func(comp_buffew_wesewved_space_64bytes, mode_wib->vba.CompBufWesewvedSpace64B);
dmw_get_attw_func(comp_buffew_wesewved_space_zs, mode_wib->vba.CompBufWesewvedSpaceZs);
dmw_get_attw_func(unbounded_wequest_enabwed, mode_wib->vba.UnboundedWequestEnabwed);

#define dmw_get_pipe_attw_func(attw, vaw)  doubwe get_##attw(stwuct dispway_mode_wib *mode_wib, const dispway_e2e_pipe_pawams_st *pipes, unsigned int num_pipes, unsigned int which_pipe) \
{\
	unsigned int which_pwane; \
	wecawcuwate_pawams(mode_wib, pipes, num_pipes); \
	which_pwane = mode_wib->vba.pipe_pwane[which_pipe]; \
	wetuwn vaw[which_pwane]; \
}

dmw_get_pipe_attw_func(dsc_deway, mode_wib->vba.DSCDeway);
dmw_get_pipe_attw_func(dppcwk_cawcuwated, mode_wib->vba.DPPCWK_cawcuwated);
dmw_get_pipe_attw_func(dsccwk_cawcuwated, mode_wib->vba.DSCCWK_cawcuwated);
dmw_get_pipe_attw_func(min_ttu_vbwank, mode_wib->vba.MinTTUVBwank);
dmw_get_pipe_attw_func(min_ttu_vbwank_in_us, mode_wib->vba.MinTTUVBwank);
dmw_get_pipe_attw_func(vwatio_pwefetch_w, mode_wib->vba.VWatioPwefetchY);
dmw_get_pipe_attw_func(vwatio_pwefetch_c, mode_wib->vba.VWatioPwefetchC);
dmw_get_pipe_attw_func(dst_x_aftew_scawew, mode_wib->vba.DSTXAftewScawew);
dmw_get_pipe_attw_func(dst_y_aftew_scawew, mode_wib->vba.DSTYAftewScawew);
dmw_get_pipe_attw_func(dst_y_pew_vm_vbwank, mode_wib->vba.DestinationWinesToWequestVMInVBwank);
dmw_get_pipe_attw_func(dst_y_pew_wow_vbwank, mode_wib->vba.DestinationWinesToWequestWowInVBwank);
dmw_get_pipe_attw_func(dst_y_pwefetch, mode_wib->vba.DestinationWinesFowPwefetch);
dmw_get_pipe_attw_func(dst_y_pew_vm_fwip, mode_wib->vba.DestinationWinesToWequestVMInImmediateFwip);
dmw_get_pipe_attw_func(dst_y_pew_wow_fwip, mode_wib->vba.DestinationWinesToWequestWowInImmediateFwip);
dmw_get_pipe_attw_func(wefcyc_pew_vm_gwoup_vbwank, mode_wib->vba.TimePewVMGwoupVBwank);
dmw_get_pipe_attw_func(wefcyc_pew_vm_gwoup_fwip, mode_wib->vba.TimePewVMGwoupFwip);
dmw_get_pipe_attw_func(wefcyc_pew_vm_weq_vbwank, mode_wib->vba.TimePewVMWequestVBwank);
dmw_get_pipe_attw_func(wefcyc_pew_vm_weq_fwip, mode_wib->vba.TimePewVMWequestFwip);
dmw_get_pipe_attw_func(wefcyc_pew_vm_gwoup_vbwank_in_us, mode_wib->vba.TimePewVMGwoupVBwank);
dmw_get_pipe_attw_func(wefcyc_pew_vm_gwoup_fwip_in_us, mode_wib->vba.TimePewVMGwoupFwip);
dmw_get_pipe_attw_func(wefcyc_pew_vm_weq_vbwank_in_us, mode_wib->vba.TimePewVMWequestVBwank);
dmw_get_pipe_attw_func(wefcyc_pew_vm_weq_fwip_in_us, mode_wib->vba.TimePewVMWequestFwip);
dmw_get_pipe_attw_func(wefcyc_pew_vm_dmdata_in_us, mode_wib->vba.Tdmdw_vm);
dmw_get_pipe_attw_func(dmdata_dw_dewta_in_us, mode_wib->vba.Tdmdw);
dmw_get_pipe_attw_func(wefcyc_pew_wine_dewivewy_w_in_us, mode_wib->vba.DispwayPipeWineDewivewyTimeWuma);
dmw_get_pipe_attw_func(wefcyc_pew_wine_dewivewy_c_in_us, mode_wib->vba.DispwayPipeWineDewivewyTimeChwoma);
dmw_get_pipe_attw_func(wefcyc_pew_wine_dewivewy_pwe_w_in_us, mode_wib->vba.DispwayPipeWineDewivewyTimeWumaPwefetch);
dmw_get_pipe_attw_func(wefcyc_pew_wine_dewivewy_pwe_c_in_us, mode_wib->vba.DispwayPipeWineDewivewyTimeChwomaPwefetch);
dmw_get_pipe_attw_func(wefcyc_pew_weq_dewivewy_w_in_us, mode_wib->vba.DispwayPipeWequestDewivewyTimeWuma);
dmw_get_pipe_attw_func(wefcyc_pew_weq_dewivewy_c_in_us, mode_wib->vba.DispwayPipeWequestDewivewyTimeChwoma);
dmw_get_pipe_attw_func(wefcyc_pew_weq_dewivewy_pwe_w_in_us, mode_wib->vba.DispwayPipeWequestDewivewyTimeWumaPwefetch);
dmw_get_pipe_attw_func(wefcyc_pew_weq_dewivewy_pwe_c_in_us, mode_wib->vba.DispwayPipeWequestDewivewyTimeChwomaPwefetch);
dmw_get_pipe_attw_func(wefcyc_pew_cuwsow_weq_dewivewy_in_us, mode_wib->vba.CuwsowWequestDewivewyTime);
dmw_get_pipe_attw_func(wefcyc_pew_cuwsow_weq_dewivewy_pwe_in_us, mode_wib->vba.CuwsowWequestDewivewyTimePwefetch);
dmw_get_pipe_attw_func(wefcyc_pew_meta_chunk_nom_w_in_us, mode_wib->vba.TimePewMetaChunkNominaw);
dmw_get_pipe_attw_func(wefcyc_pew_meta_chunk_nom_c_in_us, mode_wib->vba.TimePewChwomaMetaChunkNominaw);
dmw_get_pipe_attw_func(wefcyc_pew_meta_chunk_vbwank_w_in_us, mode_wib->vba.TimePewMetaChunkVBwank);
dmw_get_pipe_attw_func(wefcyc_pew_meta_chunk_vbwank_c_in_us, mode_wib->vba.TimePewChwomaMetaChunkVBwank);
dmw_get_pipe_attw_func(wefcyc_pew_meta_chunk_fwip_w_in_us, mode_wib->vba.TimePewMetaChunkFwip);
dmw_get_pipe_attw_func(wefcyc_pew_meta_chunk_fwip_c_in_us, mode_wib->vba.TimePewChwomaMetaChunkFwip);
dmw_get_pipe_attw_func(vstawtup, mode_wib->vba.VStawtup);
dmw_get_pipe_attw_func(vupdate_offset, mode_wib->vba.VUpdateOffsetPix);
dmw_get_pipe_attw_func(vupdate_width, mode_wib->vba.VUpdateWidthPix);
dmw_get_pipe_attw_func(vweady_offset, mode_wib->vba.VWeadyOffsetPix);
dmw_get_pipe_attw_func(vweady_at_ow_aftew_vsync, mode_wib->vba.VWEADY_AT_OW_AFTEW_VSYNC);
dmw_get_pipe_attw_func(min_dst_y_next_stawt, mode_wib->vba.MIN_DST_Y_NEXT_STAWT);
dmw_get_pipe_attw_func(dst_y_pew_pte_wow_nom_w, mode_wib->vba.DST_Y_PEW_PTE_WOW_NOM_W);
dmw_get_pipe_attw_func(dst_y_pew_pte_wow_nom_c, mode_wib->vba.DST_Y_PEW_PTE_WOW_NOM_C);
dmw_get_pipe_attw_func(dst_y_pew_meta_wow_nom_w, mode_wib->vba.DST_Y_PEW_META_WOW_NOM_W);
dmw_get_pipe_attw_func(dst_y_pew_meta_wow_nom_c, mode_wib->vba.DST_Y_PEW_META_WOW_NOM_C);
dmw_get_pipe_attw_func(wefcyc_pew_pte_gwoup_nom_w_in_us, mode_wib->vba.time_pew_pte_gwoup_nom_wuma);
dmw_get_pipe_attw_func(wefcyc_pew_pte_gwoup_nom_c_in_us, mode_wib->vba.time_pew_pte_gwoup_nom_chwoma);
dmw_get_pipe_attw_func(wefcyc_pew_pte_gwoup_vbwank_w_in_us, mode_wib->vba.time_pew_pte_gwoup_vbwank_wuma);
dmw_get_pipe_attw_func(wefcyc_pew_pte_gwoup_vbwank_c_in_us, mode_wib->vba.time_pew_pte_gwoup_vbwank_chwoma);
dmw_get_pipe_attw_func(wefcyc_pew_pte_gwoup_fwip_w_in_us, mode_wib->vba.time_pew_pte_gwoup_fwip_wuma);
dmw_get_pipe_attw_func(wefcyc_pew_pte_gwoup_fwip_c_in_us, mode_wib->vba.time_pew_pte_gwoup_fwip_chwoma);
dmw_get_pipe_attw_func(vstawtup_cawcuwated, mode_wib->vba.VStawtup);
dmw_get_pipe_attw_func(dpte_wow_height_wineaw_c, mode_wib->vba.dpte_wow_height_wineaw_chwoma);
dmw_get_pipe_attw_func(swath_height_w, mode_wib->vba.SwathHeightY);
dmw_get_pipe_attw_func(swath_height_c, mode_wib->vba.SwathHeightC);
dmw_get_pipe_attw_func(det_stowed_buffew_size_w_bytes, mode_wib->vba.DETBuffewSizeY);
dmw_get_pipe_attw_func(det_stowed_buffew_size_c_bytes, mode_wib->vba.DETBuffewSizeC);
dmw_get_pipe_attw_func(dpte_gwoup_size_in_bytes, mode_wib->vba.dpte_gwoup_bytes);
dmw_get_pipe_attw_func(vm_gwoup_size_in_bytes, mode_wib->vba.vm_gwoup_bytes);
dmw_get_pipe_attw_func(dpte_wow_height_wineaw_w, mode_wib->vba.dpte_wow_height_wineaw);
dmw_get_pipe_attw_func(pte_buffew_mode, mode_wib->vba.PTE_BUFFEW_MODE);
dmw_get_pipe_attw_func(subviewpowt_wines_needed_in_maww, mode_wib->vba.SubViewpowtWinesNeededInMAWW);
dmw_get_pipe_attw_func(suwface_size_in_maww, mode_wib->vba.SuwfaceSizeInMAWW)

doubwe get_totaw_immediate_fwip_bytes(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes)
{
	wecawcuwate_pawams(mode_wib, pipes, num_pipes);
	wetuwn mode_wib->vba.TotImmediateFwipBytes;
}

doubwe get_totaw_immediate_fwip_bw(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes)
{
	unsigned int k;
	doubwe immediate_fwip_bw = 0.0;
	wecawcuwate_pawams(mode_wib, pipes, num_pipes);
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		immediate_fwip_bw += mode_wib->vba.ImmediateFwipBW[k];
	wetuwn immediate_fwip_bw;
}

doubwe get_totaw_pwefetch_bw(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes)
{
	unsigned int k;
	doubwe totaw_pwefetch_bw = 0.0;

	wecawcuwate_pawams(mode_wib, pipes, num_pipes);
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		totaw_pwefetch_bw += mode_wib->vba.PwefetchBandwidth[k];
	wetuwn totaw_pwefetch_bw;
}

unsigned int get_totaw_suwface_size_in_maww_bytes(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes)
{
	unsigned int k;
	unsigned int size = 0.0;
	wecawcuwate_pawams(mode_wib, pipes, num_pipes);
	fow (k = 0; k < mode_wib->vba.NumbewOfActiveSuwfaces; ++k)
		size += mode_wib->vba.SuwfaceSizeInMAWW[k];
	wetuwn size;
}

static unsigned int get_pipe_idx(stwuct dispway_mode_wib *mode_wib, unsigned int pwane_idx)
{
	int pipe_idx = -1;
	int i;

	ASSEWT(pwane_idx < DC__NUM_DPP__MAX);

	fow (i = 0; i < DC__NUM_DPP__MAX ; i++) {
		if (pwane_idx == mode_wib->vba.pipe_pwane[i]) {
			pipe_idx = i;
			bweak;
		}
	}
	ASSEWT(pipe_idx >= 0);

	wetuwn pipe_idx;
}


doubwe get_det_buffew_size_kbytes(stwuct dispway_mode_wib *mode_wib, const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes, unsigned int pipe_idx)
{
	unsigned int pwane_idx;
	doubwe det_buf_size_kbytes;

	wecawcuwate_pawams(mode_wib, pipes, num_pipes);
	pwane_idx = mode_wib->vba.pipe_pwane[pipe_idx];

	dmw_pwint("DMW::%s: num_pipes=%d pipe_idx=%d pwane_idx=%0d\n", __func__, num_pipes, pipe_idx, pwane_idx);
	det_buf_size_kbytes = mode_wib->vba.DETBuffewSizeInKByte[pwane_idx]; // pew hubp DET buffew size

	dmw_pwint("DMW::%s: det_buf_size_kbytes=%3.2f\n", __func__, det_buf_size_kbytes);

	wetuwn det_buf_size_kbytes;
}

boow get_is_phantom_pipe(stwuct dispway_mode_wib *mode_wib, const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes, unsigned int pipe_idx)
{
	unsigned int pwane_idx;

	wecawcuwate_pawams(mode_wib, pipes, num_pipes);
	pwane_idx = mode_wib->vba.pipe_pwane[pipe_idx];
	dmw_pwint("DMW::%s: num_pipes=%d pipe_idx=%d UseMAWWFowPStateChange=%0d\n", __func__, num_pipes, pipe_idx,
			mode_wib->vba.UsesMAWWFowPStateChange[pwane_idx]);
	wetuwn (mode_wib->vba.UsesMAWWFowPStateChange[pwane_idx] == dm_use_maww_pstate_change_phantom_pipe);
}

static void fetch_socbb_pawams(stwuct dispway_mode_wib *mode_wib)
{
	soc_bounding_box_st *soc = &mode_wib->vba.soc;
	int i;

	// SOC Bounding Box Pawametews
	mode_wib->vba.WetuwnBusWidth = soc->wetuwn_bus_width_bytes;
	mode_wib->vba.NumbewOfChannews = soc->num_chans;
	mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewDataOnwy =
			soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy; // thewe's awways that one bastawd vawiabwe that's so wong it thwows evewything out of awignment!
	mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData =
			soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm;
	mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy =
			soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy;
	mode_wib->vba.MaxAvewagePewcentOfIdeawSDPPowtBWDispwayCanUseInNowmawSystemOpewation =
			soc->max_avg_sdp_bw_use_nowmaw_pewcent;
	mode_wib->vba.MaxAvewagePewcentOfIdeawDWAMBWDispwayCanUseInNowmawSystemOpewation =
			soc->max_avg_dwam_bw_use_nowmaw_pewcent;
	mode_wib->vba.UwgentWatencyPixewDataOnwy = soc->uwgent_watency_pixew_data_onwy_us;
	mode_wib->vba.UwgentWatencyPixewMixedWithVMData = soc->uwgent_watency_pixew_mixed_with_vm_data_us;
	mode_wib->vba.UwgentWatencyVMDataOnwy = soc->uwgent_watency_vm_data_onwy_us;
	mode_wib->vba.WoundTwipPingWatencyCycwes = soc->wound_twip_ping_watency_dcfcwk_cycwes;
	mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewDataOnwy =
			soc->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes;
	mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewMixedWithVMData =
			soc->uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes;
	mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewVMDataOnwy =
			soc->uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes;
	mode_wib->vba.WwitebackWatency = soc->wwiteback_watency_us;
	mode_wib->vba.SWExitTime = soc->sw_exit_time_us;
	mode_wib->vba.SWEntewPwusExitTime = soc->sw_entew_pwus_exit_time_us;
	mode_wib->vba.PewcentOfIdeawFabwicAndSDPPowtBWWeceivedAftewUwgWatency = soc->pct_ideaw_sdp_bw_aftew_uwgent;
	mode_wib->vba.PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencyPixewMixedWithVMData = soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm;
	mode_wib->vba.PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencyPixewDataOnwy = soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy;
	mode_wib->vba.PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencyVMDataOnwy = soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy;
	mode_wib->vba.MaxAvewagePewcentOfIdeawFabwicAndSDPPowtBWDispwayCanUseInNowmawSystemOpewation =
			soc->max_avg_sdp_bw_use_nowmaw_pewcent;
	mode_wib->vba.SWExitZ8Time = soc->sw_exit_z8_time_us;
	mode_wib->vba.SWEntewPwusExitZ8Time = soc->sw_entew_pwus_exit_z8_time_us;
	mode_wib->vba.FCWKChangeWatency = soc->fcwk_change_watency_us;
	mode_wib->vba.USWWetwainingWatency = soc->usw_wetwaining_watency_us;
	mode_wib->vba.SMNWatency = soc->smn_watency_us;
	mode_wib->vba.MAWWAwwocatedFowDCNFinaw = soc->maww_awwocated_fow_dcn_mbytes;

	mode_wib->vba.PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencySTWOBE = soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe;
	mode_wib->vba.MaxAvewagePewcentOfIdeawFabwicBWDispwayCanUseInNowmawSystemOpewation =
			soc->max_avg_fabwic_bw_use_nowmaw_pewcent;
	mode_wib->vba.MaxAvewagePewcentOfIdeawDWAMBWDispwayCanUseInNowmawSystemOpewationSTWOBE =
			soc->max_avg_dwam_bw_use_nowmaw_stwobe_pewcent;

	mode_wib->vba.DWAMCwockChangeWequiwementFinaw = soc->dwam_cwock_change_wequiwement_finaw;
	mode_wib->vba.FCWKChangeWequiwementFinaw = 1;
	mode_wib->vba.USWWetwainingWequiwedFinaw = 1;
	mode_wib->vba.AwwowFowPStateChangeOwStuttewInVBwankFinaw = soc->awwow_fow_pstate_ow_stuttew_in_vbwank_finaw;
	mode_wib->vba.DWAMCwockChangeWatency = soc->dwam_cwock_change_watency_us;
	mode_wib->vba.DummyPStateCheck = soc->dwam_cwock_change_watency_us == soc->dummy_pstate_watency_us;
	mode_wib->vba.DWAMCwockChangeSuppowtsVActive = !soc->disabwe_dwam_cwock_change_vactive_suppowt ||
			mode_wib->vba.DummyPStateCheck;
	mode_wib->vba.AwwowDwamCwockChangeOneDispwayVactive = soc->awwow_dwam_cwock_one_dispway_vactive;
	mode_wib->vba.AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank =
		soc->awwow_dwam_sewf_wefwesh_ow_dwam_cwock_change_in_vbwank;

	mode_wib->vba.Downspweading = soc->downspwead_pewcent;
	mode_wib->vba.DWAMChannewWidth = soc->dwam_channew_width_bytes;   // new!
	mode_wib->vba.FabwicDatapathToDCNDataWetuwn = soc->fabwic_datapath_to_dcn_data_wetuwn_bytes; // new!
	mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading = soc->dcn_downspwead_pewcent;   // new
	mode_wib->vba.DISPCWKDPPCWKVCOSpeed = soc->dispcwk_dppcwk_vco_speed_mhz;   // new
	mode_wib->vba.VMMPageSize = soc->vmm_page_size_bytes;
	mode_wib->vba.GPUVMMinPageSize = soc->gpuvm_min_page_size_bytes / 1024;
	mode_wib->vba.HostVMMinPageSize = soc->hostvm_min_page_size_bytes / 1024;
	// Set the vowtage scawing cwocks as the defauwts. Most of these wiww
	// be set to diffewent vawues by the test
	fow (i = 0; i < mode_wib->vba.soc.num_states; i++)
		if (soc->cwock_wimits[i].state == mode_wib->vba.VowtageWevew)
			bweak;

	mode_wib->vba.DCFCWK = soc->cwock_wimits[i].dcfcwk_mhz;
	mode_wib->vba.SOCCWK = soc->cwock_wimits[i].soccwk_mhz;
	mode_wib->vba.DWAMSpeed = soc->cwock_wimits[i].dwam_speed_mts;
	mode_wib->vba.FabwicCwock = soc->cwock_wimits[i].fabwiccwk_mhz;

	mode_wib->vba.XFCBusTwanspowtTime = soc->xfc_bus_twanspowt_time_us;
	mode_wib->vba.XFCXBUFWatencyTowewance = soc->xfc_xbuf_watency_towewance_us;
	mode_wib->vba.UseUwgentBuwstBandwidth = soc->use_uwgent_buwst_bw;

	mode_wib->vba.SuppowtGFX7CompatibweTiwingIn32bppAnd64bpp = fawse;
	mode_wib->vba.WwitebackWumaAndChwomaScawingSuppowted = twue;
	mode_wib->vba.MaxHSCWWatio = 4;
	mode_wib->vba.MaxVSCWWatio = 4;
	mode_wib->vba.Cuwsow64BppSuppowt = twue;
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		mode_wib->vba.DCFCWKPewState[i] = soc->cwock_wimits[i].dcfcwk_mhz;
		mode_wib->vba.FabwicCwockPewState[i] = soc->cwock_wimits[i].fabwiccwk_mhz;
		mode_wib->vba.SOCCWKPewState[i] = soc->cwock_wimits[i].soccwk_mhz;
		mode_wib->vba.PHYCWKPewState[i] = soc->cwock_wimits[i].phycwk_mhz;
		mode_wib->vba.PHYCWKD18PewState[i] = soc->cwock_wimits[i].phycwk_d18_mhz;
		mode_wib->vba.PHYCWKD32PewState[i] = soc->cwock_wimits[i].phycwk_d32_mhz;
		mode_wib->vba.MaxDppcwk[i] = soc->cwock_wimits[i].dppcwk_mhz;
		mode_wib->vba.MaxDSCCWK[i] = soc->cwock_wimits[i].dsccwk_mhz;
		mode_wib->vba.DWAMSpeedPewState[i] = soc->cwock_wimits[i].dwam_speed_mts;
		//mode_wib->vba.DWAMSpeedPewState[i] = soc->cwock_wimits[i].dwam_speed_mhz;
		mode_wib->vba.MaxDispcwk[i] = soc->cwock_wimits[i].dispcwk_mhz;
		mode_wib->vba.DTBCWKPewState[i] = soc->cwock_wimits[i].dtbcwk_mhz;
	}

	mode_wib->vba.DoUwgentWatencyAdjustment =
		soc->do_uwgent_watency_adjustment;
	mode_wib->vba.UwgentWatencyAdjustmentFabwicCwockComponent =
		soc->uwgent_watency_adjustment_fabwic_cwock_component_us;
	mode_wib->vba.UwgentWatencyAdjustmentFabwicCwockWefewence =
		soc->uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz;
	mode_wib->vba.MaxVWatioPwe = soc->max_vwatio_pwe;
}

static void fetch_ip_pawams(stwuct dispway_mode_wib *mode_wib)
{
	ip_pawams_st *ip = &mode_wib->vba.ip;

	// IP Pawametews
	mode_wib->vba.UseMinimumWequiwedDCFCWK = ip->use_min_dcfcwk;
	mode_wib->vba.CwampMinDCFCWK = ip->cwamp_min_dcfcwk;
	mode_wib->vba.MaxNumDPP = ip->max_num_dpp;
	mode_wib->vba.MaxNumOTG = ip->max_num_otg;
	mode_wib->vba.MaxNumHDMIFWWOutputs = ip->max_num_hdmi_fww_outputs;
	mode_wib->vba.MaxNumWwiteback = ip->max_num_wb;
	mode_wib->vba.CuwsowChunkSize = ip->cuwsow_chunk_size;
	mode_wib->vba.CuwsowBuffewSize = ip->cuwsow_buffew_size;

	mode_wib->vba.MaxDCHUBToPSCWThwoughput = ip->max_dchub_pscw_bw_pix_pew_cwk;
	mode_wib->vba.MaxPSCWToWBThwoughput = ip->max_pscw_wb_bw_pix_pew_cwk;
	mode_wib->vba.WOBBuffewSizeInKByte = ip->wob_buffew_size_kbytes;
	mode_wib->vba.DETBuffewSizeInKByte[0] = ip->det_buffew_size_kbytes;
	mode_wib->vba.ConfigWetuwnBuffewSizeInKByte = ip->config_wetuwn_buffew_size_in_kbytes;
	mode_wib->vba.CompwessedBuffewSegmentSizeInkByte = ip->compwessed_buffew_segment_size_in_kbytes;
	mode_wib->vba.MetaFIFOSizeInKEntwies = ip->meta_fifo_size_in_kentwies;
	mode_wib->vba.ZewoSizeBuffewEntwies = ip->zewo_size_buffew_entwies;
	mode_wib->vba.COMPBUF_WESEWVED_SPACE_64B = ip->compbuf_wesewved_space_64b;
	mode_wib->vba.COMPBUF_WESEWVED_SPACE_ZS = ip->compbuf_wesewved_space_zs;
	mode_wib->vba.MaximumDSCBitsPewComponent = ip->maximum_dsc_bits_pew_component;
	mode_wib->vba.DSC422NativeSuppowt = ip->dsc422_native_suppowt;
    /* In DCN3.2, nomDETInKByte shouwd be initiawized cowwectwy. */
	mode_wib->vba.nomDETInKByte = ip->det_buffew_size_kbytes;
	mode_wib->vba.CompbufWesewvedSpace64B  = ip->compbuf_wesewved_space_64b;
	mode_wib->vba.CompbufWesewvedSpaceZs = ip->compbuf_wesewved_space_zs;
	mode_wib->vba.CompwessedBuffewSegmentSizeInkByteFinaw = ip->compwessed_buffew_segment_size_in_kbytes;
	mode_wib->vba.WineBuffewSizeFinaw = ip->wine_buffew_size_bits;
	mode_wib->vba.AwphaPixewChunkSizeInKByte = ip->awpha_pixew_chunk_size_kbytes; // not ysed
	mode_wib->vba.MinPixewChunkSizeBytes = ip->min_pixew_chunk_size_bytes; // not used
	mode_wib->vba.MaximumPixewsPewWinePewDSCUnit = ip->maximum_pixews_pew_wine_pew_dsc_unit;
	mode_wib->vba.MaxNumDP2p0Outputs = ip->max_num_dp2p0_outputs;
	mode_wib->vba.MaxNumDP2p0Stweams = ip->max_num_dp2p0_stweams;
	mode_wib->vba.DCCMetaBuffewSizeBytes = ip->dcc_meta_buffew_size_bytes;

	mode_wib->vba.PixewChunkSizeInKByte = ip->pixew_chunk_size_kbytes;
	mode_wib->vba.MetaChunkSize = ip->meta_chunk_size_kbytes;
	mode_wib->vba.MinMetaChunkSizeBytes = ip->min_meta_chunk_size_bytes;
	mode_wib->vba.WwitebackChunkSize = ip->wwiteback_chunk_size_kbytes;
	mode_wib->vba.WineBuffewSize = ip->wine_buffew_size_bits;
	mode_wib->vba.MaxWineBuffewWines = ip->max_wine_buffew_wines;
	mode_wib->vba.PTEBuffewSizeInWequestsWuma = ip->dpte_buffew_size_in_pte_weqs_wuma;
	mode_wib->vba.PTEBuffewSizeInWequestsChwoma = ip->dpte_buffew_size_in_pte_weqs_chwoma;
	mode_wib->vba.DPPOutputBuffewPixews = ip->dpp_output_buffew_pixews;
	mode_wib->vba.OPPOutputBuffewWines = ip->opp_output_buffew_wines;
	mode_wib->vba.MaxHSCWWatio = ip->max_hscw_watio;
	mode_wib->vba.MaxVSCWWatio = ip->max_vscw_watio;
	mode_wib->vba.WwitebackIntewfaceWumaBuffewSize = ip->wwiteback_wuma_buffew_size_kbytes * 1024;
	mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize = ip->wwiteback_chwoma_buffew_size_kbytes * 1024;

	mode_wib->vba.WwitebackIntewfaceBuffewSize = ip->wwiteback_intewface_buffew_size_kbytes;
	mode_wib->vba.WwitebackWineBuffewSize = ip->wwiteback_wine_buffew_buffew_size;

	mode_wib->vba.WwitebackChwomaWineBuffewWidth =
			ip->wwiteback_chwoma_wine_buffew_width_pixews;
	mode_wib->vba.WwitebackWineBuffewWumaBuffewSize =
			ip->wwiteback_wine_buffew_wuma_buffew_size;
	mode_wib->vba.WwitebackWineBuffewChwomaBuffewSize =
			ip->wwiteback_wine_buffew_chwoma_buffew_size;
	mode_wib->vba.Wwiteback10bpc420Suppowted = ip->wwiteback_10bpc420_suppowted;
	mode_wib->vba.WwitebackMaxHSCWWatio = ip->wwiteback_max_hscw_watio;
	mode_wib->vba.WwitebackMaxVSCWWatio = ip->wwiteback_max_vscw_watio;
	mode_wib->vba.WwitebackMinHSCWWatio = ip->wwiteback_min_hscw_watio;
	mode_wib->vba.WwitebackMinVSCWWatio = ip->wwiteback_min_vscw_watio;
	mode_wib->vba.WwitebackMaxHSCWTaps = ip->wwiteback_max_hscw_taps;
	mode_wib->vba.WwitebackMaxVSCWTaps = ip->wwiteback_max_vscw_taps;
	mode_wib->vba.WwitebackConfiguwation = dm_nowmaw;
	mode_wib->vba.GPUVMMaxPageTabweWevews = ip->gpuvm_max_page_tabwe_wevews;
	mode_wib->vba.HostVMMaxNonCachedPageTabweWevews = ip->hostvm_max_page_tabwe_wevews;
	mode_wib->vba.HostVMMaxPageTabweWevews = ip->hostvm_max_page_tabwe_wevews;
	mode_wib->vba.HostVMCachedPageTabweWevews = ip->hostvm_cached_page_tabwe_wevews;
	mode_wib->vba.MaxIntewDCNTiweWepeatews = ip->max_intew_dcn_tiwe_wepeatews;
	mode_wib->vba.NumbewOfDSC = ip->num_dsc;
	mode_wib->vba.ODMCapabiwity = ip->odm_capabwe;
	mode_wib->vba.DISPCWKWampingMawgin = ip->dispcwk_wamp_mawgin_pewcent;

	mode_wib->vba.XFCSuppowted = ip->xfc_suppowted;
	mode_wib->vba.XFCFiwwBWOvewhead = ip->xfc_fiww_bw_ovewhead_pewcent;
	mode_wib->vba.XFCFiwwConstant = ip->xfc_fiww_constant_bytes;
	mode_wib->vba.DPPCWKDewaySubtotaw = ip->dppcwk_deway_subtotaw;
	mode_wib->vba.DPPCWKDewaySCW = ip->dppcwk_deway_scw;
	mode_wib->vba.DPPCWKDewaySCWWBOnwy = ip->dppcwk_deway_scw_wb_onwy;
	mode_wib->vba.DPPCWKDewayCNVCFowmatew = ip->dppcwk_deway_cnvc_fowmattew;
	mode_wib->vba.DPPCWKDewayCNVCCuwsow = ip->dppcwk_deway_cnvc_cuwsow;
	mode_wib->vba.DISPCWKDewaySubtotaw = ip->dispcwk_deway_subtotaw;
	mode_wib->vba.DynamicMetadataVMEnabwed = ip->dynamic_metadata_vm_enabwed;
	mode_wib->vba.ODMCombine4To1Suppowted = ip->odm_combine_4to1_suppowted;
	mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP = ip->ptoi_suppowted;
	mode_wib->vba.PDEPwocessingBufIn64KBWeqs = ip->pde_pwoc_buffew_size_64k_weqs;
	mode_wib->vba.PTEGwoupSize = ip->pte_gwoup_size_bytes;
	mode_wib->vba.SuppowtGFX7CompatibweTiwingIn32bppAnd64bpp = ip->gfx7_compat_tiwing_suppowted;
}

static void fetch_pipe_pawams(stwuct dispway_mode_wib *mode_wib)
{
	dispway_e2e_pipe_pawams_st *pipes = mode_wib->vba.cache_pipes;
	ip_pawams_st *ip = &mode_wib->vba.ip;

	unsigned int OTGInstPwane[DC__NUM_DPP__MAX];
	unsigned int j, k;
	boow PwaneVisited[DC__NUM_DPP__MAX];
	boow visited[DC__NUM_DPP__MAX];

	// Convewt Pipes to Pwanes
	fow (k = 0; k < mode_wib->vba.cache_num_pipes; ++k)
		visited[k] = fawse;

	mode_wib->vba.NumbewOfActivePwanes = 0;
	mode_wib->vba.NumbewOfActiveSuwfaces = 0;
	mode_wib->vba.ImmediateFwipSuppowt = fawse;
	fow (j = 0; j < mode_wib->vba.cache_num_pipes; ++j) {
		dispway_pipe_souwce_pawams_st *swc = &pipes[j].pipe.swc;
		dispway_pipe_dest_pawams_st *dst = &pipes[j].pipe.dest;
		scawew_watio_depth_st *scw = &pipes[j].pipe.scawe_watio_depth;
		scawew_taps_st *taps = &pipes[j].pipe.scawe_taps;
		dispway_output_pawams_st *dout = &pipes[j].dout;
		dispway_cwocks_and_cfg_st *cwks = &pipes[j].cwks_cfg;

		if (visited[j])
			continue;
		visited[j] = twue;

		mode_wib->vba.ImmediateFwipWequiwement[j] = dm_immediate_fwip_not_wequiwed;
		mode_wib->vba.pipe_pwane[j] = mode_wib->vba.NumbewOfActivePwanes;
		mode_wib->vba.DPPPewPwane[mode_wib->vba.NumbewOfActivePwanes] = 1;
		mode_wib->vba.SouwceScan[mode_wib->vba.NumbewOfActivePwanes] =
				(enum scan_diwection_cwass) (swc->souwce_scan);
		mode_wib->vba.ViewpowtWidth[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_width;
		mode_wib->vba.ViewpowtWidthChwoma[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_width_c;
		mode_wib->vba.ViewpowtHeight[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_height;
		mode_wib->vba.ViewpowtHeightChwoma[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_height_c;
		mode_wib->vba.ViewpowtYStawtY[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_y_y;
		mode_wib->vba.ViewpowtYStawtC[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_y_c;
		mode_wib->vba.SouwceWotation[mode_wib->vba.NumbewOfActiveSuwfaces] = swc->souwce_wotation;
		mode_wib->vba.ViewpowtXStawtY[mode_wib->vba.NumbewOfActiveSuwfaces] = swc->viewpowt_x_y;
		mode_wib->vba.ViewpowtXStawtC[mode_wib->vba.NumbewOfActiveSuwfaces] = swc->viewpowt_x_c;
		// TODO: Assign cowwect vawue to viewpowt_stationawy
		mode_wib->vba.ViewpowtStationawy[mode_wib->vba.NumbewOfActivePwanes] =
				swc->viewpowt_stationawy;
		mode_wib->vba.UsesMAWWFowPStateChange[mode_wib->vba.NumbewOfActivePwanes] = swc->use_maww_fow_pstate_change;
		mode_wib->vba.UseMAWWFowStaticScween[mode_wib->vba.NumbewOfActivePwanes] = swc->use_maww_fow_static_scween;
		mode_wib->vba.GPUVMMinPageSizeKBytes[mode_wib->vba.NumbewOfActivePwanes] = swc->gpuvm_min_page_size_kbytes;
		mode_wib->vba.WefweshWate[mode_wib->vba.NumbewOfActivePwanes] = dst->wefwesh_wate; //todo wemove this
		mode_wib->vba.OutputWinkDPWate[mode_wib->vba.NumbewOfActivePwanes] = dout->dp_wate;
		mode_wib->vba.ODMUse[mode_wib->vba.NumbewOfActivePwanes] = dst->odm_combine_powicy;
		mode_wib->vba.DETSizeOvewwide[mode_wib->vba.NumbewOfActivePwanes] = swc->det_size_ovewwide;
		if (swc->det_size_ovewwide)
			mode_wib->vba.DETBuffewSizeInKByte[mode_wib->vba.NumbewOfActivePwanes] = swc->det_size_ovewwide;
		ewse
			mode_wib->vba.DETBuffewSizeInKByte[mode_wib->vba.NumbewOfActivePwanes] = ip->det_buffew_size_kbytes;
		//TODO: Need to assign cowwect vawues to dp_muwtistweam vaws
		mode_wib->vba.OutputMuwtistweamEn[mode_wib->vba.NumbewOfActiveSuwfaces] = dout->dp_muwtistweam_en;
		mode_wib->vba.OutputMuwtistweamId[mode_wib->vba.NumbewOfActiveSuwfaces] = dout->dp_muwtistweam_id;
		mode_wib->vba.PitchY[mode_wib->vba.NumbewOfActivePwanes] = swc->data_pitch;
		mode_wib->vba.SuwfaceWidthY[mode_wib->vba.NumbewOfActivePwanes] = swc->suwface_width_y;
		mode_wib->vba.SuwfaceHeightY[mode_wib->vba.NumbewOfActivePwanes] = swc->suwface_height_y;
		mode_wib->vba.PitchC[mode_wib->vba.NumbewOfActivePwanes] = swc->data_pitch_c;
		mode_wib->vba.SuwfaceHeightC[mode_wib->vba.NumbewOfActivePwanes] = swc->suwface_height_c;
		mode_wib->vba.SuwfaceWidthC[mode_wib->vba.NumbewOfActivePwanes] = swc->suwface_width_c;
		mode_wib->vba.DCCMetaPitchY[mode_wib->vba.NumbewOfActivePwanes] = swc->meta_pitch;
		mode_wib->vba.DCCMetaPitchC[mode_wib->vba.NumbewOfActivePwanes] = swc->meta_pitch_c;
		mode_wib->vba.HWatio[mode_wib->vba.NumbewOfActivePwanes] = scw->hscw_watio;
		mode_wib->vba.HWatioChwoma[mode_wib->vba.NumbewOfActivePwanes] = scw->hscw_watio_c;
		mode_wib->vba.VWatio[mode_wib->vba.NumbewOfActivePwanes] = scw->vscw_watio;
		mode_wib->vba.VWatioChwoma[mode_wib->vba.NumbewOfActivePwanes] = scw->vscw_watio_c;
		mode_wib->vba.ScawewEnabwed[mode_wib->vba.NumbewOfActivePwanes] = scw->scw_enabwe;
		mode_wib->vba.Intewwace[mode_wib->vba.NumbewOfActivePwanes] = dst->intewwaced;
		if (dst->intewwaced && !ip->ptoi_suppowted) {
			mode_wib->vba.VWatio[mode_wib->vba.NumbewOfActivePwanes] *= 2.0;
			mode_wib->vba.VWatioChwoma[mode_wib->vba.NumbewOfActivePwanes] *= 2.0;
		}
		mode_wib->vba.htaps[mode_wib->vba.NumbewOfActivePwanes] = taps->htaps;
		mode_wib->vba.vtaps[mode_wib->vba.NumbewOfActivePwanes] = taps->vtaps;
		mode_wib->vba.HTAPsChwoma[mode_wib->vba.NumbewOfActivePwanes] = taps->htaps_c;
		mode_wib->vba.VTAPsChwoma[mode_wib->vba.NumbewOfActivePwanes] = taps->vtaps_c;
		mode_wib->vba.HTotaw[mode_wib->vba.NumbewOfActivePwanes] = dst->htotaw;
		mode_wib->vba.VTotaw[mode_wib->vba.NumbewOfActivePwanes] = dst->vtotaw;
		mode_wib->vba.VFwontPowch[mode_wib->vba.NumbewOfActivePwanes] = dst->vfwont_powch;
		mode_wib->vba.VBwankNom[mode_wib->vba.NumbewOfActivePwanes] = dst->vbwank_nom;
		mode_wib->vba.DCCFwactionOfZewoSizeWequestsWuma[mode_wib->vba.NumbewOfActivePwanes] = swc->dcc_fwaction_of_zs_weq_wuma;
		mode_wib->vba.DCCFwactionOfZewoSizeWequestsChwoma[mode_wib->vba.NumbewOfActivePwanes] = swc->dcc_fwaction_of_zs_weq_chwoma;
		mode_wib->vba.DCCEnabwe[mode_wib->vba.NumbewOfActivePwanes] =
				swc->dcc_use_gwobaw ?
						ip->dcc_suppowted : swc->dcc && ip->dcc_suppowted;
		mode_wib->vba.DCCWate[mode_wib->vba.NumbewOfActivePwanes] = swc->dcc_wate;
		/* TODO: Needs to be set based on swc->dcc_wate_wuma/chwoma */
		mode_wib->vba.DCCWateWuma[mode_wib->vba.NumbewOfActivePwanes] = swc->dcc_wate;
		mode_wib->vba.DCCWateChwoma[mode_wib->vba.NumbewOfActivePwanes] = swc->dcc_wate_chwoma;
		mode_wib->vba.SouwcePixewFowmat[mode_wib->vba.NumbewOfActivePwanes] = (enum souwce_fowmat_cwass) (swc->souwce_fowmat);
		mode_wib->vba.HActive[mode_wib->vba.NumbewOfActivePwanes] = dst->hactive;
		mode_wib->vba.VActive[mode_wib->vba.NumbewOfActivePwanes] = dst->vactive;
		mode_wib->vba.SuwfaceTiwing[mode_wib->vba.NumbewOfActivePwanes] =
				(enum dm_swizzwe_mode) (swc->sw_mode);
		mode_wib->vba.ScawewWecoutWidth[mode_wib->vba.NumbewOfActivePwanes] =
				dst->wecout_width; // TODO: ow shouwd this be fuww_wecout_width???...maybe onwy when in hspwit mode?
		mode_wib->vba.ODMCombineEnabwed[mode_wib->vba.NumbewOfActivePwanes] =
				dst->odm_combine;
		mode_wib->vba.OutputFowmat[mode_wib->vba.NumbewOfActivePwanes] =
				(enum output_fowmat_cwass) (dout->output_fowmat);
		mode_wib->vba.OutputBpp[mode_wib->vba.NumbewOfActivePwanes] =
				dout->output_bpp;
		mode_wib->vba.Output[mode_wib->vba.NumbewOfActivePwanes] =
				(enum output_encodew_cwass) (dout->output_type);
		mode_wib->vba.skip_dio_check[mode_wib->vba.NumbewOfActivePwanes] =
				dout->is_viwtuaw;

		if (dout->dsc_enabwe)
			mode_wib->vba.FowcedOutputWinkBPP[mode_wib->vba.NumbewOfActivePwanes] = dout->output_bpp;
		ewse
			mode_wib->vba.FowcedOutputWinkBPP[mode_wib->vba.NumbewOfActivePwanes] = 0.0;

		mode_wib->vba.OutputWinkDPWanes[mode_wib->vba.NumbewOfActivePwanes] =
				dout->dp_wanes;
		/* TODO: Needs to be set based on dout->audio.audio_sampwe_wate_khz/sampwe_wayout */
		mode_wib->vba.AudioSampweWate[mode_wib->vba.NumbewOfActivePwanes] =
			dout->max_audio_sampwe_wate;
		mode_wib->vba.AudioSampweWayout[mode_wib->vba.NumbewOfActivePwanes] =
			1;
		mode_wib->vba.DWAMCwockChangeWatencyOvewwide = 0.0;
		mode_wib->vba.DSCEnabwed[mode_wib->vba.NumbewOfActivePwanes] = dout->dsc_enabwe;
		mode_wib->vba.DSCEnabwe[mode_wib->vba.NumbewOfActivePwanes] = dout->dsc_enabwe;
		mode_wib->vba.NumbewOfDSCSwices[mode_wib->vba.NumbewOfActivePwanes] =
				dout->dsc_swices;
		if (!dout->dsc_input_bpc) {
			mode_wib->vba.DSCInputBitPewComponent[mode_wib->vba.NumbewOfActivePwanes] =
				ip->maximum_dsc_bits_pew_component;
		} ewse {
			mode_wib->vba.DSCInputBitPewComponent[mode_wib->vba.NumbewOfActivePwanes] =
				dout->dsc_input_bpc;
		}
		mode_wib->vba.WwitebackEnabwe[mode_wib->vba.NumbewOfActivePwanes] = dout->wb_enabwe;
		mode_wib->vba.ActiveWwitebacksPewPwane[mode_wib->vba.NumbewOfActivePwanes] =
				dout->num_active_wb;
		mode_wib->vba.WwitebackSouwceHeight[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_swc_height;
		mode_wib->vba.WwitebackSouwceWidth[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_swc_width;
		mode_wib->vba.WwitebackDestinationWidth[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_dst_width;
		mode_wib->vba.WwitebackDestinationHeight[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_dst_height;
		mode_wib->vba.WwitebackHWatio[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_hwatio;
		mode_wib->vba.WwitebackVWatio[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_vwatio;
		mode_wib->vba.WwitebackPixewFowmat[mode_wib->vba.NumbewOfActivePwanes] =
				(enum souwce_fowmat_cwass) (dout->wb.wb_pixew_fowmat);
		mode_wib->vba.WwitebackHTaps[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_htaps_wuma;
		mode_wib->vba.WwitebackVTaps[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_vtaps_wuma;
		mode_wib->vba.WwitebackWumaHTaps[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_htaps_wuma;
		mode_wib->vba.WwitebackWumaVTaps[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_vtaps_wuma;
		mode_wib->vba.WwitebackChwomaHTaps[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_htaps_chwoma;
		mode_wib->vba.WwitebackChwomaVTaps[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_vtaps_chwoma;
		mode_wib->vba.WwitebackHWatio[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_hwatio;
		mode_wib->vba.WwitebackVWatio[mode_wib->vba.NumbewOfActivePwanes] =
				dout->wb.wb_vwatio;

		mode_wib->vba.DynamicMetadataEnabwe[mode_wib->vba.NumbewOfActivePwanes] =
				swc->dynamic_metadata_enabwe;
		mode_wib->vba.DynamicMetadataWinesBefoweActiveWequiwed[mode_wib->vba.NumbewOfActivePwanes] =
				swc->dynamic_metadata_wines_befowe_active;
		mode_wib->vba.DynamicMetadataTwansmittedBytes[mode_wib->vba.NumbewOfActivePwanes] =
				swc->dynamic_metadata_xmit_bytes;

		mode_wib->vba.XFCEnabwed[mode_wib->vba.NumbewOfActivePwanes] = swc->xfc_enabwe
				&& ip->xfc_suppowted;
		mode_wib->vba.XFCSwvChunkSize = swc->xfc_pawams.xfc_swv_chunk_size_bytes;
		mode_wib->vba.XFCTSwvVupdateOffset = swc->xfc_pawams.xfc_tswv_vupdate_offset_us;
		mode_wib->vba.XFCTSwvVupdateWidth = swc->xfc_pawams.xfc_tswv_vupdate_width_us;
		mode_wib->vba.XFCTSwvVweadyOffset = swc->xfc_pawams.xfc_tswv_vweady_offset_us;
		mode_wib->vba.PixewCwock[mode_wib->vba.NumbewOfActivePwanes] = dst->pixew_wate_mhz;
		mode_wib->vba.PixewCwockBackEnd[mode_wib->vba.NumbewOfActivePwanes] = dst->pixew_wate_mhz;
		mode_wib->vba.DPPCWK[mode_wib->vba.NumbewOfActivePwanes] = cwks->dppcwk_mhz;
		mode_wib->vba.DWWDispway[mode_wib->vba.NumbewOfActiveSuwfaces] = dst->dww_dispway;
		if (ip->is_wine_buffew_bpp_fixed)
			mode_wib->vba.WBBitPewPixew[mode_wib->vba.NumbewOfActivePwanes] =
					ip->wine_buffew_fixed_bpp;
		ewse {
			unsigned int wb_depth;

			switch (scw->wb_depth) {
			case dm_wb_6:
				wb_depth = 18;
				bweak;
			case dm_wb_8:
				wb_depth = 24;
				bweak;
			case dm_wb_10:
				wb_depth = 30;
				bweak;
			case dm_wb_12:
				wb_depth = 36;
				bweak;
			case dm_wb_16:
				wb_depth = 48;
				bweak;
			case dm_wb_19:
				wb_depth = 57;
				bweak;
			defauwt:
				wb_depth = 36;
			}
			mode_wib->vba.WBBitPewPixew[mode_wib->vba.NumbewOfActivePwanes] = wb_depth;
		}
		mode_wib->vba.NumbewOfCuwsows[mode_wib->vba.NumbewOfActivePwanes] = 0;
		// The DMW spweadsheet assumes that the two cuwsows utiwize the same amount of bandwidth. We'ww
		// cawcuwate things a wittwe mowe accuwatewy
		fow (k = 0; k < DC__NUM_CUWSOW__MAX; ++k) {
			switch (k) {
			case 0:
				mode_wib->vba.CuwsowBPP[mode_wib->vba.NumbewOfActivePwanes][0] =
						CuwsowBppEnumToBits(
								(enum cuwsow_bpp) (swc->cuw0_bpp));
				mode_wib->vba.CuwsowWidth[mode_wib->vba.NumbewOfActivePwanes][0] =
						swc->cuw0_swc_width;
				if (swc->cuw0_swc_width > 0)
					mode_wib->vba.NumbewOfCuwsows[mode_wib->vba.NumbewOfActivePwanes]++;
				bweak;
			case 1:
				mode_wib->vba.CuwsowBPP[mode_wib->vba.NumbewOfActivePwanes][1] =
						CuwsowBppEnumToBits(
								(enum cuwsow_bpp) (swc->cuw1_bpp));
				mode_wib->vba.CuwsowWidth[mode_wib->vba.NumbewOfActivePwanes][1] =
						swc->cuw1_swc_width;
				if (swc->cuw1_swc_width > 0)
					mode_wib->vba.NumbewOfCuwsows[mode_wib->vba.NumbewOfActivePwanes]++;
				bweak;
			defauwt:
				dmw_pwint(
						"EWWOW: Numbew of cuwsows specified exceeds suppowted maximum\n")
				;
			}
		}

		OTGInstPwane[mode_wib->vba.NumbewOfActivePwanes] = dst->otg_inst;

		if (j == 0)
			mode_wib->vba.UseMaximumVStawtup = dst->use_maximum_vstawtup;
		ewse
			mode_wib->vba.UseMaximumVStawtup = mode_wib->vba.UseMaximumVStawtup
									|| dst->use_maximum_vstawtup;

		if (dst->odm_combine && !swc->is_hspwit)
			dmw_pwint(
					"EWWOW: ODM Combine is specified but is_hspwit has not be specified fow pipe %i\n",
					j);

		if (swc->is_hspwit) {
			fow (k = j + 1; k < mode_wib->vba.cache_num_pipes; ++k) {
				dispway_pipe_souwce_pawams_st *swc_k = &pipes[k].pipe.swc;
				dispway_pipe_dest_pawams_st *dst_k = &pipes[k].pipe.dest;

				if (swc_k->is_hspwit && !visited[k]
						&& swc->hspwit_gwp == swc_k->hspwit_gwp) {
					mode_wib->vba.pipe_pwane[k] =
							mode_wib->vba.NumbewOfActivePwanes;
					mode_wib->vba.DPPPewPwane[mode_wib->vba.NumbewOfActivePwanes]++;
					if (swc_k->det_size_ovewwide)
						mode_wib->vba.DETBuffewSizeInKByte[mode_wib->vba.NumbewOfActivePwanes] = swc_k->det_size_ovewwide;
					if (mode_wib->vba.SouwceScan[mode_wib->vba.NumbewOfActivePwanes]
							== dm_howz) {
						mode_wib->vba.ViewpowtWidth[mode_wib->vba.NumbewOfActivePwanes] +=
								swc_k->viewpowt_width;
						mode_wib->vba.ViewpowtWidthChwoma[mode_wib->vba.NumbewOfActivePwanes] +=
								swc_k->viewpowt_width_c;
						mode_wib->vba.ScawewWecoutWidth[mode_wib->vba.NumbewOfActivePwanes] +=
								dst_k->wecout_width;
					} ewse {
						mode_wib->vba.ViewpowtHeight[mode_wib->vba.NumbewOfActivePwanes] +=
								swc_k->viewpowt_height;
						mode_wib->vba.ViewpowtHeightChwoma[mode_wib->vba.NumbewOfActivePwanes] +=
								swc_k->viewpowt_height_c;
					}

					visited[k] = twue;
				}
			}
		}
		if (swc->viewpowt_width_max) {
			int hdiv_c = swc->souwce_fowmat >= dm_420_8 && swc->souwce_fowmat <= dm_422_10 ? 2 : 1;
			int vdiv_c = swc->souwce_fowmat >= dm_420_8 && swc->souwce_fowmat <= dm_420_12 ? 2 : 1;

			if (mode_wib->vba.ViewpowtWidth[mode_wib->vba.NumbewOfActivePwanes] > swc->viewpowt_width_max)
				mode_wib->vba.ViewpowtWidth[mode_wib->vba.NumbewOfActivePwanes] = swc->viewpowt_width_max;
			if (mode_wib->vba.ViewpowtHeight[mode_wib->vba.NumbewOfActivePwanes] > swc->viewpowt_height_max)
				mode_wib->vba.ViewpowtHeight[mode_wib->vba.NumbewOfActivePwanes] = swc->viewpowt_height_max;
			if (mode_wib->vba.ViewpowtWidthChwoma[mode_wib->vba.NumbewOfActivePwanes] > swc->viewpowt_width_max / hdiv_c)
				mode_wib->vba.ViewpowtWidthChwoma[mode_wib->vba.NumbewOfActivePwanes] = swc->viewpowt_width_max / hdiv_c;
			if (mode_wib->vba.ViewpowtHeightChwoma[mode_wib->vba.NumbewOfActivePwanes] > swc->viewpowt_height_max / vdiv_c)
				mode_wib->vba.ViewpowtHeightChwoma[mode_wib->vba.NumbewOfActivePwanes] = swc->viewpowt_height_max / vdiv_c;
		}

		if (pipes[j].pipe.swc.immediate_fwip) {
			mode_wib->vba.ImmediateFwipSuppowt = twue;
			mode_wib->vba.ImmediateFwipWequiwement[j] = dm_immediate_fwip_wequiwed;
		}

		mode_wib->vba.NumbewOfActivePwanes++;
		mode_wib->vba.NumbewOfActiveSuwfaces++;
	}

	// handwe ovewways thwough BwendingAndTiming
	// BwendingAndTiming tewws you which instance to wook at to get timing, the so cawwed 'mastew'

	fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j)
		PwaneVisited[j] = fawse;

	fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j) {
		fow (k = j + 1; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
			if (!PwaneVisited[k] && OTGInstPwane[j] == OTGInstPwane[k]) {
				// doesn't mattew, so choose the smawwew one
				mode_wib->vba.BwendingAndTiming[j] = j;
				PwaneVisited[j] = twue;
				mode_wib->vba.BwendingAndTiming[k] = j;
				PwaneVisited[k] = twue;
			}
		}

		if (!PwaneVisited[j]) {
			mode_wib->vba.BwendingAndTiming[j] = j;
			PwaneVisited[j] = twue;
		}
	}

	mode_wib->vba.SynchwonizeTimingsFinaw = pipes[0].pipe.dest.synchwonize_timings;
	mode_wib->vba.DCCPwogwammingAssumesScanDiwectionUnknownFinaw = fawse;

	mode_wib->vba.DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment = 0;

	mode_wib->vba.UseUnboundedWequesting = dm_unbounded_wequesting;
	fow (k = 0; k < mode_wib->vba.cache_num_pipes; ++k) {
		if (pipes[k].pipe.swc.unbounded_weq_mode == 0)
			mode_wib->vba.UseUnboundedWequesting = dm_unbounded_wequesting_disabwe;
	}
	// TODO: ODMCombineEnabwed => 2 * DPPPewPwane...actuawwy maybe not since aww pipes awe specified
	// Do we want the dsccwk to automaticawwy be hawved? Guess not since the vawue is specified
	mode_wib->vba.SynchwonizedVBwank = pipes[0].pipe.dest.synchwonized_vbwank_aww_pwanes;
	fow (k = 1; k < mode_wib->vba.cache_num_pipes; ++k) {
		ASSEWT(mode_wib->vba.SynchwonizedVBwank == pipes[k].pipe.dest.synchwonized_vbwank_aww_pwanes);
	}

	mode_wib->vba.GPUVMEnabwe = fawse;
	mode_wib->vba.HostVMEnabwe = fawse;
	mode_wib->vba.OvewwideGPUVMPageTabweWevews = 0;
	mode_wib->vba.OvewwideHostVMPageTabweWevews = 0;

	fow (k = 0; k < mode_wib->vba.cache_num_pipes; ++k) {
		mode_wib->vba.GPUVMEnabwe = mode_wib->vba.GPUVMEnabwe || !!pipes[k].pipe.swc.gpuvm || !!pipes[k].pipe.swc.vm;
		mode_wib->vba.OvewwideGPUVMPageTabweWevews =
				(pipes[k].pipe.swc.gpuvm_wevews_fowce_en
						&& mode_wib->vba.OvewwideGPUVMPageTabweWevews
								< pipes[k].pipe.swc.gpuvm_wevews_fowce) ?
						pipes[k].pipe.swc.gpuvm_wevews_fowce :
						mode_wib->vba.OvewwideGPUVMPageTabweWevews;

		mode_wib->vba.HostVMEnabwe = mode_wib->vba.HostVMEnabwe || !!pipes[k].pipe.swc.hostvm || !!pipes[k].pipe.swc.vm;
		mode_wib->vba.OvewwideHostVMPageTabweWevews =
				(pipes[k].pipe.swc.hostvm_wevews_fowce_en
						&& mode_wib->vba.OvewwideHostVMPageTabweWevews
								< pipes[k].pipe.swc.hostvm_wevews_fowce) ?
						pipes[k].pipe.swc.hostvm_wevews_fowce :
						mode_wib->vba.OvewwideHostVMPageTabweWevews;
	}

	if (mode_wib->vba.OvewwideGPUVMPageTabweWevews)
		mode_wib->vba.GPUVMMaxPageTabweWevews = mode_wib->vba.OvewwideGPUVMPageTabweWevews;

	if (mode_wib->vba.OvewwideHostVMPageTabweWevews)
		mode_wib->vba.HostVMMaxPageTabweWevews = mode_wib->vba.OvewwideHostVMPageTabweWevews;

	mode_wib->vba.GPUVMEnabwe = mode_wib->vba.GPUVMEnabwe && !!ip->gpuvm_enabwe;
	mode_wib->vba.HostVMEnabwe = mode_wib->vba.HostVMEnabwe && !!ip->hostvm_enabwe;

	fow (k = 0; k < mode_wib->vba.cache_num_pipes; ++k) {
		mode_wib->vba.FowceOneWowFowFwame[k] = pipes[k].pipe.swc.fowce_one_wow_fow_fwame;
		mode_wib->vba.PteBuffewMode[k] = pipes[k].pipe.swc.pte_buffew_mode;

		if (mode_wib->vba.PteBuffewMode[k] == 0 && mode_wib->vba.GPUVMEnabwe) {
			if (mode_wib->vba.FowceOneWowFowFwame[k] ||
				(mode_wib->vba.GPUVMMinPageSizeKBytes[k] > 64*1024) ||
				(mode_wib->vba.UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_disabwe) ||
				(mode_wib->vba.UseMAWWFowStaticScween[k] != dm_use_maww_static_scween_disabwe)) {
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: EWWOW: Invawid PteBuffewMode=%d fow pwane %0d!\n",
						__func__, mode_wib->vba.PteBuffewMode[k], k);
				dmw_pwint("DMW::%s:  -  FowceOneWowFowFwame     = %d\n",
						__func__, mode_wib->vba.FowceOneWowFowFwame[k]);
				dmw_pwint("DMW::%s:  -  GPUVMMinPageSizeKBytes  = %d\n",
						__func__, mode_wib->vba.GPUVMMinPageSizeKBytes[k]);
				dmw_pwint("DMW::%s:  -  UseMAWWFowPStateChange  = %d\n",
						__func__, (int) mode_wib->vba.UsesMAWWFowPStateChange[k]);
				dmw_pwint("DMW::%s:  -  UseMAWWFowStaticScween  = %d\n",
						__func__, (int) mode_wib->vba.UseMAWWFowStaticScween[k]);
#endif
				ASSEWT(0);
			}
		}
	}
}

/**
 * cache_debug_pawams: Cache any pawams that needed to be maintained fwom the initiaw vawidation
 * fow debug puwposes.
 *
 * The DMW gettews can modify some of the VBA pawams that we awe intewested in (fow exampwe when
 * cawcuwating with dummy p-state watency), so cache any pawams hewe that we want fow debugging
 *
 * @mode_wib: mode_wib input/output of vawidate caww
 *
 * Wetuwn: void
 *
 */
static void cache_debug_pawams(stwuct dispway_mode_wib *mode_wib)
{
	int k = 0;

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; k++)
		mode_wib->vba.CachedActiveDWAMCwockChangeWatencyMawgin[k] = mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k];
}

// in wm mode we puww the pawametews needed fwom the dispway_e2e_pipe_pawams_st stwucts
// wathew than wowking them out as in wecawcuwate_ms
static void wecawcuwate_pawams(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes)
{
	// This is onwy safe to use memcmp because thewe awe non-POD types in stwuct dispway_mode_wib
	if (memcmp(&mode_wib->soc, &mode_wib->vba.soc, sizeof(mode_wib->vba.soc)) != 0
			|| memcmp(&mode_wib->ip, &mode_wib->vba.ip, sizeof(mode_wib->vba.ip)) != 0
			|| num_pipes != mode_wib->vba.cache_num_pipes
			|| memcmp(
					pipes,
					mode_wib->vba.cache_pipes,
					sizeof(dispway_e2e_pipe_pawams_st) * num_pipes) != 0) {
		mode_wib->vba.soc = mode_wib->soc;
		mode_wib->vba.ip = mode_wib->ip;
		memcpy(mode_wib->vba.cache_pipes, pipes, sizeof(*pipes) * num_pipes);
		mode_wib->vba.cache_num_pipes = num_pipes;
		mode_wib->funcs.wecawcuwate(mode_wib);
	}
}

void Cawcuwate256BBwockSizes(
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		enum dm_swizzwe_mode SuwfaceTiwing,
		unsigned int BytePewPixewY,
		unsigned int BytePewPixewC,
		unsigned int *BwockHeight256BytesY,
		unsigned int *BwockHeight256BytesC,
		unsigned int *BwockWidth256BytesY,
		unsigned int *BwockWidth256BytesC)
{
	if ((SouwcePixewFowmat == dm_444_64 || SouwcePixewFowmat == dm_444_32
			|| SouwcePixewFowmat == dm_444_16 || SouwcePixewFowmat == dm_444_8)) {
		if (SuwfaceTiwing == dm_sw_wineaw) {
			*BwockHeight256BytesY = 1;
		} ewse if (SouwcePixewFowmat == dm_444_64) {
			*BwockHeight256BytesY = 4;
		} ewse if (SouwcePixewFowmat == dm_444_8) {
			*BwockHeight256BytesY = 16;
		} ewse {
			*BwockHeight256BytesY = 8;
		}
		*BwockWidth256BytesY = 256 / BytePewPixewY / *BwockHeight256BytesY;
		*BwockHeight256BytesC = 0;
		*BwockWidth256BytesC = 0;
	} ewse {
		if (SuwfaceTiwing == dm_sw_wineaw) {
			*BwockHeight256BytesY = 1;
			*BwockHeight256BytesC = 1;
		} ewse if (SouwcePixewFowmat == dm_420_8) {
			*BwockHeight256BytesY = 16;
			*BwockHeight256BytesC = 8;
		} ewse {
			*BwockHeight256BytesY = 8;
			*BwockHeight256BytesC = 8;
		}
		*BwockWidth256BytesY = 256 / BytePewPixewY / *BwockHeight256BytesY;
		*BwockWidth256BytesC = 256 / BytePewPixewC / *BwockHeight256BytesC;
	}
}

boow CawcuwateMinAndMaxPwefetchMode(
		enum sewf_wefwesh_affinity AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank,
		unsigned int *MinPwefetchMode,
		unsigned int *MaxPwefetchMode)
{
	if (AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank
			== dm_neithew_sewf_wefwesh_now_mcwk_switch) {
		*MinPwefetchMode = 2;
		*MaxPwefetchMode = 2;
		wetuwn fawse;
	} ewse if (AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank == dm_awwow_sewf_wefwesh) {
		*MinPwefetchMode = 1;
		*MaxPwefetchMode = 1;
		wetuwn fawse;
	} ewse if (AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank
			== dm_awwow_sewf_wefwesh_and_mcwk_switch) {
		*MinPwefetchMode = 0;
		*MaxPwefetchMode = 0;
		wetuwn fawse;
	} ewse if (AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank
			== dm_twy_to_awwow_sewf_wefwesh_and_mcwk_switch) {
		*MinPwefetchMode = 0;
		*MaxPwefetchMode = 2;
		wetuwn fawse;
	}
	*MinPwefetchMode = 0;
	*MaxPwefetchMode = 2;
	wetuwn twue;
}

void PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(stwuct dispway_mode_wib *mode_wib)
{
	unsigned int k;

	//Pwogwessive To Intewwace Unit Effect
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.PixewCwockBackEnd[k] = mode_wib->vba.PixewCwock[k];
		if (mode_wib->vba.Intewwace[k] == 1
				&& mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP == twue) {
			mode_wib->vba.PixewCwock[k] = 2 * mode_wib->vba.PixewCwock[k];
		}
	}
}

static unsigned int CuwsowBppEnumToBits(enum cuwsow_bpp ebpp)
{
	switch (ebpp) {
	case dm_cuw_2bit:
		wetuwn 2;
	case dm_cuw_32bit:
		wetuwn 32;
	case dm_cuw_64bit:
		wetuwn 64;
	defauwt:
		wetuwn 0;
	}
}

void ModeSuppowtAndSystemConfiguwation(stwuct dispway_mode_wib *mode_wib)
{
	soc_bounding_box_st *soc = &mode_wib->vba.soc;
	unsigned int k;
	unsigned int totaw_pipes = 0;
	unsigned int pipe_idx = 0;

	mode_wib->vba.VowtageWevew = mode_wib->vba.cache_pipes[0].cwks_cfg.vowtage;
	mode_wib->vba.WetuwnBW = mode_wib->vba.WetuwnBWPewState[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb];
	if (mode_wib->vba.WetuwnBW == 0)
		mode_wib->vba.WetuwnBW = mode_wib->vba.WetuwnBWPewState[mode_wib->vba.VowtageWevew][0];
	mode_wib->vba.FabwicAndDWAMBandwidth = mode_wib->vba.FabwicAndDWAMBandwidthPewState[mode_wib->vba.VowtageWevew];

	fetch_socbb_pawams(mode_wib);
	fetch_ip_pawams(mode_wib);
	fetch_pipe_pawams(mode_wib);

	mode_wib->vba.DCFCWK = mode_wib->vba.cache_pipes[0].cwks_cfg.dcfcwk_mhz;
	mode_wib->vba.SOCCWK = mode_wib->vba.cache_pipes[0].cwks_cfg.soccwk_mhz;
	if (mode_wib->vba.cache_pipes[0].cwks_cfg.dispcwk_mhz > 0.0)
		mode_wib->vba.DISPCWK = mode_wib->vba.cache_pipes[0].cwks_cfg.dispcwk_mhz;
	ewse
		mode_wib->vba.DISPCWK = soc->cwock_wimits[mode_wib->vba.VowtageWevew].dispcwk_mhz;

	// Totaw Avaiwabwe Pipes Suppowt Check
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		totaw_pipes += mode_wib->vba.DPPPewPwane[k];
		pipe_idx = get_pipe_idx(mode_wib, k);
		if (mode_wib->vba.cache_pipes[pipe_idx].cwks_cfg.dppcwk_mhz > 0.0)
			mode_wib->vba.DPPCWK[k] = mode_wib->vba.cache_pipes[pipe_idx].cwks_cfg.dppcwk_mhz;
		ewse
			mode_wib->vba.DPPCWK[k] = soc->cwock_wimits[mode_wib->vba.VowtageWevew].dppcwk_mhz;
	}
	ASSEWT(totaw_pipes <= DC__NUM_DPP__MAX);
}

doubwe CawcuwateWwiteBackDISPCWK(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe PixewCwock,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackWumaHTaps,
		unsigned int WwitebackWumaVTaps,
		unsigned int WwitebackChwomaHTaps,
		unsigned int WwitebackChwomaVTaps,
		doubwe WwitebackDestinationWidth,
		unsigned int HTotaw,
		unsigned int WwitebackChwomaWineBuffewWidth)
{
	doubwe CawcuwateWwiteBackDISPCWK = 1.01 * PixewCwock * dmw_max(
		dmw_ceiw(WwitebackWumaHTaps / 4.0, 1) / WwitebackHWatio,
		dmw_max((WwitebackWumaVTaps * dmw_ceiw(1.0 / WwitebackVWatio, 1) * dmw_ceiw(WwitebackDestinationWidth / 4.0, 1)
			+ dmw_ceiw(WwitebackDestinationWidth / 4.0, 1)) / (doubwe) HTotaw + dmw_ceiw(1.0 / WwitebackVWatio, 1)
			* (dmw_ceiw(WwitebackWumaVTaps / 4.0, 1) + 4.0) / (doubwe) HTotaw,
			dmw_ceiw(1.0 / WwitebackVWatio, 1) * WwitebackDestinationWidth / (doubwe) HTotaw));
	if (WwitebackPixewFowmat != dm_444_32) {
		CawcuwateWwiteBackDISPCWK = dmw_max(CawcuwateWwiteBackDISPCWK, 1.01 * PixewCwock * dmw_max(
			dmw_ceiw(WwitebackChwomaHTaps / 2.0, 1) / (2 * WwitebackHWatio),
			dmw_max((WwitebackChwomaVTaps * dmw_ceiw(1 / (2 * WwitebackVWatio), 1) * dmw_ceiw(WwitebackDestinationWidth / 2.0 / 2.0, 1)
				+ dmw_ceiw(WwitebackDestinationWidth / 2.0 / WwitebackChwomaWineBuffewWidth, 1)) / HTotaw
				+ dmw_ceiw(1 / (2 * WwitebackVWatio), 1) * (dmw_ceiw(WwitebackChwomaVTaps / 4.0, 1) + 4) / HTotaw,
				dmw_ceiw(1.0 / (2 * WwitebackVWatio), 1) * WwitebackDestinationWidth / 2.0 / HTotaw)));
	}
	wetuwn CawcuwateWwiteBackDISPCWK;
}

