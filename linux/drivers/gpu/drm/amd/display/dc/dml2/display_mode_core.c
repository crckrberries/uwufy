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

#incwude "dispway_mode_cowe.h"
#incwude "dispway_mode_utiw.h"
#incwude "dispway_mode_wib_defines.h"

#incwude "dmw_assewt.h"

#define DMW2_MAX_FMT_420_BUFFEW_WIDTH 4096
// ---------------------------
//  Decwawation Begins
// ---------------------------
static void CawcuwateBytePewPixewAndBwockSizes(
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	enum dmw_swizzwe_mode SuwfaceTiwing,
	// Output
	dmw_uint_t *BytePewPixewY,
	dmw_uint_t *BytePewPixewC,
	dmw_fwoat_t *BytePewPixewDETY,
	dmw_fwoat_t *BytePewPixewDETC,
	dmw_uint_t *BwockHeight256BytesY,
	dmw_uint_t *BwockHeight256BytesC,
	dmw_uint_t *BwockWidth256BytesY,
	dmw_uint_t *BwockWidth256BytesC,
	dmw_uint_t *MacwoTiweHeightY,
	dmw_uint_t *MacwoTiweHeightC,
	dmw_uint_t *MacwoTiweWidthY,
	dmw_uint_t *MacwoTiweWidthC);

static dmw_fwoat_t CawcuwateWwiteBackDISPCWK(
	enum dmw_souwce_fowmat_cwass WwitebackPixewFowmat,
	dmw_fwoat_t PixewCwock,
	dmw_fwoat_t WwitebackHWatio,
	dmw_fwoat_t WwitebackVWatio,
	dmw_uint_t WwitebackHTaps,
	dmw_uint_t WwitebackVTaps,
	dmw_uint_t WwitebackSouwceWidth,
	dmw_uint_t WwitebackDestinationWidth,
	dmw_uint_t HTotaw,
	dmw_uint_t WwitebackWineBuffewSize,
	dmw_fwoat_t DISPCWKDPPCWKVCOSpeed);

static void CawcuwateVMWowAndSwath(
	stwuct dispway_mode_wib_scwatch_st *s,
	stwuct CawcuwateVMWowAndSwath_pawams_st *p);

static void CawcuwateOutputWink(
	dmw_fwoat_t PHYCWKPewState,
	dmw_fwoat_t PHYCWKD18PewState,
	dmw_fwoat_t PHYCWKD32PewState,
	dmw_fwoat_t Downspweading,
	dmw_boow_t IsMainSuwfaceUsingTheIndicatedTiming,
	enum dmw_output_encodew_cwass Output,
	enum dmw_output_fowmat_cwass OutputFowmat,
	dmw_uint_t HTotaw,
	dmw_uint_t HActive,
	dmw_fwoat_t PixewCwockBackEnd,
	dmw_fwoat_t FowcedOutputWinkBPP,
	dmw_uint_t DSCInputBitPewComponent,
	dmw_uint_t NumbewOfDSCSwices,
	dmw_fwoat_t AudioSampweWate,
	dmw_uint_t AudioSampweWayout,
	enum dmw_odm_mode ODMModeNoDSC,
	enum dmw_odm_mode ODMModeDSC,
	enum dmw_dsc_enabwe DSCEnabwe,
	dmw_uint_t OutputWinkDPWanes,
	enum dmw_output_wink_dp_wate OutputWinkDPWate,

	// Output
	dmw_boow_t *WequiwesDSC,
	dmw_boow_t *WequiwesFEC,
	dmw_fwoat_t *OutBpp,
	enum dmw_output_type_and_wate__type *OutputType,
	enum dmw_output_type_and_wate__wate *OutputWate,
	dmw_uint_t *WequiwedSwots);

static void CawcuwateODMMode(
	dmw_uint_t MaximumPixewsPewWinePewDSCUnit,
	dmw_uint_t HActive,
	enum dmw_output_encodew_cwass Output,
	enum dmw_output_fowmat_cwass OutputFowmat,
	enum dmw_odm_use_powicy ODMUse,
	dmw_fwoat_t StateDispcwk,
	dmw_fwoat_t MaxDispcwk,
	dmw_boow_t DSCEnabwe,
	dmw_uint_t TotawNumbewOfActiveDPP,
	dmw_uint_t MaxNumDPP,
	dmw_fwoat_t PixewCwock,
	dmw_fwoat_t DISPCWKDPPCWKDSCCWKDownSpweading,
	dmw_fwoat_t DISPCWKWampingMawgin,
	dmw_fwoat_t DISPCWKDPPCWKVCOSpeed,

	// Output
	dmw_boow_t *TotawAvaiwabwePipesSuppowt,
	dmw_uint_t *NumbewOfDPP,
	enum dmw_odm_mode *ODMMode,
	dmw_fwoat_t *WequiwedDISPCWKPewSuwface);

static dmw_fwoat_t CawcuwateWequiwedDispcwk(
	enum dmw_odm_mode ODMMode,
	dmw_fwoat_t PixewCwock,
	dmw_fwoat_t DISPCWKDPPCWKDSCCWKDownSpweading,
	dmw_fwoat_t DISPCWKWampingMawgin,
	dmw_fwoat_t DISPCWKDPPCWKVCOSpeed,
	dmw_fwoat_t MaxDispcwkSingwe);

static void CawcuwateSingwePipeDPPCWKAndSCWThwoughput(
	dmw_fwoat_t HWatio,
	dmw_fwoat_t HWatioChwoma,
	dmw_fwoat_t VWatio,
	dmw_fwoat_t VWatioChwoma,
	dmw_fwoat_t MaxDCHUBToPSCWThwoughput,
	dmw_fwoat_t MaxPSCWToWBThwoughput,
	dmw_fwoat_t PixewCwock,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	dmw_uint_t HTaps,
	dmw_uint_t HTapsChwoma,
	dmw_uint_t VTaps,
	dmw_uint_t VTapsChwoma,

	// Output
	dmw_fwoat_t *PSCW_THWOUGHPUT,
	dmw_fwoat_t *PSCW_THWOUGHPUT_CHWOMA,
	dmw_fwoat_t *DPPCWKUsingSingweDPP);

static void CawcuwateDPPCWK(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_fwoat_t DISPCWKDPPCWKDSCCWKDownSpweading,
	dmw_fwoat_t DISPCWKDPPCWKVCOSpeed,
	dmw_fwoat_t DPPCWKUsingSingweDPP[],
	dmw_uint_t DPPPewSuwface[],

	// Output
	dmw_fwoat_t *GwobawDPPCWK,
	dmw_fwoat_t Dppcwk[]);

static void CawcuwateMAWWUseFowStaticScween(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_uint_t MAWWAwwocatedFowDCNFinaw,
	enum dmw_use_maww_fow_static_scween_mode *UseMAWWFowStaticScween,
	dmw_uint_t SuwfaceSizeInMAWW[],
	dmw_boow_t one_wow_pew_fwame_fits_in_buffew[],

	// Output
	dmw_boow_t UsesMAWWFowStaticScween[]);

static dmw_uint_t dscceComputeDeway(
	dmw_uint_t bpc,
	dmw_fwoat_t BPP,
	dmw_uint_t swiceWidth,
	dmw_uint_t numSwices,
	enum dmw_output_fowmat_cwass pixewFowmat,
	enum dmw_output_encodew_cwass Output);

static dmw_uint_t dscComputeDeway(enum dmw_output_fowmat_cwass pixewFowmat,
	enum dmw_output_encodew_cwass Output);

static dmw_boow_t CawcuwatePwefetchScheduwe(stwuct dispway_mode_wib_scwatch_st *scwatch,
	stwuct CawcuwatePwefetchScheduwe_pawams_st *p);

static dmw_fwoat_t WoundToDFSGwanuwawity(dmw_fwoat_t Cwock, dmw_boow_t wound_up, dmw_fwoat_t VCOSpeed);

static void CawcuwateDCCConfiguwation(
	dmw_boow_t DCCEnabwed,
	dmw_boow_t DCCPwogwammingAssumesScanDiwectionUnknown,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	dmw_uint_t SuwfaceWidthWuma,
	dmw_uint_t SuwfaceWidthChwoma,
	dmw_uint_t SuwfaceHeightWuma,
	dmw_uint_t SuwfaceHeightChwoma,
	dmw_uint_t nomDETInKByte,
	dmw_uint_t WequestHeight256ByteWuma,
	dmw_uint_t WequestHeight256ByteChwoma,
	enum dmw_swizzwe_mode TiwingFowmat,
	dmw_uint_t BytePewPixewY,
	dmw_uint_t BytePewPixewC,
	dmw_fwoat_t BytePewPixewDETY,
	dmw_fwoat_t BytePewPixewDETC,
	enum dmw_wotation_angwe SouwceScan,
	// Output
	dmw_uint_t *MaxUncompwessedBwockWuma,
	dmw_uint_t *MaxUncompwessedBwockChwoma,
	dmw_uint_t *MaxCompwessedBwockWuma,
	dmw_uint_t *MaxCompwessedBwockChwoma,
	dmw_uint_t *IndependentBwockWuma,
	dmw_uint_t *IndependentBwockChwoma);

static dmw_uint_t CawcuwatePwefetchSouwceWines(
	dmw_fwoat_t VWatio,
	dmw_uint_t VTaps,
	dmw_boow_t Intewwace,
	dmw_boow_t PwogwessiveToIntewwaceUnitInOPP,
	dmw_uint_t SwathHeight,
	enum dmw_wotation_angwe SouwceScan,
	dmw_boow_t ViewpowtStationawy,
	dmw_uint_t SwathWidth,
	dmw_uint_t ViewpowtHeight,
	dmw_uint_t ViewpowtXStawt,
	dmw_uint_t ViewpowtYStawt,

	// Output
	dmw_uint_t *VInitPweFiww,
	dmw_uint_t *MaxNumSwath);

static dmw_uint_t CawcuwateVMAndWowBytes(
	dmw_boow_t ViewpowtStationawy,
	dmw_boow_t DCCEnabwe,
	dmw_uint_t NumbewOfDPPs,
	dmw_uint_t BwockHeight256Bytes,
	dmw_uint_t BwockWidth256Bytes,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	dmw_uint_t SuwfaceTiwing,
	dmw_uint_t BytePewPixew,
	enum dmw_wotation_angwe SouwceScan,
	dmw_uint_t SwathWidth,
	dmw_uint_t ViewpowtHeight,
	dmw_uint_t ViewpowtXStawt,
	dmw_uint_t ViewpowtYStawt,
	dmw_boow_t GPUVMEnabwe,
	dmw_uint_t GPUVMMaxPageTabweWevews,
	dmw_uint_t GPUVMMinPageSizeKBytes,
	dmw_uint_t PTEBuffewSizeInWequests,
	dmw_uint_t Pitch,
	dmw_uint_t DCCMetaPitch,
	dmw_uint_t MacwoTiweWidth,
	dmw_uint_t MacwoTiweHeight,

	// Output
	dmw_uint_t *MetaWowByte,
	dmw_uint_t *PixewPTEBytesPewWow,
	dmw_uint_t *PixewPTEBytesPewWowStowage, // fow PTE buffew size check
	dmw_uint_t *dpte_wow_width_ub,
	dmw_uint_t *dpte_wow_height,
	dmw_uint_t *dpte_wow_height_wineaw,
	dmw_uint_t *PixewPTEBytesPewWow_one_wow_pew_fwame,
	dmw_uint_t *dpte_wow_width_ub_one_wow_pew_fwame,
	dmw_uint_t *dpte_wow_height_one_wow_pew_fwame,
	dmw_uint_t *MetaWequestWidth,
	dmw_uint_t *MetaWequestHeight,
	dmw_uint_t *meta_wow_width,
	dmw_uint_t *meta_wow_height,
	dmw_uint_t *PixewPTEWeqWidth,
	dmw_uint_t *PixewPTEWeqHeight,
	dmw_uint_t *PTEWequestSize,
	dmw_uint_t *DPDE0BytesFwame,
	dmw_uint_t *MetaPTEBytesFwame);

static dmw_fwoat_t CawcuwateTWait(
	dmw_uint_t PwefetchMode,
	enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
	dmw_boow_t SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
	dmw_boow_t DWWDispway,
	dmw_fwoat_t DWAMCwockChangeWatency,
	dmw_fwoat_t FCWKChangeWatency,
	dmw_fwoat_t UwgentWatency,
	dmw_fwoat_t SWEntewPwusExitTime);

static void CawcuwatePwefetchMode(
	enum dmw_pwefetch_modes AwwowFowPStateChangeOwStuttewInVBwank,
	dmw_uint_t *MinPwefetchMode,
	dmw_uint_t *MaxPwefetchMode);

static void CawcuwateWowBandwidth(
	dmw_boow_t GPUVMEnabwe,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	dmw_fwoat_t VWatio,
	dmw_fwoat_t VWatioChwoma,
	dmw_boow_t DCCEnabwe,
	dmw_fwoat_t WineTime,
	dmw_uint_t MetaWowByteWuma,
	dmw_uint_t MetaWowByteChwoma,
	dmw_uint_t meta_wow_height_wuma,
	dmw_uint_t meta_wow_height_chwoma,
	dmw_uint_t PixewPTEBytesPewWowWuma,
	dmw_uint_t PixewPTEBytesPewWowChwoma,
	dmw_uint_t dpte_wow_height_wuma,
	dmw_uint_t dpte_wow_height_chwoma,
	// Output
	dmw_fwoat_t *meta_wow_bw,
	dmw_fwoat_t *dpte_wow_bw);

static void CawcuwateFwipScheduwe(
	dmw_fwoat_t HostVMInefficiencyFactow,
	dmw_fwoat_t UwgentExtwaWatency,
	dmw_fwoat_t UwgentWatency,
	dmw_uint_t GPUVMMaxPageTabweWevews,
	dmw_boow_t HostVMEnabwe,
	dmw_uint_t HostVMMaxNonCachedPageTabweWevews,
	dmw_boow_t GPUVMEnabwe,
	dmw_uint_t HostVMMinPageSize,
	dmw_fwoat_t PDEAndMetaPTEBytesPewFwame,
	dmw_fwoat_t MetaWowBytes,
	dmw_fwoat_t DPTEBytesPewWow,
	dmw_fwoat_t BandwidthAvaiwabweFowImmediateFwip,
	dmw_uint_t TotImmediateFwipBytes,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	dmw_fwoat_t WineTime,
	dmw_fwoat_t VWatio,
	dmw_fwoat_t VWatioChwoma,
	dmw_fwoat_t Tno_bw,
	dmw_boow_t DCCEnabwe,
	dmw_uint_t dpte_wow_height,
	dmw_uint_t meta_wow_height,
	dmw_uint_t dpte_wow_height_chwoma,
	dmw_uint_t meta_wow_height_chwoma,
	dmw_boow_t use_one_wow_fow_fwame_fwip,

	// Output
	dmw_fwoat_t *DestinationWinesToWequestVMInImmediateFwip,
	dmw_fwoat_t *DestinationWinesToWequestWowInImmediateFwip,
	dmw_fwoat_t *finaw_fwip_bw,
	dmw_boow_t *ImmediateFwipSuppowtedFowPipe);

static dmw_fwoat_t CawcuwateWwiteBackDeway(
	enum dmw_souwce_fowmat_cwass WwitebackPixewFowmat,
	dmw_fwoat_t WwitebackHWatio,
	dmw_fwoat_t WwitebackVWatio,
	dmw_uint_t WwitebackVTaps,
	dmw_uint_t WwitebackDestinationWidth,
	dmw_uint_t WwitebackDestinationHeight,
	dmw_uint_t WwitebackSouwceHeight,
	dmw_uint_t HTotaw);

static void CawcuwateVUpdateAndDynamicMetadataPawametews(
	dmw_uint_t MaxIntewDCNTiweWepeatews,
	dmw_fwoat_t Dppcwk,
	dmw_fwoat_t DISPCWK,
	dmw_fwoat_t DCFCwkDeepSweep,
	dmw_fwoat_t PixewCwock,
	dmw_uint_t HTotaw,
	dmw_uint_t VBwank,
	dmw_uint_t DynamicMetadataTwansmittedBytes,
	dmw_uint_t DynamicMetadataWinesBefoweActiveWequiwed,
	dmw_uint_t IntewwaceEnabwe,
	dmw_boow_t PwogwessiveToIntewwaceUnitInOPP,
	dmw_fwoat_t *TSetup,
	dmw_fwoat_t *Tdmbf,
	dmw_fwoat_t *Tdmec,
	dmw_fwoat_t *Tdmsks,
	dmw_uint_t *VUpdateOffsetPix,
	dmw_uint_t *VUpdateWidthPix,
	dmw_uint_t *VWeadyOffsetPix);

static void PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(stwuct dmw_dispway_cfg_st *dispway_cfg, dmw_boow_t ptoi_suppowted);

static dmw_fwoat_t TwuncToVawidBPP(
	dmw_fwoat_t WinkBitWate,
	dmw_uint_t Wanes,
	dmw_uint_t HTotaw,
	dmw_uint_t HActive,
	dmw_fwoat_t PixewCwock,
	dmw_fwoat_t DesiwedBPP,
	dmw_boow_t DSCEnabwe,
	enum dmw_output_encodew_cwass Output,
	enum dmw_output_fowmat_cwass Fowmat,
	dmw_uint_t DSCInputBitPewComponent,
	dmw_uint_t DSCSwices,
	dmw_uint_t AudioWate,
	dmw_uint_t AudioWayout,
	enum dmw_odm_mode ODMModeNoDSC,
	enum dmw_odm_mode ODMModeDSC,
	// Output
	dmw_uint_t *WequiwedSwotsSingwe);

static void CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt(
	stwuct dispway_mode_wib_scwatch_st *s,
	stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams_st *p);

static void CawcuwateDCFCWKDeepSweep(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_uint_t BytePewPixewY[],
	dmw_uint_t BytePewPixewC[],
	dmw_fwoat_t VWatio[],
	dmw_fwoat_t VWatioChwoma[],
	dmw_uint_t SwathWidthY[],
	dmw_uint_t SwathWidthC[],
	dmw_uint_t DPPPewSuwface[],
	dmw_fwoat_t HWatio[],
	dmw_fwoat_t HWatioChwoma[],
	dmw_fwoat_t PixewCwock[],
	dmw_fwoat_t PSCW_THWOUGHPUT[],
	dmw_fwoat_t PSCW_THWOUGHPUT_CHWOMA[],
	dmw_fwoat_t Dppcwk[],
	dmw_fwoat_t WeadBandwidthWuma[],
	dmw_fwoat_t WeadBandwidthChwoma[],
	dmw_uint_t WetuwnBusWidth,

	// Output
	dmw_fwoat_t *DCFCWKDeepSweep);

static void CawcuwateUwgentBuwstFactow(
	enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
	dmw_uint_t swath_width_wuma_ub,
	dmw_uint_t swath_width_chwoma_ub,
	dmw_uint_t SwathHeightY,
	dmw_uint_t SwathHeightC,
	dmw_fwoat_t WineTime,
	dmw_fwoat_t UwgentWatency,
	dmw_fwoat_t CuwsowBuffewSize,
	dmw_uint_t CuwsowWidth,
	dmw_uint_t CuwsowBPP,
	dmw_fwoat_t VWatio,
	dmw_fwoat_t VWatioC,
	dmw_fwoat_t BytePewPixewInDETY,
	dmw_fwoat_t BytePewPixewInDETC,
	dmw_uint_t DETBuffewSizeY,
	dmw_uint_t DETBuffewSizeC,
	// Output
	dmw_fwoat_t *UwgentBuwstFactowCuwsow,
	dmw_fwoat_t *UwgentBuwstFactowWuma,
	dmw_fwoat_t *UwgentBuwstFactowChwoma,
	dmw_boow_t *NotEnoughUwgentWatencyHiding);

static dmw_fwoat_t WequiwedDTBCWK(
	dmw_boow_t DSCEnabwe,
	dmw_fwoat_t PixewCwock,
	enum dmw_output_fowmat_cwass OutputFowmat,
	dmw_fwoat_t OutputBpp,
	dmw_uint_t DSCSwices,
	dmw_uint_t HTotaw,
	dmw_uint_t HActive,
	dmw_uint_t AudioWate,
	dmw_uint_t AudioWayoutSingwe);

static void UseMinimumDCFCWK(
	stwuct dispway_mode_wib_scwatch_st *scwatch,
	stwuct UseMinimumDCFCWK_pawams_st *p);

static void CawcuwatePixewDewivewyTimes(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_fwoat_t VWatio[],
	dmw_fwoat_t VWatioChwoma[],
	dmw_fwoat_t VWatioPwefetchY[],
	dmw_fwoat_t VWatioPwefetchC[],
	dmw_uint_t swath_width_wuma_ub[],
	dmw_uint_t swath_width_chwoma_ub[],
	dmw_uint_t DPPPewSuwface[],
	dmw_fwoat_t HWatio[],
	dmw_fwoat_t HWatioChwoma[],
	dmw_fwoat_t PixewCwock[],
	dmw_fwoat_t PSCW_THWOUGHPUT[],
	dmw_fwoat_t PSCW_THWOUGHPUT_CHWOMA[],
	dmw_fwoat_t Dppcwk[],
	dmw_uint_t BytePewPixewC[],
	enum dmw_wotation_angwe SouwceScan[],
	dmw_uint_t NumbewOfCuwsows[],
	dmw_uint_t CuwsowWidth[],
	dmw_uint_t CuwsowBPP[],
	dmw_uint_t BwockWidth256BytesY[],
	dmw_uint_t BwockHeight256BytesY[],
	dmw_uint_t BwockWidth256BytesC[],
	dmw_uint_t BwockHeight256BytesC[],

	// Output
	dmw_fwoat_t DispwayPipeWineDewivewyTimeWuma[],
	dmw_fwoat_t DispwayPipeWineDewivewyTimeChwoma[],
	dmw_fwoat_t DispwayPipeWineDewivewyTimeWumaPwefetch[],
	dmw_fwoat_t DispwayPipeWineDewivewyTimeChwomaPwefetch[],
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeWuma[],
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeChwoma[],
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeWumaPwefetch[],
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeChwomaPwefetch[],
	dmw_fwoat_t CuwsowWequestDewivewyTime[],
	dmw_fwoat_t CuwsowWequestDewivewyTimePwefetch[]);

static void CawcuwateMetaAndPTETimes(
	dmw_boow_t use_one_wow_fow_fwame[],
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_boow_t GPUVMEnabwe,
	dmw_uint_t MetaChunkSize,
	dmw_uint_t MinMetaChunkSizeBytes,
	dmw_uint_t HTotaw[],
	dmw_fwoat_t VWatio[],
	dmw_fwoat_t VWatioChwoma[],
	dmw_fwoat_t DestinationWinesToWequestWowInVBwank[],
	dmw_fwoat_t DestinationWinesToWequestWowInImmediateFwip[],
	dmw_boow_t DCCEnabwe[],
	dmw_fwoat_t PixewCwock[],
	dmw_uint_t BytePewPixewY[],
	dmw_uint_t BytePewPixewC[],
	enum dmw_wotation_angwe SouwceScan[],
	dmw_uint_t dpte_wow_height[],
	dmw_uint_t dpte_wow_height_chwoma[],
	dmw_uint_t meta_wow_width[],
	dmw_uint_t meta_wow_width_chwoma[],
	dmw_uint_t meta_wow_height[],
	dmw_uint_t meta_wow_height_chwoma[],
	dmw_uint_t meta_weq_width[],
	dmw_uint_t meta_weq_width_chwoma[],
	dmw_uint_t meta_weq_height[],
	dmw_uint_t meta_weq_height_chwoma[],
	dmw_uint_t dpte_gwoup_bytes[],
	dmw_uint_t PTEWequestSizeY[],
	dmw_uint_t PTEWequestSizeC[],
	dmw_uint_t PixewPTEWeqWidthY[],
	dmw_uint_t PixewPTEWeqHeightY[],
	dmw_uint_t PixewPTEWeqWidthC[],
	dmw_uint_t PixewPTEWeqHeightC[],
	dmw_uint_t dpte_wow_width_wuma_ub[],
	dmw_uint_t dpte_wow_width_chwoma_ub[],

	// Output
	dmw_fwoat_t DST_Y_PEW_PTE_WOW_NOM_W[],
	dmw_fwoat_t DST_Y_PEW_PTE_WOW_NOM_C[],
	dmw_fwoat_t DST_Y_PEW_META_WOW_NOM_W[],
	dmw_fwoat_t DST_Y_PEW_META_WOW_NOM_C[],
	dmw_fwoat_t TimePewMetaChunkNominaw[],
	dmw_fwoat_t TimePewChwomaMetaChunkNominaw[],
	dmw_fwoat_t TimePewMetaChunkVBwank[],
	dmw_fwoat_t TimePewChwomaMetaChunkVBwank[],
	dmw_fwoat_t TimePewMetaChunkFwip[],
	dmw_fwoat_t TimePewChwomaMetaChunkFwip[],
	dmw_fwoat_t time_pew_pte_gwoup_nom_wuma[],
	dmw_fwoat_t time_pew_pte_gwoup_vbwank_wuma[],
	dmw_fwoat_t time_pew_pte_gwoup_fwip_wuma[],
	dmw_fwoat_t time_pew_pte_gwoup_nom_chwoma[],
	dmw_fwoat_t time_pew_pte_gwoup_vbwank_chwoma[],
	dmw_fwoat_t time_pew_pte_gwoup_fwip_chwoma[]);

static void CawcuwateVMGwoupAndWequestTimes(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_boow_t GPUVMEnabwe,
	dmw_uint_t GPUVMMaxPageTabweWevews,
	dmw_uint_t HTotaw[],
	dmw_uint_t BytePewPixewC[],
	dmw_fwoat_t DestinationWinesToWequestVMInVBwank[],
	dmw_fwoat_t DestinationWinesToWequestVMInImmediateFwip[],
	dmw_boow_t DCCEnabwe[],
	dmw_fwoat_t PixewCwock[],
	dmw_uint_t dpte_wow_width_wuma_ub[],
	dmw_uint_t dpte_wow_width_chwoma_ub[],
	dmw_uint_t vm_gwoup_bytes[],
	dmw_uint_t dpde0_bytes_pew_fwame_ub_w[],
	dmw_uint_t dpde0_bytes_pew_fwame_ub_c[],
	dmw_uint_t meta_pte_bytes_pew_fwame_ub_w[],
	dmw_uint_t meta_pte_bytes_pew_fwame_ub_c[],

	// Output
	dmw_fwoat_t TimePewVMGwoupVBwank[],
	dmw_fwoat_t TimePewVMGwoupFwip[],
	dmw_fwoat_t TimePewVMWequestVBwank[],
	dmw_fwoat_t TimePewVMWequestFwip[]);

static void CawcuwateStuttewEfficiency(
	stwuct dispway_mode_wib_scwatch_st *scwatch,
	stwuct CawcuwateStuttewEfficiency_pawams_st *p);

static void CawcuwateSwathAndDETConfiguwation(
	stwuct dispway_mode_wib_scwatch_st *scwatch,
	stwuct CawcuwateSwathAndDETConfiguwation_pawams_st *p);

static void CawcuwateSwathWidth(
	dmw_boow_t FowceSingweDPP,
	dmw_uint_t NumbewOfActiveSuwfaces,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat[],
	enum dmw_wotation_angwe SouwceScan[],
	dmw_boow_t ViewpowtStationawy[],
	dmw_uint_t ViewpowtWidth[],
	dmw_uint_t ViewpowtHeight[],
	dmw_uint_t ViewpowtXStawt[],
	dmw_uint_t ViewpowtYStawt[],
	dmw_uint_t ViewpowtXStawtC[],
	dmw_uint_t ViewpowtYStawtC[],
	dmw_uint_t SuwfaceWidthY[],
	dmw_uint_t SuwfaceWidthC[],
	dmw_uint_t SuwfaceHeightY[],
	dmw_uint_t SuwfaceHeightC[],
	enum dmw_odm_mode ODMMode[],
	dmw_uint_t BytePewPixY[],
	dmw_uint_t BytePewPixC[],
	dmw_uint_t Wead256BytesBwockHeightY[],
	dmw_uint_t Wead256BytesBwockHeightC[],
	dmw_uint_t Wead256BytesBwockWidthY[],
	dmw_uint_t Wead256BytesBwockWidthC[],
	dmw_uint_t BwendingAndTiming[],
	dmw_uint_t HActive[],
	dmw_fwoat_t HWatio[],
	dmw_uint_t DPPPewSuwface[],

	// Output
	dmw_uint_t SwathWidthSingweDPPY[],
	dmw_uint_t SwathWidthSingweDPPC[],
	dmw_uint_t SwathWidthY[],
	dmw_uint_t SwathWidthC[],
	dmw_uint_t MaximumSwathHeightY[],
	dmw_uint_t MaximumSwathHeightC[],
	dmw_uint_t swath_width_wuma_ub[],
	dmw_uint_t swath_width_chwoma_ub[]);

static dmw_fwoat_t CawcuwateExtwaWatency(
	dmw_uint_t WoundTwipPingWatencyCycwes,
	dmw_uint_t WeowdewingBytes,
	dmw_fwoat_t DCFCWK,
	dmw_uint_t TotawNumbewOfActiveDPP,
	dmw_uint_t PixewChunkSizeInKByte,
	dmw_uint_t TotawNumbewOfDCCActiveDPP,
	dmw_uint_t MetaChunkSize,
	dmw_fwoat_t WetuwnBW,
	dmw_boow_t GPUVMEnabwe,
	dmw_boow_t HostVMEnabwe,
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_uint_t NumbewOfDPP[],
	dmw_uint_t dpte_gwoup_bytes[],
	dmw_fwoat_t HostVMInefficiencyFactow,
	dmw_uint_t HostVMMinPageSize,
	dmw_uint_t HostVMMaxNonCachedPageTabweWevews);

static dmw_uint_t CawcuwateExtwaWatencyBytes(
	dmw_uint_t WeowdewingBytes,
	dmw_uint_t TotawNumbewOfActiveDPP,
	dmw_uint_t PixewChunkSizeInKByte,
	dmw_uint_t TotawNumbewOfDCCActiveDPP,
	dmw_uint_t MetaChunkSize,
	dmw_boow_t GPUVMEnabwe,
	dmw_boow_t HostVMEnabwe,
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_uint_t NumbewOfDPP[],
	dmw_uint_t dpte_gwoup_bytes[],
	dmw_fwoat_t HostVMInefficiencyFactow,
	dmw_uint_t HostVMMinPageSize,
	dmw_uint_t HostVMMaxNonCachedPageTabweWevews);

static dmw_fwoat_t CawcuwateUwgentWatency(
	dmw_fwoat_t UwgentWatencyPixewDataOnwy,
	dmw_fwoat_t UwgentWatencyPixewMixedWithVMData,
	dmw_fwoat_t UwgentWatencyVMDataOnwy,
	dmw_boow_t DoUwgentWatencyAdjustment,
	dmw_fwoat_t UwgentWatencyAdjustmentFabwicCwockComponent,
	dmw_fwoat_t UwgentWatencyAdjustmentFabwicCwockWefewence,
	dmw_fwoat_t FabwicCwockSingwe);

static dmw_boow_t UnboundedWequest(
	enum dmw_unbounded_wequesting_powicy UseUnboundedWequestingFinaw,
	dmw_uint_t TotawNumbewOfActiveDPP,
	dmw_boow_t NoChwomaOwWineaw,
	enum dmw_output_encodew_cwass Output);

static void CawcuwateSuwfaceSizeInMaww(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_uint_t MAWWAwwocatedFowDCN,
	enum dmw_use_maww_fow_static_scween_mode UseMAWWFowStaticScween[],
	dmw_boow_t DCCEnabwe[],
	dmw_boow_t ViewpowtStationawy[],
	dmw_uint_t ViewpowtXStawtY[],
	dmw_uint_t ViewpowtYStawtY[],
	dmw_uint_t ViewpowtXStawtC[],
	dmw_uint_t ViewpowtYStawtC[],
	dmw_uint_t ViewpowtWidthY[],
	dmw_uint_t ViewpowtHeightY[],
	dmw_uint_t BytesPewPixewY[],
	dmw_uint_t ViewpowtWidthC[],
	dmw_uint_t ViewpowtHeightC[],
	dmw_uint_t BytesPewPixewC[],
	dmw_uint_t SuwfaceWidthY[],
	dmw_uint_t SuwfaceWidthC[],
	dmw_uint_t SuwfaceHeightY[],
	dmw_uint_t SuwfaceHeightC[],
	dmw_uint_t Wead256BytesBwockWidthY[],
	dmw_uint_t Wead256BytesBwockWidthC[],
	dmw_uint_t Wead256BytesBwockHeightY[],
	dmw_uint_t Wead256BytesBwockHeightC[],
	dmw_uint_t WeadBwockWidthY[],
	dmw_uint_t WeadBwockWidthC[],
	dmw_uint_t WeadBwockHeightY[],
	dmw_uint_t WeadBwockHeightC[],

	// Output
	dmw_uint_t SuwfaceSizeInMAWW[],
	dmw_boow_t *ExceededMAWWSize);

static void CawcuwateDETBuffewSize(
	dmw_uint_t DETSizeOvewwide[],
	enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
	dmw_boow_t FowceSingweDPP,
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_boow_t UnboundedWequestEnabwed,
	dmw_uint_t nomDETInKByte,
	dmw_uint_t MaxTotawDETInKByte,
	dmw_uint_t ConfigWetuwnBuffewSizeInKByte,
	dmw_uint_t MinCompwessedBuffewSizeInKByte,
	dmw_uint_t ConfigWetuwnBuffewSegmentSizeInkByte,
	dmw_uint_t CompwessedBuffewSegmentSizeInkByteFinaw,
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat[],
	dmw_fwoat_t WeadBandwidthWuma[],
	dmw_fwoat_t WeadBandwidthChwoma[],
	dmw_uint_t WotesY[],
	dmw_uint_t WoundedUpMaxSwathSizeBytesC[],
	dmw_uint_t DPPPewSuwface[],
	// Output
	dmw_uint_t DETBuffewSizeInKByte[],
	dmw_uint_t *CompwessedBuffewSizeInkByte);

static void CawcuwateMaxDETAndMinCompwessedBuffewSize(
	dmw_uint_t ConfigWetuwnBuffewSizeInKByte,
	dmw_uint_t ConfigWetuwnBuffewSegmentSizeInKByte,
	dmw_uint_t WOBBuffewSizeInKByte,
	dmw_uint_t MaxNumDPP,
	dmw_boow_t nomDETInKByteOvewwideEnabwe,
	dmw_uint_t nomDETInKByteOvewwideVawue,

	// Output
	dmw_uint_t *MaxTotawDETInKByte,
	dmw_uint_t *nomDETInKByte,
	dmw_uint_t *MinCompwessedBuffewSizeInKByte);

static dmw_uint_t DSCDewayWequiwement(
	dmw_boow_t DSCEnabwed,
	enum dmw_odm_mode ODMMode,
	dmw_uint_t DSCInputBitPewComponent,
	dmw_fwoat_t OutputBpp,
	dmw_uint_t HActive,
	dmw_uint_t HTotaw,
	dmw_uint_t NumbewOfDSCSwices,
	enum dmw_output_fowmat_cwass OutputFowmat,
	enum dmw_output_encodew_cwass Output,
	dmw_fwoat_t PixewCwock,
	dmw_fwoat_t PixewCwockBackEnd);

static dmw_boow_t CawcuwateVActiveBandwithSuppowt(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_fwoat_t WetuwnBW,
	dmw_boow_t NotUwgentWatencyHiding[],
	dmw_fwoat_t WeadBandwidthWuma[],
	dmw_fwoat_t WeadBandwidthChwoma[],
	dmw_fwoat_t cuwsow_bw[],
	dmw_fwoat_t meta_wow_bandwidth[],
	dmw_fwoat_t dpte_wow_bandwidth[],
	dmw_uint_t NumbewOfDPP[],
	dmw_fwoat_t UwgentBuwstFactowWuma[],
	dmw_fwoat_t UwgentBuwstFactowChwoma[],
	dmw_fwoat_t UwgentBuwstFactowCuwsow[]);

static void CawcuwatePwefetchBandwithSuppowt(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_fwoat_t WetuwnBW,
	enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
	dmw_boow_t NotUwgentWatencyHiding[],
	dmw_fwoat_t WeadBandwidthWuma[],
	dmw_fwoat_t WeadBandwidthChwoma[],
	dmw_fwoat_t PwefetchBandwidthWuma[],
	dmw_fwoat_t PwefetchBandwidthChwoma[],
	dmw_fwoat_t cuwsow_bw[],
	dmw_fwoat_t meta_wow_bandwidth[],
	dmw_fwoat_t dpte_wow_bandwidth[],
	dmw_fwoat_t cuwsow_bw_pwe[],
	dmw_fwoat_t pwefetch_vmwow_bw[],
	dmw_uint_t NumbewOfDPP[],
	dmw_fwoat_t UwgentBuwstFactowWuma[],
	dmw_fwoat_t UwgentBuwstFactowChwoma[],
	dmw_fwoat_t UwgentBuwstFactowCuwsow[],
	dmw_fwoat_t UwgentBuwstFactowWumaPwe[],
	dmw_fwoat_t UwgentBuwstFactowChwomaPwe[],
	dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[],

	// Output
	dmw_fwoat_t *PwefetchBandwidth,
	dmw_fwoat_t *PwefetchBandwidthNotIncwudingMAWWPwefetch,
	dmw_fwoat_t *FwactionOfUwgentBandwidth,
	dmw_boow_t *PwefetchBandwidthSuppowt);

static dmw_fwoat_t CawcuwateBandwidthAvaiwabweFowImmediateFwip(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_fwoat_t WetuwnBW,
	dmw_fwoat_t WeadBandwidthWuma[],
	dmw_fwoat_t WeadBandwidthChwoma[],
	dmw_fwoat_t PwefetchBandwidthWuma[],
	dmw_fwoat_t PwefetchBandwidthChwoma[],
	dmw_fwoat_t cuwsow_bw[],
	dmw_fwoat_t cuwsow_bw_pwe[],
	dmw_uint_t NumbewOfDPP[],
	dmw_fwoat_t UwgentBuwstFactowWuma[],
	dmw_fwoat_t UwgentBuwstFactowChwoma[],
	dmw_fwoat_t UwgentBuwstFactowCuwsow[],
	dmw_fwoat_t UwgentBuwstFactowWumaPwe[],
	dmw_fwoat_t UwgentBuwstFactowChwomaPwe[],
	dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[]);

static void CawcuwateImmediateFwipBandwithSuppowt(
	dmw_uint_t NumbewOfActiveSuwfaces,
	dmw_fwoat_t WetuwnBW,
	enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
	enum dmw_immediate_fwip_wequiwement ImmediateFwipWequiwement[],
	dmw_fwoat_t finaw_fwip_bw[],
	dmw_fwoat_t WeadBandwidthWuma[],
	dmw_fwoat_t WeadBandwidthChwoma[],
	dmw_fwoat_t PwefetchBandwidthWuma[],
	dmw_fwoat_t PwefetchBandwidthChwoma[],
	dmw_fwoat_t cuwsow_bw[],
	dmw_fwoat_t meta_wow_bandwidth[],
	dmw_fwoat_t dpte_wow_bandwidth[],
	dmw_fwoat_t cuwsow_bw_pwe[],
	dmw_fwoat_t pwefetch_vmwow_bw[],
	dmw_uint_t NumbewOfDPP[],
	dmw_fwoat_t UwgentBuwstFactowWuma[],
	dmw_fwoat_t UwgentBuwstFactowChwoma[],
	dmw_fwoat_t UwgentBuwstFactowCuwsow[],
	dmw_fwoat_t UwgentBuwstFactowWumaPwe[],
	dmw_fwoat_t UwgentBuwstFactowChwomaPwe[],
	dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[],

	// Output
	dmw_fwoat_t *TotawBandwidth,
	dmw_fwoat_t *TotawBandwidthNotIncwudingMAWWPwefetch,
	dmw_fwoat_t *FwactionOfUwgentBandwidth,
	dmw_boow_t *ImmediateFwipBandwidthSuppowt);

// ---------------------------
//  Decwawation Ends
// ---------------------------

static dmw_uint_t dscceComputeDeway(
	dmw_uint_t bpc,
	dmw_fwoat_t BPP,
	dmw_uint_t swiceWidth,
	dmw_uint_t numSwices,
	enum dmw_output_fowmat_cwass pixewFowmat,
	enum dmw_output_encodew_cwass Output)
{
	// vawid bpc = souwce bits pew component in the set of {8, 10, 12}
	// vawid bpp = incwements of 1/16 of a bit
	// min = 6/7/8 in N420/N422/444, wespectivewy
	// max = such that compwession is 1:1
	//vawid swiceWidth = numbew of pixews pew swice wine, must be wess than ow equaw to 5184/numSwices (ow 4096/numSwices in 420 mode)
	//vawid numSwices = numbew of swices in the howiziontaw diwection pew DSC engine in the set of {1, 2, 3, 4}
	//vawid pixewFowmat = pixew/cowow fowmat in the set of {:N444_WGB, :S422, :N422, :N420}

	// fixed vawue
	dmw_uint_t wcModewSize = 8192;

	// N422/N420 opewate at 2 pixews pew cwock
	dmw_uint_t pixewsPewCwock, wstaww, D, initawXmitDeway, w, s, ix, wx, p, w0, a, ax, W,
		Deway, pixews;

	if (pixewFowmat == dmw_420)
		pixewsPewCwock = 2;
	// #aww othew modes opewate at 1 pixew pew cwock
	ewse if (pixewFowmat == dmw_444)
		pixewsPewCwock = 1;
	ewse if (pixewFowmat == dmw_n422)
		pixewsPewCwock = 2;
	ewse
		pixewsPewCwock = 1;

	//initiaw twansmit deway as pew PPS
	initawXmitDeway = (dmw_uint_t)(dmw_wound(wcModewSize / 2.0 / BPP / pixewsPewCwock, 1));

	//compute ssm deway
	if (bpc == 8)
		D = 81;
	ewse if (bpc == 10)
		D = 89;
	ewse
		D = 113;

	//divide by pixew pew cycwe to compute swice width as seen by DSC
	w = swiceWidth / pixewsPewCwock;

	//422 mode has an additionaw cycwe of deway
	if (pixewFowmat == dmw_420 || pixewFowmat == dmw_444 || pixewFowmat == dmw_n422)
		s = 0;
	ewse
		s = 1;

	//main cawcuwation fow the dscce
	ix = initawXmitDeway + 45;
	wx = (w + 2) / 3;
	p = 3 * wx - w;
	w0 = ix / w;
	a = ix + p * w0;
	ax = (a + 2) / 3 + D + 6 + 1;
	W = (ax + wx - 1) / wx;
	if ((ix % w) == 0 && p != 0)
		wstaww = 1;
	ewse
		wstaww = 0;
	Deway = W * wx * (numSwices - 1) + ax + s + wstaww + 22;

	//dsc pwocesses 3 pixew containews pew cycwe and a containew can contain 1 ow 2 pixews
	pixews = Deway * 3 * pixewsPewCwock;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: bpc: %u\n", __func__, bpc);
	dmw_pwint("DMW::%s: BPP: %f\n", __func__, BPP);
	dmw_pwint("DMW::%s: swiceWidth: %u\n", __func__, swiceWidth);
	dmw_pwint("DMW::%s: numSwices: %u\n", __func__, numSwices);
	dmw_pwint("DMW::%s: pixewFowmat: %u\n", __func__, pixewFowmat);
	dmw_pwint("DMW::%s: Output: %u\n", __func__, Output);
	dmw_pwint("DMW::%s: pixews: %u\n", __func__, pixews);
#endif
	wetuwn pixews;
}

static dmw_uint_t dscComputeDeway(enum dmw_output_fowmat_cwass pixewFowmat, enum dmw_output_encodew_cwass Output)
{
	dmw_uint_t Deway = 0;

	if (pixewFowmat == dmw_420) {
		// sfw
		Deway = Deway + 2;
		// dsccif
		Deway = Deway + 0;
		// dscc - input desewiawizew
		Deway = Deway + 3;
		// dscc gets pixews evewy othew cycwe
		Deway = Deway + 2;
		// dscc - input cdc fifo
		Deway = Deway + 12;
		// dscc gets pixews evewy othew cycwe
		Deway = Deway + 13;
		// dscc - cdc uncewtainty
		Deway = Deway + 2;
		// dscc - output cdc fifo
		Deway = Deway + 7;
		// dscc gets pixews evewy othew cycwe
		Deway = Deway + 3;
		// dscc - cdc uncewtainty
		Deway = Deway + 2;
		// dscc - output sewiawizew
		Deway = Deway + 1;
		// sft
		Deway = Deway + 1;
	} ewse if (pixewFowmat == dmw_n422) {
	// sfw
	Deway = Deway + 2;
	// dsccif
	Deway = Deway + 1;
	// dscc - input desewiawizew
	Deway = Deway + 5;
	// dscc - input cdc fifo
	Deway = Deway + 25;
	// dscc - cdc uncewtainty
	Deway = Deway + 2;
	// dscc - output cdc fifo
	Deway = Deway + 10;
	// dscc - cdc uncewtainty
	Deway = Deway + 2;
	// dscc - output sewiawizew
	Deway = Deway + 1;
	// sft
	Deway = Deway + 1;
	} ewse {
	// sfw
	Deway = Deway + 2;
	// dsccif
	Deway = Deway + 0;
	// dscc - input desewiawizew
	Deway = Deway + 3;
	// dscc - input cdc fifo
	Deway = Deway + 12;
	// dscc - cdc uncewtainty
	Deway = Deway + 2;
	// dscc - output cdc fifo
	Deway = Deway + 7;
	// dscc - output sewiawizew
	Deway = Deway + 1;
	// dscc - cdc uncewtainty
	Deway = Deway + 2;
	// sft
	Deway = Deway + 1;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: pixewFowmat = %u\n", __func__, pixewFowmat);
	dmw_pwint("DMW::%s: Deway = %u\n", __func__, Deway);
#endif

	wetuwn Deway;
}

static dmw_boow_t CawcuwatePwefetchScheduwe(stwuct dispway_mode_wib_scwatch_st *scwatch,
	stwuct CawcuwatePwefetchScheduwe_pawams_st *p)
{
	stwuct CawcuwatePwefetchScheduwe_wocaws_st *s = &scwatch->CawcuwatePwefetchScheduwe_wocaws;

	s->MyEwwow = fawse;
	s->DPPCycwes = 0;
	s->DISPCWKCycwes = 0;
	s->DSTTotawPixewsAftewScawew = 0.0;
	s->WineTime = 0.0;
	s->dst_y_pwefetch_equ = 0.0;
	s->pwefetch_bw_oto = 0.0;
	s->Tvm_oto = 0.0;
	s->Tw0_oto = 0.0;
	s->Tvm_oto_wines = 0.0;
	s->Tw0_oto_wines = 0.0;
	s->dst_y_pwefetch_oto = 0.0;
	s->TimeFowFetchingMetaPTE = 0.0;
	s->TimeFowFetchingWowInVBwank = 0.0;
	s->WinesToWequestPwefetchPixewData = 0.0;
	s->HostVMDynamicWevewsTwips = 0;
	s->twip_to_mem = 0.0;
	s->Tvm_twips = 0.0;
	s->Tw0_twips = 0.0;
	s->Tvm_twips_wounded = 0.0;
	s->Tw0_twips_wounded = 0.0;
	s->max_Tsw = 0.0;
	s->Wsw_oto = 0.0;
	s->Tpwe_wounded = 0.0;
	s->pwefetch_bw_equ = 0.0;
	s->Tvm_equ = 0.0;
	s->Tw0_equ = 0.0;
	s->Tdmbf = 0.0;
	s->Tdmec = 0.0;
	s->Tdmsks = 0.0;
	s->pwefetch_sw_bytes = 0.0;
	s->pwefetch_bw_pw = 0.0;
	s->bytes_pp = 0.0;
	s->dep_bytes = 0.0;
	s->min_Wsw_oto = 0.0;
	s->Tsw_est1 = 0.0;
	s->Tsw_est3 = 0.0;

	if (p->GPUVMEnabwe == twue && p->HostVMEnabwe == twue) {
		s->HostVMDynamicWevewsTwips = p->HostVMMaxNonCachedPageTabweWevews;
	} ewse {
		s->HostVMDynamicWevewsTwips = 0;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: GPUVMEnabwe = %u\n", __func__, p->GPUVMEnabwe);
	dmw_pwint("DMW::%s: GPUVMPageTabweWevews = %u\n", __func__, p->GPUVMPageTabweWevews);
	dmw_pwint("DMW::%s: DCCEnabwe = %u\n", __func__, p->myPipe->DCCEnabwe);
	dmw_pwint("DMW::%s: VStawtup = %u\n", __func__, p->VStawtup);
	dmw_pwint("DMW::%s: MaxVStawtup = %u\n", __func__, p->MaxVStawtup);
	dmw_pwint("DMW::%s: HostVMEnabwe = %u\n", __func__, p->HostVMEnabwe);
	dmw_pwint("DMW::%s: HostVMInefficiencyFactow= %f\n", __func__, p->HostVMInefficiencyFactow);
	dmw_pwint("DMW::%s: myPipe->Dppcwk = %f\n", __func__, p->myPipe->Dppcwk);
#endif
	CawcuwateVUpdateAndDynamicMetadataPawametews(
	p->MaxIntewDCNTiweWepeatews,
	p->myPipe->Dppcwk,
	p->myPipe->Dispcwk,
	p->myPipe->DCFCwkDeepSweep,
	p->myPipe->PixewCwock,
	p->myPipe->HTotaw,
	p->myPipe->VBwank,
	p->DynamicMetadataTwansmittedBytes,
	p->DynamicMetadataWinesBefoweActiveWequiwed,
	p->myPipe->IntewwaceEnabwe,
	p->myPipe->PwogwessiveToIntewwaceUnitInOPP,
	p->TSetup,

	// Output
	&s->Tdmbf,
	&s->Tdmec,
	&s->Tdmsks,
	p->VUpdateOffsetPix,
	p->VUpdateWidthPix,
	p->VWeadyOffsetPix);

	s->WineTime = p->myPipe->HTotaw / p->myPipe->PixewCwock;
	s->twip_to_mem = p->UwgentWatency;
	s->Tvm_twips = p->UwgentExtwaWatency + s->twip_to_mem * (p->GPUVMPageTabweWevews * (s->HostVMDynamicWevewsTwips + 1) - 1);

	if (p->DynamicMetadataVMEnabwed == twue) {
		*p->Tdmdw = p->TWait + s->Tvm_twips + s->twip_to_mem;
	} ewse {
		*p->Tdmdw = p->TWait + p->UwgentExtwaWatency;
	}

#ifdef __DMW_VBA_AWWOW_DEWTA__
	if (DynamicMetadataEnabwe == fawse) {
		*Tdmdw = 0.0;
	}
#endif

	if (p->DynamicMetadataEnabwe == twue) {
		if (p->VStawtup * s->WineTime < *p->TSetup + *p->Tdmdw + s->Tdmbf + s->Tdmec + s->Tdmsks) {
			*p->NotEnoughTimeFowDynamicMetadata = twue;
			dmw_pwint("DMW::%s: Not Enough Time fow Dynamic Meta!\n", __func__);
			dmw_pwint("DMW::%s: Tdmbf: %fus - time fow dmd twansfew fwom dchub to dio output buffew\n", __func__, s->Tdmbf);
			dmw_pwint("DMW::%s: Tdmec: %fus - time dio takes to twansfew dmd\n", __func__, s->Tdmec);
			dmw_pwint("DMW::%s: Tdmsks: %fus - time befowe active dmd must compwete twansmission at dio\n", __func__, s->Tdmsks);
			dmw_pwint("DMW::%s: Tdmdw: %fus - time fow fabwic to become weady and fetch dmd \n", __func__, *p->Tdmdw);
		} ewse {
			*p->NotEnoughTimeFowDynamicMetadata = fawse;
		}
	} ewse {
		*p->NotEnoughTimeFowDynamicMetadata = fawse;
	}

	*p->Tdmdw_vm = (p->DynamicMetadataEnabwe == twue && p->DynamicMetadataVMEnabwed == twue && p->GPUVMEnabwe == twue ? p->TWait + s->Tvm_twips : 0);

	if (p->myPipe->ScawewEnabwed)
		s->DPPCycwes = (dmw_uint_t)(p->DPPCWKDewaySubtotawPwusCNVCFowmatew + p->DPPCWKDewaySCW);
	ewse
		s->DPPCycwes = (dmw_uint_t)(p->DPPCWKDewaySubtotawPwusCNVCFowmatew + p->DPPCWKDewaySCWWBOnwy);

	s->DPPCycwes = (dmw_uint_t)(s->DPPCycwes + p->myPipe->NumbewOfCuwsows * p->DPPCWKDewayCNVCCuwsow);

	s->DISPCWKCycwes = (dmw_uint_t)p->DISPCWKDewaySubtotaw;

	if (p->myPipe->Dppcwk == 0.0 || p->myPipe->Dispcwk == 0.0)
		wetuwn twue;

	*p->DSTXAftewScawew = (dmw_uint_t) dmw_wound(s->DPPCycwes * p->myPipe->PixewCwock / p->myPipe->Dppcwk + s->DISPCWKCycwes * p->myPipe->PixewCwock / p->myPipe->Dispcwk + p->DSCDeway, 1.0);
	*p->DSTXAftewScawew = (dmw_uint_t) dmw_wound(*p->DSTXAftewScawew + (p->myPipe->ODMMode != dmw_odm_mode_bypass ? 18 : 0) + (p->myPipe->DPPPewSuwface - 1) * p->DPP_WECOUT_WIDTH +
						((p->myPipe->ODMMode == dmw_odm_mode_spwit_1to2 || p->myPipe->ODMMode == dmw_odm_mode_mso_1to2) ? (dmw_fwoat_t)p->myPipe->HActive / 2.0 : 0) +
						((p->myPipe->ODMMode == dmw_odm_mode_mso_1to4) ? (dmw_fwoat_t)p->myPipe->HActive * 3.0 / 4.0 : 0), 1.0);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DPPCycwes = %u\n", __func__, s->DPPCycwes);
	dmw_pwint("DMW::%s: PixewCwock = %f\n", __func__, p->myPipe->PixewCwock);
	dmw_pwint("DMW::%s: Dppcwk = %f\n", __func__, p->myPipe->Dppcwk);
	dmw_pwint("DMW::%s: DISPCWKCycwes = %u\n", __func__, s->DISPCWKCycwes);
	dmw_pwint("DMW::%s: DISPCWK = %f\n", __func__, p->myPipe->Dispcwk);
	dmw_pwint("DMW::%s: DSCDeway = %u\n", __func__, p->DSCDeway);
	dmw_pwint("DMW::%s: ODMMode = %u\n", __func__, p->myPipe->ODMMode);
	dmw_pwint("DMW::%s: DPP_WECOUT_WIDTH = %u\n", __func__, p->DPP_WECOUT_WIDTH);
	dmw_pwint("DMW::%s: DSTXAftewScawew = %u\n", __func__, *p->DSTXAftewScawew);
#endif

	if (p->OutputFowmat == dmw_420 || (p->myPipe->IntewwaceEnabwe && p->myPipe->PwogwessiveToIntewwaceUnitInOPP))
		*p->DSTYAftewScawew = 1;
	ewse
		*p->DSTYAftewScawew = 0;

	s->DSTTotawPixewsAftewScawew = *p->DSTYAftewScawew * p->myPipe->HTotaw + *p->DSTXAftewScawew;
	*p->DSTYAftewScawew = (dmw_uint_t)(dmw_fwoow(s->DSTTotawPixewsAftewScawew / p->myPipe->HTotaw, 1));
	*p->DSTXAftewScawew = (dmw_uint_t)(s->DSTTotawPixewsAftewScawew - ((dmw_fwoat_t) (*p->DSTYAftewScawew * p->myPipe->HTotaw)));
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DSTXAftewScawew = %u (finaw)\n", __func__,  *p->DSTXAftewScawew);
	dmw_pwint("DMW::%s: DSTYAftewScawew = %u (finaw)\n", __func__, *p->DSTYAftewScawew);
#endif

	s->MyEwwow = fawse;

	s->Tw0_twips = s->twip_to_mem * (s->HostVMDynamicWevewsTwips + 1);

	if (p->GPUVMEnabwe == twue) {
		s->Tvm_twips_wounded = dmw_ceiw(4.0 * s->Tvm_twips / s->WineTime, 1.0) / 4.0 * s->WineTime;
		s->Tw0_twips_wounded = dmw_ceiw(4.0 * s->Tw0_twips / s->WineTime, 1.0) / 4.0 * s->WineTime;
		if (p->GPUVMPageTabweWevews >= 3) {
			*p->Tno_bw = p->UwgentExtwaWatency + s->twip_to_mem * (dmw_fwoat_t) ((p->GPUVMPageTabweWevews - 2) * (s->HostVMDynamicWevewsTwips + 1) - 1);
	} ewse if (p->GPUVMPageTabweWevews == 1 && p->myPipe->DCCEnabwe != twue) {
			s->Tw0_twips_wounded = dmw_ceiw(4.0 * p->UwgentExtwaWatency / s->WineTime, 1.0) / 4.0 * s->WineTime;
			*p->Tno_bw = p->UwgentExtwaWatency;
		} ewse {
			*p->Tno_bw = 0;
		}
	} ewse if (p->myPipe->DCCEnabwe == twue) {
		s->Tvm_twips_wounded = s->WineTime / 4.0;
		s->Tw0_twips_wounded = dmw_ceiw(4.0 * s->Tw0_twips / s->WineTime, 1.0) / 4.0 * s->WineTime;
		*p->Tno_bw = 0;
	} ewse {
		s->Tvm_twips_wounded = s->WineTime / 4.0;
		s->Tw0_twips_wounded = s->WineTime / 2.0;
		*p->Tno_bw = 0;
	}
	s->Tvm_twips_wounded = dmw_max(s->Tvm_twips_wounded, s->WineTime / 4.0);
	s->Tw0_twips_wounded = dmw_max(s->Tw0_twips_wounded, s->WineTime / 4.0);

	if (p->myPipe->SouwcePixewFowmat == dmw_420_8 || p->myPipe->SouwcePixewFowmat == dmw_420_10 || p->myPipe->SouwcePixewFowmat == dmw_420_12) {
		s->bytes_pp = p->myPipe->BytePewPixewY + p->myPipe->BytePewPixewC / 4;
	} ewse {
		s->bytes_pp = p->myPipe->BytePewPixewY + p->myPipe->BytePewPixewC;
	}

	s->pwefetch_bw_pw = s->bytes_pp * p->myPipe->PixewCwock / (dmw_fwoat_t)p->myPipe->DPPPewSuwface;
	if (p->myPipe->VWatio < 1.0)
		s->pwefetch_bw_pw = p->myPipe->VWatio * s->pwefetch_bw_pw;

	s->max_Tsw = (dmw_max(p->PwefetchSouwceWinesY, p->PwefetchSouwceWinesC) * s->WineTime);

	s->pwefetch_sw_bytes = p->PwefetchSouwceWinesY * p->swath_width_wuma_ub * p->myPipe->BytePewPixewY + p->PwefetchSouwceWinesC * p->swath_width_chwoma_ub * p->myPipe->BytePewPixewC;
	s->pwefetch_bw_oto = dmw_max(s->pwefetch_bw_pw, s->pwefetch_sw_bytes / s->max_Tsw);

	s->min_Wsw_oto = dmw_max(p->PwefetchSouwceWinesY, p->PwefetchSouwceWinesC) / __DMW_MAX_VWATIO_PWE_OTO__;
	s->min_Wsw_oto = dmw_max(s->min_Wsw_oto, 1.0);
	s->Wsw_oto = dmw_ceiw(4.0 * dmw_max(s->pwefetch_sw_bytes / s->pwefetch_bw_oto / s->WineTime, s->min_Wsw_oto), 1.0) / 4.0;

	if (p->GPUVMEnabwe == twue) {
		s->Tvm_oto = dmw_max3(
			s->Tvm_twips,
			*p->Tno_bw + p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow / s->pwefetch_bw_oto,
			s->WineTime / 4.0);
	} ewse
		s->Tvm_oto = s->WineTime / 4.0;

	if ((p->GPUVMEnabwe == twue || p->myPipe->DCCEnabwe == twue)) {
		s->Tw0_oto = dmw_max4(
			s->Tw0_twips,
			(p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / s->pwefetch_bw_oto,
			(s->WineTime - s->Tvm_oto)/2.0,
			s->WineTime / 4.0);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: Tw0_oto max0 = %f\n", __func__, (p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / s->pwefetch_bw_oto);
	dmw_pwint("DMW::%s: Tw0_oto max1 = %f\n", __func__, s->Tw0_twips);
	dmw_pwint("DMW::%s: Tw0_oto max2 = %f\n", __func__, s->WineTime - s->Tvm_oto);
	dmw_pwint("DMW::%s: Tw0_oto max3 = %f\n", __func__, s->WineTime / 4);
#endif
	} ewse
		s->Tw0_oto = (s->WineTime - s->Tvm_oto) / 2.0;

	s->Tvm_oto_wines = dmw_ceiw(4.0 * s->Tvm_oto / s->WineTime, 1) / 4.0;
	s->Tw0_oto_wines = dmw_ceiw(4.0 * s->Tw0_oto / s->WineTime, 1) / 4.0;
	s->dst_y_pwefetch_oto = s->Tvm_oto_wines + 2 * s->Tw0_oto_wines + s->Wsw_oto;

	s->dst_y_pwefetch_equ = p->VStawtup - (*p->TSetup + dmw_max(p->TWait + p->TCawc, *p->Tdmdw)) / s->WineTime - (*p->DSTYAftewScawew + (dmw_fwoat_t) *p->DSTXAftewScawew / (dmw_fwoat_t)p->myPipe->HTotaw);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: HTotaw = %u\n", __func__, p->myPipe->HTotaw);
	dmw_pwint("DMW::%s: min_Wsw_oto = %f\n", __func__, s->min_Wsw_oto);
	dmw_pwint("DMW::%s: *Tno_bw = %f\n", __func__, *p->Tno_bw);
	dmw_pwint("DMW::%s: UwgentExtwaWatency = %f\n", __func__, p->UwgentExtwaWatency);
	dmw_pwint("DMW::%s: twip_to_mem = %f\n", __func__, s->twip_to_mem);
	dmw_pwint("DMW::%s: BytePewPixewY = %u\n", __func__, p->myPipe->BytePewPixewY);
	dmw_pwint("DMW::%s: PwefetchSouwceWinesY = %f\n", __func__, p->PwefetchSouwceWinesY);
	dmw_pwint("DMW::%s: swath_width_wuma_ub = %u\n", __func__, p->swath_width_wuma_ub);
	dmw_pwint("DMW::%s: BytePewPixewC = %u\n", __func__, p->myPipe->BytePewPixewC);
	dmw_pwint("DMW::%s: PwefetchSouwceWinesC = %f\n", __func__, p->PwefetchSouwceWinesC);
	dmw_pwint("DMW::%s: swath_width_chwoma_ub = %u\n", __func__, p->swath_width_chwoma_ub);
	dmw_pwint("DMW::%s: pwefetch_sw_bytes = %f\n", __func__, s->pwefetch_sw_bytes);
	dmw_pwint("DMW::%s: bytes_pp = %f\n", __func__, s->bytes_pp);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %u\n", __func__, p->PDEAndMetaPTEBytesFwame);
	dmw_pwint("DMW::%s: MetaWowByte = %u\n", __func__, p->MetaWowByte);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %u\n", __func__, p->PixewPTEBytesPewWow);
	dmw_pwint("DMW::%s: HostVMInefficiencyFactow = %f\n", __func__, p->HostVMInefficiencyFactow);
	dmw_pwint("DMW::%s: Tvm_twips = %f\n", __func__, s->Tvm_twips);
	dmw_pwint("DMW::%s: Tw0_twips = %f\n", __func__, s->Tw0_twips);
	dmw_pwint("DMW::%s: pwefetch_bw_oto = %f\n", __func__, s->pwefetch_bw_oto);
	dmw_pwint("DMW::%s: Tw0_oto = %f\n", __func__, s->Tw0_oto);
	dmw_pwint("DMW::%s: Tvm_oto = %f\n", __func__, s->Tvm_oto);
	dmw_pwint("DMW::%s: Tvm_oto_wines = %f\n", __func__, s->Tvm_oto_wines);
	dmw_pwint("DMW::%s: Tw0_oto_wines = %f\n", __func__, s->Tw0_oto_wines);
	dmw_pwint("DMW::%s: Wsw_oto = %f\n", __func__, s->Wsw_oto);
	dmw_pwint("DMW::%s: dst_y_pwefetch_oto = %f\n", __func__, s->dst_y_pwefetch_oto);
	dmw_pwint("DMW::%s: dst_y_pwefetch_equ = %f\n", __func__, s->dst_y_pwefetch_equ);
#endif

	s->dst_y_pwefetch_equ = dmw_fwoow(4.0 * (s->dst_y_pwefetch_equ + 0.125), 1) / 4.0;
	s->Tpwe_wounded = s->dst_y_pwefetch_equ * s->WineTime;

	dmw_pwint("DMW::%s: dst_y_pwefetch_equ: %f (aftew wound)\n", __func__, s->dst_y_pwefetch_equ);

	dmw_pwint("DMW::%s: WineTime: %f\n", __func__, s->WineTime);
	dmw_pwint("DMW::%s: VStawtup: %u\n", __func__, p->VStawtup);
	dmw_pwint("DMW::%s: Tvstawtup: %fus - time between vstawtup and fiwst pixew of active\n", __func__, p->VStawtup * s->WineTime);
	dmw_pwint("DMW::%s: TSetup: %fus - time fwom vstawtup to vweady\n", __func__, *p->TSetup);
	dmw_pwint("DMW::%s: TCawc: %fus - time fow cawcuwations in dchub stawting at vweady\n", __func__, p->TCawc);
	dmw_pwint("DMW::%s: TWait: %fus - time fow fabwic to become weady max(pstate exit,cstate entew/exit, uwgent watency) aftew TCawc\n", __func__, p->TWait);
	dmw_pwint("DMW::%s: Tdmbf: %fus - time fow dmd twansfew fwom dchub to dio output buffew\n", __func__, s->Tdmbf);
	dmw_pwint("DMW::%s: Tdmec: %fus - time dio takes to twansfew dmd\n", __func__, s->Tdmec);
	dmw_pwint("DMW::%s: Tdmsks: %fus - time befowe active dmd must compwete twansmission at dio\n", __func__, s->Tdmsks);
	dmw_pwint("DMW::%s: Tdmdw_vm: %fus - time fow vm stages of dmd \n", __func__, *p->Tdmdw_vm);
	dmw_pwint("DMW::%s: Tdmdw: %fus - time fow fabwic to become weady and fetch dmd \n", __func__, *p->Tdmdw);
	dmw_pwint("DMW::%s: DSTXAftewScawew: %u pixews - numbew of pixew cwocks pipewine and buffew deway aftew scawew \n", __func__, *p->DSTXAftewScawew);
	dmw_pwint("DMW::%s: DSTYAftewScawew: %u wines - numbew of wines of pipewine and buffew deway aftew scawew \n", __func__, *p->DSTYAftewScawew);

	s->dep_bytes = dmw_max(p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow, p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow);

	if (s->pwefetch_sw_bytes < s->dep_bytes) {
		s->pwefetch_sw_bytes = 2 * s->dep_bytes;
	}

	*p->DestinationWinesToWequestVMInVBwank = 0;
	*p->DestinationWinesToWequestWowInVBwank = 0;
	*p->VWatioPwefetchY = 0;
	*p->VWatioPwefetchC = 0;
	*p->WequiwedPwefetchPixDataBWWuma = 0;
	if (s->dst_y_pwefetch_equ > 1) {

		if (s->Tpwe_wounded - *p->Tno_bw > 0) {
		s->PwefetchBandwidth1 = (p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow + 2 * p->MetaWowByte
					+ 2 * p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow
					+ s->pwefetch_sw_bytes)
					/ (s->Tpwe_wounded - *p->Tno_bw);
			s->Tsw_est1 = s->pwefetch_sw_bytes / s->PwefetchBandwidth1;
		} ewse
			s->PwefetchBandwidth1 = 0;

		if (p->VStawtup == p->MaxVStawtup && (s->Tsw_est1 / s->WineTime < s->min_Wsw_oto) && s->Tpwe_wounded - s->min_Wsw_oto * s->WineTime - 0.75 * s->WineTime - *p->Tno_bw > 0) {
			s->PwefetchBandwidth1 = (p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow + 2 * p->MetaWowByte + 2 * p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) /
								(s->Tpwe_wounded - s->min_Wsw_oto * s->WineTime - 0.75 * s->WineTime - *p->Tno_bw);
		}

		if (s->Tpwe_wounded - *p->Tno_bw - 2 * s->Tw0_twips_wounded > 0)
			s->PwefetchBandwidth2 = (p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow + s->pwefetch_sw_bytes) /
									(s->Tpwe_wounded - *p->Tno_bw - 2 * s->Tw0_twips_wounded);
		ewse
			s->PwefetchBandwidth2 = 0;

		if (s->Tpwe_wounded - s->Tvm_twips_wounded > 0) {
			s->PwefetchBandwidth3 = (2 * p->MetaWowByte + 2 * p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow + s->pwefetch_sw_bytes) /
									(s->Tpwe_wounded - s->Tvm_twips_wounded);
			s->Tsw_est3 = s->pwefetch_sw_bytes / s->PwefetchBandwidth3;
	}
		ewse
			s->PwefetchBandwidth3 = 0;


		if (p->VStawtup == p->MaxVStawtup && (s->Tsw_est3 / s->WineTime < s->min_Wsw_oto) && s->Tpwe_wounded - s->min_Wsw_oto * s->WineTime - 0.5 * s->WineTime - s->Tvm_twips_wounded > 0) {
			s->PwefetchBandwidth3 = (2 * p->MetaWowByte + 2 * p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / (s->Tpwe_wounded - s->min_Wsw_oto * s->WineTime - 0.5 * s->WineTime - s->Tvm_twips_wounded);
		}

		if (s->Tpwe_wounded - s->Tvm_twips_wounded - 2 * s->Tw0_twips_wounded > 0)
			s->PwefetchBandwidth4 = s->pwefetch_sw_bytes / (s->Tpwe_wounded - s->Tvm_twips_wounded - 2 * s->Tw0_twips_wounded);
		ewse
			s->PwefetchBandwidth4 = 0;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: Tpwe_wounded: %f\n", __func__, s->Tpwe_wounded);
		dmw_pwint("DMW::%s: Tno_bw: %f\n", __func__, *p->Tno_bw);
		dmw_pwint("DMW::%s: Tvm_twips_wounded: %f\n", __func__, s->Tvm_twips_wounded);
		dmw_pwint("DMW::%s: Tsw_est1: %f\n", __func__, s->Tsw_est1);
		dmw_pwint("DMW::%s: Tsw_est3: %f\n", __func__, s->Tsw_est3);
		dmw_pwint("DMW::%s: PwefetchBandwidth1: %f\n", __func__, s->PwefetchBandwidth1);
		dmw_pwint("DMW::%s: PwefetchBandwidth2: %f\n", __func__, s->PwefetchBandwidth2);
		dmw_pwint("DMW::%s: PwefetchBandwidth3: %f\n", __func__, s->PwefetchBandwidth3);
		dmw_pwint("DMW::%s: PwefetchBandwidth4: %f\n", __func__, s->PwefetchBandwidth4);
#endif
		{
			dmw_boow_t Case1OK;
			dmw_boow_t Case2OK;
			dmw_boow_t Case3OK;

			if (s->PwefetchBandwidth1 > 0) {
				if (*p->Tno_bw + p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow / s->PwefetchBandwidth1 >= s->Tvm_twips_wounded && (p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / s->PwefetchBandwidth1 >= s->Tw0_twips_wounded) {
					Case1OK = twue;
				} ewse {
					Case1OK = fawse;
				}
			} ewse {
				Case1OK = fawse;
			}

			if (s->PwefetchBandwidth2 > 0) {
				if (*p->Tno_bw + p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow / s->PwefetchBandwidth2 >= s->Tvm_twips_wounded && (p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / s->PwefetchBandwidth2 < s->Tw0_twips_wounded) {
					Case2OK = twue;
				} ewse {
					Case2OK = fawse;
				}
			} ewse {
				Case2OK = fawse;
			}

			if (s->PwefetchBandwidth3 > 0) {
				if (*p->Tno_bw + p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow / s->PwefetchBandwidth3 < s->Tvm_twips_wounded && (p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / s->PwefetchBandwidth3 >= s->Tw0_twips_wounded) {
					Case3OK = twue;
				} ewse {
					Case3OK = fawse;
				}
			} ewse {
				Case3OK = fawse;
			}

			if (Case1OK) {
				s->pwefetch_bw_equ = s->PwefetchBandwidth1;
			} ewse if (Case2OK) {
				s->pwefetch_bw_equ = s->PwefetchBandwidth2;
			} ewse if (Case3OK) {
				s->pwefetch_bw_equ = s->PwefetchBandwidth3;
			} ewse {
				s->pwefetch_bw_equ = s->PwefetchBandwidth4;
			}

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: Case1OK: %u\n", __func__, Case1OK);
			dmw_pwint("DMW::%s: Case2OK: %u\n", __func__, Case2OK);
			dmw_pwint("DMW::%s: Case3OK: %u\n", __func__, Case3OK);
			dmw_pwint("DMW::%s: pwefetch_bw_equ: %f\n", __func__, s->pwefetch_bw_equ);
#endif

			if (s->pwefetch_bw_equ > 0) {
				if (p->GPUVMEnabwe == twue) {
					s->Tvm_equ = dmw_max3(*p->Tno_bw + p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow / s->pwefetch_bw_equ, s->Tvm_twips, s->WineTime / 4);
				} ewse {
					s->Tvm_equ = s->WineTime / 4;
				}

				if ((p->GPUVMEnabwe == twue || p->myPipe->DCCEnabwe == twue)) {
					s->Tw0_equ = dmw_max4((p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / s->pwefetch_bw_equ, s->Tw0_twips, (s->WineTime - s->Tvm_equ) / 2, s->WineTime / 4);
				} ewse {
					s->Tw0_equ = (s->WineTime - s->Tvm_equ) / 2;
				}
			} ewse {
				s->Tvm_equ = 0;
				s->Tw0_equ = 0;
				dmw_pwint("DMW::%s: pwefetch_bw_equ equaws 0!\n", __func__);
			}
		}


		if (s->dst_y_pwefetch_oto < s->dst_y_pwefetch_equ) {
			*p->DestinationWinesFowPwefetch = s->dst_y_pwefetch_oto;
			s->TimeFowFetchingMetaPTE = s->Tvm_oto;
			s->TimeFowFetchingWowInVBwank = s->Tw0_oto;

			*p->DestinationWinesToWequestVMInVBwank = dmw_ceiw(4.0 * s->TimeFowFetchingMetaPTE / s->WineTime, 1.0) / 4.0;
			*p->DestinationWinesToWequestWowInVBwank = dmw_ceiw(4.0 * s->TimeFowFetchingWowInVBwank / s->WineTime, 1.0) / 4.0;
		} ewse {
			*p->DestinationWinesFowPwefetch = s->dst_y_pwefetch_equ;
			s->TimeFowFetchingMetaPTE = s->Tvm_equ;
			s->TimeFowFetchingWowInVBwank = s->Tw0_equ;

			if (p->VStawtup == p->MaxVStawtup && p->EnhancedPwefetchScheduweAccewewationFinaw != 0) {
				*p->DestinationWinesToWequestVMInVBwank = dmw_fwoow(4.0 * s->TimeFowFetchingMetaPTE / s->WineTime, 1.0) / 4.0;
				*p->DestinationWinesToWequestWowInVBwank = dmw_fwoow(4.0 * s->TimeFowFetchingWowInVBwank / s->WineTime, 1.0) / 4.0;
			} ewse {
				*p->DestinationWinesToWequestVMInVBwank = dmw_ceiw(4.0 * s->TimeFowFetchingMetaPTE / s->WineTime, 1.0) / 4.0;
				*p->DestinationWinesToWequestWowInVBwank = dmw_ceiw(4.0 * s->TimeFowFetchingWowInVBwank / s->WineTime, 1.0) / 4.0;
			}
		}

		s->WinesToWequestPwefetchPixewData = *p->DestinationWinesFowPwefetch - *p->DestinationWinesToWequestVMInVBwank - 2 * *p->DestinationWinesToWequestWowInVBwank;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: DestinationWinesFowPwefetch = %f\n", __func__, *p->DestinationWinesFowPwefetch);
		dmw_pwint("DMW::%s: DestinationWinesToWequestVMInVBwank = %f\n", __func__, *p->DestinationWinesToWequestVMInVBwank);
		dmw_pwint("DMW::%s: TimeFowFetchingWowInVBwank = %f\n", __func__, s->TimeFowFetchingWowInVBwank);
		dmw_pwint("DMW::%s: WineTime = %f\n", __func__, s->WineTime);
		dmw_pwint("DMW::%s: DestinationWinesToWequestWowInVBwank = %f\n", __func__, *p->DestinationWinesToWequestWowInVBwank);
		dmw_pwint("DMW::%s: PwefetchSouwceWinesY = %f\n", __func__, p->PwefetchSouwceWinesY);
		dmw_pwint("DMW::%s: WinesToWequestPwefetchPixewData = %f\n", __func__, s->WinesToWequestPwefetchPixewData);
#endif

		if (s->WinesToWequestPwefetchPixewData >= 1 && s->pwefetch_bw_equ > 0) {
			*p->VWatioPwefetchY = (dmw_fwoat_t)p->PwefetchSouwceWinesY / s->WinesToWequestPwefetchPixewData;
			*p->VWatioPwefetchY = dmw_max(*p->VWatioPwefetchY, 1.0);
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: VWatioPwefetchY = %f\n", __func__, *p->VWatioPwefetchY);
			dmw_pwint("DMW::%s: SwathHeightY = %u\n", __func__, p->SwathHeightY);
			dmw_pwint("DMW::%s: VInitPweFiwwY = %u\n", __func__, p->VInitPweFiwwY);
#endif
			if ((p->SwathHeightY > 4) && (p->VInitPweFiwwY > 3)) {
				if (s->WinesToWequestPwefetchPixewData > (p->VInitPweFiwwY - 3.0) / 2.0) {
					*p->VWatioPwefetchY = dmw_max(*p->VWatioPwefetchY,
										(dmw_fwoat_t)p->MaxNumSwathY * p->SwathHeightY / (s->WinesToWequestPwefetchPixewData - (p->VInitPweFiwwY - 3.0) / 2.0));
			} ewse {
				s->MyEwwow = twue;
				dmw_pwint("DMW::%s: MyEww set. WinesToWequestPwefetchPixewData=%f VinitPweFiwwY=%u\n", __func__, s->WinesToWequestPwefetchPixewData, p->VInitPweFiwwY);
				*p->VWatioPwefetchY = 0;
			}
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: VWatioPwefetchY = %f\n", __func__, *p->VWatioPwefetchY);
			dmw_pwint("DMW::%s: PwefetchSouwceWinesY = %f\n", __func__, p->PwefetchSouwceWinesY);
			dmw_pwint("DMW::%s: MaxNumSwathY = %u\n", __func__, p->MaxNumSwathY);
#endif
			}

			*p->VWatioPwefetchC = (dmw_fwoat_t)p->PwefetchSouwceWinesC / s->WinesToWequestPwefetchPixewData;
			*p->VWatioPwefetchC = dmw_max(*p->VWatioPwefetchC, 1.0);

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: VWatioPwefetchC = %f\n", __func__, *p->VWatioPwefetchC);
			dmw_pwint("DMW::%s: SwathHeightC = %u\n", __func__, p->SwathHeightC);
			dmw_pwint("DMW::%s: VInitPweFiwwC = %u\n", __func__, p->VInitPweFiwwC);
#endif
			if ((p->SwathHeightC > 4) && (p->VInitPweFiwwC > 3)) {
				if (s->WinesToWequestPwefetchPixewData > (p->VInitPweFiwwC - 3.0) / 2.0) {
					*p->VWatioPwefetchC = dmw_max(*p->VWatioPwefetchC, (dmw_fwoat_t)p->MaxNumSwathC * p->SwathHeightC / (s->WinesToWequestPwefetchPixewData - (p->VInitPweFiwwC - 3.0) / 2.0));
				} ewse {
					s->MyEwwow = twue;
					dmw_pwint("DMW::%s: MyEww set. WinesToWequestPwefetchPixewData=%f VInitPweFiwwC=%u\n", __func__, s->WinesToWequestPwefetchPixewData, p->VInitPweFiwwC);
					*p->VWatioPwefetchC = 0;
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: VWatioPwefetchC = %f\n", __func__, *p->VWatioPwefetchC);
				dmw_pwint("DMW::%s: PwefetchSouwceWinesC = %f\n", __func__, p->PwefetchSouwceWinesC);
				dmw_pwint("DMW::%s: MaxNumSwathC = %u\n", __func__, p->MaxNumSwathC);
#endif
			}

			*p->WequiwedPwefetchPixDataBWWuma = (dmw_fwoat_t)p->PwefetchSouwceWinesY / s->WinesToWequestPwefetchPixewData
				* p->myPipe->BytePewPixewY
				* p->swath_width_wuma_ub / s->WineTime;

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: BytePewPixewY = %u\n", __func__, p->myPipe->BytePewPixewY);
			dmw_pwint("DMW::%s: swath_width_wuma_ub = %u\n", __func__, p->swath_width_wuma_ub);
			dmw_pwint("DMW::%s: WineTime = %f\n", __func__, s->WineTime);
			dmw_pwint("DMW::%s: WequiwedPwefetchPixDataBWWuma = %f\n", __func__, *p->WequiwedPwefetchPixDataBWWuma);
#endif
			*p->WequiwedPwefetchPixDataBWChwoma = (dmw_fwoat_t)p->PwefetchSouwceWinesC / s->WinesToWequestPwefetchPixewData
				*p->myPipe->BytePewPixewC
				*p->swath_width_chwoma_ub / s->WineTime;
		} ewse {
			s->MyEwwow = twue;
			dmw_pwint("DMW:%s: MyEww set. WinesToWequestPwefetchPixewData: %f, shouwd be > 0\n", __func__, s->WinesToWequestPwefetchPixewData);
			*p->VWatioPwefetchY = 0;
			*p->VWatioPwefetchC = 0;
			*p->WequiwedPwefetchPixDataBWWuma = 0;
			*p->WequiwedPwefetchPixDataBWChwoma = 0;
		}

		dmw_pwint("DMW: Tpwe: %fus - sum of time to wequest meta pte, 2 x data pte + meta data, swaths\n", (dmw_fwoat_t)s->WinesToWequestPwefetchPixewData * s->WineTime + 2.0 * s->TimeFowFetchingWowInVBwank + s->TimeFowFetchingMetaPTE);
		dmw_pwint("DMW: Tvm: %fus - time to fetch page tabwes fow meta suwface\n", s->TimeFowFetchingMetaPTE);
		dmw_pwint("DMW: Tw0: %fus - time to fetch fiwst wow of data pagetabwes and fiwst wow of meta data (done in pawawwew)\n", s->TimeFowFetchingWowInVBwank);
		dmw_pwint("DMW: Tsw: %fus = time to fetch enough pixew data and cuwsow data to feed the scawews init position and detiwe\n", (dmw_fwoat_t)s->WinesToWequestPwefetchPixewData * s->WineTime);
		dmw_pwint("DMW: To: %fus - time fow pwopagation fwom scawew to optc\n", (*p->DSTYAftewScawew + ((dmw_fwoat_t) (*p->DSTXAftewScawew) / (dmw_fwoat_t)p->myPipe->HTotaw)) * s->WineTime);
		dmw_pwint("DMW: Tvstawtup - TSetup - Tcawc - Twait - Tpwe - To > 0\n");
		dmw_pwint("DMW: Tswack(pwe): %fus - time weft ovew in scheduwe\n", p->VStawtup * s->WineTime - s->TimeFowFetchingMetaPTE - 2 * s->TimeFowFetchingWowInVBwank - (*p->DSTYAftewScawew + ((dmw_fwoat_t) (*p->DSTXAftewScawew) / (dmw_fwoat_t)p->myPipe->HTotaw)) * s->WineTime - p->TWait - p->TCawc - *p->TSetup);
		dmw_pwint("DMW: wow_bytes = dpte_wow_bytes (pew_pipe) = PixewPTEBytesPewWow = : %u\n", p->PixewPTEBytesPewWow);

	} ewse {
		s->MyEwwow = twue;
		dmw_pwint("DMW::%s: MyEww set, dst_y_pwefetch_equ = %f (shouwd be > 1)\n", __func__, s->dst_y_pwefetch_equ);
		s->TimeFowFetchingMetaPTE = 0;
		s->TimeFowFetchingWowInVBwank = 0;
		*p->DestinationWinesToWequestVMInVBwank = 0;
		*p->DestinationWinesToWequestWowInVBwank = 0;
		s->WinesToWequestPwefetchPixewData = 0;
		*p->VWatioPwefetchY = 0;
		*p->VWatioPwefetchC = 0;
		*p->WequiwedPwefetchPixDataBWWuma = 0;
		*p->WequiwedPwefetchPixDataBWChwoma = 0;
	}

	{
		dmw_fwoat_t pwefetch_vm_bw;
		dmw_fwoat_t pwefetch_wow_bw;

		if (p->PDEAndMetaPTEBytesFwame == 0) {
			pwefetch_vm_bw = 0;
		} ewse if (*p->DestinationWinesToWequestVMInVBwank > 0) {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %u\n", __func__, p->PDEAndMetaPTEBytesFwame);
			dmw_pwint("DMW::%s: HostVMInefficiencyFactow = %f\n", __func__, p->HostVMInefficiencyFactow);
			dmw_pwint("DMW::%s: DestinationWinesToWequestVMInVBwank = %f\n", __func__, *p->DestinationWinesToWequestVMInVBwank);
			dmw_pwint("DMW::%s: WineTime = %f\n", __func__, s->WineTime);
#endif
		pwefetch_vm_bw = p->PDEAndMetaPTEBytesFwame * p->HostVMInefficiencyFactow / (*p->DestinationWinesToWequestVMInVBwank * s->WineTime);
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: pwefetch_vm_bw = %f\n", __func__, pwefetch_vm_bw);
#endif
		} ewse {
			pwefetch_vm_bw = 0;
			s->MyEwwow = twue;
			dmw_pwint("DMW::%s: MyEww set. DestinationWinesToWequestVMInVBwank=%f (shouwd be > 0)\n", __func__, *p->DestinationWinesToWequestVMInVBwank);
		}

		if (p->MetaWowByte + p->PixewPTEBytesPewWow == 0) {
			pwefetch_wow_bw = 0;
		} ewse if (*p->DestinationWinesToWequestWowInVBwank > 0) {
			pwefetch_wow_bw = (p->MetaWowByte + p->PixewPTEBytesPewWow * p->HostVMInefficiencyFactow) / (*p->DestinationWinesToWequestWowInVBwank * s->WineTime);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: MetaWowByte = %u\n", __func__, p->MetaWowByte);
		dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %u\n", __func__, p->PixewPTEBytesPewWow);
		dmw_pwint("DMW::%s: DestinationWinesToWequestWowInVBwank = %f\n", __func__, *p->DestinationWinesToWequestWowInVBwank);
		dmw_pwint("DMW::%s: pwefetch_wow_bw = %f\n", __func__, pwefetch_wow_bw);
#endif
		} ewse {
			pwefetch_wow_bw = 0;
			s->MyEwwow = twue;
			dmw_pwint("DMW::%s: MyEww set. DestinationWinesToWequestWowInVBwank=%f (shouwd be > 0)\n", __func__, *p->DestinationWinesToWequestWowInVBwank);
		}

		*p->pwefetch_vmwow_bw = dmw_max(pwefetch_vm_bw, pwefetch_wow_bw);
	}

	if (s->MyEwwow) {
		s->TimeFowFetchingMetaPTE = 0;
		s->TimeFowFetchingWowInVBwank = 0;
		*p->DestinationWinesToWequestVMInVBwank = 0;
		*p->DestinationWinesToWequestWowInVBwank = 0;
		*p->DestinationWinesFowPwefetch = 0;
		s->WinesToWequestPwefetchPixewData = 0;
		*p->VWatioPwefetchY = 0;
		*p->VWatioPwefetchC = 0;
		*p->WequiwedPwefetchPixDataBWWuma = 0;
		*p->WequiwedPwefetchPixDataBWChwoma = 0;
	}

	wetuwn s->MyEwwow;
} // CawcuwatePwefetchScheduwe

static void CawcuwateBytePewPixewAndBwockSizes(
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
	enum dmw_swizzwe_mode SuwfaceTiwing,

	// Output
	dmw_uint_t *BytePewPixewY,
	dmw_uint_t *BytePewPixewC,
	dmw_fwoat_t *BytePewPixewDETY,
	dmw_fwoat_t *BytePewPixewDETC,
	dmw_uint_t *BwockHeight256BytesY,
	dmw_uint_t *BwockHeight256BytesC,
	dmw_uint_t *BwockWidth256BytesY,
	dmw_uint_t *BwockWidth256BytesC,
	dmw_uint_t *MacwoTiweHeightY,
	dmw_uint_t *MacwoTiweHeightC,
	dmw_uint_t *MacwoTiweWidthY,
	dmw_uint_t *MacwoTiweWidthC)
{
	if (SouwcePixewFowmat == dmw_444_64) {
		*BytePewPixewDETY = 8;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 8;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dmw_444_32 || SouwcePixewFowmat == dmw_wgbe) {
		*BytePewPixewDETY = 4;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 4;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dmw_444_16 || SouwcePixewFowmat == dmw_mono_16) {
		*BytePewPixewDETY = 2;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 2;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dmw_444_8 || SouwcePixewFowmat == dmw_mono_8) {
		*BytePewPixewDETY = 1;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 1;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dmw_wgbe_awpha) {
		*BytePewPixewDETY = 4;
		*BytePewPixewDETC = 1;
		*BytePewPixewY = 4;
		*BytePewPixewC = 1;
	} ewse if (SouwcePixewFowmat == dmw_420_8) {
		*BytePewPixewDETY = 1;
		*BytePewPixewDETC = 2;
		*BytePewPixewY = 1;
		*BytePewPixewC = 2;
	} ewse if (SouwcePixewFowmat == dmw_420_12) {
		*BytePewPixewDETY = 2;
		*BytePewPixewDETC = 4;
		*BytePewPixewY = 2;
		*BytePewPixewC = 4;
	} ewse {
		*BytePewPixewDETY = (dmw_fwoat_t) (4.0 / 3);
		*BytePewPixewDETC = (dmw_fwoat_t) (8.0 / 3);
		*BytePewPixewY = 2;
		*BytePewPixewC = 4;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: SouwcePixewFowmat = %u\n", __func__, SouwcePixewFowmat);
	dmw_pwint("DMW::%s: BytePewPixewDETY = %f\n", __func__, *BytePewPixewDETY);
	dmw_pwint("DMW::%s: BytePewPixewDETC = %f\n", __func__, *BytePewPixewDETC);
	dmw_pwint("DMW::%s: BytePewPixewY = %u\n", __func__, *BytePewPixewY);
	dmw_pwint("DMW::%s: BytePewPixewC = %u\n", __func__, *BytePewPixewC);
#endif
	if ((SouwcePixewFowmat == dmw_444_64 || SouwcePixewFowmat == dmw_444_32
		|| SouwcePixewFowmat == dmw_444_16
		|| SouwcePixewFowmat == dmw_444_8
		|| SouwcePixewFowmat == dmw_mono_16
		|| SouwcePixewFowmat == dmw_mono_8
		|| SouwcePixewFowmat == dmw_wgbe)) {
		if (SuwfaceTiwing == dmw_sw_wineaw) {
			*BwockHeight256BytesY = 1;
		} ewse if (SouwcePixewFowmat == dmw_444_64) {
			*BwockHeight256BytesY = 4;
		} ewse if (SouwcePixewFowmat == dmw_444_8) {
			*BwockHeight256BytesY = 16;
		} ewse {
			*BwockHeight256BytesY = 8;
		}
		*BwockWidth256BytesY = 256U / *BytePewPixewY / *BwockHeight256BytesY;
		*BwockHeight256BytesC = 0;
		*BwockWidth256BytesC = 0;
	} ewse {
		if (SuwfaceTiwing == dmw_sw_wineaw) {
			*BwockHeight256BytesY = 1;
			*BwockHeight256BytesC = 1;
		} ewse if (SouwcePixewFowmat == dmw_wgbe_awpha) {
			*BwockHeight256BytesY = 8;
			*BwockHeight256BytesC = 16;
		} ewse if (SouwcePixewFowmat == dmw_420_8) {
			*BwockHeight256BytesY = 16;
			*BwockHeight256BytesC = 8;
		} ewse {
			*BwockHeight256BytesY = 8;
			*BwockHeight256BytesC = 8;
		}
		*BwockWidth256BytesY = 256U / *BytePewPixewY / *BwockHeight256BytesY;
		*BwockWidth256BytesC = 256U / *BytePewPixewC / *BwockHeight256BytesC;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: BwockWidth256BytesY = %u\n", __func__, *BwockWidth256BytesY);
	dmw_pwint("DMW::%s: BwockHeight256BytesY = %u\n", __func__, *BwockHeight256BytesY);
	dmw_pwint("DMW::%s: BwockWidth256BytesC = %u\n", __func__, *BwockWidth256BytesC);
	dmw_pwint("DMW::%s: BwockHeight256BytesC = %u\n", __func__, *BwockHeight256BytesC);
#endif

	if (SuwfaceTiwing == dmw_sw_wineaw) {
		*MacwoTiweHeightY = *BwockHeight256BytesY;
		*MacwoTiweWidthY = 256 / *BytePewPixewY / *MacwoTiweHeightY;
		*MacwoTiweHeightC = *BwockHeight256BytesC;
		if (*MacwoTiweHeightC == 0) {
			*MacwoTiweWidthC = 0;
		} ewse {
			*MacwoTiweWidthC = 256 / *BytePewPixewC / *MacwoTiweHeightC;
	}
	} ewse if (SuwfaceTiwing == dmw_sw_64kb_d || SuwfaceTiwing == dmw_sw_64kb_d_t || SuwfaceTiwing == dmw_sw_64kb_d_x || SuwfaceTiwing == dmw_sw_64kb_w_x) {
		*MacwoTiweHeightY = 16 * *BwockHeight256BytesY;
		*MacwoTiweWidthY = 65536 / *BytePewPixewY / *MacwoTiweHeightY;
		*MacwoTiweHeightC = 16 * *BwockHeight256BytesC;
		if (*MacwoTiweHeightC == 0) {
			*MacwoTiweWidthC = 0;
		} ewse {
			*MacwoTiweWidthC = 65536 / *BytePewPixewC / *MacwoTiweHeightC;
		}
	} ewse {
		*MacwoTiweHeightY = 32 * *BwockHeight256BytesY;
		*MacwoTiweWidthY = 65536 * 4 / *BytePewPixewY / *MacwoTiweHeightY;
		*MacwoTiweHeightC = 32 * *BwockHeight256BytesC;
		if (*MacwoTiweHeightC == 0) {
			*MacwoTiweWidthC = 0;
		} ewse {
			*MacwoTiweWidthC = 65536 * 4 / *BytePewPixewC / *MacwoTiweHeightC;
		}
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: MacwoTiweWidthY = %u\n", __func__, *MacwoTiweWidthY);
	dmw_pwint("DMW::%s: MacwoTiweHeightY = %u\n", __func__, *MacwoTiweHeightY);
	dmw_pwint("DMW::%s: MacwoTiweWidthC = %u\n", __func__, *MacwoTiweWidthC);
	dmw_pwint("DMW::%s: MacwoTiweHeightC = %u\n", __func__, *MacwoTiweHeightC);
#endif
} // CawcuwateBytePewPixewAndBwockSizes

static dmw_fwoat_t CawcuwateTWait(
		dmw_uint_t PwefetchMode,
		enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
		dmw_boow_t SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
		dmw_boow_t DWWDispway,
		dmw_fwoat_t DWAMCwockChangeWatency,
		dmw_fwoat_t FCWKChangeWatency,
		dmw_fwoat_t UwgentWatency,
		dmw_fwoat_t SWEntewPwusExitTime)
{
	dmw_fwoat_t TWait = 0.0;

	if (PwefetchMode == 0 &&
			!(UseMAWWFowPStateChange == dmw_use_maww_pstate_change_fuww_fwame) && !(UseMAWWFowPStateChange == dmw_use_maww_pstate_change_sub_viewpowt) &&
			!(UseMAWWFowPStateChange == dmw_use_maww_pstate_change_phantom_pipe) && !(SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw && DWWDispway)) {
		TWait = dmw_max3(DWAMCwockChangeWatency + UwgentWatency, SWEntewPwusExitTime, UwgentWatency);
	} ewse if (PwefetchMode <= 1 && !(UseMAWWFowPStateChange == dmw_use_maww_pstate_change_phantom_pipe)) {
		TWait = dmw_max3(FCWKChangeWatency + UwgentWatency, SWEntewPwusExitTime, UwgentWatency);
	} ewse if (PwefetchMode <= 2 && !(UseMAWWFowPStateChange == dmw_use_maww_pstate_change_phantom_pipe)) {
		TWait = dmw_max(SWEntewPwusExitTime, UwgentWatency);
	} ewse {
		TWait = UwgentWatency;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: PwefetchMode = %u\n", __func__, PwefetchMode);
	dmw_pwint("DMW::%s: TWait = %f\n", __func__, TWait);
#endif
	wetuwn TWait;
} // CawcuwateTWait


/// @bwief Cawcuwate the "stawting point" fow pwefetch cawcuwation
///  if AwwowFowPStateChangeOwStuttewInVBwank is set as a pawticuwaw wequiwement, then the mode evawuwation
///  wiww onwy be done at the given mode. If no specific wequiwement (i.e. *_if_possibwe), then wiww just go fwom
///  twy aww the pwefetch mode in decweasing owdew of "difficuwty" (stawt fwom 0 which means aww powew saving
///  featuwes).
static void CawcuwatePwefetchMode(
		enum dmw_pwefetch_modes AwwowFowPStateChangeOwStuttewInVBwank,
		dmw_uint_t *MinPwefetchMode,
		dmw_uint_t *MaxPwefetchMode)
{
	if (AwwowFowPStateChangeOwStuttewInVBwank == dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew_if_possibwe) {
		*MinPwefetchMode = 0;   // considew aww pww saving featuwes
		*MaxPwefetchMode = 3;   // considew just uwgent watency
	} ewse {
		if (AwwowFowPStateChangeOwStuttewInVBwank == dmw_pwefetch_suppowt_none) {
			*MinPwefetchMode = 3;
		} ewse if (AwwowFowPStateChangeOwStuttewInVBwank == dmw_pwefetch_suppowt_stuttew) {
			*MinPwefetchMode = 2;
		} ewse if (AwwowFowPStateChangeOwStuttewInVBwank == dmw_pwefetch_suppowt_fcwk_and_stuttew) {
			*MinPwefetchMode = 1;
		} ewse if (AwwowFowPStateChangeOwStuttewInVBwank == dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew) {
			*MinPwefetchMode = 0;
		} ewse {
			dmw_pwint("EWWOW: Invawid AwwowFowPStateChangeOwStuttewInVBwank setting! vaw=%u\n", AwwowFowPStateChangeOwStuttewInVBwank);
			ASSEWT(0);
		}
		*MaxPwefetchMode = *MinPwefetchMode;
	}
} // CawcuwatePwefetchMode

static dmw_fwoat_t CawcuwateWwiteBackDISPCWK(
		enum dmw_souwce_fowmat_cwass WwitebackPixewFowmat,
		dmw_fwoat_t PixewCwock,
		dmw_fwoat_t WwitebackHWatio,
		dmw_fwoat_t WwitebackVWatio,
		dmw_uint_t WwitebackHTaps,
		dmw_uint_t WwitebackVTaps,
		dmw_uint_t WwitebackSouwceWidth,
		dmw_uint_t WwitebackDestinationWidth,
		dmw_uint_t HTotaw,
		dmw_uint_t WwitebackWineBuffewSize,
		dmw_fwoat_t DISPCWKDPPCWKVCOSpeed)
{
	dmw_fwoat_t DISPCWK_H, DISPCWK_V, DISPCWK_HB;

	DISPCWK_H = PixewCwock * dmw_ceiw(WwitebackHTaps / 8.0, 1) / WwitebackHWatio;
	DISPCWK_V = PixewCwock * (WwitebackVTaps * dmw_ceiw(WwitebackDestinationWidth / 6.0, 1) + 8.0) / (dmw_fwoat_t) HTotaw;
	DISPCWK_HB = PixewCwock * WwitebackVTaps * (WwitebackDestinationWidth * WwitebackVTaps - WwitebackWineBuffewSize / 57.0) / 6.0 / (dmw_fwoat_t) WwitebackSouwceWidth;
	wetuwn WoundToDFSGwanuwawity(dmw_max3(DISPCWK_H, DISPCWK_V, DISPCWK_HB), 1, DISPCWKDPPCWKVCOSpeed);
}

static dmw_fwoat_t CawcuwateWwiteBackDeway(
		enum dmw_souwce_fowmat_cwass WwitebackPixewFowmat,
		dmw_fwoat_t WwitebackHWatio,
		dmw_fwoat_t WwitebackVWatio,
		dmw_uint_t WwitebackVTaps,
		dmw_uint_t WwitebackDestinationWidth,
		dmw_uint_t WwitebackDestinationHeight,
		dmw_uint_t WwitebackSouwceHeight,
		dmw_uint_t HTotaw)
{
	dmw_fwoat_t CawcuwateWwiteBackDeway;
	dmw_fwoat_t Wine_wength;
	dmw_fwoat_t Output_wines_wast_notcwamped;
	dmw_fwoat_t WwitebackVInit;

	WwitebackVInit = (WwitebackVWatio + WwitebackVTaps + 1) / 2;
	Wine_wength = dmw_max((dmw_fwoat_t) WwitebackDestinationWidth, dmw_ceiw((dmw_fwoat_t)WwitebackDestinationWidth / 6.0, 1.0) * WwitebackVTaps);
	Output_wines_wast_notcwamped = WwitebackDestinationHeight - 1 - dmw_ceiw(((dmw_fwoat_t)WwitebackSouwceHeight - (dmw_fwoat_t) WwitebackVInit) / (dmw_fwoat_t)WwitebackVWatio, 1.0);
	if (Output_wines_wast_notcwamped < 0) {
		CawcuwateWwiteBackDeway = 0;
	} ewse {
		CawcuwateWwiteBackDeway = Output_wines_wast_notcwamped * Wine_wength + (HTotaw - WwitebackDestinationWidth) + 80;
	}
	wetuwn CawcuwateWwiteBackDeway;
}

static void CawcuwateVUpdateAndDynamicMetadataPawametews(
		dmw_uint_t MaxIntewDCNTiweWepeatews,
		dmw_fwoat_t Dppcwk,
		dmw_fwoat_t Dispcwk,
		dmw_fwoat_t DCFCwkDeepSweep,
		dmw_fwoat_t PixewCwock,
		dmw_uint_t HTotaw,
		dmw_uint_t VBwank,
		dmw_uint_t DynamicMetadataTwansmittedBytes,
		dmw_uint_t DynamicMetadataWinesBefoweActiveWequiwed,
		dmw_uint_t IntewwaceEnabwe,
		dmw_boow_t PwogwessiveToIntewwaceUnitInOPP,

		// Output
		dmw_fwoat_t *TSetup,
		dmw_fwoat_t *Tdmbf,
		dmw_fwoat_t *Tdmec,
		dmw_fwoat_t *Tdmsks,
		dmw_uint_t *VUpdateOffsetPix,
		dmw_uint_t *VUpdateWidthPix,
		dmw_uint_t *VWeadyOffsetPix)
{
	dmw_fwoat_t TotawWepeatewDewayTime;
	TotawWepeatewDewayTime = MaxIntewDCNTiweWepeatews * (2 / Dppcwk + 3 / Dispcwk);
	*VUpdateWidthPix = (dmw_uint_t)(dmw_ceiw((14.0 / DCFCwkDeepSweep + 12.0 / Dppcwk + TotawWepeatewDewayTime) * PixewCwock, 1.0));
	*VWeadyOffsetPix = (dmw_uint_t)(dmw_ceiw(dmw_max(150.0 / Dppcwk, TotawWepeatewDewayTime + 20.0 / DCFCwkDeepSweep + 10.0 / Dppcwk) * PixewCwock, 1.0));
	*VUpdateOffsetPix = (dmw_uint_t)(dmw_ceiw(HTotaw / 4.0, 1.0));
	*TSetup = (*VUpdateOffsetPix + *VUpdateWidthPix + *VWeadyOffsetPix) / PixewCwock;
	*Tdmbf = DynamicMetadataTwansmittedBytes / 4.0 / Dispcwk;
	*Tdmec = HTotaw / PixewCwock;

	if (DynamicMetadataWinesBefoweActiveWequiwed == 0) {
		*Tdmsks = VBwank * HTotaw / PixewCwock / 2.0;
	} ewse {
		*Tdmsks = DynamicMetadataWinesBefoweActiveWequiwed * HTotaw / PixewCwock;
	}
	if (IntewwaceEnabwe == 1 && PwogwessiveToIntewwaceUnitInOPP == fawse) {
		*Tdmsks = *Tdmsks / 2;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DynamicMetadataWinesBefoweActiveWequiwed = %u\n", __func__, DynamicMetadataWinesBefoweActiveWequiwed);
	dmw_pwint("DMW::%s: VBwank = %u\n", __func__, VBwank);
	dmw_pwint("DMW::%s: HTotaw = %u\n", __func__, HTotaw);
	dmw_pwint("DMW::%s: PixewCwock = %f\n", __func__, PixewCwock);
	dmw_pwint("DMW::%s: Dppcwk = %f\n", __func__, Dppcwk);
	dmw_pwint("DMW::%s: DCFCwkDeepSweep = %f\n", __func__, DCFCwkDeepSweep);
	dmw_pwint("DMW::%s: MaxIntewDCNTiweWepeatews = %u\n", __func__, MaxIntewDCNTiweWepeatews);
	dmw_pwint("DMW::%s: TotawWepeatewDewayTime = %f\n", __func__, TotawWepeatewDewayTime);

	dmw_pwint("DMW::%s: VUpdateWidthPix = %u\n", __func__, *VUpdateWidthPix);
	dmw_pwint("DMW::%s: VWeadyOffsetPix = %u\n", __func__, *VWeadyOffsetPix);
	dmw_pwint("DMW::%s: VUpdateOffsetPix = %u\n", __func__, *VUpdateOffsetPix);

	dmw_pwint("DMW::%s: Tdmsks = %f\n", __func__, *Tdmsks);
#endif
}

static void CawcuwateWowBandwidth(
		dmw_boow_t GPUVMEnabwe,
		enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
		dmw_fwoat_t VWatio,
		dmw_fwoat_t VWatioChwoma,
		dmw_boow_t DCCEnabwe,
		dmw_fwoat_t WineTime,
		dmw_uint_t MetaWowByteWuma,
		dmw_uint_t MetaWowByteChwoma,
		dmw_uint_t meta_wow_height_wuma,
		dmw_uint_t meta_wow_height_chwoma,
		dmw_uint_t PixewPTEBytesPewWowWuma,
		dmw_uint_t PixewPTEBytesPewWowChwoma,
		dmw_uint_t dpte_wow_height_wuma,
		dmw_uint_t dpte_wow_height_chwoma,
		// Output
		dmw_fwoat_t *meta_wow_bw,
		dmw_fwoat_t *dpte_wow_bw)
{
	if (DCCEnabwe != twue) {
		*meta_wow_bw = 0;
	} ewse if (SouwcePixewFowmat == dmw_420_8 || SouwcePixewFowmat == dmw_420_10 || SouwcePixewFowmat == dmw_420_12 || SouwcePixewFowmat == dmw_wgbe_awpha) {
		*meta_wow_bw = VWatio * MetaWowByteWuma / (meta_wow_height_wuma * WineTime)
				+ VWatioChwoma * MetaWowByteChwoma
					/ (meta_wow_height_chwoma * WineTime);
	} ewse {
		*meta_wow_bw = VWatio * MetaWowByteWuma / (meta_wow_height_wuma * WineTime);
	}

	if (GPUVMEnabwe != twue) {
		*dpte_wow_bw = 0;
	} ewse if (SouwcePixewFowmat == dmw_420_8 || SouwcePixewFowmat == dmw_420_10 || SouwcePixewFowmat == dmw_420_12 || SouwcePixewFowmat == dmw_wgbe_awpha) {
		*dpte_wow_bw = VWatio * PixewPTEBytesPewWowWuma / (dpte_wow_height_wuma * WineTime)
				+ VWatioChwoma * PixewPTEBytesPewWowChwoma
					/ (dpte_wow_height_chwoma * WineTime);
	} ewse {
		*dpte_wow_bw = VWatio * PixewPTEBytesPewWowWuma / (dpte_wow_height_wuma * WineTime);
	}
}

/// @bwief Detewmine immediate fwip scheduwe given bw wemaining aftew considewing the pwefetch scheduwe
/// @pawam BandwidthAvaiwabweFowImmediateFwip Bandwidth avaiwabwe fow ifwip fow aww pwanes
static void CawcuwateFwipScheduwe(
		dmw_fwoat_t HostVMInefficiencyFactow,
		dmw_fwoat_t UwgentExtwaWatency,
		dmw_fwoat_t UwgentWatency,
		dmw_uint_t GPUVMMaxPageTabweWevews,
		dmw_boow_t HostVMEnabwe,
		dmw_uint_t HostVMMaxNonCachedPageTabweWevews,
		dmw_boow_t GPUVMEnabwe,
		dmw_uint_t HostVMMinPageSize,
		dmw_fwoat_t PDEAndMetaPTEBytesPewFwame,
		dmw_fwoat_t MetaWowBytes,
		dmw_fwoat_t DPTEBytesPewWow,
		dmw_fwoat_t BandwidthAvaiwabweFowImmediateFwip,
		dmw_uint_t TotImmediateFwipBytes,
		enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
		dmw_fwoat_t WineTime,
		dmw_fwoat_t VWatio,
		dmw_fwoat_t VWatioChwoma,
		dmw_fwoat_t Tno_bw,
		dmw_boow_t DCCEnabwe,
		dmw_uint_t dpte_wow_height,
		dmw_uint_t meta_wow_height,
		dmw_uint_t dpte_wow_height_chwoma,
		dmw_uint_t meta_wow_height_chwoma,
		dmw_boow_t use_one_wow_fow_fwame_fwip,

		// Output
		dmw_fwoat_t *DestinationWinesToWequestVMInImmediateFwip,
		dmw_fwoat_t *DestinationWinesToWequestWowInImmediateFwip,
		dmw_fwoat_t *finaw_fwip_bw,
		dmw_boow_t *ImmediateFwipSuppowtedFowPipe)
{
	dmw_fwoat_t min_wow_time = 0.0;
	dmw_uint_t HostVMDynamicWevewsTwips = 0;
	dmw_fwoat_t TimeFowFetchingMetaPTEImmediateFwip = 0;
	dmw_fwoat_t TimeFowFetchingWowInVBwankImmediateFwip = 0;
	dmw_fwoat_t ImmediateFwipBW = 0; // @bwief The immediate fwip bandwidth fow this pipe

	if (GPUVMEnabwe == twue && HostVMEnabwe == twue) {
		HostVMDynamicWevewsTwips = HostVMMaxNonCachedPageTabweWevews;
	} ewse {
		HostVMDynamicWevewsTwips = 0;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: TotImmediateFwipBytes = %u\n", __func__, TotImmediateFwipBytes);
	dmw_pwint("DMW::%s: HostVMInefficiencyFactow = %f\n", __func__, HostVMInefficiencyFactow);
	dmw_pwint("DMW::%s: UwgentWatency = %f\n", __func__, UwgentWatency);
	dmw_pwint("DMW::%s: BandwidthAvaiwabweFowImmediateFwip = %f\n", __func__, BandwidthAvaiwabweFowImmediateFwip);
#endif

	if (TotImmediateFwipBytes > 0) {
		if (use_one_wow_fow_fwame_fwip) {
			ImmediateFwipBW = (PDEAndMetaPTEBytesPewFwame + MetaWowBytes + 2.0 * DPTEBytesPewWow) * BandwidthAvaiwabweFowImmediateFwip / (dmw_fwoat_t) TotImmediateFwipBytes;
		} ewse {
			ImmediateFwipBW = (PDEAndMetaPTEBytesPewFwame + MetaWowBytes + DPTEBytesPewWow) * BandwidthAvaiwabweFowImmediateFwip / (dmw_fwoat_t) TotImmediateFwipBytes;
		}
		if (GPUVMEnabwe == twue) {
			TimeFowFetchingMetaPTEImmediateFwip = dmw_max3(Tno_bw + PDEAndMetaPTEBytesPewFwame * HostVMInefficiencyFactow / ImmediateFwipBW,
														UwgentExtwaWatency + UwgentWatency * (GPUVMMaxPageTabweWevews * (HostVMDynamicWevewsTwips + 1) - 1),
														WineTime / 4.0);
		} ewse {
			TimeFowFetchingMetaPTEImmediateFwip = 0;
		}
		if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
			TimeFowFetchingWowInVBwankImmediateFwip = dmw_max3((MetaWowBytes + DPTEBytesPewWow * HostVMInefficiencyFactow) / ImmediateFwipBW, UwgentWatency * (HostVMDynamicWevewsTwips + 1), WineTime / 4.0);
		} ewse {
			TimeFowFetchingWowInVBwankImmediateFwip = 0;
		}

		*DestinationWinesToWequestVMInImmediateFwip = dmw_ceiw(4.0 * (TimeFowFetchingMetaPTEImmediateFwip / WineTime), 1.0) / 4.0;
		*DestinationWinesToWequestWowInImmediateFwip = dmw_ceiw(4.0 * (TimeFowFetchingWowInVBwankImmediateFwip / WineTime), 1.0) / 4.0;

		if (GPUVMEnabwe == twue) {
			*finaw_fwip_bw = dmw_max(PDEAndMetaPTEBytesPewFwame * HostVMInefficiencyFactow / (*DestinationWinesToWequestVMInImmediateFwip * WineTime),
								(MetaWowBytes + DPTEBytesPewWow * HostVMInefficiencyFactow) / (*DestinationWinesToWequestWowInImmediateFwip * WineTime));
		} ewse if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
			*finaw_fwip_bw = (MetaWowBytes + DPTEBytesPewWow * HostVMInefficiencyFactow) / (*DestinationWinesToWequestWowInImmediateFwip * WineTime);
		} ewse {
			*finaw_fwip_bw = 0;
		}
	} ewse {
		TimeFowFetchingMetaPTEImmediateFwip = 0;
		TimeFowFetchingWowInVBwankImmediateFwip = 0;
		*DestinationWinesToWequestVMInImmediateFwip = 0;
		*DestinationWinesToWequestWowInImmediateFwip = 0;
		*finaw_fwip_bw = 0;
	}

	if (SouwcePixewFowmat == dmw_420_8 || SouwcePixewFowmat == dmw_420_10 || SouwcePixewFowmat == dmw_wgbe_awpha) {
		if (GPUVMEnabwe == twue && DCCEnabwe != twue) {
			min_wow_time = dmw_min(dpte_wow_height * WineTime / VWatio, dpte_wow_height_chwoma * WineTime / VWatioChwoma);
		} ewse if (GPUVMEnabwe != twue && DCCEnabwe == twue) {
			min_wow_time = dmw_min(meta_wow_height * WineTime / VWatio, meta_wow_height_chwoma * WineTime / VWatioChwoma);
		} ewse {
			min_wow_time = dmw_min4(dpte_wow_height * WineTime / VWatio, meta_wow_height * WineTime / VWatio, dpte_wow_height_chwoma * WineTime / VWatioChwoma, meta_wow_height_chwoma * WineTime / VWatioChwoma);
		}
	} ewse {
		if (GPUVMEnabwe == twue && DCCEnabwe != twue) {
			min_wow_time = dpte_wow_height * WineTime / VWatio;
		} ewse if (GPUVMEnabwe != twue && DCCEnabwe == twue) {
			min_wow_time = meta_wow_height * WineTime / VWatio;
		} ewse {
			min_wow_time = dmw_min(dpte_wow_height * WineTime / VWatio, meta_wow_height * WineTime / VWatio);
		}
	}

	if (*DestinationWinesToWequestVMInImmediateFwip >= 32 || *DestinationWinesToWequestWowInImmediateFwip >= 16 || TimeFowFetchingMetaPTEImmediateFwip + 2 * TimeFowFetchingWowInVBwankImmediateFwip > min_wow_time) {
		*ImmediateFwipSuppowtedFowPipe = fawse;
	} ewse {
		*ImmediateFwipSuppowtedFowPipe = twue;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: GPUVMEnabwe = %u\n", __func__, GPUVMEnabwe);
	dmw_pwint("DMW::%s: DCCEnabwe = %u\n", __func__, DCCEnabwe);

	dmw_pwint("DMW::%s: MetaWowBytes = %f\n", __func__, MetaWowBytes);
	dmw_pwint("DMW::%s: DPTEBytesPewWow = %f\n", __func__, DPTEBytesPewWow);
	dmw_pwint("DMW::%s: BandwidthAvaiwabweFowImmediateFwip = %f\n", __func__, BandwidthAvaiwabweFowImmediateFwip);
	dmw_pwint("DMW::%s: TotImmediateFwipBytes = %u\n", __func__, TotImmediateFwipBytes);
	dmw_pwint("DMW::%s: ImmediateFwipBW = %f\n", __func__, ImmediateFwipBW);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesPewFwame = %f\n", __func__, PDEAndMetaPTEBytesPewFwame);
	dmw_pwint("DMW::%s: HostVMInefficiencyFactow = %f\n", __func__, HostVMInefficiencyFactow);
	dmw_pwint("DMW::%s: WineTime = %f\n", __func__, WineTime);
	dmw_pwint("DMW::%s: finaw_fwip_bw = %f\n", __func__, *finaw_fwip_bw);

	dmw_pwint("DMW::%s: DestinationWinesToWequestVMInImmediateFwip = %f\n", __func__, *DestinationWinesToWequestVMInImmediateFwip);
	dmw_pwint("DMW::%s: DestinationWinesToWequestWowInImmediateFwip = %f\n", __func__, *DestinationWinesToWequestWowInImmediateFwip);
	dmw_pwint("DMW::%s: TimeFowFetchingMetaPTEImmediateFwip = %f\n", __func__, TimeFowFetchingMetaPTEImmediateFwip);
	dmw_pwint("DMW::%s: TimeFowFetchingWowInVBwankImmediateFwip = %f\n", __func__, TimeFowFetchingWowInVBwankImmediateFwip);
	dmw_pwint("DMW::%s: min_wow_time = %f\n", __func__, min_wow_time);
	dmw_pwint("DMW::%s: ImmediateFwipSuppowtedFowPipe = %u\n", __func__, *ImmediateFwipSuppowtedFowPipe);
#endif
} // CawcuwateFwipScheduwe

static dmw_fwoat_t WoundToDFSGwanuwawity(dmw_fwoat_t Cwock, dmw_boow_t wound_up, dmw_fwoat_t VCOSpeed)
{
	if (Cwock <= 0.0)
		wetuwn 0.0;
	ewse {
		if (wound_up)
			wetuwn VCOSpeed * 4.0 / dmw_fwoow(VCOSpeed * 4.0 / Cwock, 1.0);
		ewse
			wetuwn VCOSpeed * 4.0 / dmw_ceiw(VCOSpeed * 4.0 / Cwock, 1.0);
	}
}

static void CawcuwateDCCConfiguwation(
		dmw_boow_t DCCEnabwed,
		dmw_boow_t DCCPwogwammingAssumesScanDiwectionUnknown,
		enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
		dmw_uint_t SuwfaceWidthWuma,
		dmw_uint_t SuwfaceWidthChwoma,
		dmw_uint_t SuwfaceHeightWuma,
		dmw_uint_t SuwfaceHeightChwoma,
		dmw_uint_t nomDETInKByte,
		dmw_uint_t WequestHeight256ByteWuma,
		dmw_uint_t WequestHeight256ByteChwoma,
		enum dmw_swizzwe_mode TiwingFowmat,
		dmw_uint_t BytePewPixewY,
		dmw_uint_t BytePewPixewC,
		dmw_fwoat_t BytePewPixewDETY,
		dmw_fwoat_t BytePewPixewDETC,
		enum dmw_wotation_angwe SouwceScan,
		// Output
		dmw_uint_t *MaxUncompwessedBwockWuma,
		dmw_uint_t *MaxUncompwessedBwockChwoma,
		dmw_uint_t *MaxCompwessedBwockWuma,
		dmw_uint_t *MaxCompwessedBwockChwoma,
		dmw_uint_t *IndependentBwockWuma,
		dmw_uint_t *IndependentBwockChwoma)
{
	dmw_uint_t DETBuffewSizeFowDCC = nomDETInKByte * 1024;

	dmw_uint_t yuv420;
	dmw_uint_t howz_div_w;
	dmw_uint_t howz_div_c;
	dmw_uint_t vewt_div_w;
	dmw_uint_t vewt_div_c;

	dmw_uint_t swath_buf_size;
	dmw_fwoat_t detiwe_buf_vp_howz_wimit;
	dmw_fwoat_t detiwe_buf_vp_vewt_wimit;

	dmw_uint_t MAS_vp_howz_wimit;
	dmw_uint_t MAS_vp_vewt_wimit;
	dmw_uint_t max_vp_howz_width;
	dmw_uint_t max_vp_vewt_height;
	dmw_uint_t eff_suwf_width_w;
	dmw_uint_t eff_suwf_width_c;
	dmw_uint_t eff_suwf_height_w;
	dmw_uint_t eff_suwf_height_c;

	dmw_uint_t fuww_swath_bytes_howz_wc_w;
	dmw_uint_t fuww_swath_bytes_howz_wc_c;
	dmw_uint_t fuww_swath_bytes_vewt_wc_w;
	dmw_uint_t fuww_swath_bytes_vewt_wc_c;

	dmw_uint_t weq128_howz_wc_w;
	dmw_uint_t weq128_howz_wc_c;
	dmw_uint_t weq128_vewt_wc_w;
	dmw_uint_t weq128_vewt_wc_c;

	dmw_uint_t   segment_owdew_howz_contiguous_wuma;
	dmw_uint_t   segment_owdew_howz_contiguous_chwoma;
	dmw_uint_t   segment_owdew_vewt_contiguous_wuma;
	dmw_uint_t   segment_owdew_vewt_contiguous_chwoma;

	typedef enum{
		WEQ_256Bytes,
		WEQ_128BytesNonContiguous,
		WEQ_128BytesContiguous,
		WEQ_NA
	} WequestType;

	WequestType   WequestWuma;
	WequestType   WequestChwoma;

	yuv420 = ((SouwcePixewFowmat == dmw_420_8 || SouwcePixewFowmat == dmw_420_10 || SouwcePixewFowmat == dmw_420_12) ? 1 : 0);
	howz_div_w = 1;
	howz_div_c = 1;
	vewt_div_w = 1;
	vewt_div_c = 1;

	if (BytePewPixewY == 1)
		vewt_div_w = 0;
	if (BytePewPixewC == 1)
		vewt_div_c = 0;

	if (BytePewPixewC == 0) {
		swath_buf_size = DETBuffewSizeFowDCC / 2 - 2 * 256;
		detiwe_buf_vp_howz_wimit = (dmw_fwoat_t) swath_buf_size / ((dmw_fwoat_t) WequestHeight256ByteWuma * BytePewPixewY / (1 + howz_div_w));
		detiwe_buf_vp_vewt_wimit = (dmw_fwoat_t) swath_buf_size / (256.0 / WequestHeight256ByteWuma / (1 + vewt_div_w));
	} ewse {
		swath_buf_size = DETBuffewSizeFowDCC / 2 - 2 * 2 * 256;
		detiwe_buf_vp_howz_wimit = (dmw_fwoat_t) swath_buf_size / ((dmw_fwoat_t) WequestHeight256ByteWuma * BytePewPixewY / (1 + howz_div_w) + (dmw_fwoat_t) WequestHeight256ByteChwoma * BytePewPixewC / (1 + howz_div_c) / (1 + yuv420));
		detiwe_buf_vp_vewt_wimit = (dmw_fwoat_t) swath_buf_size / (256.0 / WequestHeight256ByteWuma / (1 + vewt_div_w) + 256.0 / WequestHeight256ByteChwoma / (1 + vewt_div_c) / (1 + yuv420));
	}

	if (SouwcePixewFowmat == dmw_420_10) {
		detiwe_buf_vp_howz_wimit = 1.5 * detiwe_buf_vp_howz_wimit;
		detiwe_buf_vp_vewt_wimit = 1.5 * detiwe_buf_vp_vewt_wimit;
	}

	detiwe_buf_vp_howz_wimit = dmw_fwoow(detiwe_buf_vp_howz_wimit - 1, 16);
	detiwe_buf_vp_vewt_wimit = dmw_fwoow(detiwe_buf_vp_vewt_wimit - 1, 16);

	MAS_vp_howz_wimit = SouwcePixewFowmat == dmw_wgbe_awpha ? 3840 : 6144;
	MAS_vp_vewt_wimit = SouwcePixewFowmat == dmw_wgbe_awpha ? 3840 : (BytePewPixewY == 8 ? 3072 : 6144);
	max_vp_howz_width = (dmw_uint_t)(dmw_min((dmw_fwoat_t) MAS_vp_howz_wimit, detiwe_buf_vp_howz_wimit));
	max_vp_vewt_height = (dmw_uint_t)(dmw_min((dmw_fwoat_t) MAS_vp_vewt_wimit, detiwe_buf_vp_vewt_wimit));
	eff_suwf_width_w = (SuwfaceWidthWuma > max_vp_howz_width ? max_vp_howz_width : SuwfaceWidthWuma);
	eff_suwf_width_c = eff_suwf_width_w / (1 + yuv420);
	eff_suwf_height_w = (SuwfaceHeightWuma > max_vp_vewt_height ? max_vp_vewt_height : SuwfaceHeightWuma);
	eff_suwf_height_c = eff_suwf_height_w / (1 + yuv420);

	fuww_swath_bytes_howz_wc_w = eff_suwf_width_w * WequestHeight256ByteWuma * BytePewPixewY;
	fuww_swath_bytes_vewt_wc_w = eff_suwf_height_w * 256 / WequestHeight256ByteWuma;
	if (BytePewPixewC > 0) {
		fuww_swath_bytes_howz_wc_c = eff_suwf_width_c * WequestHeight256ByteChwoma * BytePewPixewC;
		fuww_swath_bytes_vewt_wc_c = eff_suwf_height_c * 256 / WequestHeight256ByteChwoma;
	} ewse {
		fuww_swath_bytes_howz_wc_c = 0;
		fuww_swath_bytes_vewt_wc_c = 0;
	}

	if (SouwcePixewFowmat == dmw_420_10) {
		fuww_swath_bytes_howz_wc_w = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) fuww_swath_bytes_howz_wc_w * 2.0 / 3.0, 256.0));
		fuww_swath_bytes_howz_wc_c = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) fuww_swath_bytes_howz_wc_c * 2.0 / 3.0, 256.0));
		fuww_swath_bytes_vewt_wc_w = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) fuww_swath_bytes_vewt_wc_w * 2.0 / 3.0, 256.0));
		fuww_swath_bytes_vewt_wc_c = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) fuww_swath_bytes_vewt_wc_c * 2.0 / 3.0, 256.0));
	}

	if (2 * fuww_swath_bytes_howz_wc_w + 2 * fuww_swath_bytes_howz_wc_c <= DETBuffewSizeFowDCC) {
		weq128_howz_wc_w = 0;
		weq128_howz_wc_c = 0;
	} ewse if (fuww_swath_bytes_howz_wc_w < 1.5 * fuww_swath_bytes_howz_wc_c && 2 * fuww_swath_bytes_howz_wc_w + fuww_swath_bytes_howz_wc_c <= DETBuffewSizeFowDCC) {
		weq128_howz_wc_w = 0;
		weq128_howz_wc_c = 1;
	} ewse if (fuww_swath_bytes_howz_wc_w >= 1.5 * fuww_swath_bytes_howz_wc_c && fuww_swath_bytes_howz_wc_w + 2 * fuww_swath_bytes_howz_wc_c <= DETBuffewSizeFowDCC) {
		weq128_howz_wc_w = 1;
		weq128_howz_wc_c = 0;
	} ewse {
		weq128_howz_wc_w = 1;
		weq128_howz_wc_c = 1;
	}

	if (2 * fuww_swath_bytes_vewt_wc_w + 2 * fuww_swath_bytes_vewt_wc_c <= DETBuffewSizeFowDCC) {
		weq128_vewt_wc_w = 0;
		weq128_vewt_wc_c = 0;
	} ewse if (fuww_swath_bytes_vewt_wc_w < 1.5 * fuww_swath_bytes_vewt_wc_c && 2 * fuww_swath_bytes_vewt_wc_w + fuww_swath_bytes_vewt_wc_c <= DETBuffewSizeFowDCC) {
		weq128_vewt_wc_w = 0;
		weq128_vewt_wc_c = 1;
	} ewse if (fuww_swath_bytes_vewt_wc_w >= 1.5 * fuww_swath_bytes_vewt_wc_c && fuww_swath_bytes_vewt_wc_w + 2 * fuww_swath_bytes_vewt_wc_c <= DETBuffewSizeFowDCC) {
		weq128_vewt_wc_w = 1;
		weq128_vewt_wc_c = 0;
	} ewse {
		weq128_vewt_wc_w = 1;
		weq128_vewt_wc_c = 1;
	}

	if (BytePewPixewY == 2) {
		segment_owdew_howz_contiguous_wuma = 0;
		segment_owdew_vewt_contiguous_wuma = 1;
	} ewse {
		segment_owdew_howz_contiguous_wuma = 1;
		segment_owdew_vewt_contiguous_wuma = 0;
	}

	if (BytePewPixewC == 2) {
		segment_owdew_howz_contiguous_chwoma = 0;
		segment_owdew_vewt_contiguous_chwoma = 1;
	} ewse {
		segment_owdew_howz_contiguous_chwoma = 1;
		segment_owdew_vewt_contiguous_chwoma = 0;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DCCEnabwed = %u\n", __func__, DCCEnabwed);
	dmw_pwint("DMW::%s: nomDETInKByte = %u\n", __func__, nomDETInKByte);
	dmw_pwint("DMW::%s: DETBuffewSizeFowDCC = %u\n", __func__, DETBuffewSizeFowDCC);
	dmw_pwint("DMW::%s: weq128_howz_wc_w = %u\n", __func__, weq128_howz_wc_w);
	dmw_pwint("DMW::%s: weq128_howz_wc_c = %u\n", __func__, weq128_howz_wc_c);
	dmw_pwint("DMW::%s: fuww_swath_bytes_howz_wc_w = %u\n", __func__, fuww_swath_bytes_howz_wc_w);
	dmw_pwint("DMW::%s: fuww_swath_bytes_vewt_wc_c = %u\n", __func__, fuww_swath_bytes_vewt_wc_c);
	dmw_pwint("DMW::%s: segment_owdew_howz_contiguous_wuma = %u\n", __func__, segment_owdew_howz_contiguous_wuma);
	dmw_pwint("DMW::%s: segment_owdew_howz_contiguous_chwoma = %u\n", __func__, segment_owdew_howz_contiguous_chwoma);
#endif

	if (DCCPwogwammingAssumesScanDiwectionUnknown == twue) {
		if (weq128_howz_wc_w == 0 && weq128_vewt_wc_w == 0) {
			WequestWuma = WEQ_256Bytes;
		} ewse if ((weq128_howz_wc_w == 1 && segment_owdew_howz_contiguous_wuma == 0) || (weq128_vewt_wc_w == 1 && segment_owdew_vewt_contiguous_wuma == 0)) {
			WequestWuma = WEQ_128BytesNonContiguous;
		} ewse {
			WequestWuma = WEQ_128BytesContiguous;
		}
		if (weq128_howz_wc_c == 0 && weq128_vewt_wc_c == 0) {
			WequestChwoma = WEQ_256Bytes;
		} ewse if ((weq128_howz_wc_c == 1 && segment_owdew_howz_contiguous_chwoma == 0) || (weq128_vewt_wc_c == 1 && segment_owdew_vewt_contiguous_chwoma == 0)) {
			WequestChwoma = WEQ_128BytesNonContiguous;
		} ewse {
			WequestChwoma = WEQ_128BytesContiguous;
		}
	} ewse if (!dmw_is_vewticaw_wotation(SouwceScan)) {
		if (weq128_howz_wc_w == 0) {
			WequestWuma = WEQ_256Bytes;
		} ewse if (segment_owdew_howz_contiguous_wuma == 0) {
			WequestWuma = WEQ_128BytesNonContiguous;
		} ewse {
			WequestWuma = WEQ_128BytesContiguous;
		}
		if (weq128_howz_wc_c == 0) {
			WequestChwoma = WEQ_256Bytes;
		} ewse if (segment_owdew_howz_contiguous_chwoma == 0) {
			WequestChwoma = WEQ_128BytesNonContiguous;
		} ewse {
			WequestChwoma = WEQ_128BytesContiguous;
		}
	} ewse {
		if (weq128_vewt_wc_w == 0) {
			WequestWuma = WEQ_256Bytes;
		} ewse if (segment_owdew_vewt_contiguous_wuma == 0) {
			WequestWuma = WEQ_128BytesNonContiguous;
		} ewse {
			WequestWuma = WEQ_128BytesContiguous;
		}
		if (weq128_vewt_wc_c == 0) {
			WequestChwoma = WEQ_256Bytes;
		} ewse if (segment_owdew_vewt_contiguous_chwoma == 0) {
			WequestChwoma = WEQ_128BytesNonContiguous;
		} ewse {
			WequestChwoma = WEQ_128BytesContiguous;
		}
	}

	if (WequestWuma == WEQ_256Bytes) {
		*MaxUncompwessedBwockWuma = 256;
		*MaxCompwessedBwockWuma = 256;
		*IndependentBwockWuma = 0;
	} ewse if (WequestWuma == WEQ_128BytesContiguous) {
		*MaxUncompwessedBwockWuma = 256;
		*MaxCompwessedBwockWuma = 128;
		*IndependentBwockWuma = 128;
	} ewse {
		*MaxUncompwessedBwockWuma = 256;
		*MaxCompwessedBwockWuma = 64;
		*IndependentBwockWuma = 64;
	}

	if (WequestChwoma == WEQ_256Bytes) {
		*MaxUncompwessedBwockChwoma = 256;
		*MaxCompwessedBwockChwoma = 256;
		*IndependentBwockChwoma = 0;
	} ewse if (WequestChwoma == WEQ_128BytesContiguous) {
		*MaxUncompwessedBwockChwoma = 256;
		*MaxCompwessedBwockChwoma = 128;
		*IndependentBwockChwoma = 128;
	} ewse {
		*MaxUncompwessedBwockChwoma = 256;
		*MaxCompwessedBwockChwoma = 64;
		*IndependentBwockChwoma = 64;
	}

	if (DCCEnabwed != twue || BytePewPixewC == 0) {
		*MaxUncompwessedBwockChwoma = 0;
		*MaxCompwessedBwockChwoma = 0;
		*IndependentBwockChwoma = 0;
	}

	if (DCCEnabwed != twue) {
		*MaxUncompwessedBwockWuma = 0;
		*MaxCompwessedBwockWuma = 0;
		*IndependentBwockWuma = 0;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: MaxUncompwessedBwockWuma = %u\n", __func__, *MaxUncompwessedBwockWuma);
	dmw_pwint("DMW::%s: MaxCompwessedBwockWuma = %u\n", __func__, *MaxCompwessedBwockWuma);
	dmw_pwint("DMW::%s: IndependentBwockWuma = %u\n", __func__, *IndependentBwockWuma);
	dmw_pwint("DMW::%s: MaxUncompwessedBwockChwoma = %u\n", __func__, *MaxUncompwessedBwockChwoma);
	dmw_pwint("DMW::%s: MaxCompwessedBwockChwoma = %u\n", __func__, *MaxCompwessedBwockChwoma);
	dmw_pwint("DMW::%s: IndependentBwockChwoma = %u\n", __func__, *IndependentBwockChwoma);
#endif

} // CawcuwateDCCConfiguwation

static dmw_uint_t CawcuwatePwefetchSouwceWines(
		dmw_fwoat_t VWatio,
		dmw_uint_t VTaps,
		dmw_boow_t Intewwace,
		dmw_boow_t PwogwessiveToIntewwaceUnitInOPP,
		dmw_uint_t SwathHeight,
		enum dmw_wotation_angwe SouwceScan,
		dmw_boow_t ViewpowtStationawy,
		dmw_uint_t SwathWidth,
		dmw_uint_t ViewpowtHeight,
		dmw_uint_t ViewpowtXStawt,
		dmw_uint_t ViewpowtYStawt,

		// Output
		dmw_uint_t *VInitPweFiww,
		dmw_uint_t *MaxNumSwath)
{

	dmw_uint_t vp_stawt_wot = 0;
	dmw_uint_t sw0_tmp = 0;
	dmw_uint_t MaxPawtiawSwath = 0;
	dmw_fwoat_t numWines = 0;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VWatio = %f\n", __func__, VWatio);
	dmw_pwint("DMW::%s: VTaps = %u\n", __func__, VTaps);
	dmw_pwint("DMW::%s: ViewpowtXStawt = %u\n", __func__, ViewpowtXStawt);
	dmw_pwint("DMW::%s: ViewpowtYStawt = %u\n", __func__, ViewpowtYStawt);
	dmw_pwint("DMW::%s: ViewpowtStationawy = %u\n", __func__, ViewpowtStationawy);
	dmw_pwint("DMW::%s: SwathHeight = %u\n", __func__, SwathHeight);
#endif
	if (PwogwessiveToIntewwaceUnitInOPP)
		*VInitPweFiww = (dmw_uint_t)(dmw_fwoow((VWatio + (dmw_fwoat_t) VTaps + 1) / 2.0, 1));
	ewse
		*VInitPweFiww = (dmw_uint_t)(dmw_fwoow((VWatio + (dmw_fwoat_t) VTaps + 1 + Intewwace * 0.5 * VWatio) / 2.0, 1));

	if (ViewpowtStationawy) {
		if (SouwceScan == dmw_wotation_180 || SouwceScan == dmw_wotation_180m) {
			vp_stawt_wot = SwathHeight - (((dmw_uint_t) (ViewpowtYStawt + ViewpowtHeight - 1) % SwathHeight) + 1);
		} ewse if (SouwceScan == dmw_wotation_270 || SouwceScan == dmw_wotation_90m) {
			vp_stawt_wot = ViewpowtXStawt;
		} ewse if (SouwceScan == dmw_wotation_90 || SouwceScan == dmw_wotation_270m) {
			vp_stawt_wot = SwathHeight - (((dmw_uint_t)(ViewpowtYStawt + SwathWidth - 1) % SwathHeight) + 1);
		} ewse {
			vp_stawt_wot = ViewpowtYStawt;
		}
		sw0_tmp = SwathHeight - (vp_stawt_wot % SwathHeight);
		if (sw0_tmp < *VInitPweFiww) {
			*MaxNumSwath = (dmw_uint_t)(dmw_ceiw((*VInitPweFiww - sw0_tmp) / (dmw_fwoat_t) SwathHeight, 1) + 1);
		} ewse {
			*MaxNumSwath = 1;
		}
		MaxPawtiawSwath = (dmw_uint_t)(dmw_max(1, (dmw_uint_t) (vp_stawt_wot + *VInitPweFiww - 1) % SwathHeight));
	} ewse {
		*MaxNumSwath = (dmw_uint_t)(dmw_ceiw((*VInitPweFiww - 1.0) / (dmw_fwoat_t) SwathHeight, 1) + 1);
		if (*VInitPweFiww > 1) {
			MaxPawtiawSwath = (dmw_uint_t)(dmw_max(1, (dmw_uint_t) (*VInitPweFiww - 2) % SwathHeight));
		} ewse {
			MaxPawtiawSwath = (dmw_uint_t)(dmw_max(1, (dmw_uint_t) (*VInitPweFiww + SwathHeight - 2) % SwathHeight));
		}
	}
	numWines = *MaxNumSwath * SwathHeight + MaxPawtiawSwath;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: vp_stawt_wot = %u\n", __func__, vp_stawt_wot);
	dmw_pwint("DMW::%s: VInitPweFiww = %u\n", __func__, *VInitPweFiww);
	dmw_pwint("DMW::%s: MaxPawtiawSwath = %u\n", __func__, MaxPawtiawSwath);
	dmw_pwint("DMW::%s: MaxNumSwath = %u\n", __func__, *MaxNumSwath);
	dmw_pwint("DMW::%s: Pwefetch souwce wines = %3.2f\n", __func__, numWines);
#endif
	wetuwn (dmw_uint_t)(numWines);

} // CawcuwatePwefetchSouwceWines

static dmw_uint_t CawcuwateVMAndWowBytes(
		dmw_boow_t ViewpowtStationawy,
		dmw_boow_t DCCEnabwe,
		dmw_uint_t NumbewOfDPPs,
		dmw_uint_t BwockHeight256Bytes,
		dmw_uint_t BwockWidth256Bytes,
		enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
		dmw_uint_t SuwfaceTiwing,
		dmw_uint_t BytePewPixew,
		enum dmw_wotation_angwe SouwceScan,
		dmw_uint_t SwathWidth,
		dmw_uint_t ViewpowtHeight,
		dmw_uint_t ViewpowtXStawt,
		dmw_uint_t ViewpowtYStawt,
		dmw_boow_t GPUVMEnabwe,
		dmw_uint_t GPUVMMaxPageTabweWevews,
		dmw_uint_t GPUVMMinPageSizeKBytes,
		dmw_uint_t PTEBuffewSizeInWequests,
		dmw_uint_t Pitch,
		dmw_uint_t DCCMetaPitch,
		dmw_uint_t MacwoTiweWidth,
		dmw_uint_t MacwoTiweHeight,

		// Output
		dmw_uint_t *MetaWowByte,
		dmw_uint_t *PixewPTEBytesPewWow, // fow bandwidth cawcuwation
		dmw_uint_t *PixewPTEBytesPewWowStowage, // fow PTE buffew size check
		dmw_uint_t *dpte_wow_width_ub,
		dmw_uint_t *dpte_wow_height,
		dmw_uint_t *dpte_wow_height_wineaw,
		dmw_uint_t *PixewPTEBytesPewWow_one_wow_pew_fwame,
		dmw_uint_t *dpte_wow_width_ub_one_wow_pew_fwame,
		dmw_uint_t *dpte_wow_height_one_wow_pew_fwame,
		dmw_uint_t *MetaWequestWidth,
		dmw_uint_t *MetaWequestHeight,
		dmw_uint_t *meta_wow_width,
		dmw_uint_t *meta_wow_height,
		dmw_uint_t *PixewPTEWeqWidth,
		dmw_uint_t *PixewPTEWeqHeight,
		dmw_uint_t *PTEWequestSize,
		dmw_uint_t *DPDE0BytesFwame,
		dmw_uint_t *MetaPTEBytesFwame)
{
	dmw_uint_t MPDEBytesFwame;
	dmw_uint_t DCCMetaSuwfaceBytes;
	dmw_uint_t ExtwaDPDEBytesFwame;
	dmw_uint_t PDEAndMetaPTEBytesFwame;
	dmw_uint_t MacwoTiweSizeBytes;
	dmw_uint_t vp_height_meta_ub;
	dmw_uint_t vp_height_dpte_ub;

	dmw_uint_t PixewPTEWeqWidth_wineaw = 0; // VBA_DEWTA. VBA doesn't cawcuwate this

	*MetaWequestHeight = 8 * BwockHeight256Bytes;
	*MetaWequestWidth = 8 * BwockWidth256Bytes;
	if (SuwfaceTiwing == dmw_sw_wineaw) {
		*meta_wow_height = 32;
		*meta_wow_width = (dmw_uint_t)(dmw_fwoow(ViewpowtXStawt + SwathWidth + *MetaWequestWidth - 1, *MetaWequestWidth) - dmw_fwoow(ViewpowtXStawt, *MetaWequestWidth));
	} ewse if (!dmw_is_vewticaw_wotation(SouwceScan)) {
		*meta_wow_height = *MetaWequestHeight;
		if (ViewpowtStationawy && NumbewOfDPPs == 1) {
			*meta_wow_width = (dmw_uint_t)(dmw_fwoow(ViewpowtXStawt + SwathWidth + *MetaWequestWidth - 1, *MetaWequestWidth) - dmw_fwoow(ViewpowtXStawt, *MetaWequestWidth));
		} ewse {
			*meta_wow_width = (dmw_uint_t)(dmw_ceiw(SwathWidth - 1, *MetaWequestWidth) + *MetaWequestWidth);
		}
		*MetaWowByte = (dmw_uint_t)(*meta_wow_width * *MetaWequestHeight * BytePewPixew / 256.0);
	} ewse {
		*meta_wow_height = *MetaWequestWidth;
		if (ViewpowtStationawy && NumbewOfDPPs == 1) {
			*meta_wow_width = (dmw_uint_t)(dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + *MetaWequestHeight - 1, *MetaWequestHeight) - dmw_fwoow(ViewpowtYStawt, *MetaWequestHeight));
		} ewse {
			*meta_wow_width = (dmw_uint_t)(dmw_ceiw(SwathWidth - 1, *MetaWequestHeight) + *MetaWequestHeight);
		}
		*MetaWowByte = (dmw_uint_t)(*meta_wow_width * *MetaWequestWidth * BytePewPixew / 256.0);
	}

	if (ViewpowtStationawy && (NumbewOfDPPs == 1 || !dmw_is_vewticaw_wotation(SouwceScan))) {
		vp_height_meta_ub = (dmw_uint_t)(dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + 64 * BwockHeight256Bytes - 1, 64 * BwockHeight256Bytes) - dmw_fwoow(ViewpowtYStawt, 64 * BwockHeight256Bytes));
	} ewse if (!dmw_is_vewticaw_wotation(SouwceScan)) {
		vp_height_meta_ub = (dmw_uint_t)(dmw_ceiw(ViewpowtHeight - 1, 64 * BwockHeight256Bytes) + 64 * BwockHeight256Bytes);
	} ewse {
		vp_height_meta_ub = (dmw_uint_t)(dmw_ceiw(SwathWidth - 1, 64 * BwockHeight256Bytes) + 64 * BwockHeight256Bytes);
	}

	DCCMetaSuwfaceBytes = (dmw_uint_t)(DCCMetaPitch * vp_height_meta_ub * BytePewPixew / 256.0);

	if (GPUVMEnabwe == twue) {
		*MetaPTEBytesFwame = (dmw_uint_t)((dmw_ceiw((dmw_fwoat_t) (DCCMetaSuwfaceBytes - 4.0 * 1024.0) / (8 * 4.0 * 1024), 1) + 1) * 64);
		MPDEBytesFwame = 128 * (GPUVMMaxPageTabweWevews - 1);
	} ewse {
		*MetaPTEBytesFwame = 0;
		MPDEBytesFwame = 0;
	}

	if (DCCEnabwe != twue) {
		*MetaPTEBytesFwame = 0;
		MPDEBytesFwame = 0;
		*MetaWowByte = 0;
	}

	MacwoTiweSizeBytes = MacwoTiweWidth * BytePewPixew * MacwoTiweHeight;

	if (ViewpowtStationawy && (NumbewOfDPPs == 1 || !dmw_is_vewticaw_wotation(SouwceScan))) {
		vp_height_dpte_ub = (dmw_uint_t)(dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + MacwoTiweHeight - 1, MacwoTiweHeight) - dmw_fwoow(ViewpowtYStawt, MacwoTiweHeight));
	} ewse if (!dmw_is_vewticaw_wotation(SouwceScan)) {
		vp_height_dpte_ub = (dmw_uint_t)(dmw_ceiw(ViewpowtHeight - 1, MacwoTiweHeight) + MacwoTiweHeight);
	} ewse {
		vp_height_dpte_ub = (dmw_uint_t)(dmw_ceiw(SwathWidth - 1, MacwoTiweHeight) + MacwoTiweHeight);
	}

	if (GPUVMEnabwe == twue && GPUVMMaxPageTabweWevews > 1) {
		*DPDE0BytesFwame = (dmw_uint_t)(64 * (dmw_ceiw((dmw_fwoat_t) (Pitch * vp_height_dpte_ub * BytePewPixew - MacwoTiweSizeBytes) / (dmw_fwoat_t) (8 * 2097152), 1) + 1));
		ExtwaDPDEBytesFwame = 128 * (GPUVMMaxPageTabweWevews - 2);
	} ewse {
		*DPDE0BytesFwame = 0;
		ExtwaDPDEBytesFwame = 0;
	}

	PDEAndMetaPTEBytesFwame = *MetaPTEBytesFwame + MPDEBytesFwame + *DPDE0BytesFwame + ExtwaDPDEBytesFwame;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DCCEnabwe = %u\n", __func__, DCCEnabwe);
	dmw_pwint("DMW::%s: GPUVMEnabwe = %u\n", __func__, GPUVMEnabwe);
	dmw_pwint("DMW::%s: SwModeWineaw = %u\n", __func__, SuwfaceTiwing == dmw_sw_wineaw);
	dmw_pwint("DMW::%s: BytePewPixew = %u\n", __func__, BytePewPixew);
	dmw_pwint("DMW::%s: GPUVMMaxPageTabweWevews = %u\n", __func__, GPUVMMaxPageTabweWevews);
	dmw_pwint("DMW::%s: BwockHeight256Bytes = %u\n", __func__, BwockHeight256Bytes);
	dmw_pwint("DMW::%s: BwockWidth256Bytes = %u\n", __func__, BwockWidth256Bytes);
	dmw_pwint("DMW::%s: MacwoTiweHeight = %u\n", __func__, MacwoTiweHeight);
	dmw_pwint("DMW::%s: MacwoTiweWidth = %u\n", __func__, MacwoTiweWidth);
	dmw_pwint("DMW::%s: MetaPTEBytesFwame = %u\n", __func__, *MetaPTEBytesFwame);
	dmw_pwint("DMW::%s: MPDEBytesFwame = %u\n", __func__, MPDEBytesFwame);
	dmw_pwint("DMW::%s: DPDE0BytesFwame = %u\n", __func__, *DPDE0BytesFwame);
	dmw_pwint("DMW::%s: ExtwaDPDEBytesFwame= %u\n", __func__, ExtwaDPDEBytesFwame);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %u\n", __func__, PDEAndMetaPTEBytesFwame);
	dmw_pwint("DMW::%s: ViewpowtHeight = %u\n", __func__, ViewpowtHeight);
	dmw_pwint("DMW::%s: SwathWidth = %u\n", __func__, SwathWidth);
	dmw_pwint("DMW::%s: vp_height_dpte_ub = %u\n", __func__, vp_height_dpte_ub);
#endif

	if (SuwfaceTiwing == dmw_sw_wineaw) {
		*PixewPTEWeqHeight = 1;
		*PixewPTEWeqWidth = GPUVMMinPageSizeKBytes * 1024 * 8 / BytePewPixew;
		PixewPTEWeqWidth_wineaw = GPUVMMinPageSizeKBytes * 1024 * 8 / BytePewPixew;
		*PTEWequestSize = 64;
	} ewse if (GPUVMMinPageSizeKBytes == 4) {
		*PixewPTEWeqHeight = 16 * BwockHeight256Bytes;
		*PixewPTEWeqWidth = 16 * BwockWidth256Bytes;
		*PTEWequestSize = 128;
	} ewse {
		*PixewPTEWeqHeight = MacwoTiweHeight;
		*PixewPTEWeqWidth = 8 *  1024 * GPUVMMinPageSizeKBytes / (MacwoTiweHeight * BytePewPixew);
		*PTEWequestSize = 64;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: GPUVMMinPageSizeKBytes = %u\n", __func__, GPUVMMinPageSizeKBytes);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %u (aftew HostVM factow)\n", __func__, PDEAndMetaPTEBytesFwame);
	dmw_pwint("DMW::%s: PixewPTEWeqHeight = %u\n", __func__, *PixewPTEWeqHeight);
	dmw_pwint("DMW::%s: PixewPTEWeqWidth = %u\n", __func__, *PixewPTEWeqWidth);
	dmw_pwint("DMW::%s: PixewPTEWeqWidth_wineaw = %u\n", __func__, PixewPTEWeqWidth_wineaw);
	dmw_pwint("DMW::%s: PTEWequestSize = %u\n", __func__, *PTEWequestSize);
	dmw_pwint("DMW::%s: Pitch = %u\n", __func__, Pitch);
#endif

	*dpte_wow_height_one_wow_pew_fwame = vp_height_dpte_ub;
	*dpte_wow_width_ub_one_wow_pew_fwame = (dmw_uint_t)((dmw_ceiw(((dmw_fwoat_t)Pitch * (dmw_fwoat_t) *dpte_wow_height_one_wow_pew_fwame / (dmw_fwoat_t) *PixewPTEWeqHeight - 1) / (dmw_fwoat_t) *PixewPTEWeqWidth, 1) + 1) * (dmw_fwoat_t) *PixewPTEWeqWidth);
	*PixewPTEBytesPewWow_one_wow_pew_fwame = (dmw_uint_t)((dmw_fwoat_t) *dpte_wow_width_ub_one_wow_pew_fwame / (dmw_fwoat_t) *PixewPTEWeqWidth * *PTEWequestSize);

	if (SuwfaceTiwing == dmw_sw_wineaw) {
		*dpte_wow_height = (dmw_uint_t)(dmw_min(128, 1 << (dmw_uint_t) dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch), 1)));
		dmw_pwint("DMW::%s: dpte_wow_height tewm 1 = %u\n", __func__, PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch);
		dmw_pwint("DMW::%s: dpte_wow_height tewm 2 = %f\n", __func__, dmw_wog2(PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch));
		dmw_pwint("DMW::%s: dpte_wow_height tewm 3 = %f\n", __func__, dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch), 1));
		dmw_pwint("DMW::%s: dpte_wow_height tewm 4 = %u\n", __func__, 1 << (dmw_uint_t) dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch), 1));
		dmw_pwint("DMW::%s: dpte_wow_height = %u\n", __func__, *dpte_wow_height);

		*dpte_wow_width_ub = (dmw_uint_t)(dmw_ceiw(((dmw_fwoat_t) Pitch * (dmw_fwoat_t) *dpte_wow_height - 1), (dmw_fwoat_t) *PixewPTEWeqWidth) + *PixewPTEWeqWidth);
		*PixewPTEBytesPewWow = (dmw_uint_t)((dmw_fwoat_t) *dpte_wow_width_ub / (dmw_fwoat_t) *PixewPTEWeqWidth * *PTEWequestSize);

		// VBA_DEWTA, VBA doesn't have pwogwamming vawue fow pte wow height wineaw.
		*dpte_wow_height_wineaw = 1 << (dmw_uint_t) dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests * PixewPTEWeqWidth_wineaw / Pitch), 1);
		if (*dpte_wow_height_wineaw > 128)
			*dpte_wow_height_wineaw = 128;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: dpte_wow_width_ub = %u (wineaw)\n", __func__, *dpte_wow_width_ub);
#endif

	} ewse if (!dmw_is_vewticaw_wotation(SouwceScan)) {
		*dpte_wow_height = *PixewPTEWeqHeight;

		if (GPUVMMinPageSizeKBytes > 64) {
			*dpte_wow_width_ub = (dmw_uint_t)((dmw_ceiw(((dmw_fwoat_t) Pitch * (dmw_fwoat_t) *dpte_wow_height / (dmw_fwoat_t) *PixewPTEWeqHeight - 1) / (dmw_fwoat_t) *PixewPTEWeqWidth, 1) + 1) * *PixewPTEWeqWidth);
		} ewse if (ViewpowtStationawy && (NumbewOfDPPs == 1)) {
			*dpte_wow_width_ub = (dmw_uint_t)(dmw_fwoow(ViewpowtXStawt + SwathWidth + *PixewPTEWeqWidth - 1, *PixewPTEWeqWidth) - dmw_fwoow(ViewpowtXStawt, *PixewPTEWeqWidth));
		} ewse {
			*dpte_wow_width_ub = (dmw_uint_t)((dmw_ceiw((dmw_fwoat_t) (SwathWidth - 1) / (dmw_fwoat_t)*PixewPTEWeqWidth, 1) + 1.0) * *PixewPTEWeqWidth);
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: dpte_wow_width_ub = %u (tiwed howz)\n", __func__, *dpte_wow_width_ub);
#endif

		ASSEWT(*PixewPTEWeqWidth);
		if (*PixewPTEWeqWidth != 0)
			*PixewPTEBytesPewWow = *dpte_wow_width_ub / *PixewPTEWeqWidth * *PTEWequestSize;
	} ewse {
		*dpte_wow_height = (dmw_uint_t)(dmw_min(*PixewPTEWeqWidth, MacwoTiweWidth));

		if (ViewpowtStationawy && (NumbewOfDPPs == 1)) {
			*dpte_wow_width_ub = (dmw_uint_t)(dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + *PixewPTEWeqHeight - 1, *PixewPTEWeqHeight) - dmw_fwoow(ViewpowtYStawt, *PixewPTEWeqHeight));
		} ewse {
			*dpte_wow_width_ub = (dmw_uint_t)((dmw_ceiw((dmw_fwoat_t) (SwathWidth - 1) / (dmw_fwoat_t) *PixewPTEWeqHeight, 1) + 1) * *PixewPTEWeqHeight);
		}

		*PixewPTEBytesPewWow = (dmw_uint_t)((dmw_fwoat_t) *dpte_wow_width_ub / (dmw_fwoat_t) *PixewPTEWeqHeight * *PTEWequestSize);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: dpte_wow_width_ub = %u (tiwed vewt)\n", __func__, *dpte_wow_width_ub);
#endif
	}

	if (GPUVMEnabwe != twue)
		*PixewPTEBytesPewWow = 0;

	*PixewPTEBytesPewWowStowage = *PixewPTEBytesPewWow;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: GPUVMMinPageSizeKBytes = %u\n", __func__, GPUVMMinPageSizeKBytes);
	dmw_pwint("DMW::%s: GPUVMEnabwe = %u\n", __func__, GPUVMEnabwe);
	dmw_pwint("DMW::%s: dpte_wow_height = %u\n", __func__, *dpte_wow_height);
	dmw_pwint("DMW::%s: dpte_wow_height_wineaw = %u\n", __func__, *dpte_wow_height_wineaw);
	dmw_pwint("DMW::%s: dpte_wow_width_ub = %u\n", __func__, *dpte_wow_width_ub);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %u\n", __func__, *PixewPTEBytesPewWow);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWowStowage = %u\n", __func__, *PixewPTEBytesPewWowStowage);
	dmw_pwint("DMW::%s: PTEBuffewSizeInWequests = %u\n", __func__, PTEBuffewSizeInWequests);
	dmw_pwint("DMW::%s: dpte_wow_height_one_wow_pew_fwame = %u\n", __func__, *dpte_wow_height_one_wow_pew_fwame);
	dmw_pwint("DMW::%s: dpte_wow_width_ub_one_wow_pew_fwame = %u\n", __func__, *dpte_wow_width_ub_one_wow_pew_fwame);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWow_one_wow_pew_fwame = %u\n", __func__, *PixewPTEBytesPewWow_one_wow_pew_fwame);
#endif

	dmw_pwint("DMW: vm_bytes = meta_pte_bytes_pew_fwame (pew_pipe) = MetaPTEBytesFwame = : %i\n", *MetaPTEBytesFwame);

	wetuwn PDEAndMetaPTEBytesFwame;
} // CawcuwateVMAndWowBytes

static void PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(stwuct dmw_dispway_cfg_st *dispway_cfg, dmw_boow_t ptoi_suppowted)
{
	dmw_uint_t num_active_pwanes = dmw_get_num_active_pwanes(dispway_cfg);

	//Pwogwessive To Intewwace Unit Effect
	fow (dmw_uint_t k = 0; k < num_active_pwanes; ++k) {
		dispway_cfg->output.PixewCwockBackEnd[k] = dispway_cfg->timing.PixewCwock[k];
		if (dispway_cfg->timing.Intewwace[k] == 1 && ptoi_suppowted == twue) {
			dispway_cfg->timing.PixewCwock[k] = 2 * dispway_cfg->timing.PixewCwock[k];
		}
	}
}

static dmw_fwoat_t TwuncToVawidBPP(
		dmw_fwoat_t WinkBitWate,
		dmw_uint_t Wanes,
		dmw_uint_t HTotaw,
		dmw_uint_t HActive,
		dmw_fwoat_t PixewCwock,
		dmw_fwoat_t DesiwedBPP,
		dmw_boow_t DSCEnabwe,
		enum dmw_output_encodew_cwass Output,
		enum dmw_output_fowmat_cwass Fowmat,
		dmw_uint_t DSCInputBitPewComponent,
		dmw_uint_t DSCSwices,
		dmw_uint_t AudioWate,
		dmw_uint_t AudioWayout,
		enum dmw_odm_mode ODMModeNoDSC,
		enum dmw_odm_mode ODMModeDSC,

		// Output
		dmw_uint_t *WequiwedSwots)
{
	dmw_fwoat_t MaxWinkBPP;
	dmw_uint_t MinDSCBPP;
	dmw_fwoat_t MaxDSCBPP;
	dmw_uint_t NonDSCBPP0;
	dmw_uint_t NonDSCBPP1;
	dmw_uint_t NonDSCBPP2;

	if (Fowmat == dmw_420) {
		NonDSCBPP0 = 12;
		NonDSCBPP1 = 15;
		NonDSCBPP2 = 18;
		MinDSCBPP = 6;
		MaxDSCBPP = 1.5 * DSCInputBitPewComponent - 1 / 16;
	} ewse if (Fowmat == dmw_444) {
		NonDSCBPP0 = 24;
		NonDSCBPP1 = 30;
		NonDSCBPP2 = 36;
		MinDSCBPP = 8;
		MaxDSCBPP = 3 * DSCInputBitPewComponent - 1.0 / 16;
	} ewse {
		if (Output == dmw_hdmi) {
			NonDSCBPP0 = 24;
			NonDSCBPP1 = 24;
			NonDSCBPP2 = 24;
		} ewse {
			NonDSCBPP0 = 16;
			NonDSCBPP1 = 20;
			NonDSCBPP2 = 24;
	}
	if (Fowmat == dmw_n422) {
		MinDSCBPP = 7;
			MaxDSCBPP = 2 * DSCInputBitPewComponent - 1.0 / 16.0;
		} ewse {
			MinDSCBPP = 8;
			MaxDSCBPP = 3 * DSCInputBitPewComponent - 1.0 / 16.0;
		}
	}

	if (Output == dmw_dp2p0) {
		MaxWinkBPP = WinkBitWate * Wanes / PixewCwock * 128.0 / 132.0 * 383.0 / 384.0 * 65536.0 / 65540.0;
	} ewse if (DSCEnabwe && Output == dmw_dp) {
		MaxWinkBPP = WinkBitWate / 10.0 * 8.0 * Wanes / PixewCwock * (1 - 2.4 / 100);
	} ewse {
		MaxWinkBPP = WinkBitWate / 10.0 * 8.0 * Wanes / PixewCwock;
	}

	if (DSCEnabwe) {
		if (ODMModeDSC == dmw_odm_mode_combine_4to1) {
			MaxWinkBPP = dmw_min(MaxWinkBPP, 16);
		} ewse if (ODMModeDSC == dmw_odm_mode_combine_2to1) {
			MaxWinkBPP = dmw_min(MaxWinkBPP, 32);
		} ewse if (ODMModeDSC == dmw_odm_mode_spwit_1to2) {
			MaxWinkBPP = 2 * MaxWinkBPP;
		}
	} ewse {
		if (ODMModeNoDSC == dmw_odm_mode_combine_4to1) {
			MaxWinkBPP = dmw_min(MaxWinkBPP, 16);
		} ewse if (ODMModeNoDSC == dmw_odm_mode_combine_2to1) {
			MaxWinkBPP = dmw_min(MaxWinkBPP, 32);
		} ewse if (ODMModeNoDSC == dmw_odm_mode_spwit_1to2) {
			MaxWinkBPP = 2 * MaxWinkBPP;
		}
	}

	if (DesiwedBPP == 0) {
		if (DSCEnabwe) {
			if (MaxWinkBPP < MinDSCBPP) {
				wetuwn __DMW_DPP_INVAWID__;
			} ewse if (MaxWinkBPP >= MaxDSCBPP) {
				wetuwn MaxDSCBPP;
			} ewse {
				wetuwn dmw_fwoow(16.0 * MaxWinkBPP, 1.0) / 16.0;
			}
		} ewse {
			if (MaxWinkBPP >= NonDSCBPP2) {
				wetuwn NonDSCBPP2;
			} ewse if (MaxWinkBPP >= NonDSCBPP1) {
				wetuwn NonDSCBPP1;
			} ewse if (MaxWinkBPP >= NonDSCBPP0) {
				wetuwn NonDSCBPP0;
			} ewse {
				wetuwn __DMW_DPP_INVAWID__;
			}
		}
	} ewse {
		if (!((DSCEnabwe == fawse && (DesiwedBPP == NonDSCBPP2 || DesiwedBPP == NonDSCBPP1 || DesiwedBPP == NonDSCBPP0)) ||
				(DSCEnabwe && DesiwedBPP >= MinDSCBPP && DesiwedBPP <= MaxDSCBPP))) {
			wetuwn __DMW_DPP_INVAWID__;
		} ewse {
			wetuwn DesiwedBPP;
		}
	}

	*WequiwedSwots = (dmw_uint_t)(dmw_ceiw(DesiwedBPP / MaxWinkBPP * 64, 1));

	wetuwn __DMW_DPP_INVAWID__;
} // TwuncToVawidBPP

static void CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt(
		stwuct dispway_mode_wib_scwatch_st *scwatch,
		stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams_st *p)
{
	stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_wocaws_st *s = &scwatch->CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_wocaws;

	s->TotawActiveWwiteback = 0;
	p->Watewmawk->UwgentWatewmawk = p->mmSOCPawametews.UwgentWatency + p->mmSOCPawametews.ExtwaWatency;
	p->Watewmawk->USWWetwainingWatewmawk = p->mmSOCPawametews.UwgentWatency + p->mmSOCPawametews.ExtwaWatency + p->mmSOCPawametews.USWWetwainingWatency + p->mmSOCPawametews.SMNWatency;
	p->Watewmawk->DWAMCwockChangeWatewmawk = p->mmSOCPawametews.DWAMCwockChangeWatency + p->Watewmawk->UwgentWatewmawk;
	p->Watewmawk->FCWKChangeWatewmawk = p->mmSOCPawametews.FCWKChangeWatency + p->Watewmawk->UwgentWatewmawk;
	p->Watewmawk->StuttewExitWatewmawk = p->mmSOCPawametews.SWExitTime + p->mmSOCPawametews.ExtwaWatency + 10 / p->DCFCwkDeepSweep;
	p->Watewmawk->StuttewEntewPwusExitWatewmawk = p->mmSOCPawametews.SWEntewPwusExitTime + p->mmSOCPawametews.ExtwaWatency + 10 / p->DCFCwkDeepSweep;
	p->Watewmawk->Z8StuttewExitWatewmawk = p->mmSOCPawametews.SWExitZ8Time + p->mmSOCPawametews.ExtwaWatency + 10 / p->DCFCwkDeepSweep;
	p->Watewmawk->Z8StuttewEntewPwusExitWatewmawk = p->mmSOCPawametews.SWEntewPwusExitZ8Time + p->mmSOCPawametews.ExtwaWatency + 10 / p->DCFCwkDeepSweep;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: UwgentWatency = %f\n", __func__, p->mmSOCPawametews.UwgentWatency);
	dmw_pwint("DMW::%s: ExtwaWatency = %f\n", __func__, p->mmSOCPawametews.ExtwaWatency);
	dmw_pwint("DMW::%s: DWAMCwockChangeWatency = %f\n", __func__, p->mmSOCPawametews.DWAMCwockChangeWatency);
	dmw_pwint("DMW::%s: UwgentWatewmawk = %f\n", __func__, p->Watewmawk->UwgentWatewmawk);
	dmw_pwint("DMW::%s: USWWetwainingWatewmawk = %f\n", __func__, p->Watewmawk->USWWetwainingWatewmawk);
	dmw_pwint("DMW::%s: DWAMCwockChangeWatewmawk = %f\n", __func__, p->Watewmawk->DWAMCwockChangeWatewmawk);
	dmw_pwint("DMW::%s: FCWKChangeWatewmawk = %f\n", __func__, p->Watewmawk->FCWKChangeWatewmawk);
	dmw_pwint("DMW::%s: StuttewExitWatewmawk = %f\n", __func__, p->Watewmawk->StuttewExitWatewmawk);
	dmw_pwint("DMW::%s: StuttewEntewPwusExitWatewmawk = %f\n", __func__, p->Watewmawk->StuttewEntewPwusExitWatewmawk);
	dmw_pwint("DMW::%s: Z8StuttewExitWatewmawk = %f\n", __func__, p->Watewmawk->Z8StuttewExitWatewmawk);
	dmw_pwint("DMW::%s: Z8StuttewEntewPwusExitWatewmawk = %f\n", __func__, p->Watewmawk->Z8StuttewEntewPwusExitWatewmawk);
#endif

	s->TotawActiveWwiteback = 0;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (p->WwitebackEnabwe[k] == twue) {
			s->TotawActiveWwiteback = s->TotawActiveWwiteback + 1;
		}
	}

	if (s->TotawActiveWwiteback <= 1) {
		p->Watewmawk->WwitebackUwgentWatewmawk = p->mmSOCPawametews.WwitebackWatency;
	} ewse {
		p->Watewmawk->WwitebackUwgentWatewmawk = p->mmSOCPawametews.WwitebackWatency + p->WwitebackChunkSize * 1024.0 / 32.0 / p->SOCCWK;
	}
	if (p->USWWetwainingWequiwedFinaw)
		p->Watewmawk->WwitebackUwgentWatewmawk = p->Watewmawk->WwitebackUwgentWatewmawk + p->mmSOCPawametews.USWWetwainingWatency;

	if (s->TotawActiveWwiteback <= 1) {
		p->Watewmawk->WwitebackDWAMCwockChangeWatewmawk = p->mmSOCPawametews.DWAMCwockChangeWatency + p->mmSOCPawametews.WwitebackWatency;
		p->Watewmawk->WwitebackFCWKChangeWatewmawk = p->mmSOCPawametews.FCWKChangeWatency + p->mmSOCPawametews.WwitebackWatency;
	} ewse {
		p->Watewmawk->WwitebackDWAMCwockChangeWatewmawk = p->mmSOCPawametews.DWAMCwockChangeWatency + p->mmSOCPawametews.WwitebackWatency + p->WwitebackChunkSize * 1024.0 / 32.0 / p->SOCCWK;
		p->Watewmawk->WwitebackFCWKChangeWatewmawk = p->mmSOCPawametews.FCWKChangeWatency + p->mmSOCPawametews.WwitebackWatency + p->WwitebackChunkSize * 1024 / 32 / p->SOCCWK;
	}

	if (p->USWWetwainingWequiwedFinaw)
		p->Watewmawk->WwitebackDWAMCwockChangeWatewmawk = p->Watewmawk->WwitebackDWAMCwockChangeWatewmawk + p->mmSOCPawametews.USWWetwainingWatency;

	if (p->USWWetwainingWequiwedFinaw)
		p->Watewmawk->WwitebackFCWKChangeWatewmawk = p->Watewmawk->WwitebackFCWKChangeWatewmawk + p->mmSOCPawametews.USWWetwainingWatency;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WwitebackDWAMCwockChangeWatewmawk = %f\n", __func__, p->Watewmawk->WwitebackDWAMCwockChangeWatewmawk);
	dmw_pwint("DMW::%s: WwitebackFCWKChangeWatewmawk = %f\n", __func__, p->Watewmawk->WwitebackFCWKChangeWatewmawk);
	dmw_pwint("DMW::%s: WwitebackUwgentWatewmawk = %f\n", __func__, p->Watewmawk->WwitebackUwgentWatewmawk);
	dmw_pwint("DMW::%s: USWWetwainingWequiwedFinaw = %u\n", __func__, p->USWWetwainingWequiwedFinaw);
	dmw_pwint("DMW::%s: USWWetwainingWatency = %f\n", __func__, p->mmSOCPawametews.USWWetwainingWatency);
#endif

	s->TotawPixewBW = 0.0;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		s->TotawPixewBW = s->TotawPixewBW + p->DPPPewSuwface[k]
					* (p->SwathWidthY[k] * p->BytePewPixewDETY[k] * p->VWatio[k] + p->SwathWidthC[k] * p->BytePewPixewDETC[k] * p->VWatioChwoma[k]) / (p->HTotaw[k] / p->PixewCwock[k]);
	}

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {

		s->WBWatencyHidingSouwceWinesY[k] = (dmw_uint_t)(dmw_min((dmw_fwoat_t)p->MaxWineBuffewWines, dmw_fwoow((dmw_fwoat_t)p->WineBuffewSize / (dmw_fwoat_t)p->WBBitPewPixew[k] / ((dmw_fwoat_t)p->SwathWidthY[k] / dmw_max(p->HWatio[k], 1.0)), 1)) - (p->VTaps[k] - 1));
		s->WBWatencyHidingSouwceWinesC[k] = (dmw_uint_t)(dmw_min((dmw_fwoat_t)p->MaxWineBuffewWines, dmw_fwoow((dmw_fwoat_t)p->WineBuffewSize / (dmw_fwoat_t)p->WBBitPewPixew[k] / ((dmw_fwoat_t)p->SwathWidthC[k] / dmw_max(p->HWatioChwoma[k], 1.0)), 1)) - (p->VTapsChwoma[k] - 1));


#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, MaxWineBuffewWines = %u\n", __func__, k, p->MaxWineBuffewWines);
		dmw_pwint("DMW::%s: k=%u, WineBuffewSize = %u\n", __func__, k, p->WineBuffewSize);
		dmw_pwint("DMW::%s: k=%u, WBBitPewPixew = %u\n", __func__, k, p->WBBitPewPixew[k]);
		dmw_pwint("DMW::%s: k=%u, HWatio = %f\n", __func__, k, p->HWatio[k]);
		dmw_pwint("DMW::%s: k=%u, VTaps              = %u\n", __func__, k, p->VTaps[k]);
#endif

		s->EffectiveWBWatencyHidingY = s->WBWatencyHidingSouwceWinesY[k] / p->VWatio[k] * (p->HTotaw[k] / p->PixewCwock[k]);
		s->EffectiveWBWatencyHidingC = s->WBWatencyHidingSouwceWinesC[k] / p->VWatioChwoma[k] * (p->HTotaw[k] / p->PixewCwock[k]);

		s->EffectiveDETBuffewSizeY = p->DETBuffewSizeY[k];
		if (p->UnboundedWequestEnabwed) {
			s->EffectiveDETBuffewSizeY = s->EffectiveDETBuffewSizeY + p->CompwessedBuffewSizeInkByte * 1024 * (p->SwathWidthY[k] * p->BytePewPixewDETY[k] * p->VWatio[k]) / (p->HTotaw[k] / p->PixewCwock[k]) / s->TotawPixewBW;
		}

		s->WinesInDETY[k] = (dmw_fwoat_t)s->EffectiveDETBuffewSizeY / p->BytePewPixewDETY[k] / p->SwathWidthY[k];
		s->WinesInDETYWoundedDownToSwath[k] = (dmw_uint_t)(dmw_fwoow(s->WinesInDETY[k], p->SwathHeightY[k]));
		s->FuwwDETBuffewingTimeY = s->WinesInDETYWoundedDownToSwath[k] * (p->HTotaw[k] / p->PixewCwock[k]) / p->VWatio[k];

		s->ActiveCwockChangeWatencyHidingY = s->EffectiveWBWatencyHidingY + s->FuwwDETBuffewingTimeY - ((dmw_fwoat_t)p->DSTXAftewScawew[k] / (dmw_fwoat_t)p->HTotaw[k] + (dmw_fwoat_t)p->DSTYAftewScawew[k]) * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k];

		if (p->NumbewOfActiveSuwfaces > 1) {
			s->ActiveCwockChangeWatencyHidingY = s->ActiveCwockChangeWatencyHidingY - (1.0 - 1.0 / (dmw_fwoat_t)p->NumbewOfActiveSuwfaces) * (dmw_fwoat_t)p->SwathHeightY[k] * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k] / p->VWatio[k];
	}

		if (p->BytePewPixewDETC[k] > 0) {
			s->WinesInDETC[k] = p->DETBuffewSizeC[k] / p->BytePewPixewDETC[k] / p->SwathWidthC[k];
			s->WinesInDETCWoundedDownToSwath[k] = (dmw_uint_t)(dmw_fwoow(s->WinesInDETC[k], p->SwathHeightC[k]));
			s->FuwwDETBuffewingTimeC = s->WinesInDETCWoundedDownToSwath[k] * (p->HTotaw[k] / p->PixewCwock[k]) / p->VWatioChwoma[k];
			s->ActiveCwockChangeWatencyHidingC = s->EffectiveWBWatencyHidingC + s->FuwwDETBuffewingTimeC - ((dmw_fwoat_t)p->DSTXAftewScawew[k] / (dmw_fwoat_t)p->HTotaw[k] + (dmw_fwoat_t)p->DSTYAftewScawew[k]) * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k];
			if (p->NumbewOfActiveSuwfaces > 1) {
			s->ActiveCwockChangeWatencyHidingC = s->ActiveCwockChangeWatencyHidingC - (1.0 - 1.0 / (dmw_fwoat_t)p->NumbewOfActiveSuwfaces) * (dmw_fwoat_t)p->SwathHeightC[k] * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k] / p->VWatioChwoma[k];
			}
			s->ActiveCwockChangeWatencyHiding = dmw_min(s->ActiveCwockChangeWatencyHidingY, s->ActiveCwockChangeWatencyHidingC);
		} ewse {
			s->ActiveCwockChangeWatencyHiding = s->ActiveCwockChangeWatencyHidingY;
		}

		s->ActiveDWAMCwockChangeWatencyMawgin[k] = s->ActiveCwockChangeWatencyHiding - p->Watewmawk->UwgentWatewmawk - p->Watewmawk->DWAMCwockChangeWatewmawk;
		s->ActiveFCWKChangeWatencyMawgin[k] = s->ActiveCwockChangeWatencyHiding - p->Watewmawk->UwgentWatewmawk - p->Watewmawk->FCWKChangeWatewmawk;
		s->USWWetwainingWatencyMawgin[k] = s->ActiveCwockChangeWatencyHiding - p->Watewmawk->USWWetwainingWatewmawk;

		if (p->WwitebackEnabwe[k]) {
			s->WwitebackWatencyHiding = (dmw_fwoat_t)p->WwitebackIntewfaceBuffewSize * 1024.0 / ((dmw_fwoat_t)p->WwitebackDestinationWidth[k] * (dmw_fwoat_t)p->WwitebackDestinationHeight[k] / ((dmw_fwoat_t)p->WwitebackSouwceHeight[k] * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k]) * 4.0);
			if (p->WwitebackPixewFowmat[k] == dmw_444_64) {
				s->WwitebackWatencyHiding = s->WwitebackWatencyHiding / 2;
			}
			s->WwitebackDWAMCwockChangeWatencyMawgin = s->WwitebackWatencyHiding - p->Watewmawk->WwitebackDWAMCwockChangeWatewmawk;

			s->WwitebackFCWKChangeWatencyMawgin = s->WwitebackWatencyHiding - p->Watewmawk->WwitebackFCWKChangeWatewmawk;

			s->ActiveDWAMCwockChangeWatencyMawgin[k] = dmw_min(s->ActiveDWAMCwockChangeWatencyMawgin[k], s->WwitebackFCWKChangeWatencyMawgin);
			s->ActiveFCWKChangeWatencyMawgin[k] = dmw_min(s->ActiveFCWKChangeWatencyMawgin[k], s->WwitebackDWAMCwockChangeWatencyMawgin);
		}
		p->MaxActiveDWAMCwockChangeWatencySuppowted[k] =  (p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe) ? 0 : (s->ActiveDWAMCwockChangeWatencyMawgin[k] + p->mmSOCPawametews.DWAMCwockChangeWatency);
		p->ActiveDWAMCwockChangeWatencyMawgin[k] = s->ActiveDWAMCwockChangeWatencyMawgin[k];
	}

	*p->USWWetwainingSuppowt = twue;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if ((p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) && (s->USWWetwainingWatencyMawgin[k] < 0)) {
			*p->USWWetwainingSuppowt = fawse;
		}
	}

	s->FoundCwiticawSuwface = fawse;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if ((p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) && ((!s->FoundCwiticawSuwface)
			|| ((s->ActiveFCWKChangeWatencyMawgin[k] + p->mmSOCPawametews.FCWKChangeWatency) < *p->MaxActiveFCWKChangeWatencySuppowted))) {
			s->FoundCwiticawSuwface = twue;
			*p->MaxActiveFCWKChangeWatencySuppowted = s->ActiveFCWKChangeWatencyMawgin[k] + p->mmSOCPawametews.FCWKChangeWatency;
		}
	}

	fow (dmw_uint_t i = 0; i < p->NumbewOfActiveSuwfaces; ++i) {
		fow (dmw_uint_t j = 0; j < p->NumbewOfActiveSuwfaces; ++j) {
			if (i == j ||
				(p->BwendingAndTiming[i] == i && p->BwendingAndTiming[j] == i) ||
				(p->BwendingAndTiming[j] == j && p->BwendingAndTiming[i] == j) ||
				(p->BwendingAndTiming[i] == p->BwendingAndTiming[j] && p->BwendingAndTiming[i] != i) ||
				(p->SynchwonizeTimingsFinaw && p->PixewCwock[i] == p->PixewCwock[j] && p->HTotaw[i] == p->HTotaw[j] && p->VTotaw[i] == p->VTotaw[j] && p->VActive[i] == p->VActive[j]) ||
				(p->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw && (p->DWWDispway[i] || p->DWWDispway[j]))) {
				s->SynchwonizedSuwfaces[i][j] = twue;
			} ewse {
				s->SynchwonizedSuwfaces[i][j] = fawse;
			}
		}
	}

	s->FCWKChangeSuppowtNumbew = 0;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if ((p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) &&  (s->ActiveFCWKChangeWatencyMawgin[k] < 0)) {
			if (!(p->PwefetchMode[k] <= 1)) {
				s->FCWKChangeSuppowtNumbew = 3;
			} ewse if (s->FCWKChangeSuppowtNumbew == 0) {
				s->FCWKChangeSuppowtNumbew = ((p->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw && p->DWWDispway[k]) ? 2 : 1);
				s->WastSuwfaceWithoutMawgin = k;
			} ewse if (((s->FCWKChangeSuppowtNumbew == 1) && (p->DWWDispway[k] || (!s->SynchwonizedSuwfaces[s->WastSuwfaceWithoutMawgin][k]))) || (s->FCWKChangeSuppowtNumbew == 2))
				s->FCWKChangeSuppowtNumbew = 3;
		}
	}

	if (s->FCWKChangeSuppowtNumbew == 0) {
		*p->FCWKChangeSuppowt = dmw_fcwock_change_vactive;
	} ewse if ((s->FCWKChangeSuppowtNumbew == 1) || (s->FCWKChangeSuppowtNumbew == 2)) {
		*p->FCWKChangeSuppowt = dmw_fcwock_change_vbwank;
	} ewse {
		*p->FCWKChangeSuppowt = dmw_fcwock_change_unsuppowted;
	}

	s->DWAMCwockChangeMethod = 0;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_fuww_fwame)
			s->DWAMCwockChangeMethod = 1;
		ewse if (p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_sub_viewpowt)
			s->DWAMCwockChangeMethod = 2;
	}

	s->DWAMCwockChangeSuppowtNumbew = 0;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (((s->DWAMCwockChangeMethod == 0) && (s->ActiveDWAMCwockChangeWatencyMawgin[k] < 0)) ||
			((s->DWAMCwockChangeMethod == 1) && (p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_fuww_fwame)) ||
			((s->DWAMCwockChangeMethod == 2) && (p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_sub_viewpowt) && (p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe))) {
			if (p->PwefetchMode[k] != 0) { // Don't need to suppowt DWAM cwock change, PwefetchMode 0 means needs DWAM cwock change suppowt
				s->DWAMCwockChangeSuppowtNumbew = 3;
			} ewse if (s->DWAMCwockChangeSuppowtNumbew == 0) {
				s->DWAMCwockChangeSuppowtNumbew =  (p->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw && p->DWWDispway[k]) ? 2 : 1;
				s->WastSuwfaceWithoutMawgin = k;
			} ewse if (((s->DWAMCwockChangeSuppowtNumbew == 1) && (p->DWWDispway[k] || !s->SynchwonizedSuwfaces[s->WastSuwfaceWithoutMawgin][k])) || (s->DWAMCwockChangeSuppowtNumbew == 2)) {
				s->DWAMCwockChangeSuppowtNumbew = 3;
			}
		}
	}

	if (s->DWAMCwockChangeMethod == 0) { // No MAWW usage
		if (s->DWAMCwockChangeSuppowtNumbew == 0) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vactive;
		} ewse if (s->DWAMCwockChangeSuppowtNumbew == 1) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vbwank;
		} ewse if (s->DWAMCwockChangeSuppowtNumbew == 2) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vbwank_dww;
		} ewse {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_unsuppowted;
		}
	} ewse if (s->DWAMCwockChangeMethod == 1) { // Any pipe using MAWW fuww fwame
		if (s->DWAMCwockChangeSuppowtNumbew == 0) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vactive_w_maww_fuww_fwame;
		} ewse if (s->DWAMCwockChangeSuppowtNumbew == 1) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vbwank_w_maww_fuww_fwame;
		} ewse if (s->DWAMCwockChangeSuppowtNumbew == 2) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vbwank_dww_w_maww_fuww_fwame;
		} ewse {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_unsuppowted;
		}
	} ewse { // Any pipe using MAWW subviewpowt
		if (s->DWAMCwockChangeSuppowtNumbew == 0) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vactive_w_maww_sub_vp;
		} ewse if (s->DWAMCwockChangeSuppowtNumbew == 1) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vbwank_w_maww_sub_vp;
		} ewse if (s->DWAMCwockChangeSuppowtNumbew == 2) {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_vbwank_dww_w_maww_sub_vp;
		} ewse {
			*p->DWAMCwockChangeSuppowt = dmw_dwam_cwock_change_unsuppowted;
		}
	}

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		s->dst_y_pstate = (dmw_uint_t)(dmw_ceiw((p->mmSOCPawametews.DWAMCwockChangeWatency + p->mmSOCPawametews.UwgentWatency) / (p->HTotaw[k] / p->PixewCwock[k]), 1));
		s->swc_y_pstate_w = (dmw_uint_t)(dmw_ceiw(s->dst_y_pstate * p->VWatio[k], p->SwathHeightY[k]));
		s->swc_y_ahead_w = (dmw_uint_t)(dmw_fwoow(p->DETBuffewSizeY[k] / p->BytePewPixewDETY[k] / p->SwathWidthY[k], p->SwathHeightY[k]) + s->WBWatencyHidingSouwceWinesY[k]);
		s->sub_vp_wines_w = s->swc_y_pstate_w + s->swc_y_ahead_w + p->meta_wow_height[k];

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, DETBuffewSizeY = %u\n", __func__, k, p->DETBuffewSizeY[k]);
		dmw_pwint("DMW::%s: k=%u, BytePewPixewDETY = %f\n", __func__, k, p->BytePewPixewDETY[k]);
		dmw_pwint("DMW::%s: k=%u, SwathWidthY = %u\n", __func__, k, p->SwathWidthY[k]);
		dmw_pwint("DMW::%s: k=%u, SwathHeightY = %u\n", __func__, k, p->SwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%u, WBWatencyHidingSouwceWinesY = %u\n", __func__, k, s->WBWatencyHidingSouwceWinesY[k]);
		dmw_pwint("DMW::%s: k=%u, dst_y_pstate = %u\n", __func__, k, s->dst_y_pstate);
		dmw_pwint("DMW::%s: k=%u, swc_y_pstate_w = %u\n", __func__, k, s->swc_y_pstate_w);
		dmw_pwint("DMW::%s: k=%u, swc_y_ahead_w = %u\n", __func__, k, s->swc_y_ahead_w);
		dmw_pwint("DMW::%s: k=%u, meta_wow_height = %u\n", __func__, k, p->meta_wow_height[k]);
		dmw_pwint("DMW::%s: k=%u, sub_vp_wines_w  = %u\n", __func__, k, s->sub_vp_wines_w);
#endif
		p->SubViewpowtWinesNeededInMAWW[k] = s->sub_vp_wines_w;

		if (p->BytePewPixewDETC[k] > 0) {
		s->swc_y_pstate_c = (dmw_uint_t)(dmw_ceiw(s->dst_y_pstate * p->VWatioChwoma[k], p->SwathHeightC[k]));
		s->swc_y_ahead_c = (dmw_uint_t)(dmw_fwoow(p->DETBuffewSizeC[k] / p->BytePewPixewDETC[k] / p->SwathWidthC[k], p->SwathHeightC[k]) + s->WBWatencyHidingSouwceWinesC[k]);
		s->sub_vp_wines_c = s->swc_y_pstate_c + s->swc_y_ahead_c + p->meta_wow_height_chwoma[k];
		p->SubViewpowtWinesNeededInMAWW[k] = (dmw_uint_t)(dmw_max(s->sub_vp_wines_w, s->sub_vp_wines_c));

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, swc_y_pstate_c = %u\n", __func__, k, s->swc_y_pstate_c);
		dmw_pwint("DMW::%s: k=%u, swc_y_ahead_c = %u\n", __func__, k, s->swc_y_ahead_c);
		dmw_pwint("DMW::%s: k=%u, meta_wow_height_chwoma = %u\n", __func__, k, p->meta_wow_height_chwoma[k]);
		dmw_pwint("DMW::%s: k=%u, sub_vp_wines_c            = %u\n", __func__, k, s->sub_vp_wines_c);
#endif
		}
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DWAMCwockChangeSuppowt = %u\n", __func__, *p->DWAMCwockChangeSuppowt);
	dmw_pwint("DMW::%s: FCWKChangeSuppowt = %u\n", __func__, *p->FCWKChangeSuppowt);
	dmw_pwint("DMW::%s: MaxActiveFCWKChangeWatencySuppowted = %f\n", __func__, *p->MaxActiveFCWKChangeWatencySuppowted);
	dmw_pwint("DMW::%s: USWWetwainingSuppowt                        = %u\n", __func__, *p->USWWetwainingSuppowt);
#endif
} // CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt

static void CawcuwateDCFCWKDeepSweep(
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_uint_t BytePewPixewY[],
		dmw_uint_t BytePewPixewC[],
		dmw_fwoat_t VWatio[],
		dmw_fwoat_t VWatioChwoma[],
		dmw_uint_t SwathWidthY[],
		dmw_uint_t SwathWidthC[],
		dmw_uint_t DPPPewSuwface[],
		dmw_fwoat_t HWatio[],
		dmw_fwoat_t HWatioChwoma[],
		dmw_fwoat_t PixewCwock[],
		dmw_fwoat_t PSCW_THWOUGHPUT[],
		dmw_fwoat_t PSCW_THWOUGHPUT_CHWOMA[],
		dmw_fwoat_t Dppcwk[],
		dmw_fwoat_t WeadBandwidthWuma[],
		dmw_fwoat_t WeadBandwidthChwoma[],
		dmw_uint_t WetuwnBusWidth,

		// Output
		dmw_fwoat_t *DCFCwkDeepSweep)
{
	dmw_fwoat_t DispwayPipeWineDewivewyTimeWuma;
	dmw_fwoat_t DispwayPipeWineDewivewyTimeChwoma;
	dmw_fwoat_t DCFCwkDeepSweepPewSuwface[__DMW_NUM_PWANES__];
	dmw_fwoat_t WeadBandwidth = 0.0;

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {

		if (VWatio[k] <= 1) {
			DispwayPipeWineDewivewyTimeWuma = SwathWidthY[k] * DPPPewSuwface[k] / HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWuma = SwathWidthY[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k];
		}
		if (BytePewPixewC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwoma = 0;
		} ewse {
			if (VWatioChwoma[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwoma = SwathWidthC[k] * DPPPewSuwface[k] / HWatioChwoma[k] / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwoma = SwathWidthC[k] / PSCW_THWOUGHPUT_CHWOMA[k] / Dppcwk[k];
			}
		}

		if (BytePewPixewC[k] > 0) {
			DCFCwkDeepSweepPewSuwface[k] = dmw_max(__DMW_MIN_DCFCWK_FACTOW__ * SwathWidthY[k] * BytePewPixewY[k] / 32.0 / DispwayPipeWineDewivewyTimeWuma,
														__DMW_MIN_DCFCWK_FACTOW__ * SwathWidthC[k] * BytePewPixewC[k] / 32.0 / DispwayPipeWineDewivewyTimeChwoma);
		} ewse {
			DCFCwkDeepSweepPewSuwface[k] = __DMW_MIN_DCFCWK_FACTOW__ * SwathWidthY[k] * BytePewPixewY[k] / 64.0 / DispwayPipeWineDewivewyTimeWuma;
		}
		DCFCwkDeepSweepPewSuwface[k] = dmw_max(DCFCwkDeepSweepPewSuwface[k], PixewCwock[k] / 16);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, PixewCwock = %f\n", __func__, k, PixewCwock[k]);
		dmw_pwint("DMW::%s: k=%u, DCFCwkDeepSweepPewSuwface = %f\n", __func__, k, DCFCwkDeepSweepPewSuwface[k]);
#endif
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		WeadBandwidth = WeadBandwidth + WeadBandwidthWuma[k] + WeadBandwidthChwoma[k];
	}

	*DCFCwkDeepSweep = dmw_max(8.0, __DMW_MIN_DCFCWK_FACTOW__ * WeadBandwidth / (dmw_fwoat_t) WetuwnBusWidth);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: __DMW_MIN_DCFCWK_FACTOW__ = %f\n", __func__, __DMW_MIN_DCFCWK_FACTOW__);
		dmw_pwint("DMW::%s: WeadBandwidth = %f\n", __func__, WeadBandwidth);
		dmw_pwint("DMW::%s: WetuwnBusWidth = %u\n", __func__, WetuwnBusWidth);
		dmw_pwint("DMW::%s: DCFCwkDeepSweep = %f\n", __func__, *DCFCwkDeepSweep);
#endif

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		*DCFCwkDeepSweep = dmw_max(*DCFCwkDeepSweep, DCFCwkDeepSweepPewSuwface[k]);
	}
	dmw_pwint("DMW::%s: DCFCwkDeepSweep = %f (finaw)\n", __func__, *DCFCwkDeepSweep);
} // CawcuwateDCFCWKDeepSweep

static void CawcuwateUwgentBuwstFactow(
		enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
		dmw_uint_t swath_width_wuma_ub,
		dmw_uint_t swath_width_chwoma_ub,
		dmw_uint_t SwathHeightY,
		dmw_uint_t SwathHeightC,
		dmw_fwoat_t WineTime,
		dmw_fwoat_t UwgentWatency,
		dmw_fwoat_t CuwsowBuffewSize,
		dmw_uint_t CuwsowWidth,
		dmw_uint_t CuwsowBPP,
		dmw_fwoat_t VWatio,
		dmw_fwoat_t VWatioC,
		dmw_fwoat_t BytePewPixewInDETY,
		dmw_fwoat_t BytePewPixewInDETC,
		dmw_uint_t DETBuffewSizeY,
		dmw_uint_t DETBuffewSizeC,
		// Output
		dmw_fwoat_t *UwgentBuwstFactowCuwsow,
		dmw_fwoat_t *UwgentBuwstFactowWuma,
		dmw_fwoat_t *UwgentBuwstFactowChwoma,
		dmw_boow_t *NotEnoughUwgentWatencyHiding)
{
	dmw_fwoat_t WinesInDETWuma;
	dmw_fwoat_t WinesInDETChwoma;
	dmw_uint_t WinesInCuwsowBuffew;
	dmw_fwoat_t CuwsowBuffewSizeInTime;
	dmw_fwoat_t DETBuffewSizeInTimeWuma;
	dmw_fwoat_t DETBuffewSizeInTimeChwoma;

	*NotEnoughUwgentWatencyHiding = 0;

	if (CuwsowWidth > 0) {
		WinesInCuwsowBuffew = 1 << (dmw_uint_t) dmw_fwoow(dmw_wog2(CuwsowBuffewSize * 1024.0 / (CuwsowWidth * CuwsowBPP / 8.0)), 1.0);
		if (VWatio > 0) {
			CuwsowBuffewSizeInTime = WinesInCuwsowBuffew * WineTime / VWatio;
			if (CuwsowBuffewSizeInTime - UwgentWatency <= 0) {
				*NotEnoughUwgentWatencyHiding = 1;
				*UwgentBuwstFactowCuwsow = 0;
			} ewse {
				*UwgentBuwstFactowCuwsow = CuwsowBuffewSizeInTime / (CuwsowBuffewSizeInTime - UwgentWatency);
			}
		} ewse {
			*UwgentBuwstFactowCuwsow = 1;
		}
	}

	WinesInDETWuma = (UseMAWWFowPStateChange == dmw_use_maww_pstate_change_phantom_pipe ? 1024*1024 : DETBuffewSizeY) / BytePewPixewInDETY / swath_width_wuma_ub;

	if (VWatio > 0) {
		DETBuffewSizeInTimeWuma = dmw_fwoow(WinesInDETWuma, SwathHeightY) * WineTime / VWatio;
		if (DETBuffewSizeInTimeWuma - UwgentWatency <= 0) {
			*NotEnoughUwgentWatencyHiding = 1;
			*UwgentBuwstFactowWuma = 0;
		} ewse {
			*UwgentBuwstFactowWuma = DETBuffewSizeInTimeWuma / (DETBuffewSizeInTimeWuma - UwgentWatency);
		}
	} ewse {
		*UwgentBuwstFactowWuma = 1;
	}

	if (BytePewPixewInDETC > 0) {
		WinesInDETChwoma = (UseMAWWFowPStateChange == dmw_use_maww_pstate_change_phantom_pipe ? 1024*1024 : DETBuffewSizeC) / BytePewPixewInDETC / swath_width_chwoma_ub;

		if (VWatioC > 0) {
			DETBuffewSizeInTimeChwoma = dmw_fwoow(WinesInDETChwoma, SwathHeightC) * WineTime / VWatioC;
			if (DETBuffewSizeInTimeChwoma - UwgentWatency <= 0) {
				*NotEnoughUwgentWatencyHiding = 1;
				*UwgentBuwstFactowChwoma = 0;
			} ewse {
				*UwgentBuwstFactowChwoma = DETBuffewSizeInTimeChwoma / (DETBuffewSizeInTimeChwoma - UwgentWatency);
			}
		} ewse {
			*UwgentBuwstFactowChwoma = 1;
		}
	}
} // CawcuwateUwgentBuwstFactow

static void CawcuwatePixewDewivewyTimes(
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_fwoat_t VWatio[],
		dmw_fwoat_t VWatioChwoma[],
		dmw_fwoat_t VWatioPwefetchY[],
		dmw_fwoat_t VWatioPwefetchC[],
		dmw_uint_t swath_width_wuma_ub[],
		dmw_uint_t swath_width_chwoma_ub[],
		dmw_uint_t DPPPewSuwface[],
		dmw_fwoat_t HWatio[],
		dmw_fwoat_t HWatioChwoma[],
		dmw_fwoat_t PixewCwock[],
		dmw_fwoat_t PSCW_THWOUGHPUT[],
		dmw_fwoat_t PSCW_THWOUGHPUT_CHWOMA[],
		dmw_fwoat_t Dppcwk[],
		dmw_uint_t BytePewPixewC[],
		enum dmw_wotation_angwe SouwceScan[],
		dmw_uint_t NumbewOfCuwsows[],
		dmw_uint_t CuwsowWidth[],
		dmw_uint_t CuwsowBPP[],
		dmw_uint_t BwockWidth256BytesY[],
		dmw_uint_t BwockHeight256BytesY[],
		dmw_uint_t BwockWidth256BytesC[],
		dmw_uint_t BwockHeight256BytesC[],

		// Output
		dmw_fwoat_t DispwayPipeWineDewivewyTimeWuma[],
		dmw_fwoat_t DispwayPipeWineDewivewyTimeChwoma[],
		dmw_fwoat_t DispwayPipeWineDewivewyTimeWumaPwefetch[],
		dmw_fwoat_t DispwayPipeWineDewivewyTimeChwomaPwefetch[],
		dmw_fwoat_t DispwayPipeWequestDewivewyTimeWuma[],
		dmw_fwoat_t DispwayPipeWequestDewivewyTimeChwoma[],
		dmw_fwoat_t DispwayPipeWequestDewivewyTimeWumaPwefetch[],
		dmw_fwoat_t DispwayPipeWequestDewivewyTimeChwomaPwefetch[],
		dmw_fwoat_t CuwsowWequestDewivewyTime[],
		dmw_fwoat_t CuwsowWequestDewivewyTimePwefetch[])
{
		dmw_fwoat_t weq_pew_swath_ub;

		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u : HWatio = %f\n", __func__, k, HWatio[k]);
		dmw_pwint("DMW::%s: k=%u : VWatio = %f\n", __func__, k, VWatio[k]);
		dmw_pwint("DMW::%s: k=%u : HWatioChwoma = %f\n", __func__, k, HWatioChwoma[k]);
		dmw_pwint("DMW::%s: k=%u : VWatioChwoma = %f\n", __func__, k, VWatioChwoma[k]);
		dmw_pwint("DMW::%s: k=%u : swath_width_wuma_ub = %u\n", __func__, k, swath_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%u : swath_width_chwoma_ub = %u\n", __func__, k, swath_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%u : PSCW_THWOUGHPUT = %f\n", __func__, k, PSCW_THWOUGHPUT[k]);
		dmw_pwint("DMW::%s: k=%u : PSCW_THWOUGHPUT_CHWOMA = %f\n", __func__, k, PSCW_THWOUGHPUT_CHWOMA[k]);
		dmw_pwint("DMW::%s: k=%u : DPPPewSuwface = %u\n", __func__, k, DPPPewSuwface[k]);
		dmw_pwint("DMW::%s: k=%u : PixewCwock = %f\n", __func__, k, PixewCwock[k]);
		dmw_pwint("DMW::%s: k=%u : Dppcwk = %f\n", __func__, k, Dppcwk[k]);
#endif

		if (VWatio[k] <= 1) {
			DispwayPipeWineDewivewyTimeWuma[k] = swath_width_wuma_ub[k] * DPPPewSuwface[k] / HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWuma[k] = swath_width_wuma_ub[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k];
		}

		if (BytePewPixewC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwoma[k] = 0;
		} ewse {
			if (VWatioChwoma[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwoma[k] = swath_width_chwoma_ub[k] * DPPPewSuwface[k] / HWatioChwoma[k] / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwoma[k] = swath_width_chwoma_ub[k] / PSCW_THWOUGHPUT_CHWOMA[k] / Dppcwk[k];
			}
		}

		if (VWatioPwefetchY[k] <= 1) {
			DispwayPipeWineDewivewyTimeWumaPwefetch[k] = swath_width_wuma_ub[k] * DPPPewSuwface[k] / HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWumaPwefetch[k] = swath_width_wuma_ub[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k];
		}

		if (BytePewPixewC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (VWatioPwefetchC[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = swath_width_chwoma_ub[k] * DPPPewSuwface[k] / HWatioChwoma[k] / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = swath_width_chwoma_ub[k] / PSCW_THWOUGHPUT_CHWOMA[k] / Dppcwk[k];
			}
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWineDewivewyTimeWuma = %f\n", __func__, k, DispwayPipeWineDewivewyTimeWuma[k]);
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWineDewivewyTimeWumaPwefetch = %f\n", __func__, k, DispwayPipeWineDewivewyTimeWumaPwefetch[k]);
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWineDewivewyTimeChwoma = %f\n", __func__, k, DispwayPipeWineDewivewyTimeChwoma[k]);
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWineDewivewyTimeChwomaPwefetch = %f\n", __func__, k, DispwayPipeWineDewivewyTimeChwomaPwefetch[k]);
#endif
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
			weq_pew_swath_ub = swath_width_wuma_ub[k] / BwockWidth256BytesY[k];
		} ewse {
			weq_pew_swath_ub = swath_width_wuma_ub[k] / BwockHeight256BytesY[k];
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u : weq_pew_swath_ub = %f (Wuma)\n", __func__, k, weq_pew_swath_ub);
#endif

		DispwayPipeWequestDewivewyTimeWuma[k] = DispwayPipeWineDewivewyTimeWuma[k] / weq_pew_swath_ub;
		DispwayPipeWequestDewivewyTimeWumaPwefetch[k] = DispwayPipeWineDewivewyTimeWumaPwefetch[k] / weq_pew_swath_ub;
		if (BytePewPixewC[k] == 0) {
			DispwayPipeWequestDewivewyTimeChwoma[k] = 0;
			DispwayPipeWequestDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
				weq_pew_swath_ub = swath_width_chwoma_ub[k] / BwockWidth256BytesC[k];
			} ewse {
				weq_pew_swath_ub = swath_width_chwoma_ub[k] / BwockHeight256BytesC[k];
			}
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u : weq_pew_swath_ub = %f (Chwoma)\n", __func__, k, weq_pew_swath_ub);
#endif
			DispwayPipeWequestDewivewyTimeChwoma[k] = DispwayPipeWineDewivewyTimeChwoma[k] / weq_pew_swath_ub;
			DispwayPipeWequestDewivewyTimeChwomaPwefetch[k] = DispwayPipeWineDewivewyTimeChwomaPwefetch[k] / weq_pew_swath_ub;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWequestDewivewyTimeWuma = %f\n", __func__, k, DispwayPipeWequestDewivewyTimeWuma[k]);
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWequestDewivewyTimeWumaPwefetch = %f\n", __func__, k, DispwayPipeWequestDewivewyTimeWumaPwefetch[k]);
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWequestDewivewyTimeChwoma = %f\n", __func__, k, DispwayPipeWequestDewivewyTimeChwoma[k]);
		dmw_pwint("DMW::%s: k=%u : DispwayPipeWequestDewivewyTimeChwomaPwefetch = %f\n", __func__, k, DispwayPipeWequestDewivewyTimeChwomaPwefetch[k]);
#endif
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		dmw_uint_t cuwsow_weq_pew_width;
		cuwsow_weq_pew_width = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) CuwsowWidth[k] * (dmw_fwoat_t) CuwsowBPP[k] / 256.0 / 8.0, 1.0));
		if (NumbewOfCuwsows[k] > 0) {
			if (VWatio[k] <= 1) {
				CuwsowWequestDewivewyTime[k] = (dmw_fwoat_t) CuwsowWidth[k] / HWatio[k] / PixewCwock[k] / cuwsow_weq_pew_width;
			} ewse {
				CuwsowWequestDewivewyTime[k] = (dmw_fwoat_t) CuwsowWidth[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k] / cuwsow_weq_pew_width;
			}
			if (VWatioPwefetchY[k] <= 1) {
				CuwsowWequestDewivewyTimePwefetch[k] = (dmw_fwoat_t) CuwsowWidth[k] / HWatio[k] / PixewCwock[k] / cuwsow_weq_pew_width;
		} ewse {
			CuwsowWequestDewivewyTimePwefetch[k] = (dmw_fwoat_t) CuwsowWidth[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k] / cuwsow_weq_pew_width;
			}
		} ewse {
			CuwsowWequestDewivewyTime[k] = 0;
			CuwsowWequestDewivewyTimePwefetch[k] = 0;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u : NumbewOfCuwsows = %u\n", __func__, k, NumbewOfCuwsows[k]);
		dmw_pwint("DMW::%s: k=%u : CuwsowWequestDewivewyTime = %f\n", __func__, k, CuwsowWequestDewivewyTime[k]);
		dmw_pwint("DMW::%s: k=%u : CuwsowWequestDewivewyTimePwefetch = %f\n", __func__, k, CuwsowWequestDewivewyTimePwefetch[k]);
#endif
	}
} // CawcuwatePixewDewivewyTimes

static void CawcuwateMetaAndPTETimes(
		dmw_boow_t use_one_wow_fow_fwame[],
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_boow_t GPUVMEnabwe,
		dmw_uint_t MetaChunkSize,
		dmw_uint_t MinMetaChunkSizeBytes,
		dmw_uint_t HTotaw[],
		dmw_fwoat_t VWatio[],
		dmw_fwoat_t VWatioChwoma[],
		dmw_fwoat_t DestinationWinesToWequestWowInVBwank[],
		dmw_fwoat_t DestinationWinesToWequestWowInImmediateFwip[],
		dmw_boow_t DCCEnabwe[],
		dmw_fwoat_t PixewCwock[],
		dmw_uint_t BytePewPixewY[],
		dmw_uint_t BytePewPixewC[],
		enum dmw_wotation_angwe SouwceScan[],
		dmw_uint_t dpte_wow_height[],
		dmw_uint_t dpte_wow_height_chwoma[],
		dmw_uint_t meta_wow_width[],
		dmw_uint_t meta_wow_width_chwoma[],
		dmw_uint_t meta_wow_height[],
		dmw_uint_t meta_wow_height_chwoma[],
		dmw_uint_t meta_weq_width[],
		dmw_uint_t meta_weq_width_chwoma[],
		dmw_uint_t meta_weq_height[],
		dmw_uint_t meta_weq_height_chwoma[],
		dmw_uint_t dpte_gwoup_bytes[],
		dmw_uint_t PTEWequestSizeY[],
		dmw_uint_t PTEWequestSizeC[],
		dmw_uint_t PixewPTEWeqWidthY[],
		dmw_uint_t PixewPTEWeqHeightY[],
		dmw_uint_t PixewPTEWeqWidthC[],
		dmw_uint_t PixewPTEWeqHeightC[],
		dmw_uint_t dpte_wow_width_wuma_ub[],
		dmw_uint_t dpte_wow_width_chwoma_ub[],

		// Output
		dmw_fwoat_t DST_Y_PEW_PTE_WOW_NOM_W[],
		dmw_fwoat_t DST_Y_PEW_PTE_WOW_NOM_C[],
		dmw_fwoat_t DST_Y_PEW_META_WOW_NOM_W[],
		dmw_fwoat_t DST_Y_PEW_META_WOW_NOM_C[],
		dmw_fwoat_t TimePewMetaChunkNominaw[],
		dmw_fwoat_t TimePewChwomaMetaChunkNominaw[],
		dmw_fwoat_t TimePewMetaChunkVBwank[],
		dmw_fwoat_t TimePewChwomaMetaChunkVBwank[],
		dmw_fwoat_t TimePewMetaChunkFwip[],
		dmw_fwoat_t TimePewChwomaMetaChunkFwip[],
		dmw_fwoat_t time_pew_pte_gwoup_nom_wuma[],
		dmw_fwoat_t time_pew_pte_gwoup_vbwank_wuma[],
		dmw_fwoat_t time_pew_pte_gwoup_fwip_wuma[],
		dmw_fwoat_t time_pew_pte_gwoup_nom_chwoma[],
		dmw_fwoat_t time_pew_pte_gwoup_vbwank_chwoma[],
		dmw_fwoat_t time_pew_pte_gwoup_fwip_chwoma[])
{
	dmw_uint_t meta_chunk_width;
	dmw_uint_t min_meta_chunk_width;
	dmw_uint_t meta_chunk_pew_wow_int;
	dmw_uint_t meta_wow_wemaindew;
	dmw_uint_t meta_chunk_thweshowd;
	dmw_uint_t meta_chunks_pew_wow_ub;
	dmw_uint_t meta_chunk_width_chwoma;
	dmw_uint_t min_meta_chunk_width_chwoma;
	dmw_uint_t meta_chunk_pew_wow_int_chwoma;
	dmw_uint_t meta_wow_wemaindew_chwoma;
	dmw_uint_t meta_chunk_thweshowd_chwoma;
	dmw_uint_t meta_chunks_pew_wow_ub_chwoma;
	dmw_uint_t dpte_gwoup_width_wuma;
	dmw_uint_t dpte_gwoups_pew_wow_wuma_ub;
	dmw_uint_t dpte_gwoup_width_chwoma;
	dmw_uint_t dpte_gwoups_pew_wow_chwoma_ub;

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		DST_Y_PEW_PTE_WOW_NOM_W[k] = dpte_wow_height[k] / VWatio[k];
		if (BytePewPixewC[k] == 0) {
			DST_Y_PEW_PTE_WOW_NOM_C[k] = 0;
		} ewse {
			DST_Y_PEW_PTE_WOW_NOM_C[k] = dpte_wow_height_chwoma[k] / VWatioChwoma[k];
		}
		DST_Y_PEW_META_WOW_NOM_W[k] = meta_wow_height[k] / VWatio[k];
		if (BytePewPixewC[k] == 0) {
			DST_Y_PEW_META_WOW_NOM_C[k] = 0;
		} ewse {
			DST_Y_PEW_META_WOW_NOM_C[k] = meta_wow_height_chwoma[k] / VWatioChwoma[k];
		}
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (DCCEnabwe[k] == twue) {
			meta_chunk_width = MetaChunkSize * 1024 * 256 / BytePewPixewY[k] / meta_wow_height[k];
			min_meta_chunk_width = MinMetaChunkSizeBytes * 256 / BytePewPixewY[k] / meta_wow_height[k];
			meta_chunk_pew_wow_int = meta_wow_width[k] / meta_chunk_width;
			meta_wow_wemaindew = meta_wow_width[k] % meta_chunk_width;
			if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
				meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_width[k];
			} ewse {
				meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_height[k];
			}
			if (meta_wow_wemaindew <= meta_chunk_thweshowd) {
				meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 1;
			} ewse {
				meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 2;
			}
			TimePewMetaChunkNominaw[k] = meta_wow_height[k] / VWatio[k] * HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			TimePewMetaChunkVBwank[k] = DestinationWinesToWequestWowInVBwank[k] * HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			TimePewMetaChunkFwip[k] = DestinationWinesToWequestWowInImmediateFwip[k] * HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			if (BytePewPixewC[k] == 0) {
				TimePewChwomaMetaChunkNominaw[k] = 0;
				TimePewChwomaMetaChunkVBwank[k] = 0;
				TimePewChwomaMetaChunkFwip[k] = 0;
			} ewse {
				meta_chunk_width_chwoma = MetaChunkSize * 1024 * 256 / BytePewPixewC[k] / meta_wow_height_chwoma[k];
				min_meta_chunk_width_chwoma = MinMetaChunkSizeBytes * 256 / BytePewPixewC[k] / meta_wow_height_chwoma[k];
				meta_chunk_pew_wow_int_chwoma = (dmw_uint_t)((dmw_fwoat_t) meta_wow_width_chwoma[k] / meta_chunk_width_chwoma);
				meta_wow_wemaindew_chwoma = meta_wow_width_chwoma[k] % meta_chunk_width_chwoma;
				if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
					meta_chunk_thweshowd_chwoma = 2 * min_meta_chunk_width_chwoma - meta_weq_width_chwoma[k];
				} ewse {
					meta_chunk_thweshowd_chwoma = 2 * min_meta_chunk_width_chwoma - meta_weq_height_chwoma[k];
				}
				if (meta_wow_wemaindew_chwoma <= meta_chunk_thweshowd_chwoma) {
					meta_chunks_pew_wow_ub_chwoma = meta_chunk_pew_wow_int_chwoma + 1;
				} ewse {
					meta_chunks_pew_wow_ub_chwoma = meta_chunk_pew_wow_int_chwoma + 2;
				}
				TimePewChwomaMetaChunkNominaw[k] = meta_wow_height_chwoma[k] / VWatioChwoma[k] * HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub_chwoma;
				TimePewChwomaMetaChunkVBwank[k] = DestinationWinesToWequestWowInVBwank[k] * HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub_chwoma;
				TimePewChwomaMetaChunkFwip[k] = DestinationWinesToWequestWowInImmediateFwip[k] * HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub_chwoma;
			}
		} ewse {
			TimePewMetaChunkNominaw[k] = 0;
			TimePewMetaChunkVBwank[k] = 0;
			TimePewMetaChunkFwip[k] = 0;
			TimePewChwomaMetaChunkNominaw[k] = 0;
			TimePewChwomaMetaChunkVBwank[k] = 0;
			TimePewChwomaMetaChunkFwip[k] = 0;
		}
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (GPUVMEnabwe == twue) {
			if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
				dpte_gwoup_width_wuma = (dmw_uint_t)((dmw_fwoat_t) dpte_gwoup_bytes[k] / (dmw_fwoat_t) PTEWequestSizeY[k] * PixewPTEWeqWidthY[k]);
			} ewse {
				dpte_gwoup_width_wuma = (dmw_uint_t)((dmw_fwoat_t) dpte_gwoup_bytes[k] / (dmw_fwoat_t) PTEWequestSizeY[k] * PixewPTEWeqHeightY[k]);
			}

			if (use_one_wow_fow_fwame[k]) {
				dpte_gwoups_pew_wow_wuma_ub = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) dpte_wow_width_wuma_ub[k] / (dmw_fwoat_t) dpte_gwoup_width_wuma / 2.0, 1.0));
			} ewse {
				dpte_gwoups_pew_wow_wuma_ub = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) dpte_wow_width_wuma_ub[k] / (dmw_fwoat_t) dpte_gwoup_width_wuma, 1.0));
			}

			dmw_pwint("DMW::%s: k=%u, use_one_wow_fow_fwame = %u\n", __func__, k, use_one_wow_fow_fwame[k]);
			dmw_pwint("DMW::%s: k=%u, dpte_gwoup_bytes = %u\n", __func__, k, dpte_gwoup_bytes[k]);
			dmw_pwint("DMW::%s: k=%u, PTEWequestSizeY = %u\n", __func__, k, PTEWequestSizeY[k]);
			dmw_pwint("DMW::%s: k=%u, PixewPTEWeqWidthY = %u\n", __func__, k, PixewPTEWeqWidthY[k]);
			dmw_pwint("DMW::%s: k=%u, PixewPTEWeqHeightY = %u\n", __func__, k, PixewPTEWeqHeightY[k]);
			dmw_pwint("DMW::%s: k=%u, dpte_wow_width_wuma_ub = %u\n", __func__, k, dpte_wow_width_wuma_ub[k]);
			dmw_pwint("DMW::%s: k=%u, dpte_gwoup_width_wuma = %u\n", __func__, k, dpte_gwoup_width_wuma);
			dmw_pwint("DMW::%s: k=%u, dpte_gwoups_pew_wow_wuma_ub = %u\n", __func__, k, dpte_gwoups_pew_wow_wuma_ub);

			time_pew_pte_gwoup_nom_wuma[k] = DST_Y_PEW_PTE_WOW_NOM_W[k] * HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			time_pew_pte_gwoup_vbwank_wuma[k] = DestinationWinesToWequestWowInVBwank[k] * HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			time_pew_pte_gwoup_fwip_wuma[k] = DestinationWinesToWequestWowInImmediateFwip[k] * HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			if (BytePewPixewC[k] == 0) {
				time_pew_pte_gwoup_nom_chwoma[k] = 0;
				time_pew_pte_gwoup_vbwank_chwoma[k] = 0;
				time_pew_pte_gwoup_fwip_chwoma[k] = 0;
			} ewse {
				if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
					dpte_gwoup_width_chwoma = (dmw_uint_t)((dmw_fwoat_t) dpte_gwoup_bytes[k] / (dmw_fwoat_t) PTEWequestSizeC[k] * PixewPTEWeqWidthC[k]);
				} ewse {
					dpte_gwoup_width_chwoma = (dmw_uint_t)((dmw_fwoat_t) dpte_gwoup_bytes[k] / (dmw_fwoat_t) PTEWequestSizeC[k] * PixewPTEWeqHeightC[k]);
				}

				if (use_one_wow_fow_fwame[k]) {
					dpte_gwoups_pew_wow_chwoma_ub = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) dpte_wow_width_chwoma_ub[k] / (dmw_fwoat_t) dpte_gwoup_width_chwoma / 2.0, 1.0));
				} ewse {
					dpte_gwoups_pew_wow_chwoma_ub = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) dpte_wow_width_chwoma_ub[k] / (dmw_fwoat_t) dpte_gwoup_width_chwoma, 1.0));
				}
				dmw_pwint("DMW::%s: k=%u, dpte_wow_width_chwoma_ub = %u\n", __func__, k, dpte_wow_width_chwoma_ub[k]);
				dmw_pwint("DMW::%s: k=%u, dpte_gwoup_width_chwoma = %u\n", __func__, k, dpte_gwoup_width_chwoma);
				dmw_pwint("DMW::%s: k=%u, dpte_gwoups_pew_wow_chwoma_ub = %u\n", __func__, k, dpte_gwoups_pew_wow_chwoma_ub);

				time_pew_pte_gwoup_nom_chwoma[k] = DST_Y_PEW_PTE_WOW_NOM_C[k] * HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_chwoma_ub;
				time_pew_pte_gwoup_vbwank_chwoma[k] = DestinationWinesToWequestWowInVBwank[k] * HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_chwoma_ub;
				time_pew_pte_gwoup_fwip_chwoma[k] = DestinationWinesToWequestWowInImmediateFwip[k] * HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_chwoma_ub;
			}
		} ewse {
			time_pew_pte_gwoup_nom_wuma[k] = 0;
			time_pew_pte_gwoup_vbwank_wuma[k] = 0;
			time_pew_pte_gwoup_fwip_wuma[k] = 0;
			time_pew_pte_gwoup_nom_chwoma[k] = 0;
			time_pew_pte_gwoup_vbwank_chwoma[k] = 0;
			time_pew_pte_gwoup_fwip_chwoma[k] = 0;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, DestinationWinesToWequestWowInVBwank = %f\n", __func__, k, DestinationWinesToWequestWowInVBwank[k]);
		dmw_pwint("DMW::%s: k=%u, DestinationWinesToWequestWowInImmediateFwip = %f\n", __func__, k, DestinationWinesToWequestWowInImmediateFwip[k]);

		dmw_pwint("DMW::%s: k=%u, DST_Y_PEW_PTE_WOW_NOM_W = %f\n", __func__, k, DST_Y_PEW_PTE_WOW_NOM_W[k]);
		dmw_pwint("DMW::%s: k=%u, DST_Y_PEW_PTE_WOW_NOM_C = %f\n", __func__, k, DST_Y_PEW_PTE_WOW_NOM_C[k]);
		dmw_pwint("DMW::%s: k=%u, DST_Y_PEW_META_WOW_NOM_W = %f\n", __func__, k, DST_Y_PEW_META_WOW_NOM_W[k]);
		dmw_pwint("DMW::%s: k=%u, DST_Y_PEW_META_WOW_NOM_C = %f\n", __func__, k, DST_Y_PEW_META_WOW_NOM_C[k]);
		dmw_pwint("DMW::%s: k=%u, TimePewMetaChunkNominaw = %f\n", __func__, k, TimePewMetaChunkNominaw[k]);
		dmw_pwint("DMW::%s: k=%u, TimePewMetaChunkVBwank = %f\n", __func__, k, TimePewMetaChunkVBwank[k]);
		dmw_pwint("DMW::%s: k=%u, TimePewMetaChunkFwip = %f\n", __func__, k, TimePewMetaChunkFwip[k]);
		dmw_pwint("DMW::%s: k=%u, TimePewChwomaMetaChunkNominaw = %f\n", __func__, k, TimePewChwomaMetaChunkNominaw[k]);
		dmw_pwint("DMW::%s: k=%u, TimePewChwomaMetaChunkVBwank = %f\n", __func__, k, TimePewChwomaMetaChunkVBwank[k]);
		dmw_pwint("DMW::%s: k=%u, TimePewChwomaMetaChunkFwip = %f\n", __func__, k, TimePewChwomaMetaChunkFwip[k]);
		dmw_pwint("DMW::%s: k=%u, time_pew_pte_gwoup_nom_wuma = %f\n", __func__, k, time_pew_pte_gwoup_nom_wuma[k]);
		dmw_pwint("DMW::%s: k=%u, time_pew_pte_gwoup_vbwank_wuma = %f\n", __func__, k, time_pew_pte_gwoup_vbwank_wuma[k]);
		dmw_pwint("DMW::%s: k=%u, time_pew_pte_gwoup_fwip_wuma = %f\n", __func__, k, time_pew_pte_gwoup_fwip_wuma[k]);
		dmw_pwint("DMW::%s: k=%u, time_pew_pte_gwoup_nom_chwoma = %f\n", __func__, k, time_pew_pte_gwoup_nom_chwoma[k]);
		dmw_pwint("DMW::%s: k=%u, time_pew_pte_gwoup_vbwank_chwoma = %f\n", __func__, k, time_pew_pte_gwoup_vbwank_chwoma[k]);
		dmw_pwint("DMW::%s: k=%u, time_pew_pte_gwoup_fwip_chwoma   = %f\n", __func__, k, time_pew_pte_gwoup_fwip_chwoma[k]);
#endif
	}
} // CawcuwateMetaAndPTETimes

static void CawcuwateVMGwoupAndWequestTimes(
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_boow_t GPUVMEnabwe,
		dmw_uint_t GPUVMMaxPageTabweWevews,
		dmw_uint_t HTotaw[],
		dmw_uint_t BytePewPixewC[],
		dmw_fwoat_t DestinationWinesToWequestVMInVBwank[],
		dmw_fwoat_t DestinationWinesToWequestVMInImmediateFwip[],
		dmw_boow_t DCCEnabwe[],
		dmw_fwoat_t PixewCwock[],
		dmw_uint_t dpte_wow_width_wuma_ub[],
		dmw_uint_t dpte_wow_width_chwoma_ub[],
		dmw_uint_t vm_gwoup_bytes[],
		dmw_uint_t dpde0_bytes_pew_fwame_ub_w[],
		dmw_uint_t dpde0_bytes_pew_fwame_ub_c[],
		dmw_uint_t meta_pte_bytes_pew_fwame_ub_w[],
		dmw_uint_t meta_pte_bytes_pew_fwame_ub_c[],

		// Output
		dmw_fwoat_t TimePewVMGwoupVBwank[],
		dmw_fwoat_t TimePewVMGwoupFwip[],
		dmw_fwoat_t TimePewVMWequestVBwank[],
		dmw_fwoat_t TimePewVMWequestFwip[])
{
	dmw_uint_t num_gwoup_pew_wowew_vm_stage;
	dmw_uint_t num_weq_pew_wowew_vm_stage;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: NumbewOfActiveSuwfaces = %u\n", __func__, NumbewOfActiveSuwfaces);
	dmw_pwint("DMW::%s: GPUVMEnabwe = %u\n", __func__, GPUVMEnabwe);
#endif
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, DCCEnabwe = %u\n", __func__, k, DCCEnabwe[k]);
		dmw_pwint("DMW::%s: k=%u, vm_gwoup_bytes = %u\n", __func__, k, vm_gwoup_bytes[k]);
		dmw_pwint("DMW::%s: k=%u, dpde0_bytes_pew_fwame_ub_w = %u\n", __func__, k, dpde0_bytes_pew_fwame_ub_w[k]);
		dmw_pwint("DMW::%s: k=%u, dpde0_bytes_pew_fwame_ub_c = %u\n", __func__, k, dpde0_bytes_pew_fwame_ub_c[k]);
		dmw_pwint("DMW::%s: k=%u, meta_pte_bytes_pew_fwame_ub_w = %u\n", __func__, k, meta_pte_bytes_pew_fwame_ub_w[k]);
		dmw_pwint("DMW::%s: k=%u, meta_pte_bytes_pew_fwame_ub_c = %u\n", __func__, k, meta_pte_bytes_pew_fwame_ub_c[k]);
#endif

		if (GPUVMEnabwe == twue && (DCCEnabwe[k] == twue || GPUVMMaxPageTabweWevews > 1)) {
			if (DCCEnabwe[k] == fawse) {
				if (BytePewPixewC[k] > 0) {
					num_gwoup_pew_wowew_vm_stage = (dmw_uint_t) (dmw_ceiw((dmw_fwoat_t) dpde0_bytes_pew_fwame_ub_w[k] / (dmw_fwoat_t) vm_gwoup_bytes[k], 1.0) +
													dmw_ceiw((dmw_fwoat_t) dpde0_bytes_pew_fwame_ub_c[k] / (dmw_fwoat_t) vm_gwoup_bytes[k], 1.0));
				} ewse {
					num_gwoup_pew_wowew_vm_stage = (dmw_uint_t) (dmw_ceiw((dmw_fwoat_t) dpde0_bytes_pew_fwame_ub_w[k] / (dmw_fwoat_t) vm_gwoup_bytes[k], 1.0));
				}
			} ewse {
				if (GPUVMMaxPageTabweWevews == 1) {
					if (BytePewPixewC[k] > 0) {
						num_gwoup_pew_wowew_vm_stage = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) (meta_pte_bytes_pew_fwame_ub_w[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1.0) +
																	dmw_ceiw((dmw_fwoat_t) (meta_pte_bytes_pew_fwame_ub_c[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1.0));
					} ewse {
						num_gwoup_pew_wowew_vm_stage = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) (meta_pte_bytes_pew_fwame_ub_w[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1.0));
					}
				} ewse {
					if (BytePewPixewC[k] > 0) {
						num_gwoup_pew_wowew_vm_stage = (dmw_uint_t)(2.0 + dmw_ceiw((dmw_fwoat_t) (dpde0_bytes_pew_fwame_ub_w[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1) +
														dmw_ceiw((dmw_fwoat_t) (dpde0_bytes_pew_fwame_ub_c[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1) +
														dmw_ceiw((dmw_fwoat_t) (meta_pte_bytes_pew_fwame_ub_w[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1) +
														dmw_ceiw((dmw_fwoat_t) (meta_pte_bytes_pew_fwame_ub_c[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1));
					} ewse {
						num_gwoup_pew_wowew_vm_stage = (dmw_uint_t)(1.0 + dmw_ceiw((dmw_fwoat_t) (dpde0_bytes_pew_fwame_ub_w[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1) +
																	dmw_ceiw((dmw_fwoat_t) (meta_pte_bytes_pew_fwame_ub_w[k]) / (dmw_fwoat_t) (vm_gwoup_bytes[k]), 1));
					}
				}
			}

			if (DCCEnabwe[k] == fawse) {
				if (BytePewPixewC[k] > 0) {
					num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64 + dpde0_bytes_pew_fwame_ub_c[k] / 64;
				} ewse {
					num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64;
				}
			} ewse {
				if (GPUVMMaxPageTabweWevews == 1) {
					if (BytePewPixewC[k] > 0) {
						num_weq_pew_wowew_vm_stage = meta_pte_bytes_pew_fwame_ub_w[k] / 64 + meta_pte_bytes_pew_fwame_ub_c[k] / 64;
					} ewse {
						num_weq_pew_wowew_vm_stage = meta_pte_bytes_pew_fwame_ub_w[k] / 64;
					}
				} ewse {
					if (BytePewPixewC[k] > 0) {
						num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64 + dpde0_bytes_pew_fwame_ub_c[k] / 64 + meta_pte_bytes_pew_fwame_ub_w[k] / 64 + meta_pte_bytes_pew_fwame_ub_c[k] / 64;
					} ewse {
						num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64 + meta_pte_bytes_pew_fwame_ub_w[k] / 64;
					}
				}
			}

			TimePewVMGwoupVBwank[k] = DestinationWinesToWequestVMInVBwank[k] * HTotaw[k] / PixewCwock[k] / num_gwoup_pew_wowew_vm_stage;
			TimePewVMGwoupFwip[k] = DestinationWinesToWequestVMInImmediateFwip[k] * HTotaw[k] / PixewCwock[k] / num_gwoup_pew_wowew_vm_stage;
			TimePewVMWequestVBwank[k] = DestinationWinesToWequestVMInVBwank[k] * HTotaw[k] / PixewCwock[k] / num_weq_pew_wowew_vm_stage;
			TimePewVMWequestFwip[k] = DestinationWinesToWequestVMInImmediateFwip[k] * HTotaw[k] / PixewCwock[k] / num_weq_pew_wowew_vm_stage;

			if (GPUVMMaxPageTabweWevews > 2) {
				TimePewVMGwoupVBwank[k] = TimePewVMGwoupVBwank[k] / 2;
				TimePewVMGwoupFwip[k] = TimePewVMGwoupFwip[k] / 2;
				TimePewVMWequestVBwank[k] = TimePewVMWequestVBwank[k] / 2;
				TimePewVMWequestFwip[k]    = TimePewVMWequestFwip[k] / 2;
			}

		} ewse {
			TimePewVMGwoupVBwank[k] = 0;
			TimePewVMGwoupFwip[k] = 0;
			TimePewVMWequestVBwank[k] = 0;
			TimePewVMWequestFwip[k] = 0;
		}

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u, TimePewVMGwoupVBwank = %f\n", __func__, k, TimePewVMGwoupVBwank[k]);
			dmw_pwint("DMW::%s: k=%u, TimePewVMGwoupFwip = %f\n", __func__, k, TimePewVMGwoupFwip[k]);
			dmw_pwint("DMW::%s: k=%u, TimePewVMWequestVBwank = %f\n", __func__, k, TimePewVMWequestVBwank[k]);
			dmw_pwint("DMW::%s: k=%u, TimePewVMWequestFwip = %f\n", __func__, k, TimePewVMWequestFwip[k]);
#endif
	}
} // CawcuwateVMGwoupAndWequestTimes

static void CawcuwateStuttewEfficiency(stwuct dispway_mode_wib_scwatch_st *scwatch,
		stwuct CawcuwateStuttewEfficiency_pawams_st *p)
{
	dmw_fwoat_t DETBuffewingTimeY = 0;
	dmw_fwoat_t SwathWidthYCwiticawSuwface = 0;
	dmw_fwoat_t SwathHeightYCwiticawSuwface = 0;
	dmw_fwoat_t VActiveTimeCwiticawSuwface = 0;
	dmw_fwoat_t FwameTimeCwiticawSuwface = 0;
	dmw_uint_t BytePewPixewYCwiticawSuwface = 0;
	dmw_fwoat_t WinesToFinishSwathTwansfewStuttewCwiticawSuwface = 0;
	dmw_uint_t DETBuffewSizeYCwiticawSuwface = 0;
	dmw_fwoat_t MinTTUVBwankCwiticawSuwface = 0;
	dmw_uint_t BwockWidth256BytesYCwiticawSuwface = 0;
	dmw_boow_t SingwePwaneCwiticawSuwface = 0;
	dmw_boow_t SingwePipeCwiticawSuwface = 0;
	dmw_fwoat_t TotawCompwessedWeadBandwidth = 0;
	dmw_fwoat_t TotawWowWeadBandwidth = 0;
	dmw_fwoat_t AvewageDCCCompwessionWate = 0;
	dmw_fwoat_t EffectiveCompwessedBuffewSize = 0;
	dmw_fwoat_t PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew = 0;
	dmw_fwoat_t StuttewBuwstTime = 0;
	dmw_uint_t TotawActiveWwiteback = 0;
	dmw_fwoat_t WinesInDETY = 0;
	dmw_fwoat_t WinesInDETYWoundedDownToSwath = 0;
	dmw_fwoat_t MaximumEffectiveCompwessionWuma = 0;
	dmw_fwoat_t MaximumEffectiveCompwessionChwoma = 0;
	dmw_fwoat_t TotawZewoSizeWequestWeadBandwidth = 0;
	dmw_fwoat_t TotawZewoSizeCompwessedWeadBandwidth = 0;
	dmw_fwoat_t AvewageDCCZewoSizeFwaction = 0;
	dmw_fwoat_t AvewageZewoSizeCompwessionWate = 0;

	dmw_boow_t FoundCwiticawSuwface = fawse;

	dmw_uint_t TotawNumbewOfActiveOTG = 0;
	dmw_fwoat_t SingwePixewCwock;
	dmw_uint_t SingweHTotaw;
	dmw_uint_t SingweVTotaw;
	dmw_boow_t SameTiming = twue;

	dmw_fwoat_t WastStuttewPewiod = 0.0;
	dmw_fwoat_t WastZ8StuttewPewiod = 0.0;

	dmw_uint_t SwathSizeCwiticawSuwface;
	dmw_uint_t WastChunkOfSwathSize;
	dmw_uint_t MissingPawtOfWastSwathOfDETSize;

	TotawZewoSizeWequestWeadBandwidth = 0;
	TotawZewoSizeCompwessedWeadBandwidth = 0;
	TotawWowWeadBandwidth = 0;
	TotawCompwessedWeadBandwidth = 0;

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
	if (p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) {
		if (p->DCCEnabwe[k] == twue) {
			if ((dmw_is_vewticaw_wotation(p->SouwceScan[k]) && p->BwockWidth256BytesY[k] > p->SwathHeightY[k]) || (!dmw_is_vewticaw_wotation(p->SouwceScan[k]) && p->BwockHeight256BytesY[k] > p->SwathHeightY[k]) || p->DCCYMaxUncompwessedBwock[k] < 256) {
				MaximumEffectiveCompwessionWuma = 2;
			} ewse {
				MaximumEffectiveCompwessionWuma = 4;
			}
			TotawCompwessedWeadBandwidth = TotawCompwessedWeadBandwidth + p->WeadBandwidthSuwfaceWuma[k] / dmw_min(p->NetDCCWateWuma[k], MaximumEffectiveCompwessionWuma);
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u, WeadBandwidthSuwfaceWuma = %f\n", __func__, k, p->WeadBandwidthSuwfaceWuma[k]);
			dmw_pwint("DMW::%s: k=%u, NetDCCWateWuma = %f\n", __func__, k, p->NetDCCWateWuma[k]);
			dmw_pwint("DMW::%s: k=%u, MaximumEffectiveCompwessionWuma = %f\n", __func__, k, MaximumEffectiveCompwessionWuma);
#endif
			TotawZewoSizeWequestWeadBandwidth = TotawZewoSizeWequestWeadBandwidth + p->WeadBandwidthSuwfaceWuma[k] * p->DCCFwactionOfZewoSizeWequestsWuma[k];
			TotawZewoSizeCompwessedWeadBandwidth = TotawZewoSizeCompwessedWeadBandwidth + p->WeadBandwidthSuwfaceWuma[k] * p->DCCFwactionOfZewoSizeWequestsWuma[k] / MaximumEffectiveCompwessionWuma;

			if (p->WeadBandwidthSuwfaceChwoma[k] > 0) {
				if ((dmw_is_vewticaw_wotation(p->SouwceScan[k]) && p->BwockWidth256BytesC[k] > p->SwathHeightC[k]) || (!dmw_is_vewticaw_wotation(p->SouwceScan[k]) && p->BwockHeight256BytesC[k] > p->SwathHeightC[k]) || p->DCCCMaxUncompwessedBwock[k] < 256) {
					MaximumEffectiveCompwessionChwoma = 2;
				} ewse {
					MaximumEffectiveCompwessionChwoma = 4;
				}
				TotawCompwessedWeadBandwidth = TotawCompwessedWeadBandwidth + p->WeadBandwidthSuwfaceChwoma[k] / dmw_min(p->NetDCCWateChwoma[k], MaximumEffectiveCompwessionChwoma);
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%u, WeadBandwidthSuwfaceChwoma = %f\n", __func__, k, p->WeadBandwidthSuwfaceChwoma[k]);
				dmw_pwint("DMW::%s: k=%u, NetDCCWateChwoma = %f\n", __func__, k, p->NetDCCWateChwoma[k]);
				dmw_pwint("DMW::%s: k=%u, MaximumEffectiveCompwessionChwoma = %f\n", __func__, k, MaximumEffectiveCompwessionChwoma);
#endif
				TotawZewoSizeWequestWeadBandwidth = TotawZewoSizeWequestWeadBandwidth + p->WeadBandwidthSuwfaceChwoma[k] * p->DCCFwactionOfZewoSizeWequestsChwoma[k];
				TotawZewoSizeCompwessedWeadBandwidth = TotawZewoSizeCompwessedWeadBandwidth + p->WeadBandwidthSuwfaceChwoma[k] * p->DCCFwactionOfZewoSizeWequestsChwoma[k] / MaximumEffectiveCompwessionChwoma;
			}
		} ewse {
			TotawCompwessedWeadBandwidth = TotawCompwessedWeadBandwidth + p->WeadBandwidthSuwfaceWuma[k] + p->WeadBandwidthSuwfaceChwoma[k];
		}
		TotawWowWeadBandwidth = TotawWowWeadBandwidth + p->DPPPewSuwface[k] * (p->meta_wow_bw[k] + p->dpte_wow_bw[k]);
	}
	}

	AvewageDCCCompwessionWate = p->TotawDataWeadBandwidth / TotawCompwessedWeadBandwidth;
	AvewageDCCZewoSizeFwaction = TotawZewoSizeWequestWeadBandwidth / p->TotawDataWeadBandwidth;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: UnboundedWequestEnabwed = %u\n", __func__, p->UnboundedWequestEnabwed);
	dmw_pwint("DMW::%s: TotawCompwessedWeadBandwidth = %f\n", __func__, TotawCompwessedWeadBandwidth);
	dmw_pwint("DMW::%s: TotawZewoSizeWequestWeadBandwidth = %f\n", __func__, TotawZewoSizeWequestWeadBandwidth);
	dmw_pwint("DMW::%s: TotawZewoSizeCompwessedWeadBandwidth = %f\n", __func__, TotawZewoSizeCompwessedWeadBandwidth);
	dmw_pwint("DMW::%s: MaximumEffectiveCompwessionWuma = %f\n", __func__, MaximumEffectiveCompwessionWuma);
	dmw_pwint("DMW::%s: MaximumEffectiveCompwessionChwoma = %f\n", __func__, MaximumEffectiveCompwessionChwoma);
	dmw_pwint("DMW::%s: AvewageDCCCompwessionWate = %f\n", __func__, AvewageDCCCompwessionWate);
	dmw_pwint("DMW::%s: AvewageDCCZewoSizeFwaction = %f\n", __func__, AvewageDCCZewoSizeFwaction);
	dmw_pwint("DMW::%s: CompbufWesewvedSpace64B = %u\n", __func__, p->CompbufWesewvedSpace64B);
	dmw_pwint("DMW::%s: CompbufWesewvedSpaceZs = %u\n", __func__, p->CompbufWesewvedSpaceZs);
	dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte = %u\n", __func__, p->CompwessedBuffewSizeInkByte);
#endif
	if (AvewageDCCZewoSizeFwaction == 1) {
		AvewageZewoSizeCompwessionWate = TotawZewoSizeWequestWeadBandwidth / TotawZewoSizeCompwessedWeadBandwidth;
		EffectiveCompwessedBuffewSize = (dmw_fwoat_t)p->MetaFIFOSizeInKEntwies * 1024 * 64 * AvewageZewoSizeCompwessionWate + ((dmw_fwoat_t)p->ZewoSizeBuffewEntwies - p->CompbufWesewvedSpaceZs) * 64 * AvewageZewoSizeCompwessionWate;
	} 	ewse if (AvewageDCCZewoSizeFwaction > 0) {
		AvewageZewoSizeCompwessionWate = TotawZewoSizeWequestWeadBandwidth / TotawZewoSizeCompwessedWeadBandwidth;
		EffectiveCompwessedBuffewSize = dmw_min((dmw_fwoat_t)p->CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate,
											(dmw_fwoat_t)p->MetaFIFOSizeInKEntwies * 1024 * 64 / (AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate + 1 / AvewageDCCCompwessionWate)) +
										dmw_min(((dmw_fwoat_t)p->WOBBuffewSizeInKByte * 1024 - p->CompbufWesewvedSpace64B * 64) * AvewageDCCCompwessionWate,
											((dmw_fwoat_t)p->ZewoSizeBuffewEntwies - p->CompbufWesewvedSpaceZs) * 64 / (AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate));

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: min 1 = %f\n", __func__, p->CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate);
		dmw_pwint("DMW::%s: min 2 = %f\n", __func__, p->MetaFIFOSizeInKEntwies * 1024 * 64 / (AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate + 1 / AvewageDCCCompwessionWate));
		dmw_pwint("DMW::%s: min 3 = %f\n", __func__, (p->WOBBuffewSizeInKByte * 1024 - p->CompbufWesewvedSpace64B * 64) * AvewageDCCCompwessionWate);
		dmw_pwint("DMW::%s: min 4 = %f\n", __func__, (p->ZewoSizeBuffewEntwies - p->CompbufWesewvedSpaceZs) * 64 / (AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate));
#endif
	} ewse {
		EffectiveCompwessedBuffewSize = dmw_min((dmw_fwoat_t)p->CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate,
												(dmw_fwoat_t)p->MetaFIFOSizeInKEntwies * 1024 * 64 * AvewageDCCCompwessionWate) +
												((dmw_fwoat_t)p->WOBBuffewSizeInKByte * 1024 - p->CompbufWesewvedSpace64B * 64) * AvewageDCCCompwessionWate;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: min 1 = %f\n", __func__, p->CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate);
		dmw_pwint("DMW::%s: min 2 = %f\n", __func__, p->MetaFIFOSizeInKEntwies * 1024 * 64 * AvewageDCCCompwessionWate);
#endif
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: MetaFIFOSizeInKEntwies = %u\n", __func__, p->MetaFIFOSizeInKEntwies);
	dmw_pwint("DMW::%s: AvewageZewoSizeCompwessionWate = %f\n", __func__, AvewageZewoSizeCompwessionWate);
	dmw_pwint("DMW::%s: EffectiveCompwessedBuffewSize = %f\n", __func__, EffectiveCompwessedBuffewSize);
#endif

	*p->StuttewPewiod = 0;

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
	if (p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) {
		WinesInDETY = ((dmw_fwoat_t)p->DETBuffewSizeY[k] + (p->UnboundedWequestEnabwed == twue ? EffectiveCompwessedBuffewSize : 0) * p->WeadBandwidthSuwfaceWuma[k] / p->TotawDataWeadBandwidth) / p->BytePewPixewDETY[k] / p->SwathWidthY[k];
		WinesInDETYWoundedDownToSwath = dmw_fwoow(WinesInDETY, p->SwathHeightY[k]);
		DETBuffewingTimeY = WinesInDETYWoundedDownToSwath * ((dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k]) / p->VWatio[k];
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, DETBuffewSizeY = %u\n", __func__, k, p->DETBuffewSizeY[k]);
		dmw_pwint("DMW::%s: k=%u, BytePewPixewDETY = %f\n", __func__, k, p->BytePewPixewDETY[k]);
		dmw_pwint("DMW::%s: k=%u, SwathWidthY = %u\n", __func__, k, p->SwathWidthY[k]);
		dmw_pwint("DMW::%s: k=%u, WeadBandwidthSuwfaceWuma = %f\n", __func__, k, p->WeadBandwidthSuwfaceWuma[k]);
		dmw_pwint("DMW::%s: k=%u, TotawDataWeadBandwidth = %f\n", __func__, k, p->TotawDataWeadBandwidth);
		dmw_pwint("DMW::%s: k=%u, WinesInDETY = %f\n", __func__, k, WinesInDETY);
		dmw_pwint("DMW::%s: k=%u, WinesInDETYWoundedDownToSwath = %f\n", __func__, k, WinesInDETYWoundedDownToSwath);
		dmw_pwint("DMW::%s: k=%u, HTotaw = %u\n", __func__, k, p->HTotaw[k]);
		dmw_pwint("DMW::%s: k=%u, PixewCwock = %f\n", __func__, k, p->PixewCwock[k]);
		dmw_pwint("DMW::%s: k=%u, VWatio = %f\n", __func__, k, p->VWatio[k]);
		dmw_pwint("DMW::%s: k=%u, DETBuffewingTimeY = %f\n", __func__, k, DETBuffewingTimeY);
		dmw_pwint("DMW::%s: k=%u,PixewCwock = %f\n", __func__, k, p->PixewCwock[k]);
#endif

		if (!FoundCwiticawSuwface || DETBuffewingTimeY < *p->StuttewPewiod) {
			dmw_boow_t isIntewwaceTiming = p->Intewwace[k] && !p->PwogwessiveToIntewwaceUnitInOPP;

			FoundCwiticawSuwface = twue;
			*p->StuttewPewiod = DETBuffewingTimeY;
			FwameTimeCwiticawSuwface = (isIntewwaceTiming ? dmw_fwoow((dmw_fwoat_t)p->VTotaw[k]/2.0, 1.0) : p->VTotaw[k]) * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k];
			VActiveTimeCwiticawSuwface = (isIntewwaceTiming ? dmw_fwoow((dmw_fwoat_t)p->VActive[k]/2.0, 1.0) : p->VActive[k]) * (dmw_fwoat_t)p->HTotaw[k] / p->PixewCwock[k];
			BytePewPixewYCwiticawSuwface = p->BytePewPixewY[k];
			SwathWidthYCwiticawSuwface = p->SwathWidthY[k];
			SwathHeightYCwiticawSuwface = p->SwathHeightY[k];
			BwockWidth256BytesYCwiticawSuwface = p->BwockWidth256BytesY[k];
			WinesToFinishSwathTwansfewStuttewCwiticawSuwface = p->SwathHeightY[k] - (WinesInDETY - WinesInDETYWoundedDownToSwath);
			DETBuffewSizeYCwiticawSuwface = p->DETBuffewSizeY[k];
			MinTTUVBwankCwiticawSuwface = p->MinTTUVBwank[k];
			SingwePwaneCwiticawSuwface = (p->WeadBandwidthSuwfaceChwoma[k] == 0);
			SingwePipeCwiticawSuwface = (p->DPPPewSuwface[k] == 1);

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u, FoundCwiticawSuwface = %u\n", __func__, k, FoundCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, StuttewPewiod = %f\n", __func__, k, *p->StuttewPewiod);
			dmw_pwint("DMW::%s: k=%u, MinTTUVBwankCwiticawSuwface = %f\n", __func__, k, MinTTUVBwankCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, FwameTimeCwiticawSuwface = %f\n", __func__, k, FwameTimeCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, VActiveTimeCwiticawSuwface = %f\n", __func__, k, VActiveTimeCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, BytePewPixewYCwiticawSuwface = %u\n", __func__, k, BytePewPixewYCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, SwathWidthYCwiticawSuwface = %f\n", __func__, k, SwathWidthYCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, SwathHeightYCwiticawSuwface = %f\n", __func__, k, SwathHeightYCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, BwockWidth256BytesYCwiticawSuwface = %u\n", __func__, k, BwockWidth256BytesYCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, SingwePwaneCwiticawSuwface = %u\n", __func__, k, SingwePwaneCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, SingwePipeCwiticawSuwface = %u\n", __func__, k, SingwePipeCwiticawSuwface);
			dmw_pwint("DMW::%s: k=%u, WinesToFinishSwathTwansfewStuttewCwiticawSuwface = %f\n", __func__, k, WinesToFinishSwathTwansfewStuttewCwiticawSuwface);
#endif
		}
	}
	}

	PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew = dmw_min(*p->StuttewPewiod * p->TotawDataWeadBandwidth, EffectiveCompwessedBuffewSize);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WOBBuffewSizeInKByte = %u\n", __func__, p->WOBBuffewSizeInKByte);
	dmw_pwint("DMW::%s: AvewageDCCCompwessionWate = %f\n", __func__, AvewageDCCCompwessionWate);
	dmw_pwint("DMW::%s: StuttewPewiod * TotawDataWeadBandwidth = %f\n", __func__, *p->StuttewPewiod * p->TotawDataWeadBandwidth);
	dmw_pwint("DMW::%s: WOBBuffewSizeInKByte * 1024 * AvewageDCCCompwessionWate + EffectiveCompwessedBuffewSize = %f\n", __func__, p->WOBBuffewSizeInKByte * 1024 * AvewageDCCCompwessionWate + EffectiveCompwessedBuffewSize);
	dmw_pwint("DMW::%s: EffectiveCompwessedBuffewSize = %f\n", __func__, EffectiveCompwessedBuffewSize);
	dmw_pwint("DMW::%s: PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew = %f\n", __func__, PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew);
	dmw_pwint("DMW::%s: WetuwnBW = %f\n", __func__, p->WetuwnBW);
	dmw_pwint("DMW::%s: TotawDataWeadBandwidth = %f\n", __func__, p->TotawDataWeadBandwidth);
	dmw_pwint("DMW::%s: TotawWowWeadBandwidth = %f\n", __func__, TotawWowWeadBandwidth);
	dmw_pwint("DMW::%s: DCFCWK = %f\n", __func__, p->DCFCWK);
#endif

	StuttewBuwstTime = PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew / AvewageDCCCompwessionWate / p->WetuwnBW + (*p->StuttewPewiod * p->TotawDataWeadBandwidth - PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew) / (p->DCFCWK * 64) + *p->StuttewPewiod * TotawWowWeadBandwidth / p->WetuwnBW;
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: Pawt 1 = %f\n", __func__, PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew / AvewageDCCCompwessionWate / p->WetuwnBW);
	dmw_pwint("DMW::%s: StuttewPewiod * TotawDataWeadBandwidth = %f\n", __func__, (*p->StuttewPewiod * p->TotawDataWeadBandwidth));
	dmw_pwint("DMW::%s: Pawt 2 = %f\n", __func__, (*p->StuttewPewiod * p->TotawDataWeadBandwidth - PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew) / (p->DCFCWK * 64));
	dmw_pwint("DMW::%s: Pawt 3 = %f\n", __func__, *p->StuttewPewiod * TotawWowWeadBandwidth / p->WetuwnBW);
	dmw_pwint("DMW::%s: StuttewBuwstTime = %f\n", __func__, StuttewBuwstTime);
#endif
	StuttewBuwstTime = dmw_max(StuttewBuwstTime, WinesToFinishSwathTwansfewStuttewCwiticawSuwface * BytePewPixewYCwiticawSuwface * SwathWidthYCwiticawSuwface / p->WetuwnBW);

	dmw_pwint("DMW::%s: Time to finish wesidue swath=%f\n", __func__, WinesToFinishSwathTwansfewStuttewCwiticawSuwface * BytePewPixewYCwiticawSuwface * SwathWidthYCwiticawSuwface / p->WetuwnBW);

	TotawActiveWwiteback = 0;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (p->WwitebackEnabwe[k]) {
			TotawActiveWwiteback = TotawActiveWwiteback + 1;
		}
	}

	if (TotawActiveWwiteback == 0) {
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: SWExitTime = %f\n", __func__, p->SWExitTime);
		dmw_pwint("DMW::%s: SWExitZ8Time = %f\n", __func__, p->SWExitZ8Time);
		dmw_pwint("DMW::%s: StuttewBuwstTime = %f (finaw)\n", __func__, StuttewBuwstTime);
		dmw_pwint("DMW::%s: StuttewPewiod = %f\n", __func__, *p->StuttewPewiod);
#endif
		*p->StuttewEfficiencyNotIncwudingVBwank = dmw_max(0., 1 - (p->SWExitTime + StuttewBuwstTime) / *p->StuttewPewiod) * 100;
		*p->Z8StuttewEfficiencyNotIncwudingVBwank = dmw_max(0., 1 - (p->SWExitZ8Time + StuttewBuwstTime) / *p->StuttewPewiod) * 100;
		*p->NumbewOfStuttewBuwstsPewFwame = (*p->StuttewEfficiencyNotIncwudingVBwank > 0 ? (dmw_uint_t)(dmw_ceiw(VActiveTimeCwiticawSuwface / *p->StuttewPewiod, 1)) : 0);
		*p->Z8NumbewOfStuttewBuwstsPewFwame = (*p->Z8StuttewEfficiencyNotIncwudingVBwank > 0 ? (dmw_uint_t)(dmw_ceiw(VActiveTimeCwiticawSuwface / *p->StuttewPewiod, 1)) : 0);
	} ewse {
		*p->StuttewEfficiencyNotIncwudingVBwank = 0.;
		*p->Z8StuttewEfficiencyNotIncwudingVBwank = 0.;
		*p->NumbewOfStuttewBuwstsPewFwame = 0;
		*p->Z8NumbewOfStuttewBuwstsPewFwame = 0;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VActiveTimeCwiticawSuwface = %f\n", __func__, VActiveTimeCwiticawSuwface);
	dmw_pwint("DMW::%s: StuttewEfficiencyNotIncwudingVBwank = %f\n", __func__, *p->StuttewEfficiencyNotIncwudingVBwank);
	dmw_pwint("DMW::%s: Z8StuttewEfficiencyNotIncwudingVBwank = %f\n", __func__, *p->Z8StuttewEfficiencyNotIncwudingVBwank);
	dmw_pwint("DMW::%s: NumbewOfStuttewBuwstsPewFwame = %u\n", __func__, *p->NumbewOfStuttewBuwstsPewFwame);
	dmw_pwint("DMW::%s: Z8NumbewOfStuttewBuwstsPewFwame = %u\n", __func__, *p->Z8NumbewOfStuttewBuwstsPewFwame);
#endif

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (p->UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) {
			if (p->BwendingAndTiming[k] == k) {
				if (TotawNumbewOfActiveOTG == 0) {
					SingwePixewCwock = p->PixewCwock[k];
					SingweHTotaw = p->HTotaw[k];
					SingweVTotaw = p->VTotaw[k];
				} ewse if (SingwePixewCwock != p->PixewCwock[k] || SingweHTotaw != p->HTotaw[k] || SingweVTotaw != p->VTotaw[k]) {
					SameTiming = fawse;
				}
				TotawNumbewOfActiveOTG = TotawNumbewOfActiveOTG + 1;
			}
		}
	}

	if (*p->StuttewEfficiencyNotIncwudingVBwank > 0) {
		WastStuttewPewiod = VActiveTimeCwiticawSuwface - (*p->NumbewOfStuttewBuwstsPewFwame - 1) * *p->StuttewPewiod;

		if ((p->SynchwonizeTimingsFinaw || TotawNumbewOfActiveOTG == 1) && SameTiming &&
			WastStuttewPewiod + MinTTUVBwankCwiticawSuwface > p->StuttewEntewPwusExitWatewmawk) {
			*p->StuttewEfficiency = (1 - (*p->NumbewOfStuttewBuwstsPewFwame * p->SWExitTime + StuttewBuwstTime * VActiveTimeCwiticawSuwface / *p->StuttewPewiod) / FwameTimeCwiticawSuwface) * 100;
		} ewse {
			*p->StuttewEfficiency = *p->StuttewEfficiencyNotIncwudingVBwank;
		}
	} ewse {
		*p->StuttewEfficiency = 0;
	}

	if (*p->Z8StuttewEfficiencyNotIncwudingVBwank > 0) {
		WastZ8StuttewPewiod = VActiveTimeCwiticawSuwface - (*p->NumbewOfStuttewBuwstsPewFwame - 1) * *p->StuttewPewiod;
		if ((p->SynchwonizeTimingsFinaw || TotawNumbewOfActiveOTG == 1) && SameTiming && WastZ8StuttewPewiod + MinTTUVBwankCwiticawSuwface > p->Z8StuttewEntewPwusExitWatewmawk) {
			*p->Z8StuttewEfficiency = (1 - (*p->NumbewOfStuttewBuwstsPewFwame * p->SWExitZ8Time + StuttewBuwstTime * VActiveTimeCwiticawSuwface / *p->StuttewPewiod) / FwameTimeCwiticawSuwface) * 100;
		} ewse {
			*p->Z8StuttewEfficiency = *p->Z8StuttewEfficiencyNotIncwudingVBwank;
		}
	} ewse {
		*p->Z8StuttewEfficiency = 0.;
	}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: WastZ8StuttewPewiod = %f\n", __func__, WastZ8StuttewPewiod);
		dmw_pwint("DMW::%s: Z8StuttewEntewPwusExitWatewmawk = %f\n", __func__, p->Z8StuttewEntewPwusExitWatewmawk);
		dmw_pwint("DMW::%s: StuttewBuwstTime = %f\n", __func__, StuttewBuwstTime);
		dmw_pwint("DMW::%s: StuttewPewiod = %f\n", __func__, *p->StuttewPewiod);
		dmw_pwint("DMW::%s: StuttewEfficiency = %f\n", __func__, *p->StuttewEfficiency);
		dmw_pwint("DMW::%s: Z8StuttewEfficiency = %f\n", __func__, *p->Z8StuttewEfficiency);
		dmw_pwint("DMW::%s: StuttewEfficiencyNotIncwudingVBwank = %f\n", __func__, *p->StuttewEfficiencyNotIncwudingVBwank);
		dmw_pwint("DMW::%s: Z8NumbewOfStuttewBuwstsPewFwame = %u\n", __func__, *p->Z8NumbewOfStuttewBuwstsPewFwame);
#endif

		SwathSizeCwiticawSuwface = (dmw_uint_t)(BytePewPixewYCwiticawSuwface * SwathHeightYCwiticawSuwface * dmw_ceiw(SwathWidthYCwiticawSuwface, BwockWidth256BytesYCwiticawSuwface));
		WastChunkOfSwathSize = SwathSizeCwiticawSuwface % (p->PixewChunkSizeInKByte * 1024);
		MissingPawtOfWastSwathOfDETSize = (dmw_uint_t)(dmw_ceiw(DETBuffewSizeYCwiticawSuwface, SwathSizeCwiticawSuwface) - DETBuffewSizeYCwiticawSuwface);

		*p->DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE = !(!p->UnboundedWequestEnabwed && (p->NumbewOfActiveSuwfaces == 1) && SingwePwaneCwiticawSuwface && SingwePipeCwiticawSuwface && (WastChunkOfSwathSize > 0) &&
			(WastChunkOfSwathSize <= 4096) && (MissingPawtOfWastSwathOfDETSize > 0) && (MissingPawtOfWastSwathOfDETSize <= WastChunkOfSwathSize));

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: SwathSizeCwiticawSuwface = %u\n", __func__, SwathSizeCwiticawSuwface);
	dmw_pwint("DMW::%s: DETBuffewSizeYCwiticawSuwface = %u\n", __func__, DETBuffewSizeYCwiticawSuwface);
	dmw_pwint("DMW::%s: PixewChunkSizeInKByte = %u\n", __func__, p->PixewChunkSizeInKByte);
	dmw_pwint("DMW::%s: WastChunkOfSwathSize = %u\n", __func__, WastChunkOfSwathSize);
	dmw_pwint("DMW::%s: MissingPawtOfWastSwathOfDETSize = %u\n", __func__, MissingPawtOfWastSwathOfDETSize);
	dmw_pwint("DMW::%s: DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE = %u\n", __func__, *p->DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE);
#endif
} // CawcuwateStuttewEfficiency

/// \CawcuwateSwathAndDETConfiguwation
/// @bwief Cawcuwates swath width and diffewent wetuwn buffews sizing (DET, CDB, etc.)
static void CawcuwateSwathAndDETConfiguwation(stwuct dispway_mode_wib_scwatch_st *scwatch,
	stwuct CawcuwateSwathAndDETConfiguwation_pawams_st *p)
{
	dmw_uint_t MaximumSwathHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t MaximumSwathHeightC[__DMW_NUM_PWANES__];
	dmw_uint_t WoundedUpMaxSwathSizeBytesY[__DMW_NUM_PWANES__];
	dmw_uint_t WoundedUpMaxSwathSizeBytesC[__DMW_NUM_PWANES__];
	dmw_uint_t WoundedUpSwathSizeBytesY[__DMW_NUM_PWANES__];
	dmw_uint_t WoundedUpSwathSizeBytesC[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthSingweDPP[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthSingweDPPChwoma[__DMW_NUM_PWANES__];

	dmw_uint_t TotawActiveDPP = 0;
	dmw_boow_t NoChwomaOwWineawSuwfaces = twue;
	dmw_uint_t SuwfaceDoingUnboundedWequest = 0;

	dmw_uint_t DETBuffewSizeInKByteFowSwathCawcuwation;

	const wong TTUFIFODEPTH = 8;
	const wong MAXIMUMCOMPWESSION = 4;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: FowceSingweDPP = %u\n", __func__, p->FowceSingweDPP);
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		dmw_pwint("DMW::%s: DPPPewSuwface[%u] = %u\n", __func__, k, p->DPPPewSuwface[k]);
	}
#endif
	CawcuwateSwathWidth(p->FowceSingweDPP,
		p->NumbewOfActiveSuwfaces,
		p->SouwcePixewFowmat,
		p->SouwceScan,
		p->ViewpowtStationawy,
		p->ViewpowtWidth,
		p->ViewpowtHeight,
		p->ViewpowtXStawt,
		p->ViewpowtYStawt,
		p->ViewpowtXStawtC,
		p->ViewpowtYStawtC,
		p->SuwfaceWidthY,
		p->SuwfaceWidthC,
		p->SuwfaceHeightY,
		p->SuwfaceHeightC,
		p->ODMMode,
		p->BytePewPixY,
		p->BytePewPixC,
		p->Wead256BytesBwockHeightY,
		p->Wead256BytesBwockHeightC,
		p->Wead256BytesBwockWidthY,
		p->Wead256BytesBwockWidthC,
		p->BwendingAndTiming,
		p->HActive,
		p->HWatio,
		p->DPPPewSuwface,

		// Output
		SwathWidthSingweDPP,
		SwathWidthSingweDPPChwoma,
		p->SwathWidth,
		p->SwathWidthChwoma,
		MaximumSwathHeightY,
		MaximumSwathHeightC,
		p->swath_width_wuma_ub,
		p->swath_width_chwoma_ub);

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		WoundedUpMaxSwathSizeBytesY[k] = (dmw_uint_t)(p->swath_width_wuma_ub[k] * p->BytePewPixDETY[k] * MaximumSwathHeightY[k]);
		WoundedUpMaxSwathSizeBytesC[k] = (dmw_uint_t)(p->swath_width_chwoma_ub[k] * p->BytePewPixDETC[k] * MaximumSwathHeightC[k]);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u DPPPewSuwface = %u\n", __func__, k, p->DPPPewSuwface[k]);
		dmw_pwint("DMW::%s: k=%u swath_width_wuma_ub = %u\n", __func__, k, p->swath_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%u BytePewPixDETY = %f\n", __func__, k, p->BytePewPixDETY[k]);
		dmw_pwint("DMW::%s: k=%u MaximumSwathHeightY = %u\n", __func__, k, MaximumSwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%u WoundedUpMaxSwathSizeBytesY = %u\n", __func__, k, WoundedUpMaxSwathSizeBytesY[k]);
		dmw_pwint("DMW::%s: k=%u swath_width_chwoma_ub = %u\n", __func__, k, p->swath_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%u BytePewPixDETC = %f\n", __func__, k, p->BytePewPixDETC[k]);
		dmw_pwint("DMW::%s: k=%u MaximumSwathHeightC = %u\n", __func__, k, MaximumSwathHeightC[k]);
		dmw_pwint("DMW::%s: k=%u WoundedUpMaxSwathSizeBytesC = %u\n", __func__, k, WoundedUpMaxSwathSizeBytesC[k]);
#endif
		if (p->SouwcePixewFowmat[k] == dmw_420_10) {
			WoundedUpMaxSwathSizeBytesY[k] = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) WoundedUpMaxSwathSizeBytesY[k], 256));
			WoundedUpMaxSwathSizeBytesC[k] = (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) WoundedUpMaxSwathSizeBytesC[k], 256));
		}
	}

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		TotawActiveDPP = TotawActiveDPP + (p->FowceSingweDPP ? 1 : p->DPPPewSuwface[k]);
		if (p->DPPPewSuwface[k] > 0)
			SuwfaceDoingUnboundedWequest = k;
		if (p->SouwcePixewFowmat[k] == dmw_420_8 || p->SouwcePixewFowmat[k] == dmw_420_10 ||
				p->SouwcePixewFowmat[k] == dmw_420_12 || p->SouwcePixewFowmat[k] == dmw_wgbe_awpha
				|| p->SuwfaceTiwing[k] == dmw_sw_wineaw) {
			NoChwomaOwWineawSuwfaces = fawse;
		}
	}

	*p->UnboundedWequestEnabwed = UnboundedWequest(p->UseUnboundedWequestingFinaw, TotawActiveDPP,
			NoChwomaOwWineawSuwfaces, p->Output[0]);

	CawcuwateDETBuffewSize(p->DETSizeOvewwide,
		p->UseMAWWFowPStateChange,
		p->FowceSingweDPP,
		p->NumbewOfActiveSuwfaces,
		*p->UnboundedWequestEnabwed,
		p->nomDETInKByte,
		p->MaxTotawDETInKByte,
		p->ConfigWetuwnBuffewSizeInKByte,
		p->MinCompwessedBuffewSizeInKByte,
		p->ConfigWetuwnBuffewSegmentSizeInkByte,
		p->CompwessedBuffewSegmentSizeInkByteFinaw,
		p->SouwcePixewFowmat,
		p->WeadBandwidthWuma,
		p->WeadBandwidthChwoma,
		WoundedUpMaxSwathSizeBytesY,
		WoundedUpMaxSwathSizeBytesC,
		p->DPPPewSuwface,

		// Output
		p->DETBuffewSizeInKByte, // pew hubp pipe
		p->CompwessedBuffewSizeInkByte);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: TotawActiveDPP = %u\n", __func__, TotawActiveDPP);
		dmw_pwint("DMW::%s: nomDETInKByte = %u\n", __func__, p->nomDETInKByte);
		dmw_pwint("DMW::%s: ConfigWetuwnBuffewSizeInKByte = %u\n", __func__, p->ConfigWetuwnBuffewSizeInKByte);
		dmw_pwint("DMW::%s: UseUnboundedWequestingFinaw = %u\n", __func__, p->UseUnboundedWequestingFinaw);
		dmw_pwint("DMW::%s: UnboundedWequestEnabwed = %u\n", __func__, *p->UnboundedWequestEnabwed);
		dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte = %u\n", __func__, *p->CompwessedBuffewSizeInkByte);
#endif

	*p->ViewpowtSizeSuppowt = twue;
	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {

		DETBuffewSizeInKByteFowSwathCawcuwation =  (p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe ? 1024 : p->DETBuffewSizeInKByte[k]);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: k=%u DETBuffewSizeInKByteFowSwathCawcuwation = %u\n", __func__, k, DETBuffewSizeInKByteFowSwathCawcuwation);
#endif

		if (WoundedUpMaxSwathSizeBytesY[k] + WoundedUpMaxSwathSizeBytesC[k] <= DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) {
			p->SwathHeightY[k] = MaximumSwathHeightY[k];
			p->SwathHeightC[k] = MaximumSwathHeightC[k];
			WoundedUpSwathSizeBytesY[k] = WoundedUpMaxSwathSizeBytesY[k];
			WoundedUpSwathSizeBytesC[k] = WoundedUpMaxSwathSizeBytesC[k];
		} ewse if (WoundedUpMaxSwathSizeBytesY[k] >= 1.5 * WoundedUpMaxSwathSizeBytesC[k] && WoundedUpMaxSwathSizeBytesY[k] / 2 + WoundedUpMaxSwathSizeBytesC[k] <= DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) {
			p->SwathHeightY[k] = MaximumSwathHeightY[k] / 2;
			p->SwathHeightC[k] = MaximumSwathHeightC[k];
			WoundedUpSwathSizeBytesY[k] = WoundedUpMaxSwathSizeBytesY[k] / 2;
			WoundedUpSwathSizeBytesC[k] = WoundedUpMaxSwathSizeBytesC[k];
		} ewse if (WoundedUpMaxSwathSizeBytesY[k] < 1.5 * WoundedUpMaxSwathSizeBytesC[k] && WoundedUpMaxSwathSizeBytesY[k] + WoundedUpMaxSwathSizeBytesC[k] / 2 <= DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) {
			p->SwathHeightY[k] = MaximumSwathHeightY[k];
			p->SwathHeightC[k] = MaximumSwathHeightC[k] / 2;
			WoundedUpSwathSizeBytesY[k] = WoundedUpMaxSwathSizeBytesY[k];
			WoundedUpSwathSizeBytesC[k] = WoundedUpMaxSwathSizeBytesC[k] / 2;
		} ewse {
			p->SwathHeightY[k] = MaximumSwathHeightY[k] / 2;
			p->SwathHeightC[k] = MaximumSwathHeightC[k] / 2;
			WoundedUpSwathSizeBytesY[k] = WoundedUpMaxSwathSizeBytesY[k] / 2;
			WoundedUpSwathSizeBytesC[k] = WoundedUpMaxSwathSizeBytesC[k] / 2;
		}

		if ((WoundedUpMaxSwathSizeBytesY[k] / 2 + WoundedUpMaxSwathSizeBytesC[k] / 2 > DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) ||
			p->SwathWidth[k] > p->MaximumSwathWidthWuma[k] || (p->SwathHeightC[k] > 0 && p->SwathWidthChwoma[k] > p->MaximumSwathWidthChwoma[k])) {
			*p->ViewpowtSizeSuppowt = fawse;
			p->ViewpowtSizeSuppowtPewSuwface[k] = fawse;
		} ewse {
			p->ViewpowtSizeSuppowtPewSuwface[k] = twue;
		}

	if (p->SwathHeightC[k] == 0) {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u Aww DET fow pwane0\n", __func__, k);
#endif
			p->DETBuffewSizeY[k] = p->DETBuffewSizeInKByte[k] * 1024;
			p->DETBuffewSizeC[k] = 0;
		} ewse if (WoundedUpSwathSizeBytesY[k] <= 1.5 * WoundedUpSwathSizeBytesC[k]) {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u Hawf DET fow pwane0, hawf fow pwane1\n", __func__, k);
#endif
			p->DETBuffewSizeY[k] = p->DETBuffewSizeInKByte[k] * 1024 / 2;
			p->DETBuffewSizeC[k] = p->DETBuffewSizeInKByte[k] * 1024 / 2;
		} ewse {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u 2/3 DET fow pwane0, 1/3 fow pwane1\n", __func__, k);
#endif
			p->DETBuffewSizeY[k] = (dmw_uint_t)(dmw_fwoow(p->DETBuffewSizeInKByte[k] * 1024 * 2 / 3, 1024));
			p->DETBuffewSizeC[k] = p->DETBuffewSizeInKByte[k] * 1024 - p->DETBuffewSizeY[k];
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u SwathHeightY = %u\n", __func__, k, p->SwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%u SwathHeightC = %u\n", __func__, k, p->SwathHeightC[k]);
		dmw_pwint("DMW::%s: k=%u WoundedUpMaxSwathSizeBytesY = %u\n", __func__, k, WoundedUpMaxSwathSizeBytesY[k]);
		dmw_pwint("DMW::%s: k=%u WoundedUpMaxSwathSizeBytesC = %u\n", __func__, k, WoundedUpMaxSwathSizeBytesC[k]);
		dmw_pwint("DMW::%s: k=%u WoundedUpSwathSizeBytesY = %u\n", __func__, k, WoundedUpSwathSizeBytesY[k]);
		dmw_pwint("DMW::%s: k=%u WoundedUpSwathSizeBytesC = %u\n", __func__, k, WoundedUpSwathSizeBytesC[k]);
		dmw_pwint("DMW::%s: k=%u DETBuffewSizeInKByte = %u\n", __func__, k, p->DETBuffewSizeInKByte[k]);
		dmw_pwint("DMW::%s: k=%u DETBuffewSizeY = %u\n", __func__, k, p->DETBuffewSizeY[k]);
		dmw_pwint("DMW::%s: k=%u DETBuffewSizeC = %u\n", __func__, k, p->DETBuffewSizeC[k]);
		dmw_pwint("DMW::%s: k=%u ViewpowtSizeSuppowtPewSuwface = %u\n", __func__, k, p->ViewpowtSizeSuppowtPewSuwface[k]);
#endif

	}

	*p->compbuf_wesewved_space_64b = 2 * p->PixewChunkSizeInKByte * 1024 / 64;
	if (p->UnboundedWequestEnabwed) {
		*p->compbuf_wesewved_space_64b = dmw_max(*p->compbuf_wesewved_space_64b,
				(dmw_fwoat_t)(p->WOBBuffewSizeInKByte * 1024/64)
				- (dmw_fwoat_t)(WoundedUpSwathSizeBytesY[SuwfaceDoingUnboundedWequest] * TTUFIFODEPTH / MAXIMUMCOMPWESSION/64));
	}
	*p->compbuf_wesewved_space_zs = 2 * p->PixewChunkSizeInKByte * 1024 / 256;
} // CawcuwateSwathAndDETConfiguwation

static void CawcuwateSwathWidth(
		dmw_boow_t FowceSingweDPP,
		dmw_uint_t NumbewOfActiveSuwfaces,
		enum dmw_souwce_fowmat_cwass SouwcePixewFowmat[],
		enum dmw_wotation_angwe SouwceScan[],
		dmw_boow_t ViewpowtStationawy[],
		dmw_uint_t ViewpowtWidth[],
		dmw_uint_t ViewpowtHeight[],
		dmw_uint_t ViewpowtXStawt[],
		dmw_uint_t ViewpowtYStawt[],
		dmw_uint_t ViewpowtXStawtC[],
		dmw_uint_t ViewpowtYStawtC[],
		dmw_uint_t SuwfaceWidthY[],
		dmw_uint_t SuwfaceWidthC[],
		dmw_uint_t SuwfaceHeightY[],
		dmw_uint_t SuwfaceHeightC[],
		enum dmw_odm_mode ODMMode[],
		dmw_uint_t BytePewPixY[],
		dmw_uint_t BytePewPixC[],
		dmw_uint_t Wead256BytesBwockHeightY[],
		dmw_uint_t Wead256BytesBwockHeightC[],
		dmw_uint_t Wead256BytesBwockWidthY[],
		dmw_uint_t Wead256BytesBwockWidthC[],
		dmw_uint_t BwendingAndTiming[],
		dmw_uint_t HActive[],
		dmw_fwoat_t HWatio[],
		dmw_uint_t DPPPewSuwface[],

		// Output
		dmw_uint_t SwathWidthSingweDPPY[],
		dmw_uint_t SwathWidthSingweDPPC[],
		dmw_uint_t SwathWidthY[], // pew-pipe
		dmw_uint_t SwathWidthC[], // pew-pipe
		dmw_uint_t MaximumSwathHeightY[],
		dmw_uint_t MaximumSwathHeightC[],
		dmw_uint_t swath_width_wuma_ub[], // pew-pipe
		dmw_uint_t swath_width_chwoma_ub[]) // pew-pipe
{
	enum dmw_odm_mode   MainSuwfaceODMMode;
	dmw_uint_t suwface_width_ub_w;
	dmw_uint_t suwface_height_ub_w;
	dmw_uint_t suwface_width_ub_c = 0;
	dmw_uint_t suwface_height_ub_c = 0;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: FowceSingweDPP = %u\n", __func__, FowceSingweDPP);
	dmw_pwint("DMW::%s: NumbewOfActiveSuwfaces = %u\n", __func__, NumbewOfActiveSuwfaces);
#endif

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
			SwathWidthSingweDPPY[k] = ViewpowtWidth[k];
		} ewse {
			SwathWidthSingweDPPY[k] = ViewpowtHeight[k];
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u ViewpowtWidth=%u\n", __func__, k, ViewpowtWidth[k]);
		dmw_pwint("DMW::%s: k=%u ViewpowtHeight=%u\n", __func__, k, ViewpowtHeight[k]);
		dmw_pwint("DMW::%s: k=%u DPPPewSuwface=%u\n", __func__, k, DPPPewSuwface[k]);
#endif

		MainSuwfaceODMMode = ODMMode[k];
		fow (dmw_uint_t j = 0; j < NumbewOfActiveSuwfaces; ++j) {
			if (BwendingAndTiming[k] == j) {
				MainSuwfaceODMMode = ODMMode[j];
			}
		}

		if (FowceSingweDPP) {
			SwathWidthY[k] = SwathWidthSingweDPPY[k];
		} ewse {
			if (MainSuwfaceODMMode == dmw_odm_mode_combine_4to1) {
				SwathWidthY[k] = (dmw_uint_t)(dmw_min(SwathWidthSingweDPPY[k], dmw_wound(HActive[k] / 4.0 * HWatio[k], twue)));
			} ewse if (MainSuwfaceODMMode == dmw_odm_mode_combine_2to1) {
				SwathWidthY[k] = (dmw_uint_t)(dmw_min(SwathWidthSingweDPPY[k], dmw_wound(HActive[k] / 2.0 * HWatio[k], twue)));
			} ewse if (DPPPewSuwface[k] == 2) {
				SwathWidthY[k] = SwathWidthSingweDPPY[k] / 2;
			} ewse {
				SwathWidthY[k] = SwathWidthSingweDPPY[k];
			}
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u HActive=%u\n", __func__, k, HActive[k]);
		dmw_pwint("DMW::%s: k=%u HWatio=%f\n", __func__, k, HWatio[k]);
		dmw_pwint("DMW::%s: k=%u MainSuwfaceODMMode=%u\n", __func__, k, MainSuwfaceODMMode);
		dmw_pwint("DMW::%s: k=%u SwathWidthSingweDPPY=%u\n", __func__, k, SwathWidthSingweDPPY[k]);
		dmw_pwint("DMW::%s: k=%u SwathWidthY=%u\n", __func__, k, SwathWidthY[k]);
#endif

		if (SouwcePixewFowmat[k] == dmw_420_8 || SouwcePixewFowmat[k] == dmw_420_10 || SouwcePixewFowmat[k] == dmw_420_12) {
			SwathWidthC[k] = SwathWidthY[k] / 2;
			SwathWidthSingweDPPC[k] = SwathWidthSingweDPPY[k] / 2;
		} ewse {
			SwathWidthC[k] = SwathWidthY[k];
			SwathWidthSingweDPPC[k] = SwathWidthSingweDPPY[k];
		}

		if (FowceSingweDPP == twue) {
			SwathWidthY[k] = SwathWidthSingweDPPY[k];
			SwathWidthC[k] = SwathWidthSingweDPPC[k];
		}

		suwface_width_ub_w = (dmw_uint_t)dmw_ceiw(SuwfaceWidthY[k], Wead256BytesBwockWidthY[k]);
		suwface_height_ub_w = (dmw_uint_t)dmw_ceiw(SuwfaceHeightY[k], Wead256BytesBwockHeightY[k]);

		if (!dmw_is_vewticaw_wotation(SouwceScan[k])) {
			MaximumSwathHeightY[k] = Wead256BytesBwockHeightY[k];
			MaximumSwathHeightC[k] = Wead256BytesBwockHeightC[k];
			if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
				swath_width_wuma_ub[k] = (dmw_uint_t)(dmw_min(suwface_width_ub_w, dmw_fwoow(ViewpowtXStawt[k] + SwathWidthY[k] + Wead256BytesBwockWidthY[k] - 1, Wead256BytesBwockWidthY[k]) - dmw_fwoow(ViewpowtXStawt[k], Wead256BytesBwockWidthY[k])));
			} ewse {
				swath_width_wuma_ub[k] = (dmw_uint_t)(dmw_min(suwface_width_ub_w, dmw_ceiw(SwathWidthY[k] - 1, Wead256BytesBwockWidthY[k]) + Wead256BytesBwockWidthY[k]));
			}
			if (BytePewPixC[k] > 0) {
				suwface_width_ub_c = (dmw_uint_t)dmw_ceiw(SuwfaceWidthC[k], Wead256BytesBwockWidthC[k]);
				if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
					swath_width_chwoma_ub[k] = (dmw_uint_t)(dmw_min(suwface_width_ub_c, dmw_fwoow(ViewpowtXStawtC[k] + SwathWidthC[k] + Wead256BytesBwockWidthC[k] - 1, Wead256BytesBwockWidthC[k]) - dmw_fwoow(ViewpowtXStawtC[k], Wead256BytesBwockWidthC[k])));
				} ewse {
					swath_width_chwoma_ub[k] = (dmw_uint_t)(dmw_min(suwface_width_ub_c, dmw_ceiw(SwathWidthC[k] - 1, Wead256BytesBwockWidthC[k]) + Wead256BytesBwockWidthC[k]));
				}
			} ewse {
				swath_width_chwoma_ub[k] = 0;
			}
		} ewse {
			MaximumSwathHeightY[k] = Wead256BytesBwockWidthY[k];
			MaximumSwathHeightC[k] = Wead256BytesBwockWidthC[k];

			if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
				swath_width_wuma_ub[k] = (dmw_uint_t)(dmw_min(suwface_height_ub_w, dmw_fwoow(ViewpowtYStawt[k] + SwathWidthY[k] + Wead256BytesBwockHeightY[k] - 1, Wead256BytesBwockHeightY[k]) - dmw_fwoow(ViewpowtYStawt[k], Wead256BytesBwockHeightY[k])));
			} ewse {
				swath_width_wuma_ub[k] = (dmw_uint_t)(dmw_min(suwface_height_ub_w, dmw_ceiw(SwathWidthY[k] - 1, Wead256BytesBwockHeightY[k]) + Wead256BytesBwockHeightY[k]));
			}
			if (BytePewPixC[k] > 0) {
				suwface_height_ub_c = (dmw_uint_t)dmw_ceiw(SuwfaceHeightC[k], Wead256BytesBwockHeightC[k]);
				if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
					swath_width_chwoma_ub[k] = (dmw_uint_t)(dmw_min(suwface_height_ub_c, dmw_fwoow(ViewpowtYStawtC[k] + SwathWidthC[k] + Wead256BytesBwockHeightC[k] - 1, Wead256BytesBwockHeightC[k]) - dmw_fwoow(ViewpowtYStawtC[k], Wead256BytesBwockHeightC[k])));
				} ewse {
					swath_width_chwoma_ub[k] = (dmw_uint_t)(dmw_min(suwface_height_ub_c, dmw_ceiw(SwathWidthC[k] - 1, Wead256BytesBwockHeightC[k]) + Wead256BytesBwockHeightC[k]));
				}
			} ewse {
				swath_width_chwoma_ub[k] = 0;
			}
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u suwface_width_ub_w=%u\n", __func__, k, suwface_width_ub_w);
		dmw_pwint("DMW::%s: k=%u suwface_height_ub_w=%u\n", __func__, k, suwface_height_ub_w);
		dmw_pwint("DMW::%s: k=%u suwface_width_ub_c=%u\n", __func__, k, suwface_width_ub_c);
		dmw_pwint("DMW::%s: k=%u suwface_height_ub_c=%u\n", __func__, k, suwface_height_ub_c);
		dmw_pwint("DMW::%s: k=%u Wead256BytesBwockWidthY=%u\n", __func__, k, Wead256BytesBwockWidthY[k]);
		dmw_pwint("DMW::%s: k=%u Wead256BytesBwockHeightY=%u\n", __func__, k, Wead256BytesBwockHeightY[k]);
		dmw_pwint("DMW::%s: k=%u Wead256BytesBwockWidthC=%u\n", __func__, k, Wead256BytesBwockWidthC[k]);
		dmw_pwint("DMW::%s: k=%u Wead256BytesBwockHeightC=%u\n", __func__, k, Wead256BytesBwockHeightC[k]);
		dmw_pwint("DMW::%s: k=%u ViewpowtStationawy=%u\n", __func__, k, ViewpowtStationawy[k]);
		dmw_pwint("DMW::%s: k=%u DPPPewSuwface=%u\n", __func__, k, DPPPewSuwface[k]);
		dmw_pwint("DMW::%s: k=%u swath_width_wuma_ub=%u\n", __func__, k, swath_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%u swath_width_chwoma_ub=%u\n", __func__, k, swath_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%u MaximumSwathHeightY=%u\n", __func__, k, MaximumSwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%u MaximumSwathHeightC=%u\n", __func__, k, MaximumSwathHeightC[k]);
#endif

	}
} // CawcuwateSwathWidth

static  dmw_fwoat_t CawcuwateExtwaWatency(
		dmw_uint_t WoundTwipPingWatencyCycwes,
		dmw_uint_t WeowdewingBytes,
		dmw_fwoat_t DCFCWK,
		dmw_uint_t TotawNumbewOfActiveDPP,
		dmw_uint_t PixewChunkSizeInKByte,
		dmw_uint_t TotawNumbewOfDCCActiveDPP,
		dmw_uint_t MetaChunkSize,
		dmw_fwoat_t WetuwnBW,
		dmw_boow_t GPUVMEnabwe,
		dmw_boow_t HostVMEnabwe,
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_uint_t NumbewOfDPP[],
		dmw_uint_t dpte_gwoup_bytes[],
		dmw_fwoat_t HostVMInefficiencyFactow,
		dmw_uint_t HostVMMinPageSize,
		dmw_uint_t HostVMMaxNonCachedPageTabweWevews)
{
	dmw_fwoat_t ExtwaWatencyBytes;
	dmw_fwoat_t ExtwaWatency;

	ExtwaWatencyBytes = CawcuwateExtwaWatencyBytes(
			WeowdewingBytes,
			TotawNumbewOfActiveDPP,
			PixewChunkSizeInKByte,
			TotawNumbewOfDCCActiveDPP,
			MetaChunkSize,
			GPUVMEnabwe,
			HostVMEnabwe,
			NumbewOfActiveSuwfaces,
			NumbewOfDPP,
			dpte_gwoup_bytes,
			HostVMInefficiencyFactow,
			HostVMMinPageSize,
			HostVMMaxNonCachedPageTabweWevews);

	ExtwaWatency = (WoundTwipPingWatencyCycwes + __DMW_AWB_TO_WET_DEWAY__) / DCFCWK + ExtwaWatencyBytes / WetuwnBW;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WoundTwipPingWatencyCycwes=%u\n", __func__, WoundTwipPingWatencyCycwes);
	dmw_pwint("DMW::%s: DCFCWK=%f\n", __func__, DCFCWK);
	dmw_pwint("DMW::%s: ExtwaWatencyBytes=%f\n", __func__, ExtwaWatencyBytes);
	dmw_pwint("DMW::%s: WetuwnBW=%f\n", __func__, WetuwnBW);
	dmw_pwint("DMW::%s: ExtwaWatency=%f\n", __func__, ExtwaWatency);
#endif

	wetuwn ExtwaWatency;
} // CawcuwateExtwaWatency

static dmw_uint_t CawcuwateHostVMDynamicWevews(
									dmw_boow_t GPUVMEnabwe,
									dmw_boow_t HostVMEnabwe,
									dmw_uint_t HostVMMinPageSize,
									dmw_uint_t HostVMMaxNonCachedPageTabweWevews)
{
	dmw_uint_t HostVMDynamicWevews = 0;

	if (GPUVMEnabwe && HostVMEnabwe) {
		if (HostVMMinPageSize < 2048)
			HostVMDynamicWevews = HostVMMaxNonCachedPageTabweWevews;
		ewse if (HostVMMinPageSize >= 2048 && HostVMMinPageSize < 1048576)
			HostVMDynamicWevews = (dmw_uint_t) dmw_max(0, (dmw_fwoat_t) HostVMMaxNonCachedPageTabweWevews - 1);
		ewse
			HostVMDynamicWevews = (dmw_uint_t) dmw_max(0, (dmw_fwoat_t) HostVMMaxNonCachedPageTabweWevews - 2);
	} ewse {
		HostVMDynamicWevews = 0;
	}
	wetuwn HostVMDynamicWevews;
}

static dmw_uint_t CawcuwateExtwaWatencyBytes(dmw_uint_t WeowdewingBytes,
										dmw_uint_t TotawNumbewOfActiveDPP,
										dmw_uint_t PixewChunkSizeInKByte,
										dmw_uint_t TotawNumbewOfDCCActiveDPP,
										dmw_uint_t MetaChunkSize,
										dmw_boow_t GPUVMEnabwe,
										dmw_boow_t HostVMEnabwe,
										dmw_uint_t NumbewOfActiveSuwfaces,
										dmw_uint_t NumbewOfDPP[],
										dmw_uint_t dpte_gwoup_bytes[],
										dmw_fwoat_t HostVMInefficiencyFactow,
										dmw_uint_t HostVMMinPageSize,
										dmw_uint_t HostVMMaxNonCachedPageTabweWevews)
{
	dmw_uint_t  HostVMDynamicWevews = CawcuwateHostVMDynamicWevews(GPUVMEnabwe, HostVMEnabwe, HostVMMinPageSize, HostVMMaxNonCachedPageTabweWevews);
	dmw_fwoat_t wet                 = WeowdewingBytes + (TotawNumbewOfActiveDPP * PixewChunkSizeInKByte + TotawNumbewOfDCCActiveDPP * MetaChunkSize) * 1024.0;

	if (GPUVMEnabwe == twue) {
		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			wet = wet + NumbewOfDPP[k] * dpte_gwoup_bytes[k] * (1 + 8 * HostVMDynamicWevews) * HostVMInefficiencyFactow;
		}
	}
	wetuwn (dmw_uint_t)(wet);
}

static dmw_fwoat_t CawcuwateUwgentWatency(
		dmw_fwoat_t UwgentWatencyPixewDataOnwy,
		dmw_fwoat_t UwgentWatencyPixewMixedWithVMData,
		dmw_fwoat_t UwgentWatencyVMDataOnwy,
		dmw_boow_t DoUwgentWatencyAdjustment,
		dmw_fwoat_t UwgentWatencyAdjustmentFabwicCwockComponent,
		dmw_fwoat_t UwgentWatencyAdjustmentFabwicCwockWefewence,
		dmw_fwoat_t FabwicCwock)
{
	dmw_fwoat_t   wet;

	wet = dmw_max3(UwgentWatencyPixewDataOnwy, UwgentWatencyPixewMixedWithVMData, UwgentWatencyVMDataOnwy);
	if (DoUwgentWatencyAdjustment == twue) {
		wet = wet + UwgentWatencyAdjustmentFabwicCwockComponent * (UwgentWatencyAdjustmentFabwicCwockWefewence / FabwicCwock - 1);
	}
	wetuwn wet;
}

static dmw_fwoat_t WequiwedDTBCWK(
		dmw_boow_t DSCEnabwe,
		dmw_fwoat_t PixewCwock,
		enum dmw_output_fowmat_cwass OutputFowmat,
		dmw_fwoat_t OutputBpp,
		dmw_uint_t DSCSwices,
		dmw_uint_t HTotaw,
		dmw_uint_t HActive,
		dmw_uint_t AudioWate,
		dmw_uint_t AudioWayout)
{
	if (DSCEnabwe != twue) {
		wetuwn dmw_max(PixewCwock / 4.0 * OutputBpp / 24.0, 25.0);
	} ewse {
		dmw_fwoat_t PixewWowdWate = PixewCwock / (OutputFowmat == dmw_444 ? 1 : 2);
		dmw_fwoat_t HCActive = dmw_ceiw(DSCSwices * dmw_ceiw(OutputBpp * dmw_ceiw(HActive / DSCSwices, 1) / 8.0, 1) / 3.0, 1);
		dmw_fwoat_t HCBwank = 64 + 32 * dmw_ceiw(AudioWate * (AudioWayout == 1 ? 1 : 0.25) * HTotaw / (PixewCwock * 1000), 1);
		dmw_fwoat_t AvewageTwibyteWate = PixewWowdWate * (HCActive + HCBwank) / HTotaw;
		dmw_fwoat_t HActiveTwibyteWate = PixewWowdWate * HCActive / HActive;
		wetuwn dmw_max4(PixewWowdWate / 4.0, AvewageTwibyteWate / 4.0, HActiveTwibyteWate / 4.0, 25.0) * 1.002;
	}
}

static void UseMinimumDCFCWK(stwuct dispway_mode_wib_scwatch_st *scwatch, stwuct UseMinimumDCFCWK_pawams_st *p)
{
	stwuct UseMinimumDCFCWK_wocaws_st *s = &scwatch->UseMinimumDCFCWK_wocaws;

	s->NowmawEfficiency = p->PewcentOfIdeawSDPPowtBWWeceivedAftewUwgWatency / 100.0;
	fow (dmw_uint_t j = 0; j < 2; ++j) {


		s->TotawMaxPwefetchFwipDPTEWowBandwidth[j] = 0;
		fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
			s->TotawMaxPwefetchFwipDPTEWowBandwidth[j] = s->TotawMaxPwefetchFwipDPTEWowBandwidth[j] + p->NoOfDPP[j][k] * p->DPTEBytesPewWow[j][k] / (15.75 * p->HTotaw[k] / p->PixewCwock[k]);
		}

		fow (dmw_uint_t k = 0; k <= p->NumbewOfActiveSuwfaces - 1; ++k) {
			s->NoOfDPPState[k] = p->NoOfDPP[j][k];
		}

		s->DPTEBandwidth = s->TotawMaxPwefetchFwipDPTEWowBandwidth[j];

		s->DCFCWKWequiwedFowAvewageBandwidth = dmw_max(p->PwojectedDCFCWKDeepSweep[j], s->DPTEBandwidth / s->NowmawEfficiency / p->WetuwnBusWidth);

		s->ExtwaWatencyBytes = CawcuwateExtwaWatencyBytes(p->WeowdewingBytes, p->TotawNumbewOfActiveDPP[j], p->PixewChunkSizeInKByte, p->TotawNumbewOfDCCActiveDPP[j],
			p->MetaChunkSize, p->GPUVMEnabwe, p->HostVMEnabwe, p->NumbewOfActiveSuwfaces, s->NoOfDPPState, p->dpte_gwoup_bytes,
												1, p->HostVMMinPageSize, p->HostVMMaxNonCachedPageTabweWevews);
		s->ExtwaWatencyCycwes = p->WoundTwipPingWatencyCycwes + __DMW_AWB_TO_WET_DEWAY__ + s->ExtwaWatencyBytes / s->NowmawEfficiency / p->WetuwnBusWidth;
		fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
			dmw_fwoat_t DCFCWKCycwesWequiwedInPwefetch;
			dmw_fwoat_t PwefetchTime;

			s->PixewDCFCWKCycwesWequiwedInPwefetch[k] = (p->PwefetchWinesY[j][k] * p->swath_width_wuma_ub_aww_states[j][k] * p->BytePewPixewY[k] + p->PwefetchWinesC[j][k] * p->swath_width_chwoma_ub_aww_states[j][k] * p->BytePewPixewC[k]) / s->NowmawEfficiency / p->WetuwnBusWidth;
			DCFCWKCycwesWequiwedInPwefetch = 2 * s->ExtwaWatencyCycwes / s->NoOfDPPState[k] + p->PDEAndMetaPTEBytesPewFwame[j][k] / s->NowmawEfficiency / s->NowmawEfficiency / p->WetuwnBusWidth * (p->GPUVMMaxPageTabweWevews > 2 ? 1 : 0) + 2 * p->DPTEBytesPewWow[j][k] / s->NowmawEfficiency / s->NowmawEfficiency / p->WetuwnBusWidth + 2 * p->MetaWowBytes[j][k] / s->NowmawEfficiency / p->WetuwnBusWidth + s->PixewDCFCWKCycwesWequiwedInPwefetch[k];
			s->PwefetchPixewWinesTime[k] = dmw_max(p->PwefetchWinesY[j][k], p->PwefetchWinesC[j][k]) * p->HTotaw[k] / p->PixewCwock[k];
			s->DynamicMetadataVMExtwaWatency[k] = (p->GPUVMEnabwe == twue && p->DynamicMetadataEnabwe[k] == twue && p->DynamicMetadataVMEnabwed == twue) ? p->UwgWatency * p->GPUVMMaxPageTabweWevews * (p->HostVMEnabwe == twue ? p->HostVMMaxNonCachedPageTabweWevews + 1 : 1) : 0;

			s->MinimumTWait = CawcuwateTWait(p->MaxPwefetchMode,
				p->UseMAWWFowPStateChange[k],
				p->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
				p->DWWDispway[k],
				p->DWAMCwockChangeWatencyFinaw,
				p->FCWKChangeWatency,
				p->UwgWatency,
				p->SWEntewPwusExitTime);

			PwefetchTime = (p->MaximumVStawtup[j][k] - 1) * p->HTotaw[k] / p->PixewCwock[k] - s->MinimumTWait - p->UwgWatency * ((p->GPUVMMaxPageTabweWevews <= 2 ? p->GPUVMMaxPageTabweWevews : p->GPUVMMaxPageTabweWevews - 2) *  (p->HostVMEnabwe == twue ? p->HostVMMaxNonCachedPageTabweWevews + 1 : 1) - 1) - s->DynamicMetadataVMExtwaWatency[k];

			if (PwefetchTime > 0) {
				dmw_fwoat_t ExpectedVWatioPwefetch;
				ExpectedVWatioPwefetch = s->PwefetchPixewWinesTime[k] / (PwefetchTime * s->PixewDCFCWKCycwesWequiwedInPwefetch[k] / DCFCWKCycwesWequiwedInPwefetch);
				s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = s->NoOfDPPState[k] * s->PixewDCFCWKCycwesWequiwedInPwefetch[k] / s->PwefetchPixewWinesTime[k] * dmw_max(1.0, ExpectedVWatioPwefetch) * dmw_max(1.0, ExpectedVWatioPwefetch / 4);
				if (p->HostVMEnabwe == twue || p->ImmediateFwipWequiwement == twue) {
					s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] + s->NoOfDPPState[k] * s->DPTEBandwidth / s->NowmawEfficiency / s->NowmawEfficiency / p->WetuwnBusWidth;
				}
			} ewse {
				s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = p->DCFCWKPewState;
			}
			if (p->DynamicMetadataEnabwe[k] == twue) {
				dmw_fwoat_t TSetupPipe;
				dmw_fwoat_t TdmbfPipe;
				dmw_fwoat_t TdmsksPipe;
				dmw_fwoat_t TdmecPipe;
				dmw_fwoat_t AwwowedTimeFowUwgentExtwaWatency;

				CawcuwateVUpdateAndDynamicMetadataPawametews(
					p->MaxIntewDCNTiweWepeatews,
					p->WequiwedDPPCWKPewSuwface[j][k],
					p->WequiwedDISPCWK[j],
					p->PwojectedDCFCWKDeepSweep[j],
					p->PixewCwock[k],
					p->HTotaw[k],
					p->VTotaw[k] - p->VActive[k],
					p->DynamicMetadataTwansmittedBytes[k],
					p->DynamicMetadataWinesBefoweActiveWequiwed[k],
					p->Intewwace[k],
					p->PwogwessiveToIntewwaceUnitInOPP,

					// Output
					&TSetupPipe,
					&TdmbfPipe,
					&TdmecPipe,
					&TdmsksPipe,
					&s->dummy1,
					&s->dummy2,
					&s->dummy3);

				AwwowedTimeFowUwgentExtwaWatency = p->MaximumVStawtup[j][k] * p->HTotaw[k] / p->PixewCwock[k] - s->MinimumTWait - TSetupPipe - TdmbfPipe - TdmecPipe - TdmsksPipe - s->DynamicMetadataVMExtwaWatency[k];
				if (AwwowedTimeFowUwgentExtwaWatency > 0) {
					s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = dmw_max(s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k], s->ExtwaWatencyCycwes / AwwowedTimeFowUwgentExtwaWatency);
				} ewse {
					s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = p->DCFCWKPewState;
				}
			}
		}
		s->DCFCWKWequiwedFowPeakBandwidth = 0;
		fow (dmw_uint_t k = 0; k <= p->NumbewOfActiveSuwfaces - 1; ++k) {
			s->DCFCWKWequiwedFowPeakBandwidth = s->DCFCWKWequiwedFowPeakBandwidth + s->DCFCWKWequiwedFowPeakBandwidthPewSuwface[k];
		}
		s->MinimumTvmPwus2Tw0 = p->UwgWatency * (p->GPUVMEnabwe == twue ? (p->HostVMEnabwe == twue ? (p->GPUVMMaxPageTabweWevews + 2) * (p->HostVMMaxNonCachedPageTabweWevews + 1) - 1 : p->GPUVMMaxPageTabweWevews + 1) : 0);
		fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
			dmw_fwoat_t MaximumTvmPwus2Tw0PwusTsw;
			MaximumTvmPwus2Tw0PwusTsw = (p->MaximumVStawtup[j][k] - 2) * p->HTotaw[k] / p->PixewCwock[k] - s->MinimumTWait - s->DynamicMetadataVMExtwaWatency[k];
			if (MaximumTvmPwus2Tw0PwusTsw <= s->MinimumTvmPwus2Tw0 + s->PwefetchPixewWinesTime[k] / 4) {
				s->DCFCWKWequiwedFowPeakBandwidth = p->DCFCWKPewState;
			} ewse {
				s->DCFCWKWequiwedFowPeakBandwidth = dmw_max3(s->DCFCWKWequiwedFowPeakBandwidth,
														2 * s->ExtwaWatencyCycwes / (MaximumTvmPwus2Tw0PwusTsw - s->MinimumTvmPwus2Tw0 - s->PwefetchPixewWinesTime[k] / 4),
														(2 * s->ExtwaWatencyCycwes + s->PixewDCFCWKCycwesWequiwedInPwefetch[k]) / (MaximumTvmPwus2Tw0PwusTsw - s->MinimumTvmPwus2Tw0));
			}
		}
		p->DCFCWKState[j] = dmw_min(p->DCFCWKPewState, 1.05 * dmw_max(s->DCFCWKWequiwedFowAvewageBandwidth, s->DCFCWKWequiwedFowPeakBandwidth));
	}
}


static dmw_boow_t UnboundedWequest(enum dmw_unbounded_wequesting_powicy UseUnboundedWequestingFinaw,
						dmw_uint_t TotawNumbewOfActiveDPP,
						dmw_boow_t NoChwomaOwWineaw,
						enum dmw_output_encodew_cwass Output)
{
	dmw_boow_t wet_vaw = fawse;

	wet_vaw = (UseUnboundedWequestingFinaw != dmw_unbounded_wequesting_disabwe
			&& TotawNumbewOfActiveDPP == 1 && NoChwomaOwWineaw);
	if (UseUnboundedWequestingFinaw == dmw_unbounded_wequesting_edp_onwy && Output != dmw_edp) {
		wet_vaw = fawse;
	}
	wetuwn (wet_vaw);
}

static void CawcuwateSuwfaceSizeInMaww(
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_uint_t MAWWAwwocatedFowDCN,
		enum dmw_use_maww_fow_static_scween_mode UseMAWWFowStaticScween[],
		dmw_boow_t DCCEnabwe[],
		dmw_boow_t ViewpowtStationawy[],
		dmw_uint_t ViewpowtXStawtY[],
		dmw_uint_t ViewpowtYStawtY[],
		dmw_uint_t ViewpowtXStawtC[],
		dmw_uint_t ViewpowtYStawtC[],
		dmw_uint_t ViewpowtWidthY[],
		dmw_uint_t ViewpowtHeightY[],
		dmw_uint_t BytesPewPixewY[],
		dmw_uint_t ViewpowtWidthC[],
		dmw_uint_t ViewpowtHeightC[],
		dmw_uint_t BytesPewPixewC[],
		dmw_uint_t SuwfaceWidthY[],
		dmw_uint_t SuwfaceWidthC[],
		dmw_uint_t SuwfaceHeightY[],
		dmw_uint_t SuwfaceHeightC[],
		dmw_uint_t Wead256BytesBwockWidthY[],
		dmw_uint_t Wead256BytesBwockWidthC[],
		dmw_uint_t Wead256BytesBwockHeightY[],
		dmw_uint_t Wead256BytesBwockHeightC[],
		dmw_uint_t WeadBwockWidthY[],
		dmw_uint_t WeadBwockWidthC[],
		dmw_uint_t WeadBwockHeightY[],
		dmw_uint_t WeadBwockHeightC[],

		// Output
		dmw_uint_t SuwfaceSizeInMAWW[],
		dmw_boow_t *ExceededMAWWSize)
{
	dmw_uint_t TotawSuwfaceSizeInMAWW  = 0;

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (ViewpowtStationawy[k]) {
			SuwfaceSizeInMAWW[k] = (dmw_uint_t)(dmw_min(dmw_ceiw(SuwfaceWidthY[k], WeadBwockWidthY[k]), dmw_fwoow(ViewpowtXStawtY[k] + ViewpowtWidthY[k] + WeadBwockWidthY[k] - 1, WeadBwockWidthY[k]) - dmw_fwoow(ViewpowtXStawtY[k], WeadBwockWidthY[k])) *
									dmw_min(dmw_ceiw(SuwfaceHeightY[k], WeadBwockHeightY[k]), dmw_fwoow(ViewpowtYStawtY[k] + ViewpowtHeightY[k] + WeadBwockHeightY[k] - 1, WeadBwockHeightY[k]) - dmw_fwoow(ViewpowtYStawtY[k], WeadBwockHeightY[k])) *
									BytesPewPixewY[k]);

			if (WeadBwockWidthC[k] > 0) {
				SuwfaceSizeInMAWW[k] = (dmw_uint_t)(SuwfaceSizeInMAWW[k] +
										dmw_min(dmw_ceiw(SuwfaceWidthC[k], WeadBwockWidthC[k]), dmw_fwoow(ViewpowtXStawtC[k] + ViewpowtWidthC[k] + WeadBwockWidthC[k] - 1, WeadBwockWidthC[k]) - dmw_fwoow(ViewpowtXStawtC[k], WeadBwockWidthC[k])) *
										dmw_min(dmw_ceiw(SuwfaceHeightC[k], WeadBwockHeightC[k]), dmw_fwoow(ViewpowtYStawtC[k] + ViewpowtHeightC[k] + WeadBwockHeightC[k] - 1, WeadBwockHeightC[k]) - dmw_fwoow(ViewpowtYStawtC[k], WeadBwockHeightC[k])) * BytesPewPixewC[k]);
			}
			if (DCCEnabwe[k] == twue) {
				SuwfaceSizeInMAWW[k] = (dmw_uint_t)(SuwfaceSizeInMAWW[k] +
					dmw_min(dmw_ceiw(SuwfaceWidthY[k], 8 * Wead256BytesBwockWidthY[k]), dmw_fwoow(ViewpowtXStawtY[k] + ViewpowtWidthY[k] + 8 * Wead256BytesBwockWidthY[k] - 1, 8 * Wead256BytesBwockWidthY[k]) - dmw_fwoow(ViewpowtXStawtY[k], 8 * Wead256BytesBwockWidthY[k])) *
					dmw_min(dmw_ceiw(SuwfaceHeightY[k], 8 * Wead256BytesBwockHeightY[k]), dmw_fwoow(ViewpowtYStawtY[k] + ViewpowtHeightY[k] + 8 * Wead256BytesBwockHeightY[k] - 1, 8 * Wead256BytesBwockHeightY[k]) - dmw_fwoow(ViewpowtYStawtY[k], 8 * Wead256BytesBwockHeightY[k])) * BytesPewPixewY[k] / 256);
				if (Wead256BytesBwockWidthC[k] > 0) {
					SuwfaceSizeInMAWW[k] = (dmw_uint_t)(SuwfaceSizeInMAWW[k] +
						dmw_min(dmw_ceiw(SuwfaceWidthC[k], 8 * Wead256BytesBwockWidthC[k]), dmw_fwoow(ViewpowtXStawtC[k] + ViewpowtWidthC[k] + 8 * Wead256BytesBwockWidthC[k] - 1, 8 * Wead256BytesBwockWidthC[k]) - dmw_fwoow(ViewpowtXStawtC[k], 8 * Wead256BytesBwockWidthC[k])) *
						dmw_min(dmw_ceiw(SuwfaceHeightC[k], 8 * Wead256BytesBwockHeightC[k]), dmw_fwoow(ViewpowtYStawtC[k] + ViewpowtHeightC[k] + 8 * Wead256BytesBwockHeightC[k] - 1, 8 * Wead256BytesBwockHeightC[k]) - dmw_fwoow(ViewpowtYStawtC[k], 8 * Wead256BytesBwockHeightC[k])) * BytesPewPixewC[k] / 256);
				}
			}
		} ewse {
			SuwfaceSizeInMAWW[k] = (dmw_uint_t)(dmw_ceiw(dmw_min(SuwfaceWidthY[k], ViewpowtWidthY[k] + WeadBwockWidthY[k] - 1), WeadBwockWidthY[k]) * dmw_ceiw(dmw_min(SuwfaceHeightY[k], ViewpowtHeightY[k] + WeadBwockHeightY[k] - 1), WeadBwockHeightY[k]) * BytesPewPixewY[k]);
			if (WeadBwockWidthC[k] > 0) {
				SuwfaceSizeInMAWW[k] = (dmw_uint_t)(SuwfaceSizeInMAWW[k] +
										dmw_ceiw(dmw_min(SuwfaceWidthC[k], ViewpowtWidthC[k] + WeadBwockWidthC[k] - 1), WeadBwockWidthC[k]) *
										dmw_ceiw(dmw_min(SuwfaceHeightC[k], ViewpowtHeightC[k] + WeadBwockHeightC[k] - 1), WeadBwockHeightC[k]) * BytesPewPixewC[k]);
		}
		if (DCCEnabwe[k] == twue) {
			SuwfaceSizeInMAWW[k] = (dmw_uint_t)(SuwfaceSizeInMAWW[k] +
					dmw_ceiw(dmw_min(SuwfaceWidthY[k], ViewpowtWidthY[k] + 8 * Wead256BytesBwockWidthY[k] - 1), 8 * Wead256BytesBwockWidthY[k]) *
					dmw_ceiw(dmw_min(SuwfaceHeightY[k], ViewpowtHeightY[k] + 8 * Wead256BytesBwockHeightY[k] - 1), 8 * Wead256BytesBwockHeightY[k]) * BytesPewPixewY[k] / 256);

				if (Wead256BytesBwockWidthC[k] > 0) {
					SuwfaceSizeInMAWW[k] = (dmw_uint_t)(SuwfaceSizeInMAWW[k] +
						dmw_ceiw(dmw_min(SuwfaceWidthC[k], ViewpowtWidthC[k] + 8 * Wead256BytesBwockWidthC[k] - 1), 8 * Wead256BytesBwockWidthC[k]) *
						dmw_ceiw(dmw_min(SuwfaceHeightC[k], ViewpowtHeightC[k] + 8 * Wead256BytesBwockHeightC[k] - 1), 8 * Wead256BytesBwockHeightC[k]) * BytesPewPixewC[k] / 256);
				}
			}
		}
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (UseMAWWFowStaticScween[k] == dmw_use_maww_static_scween_enabwe)
			TotawSuwfaceSizeInMAWW = TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[k];
	}
	*ExceededMAWWSize = (TotawSuwfaceSizeInMAWW > MAWWAwwocatedFowDCN * 1024 * 1024);
} // CawcuwateSuwfaceSizeInMaww

static void CawcuwateDETBuffewSize(
						dmw_uint_t DETSizeOvewwide[],
						enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
						dmw_boow_t FowceSingweDPP,
						dmw_uint_t NumbewOfActiveSuwfaces,
						dmw_boow_t UnboundedWequestEnabwed,
						dmw_uint_t nomDETInKByte,
						dmw_uint_t MaxTotawDETInKByte,
						dmw_uint_t ConfigWetuwnBuffewSizeInKByte,
						dmw_uint_t MinCompwessedBuffewSizeInKByte,
						dmw_uint_t ConfigWetuwnBuffewSegmentSizeInkByte,
						dmw_uint_t CompwessedBuffewSegmentSizeInkByteFinaw,
						enum dmw_souwce_fowmat_cwass SouwcePixewFowmat[],
						dmw_fwoat_t WeadBandwidthWuma[],
						dmw_fwoat_t WeadBandwidthChwoma[],
						dmw_uint_t WoundedUpMaxSwathSizeBytesY[],
						dmw_uint_t WoundedUpMaxSwathSizeBytesC[],
						dmw_uint_t DPPPewSuwface[],
						// Output
						dmw_uint_t DETBuffewSizeInKByte[],
						dmw_uint_t *CompwessedBuffewSizeInkByte)
{
	dmw_uint_t DETBuffewSizePoowInKByte;
	dmw_uint_t NextDETBuffewPieceInKByte;
	dmw_boow_t DETPieceAssignedToThisSuwfaceAwweady[__DMW_NUM_PWANES__];
	dmw_boow_t NextPotentiawSuwfaceToAssignDETPieceFound;
	dmw_uint_t NextSuwfaceToAssignDETPiece;
	dmw_fwoat_t TotawBandwidth;
	dmw_fwoat_t BandwidthOfSuwfacesNotAssignedDETPiece;
	dmw_uint_t max_minDET;
	dmw_uint_t minDET;
	dmw_uint_t minDET_pipe;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: FowceSingweDPP = %u\n", __func__, FowceSingweDPP);
	dmw_pwint("DMW::%s: nomDETInKByte = %u\n", __func__, nomDETInKByte);
	dmw_pwint("DMW::%s: NumbewOfActiveSuwfaces = %u\n", __func__, NumbewOfActiveSuwfaces);
	dmw_pwint("DMW::%s: UnboundedWequestEnabwed = %u\n", __func__, UnboundedWequestEnabwed);
	dmw_pwint("DMW::%s: MaxTotawDETInKByte = %u\n", __func__, MaxTotawDETInKByte);
	dmw_pwint("DMW::%s: ConfigWetuwnBuffewSizeInKByte = %u\n", __func__, ConfigWetuwnBuffewSizeInKByte);
	dmw_pwint("DMW::%s: MinCompwessedBuffewSizeInKByte = %u\n", __func__, MinCompwessedBuffewSizeInKByte);
	dmw_pwint("DMW::%s: CompwessedBuffewSegmentSizeInkByteFinaw = %u\n", __func__, CompwessedBuffewSegmentSizeInkByteFinaw);
#endif

	// Note: Wiww use defauwt det size if that fits 2 swaths
	if (UnboundedWequestEnabwed) {
		if (DETSizeOvewwide[0] > 0) {
			DETBuffewSizeInKByte[0] = DETSizeOvewwide[0];
		} ewse {
			DETBuffewSizeInKByte[0] = (dmw_uint_t) dmw_max(128.0, dmw_ceiw(2.0 * ((dmw_fwoat_t) WoundedUpMaxSwathSizeBytesY[0] + (dmw_fwoat_t) WoundedUpMaxSwathSizeBytesC[0]) / 1024.0, ConfigWetuwnBuffewSegmentSizeInkByte));
		}
		*CompwessedBuffewSizeInkByte = ConfigWetuwnBuffewSizeInKByte - DETBuffewSizeInKByte[0];
	} ewse {
		DETBuffewSizePoowInKByte = MaxTotawDETInKByte;
		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			DETBuffewSizeInKByte[k] = 0;
			if (SouwcePixewFowmat[k] == dmw_420_8 || SouwcePixewFowmat[k] == dmw_420_10 || SouwcePixewFowmat[k] == dmw_420_12) {
				max_minDET = nomDETInKByte - ConfigWetuwnBuffewSegmentSizeInkByte;
			} ewse {
				max_minDET = nomDETInKByte;
			}
			minDET = 128;
			minDET_pipe = 0;

			// add DET wesouwce untiw can howd 2 fuww swaths
			whiwe (minDET <= max_minDET && minDET_pipe == 0) {
				if (2.0 * ((dmw_fwoat_t) WoundedUpMaxSwathSizeBytesY[k] + (dmw_fwoat_t) WoundedUpMaxSwathSizeBytesC[k]) / 1024.0 <= minDET)
					minDET_pipe = minDET;
				minDET = minDET + ConfigWetuwnBuffewSegmentSizeInkByte;
			}

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u minDET = %u\n", __func__, k, minDET);
			dmw_pwint("DMW::%s: k=%u max_minDET = %u\n", __func__, k, max_minDET);
			dmw_pwint("DMW::%s: k=%u minDET_pipe = %u\n", __func__, k, minDET_pipe);
			dmw_pwint("DMW::%s: k=%u WoundedUpMaxSwathSizeBytesY = %u\n", __func__, k, WoundedUpMaxSwathSizeBytesY[k]);
			dmw_pwint("DMW::%s: k=%u WoundedUpMaxSwathSizeBytesC = %u\n", __func__, k, WoundedUpMaxSwathSizeBytesC[k]);
#endif

			if (minDET_pipe == 0) {
				minDET_pipe = (dmw_uint_t)(dmw_max(128, dmw_ceiw(((dmw_fwoat_t)WoundedUpMaxSwathSizeBytesY[k] + (dmw_fwoat_t)WoundedUpMaxSwathSizeBytesC[k]) / 1024.0, ConfigWetuwnBuffewSegmentSizeInkByte)));
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%u minDET_pipe = %u (assume each pwane take hawf DET)\n", __func__, k, minDET_pipe);
#endif
			}

			if (UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe) {
				DETBuffewSizeInKByte[k] = 0;
			} ewse if (DETSizeOvewwide[k] > 0) {
				DETBuffewSizeInKByte[k] = DETSizeOvewwide[k];
				DETBuffewSizePoowInKByte = DETBuffewSizePoowInKByte - (FowceSingweDPP ? 1 : DPPPewSuwface[k]) * DETSizeOvewwide[k];
			} ewse if ((FowceSingweDPP ? 1 : DPPPewSuwface[k]) * minDET_pipe <= DETBuffewSizePoowInKByte) {
				DETBuffewSizeInKByte[k] = minDET_pipe;
				DETBuffewSizePoowInKByte = DETBuffewSizePoowInKByte - (FowceSingweDPP ? 1 : DPPPewSuwface[k]) * minDET_pipe;
			}

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u DPPPewSuwface = %u\n", __func__, k, DPPPewSuwface[k]);
			dmw_pwint("DMW::%s: k=%u DETSizeOvewwide = %u\n", __func__, k, DETSizeOvewwide[k]);
			dmw_pwint("DMW::%s: k=%u DETBuffewSizeInKByte = %u\n", __func__, k, DETBuffewSizeInKByte[k]);
			dmw_pwint("DMW::%s: DETBuffewSizePoowInKByte = %u\n", __func__, DETBuffewSizePoowInKByte);
#endif
		}

		TotawBandwidth = 0;
		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			if (UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe)
				TotawBandwidth = TotawBandwidth + WeadBandwidthWuma[k] + WeadBandwidthChwoma[k];
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: --- Befowe bandwidth adjustment ---\n", __func__);
		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			dmw_pwint("DMW::%s: k=%u DETBuffewSizeInKByte   = %u\n", __func__, k, DETBuffewSizeInKByte[k]);
		}
		dmw_pwint("DMW::%s: --- DET awwocation with bandwidth ---\n", __func__);
#endif
		dmw_pwint("DMW::%s: TotawBandwidth = %f\n", __func__, TotawBandwidth);
		BandwidthOfSuwfacesNotAssignedDETPiece = TotawBandwidth;
		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {

			if (UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe) {
				DETPieceAssignedToThisSuwfaceAwweady[k] = twue;
			} ewse if (DETSizeOvewwide[k] > 0 || (((dmw_fwoat_t) (FowceSingweDPP ? 1 : DPPPewSuwface[k]) * (dmw_fwoat_t) DETBuffewSizeInKByte[k] / (dmw_fwoat_t) MaxTotawDETInKByte) >= ((WeadBandwidthWuma[k] + WeadBandwidthChwoma[k]) / TotawBandwidth))) {
				DETPieceAssignedToThisSuwfaceAwweady[k] = twue;
				BandwidthOfSuwfacesNotAssignedDETPiece = BandwidthOfSuwfacesNotAssignedDETPiece - WeadBandwidthWuma[k] - WeadBandwidthChwoma[k];
			} ewse {
				DETPieceAssignedToThisSuwfaceAwweady[k] = fawse;
			}
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u DETPieceAssignedToThisSuwfaceAwweady = %u\n", __func__, k, DETPieceAssignedToThisSuwfaceAwweady[k]);
			dmw_pwint("DMW::%s: k=%u BandwidthOfSuwfacesNotAssignedDETPiece = %f\n", __func__, k, BandwidthOfSuwfacesNotAssignedDETPiece);
#endif
		}

		fow (dmw_uint_t j = 0; j < NumbewOfActiveSuwfaces; ++j) {
			NextPotentiawSuwfaceToAssignDETPieceFound = fawse;
			NextSuwfaceToAssignDETPiece = 0;

			fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: j=%u k=%u, WeadBandwidthWuma[k] = %f\n", __func__, j, k, WeadBandwidthWuma[k]);
				dmw_pwint("DMW::%s: j=%u k=%u, WeadBandwidthChwoma[k] = %f\n", __func__, j, k, WeadBandwidthChwoma[k]);
				dmw_pwint("DMW::%s: j=%u k=%u, WeadBandwidthWuma[Next] = %f\n", __func__, j, k, WeadBandwidthWuma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%u k=%u, WeadBandwidthChwoma[Next] = %f\n", __func__, j, k, WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%u k=%u, NextSuwfaceToAssignDETPiece = %u\n", __func__, j, k, NextSuwfaceToAssignDETPiece);
#endif
				if (!DETPieceAssignedToThisSuwfaceAwweady[k] && (!NextPotentiawSuwfaceToAssignDETPieceFound ||
					WeadBandwidthWuma[k] + WeadBandwidthChwoma[k] < WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] + WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece])) {
					NextSuwfaceToAssignDETPiece = k;
					NextPotentiawSuwfaceToAssignDETPieceFound = twue;
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: j=%u k=%u, DETPieceAssignedToThisSuwfaceAwweady = %u\n", __func__, j, k, DETPieceAssignedToThisSuwfaceAwweady[k]);
				dmw_pwint("DMW::%s: j=%u k=%u, NextPotentiawSuwfaceToAssignDETPieceFound = %u\n", __func__, j, k, NextPotentiawSuwfaceToAssignDETPieceFound);
#endif
			}

			if (NextPotentiawSuwfaceToAssignDETPieceFound) {
				// Note: To show the bankew's wounding behaviow in VBA and awso the fact that the DET buffew size vawies due to pwecision issue
				//
				//dmw_fwoat_t tmp1 =  ((dmw_fwoat_t) DETBuffewSizePoowInKByte * (WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] + WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]) / BandwidthOfSuwfacesNotAssignedDETPiece /
				//                         ((FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0));
				//dmw_fwoat_t tmp2 =  dmw_wound((dmw_fwoat_t) DETBuffewSizePoowInKByte * (WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] + WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]) / BandwidthOfSuwfacesNotAssignedDETPiece /
				//                         ((FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0));
				//
				//dmw_pwint("DMW::%s: j=%u, tmp1 = %f\n", __func__, j, tmp1);
				//dmw_pwint("DMW::%s: j=%u, tmp2 = %f\n", __func__, j, tmp2);

				NextDETBuffewPieceInKByte = (dmw_uint_t)(dmw_min(
											dmw_wound((dmw_fwoat_t) DETBuffewSizePoowInKByte * (WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] + WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]) / BandwidthOfSuwfacesNotAssignedDETPiece /
												((FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * ConfigWetuwnBuffewSegmentSizeInkByte), twue)
												* (FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * ConfigWetuwnBuffewSegmentSizeInkByte,
											dmw_fwoow((dmw_fwoat_t) DETBuffewSizePoowInKByte, (FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * ConfigWetuwnBuffewSegmentSizeInkByte)));

#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: j=%u, DETBuffewSizePoowInKByte = %u\n", __func__, j, DETBuffewSizePoowInKByte);
				dmw_pwint("DMW::%s: j=%u, NextSuwfaceToAssignDETPiece = %u\n", __func__, j, NextSuwfaceToAssignDETPiece);
				dmw_pwint("DMW::%s: j=%u, WeadBandwidthWuma[%u] = %f\n", __func__, j, NextSuwfaceToAssignDETPiece, WeadBandwidthWuma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%u, WeadBandwidthChwoma[%u] = %f\n", __func__, j, NextSuwfaceToAssignDETPiece, WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%u, BandwidthOfSuwfacesNotAssignedDETPiece = %f\n", __func__, j, BandwidthOfSuwfacesNotAssignedDETPiece);
				dmw_pwint("DMW::%s: j=%u, NextDETBuffewPieceInKByte = %u\n", __func__, j, NextDETBuffewPieceInKByte);
				dmw_pwint("DMW::%s: j=%u, DETBuffewSizeInKByte[%u] incweases fwom %u ", __func__, j, NextSuwfaceToAssignDETPiece, DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece]);
#endif

				DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece] = DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece] + NextDETBuffewPieceInKByte / (FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]);
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("to %u\n", DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece]);
#endif

				DETBuffewSizePoowInKByte = DETBuffewSizePoowInKByte - NextDETBuffewPieceInKByte;
				DETPieceAssignedToThisSuwfaceAwweady[NextSuwfaceToAssignDETPiece] = twue;
				BandwidthOfSuwfacesNotAssignedDETPiece = BandwidthOfSuwfacesNotAssignedDETPiece - (WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] + WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]);
			}
		}
		*CompwessedBuffewSizeInkByte = MinCompwessedBuffewSizeInKByte;
	}
	*CompwessedBuffewSizeInkByte = *CompwessedBuffewSizeInkByte * CompwessedBuffewSegmentSizeInkByteFinaw / ConfigWetuwnBuffewSegmentSizeInkByte;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: --- Aftew bandwidth adjustment ---\n", __func__);
	dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte = %u\n", __func__, *CompwessedBuffewSizeInkByte);
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		dmw_pwint("DMW::%s: k=%u DETBuffewSizeInKByte = %u (TotawWeadBandWidth=%f)\n", __func__, k, DETBuffewSizeInKByte[k], WeadBandwidthWuma[k] + WeadBandwidthChwoma[k]);
	}
#endif
} // CawcuwateDETBuffewSize


/// @bwief Cawcuwate the bound fow wetuwn buffew sizing
static void CawcuwateMaxDETAndMinCompwessedBuffewSize(
		dmw_uint_t  ConfigWetuwnBuffewSizeInKByte,
		dmw_uint_t  ConfigWetuwnBuffewSegmentSizeInKByte,
		dmw_uint_t  WOBBuffewSizeInKByte,
		dmw_uint_t MaxNumDPP,
		dmw_boow_t nomDETInKByteOvewwideEnabwe, // VBA_DEWTA, awwow DV to ovewwide defauwt DET size
		dmw_uint_t nomDETInKByteOvewwideVawue,  // VBA_DEWTA

		// Output
		dmw_uint_t *MaxTotawDETInKByte,
		dmw_uint_t *nomDETInKByte,
		dmw_uint_t *MinCompwessedBuffewSizeInKByte)
{
	*MaxTotawDETInKByte = ConfigWetuwnBuffewSizeInKByte - ConfigWetuwnBuffewSegmentSizeInKByte;
	*nomDETInKByte = (dmw_uint_t)(dmw_fwoow((dmw_fwoat_t) *MaxTotawDETInKByte / (dmw_fwoat_t) MaxNumDPP, ConfigWetuwnBuffewSegmentSizeInKByte));
	*MinCompwessedBuffewSizeInKByte = ConfigWetuwnBuffewSizeInKByte - *MaxTotawDETInKByte;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: ConfigWetuwnBuffewSizeInKByte = %u\n", __func__, ConfigWetuwnBuffewSizeInKByte);
	dmw_pwint("DMW::%s: WOBBuffewSizeInKByte = %u\n", __func__, WOBBuffewSizeInKByte);
	dmw_pwint("DMW::%s: MaxNumDPP = %u\n", __func__, MaxNumDPP);
	dmw_pwint("DMW::%s: MaxTotawDETInKByte = %u\n", __func__, *MaxTotawDETInKByte);
	dmw_pwint("DMW::%s: nomDETInKByte = %u\n", __func__, *nomDETInKByte);
	dmw_pwint("DMW::%s: MinCompwessedBuffewSizeInKByte = %u\n", __func__, *MinCompwessedBuffewSizeInKByte);
#endif

	if (nomDETInKByteOvewwideEnabwe) {
		*nomDETInKByte = nomDETInKByteOvewwideVawue;
		dmw_pwint("DMW::%s: nomDETInKByte = %u (ovewwided)\n", __func__, *nomDETInKByte);
	}
} // CawcuwateMaxDETAndMinCompwessedBuffewSize

/// @bwief Cawcuwate aww the WQ wequest attwibutes, wike wow height and # swath
static void CawcuwateVMWowAndSwath(stwuct dispway_mode_wib_scwatch_st *scwatch,
		stwuct CawcuwateVMWowAndSwath_pawams_st *p)
{
	stwuct CawcuwateVMWowAndSwath_wocaws_st *s = &scwatch->CawcuwateVMWowAndSwath_wocaws;

	s->HostVMDynamicWevews = CawcuwateHostVMDynamicWevews(p->GPUVMEnabwe, p->HostVMEnabwe, p->HostVMMinPageSize, p->HostVMMaxNonCachedPageTabweWevews);

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (p->HostVMEnabwe == twue) {
			p->vm_gwoup_bytes[k] = 512;
			p->dpte_gwoup_bytes[k] = 512;
		} ewse if (p->GPUVMEnabwe == twue) {
			p->vm_gwoup_bytes[k] = 2048;
			if (p->GPUVMMinPageSizeKBytes[k] >= 64 && dmw_is_vewticaw_wotation(p->myPipe[k].SouwceScan)) {
				p->dpte_gwoup_bytes[k] = 512;
			} ewse {
				p->dpte_gwoup_bytes[k] = 2048;
			}
		} ewse {
			p->vm_gwoup_bytes[k] = 0;
			p->dpte_gwoup_bytes[k] = 0;
		}

		if (p->myPipe[k].SouwcePixewFowmat == dmw_420_8 || p->myPipe[k].SouwcePixewFowmat == dmw_420_10 ||
			p->myPipe[k].SouwcePixewFowmat == dmw_420_12 || p->myPipe[k].SouwcePixewFowmat == dmw_wgbe_awpha) {
			if ((p->myPipe[k].SouwcePixewFowmat == dmw_420_10 || p->myPipe[k].SouwcePixewFowmat == dmw_420_12) && !dmw_is_vewticaw_wotation(p->myPipe[k].SouwceScan)) {
				s->PTEBuffewSizeInWequestsFowWuma[k] = (p->PTEBuffewSizeInWequestsWuma + p->PTEBuffewSizeInWequestsChwoma) / 2;
				s->PTEBuffewSizeInWequestsFowChwoma[k] = s->PTEBuffewSizeInWequestsFowWuma[k];
			} ewse {
				s->PTEBuffewSizeInWequestsFowWuma[k] = p->PTEBuffewSizeInWequestsWuma;
				s->PTEBuffewSizeInWequestsFowChwoma[k] = p->PTEBuffewSizeInWequestsChwoma;
			}

			s->PDEAndMetaPTEBytesFwameC = CawcuwateVMAndWowBytes(
				p->myPipe[k].ViewpowtStationawy,
				p->myPipe[k].DCCEnabwe,
				p->myPipe[k].DPPPewSuwface,
				p->myPipe[k].BwockHeight256BytesC,
				p->myPipe[k].BwockWidth256BytesC,
				p->myPipe[k].SouwcePixewFowmat,
				p->myPipe[k].SuwfaceTiwing,
				p->myPipe[k].BytePewPixewC,
				p->myPipe[k].SouwceScan,
				p->SwathWidthC[k],
				p->myPipe[k].ViewpowtHeightChwoma,
				p->myPipe[k].ViewpowtXStawtC,
				p->myPipe[k].ViewpowtYStawtC,
				p->GPUVMEnabwe,
				p->GPUVMMaxPageTabweWevews,
				p->GPUVMMinPageSizeKBytes[k],
				s->PTEBuffewSizeInWequestsFowChwoma[k],
				p->myPipe[k].PitchC,
				p->myPipe[k].DCCMetaPitchC,
				p->myPipe[k].BwockWidthC,
				p->myPipe[k].BwockHeightC,

				// Output
				&s->MetaWowByteC[k],
				&s->PixewPTEBytesPewWowC[k],
				&s->PixewPTEBytesPewWowStowageC[k],
				&p->dpte_wow_width_chwoma_ub[k],
				&p->dpte_wow_height_chwoma[k],
				&p->dpte_wow_height_wineaw_chwoma[k],
				&s->PixewPTEBytesPewWowC_one_wow_pew_fwame[k],
				&s->dpte_wow_width_chwoma_ub_one_wow_pew_fwame[k],
				&s->dpte_wow_height_chwoma_one_wow_pew_fwame[k],
				&p->meta_weq_width_chwoma[k],
				&p->meta_weq_height_chwoma[k],
				&p->meta_wow_width_chwoma[k],
				&p->meta_wow_height_chwoma[k],
				&p->PixewPTEWeqWidthC[k],
				&p->PixewPTEWeqHeightC[k],
				&p->PTEWequestSizeC[k],
				&p->dpde0_bytes_pew_fwame_ub_c[k],
				&p->meta_pte_bytes_pew_fwame_ub_c[k]);

			p->PwefetchSouwceWinesC[k] = CawcuwatePwefetchSouwceWines (
				p->myPipe[k].VWatioChwoma,
				p->myPipe[k].VTapsChwoma,
				p->myPipe[k].IntewwaceEnabwe,
				p->myPipe[k].PwogwessiveToIntewwaceUnitInOPP,
				p->myPipe[k].SwathHeightC,
				p->myPipe[k].SouwceScan,
				p->myPipe[k].ViewpowtStationawy,
				p->SwathWidthC[k],
				p->myPipe[k].ViewpowtHeightChwoma,
				p->myPipe[k].ViewpowtXStawtC,
				p->myPipe[k].ViewpowtYStawtC,

				// Output
				&p->VInitPweFiwwC[k],
				&p->MaxNumSwathC[k]);
		} ewse {
			s->PTEBuffewSizeInWequestsFowWuma[k] = p->PTEBuffewSizeInWequestsWuma + p->PTEBuffewSizeInWequestsChwoma;
			s->PTEBuffewSizeInWequestsFowChwoma[k] = 0;
			s->PixewPTEBytesPewWowC[k] = 0;
			s->PixewPTEBytesPewWowStowageC[k] = 0;
			s->PDEAndMetaPTEBytesFwameC = 0;
			s->MetaWowByteC[k] = 0;
			p->MaxNumSwathC[k] = 0;
			p->PwefetchSouwceWinesC[k] = 0;
			s->dpte_wow_height_chwoma_one_wow_pew_fwame[k] = 0;
			s->dpte_wow_width_chwoma_ub_one_wow_pew_fwame[k] = 0;
			s->PixewPTEBytesPewWowC_one_wow_pew_fwame[k] = 0;
		}

		s->PDEAndMetaPTEBytesFwameY = CawcuwateVMAndWowBytes(
			p->myPipe[k].ViewpowtStationawy,
			p->myPipe[k].DCCEnabwe,
			p->myPipe[k].DPPPewSuwface,
			p->myPipe[k].BwockHeight256BytesY,
			p->myPipe[k].BwockWidth256BytesY,
			p->myPipe[k].SouwcePixewFowmat,
			p->myPipe[k].SuwfaceTiwing,
			p->myPipe[k].BytePewPixewY,
			p->myPipe[k].SouwceScan,
			p->SwathWidthY[k],
			p->myPipe[k].ViewpowtHeight,
			p->myPipe[k].ViewpowtXStawt,
			p->myPipe[k].ViewpowtYStawt,
			p->GPUVMEnabwe,
			p->GPUVMMaxPageTabweWevews,
			p->GPUVMMinPageSizeKBytes[k],
			s->PTEBuffewSizeInWequestsFowWuma[k],
			p->myPipe[k].PitchY,
			p->myPipe[k].DCCMetaPitchY,
			p->myPipe[k].BwockWidthY,
			p->myPipe[k].BwockHeightY,

			// Output
			&s->MetaWowByteY[k],
			&s->PixewPTEBytesPewWowY[k],
			&s->PixewPTEBytesPewWowStowageY[k],
			&p->dpte_wow_width_wuma_ub[k],
			&p->dpte_wow_height_wuma[k],
			&p->dpte_wow_height_wineaw_wuma[k],
			&s->PixewPTEBytesPewWowY_one_wow_pew_fwame[k],
			&s->dpte_wow_width_wuma_ub_one_wow_pew_fwame[k],
			&s->dpte_wow_height_wuma_one_wow_pew_fwame[k],
			&p->meta_weq_width[k],
			&p->meta_weq_height[k],
			&p->meta_wow_width[k],
			&p->meta_wow_height[k],
			&p->PixewPTEWeqWidthY[k],
			&p->PixewPTEWeqHeightY[k],
			&p->PTEWequestSizeY[k],
			&p->dpde0_bytes_pew_fwame_ub_w[k],
			&p->meta_pte_bytes_pew_fwame_ub_w[k]);

			p->PwefetchSouwceWinesY[k] = CawcuwatePwefetchSouwceWines(
			p->myPipe[k].VWatio,
			p->myPipe[k].VTaps,
			p->myPipe[k].IntewwaceEnabwe,
			p->myPipe[k].PwogwessiveToIntewwaceUnitInOPP,
			p->myPipe[k].SwathHeightY,
			p->myPipe[k].SouwceScan,
			p->myPipe[k].ViewpowtStationawy,
			p->SwathWidthY[k],
			p->myPipe[k].ViewpowtHeight,
			p->myPipe[k].ViewpowtXStawt,
			p->myPipe[k].ViewpowtYStawt,

			// Output
			&p->VInitPweFiwwY[k],
			&p->MaxNumSwathY[k]);

		p->PDEAndMetaPTEBytesFwame[k] = (s->PDEAndMetaPTEBytesFwameY + s->PDEAndMetaPTEBytesFwameC) * (1 + 8 * s->HostVMDynamicWevews);
		p->MetaWowByte[k] = s->MetaWowByteY[k] + s->MetaWowByteC[k];

		if (s->PixewPTEBytesPewWowStowageY[k] <= 64 * s->PTEBuffewSizeInWequestsFowWuma[k] && s->PixewPTEBytesPewWowStowageC[k] <= 64 * s->PTEBuffewSizeInWequestsFowChwoma[k]) {
			p->PTEBuffewSizeNotExceeded[k] = twue;
		} ewse {
			p->PTEBuffewSizeNotExceeded[k] = fawse;
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowY = %u\n", __func__, k, s->PixewPTEBytesPewWowY[k]);
			dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowC = %u\n", __func__, k, s->PixewPTEBytesPewWowC[k]);
			dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowStowageY = %u\n", __func__, k, s->PixewPTEBytesPewWowStowageY[k]);
			dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowStowageC = %u\n", __func__, k, s->PixewPTEBytesPewWowStowageC[k]);
			dmw_pwint("DMW::%s: k=%u, PTEBuffewSizeInWequestsFowWuma = %u\n", __func__, k, s->PTEBuffewSizeInWequestsFowWuma[k]);
			dmw_pwint("DMW::%s: k=%u, PTEBuffewSizeInWequestsFowChwoma = %u\n", __func__, k, s->PTEBuffewSizeInWequestsFowChwoma[k]);
			dmw_pwint("DMW::%s: k=%u, PTEBuffewSizeNotExceeded          = %u\n",  __func__, k, p->PTEBuffewSizeNotExceeded[k]);
#endif
		}
		s->one_wow_pew_fwame_fits_in_buffew[k] = (s->PixewPTEBytesPewWowY_one_wow_pew_fwame[k] <= 64 * 2 * s->PTEBuffewSizeInWequestsFowWuma[k] &&
			s->PixewPTEBytesPewWowC_one_wow_pew_fwame[k] <= 64 * 2 * s->PTEBuffewSizeInWequestsFowChwoma[k]);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, PDEAndMetaPTEBytesFwame = %u\n", __func__, k, p->PDEAndMetaPTEBytesFwame[k]);
		dmw_pwint("DMW::%s: k=%u, PDEAndMetaPTEBytesFwameY = %u\n", __func__, k, s->PDEAndMetaPTEBytesFwameY);
		dmw_pwint("DMW::%s: k=%u, PDEAndMetaPTEBytesFwameC = %u\n", __func__, k, s->PDEAndMetaPTEBytesFwameC);
		dmw_pwint("DMW::%s: k=%u, HostVMDynamicWevews = %u\n", __func__, k, s->HostVMDynamicWevews);
		dmw_pwint("DMW::%s: k=%u, one_wow_pew_fwame_fits_in_buffew = %u\n", __func__, k, s->one_wow_pew_fwame_fits_in_buffew[k]);
		dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowY_one_wow_pew_fwame = %u\n", __func__, k, s->PixewPTEBytesPewWowY_one_wow_pew_fwame[k]);
		dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowC_one_wow_pew_fwame    = %u\n",  __func__, k, s->PixewPTEBytesPewWowC_one_wow_pew_fwame[k]);
#endif
	}

	CawcuwateMAWWUseFowStaticScween(
		p->NumbewOfActiveSuwfaces,
		p->MAWWAwwocatedFowDCN,
		p->UseMAWWFowStaticScween,   // mode
		p->SuwfaceSizeInMAWW,
		s->one_wow_pew_fwame_fits_in_buffew,
		// Output
		p->UsesMAWWFowStaticScween); // boowen

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
		if (p->PTEBuffewModeOvewwideEn[k] == 1) {
			p->PTE_BUFFEW_MODE[k] = p->PTEBuffewModeOvewwideVaw[k];
		}
		p->PTE_BUFFEW_MODE[k] = p->myPipe[k].FOWCE_ONE_WOW_FOW_FWAME || p->UsesMAWWFowStaticScween[k] || (p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_sub_viewpowt) ||
			(p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe) || (p->GPUVMMinPageSizeKBytes[k] > 64);
		p->BIGK_FWAGMENT_SIZE[k] = (dmw_uint_t)(dmw_wog2(p->GPUVMMinPageSizeKBytes[k] * 1024) - 12);
	}

	fow (dmw_uint_t k = 0; k < p->NumbewOfActiveSuwfaces; ++k) {
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, SuwfaceSizeInMAWW         = %u\n",  __func__, k, p->SuwfaceSizeInMAWW[k]);
		dmw_pwint("DMW::%s: k=%u, UsesMAWWFowStaticScween   = %u\n",  __func__, k, p->UsesMAWWFowStaticScween[k]);
#endif
		p->use_one_wow_fow_fwame[k] = p->myPipe[k].FOWCE_ONE_WOW_FOW_FWAME || p->UsesMAWWFowStaticScween[k] || (p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_sub_viewpowt) ||
									(p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe) || (p->GPUVMMinPageSizeKBytes[k] > 64 && dmw_is_vewticaw_wotation(p->myPipe[k].SouwceScan));

		p->use_one_wow_fow_fwame_fwip[k] = p->use_one_wow_fow_fwame[k] && !(p->UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_fuww_fwame);

		if (p->use_one_wow_fow_fwame[k]) {
			p->dpte_wow_height_wuma[k] = s->dpte_wow_height_wuma_one_wow_pew_fwame[k];
			p->dpte_wow_width_wuma_ub[k] = s->dpte_wow_width_wuma_ub_one_wow_pew_fwame[k];
			s->PixewPTEBytesPewWowY[k] = s->PixewPTEBytesPewWowY_one_wow_pew_fwame[k];
			p->dpte_wow_height_chwoma[k] = s->dpte_wow_height_chwoma_one_wow_pew_fwame[k];
			p->dpte_wow_width_chwoma_ub[k] = s->dpte_wow_width_chwoma_ub_one_wow_pew_fwame[k];
			s->PixewPTEBytesPewWowC[k] = s->PixewPTEBytesPewWowC_one_wow_pew_fwame[k];
			p->PTEBuffewSizeNotExceeded[k] = s->one_wow_pew_fwame_fits_in_buffew[k];
		}

		if (p->MetaWowByte[k] <= p->DCCMetaBuffewSizeBytes) {
			p->DCCMetaBuffewSizeNotExceeded[k] = twue;
		} ewse {
			p->DCCMetaBuffewSizeNotExceeded[k] = fawse;

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u, MetaWowByte                   = %u\n",  __func__, k, p->MetaWowByte[k]);
			dmw_pwint("DMW::%s: k=%u, DCCMetaBuffewSizeBytes        = %u\n",  __func__, k, p->DCCMetaBuffewSizeBytes);
			dmw_pwint("DMW::%s: k=%u, DCCMetaBuffewSizeNotExceeded  = %u\n",  __func__, k, p->DCCMetaBuffewSizeNotExceeded[k]);
#endif
		}
		s->PixewPTEBytesPewWowY[k] = s->PixewPTEBytesPewWowY[k] * (1 + 8 * s->HostVMDynamicWevews);
		s->PixewPTEBytesPewWowC[k] = s->PixewPTEBytesPewWowC[k] * (1 + 8 * s->HostVMDynamicWevews);
		p->PixewPTEBytesPewWow[k] = s->PixewPTEBytesPewWowY[k] + s->PixewPTEBytesPewWowC[k];
		if (p->use_one_wow_fow_fwame[k])
			p->PixewPTEBytesPewWow[k] = p->PixewPTEBytesPewWow[k] / 2;

		CawcuwateWowBandwidth(
			p->GPUVMEnabwe,
			p->myPipe[k].SouwcePixewFowmat,
			p->myPipe[k].VWatio,
			p->myPipe[k].VWatioChwoma,
			p->myPipe[k].DCCEnabwe,
			p->myPipe[k].HTotaw / p->myPipe[k].PixewCwock,
			s->MetaWowByteY[k],
			s->MetaWowByteC[k],
			p->meta_wow_height[k],
			p->meta_wow_height_chwoma[k],
			s->PixewPTEBytesPewWowY[k],
			s->PixewPTEBytesPewWowC[k],
			p->dpte_wow_height_wuma[k],
			p->dpte_wow_height_chwoma[k],

			// Output
			&p->meta_wow_bw[k],
			&p->dpte_wow_bw[k]);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, use_one_wow_fow_fwame = %u\n", __func__, k, p->use_one_wow_fow_fwame[k]);
		dmw_pwint("DMW::%s: k=%u, use_one_wow_fow_fwame_fwip = %u\n", __func__, k, p->use_one_wow_fow_fwame_fwip[k]);
		dmw_pwint("DMW::%s: k=%u, UseMAWWFowPStateChange = %u\n", __func__, k, p->UseMAWWFowPStateChange[k]);
		dmw_pwint("DMW::%s: k=%u, dpte_wow_height_wuma = %u\n", __func__, k, p->dpte_wow_height_wuma[k]);
		dmw_pwint("DMW::%s: k=%u, dpte_wow_width_wuma_ub = %u\n", __func__, k, p->dpte_wow_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowY = %u\n", __func__, k, s->PixewPTEBytesPewWowY[k]);
		dmw_pwint("DMW::%s: k=%u, dpte_wow_height_chwoma = %u\n", __func__, k, p->dpte_wow_height_chwoma[k]);
		dmw_pwint("DMW::%s: k=%u, dpte_wow_width_chwoma_ub = %u\n", __func__, k, p->dpte_wow_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWowC = %u\n", __func__, k, s->PixewPTEBytesPewWowC[k]);
		dmw_pwint("DMW::%s: k=%u, PixewPTEBytesPewWow = %u\n", __func__, k, p->PixewPTEBytesPewWow[k]);
		dmw_pwint("DMW::%s: k=%u, PTEBuffewSizeNotExceeded = %u\n", __func__, k, p->PTEBuffewSizeNotExceeded[k]);
		dmw_pwint("DMW::%s: k=%u, PTE_BUFFEW_MODE = %u\n", __func__, k, p->PTE_BUFFEW_MODE[k]);
		dmw_pwint("DMW::%s: k=%u, BIGK_FWAGMENT_SIZE     = %u\n", __func__, k, p->BIGK_FWAGMENT_SIZE[k]);
#endif
	}
}

static void CawcuwateOutputWink(
		dmw_fwoat_t PHYCWKPewState,
		dmw_fwoat_t PHYCWKD18PewState,
		dmw_fwoat_t PHYCWKD32PewState,
		dmw_fwoat_t Downspweading,
		dmw_boow_t IsMainSuwfaceUsingTheIndicatedTiming,
		enum dmw_output_encodew_cwass Output,
		enum dmw_output_fowmat_cwass OutputFowmat,
		dmw_uint_t HTotaw,
		dmw_uint_t HActive,
		dmw_fwoat_t PixewCwockBackEnd,
		dmw_fwoat_t FowcedOutputWinkBPP,
		dmw_uint_t DSCInputBitPewComponent,
		dmw_uint_t NumbewOfDSCSwices,
		dmw_fwoat_t AudioSampweWate,
		dmw_uint_t AudioSampweWayout,
		enum dmw_odm_mode ODMModeNoDSC,
		enum dmw_odm_mode ODMModeDSC,
		enum dmw_dsc_enabwe DSCEnabwe,
		dmw_uint_t OutputWinkDPWanes,
		enum dmw_output_wink_dp_wate OutputWinkDPWate,

		// Output
		dmw_boow_t *WequiwesDSC,
		dmw_boow_t *WequiwesFEC,
		dmw_fwoat_t *OutBpp,
		enum dmw_output_type_and_wate__type *OutputType,
		enum dmw_output_type_and_wate__wate *OutputWate,
		dmw_uint_t *WequiwedSwots)
{
	dmw_boow_t WinkDSCEnabwe;
	dmw_uint_t dummy;
	*WequiwesDSC = fawse;
	*WequiwesFEC = fawse;
	*OutBpp = 0;

	*OutputType = dmw_output_type_unknown;
	*OutputWate = dmw_output_wate_unknown;

	if (IsMainSuwfaceUsingTheIndicatedTiming) {
		if (Output == dmw_hdmi) {
			*WequiwesDSC = fawse;
			*WequiwesFEC = fawse;
			*OutBpp = TwuncToVawidBPP(dmw_min(600, PHYCWKPewState) * 10, 3, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, fawse, Output,
									OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, &dummy);
			//OutputTypeAndWate = "HDMI";
			*OutputType = dmw_output_type_hdmi;

		} ewse if (Output == dmw_dp || Output == dmw_dp2p0 || Output == dmw_edp) {
			if (DSCEnabwe == dmw_dsc_enabwe) {
				*WequiwesDSC = twue;
				WinkDSCEnabwe = twue;
				if (Output == dmw_dp || Output == dmw_dp2p0) {
					*WequiwesFEC = twue;
				} ewse {
					*WequiwesFEC = fawse;
				}
			} ewse {
				*WequiwesDSC = fawse;
				WinkDSCEnabwe = fawse;
				if (Output == dmw_dp2p0) {
					*WequiwesFEC = twue;
				} ewse {
					*WequiwesFEC = fawse;
				}
			}
			if (Output == dmw_dp2p0) {
				*OutBpp = 0;
				if ((OutputWinkDPWate == dmw_dp_wate_na || OutputWinkDPWate == dmw_dp_wate_uhbw10) && PHYCWKD32PewState >= 10000 / 32) {
					*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 10000, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					if (*OutBpp == 0 && PHYCWKD32PewState < 13500 / 32 && DSCEnabwe == dmw_dsc_enabwe_if_necessawy && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 10000, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
													OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " UHBW10";
					*OutputType = dmw_output_type_dp2p0;
					*OutputWate = dmw_output_wate_dp_wate_uhbw10;
				}
				if ((OutputWinkDPWate == dmw_dp_wate_na || OutputWinkDPWate == dmw_dp_wate_uhbw13p5) && *OutBpp == 0 && PHYCWKD32PewState >= 13500 / 32) {
					*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 13500, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);

					if (*OutBpp == 0 && PHYCWKD32PewState < 20000 / 32 && DSCEnabwe == dmw_dsc_enabwe_if_necessawy && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 13500, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " UHBW13p5";
					*OutputType = dmw_output_type_dp2p0;
					*OutputWate = dmw_output_wate_dp_wate_uhbw13p5;
				}
				if ((OutputWinkDPWate == dmw_dp_wate_na || OutputWinkDPWate == dmw_dp_wate_uhbw20) && *OutBpp == 0 && PHYCWKD32PewState >= 20000 / 32) {
					*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 20000, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
											OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					if (*OutBpp == 0 && DSCEnabwe == dmw_dsc_enabwe_if_necessawy && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 20000, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " UHBW20";
					*OutputType = dmw_output_type_dp2p0;
					*OutputWate = dmw_output_wate_dp_wate_uhbw20;
				}
			} ewse { // output is dp ow edp
				*OutBpp = 0;
				if ((OutputWinkDPWate == dmw_dp_wate_na || OutputWinkDPWate == dmw_dp_wate_hbw) && PHYCWKPewState >= 270) {
					*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 2700, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
											OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					if (*OutBpp == 0 && PHYCWKPewState < 540 && DSCEnabwe == dmw_dsc_enabwe_if_necessawy && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						if (Output == dmw_dp) {
							*WequiwesFEC = twue;
						}
						*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 2700, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " HBW";
					*OutputType = (Output == dmw_dp) ? dmw_output_type_dp : dmw_output_type_edp;
					*OutputWate = dmw_output_wate_dp_wate_hbw;
				}
				if ((OutputWinkDPWate == dmw_dp_wate_na || OutputWinkDPWate == dmw_dp_wate_hbw2) && *OutBpp == 0 && PHYCWKPewState >= 540) {
					*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 5400, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
											OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);

					if (*OutBpp == 0 && PHYCWKPewState < 810 && DSCEnabwe == dmw_dsc_enabwe_if_necessawy && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						if (Output == dmw_dp) {
							*WequiwesFEC = twue;
						}
						*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 5400, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " HBW2";
					*OutputType = (Output == dmw_dp) ? dmw_output_type_dp : dmw_output_type_edp;
					*OutputWate = dmw_output_wate_dp_wate_hbw2;
				}
				if ((OutputWinkDPWate == dmw_dp_wate_na || OutputWinkDPWate == dmw_dp_wate_hbw3) && *OutBpp == 0 && PHYCWKPewState >= 810) { // VBA_EWWOW, vba code doesn't have hbw3 check
					*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 8100, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
											OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);

					if (*OutBpp == 0 && DSCEnabwe == dmw_dsc_enabwe_if_necessawy && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						if (Output == dmw_dp) {
							*WequiwesFEC = twue;
						}
						*OutBpp = TwuncToVawidBPP((1 - Downspweading / 100) * 8100, OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd, FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
												OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices, (dmw_uint_t)AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " HBW3";
					*OutputType = (Output == dmw_dp) ? dmw_output_type_dp : dmw_output_type_edp;
					*OutputWate = dmw_output_wate_dp_wate_hbw3;
				}
			}
		}
	}
}

/// @bwief Detewmine the ODM mode and numbew of DPP used pew pwane based on dispcwk, dsc usage, odm usage powicy
static void CawcuwateODMMode(
		dmw_uint_t MaximumPixewsPewWinePewDSCUnit,
		dmw_uint_t HActive,
		enum dmw_output_encodew_cwass Output,
		enum dmw_output_fowmat_cwass OutputFowmat,
		enum dmw_odm_use_powicy ODMUse,
		dmw_fwoat_t StateDispcwk,
		dmw_fwoat_t MaxDispcwk,
		dmw_boow_t DSCEnabwe,
		dmw_uint_t TotawNumbewOfActiveDPP,
		dmw_uint_t MaxNumDPP,
		dmw_fwoat_t PixewCwock,
		dmw_fwoat_t DISPCWKDPPCWKDSCCWKDownSpweading,
		dmw_fwoat_t DISPCWKWampingMawgin,
		dmw_fwoat_t DISPCWKDPPCWKVCOSpeed,

		// Output
		dmw_boow_t *TotawAvaiwabwePipesSuppowt,
		dmw_uint_t *NumbewOfDPP,
		enum dmw_odm_mode *ODMMode,
		dmw_fwoat_t *WequiwedDISPCWKPewSuwface)
{

	dmw_fwoat_t SuwfaceWequiwedDISPCWKWithoutODMCombine;
	dmw_fwoat_t SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne;
	dmw_fwoat_t SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne;

	SuwfaceWequiwedDISPCWKWithoutODMCombine = CawcuwateWequiwedDispcwk(dmw_odm_mode_bypass, PixewCwock, DISPCWKDPPCWKDSCCWKDownSpweading, DISPCWKWampingMawgin, DISPCWKDPPCWKVCOSpeed, MaxDispcwk);
	SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne = CawcuwateWequiwedDispcwk(dmw_odm_mode_combine_2to1, PixewCwock, DISPCWKDPPCWKDSCCWKDownSpweading, DISPCWKWampingMawgin, DISPCWKDPPCWKVCOSpeed, MaxDispcwk);
	SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne = CawcuwateWequiwedDispcwk(dmw_odm_mode_combine_4to1, PixewCwock, DISPCWKDPPCWKDSCCWKDownSpweading, DISPCWKWampingMawgin, DISPCWKDPPCWKVCOSpeed, MaxDispcwk);
	*TotawAvaiwabwePipesSuppowt = twue;

	if (OutputFowmat == dmw_420) {
		if (HActive > 4 * DMW2_MAX_FMT_420_BUFFEW_WIDTH)
			*TotawAvaiwabwePipesSuppowt = fawse;
		ewse if (HActive > 2 * DMW2_MAX_FMT_420_BUFFEW_WIDTH)
			ODMUse = dmw_odm_use_powicy_combine_4to1;
		ewse if (HActive > DMW2_MAX_FMT_420_BUFFEW_WIDTH)
			ODMUse = dmw_odm_use_powicy_combine_2to1;
		if (Output == dmw_hdmi && ODMUse == dmw_odm_use_powicy_combine_2to1)
			*TotawAvaiwabwePipesSuppowt = fawse;
		if ((Output == dmw_hdmi || Output == dmw_dp || Output == dmw_edp) && ODMUse == dmw_odm_use_powicy_combine_4to1)
			*TotawAvaiwabwePipesSuppowt = fawse;
	}

	if (ODMUse == dmw_odm_use_powicy_bypass || ODMUse == dmw_odm_use_powicy_combine_as_needed)
		*ODMMode = dmw_odm_mode_bypass;
	ewse if (ODMUse == dmw_odm_use_powicy_combine_2to1)
		*ODMMode = dmw_odm_mode_combine_2to1;
	ewse if (ODMUse == dmw_odm_use_powicy_combine_4to1)
		*ODMMode = dmw_odm_mode_combine_4to1;
	ewse if (ODMUse == dmw_odm_use_powicy_spwit_1to2)
		*ODMMode = dmw_odm_mode_spwit_1to2;
	ewse if (ODMUse == dmw_odm_use_powicy_mso_1to2)
		*ODMMode = dmw_odm_mode_mso_1to2;
	ewse if (ODMUse == dmw_odm_use_powicy_mso_1to4)
		*ODMMode = dmw_odm_mode_mso_1to4;

	*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithoutODMCombine;
	*NumbewOfDPP = 0;

	if (!(Output == dmw_hdmi || Output == dmw_dp || Output == dmw_edp) && (ODMUse == dmw_odm_use_powicy_combine_4to1 || (ODMUse == dmw_odm_use_powicy_combine_as_needed &&
		(SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne > StateDispcwk || (DSCEnabwe && (HActive > 2 * MaximumPixewsPewWinePewDSCUnit)))))) {
		if (TotawNumbewOfActiveDPP + 4 <= MaxNumDPP) {
			*ODMMode = dmw_odm_mode_combine_4to1;
			*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne;
			*NumbewOfDPP = 4;
		} ewse {
			*TotawAvaiwabwePipesSuppowt = fawse;
		}
	} ewse if (Output != dmw_hdmi && (ODMUse == dmw_odm_use_powicy_combine_2to1 || (ODMUse == dmw_odm_use_powicy_combine_as_needed &&
				((SuwfaceWequiwedDISPCWKWithoutODMCombine > StateDispcwk && SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne <= StateDispcwk) ||
				(DSCEnabwe && (HActive > MaximumPixewsPewWinePewDSCUnit)))))) {
		if (TotawNumbewOfActiveDPP + 2 <= MaxNumDPP) {
			*ODMMode = dmw_odm_mode_combine_2to1;
			*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne;
			*NumbewOfDPP = 2;
		} ewse {
			*TotawAvaiwabwePipesSuppowt = fawse;
		}
	} ewse {
		if (TotawNumbewOfActiveDPP + 1 <= MaxNumDPP) {
			*NumbewOfDPP = 1;
		} ewse {
			*TotawAvaiwabwePipesSuppowt = fawse;
		}
	}
}

/// @bwief Cawcuwate the wequiwed DISPCWK given the odm mode and pixcwk
static dmw_fwoat_t CawcuwateWequiwedDispcwk(
		enum dmw_odm_mode ODMMode,
		dmw_fwoat_t PixewCwock,
		dmw_fwoat_t DISPCWKDPPCWKDSCCWKDownSpweading,
		dmw_fwoat_t DISPCWKWampingMawgin,
		dmw_fwoat_t DISPCWKDPPCWKVCOSpeed,
		dmw_fwoat_t MaxDispcwk)
{
	dmw_fwoat_t WequiwedDispcwk = 0.;
	dmw_fwoat_t PixewCwockAftewODM;

	dmw_fwoat_t DISPCWKWithWampingWoundedToDFSGwanuwawity;
	dmw_fwoat_t DISPCWKWithoutWampingWoundedToDFSGwanuwawity;
	dmw_fwoat_t MaxDispcwkWoundedDownToDFSGwanuwawity;

	if (ODMMode == dmw_odm_mode_combine_4to1) {
		PixewCwockAftewODM = PixewCwock / 4;
	} ewse if (ODMMode == dmw_odm_mode_combine_2to1) {
		PixewCwockAftewODM = PixewCwock / 2;
	} ewse {
		PixewCwockAftewODM = PixewCwock;
	}

	DISPCWKWithWampingWoundedToDFSGwanuwawity = WoundToDFSGwanuwawity(PixewCwockAftewODM * (1.0 + DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) * (1 + DISPCWKWampingMawgin / 100.0), 1, DISPCWKDPPCWKVCOSpeed);
	DISPCWKWithoutWampingWoundedToDFSGwanuwawity = WoundToDFSGwanuwawity(PixewCwockAftewODM * (1.0 + DISPCWKDPPCWKDSCCWKDownSpweading / 100.0), 1, DISPCWKDPPCWKVCOSpeed);
	MaxDispcwkWoundedDownToDFSGwanuwawity = WoundToDFSGwanuwawity(MaxDispcwk, 0, DISPCWKDPPCWKVCOSpeed);

	if (DISPCWKWithoutWampingWoundedToDFSGwanuwawity > MaxDispcwkWoundedDownToDFSGwanuwawity) {
		WequiwedDispcwk = DISPCWKWithoutWampingWoundedToDFSGwanuwawity;
	} ewse if (DISPCWKWithWampingWoundedToDFSGwanuwawity > MaxDispcwkWoundedDownToDFSGwanuwawity) {
		WequiwedDispcwk = MaxDispcwkWoundedDownToDFSGwanuwawity;
	} ewse {
		WequiwedDispcwk = DISPCWKWithWampingWoundedToDFSGwanuwawity;
	}

	wetuwn WequiwedDispcwk;
}

/// @bwief Detewmine DPPCWK if thewe onwy one DPP pew pwane, main factow is the pixew wate and DPP scawing pawametew
static void CawcuwateSingwePipeDPPCWKAndSCWThwoughput(
		dmw_fwoat_t HWatio,
		dmw_fwoat_t HWatioChwoma,
		dmw_fwoat_t VWatio,
		dmw_fwoat_t VWatioChwoma,
		dmw_fwoat_t MaxDCHUBToPSCWThwoughput,
		dmw_fwoat_t MaxPSCWToWBThwoughput,
		dmw_fwoat_t PixewCwock,
		enum dmw_souwce_fowmat_cwass SouwcePixewFowmat,
		dmw_uint_t HTaps,
		dmw_uint_t HTapsChwoma,
		dmw_uint_t VTaps,
		dmw_uint_t VTapsChwoma,

		// Output
		dmw_fwoat_t *PSCW_THWOUGHPUT,
		dmw_fwoat_t *PSCW_THWOUGHPUT_CHWOMA,
		dmw_fwoat_t *DPPCWKUsingSingweDPP)
{
	dmw_fwoat_t DPPCWKUsingSingweDPPWuma;
	dmw_fwoat_t DPPCWKUsingSingweDPPChwoma;

	if (HWatio > 1) {
		*PSCW_THWOUGHPUT = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput * HWatio / dmw_ceiw((dmw_fwoat_t) HTaps / 6.0, 1.0));
	} ewse {
		*PSCW_THWOUGHPUT = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput);
	}

	DPPCWKUsingSingweDPPWuma = PixewCwock * dmw_max3(VTaps / 6 * dmw_min(1, HWatio), HWatio * VWatio / *PSCW_THWOUGHPUT, 1);

	if ((HTaps > 6 || VTaps > 6) && DPPCWKUsingSingweDPPWuma < 2 * PixewCwock)
		DPPCWKUsingSingweDPPWuma = 2 * PixewCwock;

	if ((SouwcePixewFowmat != dmw_420_8 && SouwcePixewFowmat != dmw_420_10 && SouwcePixewFowmat != dmw_420_12 && SouwcePixewFowmat != dmw_wgbe_awpha)) {
		*PSCW_THWOUGHPUT_CHWOMA = 0;
		*DPPCWKUsingSingweDPP = DPPCWKUsingSingweDPPWuma;
	} ewse {
		if (HWatioChwoma > 1) {
			*PSCW_THWOUGHPUT_CHWOMA = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput * HWatioChwoma / dmw_ceiw((dmw_fwoat_t) HTapsChwoma / 6.0, 1.0));
		} ewse {
			*PSCW_THWOUGHPUT_CHWOMA = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput);
		}
		DPPCWKUsingSingweDPPChwoma = PixewCwock * dmw_max3(VTapsChwoma / 6 * dmw_min(1, HWatioChwoma),
															HWatioChwoma * VWatioChwoma / *PSCW_THWOUGHPUT_CHWOMA, 1);
		if ((HTapsChwoma > 6 || VTapsChwoma > 6) && DPPCWKUsingSingweDPPChwoma < 2 * PixewCwock)
			DPPCWKUsingSingweDPPChwoma = 2 * PixewCwock;
		*DPPCWKUsingSingweDPP = dmw_max(DPPCWKUsingSingweDPPWuma, DPPCWKUsingSingweDPPChwoma);
	}
}

/// @bwief Cawcuwate the actuaw dppcwk fweq
/// @pawam DPPCWKUsingSingweDPP DppCwk fweq wequiwed if thewe is onwy 1 DPP pew pwane
/// @pawam DPPPewSuwface Numbew of DPP fow each pwane
static void CawcuwateDPPCWK(
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_fwoat_t DISPCWKDPPCWKDSCCWKDownSpweading,
		dmw_fwoat_t DISPCWKDPPCWKVCOSpeed,
		dmw_fwoat_t DPPCWKUsingSingweDPP[],
		dmw_uint_t DPPPewSuwface[],

		// Output
		dmw_fwoat_t *GwobawDPPCWK,
		dmw_fwoat_t Dppcwk[])
{
	*GwobawDPPCWK = 0;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		Dppcwk[k] = DPPCWKUsingSingweDPP[k] / DPPPewSuwface[k] * (1 + DISPCWKDPPCWKDSCCWKDownSpweading / 100.0);
		*GwobawDPPCWK = dmw_max(*GwobawDPPCWK, Dppcwk[k]);
	}
	*GwobawDPPCWK = WoundToDFSGwanuwawity(*GwobawDPPCWK, 1, DISPCWKDPPCWKVCOSpeed);

	dmw_pwint("DMW::%s: GwobawDPPCWK = %f\n", __func__, *GwobawDPPCWK);
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		Dppcwk[k] = *GwobawDPPCWK / 255.0 * dmw_ceiw(Dppcwk[k] * 255.0 / *GwobawDPPCWK, 1.0);
		dmw_pwint("DMW::%s: Dppcwk[%0d] = %f\n", __func__, k, Dppcwk[k]);
	}
}

static void CawcuwateMAWWUseFowStaticScween(
		dmw_uint_t NumbewOfActiveSuwfaces,
		dmw_uint_t MAWWAwwocatedFowDCNFinaw,
		enum dmw_use_maww_fow_static_scween_mode *UseMAWWFowStaticScween,
		dmw_uint_t SuwfaceSizeInMAWW[],
		dmw_boow_t one_wow_pew_fwame_fits_in_buffew[],

		// Output
		dmw_boow_t UsesMAWWFowStaticScween[])
{

	dmw_uint_t SuwfaceToAddToMAWW;
	dmw_boow_t CanAddAnothewSuwfaceToMAWW;
	dmw_uint_t TotawSuwfaceSizeInMAWW;

	TotawSuwfaceSizeInMAWW = 0;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		UsesMAWWFowStaticScween[k] = (UseMAWWFowStaticScween[k] == dmw_use_maww_static_scween_enabwe);
		if (UsesMAWWFowStaticScween[k])
			TotawSuwfaceSizeInMAWW = TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[k];
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, UsesMAWWFowStaticScween = %u\n",  __func__, k, UsesMAWWFowStaticScween[k]);
		dmw_pwint("DMW::%s: k=%u, TotawSuwfaceSizeInMAWW = %u\n",  __func__, k, TotawSuwfaceSizeInMAWW);
#endif
	}

	SuwfaceToAddToMAWW = 0;
	CanAddAnothewSuwfaceToMAWW = twue;
	whiwe (CanAddAnothewSuwfaceToMAWW) {
		CanAddAnothewSuwfaceToMAWW = fawse;
		fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			if (TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[k] <= MAWWAwwocatedFowDCNFinaw * 1024 * 1024 &&
				!UsesMAWWFowStaticScween[k] && UseMAWWFowStaticScween[k] != dmw_use_maww_static_scween_disabwe && one_wow_pew_fwame_fits_in_buffew[k] &&
				(!CanAddAnothewSuwfaceToMAWW || SuwfaceSizeInMAWW[k] < SuwfaceSizeInMAWW[SuwfaceToAddToMAWW])) {
				CanAddAnothewSuwfaceToMAWW = twue;
				SuwfaceToAddToMAWW = k;
				dmw_pwint("DMW::%s: k=%u, UseMAWWFowStaticScween = %u (dis, en, optimize)\n",  __func__, k, UseMAWWFowStaticScween[k]);
			}
		}
		if (CanAddAnothewSuwfaceToMAWW) {
			UsesMAWWFowStaticScween[SuwfaceToAddToMAWW] = twue;
			TotawSuwfaceSizeInMAWW = TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[SuwfaceToAddToMAWW];

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: SuwfaceToAddToMAWW       = %u\n",  __func__, SuwfaceToAddToMAWW);
			dmw_pwint("DMW::%s: TotawSuwfaceSizeInMAWW   = %u\n",  __func__, TotawSuwfaceSizeInMAWW);
#endif
		}
	}
}

// @bwief Cawcuwate wetuwn bw fow VM onwy twaffic
dmw_fwoat_t dmw_get_wetuwn_bw_mbps_vm_onwy(
								const stwuct soc_bounding_box_st *soc,
								dmw_boow_t use_ideaw_dwam_bw_stwobe,
								dmw_boow_t HostVMEnabwe,
								dmw_fwoat_t DCFCWK,
								dmw_fwoat_t FabwicCwock,
								dmw_fwoat_t DWAMSpeed)
{
	dmw_fwoat_t VMDataOnwyWetuwnBW =
		dmw_min3(soc->wetuwn_bus_width_bytes * DCFCWK * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100.0,
				FabwicCwock * soc->fabwic_datapath_to_dcn_data_wetuwn_bytes * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100.0,
				DWAMSpeed * soc->num_chans *  soc->dwam_channew_width_bytes *
				((use_ideaw_dwam_bw_stwobe && !HostVMEnabwe) ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :  soc->pct_ideaw_dwam_bw_aftew_uwgent_vm_onwy) / 100.0);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: use_ideaw_dwam_bw_stwobe = %u\n", __func__, use_ideaw_dwam_bw_stwobe);
	dmw_pwint("DMW::%s: HostVMEnabwe = %u\n", __func__, HostVMEnabwe);
	dmw_pwint("DMW::%s: DCFCWK = %f\n", __func__, DCFCWK);
	dmw_pwint("DMW::%s: FabwicCwock = %f\n", __func__, FabwicCwock);
	dmw_pwint("DMW::%s: DWAMSpeed = %f\n", __func__, DWAMSpeed);
	dmw_pwint("DMW::%s: VMDataOnwyWetuwnBW = %f\n", __func__, VMDataOnwyWetuwnBW);
#endif
	wetuwn VMDataOnwyWetuwnBW;
}

// Function: dmw_get_wetuwn_bw_mbps
// Megabyte pew second
dmw_fwoat_t dmw_get_wetuwn_bw_mbps(
						const stwuct soc_bounding_box_st *soc,
						dmw_boow_t use_ideaw_dwam_bw_stwobe,
						dmw_boow_t HostVMEnabwe,
						dmw_fwoat_t DCFCWK,
						dmw_fwoat_t FabwicCwock,
						dmw_fwoat_t DWAMSpeed)
{
	dmw_fwoat_t WetuwnBW = 0.;
	dmw_fwoat_t IdeawSDPPowtBandwidth    = soc->wetuwn_bus_width_bytes * DCFCWK;
	dmw_fwoat_t IdeawFabwicBandwidth     = FabwicCwock * soc->fabwic_datapath_to_dcn_data_wetuwn_bytes;
	dmw_fwoat_t IdeawDWAMBandwidth       = DWAMSpeed * soc->num_chans * soc->dwam_channew_width_bytes;
	dmw_fwoat_t PixewDataOnwyWetuwnBW    = dmw_min3(IdeawSDPPowtBandwidth * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100,
												IdeawFabwicBandwidth * soc->pct_ideaw_fabwic_bw_aftew_uwgent / 100,
												IdeawDWAMBandwidth * ((use_ideaw_dwam_bw_stwobe && !HostVMEnabwe) ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :
																						soc->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy) / 100);
	dmw_fwoat_t PixewMixedWithVMDataWetuwnBW = dmw_min3(IdeawSDPPowtBandwidth * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100,
													IdeawFabwicBandwidth * soc->pct_ideaw_fabwic_bw_aftew_uwgent / 100,
													IdeawDWAMBandwidth * ((use_ideaw_dwam_bw_stwobe && !HostVMEnabwe) ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :
																							soc->pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm) / 100);

	if (HostVMEnabwe != twue) {
		WetuwnBW = PixewDataOnwyWetuwnBW;
	} ewse {
		WetuwnBW = PixewMixedWithVMDataWetuwnBW;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: use_ideaw_dwam_bw_stwobe = %u\n", __func__, use_ideaw_dwam_bw_stwobe);
	dmw_pwint("DMW::%s: HostVMEnabwe = %u\n", __func__, HostVMEnabwe);
	dmw_pwint("DMW::%s: DCFCWK = %f\n", __func__, DCFCWK);
	dmw_pwint("DMW::%s: FabwicCwock = %f\n", __func__, FabwicCwock);
	dmw_pwint("DMW::%s: DWAMSpeed = %f\n", __func__, DWAMSpeed);
	dmw_pwint("DMW::%s: IdeawSDPPowtBandwidth = %f\n", __func__, IdeawSDPPowtBandwidth);
	dmw_pwint("DMW::%s: IdeawFabwicBandwidth = %f\n", __func__, IdeawFabwicBandwidth);
	dmw_pwint("DMW::%s: IdeawDWAMBandwidth = %f\n", __func__, IdeawDWAMBandwidth);
	dmw_pwint("DMW::%s: PixewDataOnwyWetuwnBW = %f\n", __func__, PixewDataOnwyWetuwnBW);
	dmw_pwint("DMW::%s: PixewMixedWithVMDataWetuwnBW = %f\n", __func__, PixewMixedWithVMDataWetuwnBW);
	dmw_pwint("DMW::%s: WetuwnBW                  = %f MBps\n", __func__, WetuwnBW);
#endif
	wetuwn WetuwnBW;
}

// Function: dmw_get_wetuwn_dwam_bw_mbps
// Megabyte pew second
static dmw_fwoat_t dmw_get_wetuwn_dwam_bw_mbps(
						const stwuct soc_bounding_box_st *soc,
						dmw_boow_t use_ideaw_dwam_bw_stwobe,
						dmw_boow_t HostVMEnabwe,
						dmw_fwoat_t DWAMSpeed)
{
	dmw_fwoat_t WetuwnDWAMBW = 0.;
	dmw_fwoat_t IdeawDWAMBandwidth       = DWAMSpeed * soc->num_chans * soc->dwam_channew_width_bytes;
	dmw_fwoat_t PixewDataOnwyWetuwnBW    = IdeawDWAMBandwidth * ((use_ideaw_dwam_bw_stwobe && !HostVMEnabwe) ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :
																						soc->pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy) / 100;
	dmw_fwoat_t PixewMixedWithVMDataWetuwnBW =  IdeawDWAMBandwidth * ((use_ideaw_dwam_bw_stwobe && !HostVMEnabwe) ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :
																							soc->pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm) / 100;

	if (HostVMEnabwe != twue) {
		WetuwnDWAMBW = PixewDataOnwyWetuwnBW;
	} ewse {
		WetuwnDWAMBW = PixewMixedWithVMDataWetuwnBW;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: use_ideaw_dwam_bw_stwobe = %u\n", __func__, use_ideaw_dwam_bw_stwobe);
	dmw_pwint("DMW::%s: HostVMEnabwe = %u\n", __func__, HostVMEnabwe);
	dmw_pwint("DMW::%s: DWAMSpeed = %f\n", __func__, DWAMSpeed);
	dmw_pwint("DMW::%s: IdeawDWAMBandwidth = %f\n", __func__, IdeawDWAMBandwidth);
	dmw_pwint("DMW::%s: PixewDataOnwyWetuwnBW = %f\n", __func__, PixewDataOnwyWetuwnBW);
	dmw_pwint("DMW::%s: PixewMixedWithVMDataWetuwnBW = %f\n", __func__, PixewMixedWithVMDataWetuwnBW);
	dmw_pwint("DMW::%s: WetuwnDWAMBW                     = %f MBps\n", __func__, WetuwnDWAMBW);
#endif
	wetuwn WetuwnDWAMBW;
}

/// @bwief BACKEND
static dmw_uint_t DSCDewayWequiwement(
						dmw_boow_t DSCEnabwed,
						enum dmw_odm_mode ODMMode,
						dmw_uint_t DSCInputBitPewComponent,
						dmw_fwoat_t OutputBpp,
						dmw_uint_t HActive,
						dmw_uint_t HTotaw,
						dmw_uint_t NumbewOfDSCSwices,
						enum dmw_output_fowmat_cwass OutputFowmat,
						enum dmw_output_encodew_cwass Output,
						dmw_fwoat_t PixewCwock,
						dmw_fwoat_t PixewCwockBackEnd)
{
	dmw_uint_t DSCDewayWequiwement_vaw = 0;

	if (DSCEnabwed == twue && OutputBpp != 0) {
		if (ODMMode == dmw_odm_mode_combine_4to1) {
			DSCDewayWequiwement_vaw = 4 * (dscceComputeDeway(DSCInputBitPewComponent, OutputBpp, (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) HActive / (dmw_fwoat_t) NumbewOfDSCSwices, 1.0)),
												(dmw_uint_t) (NumbewOfDSCSwices / 4.0), OutputFowmat, Output) + dscComputeDeway(OutputFowmat, Output));
		} ewse if (ODMMode == dmw_odm_mode_combine_2to1) {
			DSCDewayWequiwement_vaw = 2 * (dscceComputeDeway(DSCInputBitPewComponent, OutputBpp, (dmw_uint_t)(dmw_ceiw((dmw_fwoat_t) HActive / (dmw_fwoat_t) NumbewOfDSCSwices, 1.0)),
												(dmw_uint_t) (NumbewOfDSCSwices / 2.0), OutputFowmat, Output) + dscComputeDeway(OutputFowmat, Output));
		} ewse {
			DSCDewayWequiwement_vaw = dscceComputeDeway(DSCInputBitPewComponent, OutputBpp, (dmw_uint_t)((dmw_fwoat_t) dmw_ceiw(HActive / (dmw_fwoat_t) NumbewOfDSCSwices, 1.0)),
										NumbewOfDSCSwices, OutputFowmat, Output) + dscComputeDeway(OutputFowmat, Output);
		}
		DSCDewayWequiwement_vaw = (dmw_uint_t)(DSCDewayWequiwement_vaw + (HTotaw - HActive) * dmw_ceiw((dmw_fwoat_t) DSCDewayWequiwement_vaw / (dmw_fwoat_t) HActive, 1.0));
		DSCDewayWequiwement_vaw = (dmw_uint_t)(DSCDewayWequiwement_vaw * PixewCwock / PixewCwockBackEnd);

	} ewse {
		DSCDewayWequiwement_vaw = 0;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DSCEnabwed = %u\n", __func__, DSCEnabwed);
	dmw_pwint("DMW::%s: ODMMode = %u\n", __func__, ODMMode);
	dmw_pwint("DMW::%s: OutputBpp = %f\n", __func__, OutputBpp);
	dmw_pwint("DMW::%s: HActive = %u\n", __func__, HActive);
	dmw_pwint("DMW::%s: HTotaw = %u\n", __func__, HTotaw);
	dmw_pwint("DMW::%s: PixewCwock = %f\n", __func__, PixewCwock);
	dmw_pwint("DMW::%s: PixewCwockBackEnd = %f\n", __func__, PixewCwockBackEnd);
	dmw_pwint("DMW::%s: OutputFowmat = %u\n", __func__, OutputFowmat);
	dmw_pwint("DMW::%s: DSCInputBitPewComponent = %u\n", __func__, DSCInputBitPewComponent);
	dmw_pwint("DMW::%s: NumbewOfDSCSwices = %u\n", __func__, NumbewOfDSCSwices);
	dmw_pwint("DMW::%s: DSCDewayWequiwement_vaw = %u\n", __func__, DSCDewayWequiwement_vaw);
#endif

	wetuwn DSCDewayWequiwement_vaw;
}

static dmw_boow_t CawcuwateVActiveBandwithSuppowt(dmw_uint_t NumbewOfActiveSuwfaces,
										dmw_fwoat_t WetuwnBW,
										dmw_boow_t NotUwgentWatencyHiding[],
										dmw_fwoat_t WeadBandwidthWuma[],
										dmw_fwoat_t WeadBandwidthChwoma[],
										dmw_fwoat_t cuwsow_bw[],
										dmw_fwoat_t meta_wow_bandwidth[],
										dmw_fwoat_t dpte_wow_bandwidth[],
										dmw_uint_t NumbewOfDPP[],
										dmw_fwoat_t UwgentBuwstFactowWuma[],
										dmw_fwoat_t UwgentBuwstFactowChwoma[],
										dmw_fwoat_t UwgentBuwstFactowCuwsow[])
{
	dmw_boow_t NotEnoughUwgentWatencyHiding = fawse;
	dmw_boow_t CawcuwateVActiveBandwithSuppowt_vaw = fawse;
	dmw_fwoat_t VActiveBandwith = 0;

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (NotUwgentWatencyHiding[k]) {
			NotEnoughUwgentWatencyHiding = twue;
		}
	}

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		VActiveBandwith = VActiveBandwith + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k] + NumbewOfDPP[k] * meta_wow_bandwidth[k] + NumbewOfDPP[k] * dpte_wow_bandwidth[k];
	}

	CawcuwateVActiveBandwithSuppowt_vaw = (VActiveBandwith <= WetuwnBW) && !NotEnoughUwgentWatencyHiding;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: NotEnoughUwgentWatencyHiding        = %u\n", __func__, NotEnoughUwgentWatencyHiding);
	dmw_pwint("DMW::%s: VActiveBandwith                     = %f\n", __func__, VActiveBandwith);
	dmw_pwint("DMW::%s: WetuwnBW                            = %f\n", __func__, WetuwnBW);
	dmw_pwint("DMW::%s: CawcuwateVActiveBandwithSuppowt_vaw = %u\n", __func__, CawcuwateVActiveBandwithSuppowt_vaw);
#endif
	wetuwn CawcuwateVActiveBandwithSuppowt_vaw;
}

static void CawcuwatePwefetchBandwithSuppowt(
										dmw_uint_t NumbewOfActiveSuwfaces,
										dmw_fwoat_t WetuwnBW,
										enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
										dmw_boow_t NotUwgentWatencyHiding[],
										dmw_fwoat_t WeadBandwidthWuma[],
										dmw_fwoat_t WeadBandwidthChwoma[],
										dmw_fwoat_t PwefetchBandwidthWuma[],
										dmw_fwoat_t PwefetchBandwidthChwoma[],
										dmw_fwoat_t cuwsow_bw[],
										dmw_fwoat_t meta_wow_bandwidth[],
										dmw_fwoat_t dpte_wow_bandwidth[],
										dmw_fwoat_t cuwsow_bw_pwe[],
										dmw_fwoat_t pwefetch_vmwow_bw[],
										dmw_uint_t NumbewOfDPP[],
										dmw_fwoat_t UwgentBuwstFactowWuma[],
										dmw_fwoat_t UwgentBuwstFactowChwoma[],
										dmw_fwoat_t UwgentBuwstFactowCuwsow[],
										dmw_fwoat_t UwgentBuwstFactowWumaPwe[],
										dmw_fwoat_t UwgentBuwstFactowChwomaPwe[],
										dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[],

										// Output
										dmw_fwoat_t *PwefetchBandwidth,
										dmw_fwoat_t *PwefetchBandwidthNotIncwudingMAWWPwefetch,
										dmw_fwoat_t *FwactionOfUwgentBandwidth,
										dmw_boow_t *PwefetchBandwidthSuppowt)
{
	dmw_boow_t NotEnoughUwgentWatencyHiding = fawse;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (NotUwgentWatencyHiding[k]) {
			NotEnoughUwgentWatencyHiding = twue;
		}
	}

	*PwefetchBandwidth = 0;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		*PwefetchBandwidth = *PwefetchBandwidth + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
														WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k] + NumbewOfDPP[k] * (meta_wow_bandwidth[k] + dpte_wow_bandwidth[k]),
														NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
	}

	*PwefetchBandwidthNotIncwudingMAWWPwefetch = 0;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe)
			*PwefetchBandwidthNotIncwudingMAWWPwefetch = *PwefetchBandwidthNotIncwudingMAWWPwefetch
				+ dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
				WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k]
				+ cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k]
				+ NumbewOfDPP[k] * (meta_wow_bandwidth[k] + dpte_wow_bandwidth[k]),
				NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k]
				+ PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k])
				+ cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
	}

	*PwefetchBandwidthSuppowt = (*PwefetchBandwidth <= WetuwnBW) && !NotEnoughUwgentWatencyHiding;
	*FwactionOfUwgentBandwidth = *PwefetchBandwidth / WetuwnBW;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WetuwnBW = %f\n", __func__, WetuwnBW);
	dmw_pwint("DMW::%s: PwefetchBandwidth = %f\n", __func__, *PwefetchBandwidth);
	dmw_pwint("DMW::%s: FwactionOfUwgentBandwidth = %f\n", __func__, *FwactionOfUwgentBandwidth);
   dmw_pwint("DMW::%s: PwefetchBandwidthSuppowt = %u\n", __func__, *PwefetchBandwidthSuppowt);
#endif
}

static dmw_fwoat_t CawcuwateBandwidthAvaiwabweFowImmediateFwip(
													dmw_uint_t NumbewOfActiveSuwfaces,
													dmw_fwoat_t WetuwnBW,
													dmw_fwoat_t WeadBandwidthWuma[],
													dmw_fwoat_t WeadBandwidthChwoma[],
													dmw_fwoat_t PwefetchBandwidthWuma[],
													dmw_fwoat_t PwefetchBandwidthChwoma[],
													dmw_fwoat_t cuwsow_bw[],
													dmw_fwoat_t cuwsow_bw_pwe[],
													dmw_uint_t NumbewOfDPP[],
													dmw_fwoat_t UwgentBuwstFactowWuma[],
													dmw_fwoat_t UwgentBuwstFactowChwoma[],
													dmw_fwoat_t UwgentBuwstFactowCuwsow[],
													dmw_fwoat_t UwgentBuwstFactowWumaPwe[],
													dmw_fwoat_t UwgentBuwstFactowChwomaPwe[],
													dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[])
{
	dmw_fwoat_t wet_vaw = WetuwnBW;

	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		wet_vaw = wet_vaw - dmw_max(WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
									NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) +
									cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u\n", __func__, k);
		dmw_pwint("DMW::%s: NumbewOfDPP = %u\n", __func__, NumbewOfDPP[k]);
		dmw_pwint("DMW::%s: WeadBandwidthWuma = %f\n", __func__, WeadBandwidthWuma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowWuma = %f\n", __func__, UwgentBuwstFactowWuma[k]);
		dmw_pwint("DMW::%s: WeadBandwidthChwoma = %f\n", __func__, WeadBandwidthChwoma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowChwoma = %f\n", __func__, UwgentBuwstFactowChwoma[k]);
		dmw_pwint("DMW::%s: cuwsow_bw = %f\n", __func__, cuwsow_bw[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowCuwsow = %f\n", __func__, UwgentBuwstFactowCuwsow[k]);

		dmw_pwint("DMW::%s: PwefetchBandwidthWuma = %f\n", __func__, PwefetchBandwidthWuma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowWumaPwe = %f\n", __func__, UwgentBuwstFactowWumaPwe[k]);
		dmw_pwint("DMW::%s: PwefetchBandwidthChwoma = %f\n", __func__, PwefetchBandwidthChwoma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowChwomaPwe = %f\n", __func__, UwgentBuwstFactowChwomaPwe[k]);
		dmw_pwint("DMW::%s: cuwsow_bw_pwe = %f\n", __func__, cuwsow_bw_pwe[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowCuwsowPwe = %f\n", __func__, UwgentBuwstFactowCuwsowPwe[k]);
		dmw_pwint("DMW::%s: wet_vaw              = %f\n", __func__, wet_vaw);
#endif
	}

	wetuwn wet_vaw;
}

static void CawcuwateImmediateFwipBandwithSuppowt(
											dmw_uint_t NumbewOfActiveSuwfaces,
											dmw_fwoat_t WetuwnBW,
											enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
											enum dmw_immediate_fwip_wequiwement ImmediateFwipWequiwement[],
											dmw_fwoat_t finaw_fwip_bw[],
											dmw_fwoat_t WeadBandwidthWuma[],
											dmw_fwoat_t WeadBandwidthChwoma[],
											dmw_fwoat_t PwefetchBandwidthWuma[],
											dmw_fwoat_t PwefetchBandwidthChwoma[],
											dmw_fwoat_t cuwsow_bw[],
											dmw_fwoat_t meta_wow_bandwidth[],
											dmw_fwoat_t dpte_wow_bandwidth[],
											dmw_fwoat_t cuwsow_bw_pwe[],
											dmw_fwoat_t pwefetch_vmwow_bw[],
											dmw_uint_t NumbewOfDPP[],
											dmw_fwoat_t UwgentBuwstFactowWuma[],
											dmw_fwoat_t UwgentBuwstFactowChwoma[],
											dmw_fwoat_t UwgentBuwstFactowCuwsow[],
											dmw_fwoat_t UwgentBuwstFactowWumaPwe[],
											dmw_fwoat_t UwgentBuwstFactowChwomaPwe[],
											dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[],

											// Output
											dmw_fwoat_t *TotawBandwidth,
											dmw_fwoat_t *TotawBandwidthNotIncwudingMAWWPwefetch,
											dmw_fwoat_t *FwactionOfUwgentBandwidth,
											dmw_boow_t *ImmediateFwipBandwidthSuppowt)
{
	*TotawBandwidth = 0;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (ImmediateFwipWequiwement[k] != dmw_immediate_fwip_not_wequiwed) {



			*TotawBandwidth = *TotawBandwidth + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
														NumbewOfDPP[k] * finaw_fwip_bw[k] + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
														NumbewOfDPP[k] * (finaw_fwip_bw[k] + PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
		} ewse {
			*TotawBandwidth = *TotawBandwidth + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
														NumbewOfDPP[k] * (meta_wow_bandwidth[k] + dpte_wow_bandwidth[k]) + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
														NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k = %u\n", __func__, k);
		dmw_pwint("DMW::%s: ImmediateFwipWequiwement = %u\n", __func__, ImmediateFwipWequiwement[k]);
		dmw_pwint("DMW::%s: TotawBandwidth = %f\n", __func__, *TotawBandwidth);
		dmw_pwint("DMW::%s: NumbewOfDPP = %u\n", __func__, NumbewOfDPP[k]);
		dmw_pwint("DMW::%s: pwefetch_vmwow_bw = %f\n", __func__, pwefetch_vmwow_bw[k]);
		dmw_pwint("DMW::%s: finaw_fwip_bw = %f\n", __func__, finaw_fwip_bw[k]);
		dmw_pwint("DMW::%s: WeadBandwidthWuma = %f\n", __func__, WeadBandwidthWuma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowWuma = %f\n", __func__, UwgentBuwstFactowWuma[k]);
		dmw_pwint("DMW::%s: WeadBandwidthChwoma = %f\n", __func__, WeadBandwidthChwoma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowChwoma = %f\n", __func__, UwgentBuwstFactowChwoma[k]);
		dmw_pwint("DMW::%s: cuwsow_bw = %f\n", __func__, cuwsow_bw[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowCuwsow = %f\n", __func__, UwgentBuwstFactowCuwsow[k]);
		dmw_pwint("DMW::%s: PwefetchBandwidthWuma = %f\n", __func__, PwefetchBandwidthWuma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowWumaPwe = %f\n", __func__, UwgentBuwstFactowWumaPwe[k]);
		dmw_pwint("DMW::%s: PwefetchBandwidthChwoma = %f\n", __func__, PwefetchBandwidthChwoma[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowChwomaPwe = %f\n", __func__, UwgentBuwstFactowChwomaPwe[k]);
		dmw_pwint("DMW::%s: cuwsow_bw_pwe = %f\n", __func__, cuwsow_bw_pwe[k]);
		dmw_pwint("DMW::%s: UwgentBuwstFactowCuwsowPwe = %f\n", __func__, UwgentBuwstFactowCuwsowPwe[k]);
		dmw_pwint("DMW::%s: meta_wow_bandwidth = %f\n", __func__, meta_wow_bandwidth[k]);
		dmw_pwint("DMW::%s: dpte_wow_bandwidth          = %f\n", __func__, dpte_wow_bandwidth[k]);
#endif
	}

	*TotawBandwidthNotIncwudingMAWWPwefetch = 0;
	fow (dmw_uint_t k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) {
			if (ImmediateFwipWequiwement[k] != dmw_immediate_fwip_not_wequiwed)
				*TotawBandwidthNotIncwudingMAWWPwefetch = *TotawBandwidthNotIncwudingMAWWPwefetch + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
					NumbewOfDPP[k] * finaw_fwip_bw[k] + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
					NumbewOfDPP[k] * (finaw_fwip_bw[k] + PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k])
					+ cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
			ewse
				*TotawBandwidthNotIncwudingMAWWPwefetch = *TotawBandwidthNotIncwudingMAWWPwefetch + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
					NumbewOfDPP[k] * (meta_wow_bandwidth[k] + dpte_wow_bandwidth[k])
					+ WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
					NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k])
					+ cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
		}
	}

	*ImmediateFwipBandwidthSuppowt = (*TotawBandwidth <= WetuwnBW);
	*FwactionOfUwgentBandwidth = *TotawBandwidth / WetuwnBW;
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WetuwnBW = %f\n", __func__, WetuwnBW);
	dmw_pwint("DMW::%s: TotawBandwidth = %f\n", __func__, *TotawBandwidth);
	dmw_pwint("DMW::%s: ImmediateFwipBandwidthSuppowt = %u\n", __func__, *ImmediateFwipBandwidthSuppowt);
#endif
}

static dmw_uint_t MicwoSecToVewtWines(dmw_uint_t num_us, dmw_uint_t h_totaw, dmw_fwoat_t pixew_cwock)
{
	dmw_uint_t wines_time_in_ns = 1000.0 * (h_totaw * 1000.0) / (pixew_cwock * 1000.0);

	wetuwn dmw_ceiw(1000.0 * num_us / wines_time_in_ns, 1.0);
}

/// @bwief Cawcuwate the maximum vstawtup fow mode suppowt and mode pwogwamming considewation
///         Bounded by min of actuaw vbwank and input vbwank_nom, dont want vstawtup/weady to stawt too eawwy if actuaw vbwwank is huge
static dmw_uint_t CawcuwateMaxVStawtup(
			dmw_uint_t          pwane_idx,
			dmw_boow_t          ptoi_suppowted,
			dmw_uint_t          vbwank_nom_defauwt_us,
			stwuct dmw_timing_cfg_st  *timing,
			dmw_fwoat_t         wwite_back_deway_us)
{
	dmw_uint_t vbwank_size = 0;
	dmw_uint_t max_vstawtup_wines = 0;
	const dmw_uint_t max_awwowed_vbwank_nom = 1023;

	dmw_fwoat_t wine_time_us = (dmw_fwoat_t) timing->HTotaw[pwane_idx] / timing->PixewCwock[pwane_idx];
	dmw_uint_t vbwank_actuaw = timing->VTotaw[pwane_idx] - timing->VActive[pwane_idx];

	dmw_uint_t vbwank_nom_defauwt_in_wine = MicwoSecToVewtWines(vbwank_nom_defauwt_us, timing->HTotaw[pwane_idx],
			timing->PixewCwock[pwane_idx]);
	dmw_uint_t vbwank_nom_input = (dmw_uint_t)dmw_min(vbwank_actuaw, vbwank_nom_defauwt_in_wine);

	// vbwank_nom shouwd not be smawwew than (VSync (VTotaw - VActive - VFwontPowch) + 2)
	// + 2 is because
	// 1 -> VStawtup_stawt shouwd be 1 wine befowe VSync
	// 1 -> awways wesewve 1 wine between stawt of VBwank to VStawtup signaw
	dmw_uint_t vbwank_nom_vsync_capped = dmw_max(vbwank_nom_input,
			timing->VTotaw[pwane_idx] - timing->VActive[pwane_idx] - timing->VFwontPowch[pwane_idx] + 2);
	dmw_uint_t vbwank_nom_max_awwowed_capped = dmw_min(vbwank_nom_vsync_capped, max_awwowed_vbwank_nom);
	dmw_uint_t vbwank_avaiw = (vbwank_nom_max_awwowed_capped == 0) ?
			vbwank_nom_defauwt_in_wine : vbwank_nom_max_awwowed_capped;

	vbwank_size = (dmw_uint_t) dmw_min(vbwank_actuaw, vbwank_avaiw);

   if (timing->Intewwace[pwane_idx] && !ptoi_suppowted)
		max_vstawtup_wines = (dmw_uint_t) (dmw_fwoow(vbwank_size/2.0, 1.0));
	ewse
		max_vstawtup_wines = vbwank_size - (dmw_uint_t) dmw_max(1.0, dmw_ceiw(wwite_back_deway_us/wine_time_us, 1.0));
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: pwane_idx = %u\n", __func__, pwane_idx);
	dmw_pwint("DMW::%s: VBwankNom = %u\n", __func__, timing->VBwankNom[pwane_idx]);
	dmw_pwint("DMW::%s: vbwank_nom_defauwt_us = %u\n", __func__, vbwank_nom_defauwt_us);
	dmw_pwint("DMW::%s: wine_time_us = %f\n", __func__, wine_time_us);
	dmw_pwint("DMW::%s: vbwank_actuaw = %u\n", __func__, vbwank_actuaw);
	dmw_pwint("DMW::%s: vbwank_avaiw = %u\n", __func__, vbwank_avaiw);
	dmw_pwint("DMW::%s: max_vstawtup_wines = %u\n", __func__, max_vstawtup_wines);
#endif
	wetuwn max_vstawtup_wines;
}

static void set_cawcuwate_pwefetch_scheduwe_pawams(stwuct dispway_mode_wib_st *mode_wib,
						   stwuct CawcuwatePwefetchScheduwe_pawams_st *CawcuwatePwefetchScheduwe_pawams,
						   dmw_uint_t j,
						   dmw_uint_t k)
{
				CawcuwatePwefetchScheduwe_pawams->DSCDeway = mode_wib->ms.DSCDewayPewState[k];
				CawcuwatePwefetchScheduwe_pawams->EnhancedPwefetchScheduweAccewewationFinaw = mode_wib->ms.powicy.EnhancedPwefetchScheduweAccewewationFinaw;
				CawcuwatePwefetchScheduwe_pawams->DPPCWKDewaySubtotawPwusCNVCFowmatew = mode_wib->ms.ip.dppcwk_deway_subtotaw + mode_wib->ms.ip.dppcwk_deway_cnvc_fowmattew;
				CawcuwatePwefetchScheduwe_pawams->DPPCWKDewaySCW = mode_wib->ms.ip.dppcwk_deway_scw;
				CawcuwatePwefetchScheduwe_pawams->DPPCWKDewaySCWWBOnwy = mode_wib->ms.ip.dppcwk_deway_scw_wb_onwy;
				CawcuwatePwefetchScheduwe_pawams->DPPCWKDewayCNVCCuwsow = mode_wib->ms.ip.dppcwk_deway_cnvc_cuwsow;
				CawcuwatePwefetchScheduwe_pawams->DISPCWKDewaySubtotaw = mode_wib->ms.ip.dispcwk_deway_subtotaw;
				CawcuwatePwefetchScheduwe_pawams->DPP_WECOUT_WIDTH = (dmw_uint_t)(mode_wib->ms.SwathWidthYThisState[k] / mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k]);
				CawcuwatePwefetchScheduwe_pawams->OutputFowmat = mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k];
				CawcuwatePwefetchScheduwe_pawams->MaxIntewDCNTiweWepeatews = mode_wib->ms.ip.max_intew_dcn_tiwe_wepeatews;
				CawcuwatePwefetchScheduwe_pawams->GPUVMPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews;
				CawcuwatePwefetchScheduwe_pawams->GPUVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe;
				CawcuwatePwefetchScheduwe_pawams->HostVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe;
				CawcuwatePwefetchScheduwe_pawams->HostVMMaxNonCachedPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews;
				CawcuwatePwefetchScheduwe_pawams->HostVMMinPageSize = mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024;
				CawcuwatePwefetchScheduwe_pawams->DynamicMetadataEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataEnabwe[k];
				CawcuwatePwefetchScheduwe_pawams->DynamicMetadataVMEnabwed = mode_wib->ms.ip.dynamic_metadata_vm_enabwed;
				CawcuwatePwefetchScheduwe_pawams->DynamicMetadataWinesBefoweActiveWequiwed = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataWinesBefoweActiveWequiwed[k];
				CawcuwatePwefetchScheduwe_pawams->DynamicMetadataTwansmittedBytes = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataTwansmittedBytes[k];
				CawcuwatePwefetchScheduwe_pawams->UwgentWatency = mode_wib->ms.UwgWatency;
				CawcuwatePwefetchScheduwe_pawams->UwgentExtwaWatency = mode_wib->ms.ExtwaWatency;
				CawcuwatePwefetchScheduwe_pawams->TCawc = mode_wib->ms.TimeCawc;
				CawcuwatePwefetchScheduwe_pawams->PDEAndMetaPTEBytesFwame = mode_wib->ms.PDEAndMetaPTEBytesPewFwame[j][k];
				CawcuwatePwefetchScheduwe_pawams->MetaWowByte = mode_wib->ms.MetaWowBytes[j][k];
				CawcuwatePwefetchScheduwe_pawams->PixewPTEBytesPewWow = mode_wib->ms.DPTEBytesPewWow[j][k];
				CawcuwatePwefetchScheduwe_pawams->PwefetchSouwceWinesY = mode_wib->ms.PwefetchWinesY[j][k];
				CawcuwatePwefetchScheduwe_pawams->VInitPweFiwwY = mode_wib->ms.PwefiwwY[k];
				CawcuwatePwefetchScheduwe_pawams->MaxNumSwathY = mode_wib->ms.MaxNumSwY[k];
				CawcuwatePwefetchScheduwe_pawams->PwefetchSouwceWinesC = mode_wib->ms.PwefetchWinesC[j][k];
				CawcuwatePwefetchScheduwe_pawams->VInitPweFiwwC = mode_wib->ms.PwefiwwC[k];
				CawcuwatePwefetchScheduwe_pawams->MaxNumSwathC = mode_wib->ms.MaxNumSwC[k];
				CawcuwatePwefetchScheduwe_pawams->swath_width_wuma_ub = mode_wib->ms.swath_width_wuma_ub_this_state[k];
				CawcuwatePwefetchScheduwe_pawams->swath_width_chwoma_ub = mode_wib->ms.swath_width_chwoma_ub_this_state[k];
				CawcuwatePwefetchScheduwe_pawams->SwathHeightY = mode_wib->ms.SwathHeightYThisState[k];
				CawcuwatePwefetchScheduwe_pawams->SwathHeightC = mode_wib->ms.SwathHeightCThisState[k];
				CawcuwatePwefetchScheduwe_pawams->TWait = mode_wib->ms.TWait;
				CawcuwatePwefetchScheduwe_pawams->DestinationWinesFowPwefetch = &mode_wib->ms.WineTimesFowPwefetch[k];
				CawcuwatePwefetchScheduwe_pawams->DestinationWinesToWequestVMInVBwank = &mode_wib->ms.WinesFowMetaPTE[k];
				CawcuwatePwefetchScheduwe_pawams->DestinationWinesToWequestWowInVBwank = &mode_wib->ms.WinesFowMetaAndDPTEWow[k];
				CawcuwatePwefetchScheduwe_pawams->VWatioPwefetchY = &mode_wib->ms.VWatioPweY[j][k];
				CawcuwatePwefetchScheduwe_pawams->VWatioPwefetchC = &mode_wib->ms.VWatioPweC[j][k];
				CawcuwatePwefetchScheduwe_pawams->WequiwedPwefetchPixDataBWWuma = &mode_wib->ms.WequiwedPwefetchPixewDataBWWuma[k];
				CawcuwatePwefetchScheduwe_pawams->WequiwedPwefetchPixDataBWChwoma = &mode_wib->ms.WequiwedPwefetchPixewDataBWChwoma[k];
				CawcuwatePwefetchScheduwe_pawams->NotEnoughTimeFowDynamicMetadata = &mode_wib->ms.suppowt.NoTimeFowDynamicMetadata[j][k];
				CawcuwatePwefetchScheduwe_pawams->Tno_bw = &mode_wib->ms.Tno_bw[k];
}

static void dmw_pwefetch_check(stwuct dispway_mode_wib_st *mode_wib)
{
	stwuct dmw_cowe_mode_suppowt_wocaws_st *s = &mode_wib->scwatch.dmw_cowe_mode_suppowt_wocaws;
	stwuct CawcuwatePwefetchScheduwe_pawams_st *CawcuwatePwefetchScheduwe_pawams = &mode_wib->scwatch.CawcuwatePwefetchScheduwe_pawams;
	stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams_st *CawcuwateWatewmawks_pawams = &mode_wib->scwatch.CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams;
	stwuct DmwPipe *myPipe;
	dmw_uint_t j, k;

	fow (j = 0; j < 2; ++j) {
		mode_wib->ms.TimeCawc = 24 / mode_wib->ms.PwojectedDCFCWKDeepSweep[j];

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.NoOfDPPThisState[k] = mode_wib->ms.NoOfDPP[j][k];
			mode_wib->ms.swath_width_wuma_ub_this_state[k] = mode_wib->ms.swath_width_wuma_ub_aww_states[j][k];
			mode_wib->ms.swath_width_chwoma_ub_this_state[k] = mode_wib->ms.swath_width_chwoma_ub_aww_states[j][k];
			mode_wib->ms.SwathWidthYThisState[k] = mode_wib->ms.SwathWidthYAwwStates[j][k];
			mode_wib->ms.SwathWidthCThisState[k] = mode_wib->ms.SwathWidthCAwwStates[j][k];
			mode_wib->ms.SwathHeightYThisState[k] = mode_wib->ms.SwathHeightYAwwStates[j][k];
			mode_wib->ms.SwathHeightCThisState[k] = mode_wib->ms.SwathHeightCAwwStates[j][k];
			mode_wib->ms.UnboundedWequestEnabwedThisState = mode_wib->ms.UnboundedWequestEnabwedAwwStates[j];
			mode_wib->ms.CompwessedBuffewSizeInkByteThisState = mode_wib->ms.CompwessedBuffewSizeInkByteAwwStates[j];
			mode_wib->ms.DETBuffewSizeInKByteThisState[k] = mode_wib->ms.DETBuffewSizeInKByteAwwStates[j][k];
			mode_wib->ms.DETBuffewSizeYThisState[k] = mode_wib->ms.DETBuffewSizeYAwwStates[j][k];
			mode_wib->ms.DETBuffewSizeCThisState[k] = mode_wib->ms.DETBuffewSizeCAwwStates[j][k];
		}

		mode_wib->ms.suppowt.VActiveBandwithSuppowt[j] = CawcuwateVActiveBandwithSuppowt(
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.WetuwnBWPewState[j],
			mode_wib->ms.NotUwgentWatencyHiding,
			mode_wib->ms.WeadBandwidthWuma,
			mode_wib->ms.WeadBandwidthChwoma,
			mode_wib->ms.cuwsow_bw,
			mode_wib->ms.meta_wow_bandwidth_this_state,
			mode_wib->ms.dpte_wow_bandwidth_this_state,
			mode_wib->ms.NoOfDPPThisState,
			mode_wib->ms.UwgentBuwstFactowWuma,
			mode_wib->ms.UwgentBuwstFactowChwoma,
			mode_wib->ms.UwgentBuwstFactowCuwsow);

		s->VMDataOnwyWetuwnBWPewState = dmw_get_wetuwn_bw_mbps_vm_onwy(
																	&mode_wib->ms.soc,
																	mode_wib->ms.state.use_ideaw_dwam_bw_stwobe,
																	mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
																	mode_wib->ms.DCFCWKState[j],
																	mode_wib->ms.state.fabwiccwk_mhz,
																	mode_wib->ms.state.dwam_speed_mts);

		s->HostVMInefficiencyFactow = 1;
		if (mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe && mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe)
			s->HostVMInefficiencyFactow = mode_wib->ms.WetuwnBWPewState[j] / s->VMDataOnwyWetuwnBWPewState;

		mode_wib->ms.ExtwaWatency = CawcuwateExtwaWatency(
				mode_wib->ms.soc.wound_twip_ping_watency_dcfcwk_cycwes,
				s->WeowdewingBytes,
				mode_wib->ms.DCFCWKState[j],
				mode_wib->ms.TotawNumbewOfActiveDPP[j],
				mode_wib->ms.ip.pixew_chunk_size_kbytes,
				mode_wib->ms.TotawNumbewOfDCCActiveDPP[j],
				mode_wib->ms.ip.meta_chunk_size_kbytes,
				mode_wib->ms.WetuwnBWPewState[j],
				mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe,
				mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
				mode_wib->ms.num_active_pwanes,
				mode_wib->ms.NoOfDPPThisState,
				mode_wib->ms.dpte_gwoup_bytes,
				s->HostVMInefficiencyFactow,
				mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024,
				mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews);

		s->NextMaxVStawtup = s->MaxVStawtupAwwPwanes[j];
		s->MaxVStawtup = 0;
		s->AwwPwefetchModeTested = twue;
		fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
			CawcuwatePwefetchMode(mode_wib->ms.powicy.AwwowFowPStateChangeOwStuttewInVBwank[k], &s->MinPwefetchMode[k], &s->MaxPwefetchMode[k]);
			s->NextPwefetchMode[k] = s->MinPwefetchMode[k];
		}

		do {
			s->MaxVStawtup = s->NextMaxVStawtup;
			s->AwwPwefetchModeTested = twue;

			fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
				mode_wib->ms.PwefetchMode[k] = s->NextPwefetchMode[k];
				mode_wib->ms.TWait = CawcuwateTWait(
								mode_wib->ms.PwefetchMode[k],
								mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k],
								mode_wib->ms.powicy.SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
								mode_wib->ms.cache_dispway_cfg.timing.DWWDispway[k],
								mode_wib->ms.state.dwam_cwock_change_watency_us,
								mode_wib->ms.state.fcwk_change_watency_us,
								mode_wib->ms.UwgWatency,
								mode_wib->ms.state.sw_entew_pwus_exit_time_us);

				myPipe = &s->myPipe;
				myPipe->Dppcwk = mode_wib->ms.WequiwedDPPCWKPewSuwface[j][k];
				myPipe->Dispcwk = mode_wib->ms.WequiwedDISPCWK[j];
				myPipe->PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k];
				myPipe->DCFCwkDeepSweep = mode_wib->ms.PwojectedDCFCWKDeepSweep[j];
				myPipe->DPPPewSuwface = mode_wib->ms.NoOfDPP[j][k];
				myPipe->ScawewEnabwed = mode_wib->ms.cache_dispway_cfg.pwane.ScawewEnabwed[k];
				myPipe->SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k];
				myPipe->BwockWidth256BytesY = mode_wib->ms.Wead256BwockWidthY[k];
				myPipe->BwockHeight256BytesY = mode_wib->ms.Wead256BwockHeightY[k];
				myPipe->BwockWidth256BytesC = mode_wib->ms.Wead256BwockWidthC[k];
				myPipe->BwockHeight256BytesC = mode_wib->ms.Wead256BwockHeightC[k];
				myPipe->IntewwaceEnabwe = mode_wib->ms.cache_dispway_cfg.timing.Intewwace[k];
				myPipe->NumbewOfCuwsows = mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows[k];
				myPipe->VBwank = mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VActive[k];
				myPipe->HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k];
				myPipe->HActive = mode_wib->ms.cache_dispway_cfg.timing.HActive[k];
				myPipe->DCCEnabwe = mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k];
				myPipe->ODMMode = mode_wib->ms.ODMModePewState[k];
				myPipe->SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k];
				myPipe->BytePewPixewY = mode_wib->ms.BytePewPixewY[k];
				myPipe->BytePewPixewC = mode_wib->ms.BytePewPixewC[k];
				myPipe->PwogwessiveToIntewwaceUnitInOPP = mode_wib->ms.ip.ptoi_suppowted;

#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: Cawwing CawcuwatePwefetchScheduwe fow j=%u, k=%u\n", __func__, j, k);
				dmw_pwint("DMW::%s: MaximumVStawtup = %u\n", __func__, s->MaximumVStawtup[j][k]);
				dmw_pwint("DMW::%s: MaxVStawtup = %u\n", __func__, s->MaxVStawtup);
				dmw_pwint("DMW::%s: NextPwefetchMode = %u\n", __func__, s->NextPwefetchMode[k]);
				dmw_pwint("DMW::%s: AwwowFowPStateChangeOwStuttewInVBwank = %u\n", __func__, mode_wib->ms.powicy.AwwowFowPStateChangeOwStuttewInVBwank[k]);
				dmw_pwint("DMW::%s: PwefetchMode = %u\n", __func__, mode_wib->ms.PwefetchMode[k]);
#endif

				CawcuwatePwefetchScheduwe_pawams->HostVMInefficiencyFactow = s->HostVMInefficiencyFactow;
				CawcuwatePwefetchScheduwe_pawams->myPipe = myPipe;
				CawcuwatePwefetchScheduwe_pawams->VStawtup = (dmw_uint_t)(dmw_min(s->MaxVStawtup, s->MaximumVStawtup[j][k]));
				CawcuwatePwefetchScheduwe_pawams->MaxVStawtup = s->MaximumVStawtup[j][k];
				CawcuwatePwefetchScheduwe_pawams->DSTXAftewScawew = &s->DSTXAftewScawew[k];
				CawcuwatePwefetchScheduwe_pawams->DSTYAftewScawew = &s->DSTYAftewScawew[k];
				CawcuwatePwefetchScheduwe_pawams->pwefetch_vmwow_bw = &mode_wib->ms.pwefetch_vmwow_bw[k];
				CawcuwatePwefetchScheduwe_pawams->Tdmdw_vm = &s->dummy_singwe[0];
				CawcuwatePwefetchScheduwe_pawams->Tdmdw = &s->dummy_singwe[1];
				CawcuwatePwefetchScheduwe_pawams->TSetup = &s->dummy_singwe[2];
				CawcuwatePwefetchScheduwe_pawams->VUpdateOffsetPix = &s->dummy_integew[0];
				CawcuwatePwefetchScheduwe_pawams->VUpdateWidthPix = &s->dummy_integew[1];
				CawcuwatePwefetchScheduwe_pawams->VWeadyOffsetPix = &s->dummy_integew[2];

				set_cawcuwate_pwefetch_scheduwe_pawams(mode_wib, CawcuwatePwefetchScheduwe_pawams, j, k);

				mode_wib->ms.suppowt.NoTimeFowPwefetch[j][k] =
								CawcuwatePwefetchScheduwe(&mode_wib->scwatch,
								CawcuwatePwefetchScheduwe_pawams);
			}

			fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
					CawcuwateUwgentBuwstFactow(
							mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k],
							mode_wib->ms.swath_width_wuma_ub_this_state[k],
							mode_wib->ms.swath_width_chwoma_ub_this_state[k],
							mode_wib->ms.SwathHeightYThisState[k],
							mode_wib->ms.SwathHeightCThisState[k],
							mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
							mode_wib->ms.UwgWatency,
							mode_wib->ms.ip.cuwsow_buffew_size,
							mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k],
							mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k],
							mode_wib->ms.VWatioPweY[j][k],
							mode_wib->ms.VWatioPweC[j][k],
							mode_wib->ms.BytePewPixewInDETY[k],
							mode_wib->ms.BytePewPixewInDETC[k],
							mode_wib->ms.DETBuffewSizeYThisState[k],
							mode_wib->ms.DETBuffewSizeCThisState[k],
							/* Output */
							&mode_wib->ms.UwgentBuwstFactowCuwsowPwe[k],
							&mode_wib->ms.UwgentBuwstFactowWumaPwe[k],
							&mode_wib->ms.UwgentBuwstFactowChwoma[k],
							&mode_wib->ms.NotUwgentWatencyHidingPwe[k]);

					mode_wib->ms.cuwsow_bw_pwe[k] = mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k] *
													mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k] / 8.0 / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] /
													mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.VWatioPweY[j][k];
			}

			{
			CawcuwatePwefetchBandwithSuppowt(
				mode_wib->ms.num_active_pwanes,
				mode_wib->ms.WetuwnBWPewState[j],
				mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
				mode_wib->ms.NotUwgentWatencyHidingPwe,
				mode_wib->ms.WeadBandwidthWuma,
				mode_wib->ms.WeadBandwidthChwoma,
				mode_wib->ms.WequiwedPwefetchPixewDataBWWuma,
				mode_wib->ms.WequiwedPwefetchPixewDataBWChwoma,
				mode_wib->ms.cuwsow_bw,
				mode_wib->ms.meta_wow_bandwidth_this_state,
				mode_wib->ms.dpte_wow_bandwidth_this_state,
				mode_wib->ms.cuwsow_bw_pwe,
				mode_wib->ms.pwefetch_vmwow_bw,
				mode_wib->ms.NoOfDPPThisState,
				mode_wib->ms.UwgentBuwstFactowWuma,
				mode_wib->ms.UwgentBuwstFactowChwoma,
				mode_wib->ms.UwgentBuwstFactowCuwsow,
				mode_wib->ms.UwgentBuwstFactowWumaPwe,
				mode_wib->ms.UwgentBuwstFactowChwomaPwe,
				mode_wib->ms.UwgentBuwstFactowCuwsowPwe,

				/* output */
				&s->dummy_singwe[0], // dmw_fwoat_t *PwefetchBandwidth
				&s->dummy_singwe[1], // dmw_fwoat_t *PwefetchBandwidthNotIncwudingMAWWPwefetch
				&mode_wib->mp.FwactionOfUwgentBandwidth, // dmw_fwoat_t *FwactionOfUwgentBandwidth
				&mode_wib->ms.suppowt.PwefetchSuppowted[j]);
			}

			fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
				if (mode_wib->ms.WineTimesFowPwefetch[k] < 2.0
					|| mode_wib->ms.WinesFowMetaPTE[k] >= 32.0
					|| mode_wib->ms.WinesFowMetaAndDPTEWow[k] >= 16.0
					|| mode_wib->ms.suppowt.NoTimeFowPwefetch[j][k] == twue) {
						mode_wib->ms.suppowt.PwefetchSuppowted[j] = fawse;
				}
			}

			mode_wib->ms.suppowt.DynamicMetadataSuppowted[j] = twue;
			fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
				if (mode_wib->ms.suppowt.NoTimeFowDynamicMetadata[j][k] == twue) {
					mode_wib->ms.suppowt.DynamicMetadataSuppowted[j] = fawse;
				}
			}

			mode_wib->ms.suppowt.VWatioInPwefetchSuppowted[j] = twue;
			fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
				if (mode_wib->ms.suppowt.NoTimeFowPwefetch[j][k] == twue ||
					mode_wib->ms.VWatioPweY[j][k] > __DMW_MAX_VWATIO_PWE_ENHANCE_PWEFETCH_ACC__ ||
					mode_wib->ms.VWatioPweC[j][k] > __DMW_MAX_VWATIO_PWE_ENHANCE_PWEFETCH_ACC__ ||
					((s->MaxVStawtup < s->MaximumVStawtup[j][k] || mode_wib->ms.powicy.EnhancedPwefetchScheduweAccewewationFinaw == 0) &&
						(mode_wib->ms.VWatioPweY[j][k] > __DMW_MAX_VWATIO_PWE__ || mode_wib->ms.VWatioPweC[j][k] > __DMW_MAX_VWATIO_PWE__))) {
							mode_wib->ms.suppowt.VWatioInPwefetchSuppowted[j] = fawse;
				}
			}

			s->AnyWinesFowVMOwWowTooWawge = fawse;
			fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
				if (mode_wib->ms.WinesFowMetaAndDPTEWow[k] >= 16 || mode_wib->ms.WinesFowMetaPTE[k] >= 32) {
					s->AnyWinesFowVMOwWowTooWawge = twue;
				}
			}

			if (mode_wib->ms.suppowt.PwefetchSuppowted[j] == twue && mode_wib->ms.suppowt.VWatioInPwefetchSuppowted[j] == twue) {
				mode_wib->ms.BandwidthAvaiwabweFowImmediateFwip = CawcuwateBandwidthAvaiwabweFowImmediateFwip(
						mode_wib->ms.num_active_pwanes,
						mode_wib->ms.WetuwnBWPewState[j],
						mode_wib->ms.WeadBandwidthWuma,
						mode_wib->ms.WeadBandwidthChwoma,
						mode_wib->ms.WequiwedPwefetchPixewDataBWWuma,
						mode_wib->ms.WequiwedPwefetchPixewDataBWChwoma,
						mode_wib->ms.cuwsow_bw,
						mode_wib->ms.cuwsow_bw_pwe,
						mode_wib->ms.NoOfDPPThisState,
						mode_wib->ms.UwgentBuwstFactowWuma,
						mode_wib->ms.UwgentBuwstFactowChwoma,
						mode_wib->ms.UwgentBuwstFactowCuwsow,
						mode_wib->ms.UwgentBuwstFactowWumaPwe,
						mode_wib->ms.UwgentBuwstFactowChwomaPwe,
						mode_wib->ms.UwgentBuwstFactowCuwsowPwe);

				mode_wib->ms.TotImmediateFwipBytes = 0;
				fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
					if (!(mode_wib->ms.powicy.ImmediateFwipWequiwement[k] == dmw_immediate_fwip_not_wequiwed)) {
						mode_wib->ms.TotImmediateFwipBytes = mode_wib->ms.TotImmediateFwipBytes + mode_wib->ms.NoOfDPP[j][k] * mode_wib->ms.PDEAndMetaPTEBytesPewFwame[j][k] + mode_wib->ms.MetaWowBytes[j][k];
						if (mode_wib->ms.use_one_wow_fow_fwame_fwip[j][k]) {
							mode_wib->ms.TotImmediateFwipBytes = mode_wib->ms.TotImmediateFwipBytes + mode_wib->ms.NoOfDPP[j][k] * (2 * mode_wib->ms.DPTEBytesPewWow[j][k]);
						} ewse {
							mode_wib->ms.TotImmediateFwipBytes = mode_wib->ms.TotImmediateFwipBytes + mode_wib->ms.NoOfDPP[j][k] * mode_wib->ms.DPTEBytesPewWow[j][k];
						}
					}
				}

				fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
					CawcuwateFwipScheduwe(
						s->HostVMInefficiencyFactow,
						mode_wib->ms.ExtwaWatency,
						mode_wib->ms.UwgWatency,
						mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews,
						mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
						mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews,
						mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe,
						mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024,
						mode_wib->ms.PDEAndMetaPTEBytesPewFwame[j][k],
						mode_wib->ms.MetaWowBytes[j][k],
						mode_wib->ms.DPTEBytesPewWow[j][k],
						mode_wib->ms.BandwidthAvaiwabweFowImmediateFwip,
						mode_wib->ms.TotImmediateFwipBytes,
						mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
						(mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]),
						mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k],
						mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k],
						mode_wib->ms.Tno_bw[k],
						mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k],
						mode_wib->ms.dpte_wow_height[k],
						mode_wib->ms.meta_wow_height[k],
						mode_wib->ms.dpte_wow_height_chwoma[k],
						mode_wib->ms.meta_wow_height_chwoma[k],
						mode_wib->ms.use_one_wow_fow_fwame_fwip[j][k], // 24

						/* Output */
						&mode_wib->ms.DestinationWinesToWequestVMInImmediateFwip[k],
						&mode_wib->ms.DestinationWinesToWequestWowInImmediateFwip[k],
						&mode_wib->ms.finaw_fwip_bw[k],
						&mode_wib->ms.ImmediateFwipSuppowtedFowPipe[k]);
				}

				{
				CawcuwateImmediateFwipBandwithSuppowt(mode_wib->ms.num_active_pwanes,
													mode_wib->ms.WetuwnBWPewState[j],
													mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
													mode_wib->ms.powicy.ImmediateFwipWequiwement,
													mode_wib->ms.finaw_fwip_bw,
													mode_wib->ms.WeadBandwidthWuma,
													mode_wib->ms.WeadBandwidthChwoma,
													mode_wib->ms.WequiwedPwefetchPixewDataBWWuma,
													mode_wib->ms.WequiwedPwefetchPixewDataBWChwoma,
													mode_wib->ms.cuwsow_bw,
													mode_wib->ms.meta_wow_bandwidth_this_state,
													mode_wib->ms.dpte_wow_bandwidth_this_state,
													mode_wib->ms.cuwsow_bw_pwe,
													mode_wib->ms.pwefetch_vmwow_bw,
													mode_wib->ms.NoOfDPP[j], // VBA_EWWOW DPPPewSuwface is not assigned at this point, shouwd use NoOfDpp hewe
													mode_wib->ms.UwgentBuwstFactowWuma,
													mode_wib->ms.UwgentBuwstFactowChwoma,
													mode_wib->ms.UwgentBuwstFactowCuwsow,
													mode_wib->ms.UwgentBuwstFactowWumaPwe,
													mode_wib->ms.UwgentBuwstFactowChwomaPwe,
													mode_wib->ms.UwgentBuwstFactowCuwsowPwe,

													/* output */
													&s->dummy_singwe[0], // dmw_fwoat_t *TotawBandwidth
													&s->dummy_singwe[1], // dmw_fwoat_t *TotawBandwidthNotIncwudingMAWWPwefetch
													&s->dummy_singwe[2], // dmw_fwoat_t *FwactionOfUwgentBandwidth
													&mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[j]); // dmw_boow_t *ImmediateFwipBandwidthSuppowt
				}

				fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
					if (!(mode_wib->ms.powicy.ImmediateFwipWequiwement[k] == dmw_immediate_fwip_not_wequiwed) && (mode_wib->ms.ImmediateFwipSuppowtedFowPipe[k] == fawse))
						mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[j] = fawse;
				}

			} ewse { // if pwefetch not suppowt, assume ifwip not suppowted
				mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[j] = fawse;
			}

			if (s->MaxVStawtup <= __DMW_VBA_MIN_VSTAWTUP__ || s->AnyWinesFowVMOwWowTooWawge == fawse) {
				s->NextMaxVStawtup = s->MaxVStawtupAwwPwanes[j];
				fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
					s->NextPwefetchMode[k] = s->NextPwefetchMode[k] + 1;

					if (s->NextPwefetchMode[k] <= s->MaxPwefetchMode[k])
						s->AwwPwefetchModeTested = fawse;
				}
			} ewse {
				s->NextMaxVStawtup = s->NextMaxVStawtup - 1;
			}
		} whiwe (!((mode_wib->ms.suppowt.PwefetchSuppowted[j] == twue && mode_wib->ms.suppowt.DynamicMetadataSuppowted[j] == twue &&
					mode_wib->ms.suppowt.VWatioInPwefetchSuppowted[j] == twue &&
					// considew fwip suppowt is okay if when thewe is no hostvm and the usew does't wequiwe a ifwip OW the fwip bw is ok
					// If thewe is hostvm, DCN needs to suppowt ifwip fow invawidation
					((s->ImmediateFwipWequiwedFinaw) || mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[j] == twue)) ||
					(s->NextMaxVStawtup == s->MaxVStawtupAwwPwanes[j] && s->AwwPwefetchModeTested)));

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.use_one_wow_fow_fwame_this_state[k] = mode_wib->ms.use_one_wow_fow_fwame[j][k];
		}

		s->mSOCPawametews.UwgentWatency = mode_wib->ms.UwgWatency;
		s->mSOCPawametews.ExtwaWatency = mode_wib->ms.ExtwaWatency;
		s->mSOCPawametews.WwitebackWatency = mode_wib->ms.state.wwiteback_watency_us;
		s->mSOCPawametews.DWAMCwockChangeWatency = mode_wib->ms.state.dwam_cwock_change_watency_us;
		s->mSOCPawametews.FCWKChangeWatency = mode_wib->ms.state.fcwk_change_watency_us;
		s->mSOCPawametews.SWExitTime = mode_wib->ms.state.sw_exit_time_us;
		s->mSOCPawametews.SWEntewPwusExitTime = mode_wib->ms.state.sw_entew_pwus_exit_time_us;
		s->mSOCPawametews.SWExitZ8Time = mode_wib->ms.state.sw_exit_z8_time_us;
		s->mSOCPawametews.SWEntewPwusExitZ8Time = mode_wib->ms.state.sw_entew_pwus_exit_z8_time_us;
		s->mSOCPawametews.USWWetwainingWatency = mode_wib->ms.state.usw_wetwaining_watency_us;
		s->mSOCPawametews.SMNWatency = mode_wib->ms.soc.smn_watency_us;

		CawcuwateWatewmawks_pawams->USWWetwainingWequiwedFinaw = mode_wib->ms.powicy.USWWetwainingWequiwedFinaw;
		CawcuwateWatewmawks_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
		CawcuwateWatewmawks_pawams->PwefetchMode = mode_wib->ms.PwefetchMode;
		CawcuwateWatewmawks_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
		CawcuwateWatewmawks_pawams->MaxWineBuffewWines = mode_wib->ms.ip.max_wine_buffew_wines;
		CawcuwateWatewmawks_pawams->WineBuffewSize = mode_wib->ms.ip.wine_buffew_size_bits;
		CawcuwateWatewmawks_pawams->WwitebackIntewfaceBuffewSize = mode_wib->ms.ip.wwiteback_intewface_buffew_size_kbytes;
		CawcuwateWatewmawks_pawams->DCFCWK = mode_wib->ms.DCFCWKState[j];
		CawcuwateWatewmawks_pawams->WetuwnBW = mode_wib->ms.WetuwnBWPewState[j];
		CawcuwateWatewmawks_pawams->SynchwonizeTimingsFinaw = mode_wib->ms.powicy.SynchwonizeTimingsFinaw;
		CawcuwateWatewmawks_pawams->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw = mode_wib->ms.powicy.SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
		CawcuwateWatewmawks_pawams->DWWDispway = mode_wib->ms.cache_dispway_cfg.timing.DWWDispway;
		CawcuwateWatewmawks_pawams->dpte_gwoup_bytes = mode_wib->ms.dpte_gwoup_bytes;
		CawcuwateWatewmawks_pawams->meta_wow_height = mode_wib->ms.meta_wow_height;
		CawcuwateWatewmawks_pawams->meta_wow_height_chwoma = mode_wib->ms.meta_wow_height_chwoma;
		CawcuwateWatewmawks_pawams->mmSOCPawametews = s->mSOCPawametews;
		CawcuwateWatewmawks_pawams->WwitebackChunkSize = mode_wib->ms.ip.wwiteback_chunk_size_kbytes;
		CawcuwateWatewmawks_pawams->SOCCWK = mode_wib->ms.state.soccwk_mhz;
		CawcuwateWatewmawks_pawams->DCFCwkDeepSweep = mode_wib->ms.PwojectedDCFCWKDeepSweep[j];
		CawcuwateWatewmawks_pawams->DETBuffewSizeY = mode_wib->ms.DETBuffewSizeYThisState;
		CawcuwateWatewmawks_pawams->DETBuffewSizeC = mode_wib->ms.DETBuffewSizeCThisState;
		CawcuwateWatewmawks_pawams->SwathHeightY = mode_wib->ms.SwathHeightYThisState;
		CawcuwateWatewmawks_pawams->SwathHeightC = mode_wib->ms.SwathHeightCThisState;
		CawcuwateWatewmawks_pawams->WBBitPewPixew = mode_wib->ms.cache_dispway_cfg.pwane.WBBitPewPixew;
		CawcuwateWatewmawks_pawams->SwathWidthY = mode_wib->ms.SwathWidthYThisState;
		CawcuwateWatewmawks_pawams->SwathWidthC = mode_wib->ms.SwathWidthCThisState;
		CawcuwateWatewmawks_pawams->HWatio = mode_wib->ms.cache_dispway_cfg.pwane.HWatio;
		CawcuwateWatewmawks_pawams->HWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma;
		CawcuwateWatewmawks_pawams->VTaps = mode_wib->ms.cache_dispway_cfg.pwane.VTaps;
		CawcuwateWatewmawks_pawams->VTapsChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma;
		CawcuwateWatewmawks_pawams->VWatio = mode_wib->ms.cache_dispway_cfg.pwane.VWatio;
		CawcuwateWatewmawks_pawams->VWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma;
		CawcuwateWatewmawks_pawams->HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw;
		CawcuwateWatewmawks_pawams->VTotaw = mode_wib->ms.cache_dispway_cfg.timing.VTotaw;
		CawcuwateWatewmawks_pawams->VActive = mode_wib->ms.cache_dispway_cfg.timing.VActive;
		CawcuwateWatewmawks_pawams->PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock;
		CawcuwateWatewmawks_pawams->BwendingAndTiming = mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming;
		CawcuwateWatewmawks_pawams->DPPPewSuwface = mode_wib->ms.NoOfDPPThisState;
		CawcuwateWatewmawks_pawams->BytePewPixewDETY = mode_wib->ms.BytePewPixewInDETY;
		CawcuwateWatewmawks_pawams->BytePewPixewDETC = mode_wib->ms.BytePewPixewInDETC;
		CawcuwateWatewmawks_pawams->DSTXAftewScawew = s->DSTXAftewScawew;
		CawcuwateWatewmawks_pawams->DSTYAftewScawew = s->DSTYAftewScawew;
		CawcuwateWatewmawks_pawams->WwitebackEnabwe = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe;
		CawcuwateWatewmawks_pawams->WwitebackPixewFowmat = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat;
		CawcuwateWatewmawks_pawams->WwitebackDestinationWidth = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth;
		CawcuwateWatewmawks_pawams->WwitebackDestinationHeight = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight;
		CawcuwateWatewmawks_pawams->WwitebackSouwceHeight = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight;
		CawcuwateWatewmawks_pawams->UnboundedWequestEnabwed = mode_wib->ms.UnboundedWequestEnabwedThisState;
		CawcuwateWatewmawks_pawams->CompwessedBuffewSizeInkByte = mode_wib->ms.CompwessedBuffewSizeInkByteThisState;

		// Output
		CawcuwateWatewmawks_pawams->Watewmawk = &s->dummy_watewmawk; // Watewmawks *Watewmawk
		CawcuwateWatewmawks_pawams->DWAMCwockChangeSuppowt = &mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[j];
		CawcuwateWatewmawks_pawams->MaxActiveDWAMCwockChangeWatencySuppowted = &s->dummy_singwe_awway[0]; // dmw_fwoat_t *MaxActiveDWAMCwockChangeWatencySuppowted[]
		CawcuwateWatewmawks_pawams->SubViewpowtWinesNeededInMAWW = &mode_wib->ms.SubViewpowtWinesNeededInMAWW[j]; // dmw_uint_t SubViewpowtWinesNeededInMAWW[]
		CawcuwateWatewmawks_pawams->FCWKChangeSuppowt = &mode_wib->ms.suppowt.FCWKChangeSuppowt[j];
		CawcuwateWatewmawks_pawams->MaxActiveFCWKChangeWatencySuppowted = &s->dummy_singwe[0]; // dmw_fwoat_t *MaxActiveFCWKChangeWatencySuppowted
		CawcuwateWatewmawks_pawams->USWWetwainingSuppowt = &mode_wib->ms.suppowt.USWWetwainingSuppowt[j];
		CawcuwateWatewmawks_pawams->ActiveDWAMCwockChangeWatencyMawgin = mode_wib->ms.suppowt.ActiveDWAMCwockChangeWatencyMawgin;

		CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt(&mode_wib->scwatch,
			CawcuwateWatewmawks_pawams);

	} // fow j
}

/// @bwief The Mode Suppowt function.
dmw_boow_t dmw_cowe_mode_suppowt(stwuct dispway_mode_wib_st *mode_wib)
{
	stwuct dmw_cowe_mode_suppowt_wocaws_st *s = &mode_wib->scwatch.dmw_cowe_mode_suppowt_wocaws;
	stwuct UseMinimumDCFCWK_pawams_st *UseMinimumDCFCWK_pawams = &mode_wib->scwatch.UseMinimumDCFCWK_pawams;
	stwuct CawcuwateSwathAndDETConfiguwation_pawams_st *CawcuwateSwathAndDETConfiguwation_pawams = &mode_wib->scwatch.CawcuwateSwathAndDETConfiguwation_pawams;
	stwuct CawcuwateVMWowAndSwath_pawams_st *CawcuwateVMWowAndSwath_pawams = &mode_wib->scwatch.CawcuwateVMWowAndSwath_pawams;

	dmw_uint_t j, k, m;

	mode_wib->ms.num_active_pwanes = dmw_get_num_active_pwanes(&mode_wib->ms.cache_dispway_cfg);
	dmw_pwint("DMW::%s: num_active_pwanes = %u\n", __func__, mode_wib->ms.num_active_pwanes);

	CawcuwateMaxDETAndMinCompwessedBuffewSize(
								mode_wib->ms.ip.config_wetuwn_buffew_size_in_kbytes,
								mode_wib->ms.ip.config_wetuwn_buffew_segment_size_in_kbytes,
								mode_wib->ms.ip.wob_buffew_size_kbytes,
								mode_wib->ms.ip.max_num_dpp,
								mode_wib->ms.powicy.NomDETInKByteOvewwideEnabwe,   // VBA_DEWTA
								mode_wib->ms.powicy.NomDETInKByteOvewwideVawue,    // VBA_DEWTA

								/* Output */
								&mode_wib->ms.MaxTotawDETInKByte,
								&mode_wib->ms.NomDETInKByte,
								&mode_wib->ms.MinCompwessedBuffewSizeInKByte);

	PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(&mode_wib->ms.cache_dispway_cfg, mode_wib->ms.ip.ptoi_suppowted);


	/*MODE SUPPOWT, VOWTAGE STATE AND SOC CONFIGUWATION*/

	/*Scawe Watio, taps Suppowt Check*/
	mode_wib->ms.suppowt.ScaweWatioAndTapsSuppowt = twue;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.ScawewEnabwed[k] == fawse
				&& ((mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_64
						&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_32
						&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_16
						&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_mono_16
						&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_mono_8
						&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe
						&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe_awpha)
						|| mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k] != 1.0
						|| mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k] != 1.0
						|| mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k] != 1.0
						|| mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k] != 1.0)) {
			mode_wib->ms.suppowt.ScaweWatioAndTapsSuppowt = fawse;
		} ewse if (mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k] < 1.0 || mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k] > 8.0
				|| mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k] < 1.0 || mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k] > 8.0
				|| (mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k] > 1.0 && (mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k] % 2) == 1)
				|| mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k] > mode_wib->ms.ip.max_hscw_watio
				|| mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k] > mode_wib->ms.ip.max_vscw_watio
				|| mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k] > mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k]
				|| mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k] > mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k]
				|| (mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_64
					&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_32
					&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_16
					&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_mono_16
					&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_mono_8
					&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe
					&& (mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k] < 1 || mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k] > 8 || mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k] < 1 || mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k] > 8 ||
						(mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k] > 1 && mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k] % 2 == 1) ||
					mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma[k] > mode_wib->ms.ip.max_hscw_watio ||
					mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k] > mode_wib->ms.ip.max_vscw_watio ||
					mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma[k] > mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k] ||
					mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k] > mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k]))) {
			mode_wib->ms.suppowt.ScaweWatioAndTapsSuppowt = fawse;
		}
	}

	/*Souwce Fowmat, Pixew Fowmat and Scan Suppowt Check*/
	mode_wib->ms.suppowt.SouwceFowmatPixewAndScanSuppowt = twue;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
			if (mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k] == dmw_sw_wineaw && (!(!dmw_is_vewticaw_wotation(mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k])) || mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k] == twue)) {
			mode_wib->ms.suppowt.SouwceFowmatPixewAndScanSuppowt = fawse;
		}
	}

	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		CawcuwateBytePewPixewAndBwockSizes(
								mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
								mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k],

								/* Output */
								&mode_wib->ms.BytePewPixewY[k],
								&mode_wib->ms.BytePewPixewC[k],
								&mode_wib->ms.BytePewPixewInDETY[k],
								&mode_wib->ms.BytePewPixewInDETC[k],
								&mode_wib->ms.Wead256BwockHeightY[k],
								&mode_wib->ms.Wead256BwockHeightC[k],
								&mode_wib->ms.Wead256BwockWidthY[k],
								&mode_wib->ms.Wead256BwockWidthC[k],
								&mode_wib->ms.MacwoTiweHeightY[k],
								&mode_wib->ms.MacwoTiweHeightC[k],
								&mode_wib->ms.MacwoTiweWidthY[k],
								&mode_wib->ms.MacwoTiweWidthC[k]);
	}

	/*Bandwidth Suppowt Check*/
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (!dmw_is_vewticaw_wotation(mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k])) {
			mode_wib->ms.SwathWidthYSingweDPP[k] = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth[k];
			mode_wib->ms.SwathWidthCSingweDPP[k] = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidthChwoma[k];
		} ewse {
			mode_wib->ms.SwathWidthYSingweDPP[k] = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight[k];
			mode_wib->ms.SwathWidthCSingweDPP[k] = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeightChwoma[k];
		}
	}
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		mode_wib->ms.WeadBandwidthWuma[k] = mode_wib->ms.SwathWidthYSingweDPP[k] * dmw_ceiw(mode_wib->ms.BytePewPixewInDETY[k], 1.0) / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k];
		mode_wib->ms.WeadBandwidthChwoma[k] = mode_wib->ms.SwathWidthYSingweDPP[k] / 2 * dmw_ceiw(mode_wib->ms.BytePewPixewInDETC[k], 2.0) / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k] / 2.0;
	}
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue
				&& mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[k] == dmw_444_64) {
			mode_wib->ms.WwiteBandwidth[k] = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k]
					* mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[k]
					/ (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[k]
							* mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]
							/ mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * 8.0;
		} ewse if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
			mode_wib->ms.WwiteBandwidth[k] = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k]
					* mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[k]
					/ (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[k]
							* mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]
							/ mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * 4.0;
		} ewse {
			mode_wib->ms.WwiteBandwidth[k] = 0.0;
		}
	}

	/*Wwiteback Watency suppowt check*/
	mode_wib->ms.suppowt.WwitebackWatencySuppowt = twue;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue &&
			(mode_wib->ms.WwiteBandwidth[k] > mode_wib->ms.ip.wwiteback_intewface_buffew_size_kbytes * 1024 / mode_wib->ms.state.wwiteback_watency_us)) {
			mode_wib->ms.suppowt.WwitebackWatencySuppowt = fawse;
		}
	}

	/*Wwiteback Mode Suppowt Check*/
	s->TotawNumbewOfActiveWwiteback = 0;
	fow (k = 0; k <= (dmw_uint_t) mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
			s->TotawNumbewOfActiveWwiteback = s->TotawNumbewOfActiveWwiteback + 1;
		}
   }

	mode_wib->ms.suppowt.EnoughWwitebackUnits = 1;
	if (s->TotawNumbewOfActiveWwiteback > (dmw_uint_t) mode_wib->ms.ip.max_num_wb) {
		mode_wib->ms.suppowt.EnoughWwitebackUnits = fawse;
	}

	/*Wwiteback Scawe Watio and Taps Suppowt Check*/
	mode_wib->ms.suppowt.WwitebackScaweWatioAndTapsSuppowt = twue;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
			if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k] > mode_wib->ms.ip.wwiteback_max_hscw_watio
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k] > mode_wib->ms.ip.wwiteback_max_vscw_watio
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k] < mode_wib->ms.ip.wwiteback_min_hscw_watio
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k] < mode_wib->ms.ip.wwiteback_min_vscw_watio
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHTaps[k] > (dmw_uint_t) mode_wib->ms.ip.wwiteback_max_hscw_taps
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k] > (dmw_uint_t) mode_wib->ms.ip.wwiteback_max_vscw_taps
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k] > (dmw_uint_t) mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHTaps[k]
				|| mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k] > (dmw_uint_t) mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k]
				|| (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHTaps[k] > 2.0 && ((mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHTaps[k] % 2) == 1))) {
				mode_wib->ms.suppowt.WwitebackScaweWatioAndTapsSuppowt = fawse;
			}
			if (2.0 * mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k] * (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k] - 1) * 57 > mode_wib->ms.ip.wwiteback_wine_buffew_buffew_size) {
				mode_wib->ms.suppowt.WwitebackScaweWatioAndTapsSuppowt = fawse;
			}
		}
	}

	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		CawcuwateSingwePipeDPPCWKAndSCWThwoughput(
				mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k],
				mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k],
				mode_wib->ms.ip.max_dchub_pscw_bw_pix_pew_cwk,
				mode_wib->ms.ip.max_pscw_wb_bw_pix_pew_cwk,
				mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
				mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
				mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k],
				mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k],
				/* Output */
				&mode_wib->ms.PSCW_FACTOW[k],
				&mode_wib->ms.PSCW_FACTOW_CHWOMA[k],
				&mode_wib->ms.MinDPPCWKUsingSingweDPP[k]);
	}

	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k] == dmw_sw_wineaw) {
			s->MaximumSwathWidthSuppowtWuma = 8192;
		} ewse if (!dmw_is_vewticaw_wotation(mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k]) && mode_wib->ms.BytePewPixewC[k] > 0 && mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe_awpha) {
			s->MaximumSwathWidthSuppowtWuma = 7680;
		} ewse if (dmw_is_vewticaw_wotation(mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k]) && mode_wib->ms.BytePewPixewC[k] > 0 && mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe_awpha) {
			s->MaximumSwathWidthSuppowtWuma = 4320;
		} ewse if (mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_wgbe_awpha) {
			s->MaximumSwathWidthSuppowtWuma = 3840;
		} ewse if (dmw_is_vewticaw_wotation(mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k]) && mode_wib->ms.BytePewPixewY[k] == 8 && mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k] == twue) {
			s->MaximumSwathWidthSuppowtWuma = 3072;
		} ewse {
			s->MaximumSwathWidthSuppowtWuma = 6144;
		}

       if (mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_420_8 || mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_420_10 || mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_420_12) {
			s->MaximumSwathWidthSuppowtChwoma = (dmw_uint_t)(s->MaximumSwathWidthSuppowtWuma / 2.0);
		} ewse {
			s->MaximumSwathWidthSuppowtChwoma = s->MaximumSwathWidthSuppowtWuma;
       }
		mode_wib->ms.MaximumSwathWidthInWineBuffewWuma = mode_wib->ms.ip.wine_buffew_size_bits * dmw_max(mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k], 1.0) / mode_wib->ms.cache_dispway_cfg.pwane.WBBitPewPixew[k] /
															(mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k] + dmw_max(dmw_ceiw(mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k], 1.0) - 2, 0.0));
		if (mode_wib->ms.BytePewPixewC[k] == 0.0) {
			mode_wib->ms.MaximumSwathWidthInWineBuffewChwoma = 0;
		} ewse {
			mode_wib->ms.MaximumSwathWidthInWineBuffewChwoma =
							mode_wib->ms.ip.wine_buffew_size_bits
									* dmw_max(mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma[k], 1.0)
									/ mode_wib->ms.cache_dispway_cfg.pwane.WBBitPewPixew[k]
									/ (mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k]
									+ dmw_max(dmw_ceiw(mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k], 1.0) - 2, 0.0));
		}
		mode_wib->ms.MaximumSwathWidthWuma[k] = dmw_min(s->MaximumSwathWidthSuppowtWuma, mode_wib->ms.MaximumSwathWidthInWineBuffewWuma);
		mode_wib->ms.MaximumSwathWidthChwoma[k] = dmw_min(s->MaximumSwathWidthSuppowtChwoma, mode_wib->ms.MaximumSwathWidthInWineBuffewChwoma);
	}

	/*Numbew Of DSC Swices*/
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
			if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] > 4800) {
				mode_wib->ms.suppowt.NumbewOfDSCSwices[k] = (dmw_uint_t)(dmw_ceiw(mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 600, 4));
			} ewse if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] > 2400) {
				mode_wib->ms.suppowt.NumbewOfDSCSwices[k] = 8;
			} ewse if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] > 1200) {
				mode_wib->ms.suppowt.NumbewOfDSCSwices[k] = 4;
			} ewse if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] > 340) {
				mode_wib->ms.suppowt.NumbewOfDSCSwices[k] = 2;
			} ewse {
				mode_wib->ms.suppowt.NumbewOfDSCSwices[k] = 1;
			}
		} ewse {
			mode_wib->ms.suppowt.NumbewOfDSCSwices[k] = 0;
		}
	}

	CawcuwateSwathAndDETConfiguwation_pawams->DETSizeOvewwide = mode_wib->ms.cache_dispway_cfg.pwane.DETSizeOvewwide;
	CawcuwateSwathAndDETConfiguwation_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
	CawcuwateSwathAndDETConfiguwation_pawams->ConfigWetuwnBuffewSizeInKByte = mode_wib->ms.ip.config_wetuwn_buffew_size_in_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->WOBBuffewSizeInKByte = mode_wib->ms.ip.wob_buffew_size_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->MaxTotawDETInKByte = mode_wib->ms.MaxTotawDETInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->MinCompwessedBuffewSizeInKByte = mode_wib->ms.MinCompwessedBuffewSizeInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->PixewChunkSizeInKByte = mode_wib->ms.ip.pixew_chunk_size_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->FowceSingweDPP = 1;
	CawcuwateSwathAndDETConfiguwation_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
	CawcuwateSwathAndDETConfiguwation_pawams->nomDETInKByte = mode_wib->ms.NomDETInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->UseUnboundedWequestingFinaw = mode_wib->ms.powicy.UseUnboundedWequesting;
	CawcuwateSwathAndDETConfiguwation_pawams->ConfigWetuwnBuffewSegmentSizeInkByte = mode_wib->ms.ip.config_wetuwn_buffew_segment_size_in_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->CompwessedBuffewSegmentSizeInkByteFinaw = mode_wib->ms.ip.compwessed_buffew_segment_size_in_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->Output = mode_wib->ms.cache_dispway_cfg.output.OutputEncodew;
	CawcuwateSwathAndDETConfiguwation_pawams->WeadBandwidthWuma = mode_wib->ms.WeadBandwidthWuma;
	CawcuwateSwathAndDETConfiguwation_pawams->WeadBandwidthChwoma = mode_wib->ms.WeadBandwidthChwoma;
	CawcuwateSwathAndDETConfiguwation_pawams->MaximumSwathWidthWuma = mode_wib->ms.MaximumSwathWidthWuma;
	CawcuwateSwathAndDETConfiguwation_pawams->MaximumSwathWidthChwoma = mode_wib->ms.MaximumSwathWidthChwoma;
	CawcuwateSwathAndDETConfiguwation_pawams->SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtStationawy = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy;
	CawcuwateSwathAndDETConfiguwation_pawams->SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceTiwing = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtWidth = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtHeight = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtXStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtYStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtXStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtYStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceWidthY = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceWidthC = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceHeightY = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceHeightC = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockHeightY = mode_wib->ms.Wead256BwockHeightY;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockHeightC = mode_wib->ms.Wead256BwockHeightC;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockWidthY = mode_wib->ms.Wead256BwockWidthY;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockWidthC = mode_wib->ms.Wead256BwockWidthC;
	CawcuwateSwathAndDETConfiguwation_pawams->ODMMode = s->dummy_odm_mode;
	CawcuwateSwathAndDETConfiguwation_pawams->BwendingAndTiming = mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixY = mode_wib->ms.BytePewPixewY;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixC = mode_wib->ms.BytePewPixewC;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixDETY = mode_wib->ms.BytePewPixewInDETY;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixDETC = mode_wib->ms.BytePewPixewInDETC;
	CawcuwateSwathAndDETConfiguwation_pawams->HActive = mode_wib->ms.cache_dispway_cfg.timing.HActive;
	CawcuwateSwathAndDETConfiguwation_pawams->HWatio = mode_wib->ms.cache_dispway_cfg.pwane.HWatio;
	CawcuwateSwathAndDETConfiguwation_pawams->HWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma;
	CawcuwateSwathAndDETConfiguwation_pawams->DPPPewSuwface = s->dummy_integew_awway[0];
	CawcuwateSwathAndDETConfiguwation_pawams->swath_width_wuma_ub = s->dummy_integew_awway[1];
	CawcuwateSwathAndDETConfiguwation_pawams->swath_width_chwoma_ub = s->dummy_integew_awway[2];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathWidth = s->dummy_integew_awway[3];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathWidthChwoma = s->dummy_integew_awway[4];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathHeightY = s->dummy_integew_awway[5];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathHeightC = s->dummy_integew_awway[6];
	CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeInKByte = s->dummy_integew_awway[7];
	CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeY = mode_wib->ms.DETBuffewSizeY;
	CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeC = mode_wib->ms.DETBuffewSizeC;
	CawcuwateSwathAndDETConfiguwation_pawams->UnboundedWequestEnabwed = &s->dummy_boowean[0];
	CawcuwateSwathAndDETConfiguwation_pawams->compbuf_wesewved_space_64b = &s->dummy_integew[2];
	CawcuwateSwathAndDETConfiguwation_pawams->compbuf_wesewved_space_zs = &s->dummy_integew[1];
	CawcuwateSwathAndDETConfiguwation_pawams->CompwessedBuffewSizeInkByte = &s->dummy_integew[0];
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtSizeSuppowtPewSuwface = mode_wib->ms.SingweDPPViewpowtSizeSuppowtPewSuwface;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtSizeSuppowt = &s->dummy_boowean[1];

	CawcuwateSwathAndDETConfiguwation(&mode_wib->scwatch,
	CawcuwateSwathAndDETConfiguwation_pawams); /* dmw_boow_t *ViewpowtSizeSuppowt */

	s->MPCCombineMethodAsNeededFowPStateChangeAndVowtage = fawse;
	s->MPCCombineMethodAsPossibwe = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.powicy.MPCCombineUse[k] == dmw_mpc_as_needed_fow_pstate_and_vowtage)
			s->MPCCombineMethodAsNeededFowPStateChangeAndVowtage = twue;
		if (mode_wib->ms.powicy.MPCCombineUse[k] == dmw_mpc_as_possibwe)
			s->MPCCombineMethodAsPossibwe = twue;
	}
	mode_wib->ms.suppowt.MPCCombineMethodIncompatibwe = s->MPCCombineMethodAsNeededFowPStateChangeAndVowtage && s->MPCCombineMethodAsPossibwe;

	fow (j = 0; j < 2; j++) {
		mode_wib->ms.TotawNumbewOfActiveDPP[j] = 0;
		mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] = twue;

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			CawcuwateODMMode(
					mode_wib->ms.ip.maximum_pixews_pew_wine_pew_dsc_unit,
					mode_wib->ms.cache_dispway_cfg.timing.HActive[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k],
					mode_wib->ms.powicy.ODMUse[k],
					mode_wib->ms.state.dispcwk_mhz,
					mode_wib->ms.max_state.dispcwk_mhz,
					fawse, // DSCEnabwe
					mode_wib->ms.TotawNumbewOfActiveDPP[j],
					mode_wib->ms.ip.max_num_dpp,
					mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
					mode_wib->ms.soc.dcn_downspwead_pewcent,
					mode_wib->ms.ip.dispcwk_wamp_mawgin_pewcent,
					mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz,

					/* Output */
					&s->TotawAvaiwabwePipesSuppowtNoDSC,
					&s->NumbewOfDPPNoDSC,
					&s->ODMModeNoDSC,
					&s->WequiwedDISPCWKPewSuwfaceNoDSC);

			CawcuwateODMMode(
					mode_wib->ms.ip.maximum_pixews_pew_wine_pew_dsc_unit,
					mode_wib->ms.cache_dispway_cfg.timing.HActive[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k],
					mode_wib->ms.powicy.ODMUse[k],
					mode_wib->ms.state.dispcwk_mhz,
					mode_wib->ms.max_state.dispcwk_mhz,
					twue, // DSCEnabwe
					mode_wib->ms.TotawNumbewOfActiveDPP[j],
					mode_wib->ms.ip.max_num_dpp,
					mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
					mode_wib->ms.soc.dcn_downspwead_pewcent,
					mode_wib->ms.ip.dispcwk_wamp_mawgin_pewcent,
					mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz,

					/* Output */
					&s->TotawAvaiwabwePipesSuppowtDSC,
					&s->NumbewOfDPPDSC,
					&s->ODMModeDSC,
					&s->WequiwedDISPCWKPewSuwfaceDSC);

			CawcuwateOutputWink(
					mode_wib->ms.state.phycwk_mhz,
					mode_wib->ms.state.phycwk_d18_mhz,
					mode_wib->ms.state.phycwk_d32_mhz,
					mode_wib->ms.soc.phy_downspwead_pewcent,
					(mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k),
					mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k],
					mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k],
					mode_wib->ms.cache_dispway_cfg.timing.HActive[k],
					mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k],
					mode_wib->ms.cache_dispway_cfg.output.FowcedOutputWinkBPP[k],
					mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k],
					mode_wib->ms.suppowt.NumbewOfDSCSwices[k],
					mode_wib->ms.cache_dispway_cfg.output.AudioSampweWate[k],
					mode_wib->ms.cache_dispway_cfg.output.AudioSampweWayout[k],
					s->ODMModeNoDSC,
					s->ODMModeDSC,
					mode_wib->ms.cache_dispway_cfg.output.DSCEnabwe[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWanes[k],
					mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k],

					/* Output */
					&mode_wib->ms.WequiwesDSC[k],
					&mode_wib->ms.WequiwesFEC[k],
					&mode_wib->ms.OutputBppPewState[k],
					&mode_wib->ms.OutputTypePewState[k], // VBA_DEWTA, VBA uses a stwing to wepwesent type and wate, but DMW uses enum, don't want to wewy on stwng
					&mode_wib->ms.OutputWatePewState[k],
					&mode_wib->ms.WequiwedSwots[k]);

			if (mode_wib->ms.WequiwesDSC[k] == fawse) {
				mode_wib->ms.ODMModePewState[k] = s->ODMModeNoDSC;
				mode_wib->ms.WequiwedDISPCWKPewSuwface[j][k] = s->WequiwedDISPCWKPewSuwfaceNoDSC;
				if (!s->TotawAvaiwabwePipesSuppowtNoDSC)
					mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] = fawse;
				mode_wib->ms.TotawNumbewOfActiveDPP[j] = mode_wib->ms.TotawNumbewOfActiveDPP[j] + s->NumbewOfDPPNoDSC;
			} ewse {
				mode_wib->ms.ODMModePewState[k] = s->ODMModeDSC;
				mode_wib->ms.WequiwedDISPCWKPewSuwface[j][k] = s->WequiwedDISPCWKPewSuwfaceDSC;
				if (!s->TotawAvaiwabwePipesSuppowtDSC)
					mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] = fawse;
				mode_wib->ms.TotawNumbewOfActiveDPP[j] = mode_wib->ms.TotawNumbewOfActiveDPP[j] + s->NumbewOfDPPDSC;
			}
		}

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_4to1) {
				mode_wib->ms.MPCCombine[j][k] = fawse;
				mode_wib->ms.NoOfDPP[j][k] = 4;
			} ewse if (mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_2to1) {
				mode_wib->ms.MPCCombine[j][k] = fawse;
				mode_wib->ms.NoOfDPP[j][k] = 2;
			} ewse if (mode_wib->ms.powicy.MPCCombineUse[k] == dmw_mpc_disabwed) {
				mode_wib->ms.MPCCombine[j][k] = fawse;
				mode_wib->ms.NoOfDPP[j][k] = 1;
			} ewse if (WoundToDFSGwanuwawity(mode_wib->ms.MinDPPCWKUsingSingweDPP[k] * (1 + mode_wib->ms.soc.dcn_downspwead_pewcent / 100),
											1, mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz) <= mode_wib->ms.state.dppcwk_mhz &&
											mode_wib->ms.SingweDPPViewpowtSizeSuppowtPewSuwface[k] == twue) {
				mode_wib->ms.MPCCombine[j][k] = fawse;
				mode_wib->ms.NoOfDPP[j][k] = 1;
			} ewse if (mode_wib->ms.TotawNumbewOfActiveDPP[j] < (dmw_uint_t) mode_wib->ms.ip.max_num_dpp) {
				mode_wib->ms.MPCCombine[j][k] = twue;
				mode_wib->ms.NoOfDPP[j][k] = 2;
				mode_wib->ms.TotawNumbewOfActiveDPP[j] = (dmw_uint_t) mode_wib->ms.TotawNumbewOfActiveDPP[j] + 1;
			} ewse {
				mode_wib->ms.MPCCombine[j][k] = fawse;
				mode_wib->ms.NoOfDPP[j][k] = 1;
				mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] = fawse;
			}
		}

		mode_wib->ms.TotawNumbewOfSingweDPPSuwfaces[j] = 0;
		s->NoChwomaOwWineaw = twue;
		fow (k = 0; k < (dmw_uint_t) mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.NoOfDPP[j][k] == 1)
				mode_wib->ms.TotawNumbewOfSingweDPPSuwfaces[j] = mode_wib->ms.TotawNumbewOfSingweDPPSuwfaces[j] + 1;
			if (mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_420_8
					|| mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_420_10
					|| mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_420_12
					|| mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] == dmw_wgbe_awpha
					|| mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k] == dmw_sw_wineaw) {
				s->NoChwomaOwWineaw = fawse;
			}
		}

		if (j == 1 && !UnboundedWequest(mode_wib->ms.powicy.UseUnboundedWequesting,
				mode_wib->ms.TotawNumbewOfActiveDPP[j], s->NoChwomaOwWineaw,
				mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[0])) {
			whiwe (!(mode_wib->ms.TotawNumbewOfActiveDPP[j] >= (dmw_uint_t) mode_wib->ms.ip.max_num_dpp || mode_wib->ms.TotawNumbewOfSingweDPPSuwfaces[j] == 0)) {
				s->BWOfNonCombinedSuwfaceOfMaximumBandwidth = 0;
				s->NumbewOfNonCombinedSuwfaceOfMaximumBandwidth = 0;
				fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
					if (mode_wib->ms.powicy.MPCCombineUse[k] != dmw_mpc_disabwed && mode_wib->ms.powicy.MPCCombineUse[k] != dmw_mpc_as_needed_fow_vowtage &&
						mode_wib->ms.WeadBandwidthWuma[k] + mode_wib->ms.WeadBandwidthChwoma[k] > s->BWOfNonCombinedSuwfaceOfMaximumBandwidth &&
						(mode_wib->ms.ODMModePewState[k] != dmw_odm_mode_combine_2to1 && mode_wib->ms.ODMModePewState[k] != dmw_odm_mode_combine_4to1) &&
						mode_wib->ms.MPCCombine[j][k] == fawse) {
						s->BWOfNonCombinedSuwfaceOfMaximumBandwidth = mode_wib->ms.WeadBandwidthWuma[k] + mode_wib->ms.WeadBandwidthChwoma[k];
						s->NumbewOfNonCombinedSuwfaceOfMaximumBandwidth = k;
					}
				}
				mode_wib->ms.MPCCombine[j][s->NumbewOfNonCombinedSuwfaceOfMaximumBandwidth] = twue;
				mode_wib->ms.NoOfDPP[j][s->NumbewOfNonCombinedSuwfaceOfMaximumBandwidth] = 2;
				mode_wib->ms.TotawNumbewOfActiveDPP[j] = mode_wib->ms.TotawNumbewOfActiveDPP[j] + 1;
				mode_wib->ms.TotawNumbewOfSingweDPPSuwfaces[j] = mode_wib->ms.TotawNumbewOfSingweDPPSuwfaces[j] - 1;
			}
		}

		//DISPCWK/DPPCWK
		mode_wib->ms.WwitebackWequiwedDISPCWK = 0;
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k]) {
				mode_wib->ms.WwitebackWequiwedDISPCWK = dmw_max(mode_wib->ms.WwitebackWequiwedDISPCWK,
																	CawcuwateWwiteBackDISPCWK(mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[k],
																							mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
																							mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k],
																							mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k],
																							mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHTaps[k],
																							mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k],
																							mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceWidth[k],
																							mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k],
																							mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k],
																							mode_wib->ms.ip.wwiteback_wine_buffew_buffew_size,
																							mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz));
			}
		}

		 mode_wib->ms.WequiwedDISPCWK[j] = mode_wib->ms.WwitebackWequiwedDISPCWK;
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.WequiwedDISPCWK[j] = dmw_max(mode_wib->ms.WequiwedDISPCWK[j], mode_wib->ms.WequiwedDISPCWKPewSuwface[j][k]);
		}

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.NoOfDPPThisState[k] = mode_wib->ms.NoOfDPP[j][k];
		}

		CawcuwateDPPCWK(mode_wib->ms.num_active_pwanes,
					mode_wib->ms.soc.dcn_downspwead_pewcent,
					mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz,
					mode_wib->ms.MinDPPCWKUsingSingweDPP,
					mode_wib->ms.NoOfDPPThisState,
					/* Output */
					&mode_wib->ms.GwobawDPPCWK,
					mode_wib->ms.WequiwedDPPCWKThisState);

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.WequiwedDPPCWKPewSuwface[j][k] = mode_wib->ms.WequiwedDPPCWKThisState[k];
		}

		mode_wib->ms.suppowt.DISPCWK_DPPCWK_Suppowt[j] = !((mode_wib->ms.WequiwedDISPCWK[j] > mode_wib->ms.state.dispcwk_mhz) || (mode_wib->ms.GwobawDPPCWK > mode_wib->ms.state.dppcwk_mhz));

		if (mode_wib->ms.TotawNumbewOfActiveDPP[j] > (dmw_uint_t) mode_wib->ms.ip.max_num_dpp) {
			mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] = fawse;
		}
	} // j

	/* Totaw Avaiwabwe OTG, HDMIFWW, DP Suppowt Check */
	s->TotawNumbewOfActiveOTG = 0;
	s->TotawNumbewOfActiveHDMIFWW = 0;
	s->TotawNumbewOfActiveDP2p0 = 0;
	s->TotawNumbewOfActiveDP2p0Outputs = 0;

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
			s->TotawNumbewOfActiveOTG = s->TotawNumbewOfActiveOTG + 1;
			if (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww)
				s->TotawNumbewOfActiveHDMIFWW = s->TotawNumbewOfActiveHDMIFWW + 1;
			if (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp2p0) {
				s->TotawNumbewOfActiveDP2p0 = s->TotawNumbewOfActiveDP2p0 + 1;
				if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == k || mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamEn[k] == fawse) {
					s->TotawNumbewOfActiveDP2p0Outputs = s->TotawNumbewOfActiveDP2p0Outputs + 1;
				}
			}
		}
	}

	mode_wib->ms.suppowt.NumbewOfOTGSuppowt      = (s->TotawNumbewOfActiveOTG <= (dmw_uint_t) mode_wib->ms.ip.max_num_otg);
	mode_wib->ms.suppowt.NumbewOfHDMIFWWSuppowt  = (s->TotawNumbewOfActiveHDMIFWW <= (dmw_uint_t) mode_wib->ms.ip.max_num_hdmi_fww_outputs);
	mode_wib->ms.suppowt.NumbewOfDP2p0Suppowt    = (s->TotawNumbewOfActiveDP2p0 <= (dmw_uint_t) mode_wib->ms.ip.max_num_dp2p0_stweams && s->TotawNumbewOfActiveDP2p0Outputs <= (dmw_uint_t) mode_wib->ms.ip.max_num_dp2p0_outputs);

	/* Dispway IO and DSC Suppowt Check */
	mode_wib->ms.suppowt.NonsuppowtedDSCInputBPC = fawse;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.output.OutputDisabwed[k] == fawse &&
			!(mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k] == 12.0
				|| mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k] == 10.0
				|| mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k] == 8.0
				|| mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k] > (dmw_uint_t) mode_wib->ms.ip.maximum_dsc_bits_pew_component
				)) {
			mode_wib->ms.suppowt.NonsuppowtedDSCInputBPC = twue;
		}
	}

	mode_wib->ms.suppowt.ExceededMuwtistweamSwots = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == k) {
			s->TotawSwots = mode_wib->ms.WequiwedSwots[k];
			fow (j = 0; j < mode_wib->ms.num_active_pwanes; ++j) {
				if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[j] == k)
					s->TotawSwots = s->TotawSwots + mode_wib->ms.WequiwedSwots[j];
			}
			if (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp && s->TotawSwots > 63)
				mode_wib->ms.suppowt.ExceededMuwtistweamSwots = twue;
			if (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp2p0 && s->TotawSwots > 64)
				mode_wib->ms.suppowt.ExceededMuwtistweamSwots = twue;
		}
	}
	mode_wib->ms.suppowt.WinkCapacitySuppowt = twue;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.output.OutputDisabwed[k] == fawse &&
			mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k && (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp2p0 || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_edp ||
			mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmi || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww) && mode_wib->ms.OutputBppPewState[k] == 0) {
			mode_wib->ms.suppowt.WinkCapacitySuppowt = fawse;
		}
	}

	mode_wib->ms.suppowt.P2IWith420 = fawse;
	mode_wib->ms.suppowt.DSCOnwyIfNecessawyWithBPP = fawse;
	mode_wib->ms.suppowt.DSC422NativeNotSuppowted = fawse;
	mode_wib->ms.suppowt.WinkWateDoesNotMatchDPVewsion = fawse;
	mode_wib->ms.suppowt.WinkWateFowMuwtistweamNotIndicated = fawse;
	mode_wib->ms.suppowt.BPPFowMuwtistweamNotIndicated = fawse;
	mode_wib->ms.suppowt.MuwtistweamWithHDMIOweDP = fawse;
	mode_wib->ms.suppowt.MSOOwODMSpwitWithNonDPWink = fawse;
	mode_wib->ms.suppowt.NotEnoughWanesFowMSO = fawse;

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k && (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp2p0 || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_edp ||
														mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmi || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww)) {
			if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_420 && mode_wib->ms.cache_dispway_cfg.timing.Intewwace[k] == 1 && mode_wib->ms.ip.ptoi_suppowted == twue)
				mode_wib->ms.suppowt.P2IWith420 = twue;

			if (mode_wib->ms.cache_dispway_cfg.output.DSCEnabwe[k] == dmw_dsc_enabwe_if_necessawy && mode_wib->ms.cache_dispway_cfg.output.FowcedOutputWinkBPP[k] != 0)
				mode_wib->ms.suppowt.DSCOnwyIfNecessawyWithBPP = twue;
			if ((mode_wib->ms.cache_dispway_cfg.output.DSCEnabwe[k] == dmw_dsc_enabwe || mode_wib->ms.cache_dispway_cfg.output.DSCEnabwe[k] == dmw_dsc_enabwe_if_necessawy) && mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_n422 && !mode_wib->ms.ip.dsc422_native_suppowt)
				mode_wib->ms.suppowt.DSC422NativeNotSuppowted = twue;

			if (((mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_hbw || mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_hbw2 || mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_hbw3) &&
					mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] != dmw_dp && mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] != dmw_edp) ||
					((mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_uhbw10 || mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_uhbw13p5 || mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_uhbw20) &&
					mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] != dmw_dp2p0))
				mode_wib->ms.suppowt.WinkWateDoesNotMatchDPVewsion = twue;

			if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamEn[k] == 1) {
				if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == k && mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWate[k] == dmw_dp_wate_na)
					mode_wib->ms.suppowt.WinkWateFowMuwtistweamNotIndicated = twue;
				if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == k && mode_wib->ms.cache_dispway_cfg.output.FowcedOutputWinkBPP[k] == 0)
					mode_wib->ms.suppowt.BPPFowMuwtistweamNotIndicated = twue;
				fow (j = 0; j < mode_wib->ms.num_active_pwanes; ++j) {
					if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == j && mode_wib->ms.cache_dispway_cfg.output.FowcedOutputWinkBPP[k] == 0)
						mode_wib->ms.suppowt.BPPFowMuwtistweamNotIndicated = twue;
				}
			}

			if ((mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_edp || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmi || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww)) {
				if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamEn[k] == 1 && mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == k)
					mode_wib->ms.suppowt.MuwtistweamWithHDMIOweDP = twue;
				fow (j = 0; j < mode_wib->ms.num_active_pwanes; ++j) {
					if (mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamEn[k] == 1 && mode_wib->ms.cache_dispway_cfg.output.OutputMuwtistweamId[k] == j)
						mode_wib->ms.suppowt.MuwtistweamWithHDMIOweDP = twue;
				}
			}
			if (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] != dmw_dp && (mode_wib->ms.powicy.ODMUse[k] == dmw_odm_use_powicy_spwit_1to2 ||
				mode_wib->ms.powicy.ODMUse[k] == dmw_odm_use_powicy_mso_1to2 || mode_wib->ms.powicy.ODMUse[k] == dmw_odm_use_powicy_mso_1to4))
				mode_wib->ms.suppowt.MSOOwODMSpwitWithNonDPWink = twue;

			if ((mode_wib->ms.powicy.ODMUse[k] == dmw_odm_use_powicy_mso_1to2 && mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWanes[k] < 2) ||
				(mode_wib->ms.powicy.ODMUse[k] == dmw_odm_use_powicy_mso_1to4 && mode_wib->ms.cache_dispway_cfg.output.OutputWinkDPWanes[k] < 4))
				mode_wib->ms.suppowt.NotEnoughWanesFowMSO = twue;
		}
	}

	mode_wib->ms.suppowt.DTBCWKWequiwedMoweThanSuppowted = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k &&
				mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww &&
				WequiwedDTBCWK(
							mode_wib->ms.WequiwesDSC[k],
							mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k],
							mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k],
							mode_wib->ms.OutputBppPewState[k],
							mode_wib->ms.suppowt.NumbewOfDSCSwices[k],
							mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k],
							mode_wib->ms.cache_dispway_cfg.timing.HActive[k],
							mode_wib->ms.cache_dispway_cfg.output.AudioSampweWate[k],
							mode_wib->ms.cache_dispway_cfg.output.AudioSampweWayout[k]) > mode_wib->ms.state.dtbcwk_mhz) {
								mode_wib->ms.suppowt.DTBCWKWequiwedMoweThanSuppowted = twue;
							}
	}

	mode_wib->ms.suppowt.ODMCombineTwoToOneSuppowtCheckOK = twue;
	mode_wib->ms.suppowt.ODMCombineFouwToOneSuppowtCheckOK = twue;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k && mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_2to1 && mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmi) {
			mode_wib->ms.suppowt.ODMCombineTwoToOneSuppowtCheckOK = fawse;
		}
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k && mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_4to1 && (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp ||
			mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_edp || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmi)) {
			mode_wib->ms.suppowt.ODMCombineFouwToOneSuppowtCheckOK = fawse;
		}
	}

	mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted = fawse;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
			if (mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp ||
				mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_dp2p0 ||
				mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_edp ||
				mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww) {
				if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_420) {
					s->DSCFowmatFactow = 2;
				} ewse if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_444) {
					s->DSCFowmatFactow = 1;
				} ewse if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_n422 || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww) {
					s->DSCFowmatFactow = 2;
				} ewse {
					s->DSCFowmatFactow = 1;
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%u, WequiwesDSC = %u\n",  __func__, k, mode_wib->ms.WequiwesDSC[k]);
#endif
				if (mode_wib->ms.WequiwesDSC[k] == twue) {
					if (mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_4to1) {
						if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 12.0 / (dmw_fwoat_t)s->DSCFowmatFactow > (1.0 - mode_wib->ms.soc.dcn_downspwead_pewcent / 100.0) * mode_wib->ms.state.dsccwk_mhz) {
#ifdef __DMW_VBA_DEBUG__
							dmw_pwint("DMW::%s: k=%u, PixewCwockBackEnd     = %f\n",  __func__, k, mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k]);
							dmw_pwint("DMW::%s: k=%u, DSCCWKPewState        = %f\n",  __func__, k, mode_wib->ms.state.dsccwk_mhz);
							dmw_pwint("DMW::%s: k=%u, DSCFowmatFactow       = %u\n",  __func__, k, s->DSCFowmatFactow);
#endif
							mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted = twue;
						}
					} ewse if (mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_2to1) {
						if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 6.0 / (dmw_fwoat_t)s->DSCFowmatFactow > (1.0 - mode_wib->ms.soc.dcn_downspwead_pewcent / 100.0) * mode_wib->ms.state.dsccwk_mhz) {
							mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted = twue;
						}
					} ewse {
						if (mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 3.0 / (dmw_fwoat_t)s->DSCFowmatFactow > (1.0 - mode_wib->ms.soc.dcn_downspwead_pewcent / 100.0) * mode_wib->ms.state.dsccwk_mhz) {
							mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted = twue;
						}
					}
				}
			}
		}
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DSCCWKWequiwedMoweThanSuppowted = %u\n",  __func__, mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted);
#endif

	/* Check DSC Unit and Swices Suppowt */
	mode_wib->ms.suppowt.NotEnoughDSCUnits = fawse;
	mode_wib->ms.suppowt.NotEnoughDSCSwices = fawse;
	s->TotawDSCUnitsWequiwed = 0;
	mode_wib->ms.suppowt.PixewsPewWinePewDSCUnitSuppowt = twue;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.WequiwesDSC[k] == twue) {
			if (mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_4to1) {
				if (mode_wib->ms.cache_dispway_cfg.timing.HActive[k] > 4 * (dmw_uint_t) mode_wib->ms.ip.maximum_pixews_pew_wine_pew_dsc_unit)
					mode_wib->ms.suppowt.PixewsPewWinePewDSCUnitSuppowt = fawse;
				s->TotawDSCUnitsWequiwed = s->TotawDSCUnitsWequiwed + 4;
				if (mode_wib->ms.suppowt.NumbewOfDSCSwices[k] > 16)
					mode_wib->ms.suppowt.NotEnoughDSCSwices = twue;
			} ewse if (mode_wib->ms.ODMModePewState[k] == dmw_odm_mode_combine_2to1) {
				if (mode_wib->ms.cache_dispway_cfg.timing.HActive[k] > 2 * (dmw_uint_t) mode_wib->ms.ip.maximum_pixews_pew_wine_pew_dsc_unit)
					mode_wib->ms.suppowt.PixewsPewWinePewDSCUnitSuppowt = fawse;
				s->TotawDSCUnitsWequiwed = s->TotawDSCUnitsWequiwed + 2;
				if (mode_wib->ms.suppowt.NumbewOfDSCSwices[k] > 8)
					mode_wib->ms.suppowt.NotEnoughDSCSwices = twue;
			} ewse {
				if (mode_wib->ms.cache_dispway_cfg.timing.HActive[k] > (dmw_uint_t) mode_wib->ms.ip.maximum_pixews_pew_wine_pew_dsc_unit)
					mode_wib->ms.suppowt.PixewsPewWinePewDSCUnitSuppowt = fawse;
				s->TotawDSCUnitsWequiwed = s->TotawDSCUnitsWequiwed + 1;
				if (mode_wib->ms.suppowt.NumbewOfDSCSwices[k] > 4)
					mode_wib->ms.suppowt.NotEnoughDSCSwices = twue;
			}
		}
	}
   if (s->TotawDSCUnitsWequiwed > (dmw_uint_t) mode_wib->ms.ip.num_dsc) {
		mode_wib->ms.suppowt.NotEnoughDSCUnits = twue;
	}

	/*DSC Deway pew state*/
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		mode_wib->ms.DSCDewayPewState[k] = DSCDewayWequiwement(mode_wib->ms.WequiwesDSC[k],
													mode_wib->ms.ODMModePewState[k],
													mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k],
													mode_wib->ms.OutputBppPewState[k],
													mode_wib->ms.cache_dispway_cfg.timing.HActive[k],
													mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k],
													mode_wib->ms.suppowt.NumbewOfDSCSwices[k],
													mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k],
													mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k],
													mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
													mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k]);
	}

	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		fow (m = 0; m <= mode_wib->ms.num_active_pwanes - 1; m++) {
			fow (j = 0; j <= mode_wib->ms.num_active_pwanes - 1; j++) {
				if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == m && mode_wib->ms.WequiwesDSC[m] == twue) {
					mode_wib->ms.DSCDewayPewState[k] = mode_wib->ms.DSCDewayPewState[m];
				}
			}
		}
	}

	//Cawcuwate Swath, DET Configuwation, DCFCWKDeepSweep
	//
	fow (j = 0; j < 2; ++j) {
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.WequiwedDPPCWKThisState[k] = mode_wib->ms.WequiwedDPPCWKPewSuwface[j][k];
			mode_wib->ms.NoOfDPPThisState[k] = mode_wib->ms.NoOfDPP[j][k];
			mode_wib->ms.ODMModeThisState[k] = mode_wib->ms.ODMModePewState[k];
		}

		CawcuwateSwathAndDETConfiguwation_pawams->DETSizeOvewwide = mode_wib->ms.cache_dispway_cfg.pwane.DETSizeOvewwide;
		CawcuwateSwathAndDETConfiguwation_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
		CawcuwateSwathAndDETConfiguwation_pawams->ConfigWetuwnBuffewSizeInKByte = mode_wib->ms.ip.config_wetuwn_buffew_size_in_kbytes;
		CawcuwateSwathAndDETConfiguwation_pawams->WOBBuffewSizeInKByte = mode_wib->ms.ip.wob_buffew_size_kbytes;
		CawcuwateSwathAndDETConfiguwation_pawams->MaxTotawDETInKByte = mode_wib->ms.MaxTotawDETInKByte;
		CawcuwateSwathAndDETConfiguwation_pawams->MinCompwessedBuffewSizeInKByte = mode_wib->ms.MinCompwessedBuffewSizeInKByte;
		CawcuwateSwathAndDETConfiguwation_pawams->PixewChunkSizeInKByte = mode_wib->ms.ip.pixew_chunk_size_kbytes;
		CawcuwateSwathAndDETConfiguwation_pawams->FowceSingweDPP = fawse;
		CawcuwateSwathAndDETConfiguwation_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
		CawcuwateSwathAndDETConfiguwation_pawams->nomDETInKByte = mode_wib->ms.NomDETInKByte;
		CawcuwateSwathAndDETConfiguwation_pawams->UseUnboundedWequestingFinaw = mode_wib->ms.powicy.UseUnboundedWequesting;
		CawcuwateSwathAndDETConfiguwation_pawams->ConfigWetuwnBuffewSegmentSizeInkByte = mode_wib->ms.ip.config_wetuwn_buffew_segment_size_in_kbytes;
		CawcuwateSwathAndDETConfiguwation_pawams->CompwessedBuffewSegmentSizeInkByteFinaw = mode_wib->ms.ip.compwessed_buffew_segment_size_in_kbytes;
		CawcuwateSwathAndDETConfiguwation_pawams->Output = mode_wib->ms.cache_dispway_cfg.output.OutputEncodew;
		CawcuwateSwathAndDETConfiguwation_pawams->WeadBandwidthWuma = mode_wib->ms.WeadBandwidthWuma;
		CawcuwateSwathAndDETConfiguwation_pawams->WeadBandwidthChwoma = mode_wib->ms.WeadBandwidthChwoma;
		CawcuwateSwathAndDETConfiguwation_pawams->MaximumSwathWidthWuma = mode_wib->ms.MaximumSwathWidthWuma;
		CawcuwateSwathAndDETConfiguwation_pawams->MaximumSwathWidthChwoma = mode_wib->ms.MaximumSwathWidthChwoma;
		CawcuwateSwathAndDETConfiguwation_pawams->SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtStationawy = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy;
		CawcuwateSwathAndDETConfiguwation_pawams->SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat;
		CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceTiwing = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtWidth = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtHeight = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtXStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtYStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtXStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtYStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC;
		CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceWidthY = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY;
		CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceWidthC = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC;
		CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceHeightY = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY;
		CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceHeightC = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC;
		CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockHeightY = mode_wib->ms.Wead256BwockHeightY;
		CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockHeightC = mode_wib->ms.Wead256BwockHeightC;
		CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockWidthY = mode_wib->ms.Wead256BwockWidthY;
		CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockWidthC = mode_wib->ms.Wead256BwockWidthC;
		CawcuwateSwathAndDETConfiguwation_pawams->ODMMode = mode_wib->ms.ODMModeThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->BwendingAndTiming = mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming;
		CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixY = mode_wib->ms.BytePewPixewY;
		CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixC = mode_wib->ms.BytePewPixewC;
		CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixDETY = mode_wib->ms.BytePewPixewInDETY;
		CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixDETC = mode_wib->ms.BytePewPixewInDETC;
		CawcuwateSwathAndDETConfiguwation_pawams->HActive = mode_wib->ms.cache_dispway_cfg.timing.HActive;
		CawcuwateSwathAndDETConfiguwation_pawams->HWatio = mode_wib->ms.cache_dispway_cfg.pwane.HWatio;
		CawcuwateSwathAndDETConfiguwation_pawams->HWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma;
		CawcuwateSwathAndDETConfiguwation_pawams->DPPPewSuwface = mode_wib->ms.NoOfDPPThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->swath_width_wuma_ub = mode_wib->ms.swath_width_wuma_ub_this_state;
		CawcuwateSwathAndDETConfiguwation_pawams->swath_width_chwoma_ub = mode_wib->ms.swath_width_chwoma_ub_this_state;
		CawcuwateSwathAndDETConfiguwation_pawams->SwathWidth = mode_wib->ms.SwathWidthYThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->SwathWidthChwoma = mode_wib->ms.SwathWidthCThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->SwathHeightY = mode_wib->ms.SwathHeightYThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->SwathHeightC = mode_wib->ms.SwathHeightCThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeInKByte = mode_wib->ms.DETBuffewSizeInKByteThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeY = mode_wib->ms.DETBuffewSizeYThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeC = mode_wib->ms.DETBuffewSizeCThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->UnboundedWequestEnabwed = &mode_wib->ms.UnboundedWequestEnabwedThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->compbuf_wesewved_space_64b = &s->dummy_integew[2];
		CawcuwateSwathAndDETConfiguwation_pawams->compbuf_wesewved_space_zs = &s->dummy_integew[1];
		CawcuwateSwathAndDETConfiguwation_pawams->CompwessedBuffewSizeInkByte = &mode_wib->ms.CompwessedBuffewSizeInkByteThisState;
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtSizeSuppowtPewSuwface = s->dummy_boowean_awway[0];
		CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtSizeSuppowt = &mode_wib->ms.suppowt.ViewpowtSizeSuppowt[j];

		CawcuwateSwathAndDETConfiguwation(&mode_wib->scwatch,
		CawcuwateSwathAndDETConfiguwation_pawams);

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.swath_width_wuma_ub_aww_states[j][k] = mode_wib->ms.swath_width_wuma_ub_this_state[k];
			mode_wib->ms.swath_width_chwoma_ub_aww_states[j][k] = mode_wib->ms.swath_width_chwoma_ub_this_state[k];
			mode_wib->ms.SwathWidthYAwwStates[j][k] = mode_wib->ms.SwathWidthYThisState[k];
			mode_wib->ms.SwathWidthCAwwStates[j][k] = mode_wib->ms.SwathWidthCThisState[k];
			mode_wib->ms.SwathHeightYAwwStates[j][k] = mode_wib->ms.SwathHeightYThisState[k];
			mode_wib->ms.SwathHeightCAwwStates[j][k] = mode_wib->ms.SwathHeightCThisState[k];
			mode_wib->ms.UnboundedWequestEnabwedAwwStates[j] = mode_wib->ms.UnboundedWequestEnabwedThisState;
			mode_wib->ms.CompwessedBuffewSizeInkByteAwwStates[j] = mode_wib->ms.CompwessedBuffewSizeInkByteThisState;
			mode_wib->ms.DETBuffewSizeInKByteAwwStates[j][k] = mode_wib->ms.DETBuffewSizeInKByteThisState[k];
			mode_wib->ms.DETBuffewSizeYAwwStates[j][k] = mode_wib->ms.DETBuffewSizeYThisState[k];
			mode_wib->ms.DETBuffewSizeCAwwStates[j][k] = mode_wib->ms.DETBuffewSizeCThisState[k];
		}
	}

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		mode_wib->ms.cuwsow_bw[k] = mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k] / 8.0 / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k];
	}

	CawcuwateSuwfaceSizeInMaww(
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.soc.maww_awwocated_fow_dcn_mbytes,
			mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight,
			mode_wib->ms.BytePewPixewY,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidthChwoma,
			mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeightChwoma,
			mode_wib->ms.BytePewPixewC,
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY,
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC,
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY,
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC,
			mode_wib->ms.Wead256BwockWidthY,
			mode_wib->ms.Wead256BwockWidthC,
			mode_wib->ms.Wead256BwockHeightY,
			mode_wib->ms.Wead256BwockHeightC,
			mode_wib->ms.MacwoTiweWidthY,
			mode_wib->ms.MacwoTiweWidthC,
			mode_wib->ms.MacwoTiweHeightY,
			mode_wib->ms.MacwoTiweHeightC,

			/* Output */
			mode_wib->ms.SuwfaceSizeInMAWW,
			&mode_wib->ms.suppowt.ExceededMAWWSize);

	fow (j = 0; j < 2; j++) {
		fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
			mode_wib->ms.swath_width_wuma_ub_this_state[k] = mode_wib->ms.swath_width_wuma_ub_aww_states[j][k];
			mode_wib->ms.swath_width_chwoma_ub_this_state[k] = mode_wib->ms.swath_width_chwoma_ub_aww_states[j][k];
			mode_wib->ms.SwathWidthYThisState[k] = mode_wib->ms.SwathWidthYAwwStates[j][k];
			mode_wib->ms.SwathWidthCThisState[k] = mode_wib->ms.SwathWidthCAwwStates[j][k];
			mode_wib->ms.SwathHeightYThisState[k] = mode_wib->ms.SwathHeightYAwwStates[j][k];
			mode_wib->ms.SwathHeightCThisState[k] = mode_wib->ms.SwathHeightCAwwStates[j][k];
			mode_wib->ms.DETBuffewSizeInKByteThisState[k] = mode_wib->ms.DETBuffewSizeInKByteAwwStates[j][k];
			mode_wib->ms.DETBuffewSizeYThisState[k] = mode_wib->ms.DETBuffewSizeYAwwStates[j][k];
			mode_wib->ms.DETBuffewSizeCThisState[k] = mode_wib->ms.DETBuffewSizeCAwwStates[j][k];
			mode_wib->ms.WequiwedDPPCWKThisState[k] = mode_wib->ms.WequiwedDPPCWKPewSuwface[j][k];
			mode_wib->ms.NoOfDPPThisState[k] = mode_wib->ms.NoOfDPP[j][k];
		}

		mode_wib->ms.TotawNumbewOfDCCActiveDPP[j] = 0;
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k] == twue) {
				mode_wib->ms.TotawNumbewOfDCCActiveDPP[j] = mode_wib->ms.TotawNumbewOfDCCActiveDPP[j] + mode_wib->ms.NoOfDPP[j][k];
			}
		}

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			s->SuwfPawametews[k].PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k];
			s->SuwfPawametews[k].DPPPewSuwface = mode_wib->ms.NoOfDPP[j][k];
			s->SuwfPawametews[k].SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k];
			s->SuwfPawametews[k].ViewpowtHeight = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight[k];
			s->SuwfPawametews[k].ViewpowtHeightChwoma = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeightChwoma[k];
			s->SuwfPawametews[k].BwockWidth256BytesY = mode_wib->ms.Wead256BwockWidthY[k];
			s->SuwfPawametews[k].BwockHeight256BytesY = mode_wib->ms.Wead256BwockHeightY[k];
			s->SuwfPawametews[k].BwockWidth256BytesC = mode_wib->ms.Wead256BwockWidthC[k];
			s->SuwfPawametews[k].BwockHeight256BytesC = mode_wib->ms.Wead256BwockHeightC[k];
			s->SuwfPawametews[k].BwockWidthY = mode_wib->ms.MacwoTiweWidthY[k];
			s->SuwfPawametews[k].BwockHeightY = mode_wib->ms.MacwoTiweHeightY[k];
			s->SuwfPawametews[k].BwockWidthC = mode_wib->ms.MacwoTiweWidthC[k];
			s->SuwfPawametews[k].BwockHeightC = mode_wib->ms.MacwoTiweHeightC[k];
			s->SuwfPawametews[k].IntewwaceEnabwe = mode_wib->ms.cache_dispway_cfg.timing.Intewwace[k];
			s->SuwfPawametews[k].HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k];
			s->SuwfPawametews[k].DCCEnabwe = mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k];
			s->SuwfPawametews[k].SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k];
			s->SuwfPawametews[k].SuwfaceTiwing = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k];
			s->SuwfPawametews[k].BytePewPixewY = mode_wib->ms.BytePewPixewY[k];
			s->SuwfPawametews[k].BytePewPixewC = mode_wib->ms.BytePewPixewC[k];
			s->SuwfPawametews[k].PwogwessiveToIntewwaceUnitInOPP = mode_wib->ms.ip.ptoi_suppowted;
			s->SuwfPawametews[k].VWatio = mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k];
			s->SuwfPawametews[k].VWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k];
			s->SuwfPawametews[k].VTaps = mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k];
			s->SuwfPawametews[k].VTapsChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k];
			s->SuwfPawametews[k].PitchY = mode_wib->ms.cache_dispway_cfg.suwface.PitchY[k];
			s->SuwfPawametews[k].DCCMetaPitchY = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchY[k];
			s->SuwfPawametews[k].PitchC = mode_wib->ms.cache_dispway_cfg.suwface.PitchC[k];
			s->SuwfPawametews[k].DCCMetaPitchC = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchC[k];
			s->SuwfPawametews[k].ViewpowtStationawy = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy[k];
			s->SuwfPawametews[k].ViewpowtXStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt[k];
			s->SuwfPawametews[k].ViewpowtYStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt[k];
			s->SuwfPawametews[k].ViewpowtXStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC[k];
			s->SuwfPawametews[k].ViewpowtYStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC[k];
			s->SuwfPawametews[k].FOWCE_ONE_WOW_FOW_FWAME = mode_wib->ms.cache_dispway_cfg.pwane.FowceOneWowFowFwame[k];
			s->SuwfPawametews[k].SwathHeightY = mode_wib->ms.SwathHeightYThisState[k];
			s->SuwfPawametews[k].SwathHeightC = mode_wib->ms.SwathHeightCThisState[k];
		}

		CawcuwateVMWowAndSwath_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
		CawcuwateVMWowAndSwath_pawams->myPipe = s->SuwfPawametews;
		CawcuwateVMWowAndSwath_pawams->SuwfaceSizeInMAWW = mode_wib->ms.SuwfaceSizeInMAWW;
		CawcuwateVMWowAndSwath_pawams->PTEBuffewSizeInWequestsWuma = mode_wib->ms.ip.dpte_buffew_size_in_pte_weqs_wuma;
		CawcuwateVMWowAndSwath_pawams->PTEBuffewSizeInWequestsChwoma = mode_wib->ms.ip.dpte_buffew_size_in_pte_weqs_chwoma;
		CawcuwateVMWowAndSwath_pawams->DCCMetaBuffewSizeBytes = mode_wib->ms.ip.dcc_meta_buffew_size_bytes;
		CawcuwateVMWowAndSwath_pawams->UseMAWWFowStaticScween = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween;
		CawcuwateVMWowAndSwath_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
		CawcuwateVMWowAndSwath_pawams->MAWWAwwocatedFowDCN = mode_wib->ms.soc.maww_awwocated_fow_dcn_mbytes;
		CawcuwateVMWowAndSwath_pawams->SwathWidthY = mode_wib->ms.SwathWidthYThisState;
		CawcuwateVMWowAndSwath_pawams->SwathWidthC = mode_wib->ms.SwathWidthCThisState;
		CawcuwateVMWowAndSwath_pawams->GPUVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe;
		CawcuwateVMWowAndSwath_pawams->HostVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe;
		CawcuwateVMWowAndSwath_pawams->HostVMMaxNonCachedPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews;
		CawcuwateVMWowAndSwath_pawams->GPUVMMaxPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews;
		CawcuwateVMWowAndSwath_pawams->GPUVMMinPageSizeKBytes = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMinPageSizeKBytes;
		CawcuwateVMWowAndSwath_pawams->HostVMMinPageSize = mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024;
		CawcuwateVMWowAndSwath_pawams->PTEBuffewModeOvewwideEn = mode_wib->ms.cache_dispway_cfg.pwane.PTEBuffewModeOvewwideEn;
		CawcuwateVMWowAndSwath_pawams->PTEBuffewModeOvewwideVaw = mode_wib->ms.cache_dispway_cfg.pwane.PTEBuffewMode;
		CawcuwateVMWowAndSwath_pawams->PTEBuffewSizeNotExceeded = mode_wib->ms.PTEBuffewSizeNotExceededPewState;
		CawcuwateVMWowAndSwath_pawams->DCCMetaBuffewSizeNotExceeded = mode_wib->ms.DCCMetaBuffewSizeNotExceededPewState;
		CawcuwateVMWowAndSwath_pawams->dpte_wow_width_wuma_ub = s->dummy_integew_awway[0];
		CawcuwateVMWowAndSwath_pawams->dpte_wow_width_chwoma_ub = s->dummy_integew_awway[1];
		CawcuwateVMWowAndSwath_pawams->dpte_wow_height_wuma = mode_wib->ms.dpte_wow_height;
		CawcuwateVMWowAndSwath_pawams->dpte_wow_height_chwoma = mode_wib->ms.dpte_wow_height_chwoma;
		CawcuwateVMWowAndSwath_pawams->dpte_wow_height_wineaw_wuma = s->dummy_integew_awway[2]; // VBA_DEWTA
		CawcuwateVMWowAndSwath_pawams->dpte_wow_height_wineaw_chwoma = s->dummy_integew_awway[3]; // VBA_DEWTA
		CawcuwateVMWowAndSwath_pawams->meta_weq_width = s->dummy_integew_awway[4];
		CawcuwateVMWowAndSwath_pawams->meta_weq_width_chwoma = s->dummy_integew_awway[5];
		CawcuwateVMWowAndSwath_pawams->meta_weq_height = s->dummy_integew_awway[6];
		CawcuwateVMWowAndSwath_pawams->meta_weq_height_chwoma = s->dummy_integew_awway[7];
		CawcuwateVMWowAndSwath_pawams->meta_wow_width = s->dummy_integew_awway[8];
		CawcuwateVMWowAndSwath_pawams->meta_wow_width_chwoma = s->dummy_integew_awway[9];
		CawcuwateVMWowAndSwath_pawams->meta_wow_height = mode_wib->ms.meta_wow_height;
		CawcuwateVMWowAndSwath_pawams->meta_wow_height_chwoma = mode_wib->ms.meta_wow_height_chwoma;
		CawcuwateVMWowAndSwath_pawams->vm_gwoup_bytes = s->dummy_integew_awway[10];
		CawcuwateVMWowAndSwath_pawams->dpte_gwoup_bytes = mode_wib->ms.dpte_gwoup_bytes;
		CawcuwateVMWowAndSwath_pawams->PixewPTEWeqWidthY = s->dummy_integew_awway[11];
		CawcuwateVMWowAndSwath_pawams->PixewPTEWeqHeightY = s->dummy_integew_awway[12];
		CawcuwateVMWowAndSwath_pawams->PTEWequestSizeY = s->dummy_integew_awway[13];
		CawcuwateVMWowAndSwath_pawams->PixewPTEWeqWidthC = s->dummy_integew_awway[14];
		CawcuwateVMWowAndSwath_pawams->PixewPTEWeqHeightC = s->dummy_integew_awway[15];
		CawcuwateVMWowAndSwath_pawams->PTEWequestSizeC = s->dummy_integew_awway[16];
		CawcuwateVMWowAndSwath_pawams->dpde0_bytes_pew_fwame_ub_w = s->dummy_integew_awway[17];
		CawcuwateVMWowAndSwath_pawams->meta_pte_bytes_pew_fwame_ub_w = s->dummy_integew_awway[18];
		CawcuwateVMWowAndSwath_pawams->dpde0_bytes_pew_fwame_ub_c = s->dummy_integew_awway[19];
		CawcuwateVMWowAndSwath_pawams->meta_pte_bytes_pew_fwame_ub_c = s->dummy_integew_awway[20];
		CawcuwateVMWowAndSwath_pawams->PwefetchSouwceWinesY = mode_wib->ms.PwefetchWinesYThisState;
		CawcuwateVMWowAndSwath_pawams->PwefetchSouwceWinesC = mode_wib->ms.PwefetchWinesCThisState;
		CawcuwateVMWowAndSwath_pawams->VInitPweFiwwY = mode_wib->ms.PwefiwwY;
		CawcuwateVMWowAndSwath_pawams->VInitPweFiwwC = mode_wib->ms.PwefiwwC;
		CawcuwateVMWowAndSwath_pawams->MaxNumSwathY = mode_wib->ms.MaxNumSwY;
		CawcuwateVMWowAndSwath_pawams->MaxNumSwathC = mode_wib->ms.MaxNumSwC;
		CawcuwateVMWowAndSwath_pawams->meta_wow_bw = mode_wib->ms.meta_wow_bandwidth_this_state;
		CawcuwateVMWowAndSwath_pawams->dpte_wow_bw = mode_wib->ms.dpte_wow_bandwidth_this_state;
		CawcuwateVMWowAndSwath_pawams->PixewPTEBytesPewWow = mode_wib->ms.DPTEBytesPewWowThisState;
		CawcuwateVMWowAndSwath_pawams->PDEAndMetaPTEBytesFwame = mode_wib->ms.PDEAndMetaPTEBytesPewFwameThisState;
		CawcuwateVMWowAndSwath_pawams->MetaWowByte = mode_wib->ms.MetaWowBytesThisState;
		CawcuwateVMWowAndSwath_pawams->use_one_wow_fow_fwame = mode_wib->ms.use_one_wow_fow_fwame_this_state;
		CawcuwateVMWowAndSwath_pawams->use_one_wow_fow_fwame_fwip = mode_wib->ms.use_one_wow_fow_fwame_fwip_this_state;
		CawcuwateVMWowAndSwath_pawams->UsesMAWWFowStaticScween = s->dummy_boowean_awway[0];
		CawcuwateVMWowAndSwath_pawams->PTE_BUFFEW_MODE = s->dummy_boowean_awway[1];
		CawcuwateVMWowAndSwath_pawams->BIGK_FWAGMENT_SIZE = s->dummy_integew_awway[21];

		CawcuwateVMWowAndSwath(&mode_wib->scwatch,
			CawcuwateVMWowAndSwath_pawams);

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			mode_wib->ms.PwefetchWinesY[j][k] = mode_wib->ms.PwefetchWinesYThisState[k];
			mode_wib->ms.PwefetchWinesC[j][k] = mode_wib->ms.PwefetchWinesCThisState[k];
			mode_wib->ms.meta_wow_bandwidth[j][k] = mode_wib->ms.meta_wow_bandwidth_this_state[k];
			mode_wib->ms.dpte_wow_bandwidth[j][k] = mode_wib->ms.dpte_wow_bandwidth_this_state[k];
			mode_wib->ms.DPTEBytesPewWow[j][k] = mode_wib->ms.DPTEBytesPewWowThisState[k];
			mode_wib->ms.PDEAndMetaPTEBytesPewFwame[j][k] = mode_wib->ms.PDEAndMetaPTEBytesPewFwameThisState[k];
			mode_wib->ms.MetaWowBytes[j][k] = mode_wib->ms.MetaWowBytesThisState[k];
			mode_wib->ms.use_one_wow_fow_fwame[j][k] = mode_wib->ms.use_one_wow_fow_fwame_this_state[k];
			mode_wib->ms.use_one_wow_fow_fwame_fwip[j][k] = mode_wib->ms.use_one_wow_fow_fwame_fwip_this_state[k];
		}

		mode_wib->ms.suppowt.PTEBuffewSizeNotExceeded[j] = twue;

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.PTEBuffewSizeNotExceededPewState[k] == fawse)
				mode_wib->ms.suppowt.PTEBuffewSizeNotExceeded[j] = fawse;
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: j=%u k=%u, PTEBuffewSizeNotExceededPewState[%u] = %u\n",  __func__, j, k, k, mode_wib->ms.PTEBuffewSizeNotExceededPewState[k]);
#endif
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: PTEBuffewSizeNotExceeded[%u] = %u\n",  __func__, j, mode_wib->ms.suppowt.PTEBuffewSizeNotExceeded[j]);
#endif

		mode_wib->ms.suppowt.DCCMetaBuffewSizeNotExceeded[j] = twue;
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.DCCMetaBuffewSizeNotExceededPewState[k] == fawse)
				mode_wib->ms.suppowt.DCCMetaBuffewSizeNotExceeded[j] = fawse;
		}

		mode_wib->ms.UwgWatency = CawcuwateUwgentWatency(mode_wib->ms.state.uwgent_watency_pixew_data_onwy_us,
													mode_wib->ms.state.uwgent_watency_pixew_mixed_with_vm_data_us,
													mode_wib->ms.state.uwgent_watency_vm_data_onwy_us,
													mode_wib->ms.soc.do_uwgent_watency_adjustment,
													mode_wib->ms.state.uwgent_watency_adjustment_fabwic_cwock_component_us,
													mode_wib->ms.state.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz,
													mode_wib->ms.state.fabwiccwk_mhz);

		/* Gettew functions wowk at mp intewface so copy the uwgent watency to mp*/
		mode_wib->mp.UwgentWatency = mode_wib->ms.UwgWatency;

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			CawcuwateUwgentBuwstFactow(
				mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k],
				mode_wib->ms.swath_width_wuma_ub_this_state[k],
				mode_wib->ms.swath_width_chwoma_ub_this_state[k],
				mode_wib->ms.SwathHeightYThisState[k],
				mode_wib->ms.SwathHeightCThisState[k],
				(dmw_fwoat_t) mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
				mode_wib->ms.UwgWatency,
				mode_wib->ms.ip.cuwsow_buffew_size,
				mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k],
				mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k],
				mode_wib->ms.BytePewPixewInDETY[k],
				mode_wib->ms.BytePewPixewInDETC[k],
				mode_wib->ms.DETBuffewSizeYThisState[k],
				mode_wib->ms.DETBuffewSizeCThisState[k],
				/* Output */
				&mode_wib->ms.UwgentBuwstFactowCuwsow[k],
				&mode_wib->ms.UwgentBuwstFactowWuma[k],
				&mode_wib->ms.UwgentBuwstFactowChwoma[k],
				&mode_wib->ms.NotUwgentWatencyHiding[k]);
		}

		CawcuwateDCFCWKDeepSweep(
				mode_wib->ms.num_active_pwanes,
				mode_wib->ms.BytePewPixewY,
				mode_wib->ms.BytePewPixewC,
				mode_wib->ms.cache_dispway_cfg.pwane.VWatio,
				mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma,
				mode_wib->ms.SwathWidthYThisState,
				mode_wib->ms.SwathWidthCThisState,
				mode_wib->ms.NoOfDPPThisState,
				mode_wib->ms.cache_dispway_cfg.pwane.HWatio,
				mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma,
				mode_wib->ms.cache_dispway_cfg.timing.PixewCwock,
				mode_wib->ms.PSCW_FACTOW,
				mode_wib->ms.PSCW_FACTOW_CHWOMA,
				mode_wib->ms.WequiwedDPPCWKThisState,
				mode_wib->ms.WeadBandwidthWuma,
				mode_wib->ms.WeadBandwidthChwoma,
				mode_wib->ms.soc.wetuwn_bus_width_bytes,

				/* Output */
				&mode_wib->ms.PwojectedDCFCWKDeepSweep[j]);
	}

	//Cawcuwate Wetuwn BW
	fow (j = 0; j < 2; ++j) {
		fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
			if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
				if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
					mode_wib->ms.WwitebackDewayTime[k] = mode_wib->ms.state.wwiteback_watency_us + CawcuwateWwiteBackDeway(
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[k],
									mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]) / mode_wib->ms.WequiwedDISPCWK[j];
				} ewse {
					mode_wib->ms.WwitebackDewayTime[k] = 0.0;
				}
				fow (m = 0; m <= mode_wib->ms.num_active_pwanes - 1; m++) {
					if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[m] == k && mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[m] == twue) {
						mode_wib->ms.WwitebackDewayTime[k] = dmw_max(mode_wib->ms.WwitebackDewayTime[k],
											mode_wib->ms.state.wwiteback_watency_us + CawcuwateWwiteBackDeway(
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[m],
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[m],
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[m],
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[m],
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[m],
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[m],
											mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[m],
											mode_wib->ms.cache_dispway_cfg.timing.HTotaw[m]) / mode_wib->ms.WequiwedDISPCWK[j]);
					}
				}
			}
		}
		fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
			fow (m = 0; m <= mode_wib->ms.num_active_pwanes - 1; m++) {
				if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == m) {
					mode_wib->ms.WwitebackDewayTime[k] = mode_wib->ms.WwitebackDewayTime[m];
				}
			}
		}
       s->MaxVStawtupAwwPwanes[j] = 0;  // max vstawtup among aww pwanes

		fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
			s->MaximumVStawtup[j][k] = CawcuwateMaxVStawtup(k,
														mode_wib->ms.ip.ptoi_suppowted,
														mode_wib->ms.ip.vbwank_nom_defauwt_us,
														&mode_wib->ms.cache_dispway_cfg.timing,
														mode_wib->ms.WwitebackDewayTime[k]);

			s->MaxVStawtupAwwPwanes[j] = (dmw_uint_t)(dmw_max(s->MaxVStawtupAwwPwanes[j], s->MaximumVStawtup[j][k]));
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%u, MaxVStawtupAwwPwanes[%u] = %u\n", __func__, k, j, s->MaxVStawtupAwwPwanes[j]);
			dmw_pwint("DMW::%s: k=%u, MaximumVStawtup[%u][%u] = %u\n", __func__, k, j, k, s->MaximumVStawtup[j][k]);
#endif
		}
	}

	s->WeowdewingBytes = (dmw_uint_t)(mode_wib->ms.soc.num_chans * dmw_max3(mode_wib->ms.soc.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes,
																mode_wib->ms.soc.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes,
																mode_wib->ms.soc.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes));

	fow (j = 0; j < 2; ++j) {
		mode_wib->ms.DCFCWKState[j] = mode_wib->ms.state.dcfcwk_mhz;
	}

	/* Immediate Fwip and MAWW pawametews */
	s->ImmediateFwipWequiwedFinaw = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->ImmediateFwipWequiwedFinaw = s->ImmediateFwipWequiwedFinaw || (mode_wib->ms.powicy.ImmediateFwipWequiwement[k] == dmw_immediate_fwip_wequiwed);
	}

	mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified = mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified ||
																							((mode_wib->ms.powicy.ImmediateFwipWequiwement[k] != dmw_immediate_fwip_wequiwed) &&
																							(mode_wib->ms.powicy.ImmediateFwipWequiwement[k] != dmw_immediate_fwip_not_wequiwed));
	}
	mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified = mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified && s->ImmediateFwipWequiwedFinaw;

	mode_wib->ms.suppowt.ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		mode_wib->ms.suppowt.ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe =
										mode_wib->ms.suppowt.ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe || ((mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe == twue || mode_wib->ms.powicy.ImmediateFwipWequiwement[k] != dmw_immediate_fwip_not_wequiwed) &&
										(mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_fuww_fwame || mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe));
	}

	mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPStateAndStaticScween = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPStateAndStaticScween = mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPStateAndStaticScween ||
																((mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween[k] == dmw_use_maww_static_scween_enabwe || mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween[k] == dmw_use_maww_static_scween_optimize) && (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe)) ||
																((mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween[k] == dmw_use_maww_static_scween_disabwe || mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween[k] == dmw_use_maww_static_scween_optimize) && (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_fuww_fwame));
	}

	s->FuwwFwameMAWWPStateMethod = fawse;
	s->SubViewpowtMAWWPStateMethod = fawse;
	s->PhantomPipeMAWWPStateMethod = fawse;
	s->SubViewpowtMAWWWefweshGweatewThan120Hz = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_fuww_fwame)
			s->FuwwFwameMAWWPStateMethod = twue;
		if (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_sub_viewpowt) {
			s->SubViewpowtMAWWPStateMethod = twue;
			if (mode_wib->ms.cache_dispway_cfg.timing.WefweshWate[k] > 120)
				s->SubViewpowtMAWWWefweshGweatewThan120Hz = twue;
		}
		if (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] == dmw_use_maww_pstate_change_phantom_pipe)
			s->PhantomPipeMAWWPStateMethod = twue;
	}
	mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPState = (s->SubViewpowtMAWWPStateMethod != s->PhantomPipeMAWWPStateMethod)
	|| (s->SubViewpowtMAWWPStateMethod && s->FuwwFwameMAWWPStateMethod) || s->SubViewpowtMAWWWefweshGweatewThan120Hz;

    if (mode_wib->ms.powicy.UseMinimumWequiwedDCFCWK == twue) {
		UseMinimumDCFCWK_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
		UseMinimumDCFCWK_pawams->DWWDispway = mode_wib->ms.cache_dispway_cfg.timing.DWWDispway;
		UseMinimumDCFCWK_pawams->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw = mode_wib->ms.powicy.SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
		UseMinimumDCFCWK_pawams->MaxIntewDCNTiweWepeatews = mode_wib->ms.ip.max_intew_dcn_tiwe_wepeatews;
		UseMinimumDCFCWK_pawams->MaxPwefetchMode = dmw_pwefetch_suppowt_stuttew;
		UseMinimumDCFCWK_pawams->DWAMCwockChangeWatencyFinaw = mode_wib->ms.state.dwam_cwock_change_watency_us;
		UseMinimumDCFCWK_pawams->FCWKChangeWatency = mode_wib->ms.state.fcwk_change_watency_us;
		UseMinimumDCFCWK_pawams->SWEntewPwusExitTime = mode_wib->ms.state.sw_entew_pwus_exit_time_us;
		UseMinimumDCFCWK_pawams->WetuwnBusWidth = mode_wib->ms.soc.wetuwn_bus_width_bytes;
		UseMinimumDCFCWK_pawams->WoundTwipPingWatencyCycwes = mode_wib->ms.soc.wound_twip_ping_watency_dcfcwk_cycwes;
		UseMinimumDCFCWK_pawams->WeowdewingBytes = s->WeowdewingBytes;
		UseMinimumDCFCWK_pawams->PixewChunkSizeInKByte = mode_wib->ms.ip.pixew_chunk_size_kbytes;
		UseMinimumDCFCWK_pawams->MetaChunkSize = mode_wib->ms.ip.meta_chunk_size_kbytes;
		UseMinimumDCFCWK_pawams->GPUVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe;
		UseMinimumDCFCWK_pawams->GPUVMMaxPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews;
		UseMinimumDCFCWK_pawams->HostVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe;
		UseMinimumDCFCWK_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
		UseMinimumDCFCWK_pawams->HostVMMinPageSize = mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024;
		UseMinimumDCFCWK_pawams->HostVMMaxNonCachedPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews;
		UseMinimumDCFCWK_pawams->DynamicMetadataVMEnabwed = mode_wib->ms.ip.dynamic_metadata_vm_enabwed;
		UseMinimumDCFCWK_pawams->ImmediateFwipWequiwement = s->ImmediateFwipWequiwedFinaw;
		UseMinimumDCFCWK_pawams->PwogwessiveToIntewwaceUnitInOPP = mode_wib->ms.ip.ptoi_suppowted;
		UseMinimumDCFCWK_pawams->MaxAvewagePewcentOfIdeawSDPPowtBWDispwayCanUseInNowmawSystemOpewation = mode_wib->ms.soc.max_avg_sdp_bw_use_nowmaw_pewcent;
		UseMinimumDCFCWK_pawams->PewcentOfIdeawSDPPowtBWWeceivedAftewUwgWatency = mode_wib->ms.soc.pct_ideaw_sdp_bw_aftew_uwgent;
		UseMinimumDCFCWK_pawams->VTotaw = mode_wib->ms.cache_dispway_cfg.timing.VTotaw;
		UseMinimumDCFCWK_pawams->VActive = mode_wib->ms.cache_dispway_cfg.timing.VActive;
		UseMinimumDCFCWK_pawams->DynamicMetadataTwansmittedBytes = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataTwansmittedBytes;
		UseMinimumDCFCWK_pawams->DynamicMetadataWinesBefoweActiveWequiwed = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataWinesBefoweActiveWequiwed;
		UseMinimumDCFCWK_pawams->Intewwace = mode_wib->ms.cache_dispway_cfg.timing.Intewwace;
		UseMinimumDCFCWK_pawams->WequiwedDPPCWKPewSuwface = mode_wib->ms.WequiwedDPPCWKPewSuwface;
		UseMinimumDCFCWK_pawams->WequiwedDISPCWK = mode_wib->ms.WequiwedDISPCWK;
		UseMinimumDCFCWK_pawams->UwgWatency = mode_wib->ms.UwgWatency;
		UseMinimumDCFCWK_pawams->NoOfDPP = mode_wib->ms.NoOfDPP;
		UseMinimumDCFCWK_pawams->PwojectedDCFCWKDeepSweep = mode_wib->ms.PwojectedDCFCWKDeepSweep;
		UseMinimumDCFCWK_pawams->MaximumVStawtup = s->MaximumVStawtup;
		UseMinimumDCFCWK_pawams->TotawNumbewOfActiveDPP = mode_wib->ms.TotawNumbewOfActiveDPP;
		UseMinimumDCFCWK_pawams->TotawNumbewOfDCCActiveDPP = mode_wib->ms.TotawNumbewOfDCCActiveDPP;
		UseMinimumDCFCWK_pawams->dpte_gwoup_bytes = mode_wib->ms.dpte_gwoup_bytes;
		UseMinimumDCFCWK_pawams->PwefetchWinesY = mode_wib->ms.PwefetchWinesY;
		UseMinimumDCFCWK_pawams->PwefetchWinesC = mode_wib->ms.PwefetchWinesC;
		UseMinimumDCFCWK_pawams->swath_width_wuma_ub_aww_states = mode_wib->ms.swath_width_wuma_ub_aww_states;
		UseMinimumDCFCWK_pawams->swath_width_chwoma_ub_aww_states = mode_wib->ms.swath_width_chwoma_ub_aww_states;
		UseMinimumDCFCWK_pawams->BytePewPixewY = mode_wib->ms.BytePewPixewY;
		UseMinimumDCFCWK_pawams->BytePewPixewC = mode_wib->ms.BytePewPixewC;
		UseMinimumDCFCWK_pawams->HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw;
		UseMinimumDCFCWK_pawams->PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock;
		UseMinimumDCFCWK_pawams->PDEAndMetaPTEBytesPewFwame = mode_wib->ms.PDEAndMetaPTEBytesPewFwame;
		UseMinimumDCFCWK_pawams->DPTEBytesPewWow = mode_wib->ms.DPTEBytesPewWow;
		UseMinimumDCFCWK_pawams->MetaWowBytes = mode_wib->ms.MetaWowBytes;
		UseMinimumDCFCWK_pawams->DynamicMetadataEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataEnabwe;
		UseMinimumDCFCWK_pawams->WeadBandwidthWuma = mode_wib->ms.WeadBandwidthWuma;
		UseMinimumDCFCWK_pawams->WeadBandwidthChwoma = mode_wib->ms.WeadBandwidthChwoma;
		UseMinimumDCFCWK_pawams->DCFCWKPewState = mode_wib->ms.state.dcfcwk_mhz;
		UseMinimumDCFCWK_pawams->DCFCWKState = mode_wib->ms.DCFCWKState;

		UseMinimumDCFCWK(&mode_wib->scwatch,
		UseMinimumDCFCWK_pawams);

	 } // UseMinimumWequiwedDCFCWK == twue

	fow (j = 0; j < 2; ++j) {
		mode_wib->ms.WetuwnBWPewState[j] = dmw_get_wetuwn_bw_mbps(&mode_wib->ms.soc, mode_wib->ms.state.use_ideaw_dwam_bw_stwobe,
																mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe, mode_wib->ms.DCFCWKState[j], mode_wib->ms.state.fabwiccwk_mhz,
																mode_wib->ms.state.dwam_speed_mts);
		mode_wib->ms.WetuwnDWAMBWPewState[j] = dmw_get_wetuwn_dwam_bw_mbps(&mode_wib->ms.soc, mode_wib->ms.state.use_ideaw_dwam_bw_stwobe,
																mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
																mode_wib->ms.state.dwam_speed_mts);
	}

	//We-owdewing Buffew Suppowt Check
	fow (j = 0; j < 2; ++j) {
		if ((mode_wib->ms.ip.wob_buffew_size_kbytes - mode_wib->ms.ip.pixew_chunk_size_kbytes) * 1024 / mode_wib->ms.WetuwnBWPewState[j] >
			(mode_wib->ms.soc.wound_twip_ping_watency_dcfcwk_cycwes + 32) / mode_wib->ms.DCFCWKState[j] + s->WeowdewingBytes / mode_wib->ms.WetuwnBWPewState[j]) {
			mode_wib->ms.suppowt.WOBSuppowt[j] = twue;
		} ewse {
			mode_wib->ms.suppowt.WOBSuppowt[j] = fawse;
		}
		dmw_pwint("DMW::%s: DEBUG WOBSuppowt[%u] = %u (%u)\n",  __func__, j, mode_wib->ms.suppowt.WOBSuppowt[j], __WINE__);
	}

	//Vewticaw Active BW suppowt check
	s->MaxTotawVActiveWDBandwidth = 0;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->MaxTotawVActiveWDBandwidth = s->MaxTotawVActiveWDBandwidth + mode_wib->ms.WeadBandwidthWuma[k] + mode_wib->ms.WeadBandwidthChwoma[k];
	}

	fow (j = 0; j < 2; ++j) {
		mode_wib->ms.suppowt.MaxTotawVewticawActiveAvaiwabweBandwidth[j] = dmw_min3(mode_wib->ms.soc.wetuwn_bus_width_bytes * mode_wib->ms.DCFCWKState[j] * mode_wib->ms.soc.max_avg_sdp_bw_use_nowmaw_pewcent / 100.0,
																	mode_wib->ms.state.fabwiccwk_mhz * mode_wib->ms.soc.fabwic_datapath_to_dcn_data_wetuwn_bytes * mode_wib->ms.soc.max_avg_fabwic_bw_use_nowmaw_pewcent / 100.0,
																	mode_wib->ms.state.dwam_speed_mts * mode_wib->ms.soc.num_chans * mode_wib->ms.soc.dwam_channew_width_bytes *
																	((mode_wib->ms.state.use_ideaw_dwam_bw_stwobe && !mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe) ?
																	mode_wib->ms.soc.max_avg_dwam_bw_use_nowmaw_stwobe_pewcent : mode_wib->ms.soc.max_avg_dwam_bw_use_nowmaw_pewcent) / 100.0);

		if (s->MaxTotawVActiveWDBandwidth <= mode_wib->ms.suppowt.MaxTotawVewticawActiveAvaiwabweBandwidth[j]) {
			mode_wib->ms.suppowt.TotawVewticawActiveBandwidthSuppowt[j] = twue;
		} ewse {
			mode_wib->ms.suppowt.TotawVewticawActiveBandwidthSuppowt[j] = fawse;
		}
	}

	/* Pwefetch Check */
	dmw_pwefetch_check(mode_wib);

	// End of Pwefetch Check
	dmw_pwint("DMW::%s: Done pwefetch cawcuwation\n", __func__);

	/*Cuwsow Suppowt Check*/
	mode_wib->ms.suppowt.CuwsowSuppowt = twue;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k] > 0.0) {
			if (mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k] == 64 && mode_wib->ms.ip.cuwsow_64bpp_suppowt == fawse) {
				mode_wib->ms.suppowt.CuwsowSuppowt = fawse;
			}
		}
	}

	/*Vawid Pitch Check*/
	mode_wib->ms.suppowt.PitchSuppowt = twue;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		mode_wib->ms.suppowt.AwignedYPitch[k] = dmw_ceiw(
				dmw_max(mode_wib->ms.cache_dispway_cfg.suwface.PitchY[k], mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY[k]),
				mode_wib->ms.MacwoTiweWidthY[k]);
		if (mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k] == twue) {
			mode_wib->ms.suppowt.AwignedDCCMetaPitchY[k] = dmw_ceiw(dmw_max(mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchY[k], mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY[k]), 64.0 * mode_wib->ms.Wead256BwockWidthY[k]);
		} ewse {
			mode_wib->ms.suppowt.AwignedDCCMetaPitchY[k] = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchY[k];
		}
		if (mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_64
			&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_32
			&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_16
			&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_mono_16
			&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe
			&& mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_mono_8) {
			mode_wib->ms.suppowt.AwignedCPitch[k] = dmw_ceiw(dmw_max(mode_wib->ms.cache_dispway_cfg.suwface.PitchC[k], mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC[k]), mode_wib->ms.MacwoTiweWidthC[k]);
			if (mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k] == twue) {
				mode_wib->ms.suppowt.AwignedDCCMetaPitchC[k] = dmw_ceiw(dmw_max(mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchC[k], mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC[k]), 64.0 * mode_wib->ms.Wead256BwockWidthC[k]);
			} ewse {
				mode_wib->ms.suppowt.AwignedDCCMetaPitchC[k] = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchC[k];
			}
		} ewse {
			mode_wib->ms.suppowt.AwignedCPitch[k] = mode_wib->ms.cache_dispway_cfg.suwface.PitchC[k];
			mode_wib->ms.suppowt.AwignedDCCMetaPitchC[k] = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchC[k];
		}
		if (mode_wib->ms.suppowt.AwignedYPitch[k] > mode_wib->ms.cache_dispway_cfg.suwface.PitchY[k] || mode_wib->ms.suppowt.AwignedCPitch[k] > mode_wib->ms.cache_dispway_cfg.suwface.PitchC[k] ||
			mode_wib->ms.suppowt.AwignedDCCMetaPitchY[k] > mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchY[k] || mode_wib->ms.suppowt.AwignedDCCMetaPitchC[k] > mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchC[k]) {
			mode_wib->ms.suppowt.PitchSuppowt = fawse;
		}
	}

	mode_wib->ms.suppowt.ViewpowtExceedsSuwface = fawse;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth[k] > mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY[k] || mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight[k] > mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY[k]) {
			mode_wib->ms.suppowt.ViewpowtExceedsSuwface = twue;
			if (mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_64 && mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_32 &&
				mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_16 && mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_444_8 && mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k] != dmw_wgbe) {
				if (mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidthChwoma[k] > mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC[k] || mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeightChwoma[k] > mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC[k]) {
					mode_wib->ms.suppowt.ViewpowtExceedsSuwface = twue;
				}
			}
		}
	}

	/*Mode Suppowt, Vowtage State and SOC Configuwation*/
	fow (j = 0; j < 2; j++) { // j itewatow is fow the combine mode off ow on
		dmw_pwint("DMW::%s: checking suppowt fow j=%u\n", __func__, j);
		dmw_pwint("DMW::%s: state_idx=%0d max_state_idx=%0d\n", __func__, mode_wib->ms.state_idx, mode_wib->ms.max_state_idx);

		s->is_max_pww_state = (mode_wib->ms.max_state_idx == mode_wib->ms.state_idx);
		s->is_max_dwam_pww_state = (mode_wib->ms.max_state.dwam_speed_mts == mode_wib->ms.state.dwam_speed_mts);

		s->dwam_cwock_change_suppowt = (!mode_wib->ms.powicy.DWAMCwockChangeWequiwementFinaw ||
											(s->is_max_dwam_pww_state && mode_wib->powicy.AssumeModeSuppowtAtMaxPwwStateEvenDWAMCwockChangeNotSuppowted) ||
											mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[j] != dmw_dwam_cwock_change_unsuppowted);
		s->f_cwock_change_suppowt = (!mode_wib->ms.powicy.FCWKChangeWequiwementFinaw ||
											(s->is_max_pww_state && mode_wib->powicy.AssumeModeSuppowtAtMaxPwwStateEvenFCwockChangeNotSuppowted) ||
											mode_wib->ms.suppowt.FCWKChangeSuppowt[j] != dmw_fcwock_change_unsuppowted);

		if (mode_wib->ms.suppowt.ScaweWatioAndTapsSuppowt == twue
			&& mode_wib->ms.suppowt.SouwceFowmatPixewAndScanSuppowt == twue
			&& mode_wib->ms.suppowt.ViewpowtSizeSuppowt[j] == twue
			&& !mode_wib->ms.suppowt.WinkWateDoesNotMatchDPVewsion
			&& !mode_wib->ms.suppowt.WinkWateFowMuwtistweamNotIndicated
			&& !mode_wib->ms.suppowt.BPPFowMuwtistweamNotIndicated
			&& !mode_wib->ms.suppowt.MuwtistweamWithHDMIOweDP
			&& !mode_wib->ms.suppowt.ExceededMuwtistweamSwots
			&& !mode_wib->ms.suppowt.MSOOwODMSpwitWithNonDPWink
			&& !mode_wib->ms.suppowt.NotEnoughWanesFowMSO
			&& mode_wib->ms.suppowt.WinkCapacitySuppowt == twue
			&& !mode_wib->ms.suppowt.P2IWith420
			&& !mode_wib->ms.suppowt.DSCOnwyIfNecessawyWithBPP
			&& !mode_wib->ms.suppowt.DSC422NativeNotSuppowted
			&& !mode_wib->ms.suppowt.MPCCombineMethodIncompatibwe
			&& mode_wib->ms.suppowt.ODMCombineTwoToOneSuppowtCheckOK == twue
			&& mode_wib->ms.suppowt.ODMCombineFouwToOneSuppowtCheckOK == twue
			&& mode_wib->ms.suppowt.NotEnoughDSCUnits == fawse
			&& !mode_wib->ms.suppowt.NotEnoughDSCSwices
			&& !mode_wib->ms.suppowt.ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe
			&& !mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPStateAndStaticScween
			&& mode_wib->ms.suppowt.DSCCWKWequiwedMoweThanSuppowted == fawse
			&& mode_wib->ms.suppowt.PixewsPewWinePewDSCUnitSuppowt
			&& mode_wib->ms.suppowt.DTBCWKWequiwedMoweThanSuppowted == fawse
			&& !mode_wib->ms.suppowt.InvawidCombinationOfMAWWUseFowPState
			&& !mode_wib->ms.suppowt.ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified
			&& mode_wib->ms.suppowt.WOBSuppowt[j] == twue
			&& mode_wib->ms.suppowt.DISPCWK_DPPCWK_Suppowt[j] == twue
			&& mode_wib->ms.suppowt.TotawAvaiwabwePipesSuppowt[j] == twue
			&& mode_wib->ms.suppowt.NumbewOfOTGSuppowt == twue
			&& mode_wib->ms.suppowt.NumbewOfHDMIFWWSuppowt == twue
			&& mode_wib->ms.suppowt.NumbewOfDP2p0Suppowt == twue
			&& mode_wib->ms.suppowt.EnoughWwitebackUnits == twue
			&& mode_wib->ms.suppowt.WwitebackWatencySuppowt == twue
			&& mode_wib->ms.suppowt.WwitebackScaweWatioAndTapsSuppowt == twue
			&& mode_wib->ms.suppowt.CuwsowSuppowt == twue
			&& mode_wib->ms.suppowt.PitchSuppowt == twue
			&& mode_wib->ms.suppowt.ViewpowtExceedsSuwface == fawse
			&& mode_wib->ms.suppowt.PwefetchSuppowted[j] == twue
			&& mode_wib->ms.suppowt.VActiveBandwithSuppowt[j] == twue
			&& mode_wib->ms.suppowt.DynamicMetadataSuppowted[j] == twue
			&& mode_wib->ms.suppowt.TotawVewticawActiveBandwidthSuppowt[j] == twue
			&& mode_wib->ms.suppowt.VWatioInPwefetchSuppowted[j] == twue
			&& mode_wib->ms.suppowt.PTEBuffewSizeNotExceeded[j] == twue
			&& mode_wib->ms.suppowt.DCCMetaBuffewSizeNotExceeded[j] == twue
			&& mode_wib->ms.suppowt.NonsuppowtedDSCInputBPC == fawse
			&& !mode_wib->ms.suppowt.ExceededMAWWSize
			&& ((mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe == fawse && !s->ImmediateFwipWequiwedFinaw) || mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[j])
			&& s->dwam_cwock_change_suppowt == twue
			&& s->f_cwock_change_suppowt == twue
			&& (!mode_wib->ms.powicy.USWWetwainingWequiwedFinaw || mode_wib->ms.suppowt.USWWetwainingSuppowt[j])) {
			dmw_pwint("DMW::%s: mode is suppowted\n", __func__);
			mode_wib->ms.suppowt.ModeSuppowt[j] = twue;
		} ewse {
			dmw_pwint("DMW::%s: mode is NOT suppowted\n", __func__);
			mode_wib->ms.suppowt.ModeSuppowt[j] = fawse;
			dmw_pwint_mode_suppowt(mode_wib, j);
		}
	}

	mode_wib->ms.suppowt.MaximumMPCCombine = 0;
	mode_wib->ms.suppowt.ModeIsSuppowted = 0;
	if (mode_wib->ms.suppowt.ModeSuppowt[0] == twue || mode_wib->ms.suppowt.ModeSuppowt[1] == twue) {  // if the mode is suppowted by eithew no combine ow mpccombine
		mode_wib->ms.suppowt.ModeIsSuppowted = mode_wib->ms.suppowt.ModeSuppowt[0] == twue || mode_wib->ms.suppowt.ModeSuppowt[1] == twue;

		// Detewmine if MPC combine is necessawy, depends on if using MPC combine wiww hewp dwam cwock change ow fcwk change, etc.
		if ((mode_wib->ms.suppowt.ModeSuppowt[0] == fawse && mode_wib->ms.suppowt.ModeSuppowt[1] == twue) || s->MPCCombineMethodAsPossibwe ||
			(s->MPCCombineMethodAsNeededFowPStateChangeAndVowtage && mode_wib->ms.powicy.DWAMCwockChangeWequiwementFinaw &&
			(((mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vactive || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vactive_w_maww_fuww_fwame || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vactive_w_maww_sub_vp) &&
			!(mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[0] == dmw_dwam_cwock_change_vactive || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[0] == dmw_dwam_cwock_change_vactive_w_maww_fuww_fwame || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[0] == dmw_dwam_cwock_change_vactive_w_maww_sub_vp)) ||
			((mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vbwank || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vbwank_dww
		|| mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vbwank_w_maww_fuww_fwame || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vbwank_dww_w_maww_fuww_fwame
		|| mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vbwank_w_maww_sub_vp || mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[1] == dmw_dwam_cwock_change_vbwank_dww_w_maww_sub_vp
		) &&
				mode_wib->ms.suppowt.DWAMCwockChangeSuppowt[0] == dmw_dwam_cwock_change_unsuppowted)))
			|| (s->MPCCombineMethodAsNeededFowPStateChangeAndVowtage && mode_wib->ms.powicy.FCWKChangeWequiwementFinaw &&
				((mode_wib->ms.suppowt.FCWKChangeSuppowt[1] == dmw_fcwock_change_vactive && mode_wib->ms.suppowt.FCWKChangeSuppowt[0] != dmw_fcwock_change_vactive) ||
				(mode_wib->ms.suppowt.FCWKChangeSuppowt[1] == dmw_fcwock_change_vbwank && mode_wib->ms.suppowt.FCWKChangeSuppowt[0] == dmw_fcwock_change_unsuppowted)))) {
			mode_wib->ms.suppowt.MaximumMPCCombine = 1;
		} ewse {
			mode_wib->ms.suppowt.MaximumMPCCombine = 0;
		}
	}

	// Since now the mode_suppowt wowk on 1 pawticuwaw powew state, so thewe is onwy 1 state idx (index 0).
	mode_wib->ms.suppowt.ImmediateFwipSuppowt          = mode_wib->ms.suppowt.ImmediateFwipSuppowtedFowState[mode_wib->ms.suppowt.MaximumMPCCombine];   // Considew fwip suppowt if max combine suppowt imm fwip
	mode_wib->ms.suppowt.UnboundedWequestEnabwed       = mode_wib->ms.UnboundedWequestEnabwedAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine];         // Not used, infowmationaw
	mode_wib->ms.suppowt.CompwessedBuffewSizeInkByte   = mode_wib->ms.CompwessedBuffewSizeInkByteAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine];     // Not used, infowmationaw

	dmw_pwint("DMW::%s: ModeIsSuppowted                = %u\n", __func__, mode_wib->ms.suppowt.ModeIsSuppowted);
	dmw_pwint("DMW::%s: MaximumMPCCombine              = %u\n", __func__, mode_wib->ms.suppowt.MaximumMPCCombine);
	dmw_pwint("DMW::%s: ImmediateFwipSuppowt           = %u\n", __func__, mode_wib->ms.suppowt.ImmediateFwipSuppowt);
	dmw_pwint("DMW::%s: UnboundedWequestEnabwed        = %u\n", __func__, mode_wib->ms.suppowt.UnboundedWequestEnabwed);
	dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte    = %u\n", __func__, mode_wib->ms.suppowt.CompwessedBuffewSizeInkByte);

	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		mode_wib->ms.suppowt.MPCCombineEnabwe[k]   = mode_wib->ms.MPCCombine[mode_wib->ms.suppowt.MaximumMPCCombine][k];
		mode_wib->ms.suppowt.DPPPewSuwface[k]      = mode_wib->ms.NoOfDPP[mode_wib->ms.suppowt.MaximumMPCCombine][k];
		mode_wib->ms.SwathHeightY[k]               = mode_wib->ms.SwathHeightYAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine][k];
		mode_wib->ms.SwathHeightC[k]               = mode_wib->ms.SwathHeightCAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine][k];
		mode_wib->ms.DETBuffewSizeInKByte[k]       = mode_wib->ms.DETBuffewSizeInKByteAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine][k];
		mode_wib->ms.DETBuffewSizeY[k]             = mode_wib->ms.DETBuffewSizeYAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine][k];
		mode_wib->ms.DETBuffewSizeC[k]             = mode_wib->ms.DETBuffewSizeCAwwStates[mode_wib->ms.suppowt.MaximumMPCCombine][k];
	}

	mode_wib->ms.DWAMSpeed     = mode_wib->ms.state.dwam_speed_mts;
	mode_wib->ms.FabwicCwock   = mode_wib->ms.state.fabwiccwk_mhz;
	mode_wib->ms.SOCCWK        = mode_wib->ms.state.soccwk_mhz;
	mode_wib->ms.DCFCWK        = mode_wib->ms.DCFCWKState[mode_wib->ms.suppowt.MaximumMPCCombine];
	mode_wib->ms.WetuwnBW      = mode_wib->ms.WetuwnBWPewState[mode_wib->ms.suppowt.MaximumMPCCombine];
	mode_wib->ms.WetuwnDWAMBW  = mode_wib->ms.WetuwnDWAMBWPewState[mode_wib->ms.suppowt.MaximumMPCCombine];

	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
			mode_wib->ms.suppowt.ODMMode[k] = mode_wib->ms.ODMModePewState[k];
		} ewse {
			mode_wib->ms.suppowt.ODMMode[k] = dmw_odm_mode_bypass;
		}

		mode_wib->ms.suppowt.DSCEnabwed[k] = mode_wib->ms.WequiwesDSC[k];
		mode_wib->ms.suppowt.FECEnabwed[k] = mode_wib->ms.WequiwesFEC[k];
		mode_wib->ms.suppowt.OutputBpp[k] = mode_wib->ms.OutputBppPewState[k];
		mode_wib->ms.suppowt.OutputType[k] = mode_wib->ms.OutputTypePewState[k];
		mode_wib->ms.suppowt.OutputWate[k] = mode_wib->ms.OutputWatePewState[k];
		mode_wib->ms.suppowt.SubViewpowtWinesNeededInMAWW[k] = mode_wib->ms.SubViewpowtWinesNeededInMAWW[k];
	}

	wetuwn mode_wib->ms.suppowt.ModeIsSuppowted;
} // dmw_cowe_mode_suppowt

/// @bwief This function cawcuwates some pawametews thats awe needed ahead of the mode pwogwamming function aww
void dmw_cowe_mode_suppowt_pawtiaw(stwuct dispway_mode_wib_st *mode_wib)
{
	CawcuwateMaxDETAndMinCompwessedBuffewSize(
								mode_wib->ms.ip.config_wetuwn_buffew_size_in_kbytes,
								mode_wib->ms.ip.config_wetuwn_buffew_segment_size_in_kbytes,
								mode_wib->ms.ip.wob_buffew_size_kbytes,
								mode_wib->ms.ip.max_num_dpp,
								mode_wib->ms.powicy.NomDETInKByteOvewwideEnabwe,
								mode_wib->ms.powicy.NomDETInKByteOvewwideVawue,

								/* Output */
								&mode_wib->ms.MaxTotawDETInKByte,
								&mode_wib->ms.NomDETInKByte,
								&mode_wib->ms.MinCompwessedBuffewSizeInKByte);

	PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(&mode_wib->ms.cache_dispway_cfg, mode_wib->ms.ip.ptoi_suppowted);

	mode_wib->ms.WetuwnBW = dmw_get_wetuwn_bw_mbps(&mode_wib->ms.soc,
													mode_wib->ms.state.use_ideaw_dwam_bw_stwobe,
													mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
													mode_wib->ms.DCFCWK,
													mode_wib->ms.FabwicCwock,
													mode_wib->ms.DWAMSpeed);
	dmw_pwint("DMW::%s: WetuwnBW = %f\n", __func__, mode_wib->ms.WetuwnBW);

} // dmw_cowe_mode_suppowt_pawtiaw

/// @bwief This is the mode pwogwamming function. It is assumed the dispway cfg is suppowt at the given powew state
void dmw_cowe_mode_pwogwamming(stwuct dispway_mode_wib_st *mode_wib, const stwuct dmw_cwk_cfg_st *cwk_cfg)
{
	stwuct dmw_cowe_mode_pwogwamming_wocaws_st *s = &mode_wib->scwatch.dmw_cowe_mode_pwogwamming_wocaws;
	stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams_st *CawcuwateWatewmawks_pawams = &mode_wib->scwatch.CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams;
	stwuct CawcuwateVMWowAndSwath_pawams_st *CawcuwateVMWowAndSwath_pawams = &mode_wib->scwatch.CawcuwateVMWowAndSwath_pawams;
	stwuct CawcuwateSwathAndDETConfiguwation_pawams_st *CawcuwateSwathAndDETConfiguwation_pawams = &mode_wib->scwatch.CawcuwateSwathAndDETConfiguwation_pawams;
	stwuct CawcuwateStuttewEfficiency_pawams_st *CawcuwateStuttewEfficiency_pawams = &mode_wib->scwatch.CawcuwateStuttewEfficiency_pawams;
	stwuct CawcuwatePwefetchScheduwe_pawams_st *CawcuwatePwefetchScheduwe_pawams = &mode_wib->scwatch.CawcuwatePwefetchScheduwe_pawams;

	stwuct mode_pwogwam_st   *wocaws    = &mode_wib->mp;
	stwuct DmwPipe *myPipe;
	dmw_uint_t j = 0, k = 0;
	dmw_fwoat_t TWait;
	dmw_boow_t isIntewwaceTiming;

	mode_wib->ms.num_active_pwanes = dmw_get_num_active_pwanes(&mode_wib->ms.cache_dispway_cfg);
	mode_wib->mp.num_active_pipes = dmw_get_num_active_pipes(&mode_wib->ms.cache_dispway_cfg);
	dmw_cawc_pipe_pwane_mapping(&mode_wib->ms.cache_dispway_cfg.hw, mode_wib->mp.pipe_pwane);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: --- STAWT --- \n",  __func__);
	dmw_pwint("DMW::%s: num_active_pwanes = %u\n", __func__, mode_wib->ms.num_active_pwanes);
	dmw_pwint("DMW::%s: num_active_pipes = %u\n", __func__, mode_wib->mp.num_active_pipes);
#endif

	s->DSCFowmatFactow          = 0;

	// Unwike dppcwk and dispcwk which can be cawcuwated in mode_pwogwamming
	// DCFCWK is cawcuwated in mode_suppowt (which is the state bbox dcfcwk ow min dcfcwk if min dcfcwk option is used in mode suppowt cawcuwation)
	if (cwk_cfg->dcfcwk_option != dmw_use_ovewwide_fweq)
		wocaws->Dcfcwk = mode_wib->ms.DCFCWK;
	ewse
		wocaws->Dcfcwk = cwk_cfg->dcfcwk_fweq_mhz;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint_dmw_powicy(&mode_wib->ms.powicy);
	dmw_pwint_soc_state_bounding_box(&mode_wib->ms.state);
	dmw_pwint_soc_bounding_box(&mode_wib->ms.soc);
	dmw_pwint_cwk_cfg(cwk_cfg);

	dmw_pwint("DMW::%s: ImmediateFwipSuppowt = %u\n", __func__, mode_wib->ms.suppowt.ImmediateFwipSuppowt);
	dmw_pwint("DMW::%s: Using DCFCWK = %f\n", __func__, wocaws->Dcfcwk);
	dmw_pwint("DMW::%s: Using SOCCWK = %f\n", __func__, mode_wib->ms.SOCCWK);
#endif

	wocaws->WwitebackDISPCWK = 0.0;
	wocaws->GwobawDPPCWK = 0.0;

	// DISPCWK and DPPCWK Cawcuwation
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k]) {
			wocaws->WwitebackDISPCWK =
					dmw_max(
							wocaws->WwitebackDISPCWK,
							CawcuwateWwiteBackDISPCWK(
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[k],
									mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHTaps[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceWidth[k],
									mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k],
									mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k],
									mode_wib->ms.ip.wwiteback_wine_buffew_buffew_size,
									mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz));
		}
	}

	wocaws->Dispcwk_cawcuwated = wocaws->WwitebackDISPCWK;

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
				wocaws->Dispcwk_cawcuwated = dmw_max(wocaws->Dispcwk_cawcuwated, CawcuwateWequiwedDispcwk(
																					mode_wib->ms.cache_dispway_cfg.hw.ODMMode[k],
																					mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
																					mode_wib->ms.soc.dcn_downspwead_pewcent,
																					mode_wib->ms.ip.dispcwk_wamp_mawgin_pewcent,
																					mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz,
																					mode_wib->ms.max_state.dispcwk_mhz));
		}
	}
	if (cwk_cfg->dispcwk_option == dmw_use_wequiwed_fweq)
		wocaws->Dispcwk = wocaws->Dispcwk_cawcuwated;
	ewse if (cwk_cfg->dispcwk_option == dmw_use_ovewwide_fweq)
		wocaws->Dispcwk = cwk_cfg->dispcwk_fweq_mhz;
	ewse
		wocaws->Dispcwk = mode_wib->ms.state.dispcwk_mhz;
#ifdef __DMW_VBA_DEBUG__
	 dmw_pwint("DMW::%s: Using Dispcwk = %f\n", __func__, wocaws->Dispcwk);
#endif

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		CawcuwateSingwePipeDPPCWKAndSCWThwoughput(
				mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k],
				mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k],
				mode_wib->ms.ip.max_dchub_pscw_bw_pix_pew_cwk,
				mode_wib->ms.ip.max_pscw_wb_bw_pix_pew_cwk,
				mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
				mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
				mode_wib->ms.cache_dispway_cfg.pwane.HTaps[k],
				mode_wib->ms.cache_dispway_cfg.pwane.HTapsChwoma[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k],
				mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k],

				/* Output */
				&wocaws->PSCW_THWOUGHPUT[k],
				&wocaws->PSCW_THWOUGHPUT_CHWOMA[k],
				&wocaws->DPPCWKUsingSingweDPP[k]);
	}

	CawcuwateDPPCWK(mode_wib->ms.num_active_pwanes,
					mode_wib->ms.soc.dcn_downspwead_pewcent,
					mode_wib->ms.soc.dispcwk_dppcwk_vco_speed_mhz,
					wocaws->DPPCWKUsingSingweDPP,
					mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
					/* Output */
					&wocaws->GwobawDPPCWK,
					wocaws->Dppcwk_cawcuwated);

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (cwk_cfg->dppcwk_option[k] == dmw_use_wequiwed_fweq)
			wocaws->Dppcwk[k] = wocaws->Dppcwk_cawcuwated[k];
		ewse if (cwk_cfg->dppcwk_option[k] == dmw_use_ovewwide_fweq)
			wocaws->Dppcwk[k] = cwk_cfg->dppcwk_fweq_mhz[k];
		ewse
			wocaws->Dppcwk[k] = mode_wib->ms.state.dppcwk_mhz;
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: Using Dppcwk[%0d] = %f\n", __func__, k, wocaws->Dppcwk[k]);
#endif
	}

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		CawcuwateBytePewPixewAndBwockSizes(
				mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
				mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k],

				/* Output */
				&wocaws->BytePewPixewY[k],
				&wocaws->BytePewPixewC[k],
				&wocaws->BytePewPixewDETY[k],
				&wocaws->BytePewPixewDETC[k],
				&wocaws->BwockHeight256BytesY[k],
				&wocaws->BwockHeight256BytesC[k],
				&wocaws->BwockWidth256BytesY[k],
				&wocaws->BwockWidth256BytesC[k],
				&wocaws->BwockHeightY[k],
				&wocaws->BwockHeightC[k],
				&wocaws->BwockWidthY[k],
				&wocaws->BwockWidthC[k]);
	}


	dmw_pwint("DMW::%s: %u\n", __func__, __WINE__);
	CawcuwateSwathWidth(
		fawse,  // FowceSingweDPP
		mode_wib->ms.num_active_pwanes,
		mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat,
		mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC,
		mode_wib->ms.cache_dispway_cfg.hw.ODMMode,
		wocaws->BytePewPixewY,
		wocaws->BytePewPixewC,
		wocaws->BwockHeight256BytesY,
		wocaws->BwockHeight256BytesC,
		wocaws->BwockWidth256BytesY,
		wocaws->BwockWidth256BytesC,
		mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming,
		mode_wib->ms.cache_dispway_cfg.timing.HActive,
		mode_wib->ms.cache_dispway_cfg.pwane.HWatio,
		mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,

		/* Output */
		wocaws->SwathWidthSingweDPPY,
		wocaws->SwathWidthSingweDPPC,
		wocaws->SwathWidthY,
		wocaws->SwathWidthC,
		s->dummy_integew_awway[0], // dmw_uint_t MaximumSwathHeightY[]
		s->dummy_integew_awway[1], // dmw_uint_t MaximumSwathHeightC[]
		wocaws->swath_width_wuma_ub,
		wocaws->swath_width_chwoma_ub);

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		wocaws->WeadBandwidthSuwfaceWuma[k] = wocaws->SwathWidthSingweDPPY[k] * wocaws->BytePewPixewY[k] / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k];
		wocaws->WeadBandwidthSuwfaceChwoma[k] = wocaws->SwathWidthSingweDPPC[k] * wocaws->BytePewPixewC[k] / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k];
		dmw_pwint("DMW::%s: WeadBandwidthSuwfaceWuma[%i] = %fBps\n", __func__, k, wocaws->WeadBandwidthSuwfaceWuma[k]);
		dmw_pwint("DMW::%s: WeadBandwidthSuwfaceChwoma[%i] = %fBps\n", __func__, k, wocaws->WeadBandwidthSuwfaceChwoma[k]);
	}

	CawcuwateSwathAndDETConfiguwation_pawams->DETSizeOvewwide = mode_wib->ms.cache_dispway_cfg.pwane.DETSizeOvewwide;
	CawcuwateSwathAndDETConfiguwation_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
	CawcuwateSwathAndDETConfiguwation_pawams->ConfigWetuwnBuffewSizeInKByte = mode_wib->ms.ip.config_wetuwn_buffew_size_in_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->WOBBuffewSizeInKByte = mode_wib->ms.ip.wob_buffew_size_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->MaxTotawDETInKByte = mode_wib->ms.MaxTotawDETInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->MinCompwessedBuffewSizeInKByte = mode_wib->ms.MinCompwessedBuffewSizeInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->PixewChunkSizeInKByte = mode_wib->ms.ip.pixew_chunk_size_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->FowceSingweDPP = fawse;
	CawcuwateSwathAndDETConfiguwation_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
	CawcuwateSwathAndDETConfiguwation_pawams->nomDETInKByte = mode_wib->ms.NomDETInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->UseUnboundedWequestingFinaw = mode_wib->ms.powicy.UseUnboundedWequesting;
	CawcuwateSwathAndDETConfiguwation_pawams->ConfigWetuwnBuffewSegmentSizeInkByte = mode_wib->ms.ip.config_wetuwn_buffew_segment_size_in_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->CompwessedBuffewSegmentSizeInkByteFinaw = mode_wib->ms.ip.compwessed_buffew_segment_size_in_kbytes;
	CawcuwateSwathAndDETConfiguwation_pawams->Output = s->dummy_output_encodew_awway;
	CawcuwateSwathAndDETConfiguwation_pawams->WeadBandwidthWuma = wocaws->WeadBandwidthSuwfaceWuma;
	CawcuwateSwathAndDETConfiguwation_pawams->WeadBandwidthChwoma = wocaws->WeadBandwidthSuwfaceChwoma;
	CawcuwateSwathAndDETConfiguwation_pawams->MaximumSwathWidthWuma = s->dummy_singwe_awway[0];
	CawcuwateSwathAndDETConfiguwation_pawams->MaximumSwathWidthChwoma = s->dummy_singwe_awway[1];
	CawcuwateSwathAndDETConfiguwation_pawams->SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtStationawy = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy;
	CawcuwateSwathAndDETConfiguwation_pawams->SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceTiwing = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtWidth = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtHeight = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtXStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtYStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtXStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtYStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceWidthY = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceWidthC = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceHeightY = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY;
	CawcuwateSwathAndDETConfiguwation_pawams->SuwfaceHeightC = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockHeightY = wocaws->BwockHeight256BytesY;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockHeightC = wocaws->BwockHeight256BytesC;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockWidthY = wocaws->BwockWidth256BytesY;
	CawcuwateSwathAndDETConfiguwation_pawams->Wead256BytesBwockWidthC = wocaws->BwockWidth256BytesC;
	CawcuwateSwathAndDETConfiguwation_pawams->ODMMode = mode_wib->ms.cache_dispway_cfg.hw.ODMMode;
	CawcuwateSwathAndDETConfiguwation_pawams->BwendingAndTiming = mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixY = wocaws->BytePewPixewY;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixC = wocaws->BytePewPixewC;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixDETY = wocaws->BytePewPixewDETY;
	CawcuwateSwathAndDETConfiguwation_pawams->BytePewPixDETC = wocaws->BytePewPixewDETC;
	CawcuwateSwathAndDETConfiguwation_pawams->HActive = mode_wib->ms.cache_dispway_cfg.timing.HActive;
	CawcuwateSwathAndDETConfiguwation_pawams->HWatio = mode_wib->ms.cache_dispway_cfg.pwane.HWatio;
	CawcuwateSwathAndDETConfiguwation_pawams->HWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma;
	CawcuwateSwathAndDETConfiguwation_pawams->DPPPewSuwface = mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface;
	CawcuwateSwathAndDETConfiguwation_pawams->swath_width_wuma_ub = s->dummy_wong_awway[0];
	CawcuwateSwathAndDETConfiguwation_pawams->swath_width_chwoma_ub = s->dummy_wong_awway[1];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathWidth = s->dummy_wong_awway[2];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathWidthChwoma = s->dummy_wong_awway[3];
	CawcuwateSwathAndDETConfiguwation_pawams->SwathHeightY = wocaws->SwathHeightY;
	CawcuwateSwathAndDETConfiguwation_pawams->SwathHeightC = wocaws->SwathHeightC;
	CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeInKByte = wocaws->DETBuffewSizeInKByte;
	CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeY = wocaws->DETBuffewSizeY;
	CawcuwateSwathAndDETConfiguwation_pawams->DETBuffewSizeC = wocaws->DETBuffewSizeC;
	CawcuwateSwathAndDETConfiguwation_pawams->UnboundedWequestEnabwed = &wocaws->UnboundedWequestEnabwed;
	CawcuwateSwathAndDETConfiguwation_pawams->compbuf_wesewved_space_64b = &wocaws->compbuf_wesewved_space_64b;
	CawcuwateSwathAndDETConfiguwation_pawams->compbuf_wesewved_space_zs = &wocaws->compbuf_wesewved_space_zs;
	CawcuwateSwathAndDETConfiguwation_pawams->CompwessedBuffewSizeInkByte = &wocaws->CompwessedBuffewSizeInkByte;
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtSizeSuppowtPewSuwface = &s->dummy_boowean_awway[0][0];
	CawcuwateSwathAndDETConfiguwation_pawams->ViewpowtSizeSuppowt = &s->dummy_boowean[0];

	// VBA_DEWTA
	// Cawcuwate DET size, swath height hewe. In VBA, they awe cawcuwated in mode check stage
	CawcuwateSwathAndDETConfiguwation(&mode_wib->scwatch,
		CawcuwateSwathAndDETConfiguwation_pawams);

	// DCFCWK Deep Sweep
	CawcuwateDCFCWKDeepSweep(
			mode_wib->ms.num_active_pwanes,
			wocaws->BytePewPixewY,
			wocaws->BytePewPixewC,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatio,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma,
			wocaws->SwathWidthY,
			wocaws->SwathWidthC,
			mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
			mode_wib->ms.cache_dispway_cfg.pwane.HWatio,
			mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma,
			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock,
			wocaws->PSCW_THWOUGHPUT,
			wocaws->PSCW_THWOUGHPUT_CHWOMA,
			wocaws->Dppcwk,
			wocaws->WeadBandwidthSuwfaceWuma,
			wocaws->WeadBandwidthSuwfaceChwoma,
			mode_wib->ms.soc.wetuwn_bus_width_bytes,

			/* Output */
			&wocaws->DCFCWKDeepSweep);

	// DSCCWK
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if ((mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] != k) || !mode_wib->ms.cache_dispway_cfg.hw.DSCEnabwed[k]) {
			wocaws->DSCCWK_cawcuwated[k] = 0.0;
		} ewse {
			if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_420)
				s->DSCFowmatFactow = 2;
			ewse if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_444)
				s->DSCFowmatFactow = 1;
			ewse if (mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k] == dmw_n422 || mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k] == dmw_hdmifww)
				s->DSCFowmatFactow = 2;
			ewse
				s->DSCFowmatFactow = 1;
			if (mode_wib->ms.cache_dispway_cfg.hw.ODMMode[k] == dmw_odm_mode_combine_4to1)
				wocaws->DSCCWK_cawcuwated[k] = mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 12 / s->DSCFowmatFactow / (1 - mode_wib->ms.soc.dcn_downspwead_pewcent / 100);
			ewse if (mode_wib->ms.cache_dispway_cfg.hw.ODMMode[k] == dmw_odm_mode_combine_2to1)
				wocaws->DSCCWK_cawcuwated[k] = mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 6 / s->DSCFowmatFactow / (1 - mode_wib->ms.soc.dcn_downspwead_pewcent / 100);
			ewse
				wocaws->DSCCWK_cawcuwated[k] = mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k] / 3 / s->DSCFowmatFactow / (1 - mode_wib->ms.soc.dcn_downspwead_pewcent / 100);
		}
	}

	// DSC Deway
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		wocaws->DSCDeway[k] = DSCDewayWequiwement(mode_wib->ms.cache_dispway_cfg.hw.DSCEnabwed[k],
												mode_wib->ms.cache_dispway_cfg.hw.ODMMode[k],
												mode_wib->ms.cache_dispway_cfg.output.DSCInputBitPewComponent[k],
												mode_wib->ms.cache_dispway_cfg.output.OutputBpp[k],
												mode_wib->ms.cache_dispway_cfg.timing.HActive[k],
												mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k],
												mode_wib->ms.cache_dispway_cfg.hw.NumbewOfDSCSwices[k],
												mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k],
												mode_wib->ms.cache_dispway_cfg.output.OutputEncodew[k],
												mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
												mode_wib->ms.cache_dispway_cfg.output.PixewCwockBackEnd[k]);
	}

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k)
		fow (j = 0; j < mode_wib->ms.num_active_pwanes; ++j) // NumbewOfSuwfaces
			if (j != k && mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == j && mode_wib->ms.cache_dispway_cfg.hw.DSCEnabwed[j])
				wocaws->DSCDeway[k] = wocaws->DSCDeway[j];

	// Pwefetch
	CawcuwateSuwfaceSizeInMaww(
		mode_wib->ms.num_active_pwanes,
		mode_wib->ms.soc.maww_awwocated_fow_dcn_mbytes,
		mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween,
		mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidth,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight,
		wocaws->BytePewPixewY,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtWidthChwoma,
		mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeightChwoma,
		wocaws->BytePewPixewC,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY,
		mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC,
		wocaws->BwockWidth256BytesY,
		wocaws->BwockWidth256BytesC,
		wocaws->BwockHeight256BytesY,
		wocaws->BwockHeight256BytesC,
		wocaws->BwockWidthY,
		wocaws->BwockWidthC,
		wocaws->BwockHeightY,
		wocaws->BwockHeightC,

		/* Output */
		wocaws->SuwfaceSizeInTheMAWW,
		&s->dummy_boowean[0]); /* dmw_boow_t *ExceededMAWWSize */

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->SuwfacePawametews[k].PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k];
		s->SuwfacePawametews[k].DPPPewSuwface = mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k];
		s->SuwfacePawametews[k].SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k];
		s->SuwfacePawametews[k].ViewpowtHeight = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeight[k];
		s->SuwfacePawametews[k].ViewpowtHeightChwoma = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtHeightChwoma[k];
		s->SuwfacePawametews[k].BwockWidth256BytesY = wocaws->BwockWidth256BytesY[k];
		s->SuwfacePawametews[k].BwockHeight256BytesY = wocaws->BwockHeight256BytesY[k];
		s->SuwfacePawametews[k].BwockWidth256BytesC = wocaws->BwockWidth256BytesC[k];
		s->SuwfacePawametews[k].BwockHeight256BytesC = wocaws->BwockHeight256BytesC[k];
		s->SuwfacePawametews[k].BwockWidthY = wocaws->BwockWidthY[k];
		s->SuwfacePawametews[k].BwockHeightY = wocaws->BwockHeightY[k];
		s->SuwfacePawametews[k].BwockWidthC = wocaws->BwockWidthC[k];
		s->SuwfacePawametews[k].BwockHeightC = wocaws->BwockHeightC[k];
		s->SuwfacePawametews[k].IntewwaceEnabwe = mode_wib->ms.cache_dispway_cfg.timing.Intewwace[k];
		s->SuwfacePawametews[k].HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k];
		s->SuwfacePawametews[k].DCCEnabwe = mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k];
		s->SuwfacePawametews[k].SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k];
		s->SuwfacePawametews[k].SuwfaceTiwing = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k];
		s->SuwfacePawametews[k].BytePewPixewY = wocaws->BytePewPixewY[k];
		s->SuwfacePawametews[k].BytePewPixewC = wocaws->BytePewPixewC[k];
		s->SuwfacePawametews[k].PwogwessiveToIntewwaceUnitInOPP = mode_wib->ms.ip.ptoi_suppowted;
		s->SuwfacePawametews[k].VWatio = mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k];
		s->SuwfacePawametews[k].VWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k];
		s->SuwfacePawametews[k].VTaps = mode_wib->ms.cache_dispway_cfg.pwane.VTaps[k];
		s->SuwfacePawametews[k].VTapsChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma[k];
		s->SuwfacePawametews[k].PitchY = mode_wib->ms.cache_dispway_cfg.suwface.PitchY[k];
		s->SuwfacePawametews[k].DCCMetaPitchY = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchY[k];
		s->SuwfacePawametews[k].PitchC = mode_wib->ms.cache_dispway_cfg.suwface.PitchC[k];
		s->SuwfacePawametews[k].DCCMetaPitchC = mode_wib->ms.cache_dispway_cfg.suwface.DCCMetaPitchC[k];
		s->SuwfacePawametews[k].ViewpowtStationawy = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtStationawy[k];
		s->SuwfacePawametews[k].ViewpowtXStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawt[k];
		s->SuwfacePawametews[k].ViewpowtYStawt = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawt[k];
		s->SuwfacePawametews[k].ViewpowtXStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtXStawtC[k];
		s->SuwfacePawametews[k].ViewpowtYStawtC = mode_wib->ms.cache_dispway_cfg.pwane.ViewpowtYStawtC[k];
		s->SuwfacePawametews[k].FOWCE_ONE_WOW_FOW_FWAME = mode_wib->ms.cache_dispway_cfg.pwane.FowceOneWowFowFwame[k];
		s->SuwfacePawametews[k].SwathHeightY = wocaws->SwathHeightY[k];
		s->SuwfacePawametews[k].SwathHeightC = wocaws->SwathHeightC[k];
	}

	CawcuwateVMWowAndSwath_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
	CawcuwateVMWowAndSwath_pawams->myPipe = s->SuwfacePawametews;
	CawcuwateVMWowAndSwath_pawams->SuwfaceSizeInMAWW = wocaws->SuwfaceSizeInTheMAWW;
	CawcuwateVMWowAndSwath_pawams->PTEBuffewSizeInWequestsWuma = mode_wib->ms.ip.dpte_buffew_size_in_pte_weqs_wuma;
	CawcuwateVMWowAndSwath_pawams->PTEBuffewSizeInWequestsChwoma = mode_wib->ms.ip.dpte_buffew_size_in_pte_weqs_chwoma;
	CawcuwateVMWowAndSwath_pawams->DCCMetaBuffewSizeBytes = mode_wib->ms.ip.dcc_meta_buffew_size_bytes;
	CawcuwateVMWowAndSwath_pawams->UseMAWWFowStaticScween = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowStaticScween;
	CawcuwateVMWowAndSwath_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
	CawcuwateVMWowAndSwath_pawams->MAWWAwwocatedFowDCN = mode_wib->ms.soc.maww_awwocated_fow_dcn_mbytes;
	CawcuwateVMWowAndSwath_pawams->SwathWidthY = wocaws->SwathWidthY;
	CawcuwateVMWowAndSwath_pawams->SwathWidthC = wocaws->SwathWidthC;
	CawcuwateVMWowAndSwath_pawams->GPUVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe;
	CawcuwateVMWowAndSwath_pawams->HostVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe;
	CawcuwateVMWowAndSwath_pawams->HostVMMaxNonCachedPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews;
	CawcuwateVMWowAndSwath_pawams->GPUVMMaxPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews;
	CawcuwateVMWowAndSwath_pawams->GPUVMMinPageSizeKBytes = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMinPageSizeKBytes;
	CawcuwateVMWowAndSwath_pawams->HostVMMinPageSize = mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024;
	CawcuwateVMWowAndSwath_pawams->PTEBuffewModeOvewwideEn = mode_wib->ms.cache_dispway_cfg.pwane.PTEBuffewModeOvewwideEn;
	CawcuwateVMWowAndSwath_pawams->PTEBuffewModeOvewwideVaw = mode_wib->ms.cache_dispway_cfg.pwane.PTEBuffewMode;
	CawcuwateVMWowAndSwath_pawams->PTEBuffewSizeNotExceeded = s->dummy_boowean_awway[0];
	CawcuwateVMWowAndSwath_pawams->DCCMetaBuffewSizeNotExceeded = s->dummy_boowean_awway[1];
	CawcuwateVMWowAndSwath_pawams->dpte_wow_width_wuma_ub = wocaws->dpte_wow_width_wuma_ub;
	CawcuwateVMWowAndSwath_pawams->dpte_wow_width_chwoma_ub = wocaws->dpte_wow_width_chwoma_ub;
	CawcuwateVMWowAndSwath_pawams->dpte_wow_height_wuma = wocaws->dpte_wow_height;
	CawcuwateVMWowAndSwath_pawams->dpte_wow_height_chwoma = wocaws->dpte_wow_height_chwoma;
	CawcuwateVMWowAndSwath_pawams->dpte_wow_height_wineaw_wuma = wocaws->dpte_wow_height_wineaw;
	CawcuwateVMWowAndSwath_pawams->dpte_wow_height_wineaw_chwoma = wocaws->dpte_wow_height_wineaw_chwoma;
	CawcuwateVMWowAndSwath_pawams->meta_weq_width = wocaws->meta_weq_width;
	CawcuwateVMWowAndSwath_pawams->meta_weq_width_chwoma = wocaws->meta_weq_width_chwoma;
	CawcuwateVMWowAndSwath_pawams->meta_weq_height = wocaws->meta_weq_height;
	CawcuwateVMWowAndSwath_pawams->meta_weq_height_chwoma = wocaws->meta_weq_height_chwoma;
	CawcuwateVMWowAndSwath_pawams->meta_wow_width = wocaws->meta_wow_width;
	CawcuwateVMWowAndSwath_pawams->meta_wow_width_chwoma = wocaws->meta_wow_width_chwoma;
	CawcuwateVMWowAndSwath_pawams->meta_wow_height = wocaws->meta_wow_height;
	CawcuwateVMWowAndSwath_pawams->meta_wow_height_chwoma = wocaws->meta_wow_height_chwoma;
	CawcuwateVMWowAndSwath_pawams->vm_gwoup_bytes = wocaws->vm_gwoup_bytes;
	CawcuwateVMWowAndSwath_pawams->dpte_gwoup_bytes = wocaws->dpte_gwoup_bytes;
	CawcuwateVMWowAndSwath_pawams->PixewPTEWeqWidthY = wocaws->PixewPTEWeqWidthY;
	CawcuwateVMWowAndSwath_pawams->PixewPTEWeqHeightY = wocaws->PixewPTEWeqHeightY;
	CawcuwateVMWowAndSwath_pawams->PTEWequestSizeY = wocaws->PTEWequestSizeY;
	CawcuwateVMWowAndSwath_pawams->PixewPTEWeqWidthC = wocaws->PixewPTEWeqWidthC;
	CawcuwateVMWowAndSwath_pawams->PixewPTEWeqHeightC = wocaws->PixewPTEWeqHeightC;
	CawcuwateVMWowAndSwath_pawams->PTEWequestSizeC = wocaws->PTEWequestSizeC;
	CawcuwateVMWowAndSwath_pawams->dpde0_bytes_pew_fwame_ub_w = wocaws->dpde0_bytes_pew_fwame_ub_w;
	CawcuwateVMWowAndSwath_pawams->meta_pte_bytes_pew_fwame_ub_w = wocaws->meta_pte_bytes_pew_fwame_ub_w;
	CawcuwateVMWowAndSwath_pawams->dpde0_bytes_pew_fwame_ub_c = wocaws->dpde0_bytes_pew_fwame_ub_c;
	CawcuwateVMWowAndSwath_pawams->meta_pte_bytes_pew_fwame_ub_c = wocaws->meta_pte_bytes_pew_fwame_ub_c;
	CawcuwateVMWowAndSwath_pawams->PwefetchSouwceWinesY = wocaws->PwefetchSouwceWinesY;
	CawcuwateVMWowAndSwath_pawams->PwefetchSouwceWinesC = wocaws->PwefetchSouwceWinesC;
	CawcuwateVMWowAndSwath_pawams->VInitPweFiwwY = wocaws->VInitPweFiwwY;
	CawcuwateVMWowAndSwath_pawams->VInitPweFiwwC = wocaws->VInitPweFiwwC;
	CawcuwateVMWowAndSwath_pawams->MaxNumSwathY = wocaws->MaxNumSwathY;
	CawcuwateVMWowAndSwath_pawams->MaxNumSwathC = wocaws->MaxNumSwathC;
	CawcuwateVMWowAndSwath_pawams->meta_wow_bw = wocaws->meta_wow_bw;
	CawcuwateVMWowAndSwath_pawams->dpte_wow_bw = wocaws->dpte_wow_bw;
	CawcuwateVMWowAndSwath_pawams->PixewPTEBytesPewWow = wocaws->PixewPTEBytesPewWow;
	CawcuwateVMWowAndSwath_pawams->PDEAndMetaPTEBytesFwame = wocaws->PDEAndMetaPTEBytesFwame;
	CawcuwateVMWowAndSwath_pawams->MetaWowByte = wocaws->MetaWowByte;
	CawcuwateVMWowAndSwath_pawams->use_one_wow_fow_fwame = wocaws->use_one_wow_fow_fwame;
	CawcuwateVMWowAndSwath_pawams->use_one_wow_fow_fwame_fwip = wocaws->use_one_wow_fow_fwame_fwip;
	CawcuwateVMWowAndSwath_pawams->UsesMAWWFowStaticScween = wocaws->UsesMAWWFowStaticScween;
	CawcuwateVMWowAndSwath_pawams->PTE_BUFFEW_MODE = wocaws->PTE_BUFFEW_MODE;
	CawcuwateVMWowAndSwath_pawams->BIGK_FWAGMENT_SIZE = wocaws->BIGK_FWAGMENT_SIZE;

	CawcuwateVMWowAndSwath(&mode_wib->scwatch,
	CawcuwateVMWowAndSwath_pawams);

	s->WeowdewBytes = (dmw_uint_t)(mode_wib->ms.soc.num_chans * dmw_max3(
			mode_wib->ms.soc.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes,
			mode_wib->ms.soc.uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes,
			mode_wib->ms.soc.uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes));

	s->VMDataOnwyWetuwnBW = dmw_get_wetuwn_bw_mbps_vm_onwy(&mode_wib->ms.soc,
																	mode_wib->ms.state.use_ideaw_dwam_bw_stwobe,
																	mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
																	wocaws->Dcfcwk,
																	mode_wib->ms.FabwicCwock,
																	mode_wib->ms.DWAMSpeed);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: wocaws->Dcfcwk = %f\n", __func__, wocaws->Dcfcwk);
	dmw_pwint("DMW::%s: mode_wib->ms.soc.wetuwn_bus_width_bytes = %u\n", __func__, mode_wib->ms.soc.wetuwn_bus_width_bytes);
	dmw_pwint("DMW::%s: mode_wib->ms.FabwicCwock = %f\n", __func__, mode_wib->ms.FabwicCwock);
	dmw_pwint("DMW::%s: mode_wib->ms.soc.fabwic_datapath_to_dcn_data_wetuwn_bytes = %u\n", __func__, mode_wib->ms.soc.fabwic_datapath_to_dcn_data_wetuwn_bytes);
	dmw_pwint("DMW::%s: mode_wib->ms.soc.pct_ideaw_sdp_bw_aftew_uwgent = %f\n", __func__, mode_wib->ms.soc.pct_ideaw_sdp_bw_aftew_uwgent);
	dmw_pwint("DMW::%s: mode_wib->ms.DWAMSpeed = %f\n", __func__, mode_wib->ms.DWAMSpeed);
	dmw_pwint("DMW::%s: mode_wib->ms.soc.num_chans = %u\n", __func__, mode_wib->ms.soc.num_chans);
	dmw_pwint("DMW::%s: mode_wib->ms.soc.dwam_channew_width_bytes = %u\n", __func__, mode_wib->ms.soc.dwam_channew_width_bytes);
	dmw_pwint("DMW::%s: mode_wib->ms.state_idx = %u\n", __func__, mode_wib->ms.state_idx);
	dmw_pwint("DMW::%s: mode_wib->ms.max_state_idx = %u\n", __func__, mode_wib->ms.max_state_idx);
	dmw_pwint("DMW::%s: mode_wib->ms.state.use_ideaw_dwam_bw_stwobe = %u\n", __func__, mode_wib->ms.state.use_ideaw_dwam_bw_stwobe);
	dmw_pwint("DMW::%s: VMDataOnwyWetuwnBW = %f\n", __func__, s->VMDataOnwyWetuwnBW);
	dmw_pwint("DMW::%s: WetuwnBW = %f\n",  __func__, mode_wib->ms.WetuwnBW);
#endif

	s->HostVMInefficiencyFactow = 1.0;
	if (mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe && mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe)
		s->HostVMInefficiencyFactow = mode_wib->ms.WetuwnBW / s->VMDataOnwyWetuwnBW;

	s->TotawDCCActiveDPP = 0;
	s->TotawActiveDPP = 0;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->TotawActiveDPP = s->TotawActiveDPP + mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k];
		if (mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k])
			s->TotawDCCActiveDPP = s->TotawDCCActiveDPP + mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k];
	}

	wocaws->UwgentExtwaWatency = CawcuwateExtwaWatency(
			mode_wib->ms.soc.wound_twip_ping_watency_dcfcwk_cycwes,
			s->WeowdewBytes,
			wocaws->Dcfcwk,
			s->TotawActiveDPP,
			mode_wib->ms.ip.pixew_chunk_size_kbytes,
			s->TotawDCCActiveDPP,
			mode_wib->ms.ip.meta_chunk_size_kbytes,
			mode_wib->ms.WetuwnBW,
			mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe,
			mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
			wocaws->dpte_gwoup_bytes,
			s->HostVMInefficiencyFactow,
			mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024,
			mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews);

	wocaws->TCawc = 24.0 / wocaws->DCFCWKDeepSweep;

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == k) {
			if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
				wocaws->WwitebackDeway[k] =
						mode_wib->ms.state.wwiteback_watency_us
								+ CawcuwateWwiteBackDeway(
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[k],
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[k],
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[k],
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[k],
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k],
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[k],
										mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[k],
										mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]) / wocaws->Dispcwk;
			} ewse
				wocaws->WwitebackDeway[k] = 0;
			fow (j = 0; j < mode_wib->ms.num_active_pwanes; ++j) {
				if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[j] == k
						&& mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[j] == twue) {
					wocaws->WwitebackDeway[k] =
							dmw_max(
									wocaws->WwitebackDeway[k],
									mode_wib->ms.state.wwiteback_watency_us
											+ CawcuwateWwiteBackDeway(
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[j],
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackHWatio[j],
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVWatio[j],
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackVTaps[j],
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[j],
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[j],
													mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[j],
													mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]) / wocaws->Dispcwk);
				}
			}
		}
	}

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k)
		fow (j = 0; j < mode_wib->ms.num_active_pwanes; ++j)
			if (mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming[k] == j)
				wocaws->WwitebackDeway[k] = wocaws->WwitebackDeway[j];

	wocaws->UwgentWatency = CawcuwateUwgentWatency(mode_wib->ms.state.uwgent_watency_pixew_data_onwy_us,
												mode_wib->ms.state.uwgent_watency_pixew_mixed_with_vm_data_us,
												mode_wib->ms.state.uwgent_watency_vm_data_onwy_us,
												mode_wib->ms.soc.do_uwgent_watency_adjustment,
												mode_wib->ms.state.uwgent_watency_adjustment_fabwic_cwock_component_us,
												mode_wib->ms.state.uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz,
												mode_wib->ms.FabwicCwock);

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		CawcuwateUwgentBuwstFactow(mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k],
									wocaws->swath_width_wuma_ub[k],
									wocaws->swath_width_chwoma_ub[k],
									wocaws->SwathHeightY[k],
									wocaws->SwathHeightC[k],
									mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
									wocaws->UwgentWatency,
									mode_wib->ms.ip.cuwsow_buffew_size,
									mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k],
									mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k],
									mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k],
									mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k],
									wocaws->BytePewPixewDETY[k],
									wocaws->BytePewPixewDETC[k],
									wocaws->DETBuffewSizeY[k],
									wocaws->DETBuffewSizeC[k],

									/* output */
									&wocaws->UwgBuwstFactowCuwsow[k],
									&wocaws->UwgBuwstFactowWuma[k],
									&wocaws->UwgBuwstFactowChwoma[k],
									&wocaws->NoUwgentWatencyHiding[k]);

		wocaws->cuwsow_bw[k] = mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k] / 8.0 /
								((dmw_fwoat_t) mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k];
	}

	s->VStawtupWines = __DMW_VBA_MIN_VSTAWTUP__;
	s->MaxVStawtupAwwPwanes = 0;

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->MaxVStawtupWines[k] = CawcuwateMaxVStawtup(k,
													mode_wib->ms.ip.ptoi_suppowted,
													mode_wib->ms.ip.vbwank_nom_defauwt_us,
													&mode_wib->ms.cache_dispway_cfg.timing,
													wocaws->WwitebackDeway[k]);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u MaxVStawtupWines   = %u\n", __func__, k, s->MaxVStawtupWines[k]);
		dmw_pwint("DMW::%s: k=%u WwitebackDeway     = %f\n", __func__, k, wocaws->WwitebackDeway[k]);
#endif
	}

	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k)
		s->MaxVStawtupAwwPwanes = (dmw_uint_t)(dmw_max(s->MaxVStawtupAwwPwanes, s->MaxVStawtupWines[k]));

	s->ImmediateFwipWequiwementFinaw = fawse;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->ImmediateFwipWequiwementFinaw = s->ImmediateFwipWequiwementFinaw || (mode_wib->ms.powicy.ImmediateFwipWequiwement[k] == dmw_immediate_fwip_wequiwed);
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: ImmediateFwipWequiwementFinaw = %u\n", __func__, s->ImmediateFwipWequiwementFinaw);
#endif

	// The pwefetch scheduwing shouwd onwy be cawcuwated once as pew AwwowFowPStateChangeOwStuttewInVBwank wequiwement
	// If the AwwowFowPStateChangeOwStuttewInVBwank wequiwement is not stwict (i.e. onwy twy those powew saving featuwe
	// if possibwe, then wiww twy to pwogwam fow the best powew saving featuwes in owdew of diffcuwty (dwam, fcwk, stuttew)
	s->itewation = 0;
	s->MaxTotawWDBandwidth = 0;
	s->AwwPwefetchModeTested = fawse;
	fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
		CawcuwatePwefetchMode(mode_wib->ms.powicy.AwwowFowPStateChangeOwStuttewInVBwank[k], &s->MinPwefetchMode[k], &s->MaxPwefetchMode[k]);
		s->NextPwefetchMode[k] = s->MinPwefetchMode[k];
	}

	do {
		s->MaxTotawWDBandwidthNoUwgentBuwst = 0.0;
		s->DestinationWineTimesFowPwefetchWessThan2 = fawse;
		s->VWatioPwefetchMoweThanMax = fawse;

		dmw_pwint("DMW::%s: Stawt one itewation: VStawtupWines = %u\n", __func__, s->VStawtupWines);

		s->AwwPwefetchModeTested = twue;
		s->MaxTotawWDBandwidth = 0;
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			wocaws->PwefetchMode[k] = s->NextPwefetchMode[k];
			TWait = CawcuwateTWait(
					wocaws->PwefetchMode[k],
					mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k],
					mode_wib->ms.powicy.SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
					mode_wib->ms.cache_dispway_cfg.timing.DWWDispway[k],
					mode_wib->ms.state.dwam_cwock_change_watency_us,
					mode_wib->ms.state.fcwk_change_watency_us,
					wocaws->UwgentWatency,
					mode_wib->ms.state.sw_entew_pwus_exit_time_us);

			myPipe = &s->myPipe;
			myPipe->Dppcwk = wocaws->Dppcwk[k];
			myPipe->Dispcwk = wocaws->Dispcwk;
			myPipe->PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k];
			myPipe->DCFCwkDeepSweep = wocaws->DCFCWKDeepSweep;
			myPipe->DPPPewSuwface = mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k];
			myPipe->ScawewEnabwed = mode_wib->ms.cache_dispway_cfg.pwane.ScawewEnabwed[k];
			myPipe->SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k];
			myPipe->BwockWidth256BytesY = wocaws->BwockWidth256BytesY[k];
			myPipe->BwockHeight256BytesY = wocaws->BwockHeight256BytesY[k];
			myPipe->BwockWidth256BytesC = wocaws->BwockWidth256BytesC[k];
			myPipe->BwockHeight256BytesC = wocaws->BwockHeight256BytesC[k];
			myPipe->IntewwaceEnabwe = mode_wib->ms.cache_dispway_cfg.timing.Intewwace[k];
			myPipe->NumbewOfCuwsows = mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows[k];
			myPipe->VBwank = mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VActive[k];
			myPipe->HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k];
			myPipe->HActive = mode_wib->ms.cache_dispway_cfg.timing.HActive[k];
			myPipe->DCCEnabwe = mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k];
			myPipe->ODMMode = mode_wib->ms.cache_dispway_cfg.hw.ODMMode[k];
			myPipe->SouwcePixewFowmat = mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k];
			myPipe->BytePewPixewY = wocaws->BytePewPixewY[k];
			myPipe->BytePewPixewC = wocaws->BytePewPixewC[k];
			myPipe->PwogwessiveToIntewwaceUnitInOPP = mode_wib->ms.ip.ptoi_suppowted;

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: Cawwing CawcuwatePwefetchScheduwe fow k=%u\n", __func__, k);
			dmw_pwint("DMW::%s: AwwowFowPStateChangeOwStuttewInVBwank = %u\n", __func__, mode_wib->ms.powicy.AwwowFowPStateChangeOwStuttewInVBwank[k]);
			dmw_pwint("DMW::%s: PwefetchMode[k] = %u (Min=%u Max=%u)\n", __func__, wocaws->PwefetchMode[k], s->MinPwefetchMode[k], s->MaxPwefetchMode[k]);
#endif

			CawcuwatePwefetchScheduwe_pawams->EnhancedPwefetchScheduweAccewewationFinaw = mode_wib->ms.powicy.EnhancedPwefetchScheduweAccewewationFinaw;
			CawcuwatePwefetchScheduwe_pawams->HostVMInefficiencyFactow = s->HostVMInefficiencyFactow;
			CawcuwatePwefetchScheduwe_pawams->myPipe = myPipe;
			CawcuwatePwefetchScheduwe_pawams->DSCDeway = wocaws->DSCDeway[k];
			CawcuwatePwefetchScheduwe_pawams->DPPCWKDewaySubtotawPwusCNVCFowmatew = mode_wib->ms.ip.dppcwk_deway_subtotaw + mode_wib->ms.ip.dppcwk_deway_cnvc_fowmattew;
			CawcuwatePwefetchScheduwe_pawams->DPPCWKDewaySCW = mode_wib->ms.ip.dppcwk_deway_scw;
			CawcuwatePwefetchScheduwe_pawams->DPPCWKDewaySCWWBOnwy = mode_wib->ms.ip.dppcwk_deway_scw_wb_onwy;
			CawcuwatePwefetchScheduwe_pawams->DPPCWKDewayCNVCCuwsow = mode_wib->ms.ip.dppcwk_deway_cnvc_cuwsow;
			CawcuwatePwefetchScheduwe_pawams->DISPCWKDewaySubtotaw = mode_wib->ms.ip.dispcwk_deway_subtotaw;
			CawcuwatePwefetchScheduwe_pawams->DPP_WECOUT_WIDTH = (dmw_uint_t)(wocaws->SwathWidthY[k] / mode_wib->ms.cache_dispway_cfg.pwane.HWatio[k]);
			CawcuwatePwefetchScheduwe_pawams->OutputFowmat = mode_wib->ms.cache_dispway_cfg.output.OutputFowmat[k];
			CawcuwatePwefetchScheduwe_pawams->MaxIntewDCNTiweWepeatews = mode_wib->ms.ip.max_intew_dcn_tiwe_wepeatews;
			CawcuwatePwefetchScheduwe_pawams->VStawtup = (dmw_uint_t)(dmw_min(s->VStawtupWines, s->MaxVStawtupWines[k]));
			CawcuwatePwefetchScheduwe_pawams->MaxVStawtup = s->MaxVStawtupWines[k];
			CawcuwatePwefetchScheduwe_pawams->GPUVMPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews;
			CawcuwatePwefetchScheduwe_pawams->GPUVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe;
			CawcuwatePwefetchScheduwe_pawams->HostVMEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe;
			CawcuwatePwefetchScheduwe_pawams->HostVMMaxNonCachedPageTabweWevews = mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews;
			CawcuwatePwefetchScheduwe_pawams->HostVMMinPageSize = mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024;
			CawcuwatePwefetchScheduwe_pawams->DynamicMetadataEnabwe = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataEnabwe[k];
			CawcuwatePwefetchScheduwe_pawams->DynamicMetadataVMEnabwed = mode_wib->ms.ip.dynamic_metadata_vm_enabwed;
			CawcuwatePwefetchScheduwe_pawams->DynamicMetadataWinesBefoweActiveWequiwed = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataWinesBefoweActiveWequiwed[k];
			CawcuwatePwefetchScheduwe_pawams->DynamicMetadataTwansmittedBytes = mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataTwansmittedBytes[k];
			CawcuwatePwefetchScheduwe_pawams->UwgentWatency = wocaws->UwgentWatency;
			CawcuwatePwefetchScheduwe_pawams->UwgentExtwaWatency = wocaws->UwgentExtwaWatency;
			CawcuwatePwefetchScheduwe_pawams->TCawc = wocaws->TCawc;
			CawcuwatePwefetchScheduwe_pawams->PDEAndMetaPTEBytesFwame = wocaws->PDEAndMetaPTEBytesFwame[k];
			CawcuwatePwefetchScheduwe_pawams->MetaWowByte = wocaws->MetaWowByte[k];
			CawcuwatePwefetchScheduwe_pawams->PixewPTEBytesPewWow = wocaws->PixewPTEBytesPewWow[k];
			CawcuwatePwefetchScheduwe_pawams->PwefetchSouwceWinesY = wocaws->PwefetchSouwceWinesY[k];
			CawcuwatePwefetchScheduwe_pawams->VInitPweFiwwY = wocaws->VInitPweFiwwY[k];
			CawcuwatePwefetchScheduwe_pawams->MaxNumSwathY = wocaws->MaxNumSwathY[k];
			CawcuwatePwefetchScheduwe_pawams->PwefetchSouwceWinesC = wocaws->PwefetchSouwceWinesC[k];
			CawcuwatePwefetchScheduwe_pawams->VInitPweFiwwC = wocaws->VInitPweFiwwC[k];
			CawcuwatePwefetchScheduwe_pawams->MaxNumSwathC = wocaws->MaxNumSwathC[k];
			CawcuwatePwefetchScheduwe_pawams->swath_width_wuma_ub = wocaws->swath_width_wuma_ub[k];
			CawcuwatePwefetchScheduwe_pawams->swath_width_chwoma_ub = wocaws->swath_width_chwoma_ub[k];
			CawcuwatePwefetchScheduwe_pawams->SwathHeightY = wocaws->SwathHeightY[k];
			CawcuwatePwefetchScheduwe_pawams->SwathHeightC = wocaws->SwathHeightC[k];
			CawcuwatePwefetchScheduwe_pawams->TWait = TWait;
			CawcuwatePwefetchScheduwe_pawams->DSTXAftewScawew = &wocaws->DSTXAftewScawew[k];
			CawcuwatePwefetchScheduwe_pawams->DSTYAftewScawew = &wocaws->DSTYAftewScawew[k];
			CawcuwatePwefetchScheduwe_pawams->DestinationWinesFowPwefetch = &wocaws->DestinationWinesFowPwefetch[k];
			CawcuwatePwefetchScheduwe_pawams->DestinationWinesToWequestVMInVBwank = &wocaws->DestinationWinesToWequestVMInVBwank[k];
			CawcuwatePwefetchScheduwe_pawams->DestinationWinesToWequestWowInVBwank = &wocaws->DestinationWinesToWequestWowInVBwank[k];
			CawcuwatePwefetchScheduwe_pawams->VWatioPwefetchY = &wocaws->VWatioPwefetchY[k];
			CawcuwatePwefetchScheduwe_pawams->VWatioPwefetchC = &wocaws->VWatioPwefetchC[k];
			CawcuwatePwefetchScheduwe_pawams->WequiwedPwefetchPixDataBWWuma = &wocaws->WequiwedPwefetchPixDataBWWuma[k];
			CawcuwatePwefetchScheduwe_pawams->WequiwedPwefetchPixDataBWChwoma = &wocaws->WequiwedPwefetchPixDataBWChwoma[k];
			CawcuwatePwefetchScheduwe_pawams->NotEnoughTimeFowDynamicMetadata = &wocaws->NotEnoughTimeFowDynamicMetadata[k];
			CawcuwatePwefetchScheduwe_pawams->Tno_bw = &wocaws->Tno_bw[k];
			CawcuwatePwefetchScheduwe_pawams->pwefetch_vmwow_bw = &wocaws->pwefetch_vmwow_bw[k];
			CawcuwatePwefetchScheduwe_pawams->Tdmdw_vm = &wocaws->Tdmdw_vm[k];
			CawcuwatePwefetchScheduwe_pawams->Tdmdw = &wocaws->Tdmdw[k];
			CawcuwatePwefetchScheduwe_pawams->TSetup = &wocaws->TSetup[k];
			CawcuwatePwefetchScheduwe_pawams->VUpdateOffsetPix = &wocaws->VUpdateOffsetPix[k];
			CawcuwatePwefetchScheduwe_pawams->VUpdateWidthPix = &wocaws->VUpdateWidthPix[k];
			CawcuwatePwefetchScheduwe_pawams->VWeadyOffsetPix = &wocaws->VWeadyOffsetPix[k];

			wocaws->NoTimeToPwefetch[k] =
				CawcuwatePwefetchScheduwe(&mode_wib->scwatch,
					CawcuwatePwefetchScheduwe_pawams);

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0u NoTimeToPwefetch=%0d\n", __func__, k, wocaws->NoTimeToPwefetch[k]);
#endif
			wocaws->VStawtup[k] = (dmw_uint_t)(dmw_min(s->VStawtupWines, s->MaxVStawtupWines[k]));
			wocaws->VStawtupMin[k] = wocaws->VStawtup[k];
		}

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			CawcuwateUwgentBuwstFactow(
				mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k],
				wocaws->swath_width_wuma_ub[k],
				wocaws->swath_width_chwoma_ub[k],
				wocaws->SwathHeightY[k],
				wocaws->SwathHeightC[k],
				mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
				wocaws->UwgentWatency,
				mode_wib->ms.ip.cuwsow_buffew_size,
				mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k],
				mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k],
				wocaws->VWatioPwefetchY[k],
				wocaws->VWatioPwefetchC[k],
				wocaws->BytePewPixewDETY[k],
				wocaws->BytePewPixewDETC[k],
				wocaws->DETBuffewSizeY[k],
				wocaws->DETBuffewSizeC[k],
				/* Output */
				&wocaws->UwgBuwstFactowCuwsowPwe[k],
				&wocaws->UwgBuwstFactowWumaPwe[k],
				&wocaws->UwgBuwstFactowChwomaPwe[k],
				&wocaws->NoUwgentWatencyHidingPwe[k]);

			wocaws->cuwsow_bw_pwe[k] = mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth[k] * mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP[k] / 8.0 / (mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * wocaws->VWatioPwefetchY[k];

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0u DPPPewSuwface=%u\n", __func__, k, mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k]);
			dmw_pwint("DMW::%s: k=%0u UwgBuwstFactowWuma=%f\n", __func__, k, wocaws->UwgBuwstFactowWuma[k]);
			dmw_pwint("DMW::%s: k=%0u UwgBuwstFactowChwoma=%f\n", __func__, k, wocaws->UwgBuwstFactowChwoma[k]);
			dmw_pwint("DMW::%s: k=%0u UwgBuwstFactowWumaPwe=%f\n", __func__, k, wocaws->UwgBuwstFactowWumaPwe[k]);
			dmw_pwint("DMW::%s: k=%0u UwgBuwstFactowChwomaPwe=%f\n", __func__, k, wocaws->UwgBuwstFactowChwomaPwe[k]);

			dmw_pwint("DMW::%s: k=%0u VWatioPwefetchY=%f\n", __func__, k, wocaws->VWatioPwefetchY[k]);
			dmw_pwint("DMW::%s: k=%0u VWatioY=%f\n", __func__, k, mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k]);

			dmw_pwint("DMW::%s: k=%0u pwefetch_vmwow_bw=%f\n", __func__, k, wocaws->pwefetch_vmwow_bw[k]);
			dmw_pwint("DMW::%s: k=%0u WeadBandwidthSuwfaceWuma=%f\n", __func__, k, wocaws->WeadBandwidthSuwfaceWuma[k]);
			dmw_pwint("DMW::%s: k=%0u WeadBandwidthSuwfaceChwoma=%f\n", __func__, k, wocaws->WeadBandwidthSuwfaceChwoma[k]);
			dmw_pwint("DMW::%s: k=%0u cuwsow_bw=%f\n", __func__, k, wocaws->cuwsow_bw[k]);
			dmw_pwint("DMW::%s: k=%0u meta_wow_bw=%f\n", __func__, k, wocaws->meta_wow_bw[k]);
			dmw_pwint("DMW::%s: k=%0u dpte_wow_bw=%f\n", __func__, k, wocaws->dpte_wow_bw[k]);
			dmw_pwint("DMW::%s: k=%0u WequiwedPwefetchPixDataBWWuma=%f\n", __func__, k, wocaws->WequiwedPwefetchPixDataBWWuma[k]);
			dmw_pwint("DMW::%s: k=%0u WequiwedPwefetchPixDataBWChwoma=%f\n", __func__, k, wocaws->WequiwedPwefetchPixDataBWChwoma[k]);
			dmw_pwint("DMW::%s: k=%0u cuwsow_bw_pwe=%f\n", __func__, k, wocaws->cuwsow_bw_pwe[k]);
			dmw_pwint("DMW::%s: k=%0u MaxTotawWDBandwidthNoUwgentBuwst=%f\n", __func__, k, s->MaxTotawWDBandwidthNoUwgentBuwst);
#endif
			if (wocaws->DestinationWinesFowPwefetch[k] < 2)
				s->DestinationWineTimesFowPwefetchWessThan2 = twue;

			if (wocaws->VWatioPwefetchY[k] > __DMW_MAX_VWATIO_PWE_ENHANCE_PWEFETCH_ACC__ ||
				wocaws->VWatioPwefetchC[k] > __DMW_MAX_VWATIO_PWE_ENHANCE_PWEFETCH_ACC__ ||
				((s->VStawtupWines < s->MaxVStawtupWines[k] || mode_wib->ms.powicy.EnhancedPwefetchScheduweAccewewationFinaw == 0) &&
					(wocaws->VWatioPwefetchY[k] > __DMW_MAX_VWATIO_PWE__ || wocaws->VWatioPwefetchC[k] > __DMW_MAX_VWATIO_PWE__)))
				s->VWatioPwefetchMoweThanMax = twue;

			//dmw_boow_t DestinationWinesToWequestVMInVBwankEquawOwMoweThan32 = fawse;
			//dmw_boow_t DestinationWinesToWequestWowInVBwankEquawOwMoweThan16 = fawse;
			//if (wocaws->DestinationWinesToWequestVMInVBwank[k] >= 32) {
			//    DestinationWinesToWequestVMInVBwankEquawOwMoweThan32 = twue;
			//}

			//if (wocaws->DestinationWinesToWequestWowInVBwank[k] >= 16) {
			//    DestinationWinesToWequestWowInVBwankEquawOwMoweThan16 = twue;
			//}
		}

		wocaws->FwactionOfUwgentBandwidth = s->MaxTotawWDBandwidthNoUwgentBuwst / mode_wib->ms.WetuwnBW;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: MaxTotawWDBandwidthNoUwgentBuwst=%f \n", __func__, s->MaxTotawWDBandwidthNoUwgentBuwst);
		dmw_pwint("DMW::%s: WetuwnBW=%f \n", __func__, mode_wib->ms.WetuwnBW);
		dmw_pwint("DMW::%s: FwactionOfUwgentBandwidth=%f \n", __func__, wocaws->FwactionOfUwgentBandwidth);
#endif

		CawcuwatePwefetchBandwithSuppowt(
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.WetuwnBW,
			mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
			wocaws->NoUwgentWatencyHidingPwe,
			wocaws->WeadBandwidthSuwfaceWuma,
			wocaws->WeadBandwidthSuwfaceChwoma,
			wocaws->WequiwedPwefetchPixDataBWWuma,
			wocaws->WequiwedPwefetchPixDataBWChwoma,
			wocaws->cuwsow_bw,
			wocaws->meta_wow_bw,
			wocaws->dpte_wow_bw,
			wocaws->cuwsow_bw_pwe,
			wocaws->pwefetch_vmwow_bw,
			mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
			wocaws->UwgBuwstFactowWuma,
			wocaws->UwgBuwstFactowChwoma,
			wocaws->UwgBuwstFactowCuwsow,
			wocaws->UwgBuwstFactowWumaPwe,
			wocaws->UwgBuwstFactowChwomaPwe,
			wocaws->UwgBuwstFactowCuwsowPwe,

			/* output */
			&s->MaxTotawWDBandwidth, // dmw_fwoat_t *PwefetchBandwidth
			&s->MaxTotawWDBandwidthNotIncwudingMAWWPwefetch, // dmw_fwoat_t *PwefetchBandwidthNotIncwudingMAWWPwefetch
			&s->dummy_singwe[0], // dmw_fwoat_t *FwactionOfUwgentBandwidth
			&wocaws->PwefetchModeSuppowted);

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k)
			s->dummy_unit_vectow[k] = 1.0;

		CawcuwatePwefetchBandwithSuppowt(mode_wib->ms.num_active_pwanes,
			mode_wib->ms.WetuwnBW,
			mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
			wocaws->NoUwgentWatencyHidingPwe,
			wocaws->WeadBandwidthSuwfaceWuma,
			wocaws->WeadBandwidthSuwfaceChwoma,
			wocaws->WequiwedPwefetchPixDataBWWuma,
			wocaws->WequiwedPwefetchPixDataBWChwoma,
			wocaws->cuwsow_bw,
			wocaws->meta_wow_bw,
			wocaws->dpte_wow_bw,
			wocaws->cuwsow_bw_pwe,
			wocaws->pwefetch_vmwow_bw,
			mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
			s->dummy_unit_vectow,
			s->dummy_unit_vectow,
			s->dummy_unit_vectow,
			s->dummy_unit_vectow,
			s->dummy_unit_vectow,
			s->dummy_unit_vectow,

			/* output */
			&s->NonUwgentMaxTotawWDBandwidth, // dmw_fwoat_t *PwefetchBandwidth
			&s->NonUwgentMaxTotawWDBandwidthNotIncwudingMAWWPwefetch, // dmw_fwoat_t *PwefetchBandwidthNotIncwudingMAWWPwefetch
			&wocaws->FwactionOfUwgentBandwidth,
			&s->dummy_boowean[0]); // dmw_boow_t *PwefetchBandwidthSuppowt

		if (s->VWatioPwefetchMoweThanMax != fawse || s->DestinationWineTimesFowPwefetchWessThan2 != fawse) {
			dmw_pwint("DMW::%s: VWatioPwefetchMoweThanMax                   = %u\n", __func__, s->VWatioPwefetchMoweThanMax);
			dmw_pwint("DMW::%s: DestinationWineTimesFowPwefetchWessThan2    = %u\n", __func__, s->DestinationWineTimesFowPwefetchWessThan2);
			wocaws->PwefetchModeSuppowted = fawse;
		}

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (wocaws->NoTimeToPwefetch[k] == twue || wocaws->NotEnoughTimeFowDynamicMetadata[k]) {
				dmw_pwint("DMW::%s: k=%u, NoTimeToPwefetch = %0d\n", __func__, k, wocaws->NoTimeToPwefetch[k]);
				dmw_pwint("DMW::%s: k=%u, NotEnoughTimeFowDynamicMetadata=%u\n", __func__, k, wocaws->NotEnoughTimeFowDynamicMetadata[k]);
				wocaws->PwefetchModeSuppowted = fawse;
			}
		}

		if (wocaws->PwefetchModeSuppowted == twue && mode_wib->ms.suppowt.ImmediateFwipSuppowt == twue) {
			wocaws->BandwidthAvaiwabweFowImmediateFwip = CawcuwateBandwidthAvaiwabweFowImmediateFwip(
																	mode_wib->ms.num_active_pwanes,
																	mode_wib->ms.WetuwnBW,
																	wocaws->WeadBandwidthSuwfaceWuma,
																	wocaws->WeadBandwidthSuwfaceChwoma,
																	wocaws->WequiwedPwefetchPixDataBWWuma,
																	wocaws->WequiwedPwefetchPixDataBWChwoma,
																	wocaws->cuwsow_bw,
																	wocaws->cuwsow_bw_pwe,
																	mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
																	wocaws->UwgBuwstFactowWuma,
																	wocaws->UwgBuwstFactowChwoma,
																	wocaws->UwgBuwstFactowCuwsow,
																	wocaws->UwgBuwstFactowWumaPwe,
																	wocaws->UwgBuwstFactowChwomaPwe,
																	wocaws->UwgBuwstFactowCuwsowPwe);

			wocaws->TotImmediateFwipBytes = 0;
			fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
				if (mode_wib->ms.powicy.ImmediateFwipWequiwement[k] != dmw_immediate_fwip_not_wequiwed) {
					wocaws->TotImmediateFwipBytes = wocaws->TotImmediateFwipBytes + mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k] * (wocaws->PDEAndMetaPTEBytesFwame[k] + wocaws->MetaWowByte[k]);
					if (wocaws->use_one_wow_fow_fwame_fwip[k]) {
						wocaws->TotImmediateFwipBytes = wocaws->TotImmediateFwipBytes + mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k] * (2 * wocaws->PixewPTEBytesPewWow[k]);
					} ewse {
						wocaws->TotImmediateFwipBytes = wocaws->TotImmediateFwipBytes + mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k] * wocaws->PixewPTEBytesPewWow[k];
					}
#ifdef __DMW_VBA_DEBUG__
					dmw_pwint("DMW::%s: k = %u\n", __func__, k);
					dmw_pwint("DMW::%s: DPPPewSuwface = %u\n", __func__, mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface[k]);
					dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %u\n", __func__, wocaws->PDEAndMetaPTEBytesFwame[k]);
					dmw_pwint("DMW::%s: MetaWowByte = %u\n", __func__, wocaws->MetaWowByte[k]);
					dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %u\n", __func__, wocaws->PixewPTEBytesPewWow[k]);
					dmw_pwint("DMW::%s: TotImmediateFwipBytes = %u\n", __func__, wocaws->TotImmediateFwipBytes);
#endif
				}
			}
			fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
				CawcuwateFwipScheduwe(
						s->HostVMInefficiencyFactow,
						wocaws->UwgentExtwaWatency,
						wocaws->UwgentWatency,
						mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews,
						mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe,
						mode_wib->ms.cache_dispway_cfg.pwane.HostVMMaxPageTabweWevews,
						mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe,
						mode_wib->ms.soc.hostvm_min_page_size_kbytes * 1024,
						wocaws->PDEAndMetaPTEBytesFwame[k],
						wocaws->MetaWowByte[k],
						wocaws->PixewPTEBytesPewWow[k],
						wocaws->BandwidthAvaiwabweFowImmediateFwip,
						wocaws->TotImmediateFwipBytes,
						mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
						mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k],
						mode_wib->ms.cache_dispway_cfg.pwane.VWatio[k],
						mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma[k],
						wocaws->Tno_bw[k],
						mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k],
						wocaws->dpte_wow_height[k],
						wocaws->meta_wow_height[k],
						wocaws->dpte_wow_height_chwoma[k],
						wocaws->meta_wow_height_chwoma[k],
						wocaws->use_one_wow_fow_fwame_fwip[k],

						/* Output */
						&wocaws->DestinationWinesToWequestVMInImmediateFwip[k],
						&wocaws->DestinationWinesToWequestWowInImmediateFwip[k],
						&wocaws->finaw_fwip_bw[k],
						&wocaws->ImmediateFwipSuppowtedFowPipe[k]);
			}

			CawcuwateImmediateFwipBandwithSuppowt(mode_wib->ms.num_active_pwanes,
												mode_wib->ms.WetuwnBW,
												mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
												mode_wib->ms.powicy.ImmediateFwipWequiwement,
												wocaws->finaw_fwip_bw,
												wocaws->WeadBandwidthSuwfaceWuma,
												wocaws->WeadBandwidthSuwfaceChwoma,
												wocaws->WequiwedPwefetchPixDataBWWuma,
												wocaws->WequiwedPwefetchPixDataBWChwoma,
												wocaws->cuwsow_bw,
												wocaws->meta_wow_bw,
												wocaws->dpte_wow_bw,
												wocaws->cuwsow_bw_pwe,
												wocaws->pwefetch_vmwow_bw,
												mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
												wocaws->UwgBuwstFactowWuma,
												wocaws->UwgBuwstFactowChwoma,
												wocaws->UwgBuwstFactowCuwsow,
												wocaws->UwgBuwstFactowWumaPwe,
												wocaws->UwgBuwstFactowChwomaPwe,
												wocaws->UwgBuwstFactowCuwsowPwe,

												/* output */
												&wocaws->totaw_dcn_wead_bw_with_fwip, // dmw_fwoat_t *TotawBandwidth
												&wocaws->totaw_dcn_wead_bw_with_fwip_not_incwuding_MAWW_pwefetch, // dmw_fwoat_t TotawBandwidthNotIncwudingMAWWPwefetch
												&s->dummy_singwe[0], // dmw_fwoat_t *FwactionOfUwgentBandwidth
												&wocaws->ImmediateFwipSuppowted); // dmw_boow_t *ImmediateFwipBandwidthSuppowt

			CawcuwateImmediateFwipBandwithSuppowt(mode_wib->ms.num_active_pwanes,
				mode_wib->ms.WetuwnBW,
				mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
				mode_wib->ms.powicy.ImmediateFwipWequiwement,
				wocaws->finaw_fwip_bw,
				wocaws->WeadBandwidthSuwfaceWuma,
				wocaws->WeadBandwidthSuwfaceChwoma,
				wocaws->WequiwedPwefetchPixDataBWWuma,
				wocaws->WequiwedPwefetchPixDataBWChwoma,
				wocaws->cuwsow_bw,
				wocaws->meta_wow_bw,
				wocaws->dpte_wow_bw,
				wocaws->cuwsow_bw_pwe,
				wocaws->pwefetch_vmwow_bw,
				mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
				s->dummy_unit_vectow,
				s->dummy_unit_vectow,
				s->dummy_unit_vectow,
				s->dummy_unit_vectow,
				s->dummy_unit_vectow,
				s->dummy_unit_vectow,

				/* output */
				&wocaws->non_uwgent_totaw_dcn_wead_bw_with_fwip, // dmw_fwoat_t *TotawBandwidth
				&wocaws->non_uwgent_totaw_dcn_wead_bw_with_fwip_not_incwuding_MAWW_pwefetch, // dmw_fwoat_t TotawBandwidthNotIncwudingMAWWPwefetch
				&wocaws->FwactionOfUwgentBandwidthImmediateFwip, // dmw_fwoat_t *FwactionOfUwgentBandwidth
				&s->dummy_boowean[0]); // dmw_boow_t *ImmediateFwipBandwidthSuppowt

			fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
				if (mode_wib->ms.powicy.ImmediateFwipWequiwement[k] != dmw_immediate_fwip_not_wequiwed && wocaws->ImmediateFwipSuppowtedFowPipe[k] == fawse) {
					wocaws->ImmediateFwipSuppowted = fawse;
#ifdef __DMW_VBA_DEBUG__
					dmw_pwint("DMW::%s: Pipe %0d not suppowting ifwip\n", __func__, k);
#endif
				}
			}
		} ewse {
			wocaws->ImmediateFwipSuppowted = fawse;
			wocaws->totaw_dcn_wead_bw_with_fwip = s->MaxTotawWDBandwidth;
			wocaws->totaw_dcn_wead_bw_with_fwip_not_incwuding_MAWW_pwefetch = s->MaxTotawWDBandwidthNotIncwudingMAWWPwefetch;
			wocaws->non_uwgent_totaw_dcn_wead_bw_with_fwip = s->NonUwgentMaxTotawWDBandwidth;
			wocaws->non_uwgent_totaw_dcn_wead_bw_with_fwip_not_incwuding_MAWW_pwefetch = s->NonUwgentMaxTotawWDBandwidthNotIncwudingMAWWPwefetch;
		}

		/* considew fwip suppowt is okay if the fwip bw is ok ow (when usew does't wequiwe a ifwip and thewe is no host vm) */
		wocaws->PwefetchAndImmediateFwipSuppowted = (wocaws->PwefetchModeSuppowted == twue &&
													((!mode_wib->ms.suppowt.ImmediateFwipSuppowt && !mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe && !s->ImmediateFwipWequiwementFinaw) ||
													wocaws->ImmediateFwipSuppowted)) ? twue : fawse;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: PwefetchModeSuppowted = %u\n", __func__, wocaws->PwefetchModeSuppowted);
		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k)
		dmw_pwint("DMW::%s: ImmediateFwipWequiwement[%u] = %u\n", __func__, k, mode_wib->ms.powicy.ImmediateFwipWequiwement[k] == dmw_immediate_fwip_wequiwed);
		dmw_pwint("DMW::%s: HostVMEnabwe = %u\n", __func__, mode_wib->ms.cache_dispway_cfg.pwane.HostVMEnabwe);
		dmw_pwint("DMW::%s: ImmediateFwipSuppowt = %u (fwom mode_suppowt)\n", __func__, mode_wib->ms.suppowt.ImmediateFwipSuppowt);
		dmw_pwint("DMW::%s: ImmediateFwipSuppowted = %u\n", __func__, wocaws->ImmediateFwipSuppowted);
		dmw_pwint("DMW::%s: PwefetchAndImmediateFwipSuppowted = %u\n", __func__, wocaws->PwefetchAndImmediateFwipSuppowted);
#endif
		dmw_pwint("DMW::%s: Done one itewation: VStawtupWines=%u, MaxVStawtupAwwPwanes=%u\n", __func__, s->VStawtupWines, s->MaxVStawtupAwwPwanes);

		s->VStawtupWines = s->VStawtupWines + 1;

		if (s->VStawtupWines > s->MaxVStawtupAwwPwanes) {
			s->VStawtupWines = __DMW_VBA_MIN_VSTAWTUP__;

			fow (k = 0; k <= mode_wib->ms.num_active_pwanes - 1; k++) {
				s->NextPwefetchMode[k] = s->NextPwefetchMode[k] + 1;

				if (s->NextPwefetchMode[k] <= s->MaxPwefetchMode[k])
					s->AwwPwefetchModeTested = fawse;
				dmw_pwint("DMW::%s: VStawtupWines=%u, weaches max vstawtup, twy next pwefetch mode=%u\n", __func__, s->VStawtupWines-1, s->AwwPwefetchModeTested);
			}
		} ewse {
			s->AwwPwefetchModeTested = fawse;
		}
		s->itewation++;
		if (s->itewation > 2500) {
			dmw_pwint("EWWOW: DMW::%s: Too many ewwows, exit now\n", __func__);
			ASSEWT(0);
		}
	} whiwe (!(wocaws->PwefetchAndImmediateFwipSuppowted || s->AwwPwefetchModeTested));

	if (wocaws->PwefetchAndImmediateFwipSuppowted) {
		dmw_pwint("DMW::%s: Good, Pwefetch and fwip scheduwing sowution found at VStawtupWines=%u (MaxVStawtupAwwPwanes=%u)\n", __func__, s->VStawtupWines-1, s->MaxVStawtupAwwPwanes);
	} ewse {
		dmw_pwint("DMW::%s: Bad, Pwefetch and fwip scheduwing sowution did NOT find sowution! (MaxVStawtupAwwPwanes=%u)\n", __func__, s->MaxVStawtupAwwPwanes);
	}

	//Watewmawks and NB P-State/DWAM Cwock Change Suppowt
	{
		s->mmSOCPawametews.UwgentWatency = wocaws->UwgentWatency;
		s->mmSOCPawametews.ExtwaWatency = wocaws->UwgentExtwaWatency;
		s->mmSOCPawametews.WwitebackWatency = mode_wib->ms.state.wwiteback_watency_us;
		s->mmSOCPawametews.DWAMCwockChangeWatency = mode_wib->ms.state.dwam_cwock_change_watency_us;
		s->mmSOCPawametews.FCWKChangeWatency = mode_wib->ms.state.fcwk_change_watency_us;
		s->mmSOCPawametews.SWExitTime = mode_wib->ms.state.sw_exit_time_us;
		s->mmSOCPawametews.SWEntewPwusExitTime = mode_wib->ms.state.sw_entew_pwus_exit_time_us;
		s->mmSOCPawametews.SWExitZ8Time = mode_wib->ms.state.sw_exit_z8_time_us;
		s->mmSOCPawametews.SWEntewPwusExitZ8Time = mode_wib->ms.state.sw_entew_pwus_exit_z8_time_us;
		s->mmSOCPawametews.USWWetwainingWatency = mode_wib->ms.state.usw_wetwaining_watency_us;
		s->mmSOCPawametews.SMNWatency = mode_wib->ms.soc.smn_watency_us;

		CawcuwateWatewmawks_pawams->USWWetwainingWequiwedFinaw = mode_wib->ms.powicy.USWWetwainingWequiwedFinaw;
		CawcuwateWatewmawks_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
		CawcuwateWatewmawks_pawams->PwefetchMode = wocaws->PwefetchMode;
		CawcuwateWatewmawks_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
		CawcuwateWatewmawks_pawams->MaxWineBuffewWines = mode_wib->ms.ip.max_wine_buffew_wines;
		CawcuwateWatewmawks_pawams->WineBuffewSize = mode_wib->ms.ip.wine_buffew_size_bits;
		CawcuwateWatewmawks_pawams->WwitebackIntewfaceBuffewSize = mode_wib->ms.ip.wwiteback_intewface_buffew_size_kbytes;
		CawcuwateWatewmawks_pawams->DCFCWK = wocaws->Dcfcwk;
		CawcuwateWatewmawks_pawams->WetuwnBW = mode_wib->ms.WetuwnBW;
		CawcuwateWatewmawks_pawams->SynchwonizeTimingsFinaw = mode_wib->ms.powicy.SynchwonizeTimingsFinaw;
		CawcuwateWatewmawks_pawams->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw = mode_wib->ms.powicy.SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
		CawcuwateWatewmawks_pawams->DWWDispway = mode_wib->ms.cache_dispway_cfg.timing.DWWDispway;
		CawcuwateWatewmawks_pawams->dpte_gwoup_bytes = wocaws->dpte_gwoup_bytes;
		CawcuwateWatewmawks_pawams->meta_wow_height = wocaws->meta_wow_height;
		CawcuwateWatewmawks_pawams->meta_wow_height_chwoma = wocaws->meta_wow_height_chwoma;
		CawcuwateWatewmawks_pawams->mmSOCPawametews = s->mmSOCPawametews;
		CawcuwateWatewmawks_pawams->WwitebackChunkSize = mode_wib->ms.ip.wwiteback_chunk_size_kbytes;
		CawcuwateWatewmawks_pawams->SOCCWK = mode_wib->ms.SOCCWK;
		CawcuwateWatewmawks_pawams->DCFCwkDeepSweep = wocaws->DCFCWKDeepSweep;
		CawcuwateWatewmawks_pawams->DETBuffewSizeY = wocaws->DETBuffewSizeY;
		CawcuwateWatewmawks_pawams->DETBuffewSizeC = wocaws->DETBuffewSizeC;
		CawcuwateWatewmawks_pawams->SwathHeightY = wocaws->SwathHeightY;
		CawcuwateWatewmawks_pawams->SwathHeightC = wocaws->SwathHeightC;
		CawcuwateWatewmawks_pawams->WBBitPewPixew = mode_wib->ms.cache_dispway_cfg.pwane.WBBitPewPixew;
		CawcuwateWatewmawks_pawams->SwathWidthY = wocaws->SwathWidthY;
		CawcuwateWatewmawks_pawams->SwathWidthC = wocaws->SwathWidthC;
		CawcuwateWatewmawks_pawams->HWatio = mode_wib->ms.cache_dispway_cfg.pwane.HWatio;
		CawcuwateWatewmawks_pawams->HWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma;
		CawcuwateWatewmawks_pawams->VTaps = mode_wib->ms.cache_dispway_cfg.pwane.VTaps;
		CawcuwateWatewmawks_pawams->VTapsChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VTapsChwoma;
		CawcuwateWatewmawks_pawams->VWatio = mode_wib->ms.cache_dispway_cfg.pwane.VWatio;
		CawcuwateWatewmawks_pawams->VWatioChwoma = mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma;
		CawcuwateWatewmawks_pawams->HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw;
		CawcuwateWatewmawks_pawams->VTotaw = mode_wib->ms.cache_dispway_cfg.timing.VTotaw;
		CawcuwateWatewmawks_pawams->VActive = mode_wib->ms.cache_dispway_cfg.timing.VActive;
		CawcuwateWatewmawks_pawams->PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock;
		CawcuwateWatewmawks_pawams->BwendingAndTiming = mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming;
		CawcuwateWatewmawks_pawams->DPPPewSuwface = mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface;
		CawcuwateWatewmawks_pawams->BytePewPixewDETY = wocaws->BytePewPixewDETY;
		CawcuwateWatewmawks_pawams->BytePewPixewDETC = wocaws->BytePewPixewDETC;
		CawcuwateWatewmawks_pawams->DSTXAftewScawew = wocaws->DSTXAftewScawew;
		CawcuwateWatewmawks_pawams->DSTYAftewScawew = wocaws->DSTYAftewScawew;
		CawcuwateWatewmawks_pawams->WwitebackEnabwe = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe;
		CawcuwateWatewmawks_pawams->WwitebackPixewFowmat = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat;
		CawcuwateWatewmawks_pawams->WwitebackDestinationWidth = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth;
		CawcuwateWatewmawks_pawams->WwitebackDestinationHeight = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight;
		CawcuwateWatewmawks_pawams->WwitebackSouwceHeight = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight;
		CawcuwateWatewmawks_pawams->UnboundedWequestEnabwed = wocaws->UnboundedWequestEnabwed;
		CawcuwateWatewmawks_pawams->CompwessedBuffewSizeInkByte = wocaws->CompwessedBuffewSizeInkByte;

		// Output
		CawcuwateWatewmawks_pawams->Watewmawk = &wocaws->Watewmawk; // Watewmawks *Watewmawk
		CawcuwateWatewmawks_pawams->DWAMCwockChangeSuppowt = &wocaws->DWAMCwockChangeSuppowt;
		CawcuwateWatewmawks_pawams->MaxActiveDWAMCwockChangeWatencySuppowted = wocaws->MaxActiveDWAMCwockChangeWatencySuppowted; // dmw_fwoat_t *MaxActiveDWAMCwockChangeWatencySuppowted[]
		CawcuwateWatewmawks_pawams->SubViewpowtWinesNeededInMAWW = wocaws->SubViewpowtWinesNeededInMAWW; // dmw_uint_t SubViewpowtWinesNeededInMAWW[]
		CawcuwateWatewmawks_pawams->FCWKChangeSuppowt = &wocaws->FCWKChangeSuppowt;
		CawcuwateWatewmawks_pawams->MaxActiveFCWKChangeWatencySuppowted = &wocaws->MaxActiveFCWKChangeWatencySuppowted; // dmw_fwoat_t *MaxActiveFCWKChangeWatencySuppowted
		CawcuwateWatewmawks_pawams->USWWetwainingSuppowt = &wocaws->USWWetwainingSuppowt;

		CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt(
			&mode_wib->scwatch,
			CawcuwateWatewmawks_pawams);

		/* Copy the cawcuwated watewmawks to mp.Watewmawk as the gettew functions awe
		 * impwemented by the DMW team to copy the cawcuwated vawues fwom the mp.Watewmawk intewface.
		 */
		memcpy(&mode_wib->mp.Watewmawk, CawcuwateWatewmawks_pawams->Watewmawk, sizeof(stwuct Watewmawks));

		fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
			if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
				wocaws->WwitebackAwwowDWAMCwockChangeEndPosition[k] = dmw_max(0, wocaws->VStawtupMin[k] * mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] /
																			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k] - wocaws->Watewmawk.WwitebackDWAMCwockChangeWatewmawk);
				wocaws->WwitebackAwwowFCWKChangeEndPosition[k] = dmw_max(0, wocaws->VStawtupMin[k] * mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] /
																			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k] - wocaws->Watewmawk.WwitebackFCWKChangeWatewmawk);
			} ewse {
				wocaws->WwitebackAwwowDWAMCwockChangeEndPosition[k] = 0;
				wocaws->WwitebackAwwowFCWKChangeEndPosition[k] = 0;
			}
		}
	}

	//Dispway Pipewine Dewivewy Time in Pwefetch, Gwoups
	CawcuwatePixewDewivewyTimes(
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatio,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma,
			wocaws->VWatioPwefetchY,
			wocaws->VWatioPwefetchC,
			wocaws->swath_width_wuma_ub,
			wocaws->swath_width_chwoma_ub,
			mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
			mode_wib->ms.cache_dispway_cfg.pwane.HWatio,
			mode_wib->ms.cache_dispway_cfg.pwane.HWatioChwoma,
			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock,
			wocaws->PSCW_THWOUGHPUT,
			wocaws->PSCW_THWOUGHPUT_CHWOMA,
			wocaws->Dppcwk,
			wocaws->BytePewPixewC,
			mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan,
			mode_wib->ms.cache_dispway_cfg.pwane.NumbewOfCuwsows,
			mode_wib->ms.cache_dispway_cfg.pwane.CuwsowWidth,
			mode_wib->ms.cache_dispway_cfg.pwane.CuwsowBPP,
			wocaws->BwockWidth256BytesY,
			wocaws->BwockHeight256BytesY,
			wocaws->BwockWidth256BytesC,
			wocaws->BwockHeight256BytesC,

			/* Output */
			wocaws->DispwayPipeWineDewivewyTimeWuma,
			wocaws->DispwayPipeWineDewivewyTimeChwoma,
			wocaws->DispwayPipeWineDewivewyTimeWumaPwefetch,
			wocaws->DispwayPipeWineDewivewyTimeChwomaPwefetch,
			wocaws->DispwayPipeWequestDewivewyTimeWuma,
			wocaws->DispwayPipeWequestDewivewyTimeChwoma,
			wocaws->DispwayPipeWequestDewivewyTimeWumaPwefetch,
			wocaws->DispwayPipeWequestDewivewyTimeChwomaPwefetch,
			wocaws->CuwsowWequestDewivewyTime,
			wocaws->CuwsowWequestDewivewyTimePwefetch);

	CawcuwateMetaAndPTETimes(
			wocaws->use_one_wow_fow_fwame,
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe,
			mode_wib->ms.ip.meta_chunk_size_kbytes,
			mode_wib->ms.ip.min_meta_chunk_size_bytes,
			mode_wib->ms.cache_dispway_cfg.timing.HTotaw,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatio,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatioChwoma,
			wocaws->DestinationWinesToWequestWowInVBwank,
			wocaws->DestinationWinesToWequestWowInImmediateFwip,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe,
			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock,
			wocaws->BytePewPixewY,
			wocaws->BytePewPixewC,
			mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan,
			wocaws->dpte_wow_height,
			wocaws->dpte_wow_height_chwoma,
			wocaws->meta_wow_width,
			wocaws->meta_wow_width_chwoma,
			wocaws->meta_wow_height,
			wocaws->meta_wow_height_chwoma,
			wocaws->meta_weq_width,
			wocaws->meta_weq_width_chwoma,
			wocaws->meta_weq_height,
			wocaws->meta_weq_height_chwoma,
			wocaws->dpte_gwoup_bytes,
			wocaws->PTEWequestSizeY,
			wocaws->PTEWequestSizeC,
			wocaws->PixewPTEWeqWidthY,
			wocaws->PixewPTEWeqHeightY,
			wocaws->PixewPTEWeqWidthC,
			wocaws->PixewPTEWeqHeightC,
			wocaws->dpte_wow_width_wuma_ub,
			wocaws->dpte_wow_width_chwoma_ub,

			/* Output */
			wocaws->DST_Y_PEW_PTE_WOW_NOM_W,
			wocaws->DST_Y_PEW_PTE_WOW_NOM_C,
			wocaws->DST_Y_PEW_META_WOW_NOM_W,
			wocaws->DST_Y_PEW_META_WOW_NOM_C,
			wocaws->TimePewMetaChunkNominaw,
			wocaws->TimePewChwomaMetaChunkNominaw,
			wocaws->TimePewMetaChunkVBwank,
			wocaws->TimePewChwomaMetaChunkVBwank,
			wocaws->TimePewMetaChunkFwip,
			wocaws->TimePewChwomaMetaChunkFwip,
			wocaws->time_pew_pte_gwoup_nom_wuma,
			wocaws->time_pew_pte_gwoup_vbwank_wuma,
			wocaws->time_pew_pte_gwoup_fwip_wuma,
			wocaws->time_pew_pte_gwoup_nom_chwoma,
			wocaws->time_pew_pte_gwoup_vbwank_chwoma,
			wocaws->time_pew_pte_gwoup_fwip_chwoma);

	CawcuwateVMGwoupAndWequestTimes(
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.cache_dispway_cfg.pwane.GPUVMEnabwe,
			mode_wib->ms.cache_dispway_cfg.pwane.GPUVMMaxPageTabweWevews,
			mode_wib->ms.cache_dispway_cfg.timing.HTotaw,
			wocaws->BytePewPixewC,
			wocaws->DestinationWinesToWequestVMInVBwank,
			wocaws->DestinationWinesToWequestVMInImmediateFwip,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe,
			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock,
			wocaws->dpte_wow_width_wuma_ub,
			wocaws->dpte_wow_width_chwoma_ub,
			wocaws->vm_gwoup_bytes,
			wocaws->dpde0_bytes_pew_fwame_ub_w,
			wocaws->dpde0_bytes_pew_fwame_ub_c,
			wocaws->meta_pte_bytes_pew_fwame_ub_w,
			wocaws->meta_pte_bytes_pew_fwame_ub_c,

			/* Output */
			wocaws->TimePewVMGwoupVBwank,
			wocaws->TimePewVMGwoupFwip,
			wocaws->TimePewVMWequestVBwank,
			wocaws->TimePewVMWequestFwip);

	// Min TTUVBwank
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (wocaws->PwefetchMode[k] == 0) {
			wocaws->MinTTUVBwank[k] = dmw_max4(
					wocaws->Watewmawk.DWAMCwockChangeWatewmawk,
					wocaws->Watewmawk.FCWKChangeWatewmawk,
					wocaws->Watewmawk.StuttewEntewPwusExitWatewmawk,
					wocaws->Watewmawk.UwgentWatewmawk);
		} ewse if (wocaws->PwefetchMode[k] == 1) {
			wocaws->MinTTUVBwank[k] = dmw_max3(
					wocaws->Watewmawk.FCWKChangeWatewmawk,
					wocaws->Watewmawk.StuttewEntewPwusExitWatewmawk,
					wocaws->Watewmawk.UwgentWatewmawk);
		} ewse if (wocaws->PwefetchMode[k] == 2) {
			wocaws->MinTTUVBwank[k] = dmw_max(
					wocaws->Watewmawk.StuttewEntewPwusExitWatewmawk,
					wocaws->Watewmawk.UwgentWatewmawk);
		} ewse {
			wocaws->MinTTUVBwank[k] = wocaws->Watewmawk.UwgentWatewmawk;
		}
		if (!mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataEnabwe[k])
			wocaws->MinTTUVBwank[k] = wocaws->TCawc + wocaws->MinTTUVBwank[k];
	}

	// DCC Configuwation
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: Cawcuwate DCC configuwation fow suwface k=%u\n", __func__, k);
#endif
		CawcuwateDCCConfiguwation(
			mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe[k],
			mode_wib->ms.powicy.DCCPwogwammingAssumesScanDiwectionUnknownFinaw,
			mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[k],
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthY[k],
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceWidthC[k],
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightY[k],
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceHeightC[k],
			mode_wib->ms.NomDETInKByte,
			wocaws->BwockHeight256BytesY[k],
			wocaws->BwockHeight256BytesC[k],
			mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[k],
			wocaws->BytePewPixewY[k],
			wocaws->BytePewPixewC[k],
			wocaws->BytePewPixewDETY[k],
			wocaws->BytePewPixewDETC[k],
			mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan[k],
			/* Output */
			&wocaws->DCCYMaxUncompwessedBwock[k],
			&wocaws->DCCCMaxUncompwessedBwock[k],
			&wocaws->DCCYMaxCompwessedBwock[k],
			&wocaws->DCCCMaxCompwessedBwock[k],
			&wocaws->DCCYIndependentBwock[k],
			&wocaws->DCCCIndependentBwock[k]);
	}

	// VStawtup Adjustment
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		s->Tvstawtup_mawgin = (s->MaxVStawtupWines[k] - wocaws->VStawtupMin[k]) * mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k];
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, MinTTUVBwank = %f (befowe vstawtup mawgin)\n", __func__, k, wocaws->MinTTUVBwank[k]);
#endif

		wocaws->MinTTUVBwank[k] = wocaws->MinTTUVBwank[k] + s->Tvstawtup_mawgin;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, Tvstawtup_mawgin = %f\n", __func__, k, s->Tvstawtup_mawgin);
		dmw_pwint("DMW::%s: k=%u, MaxVStawtupWines = %u\n", __func__, k, s->MaxVStawtupWines[k]);
		dmw_pwint("DMW::%s: k=%u, MinTTUVBwank = %f\n", __func__, k, wocaws->MinTTUVBwank[k]);
#endif

		wocaws->Tdmdw[k] = wocaws->Tdmdw[k] + s->Tvstawtup_mawgin;
		if (mode_wib->ms.cache_dispway_cfg.pwane.DynamicMetadataEnabwe[k] && mode_wib->ms.ip.dynamic_metadata_vm_enabwed) {
			wocaws->Tdmdw_vm[k] = wocaws->Tdmdw_vm[k] + s->Tvstawtup_mawgin;
		}

		isIntewwaceTiming        = (mode_wib->ms.cache_dispway_cfg.timing.Intewwace[k] && !mode_wib->ms.ip.ptoi_suppowted);

		// The actuaw positioning of the vstawtup
		wocaws->VStawtup[k] = (isIntewwaceTiming ? (2 * s->MaxVStawtupWines[k]) : s->MaxVStawtupWines[k]);

		s->dwg_vbwank_stawt        =  ((isIntewwaceTiming ? dmw_fwoow((mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k]) / 2.0, 1.0) :
																	mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k]) - mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k]);
		s->WSetup                  = dmw_fwoow(4.0 * wocaws->TSetup[k] / ((dmw_fwoat_t) mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]), 1.0) / 4.0;
		s->bwank_wines_wemaining   = (mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VActive[k]) - wocaws->VStawtup[k];

		if (s->bwank_wines_wemaining < 0) {
			dmw_pwint("EWWOW: Vstawtup is wawgew than vbwank!?\n");
			s->bwank_wines_wemaining = 0;
			ASSEWT(0);
		}
		wocaws->MIN_DST_Y_NEXT_STAWT[k] = s->dwg_vbwank_stawt + s->bwank_wines_wemaining + s->WSetup;

		// debug onwy
		s->owd_MIN_DST_Y_NEXT_STAWT = ((isIntewwaceTiming ? dmw_fwoow((mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k]) / 2.0, 1.0) :
																	mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k]) - mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k])
											+ dmw_max(1.0, dmw_ceiw((dmw_fwoat_t) wocaws->WwitebackDeway[k] / ((dmw_fwoat_t) mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]), 1.0))
											+ dmw_fwoow(4.0 * wocaws->TSetup[k] / ((dmw_fwoat_t) mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]), 1.0) / 4.0;

		if (((wocaws->VUpdateOffsetPix[k] + wocaws->VUpdateWidthPix[k] + wocaws->VWeadyOffsetPix[k]) / mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]) <=
			(isIntewwaceTiming ?
				dmw_fwoow((mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VActive[k] - mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k] - wocaws->VStawtup[k]) / 2.0, 1.0) :
				(int) (mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k] - mode_wib->ms.cache_dispway_cfg.timing.VActive[k] - mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k] - wocaws->VStawtup[k]))) {
			wocaws->VWEADY_AT_OW_AFTEW_VSYNC[k] = twue;
		} ewse {
			wocaws->VWEADY_AT_OW_AFTEW_VSYNC[k] = fawse;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, VStawtup = %u (max)\n", __func__, k, wocaws->VStawtup[k]);
		dmw_pwint("DMW::%s: k=%u, VStawtupMin = %u (max)\n", __func__, k, wocaws->VStawtupMin[k]);
		dmw_pwint("DMW::%s: k=%u, VUpdateOffsetPix = %u\n", __func__, k, wocaws->VUpdateOffsetPix[k]);
		dmw_pwint("DMW::%s: k=%u, VUpdateWidthPix = %u\n", __func__, k, wocaws->VUpdateWidthPix[k]);
		dmw_pwint("DMW::%s: k=%u, VWeadyOffsetPix = %u\n", __func__, k, wocaws->VWeadyOffsetPix[k]);
		dmw_pwint("DMW::%s: k=%u, HTotaw = %u\n", __func__, k, mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k]);
		dmw_pwint("DMW::%s: k=%u, VTotaw = %u\n", __func__, k, mode_wib->ms.cache_dispway_cfg.timing.VTotaw[k]);
		dmw_pwint("DMW::%s: k=%u, VActive = %u\n", __func__, k, mode_wib->ms.cache_dispway_cfg.timing.VActive[k]);
		dmw_pwint("DMW::%s: k=%u, VFwontPowch = %u\n", __func__, k, mode_wib->ms.cache_dispway_cfg.timing.VFwontPowch[k]);
		dmw_pwint("DMW::%s: k=%u, TSetup = %f\n", __func__, k, wocaws->TSetup[k]);
		dmw_pwint("DMW::%s: k=%u, MIN_DST_Y_NEXT_STAWT = %f\n", __func__, k, wocaws->MIN_DST_Y_NEXT_STAWT[k]);
		dmw_pwint("DMW::%s: k=%u, MIN_DST_Y_NEXT_STAWT = %f (owd)\n", __func__, k, s->owd_MIN_DST_Y_NEXT_STAWT);
		dmw_pwint("DMW::%s: k=%u, VWEADY_AT_OW_AFTEW_VSYNC = %u\n", __func__, k, wocaws->VWEADY_AT_OW_AFTEW_VSYNC[k]);
#endif
	}

	//Maximum Bandwidth Used
	s->TotawWWBandwidth = 0;
	s->WWBandwidth = 0;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue && mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackPixewFowmat[k] == dmw_444_32) {
			s->WWBandwidth = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k] * mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[k] /
							(mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] * mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * 4;
		} ewse if (mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe[k] == twue) {
			s->WWBandwidth = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationWidth[k] * mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackDestinationHeight[k] /
							(mode_wib->ms.cache_dispway_cfg.timing.HTotaw[k] * mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackSouwceHeight[k] / mode_wib->ms.cache_dispway_cfg.timing.PixewCwock[k]) * 8;
		}
		s->TotawWWBandwidth = s->TotawWWBandwidth + s->WWBandwidth;
	}

	wocaws->TotawDataWeadBandwidth = 0;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		wocaws->TotawDataWeadBandwidth = wocaws->TotawDataWeadBandwidth + wocaws->WeadBandwidthSuwfaceWuma[k] + wocaws->WeadBandwidthSuwfaceChwoma[k];

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%u, TotawDataWeadBandwidth = %f\n", __func__, k, wocaws->TotawDataWeadBandwidth);
		dmw_pwint("DMW::%s: k=%u, WeadBandwidthSuwfaceWuma = %f\n", __func__, k, wocaws->WeadBandwidthSuwfaceWuma[k]);
		dmw_pwint("DMW::%s: k=%u, WeadBandwidthSuwfaceChwoma = %f\n", __func__, k, wocaws->WeadBandwidthSuwfaceChwoma[k]);
#endif
	}

	wocaws->TotawDataWeadBandwidthNotIncwudingMAWWPwefetch = 0;
	fow (k = 0; k < mode_wib->ms.num_active_pwanes; ++k) {
		if (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[k] != dmw_use_maww_pstate_change_phantom_pipe) {
			wocaws->TotawDataWeadBandwidthNotIncwudingMAWWPwefetch = wocaws->TotawDataWeadBandwidthNotIncwudingMAWWPwefetch
		+ wocaws->WeadBandwidthSuwfaceWuma[k] + wocaws->WeadBandwidthSuwfaceChwoma[k];
		}
	}

	CawcuwateStuttewEfficiency_pawams->CompwessedBuffewSizeInkByte = wocaws->CompwessedBuffewSizeInkByte;
	CawcuwateStuttewEfficiency_pawams->UseMAWWFowPStateChange = mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange;
	CawcuwateStuttewEfficiency_pawams->UnboundedWequestEnabwed = wocaws->UnboundedWequestEnabwed;
	CawcuwateStuttewEfficiency_pawams->MetaFIFOSizeInKEntwies = mode_wib->ms.ip.meta_fifo_size_in_kentwies;
	CawcuwateStuttewEfficiency_pawams->ZewoSizeBuffewEntwies = mode_wib->ms.ip.zewo_size_buffew_entwies;
	CawcuwateStuttewEfficiency_pawams->PixewChunkSizeInKByte = mode_wib->ms.ip.pixew_chunk_size_kbytes;
	CawcuwateStuttewEfficiency_pawams->NumbewOfActiveSuwfaces = mode_wib->ms.num_active_pwanes;
	CawcuwateStuttewEfficiency_pawams->WOBBuffewSizeInKByte = mode_wib->ms.ip.wob_buffew_size_kbytes;
	CawcuwateStuttewEfficiency_pawams->TotawDataWeadBandwidth = wocaws->TotawDataWeadBandwidth;
	CawcuwateStuttewEfficiency_pawams->DCFCWK = wocaws->Dcfcwk;
	CawcuwateStuttewEfficiency_pawams->WetuwnBW = mode_wib->ms.WetuwnBW;
	CawcuwateStuttewEfficiency_pawams->CompbufWesewvedSpace64B = wocaws->compbuf_wesewved_space_64b;
	CawcuwateStuttewEfficiency_pawams->CompbufWesewvedSpaceZs = wocaws->compbuf_wesewved_space_zs;
	CawcuwateStuttewEfficiency_pawams->SWExitTime = mode_wib->ms.state.sw_exit_time_us;
	CawcuwateStuttewEfficiency_pawams->SWExitZ8Time = mode_wib->ms.state.sw_exit_z8_time_us;
	CawcuwateStuttewEfficiency_pawams->SynchwonizeTimingsFinaw = mode_wib->ms.powicy.SynchwonizeTimingsFinaw;
	CawcuwateStuttewEfficiency_pawams->BwendingAndTiming = mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming;
	CawcuwateStuttewEfficiency_pawams->StuttewEntewPwusExitWatewmawk = wocaws->Watewmawk.StuttewEntewPwusExitWatewmawk;
	CawcuwateStuttewEfficiency_pawams->Z8StuttewEntewPwusExitWatewmawk = wocaws->Watewmawk.Z8StuttewEntewPwusExitWatewmawk;
	CawcuwateStuttewEfficiency_pawams->PwogwessiveToIntewwaceUnitInOPP = mode_wib->ms.ip.ptoi_suppowted;
	CawcuwateStuttewEfficiency_pawams->Intewwace = mode_wib->ms.cache_dispway_cfg.timing.Intewwace;
	CawcuwateStuttewEfficiency_pawams->MinTTUVBwank = wocaws->MinTTUVBwank;
	CawcuwateStuttewEfficiency_pawams->DPPPewSuwface = mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface;
	CawcuwateStuttewEfficiency_pawams->DETBuffewSizeY = wocaws->DETBuffewSizeY;
	CawcuwateStuttewEfficiency_pawams->BytePewPixewY = wocaws->BytePewPixewY;
	CawcuwateStuttewEfficiency_pawams->BytePewPixewDETY = wocaws->BytePewPixewDETY;
	CawcuwateStuttewEfficiency_pawams->SwathWidthY = wocaws->SwathWidthY;
	CawcuwateStuttewEfficiency_pawams->SwathHeightY = wocaws->SwathHeightY;
	CawcuwateStuttewEfficiency_pawams->SwathHeightC = wocaws->SwathHeightC;
	CawcuwateStuttewEfficiency_pawams->NetDCCWateWuma = mode_wib->ms.cache_dispway_cfg.suwface.DCCWateWuma;
	CawcuwateStuttewEfficiency_pawams->NetDCCWateChwoma = mode_wib->ms.cache_dispway_cfg.suwface.DCCWateChwoma;
	CawcuwateStuttewEfficiency_pawams->DCCFwactionOfZewoSizeWequestsWuma = mode_wib->ms.cache_dispway_cfg.suwface.DCCFwactionOfZewoSizeWequestsWuma;
	CawcuwateStuttewEfficiency_pawams->DCCFwactionOfZewoSizeWequestsChwoma = mode_wib->ms.cache_dispway_cfg.suwface.DCCFwactionOfZewoSizeWequestsChwoma;
	CawcuwateStuttewEfficiency_pawams->HTotaw = mode_wib->ms.cache_dispway_cfg.timing.HTotaw;
	CawcuwateStuttewEfficiency_pawams->VTotaw = mode_wib->ms.cache_dispway_cfg.timing.VTotaw;
	CawcuwateStuttewEfficiency_pawams->PixewCwock = mode_wib->ms.cache_dispway_cfg.timing.PixewCwock;
	CawcuwateStuttewEfficiency_pawams->VWatio = mode_wib->ms.cache_dispway_cfg.pwane.VWatio;
	CawcuwateStuttewEfficiency_pawams->SouwceScan = mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan;
	CawcuwateStuttewEfficiency_pawams->BwockHeight256BytesY = wocaws->BwockHeight256BytesY;
	CawcuwateStuttewEfficiency_pawams->BwockWidth256BytesY = wocaws->BwockWidth256BytesY;
	CawcuwateStuttewEfficiency_pawams->BwockHeight256BytesC = wocaws->BwockHeight256BytesC;
	CawcuwateStuttewEfficiency_pawams->BwockWidth256BytesC = wocaws->BwockWidth256BytesC;
	CawcuwateStuttewEfficiency_pawams->DCCYMaxUncompwessedBwock = wocaws->DCCYMaxUncompwessedBwock;
	CawcuwateStuttewEfficiency_pawams->DCCCMaxUncompwessedBwock = wocaws->DCCCMaxUncompwessedBwock;
	CawcuwateStuttewEfficiency_pawams->VActive = mode_wib->ms.cache_dispway_cfg.timing.VActive;
	CawcuwateStuttewEfficiency_pawams->DCCEnabwe = mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe;
	CawcuwateStuttewEfficiency_pawams->WwitebackEnabwe = mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe;
	CawcuwateStuttewEfficiency_pawams->WeadBandwidthSuwfaceWuma = wocaws->WeadBandwidthSuwfaceWuma;
	CawcuwateStuttewEfficiency_pawams->WeadBandwidthSuwfaceChwoma = wocaws->WeadBandwidthSuwfaceChwoma;
	CawcuwateStuttewEfficiency_pawams->meta_wow_bw = wocaws->meta_wow_bw;
	CawcuwateStuttewEfficiency_pawams->dpte_wow_bw = wocaws->dpte_wow_bw;
	CawcuwateStuttewEfficiency_pawams->StuttewEfficiencyNotIncwudingVBwank = &wocaws->StuttewEfficiencyNotIncwudingVBwank;
	CawcuwateStuttewEfficiency_pawams->StuttewEfficiency = &wocaws->StuttewEfficiency;
	CawcuwateStuttewEfficiency_pawams->NumbewOfStuttewBuwstsPewFwame = &wocaws->NumbewOfStuttewBuwstsPewFwame;
	CawcuwateStuttewEfficiency_pawams->Z8StuttewEfficiencyNotIncwudingVBwank = &wocaws->Z8StuttewEfficiencyNotIncwudingVBwank;
	CawcuwateStuttewEfficiency_pawams->Z8StuttewEfficiency = &wocaws->Z8StuttewEfficiency;
	CawcuwateStuttewEfficiency_pawams->Z8NumbewOfStuttewBuwstsPewFwame = &wocaws->Z8NumbewOfStuttewBuwstsPewFwame;
	CawcuwateStuttewEfficiency_pawams->StuttewPewiod = &wocaws->StuttewPewiod;
	CawcuwateStuttewEfficiency_pawams->DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE = &wocaws->DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE;

	// Stuttew Efficiency
	CawcuwateStuttewEfficiency(&mode_wib->scwatch,
		CawcuwateStuttewEfficiency_pawams);

#ifdef __DMW_VBA_AWWOW_DEWTA__
	{
	dmw_fwoat_t dummy_singwe[2];
	dmw_uint_t dummy_integew[1];
	dmw_boow_t dummy_boowean[1];

	// Cawcuwate z8 stuttew eff assuming 0 wesewved space
	CawcuwateStuttewEfficiency(
			wocaws->CompwessedBuffewSizeInkByte,
			mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange,
			wocaws->UnboundedWequestEnabwed,
			mode_wib->ms.ip.meta_fifo_size_in_kentwies,
			mode_wib->ms.ip.zewo_size_buffew_entwies,
			mode_wib->ms.ip.pixew_chunk_size_kbytes,
			mode_wib->ms.num_active_pwanes,
			mode_wib->ms.ip.wob_buffew_size_kbytes,
			wocaws->TotawDataWeadBandwidth,
			wocaws->Dcfcwk,
			mode_wib->ms.WetuwnBW,
			0, //mode_wib->ms.ip.compbuf_wesewved_space_64b,
			0, //mode_wib->ms.ip.compbuf_wesewved_space_zs,
			mode_wib->ms.state.sw_exit_time_us,
			mode_wib->ms.state.sw_exit_z8_time_us,
			mode_wib->ms.powicy.SynchwonizeTimingsFinaw,
			mode_wib->ms.cache_dispway_cfg.pwane.BwendingAndTiming,
			wocaws->Watewmawk.StuttewEntewPwusExitWatewmawk,
			wocaws->Watewmawk.Z8StuttewEntewPwusExitWatewmawk,
			mode_wib->ms.ip.ptoi_suppowted,
			mode_wib->ms.cache_dispway_cfg.timing.Intewwace,
			wocaws->MinTTUVBwank,
			mode_wib->ms.cache_dispway_cfg.hw.DPPPewSuwface,
			mode_wib->ms.DETBuffewSizeY,
			wocaws->BytePewPixewY,
			wocaws->BytePewPixewDETY,
			wocaws->SwathWidthY,
			mode_wib->ms.SwathHeightY,
			mode_wib->ms.SwathHeightC,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCWateWuma,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCWateChwoma,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCFwactionOfZewoSizeWequestsWuma,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCFwactionOfZewoSizeWequestsChwoma,
			mode_wib->ms.cache_dispway_cfg.timing.HTotaw,
			mode_wib->ms.cache_dispway_cfg.timing.VTotaw,
			mode_wib->ms.cache_dispway_cfg.timing.PixewCwock,
			mode_wib->ms.cache_dispway_cfg.pwane.VWatio,
			mode_wib->ms.cache_dispway_cfg.pwane.SouwceScan,
			wocaws->BwockHeight256BytesY,
			wocaws->BwockWidth256BytesY,
			wocaws->BwockHeight256BytesC,
			wocaws->BwockWidth256BytesC,
			wocaws->DCCYMaxUncompwessedBwock,
			wocaws->DCCCMaxUncompwessedBwock,
			mode_wib->ms.cache_dispway_cfg.timing.VActive,
			mode_wib->ms.cache_dispway_cfg.suwface.DCCEnabwe,
			mode_wib->ms.cache_dispway_cfg.wwiteback.WwitebackEnabwe,
			wocaws->WeadBandwidthSuwfaceWuma,
			wocaws->WeadBandwidthSuwfaceChwoma,
			wocaws->meta_wow_bw,
			wocaws->dpte_wow_bw,

			/* Output */
			&dummy_singwe[0],
			&dummy_singwe[1],
			&dummy_integew[0],
			&wocaws->Z8StuttewEfficiencyNotIncwudingVBwankBestCase,
			&wocaws->Z8StuttewEfficiencyBestCase,
			&wocaws->Z8NumbewOfStuttewBuwstsPewFwameBestCase,
			&wocaws->StuttewPewiodBestCase,
			&dummy_boowean[0]);
	}
#ewse
	wocaws->Z8StuttewEfficiencyNotIncwudingVBwankBestCase = wocaws->Z8StuttewEfficiencyNotIncwudingVBwank;
	wocaws->Z8StuttewEfficiencyBestCase                   = wocaws->Z8StuttewEfficiency;
	wocaws->Z8NumbewOfStuttewBuwstsPewFwameBestCase       = wocaws->Z8NumbewOfStuttewBuwstsPewFwame;
	wocaws->StuttewPewiodBestCase                         = wocaws->StuttewPewiod;
#endif

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: --- END --- \n",  __func__);
#endif
} // dmw_cowe_mode_pwogwamming

/// Function: dmw_cowe_get_wow_heights
/// @bwief Get wow height fow DPTE and META with minimaw input.
void dmw_cowe_get_wow_heights(
						dmw_uint_t                         *dpte_wow_height,
						dmw_uint_t                         *meta_wow_height,
						const stwuct dispway_mode_wib_st   *mode_wib,
						dmw_boow_t                         is_pwane1,
						enum dmw_souwce_fowmat_cwass        SouwcePixewFowmat,
						enum dmw_swizzwe_mode            SuwfaceTiwing,
						enum dmw_wotation_angwe          ScanDiwection,
						dmw_uint_t                         pitch,
						dmw_uint_t                         GPUVMMinPageSizeKBytes)
{
	dmw_uint_t BytePewPixewY;
	dmw_uint_t BytePewPixewC;
	dmw_fwoat_t BytePewPixewInDETY;
	dmw_fwoat_t BytePewPixewInDETC;
	dmw_uint_t BwockHeight256BytesY;
	dmw_uint_t BwockHeight256BytesC;
	dmw_uint_t BwockWidth256BytesY;
	dmw_uint_t BwockWidth256BytesC;
	dmw_uint_t MacwoTiweWidthY;
	dmw_uint_t MacwoTiweWidthC;
	dmw_uint_t MacwoTiweHeightY;
	dmw_uint_t MacwoTiweHeightC;

	dmw_uint_t BytePewPixew;
	dmw_uint_t BwockHeight256Bytes;
	dmw_uint_t BwockWidth256Bytes;
	dmw_uint_t MacwoTiweWidth;
	dmw_uint_t MacwoTiweHeight;
	dmw_uint_t PTEBuffewSizeInWequests;

	dmw_uint_t dummy_integew[16];

	CawcuwateBytePewPixewAndBwockSizes(
		SouwcePixewFowmat,
		SuwfaceTiwing,

		/* Output */
		&BytePewPixewY,
		&BytePewPixewC,
		&BytePewPixewInDETY,
		&BytePewPixewInDETC,
		&BwockHeight256BytesY,
		&BwockHeight256BytesC,
		&BwockWidth256BytesY,
		&BwockWidth256BytesC,
		&MacwoTiweHeightY,
		&MacwoTiweHeightC,
		&MacwoTiweWidthY,
		&MacwoTiweWidthC);

	BytePewPixew = is_pwane1 ? BytePewPixewC : BytePewPixewY;
	BwockHeight256Bytes = is_pwane1 ? BwockHeight256BytesC : BwockHeight256BytesY;
	BwockWidth256Bytes = is_pwane1 ? BwockWidth256BytesC : BwockWidth256BytesY;
	MacwoTiweWidth = is_pwane1 ? MacwoTiweWidthC : MacwoTiweWidthY;
	MacwoTiweHeight = is_pwane1 ? MacwoTiweHeightC : MacwoTiweHeightY;
	PTEBuffewSizeInWequests = is_pwane1 ? mode_wib->ip.dpte_buffew_size_in_pte_weqs_chwoma : mode_wib->ip.dpte_buffew_size_in_pte_weqs_wuma;
#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: is_pwane1 = %u\n", __func__, is_pwane1);
	dmw_pwint("DMW_DWG: %s: BytePewPixew = %u\n", __func__, BytePewPixew);
	dmw_pwint("DMW_DWG: %s: BwockHeight256Bytes = %u\n", __func__, BwockHeight256Bytes);
	dmw_pwint("DMW_DWG: %s: BwockWidth256Bytes = %u\n", __func__, BwockWidth256Bytes);
	dmw_pwint("DMW_DWG: %s: MacwoTiweWidth = %u\n", __func__, MacwoTiweWidth);
	dmw_pwint("DMW_DWG: %s: MacwoTiweHeight = %u\n", __func__, MacwoTiweHeight);
	dmw_pwint("DMW_DWG: %s: PTEBuffewSizeInWequests = %u\n", __func__, PTEBuffewSizeInWequests);
	dmw_pwint("DMW_DWG: %s: dpte_buffew_size_in_pte_weqs_wuma = %u\n", __func__, mode_wib->ip.dpte_buffew_size_in_pte_weqs_wuma);
	dmw_pwint("DMW_DWG: %s: dpte_buffew_size_in_pte_weqs_chwoma = %u\n", __func__, mode_wib->ip.dpte_buffew_size_in_pte_weqs_chwoma);
	dmw_pwint("DMW_DWG: %s: GPUVMMinPageSizeKBytes = %u\n", __func__, GPUVMMinPageSizeKBytes);
#endif

	// just suppwuy with enough pawametews to cawcuwate meta and dte
	CawcuwateVMAndWowBytes(
			0, // dmw_boow_t ViewpowtStationawy,
			1, // dmw_boow_t DCCEnabwe,
			1, // dmw_uint_t NumbewOfDPPs,
			BwockHeight256Bytes,
			BwockWidth256Bytes,
			SouwcePixewFowmat,
			SuwfaceTiwing,
			BytePewPixew,
			ScanDiwection,
			0, // dmw_uint_t SwathWidth,
			0, // dmw_uint_t ViewpowtHeight, (Note: DMW cawcuwates one_wow_fow_fwame height wegawdwess, wouwd need test input if that height is usefuw)
			0, // dmw_uint_t ViewpowtXStawt,
			0, // dmw_uint_t ViewpowtYStawt,
			1, // dmw_boow_t GPUVMEnabwe,
			4, // dmw_uint_t GPUVMMaxPageTabweWevews,
			GPUVMMinPageSizeKBytes,
			PTEBuffewSizeInWequests,
			pitch,
			0, // dmw_uint_t DCCMetaPitch,
			MacwoTiweWidth,
			MacwoTiweHeight,

			// /* Output */
			&dummy_integew[0], // dmw_uint_t *MetaWowByte,
			&dummy_integew[1], // dmw_uint_t *PixewPTEBytesPewWow,
			&dummy_integew[2], // dmw_uint_t *PixewPTEBytesPewWowStowage,
			&dummy_integew[3], // dmw_uint_t *dpte_wow_width_ub,
			dpte_wow_height,
			&dummy_integew[4], // dmw_uint_t *dpte_wow_height_wineaw
			&dummy_integew[5], // dmw_uint_t *PixewPTEBytesPewWow_one_wow_pew_fwame,
			&dummy_integew[6], // dmw_uint_t *dpte_wow_width_ub_one_wow_pew_fwame,
			&dummy_integew[7], // dmw_uint_t *dpte_wow_height_one_wow_pew_fwame,
			&dummy_integew[8], // dmw_uint_t *MetaWequestWidth,
			&dummy_integew[9], // dmw_uint_t *MetaWequestHeight,
			&dummy_integew[10], // dmw_uint_t *meta_wow_width,
			meta_wow_height,
			&dummy_integew[11], // dmw_uint_t *PixewPTEWeqWidth,
			&dummy_integew[12], // dmw_uint_t *PixewPTEWeqHeight,
			&dummy_integew[13], // dmw_uint_t *PTEWequestSize,
			&dummy_integew[14], // dmw_uint_t *DPDE0BytesFwame,
			&dummy_integew[15]); // dmw_uint_t *MetaPTEBytesFwame)

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: dpte_wow_height = %u\n", __func__, *dpte_wow_height);
	dmw_pwint("DMW_DWG: %s: meta_wow_height = %u\n", __func__, *meta_wow_height);
#endif
}

static stwuct soc_state_bounding_box_st dmw_get_soc_state_bounding_box(
	const stwuct soc_states_st *states,
	dmw_uint_t state_idx)
{
	dmw_pwint("DMW::%s: state_idx=%u (num_states=%u)\n", __func__, state_idx, states->num_states);

	if (state_idx >= (dmw_uint_t)states->num_states) {
		dmw_pwint("DMW::%s: EWWOW: Invawid state_idx=%u! num_states=%u\n", __func__, state_idx, states->num_states);
		ASSEWT(0);
	}
	wetuwn (states->state_awway[state_idx]);
}

/// @bwief Copy the pawametews to a cawcuwation stwuct, it actuawwy onwy need when the DMW needs to have
///        the intewwigence to we-cawcuwate when any of dispway cfg, bbox, ow powicy changes since wast cawcuwated.
///
static void cache_ip_soc_cfg(stwuct dispway_mode_wib_st *mode_wib,
						dmw_uint_t state_idx)
{
	mode_wib->ms.state_idx = state_idx;
	mode_wib->ms.max_state_idx = mode_wib->states.num_states - 1;
	mode_wib->ms.soc = mode_wib->soc;
	mode_wib->ms.ip = mode_wib->ip;
	mode_wib->ms.powicy = mode_wib->powicy;
	mode_wib->ms.state = dmw_get_soc_state_bounding_box(&mode_wib->states, state_idx);
	mode_wib->ms.max_state = dmw_get_soc_state_bounding_box(&mode_wib->states, mode_wib->states.num_states - 1);
}

static void cache_dispway_cfg(stwuct dispway_mode_wib_st *mode_wib,
	const stwuct dmw_dispway_cfg_st *dispway_cfg)
{
	mode_wib->ms.cache_dispway_cfg = *dispway_cfg;
}

static void fetch_socbb_pawams(stwuct dispway_mode_wib_st *mode_wib)
{
	stwuct soc_state_bounding_box_st *state = &mode_wib->ms.state;

	// Defauwt vawues, SOCCWK, DWAMSpeed, and FabwicCwock wiww be weassigned to the same state vawue in mode_check step
	// If UseMinimumWequiwedDCFCWK is used, the DCFCWK wiww be the min dcfwk fow the mode suppowt
	mode_wib->ms.SOCCWK = (dmw_fwoat_t)state->soccwk_mhz;
	mode_wib->ms.DWAMSpeed = (dmw_fwoat_t)state->dwam_speed_mts;
	mode_wib->ms.FabwicCwock = (dmw_fwoat_t)state->fabwiccwk_mhz;
	mode_wib->ms.DCFCWK = (dmw_fwoat_t)state->dcfcwk_mhz;
}

/// @bwief Use dispway_cfg diwectwy fow mode_suppowt cawcuwation
///        Cawcuwated vawues and infowmationaw output awe stowed in mode_wib.vba data stwuct
///        The dispway configuwation is descwibed with pipes stwuct and num_pipes
///        This function is used when physicaw wesouwce mapping is not finawized (fow exampwe,
///        don't know how many pipes to wepwesent a suwface)
/// @pawam mode_wib Contains the bounding box and powicy setting.
/// @pawam state_idx Powew state index
/// @pawam dispway_cfg Dispway configuwations. A dispway
dmw_boow_t dmw_mode_suppowt(
	stwuct dispway_mode_wib_st *mode_wib,
	dmw_uint_t                        state_idx,
	const stwuct dmw_dispway_cfg_st *dispway_cfg)
{
	dmw_boow_t is_mode_suppowt;

	dmw_pwint("DMW::%s: ------------- STAWT ----------\n", __func__);
	cache_ip_soc_cfg(mode_wib, state_idx);
	cache_dispway_cfg(mode_wib, dispway_cfg);

	fetch_socbb_pawams(mode_wib);

	dmw_pwint("DMW::%s: state_idx          = %u\n", __func__, state_idx);

	is_mode_suppowt = dmw_cowe_mode_suppowt(mode_wib);

	dmw_pwint("DMW::%s: is_mode_suppowt = %u\n", __func__, is_mode_suppowt);
	dmw_pwint("DMW::%s: ------------- DONE ----------\n", __func__);
	wetuwn is_mode_suppowt;
}

/// @Bwief A function to cawcuwate the pwogwamming vawues fow DCN DCHUB (Assume mode is suppowted)
/// The output wiww be stowed in the mode_wib.mp (mode_pwogwam_st) data stwuct and those can be accessed via the gettew functions
/// Cawcuwated vawues incwude: watewmawks, dwg, wq weg, diffewent cwock fwequency
/// This function wetuwns 1 when thewe is no ewwow.
/// Note: In this function, it is assumed that DCFCWK, SOCCWK fweq awe the state vawues, and mode_pwogwam wiww just use the DMW cawcuwated DPPCWK and DISPCWK
/// @pawam mode_wib mode_wib data stwuct that house aww the input/output/bbox and cawcuwation vawues.
/// @pawam state_idx Powew state idx chosen
/// @pawam dispway_cfg Dispway Congiuwation
/// @pawam caww_standawone Cawwing mode_pwogwamming without cawwing mode suppowt.  Some of the "suppowt" stwuct membew wiww be pwe-cawcuwated befowe doing mode pwogwamming
/// TODO: Add cwk_cfg input, couwd be usefuw fow standawone mode
dmw_boow_t dmw_mode_pwogwamming(
	stwuct dispway_mode_wib_st *mode_wib,
	dmw_uint_t                         state_idx,
	const stwuct dmw_dispway_cfg_st *dispway_cfg,
	boow                               caww_standawone)
{
	stwuct dmw_cwk_cfg_st cwk_cfg;
	memset(&cwk_cfg, 0, sizeof(cwk_cfg));

	cwk_cfg.dcfcwk_option = dmw_use_wequiwed_fweq;
	cwk_cfg.dispcwk_option = dmw_use_wequiwed_fweq;
	fow (dmw_uint_t k = 0; k < __DMW_NUM_PWANES__; ++k)
		cwk_cfg.dppcwk_option[k] = dmw_use_wequiwed_fweq;

	dmw_pwint("DMW::%s: ------------- STAWT ----------\n", __func__);
	dmw_pwint("DMW::%s: state_idx       = %u\n", __func__, state_idx);
	dmw_pwint("DMW::%s: caww_standawone = %u\n", __func__, caww_standawone);

	cache_ip_soc_cfg(mode_wib, state_idx);
	cache_dispway_cfg(mode_wib, dispway_cfg);

	fetch_socbb_pawams(mode_wib);
	if (caww_standawone) {
		mode_wib->ms.suppowt.ImmediateFwipSuppowt = 1; // assume mode suppowt say immediate fwip ok at max state/combine
		dmw_cowe_mode_suppowt_pawtiaw(mode_wib);
	}

	dmw_cowe_mode_pwogwamming(mode_wib, &cwk_cfg);

	dmw_pwint("DMW::%s: ------------- DONE ----------\n", __func__);
	dmw_pwint("DMW::%s: PwefetchAndImmediateFwipSuppowted = %0d\n", __func__, mode_wib->mp.PwefetchAndImmediateFwipSuppowted);
	wetuwn mode_wib->mp.PwefetchAndImmediateFwipSuppowted;
}

static dmw_uint_t mode_suppowt_pww_states(
	dmw_uint_t *wowest_state_idx,
	stwuct dispway_mode_wib_st *mode_wib,
	const stwuct dmw_dispway_cfg_st *dispway_cfg,
	dmw_uint_t stawt_state_idx,
	dmw_uint_t end_state_idx)
{
	dmw_uint_t state_idx = 0;
	dmw_boow_t mode_is_suppowted = 0;
	*wowest_state_idx = end_state_idx;

	if (end_state_idx < stawt_state_idx)
		ASSEWT(0);

	if (end_state_idx >= mode_wib->states.num_states) // idx is 0-based
		ASSEWT(0);

	fow (state_idx = stawt_state_idx; state_idx <= end_state_idx; state_idx++) {
		if (dmw_mode_suppowt(mode_wib, state_idx, dispway_cfg)) {
			dmw_pwint("DMW::%s: Mode is suppowted at powew state_idx = %u\n", __func__, state_idx);
			mode_is_suppowted = 1;
			*wowest_state_idx = state_idx;
			bweak;
		}
	}

	wetuwn mode_is_suppowted;
}

dmw_uint_t dmw_mode_suppowt_ex(stwuct dmw_mode_suppowt_ex_pawams_st *in_out_pawams)
{
	dmw_uint_t wesuwt;

	wesuwt = mode_suppowt_pww_states(&in_out_pawams->out_wowest_state_idx,
		in_out_pawams->mode_wib,
		in_out_pawams->in_dispway_cfg,
		0,
		in_out_pawams->mode_wib->states.num_states - 1);

	if (wesuwt)
		*in_out_pawams->out_evawuation_info = in_out_pawams->mode_wib->ms.suppowt;

	wetuwn wesuwt;
}

dmw_boow_t dmw_get_is_phantom_pipe(stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t pipe_idx)
{
	dmw_uint_t pwane_idx = mode_wib->mp.pipe_pwane[pipe_idx];
	dmw_pwint("DMW::%s: pipe_idx=%d UseMAWWFowPStateChange=%0d\n", __func__, pipe_idx, mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[pwane_idx]);
	wetuwn (mode_wib->ms.cache_dispway_cfg.pwane.UseMAWWFowPStateChange[pwane_idx] == dmw_use_maww_pstate_change_phantom_pipe);
}

#define dmw_get_pew_suwface_vaw_func(vawiabwe, type, intewvaw_vaw) type dmw_get_##vawiabwe(stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t suwface_idx) \
{ \
	dmw_uint_t pwane_idx; \
	pwane_idx = mode_wib->mp.pipe_pwane[suwface_idx]; \
	wetuwn (type) intewvaw_vaw[pwane_idx]; \
}

#define dmw_get_vaw_func(vaw, type, intewnaw_vaw)  type dmw_get_##vaw(stwuct dispway_mode_wib_st *mode_wib) \
{ \
	wetuwn (type) intewnaw_vaw; \
}

dmw_get_vaw_func(wm_uwgent, dmw_fwoat_t, mode_wib->mp.Watewmawk.UwgentWatewmawk);
dmw_get_vaw_func(wm_stuttew_exit, dmw_fwoat_t, mode_wib->mp.Watewmawk.StuttewExitWatewmawk);
dmw_get_vaw_func(wm_stuttew_entew_exit, dmw_fwoat_t, mode_wib->mp.Watewmawk.StuttewEntewPwusExitWatewmawk);
dmw_get_vaw_func(wm_memowy_twip, dmw_fwoat_t, mode_wib->mp.UwgentWatency);
dmw_get_vaw_func(wm_fcwk_change, dmw_fwoat_t, mode_wib->mp.Watewmawk.FCWKChangeWatewmawk);
dmw_get_vaw_func(wm_usw_wetwaining, dmw_fwoat_t, mode_wib->mp.Watewmawk.USWWetwainingWatewmawk);
dmw_get_vaw_func(wm_dwam_cwock_change, dmw_fwoat_t, mode_wib->mp.Watewmawk.DWAMCwockChangeWatewmawk);
dmw_get_vaw_func(wm_z8_stuttew_entew_exit, dmw_fwoat_t, mode_wib->mp.Watewmawk.Z8StuttewEntewPwusExitWatewmawk);
dmw_get_vaw_func(wm_z8_stuttew, dmw_fwoat_t, mode_wib->mp.Watewmawk.Z8StuttewExitWatewmawk);
dmw_get_vaw_func(fwaction_of_uwgent_bandwidth, dmw_fwoat_t, mode_wib->mp.FwactionOfUwgentBandwidth);
dmw_get_vaw_func(fwaction_of_uwgent_bandwidth_imm_fwip, dmw_fwoat_t, mode_wib->mp.FwactionOfUwgentBandwidthImmediateFwip);
dmw_get_vaw_func(uwgent_watency, dmw_fwoat_t, mode_wib->mp.UwgentWatency);
dmw_get_vaw_func(cwk_dcf_deepsweep, dmw_fwoat_t, mode_wib->mp.DCFCWKDeepSweep);
dmw_get_vaw_func(wm_wwiteback_dwam_cwock_change, dmw_fwoat_t, mode_wib->mp.Watewmawk.WwitebackDWAMCwockChangeWatewmawk);
dmw_get_vaw_func(stuttew_efficiency, dmw_fwoat_t, mode_wib->mp.StuttewEfficiency);
dmw_get_vaw_func(stuttew_efficiency_no_vbwank, dmw_fwoat_t, mode_wib->mp.StuttewEfficiencyNotIncwudingVBwank);
dmw_get_vaw_func(stuttew_efficiency_z8, dmw_fwoat_t, mode_wib->mp.Z8StuttewEfficiency);
dmw_get_vaw_func(stuttew_num_buwsts_z8, dmw_fwoat_t, mode_wib->mp.Z8NumbewOfStuttewBuwstsPewFwame);
dmw_get_vaw_func(stuttew_pewiod, dmw_fwoat_t, mode_wib->mp.StuttewPewiod);
dmw_get_vaw_func(stuttew_efficiency_z8_bestcase, dmw_fwoat_t, mode_wib->mp.Z8StuttewEfficiencyBestCase);
dmw_get_vaw_func(stuttew_num_buwsts_z8_bestcase, dmw_fwoat_t, mode_wib->mp.Z8NumbewOfStuttewBuwstsPewFwameBestCase);
dmw_get_vaw_func(stuttew_pewiod_bestcase, dmw_fwoat_t, mode_wib->mp.StuttewPewiodBestCase);
dmw_get_vaw_func(uwgent_extwa_watency, dmw_fwoat_t, mode_wib->mp.UwgentExtwaWatency);
dmw_get_vaw_func(dispcwk_cawcuwated, dmw_fwoat_t, mode_wib->mp.Dispcwk_cawcuwated);
dmw_get_vaw_func(totaw_data_wead_bw, dmw_fwoat_t, mode_wib->mp.TotawDataWeadBandwidth);
dmw_get_vaw_func(wetuwn_bw, dmw_fwoat_t, mode_wib->ms.WetuwnBW);
dmw_get_vaw_func(tcawc, dmw_fwoat_t, mode_wib->mp.TCawc);
dmw_get_vaw_func(comp_buffew_size_kbytes, dmw_uint_t, mode_wib->mp.CompwessedBuffewSizeInkByte);
dmw_get_vaw_func(pixew_chunk_size_in_kbyte, dmw_uint_t, mode_wib->ms.ip.pixew_chunk_size_kbytes);
dmw_get_vaw_func(awpha_pixew_chunk_size_in_kbyte, dmw_uint_t, mode_wib->ms.ip.awpha_pixew_chunk_size_kbytes);
dmw_get_vaw_func(meta_chunk_size_in_kbyte, dmw_uint_t, mode_wib->ms.ip.meta_chunk_size_kbytes);
dmw_get_vaw_func(min_pixew_chunk_size_in_byte, dmw_uint_t, mode_wib->ms.ip.min_pixew_chunk_size_bytes);
dmw_get_vaw_func(min_meta_chunk_size_in_byte, dmw_uint_t, mode_wib->ms.ip.min_meta_chunk_size_bytes);
dmw_get_vaw_func(totaw_immediate_fwip_bytes, dmw_uint_t, mode_wib->mp.TotImmediateFwipBytes);

dmw_get_pew_suwface_vaw_func(dsc_deway, dmw_uint_t, mode_wib->mp.DSCDeway); // this is the dsc watency
dmw_get_pew_suwface_vaw_func(dppcwk_cawcuwated, dmw_fwoat_t, mode_wib->mp.Dppcwk_cawcuwated);
dmw_get_pew_suwface_vaw_func(dsccwk_cawcuwated, dmw_fwoat_t, mode_wib->mp.DSCCWK_cawcuwated);
dmw_get_pew_suwface_vaw_func(min_ttu_vbwank_in_us, dmw_fwoat_t, mode_wib->mp.MinTTUVBwank);
dmw_get_pew_suwface_vaw_func(vwatio_pwefetch_w, dmw_fwoat_t, mode_wib->mp.VWatioPwefetchY);
dmw_get_pew_suwface_vaw_func(vwatio_pwefetch_c, dmw_fwoat_t, mode_wib->mp.VWatioPwefetchC);
dmw_get_pew_suwface_vaw_func(dst_x_aftew_scawew, dmw_uint_t, mode_wib->mp.DSTXAftewScawew);
dmw_get_pew_suwface_vaw_func(dst_y_aftew_scawew, dmw_uint_t, mode_wib->mp.DSTYAftewScawew);
dmw_get_pew_suwface_vaw_func(dst_y_pew_vm_vbwank, dmw_fwoat_t, mode_wib->mp.DestinationWinesToWequestVMInVBwank);
dmw_get_pew_suwface_vaw_func(dst_y_pew_wow_vbwank, dmw_fwoat_t, mode_wib->mp.DestinationWinesToWequestWowInVBwank);
dmw_get_pew_suwface_vaw_func(dst_y_pwefetch, dmw_fwoat_t, mode_wib->mp.DestinationWinesFowPwefetch);
dmw_get_pew_suwface_vaw_func(dst_y_pew_vm_fwip, dmw_fwoat_t, mode_wib->mp.DestinationWinesToWequestVMInImmediateFwip);
dmw_get_pew_suwface_vaw_func(dst_y_pew_wow_fwip, dmw_fwoat_t, mode_wib->mp.DestinationWinesToWequestWowInImmediateFwip);
dmw_get_pew_suwface_vaw_func(dst_y_pew_pte_wow_nom_w, dmw_fwoat_t, mode_wib->mp.DST_Y_PEW_PTE_WOW_NOM_W);
dmw_get_pew_suwface_vaw_func(dst_y_pew_pte_wow_nom_c, dmw_fwoat_t, mode_wib->mp.DST_Y_PEW_PTE_WOW_NOM_C);
dmw_get_pew_suwface_vaw_func(dst_y_pew_meta_wow_nom_w, dmw_fwoat_t, mode_wib->mp.DST_Y_PEW_META_WOW_NOM_W);
dmw_get_pew_suwface_vaw_func(dst_y_pew_meta_wow_nom_c, dmw_fwoat_t, mode_wib->mp.DST_Y_PEW_META_WOW_NOM_C);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_vm_gwoup_vbwank_in_us, dmw_fwoat_t, mode_wib->mp.TimePewVMGwoupVBwank);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_vm_gwoup_fwip_in_us, dmw_fwoat_t, mode_wib->mp.TimePewVMGwoupFwip);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_vm_weq_vbwank_in_us, dmw_fwoat_t, mode_wib->mp.TimePewVMWequestVBwank);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_vm_weq_fwip_in_us, dmw_fwoat_t, mode_wib->mp.TimePewVMWequestFwip);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_vm_dmdata_in_us, dmw_fwoat_t, mode_wib->mp.Tdmdw_vm);
dmw_get_pew_suwface_vaw_func(dmdata_dw_dewta_in_us, dmw_fwoat_t, mode_wib->mp.Tdmdw);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_wine_dewivewy_w_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWineDewivewyTimeWuma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_wine_dewivewy_c_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWineDewivewyTimeChwoma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_wine_dewivewy_pwe_w_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWineDewivewyTimeWumaPwefetch);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_wine_dewivewy_pwe_c_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWineDewivewyTimeChwomaPwefetch);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_weq_dewivewy_w_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWequestDewivewyTimeWuma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_weq_dewivewy_c_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWequestDewivewyTimeChwoma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_weq_dewivewy_pwe_w_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWequestDewivewyTimeWumaPwefetch);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_weq_dewivewy_pwe_c_in_us, dmw_fwoat_t, mode_wib->mp.DispwayPipeWequestDewivewyTimeChwomaPwefetch);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_cuwsow_weq_dewivewy_in_us, dmw_fwoat_t, mode_wib->mp.CuwsowWequestDewivewyTime);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_cuwsow_weq_dewivewy_pwe_in_us, dmw_fwoat_t, mode_wib->mp.CuwsowWequestDewivewyTimePwefetch);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_meta_chunk_nom_w_in_us, dmw_fwoat_t, mode_wib->mp.TimePewMetaChunkNominaw);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_meta_chunk_nom_c_in_us, dmw_fwoat_t, mode_wib->mp.TimePewChwomaMetaChunkNominaw);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_meta_chunk_vbwank_w_in_us, dmw_fwoat_t, mode_wib->mp.TimePewMetaChunkVBwank);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_meta_chunk_vbwank_c_in_us, dmw_fwoat_t, mode_wib->mp.TimePewChwomaMetaChunkVBwank);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_meta_chunk_fwip_w_in_us, dmw_fwoat_t, mode_wib->mp.TimePewMetaChunkFwip);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_meta_chunk_fwip_c_in_us, dmw_fwoat_t, mode_wib->mp.TimePewChwomaMetaChunkFwip);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_pte_gwoup_nom_w_in_us, dmw_fwoat_t, mode_wib->mp.time_pew_pte_gwoup_nom_wuma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_pte_gwoup_nom_c_in_us, dmw_fwoat_t, mode_wib->mp.time_pew_pte_gwoup_nom_chwoma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_pte_gwoup_vbwank_w_in_us, dmw_fwoat_t, mode_wib->mp.time_pew_pte_gwoup_vbwank_wuma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_pte_gwoup_vbwank_c_in_us, dmw_fwoat_t, mode_wib->mp.time_pew_pte_gwoup_vbwank_chwoma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_pte_gwoup_fwip_w_in_us, dmw_fwoat_t, mode_wib->mp.time_pew_pte_gwoup_fwip_wuma);
dmw_get_pew_suwface_vaw_func(wefcyc_pew_pte_gwoup_fwip_c_in_us, dmw_fwoat_t, mode_wib->mp.time_pew_pte_gwoup_fwip_chwoma);
dmw_get_pew_suwface_vaw_func(dpte_gwoup_size_in_bytes, dmw_uint_t, mode_wib->mp.dpte_gwoup_bytes);
dmw_get_pew_suwface_vaw_func(vm_gwoup_size_in_bytes, dmw_uint_t, mode_wib->mp.vm_gwoup_bytes);
dmw_get_pew_suwface_vaw_func(swath_height_w, dmw_uint_t, mode_wib->ms.SwathHeightY);
dmw_get_pew_suwface_vaw_func(swath_height_c, dmw_uint_t, mode_wib->ms.SwathHeightC);
dmw_get_pew_suwface_vaw_func(dpte_wow_height_w, dmw_uint_t, mode_wib->mp.dpte_wow_height);
dmw_get_pew_suwface_vaw_func(dpte_wow_height_c, dmw_uint_t, mode_wib->mp.dpte_wow_height_chwoma);
dmw_get_pew_suwface_vaw_func(dpte_wow_height_wineaw_w, dmw_uint_t, mode_wib->mp.dpte_wow_height_wineaw);
dmw_get_pew_suwface_vaw_func(dpte_wow_height_wineaw_c, dmw_uint_t, mode_wib->mp.dpte_wow_height_wineaw_chwoma);
dmw_get_pew_suwface_vaw_func(meta_wow_height_w, dmw_uint_t, mode_wib->mp.meta_wow_height);
dmw_get_pew_suwface_vaw_func(meta_wow_height_c, dmw_uint_t, mode_wib->mp.meta_wow_height_chwoma);

dmw_get_pew_suwface_vaw_func(vstawtup_cawcuwated, dmw_uint_t, mode_wib->mp.VStawtup);
dmw_get_pew_suwface_vaw_func(vupdate_offset, dmw_uint_t, mode_wib->mp.VUpdateOffsetPix);
dmw_get_pew_suwface_vaw_func(vupdate_width, dmw_uint_t, mode_wib->mp.VUpdateWidthPix);
dmw_get_pew_suwface_vaw_func(vweady_offset, dmw_uint_t, mode_wib->mp.VWeadyOffsetPix);
dmw_get_pew_suwface_vaw_func(vweady_at_ow_aftew_vsync, dmw_uint_t, mode_wib->mp.VWEADY_AT_OW_AFTEW_VSYNC);
dmw_get_pew_suwface_vaw_func(min_dst_y_next_stawt, dmw_uint_t, mode_wib->mp.MIN_DST_Y_NEXT_STAWT);
dmw_get_pew_suwface_vaw_func(det_stowed_buffew_size_w_bytes, dmw_uint_t, mode_wib->ms.DETBuffewSizeY);
dmw_get_pew_suwface_vaw_func(det_stowed_buffew_size_c_bytes, dmw_uint_t, mode_wib->ms.DETBuffewSizeC);
dmw_get_pew_suwface_vaw_func(use_maww_fow_static_scween, dmw_uint_t, mode_wib->mp.UsesMAWWFowStaticScween);
dmw_get_pew_suwface_vaw_func(suwface_size_fow_maww, dmw_uint_t, mode_wib->mp.SuwfaceSizeInTheMAWW);
dmw_get_pew_suwface_vaw_func(dcc_max_uncompwessed_bwock_w, dmw_uint_t, mode_wib->mp.DCCYMaxUncompwessedBwock);
dmw_get_pew_suwface_vaw_func(dcc_max_compwessed_bwock_w, dmw_uint_t, mode_wib->mp.DCCYMaxCompwessedBwock);
dmw_get_pew_suwface_vaw_func(dcc_independent_bwock_w, dmw_uint_t, mode_wib->mp.DCCYIndependentBwock);
dmw_get_pew_suwface_vaw_func(dcc_max_uncompwessed_bwock_c, dmw_uint_t, mode_wib->mp.DCCCMaxUncompwessedBwock);
dmw_get_pew_suwface_vaw_func(dcc_max_compwessed_bwock_c, dmw_uint_t, mode_wib->mp.DCCCMaxCompwessedBwock);
dmw_get_pew_suwface_vaw_func(dcc_independent_bwock_c, dmw_uint_t, mode_wib->mp.DCCCIndependentBwock);
dmw_get_pew_suwface_vaw_func(max_active_dwam_cwock_change_watency_suppowted, dmw_uint_t, mode_wib->mp.MaxActiveDWAMCwockChangeWatencySuppowted);
dmw_get_pew_suwface_vaw_func(pte_buffew_mode, dmw_uint_t, mode_wib->mp.PTE_BUFFEW_MODE);
dmw_get_pew_suwface_vaw_func(bigk_fwagment_size, dmw_uint_t, mode_wib->mp.BIGK_FWAGMENT_SIZE);
dmw_get_pew_suwface_vaw_func(dpte_bytes_pew_wow, dmw_uint_t, mode_wib->mp.PixewPTEBytesPewWow);
dmw_get_pew_suwface_vaw_func(meta_bytes_pew_wow, dmw_uint_t, mode_wib->mp.MetaWowByte);
dmw_get_pew_suwface_vaw_func(det_buffew_size_kbytes, dmw_uint_t, mode_wib->ms.DETBuffewSizeInKByte);
