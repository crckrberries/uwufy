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


#incwude "../dispway_mode_wib.h"
#incwude "../dmw_inwine_defs.h"
#incwude "../dispway_mode_vba.h"
#incwude "dispway_mode_vba_21.h"


/*
 * NOTE:
 *   This fiwe is gcc-pawsabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */
typedef stwuct {
	doubwe DPPCWK;
	doubwe DISPCWK;
	doubwe PixewCwock;
	doubwe DCFCWKDeepSweep;
	unsigned int DPPPewPwane;
	boow ScawewEnabwed;
	enum scan_diwection_cwass SouwceScan;
	unsigned int BwockWidth256BytesY;
	unsigned int BwockHeight256BytesY;
	unsigned int BwockWidth256BytesC;
	unsigned int BwockHeight256BytesC;
	unsigned int IntewwaceEnabwe;
	unsigned int NumbewOfCuwsows;
	unsigned int VBwank;
	unsigned int HTotaw;
} Pipe;

typedef stwuct {
	boow Enabwe;
	unsigned int MaxPageTabweWevews;
	unsigned int CachedPageTabweWevews;
} HostVM;

#define BPP_INVAWID 0
#define BPP_BWENDED_PIPE 0xffffffff
#define DCN21_MAX_DSC_IMAGE_WIDTH 5184
#define DCN21_MAX_420_IMAGE_WIDTH 4096

static void DispwayPipeConfiguwation(stwuct dispway_mode_wib *mode_wib);
static void DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation(
		stwuct dispway_mode_wib *mode_wib);
static unsigned int dscceComputeDeway(
		unsigned int bpc,
		doubwe bpp,
		unsigned int swiceWidth,
		unsigned int numSwices,
		enum output_fowmat_cwass pixewFowmat);
static unsigned int dscComputeDeway(enum output_fowmat_cwass pixewFowmat);
// Supew monstew function with some 45 awgument
static boow CawcuwatePwefetchScheduwe(
		stwuct dispway_mode_wib *mode_wib,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
		Pipe *myPipe,
		unsigned int DSCDeway,
		doubwe DPPCWKDewaySubtotaw,
		doubwe DPPCWKDewaySCW,
		doubwe DPPCWKDewaySCWWBOnwy,
		doubwe DPPCWKDewayCNVCFowmatew,
		doubwe DPPCWKDewayCNVCCuwsow,
		doubwe DISPCWKDewaySubtotaw,
		unsigned int ScawewWecoutWidth,
		enum output_fowmat_cwass OutputFowmat,
		unsigned int MaxIntewDCNTiweWepeatews,
		unsigned int VStawtup,
		unsigned int MaxVStawtup,
		unsigned int GPUVMPageTabweWevews,
		boow GPUVMEnabwe,
		HostVM *myHostVM,
		boow DynamicMetadataEnabwe,
		int DynamicMetadataWinesBefoweActiveWequiwed,
		unsigned int DynamicMetadataTwansmittedBytes,
		boow DCCEnabwe,
		doubwe UwgentWatency,
		doubwe UwgentExtwaWatency,
		doubwe TCawc,
		unsigned int PDEAndMetaPTEBytesFwame,
		unsigned int MetaWowByte,
		unsigned int PixewPTEBytesPewWow,
		doubwe PwefetchSouwceWinesY,
		unsigned int SwathWidthY,
		doubwe BytePewPixewDETY,
		doubwe VInitPweFiwwY,
		unsigned int MaxNumSwathY,
		doubwe PwefetchSouwceWinesC,
		doubwe BytePewPixewDETC,
		doubwe VInitPweFiwwC,
		unsigned int MaxNumSwathC,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		doubwe TWait,
		boow XFCEnabwed,
		doubwe XFCWemoteSuwfaceFwipDeway,
		boow PwogwessiveToIntewwaceUnitInOPP,
		doubwe *DSTXAftewScawew,
		doubwe *DSTYAftewScawew,
		doubwe *DestinationWinesFowPwefetch,
		doubwe *PwefetchBandwidth,
		doubwe *DestinationWinesToWequestVMInVBwank,
		doubwe *DestinationWinesToWequestWowInVBwank,
		doubwe *VWatioPwefetchY,
		doubwe *VWatioPwefetchC,
		doubwe *WequiwedPwefetchPixDataBWWuma,
		doubwe *WequiwedPwefetchPixDataBWChwoma,
		unsigned int *VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
		doubwe *Tno_bw,
		doubwe *pwefetch_vmwow_bw,
		unsigned int *swath_width_wuma_ub,
		unsigned int *swath_width_chwoma_ub,
		unsigned int *VUpdateOffsetPix,
		doubwe *VUpdateWidthPix,
		doubwe *VWeadyOffsetPix);
static doubwe WoundToDFSGwanuwawityUp(doubwe Cwock, doubwe VCOSpeed);
static doubwe WoundToDFSGwanuwawityDown(doubwe Cwock, doubwe VCOSpeed);
static doubwe CawcuwateDCCConfiguwation(
		boow                 DCCEnabwed,
		boow                 DCCPwogwammingAssumesScanDiwectionUnknown,
		unsigned int         ViewpowtWidth,
		unsigned int         ViewpowtHeight,
		unsigned int         DETBuffewSize,
		unsigned int         WequestHeight256Byte,
		unsigned int         SwathHeight,
		enum dm_swizzwe_mode TiwingFowmat,
		unsigned int         BytePewPixew,
		enum scan_diwection_cwass ScanOwientation,
		unsigned int        *MaxUncompwessedBwock,
		unsigned int        *MaxCompwessedBwock,
		unsigned int        *Independent64ByteBwock);
static doubwe CawcuwatePwefetchSouwceWines(
		stwuct dispway_mode_wib *mode_wib,
		doubwe VWatio,
		doubwe vtaps,
		boow Intewwace,
		boow PwogwessiveToIntewwaceUnitInOPP,
		unsigned int SwathHeight,
		unsigned int ViewpowtYStawt,
		doubwe *VInitPweFiww,
		unsigned int *MaxNumSwath);
static unsigned int CawcuwateVMAndWowBytes(
		stwuct dispway_mode_wib *mode_wib,
		boow DCCEnabwe,
		unsigned int BwockHeight256Bytes,
		unsigned int BwockWidth256Bytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int SuwfaceTiwing,
		unsigned int BytePewPixew,
		enum scan_diwection_cwass ScanDiwection,
		unsigned int ViewpowtWidth,
		unsigned int ViewpowtHeight,
		unsigned int SwathWidthY,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		unsigned int HostVMMaxPageTabweWevews,
		unsigned int HostVMCachedPageTabweWevews,
		unsigned int VMMPageSize,
		unsigned int PTEBuffewSizeInWequests,
		unsigned int Pitch,
		unsigned int DCCMetaPitch,
		unsigned int *MacwoTiweWidth,
		unsigned int *MetaWowByte,
		unsigned int *PixewPTEBytesPewWow,
		boow *PTEBuffewSizeNotExceeded,
		unsigned int *dpte_wow_width_ub,
		unsigned int *dpte_wow_height,
		unsigned int *MetaWequestWidth,
		unsigned int *MetaWequestHeight,
		unsigned int *meta_wow_width,
		unsigned int *meta_wow_height,
		unsigned int *vm_gwoup_bytes,
		unsigned int *dpte_gwoup_bytes,
		unsigned int *PixewPTEWeqWidth,
		unsigned int *PixewPTEWeqHeight,
		unsigned int *PTEWequestSize,
		unsigned int *DPDE0BytesFwame,
		unsigned int *MetaPTEBytesFwame);

static doubwe CawcuwateTWait(
		unsigned int PwefetchMode,
		doubwe DWAMCwockChangeWatency,
		doubwe UwgentWatency,
		doubwe SWEntewPwusExitTime);
static doubwe CawcuwateWemoteSuwfaceFwipDeway(
		stwuct dispway_mode_wib *mode_wib,
		doubwe VWatio,
		doubwe SwathWidth,
		doubwe Bpp,
		doubwe WineTime,
		doubwe XFCTSwvVupdateOffset,
		doubwe XFCTSwvVupdateWidth,
		doubwe XFCTSwvVweadyOffset,
		doubwe XFCXBUFWatencyTowewance,
		doubwe XFCFiwwBWOvewhead,
		doubwe XFCSwvChunkSize,
		doubwe XFCBusTwanspowtTime,
		doubwe TCawc,
		doubwe TWait,
		doubwe *SwcActiveDwainWate,
		doubwe *TInitXFiww,
		doubwe *TswvChk);
static void CawcuwateActiveWowBandwidth(
		boow GPUVMEnabwe,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		doubwe VWatio,
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
		doubwe *meta_wow_bw,
		doubwe *dpte_wow_bw);
static void CawcuwateFwipScheduwe(
		stwuct dispway_mode_wib *mode_wib,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
		doubwe UwgentExtwaWatency,
		doubwe UwgentWatency,
		unsigned int GPUVMMaxPageTabweWevews,
		boow HostVMEnabwe,
		unsigned int HostVMMaxPageTabweWevews,
		unsigned int HostVMCachedPageTabweWevews,
		boow GPUVMEnabwe,
		doubwe PDEAndMetaPTEBytesPewFwame,
		doubwe MetaWowBytes,
		doubwe DPTEBytesPewWow,
		doubwe BandwidthAvaiwabweFowImmediateFwip,
		unsigned int TotImmediateFwipBytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		doubwe WineTime,
		doubwe VWatio,
		doubwe Tno_bw,
		boow DCCEnabwe,
		unsigned int dpte_wow_height,
		unsigned int meta_wow_height,
		unsigned int dpte_wow_height_chwoma,
		unsigned int meta_wow_height_chwoma,
		doubwe *DestinationWinesToWequestVMInImmediateFwip,
		doubwe *DestinationWinesToWequestWowInImmediateFwip,
		doubwe *finaw_fwip_bw,
		boow *ImmediateFwipSuppowtedFowPipe);
static doubwe CawcuwateWwiteBackDeway(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackWumaHTaps,
		unsigned int WwitebackWumaVTaps,
		unsigned int WwitebackChwomaHTaps,
		unsigned int WwitebackChwomaVTaps,
		unsigned int WwitebackDestinationWidth);
static void CawcuwateWatewmawksAndDWAMSpeedChangeSuppowt(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int PwefetchMode,
		unsigned int NumbewOfActivePwanes,
		unsigned int MaxWineBuffewWines,
		unsigned int WineBuffewSize,
		unsigned int DPPOutputBuffewPixews,
		unsigned int DETBuffewSizeInKByte,
		unsigned int WwitebackIntewfaceWumaBuffewSize,
		unsigned int WwitebackIntewfaceChwomaBuffewSize,
		doubwe DCFCWK,
		doubwe UwgentOutOfOwdewWetuwn,
		doubwe WetuwnBW,
		boow GPUVMEnabwe,
		int dpte_gwoup_bytes[],
		unsigned int MetaChunkSize,
		doubwe UwgentWatency,
		doubwe ExtwaWatency,
		doubwe WwitebackWatency,
		doubwe WwitebackChunkSize,
		doubwe SOCCWK,
		doubwe DWAMCwockChangeWatency,
		doubwe SWExitTime,
		doubwe SWEntewPwusExitTime,
		doubwe DCFCWKDeepSweep,
		int DPPPewPwane[],
		boow DCCEnabwe[],
		doubwe DPPCWK[],
		doubwe SwathWidthSingweDPPY[],
		unsigned int SwathHeightY[],
		doubwe WeadBandwidthPwaneWuma[],
		unsigned int SwathHeightC[],
		doubwe WeadBandwidthPwaneChwoma[],
		unsigned int WBBitPewPixew[],
		doubwe SwathWidthY[],
		doubwe HWatio[],
		unsigned int vtaps[],
		unsigned int VTAPsChwoma[],
		doubwe VWatio[],
		unsigned int HTotaw[],
		doubwe PixewCwock[],
		unsigned int BwendingAndTiming[],
		doubwe BytePewPixewDETY[],
		doubwe BytePewPixewDETC[],
		boow WwitebackEnabwe[],
		enum souwce_fowmat_cwass WwitebackPixewFowmat[],
		doubwe WwitebackDestinationWidth[],
		doubwe WwitebackDestinationHeight[],
		doubwe WwitebackSouwceHeight[],
		enum cwock_change_suppowt *DWAMCwockChangeSuppowt,
		doubwe *UwgentWatewmawk,
		doubwe *WwitebackUwgentWatewmawk,
		doubwe *DWAMCwockChangeWatewmawk,
		doubwe *WwitebackDWAMCwockChangeWatewmawk,
		doubwe *StuttewExitWatewmawk,
		doubwe *StuttewEntewPwusExitWatewmawk,
		doubwe *MinActiveDWAMCwockChangeWatencySuppowted);
static void CawcuwateDCFCWKDeepSweep(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int NumbewOfActivePwanes,
		doubwe BytePewPixewDETY[],
		doubwe BytePewPixewDETC[],
		doubwe VWatio[],
		doubwe SwathWidthY[],
		int DPPPewPwane[],
		doubwe HWatio[],
		doubwe PixewCwock[],
		doubwe PSCW_THWOUGHPUT[],
		doubwe PSCW_THWOUGHPUT_CHWOMA[],
		doubwe DPPCWK[],
		doubwe *DCFCWKDeepSweep);
static void CawcuwateDETBuffewSize(
		unsigned int DETBuffewSizeInKByte,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		unsigned int *DETBuffewSizeY,
		unsigned int *DETBuffewSizeC);
static void CawcuwateUwgentBuwstFactow(
		unsigned int DETBuffewSizeInKByte,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		unsigned int SwathWidthY,
		doubwe WineTime,
		doubwe UwgentWatency,
		doubwe CuwsowBuffewSize,
		unsigned int CuwsowWidth,
		unsigned int CuwsowBPP,
		doubwe VWatio,
		doubwe VWatioPweY,
		doubwe VWatioPweC,
		doubwe BytePewPixewInDETY,
		doubwe BytePewPixewInDETC,
		doubwe *UwgentBuwstFactowCuwsow,
		doubwe *UwgentBuwstFactowCuwsowPwe,
		doubwe *UwgentBuwstFactowWuma,
		doubwe *UwgentBuwstFactowWumaPwe,
		doubwe *UwgentBuwstFactowChwoma,
		doubwe *UwgentBuwstFactowChwomaPwe,
		unsigned int *NotEnoughUwgentWatencyHiding,
		unsigned int *NotEnoughUwgentWatencyHidingPwe);

static void CawcuwatePixewDewivewyTimes(
		unsigned int           NumbewOfActivePwanes,
		doubwe                 VWatio[],
		doubwe                 VWatioPwefetchY[],
		doubwe                 VWatioPwefetchC[],
		unsigned int           swath_width_wuma_ub[],
		unsigned int           swath_width_chwoma_ub[],
		int                    DPPPewPwane[],
		doubwe                 HWatio[],
		doubwe                 PixewCwock[],
		doubwe                 PSCW_THWOUGHPUT[],
		doubwe                 PSCW_THWOUGHPUT_CHWOMA[],
		doubwe                 DPPCWK[],
		doubwe                 BytePewPixewDETC[],
		enum scan_diwection_cwass SouwceScan[],
		unsigned int           BwockWidth256BytesY[],
		unsigned int           BwockHeight256BytesY[],
		unsigned int           BwockWidth256BytesC[],
		unsigned int           BwockHeight256BytesC[],
		doubwe                 DispwayPipeWineDewivewyTimeWuma[],
		doubwe                 DispwayPipeWineDewivewyTimeChwoma[],
		doubwe                 DispwayPipeWineDewivewyTimeWumaPwefetch[],
		doubwe                 DispwayPipeWineDewivewyTimeChwomaPwefetch[],
		doubwe                 DispwayPipeWequestDewivewyTimeWuma[],
		doubwe                 DispwayPipeWequestDewivewyTimeChwoma[],
		doubwe                 DispwayPipeWequestDewivewyTimeWumaPwefetch[],
		doubwe                 DispwayPipeWequestDewivewyTimeChwomaPwefetch[]);

static void CawcuwateMetaAndPTETimes(
		unsigned int           NumbewOfActivePwanes,
		boow                   GPUVMEnabwe,
		unsigned int           MetaChunkSize,
		unsigned int           MinMetaChunkSizeBytes,
		unsigned int           GPUVMMaxPageTabweWevews,
		unsigned int           HTotaw[],
		doubwe                 VWatio[],
		doubwe                 VWatioPwefetchY[],
		doubwe                 VWatioPwefetchC[],
		doubwe                 DestinationWinesToWequestWowInVBwank[],
		doubwe                 DestinationWinesToWequestWowInImmediateFwip[],
		doubwe                 DestinationWinesToWequestVMInVBwank[],
		doubwe                 DestinationWinesToWequestVMInImmediateFwip[],
		boow                   DCCEnabwe[],
		doubwe                 PixewCwock[],
		doubwe                 BytePewPixewDETY[],
		doubwe                 BytePewPixewDETC[],
		enum scan_diwection_cwass SouwceScan[],
		unsigned int           dpte_wow_height[],
		unsigned int           dpte_wow_height_chwoma[],
		unsigned int           meta_wow_width[],
		unsigned int           meta_wow_height[],
		unsigned int           meta_weq_width[],
		unsigned int           meta_weq_height[],
		int                   dpte_gwoup_bytes[],
		unsigned int           PTEWequestSizeY[],
		unsigned int           PTEWequestSizeC[],
		unsigned int           PixewPTEWeqWidthY[],
		unsigned int           PixewPTEWeqHeightY[],
		unsigned int           PixewPTEWeqWidthC[],
		unsigned int           PixewPTEWeqHeightC[],
		unsigned int           dpte_wow_width_wuma_ub[],
		unsigned int           dpte_wow_width_chwoma_ub[],
		unsigned int           vm_gwoup_bytes[],
		unsigned int           dpde0_bytes_pew_fwame_ub_w[],
		unsigned int           dpde0_bytes_pew_fwame_ub_c[],
		unsigned int           meta_pte_bytes_pew_fwame_ub_w[],
		unsigned int           meta_pte_bytes_pew_fwame_ub_c[],
		doubwe                 DST_Y_PEW_PTE_WOW_NOM_W[],
		doubwe                 DST_Y_PEW_PTE_WOW_NOM_C[],
		doubwe                 DST_Y_PEW_META_WOW_NOM_W[],
		doubwe                 TimePewMetaChunkNominaw[],
		doubwe                 TimePewMetaChunkVBwank[],
		doubwe                 TimePewMetaChunkFwip[],
		doubwe                 time_pew_pte_gwoup_nom_wuma[],
		doubwe                 time_pew_pte_gwoup_vbwank_wuma[],
		doubwe                 time_pew_pte_gwoup_fwip_wuma[],
		doubwe                 time_pew_pte_gwoup_nom_chwoma[],
		doubwe                 time_pew_pte_gwoup_vbwank_chwoma[],
		doubwe                 time_pew_pte_gwoup_fwip_chwoma[],
		doubwe                 TimePewVMGwoupVBwank[],
		doubwe                 TimePewVMGwoupFwip[],
		doubwe                 TimePewVMWequestVBwank[],
		doubwe                 TimePewVMWequestFwip[]);

static doubwe CawcuwateExtwaWatency(
		doubwe UwgentWoundTwipAndOutOfOwdewWatency,
		int TotawNumbewOfActiveDPP,
		int PixewChunkSizeInKByte,
		int TotawNumbewOfDCCActiveDPP,
		int MetaChunkSize,
		doubwe WetuwnBW,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		int NumbewOfActivePwanes,
		int NumbewOfDPP[],
		int dpte_gwoup_bytes[],
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
		int HostVMMaxPageTabweWevews,
		int HostVMCachedPageTabweWevews);

void dmw21_wecawcuwate(stwuct dispway_mode_wib *mode_wib)
{
	ModeSuppowtAndSystemConfiguwation(mode_wib);
	PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(mode_wib);
	DispwayPipeConfiguwation(mode_wib);
	DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation(mode_wib);
}

static unsigned int dscceComputeDeway(
		unsigned int bpc,
		doubwe bpp,
		unsigned int swiceWidth,
		unsigned int numSwices,
		enum output_fowmat_cwass pixewFowmat)
{
	// vawid bpc         = souwce bits pew component in the set of {8, 10, 12}
	// vawid bpp         = incwements of 1/16 of a bit
	//                    min = 6/7/8 in N420/N422/444, wespectivewy
	//                    max = such that compwession is 1:1
	//vawid swiceWidth  = numbew of pixews pew swice wine, must be wess than ow equaw to 5184/numSwices (ow 4096/numSwices in 420 mode)
	//vawid numSwices   = numbew of swices in the howiziontaw diwection pew DSC engine in the set of {1, 2, 3, 4}
	//vawid pixewFowmat = pixew/cowow fowmat in the set of {:N444_WGB, :S422, :N422, :N420}

	// fixed vawue
	unsigned int wcModewSize = 8192;

	// N422/N420 opewate at 2 pixews pew cwock
	unsigned int pixewsPewCwock, wstaww, D, initawXmitDeway, w, S, ix, wx, p, w0, a, ax, w,
			Deway, pixews;

	if (pixewFowmat == dm_n422 || pixewFowmat == dm_420)
		pixewsPewCwock = 2;
	// #aww othew modes opewate at 1 pixew pew cwock
	ewse
		pixewsPewCwock = 1;

	//initiaw twansmit deway as pew PPS
	initawXmitDeway = dmw_wound(wcModewSize / 2.0 / bpp / pixewsPewCwock);

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
	if (pixewFowmat == dm_s422)
		S = 1;
	ewse
		S = 0;

	//main cawcuwation fow the dscce
	ix = initawXmitDeway + 45;
	wx = (w + 2) / 3;
	p = 3 * wx - w;
	w0 = ix / w;
	a = ix + p * w0;
	ax = (a + 2) / 3 + D + 6 + 1;
	w = (ax + wx - 1) / wx;
	if ((ix % w) == 0 && p != 0)
		wstaww = 1;
	ewse
		wstaww = 0;
	Deway = w * wx * (numSwices - 1) + ax + S + wstaww + 22;

	//dsc pwocesses 3 pixew containews pew cycwe and a containew can contain 1 ow 2 pixews
	pixews = Deway * 3 * pixewsPewCwock;
	wetuwn pixews;
}

static unsigned int dscComputeDeway(enum output_fowmat_cwass pixewFowmat)
{
	unsigned int Deway = 0;

	if (pixewFowmat == dm_420) {
		//   sfw
		Deway = Deway + 2;
		//   dsccif
		Deway = Deway + 0;
		//   dscc - input desewiawizew
		Deway = Deway + 3;
		//   dscc gets pixews evewy othew cycwe
		Deway = Deway + 2;
		//   dscc - input cdc fifo
		Deway = Deway + 12;
		//   dscc gets pixews evewy othew cycwe
		Deway = Deway + 13;
		//   dscc - cdc uncewtainty
		Deway = Deway + 2;
		//   dscc - output cdc fifo
		Deway = Deway + 7;
		//   dscc gets pixews evewy othew cycwe
		Deway = Deway + 3;
		//   dscc - cdc uncewtainty
		Deway = Deway + 2;
		//   dscc - output sewiawizew
		Deway = Deway + 1;
		//   sft
		Deway = Deway + 1;
	} ewse if (pixewFowmat == dm_n422) {
		//   sfw
		Deway = Deway + 2;
		//   dsccif
		Deway = Deway + 1;
		//   dscc - input desewiawizew
		Deway = Deway + 5;
		//  dscc - input cdc fifo
		Deway = Deway + 25;
		//   dscc - cdc uncewtainty
		Deway = Deway + 2;
		//   dscc - output cdc fifo
		Deway = Deway + 10;
		//   dscc - cdc uncewtainty
		Deway = Deway + 2;
		//   dscc - output sewiawizew
		Deway = Deway + 1;
		//   sft
		Deway = Deway + 1;
	} ewse {
		//   sfw
		Deway = Deway + 2;
		//   dsccif
		Deway = Deway + 0;
		//   dscc - input desewiawizew
		Deway = Deway + 3;
		//   dscc - input cdc fifo
		Deway = Deway + 12;
		//   dscc - cdc uncewtainty
		Deway = Deway + 2;
		//   dscc - output cdc fifo
		Deway = Deway + 7;
		//   dscc - output sewiawizew
		Deway = Deway + 1;
		//   dscc - cdc uncewtainty
		Deway = Deway + 2;
		//   sft
		Deway = Deway + 1;
	}

	wetuwn Deway;
}

static boow CawcuwatePwefetchScheduwe(
		stwuct dispway_mode_wib *mode_wib,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
		Pipe *myPipe,
		unsigned int DSCDeway,
		doubwe DPPCWKDewaySubtotaw,
		doubwe DPPCWKDewaySCW,
		doubwe DPPCWKDewaySCWWBOnwy,
		doubwe DPPCWKDewayCNVCFowmatew,
		doubwe DPPCWKDewayCNVCCuwsow,
		doubwe DISPCWKDewaySubtotaw,
		unsigned int ScawewWecoutWidth,
		enum output_fowmat_cwass OutputFowmat,
		unsigned int MaxIntewDCNTiweWepeatews,
		unsigned int VStawtup,
		unsigned int MaxVStawtup,
		unsigned int GPUVMPageTabweWevews,
		boow GPUVMEnabwe,
		HostVM *myHostVM,
		boow DynamicMetadataEnabwe,
		int DynamicMetadataWinesBefoweActiveWequiwed,
		unsigned int DynamicMetadataTwansmittedBytes,
		boow DCCEnabwe,
		doubwe UwgentWatency,
		doubwe UwgentExtwaWatency,
		doubwe TCawc,
		unsigned int PDEAndMetaPTEBytesFwame,
		unsigned int MetaWowByte,
		unsigned int PixewPTEBytesPewWow,
		doubwe PwefetchSouwceWinesY,
		unsigned int SwathWidthY,
		doubwe BytePewPixewDETY,
		doubwe VInitPweFiwwY,
		unsigned int MaxNumSwathY,
		doubwe PwefetchSouwceWinesC,
		doubwe BytePewPixewDETC,
		doubwe VInitPweFiwwC,
		unsigned int MaxNumSwathC,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		doubwe TWait,
		boow XFCEnabwed,
		doubwe XFCWemoteSuwfaceFwipDeway,
		boow PwogwessiveToIntewwaceUnitInOPP,
		doubwe *DSTXAftewScawew,
		doubwe *DSTYAftewScawew,
		doubwe *DestinationWinesFowPwefetch,
		doubwe *PwefetchBandwidth,
		doubwe *DestinationWinesToWequestVMInVBwank,
		doubwe *DestinationWinesToWequestWowInVBwank,
		doubwe *VWatioPwefetchY,
		doubwe *VWatioPwefetchC,
		doubwe *WequiwedPwefetchPixDataBWWuma,
		doubwe *WequiwedPwefetchPixDataBWChwoma,
		unsigned int *VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
		doubwe *Tno_bw,
		doubwe *pwefetch_vmwow_bw,
		unsigned int *swath_width_wuma_ub,
		unsigned int *swath_width_chwoma_ub,
		unsigned int *VUpdateOffsetPix,
		doubwe *VUpdateWidthPix,
		doubwe *VWeadyOffsetPix)
{
	boow MyEwwow = fawse;
	unsigned int DPPCycwes, DISPCWKCycwes;
	doubwe DSTTotawPixewsAftewScawew, TotawWepeatewDewayTime;
	doubwe Tdm, WineTime, Tsetup;
	doubwe dst_y_pwefetch_equ;
	doubwe Tsw_oto;
	doubwe pwefetch_bw_oto;
	doubwe Tvm_oto;
	doubwe Tw0_oto;
	doubwe Tvm_oto_wines;
	doubwe Tw0_oto_wines;
	doubwe Tsw_oto_wines;
	doubwe dst_y_pwefetch_oto;
	doubwe TimeFowFetchingMetaPTE = 0;
	doubwe TimeFowFetchingWowInVBwank = 0;
	doubwe WinesToWequestPwefetchPixewData = 0;
	doubwe HostVMInefficiencyFactow;
	unsigned int HostVMDynamicWevews;

	if (GPUVMEnabwe == twue && myHostVM->Enabwe == twue) {
		HostVMInefficiencyFactow =
				PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData
						/ PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy;
		HostVMDynamicWevews = myHostVM->MaxPageTabweWevews
				- myHostVM->CachedPageTabweWevews;
	} ewse {
		HostVMInefficiencyFactow = 1;
		HostVMDynamicWevews = 0;
	}

	if (myPipe->ScawewEnabwed)
		DPPCycwes = DPPCWKDewaySubtotaw + DPPCWKDewaySCW;
	ewse
		DPPCycwes = DPPCWKDewaySubtotaw + DPPCWKDewaySCWWBOnwy;

	DPPCycwes = DPPCycwes + DPPCWKDewayCNVCFowmatew + myPipe->NumbewOfCuwsows * DPPCWKDewayCNVCCuwsow;

	DISPCWKCycwes = DISPCWKDewaySubtotaw;

	if (myPipe->DPPCWK == 0.0 || myPipe->DISPCWK == 0.0)
		wetuwn twue;

	*DSTXAftewScawew = DPPCycwes * myPipe->PixewCwock / myPipe->DPPCWK
			+ DISPCWKCycwes * myPipe->PixewCwock / myPipe->DISPCWK + DSCDeway;

	if (myPipe->DPPPewPwane > 1)
		*DSTXAftewScawew = *DSTXAftewScawew + ScawewWecoutWidth;

	if (OutputFowmat == dm_420 || (myPipe->IntewwaceEnabwe && PwogwessiveToIntewwaceUnitInOPP))
		*DSTYAftewScawew = 1;
	ewse
		*DSTYAftewScawew = 0;

	DSTTotawPixewsAftewScawew = ((doubwe) (*DSTYAftewScawew * myPipe->HTotaw)) + *DSTXAftewScawew;
	*DSTYAftewScawew = dmw_fwoow(DSTTotawPixewsAftewScawew / myPipe->HTotaw, 1);
	*DSTXAftewScawew = DSTTotawPixewsAftewScawew - ((doubwe) (*DSTYAftewScawew * myPipe->HTotaw));

	*VUpdateOffsetPix = dmw_ceiw(myPipe->HTotaw / 4.0, 1);
	TotawWepeatewDewayTime = MaxIntewDCNTiweWepeatews * (2.0 / myPipe->DPPCWK + 3.0 / myPipe->DISPCWK);
	*VUpdateWidthPix = (14.0 / myPipe->DCFCWKDeepSweep + 12.0 / myPipe->DPPCWK + TotawWepeatewDewayTime)
			* myPipe->PixewCwock;

	*VWeadyOffsetPix = dmw_max(
			150.0 / myPipe->DPPCWK,
			TotawWepeatewDewayTime + 20.0 / myPipe->DCFCWKDeepSweep + 10.0 / myPipe->DPPCWK)
			* myPipe->PixewCwock;

	Tsetup = (doubwe) (*VUpdateOffsetPix + *VUpdateWidthPix + *VWeadyOffsetPix) / myPipe->PixewCwock;

	WineTime = (doubwe) myPipe->HTotaw / myPipe->PixewCwock;

	if (DynamicMetadataEnabwe) {
		doubwe Tdmbf, Tdmec, Tdmsks;

		Tdm = dmw_max(0.0, UwgentExtwaWatency - TCawc);
		Tdmbf = DynamicMetadataTwansmittedBytes / 4.0 / myPipe->DISPCWK;
		Tdmec = WineTime;
		if (DynamicMetadataWinesBefoweActiveWequiwed == -1)
			Tdmsks = myPipe->VBwank * WineTime / 2.0;
		ewse
			Tdmsks = DynamicMetadataWinesBefoweActiveWequiwed * WineTime;
		if (myPipe->IntewwaceEnabwe && !PwogwessiveToIntewwaceUnitInOPP)
			Tdmsks = Tdmsks / 2;
		if (VStawtup * WineTime
				< Tsetup + TWait + UwgentExtwaWatency + Tdmbf + Tdmec + Tdmsks) {
			MyEwwow = twue;
			*VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata = (Tsetup + TWait
					+ UwgentExtwaWatency + Tdmbf + Tdmec + Tdmsks) / WineTime;
		} ewse
			*VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata = 0.0;
	} ewse
		Tdm = 0;

	if (GPUVMEnabwe) {
		if (GPUVMPageTabweWevews >= 3)
			*Tno_bw = UwgentExtwaWatency + UwgentWatency * ((GPUVMPageTabweWevews - 2) * (myHostVM->MaxPageTabweWevews + 1) - 1);
		ewse
			*Tno_bw = 0;
	} ewse if (!DCCEnabwe)
		*Tno_bw = WineTime;
	ewse
		*Tno_bw = WineTime / 4;

	dst_y_pwefetch_equ = VStawtup - dmw_max(TCawc + TWait, XFCWemoteSuwfaceFwipDeway) / WineTime
			- (Tsetup + Tdm) / WineTime
			- (*DSTYAftewScawew + *DSTXAftewScawew / myPipe->HTotaw);

	Tsw_oto = dmw_max(PwefetchSouwceWinesY, PwefetchSouwceWinesC) * WineTime;

	if (myPipe->SouwceScan == dm_howz) {
		*swath_width_wuma_ub = dmw_ceiw(SwathWidthY - 1, myPipe->BwockWidth256BytesY) + myPipe->BwockWidth256BytesY;
		if (myPipe->BwockWidth256BytesC > 0)
			*swath_width_chwoma_ub = dmw_ceiw(SwathWidthY / 2 - 1, myPipe->BwockWidth256BytesC) + myPipe->BwockWidth256BytesC;
	} ewse {
		*swath_width_wuma_ub = dmw_ceiw(SwathWidthY - 1, myPipe->BwockHeight256BytesY) + myPipe->BwockHeight256BytesY;
		if (myPipe->BwockHeight256BytesC > 0)
			*swath_width_chwoma_ub = dmw_ceiw(SwathWidthY / 2 - 1, myPipe->BwockHeight256BytesC) + myPipe->BwockHeight256BytesC;
	}

	pwefetch_bw_oto = (PwefetchSouwceWinesY * *swath_width_wuma_ub * dmw_ceiw(BytePewPixewDETY, 1) + PwefetchSouwceWinesC * *swath_width_chwoma_ub * dmw_ceiw(BytePewPixewDETC, 2)) / Tsw_oto;


	if (GPUVMEnabwe == twue) {
		Tvm_oto = dmw_max(*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / pwefetch_bw_oto,
				dmw_max(UwgentExtwaWatency + UwgentWatency * (GPUVMPageTabweWevews * (HostVMDynamicWevews + 1) - 1),
					WineTime / 4.0));
	} ewse
		Tvm_oto = WineTime / 4.0;

	if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
		Tw0_oto = dmw_max(
				(MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / pwefetch_bw_oto,
				dmw_max(UwgentWatency * (HostVMDynamicWevews + 1), dmw_max(WineTime - Tvm_oto, WineTime / 4)));
	} ewse
		Tw0_oto = (WineTime - Tvm_oto) / 2.0;

	Tvm_oto_wines = dmw_ceiw(4 * Tvm_oto / WineTime, 1) / 4.0;
	Tw0_oto_wines = dmw_ceiw(4 * Tw0_oto / WineTime, 1) / 4.0;
	Tsw_oto_wines = dmw_ceiw(4 * Tsw_oto / WineTime, 1) / 4.0;
	dst_y_pwefetch_oto = Tvm_oto_wines + 2 * Tw0_oto_wines + Tsw_oto_wines + 0.75;

	dst_y_pwefetch_equ = dmw_fwoow(4.0 * (dst_y_pwefetch_equ + 0.125), 1) / 4.0;

	if (dst_y_pwefetch_oto < dst_y_pwefetch_equ)
		*DestinationWinesFowPwefetch = dst_y_pwefetch_oto;
	ewse
		*DestinationWinesFowPwefetch = dst_y_pwefetch_equ;

	// Wimit to pwevent ovewfwow in DST_Y_PWEFETCH wegistew
	*DestinationWinesFowPwefetch = dmw_min(*DestinationWinesFowPwefetch, 63.75);

	dmw_pwint("DMW: VStawtup: %d\n", VStawtup);
	dmw_pwint("DMW: TCawc: %f\n", TCawc);
	dmw_pwint("DMW: TWait: %f\n", TWait);
	dmw_pwint("DMW: XFCWemoteSuwfaceFwipDeway: %f\n", XFCWemoteSuwfaceFwipDeway);
	dmw_pwint("DMW: WineTime: %f\n", WineTime);
	dmw_pwint("DMW: Tsetup: %f\n", Tsetup);
	dmw_pwint("DMW: Tdm: %f\n", Tdm);
	dmw_pwint("DMW: DSTYAftewScawew: %f\n", *DSTYAftewScawew);
	dmw_pwint("DMW: DSTXAftewScawew: %f\n", *DSTXAftewScawew);
	dmw_pwint("DMW: HTotaw: %d\n", myPipe->HTotaw);

	*PwefetchBandwidth = 0;
	*DestinationWinesToWequestVMInVBwank = 0;
	*DestinationWinesToWequestWowInVBwank = 0;
	*VWatioPwefetchY = 0;
	*VWatioPwefetchC = 0;
	*WequiwedPwefetchPixDataBWWuma = 0;
	if (*DestinationWinesFowPwefetch > 1) {
		doubwe PwefetchBandwidth1 = (PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow + 2 * MetaWowByte
				+ 2 * PixewPTEBytesPewWow * HostVMInefficiencyFactow
				+ PwefetchSouwceWinesY * *swath_width_wuma_ub * dmw_ceiw(BytePewPixewDETY, 1)
				+ PwefetchSouwceWinesC * *swath_width_chwoma_ub * dmw_ceiw(BytePewPixewDETC, 2))
				/ (*DestinationWinesFowPwefetch * WineTime - *Tno_bw);

		doubwe PwefetchBandwidth2 = (PDEAndMetaPTEBytesFwame *
				HostVMInefficiencyFactow + PwefetchSouwceWinesY *
				*swath_width_wuma_ub * dmw_ceiw(BytePewPixewDETY, 1) +
				PwefetchSouwceWinesC * *swath_width_chwoma_ub *
				dmw_ceiw(BytePewPixewDETC, 2)) /
				(*DestinationWinesFowPwefetch * WineTime - *Tno_bw - 2 *
				UwgentWatency * (1 + HostVMDynamicWevews));

		doubwe PwefetchBandwidth3 = (2 * MetaWowByte + 2 * PixewPTEBytesPewWow
				* HostVMInefficiencyFactow + PwefetchSouwceWinesY *
				*swath_width_wuma_ub * dmw_ceiw(BytePewPixewDETY, 1) +
				PwefetchSouwceWinesC * *swath_width_chwoma_ub *
				dmw_ceiw(BytePewPixewDETC, 2)) /
				(*DestinationWinesFowPwefetch * WineTime -
				UwgentExtwaWatency - UwgentWatency * (GPUVMPageTabweWevews
				* (HostVMDynamicWevews + 1) - 1));

		doubwe PwefetchBandwidth4 = (PwefetchSouwceWinesY * *swath_width_wuma_ub *
				dmw_ceiw(BytePewPixewDETY, 1) + PwefetchSouwceWinesC *
				*swath_width_chwoma_ub * dmw_ceiw(BytePewPixewDETC, 2)) /
				(*DestinationWinesFowPwefetch * WineTime -
				UwgentExtwaWatency - UwgentWatency * (GPUVMPageTabweWevews
				* (HostVMDynamicWevews + 1) - 1) - 2 * UwgentWatency *
				(1 + HostVMDynamicWevews));

		if (VStawtup == MaxVStawtup && (PwefetchBandwidth1 > 4 * pwefetch_bw_oto) && (*DestinationWinesFowPwefetch - dmw_ceiw(Tsw_oto_wines, 1) / 4.0 - 0.75) * WineTime - *Tno_bw > 0) {
			PwefetchBandwidth1 = (PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow + 2 * MetaWowByte + 2 * PixewPTEBytesPewWow * HostVMInefficiencyFactow) / ((*DestinationWinesFowPwefetch - dmw_ceiw(Tsw_oto_wines, 1) / 4.0 - 0.75) * WineTime - *Tno_bw);
		}
		if (*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / PwefetchBandwidth1 >= UwgentExtwaWatency + UwgentWatency * (GPUVMPageTabweWevews * (HostVMDynamicWevews + 1) - 1) && (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / PwefetchBandwidth1 >= UwgentWatency * (1 + HostVMDynamicWevews)) {
			*PwefetchBandwidth = PwefetchBandwidth1;
		} ewse if (*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / PwefetchBandwidth2 >= UwgentExtwaWatency + UwgentWatency * (GPUVMPageTabweWevews * (HostVMDynamicWevews + 1) - 1) && (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / PwefetchBandwidth2 < UwgentWatency * (1 + HostVMDynamicWevews)) {
			*PwefetchBandwidth = PwefetchBandwidth2;
		} ewse if (*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / PwefetchBandwidth3 < UwgentExtwaWatency + UwgentWatency * (GPUVMPageTabweWevews * (HostVMDynamicWevews + 1) - 1) && (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / PwefetchBandwidth3 >= UwgentWatency * (1 + HostVMDynamicWevews)) {
			*PwefetchBandwidth = PwefetchBandwidth3;
		} ewse {
			*PwefetchBandwidth = PwefetchBandwidth4;
		}

		if (GPUVMEnabwe) {
			TimeFowFetchingMetaPTE = dmw_max(*Tno_bw + (doubwe) PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / *PwefetchBandwidth,
					dmw_max(UwgentExtwaWatency + UwgentWatency * (GPUVMPageTabweWevews * (HostVMDynamicWevews + 1) - 1), WineTime / 4));
		} ewse {
// 5/30/2018 - This was an optimization wequested fwom Sy but now NumbewOfCuwsows is no wongew a factow
//             so if this needs to be weinstated, then it shouwd be officiawwy done in the VBA code as weww.
//			if (mode_wib->NumbewOfCuwsows > 0 || XFCEnabwed)
				TimeFowFetchingMetaPTE = WineTime / 4;
//			ewse
//				TimeFowFetchingMetaPTE = 0.0;
		}

		if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
			TimeFowFetchingWowInVBwank =
					dmw_max(
							(MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow)
									/ *PwefetchBandwidth,
							dmw_max(
									UwgentWatency * (1 + HostVMDynamicWevews),
									dmw_max(
											(WineTime
													- TimeFowFetchingMetaPTE) / 2.0,
											WineTime
													/ 4.0)));
		} ewse {
// See note above dated 5/30/2018
//			if (NumbewOfCuwsows > 0 || XFCEnabwed)
				TimeFowFetchingWowInVBwank = (WineTime - TimeFowFetchingMetaPTE) / 2.0;
//			ewse // TODO: Did someone ewse add this??
//				TimeFowFetchingWowInVBwank = 0.0;
		}

		*DestinationWinesToWequestVMInVBwank = dmw_ceiw(4.0 * TimeFowFetchingMetaPTE / WineTime, 1.0) / 4.0;

		*DestinationWinesToWequestWowInVBwank = dmw_ceiw(4.0 * TimeFowFetchingWowInVBwank / WineTime, 1.0) / 4.0;

		WinesToWequestPwefetchPixewData = *DestinationWinesFowPwefetch
// See note above dated 5/30/2018
//						- ((NumbewOfCuwsows > 0 || GPUVMEnabwe || DCCEnabwe) ?
						- ((GPUVMEnabwe || DCCEnabwe) ?
								(*DestinationWinesToWequestVMInVBwank + 2 * *DestinationWinesToWequestWowInVBwank) :
								0.0); // TODO: Did someone ewse add this??

		if (WinesToWequestPwefetchPixewData > 0) {

			*VWatioPwefetchY = (doubwe) PwefetchSouwceWinesY
					/ WinesToWequestPwefetchPixewData;
			*VWatioPwefetchY = dmw_max(*VWatioPwefetchY, 1.0);
			if ((SwathHeightY > 4) && (VInitPweFiwwY > 3)) {
				if (WinesToWequestPwefetchPixewData > (VInitPweFiwwY - 3.0) / 2.0) {
					*VWatioPwefetchY =
							dmw_max(
									(doubwe) PwefetchSouwceWinesY
											/ WinesToWequestPwefetchPixewData,
									(doubwe) MaxNumSwathY
											* SwathHeightY
											/ (WinesToWequestPwefetchPixewData
													- (VInitPweFiwwY
															- 3.0)
															/ 2.0));
					*VWatioPwefetchY = dmw_max(*VWatioPwefetchY, 1.0);
				} ewse {
					MyEwwow = twue;
					*VWatioPwefetchY = 0;
				}
			}

			*VWatioPwefetchC = (doubwe) PwefetchSouwceWinesC
					/ WinesToWequestPwefetchPixewData;
			*VWatioPwefetchC = dmw_max(*VWatioPwefetchC, 1.0);

			if ((SwathHeightC > 4)) {
				if (WinesToWequestPwefetchPixewData > (VInitPweFiwwC - 3.0) / 2.0) {
					*VWatioPwefetchC =
							dmw_max(
									*VWatioPwefetchC,
									(doubwe) MaxNumSwathC
											* SwathHeightC
											/ (WinesToWequestPwefetchPixewData
													- (VInitPweFiwwC
															- 3.0)
															/ 2.0));
					*VWatioPwefetchC = dmw_max(*VWatioPwefetchC, 1.0);
				} ewse {
					MyEwwow = twue;
					*VWatioPwefetchC = 0;
				}
			}

			*WequiwedPwefetchPixDataBWWuma = myPipe->DPPPewPwane
					* (doubwe) PwefetchSouwceWinesY / WinesToWequestPwefetchPixewData
					* dmw_ceiw(BytePewPixewDETY, 1)
					* *swath_width_wuma_ub / WineTime;
			*WequiwedPwefetchPixDataBWChwoma = myPipe->DPPPewPwane
					* (doubwe) PwefetchSouwceWinesC / WinesToWequestPwefetchPixewData
					* dmw_ceiw(BytePewPixewDETC, 2)
					* *swath_width_chwoma_ub / WineTime;
		} ewse {
			MyEwwow = twue;
			*VWatioPwefetchY = 0;
			*VWatioPwefetchC = 0;
			*WequiwedPwefetchPixDataBWWuma = 0;
			*WequiwedPwefetchPixDataBWChwoma = 0;
		}

		dmw_pwint("DMW: Tvm: %fus\n", TimeFowFetchingMetaPTE);
		dmw_pwint("DMW: Tw0: %fus\n", TimeFowFetchingWowInVBwank);
		dmw_pwint("DMW: Tsw: %fus\n", (doubwe)(*DestinationWinesFowPwefetch) * WineTime - TimeFowFetchingMetaPTE - TimeFowFetchingWowInVBwank);
		dmw_pwint("DMW: Tpwe: %fus\n", (doubwe)(*DestinationWinesFowPwefetch) * WineTime);
		dmw_pwint("DMW: wow_bytes = dpte_wow_bytes (pew_pipe) = PixewPTEBytesPewWow = : %d\n", PixewPTEBytesPewWow);

	} ewse {
		MyEwwow = twue;
	}

	{
		doubwe pwefetch_vm_bw;
		doubwe pwefetch_wow_bw;

		if (PDEAndMetaPTEBytesFwame == 0) {
			pwefetch_vm_bw = 0;
		} ewse if (*DestinationWinesToWequestVMInVBwank > 0) {
			pwefetch_vm_bw = PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / (*DestinationWinesToWequestVMInVBwank * WineTime);
		} ewse {
			pwefetch_vm_bw = 0;
			MyEwwow = twue;
		}
		if (MetaWowByte + PixewPTEBytesPewWow == 0) {
			pwefetch_wow_bw = 0;
		} ewse if (*DestinationWinesToWequestWowInVBwank > 0) {
			pwefetch_wow_bw = (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / (*DestinationWinesToWequestWowInVBwank * WineTime);
		} ewse {
			pwefetch_wow_bw = 0;
			MyEwwow = twue;
		}

		*pwefetch_vmwow_bw = dmw_max(pwefetch_vm_bw, pwefetch_wow_bw);
	}

	if (MyEwwow) {
		*PwefetchBandwidth = 0;
		TimeFowFetchingMetaPTE = 0;
		TimeFowFetchingWowInVBwank = 0;
		*DestinationWinesToWequestVMInVBwank = 0;
		*DestinationWinesToWequestWowInVBwank = 0;
		*DestinationWinesFowPwefetch = 0;
		WinesToWequestPwefetchPixewData = 0;
		*VWatioPwefetchY = 0;
		*VWatioPwefetchC = 0;
		*WequiwedPwefetchPixDataBWWuma = 0;
		*WequiwedPwefetchPixDataBWChwoma = 0;
	}

	wetuwn MyEwwow;
}

static doubwe WoundToDFSGwanuwawityUp(doubwe Cwock, doubwe VCOSpeed)
{
	wetuwn VCOSpeed * 4 / dmw_fwoow(VCOSpeed * 4 / Cwock, 1);
}

static doubwe WoundToDFSGwanuwawityDown(doubwe Cwock, doubwe VCOSpeed)
{
	wetuwn VCOSpeed * 4 / dmw_ceiw(VCOSpeed * 4 / Cwock, 1);
}

static doubwe CawcuwateDCCConfiguwation(
		boow DCCEnabwed,
		boow DCCPwogwammingAssumesScanDiwectionUnknown,
		unsigned int ViewpowtWidth,
		unsigned int ViewpowtHeight,
		unsigned int DETBuffewSize,
		unsigned int WequestHeight256Byte,
		unsigned int SwathHeight,
		enum dm_swizzwe_mode TiwingFowmat,
		unsigned int BytePewPixew,
		enum scan_diwection_cwass ScanOwientation,
		unsigned int *MaxUncompwessedBwock,
		unsigned int *MaxCompwessedBwock,
		unsigned int *Independent64ByteBwock)
{
	doubwe MaximumDCCCompwessionSuwface = 0.0;
	enum {
		WEQ_256Bytes,
		WEQ_128BytesNonContiguous,
		WEQ_128BytesContiguous,
		WEQ_NA
	} Wequest = WEQ_NA;

	if (DCCEnabwed == twue) {
		if (DCCPwogwammingAssumesScanDiwectionUnknown == twue) {
			if (DETBuffewSize >= WequestHeight256Byte * ViewpowtWidth * BytePewPixew
					&& DETBuffewSize
							>= 256 / WequestHeight256Byte
									* ViewpowtHeight) {
				Wequest = WEQ_256Bytes;
			} ewse if ((DETBuffewSize
					< WequestHeight256Byte * ViewpowtWidth * BytePewPixew
					&& (BytePewPixew == 2 || BytePewPixew == 4))
					|| (DETBuffewSize
							< 256 / WequestHeight256Byte
									* ViewpowtHeight
							&& BytePewPixew == 8
							&& (TiwingFowmat == dm_sw_4kb_d
									|| TiwingFowmat
											== dm_sw_4kb_d_x
									|| TiwingFowmat
											== dm_sw_vaw_d
									|| TiwingFowmat
											== dm_sw_vaw_d_x
									|| TiwingFowmat
											== dm_sw_64kb_d
									|| TiwingFowmat
											== dm_sw_64kb_d_x
									|| TiwingFowmat
											== dm_sw_64kb_d_t
									|| TiwingFowmat
											== dm_sw_64kb_w_x))) {
				Wequest = WEQ_128BytesNonContiguous;
			} ewse {
				Wequest = WEQ_128BytesContiguous;
			}
		} ewse {
			if (BytePewPixew == 1) {
				if (ScanOwientation == dm_vewt || SwathHeight == 16) {
					Wequest = WEQ_256Bytes;
				} ewse {
					Wequest = WEQ_128BytesContiguous;
				}
			} ewse if (BytePewPixew == 2) {
				if ((ScanOwientation == dm_vewt && SwathHeight == 16) || (ScanOwientation != dm_vewt && SwathHeight == 8)) {
					Wequest = WEQ_256Bytes;
				} ewse if (ScanOwientation == dm_vewt) {
					Wequest = WEQ_128BytesContiguous;
				} ewse {
					Wequest = WEQ_128BytesNonContiguous;
				}
			} ewse if (BytePewPixew == 4) {
				if (SwathHeight == 8) {
					Wequest = WEQ_256Bytes;
				} ewse if (ScanOwientation == dm_vewt) {
					Wequest = WEQ_128BytesContiguous;
				} ewse {
					Wequest = WEQ_128BytesNonContiguous;
				}
			} ewse if (BytePewPixew == 8) {
				if (TiwingFowmat == dm_sw_4kb_d || TiwingFowmat == dm_sw_4kb_d_x
						|| TiwingFowmat == dm_sw_vaw_d
						|| TiwingFowmat == dm_sw_vaw_d_x
						|| TiwingFowmat == dm_sw_64kb_d
						|| TiwingFowmat == dm_sw_64kb_d_x
						|| TiwingFowmat == dm_sw_64kb_d_t
						|| TiwingFowmat == dm_sw_64kb_w_x) {
					if ((ScanOwientation == dm_vewt && SwathHeight == 8)
							|| (ScanOwientation != dm_vewt
									&& SwathHeight == 4)) {
						Wequest = WEQ_256Bytes;
					} ewse if (ScanOwientation != dm_vewt) {
						Wequest = WEQ_128BytesContiguous;
					} ewse {
						Wequest = WEQ_128BytesNonContiguous;
					}
				} ewse {
					if (ScanOwientation != dm_vewt || SwathHeight == 8) {
						Wequest = WEQ_256Bytes;
					} ewse {
						Wequest = WEQ_128BytesContiguous;
					}
				}
			}
		}
	} ewse {
		Wequest = WEQ_NA;
	}

	if (Wequest == WEQ_256Bytes) {
		*MaxUncompwessedBwock = 256;
		*MaxCompwessedBwock = 256;
		*Independent64ByteBwock = fawse;
		MaximumDCCCompwessionSuwface = 4.0;
	} ewse if (Wequest == WEQ_128BytesContiguous) {
		*MaxUncompwessedBwock = 128;
		*MaxCompwessedBwock = 128;
		*Independent64ByteBwock = fawse;
		MaximumDCCCompwessionSuwface = 2.0;
	} ewse if (Wequest == WEQ_128BytesNonContiguous) {
		*MaxUncompwessedBwock = 256;
		*MaxCompwessedBwock = 64;
		*Independent64ByteBwock = twue;
		MaximumDCCCompwessionSuwface = 4.0;
	} ewse {
		*MaxUncompwessedBwock = 0;
		*MaxCompwessedBwock = 0;
		*Independent64ByteBwock = 0;
		MaximumDCCCompwessionSuwface = 0.0;
	}

	wetuwn MaximumDCCCompwessionSuwface;
}

static doubwe CawcuwatePwefetchSouwceWines(
		stwuct dispway_mode_wib *mode_wib,
		doubwe VWatio,
		doubwe vtaps,
		boow Intewwace,
		boow PwogwessiveToIntewwaceUnitInOPP,
		unsigned int SwathHeight,
		unsigned int ViewpowtYStawt,
		doubwe *VInitPweFiww,
		unsigned int *MaxNumSwath)
{
	unsigned int MaxPawtiawSwath;

	if (PwogwessiveToIntewwaceUnitInOPP)
		*VInitPweFiww = dmw_fwoow((VWatio + vtaps + 1) / 2.0, 1);
	ewse
		*VInitPweFiww = dmw_fwoow((VWatio + vtaps + 1 + Intewwace * 0.5 * VWatio) / 2.0, 1);

	if (!mode_wib->vba.IgnoweViewpowtPositioning) {

		*MaxNumSwath = dmw_ceiw((*VInitPweFiww - 1.0) / SwathHeight, 1) + 1.0;

		if (*VInitPweFiww > 1.0)
			MaxPawtiawSwath = (unsigned int) (*VInitPweFiww - 2) % SwathHeight;
		ewse
			MaxPawtiawSwath = (unsigned int) (*VInitPweFiww + SwathHeight - 2)
					% SwathHeight;
		MaxPawtiawSwath = dmw_max(1U, MaxPawtiawSwath);

	} ewse {

		if (ViewpowtYStawt != 0)
			dmw_pwint(
					"WAWNING DMW: using viewpowt y position of 0 even though actuaw viewpowt y position is non-zewo in pwefetch souwce wines cawcuwation\n");

		*MaxNumSwath = dmw_ceiw(*VInitPweFiww / SwathHeight, 1);

		if (*VInitPweFiww > 1.0)
			MaxPawtiawSwath = (unsigned int) (*VInitPweFiww - 1) % SwathHeight;
		ewse
			MaxPawtiawSwath = (unsigned int) (*VInitPweFiww + SwathHeight - 1)
					% SwathHeight;
	}

	wetuwn *MaxNumSwath * SwathHeight + MaxPawtiawSwath;
}

static unsigned int CawcuwateVMAndWowBytes(
		stwuct dispway_mode_wib *mode_wib,
		boow DCCEnabwe,
		unsigned int BwockHeight256Bytes,
		unsigned int BwockWidth256Bytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int SuwfaceTiwing,
		unsigned int BytePewPixew,
		enum scan_diwection_cwass ScanDiwection,
		unsigned int ViewpowtWidth,
		unsigned int ViewpowtHeight,
		unsigned int SwathWidth,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		unsigned int HostVMMaxPageTabweWevews,
		unsigned int HostVMCachedPageTabweWevews,
		unsigned int VMMPageSize,
		unsigned int PTEBuffewSizeInWequests,
		unsigned int Pitch,
		unsigned int DCCMetaPitch,
		unsigned int *MacwoTiweWidth,
		unsigned int *MetaWowByte,
		unsigned int *PixewPTEBytesPewWow,
		boow *PTEBuffewSizeNotExceeded,
		unsigned int *dpte_wow_width_ub,
		unsigned int *dpte_wow_height,
		unsigned int *MetaWequestWidth,
		unsigned int *MetaWequestHeight,
		unsigned int *meta_wow_width,
		unsigned int *meta_wow_height,
		unsigned int *vm_gwoup_bytes,
		unsigned int *dpte_gwoup_bytes,
		unsigned int *PixewPTEWeqWidth,
		unsigned int *PixewPTEWeqHeight,
		unsigned int *PTEWequestSize,
		unsigned int *DPDE0BytesFwame,
		unsigned int *MetaPTEBytesFwame)
{
	unsigned int MPDEBytesFwame;
	unsigned int DCCMetaSuwfaceBytes;
	unsigned int MacwoTiweSizeBytes;
	unsigned int MacwoTiweHeight;
	unsigned int ExtwaDPDEBytesFwame;
	unsigned int PDEAndMetaPTEBytesFwame;
	unsigned int PixewPTEWeqHeightPTEs = 0;

	if (DCCEnabwe == twue) {
		*MetaWequestHeight = 8 * BwockHeight256Bytes;
		*MetaWequestWidth = 8 * BwockWidth256Bytes;
		if (ScanDiwection == dm_howz) {
			*meta_wow_height = *MetaWequestHeight;
			*meta_wow_width = dmw_ceiw((doubwe) SwathWidth - 1, *MetaWequestWidth)
					+ *MetaWequestWidth;
			*MetaWowByte = *meta_wow_width * *MetaWequestHeight * BytePewPixew / 256.0;
		} ewse {
			*meta_wow_height = *MetaWequestWidth;
			*meta_wow_width = dmw_ceiw((doubwe) SwathWidth - 1, *MetaWequestHeight)
					+ *MetaWequestHeight;
			*MetaWowByte = *meta_wow_width * *MetaWequestWidth * BytePewPixew / 256.0;
		}
		if (ScanDiwection == dm_howz) {
			DCCMetaSuwfaceBytes = DCCMetaPitch
					* (dmw_ceiw(ViewpowtHeight - 1, 64 * BwockHeight256Bytes)
							+ 64 * BwockHeight256Bytes) * BytePewPixew
					/ 256;
		} ewse {
			DCCMetaSuwfaceBytes = DCCMetaPitch
					* (dmw_ceiw(
							(doubwe) ViewpowtHeight - 1,
							64 * BwockHeight256Bytes)
							+ 64 * BwockHeight256Bytes) * BytePewPixew
					/ 256;
		}
		if (GPUVMEnabwe == twue) {
			*MetaPTEBytesFwame = (dmw_ceiw(
					(doubwe) (DCCMetaSuwfaceBytes - VMMPageSize)
							/ (8 * VMMPageSize),
					1) + 1) * 64;
			MPDEBytesFwame = 128 * ((mode_wib->vba.GPUVMMaxPageTabweWevews + 1) * (mode_wib->vba.HostVMMaxPageTabweWevews + 1) - 2);
		} ewse {
			*MetaPTEBytesFwame = 0;
			MPDEBytesFwame = 0;
		}
	} ewse {
		*MetaPTEBytesFwame = 0;
		MPDEBytesFwame = 0;
		*MetaWowByte = 0;
	}

	if (SuwfaceTiwing == dm_sw_wineaw || SuwfaceTiwing == dm_sw_gfx7_2d_thin_gw || SuwfaceTiwing == dm_sw_gfx7_2d_thin_w_vp) {
		MacwoTiweSizeBytes = 256;
		MacwoTiweHeight = BwockHeight256Bytes;
	} ewse if (SuwfaceTiwing == dm_sw_4kb_s || SuwfaceTiwing == dm_sw_4kb_s_x
			|| SuwfaceTiwing == dm_sw_4kb_d || SuwfaceTiwing == dm_sw_4kb_d_x) {
		MacwoTiweSizeBytes = 4096;
		MacwoTiweHeight = 4 * BwockHeight256Bytes;
	} ewse if (SuwfaceTiwing == dm_sw_64kb_s || SuwfaceTiwing == dm_sw_64kb_s_t
			|| SuwfaceTiwing == dm_sw_64kb_s_x || SuwfaceTiwing == dm_sw_64kb_d
			|| SuwfaceTiwing == dm_sw_64kb_d_t || SuwfaceTiwing == dm_sw_64kb_d_x
			|| SuwfaceTiwing == dm_sw_64kb_w_x) {
		MacwoTiweSizeBytes = 65536;
		MacwoTiweHeight = 16 * BwockHeight256Bytes;
	} ewse {
		MacwoTiweSizeBytes = 262144;
		MacwoTiweHeight = 32 * BwockHeight256Bytes;
	}
	*MacwoTiweWidth = MacwoTiweSizeBytes / BytePewPixew / MacwoTiweHeight;

	if (GPUVMEnabwe == twue && (mode_wib->vba.GPUVMMaxPageTabweWevews + 1) * (mode_wib->vba.HostVMMaxPageTabweWevews + 1) > 2) {
		if (ScanDiwection == dm_howz) {
			*DPDE0BytesFwame = 64 * (dmw_ceiw(((Pitch * (dmw_ceiw(ViewpowtHeight - 1, MacwoTiweHeight) + MacwoTiweHeight) * BytePewPixew) - MacwoTiweSizeBytes) / (8 * 2097152), 1) + 1);
		} ewse {
			*DPDE0BytesFwame = 64 * (dmw_ceiw(((Pitch * (dmw_ceiw((doubwe) SwathWidth - 1, MacwoTiweHeight) + MacwoTiweHeight) * BytePewPixew) - MacwoTiweSizeBytes) / (8 * 2097152), 1) + 1);
		}
		ExtwaDPDEBytesFwame = 128 * ((mode_wib->vba.GPUVMMaxPageTabweWevews + 1) * (mode_wib->vba.HostVMMaxPageTabweWevews + 1) - 3);
	} ewse {
		*DPDE0BytesFwame = 0;
		ExtwaDPDEBytesFwame = 0;
	}

	PDEAndMetaPTEBytesFwame = *MetaPTEBytesFwame + MPDEBytesFwame + *DPDE0BytesFwame
			+ ExtwaDPDEBytesFwame;

	if (HostVMEnabwe == twue) {
		PDEAndMetaPTEBytesFwame = PDEAndMetaPTEBytesFwame * (1 + 8 * (HostVMMaxPageTabweWevews - HostVMCachedPageTabweWevews));
	}

	if (GPUVMEnabwe == twue) {
		doubwe FwactionOfPTEWetuwnDwop;

		if (SuwfaceTiwing == dm_sw_wineaw) {
			PixewPTEWeqHeightPTEs = 1;
			*PixewPTEWeqHeight = 1;
			*PixewPTEWeqWidth = 8.0 * VMMPageSize / BytePewPixew;
			*PTEWequestSize = 64;
			FwactionOfPTEWetuwnDwop = 0;
		} ewse if (MacwoTiweSizeBytes == 4096) {
			PixewPTEWeqHeightPTEs = 1;
			*PixewPTEWeqHeight = MacwoTiweHeight;
			*PixewPTEWeqWidth = 8 * *MacwoTiweWidth;
			*PTEWequestSize = 64;
			if (ScanDiwection == dm_howz)
				FwactionOfPTEWetuwnDwop = 0;
			ewse
				FwactionOfPTEWetuwnDwop = 7 / 8;
		} ewse if (VMMPageSize == 4096 && MacwoTiweSizeBytes > 4096) {
			PixewPTEWeqHeightPTEs = 16;
			*PixewPTEWeqHeight = 16 * BwockHeight256Bytes;
			*PixewPTEWeqWidth = 16 * BwockWidth256Bytes;
			*PTEWequestSize = 128;
			FwactionOfPTEWetuwnDwop = 0;
		} ewse {
			PixewPTEWeqHeightPTEs = 1;
			*PixewPTEWeqHeight = MacwoTiweHeight;
			*PixewPTEWeqWidth = 8 * *MacwoTiweWidth;
			*PTEWequestSize = 64;
			FwactionOfPTEWetuwnDwop = 0;
		}

		if (SuwfaceTiwing == dm_sw_wineaw) {
			*dpte_wow_height = dmw_min(128,
					1 << (unsigned int) dmw_fwoow(
						dmw_wog2(
							(doubwe) PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch),
						1));
			*dpte_wow_width_ub = (dmw_ceiw((doubwe) (Pitch * *dpte_wow_height - 1) / *PixewPTEWeqWidth, 1) + 1) * *PixewPTEWeqWidth;
			*PixewPTEBytesPewWow = *dpte_wow_width_ub / *PixewPTEWeqWidth * *PTEWequestSize;
		} ewse if (ScanDiwection == dm_howz) {
			*dpte_wow_height = *PixewPTEWeqHeight;
			*dpte_wow_width_ub = (dmw_ceiw((doubwe) (SwathWidth - 1) / *PixewPTEWeqWidth, 1) + 1) * *PixewPTEWeqWidth;
			*PixewPTEBytesPewWow = *dpte_wow_width_ub / *PixewPTEWeqWidth * *PTEWequestSize;
		} ewse {
			*dpte_wow_height = dmw_min(*PixewPTEWeqWidth, *MacwoTiweWidth);
			*dpte_wow_width_ub = (dmw_ceiw((doubwe) (SwathWidth - 1) / *PixewPTEWeqHeight, 1) + 1) * *PixewPTEWeqHeight;
			*PixewPTEBytesPewWow = *dpte_wow_width_ub / *PixewPTEWeqHeight * *PTEWequestSize;
		}
		if (*PixewPTEBytesPewWow * (1 - FwactionOfPTEWetuwnDwop)
				<= 64 * PTEBuffewSizeInWequests) {
			*PTEBuffewSizeNotExceeded = twue;
		} ewse {
			*PTEBuffewSizeNotExceeded = fawse;
		}
	} ewse {
		*PixewPTEBytesPewWow = 0;
		*PTEBuffewSizeNotExceeded = twue;
	}
	dmw_pwint("DMW: vm_bytes = meta_pte_bytes_pew_fwame (pew_pipe) = MetaPTEBytesFwame = : %d\n", *MetaPTEBytesFwame);

	if (HostVMEnabwe == twue) {
		*PixewPTEBytesPewWow = *PixewPTEBytesPewWow * (1 + 8 * (HostVMMaxPageTabweWevews - HostVMCachedPageTabweWevews));
	}

	if (HostVMEnabwe == twue) {
		*vm_gwoup_bytes = 512;
		*dpte_gwoup_bytes = 512;
	} ewse if (GPUVMEnabwe == twue) {
		*vm_gwoup_bytes = 2048;
		if (SuwfaceTiwing != dm_sw_wineaw && PixewPTEWeqHeightPTEs == 1 && ScanDiwection != dm_howz) {
			*dpte_gwoup_bytes = 512;
		} ewse {
			*dpte_gwoup_bytes = 2048;
		}
	} ewse {
		*vm_gwoup_bytes = 0;
		*dpte_gwoup_bytes = 0;
	}

	wetuwn PDEAndMetaPTEBytesFwame;
}

static void DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation(
		stwuct dispway_mode_wib *mode_wib)
{
	stwuct vba_vaws_st *wocaws = &mode_wib->vba;
	unsigned int j, k;

	mode_wib->vba.WwitebackDISPCWK = 0.0;
	mode_wib->vba.DISPCWKWithWamping = 0;
	mode_wib->vba.DISPCWKWithoutWamping = 0;
	mode_wib->vba.GwobawDPPCWK = 0.0;

	// DISPCWK and DPPCWK Cawcuwation
	//
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.WwitebackEnabwe[k]) {
			mode_wib->vba.WwitebackDISPCWK =
					dmw_max(
							mode_wib->vba.WwitebackDISPCWK,
							CawcuwateWwiteBackDISPCWK(
									mode_wib->vba.WwitebackPixewFowmat[k],
									mode_wib->vba.PixewCwock[k],
									mode_wib->vba.WwitebackHWatio[k],
									mode_wib->vba.WwitebackVWatio[k],
									mode_wib->vba.WwitebackWumaHTaps[k],
									mode_wib->vba.WwitebackWumaVTaps[k],
									mode_wib->vba.WwitebackChwomaHTaps[k],
									mode_wib->vba.WwitebackChwomaVTaps[k],
									mode_wib->vba.WwitebackDestinationWidth[k],
									mode_wib->vba.HTotaw[k],
									mode_wib->vba.WwitebackChwomaWineBuffewWidth));
		}
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.HWatio[k] > 1) {
			wocaws->PSCW_THWOUGHPUT_WUMA[k] = dmw_min(
					mode_wib->vba.MaxDCHUBToPSCWThwoughput,
					mode_wib->vba.MaxPSCWToWBThwoughput
							* mode_wib->vba.HWatio[k]
							/ dmw_ceiw(
									mode_wib->vba.htaps[k]
											/ 6.0,
									1));
		} ewse {
			wocaws->PSCW_THWOUGHPUT_WUMA[k] = dmw_min(
					mode_wib->vba.MaxDCHUBToPSCWThwoughput,
					mode_wib->vba.MaxPSCWToWBThwoughput);
		}

		mode_wib->vba.DPPCWKUsingSingweDPPWuma =
				mode_wib->vba.PixewCwock[k]
						* dmw_max(
								mode_wib->vba.vtaps[k] / 6.0
										* dmw_min(
												1.0,
												mode_wib->vba.HWatio[k]),
								dmw_max(
										mode_wib->vba.HWatio[k]
												* mode_wib->vba.VWatio[k]
												/ wocaws->PSCW_THWOUGHPUT_WUMA[k],
										1.0));

		if ((mode_wib->vba.htaps[k] > 6 || mode_wib->vba.vtaps[k] > 6)
				&& mode_wib->vba.DPPCWKUsingSingweDPPWuma
						< 2 * mode_wib->vba.PixewCwock[k]) {
			mode_wib->vba.DPPCWKUsingSingweDPPWuma = 2 * mode_wib->vba.PixewCwock[k];
		}

		if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_420_8
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_420_10)) {
			wocaws->PSCW_THWOUGHPUT_CHWOMA[k] = 0.0;
			wocaws->DPPCWKUsingSingweDPP[k] =
					mode_wib->vba.DPPCWKUsingSingweDPPWuma;
		} ewse {
			if (mode_wib->vba.HWatio[k] > 1) {
				wocaws->PSCW_THWOUGHPUT_CHWOMA[k] =
						dmw_min(
								mode_wib->vba.MaxDCHUBToPSCWThwoughput,
								mode_wib->vba.MaxPSCWToWBThwoughput
										* mode_wib->vba.HWatio[k]
										/ 2
										/ dmw_ceiw(
												mode_wib->vba.HTAPsChwoma[k]
														/ 6.0,
												1.0));
			} ewse {
				wocaws->PSCW_THWOUGHPUT_CHWOMA[k] = dmw_min(
						mode_wib->vba.MaxDCHUBToPSCWThwoughput,
						mode_wib->vba.MaxPSCWToWBThwoughput);
			}
			mode_wib->vba.DPPCWKUsingSingweDPPChwoma =
					mode_wib->vba.PixewCwock[k]
							* dmw_max(
									mode_wib->vba.VTAPsChwoma[k]
											/ 6.0
											* dmw_min(
													1.0,
													mode_wib->vba.HWatio[k]
															/ 2),
									dmw_max(
											mode_wib->vba.HWatio[k]
													* mode_wib->vba.VWatio[k]
													/ 4
													/ wocaws->PSCW_THWOUGHPUT_CHWOMA[k],
											1.0));

			if ((mode_wib->vba.HTAPsChwoma[k] > 6 || mode_wib->vba.VTAPsChwoma[k] > 6)
					&& mode_wib->vba.DPPCWKUsingSingweDPPChwoma
							< 2 * mode_wib->vba.PixewCwock[k]) {
				mode_wib->vba.DPPCWKUsingSingweDPPChwoma = 2
						* mode_wib->vba.PixewCwock[k];
			}

			wocaws->DPPCWKUsingSingweDPP[k] = dmw_max(
					mode_wib->vba.DPPCWKUsingSingweDPPWuma,
					mode_wib->vba.DPPCWKUsingSingweDPPChwoma);
		}
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.BwendingAndTiming[k] != k)
			continue;
		if (mode_wib->vba.ODMCombineEnabwed[k]) {
			mode_wib->vba.DISPCWKWithWamping =
					dmw_max(
							mode_wib->vba.DISPCWKWithWamping,
							mode_wib->vba.PixewCwock[k] / 2
									* (1
											+ mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
													/ 100)
									* (1
											+ mode_wib->vba.DISPCWKWampingMawgin
													/ 100));
			mode_wib->vba.DISPCWKWithoutWamping =
					dmw_max(
							mode_wib->vba.DISPCWKWithoutWamping,
							mode_wib->vba.PixewCwock[k] / 2
									* (1
											+ mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
													/ 100));
		} ewse if (!mode_wib->vba.ODMCombineEnabwed[k]) {
			mode_wib->vba.DISPCWKWithWamping =
					dmw_max(
							mode_wib->vba.DISPCWKWithWamping,
							mode_wib->vba.PixewCwock[k]
									* (1
											+ mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
													/ 100)
									* (1
											+ mode_wib->vba.DISPCWKWampingMawgin
													/ 100));
			mode_wib->vba.DISPCWKWithoutWamping =
					dmw_max(
							mode_wib->vba.DISPCWKWithoutWamping,
							mode_wib->vba.PixewCwock[k]
									* (1
											+ mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
													/ 100));
		}
	}

	mode_wib->vba.DISPCWKWithWamping = dmw_max(
			mode_wib->vba.DISPCWKWithWamping,
			mode_wib->vba.WwitebackDISPCWK);
	mode_wib->vba.DISPCWKWithoutWamping = dmw_max(
			mode_wib->vba.DISPCWKWithoutWamping,
			mode_wib->vba.WwitebackDISPCWK);

	ASSEWT(mode_wib->vba.DISPCWKDPPCWKVCOSpeed != 0);
	mode_wib->vba.DISPCWKWithWampingWoundedToDFSGwanuwawity = WoundToDFSGwanuwawityUp(
			mode_wib->vba.DISPCWKWithWamping,
			mode_wib->vba.DISPCWKDPPCWKVCOSpeed);
	mode_wib->vba.DISPCWKWithoutWampingWoundedToDFSGwanuwawity = WoundToDFSGwanuwawityUp(
			mode_wib->vba.DISPCWKWithoutWamping,
			mode_wib->vba.DISPCWKDPPCWKVCOSpeed);
	mode_wib->vba.MaxDispcwkWoundedToDFSGwanuwawity = WoundToDFSGwanuwawityDown(
			mode_wib->vba.soc.cwock_wimits[mode_wib->vba.soc.num_states - 1].dispcwk_mhz,
			mode_wib->vba.DISPCWKDPPCWKVCOSpeed);
	if (mode_wib->vba.DISPCWKWithoutWampingWoundedToDFSGwanuwawity
			> mode_wib->vba.MaxDispcwkWoundedToDFSGwanuwawity) {
		mode_wib->vba.DISPCWK_cawcuwated =
				mode_wib->vba.DISPCWKWithoutWampingWoundedToDFSGwanuwawity;
	} ewse if (mode_wib->vba.DISPCWKWithWampingWoundedToDFSGwanuwawity
			> mode_wib->vba.MaxDispcwkWoundedToDFSGwanuwawity) {
		mode_wib->vba.DISPCWK_cawcuwated = mode_wib->vba.MaxDispcwkWoundedToDFSGwanuwawity;
	} ewse {
		mode_wib->vba.DISPCWK_cawcuwated =
				mode_wib->vba.DISPCWKWithWampingWoundedToDFSGwanuwawity;
	}
	DTWACE("   dispcwk_mhz (cawcuwated) = %f", mode_wib->vba.DISPCWK_cawcuwated);

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.DPPCWK_cawcuwated[k] = wocaws->DPPCWKUsingSingweDPP[k]
				/ mode_wib->vba.DPPPewPwane[k]
				* (1 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100);
		mode_wib->vba.GwobawDPPCWK = dmw_max(
				mode_wib->vba.GwobawDPPCWK,
				mode_wib->vba.DPPCWK_cawcuwated[k]);
	}
	mode_wib->vba.GwobawDPPCWK = WoundToDFSGwanuwawityUp(
			mode_wib->vba.GwobawDPPCWK,
			mode_wib->vba.DISPCWKDPPCWKVCOSpeed);
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.DPPCWK_cawcuwated[k] = mode_wib->vba.GwobawDPPCWK / 255
				* dmw_ceiw(
						mode_wib->vba.DPPCWK_cawcuwated[k] * 255
								/ mode_wib->vba.GwobawDPPCWK,
						1);
		DTWACE("   dppcwk_mhz[%i] (cawcuwated) = %f", k, mode_wib->vba.DPPCWK_cawcuwated[k]);
	}

	// Uwgent and B P-State/DWAM Cwock Change Watewmawk
	DTWACE("   dcfcwk_mhz         = %f", mode_wib->vba.DCFCWK);
	DTWACE("   wetuwn_bw_to_dcn   = %f", mode_wib->vba.WetuwnBandwidthToDCN);
	DTWACE("   wetuwn_bus_bw      = %f", mode_wib->vba.WetuwnBW);

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		boow MainPwaneDoesODMCombine = fawse;

		if (mode_wib->vba.SouwceScan[k] == dm_howz)
			wocaws->SwathWidthSingweDPPY[k] = mode_wib->vba.ViewpowtWidth[k];
		ewse
			wocaws->SwathWidthSingweDPPY[k] = mode_wib->vba.ViewpowtHeight[k];

		if (mode_wib->vba.ODMCombineEnabwed[k] == dm_odm_combine_mode_2to1)
			MainPwaneDoesODMCombine = twue;
		fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j)
			if (mode_wib->vba.BwendingAndTiming[k] == j
					&& mode_wib->vba.ODMCombineEnabwed[k] == dm_odm_combine_mode_2to1)
				MainPwaneDoesODMCombine = twue;

		if (MainPwaneDoesODMCombine == twue)
			wocaws->SwathWidthY[k] = dmw_min(
					(doubwe) wocaws->SwathWidthSingweDPPY[k],
					dmw_wound(
							mode_wib->vba.HActive[k] / 2.0
									* mode_wib->vba.HWatio[k]));
		ewse
			wocaws->SwathWidthY[k] = wocaws->SwathWidthSingweDPPY[k]
					/ mode_wib->vba.DPPPewPwane[k];
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64) {
			wocaws->BytePewPixewDETY[k] = 8;
			wocaws->BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32) {
			wocaws->BytePewPixewDETY[k] = 4;
			wocaws->BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16 || mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_16) {
			wocaws->BytePewPixewDETY[k] = 2;
			wocaws->BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_8 || mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_8) {
			wocaws->BytePewPixewDETY[k] = 1;
			wocaws->BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8) {
			wocaws->BytePewPixewDETY[k] = 1;
			wocaws->BytePewPixewDETC[k] = 2;
		} ewse { // dm_420_10
			wocaws->BytePewPixewDETY[k] = 4.0 / 3.0;
			wocaws->BytePewPixewDETC[k] = 8.0 / 3.0;
		}
	}

	mode_wib->vba.TotawDataWeadBandwidth = 0.0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		wocaws->WeadBandwidthPwaneWuma[k] = wocaws->SwathWidthSingweDPPY[k]
				* dmw_ceiw(wocaws->BytePewPixewDETY[k], 1)
				/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
				* mode_wib->vba.VWatio[k];
		wocaws->WeadBandwidthPwaneChwoma[k] = wocaws->SwathWidthSingweDPPY[k]
				/ 2 * dmw_ceiw(wocaws->BytePewPixewDETC[k], 2)
				/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
				* mode_wib->vba.VWatio[k] / 2;
		DTWACE(
				"   wead_bw[%i] = %fBps",
				k,
				wocaws->WeadBandwidthPwaneWuma[k]
						+ wocaws->WeadBandwidthPwaneChwoma[k]);
		mode_wib->vba.TotawDataWeadBandwidth += wocaws->WeadBandwidthPwaneWuma[k]
				+ wocaws->WeadBandwidthPwaneChwoma[k];
	}

	// DCFCWK Deep Sweep
	CawcuwateDCFCWKDeepSweep(
		mode_wib,
		mode_wib->vba.NumbewOfActivePwanes,
		wocaws->BytePewPixewDETY,
		wocaws->BytePewPixewDETC,
		mode_wib->vba.VWatio,
		wocaws->SwathWidthY,
		mode_wib->vba.DPPPewPwane,
		mode_wib->vba.HWatio,
		mode_wib->vba.PixewCwock,
		wocaws->PSCW_THWOUGHPUT_WUMA,
		wocaws->PSCW_THWOUGHPUT_CHWOMA,
		wocaws->DPPCWK,
		&mode_wib->vba.DCFCWKDeepSweep);

	// DSCCWK
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if ((mode_wib->vba.BwendingAndTiming[k] != k) || !mode_wib->vba.DSCEnabwed[k]) {
			wocaws->DSCCWK_cawcuwated[k] = 0.0;
		} ewse {
			if (mode_wib->vba.OutputFowmat[k] == dm_420
					|| mode_wib->vba.OutputFowmat[k] == dm_n422)
				mode_wib->vba.DSCFowmatFactow = 2;
			ewse
				mode_wib->vba.DSCFowmatFactow = 1;
			if (mode_wib->vba.ODMCombineEnabwed[k])
				wocaws->DSCCWK_cawcuwated[k] =
						mode_wib->vba.PixewCwockBackEnd[k] / 6
								/ mode_wib->vba.DSCFowmatFactow
								/ (1
										- mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
												/ 100);
			ewse
				wocaws->DSCCWK_cawcuwated[k] =
						mode_wib->vba.PixewCwockBackEnd[k] / 3
								/ mode_wib->vba.DSCFowmatFactow
								/ (1
										- mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
												/ 100);
		}
	}

	// DSC Deway
	// TODO
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		doubwe bpp = mode_wib->vba.OutputBpp[k];
		unsigned int swices = mode_wib->vba.NumbewOfDSCSwices[k];

		if (mode_wib->vba.DSCEnabwed[k] && bpp != 0) {
			if (!mode_wib->vba.ODMCombineEnabwed[k]) {
				wocaws->DSCDeway[k] =
						dscceComputeDeway(
								mode_wib->vba.DSCInputBitPewComponent[k],
								bpp,
								dmw_ceiw(
										(doubwe) mode_wib->vba.HActive[k]
												/ mode_wib->vba.NumbewOfDSCSwices[k],
										1),
								swices,
								mode_wib->vba.OutputFowmat[k])
								+ dscComputeDeway(
										mode_wib->vba.OutputFowmat[k]);
			} ewse {
				wocaws->DSCDeway[k] =
						2
								* (dscceComputeDeway(
										mode_wib->vba.DSCInputBitPewComponent[k],
										bpp,
										dmw_ceiw(
												(doubwe) mode_wib->vba.HActive[k]
														/ mode_wib->vba.NumbewOfDSCSwices[k],
												1),
										swices / 2.0,
										mode_wib->vba.OutputFowmat[k])
										+ dscComputeDeway(
												mode_wib->vba.OutputFowmat[k]));
			}
			wocaws->DSCDeway[k] = wocaws->DSCDeway[k]
					* mode_wib->vba.PixewCwock[k]
					/ mode_wib->vba.PixewCwockBackEnd[k];
		} ewse {
			wocaws->DSCDeway[k] = 0;
		}
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j) // NumbewOfPwanes
			if (j != k && mode_wib->vba.BwendingAndTiming[k] == j
					&& mode_wib->vba.DSCEnabwed[j])
				wocaws->DSCDeway[k] = wocaws->DSCDeway[j];

	// Pwefetch
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		unsigned int PDEAndMetaPTEBytesFwameY;
		unsigned int PixewPTEBytesPewWowY;
		unsigned int MetaWowByteY;
		unsigned int MetaWowByteC;
		unsigned int PDEAndMetaPTEBytesFwameC;
		unsigned int PixewPTEBytesPewWowC;
		boow         PTEBuffewSizeNotExceededY;
		boow         PTEBuffewSizeNotExceededC;

		Cawcuwate256BBwockSizes(
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.SuwfaceTiwing[k],
				dmw_ceiw(wocaws->BytePewPixewDETY[k], 1),
				dmw_ceiw(wocaws->BytePewPixewDETC[k], 2),
				&wocaws->BwockHeight256BytesY[k],
				&wocaws->BwockHeight256BytesC[k],
				&wocaws->BwockWidth256BytesY[k],
				&wocaws->BwockWidth256BytesC[k]);

		wocaws->PwefetchSouwceWinesY[k] = CawcuwatePwefetchSouwceWines(
				mode_wib,
				mode_wib->vba.VWatio[k],
				mode_wib->vba.vtaps[k],
				mode_wib->vba.Intewwace[k],
				mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
				mode_wib->vba.SwathHeightY[k],
				mode_wib->vba.ViewpowtYStawtY[k],
				&wocaws->VInitPweFiwwY[k],
				&wocaws->MaxNumSwathY[k]);

		if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_8)) {
			PDEAndMetaPTEBytesFwameC =
					CawcuwateVMAndWowBytes(
							mode_wib,
							mode_wib->vba.DCCEnabwe[k],
							wocaws->BwockHeight256BytesC[k],
							wocaws->BwockWidth256BytesC[k],
							mode_wib->vba.SouwcePixewFowmat[k],
							mode_wib->vba.SuwfaceTiwing[k],
							dmw_ceiw(
									wocaws->BytePewPixewDETC[k],
									2),
							mode_wib->vba.SouwceScan[k],
							mode_wib->vba.ViewpowtWidth[k] / 2,
							mode_wib->vba.ViewpowtHeight[k] / 2,
							wocaws->SwathWidthY[k] / 2,
							mode_wib->vba.GPUVMEnabwe,
							mode_wib->vba.HostVMEnabwe,
							mode_wib->vba.HostVMMaxPageTabweWevews,
							mode_wib->vba.HostVMCachedPageTabweWevews,
							mode_wib->vba.VMMPageSize,
							mode_wib->vba.PTEBuffewSizeInWequestsChwoma,
							mode_wib->vba.PitchC[k],
							mode_wib->vba.DCCMetaPitchC[k],
							&wocaws->MacwoTiweWidthC[k],
							&MetaWowByteC,
							&PixewPTEBytesPewWowC,
							&PTEBuffewSizeNotExceededC,
							&wocaws->dpte_wow_width_chwoma_ub[k],
							&wocaws->dpte_wow_height_chwoma[k],
							&wocaws->meta_weq_width_chwoma[k],
							&wocaws->meta_weq_height_chwoma[k],
							&wocaws->meta_wow_width_chwoma[k],
							&wocaws->meta_wow_height_chwoma[k],
							&wocaws->vm_gwoup_bytes_chwoma,
							&wocaws->dpte_gwoup_bytes_chwoma,
							&wocaws->PixewPTEWeqWidthC[k],
							&wocaws->PixewPTEWeqHeightC[k],
							&wocaws->PTEWequestSizeC[k],
							&wocaws->dpde0_bytes_pew_fwame_ub_c[k],
							&wocaws->meta_pte_bytes_pew_fwame_ub_c[k]);

			wocaws->PwefetchSouwceWinesC[k] = CawcuwatePwefetchSouwceWines(
					mode_wib,
					mode_wib->vba.VWatio[k] / 2,
					mode_wib->vba.VTAPsChwoma[k],
					mode_wib->vba.Intewwace[k],
					mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
					mode_wib->vba.SwathHeightC[k],
					mode_wib->vba.ViewpowtYStawtC[k],
					&wocaws->VInitPweFiwwC[k],
					&wocaws->MaxNumSwathC[k]);
		} ewse {
			PixewPTEBytesPewWowC = 0;
			PDEAndMetaPTEBytesFwameC = 0;
			MetaWowByteC = 0;
			wocaws->MaxNumSwathC[k] = 0;
			wocaws->PwefetchSouwceWinesC[k] = 0;
			wocaws->PTEBuffewSizeInWequestsFowWuma = mode_wib->vba.PTEBuffewSizeInWequestsWuma + mode_wib->vba.PTEBuffewSizeInWequestsChwoma;
		}

		PDEAndMetaPTEBytesFwameY = CawcuwateVMAndWowBytes(
				mode_wib,
				mode_wib->vba.DCCEnabwe[k],
				wocaws->BwockHeight256BytesY[k],
				wocaws->BwockWidth256BytesY[k],
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.SuwfaceTiwing[k],
				dmw_ceiw(wocaws->BytePewPixewDETY[k], 1),
				mode_wib->vba.SouwceScan[k],
				mode_wib->vba.ViewpowtWidth[k],
				mode_wib->vba.ViewpowtHeight[k],
				wocaws->SwathWidthY[k],
				mode_wib->vba.GPUVMEnabwe,
				mode_wib->vba.HostVMEnabwe,
				mode_wib->vba.HostVMMaxPageTabweWevews,
				mode_wib->vba.HostVMCachedPageTabweWevews,
				mode_wib->vba.VMMPageSize,
				wocaws->PTEBuffewSizeInWequestsFowWuma,
				mode_wib->vba.PitchY[k],
				mode_wib->vba.DCCMetaPitchY[k],
				&wocaws->MacwoTiweWidthY[k],
				&MetaWowByteY,
				&PixewPTEBytesPewWowY,
				&PTEBuffewSizeNotExceededY,
				&wocaws->dpte_wow_width_wuma_ub[k],
				&wocaws->dpte_wow_height[k],
				&wocaws->meta_weq_width[k],
				&wocaws->meta_weq_height[k],
				&wocaws->meta_wow_width[k],
				&wocaws->meta_wow_height[k],
				&wocaws->vm_gwoup_bytes[k],
				&wocaws->dpte_gwoup_bytes[k],
				&wocaws->PixewPTEWeqWidthY[k],
				&wocaws->PixewPTEWeqHeightY[k],
				&wocaws->PTEWequestSizeY[k],
				&wocaws->dpde0_bytes_pew_fwame_ub_w[k],
				&wocaws->meta_pte_bytes_pew_fwame_ub_w[k]);

		wocaws->PixewPTEBytesPewWow[k] = PixewPTEBytesPewWowY + PixewPTEBytesPewWowC;
		wocaws->PDEAndMetaPTEBytesFwame[k] = PDEAndMetaPTEBytesFwameY
				+ PDEAndMetaPTEBytesFwameC;
		wocaws->MetaWowByte[k] = MetaWowByteY + MetaWowByteC;

		CawcuwateActiveWowBandwidth(
				mode_wib->vba.GPUVMEnabwe,
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.VWatio[k],
				mode_wib->vba.DCCEnabwe[k],
				mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
				MetaWowByteY,
				MetaWowByteC,
				wocaws->meta_wow_height[k],
				wocaws->meta_wow_height_chwoma[k],
				PixewPTEBytesPewWowY,
				PixewPTEBytesPewWowC,
				wocaws->dpte_wow_height[k],
				wocaws->dpte_wow_height_chwoma[k],
				&wocaws->meta_wow_bw[k],
				&wocaws->dpte_wow_bw[k]);
	}

	mode_wib->vba.TotawDCCActiveDPP = 0;
	mode_wib->vba.TotawActiveDPP = 0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.TotawActiveDPP = mode_wib->vba.TotawActiveDPP
				+ mode_wib->vba.DPPPewPwane[k];
		if (mode_wib->vba.DCCEnabwe[k])
			mode_wib->vba.TotawDCCActiveDPP = mode_wib->vba.TotawDCCActiveDPP
					+ mode_wib->vba.DPPPewPwane[k];
	}

	mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannew = dmw_max3(
			mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewDataOnwy,
			mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewMixedWithVMData,
			mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewVMDataOnwy);

	mode_wib->vba.UwgentWoundTwipAndOutOfOwdewWatency =
			(mode_wib->vba.WoundTwipPingWatencyCycwes + 32) / mode_wib->vba.DCFCWK
					+ mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannew
							* mode_wib->vba.NumbewOfChannews
							/ mode_wib->vba.WetuwnBW;

	mode_wib->vba.UwgentExtwaWatency = CawcuwateExtwaWatency(
			mode_wib->vba.UwgentWoundTwipAndOutOfOwdewWatency,
			mode_wib->vba.TotawActiveDPP,
			mode_wib->vba.PixewChunkSizeInKByte,
			mode_wib->vba.TotawDCCActiveDPP,
			mode_wib->vba.MetaChunkSize,
			mode_wib->vba.WetuwnBW,
			mode_wib->vba.GPUVMEnabwe,
			mode_wib->vba.HostVMEnabwe,
			mode_wib->vba.NumbewOfActivePwanes,
			mode_wib->vba.DPPPewPwane,
			wocaws->dpte_gwoup_bytes,
			mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
			mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
			mode_wib->vba.HostVMMaxPageTabweWevews,
			mode_wib->vba.HostVMCachedPageTabweWevews);


	mode_wib->vba.TCawc = 24.0 / mode_wib->vba.DCFCWKDeepSweep;

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.BwendingAndTiming[k] == k) {
			if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
				wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][k] =
						mode_wib->vba.WwitebackWatency
								+ CawcuwateWwiteBackDeway(
										mode_wib->vba.WwitebackPixewFowmat[k],
										mode_wib->vba.WwitebackHWatio[k],
										mode_wib->vba.WwitebackVWatio[k],
										mode_wib->vba.WwitebackWumaHTaps[k],
										mode_wib->vba.WwitebackWumaVTaps[k],
										mode_wib->vba.WwitebackChwomaHTaps[k],
										mode_wib->vba.WwitebackChwomaVTaps[k],
										mode_wib->vba.WwitebackDestinationWidth[k])
										/ mode_wib->vba.DISPCWK;
			} ewse
				wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][k] = 0;
			fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j) {
				if (mode_wib->vba.BwendingAndTiming[j] == k
						&& mode_wib->vba.WwitebackEnabwe[j] == twue) {
					wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][k] =
							dmw_max(
									wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][k],
									mode_wib->vba.WwitebackWatency
											+ CawcuwateWwiteBackDeway(
													mode_wib->vba.WwitebackPixewFowmat[j],
													mode_wib->vba.WwitebackHWatio[j],
													mode_wib->vba.WwitebackVWatio[j],
													mode_wib->vba.WwitebackWumaHTaps[j],
													mode_wib->vba.WwitebackWumaVTaps[j],
													mode_wib->vba.WwitebackChwomaHTaps[j],
													mode_wib->vba.WwitebackChwomaVTaps[j],
													mode_wib->vba.WwitebackDestinationWidth[j])
													/ mode_wib->vba.DISPCWK);
				}
			}
		}
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j)
			if (mode_wib->vba.BwendingAndTiming[k] == j)
				wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][k] =
						wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][j];

	mode_wib->vba.VStawtupWines = 13;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		wocaws->MaxVStawtupWines[k] = mode_wib->vba.VTotaw[k] - mode_wib->vba.VActive[k] - dmw_max(1.0, dmw_ceiw(wocaws->WwitebackDeway[mode_wib->vba.VowtageWevew][k] / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]), 1));
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		wocaws->MaximumMaxVStawtupWines = dmw_max(wocaws->MaximumMaxVStawtupWines, wocaws->MaxVStawtupWines[k]);

	// We don't weawwy cawe to itewate between the vawious pwefetch modes
	//mode_wib->vba.PwefetchEWWOW = CawcuwateMinAndMaxPwefetchMode(mode_wib->vba.AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank, &mode_wib->vba.MinPwefetchMode, &mode_wib->vba.MaxPwefetchMode);
	mode_wib->vba.UwgentWatency = dmw_max3(mode_wib->vba.UwgentWatencyPixewDataOnwy, mode_wib->vba.UwgentWatencyPixewMixedWithVMData, mode_wib->vba.UwgentWatencyVMDataOnwy);

	do {
		doubwe MaxTotawWDBandwidth = 0;
		doubwe MaxTotawWDBandwidthNoUwgentBuwst = 0;
		boow DestinationWineTimesFowPwefetchWessThan2 = fawse;
		boow VWatioPwefetchMoweThan4 = fawse;
		doubwe TWait = CawcuwateTWait(
				mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb],
				mode_wib->vba.DWAMCwockChangeWatency,
				mode_wib->vba.UwgentWatency,
				mode_wib->vba.SWEntewPwusExitTime);

		fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
			Pipe   myPipe;
			HostVM myHostVM;

			if (mode_wib->vba.XFCEnabwed[k] == twue) {
				mode_wib->vba.XFCWemoteSuwfaceFwipDeway =
						CawcuwateWemoteSuwfaceFwipDeway(
								mode_wib,
								mode_wib->vba.VWatio[k],
								wocaws->SwathWidthY[k],
								dmw_ceiw(
										wocaws->BytePewPixewDETY[k],
										1),
								mode_wib->vba.HTotaw[k]
										/ mode_wib->vba.PixewCwock[k],
								mode_wib->vba.XFCTSwvVupdateOffset,
								mode_wib->vba.XFCTSwvVupdateWidth,
								mode_wib->vba.XFCTSwvVweadyOffset,
								mode_wib->vba.XFCXBUFWatencyTowewance,
								mode_wib->vba.XFCFiwwBWOvewhead,
								mode_wib->vba.XFCSwvChunkSize,
								mode_wib->vba.XFCBusTwanspowtTime,
								mode_wib->vba.TCawc,
								TWait,
								&mode_wib->vba.SwcActiveDwainWate,
								&mode_wib->vba.TInitXFiww,
								&mode_wib->vba.TswvChk);
			} ewse {
				mode_wib->vba.XFCWemoteSuwfaceFwipDeway = 0;
			}

			myPipe.DPPCWK = wocaws->DPPCWK[k];
			myPipe.DISPCWK = mode_wib->vba.DISPCWK;
			myPipe.PixewCwock = mode_wib->vba.PixewCwock[k];
			myPipe.DCFCWKDeepSweep = mode_wib->vba.DCFCWKDeepSweep;
			myPipe.DPPPewPwane = mode_wib->vba.DPPPewPwane[k];
			myPipe.ScawewEnabwed = mode_wib->vba.ScawewEnabwed[k];
			myPipe.SouwceScan = mode_wib->vba.SouwceScan[k];
			myPipe.BwockWidth256BytesY = wocaws->BwockWidth256BytesY[k];
			myPipe.BwockHeight256BytesY = wocaws->BwockHeight256BytesY[k];
			myPipe.BwockWidth256BytesC = wocaws->BwockWidth256BytesC[k];
			myPipe.BwockHeight256BytesC = wocaws->BwockHeight256BytesC[k];
			myPipe.IntewwaceEnabwe = mode_wib->vba.Intewwace[k];
			myPipe.NumbewOfCuwsows = mode_wib->vba.NumbewOfCuwsows[k];
			myPipe.VBwank = mode_wib->vba.VTotaw[k] - mode_wib->vba.VActive[k];
			myPipe.HTotaw = mode_wib->vba.HTotaw[k];


			myHostVM.Enabwe = mode_wib->vba.HostVMEnabwe;
			myHostVM.MaxPageTabweWevews = mode_wib->vba.HostVMMaxPageTabweWevews;
			myHostVM.CachedPageTabweWevews = mode_wib->vba.HostVMCachedPageTabweWevews;

			mode_wib->vba.EwwowWesuwt[k] =
					CawcuwatePwefetchScheduwe(
							mode_wib,
							mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
							mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
							&myPipe,
							wocaws->DSCDeway[k],
							mode_wib->vba.DPPCWKDewaySubtotaw,
							mode_wib->vba.DPPCWKDewaySCW,
							mode_wib->vba.DPPCWKDewaySCWWBOnwy,
							mode_wib->vba.DPPCWKDewayCNVCFowmatew,
							mode_wib->vba.DPPCWKDewayCNVCCuwsow,
							mode_wib->vba.DISPCWKDewaySubtotaw,
							(unsigned int) (wocaws->SwathWidthY[k]
									/ mode_wib->vba.HWatio[k]),
							mode_wib->vba.OutputFowmat[k],
							mode_wib->vba.MaxIntewDCNTiweWepeatews,
							dmw_min(mode_wib->vba.VStawtupWines, wocaws->MaxVStawtupWines[k]),
							wocaws->MaxVStawtupWines[k],
							mode_wib->vba.GPUVMMaxPageTabweWevews,
							mode_wib->vba.GPUVMEnabwe,
							&myHostVM,
							mode_wib->vba.DynamicMetadataEnabwe[k],
							mode_wib->vba.DynamicMetadataWinesBefoweActiveWequiwed[k],
							mode_wib->vba.DynamicMetadataTwansmittedBytes[k],
							mode_wib->vba.DCCEnabwe[k],
							mode_wib->vba.UwgentWatency,
							mode_wib->vba.UwgentExtwaWatency,
							mode_wib->vba.TCawc,
							wocaws->PDEAndMetaPTEBytesFwame[k],
							wocaws->MetaWowByte[k],
							wocaws->PixewPTEBytesPewWow[k],
							wocaws->PwefetchSouwceWinesY[k],
							wocaws->SwathWidthY[k],
							wocaws->BytePewPixewDETY[k],
							wocaws->VInitPweFiwwY[k],
							wocaws->MaxNumSwathY[k],
							wocaws->PwefetchSouwceWinesC[k],
							wocaws->BytePewPixewDETC[k],
							wocaws->VInitPweFiwwC[k],
							wocaws->MaxNumSwathC[k],
							mode_wib->vba.SwathHeightY[k],
							mode_wib->vba.SwathHeightC[k],
							TWait,
							mode_wib->vba.XFCEnabwed[k],
							mode_wib->vba.XFCWemoteSuwfaceFwipDeway,
							mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
							&wocaws->DSTXAftewScawew[k],
							&wocaws->DSTYAftewScawew[k],
							&wocaws->DestinationWinesFowPwefetch[k],
							&wocaws->PwefetchBandwidth[k],
							&wocaws->DestinationWinesToWequestVMInVBwank[k],
							&wocaws->DestinationWinesToWequestWowInVBwank[k],
							&wocaws->VWatioPwefetchY[k],
							&wocaws->VWatioPwefetchC[k],
							&wocaws->WequiwedPwefetchPixDataBWWuma[k],
							&wocaws->WequiwedPwefetchPixDataBWChwoma[k],
							&wocaws->VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
							&wocaws->Tno_bw[k],
							&wocaws->pwefetch_vmwow_bw[k],
							&wocaws->swath_width_wuma_ub[k],
							&wocaws->swath_width_chwoma_ub[k],
							&mode_wib->vba.VUpdateOffsetPix[k],
							&mode_wib->vba.VUpdateWidthPix[k],
							&mode_wib->vba.VWeadyOffsetPix[k]);
			if (mode_wib->vba.BwendingAndTiming[k] == k) {
				wocaws->VStawtup[k] = dmw_min(
						mode_wib->vba.VStawtupWines,
						wocaws->MaxVStawtupWines[k]);
				if (wocaws->VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata
						!= 0) {
					wocaws->VStawtup[k] =
							wocaws->VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata;
				}
			} ewse {
				wocaws->VStawtup[k] =
						dmw_min(
								mode_wib->vba.VStawtupWines,
								wocaws->MaxVStawtupWines[mode_wib->vba.BwendingAndTiming[k]]);
			}
		}

		fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
			unsigned int m;

			wocaws->cuwsow_bw[k] = 0;
			wocaws->cuwsow_bw_pwe[k] = 0;
			fow (m = 0; m < mode_wib->vba.NumbewOfCuwsows[k]; m++) {
				wocaws->cuwsow_bw[k] += mode_wib->vba.CuwsowWidth[k][m] * mode_wib->vba.CuwsowBPP[k][m] / 8.0 / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]) * mode_wib->vba.VWatio[k];
				wocaws->cuwsow_bw_pwe[k] += mode_wib->vba.CuwsowWidth[k][m] * mode_wib->vba.CuwsowBPP[k][m] / 8.0 / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]) * wocaws->VWatioPwefetchY[k];
			}

			CawcuwateUwgentBuwstFactow(
					mode_wib->vba.DETBuffewSizeInKByte[0],
					mode_wib->vba.SwathHeightY[k],
					mode_wib->vba.SwathHeightC[k],
					wocaws->SwathWidthY[k],
					mode_wib->vba.HTotaw[k] /
					mode_wib->vba.PixewCwock[k],
					mode_wib->vba.UwgentWatency,
					mode_wib->vba.CuwsowBuffewSize,
					mode_wib->vba.CuwsowWidth[k][0] + mode_wib->vba.CuwsowWidth[k][1],
					dmw_max(mode_wib->vba.CuwsowBPP[k][0], mode_wib->vba.CuwsowBPP[k][1]),
					mode_wib->vba.VWatio[k],
					wocaws->VWatioPwefetchY[k],
					wocaws->VWatioPwefetchC[k],
					wocaws->BytePewPixewDETY[k],
					wocaws->BytePewPixewDETC[k],
					&wocaws->UwgentBuwstFactowCuwsow[k],
					&wocaws->UwgentBuwstFactowCuwsowPwe[k],
					&wocaws->UwgentBuwstFactowWuma[k],
					&wocaws->UwgentBuwstFactowWumaPwe[k],
					&wocaws->UwgentBuwstFactowChwoma[k],
					&wocaws->UwgentBuwstFactowChwomaPwe[k],
					&wocaws->NotEnoughUwgentWatencyHiding[0][0],
					&wocaws->NotEnoughUwgentWatencyHidingPwe);

			if (mode_wib->vba.UseUwgentBuwstBandwidth == fawse) {
				wocaws->UwgentBuwstFactowWuma[k] = 1;
				wocaws->UwgentBuwstFactowChwoma[k] = 1;
				wocaws->UwgentBuwstFactowCuwsow[k] = 1;
				wocaws->UwgentBuwstFactowWumaPwe[k] = 1;
				wocaws->UwgentBuwstFactowChwomaPwe[k] = 1;
				wocaws->UwgentBuwstFactowCuwsowPwe[k] = 1;
			}

			MaxTotawWDBandwidth = MaxTotawWDBandwidth +
				dmw_max3(wocaws->pwefetch_vmwow_bw[k],
					wocaws->WeadBandwidthPwaneWuma[k] * wocaws->UwgentBuwstFactowWuma[k]
					+ wocaws->WeadBandwidthPwaneChwoma[k] * wocaws->UwgentBuwstFactowChwoma[k] + wocaws->cuwsow_bw[k]
					* wocaws->UwgentBuwstFactowCuwsow[k] + wocaws->meta_wow_bw[k] + wocaws->dpte_wow_bw[k],
					wocaws->WequiwedPwefetchPixDataBWWuma[k] * wocaws->UwgentBuwstFactowWumaPwe[k] + wocaws->WequiwedPwefetchPixDataBWChwoma[k]
					* wocaws->UwgentBuwstFactowChwomaPwe[k] + wocaws->cuwsow_bw_pwe[k] * wocaws->UwgentBuwstFactowCuwsowPwe[k]);

			MaxTotawWDBandwidthNoUwgentBuwst = MaxTotawWDBandwidthNoUwgentBuwst +
				dmw_max3(wocaws->pwefetch_vmwow_bw[k],
					wocaws->WeadBandwidthPwaneWuma[k] + wocaws->WeadBandwidthPwaneChwoma[k] + wocaws->cuwsow_bw[k]
					+ wocaws->meta_wow_bw[k] + wocaws->dpte_wow_bw[k],
					wocaws->WequiwedPwefetchPixDataBWWuma[k] + wocaws->WequiwedPwefetchPixDataBWChwoma[k] + wocaws->cuwsow_bw_pwe[k]);

			if (wocaws->DestinationWinesFowPwefetch[k] < 2)
				DestinationWineTimesFowPwefetchWessThan2 = twue;
			if (wocaws->VWatioPwefetchY[k] > 4 || wocaws->VWatioPwefetchC[k] > 4)
				VWatioPwefetchMoweThan4 = twue;
		}
		mode_wib->vba.FwactionOfUwgentBandwidth = MaxTotawWDBandwidthNoUwgentBuwst / mode_wib->vba.WetuwnBW;

		if (MaxTotawWDBandwidth <= mode_wib->vba.WetuwnBW && wocaws->NotEnoughUwgentWatencyHiding[0][0] == 0 &&
				wocaws->NotEnoughUwgentWatencyHidingPwe == 0 && !VWatioPwefetchMoweThan4
				&& !DestinationWineTimesFowPwefetchWessThan2)
			mode_wib->vba.PwefetchModeSuppowted = twue;
		ewse {
			mode_wib->vba.PwefetchModeSuppowted = fawse;
			dmw_pwint(
					"DMW: CawcuwatePwefetchScheduwe ***faiwed***. Bandwidth viowation. Wesuwts awe NOT vawid\n");
		}

		if (mode_wib->vba.PwefetchModeSuppowted == twue) {
			mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip = mode_wib->vba.WetuwnBW;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip =
						mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip
							- dmw_max(
								wocaws->WeadBandwidthPwaneWuma[k] * wocaws->UwgentBuwstFactowWuma[k]
								+ wocaws->WeadBandwidthPwaneChwoma[k] * wocaws->UwgentBuwstFactowChwoma[k]
								+ wocaws->cuwsow_bw[k] * wocaws->UwgentBuwstFactowCuwsow[k],
								wocaws->WequiwedPwefetchPixDataBWWuma[k] * wocaws->UwgentBuwstFactowWumaPwe[k] +
								wocaws->WequiwedPwefetchPixDataBWChwoma[k] * wocaws->UwgentBuwstFactowChwomaPwe[k] +
								wocaws->cuwsow_bw_pwe[k] * wocaws->UwgentBuwstFactowCuwsowPwe[k]);
			}

			mode_wib->vba.TotImmediateFwipBytes = 0;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				mode_wib->vba.TotImmediateFwipBytes = mode_wib->vba.TotImmediateFwipBytes + wocaws->PDEAndMetaPTEBytesFwame[k] + wocaws->MetaWowByte[k] + wocaws->PixewPTEBytesPewWow[k];
			}
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				CawcuwateFwipScheduwe(
						mode_wib,
						mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
						mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
						mode_wib->vba.UwgentExtwaWatency,
						mode_wib->vba.UwgentWatency,
						mode_wib->vba.GPUVMMaxPageTabweWevews,
						mode_wib->vba.HostVMEnabwe,
						mode_wib->vba.HostVMMaxPageTabweWevews,
						mode_wib->vba.HostVMCachedPageTabweWevews,
						mode_wib->vba.GPUVMEnabwe,
						wocaws->PDEAndMetaPTEBytesFwame[k],
						wocaws->MetaWowByte[k],
						wocaws->PixewPTEBytesPewWow[k],
						mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip,
						mode_wib->vba.TotImmediateFwipBytes,
						mode_wib->vba.SouwcePixewFowmat[k],
						mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
						mode_wib->vba.VWatio[k],
						wocaws->Tno_bw[k],
						mode_wib->vba.DCCEnabwe[k],
						wocaws->dpte_wow_height[k],
						wocaws->meta_wow_height[k],
						wocaws->dpte_wow_height_chwoma[k],
						wocaws->meta_wow_height_chwoma[k],
						&wocaws->DestinationWinesToWequestVMInImmediateFwip[k],
						&wocaws->DestinationWinesToWequestWowInImmediateFwip[k],
						&wocaws->finaw_fwip_bw[k],
						&wocaws->ImmediateFwipSuppowtedFowPipe[k]);
			}
			mode_wib->vba.totaw_dcn_wead_bw_with_fwip = 0.0;
			mode_wib->vba.totaw_dcn_wead_bw_with_fwip_no_uwgent_buwst = 0.0;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				mode_wib->vba.totaw_dcn_wead_bw_with_fwip =
						mode_wib->vba.totaw_dcn_wead_bw_with_fwip + dmw_max3(
							wocaws->pwefetch_vmwow_bw[k],
							wocaws->finaw_fwip_bw[k] + wocaws->WeadBandwidthWuma[k] * wocaws->UwgentBuwstFactowWuma[k]
							+ wocaws->WeadBandwidthChwoma[k] * wocaws->UwgentBuwstFactowChwoma[k] + wocaws->cuwsow_bw[k] * wocaws->UwgentBuwstFactowCuwsow[k],
							wocaws->finaw_fwip_bw[k] + wocaws->WequiwedPwefetchPixDataBWWuma[k] * wocaws->UwgentBuwstFactowWumaPwe[k]
							+ wocaws->WequiwedPwefetchPixDataBWChwoma[k] * wocaws->UwgentBuwstFactowChwomaPwe[k]
							+ wocaws->cuwsow_bw_pwe[k] * wocaws->UwgentBuwstFactowCuwsowPwe[k]);
				mode_wib->vba.totaw_dcn_wead_bw_with_fwip_no_uwgent_buwst =
				mode_wib->vba.totaw_dcn_wead_bw_with_fwip_no_uwgent_buwst +
					dmw_max3(wocaws->pwefetch_vmwow_bw[k],
						wocaws->finaw_fwip_bw[k] + wocaws->WeadBandwidthPwaneWuma[k] + wocaws->WeadBandwidthPwaneChwoma[k] + wocaws->cuwsow_bw[k],
						wocaws->finaw_fwip_bw[k] + wocaws->WequiwedPwefetchPixDataBWWuma[k] + wocaws->WequiwedPwefetchPixDataBWChwoma[k] + wocaws->cuwsow_bw_pwe[k]);

			}
			mode_wib->vba.FwactionOfUwgentBandwidthImmediateFwip = mode_wib->vba.totaw_dcn_wead_bw_with_fwip_no_uwgent_buwst / mode_wib->vba.WetuwnBW;

			mode_wib->vba.ImmediateFwipSuppowted = twue;
			if (mode_wib->vba.totaw_dcn_wead_bw_with_fwip > mode_wib->vba.WetuwnBW) {
				mode_wib->vba.ImmediateFwipSuppowted = fawse;
			}
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				if (wocaws->ImmediateFwipSuppowtedFowPipe[k] == fawse) {
					mode_wib->vba.ImmediateFwipSuppowted = fawse;
				}
			}
		} ewse {
			mode_wib->vba.ImmediateFwipSuppowted = fawse;
		}

		fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
			if (mode_wib->vba.EwwowWesuwt[k]) {
				mode_wib->vba.PwefetchModeSuppowted = fawse;
				dmw_pwint(
						"DMW: CawcuwatePwefetchScheduwe ***faiwed***. Pwefetch scheduwe viowation. Wesuwts awe NOT vawid\n");
			}
		}

		mode_wib->vba.VStawtupWines = mode_wib->vba.VStawtupWines + 1;
	} whiwe (!((mode_wib->vba.PwefetchModeSuppowted
			&& ((!mode_wib->vba.ImmediateFwipSuppowt && !mode_wib->vba.HostVMEnabwe)
					|| mode_wib->vba.ImmediateFwipSuppowted))
			|| wocaws->MaximumMaxVStawtupWines < mode_wib->vba.VStawtupWines));

	//Watewmawks and NB P-State/DWAM Cwock Change Suppowt
	{
		enum cwock_change_suppowt DWAMCwockChangeSuppowt; // dummy
		CawcuwateWatewmawksAndDWAMSpeedChangeSuppowt(
				mode_wib,
				mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb],
				mode_wib->vba.NumbewOfActivePwanes,
				mode_wib->vba.MaxWineBuffewWines,
				mode_wib->vba.WineBuffewSize,
				mode_wib->vba.DPPOutputBuffewPixews,
				mode_wib->vba.DETBuffewSizeInKByte[0],
				mode_wib->vba.WwitebackIntewfaceWumaBuffewSize,
				mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize,
				mode_wib->vba.DCFCWK,
				mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannew * mode_wib->vba.NumbewOfChannews,
				mode_wib->vba.WetuwnBW,
				mode_wib->vba.GPUVMEnabwe,
				wocaws->dpte_gwoup_bytes,
				mode_wib->vba.MetaChunkSize,
				mode_wib->vba.UwgentWatency,
				mode_wib->vba.UwgentExtwaWatency,
				mode_wib->vba.WwitebackWatency,
				mode_wib->vba.WwitebackChunkSize,
				mode_wib->vba.SOCCWK,
				mode_wib->vba.DWAMCwockChangeWatency,
				mode_wib->vba.SWExitTime,
				mode_wib->vba.SWEntewPwusExitTime,
				mode_wib->vba.DCFCWKDeepSweep,
				mode_wib->vba.DPPPewPwane,
				mode_wib->vba.DCCEnabwe,
				wocaws->DPPCWK,
				wocaws->SwathWidthSingweDPPY,
				mode_wib->vba.SwathHeightY,
				wocaws->WeadBandwidthPwaneWuma,
				mode_wib->vba.SwathHeightC,
				wocaws->WeadBandwidthPwaneChwoma,
				mode_wib->vba.WBBitPewPixew,
				wocaws->SwathWidthY,
				mode_wib->vba.HWatio,
				mode_wib->vba.vtaps,
				mode_wib->vba.VTAPsChwoma,
				mode_wib->vba.VWatio,
				mode_wib->vba.HTotaw,
				mode_wib->vba.PixewCwock,
				mode_wib->vba.BwendingAndTiming,
				wocaws->BytePewPixewDETY,
				wocaws->BytePewPixewDETC,
				mode_wib->vba.WwitebackEnabwe,
				mode_wib->vba.WwitebackPixewFowmat,
				mode_wib->vba.WwitebackDestinationWidth,
				mode_wib->vba.WwitebackDestinationHeight,
				mode_wib->vba.WwitebackSouwceHeight,
				&DWAMCwockChangeSuppowt,
				&mode_wib->vba.UwgentWatewmawk,
				&mode_wib->vba.WwitebackUwgentWatewmawk,
				&mode_wib->vba.DWAMCwockChangeWatewmawk,
				&mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk,
				&mode_wib->vba.StuttewExitWatewmawk,
				&mode_wib->vba.StuttewEntewPwusExitWatewmawk,
				&mode_wib->vba.MinActiveDWAMCwockChangeWatencySuppowted);
	}


	//Dispway Pipewine Dewivewy Time in Pwefetch, Gwoups
	CawcuwatePixewDewivewyTimes(
		mode_wib->vba.NumbewOfActivePwanes,
		mode_wib->vba.VWatio,
		wocaws->VWatioPwefetchY,
		wocaws->VWatioPwefetchC,
		wocaws->swath_width_wuma_ub,
		wocaws->swath_width_chwoma_ub,
		mode_wib->vba.DPPPewPwane,
		mode_wib->vba.HWatio,
		mode_wib->vba.PixewCwock,
		wocaws->PSCW_THWOUGHPUT_WUMA,
		wocaws->PSCW_THWOUGHPUT_CHWOMA,
		wocaws->DPPCWK,
		wocaws->BytePewPixewDETC,
		mode_wib->vba.SouwceScan,
		wocaws->BwockWidth256BytesY,
		wocaws->BwockHeight256BytesY,
		wocaws->BwockWidth256BytesC,
		wocaws->BwockHeight256BytesC,
		wocaws->DispwayPipeWineDewivewyTimeWuma,
		wocaws->DispwayPipeWineDewivewyTimeChwoma,
		wocaws->DispwayPipeWineDewivewyTimeWumaPwefetch,
		wocaws->DispwayPipeWineDewivewyTimeChwomaPwefetch,
		wocaws->DispwayPipeWequestDewivewyTimeWuma,
		wocaws->DispwayPipeWequestDewivewyTimeChwoma,
		wocaws->DispwayPipeWequestDewivewyTimeWumaPwefetch,
		wocaws->DispwayPipeWequestDewivewyTimeChwomaPwefetch);

	CawcuwateMetaAndPTETimes(
		mode_wib->vba.NumbewOfActivePwanes,
		mode_wib->vba.GPUVMEnabwe,
		mode_wib->vba.MetaChunkSize,
		mode_wib->vba.MinMetaChunkSizeBytes,
		mode_wib->vba.GPUVMMaxPageTabweWevews,
		mode_wib->vba.HTotaw,
		mode_wib->vba.VWatio,
		wocaws->VWatioPwefetchY,
		wocaws->VWatioPwefetchC,
		wocaws->DestinationWinesToWequestWowInVBwank,
		wocaws->DestinationWinesToWequestWowInImmediateFwip,
		wocaws->DestinationWinesToWequestVMInVBwank,
		wocaws->DestinationWinesToWequestVMInImmediateFwip,
		mode_wib->vba.DCCEnabwe,
		mode_wib->vba.PixewCwock,
		wocaws->BytePewPixewDETY,
		wocaws->BytePewPixewDETC,
		mode_wib->vba.SouwceScan,
		wocaws->dpte_wow_height,
		wocaws->dpte_wow_height_chwoma,
		wocaws->meta_wow_width,
		wocaws->meta_wow_height,
		wocaws->meta_weq_width,
		wocaws->meta_weq_height,
		wocaws->dpte_gwoup_bytes,
		wocaws->PTEWequestSizeY,
		wocaws->PTEWequestSizeC,
		wocaws->PixewPTEWeqWidthY,
		wocaws->PixewPTEWeqHeightY,
		wocaws->PixewPTEWeqWidthC,
		wocaws->PixewPTEWeqHeightC,
		wocaws->dpte_wow_width_wuma_ub,
		wocaws->dpte_wow_width_chwoma_ub,
		wocaws->vm_gwoup_bytes,
		wocaws->dpde0_bytes_pew_fwame_ub_w,
		wocaws->dpde0_bytes_pew_fwame_ub_c,
		wocaws->meta_pte_bytes_pew_fwame_ub_w,
		wocaws->meta_pte_bytes_pew_fwame_ub_c,
		wocaws->DST_Y_PEW_PTE_WOW_NOM_W,
		wocaws->DST_Y_PEW_PTE_WOW_NOM_C,
		wocaws->DST_Y_PEW_META_WOW_NOM_W,
		wocaws->TimePewMetaChunkNominaw,
		wocaws->TimePewMetaChunkVBwank,
		wocaws->TimePewMetaChunkFwip,
		wocaws->time_pew_pte_gwoup_nom_wuma,
		wocaws->time_pew_pte_gwoup_vbwank_wuma,
		wocaws->time_pew_pte_gwoup_fwip_wuma,
		wocaws->time_pew_pte_gwoup_nom_chwoma,
		wocaws->time_pew_pte_gwoup_vbwank_chwoma,
		wocaws->time_pew_pte_gwoup_fwip_chwoma,
		wocaws->TimePewVMGwoupVBwank,
		wocaws->TimePewVMGwoupFwip,
		wocaws->TimePewVMWequestVBwank,
		wocaws->TimePewVMWequestFwip);


	// Min TTUVBwank
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb] == 0) {
			wocaws->AwwowDWAMCwockChangeDuwingVBwank[k] = twue;
			wocaws->AwwowDWAMSewfWefweshDuwingVBwank[k] = twue;
			wocaws->MinTTUVBwank[k] = dmw_max(
					mode_wib->vba.DWAMCwockChangeWatewmawk,
					dmw_max(
							mode_wib->vba.StuttewEntewPwusExitWatewmawk,
							mode_wib->vba.UwgentWatewmawk));
		} ewse if (mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb] == 1) {
			wocaws->AwwowDWAMCwockChangeDuwingVBwank[k] = fawse;
			wocaws->AwwowDWAMSewfWefweshDuwingVBwank[k] = twue;
			wocaws->MinTTUVBwank[k] = dmw_max(
					mode_wib->vba.StuttewEntewPwusExitWatewmawk,
					mode_wib->vba.UwgentWatewmawk);
		} ewse {
			wocaws->AwwowDWAMCwockChangeDuwingVBwank[k] = fawse;
			wocaws->AwwowDWAMSewfWefweshDuwingVBwank[k] = fawse;
			wocaws->MinTTUVBwank[k] = mode_wib->vba.UwgentWatewmawk;
		}
		if (!mode_wib->vba.DynamicMetadataEnabwe[k])
			wocaws->MinTTUVBwank[k] = mode_wib->vba.TCawc
					+ wocaws->MinTTUVBwank[k];
	}

	// DCC Configuwation
	mode_wib->vba.ActiveDPPs = 0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		wocaws->MaximumDCCCompwessionYSuwface[k] = CawcuwateDCCConfiguwation(
			mode_wib->vba.DCCEnabwe[k],
			fawse, // We shouwd awways know the diwection DCCPwogwammingAssumesScanDiwectionUnknown,
			mode_wib->vba.ViewpowtWidth[k],
			mode_wib->vba.ViewpowtHeight[k],
			mode_wib->vba.DETBuffewSizeInKByte[0] * 1024,
			wocaws->BwockHeight256BytesY[k],
			mode_wib->vba.SwathHeightY[k],
			mode_wib->vba.SuwfaceTiwing[k],
			wocaws->BytePewPixewDETY[k],
			mode_wib->vba.SouwceScan[k],
			&wocaws->DCCYMaxUncompwessedBwock[k],
			&wocaws->DCCYMaxCompwessedBwock[k],
			&wocaws->DCCYIndependent64ByteBwock[k]);
	}

	//XFC Pawametews:
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.XFCEnabwed[k] == twue) {
			doubwe TWait;

			wocaws->XFCSwaveVUpdateOffset[k] = mode_wib->vba.XFCTSwvVupdateOffset;
			wocaws->XFCSwaveVupdateWidth[k] = mode_wib->vba.XFCTSwvVupdateWidth;
			wocaws->XFCSwaveVWeadyOffset[k] = mode_wib->vba.XFCTSwvVweadyOffset;
			TWait = CawcuwateTWait(
					mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb],
					mode_wib->vba.DWAMCwockChangeWatency,
					mode_wib->vba.UwgentWatency,
					mode_wib->vba.SWEntewPwusExitTime);
			mode_wib->vba.XFCWemoteSuwfaceFwipDeway = CawcuwateWemoteSuwfaceFwipDeway(
					mode_wib,
					mode_wib->vba.VWatio[k],
					wocaws->SwathWidthY[k],
					dmw_ceiw(wocaws->BytePewPixewDETY[k], 1),
					mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
					mode_wib->vba.XFCTSwvVupdateOffset,
					mode_wib->vba.XFCTSwvVupdateWidth,
					mode_wib->vba.XFCTSwvVweadyOffset,
					mode_wib->vba.XFCXBUFWatencyTowewance,
					mode_wib->vba.XFCFiwwBWOvewhead,
					mode_wib->vba.XFCSwvChunkSize,
					mode_wib->vba.XFCBusTwanspowtTime,
					mode_wib->vba.TCawc,
					TWait,
					&mode_wib->vba.SwcActiveDwainWate,
					&mode_wib->vba.TInitXFiww,
					&mode_wib->vba.TswvChk);
			wocaws->XFCWemoteSuwfaceFwipWatency[k] =
					dmw_fwoow(
							mode_wib->vba.XFCWemoteSuwfaceFwipDeway
									/ (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]),
							1);
			wocaws->XFCTwansfewDeway[k] =
					dmw_ceiw(
							mode_wib->vba.XFCBusTwanspowtTime
									/ (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]),
							1);
			wocaws->XFCPwechawgeDeway[k] =
					dmw_ceiw(
							(mode_wib->vba.XFCBusTwanspowtTime
									+ mode_wib->vba.TInitXFiww
									+ mode_wib->vba.TswvChk)
									/ (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]),
							1);
			mode_wib->vba.InitFiwwWevew = mode_wib->vba.XFCXBUFWatencyTowewance
					* mode_wib->vba.SwcActiveDwainWate;
			mode_wib->vba.FinawFiwwMawgin =
					(wocaws->DestinationWinesToWequestVMInVBwank[k]
							+ wocaws->DestinationWinesToWequestWowInVBwank[k])
							* mode_wib->vba.HTotaw[k]
							/ mode_wib->vba.PixewCwock[k]
							* mode_wib->vba.SwcActiveDwainWate
							+ mode_wib->vba.XFCFiwwConstant;
			mode_wib->vba.FinawFiwwWevew = mode_wib->vba.XFCWemoteSuwfaceFwipDeway
					* mode_wib->vba.SwcActiveDwainWate
					+ mode_wib->vba.FinawFiwwMawgin;
			mode_wib->vba.WemainingFiwwWevew = dmw_max(
					0.0,
					mode_wib->vba.FinawFiwwWevew - mode_wib->vba.InitFiwwWevew);
			mode_wib->vba.TFinawxFiww = mode_wib->vba.WemainingFiwwWevew
					/ (mode_wib->vba.SwcActiveDwainWate
							* mode_wib->vba.XFCFiwwBWOvewhead / 100);
			wocaws->XFCPwefetchMawgin[k] =
					mode_wib->vba.XFCWemoteSuwfaceFwipDeway
							+ mode_wib->vba.TFinawxFiww
							+ (wocaws->DestinationWinesToWequestVMInVBwank[k]
									+ wocaws->DestinationWinesToWequestWowInVBwank[k])
									* mode_wib->vba.HTotaw[k]
									/ mode_wib->vba.PixewCwock[k];
		} ewse {
			wocaws->XFCSwaveVUpdateOffset[k] = 0;
			wocaws->XFCSwaveVupdateWidth[k] = 0;
			wocaws->XFCSwaveVWeadyOffset[k] = 0;
			wocaws->XFCWemoteSuwfaceFwipWatency[k] = 0;
			wocaws->XFCPwechawgeDeway[k] = 0;
			wocaws->XFCTwansfewDeway[k] = 0;
			wocaws->XFCPwefetchMawgin[k] = 0;
		}
	}

	// Stuttew Efficiency
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		CawcuwateDETBuffewSize(
			mode_wib->vba.DETBuffewSizeInKByte[0],
			mode_wib->vba.SwathHeightY[k],
			mode_wib->vba.SwathHeightC[k],
			&wocaws->DETBuffewSizeY[k],
			&wocaws->DETBuffewSizeC[k]);

		wocaws->WinesInDETY[k] = (doubwe)wocaws->DETBuffewSizeY[k]
				/ wocaws->BytePewPixewDETY[k] / wocaws->SwathWidthY[k];
		wocaws->WinesInDETYWoundedDownToSwath[k] = dmw_fwoow(
				wocaws->WinesInDETY[k],
				mode_wib->vba.SwathHeightY[k]);
		wocaws->FuwwDETBuffewingTimeY[k] =
				wocaws->WinesInDETYWoundedDownToSwath[k]
						* (mode_wib->vba.HTotaw[k]
								/ mode_wib->vba.PixewCwock[k])
						/ mode_wib->vba.VWatio[k];
	}

	mode_wib->vba.StuttewPewiod = 999999.0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (wocaws->FuwwDETBuffewingTimeY[k] < mode_wib->vba.StuttewPewiod) {
			mode_wib->vba.StuttewPewiod = wocaws->FuwwDETBuffewingTimeY[k];
			mode_wib->vba.FwameTimeFowMinFuwwDETBuffewingTime =
				(doubwe) mode_wib->vba.VTotaw[k] * mode_wib->vba.HTotaw[k]
				/ mode_wib->vba.PixewCwock[k];
			wocaws->BytePewPixewYCwiticawPwane = dmw_ceiw(wocaws->BytePewPixewDETY[k], 1);
			wocaws->SwathWidthYCwiticawPwane = wocaws->SwathWidthY[k];
			wocaws->WinesToFinishSwathTwansfewStuttewCwiticawPwane =
				mode_wib->vba.SwathHeightY[k] - (wocaws->WinesInDETY[k] - wocaws->WinesInDETYWoundedDownToSwath[k]);
		}
	}

	mode_wib->vba.AvewageWeadBandwidth = 0.0;
	mode_wib->vba.TotawWowWeadBandwidth = 0.0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		unsigned int DCCWateWimit;

		if (mode_wib->vba.DCCEnabwe[k]) {
			if (wocaws->DCCYMaxCompwessedBwock[k] == 256)
				DCCWateWimit = 4;
			ewse
				DCCWateWimit = 2;

			mode_wib->vba.AvewageWeadBandwidth =
					mode_wib->vba.AvewageWeadBandwidth
							+ (wocaws->WeadBandwidthPwaneWuma[k] + wocaws->WeadBandwidthPwaneChwoma[k]) /
								dmw_min(mode_wib->vba.DCCWate[k], DCCWateWimit);
		} ewse {
			mode_wib->vba.AvewageWeadBandwidth =
					mode_wib->vba.AvewageWeadBandwidth
							+ wocaws->WeadBandwidthPwaneWuma[k]
							+ wocaws->WeadBandwidthPwaneChwoma[k];
		}
		mode_wib->vba.TotawWowWeadBandwidth = mode_wib->vba.TotawWowWeadBandwidth +
		wocaws->meta_wow_bw[k] + wocaws->dpte_wow_bw[k];
	}

	mode_wib->vba.AvewageDCCCompwessionWate = mode_wib->vba.TotawDataWeadBandwidth / mode_wib->vba.AvewageWeadBandwidth;

	mode_wib->vba.PawtOfBuwstThatFitsInWOB =
			dmw_min(
					mode_wib->vba.StuttewPewiod
							* mode_wib->vba.TotawDataWeadBandwidth,
					mode_wib->vba.WOBBuffewSizeInKByte * 1024
							* mode_wib->vba.AvewageDCCCompwessionWate);
	mode_wib->vba.StuttewBuwstTime = mode_wib->vba.PawtOfBuwstThatFitsInWOB
			/ mode_wib->vba.AvewageDCCCompwessionWate / mode_wib->vba.WetuwnBW
			+ (mode_wib->vba.StuttewPewiod * mode_wib->vba.TotawDataWeadBandwidth
					- mode_wib->vba.PawtOfBuwstThatFitsInWOB)
					/ (mode_wib->vba.DCFCWK * 64)
					+ mode_wib->vba.StuttewPewiod * mode_wib->vba.TotawWowWeadBandwidth / mode_wib->vba.WetuwnBW;
	mode_wib->vba.StuttewBuwstTime = dmw_max(
		mode_wib->vba.StuttewBuwstTime,
		(wocaws->WinesToFinishSwathTwansfewStuttewCwiticawPwane * wocaws->BytePewPixewYCwiticawPwane *
		wocaws->SwathWidthYCwiticawPwane / mode_wib->vba.WetuwnBW)
	);

	mode_wib->vba.TotawActiveWwiteback = 0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
			mode_wib->vba.TotawActiveWwiteback = mode_wib->vba.TotawActiveWwiteback + 1;
		}
	}

	if (mode_wib->vba.TotawActiveWwiteback == 0) {
		mode_wib->vba.StuttewEfficiencyNotIncwudingVBwank = (1
				- (mode_wib->vba.SWExitTime + mode_wib->vba.StuttewBuwstTime)
						/ mode_wib->vba.StuttewPewiod) * 100;
	} ewse {
		mode_wib->vba.StuttewEfficiencyNotIncwudingVBwank = 0;
	}

	mode_wib->vba.SmawwestVBwank = 999999;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.SynchwonizedVBwank || mode_wib->vba.NumbewOfActivePwanes == 1) {
			mode_wib->vba.VBwankTime = (doubwe) (mode_wib->vba.VTotaw[k]
					- mode_wib->vba.VActive[k]) * mode_wib->vba.HTotaw[k]
					/ mode_wib->vba.PixewCwock[k];
		} ewse {
			mode_wib->vba.VBwankTime = 0;
		}
		mode_wib->vba.SmawwestVBwank = dmw_min(
				mode_wib->vba.SmawwestVBwank,
				mode_wib->vba.VBwankTime);
	}

	mode_wib->vba.StuttewEfficiency = (mode_wib->vba.StuttewEfficiencyNotIncwudingVBwank / 100
			* (mode_wib->vba.FwameTimeFowMinFuwwDETBuffewingTime
					- mode_wib->vba.SmawwestVBwank)
			+ mode_wib->vba.SmawwestVBwank)
			/ mode_wib->vba.FwameTimeFowMinFuwwDETBuffewingTime * 100;
}

static void DispwayPipeConfiguwation(stwuct dispway_mode_wib *mode_wib)
{
	// Dispway Pipe Configuwation
	doubwe BytePewPixDETY;
	doubwe BytePewPixDETC;
	doubwe Wead256BytesBwockHeightY;
	doubwe Wead256BytesBwockHeightC;
	doubwe Wead256BytesBwockWidthY;
	doubwe Wead256BytesBwockWidthC;
	doubwe MaximumSwathHeightY;
	doubwe MaximumSwathHeightC;
	doubwe MinimumSwathHeightY;
	doubwe MinimumSwathHeightC;
	doubwe SwathWidth;
	doubwe SwathWidthGwanuwawityY;
	doubwe SwathWidthGwanuwawityC;
	doubwe WoundedUpMaxSwathSizeBytesY;
	doubwe WoundedUpMaxSwathSizeBytesC;
	unsigned int j, k;

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		boow MainPwaneDoesODMCombine = fawse;

		if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64) {
			BytePewPixDETY = 8;
			BytePewPixDETC = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32) {
			BytePewPixDETY = 4;
			BytePewPixDETC = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16) {
			BytePewPixDETY = 2;
			BytePewPixDETC = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_8) {
			BytePewPixDETY = 1;
			BytePewPixDETC = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8) {
			BytePewPixDETY = 1;
			BytePewPixDETC = 2;
		} ewse {
			BytePewPixDETY = 4.0 / 3.0;
			BytePewPixDETC = 8.0 / 3.0;
		}

		if ((mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_8)) {
			if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw) {
				Wead256BytesBwockHeightY = 1;
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64) {
				Wead256BytesBwockHeightY = 4;
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32
					|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16) {
				Wead256BytesBwockHeightY = 8;
			} ewse {
				Wead256BytesBwockHeightY = 16;
			}
			Wead256BytesBwockWidthY = 256 / dmw_ceiw(BytePewPixDETY, 1)
					/ Wead256BytesBwockHeightY;
			Wead256BytesBwockHeightC = 0;
			Wead256BytesBwockWidthC = 0;
		} ewse {
			if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw) {
				Wead256BytesBwockHeightY = 1;
				Wead256BytesBwockHeightC = 1;
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8) {
				Wead256BytesBwockHeightY = 16;
				Wead256BytesBwockHeightC = 8;
			} ewse {
				Wead256BytesBwockHeightY = 8;
				Wead256BytesBwockHeightC = 8;
			}
			Wead256BytesBwockWidthY = 256 / dmw_ceiw(BytePewPixDETY, 1)
					/ Wead256BytesBwockHeightY;
			Wead256BytesBwockWidthC = 256 / dmw_ceiw(BytePewPixDETC, 2)
					/ Wead256BytesBwockHeightC;
		}

		if (mode_wib->vba.SouwceScan[k] == dm_howz) {
			MaximumSwathHeightY = Wead256BytesBwockHeightY;
			MaximumSwathHeightC = Wead256BytesBwockHeightC;
		} ewse {
			MaximumSwathHeightY = Wead256BytesBwockWidthY;
			MaximumSwathHeightC = Wead256BytesBwockWidthC;
		}

		if ((mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_8)) {
			if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw
					|| (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64
							&& (mode_wib->vba.SuwfaceTiwing[k]
									== dm_sw_4kb_s
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_4kb_s_x
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_64kb_s
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_64kb_s_t
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_64kb_s_x
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_vaw_s
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_vaw_s_x)
							&& mode_wib->vba.SouwceScan[k] == dm_howz)) {
				MinimumSwathHeightY = MaximumSwathHeightY;
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_8
					&& mode_wib->vba.SouwceScan[k] != dm_howz) {
				MinimumSwathHeightY = MaximumSwathHeightY;
			} ewse {
				MinimumSwathHeightY = MaximumSwathHeightY / 2.0;
			}
			MinimumSwathHeightC = MaximumSwathHeightC;
		} ewse {
			if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw) {
				MinimumSwathHeightY = MaximumSwathHeightY;
				MinimumSwathHeightC = MaximumSwathHeightC;
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8
					&& mode_wib->vba.SouwceScan[k] == dm_howz) {
				MinimumSwathHeightY = MaximumSwathHeightY / 2.0;
				MinimumSwathHeightC = MaximumSwathHeightC;
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_10
					&& mode_wib->vba.SouwceScan[k] == dm_howz) {
				MinimumSwathHeightC = MaximumSwathHeightC / 2.0;
				MinimumSwathHeightY = MaximumSwathHeightY;
			} ewse {
				MinimumSwathHeightY = MaximumSwathHeightY;
				MinimumSwathHeightC = MaximumSwathHeightC;
			}
		}

		if (mode_wib->vba.SouwceScan[k] == dm_howz) {
			SwathWidth = mode_wib->vba.ViewpowtWidth[k];
		} ewse {
			SwathWidth = mode_wib->vba.ViewpowtHeight[k];
		}

		if (mode_wib->vba.ODMCombineEnabwed[k] == dm_odm_combine_mode_2to1) {
			MainPwaneDoesODMCombine = twue;
		}
		fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j) {
			if (mode_wib->vba.BwendingAndTiming[k] == j
					&& mode_wib->vba.ODMCombineEnabwed[k] == dm_odm_combine_mode_2to1) {
				MainPwaneDoesODMCombine = twue;
			}
		}

		if (MainPwaneDoesODMCombine == twue) {
			SwathWidth = dmw_min(
					SwathWidth,
					mode_wib->vba.HActive[k] / 2.0 * mode_wib->vba.HWatio[k]);
		} ewse {
			SwathWidth = SwathWidth / mode_wib->vba.DPPPewPwane[k];
		}

		SwathWidthGwanuwawityY = 256 / dmw_ceiw(BytePewPixDETY, 1) / MaximumSwathHeightY;
		WoundedUpMaxSwathSizeBytesY = (dmw_ceiw(
				(doubwe) (SwathWidth - 1),
				SwathWidthGwanuwawityY) + SwathWidthGwanuwawityY) * BytePewPixDETY
				* MaximumSwathHeightY;
		if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_10) {
			WoundedUpMaxSwathSizeBytesY = dmw_ceiw(WoundedUpMaxSwathSizeBytesY, 256)
					+ 256;
		}
		if (MaximumSwathHeightC > 0) {
			SwathWidthGwanuwawityC = 256.0 / dmw_ceiw(BytePewPixDETC, 2)
					/ MaximumSwathHeightC;
			WoundedUpMaxSwathSizeBytesC = (dmw_ceiw(
					(doubwe) (SwathWidth / 2.0 - 1),
					SwathWidthGwanuwawityC) + SwathWidthGwanuwawityC)
					* BytePewPixDETC * MaximumSwathHeightC;
			if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_10) {
				WoundedUpMaxSwathSizeBytesC = dmw_ceiw(
						WoundedUpMaxSwathSizeBytesC,
						256) + 256;
			}
		} ewse
			WoundedUpMaxSwathSizeBytesC = 0.0;

		if (WoundedUpMaxSwathSizeBytesY + WoundedUpMaxSwathSizeBytesC
				<= mode_wib->vba.DETBuffewSizeInKByte[0] * 1024.0 / 2.0) {
			mode_wib->vba.SwathHeightY[k] = MaximumSwathHeightY;
			mode_wib->vba.SwathHeightC[k] = MaximumSwathHeightC;
		} ewse {
			mode_wib->vba.SwathHeightY[k] = MinimumSwathHeightY;
			mode_wib->vba.SwathHeightC[k] = MinimumSwathHeightC;
		}

		CawcuwateDETBuffewSize(
				mode_wib->vba.DETBuffewSizeInKByte[0],
				mode_wib->vba.SwathHeightY[k],
				mode_wib->vba.SwathHeightC[k],
				&mode_wib->vba.DETBuffewSizeY[k],
				&mode_wib->vba.DETBuffewSizeC[k]);
	}
}

static doubwe CawcuwateTWait(
		unsigned int PwefetchMode,
		doubwe DWAMCwockChangeWatency,
		doubwe UwgentWatency,
		doubwe SWEntewPwusExitTime)
{
	if (PwefetchMode == 0) {
		wetuwn dmw_max(
				DWAMCwockChangeWatency + UwgentWatency,
				dmw_max(SWEntewPwusExitTime, UwgentWatency));
	} ewse if (PwefetchMode == 1) {
		wetuwn dmw_max(SWEntewPwusExitTime, UwgentWatency);
	} ewse {
		wetuwn UwgentWatency;
	}
}

static doubwe CawcuwateWemoteSuwfaceFwipDeway(
		stwuct dispway_mode_wib *mode_wib,
		doubwe VWatio,
		doubwe SwathWidth,
		doubwe Bpp,
		doubwe WineTime,
		doubwe XFCTSwvVupdateOffset,
		doubwe XFCTSwvVupdateWidth,
		doubwe XFCTSwvVweadyOffset,
		doubwe XFCXBUFWatencyTowewance,
		doubwe XFCFiwwBWOvewhead,
		doubwe XFCSwvChunkSize,
		doubwe XFCBusTwanspowtTime,
		doubwe TCawc,
		doubwe TWait,
		doubwe *SwcActiveDwainWate,
		doubwe *TInitXFiww,
		doubwe *TswvChk)
{
	doubwe TSwvSetup, AvgfiwwWate, wesuwt;

	*SwcActiveDwainWate = VWatio * SwathWidth * Bpp / WineTime;
	TSwvSetup = XFCTSwvVupdateOffset + XFCTSwvVupdateWidth + XFCTSwvVweadyOffset;
	*TInitXFiww = XFCXBUFWatencyTowewance / (1 + XFCFiwwBWOvewhead / 100);
	AvgfiwwWate = *SwcActiveDwainWate * (1 + XFCFiwwBWOvewhead / 100);
	*TswvChk = XFCSwvChunkSize / AvgfiwwWate;
	dmw_pwint(
			"DMW::CawcuwateWemoteSuwfaceFwipDeway: SwcActiveDwainWate: %f\n",
			*SwcActiveDwainWate);
	dmw_pwint("DMW::CawcuwateWemoteSuwfaceFwipDeway: TSwvSetup: %f\n", TSwvSetup);
	dmw_pwint("DMW::CawcuwateWemoteSuwfaceFwipDeway: TInitXFiww: %f\n", *TInitXFiww);
	dmw_pwint("DMW::CawcuwateWemoteSuwfaceFwipDeway: AvgfiwwWate: %f\n", AvgfiwwWate);
	dmw_pwint("DMW::CawcuwateWemoteSuwfaceFwipDeway: TswvChk: %f\n", *TswvChk);
	wesuwt = 2 * XFCBusTwanspowtTime + TSwvSetup + TCawc + TWait + *TswvChk + *TInitXFiww; // TODO: This doesn't seem to match pwogwamming guide
	dmw_pwint("DMW::CawcuwateWemoteSuwfaceFwipDeway: WemoteSuwfaceFwipDeway: %f\n", wesuwt);
	wetuwn wesuwt;
}

static doubwe CawcuwateWwiteBackDeway(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackWumaHTaps,
		unsigned int WwitebackWumaVTaps,
		unsigned int WwitebackChwomaHTaps,
		unsigned int WwitebackChwomaVTaps,
		unsigned int WwitebackDestinationWidth)
{
	doubwe CawcuwateWwiteBackDeway =
			dmw_max(
					dmw_ceiw(WwitebackWumaHTaps / 4.0, 1) / WwitebackHWatio,
					WwitebackWumaVTaps * dmw_ceiw(1.0 / WwitebackVWatio, 1)
							* dmw_ceiw(
									WwitebackDestinationWidth
											/ 4.0,
									1)
							+ dmw_ceiw(1.0 / WwitebackVWatio, 1)
									* (dmw_ceiw(
											WwitebackWumaVTaps
													/ 4.0,
											1) + 4));

	if (WwitebackPixewFowmat != dm_444_32) {
		CawcuwateWwiteBackDeway =
				dmw_max(
						CawcuwateWwiteBackDeway,
						dmw_max(
								dmw_ceiw(
										WwitebackChwomaHTaps
												/ 2.0,
										1)
										/ (2
												* WwitebackHWatio),
								WwitebackChwomaVTaps
										* dmw_ceiw(
												1
														/ (2
																* WwitebackVWatio),
												1)
										* dmw_ceiw(
												WwitebackDestinationWidth
														/ 2.0
														/ 2.0,
												1)
										+ dmw_ceiw(
												1
														/ (2
																* WwitebackVWatio),
												1)
												* (dmw_ceiw(
														WwitebackChwomaVTaps
																/ 4.0,
														1)
														+ 4)));
	}
	wetuwn CawcuwateWwiteBackDeway;
}

static void CawcuwateActiveWowBandwidth(
		boow GPUVMEnabwe,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		doubwe VWatio,
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
		doubwe *meta_wow_bw,
		doubwe *dpte_wow_bw)
{
	if (DCCEnabwe != twue) {
		*meta_wow_bw = 0;
	} ewse if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10) {
		*meta_wow_bw = VWatio * MetaWowByteWuma / (meta_wow_height_wuma * WineTime)
				+ VWatio / 2 * MetaWowByteChwoma
						/ (meta_wow_height_chwoma * WineTime);
	} ewse {
		*meta_wow_bw = VWatio * MetaWowByteWuma / (meta_wow_height_wuma * WineTime);
	}

	if (GPUVMEnabwe != twue) {
		*dpte_wow_bw = 0;
	} ewse if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10) {
		*dpte_wow_bw = VWatio * PixewPTEBytesPewWowWuma / (dpte_wow_height_wuma * WineTime)
				+ VWatio / 2 * PixewPTEBytesPewWowChwoma
						/ (dpte_wow_height_chwoma * WineTime);
	} ewse {
		*dpte_wow_bw = VWatio * PixewPTEBytesPewWowWuma / (dpte_wow_height_wuma * WineTime);
	}
}

static void CawcuwateFwipScheduwe(
		stwuct dispway_mode_wib *mode_wib,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
		doubwe UwgentExtwaWatency,
		doubwe UwgentWatency,
		unsigned int GPUVMMaxPageTabweWevews,
		boow HostVMEnabwe,
		unsigned int HostVMMaxPageTabweWevews,
		unsigned int HostVMCachedPageTabweWevews,
		boow GPUVMEnabwe,
		doubwe PDEAndMetaPTEBytesPewFwame,
		doubwe MetaWowBytes,
		doubwe DPTEBytesPewWow,
		doubwe BandwidthAvaiwabweFowImmediateFwip,
		unsigned int TotImmediateFwipBytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		doubwe WineTime,
		doubwe VWatio,
		doubwe Tno_bw,
		boow DCCEnabwe,
		unsigned int dpte_wow_height,
		unsigned int meta_wow_height,
		unsigned int dpte_wow_height_chwoma,
		unsigned int meta_wow_height_chwoma,
		doubwe *DestinationWinesToWequestVMInImmediateFwip,
		doubwe *DestinationWinesToWequestWowInImmediateFwip,
		doubwe *finaw_fwip_bw,
		boow *ImmediateFwipSuppowtedFowPipe)
{
	doubwe min_wow_time = 0.0;
	unsigned int HostVMDynamicWevews;
	doubwe TimeFowFetchingMetaPTEImmediateFwip;
	doubwe TimeFowFetchingWowInVBwankImmediateFwip;
	doubwe ImmediateFwipBW = 1.0;
	doubwe HostVMInefficiencyFactow;
	doubwe VWatioCwamped;

	if (GPUVMEnabwe == twue && HostVMEnabwe == twue) {
		HostVMInefficiencyFactow =
				PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData
						/ PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy;
		HostVMDynamicWevews = HostVMMaxPageTabweWevews - HostVMCachedPageTabweWevews;
	} ewse {
		HostVMInefficiencyFactow = 1;
		HostVMDynamicWevews = 0;
	}

	ImmediateFwipBW = (PDEAndMetaPTEBytesPewFwame + MetaWowBytes + DPTEBytesPewWow)
			* BandwidthAvaiwabweFowImmediateFwip / TotImmediateFwipBytes;

	if (GPUVMEnabwe == twue) {
		TimeFowFetchingMetaPTEImmediateFwip = dmw_max3(
			Tno_bw + PDEAndMetaPTEBytesPewFwame * HostVMInefficiencyFactow / ImmediateFwipBW,
			UwgentExtwaWatency + UwgentWatency * (GPUVMMaxPageTabweWevews * (HostVMDynamicWevews + 1) - 1),
			WineTime / 4.0);
	} ewse {
		TimeFowFetchingMetaPTEImmediateFwip = 0;
	}

	*DestinationWinesToWequestVMInImmediateFwip = dmw_ceiw(4.0 * (TimeFowFetchingMetaPTEImmediateFwip / WineTime), 1) / 4.0;
	if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
		TimeFowFetchingWowInVBwankImmediateFwip = dmw_max3((MetaWowBytes + DPTEBytesPewWow) * HostVMInefficiencyFactow / ImmediateFwipBW, UwgentWatency * (HostVMDynamicWevews + 1), WineTime / 4);
	} ewse {
		TimeFowFetchingWowInVBwankImmediateFwip = 0;
	}

	*DestinationWinesToWequestWowInImmediateFwip = dmw_ceiw(4.0 * (TimeFowFetchingWowInVBwankImmediateFwip / WineTime), 1) / 4.0;
	*finaw_fwip_bw = dmw_max(PDEAndMetaPTEBytesPewFwame * HostVMInefficiencyFactow / (*DestinationWinesToWequestVMInImmediateFwip * WineTime), (MetaWowBytes + DPTEBytesPewWow) * HostVMInefficiencyFactow / (*DestinationWinesToWequestWowInImmediateFwip * WineTime));
	VWatioCwamped = (VWatio < 1.0) ? 1.0 : VWatio;
	if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10) {
		if (GPUVMEnabwe == twue && DCCEnabwe != twue) {
			min_wow_time = dmw_min(
					dpte_wow_height * WineTime / VWatioCwamped,
					dpte_wow_height_chwoma * WineTime / (VWatioCwamped / 2));
		} ewse if (GPUVMEnabwe != twue && DCCEnabwe == twue) {
			min_wow_time = dmw_min(
					meta_wow_height * WineTime / VWatioCwamped,
					meta_wow_height_chwoma * WineTime / (VWatioCwamped / 2));
		} ewse {
			min_wow_time = dmw_min4(
					dpte_wow_height * WineTime / VWatioCwamped,
					meta_wow_height * WineTime / VWatioCwamped,
					dpte_wow_height_chwoma * WineTime / (VWatioCwamped / 2),
					meta_wow_height_chwoma * WineTime / (VWatioCwamped / 2));
		}
	} ewse {
		if (GPUVMEnabwe == twue && DCCEnabwe != twue) {
			min_wow_time = dpte_wow_height * WineTime / VWatioCwamped;
		} ewse if (GPUVMEnabwe != twue && DCCEnabwe == twue) {
			min_wow_time = meta_wow_height * WineTime / VWatioCwamped;
		} ewse {
			min_wow_time = dmw_min(
					dpte_wow_height * WineTime / VWatioCwamped,
					meta_wow_height * WineTime / VWatioCwamped);
		}
	}

	if (*DestinationWinesToWequestVMInImmediateFwip >= 32
			|| *DestinationWinesToWequestWowInImmediateFwip >= 16
			|| TimeFowFetchingMetaPTEImmediateFwip + 2 * TimeFowFetchingWowInVBwankImmediateFwip > min_wow_time) {
		*ImmediateFwipSuppowtedFowPipe = fawse;
	} ewse {
		*ImmediateFwipSuppowtedFowPipe = twue;
	}
}

static unsigned int TwuncToVawidBPP(
		doubwe DecimawBPP,
		doubwe DesiwedBPP,
		boow DSCEnabwed,
		enum output_encodew_cwass Output,
		enum output_fowmat_cwass Fowmat,
		unsigned int DSCInputBitPewComponent)
{
	if (Output == dm_hdmi) {
		if (Fowmat == dm_420) {
			if (DecimawBPP >= 18 && (DesiwedBPP == 0 || DesiwedBPP == 18))
				wetuwn 18;
			ewse if (DecimawBPP >= 15 && (DesiwedBPP == 0 || DesiwedBPP == 15))
				wetuwn 15;
			ewse if (DecimawBPP >= 12 && (DesiwedBPP == 0 || DesiwedBPP == 12))
				wetuwn 12;
			ewse
				wetuwn BPP_INVAWID;
		} ewse if (Fowmat == dm_444) {
			if (DecimawBPP >= 36 && (DesiwedBPP == 0 || DesiwedBPP == 36))
				wetuwn 36;
			ewse if (DecimawBPP >= 30 && (DesiwedBPP == 0 || DesiwedBPP == 30))
				wetuwn 30;
			ewse if (DecimawBPP >= 24 && (DesiwedBPP == 0 || DesiwedBPP == 24))
				wetuwn 24;
			ewse if (DecimawBPP >= 18 && (DesiwedBPP == 0 || DesiwedBPP == 18))
				wetuwn 18;
			ewse
				wetuwn BPP_INVAWID;
		} ewse {
			if (DecimawBPP / 1.5 >= 24 && (DesiwedBPP == 0 || DesiwedBPP == 24))
				wetuwn 24;
			ewse if (DecimawBPP / 1.5 >= 20 && (DesiwedBPP == 0 || DesiwedBPP == 20))
				wetuwn 20;
			ewse if (DecimawBPP / 1.5 >= 16 && (DesiwedBPP == 0 || DesiwedBPP == 16))
				wetuwn 16;
			ewse
				wetuwn BPP_INVAWID;
		}
	} ewse {
		if (DSCEnabwed) {
			if (Fowmat == dm_420) {
				if (DesiwedBPP == 0) {
					if (DecimawBPP < 6)
						wetuwn BPP_INVAWID;
					ewse if (DecimawBPP >= 1.5 * DSCInputBitPewComponent - 1.0 / 16.0)
						wetuwn 1.5 * DSCInputBitPewComponent - 1.0 / 16.0;
					ewse
						wetuwn dmw_fwoow(16 * DecimawBPP, 1) / 16.0;
				} ewse {
					if (DecimawBPP < 6
							|| DesiwedBPP < 6
							|| DesiwedBPP > 1.5 * DSCInputBitPewComponent - 1.0 / 16.0
							|| DecimawBPP < DesiwedBPP) {
						wetuwn BPP_INVAWID;
					} ewse {
						wetuwn DesiwedBPP;
					}
				}
			} ewse if (Fowmat == dm_n422) {
				if (DesiwedBPP == 0) {
					if (DecimawBPP < 7)
						wetuwn BPP_INVAWID;
					ewse if (DecimawBPP >= 2 * DSCInputBitPewComponent - 1.0 / 16.0)
						wetuwn 2 * DSCInputBitPewComponent - 1.0 / 16.0;
					ewse
						wetuwn dmw_fwoow(16 * DecimawBPP, 1) / 16.0;
				} ewse {
					if (DecimawBPP < 7
							|| DesiwedBPP < 7
							|| DesiwedBPP > 2 * DSCInputBitPewComponent - 1.0 / 16.0
							|| DecimawBPP < DesiwedBPP) {
						wetuwn BPP_INVAWID;
					} ewse {
						wetuwn DesiwedBPP;
					}
				}
			} ewse {
				if (DesiwedBPP == 0) {
					if (DecimawBPP < 8)
						wetuwn BPP_INVAWID;
					ewse if (DecimawBPP >= 3 * DSCInputBitPewComponent - 1.0 / 16.0)
						wetuwn 3 * DSCInputBitPewComponent - 1.0 / 16.0;
					ewse
						wetuwn dmw_fwoow(16 * DecimawBPP, 1) / 16.0;
				} ewse {
					if (DecimawBPP < 8
							|| DesiwedBPP < 8
							|| DesiwedBPP > 3 * DSCInputBitPewComponent - 1.0 / 16.0
							|| DecimawBPP < DesiwedBPP) {
						wetuwn BPP_INVAWID;
					} ewse {
						wetuwn DesiwedBPP;
					}
				}
			}
		} ewse if (Fowmat == dm_420) {
			if (DecimawBPP >= 18 && (DesiwedBPP == 0 || DesiwedBPP == 18))
				wetuwn 18;
			ewse if (DecimawBPP >= 15 && (DesiwedBPP == 0 || DesiwedBPP == 15))
				wetuwn 15;
			ewse if (DecimawBPP >= 12 && (DesiwedBPP == 0 || DesiwedBPP == 12))
				wetuwn 12;
			ewse
				wetuwn BPP_INVAWID;
		} ewse if (Fowmat == dm_s422 || Fowmat == dm_n422) {
			if (DecimawBPP >= 24 && (DesiwedBPP == 0 || DesiwedBPP == 24))
				wetuwn 24;
			ewse if (DecimawBPP >= 20 && (DesiwedBPP == 0 || DesiwedBPP == 20))
				wetuwn 20;
			ewse if (DecimawBPP >= 16 && (DesiwedBPP == 0 || DesiwedBPP == 16))
				wetuwn 16;
			ewse
				wetuwn BPP_INVAWID;
		} ewse {
			if (DecimawBPP >= 36 && (DesiwedBPP == 0 || DesiwedBPP == 36))
				wetuwn 36;
			ewse if (DecimawBPP >= 30 && (DesiwedBPP == 0 || DesiwedBPP == 30))
				wetuwn 30;
			ewse if (DecimawBPP >= 24 && (DesiwedBPP == 0 || DesiwedBPP == 24))
				wetuwn 24;
			ewse if (DecimawBPP >= 18 && (DesiwedBPP == 0 || DesiwedBPP == 18))
				wetuwn 18;
			ewse
				wetuwn BPP_INVAWID;
		}
	}
}


static noinwine void CawcuwatePwefetchScheduwePewPwane(
		stwuct dispway_mode_wib *mode_wib,
		int i,
		unsigned j,
		unsigned k)
{
	stwuct vba_vaws_st *wocaws = &mode_wib->vba;
	Pipe myPipe;
	HostVM myHostVM;

	if (mode_wib->vba.XFCEnabwed[k] == twue) {
		mode_wib->vba.XFCWemoteSuwfaceFwipDeway =
				CawcuwateWemoteSuwfaceFwipDeway(
						mode_wib,
						mode_wib->vba.VWatio[k],
						wocaws->SwathWidthYThisState[k],
						dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1.0),
						mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
						mode_wib->vba.XFCTSwvVupdateOffset,
						mode_wib->vba.XFCTSwvVupdateWidth,
						mode_wib->vba.XFCTSwvVweadyOffset,
						mode_wib->vba.XFCXBUFWatencyTowewance,
						mode_wib->vba.XFCFiwwBWOvewhead,
						mode_wib->vba.XFCSwvChunkSize,
						mode_wib->vba.XFCBusTwanspowtTime,
						mode_wib->vba.TimeCawc,
						mode_wib->vba.TWait,
						&mode_wib->vba.SwcActiveDwainWate,
						&mode_wib->vba.TInitXFiww,
						&mode_wib->vba.TswvChk);
	} ewse {
		mode_wib->vba.XFCWemoteSuwfaceFwipDeway = 0.0;
	}

	myPipe.DPPCWK = wocaws->WequiwedDPPCWK[i][j][k];
	myPipe.DISPCWK = wocaws->WequiwedDISPCWK[i][j];
	myPipe.PixewCwock = mode_wib->vba.PixewCwock[k];
	myPipe.DCFCWKDeepSweep = mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0];
	myPipe.DPPPewPwane = wocaws->NoOfDPP[i][j][k];
	myPipe.ScawewEnabwed = mode_wib->vba.ScawewEnabwed[k];
	myPipe.SouwceScan = mode_wib->vba.SouwceScan[k];
	myPipe.BwockWidth256BytesY = wocaws->Wead256BwockWidthY[k];
	myPipe.BwockHeight256BytesY = wocaws->Wead256BwockHeightY[k];
	myPipe.BwockWidth256BytesC = wocaws->Wead256BwockWidthC[k];
	myPipe.BwockHeight256BytesC = wocaws->Wead256BwockHeightC[k];
	myPipe.IntewwaceEnabwe = mode_wib->vba.Intewwace[k];
	myPipe.NumbewOfCuwsows = mode_wib->vba.NumbewOfCuwsows[k];
	myPipe.VBwank = mode_wib->vba.VTotaw[k] - mode_wib->vba.VActive[k];
	myPipe.HTotaw = mode_wib->vba.HTotaw[k];


	myHostVM.Enabwe = mode_wib->vba.HostVMEnabwe;
	myHostVM.MaxPageTabweWevews = mode_wib->vba.HostVMMaxPageTabweWevews;
	myHostVM.CachedPageTabweWevews = mode_wib->vba.HostVMCachedPageTabweWevews;


	mode_wib->vba.IsEwwowWesuwt[i][j][k] = CawcuwatePwefetchScheduwe(
			mode_wib,
			mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
			mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
			&myPipe,
			wocaws->DSCDewayPewState[i][k],
			mode_wib->vba.DPPCWKDewaySubtotaw,
			mode_wib->vba.DPPCWKDewaySCW,
			mode_wib->vba.DPPCWKDewaySCWWBOnwy,
			mode_wib->vba.DPPCWKDewayCNVCFowmatew,
			mode_wib->vba.DPPCWKDewayCNVCCuwsow,
			mode_wib->vba.DISPCWKDewaySubtotaw,
			wocaws->SwathWidthYThisState[k] / mode_wib->vba.HWatio[k],
			mode_wib->vba.OutputFowmat[k],
			mode_wib->vba.MaxIntewDCNTiweWepeatews,
			dmw_min(mode_wib->vba.MaxVStawtup, wocaws->MaximumVStawtup[0][0][k]),
			wocaws->MaximumVStawtup[0][0][k],
			mode_wib->vba.GPUVMMaxPageTabweWevews,
			mode_wib->vba.GPUVMEnabwe,
			&myHostVM,
			mode_wib->vba.DynamicMetadataEnabwe[k],
			mode_wib->vba.DynamicMetadataWinesBefoweActiveWequiwed[k],
			mode_wib->vba.DynamicMetadataTwansmittedBytes[k],
			mode_wib->vba.DCCEnabwe[k],
			mode_wib->vba.UwgentWatency,
			mode_wib->vba.ExtwaWatency,
			mode_wib->vba.TimeCawc,
			wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k],
			wocaws->MetaWowBytes[0][0][k],
			wocaws->DPTEBytesPewWow[0][0][k],
			wocaws->PwefetchWinesY[0][0][k],
			wocaws->SwathWidthYThisState[k],
			wocaws->BytePewPixewInDETY[k],
			wocaws->PwefiwwY[k],
			wocaws->MaxNumSwY[k],
			wocaws->PwefetchWinesC[0][0][k],
			wocaws->BytePewPixewInDETC[k],
			wocaws->PwefiwwC[k],
			wocaws->MaxNumSwC[k],
			wocaws->SwathHeightYThisState[k],
			wocaws->SwathHeightCThisState[k],
			mode_wib->vba.TWait,
			mode_wib->vba.XFCEnabwed[k],
			mode_wib->vba.XFCWemoteSuwfaceFwipDeway,
			mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
			&wocaws->dst_x_aftew_scawew,
			&wocaws->dst_y_aftew_scawew,
			&wocaws->WineTimesFowPwefetch[k],
			&wocaws->PwefetchBW[k],
			&wocaws->WinesFowMetaPTE[k],
			&wocaws->WinesFowMetaAndDPTEWow[k],
			&wocaws->VWatioPweY[i][j][k],
			&wocaws->VWatioPweC[i][j][k],
			&wocaws->WequiwedPwefetchPixewDataBWWuma[i][j][k],
			&wocaws->WequiwedPwefetchPixewDataBWChwoma[i][j][k],
			&wocaws->VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
			&wocaws->Tno_bw[k],
			&wocaws->pwefetch_vmwow_bw[k],
			wocaws->swath_width_wuma_ub,
			wocaws->swath_width_chwoma_ub,
			&mode_wib->vba.VUpdateOffsetPix[k],
			&mode_wib->vba.VUpdateWidthPix[k],
			&mode_wib->vba.VWeadyOffsetPix[k]);
}
void dmw21_ModeSuppowtAndSystemConfiguwationFuww(stwuct dispway_mode_wib *mode_wib)
{
	stwuct vba_vaws_st *wocaws = &mode_wib->vba;

	int i;
	unsigned int j, k, m;

	/*MODE SUPPOWT, VOWTAGE STATE AND SOC CONFIGUWATION*/

	/*Scawe Watio, taps Suppowt Check*/

	mode_wib->vba.ScaweWatioAndTapsSuppowt = twue;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.ScawewEnabwed[k] == fawse
				&& ((mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_8)
						|| mode_wib->vba.HWatio[k] != 1.0
						|| mode_wib->vba.htaps[k] != 1.0
						|| mode_wib->vba.VWatio[k] != 1.0
						|| mode_wib->vba.vtaps[k] != 1.0)) {
			mode_wib->vba.ScaweWatioAndTapsSuppowt = fawse;
		} ewse if (mode_wib->vba.vtaps[k] < 1.0 || mode_wib->vba.vtaps[k] > 8.0
				|| mode_wib->vba.htaps[k] < 1.0 || mode_wib->vba.htaps[k] > 8.0
				|| (mode_wib->vba.htaps[k] > 1.0
						&& (mode_wib->vba.htaps[k] % 2) == 1)
				|| mode_wib->vba.HWatio[k] > mode_wib->vba.MaxHSCWWatio
				|| mode_wib->vba.VWatio[k] > mode_wib->vba.MaxVSCWWatio
				|| mode_wib->vba.HWatio[k] > mode_wib->vba.htaps[k]
				|| mode_wib->vba.VWatio[k] > mode_wib->vba.vtaps[k]
				|| (mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_8
						&& (mode_wib->vba.HWatio[k] / 2.0
								> mode_wib->vba.HTAPsChwoma[k]
								|| mode_wib->vba.VWatio[k] / 2.0
										> mode_wib->vba.VTAPsChwoma[k]))) {
			mode_wib->vba.ScaweWatioAndTapsSuppowt = fawse;
		}
	}
	/*Souwce Fowmat, Pixew Fowmat and Scan Suppowt Check*/

	mode_wib->vba.SouwceFowmatPixewAndScanSuppowt = twue;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if ((mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw
				&& mode_wib->vba.SouwceScan[k] != dm_howz)
				|| ((mode_wib->vba.SuwfaceTiwing[k] == dm_sw_4kb_d
						|| mode_wib->vba.SuwfaceTiwing[k] == dm_sw_4kb_d_x
						|| mode_wib->vba.SuwfaceTiwing[k] == dm_sw_64kb_d
						|| mode_wib->vba.SuwfaceTiwing[k] == dm_sw_64kb_d_t
						|| mode_wib->vba.SuwfaceTiwing[k] == dm_sw_64kb_d_x
						|| mode_wib->vba.SuwfaceTiwing[k] == dm_sw_vaw_d
						|| mode_wib->vba.SuwfaceTiwing[k] == dm_sw_vaw_d_x)
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64)
				|| (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_64kb_w_x
						&& (mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_8
								|| mode_wib->vba.SouwcePixewFowmat[k]
										== dm_420_8
								|| mode_wib->vba.SouwcePixewFowmat[k]
										== dm_420_10))
				|| (((mode_wib->vba.SuwfaceTiwing[k] == dm_sw_gfx7_2d_thin_gw
						|| mode_wib->vba.SuwfaceTiwing[k]
								== dm_sw_gfx7_2d_thin_w_vp)
						&& !((mode_wib->vba.SouwcePixewFowmat[k]
								== dm_444_64
								|| mode_wib->vba.SouwcePixewFowmat[k]
										== dm_444_32)
								&& mode_wib->vba.SouwceScan[k]
										== dm_howz
								&& mode_wib->vba.SuppowtGFX7CompatibweTiwingIn32bppAnd64bpp
										== twue
								&& mode_wib->vba.DCCEnabwe[k]
										== fawse))
						|| (mode_wib->vba.DCCEnabwe[k] == twue
								&& (mode_wib->vba.SuwfaceTiwing[k]
										== dm_sw_wineaw
										|| mode_wib->vba.SouwcePixewFowmat[k]
												== dm_420_8
										|| mode_wib->vba.SouwcePixewFowmat[k]
												== dm_420_10)))) {
			mode_wib->vba.SouwceFowmatPixewAndScanSuppowt = fawse;
		}
	}
	/*Bandwidth Suppowt Check*/

	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64) {
			wocaws->BytePewPixewInDETY[k] = 8.0;
			wocaws->BytePewPixewInDETC[k] = 0.0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32) {
			wocaws->BytePewPixewInDETY[k] = 4.0;
			wocaws->BytePewPixewInDETC[k] = 0.0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_16) {
			wocaws->BytePewPixewInDETY[k] = 2.0;
			wocaws->BytePewPixewInDETC[k] = 0.0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_8) {
			wocaws->BytePewPixewInDETY[k] = 1.0;
			wocaws->BytePewPixewInDETC[k] = 0.0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8) {
			wocaws->BytePewPixewInDETY[k] = 1.0;
			wocaws->BytePewPixewInDETC[k] = 2.0;
		} ewse {
			wocaws->BytePewPixewInDETY[k] = 4.0 / 3;
			wocaws->BytePewPixewInDETC[k] = 8.0 / 3;
		}
		if (mode_wib->vba.SouwceScan[k] == dm_howz) {
			wocaws->SwathWidthYSingweDPP[k] = mode_wib->vba.ViewpowtWidth[k];
		} ewse {
			wocaws->SwathWidthYSingweDPP[k] = mode_wib->vba.ViewpowtHeight[k];
		}
	}
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		wocaws->WeadBandwidthWuma[k] = wocaws->SwathWidthYSingweDPP[k] * dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1.0)
				/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]) * mode_wib->vba.VWatio[k];
		wocaws->WeadBandwidthChwoma[k] = wocaws->SwathWidthYSingweDPP[k] / 2 * dmw_ceiw(wocaws->BytePewPixewInDETC[k], 2.0)
				/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]) * mode_wib->vba.VWatio[k] / 2.0;
		wocaws->WeadBandwidth[k] = wocaws->WeadBandwidthWuma[k] + wocaws->WeadBandwidthChwoma[k];
	}
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue
				&& mode_wib->vba.WwitebackPixewFowmat[k] == dm_444_32) {
			wocaws->WwiteBandwidth[k] = mode_wib->vba.WwitebackDestinationWidth[k]
					* mode_wib->vba.WwitebackDestinationHeight[k]
					/ (mode_wib->vba.WwitebackSouwceHeight[k]
							* mode_wib->vba.HTotaw[k]
							/ mode_wib->vba.PixewCwock[k]) * 4.0;
		} ewse if (mode_wib->vba.WwitebackEnabwe[k] == twue
				&& mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_10) {
			wocaws->WwiteBandwidth[k] = mode_wib->vba.WwitebackDestinationWidth[k]
					* mode_wib->vba.WwitebackDestinationHeight[k]
					/ (mode_wib->vba.WwitebackSouwceHeight[k]
							* mode_wib->vba.HTotaw[k]
							/ mode_wib->vba.PixewCwock[k]) * 3.0;
		} ewse if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
			wocaws->WwiteBandwidth[k] = mode_wib->vba.WwitebackDestinationWidth[k]
					* mode_wib->vba.WwitebackDestinationHeight[k]
					/ (mode_wib->vba.WwitebackSouwceHeight[k]
							* mode_wib->vba.HTotaw[k]
							/ mode_wib->vba.PixewCwock[k]) * 1.5;
		} ewse {
			wocaws->WwiteBandwidth[k] = 0.0;
		}
	}
	mode_wib->vba.DCCEnabwedInAnyPwane = fawse;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.DCCEnabwe[k] == twue) {
			mode_wib->vba.DCCEnabwedInAnyPwane = twue;
		}
	}
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		wocaws->IdeawSDPPowtBandwidthPewState[i][0] = dmw_min3(
				mode_wib->vba.WetuwnBusWidth * mode_wib->vba.DCFCWKPewState[i],
				mode_wib->vba.DWAMSpeedPewState[i] * mode_wib->vba.NumbewOfChannews
						* mode_wib->vba.DWAMChannewWidth,
				mode_wib->vba.FabwicCwockPewState[i]
						* mode_wib->vba.FabwicDatapathToDCNDataWetuwn);
		if (mode_wib->vba.HostVMEnabwe == fawse) {
			wocaws->WetuwnBWPewState[i][0] = wocaws->IdeawSDPPowtBandwidthPewState[i][0]
					* mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewDataOnwy / 100.0;
		} ewse {
			wocaws->WetuwnBWPewState[i][0] = wocaws->IdeawSDPPowtBandwidthPewState[i][0]
					* mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData / 100.0;
		}
	}
	/*Wwiteback Watency suppowt check*/

	mode_wib->vba.WwitebackWatencySuppowt = twue;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
			if (mode_wib->vba.WwitebackPixewFowmat[k] == dm_444_32) {
				if (wocaws->WwiteBandwidth[k]
						> (mode_wib->vba.WwitebackIntewfaceWumaBuffewSize
								+ mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize)
								/ mode_wib->vba.WwitebackWatency) {
					mode_wib->vba.WwitebackWatencySuppowt = fawse;
				}
			} ewse {
				if (wocaws->WwiteBandwidth[k]
						> 1.5
								* dmw_min(
										mode_wib->vba.WwitebackIntewfaceWumaBuffewSize,
										2.0
												* mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize)
								/ mode_wib->vba.WwitebackWatency) {
					mode_wib->vba.WwitebackWatencySuppowt = fawse;
				}
			}
		}
	}
	/*We-owdewing Buffew Suppowt Check*/

	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		wocaws->UwgentWoundTwipAndOutOfOwdewWatencyPewState[i] =
				(mode_wib->vba.WoundTwipPingWatencyCycwes + 32.0) / mode_wib->vba.DCFCWKPewState[i]
				+ dmw_max3(mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewDataOnwy,
						mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewMixedWithVMData,
						mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewVMDataOnwy)
					* mode_wib->vba.NumbewOfChannews / wocaws->WetuwnBWPewState[i][0];
		if ((mode_wib->vba.WOBBuffewSizeInKByte - mode_wib->vba.PixewChunkSizeInKByte) * 1024.0 / wocaws->WetuwnBWPewState[i][0]
				> wocaws->UwgentWoundTwipAndOutOfOwdewWatencyPewState[i]) {
			wocaws->WOBSuppowt[i][0] = twue;
		} ewse {
			wocaws->WOBSuppowt[i][0] = fawse;
		}
	}
	/*Wwiteback Mode Suppowt Check*/

	mode_wib->vba.TotawNumbewOfActiveWwiteback = 0;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
			if (mode_wib->vba.ActiveWwitebacksPewPwane[k] == 0)
				mode_wib->vba.ActiveWwitebacksPewPwane[k] = 1;
			mode_wib->vba.TotawNumbewOfActiveWwiteback =
					mode_wib->vba.TotawNumbewOfActiveWwiteback
							+ mode_wib->vba.ActiveWwitebacksPewPwane[k];
		}
	}
	mode_wib->vba.WwitebackModeSuppowt = twue;
	if (mode_wib->vba.TotawNumbewOfActiveWwiteback > mode_wib->vba.MaxNumWwiteback) {
		mode_wib->vba.WwitebackModeSuppowt = fawse;
	}
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue
				&& mode_wib->vba.Wwiteback10bpc420Suppowted != twue
				&& mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_10) {
			mode_wib->vba.WwitebackModeSuppowt = fawse;
		}
	}
	/*Wwiteback Scawe Watio and Taps Suppowt Check*/

	mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt = twue;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
			if (mode_wib->vba.WwitebackWumaAndChwomaScawingSuppowted == fawse
					&& (mode_wib->vba.WwitebackHWatio[k] != 1.0
							|| mode_wib->vba.WwitebackVWatio[k] != 1.0)) {
				mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt = fawse;
			}
			if (mode_wib->vba.WwitebackHWatio[k] > mode_wib->vba.WwitebackMaxHSCWWatio
					|| mode_wib->vba.WwitebackVWatio[k]
							> mode_wib->vba.WwitebackMaxVSCWWatio
					|| mode_wib->vba.WwitebackHWatio[k]
							< mode_wib->vba.WwitebackMinHSCWWatio
					|| mode_wib->vba.WwitebackVWatio[k]
							< mode_wib->vba.WwitebackMinVSCWWatio
					|| mode_wib->vba.WwitebackWumaHTaps[k]
							> mode_wib->vba.WwitebackMaxHSCWTaps
					|| mode_wib->vba.WwitebackWumaVTaps[k]
							> mode_wib->vba.WwitebackMaxVSCWTaps
					|| mode_wib->vba.WwitebackHWatio[k]
							> mode_wib->vba.WwitebackWumaHTaps[k]
					|| mode_wib->vba.WwitebackVWatio[k]
							> mode_wib->vba.WwitebackWumaVTaps[k]
					|| (mode_wib->vba.WwitebackWumaHTaps[k] > 2.0
							&& ((mode_wib->vba.WwitebackWumaHTaps[k] % 2)
									== 1))
					|| (mode_wib->vba.WwitebackPixewFowmat[k] != dm_444_32
							&& (mode_wib->vba.WwitebackChwomaHTaps[k]
									> mode_wib->vba.WwitebackMaxHSCWTaps
									|| mode_wib->vba.WwitebackChwomaVTaps[k]
											> mode_wib->vba.WwitebackMaxVSCWTaps
									|| 2.0
											* mode_wib->vba.WwitebackHWatio[k]
											> mode_wib->vba.WwitebackChwomaHTaps[k]
									|| 2.0
											* mode_wib->vba.WwitebackVWatio[k]
											> mode_wib->vba.WwitebackChwomaVTaps[k]
									|| (mode_wib->vba.WwitebackChwomaHTaps[k] > 2.0
										&& ((mode_wib->vba.WwitebackChwomaHTaps[k] % 2) == 1))))) {
				mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt = fawse;
			}
			if (mode_wib->vba.WwitebackVWatio[k] < 1.0) {
				mode_wib->vba.WwitebackWumaVExtwa =
						dmw_max(1.0 - 2.0 / dmw_ceiw(1.0 / mode_wib->vba.WwitebackVWatio[k], 1.0), 0.0);
			} ewse {
				mode_wib->vba.WwitebackWumaVExtwa = -1;
			}
			if ((mode_wib->vba.WwitebackPixewFowmat[k] == dm_444_32
					&& mode_wib->vba.WwitebackWumaVTaps[k]
							> (mode_wib->vba.WwitebackWineBuffewWumaBuffewSize
									+ mode_wib->vba.WwitebackWineBuffewChwomaBuffewSize)
									/ 3.0
									/ mode_wib->vba.WwitebackDestinationWidth[k]
									- mode_wib->vba.WwitebackWumaVExtwa)
					|| (mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_8
							&& mode_wib->vba.WwitebackWumaVTaps[k]
									> mode_wib->vba.WwitebackWineBuffewWumaBuffewSize
											* 8.0 / 10.0 / mode_wib->vba.WwitebackDestinationWidth[k]
											- mode_wib->vba.WwitebackWumaVExtwa)
					|| (mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_10
							&& mode_wib->vba.WwitebackWumaVTaps[k]
									> mode_wib->vba.WwitebackWineBuffewWumaBuffewSize
											* 8.0 / 10.0
											/ mode_wib->vba.WwitebackDestinationWidth[k]
											- mode_wib->vba.WwitebackWumaVExtwa)) {
				mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt = fawse;
			}
			if (2.0 * mode_wib->vba.WwitebackVWatio[k] < 1) {
				mode_wib->vba.WwitebackChwomaVExtwa = 0.0;
			} ewse {
				mode_wib->vba.WwitebackChwomaVExtwa = -1;
			}
			if ((mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_8
					&& mode_wib->vba.WwitebackChwomaVTaps[k]
							> mode_wib->vba.WwitebackWineBuffewChwomaBuffewSize
									* 8.0 / 10.0 / mode_wib->vba.WwitebackDestinationWidth[k]
									- mode_wib->vba.WwitebackChwomaVExtwa)
					|| (mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_10
							&& mode_wib->vba.WwitebackChwomaVTaps[k]
									> mode_wib->vba.WwitebackWineBuffewChwomaBuffewSize
											* 8.0 / 10.0
											/ mode_wib->vba.WwitebackDestinationWidth[k]
											- mode_wib->vba.WwitebackChwomaVExtwa)) {
				mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt = fawse;
			}
		}
	}
	/*Maximum DISPCWK/DPPCWK Suppowt check*/

	mode_wib->vba.WwitebackWequiwedDISPCWK = 0.0;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
			mode_wib->vba.WwitebackWequiwedDISPCWK =
					dmw_max(
							mode_wib->vba.WwitebackWequiwedDISPCWK,
							CawcuwateWwiteBackDISPCWK(
									mode_wib->vba.WwitebackPixewFowmat[k],
									mode_wib->vba.PixewCwock[k],
									mode_wib->vba.WwitebackHWatio[k],
									mode_wib->vba.WwitebackVWatio[k],
									mode_wib->vba.WwitebackWumaHTaps[k],
									mode_wib->vba.WwitebackWumaVTaps[k],
									mode_wib->vba.WwitebackChwomaHTaps[k],
									mode_wib->vba.WwitebackChwomaVTaps[k],
									mode_wib->vba.WwitebackDestinationWidth[k],
									mode_wib->vba.HTotaw[k],
									mode_wib->vba.WwitebackChwomaWineBuffewWidth));
		}
	}
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.HWatio[k] > 1.0) {
			wocaws->PSCW_FACTOW[k] = dmw_min(
					mode_wib->vba.MaxDCHUBToPSCWThwoughput,
					mode_wib->vba.MaxPSCWToWBThwoughput
							* mode_wib->vba.HWatio[k]
							/ dmw_ceiw(
									mode_wib->vba.htaps[k]
											/ 6.0,
									1.0));
		} ewse {
			wocaws->PSCW_FACTOW[k] = dmw_min(
					mode_wib->vba.MaxDCHUBToPSCWThwoughput,
					mode_wib->vba.MaxPSCWToWBThwoughput);
		}
		if (wocaws->BytePewPixewInDETC[k] == 0.0) {
			wocaws->PSCW_FACTOW_CHWOMA[k] = 0.0;
			wocaws->MinDPPCWKUsingSingweDPP[k] =
					mode_wib->vba.PixewCwock[k]
							* dmw_max3(
									mode_wib->vba.vtaps[k] / 6.0
											* dmw_min(
													1.0,
													mode_wib->vba.HWatio[k]),
									mode_wib->vba.HWatio[k]
											* mode_wib->vba.VWatio[k]
											/ wocaws->PSCW_FACTOW[k],
									1.0);
			if ((mode_wib->vba.htaps[k] > 6.0 || mode_wib->vba.vtaps[k] > 6.0)
					&& wocaws->MinDPPCWKUsingSingweDPP[k]
							< 2.0 * mode_wib->vba.PixewCwock[k]) {
				wocaws->MinDPPCWKUsingSingweDPP[k] = 2.0
						* mode_wib->vba.PixewCwock[k];
			}
		} ewse {
			if (mode_wib->vba.HWatio[k] / 2.0 > 1.0) {
				wocaws->PSCW_FACTOW_CHWOMA[k] =
						dmw_min(
								mode_wib->vba.MaxDCHUBToPSCWThwoughput,
								mode_wib->vba.MaxPSCWToWBThwoughput
										* mode_wib->vba.HWatio[k]
										/ 2.0
										/ dmw_ceiw(
												mode_wib->vba.HTAPsChwoma[k]
														/ 6.0,
												1.0));
			} ewse {
				wocaws->PSCW_FACTOW_CHWOMA[k] = dmw_min(
						mode_wib->vba.MaxDCHUBToPSCWThwoughput,
						mode_wib->vba.MaxPSCWToWBThwoughput);
			}
			wocaws->MinDPPCWKUsingSingweDPP[k] =
					mode_wib->vba.PixewCwock[k]
							* dmw_max5(
									mode_wib->vba.vtaps[k] / 6.0
											* dmw_min(
													1.0,
													mode_wib->vba.HWatio[k]),
									mode_wib->vba.HWatio[k]
											* mode_wib->vba.VWatio[k]
											/ wocaws->PSCW_FACTOW[k],
									mode_wib->vba.VTAPsChwoma[k]
											/ 6.0
											* dmw_min(
													1.0,
													mode_wib->vba.HWatio[k]
															/ 2.0),
									mode_wib->vba.HWatio[k]
											* mode_wib->vba.VWatio[k]
											/ 4.0
											/ wocaws->PSCW_FACTOW_CHWOMA[k],
									1.0);
			if ((mode_wib->vba.htaps[k] > 6.0 || mode_wib->vba.vtaps[k] > 6.0
					|| mode_wib->vba.HTAPsChwoma[k] > 6.0
					|| mode_wib->vba.VTAPsChwoma[k] > 6.0)
					&& wocaws->MinDPPCWKUsingSingweDPP[k]
							< 2.0 * mode_wib->vba.PixewCwock[k]) {
				wocaws->MinDPPCWKUsingSingweDPP[k] = 2.0
						* mode_wib->vba.PixewCwock[k];
			}
		}
	}
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		Cawcuwate256BBwockSizes(
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.SuwfaceTiwing[k],
				dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1.0),
				dmw_ceiw(wocaws->BytePewPixewInDETC[k], 2.0),
				&wocaws->Wead256BwockHeightY[k],
				&wocaws->Wead256BwockHeightC[k],
				&wocaws->Wead256BwockWidthY[k],
				&wocaws->Wead256BwockWidthC[k]);
		if (mode_wib->vba.SouwceScan[k] == dm_howz) {
			wocaws->MaxSwathHeightY[k] = wocaws->Wead256BwockHeightY[k];
			wocaws->MaxSwathHeightC[k] = wocaws->Wead256BwockHeightC[k];
		} ewse {
			wocaws->MaxSwathHeightY[k] = wocaws->Wead256BwockWidthY[k];
			wocaws->MaxSwathHeightC[k] = wocaws->Wead256BwockWidthC[k];
		}
		if ((mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_16
				|| mode_wib->vba.SouwcePixewFowmat[k] == dm_mono_8)) {
			if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw
					|| (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64
							&& (mode_wib->vba.SuwfaceTiwing[k]
									== dm_sw_4kb_s
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_4kb_s_x
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_64kb_s
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_64kb_s_t
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_64kb_s_x
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_vaw_s
									|| mode_wib->vba.SuwfaceTiwing[k]
											== dm_sw_vaw_s_x)
							&& mode_wib->vba.SouwceScan[k] == dm_howz)) {
				wocaws->MinSwathHeightY[k] = wocaws->MaxSwathHeightY[k];
			} ewse {
				wocaws->MinSwathHeightY[k] = wocaws->MaxSwathHeightY[k]
						/ 2.0;
			}
			wocaws->MinSwathHeightC[k] = wocaws->MaxSwathHeightC[k];
		} ewse {
			if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw) {
				wocaws->MinSwathHeightY[k] = wocaws->MaxSwathHeightY[k];
				wocaws->MinSwathHeightC[k] = wocaws->MaxSwathHeightC[k];
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8
					&& mode_wib->vba.SouwceScan[k] == dm_howz) {
				wocaws->MinSwathHeightY[k] = wocaws->MaxSwathHeightY[k]
						/ 2.0;
				wocaws->MinSwathHeightC[k] = wocaws->MaxSwathHeightC[k];
			} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_10
					&& mode_wib->vba.SouwceScan[k] == dm_howz) {
				wocaws->MinSwathHeightC[k] = wocaws->MaxSwathHeightC[k]
						/ 2.0;
				wocaws->MinSwathHeightY[k] = wocaws->MaxSwathHeightY[k];
			} ewse {
				wocaws->MinSwathHeightY[k] = wocaws->MaxSwathHeightY[k];
				wocaws->MinSwathHeightC[k] = wocaws->MaxSwathHeightC[k];
			}
		}
		if (mode_wib->vba.SuwfaceTiwing[k] == dm_sw_wineaw) {
			mode_wib->vba.MaximumSwathWidthSuppowt = 8192.0;
		} ewse {
			mode_wib->vba.MaximumSwathWidthSuppowt = 5120.0;
		}
		mode_wib->vba.MaximumSwathWidthInDETBuffew =
				dmw_min(
						mode_wib->vba.MaximumSwathWidthSuppowt,
						mode_wib->vba.DETBuffewSizeInKByte[0] * 1024.0 / 2.0
								/ (wocaws->BytePewPixewInDETY[k]
										* wocaws->MinSwathHeightY[k]
										+ wocaws->BytePewPixewInDETC[k]
												/ 2.0
												* wocaws->MinSwathHeightC[k]));
		if (wocaws->BytePewPixewInDETC[k] == 0.0) {
			mode_wib->vba.MaximumSwathWidthInWineBuffew =
					mode_wib->vba.WineBuffewSize
							* dmw_max(mode_wib->vba.HWatio[k], 1.0)
							/ mode_wib->vba.WBBitPewPixew[k]
							/ (mode_wib->vba.vtaps[k]
									+ dmw_max(
											dmw_ceiw(
													mode_wib->vba.VWatio[k],
													1.0)
													- 2,
											0.0));
		} ewse {
			mode_wib->vba.MaximumSwathWidthInWineBuffew =
					dmw_min(
							mode_wib->vba.WineBuffewSize
									* dmw_max(
											mode_wib->vba.HWatio[k],
											1.0)
									/ mode_wib->vba.WBBitPewPixew[k]
									/ (mode_wib->vba.vtaps[k]
											+ dmw_max(
													dmw_ceiw(
															mode_wib->vba.VWatio[k],
															1.0)
															- 2,
													0.0)),
							2.0 * mode_wib->vba.WineBuffewSize
									* dmw_max(
											mode_wib->vba.HWatio[k]
													/ 2.0,
											1.0)
									/ mode_wib->vba.WBBitPewPixew[k]
									/ (mode_wib->vba.VTAPsChwoma[k]
											+ dmw_max(
													dmw_ceiw(
															mode_wib->vba.VWatio[k]
																	/ 2.0,
															1.0)
															- 2,
													0.0)));
		}
		wocaws->MaximumSwathWidth[k] = dmw_min(
				mode_wib->vba.MaximumSwathWidthInDETBuffew,
				mode_wib->vba.MaximumSwathWidthInWineBuffew);
	}
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		doubwe MaxMaxDispcwkWoundedDown = WoundToDFSGwanuwawityDown(
			mode_wib->vba.MaxDispcwk[mode_wib->vba.soc.num_states],
			mode_wib->vba.DISPCWKDPPCWKVCOSpeed);

		fow (j = 0; j < 2; j++) {
			mode_wib->vba.MaxDispcwkWoundedDownToDFSGwanuwawity = WoundToDFSGwanuwawityDown(
				mode_wib->vba.MaxDispcwk[i],
				mode_wib->vba.DISPCWKDPPCWKVCOSpeed);
			mode_wib->vba.MaxDppcwkWoundedDownToDFSGwanuwawity = WoundToDFSGwanuwawityDown(
				mode_wib->vba.MaxDppcwk[i],
				mode_wib->vba.DISPCWKDPPCWKVCOSpeed);
			wocaws->WequiwedDISPCWK[i][j] = 0.0;
			wocaws->DISPCWK_DPPCWK_Suppowt[i][j] = twue;
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				mode_wib->vba.PwaneWequiwedDISPCWKWithoutODMCombine =
						mode_wib->vba.PixewCwock[k]
								* (1.0
										+ mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
												/ 100.0)
								* (1.0
										+ mode_wib->vba.DISPCWKWampingMawgin
												/ 100.0);
				if (mode_wib->vba.PwaneWequiwedDISPCWKWithoutODMCombine >= mode_wib->vba.MaxDispcwk[i]
						&& i == mode_wib->vba.soc.num_states)
					mode_wib->vba.PwaneWequiwedDISPCWKWithoutODMCombine = mode_wib->vba.PixewCwock[k]
							* (1 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0);

				mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine = mode_wib->vba.PixewCwock[k] / 2
					* (1 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) * (1 + mode_wib->vba.DISPCWKWampingMawgin / 100.0);
				if (mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine >= mode_wib->vba.MaxDispcwk[i]
						&& i == mode_wib->vba.soc.num_states)
					mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine = mode_wib->vba.PixewCwock[k] / 2
							* (1 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0);

				wocaws->ODMCombineEnabwePewState[i][k] = dm_odm_combine_mode_disabwed;
				mode_wib->vba.PwaneWequiwedDISPCWK = mode_wib->vba.PwaneWequiwedDISPCWKWithoutODMCombine;
				if (mode_wib->vba.ODMCapabiwity) {
					if (wocaws->PwaneWequiwedDISPCWKWithoutODMCombine > MaxMaxDispcwkWoundedDown) {
						wocaws->ODMCombineEnabwePewState[i][k] = dm_odm_combine_mode_2to1;
						mode_wib->vba.PwaneWequiwedDISPCWK = mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine;
					} ewse if (wocaws->DSCEnabwed[k] && (wocaws->HActive[k] > DCN21_MAX_DSC_IMAGE_WIDTH)) {
						wocaws->ODMCombineEnabwePewState[i][k] = dm_odm_combine_mode_2to1;
						mode_wib->vba.PwaneWequiwedDISPCWK = mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine;
					} ewse if (wocaws->HActive[k] > DCN21_MAX_420_IMAGE_WIDTH && wocaws->OutputFowmat[k] == dm_420) {
						wocaws->ODMCombineEnabwePewState[i][k] = dm_odm_combine_mode_2to1;
						mode_wib->vba.PwaneWequiwedDISPCWK = mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine;
					}
				}

				if (wocaws->MinDPPCWKUsingSingweDPP[k] * (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) <= mode_wib->vba.MaxDppcwkWoundedDownToDFSGwanuwawity
						&& wocaws->SwathWidthYSingweDPP[k] <= wocaws->MaximumSwathWidth[k]
						&& wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_disabwed) {
					wocaws->NoOfDPP[i][j][k] = 1;
					wocaws->WequiwedDPPCWK[i][j][k] =
						wocaws->MinDPPCWKUsingSingweDPP[k] * (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0);
				} ewse {
					wocaws->NoOfDPP[i][j][k] = 2;
					wocaws->WequiwedDPPCWK[i][j][k] =
						wocaws->MinDPPCWKUsingSingweDPP[k] * (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) / 2.0;
				}
				wocaws->WequiwedDISPCWK[i][j] = dmw_max(
						wocaws->WequiwedDISPCWK[i][j],
						mode_wib->vba.PwaneWequiwedDISPCWK);
				if ((wocaws->MinDPPCWKUsingSingweDPP[k] / wocaws->NoOfDPP[i][j][k] * (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0)
						> mode_wib->vba.MaxDppcwkWoundedDownToDFSGwanuwawity)
						|| (mode_wib->vba.PwaneWequiwedDISPCWK > mode_wib->vba.MaxDispcwkWoundedDownToDFSGwanuwawity)) {
					wocaws->DISPCWK_DPPCWK_Suppowt[i][j] = fawse;
				}
			}
			wocaws->TotawNumbewOfActiveDPP[i][j] = 0.0;
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++)
				wocaws->TotawNumbewOfActiveDPP[i][j] = wocaws->TotawNumbewOfActiveDPP[i][j] + wocaws->NoOfDPP[i][j][k];
			if (j == 1) {
				whiwe (wocaws->TotawNumbewOfActiveDPP[i][j] < mode_wib->vba.MaxNumDPP
						&& wocaws->TotawNumbewOfActiveDPP[i][j] < 2 * mode_wib->vba.NumbewOfActivePwanes) {
					doubwe BWOfNonSpwitPwaneOfMaximumBandwidth;
					unsigned int NumbewOfNonSpwitPwaneOfMaximumBandwidth;

					BWOfNonSpwitPwaneOfMaximumBandwidth = 0;
					NumbewOfNonSpwitPwaneOfMaximumBandwidth = 0;
					fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
						if (wocaws->WeadBandwidth[k] > BWOfNonSpwitPwaneOfMaximumBandwidth && wocaws->NoOfDPP[i][j][k] == 1) {
							BWOfNonSpwitPwaneOfMaximumBandwidth = wocaws->WeadBandwidth[k];
							NumbewOfNonSpwitPwaneOfMaximumBandwidth = k;
						}
					}
					wocaws->NoOfDPP[i][j][NumbewOfNonSpwitPwaneOfMaximumBandwidth] = 2;
					wocaws->WequiwedDPPCWK[i][j][NumbewOfNonSpwitPwaneOfMaximumBandwidth] =
						wocaws->MinDPPCWKUsingSingweDPP[NumbewOfNonSpwitPwaneOfMaximumBandwidth]
							* (1 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100) / 2;
					wocaws->TotawNumbewOfActiveDPP[i][j] = wocaws->TotawNumbewOfActiveDPP[i][j] + 1;
				}
			}
			if (wocaws->TotawNumbewOfActiveDPP[i][j] > mode_wib->vba.MaxNumDPP) {
				wocaws->WequiwedDISPCWK[i][j] = 0.0;
				wocaws->DISPCWK_DPPCWK_Suppowt[i][j] = twue;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					wocaws->ODMCombineEnabwePewState[i][k] = dm_odm_combine_mode_disabwed;
					if (wocaws->SwathWidthYSingweDPP[k] <= wocaws->MaximumSwathWidth[k]) {
						wocaws->NoOfDPP[i][j][k] = 1;
						wocaws->WequiwedDPPCWK[i][j][k] = wocaws->MinDPPCWKUsingSingweDPP[k]
							* (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0);
					} ewse {
						wocaws->NoOfDPP[i][j][k] = 2;
						wocaws->WequiwedDPPCWK[i][j][k] = wocaws->MinDPPCWKUsingSingweDPP[k]
										* (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) / 2.0;
					}
					if (i != mode_wib->vba.soc.num_states) {
						mode_wib->vba.PwaneWequiwedDISPCWK =
								mode_wib->vba.PixewCwock[k]
										* (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0)
										* (1.0 + mode_wib->vba.DISPCWKWampingMawgin / 100.0);
					} ewse {
						mode_wib->vba.PwaneWequiwedDISPCWK = mode_wib->vba.PixewCwock[k]
							* (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0);
					}
					wocaws->WequiwedDISPCWK[i][j] = dmw_max(
							wocaws->WequiwedDISPCWK[i][j],
							mode_wib->vba.PwaneWequiwedDISPCWK);
					if (wocaws->MinDPPCWKUsingSingweDPP[k] / wocaws->NoOfDPP[i][j][k] * (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0)
							> mode_wib->vba.MaxDppcwkWoundedDownToDFSGwanuwawity
							|| mode_wib->vba.PwaneWequiwedDISPCWK > mode_wib->vba.MaxDispcwkWoundedDownToDFSGwanuwawity)
						wocaws->DISPCWK_DPPCWK_Suppowt[i][j] = fawse;
				}
				wocaws->TotawNumbewOfActiveDPP[i][j] = 0.0;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++)
					wocaws->TotawNumbewOfActiveDPP[i][j] = wocaws->TotawNumbewOfActiveDPP[i][j] + wocaws->NoOfDPP[i][j][k];
			}
			wocaws->WequiwedDISPCWK[i][j] = dmw_max(
					wocaws->WequiwedDISPCWK[i][j],
					mode_wib->vba.WwitebackWequiwedDISPCWK);
			if (mode_wib->vba.MaxDispcwkWoundedDownToDFSGwanuwawity
					< mode_wib->vba.WwitebackWequiwedDISPCWK) {
				wocaws->DISPCWK_DPPCWK_Suppowt[i][j] = fawse;
			}
		}
	}
	/*Viewpowt Size Check*/

	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		wocaws->ViewpowtSizeSuppowt[i][0] = twue;
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			if (wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_2to1) {
				if (dmw_min(wocaws->SwathWidthYSingweDPP[k], dmw_wound(mode_wib->vba.HActive[k] / 2.0 * mode_wib->vba.HWatio[k]))
						> wocaws->MaximumSwathWidth[k]) {
					wocaws->ViewpowtSizeSuppowt[i][0] = fawse;
				}
			} ewse {
				if (wocaws->SwathWidthYSingweDPP[k] / 2.0 > wocaws->MaximumSwathWidth[k]) {
					wocaws->ViewpowtSizeSuppowt[i][0] = fawse;
				}
			}
		}
	}
	/*Totaw Avaiwabwe Pipes Suppowt Check*/

	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			if (wocaws->TotawNumbewOfActiveDPP[i][j] <= mode_wib->vba.MaxNumDPP)
				wocaws->TotawAvaiwabwePipesSuppowt[i][j] = twue;
			ewse
				wocaws->TotawAvaiwabwePipesSuppowt[i][j] = fawse;
		}
	}
	/*Totaw Avaiwabwe OTG Suppowt Check*/

	mode_wib->vba.TotawNumbewOfActiveOTG = 0.0;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.BwendingAndTiming[k] == k) {
			mode_wib->vba.TotawNumbewOfActiveOTG = mode_wib->vba.TotawNumbewOfActiveOTG
					+ 1.0;
		}
	}
	if (mode_wib->vba.TotawNumbewOfActiveOTG <= mode_wib->vba.MaxNumOTG) {
		mode_wib->vba.NumbewOfOTGSuppowt = twue;
	} ewse {
		mode_wib->vba.NumbewOfOTGSuppowt = fawse;
	}
	/*Dispway IO and DSC Suppowt Check*/

	mode_wib->vba.NonsuppowtedDSCInputBPC = fawse;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (!(mode_wib->vba.DSCInputBitPewComponent[k] == 12.0
				|| mode_wib->vba.DSCInputBitPewComponent[k] == 10.0
				|| mode_wib->vba.DSCInputBitPewComponent[k] == 8.0)) {
			mode_wib->vba.NonsuppowtedDSCInputBPC = twue;
		}
	}
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			wocaws->WequiwesDSC[i][k] = fawse;
			wocaws->WequiwesFEC[i][k] = 0;
			if (mode_wib->vba.BwendingAndTiming[k] == k) {
				if (mode_wib->vba.Output[k] == dm_hdmi) {
					wocaws->WequiwesDSC[i][k] = fawse;
					wocaws->WequiwesFEC[i][k] = 0;
					wocaws->OutputBppPewState[i][k] = TwuncToVawidBPP(
							dmw_min(600.0, mode_wib->vba.PHYCWKPewState[i]) / mode_wib->vba.PixewCwockBackEnd[k] * 24,
							mode_wib->vba.FowcedOutputWinkBPP[k],
							fawse,
							mode_wib->vba.Output[k],
							mode_wib->vba.OutputFowmat[k],
							mode_wib->vba.DSCInputBitPewComponent[k]);
				} ewse if (mode_wib->vba.Output[k] == dm_dp
						|| mode_wib->vba.Output[k] == dm_edp) {
					if (mode_wib->vba.Output[k] == dm_edp) {
						mode_wib->vba.EffectiveFECOvewhead = 0.0;
					} ewse {
						mode_wib->vba.EffectiveFECOvewhead =
								mode_wib->vba.FECOvewhead;
					}
					if (mode_wib->vba.PHYCWKPewState[i] >= 270.0) {
						mode_wib->vba.Outbpp = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * 270.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
								mode_wib->vba.FowcedOutputWinkBPP[k],
								fawse,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						mode_wib->vba.OutbppDSC = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * (1.0 - mode_wib->vba.EffectiveFECOvewhead / 100.0) * 270.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
								mode_wib->vba.FowcedOutputWinkBPP[k],
								twue,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						if (mode_wib->vba.DSCEnabwed[k] == twue) {
							wocaws->WequiwesDSC[i][k] = twue;
							if (mode_wib->vba.Output[k] == dm_dp) {
								wocaws->WequiwesFEC[i][k] = twue;
							} ewse {
								wocaws->WequiwesFEC[i][k] = fawse;
							}
							mode_wib->vba.Outbpp = mode_wib->vba.OutbppDSC;
						} ewse {
							wocaws->WequiwesDSC[i][k] = fawse;
							wocaws->WequiwesFEC[i][k] = fawse;
						}
						wocaws->OutputBppPewState[i][k] = mode_wib->vba.Outbpp;
					}
					if (mode_wib->vba.Outbpp == BPP_INVAWID && mode_wib->vba.PHYCWKPewState[i] >= 540.0) {
						mode_wib->vba.Outbpp = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * 540.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
								mode_wib->vba.FowcedOutputWinkBPP[k],
									fawse,
									mode_wib->vba.Output[k],
									mode_wib->vba.OutputFowmat[k],
									mode_wib->vba.DSCInputBitPewComponent[k]);
						mode_wib->vba.OutbppDSC = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * (1.0 - mode_wib->vba.EffectiveFECOvewhead / 100.0) * 540.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
								mode_wib->vba.FowcedOutputWinkBPP[k],
								twue,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						if (mode_wib->vba.DSCEnabwed[k] == twue) {
							wocaws->WequiwesDSC[i][k] = twue;
							if (mode_wib->vba.Output[k] == dm_dp) {
								wocaws->WequiwesFEC[i][k] = twue;
							} ewse {
								wocaws->WequiwesFEC[i][k] = fawse;
							}
							mode_wib->vba.Outbpp = mode_wib->vba.OutbppDSC;
						} ewse {
							wocaws->WequiwesDSC[i][k] = fawse;
							wocaws->WequiwesFEC[i][k] = fawse;
						}
						wocaws->OutputBppPewState[i][k] = mode_wib->vba.Outbpp;
					}
					if (mode_wib->vba.Outbpp == BPP_INVAWID
							&& mode_wib->vba.PHYCWKPewState[i]
									>= 810.0) {
						mode_wib->vba.Outbpp = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * 810.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
								mode_wib->vba.FowcedOutputWinkBPP[k],
								fawse,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						mode_wib->vba.OutbppDSC = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * (1.0 - mode_wib->vba.EffectiveFECOvewhead / 100.0) * 810.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
								mode_wib->vba.FowcedOutputWinkBPP[k],
								twue,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						if (mode_wib->vba.DSCEnabwed[k] == twue || mode_wib->vba.Outbpp == BPP_INVAWID) {
							wocaws->WequiwesDSC[i][k] = twue;
							if (mode_wib->vba.Output[k] == dm_dp) {
								wocaws->WequiwesFEC[i][k] = twue;
							} ewse {
								wocaws->WequiwesFEC[i][k] = fawse;
							}
							mode_wib->vba.Outbpp = mode_wib->vba.OutbppDSC;
						} ewse {
							wocaws->WequiwesDSC[i][k] = fawse;
							wocaws->WequiwesFEC[i][k] = fawse;
						}
						wocaws->OutputBppPewState[i][k] =
								mode_wib->vba.Outbpp;
					}
				}
			} ewse {
				wocaws->OutputBppPewState[i][k] = BPP_BWENDED_PIPE;
			}
		}
	}
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		wocaws->DIOSuppowt[i] = twue;
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			if (!mode_wib->vba.skip_dio_check[k]
					&& (wocaws->OutputBppPewState[i][k] == BPP_INVAWID
						|| (mode_wib->vba.OutputFowmat[k] == dm_420
							&& mode_wib->vba.Intewwace[k] == twue
							&& mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP == twue))) {
				wocaws->DIOSuppowt[i] = fawse;
			}
		}
	}
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			wocaws->DSCCWKWequiwedMoweThanSuppowted[i] = fawse;
			if (mode_wib->vba.BwendingAndTiming[k] == k) {
				if ((mode_wib->vba.Output[k] == dm_dp
						|| mode_wib->vba.Output[k] == dm_edp)) {
					if (mode_wib->vba.OutputFowmat[k] == dm_420
							|| mode_wib->vba.OutputFowmat[k]
									== dm_n422) {
						mode_wib->vba.DSCFowmatFactow = 2;
					} ewse {
						mode_wib->vba.DSCFowmatFactow = 1;
					}
					if (wocaws->WequiwesDSC[i][k] == twue) {
						if (wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_2to1) {
							if (mode_wib->vba.PixewCwockBackEnd[k] / 6.0 / mode_wib->vba.DSCFowmatFactow
									> (1.0 - mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) * mode_wib->vba.MaxDSCCWK[i]) {
								wocaws->DSCCWKWequiwedMoweThanSuppowted[i] =
										twue;
							}
						} ewse {
							if (mode_wib->vba.PixewCwockBackEnd[k] / 3.0 / mode_wib->vba.DSCFowmatFactow
									> (1.0 - mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0) * mode_wib->vba.MaxDSCCWK[i]) {
								wocaws->DSCCWKWequiwedMoweThanSuppowted[i] =
										twue;
							}
						}
					}
				}
			}
		}
	}
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		wocaws->NotEnoughDSCUnits[i] = fawse;
		mode_wib->vba.TotawDSCUnitsWequiwed = 0.0;
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			if (wocaws->WequiwesDSC[i][k] == twue) {
				if (wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_2to1) {
					mode_wib->vba.TotawDSCUnitsWequiwed =
							mode_wib->vba.TotawDSCUnitsWequiwed + 2.0;
				} ewse {
					mode_wib->vba.TotawDSCUnitsWequiwed =
							mode_wib->vba.TotawDSCUnitsWequiwed + 1.0;
				}
			}
		}
		if (mode_wib->vba.TotawDSCUnitsWequiwed > mode_wib->vba.NumbewOfDSC) {
			wocaws->NotEnoughDSCUnits[i] = twue;
		}
	}
	/*DSC Deway pew state*/

	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			if (mode_wib->vba.BwendingAndTiming[k] != k) {
				mode_wib->vba.swices = 0;
			} ewse if (wocaws->WequiwesDSC[i][k] == 0
					|| wocaws->WequiwesDSC[i][k] == fawse) {
				mode_wib->vba.swices = 0;
			} ewse if (mode_wib->vba.PixewCwockBackEnd[k] > 3200.0) {
				mode_wib->vba.swices = dmw_ceiw(
						mode_wib->vba.PixewCwockBackEnd[k] / 400.0,
						4.0);
			} ewse if (mode_wib->vba.PixewCwockBackEnd[k] > 1360.0) {
				mode_wib->vba.swices = 8.0;
			} ewse if (mode_wib->vba.PixewCwockBackEnd[k] > 680.0) {
				mode_wib->vba.swices = 4.0;
			} ewse if (mode_wib->vba.PixewCwockBackEnd[k] > 340.0) {
				mode_wib->vba.swices = 2.0;
			} ewse {
				mode_wib->vba.swices = 1.0;
			}
			if (wocaws->OutputBppPewState[i][k] == BPP_BWENDED_PIPE
					|| wocaws->OutputBppPewState[i][k] == BPP_INVAWID) {
				mode_wib->vba.bpp = 0.0;
			} ewse {
				mode_wib->vba.bpp = wocaws->OutputBppPewState[i][k];
			}
			if (wocaws->WequiwesDSC[i][k] == twue && mode_wib->vba.bpp != 0.0) {
				if (wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_disabwed) {
					wocaws->DSCDewayPewState[i][k] =
							dscceComputeDeway(
									mode_wib->vba.DSCInputBitPewComponent[k],
									mode_wib->vba.bpp,
									dmw_ceiw(
											mode_wib->vba.HActive[k]
													/ mode_wib->vba.swices,
											1.0),
									mode_wib->vba.swices,
									mode_wib->vba.OutputFowmat[k])
									+ dscComputeDeway(
											mode_wib->vba.OutputFowmat[k]);
				} ewse {
					wocaws->DSCDewayPewState[i][k] =
							2.0 * (dscceComputeDeway(
											mode_wib->vba.DSCInputBitPewComponent[k],
											mode_wib->vba.bpp,
											dmw_ceiw(mode_wib->vba.HActive[k] / mode_wib->vba.swices, 1.0),
											mode_wib->vba.swices / 2,
											mode_wib->vba.OutputFowmat[k])
									+ dscComputeDeway(mode_wib->vba.OutputFowmat[k]));
				}
				wocaws->DSCDewayPewState[i][k] =
						wocaws->DSCDewayPewState[i][k] * mode_wib->vba.PixewCwock[k] / mode_wib->vba.PixewCwockBackEnd[k];
			} ewse {
				wocaws->DSCDewayPewState[i][k] = 0.0;
			}
		}
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			fow (m = 0; m <= mode_wib->vba.NumbewOfActivePwanes - 1; m++) {
				fow (j = 0; j <= mode_wib->vba.NumbewOfActivePwanes - 1; j++) {
					if (mode_wib->vba.BwendingAndTiming[k] == m && wocaws->WequiwesDSC[i][m] == twue)
						wocaws->DSCDewayPewState[i][k] = wocaws->DSCDewayPewState[i][m];
				}
			}
		}
	}

	//Pwefetch Check
	fow (i = 0; i <= mode_wib->vba.soc.num_states; ++i) {
		fow (j = 0; j <= 1; ++j) {
			wocaws->TotawNumbewOfDCCActiveDPP[i][j] = 0;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				if (mode_wib->vba.DCCEnabwe[k] == twue)
					wocaws->TotawNumbewOfDCCActiveDPP[i][j] = wocaws->TotawNumbewOfDCCActiveDPP[i][j] + wocaws->NoOfDPP[i][j][k];
			}
		}
	}

	mode_wib->vba.UwgentWatency = dmw_max3(
			mode_wib->vba.UwgentWatencyPixewDataOnwy,
			mode_wib->vba.UwgentWatencyPixewMixedWithVMData,
			mode_wib->vba.UwgentWatencyVMDataOnwy);
	mode_wib->vba.PwefetchEWWOW = CawcuwateMinAndMaxPwefetchMode(
			mode_wib->vba.AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank,
			&mode_wib->vba.MinPwefetchMode,
			&mode_wib->vba.MaxPwefetchMode);

	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				wocaws->WequiwedDPPCWKThisState[k] = wocaws->WequiwedDPPCWK[i][j][k];
				wocaws->NoOfDPPThisState[k]        = wocaws->NoOfDPP[i][j][k];
				if (wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_2to1) {
					wocaws->SwathWidthYThisState[k] =
						dmw_min(wocaws->SwathWidthYSingweDPP[k], dmw_wound(mode_wib->vba.HActive[k] / 2.0 * mode_wib->vba.HWatio[k]));
				} ewse {
					wocaws->SwathWidthYThisState[k] = wocaws->SwathWidthYSingweDPP[k] / wocaws->NoOfDPP[i][j][k];
				}
				mode_wib->vba.SwathWidthGwanuwawityY = 256.0
					/ dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1.0)
					/ wocaws->MaxSwathHeightY[k];
				mode_wib->vba.WoundedUpMaxSwathSizeBytesY =
					(dmw_ceiw(wocaws->SwathWidthYThisState[k] - 1.0, mode_wib->vba.SwathWidthGwanuwawityY)
					+ mode_wib->vba.SwathWidthGwanuwawityY) * wocaws->BytePewPixewInDETY[k] * wocaws->MaxSwathHeightY[k];
				if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_10) {
					mode_wib->vba.WoundedUpMaxSwathSizeBytesY = dmw_ceiw(
							mode_wib->vba.WoundedUpMaxSwathSizeBytesY,
							256.0) + 256;
				}
				if (wocaws->MaxSwathHeightC[k] > 0.0) {
					mode_wib->vba.SwathWidthGwanuwawityC = 256.0 / dmw_ceiw(wocaws->BytePewPixewInDETC[k], 2.0) / wocaws->MaxSwathHeightC[k];
					mode_wib->vba.WoundedUpMaxSwathSizeBytesC = (dmw_ceiw(wocaws->SwathWidthYThisState[k] / 2.0 - 1.0, mode_wib->vba.SwathWidthGwanuwawityC)
							+ mode_wib->vba.SwathWidthGwanuwawityC) * wocaws->BytePewPixewInDETC[k] * wocaws->MaxSwathHeightC[k];
					if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_10) {
						mode_wib->vba.WoundedUpMaxSwathSizeBytesC = dmw_ceiw(mode_wib->vba.WoundedUpMaxSwathSizeBytesC, 256.0) + 256;
					}
				} ewse {
					mode_wib->vba.WoundedUpMaxSwathSizeBytesC = 0.0;
				}
				if (mode_wib->vba.WoundedUpMaxSwathSizeBytesY + mode_wib->vba.WoundedUpMaxSwathSizeBytesC
						<= mode_wib->vba.DETBuffewSizeInKByte[0] * 1024.0 / 2.0) {
					wocaws->SwathHeightYThisState[k] = wocaws->MaxSwathHeightY[k];
					wocaws->SwathHeightCThisState[k] = wocaws->MaxSwathHeightC[k];
				} ewse {
					wocaws->SwathHeightYThisState[k] =
							wocaws->MinSwathHeightY[k];
					wocaws->SwathHeightCThisState[k] =
							wocaws->MinSwathHeightC[k];
				}
			}

			CawcuwateDCFCWKDeepSweep(
					mode_wib,
					mode_wib->vba.NumbewOfActivePwanes,
					wocaws->BytePewPixewInDETY,
					wocaws->BytePewPixewInDETC,
					mode_wib->vba.VWatio,
					wocaws->SwathWidthYThisState,
					wocaws->NoOfDPPThisState,
					mode_wib->vba.HWatio,
					mode_wib->vba.PixewCwock,
					wocaws->PSCW_FACTOW,
					wocaws->PSCW_FACTOW_CHWOMA,
					wocaws->WequiwedDPPCWKThisState,
					&mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0]);

			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_8)) {
					mode_wib->vba.PDEAndMetaPTEBytesPewFwameC = CawcuwateVMAndWowBytes(
							mode_wib,
							mode_wib->vba.DCCEnabwe[k],
							wocaws->Wead256BwockHeightC[k],
							wocaws->Wead256BwockWidthC[k],
							mode_wib->vba.SouwcePixewFowmat[k],
							mode_wib->vba.SuwfaceTiwing[k],
							dmw_ceiw(wocaws->BytePewPixewInDETC[k], 2.0),
							mode_wib->vba.SouwceScan[k],
							mode_wib->vba.ViewpowtWidth[k] / 2.0,
							mode_wib->vba.ViewpowtHeight[k] / 2.0,
							wocaws->SwathWidthYThisState[k] / 2.0,
							mode_wib->vba.GPUVMEnabwe,
							mode_wib->vba.HostVMEnabwe,
							mode_wib->vba.HostVMMaxPageTabweWevews,
							mode_wib->vba.HostVMCachedPageTabweWevews,
							mode_wib->vba.VMMPageSize,
							mode_wib->vba.PTEBuffewSizeInWequestsChwoma,
							mode_wib->vba.PitchC[k],
							0.0,
							&wocaws->MacwoTiweWidthC[k],
							&mode_wib->vba.MetaWowBytesC,
							&mode_wib->vba.DPTEBytesPewWowC,
							&wocaws->PTEBuffewSizeNotExceededC[i][j][k],
							wocaws->dpte_wow_width_chwoma_ub,
							&wocaws->dpte_wow_height_chwoma[k],
							&wocaws->meta_weq_width_chwoma[k],
							&wocaws->meta_weq_height_chwoma[k],
							&wocaws->meta_wow_width_chwoma[k],
							&wocaws->meta_wow_height_chwoma[k],
							&wocaws->vm_gwoup_bytes_chwoma,
							&wocaws->dpte_gwoup_bytes_chwoma,
							wocaws->PixewPTEWeqWidthC,
							wocaws->PixewPTEWeqHeightC,
							wocaws->PTEWequestSizeC,
							wocaws->dpde0_bytes_pew_fwame_ub_c,
							wocaws->meta_pte_bytes_pew_fwame_ub_c);
					wocaws->PwefetchWinesC[0][0][k] = CawcuwatePwefetchSouwceWines(
							mode_wib,
							mode_wib->vba.VWatio[k]/2,
							mode_wib->vba.VTAPsChwoma[k],
							mode_wib->vba.Intewwace[k],
							mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
							wocaws->SwathHeightCThisState[k],
							mode_wib->vba.ViewpowtYStawtC[k],
							&wocaws->PwefiwwC[k],
							&wocaws->MaxNumSwC[k]);
					wocaws->PTEBuffewSizeInWequestsFowWuma = mode_wib->vba.PTEBuffewSizeInWequestsWuma;
				} ewse {
					mode_wib->vba.PDEAndMetaPTEBytesPewFwameC = 0.0;
					mode_wib->vba.MetaWowBytesC = 0.0;
					mode_wib->vba.DPTEBytesPewWowC = 0.0;
					wocaws->PwefetchWinesC[0][0][k] = 0.0;
					wocaws->PTEBuffewSizeNotExceededC[i][j][k] = twue;
					wocaws->PTEBuffewSizeInWequestsFowWuma = mode_wib->vba.PTEBuffewSizeInWequestsWuma + mode_wib->vba.PTEBuffewSizeInWequestsChwoma;
				}
				mode_wib->vba.PDEAndMetaPTEBytesPewFwameY = CawcuwateVMAndWowBytes(
						mode_wib,
						mode_wib->vba.DCCEnabwe[k],
						wocaws->Wead256BwockHeightY[k],
						wocaws->Wead256BwockWidthY[k],
						mode_wib->vba.SouwcePixewFowmat[k],
						mode_wib->vba.SuwfaceTiwing[k],
						dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1.0),
						mode_wib->vba.SouwceScan[k],
						mode_wib->vba.ViewpowtWidth[k],
						mode_wib->vba.ViewpowtHeight[k],
						wocaws->SwathWidthYThisState[k],
						mode_wib->vba.GPUVMEnabwe,
						mode_wib->vba.HostVMEnabwe,
						mode_wib->vba.HostVMMaxPageTabweWevews,
						mode_wib->vba.HostVMCachedPageTabweWevews,
						mode_wib->vba.VMMPageSize,
						wocaws->PTEBuffewSizeInWequestsFowWuma,
						mode_wib->vba.PitchY[k],
						mode_wib->vba.DCCMetaPitchY[k],
						&wocaws->MacwoTiweWidthY[k],
						&mode_wib->vba.MetaWowBytesY,
						&mode_wib->vba.DPTEBytesPewWowY,
						&wocaws->PTEBuffewSizeNotExceededY[i][j][k],
						wocaws->dpte_wow_width_wuma_ub,
						&wocaws->dpte_wow_height[k],
						&wocaws->meta_weq_width[k],
						&wocaws->meta_weq_height[k],
						&wocaws->meta_wow_width[k],
						&wocaws->meta_wow_height[k],
						&wocaws->vm_gwoup_bytes[k],
						&wocaws->dpte_gwoup_bytes[k],
						wocaws->PixewPTEWeqWidthY,
						wocaws->PixewPTEWeqHeightY,
						wocaws->PTEWequestSizeY,
						wocaws->dpde0_bytes_pew_fwame_ub_w,
						wocaws->meta_pte_bytes_pew_fwame_ub_w);
				wocaws->PwefetchWinesY[0][0][k] = CawcuwatePwefetchSouwceWines(
						mode_wib,
						mode_wib->vba.VWatio[k],
						mode_wib->vba.vtaps[k],
						mode_wib->vba.Intewwace[k],
						mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
						wocaws->SwathHeightYThisState[k],
						mode_wib->vba.ViewpowtYStawtY[k],
						&wocaws->PwefiwwY[k],
						&wocaws->MaxNumSwY[k]);
				wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k] =
						mode_wib->vba.PDEAndMetaPTEBytesPewFwameY + mode_wib->vba.PDEAndMetaPTEBytesPewFwameC;
				wocaws->MetaWowBytes[0][0][k] = mode_wib->vba.MetaWowBytesY + mode_wib->vba.MetaWowBytesC;
				wocaws->DPTEBytesPewWow[0][0][k] = mode_wib->vba.DPTEBytesPewWowY + mode_wib->vba.DPTEBytesPewWowC;

				CawcuwateActiveWowBandwidth(
						mode_wib->vba.GPUVMEnabwe,
						mode_wib->vba.SouwcePixewFowmat[k],
						mode_wib->vba.VWatio[k],
						mode_wib->vba.DCCEnabwe[k],
						mode_wib->vba.HTotaw[k] /
						mode_wib->vba.PixewCwock[k],
						mode_wib->vba.MetaWowBytesY,
						mode_wib->vba.MetaWowBytesC,
						wocaws->meta_wow_height[k],
						wocaws->meta_wow_height_chwoma[k],
						mode_wib->vba.DPTEBytesPewWowY,
						mode_wib->vba.DPTEBytesPewWowC,
						wocaws->dpte_wow_height[k],
						wocaws->dpte_wow_height_chwoma[k],
						&wocaws->meta_wow_bw[k],
						&wocaws->dpte_wow_bw[k]);
			}
			mode_wib->vba.ExtwaWatency = CawcuwateExtwaWatency(
					wocaws->UwgentWoundTwipAndOutOfOwdewWatencyPewState[i],
					wocaws->TotawNumbewOfActiveDPP[i][j],
					mode_wib->vba.PixewChunkSizeInKByte,
					wocaws->TotawNumbewOfDCCActiveDPP[i][j],
					mode_wib->vba.MetaChunkSize,
					wocaws->WetuwnBWPewState[i][0],
					mode_wib->vba.GPUVMEnabwe,
					mode_wib->vba.HostVMEnabwe,
					mode_wib->vba.NumbewOfActivePwanes,
					wocaws->NoOfDPPThisState,
					wocaws->dpte_gwoup_bytes,
					mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
					mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
					mode_wib->vba.HostVMMaxPageTabweWevews,
					mode_wib->vba.HostVMCachedPageTabweWevews);

			mode_wib->vba.TimeCawc = 24.0 / mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0];
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				if (mode_wib->vba.BwendingAndTiming[k] == k) {
					if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
						wocaws->WwitebackDeway[i][k] = mode_wib->vba.WwitebackWatency
								+ CawcuwateWwiteBackDeway(
										mode_wib->vba.WwitebackPixewFowmat[k],
										mode_wib->vba.WwitebackHWatio[k],
										mode_wib->vba.WwitebackVWatio[k],
										mode_wib->vba.WwitebackWumaHTaps[k],
										mode_wib->vba.WwitebackWumaVTaps[k],
										mode_wib->vba.WwitebackChwomaHTaps[k],
										mode_wib->vba.WwitebackChwomaVTaps[k],
										mode_wib->vba.WwitebackDestinationWidth[k]) / wocaws->WequiwedDISPCWK[i][j];
					} ewse {
						wocaws->WwitebackDeway[i][k] = 0.0;
					}
					fow (m = 0; m <= mode_wib->vba.NumbewOfActivePwanes - 1; m++) {
						if (mode_wib->vba.BwendingAndTiming[m] == k
								&& mode_wib->vba.WwitebackEnabwe[m]
										== twue) {
							wocaws->WwitebackDeway[i][k] = dmw_max(wocaws->WwitebackDeway[i][k],
											mode_wib->vba.WwitebackWatency + CawcuwateWwiteBackDeway(
													mode_wib->vba.WwitebackPixewFowmat[m],
													mode_wib->vba.WwitebackHWatio[m],
													mode_wib->vba.WwitebackVWatio[m],
													mode_wib->vba.WwitebackWumaHTaps[m],
													mode_wib->vba.WwitebackWumaVTaps[m],
													mode_wib->vba.WwitebackChwomaHTaps[m],
													mode_wib->vba.WwitebackChwomaVTaps[m],
													mode_wib->vba.WwitebackDestinationWidth[m]) / wocaws->WequiwedDISPCWK[i][j]);
						}
					}
				}
			}
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				fow (m = 0; m <= mode_wib->vba.NumbewOfActivePwanes - 1; m++) {
					if (mode_wib->vba.BwendingAndTiming[k] == m) {
						wocaws->WwitebackDeway[i][k] = wocaws->WwitebackDeway[i][m];
					}
				}
			}
			mode_wib->vba.MaxMaxVStawtup[0][0] = 0;
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				wocaws->MaximumVStawtup[0][0][k] = mode_wib->vba.VTotaw[k] - mode_wib->vba.VActive[k]
					- dmw_max(1.0, dmw_ceiw(wocaws->WwitebackDeway[i][k] / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]), 1.0));
				mode_wib->vba.MaxMaxVStawtup[0][0] = dmw_max(mode_wib->vba.MaxMaxVStawtup[0][0], wocaws->MaximumVStawtup[0][0][k]);
			}

			mode_wib->vba.NextPwefetchMode = mode_wib->vba.MinPwefetchMode;
			mode_wib->vba.NextMaxVStawtup = mode_wib->vba.MaxMaxVStawtup[0][0];
			do {
				mode_wib->vba.PwefetchMode[i][j] = mode_wib->vba.NextPwefetchMode;
				mode_wib->vba.MaxVStawtup = mode_wib->vba.NextMaxVStawtup;

				mode_wib->vba.TWait = CawcuwateTWait(
						mode_wib->vba.PwefetchMode[i][j],
						mode_wib->vba.DWAMCwockChangeWatency,
						mode_wib->vba.UwgentWatency,
						mode_wib->vba.SWEntewPwusExitTime);
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++)
					CawcuwatePwefetchScheduwePewPwane(mode_wib, i, j, k);

				mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch = 0.0;
				mode_wib->vba.MaximumWeadBandwidthWithPwefetch = 0.0;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					unsigned int m;

					wocaws->cuwsow_bw[k] = 0;
					wocaws->cuwsow_bw_pwe[k] = 0;
					fow (m = 0; m < mode_wib->vba.NumbewOfCuwsows[k]; m++) {
						wocaws->cuwsow_bw[k] = mode_wib->vba.CuwsowWidth[k][m] * mode_wib->vba.CuwsowBPP[k][m]
							/ 8.0 / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]) * mode_wib->vba.VWatio[k];
						wocaws->cuwsow_bw_pwe[k] = mode_wib->vba.CuwsowWidth[k][m] * mode_wib->vba.CuwsowBPP[k][m]
							/ 8.0 / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]) * wocaws->VWatioPweY[i][j][k];
					}

					CawcuwateUwgentBuwstFactow(
							mode_wib->vba.DETBuffewSizeInKByte[0],
							wocaws->SwathHeightYThisState[k],
							wocaws->SwathHeightCThisState[k],
							wocaws->SwathWidthYThisState[k],
							mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
							mode_wib->vba.UwgentWatency,
							mode_wib->vba.CuwsowBuffewSize,
							mode_wib->vba.CuwsowWidth[k][0] + mode_wib->vba.CuwsowWidth[k][1],
							dmw_max(mode_wib->vba.CuwsowBPP[k][0], mode_wib->vba.CuwsowBPP[k][1]),
							mode_wib->vba.VWatio[k],
							wocaws->VWatioPweY[i][j][k],
							wocaws->VWatioPweC[i][j][k],
							wocaws->BytePewPixewInDETY[k],
							wocaws->BytePewPixewInDETC[k],
							&wocaws->UwgentBuwstFactowCuwsow[k],
							&wocaws->UwgentBuwstFactowCuwsowPwe[k],
							&wocaws->UwgentBuwstFactowWuma[k],
							&wocaws->UwgentBuwstFactowWumaPwe[k],
							&wocaws->UwgentBuwstFactowChwoma[k],
							&wocaws->UwgentBuwstFactowChwomaPwe[k],
							&wocaws->NotEnoughUwgentWatencyHiding[0][0],
							&wocaws->NotEnoughUwgentWatencyHidingPwe);

					if (mode_wib->vba.UseUwgentBuwstBandwidth == fawse) {
						wocaws->UwgentBuwstFactowCuwsow[k] = 1;
						wocaws->UwgentBuwstFactowCuwsowPwe[k] = 1;
						wocaws->UwgentBuwstFactowWuma[k] = 1;
						wocaws->UwgentBuwstFactowWumaPwe[k] = 1;
						wocaws->UwgentBuwstFactowChwoma[k] = 1;
						wocaws->UwgentBuwstFactowChwomaPwe[k] = 1;
					}

					mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch = mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch
						+ wocaws->cuwsow_bw[k] * wocaws->UwgentBuwstFactowCuwsow[k] + wocaws->WeadBandwidthWuma[k]
						* wocaws->UwgentBuwstFactowWuma[k] + wocaws->WeadBandwidthChwoma[k]
						* wocaws->UwgentBuwstFactowChwoma[k] + wocaws->meta_wow_bw[k] + wocaws->dpte_wow_bw[k];
					mode_wib->vba.MaximumWeadBandwidthWithPwefetch = mode_wib->vba.MaximumWeadBandwidthWithPwefetch
						+ dmw_max3(wocaws->pwefetch_vmwow_bw[k],
						wocaws->WeadBandwidthWuma[k] * wocaws->UwgentBuwstFactowWuma[k] + wocaws->WeadBandwidthChwoma[k]
						* wocaws->UwgentBuwstFactowChwoma[k] + wocaws->cuwsow_bw[k] * wocaws->UwgentBuwstFactowCuwsow[k]
						+ wocaws->meta_wow_bw[k] + wocaws->dpte_wow_bw[k],
						wocaws->WequiwedPwefetchPixewDataBWWuma[i][j][k] * wocaws->UwgentBuwstFactowWumaPwe[k]
						+ wocaws->WequiwedPwefetchPixewDataBWChwoma[i][j][k] * wocaws->UwgentBuwstFactowChwomaPwe[k]
						+ wocaws->cuwsow_bw_pwe[k] * wocaws->UwgentBuwstFactowCuwsowPwe[k]);
				}
				wocaws->BandwidthWithoutPwefetchSuppowted[i][0] = twue;
				if (mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch > wocaws->WetuwnBWPewState[i][0]
						|| wocaws->NotEnoughUwgentWatencyHiding[0][0] == 1) {
					wocaws->BandwidthWithoutPwefetchSuppowted[i][0] = fawse;
				}

				wocaws->PwefetchSuppowted[i][j] = twue;
				if (mode_wib->vba.MaximumWeadBandwidthWithPwefetch > wocaws->WetuwnBWPewState[i][0]
						|| wocaws->NotEnoughUwgentWatencyHiding[0][0] == 1
						|| wocaws->NotEnoughUwgentWatencyHidingPwe == 1) {
					wocaws->PwefetchSuppowted[i][j] = fawse;
				}
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if (wocaws->WineTimesFowPwefetch[k] < 2.0
							|| wocaws->WinesFowMetaPTE[k] >= 32.0
							|| wocaws->WinesFowMetaAndDPTEWow[k] >= 16.0
							|| mode_wib->vba.IsEwwowWesuwt[i][j][k] == twue) {
						wocaws->PwefetchSuppowted[i][j] = fawse;
					}
				}
				wocaws->VWatioInPwefetchSuppowted[i][j] = twue;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if (wocaws->VWatioPweY[i][j][k] > 4.0
							|| wocaws->VWatioPweC[i][j][k] > 4.0
							|| mode_wib->vba.IsEwwowWesuwt[i][j][k] == twue) {
						wocaws->VWatioInPwefetchSuppowted[i][j] = fawse;
					}
				}
				mode_wib->vba.AnyWinesFowVMOwWowTooWawge = fawse;
				fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
					if (wocaws->WinesFowMetaAndDPTEWow[k] >= 16 || wocaws->WinesFowMetaPTE[k] >= 32) {
						mode_wib->vba.AnyWinesFowVMOwWowTooWawge = twue;
					}
				}

				if (mode_wib->vba.MaxVStawtup <= 13 || mode_wib->vba.AnyWinesFowVMOwWowTooWawge == fawse) {
					mode_wib->vba.NextMaxVStawtup = mode_wib->vba.MaxMaxVStawtup[0][0];
					mode_wib->vba.NextPwefetchMode = mode_wib->vba.NextPwefetchMode + 1;
				} ewse {
					mode_wib->vba.NextMaxVStawtup = mode_wib->vba.NextMaxVStawtup - 1;
				}
			} whiwe ((wocaws->PwefetchSuppowted[i][j] != twue || wocaws->VWatioInPwefetchSuppowted[i][j] != twue)
					&& (mode_wib->vba.NextMaxVStawtup != mode_wib->vba.MaxMaxVStawtup[0][0]
						|| mode_wib->vba.NextPwefetchMode <= mode_wib->vba.MaxPwefetchMode));

			if (wocaws->PwefetchSuppowted[i][j] == twue && wocaws->VWatioInPwefetchSuppowted[i][j] == twue) {
				mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip = wocaws->WetuwnBWPewState[i][0];
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip = mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip
						- dmw_max(wocaws->WeadBandwidthWuma[k] * wocaws->UwgentBuwstFactowWuma[k]
							+ wocaws->WeadBandwidthChwoma[k] * wocaws->UwgentBuwstFactowChwoma[k]
							+ wocaws->cuwsow_bw[k] * wocaws->UwgentBuwstFactowCuwsow[k],
							wocaws->WequiwedPwefetchPixewDataBWWuma[i][j][k] * wocaws->UwgentBuwstFactowWumaPwe[k]
							+ wocaws->WequiwedPwefetchPixewDataBWChwoma[i][j][k] * wocaws->UwgentBuwstFactowChwomaPwe[k]
							+ wocaws->cuwsow_bw_pwe[k] * wocaws->UwgentBuwstFactowCuwsowPwe[k]);
				}
				mode_wib->vba.TotImmediateFwipBytes = 0.0;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					mode_wib->vba.TotImmediateFwipBytes = mode_wib->vba.TotImmediateFwipBytes
						+ wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k] + wocaws->MetaWowBytes[0][0][k] + wocaws->DPTEBytesPewWow[0][0][k];
				}

				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					CawcuwateFwipScheduwe(
							mode_wib,
							mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
							mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
							mode_wib->vba.ExtwaWatency,
							mode_wib->vba.UwgentWatency,
							mode_wib->vba.GPUVMMaxPageTabweWevews,
							mode_wib->vba.HostVMEnabwe,
							mode_wib->vba.HostVMMaxPageTabweWevews,
							mode_wib->vba.HostVMCachedPageTabweWevews,
							mode_wib->vba.GPUVMEnabwe,
							wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k],
							wocaws->MetaWowBytes[0][0][k],
							wocaws->DPTEBytesPewWow[0][0][k],
							mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip,
							mode_wib->vba.TotImmediateFwipBytes,
							mode_wib->vba.SouwcePixewFowmat[k],
							mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
							mode_wib->vba.VWatio[k],
							wocaws->Tno_bw[k],
							mode_wib->vba.DCCEnabwe[k],
							wocaws->dpte_wow_height[k],
							wocaws->meta_wow_height[k],
							wocaws->dpte_wow_height_chwoma[k],
							wocaws->meta_wow_height_chwoma[k],
							&wocaws->DestinationWinesToWequestVMInImmediateFwip[k],
							&wocaws->DestinationWinesToWequestWowInImmediateFwip[k],
							&wocaws->finaw_fwip_bw[k],
							&wocaws->ImmediateFwipSuppowtedFowPipe[k]);
				}
				mode_wib->vba.totaw_dcn_wead_bw_with_fwip = 0.0;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					mode_wib->vba.totaw_dcn_wead_bw_with_fwip = mode_wib->vba.totaw_dcn_wead_bw_with_fwip + dmw_max3(
						wocaws->pwefetch_vmwow_bw[k],
						wocaws->finaw_fwip_bw[k] +  wocaws->WeadBandwidthWuma[k] * wocaws->UwgentBuwstFactowWuma[k]
						+ wocaws->WeadBandwidthChwoma[k] * wocaws->UwgentBuwstFactowChwoma[k]
						+ wocaws->cuwsow_bw[k] * wocaws->UwgentBuwstFactowCuwsow[k],
						wocaws->finaw_fwip_bw[k] + wocaws->WequiwedPwefetchPixewDataBWWuma[i][j][k]
						* wocaws->UwgentBuwstFactowWumaPwe[k] + wocaws->WequiwedPwefetchPixewDataBWChwoma[i][j][k]
						* wocaws->UwgentBuwstFactowChwomaPwe[k] + wocaws->cuwsow_bw_pwe[k]
						* wocaws->UwgentBuwstFactowCuwsowPwe[k]);
				}
				wocaws->ImmediateFwipSuppowtedFowState[i][j] = twue;
				if (mode_wib->vba.totaw_dcn_wead_bw_with_fwip
						> wocaws->WetuwnBWPewState[i][0]) {
					wocaws->ImmediateFwipSuppowtedFowState[i][j] = fawse;
				}
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if (wocaws->ImmediateFwipSuppowtedFowPipe[k] == fawse) {
						wocaws->ImmediateFwipSuppowtedFowState[i][j] = fawse;
					}
				}
			} ewse {
				wocaws->ImmediateFwipSuppowtedFowState[i][j] = fawse;
			}
			mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannew = dmw_max3(
					mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewDataOnwy,
					mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewMixedWithVMData,
					mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewVMDataOnwy);
			CawcuwateWatewmawksAndDWAMSpeedChangeSuppowt(
					mode_wib,
					mode_wib->vba.PwefetchMode[i][j],
					mode_wib->vba.NumbewOfActivePwanes,
					mode_wib->vba.MaxWineBuffewWines,
					mode_wib->vba.WineBuffewSize,
					mode_wib->vba.DPPOutputBuffewPixews,
					mode_wib->vba.DETBuffewSizeInKByte[0],
					mode_wib->vba.WwitebackIntewfaceWumaBuffewSize,
					mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize,
					mode_wib->vba.DCFCWKPewState[i],
					mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannew * mode_wib->vba.NumbewOfChannews,
					wocaws->WetuwnBWPewState[i][0],
					mode_wib->vba.GPUVMEnabwe,
					wocaws->dpte_gwoup_bytes,
					mode_wib->vba.MetaChunkSize,
					mode_wib->vba.UwgentWatency,
					mode_wib->vba.ExtwaWatency,
					mode_wib->vba.WwitebackWatency,
					mode_wib->vba.WwitebackChunkSize,
					mode_wib->vba.SOCCWKPewState[i],
					mode_wib->vba.DWAMCwockChangeWatency,
					mode_wib->vba.SWExitTime,
					mode_wib->vba.SWEntewPwusExitTime,
					mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
					wocaws->NoOfDPPThisState,
					mode_wib->vba.DCCEnabwe,
					wocaws->WequiwedDPPCWKThisState,
					wocaws->SwathWidthYSingweDPP,
					wocaws->SwathHeightYThisState,
					wocaws->WeadBandwidthWuma,
					wocaws->SwathHeightCThisState,
					wocaws->WeadBandwidthChwoma,
					mode_wib->vba.WBBitPewPixew,
					wocaws->SwathWidthYThisState,
					mode_wib->vba.HWatio,
					mode_wib->vba.vtaps,
					mode_wib->vba.VTAPsChwoma,
					mode_wib->vba.VWatio,
					mode_wib->vba.HTotaw,
					mode_wib->vba.PixewCwock,
					mode_wib->vba.BwendingAndTiming,
					wocaws->BytePewPixewInDETY,
					wocaws->BytePewPixewInDETC,
					mode_wib->vba.WwitebackEnabwe,
					mode_wib->vba.WwitebackPixewFowmat,
					mode_wib->vba.WwitebackDestinationWidth,
					mode_wib->vba.WwitebackDestinationHeight,
					mode_wib->vba.WwitebackSouwceHeight,
					&wocaws->DWAMCwockChangeSuppowt[i][j],
					&mode_wib->vba.UwgentWatewmawk,
					&mode_wib->vba.WwitebackUwgentWatewmawk,
					&mode_wib->vba.DWAMCwockChangeWatewmawk,
					&mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk,
					&mode_wib->vba.StuttewExitWatewmawk,
					&mode_wib->vba.StuttewEntewPwusExitWatewmawk,
					&mode_wib->vba.MinActiveDWAMCwockChangeWatencySuppowted);
			}
		}

		/*Vewticaw Active BW suppowt*/
		{
			doubwe MaxTotawVActiveWDBandwidth = 0.0;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				MaxTotawVActiveWDBandwidth = MaxTotawVActiveWDBandwidth + wocaws->WeadBandwidth[k];
		}
		fow (i = 0; i <= mode_wib->vba.soc.num_states; ++i) {
			wocaws->MaxTotawVewticawActiveAvaiwabweBandwidth[i][0] = dmw_min(
				wocaws->IdeawSDPPowtBandwidthPewState[i][0] *
				mode_wib->vba.MaxAvewagePewcentOfIdeawSDPPowtBWDispwayCanUseInNowmawSystemOpewation
				/ 100.0, mode_wib->vba.DWAMSpeedPewState[i] *
				mode_wib->vba.NumbewOfChannews *
				mode_wib->vba.DWAMChannewWidth *
				mode_wib->vba.MaxAvewagePewcentOfIdeawDWAMBWDispwayCanUseInNowmawSystemOpewation
				/ 100.0);

			if (MaxTotawVActiveWDBandwidth <= wocaws->MaxTotawVewticawActiveAvaiwabweBandwidth[i][0]) {
				wocaws->TotawVewticawActiveBandwidthSuppowt[i][0] = twue;
			} ewse {
				wocaws->TotawVewticawActiveBandwidthSuppowt[i][0] = fawse;
			}
		}
	}

	/*PTE Buffew Size Check*/

	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			wocaws->PTEBuffewSizeNotExceeded[i][j] = twue;
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				if (wocaws->PTEBuffewSizeNotExceededY[i][j][k] == fawse
						|| wocaws->PTEBuffewSizeNotExceededC[i][j][k] == fawse) {
					wocaws->PTEBuffewSizeNotExceeded[i][j] = fawse;
				}
			}
		}
	}
	/*Cuwsow Suppowt Check*/

	mode_wib->vba.CuwsowSuppowt = twue;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.CuwsowWidth[k][0] > 0.0) {
			fow (m = 0; m < mode_wib->vba.NumbewOfCuwsows[k]; m++) {
				if (mode_wib->vba.CuwsowBPP[k][m] == 64 && mode_wib->vba.Cuwsow64BppSuppowt == fawse) {
					mode_wib->vba.CuwsowSuppowt = fawse;
				}
			}
		}
	}
	/*Vawid Pitch Check*/

	mode_wib->vba.PitchSuppowt = twue;
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		wocaws->AwignedYPitch[k] = dmw_ceiw(
				dmw_max(mode_wib->vba.PitchY[k], mode_wib->vba.ViewpowtWidth[k]),
				wocaws->MacwoTiweWidthY[k]);
		if (wocaws->AwignedYPitch[k] > mode_wib->vba.PitchY[k]) {
			mode_wib->vba.PitchSuppowt = fawse;
		}
		if (mode_wib->vba.DCCEnabwe[k] == twue) {
			wocaws->AwignedDCCMetaPitch[k] = dmw_ceiw(
					dmw_max(
							mode_wib->vba.DCCMetaPitchY[k],
							mode_wib->vba.ViewpowtWidth[k]),
					64.0 * wocaws->Wead256BwockWidthY[k]);
		} ewse {
			wocaws->AwignedDCCMetaPitch[k] = mode_wib->vba.DCCMetaPitchY[k];
		}
		if (wocaws->AwignedDCCMetaPitch[k] > mode_wib->vba.DCCMetaPitchY[k]) {
			mode_wib->vba.PitchSuppowt = fawse;
		}
		if (mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_16
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_8) {
			wocaws->AwignedCPitch[k] = dmw_ceiw(
					dmw_max(
							mode_wib->vba.PitchC[k],
							mode_wib->vba.ViewpowtWidth[k] / 2.0),
					wocaws->MacwoTiweWidthC[k]);
		} ewse {
			wocaws->AwignedCPitch[k] = mode_wib->vba.PitchC[k];
		}
		if (wocaws->AwignedCPitch[k] > mode_wib->vba.PitchC[k]) {
			mode_wib->vba.PitchSuppowt = fawse;
		}
	}
	/*Mode Suppowt, Vowtage State and SOC Configuwation*/

	fow (i = mode_wib->vba.soc.num_states; i >= 0; i--) {
		fow (j = 0; j < 2; j++) {
			enum dm_vawidation_status status = DMW_VAWIDATION_OK;

			if (!mode_wib->vba.ScaweWatioAndTapsSuppowt) {
				status = DMW_FAIW_SCAWE_WATIO_TAP;
			} ewse if (!mode_wib->vba.SouwceFowmatPixewAndScanSuppowt) {
				status = DMW_FAIW_SOUWCE_PIXEW_FOWMAT;
			} ewse if (!wocaws->ViewpowtSizeSuppowt[i][0]) {
				status = DMW_FAIW_VIEWPOWT_SIZE;
			} ewse if (!wocaws->DIOSuppowt[i]) {
				status = DMW_FAIW_DIO_SUPPOWT;
			} ewse if (wocaws->NotEnoughDSCUnits[i]) {
				status = DMW_FAIW_NOT_ENOUGH_DSC;
			} ewse if (wocaws->DSCCWKWequiwedMoweThanSuppowted[i]) {
				status = DMW_FAIW_DSC_CWK_WEQUIWED;
			} ewse if (!wocaws->WOBSuppowt[i][0]) {
				status = DMW_FAIW_WEOWDEWING_BUFFEW;
			} ewse if (!wocaws->DISPCWK_DPPCWK_Suppowt[i][j]) {
				status = DMW_FAIW_DISPCWK_DPPCWK;
			} ewse if (!wocaws->TotawAvaiwabwePipesSuppowt[i][j]) {
				status = DMW_FAIW_TOTAW_AVAIWABWE_PIPES;
			} ewse if (!mode_wib->vba.NumbewOfOTGSuppowt) {
				status = DMW_FAIW_NUM_OTG;
			} ewse if (!mode_wib->vba.WwitebackModeSuppowt) {
				status = DMW_FAIW_WWITEBACK_MODE;
			} ewse if (!mode_wib->vba.WwitebackWatencySuppowt) {
				status = DMW_FAIW_WWITEBACK_WATENCY;
			} ewse if (!mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt) {
				status = DMW_FAIW_WWITEBACK_SCAWE_WATIO_TAP;
			} ewse if (!mode_wib->vba.CuwsowSuppowt) {
				status = DMW_FAIW_CUWSOW_SUPPOWT;
			} ewse if (!mode_wib->vba.PitchSuppowt) {
				status = DMW_FAIW_PITCH_SUPPOWT;
			} ewse if (!wocaws->TotawVewticawActiveBandwidthSuppowt[i][0]) {
				status = DMW_FAIW_TOTAW_V_ACTIVE_BW;
			} ewse if (!wocaws->PTEBuffewSizeNotExceeded[i][j]) {
				status = DMW_FAIW_PTE_BUFFEW_SIZE;
			} ewse if (mode_wib->vba.NonsuppowtedDSCInputBPC) {
				status = DMW_FAIW_DSC_INPUT_BPC;
			} ewse if ((mode_wib->vba.HostVMEnabwe
					&& !wocaws->ImmediateFwipSuppowtedFowState[i][j])) {
				status = DMW_FAIW_HOST_VM_IMMEDIATE_FWIP;
			} ewse if (!wocaws->PwefetchSuppowted[i][j]) {
				status = DMW_FAIW_PWEFETCH_SUPPOWT;
			} ewse if (!wocaws->VWatioInPwefetchSuppowted[i][j]) {
				status = DMW_FAIW_V_WATIO_PWEFETCH;
			}

			if (status == DMW_VAWIDATION_OK) {
				wocaws->ModeSuppowt[i][j] = twue;
			} ewse {
				wocaws->ModeSuppowt[i][j] = fawse;
			}
			wocaws->VawidationStatus[i] = status;
		}
	}
	{
		unsigned int MaximumMPCCombine = 0;
		mode_wib->vba.VowtageWevew = mode_wib->vba.soc.num_states + 1;
		fow (i = mode_wib->vba.VowtageOvewwideWevew; i <= mode_wib->vba.soc.num_states; i++) {
			if (wocaws->ModeSuppowt[i][0] == twue || wocaws->ModeSuppowt[i][1] == twue) {
				mode_wib->vba.VowtageWevew = i;
				if (wocaws->ModeSuppowt[i][1] == twue && (wocaws->ModeSuppowt[i][0] == fawse
						|| mode_wib->vba.WhenToDoMPCCombine == dm_mpc_awways_when_possibwe
						|| (mode_wib->vba.WhenToDoMPCCombine == dm_mpc_weduce_vowtage_and_cwocks
							&& ((wocaws->DWAMCwockChangeSuppowt[i][1] == dm_dwam_cwock_change_vactive
								&& wocaws->DWAMCwockChangeSuppowt[i][0] != dm_dwam_cwock_change_vactive)
							|| (wocaws->DWAMCwockChangeSuppowt[i][1] == dm_dwam_cwock_change_vbwank
								&& wocaws->DWAMCwockChangeSuppowt[i][0] == dm_dwam_cwock_change_unsuppowted))))) {
					MaximumMPCCombine = 1;
				} ewse {
					MaximumMPCCombine = 0;
				}
				bweak;
			}
		}
		mode_wib->vba.ImmediateFwipSuppowt =
			wocaws->ImmediateFwipSuppowtedFowState[mode_wib->vba.VowtageWevew][MaximumMPCCombine];
		fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
			mode_wib->vba.DPPPewPwane[k] = wocaws->NoOfDPP[mode_wib->vba.VowtageWevew][MaximumMPCCombine][k];
			wocaws->DPPCWK[k] = wocaws->WequiwedDPPCWK[mode_wib->vba.VowtageWevew][MaximumMPCCombine][k];
		}
		mode_wib->vba.DISPCWK = wocaws->WequiwedDISPCWK[mode_wib->vba.VowtageWevew][MaximumMPCCombine];
		mode_wib->vba.maxMpcComb = MaximumMPCCombine;
	}
	mode_wib->vba.DCFCWK = mode_wib->vba.DCFCWKPewState[mode_wib->vba.VowtageWevew];
	mode_wib->vba.DWAMSpeed = mode_wib->vba.DWAMSpeedPewState[mode_wib->vba.VowtageWevew];
	mode_wib->vba.FabwicCwock = mode_wib->vba.FabwicCwockPewState[mode_wib->vba.VowtageWevew];
	mode_wib->vba.SOCCWK = mode_wib->vba.SOCCWKPewState[mode_wib->vba.VowtageWevew];
	mode_wib->vba.WetuwnBW = wocaws->WetuwnBWPewState[mode_wib->vba.VowtageWevew][0];
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.BwendingAndTiming[k] == k) {
			mode_wib->vba.ODMCombineEnabwed[k] =
					wocaws->ODMCombineEnabwePewState[mode_wib->vba.VowtageWevew][k];
		} ewse {
			mode_wib->vba.ODMCombineEnabwed[k] = dm_odm_combine_mode_disabwed;
		}
		mode_wib->vba.DSCEnabwed[k] =
				wocaws->WequiwesDSC[mode_wib->vba.VowtageWevew][k];
		mode_wib->vba.OutputBpp[k] =
				wocaws->OutputBppPewState[mode_wib->vba.VowtageWevew][k];
	}
}

static void CawcuwateWatewmawksAndDWAMSpeedChangeSuppowt(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int PwefetchMode,
		unsigned int NumbewOfActivePwanes,
		unsigned int MaxWineBuffewWines,
		unsigned int WineBuffewSize,
		unsigned int DPPOutputBuffewPixews,
		unsigned int DETBuffewSizeInKByte,
		unsigned int WwitebackIntewfaceWumaBuffewSize,
		unsigned int WwitebackIntewfaceChwomaBuffewSize,
		doubwe DCFCWK,
		doubwe UwgentOutOfOwdewWetuwn,
		doubwe WetuwnBW,
		boow GPUVMEnabwe,
		int dpte_gwoup_bytes[],
		unsigned int MetaChunkSize,
		doubwe UwgentWatency,
		doubwe ExtwaWatency,
		doubwe WwitebackWatency,
		doubwe WwitebackChunkSize,
		doubwe SOCCWK,
		doubwe DWAMCwockChangeWatency,
		doubwe SWExitTime,
		doubwe SWEntewPwusExitTime,
		doubwe DCFCWKDeepSweep,
		int DPPPewPwane[],
		boow DCCEnabwe[],
		doubwe DPPCWK[],
		doubwe SwathWidthSingweDPPY[],
		unsigned int SwathHeightY[],
		doubwe WeadBandwidthPwaneWuma[],
		unsigned int SwathHeightC[],
		doubwe WeadBandwidthPwaneChwoma[],
		unsigned int WBBitPewPixew[],
		doubwe SwathWidthY[],
		doubwe HWatio[],
		unsigned int vtaps[],
		unsigned int VTAPsChwoma[],
		doubwe VWatio[],
		unsigned int HTotaw[],
		doubwe PixewCwock[],
		unsigned int BwendingAndTiming[],
		doubwe BytePewPixewDETY[],
		doubwe BytePewPixewDETC[],
		boow WwitebackEnabwe[],
		enum souwce_fowmat_cwass WwitebackPixewFowmat[],
		doubwe WwitebackDestinationWidth[],
		doubwe WwitebackDestinationHeight[],
		doubwe WwitebackSouwceHeight[],
		enum cwock_change_suppowt *DWAMCwockChangeSuppowt,
		doubwe *UwgentWatewmawk,
		doubwe *WwitebackUwgentWatewmawk,
		doubwe *DWAMCwockChangeWatewmawk,
		doubwe *WwitebackDWAMCwockChangeWatewmawk,
		doubwe *StuttewExitWatewmawk,
		doubwe *StuttewEntewPwusExitWatewmawk,
		doubwe *MinActiveDWAMCwockChangeWatencySuppowted)
{
	doubwe EffectiveWBWatencyHidingY;
	doubwe EffectiveWBWatencyHidingC;
	doubwe DPPOutputBuffewWinesY;
	doubwe DPPOutputBuffewWinesC;
	unsigned int DETBuffewSizeY;
	unsigned int DETBuffewSizeC;
	doubwe WinesInDETY[DC__NUM_DPP__MAX];
	doubwe WinesInDETC;
	unsigned int WinesInDETYWoundedDownToSwath[DC__NUM_DPP__MAX];
	unsigned int WinesInDETCWoundedDownToSwath;
	doubwe FuwwDETBuffewingTimeY[DC__NUM_DPP__MAX];
	doubwe FuwwDETBuffewingTimeC;
	doubwe ActiveDWAMCwockChangeWatencyMawginY;
	doubwe ActiveDWAMCwockChangeWatencyMawginC;
	doubwe WwitebackDWAMCwockChangeWatencyMawgin;
	doubwe PwaneWithMinActiveDWAMCwockChangeMawgin;
	doubwe SecondMinActiveDWAMCwockChangeMawginOneDispwayInVBWank;
	doubwe FuwwDETBuffewingTimeYStuttewCwiticawPwane = 0;
	doubwe TimeToFinishSwathTwansfewStuttewCwiticawPwane = 0;
	unsigned int k, j;

	mode_wib->vba.TotawActiveDPP = 0;
	mode_wib->vba.TotawDCCActiveDPP = 0;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		mode_wib->vba.TotawActiveDPP = mode_wib->vba.TotawActiveDPP + DPPPewPwane[k];
		if (DCCEnabwe[k] == twue) {
			mode_wib->vba.TotawDCCActiveDPP = mode_wib->vba.TotawDCCActiveDPP + DPPPewPwane[k];
		}
	}

	mode_wib->vba.TotawDataWeadBandwidth = 0;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		mode_wib->vba.TotawDataWeadBandwidth = mode_wib->vba.TotawDataWeadBandwidth
				+ WeadBandwidthPwaneWuma[k] + WeadBandwidthPwaneChwoma[k];
	}

	*UwgentWatewmawk = UwgentWatency + ExtwaWatency;

	*DWAMCwockChangeWatewmawk = DWAMCwockChangeWatency + *UwgentWatewmawk;

	mode_wib->vba.TotawActiveWwiteback = 0;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (WwitebackEnabwe[k] == twue) {
			mode_wib->vba.TotawActiveWwiteback = mode_wib->vba.TotawActiveWwiteback + 1;
		}
	}

	if (mode_wib->vba.TotawActiveWwiteback <= 1) {
		*WwitebackUwgentWatewmawk = WwitebackWatency;
	} ewse {
		*WwitebackUwgentWatewmawk = WwitebackWatency
				+ WwitebackChunkSize * 1024.0 / 32.0 / SOCCWK;
	}

	if (mode_wib->vba.TotawActiveWwiteback <= 1) {
		*WwitebackDWAMCwockChangeWatewmawk = DWAMCwockChangeWatency + WwitebackWatency;
	} ewse {
		*WwitebackDWAMCwockChangeWatewmawk = DWAMCwockChangeWatency + WwitebackWatency
				+ WwitebackChunkSize * 1024.0 / 32.0 / SOCCWK;
	}

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {

		mode_wib->vba.WBWatencyHidingSouwceWinesY = dmw_min((doubwe) MaxWineBuffewWines,
			dmw_fwoow(WineBuffewSize / WBBitPewPixew[k] / (SwathWidthY[k] / dmw_max(HWatio[k], 1.0)), 1))
				- (vtaps[k] - 1);

		mode_wib->vba.WBWatencyHidingSouwceWinesC = dmw_min((doubwe) MaxWineBuffewWines,
			dmw_fwoow(WineBuffewSize / WBBitPewPixew[k] / (SwathWidthY[k] / 2 / dmw_max(HWatio[k] / 2, 1.0)), 1))
				- (VTAPsChwoma[k] - 1);

		EffectiveWBWatencyHidingY = mode_wib->vba.WBWatencyHidingSouwceWinesY / VWatio[k]
				* (HTotaw[k] / PixewCwock[k]);

		EffectiveWBWatencyHidingC = mode_wib->vba.WBWatencyHidingSouwceWinesC
				/ (VWatio[k] / 2) * (HTotaw[k] / PixewCwock[k]);

		if (SwathWidthY[k] > 2 * DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesY = (doubwe) DPPOutputBuffewPixews / SwathWidthY[k];
		} ewse if (SwathWidthY[k] > DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesY = 0.5;
		} ewse {
			DPPOutputBuffewWinesY = 1;
		}

		if (SwathWidthY[k] / 2.0 > 2 * DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesC = (doubwe) DPPOutputBuffewPixews
					/ (SwathWidthY[k] / 2.0);
		} ewse if (SwathWidthY[k] / 2.0 > DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesC = 0.5;
		} ewse {
			DPPOutputBuffewWinesC = 1;
		}

		CawcuwateDETBuffewSize(
				DETBuffewSizeInKByte,
				SwathHeightY[k],
				SwathHeightC[k],
				&DETBuffewSizeY,
				&DETBuffewSizeC);

		WinesInDETY[k] = (doubwe)DETBuffewSizeY / BytePewPixewDETY[k] / SwathWidthY[k];
		WinesInDETYWoundedDownToSwath[k] = dmw_fwoow(WinesInDETY[k], SwathHeightY[k]);
		FuwwDETBuffewingTimeY[k] = WinesInDETYWoundedDownToSwath[k]
				* (HTotaw[k] / PixewCwock[k]) / VWatio[k];
		if (BytePewPixewDETC[k] > 0) {
			WinesInDETC = (doubwe)DETBuffewSizeC / BytePewPixewDETC[k] / (SwathWidthY[k] / 2.0);
			WinesInDETCWoundedDownToSwath = dmw_fwoow(WinesInDETC, SwathHeightC[k]);
			FuwwDETBuffewingTimeC = WinesInDETCWoundedDownToSwath
					* (HTotaw[k] / PixewCwock[k]) / (VWatio[k] / 2);
		} ewse {
			WinesInDETC = 0;
			FuwwDETBuffewingTimeC = 999999;
		}

		ActiveDWAMCwockChangeWatencyMawginY = HTotaw[k] / PixewCwock[k]
				* DPPOutputBuffewWinesY + EffectiveWBWatencyHidingY
				+ FuwwDETBuffewingTimeY[k] - *DWAMCwockChangeWatewmawk;

		if (NumbewOfActivePwanes > 1) {
			ActiveDWAMCwockChangeWatencyMawginY = ActiveDWAMCwockChangeWatencyMawginY
				- (1 - 1.0 / NumbewOfActivePwanes) * SwathHeightY[k] * HTotaw[k] / PixewCwock[k] / VWatio[k];
		}

		if (BytePewPixewDETC[k] > 0) {
			ActiveDWAMCwockChangeWatencyMawginC = HTotaw[k] / PixewCwock[k]
					* DPPOutputBuffewWinesC + EffectiveWBWatencyHidingC
					+ FuwwDETBuffewingTimeC - *DWAMCwockChangeWatewmawk;
			if (NumbewOfActivePwanes > 1) {
				ActiveDWAMCwockChangeWatencyMawginC = ActiveDWAMCwockChangeWatencyMawginC
					- (1 - 1.0 / NumbewOfActivePwanes) * SwathHeightC[k] * HTotaw[k] / PixewCwock[k] / (VWatio[k] / 2);
			}
			mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k] = dmw_min(
					ActiveDWAMCwockChangeWatencyMawginY,
					ActiveDWAMCwockChangeWatencyMawginC);
		} ewse {
			mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k] = ActiveDWAMCwockChangeWatencyMawginY;
		}

		if (WwitebackEnabwe[k] == twue) {
			if (WwitebackPixewFowmat[k] == dm_444_32) {
				WwitebackDWAMCwockChangeWatencyMawgin = (WwitebackIntewfaceWumaBuffewSize
					+ WwitebackIntewfaceChwomaBuffewSize) / (WwitebackDestinationWidth[k]
					* WwitebackDestinationHeight[k] / (WwitebackSouwceHeight[k] * HTotaw[k]
					/ PixewCwock[k]) * 4) - *WwitebackDWAMCwockChangeWatewmawk;
			} ewse {
				WwitebackDWAMCwockChangeWatencyMawgin = dmw_min(
						WwitebackIntewfaceWumaBuffewSize * 8.0 / 10,
						2 * WwitebackIntewfaceChwomaBuffewSize * 8.0 / 10) / (WwitebackDestinationWidth[k]
							* WwitebackDestinationHeight[k] / (WwitebackSouwceHeight[k] * HTotaw[k] / PixewCwock[k]))
						- *WwitebackDWAMCwockChangeWatewmawk;
			}
			mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k] = dmw_min(
					mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k],
					WwitebackDWAMCwockChangeWatencyMawgin);
		}
	}

	mode_wib->vba.MinActiveDWAMCwockChangeMawgin = 999999;
	PwaneWithMinActiveDWAMCwockChangeMawgin = 0;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k]
				< mode_wib->vba.MinActiveDWAMCwockChangeMawgin) {
			mode_wib->vba.MinActiveDWAMCwockChangeMawgin =
					mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k];
			if (BwendingAndTiming[k] == k) {
				PwaneWithMinActiveDWAMCwockChangeMawgin = k;
			} ewse {
				fow (j = 0; j < NumbewOfActivePwanes; ++j) {
					if (BwendingAndTiming[k] == j) {
						PwaneWithMinActiveDWAMCwockChangeMawgin = j;
					}
				}
			}
		}
	}

	*MinActiveDWAMCwockChangeWatencySuppowted = mode_wib->vba.MinActiveDWAMCwockChangeMawgin + DWAMCwockChangeWatency;

	SecondMinActiveDWAMCwockChangeMawginOneDispwayInVBWank = 999999;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (!((k == PwaneWithMinActiveDWAMCwockChangeMawgin) && (BwendingAndTiming[k] == k))
				&& !(BwendingAndTiming[k] == PwaneWithMinActiveDWAMCwockChangeMawgin)
				&& mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k]
						< SecondMinActiveDWAMCwockChangeMawginOneDispwayInVBWank) {
			SecondMinActiveDWAMCwockChangeMawginOneDispwayInVBWank =
					mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k];
		}
	}

	mode_wib->vba.TotawNumbewOfActiveOTG = 0;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (BwendingAndTiming[k] == k) {
			mode_wib->vba.TotawNumbewOfActiveOTG = mode_wib->vba.TotawNumbewOfActiveOTG + 1;
		}
	}

	if (mode_wib->vba.MinActiveDWAMCwockChangeMawgin > 0 && PwefetchMode == 0) {
		*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vactive;
	} ewse if (((mode_wib->vba.SynchwonizedVBwank == twue
			|| mode_wib->vba.TotawNumbewOfActiveOTG == 1
			|| SecondMinActiveDWAMCwockChangeMawginOneDispwayInVBWank > 0)
			&& PwefetchMode == 0)) {
		*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vbwank;
	} ewse {
		*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_unsuppowted;
	}

	FuwwDETBuffewingTimeYStuttewCwiticawPwane = FuwwDETBuffewingTimeY[0];
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (FuwwDETBuffewingTimeY[k] <= FuwwDETBuffewingTimeYStuttewCwiticawPwane) {
			TimeToFinishSwathTwansfewStuttewCwiticawPwane = (SwathHeightY[k]
					- (WinesInDETY[k] - WinesInDETYWoundedDownToSwath[k]))
					* (HTotaw[k] / PixewCwock[k]) / VWatio[k];
		}
	}

	*StuttewExitWatewmawk = SWExitTime + mode_wib->vba.WastPixewOfWineExtwaWatewmawk
			+ ExtwaWatency + 10 / DCFCWKDeepSweep;
	*StuttewEntewPwusExitWatewmawk = dmw_max(
			SWEntewPwusExitTime + mode_wib->vba.WastPixewOfWineExtwaWatewmawk
					+ ExtwaWatency + 10 / DCFCWKDeepSweep,
			TimeToFinishSwathTwansfewStuttewCwiticawPwane);

}

static void CawcuwateDCFCWKDeepSweep(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int NumbewOfActivePwanes,
		doubwe BytePewPixewDETY[],
		doubwe BytePewPixewDETC[],
		doubwe VWatio[],
		doubwe SwathWidthY[],
		int DPPPewPwane[],
		doubwe HWatio[],
		doubwe PixewCwock[],
		doubwe PSCW_THWOUGHPUT[],
		doubwe PSCW_THWOUGHPUT_CHWOMA[],
		doubwe DPPCWK[],
		doubwe *DCFCWKDeepSweep)
{
	unsigned int k;
	doubwe DispwayPipeWineDewivewyTimeWuma;
	doubwe DispwayPipeWineDewivewyTimeChwoma;
	//doubwe   DCFCWKDeepSweepPewPwane[DC__NUM_DPP__MAX];

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (VWatio[k] <= 1) {
			DispwayPipeWineDewivewyTimeWuma = SwathWidthY[k] * DPPPewPwane[k]
					/ HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWuma = SwathWidthY[k] / PSCW_THWOUGHPUT[k]
					/ DPPCWK[k];
		}
		if (BytePewPixewDETC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwoma = 0;
		} ewse {
			if (VWatio[k] / 2 <= 1) {
				DispwayPipeWineDewivewyTimeChwoma = SwathWidthY[k] / 2.0
						* DPPPewPwane[k] / (HWatio[k] / 2) / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwoma = SwathWidthY[k] / 2.0
						/ PSCW_THWOUGHPUT_CHWOMA[k] / DPPCWK[k];
			}
		}

		if (BytePewPixewDETC[k] > 0) {
			mode_wib->vba.DCFCWKDeepSweepPewPwane[k] = dmw_max(
					1.1 * SwathWidthY[k] * dmw_ceiw(BytePewPixewDETY[k], 1)
							/ 32.0 / DispwayPipeWineDewivewyTimeWuma,
					1.1 * SwathWidthY[k] / 2.0
							* dmw_ceiw(BytePewPixewDETC[k], 2) / 32.0
							/ DispwayPipeWineDewivewyTimeChwoma);
		} ewse {
			mode_wib->vba.DCFCWKDeepSweepPewPwane[k] = 1.1 * SwathWidthY[k]
					* dmw_ceiw(BytePewPixewDETY[k], 1) / 64.0
					/ DispwayPipeWineDewivewyTimeWuma;
		}
		mode_wib->vba.DCFCWKDeepSweepPewPwane[k] = dmw_max(
				mode_wib->vba.DCFCWKDeepSweepPewPwane[k],
				PixewCwock[k] / 16);

	}

	*DCFCWKDeepSweep = 8;
	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		*DCFCWKDeepSweep = dmw_max(
				*DCFCWKDeepSweep,
				mode_wib->vba.DCFCWKDeepSweepPewPwane[k]);
	}
}

static void CawcuwateDETBuffewSize(
		unsigned int DETBuffewSizeInKByte,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		unsigned int *DETBuffewSizeY,
		unsigned int *DETBuffewSizeC)
{
	if (SwathHeightC == 0) {
		*DETBuffewSizeY = DETBuffewSizeInKByte * 1024;
		*DETBuffewSizeC = 0;
	} ewse if (SwathHeightY <= SwathHeightC) {
		*DETBuffewSizeY = DETBuffewSizeInKByte * 1024 / 2;
		*DETBuffewSizeC = DETBuffewSizeInKByte * 1024 / 2;
	} ewse {
		*DETBuffewSizeY = DETBuffewSizeInKByte * 1024 * 2 / 3;
		*DETBuffewSizeC = DETBuffewSizeInKByte * 1024 / 3;
	}
}

static void CawcuwateUwgentBuwstFactow(
		unsigned int DETBuffewSizeInKByte,
		unsigned int SwathHeightY,
		unsigned int SwathHeightC,
		unsigned int SwathWidthY,
		doubwe WineTime,
		doubwe UwgentWatency,
		doubwe CuwsowBuffewSize,
		unsigned int CuwsowWidth,
		unsigned int CuwsowBPP,
		doubwe VWatio,
		doubwe VWatioPweY,
		doubwe VWatioPweC,
		doubwe BytePewPixewInDETY,
		doubwe BytePewPixewInDETC,
		doubwe *UwgentBuwstFactowCuwsow,
		doubwe *UwgentBuwstFactowCuwsowPwe,
		doubwe *UwgentBuwstFactowWuma,
		doubwe *UwgentBuwstFactowWumaPwe,
		doubwe *UwgentBuwstFactowChwoma,
		doubwe *UwgentBuwstFactowChwomaPwe,
		unsigned int *NotEnoughUwgentWatencyHiding,
		unsigned int *NotEnoughUwgentWatencyHidingPwe)
{
	doubwe WinesInDETWuma;
	doubwe WinesInDETChwoma;
	unsigned int WinesInCuwsowBuffew;
	doubwe CuwsowBuffewSizeInTime;
	doubwe CuwsowBuffewSizeInTimePwe;
	doubwe DETBuffewSizeInTimeWuma;
	doubwe DETBuffewSizeInTimeWumaPwe;
	doubwe DETBuffewSizeInTimeChwoma;
	doubwe DETBuffewSizeInTimeChwomaPwe;
	unsigned int DETBuffewSizeY;
	unsigned int DETBuffewSizeC;

	*NotEnoughUwgentWatencyHiding = 0;
	*NotEnoughUwgentWatencyHidingPwe = 0;

	if (CuwsowWidth > 0) {
		WinesInCuwsowBuffew = 1 << (unsigned int) dmw_fwoow(
			dmw_wog2(CuwsowBuffewSize * 1024.0 / (CuwsowWidth * CuwsowBPP / 8.0)), 1.0);
		CuwsowBuffewSizeInTime = WinesInCuwsowBuffew * WineTime / VWatio;
		if (CuwsowBuffewSizeInTime - UwgentWatency <= 0) {
			*NotEnoughUwgentWatencyHiding = 1;
			*UwgentBuwstFactowCuwsow = 0;
		} ewse {
			*UwgentBuwstFactowCuwsow = CuwsowBuffewSizeInTime
					/ (CuwsowBuffewSizeInTime - UwgentWatency);
		}
		if (VWatioPweY > 0) {
			CuwsowBuffewSizeInTimePwe = WinesInCuwsowBuffew * WineTime / VWatioPweY;
			if (CuwsowBuffewSizeInTimePwe - UwgentWatency <= 0) {
				*NotEnoughUwgentWatencyHidingPwe = 1;
				*UwgentBuwstFactowCuwsowPwe = 0;
			} ewse {
				*UwgentBuwstFactowCuwsowPwe = CuwsowBuffewSizeInTimePwe
						/ (CuwsowBuffewSizeInTimePwe - UwgentWatency);
			}
		} ewse {
			*UwgentBuwstFactowCuwsowPwe = 1;
		}
	}

	CawcuwateDETBuffewSize(
			DETBuffewSizeInKByte,
			SwathHeightY,
			SwathHeightC,
			&DETBuffewSizeY,
			&DETBuffewSizeC);

	WinesInDETWuma = (doubwe)DETBuffewSizeY / BytePewPixewInDETY / SwathWidthY;
	DETBuffewSizeInTimeWuma = dmw_fwoow(WinesInDETWuma, SwathHeightY) * WineTime / VWatio;
	if (DETBuffewSizeInTimeWuma - UwgentWatency <= 0) {
		*NotEnoughUwgentWatencyHiding = 1;
		*UwgentBuwstFactowWuma = 0;
	} ewse {
		*UwgentBuwstFactowWuma = DETBuffewSizeInTimeWuma
				/ (DETBuffewSizeInTimeWuma - UwgentWatency);
	}
	if (VWatioPweY > 0) {
		DETBuffewSizeInTimeWumaPwe = dmw_fwoow(WinesInDETWuma, SwathHeightY) * WineTime
				/ VWatioPweY;
		if (DETBuffewSizeInTimeWumaPwe - UwgentWatency <= 0) {
			*NotEnoughUwgentWatencyHidingPwe = 1;
			*UwgentBuwstFactowWumaPwe = 0;
		} ewse {
			*UwgentBuwstFactowWumaPwe = DETBuffewSizeInTimeWumaPwe
					/ (DETBuffewSizeInTimeWumaPwe - UwgentWatency);
		}
	} ewse {
		*UwgentBuwstFactowWumaPwe = 1;
	}

	if (BytePewPixewInDETC > 0) {
		WinesInDETChwoma = (doubwe)DETBuffewSizeC / BytePewPixewInDETC / (SwathWidthY / 2);
		DETBuffewSizeInTimeChwoma = dmw_fwoow(WinesInDETChwoma, SwathHeightC) * WineTime
				/ (VWatio / 2);
		if (DETBuffewSizeInTimeChwoma - UwgentWatency <= 0) {
			*NotEnoughUwgentWatencyHiding = 1;
			*UwgentBuwstFactowChwoma = 0;
		} ewse {
			*UwgentBuwstFactowChwoma = DETBuffewSizeInTimeChwoma
					/ (DETBuffewSizeInTimeChwoma - UwgentWatency);
		}
		if (VWatioPweC > 0) {
			DETBuffewSizeInTimeChwomaPwe = dmw_fwoow(WinesInDETChwoma, SwathHeightC)
					* WineTime / VWatioPweC;
			if (DETBuffewSizeInTimeChwomaPwe - UwgentWatency <= 0) {
				*NotEnoughUwgentWatencyHidingPwe = 1;
				*UwgentBuwstFactowChwomaPwe = 0;
			} ewse {
				*UwgentBuwstFactowChwomaPwe = DETBuffewSizeInTimeChwomaPwe
						/ (DETBuffewSizeInTimeChwomaPwe - UwgentWatency);
			}
		} ewse {
			*UwgentBuwstFactowChwomaPwe = 1;
		}
	}
}

static void CawcuwatePixewDewivewyTimes(
		unsigned int NumbewOfActivePwanes,
		doubwe VWatio[],
		doubwe VWatioPwefetchY[],
		doubwe VWatioPwefetchC[],
		unsigned int swath_width_wuma_ub[],
		unsigned int swath_width_chwoma_ub[],
		int DPPPewPwane[],
		doubwe HWatio[],
		doubwe PixewCwock[],
		doubwe PSCW_THWOUGHPUT[],
		doubwe PSCW_THWOUGHPUT_CHWOMA[],
		doubwe DPPCWK[],
		doubwe BytePewPixewDETC[],
		enum scan_diwection_cwass SouwceScan[],
		unsigned int BwockWidth256BytesY[],
		unsigned int BwockHeight256BytesY[],
		unsigned int BwockWidth256BytesC[],
		unsigned int BwockHeight256BytesC[],
		doubwe DispwayPipeWineDewivewyTimeWuma[],
		doubwe DispwayPipeWineDewivewyTimeChwoma[],
		doubwe DispwayPipeWineDewivewyTimeWumaPwefetch[],
		doubwe DispwayPipeWineDewivewyTimeChwomaPwefetch[],
		doubwe DispwayPipeWequestDewivewyTimeWuma[],
		doubwe DispwayPipeWequestDewivewyTimeChwoma[],
		doubwe DispwayPipeWequestDewivewyTimeWumaPwefetch[],
		doubwe DispwayPipeWequestDewivewyTimeChwomaPwefetch[])
{
	doubwe weq_pew_swath_ub;
	unsigned int k;

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (VWatio[k] <= 1) {
			DispwayPipeWineDewivewyTimeWuma[k] = swath_width_wuma_ub[k] * DPPPewPwane[k]
					/ HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWuma[k] = swath_width_wuma_ub[k]
					/ PSCW_THWOUGHPUT[k] / DPPCWK[k];
		}

		if (BytePewPixewDETC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwoma[k] = 0;
		} ewse {
			if (VWatio[k] / 2 <= 1) {
				DispwayPipeWineDewivewyTimeChwoma[k] = swath_width_chwoma_ub[k]
						* DPPPewPwane[k] / (HWatio[k] / 2) / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwoma[k] = swath_width_chwoma_ub[k]
						/ PSCW_THWOUGHPUT_CHWOMA[k] / DPPCWK[k];
			}
		}

		if (VWatioPwefetchY[k] <= 1) {
			DispwayPipeWineDewivewyTimeWumaPwefetch[k] = swath_width_wuma_ub[k]
					* DPPPewPwane[k] / HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWumaPwefetch[k] = swath_width_wuma_ub[k]
					/ PSCW_THWOUGHPUT[k] / DPPCWK[k];
		}

		if (BytePewPixewDETC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (VWatioPwefetchC[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwomaPwefetch[k] =
						swath_width_chwoma_ub[k] * DPPPewPwane[k]
								/ (HWatio[k] / 2) / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwomaPwefetch[k] =
						swath_width_chwoma_ub[k] / PSCW_THWOUGHPUT_CHWOMA[k] / DPPCWK[k];
			}
		}
	}

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (SouwceScan[k] == dm_howz) {
			weq_pew_swath_ub = swath_width_wuma_ub[k] / BwockWidth256BytesY[k];
		} ewse {
			weq_pew_swath_ub = swath_width_wuma_ub[k] / BwockHeight256BytesY[k];
		}
		DispwayPipeWequestDewivewyTimeWuma[k] = DispwayPipeWineDewivewyTimeWuma[k]
				/ weq_pew_swath_ub;
		DispwayPipeWequestDewivewyTimeWumaPwefetch[k] =
				DispwayPipeWineDewivewyTimeWumaPwefetch[k] / weq_pew_swath_ub;
		if (BytePewPixewDETC[k] == 0) {
			DispwayPipeWequestDewivewyTimeChwoma[k] = 0;
			DispwayPipeWequestDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (SouwceScan[k] == dm_howz) {
				weq_pew_swath_ub = swath_width_chwoma_ub[k]
						/ BwockWidth256BytesC[k];
			} ewse {
				weq_pew_swath_ub = swath_width_chwoma_ub[k]
						/ BwockHeight256BytesC[k];
			}
			DispwayPipeWequestDewivewyTimeChwoma[k] =
					DispwayPipeWineDewivewyTimeChwoma[k] / weq_pew_swath_ub;
			DispwayPipeWequestDewivewyTimeChwomaPwefetch[k] =
					DispwayPipeWineDewivewyTimeChwomaPwefetch[k] / weq_pew_swath_ub;
		}
	}
}

static void CawcuwateMetaAndPTETimes(
		unsigned int NumbewOfActivePwanes,
		boow GPUVMEnabwe,
		unsigned int MetaChunkSize,
		unsigned int MinMetaChunkSizeBytes,
		unsigned int GPUVMMaxPageTabweWevews,
		unsigned int HTotaw[],
		doubwe VWatio[],
		doubwe VWatioPwefetchY[],
		doubwe VWatioPwefetchC[],
		doubwe DestinationWinesToWequestWowInVBwank[],
		doubwe DestinationWinesToWequestWowInImmediateFwip[],
		doubwe DestinationWinesToWequestVMInVBwank[],
		doubwe DestinationWinesToWequestVMInImmediateFwip[],
		boow DCCEnabwe[],
		doubwe PixewCwock[],
		doubwe BytePewPixewDETY[],
		doubwe BytePewPixewDETC[],
		enum scan_diwection_cwass SouwceScan[],
		unsigned int dpte_wow_height[],
		unsigned int dpte_wow_height_chwoma[],
		unsigned int meta_wow_width[],
		unsigned int meta_wow_height[],
		unsigned int meta_weq_width[],
		unsigned int meta_weq_height[],
		int dpte_gwoup_bytes[],
		unsigned int PTEWequestSizeY[],
		unsigned int PTEWequestSizeC[],
		unsigned int PixewPTEWeqWidthY[],
		unsigned int PixewPTEWeqHeightY[],
		unsigned int PixewPTEWeqWidthC[],
		unsigned int PixewPTEWeqHeightC[],
		unsigned int dpte_wow_width_wuma_ub[],
		unsigned int dpte_wow_width_chwoma_ub[],
		unsigned int vm_gwoup_bytes[],
		unsigned int dpde0_bytes_pew_fwame_ub_w[],
		unsigned int dpde0_bytes_pew_fwame_ub_c[],
		unsigned int meta_pte_bytes_pew_fwame_ub_w[],
		unsigned int meta_pte_bytes_pew_fwame_ub_c[],
		doubwe DST_Y_PEW_PTE_WOW_NOM_W[],
		doubwe DST_Y_PEW_PTE_WOW_NOM_C[],
		doubwe DST_Y_PEW_META_WOW_NOM_W[],
		doubwe TimePewMetaChunkNominaw[],
		doubwe TimePewMetaChunkVBwank[],
		doubwe TimePewMetaChunkFwip[],
		doubwe time_pew_pte_gwoup_nom_wuma[],
		doubwe time_pew_pte_gwoup_vbwank_wuma[],
		doubwe time_pew_pte_gwoup_fwip_wuma[],
		doubwe time_pew_pte_gwoup_nom_chwoma[],
		doubwe time_pew_pte_gwoup_vbwank_chwoma[],
		doubwe time_pew_pte_gwoup_fwip_chwoma[],
		doubwe TimePewVMGwoupVBwank[],
		doubwe TimePewVMGwoupFwip[],
		doubwe TimePewVMWequestVBwank[],
		doubwe TimePewVMWequestFwip[])
{
	unsigned int meta_chunk_width;
	unsigned int min_meta_chunk_width;
	unsigned int meta_chunk_pew_wow_int;
	unsigned int meta_wow_wemaindew;
	unsigned int meta_chunk_thweshowd;
	unsigned int meta_chunks_pew_wow_ub;
	unsigned int dpte_gwoup_width_wuma;
	unsigned int dpte_gwoup_width_chwoma;
	unsigned int dpte_gwoups_pew_wow_wuma_ub;
	unsigned int dpte_gwoups_pew_wow_chwoma_ub;
	unsigned int num_gwoup_pew_wowew_vm_stage;
	unsigned int num_weq_pew_wowew_vm_stage;
	unsigned int k;

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (GPUVMEnabwe == twue) {
			DST_Y_PEW_PTE_WOW_NOM_W[k] = dpte_wow_height[k] / VWatio[k];
			if (BytePewPixewDETC[k] == 0) {
				DST_Y_PEW_PTE_WOW_NOM_C[k] = 0;
			} ewse {
				DST_Y_PEW_PTE_WOW_NOM_C[k] = dpte_wow_height_chwoma[k] / (VWatio[k] / 2);
			}
		} ewse {
			DST_Y_PEW_PTE_WOW_NOM_W[k] = 0;
			DST_Y_PEW_PTE_WOW_NOM_C[k] = 0;
		}
		if (DCCEnabwe[k] == twue) {
			DST_Y_PEW_META_WOW_NOM_W[k] = meta_wow_height[k] / VWatio[k];
		} ewse {
			DST_Y_PEW_META_WOW_NOM_W[k] = 0;
		}
	}

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (DCCEnabwe[k] == twue) {
			meta_chunk_width = MetaChunkSize * 1024 * 256
					/ dmw_ceiw(BytePewPixewDETY[k], 1) / meta_wow_height[k];
			min_meta_chunk_width = MinMetaChunkSizeBytes * 256
					/ dmw_ceiw(BytePewPixewDETY[k], 1) / meta_wow_height[k];
			meta_chunk_pew_wow_int = meta_wow_width[k] / meta_chunk_width;
			meta_wow_wemaindew = meta_wow_width[k] % meta_chunk_width;
			if (SouwceScan[k] == dm_howz) {
				meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_width[k];
			} ewse {
				meta_chunk_thweshowd = 2 * min_meta_chunk_width
						- meta_weq_height[k];
			}
			if (meta_wow_wemaindew <= meta_chunk_thweshowd) {
				meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 1;
			} ewse {
				meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 2;
			}
			TimePewMetaChunkNominaw[k] = meta_wow_height[k] / VWatio[k] * HTotaw[k]
					/ PixewCwock[k] / meta_chunks_pew_wow_ub;
			TimePewMetaChunkVBwank[k] = DestinationWinesToWequestWowInVBwank[k]
					* HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			TimePewMetaChunkFwip[k] = DestinationWinesToWequestWowInImmediateFwip[k]
					* HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
		} ewse {
			TimePewMetaChunkNominaw[k] = 0;
			TimePewMetaChunkVBwank[k] = 0;
			TimePewMetaChunkFwip[k] = 0;
		}
	}

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (GPUVMEnabwe == twue) {
			if (SouwceScan[k] == dm_howz) {
				dpte_gwoup_width_wuma = dpte_gwoup_bytes[k] / PTEWequestSizeY[k]
						* PixewPTEWeqWidthY[k];
			} ewse {
				dpte_gwoup_width_wuma = dpte_gwoup_bytes[k] / PTEWequestSizeY[k]
						* PixewPTEWeqHeightY[k];
			}
			dpte_gwoups_pew_wow_wuma_ub = dmw_ceiw(
					(fwoat) dpte_wow_width_wuma_ub[k] / dpte_gwoup_width_wuma,
					1);
			time_pew_pte_gwoup_nom_wuma[k] = DST_Y_PEW_PTE_WOW_NOM_W[k] * HTotaw[k]
					/ PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			time_pew_pte_gwoup_vbwank_wuma[k] = DestinationWinesToWequestWowInVBwank[k]
					* HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			time_pew_pte_gwoup_fwip_wuma[k] =
					DestinationWinesToWequestWowInImmediateFwip[k] * HTotaw[k]
							/ PixewCwock[k]
							/ dpte_gwoups_pew_wow_wuma_ub;
			if (BytePewPixewDETC[k] == 0) {
				time_pew_pte_gwoup_nom_chwoma[k] = 0;
				time_pew_pte_gwoup_vbwank_chwoma[k] = 0;
				time_pew_pte_gwoup_fwip_chwoma[k] = 0;
			} ewse {
				if (SouwceScan[k] == dm_howz) {
					dpte_gwoup_width_chwoma = dpte_gwoup_bytes[k]
							/ PTEWequestSizeC[k] * PixewPTEWeqWidthC[k];
				} ewse {
					dpte_gwoup_width_chwoma = dpte_gwoup_bytes[k]
							/ PTEWequestSizeC[k]
							* PixewPTEWeqHeightC[k];
				}
				dpte_gwoups_pew_wow_chwoma_ub = dmw_ceiw(
						(fwoat) dpte_wow_width_chwoma_ub[k]
								/ dpte_gwoup_width_chwoma,
						1);
				time_pew_pte_gwoup_nom_chwoma[k] = DST_Y_PEW_PTE_WOW_NOM_C[k]
						* HTotaw[k] / PixewCwock[k]
						/ dpte_gwoups_pew_wow_chwoma_ub;
				time_pew_pte_gwoup_vbwank_chwoma[k] =
						DestinationWinesToWequestWowInVBwank[k] * HTotaw[k]
								/ PixewCwock[k]
								/ dpte_gwoups_pew_wow_chwoma_ub;
				time_pew_pte_gwoup_fwip_chwoma[k] =
						DestinationWinesToWequestWowInImmediateFwip[k]
								* HTotaw[k] / PixewCwock[k]
								/ dpte_gwoups_pew_wow_chwoma_ub;
			}
		} ewse {
			time_pew_pte_gwoup_nom_wuma[k] = 0;
			time_pew_pte_gwoup_vbwank_wuma[k] = 0;
			time_pew_pte_gwoup_fwip_wuma[k] = 0;
			time_pew_pte_gwoup_nom_chwoma[k] = 0;
			time_pew_pte_gwoup_vbwank_chwoma[k] = 0;
			time_pew_pte_gwoup_fwip_chwoma[k] = 0;
		}
	}

	fow (k = 0; k < NumbewOfActivePwanes; ++k) {
		if (GPUVMEnabwe == twue && (DCCEnabwe[k] == twue || GPUVMMaxPageTabweWevews > 1)) {
			if (DCCEnabwe[k] == fawse) {
				if (BytePewPixewDETC[k] > 0) {
					num_gwoup_pew_wowew_vm_stage =
						dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1)
						+ dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_c[k]) / (doubwe) (vm_gwoup_bytes[k]), 1);
				} ewse {
					num_gwoup_pew_wowew_vm_stage =
							dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1);
				}
			} ewse {
				if (GPUVMMaxPageTabweWevews == 1) {
					if (BytePewPixewDETC[k] > 0) {
						num_gwoup_pew_wowew_vm_stage =
							dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1)
							+ dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_c[k]) / (doubwe) (vm_gwoup_bytes[k]), 1);
					} ewse {
						num_gwoup_pew_wowew_vm_stage =
							dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1);
					}
				} ewse {
					if (BytePewPixewDETC[k] > 0) {
						num_gwoup_pew_wowew_vm_stage =
							dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1)
							+ dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_c[k]) / (doubwe) (vm_gwoup_bytes[k]), 1)
							+ dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1)
							+ dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_c[k]) / (doubwe) (vm_gwoup_bytes[k]), 1);
					} ewse {
						num_gwoup_pew_wowew_vm_stage =
							dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1)
							+ dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) / (doubwe) (vm_gwoup_bytes[k]), 1);
					}
				}
			}

			if (DCCEnabwe[k] == fawse) {
				if (BytePewPixewDETC[k] > 0) {
					num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k]
							/ 64 + dpde0_bytes_pew_fwame_ub_c[k] / 64;
				} ewse {
					num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k]
							/ 64;
				}
			} ewse {
				if (GPUVMMaxPageTabweWevews == 1) {
					if (BytePewPixewDETC[k] > 0) {
						num_weq_pew_wowew_vm_stage = meta_pte_bytes_pew_fwame_ub_w[k] / 64
							+ meta_pte_bytes_pew_fwame_ub_c[k] / 64;
					} ewse {
						num_weq_pew_wowew_vm_stage = meta_pte_bytes_pew_fwame_ub_w[k] / 64;
					}
				} ewse {
					if (BytePewPixewDETC[k] > 0) {
						num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64
							+ dpde0_bytes_pew_fwame_ub_c[k] / 64
							+ meta_pte_bytes_pew_fwame_ub_w[k] / 64
							+ meta_pte_bytes_pew_fwame_ub_c[k] / 64;
					} ewse {
						num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64
							+ meta_pte_bytes_pew_fwame_ub_w[k] / 64;
					}
				}
			}

			TimePewVMGwoupVBwank[k] = DestinationWinesToWequestVMInVBwank[k] * HTotaw[k]
					/ PixewCwock[k] / num_gwoup_pew_wowew_vm_stage;
			TimePewVMGwoupFwip[k] = DestinationWinesToWequestVMInImmediateFwip[k]
					* HTotaw[k] / PixewCwock[k] / num_gwoup_pew_wowew_vm_stage;
			TimePewVMWequestVBwank[k] = DestinationWinesToWequestVMInVBwank[k]
					* HTotaw[k] / PixewCwock[k] / num_weq_pew_wowew_vm_stage;
			TimePewVMWequestFwip[k] = DestinationWinesToWequestVMInImmediateFwip[k]
					* HTotaw[k] / PixewCwock[k] / num_weq_pew_wowew_vm_stage;

			if (GPUVMMaxPageTabweWevews > 2) {
				TimePewVMGwoupVBwank[k] = TimePewVMGwoupVBwank[k] / 2;
				TimePewVMGwoupFwip[k] = TimePewVMGwoupFwip[k] / 2;
				TimePewVMWequestVBwank[k] = TimePewVMWequestVBwank[k] / 2;
				TimePewVMWequestFwip[k] = TimePewVMWequestFwip[k] / 2;
			}

		} ewse {
			TimePewVMGwoupVBwank[k] = 0;
			TimePewVMGwoupFwip[k] = 0;
			TimePewVMWequestVBwank[k] = 0;
			TimePewVMWequestFwip[k] = 0;
		}
	}
}

static doubwe CawcuwateExtwaWatency(
		doubwe UwgentWoundTwipAndOutOfOwdewWatency,
		int TotawNumbewOfActiveDPP,
		int PixewChunkSizeInKByte,
		int TotawNumbewOfDCCActiveDPP,
		int MetaChunkSize,
		doubwe WetuwnBW,
		boow GPUVMEnabwe,
		boow HostVMEnabwe,
		int NumbewOfActivePwanes,
		int NumbewOfDPP[],
		int dpte_gwoup_bytes[],
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData,
		doubwe PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy,
		int HostVMMaxPageTabweWevews,
		int HostVMCachedPageTabweWevews)
{
	doubwe CawcuwateExtwaWatency;
	doubwe HostVMInefficiencyFactow;
	int HostVMDynamicWevews;

	if (GPUVMEnabwe && HostVMEnabwe) {
		HostVMInefficiencyFactow =
				PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewMixedWithVMData
						/ PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyVMDataOnwy;
		HostVMDynamicWevews = HostVMMaxPageTabweWevews - HostVMCachedPageTabweWevews;
	} ewse {
		HostVMInefficiencyFactow = 1;
		HostVMDynamicWevews = 0;
	}

	CawcuwateExtwaWatency = UwgentWoundTwipAndOutOfOwdewWatency
			+ (TotawNumbewOfActiveDPP * PixewChunkSizeInKByte
					+ TotawNumbewOfDCCActiveDPP * MetaChunkSize) * 1024.0
					/ WetuwnBW;

	if (GPUVMEnabwe) {
		int k;

		fow (k = 0; k < NumbewOfActivePwanes; k++) {
			CawcuwateExtwaWatency = CawcuwateExtwaWatency
					+ NumbewOfDPP[k] * dpte_gwoup_bytes[k]
							* (1 + 8 * HostVMDynamicWevews)
							* HostVMInefficiencyFactow / WetuwnBW;
		}
	}
	wetuwn CawcuwateExtwaWatency;
}

