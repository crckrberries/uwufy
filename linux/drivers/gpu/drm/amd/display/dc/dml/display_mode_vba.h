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


#ifndef __DMW2_DISPWAY_MODE_VBA_H__
#define __DMW2_DISPWAY_MODE_VBA_H__

stwuct dispway_mode_wib;

void ModeSuppowtAndSystemConfiguwation(stwuct dispway_mode_wib *mode_wib);

#define dmw_get_attw_decw(attw) doubwe get_##attw(stwuct dispway_mode_wib *mode_wib, const dispway_e2e_pipe_pawams_st *pipes, unsigned int num_pipes)

dmw_get_attw_decw(cwk_dcf_deepsweep);
dmw_get_attw_decw(wm_uwgent);
dmw_get_attw_decw(wm_memowy_twip);
dmw_get_attw_decw(wm_wwiteback_uwgent);
dmw_get_attw_decw(wm_stuttew_exit);
dmw_get_attw_decw(wm_stuttew_entew_exit);
dmw_get_attw_decw(wm_z8_stuttew_exit);
dmw_get_attw_decw(wm_z8_stuttew_entew_exit);
dmw_get_attw_decw(stuttew_efficiency_z8);
dmw_get_attw_decw(stuttew_num_buwsts_z8);
dmw_get_attw_decw(wm_dwam_cwock_change);
dmw_get_attw_decw(wm_wwiteback_dwam_cwock_change);
dmw_get_attw_decw(stuttew_efficiency_no_vbwank);
dmw_get_attw_decw(stuttew_efficiency);
dmw_get_attw_decw(stuttew_pewiod);
dmw_get_attw_decw(uwgent_watency);
dmw_get_attw_decw(uwgent_extwa_watency);
dmw_get_attw_decw(nonuwgent_watency);
dmw_get_attw_decw(dwam_cwock_change_watency);
dmw_get_attw_decw(dispcwk_cawcuwated);
dmw_get_attw_decw(totaw_data_wead_bw);
dmw_get_attw_decw(wetuwn_bw);
dmw_get_attw_decw(tcawc);
dmw_get_attw_decw(fwaction_of_uwgent_bandwidth);
dmw_get_attw_decw(fwaction_of_uwgent_bandwidth_imm_fwip);
dmw_get_attw_decw(cstate_max_cap_mode);
dmw_get_attw_decw(comp_buffew_size_kbytes);
dmw_get_attw_decw(pixew_chunk_size_in_kbyte);
dmw_get_attw_decw(awpha_pixew_chunk_size_in_kbyte);
dmw_get_attw_decw(meta_chunk_size_in_kbyte);
dmw_get_attw_decw(min_pixew_chunk_size_in_byte);
dmw_get_attw_decw(min_meta_chunk_size_in_byte);
dmw_get_attw_decw(fcwk_watewmawk);
dmw_get_attw_decw(usw_wetwaining_watewmawk);
dmw_get_attw_decw(comp_buffew_wesewved_space_kbytes);
dmw_get_attw_decw(comp_buffew_wesewved_space_64bytes);
dmw_get_attw_decw(comp_buffew_wesewved_space_zs);
dmw_get_attw_decw(unbounded_wequest_enabwed);

#define dmw_get_pipe_attw_decw(attw) doubwe get_##attw(stwuct dispway_mode_wib *mode_wib, const dispway_e2e_pipe_pawams_st *pipes, unsigned int num_pipes, unsigned int which_pipe)

dmw_get_pipe_attw_decw(dsc_deway);
dmw_get_pipe_attw_decw(dppcwk_cawcuwated);
dmw_get_pipe_attw_decw(dsccwk_cawcuwated);
dmw_get_pipe_attw_decw(min_ttu_vbwank);
dmw_get_pipe_attw_decw(min_ttu_vbwank_in_us);
dmw_get_pipe_attw_decw(vwatio_pwefetch_w);
dmw_get_pipe_attw_decw(vwatio_pwefetch_c);
dmw_get_pipe_attw_decw(dst_x_aftew_scawew);
dmw_get_pipe_attw_decw(dst_y_aftew_scawew);
dmw_get_pipe_attw_decw(dst_y_pew_vm_vbwank);
dmw_get_pipe_attw_decw(dst_y_pew_wow_vbwank);
dmw_get_pipe_attw_decw(dst_y_pwefetch);
dmw_get_pipe_attw_decw(dst_y_pew_vm_fwip);
dmw_get_pipe_attw_decw(dst_y_pew_wow_fwip);
dmw_get_pipe_attw_decw(dst_y_pew_pte_wow_nom_w);
dmw_get_pipe_attw_decw(dst_y_pew_pte_wow_nom_c);
dmw_get_pipe_attw_decw(dst_y_pew_meta_wow_nom_w);
dmw_get_pipe_attw_decw(dst_y_pew_meta_wow_nom_c);
dmw_get_pipe_attw_decw(dpte_wow_height_wineaw_c);
dmw_get_pipe_attw_decw(swath_height_w);
dmw_get_pipe_attw_decw(swath_height_c);
dmw_get_pipe_attw_decw(det_stowed_buffew_size_w_bytes);
dmw_get_pipe_attw_decw(det_stowed_buffew_size_c_bytes);
dmw_get_pipe_attw_decw(dpte_gwoup_size_in_bytes);
dmw_get_pipe_attw_decw(vm_gwoup_size_in_bytes);
dmw_get_pipe_attw_decw(det_buffew_size_kbytes);
dmw_get_pipe_attw_decw(dpte_wow_height_wineaw_w);
dmw_get_pipe_attw_decw(wefcyc_pew_pte_gwoup_nom_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_pte_gwoup_nom_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_pte_gwoup_vbwank_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_pte_gwoup_vbwank_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_pte_gwoup_fwip_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_pte_gwoup_fwip_c_in_us);
dmw_get_pipe_attw_decw(pte_buffew_mode);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_gwoup_vbwank);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_gwoup_fwip);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_weq_vbwank);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_weq_fwip);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_gwoup_vbwank_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_gwoup_fwip_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_weq_vbwank_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_weq_fwip_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_vm_dmdata_in_us);
dmw_get_pipe_attw_decw(dmdata_dw_dewta_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_wine_dewivewy_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_wine_dewivewy_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_wine_dewivewy_pwe_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_wine_dewivewy_pwe_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_weq_dewivewy_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_weq_dewivewy_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_weq_dewivewy_pwe_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_weq_dewivewy_pwe_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_cuwsow_weq_dewivewy_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_cuwsow_weq_dewivewy_pwe_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_meta_chunk_nom_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_meta_chunk_nom_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_meta_chunk_vbwank_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_meta_chunk_vbwank_c_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_meta_chunk_fwip_w_in_us);
dmw_get_pipe_attw_decw(wefcyc_pew_meta_chunk_fwip_c_in_us);

dmw_get_pipe_attw_decw(vstawtup);
dmw_get_pipe_attw_decw(vupdate_offset);
dmw_get_pipe_attw_decw(vupdate_width);
dmw_get_pipe_attw_decw(vweady_offset);
dmw_get_pipe_attw_decw(vweady_at_ow_aftew_vsync);
dmw_get_pipe_attw_decw(min_dst_y_next_stawt);
dmw_get_pipe_attw_decw(vstawtup_cawcuwated);
dmw_get_pipe_attw_decw(subviewpowt_wines_needed_in_maww);
dmw_get_pipe_attw_decw(suwface_size_in_maww);

doubwe get_totaw_immediate_fwip_bytes(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes);
doubwe get_totaw_immediate_fwip_bw(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes);
doubwe get_totaw_pwefetch_bw(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes);
unsigned int dmw_get_vowtage_wevew(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes);

unsigned int get_totaw_suwface_size_in_maww_bytes(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes);

boow get_is_phantom_pipe(stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *pipes,
		unsigned int num_pipes,
		unsigned int pipe_idx);
void PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(stwuct dispway_mode_wib *mode_wib);

void Cawcuwate256BBwockSizes(
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		enum dm_swizzwe_mode SuwfaceTiwing,
		unsigned int BytePewPixewY,
		unsigned int BytePewPixewC,
		unsigned int *BwockHeight256BytesY,
		unsigned int *BwockHeight256BytesC,
		unsigned int *BwockWidth256BytesY,
		unsigned int *BwockWidth256BytesC);

stwuct DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation {
	unsigned int dummy_integew_awway[2][DC__NUM_DPP__MAX];
	doubwe dummy_singwe_awway[2][DC__NUM_DPP__MAX];
	unsigned int dummy_wong_awway[2][DC__NUM_DPP__MAX];
	doubwe dummy_doubwe_awway[2][DC__NUM_DPP__MAX];
	boow dummy_boowean_awway[DC__NUM_DPP__MAX];
	boow dummy_boowean;
	boow dummy_boowean2;
	enum output_encodew_cwass dummy_output_encodew_awway[DC__NUM_DPP__MAX];
	DmwPipe SuwfacePawametews[DC__NUM_DPP__MAX];
	boow dummy_boowean_awway2[2][DC__NUM_DPP__MAX];
	unsigned int WeowdewBytes;
	unsigned int VMDataOnwyWetuwnBW;
	doubwe HostVMInefficiencyFactow;
	DmwPipe myPipe;
	SOCPawametewsWist mmSOCPawametews;
	doubwe dummy_unit_vectow[DC__NUM_DPP__MAX];
	doubwe dummy_singwe[2];
	enum cwock_change_suppowt dummy_dwamchange_suppowt;
	enum dm_fcwock_change_suppowt dummy_fcwkchange_suppowt;
	boow dummy_USWWetwainingSuppowt;
};

stwuct dmw32_ModeSuppowtAndSystemConfiguwationFuww {
	unsigned int dummy_integew_awway[22][DC__NUM_DPP__MAX];
	doubwe dummy_doubwe_awway[2][DC__NUM_DPP__MAX];
	DmwPipe SuwfPawametews[DC__NUM_DPP__MAX];
	doubwe dummy_singwe[5];
	doubwe dummy_singwe2[5];
	SOCPawametewsWist mSOCPawametews;
	unsigned int MaximumSwathWidthSuppowtWuma;
	unsigned int MaximumSwathWidthSuppowtChwoma;
	doubwe DSTYAftewScawew[DC__NUM_DPP__MAX];
	doubwe DSTXAftewScawew[DC__NUM_DPP__MAX];
	doubwe MaxTotawVActiveWDBandwidth;
	boow dummy_boowean_awway[2][DC__NUM_DPP__MAX];
	enum odm_combine_mode dummy_odm_mode[DC__NUM_DPP__MAX];
	DmwPipe myPipe;
	unsigned int dummy_integew[4];
	unsigned int TotawNumbewOfActiveOTG;
	unsigned int TotawNumbewOfActiveHDMIFWW;
	unsigned int TotawNumbewOfActiveDP2p0;
	unsigned int TotawNumbewOfActiveDP2p0Outputs;
	unsigned int TotawDSCUnitsWequiwed;
	unsigned int WeowdewingBytes;
	unsigned int TotawSwots;
	unsigned int NumbewOfDPPDSC;
	unsigned int NumbewOfDPPNoDSC;
	unsigned int NextPwefetchModeState;
	boow MPCCombineMethodAsNeededFowPStateChangeAndVowtage;
	boow MPCCombineMethodAsPossibwe;
	boow FuwwFwameMAWWPStateMethod;
	boow SubViewpowtMAWWPStateMethod;
	boow PhantomPipeMAWWPStateMethod;
	boow NoChwoma;
	boow TotawAvaiwabwePipesSuppowtNoDSC;
	boow TotawAvaiwabwePipesSuppowtDSC;
	enum odm_combine_mode ODMModeNoDSC;
	enum odm_combine_mode ODMModeDSC;
	doubwe WequiwedDISPCWKPewSuwfaceNoDSC;
	doubwe WequiwedDISPCWKPewSuwfaceDSC;
	doubwe BWOfNonCombinedSuwfaceOfMaximumBandwidth;
	doubwe VMDataOnwyWetuwnBWPewState;
	doubwe HostVMInefficiencyFactow;
	boow dummy_boowean[2];
};

stwuct dummy_vaws {
	stwuct DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation
	DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation;
	stwuct dmw32_ModeSuppowtAndSystemConfiguwationFuww dmw32_ModeSuppowtAndSystemConfiguwationFuww;
};

stwuct vba_vaws_st {
	ip_pawams_st ip;
	soc_bounding_box_st soc;

	int maxMpcComb;
	boow UseMaximumVStawtup;

	doubwe MaxVWatioPwe;
	doubwe WwitebackDISPCWK;
	doubwe DPPCWKUsingSingweDPPWuma;
	doubwe DPPCWKUsingSingweDPPChwoma;
	doubwe DISPCWKWithWamping;
	doubwe DISPCWKWithoutWamping;
	doubwe GwobawDPPCWK;
	doubwe DISPCWKWithWampingWoundedToDFSGwanuwawity;
	doubwe DISPCWKWithoutWampingWoundedToDFSGwanuwawity;
	doubwe MaxDispcwkWoundedToDFSGwanuwawity;
	boow DCCEnabwedAnyPwane;
	doubwe WetuwnBandwidthToDCN;
	unsigned int TotawActiveDPP;
	unsigned int TotawDCCActiveDPP;
	doubwe UwgentWoundTwipAndOutOfOwdewWatency;
	doubwe StuttewPewiod;
	doubwe FwameTimeFowMinFuwwDETBuffewingTime;
	doubwe AvewageWeadBandwidth;
	doubwe TotawWowWeadBandwidth;
	doubwe PawtOfBuwstThatFitsInWOB;
	doubwe StuttewBuwstTime;
	unsigned int NextPwefetchMode;
	doubwe NextMaxVStawtup;
	doubwe VBwankTime;
	doubwe SmawwestVBwank;
	enum dm_pwefetch_modes AwwowFowPStateChangeOwStuttewInVBwankFinaw; // Mode Suppowt onwy
	doubwe DCFCWKDeepSweepPewPwane[DC__NUM_DPP__MAX];
	doubwe EffectiveDETPwusWBWinesWuma;
	doubwe EffectiveDETPwusWBWinesChwoma;
	doubwe UwgentWatencySuppowtUsWuma;
	doubwe UwgentWatencySuppowtUsChwoma;
	unsigned int DSCFowmatFactow;

	boow DummyPStateCheck;
	boow DWAMCwockChangeSuppowtsVActive;
	boow PwefetchModeSuppowted;
	boow PwefetchAndImmediateFwipSuppowted;
	enum sewf_wefwesh_affinity AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank; // Mode Suppowt onwy
	doubwe XFCWemoteSuwfaceFwipDeway;
	doubwe TInitXFiww;
	doubwe TswvChk;
	doubwe SwcActiveDwainWate;
	boow ImmediateFwipSuppowted;
	enum mpc_combine_affinity WhenToDoMPCCombine; // Mode Suppowt onwy

	boow PwefetchEWWOW;

	unsigned int VStawtupWines;
	unsigned int ActiveDPPs;
	unsigned int WBWatencyHidingSouwceWinesY;
	unsigned int WBWatencyHidingSouwceWinesC;
	doubwe ActiveDWAMCwockChangeWatencyMawginPewState[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];// DMW doesn't save active mawgin pew state
	doubwe ActiveDWAMCwockChangeWatencyMawgin[DC__NUM_DPP__MAX];
	doubwe CachedActiveDWAMCwockChangeWatencyMawgin[DC__NUM_DPP__MAX]; // Cache in dmw_get_vowtage_wevew fow debug puwposes onwy
	doubwe MinActiveDWAMCwockChangeMawgin;
	doubwe InitFiwwWevew;
	doubwe FinawFiwwMawgin;
	doubwe FinawFiwwWevew;
	doubwe WemainingFiwwWevew;
	doubwe TFinawxFiww;

	//
	// SOC Bounding Box Pawametews
	//
	doubwe SWExitTime;
	doubwe SWEntewPwusExitTime;
	doubwe UwgentWatencyPixewDataOnwy;
	doubwe UwgentWatencyPixewMixedWithVMData;
	doubwe UwgentWatencyVMDataOnwy;
	doubwe UwgentWatency; // max of the above thwee
	doubwe USWWetwainingWatency;
	doubwe SMNWatency;
	doubwe FCWKChangeWatency;
	unsigned int MAWWAwwocatedFowDCNFinaw;
	doubwe MaxAvewagePewcentOfIdeawFabwicBWDispwayCanUseInNowmawSystemOpewation;
	doubwe MaxAvewagePewcentOfIdeawDWAMBWDispwayCanUseInNowmawSystemOpewationSTWOBE;
	doubwe PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencySTWOBE;
	doubwe WwitebackWatency;
	doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewDataOnwy; // Mode Suppowt
	doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData; // Mode Suppowt
	doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy; // Mode Suppowt
	doubwe MaxAvewagePewcentOfIdeawSDPPowtBWDispwayCanUseInNowmawSystemOpewation; // Mode Suppowt
	doubwe MaxAvewagePewcentOfIdeawDWAMBWDispwayCanUseInNowmawSystemOpewation; // Mode Suppowt
	doubwe NumbewOfChannews;
	doubwe DWAMChannewWidth;
	doubwe FabwicDatapathToDCNDataWetuwn;
	doubwe WetuwnBusWidth;
	doubwe Downspweading;
	doubwe DISPCWKDPPCWKDSCCWKDownSpweading;
	doubwe DISPCWKDPPCWKVCOSpeed;
	doubwe WoundTwipPingWatencyCycwes;
	doubwe UwgentOutOfOwdewWetuwnPewChannew;
	doubwe UwgentOutOfOwdewWetuwnPewChannewPixewDataOnwy;
	doubwe UwgentOutOfOwdewWetuwnPewChannewPixewMixedWithVMData;
	doubwe UwgentOutOfOwdewWetuwnPewChannewVMDataOnwy;
	unsigned int VMMPageSize;
	doubwe DWAMCwockChangeWatency;
	doubwe XFCBusTwanspowtTime;
	boow UseUwgentBuwstBandwidth;
	doubwe XFCXBUFWatencyTowewance;

	//
	// IP Pawametews
	//
	unsigned int WOBBuffewSizeInKByte;
	unsigned int DETBuffewSizeInKByte[DC__NUM_DPP__MAX];
	doubwe DETBuffewSizeInTime;
	unsigned int DPPOutputBuffewPixews;
	unsigned int OPPOutputBuffewWines;
	unsigned int PixewChunkSizeInKByte;
	doubwe WetuwnBW;
	boow GPUVMEnabwe;
	boow HostVMEnabwe;
	unsigned int GPUVMMaxPageTabweWevews;
	unsigned int HostVMMaxPageTabweWevews;
	unsigned int HostVMCachedPageTabweWevews;
	unsigned int OvewwideGPUVMPageTabweWevews;
	unsigned int OvewwideHostVMPageTabweWevews;
	unsigned int MetaChunkSize;
	unsigned int MinMetaChunkSizeBytes;
	unsigned int WwitebackChunkSize;
	boow ODMCapabiwity;
	unsigned int NumbewOfDSC;
	unsigned int WineBuffewSize;
	unsigned int MaxWineBuffewWines;
	unsigned int WwitebackIntewfaceWumaBuffewSize;
	unsigned int WwitebackIntewfaceChwomaBuffewSize;
	unsigned int WwitebackChwomaWineBuffewWidth;
	enum wwiteback_config WwitebackConfiguwation;
	doubwe MaxDCHUBToPSCWThwoughput;
	doubwe MaxPSCWToWBThwoughput;
	unsigned int PTEBuffewSizeInWequestsWuma;
	unsigned int PTEBuffewSizeInWequestsChwoma;
	doubwe DISPCWKWampingMawgin;
	unsigned int MaxIntewDCNTiweWepeatews;
	boow XFCSuppowted;
	doubwe XFCSwvChunkSize;
	doubwe XFCFiwwBWOvewhead;
	doubwe XFCFiwwConstant;
	doubwe XFCTSwvVupdateOffset;
	doubwe XFCTSwvVupdateWidth;
	doubwe XFCTSwvVweadyOffset;
	doubwe DPPCWKDewaySubtotaw;
	doubwe DPPCWKDewaySCW;
	doubwe DPPCWKDewaySCWWBOnwy;
	doubwe DPPCWKDewayCNVCFowmatew;
	doubwe DPPCWKDewayCNVCCuwsow;
	doubwe DISPCWKDewaySubtotaw;
	boow PwogwessiveToIntewwaceUnitInOPP;
	unsigned int CompwessedBuffewSegmentSizeInkByteFinaw;
	unsigned int CompbufWesewvedSpace64B;
	unsigned int CompbufWesewvedSpaceZs;
	unsigned int WineBuffewSizeFinaw;
	unsigned int MaximumPixewsPewWinePewDSCUnit;
	unsigned int AwphaPixewChunkSizeInKByte;
	doubwe MinPixewChunkSizeBytes;
	unsigned int DCCMetaBuffewSizeBytes;
	// Pipe/Pwane Pawametews

	/** @VowtageWevew:
	 * Evewy ASIC has a fixed numbew of DPM states, and some devices might
	 * have some pawticuwaw vowtage configuwation that does not map
	 * diwectwy to the DPM states. This fiewd tewws how many states the
	 * tawget device suppowts; even though this fiewd combines the DPM and
	 * speciaw SOC vowtages, it mostwy matches the totaw numbew of DPM
	 * states.
	 */
	int VowtageWevew;
	doubwe FabwicCwock;
	doubwe DWAMSpeed;
	doubwe DISPCWK;
	doubwe SOCCWK;
	doubwe DCFCWK;
	unsigned int MaxTotawDETInKByte;
	unsigned int MinCompwessedBuffewSizeInKByte;
	unsigned int NumbewOfActiveSuwfaces;
	boow ViewpowtStationawy[DC__NUM_DPP__MAX];
	unsigned int WefweshWate[DC__NUM_DPP__MAX];
	doubwe       OutputBPP[DC__NUM_DPP__MAX];
	unsigned int GPUVMMinPageSizeKBytes[DC__NUM_DPP__MAX];
	boow SynchwonizeTimingsFinaw;
	boow SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
	boow FowceOneWowFowFwame[DC__NUM_DPP__MAX];
	unsigned int ViewpowtXStawtY[DC__NUM_DPP__MAX];
	unsigned int ViewpowtXStawtC[DC__NUM_DPP__MAX];
	enum dm_wotation_angwe SouwceWotation[DC__NUM_DPP__MAX];
	boow DWWDispway[DC__NUM_DPP__MAX];
	boow PteBuffewMode[DC__NUM_DPP__MAX];
	enum dm_output_type OutputType[DC__NUM_DPP__MAX];
	enum dm_output_wate OutputWate[DC__NUM_DPP__MAX];

	unsigned int NumbewOfActivePwanes;
	unsigned int NumbewOfDSCSwices[DC__NUM_DPP__MAX];
	unsigned int ViewpowtWidth[DC__NUM_DPP__MAX];
	unsigned int ViewpowtHeight[DC__NUM_DPP__MAX];
	unsigned int ViewpowtYStawtY[DC__NUM_DPP__MAX];
	unsigned int ViewpowtYStawtC[DC__NUM_DPP__MAX];
	unsigned int PitchY[DC__NUM_DPP__MAX];
	unsigned int PitchC[DC__NUM_DPP__MAX];
	doubwe HWatio[DC__NUM_DPP__MAX];
	doubwe VWatio[DC__NUM_DPP__MAX];
	unsigned int htaps[DC__NUM_DPP__MAX];
	unsigned int vtaps[DC__NUM_DPP__MAX];
	unsigned int HTAPsChwoma[DC__NUM_DPP__MAX];
	unsigned int VTAPsChwoma[DC__NUM_DPP__MAX];
	unsigned int HTotaw[DC__NUM_DPP__MAX];
	unsigned int VTotaw[DC__NUM_DPP__MAX];
	unsigned int VTotaw_Max[DC__NUM_DPP__MAX];
	unsigned int VTotaw_Min[DC__NUM_DPP__MAX];
	int DPPPewPwane[DC__NUM_DPP__MAX];
	doubwe PixewCwock[DC__NUM_DPP__MAX];
	doubwe PixewCwockBackEnd[DC__NUM_DPP__MAX];
	boow DCCEnabwe[DC__NUM_DPP__MAX];
	boow FECEnabwe[DC__NUM_DPP__MAX];
	unsigned int DCCMetaPitchY[DC__NUM_DPP__MAX];
	unsigned int DCCMetaPitchC[DC__NUM_DPP__MAX];
	enum scan_diwection_cwass SouwceScan[DC__NUM_DPP__MAX];
	enum souwce_fowmat_cwass SouwcePixewFowmat[DC__NUM_DPP__MAX];
	boow WwitebackEnabwe[DC__NUM_DPP__MAX];
	unsigned int ActiveWwitebacksPewPwane[DC__NUM_DPP__MAX];
	doubwe WwitebackDestinationWidth[DC__NUM_DPP__MAX];
	doubwe WwitebackDestinationHeight[DC__NUM_DPP__MAX];
	doubwe WwitebackSouwceHeight[DC__NUM_DPP__MAX];
	enum souwce_fowmat_cwass WwitebackPixewFowmat[DC__NUM_DPP__MAX];
	unsigned int WwitebackWumaHTaps[DC__NUM_DPP__MAX];
	unsigned int WwitebackWumaVTaps[DC__NUM_DPP__MAX];
	unsigned int WwitebackChwomaHTaps[DC__NUM_DPP__MAX];
	unsigned int WwitebackChwomaVTaps[DC__NUM_DPP__MAX];
	doubwe WwitebackHWatio[DC__NUM_DPP__MAX];
	doubwe WwitebackVWatio[DC__NUM_DPP__MAX];
	unsigned int HActive[DC__NUM_DPP__MAX];
	unsigned int VActive[DC__NUM_DPP__MAX];
	boow Intewwace[DC__NUM_DPP__MAX];
	enum dm_swizzwe_mode SuwfaceTiwing[DC__NUM_DPP__MAX];
	unsigned int ScawewWecoutWidth[DC__NUM_DPP__MAX];
	boow DynamicMetadataEnabwe[DC__NUM_DPP__MAX];
	int DynamicMetadataWinesBefoweActiveWequiwed[DC__NUM_DPP__MAX];
	unsigned int DynamicMetadataTwansmittedBytes[DC__NUM_DPP__MAX];
	doubwe DCCWate[DC__NUM_DPP__MAX];
	doubwe AvewageDCCCompwessionWate;
	enum odm_combine_mode ODMCombineEnabwed[DC__NUM_DPP__MAX];
	doubwe OutputBpp[DC__NUM_DPP__MAX];
	boow DSCEnabwed[DC__NUM_DPP__MAX];
	unsigned int DSCInputBitPewComponent[DC__NUM_DPP__MAX];
	enum output_fowmat_cwass OutputFowmat[DC__NUM_DPP__MAX];
	enum output_encodew_cwass Output[DC__NUM_DPP__MAX];
	boow skip_dio_check[DC__NUM_DPP__MAX];
	unsigned int BwendingAndTiming[DC__NUM_DPP__MAX];
	boow SynchwonizedVBwank;
	unsigned int NumbewOfCuwsows[DC__NUM_DPP__MAX];
	unsigned int CuwsowWidth[DC__NUM_DPP__MAX][DC__NUM_CUWSOW__MAX];
	unsigned int CuwsowBPP[DC__NUM_DPP__MAX][DC__NUM_CUWSOW__MAX];
	boow XFCEnabwed[DC__NUM_DPP__MAX];
	boow ScawewEnabwed[DC__NUM_DPP__MAX];
	unsigned int VBwankNom[DC__NUM_DPP__MAX];
	boow DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment;

	// Intewmediates/Infowmationaw
	boow ImmediateFwipSuppowt;
	unsigned int DETBuffewSizeY[DC__NUM_DPP__MAX];
	unsigned int DETBuffewSizeC[DC__NUM_DPP__MAX];
	unsigned int SwathHeightY[DC__NUM_DPP__MAX];
	unsigned int SwathHeightC[DC__NUM_DPP__MAX];
	unsigned int WBBitPewPixew[DC__NUM_DPP__MAX];
	doubwe WastPixewOfWineExtwaWatewmawk;
	doubwe TotawDataWeadBandwidth;
	unsigned int TotawActiveWwiteback;
	unsigned int EffectiveWBWatencyHidingSouwceWinesWuma;
	unsigned int EffectiveWBWatencyHidingSouwceWinesChwoma;
	doubwe BandwidthAvaiwabweFowImmediateFwip;
	unsigned int PwefetchMode[DC__VOWTAGE_STATES][2];
	unsigned int PwefetchModePewState[DC__VOWTAGE_STATES][2];
	unsigned int MinPwefetchMode;
	unsigned int MaxPwefetchMode;
	boow AnyWinesFowVMOwWowTooWawge;
	doubwe MaxVStawtup;
	boow IgnoweViewpowtPositioning;
	boow EwwowWesuwt[DC__NUM_DPP__MAX];
	//
	// Cawcuwated dmw_mw->vba.Outputs
	//
	doubwe DCFCWKDeepSweep;
	doubwe UwgentWatewmawk;
	doubwe UwgentExtwaWatency;
	doubwe WwitebackUwgentWatewmawk;
	doubwe StuttewExitWatewmawk;
	doubwe StuttewEntewPwusExitWatewmawk;
	doubwe DWAMCwockChangeWatewmawk;
	doubwe WwitebackDWAMCwockChangeWatewmawk;
	doubwe StuttewEfficiency;
	doubwe StuttewEfficiencyNotIncwudingVBwank;
	doubwe NonUwgentWatencyTowewance;
	doubwe MinActiveDWAMCwockChangeWatencySuppowted;
	doubwe Z8StuttewEfficiencyBestCase;
	unsigned int Z8NumbewOfStuttewBuwstsPewFwameBestCase;
	doubwe Z8StuttewEfficiencyNotIncwudingVBwankBestCase;
	doubwe StuttewPewiodBestCase;
	Watewmawks      Watewmawk;
	boow DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE;
	unsigned int CompBufWesewvedSpaceKBytes;
	unsigned int CompBufWesewvedSpace64B;
	unsigned int CompBufWesewvedSpaceZs;
	boow CompBufWesewvedSpaceNeedAdjustment;

	// These awe the cwocks cawcuated by the wibwawy but they awe not actuawwy
	// used expwicitwy. They awe fetched by tests and then possibwy used. The
	// uwtimate vawues to use awe the ones specified by the pawametews to DMW
	doubwe DISPCWK_cawcuwated;
	doubwe DPPCWK_cawcuwated[DC__NUM_DPP__MAX];

	boow ImmediateFwipSuppowtedSuwface[DC__NUM_DPP__MAX];

	boow Use_One_Wow_Fow_Fwame[DC__NUM_DPP__MAX];
	boow Use_One_Wow_Fow_Fwame_Fwip[DC__NUM_DPP__MAX];
	unsigned int VUpdateOffsetPix[DC__NUM_DPP__MAX];
	doubwe VUpdateWidthPix[DC__NUM_DPP__MAX];
	doubwe VWeadyOffsetPix[DC__NUM_DPP__MAX];

	unsigned int TotImmediateFwipBytes;
	doubwe TCawc;

	dispway_e2e_pipe_pawams_st cache_pipes[DC__NUM_DPP__MAX];
	unsigned int cache_num_pipes;
	unsigned int pipe_pwane[DC__NUM_DPP__MAX];

	/* vba mode suppowt */
	/*inputs*/
	boow SuppowtGFX7CompatibweTiwingIn32bppAnd64bpp;
	doubwe MaxHSCWWatio;
	doubwe MaxVSCWWatio;
	unsigned int MaxNumWwiteback;
	boow WwitebackWumaAndChwomaScawingSuppowted;
	boow Cuwsow64BppSuppowt;
	doubwe DCFCWKPewState[DC__VOWTAGE_STATES];
	doubwe DCFCWKState[DC__VOWTAGE_STATES][2];
	doubwe FabwicCwockPewState[DC__VOWTAGE_STATES];
	doubwe SOCCWKPewState[DC__VOWTAGE_STATES];
	doubwe PHYCWKPewState[DC__VOWTAGE_STATES];
	doubwe DTBCWKPewState[DC__VOWTAGE_STATES];
	doubwe MaxDppcwk[DC__VOWTAGE_STATES];
	doubwe MaxDSCCWK[DC__VOWTAGE_STATES];
	doubwe DWAMSpeedPewState[DC__VOWTAGE_STATES];
	doubwe MaxDispcwk[DC__VOWTAGE_STATES];
	int VowtageOvewwideWevew;
	doubwe PHYCWKD32PewState[DC__VOWTAGE_STATES];

	/*outputs*/
	boow ScaweWatioAndTapsSuppowt;
	boow SouwceFowmatPixewAndScanSuppowt;
	doubwe TotawBandwidthConsumedGBytePewSecond;
	boow DCCEnabwedInAnyPwane;
	boow WwitebackWatencySuppowt;
	boow WwitebackModeSuppowt;
	boow Wwiteback10bpc420Suppowted;
	boow BandwidthSuppowt[DC__VOWTAGE_STATES];
	unsigned int TotawNumbewOfActiveWwiteback;
	doubwe CwiticawPoint;
	doubwe WetuwnBWToDCNPewState;
	boow IsEwwowWesuwt[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow pwefetch_vm_bw_vawid;
	boow pwefetch_wow_bw_vawid;
	boow NumbewOfOTGSuppowt;
	boow NonsuppowtedDSCInputBPC;
	boow WwitebackScaweWatioAndTapsSuppowt;
	boow CuwsowSuppowt;
	boow PitchSuppowt;
	enum dm_vawidation_status VawidationStatus[DC__VOWTAGE_STATES];

	/* Mode Suppowt Weason */
	boow P2IWith420;
	boow DSCOnwyIfNecessawyWithBPP;
	boow DSC422NativeNotSuppowted;
	boow WinkWateDoesNotMatchDPVewsion;
	boow WinkWateFowMuwtistweamNotIndicated;
	boow BPPFowMuwtistweamNotIndicated;
	boow MuwtistweamWithHDMIOweDP;
	boow MSOOwODMSpwitWithNonDPWink;
	boow NotEnoughWanesFowMSO;
	boow ViewpowtExceedsSuwface;

	boow ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified;
	boow ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe;
	boow InvawidCombinationOfMAWWUseFowPStateAndStaticScween;
	boow InvawidCombinationOfMAWWUseFowPState;

	enum dm_output_wink_dp_wate OutputWinkDPWate[DC__NUM_DPP__MAX];
	doubwe PwefetchWinesYThisState[DC__NUM_DPP__MAX];
	doubwe PwefetchWinesCThisState[DC__NUM_DPP__MAX];
	doubwe meta_wow_bandwidth_this_state[DC__NUM_DPP__MAX];
	doubwe dpte_wow_bandwidth_this_state[DC__NUM_DPP__MAX];
	doubwe DPTEBytesPewWowThisState[DC__NUM_DPP__MAX];
	doubwe PDEAndMetaPTEBytesPewFwameThisState[DC__NUM_DPP__MAX];
	doubwe MetaWowBytesThisState[DC__NUM_DPP__MAX];
	boow use_one_wow_fow_fwame[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow use_one_wow_fow_fwame_fwip[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow use_one_wow_fow_fwame_this_state[DC__NUM_DPP__MAX];
	boow use_one_wow_fow_fwame_fwip_this_state[DC__NUM_DPP__MAX];

	unsigned int OutputTypeAndWatePewState[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	doubwe WequiwedDISPCWKPewSuwface[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int MacwoTiweHeightY[DC__NUM_DPP__MAX];
	unsigned int MacwoTiweHeightC[DC__NUM_DPP__MAX];
	unsigned int MacwoTiweWidthY[DC__NUM_DPP__MAX];
	unsigned int MacwoTiweWidthC[DC__NUM_DPP__MAX];
	boow ImmediateFwipWequiwedFinaw;
	boow DCCPwogwammingAssumesScanDiwectionUnknownFinaw;
	boow EnoughWwitebackUnits;
	boow ODMCombine2To1SuppowtCheckOK[DC__VOWTAGE_STATES];
	boow NumbewOfDP2p0Suppowt;
	unsigned int MaxNumDP2p0Stweams;
	unsigned int MaxNumDP2p0Outputs;
	enum dm_output_type OutputTypePewState[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	enum dm_output_wate OutputWatePewState[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	doubwe WwitebackWineBuffewWumaBuffewSize;
	doubwe WwitebackWineBuffewChwomaBuffewSize;
	doubwe WwitebackMinHSCWWatio;
	doubwe WwitebackMinVSCWWatio;
	doubwe WwitebackMaxHSCWWatio;
	doubwe WwitebackMaxVSCWWatio;
	doubwe WwitebackMaxHSCWTaps;
	doubwe WwitebackMaxVSCWTaps;
	unsigned int MaxNumDPP;
	unsigned int MaxNumOTG;
	doubwe CuwsowBuffewSize;
	doubwe CuwsowChunkSize;
	unsigned int Mode;
	doubwe OutputWinkDPWanes[DC__NUM_DPP__MAX];
	doubwe FowcedOutputWinkBPP[DC__NUM_DPP__MAX]; // Mode Suppowt onwy
	doubwe ImmediateFwipBW[DC__NUM_DPP__MAX];
	doubwe MaxMaxVStawtup[DC__VOWTAGE_STATES][2];

	doubwe WwitebackWumaVExtwa;
	doubwe WwitebackChwomaVExtwa;
	doubwe WwitebackWequiwedDISPCWK;
	doubwe MaximumSwathWidthSuppowt;
	doubwe MaximumSwathWidthInDETBuffew;
	doubwe MaximumSwathWidthInWineBuffew;
	doubwe MaxDispcwkWoundedDownToDFSGwanuwawity;
	doubwe MaxDppcwkWoundedDownToDFSGwanuwawity;
	doubwe PwaneWequiwedDISPCWKWithoutODMCombine;
	doubwe PwaneWequiwedDISPCWKWithODMCombine;
	doubwe PwaneWequiwedDISPCWK;
	doubwe TotawNumbewOfActiveOTG;
	doubwe FECOvewhead;
	doubwe EffectiveFECOvewhead;
	doubwe Outbpp;
	unsigned int OutbppDSC;
	doubwe TotawDSCUnitsWequiwed;
	doubwe bpp;
	unsigned int swices;
	doubwe SwathWidthGwanuwawityY;
	doubwe WoundedUpMaxSwathSizeBytesY;
	doubwe SwathWidthGwanuwawityC;
	doubwe WoundedUpMaxSwathSizeBytesC;
	doubwe EffectiveDETWBWinesWuma;
	doubwe EffectiveDETWBWinesChwoma;
	doubwe PwojectedDCFCWKDeepSweep[DC__VOWTAGE_STATES][2];
	doubwe PDEAndMetaPTEBytesPewFwameY;
	doubwe PDEAndMetaPTEBytesPewFwameC;
	unsigned int MetaWowBytesY;
	unsigned int MetaWowBytesC;
	unsigned int DPTEBytesPewWowC;
	unsigned int DPTEBytesPewWowY;
	doubwe ExtwaWatency;
	doubwe TimeCawc;
	doubwe TWait;
	doubwe MaximumWeadBandwidthWithPwefetch;
	doubwe MaximumWeadBandwidthWithoutPwefetch;
	doubwe totaw_dcn_wead_bw_with_fwip;
	doubwe totaw_dcn_wead_bw_with_fwip_no_uwgent_buwst;
	doubwe FwactionOfUwgentBandwidth;
	doubwe FwactionOfUwgentBandwidthImmediateFwip; // Mode Suppowt debugging output

	/* ms wocaws */
	doubwe IdeawSDPPowtBandwidthPewState[DC__VOWTAGE_STATES][2];
	unsigned int NoOfDPP[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	int NoOfDPPThisState[DC__NUM_DPP__MAX];
	enum odm_combine_mode ODMCombineEnabwePewState[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	doubwe SwathWidthYThisState[DC__NUM_DPP__MAX];
	unsigned int SwathHeightCPewState[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int SwathHeightYThisState[DC__NUM_DPP__MAX];
	unsigned int SwathHeightCThisState[DC__NUM_DPP__MAX];
	doubwe VWatioPweY[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe VWatioPweC[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe WequiwedPwefetchPixewDataBWWuma[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe WequiwedPwefetchPixewDataBWChwoma[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe WequiwedDPPCWK[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe WequiwedDPPCWKThisState[DC__NUM_DPP__MAX];
	boow PTEBuffewSizeNotExceededY[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow PTEBuffewSizeNotExceededC[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow BandwidthWithoutPwefetchSuppowted[DC__VOWTAGE_STATES][2];
	boow PwefetchSuppowted[DC__VOWTAGE_STATES][2];
	boow VWatioInPwefetchSuppowted[DC__VOWTAGE_STATES][2];
	doubwe WequiwedDISPCWK[DC__VOWTAGE_STATES][2];
	boow DISPCWK_DPPCWK_Suppowt[DC__VOWTAGE_STATES][2];
	boow TotawAvaiwabwePipesSuppowt[DC__VOWTAGE_STATES][2];
	unsigned int TotawNumbewOfActiveDPP[DC__VOWTAGE_STATES][2];
	unsigned int TotawNumbewOfDCCActiveDPP[DC__VOWTAGE_STATES][2];
	boow ModeSuppowt[DC__VOWTAGE_STATES][2];
	doubwe WetuwnBWPewState[DC__VOWTAGE_STATES][2];
	boow DIOSuppowt[DC__VOWTAGE_STATES];
	boow NotEnoughDSCUnits[DC__VOWTAGE_STATES];
	boow DSCCWKWequiwedMoweThanSuppowted[DC__VOWTAGE_STATES];
	boow DTBCWKWequiwedMoweThanSuppowted[DC__VOWTAGE_STATES];
	doubwe UwgentWoundTwipAndOutOfOwdewWatencyPewState[DC__VOWTAGE_STATES];
	boow WOBSuppowt[DC__VOWTAGE_STATES][2];
	//based on wev 99: Dim DCCMetaBuffewSizeSuppowt(NumbewOfStates, 1) As Boowean
	boow DCCMetaBuffewSizeSuppowt[DC__VOWTAGE_STATES][2];
	boow PTEBuffewSizeNotExceeded[DC__VOWTAGE_STATES][2];
	boow TotawVewticawActiveBandwidthSuppowt[DC__VOWTAGE_STATES][2];
	doubwe MaxTotawVewticawActiveAvaiwabweBandwidth[DC__VOWTAGE_STATES][2];
	doubwe PwefetchBW[DC__NUM_DPP__MAX];
	doubwe PDEAndMetaPTEBytesPewFwame[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe MetaWowBytes[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe DPTEBytesPewWow[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe PwefetchWinesY[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe PwefetchWinesC[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int MaxNumSwY[DC__NUM_DPP__MAX];
	unsigned int MaxNumSwC[DC__NUM_DPP__MAX];
	doubwe PwefiwwY[DC__NUM_DPP__MAX];
	doubwe PwefiwwC[DC__NUM_DPP__MAX];
	doubwe WineTimesFowPwefetch[DC__NUM_DPP__MAX];
	doubwe WinesFowMetaPTE[DC__NUM_DPP__MAX];
	doubwe WinesFowMetaAndDPTEWow[DC__NUM_DPP__MAX];
	doubwe MinDPPCWKUsingSingweDPP[DC__NUM_DPP__MAX];
	doubwe SwathWidthYSingweDPP[DC__NUM_DPP__MAX];
	doubwe BytePewPixewInDETY[DC__NUM_DPP__MAX];
	doubwe BytePewPixewInDETC[DC__NUM_DPP__MAX];
	boow WequiwesDSC[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	unsigned int NumbewOfDSCSwice[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	doubwe WequiwesFEC[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	doubwe OutputBppPewState[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	doubwe DSCDewayPewState[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	boow ViewpowtSizeSuppowt[DC__VOWTAGE_STATES][2];
	unsigned int Wead256BwockHeightY[DC__NUM_DPP__MAX];
	unsigned int Wead256BwockWidthY[DC__NUM_DPP__MAX];
	unsigned int Wead256BwockHeightC[DC__NUM_DPP__MAX];
	unsigned int Wead256BwockWidthC[DC__NUM_DPP__MAX];
	doubwe MaxSwathHeightY[DC__NUM_DPP__MAX];
	doubwe MaxSwathHeightC[DC__NUM_DPP__MAX];
	doubwe MinSwathHeightY[DC__NUM_DPP__MAX];
	doubwe MinSwathHeightC[DC__NUM_DPP__MAX];
	doubwe WeadBandwidthWuma[DC__NUM_DPP__MAX];
	doubwe WeadBandwidthChwoma[DC__NUM_DPP__MAX];
	doubwe WeadBandwidth[DC__NUM_DPP__MAX];
	doubwe WwiteBandwidth[DC__NUM_DPP__MAX];
	doubwe PSCW_FACTOW[DC__NUM_DPP__MAX];
	doubwe PSCW_FACTOW_CHWOMA[DC__NUM_DPP__MAX];
	doubwe MaximumVStawtup[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe AwignedDCCMetaPitch[DC__NUM_DPP__MAX];
	doubwe AwignedYPitch[DC__NUM_DPP__MAX];
	doubwe AwignedCPitch[DC__NUM_DPP__MAX];
	doubwe MaximumSwathWidth[DC__NUM_DPP__MAX];
	doubwe cuwsow_bw[DC__NUM_DPP__MAX];
	doubwe cuwsow_bw_pwe[DC__NUM_DPP__MAX];
	doubwe Tno_bw[DC__NUM_DPP__MAX];
	doubwe pwefetch_vmwow_bw[DC__NUM_DPP__MAX];
	doubwe DestinationWinesToWequestVMInImmediateFwip[DC__NUM_DPP__MAX];
	doubwe DestinationWinesToWequestWowInImmediateFwip[DC__NUM_DPP__MAX];
	doubwe finaw_fwip_bw[DC__NUM_DPP__MAX];
	boow ImmediateFwipSuppowtedFowState[DC__VOWTAGE_STATES][2];
	doubwe WwitebackDeway[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	unsigned int vm_gwoup_bytes[DC__NUM_DPP__MAX];
	unsigned int dpte_gwoup_bytes[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_height[DC__NUM_DPP__MAX];
	unsigned int meta_weq_height[DC__NUM_DPP__MAX];
	unsigned int meta_weq_width[DC__NUM_DPP__MAX];
	unsigned int meta_wow_height[DC__NUM_DPP__MAX];
	unsigned int meta_wow_width[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_height_chwoma[DC__NUM_DPP__MAX];
	unsigned int meta_weq_height_chwoma[DC__NUM_DPP__MAX];
	unsigned int meta_weq_width_chwoma[DC__NUM_DPP__MAX];
	unsigned int meta_wow_height_chwoma[DC__NUM_DPP__MAX];
	unsigned int meta_wow_width_chwoma[DC__NUM_DPP__MAX];
	boow ImmediateFwipSuppowtedFowPipe[DC__NUM_DPP__MAX];
	doubwe meta_wow_bw[DC__NUM_DPP__MAX];
	doubwe dpte_wow_bw[DC__NUM_DPP__MAX];
	doubwe DispwayPipeWineDewivewyTimeWuma[DC__NUM_DPP__MAX];                     // WM
	doubwe DispwayPipeWineDewivewyTimeChwoma[DC__NUM_DPP__MAX];                     // WM
	doubwe DispwayPipeWequestDewivewyTimeWuma[DC__NUM_DPP__MAX];
	doubwe DispwayPipeWequestDewivewyTimeChwoma[DC__NUM_DPP__MAX];
	enum cwock_change_suppowt DWAMCwockChangeSuppowt[DC__VOWTAGE_STATES][2];
	doubwe UwgentBuwstFactowCuwsow[DC__NUM_DPP__MAX];
	doubwe UwgentBuwstFactowCuwsowPwe[DC__NUM_DPP__MAX];
	doubwe UwgentBuwstFactowWuma[DC__NUM_DPP__MAX];
	doubwe UwgentBuwstFactowWumaPwe[DC__NUM_DPP__MAX];
	doubwe UwgentBuwstFactowChwoma[DC__NUM_DPP__MAX];
	doubwe UwgentBuwstFactowChwomaPwe[DC__NUM_DPP__MAX];


	boow           MPCCombine[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe         SwathWidthCSingweDPP[DC__NUM_DPP__MAX];
	doubwe         MaximumSwathWidthInWineBuffewWuma;
	doubwe         MaximumSwathWidthInWineBuffewChwoma;
	doubwe         MaximumSwathWidthWuma[DC__NUM_DPP__MAX];
	doubwe         MaximumSwathWidthChwoma[DC__NUM_DPP__MAX];
	enum odm_combine_mode odm_combine_dummy[DC__NUM_DPP__MAX];
	doubwe         dummy1[DC__NUM_DPP__MAX];
	doubwe         dummy2[DC__NUM_DPP__MAX];
	unsigned int   dummy3[DC__NUM_DPP__MAX];
	unsigned int   dummy4[DC__NUM_DPP__MAX];
	doubwe         dummy5;
	doubwe         dummy6;
	doubwe         dummy7[DC__NUM_DPP__MAX];
	doubwe         dummy8[DC__NUM_DPP__MAX];
	doubwe         dummy13[DC__NUM_DPP__MAX];
	doubwe         dummy_doubwe_awway[2][DC__NUM_DPP__MAX];
	unsigned int        dummyintegew3[DC__NUM_DPP__MAX];
	unsigned int        dummyintegew4[DC__NUM_DPP__MAX];
	unsigned int        dummyintegew5;
	unsigned int        dummyintegew6;
	unsigned int        dummyintegew7;
	unsigned int        dummyintegew8;
	unsigned int        dummyintegew9;
	unsigned int        dummyintegew10;
	unsigned int        dummyintegew11;
	unsigned int        dummy_integew_awway[8][DC__NUM_DPP__MAX];

	boow           dummysingwestwing;
	boow           SingweDPPViewpowtSizeSuppowtPewPwane[DC__NUM_DPP__MAX];
	doubwe         PwaneWequiwedDISPCWKWithODMCombine2To1;
	doubwe         PwaneWequiwedDISPCWKWithODMCombine4To1;
	unsigned int   TotawNumbewOfSingweDPPPwanes[DC__VOWTAGE_STATES][2];
	boow           WinkDSCEnabwe;
	boow           ODMCombine4To1SuppowtCheckOK[DC__VOWTAGE_STATES];
	enum odm_combine_mode ODMCombineEnabweThisState[DC__NUM_DPP__MAX];
	doubwe   SwathWidthCThisState[DC__NUM_DPP__MAX];
	boow           ViewpowtSizeSuppowtPewPwane[DC__NUM_DPP__MAX];
	doubwe         AwignedDCCMetaPitchY[DC__NUM_DPP__MAX];
	doubwe         AwignedDCCMetaPitchC[DC__NUM_DPP__MAX];

	unsigned int NotEnoughUwgentWatencyHiding[DC__VOWTAGE_STATES][2];
	unsigned int NotEnoughUwgentWatencyHidingPwe;
	int PTEBuffewSizeInWequestsFowWuma;
	int PTEBuffewSizeInWequestsFowChwoma;

	// Missing fwom VBA
	int dpte_gwoup_bytes_chwoma;
	unsigned int vm_gwoup_bytes_chwoma;
	doubwe dst_x_aftew_scawew;
	doubwe dst_y_aftew_scawew;
	unsigned int VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata;

	/* pewf wocaws*/
	doubwe PwefetchBandwidth[DC__NUM_DPP__MAX];
	doubwe VInitPweFiwwY[DC__NUM_DPP__MAX];
	doubwe VInitPweFiwwC[DC__NUM_DPP__MAX];
	unsigned int MaxNumSwathY[DC__NUM_DPP__MAX];
	unsigned int MaxNumSwathC[DC__NUM_DPP__MAX];
	unsigned int VStawtup[DC__NUM_DPP__MAX];
	doubwe DSTYAftewScawew[DC__NUM_DPP__MAX];
	doubwe DSTXAftewScawew[DC__NUM_DPP__MAX];
	boow AwwowDWAMCwockChangeDuwingVBwank[DC__NUM_DPP__MAX];
	boow AwwowDWAMSewfWefweshDuwingVBwank[DC__NUM_DPP__MAX];
	doubwe VWatioPwefetchY[DC__NUM_DPP__MAX];
	doubwe VWatioPwefetchC[DC__NUM_DPP__MAX];
	doubwe DestinationWinesFowPwefetch[DC__NUM_DPP__MAX];
	doubwe DestinationWinesToWequestVMInVBwank[DC__NUM_DPP__MAX];
	doubwe DestinationWinesToWequestWowInVBwank[DC__NUM_DPP__MAX];
	doubwe MinTTUVBwank[DC__NUM_DPP__MAX];
	doubwe BytePewPixewDETY[DC__NUM_DPP__MAX];
	doubwe BytePewPixewDETC[DC__NUM_DPP__MAX];
	doubwe SwathWidthY[DC__NUM_DPP__MAX];
	doubwe SwathWidthSingweDPPY[DC__NUM_DPP__MAX];
	doubwe CuwsowWequestDewivewyTime[DC__NUM_DPP__MAX];
	doubwe CuwsowWequestDewivewyTimePwefetch[DC__NUM_DPP__MAX];
	doubwe WeadBandwidthPwaneWuma[DC__NUM_DPP__MAX];
	doubwe WeadBandwidthPwaneChwoma[DC__NUM_DPP__MAX];
	doubwe DispwayPipeWineDewivewyTimeWumaPwefetch[DC__NUM_DPP__MAX];
	doubwe DispwayPipeWineDewivewyTimeChwomaPwefetch[DC__NUM_DPP__MAX];
	doubwe DispwayPipeWequestDewivewyTimeWumaPwefetch[DC__NUM_DPP__MAX];
	doubwe DispwayPipeWequestDewivewyTimeChwomaPwefetch[DC__NUM_DPP__MAX];
	doubwe PixewPTEBytesPewWow[DC__NUM_DPP__MAX];
	doubwe PDEAndMetaPTEBytesFwame[DC__NUM_DPP__MAX];
	doubwe MetaWowByte[DC__NUM_DPP__MAX];
	doubwe PwefetchSouwceWinesY[DC__NUM_DPP__MAX];
	doubwe WequiwedPwefetchPixDataBWWuma[DC__NUM_DPP__MAX];
	doubwe WequiwedPwefetchPixDataBWChwoma[DC__NUM_DPP__MAX];
	doubwe PwefetchSouwceWinesC[DC__NUM_DPP__MAX];
	doubwe PSCW_THWOUGHPUT_WUMA[DC__NUM_DPP__MAX];
	doubwe PSCW_THWOUGHPUT_CHWOMA[DC__NUM_DPP__MAX];
	doubwe DSCCWK_cawcuwated[DC__NUM_DPP__MAX];
	unsigned int DSCDeway[DC__NUM_DPP__MAX];
	unsigned int MaxVStawtupWines[DC__NUM_DPP__MAX];
	doubwe DPPCWKUsingSingweDPP[DC__NUM_DPP__MAX];
	doubwe DPPCWK[DC__NUM_DPP__MAX];
	unsigned int DCCYMaxUncompwessedBwock[DC__NUM_DPP__MAX];
	unsigned int DCCYMaxCompwessedBwock[DC__NUM_DPP__MAX];
	unsigned int DCCYIndependent64ByteBwock[DC__NUM_DPP__MAX];
	doubwe MaximumDCCCompwessionYSuwface[DC__NUM_DPP__MAX];
	unsigned int BwockHeight256BytesY[DC__NUM_DPP__MAX];
	unsigned int BwockHeight256BytesC[DC__NUM_DPP__MAX];
	unsigned int BwockWidth256BytesY[DC__NUM_DPP__MAX];
	unsigned int BwockWidth256BytesC[DC__NUM_DPP__MAX];
	doubwe XFCSwaveVUpdateOffset[DC__NUM_DPP__MAX];
	doubwe XFCSwaveVupdateWidth[DC__NUM_DPP__MAX];
	doubwe XFCSwaveVWeadyOffset[DC__NUM_DPP__MAX];
	doubwe XFCTwansfewDeway[DC__NUM_DPP__MAX];
	doubwe XFCPwechawgeDeway[DC__NUM_DPP__MAX];
	doubwe XFCWemoteSuwfaceFwipWatency[DC__NUM_DPP__MAX];
	doubwe XFCPwefetchMawgin[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_width_wuma_ub[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_width_chwoma_ub[DC__NUM_DPP__MAX];
	doubwe FuwwDETBuffewingTimeY[DC__NUM_DPP__MAX];                     // WM
	doubwe FuwwDETBuffewingTimeC[DC__NUM_DPP__MAX];                     // WM
	doubwe DST_Y_PEW_PTE_WOW_NOM_W[DC__NUM_DPP__MAX];
	doubwe DST_Y_PEW_PTE_WOW_NOM_C[DC__NUM_DPP__MAX];
	doubwe DST_Y_PEW_META_WOW_NOM_W[DC__NUM_DPP__MAX];
	doubwe TimePewMetaChunkNominaw[DC__NUM_DPP__MAX];
	doubwe TimePewMetaChunkVBwank[DC__NUM_DPP__MAX];
	doubwe TimePewMetaChunkFwip[DC__NUM_DPP__MAX];
	unsigned int swath_width_wuma_ub[DC__NUM_DPP__MAX];
	unsigned int swath_width_chwoma_ub[DC__NUM_DPP__MAX];
	unsigned int PixewPTEWeqWidthY[DC__NUM_DPP__MAX];
	unsigned int PixewPTEWeqHeightY[DC__NUM_DPP__MAX];
	unsigned int PTEWequestSizeY[DC__NUM_DPP__MAX];
	unsigned int PixewPTEWeqWidthC[DC__NUM_DPP__MAX];
	unsigned int PixewPTEWeqHeightC[DC__NUM_DPP__MAX];
	unsigned int PTEWequestSizeC[DC__NUM_DPP__MAX];
	doubwe time_pew_pte_gwoup_nom_wuma[DC__NUM_DPP__MAX];
	doubwe time_pew_pte_gwoup_nom_chwoma[DC__NUM_DPP__MAX];
	doubwe time_pew_pte_gwoup_vbwank_wuma[DC__NUM_DPP__MAX];
	doubwe time_pew_pte_gwoup_vbwank_chwoma[DC__NUM_DPP__MAX];
	doubwe time_pew_pte_gwoup_fwip_wuma[DC__NUM_DPP__MAX];
	doubwe time_pew_pte_gwoup_fwip_chwoma[DC__NUM_DPP__MAX];
	doubwe TimePewVMGwoupVBwank[DC__NUM_DPP__MAX];
	doubwe TimePewVMGwoupFwip[DC__NUM_DPP__MAX];
	doubwe TimePewVMWequestVBwank[DC__NUM_DPP__MAX];
	doubwe TimePewVMWequestFwip[DC__NUM_DPP__MAX];
	unsigned int dpde0_bytes_pew_fwame_ub_w[DC__NUM_DPP__MAX];
	unsigned int meta_pte_bytes_pew_fwame_ub_w[DC__NUM_DPP__MAX];
	unsigned int dpde0_bytes_pew_fwame_ub_c[DC__NUM_DPP__MAX];
	unsigned int meta_pte_bytes_pew_fwame_ub_c[DC__NUM_DPP__MAX];
	doubwe WinesToFinishSwathTwansfewStuttewCwiticawPwane;
	unsigned int BytePewPixewYCwiticawPwane;
	doubwe SwathWidthYCwiticawPwane;
	doubwe WinesInDETY[DC__NUM_DPP__MAX];
	doubwe WinesInDETYWoundedDownToSwath[DC__NUM_DPP__MAX];

	doubwe SwathWidthSingweDPPC[DC__NUM_DPP__MAX];
	doubwe SwathWidthC[DC__NUM_DPP__MAX];
	unsigned int BytePewPixewY[DC__NUM_DPP__MAX];
	unsigned int BytePewPixewC[DC__NUM_DPP__MAX];
	unsigned int dummyintegew1;
	unsigned int dummyintegew2;
	doubwe FinawDWAMCwockChangeWatency;
	doubwe Tdmdw_vm[DC__NUM_DPP__MAX];
	doubwe Tdmdw[DC__NUM_DPP__MAX];
	doubwe TSetup[DC__NUM_DPP__MAX];
	unsigned int ThisVStawtup;
	boow WwitebackAwwowDWAMCwockChangeEndPosition[DC__NUM_DPP__MAX];
	doubwe DST_Y_PEW_META_WOW_NOM_C[DC__NUM_DPP__MAX];
	doubwe TimePewChwomaMetaChunkNominaw[DC__NUM_DPP__MAX];
	doubwe TimePewChwomaMetaChunkVBwank[DC__NUM_DPP__MAX];
	doubwe TimePewChwomaMetaChunkFwip[DC__NUM_DPP__MAX];
	unsigned int DCCCMaxUncompwessedBwock[DC__NUM_DPP__MAX];
	unsigned int DCCCMaxCompwessedBwock[DC__NUM_DPP__MAX];
	doubwe VStawtupMawgin;
	boow NotEnoughTimeFowDynamicMetadata[DC__NUM_DPP__MAX];

	/* Missing fwom VBA */
	unsigned int MaximumMaxVStawtupWines;
	doubwe FabwicAndDWAMBandwidth;
	doubwe WinesInDETWuma;
	doubwe WinesInDETChwoma;
	unsigned int ImmediateFwipBytes[DC__NUM_DPP__MAX];
	unsigned int WinesInDETC[DC__NUM_DPP__MAX];
	unsigned int WinesInDETCWoundedDownToSwath[DC__NUM_DPP__MAX];
	doubwe UwgentWatencySuppowtUsPewState[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe UwgentWatencySuppowtUs[DC__NUM_DPP__MAX];
	doubwe FabwicAndDWAMBandwidthPewState[DC__VOWTAGE_STATES];
	boow UwgentWatencySuppowt[DC__VOWTAGE_STATES][2];
	unsigned int SwathWidthYPewState[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int SwathHeightYPewState[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe quaw_wow_bw[DC__NUM_DPP__MAX];
	doubwe pwefetch_wow_bw[DC__NUM_DPP__MAX];
	doubwe pwefetch_vm_bw[DC__NUM_DPP__MAX];

	doubwe PTEGwoupSize;
	unsigned int PDEPwocessingBufIn64KBWeqs;

	doubwe MaxTotawVActiveWDBandwidth;
	boow DoUwgentWatencyAdjustment;
	doubwe UwgentWatencyAdjustmentFabwicCwockComponent;
	doubwe UwgentWatencyAdjustmentFabwicCwockWefewence;
	doubwe MinUwgentWatencySuppowtUs;
	doubwe MinFuwwDETBuffewingTime;
	doubwe AvewageWeadBandwidthGBytePewSecond;
	boow   FiwstMainPwane;
	boow NotEnoughDETSwathFiwwWatencyHiding;

	unsigned int ViewpowtWidthChwoma[DC__NUM_DPP__MAX];
	unsigned int ViewpowtHeightChwoma[DC__NUM_DPP__MAX];
	doubwe HWatioChwoma[DC__NUM_DPP__MAX];
	doubwe VWatioChwoma[DC__NUM_DPP__MAX];
	int WwitebackSouwceWidth[DC__NUM_DPP__MAX];

	boow ModeIsSuppowted;
	boow ODMCombine4To1Suppowted;

	unsigned int SuwfaceWidthY[DC__NUM_DPP__MAX];
	unsigned int SuwfaceWidthC[DC__NUM_DPP__MAX];
	unsigned int SuwfaceHeightY[DC__NUM_DPP__MAX];
	unsigned int SuwfaceHeightC[DC__NUM_DPP__MAX];
	unsigned int WwitebackHTaps[DC__NUM_DPP__MAX];
	unsigned int WwitebackVTaps[DC__NUM_DPP__MAX];
	boow DSCEnabwe[DC__NUM_DPP__MAX];

	doubwe DWAMCwockChangeWatencyOvewwide;

	doubwe GPUVMMinPageSize;
	doubwe HostVMMinPageSize;

	boow   MPCCombineEnabwe[DC__NUM_DPP__MAX];
	unsigned int HostVMMaxNonCachedPageTabweWevews;
	boow   DynamicMetadataVMEnabwed;
	doubwe       WwitebackIntewfaceBuffewSize;
	doubwe       WwitebackWineBuffewSize;

	doubwe DCCWateWuma[DC__NUM_DPP__MAX];
	doubwe DCCWateChwoma[DC__NUM_DPP__MAX];

	doubwe PHYCWKD18PewState[DC__VOWTAGE_STATES];

	boow WwitebackSuppowtIntewweaveAndUsingWhoweBuffewFowASingweStweam;
	boow NumbewOfHDMIFWWSuppowt;
	unsigned int MaxNumHDMIFWWOutputs;
	int    AudioSampweWate[DC__NUM_DPP__MAX];
	int    AudioSampweWayout[DC__NUM_DPP__MAX];

	int PewcentMawginOvewMinimumWequiwedDCFCWK;
	boow DynamicMetadataSuppowted[DC__VOWTAGE_STATES][2];
	enum immediate_fwip_wequiwement ImmediateFwipWequiwement[DC__NUM_DPP__MAX];
	unsigned int DETBuffewSizeYThisState[DC__NUM_DPP__MAX];
	unsigned int DETBuffewSizeCThisState[DC__NUM_DPP__MAX];
	boow NoUwgentWatencyHiding[DC__NUM_DPP__MAX];
	boow NoUwgentWatencyHidingPwe[DC__NUM_DPP__MAX];
	int swath_width_wuma_ub_this_state[DC__NUM_DPP__MAX];
	int swath_width_chwoma_ub_this_state[DC__NUM_DPP__MAX];
	doubwe UwgWatency[DC__VOWTAGE_STATES];
	doubwe VActiveCuwsowBandwidth[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe VActivePixewBandwidth[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow NoTimeFowPwefetch[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow NoTimeFowDynamicMetadata[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe dpte_wow_bandwidth[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe meta_wow_bandwidth[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe DETBuffewSizeYAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe DETBuffewSizeCAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int swath_width_wuma_ub_aww_states[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int swath_width_chwoma_ub_aww_states[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	boow NotUwgentWatencyHiding[DC__VOWTAGE_STATES][2];
	unsigned int SwathHeightYAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int SwathHeightCAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int SwathWidthYAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int SwathWidthCAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	doubwe TotawDPTEWowBandwidth[DC__VOWTAGE_STATES][2];
	doubwe TotawMetaWowBandwidth[DC__VOWTAGE_STATES][2];
	doubwe TotawVActiveCuwsowBandwidth[DC__VOWTAGE_STATES][2];
	doubwe TotawVActivePixewBandwidth[DC__VOWTAGE_STATES][2];
	doubwe WwitebackDewayTime[DC__NUM_DPP__MAX];
	unsigned int DCCYIndependentBwock[DC__NUM_DPP__MAX];
	unsigned int DCCCIndependentBwock[DC__NUM_DPP__MAX];
	unsigned int dummyintegew17;
	unsigned int dummyintegew18;
	unsigned int dummyintegew19;
	unsigned int dummyintegew20;
	unsigned int dummyintegew21;
	unsigned int dummyintegew22;
	unsigned int dummyintegew23;
	unsigned int dummyintegew24;
	unsigned int dummyintegew25;
	unsigned int dummyintegew26;
	unsigned int dummyintegew27;
	unsigned int dummyintegew28;
	unsigned int dummyintegew29;
	boow dummystwing[DC__NUM_DPP__MAX];
	doubwe BPP;
	enum odm_combine_powicy ODMCombinePowicy;
	boow UseMinimumWequiwedDCFCWK;
	boow CwampMinDCFCWK;
	boow AwwowDwamCwockChangeOneDispwayVactive;

	doubwe MaxAvewagePewcentOfIdeawFabwicAndSDPPowtBWDispwayCanUseInNowmawSystemOpewation;
	doubwe PewcentOfIdeawFabwicAndSDPPowtBWWeceivedAftewUwgWatency;
	doubwe PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencyPixewMixedWithVMData;
	doubwe PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencyVMDataOnwy;
	doubwe PewcentOfIdeawDWAMBWWeceivedAftewUwgWatencyPixewDataOnwy;
	doubwe SWExitZ8Time;
	doubwe SWEntewPwusExitZ8Time;
	doubwe Z8StuttewExitWatewmawk;
	doubwe Z8StuttewEntewPwusExitWatewmawk;
	doubwe Z8StuttewEfficiencyNotIncwudingVBwank;
	doubwe Z8StuttewEfficiency;
	doubwe DCCFwactionOfZewoSizeWequestsWuma[DC__NUM_DPP__MAX];
	doubwe DCCFwactionOfZewoSizeWequestsChwoma[DC__NUM_DPP__MAX];
	doubwe UwgBuwstFactowCuwsow[DC__NUM_DPP__MAX];
	doubwe UwgBuwstFactowWuma[DC__NUM_DPP__MAX];
	doubwe UwgBuwstFactowChwoma[DC__NUM_DPP__MAX];
	doubwe UwgBuwstFactowCuwsowPwe[DC__NUM_DPP__MAX];
	doubwe UwgBuwstFactowWumaPwe[DC__NUM_DPP__MAX];
	doubwe UwgBuwstFactowChwomaPwe[DC__NUM_DPP__MAX];
	boow NotUwgentWatencyHidingPwe[DC__NUM_DPP__MAX];
	boow WinkCapacitySuppowt[DC__VOWTAGE_STATES];
	boow VWEADY_AT_OW_AFTEW_VSYNC[DC__NUM_DPP__MAX];
	unsigned int MIN_DST_Y_NEXT_STAWT[DC__NUM_DPP__MAX];
	unsigned int VFwontPowch[DC__NUM_DPP__MAX];
	int ConfigWetuwnBuffewSizeInKByte;
	enum unbounded_wequesting_powicy UseUnboundedWequesting;
	int CompwessedBuffewSegmentSizeInkByte;
	int CompwessedBuffewSizeInkByte;
	int MetaFIFOSizeInKEntwies;
	int ZewoSizeBuffewEntwies;
	int COMPBUF_WESEWVED_SPACE_64B;
	int COMPBUF_WESEWVED_SPACE_ZS;
	boow UnboundedWequestEnabwed;
	boow DSC422NativeSuppowt;
	boow NoEnoughUwgentWatencyHiding;
	boow NoEnoughUwgentWatencyHidingPwe;
	int NumbewOfStuttewBuwstsPewFwame;
	int Z8NumbewOfStuttewBuwstsPewFwame;
	unsigned int MaximumDSCBitsPewComponent;
	unsigned int NotEnoughUwgentWatencyHidingA[DC__VOWTAGE_STATES][2];
	doubwe WeadBandwidthSuwfaceWuma[DC__NUM_DPP__MAX];
	doubwe WeadBandwidthSuwfaceChwoma[DC__NUM_DPP__MAX];
	doubwe SuwfaceWequiwedDISPCWKWithoutODMCombine;
	doubwe SuwfaceWequiwedDISPCWK;
	doubwe MinActiveFCWKChangeWatencySuppowted;
	int MinVowtageWevew;
	int MaxVowtageWevew;
	unsigned int TotawNumbewOfSingweDPPSuwfaces[DC__VOWTAGE_STATES][2];
	unsigned int CompwessedBuffewSizeInkByteAwwStates[DC__VOWTAGE_STATES][2];
	unsigned int DETBuffewSizeInKByteAwwStates[DC__VOWTAGE_STATES][2][DC__NUM_DPP__MAX];
	unsigned int DETBuffewSizeInKByteThisState[DC__NUM_DPP__MAX];
	unsigned int SuwfaceSizeInMAWW[DC__NUM_DPP__MAX];
	boow ExceededMAWWSize;
	boow PTE_BUFFEW_MODE[DC__NUM_DPP__MAX];
	unsigned int BIGK_FWAGMENT_SIZE[DC__NUM_DPP__MAX];
	unsigned int CompwessedBuffewSizeInkByteThisState;
	enum dm_fcwock_change_suppowt FCWKChangeSuppowt[DC__VOWTAGE_STATES][2];
	boow USWWetwainingSuppowt[DC__VOWTAGE_STATES][2];
	enum dm_use_maww_fow_pstate_change_mode UsesMAWWFowPStateChange[DC__NUM_DPP__MAX];
	boow UnboundedWequestEnabwedAwwStates[DC__VOWTAGE_STATES][2];
	boow SingweDPPViewpowtSizeSuppowtPewSuwface[DC__NUM_DPP__MAX];
	enum dm_use_maww_fow_static_scween_mode UseMAWWFowStaticScween[DC__NUM_DPP__MAX];
	boow UnboundedWequestEnabwedThisState;
	boow DWAMCwockChangeWequiwementFinaw;
	boow FCWKChangeWequiwementFinaw;
	boow USWWetwainingWequiwedFinaw;
	unsigned int DETSizeOvewwide[DC__NUM_DPP__MAX];
	unsigned int nomDETInKByte;
	enum mpc_combine_affinity  MPCCombineUse[DC__NUM_DPP__MAX];
	boow MPCCombineMethodIncompatibwe;
	unsigned int WequiwedSwots[DC__VOWTAGE_STATES][DC__NUM_DPP__MAX];
	boow ExceededMuwtistweamSwots[DC__VOWTAGE_STATES];
	enum odm_combine_powicy ODMUse[DC__NUM_DPP__MAX];
	unsigned int OutputMuwtistweamId[DC__NUM_DPP__MAX];
	boow OutputMuwtistweamEn[DC__NUM_DPP__MAX];
	boow UsesMAWWFowStaticScween[DC__NUM_DPP__MAX];
	doubwe MaxActiveDWAMCwockChangeWatencySuppowted[DC__NUM_DPP__MAX];
	doubwe WwitebackAwwowFCWKChangeEndPosition[DC__NUM_DPP__MAX];
	boow PTEBuffewSizeNotExceededPewState[DC__NUM_DPP__MAX]; // new in DMW32
	boow DCCMetaBuffewSizeNotExceededPewState[DC__NUM_DPP__MAX]; // new in DMW32
	boow NotEnoughDSCSwices[DC__VOWTAGE_STATES];
	boow PixewsPewWinePewDSCUnitSuppowt[DC__VOWTAGE_STATES];
	boow DCCMetaBuffewSizeNotExceeded[DC__VOWTAGE_STATES][2];
	unsigned int dpte_wow_height_wineaw[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_height_wineaw_chwoma[DC__NUM_DPP__MAX];
	unsigned int BwockHeightY[DC__NUM_DPP__MAX];
	unsigned int BwockHeightC[DC__NUM_DPP__MAX];
	unsigned int BwockWidthY[DC__NUM_DPP__MAX];
	unsigned int BwockWidthC[DC__NUM_DPP__MAX];
	unsigned int SubViewpowtWinesNeededInMAWW[DC__NUM_DPP__MAX];
	boow VActiveBandwithSuppowt[DC__VOWTAGE_STATES][2];
	boow NotEnoughDETSwathFiwwWatencyHidingPewState[DC__VOWTAGE_STATES][2];
	stwuct dummy_vaws dummy_vaws;
};

boow CawcuwateMinAndMaxPwefetchMode(
		enum sewf_wefwesh_affinity AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank,
		unsigned int *MinPwefetchMode,
		unsigned int *MaxPwefetchMode);

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
		unsigned int WwitebackChwomaWineBuffewWidth);

#endif /* _DMW2_DISPWAY_MODE_VBA_H_ */
