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
#incwude "dispway_mode_vba_utiw_32.h"
#incwude "../dmw_inwine_defs.h"
#incwude "dispway_mode_vba_32.h"
#incwude "../dispway_mode_wib.h"

#define DCN32_MAX_FMT_420_BUFFEW_WIDTH 4096

unsigned int dmw32_dscceComputeDeway(
		unsigned int bpc,
		doubwe BPP,
		unsigned int swiceWidth,
		unsigned int numSwices,
		enum output_fowmat_cwass pixewFowmat,
		enum output_encodew_cwass Output)
{
	// vawid bpc         = souwce bits pew component in the set of {8, 10, 12}
	// vawid bpp         = incwements of 1/16 of a bit
	//                    min = 6/7/8 in N420/N422/444, wespectivewy
	//                    max = such that compwession is 1:1
	//vawid swiceWidth  = numbew of pixews pew swice wine,
	//	must be wess than ow equaw to 5184/numSwices (ow 4096/numSwices in 420 mode)
	//vawid numSwices   = numbew of swices in the howiziontaw diwection pew DSC engine in the set of {1, 2, 3, 4}
	//vawid pixewFowmat = pixew/cowow fowmat in the set of {:N444_WGB, :S422, :N422, :N420}

	// fixed vawue
	unsigned int wcModewSize = 8192;

	// N422/N420 opewate at 2 pixews pew cwock
	unsigned int pixewsPewCwock, wstaww, D, initawXmitDeway, w, s, ix, wx, p, w0, a, ax, W,
	Deway, pixews;

	if (pixewFowmat == dm_420)
		pixewsPewCwock = 2;
	ewse if (pixewFowmat == dm_n422)
		pixewsPewCwock = 2;
	// #aww othew modes opewate at 1 pixew pew cwock
	ewse
		pixewsPewCwock = 1;

	//initiaw twansmit deway as pew PPS
	initawXmitDeway = dmw_wound(wcModewSize / 2.0 / BPP / pixewsPewCwock);

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
	if (pixewFowmat == dm_420 || pixewFowmat == dm_444 || pixewFowmat == dm_n422)
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
	dmw_pwint("DMW::%s: bpc: %d\n", __func__, bpc);
	dmw_pwint("DMW::%s: BPP: %f\n", __func__, BPP);
	dmw_pwint("DMW::%s: swiceWidth: %d\n", __func__, swiceWidth);
	dmw_pwint("DMW::%s: numSwices: %d\n", __func__, numSwices);
	dmw_pwint("DMW::%s: pixewFowmat: %d\n", __func__, pixewFowmat);
	dmw_pwint("DMW::%s: Output: %d\n", __func__, Output);
	dmw_pwint("DMW::%s: pixews: %d\n", __func__, pixews);
#endif

	wetuwn pixews;
}

unsigned int dmw32_dscComputeDeway(enum output_fowmat_cwass pixewFowmat, enum output_encodew_cwass Output)
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
	} ewse if (pixewFowmat == dm_n422 || (pixewFowmat != dm_444)) {
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


boow IsVewticaw(enum dm_wotation_angwe Scan)
{
	boow is_vewt = fawse;

	if (Scan == dm_wotation_90 || Scan == dm_wotation_90m || Scan == dm_wotation_270 || Scan == dm_wotation_270m)
		is_vewt = twue;
	ewse
		is_vewt = fawse;
	wetuwn is_vewt;
}

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
		doubwe *DPPCWKUsingSingweDPP)
{
	doubwe DPPCWKUsingSingweDPPWuma;
	doubwe DPPCWKUsingSingweDPPChwoma;

	if (HWatio > 1) {
		*PSCW_THWOUGHPUT = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput * HWatio /
				dmw_ceiw((doubwe) HTaps / 6.0, 1.0));
	} ewse {
		*PSCW_THWOUGHPUT = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput);
	}

	DPPCWKUsingSingweDPPWuma = PixewCwock * dmw_max3(VTaps / 6 * dmw_min(1, HWatio), HWatio * VWatio /
			*PSCW_THWOUGHPUT, 1);

	if ((HTaps > 6 || VTaps > 6) && DPPCWKUsingSingweDPPWuma < 2 * PixewCwock)
		DPPCWKUsingSingweDPPWuma = 2 * PixewCwock;

	if ((SouwcePixewFowmat != dm_420_8 && SouwcePixewFowmat != dm_420_10 && SouwcePixewFowmat != dm_420_12 &&
			SouwcePixewFowmat != dm_wgbe_awpha)) {
		*PSCW_THWOUGHPUT_CHWOMA = 0;
		*DPPCWKUsingSingweDPP = DPPCWKUsingSingweDPPWuma;
	} ewse {
		if (HWatioChwoma > 1) {
			*PSCW_THWOUGHPUT_CHWOMA = dmw_min(MaxDCHUBToPSCWThwoughput, MaxPSCWToWBThwoughput *
					HWatioChwoma / dmw_ceiw((doubwe) HTapsChwoma / 6.0, 1.0));
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

void dmw32_CawcuwateBytePewPixewAndBwockSizes(
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		enum dm_swizzwe_mode SuwfaceTiwing,

		/* Output */
		unsigned int *BytePewPixewY,
		unsigned int *BytePewPixewC,
		doubwe  *BytePewPixewDETY,
		doubwe  *BytePewPixewDETC,
		unsigned int *BwockHeight256BytesY,
		unsigned int *BwockHeight256BytesC,
		unsigned int *BwockWidth256BytesY,
		unsigned int *BwockWidth256BytesC,
		unsigned int *MacwoTiweHeightY,
		unsigned int *MacwoTiweHeightC,
		unsigned int *MacwoTiweWidthY,
		unsigned int *MacwoTiweWidthC)
{
	if (SouwcePixewFowmat == dm_444_64) {
		*BytePewPixewDETY = 8;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 8;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dm_444_32 || SouwcePixewFowmat == dm_wgbe) {
		*BytePewPixewDETY = 4;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 4;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dm_444_16) {
		*BytePewPixewDETY = 2;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 2;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dm_444_8) {
		*BytePewPixewDETY = 1;
		*BytePewPixewDETC = 0;
		*BytePewPixewY = 1;
		*BytePewPixewC = 0;
	} ewse if (SouwcePixewFowmat == dm_wgbe_awpha) {
		*BytePewPixewDETY = 4;
		*BytePewPixewDETC = 1;
		*BytePewPixewY = 4;
		*BytePewPixewC = 1;
	} ewse if (SouwcePixewFowmat == dm_420_8) {
		*BytePewPixewDETY = 1;
		*BytePewPixewDETC = 2;
		*BytePewPixewY = 1;
		*BytePewPixewC = 2;
	} ewse if (SouwcePixewFowmat == dm_420_12) {
		*BytePewPixewDETY = 2;
		*BytePewPixewDETC = 4;
		*BytePewPixewY = 2;
		*BytePewPixewC = 4;
	} ewse {
		*BytePewPixewDETY = 4.0 / 3;
		*BytePewPixewDETC = 8.0 / 3;
		*BytePewPixewY = 2;
		*BytePewPixewC = 4;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: SouwcePixewFowmat = %d\n", __func__, SouwcePixewFowmat);
	dmw_pwint("DMW::%s: BytePewPixewDETY = %f\n", __func__, *BytePewPixewDETY);
	dmw_pwint("DMW::%s: BytePewPixewDETC = %f\n", __func__, *BytePewPixewDETC);
	dmw_pwint("DMW::%s: BytePewPixewY    = %d\n", __func__, *BytePewPixewY);
	dmw_pwint("DMW::%s: BytePewPixewC    = %d\n", __func__, *BytePewPixewC);
#endif
	if ((SouwcePixewFowmat == dm_444_64 || SouwcePixewFowmat == dm_444_32
			|| SouwcePixewFowmat == dm_444_16
			|| SouwcePixewFowmat == dm_444_8
			|| SouwcePixewFowmat == dm_mono_16
			|| SouwcePixewFowmat == dm_mono_8
			|| SouwcePixewFowmat == dm_wgbe)) {
		if (SuwfaceTiwing == dm_sw_wineaw)
			*BwockHeight256BytesY = 1;
		ewse if (SouwcePixewFowmat == dm_444_64)
			*BwockHeight256BytesY = 4;
		ewse if (SouwcePixewFowmat == dm_444_8)
			*BwockHeight256BytesY = 16;
		ewse
			*BwockHeight256BytesY = 8;

		*BwockWidth256BytesY = 256U / *BytePewPixewY / *BwockHeight256BytesY;
		*BwockHeight256BytesC = 0;
		*BwockWidth256BytesC = 0;
	} ewse {
		if (SuwfaceTiwing == dm_sw_wineaw) {
			*BwockHeight256BytesY = 1;
			*BwockHeight256BytesC = 1;
		} ewse if (SouwcePixewFowmat == dm_wgbe_awpha) {
			*BwockHeight256BytesY = 8;
			*BwockHeight256BytesC = 16;
		} ewse if (SouwcePixewFowmat == dm_420_8) {
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
	dmw_pwint("DMW::%s: BwockWidth256BytesY  = %d\n", __func__, *BwockWidth256BytesY);
	dmw_pwint("DMW::%s: BwockHeight256BytesY = %d\n", __func__, *BwockHeight256BytesY);
	dmw_pwint("DMW::%s: BwockWidth256BytesC  = %d\n", __func__, *BwockWidth256BytesC);
	dmw_pwint("DMW::%s: BwockHeight256BytesC = %d\n", __func__, *BwockHeight256BytesC);
#endif

	if (SuwfaceTiwing == dm_sw_wineaw) {
		*MacwoTiweHeightY = *BwockHeight256BytesY;
		*MacwoTiweWidthY = 256 / *BytePewPixewY / *MacwoTiweHeightY;
		*MacwoTiweHeightC = *BwockHeight256BytesC;
		if (*MacwoTiweHeightC == 0)
			*MacwoTiweWidthC = 0;
		ewse
			*MacwoTiweWidthC = 256 / *BytePewPixewC / *MacwoTiweHeightC;
	} ewse if (SuwfaceTiwing == dm_sw_64kb_d || SuwfaceTiwing == dm_sw_64kb_d_t ||
			SuwfaceTiwing == dm_sw_64kb_d_x || SuwfaceTiwing == dm_sw_64kb_w_x) {
		*MacwoTiweHeightY = 16 * *BwockHeight256BytesY;
		*MacwoTiweWidthY = 65536 / *BytePewPixewY / *MacwoTiweHeightY;
		*MacwoTiweHeightC = 16 * *BwockHeight256BytesC;
		if (*MacwoTiweHeightC == 0)
			*MacwoTiweWidthC = 0;
		ewse
			*MacwoTiweWidthC = 65536 / *BytePewPixewC / *MacwoTiweHeightC;
	} ewse {
		*MacwoTiweHeightY = 32 * *BwockHeight256BytesY;
		*MacwoTiweWidthY = 65536 * 4 / *BytePewPixewY / *MacwoTiweHeightY;
		*MacwoTiweHeightC = 32 * *BwockHeight256BytesC;
		if (*MacwoTiweHeightC == 0)
			*MacwoTiweWidthC = 0;
		ewse
			*MacwoTiweWidthC = 65536 * 4 / *BytePewPixewC / *MacwoTiweHeightC;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: MacwoTiweWidthY  = %d\n", __func__, *MacwoTiweWidthY);
	dmw_pwint("DMW::%s: MacwoTiweHeightY = %d\n", __func__, *MacwoTiweHeightY);
	dmw_pwint("DMW::%s: MacwoTiweWidthC  = %d\n", __func__, *MacwoTiweWidthC);
	dmw_pwint("DMW::%s: MacwoTiweHeightC = %d\n", __func__, *MacwoTiweHeightC);
#endif
} // CawcuwateBytePewPixewAndBwockSizes

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
		boow *ViewpowtSizeSuppowt)
{
	unsigned int MaximumSwathHeightY[DC__NUM_DPP__MAX];
	unsigned int MaximumSwathHeightC[DC__NUM_DPP__MAX];
	unsigned int WoundedUpMaxSwathSizeBytesY[DC__NUM_DPP__MAX];
	unsigned int WoundedUpMaxSwathSizeBytesC[DC__NUM_DPP__MAX];
	unsigned int WoundedUpSwathSizeBytesY;
	unsigned int WoundedUpSwathSizeBytesC;
	doubwe SwathWidthdoubweDPP[DC__NUM_DPP__MAX];
	doubwe SwathWidthdoubweDPPChwoma[DC__NUM_DPP__MAX];
	unsigned int k;
	unsigned int TotawActiveDPP = 0;
	boow NoChwomaSuwfaces = twue;
	unsigned int DETBuffewSizeInKByteFowSwathCawcuwation;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: FowceSingweDPP = %d\n", __func__, FowceSingweDPP);
	dmw_pwint("DMW::%s: WOBSizeKBytes = %d\n", __func__, WOBSizeKBytes);
	dmw_pwint("DMW::%s: PixewChunkSizeKBytes = %d\n", __func__, PixewChunkSizeKBytes);
#endif
	dmw32_CawcuwateSwathWidth(FowceSingweDPP,
			NumbewOfActiveSuwfaces,
			SouwcePixewFowmat,
			SouwceWotation,
			ViewpowtStationawy,
			ViewpowtWidth,
			ViewpowtHeight,
			ViewpowtXStawt,
			ViewpowtYStawt,
			ViewpowtXStawtC,
			ViewpowtYStawtC,
			SuwfaceWidthY,
			SuwfaceWidthC,
			SuwfaceHeightY,
			SuwfaceHeightC,
			ODMMode,
			BytePewPixY,
			BytePewPixC,
			Wead256BytesBwockHeightY,
			Wead256BytesBwockHeightC,
			Wead256BytesBwockWidthY,
			Wead256BytesBwockWidthC,
			BwendingAndTiming,
			HActive,
			HWatio,
			DPPPewSuwface,

			/* Output */
			SwathWidthdoubweDPP,
			SwathWidthdoubweDPPChwoma,
			SwathWidth,
			SwathWidthChwoma,
			MaximumSwathHeightY,
			MaximumSwathHeightC,
			swath_width_wuma_ub,
			swath_width_chwoma_ub);

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		WoundedUpMaxSwathSizeBytesY[k] = swath_width_wuma_ub[k] * BytePewPixDETY[k] * MaximumSwathHeightY[k];
		WoundedUpMaxSwathSizeBytesC[k] = swath_width_chwoma_ub[k] * BytePewPixDETC[k] * MaximumSwathHeightC[k];
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%0d DPPPewSuwface = %d\n", __func__, k, DPPPewSuwface[k]);
		dmw_pwint("DMW::%s: k=%0d swath_width_wuma_ub = %d\n", __func__, k, swath_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%0d BytePewPixDETY = %f\n", __func__, k, BytePewPixDETY[k]);
		dmw_pwint("DMW::%s: k=%0d MaximumSwathHeightY = %d\n", __func__, k, MaximumSwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%0d WoundedUpMaxSwathSizeBytesY = %d\n", __func__, k,
				WoundedUpMaxSwathSizeBytesY[k]);
		dmw_pwint("DMW::%s: k=%0d swath_width_chwoma_ub = %d\n", __func__, k, swath_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%0d BytePewPixDETC = %f\n", __func__, k, BytePewPixDETC[k]);
		dmw_pwint("DMW::%s: k=%0d MaximumSwathHeightC = %d\n", __func__, k, MaximumSwathHeightC[k]);
		dmw_pwint("DMW::%s: k=%0d WoundedUpMaxSwathSizeBytesC = %d\n", __func__, k,
				WoundedUpMaxSwathSizeBytesC[k]);
#endif

		if (SouwcePixewFowmat[k] == dm_420_10) {
			WoundedUpMaxSwathSizeBytesY[k] = dmw_ceiw((unsigned int) WoundedUpMaxSwathSizeBytesY[k], 256);
			WoundedUpMaxSwathSizeBytesC[k] = dmw_ceiw((unsigned int) WoundedUpMaxSwathSizeBytesC[k], 256);
		}
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		TotawActiveDPP = TotawActiveDPP + (FowceSingweDPP ? 1 : DPPPewSuwface[k]);
		if (SouwcePixewFowmat[k] == dm_420_8 || SouwcePixewFowmat[k] == dm_420_10 ||
				SouwcePixewFowmat[k] == dm_420_12 || SouwcePixewFowmat[k] == dm_wgbe_awpha) {
			NoChwomaSuwfaces = fawse;
		}
	}

	// By defauwt, just set the wesewved space to 2 pixew chunks size
	*CompBufWesewvedSpaceKBytes = PixewChunkSizeKBytes * 2;

	// if unbounded weq is enabwed, pwogwam wesewved space such that the WOB wiww not howd mowe than 8 swaths wowth of data
	// - assume wowst-case compwession wate of 4. [WOB size - 8 * swath_size / max_compwession watio]
	// - assume fow "nawwow" vp case in which the WOB can fit 8 swaths, the DET shouwd be big enough to do fuww size weq
	*CompBufWesewvedSpaceNeedAdjustment = ((int) WOBSizeKBytes - (int) *CompBufWesewvedSpaceKBytes) > (int) (WoundedUpMaxSwathSizeBytesY[0]/512);

	if (*CompBufWesewvedSpaceNeedAdjustment == 1) {
		*CompBufWesewvedSpaceKBytes = WOBSizeKBytes - WoundedUpMaxSwathSizeBytesY[0]/512;
	}

	#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: CompBufWesewvedSpaceKBytes          = %d\n",  __func__, *CompBufWesewvedSpaceKBytes);
		dmw_pwint("DMW::%s: CompBufWesewvedSpaceNeedAdjustment  = %d\n",  __func__, *CompBufWesewvedSpaceNeedAdjustment);
	#endif

	*UnboundedWequestEnabwed = dmw32_UnboundedWequest(UseUnboundedWequestingFinaw, TotawActiveDPP, NoChwomaSuwfaces, Output[0], SuwfaceTiwing[0], *CompBufWesewvedSpaceNeedAdjustment, DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment);

	dmw32_CawcuwateDETBuffewSize(DETSizeOvewwide,
			UseMAWWFowPStateChange,
			FowceSingweDPP,
			NumbewOfActiveSuwfaces,
			*UnboundedWequestEnabwed,
			nomDETInKByte,
			MaxTotawDETInKByte,
			ConfigWetuwnBuffewSizeInKByte,
			MinCompwessedBuffewSizeInKByte,
			CompwessedBuffewSegmentSizeInkByteFinaw,
			SouwcePixewFowmat,
			WeadBandwidthWuma,
			WeadBandwidthChwoma,
			WoundedUpMaxSwathSizeBytesY,
			WoundedUpMaxSwathSizeBytesC,
			DPPPewSuwface,

			/* Output */
			DETBuffewSizeInKByte,    // pew hubp pipe
			CompwessedBuffewSizeInkByte);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: TotawActiveDPP = %d\n", __func__, TotawActiveDPP);
	dmw_pwint("DMW::%s: nomDETInKByte = %d\n", __func__, nomDETInKByte);
	dmw_pwint("DMW::%s: ConfigWetuwnBuffewSizeInKByte = %d\n", __func__, ConfigWetuwnBuffewSizeInKByte);
	dmw_pwint("DMW::%s: UseUnboundedWequestingFinaw = %d\n", __func__, UseUnboundedWequestingFinaw);
	dmw_pwint("DMW::%s: UnboundedWequestEnabwed = %d\n", __func__, *UnboundedWequestEnabwed);
	dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte = %d\n", __func__, *CompwessedBuffewSizeInkByte);
#endif

	*ViewpowtSizeSuppowt = twue;
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {

		DETBuffewSizeInKByteFowSwathCawcuwation = (UseMAWWFowPStateChange[k] ==
				dm_use_maww_pstate_change_phantom_pipe ? 1024 : DETBuffewSizeInKByte[k]);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%0d DETBuffewSizeInKByteFowSwathCawcuwation = %d\n", __func__, k,
				DETBuffewSizeInKByteFowSwathCawcuwation);
#endif

		if (WoundedUpMaxSwathSizeBytesY[k] + WoundedUpMaxSwathSizeBytesC[k] <=
				DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) {
			SwathHeightY[k] = MaximumSwathHeightY[k];
			SwathHeightC[k] = MaximumSwathHeightC[k];
			WoundedUpSwathSizeBytesY = WoundedUpMaxSwathSizeBytesY[k];
			WoundedUpSwathSizeBytesC = WoundedUpMaxSwathSizeBytesC[k];
		} ewse if (WoundedUpMaxSwathSizeBytesY[k] >= 1.5 * WoundedUpMaxSwathSizeBytesC[k] &&
				WoundedUpMaxSwathSizeBytesY[k] / 2 + WoundedUpMaxSwathSizeBytesC[k] <=
				DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) {
			SwathHeightY[k] = MaximumSwathHeightY[k] / 2;
			SwathHeightC[k] = MaximumSwathHeightC[k];
			WoundedUpSwathSizeBytesY = WoundedUpMaxSwathSizeBytesY[k] / 2;
			WoundedUpSwathSizeBytesC = WoundedUpMaxSwathSizeBytesC[k];
		} ewse if (WoundedUpMaxSwathSizeBytesY[k] < 1.5 * WoundedUpMaxSwathSizeBytesC[k] &&
				WoundedUpMaxSwathSizeBytesY[k] + WoundedUpMaxSwathSizeBytesC[k] / 2 <=
				DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2) {
			SwathHeightY[k] = MaximumSwathHeightY[k];
			SwathHeightC[k] = MaximumSwathHeightC[k] / 2;
			WoundedUpSwathSizeBytesY = WoundedUpMaxSwathSizeBytesY[k];
			WoundedUpSwathSizeBytesC = WoundedUpMaxSwathSizeBytesC[k] / 2;
		} ewse {
			SwathHeightY[k] = MaximumSwathHeightY[k] / 2;
			SwathHeightC[k] = MaximumSwathHeightC[k] / 2;
			WoundedUpSwathSizeBytesY = WoundedUpMaxSwathSizeBytesY[k] / 2;
			WoundedUpSwathSizeBytesC = WoundedUpMaxSwathSizeBytesC[k] / 2;
		}

		if ((WoundedUpMaxSwathSizeBytesY[k] / 2 + WoundedUpMaxSwathSizeBytesC[k] / 2 >
				DETBuffewSizeInKByteFowSwathCawcuwation * 1024 / 2)
				|| SwathWidth[k] > MaximumSwathWidthWuma[k] || (SwathHeightC[k] > 0 &&
						SwathWidthChwoma[k] > MaximumSwathWidthChwoma[k])) {
			*ViewpowtSizeSuppowt = fawse;
			ViewpowtSizeSuppowtPewSuwface[k] = fawse;
		} ewse {
			ViewpowtSizeSuppowtPewSuwface[k] = twue;
		}

		if (SwathHeightC[k] == 0) {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0d Aww DET fow pwane0\n", __func__, k);
#endif
			DETBuffewSizeY[k] = DETBuffewSizeInKByte[k] * 1024;
			DETBuffewSizeC[k] = 0;
		} ewse if (WoundedUpSwathSizeBytesY <= 1.5 * WoundedUpSwathSizeBytesC) {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0d Hawf DET fow pwane0, hawf fow pwane1\n", __func__, k);
#endif
			DETBuffewSizeY[k] = DETBuffewSizeInKByte[k] * 1024 / 2;
			DETBuffewSizeC[k] = DETBuffewSizeInKByte[k] * 1024 / 2;
		} ewse {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0d 2/3 DET fow pwane0, 1/3 fow pwane1\n", __func__, k);
#endif
			DETBuffewSizeY[k] = dmw_fwoow(DETBuffewSizeInKByte[k] * 1024 * 2 / 3, 1024);
			DETBuffewSizeC[k] = DETBuffewSizeInKByte[k] * 1024 - DETBuffewSizeY[k];
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%0d SwathHeightY = %d\n", __func__, k, SwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%0d SwathHeightC = %d\n", __func__, k, SwathHeightC[k]);
		dmw_pwint("DMW::%s: k=%0d WoundedUpMaxSwathSizeBytesY = %d\n", __func__,
				k, WoundedUpMaxSwathSizeBytesY[k]);
		dmw_pwint("DMW::%s: k=%0d WoundedUpMaxSwathSizeBytesC = %d\n", __func__,
				k, WoundedUpMaxSwathSizeBytesC[k]);
		dmw_pwint("DMW::%s: k=%0d WoundedUpSwathSizeBytesY = %d\n", __func__, k, WoundedUpSwathSizeBytesY);
		dmw_pwint("DMW::%s: k=%0d WoundedUpSwathSizeBytesC = %d\n", __func__, k, WoundedUpSwathSizeBytesC);
		dmw_pwint("DMW::%s: k=%0d DETBuffewSizeInKByte = %d\n", __func__, k, DETBuffewSizeInKByte[k]);
		dmw_pwint("DMW::%s: k=%0d DETBuffewSizeY = %d\n", __func__, k, DETBuffewSizeY[k]);
		dmw_pwint("DMW::%s: k=%0d DETBuffewSizeC = %d\n", __func__, k, DETBuffewSizeC[k]);
		dmw_pwint("DMW::%s: k=%0d ViewpowtSizeSuppowtPewSuwface = %d\n", __func__, k,
				ViewpowtSizeSuppowtPewSuwface[k]);
#endif

	}
} // CawcuwateSwathAndDETConfiguwation

void dmw32_CawcuwateSwathWidth(
		boow				FowceSingweDPP,
		unsigned int			NumbewOfActiveSuwfaces,
		enum souwce_fowmat_cwass	SouwcePixewFowmat[],
		enum dm_wotation_angwe		SouwceWotation[],
		boow				ViewpowtStationawy[],
		unsigned int			ViewpowtWidth[],
		unsigned int			ViewpowtHeight[],
		unsigned int			ViewpowtXStawt[],
		unsigned int			ViewpowtYStawt[],
		unsigned int			ViewpowtXStawtC[],
		unsigned int			ViewpowtYStawtC[],
		unsigned int			SuwfaceWidthY[],
		unsigned int			SuwfaceWidthC[],
		unsigned int			SuwfaceHeightY[],
		unsigned int			SuwfaceHeightC[],
		enum odm_combine_mode		ODMMode[],
		unsigned int			BytePewPixY[],
		unsigned int			BytePewPixC[],
		unsigned int			Wead256BytesBwockHeightY[],
		unsigned int			Wead256BytesBwockHeightC[],
		unsigned int			Wead256BytesBwockWidthY[],
		unsigned int			Wead256BytesBwockWidthC[],
		unsigned int			BwendingAndTiming[],
		unsigned int			HActive[],
		doubwe				HWatio[],
		unsigned int			DPPPewSuwface[],

		/* Output */
		doubwe				SwathWidthdoubweDPPY[],
		doubwe				SwathWidthdoubweDPPC[],
		doubwe				SwathWidthY[], // pew-pipe
		doubwe				SwathWidthC[], // pew-pipe
		unsigned int			MaximumSwathHeightY[],
		unsigned int			MaximumSwathHeightC[],
		unsigned int			swath_width_wuma_ub[], // pew-pipe
		unsigned int			swath_width_chwoma_ub[]) // pew-pipe
{
	unsigned int k, j;
	enum odm_combine_mode MainSuwfaceODMMode;

	unsigned int suwface_width_ub_w;
	unsigned int suwface_height_ub_w;
	unsigned int suwface_width_ub_c = 0;
	unsigned int suwface_height_ub_c = 0;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: FowceSingweDPP = %d\n", __func__, FowceSingweDPP);
	dmw_pwint("DMW::%s: NumbewOfActiveSuwfaces = %d\n", __func__, NumbewOfActiveSuwfaces);
#endif

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (!IsVewticaw(SouwceWotation[k]))
			SwathWidthdoubweDPPY[k] = ViewpowtWidth[k];
		ewse
			SwathWidthdoubweDPPY[k] = ViewpowtHeight[k];

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d ViewpowtWidth=%d\n", __func__, k, ViewpowtWidth[k]);
		dmw_pwint("DMW::%s: k=%d ViewpowtHeight=%d\n", __func__, k, ViewpowtHeight[k]);
#endif

		MainSuwfaceODMMode = ODMMode[k];
		fow (j = 0; j < NumbewOfActiveSuwfaces; ++j) {
			if (BwendingAndTiming[k] == j)
				MainSuwfaceODMMode = ODMMode[j];
		}

		if (FowceSingweDPP) {
			SwathWidthY[k] = SwathWidthdoubweDPPY[k];
		} ewse {
			if (MainSuwfaceODMMode == dm_odm_combine_mode_4to1) {
				SwathWidthY[k] = dmw_min(SwathWidthdoubweDPPY[k],
						dmw_wound(HActive[k] / 4.0 * HWatio[k]));
			} ewse if (MainSuwfaceODMMode == dm_odm_combine_mode_2to1) {
				SwathWidthY[k] = dmw_min(SwathWidthdoubweDPPY[k],
						dmw_wound(HActive[k] / 2.0 * HWatio[k]));
			} ewse if (DPPPewSuwface[k] == 2) {
				SwathWidthY[k] = SwathWidthdoubweDPPY[k] / 2;
			} ewse {
				SwathWidthY[k] = SwathWidthdoubweDPPY[k];
			}
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d HActive=%d\n", __func__, k, HActive[k]);
		dmw_pwint("DMW::%s: k=%d HWatio=%f\n", __func__, k, HWatio[k]);
		dmw_pwint("DMW::%s: k=%d MainSuwfaceODMMode=%d\n", __func__, k, MainSuwfaceODMMode);
		dmw_pwint("DMW::%s: k=%d SwathWidthdoubweDPPY=%d\n", __func__, k, SwathWidthdoubweDPPY[k]);
		dmw_pwint("DMW::%s: k=%d SwathWidthY=%d\n", __func__, k, SwathWidthY[k]);
#endif

		if (SouwcePixewFowmat[k] == dm_420_8 || SouwcePixewFowmat[k] == dm_420_10 ||
				SouwcePixewFowmat[k] == dm_420_12) {
			SwathWidthC[k] = SwathWidthY[k] / 2;
			SwathWidthdoubweDPPC[k] = SwathWidthdoubweDPPY[k] / 2;
		} ewse {
			SwathWidthC[k] = SwathWidthY[k];
			SwathWidthdoubweDPPC[k] = SwathWidthdoubweDPPY[k];
		}

		if (FowceSingweDPP == twue) {
			SwathWidthY[k] = SwathWidthdoubweDPPY[k];
			SwathWidthC[k] = SwathWidthdoubweDPPC[k];
		}

		suwface_width_ub_w  = dmw_ceiw(SuwfaceWidthY[k], Wead256BytesBwockWidthY[k]);
		suwface_height_ub_w = dmw_ceiw(SuwfaceHeightY[k], Wead256BytesBwockHeightY[k]);

		if (!IsVewticaw(SouwceWotation[k])) {
			MaximumSwathHeightY[k] = Wead256BytesBwockHeightY[k];
			MaximumSwathHeightC[k] = Wead256BytesBwockHeightC[k];
			if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
				swath_width_wuma_ub[k] = dmw_min(suwface_width_ub_w,
						dmw_fwoow(ViewpowtXStawt[k] +
								SwathWidthY[k] +
								Wead256BytesBwockWidthY[k] - 1,
								Wead256BytesBwockWidthY[k]) -
								dmw_fwoow(ViewpowtXStawt[k],
								Wead256BytesBwockWidthY[k]));
			} ewse {
				swath_width_wuma_ub[k] = dmw_min(suwface_width_ub_w,
						dmw_ceiw(SwathWidthY[k] - 1,
								Wead256BytesBwockWidthY[k]) +
								Wead256BytesBwockWidthY[k]);
			}
			if (BytePewPixC[k] > 0) {
				suwface_width_ub_c  = dmw_ceiw(SuwfaceWidthC[k], Wead256BytesBwockWidthC[k]);
				if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
					swath_width_chwoma_ub[k] = dmw_min(suwface_width_ub_c,
							dmw_fwoow(ViewpowtXStawtC[k] + SwathWidthC[k] +
									Wead256BytesBwockWidthC[k] - 1,
									Wead256BytesBwockWidthC[k]) -
									dmw_fwoow(ViewpowtXStawtC[k],
									Wead256BytesBwockWidthC[k]));
				} ewse {
					swath_width_chwoma_ub[k] = dmw_min(suwface_width_ub_c,
							dmw_ceiw(SwathWidthC[k] - 1,
								Wead256BytesBwockWidthC[k]) +
								Wead256BytesBwockWidthC[k]);
				}
			} ewse {
				swath_width_chwoma_ub[k] = 0;
			}
		} ewse {
			MaximumSwathHeightY[k] = Wead256BytesBwockWidthY[k];
			MaximumSwathHeightC[k] = Wead256BytesBwockWidthC[k];

			if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
				swath_width_wuma_ub[k] = dmw_min(suwface_height_ub_w, dmw_fwoow(ViewpowtYStawt[k] +
						SwathWidthY[k] + Wead256BytesBwockHeightY[k] - 1,
						Wead256BytesBwockHeightY[k]) -
						dmw_fwoow(ViewpowtYStawt[k], Wead256BytesBwockHeightY[k]));
			} ewse {
				swath_width_wuma_ub[k] = dmw_min(suwface_height_ub_w, dmw_ceiw(SwathWidthY[k] - 1,
						Wead256BytesBwockHeightY[k]) + Wead256BytesBwockHeightY[k]);
			}
			if (BytePewPixC[k] > 0) {
				suwface_height_ub_c = dmw_ceiw(SuwfaceHeightC[k], Wead256BytesBwockHeightC[k]);
				if (ViewpowtStationawy[k] && DPPPewSuwface[k] == 1) {
					swath_width_chwoma_ub[k] = dmw_min(suwface_height_ub_c,
							dmw_fwoow(ViewpowtYStawtC[k] + SwathWidthC[k] +
									Wead256BytesBwockHeightC[k] - 1,
									Wead256BytesBwockHeightC[k]) -
									dmw_fwoow(ViewpowtYStawtC[k],
											Wead256BytesBwockHeightC[k]));
				} ewse {
					swath_width_chwoma_ub[k] = dmw_min(suwface_height_ub_c,
							dmw_ceiw(SwathWidthC[k] - 1, Wead256BytesBwockHeightC[k]) +
							Wead256BytesBwockHeightC[k]);
				}
			} ewse {
				swath_width_chwoma_ub[k] = 0;
			}
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d suwface_width_ub_w=%0d\n", __func__, k, suwface_width_ub_w);
		dmw_pwint("DMW::%s: k=%d suwface_height_ub_w=%0d\n", __func__, k, suwface_height_ub_w);
		dmw_pwint("DMW::%s: k=%d suwface_width_ub_c=%0d\n", __func__, k, suwface_width_ub_c);
		dmw_pwint("DMW::%s: k=%d suwface_height_ub_c=%0d\n", __func__, k, suwface_height_ub_c);
		dmw_pwint("DMW::%s: k=%d Wead256BytesBwockWidthY=%0d\n", __func__, k, Wead256BytesBwockWidthY[k]);
		dmw_pwint("DMW::%s: k=%d Wead256BytesBwockHeightY=%0d\n", __func__, k, Wead256BytesBwockHeightY[k]);
		dmw_pwint("DMW::%s: k=%d Wead256BytesBwockWidthC=%0d\n", __func__, k, Wead256BytesBwockWidthC[k]);
		dmw_pwint("DMW::%s: k=%d Wead256BytesBwockHeightC=%0d\n", __func__, k, Wead256BytesBwockHeightC[k]);
		dmw_pwint("DMW::%s: k=%d ViewpowtStationawy=%0d\n", __func__, k, ViewpowtStationawy[k]);
		dmw_pwint("DMW::%s: k=%d DPPPewSuwface=%0d\n", __func__, k, DPPPewSuwface[k]);
		dmw_pwint("DMW::%s: k=%d swath_width_wuma_ub=%0d\n", __func__, k, swath_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%d swath_width_chwoma_ub=%0d\n", __func__, k, swath_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%d MaximumSwathHeightY=%0d\n", __func__, k, MaximumSwathHeightY[k]);
		dmw_pwint("DMW::%s: k=%d MaximumSwathHeightC=%0d\n", __func__, k, MaximumSwathHeightC[k]);
#endif

	}
} // CawcuwateSwathWidth

boow dmw32_UnboundedWequest(enum unbounded_wequesting_powicy UseUnboundedWequestingFinaw,
			unsigned int TotawNumbewOfActiveDPP,
			boow NoChwoma,
			enum output_encodew_cwass Output,
			enum dm_swizzwe_mode SuwfaceTiwing,
			boow CompBufWesewvedSpaceNeedAdjustment,
			boow DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment)
{
	boow wet_vaw = fawse;

	wet_vaw = (UseUnboundedWequestingFinaw != dm_unbounded_wequesting_disabwe &&
			TotawNumbewOfActiveDPP == 1 && NoChwoma);
	if (UseUnboundedWequestingFinaw == dm_unbounded_wequesting_edp_onwy && Output != dm_edp)
		wet_vaw = fawse;

	if (SuwfaceTiwing == dm_sw_wineaw)
		wet_vaw = fawse;

	if (CompBufWesewvedSpaceNeedAdjustment == 1 && DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment)
		wet_vaw = fawse;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: CompBufWesewvedSpaceNeedAdjustment  = %d\n",  __func__, CompBufWesewvedSpaceNeedAdjustment);
	dmw_pwint("DMW::%s: DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment  = %d\n",  __func__, DisabweUnboundWequestIfCompBufWesewvedSpaceNeedAdjustment);
	dmw_pwint("DMW::%s: wet_vaw = %d\n",  __func__, wet_vaw);
#endif

	wetuwn (wet_vaw);
}

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
		unsigned int *CompwessedBuffewSizeInkByte)
{
	unsigned int DETBuffewSizePoowInKByte;
	unsigned int NextDETBuffewPieceInKByte;
	boow DETPieceAssignedToThisSuwfaceAwweady[DC__NUM_DPP__MAX];
	boow NextPotentiawSuwfaceToAssignDETPieceFound;
	unsigned int NextSuwfaceToAssignDETPiece;
	doubwe TotawBandwidth;
	doubwe BandwidthOfSuwfacesNotAssignedDETPiece;
	unsigned int max_minDET;
	unsigned int minDET;
	unsigned int minDET_pipe;
	unsigned int j, k;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: FowceSingweDPP = %d\n", __func__, FowceSingweDPP);
	dmw_pwint("DMW::%s: nomDETInKByte = %d\n", __func__, nomDETInKByte);
	dmw_pwint("DMW::%s: NumbewOfActiveSuwfaces = %d\n", __func__, NumbewOfActiveSuwfaces);
	dmw_pwint("DMW::%s: UnboundedWequestEnabwed = %d\n", __func__, UnboundedWequestEnabwed);
	dmw_pwint("DMW::%s: MaxTotawDETInKByte = %d\n", __func__, MaxTotawDETInKByte);
	dmw_pwint("DMW::%s: ConfigWetuwnBuffewSizeInKByte = %d\n", __func__, ConfigWetuwnBuffewSizeInKByte);
	dmw_pwint("DMW::%s: MinCompwessedBuffewSizeInKByte = %d\n", __func__, MinCompwessedBuffewSizeInKByte);
	dmw_pwint("DMW::%s: CompwessedBuffewSegmentSizeInkByteFinaw = %d\n", __func__,
			CompwessedBuffewSegmentSizeInkByteFinaw);
#endif

	// Note: Wiww use defauwt det size if that fits 2 swaths
	if (UnboundedWequestEnabwed) {
		if (DETSizeOvewwide[0] > 0) {
			DETBuffewSizeInKByte[0] = DETSizeOvewwide[0];
		} ewse {
			DETBuffewSizeInKByte[0] = dmw_max(nomDETInKByte, dmw_ceiw(2.0 *
					((doubwe) WoundedUpMaxSwathSizeBytesY[0] +
							(doubwe) WoundedUpMaxSwathSizeBytesC[0]) / 1024.0, 64.0));
		}
		*CompwessedBuffewSizeInkByte = ConfigWetuwnBuffewSizeInKByte - DETBuffewSizeInKByte[0];
	} ewse {
		DETBuffewSizePoowInKByte = MaxTotawDETInKByte;
		fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			DETBuffewSizeInKByte[k] = nomDETInKByte;
			if (SouwcePixewFowmat[k] == dm_420_8 || SouwcePixewFowmat[k] == dm_420_10 ||
					SouwcePixewFowmat[k] == dm_420_12) {
				max_minDET = nomDETInKByte - 64;
			} ewse {
				max_minDET = nomDETInKByte;
			}
			minDET = 128;
			minDET_pipe = 0;

			// add DET wesouwce untiw can howd 2 fuww swaths
			whiwe (minDET <= max_minDET && minDET_pipe == 0) {
				if (2.0 * ((doubwe) WoundedUpMaxSwathSizeBytesY[k] +
						(doubwe) WoundedUpMaxSwathSizeBytesC[k]) / 1024.0 <= minDET)
					minDET_pipe = minDET;
				minDET = minDET + 64;
			}

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0d minDET        = %d\n", __func__, k, minDET);
			dmw_pwint("DMW::%s: k=%0d max_minDET    = %d\n", __func__, k, max_minDET);
			dmw_pwint("DMW::%s: k=%0d minDET_pipe   = %d\n", __func__, k, minDET_pipe);
			dmw_pwint("DMW::%s: k=%0d WoundedUpMaxSwathSizeBytesY = %d\n", __func__, k,
					WoundedUpMaxSwathSizeBytesY[k]);
			dmw_pwint("DMW::%s: k=%0d WoundedUpMaxSwathSizeBytesC = %d\n", __func__, k,
					WoundedUpMaxSwathSizeBytesC[k]);
#endif

			if (minDET_pipe == 0) {
				minDET_pipe = dmw_max(128, dmw_ceiw(((doubwe)WoundedUpMaxSwathSizeBytesY[k] +
						(doubwe)WoundedUpMaxSwathSizeBytesC[k]) / 1024.0, 64));
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%0d minDET_pipe = %d (assume each pwane take hawf DET)\n",
						__func__, k, minDET_pipe);
#endif
			}

			if (UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_phantom_pipe) {
				DETBuffewSizeInKByte[k] = 0;
			} ewse if (DETSizeOvewwide[k] > 0) {
				DETBuffewSizeInKByte[k] = DETSizeOvewwide[k];
				DETBuffewSizePoowInKByte = DETBuffewSizePoowInKByte -
						(FowceSingweDPP ? 1 : DPPPewSuwface[k]) * DETSizeOvewwide[k];
			} ewse if ((FowceSingweDPP ? 1 : DPPPewSuwface[k]) * minDET_pipe <= DETBuffewSizePoowInKByte) {
				DETBuffewSizeInKByte[k] = minDET_pipe;
				DETBuffewSizePoowInKByte = DETBuffewSizePoowInKByte -
						(FowceSingweDPP ? 1 : DPPPewSuwface[k]) * minDET_pipe;
			}

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%d DPPPewSuwface = %d\n", __func__, k, DPPPewSuwface[k]);
			dmw_pwint("DMW::%s: k=%d DETSizeOvewwide = %d\n", __func__, k, DETSizeOvewwide[k]);
			dmw_pwint("DMW::%s: k=%d DETBuffewSizeInKByte = %d\n", __func__, k, DETBuffewSizeInKByte[k]);
			dmw_pwint("DMW::%s: DETBuffewSizePoowInKByte = %d\n", __func__, DETBuffewSizePoowInKByte);
#endif
		}

		TotawBandwidth = 0;
		fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			if (UseMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe)
				TotawBandwidth = TotawBandwidth + WeadBandwidthWuma[k] + WeadBandwidthChwoma[k];
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: --- Befowe bandwidth adjustment ---\n", __func__);
		fow (uint k = 0; k < NumbewOfActiveSuwfaces; ++k)
			dmw_pwint("DMW::%s: k=%d DETBuffewSizeInKByte   = %d\n", __func__, k, DETBuffewSizeInKByte[k]);
		dmw_pwint("DMW::%s: --- DET awwocation with bandwidth ---\n", __func__);
		dmw_pwint("DMW::%s: TotawBandwidth = %f\n", __func__, TotawBandwidth);
#endif
		BandwidthOfSuwfacesNotAssignedDETPiece = TotawBandwidth;
		fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {

			if (UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_phantom_pipe) {
				DETPieceAssignedToThisSuwfaceAwweady[k] = twue;
			} ewse if (DETSizeOvewwide[k] > 0 || (((doubwe) (FowceSingweDPP ? 1 : DPPPewSuwface[k]) *
					(doubwe) DETBuffewSizeInKByte[k] / (doubwe) MaxTotawDETInKByte) >=
					((WeadBandwidthWuma[k] + WeadBandwidthChwoma[k]) / TotawBandwidth))) {
				DETPieceAssignedToThisSuwfaceAwweady[k] = twue;
				BandwidthOfSuwfacesNotAssignedDETPiece = BandwidthOfSuwfacesNotAssignedDETPiece -
						WeadBandwidthWuma[k] - WeadBandwidthChwoma[k];
			} ewse {
				DETPieceAssignedToThisSuwfaceAwweady[k] = fawse;
			}
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%d DETPieceAssignedToThisSuwfaceAwweady = %d\n", __func__, k,
					DETPieceAssignedToThisSuwfaceAwweady[k]);
			dmw_pwint("DMW::%s: k=%d BandwidthOfSuwfacesNotAssignedDETPiece = %f\n", __func__, k,
					BandwidthOfSuwfacesNotAssignedDETPiece);
#endif
		}

		fow (j = 0; j < NumbewOfActiveSuwfaces; ++j) {
			NextPotentiawSuwfaceToAssignDETPieceFound = fawse;
			NextSuwfaceToAssignDETPiece = 0;

			fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: j=%d k=%d, WeadBandwidthWuma[k] = %f\n", __func__, j, k,
						WeadBandwidthWuma[k]);
				dmw_pwint("DMW::%s: j=%d k=%d, WeadBandwidthChwoma[k] = %f\n", __func__, j, k,
						WeadBandwidthChwoma[k]);
				dmw_pwint("DMW::%s: j=%d k=%d, WeadBandwidthWuma[Next] = %f\n", __func__, j, k,
						WeadBandwidthWuma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%d k=%d, WeadBandwidthChwoma[Next] = %f\n", __func__, j, k,
						WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%d k=%d, NextSuwfaceToAssignDETPiece = %d\n", __func__, j, k,
						NextSuwfaceToAssignDETPiece);
#endif
				if (!DETPieceAssignedToThisSuwfaceAwweady[k] &&
						(!NextPotentiawSuwfaceToAssignDETPieceFound ||
						WeadBandwidthWuma[k] + WeadBandwidthChwoma[k] <
						WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] +
						WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece])) {
					NextSuwfaceToAssignDETPiece = k;
					NextPotentiawSuwfaceToAssignDETPieceFound = twue;
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: j=%d k=%d, DETPieceAssignedToThisSuwfaceAwweady = %d\n",
						__func__, j, k, DETPieceAssignedToThisSuwfaceAwweady[k]);
				dmw_pwint("DMW::%s: j=%d k=%d, NextPotentiawSuwfaceToAssignDETPieceFound = %d\n",
						__func__, j, k, NextPotentiawSuwfaceToAssignDETPieceFound);
#endif
			}

			if (NextPotentiawSuwfaceToAssignDETPieceFound) {
				// Note: To show the bankew's wounding behaviow in VBA and awso the fact
				// that the DET buffew size vawies due to pwecision issue
				//
				//doubwe tmp1 =  ((doubwe) DETBuffewSizePoowInKByte *
				// (WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] +
				// WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]) /
				// BandwidthOfSuwfacesNotAssignedDETPiece /
				// ((FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0));
				//doubwe tmp2 =  dmw_wound((doubwe) DETBuffewSizePoowInKByte *
				// (WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] +
				// WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]) /
				 //BandwidthOfSuwfacesNotAssignedDETPiece /
				// ((FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0));
				//
				//dmw_pwint("DMW::%s: j=%d, tmp1 = %f\n", __func__, j, tmp1);
				//dmw_pwint("DMW::%s: j=%d, tmp2 = %f\n", __func__, j, tmp2);

				NextDETBuffewPieceInKByte = dmw_min(
					dmw_wound((doubwe) DETBuffewSizePoowInKByte *
						(WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] +
						WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]) /
						BandwidthOfSuwfacesNotAssignedDETPiece /
						((FowceSingweDPP ? 1 :
								DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0)) *
						(FowceSingweDPP ? 1 :
								DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0,
						dmw_fwoow((doubwe) DETBuffewSizePoowInKByte,
						(FowceSingweDPP ? 1 :
								DPPPewSuwface[NextSuwfaceToAssignDETPiece]) * 64.0));

				// Above cawcuwation can assign the entiwe DET buffew awwocation to a singwe pipe.
				// We shouwd wimit the pew-pipe DET size to the nominaw / max pew pipe.
				if (NextDETBuffewPieceInKByte > nomDETInKByte * (FowceSingweDPP ? 1 : DPPPewSuwface[k])) {
					if (DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece] <
							nomDETInKByte * (FowceSingweDPP ? 1 : DPPPewSuwface[k])) {
						NextDETBuffewPieceInKByte = nomDETInKByte * (FowceSingweDPP ? 1 : DPPPewSuwface[k]) -
								DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece];
					} ewse {
						// Case whewe DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece]
						// awweady has the max pew-pipe vawue
						NextDETBuffewPieceInKByte = 0;
					}
				}

#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: j=%0d, DETBuffewSizePoowInKByte = %d\n", __func__, j,
					DETBuffewSizePoowInKByte);
				dmw_pwint("DMW::%s: j=%0d, NextSuwfaceToAssignDETPiece = %d\n", __func__, j,
					NextSuwfaceToAssignDETPiece);
				dmw_pwint("DMW::%s: j=%0d, WeadBandwidthWuma[%0d] = %f\n", __func__, j,
					NextSuwfaceToAssignDETPiece, WeadBandwidthWuma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%0d, WeadBandwidthChwoma[%0d] = %f\n", __func__, j,
					NextSuwfaceToAssignDETPiece, WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]);
				dmw_pwint("DMW::%s: j=%0d, BandwidthOfSuwfacesNotAssignedDETPiece = %f\n",
					__func__, j, BandwidthOfSuwfacesNotAssignedDETPiece);
				dmw_pwint("DMW::%s: j=%0d, NextDETBuffewPieceInKByte = %d\n", __func__, j,
					NextDETBuffewPieceInKByte);
				dmw_pwint("DMW::%s: j=%0d, DETBuffewSizeInKByte[%0d] incweases fwom %0d ",
					__func__, j, NextSuwfaceToAssignDETPiece,
					DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece]);
#endif

				DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece] =
						DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece]
						+ NextDETBuffewPieceInKByte
						/ (FowceSingweDPP ? 1 : DPPPewSuwface[NextSuwfaceToAssignDETPiece]);
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("to %0d\n", DETBuffewSizeInKByte[NextSuwfaceToAssignDETPiece]);
#endif

				DETBuffewSizePoowInKByte = DETBuffewSizePoowInKByte - NextDETBuffewPieceInKByte;
				DETPieceAssignedToThisSuwfaceAwweady[NextSuwfaceToAssignDETPiece] = twue;
				BandwidthOfSuwfacesNotAssignedDETPiece = BandwidthOfSuwfacesNotAssignedDETPiece -
						(WeadBandwidthWuma[NextSuwfaceToAssignDETPiece] +
								WeadBandwidthChwoma[NextSuwfaceToAssignDETPiece]);
			}
		}
		*CompwessedBuffewSizeInkByte = MinCompwessedBuffewSizeInKByte;
	}
	*CompwessedBuffewSizeInkByte = *CompwessedBuffewSizeInkByte * CompwessedBuffewSegmentSizeInkByteFinaw / 64;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: --- Aftew bandwidth adjustment ---\n", __func__);
	dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte = %d\n", __func__, *CompwessedBuffewSizeInkByte);
	fow (uint k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		dmw_pwint("DMW::%s: k=%d DETBuffewSizeInKByte = %d (TotawWeadBandWidth=%f)\n",
				__func__, k, DETBuffewSizeInKByte[k], WeadBandwidthWuma[k] + WeadBandwidthChwoma[k]);
	}
#endif
} // CawcuwateDETBuffewSize

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
		doubwe *WequiwedDISPCWKPewSuwface)
{

	doubwe SuwfaceWequiwedDISPCWKWithoutODMCombine;
	doubwe SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne;
	doubwe SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne;

	SuwfaceWequiwedDISPCWKWithoutODMCombine = dmw32_CawcuwateWequiwedDispcwk(dm_odm_combine_mode_disabwed,
			PixewCwock, DISPCWKDPPCWKDSCCWKDownSpweading, DISPCWKWampingMawgin, DISPCWKDPPCWKVCOSpeed,
			MaxDispcwk);
	SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne = dmw32_CawcuwateWequiwedDispcwk(dm_odm_combine_mode_2to1,
			PixewCwock, DISPCWKDPPCWKDSCCWKDownSpweading, DISPCWKWampingMawgin, DISPCWKDPPCWKVCOSpeed,
			MaxDispcwk);
	SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne = dmw32_CawcuwateWequiwedDispcwk(dm_odm_combine_mode_4to1,
			PixewCwock, DISPCWKDPPCWKDSCCWKDownSpweading, DISPCWKWampingMawgin, DISPCWKDPPCWKVCOSpeed,
			MaxDispcwk);
	*TotawAvaiwabwePipesSuppowt = twue;
	*ODMMode = dm_odm_combine_mode_disabwed; // initiawize as disabwe

	if (ODMUse == dm_odm_combine_powicy_none)
		*ODMMode = dm_odm_combine_mode_disabwed;

	*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithoutODMCombine;
	*NumbewOfDPP = 0;

	// FIXME check ODMUse == "" condition does it mean bypass ow Gabwiew means something wike don't cawe??
	// (ODMUse == "" || ODMUse == "CombineAsNeeded")

	if (!(Output == dm_hdmi || Output == dm_dp || Output == dm_edp) && (ODMUse == dm_odm_combine_powicy_4to1 ||
			((SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne > StateDispcwk ||
					(DSCEnabwe && (HActive > 2 * MaximumPixewsPewWinePewDSCUnit))
					|| NumbewOfDSCSwices > 8)))) {
		if (TotawNumbewOfActiveDPP + 4 <= MaxNumDPP) {
			*ODMMode = dm_odm_combine_mode_4to1;
			*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne;
			*NumbewOfDPP = 4;
		} ewse {
			*TotawAvaiwabwePipesSuppowt = fawse;
		}
	} ewse if (Output != dm_hdmi && (ODMUse == dm_odm_combine_powicy_2to1 ||
			(((SuwfaceWequiwedDISPCWKWithoutODMCombine > StateDispcwk &&
					SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne <= StateDispcwk) ||
					(DSCEnabwe && (HActive > MaximumPixewsPewWinePewDSCUnit))
					|| (NumbewOfDSCSwices <= 8 && NumbewOfDSCSwices > 4))))) {
		if (TotawNumbewOfActiveDPP + 2 <= MaxNumDPP) {
			*ODMMode = dm_odm_combine_mode_2to1;
			*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne;
			*NumbewOfDPP = 2;
		} ewse {
			*TotawAvaiwabwePipesSuppowt = fawse;
		}
	} ewse {
		if (TotawNumbewOfActiveDPP + 1 <= MaxNumDPP)
			*NumbewOfDPP = 1;
		ewse
			*TotawAvaiwabwePipesSuppowt = fawse;
	}
	if (OutFowmat == dm_420 && HActive > DCN32_MAX_FMT_420_BUFFEW_WIDTH &&
			ODMUse != dm_odm_combine_powicy_4to1) {
		if (HActive > DCN32_MAX_FMT_420_BUFFEW_WIDTH * 4) {
			*ODMMode = dm_odm_combine_mode_disabwed;
			*NumbewOfDPP = 0;
			*TotawAvaiwabwePipesSuppowt = fawse;
		} ewse if (HActive > DCN32_MAX_FMT_420_BUFFEW_WIDTH * 2 ||
				*ODMMode == dm_odm_combine_mode_4to1) {
			*ODMMode = dm_odm_combine_mode_4to1;
			*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithODMCombineFouwToOne;
			*NumbewOfDPP = 4;
		} ewse {
			*ODMMode = dm_odm_combine_mode_2to1;
			*WequiwedDISPCWKPewSuwface = SuwfaceWequiwedDISPCWKWithODMCombineTwoToOne;
			*NumbewOfDPP = 2;
		}
	}
	if (Output == dm_hdmi && OutFowmat == dm_420 &&
			HActive > DCN32_MAX_FMT_420_BUFFEW_WIDTH) {
		*ODMMode = dm_odm_combine_mode_disabwed;
		*NumbewOfDPP = 0;
		*TotawAvaiwabwePipesSuppowt = fawse;
	}
}

doubwe dmw32_CawcuwateWequiwedDispcwk(
		enum odm_combine_mode ODMMode,
		doubwe PixewCwock,
		doubwe DISPCWKDPPCWKDSCCWKDownSpweading,
		doubwe DISPCWKWampingMawgin,
		doubwe DISPCWKDPPCWKVCOSpeed,
		doubwe MaxDispcwk)
{
	doubwe WequiwedDispcwk = 0.;
	doubwe PixewCwockAftewODM;
	doubwe DISPCWKWithWampingWoundedToDFSGwanuwawity;
	doubwe DISPCWKWithoutWampingWoundedToDFSGwanuwawity;
	doubwe MaxDispcwkWoundedDownToDFSGwanuwawity;

	if (ODMMode == dm_odm_combine_mode_4to1)
		PixewCwockAftewODM = PixewCwock / 4;
	ewse if (ODMMode == dm_odm_combine_mode_2to1)
		PixewCwockAftewODM = PixewCwock / 2;
	ewse
		PixewCwockAftewODM = PixewCwock;


	DISPCWKWithWampingWoundedToDFSGwanuwawity = dmw32_WoundToDFSGwanuwawity(
			PixewCwockAftewODM * (1 + DISPCWKDPPCWKDSCCWKDownSpweading / 100)
					* (1 + DISPCWKWampingMawgin / 100), 1, DISPCWKDPPCWKVCOSpeed);

	DISPCWKWithoutWampingWoundedToDFSGwanuwawity = dmw32_WoundToDFSGwanuwawity(
			PixewCwockAftewODM * (1 + DISPCWKDPPCWKDSCCWKDownSpweading / 100), 1, DISPCWKDPPCWKVCOSpeed);

	MaxDispcwkWoundedDownToDFSGwanuwawity = dmw32_WoundToDFSGwanuwawity(MaxDispcwk, 0, DISPCWKDPPCWKVCOSpeed);

	if (DISPCWKWithoutWampingWoundedToDFSGwanuwawity > MaxDispcwkWoundedDownToDFSGwanuwawity)
		WequiwedDispcwk = DISPCWKWithoutWampingWoundedToDFSGwanuwawity;
	ewse if (DISPCWKWithWampingWoundedToDFSGwanuwawity > MaxDispcwkWoundedDownToDFSGwanuwawity)
		WequiwedDispcwk = MaxDispcwkWoundedDownToDFSGwanuwawity;
	ewse
		WequiwedDispcwk = DISPCWKWithWampingWoundedToDFSGwanuwawity;

	wetuwn WequiwedDispcwk;
}

doubwe dmw32_WoundToDFSGwanuwawity(doubwe Cwock, boow wound_up, doubwe VCOSpeed)
{
	if (Cwock <= 0.0)
		wetuwn 0.0;

	if (wound_up)
		wetuwn VCOSpeed * 4.0 / dmw_fwoow(VCOSpeed * 4.0 / Cwock, 1.0);
	ewse
		wetuwn VCOSpeed * 4.0 / dmw_ceiw(VCOSpeed * 4.0 / Cwock, 1.0);
}

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
		unsigned int *WequiwedSwots)
{
	boow WinkDSCEnabwe;
	unsigned int dummy;
	*WequiwesDSC = fawse;
	*WequiwesFEC = fawse;
	*OutBpp = 0;
	*OutputType = dm_output_type_unknown;
	*OutputWate = dm_output_wate_unknown;

	if (IsMainSuwfaceUsingTheIndicatedTiming) {
		if (Output == dm_hdmi) {
			*WequiwesDSC = fawse;
			*WequiwesFEC = fawse;
			*OutBpp = dmw32_TwuncToVawidBPP(dmw_min(600, PHYCWKPewState) * 10, 3, HTotaw, HActive,
					PixewCwockBackEnd, FowcedOutputWinkBPP, fawse, Output, OutputFowmat,
					DSCInputBitPewComponent, NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
					ODMModeNoDSC, ODMModeDSC, &dummy);
			//OutputTypeAndWate = "HDMI";
			*OutputType = dm_output_type_hdmi;

		} ewse if (Output == dm_dp || Output == dm_dp2p0 || Output == dm_edp) {
			if (DSCEnabwe == twue) {
				*WequiwesDSC = twue;
				WinkDSCEnabwe = twue;
				if (Output == dm_dp || Output == dm_dp2p0)
					*WequiwesFEC = twue;
				ewse
					*WequiwesFEC = fawse;
			} ewse {
				*WequiwesDSC = fawse;
				WinkDSCEnabwe = fawse;
				if (Output == dm_dp2p0)
					*WequiwesFEC = twue;
				ewse
					*WequiwesFEC = fawse;
			}
			if (Output == dm_dp2p0) {
				*OutBpp = 0;
				if ((OutputWinkDPWate == dm_dp_wate_na || OutputWinkDPWate == dm_dp_wate_uhbw10) &&
						PHYCWKD32PewState >= 10000 / 32) {
					*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 10000,
							OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
							FowcedOutputWinkBPP, WinkDSCEnabwe, Output, OutputFowmat,
							DSCInputBitPewComponent, NumbewOfDSCSwices, AudioSampweWate,
							AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					if (*OutBpp == 0 && PHYCWKD32PewState < 13500 / 32 && DSCEnabwe == twue &&
							FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 10000,
								OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
								FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
								OutputFowmat, DSCInputBitPewComponent,
								NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
								ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " UHBW10";
					*OutputType = dm_output_type_dp2p0;
					*OutputWate = dm_output_wate_dp_wate_uhbw10;
				}
				if ((OutputWinkDPWate == dm_dp_wate_na || OutputWinkDPWate == dm_dp_wate_uhbw13p5) &&
						*OutBpp == 0 && PHYCWKD32PewState >= 13500 / 32) {
					*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 13500,
							OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
							FowcedOutputWinkBPP, WinkDSCEnabwe, Output, OutputFowmat,
							DSCInputBitPewComponent, NumbewOfDSCSwices, AudioSampweWate,
							AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);

					if (*OutBpp == 0 && PHYCWKD32PewState < 20000 / 32 && DSCEnabwe == twue &&
							FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 13500,
								OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
								FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
								OutputFowmat, DSCInputBitPewComponent,
								NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
								ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " UHBW13p5";
					*OutputType = dm_output_type_dp2p0;
					*OutputWate = dm_output_wate_dp_wate_uhbw13p5;
				}
				if ((OutputWinkDPWate == dm_dp_wate_na || OutputWinkDPWate == dm_dp_wate_uhbw20) &&
						*OutBpp == 0 && PHYCWKD32PewState >= 20000 / 32) {
					*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 20000,
							OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
							FowcedOutputWinkBPP, WinkDSCEnabwe, Output, OutputFowmat,
							DSCInputBitPewComponent, NumbewOfDSCSwices, AudioSampweWate,
							AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					if (*OutBpp == 0 && DSCEnabwe == twue && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 20000,
								OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
								FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
								OutputFowmat, DSCInputBitPewComponent,
								NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
								ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " UHBW20";
					*OutputType = dm_output_type_dp2p0;
					*OutputWate = dm_output_wate_dp_wate_uhbw20;
				}
			} ewse {
				*OutBpp = 0;
				if ((OutputWinkDPWate == dm_dp_wate_na || OutputWinkDPWate == dm_dp_wate_hbw) &&
						PHYCWKPewState >= 270) {
					*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 2700,
							OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
							FowcedOutputWinkBPP, WinkDSCEnabwe, Output, OutputFowmat,
							DSCInputBitPewComponent, NumbewOfDSCSwices, AudioSampweWate,
							AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					if (*OutBpp == 0 && PHYCWKPewState < 540 && DSCEnabwe == twue &&
							FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						if (Output == dm_dp)
							*WequiwesFEC = twue;
						*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 2700,
								OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
								FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
								OutputFowmat, DSCInputBitPewComponent,
								NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
								ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " HBW";
					*OutputType = (Output == dm_dp) ? dm_output_type_dp : dm_output_type_edp;
					*OutputWate = dm_output_wate_dp_wate_hbw;
				}
				if ((OutputWinkDPWate == dm_dp_wate_na || OutputWinkDPWate == dm_dp_wate_hbw2) &&
						*OutBpp == 0 && PHYCWKPewState >= 540) {
					*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 5400,
							OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
							FowcedOutputWinkBPP, WinkDSCEnabwe, Output, OutputFowmat,
							DSCInputBitPewComponent, NumbewOfDSCSwices, AudioSampweWate,
							AudioSampweWayout, ODMModeNoDSC, ODMModeDSC, WequiwedSwots);

					if (*OutBpp == 0 && PHYCWKPewState < 810 && DSCEnabwe == twue &&
							FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						if (Output == dm_dp)
							*WequiwesFEC = twue;

						*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 5400,
								OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
								FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
								OutputFowmat, DSCInputBitPewComponent,
								NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
								ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " HBW2";
					*OutputType = (Output == dm_dp) ? dm_output_type_dp : dm_output_type_edp;
					*OutputWate = dm_output_wate_dp_wate_hbw2;
				}
				if ((OutputWinkDPWate == dm_dp_wate_na || OutputWinkDPWate == dm_dp_wate_hbw3) && *OutBpp == 0 && PHYCWKPewState >= 810) {
					*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 8100,
							OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
							FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
							OutputFowmat, DSCInputBitPewComponent, NumbewOfDSCSwices,
							AudioSampweWate, AudioSampweWayout, ODMModeNoDSC, ODMModeDSC,
							WequiwedSwots);

					if (*OutBpp == 0 && DSCEnabwe == twue && FowcedOutputWinkBPP == 0) {
						*WequiwesDSC = twue;
						WinkDSCEnabwe = twue;
						if (Output == dm_dp)
							*WequiwesFEC = twue;

						*OutBpp = dmw32_TwuncToVawidBPP((1 - Downspweading / 100) * 8100,
								OutputWinkDPWanes, HTotaw, HActive, PixewCwockBackEnd,
								FowcedOutputWinkBPP, WinkDSCEnabwe, Output,
								OutputFowmat, DSCInputBitPewComponent,
								NumbewOfDSCSwices, AudioSampweWate, AudioSampweWayout,
								ODMModeNoDSC, ODMModeDSC, WequiwedSwots);
					}
					//OutputTypeAndWate = Output & " HBW3";
					*OutputType = (Output == dm_dp) ? dm_output_type_dp : dm_output_type_edp;
					*OutputWate = dm_output_wate_dp_wate_hbw3;
				}
			}
		}
	}
}

void dmw32_CawcuwateDPPCWK(
		unsigned int NumbewOfActiveSuwfaces,
		doubwe DISPCWKDPPCWKDSCCWKDownSpweading,
		doubwe DISPCWKDPPCWKVCOSpeed,
		doubwe DPPCWKUsingSingweDPP[],
		unsigned int DPPPewSuwface[],

		/* output */
		doubwe *GwobawDPPCWK,
		doubwe Dppcwk[])
{
	unsigned int k;
	*GwobawDPPCWK = 0;
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		Dppcwk[k] = DPPCWKUsingSingweDPP[k] / DPPPewSuwface[k] * (1 + DISPCWKDPPCWKDSCCWKDownSpweading / 100);
		*GwobawDPPCWK = dmw_max(*GwobawDPPCWK, Dppcwk[k]);
	}
	*GwobawDPPCWK = dmw32_WoundToDFSGwanuwawity(*GwobawDPPCWK, 1, DISPCWKDPPCWKVCOSpeed);
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k)
		Dppcwk[k] = *GwobawDPPCWK / 255 * dmw_ceiw(Dppcwk[k] * 255.0 / *GwobawDPPCWK, 1.0);
}

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
		unsigned int *WequiwedSwots)
{
	doubwe    MaxWinkBPP;
	unsigned int   MinDSCBPP;
	doubwe    MaxDSCBPP;
	unsigned int   NonDSCBPP0;
	unsigned int   NonDSCBPP1;
	unsigned int   NonDSCBPP2;

	if (Fowmat == dm_420) {
		NonDSCBPP0 = 12;
		NonDSCBPP1 = 15;
		NonDSCBPP2 = 18;
		MinDSCBPP = 6;
		MaxDSCBPP = 1.5 * DSCInputBitPewComponent - 1 / 16;
	} ewse if (Fowmat == dm_444) {
		NonDSCBPP0 = 24;
		NonDSCBPP1 = 30;
		NonDSCBPP2 = 36;
		MinDSCBPP = 8;
		MaxDSCBPP = 3 * DSCInputBitPewComponent - 1.0 / 16;
	} ewse {
		if (Output == dm_hdmi) {
			NonDSCBPP0 = 24;
			NonDSCBPP1 = 24;
			NonDSCBPP2 = 24;
		} ewse {
			NonDSCBPP0 = 16;
			NonDSCBPP1 = 20;
			NonDSCBPP2 = 24;
		}
		if (Fowmat == dm_n422) {
			MinDSCBPP = 7;
			MaxDSCBPP = 2 * DSCInputBitPewComponent - 1.0 / 16.0;
		} ewse {
			MinDSCBPP = 8;
			MaxDSCBPP = 3 * DSCInputBitPewComponent - 1.0 / 16.0;
		}
	}
	if (Output == dm_dp2p0) {
		MaxWinkBPP = WinkBitWate * Wanes / PixewCwock * 128 / 132 * 383 / 384 * 65536 / 65540;
	} ewse if (DSCEnabwe && Output == dm_dp) {
		MaxWinkBPP = WinkBitWate / 10 * 8 * Wanes / PixewCwock * (1 - 2.4 / 100);
	} ewse {
		MaxWinkBPP = WinkBitWate / 10 * 8 * Wanes / PixewCwock;
	}

	if (DSCEnabwe) {
		if (ODMModeDSC == dm_odm_combine_mode_4to1)
			MaxWinkBPP = dmw_min(MaxWinkBPP, 16);
		ewse if (ODMModeDSC == dm_odm_combine_mode_2to1)
			MaxWinkBPP = dmw_min(MaxWinkBPP, 32);
		ewse if (ODMModeDSC == dm_odm_spwit_mode_1to2)
			MaxWinkBPP = 2 * MaxWinkBPP;
	} ewse {
		if (ODMModeNoDSC == dm_odm_combine_mode_4to1)
			MaxWinkBPP = dmw_min(MaxWinkBPP, 16);
		ewse if (ODMModeNoDSC == dm_odm_combine_mode_2to1)
			MaxWinkBPP = dmw_min(MaxWinkBPP, 32);
		ewse if (ODMModeNoDSC == dm_odm_spwit_mode_1to2)
			MaxWinkBPP = 2 * MaxWinkBPP;
	}

	if (DesiwedBPP == 0) {
		if (DSCEnabwe) {
			if (MaxWinkBPP < MinDSCBPP)
				wetuwn BPP_INVAWID;
			ewse if (MaxWinkBPP >= MaxDSCBPP)
				wetuwn MaxDSCBPP;
			ewse
				wetuwn dmw_fwoow(16.0 * MaxWinkBPP, 1.0) / 16.0;
		} ewse {
			if (MaxWinkBPP >= NonDSCBPP2)
				wetuwn NonDSCBPP2;
			ewse if (MaxWinkBPP >= NonDSCBPP1)
				wetuwn NonDSCBPP1;
			ewse if (MaxWinkBPP >= NonDSCBPP0)
				wetuwn 16.0;
			ewse
				wetuwn BPP_INVAWID;
		}
	} ewse {
		if (!((DSCEnabwe == fawse && (DesiwedBPP == NonDSCBPP2 || DesiwedBPP == NonDSCBPP1 ||
				DesiwedBPP <= NonDSCBPP0)) ||
				(DSCEnabwe && DesiwedBPP >= MinDSCBPP && DesiwedBPP <= MaxDSCBPP)))
			wetuwn BPP_INVAWID;
		ewse
			wetuwn DesiwedBPP;
	}

	*WequiwedSwots = dmw_ceiw(DesiwedBPP / MaxWinkBPP * 64, 1);

	wetuwn BPP_INVAWID;
} // TwuncToVawidBPP

doubwe dmw32_WequiwedDTBCWK(
		boow              DSCEnabwe,
		doubwe               PixewCwock,
		enum output_fowmat_cwass  OutputFowmat,
		doubwe               OutputBpp,
		unsigned int              DSCSwices,
		unsigned int                 HTotaw,
		unsigned int                 HActive,
		unsigned int              AudioWate,
		unsigned int              AudioWayout)
{
	doubwe PixewWowdWate;
	doubwe HCActive;
	doubwe HCBwank;
	doubwe AvewageTwibyteWate;
	doubwe HActiveTwibyteWate;

	if (DSCEnabwe != twue)
		wetuwn dmw_max(PixewCwock / 4.0 * OutputBpp / 24.0, 25.0);

	PixewWowdWate = PixewCwock /  (OutputFowmat == dm_444 ? 1 : 2);
	HCActive = dmw_ceiw(DSCSwices * dmw_ceiw(OutputBpp *
			dmw_ceiw(HActive / DSCSwices, 1) / 8.0, 1) / 3.0, 1);
	HCBwank = 64 + 32 *
			dmw_ceiw(AudioWate *  (AudioWayout == 1 ? 1 : 0.25) * HTotaw / (PixewCwock * 1000), 1);
	AvewageTwibyteWate = PixewWowdWate * (HCActive + HCBwank) / HTotaw;
	HActiveTwibyteWate = PixewWowdWate * HCActive / HActive;
	wetuwn dmw_max4(PixewWowdWate / 4.0, AvewageTwibyteWate / 4.0, HActiveTwibyteWate / 4.0, 25.0) * 1.002;
}

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
		doubwe dsc_deway_factow_wa)
{
	unsigned int DSCDewayWequiwement_vaw;

	if (DSCEnabwed == twue && OutputBpp != 0) {
		if (ODMMode == dm_odm_combine_mode_4to1) {
			DSCDewayWequiwement_vaw = 4 * (dmw32_dscceComputeDeway(DSCInputBitPewComponent, OutputBpp,
					dmw_ceiw(HActive / NumbewOfDSCSwices, 1), NumbewOfDSCSwices / 4,
					OutputFowmat, Output) + dmw32_dscComputeDeway(OutputFowmat, Output));
		} ewse if (ODMMode == dm_odm_combine_mode_2to1) {
			DSCDewayWequiwement_vaw = 2 * (dmw32_dscceComputeDeway(DSCInputBitPewComponent, OutputBpp,
					dmw_ceiw(HActive / NumbewOfDSCSwices, 1), NumbewOfDSCSwices / 2,
					OutputFowmat, Output) + dmw32_dscComputeDeway(OutputFowmat, Output));
		} ewse {
			DSCDewayWequiwement_vaw = dmw32_dscceComputeDeway(DSCInputBitPewComponent, OutputBpp,
					dmw_ceiw(HActive / NumbewOfDSCSwices, 1), NumbewOfDSCSwices,
					OutputFowmat, Output) + dmw32_dscComputeDeway(OutputFowmat, Output);
		}

		DSCDewayWequiwement_vaw = DSCDewayWequiwement_vaw + (HTotaw - HActive) *
				dmw_ceiw((doubwe)DSCDewayWequiwement_vaw / HActive, 1);

		DSCDewayWequiwement_vaw = DSCDewayWequiwement_vaw * PixewCwock / PixewCwockBackEnd;

	} ewse {
		DSCDewayWequiwement_vaw = 0;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DSCEnabwed              = %d\n", __func__, DSCEnabwed);
	dmw_pwint("DMW::%s: OutputBpp               = %f\n", __func__, OutputBpp);
	dmw_pwint("DMW::%s: HActive                 = %d\n", __func__, HActive);
	dmw_pwint("DMW::%s: OutputFowmat            = %d\n", __func__, OutputFowmat);
	dmw_pwint("DMW::%s: DSCInputBitPewComponent = %d\n", __func__, DSCInputBitPewComponent);
	dmw_pwint("DMW::%s: NumbewOfDSCSwices       = %d\n", __func__, NumbewOfDSCSwices);
	dmw_pwint("DMW::%s: DSCDewayWequiwement_vaw = %d\n", __func__, DSCDewayWequiwement_vaw);
#endif

	wetuwn dmw_ceiw(DSCDewayWequiwement_vaw * dsc_deway_factow_wa, 1);
}

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
		boow *ExceededMAWWSize)
{
	unsigned int k;
	unsigned int TotawSuwfaceSizeInMAWWFowSS = 0;
	unsigned int TotawSuwfaceSizeInMAWWFowSubVP = 0;
	unsigned int MAWWAwwocatedFowDCNInBytes = MAWWAwwocatedFowDCN * 1024 * 1024;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (ViewpowtStationawy[k]) {
			SuwfaceSizeInMAWW[k] = dmw_min(dmw_ceiw(SuwfaceWidthY[k], WeadBwockWidthY[k]),
					dmw_fwoow(ViewpowtXStawtY[k] + ViewpowtWidthY[k] + WeadBwockWidthY[k] - 1,
						WeadBwockWidthY[k]) - dmw_fwoow(ViewpowtXStawtY[k],
						WeadBwockWidthY[k])) * dmw_min(dmw_ceiw(SuwfaceHeightY[k],
						WeadBwockHeightY[k]), dmw_fwoow(ViewpowtYStawtY[k] +
						ViewpowtHeightY[k] + WeadBwockHeightY[k] - 1, WeadBwockHeightY[k]) -
						dmw_fwoow(ViewpowtYStawtY[k], WeadBwockHeightY[k])) * BytesPewPixewY[k];

			if (WeadBwockWidthC[k] > 0) {
				SuwfaceSizeInMAWW[k] = SuwfaceSizeInMAWW[k] +
						dmw_min(dmw_ceiw(SuwfaceWidthC[k], WeadBwockWidthC[k]),
							dmw_fwoow(ViewpowtXStawtC[k] + ViewpowtWidthC[k] +
							WeadBwockWidthC[k] - 1, WeadBwockWidthC[k]) -
							dmw_fwoow(ViewpowtXStawtC[k], WeadBwockWidthC[k])) *
							dmw_min(dmw_ceiw(SuwfaceHeightC[k], WeadBwockHeightC[k]),
							dmw_fwoow(ViewpowtYStawtC[k] + ViewpowtHeightC[k] +
							WeadBwockHeightC[k] - 1, WeadBwockHeightC[k]) -
							dmw_fwoow(ViewpowtYStawtC[k], WeadBwockHeightC[k])) *
							BytesPewPixewC[k];
			}
			if (DCCEnabwe[k] == twue) {
				SuwfaceSizeInMAWW[k] = SuwfaceSizeInMAWW[k] +
						(dmw_min(dmw_ceiw(DCCMetaPitchY[k], 8 * Wead256BytesBwockWidthY[k]),
							dmw_fwoow(ViewpowtXStawtY[k] + ViewpowtWidthY[k] + 8 *
							Wead256BytesBwockWidthY[k] - 1, 8 * Wead256BytesBwockWidthY[k])
							- dmw_fwoow(ViewpowtXStawtY[k], 8 * Wead256BytesBwockWidthY[k]))
							* dmw_min(dmw_ceiw(SuwfaceHeightY[k], 8 *
							Wead256BytesBwockHeightY[k]), dmw_fwoow(ViewpowtYStawtY[k] +
							ViewpowtHeightY[k] + 8 * Wead256BytesBwockHeightY[k] - 1, 8 *
							Wead256BytesBwockHeightY[k]) - dmw_fwoow(ViewpowtYStawtY[k], 8 *
							Wead256BytesBwockHeightY[k])) * BytesPewPixewY[k] / 256) + (64 * 1024);
				if (Wead256BytesBwockWidthC[k] > 0) {
					SuwfaceSizeInMAWW[k] = SuwfaceSizeInMAWW[k] +
							dmw_min(dmw_ceiw(DCCMetaPitchC[k], 8 *
								Wead256BytesBwockWidthC[k]),
								dmw_fwoow(ViewpowtXStawtC[k] + ViewpowtWidthC[k] + 8
								* Wead256BytesBwockWidthC[k] - 1, 8 *
								Wead256BytesBwockWidthC[k]) -
								dmw_fwoow(ViewpowtXStawtC[k], 8 *
								Wead256BytesBwockWidthC[k])) *
								dmw_min(dmw_ceiw(SuwfaceHeightC[k], 8 *
								Wead256BytesBwockHeightC[k]),
								dmw_fwoow(ViewpowtYStawtC[k] + ViewpowtHeightC[k] +
								8 * Wead256BytesBwockHeightC[k] - 1, 8 *
								Wead256BytesBwockHeightC[k]) -
								dmw_fwoow(ViewpowtYStawtC[k], 8 *
								Wead256BytesBwockHeightC[k])) *
								BytesPewPixewC[k] / 256;
				}
			}
		} ewse {
			SuwfaceSizeInMAWW[k] = dmw_ceiw(dmw_min(SuwfaceWidthY[k], ViewpowtWidthY[k] +
					WeadBwockWidthY[k] - 1), WeadBwockWidthY[k]) *
					dmw_ceiw(dmw_min(SuwfaceHeightY[k], ViewpowtHeightY[k] +
							WeadBwockHeightY[k] - 1), WeadBwockHeightY[k]) *
							BytesPewPixewY[k];
			if (WeadBwockWidthC[k] > 0) {
				SuwfaceSizeInMAWW[k] = SuwfaceSizeInMAWW[k] +
						dmw_ceiw(dmw_min(SuwfaceWidthC[k], ViewpowtWidthC[k] +
								WeadBwockWidthC[k] - 1), WeadBwockWidthC[k]) *
						dmw_ceiw(dmw_min(SuwfaceHeightC[k], ViewpowtHeightC[k] +
								WeadBwockHeightC[k] - 1), WeadBwockHeightC[k]) *
								BytesPewPixewC[k];
			}
			if (DCCEnabwe[k] == twue) {
				SuwfaceSizeInMAWW[k] = SuwfaceSizeInMAWW[k] +
						(dmw_ceiw(dmw_min(DCCMetaPitchY[k], ViewpowtWidthY[k] + 8 *
								Wead256BytesBwockWidthY[k] - 1), 8 *
								Wead256BytesBwockWidthY[k]) *
						dmw_ceiw(dmw_min(SuwfaceHeightY[k], ViewpowtHeightY[k] + 8 *
								Wead256BytesBwockHeightY[k] - 1), 8 *
								Wead256BytesBwockHeightY[k]) * BytesPewPixewY[k] / 256) + (64 * 1024);

				if (Wead256BytesBwockWidthC[k] > 0) {
					SuwfaceSizeInMAWW[k] = SuwfaceSizeInMAWW[k] +
							dmw_ceiw(dmw_min(DCCMetaPitchC[k], ViewpowtWidthC[k] + 8 *
									Wead256BytesBwockWidthC[k] - 1), 8 *
									Wead256BytesBwockWidthC[k]) *
							dmw_ceiw(dmw_min(SuwfaceHeightC[k], ViewpowtHeightC[k] + 8 *
									Wead256BytesBwockHeightC[k] - 1), 8 *
									Wead256BytesBwockHeightC[k]) *
									BytesPewPixewC[k] / 256;
				}
			}
		}
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		/* SS and Subvp counted sepawate as they awe nevew used at the same time */
		if (UsesMAWWFowPStateChange[k] == dm_use_maww_pstate_change_phantom_pipe)
			TotawSuwfaceSizeInMAWWFowSubVP = TotawSuwfaceSizeInMAWWFowSubVP + SuwfaceSizeInMAWW[k];
		ewse if (UseMAWWFowStaticScween[k] == dm_use_maww_static_scween_enabwe)
			TotawSuwfaceSizeInMAWWFowSS = TotawSuwfaceSizeInMAWWFowSS + SuwfaceSizeInMAWW[k];
	}
	*ExceededMAWWSize =  (TotawSuwfaceSizeInMAWWFowSS > MAWWAwwocatedFowDCNInBytes) ||
							(TotawSuwfaceSizeInMAWWFowSubVP > MAWWAwwocatedFowDCNInBytes);
} // CawcuwateSuwfaceSizeInMaww

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
		unsigned int BIGK_FWAGMENT_SIZE[])
{
	unsigned int k;
	unsigned int PTEBuffewSizeInWequestsFowWuma[DC__NUM_DPP__MAX];
	unsigned int PTEBuffewSizeInWequestsFowChwoma[DC__NUM_DPP__MAX];
	unsigned int PDEAndMetaPTEBytesFwameY;
	unsigned int PDEAndMetaPTEBytesFwameC;
	unsigned int MetaWowByteY[DC__NUM_DPP__MAX];
	unsigned int MetaWowByteC[DC__NUM_DPP__MAX];
	unsigned int PixewPTEBytesPewWowY[DC__NUM_DPP__MAX];
	unsigned int PixewPTEBytesPewWowC[DC__NUM_DPP__MAX];
	unsigned int PixewPTEBytesPewWowY_one_wow_pew_fwame[DC__NUM_DPP__MAX];
	unsigned int PixewPTEBytesPewWowC_one_wow_pew_fwame[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_width_wuma_ub_one_wow_pew_fwame[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_height_wuma_one_wow_pew_fwame[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_width_chwoma_ub_one_wow_pew_fwame[DC__NUM_DPP__MAX];
	unsigned int dpte_wow_height_chwoma_one_wow_pew_fwame[DC__NUM_DPP__MAX];
	boow one_wow_pew_fwame_fits_in_buffew[DC__NUM_DPP__MAX];

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (HostVMEnabwe == twue) {
			vm_gwoup_bytes[k] = 512;
			dpte_gwoup_bytes[k] = 512;
		} ewse if (GPUVMEnabwe == twue) {
			vm_gwoup_bytes[k] = 2048;
			if (GPUVMMinPageSizeKBytes[k] >= 64 && IsVewticaw(myPipe[k].SouwceWotation))
				dpte_gwoup_bytes[k] = 512;
			ewse
				dpte_gwoup_bytes[k] = 2048;
		} ewse {
			vm_gwoup_bytes[k] = 0;
			dpte_gwoup_bytes[k] = 0;
		}

		if (myPipe[k].SouwcePixewFowmat == dm_420_8 || myPipe[k].SouwcePixewFowmat == dm_420_10 ||
				myPipe[k].SouwcePixewFowmat == dm_420_12 ||
				myPipe[k].SouwcePixewFowmat == dm_wgbe_awpha) {
			if ((myPipe[k].SouwcePixewFowmat == dm_420_10 || myPipe[k].SouwcePixewFowmat == dm_420_12) &&
					!IsVewticaw(myPipe[k].SouwceWotation)) {
				PTEBuffewSizeInWequestsFowWuma[k] =
						(PTEBuffewSizeInWequestsWuma + PTEBuffewSizeInWequestsChwoma) / 2;
				PTEBuffewSizeInWequestsFowChwoma[k] = PTEBuffewSizeInWequestsFowWuma[k];
			} ewse {
				PTEBuffewSizeInWequestsFowWuma[k] = PTEBuffewSizeInWequestsWuma;
				PTEBuffewSizeInWequestsFowChwoma[k] = PTEBuffewSizeInWequestsChwoma;
			}

			PDEAndMetaPTEBytesFwameC = dmw32_CawcuwateVMAndWowBytes(
					myPipe[k].ViewpowtStationawy,
					myPipe[k].DCCEnabwe,
					myPipe[k].DPPPewSuwface,
					myPipe[k].BwockHeight256BytesC,
					myPipe[k].BwockWidth256BytesC,
					myPipe[k].SouwcePixewFowmat,
					myPipe[k].SuwfaceTiwing,
					myPipe[k].BytePewPixewC,
					myPipe[k].SouwceWotation,
					SwathWidthC[k],
					myPipe[k].ViewpowtHeightChwoma,
					myPipe[k].ViewpowtXStawtC,
					myPipe[k].ViewpowtYStawtC,
					GPUVMEnabwe,
					HostVMEnabwe,
					HostVMMaxNonCachedPageTabweWevews,
					GPUVMMaxPageTabweWevews,
					GPUVMMinPageSizeKBytes[k],
					HostVMMinPageSize,
					PTEBuffewSizeInWequestsFowChwoma[k],
					myPipe[k].PitchC,
					myPipe[k].DCCMetaPitchC,
					myPipe[k].BwockWidthC,
					myPipe[k].BwockHeightC,

					/* Output */
					&MetaWowByteC[k],
					&PixewPTEBytesPewWowC[k],
					&dpte_wow_width_chwoma_ub[k],
					&dpte_wow_height_chwoma[k],
					&dpte_wow_height_wineaw_chwoma[k],
					&PixewPTEBytesPewWowC_one_wow_pew_fwame[k],
					&dpte_wow_width_chwoma_ub_one_wow_pew_fwame[k],
					&dpte_wow_height_chwoma_one_wow_pew_fwame[k],
					&meta_weq_width_chwoma[k],
					&meta_weq_height_chwoma[k],
					&meta_wow_width_chwoma[k],
					&meta_wow_height_chwoma[k],
					&PixewPTEWeqWidthC[k],
					&PixewPTEWeqHeightC[k],
					&PTEWequestSizeC[k],
					&dpde0_bytes_pew_fwame_ub_c[k],
					&meta_pte_bytes_pew_fwame_ub_c[k]);

			PwefetchSouwceWinesC[k] = dmw32_CawcuwatePwefetchSouwceWines(
					myPipe[k].VWatioChwoma,
					myPipe[k].VTapsChwoma,
					myPipe[k].IntewwaceEnabwe,
					myPipe[k].PwogwessiveToIntewwaceUnitInOPP,
					myPipe[k].SwathHeightC,
					myPipe[k].SouwceWotation,
					myPipe[k].ViewpowtStationawy,
					SwathWidthC[k],
					myPipe[k].ViewpowtHeightChwoma,
					myPipe[k].ViewpowtXStawtC,
					myPipe[k].ViewpowtYStawtC,

					/* Output */
					&VInitPweFiwwC[k],
					&MaxNumSwathC[k]);
		} ewse {
			PTEBuffewSizeInWequestsFowWuma[k] = PTEBuffewSizeInWequestsWuma + PTEBuffewSizeInWequestsChwoma;
			PTEBuffewSizeInWequestsFowChwoma[k] = 0;
			PixewPTEBytesPewWowC[k] = 0;
			PDEAndMetaPTEBytesFwameC = 0;
			MetaWowByteC[k] = 0;
			MaxNumSwathC[k] = 0;
			PwefetchSouwceWinesC[k] = 0;
			dpte_wow_height_chwoma_one_wow_pew_fwame[k] = 0;
			dpte_wow_width_chwoma_ub_one_wow_pew_fwame[k] = 0;
			PixewPTEBytesPewWowC_one_wow_pew_fwame[k] = 0;
		}

		PDEAndMetaPTEBytesFwameY = dmw32_CawcuwateVMAndWowBytes(
				myPipe[k].ViewpowtStationawy,
				myPipe[k].DCCEnabwe,
				myPipe[k].DPPPewSuwface,
				myPipe[k].BwockHeight256BytesY,
				myPipe[k].BwockWidth256BytesY,
				myPipe[k].SouwcePixewFowmat,
				myPipe[k].SuwfaceTiwing,
				myPipe[k].BytePewPixewY,
				myPipe[k].SouwceWotation,
				SwathWidthY[k],
				myPipe[k].ViewpowtHeight,
				myPipe[k].ViewpowtXStawt,
				myPipe[k].ViewpowtYStawt,
				GPUVMEnabwe,
				HostVMEnabwe,
				HostVMMaxNonCachedPageTabweWevews,
				GPUVMMaxPageTabweWevews,
				GPUVMMinPageSizeKBytes[k],
				HostVMMinPageSize,
				PTEBuffewSizeInWequestsFowWuma[k],
				myPipe[k].PitchY,
				myPipe[k].DCCMetaPitchY,
				myPipe[k].BwockWidthY,
				myPipe[k].BwockHeightY,

				/* Output */
				&MetaWowByteY[k],
				&PixewPTEBytesPewWowY[k],
				&dpte_wow_width_wuma_ub[k],
				&dpte_wow_height_wuma[k],
				&dpte_wow_height_wineaw_wuma[k],
				&PixewPTEBytesPewWowY_one_wow_pew_fwame[k],
				&dpte_wow_width_wuma_ub_one_wow_pew_fwame[k],
				&dpte_wow_height_wuma_one_wow_pew_fwame[k],
				&meta_weq_width[k],
				&meta_weq_height[k],
				&meta_wow_width[k],
				&meta_wow_height[k],
				&PixewPTEWeqWidthY[k],
				&PixewPTEWeqHeightY[k],
				&PTEWequestSizeY[k],
				&dpde0_bytes_pew_fwame_ub_w[k],
				&meta_pte_bytes_pew_fwame_ub_w[k]);

		PwefetchSouwceWinesY[k] = dmw32_CawcuwatePwefetchSouwceWines(
				myPipe[k].VWatio,
				myPipe[k].VTaps,
				myPipe[k].IntewwaceEnabwe,
				myPipe[k].PwogwessiveToIntewwaceUnitInOPP,
				myPipe[k].SwathHeightY,
				myPipe[k].SouwceWotation,
				myPipe[k].ViewpowtStationawy,
				SwathWidthY[k],
				myPipe[k].ViewpowtHeight,
				myPipe[k].ViewpowtXStawt,
				myPipe[k].ViewpowtYStawt,

				/* Output */
				&VInitPweFiwwY[k],
				&MaxNumSwathY[k]);

		PDEAndMetaPTEBytesFwame[k] = PDEAndMetaPTEBytesFwameY + PDEAndMetaPTEBytesFwameC;
		MetaWowByte[k] = MetaWowByteY[k] + MetaWowByteC[k];

		if (PixewPTEBytesPewWowY[k] <= 64 * PTEBuffewSizeInWequestsFowWuma[k] &&
				PixewPTEBytesPewWowC[k] <= 64 * PTEBuffewSizeInWequestsFowChwoma[k]) {
			PTEBuffewSizeNotExceeded[k] = twue;
		} ewse {
			PTEBuffewSizeNotExceeded[k] = fawse;
		}

		one_wow_pew_fwame_fits_in_buffew[k] = (PixewPTEBytesPewWowY_one_wow_pew_fwame[k] <= 64 * 2 *
			PTEBuffewSizeInWequestsFowWuma[k] &&
			PixewPTEBytesPewWowC_one_wow_pew_fwame[k] <= 64 * 2 * PTEBuffewSizeInWequestsFowChwoma[k]);
	}

	dmw32_CawcuwateMAWWUseFowStaticScween(
			NumbewOfActiveSuwfaces,
			MAWWAwwocatedFowDCN,
			UseMAWWFowStaticScween,   // mode
			SuwfaceSizeInMAWW,
			one_wow_pew_fwame_fits_in_buffew,
			/* Output */
			UsesMAWWFowStaticScween); // boowen

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		PTE_BUFFEW_MODE[k] = myPipe[k].FOWCE_ONE_WOW_FOW_FWAME || UsesMAWWFowStaticScween[k] ||
				(UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_sub_viewpowt) ||
				(UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_phantom_pipe) ||
				(GPUVMMinPageSizeKBytes[k] > 64);
		BIGK_FWAGMENT_SIZE[k] = dmw_wog2(GPUVMMinPageSizeKBytes[k] * 1024) - 12;
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d, SuwfaceSizeInMAWW = %d\n",  __func__, k, SuwfaceSizeInMAWW[k]);
		dmw_pwint("DMW::%s: k=%d, UsesMAWWFowStaticScween = %d\n",  __func__, k, UsesMAWWFowStaticScween[k]);
#endif
		use_one_wow_fow_fwame[k] = myPipe[k].FOWCE_ONE_WOW_FOW_FWAME || UsesMAWWFowStaticScween[k] ||
				(UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_sub_viewpowt) ||
				(UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_phantom_pipe) ||
				(GPUVMMinPageSizeKBytes[k] > 64 && IsVewticaw(myPipe[k].SouwceWotation));

		use_one_wow_fow_fwame_fwip[k] = use_one_wow_fow_fwame[k] &&
				!(UseMAWWFowPStateChange[k] == dm_use_maww_pstate_change_fuww_fwame);

		if (use_one_wow_fow_fwame[k]) {
			dpte_wow_height_wuma[k] = dpte_wow_height_wuma_one_wow_pew_fwame[k];
			dpte_wow_width_wuma_ub[k] = dpte_wow_width_wuma_ub_one_wow_pew_fwame[k];
			PixewPTEBytesPewWowY[k] = PixewPTEBytesPewWowY_one_wow_pew_fwame[k];
			dpte_wow_height_chwoma[k] = dpte_wow_height_chwoma_one_wow_pew_fwame[k];
			dpte_wow_width_chwoma_ub[k] = dpte_wow_width_chwoma_ub_one_wow_pew_fwame[k];
			PixewPTEBytesPewWowC[k] = PixewPTEBytesPewWowC_one_wow_pew_fwame[k];
			PTEBuffewSizeNotExceeded[k] = one_wow_pew_fwame_fits_in_buffew[k];
		}

		if (MetaWowByte[k] <= DCCMetaBuffewSizeBytes)
			DCCMetaBuffewSizeNotExceeded[k] = twue;
		ewse
			DCCMetaBuffewSizeNotExceeded[k] = fawse;

		PixewPTEBytesPewWow[k] = PixewPTEBytesPewWowY[k] + PixewPTEBytesPewWowC[k];
		if (use_one_wow_fow_fwame[k])
			PixewPTEBytesPewWow[k] = PixewPTEBytesPewWow[k] / 2;

		dmw32_CawcuwateWowBandwidth(
				GPUVMEnabwe,
				myPipe[k].SouwcePixewFowmat,
				myPipe[k].VWatio,
				myPipe[k].VWatioChwoma,
				myPipe[k].DCCEnabwe,
				myPipe[k].HTotaw / myPipe[k].PixewCwock,
				MetaWowByteY[k], MetaWowByteC[k],
				meta_wow_height[k],
				meta_wow_height_chwoma[k],
				PixewPTEBytesPewWowY[k],
				PixewPTEBytesPewWowC[k],
				dpte_wow_height_wuma[k],
				dpte_wow_height_chwoma[k],

				/* Output */
				&meta_wow_bw[k],
				&dpte_wow_bw[k]);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d, use_one_wow_fow_fwame        = %d\n",  __func__, k, use_one_wow_fow_fwame[k]);
		dmw_pwint("DMW::%s: k=%d, use_one_wow_fow_fwame_fwip   = %d\n",
				__func__, k, use_one_wow_fow_fwame_fwip[k]);
		dmw_pwint("DMW::%s: k=%d, UseMAWWFowPStateChange       = %d\n",
				__func__, k, UseMAWWFowPStateChange[k]);
		dmw_pwint("DMW::%s: k=%d, dpte_wow_height_wuma         = %d\n",  __func__, k, dpte_wow_height_wuma[k]);
		dmw_pwint("DMW::%s: k=%d, dpte_wow_width_wuma_ub       = %d\n",
				__func__, k, dpte_wow_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%d, PixewPTEBytesPewWowY         = %d\n",  __func__, k, PixewPTEBytesPewWowY[k]);
		dmw_pwint("DMW::%s: k=%d, dpte_wow_height_chwoma       = %d\n",
				__func__, k, dpte_wow_height_chwoma[k]);
		dmw_pwint("DMW::%s: k=%d, dpte_wow_width_chwoma_ub     = %d\n",
				__func__, k, dpte_wow_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%d, PixewPTEBytesPewWowC         = %d\n",  __func__, k, PixewPTEBytesPewWowC[k]);
		dmw_pwint("DMW::%s: k=%d, PixewPTEBytesPewWow          = %d\n",  __func__, k, PixewPTEBytesPewWow[k]);
		dmw_pwint("DMW::%s: k=%d, PTEBuffewSizeNotExceeded     = %d\n",
				__func__, k, PTEBuffewSizeNotExceeded[k]);
		dmw_pwint("DMW::%s: k=%d, PTE_BUFFEW_MODE              = %d\n", __func__, k, PTE_BUFFEW_MODE[k]);
		dmw_pwint("DMW::%s: k=%d, BIGK_FWAGMENT_SIZE           = %d\n", __func__, k, BIGK_FWAGMENT_SIZE[k]);
#endif
	}
} // CawcuwateVMWowAndSwath

unsigned int dmw32_CawcuwateVMAndWowBytes(
		boow ViewpowtStationawy,
		boow DCCEnabwe,
		unsigned int NumbewOfDPPs,
		unsigned int BwockHeight256Bytes,
		unsigned int BwockWidth256Bytes,
		enum souwce_fowmat_cwass SouwcePixewFowmat,
		unsigned int SuwfaceTiwing,
		unsigned int BytePewPixew,
		enum dm_wotation_angwe SouwceWotation,
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
		unsigned int    *MetaPTEBytesFwame)
{
	unsigned int MPDEBytesFwame;
	unsigned int DCCMetaSuwfaceBytes;
	unsigned int ExtwaDPDEBytesFwame;
	unsigned int PDEAndMetaPTEBytesFwame;
	unsigned int HostVMDynamicWevews = 0;
	unsigned int    MacwoTiweSizeBytes;
	unsigned int    vp_height_meta_ub;
	unsigned int    vp_height_dpte_ub;
	unsigned int PixewPTEWeqWidth_wineaw = 0; // VBA_DEWTA. VBA doesn't cawcuwate this

	if (GPUVMEnabwe == twue && HostVMEnabwe == twue) {
		if (HostVMMinPageSize < 2048)
			HostVMDynamicWevews = HostVMMaxNonCachedPageTabweWevews;
		ewse if (HostVMMinPageSize >= 2048 && HostVMMinPageSize < 1048576)
			HostVMDynamicWevews = dmw_max(0, (int) HostVMMaxNonCachedPageTabweWevews - 1);
		ewse
			HostVMDynamicWevews = dmw_max(0, (int) HostVMMaxNonCachedPageTabweWevews - 2);
	}

	*MetaWequestHeight = 8 * BwockHeight256Bytes;
	*MetaWequestWidth = 8 * BwockWidth256Bytes;
	if (SuwfaceTiwing == dm_sw_wineaw) {
		*meta_wow_height = 32;
		*meta_wow_width = dmw_fwoow(ViewpowtXStawt + SwathWidth + *MetaWequestWidth - 1, *MetaWequestWidth)
				- dmw_fwoow(ViewpowtXStawt, *MetaWequestWidth);
	} ewse if (!IsVewticaw(SouwceWotation)) {
		*meta_wow_height = *MetaWequestHeight;
		if (ViewpowtStationawy && NumbewOfDPPs == 1) {
			*meta_wow_width = dmw_fwoow(ViewpowtXStawt + SwathWidth + *MetaWequestWidth - 1,
					*MetaWequestWidth) - dmw_fwoow(ViewpowtXStawt, *MetaWequestWidth);
		} ewse {
			*meta_wow_width = dmw_ceiw(SwathWidth - 1, *MetaWequestWidth) + *MetaWequestWidth;
		}
		*MetaWowByte = *meta_wow_width * *MetaWequestHeight * BytePewPixew / 256.0;
	} ewse {
		*meta_wow_height = *MetaWequestWidth;
		if (ViewpowtStationawy && NumbewOfDPPs == 1) {
			*meta_wow_width = dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + *MetaWequestHeight - 1,
					*MetaWequestHeight) - dmw_fwoow(ViewpowtYStawt, *MetaWequestHeight);
		} ewse {
			*meta_wow_width = dmw_ceiw(SwathWidth - 1, *MetaWequestHeight) + *MetaWequestHeight;
		}
		*MetaWowByte = *meta_wow_width * *MetaWequestWidth * BytePewPixew / 256.0;
	}

	if (ViewpowtStationawy && (NumbewOfDPPs == 1 || !IsVewticaw(SouwceWotation))) {
		vp_height_meta_ub = dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + 64 * BwockHeight256Bytes - 1,
				64 * BwockHeight256Bytes) - dmw_fwoow(ViewpowtYStawt, 64 * BwockHeight256Bytes);
	} ewse if (!IsVewticaw(SouwceWotation)) {
		vp_height_meta_ub = dmw_ceiw(ViewpowtHeight - 1, 64 * BwockHeight256Bytes) + 64 * BwockHeight256Bytes;
	} ewse {
		vp_height_meta_ub = dmw_ceiw(SwathWidth - 1, 64 * BwockHeight256Bytes) + 64 * BwockHeight256Bytes;
	}

	DCCMetaSuwfaceBytes = DCCMetaPitch * vp_height_meta_ub * BytePewPixew / 256.0;

	if (GPUVMEnabwe == twue) {
		*MetaPTEBytesFwame = (dmw_ceiw((doubwe) (DCCMetaSuwfaceBytes - 4.0 * 1024.0) /
				(8 * 4.0 * 1024), 1) + 1) * 64;
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

	if (GPUVMEnabwe == twue && GPUVMMaxPageTabweWevews > 1) {
		if (ViewpowtStationawy && (NumbewOfDPPs == 1 || !IsVewticaw(SouwceWotation))) {
			vp_height_dpte_ub = dmw_fwoow(ViewpowtYStawt + ViewpowtHeight +
					MacwoTiweHeight - 1, MacwoTiweHeight) -
					dmw_fwoow(ViewpowtYStawt, MacwoTiweHeight);
		} ewse if (!IsVewticaw(SouwceWotation)) {
			vp_height_dpte_ub = dmw_ceiw(ViewpowtHeight - 1, MacwoTiweHeight) + MacwoTiweHeight;
		} ewse {
			vp_height_dpte_ub = dmw_ceiw(SwathWidth - 1, MacwoTiweHeight) + MacwoTiweHeight;
		}
		*DPDE0BytesFwame = 64 * (dmw_ceiw((Pitch * vp_height_dpte_ub * BytePewPixew - MacwoTiweSizeBytes) /
				(8 * 2097152), 1) + 1);
		ExtwaDPDEBytesFwame = 128 * (GPUVMMaxPageTabweWevews - 2);
	} ewse {
		*DPDE0BytesFwame = 0;
		ExtwaDPDEBytesFwame = 0;
		vp_height_dpte_ub = 0;
	}

	PDEAndMetaPTEBytesFwame = *MetaPTEBytesFwame + MPDEBytesFwame + *DPDE0BytesFwame + ExtwaDPDEBytesFwame;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DCCEnabwe = %d\n", __func__, DCCEnabwe);
	dmw_pwint("DMW::%s: GPUVMEnabwe = %d\n", __func__, GPUVMEnabwe);
	dmw_pwint("DMW::%s: SwModeWineaw = %d\n", __func__, SuwfaceTiwing == dm_sw_wineaw);
	dmw_pwint("DMW::%s: BytePewPixew = %d\n", __func__, BytePewPixew);
	dmw_pwint("DMW::%s: GPUVMMaxPageTabweWevews = %d\n", __func__, GPUVMMaxPageTabweWevews);
	dmw_pwint("DMW::%s: BwockHeight256Bytes = %d\n", __func__, BwockHeight256Bytes);
	dmw_pwint("DMW::%s: BwockWidth256Bytes = %d\n", __func__, BwockWidth256Bytes);
	dmw_pwint("DMW::%s: MacwoTiweHeight = %d\n", __func__, MacwoTiweHeight);
	dmw_pwint("DMW::%s: MacwoTiweWidth = %d\n", __func__, MacwoTiweWidth);
	dmw_pwint("DMW::%s: MetaPTEBytesFwame = %d\n", __func__, *MetaPTEBytesFwame);
	dmw_pwint("DMW::%s: MPDEBytesFwame = %d\n", __func__, MPDEBytesFwame);
	dmw_pwint("DMW::%s: DPDE0BytesFwame = %d\n", __func__, *DPDE0BytesFwame);
	dmw_pwint("DMW::%s: ExtwaDPDEBytesFwame= %d\n", __func__, ExtwaDPDEBytesFwame);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %d\n", __func__, PDEAndMetaPTEBytesFwame);
	dmw_pwint("DMW::%s: ViewpowtHeight = %d\n", __func__, ViewpowtHeight);
	dmw_pwint("DMW::%s: SwathWidth = %d\n", __func__, SwathWidth);
	dmw_pwint("DMW::%s: vp_height_dpte_ub = %d\n", __func__, vp_height_dpte_ub);
#endif

	if (HostVMEnabwe == twue)
		PDEAndMetaPTEBytesFwame = PDEAndMetaPTEBytesFwame * (1 + 8 * HostVMDynamicWevews);

	if (SuwfaceTiwing == dm_sw_wineaw) {
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
	dmw_pwint("DMW::%s: GPUVMMinPageSizeKBytes = %d\n", __func__, GPUVMMinPageSizeKBytes);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %d (aftew HostVM factow)\n", __func__, PDEAndMetaPTEBytesFwame);
	dmw_pwint("DMW::%s: PixewPTEWeqHeight = %d\n", __func__, *PixewPTEWeqHeight);
	dmw_pwint("DMW::%s: PixewPTEWeqWidth = %d\n", __func__, *PixewPTEWeqWidth);
	dmw_pwint("DMW::%s: PixewPTEWeqWidth_wineaw = %d\n", __func__, PixewPTEWeqWidth_wineaw);
	dmw_pwint("DMW::%s: PTEWequestSize = %d\n", __func__, *PTEWequestSize);
	dmw_pwint("DMW::%s: Pitch = %d\n", __func__, Pitch);
#endif

	*dpte_wow_height_one_wow_pew_fwame = vp_height_dpte_ub;
	*dpte_wow_width_ub_one_wow_pew_fwame = (dmw_ceiw(((doubwe)Pitch * (doubwe)*dpte_wow_height_one_wow_pew_fwame /
			(doubwe) *PixewPTEWeqHeight - 1) / (doubwe) *PixewPTEWeqWidth, 1) + 1) *
					(doubwe) *PixewPTEWeqWidth;
	*PixewPTEBytesPewWow_one_wow_pew_fwame = *dpte_wow_width_ub_one_wow_pew_fwame / *PixewPTEWeqWidth *
			*PTEWequestSize;

	if (SuwfaceTiwing == dm_sw_wineaw) {
		*dpte_wow_height = dmw_min(128, 1 << (unsigned int) dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests *
				*PixewPTEWeqWidth / Pitch), 1));
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: dpte_wow_height = %d (1)\n", __func__,
				PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch);
		dmw_pwint("DMW::%s: dpte_wow_height = %f (2)\n", __func__,
				dmw_wog2(PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch));
		dmw_pwint("DMW::%s: dpte_wow_height = %f (3)\n", __func__,
				dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests * *PixewPTEWeqWidth / Pitch), 1));
		dmw_pwint("DMW::%s: dpte_wow_height = %d (4)\n", __func__,
				1 << (unsigned int) dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests *
						*PixewPTEWeqWidth / Pitch), 1));
		dmw_pwint("DMW::%s: dpte_wow_height = %d\n", __func__, *dpte_wow_height);
#endif
		*dpte_wow_width_ub = dmw_ceiw(((doubwe) Pitch * (doubwe) *dpte_wow_height - 1),
				(doubwe) *PixewPTEWeqWidth) + *PixewPTEWeqWidth;
		*PixewPTEBytesPewWow = *dpte_wow_width_ub / (doubwe)*PixewPTEWeqWidth * (doubwe)*PTEWequestSize;

		// VBA_DEWTA, VBA doesn't have pwogwamming vawue fow pte wow height wineaw.
		*dpte_wow_height_wineaw = 1 << (unsigned int) dmw_fwoow(dmw_wog2(PTEBuffewSizeInWequests *
				PixewPTEWeqWidth_wineaw / Pitch), 1);
		if (*dpte_wow_height_wineaw > 128)
			*dpte_wow_height_wineaw = 128;

	} ewse if (!IsVewticaw(SouwceWotation)) {
		*dpte_wow_height = *PixewPTEWeqHeight;

		if (GPUVMMinPageSizeKBytes > 64) {
			*dpte_wow_width_ub = (dmw_ceiw((Pitch * *dpte_wow_height / *PixewPTEWeqHeight - 1) /
					*PixewPTEWeqWidth, 1) + 1) * *PixewPTEWeqWidth;
		} ewse if (ViewpowtStationawy && (NumbewOfDPPs == 1)) {
			*dpte_wow_width_ub = dmw_fwoow(ViewpowtXStawt + SwathWidth +
					*PixewPTEWeqWidth - 1, *PixewPTEWeqWidth) -
					dmw_fwoow(ViewpowtXStawt, *PixewPTEWeqWidth);
		} ewse {
			*dpte_wow_width_ub = (dmw_ceiw((SwathWidth - 1) / *PixewPTEWeqWidth, 1) + 1) *
					*PixewPTEWeqWidth;
		}

		*PixewPTEBytesPewWow = *dpte_wow_width_ub / *PixewPTEWeqWidth * *PTEWequestSize;
	} ewse {
		*dpte_wow_height = dmw_min(*PixewPTEWeqWidth, MacwoTiweWidth);

		if (ViewpowtStationawy && (NumbewOfDPPs == 1)) {
			*dpte_wow_width_ub = dmw_fwoow(ViewpowtYStawt + ViewpowtHeight + *PixewPTEWeqHeight - 1,
					*PixewPTEWeqHeight) - dmw_fwoow(ViewpowtYStawt, *PixewPTEWeqHeight);
		} ewse {
			*dpte_wow_width_ub = (dmw_ceiw((SwathWidth - 1) / *PixewPTEWeqHeight, 1) + 1)
					* *PixewPTEWeqHeight;
		}

		*PixewPTEBytesPewWow = *dpte_wow_width_ub / *PixewPTEWeqHeight * *PTEWequestSize;
	}

	if (GPUVMEnabwe != twue)
		*PixewPTEBytesPewWow = 0;
	if (HostVMEnabwe == twue)
		*PixewPTEBytesPewWow = *PixewPTEBytesPewWow * (1 + 8 * HostVMDynamicWevews);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: GPUVMMinPageSizeKBytes = %d\n", __func__, GPUVMMinPageSizeKBytes);
	dmw_pwint("DMW::%s: dpte_wow_height = %d\n", __func__, *dpte_wow_height);
	dmw_pwint("DMW::%s: dpte_wow_height_wineaw = %d\n", __func__, *dpte_wow_height_wineaw);
	dmw_pwint("DMW::%s: dpte_wow_width_ub = %d\n", __func__, *dpte_wow_width_ub);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %d\n", __func__, *PixewPTEBytesPewWow);
	dmw_pwint("DMW::%s: PTEBuffewSizeInWequests = %d\n", __func__, PTEBuffewSizeInWequests);
	dmw_pwint("DMW::%s: dpte_wow_height_one_wow_pew_fwame = %d\n", __func__, *dpte_wow_height_one_wow_pew_fwame);
	dmw_pwint("DMW::%s: dpte_wow_width_ub_one_wow_pew_fwame = %d\n",
			__func__, *dpte_wow_width_ub_one_wow_pew_fwame);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWow_one_wow_pew_fwame = %d\n",
			__func__, *PixewPTEBytesPewWow_one_wow_pew_fwame);
	dmw_pwint("DMW: vm_bytes = meta_pte_bytes_pew_fwame (pew_pipe) = MetaPTEBytesFwame = : %i\n",
			*MetaPTEBytesFwame);
#endif

	wetuwn PDEAndMetaPTEBytesFwame;
} // CawcuwateVMAndWowBytes

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
		unsigned int *MaxNumSwath)
{

	unsigned int vp_stawt_wot;
	unsigned int sw0_tmp;
	unsigned int MaxPawtiawSwath;
	doubwe numWines;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VWatio = %f\n", __func__, VWatio);
	dmw_pwint("DMW::%s: VTaps = %d\n", __func__, VTaps);
	dmw_pwint("DMW::%s: ViewpowtXStawt = %d\n", __func__, ViewpowtXStawt);
	dmw_pwint("DMW::%s: ViewpowtYStawt = %d\n", __func__, ViewpowtYStawt);
	dmw_pwint("DMW::%s: ViewpowtStationawy = %d\n", __func__, ViewpowtStationawy);
	dmw_pwint("DMW::%s: SwathHeight = %d\n", __func__, SwathHeight);
#endif
	if (PwogwessiveToIntewwaceUnitInOPP)
		*VInitPweFiww = dmw_fwoow((VWatio + (doubwe) VTaps + 1) / 2.0, 1);
	ewse
		*VInitPweFiww = dmw_fwoow((VWatio + (doubwe) VTaps + 1 + Intewwace * 0.5 * VWatio) / 2.0, 1);

	if (ViewpowtStationawy) {
		if (SouwceWotation == dm_wotation_180 || SouwceWotation == dm_wotation_180m) {
			vp_stawt_wot = SwathHeight -
					(((unsigned int) (ViewpowtYStawt + ViewpowtHeight - 1) % SwathHeight) + 1);
		} ewse if (SouwceWotation == dm_wotation_270 || SouwceWotation == dm_wotation_90m) {
			vp_stawt_wot = ViewpowtXStawt;
		} ewse if (SouwceWotation == dm_wotation_90 || SouwceWotation == dm_wotation_270m) {
			vp_stawt_wot = SwathHeight -
					(((unsigned int)(ViewpowtYStawt + SwathWidth - 1) % SwathHeight) + 1);
		} ewse {
			vp_stawt_wot = ViewpowtYStawt;
		}
		sw0_tmp = SwathHeight - (vp_stawt_wot % SwathHeight);
		if (sw0_tmp < *VInitPweFiww)
			*MaxNumSwath = dmw_ceiw((*VInitPweFiww - sw0_tmp) / SwathHeight, 1) + 1;
		ewse
			*MaxNumSwath = 1;
		MaxPawtiawSwath = dmw_max(1, (unsigned int) (vp_stawt_wot + *VInitPweFiww - 1) % SwathHeight);
	} ewse {
		*MaxNumSwath = dmw_ceiw((*VInitPweFiww - 1.0) / SwathHeight, 1) + 1;
		if (*VInitPweFiww > 1)
			MaxPawtiawSwath = dmw_max(1, (unsigned int) (*VInitPweFiww - 2) % SwathHeight);
		ewse
			MaxPawtiawSwath = dmw_max(1, (unsigned int) (*VInitPweFiww + SwathHeight - 2) % SwathHeight);
	}
	numWines = *MaxNumSwath * SwathHeight + MaxPawtiawSwath;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: vp_stawt_wot = %d\n", __func__, vp_stawt_wot);
	dmw_pwint("DMW::%s: VInitPweFiww = %d\n", __func__, *VInitPweFiww);
	dmw_pwint("DMW::%s: MaxPawtiawSwath = %d\n", __func__, MaxPawtiawSwath);
	dmw_pwint("DMW::%s: MaxNumSwath = %d\n", __func__, *MaxNumSwath);
	dmw_pwint("DMW::%s: Pwefetch souwce wines = %3.2f\n", __func__, numWines);
#endif
	wetuwn numWines;

} // CawcuwatePwefetchSouwceWines

void dmw32_CawcuwateMAWWUseFowStaticScween(
		unsigned int NumbewOfActiveSuwfaces,
		unsigned int MAWWAwwocatedFowDCNFinaw,
		enum dm_use_maww_fow_static_scween_mode *UseMAWWFowStaticScween,
		unsigned int SuwfaceSizeInMAWW[],
		boow one_wow_pew_fwame_fits_in_buffew[],

		/* output */
		boow UsesMAWWFowStaticScween[])
{
	unsigned int k;
	unsigned int SuwfaceToAddToMAWW;
	boow CanAddAnothewSuwfaceToMAWW;
	unsigned int TotawSuwfaceSizeInMAWW;

	TotawSuwfaceSizeInMAWW = 0;
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		UsesMAWWFowStaticScween[k] = (UseMAWWFowStaticScween[k] == dm_use_maww_static_scween_enabwe);
		if (UsesMAWWFowStaticScween[k])
			TotawSuwfaceSizeInMAWW = TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[k];
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d, UsesMAWWFowStaticScween = %d\n",  __func__, k, UsesMAWWFowStaticScween[k]);
		dmw_pwint("DMW::%s: k=%d, TotawSuwfaceSizeInMAWW = %d\n",  __func__, k, TotawSuwfaceSizeInMAWW);
#endif
	}

	SuwfaceToAddToMAWW = 0;
	CanAddAnothewSuwfaceToMAWW = twue;
	whiwe (CanAddAnothewSuwfaceToMAWW) {
		CanAddAnothewSuwfaceToMAWW = fawse;
		fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			if (TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[k] <= MAWWAwwocatedFowDCNFinaw * 1024 * 1024 &&
					!UsesMAWWFowStaticScween[k] &&
					UseMAWWFowStaticScween[k] != dm_use_maww_static_scween_disabwe &&
					one_wow_pew_fwame_fits_in_buffew[k] &&
					(!CanAddAnothewSuwfaceToMAWW ||
					SuwfaceSizeInMAWW[k] < SuwfaceSizeInMAWW[SuwfaceToAddToMAWW])) {
				CanAddAnothewSuwfaceToMAWW = twue;
				SuwfaceToAddToMAWW = k;
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%d, UseMAWWFowStaticScween = %d (dis, en, optimize)\n",
						__func__, k, UseMAWWFowStaticScween[k]);
#endif
			}
		}
		if (CanAddAnothewSuwfaceToMAWW) {
			UsesMAWWFowStaticScween[SuwfaceToAddToMAWW] = twue;
			TotawSuwfaceSizeInMAWW = TotawSuwfaceSizeInMAWW + SuwfaceSizeInMAWW[SuwfaceToAddToMAWW];

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: SuwfaceToAddToMAWW       = %d\n",  __func__, SuwfaceToAddToMAWW);
			dmw_pwint("DMW::%s: TotawSuwfaceSizeInMAWW   = %d\n",  __func__, TotawSuwfaceSizeInMAWW);
#endif

		}
	}
}

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
		doubwe *dpte_wow_bw)
{
	if (DCCEnabwe != twue) {
		*meta_wow_bw = 0;
	} ewse if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10 || SouwcePixewFowmat == dm_420_12 ||
			SouwcePixewFowmat == dm_wgbe_awpha) {
		*meta_wow_bw = VWatio * MetaWowByteWuma / (meta_wow_height_wuma * WineTime) + VWatioChwoma *
				MetaWowByteChwoma / (meta_wow_height_chwoma * WineTime);
	} ewse {
		*meta_wow_bw = VWatio * MetaWowByteWuma / (meta_wow_height_wuma * WineTime);
	}

	if (GPUVMEnabwe != twue) {
		*dpte_wow_bw = 0;
	} ewse if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10 || SouwcePixewFowmat == dm_420_12 ||
			SouwcePixewFowmat == dm_wgbe_awpha) {
		*dpte_wow_bw = VWatio * PixewPTEBytesPewWowWuma / (dpte_wow_height_wuma * WineTime) +
				VWatioChwoma * PixewPTEBytesPewWowChwoma / (dpte_wow_height_chwoma * WineTime);
	} ewse {
		*dpte_wow_bw = VWatio * PixewPTEBytesPewWowWuma / (dpte_wow_height_wuma * WineTime);
	}
}

doubwe dmw32_CawcuwateUwgentWatency(
		doubwe UwgentWatencyPixewDataOnwy,
		doubwe UwgentWatencyPixewMixedWithVMData,
		doubwe UwgentWatencyVMDataOnwy,
		boow   DoUwgentWatencyAdjustment,
		doubwe UwgentWatencyAdjustmentFabwicCwockComponent,
		doubwe UwgentWatencyAdjustmentFabwicCwockWefewence,
		doubwe FabwicCwock)
{
	doubwe   wet;

	wet = dmw_max3(UwgentWatencyPixewDataOnwy, UwgentWatencyPixewMixedWithVMData, UwgentWatencyVMDataOnwy);
	if (DoUwgentWatencyAdjustment == twue) {
		wet = wet + UwgentWatencyAdjustmentFabwicCwockComponent *
				(UwgentWatencyAdjustmentFabwicCwockWefewence / FabwicCwock - 1);
	}
	wetuwn wet;
}

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
		boow   *NotEnoughUwgentWatencyHiding)
{
	doubwe       WinesInDETWuma;
	doubwe       WinesInDETChwoma;
	unsigned int WinesInCuwsowBuffew;
	doubwe       CuwsowBuffewSizeInTime;
	doubwe       DETBuffewSizeInTimeWuma;
	doubwe       DETBuffewSizeInTimeChwoma;

	*NotEnoughUwgentWatencyHiding = 0;

	if (CuwsowWidth > 0) {
		WinesInCuwsowBuffew = 1 << (unsigned int) dmw_fwoow(dmw_wog2(CuwsowBuffewSize * 1024.0 /
				(CuwsowWidth * CuwsowBPP / 8.0)), 1.0);
		if (VWatio > 0) {
			CuwsowBuffewSizeInTime = WinesInCuwsowBuffew * WineTime / VWatio;
			if (CuwsowBuffewSizeInTime - UwgentWatency <= 0) {
				*NotEnoughUwgentWatencyHiding = 1;
				*UwgentBuwstFactowCuwsow = 0;
			} ewse {
				*UwgentBuwstFactowCuwsow = CuwsowBuffewSizeInTime /
						(CuwsowBuffewSizeInTime - UwgentWatency);
			}
		} ewse {
			*UwgentBuwstFactowCuwsow = 1;
		}
	}

	WinesInDETWuma = (UseMAWWFowPStateChange == dm_use_maww_pstate_change_phantom_pipe ? 1024*1024 :
			DETBuffewSizeY) / BytePewPixewInDETY / swath_width_wuma_ub;

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
		WinesInDETChwoma = (UseMAWWFowPStateChange == dm_use_maww_pstate_change_phantom_pipe ?
					1024 * 1024 : DETBuffewSizeC) / BytePewPixewInDETC
					/ swath_width_chwoma_ub;

		if (VWatio > 0) {
			DETBuffewSizeInTimeChwoma = dmw_fwoow(WinesInDETChwoma, SwathHeightC) * WineTime / VWatio;
			if (DETBuffewSizeInTimeChwoma - UwgentWatency <= 0) {
				*NotEnoughUwgentWatencyHiding = 1;
				*UwgentBuwstFactowChwoma = 0;
			} ewse {
				*UwgentBuwstFactowChwoma = DETBuffewSizeInTimeChwoma
						/ (DETBuffewSizeInTimeChwoma - UwgentWatency);
			}
		} ewse {
			*UwgentBuwstFactowChwoma = 1;
		}
	}
} // CawcuwateUwgentBuwstFactow

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
		doubwe *DCFCwkDeepSweep)
{
	unsigned int k;
	doubwe   DispwayPipeWineDewivewyTimeWuma;
	doubwe   DispwayPipeWineDewivewyTimeChwoma;
	doubwe   DCFCwkDeepSweepPewSuwface[DC__NUM_DPP__MAX];
	doubwe WeadBandwidth = 0.0;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {

		if (VWatio[k] <= 1) {
			DispwayPipeWineDewivewyTimeWuma = SwathWidthY[k] * DPPPewSuwface[k] / HWatio[k]
					/ PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWuma = SwathWidthY[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k];
		}
		if (BytePewPixewC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwoma = 0;
		} ewse {
			if (VWatioChwoma[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwoma = SwathWidthC[k] *
						DPPPewSuwface[k] / HWatioChwoma[k] / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwoma = SwathWidthC[k] / PSCW_THWOUGHPUT_CHWOMA[k]
						/ Dppcwk[k];
			}
		}

		if (BytePewPixewC[k] > 0) {
			DCFCwkDeepSweepPewSuwface[k] = dmw_max(__DMW_MIN_DCFCWK_FACTOW__ * SwathWidthY[k] *
					BytePewPixewY[k] / 32.0 / DispwayPipeWineDewivewyTimeWuma,
					__DMW_MIN_DCFCWK_FACTOW__ * SwathWidthC[k] * BytePewPixewC[k] /
					32.0 / DispwayPipeWineDewivewyTimeChwoma);
		} ewse {
			DCFCwkDeepSweepPewSuwface[k] = __DMW_MIN_DCFCWK_FACTOW__ * SwathWidthY[k] * BytePewPixewY[k] /
					64.0 / DispwayPipeWineDewivewyTimeWuma;
		}
		DCFCwkDeepSweepPewSuwface[k] = dmw_max(DCFCwkDeepSweepPewSuwface[k], PixewCwock[k] / 16);

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d, PixewCwock = %f\n", __func__, k, PixewCwock[k]);
		dmw_pwint("DMW::%s: k=%d, DCFCwkDeepSweepPewSuwface = %f\n", __func__, k, DCFCwkDeepSweepPewSuwface[k]);
#endif
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k)
		WeadBandwidth = WeadBandwidth + WeadBandwidthWuma[k] + WeadBandwidthChwoma[k];

	*DCFCwkDeepSweep = dmw_max(8.0, __DMW_MIN_DCFCWK_FACTOW__ * WeadBandwidth / (doubwe) WetuwnBusWidth);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: __DMW_MIN_DCFCWK_FACTOW__ = %f\n", __func__, __DMW_MIN_DCFCWK_FACTOW__);
	dmw_pwint("DMW::%s: WeadBandwidth = %f\n", __func__, WeadBandwidth);
	dmw_pwint("DMW::%s: WetuwnBusWidth = %d\n", __func__, WetuwnBusWidth);
	dmw_pwint("DMW::%s: DCFCwkDeepSweep = %f\n", __func__, *DCFCwkDeepSweep);
#endif

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k)
		*DCFCwkDeepSweep = dmw_max(*DCFCwkDeepSweep, DCFCwkDeepSweepPewSuwface[k]);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DCFCwkDeepSweep = %f (finaw)\n", __func__, *DCFCwkDeepSweep);
#endif
} // CawcuwateDCFCWKDeepSweep

doubwe dmw32_CawcuwateWwiteBackDeway(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackVTaps,
		unsigned int         WwitebackDestinationWidth,
		unsigned int         WwitebackDestinationHeight,
		unsigned int         WwitebackSouwceHeight,
		unsigned int HTotaw)
{
	doubwe CawcuwateWwiteBackDeway;
	doubwe Wine_wength;
	doubwe Output_wines_wast_notcwamped;
	doubwe WwitebackVInit;

	WwitebackVInit = (WwitebackVWatio + WwitebackVTaps + 1) / 2;
	Wine_wength = dmw_max((doubwe) WwitebackDestinationWidth,
			dmw_ceiw((doubwe)WwitebackDestinationWidth / 6.0, 1.0) * WwitebackVTaps);
	Output_wines_wast_notcwamped = WwitebackDestinationHeight - 1 -
			dmw_ceiw(((doubwe)WwitebackSouwceHeight -
					(doubwe) WwitebackVInit) / (doubwe)WwitebackVWatio, 1.0);
	if (Output_wines_wast_notcwamped < 0) {
		CawcuwateWwiteBackDeway = 0;
	} ewse {
		CawcuwateWwiteBackDeway = Output_wines_wast_notcwamped * Wine_wength +
				(HTotaw - WwitebackDestinationWidth) + 80;
	}
	wetuwn CawcuwateWwiteBackDeway;
}

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
		doubwe DCFCWKState[][2])
{
	unsigned int i, j, k;
	unsigned int     dummy1;
	doubwe dummy2, dummy3;
	doubwe   NowmawEfficiency;
	doubwe   TotawMaxPwefetchFwipDPTEWowBandwidth[DC__VOWTAGE_STATES][2];

	NowmawEfficiency = PewcentOfIdeawSDPPowtBWWeceivedAftewUwgWatency / 100.0;
	fow  (i = 0; i < DC__VOWTAGE_STATES; ++i) {
		fow  (j = 0; j <= 1; ++j) {
			doubwe PixewDCFCWKCycwesWequiwedInPwefetch[DC__NUM_DPP__MAX];
			doubwe PwefetchPixewWinesTime[DC__NUM_DPP__MAX];
			doubwe DCFCWKWequiwedFowPeakBandwidthPewSuwface[DC__NUM_DPP__MAX];
			doubwe DynamicMetadataVMExtwaWatency[DC__NUM_DPP__MAX];
			doubwe MinimumTWait = 0.0;
			doubwe DPTEBandwidth;
			doubwe DCFCWKWequiwedFowAvewageBandwidth;
			unsigned int ExtwaWatencyBytes;
			doubwe ExtwaWatencyCycwes;
			doubwe DCFCWKWequiwedFowPeakBandwidth;
			unsigned int NoOfDPPState[DC__NUM_DPP__MAX];
			doubwe MinimumTvmPwus2Tw0;

			TotawMaxPwefetchFwipDPTEWowBandwidth[i][j] = 0;
			fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
				TotawMaxPwefetchFwipDPTEWowBandwidth[i][j] = TotawMaxPwefetchFwipDPTEWowBandwidth[i][j]
						+ NoOfDPP[i][j][k] * DPTEBytesPewWow[i][j][k]
								/ (15.75 * HTotaw[k] / PixewCwock[k]);
			}

			fow (k = 0; k <= NumbewOfActiveSuwfaces - 1; ++k)
				NoOfDPPState[k] = NoOfDPP[i][j][k];

			DPTEBandwidth = TotawMaxPwefetchFwipDPTEWowBandwidth[i][j];
			DCFCWKWequiwedFowAvewageBandwidth = dmw_max(PwojectedDCFCwkDeepSweep[i][j], DPTEBandwidth / NowmawEfficiency / WetuwnBusWidth);

			ExtwaWatencyBytes = dmw32_CawcuwateExtwaWatencyBytes(WeowdewingBytes,
					TotawNumbewOfActiveDPP[i][j], PixewChunkSizeInKByte,
					TotawNumbewOfDCCActiveDPP[i][j], MetaChunkSize, GPUVMEnabwe, HostVMEnabwe,
					NumbewOfActiveSuwfaces, NoOfDPPState, dpte_gwoup_bytes, 1, HostVMMinPageSize,
					HostVMMaxNonCachedPageTabweWevews);
			ExtwaWatencyCycwes = WoundTwipPingWatencyCycwes + __DMW_AWB_TO_WET_DEWAY__
					+ ExtwaWatencyBytes / NowmawEfficiency / WetuwnBusWidth;
			fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
				doubwe DCFCWKCycwesWequiwedInPwefetch;
				doubwe PwefetchTime;

				PixewDCFCWKCycwesWequiwedInPwefetch[k] = (PwefetchWinesY[i][j][k]
						* swath_width_wuma_ub_aww_states[i][j][k] * BytePewPixewY[k]
						+ PwefetchWinesC[i][j][k] * swath_width_chwoma_ub_aww_states[i][j][k]
								* BytePewPixewC[k]) / NowmawEfficiency
						/ WetuwnBusWidth;
				DCFCWKCycwesWequiwedInPwefetch = 2 * ExtwaWatencyCycwes / NoOfDPPState[k]
						+ PDEAndMetaPTEBytesPewFwame[i][j][k] / NowmawEfficiency
								/ NowmawEfficiency / WetuwnBusWidth
								* (GPUVMMaxPageTabweWevews > 2 ? 1 : 0)
						+ 2 * DPTEBytesPewWow[i][j][k] / NowmawEfficiency / NowmawEfficiency
								/ WetuwnBusWidth
						+ 2 * MetaWowBytes[i][j][k] / NowmawEfficiency / WetuwnBusWidth
						+ PixewDCFCWKCycwesWequiwedInPwefetch[k];
				PwefetchPixewWinesTime[k] = dmw_max(PwefetchWinesY[i][j][k], PwefetchWinesC[i][j][k])
						* HTotaw[k] / PixewCwock[k];
				DynamicMetadataVMExtwaWatency[k] = (GPUVMEnabwe == twue &&
						DynamicMetadataEnabwe[k] == twue && DynamicMetadataVMEnabwed == twue) ?
						UwgWatency[i] * GPUVMMaxPageTabweWevews *
						(HostVMEnabwe == twue ? HostVMMaxNonCachedPageTabweWevews + 1 : 1) : 0;

				MinimumTWait = dmw32_CawcuwateTWait(MaxPwefetchMode,
						UseMAWWFowPStateChange[k],
						SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
						DWWDispway[k],
						DWAMCwockChangeWatencyFinaw,
						FCWKChangeWatency,
						UwgWatency[i],
						SWEntewPwusExitTime);

				PwefetchTime = (MaximumVStawtup[i][j][k] - 1) * HTotaw[k] / PixewCwock[k] -
						MinimumTWait - UwgWatency[i] *
						((GPUVMMaxPageTabweWevews <= 2 ? GPUVMMaxPageTabweWevews :
						GPUVMMaxPageTabweWevews - 2) *  (HostVMEnabwe == twue ?
						HostVMMaxNonCachedPageTabweWevews + 1 : 1) - 1) -
						DynamicMetadataVMExtwaWatency[k];

				if (PwefetchTime > 0) {
					doubwe ExpectedVWatioPwefetch;

					ExpectedVWatioPwefetch = PwefetchPixewWinesTime[k] / (PwefetchTime *
							PixewDCFCWKCycwesWequiwedInPwefetch[k] /
							DCFCWKCycwesWequiwedInPwefetch);
					DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = NoOfDPPState[k] *
							PixewDCFCWKCycwesWequiwedInPwefetch[k] /
							PwefetchPixewWinesTime[k] *
							dmw_max(1.0, ExpectedVWatioPwefetch) *
							dmw_max(1.0, ExpectedVWatioPwefetch / 4);
					if (HostVMEnabwe == twue || ImmediateFwipWequiwement == twue) {
						DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] =
								DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] +
								NoOfDPPState[k] * DPTEBandwidth / NowmawEfficiency /
								NowmawEfficiency / WetuwnBusWidth;
					}
				} ewse {
					DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = DCFCWKPewState[i];
				}
				if (DynamicMetadataEnabwe[k] == twue) {
					doubwe TSetupPipe;
					doubwe TdmbfPipe;
					doubwe TdmsksPipe;
					doubwe TdmecPipe;
					doubwe AwwowedTimeFowUwgentExtwaWatency;

					dmw32_CawcuwateVUpdateAndDynamicMetadataPawametews(
							MaxIntewDCNTiweWepeatews,
							WequiwedDPPCWKPewSuwface[i][j][k],
							WequiwedDISPCWK[i][j],
							PwojectedDCFCwkDeepSweep[i][j],
							PixewCwock[k],
							HTotaw[k],
							VTotaw[k] - VActive[k],
							DynamicMetadataTwansmittedBytes[k],
							DynamicMetadataWinesBefoweActiveWequiwed[k],
							Intewwace[k],
							PwogwessiveToIntewwaceUnitInOPP,

							/* output */
							&TSetupPipe,
							&TdmbfPipe,
							&TdmecPipe,
							&TdmsksPipe,
							&dummy1,
							&dummy2,
							&dummy3);
					AwwowedTimeFowUwgentExtwaWatency = MaximumVStawtup[i][j][k] * HTotaw[k] /
							PixewCwock[k] - MinimumTWait - TSetupPipe - TdmbfPipe -
							TdmecPipe - TdmsksPipe - DynamicMetadataVMExtwaWatency[k];
					if (AwwowedTimeFowUwgentExtwaWatency > 0)
						DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] =
								dmw_max(DCFCWKWequiwedFowPeakBandwidthPewSuwface[k],
								ExtwaWatencyCycwes / AwwowedTimeFowUwgentExtwaWatency);
					ewse
						DCFCWKWequiwedFowPeakBandwidthPewSuwface[k] = DCFCWKPewState[i];
				}
			}
			DCFCWKWequiwedFowPeakBandwidth = 0;
			fow (k = 0; k <= NumbewOfActiveSuwfaces - 1; ++k) {
				DCFCWKWequiwedFowPeakBandwidth = DCFCWKWequiwedFowPeakBandwidth +
						DCFCWKWequiwedFowPeakBandwidthPewSuwface[k];
			}
			MinimumTvmPwus2Tw0 = UwgWatency[i] * (GPUVMEnabwe == twue ?
					(HostVMEnabwe == twue ? (GPUVMMaxPageTabweWevews + 2) *
					(HostVMMaxNonCachedPageTabweWevews + 1) - 1 : GPUVMMaxPageTabweWevews + 1) : 0);
			fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
				doubwe MaximumTvmPwus2Tw0PwusTsw;

				MaximumTvmPwus2Tw0PwusTsw = (MaximumVStawtup[i][j][k] - 2) * HTotaw[k] /
						PixewCwock[k] - MinimumTWait - DynamicMetadataVMExtwaWatency[k];
				if (MaximumTvmPwus2Tw0PwusTsw <= MinimumTvmPwus2Tw0 + PwefetchPixewWinesTime[k] / 4) {
					DCFCWKWequiwedFowPeakBandwidth = DCFCWKPewState[i];
				} ewse {
					DCFCWKWequiwedFowPeakBandwidth = dmw_max3(DCFCWKWequiwedFowPeakBandwidth,
							2 * ExtwaWatencyCycwes / (MaximumTvmPwus2Tw0PwusTsw -
								MinimumTvmPwus2Tw0 -
								PwefetchPixewWinesTime[k] / 4),
							(2 * ExtwaWatencyCycwes +
								PixewDCFCWKCycwesWequiwedInPwefetch[k]) /
								(MaximumTvmPwus2Tw0PwusTsw - MinimumTvmPwus2Tw0));
				}
			}
			DCFCWKState[i][j] = dmw_min(DCFCWKPewState[i], 1.05 *
					dmw_max(DCFCWKWequiwedFowAvewageBandwidth, DCFCWKWequiwedFowPeakBandwidth));
		}
	}
}

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
		unsigned int HostVMMaxNonCachedPageTabweWevews)
{
	unsigned int k;
	doubwe   wet;
	unsigned int  HostVMDynamicWevews;

	if (GPUVMEnabwe == twue && HostVMEnabwe == twue) {
		if (HostVMMinPageSize < 2048)
			HostVMDynamicWevews = HostVMMaxNonCachedPageTabweWevews;
		ewse if (HostVMMinPageSize >= 2048 && HostVMMinPageSize < 1048576)
			HostVMDynamicWevews = dmw_max(0, (int) HostVMMaxNonCachedPageTabweWevews - 1);
		ewse
			HostVMDynamicWevews = dmw_max(0, (int) HostVMMaxNonCachedPageTabweWevews - 2);
	} ewse {
		HostVMDynamicWevews = 0;
	}

	wet = WeowdewingBytes + (TotawNumbewOfActiveDPP * PixewChunkSizeInKByte +
			TotawNumbewOfDCCActiveDPP * MetaChunkSize) * 1024.0;

	if (GPUVMEnabwe == twue) {
		fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
			wet = wet + NumbewOfDPP[k] * dpte_gwoup_bytes[k] *
					(1 + 8 * HostVMDynamicWevews) * HostVMInefficiencyFactow;
		}
	}
	wetuwn wet;
}

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

		/* output */
		doubwe *TSetup,
		doubwe *Tdmbf,
		doubwe *Tdmec,
		doubwe *Tdmsks,
		unsigned int *VUpdateOffsetPix,
		doubwe *VUpdateWidthPix,
		doubwe *VWeadyOffsetPix)
{
	doubwe TotawWepeatewDewayTime;

	TotawWepeatewDewayTime = MaxIntewDCNTiweWepeatews * (2 / Dppcwk + 3 / Dispcwk);
	*VUpdateWidthPix  =
			dmw_ceiw((14.0 / DCFCwkDeepSweep + 12.0 / Dppcwk + TotawWepeatewDewayTime) * PixewCwock, 1.0);
	*VWeadyOffsetPix  = dmw_ceiw(dmw_max(150.0 / Dppcwk,
			TotawWepeatewDewayTime + 20.0 / DCFCwkDeepSweep + 10.0 / Dppcwk) * PixewCwock, 1.0);
	*VUpdateOffsetPix = dmw_ceiw(HTotaw / 4.0, 1.0);
	*TSetup = (*VUpdateOffsetPix + *VUpdateWidthPix + *VWeadyOffsetPix) / PixewCwock;
	*Tdmbf = DynamicMetadataTwansmittedBytes / 4.0 / Dispcwk;
	*Tdmec = HTotaw / PixewCwock;

	if (DynamicMetadataWinesBefoweActiveWequiwed == 0)
		*Tdmsks = VBwank * HTotaw / PixewCwock / 2.0;
	ewse
		*Tdmsks = DynamicMetadataWinesBefoweActiveWequiwed * HTotaw / PixewCwock;

	if (IntewwaceEnabwe == 1 && PwogwessiveToIntewwaceUnitInOPP == fawse)
		*Tdmsks = *Tdmsks / 2;
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VUpdateWidthPix = %d\n", __func__, *VUpdateWidthPix);
	dmw_pwint("DMW::%s: VWeadyOffsetPix = %d\n", __func__, *VWeadyOffsetPix);
	dmw_pwint("DMW::%s: VUpdateOffsetPix = %d\n", __func__, *VUpdateOffsetPix);

	dmw_pwint("DMW::%s: DynamicMetadataWinesBefoweActiveWequiwed = %d\n",
			__func__, DynamicMetadataWinesBefoweActiveWequiwed);
	dmw_pwint("DMW::%s: VBwank = %d\n", __func__, VBwank);
	dmw_pwint("DMW::%s: HTotaw = %d\n", __func__, HTotaw);
	dmw_pwint("DMW::%s: PixewCwock = %f\n", __func__, PixewCwock);
	dmw_pwint("DMW::%s: Tdmsks = %f\n", __func__, *Tdmsks);
#endif
}

doubwe dmw32_CawcuwateTWait(
		unsigned int PwefetchMode,
		enum dm_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange,
		boow SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw,
		boow DWWDispway,
		doubwe DWAMCwockChangeWatency,
		doubwe FCWKChangeWatency,
		doubwe UwgentWatency,
		doubwe SWEntewPwusExitTime)
{
	doubwe TWait = 0.0;

	if (PwefetchMode == 0 &&
			!(UseMAWWFowPStateChange == dm_use_maww_pstate_change_fuww_fwame) &&
			!(UseMAWWFowPStateChange == dm_use_maww_pstate_change_sub_viewpowt) &&
			!(UseMAWWFowPStateChange == dm_use_maww_pstate_change_phantom_pipe) &&
			!(SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw && DWWDispway)) {
		TWait = dmw_max3(DWAMCwockChangeWatency + UwgentWatency, SWEntewPwusExitTime, UwgentWatency);
	} ewse if (PwefetchMode <= 1 && !(UseMAWWFowPStateChange == dm_use_maww_pstate_change_phantom_pipe)) {
		TWait = dmw_max3(FCWKChangeWatency + UwgentWatency, SWEntewPwusExitTime, UwgentWatency);
	} ewse if (PwefetchMode <= 2 && !(UseMAWWFowPStateChange == dm_use_maww_pstate_change_phantom_pipe)) {
		TWait = dmw_max(SWEntewPwusExitTime, UwgentWatency);
	} ewse {
		TWait = UwgentWatency;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: PwefetchMode = %d\n", __func__, PwefetchMode);
	dmw_pwint("DMW::%s: TWait = %f\n", __func__, TWait);
#endif
	wetuwn TWait;
} // CawcuwateTWait

// Function: get_wetuwn_bw_mbps
// Megabyte pew second
doubwe dmw32_get_wetuwn_bw_mbps(const soc_bounding_box_st *soc,
		const int VowtageWevew,
		const boow HostVMEnabwe,
		const doubwe DCFCWK,
		const doubwe FabwicCwock,
		const doubwe DWAMSpeed)
{
	doubwe WetuwnBW = 0.;
	doubwe IdeawSDPPowtBandwidth    = soc->wetuwn_bus_width_bytes /*mode_wib->vba.WetuwnBusWidth*/ * DCFCWK;
	doubwe IdeawFabwicBandwidth     = FabwicCwock * soc->fabwic_datapath_to_dcn_data_wetuwn_bytes;
	doubwe IdeawDWAMBandwidth       = DWAMSpeed * soc->num_chans * soc->dwam_channew_width_bytes;
	doubwe PixewDataOnwyWetuwnBW    = dmw_min3(IdeawSDPPowtBandwidth * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100,
			IdeawFabwicBandwidth * soc->pct_ideaw_fabwic_bw_aftew_uwgent / 100,
			IdeawDWAMBandwidth * (VowtageWevew < 2 ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe  :
					soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy) / 100);
	doubwe PixewMixedWithVMDataWetuwnBW = dmw_min3(IdeawSDPPowtBandwidth * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100,
			IdeawFabwicBandwidth * soc->pct_ideaw_fabwic_bw_aftew_uwgent / 100,
			IdeawDWAMBandwidth * (VowtageWevew < 2 ? soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :
					soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy) / 100);

	if (HostVMEnabwe != twue)
		WetuwnBW = PixewDataOnwyWetuwnBW;
	ewse
		WetuwnBW = PixewMixedWithVMDataWetuwnBW;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VowtageWevew = %d\n", __func__, VowtageWevew);
	dmw_pwint("DMW::%s: HostVMEnabwe = %d\n", __func__, HostVMEnabwe);
	dmw_pwint("DMW::%s: DCFCWK       = %f\n", __func__, DCFCWK);
	dmw_pwint("DMW::%s: FabwicCwock  = %f\n", __func__, FabwicCwock);
	dmw_pwint("DMW::%s: DWAMSpeed    = %f\n", __func__, DWAMSpeed);
	dmw_pwint("DMW::%s: IdeawSDPPowtBandwidth        = %f\n", __func__, IdeawSDPPowtBandwidth);
	dmw_pwint("DMW::%s: IdeawFabwicBandwidth         = %f\n", __func__, IdeawFabwicBandwidth);
	dmw_pwint("DMW::%s: IdeawDWAMBandwidth           = %f\n", __func__, IdeawDWAMBandwidth);
	dmw_pwint("DMW::%s: PixewDataOnwyWetuwnBW        = %f\n", __func__, PixewDataOnwyWetuwnBW);
	dmw_pwint("DMW::%s: PixewMixedWithVMDataWetuwnBW = %f\n", __func__, PixewMixedWithVMDataWetuwnBW);
	dmw_pwint("DMW::%s: WetuwnBW                     = %f MBps\n", __func__, WetuwnBW);
#endif
	wetuwn WetuwnBW;
}

// Function: get_wetuwn_bw_mbps_vm_onwy
// Megabyte pew second
doubwe dmw32_get_wetuwn_bw_mbps_vm_onwy(const soc_bounding_box_st *soc,
		const int VowtageWevew,
		const doubwe DCFCWK,
		const doubwe FabwicCwock,
		const doubwe DWAMSpeed)
{
	doubwe VMDataOnwyWetuwnBW = dmw_min3(
			soc->wetuwn_bus_width_bytes * DCFCWK * soc->pct_ideaw_sdp_bw_aftew_uwgent / 100.0,
			FabwicCwock * soc->fabwic_datapath_to_dcn_data_wetuwn_bytes
					* soc->pct_ideaw_sdp_bw_aftew_uwgent / 100.0,
			DWAMSpeed * soc->num_chans * soc->dwam_channew_width_bytes
					* (VowtageWevew < 2 ?
							soc->pct_ideaw_dwam_bw_aftew_uwgent_stwobe :
							soc->pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy) / 100.0);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VowtageWevew = %d\n", __func__, VowtageWevew);
	dmw_pwint("DMW::%s: DCFCWK       = %f\n", __func__, DCFCWK);
	dmw_pwint("DMW::%s: FabwicCwock  = %f\n", __func__, FabwicCwock);
	dmw_pwint("DMW::%s: DWAMSpeed    = %f\n", __func__, DWAMSpeed);
	dmw_pwint("DMW::%s: VMDataOnwyWetuwnBW = %f\n", __func__, VMDataOnwyWetuwnBW);
#endif
	wetuwn VMDataOnwyWetuwnBW;
}

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
		unsigned int HostVMMaxNonCachedPageTabweWevews)
{
	doubwe ExtwaWatencyBytes;
	doubwe ExtwaWatency;

	ExtwaWatencyBytes = dmw32_CawcuwateExtwaWatencyBytes(
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
	dmw_pwint("DMW::%s: WoundTwipPingWatencyCycwes=%d\n", __func__, WoundTwipPingWatencyCycwes);
	dmw_pwint("DMW::%s: DCFCWK=%f\n", __func__, DCFCWK);
	dmw_pwint("DMW::%s: ExtwaWatencyBytes=%f\n", __func__, ExtwaWatencyBytes);
	dmw_pwint("DMW::%s: WetuwnBW=%f\n", __func__, WetuwnBW);
	dmw_pwint("DMW::%s: ExtwaWatency=%f\n", __func__, ExtwaWatency);
#endif

	wetuwn ExtwaWatency;
} // CawcuwateExtwaWatency

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
		doubwe   *VWeadyOffsetPix)
{
	doubwe DPPCWKDewaySubtotawPwusCNVCFowmatew = v->DPPCWKDewaySubtotaw + v->DPPCWKDewayCNVCFowmatew;
	boow MyEwwow = fawse;
	unsigned int DPPCycwes, DISPCWKCycwes;
	doubwe DSTTotawPixewsAftewScawew;
	doubwe WineTime;
	doubwe dst_y_pwefetch_equ;
	doubwe pwefetch_bw_oto;
	doubwe Tvm_oto;
	doubwe Tw0_oto;
	doubwe Tvm_oto_wines;
	doubwe Tw0_oto_wines;
	doubwe dst_y_pwefetch_oto;
	doubwe TimeFowFetchingMetaPTE = 0;
	doubwe TimeFowFetchingWowInVBwank = 0;
	doubwe WinesToWequestPwefetchPixewData = 0;
	doubwe WinesFowPwefetchBandwidth = 0;
	unsigned int HostVMDynamicWevewsTwips;
	doubwe  twip_to_mem;
	doubwe  Tvm_twips;
	doubwe  Tw0_twips;
	doubwe  Tvm_twips_wounded;
	doubwe  Tw0_twips_wounded;
	doubwe  Wsw_oto;
	doubwe  Tpwe_wounded;
	doubwe  pwefetch_bw_equ;
	doubwe  Tvm_equ;
	doubwe  Tw0_equ;
	doubwe  Tdmbf;
	doubwe  Tdmec;
	doubwe  Tdmsks;
	doubwe  pwefetch_sw_bytes;
	doubwe  bytes_pp;
	doubwe  dep_bytes;
	unsigned int max_vwatio_pwe = v->MaxVWatioPwe;
	doubwe  min_Wsw;
	doubwe  Tsw_est1 = 0;
	doubwe  Tsw_est3 = 0;

	if (v->GPUVMEnabwe == twue && v->HostVMEnabwe == twue)
		HostVMDynamicWevewsTwips = v->HostVMMaxNonCachedPageTabweWevews;
	ewse
		HostVMDynamicWevewsTwips = 0;
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: v->GPUVMEnabwe = %d\n", __func__, v->GPUVMEnabwe);
	dmw_pwint("DMW::%s: v->GPUVMMaxPageTabweWevews = %d\n", __func__, v->GPUVMMaxPageTabweWevews);
	dmw_pwint("DMW::%s: DCCEnabwe = %d\n", __func__, myPipe->DCCEnabwe);
	dmw_pwint("DMW::%s: v->HostVMEnabwe=%d HostVMInefficiencyFactow=%f\n",
			__func__, v->HostVMEnabwe, HostVMInefficiencyFactow);
#endif
	dmw32_CawcuwateVUpdateAndDynamicMetadataPawametews(
			v->MaxIntewDCNTiweWepeatews,
			myPipe->Dppcwk,
			myPipe->Dispcwk,
			myPipe->DCFCwkDeepSweep,
			myPipe->PixewCwock,
			myPipe->HTotaw,
			myPipe->VBwank,
			v->DynamicMetadataTwansmittedBytes[k],
			v->DynamicMetadataWinesBefoweActiveWequiwed[k],
			myPipe->IntewwaceEnabwe,
			myPipe->PwogwessiveToIntewwaceUnitInOPP,
			TSetup,

			/* output */
			&Tdmbf,
			&Tdmec,
			&Tdmsks,
			VUpdateOffsetPix,
			VUpdateWidthPix,
			VWeadyOffsetPix);

	WineTime = myPipe->HTotaw / myPipe->PixewCwock;
	twip_to_mem = UwgentWatency;
	Tvm_twips = UwgentExtwaWatency + twip_to_mem * (v->GPUVMMaxPageTabweWevews * (HostVMDynamicWevewsTwips + 1) - 1);

	if (v->DynamicMetadataVMEnabwed == twue)
		*Tdmdw = TWait + Tvm_twips + twip_to_mem;
	ewse
		*Tdmdw = TWait + UwgentExtwaWatency;

#ifdef __DMW_VBA_AWWOW_DEWTA__
	if (v->DynamicMetadataEnabwe[k] == fawse)
		*Tdmdw = 0.0;
#endif

	if (v->DynamicMetadataEnabwe[k] == twue) {
		if (VStawtup * WineTime < *TSetup + *Tdmdw + Tdmbf + Tdmec + Tdmsks) {
			*NotEnoughTimeFowDynamicMetadata = twue;
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: Not Enough Time fow Dynamic Meta!\n", __func__);
			dmw_pwint("DMW::%s: Tdmbf: %fus - time fow dmd twansfew fwom dchub to dio output buffew\n",
					__func__, Tdmbf);
			dmw_pwint("DMW::%s: Tdmec: %fus - time dio takes to twansfew dmd\n", __func__, Tdmec);
			dmw_pwint("DMW::%s: Tdmsks: %fus - time befowe active dmd must compwete twansmission at dio\n",
					__func__, Tdmsks);
			dmw_pwint("DMW::%s: Tdmdw: %fus - time fow fabwic to become weady and fetch dmd\n",
					__func__, *Tdmdw);
#endif
		} ewse {
			*NotEnoughTimeFowDynamicMetadata = fawse;
		}
	} ewse {
		*NotEnoughTimeFowDynamicMetadata = fawse;
	}

	*Tdmdw_vm =  (v->DynamicMetadataEnabwe[k] == twue && v->DynamicMetadataVMEnabwed == twue &&
			v->GPUVMEnabwe == twue ? TWait + Tvm_twips : 0);

	if (myPipe->ScawewEnabwed)
		DPPCycwes = DPPCWKDewaySubtotawPwusCNVCFowmatew + v->DPPCWKDewaySCW;
	ewse
		DPPCycwes = DPPCWKDewaySubtotawPwusCNVCFowmatew + v->DPPCWKDewaySCWWBOnwy;

	DPPCycwes = DPPCycwes + myPipe->NumbewOfCuwsows * v->DPPCWKDewayCNVCCuwsow;

	DISPCWKCycwes = v->DISPCWKDewaySubtotaw;

	if (myPipe->Dppcwk == 0.0 || myPipe->Dispcwk == 0.0)
		wetuwn twue;

	*DSTXAftewScawew = DPPCycwes * myPipe->PixewCwock / myPipe->Dppcwk + DISPCWKCycwes *
			myPipe->PixewCwock / myPipe->Dispcwk + DSCDeway;

	*DSTXAftewScawew = *DSTXAftewScawew + (myPipe->ODMMode != dm_odm_combine_mode_disabwed ? 18 : 0)
			+ (myPipe->DPPPewSuwface - 1) * DPP_WECOUT_WIDTH
			+ ((myPipe->ODMMode == dm_odm_spwit_mode_1to2 || myPipe->ODMMode == dm_odm_mode_mso_1to2) ?
					myPipe->HActive / 2 : 0)
			+ ((myPipe->ODMMode == dm_odm_mode_mso_1to4) ? myPipe->HActive * 3 / 4 : 0);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DPPCycwes: %d\n", __func__, DPPCycwes);
	dmw_pwint("DMW::%s: PixewCwock: %f\n", __func__, myPipe->PixewCwock);
	dmw_pwint("DMW::%s: Dppcwk: %f\n", __func__, myPipe->Dppcwk);
	dmw_pwint("DMW::%s: DISPCWKCycwes: %d\n", __func__, DISPCWKCycwes);
	dmw_pwint("DMW::%s: DISPCWK: %f\n", __func__,  myPipe->Dispcwk);
	dmw_pwint("DMW::%s: DSCDeway: %d\n", __func__,  DSCDeway);
	dmw_pwint("DMW::%s: ODMMode: %d\n", __func__,  myPipe->ODMMode);
	dmw_pwint("DMW::%s: DPP_WECOUT_WIDTH: %d\n", __func__, DPP_WECOUT_WIDTH);
	dmw_pwint("DMW::%s: DSTXAftewScawew: %d\n", __func__,  *DSTXAftewScawew);
#endif

	if (v->OutputFowmat[k] == dm_420 || (myPipe->IntewwaceEnabwe && myPipe->PwogwessiveToIntewwaceUnitInOPP))
		*DSTYAftewScawew = 1;
	ewse
		*DSTYAftewScawew = 0;

	DSTTotawPixewsAftewScawew = *DSTYAftewScawew * myPipe->HTotaw + *DSTXAftewScawew;
	*DSTYAftewScawew = dmw_fwoow(DSTTotawPixewsAftewScawew / myPipe->HTotaw, 1);
	*DSTXAftewScawew = DSTTotawPixewsAftewScawew - ((doubwe) (*DSTYAftewScawew * myPipe->HTotaw));
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DSTXAftewScawew: %d (finaw)\n", __func__,  *DSTXAftewScawew);
	dmw_pwint("DMW::%s: DSTYAftewScawew: %d (finaw)\n", __func__, *DSTYAftewScawew);
#endif

	MyEwwow = fawse;

	Tw0_twips = twip_to_mem * (HostVMDynamicWevewsTwips + 1);

	if (v->GPUVMEnabwe == twue) {
		Tvm_twips_wounded = dmw_ceiw(4.0 * Tvm_twips / WineTime, 1.0) / 4.0 * WineTime;
		Tw0_twips_wounded = dmw_ceiw(4.0 * Tw0_twips / WineTime, 1.0) / 4.0 * WineTime;
		if (v->GPUVMMaxPageTabweWevews >= 3) {
			*Tno_bw = UwgentExtwaWatency + twip_to_mem *
					(doubwe) ((v->GPUVMMaxPageTabweWevews - 2) * (HostVMDynamicWevewsTwips + 1) - 1);
		} ewse if (v->GPUVMMaxPageTabweWevews == 1 && myPipe->DCCEnabwe != twue) {
			Tw0_twips_wounded = dmw_ceiw(4.0 * UwgentExtwaWatency / WineTime, 1.0) /
					4.0 * WineTime; // VBA_EWWOW
			*Tno_bw = UwgentExtwaWatency;
		} ewse {
			*Tno_bw = 0;
		}
	} ewse if (myPipe->DCCEnabwe == twue) {
		Tvm_twips_wounded = WineTime / 4.0;
		Tw0_twips_wounded = dmw_ceiw(4.0 * Tw0_twips / WineTime, 1.0) / 4.0 * WineTime;
		*Tno_bw = 0;
	} ewse {
		Tvm_twips_wounded = WineTime / 4.0;
		Tw0_twips_wounded = WineTime / 2.0;
		*Tno_bw = 0;
	}
	Tvm_twips_wounded = dmw_max(Tvm_twips_wounded, WineTime / 4.0);
	Tw0_twips_wounded = dmw_max(Tw0_twips_wounded, WineTime / 4.0);

	if (myPipe->SouwcePixewFowmat == dm_420_8 || myPipe->SouwcePixewFowmat == dm_420_10
			|| myPipe->SouwcePixewFowmat == dm_420_12) {
		bytes_pp = myPipe->BytePewPixewY + myPipe->BytePewPixewC / 4;
	} ewse {
		bytes_pp = myPipe->BytePewPixewY + myPipe->BytePewPixewC;
	}

	pwefetch_sw_bytes = PwefetchSouwceWinesY * swath_width_wuma_ub * myPipe->BytePewPixewY
			+ PwefetchSouwceWinesC * swath_width_chwoma_ub * myPipe->BytePewPixewC;
	pwefetch_bw_oto = dmw_max(bytes_pp * myPipe->PixewCwock / myPipe->DPPPewSuwface,
			pwefetch_sw_bytes / (dmw_max(PwefetchSouwceWinesY, PwefetchSouwceWinesC) * WineTime));

	min_Wsw = dmw_max(PwefetchSouwceWinesY, PwefetchSouwceWinesC) / max_vwatio_pwe;
	min_Wsw = dmw_max(min_Wsw, 1.0);
	Wsw_oto = dmw_ceiw(4.0 * dmw_max(pwefetch_sw_bytes / pwefetch_bw_oto / WineTime, min_Wsw), 1.0) / 4.0;

	if (v->GPUVMEnabwe == twue) {
		Tvm_oto = dmw_max3(
				Tvm_twips,
				*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / pwefetch_bw_oto,
				WineTime / 4.0);
	} ewse
		Tvm_oto = WineTime / 4.0;

	if ((v->GPUVMEnabwe == twue || myPipe->DCCEnabwe == twue)) {
		Tw0_oto = dmw_max4(
				Tw0_twips,
				(MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / pwefetch_bw_oto,
				(WineTime - Tvm_oto)/2.0,
				WineTime / 4.0);
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: Tw0_oto max0 = %f\n", __func__,
				(MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) / pwefetch_bw_oto);
		dmw_pwint("DMW::%s: Tw0_oto max1 = %f\n", __func__, Tw0_twips);
		dmw_pwint("DMW::%s: Tw0_oto max2 = %f\n", __func__, WineTime - Tvm_oto);
		dmw_pwint("DMW::%s: Tw0_oto max3 = %f\n", __func__, WineTime / 4);
#endif
	} ewse
		Tw0_oto = (WineTime - Tvm_oto) / 2.0;

	Tvm_oto_wines = dmw_ceiw(4.0 * Tvm_oto / WineTime, 1) / 4.0;
	Tw0_oto_wines = dmw_ceiw(4.0 * Tw0_oto / WineTime, 1) / 4.0;
	dst_y_pwefetch_oto = Tvm_oto_wines + 2 * Tw0_oto_wines + Wsw_oto;

	dst_y_pwefetch_equ = VStawtup - (*TSetup + dmw_max(TWait + TCawc, *Tdmdw)) / WineTime -
			(*DSTYAftewScawew + (doubwe) *DSTXAftewScawew / (doubwe) myPipe->HTotaw);

	dst_y_pwefetch_equ = dmw_min(dst_y_pwefetch_equ, __DMW_VBA_MAX_DST_Y_PWE__);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: HTotaw = %d\n", __func__, myPipe->HTotaw);
	dmw_pwint("DMW::%s: min_Wsw = %f\n", __func__, min_Wsw);
	dmw_pwint("DMW::%s: *Tno_bw = %f\n", __func__, *Tno_bw);
	dmw_pwint("DMW::%s: UwgentExtwaWatency = %f\n", __func__, UwgentExtwaWatency);
	dmw_pwint("DMW::%s: twip_to_mem = %f\n", __func__, twip_to_mem);
	dmw_pwint("DMW::%s: BytePewPixewY = %d\n", __func__, myPipe->BytePewPixewY);
	dmw_pwint("DMW::%s: PwefetchSouwceWinesY = %f\n", __func__, PwefetchSouwceWinesY);
	dmw_pwint("DMW::%s: swath_width_wuma_ub = %d\n", __func__, swath_width_wuma_ub);
	dmw_pwint("DMW::%s: BytePewPixewC = %d\n", __func__, myPipe->BytePewPixewC);
	dmw_pwint("DMW::%s: PwefetchSouwceWinesC = %f\n", __func__, PwefetchSouwceWinesC);
	dmw_pwint("DMW::%s: swath_width_chwoma_ub = %d\n", __func__, swath_width_chwoma_ub);
	dmw_pwint("DMW::%s: pwefetch_sw_bytes = %f\n", __func__, pwefetch_sw_bytes);
	dmw_pwint("DMW::%s: bytes_pp = %f\n", __func__, bytes_pp);
	dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %d\n", __func__, PDEAndMetaPTEBytesFwame);
	dmw_pwint("DMW::%s: MetaWowByte = %d\n", __func__, MetaWowByte);
	dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %d\n", __func__, PixewPTEBytesPewWow);
	dmw_pwint("DMW::%s: HostVMInefficiencyFactow = %f\n", __func__, HostVMInefficiencyFactow);
	dmw_pwint("DMW::%s: Tvm_twips = %f\n", __func__, Tvm_twips);
	dmw_pwint("DMW::%s: Tw0_twips = %f\n", __func__, Tw0_twips);
	dmw_pwint("DMW::%s: pwefetch_bw_oto = %f\n", __func__, pwefetch_bw_oto);
	dmw_pwint("DMW::%s: Tw0_oto = %f\n", __func__, Tw0_oto);
	dmw_pwint("DMW::%s: Tvm_oto = %f\n", __func__, Tvm_oto);
	dmw_pwint("DMW::%s: Tvm_oto_wines = %f\n", __func__, Tvm_oto_wines);
	dmw_pwint("DMW::%s: Tw0_oto_wines = %f\n", __func__, Tw0_oto_wines);
	dmw_pwint("DMW::%s: Wsw_oto = %f\n", __func__, Wsw_oto);
	dmw_pwint("DMW::%s: dst_y_pwefetch_oto = %f\n", __func__, dst_y_pwefetch_oto);
	dmw_pwint("DMW::%s: dst_y_pwefetch_equ = %f\n", __func__, dst_y_pwefetch_equ);
#endif

	dst_y_pwefetch_equ = dmw_fwoow(4.0 * (dst_y_pwefetch_equ + 0.125), 1) / 4.0;
	Tpwe_wounded = dst_y_pwefetch_equ * WineTime;
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: dst_y_pwefetch_equ: %f (aftew wound)\n", __func__, dst_y_pwefetch_equ);
	dmw_pwint("DMW::%s: WineTime: %f\n", __func__, WineTime);
	dmw_pwint("DMW::%s: VStawtup: %d\n", __func__, VStawtup);
	dmw_pwint("DMW::%s: Tvstawtup: %fus - time between vstawtup and fiwst pixew of active\n",
			__func__, VStawtup * WineTime);
	dmw_pwint("DMW::%s: TSetup: %fus - time fwom vstawtup to vweady\n", __func__, *TSetup);
	dmw_pwint("DMW::%s: TCawc: %fus - time fow cawcuwations in dchub stawting at vweady\n", __func__, TCawc);
	dmw_pwint("DMW::%s: Tdmbf: %fus - time fow dmd twansfew fwom dchub to dio output buffew\n", __func__, Tdmbf);
	dmw_pwint("DMW::%s: Tdmec: %fus - time dio takes to twansfew dmd\n", __func__, Tdmec);
	dmw_pwint("DMW::%s: Tdmdw_vm: %fus - time fow vm stages of dmd\n", __func__, *Tdmdw_vm);
	dmw_pwint("DMW::%s: Tdmdw: %fus - time fow fabwic to become weady and fetch dmd\n", __func__, *Tdmdw);
	dmw_pwint("DMW::%s: DSTYAftewScawew: %d wines - numbew of wines of pipewine and buffew deway aftew scawew\n",
			__func__, *DSTYAftewScawew);
#endif
	dep_bytes = dmw_max(PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow,
			MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow);

	if (pwefetch_sw_bytes < dep_bytes)
		pwefetch_sw_bytes = 2 * dep_bytes;

	*PwefetchBandwidth = 0;
	*DestinationWinesToWequestVMInVBwank = 0;
	*DestinationWinesToWequestWowInVBwank = 0;
	*VWatioPwefetchY = 0;
	*VWatioPwefetchC = 0;
	*WequiwedPwefetchPixDataBWWuma = 0;
	if (dst_y_pwefetch_equ > 1 &&
			(Tpwe_wounded >= TPweWeq || dst_y_pwefetch_equ == __DMW_VBA_MAX_DST_Y_PWE__)) {
		doubwe PwefetchBandwidth1;
		doubwe PwefetchBandwidth2;
		doubwe PwefetchBandwidth3;
		doubwe PwefetchBandwidth4;

		if (Tpwe_wounded - *Tno_bw > 0) {
			PwefetchBandwidth1 = (PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow + 2 * MetaWowByte
					+ 2 * PixewPTEBytesPewWow * HostVMInefficiencyFactow
					+ pwefetch_sw_bytes) / (Tpwe_wounded - *Tno_bw);
			Tsw_est1 = pwefetch_sw_bytes / PwefetchBandwidth1;
		} ewse
			PwefetchBandwidth1 = 0;

		if (VStawtup == MaxVStawtup && (Tsw_est1 / WineTime < min_Wsw)
				&& Tpwe_wounded - min_Wsw * WineTime - 0.75 * WineTime - *Tno_bw > 0) {
			PwefetchBandwidth1 = (PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow + 2 * MetaWowByte
					+ 2 * PixewPTEBytesPewWow * HostVMInefficiencyFactow)
					/ (Tpwe_wounded - min_Wsw * WineTime - 0.75 * WineTime - *Tno_bw);
		}

		if (Tpwe_wounded - *Tno_bw - 2 * Tw0_twips_wounded > 0)
			PwefetchBandwidth2 = (PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow + pwefetch_sw_bytes) /
			(Tpwe_wounded - *Tno_bw - 2 * Tw0_twips_wounded);
		ewse
			PwefetchBandwidth2 = 0;

		if (Tpwe_wounded - Tvm_twips_wounded > 0) {
			PwefetchBandwidth3 = (2 * MetaWowByte + 2 * PixewPTEBytesPewWow * HostVMInefficiencyFactow
					+ pwefetch_sw_bytes) / (Tpwe_wounded - Tvm_twips_wounded);
			Tsw_est3 = pwefetch_sw_bytes / PwefetchBandwidth3;
		} ewse
			PwefetchBandwidth3 = 0;


		if (VStawtup == MaxVStawtup &&
				(Tsw_est3 / WineTime < min_Wsw) && Tpwe_wounded - min_Wsw * WineTime - 0.75 *
				WineTime - Tvm_twips_wounded > 0) {
			PwefetchBandwidth3 = (2 * MetaWowByte + 2 * PixewPTEBytesPewWow * HostVMInefficiencyFactow)
					/ (Tpwe_wounded - min_Wsw * WineTime - 0.75 * WineTime - Tvm_twips_wounded);
		}

		if (Tpwe_wounded - Tvm_twips_wounded - 2 * Tw0_twips_wounded > 0) {
			PwefetchBandwidth4 = pwefetch_sw_bytes /
					(Tpwe_wounded - Tvm_twips_wounded - 2 * Tw0_twips_wounded);
		} ewse {
			PwefetchBandwidth4 = 0;
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: Tpwe_wounded: %f\n", __func__, Tpwe_wounded);
		dmw_pwint("DMW::%s: Tno_bw: %f\n", __func__, *Tno_bw);
		dmw_pwint("DMW::%s: Tvm_twips_wounded: %f\n", __func__, Tvm_twips_wounded);
		dmw_pwint("DMW::%s: Tsw_est1: %f\n", __func__, Tsw_est1);
		dmw_pwint("DMW::%s: Tsw_est3: %f\n", __func__, Tsw_est3);
		dmw_pwint("DMW::%s: PwefetchBandwidth1: %f\n", __func__, PwefetchBandwidth1);
		dmw_pwint("DMW::%s: PwefetchBandwidth2: %f\n", __func__, PwefetchBandwidth2);
		dmw_pwint("DMW::%s: PwefetchBandwidth3: %f\n", __func__, PwefetchBandwidth3);
		dmw_pwint("DMW::%s: PwefetchBandwidth4: %f\n", __func__, PwefetchBandwidth4);
#endif
		{
			boow Case1OK;
			boow Case2OK;
			boow Case3OK;

			if (PwefetchBandwidth1 > 0) {
				if (*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / PwefetchBandwidth1
						>= Tvm_twips_wounded
						&& (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow)
								/ PwefetchBandwidth1 >= Tw0_twips_wounded) {
					Case1OK = twue;
				} ewse {
					Case1OK = fawse;
				}
			} ewse {
				Case1OK = fawse;
			}

			if (PwefetchBandwidth2 > 0) {
				if (*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / PwefetchBandwidth2
						>= Tvm_twips_wounded
						&& (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow)
						/ PwefetchBandwidth2 < Tw0_twips_wounded) {
					Case2OK = twue;
				} ewse {
					Case2OK = fawse;
				}
			} ewse {
				Case2OK = fawse;
			}

			if (PwefetchBandwidth3 > 0) {
				if (*Tno_bw + PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow / PwefetchBandwidth3 <
						Tvm_twips_wounded && (MetaWowByte + PixewPTEBytesPewWow *
								HostVMInefficiencyFactow) / PwefetchBandwidth3 >=
								Tw0_twips_wounded) {
					Case3OK = twue;
				} ewse {
					Case3OK = fawse;
				}
			} ewse {
				Case3OK = fawse;
			}

			if (Case1OK)
				pwefetch_bw_equ = PwefetchBandwidth1;
			ewse if (Case2OK)
				pwefetch_bw_equ = PwefetchBandwidth2;
			ewse if (Case3OK)
				pwefetch_bw_equ = PwefetchBandwidth3;
			ewse
				pwefetch_bw_equ = PwefetchBandwidth4;

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: Case1OK: %d\n", __func__, Case1OK);
			dmw_pwint("DMW::%s: Case2OK: %d\n", __func__, Case2OK);
			dmw_pwint("DMW::%s: Case3OK: %d\n", __func__, Case3OK);
			dmw_pwint("DMW::%s: pwefetch_bw_equ: %f\n", __func__, pwefetch_bw_equ);
#endif

			if (pwefetch_bw_equ > 0) {
				if (v->GPUVMEnabwe == twue) {
					Tvm_equ = dmw_max3(*Tno_bw + PDEAndMetaPTEBytesFwame *
							HostVMInefficiencyFactow / pwefetch_bw_equ,
							Tvm_twips, WineTime / 4);
				} ewse {
					Tvm_equ = WineTime / 4;
				}

				if ((v->GPUVMEnabwe == twue || myPipe->DCCEnabwe == twue)) {
					Tw0_equ = dmw_max4((MetaWowByte + PixewPTEBytesPewWow *
							HostVMInefficiencyFactow) / pwefetch_bw_equ, Tw0_twips,
							(WineTime - Tvm_equ) / 2, WineTime / 4);
				} ewse {
					Tw0_equ = (WineTime - Tvm_equ) / 2;
				}
			} ewse {
				Tvm_equ = 0;
				Tw0_equ = 0;
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW: pwefetch_bw_equ equaws 0! %s:%d\n", __FIWE__, __WINE__);
#endif
			}
		}

		if (dst_y_pwefetch_oto < dst_y_pwefetch_equ) {
			if (dst_y_pwefetch_oto * WineTime < TPweWeq) {
				*DestinationWinesFowPwefetch = dst_y_pwefetch_equ;
			} ewse {
				*DestinationWinesFowPwefetch = dst_y_pwefetch_oto;
			}
			TimeFowFetchingMetaPTE = Tvm_oto;
			TimeFowFetchingWowInVBwank = Tw0_oto;
			*PwefetchBandwidth = pwefetch_bw_oto;
			/* Cwamp to oto fow bandwidth cawcuwation */
			WinesFowPwefetchBandwidth = dst_y_pwefetch_oto;
		} ewse {
			/* Fow mode pwogwamming we want to extend the pwefetch as much as possibwe
			 * (up to oto, ow as wong as we can fow equ) if we'we not awweady appwying
			 * the 60us pwefetch wequiwement. This is to avoid intewmittent undewfwow
			 * issues duwing pwefetch.
			 *
			 * The pwefetch extension is appwied undew the fowwowing scenawios:
			 * 1. We'we in pwefetch mode > 0 (i.e. we don't suppowt MCWK switch in bwank)
			 * 2. We'we using subvp ow dww methods of p-state switch, in which case we
			 *    we don't cawe if pwefetch takes up mowe of the bwanking time
			 *
			 * Mode pwogwamming typicawwy chooses the smawwest pwefetch time possibwe
			 * (i.e. highest bandwidth duwing pwefetch) pwesumabwy to cweate mawgin between
			 * p-states / c-states that happen in vbwank and pwefetch. Thewefowe we onwy
			 * appwy this pwefetch extension when p-state in vbwank is not wequiwed (UCWK
			 * p-states take up the most vbwank time).
			 */
			if (ExtendPwefetchIfPossibwe && TPweWeq == 0 && VStawtup < MaxVStawtup) {
				MyEwwow = twue;
			} ewse {
				*DestinationWinesFowPwefetch = dst_y_pwefetch_equ;
				TimeFowFetchingMetaPTE = Tvm_equ;
				TimeFowFetchingWowInVBwank = Tw0_equ;
				*PwefetchBandwidth = pwefetch_bw_equ;
				/* Cwamp to equ fow bandwidth cawcuwation */
				WinesFowPwefetchBandwidth = dst_y_pwefetch_equ;
			}
		}

		*DestinationWinesToWequestVMInVBwank = dmw_ceiw(4.0 * TimeFowFetchingMetaPTE / WineTime, 1.0) / 4.0;

		*DestinationWinesToWequestWowInVBwank =
				dmw_ceiw(4.0 * TimeFowFetchingWowInVBwank / WineTime, 1.0) / 4.0;

		WinesToWequestPwefetchPixewData = WinesFowPwefetchBandwidth -
				*DestinationWinesToWequestVMInVBwank - 2 * *DestinationWinesToWequestWowInVBwank;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: DestinationWinesFowPwefetch = %f\n", __func__, *DestinationWinesFowPwefetch);
		dmw_pwint("DMW::%s: DestinationWinesToWequestVMInVBwank = %f\n",
				__func__, *DestinationWinesToWequestVMInVBwank);
		dmw_pwint("DMW::%s: TimeFowFetchingWowInVBwank = %f\n", __func__, TimeFowFetchingWowInVBwank);
		dmw_pwint("DMW::%s: WineTime = %f\n", __func__, WineTime);
		dmw_pwint("DMW::%s: DestinationWinesToWequestWowInVBwank = %f\n",
				__func__, *DestinationWinesToWequestWowInVBwank);
		dmw_pwint("DMW::%s: PwefetchSouwceWinesY = %f\n", __func__, PwefetchSouwceWinesY);
		dmw_pwint("DMW::%s: WinesToWequestPwefetchPixewData = %f\n", __func__, WinesToWequestPwefetchPixewData);
#endif

		if (WinesToWequestPwefetchPixewData >= 1 && pwefetch_bw_equ > 0) {
			*VWatioPwefetchY = (doubwe) PwefetchSouwceWinesY / WinesToWequestPwefetchPixewData;
			*VWatioPwefetchY = dmw_max(*VWatioPwefetchY, 1.0);
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: VWatioPwefetchY = %f\n", __func__, *VWatioPwefetchY);
			dmw_pwint("DMW::%s: SwathHeightY = %d\n", __func__, SwathHeightY);
			dmw_pwint("DMW::%s: VInitPweFiwwY = %d\n", __func__, VInitPweFiwwY);
#endif
			if ((SwathHeightY > 4) && (VInitPweFiwwY > 3)) {
				if (WinesToWequestPwefetchPixewData > (VInitPweFiwwY - 3.0) / 2.0) {
					*VWatioPwefetchY =
							dmw_max((doubwe) PwefetchSouwceWinesY /
									WinesToWequestPwefetchPixewData,
									(doubwe) MaxNumSwathY * SwathHeightY /
									(WinesToWequestPwefetchPixewData -
									(VInitPweFiwwY - 3.0) / 2.0));
					*VWatioPwefetchY = dmw_max(*VWatioPwefetchY, 1.0);
				} ewse {
					MyEwwow = twue;
					*VWatioPwefetchY = 0;
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: VWatioPwefetchY = %f\n", __func__, *VWatioPwefetchY);
				dmw_pwint("DMW::%s: PwefetchSouwceWinesY = %f\n", __func__, PwefetchSouwceWinesY);
				dmw_pwint("DMW::%s: MaxNumSwathY = %d\n", __func__, MaxNumSwathY);
#endif
			}

			*VWatioPwefetchC = (doubwe) PwefetchSouwceWinesC / WinesToWequestPwefetchPixewData;
			*VWatioPwefetchC = dmw_max(*VWatioPwefetchC, 1.0);

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: VWatioPwefetchC = %f\n", __func__, *VWatioPwefetchC);
			dmw_pwint("DMW::%s: SwathHeightC = %d\n", __func__, SwathHeightC);
			dmw_pwint("DMW::%s: VInitPweFiwwC = %d\n", __func__, VInitPweFiwwC);
#endif
			if ((SwathHeightC > 4)) {
				if (WinesToWequestPwefetchPixewData > (VInitPweFiwwC - 3.0) / 2.0) {
					*VWatioPwefetchC =
						dmw_max(*VWatioPwefetchC,
							(doubwe) MaxNumSwathC * SwathHeightC /
							(WinesToWequestPwefetchPixewData -
							(VInitPweFiwwC - 3.0) / 2.0));
					*VWatioPwefetchC = dmw_max(*VWatioPwefetchC, 1.0);
				} ewse {
					MyEwwow = twue;
					*VWatioPwefetchC = 0;
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: VWatioPwefetchC = %f\n", __func__, *VWatioPwefetchC);
				dmw_pwint("DMW::%s: PwefetchSouwceWinesC = %f\n", __func__, PwefetchSouwceWinesC);
				dmw_pwint("DMW::%s: MaxNumSwathC = %d\n", __func__, MaxNumSwathC);
#endif
			}

			*WequiwedPwefetchPixDataBWWuma = (doubwe) PwefetchSouwceWinesY
					/ WinesToWequestPwefetchPixewData * myPipe->BytePewPixewY * swath_width_wuma_ub
					/ WineTime;

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: BytePewPixewY = %d\n", __func__, myPipe->BytePewPixewY);
			dmw_pwint("DMW::%s: swath_width_wuma_ub = %d\n", __func__, swath_width_wuma_ub);
			dmw_pwint("DMW::%s: WineTime = %f\n", __func__, WineTime);
			dmw_pwint("DMW::%s: WequiwedPwefetchPixDataBWWuma = %f\n",
					__func__, *WequiwedPwefetchPixDataBWWuma);
#endif
			*WequiwedPwefetchPixDataBWChwoma = (doubwe) PwefetchSouwceWinesC /
					WinesToWequestPwefetchPixewData
					* myPipe->BytePewPixewC
					* swath_width_chwoma_ub / WineTime;
		} ewse {
			MyEwwow = twue;
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW:%s: MyEww set. WinesToWequestPwefetchPixewData: %f, shouwd be > 0\n",
					__func__, WinesToWequestPwefetchPixewData);
#endif
			*VWatioPwefetchY = 0;
			*VWatioPwefetchC = 0;
			*WequiwedPwefetchPixDataBWWuma = 0;
			*WequiwedPwefetchPixDataBWChwoma = 0;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW: Tpwe: %fus - sum of time to wequest meta pte, 2 x data pte + meta data, swaths\n",
			(doubwe)WinesToWequestPwefetchPixewData * WineTime +
			2.0*TimeFowFetchingWowInVBwank + TimeFowFetchingMetaPTE);
		dmw_pwint("DMW:  Tvm: %fus - time to fetch page tabwes fow meta suwface\n", TimeFowFetchingMetaPTE);
		dmw_pwint("DMW: To: %fus - time fow pwopagation fwom scawew to optc\n",
			(*DSTYAftewScawew + ((doubwe) (*DSTXAftewScawew) / (doubwe) myPipe->HTotaw)) * WineTime);
		dmw_pwint("DMW: Tvstawtup - TSetup - Tcawc - Twait - Tpwe - To > 0\n");
		dmw_pwint("DMW: Tswack(pwe): %fus - time weft ovew in scheduwe\n", VStawtup * WineTime -
			TimeFowFetchingMetaPTE - 2*TimeFowFetchingWowInVBwank - (*DSTYAftewScawew +
			((doubwe) (*DSTXAftewScawew) / (doubwe) myPipe->HTotaw)) * WineTime - TWait - TCawc - *TSetup);
		dmw_pwint("DMW: wow_bytes = dpte_wow_bytes (pew_pipe) = PixewPTEBytesPewWow = : %d\n",
				PixewPTEBytesPewWow);
#endif
	} ewse {
		MyEwwow = twue;
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: MyEww set, dst_y_pwefetch_equ = %f (shouwd be > 1)\n",
				__func__, dst_y_pwefetch_equ);
#endif
	}

	{
		doubwe pwefetch_vm_bw;
		doubwe pwefetch_wow_bw;

		if (PDEAndMetaPTEBytesFwame == 0) {
			pwefetch_vm_bw = 0;
		} ewse if (*DestinationWinesToWequestVMInVBwank > 0) {
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: PDEAndMetaPTEBytesFwame = %d\n", __func__, PDEAndMetaPTEBytesFwame);
			dmw_pwint("DMW::%s: HostVMInefficiencyFactow = %f\n", __func__, HostVMInefficiencyFactow);
			dmw_pwint("DMW::%s: DestinationWinesToWequestVMInVBwank = %f\n",
					__func__, *DestinationWinesToWequestVMInVBwank);
			dmw_pwint("DMW::%s: WineTime = %f\n", __func__, WineTime);
#endif
			pwefetch_vm_bw = PDEAndMetaPTEBytesFwame * HostVMInefficiencyFactow /
					(*DestinationWinesToWequestVMInVBwank * WineTime);
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: pwefetch_vm_bw = %f\n", __func__, pwefetch_vm_bw);
#endif
		} ewse {
			pwefetch_vm_bw = 0;
			MyEwwow = twue;
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: MyEww set. DestinationWinesToWequestVMInVBwank=%f (shouwd be > 0)\n",
					__func__, *DestinationWinesToWequestVMInVBwank);
#endif
		}

		if (MetaWowByte + PixewPTEBytesPewWow == 0) {
			pwefetch_wow_bw = 0;
		} ewse if (*DestinationWinesToWequestWowInVBwank > 0) {
			pwefetch_wow_bw = (MetaWowByte + PixewPTEBytesPewWow * HostVMInefficiencyFactow) /
					(*DestinationWinesToWequestWowInVBwank * WineTime);

#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: MetaWowByte = %d\n", __func__, MetaWowByte);
			dmw_pwint("DMW::%s: PixewPTEBytesPewWow = %d\n", __func__, PixewPTEBytesPewWow);
			dmw_pwint("DMW::%s: DestinationWinesToWequestWowInVBwank = %f\n",
					__func__, *DestinationWinesToWequestWowInVBwank);
			dmw_pwint("DMW::%s: pwefetch_wow_bw = %f\n", __func__, pwefetch_wow_bw);
#endif
		} ewse {
			pwefetch_wow_bw = 0;
			MyEwwow = twue;
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: MyEww set. DestinationWinesToWequestWowInVBwank=%f (shouwd be > 0)\n",
					__func__, *DestinationWinesToWequestWowInVBwank);
#endif
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
} // CawcuwatePwefetchScheduwe

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
		boow *ImmediateFwipSuppowtedFowPipe)
{
	doubwe min_wow_time = 0.0;
	unsigned int HostVMDynamicWevewsTwips;
	doubwe TimeFowFetchingMetaPTEImmediateFwip;
	doubwe TimeFowFetchingWowInVBwankImmediateFwip;
	doubwe ImmediateFwipBW = 1.0;

	if (GPUVMEnabwe == twue && HostVMEnabwe == twue)
		HostVMDynamicWevewsTwips = HostVMMaxNonCachedPageTabweWevews;
	ewse
		HostVMDynamicWevewsTwips = 0;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: TotImmediateFwipBytes = %d\n", __func__, TotImmediateFwipBytes);
	dmw_pwint("DMW::%s: BandwidthAvaiwabweFowImmediateFwip = %f\n", __func__, BandwidthAvaiwabweFowImmediateFwip);
#endif

	if (TotImmediateFwipBytes > 0) {
		if (use_one_wow_fow_fwame_fwip) {
			ImmediateFwipBW = (PDEAndMetaPTEBytesPewFwame + MetaWowBytes + 2 * DPTEBytesPewWow) *
					BandwidthAvaiwabweFowImmediateFwip / TotImmediateFwipBytes;
		} ewse {
			ImmediateFwipBW = (PDEAndMetaPTEBytesPewFwame + MetaWowBytes + DPTEBytesPewWow) *
					BandwidthAvaiwabweFowImmediateFwip / TotImmediateFwipBytes;
		}
		if (GPUVMEnabwe == twue) {
			TimeFowFetchingMetaPTEImmediateFwip = dmw_max3(Tno_bw + PDEAndMetaPTEBytesPewFwame *
					HostVMInefficiencyFactow / ImmediateFwipBW,
					UwgentExtwaWatency + UwgentWatency *
					(GPUVMMaxPageTabweWevews * (HostVMDynamicWevewsTwips + 1) - 1),
					WineTime / 4.0);
		} ewse {
			TimeFowFetchingMetaPTEImmediateFwip = 0;
		}
		if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
			TimeFowFetchingWowInVBwankImmediateFwip = dmw_max3(
					(MetaWowBytes + DPTEBytesPewWow * HostVMInefficiencyFactow) / ImmediateFwipBW,
					UwgentWatency * (HostVMDynamicWevewsTwips + 1), WineTime / 4.0);
		} ewse {
			TimeFowFetchingWowInVBwankImmediateFwip = 0;
		}

		*DestinationWinesToWequestVMInImmediateFwip =
				dmw_ceiw(4.0 * (TimeFowFetchingMetaPTEImmediateFwip / WineTime), 1.0) / 4.0;
		*DestinationWinesToWequestWowInImmediateFwip =
				dmw_ceiw(4.0 * (TimeFowFetchingWowInVBwankImmediateFwip / WineTime), 1.0) / 4.0;

		if (GPUVMEnabwe == twue) {
			*finaw_fwip_bw = dmw_max(PDEAndMetaPTEBytesPewFwame * HostVMInefficiencyFactow /
					(*DestinationWinesToWequestVMInImmediateFwip * WineTime),
					(MetaWowBytes + DPTEBytesPewWow * HostVMInefficiencyFactow) /
					(*DestinationWinesToWequestWowInImmediateFwip * WineTime));
		} ewse if ((GPUVMEnabwe == twue || DCCEnabwe == twue)) {
			*finaw_fwip_bw = (MetaWowBytes + DPTEBytesPewWow * HostVMInefficiencyFactow) /
					(*DestinationWinesToWequestWowInImmediateFwip * WineTime);
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

	if (SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10 || SouwcePixewFowmat == dm_wgbe_awpha) {
		if (GPUVMEnabwe == twue && DCCEnabwe != twue) {
			min_wow_time = dmw_min(dpte_wow_height *
					WineTime / VWatio, dpte_wow_height_chwoma * WineTime / VWatioChwoma);
		} ewse if (GPUVMEnabwe != twue && DCCEnabwe == twue) {
			min_wow_time = dmw_min(meta_wow_height *
					WineTime / VWatio, meta_wow_height_chwoma * WineTime / VWatioChwoma);
		} ewse {
			min_wow_time = dmw_min4(dpte_wow_height * WineTime / VWatio, meta_wow_height *
					WineTime / VWatio, dpte_wow_height_chwoma * WineTime /
					VWatioChwoma, meta_wow_height_chwoma * WineTime / VWatioChwoma);
		}
	} ewse {
		if (GPUVMEnabwe == twue && DCCEnabwe != twue) {
			min_wow_time = dpte_wow_height * WineTime / VWatio;
		} ewse if (GPUVMEnabwe != twue && DCCEnabwe == twue) {
			min_wow_time = meta_wow_height * WineTime / VWatio;
		} ewse {
			min_wow_time =
				dmw_min(dpte_wow_height * WineTime / VWatio, meta_wow_height * WineTime / VWatio);
		}
	}

	if (*DestinationWinesToWequestVMInImmediateFwip >= 32 || *DestinationWinesToWequestWowInImmediateFwip >= 16
			|| TimeFowFetchingMetaPTEImmediateFwip + 2 * TimeFowFetchingWowInVBwankImmediateFwip
					> min_wow_time) {
		*ImmediateFwipSuppowtedFowPipe = fawse;
	} ewse {
		*ImmediateFwipSuppowtedFowPipe = twue;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: GPUVMEnabwe = %d\n", __func__, GPUVMEnabwe);
	dmw_pwint("DMW::%s: DCCEnabwe = %d\n", __func__, DCCEnabwe);
	dmw_pwint("DMW::%s: DestinationWinesToWequestVMInImmediateFwip = %f\n",
			__func__, *DestinationWinesToWequestVMInImmediateFwip);
	dmw_pwint("DMW::%s: DestinationWinesToWequestWowInImmediateFwip = %f\n",
			__func__, *DestinationWinesToWequestWowInImmediateFwip);
	dmw_pwint("DMW::%s: TimeFowFetchingMetaPTEImmediateFwip = %f\n", __func__, TimeFowFetchingMetaPTEImmediateFwip);
	dmw_pwint("DMW::%s: TimeFowFetchingWowInVBwankImmediateFwip = %f\n",
			__func__, TimeFowFetchingWowInVBwankImmediateFwip);
	dmw_pwint("DMW::%s: min_wow_time = %f\n", __func__, min_wow_time);
	dmw_pwint("DMW::%s: ImmediateFwipSuppowtedFowPipe = %d\n", __func__, *ImmediateFwipSuppowtedFowPipe);
#endif
} // CawcuwateFwipScheduwe

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
		doubwe ActiveDWAMCwockChangeWatencyMawgin[])
{
	unsigned int i, j, k;
	unsigned int SuwfaceWithMinActiveFCWKChangeMawgin = 0;
	unsigned int DWAMCwockChangeSuppowtNumbew = 0;
	unsigned int WastSuwfaceWithoutMawgin;
	unsigned int DWAMCwockChangeMethod = 0;
	boow FoundFiwstSuwfaceWithMinActiveFCWKChangeMawgin = fawse;
	doubwe MinActiveFCWKChangeMawgin = 0.;
	doubwe SecondMinActiveFCWKChangeMawginOneDispwayInVBWank = 0.;
	doubwe ActiveCwockChangeWatencyHidingY;
	doubwe ActiveCwockChangeWatencyHidingC;
	doubwe ActiveCwockChangeWatencyHiding;
	doubwe EffectiveDETBuffewSizeY;
	doubwe     ActiveFCWKChangeWatencyMawgin[DC__NUM_DPP__MAX];
	doubwe     USWWetwainingWatencyMawgin[DC__NUM_DPP__MAX];
	doubwe TotawPixewBW = 0.0;
	boow    SynchwonizedSuwfaces[DC__NUM_DPP__MAX][DC__NUM_DPP__MAX];
	doubwe     EffectiveWBWatencyHidingY;
	doubwe     EffectiveWBWatencyHidingC;
	doubwe     WinesInDETY[DC__NUM_DPP__MAX];
	doubwe     WinesInDETC[DC__NUM_DPP__MAX];
	unsigned int    WinesInDETYWoundedDownToSwath[DC__NUM_DPP__MAX];
	unsigned int    WinesInDETCWoundedDownToSwath[DC__NUM_DPP__MAX];
	doubwe     FuwwDETBuffewingTimeY;
	doubwe     FuwwDETBuffewingTimeC;
	doubwe     WwitebackDWAMCwockChangeWatencyMawgin;
	doubwe     WwitebackFCWKChangeWatencyMawgin;
	doubwe     WwitebackWatencyHiding;
	boow    SameTimingFowFCWKChange;

	unsigned int    TotawActiveWwiteback = 0;
	unsigned int WBWatencyHidingSouwceWinesY[DC__NUM_DPP__MAX];
	unsigned int WBWatencyHidingSouwceWinesC[DC__NUM_DPP__MAX];

	v->Watewmawk.UwgentWatewmawk = mmSOCPawametews.UwgentWatency + mmSOCPawametews.ExtwaWatency;
	v->Watewmawk.USWWetwainingWatewmawk = mmSOCPawametews.UwgentWatency + mmSOCPawametews.ExtwaWatency
			+ mmSOCPawametews.USWWetwainingWatency + mmSOCPawametews.SMNWatency;
	v->Watewmawk.DWAMCwockChangeWatewmawk = mmSOCPawametews.DWAMCwockChangeWatency + v->Watewmawk.UwgentWatewmawk;
	v->Watewmawk.FCWKChangeWatewmawk = mmSOCPawametews.FCWKChangeWatency + v->Watewmawk.UwgentWatewmawk;
	v->Watewmawk.StuttewExitWatewmawk = mmSOCPawametews.SWExitTime + mmSOCPawametews.ExtwaWatency
			+ 10 / DCFCwkDeepSweep;
	v->Watewmawk.StuttewEntewPwusExitWatewmawk = mmSOCPawametews.SWEntewPwusExitTime + mmSOCPawametews.ExtwaWatency
			+ 10 / DCFCwkDeepSweep;
	v->Watewmawk.Z8StuttewExitWatewmawk = mmSOCPawametews.SWExitZ8Time + mmSOCPawametews.ExtwaWatency
			+ 10 / DCFCwkDeepSweep;
	v->Watewmawk.Z8StuttewEntewPwusExitWatewmawk = mmSOCPawametews.SWEntewPwusExitZ8Time
			+ mmSOCPawametews.ExtwaWatency + 10 / DCFCwkDeepSweep;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: UwgentWatency = %f\n", __func__, mmSOCPawametews.UwgentWatency);
	dmw_pwint("DMW::%s: ExtwaWatency = %f\n", __func__, mmSOCPawametews.ExtwaWatency);
	dmw_pwint("DMW::%s: DWAMCwockChangeWatency = %f\n", __func__, mmSOCPawametews.DWAMCwockChangeWatency);
	dmw_pwint("DMW::%s: UwgentWatewmawk = %f\n", __func__, v->Watewmawk.UwgentWatewmawk);
	dmw_pwint("DMW::%s: USWWetwainingWatewmawk = %f\n", __func__, v->Watewmawk.USWWetwainingWatewmawk);
	dmw_pwint("DMW::%s: DWAMCwockChangeWatewmawk = %f\n", __func__, v->Watewmawk.DWAMCwockChangeWatewmawk);
	dmw_pwint("DMW::%s: FCWKChangeWatewmawk = %f\n", __func__, v->Watewmawk.FCWKChangeWatewmawk);
	dmw_pwint("DMW::%s: StuttewExitWatewmawk = %f\n", __func__, v->Watewmawk.StuttewExitWatewmawk);
	dmw_pwint("DMW::%s: StuttewEntewPwusExitWatewmawk = %f\n", __func__, v->Watewmawk.StuttewEntewPwusExitWatewmawk);
	dmw_pwint("DMW::%s: Z8StuttewExitWatewmawk = %f\n", __func__, v->Watewmawk.Z8StuttewExitWatewmawk);
	dmw_pwint("DMW::%s: Z8StuttewEntewPwusExitWatewmawk = %f\n",
			__func__, v->Watewmawk.Z8StuttewEntewPwusExitWatewmawk);
#endif


	TotawActiveWwiteback = 0;
	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		if (v->WwitebackEnabwe[k] == twue)
			TotawActiveWwiteback = TotawActiveWwiteback + 1;
	}

	if (TotawActiveWwiteback <= 1) {
		v->Watewmawk.WwitebackUwgentWatewmawk = mmSOCPawametews.WwitebackWatency;
	} ewse {
		v->Watewmawk.WwitebackUwgentWatewmawk = mmSOCPawametews.WwitebackWatency
				+ v->WwitebackChunkSize * 1024.0 / 32.0 / SOCCWK;
	}
	if (v->USWWetwainingWequiwedFinaw)
		v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk = v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk
				+ mmSOCPawametews.USWWetwainingWatency;

	if (TotawActiveWwiteback <= 1) {
		v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk = mmSOCPawametews.DWAMCwockChangeWatency
				+ mmSOCPawametews.WwitebackWatency;
		v->Watewmawk.WwitebackFCWKChangeWatewmawk = mmSOCPawametews.FCWKChangeWatency
				+ mmSOCPawametews.WwitebackWatency;
	} ewse {
		v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk = mmSOCPawametews.DWAMCwockChangeWatency
				+ mmSOCPawametews.WwitebackWatency + v->WwitebackChunkSize * 1024.0 / 32.0 / SOCCWK;
		v->Watewmawk.WwitebackFCWKChangeWatewmawk = mmSOCPawametews.FCWKChangeWatency
				+ mmSOCPawametews.WwitebackWatency + v->WwitebackChunkSize * 1024 / 32 / SOCCWK;
	}

	if (v->USWWetwainingWequiwedFinaw)
		v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk = v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk
				+ mmSOCPawametews.USWWetwainingWatency;

	if (v->USWWetwainingWequiwedFinaw)
		v->Watewmawk.WwitebackFCWKChangeWatewmawk = v->Watewmawk.WwitebackFCWKChangeWatewmawk
				+ mmSOCPawametews.USWWetwainingWatency;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WwitebackDWAMCwockChangeWatewmawk = %f\n",
			__func__, v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk);
	dmw_pwint("DMW::%s: WwitebackFCWKChangeWatewmawk = %f\n", __func__, v->Watewmawk.WwitebackFCWKChangeWatewmawk);
	dmw_pwint("DMW::%s: WwitebackUwgentWatewmawk = %f\n", __func__, v->Watewmawk.WwitebackUwgentWatewmawk);
	dmw_pwint("DMW::%s: v->USWWetwainingWequiwedFinaw = %d\n", __func__, v->USWWetwainingWequiwedFinaw);
	dmw_pwint("DMW::%s: USWWetwainingWatency = %f\n", __func__, mmSOCPawametews.USWWetwainingWatency);
#endif

	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		TotawPixewBW = TotawPixewBW + DPPPewSuwface[k] * (SwathWidthY[k] * BytePewPixewDETY[k] * v->VWatio[k] +
				SwathWidthC[k] * BytePewPixewDETC[k] * v->VWatioChwoma[k]) / (v->HTotaw[k] / v->PixewCwock[k]);
	}

	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {

		WBWatencyHidingSouwceWinesY[k] = dmw_min((doubwe) v->MaxWineBuffewWines, dmw_fwoow(v->WineBuffewSizeFinaw / v->WBBitPewPixew[k] / (SwathWidthY[k] / dmw_max(v->HWatio[k], 1.0)), 1)) - (v->vtaps[k] - 1);
		WBWatencyHidingSouwceWinesC[k] = dmw_min((doubwe) v->MaxWineBuffewWines, dmw_fwoow(v->WineBuffewSizeFinaw / v->WBBitPewPixew[k] / (SwathWidthC[k] / dmw_max(v->HWatioChwoma[k], 1.0)), 1)) - (v->VTAPsChwoma[k] - 1);


#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d, v->MaxWineBuffewWines = %d\n", __func__, k, v->MaxWineBuffewWines);
		dmw_pwint("DMW::%s: k=%d, v->WineBuffewSizeFinaw     = %d\n", __func__, k, v->WineBuffewSizeFinaw);
		dmw_pwint("DMW::%s: k=%d, v->WBBitPewPixew      = %d\n", __func__, k, v->WBBitPewPixew[k]);
		dmw_pwint("DMW::%s: k=%d, v->HWatio             = %f\n", __func__, k, v->HWatio[k]);
		dmw_pwint("DMW::%s: k=%d, v->vtaps              = %d\n", __func__, k, v->vtaps[k]);
#endif

		EffectiveWBWatencyHidingY = WBWatencyHidingSouwceWinesY[k] / v->VWatio[k] * (v->HTotaw[k] / v->PixewCwock[k]);
		EffectiveWBWatencyHidingC = WBWatencyHidingSouwceWinesC[k] / v->VWatioChwoma[k] * (v->HTotaw[k] / v->PixewCwock[k]);
		EffectiveDETBuffewSizeY = DETBuffewSizeY[k];

		if (UnboundedWequestEnabwed) {
			EffectiveDETBuffewSizeY = EffectiveDETBuffewSizeY
					+ CompwessedBuffewSizeInkByte * 1024
							* (SwathWidthY[k] * BytePewPixewDETY[k] * v->VWatio[k])
							/ (v->HTotaw[k] / v->PixewCwock[k]) / TotawPixewBW;
		}

		WinesInDETY[k] = (doubwe) EffectiveDETBuffewSizeY / BytePewPixewDETY[k] / SwathWidthY[k];
		WinesInDETYWoundedDownToSwath[k] = dmw_fwoow(WinesInDETY[k], SwathHeightY[k]);
		FuwwDETBuffewingTimeY = WinesInDETYWoundedDownToSwath[k] * (v->HTotaw[k] / v->PixewCwock[k]) / v->VWatio[k];

		ActiveCwockChangeWatencyHidingY = EffectiveWBWatencyHidingY + FuwwDETBuffewingTimeY
				- (DSTXAftewScawew[k] / v->HTotaw[k] + DSTYAftewScawew[k]) * v->HTotaw[k] / v->PixewCwock[k];

		if (v->NumbewOfActiveSuwfaces > 1) {
			ActiveCwockChangeWatencyHidingY = ActiveCwockChangeWatencyHidingY
					- (1.0 - 1.0 / v->NumbewOfActiveSuwfaces) * SwathHeightY[k] * v->HTotaw[k]
							/ v->PixewCwock[k] / v->VWatio[k];
		}

		if (BytePewPixewDETC[k] > 0) {
			WinesInDETC[k] = DETBuffewSizeC[k] / BytePewPixewDETC[k] / SwathWidthC[k];
			WinesInDETCWoundedDownToSwath[k] = dmw_fwoow(WinesInDETC[k], SwathHeightC[k]);
			FuwwDETBuffewingTimeC = WinesInDETCWoundedDownToSwath[k] * (v->HTotaw[k] / v->PixewCwock[k])
					/ v->VWatioChwoma[k];
			ActiveCwockChangeWatencyHidingC = EffectiveWBWatencyHidingC + FuwwDETBuffewingTimeC
					- (DSTXAftewScawew[k] / v->HTotaw[k] + DSTYAftewScawew[k]) * v->HTotaw[k]
							/ v->PixewCwock[k];
			if (v->NumbewOfActiveSuwfaces > 1) {
				ActiveCwockChangeWatencyHidingC = ActiveCwockChangeWatencyHidingC
						- (1 - 1 / v->NumbewOfActiveSuwfaces) * SwathHeightC[k] * v->HTotaw[k]
								/ v->PixewCwock[k] / v->VWatioChwoma[k];
			}
			ActiveCwockChangeWatencyHiding = dmw_min(ActiveCwockChangeWatencyHidingY,
					ActiveCwockChangeWatencyHidingC);
		} ewse {
			ActiveCwockChangeWatencyHiding = ActiveCwockChangeWatencyHidingY;
		}

		ActiveDWAMCwockChangeWatencyMawgin[k] = ActiveCwockChangeWatencyHiding - v->Watewmawk.UwgentWatewmawk
				- v->Watewmawk.DWAMCwockChangeWatewmawk;
		ActiveFCWKChangeWatencyMawgin[k] = ActiveCwockChangeWatencyHiding - v->Watewmawk.UwgentWatewmawk
				- v->Watewmawk.FCWKChangeWatewmawk;
		USWWetwainingWatencyMawgin[k] = ActiveCwockChangeWatencyHiding - v->Watewmawk.USWWetwainingWatewmawk;

		if (v->WwitebackEnabwe[k]) {
			WwitebackWatencyHiding = v->WwitebackIntewfaceBuffewSize * 1024
					/ (v->WwitebackDestinationWidth[k] * v->WwitebackDestinationHeight[k]
							/ (v->WwitebackSouwceHeight[k] * v->HTotaw[k] / v->PixewCwock[k]) * 4);
			if (v->WwitebackPixewFowmat[k] == dm_444_64)
				WwitebackWatencyHiding = WwitebackWatencyHiding / 2;

			WwitebackDWAMCwockChangeWatencyMawgin = WwitebackWatencyHiding
					- v->Watewmawk.WwitebackDWAMCwockChangeWatewmawk;

			WwitebackFCWKChangeWatencyMawgin = WwitebackWatencyHiding
					- v->Watewmawk.WwitebackFCWKChangeWatewmawk;

			ActiveDWAMCwockChangeWatencyMawgin[k] = dmw_min(ActiveDWAMCwockChangeWatencyMawgin[k],
					WwitebackFCWKChangeWatencyMawgin);
			ActiveFCWKChangeWatencyMawgin[k] = dmw_min(ActiveFCWKChangeWatencyMawgin[k],
					WwitebackDWAMCwockChangeWatencyMawgin);
		}
		MaxActiveDWAMCwockChangeWatencySuppowted[k] =
				(v->UsesMAWWFowPStateChange[k] == dm_use_maww_pstate_change_phantom_pipe) ?
						0 :
						(ActiveDWAMCwockChangeWatencyMawgin[k]
								+ mmSOCPawametews.DWAMCwockChangeWatency);
	}

	fow (i = 0; i < v->NumbewOfActiveSuwfaces; ++i) {
		fow (j = 0; j < v->NumbewOfActiveSuwfaces; ++j) {
			if (i == j ||
					(v->BwendingAndTiming[i] == i && v->BwendingAndTiming[j] == i) ||
					(v->BwendingAndTiming[j] == j && v->BwendingAndTiming[i] == j) ||
					(v->BwendingAndTiming[i] == v->BwendingAndTiming[j] && v->BwendingAndTiming[i] != i) ||
					(v->SynchwonizeTimingsFinaw && v->PixewCwock[i] == v->PixewCwock[j] &&
					v->HTotaw[i] == v->HTotaw[j] && v->VTotaw[i] == v->VTotaw[j] &&
					v->VActive[i] == v->VActive[j]) || (v->SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw &&
					(v->DWWDispway[i] || v->DWWDispway[j]))) {
				SynchwonizedSuwfaces[i][j] = twue;
			} ewse {
				SynchwonizedSuwfaces[i][j] = fawse;
			}
		}
	}

	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		if ((v->UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) &&
				(!FoundFiwstSuwfaceWithMinActiveFCWKChangeMawgin ||
				ActiveFCWKChangeWatencyMawgin[k] < MinActiveFCWKChangeMawgin)) {
			FoundFiwstSuwfaceWithMinActiveFCWKChangeMawgin = twue;
			MinActiveFCWKChangeMawgin = ActiveFCWKChangeWatencyMawgin[k];
			SuwfaceWithMinActiveFCWKChangeMawgin = k;
		}
	}

	*MinActiveFCWKChangeWatencySuppowted = MinActiveFCWKChangeMawgin + mmSOCPawametews.FCWKChangeWatency;

	SameTimingFowFCWKChange = twue;
	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		if (!SynchwonizedSuwfaces[k][SuwfaceWithMinActiveFCWKChangeMawgin]) {
			if ((v->UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) &&
					(SameTimingFowFCWKChange ||
					ActiveFCWKChangeWatencyMawgin[k] <
					SecondMinActiveFCWKChangeMawginOneDispwayInVBWank)) {
				SecondMinActiveFCWKChangeMawginOneDispwayInVBWank = ActiveFCWKChangeWatencyMawgin[k];
			}
			SameTimingFowFCWKChange = fawse;
		}
	}

	if (MinActiveFCWKChangeMawgin > 0) {
		*FCWKChangeSuppowt = dm_fcwock_change_vactive;
	} ewse if ((SameTimingFowFCWKChange || SecondMinActiveFCWKChangeMawginOneDispwayInVBWank > 0) &&
			(PwefetchMode <= 1)) {
		*FCWKChangeSuppowt = dm_fcwock_change_vbwank;
	} ewse {
		*FCWKChangeSuppowt = dm_fcwock_change_unsuppowted;
	}

	*USWWetwainingSuppowt = twue;
	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		if ((v->UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) &&
				(USWWetwainingWatencyMawgin[k] < 0)) {
			*USWWetwainingSuppowt = fawse;
		}
	}

	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		if (v->UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_fuww_fwame &&
				v->UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_sub_viewpowt &&
				v->UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe &&
				ActiveDWAMCwockChangeWatencyMawgin[k] < 0) {
			if (PwefetchMode > 0) {
				DWAMCwockChangeSuppowtNumbew = 2;
			} ewse if (DWAMCwockChangeSuppowtNumbew == 0) {
				DWAMCwockChangeSuppowtNumbew = 1;
				WastSuwfaceWithoutMawgin = k;
			} ewse if (DWAMCwockChangeSuppowtNumbew == 1 &&
					!SynchwonizedSuwfaces[WastSuwfaceWithoutMawgin][k]) {
				DWAMCwockChangeSuppowtNumbew = 2;
			}
		}
	}

	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		if (v->UsesMAWWFowPStateChange[k] == dm_use_maww_pstate_change_fuww_fwame)
			DWAMCwockChangeMethod = 1;
		ewse if (v->UsesMAWWFowPStateChange[k] == dm_use_maww_pstate_change_sub_viewpowt)
			DWAMCwockChangeMethod = 2;
	}

	if (DWAMCwockChangeMethod == 0) {
		if (DWAMCwockChangeSuppowtNumbew == 0)
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vactive;
		ewse if (DWAMCwockChangeSuppowtNumbew == 1)
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vbwank;
		ewse
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_unsuppowted;
	} ewse if (DWAMCwockChangeMethod == 1) {
		if (DWAMCwockChangeSuppowtNumbew == 0)
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vactive_w_maww_fuww_fwame;
		ewse if (DWAMCwockChangeSuppowtNumbew == 1)
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vbwank_w_maww_fuww_fwame;
		ewse
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_unsuppowted;
	} ewse {
		if (DWAMCwockChangeSuppowtNumbew == 0)
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vactive_w_maww_sub_vp;
		ewse if (DWAMCwockChangeSuppowtNumbew == 1)
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_vbwank_w_maww_sub_vp;
		ewse
			*DWAMCwockChangeSuppowt = dm_dwam_cwock_change_unsuppowted;
	}

	fow (k = 0; k < v->NumbewOfActiveSuwfaces; ++k) {
		unsigned int dst_y_pstate;
		unsigned int swc_y_pstate_w;
		unsigned int swc_y_pstate_c;
		unsigned int swc_y_ahead_w, swc_y_ahead_c, sub_vp_wines_w, sub_vp_wines_c;

		dst_y_pstate = dmw_ceiw((mmSOCPawametews.DWAMCwockChangeWatency + mmSOCPawametews.UwgentWatency) / (v->HTotaw[k] / v->PixewCwock[k]), 1);
		swc_y_pstate_w = dmw_ceiw(dst_y_pstate * v->VWatio[k], SwathHeightY[k]);
		swc_y_ahead_w = dmw_fwoow(DETBuffewSizeY[k] / BytePewPixewDETY[k] / SwathWidthY[k], SwathHeightY[k]) + WBWatencyHidingSouwceWinesY[k];
		sub_vp_wines_w = swc_y_pstate_w + swc_y_ahead_w + v->meta_wow_height[k];

#ifdef __DMW_VBA_DEBUG__
dmw_pwint("DMW::%s: k=%d, DETBuffewSizeY               = %d\n", __func__, k, DETBuffewSizeY[k]);
dmw_pwint("DMW::%s: k=%d, BytePewPixewDETY             = %f\n", __func__, k, BytePewPixewDETY[k]);
dmw_pwint("DMW::%s: k=%d, SwathWidthY                  = %d\n", __func__, k, SwathWidthY[k]);
dmw_pwint("DMW::%s: k=%d, SwathHeightY                 = %d\n", __func__, k, SwathHeightY[k]);
dmw_pwint("DMW::%s: k=%d, WBWatencyHidingSouwceWinesY  = %d\n", __func__, k, WBWatencyHidingSouwceWinesY[k]);
dmw_pwint("DMW::%s: k=%d, dst_y_pstate      = %d\n", __func__, k, dst_y_pstate);
dmw_pwint("DMW::%s: k=%d, swc_y_pstate_w    = %d\n", __func__, k, swc_y_pstate_w);
dmw_pwint("DMW::%s: k=%d, swc_y_ahead_w     = %d\n", __func__, k, swc_y_ahead_w);
dmw_pwint("DMW::%s: k=%d, v->meta_wow_height   = %d\n", __func__, k, v->meta_wow_height[k]);
dmw_pwint("DMW::%s: k=%d, sub_vp_wines_w    = %d\n", __func__, k, sub_vp_wines_w);
#endif
		SubViewpowtWinesNeededInMAWW[k] = sub_vp_wines_w;

		if (BytePewPixewDETC[k] > 0) {
			swc_y_pstate_c = dmw_ceiw(dst_y_pstate * v->VWatioChwoma[k], SwathHeightC[k]);
			swc_y_ahead_c = dmw_fwoow(DETBuffewSizeC[k] / BytePewPixewDETC[k] / SwathWidthC[k], SwathHeightC[k]) + WBWatencyHidingSouwceWinesC[k];
			sub_vp_wines_c = swc_y_pstate_c + swc_y_ahead_c + v->meta_wow_height_chwoma[k];
			SubViewpowtWinesNeededInMAWW[k] = dmw_max(sub_vp_wines_w, sub_vp_wines_c);

#ifdef __DMW_VBA_DEBUG__
dmw_pwint("DMW::%s: k=%d, swc_y_pstate_c            = %d\n", __func__, k, swc_y_pstate_c);
dmw_pwint("DMW::%s: k=%d, swc_y_ahead_c             = %d\n", __func__, k, swc_y_ahead_c);
dmw_pwint("DMW::%s: k=%d, v->meta_wow_height_chwoma    = %d\n", __func__, k, v->meta_wow_height_chwoma[k]);
dmw_pwint("DMW::%s: k=%d, sub_vp_wines_c            = %d\n", __func__, k, sub_vp_wines_c);
#endif
		}
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: DWAMCwockChangeSuppowt = %d\n", __func__, *DWAMCwockChangeSuppowt);
	dmw_pwint("DMW::%s: FCWKChangeSuppowt = %d\n", __func__, *FCWKChangeSuppowt);
	dmw_pwint("DMW::%s: MinActiveFCWKChangeWatencySuppowted = %f\n",
			__func__, *MinActiveFCWKChangeWatencySuppowted);
	dmw_pwint("DMW::%s: USWWetwainingSuppowt = %d\n", __func__, *USWWetwainingSuppowt);
#endif
} // CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt

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
		doubwe DISPCWKDPPCWKVCOSpeed)
{
	doubwe DISPCWK_H, DISPCWK_V, DISPCWK_HB;

	DISPCWK_H = PixewCwock * dmw_ceiw(WwitebackHTaps / 8.0, 1) / WwitebackHWatio;
	DISPCWK_V = PixewCwock * (WwitebackVTaps * dmw_ceiw(WwitebackDestinationWidth / 6.0, 1) + 8.0) / HTotaw;
	DISPCWK_HB = PixewCwock * WwitebackVTaps * (WwitebackDestinationWidth *
			WwitebackVTaps - WwitebackWineBuffewSize / 57.0) / 6.0 / WwitebackSouwceWidth;
	wetuwn dmw32_WoundToDFSGwanuwawity(dmw_max3(DISPCWK_H, DISPCWK_V, DISPCWK_HB), 1, DISPCWKDPPCWKVCOSpeed);
}

void dmw32_CawcuwateMinAndMaxPwefetchMode(
		enum dm_pwefetch_modes   AwwowFowPStateChangeOwStuttewInVBwankFinaw,
		unsigned int             *MinPwefetchMode,
		unsigned int             *MaxPwefetchMode)
{
	if (AwwowFowPStateChangeOwStuttewInVBwankFinaw == dm_pwefetch_suppowt_none) {
		*MinPwefetchMode = 3;
		*MaxPwefetchMode = 3;
	} ewse if (AwwowFowPStateChangeOwStuttewInVBwankFinaw == dm_pwefetch_suppowt_stuttew) {
		*MinPwefetchMode = 2;
		*MaxPwefetchMode = 2;
	} ewse if (AwwowFowPStateChangeOwStuttewInVBwankFinaw == dm_pwefetch_suppowt_fcwk_and_stuttew) {
		*MinPwefetchMode = 1;
		*MaxPwefetchMode = 1;
	} ewse if (AwwowFowPStateChangeOwStuttewInVBwankFinaw == dm_pwefetch_suppowt_ucwk_fcwk_and_stuttew) {
		*MinPwefetchMode = 0;
		*MaxPwefetchMode = 0;
	} ewse {
		*MinPwefetchMode = 0;
		*MaxPwefetchMode = 3;
	}
} // CawcuwateMinAndMaxPwefetchMode

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
		doubwe              CuwsowWequestDewivewyTimePwefetch[])
{
	doubwe   weq_pew_swath_ub;
	unsigned int k;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d : HWatio = %f\n", __func__, k, HWatio[k]);
		dmw_pwint("DMW::%s: k=%d : VWatio = %f\n", __func__, k, VWatio[k]);
		dmw_pwint("DMW::%s: k=%d : HWatioChwoma = %f\n", __func__, k, HWatioChwoma[k]);
		dmw_pwint("DMW::%s: k=%d : VWatioChwoma = %f\n", __func__, k, VWatioChwoma[k]);
		dmw_pwint("DMW::%s: k=%d : swath_width_wuma_ub = %d\n", __func__, k, swath_width_wuma_ub[k]);
		dmw_pwint("DMW::%s: k=%d : swath_width_chwoma_ub = %d\n", __func__, k, swath_width_chwoma_ub[k]);
		dmw_pwint("DMW::%s: k=%d : PSCW_THWOUGHPUT = %f\n", __func__, k, PSCW_THWOUGHPUT[k]);
		dmw_pwint("DMW::%s: k=%d : PSCW_THWOUGHPUT_CHWOMA = %f\n", __func__, k, PSCW_THWOUGHPUT_CHWOMA[k]);
		dmw_pwint("DMW::%s: k=%d : DPPPewSuwface = %d\n", __func__, k, DPPPewSuwface[k]);
		dmw_pwint("DMW::%s: k=%d : PixewCwock = %f\n", __func__, k, PixewCwock[k]);
		dmw_pwint("DMW::%s: k=%d : Dppcwk = %f\n", __func__, k, Dppcwk[k]);
#endif

		if (VWatio[k] <= 1) {
			DispwayPipeWineDewivewyTimeWuma[k] =
					swath_width_wuma_ub[k] * DPPPewSuwface[k] / HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWuma[k] = swath_width_wuma_ub[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k];
		}

		if (BytePewPixewC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwoma[k] = 0;
		} ewse {
			if (VWatioChwoma[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwoma[k] =
					swath_width_chwoma_ub[k] * DPPPewSuwface[k] / HWatioChwoma[k] / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwoma[k] =
					swath_width_chwoma_ub[k] / PSCW_THWOUGHPUT_CHWOMA[k] / Dppcwk[k];
			}
		}

		if (VWatioPwefetchY[k] <= 1) {
			DispwayPipeWineDewivewyTimeWumaPwefetch[k] =
					swath_width_wuma_ub[k] * DPPPewSuwface[k] / HWatio[k] / PixewCwock[k];
		} ewse {
			DispwayPipeWineDewivewyTimeWumaPwefetch[k] =
					swath_width_wuma_ub[k] / PSCW_THWOUGHPUT[k] / Dppcwk[k];
		}

		if (BytePewPixewC[k] == 0) {
			DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (VWatioPwefetchC[k] <= 1) {
				DispwayPipeWineDewivewyTimeChwomaPwefetch[k] = swath_width_chwoma_ub[k] *
						DPPPewSuwface[k] / HWatioChwoma[k] / PixewCwock[k];
			} ewse {
				DispwayPipeWineDewivewyTimeChwomaPwefetch[k] =
						swath_width_chwoma_ub[k] / PSCW_THWOUGHPUT_CHWOMA[k] / Dppcwk[k];
			}
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWineDewivewyTimeWuma = %f\n",
				__func__, k, DispwayPipeWineDewivewyTimeWuma[k]);
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWineDewivewyTimeWumaPwefetch = %f\n",
				__func__, k, DispwayPipeWineDewivewyTimeWumaPwefetch[k]);
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWineDewivewyTimeChwoma = %f\n",
				__func__, k, DispwayPipeWineDewivewyTimeChwoma[k]);
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWineDewivewyTimeChwomaPwefetch = %f\n",
				__func__, k, DispwayPipeWineDewivewyTimeChwomaPwefetch[k]);
#endif
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (!IsVewticaw(SouwceWotation[k]))
			weq_pew_swath_ub = swath_width_wuma_ub[k] / BwockWidth256BytesY[k];
		ewse
			weq_pew_swath_ub = swath_width_wuma_ub[k] / BwockHeight256BytesY[k];
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d : weq_pew_swath_ub = %f (Wuma)\n", __func__, k, weq_pew_swath_ub);
#endif

		DispwayPipeWequestDewivewyTimeWuma[k] = DispwayPipeWineDewivewyTimeWuma[k] / weq_pew_swath_ub;
		DispwayPipeWequestDewivewyTimeWumaPwefetch[k] =
				DispwayPipeWineDewivewyTimeWumaPwefetch[k] / weq_pew_swath_ub;
		if (BytePewPixewC[k] == 0) {
			DispwayPipeWequestDewivewyTimeChwoma[k] = 0;
			DispwayPipeWequestDewivewyTimeChwomaPwefetch[k] = 0;
		} ewse {
			if (!IsVewticaw(SouwceWotation[k]))
				weq_pew_swath_ub = swath_width_chwoma_ub[k] / BwockWidth256BytesC[k];
			ewse
				weq_pew_swath_ub = swath_width_chwoma_ub[k] / BwockHeight256BytesC[k];
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%d : weq_pew_swath_ub = %f (Chwoma)\n", __func__, k, weq_pew_swath_ub);
#endif
			DispwayPipeWequestDewivewyTimeChwoma[k] =
					DispwayPipeWineDewivewyTimeChwoma[k] / weq_pew_swath_ub;
			DispwayPipeWequestDewivewyTimeChwomaPwefetch[k] =
					DispwayPipeWineDewivewyTimeChwomaPwefetch[k] / weq_pew_swath_ub;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWequestDewivewyTimeWuma = %f\n",
				__func__, k, DispwayPipeWequestDewivewyTimeWuma[k]);
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWequestDewivewyTimeWumaPwefetch = %f\n",
				__func__, k, DispwayPipeWequestDewivewyTimeWumaPwefetch[k]);
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWequestDewivewyTimeChwoma = %f\n",
				__func__, k, DispwayPipeWequestDewivewyTimeChwoma[k]);
		dmw_pwint("DMW::%s: k=%d : DispwayPipeWequestDewivewyTimeChwomaPwefetch = %f\n",
				__func__, k, DispwayPipeWequestDewivewyTimeChwomaPwefetch[k]);
#endif
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		unsigned int cuwsow_weq_pew_width;

		cuwsow_weq_pew_width = dmw_ceiw((doubwe) CuwsowWidth[k][0] * (doubwe) CuwsowBPP[k][0] /
				256.0 / 8.0, 1.0);
		if (NumbewOfCuwsows[k] > 0) {
			if (VWatio[k] <= 1) {
				CuwsowWequestDewivewyTime[k] = (doubwe) CuwsowWidth[k][0] /
						HWatio[k] / PixewCwock[k] / cuwsow_weq_pew_width;
			} ewse {
				CuwsowWequestDewivewyTime[k] = (doubwe) CuwsowWidth[k][0] /
						PSCW_THWOUGHPUT[k] / Dppcwk[k] / cuwsow_weq_pew_width;
			}
			if (VWatioPwefetchY[k] <= 1) {
				CuwsowWequestDewivewyTimePwefetch[k] = (doubwe) CuwsowWidth[k][0] /
						HWatio[k] / PixewCwock[k] / cuwsow_weq_pew_width;
			} ewse {
				CuwsowWequestDewivewyTimePwefetch[k] = (doubwe) CuwsowWidth[k][0] /
						PSCW_THWOUGHPUT[k] / Dppcwk[k] / cuwsow_weq_pew_width;
			}
		} ewse {
			CuwsowWequestDewivewyTime[k] = 0;
			CuwsowWequestDewivewyTimePwefetch[k] = 0;
		}
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%d : NumbewOfCuwsows = %d\n",
				__func__, k, NumbewOfCuwsows[k]);
		dmw_pwint("DMW::%s: k=%d : CuwsowWequestDewivewyTime = %f\n",
				__func__, k, CuwsowWequestDewivewyTime[k]);
		dmw_pwint("DMW::%s: k=%d : CuwsowWequestDewivewyTimePwefetch = %f\n",
				__func__, k, CuwsowWequestDewivewyTimePwefetch[k]);
#endif
	}
} // CawcuwatePixewDewivewyTimes

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
		doubwe time_pew_pte_gwoup_fwip_chwoma[])
{
	unsigned int   meta_chunk_width;
	unsigned int   min_meta_chunk_width;
	unsigned int   meta_chunk_pew_wow_int;
	unsigned int   meta_wow_wemaindew;
	unsigned int   meta_chunk_thweshowd;
	unsigned int   meta_chunks_pew_wow_ub;
	unsigned int   meta_chunk_width_chwoma;
	unsigned int   min_meta_chunk_width_chwoma;
	unsigned int   meta_chunk_pew_wow_int_chwoma;
	unsigned int   meta_wow_wemaindew_chwoma;
	unsigned int   meta_chunk_thweshowd_chwoma;
	unsigned int   meta_chunks_pew_wow_ub_chwoma;
	unsigned int   dpte_gwoup_width_wuma;
	unsigned int   dpte_gwoups_pew_wow_wuma_ub;
	unsigned int   dpte_gwoup_width_chwoma;
	unsigned int   dpte_gwoups_pew_wow_chwoma_ub;
	unsigned int k;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		DST_Y_PEW_PTE_WOW_NOM_W[k] = dpte_wow_height[k] / VWatio[k];
		if (BytePewPixewC[k] == 0)
			DST_Y_PEW_PTE_WOW_NOM_C[k] = 0;
		ewse
			DST_Y_PEW_PTE_WOW_NOM_C[k] = dpte_wow_height_chwoma[k] / VWatioChwoma[k];
		DST_Y_PEW_META_WOW_NOM_W[k] = meta_wow_height[k] / VWatio[k];
		if (BytePewPixewC[k] == 0)
			DST_Y_PEW_META_WOW_NOM_C[k] = 0;
		ewse
			DST_Y_PEW_META_WOW_NOM_C[k] = meta_wow_height_chwoma[k] / VWatioChwoma[k];
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (DCCEnabwe[k] == twue) {
			meta_chunk_width = MetaChunkSize * 1024 * 256 / BytePewPixewY[k] / meta_wow_height[k];
			min_meta_chunk_width = MinMetaChunkSizeBytes * 256 / BytePewPixewY[k] / meta_wow_height[k];
			meta_chunk_pew_wow_int = meta_wow_width[k] / meta_chunk_width;
			meta_wow_wemaindew = meta_wow_width[k] % meta_chunk_width;
			if (!IsVewticaw(SouwceWotation[k]))
				meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_width[k];
			ewse
				meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_height[k];

			if (meta_wow_wemaindew <= meta_chunk_thweshowd)
				meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 1;
			ewse
				meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 2;

			TimePewMetaChunkNominaw[k] = meta_wow_height[k] / VWatio[k] *
					HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			TimePewMetaChunkVBwank[k] = DestinationWinesToWequestWowInVBwank[k] *
					HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			TimePewMetaChunkFwip[k] = DestinationWinesToWequestWowInImmediateFwip[k] *
					HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub;
			if (BytePewPixewC[k] == 0) {
				TimePewChwomaMetaChunkNominaw[k] = 0;
				TimePewChwomaMetaChunkVBwank[k] = 0;
				TimePewChwomaMetaChunkFwip[k] = 0;
			} ewse {
				meta_chunk_width_chwoma = MetaChunkSize * 1024 * 256 / BytePewPixewC[k] /
						meta_wow_height_chwoma[k];
				min_meta_chunk_width_chwoma = MinMetaChunkSizeBytes * 256 / BytePewPixewC[k] /
						meta_wow_height_chwoma[k];
				meta_chunk_pew_wow_int_chwoma = (doubwe) meta_wow_width_chwoma[k] /
						meta_chunk_width_chwoma;
				meta_wow_wemaindew_chwoma = meta_wow_width_chwoma[k] % meta_chunk_width_chwoma;
				if (!IsVewticaw(SouwceWotation[k])) {
					meta_chunk_thweshowd_chwoma = 2 * min_meta_chunk_width_chwoma -
							meta_weq_width_chwoma[k];
				} ewse {
					meta_chunk_thweshowd_chwoma = 2 * min_meta_chunk_width_chwoma -
							meta_weq_height_chwoma[k];
				}
				if (meta_wow_wemaindew_chwoma <= meta_chunk_thweshowd_chwoma)
					meta_chunks_pew_wow_ub_chwoma = meta_chunk_pew_wow_int_chwoma + 1;
				ewse
					meta_chunks_pew_wow_ub_chwoma = meta_chunk_pew_wow_int_chwoma + 2;

				TimePewChwomaMetaChunkNominaw[k] = meta_wow_height_chwoma[k] / VWatioChwoma[k] *
						HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub_chwoma;
				TimePewChwomaMetaChunkVBwank[k] = DestinationWinesToWequestWowInVBwank[k] *
						HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub_chwoma;
				TimePewChwomaMetaChunkFwip[k] = DestinationWinesToWequestWowInImmediateFwip[k] *
						HTotaw[k] / PixewCwock[k] / meta_chunks_pew_wow_ub_chwoma;
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

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (GPUVMEnabwe == twue) {
			if (!IsVewticaw(SouwceWotation[k])) {
				dpte_gwoup_width_wuma = (doubwe) dpte_gwoup_bytes[k] /
						(doubwe) PTEWequestSizeY[k] * PixewPTEWeqWidthY[k];
			} ewse {
				dpte_gwoup_width_wuma = (doubwe) dpte_gwoup_bytes[k] /
						(doubwe) PTEWequestSizeY[k] * PixewPTEWeqHeightY[k];
			}

			if (use_one_wow_fow_fwame[k]) {
				dpte_gwoups_pew_wow_wuma_ub = dmw_ceiw((doubwe) dpte_wow_width_wuma_ub[k] /
						(doubwe) dpte_gwoup_width_wuma / 2.0, 1.0);
			} ewse {
				dpte_gwoups_pew_wow_wuma_ub = dmw_ceiw((doubwe) dpte_wow_width_wuma_ub[k] /
						(doubwe) dpte_gwoup_width_wuma, 1.0);
			}
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0d, use_one_wow_fow_fwame        = %d\n",
					__func__, k, use_one_wow_fow_fwame[k]);
			dmw_pwint("DMW::%s: k=%0d, dpte_gwoup_bytes             = %d\n",
					__func__, k, dpte_gwoup_bytes[k]);
			dmw_pwint("DMW::%s: k=%0d, PTEWequestSizeY              = %d\n",
					__func__, k, PTEWequestSizeY[k]);
			dmw_pwint("DMW::%s: k=%0d, PixewPTEWeqWidthY            = %d\n",
					__func__, k, PixewPTEWeqWidthY[k]);
			dmw_pwint("DMW::%s: k=%0d, PixewPTEWeqHeightY           = %d\n",
					__func__, k, PixewPTEWeqHeightY[k]);
			dmw_pwint("DMW::%s: k=%0d, dpte_wow_width_wuma_ub       = %d\n",
					__func__, k, dpte_wow_width_wuma_ub[k]);
			dmw_pwint("DMW::%s: k=%0d, dpte_gwoup_width_wuma        = %d\n",
					__func__, k, dpte_gwoup_width_wuma);
			dmw_pwint("DMW::%s: k=%0d, dpte_gwoups_pew_wow_wuma_ub  = %d\n",
					__func__, k, dpte_gwoups_pew_wow_wuma_ub);
#endif

			time_pew_pte_gwoup_nom_wuma[k] = DST_Y_PEW_PTE_WOW_NOM_W[k] *
					HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			time_pew_pte_gwoup_vbwank_wuma[k] = DestinationWinesToWequestWowInVBwank[k] *
					HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			time_pew_pte_gwoup_fwip_wuma[k] = DestinationWinesToWequestWowInImmediateFwip[k] *
					HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_wuma_ub;
			if (BytePewPixewC[k] == 0) {
				time_pew_pte_gwoup_nom_chwoma[k] = 0;
				time_pew_pte_gwoup_vbwank_chwoma[k] = 0;
				time_pew_pte_gwoup_fwip_chwoma[k] = 0;
			} ewse {
				if (!IsVewticaw(SouwceWotation[k])) {
					dpte_gwoup_width_chwoma = (doubwe) dpte_gwoup_bytes[k] /
							(doubwe) PTEWequestSizeC[k] * PixewPTEWeqWidthC[k];
				} ewse {
					dpte_gwoup_width_chwoma = (doubwe) dpte_gwoup_bytes[k] /
							(doubwe) PTEWequestSizeC[k] * PixewPTEWeqHeightC[k];
				}

				if (use_one_wow_fow_fwame[k]) {
					dpte_gwoups_pew_wow_chwoma_ub = dmw_ceiw((doubwe) dpte_wow_width_chwoma_ub[k] /
							(doubwe) dpte_gwoup_width_chwoma / 2.0, 1.0);
				} ewse {
					dpte_gwoups_pew_wow_chwoma_ub = dmw_ceiw((doubwe) dpte_wow_width_chwoma_ub[k] /
							(doubwe) dpte_gwoup_width_chwoma, 1.0);
				}
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%0d, dpte_wow_width_chwoma_ub        = %d\n",
						__func__, k, dpte_wow_width_chwoma_ub[k]);
				dmw_pwint("DMW::%s: k=%0d, dpte_gwoup_width_chwoma        = %d\n",
						__func__, k, dpte_gwoup_width_chwoma);
				dmw_pwint("DMW::%s: k=%0d, dpte_gwoups_pew_wow_chwoma_ub  = %d\n",
						__func__, k, dpte_gwoups_pew_wow_chwoma_ub);
#endif
				time_pew_pte_gwoup_nom_chwoma[k] = DST_Y_PEW_PTE_WOW_NOM_C[k] *
						HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_chwoma_ub;
				time_pew_pte_gwoup_vbwank_chwoma[k] = DestinationWinesToWequestWowInVBwank[k] *
						HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_chwoma_ub;
				time_pew_pte_gwoup_fwip_chwoma[k] = DestinationWinesToWequestWowInImmediateFwip[k] *
						HTotaw[k] / PixewCwock[k] / dpte_gwoups_pew_wow_chwoma_ub;
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
		dmw_pwint("DMW::%s: k=%0d, DestinationWinesToWequestWowInVBwank         = %f\n",
				__func__, k, DestinationWinesToWequestWowInVBwank[k]);
		dmw_pwint("DMW::%s: k=%0d, DestinationWinesToWequestWowInImmediateFwip  = %f\n",
				__func__, k, DestinationWinesToWequestWowInImmediateFwip[k]);
		dmw_pwint("DMW::%s: k=%0d, DST_Y_PEW_PTE_WOW_NOM_W                      = %f\n",
				__func__, k, DST_Y_PEW_PTE_WOW_NOM_W[k]);
		dmw_pwint("DMW::%s: k=%0d, DST_Y_PEW_PTE_WOW_NOM_C                      = %f\n",
				__func__, k, DST_Y_PEW_PTE_WOW_NOM_C[k]);
		dmw_pwint("DMW::%s: k=%0d, DST_Y_PEW_META_WOW_NOM_W                     = %f\n",
				__func__, k, DST_Y_PEW_META_WOW_NOM_W[k]);
		dmw_pwint("DMW::%s: k=%0d, DST_Y_PEW_META_WOW_NOM_C                     = %f\n",
				__func__, k, DST_Y_PEW_META_WOW_NOM_C[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewMetaChunkNominaw          = %f\n",
				__func__, k, TimePewMetaChunkNominaw[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewMetaChunkVBwank           = %f\n",
				__func__, k, TimePewMetaChunkVBwank[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewMetaChunkFwip             = %f\n",
				__func__, k, TimePewMetaChunkFwip[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewChwomaMetaChunkNominaw    = %f\n",
				__func__, k, TimePewChwomaMetaChunkNominaw[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewChwomaMetaChunkVBwank     = %f\n",
				__func__, k, TimePewChwomaMetaChunkVBwank[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewChwomaMetaChunkFwip       = %f\n",
				__func__, k, TimePewChwomaMetaChunkFwip[k]);
		dmw_pwint("DMW::%s: k=%0d, time_pew_pte_gwoup_nom_wuma      = %f\n",
				__func__, k, time_pew_pte_gwoup_nom_wuma[k]);
		dmw_pwint("DMW::%s: k=%0d, time_pew_pte_gwoup_vbwank_wuma   = %f\n",
				__func__, k, time_pew_pte_gwoup_vbwank_wuma[k]);
		dmw_pwint("DMW::%s: k=%0d, time_pew_pte_gwoup_fwip_wuma     = %f\n",
				__func__, k, time_pew_pte_gwoup_fwip_wuma[k]);
		dmw_pwint("DMW::%s: k=%0d, time_pew_pte_gwoup_nom_chwoma    = %f\n",
				__func__, k, time_pew_pte_gwoup_nom_chwoma[k]);
		dmw_pwint("DMW::%s: k=%0d, time_pew_pte_gwoup_vbwank_chwoma = %f\n",
				__func__, k, time_pew_pte_gwoup_vbwank_chwoma[k]);
		dmw_pwint("DMW::%s: k=%0d, time_pew_pte_gwoup_fwip_chwoma   = %f\n",
				__func__, k, time_pew_pte_gwoup_fwip_chwoma[k]);
#endif
	}
} // CawcuwateMetaAndPTETimes

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
		doubwe      TimePewVMWequestFwip[])
{
	unsigned int k;
	unsigned int   num_gwoup_pew_wowew_vm_stage;
	unsigned int   num_weq_pew_wowew_vm_stage;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: NumbewOfActiveSuwfaces = %d\n", __func__, NumbewOfActiveSuwfaces);
	dmw_pwint("DMW::%s: GPUVMEnabwe = %d\n", __func__, GPUVMEnabwe);
#endif
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%0d, DCCEnabwe = %d\n", __func__, k, DCCEnabwe[k]);
		dmw_pwint("DMW::%s: k=%0d, vm_gwoup_bytes = %d\n", __func__, k, vm_gwoup_bytes[k]);
		dmw_pwint("DMW::%s: k=%0d, dpde0_bytes_pew_fwame_ub_w = %d\n",
				__func__, k, dpde0_bytes_pew_fwame_ub_w[k]);
		dmw_pwint("DMW::%s: k=%0d, dpde0_bytes_pew_fwame_ub_c = %d\n",
				__func__, k, dpde0_bytes_pew_fwame_ub_c[k]);
		dmw_pwint("DMW::%s: k=%0d, meta_pte_bytes_pew_fwame_ub_w = %d\n",
				__func__, k, meta_pte_bytes_pew_fwame_ub_w[k]);
		dmw_pwint("DMW::%s: k=%0d, meta_pte_bytes_pew_fwame_ub_c = %d\n",
				__func__, k, meta_pte_bytes_pew_fwame_ub_c[k]);
#endif

		if (GPUVMEnabwe == twue && (DCCEnabwe[k] == twue || GPUVMMaxPageTabweWevews > 1)) {
			if (DCCEnabwe[k] == fawse) {
				if (BytePewPixewC[k] > 0) {
					num_gwoup_pew_wowew_vm_stage = dmw_ceiw(
							(doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1.0) +
							dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_c[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1.0);
				} ewse {
					num_gwoup_pew_wowew_vm_stage = dmw_ceiw(
							(doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1.0);
				}
			} ewse {
				if (GPUVMMaxPageTabweWevews == 1) {
					if (BytePewPixewC[k] > 0) {
						num_gwoup_pew_wowew_vm_stage = dmw_ceiw(
							(doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1.0) +
							dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_c[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1.0);
					} ewse {
						num_gwoup_pew_wowew_vm_stage = dmw_ceiw(
								(doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) /
								(doubwe) (vm_gwoup_bytes[k]), 1.0);
					}
				} ewse {
					if (BytePewPixewC[k] > 0) {
						num_gwoup_pew_wowew_vm_stage = 2 + dmw_ceiw(
							(doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1) +
							dmw_ceiw((doubwe) (dpde0_bytes_pew_fwame_ub_c[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1) +
							dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1) +
							dmw_ceiw((doubwe) (meta_pte_bytes_pew_fwame_ub_c[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1);
					} ewse {
						num_gwoup_pew_wowew_vm_stage = 1 + dmw_ceiw(
							(doubwe) (dpde0_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1) + dmw_ceiw(
							(doubwe) (meta_pte_bytes_pew_fwame_ub_w[k]) /
							(doubwe) (vm_gwoup_bytes[k]), 1);
					}
				}
			}

			if (DCCEnabwe[k] == fawse) {
				if (BytePewPixewC[k] > 0) {
					num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64 +
							dpde0_bytes_pew_fwame_ub_c[k] / 64;
				} ewse {
					num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] / 64;
				}
			} ewse {
				if (GPUVMMaxPageTabweWevews == 1) {
					if (BytePewPixewC[k] > 0) {
						num_weq_pew_wowew_vm_stage = meta_pte_bytes_pew_fwame_ub_w[k] / 64 +
								meta_pte_bytes_pew_fwame_ub_c[k] / 64;
					} ewse {
						num_weq_pew_wowew_vm_stage = meta_pte_bytes_pew_fwame_ub_w[k] / 64;
					}
				} ewse {
					if (BytePewPixewC[k] > 0) {
						num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] /
								64 + dpde0_bytes_pew_fwame_ub_c[k] / 64 +
								meta_pte_bytes_pew_fwame_ub_w[k] / 64 +
								meta_pte_bytes_pew_fwame_ub_c[k] / 64;
					} ewse {
						num_weq_pew_wowew_vm_stage = dpde0_bytes_pew_fwame_ub_w[k] /
								64 + meta_pte_bytes_pew_fwame_ub_w[k] / 64;
					}
				}
			}

			TimePewVMGwoupVBwank[k] = DestinationWinesToWequestVMInVBwank[k] *
					HTotaw[k] / PixewCwock[k] / num_gwoup_pew_wowew_vm_stage;
			TimePewVMGwoupFwip[k] = DestinationWinesToWequestVMInImmediateFwip[k] *
					HTotaw[k] / PixewCwock[k] / num_gwoup_pew_wowew_vm_stage;
			TimePewVMWequestVBwank[k] = DestinationWinesToWequestVMInVBwank[k] *
					HTotaw[k] / PixewCwock[k] / num_weq_pew_wowew_vm_stage;
			TimePewVMWequestFwip[k] = DestinationWinesToWequestVMInImmediateFwip[k] *
					HTotaw[k] / PixewCwock[k] / num_weq_pew_wowew_vm_stage;

			if (GPUVMMaxPageTabweWevews > 2) {
				TimePewVMGwoupVBwank[k]    = TimePewVMGwoupVBwank[k] / 2;
				TimePewVMGwoupFwip[k]      = TimePewVMGwoupFwip[k] / 2;
				TimePewVMWequestVBwank[k]  = TimePewVMWequestVBwank[k] / 2;
				TimePewVMWequestFwip[k]    = TimePewVMWequestFwip[k] / 2;
			}

		} ewse {
			TimePewVMGwoupVBwank[k] = 0;
			TimePewVMGwoupFwip[k] = 0;
			TimePewVMWequestVBwank[k] = 0;
			TimePewVMWequestFwip[k] = 0;
		}

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: k=%0d, TimePewVMGwoupVBwank = %f\n", __func__, k, TimePewVMGwoupVBwank[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewVMGwoupFwip = %f\n", __func__, k, TimePewVMGwoupFwip[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewVMWequestVBwank = %f\n", __func__, k, TimePewVMWequestVBwank[k]);
		dmw_pwint("DMW::%s: k=%0d, TimePewVMWequestFwip = %f\n", __func__, k, TimePewVMWequestFwip[k]);
#endif
	}
} // CawcuwateVMGwoupAndWequestTimes

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
		unsigned int        *IndependentBwockChwoma)
{
	typedef enum {
		WEQ_256Bytes,
		WEQ_128BytesNonContiguous,
		WEQ_128BytesContiguous,
		WEQ_NA
	} WequestType;

	WequestType   WequestWuma;
	WequestType   WequestChwoma;

	unsigned int   segment_owdew_howz_contiguous_wuma;
	unsigned int   segment_owdew_howz_contiguous_chwoma;
	unsigned int   segment_owdew_vewt_contiguous_wuma;
	unsigned int   segment_owdew_vewt_contiguous_chwoma;
	unsigned int weq128_howz_wc_w;
	unsigned int weq128_howz_wc_c;
	unsigned int weq128_vewt_wc_w;
	unsigned int weq128_vewt_wc_c;
	unsigned int MAS_vp_howz_wimit;
	unsigned int MAS_vp_vewt_wimit;
	unsigned int max_vp_howz_width;
	unsigned int max_vp_vewt_height;
	unsigned int eff_suwf_width_w;
	unsigned int eff_suwf_width_c;
	unsigned int eff_suwf_height_w;
	unsigned int eff_suwf_height_c;
	unsigned int fuww_swath_bytes_howz_wc_w;
	unsigned int fuww_swath_bytes_howz_wc_c;
	unsigned int fuww_swath_bytes_vewt_wc_w;
	unsigned int fuww_swath_bytes_vewt_wc_c;
	unsigned int DETBuffewSizeFowDCC = nomDETInKByte * 1024;

	unsigned int   yuv420;
	unsigned int   howz_div_w;
	unsigned int   howz_div_c;
	unsigned int   vewt_div_w;
	unsigned int   vewt_div_c;

	unsigned int     swath_buf_size;
	doubwe   detiwe_buf_vp_howz_wimit;
	doubwe   detiwe_buf_vp_vewt_wimit;

	yuv420 = ((SouwcePixewFowmat == dm_420_8 || SouwcePixewFowmat == dm_420_10 ||
			SouwcePixewFowmat == dm_420_12) ? 1 : 0);
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
		detiwe_buf_vp_howz_wimit = (doubwe) swath_buf_size / ((doubwe) WequestHeight256ByteWuma *
				BytePewPixewY / (1 + howz_div_w));
		detiwe_buf_vp_vewt_wimit = (doubwe) swath_buf_size / (256.0 / WequestHeight256ByteWuma /
				(1 + vewt_div_w));
	} ewse {
		swath_buf_size = DETBuffewSizeFowDCC / 2 - 2 * 2 * 256;
		detiwe_buf_vp_howz_wimit = (doubwe) swath_buf_size / ((doubwe) WequestHeight256ByteWuma *
				BytePewPixewY / (1 + howz_div_w) + (doubwe) WequestHeight256ByteChwoma *
				BytePewPixewC / (1 + howz_div_c) / (1 + yuv420));
		detiwe_buf_vp_vewt_wimit = (doubwe) swath_buf_size / (256.0 / WequestHeight256ByteWuma /
				(1 + vewt_div_w) + 256.0 / WequestHeight256ByteChwoma /
				(1 + vewt_div_c) / (1 + yuv420));
	}

	if (SouwcePixewFowmat == dm_420_10) {
		detiwe_buf_vp_howz_wimit = 1.5 * detiwe_buf_vp_howz_wimit;
		detiwe_buf_vp_vewt_wimit = 1.5 * detiwe_buf_vp_vewt_wimit;
	}

	detiwe_buf_vp_howz_wimit = dmw_fwoow(detiwe_buf_vp_howz_wimit - 1, 16);
	detiwe_buf_vp_vewt_wimit = dmw_fwoow(detiwe_buf_vp_vewt_wimit - 1, 16);

	MAS_vp_howz_wimit = SouwcePixewFowmat == dm_wgbe_awpha ? 3840 : 6144;
	MAS_vp_vewt_wimit = SouwcePixewFowmat == dm_wgbe_awpha ? 3840 : (BytePewPixewY == 8 ? 3072 : 6144);
	max_vp_howz_width = dmw_min((doubwe) MAS_vp_howz_wimit, detiwe_buf_vp_howz_wimit);
	max_vp_vewt_height = dmw_min((doubwe) MAS_vp_vewt_wimit, detiwe_buf_vp_vewt_wimit);
	eff_suwf_width_w =  (SuwfaceWidthWuma > max_vp_howz_width ? max_vp_howz_width : SuwfaceWidthWuma);
	eff_suwf_width_c =  eff_suwf_width_w / (1 + yuv420);
	eff_suwf_height_w =  (SuwfaceHeightWuma > max_vp_vewt_height ? max_vp_vewt_height : SuwfaceHeightWuma);
	eff_suwf_height_c =  eff_suwf_height_w / (1 + yuv420);

	fuww_swath_bytes_howz_wc_w = eff_suwf_width_w * WequestHeight256ByteWuma * BytePewPixewY;
	fuww_swath_bytes_vewt_wc_w = eff_suwf_height_w * 256 / WequestHeight256ByteWuma;
	if (BytePewPixewC > 0) {
		fuww_swath_bytes_howz_wc_c = eff_suwf_width_c * WequestHeight256ByteChwoma * BytePewPixewC;
		fuww_swath_bytes_vewt_wc_c = eff_suwf_height_c * 256 / WequestHeight256ByteChwoma;
	} ewse {
		fuww_swath_bytes_howz_wc_c = 0;
		fuww_swath_bytes_vewt_wc_c = 0;
	}

	if (SouwcePixewFowmat == dm_420_10) {
		fuww_swath_bytes_howz_wc_w = dmw_ceiw((doubwe) fuww_swath_bytes_howz_wc_w * 2.0 / 3.0, 256.0);
		fuww_swath_bytes_howz_wc_c = dmw_ceiw((doubwe) fuww_swath_bytes_howz_wc_c * 2.0 / 3.0, 256.0);
		fuww_swath_bytes_vewt_wc_w = dmw_ceiw((doubwe) fuww_swath_bytes_vewt_wc_w * 2.0 / 3.0, 256.0);
		fuww_swath_bytes_vewt_wc_c = dmw_ceiw((doubwe) fuww_swath_bytes_vewt_wc_c * 2.0 / 3.0, 256.0);
	}

	if (2 * fuww_swath_bytes_howz_wc_w + 2 * fuww_swath_bytes_howz_wc_c <= DETBuffewSizeFowDCC) {
		weq128_howz_wc_w = 0;
		weq128_howz_wc_c = 0;
	} ewse if (fuww_swath_bytes_howz_wc_w < 1.5 * fuww_swath_bytes_howz_wc_c && 2 * fuww_swath_bytes_howz_wc_w +
			fuww_swath_bytes_howz_wc_c <= DETBuffewSizeFowDCC) {
		weq128_howz_wc_w = 0;
		weq128_howz_wc_c = 1;
	} ewse if (fuww_swath_bytes_howz_wc_w >= 1.5 * fuww_swath_bytes_howz_wc_c && fuww_swath_bytes_howz_wc_w + 2 *
			fuww_swath_bytes_howz_wc_c <= DETBuffewSizeFowDCC) {
		weq128_howz_wc_w = 1;
		weq128_howz_wc_c = 0;
	} ewse {
		weq128_howz_wc_w = 1;
		weq128_howz_wc_c = 1;
	}

	if (2 * fuww_swath_bytes_vewt_wc_w + 2 * fuww_swath_bytes_vewt_wc_c <= DETBuffewSizeFowDCC) {
		weq128_vewt_wc_w = 0;
		weq128_vewt_wc_c = 0;
	} ewse if (fuww_swath_bytes_vewt_wc_w < 1.5 * fuww_swath_bytes_vewt_wc_c && 2 *
			fuww_swath_bytes_vewt_wc_w + fuww_swath_bytes_vewt_wc_c <= DETBuffewSizeFowDCC) {
		weq128_vewt_wc_w = 0;
		weq128_vewt_wc_c = 1;
	} ewse if (fuww_swath_bytes_vewt_wc_w >= 1.5 * fuww_swath_bytes_vewt_wc_c &&
			fuww_swath_bytes_vewt_wc_w + 2 * fuww_swath_bytes_vewt_wc_c <= DETBuffewSizeFowDCC) {
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
	dmw_pwint("DMW::%s: DCCEnabwed = %d\n", __func__, DCCEnabwed);
	dmw_pwint("DMW::%s: nomDETInKByte = %d\n", __func__, nomDETInKByte);
	dmw_pwint("DMW::%s: DETBuffewSizeFowDCC = %d\n", __func__, DETBuffewSizeFowDCC);
	dmw_pwint("DMW::%s: weq128_howz_wc_w = %d\n", __func__, weq128_howz_wc_w);
	dmw_pwint("DMW::%s: weq128_howz_wc_c = %d\n", __func__, weq128_howz_wc_c);
	dmw_pwint("DMW::%s: fuww_swath_bytes_howz_wc_w = %d\n", __func__, fuww_swath_bytes_howz_wc_w);
	dmw_pwint("DMW::%s: fuww_swath_bytes_vewt_wc_c = %d\n", __func__, fuww_swath_bytes_vewt_wc_c);
	dmw_pwint("DMW::%s: segment_owdew_howz_contiguous_wuma = %d\n", __func__, segment_owdew_howz_contiguous_wuma);
	dmw_pwint("DMW::%s: segment_owdew_howz_contiguous_chwoma = %d\n",
			__func__, segment_owdew_howz_contiguous_chwoma);
#endif

	if (DCCPwogwammingAssumesScanDiwectionUnknown == twue) {
		if (weq128_howz_wc_w == 0 && weq128_vewt_wc_w == 0)
			WequestWuma = WEQ_256Bytes;
		ewse if ((weq128_howz_wc_w == 1 && segment_owdew_howz_contiguous_wuma == 0) ||
				(weq128_vewt_wc_w == 1 && segment_owdew_vewt_contiguous_wuma == 0))
			WequestWuma = WEQ_128BytesNonContiguous;
		ewse
			WequestWuma = WEQ_128BytesContiguous;

		if (weq128_howz_wc_c == 0 && weq128_vewt_wc_c == 0)
			WequestChwoma = WEQ_256Bytes;
		ewse if ((weq128_howz_wc_c == 1 && segment_owdew_howz_contiguous_chwoma == 0) ||
				(weq128_vewt_wc_c == 1 && segment_owdew_vewt_contiguous_chwoma == 0))
			WequestChwoma = WEQ_128BytesNonContiguous;
		ewse
			WequestChwoma = WEQ_128BytesContiguous;

	} ewse if (!IsVewticaw(SouwceWotation)) {
		if (weq128_howz_wc_w == 0)
			WequestWuma = WEQ_256Bytes;
		ewse if (segment_owdew_howz_contiguous_wuma == 0)
			WequestWuma = WEQ_128BytesNonContiguous;
		ewse
			WequestWuma = WEQ_128BytesContiguous;

		if (weq128_howz_wc_c == 0)
			WequestChwoma = WEQ_256Bytes;
		ewse if (segment_owdew_howz_contiguous_chwoma == 0)
			WequestChwoma = WEQ_128BytesNonContiguous;
		ewse
			WequestChwoma = WEQ_128BytesContiguous;

	} ewse {
		if (weq128_vewt_wc_w == 0)
			WequestWuma = WEQ_256Bytes;
		ewse if (segment_owdew_vewt_contiguous_wuma == 0)
			WequestWuma = WEQ_128BytesNonContiguous;
		ewse
			WequestWuma = WEQ_128BytesContiguous;

		if (weq128_vewt_wc_c == 0)
			WequestChwoma = WEQ_256Bytes;
		ewse if (segment_owdew_vewt_contiguous_chwoma == 0)
			WequestChwoma = WEQ_128BytesNonContiguous;
		ewse
			WequestChwoma = WEQ_128BytesContiguous;
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
	dmw_pwint("DMW::%s: MaxUncompwessedBwockWuma = %d\n", __func__, *MaxUncompwessedBwockWuma);
	dmw_pwint("DMW::%s: MaxCompwessedBwockWuma = %d\n", __func__, *MaxCompwessedBwockWuma);
	dmw_pwint("DMW::%s: IndependentBwockWuma = %d\n", __func__, *IndependentBwockWuma);
	dmw_pwint("DMW::%s: MaxUncompwessedBwockChwoma = %d\n", __func__, *MaxUncompwessedBwockChwoma);
	dmw_pwint("DMW::%s: MaxCompwessedBwockChwoma = %d\n", __func__, *MaxCompwessedBwockChwoma);
	dmw_pwint("DMW::%s: IndependentBwockChwoma = %d\n", __func__, *IndependentBwockChwoma);
#endif

} // CawcuwateDCCConfiguwation

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
		boow  *DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE)
{

	boow FoundCwiticawSuwface = fawse;
	unsigned int SwathSizeCwiticawSuwface = 0;
	unsigned int WastChunkOfSwathSize;
	unsigned int MissingPawtOfWastSwathOfDETSize;
	doubwe WastZ8StuttewPewiod = 0.0;
	doubwe WastStuttewPewiod = 0.0;
	unsigned int TotawNumbewOfActiveOTG = 0;
	doubwe doubwePixewCwock;
	unsigned int doubweHTotaw;
	unsigned int doubweVTotaw;
	boow SameTiming = twue;
	doubwe DETBuffewingTimeY;
	doubwe SwathWidthYCwiticawSuwface = 0.0;
	doubwe SwathHeightYCwiticawSuwface = 0.0;
	doubwe VActiveTimeCwiticawSuwface = 0.0;
	doubwe FwameTimeCwiticawSuwface = 0.0;
	unsigned int BytePewPixewYCwiticawSuwface = 0;
	doubwe WinesToFinishSwathTwansfewStuttewCwiticawSuwface = 0.0;
	unsigned int DETBuffewSizeYCwiticawSuwface = 0;
	doubwe MinTTUVBwankCwiticawSuwface = 0.0;
	unsigned int BwockWidth256BytesYCwiticawSuwface = 0;
	boow doubwePwaneCwiticawSuwface = 0;
	boow doubwePipeCwiticawSuwface = 0;
	doubwe TotawCompwessedWeadBandwidth;
	doubwe TotawWowWeadBandwidth;
	doubwe AvewageDCCCompwessionWate;
	doubwe EffectiveCompwessedBuffewSize;
	doubwe PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew;
	doubwe StuttewBuwstTime;
	unsigned int TotawActiveWwiteback;
	doubwe WinesInDETY;
	doubwe WinesInDETYWoundedDownToSwath;
	doubwe MaximumEffectiveCompwessionWuma;
	doubwe MaximumEffectiveCompwessionChwoma;
	doubwe TotawZewoSizeWequestWeadBandwidth;
	doubwe TotawZewoSizeCompwessedWeadBandwidth;
	doubwe AvewageDCCZewoSizeFwaction;
	doubwe AvewageZewoSizeCompwessionWate;
	unsigned int k;

	TotawZewoSizeWequestWeadBandwidth = 0;
	TotawZewoSizeCompwessedWeadBandwidth = 0;
	TotawWowWeadBandwidth = 0;
	TotawCompwessedWeadBandwidth = 0;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (UseMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) {
			if (DCCEnabwe[k] == twue) {
				if ((IsVewticaw(SouwceWotation[k]) && BwockWidth256BytesY[k] > SwathHeightY[k])
						|| (!IsVewticaw(SouwceWotation[k])
								&& BwockHeight256BytesY[k] > SwathHeightY[k])
						|| DCCYMaxUncompwessedBwock[k] < 256) {
					MaximumEffectiveCompwessionWuma = 2;
				} ewse {
					MaximumEffectiveCompwessionWuma = 4;
				}
				TotawCompwessedWeadBandwidth = TotawCompwessedWeadBandwidth
						+ WeadBandwidthSuwfaceWuma[k]
								/ dmw_min(NetDCCWateWuma[k],
										MaximumEffectiveCompwessionWuma);
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%0d, WeadBandwidthSuwfaceWuma = %f\n",
						__func__, k, WeadBandwidthSuwfaceWuma[k]);
				dmw_pwint("DMW::%s: k=%0d, NetDCCWateWuma = %f\n",
						__func__, k, NetDCCWateWuma[k]);
				dmw_pwint("DMW::%s: k=%0d, MaximumEffectiveCompwessionWuma = %f\n",
						__func__, k, MaximumEffectiveCompwessionWuma);
#endif
				TotawZewoSizeWequestWeadBandwidth = TotawZewoSizeWequestWeadBandwidth
						+ WeadBandwidthSuwfaceWuma[k] * DCCFwactionOfZewoSizeWequestsWuma[k];
				TotawZewoSizeCompwessedWeadBandwidth = TotawZewoSizeCompwessedWeadBandwidth
						+ WeadBandwidthSuwfaceWuma[k] * DCCFwactionOfZewoSizeWequestsWuma[k]
								/ MaximumEffectiveCompwessionWuma;

				if (WeadBandwidthSuwfaceChwoma[k] > 0) {
					if ((IsVewticaw(SouwceWotation[k]) && BwockWidth256BytesC[k] > SwathHeightC[k])
							|| (!IsVewticaw(SouwceWotation[k])
									&& BwockHeight256BytesC[k] > SwathHeightC[k])
							|| DCCCMaxUncompwessedBwock[k] < 256) {
						MaximumEffectiveCompwessionChwoma = 2;
					} ewse {
						MaximumEffectiveCompwessionChwoma = 4;
					}
					TotawCompwessedWeadBandwidth =
							TotawCompwessedWeadBandwidth
							+ WeadBandwidthSuwfaceChwoma[k]
							/ dmw_min(NetDCCWateChwoma[k],
							MaximumEffectiveCompwessionChwoma);
#ifdef __DMW_VBA_DEBUG__
					dmw_pwint("DMW::%s: k=%0d, WeadBandwidthSuwfaceChwoma = %f\n",
							__func__, k, WeadBandwidthSuwfaceChwoma[k]);
					dmw_pwint("DMW::%s: k=%0d, NetDCCWateChwoma = %f\n",
							__func__, k, NetDCCWateChwoma[k]);
					dmw_pwint("DMW::%s: k=%0d, MaximumEffectiveCompwessionChwoma = %f\n",
							__func__, k, MaximumEffectiveCompwessionChwoma);
#endif
					TotawZewoSizeWequestWeadBandwidth = TotawZewoSizeWequestWeadBandwidth
							+ WeadBandwidthSuwfaceChwoma[k]
									* DCCFwactionOfZewoSizeWequestsChwoma[k];
					TotawZewoSizeCompwessedWeadBandwidth = TotawZewoSizeCompwessedWeadBandwidth
							+ WeadBandwidthSuwfaceChwoma[k]
									* DCCFwactionOfZewoSizeWequestsChwoma[k]
									/ MaximumEffectiveCompwessionChwoma;
				}
			} ewse {
				TotawCompwessedWeadBandwidth = TotawCompwessedWeadBandwidth
						+ WeadBandwidthSuwfaceWuma[k] + WeadBandwidthSuwfaceChwoma[k];
			}
			TotawWowWeadBandwidth = TotawWowWeadBandwidth
					+ DPPPewSuwface[k] * (meta_wow_bw[k] + dpte_wow_bw[k]);
		}
	}

	AvewageDCCCompwessionWate = TotawDataWeadBandwidth / TotawCompwessedWeadBandwidth;
	AvewageDCCZewoSizeFwaction = TotawZewoSizeWequestWeadBandwidth / TotawDataWeadBandwidth;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: UnboundedWequestEnabwed = %d\n", __func__, UnboundedWequestEnabwed);
	dmw_pwint("DMW::%s: TotawCompwessedWeadBandwidth = %f\n", __func__, TotawCompwessedWeadBandwidth);
	dmw_pwint("DMW::%s: TotawZewoSizeWequestWeadBandwidth = %f\n", __func__, TotawZewoSizeWequestWeadBandwidth);
	dmw_pwint("DMW::%s: TotawZewoSizeCompwessedWeadBandwidth = %f\n",
			__func__, TotawZewoSizeCompwessedWeadBandwidth);
	dmw_pwint("DMW::%s: MaximumEffectiveCompwessionWuma = %f\n", __func__, MaximumEffectiveCompwessionWuma);
	dmw_pwint("DMW::%s: MaximumEffectiveCompwessionChwoma = %f\n", __func__, MaximumEffectiveCompwessionChwoma);
	dmw_pwint("DMW::%s: AvewageDCCCompwessionWate = %f\n", __func__, AvewageDCCCompwessionWate);
	dmw_pwint("DMW::%s: AvewageDCCZewoSizeFwaction = %f\n", __func__, AvewageDCCZewoSizeFwaction);
	dmw_pwint("DMW::%s: CompbufWesewvedSpace64B = %d\n", __func__, CompbufWesewvedSpace64B);
	dmw_pwint("DMW::%s: CompbufWesewvedSpaceZs = %d\n", __func__, CompbufWesewvedSpaceZs);
	dmw_pwint("DMW::%s: CompwessedBuffewSizeInkByte = %d\n", __func__, CompwessedBuffewSizeInkByte);
#endif
	if (AvewageDCCZewoSizeFwaction == 1) {
		AvewageZewoSizeCompwessionWate = TotawZewoSizeWequestWeadBandwidth
				/ TotawZewoSizeCompwessedWeadBandwidth;
		EffectiveCompwessedBuffewSize = (doubwe) MetaFIFOSizeInKEntwies * 1024 * 64
				* AvewageZewoSizeCompwessionWate
				+ ((doubwe) ZewoSizeBuffewEntwies - CompbufWesewvedSpaceZs) * 64
						* AvewageZewoSizeCompwessionWate;
	} ewse if (AvewageDCCZewoSizeFwaction > 0) {
		AvewageZewoSizeCompwessionWate = TotawZewoSizeWequestWeadBandwidth
				/ TotawZewoSizeCompwessedWeadBandwidth;
		EffectiveCompwessedBuffewSize = dmw_min(
				(doubwe) CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate,
				(doubwe) MetaFIFOSizeInKEntwies * 1024 * 64
					/ (AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate
					+ 1 / AvewageDCCCompwessionWate))
					+ dmw_min(((doubwe) WOBBuffewSizeInKByte * 1024 - CompbufWesewvedSpace64B * 64)
					* AvewageDCCCompwessionWate,
					((doubwe) ZewoSizeBuffewEntwies - CompbufWesewvedSpaceZs) * 64
					/ (AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate));

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: min 1 = %f\n", __func__,
				CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate);
		dmw_pwint("DMW::%s: min 2 = %f\n", __func__, MetaFIFOSizeInKEntwies * 1024 * 64 /
				(AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate + 1 /
						AvewageDCCCompwessionWate));
		dmw_pwint("DMW::%s: min 3 = %f\n", __func__, (WOBBuffewSizeInKByte * 1024 -
				CompbufWesewvedSpace64B * 64) * AvewageDCCCompwessionWate);
		dmw_pwint("DMW::%s: min 4 = %f\n", __func__, (ZewoSizeBuffewEntwies - CompbufWesewvedSpaceZs) * 64 /
				(AvewageDCCZewoSizeFwaction / AvewageZewoSizeCompwessionWate));
#endif
	} ewse {
		EffectiveCompwessedBuffewSize = dmw_min(
				(doubwe) CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate,
				(doubwe) MetaFIFOSizeInKEntwies * 1024 * 64 * AvewageDCCCompwessionWate)
				+ ((doubwe) WOBBuffewSizeInKByte * 1024 - CompbufWesewvedSpace64B * 64)
						* AvewageDCCCompwessionWate;

#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: min 1 = %f\n", __func__,
				CompwessedBuffewSizeInkByte * 1024 * AvewageDCCCompwessionWate);
		dmw_pwint("DMW::%s: min 2 = %f\n", __func__,
				MetaFIFOSizeInKEntwies * 1024 * 64 * AvewageDCCCompwessionWate);
#endif
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: MetaFIFOSizeInKEntwies = %d\n", __func__, MetaFIFOSizeInKEntwies);
	dmw_pwint("DMW::%s: AvewageZewoSizeCompwessionWate = %f\n", __func__, AvewageZewoSizeCompwessionWate);
	dmw_pwint("DMW::%s: EffectiveCompwessedBuffewSize = %f\n", __func__, EffectiveCompwessedBuffewSize);
#endif

	*StuttewPewiod = 0;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (UseMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) {
			WinesInDETY = ((doubwe) DETBuffewSizeY[k]
					+ (UnboundedWequestEnabwed == twue ? EffectiveCompwessedBuffewSize : 0)
							* WeadBandwidthSuwfaceWuma[k] / TotawDataWeadBandwidth)
					/ BytePewPixewDETY[k] / SwathWidthY[k];
			WinesInDETYWoundedDownToSwath = dmw_fwoow(WinesInDETY, SwathHeightY[k]);
			DETBuffewingTimeY = WinesInDETYWoundedDownToSwath * ((doubwe) HTotaw[k] / PixewCwock[k])
					/ VWatio[k];
#ifdef __DMW_VBA_DEBUG__
			dmw_pwint("DMW::%s: k=%0d, DETBuffewSizeY = %d\n", __func__, k, DETBuffewSizeY[k]);
			dmw_pwint("DMW::%s: k=%0d, BytePewPixewDETY = %f\n", __func__, k, BytePewPixewDETY[k]);
			dmw_pwint("DMW::%s: k=%0d, SwathWidthY = %d\n", __func__, k, SwathWidthY[k]);
			dmw_pwint("DMW::%s: k=%0d, WeadBandwidthSuwfaceWuma = %f\n",
					__func__, k, WeadBandwidthSuwfaceWuma[k]);
			dmw_pwint("DMW::%s: k=%0d, TotawDataWeadBandwidth = %f\n", __func__, k, TotawDataWeadBandwidth);
			dmw_pwint("DMW::%s: k=%0d, WinesInDETY = %f\n", __func__, k, WinesInDETY);
			dmw_pwint("DMW::%s: k=%0d, WinesInDETYWoundedDownToSwath = %f\n",
					__func__, k, WinesInDETYWoundedDownToSwath);
			dmw_pwint("DMW::%s: k=%0d, HTotaw = %d\n", __func__, k, HTotaw[k]);
			dmw_pwint("DMW::%s: k=%0d, PixewCwock = %f\n", __func__, k, PixewCwock[k]);
			dmw_pwint("DMW::%s: k=%0d, VWatio = %f\n", __func__, k, VWatio[k]);
			dmw_pwint("DMW::%s: k=%0d, DETBuffewingTimeY = %f\n", __func__, k, DETBuffewingTimeY);
			dmw_pwint("DMW::%s: k=%0d, PixewCwock = %f\n", __func__, k, PixewCwock[k]);
#endif

			if (!FoundCwiticawSuwface || DETBuffewingTimeY < *StuttewPewiod) {
				boow isIntewwaceTiming = Intewwace[k] && !PwogwessiveToIntewwaceUnitInOPP;

				FoundCwiticawSuwface = twue;
				*StuttewPewiod = DETBuffewingTimeY;
				FwameTimeCwiticawSuwface = (
						isIntewwaceTiming ?
								dmw_fwoow((doubwe) VTotaw[k] / 2.0, 1.0) : VTotaw[k])
						* (doubwe) HTotaw[k] / PixewCwock[k];
				VActiveTimeCwiticawSuwface = (
						isIntewwaceTiming ?
								dmw_fwoow((doubwe) VActive[k] / 2.0, 1.0) : VActive[k])
						* (doubwe) HTotaw[k] / PixewCwock[k];
				BytePewPixewYCwiticawSuwface = BytePewPixewY[k];
				SwathWidthYCwiticawSuwface = SwathWidthY[k];
				SwathHeightYCwiticawSuwface = SwathHeightY[k];
				BwockWidth256BytesYCwiticawSuwface = BwockWidth256BytesY[k];
				WinesToFinishSwathTwansfewStuttewCwiticawSuwface = SwathHeightY[k]
						- (WinesInDETY - WinesInDETYWoundedDownToSwath);
				DETBuffewSizeYCwiticawSuwface = DETBuffewSizeY[k];
				MinTTUVBwankCwiticawSuwface = MinTTUVBwank[k];
				doubwePwaneCwiticawSuwface = (WeadBandwidthSuwfaceChwoma[k] == 0);
				doubwePipeCwiticawSuwface = (DPPPewSuwface[k] == 1);

#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW::%s: k=%0d, FoundCwiticawSuwface                = %d\n",
						__func__, k, FoundCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, StuttewPewiod                       = %f\n",
						__func__, k, *StuttewPewiod);
				dmw_pwint("DMW::%s: k=%0d, MinTTUVBwankCwiticawSuwface         = %f\n",
						__func__, k, MinTTUVBwankCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, FwameTimeCwiticawSuwface            = %f\n",
						__func__, k, FwameTimeCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, VActiveTimeCwiticawSuwface          = %f\n",
						__func__, k, VActiveTimeCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, BytePewPixewYCwiticawSuwface        = %d\n",
						__func__, k, BytePewPixewYCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, SwathWidthYCwiticawSuwface          = %f\n",
						__func__, k, SwathWidthYCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, SwathHeightYCwiticawSuwface         = %f\n",
						__func__, k, SwathHeightYCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, BwockWidth256BytesYCwiticawSuwface  = %d\n",
						__func__, k, BwockWidth256BytesYCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, doubwePwaneCwiticawSuwface          = %d\n",
						__func__, k, doubwePwaneCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, doubwePipeCwiticawSuwface           = %d\n",
						__func__, k, doubwePipeCwiticawSuwface);
				dmw_pwint("DMW::%s: k=%0d, WinesToFinishSwathTwansfewStuttewCwiticawSuwface = %f\n",
						__func__, k, WinesToFinishSwathTwansfewStuttewCwiticawSuwface);
#endif
			}
		}
	}

	PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew = dmw_min(*StuttewPewiod * TotawDataWeadBandwidth,
			EffectiveCompwessedBuffewSize);
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WOBBuffewSizeInKByte = %d\n", __func__, WOBBuffewSizeInKByte);
	dmw_pwint("DMW::%s: AvewageDCCCompwessionWate = %f\n", __func__, AvewageDCCCompwessionWate);
	dmw_pwint("DMW::%s: StuttewPewiod * TotawDataWeadBandwidth = %f\n",
			__func__, *StuttewPewiod * TotawDataWeadBandwidth);
	dmw_pwint("DMW::%s: EffectiveCompwessedBuffewSize = %f\n", __func__, EffectiveCompwessedBuffewSize);
	dmw_pwint("DMW::%s: PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew = %f\n", __func__,
			PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew);
	dmw_pwint("DMW::%s: WetuwnBW = %f\n", __func__, WetuwnBW);
	dmw_pwint("DMW::%s: TotawDataWeadBandwidth = %f\n", __func__, TotawDataWeadBandwidth);
	dmw_pwint("DMW::%s: TotawWowWeadBandwidth = %f\n", __func__, TotawWowWeadBandwidth);
	dmw_pwint("DMW::%s: DCFCWK = %f\n", __func__, DCFCWK);
#endif

	StuttewBuwstTime = PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew / AvewageDCCCompwessionWate
			/ WetuwnBW
			+ (*StuttewPewiod * TotawDataWeadBandwidth
					- PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew) / (DCFCWK * 64)
			+ *StuttewPewiod * TotawWowWeadBandwidth / WetuwnBW;
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: Pawt 1 = %f\n", __func__, PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew /
			AvewageDCCCompwessionWate / WetuwnBW);
	dmw_pwint("DMW::%s: StuttewPewiod * TotawDataWeadBandwidth = %f\n",
			__func__, (*StuttewPewiod * TotawDataWeadBandwidth));
	dmw_pwint("DMW::%s: Pawt 2 = %f\n", __func__, (*StuttewPewiod * TotawDataWeadBandwidth -
			PawtOfUncompwessedPixewBuwstThatFitsInWOBAndCompwessedBuffew) / (DCFCWK * 64));
	dmw_pwint("DMW::%s: Pawt 3 = %f\n", __func__, *StuttewPewiod * TotawWowWeadBandwidth / WetuwnBW);
	dmw_pwint("DMW::%s: StuttewBuwstTime = %f\n", __func__, StuttewBuwstTime);
#endif
	StuttewBuwstTime = dmw_max(StuttewBuwstTime,
			WinesToFinishSwathTwansfewStuttewCwiticawSuwface * BytePewPixewYCwiticawSuwface
					* SwathWidthYCwiticawSuwface / WetuwnBW);

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: Time to finish wesidue swath=%f\n",
			__func__,
			WinesToFinishSwathTwansfewStuttewCwiticawSuwface *
			BytePewPixewYCwiticawSuwface * SwathWidthYCwiticawSuwface / WetuwnBW);
#endif

	TotawActiveWwiteback = 0;
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (WwitebackEnabwe[k])
			TotawActiveWwiteback = TotawActiveWwiteback + 1;
	}

	if (TotawActiveWwiteback == 0) {
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: SWExitTime = %f\n", __func__, SWExitTime);
		dmw_pwint("DMW::%s: SWExitZ8Time = %f\n", __func__, SWExitZ8Time);
		dmw_pwint("DMW::%s: StuttewBuwstTime = %f (finaw)\n", __func__, StuttewBuwstTime);
		dmw_pwint("DMW::%s: StuttewPewiod = %f\n", __func__, *StuttewPewiod);
#endif
		*StuttewEfficiencyNotIncwudingVBwank = dmw_max(0.,
				1 - (SWExitTime + StuttewBuwstTime) / *StuttewPewiod) * 100;
		*Z8StuttewEfficiencyNotIncwudingVBwank = dmw_max(0.,
				1 - (SWExitZ8Time + StuttewBuwstTime) / *StuttewPewiod) * 100;
		*NumbewOfStuttewBuwstsPewFwame = (
				*StuttewEfficiencyNotIncwudingVBwank > 0 ?
						dmw_ceiw(VActiveTimeCwiticawSuwface / *StuttewPewiod, 1) : 0);
		*Z8NumbewOfStuttewBuwstsPewFwame = (
				*Z8StuttewEfficiencyNotIncwudingVBwank > 0 ?
						dmw_ceiw(VActiveTimeCwiticawSuwface / *StuttewPewiod, 1) : 0);
	} ewse {
		*StuttewEfficiencyNotIncwudingVBwank = 0.;
		*Z8StuttewEfficiencyNotIncwudingVBwank = 0.;
		*NumbewOfStuttewBuwstsPewFwame = 0;
		*Z8NumbewOfStuttewBuwstsPewFwame = 0;
	}
#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: VActiveTimeCwiticawSuwface = %f\n", __func__, VActiveTimeCwiticawSuwface);
	dmw_pwint("DMW::%s: StuttewEfficiencyNotIncwudingVBwank = %f\n",
			__func__, *StuttewEfficiencyNotIncwudingVBwank);
	dmw_pwint("DMW::%s: Z8StuttewEfficiencyNotIncwudingVBwank = %f\n",
			__func__, *Z8StuttewEfficiencyNotIncwudingVBwank);
	dmw_pwint("DMW::%s: NumbewOfStuttewBuwstsPewFwame = %d\n", __func__, *NumbewOfStuttewBuwstsPewFwame);
	dmw_pwint("DMW::%s: Z8NumbewOfStuttewBuwstsPewFwame = %d\n", __func__, *Z8NumbewOfStuttewBuwstsPewFwame);
#endif

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (UseMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) {
			if (BwendingAndTiming[k] == k) {
				if (TotawNumbewOfActiveOTG == 0) {
					doubwePixewCwock = PixewCwock[k];
					doubweHTotaw = HTotaw[k];
					doubweVTotaw = VTotaw[k];
				} ewse if (doubwePixewCwock != PixewCwock[k] || doubweHTotaw != HTotaw[k]
						|| doubweVTotaw != VTotaw[k]) {
					SameTiming = fawse;
				}
				TotawNumbewOfActiveOTG = TotawNumbewOfActiveOTG + 1;
			}
		}
	}

	if (*StuttewEfficiencyNotIncwudingVBwank > 0) {
		WastStuttewPewiod = VActiveTimeCwiticawSuwface - (*NumbewOfStuttewBuwstsPewFwame - 1) * *StuttewPewiod;

		if ((SynchwonizeTimingsFinaw || TotawNumbewOfActiveOTG == 1) && SameTiming
				&& WastStuttewPewiod + MinTTUVBwankCwiticawSuwface > StuttewEntewPwusExitWatewmawk) {
			*StuttewEfficiency = (1 - (*NumbewOfStuttewBuwstsPewFwame * SWExitTime
						+ StuttewBuwstTime * VActiveTimeCwiticawSuwface
						/ *StuttewPewiod) / FwameTimeCwiticawSuwface) * 100;
		} ewse {
			*StuttewEfficiency = *StuttewEfficiencyNotIncwudingVBwank;
		}
	} ewse {
		*StuttewEfficiency = 0;
	}

	if (*Z8StuttewEfficiencyNotIncwudingVBwank > 0) {
		WastZ8StuttewPewiod = VActiveTimeCwiticawSuwface
				- (*NumbewOfStuttewBuwstsPewFwame - 1) * *StuttewPewiod;
		if ((SynchwonizeTimingsFinaw || TotawNumbewOfActiveOTG == 1) && SameTiming && WastZ8StuttewPewiod +
				MinTTUVBwankCwiticawSuwface > Z8StuttewEntewPwusExitWatewmawk) {
			*Z8StuttewEfficiency = (1 - (*NumbewOfStuttewBuwstsPewFwame * SWExitZ8Time + StuttewBuwstTime
				* VActiveTimeCwiticawSuwface / *StuttewPewiod) / FwameTimeCwiticawSuwface) * 100;
		} ewse {
			*Z8StuttewEfficiency = *Z8StuttewEfficiencyNotIncwudingVBwank;
		}
	} ewse {
		*Z8StuttewEfficiency = 0.;
	}

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: WastZ8StuttewPewiod = %f\n", __func__, WastZ8StuttewPewiod);
	dmw_pwint("DMW::%s: Z8StuttewEntewPwusExitWatewmawk = %f\n", __func__, Z8StuttewEntewPwusExitWatewmawk);
	dmw_pwint("DMW::%s: StuttewBuwstTime = %f\n", __func__, StuttewBuwstTime);
	dmw_pwint("DMW::%s: StuttewPewiod = %f\n", __func__, *StuttewPewiod);
	dmw_pwint("DMW::%s: StuttewEfficiency = %f\n", __func__, *StuttewEfficiency);
	dmw_pwint("DMW::%s: Z8StuttewEfficiency = %f\n", __func__, *Z8StuttewEfficiency);
	dmw_pwint("DMW::%s: StuttewEfficiencyNotIncwudingVBwank = %f\n",
			__func__, *StuttewEfficiencyNotIncwudingVBwank);
	dmw_pwint("DMW::%s: Z8NumbewOfStuttewBuwstsPewFwame = %d\n", __func__, *Z8NumbewOfStuttewBuwstsPewFwame);
#endif

	SwathSizeCwiticawSuwface = BytePewPixewYCwiticawSuwface * SwathHeightYCwiticawSuwface
			* dmw_ceiw(SwathWidthYCwiticawSuwface, BwockWidth256BytesYCwiticawSuwface);
	WastChunkOfSwathSize = SwathSizeCwiticawSuwface % (PixewChunkSizeInKByte * 1024);
	MissingPawtOfWastSwathOfDETSize = dmw_ceiw(DETBuffewSizeYCwiticawSuwface, SwathSizeCwiticawSuwface)
			- DETBuffewSizeYCwiticawSuwface;

	*DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE = !(!UnboundedWequestEnabwed && (NumbewOfActiveSuwfaces == 1)
			&& doubwePwaneCwiticawSuwface && doubwePipeCwiticawSuwface && (WastChunkOfSwathSize > 0)
			&& (WastChunkOfSwathSize <= 4096) && (MissingPawtOfWastSwathOfDETSize > 0)
			&& (MissingPawtOfWastSwathOfDETSize <= WastChunkOfSwathSize));

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: SwathSizeCwiticawSuwface = %d\n", __func__, SwathSizeCwiticawSuwface);
	dmw_pwint("DMW::%s: WastChunkOfSwathSize = %d\n", __func__, WastChunkOfSwathSize);
	dmw_pwint("DMW::%s: MissingPawtOfWastSwathOfDETSize = %d\n", __func__, MissingPawtOfWastSwathOfDETSize);
	dmw_pwint("DMW::%s: DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE = %d\n", __func__, *DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE);
#endif
} // CawcuwateStuttewEfficiency

void dmw32_CawcuwateMaxDETAndMinCompwessedBuffewSize(
		unsigned int    ConfigWetuwnBuffewSizeInKByte,
		unsigned int    WOBBuffewSizeInKByte,
		unsigned int MaxNumDPP,
		boow nomDETInKByteOvewwideEnabwe, // VBA_DEWTA, awwow DV to ovewwide defauwt DET size
		unsigned int nomDETInKByteOvewwideVawue,  // VBA_DEWTA

		/* Output */
		unsigned int *MaxTotawDETInKByte,
		unsigned int *nomDETInKByte,
		unsigned int *MinCompwessedBuffewSizeInKByte)
{
	boow     det_buff_size_ovewwide_en  = nomDETInKByteOvewwideEnabwe;
	unsigned int        det_buff_size_ovewwide_vaw = nomDETInKByteOvewwideVawue;

	*MaxTotawDETInKByte = dmw_ceiw(((doubwe)ConfigWetuwnBuffewSizeInKByte +
			(doubwe) WOBBuffewSizeInKByte) * 4.0 / 5.0, 64);
	*nomDETInKByte = dmw_fwoow((doubwe) *MaxTotawDETInKByte / (doubwe) MaxNumDPP, 64);
	*MinCompwessedBuffewSizeInKByte = ConfigWetuwnBuffewSizeInKByte - *MaxTotawDETInKByte;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW::%s: ConfigWetuwnBuffewSizeInKByte = %0d\n", __func__, ConfigWetuwnBuffewSizeInKByte);
	dmw_pwint("DMW::%s: WOBBuffewSizeInKByte = %0d\n", __func__, WOBBuffewSizeInKByte);
	dmw_pwint("DMW::%s: MaxNumDPP = %0d\n", __func__, MaxNumDPP);
	dmw_pwint("DMW::%s: MaxTotawDETInKByte = %0d\n", __func__, *MaxTotawDETInKByte);
	dmw_pwint("DMW::%s: nomDETInKByte = %0d\n", __func__, *nomDETInKByte);
	dmw_pwint("DMW::%s: MinCompwessedBuffewSizeInKByte = %0d\n", __func__, *MinCompwessedBuffewSizeInKByte);
#endif

	if (det_buff_size_ovewwide_en) {
		*nomDETInKByte = det_buff_size_ovewwide_vaw;
#ifdef __DMW_VBA_DEBUG__
		dmw_pwint("DMW::%s: nomDETInKByte = %0d (ovewwide)\n", __func__, *nomDETInKByte);
#endif
	}
} // CawcuwateMaxDETAndMinCompwessedBuffewSize

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
		doubwe UwgentBuwstFactowCuwsow[])
{
	unsigned int k;
	boow NotEnoughUwgentWatencyHiding = fawse;
	boow CawcuwateVActiveBandwithSuppowt_vaw = fawse;
	doubwe VActiveBandwith = 0;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (NotUwgentWatencyHiding[k]) {
			NotEnoughUwgentWatencyHiding = twue;
		}
	}

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		VActiveBandwith = VActiveBandwith + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k] + NumbewOfDPP[k] * meta_wow_bandwidth[k] + NumbewOfDPP[k] * dpte_wow_bandwidth[k];
	}

	CawcuwateVActiveBandwithSuppowt_vaw = (VActiveBandwith <= WetuwnBW) && !NotEnoughUwgentWatencyHiding;

#ifdef __DMW_VBA_DEBUG__
dmw_pwint("DMW::%s: NotEnoughUwgentWatencyHiding        = %d\n", __func__, NotEnoughUwgentWatencyHiding);
dmw_pwint("DMW::%s: VActiveBandwith                     = %f\n", __func__, VActiveBandwith);
dmw_pwint("DMW::%s: WetuwnBW                            = %f\n", __func__, WetuwnBW);
dmw_pwint("DMW::%s: CawcuwateVActiveBandwithSuppowt_vaw = %d\n", __func__, CawcuwateVActiveBandwithSuppowt_vaw);
#endif
	wetuwn CawcuwateVActiveBandwithSuppowt_vaw;
}

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
		boow *PwefetchBandwidthSuppowt)
{
	unsigned int k;
	doubwe ActiveBandwidthPewSuwface;
	boow NotEnoughUwgentWatencyHiding = fawse;
	doubwe TotawActiveBandwidth = 0;
	doubwe TotawPwefetchBandwidth = 0;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (NotUwgentWatencyHiding[k]) {
			NotEnoughUwgentWatencyHiding = twue;
		}
	}

	*MaxPwefetchBandwidth = 0;
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		ActiveBandwidthPewSuwface = WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k] + NumbewOfDPP[k] * (meta_wow_bandwidth[k] + dpte_wow_bandwidth[k]);

		TotawActiveBandwidth += ActiveBandwidthPewSuwface;

		TotawPwefetchBandwidth = TotawPwefetchBandwidth + PwefetchBW[k] * VWatio[k];

		*MaxPwefetchBandwidth = *MaxPwefetchBandwidth + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
				ActiveBandwidthPewSuwface,
				NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
	}

	if (MaxVWatioPwe == __DMW_MAX_VWATIO_PWE__)
		*PwefetchBandwidthSuppowt = (*MaxPwefetchBandwidth <= WetuwnBW) && (TotawPwefetchBandwidth <= TotawActiveBandwidth * __DMW_MAX_BW_WATIO_PWE__) && !NotEnoughUwgentWatencyHiding;
	ewse
		*PwefetchBandwidthSuppowt = (*MaxPwefetchBandwidth <= WetuwnBW) && !NotEnoughUwgentWatencyHiding;

	*FwactionOfUwgentBandwidth = *MaxPwefetchBandwidth / WetuwnBW;
}

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
		doubwe UwgentBuwstFactowCuwsowPwe[])
{
	unsigned int k;
	doubwe CawcuwateBandwidthAvaiwabweFowImmediateFwip_vaw = WetuwnBW;

	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		CawcuwateBandwidthAvaiwabweFowImmediateFwip_vaw = CawcuwateBandwidthAvaiwabweFowImmediateFwip_vaw - dmw_max(WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
				NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
	}

	wetuwn CawcuwateBandwidthAvaiwabweFowImmediateFwip_vaw;
}

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
		boow *ImmediateFwipBandwidthSuppowt)
{
	unsigned int k;
	*TotawBandwidth = 0;
	fow (k = 0; k < NumbewOfActiveSuwfaces; ++k) {
		if (ImmediateFwipWequiwement[k] != dm_immediate_fwip_not_wequiwed) {
			*TotawBandwidth = *TotawBandwidth + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
					NumbewOfDPP[k] * finaw_fwip_bw[k] + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
					NumbewOfDPP[k] * (finaw_fwip_bw[k] + PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
		} ewse {
			*TotawBandwidth = *TotawBandwidth + dmw_max3(NumbewOfDPP[k] * pwefetch_vmwow_bw[k],
					NumbewOfDPP[k] * (meta_wow_bandwidth[k] + dpte_wow_bandwidth[k]) + WeadBandwidthWuma[k] * UwgentBuwstFactowWuma[k] + WeadBandwidthChwoma[k] * UwgentBuwstFactowChwoma[k] + cuwsow_bw[k] * UwgentBuwstFactowCuwsow[k],
					NumbewOfDPP[k] * (PwefetchBandwidthWuma[k] * UwgentBuwstFactowWumaPwe[k] + PwefetchBandwidthChwoma[k] * UwgentBuwstFactowChwomaPwe[k]) + cuwsow_bw_pwe[k] * UwgentBuwstFactowCuwsowPwe[k]);
		}
	}
	*ImmediateFwipBandwidthSuppowt = (*TotawBandwidth <= WetuwnBW);
	*FwactionOfUwgentBandwidth = *TotawBandwidth / WetuwnBW;
}

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
		enum unbounded_wequesting_powicy UseUnboundedWequesting)
{
	int k;
	doubwe SwathSizeAwwSuwfaces = 0;
	doubwe SwathSizeAwwSuwfacesInFetchTimeUs;
	doubwe DETSwathWatencyHidingUs;
	doubwe DETSwathWatencyHidingYUs;
	doubwe DETSwathWatencyHidingCUs;
	doubwe SwathSizePewSuwfaceY[DC__NUM_DPP__MAX];
	doubwe SwathSizePewSuwfaceC[DC__NUM_DPP__MAX];
	boow NotEnoughDETSwathFiwwWatencyHiding = fawse;

	if (UseUnboundedWequesting == dm_unbounded_wequesting)
		wetuwn fawse;

	/* cawcuwate sum of singwe swath size fow aww pipes in bytes */
	fow (k = 0; k < NumbewOfActiveSuwfaces; k++) {
		SwathSizePewSuwfaceY[k] = SwathHeightY[k] * SwathWidthY[k] * BytePewPixewInDETY[k] * NumOfDPP[k];

		if (SwathHeightC[k] != 0)
			SwathSizePewSuwfaceC[k] = SwathHeightC[k] * SwathWidthC[k] * BytePewPixewInDETC[k] * NumOfDPP[k];
		ewse
			SwathSizePewSuwfaceC[k] = 0;

		SwathSizeAwwSuwfaces += SwathSizePewSuwfaceY[k] + SwathSizePewSuwfaceC[k];
	}

	SwathSizeAwwSuwfacesInFetchTimeUs = SwathSizeAwwSuwfaces / WetuwnBW + UwgentWatency;

	/* ensuwe aww DET - 1 swath can hide a fetch fow aww suwfaces */
	fow (k = 0; k < NumbewOfActiveSuwfaces; k++) {
		doubwe WineTime = HTotaw[k] / PixewCwock[k];

		/* onwy cawe if suwface is not phantom */
		if (UsesMAWWFowPStateChange[k] != dm_use_maww_pstate_change_phantom_pipe) {
			DETSwathWatencyHidingYUs = (dmw_fwoow(DETBuffewSizeY[k] / BytePewPixewInDETY[k] / SwathWidthY[k], 1.0) - SwathHeightY[k]) / VWatioY[k] * WineTime;

			if (SwathHeightC[k] != 0) {
				DETSwathWatencyHidingCUs = (dmw_fwoow(DETBuffewSizeC[k] / BytePewPixewInDETC[k] / SwathWidthC[k], 1.0) - SwathHeightC[k]) / VWatioC[k] * WineTime;

				DETSwathWatencyHidingUs = dmw_min(DETSwathWatencyHidingYUs, DETSwathWatencyHidingCUs);
			} ewse {
				DETSwathWatencyHidingUs = DETSwathWatencyHidingYUs;
			}

			/* DET must be abwe to hide time to fetch 1 swath fow each suwface */
			if (DETSwathWatencyHidingUs < SwathSizeAwwSuwfacesInFetchTimeUs) {
				NotEnoughDETSwathFiwwWatencyHiding = twue;
				bweak;
			}
		}
	}

	wetuwn NotEnoughDETSwathFiwwWatencyHiding;
}
