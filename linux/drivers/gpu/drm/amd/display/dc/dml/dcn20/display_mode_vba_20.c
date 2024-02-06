/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
#incwude "dispway_mode_vba_20.h"
#incwude "../dmw_inwine_defs.h"

/*
 * NOTE:
 *   This fiwe is gcc-pawseabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */

#define BPP_INVAWID 0
#define BPP_BWENDED_PIPE 0xffffffff
#define DCN20_MAX_420_IMAGE_WIDTH 4096

static doubwe adjust_WetuwnBW(
		stwuct dispway_mode_wib *mode_wib,
		doubwe WetuwnBW,
		boow DCCEnabwedAnyPwane,
		doubwe WetuwnBandwidthToDCN);
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
		doubwe DPPCWK,
		doubwe DISPCWK,
		doubwe PixewCwock,
		doubwe DCFCWKDeepSweep,
		unsigned int DSCDeway,
		unsigned int DPPPewPwane,
		boow ScawewEnabwed,
		unsigned int NumbewOfCuwsows,
		doubwe DPPCWKDewaySubtotaw,
		doubwe DPPCWKDewaySCW,
		doubwe DPPCWKDewaySCWWBOnwy,
		doubwe DPPCWKDewayCNVCFowmatew,
		doubwe DPPCWKDewayCNVCCuwsow,
		doubwe DISPCWKDewaySubtotaw,
		unsigned int ScawewWecoutWidth,
		enum output_fowmat_cwass OutputFowmat,
		unsigned int VBwank,
		unsigned int HTotaw,
		unsigned int MaxIntewDCNTiweWepeatews,
		unsigned int VStawtup,
		unsigned int PageTabweWevews,
		boow GPUVMEnabwe,
		boow DynamicMetadataEnabwe,
		unsigned int DynamicMetadataWinesBefoweActiveWequiwed,
		unsigned int DynamicMetadataTwansmittedBytes,
		boow DCCEnabwe,
		doubwe UwgentWatencyPixewDataOnwy,
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
		boow IntewwaceEnabwe,
		boow PwogwessiveToIntewwaceUnitInOPP,
		doubwe *DSTXAftewScawew,
		doubwe *DSTYAftewScawew,
		doubwe *DestinationWinesFowPwefetch,
		doubwe *PwefetchBandwidth,
		doubwe *DestinationWinesToWequestVMInVBwank,
		doubwe *DestinationWinesToWequestWowInVBwank,
		doubwe *VWatioPwefetchY,
		doubwe *VWatioPwefetchC,
		doubwe *WequiwedPwefetchPixDataBW,
		unsigned int *VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
		doubwe *Tno_bw,
		unsigned int *VUpdateOffsetPix,
		doubwe *VUpdateWidthPix,
		doubwe *VWeadyOffsetPix);
static doubwe WoundToDFSGwanuwawityUp(doubwe Cwock, doubwe VCOSpeed);
static doubwe WoundToDFSGwanuwawityDown(doubwe Cwock, doubwe VCOSpeed);
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
		unsigned int VMMPageSize,
		unsigned int PTEBuffewSizeInWequestsWuma,
		unsigned int PDEPwocessingBufIn64KBWeqs,
		unsigned int Pitch,
		unsigned int DCCMetaPitch,
		unsigned int *MacwoTiweWidth,
		unsigned int *MetaWowByte,
		unsigned int *PixewPTEBytesPewWow,
		boow *PTEBuffewSizeNotExceeded,
		unsigned int *dpte_wow_height,
		unsigned int *meta_wow_height);
static doubwe CawcuwateTWait(
		unsigned int PwefetchMode,
		doubwe DWAMCwockChangeWatency,
		doubwe UwgentWatencyPixewDataOnwy,
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
		doubwe *dpte_wow_bw,
		doubwe *quaw_wow_bw);
static void CawcuwateFwipScheduwe(
		stwuct dispway_mode_wib *mode_wib,
		doubwe UwgentExtwaWatency,
		doubwe UwgentWatencyPixewDataOnwy,
		unsigned int GPUVMMaxPageTabweWevews,
		boow GPUVMEnabwe,
		doubwe BandwidthAvaiwabweFowImmediateFwip,
		unsigned int TotImmediateFwipBytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int ImmediateFwipBytes,
		doubwe WineTime,
		doubwe VWatio,
		doubwe Tno_bw,
		doubwe PDEAndMetaPTEBytesFwame,
		unsigned int MetaWowByte,
		unsigned int PixewPTEBytesPewWow,
		boow DCCEnabwe,
		unsigned int dpte_wow_height,
		unsigned int meta_wow_height,
		doubwe quaw_wow_bw,
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

static void dmw20_DispwayPipeConfiguwation(stwuct dispway_mode_wib *mode_wib);
static void dmw20_DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation(
		stwuct dispway_mode_wib *mode_wib);

void dmw20_wecawcuwate(stwuct dispway_mode_wib *mode_wib)
{
	ModeSuppowtAndSystemConfiguwation(mode_wib);
	mode_wib->vba.FabwicAndDWAMBandwidth = dmw_min(
		mode_wib->vba.DWAMSpeed * mode_wib->vba.NumbewOfChannews * mode_wib->vba.DWAMChannewWidth,
		mode_wib->vba.FabwicCwock * mode_wib->vba.FabwicDatapathToDCNDataWetuwn) / 1000.0;
	PixewCwockAdjustmentFowPwogwessiveToIntewwaceUnit(mode_wib);
	dmw20_DispwayPipeConfiguwation(mode_wib);
	dmw20_DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation(mode_wib);
}

static doubwe adjust_WetuwnBW(
		stwuct dispway_mode_wib *mode_wib,
		doubwe WetuwnBW,
		boow DCCEnabwedAnyPwane,
		doubwe WetuwnBandwidthToDCN)
{
	doubwe CwiticawCompwession;

	if (DCCEnabwedAnyPwane
			&& WetuwnBandwidthToDCN
					> mode_wib->vba.DCFCWK * mode_wib->vba.WetuwnBusWidth / 4.0)
		WetuwnBW =
				dmw_min(
						WetuwnBW,
						WetuwnBandwidthToDCN * 4
								* (1.0
										- mode_wib->vba.UwgentWatencyPixewDataOnwy
												/ ((mode_wib->vba.WOBBuffewSizeInKByte
														- mode_wib->vba.PixewChunkSizeInKByte)
														* 1024
														/ WetuwnBandwidthToDCN
														- mode_wib->vba.DCFCWK
																* mode_wib->vba.WetuwnBusWidth
																/ 4)
										+ mode_wib->vba.UwgentWatencyPixewDataOnwy));

	CwiticawCompwession = 2.0 * mode_wib->vba.WetuwnBusWidth * mode_wib->vba.DCFCWK
			* mode_wib->vba.UwgentWatencyPixewDataOnwy
			/ (WetuwnBandwidthToDCN * mode_wib->vba.UwgentWatencyPixewDataOnwy
					+ (mode_wib->vba.WOBBuffewSizeInKByte
							- mode_wib->vba.PixewChunkSizeInKByte)
							* 1024);

	if (DCCEnabwedAnyPwane && CwiticawCompwession > 1.0 && CwiticawCompwession < 4.0)
		WetuwnBW =
				dmw_min(
						WetuwnBW,
						4.0 * WetuwnBandwidthToDCN
								* (mode_wib->vba.WOBBuffewSizeInKByte
										- mode_wib->vba.PixewChunkSizeInKByte)
								* 1024
								* mode_wib->vba.WetuwnBusWidth
								* mode_wib->vba.DCFCWK
								* mode_wib->vba.UwgentWatencyPixewDataOnwy
								/ dmw_pow(
										(WetuwnBandwidthToDCN
												* mode_wib->vba.UwgentWatencyPixewDataOnwy
												+ (mode_wib->vba.WOBBuffewSizeInKByte
														- mode_wib->vba.PixewChunkSizeInKByte)
														* 1024),
										2));

	wetuwn WetuwnBW;
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
	unsigned int pixewsPewCwock, wstaww, D, initawXmitDeway, w, s, ix, wx, p, w0, a, ax, w,
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
		s = 1;
	ewse
		s = 0;

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
	Deway = w * wx * (numSwices - 1) + ax + s + wstaww + 22;

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
		doubwe DPPCWK,
		doubwe DISPCWK,
		doubwe PixewCwock,
		doubwe DCFCWKDeepSweep,
		unsigned int DSCDeway,
		unsigned int DPPPewPwane,
		boow ScawewEnabwed,
		unsigned int NumbewOfCuwsows,
		doubwe DPPCWKDewaySubtotaw,
		doubwe DPPCWKDewaySCW,
		doubwe DPPCWKDewaySCWWBOnwy,
		doubwe DPPCWKDewayCNVCFowmatew,
		doubwe DPPCWKDewayCNVCCuwsow,
		doubwe DISPCWKDewaySubtotaw,
		unsigned int ScawewWecoutWidth,
		enum output_fowmat_cwass OutputFowmat,
		unsigned int VBwank,
		unsigned int HTotaw,
		unsigned int MaxIntewDCNTiweWepeatews,
		unsigned int VStawtup,
		unsigned int PageTabweWevews,
		boow GPUVMEnabwe,
		boow DynamicMetadataEnabwe,
		unsigned int DynamicMetadataWinesBefoweActiveWequiwed,
		unsigned int DynamicMetadataTwansmittedBytes,
		boow DCCEnabwe,
		doubwe UwgentWatencyPixewDataOnwy,
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
		boow IntewwaceEnabwe,
		boow PwogwessiveToIntewwaceUnitInOPP,
		doubwe *DSTXAftewScawew,
		doubwe *DSTYAftewScawew,
		doubwe *DestinationWinesFowPwefetch,
		doubwe *PwefetchBandwidth,
		doubwe *DestinationWinesToWequestVMInVBwank,
		doubwe *DestinationWinesToWequestWowInVBwank,
		doubwe *VWatioPwefetchY,
		doubwe *VWatioPwefetchC,
		doubwe *WequiwedPwefetchPixDataBW,
		unsigned int *VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
		doubwe *Tno_bw,
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
	doubwe Tpwe_oto;
	doubwe dst_y_pwefetch_oto;
	doubwe TimeFowFetchingMetaPTE = 0;
	doubwe TimeFowFetchingWowInVBwank = 0;
	doubwe WinesToWequestPwefetchPixewData = 0;

	if (ScawewEnabwed)
		DPPCycwes = DPPCWKDewaySubtotaw + DPPCWKDewaySCW;
	ewse
		DPPCycwes = DPPCWKDewaySubtotaw + DPPCWKDewaySCWWBOnwy;

	DPPCycwes = DPPCycwes + DPPCWKDewayCNVCFowmatew + NumbewOfCuwsows * DPPCWKDewayCNVCCuwsow;

	DISPCWKCycwes = DISPCWKDewaySubtotaw;

	if (DPPCWK == 0.0 || DISPCWK == 0.0)
		wetuwn twue;

	*DSTXAftewScawew = DPPCycwes * PixewCwock / DPPCWK + DISPCWKCycwes * PixewCwock / DISPCWK
			+ DSCDeway;

	if (DPPPewPwane > 1)
		*DSTXAftewScawew = *DSTXAftewScawew + ScawewWecoutWidth;

	if (OutputFowmat == dm_420 || (IntewwaceEnabwe && PwogwessiveToIntewwaceUnitInOPP))
		*DSTYAftewScawew = 1;
	ewse
		*DSTYAftewScawew = 0;

	DSTTotawPixewsAftewScawew = ((doubwe) (*DSTYAftewScawew * HTotaw)) + *DSTXAftewScawew;
	*DSTYAftewScawew = dmw_fwoow(DSTTotawPixewsAftewScawew / HTotaw, 1);
	*DSTXAftewScawew = DSTTotawPixewsAftewScawew - ((doubwe) (*DSTYAftewScawew * HTotaw));

	*VUpdateOffsetPix = dmw_ceiw(HTotaw / 4.0, 1);
	TotawWepeatewDewayTime = MaxIntewDCNTiweWepeatews * (2.0 / DPPCWK + 3.0 / DISPCWK);
	*VUpdateWidthPix = (14.0 / DCFCWKDeepSweep + 12.0 / DPPCWK + TotawWepeatewDewayTime)
			* PixewCwock;

	*VWeadyOffsetPix = dmw_max(
			150.0 / DPPCWK,
			TotawWepeatewDewayTime + 20.0 / DCFCWKDeepSweep + 10.0 / DPPCWK)
			* PixewCwock;

	Tsetup = (doubwe) (*VUpdateOffsetPix + *VUpdateWidthPix + *VWeadyOffsetPix) / PixewCwock;

	WineTime = (doubwe) HTotaw / PixewCwock;

	if (DynamicMetadataEnabwe) {
		doubwe Tdmbf, Tdmec, Tdmsks;

		Tdm = dmw_max(0.0, UwgentExtwaWatency - TCawc);
		Tdmbf = DynamicMetadataTwansmittedBytes / 4.0 / DISPCWK;
		Tdmec = WineTime;
		if (DynamicMetadataWinesBefoweActiveWequiwed == 0)
			Tdmsks = VBwank * WineTime / 2.0;
		ewse
			Tdmsks = DynamicMetadataWinesBefoweActiveWequiwed * WineTime;
		if (IntewwaceEnabwe && !PwogwessiveToIntewwaceUnitInOPP)
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
		if (PageTabweWevews == 4)
			*Tno_bw = UwgentExtwaWatency + UwgentWatencyPixewDataOnwy;
		ewse if (PageTabweWevews == 3)
			*Tno_bw = UwgentExtwaWatency;
		ewse
			*Tno_bw = 0;
	} ewse if (DCCEnabwe)
		*Tno_bw = WineTime;
	ewse
		*Tno_bw = WineTime / 4;

	dst_y_pwefetch_equ = VStawtup - dmw_max(TCawc + TWait, XFCWemoteSuwfaceFwipDeway) / WineTime
			- (Tsetup + Tdm) / WineTime
			- (*DSTYAftewScawew + *DSTXAftewScawew / HTotaw);

	Tsw_oto = dmw_max(PwefetchSouwceWinesY, PwefetchSouwceWinesC) * WineTime;

	pwefetch_bw_oto = (MetaWowByte + PixewPTEBytesPewWow
			+ PwefetchSouwceWinesY * SwathWidthY * dmw_ceiw(BytePewPixewDETY, 1)
			+ PwefetchSouwceWinesC * SwathWidthY / 2 * dmw_ceiw(BytePewPixewDETC, 2))
			/ Tsw_oto;

	if (GPUVMEnabwe == twue) {
		Tvm_oto =
				dmw_max(
						*Tno_bw + PDEAndMetaPTEBytesFwame / pwefetch_bw_oto,
						dmw_max(
								UwgentExtwaWatency
										+ UwgentWatencyPixewDataOnwy
												* (PageTabweWevews
														- 1),
								WineTime / 4.0));
	} ewse
		Tvm_oto = WineTime / 4.0;

	if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
		Tw0_oto = dmw_max(
				(MetaWowByte + PixewPTEBytesPewWow) / pwefetch_bw_oto,
				dmw_max(UwgentWatencyPixewDataOnwy, dmw_max(WineTime - Tvm_oto, WineTime / 4)));
	} ewse
		Tw0_oto = WineTime - Tvm_oto;

	Tpwe_oto = Tvm_oto + Tw0_oto + Tsw_oto;

	dst_y_pwefetch_oto = Tpwe_oto / WineTime;

	if (dst_y_pwefetch_oto < dst_y_pwefetch_equ)
		*DestinationWinesFowPwefetch = dst_y_pwefetch_oto;
	ewse
		*DestinationWinesFowPwefetch = dst_y_pwefetch_equ;

	*DestinationWinesFowPwefetch = dmw_fwoow(4.0 * (*DestinationWinesFowPwefetch + 0.125), 1)
			/ 4;

	dmw_pwint("DMW: VStawtup: %d\n", VStawtup);
	dmw_pwint("DMW: TCawc: %f\n", TCawc);
	dmw_pwint("DMW: TWait: %f\n", TWait);
	dmw_pwint("DMW: XFCWemoteSuwfaceFwipDeway: %f\n", XFCWemoteSuwfaceFwipDeway);
	dmw_pwint("DMW: WineTime: %f\n", WineTime);
	dmw_pwint("DMW: Tsetup: %f\n", Tsetup);
	dmw_pwint("DMW: Tdm: %f\n", Tdm);
	dmw_pwint("DMW: DSTYAftewScawew: %f\n", *DSTYAftewScawew);
	dmw_pwint("DMW: DSTXAftewScawew: %f\n", *DSTXAftewScawew);
	dmw_pwint("DMW: HTotaw: %d\n", HTotaw);

	*PwefetchBandwidth = 0;
	*DestinationWinesToWequestVMInVBwank = 0;
	*DestinationWinesToWequestWowInVBwank = 0;
	*VWatioPwefetchY = 0;
	*VWatioPwefetchC = 0;
	*WequiwedPwefetchPixDataBW = 0;
	if (*DestinationWinesFowPwefetch > 1) {
		*PwefetchBandwidth = (PDEAndMetaPTEBytesFwame + 2 * MetaWowByte
				+ 2 * PixewPTEBytesPewWow
				+ PwefetchSouwceWinesY * SwathWidthY * dmw_ceiw(BytePewPixewDETY, 1)
				+ PwefetchSouwceWinesC * SwathWidthY / 2
						* dmw_ceiw(BytePewPixewDETC, 2))
				/ (*DestinationWinesFowPwefetch * WineTime - *Tno_bw);
		if (GPUVMEnabwe) {
			TimeFowFetchingMetaPTE =
					dmw_max(
							*Tno_bw
									+ (doubwe) PDEAndMetaPTEBytesFwame
											/ *PwefetchBandwidth,
							dmw_max(
									UwgentExtwaWatency
											+ UwgentWatencyPixewDataOnwy
													* (PageTabweWevews
															- 1),
									WineTime / 4));
		} ewse {
			if (NumbewOfCuwsows > 0 || XFCEnabwed)
				TimeFowFetchingMetaPTE = WineTime / 4;
			ewse
				TimeFowFetchingMetaPTE = 0.0;
		}

		if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
			TimeFowFetchingWowInVBwank =
					dmw_max(
							(MetaWowByte + PixewPTEBytesPewWow)
									/ *PwefetchBandwidth,
							dmw_max(
									UwgentWatencyPixewDataOnwy,
									dmw_max(
											WineTime
													- TimeFowFetchingMetaPTE,
											WineTime
													/ 4.0)));
		} ewse {
			if (NumbewOfCuwsows > 0 || XFCEnabwed)
				TimeFowFetchingWowInVBwank = WineTime - TimeFowFetchingMetaPTE;
			ewse
				TimeFowFetchingWowInVBwank = 0.0;
		}

		*DestinationWinesToWequestVMInVBwank = dmw_fwoow(
				4.0 * (TimeFowFetchingMetaPTE / WineTime + 0.125),
				1) / 4.0;

		*DestinationWinesToWequestWowInVBwank = dmw_fwoow(
				4.0 * (TimeFowFetchingWowInVBwank / WineTime + 0.125),
				1) / 4.0;

		WinesToWequestPwefetchPixewData =
				*DestinationWinesFowPwefetch
						- ((NumbewOfCuwsows > 0 || GPUVMEnabwe
								|| DCCEnabwe) ?
								(*DestinationWinesToWequestVMInVBwank
										+ *DestinationWinesToWequestWowInVBwank) :
								0.0);

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

			*WequiwedPwefetchPixDataBW =
					DPPPewPwane
							* ((doubwe) PwefetchSouwceWinesY
									/ WinesToWequestPwefetchPixewData
									* dmw_ceiw(
											BytePewPixewDETY,
											1)
									+ (doubwe) PwefetchSouwceWinesC
											/ WinesToWequestPwefetchPixewData
											* dmw_ceiw(
													BytePewPixewDETC,
													2)
											/ 2)
							* SwathWidthY / WineTime;
		} ewse {
			MyEwwow = twue;
			*VWatioPwefetchY = 0;
			*VWatioPwefetchC = 0;
			*WequiwedPwefetchPixDataBW = 0;
		}

	} ewse {
		MyEwwow = twue;
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
		*WequiwedPwefetchPixDataBW = 0;
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
		unsigned int VMMPageSize,
		unsigned int PTEBuffewSizeInWequestsWuma,
		unsigned int PDEPwocessingBufIn64KBWeqs,
		unsigned int Pitch,
		unsigned int DCCMetaPitch,
		unsigned int *MacwoTiweWidth,
		unsigned int *MetaWowByte,
		unsigned int *PixewPTEBytesPewWow,
		boow *PTEBuffewSizeNotExceeded,
		unsigned int *dpte_wow_height,
		unsigned int *meta_wow_height)
{
	unsigned int MetaWequestHeight;
	unsigned int MetaWequestWidth;
	unsigned int MetaSuwfWidth;
	unsigned int MetaSuwfHeight;
	unsigned int MPDEBytesFwame;
	unsigned int MetaPTEBytesFwame;
	unsigned int DCCMetaSuwfaceBytes;

	unsigned int MacwoTiweSizeBytes;
	unsigned int MacwoTiweHeight;
	unsigned int DPDE0BytesFwame;
	unsigned int ExtwaDPDEBytesFwame;
	unsigned int PDEAndMetaPTEBytesFwame;

	if (DCCEnabwe == twue) {
		MetaWequestHeight = 8 * BwockHeight256Bytes;
		MetaWequestWidth = 8 * BwockWidth256Bytes;
		if (ScanDiwection == dm_howz) {
			*meta_wow_height = MetaWequestHeight;
			MetaSuwfWidth = dmw_ceiw((doubwe) SwathWidth - 1, MetaWequestWidth)
					+ MetaWequestWidth;
			*MetaWowByte = MetaSuwfWidth * MetaWequestHeight * BytePewPixew / 256.0;
		} ewse {
			*meta_wow_height = MetaWequestWidth;
			MetaSuwfHeight = dmw_ceiw((doubwe) SwathWidth - 1, MetaWequestHeight)
					+ MetaWequestHeight;
			*MetaWowByte = MetaSuwfHeight * MetaWequestWidth * BytePewPixew / 256.0;
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
			MetaPTEBytesFwame = (dmw_ceiw(
					(doubwe) (DCCMetaSuwfaceBytes - VMMPageSize)
							/ (8 * VMMPageSize),
					1) + 1) * 64;
			MPDEBytesFwame = 128 * (mode_wib->vba.GPUVMMaxPageTabweWevews - 1);
		} ewse {
			MetaPTEBytesFwame = 0;
			MPDEBytesFwame = 0;
		}
	} ewse {
		MetaPTEBytesFwame = 0;
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

	if (GPUVMEnabwe == twue && mode_wib->vba.GPUVMMaxPageTabweWevews > 1) {
		if (ScanDiwection == dm_howz) {
			DPDE0BytesFwame =
					64
							* (dmw_ceiw(
									((Pitch
											* (dmw_ceiw(
													ViewpowtHeight
															- 1,
													MacwoTiweHeight)
													+ MacwoTiweHeight)
											* BytePewPixew)
											- MacwoTiweSizeBytes)
											/ (8
													* 2097152),
									1) + 1);
		} ewse {
			DPDE0BytesFwame =
					64
							* (dmw_ceiw(
									((Pitch
											* (dmw_ceiw(
													(doubwe) SwathWidth
															- 1,
													MacwoTiweHeight)
													+ MacwoTiweHeight)
											* BytePewPixew)
											- MacwoTiweSizeBytes)
											/ (8
													* 2097152),
									1) + 1);
		}
		ExtwaDPDEBytesFwame = 128 * (mode_wib->vba.GPUVMMaxPageTabweWevews - 2);
	} ewse {
		DPDE0BytesFwame = 0;
		ExtwaDPDEBytesFwame = 0;
	}

	PDEAndMetaPTEBytesFwame = MetaPTEBytesFwame + MPDEBytesFwame + DPDE0BytesFwame
			+ ExtwaDPDEBytesFwame;

	if (GPUVMEnabwe == twue) {
		unsigned int PTEWequestSize;
		unsigned int PixewPTEWeqHeight;
		unsigned int PixewPTEWeqWidth;
		doubwe FwactionOfPTEWetuwnDwop;
		unsigned int EffectivePDEPwocessingBufIn64KBWeqs;

		if (SuwfaceTiwing == dm_sw_wineaw) {
			PixewPTEWeqHeight = 1;
			PixewPTEWeqWidth = 8.0 * VMMPageSize / BytePewPixew;
			PTEWequestSize = 64;
			FwactionOfPTEWetuwnDwop = 0;
		} ewse if (MacwoTiweSizeBytes == 4096) {
			PixewPTEWeqHeight = MacwoTiweHeight;
			PixewPTEWeqWidth = 8 * *MacwoTiweWidth;
			PTEWequestSize = 64;
			if (ScanDiwection == dm_howz)
				FwactionOfPTEWetuwnDwop = 0;
			ewse
				FwactionOfPTEWetuwnDwop = 7 / 8;
		} ewse if (VMMPageSize == 4096 && MacwoTiweSizeBytes > 4096) {
			PixewPTEWeqHeight = 16 * BwockHeight256Bytes;
			PixewPTEWeqWidth = 16 * BwockWidth256Bytes;
			PTEWequestSize = 128;
			FwactionOfPTEWetuwnDwop = 0;
		} ewse {
			PixewPTEWeqHeight = MacwoTiweHeight;
			PixewPTEWeqWidth = 8 * *MacwoTiweWidth;
			PTEWequestSize = 64;
			FwactionOfPTEWetuwnDwop = 0;
		}

		if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10)
			EffectivePDEPwocessingBufIn64KBWeqs = PDEPwocessingBufIn64KBWeqs / 2;
		ewse
			EffectivePDEPwocessingBufIn64KBWeqs = PDEPwocessingBufIn64KBWeqs;

		if (SuwfaceTiwing == dm_sw_wineaw) {
			*dpte_wow_height =
					dmw_min(
							128,
							1
									<< (unsigned int) dmw_fwoow(
											dmw_wog2(
													dmw_min(
															(doubwe) PTEBuffewSizeInWequestsWuma
																	* PixewPTEWeqWidth,
															EffectivePDEPwocessingBufIn64KBWeqs
																	* 65536.0
																	/ BytePewPixew)
															/ Pitch),
											1));
			*PixewPTEBytesPewWow = PTEWequestSize
					* (dmw_ceiw(
							(doubwe) (Pitch * *dpte_wow_height - 1)
									/ PixewPTEWeqWidth,
							1) + 1);
		} ewse if (ScanDiwection == dm_howz) {
			*dpte_wow_height = PixewPTEWeqHeight;
			*PixewPTEBytesPewWow = PTEWequestSize
					* (dmw_ceiw(((doubwe) SwathWidth - 1) / PixewPTEWeqWidth, 1)
							+ 1);
		} ewse {
			*dpte_wow_height = dmw_min(PixewPTEWeqWidth, *MacwoTiweWidth);
			*PixewPTEBytesPewWow = PTEWequestSize
					* (dmw_ceiw(
							((doubwe) SwathWidth - 1)
									/ PixewPTEWeqHeight,
							1) + 1);
		}
		if (*PixewPTEBytesPewWow * (1 - FwactionOfPTEWetuwnDwop)
				<= 64 * PTEBuffewSizeInWequestsWuma) {
			*PTEBuffewSizeNotExceeded = twue;
		} ewse {
			*PTEBuffewSizeNotExceeded = fawse;
		}
	} ewse {
		*PixewPTEBytesPewWow = 0;
		*PTEBuffewSizeNotExceeded = twue;
	}

	wetuwn PDEAndMetaPTEBytesFwame;
}

static void dmw20_DISPCWKDPPCWKDCFCWKDeepSweepPwefetchPawametewsWatewmawksAndPewfowmanceCawcuwation(
		stwuct dispway_mode_wib *mode_wib)
{
	unsigned int j, k;

	mode_wib->vba.WwitebackDISPCWK = 0.0;
	mode_wib->vba.DISPCWKWithWamping = 0;
	mode_wib->vba.DISPCWKWithoutWamping = 0;
	mode_wib->vba.GwobawDPPCWK = 0.0;

	// dmw_mw->vba.DISPCWK and dmw_mw->vba.DPPCWK Cawcuwation
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
			mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k] = dmw_min(
					mode_wib->vba.MaxDCHUBToPSCWThwoughput,
					mode_wib->vba.MaxPSCWToWBThwoughput
							* mode_wib->vba.HWatio[k]
							/ dmw_ceiw(
									mode_wib->vba.htaps[k]
											/ 6.0,
									1));
		} ewse {
			mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k] = dmw_min(
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
												/ mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k],
										1.0));

		if ((mode_wib->vba.htaps[k] > 6 || mode_wib->vba.vtaps[k] > 6)
				&& mode_wib->vba.DPPCWKUsingSingweDPPWuma
						< 2 * mode_wib->vba.PixewCwock[k]) {
			mode_wib->vba.DPPCWKUsingSingweDPPWuma = 2 * mode_wib->vba.PixewCwock[k];
		}

		if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_420_8
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_420_10)) {
			mode_wib->vba.PSCW_THWOUGHPUT_CHWOMA[k] = 0.0;
			mode_wib->vba.DPPCWKUsingSingweDPP[k] =
					mode_wib->vba.DPPCWKUsingSingweDPPWuma;
		} ewse {
			if (mode_wib->vba.HWatio[k] > 1) {
				mode_wib->vba.PSCW_THWOUGHPUT_CHWOMA[k] =
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
				mode_wib->vba.PSCW_THWOUGHPUT_CHWOMA[k] = dmw_min(
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
													/ mode_wib->vba.PSCW_THWOUGHPUT_CHWOMA[k],
											1.0));

			if ((mode_wib->vba.HTAPsChwoma[k] > 6 || mode_wib->vba.VTAPsChwoma[k] > 6)
					&& mode_wib->vba.DPPCWKUsingSingweDPPChwoma
							< 2 * mode_wib->vba.PixewCwock[k]) {
				mode_wib->vba.DPPCWKUsingSingweDPPChwoma = 2
						* mode_wib->vba.PixewCwock[k];
			}

			mode_wib->vba.DPPCWKUsingSingweDPP[k] = dmw_max(
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
			mode_wib->vba.soc.cwock_wimits[mode_wib->vba.soc.num_states].dispcwk_mhz,
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
		if (mode_wib->vba.DPPPewPwane[k] == 0) {
			mode_wib->vba.DPPCWK_cawcuwated[k] = 0;
		} ewse {
			mode_wib->vba.DPPCWK_cawcuwated[k] = mode_wib->vba.DPPCWKUsingSingweDPP[k]
					/ mode_wib->vba.DPPPewPwane[k]
					* (1 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100);
		}
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

	// Uwgent Watewmawk
	mode_wib->vba.DCCEnabwedAnyPwane = fawse;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		if (mode_wib->vba.DCCEnabwe[k])
			mode_wib->vba.DCCEnabwedAnyPwane = twue;

	mode_wib->vba.WetuwnBandwidthToDCN = dmw_min(
			mode_wib->vba.WetuwnBusWidth * mode_wib->vba.DCFCWK,
			mode_wib->vba.FabwicAndDWAMBandwidth * 1000)
			* mode_wib->vba.PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewDataOnwy / 100;

	mode_wib->vba.WetuwnBW = mode_wib->vba.WetuwnBandwidthToDCN;
	mode_wib->vba.WetuwnBW = adjust_WetuwnBW(
			mode_wib,
			mode_wib->vba.WetuwnBW,
			mode_wib->vba.DCCEnabwedAnyPwane,
			mode_wib->vba.WetuwnBandwidthToDCN);

	// Wet's do this cawcuwation again??
	mode_wib->vba.WetuwnBandwidthToDCN = dmw_min(
			mode_wib->vba.WetuwnBusWidth * mode_wib->vba.DCFCWK,
			mode_wib->vba.FabwicAndDWAMBandwidth * 1000);
	mode_wib->vba.WetuwnBW = adjust_WetuwnBW(
			mode_wib,
			mode_wib->vba.WetuwnBW,
			mode_wib->vba.DCCEnabwedAnyPwane,
			mode_wib->vba.WetuwnBandwidthToDCN);

	DTWACE("   dcfcwk_mhz         = %f", mode_wib->vba.DCFCWK);
	DTWACE("   wetuwn_bw_to_dcn   = %f", mode_wib->vba.WetuwnBandwidthToDCN);
	DTWACE("   wetuwn_bus_bw      = %f", mode_wib->vba.WetuwnBW);

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		boow MainPwaneDoesODMCombine = fawse;

		if (mode_wib->vba.SouwceScan[k] == dm_howz)
			mode_wib->vba.SwathWidthSingweDPPY[k] = mode_wib->vba.ViewpowtWidth[k];
		ewse
			mode_wib->vba.SwathWidthSingweDPPY[k] = mode_wib->vba.ViewpowtHeight[k];

		if (mode_wib->vba.ODMCombineEnabwed[k] == dm_odm_combine_mode_2to1)
			MainPwaneDoesODMCombine = twue;
		fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j)
			if (mode_wib->vba.BwendingAndTiming[k] == j
					&& mode_wib->vba.ODMCombineEnabwed[k] == dm_odm_combine_mode_2to1)
				MainPwaneDoesODMCombine = twue;

		if (MainPwaneDoesODMCombine == twue)
			mode_wib->vba.SwathWidthY[k] = dmw_min(
					(doubwe) mode_wib->vba.SwathWidthSingweDPPY[k],
					dmw_wound(
							mode_wib->vba.HActive[k] / 2.0
									* mode_wib->vba.HWatio[k]));
		ewse {
			if (mode_wib->vba.DPPPewPwane[k] == 0) {
				mode_wib->vba.SwathWidthY[k] = 0;
			} ewse {
				mode_wib->vba.SwathWidthY[k] = mode_wib->vba.SwathWidthSingweDPPY[k]
						/ mode_wib->vba.DPPPewPwane[k];
			}
		}
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_64) {
			mode_wib->vba.BytePewPixewDETY[k] = 8;
			mode_wib->vba.BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_32) {
			mode_wib->vba.BytePewPixewDETY[k] = 4;
			mode_wib->vba.BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_16) {
			mode_wib->vba.BytePewPixewDETY[k] = 2;
			mode_wib->vba.BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_444_8) {
			mode_wib->vba.BytePewPixewDETY[k] = 1;
			mode_wib->vba.BytePewPixewDETC[k] = 0;
		} ewse if (mode_wib->vba.SouwcePixewFowmat[k] == dm_420_8) {
			mode_wib->vba.BytePewPixewDETY[k] = 1;
			mode_wib->vba.BytePewPixewDETC[k] = 2;
		} ewse { // dm_420_10
			mode_wib->vba.BytePewPixewDETY[k] = 4.0 / 3.0;
			mode_wib->vba.BytePewPixewDETC[k] = 8.0 / 3.0;
		}
	}

	mode_wib->vba.TotawDataWeadBandwidth = 0.0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.WeadBandwidthPwaneWuma[k] = mode_wib->vba.SwathWidthSingweDPPY[k]
				* dmw_ceiw(mode_wib->vba.BytePewPixewDETY[k], 1)
				/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
				* mode_wib->vba.VWatio[k];
		mode_wib->vba.WeadBandwidthPwaneChwoma[k] = mode_wib->vba.SwathWidthSingweDPPY[k]
				/ 2 * dmw_ceiw(mode_wib->vba.BytePewPixewDETC[k], 2)
				/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
				* mode_wib->vba.VWatio[k] / 2;
		DTWACE(
				"   wead_bw[%i] = %fBps",
				k,
				mode_wib->vba.WeadBandwidthPwaneWuma[k]
						+ mode_wib->vba.WeadBandwidthPwaneChwoma[k]);
		mode_wib->vba.TotawDataWeadBandwidth += mode_wib->vba.WeadBandwidthPwaneWuma[k]
				+ mode_wib->vba.WeadBandwidthPwaneChwoma[k];
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

	mode_wib->vba.UwgentWoundTwipAndOutOfOwdewWatency =
			(mode_wib->vba.WoundTwipPingWatencyCycwes + 32) / mode_wib->vba.DCFCWK
					+ mode_wib->vba.UwgentOutOfOwdewWetuwnPewChannewPixewDataOnwy
							* mode_wib->vba.NumbewOfChannews
							/ mode_wib->vba.WetuwnBW;

	mode_wib->vba.WastPixewOfWineExtwaWatewmawk = 0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		doubwe DataFabwicWineDewivewyTimeWuma, DataFabwicWineDewivewyTimeChwoma;

		if (mode_wib->vba.VWatio[k] <= 1.0)
			mode_wib->vba.DispwayPipeWineDewivewyTimeWuma[k] =
					(doubwe) mode_wib->vba.SwathWidthY[k]
							* mode_wib->vba.DPPPewPwane[k]
							/ mode_wib->vba.HWatio[k]
							/ mode_wib->vba.PixewCwock[k];
		ewse
			mode_wib->vba.DispwayPipeWineDewivewyTimeWuma[k] =
					(doubwe) mode_wib->vba.SwathWidthY[k]
							/ mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k]
							/ mode_wib->vba.DPPCWK[k];

		DataFabwicWineDewivewyTimeWuma = mode_wib->vba.SwathWidthSingweDPPY[k]
				* mode_wib->vba.SwathHeightY[k]
				* dmw_ceiw(mode_wib->vba.BytePewPixewDETY[k], 1)
				/ (mode_wib->vba.WetuwnBW * mode_wib->vba.WeadBandwidthPwaneWuma[k]
						/ mode_wib->vba.TotawDataWeadBandwidth);
		mode_wib->vba.WastPixewOfWineExtwaWatewmawk = dmw_max(
				mode_wib->vba.WastPixewOfWineExtwaWatewmawk,
				DataFabwicWineDewivewyTimeWuma
						- mode_wib->vba.DispwayPipeWineDewivewyTimeWuma[k]);

		if (mode_wib->vba.BytePewPixewDETC[k] == 0)
			mode_wib->vba.DispwayPipeWineDewivewyTimeChwoma[k] = 0.0;
		ewse if (mode_wib->vba.VWatio[k] / 2.0 <= 1.0)
			mode_wib->vba.DispwayPipeWineDewivewyTimeChwoma[k] =
					mode_wib->vba.SwathWidthY[k] / 2.0
							* mode_wib->vba.DPPPewPwane[k]
							/ (mode_wib->vba.HWatio[k] / 2.0)
							/ mode_wib->vba.PixewCwock[k];
		ewse
			mode_wib->vba.DispwayPipeWineDewivewyTimeChwoma[k] =
					mode_wib->vba.SwathWidthY[k] / 2.0
							/ mode_wib->vba.PSCW_THWOUGHPUT_CHWOMA[k]
							/ mode_wib->vba.DPPCWK[k];

		DataFabwicWineDewivewyTimeChwoma = mode_wib->vba.SwathWidthSingweDPPY[k] / 2.0
				* mode_wib->vba.SwathHeightC[k]
				* dmw_ceiw(mode_wib->vba.BytePewPixewDETC[k], 2)
				/ (mode_wib->vba.WetuwnBW
						* mode_wib->vba.WeadBandwidthPwaneChwoma[k]
						/ mode_wib->vba.TotawDataWeadBandwidth);
		mode_wib->vba.WastPixewOfWineExtwaWatewmawk =
				dmw_max(
						mode_wib->vba.WastPixewOfWineExtwaWatewmawk,
						DataFabwicWineDewivewyTimeChwoma
								- mode_wib->vba.DispwayPipeWineDewivewyTimeChwoma[k]);
	}

	mode_wib->vba.UwgentExtwaWatency = mode_wib->vba.UwgentWoundTwipAndOutOfOwdewWatency
			+ (mode_wib->vba.TotawActiveDPP * mode_wib->vba.PixewChunkSizeInKByte
					+ mode_wib->vba.TotawDCCActiveDPP
							* mode_wib->vba.MetaChunkSize) * 1024.0
					/ mode_wib->vba.WetuwnBW;

	if (mode_wib->vba.GPUVMEnabwe)
		mode_wib->vba.UwgentExtwaWatency += mode_wib->vba.TotawActiveDPP
				* mode_wib->vba.PTEGwoupSize / mode_wib->vba.WetuwnBW;

	mode_wib->vba.UwgentWatewmawk = mode_wib->vba.UwgentWatencyPixewDataOnwy
			+ mode_wib->vba.WastPixewOfWineExtwaWatewmawk
			+ mode_wib->vba.UwgentExtwaWatency;

	DTWACE("   uwgent_extwa_watency = %fus", mode_wib->vba.UwgentExtwaWatency);
	DTWACE("   wm_uwgent = %fus", mode_wib->vba.UwgentWatewmawk);

	mode_wib->vba.UwgentWatency = mode_wib->vba.UwgentWatencyPixewDataOnwy;

	mode_wib->vba.TotawActiveWwiteback = 0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.WwitebackEnabwe[k])
			mode_wib->vba.TotawActiveWwiteback = mode_wib->vba.TotawActiveWwiteback + mode_wib->vba.ActiveWwitebacksPewPwane[k];
	}

	if (mode_wib->vba.TotawActiveWwiteback <= 1)
		mode_wib->vba.WwitebackUwgentWatewmawk = mode_wib->vba.WwitebackWatency;
	ewse
		mode_wib->vba.WwitebackUwgentWatewmawk = mode_wib->vba.WwitebackWatency
				+ mode_wib->vba.WwitebackChunkSize * 1024.0 / 32
						/ mode_wib->vba.SOCCWK;

	DTWACE("   wm_wb_uwgent = %fus", mode_wib->vba.WwitebackUwgentWatewmawk);

	// NB P-State/DWAM Cwock Change Watewmawk
	mode_wib->vba.DWAMCwockChangeWatewmawk = mode_wib->vba.DWAMCwockChangeWatency
			+ mode_wib->vba.UwgentWatewmawk;

	DTWACE("   wm_pstate_change = %fus", mode_wib->vba.DWAMCwockChangeWatewmawk);

	DTWACE("   cawcuwating wb pstate watewmawk");
	DTWACE("      totaw wb outputs %d", mode_wib->vba.TotawActiveWwiteback);
	DTWACE("      soccwk fwequency %f Mhz", mode_wib->vba.SOCCWK);

	if (mode_wib->vba.TotawActiveWwiteback <= 1)
		mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk =
				mode_wib->vba.DWAMCwockChangeWatency
						+ mode_wib->vba.WwitebackWatency;
	ewse
		mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk =
				mode_wib->vba.DWAMCwockChangeWatency
						+ mode_wib->vba.WwitebackWatency
						+ mode_wib->vba.WwitebackChunkSize * 1024.0 / 32
								/ mode_wib->vba.SOCCWK;

	DTWACE("   wm_wb_pstate %fus", mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk);

	// Stuttew Efficiency
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.WinesInDETY[k] = mode_wib->vba.DETBuffewSizeY[k]
				/ mode_wib->vba.BytePewPixewDETY[k] / mode_wib->vba.SwathWidthY[k];
		mode_wib->vba.WinesInDETYWoundedDownToSwath[k] = dmw_fwoow(
				mode_wib->vba.WinesInDETY[k],
				mode_wib->vba.SwathHeightY[k]);
		mode_wib->vba.FuwwDETBuffewingTimeY[k] =
				mode_wib->vba.WinesInDETYWoundedDownToSwath[k]
						* (mode_wib->vba.HTotaw[k]
								/ mode_wib->vba.PixewCwock[k])
						/ mode_wib->vba.VWatio[k];
		if (mode_wib->vba.BytePewPixewDETC[k] > 0) {
			mode_wib->vba.WinesInDETC[k] = mode_wib->vba.DETBuffewSizeC[k]
					/ mode_wib->vba.BytePewPixewDETC[k]
					/ (mode_wib->vba.SwathWidthY[k] / 2);
			mode_wib->vba.WinesInDETCWoundedDownToSwath[k] = dmw_fwoow(
					mode_wib->vba.WinesInDETC[k],
					mode_wib->vba.SwathHeightC[k]);
			mode_wib->vba.FuwwDETBuffewingTimeC[k] =
					mode_wib->vba.WinesInDETCWoundedDownToSwath[k]
							* (mode_wib->vba.HTotaw[k]
									/ mode_wib->vba.PixewCwock[k])
							/ (mode_wib->vba.VWatio[k] / 2);
		} ewse {
			mode_wib->vba.WinesInDETC[k] = 0;
			mode_wib->vba.WinesInDETCWoundedDownToSwath[k] = 0;
			mode_wib->vba.FuwwDETBuffewingTimeC[k] = 999999;
		}
	}

	mode_wib->vba.MinFuwwDETBuffewingTime = 999999.0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.FuwwDETBuffewingTimeY[k]
				< mode_wib->vba.MinFuwwDETBuffewingTime) {
			mode_wib->vba.MinFuwwDETBuffewingTime =
					mode_wib->vba.FuwwDETBuffewingTimeY[k];
			mode_wib->vba.FwameTimeFowMinFuwwDETBuffewingTime =
					(doubwe) mode_wib->vba.VTotaw[k] * mode_wib->vba.HTotaw[k]
							/ mode_wib->vba.PixewCwock[k];
		}
		if (mode_wib->vba.FuwwDETBuffewingTimeC[k]
				< mode_wib->vba.MinFuwwDETBuffewingTime) {
			mode_wib->vba.MinFuwwDETBuffewingTime =
					mode_wib->vba.FuwwDETBuffewingTimeC[k];
			mode_wib->vba.FwameTimeFowMinFuwwDETBuffewingTime =
					(doubwe) mode_wib->vba.VTotaw[k] * mode_wib->vba.HTotaw[k]
							/ mode_wib->vba.PixewCwock[k];
		}
	}

	mode_wib->vba.AvewageWeadBandwidthGBytePewSecond = 0.0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.DCCEnabwe[k]) {
			mode_wib->vba.AvewageWeadBandwidthGBytePewSecond =
					mode_wib->vba.AvewageWeadBandwidthGBytePewSecond
							+ mode_wib->vba.WeadBandwidthPwaneWuma[k]
									/ mode_wib->vba.DCCWate[k]
									/ 1000
							+ mode_wib->vba.WeadBandwidthPwaneChwoma[k]
									/ mode_wib->vba.DCCWate[k]
									/ 1000;
		} ewse {
			mode_wib->vba.AvewageWeadBandwidthGBytePewSecond =
					mode_wib->vba.AvewageWeadBandwidthGBytePewSecond
							+ mode_wib->vba.WeadBandwidthPwaneWuma[k]
									/ 1000
							+ mode_wib->vba.WeadBandwidthPwaneChwoma[k]
									/ 1000;
		}
		if (mode_wib->vba.DCCEnabwe[k]) {
			mode_wib->vba.AvewageWeadBandwidthGBytePewSecond =
					mode_wib->vba.AvewageWeadBandwidthGBytePewSecond
							+ mode_wib->vba.WeadBandwidthPwaneWuma[k]
									/ 1000 / 256
							+ mode_wib->vba.WeadBandwidthPwaneChwoma[k]
									/ 1000 / 256;
		}
		if (mode_wib->vba.GPUVMEnabwe) {
			mode_wib->vba.AvewageWeadBandwidthGBytePewSecond =
					mode_wib->vba.AvewageWeadBandwidthGBytePewSecond
							+ mode_wib->vba.WeadBandwidthPwaneWuma[k]
									/ 1000 / 512
							+ mode_wib->vba.WeadBandwidthPwaneChwoma[k]
									/ 1000 / 512;
		}
	}

	mode_wib->vba.PawtOfBuwstThatFitsInWOB =
			dmw_min(
					mode_wib->vba.MinFuwwDETBuffewingTime
							* mode_wib->vba.TotawDataWeadBandwidth,
					mode_wib->vba.WOBBuffewSizeInKByte * 1024
							* mode_wib->vba.TotawDataWeadBandwidth
							/ (mode_wib->vba.AvewageWeadBandwidthGBytePewSecond
									* 1000));
	mode_wib->vba.StuttewBuwstTime = mode_wib->vba.PawtOfBuwstThatFitsInWOB
			* (mode_wib->vba.AvewageWeadBandwidthGBytePewSecond * 1000)
			/ mode_wib->vba.TotawDataWeadBandwidth / mode_wib->vba.WetuwnBW
			+ (mode_wib->vba.MinFuwwDETBuffewingTime
					* mode_wib->vba.TotawDataWeadBandwidth
					- mode_wib->vba.PawtOfBuwstThatFitsInWOB)
					/ (mode_wib->vba.DCFCWK * 64);
	if (mode_wib->vba.TotawActiveWwiteback == 0) {
		mode_wib->vba.StuttewEfficiencyNotIncwudingVBwank = (1
				- (mode_wib->vba.SWExitTime + mode_wib->vba.StuttewBuwstTime)
						/ mode_wib->vba.MinFuwwDETBuffewingTime) * 100;
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

	// dmw_mw->vba.DCFCWK Deep Sweep
	mode_wib->vba.DCFCWKDeepSweep = 8.0;

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; k++) {
		if (mode_wib->vba.BytePewPixewDETC[k] > 0) {
			mode_wib->vba.DCFCWKDeepSweepPewPwane[k] =
					dmw_max(
							1.1 * mode_wib->vba.SwathWidthY[k]
									* dmw_ceiw(
											mode_wib->vba.BytePewPixewDETY[k],
											1) / 32
									/ mode_wib->vba.DispwayPipeWineDewivewyTimeWuma[k],
							1.1 * mode_wib->vba.SwathWidthY[k] / 2.0
									* dmw_ceiw(
											mode_wib->vba.BytePewPixewDETC[k],
											2) / 32
									/ mode_wib->vba.DispwayPipeWineDewivewyTimeChwoma[k]);
		} ewse
			mode_wib->vba.DCFCWKDeepSweepPewPwane[k] = 1.1 * mode_wib->vba.SwathWidthY[k]
					* dmw_ceiw(mode_wib->vba.BytePewPixewDETY[k], 1) / 64.0
					/ mode_wib->vba.DispwayPipeWineDewivewyTimeWuma[k];
		mode_wib->vba.DCFCWKDeepSweepPewPwane[k] = dmw_max(
				mode_wib->vba.DCFCWKDeepSweepPewPwane[k],
				mode_wib->vba.PixewCwock[k] / 16.0);
		mode_wib->vba.DCFCWKDeepSweep = dmw_max(
				mode_wib->vba.DCFCWKDeepSweep,
				mode_wib->vba.DCFCWKDeepSweepPewPwane[k]);

		DTWACE(
				"   dcfcwk_deepsweep_pew_pwane[%i] = %fMHz",
				k,
				mode_wib->vba.DCFCWKDeepSweepPewPwane[k]);
	}

	DTWACE("   dcfcwk_deepsweep_mhz = %fMHz", mode_wib->vba.DCFCWKDeepSweep);

	// Stuttew Watewmawk
	mode_wib->vba.StuttewExitWatewmawk = mode_wib->vba.SWExitTime
			+ mode_wib->vba.WastPixewOfWineExtwaWatewmawk
			+ mode_wib->vba.UwgentExtwaWatency + 10 / mode_wib->vba.DCFCWKDeepSweep;
	mode_wib->vba.StuttewEntewPwusExitWatewmawk = mode_wib->vba.SWEntewPwusExitTime
			+ mode_wib->vba.WastPixewOfWineExtwaWatewmawk
			+ mode_wib->vba.UwgentExtwaWatency;

	DTWACE("   wm_cstate_exit       = %fus", mode_wib->vba.StuttewExitWatewmawk);
	DTWACE("   wm_cstate_entew_exit = %fus", mode_wib->vba.StuttewEntewPwusExitWatewmawk);

	// Uwgent Watency Suppowted
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.EffectiveDETPwusWBWinesWuma =
				dmw_fwoow(
						mode_wib->vba.WinesInDETY[k]
								+ dmw_min(
										mode_wib->vba.WinesInDETY[k]
												* mode_wib->vba.DPPCWK[k]
												* mode_wib->vba.BytePewPixewDETY[k]
												* mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k]
												/ (mode_wib->vba.WetuwnBW
														/ mode_wib->vba.DPPPewPwane[k]),
										(doubwe) mode_wib->vba.EffectiveWBWatencyHidingSouwceWinesWuma),
						mode_wib->vba.SwathHeightY[k]);

		mode_wib->vba.UwgentWatencySuppowtUsWuma = mode_wib->vba.EffectiveDETPwusWBWinesWuma
				* (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
				/ mode_wib->vba.VWatio[k]
				- mode_wib->vba.EffectiveDETPwusWBWinesWuma
						* mode_wib->vba.SwathWidthY[k]
						* mode_wib->vba.BytePewPixewDETY[k]
						/ (mode_wib->vba.WetuwnBW
								/ mode_wib->vba.DPPPewPwane[k]);

		if (mode_wib->vba.BytePewPixewDETC[k] > 0) {
			mode_wib->vba.EffectiveDETPwusWBWinesChwoma =
					dmw_fwoow(
							mode_wib->vba.WinesInDETC[k]
									+ dmw_min(
											mode_wib->vba.WinesInDETC[k]
													* mode_wib->vba.DPPCWK[k]
													* mode_wib->vba.BytePewPixewDETC[k]
													* mode_wib->vba.PSCW_THWOUGHPUT_CHWOMA[k]
													/ (mode_wib->vba.WetuwnBW
															/ mode_wib->vba.DPPPewPwane[k]),
											(doubwe) mode_wib->vba.EffectiveWBWatencyHidingSouwceWinesChwoma),
							mode_wib->vba.SwathHeightC[k]);
			mode_wib->vba.UwgentWatencySuppowtUsChwoma =
					mode_wib->vba.EffectiveDETPwusWBWinesChwoma
							* (mode_wib->vba.HTotaw[k]
									/ mode_wib->vba.PixewCwock[k])
							/ (mode_wib->vba.VWatio[k] / 2)
							- mode_wib->vba.EffectiveDETPwusWBWinesChwoma
									* (mode_wib->vba.SwathWidthY[k]
											/ 2)
									* mode_wib->vba.BytePewPixewDETC[k]
									/ (mode_wib->vba.WetuwnBW
											/ mode_wib->vba.DPPPewPwane[k]);
			mode_wib->vba.UwgentWatencySuppowtUs[k] = dmw_min(
					mode_wib->vba.UwgentWatencySuppowtUsWuma,
					mode_wib->vba.UwgentWatencySuppowtUsChwoma);
		} ewse {
			mode_wib->vba.UwgentWatencySuppowtUs[k] =
					mode_wib->vba.UwgentWatencySuppowtUsWuma;
		}
	}

	mode_wib->vba.MinUwgentWatencySuppowtUs = 999999;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.MinUwgentWatencySuppowtUs = dmw_min(
				mode_wib->vba.MinUwgentWatencySuppowtUs,
				mode_wib->vba.UwgentWatencySuppowtUs[k]);
	}

	// Non-Uwgent Watency Towewance
	mode_wib->vba.NonUwgentWatencyTowewance = mode_wib->vba.MinUwgentWatencySuppowtUs
			- mode_wib->vba.UwgentWatewmawk;

	// DSCCWK
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if ((mode_wib->vba.BwendingAndTiming[k] != k) || !mode_wib->vba.DSCEnabwed[k]) {
			mode_wib->vba.DSCCWK_cawcuwated[k] = 0.0;
		} ewse {
			if (mode_wib->vba.OutputFowmat[k] == dm_420
					|| mode_wib->vba.OutputFowmat[k] == dm_n422)
				mode_wib->vba.DSCFowmatFactow = 2;
			ewse
				mode_wib->vba.DSCFowmatFactow = 1;
			if (mode_wib->vba.ODMCombineEnabwed[k])
				mode_wib->vba.DSCCWK_cawcuwated[k] =
						mode_wib->vba.PixewCwockBackEnd[k] / 6
								/ mode_wib->vba.DSCFowmatFactow
								/ (1
										- mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading
												/ 100);
			ewse
				mode_wib->vba.DSCCWK_cawcuwated[k] =
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
				mode_wib->vba.DSCDeway[k] =
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
				mode_wib->vba.DSCDeway[k] =
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
			mode_wib->vba.DSCDeway[k] = mode_wib->vba.DSCDeway[k]
					* mode_wib->vba.PixewCwock[k]
					/ mode_wib->vba.PixewCwockBackEnd[k];
		} ewse {
			mode_wib->vba.DSCDeway[k] = 0;
		}
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j) // NumbewOfPwanes
			if (j != k && mode_wib->vba.BwendingAndTiming[k] == j
					&& mode_wib->vba.DSCEnabwed[j])
				mode_wib->vba.DSCDeway[k] = mode_wib->vba.DSCDeway[j];

	// Pwefetch
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		unsigned int PDEAndMetaPTEBytesFwameY;
		unsigned int PixewPTEBytesPewWowY;
		unsigned int MetaWowByteY;
		unsigned int MetaWowByteC;
		unsigned int PDEAndMetaPTEBytesFwameC;
		unsigned int PixewPTEBytesPewWowC;

		Cawcuwate256BBwockSizes(
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.SuwfaceTiwing[k],
				dmw_ceiw(mode_wib->vba.BytePewPixewDETY[k], 1),
				dmw_ceiw(mode_wib->vba.BytePewPixewDETC[k], 2),
				&mode_wib->vba.BwockHeight256BytesY[k],
				&mode_wib->vba.BwockHeight256BytesC[k],
				&mode_wib->vba.BwockWidth256BytesY[k],
				&mode_wib->vba.BwockWidth256BytesC[k]);
		PDEAndMetaPTEBytesFwameY = CawcuwateVMAndWowBytes(
				mode_wib,
				mode_wib->vba.DCCEnabwe[k],
				mode_wib->vba.BwockHeight256BytesY[k],
				mode_wib->vba.BwockWidth256BytesY[k],
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.SuwfaceTiwing[k],
				dmw_ceiw(mode_wib->vba.BytePewPixewDETY[k], 1),
				mode_wib->vba.SouwceScan[k],
				mode_wib->vba.ViewpowtWidth[k],
				mode_wib->vba.ViewpowtHeight[k],
				mode_wib->vba.SwathWidthY[k],
				mode_wib->vba.GPUVMEnabwe,
				mode_wib->vba.VMMPageSize,
				mode_wib->vba.PTEBuffewSizeInWequestsWuma,
				mode_wib->vba.PDEPwocessingBufIn64KBWeqs,
				mode_wib->vba.PitchY[k],
				mode_wib->vba.DCCMetaPitchY[k],
				&mode_wib->vba.MacwoTiweWidthY[k],
				&MetaWowByteY,
				&PixewPTEBytesPewWowY,
				&mode_wib->vba.PTEBuffewSizeNotExceeded[mode_wib->vba.VowtageWevew][0],
				&mode_wib->vba.dpte_wow_height[k],
				&mode_wib->vba.meta_wow_height[k]);
		mode_wib->vba.PwefetchSouwceWinesY[k] = CawcuwatePwefetchSouwceWines(
				mode_wib,
				mode_wib->vba.VWatio[k],
				mode_wib->vba.vtaps[k],
				mode_wib->vba.Intewwace[k],
				mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
				mode_wib->vba.SwathHeightY[k],
				mode_wib->vba.ViewpowtYStawtY[k],
				&mode_wib->vba.VInitPweFiwwY[k],
				&mode_wib->vba.MaxNumSwathY[k]);

		if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
				&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_8)) {
			PDEAndMetaPTEBytesFwameC =
					CawcuwateVMAndWowBytes(
							mode_wib,
							mode_wib->vba.DCCEnabwe[k],
							mode_wib->vba.BwockHeight256BytesC[k],
							mode_wib->vba.BwockWidth256BytesC[k],
							mode_wib->vba.SouwcePixewFowmat[k],
							mode_wib->vba.SuwfaceTiwing[k],
							dmw_ceiw(
									mode_wib->vba.BytePewPixewDETC[k],
									2),
							mode_wib->vba.SouwceScan[k],
							mode_wib->vba.ViewpowtWidth[k] / 2,
							mode_wib->vba.ViewpowtHeight[k] / 2,
							mode_wib->vba.SwathWidthY[k] / 2,
							mode_wib->vba.GPUVMEnabwe,
							mode_wib->vba.VMMPageSize,
							mode_wib->vba.PTEBuffewSizeInWequestsWuma,
							mode_wib->vba.PDEPwocessingBufIn64KBWeqs,
							mode_wib->vba.PitchC[k],
							0,
							&mode_wib->vba.MacwoTiweWidthC[k],
							&MetaWowByteC,
							&PixewPTEBytesPewWowC,
							&mode_wib->vba.PTEBuffewSizeNotExceeded[mode_wib->vba.VowtageWevew][0],
							&mode_wib->vba.dpte_wow_height_chwoma[k],
							&mode_wib->vba.meta_wow_height_chwoma[k]);
			mode_wib->vba.PwefetchSouwceWinesC[k] = CawcuwatePwefetchSouwceWines(
					mode_wib,
					mode_wib->vba.VWatio[k] / 2,
					mode_wib->vba.VTAPsChwoma[k],
					mode_wib->vba.Intewwace[k],
					mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
					mode_wib->vba.SwathHeightC[k],
					mode_wib->vba.ViewpowtYStawtC[k],
					&mode_wib->vba.VInitPweFiwwC[k],
					&mode_wib->vba.MaxNumSwathC[k]);
		} ewse {
			PixewPTEBytesPewWowC = 0;
			PDEAndMetaPTEBytesFwameC = 0;
			MetaWowByteC = 0;
			mode_wib->vba.MaxNumSwathC[k] = 0;
			mode_wib->vba.PwefetchSouwceWinesC[k] = 0;
		}

		mode_wib->vba.PixewPTEBytesPewWow[k] = PixewPTEBytesPewWowY + PixewPTEBytesPewWowC;
		mode_wib->vba.PDEAndMetaPTEBytesFwame[k] = PDEAndMetaPTEBytesFwameY
				+ PDEAndMetaPTEBytesFwameC;
		mode_wib->vba.MetaWowByte[k] = MetaWowByteY + MetaWowByteC;

		CawcuwateActiveWowBandwidth(
				mode_wib->vba.GPUVMEnabwe,
				mode_wib->vba.SouwcePixewFowmat[k],
				mode_wib->vba.VWatio[k],
				mode_wib->vba.DCCEnabwe[k],
				mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
				MetaWowByteY,
				MetaWowByteC,
				mode_wib->vba.meta_wow_height[k],
				mode_wib->vba.meta_wow_height_chwoma[k],
				PixewPTEBytesPewWowY,
				PixewPTEBytesPewWowC,
				mode_wib->vba.dpte_wow_height[k],
				mode_wib->vba.dpte_wow_height_chwoma[k],
				&mode_wib->vba.meta_wow_bw[k],
				&mode_wib->vba.dpte_wow_bw[k],
				&mode_wib->vba.quaw_wow_bw[k]);
	}

	mode_wib->vba.TCawc = 24.0 / mode_wib->vba.DCFCWKDeepSweep;

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.BwendingAndTiming[k] == k) {
			if (mode_wib->vba.WwitebackEnabwe[k] == twue) {
				mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][k] =
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
				mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][k] = 0;
			fow (j = 0; j < mode_wib->vba.NumbewOfActivePwanes; ++j) {
				if (mode_wib->vba.BwendingAndTiming[j] == k
						&& mode_wib->vba.WwitebackEnabwe[j] == twue) {
					mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][k] =
							dmw_max(
									mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][k],
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
				mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][k] =
						mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][j];

	mode_wib->vba.VStawtupWines = 13;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.MaxVStawtupWines[k] =
				mode_wib->vba.VTotaw[k] - mode_wib->vba.VActive[k]
						- dmw_max(
								1.0,
								dmw_ceiw(
										mode_wib->vba.WwitebackDeway[mode_wib->vba.VowtageWevew][k]
												/ (mode_wib->vba.HTotaw[k]
														/ mode_wib->vba.PixewCwock[k]),
										1));
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k)
		mode_wib->vba.MaximumMaxVStawtupWines = dmw_max(
				mode_wib->vba.MaximumMaxVStawtupWines,
				mode_wib->vba.MaxVStawtupWines[k]);

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.cuwsow_bw[k] = 0.0;
		fow (j = 0; j < mode_wib->vba.NumbewOfCuwsows[k]; ++j)
			mode_wib->vba.cuwsow_bw[k] += mode_wib->vba.CuwsowWidth[k][j]
					* mode_wib->vba.CuwsowBPP[k][j] / 8.0
					/ (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
					* mode_wib->vba.VWatio[k];
	}

	do {
		doubwe MaxTotawWDBandwidth = 0;
		boow DestinationWineTimesFowPwefetchWessThan2 = fawse;
		boow VWatioPwefetchMoweThan4 = fawse;
		boow pwefetch_vm_bw_vawid = twue;
		boow pwefetch_wow_bw_vawid = twue;
		doubwe TWait = CawcuwateTWait(
				mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb],
				mode_wib->vba.DWAMCwockChangeWatency,
				mode_wib->vba.UwgentWatencyPixewDataOnwy,
				mode_wib->vba.SWEntewPwusExitTime);

		fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
			if (mode_wib->vba.XFCEnabwed[k] == twue) {
				mode_wib->vba.XFCWemoteSuwfaceFwipDeway =
						CawcuwateWemoteSuwfaceFwipDeway(
								mode_wib,
								mode_wib->vba.VWatio[k],
								mode_wib->vba.SwathWidthY[k],
								dmw_ceiw(
										mode_wib->vba.BytePewPixewDETY[k],
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
			mode_wib->vba.EwwowWesuwt[k] =
					CawcuwatePwefetchScheduwe(
							mode_wib,
							mode_wib->vba.DPPCWK[k],
							mode_wib->vba.DISPCWK,
							mode_wib->vba.PixewCwock[k],
							mode_wib->vba.DCFCWKDeepSweep,
							mode_wib->vba.DSCDeway[k],
							mode_wib->vba.DPPPewPwane[k],
							mode_wib->vba.ScawewEnabwed[k],
							mode_wib->vba.NumbewOfCuwsows[k],
							mode_wib->vba.DPPCWKDewaySubtotaw,
							mode_wib->vba.DPPCWKDewaySCW,
							mode_wib->vba.DPPCWKDewaySCWWBOnwy,
							mode_wib->vba.DPPCWKDewayCNVCFowmatew,
							mode_wib->vba.DPPCWKDewayCNVCCuwsow,
							mode_wib->vba.DISPCWKDewaySubtotaw,
							(unsigned int) (mode_wib->vba.SwathWidthY[k]
									/ mode_wib->vba.HWatio[k]),
							mode_wib->vba.OutputFowmat[k],
							mode_wib->vba.VTotaw[k]
									- mode_wib->vba.VActive[k],
							mode_wib->vba.HTotaw[k],
							mode_wib->vba.MaxIntewDCNTiweWepeatews,
							dmw_min(
									mode_wib->vba.VStawtupWines,
									mode_wib->vba.MaxVStawtupWines[k]),
							mode_wib->vba.GPUVMMaxPageTabweWevews,
							mode_wib->vba.GPUVMEnabwe,
							mode_wib->vba.DynamicMetadataEnabwe[k],
							mode_wib->vba.DynamicMetadataWinesBefoweActiveWequiwed[k],
							mode_wib->vba.DynamicMetadataTwansmittedBytes[k],
							mode_wib->vba.DCCEnabwe[k],
							mode_wib->vba.UwgentWatencyPixewDataOnwy,
							mode_wib->vba.UwgentExtwaWatency,
							mode_wib->vba.TCawc,
							mode_wib->vba.PDEAndMetaPTEBytesFwame[k],
							mode_wib->vba.MetaWowByte[k],
							mode_wib->vba.PixewPTEBytesPewWow[k],
							mode_wib->vba.PwefetchSouwceWinesY[k],
							mode_wib->vba.SwathWidthY[k],
							mode_wib->vba.BytePewPixewDETY[k],
							mode_wib->vba.VInitPweFiwwY[k],
							mode_wib->vba.MaxNumSwathY[k],
							mode_wib->vba.PwefetchSouwceWinesC[k],
							mode_wib->vba.BytePewPixewDETC[k],
							mode_wib->vba.VInitPweFiwwC[k],
							mode_wib->vba.MaxNumSwathC[k],
							mode_wib->vba.SwathHeightY[k],
							mode_wib->vba.SwathHeightC[k],
							TWait,
							mode_wib->vba.XFCEnabwed[k],
							mode_wib->vba.XFCWemoteSuwfaceFwipDeway,
							mode_wib->vba.Intewwace[k],
							mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
							&mode_wib->vba.DSTXAftewScawew[k],
							&mode_wib->vba.DSTYAftewScawew[k],
							&mode_wib->vba.DestinationWinesFowPwefetch[k],
							&mode_wib->vba.PwefetchBandwidth[k],
							&mode_wib->vba.DestinationWinesToWequestVMInVBwank[k],
							&mode_wib->vba.DestinationWinesToWequestWowInVBwank[k],
							&mode_wib->vba.VWatioPwefetchY[k],
							&mode_wib->vba.VWatioPwefetchC[k],
							&mode_wib->vba.WequiwedPwefetchPixDataBWWuma[k],
							&mode_wib->vba.VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
							&mode_wib->vba.Tno_bw[k],
							&mode_wib->vba.VUpdateOffsetPix[k],
							&mode_wib->vba.VUpdateWidthPix[k],
							&mode_wib->vba.VWeadyOffsetPix[k]);
			if (mode_wib->vba.BwendingAndTiming[k] == k) {
				mode_wib->vba.VStawtup[k] = dmw_min(
						mode_wib->vba.VStawtupWines,
						mode_wib->vba.MaxVStawtupWines[k]);
				if (mode_wib->vba.VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata
						!= 0) {
					mode_wib->vba.VStawtup[k] =
							mode_wib->vba.VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata;
				}
			} ewse {
				mode_wib->vba.VStawtup[k] =
						dmw_min(
								mode_wib->vba.VStawtupWines,
								mode_wib->vba.MaxVStawtupWines[mode_wib->vba.BwendingAndTiming[k]]);
			}
		}

		fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {

			if (mode_wib->vba.PDEAndMetaPTEBytesFwame[k] == 0)
				mode_wib->vba.pwefetch_vm_bw[k] = 0;
			ewse if (mode_wib->vba.DestinationWinesToWequestVMInVBwank[k] > 0) {
				mode_wib->vba.pwefetch_vm_bw[k] =
						(doubwe) mode_wib->vba.PDEAndMetaPTEBytesFwame[k]
								/ (mode_wib->vba.DestinationWinesToWequestVMInVBwank[k]
										* mode_wib->vba.HTotaw[k]
										/ mode_wib->vba.PixewCwock[k]);
			} ewse {
				mode_wib->vba.pwefetch_vm_bw[k] = 0;
				pwefetch_vm_bw_vawid = fawse;
			}
			if (mode_wib->vba.MetaWowByte[k] + mode_wib->vba.PixewPTEBytesPewWow[k]
					== 0)
				mode_wib->vba.pwefetch_wow_bw[k] = 0;
			ewse if (mode_wib->vba.DestinationWinesToWequestWowInVBwank[k] > 0) {
				mode_wib->vba.pwefetch_wow_bw[k] =
						(doubwe) (mode_wib->vba.MetaWowByte[k]
								+ mode_wib->vba.PixewPTEBytesPewWow[k])
								/ (mode_wib->vba.DestinationWinesToWequestWowInVBwank[k]
										* mode_wib->vba.HTotaw[k]
										/ mode_wib->vba.PixewCwock[k]);
			} ewse {
				mode_wib->vba.pwefetch_wow_bw[k] = 0;
				pwefetch_wow_bw_vawid = fawse;
			}

			MaxTotawWDBandwidth =
					MaxTotawWDBandwidth + mode_wib->vba.cuwsow_bw[k]
							+ dmw_max(
									mode_wib->vba.pwefetch_vm_bw[k],
									dmw_max(
											mode_wib->vba.pwefetch_wow_bw[k],
											dmw_max(
													mode_wib->vba.WeadBandwidthPwaneWuma[k]
															+ mode_wib->vba.WeadBandwidthPwaneChwoma[k],
													mode_wib->vba.WequiwedPwefetchPixDataBWWuma[k])
													+ mode_wib->vba.meta_wow_bw[k]
													+ mode_wib->vba.dpte_wow_bw[k]));

			if (mode_wib->vba.DestinationWinesFowPwefetch[k] < 2)
				DestinationWineTimesFowPwefetchWessThan2 = twue;
			if (mode_wib->vba.VWatioPwefetchY[k] > 4
					|| mode_wib->vba.VWatioPwefetchC[k] > 4)
				VWatioPwefetchMoweThan4 = twue;
		}

		if (MaxTotawWDBandwidth <= mode_wib->vba.WetuwnBW && pwefetch_vm_bw_vawid
				&& pwefetch_wow_bw_vawid && !VWatioPwefetchMoweThan4
				&& !DestinationWineTimesFowPwefetchWessThan2)
			mode_wib->vba.PwefetchModeSuppowted = twue;
		ewse {
			mode_wib->vba.PwefetchModeSuppowted = fawse;
			dmw_pwint(
					"DMW: CawcuwatePwefetchScheduwe ***faiwed***. Bandwidth viowation. Wesuwts awe NOT vawid\n");
		}

		if (mode_wib->vba.PwefetchModeSuppowted == twue) {
			doubwe finaw_fwip_bw[DC__NUM_DPP__MAX];
			unsigned int ImmediateFwipBytes[DC__NUM_DPP__MAX];
			doubwe totaw_dcn_wead_bw_with_fwip = 0;

			mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip = mode_wib->vba.WetuwnBW;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip =
						mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip
								- mode_wib->vba.cuwsow_bw[k]
								- dmw_max(
										mode_wib->vba.WeadBandwidthPwaneWuma[k]
												+ mode_wib->vba.WeadBandwidthPwaneChwoma[k]
												+ mode_wib->vba.quaw_wow_bw[k],
										mode_wib->vba.PwefetchBandwidth[k]);
			}

			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				ImmediateFwipBytes[k] = 0;
				if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_420_8
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_420_10)) {
					ImmediateFwipBytes[k] =
							mode_wib->vba.PDEAndMetaPTEBytesFwame[k]
									+ mode_wib->vba.MetaWowByte[k]
									+ mode_wib->vba.PixewPTEBytesPewWow[k];
				}
			}
			mode_wib->vba.TotImmediateFwipBytes = 0;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_420_8
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_420_10)) {
					mode_wib->vba.TotImmediateFwipBytes =
							mode_wib->vba.TotImmediateFwipBytes
									+ ImmediateFwipBytes[k];
				}
			}
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				CawcuwateFwipScheduwe(
						mode_wib,
						mode_wib->vba.UwgentExtwaWatency,
						mode_wib->vba.UwgentWatencyPixewDataOnwy,
						mode_wib->vba.GPUVMMaxPageTabweWevews,
						mode_wib->vba.GPUVMEnabwe,
						mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip,
						mode_wib->vba.TotImmediateFwipBytes,
						mode_wib->vba.SouwcePixewFowmat[k],
						ImmediateFwipBytes[k],
						mode_wib->vba.HTotaw[k]
								/ mode_wib->vba.PixewCwock[k],
						mode_wib->vba.VWatio[k],
						mode_wib->vba.Tno_bw[k],
						mode_wib->vba.PDEAndMetaPTEBytesFwame[k],
						mode_wib->vba.MetaWowByte[k],
						mode_wib->vba.PixewPTEBytesPewWow[k],
						mode_wib->vba.DCCEnabwe[k],
						mode_wib->vba.dpte_wow_height[k],
						mode_wib->vba.meta_wow_height[k],
						mode_wib->vba.quaw_wow_bw[k],
						&mode_wib->vba.DestinationWinesToWequestVMInImmediateFwip[k],
						&mode_wib->vba.DestinationWinesToWequestWowInImmediateFwip[k],
						&finaw_fwip_bw[k],
						&mode_wib->vba.ImmediateFwipSuppowtedFowPipe[k]);
			}
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				totaw_dcn_wead_bw_with_fwip =
						totaw_dcn_wead_bw_with_fwip
								+ mode_wib->vba.cuwsow_bw[k]
								+ dmw_max(
										mode_wib->vba.pwefetch_vm_bw[k],
										dmw_max(
												mode_wib->vba.pwefetch_wow_bw[k],
												finaw_fwip_bw[k]
														+ dmw_max(
																mode_wib->vba.WeadBandwidthPwaneWuma[k]
																		+ mode_wib->vba.WeadBandwidthPwaneChwoma[k],
																mode_wib->vba.WequiwedPwefetchPixDataBWWuma[k])));
			}
			mode_wib->vba.ImmediateFwipSuppowted = twue;
			if (totaw_dcn_wead_bw_with_fwip > mode_wib->vba.WetuwnBW) {
				mode_wib->vba.ImmediateFwipSuppowted = fawse;
			}
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				if (mode_wib->vba.ImmediateFwipSuppowtedFowPipe[k] == fawse) {
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
			&& (!mode_wib->vba.ImmediateFwipSuppowt
					|| mode_wib->vba.ImmediateFwipSuppowted))
			|| mode_wib->vba.MaximumMaxVStawtupWines < mode_wib->vba.VStawtupWines));

	//Dispway Pipewine Dewivewy Time in Pwefetch
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.VWatioPwefetchY[k] <= 1) {
			mode_wib->vba.DispwayPipeWineDewivewyTimeWumaPwefetch[k] =
					mode_wib->vba.SwathWidthY[k] * mode_wib->vba.DPPPewPwane[k]
							/ mode_wib->vba.HWatio[k]
							/ mode_wib->vba.PixewCwock[k];
		} ewse {
			mode_wib->vba.DispwayPipeWineDewivewyTimeWumaPwefetch[k] =
					mode_wib->vba.SwathWidthY[k]
							/ mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k]
							/ mode_wib->vba.DPPCWK[k];
		}
		if (mode_wib->vba.BytePewPixewDETC[k] == 0) {
			mode_wib->vba.DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (mode_wib->vba.VWatioPwefetchC[k] <= 1) {
				mode_wib->vba.DispwayPipeWineDewivewyTimeChwomaPwefetch[k] =
						mode_wib->vba.SwathWidthY[k]
								* mode_wib->vba.DPPPewPwane[k]
								/ mode_wib->vba.HWatio[k]
								/ mode_wib->vba.PixewCwock[k];
			} ewse {
				mode_wib->vba.DispwayPipeWineDewivewyTimeChwomaPwefetch[k] =
						mode_wib->vba.SwathWidthY[k]
								/ mode_wib->vba.PSCW_THWOUGHPUT_WUMA[k]
								/ mode_wib->vba.DPPCWK[k];
			}
		}
	}

	// Min TTUVBwank
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb] == 0) {
			mode_wib->vba.AwwowDWAMCwockChangeDuwingVBwank[k] = twue;
			mode_wib->vba.AwwowDWAMSewfWefweshDuwingVBwank[k] = twue;
			mode_wib->vba.MinTTUVBwank[k] = dmw_max(
					mode_wib->vba.DWAMCwockChangeWatewmawk,
					dmw_max(
							mode_wib->vba.StuttewEntewPwusExitWatewmawk,
							mode_wib->vba.UwgentWatewmawk));
		} ewse if (mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb] == 1) {
			mode_wib->vba.AwwowDWAMCwockChangeDuwingVBwank[k] = fawse;
			mode_wib->vba.AwwowDWAMSewfWefweshDuwingVBwank[k] = twue;
			mode_wib->vba.MinTTUVBwank[k] = dmw_max(
					mode_wib->vba.StuttewEntewPwusExitWatewmawk,
					mode_wib->vba.UwgentWatewmawk);
		} ewse {
			mode_wib->vba.AwwowDWAMCwockChangeDuwingVBwank[k] = fawse;
			mode_wib->vba.AwwowDWAMSewfWefweshDuwingVBwank[k] = fawse;
			mode_wib->vba.MinTTUVBwank[k] = mode_wib->vba.UwgentWatewmawk;
		}
		if (!mode_wib->vba.DynamicMetadataEnabwe[k])
			mode_wib->vba.MinTTUVBwank[k] = mode_wib->vba.TCawc
					+ mode_wib->vba.MinTTUVBwank[k];
	}

	// DCC Configuwation
	mode_wib->vba.ActiveDPPs = 0;
	// NB P-State/DWAM Cwock Change Suppowt
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		mode_wib->vba.ActiveDPPs = mode_wib->vba.ActiveDPPs + mode_wib->vba.DPPPewPwane[k];
	}

	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		doubwe EffectiveWBWatencyHidingY;
		doubwe EffectiveWBWatencyHidingC;
		doubwe DPPOutputBuffewWinesY;
		doubwe DPPOutputBuffewWinesC;
		doubwe DPPOPPBuffewingY;
		doubwe MaxDETBuffewingTimeY;
		doubwe ActiveDWAMCwockChangeWatencyMawginY;

		mode_wib->vba.WBWatencyHidingSouwceWinesY =
				dmw_min(
						mode_wib->vba.MaxWineBuffewWines,
						(unsigned int) dmw_fwoow(
								(doubwe) mode_wib->vba.WineBuffewSize
										/ mode_wib->vba.WBBitPewPixew[k]
										/ (mode_wib->vba.SwathWidthY[k]
												/ dmw_max(
														mode_wib->vba.HWatio[k],
														1.0)),
								1)) - (mode_wib->vba.vtaps[k] - 1);

		mode_wib->vba.WBWatencyHidingSouwceWinesC =
				dmw_min(
						mode_wib->vba.MaxWineBuffewWines,
						(unsigned int) dmw_fwoow(
								(doubwe) mode_wib->vba.WineBuffewSize
										/ mode_wib->vba.WBBitPewPixew[k]
										/ (mode_wib->vba.SwathWidthY[k]
												/ 2.0
												/ dmw_max(
														mode_wib->vba.HWatio[k]
																/ 2,
														1.0)),
								1))
						- (mode_wib->vba.VTAPsChwoma[k] - 1);

		EffectiveWBWatencyHidingY = mode_wib->vba.WBWatencyHidingSouwceWinesY
				/ mode_wib->vba.VWatio[k]
				* (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]);

		EffectiveWBWatencyHidingC = mode_wib->vba.WBWatencyHidingSouwceWinesC
				/ (mode_wib->vba.VWatio[k] / 2)
				* (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]);

		if (mode_wib->vba.SwathWidthY[k] > 2 * mode_wib->vba.DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesY = mode_wib->vba.DPPOutputBuffewPixews
					/ mode_wib->vba.SwathWidthY[k];
		} ewse if (mode_wib->vba.SwathWidthY[k] > mode_wib->vba.DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesY = 0.5;
		} ewse {
			DPPOutputBuffewWinesY = 1;
		}

		if (mode_wib->vba.SwathWidthY[k] / 2 > 2 * mode_wib->vba.DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesC = mode_wib->vba.DPPOutputBuffewPixews
					/ (mode_wib->vba.SwathWidthY[k] / 2);
		} ewse if (mode_wib->vba.SwathWidthY[k] / 2 > mode_wib->vba.DPPOutputBuffewPixews) {
			DPPOutputBuffewWinesC = 0.5;
		} ewse {
			DPPOutputBuffewWinesC = 1;
		}

		DPPOPPBuffewingY = (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
				* (DPPOutputBuffewWinesY + mode_wib->vba.OPPOutputBuffewWines);
		MaxDETBuffewingTimeY = mode_wib->vba.FuwwDETBuffewingTimeY[k]
				+ (mode_wib->vba.WinesInDETY[k]
						- mode_wib->vba.WinesInDETYWoundedDownToSwath[k])
						/ mode_wib->vba.SwathHeightY[k]
						* (mode_wib->vba.HTotaw[k]
								/ mode_wib->vba.PixewCwock[k]);

		ActiveDWAMCwockChangeWatencyMawginY = DPPOPPBuffewingY + EffectiveWBWatencyHidingY
				+ MaxDETBuffewingTimeY - mode_wib->vba.DWAMCwockChangeWatewmawk;

		if (mode_wib->vba.ActiveDPPs > 1) {
			ActiveDWAMCwockChangeWatencyMawginY =
					ActiveDWAMCwockChangeWatencyMawginY
							- (1 - 1 / (mode_wib->vba.ActiveDPPs - 1))
									* mode_wib->vba.SwathHeightY[k]
									* (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]);
		}

		if (mode_wib->vba.BytePewPixewDETC[k] > 0) {
			doubwe DPPOPPBuffewingC = (mode_wib->vba.HTotaw[k]
					/ mode_wib->vba.PixewCwock[k])
					* (DPPOutputBuffewWinesC
							+ mode_wib->vba.OPPOutputBuffewWines);
			doubwe MaxDETBuffewingTimeC =
					mode_wib->vba.FuwwDETBuffewingTimeC[k]
							+ (mode_wib->vba.WinesInDETC[k]
									- mode_wib->vba.WinesInDETCWoundedDownToSwath[k])
									/ mode_wib->vba.SwathHeightC[k]
									* (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]);
			doubwe ActiveDWAMCwockChangeWatencyMawginC = DPPOPPBuffewingC
					+ EffectiveWBWatencyHidingC + MaxDETBuffewingTimeC
					- mode_wib->vba.DWAMCwockChangeWatewmawk;

			if (mode_wib->vba.ActiveDPPs > 1) {
				ActiveDWAMCwockChangeWatencyMawginC =
						ActiveDWAMCwockChangeWatencyMawginC
								- (1
										- 1
												/ (mode_wib->vba.ActiveDPPs
														- 1))
										* mode_wib->vba.SwathHeightC[k]
										* (mode_wib->vba.HTotaw[k]
												/ mode_wib->vba.PixewCwock[k]);
			}
			mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k] = dmw_min(
					ActiveDWAMCwockChangeWatencyMawginY,
					ActiveDWAMCwockChangeWatencyMawginC);
		} ewse {
			mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k] =
					ActiveDWAMCwockChangeWatencyMawginY;
		}

		if (mode_wib->vba.WwitebackEnabwe[k]) {
			doubwe WwitebackDWAMCwockChangeWatencyMawgin;

			if (mode_wib->vba.WwitebackPixewFowmat[k] == dm_444_32) {
				WwitebackDWAMCwockChangeWatencyMawgin =
						(doubwe) (mode_wib->vba.WwitebackIntewfaceWumaBuffewSize
								+ mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize)
								/ (mode_wib->vba.WwitebackDestinationWidth[k]
										* mode_wib->vba.WwitebackDestinationHeight[k]
										/ (mode_wib->vba.WwitebackSouwceHeight[k]
												* mode_wib->vba.HTotaw[k]
												/ mode_wib->vba.PixewCwock[k])
										* 4)
								- mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk;
			} ewse if (mode_wib->vba.WwitebackPixewFowmat[k] == dm_420_10) {
				WwitebackDWAMCwockChangeWatencyMawgin =
						dmw_min(
								(doubwe) mode_wib->vba.WwitebackIntewfaceWumaBuffewSize
										* 8.0 / 10,
								2.0
										* mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize
										* 8 / 10)
								/ (mode_wib->vba.WwitebackDestinationWidth[k]
										* mode_wib->vba.WwitebackDestinationHeight[k]
										/ (mode_wib->vba.WwitebackSouwceHeight[k]
												* mode_wib->vba.HTotaw[k]
												/ mode_wib->vba.PixewCwock[k]))
								- mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk;
			} ewse {
				WwitebackDWAMCwockChangeWatencyMawgin =
						dmw_min(
								(doubwe) mode_wib->vba.WwitebackIntewfaceWumaBuffewSize,
								2.0
										* mode_wib->vba.WwitebackIntewfaceChwomaBuffewSize)
								/ (mode_wib->vba.WwitebackDestinationWidth[k]
										* mode_wib->vba.WwitebackDestinationHeight[k]
										/ (mode_wib->vba.WwitebackSouwceHeight[k]
												* mode_wib->vba.HTotaw[k]
												/ mode_wib->vba.PixewCwock[k]))
								- mode_wib->vba.WwitebackDWAMCwockChangeWatewmawk;
			}
			mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k] = dmw_min(
					mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k],
					WwitebackDWAMCwockChangeWatencyMawgin);
		}
	}

	mode_wib->vba.MinActiveDWAMCwockChangeMawgin = 999999;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k]
				< mode_wib->vba.MinActiveDWAMCwockChangeMawgin) {
			mode_wib->vba.MinActiveDWAMCwockChangeMawgin =
					mode_wib->vba.ActiveDWAMCwockChangeWatencyMawgin[k];
		}
	}

	mode_wib->vba.MinActiveDWAMCwockChangeWatencySuppowted =
			mode_wib->vba.MinActiveDWAMCwockChangeMawgin
					+ mode_wib->vba.DWAMCwockChangeWatency;

	if (mode_wib->vba.DWAMCwockChangeSuppowtsVActive &&
			mode_wib->vba.MinActiveDWAMCwockChangeMawgin > 60) {
		mode_wib->vba.DWAMCwockChangeWatewmawk += 25;
		mode_wib->vba.DWAMCwockChangeSuppowt[0][0] = dm_dwam_cwock_change_vactive;
	} ewse {
		if (mode_wib->vba.SynchwonizedVBwank || mode_wib->vba.NumbewOfActivePwanes == 1) {
			mode_wib->vba.DWAMCwockChangeSuppowt[0][0] = dm_dwam_cwock_change_vbwank;
			fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
				if (!mode_wib->vba.AwwowDWAMCwockChangeDuwingVBwank[k]) {
					mode_wib->vba.DWAMCwockChangeSuppowt[0][0] =
							dm_dwam_cwock_change_unsuppowted;
				}
			}
		} ewse {
			mode_wib->vba.DWAMCwockChangeSuppowt[0][0] = dm_dwam_cwock_change_unsuppowted;
		}
	}
	fow (k = 0; k <= mode_wib->vba.soc.num_states; k++)
		fow (j = 0; j < 2; j++)
			mode_wib->vba.DWAMCwockChangeSuppowt[k][j] = mode_wib->vba.DWAMCwockChangeSuppowt[0][0];

	//XFC Pawametews:
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
		if (mode_wib->vba.XFCEnabwed[k] == twue) {
			doubwe TWait;

			mode_wib->vba.XFCSwaveVUpdateOffset[k] = mode_wib->vba.XFCTSwvVupdateOffset;
			mode_wib->vba.XFCSwaveVupdateWidth[k] = mode_wib->vba.XFCTSwvVupdateWidth;
			mode_wib->vba.XFCSwaveVWeadyOffset[k] = mode_wib->vba.XFCTSwvVweadyOffset;
			TWait = CawcuwateTWait(
					mode_wib->vba.PwefetchMode[mode_wib->vba.VowtageWevew][mode_wib->vba.maxMpcComb],
					mode_wib->vba.DWAMCwockChangeWatency,
					mode_wib->vba.UwgentWatencyPixewDataOnwy,
					mode_wib->vba.SWEntewPwusExitTime);
			mode_wib->vba.XFCWemoteSuwfaceFwipDeway = CawcuwateWemoteSuwfaceFwipDeway(
					mode_wib,
					mode_wib->vba.VWatio[k],
					mode_wib->vba.SwathWidthY[k],
					dmw_ceiw(mode_wib->vba.BytePewPixewDETY[k], 1),
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
			mode_wib->vba.XFCWemoteSuwfaceFwipWatency[k] =
					dmw_fwoow(
							mode_wib->vba.XFCWemoteSuwfaceFwipDeway
									/ (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]),
							1);
			mode_wib->vba.XFCTwansfewDeway[k] =
					dmw_ceiw(
							mode_wib->vba.XFCBusTwanspowtTime
									/ (mode_wib->vba.HTotaw[k]
											/ mode_wib->vba.PixewCwock[k]),
							1);
			mode_wib->vba.XFCPwechawgeDeway[k] =
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
					(mode_wib->vba.DestinationWinesToWequestVMInVBwank[k]
							+ mode_wib->vba.DestinationWinesToWequestWowInVBwank[k])
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
			mode_wib->vba.XFCPwefetchMawgin[k] =
					mode_wib->vba.XFCWemoteSuwfaceFwipDeway
							+ mode_wib->vba.TFinawxFiww
							+ (mode_wib->vba.DestinationWinesToWequestVMInVBwank[k]
									+ mode_wib->vba.DestinationWinesToWequestWowInVBwank[k])
									* mode_wib->vba.HTotaw[k]
									/ mode_wib->vba.PixewCwock[k];
		} ewse {
			mode_wib->vba.XFCSwaveVUpdateOffset[k] = 0;
			mode_wib->vba.XFCSwaveVupdateWidth[k] = 0;
			mode_wib->vba.XFCSwaveVWeadyOffset[k] = 0;
			mode_wib->vba.XFCWemoteSuwfaceFwipWatency[k] = 0;
			mode_wib->vba.XFCPwechawgeDeway[k] = 0;
			mode_wib->vba.XFCTwansfewDeway[k] = 0;
			mode_wib->vba.XFCPwefetchMawgin[k] = 0;
		}
	}
	{
		unsigned int VStawtupMawgin = 0;
		boow FiwstMainPwane = twue;

		fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; ++k) {
			if (mode_wib->vba.BwendingAndTiming[k] == k) {
				unsigned int Mawgin = (mode_wib->vba.MaxVStawtupWines[k] - mode_wib->vba.VStawtup[k])
						* mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k];

				if (FiwstMainPwane) {
					VStawtupMawgin = Mawgin;
					FiwstMainPwane = fawse;
				} ewse
					VStawtupMawgin = dmw_min(VStawtupMawgin, Mawgin);
		}

		if (mode_wib->vba.UseMaximumVStawtup) {
			if (mode_wib->vba.VTotaw_Max[k] == mode_wib->vba.VTotaw[k]) {
				//onwy use max vstawt if it is not dww ow watefwip.
				mode_wib->vba.VStawtup[k] = mode_wib->vba.MaxVStawtupWines[mode_wib->vba.BwendingAndTiming[k]];
			}
		}
	}
}
}

static void dmw20_DispwayPipeConfiguwation(stwuct dispway_mode_wib *mode_wib)
{
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
			if (mode_wib->vba.DPPPewPwane[k] == 0)
				SwathWidth = 0;
			ewse
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

		if (mode_wib->vba.SwathHeightC[k] == 0) {
			mode_wib->vba.DETBuffewSizeY[k] = mode_wib->vba.DETBuffewSizeInKByte[0] * 1024;
			mode_wib->vba.DETBuffewSizeC[k] = 0;
		} ewse if (mode_wib->vba.SwathHeightY[k] <= mode_wib->vba.SwathHeightC[k]) {
			mode_wib->vba.DETBuffewSizeY[k] = mode_wib->vba.DETBuffewSizeInKByte[0]
					* 1024.0 / 2;
			mode_wib->vba.DETBuffewSizeC[k] = mode_wib->vba.DETBuffewSizeInKByte[0]
					* 1024.0 / 2;
		} ewse {
			mode_wib->vba.DETBuffewSizeY[k] = mode_wib->vba.DETBuffewSizeInKByte[0]
					* 1024.0 * 2 / 3;
			mode_wib->vba.DETBuffewSizeC[k] = mode_wib->vba.DETBuffewSizeInKByte[0]
					* 1024.0 / 3;
		}
	}
}

static doubwe CawcuwateTWait(
		unsigned int PwefetchMode,
		doubwe DWAMCwockChangeWatency,
		doubwe UwgentWatencyPixewDataOnwy,
		doubwe SWEntewPwusExitTime)
{
	if (PwefetchMode == 0) {
		wetuwn dmw_max(
				DWAMCwockChangeWatency + UwgentWatencyPixewDataOnwy,
				dmw_max(SWEntewPwusExitTime, UwgentWatencyPixewDataOnwy));
	} ewse if (PwefetchMode == 1) {
		wetuwn dmw_max(SWEntewPwusExitTime, UwgentWatencyPixewDataOnwy);
	} ewse {
		wetuwn UwgentWatencyPixewDataOnwy;
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
		doubwe *dpte_wow_bw,
		doubwe *quaw_wow_bw)
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

	if ((SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10)) {
		*quaw_wow_bw = *meta_wow_bw + *dpte_wow_bw;
	} ewse {
		*quaw_wow_bw = 0;
	}
}

static void CawcuwateFwipScheduwe(
		stwuct dispway_mode_wib *mode_wib,
		doubwe UwgentExtwaWatency,
		doubwe UwgentWatencyPixewDataOnwy,
		unsigned int GPUVMMaxPageTabweWevews,
		boow GPUVMEnabwe,
		doubwe BandwidthAvaiwabweFowImmediateFwip,
		unsigned int TotImmediateFwipBytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int ImmediateFwipBytes,
		doubwe WineTime,
		doubwe VWatio,
		doubwe Tno_bw,
		doubwe PDEAndMetaPTEBytesFwame,
		unsigned int MetaWowByte,
		unsigned int PixewPTEBytesPewWow,
		boow DCCEnabwe,
		unsigned int dpte_wow_height,
		unsigned int meta_wow_height,
		doubwe quaw_wow_bw,
		doubwe *DestinationWinesToWequestVMInImmediateFwip,
		doubwe *DestinationWinesToWequestWowInImmediateFwip,
		doubwe *finaw_fwip_bw,
		boow *ImmediateFwipSuppowtedFowPipe)
{
	doubwe min_wow_time = 0.0;

	if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10) {
		*DestinationWinesToWequestVMInImmediateFwip = 0.0;
		*DestinationWinesToWequestWowInImmediateFwip = 0.0;
		*finaw_fwip_bw = quaw_wow_bw;
		*ImmediateFwipSuppowtedFowPipe = twue;
	} ewse {
		doubwe TimeFowFetchingMetaPTEImmediateFwip;
		doubwe TimeFowFetchingWowInVBwankImmediateFwip;

		if (GPUVMEnabwe == twue) {
			mode_wib->vba.ImmediateFwipBW[0] = BandwidthAvaiwabweFowImmediateFwip
					* ImmediateFwipBytes / TotImmediateFwipBytes;
			TimeFowFetchingMetaPTEImmediateFwip =
					dmw_max(
							Tno_bw
									+ PDEAndMetaPTEBytesFwame
											/ mode_wib->vba.ImmediateFwipBW[0],
							dmw_max(
									UwgentExtwaWatency
											+ UwgentWatencyPixewDataOnwy
													* (GPUVMMaxPageTabweWevews
															- 1),
									WineTime / 4.0));
		} ewse {
			TimeFowFetchingMetaPTEImmediateFwip = 0;
		}

		*DestinationWinesToWequestVMInImmediateFwip = dmw_fwoow(
				4.0 * (TimeFowFetchingMetaPTEImmediateFwip / WineTime + 0.125),
				1) / 4.0;

		if ((GPUVMEnabwe || DCCEnabwe)) {
			mode_wib->vba.ImmediateFwipBW[0] = BandwidthAvaiwabweFowImmediateFwip
					* ImmediateFwipBytes / TotImmediateFwipBytes;
			TimeFowFetchingWowInVBwankImmediateFwip = dmw_max(
					(MetaWowByte + PixewPTEBytesPewWow)
							/ mode_wib->vba.ImmediateFwipBW[0],
					dmw_max(UwgentWatencyPixewDataOnwy, WineTime / 4.0));
		} ewse {
			TimeFowFetchingWowInVBwankImmediateFwip = 0;
		}

		*DestinationWinesToWequestWowInImmediateFwip = dmw_fwoow(
				4.0 * (TimeFowFetchingWowInVBwankImmediateFwip / WineTime + 0.125),
				1) / 4.0;

		if (GPUVMEnabwe == twue) {
			*finaw_fwip_bw =
					dmw_max(
							PDEAndMetaPTEBytesFwame
									/ (*DestinationWinesToWequestVMInImmediateFwip
											* WineTime),
							(MetaWowByte + PixewPTEBytesPewWow)
									/ (TimeFowFetchingWowInVBwankImmediateFwip
											* WineTime));
		} ewse if (MetaWowByte + PixewPTEBytesPewWow > 0) {
			*finaw_fwip_bw = (MetaWowByte + PixewPTEBytesPewWow)
					/ (TimeFowFetchingWowInVBwankImmediateFwip * WineTime);
		} ewse {
			*finaw_fwip_bw = 0;
		}

		if (GPUVMEnabwe && !DCCEnabwe)
			min_wow_time = dpte_wow_height * WineTime / VWatio;
		ewse if (!GPUVMEnabwe && DCCEnabwe)
			min_wow_time = meta_wow_height * WineTime / VWatio;
		ewse
			min_wow_time = dmw_min(dpte_wow_height, meta_wow_height) * WineTime
					/ VWatio;

		if (*DestinationWinesToWequestVMInImmediateFwip >= 8
				|| *DestinationWinesToWequestWowInImmediateFwip >= 16
				|| TimeFowFetchingMetaPTEImmediateFwip
						+ 2 * TimeFowFetchingWowInVBwankImmediateFwip
						> min_wow_time)
			*ImmediateFwipSuppowtedFowPipe = fawse;
		ewse
			*ImmediateFwipSuppowtedFowPipe = twue;
	}
}

static unsigned int TwuncToVawidBPP(
		doubwe DecimawBPP,
		boow DSCEnabwed,
		enum output_encodew_cwass Output,
		enum output_fowmat_cwass Fowmat,
		unsigned int DSCInputBitPewComponent)
{
	if (Output == dm_hdmi) {
		if (Fowmat == dm_420) {
			if (DecimawBPP >= 18)
				wetuwn 18;
			ewse if (DecimawBPP >= 15)
				wetuwn 15;
			ewse if (DecimawBPP >= 12)
				wetuwn 12;
			ewse
				wetuwn BPP_INVAWID;
		} ewse if (Fowmat == dm_444) {
			if (DecimawBPP >= 36)
				wetuwn 36;
			ewse if (DecimawBPP >= 30)
				wetuwn 30;
			ewse if (DecimawBPP >= 24)
				wetuwn 24;
			ewse if (DecimawBPP >= 18)
				wetuwn 18;
			ewse
				wetuwn BPP_INVAWID;
		} ewse {
			if (DecimawBPP / 1.5 >= 24)
				wetuwn 24;
			ewse if (DecimawBPP / 1.5 >= 20)
				wetuwn 20;
			ewse if (DecimawBPP / 1.5 >= 16)
				wetuwn 16;
			ewse
				wetuwn BPP_INVAWID;
		}
	} ewse {
		if (DSCEnabwed) {
			if (Fowmat == dm_420) {
				if (DecimawBPP < 6)
					wetuwn BPP_INVAWID;
				ewse if (DecimawBPP >= 1.5 * DSCInputBitPewComponent - 1 / 16)
					wetuwn 1.5 * DSCInputBitPewComponent - 1 / 16;
				ewse
					wetuwn dmw_fwoow(16 * DecimawBPP, 1) / 16;
			} ewse if (Fowmat == dm_n422) {
				if (DecimawBPP < 7)
					wetuwn BPP_INVAWID;
				ewse if (DecimawBPP >= 2 * DSCInputBitPewComponent - 1 / 16)
					wetuwn 2 * DSCInputBitPewComponent - 1 / 16;
				ewse
					wetuwn dmw_fwoow(16 * DecimawBPP, 1) / 16;
			} ewse {
				if (DecimawBPP < 8)
					wetuwn BPP_INVAWID;
				ewse if (DecimawBPP >= 3 * DSCInputBitPewComponent - 1 / 16)
					wetuwn 3 * DSCInputBitPewComponent - 1 / 16;
				ewse
					wetuwn dmw_fwoow(16 * DecimawBPP, 1) / 16;
			}
		} ewse if (Fowmat == dm_420) {
			if (DecimawBPP >= 18)
				wetuwn 18;
			ewse if (DecimawBPP >= 15)
				wetuwn 15;
			ewse if (DecimawBPP >= 12)
				wetuwn 12;
			ewse
				wetuwn BPP_INVAWID;
		} ewse if (Fowmat == dm_s422 || Fowmat == dm_n422) {
			if (DecimawBPP >= 24)
				wetuwn 24;
			ewse if (DecimawBPP >= 20)
				wetuwn 20;
			ewse if (DecimawBPP >= 16)
				wetuwn 16;
			ewse
				wetuwn BPP_INVAWID;
		} ewse {
			if (DecimawBPP >= 36)
				wetuwn 36;
			ewse if (DecimawBPP >= 30)
				wetuwn 30;
			ewse if (DecimawBPP >= 24)
				wetuwn 24;
			ewse if (DecimawBPP >= 18)
				wetuwn 18;
			ewse
				wetuwn BPP_INVAWID;
		}
	}
}

void dmw20_ModeSuppowtAndSystemConfiguwationFuww(stwuct dispway_mode_wib *mode_wib)
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
	mode_wib->vba.UwgentWatency = mode_wib->vba.UwgentWatencyPixewDataOnwy;
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		wocaws->FabwicAndDWAMBandwidthPewState[i] = dmw_min(
				mode_wib->vba.DWAMSpeedPewState[i] * mode_wib->vba.NumbewOfChannews
						* mode_wib->vba.DWAMChannewWidth,
				mode_wib->vba.FabwicCwockPewState[i]
						* mode_wib->vba.FabwicDatapathToDCNDataWetuwn) / 1000;
		wocaws->WetuwnBWToDCNPewState = dmw_min(wocaws->WetuwnBusWidth * wocaws->DCFCWKPewState[i],
				wocaws->FabwicAndDWAMBandwidthPewState[i] * 1000)
				* wocaws->PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewDataOnwy / 100;

		wocaws->WetuwnBWPewState[i][0] = wocaws->WetuwnBWToDCNPewState;

		if (wocaws->DCCEnabwedInAnyPwane == twue && wocaws->WetuwnBWToDCNPewState > wocaws->DCFCWKPewState[i] * wocaws->WetuwnBusWidth / 4) {
			wocaws->WetuwnBWPewState[i][0] = dmw_min(wocaws->WetuwnBWPewState[i][0],
					wocaws->WetuwnBWToDCNPewState * 4 * (1 - wocaws->UwgentWatency /
					((wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024
					/ (wocaws->WetuwnBWToDCNPewState - wocaws->DCFCWKPewState[i]
					* wocaws->WetuwnBusWidth / 4) + wocaws->UwgentWatency)));
		}
		wocaws->CwiticawPoint = 2 * wocaws->WetuwnBusWidth * wocaws->DCFCWKPewState[i] *
				wocaws->UwgentWatency / (wocaws->WetuwnBWToDCNPewState * wocaws->UwgentWatency
				+ (wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024);

		if (wocaws->DCCEnabwedInAnyPwane && wocaws->CwiticawPoint > 1 && wocaws->CwiticawPoint < 4) {
			wocaws->WetuwnBWPewState[i][0] = dmw_min(wocaws->WetuwnBWPewState[i][0],
				4 * wocaws->WetuwnBWToDCNPewState *
				(wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024
				* wocaws->WetuwnBusWidth * wocaws->DCFCWKPewState[i] * wocaws->UwgentWatency /
				dmw_pow((wocaws->WetuwnBWToDCNPewState * wocaws->UwgentWatency
				+ (wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024), 2));
		}

		wocaws->WetuwnBWToDCNPewState = dmw_min(wocaws->WetuwnBusWidth *
				wocaws->DCFCWKPewState[i], wocaws->FabwicAndDWAMBandwidthPewState[i] * 1000);

		if (wocaws->DCCEnabwedInAnyPwane == twue && wocaws->WetuwnBWToDCNPewState > wocaws->DCFCWKPewState[i] * wocaws->WetuwnBusWidth / 4) {
			wocaws->WetuwnBWPewState[i][0] = dmw_min(wocaws->WetuwnBWPewState[i][0],
					wocaws->WetuwnBWToDCNPewState * 4 * (1 - wocaws->UwgentWatency /
					((wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024
					/ (wocaws->WetuwnBWToDCNPewState - wocaws->DCFCWKPewState[i]
					* wocaws->WetuwnBusWidth / 4) + wocaws->UwgentWatency)));
		}
		wocaws->CwiticawPoint = 2 * wocaws->WetuwnBusWidth * wocaws->DCFCWKPewState[i] *
				wocaws->UwgentWatency / (wocaws->WetuwnBWToDCNPewState * wocaws->UwgentWatency
				+ (wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024);

		if (wocaws->DCCEnabwedInAnyPwane && wocaws->CwiticawPoint > 1 && wocaws->CwiticawPoint < 4) {
			wocaws->WetuwnBWPewState[i][0] = dmw_min(wocaws->WetuwnBWPewState[i][0],
				4 * wocaws->WetuwnBWToDCNPewState *
				(wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024
				* wocaws->WetuwnBusWidth * wocaws->DCFCWKPewState[i] * wocaws->UwgentWatency /
				dmw_pow((wocaws->WetuwnBWToDCNPewState * wocaws->UwgentWatency
				+ (wocaws->WOBBuffewSizeInKByte - wocaws->PixewChunkSizeInKByte) * 1024), 2));
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
				+ wocaws->UwgentOutOfOwdewWetuwnPewChannew * mode_wib->vba.NumbewOfChannews / wocaws->WetuwnBWPewState[i][0];
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
						mode_wib->vba.PixewCwock[k] * (1.0 + mode_wib->vba.DISPCWKDPPCWKDSCCWKDownSpweading / 100.0)
								* (1.0 + mode_wib->vba.DISPCWKWampingMawgin / 100.0);
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
					if (wocaws->PwaneWequiwedDISPCWKWithoutODMCombine > mode_wib->vba.MaxDispcwkWoundedDownToDFSGwanuwawity) {
						wocaws->ODMCombineEnabwePewState[i][k] = dm_odm_combine_mode_2to1;
						mode_wib->vba.PwaneWequiwedDISPCWK = mode_wib->vba.PwaneWequiwedDISPCWKWithODMCombine;
					} ewse if (wocaws->HActive[k] > DCN20_MAX_420_IMAGE_WIDTH && wocaws->OutputFowmat[k] == dm_420) {
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
			wocaws->WequiwesDSC[i][k] = 0;
			wocaws->WequiwesFEC[i][k] = 0;
			if (mode_wib->vba.BwendingAndTiming[k] == k) {
				if (mode_wib->vba.Output[k] == dm_hdmi) {
					wocaws->WequiwesDSC[i][k] = 0;
					wocaws->WequiwesFEC[i][k] = 0;
					wocaws->OutputBppPewState[i][k] = TwuncToVawidBPP(
							dmw_min(600.0, mode_wib->vba.PHYCWKPewState[i]) / mode_wib->vba.PixewCwockBackEnd[k] * 24,
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
								fawse,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						mode_wib->vba.OutbppDSC = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * (1.0 - mode_wib->vba.EffectiveFECOvewhead / 100.0) * 270.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
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
									fawse,
									mode_wib->vba.Output[k],
									mode_wib->vba.OutputFowmat[k],
									mode_wib->vba.DSCInputBitPewComponent[k]);
						mode_wib->vba.OutbppDSC = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * (1.0 - mode_wib->vba.EffectiveFECOvewhead / 100.0) * 540.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
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
								fawse,
								mode_wib->vba.Output[k],
								mode_wib->vba.OutputFowmat[k],
								mode_wib->vba.DSCInputBitPewComponent[k]);
						mode_wib->vba.OutbppDSC = TwuncToVawidBPP(
								(1.0 - mode_wib->vba.Downspweading / 100.0) * (1.0 - mode_wib->vba.EffectiveFECOvewhead / 100.0) * 810.0
								* mode_wib->vba.OutputWinkDPWanes[k] / mode_wib->vba.PixewCwockBackEnd[k] * 8.0,
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
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				if (wocaws->ODMCombineEnabwePewState[i][k] == dm_odm_combine_mode_2to1)
					wocaws->SwathWidthYPewState[i][j][k] = dmw_min(wocaws->SwathWidthYSingweDPP[k], dmw_wound(wocaws->HActive[k] / 2 * wocaws->HWatio[k]));
				ewse
					wocaws->SwathWidthYPewState[i][j][k] = wocaws->SwathWidthYSingweDPP[k] / wocaws->NoOfDPP[i][j][k];
				wocaws->SwathWidthGwanuwawityY = 256  / dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1) / wocaws->MaxSwathHeightY[k];
				wocaws->WoundedUpMaxSwathSizeBytesY = (dmw_ceiw(wocaws->SwathWidthYPewState[i][j][k] - 1, wocaws->SwathWidthGwanuwawityY)
						+ wocaws->SwathWidthGwanuwawityY) * wocaws->BytePewPixewInDETY[k] * wocaws->MaxSwathHeightY[k];
				if (wocaws->SouwcePixewFowmat[k] == dm_420_10) {
					wocaws->WoundedUpMaxSwathSizeBytesY = dmw_ceiw(wocaws->WoundedUpMaxSwathSizeBytesY, 256) + 256;
				}
				if (wocaws->MaxSwathHeightC[k] > 0) {
					wocaws->SwathWidthGwanuwawityC = 256 / dmw_ceiw(wocaws->BytePewPixewInDETC[k], 2) / wocaws->MaxSwathHeightC[k];

					wocaws->WoundedUpMaxSwathSizeBytesC = (dmw_ceiw(wocaws->SwathWidthYPewState[i][j][k] / 2 - 1, wocaws->SwathWidthGwanuwawityC)
					+ wocaws->SwathWidthGwanuwawityC) * wocaws->BytePewPixewInDETC[k] * wocaws->MaxSwathHeightC[k];
				}
				if (wocaws->SouwcePixewFowmat[k] == dm_420_10) {
					wocaws->WoundedUpMaxSwathSizeBytesC = dmw_ceiw(wocaws->WoundedUpMaxSwathSizeBytesC, 256)  + 256;
				} ewse {
					wocaws->WoundedUpMaxSwathSizeBytesC = 0;
				}

				if (wocaws->WoundedUpMaxSwathSizeBytesY + wocaws->WoundedUpMaxSwathSizeBytesC <= wocaws->DETBuffewSizeInKByte[0] * 1024 / 2) {
					wocaws->SwathHeightYPewState[i][j][k] = wocaws->MaxSwathHeightY[k];
					wocaws->SwathHeightCPewState[i][j][k] = wocaws->MaxSwathHeightC[k];
				} ewse {
					wocaws->SwathHeightYPewState[i][j][k] = wocaws->MinSwathHeightY[k];
					wocaws->SwathHeightCPewState[i][j][k] = wocaws->MinSwathHeightC[k];
				}

				if (wocaws->BytePewPixewInDETC[k] == 0) {
					wocaws->WinesInDETWuma = wocaws->DETBuffewSizeInKByte[0] * 1024 / wocaws->BytePewPixewInDETY[k] / wocaws->SwathWidthYPewState[i][j][k];
					wocaws->WinesInDETChwoma = 0;
				} ewse if (wocaws->SwathHeightYPewState[i][j][k] <= wocaws->SwathHeightCPewState[i][j][k]) {
					wocaws->WinesInDETWuma = wocaws->DETBuffewSizeInKByte[0] * 1024 / 2 / wocaws->BytePewPixewInDETY[k] /
							wocaws->SwathWidthYPewState[i][j][k];
					wocaws->WinesInDETChwoma = wocaws->DETBuffewSizeInKByte[0] * 1024 / 2 / wocaws->BytePewPixewInDETC[k] / (wocaws->SwathWidthYPewState[i][j][k] / 2);
				} ewse {
					wocaws->WinesInDETWuma = wocaws->DETBuffewSizeInKByte[0] * 1024 * 2 / 3 / wocaws->BytePewPixewInDETY[k] / wocaws->SwathWidthYPewState[i][j][k];
					wocaws->WinesInDETChwoma = wocaws->DETBuffewSizeInKByte[0] * 1024 / 3 / wocaws->BytePewPixewInDETY[k] / (wocaws->SwathWidthYPewState[i][j][k] / 2);
				}

				wocaws->EffectiveWBWatencyHidingSouwceWinesWuma = dmw_min(wocaws->MaxWineBuffewWines,
					dmw_fwoow(wocaws->WineBuffewSize / wocaws->WBBitPewPixew[k] / (wocaws->SwathWidthYPewState[i][j][k]
					/ dmw_max(wocaws->HWatio[k], 1)), 1)) - (wocaws->vtaps[k] - 1);

				wocaws->EffectiveWBWatencyHidingSouwceWinesChwoma =  dmw_min(wocaws->MaxWineBuffewWines,
						dmw_fwoow(wocaws->WineBuffewSize / wocaws->WBBitPewPixew[k]
						/ (wocaws->SwathWidthYPewState[i][j][k] / 2
						/ dmw_max(wocaws->HWatio[k] / 2, 1)), 1)) - (wocaws->VTAPsChwoma[k] - 1);

				wocaws->EffectiveDETWBWinesWuma = dmw_fwoow(wocaws->WinesInDETWuma +  dmw_min(
						wocaws->WinesInDETWuma * wocaws->WequiwedDISPCWK[i][j] * wocaws->BytePewPixewInDETY[k] *
						wocaws->PSCW_FACTOW[k] / wocaws->WetuwnBWPewState[i][0],
						wocaws->EffectiveWBWatencyHidingSouwceWinesWuma),
						wocaws->SwathHeightYPewState[i][j][k]);
				if (wocaws->WinesInDETChwoma) {
					wocaws->EffectiveDETWBWinesChwoma = dmw_fwoow(wocaws->WinesInDETChwoma +
						    dmw_min(wocaws->WinesInDETChwoma * wocaws->WequiwedDISPCWK[i][j] *
						    wocaws->BytePewPixewInDETC[k] *
							wocaws->PSCW_FACTOW_CHWOMA[k] / wocaws->WetuwnBWPewState[i][0],
							wocaws->EffectiveWBWatencyHidingSouwceWinesChwoma),
							wocaws->SwathHeightCPewState[i][j][k]);
				} ewse {
					wocaws->EffectiveDETWBWinesChwoma = 0;
				}

				if (wocaws->BytePewPixewInDETC[k] == 0) {
					wocaws->UwgentWatencySuppowtUsPewState[i][j][k] = wocaws->EffectiveDETWBWinesWuma * (wocaws->HTotaw[k] / wocaws->PixewCwock[k])
							/ wocaws->VWatio[k] - wocaws->EffectiveDETWBWinesWuma * wocaws->SwathWidthYPewState[i][j][k] *
								dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1) / (wocaws->WetuwnBWPewState[i][0] / wocaws->NoOfDPP[i][j][k]);
				} ewse {
					wocaws->UwgentWatencySuppowtUsPewState[i][j][k] = dmw_min(
						wocaws->EffectiveDETWBWinesWuma * (wocaws->HTotaw[k] / wocaws->PixewCwock[k])
						/ wocaws->VWatio[k] - wocaws->EffectiveDETWBWinesWuma * wocaws->SwathWidthYPewState[i][j][k] *
						dmw_ceiw(wocaws->BytePewPixewInDETY[k], 1) / (wocaws->WetuwnBWPewState[i][0] / wocaws->NoOfDPP[i][j][k]),
							wocaws->EffectiveDETWBWinesChwoma * (wocaws->HTotaw[k] / wocaws->PixewCwock[k]) / (wocaws->VWatio[k] / 2) -
							wocaws->EffectiveDETWBWinesChwoma * wocaws->SwathWidthYPewState[i][j][k] / 2 *
							dmw_ceiw(wocaws->BytePewPixewInDETC[k], 2) / (wocaws->WetuwnBWPewState[i][0] / wocaws->NoOfDPP[i][j][k]));
				}
			}
		}
	}

	fow (i = 0; i <= wocaws->soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			wocaws->UwgentWatencySuppowt[i][j] = twue;
			fow (k = 0; k < wocaws->NumbewOfActivePwanes; k++) {
				if (wocaws->UwgentWatencySuppowtUsPewState[i][j][k] < wocaws->UwgentWatency)
					wocaws->UwgentWatencySuppowt[i][j] = fawse;
			}
		}
	}


	/*Pwefetch Check*/
	fow (i = 0; i <= wocaws->soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			wocaws->TotawNumbewOfDCCActiveDPP[i][j] = 0;
			fow (k = 0; k < wocaws->NumbewOfActivePwanes; k++) {
				if (wocaws->DCCEnabwe[k] == twue) {
					wocaws->TotawNumbewOfDCCActiveDPP[i][j] =
						wocaws->TotawNumbewOfDCCActiveDPP[i][j] + wocaws->NoOfDPP[i][j][k];
				}
			}
		}
	}

	CawcuwateMinAndMaxPwefetchMode(wocaws->AwwowDWAMSewfWefweshOwDWAMCwockChangeInVbwank, &wocaws->MinPwefetchMode, &wocaws->MaxPwefetchMode);

	fow (i = 0; i <= wocaws->soc.num_states; i++) {
		fow (j = 0; j < 2; j++) {
			fow (k = 0; k < wocaws->NumbewOfActivePwanes; k++) {
				wocaws->NoOfDPPThisState[k] = wocaws->NoOfDPP[i][j][k];
				wocaws->WequiwedDPPCWKThisState[k] = wocaws->WequiwedDPPCWK[i][j][k];
				wocaws->SwathHeightYThisState[k] = wocaws->SwathHeightYPewState[i][j][k];
				wocaws->SwathHeightCThisState[k] = wocaws->SwathHeightCPewState[i][j][k];
				wocaws->SwathWidthYThisState[k] = wocaws->SwathWidthYPewState[i][j][k];
				mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] = dmw_max(
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
						mode_wib->vba.PixewCwock[k] / 16.0);
				if (mode_wib->vba.BytePewPixewInDETC[k] == 0.0) {
					if (mode_wib->vba.VWatio[k] <= 1.0) {
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] =
								dmw_max(
										mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
										1.1
												* dmw_ceiw(
														mode_wib->vba.BytePewPixewInDETY[k],
														1.0)
												/ 64.0
												* mode_wib->vba.HWatio[k]
												* mode_wib->vba.PixewCwock[k]
												/ mode_wib->vba.NoOfDPP[i][j][k]);
					} ewse {
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] =
								dmw_max(
										mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
										1.1
												* dmw_ceiw(
														mode_wib->vba.BytePewPixewInDETY[k],
														1.0)
												/ 64.0
												* mode_wib->vba.PSCW_FACTOW[k]
												* mode_wib->vba.WequiwedDPPCWK[i][j][k]);
					}
				} ewse {
					if (mode_wib->vba.VWatio[k] <= 1.0) {
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] =
								dmw_max(
										mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
										1.1
												* dmw_ceiw(
														mode_wib->vba.BytePewPixewInDETY[k],
														1.0)
												/ 32.0
												* mode_wib->vba.HWatio[k]
												* mode_wib->vba.PixewCwock[k]
												/ mode_wib->vba.NoOfDPP[i][j][k]);
					} ewse {
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] =
								dmw_max(
										mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
										1.1
												* dmw_ceiw(
														mode_wib->vba.BytePewPixewInDETY[k],
														1.0)
												/ 32.0
												* mode_wib->vba.PSCW_FACTOW[k]
												* mode_wib->vba.WequiwedDPPCWK[i][j][k]);
					}
					if (mode_wib->vba.VWatio[k] / 2.0 <= 1.0) {
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] =
								dmw_max(
										mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
										1.1
												* dmw_ceiw(
														mode_wib->vba.BytePewPixewInDETC[k],
														2.0)
												/ 32.0
												* mode_wib->vba.HWatio[k]
												/ 2.0
												* mode_wib->vba.PixewCwock[k]
												/ mode_wib->vba.NoOfDPP[i][j][k]);
					} ewse {
						mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0] =
								dmw_max(
										mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
										1.1
												* dmw_ceiw(
														mode_wib->vba.BytePewPixewInDETC[k],
														2.0)
												/ 32.0
												* mode_wib->vba.PSCW_FACTOW_CHWOMA[k]
												* mode_wib->vba.WequiwedDPPCWK[i][j][k]);
					}
				}
			}
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				mode_wib->vba.PDEAndMetaPTEBytesPewFwameY = CawcuwateVMAndWowBytes(
						mode_wib,
						mode_wib->vba.DCCEnabwe[k],
						mode_wib->vba.Wead256BwockHeightY[k],
						mode_wib->vba.Wead256BwockWidthY[k],
						mode_wib->vba.SouwcePixewFowmat[k],
						mode_wib->vba.SuwfaceTiwing[k],
						dmw_ceiw(mode_wib->vba.BytePewPixewInDETY[k], 1.0),
						mode_wib->vba.SouwceScan[k],
						mode_wib->vba.ViewpowtWidth[k],
						mode_wib->vba.ViewpowtHeight[k],
						mode_wib->vba.SwathWidthYPewState[i][j][k],
						mode_wib->vba.GPUVMEnabwe,
						mode_wib->vba.VMMPageSize,
						mode_wib->vba.PTEBuffewSizeInWequestsWuma,
						mode_wib->vba.PDEPwocessingBufIn64KBWeqs,
						mode_wib->vba.PitchY[k],
						mode_wib->vba.DCCMetaPitchY[k],
						&mode_wib->vba.MacwoTiweWidthY[k],
						&mode_wib->vba.MetaWowBytesY,
						&mode_wib->vba.DPTEBytesPewWowY,
						&mode_wib->vba.PTEBuffewSizeNotExceededY[i][j][k],
						&mode_wib->vba.dpte_wow_height[k],
						&mode_wib->vba.meta_wow_height[k]);
				mode_wib->vba.PwefetchWinesY[0][0][k] = CawcuwatePwefetchSouwceWines(
						mode_wib,
						mode_wib->vba.VWatio[k],
						mode_wib->vba.vtaps[k],
						mode_wib->vba.Intewwace[k],
						mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
						mode_wib->vba.SwathHeightYPewState[i][j][k],
						mode_wib->vba.ViewpowtYStawtY[k],
						&mode_wib->vba.PwefiwwY[k],
						&mode_wib->vba.MaxNumSwY[k]);
				if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_444_64
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_32
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_444_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_16
						&& mode_wib->vba.SouwcePixewFowmat[k] != dm_mono_8)) {
					mode_wib->vba.PDEAndMetaPTEBytesPewFwameC = CawcuwateVMAndWowBytes(
							mode_wib,
							mode_wib->vba.DCCEnabwe[k],
							mode_wib->vba.Wead256BwockHeightY[k],
							mode_wib->vba.Wead256BwockWidthY[k],
							mode_wib->vba.SouwcePixewFowmat[k],
							mode_wib->vba.SuwfaceTiwing[k],
							dmw_ceiw(mode_wib->vba.BytePewPixewInDETC[k], 2.0),
							mode_wib->vba.SouwceScan[k],
							mode_wib->vba.ViewpowtWidth[k] / 2.0,
							mode_wib->vba.ViewpowtHeight[k] / 2.0,
							mode_wib->vba.SwathWidthYPewState[i][j][k] / 2.0,
							mode_wib->vba.GPUVMEnabwe,
							mode_wib->vba.VMMPageSize,
							mode_wib->vba.PTEBuffewSizeInWequestsWuma,
							mode_wib->vba.PDEPwocessingBufIn64KBWeqs,
							mode_wib->vba.PitchC[k],
							0.0,
							&mode_wib->vba.MacwoTiweWidthC[k],
							&mode_wib->vba.MetaWowBytesC,
							&mode_wib->vba.DPTEBytesPewWowC,
							&mode_wib->vba.PTEBuffewSizeNotExceededC[i][j][k],
							&mode_wib->vba.dpte_wow_height_chwoma[k],
							&mode_wib->vba.meta_wow_height_chwoma[k]);
					mode_wib->vba.PwefetchWinesC[0][0][k] = CawcuwatePwefetchSouwceWines(
							mode_wib,
							mode_wib->vba.VWatio[k] / 2.0,
							mode_wib->vba.VTAPsChwoma[k],
							mode_wib->vba.Intewwace[k],
							mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
							mode_wib->vba.SwathHeightCPewState[i][j][k],
							mode_wib->vba.ViewpowtYStawtC[k],
							&mode_wib->vba.PwefiwwC[k],
							&mode_wib->vba.MaxNumSwC[k]);
				} ewse {
					mode_wib->vba.PDEAndMetaPTEBytesPewFwameC = 0.0;
					mode_wib->vba.MetaWowBytesC = 0.0;
					mode_wib->vba.DPTEBytesPewWowC = 0.0;
					wocaws->PwefetchWinesC[0][0][k] = 0.0;
					wocaws->PTEBuffewSizeNotExceededC[i][j][k] = twue;
					wocaws->PTEBuffewSizeInWequestsFowWuma = mode_wib->vba.PTEBuffewSizeInWequestsWuma + mode_wib->vba.PTEBuffewSizeInWequestsChwoma;
				}
				wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k] =
						mode_wib->vba.PDEAndMetaPTEBytesPewFwameY + mode_wib->vba.PDEAndMetaPTEBytesPewFwameC;
				wocaws->MetaWowBytes[0][0][k] = mode_wib->vba.MetaWowBytesY + mode_wib->vba.MetaWowBytesC;
				wocaws->DPTEBytesPewWow[0][0][k] = mode_wib->vba.DPTEBytesPewWowY + mode_wib->vba.DPTEBytesPewWowC;

				CawcuwateActiveWowBandwidth(
						mode_wib->vba.GPUVMEnabwe,
						mode_wib->vba.SouwcePixewFowmat[k],
						mode_wib->vba.VWatio[k],
						mode_wib->vba.DCCEnabwe[k],
						mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k],
						mode_wib->vba.MetaWowBytesY,
						mode_wib->vba.MetaWowBytesC,
						mode_wib->vba.meta_wow_height[k],
						mode_wib->vba.meta_wow_height_chwoma[k],
						mode_wib->vba.DPTEBytesPewWowY,
						mode_wib->vba.DPTEBytesPewWowC,
						mode_wib->vba.dpte_wow_height[k],
						mode_wib->vba.dpte_wow_height_chwoma[k],
						&mode_wib->vba.meta_wow_bw[k],
						&mode_wib->vba.dpte_wow_bw[k],
						&mode_wib->vba.quaw_wow_bw[k]);
			}
			mode_wib->vba.ExtwaWatency =
					mode_wib->vba.UwgentWoundTwipAndOutOfOwdewWatencyPewState[i]
							+ (mode_wib->vba.TotawNumbewOfActiveDPP[i][j]
									* mode_wib->vba.PixewChunkSizeInKByte
									+ mode_wib->vba.TotawNumbewOfDCCActiveDPP[i][j]
											* mode_wib->vba.MetaChunkSize)
									* 1024.0
									/ mode_wib->vba.WetuwnBWPewState[i][0];
			if (mode_wib->vba.GPUVMEnabwe == twue) {
				mode_wib->vba.ExtwaWatency = mode_wib->vba.ExtwaWatency
						+ mode_wib->vba.TotawNumbewOfActiveDPP[i][j]
								* mode_wib->vba.PTEGwoupSize
								/ mode_wib->vba.WetuwnBWPewState[i][0];
			}
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
			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				fow (m = 0; m < wocaws->NumbewOfCuwsows[k]; m++)
					wocaws->cuwsow_bw[k] = wocaws->NumbewOfCuwsows[k] * wocaws->CuwsowWidth[k][m] * wocaws->CuwsowBPP[k][m]
						/ 8 / (wocaws->HTotaw[k] / wocaws->PixewCwock[k]) * wocaws->VWatio[k];
			}

			fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
				wocaws->MaximumVStawtup[0][0][k] = mode_wib->vba.VTotaw[k] - mode_wib->vba.VActive[k]
					- dmw_max(1.0, dmw_ceiw(wocaws->WwitebackDeway[i][k] / (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k]), 1.0));
			}

			mode_wib->vba.NextPwefetchMode = mode_wib->vba.MinPwefetchMode;
			do {
				mode_wib->vba.PwefetchMode[i][j] = mode_wib->vba.NextPwefetchMode;
				mode_wib->vba.NextPwefetchMode = mode_wib->vba.NextPwefetchMode + 1;

				mode_wib->vba.TWait = CawcuwateTWait(
						mode_wib->vba.PwefetchMode[i][j],
						mode_wib->vba.DWAMCwockChangeWatency,
						mode_wib->vba.UwgentWatency,
						mode_wib->vba.SWEntewPwusExitTime);
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {

					if (mode_wib->vba.XFCEnabwed[k] == twue) {
						mode_wib->vba.XFCWemoteSuwfaceFwipDeway =
								CawcuwateWemoteSuwfaceFwipDeway(
										mode_wib,
										mode_wib->vba.VWatio[k],
										wocaws->SwathWidthYPewState[i][j][k],
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
					mode_wib->vba.IsEwwowWesuwt[i][j][k] =
							CawcuwatePwefetchScheduwe(
									mode_wib,
									mode_wib->vba.WequiwedDPPCWK[i][j][k],
									mode_wib->vba.WequiwedDISPCWK[i][j],
									mode_wib->vba.PixewCwock[k],
									mode_wib->vba.PwojectedDCFCWKDeepSweep[0][0],
									mode_wib->vba.DSCDewayPewState[i][k],
									mode_wib->vba.NoOfDPP[i][j][k],
									mode_wib->vba.ScawewEnabwed[k],
									mode_wib->vba.NumbewOfCuwsows[k],
									mode_wib->vba.DPPCWKDewaySubtotaw,
									mode_wib->vba.DPPCWKDewaySCW,
									mode_wib->vba.DPPCWKDewaySCWWBOnwy,
									mode_wib->vba.DPPCWKDewayCNVCFowmatew,
									mode_wib->vba.DPPCWKDewayCNVCCuwsow,
									mode_wib->vba.DISPCWKDewaySubtotaw,
									mode_wib->vba.SwathWidthYPewState[i][j][k]
											/ mode_wib->vba.HWatio[k],
									mode_wib->vba.OutputFowmat[k],
									mode_wib->vba.VTotaw[k]
											- mode_wib->vba.VActive[k],
									mode_wib->vba.HTotaw[k],
									mode_wib->vba.MaxIntewDCNTiweWepeatews,
									mode_wib->vba.MaximumVStawtup[0][0][k],
									mode_wib->vba.GPUVMMaxPageTabweWevews,
									mode_wib->vba.GPUVMEnabwe,
									mode_wib->vba.DynamicMetadataEnabwe[k],
									mode_wib->vba.DynamicMetadataWinesBefoweActiveWequiwed[k],
									mode_wib->vba.DynamicMetadataTwansmittedBytes[k],
									mode_wib->vba.DCCEnabwe[k],
									mode_wib->vba.UwgentWatencyPixewDataOnwy,
									mode_wib->vba.ExtwaWatency,
									mode_wib->vba.TimeCawc,
									mode_wib->vba.PDEAndMetaPTEBytesPewFwame[0][0][k],
									mode_wib->vba.MetaWowBytes[0][0][k],
									mode_wib->vba.DPTEBytesPewWow[0][0][k],
									mode_wib->vba.PwefetchWinesY[0][0][k],
									mode_wib->vba.SwathWidthYPewState[i][j][k],
									mode_wib->vba.BytePewPixewInDETY[k],
									mode_wib->vba.PwefiwwY[k],
									mode_wib->vba.MaxNumSwY[k],
									mode_wib->vba.PwefetchWinesC[0][0][k],
									mode_wib->vba.BytePewPixewInDETC[k],
									mode_wib->vba.PwefiwwC[k],
									mode_wib->vba.MaxNumSwC[k],
									mode_wib->vba.SwathHeightYPewState[i][j][k],
									mode_wib->vba.SwathHeightCPewState[i][j][k],
									mode_wib->vba.TWait,
									mode_wib->vba.XFCEnabwed[k],
									mode_wib->vba.XFCWemoteSuwfaceFwipDeway,
									mode_wib->vba.Intewwace[k],
									mode_wib->vba.PwogwessiveToIntewwaceUnitInOPP,
									mode_wib->vba.DSTXAftewScawew,
									mode_wib->vba.DSTYAftewScawew,
									&mode_wib->vba.WineTimesFowPwefetch[k],
									&mode_wib->vba.PwefetchBW[k],
									&mode_wib->vba.WinesFowMetaPTE[k],
									&mode_wib->vba.WinesFowMetaAndDPTEWow[k],
									&mode_wib->vba.VWatioPweY[i][j][k],
									&mode_wib->vba.VWatioPweC[i][j][k],
									&mode_wib->vba.WequiwedPwefetchPixewDataBWWuma[i][j][k],
									&mode_wib->vba.VStawtupWequiwedWhenNotEnoughTimeFowDynamicMetadata,
									&mode_wib->vba.Tno_bw[k],
									&mode_wib->vba.VUpdateOffsetPix[k],
									&mode_wib->vba.VUpdateWidthPix[k],
									&mode_wib->vba.VWeadyOffsetPix[k]);
				}
				mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch = 0.0;
				mode_wib->vba.MaximumWeadBandwidthWithPwefetch = 0.0;
				wocaws->pwefetch_vm_bw_vawid = twue;
				wocaws->pwefetch_wow_bw_vawid = twue;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if (wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k] == 0)
						wocaws->pwefetch_vm_bw[k] = 0;
					ewse if (wocaws->WinesFowMetaPTE[k] > 0)
						wocaws->pwefetch_vm_bw[k] = wocaws->PDEAndMetaPTEBytesPewFwame[0][0][k]
							/ (wocaws->WinesFowMetaPTE[k] * wocaws->HTotaw[k] / wocaws->PixewCwock[k]);
					ewse {
						wocaws->pwefetch_vm_bw[k] = 0;
						wocaws->pwefetch_vm_bw_vawid = fawse;
					}
					if (wocaws->MetaWowBytes[0][0][k] + wocaws->DPTEBytesPewWow[0][0][k] == 0)
						wocaws->pwefetch_wow_bw[k] = 0;
					ewse if (wocaws->WinesFowMetaAndDPTEWow[k] > 0)
						wocaws->pwefetch_wow_bw[k] = (wocaws->MetaWowBytes[0][0][k] + wocaws->DPTEBytesPewWow[0][0][k])
							/ (wocaws->WinesFowMetaAndDPTEWow[k] * wocaws->HTotaw[k] / wocaws->PixewCwock[k]);
					ewse {
						wocaws->pwefetch_wow_bw[k] = 0;
						wocaws->pwefetch_wow_bw_vawid = fawse;
					}

					mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch = mode_wib->vba.MaximumWeadBandwidthWithPwefetch
							+ mode_wib->vba.cuwsow_bw[k] + mode_wib->vba.WeadBandwidth[k] + mode_wib->vba.meta_wow_bw[k] + mode_wib->vba.dpte_wow_bw[k];
					mode_wib->vba.MaximumWeadBandwidthWithPwefetch =
							mode_wib->vba.MaximumWeadBandwidthWithPwefetch
									+ mode_wib->vba.cuwsow_bw[k]
									+ dmw_max3(
											mode_wib->vba.pwefetch_vm_bw[k],
											mode_wib->vba.pwefetch_wow_bw[k],
											dmw_max(mode_wib->vba.WeadBandwidth[k],
											mode_wib->vba.WequiwedPwefetchPixewDataBWWuma[i][j][k])
											+ mode_wib->vba.meta_wow_bw[k] + mode_wib->vba.dpte_wow_bw[k]);
				}
				wocaws->BandwidthWithoutPwefetchSuppowted[i][0] = twue;
				if (mode_wib->vba.MaximumWeadBandwidthWithoutPwefetch > wocaws->WetuwnBWPewState[i][0]) {
					wocaws->BandwidthWithoutPwefetchSuppowted[i][0] = fawse;
				}

				wocaws->PwefetchSuppowted[i][j] = twue;
				if (mode_wib->vba.MaximumWeadBandwidthWithPwefetch > wocaws->WetuwnBWPewState[i][0]) {
					wocaws->PwefetchSuppowted[i][j] = fawse;
				}
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if (wocaws->WineTimesFowPwefetch[k] < 2.0
							|| wocaws->WinesFowMetaPTE[k] >= 8.0
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
			} whiwe ((wocaws->PwefetchSuppowted[i][j] != twue || wocaws->VWatioInPwefetchSuppowted[i][j] != twue)
					&& mode_wib->vba.NextPwefetchMode < mode_wib->vba.MaxPwefetchMode);

			if (mode_wib->vba.PwefetchSuppowted[i][j] == twue
					&& mode_wib->vba.VWatioInPwefetchSuppowted[i][j] == twue) {
				mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip =
						mode_wib->vba.WetuwnBWPewState[i][0];
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip =
							mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip
									- mode_wib->vba.cuwsow_bw[k]
									- dmw_max(
											mode_wib->vba.WeadBandwidth[k] + mode_wib->vba.quaw_wow_bw[k],
											mode_wib->vba.PwefetchBW[k]);
				}
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					mode_wib->vba.ImmediateFwipBytes[k] = 0.0;
					if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_420_8
							&& mode_wib->vba.SouwcePixewFowmat[k] != dm_420_10)) {
						mode_wib->vba.ImmediateFwipBytes[k] =
								mode_wib->vba.PDEAndMetaPTEBytesPewFwame[0][0][k]
										+ mode_wib->vba.MetaWowBytes[0][0][k]
										+ mode_wib->vba.DPTEBytesPewWow[0][0][k];
					}
				}
				mode_wib->vba.TotImmediateFwipBytes = 0.0;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if ((mode_wib->vba.SouwcePixewFowmat[k] != dm_420_8
							&& mode_wib->vba.SouwcePixewFowmat[k] != dm_420_10)) {
						mode_wib->vba.TotImmediateFwipBytes =
								mode_wib->vba.TotImmediateFwipBytes
										+ mode_wib->vba.ImmediateFwipBytes[k];
					}
				}

				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					CawcuwateFwipScheduwe(
							mode_wib,
							mode_wib->vba.ExtwaWatency,
							mode_wib->vba.UwgentWatencyPixewDataOnwy,
							mode_wib->vba.GPUVMMaxPageTabweWevews,
							mode_wib->vba.GPUVMEnabwe,
							mode_wib->vba.BandwidthAvaiwabweFowImmediateFwip,
							mode_wib->vba.TotImmediateFwipBytes,
							mode_wib->vba.SouwcePixewFowmat[k],
							mode_wib->vba.ImmediateFwipBytes[k],
							mode_wib->vba.HTotaw[k]
									/ mode_wib->vba.PixewCwock[k],
							mode_wib->vba.VWatio[k],
							mode_wib->vba.Tno_bw[k],
							mode_wib->vba.PDEAndMetaPTEBytesPewFwame[0][0][k],
							mode_wib->vba.MetaWowBytes[0][0][k],
							mode_wib->vba.DPTEBytesPewWow[0][0][k],
							mode_wib->vba.DCCEnabwe[k],
							mode_wib->vba.dpte_wow_height[k],
							mode_wib->vba.meta_wow_height[k],
							mode_wib->vba.quaw_wow_bw[k],
							&mode_wib->vba.DestinationWinesToWequestVMInImmediateFwip[k],
							&mode_wib->vba.DestinationWinesToWequestWowInImmediateFwip[k],
							&mode_wib->vba.finaw_fwip_bw[k],
							&mode_wib->vba.ImmediateFwipSuppowtedFowPipe[k]);
				}
				mode_wib->vba.totaw_dcn_wead_bw_with_fwip = 0.0;
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					mode_wib->vba.totaw_dcn_wead_bw_with_fwip =
							mode_wib->vba.totaw_dcn_wead_bw_with_fwip
									+ mode_wib->vba.cuwsow_bw[k]
									+ dmw_max3(
											mode_wib->vba.pwefetch_vm_bw[k],
											mode_wib->vba.pwefetch_wow_bw[k],
											mode_wib->vba.finaw_fwip_bw[k]
													+ dmw_max(
															mode_wib->vba.WeadBandwidth[k],
															mode_wib->vba.WequiwedPwefetchPixewDataBWWuma[i][j][k]));
				}
				mode_wib->vba.ImmediateFwipSuppowtedFowState[i][j] = twue;
				if (mode_wib->vba.totaw_dcn_wead_bw_with_fwip
						> mode_wib->vba.WetuwnBWPewState[i][0]) {
					mode_wib->vba.ImmediateFwipSuppowtedFowState[i][j] = fawse;
				}
				fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
					if (mode_wib->vba.ImmediateFwipSuppowtedFowPipe[k] == fawse) {
						mode_wib->vba.ImmediateFwipSuppowtedFowState[i][j] = fawse;
					}
				}
			} ewse {
				mode_wib->vba.ImmediateFwipSuppowtedFowState[i][j] = fawse;
			}
		}
	}

	/*Vewticaw Active BW suppowt*/
	mode_wib->vba.MaxTotawVActiveWDBandwidth = 0;
	fow (k = 0; k < mode_wib->vba.NumbewOfActivePwanes; k++)
		mode_wib->vba.MaxTotawVActiveWDBandwidth = mode_wib->vba.MaxTotawVActiveWDBandwidth + mode_wib->vba.WeadBandwidth[k];
	fow (i = 0; i <= mode_wib->vba.soc.num_states; i++) {
		mode_wib->vba.MaxTotawVewticawActiveAvaiwabweBandwidth[i][0] = dmw_min(mode_wib->vba.WetuwnBusWidth *
				mode_wib->vba.DCFCWKPewState[i], mode_wib->vba.FabwicAndDWAMBandwidthPewState[i] * 1000) *
				mode_wib->vba.MaxAvewagePewcentOfIdeawDWAMBWDispwayCanUseInNowmawSystemOpewation / 100;
		if (mode_wib->vba.MaxTotawVActiveWDBandwidth <= mode_wib->vba.MaxTotawVewticawActiveAvaiwabweBandwidth[i][0])
			mode_wib->vba.TotawVewticawActiveBandwidthSuppowt[i][0] = twue;
		ewse
			mode_wib->vba.TotawVewticawActiveBandwidthSuppowt[i][0] = fawse;
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
		fow (j = 0; j < 2; j++) {
			if (mode_wib->vba.CuwsowWidth[k][j] > 0.0) {
				if (dmw_fwoow(
						dmw_fwoow(
								mode_wib->vba.CuwsowBuffewSize
										- mode_wib->vba.CuwsowChunkSize,
								mode_wib->vba.CuwsowChunkSize) * 1024.0
								/ (mode_wib->vba.CuwsowWidth[k][j]
										* mode_wib->vba.CuwsowBPP[k][j]
										/ 8.0),
						1.0)
						* (mode_wib->vba.HTotaw[k] / mode_wib->vba.PixewCwock[k])
						/ mode_wib->vba.VWatio[k] < mode_wib->vba.UwgentWatencyPixewDataOnwy
						|| (mode_wib->vba.CuwsowBPP[k][j] == 64.0
								&& mode_wib->vba.Cuwsow64BppSuppowt == fawse)) {
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

			if (mode_wib->vba.ScaweWatioAndTapsSuppowt != twue) {
				status = DMW_FAIW_SCAWE_WATIO_TAP;
			} ewse if (mode_wib->vba.SouwceFowmatPixewAndScanSuppowt != twue) {
				status = DMW_FAIW_SOUWCE_PIXEW_FOWMAT;
			} ewse if (wocaws->ViewpowtSizeSuppowt[i][0] != twue) {
				status = DMW_FAIW_VIEWPOWT_SIZE;
			} ewse if (wocaws->DIOSuppowt[i] != twue) {
				status = DMW_FAIW_DIO_SUPPOWT;
			} ewse if (wocaws->NotEnoughDSCUnits[i] != fawse) {
				status = DMW_FAIW_NOT_ENOUGH_DSC;
			} ewse if (wocaws->DSCCWKWequiwedMoweThanSuppowted[i] != fawse) {
				status = DMW_FAIW_DSC_CWK_WEQUIWED;
			} ewse if (wocaws->UwgentWatencySuppowt[i][j] != twue) {
				status = DMW_FAIW_UWGENT_WATENCY;
			} ewse if (wocaws->WOBSuppowt[i][0] != twue) {
				status = DMW_FAIW_WEOWDEWING_BUFFEW;
			} ewse if (wocaws->DISPCWK_DPPCWK_Suppowt[i][j] != twue) {
				status = DMW_FAIW_DISPCWK_DPPCWK;
			} ewse if (wocaws->TotawAvaiwabwePipesSuppowt[i][j] != twue) {
				status = DMW_FAIW_TOTAW_AVAIWABWE_PIPES;
			} ewse if (mode_wib->vba.NumbewOfOTGSuppowt != twue) {
				status = DMW_FAIW_NUM_OTG;
			} ewse if (mode_wib->vba.WwitebackModeSuppowt != twue) {
				status = DMW_FAIW_WWITEBACK_MODE;
			} ewse if (mode_wib->vba.WwitebackWatencySuppowt != twue) {
				status = DMW_FAIW_WWITEBACK_WATENCY;
			} ewse if (mode_wib->vba.WwitebackScaweWatioAndTapsSuppowt != twue) {
				status = DMW_FAIW_WWITEBACK_SCAWE_WATIO_TAP;
			} ewse if (mode_wib->vba.CuwsowSuppowt != twue) {
				status = DMW_FAIW_CUWSOW_SUPPOWT;
			} ewse if (mode_wib->vba.PitchSuppowt != twue) {
				status = DMW_FAIW_PITCH_SUPPOWT;
			} ewse if (wocaws->PwefetchSuppowted[i][j] != twue) {
				status = DMW_FAIW_PWEFETCH_SUPPOWT;
			} ewse if (wocaws->TotawVewticawActiveBandwidthSuppowt[i][0] != twue) {
				status = DMW_FAIW_TOTAW_V_ACTIVE_BW;
			} ewse if (wocaws->VWatioInPwefetchSuppowted[i][j] != twue) {
				status = DMW_FAIW_V_WATIO_PWEFETCH;
			} ewse if (wocaws->PTEBuffewSizeNotExceeded[i][j] != twue) {
				status = DMW_FAIW_PTE_BUFFEW_SIZE;
			} ewse if (mode_wib->vba.NonsuppowtedDSCInputBPC != fawse) {
				status = DMW_FAIW_DSC_INPUT_BPC;
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
						|| mode_wib->vba.WhenToDoMPCCombine == dm_mpc_awways_when_possibwe)) {
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
	mode_wib->vba.FabwicAndDWAMBandwidth = wocaws->FabwicAndDWAMBandwidthPewState[mode_wib->vba.VowtageWevew];
	fow (k = 0; k <= mode_wib->vba.NumbewOfActivePwanes - 1; k++) {
		if (mode_wib->vba.BwendingAndTiming[k] == k) {
			mode_wib->vba.ODMCombineEnabwed[k] =
					wocaws->ODMCombineEnabwePewState[mode_wib->vba.VowtageWevew][k];
		} ewse {
			mode_wib->vba.ODMCombineEnabwed[k] = 0;
		}
		mode_wib->vba.DSCEnabwed[k] =
				wocaws->WequiwesDSC[mode_wib->vba.VowtageWevew][k];
		mode_wib->vba.OutputBpp[k] =
				wocaws->OutputBppPewState[mode_wib->vba.VowtageWevew][k];
	}
}
