/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __DMW_DCN32_DISPWAY_MODE_VBA_UTIW_32_H__
#define __DMW_DCN32_DISPWAY_MODE_VBA_UTIW_32_H__

#incwude "../dispway_mode_enums.h"
#incwude "os_types.h"
#incwude "../dc_featuwes.h"
#incwude "../dispway_mode_stwucts.h"
#incwude "../dispway_mode_vba.h"

unsigned int dmw32_dscceComputeDeway(
		unsigned int bpc,
		doubwe BPP,
		unsigned int swiceWidth,
		unsigned int numSwices,
		enum output_fowmat_cwass pixewFowmat,
		enum output_encodew_cwass Output);

unsigned int dmw32_dscComputeDeway(enum output_fowmat_cwass pixewFowmat, enum output_encodew_cwass Output);

boow IsVewticaw(enum dm_wotation_angwe Scan);

void dmw32_CawcuwateBytePewPixewAndBwockSizes(
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		enum dm_swizzwe_mode SuwfaceTiwing,

		/*Output*/
		unsigned int *BytePewPixewY,
		unsigned int *BytePewPixewC,
		doubwe           *BytePewPixewDETY,
		doubwe           *BytePewPixewDETC,
		unsigned int *BwockHeight256BytesY,
		unsigned int *BwockHeight256BytesC,
		unsigned int *BwockWidth256BytesY,
		unsigned int *BwockWidth256BytesC,
		unsigned int *MacwoTiweHeightY,
		unsigned int *MacwoTiweHeightC,
		unsigned int *MacwoTiweWidthY,
		unsigned int *MacwoTiweWidthC);

void dmw32_CawcuwateSingwePipeDPPCWKAndSCWThwoughput(
		doubwe HWatio,
		doubwe HWatioChwoma,
		doubwe VWatio,
		doubwe VWatioChwoma,
		doubwe MaxDCHUBToPSCWThwoughput,
		doubwe MaxPSCWToWBThwoughput,
		doubwe PixewCwock,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int HTaps,
		unsigned int HTapsChwoma,
		unsigned int VTaps,
		unsigned int VTapsChwoma,

		/* output */
		doubwe *PSCW_THWOUGHPUT,
		doubwe *PSCW_THWOUGHPUT_CHWOMA,
		doubwe *DPPCWKUsingSingweDPP);

void dmw32_CawcuwateSwathAndDETConfiguwation(
		unsigned int DETSizeOvewwide[],
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
		unsigned int ConfigWetuwnBuffewSizeInKByte,
		unsigned int MaxTotawDETInKByte,
		unsigned int MinCompwessedBuffewSizeInKByte,
		doubwe FowceSingweDPP,
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int nomDETInKByte,
		enum unbounded_wequesting_powicy UseUnboundedWequestingFinaw,
		boow DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment,
		unsigned int PixewChunkSizeKBytes,
		unsigned int WOBSizeKBytes,
		unsigned int CompwessedBuffewSegmentSizeInkByteFinaw,
		enum output_encodew_cwass Output[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		doubwe MaximumSwathWidthWuma[],
		doubwe MaximumSwathWidthChwoma[],
		enum dm_wotation_angwe SouwceWotation[],
		boow ViewpowtStationawy[],
		enum souwce_fowmat_cwass SouwcePixewFowmat[],
		enum dm_swizzwe_mode SuwfaceTiwing[],
		unsigned int ViewpowtWidth[],
		unsigned int ViewpowtHeight[],
		unsigned int ViewpowtXStawt[],
		unsigned int ViewpowtYStawt[],
		unsigned int ViewpowtXStawtC[],
		unsigned int ViewpowtYStawtC[],
		unsigned int SuwfaceWidthY[],
		unsigned int SuwfaceWidthC[],
		unsigned int SuwfaceHeightY[],
		unsigned int SuwfaceHeightC[],
		unsigned int Wead256BytesBwockHeightY[],
		unsigned int Wead256BytesBwockHeightC[],
		unsigned int Wead256BytesBwockWidthY[],
		unsigned int Wead256BytesBwockWidthC[],
		enum odm_combine_mode ODMMode[],
		unsigned int BwendingAndTiming[],
		unsigned int BytePewPixY[],
		unsigned int BytePewPixC[],
		doubwe BytePewPixDETY[],
		doubwe BytePewPixDETC[],
		unsigned int HActive[],
		doubwe HWatio[],
		doubwe HWatioChwoma[],
		unsigned int DPPPewSuwface[],

		/* Output */
		unsigned int swath_width_wuma_ub[],
		unsigned int swath_width_chwoma_ub[],
		doubwe SwathWidth[],
		doubwe SwathWidthChwoma[],
		unsigned int SwathHeightY[],
		unsigned int SwathHeightC[],
		unsigned int DETBuffewSizeInKByte[],
		unsigned int DETBuffewSizeY[],
		unsigned int DETBuffewSizeC[],
		boow *UnboundedWequestEnabwed,
		unsigned int *CompwessedBuffewSizeInkByte,
		unsigned int *CompBufWesewvedSpaceKBytes,
		boow *CompBufWesewvedSpaceNeedAdjustment,
		boow ViewpowtSizeSuppowtPewSuwface[],
		boow *ViewpowtSizeSuppowt);

void dmw32_CawcuwateSwathWidth(
		boow FowceSingweDPP,
		unsigned int NumbewOfActiveSuwfaces,
		enum souwce_fowmat_cwass SouwcePixewFowmat[],
		enum dm_wotation_angwe SouwceScan[],
		boow ViewpowtStationawy[],
		unsigned int ViewpowtWidth[],
		unsigned int ViewpowtHeight[],
		unsigned int ViewpowtXStawt[],
		unsigned int ViewpowtYStawt[],
		unsigned int ViewpowtXStawtC[],
		unsigned int ViewpowtYStawtC[],
		unsigned int SuwfaceWidthY[],
		unsigned int SuwfaceWidthC[],
		unsigned int SuwfaceHeightY[],
		unsigned int SuwfaceHeightC[],
		enum odm_combine_mode ODMMode[],
		unsigned int BytePewPixY[],
		unsigned int BytePewPixC[],
		unsigned int Wead256BytesBwockHeightY[],
		unsigned int Wead256BytesBwockHeightC[],
		unsigned int Wead256BytesBwockWidthY[],
		unsigned int Wead256BytesBwockWidthC[],
		unsigned int BwendingAndTiming[],
		unsigned int HActive[],
		doubwe HWatio[],
		unsigned int DPPPewSuwface[],

		/* Output */
		doubwe SwathWidthdoubweDPPY[],
		doubwe SwathWidthdoubweDPPC[],
		doubwe SwathWidthY[], // pew-pipe
		doubwe SwathWidthC[], // pew-pipe
		unsigned int MaximumSwathHeightY[],
		unsigned int MaximumSwathHeightC[],
		unsigned int swath_width_wuma_ub[], // pew-pipe
		unsigned int swath_width_chwoma_ub[]);

boow dmw32_UnboundedWequest(enum unbounded_wequesting_powicy UseUnboundedWequestingFinaw,
		unsigned int TotawNumbewOfActiveDPP,
		boow NoChwoma,
		enum output_encodew_cwass Output,
		enum dm_swizzwe_mode SuwfaceTiwing,
		boow CompBufWesewvedSpaceNeedAdjustment,
		boow DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment);

void dmw32_CawcuwateDETBuffewSize(
		unsigned int DETSizeOvewwide[],
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
		boow FowceSingweDPP,
		unsigned int NumbewOfActiveSuwfaces,
		boow UnboundedWequestEnabwed,
		unsigned int nomDETInKByte,
		unsigned int MaxTotawDETInKByte,
		unsigned int ConfigWetuwnBuffewSizeInKByte,
		unsigned int MinCompwessedBuffewSizeInKByte,
		unsigned int CompwessedBuffewSegmentSizeInkByteFinaw,
		enum souwce_fowmat_cwass SouwcePixewFowmat[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		unsigned int WoundedUpMaxSwathSizeBytesY[],
		unsigned int WoundedUpMaxSwathSizeBytesC[],
		unsigned int DPPPewSuwface[],
		/* Output */
		unsigned int DETBuffewSizeInKByte[],
		unsigned int *CompwessedBuffewSizeInkByte);

void dmw32_CawcuwateODMMode(
		unsigned int MaximumPixewsPewWinePewDSCUnit,
		unsigned int HActive,
		enum output_fowmat_cwass OutFowmat,
		enum output_encodew_cwass Output,
		enum odm_combine_powicy ODMUse,
		doubwe StateDispcwk,
		doubwe MaxDispcwk,
		boow DSCEnabwe,
		unsigned int TotawNumbewOfActiveDPP,
		unsigned int MaxNumDPP,
		doubwe PixewCwock,
		doubwe DISPCWKDPPCWKDSCCWKDownSpweading,
		doubwe DISPCWKWampingMawgin,
		doubwe DISPCWKDPPCWKVCOSpeed,
		unsigned int NumbewOfDSCSwices,

		/* Output */
		boow *TotawAvaiwabwePipesSuppowt,
		unsigned int *NumbewOfDPP,
		enum odm_combine_mode *ODMMode,
		doubwe *WequiwedDISPCWKPewSuwface);

doubwe dmw32_CawcuwateWequiwedDispcwk(
		enum odm_combine_mode ODMMode,
		doubwe PixewCwock,
		doubwe DISPCWKDPPCWKDSCCWKDownSpweading,
		doubwe DISPCWKWampingMawgin,
		doubwe DISPCWKDPPCWKVCOSpeed,
		doubwe MaxDispcwk);

doubwe dmw32_WoundToDFSGwanuwawity(doubwe Cwock, boow wound_up, doubwe VCOSpeed);

void dmw32_CawcuwateOutputWink(
		doubwe PHYCWKPewState,
		doubwe PHYCWKD18PewState,
		doubwe PHYCWKD32PewState,
		doubwe Downspweading,
		boow IsMainSuwfaceUsingTheIndicatedTiming,
		enum output_encodew_cwass Output,
		enum output_fowmat_cwass OutputFowmat,
		unsigned int HTotaw,
		unsigned int HActive,
		doubwe PixewCwockBackEnd,
		doubwe FowcedOutputWinkBPP,
		unsigned int DSCInputBitPewComponent,
		unsigned int NumbewOfDSCSwices,
		doubwe AudioSampweWate,
		unsigned int AudioSampweWayout,
		enum odm_combine_mode ODMModeNoDSC,
		enum odm_combine_mode ODMModeDSC,
		boow DSCEnabwe,
		unsigned int OutputWinkDPWanes,
		enum dm_output_wink_dp_wate OutputWinkDPWate,

		/* Output */
		boow *WequiwesDSC,
		doubwe *WequiwesFEC,
		doubwe  *OutBpp,
		enum dm_output_type *OutputType,
		enum dm_output_wate *OutputWate,
		unsigned int *WequiwedSwots);

void dmw32_CawcuwateDPPCWK(
		unsigned int NumbewOfActiveSuwfaces,
		doubwe DISPCWKDPPCWKDSCCWKDownSpweading,
		doubwe DISPCWKDPPCWKVCOSpeed,
		doubwe DPPCWKUsingSingweDPP[],
		unsigned int DPPPewSuwface[],

		/* output */
		doubwe *GwobawDPPCWK,
		doubwe Dppcwk[]);

doubwe dmw32_TwuncToVawidBPP(
		doubwe WinkBitWate,
		unsigned int Wanes,
		unsigned int HTotaw,
		unsigned int HActive,
		doubwe PixewCwock,
		doubwe DesiwedBPP,
		boow DSCEnabwe,
		enum output_encodew_cwass Output,
		enum output_fowmat_cwass Fowmat,
		unsigned int DSCInputBitPewComponent,
		unsigned int DSCSwices,
		unsigned int AudioWate,
		unsigned int AudioWayout,
		enum odm_combine_mode ODMModeNoDSC,
		enum odm_combine_mode ODMModeDSC,
		/* Output */
		unsigned int *WequiwedSwots);

doubwe dmw32_WequiwedDTBCWK(
		boow              DSCEnabwe,
		doubwe               PixewCwock,
		enum output_fowmat_cwass  OutputFowmat,
		doubwe               OutputBpp,
		unsigned int              DSCSwices,
		unsigned int                 HTotaw,
		unsigned int                 HActive,
		unsigned int              AudioWate,
		unsigned int              AudioWayout);

unsigned int dmw32_DSCDewayWequiwement(boow DSCEnabwed,
		enum odm_combine_mode ODMMode,
		unsigned int DSCInputBitPewComponent,
		doubwe OutputBpp,
		unsigned int HActive,
		unsigned int HTotaw,
		unsigned int NumbewOfDSCSwices,
		enum output_fowmat_cwass  OutputFowmat,
		enum output_encodew_cwass Output,
		doubwe PixewCwock,
		doubwe PixewCwockBackEnd,
		doubwe dsc_deway_factow_wa);

void dmw32_CawcuwateSuwfaceSizeInMaww(
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int MAWWAwwocatedFowDCN,
		enum dm_use_maww_fow_static_scween_mode UseMAWWFowStaticScween[],
		enum dm_use_maww_fow_pstate_change_mode UsesMAWWFowPStateChange[],
		boow DCCEnabwe[],
		boow ViewpowtStationawy[],
		unsigned int ViewpowtXStawtY[],
		unsigned int ViewpowtYStawtY[],
		unsigned int ViewpowtXStawtC[],
		unsigned int ViewpowtYStawtC[],
		unsigned int ViewpowtWidthY[],
		unsigned int ViewpowtHeightY[],
		unsigned int BytesPewPixewY[],
		unsigned int ViewpowtWidthC[],
		unsigned int ViewpowtHeightC[],
		unsigned int BytesPewPixewC[],
		unsigned int SuwfaceWidthY[],
		unsigned int SuwfaceWidthC[],
		unsigned int SuwfaceHeightY[],
		unsigned int SuwfaceHeightC[],
		unsigned int Wead256BytesBwockWidthY[],
		unsigned int Wead256BytesBwockWidthC[],
		unsigned int Wead256BytesBwockHeightY[],
		unsigned int Wead256BytesBwockHeightC[],
		unsigned int WeadBwockWidthY[],
		unsigned int WeadBwockWidthC[],
		unsigned int WeadBwockHeightY[],
		unsigned int WeadBwockHeightC[],
		unsigned int DCCMetaPitchY[],
		unsigned int DCCMetaPitchC[],

		/* Output */
		unsigned int    SuwfaceSizeInMAWW[],
		boow *ExceededMAWWSize);

void dmw32_CawcuwateVMWowAndSwath(
		unsigned int NumbewOfActiveSuwfaces,
		DmwPipe myPipe[],
		unsigned int SuwfaceSizeInMAWW[],
		unsigned int PTEBuffewSizeInWequestsWuma,
		unsigned int PTEBuffewSizeInWequestsChwoma,
		unsigned int DCCMetaBuffewSizeBytes,
		enum dm_use_maww_fow_static_scween_mode UseMAWWFowStaticScween[],
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
		unsigned int MAWWAwwocatedFowDCN,
		doubwe SwathWidthY[],
		doubwe SwathWidthC[],
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		unsigned int HostVMMaxNonCachedPageTabweWevews,
		unsigned int GPUVMMaxPageTabweWevews,
		unsigned int GPUVMMinPageSizeKBytes[],
		unsigned int HostVMMinPageSize,

		/* Output */
		boow PTEBuffewSizeNotExceeded[],
		boow DCCMetaBuffewSizeNotExceeded[],
		unsigned int dpte_wow_width_wuma_ub[],
		unsigned int dpte_wow_width_chwoma_ub[],
		unsigned int dpte_wow_height_wuma[],
		unsigned int dpte_wow_height_chwoma[],
		unsigned int dpte_wow_height_wineaw_wuma[],     // VBA_DEWTA
		unsigned int dpte_wow_height_wineaw_chwoma[],   // VBA_DEWTA
		unsigned int meta_weq_width[],
		unsigned int meta_weq_width_chwoma[],
		unsigned int meta_weq_height[],
		unsigned int meta_weq_height_chwoma[],
		unsigned int meta_wow_width[],
		unsigned int meta_wow_width_chwoma[],
		unsigned int meta_wow_height[],
		unsigned int meta_wow_height_chwoma[],
		unsigned int vm_gwoup_bytes[],
		unsigned int dpte_gwoup_bytes[],
		unsigned int PixewPTEWeqWidthY[],
		unsigned int PixewPTEWeqHeightY[],
		unsigned int PTEWequestSizeY[],
		unsigned int PixewPTEWeqWidthC[],
		unsigned int PixewPTEWeqHeightC[],
		unsigned int PTEWequestSizeC[],
		unsigned int dpde0_bytes_pew_fwame_ub_w[],
		unsigned int meta_pte_bytes_pew_fwame_ub_w[],
		unsigned int dpde0_bytes_pew_fwame_ub_c[],
		unsigned int meta_pte_bytes_pew_fwame_ub_c[],
		doubwe PwefetchSouwceWinesY[],
		doubwe PwefetchSouwceWinesC[],
		doubwe VInitPweFiwwY[],
		doubwe VInitPweFiwwC[],
		unsigned int MaxNumSwathY[],
		unsigned int MaxNumSwathC[],
		doubwe meta_wow_bw[],
		doubwe dpte_wow_bw[],
		doubwe PixewPTEBytesPewWow[],
		doubwe PDEAndMetaPTEBytesFwame[],
		doubwe MetaWowByte[],
		boow use_one_wow_fow_fwame[],
		boow use_one_wow_fow_fwame_fwip[],
		boow UsesMAWWFowStaticScween[],
		boow PTE_BUFFEW_MODE[],
		unsigned int BIGK_FWAGMENT_SIZE[]);

unsigned int dmw32_CawcuwateVMAndWowBytes(
		boow ViewpowtStationawy,
		boow DCCEnabwe,
		unsigned int NumbewOfDPPs,
		unsigned int BwockHeight256Bytes,
		unsigned int BwockWidth256Bytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int SuwfaceTiwing,
		unsigned int BytePewPixew,
		enum dm_wotation_angwe SouwceScan,
		doubwe SwathWidth,
		unsigned int ViewpowtHeight,
		unsigned int    ViewpowtXStawt,
		unsigned int    ViewpowtYStawt,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		unsigned int HostVMMaxNonCachedPageTabweWevews,
		unsigned int GPUVMMaxPageTabweWevews,
		unsigned int GPUVMMinPageSizeKBytes,
		unsigned int HostVMMinPageSize,
		unsigned int PTEBuffewSizeInWequests,
		unsigned int Pitch,
		unsigned int DCCMetaPitch,
		unsigned int MacwoTiweWidth,
		unsigned int MacwoTiweHeight,

		/* Output */
		unsigned int *MetaWowByte,
		unsigned int *PixewPTEBytesPewWow,
		unsigned int    *dpte_wow_width_ub,
		unsigned int *dpte_wow_height,
		unsigned int *dpte_wow_height_wineaw,
		unsigned int    *PixewPTEBytesPewWow_one_wow_pew_fwame,
		unsigned int    *dpte_wow_width_ub_one_wow_pew_fwame,
		unsigned int    *dpte_wow_height_one_wow_pew_fwame,
		unsigned int *MetaWequestWidth,
		unsigned int *MetaWequestHeight,
		unsigned int *meta_wow_width,
		unsigned int *meta_wow_height,
		unsigned int *PixewPTEWeqWidth,
		unsigned int *PixewPTEWeqHeight,
		unsigned int *PTEWequestSize,
		unsigned int    *DPDE0BytesFwame,
		unsigned int    *MetaPTEBytesFwame);

doubwe dmw32_CawcuwatePwefetchSouwceWines(
		doubwe VWatio,
		unsigned int VTaps,
		boow Intewwace,
		boow PwogwessiveToIntewwaceUnitInOPP,
		unsigned int SwathHeight,
		enum dm_wotation_angwe SouwceWotation,
		boow ViewpowtStationawy,
		doubwe SwathWidth,
		unsigned int ViewpowtHeight,
		unsigned int ViewpowtXStawt,
		unsigned int ViewpowtYStawt,

		/* Output */
		doubwe *VInitPweFiww,
		unsigned int *MaxNumSwath);

void dmw32_CawcuwateMAWWUseFowStaticScween(
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int MAWWAwwocatedFowDCNFinaw,
		enum dm_use_maww_fow_static_scween_mode *UseMAWWFowStaticScween,
		unsigned int SuwfaceSizeInMAWW[],
		boow one_wow_pew_fwame_fits_in_buffew[],

		/* output */
		boow UsesMAWWFowStaticScween[]);

void dmw32_CawcuwateWowBandwidth(
		boow GPUVMEnabwe,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		doubwe VWatio,
		doubwe VWatioChwoma,
		boow DCCEnabwe,
		doubwe WineTime,
		unsigned int MetaWowByteWuma,
		unsigned int MetaWowByteChwoma,
		unsigned int meta_wow_height_wuma,
		unsigned int meta_wow_height_chwoma,
		unsigned int PixewPTEBytesPewWowWuma,
		unsigned int PixewPTEBytesPewWowChwoma,
		unsigned int dpte_wow_height_wuma,
		unsigned int dpte_wow_height_chwoma,
		/* Output */
		doubwe *meta_wow_bw,
		doubwe *dpte_wow_bw);

doubwe dmw32_CawcuwateUwgentWatency(
		doubwe UwgentWatencyPixewDataOnwy,
		doubwe UwgentWatencyPixewMixedWithVMData,
		doubwe UwgentWatencyVMDataOnwy,
		boow   DoUwgentWatencyAdjustment,
		doubwe UwgentWatencyAdjustmentFabwicCwockComponent,
		doubwe UwgentWatencyAdjustmentFabwicCwockWefewence,
		doubwe FabwicCwock);

void dmw32_CawcuwateUwgentBuwstFactow(
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
		unsigned int    swath_width_wuma_ub,
		unsigned int    swath_width_chwoma_ub,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		doubwe  WineTime,
		doubwe  UwgentWatency,
		doubwe  CuwsowBuffewSize,
		unsigned int CuwsowWidth,
		unsigned int CuwsowBPP,
		doubwe  VWatio,
		doubwe  VWatioC,
		doubwe  BytePewPixewInDETY,
		doubwe  BytePewPixewInDETC,
		unsigned int    DETBuffewSizeY,
		unsigned int    DETBuffewSizeC,
		/* Output */
		doubwe *UwgentBuwstFactowCuwsow,
		doubwe *UwgentBuwstFactowWuma,
		doubwe *UwgentBuwstFactowChwoma,
		boow   *NotEnoughUwgentWatencyHiding);

void dmw32_CawcuwateDCFCWKDeepSweep(
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int BytePewPixewY[],
		unsigned int BytePewPixewC[],
		doubwe VWatio[],
		doubwe VWatioChwoma[],
		doubwe SwathWidthY[],
		doubwe SwathWidthC[],
		unsigned int DPPPewSuwface[],
		doubwe HWatio[],
		doubwe HWatioChwoma[],
		doubwe PixewCwock[],
		doubwe PSCW_THWOUGHPUT[],
		doubwe PSCW_THWOUGHPUT_CHWOMA[],
		doubwe Dppcwk[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		unsigned int WetuwnBusWidth,

		/* Output */
		doubwe *DCFCwkDeepSweep);

doubwe dmw32_CawcuwateWwiteBackDeway(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackVTaps,
		unsigned int         WwitebackDestinationWidth,
		unsigned int         WwitebackDestinationHeight,
		unsigned int         WwitebackSouwceHeight,
		unsigned int HTotaw);

void dmw32_UseMinimumDCFCWK(
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
		boow DWWDispway[],
		boow SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
		unsigned int MaxIntewDCNTiweWepeatews,
		unsigned int MaxPwefetchMode,
		doubwe DWAMCwockChangeWatencyFinaw,
		doubwe FCWKChangeWatency,
		doubwe SWEntewPwusExitTime,
		unsigned int WetuwnBusWidth,
		unsigned int WoundTwipPingWatencyCycwes,
		unsigned int WeowdewingBytes,
		unsigned int PixewChunkSizeInKByte,
		unsigned int MetaChunkSize,
		boow GPUVMEnabwe,
		unsigned int GPUVMMaxPageTabweWevews,
		boow HostVMEnabwe,
		unsigned int NumbewOfActiveSuwfaces,
		doubwe HostVMMinPageSize,
		unsigned int HostVMMaxNonCachedPageTabweWevews,
		boow DynamicMetadataVMEnabwed,
		boow ImmediateFwipWequiwement,
		boow PwogwessiveToIntewwaceUnitInOPP,
		doubwe MaxAvewagePewcentOfIdeawSDPPowtBWDispwayCanUseInNowmawSystemOpewation,
		doubwe PewcentOfIdeawSDPPowtBWWeceivedAftewUwgWatency,
		unsigned int VTotaw[],
		unsigned int VActive[],
		unsigned int DynamicMetadataTwansmittedBytes[],
		unsigned int DynamicMetadataWinesBefoweActiveWequiwed[],
		boow Intewwace[],
		doubwe WequiwedDPPCWKPewSuwface[][2][DC__NUM_DPP__MAX],
		doubwe WequiwedDISPCWK[][2],
		doubwe UwgWatency[],
		unsigned int NoOfDPP[][2][DC__NUM_DPP__MAX],
		doubwe PwojectedDCFCwkDeepSweep[][2],
		doubwe MaximumVStawtup[][2][DC__NUM_DPP__MAX],
		unsigned int TotawNumbewOfActiveDPP[][2],
		unsigned int TotawNumbewOfDCCActiveDPP[][2],
		unsigned int dpte_gwoup_bytes[],
		doubwe PwefetchWinesY[][2][DC__NUM_DPP__MAX],
		doubwe PwefetchWinesC[][2][DC__NUM_DPP__MAX],
		unsigned int swath_width_wuma_ub_aww_states[][2][DC__NUM_DPP__MAX],
		unsigned int swath_width_chwoma_ub_aww_states[][2][DC__NUM_DPP__MAX],
		unsigned int BytePewPixewY[],
		unsigned int BytePewPixewC[],
		unsigned int HTotaw[],
		doubwe PixewCwock[],
		doubwe PDEAndMetaPTEBytesPewFwame[][2][DC__NUM_DPP__MAX],
		doubwe DPTEBytesPewWow[][2][DC__NUM_DPP__MAX],
		doubwe MetaWowBytes[][2][DC__NUM_DPP__MAX],
		boow DynamicMetadataEnabwe[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		doubwe DCFCWKPewState[],
		/* Output */
		doubwe DCFCWKState[][2]);

unsigned int dmw32_CawcuwateExtwaWatencyBytes(unsigned int WeowdewingBytes,
		unsigned int TotawNumbewOfActiveDPP,
		unsigned int PixewChunkSizeInKByte,
		unsigned int TotawNumbewOfDCCActiveDPP,
		unsigned int MetaChunkSize,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int NumbewOfDPP[],
		unsigned int dpte_gwoup_bytes[],
		doubwe HostVMInefficiencyFactow,
		doubwe HostVMMinPageSize,
		unsigned int HostVMMaxNonCachedPageTabweWevews);

void dmw32_CawcuwateVUpdateAndDynamicMetadataPawametews(
		unsigned int MaxIntewDCNTiweWepeatews,
		doubwe Dppcwk,
		doubwe Dispcwk,
		doubwe DCFCwkDeepSweep,
		doubwe PixewCwock,
		unsigned int HTotaw,
		unsigned int VBwank,
		unsigned int DynamicMetadataTwansmittedBytes,
		unsigned int DynamicMetadataWinesBefoweActiveWequiwed,
		unsigned int IntewwaceEnabwe,
		boow PwogwessiveToIntewwaceUnitInOPP,
		doubwe *TSetup,
		doubwe *Tdmbf,
		doubwe *Tdmec,
		doubwe *Tdmsks,
		unsigned int *VUpdateOffsetPix,
		doubwe *VUpdateWidthPix,
		doubwe *VWeadyOffsetPix);

doubwe dmw32_CawcuwateTWait(
		unsigned int PwefetchMode,
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
		boow SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
		boow DWWDispway,
		doubwe DWAMCwockChangeWatency,
		doubwe FCWKChangeWatency,
		doubwe UwgentWatency,
		doubwe SWEntewPwusExitTime);

doubwe dmw32_get_wetuwn_bw_mbps(const soc_bounding_box_st *soc,
		const int VowtageWevew,
		const boow HostVMEnabwe,
		const doubwe DCFCWK,
		const doubwe FabwicCwock,
		const doubwe DWAMSpeed);

doubwe dmw32_get_wetuwn_bw_mbps_vm_onwy(const soc_bounding_box_st *soc,
		const int VowtageWevew,
		const doubwe DCFCWK,
		const doubwe FabwicCwock,
		const doubwe DWAMSpeed);

doubwe dmw32_CawcuwateExtwaWatency(
		unsigned int WoundTwipPingWatencyCycwes,
		unsigned int WeowdewingBytes,
		doubwe DCFCWK,
		unsigned int TotawNumbewOfActiveDPP,
		unsigned int PixewChunkSizeInKByte,
		unsigned int TotawNumbewOfDCCActiveDPP,
		unsigned int MetaChunkSize,
		doubwe WetuwnBW,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int NumbewOfDPP[],
		unsigned int dpte_gwoup_bytes[],
		doubwe HostVMInefficiencyFactow,
		doubwe HostVMMinPageSize,
		unsigned int HostVMMaxNonCachedPageTabweWevews);

boow dmw32_CawcuwatePwefetchScheduwe(
		stwuct vba_vaws_st *v,
		unsigned int k,
		doubwe HostVMInefficiencyFactow,
		DmwPipe *myPipe,
		unsigned int DSCDeway,
		unsigned int DPP_WECOUT_WIDTH,
		unsigned int VStawtup,
		unsigned int MaxVStawtup,
		doubwe UwgentWatency,
		doubwe UwgentExtwaWatency,
		doubwe TCawc,
		unsigned int PDEAndMetaPTEBytesFwame,
		unsigned int MetaWowByte,
		unsigned int PixewPTEBytesPewWow,
		doubwe PwefetchSouwceWinesY,
		unsigned int SwathWidthY,
		unsigned int VInitPweFiwwY,
		unsigned int MaxNumSwathY,
		doubwe PwefetchSouwceWinesC,
		unsigned int SwathWidthC,
		unsigned int VInitPweFiwwC,
		unsigned int MaxNumSwathC,
		unsigned int swath_width_wuma_ub,
		unsigned int swath_width_chwoma_ub,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		doubwe TWait,
		doubwe TPweWeq,
		boow ExtendPwefetchIfPossibwe,
		/* Output */
		doubwe   *DSTXAftewScawew,
		doubwe   *DSTYAftewScawew,
		doubwe *DestinationWinesFowPwefetch,
		doubwe *PwefetchBandwidth,
		doubwe *DestinationWinesToWequestVMInVBwank,
		doubwe *DestinationWinesToWequestWowInVBwank,
		doubwe *VWatioPwefetchY,
		doubwe *VWatioPwefetchC,
		doubwe *WequiwedPwefetchPixDataBWWuma,
		doubwe *WequiwedPwefetchPixDataBWChwoma,
		boow   *NotEnoughTimeFowDynamicMetadata,
		doubwe *Tno_bw,
		doubwe *pwefetch_vmwow_bw,
		doubwe *Tdmdw_vm,
		doubwe *Tdmdw,
		doubwe *TSetup,
		unsigned int   *VUpdateOffsetPix,
		doubwe   *VUpdateWidthPix,
		doubwe   *VWeadyOffsetPix);

void dmw32_CawcuwateFwipScheduwe(
		doubwe HostVMInefficiencyFactow,
		doubwe UwgentExtwaWatency,
		doubwe UwgentWatency,
		unsigned int GPUVMMaxPageTabweWevews,
		boow HostVMEnabwe,
		unsigned int HostVMMaxNonCachedPageTabweWevews,
		boow GPUVMEnabwe,
		doubwe HostVMMinPageSize,
		doubwe PDEAndMetaPTEBytesPewFwame,
		doubwe MetaWowBytes,
		doubwe DPTEBytesPewWow,
		doubwe BandwidthAvaiwabweFowImmediateFwip,
		unsigned int TotImmediateFwipBytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		doubwe WineTime,
		doubwe VWatio,
		doubwe VWatioChwoma,
		doubwe Tno_bw,
		boow DCCEnabwe,
		unsigned int dpte_wow_height,
		unsigned int meta_wow_height,
		unsigned int dpte_wow_height_chwoma,
		unsigned int meta_wow_height_chwoma,
		boow    use_one_wow_fow_fwame_fwip,

		/* Output */
		doubwe *DestinationWinesToWequestVMInImmediateFwip,
		doubwe *DestinationWinesToWequestWowInImmediateFwip,
		doubwe *finaw_fwip_bw,
		boow *ImmediateFwipSuppowtedFowPipe);

void dmw32_CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt(
		stwuct vba_vaws_st *v,
		unsigned int PwefetchMode,
		doubwe DCFCWK,
		doubwe WetuwnBW,
		SOCPawametewsWist mmSOCPawametews,
		doubwe SOCCWK,
		doubwe DCFCwkDeepSweep,
		unsigned int DETBuffewSizeY[],
		unsigned int DETBuffewSizeC[],
		unsigned int SwathHeightY[],
		unsigned int SwathHeightC[],
		doubwe SwathWidthY[],
		doubwe SwathWidthC[],
		unsigned int DPPPewSuwface[],
		doubwe BytePewPixewDETY[],
		doubwe BytePewPixewDETC[],
		doubwe DSTXAftewScawew[],
		doubwe DSTYAftewScawew[],
		boow UnboundedWequestEnabwed,
		unsigned int CompwessedBuffewSizeInkByte,

		/* Output */
		enum cwock_change_suppowt *DWAMCwockChangeSuppowt,
		doubwe MaxActiveDWAMCwockChangeWatencySuppowted[],
		unsigned int SubViewpowtWinesNeededInMAWW[],
		enum dm_fcwock_change_suppowt *FCWKChangeSuppowt,
		doubwe *MinActiveFCWKChangeWatencySuppowted,
		boow *USWWetwainingSuppowt,
		doubwe ActiveDWAMCwockChangeWatencyMawgin[]);

doubwe dmw32_CawcuwateWwiteBackDISPCWK(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe PixewCwock,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackHTaps,
		unsigned int WwitebackVTaps,
		unsigned int   WwitebackSouwceWidth,
		unsigned int   WwitebackDestinationWidth,
		unsigned int HTotaw,
		unsigned int WwitebackWineBuffewSize,
		doubwe DISPCWKDPPCWKVCOSpeed);

void dmw32_CawcuwateMinAndMaxPwefetchMode(
		enum dm_pwefetch_modes   AwwowFowPStateChangeOwStuttewInVBwankFinaw,
		unsigned int             *MinPwefetchMode,
		unsigned int             *MaxPwefetchMode);

void dmw32_CawcuwatePixewDewivewyTimes(
		unsigned int             NumbewOfActiveSuwfaces,
		doubwe              VWatio[],
		doubwe              VWatioChwoma[],
		doubwe              VWatioPwefetchY[],
		doubwe              VWatioPwefetchC[],
		unsigned int             swath_width_wuma_ub[],
		unsigned int             swath_width_chwoma_ub[],
		unsigned int             DPPPewSuwface[],
		doubwe              HWatio[],
		doubwe              HWatioChwoma[],
		doubwe              PixewCwock[],
		doubwe              PSCW_THWOUGHPUT[],
		doubwe              PSCW_THWOUGHPUT_CHWOMA[],
		doubwe              Dppcwk[],
		unsigned int             BytePewPixewC[],
		enum dm_wotation_angwe   SouwceWotation[],
		unsigned int             NumbewOfCuwsows[],
		unsigned int             CuwsowWidth[][DC__NUM_CUWSOW__MAX],
		unsigned int             CuwsowBPP[][DC__NUM_CUWSOW__MAX],
		unsigned int             BwockWidth256BytesY[],
		unsigned int             BwockHeight256BytesY[],
		unsigned int             BwockWidth256BytesC[],
		unsigned int             BwockHeight256BytesC[],

		/* Output */
		doubwe              DispwayPipeWineDewivewyTimeWuma[],
		doubwe              DispwayPipeWineDewivewyTimeChwoma[],
		doubwe              DispwayPipeWineDewivewyTimeWumaPwefetch[],
		doubwe              DispwayPipeWineDewivewyTimeChwomaPwefetch[],
		doubwe              DispwayPipeWequestDewivewyTimeWuma[],
		doubwe              DispwayPipeWequestDewivewyTimeChwoma[],
		doubwe              DispwayPipeWequestDewivewyTimeWumaPwefetch[],
		doubwe              DispwayPipeWequestDewivewyTimeChwomaPwefetch[],
		doubwe              CuwsowWequestDewivewyTime[],
		doubwe              CuwsowWequestDewivewyTimePwefetch[]);

void dmw32_CawcuwateMetaAndPTETimes(
		boow use_one_wow_fow_fwame[],
		unsigned int NumbewOfActiveSuwfaces,
		boow GPUVMEnabwe,
		unsigned int MetaChunkSize,
		unsigned int MinMetaChunkSizeBytes,
		unsigned int    HTotaw[],
		doubwe  VWatio[],
		doubwe  VWatioChwoma[],
		doubwe  DestinationWinesToWequestWowInVBwank[],
		doubwe  DestinationWinesToWequestWowInImmediateFwip[],
		boow DCCEnabwe[],
		doubwe  PixewCwock[],
		unsigned int BytePewPixewY[],
		unsigned int BytePewPixewC[],
		enum dm_wotation_angwe SouwceWotation[],
		unsigned int dpte_wow_height[],
		unsigned int dpte_wow_height_chwoma[],
		unsigned int meta_wow_width[],
		unsigned int meta_wow_width_chwoma[],
		unsigned int meta_wow_height[],
		unsigned int meta_wow_height_chwoma[],
		unsigned int meta_weq_width[],
		unsigned int meta_weq_width_chwoma[],
		unsigned int meta_weq_height[],
		unsigned int meta_weq_height_chwoma[],
		unsigned int dpte_gwoup_bytes[],
		unsigned int    PTEWequestSizeY[],
		unsigned int    PTEWequestSizeC[],
		unsigned int    PixewPTEWeqWidthY[],
		unsigned int    PixewPTEWeqHeightY[],
		unsigned int    PixewPTEWeqWidthC[],
		unsigned int    PixewPTEWeqHeightC[],
		unsigned int    dpte_wow_width_wuma_ub[],
		unsigned int    dpte_wow_width_chwoma_ub[],

		/* Output */
		doubwe DST_Y_PEW_PTE_WOW_NOM_W[],
		doubwe DST_Y_PEW_PTE_WOW_NOM_C[],
		doubwe DST_Y_PEW_META_WOW_NOM_W[],
		doubwe DST_Y_PEW_META_WOW_NOM_C[],
		doubwe TimePewMetaChunkNominaw[],
		doubwe TimePewChwomaMetaChunkNominaw[],
		doubwe TimePewMetaChunkVBwank[],
		doubwe TimePewChwomaMetaChunkVBwank[],
		doubwe TimePewMetaChunkFwip[],
		doubwe TimePewChwomaMetaChunkFwip[],
		doubwe time_pew_pte_gwoup_nom_wuma[],
		doubwe time_pew_pte_gwoup_vbwank_wuma[],
		doubwe time_pew_pte_gwoup_fwip_wuma[],
		doubwe time_pew_pte_gwoup_nom_chwoma[],
		doubwe time_pew_pte_gwoup_vbwank_chwoma[],
		doubwe time_pew_pte_gwoup_fwip_chwoma[]);

void dmw32_CawcuwateVMGwoupAndWequestTimes(
		unsigned int     NumbewOfActiveSuwfaces,
		boow     GPUVMEnabwe,
		unsigned int     GPUVMMaxPageTabweWevews,
		unsigned int     HTotaw[],
		unsigned int     BytePewPixewC[],
		doubwe      DestinationWinesToWequestVMInVBwank[],
		doubwe      DestinationWinesToWequestVMInImmediateFwip[],
		boow     DCCEnabwe[],
		doubwe      PixewCwock[],
		unsigned int        dpte_wow_width_wuma_ub[],
		unsigned int        dpte_wow_width_chwoma_ub[],
		unsigned int     vm_gwoup_bytes[],
		unsigned int     dpde0_bytes_pew_fwame_ub_w[],
		unsigned int     dpde0_bytes_pew_fwame_ub_c[],
		unsigned int        meta_pte_bytes_pew_fwame_ub_w[],
		unsigned int        meta_pte_bytes_pew_fwame_ub_c[],

		/* Output */
		doubwe      TimePewVMGwoupVBwank[],
		doubwe      TimePewVMGwoupFwip[],
		doubwe      TimePewVMWequestVBwank[],
		doubwe      TimePewVMWequestFwip[]);

void dmw32_CawcuwateDCCConfiguwation(
		boow             DCCEnabwed,
		boow             DCCPwogwammingAssumesScanDiwectionUnknown,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int             SuwfaceWidthWuma,
		unsigned int             SuwfaceWidthChwoma,
		unsigned int             SuwfaceHeightWuma,
		unsigned int             SuwfaceHeightChwoma,
		unsigned int                nomDETInKByte,
		unsigned int             WequestHeight256ByteWuma,
		unsigned int             WequestHeight256ByteChwoma,
		enum dm_swizzwe_mode     TiwingFowmat,
		unsigned int             BytePewPixewY,
		unsigned int             BytePewPixewC,
		doubwe              BytePewPixewDETY,
		doubwe              BytePewPixewDETC,
		enum dm_wotation_angwe   SouwceWotation,
		/* Output */
		unsigned int        *MaxUncompwessedBwockWuma,
		unsigned int        *MaxUncompwessedBwockChwoma,
		unsigned int        *MaxCompwessedBwockWuma,
		unsigned int        *MaxCompwessedBwockChwoma,
		unsigned int        *IndependentBwockWuma,
		unsigned int        *IndependentBwockChwoma);

void dmw32_CawcuwateStuttewEfficiency(
		unsigned int      CompwessedBuffewSizeInkByte,
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[],
		boow   UnboundedWequestEnabwed,
		unsigned int      MetaFIFOSizeInKEntwies,
		unsigned int      ZewoSizeBuffewEntwies,
		unsigned int      PixewChunkSizeInKByte,
		unsigned int   NumbewOfActiveSuwfaces,
		unsigned int      WOBBuffewSizeInKByte,
		doubwe    TotawDataWeadBandwidth,
		doubwe    DCFCWK,
		doubwe    WetuwnBW,
		unsigned int      CompbufWesewvedSpace64B,
		unsigned int      CompbufWesewvedSpaceZs,
		doubwe    SWExitTime,
		doubwe    SWExitZ8Time,
		boow   SynchwonizeTimingsFinaw,
		unsigned int   BwendingAndTiming[],
		doubwe    StuttewEntewPwusExitWatewmawk,
		doubwe    Z8StuttewEntewPwusExitWatewmawk,
		boow   PwogwessiveToIntewwaceUnitInOPP,
		boow   Intewwace[],
		doubwe    MinTTUVBwank[],
		unsigned int   DPPPewSuwface[],
		unsigned int      DETBuffewSizeY[],
		unsigned int   BytePewPixewY[],
		doubwe    BytePewPixewDETY[],
		doubwe      SwathWidthY[],
		unsigned int   SwathHeightY[],
		unsigned int   SwathHeightC[],
		doubwe    NetDCCWateWuma[],
		doubwe    NetDCCWateChwoma[],
		doubwe    DCCFwactionOfZewoSizeWequestsWuma[],
		doubwe    DCCFwactionOfZewoSizeWequestsChwoma[],
		unsigned int      HTotaw[],
		unsigned int      VTotaw[],
		doubwe    PixewCwock[],
		doubwe    VWatio[],
		enum dm_wotation_angwe SouwceWotation[],
		unsigned int   BwockHeight256BytesY[],
		unsigned int   BwockWidth256BytesY[],
		unsigned int   BwockHeight256BytesC[],
		unsigned int   BwockWidth256BytesC[],
		unsigned int   DCCYMaxUncompwessedBwock[],
		unsigned int   DCCCMaxUncompwessedBwock[],
		unsigned int      VActive[],
		boow   DCCEnabwe[],
		boow   WwitebackEnabwe[],
		doubwe    WeadBandwidthSuwfaceWuma[],
		doubwe    WeadBandwidthSuwfaceChwoma[],
		doubwe    meta_wow_bw[],
		doubwe    dpte_wow_bw[],

		/* Output */
		doubwe   *StuttewEfficiencyNotIncwudingVBwank,
		doubwe   *StuttewEfficiency,
		unsigned int     *NumbewOfStuttewBuwstsPewFwame,
		doubwe   *Z8StuttewEfficiencyNotIncwudingVBwank,
		doubwe   *Z8StuttewEfficiency,
		unsigned int     *Z8NumbewOfStuttewBuwstsPewFwame,
		doubwe   *StuttewPewiod,
		boow  *DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE);

void dmw32_CawcuwateMaxDETAndMinCompwessedBuffewSize(
		unsigned int    ConfigWetuwnBuffewSizeInKByte,
		unsigned int    WOBBuffewSizeInKByte,
		unsigned int MaxNumDPP,
		boow nomDETInKByteOvewwideEnabwe, // VBA_DEWTA, awwow DV to ovewwide defauwt DET size
		unsigned int nomDETInKByteOvewwideVawue,  // VBA_DEWTA

		/* Output */
		unsigned int *MaxTotawDETInKByte,
		unsigned int *nomDETInKByte,
		unsigned int *MinCompwessedBuffewSizeInKByte);

boow dmw32_CawcuwateVActiveBandwithSuppowt(unsigned int NumbewOfActiveSuwfaces,
		doubwe WetuwnBW,
		boow NotUwgentWatencyHiding[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		doubwe cuwsow_bw[],
		doubwe meta_wow_bandwidth[],
		doubwe dpte_wow_bandwidth[],
		unsigned int NumbewOfDPP[],
		doubwe UwgentBuwstFactowWuma[],
		doubwe UwgentBuwstFactowChwoma[],
		doubwe UwgentBuwstFactowCuwsow[]);

void dmw32_CawcuwatePwefetchBandwithSuppowt(unsigned int NumbewOfActiveSuwfaces,
		doubwe WetuwnBW,
		boow NotUwgentWatencyHiding[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		doubwe PwefetchBandwidthWuma[],
		doubwe PwefetchBandwidthChwoma[],
		doubwe cuwsow_bw[],
		doubwe meta_wow_bandwidth[],
		doubwe dpte_wow_bandwidth[],
		doubwe cuwsow_bw_pwe[],
		doubwe pwefetch_vmwow_bw[],
		unsigned int NumbewOfDPP[],
		doubwe UwgentBuwstFactowWuma[],
		doubwe UwgentBuwstFactowChwoma[],
		doubwe UwgentBuwstFactowCuwsow[],
		doubwe UwgentBuwstFactowWumaPwe[],
		doubwe UwgentBuwstFactowChwomaPwe[],
		doubwe UwgentBuwstFactowCuwsowPwe[],
		doubwe PwefetchBW[],
		doubwe VWatio[],
		doubwe MaxVWatioPwe,

		/* output */
		doubwe  *MaxPwefetchBandwidth,
		doubwe  *FwactionOfUwgentBandwidth,
		boow *PwefetchBandwidthSuppowt);

doubwe dmw32_CawcuwateBandwidthAvaiwabweFowImmediateFwip(unsigned int NumbewOfActiveSuwfaces,
		doubwe WetuwnBW,
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		doubwe PwefetchBandwidthWuma[],
		doubwe PwefetchBandwidthChwoma[],
		doubwe cuwsow_bw[],
		doubwe cuwsow_bw_pwe[],
		unsigned int NumbewOfDPP[],
		doubwe UwgentBuwstFactowWuma[],
		doubwe UwgentBuwstFactowChwoma[],
		doubwe UwgentBuwstFactowCuwsow[],
		doubwe UwgentBuwstFactowWumaPwe[],
		doubwe UwgentBuwstFactowChwomaPwe[],
		doubwe UwgentBuwstFactowCuwsowPwe[]);

void dmw32_CawcuwateImmediateFwipBandwithSuppowt(unsigned int NumbewOfActiveSuwfaces,
		doubwe WetuwnBW,
		enum immediate_fwip_wequiwement ImmediateFwipWequiwement[],
		doubwe finaw_fwip_bw[],
		doubwe WeadBandwidthWuma[],
		doubwe WeadBandwidthChwoma[],
		doubwe PwefetchBandwidthWuma[],
		doubwe PwefetchBandwidthChwoma[],
		doubwe cuwsow_bw[],
		doubwe meta_wow_bandwidth[],
		doubwe dpte_wow_bandwidth[],
		doubwe cuwsow_bw_pwe[],
		doubwe pwefetch_vmwow_bw[],
		unsigned int NumbewOfDPP[],
		doubwe UwgentBuwstFactowWuma[],
		doubwe UwgentBuwstFactowChwoma[],
		doubwe UwgentBuwstFactowCuwsow[],
		doubwe UwgentBuwstFactowWumaPwe[],
		doubwe UwgentBuwstFactowChwomaPwe[],
		doubwe UwgentBuwstFactowCuwsowPwe[],

		/* output */
		doubwe  *TotawBandwidth,
		doubwe  *FwactionOfUwgentBandwidth,
		boow *ImmediateFwipBandwidthSuppowt);

boow dmw32_CawcuwateDETSwathFiwwWatencyHiding(unsigned int NumbewOfActiveSuwfaces,
		doubwe WetuwnBW,
		doubwe UwgentWatency,
		unsigned int SwathHeightY[],
		unsigned int SwathHeightC[],
		unsigned int SwathWidthY[],
		unsigned int SwathWidthC[],
		doubwe  BytePewPixewInDETY[],
		doubwe  BytePewPixewInDETC[],
		unsigned int    DETBuffewSizeY[],
		unsigned int    DETBuffewSizeC[],
		unsigned int	NumOfDPP[],
		unsigned int	HTotaw[],
		doubwe	PixewCwock[],
		doubwe	VWatioY[],
		doubwe	VWatioC[],
		enum dm_use_maww_fow_pstate_change_mode UsesMAWWFowPStateChange[],
		enum unbounded_wequesting_powicy UseUnboundedWequesting);

#endif