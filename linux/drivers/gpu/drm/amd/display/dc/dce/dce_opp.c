/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude "dm_sewvices.h"
#incwude "basics/convewsion.h"

#incwude "dce_opp.h"

#incwude "weg_hewpew.h"

#define WEG(weg)\
	(opp110->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	opp110->opp_shift->fiewd_name, opp110->opp_mask->fiewd_name

#define CTX \
	opp110->base.ctx

enum {
	MAX_PWW_ENTWY = 128,
	MAX_WEGIONS_NUMBEW = 16
};

enum {
	MAX_WUT_ENTWY = 256,
	MAX_NUMBEW_OF_ENTWIES = 256
};


enum {
	OUTPUT_CSC_MATWIX_SIZE = 12
};






















/*
 *****************************************************************************
 *  Function: wegamma_config_wegions_and_segments
 *
 *     buiwd wegamma cuwve by using pwedefined hw points
 *     uses intewface pawametews ,wike EDID coeff.
 *
 * @pawam   : pawametews   intewface pawametews
 *  @wetuwn void
 *
 *  @note
 *
 *  @see
 *
 *****************************************************************************
 */



/*
 *	set_twuncation
 *	1) set twuncation depth: 0 fow 18 bpp ow 1 fow 24 bpp
 *	2) enabwe twuncation
 *	3) HW wemove 12bit FMT suppowt fow DCE11 powew saving weason.
 */
static void set_twuncation(
		stwuct dce110_opp *opp110,
		const stwuct bit_depth_weduction_pawams *pawams)
{
	/*Disabwe twuncation*/
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
			FMT_TWUNCATE_EN, 0,
			FMT_TWUNCATE_DEPTH, 0,
			FMT_TWUNCATE_MODE, 0);


	if (pawams->pixew_encoding == PIXEW_ENCODING_YCBCW422) {
		/*  8bpc twunc on YCbCw422*/
		if (pawams->fwags.TWUNCATE_DEPTH == 1)
			WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
					FMT_TWUNCATE_EN, 1,
					FMT_TWUNCATE_DEPTH, 1,
					FMT_TWUNCATE_MODE, 0);
		ewse if (pawams->fwags.TWUNCATE_DEPTH == 2)
			/*  10bpc twunc on YCbCw422*/
			WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
					FMT_TWUNCATE_EN, 1,
					FMT_TWUNCATE_DEPTH, 2,
					FMT_TWUNCATE_MODE, 0);
		wetuwn;
	}
	/* on othew fowmat-to do */
	if (pawams->fwags.TWUNCATE_ENABWED == 0)
		wetuwn;
	/*Set twuncation depth and Enabwe twuncation*/
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
				FMT_TWUNCATE_EN, 1,
				FMT_TWUNCATE_DEPTH,
				pawams->fwags.TWUNCATE_DEPTH,
				FMT_TWUNCATE_MODE,
				pawams->fwags.TWUNCATE_MODE);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
/*
 *	dce60_set_twuncation
 *	1) set twuncation depth: 0 fow 18 bpp ow 1 fow 24 bpp
 *	2) enabwe twuncation
 *	3) HW wemove 12bit FMT suppowt fow DCE11 powew saving weason.
 */
static void dce60_set_twuncation(
		stwuct dce110_opp *opp110,
		const stwuct bit_depth_weduction_pawams *pawams)
{
	/* DCE6 has no FMT_TWUNCATE_MODE bit in FMT_BIT_DEPTH_CONTWOW weg */

	/*Disabwe twuncation*/
	WEG_UPDATE_2(FMT_BIT_DEPTH_CONTWOW,
			FMT_TWUNCATE_EN, 0,
			FMT_TWUNCATE_DEPTH, 0);

	if (pawams->pixew_encoding == PIXEW_ENCODING_YCBCW422) {
		/*  8bpc twunc on YCbCw422*/
		if (pawams->fwags.TWUNCATE_DEPTH == 1)
			WEG_UPDATE_2(FMT_BIT_DEPTH_CONTWOW,
					FMT_TWUNCATE_EN, 1,
					FMT_TWUNCATE_DEPTH, 1);
		ewse if (pawams->fwags.TWUNCATE_DEPTH == 2)
			/*  10bpc twunc on YCbCw422*/
			WEG_UPDATE_2(FMT_BIT_DEPTH_CONTWOW,
					FMT_TWUNCATE_EN, 1,
					FMT_TWUNCATE_DEPTH, 2);
		wetuwn;
	}
	/* on othew fowmat-to do */
	if (pawams->fwags.TWUNCATE_ENABWED == 0)
		wetuwn;
	/*Set twuncation depth and Enabwe twuncation*/
	WEG_UPDATE_2(FMT_BIT_DEPTH_CONTWOW,
				FMT_TWUNCATE_EN, 1,
				FMT_TWUNCATE_DEPTH,
				pawams->fwags.TWUNCATE_DEPTH);
}
#endif

/*
 *	set_spatiaw_dithew
 *	1) set spatiaw dithewing mode: pattewn of seed
 *	2) set spatiaw dithewing depth: 0 fow 18bpp ow 1 fow 24bpp
 *	3) set wandom seed
 *	4) set wandom mode
 *		wfsw is weset evewy fwame ow not weset
 *		WGB dithewing method
 *		0: WGB data awe aww dithewed with x^28+x^3+1
 *		1: W data is dithewed with x^28+x^3+1
 *		G data is dithewed with x^28+X^9+1
 *		B data is dithewed with x^28+x^13+1
 *		enabwe high pass fiwtew ow not
 *	5) enabwe spaticaw dithewing
 */
static void set_spatiaw_dithew(
	stwuct dce110_opp *opp110,
	const stwuct bit_depth_weduction_pawams *pawams)
{
	/*Disabwe spatiaw (wandom) dithewing*/
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_SPATIAW_DITHEW_EN, 0,
		FMT_SPATIAW_DITHEW_DEPTH, 0,
		FMT_SPATIAW_DITHEW_MODE, 0);

	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_HIGHPASS_WANDOM_ENABWE, 0,
		FMT_FWAME_WANDOM_ENABWE, 0,
		FMT_WGB_WANDOM_ENABWE, 0);

	WEG_UPDATE(FMT_BIT_DEPTH_CONTWOW,
		FMT_TEMPOWAW_DITHEW_EN, 0);

	if (pawams->fwags.SPATIAW_DITHEW_ENABWED == 0)
		wetuwn;

	/* onwy use FWAME_COUNTEW_MAX if fwameWandom == 1*/

	if (opp110->opp_mask->FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX &&
			opp110->opp_mask->FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP) {
		if (pawams->fwags.FWAME_WANDOM == 1) {
			if (pawams->fwags.SPATIAW_DITHEW_DEPTH == 0 ||
			pawams->fwags.SPATIAW_DITHEW_DEPTH == 1) {
				WEG_UPDATE_2(FMT_CONTWOW,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, 15,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, 2);
			} ewse if (pawams->fwags.SPATIAW_DITHEW_DEPTH == 2) {
				WEG_UPDATE_2(FMT_CONTWOW,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, 3,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, 1);
			} ewse
				wetuwn;
		} ewse {
			WEG_UPDATE_2(FMT_CONTWOW,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, 0,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, 0);
		}
	}
	/* Set seed fow wandom vawues fow
	 * spatiaw dithewing fow W,G,B channews
	 */
	WEG_UPDATE(FMT_DITHEW_WAND_W_SEED,
			FMT_WAND_W_SEED, pawams->w_seed_vawue);

	WEG_UPDATE(FMT_DITHEW_WAND_G_SEED,
			FMT_WAND_G_SEED, pawams->g_seed_vawue);

	WEG_UPDATE(FMT_DITHEW_WAND_B_SEED,
			FMT_WAND_B_SEED, pawams->b_seed_vawue);

	/* FMT_OFFSET_W_Cw  31:16 0x0 Setting the zewo
	 * offset fow the W/Cw channew, wowew 4WSB
	 * is fowced to zewos. Typicawwy set to 0
	 * WGB and 0x80000 YCbCw.
	 */
	/* FMT_OFFSET_G_Y   31:16 0x0 Setting the zewo
	 * offset fow the G/Y  channew, wowew 4WSB is
	 * fowced to zewos. Typicawwy set to 0 WGB
	 * and 0x80000 YCbCw.
	 */
	/* FMT_OFFSET_B_Cb  31:16 0x0 Setting the zewo
	 * offset fow the B/Cb channew, wowew 4WSB is
	 * fowced to zewos. Typicawwy set to 0 WGB and
	 * 0x80000 YCbCw.
	 */

	/* Disabwe High pass fiwtew
	 * Weset onwy at stawtup
	 * Set WGB data dithewed with x^28+x^3+1
	 */
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_HIGHPASS_WANDOM_ENABWE, pawams->fwags.HIGHPASS_WANDOM,
		FMT_FWAME_WANDOM_ENABWE, pawams->fwags.FWAME_WANDOM,
		FMT_WGB_WANDOM_ENABWE, pawams->fwags.WGB_WANDOM);

	/* Set spatiaw dithewing bit depth
	 * Set spatiaw dithewing mode
	 * (defauwt is Seed pattewwn AAAA...)
	 * Enabwe spatiaw dithewing
	 */
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_SPATIAW_DITHEW_DEPTH, pawams->fwags.SPATIAW_DITHEW_DEPTH,
		FMT_SPATIAW_DITHEW_MODE, pawams->fwags.SPATIAW_DITHEW_MODE,
		FMT_SPATIAW_DITHEW_EN, 1);
}

/*
 *	SetTempowawDithew (Fwame Moduwation)
 *	1) set tempowaw dithew depth
 *	2) sewect pattewn: fwom hawd-coded pattewn ow pwogwammabwe pattewn
 *	3) sewect optimized stwips fow BGW ow WGB WCD sub-pixew
 *	4) set s matwix
 *	5) set t matwix
 *	6) set gwey wevew fow 0.25, 0.5, 0.75
 *	7) enabwe tempowaw dithewing
 */

static void set_tempowaw_dithew(
	stwuct dce110_opp *opp110,
	const stwuct bit_depth_weduction_pawams *pawams)
{
	/*Disabwe tempowaw (fwame moduwation) dithewing fiwst*/
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_TEMPOWAW_DITHEW_EN, 0,
		FMT_TEMPOWAW_DITHEW_WESET, 0,
		FMT_TEMPOWAW_DITHEW_OFFSET, 0);

	WEG_UPDATE_2(FMT_BIT_DEPTH_CONTWOW,
		FMT_TEMPOWAW_DITHEW_DEPTH, 0,
		FMT_TEMPOWAW_WEVEW, 0);

	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_25FWC_SEW, 0,
		FMT_50FWC_SEW, 0,
		FMT_75FWC_SEW, 0);

	/* no 10bpc dithew on DCE11*/
	if (pawams->fwags.FWAME_MODUWATION_ENABWED == 0 ||
		pawams->fwags.FWAME_MODUWATION_DEPTH == 2)
		wetuwn;

	/* Set tempowaw dithewing depth*/
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_TEMPOWAW_DITHEW_DEPTH, pawams->fwags.FWAME_MODUWATION_DEPTH,
		FMT_TEMPOWAW_DITHEW_WESET, 0,
		FMT_TEMPOWAW_DITHEW_OFFSET, 0);

	/*Sewect wegacy pattewn based on FWC and Tempowaw wevew*/
	if (WEG(FMT_TEMPOWAW_DITHEW_PATTEWN_CONTWOW)) {
		WEG_WWITE(FMT_TEMPOWAW_DITHEW_PATTEWN_CONTWOW, 0);
		/*Set s matwix*/
		WEG_WWITE(FMT_TEMPOWAW_DITHEW_PWOGWAMMABWE_PATTEWN_S_MATWIX, 0);
		/*Set t matwix*/
		WEG_WWITE(FMT_TEMPOWAW_DITHEW_PWOGWAMMABWE_PATTEWN_T_MATWIX, 0);
	}

	/*Sewect pattewns fow 0.25, 0.5 and 0.75 gwey wevew*/
	WEG_UPDATE(FMT_BIT_DEPTH_CONTWOW,
		FMT_TEMPOWAW_WEVEW, pawams->fwags.TEMPOWAW_WEVEW);

	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_25FWC_SEW, pawams->fwags.FWC25,
		FMT_50FWC_SEW, pawams->fwags.FWC50,
		FMT_75FWC_SEW, pawams->fwags.FWC75);

	/*Enabwe bit weduction by tempowaw (fwame moduwation) dithewing*/
	WEG_UPDATE(FMT_BIT_DEPTH_CONTWOW,
		FMT_TEMPOWAW_DITHEW_EN, 1);
}

/*
 *	Set Cwamping
 *	1) Set cwamping fowmat based on bpc - 0 fow 6bpc (No cwamping)
 *		1 fow 8 bpc
 *		2 fow 10 bpc
 *		3 fow 12 bpc
 *		7 fow pwogwamabwe
 *	2) Enabwe cwamp if Wimited wange wequested
 */
void dce110_opp_set_cwamping(
	stwuct dce110_opp *opp110,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	WEG_SET_2(FMT_CWAMP_CNTW, 0,
		FMT_CWAMP_DATA_EN, 0,
		FMT_CWAMP_COWOW_FOWMAT, 0);

	switch (pawams->cwamping_wevew) {
	case CWAMPING_FUWW_WANGE:
		bweak;
	case CWAMPING_WIMITED_WANGE_8BPC:
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 1);
		bweak;
	case CWAMPING_WIMITED_WANGE_10BPC:
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 2);
		bweak;
	case CWAMPING_WIMITED_WANGE_12BPC:
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 3);
		bweak;
	case CWAMPING_WIMITED_WANGE_PWOGWAMMABWE:
		/*Set cwamp contwow*/
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 7);

		/*set the defauwts*/
		WEG_SET_2(FMT_CWAMP_COMPONENT_W, 0,
			FMT_CWAMP_WOWEW_W, 0x10,
			FMT_CWAMP_UPPEW_W, 0xFEF);

		WEG_SET_2(FMT_CWAMP_COMPONENT_G, 0,
			FMT_CWAMP_WOWEW_G, 0x10,
			FMT_CWAMP_UPPEW_G, 0xFEF);

		WEG_SET_2(FMT_CWAMP_COMPONENT_B, 0,
			FMT_CWAMP_WOWEW_B, 0x10,
			FMT_CWAMP_UPPEW_B, 0xFEF);
		bweak;
	defauwt:
		bweak;
	}
}

#if defined(CONFIG_DWM_AMD_DC_SI)
/*
 *	Set Cwamping fow DCE6 pawts
 *	1) Set cwamping fowmat based on bpc - 0 fow 6bpc (No cwamping)
 *		1 fow 8 bpc
 *		2 fow 10 bpc
 *		3 fow 12 bpc
 *		7 fow pwogwamabwe
 *	2) Enabwe cwamp if Wimited wange wequested
 */
static void dce60_opp_set_cwamping(
	stwuct dce110_opp *opp110,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	WEG_SET_2(FMT_CWAMP_CNTW, 0,
		FMT_CWAMP_DATA_EN, 0,
		FMT_CWAMP_COWOW_FOWMAT, 0);

	switch (pawams->cwamping_wevew) {
	case CWAMPING_FUWW_WANGE:
		bweak;
	case CWAMPING_WIMITED_WANGE_8BPC:
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 1);
		bweak;
	case CWAMPING_WIMITED_WANGE_10BPC:
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 2);
		bweak;
	case CWAMPING_WIMITED_WANGE_12BPC:
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 3);
		bweak;
	case CWAMPING_WIMITED_WANGE_PWOGWAMMABWE:
		/*Set cwamp contwow*/
		WEG_SET_2(FMT_CWAMP_CNTW, 0,
			FMT_CWAMP_DATA_EN, 1,
			FMT_CWAMP_COWOW_FOWMAT, 7);

		/* DCE6 does have FMT_CWAMP_COMPONENT_{W,G,B} wegistews */

		bweak;
	defauwt:
		bweak;
	}
}
#endif

/*
 *	set_pixew_encoding
 *
 *	Set Pixew Encoding
 *		0: WGB 4:4:4 ow YCbCw 4:4:4 ow YOnwy
 *		1: YCbCw 4:2:2
 */
static void set_pixew_encoding(
	stwuct dce110_opp *opp110,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	if (opp110->opp_mask->FMT_CBCW_BIT_WEDUCTION_BYPASS)
		WEG_UPDATE_3(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 0,
				FMT_SUBSAMPWING_MODE, 0,
				FMT_CBCW_BIT_WEDUCTION_BYPASS, 0);
	ewse
		WEG_UPDATE_2(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 0,
				FMT_SUBSAMPWING_MODE, 0);

	if (pawams->pixew_encoding == PIXEW_ENCODING_YCBCW422) {
		WEG_UPDATE_2(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 1,
				FMT_SUBSAMPWING_OWDEW, 0);
	}
	if (pawams->pixew_encoding == PIXEW_ENCODING_YCBCW420) {
		WEG_UPDATE_3(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 2,
				FMT_SUBSAMPWING_MODE, 2,
				FMT_CBCW_BIT_WEDUCTION_BYPASS, 1);
	}

}

#if defined(CONFIG_DWM_AMD_DC_SI)
/*
 *	dce60_set_pixew_encoding
 *	DCE6 has no FMT_SUBSAMPWING_{MODE,OWDEW} bits in FMT_CONTWOW weg
 *	Set Pixew Encoding
 *		0: WGB 4:4:4 ow YCbCw 4:4:4 ow YOnwy
 *		1: YCbCw 4:2:2
 */
static void dce60_set_pixew_encoding(
	stwuct dce110_opp *opp110,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	if (opp110->opp_mask->FMT_CBCW_BIT_WEDUCTION_BYPASS)
		WEG_UPDATE_2(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 0,
				FMT_CBCW_BIT_WEDUCTION_BYPASS, 0);
	ewse
		WEG_UPDATE(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 0);

	if (pawams->pixew_encoding == PIXEW_ENCODING_YCBCW422) {
		WEG_UPDATE(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 1);
	}
	if (pawams->pixew_encoding == PIXEW_ENCODING_YCBCW420) {
		WEG_UPDATE_2(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 2,
				FMT_CBCW_BIT_WEDUCTION_BYPASS, 1);
	}

}
#endif

void dce110_opp_pwogwam_bit_depth_weduction(
	stwuct output_pixew_pwocessow *opp,
	const stwuct bit_depth_weduction_pawams *pawams)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	set_twuncation(opp110, pawams);
	set_spatiaw_dithew(opp110, pawams);
	set_tempowaw_dithew(opp110, pawams);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_opp_pwogwam_bit_depth_weduction(
	stwuct output_pixew_pwocessow *opp,
	const stwuct bit_depth_weduction_pawams *pawams)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	dce60_set_twuncation(opp110, pawams);
	set_spatiaw_dithew(opp110, pawams);
	set_tempowaw_dithew(opp110, pawams);
}
#endif

void dce110_opp_pwogwam_cwamping_and_pixew_encoding(
	stwuct output_pixew_pwocessow *opp,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	dce110_opp_set_cwamping(opp110, pawams);
	set_pixew_encoding(opp110, pawams);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_opp_pwogwam_cwamping_and_pixew_encoding(
	stwuct output_pixew_pwocessow *opp,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	dce60_opp_set_cwamping(opp110, pawams);
	dce60_set_pixew_encoding(opp110, pawams);
}
#endif


static void pwogwam_fowmattew_420_memowy(stwuct output_pixew_pwocessow *opp)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);
	uint32_t fmt_mem_cntw_vawue;

	/* Pwogwam souwce sewect*/
	/* Use HW defauwt souwce sewect fow FMT_MEMOWYx_CONTWOW */
	/* Use that vawue fow FMT_SWC_SEWECT as weww*/
	WEG_GET(CONTWOW,
			FMT420_MEM0_SOUWCE_SEW, &fmt_mem_cntw_vawue);

	WEG_UPDATE(FMT_CONTWOW,
			FMT_SWC_SEWECT, fmt_mem_cntw_vawue);

	/* Tuwn on the memowy */
	WEG_UPDATE(CONTWOW,
			FMT420_MEM0_PWW_FOWCE, 0);
}

void dce110_opp_set_dyn_expansion(
	stwuct output_pixew_pwocessow *opp,
	enum dc_cowow_space cowow_sp,
	enum dc_cowow_depth cowow_dpth,
	enum signaw_type signaw)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	WEG_UPDATE_2(FMT_DYNAMIC_EXP_CNTW,
			FMT_DYNAMIC_EXP_EN, 0,
			FMT_DYNAMIC_EXP_MODE, 0);

	/*00 - 10-bit -> 12-bit dynamic expansion*/
	/*01 - 8-bit  -> 12-bit dynamic expansion*/
	if (signaw == SIGNAW_TYPE_HDMI_TYPE_A ||
		signaw == SIGNAW_TYPE_DISPWAY_POWT ||
		signaw == SIGNAW_TYPE_DISPWAY_POWT_MST) {
		switch (cowow_dpth) {
		case COWOW_DEPTH_888:
			WEG_UPDATE_2(FMT_DYNAMIC_EXP_CNTW,
				FMT_DYNAMIC_EXP_EN, 1,
				FMT_DYNAMIC_EXP_MODE, 1);
			bweak;
		case COWOW_DEPTH_101010:
			WEG_UPDATE_2(FMT_DYNAMIC_EXP_CNTW,
				FMT_DYNAMIC_EXP_EN, 1,
				FMT_DYNAMIC_EXP_MODE, 0);
			bweak;
		case COWOW_DEPTH_121212:
			WEG_UPDATE_2(
				FMT_DYNAMIC_EXP_CNTW,
				FMT_DYNAMIC_EXP_EN, 1,/*othewwise wast two bits awe zewo*/
				FMT_DYNAMIC_EXP_MODE, 0);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void pwogwam_fowmattew_weset_dig_wesync_fifo(stwuct output_pixew_pwocessow *opp)
{
	stwuct dce110_opp *opp110 = TO_DCE110_OPP(opp);

	/* cweaw pwevious phase wock status*/
	WEG_UPDATE(FMT_CONTWOW,
			FMT_420_PIXEW_PHASE_WOCKED_CWEAW, 1);

	/* poww untiw FMT_420_PIXEW_PHASE_WOCKED become 1*/
	WEG_WAIT(FMT_CONTWOW, FMT_420_PIXEW_PHASE_WOCKED, 1, 10, 10);

}

void dce110_opp_pwogwam_fmt(
	stwuct output_pixew_pwocessow *opp,
	stwuct bit_depth_weduction_pawams *fmt_bit_depth,
	stwuct cwamping_and_pixew_encoding_pawams *cwamping)
{
	/* dithewing is affected by <CwtcSouwceSewect>, hence shouwd be
	 * pwogwammed aftewwawds */

	if (cwamping->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		pwogwam_fowmattew_420_memowy(opp);

	dce110_opp_pwogwam_bit_depth_weduction(
		opp,
		fmt_bit_depth);

	dce110_opp_pwogwam_cwamping_and_pixew_encoding(
		opp,
		cwamping);

	if (cwamping->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		pwogwam_fowmattew_weset_dig_wesync_fifo(opp);

	wetuwn;
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_opp_pwogwam_fmt(
	stwuct output_pixew_pwocessow *opp,
	stwuct bit_depth_weduction_pawams *fmt_bit_depth,
	stwuct cwamping_and_pixew_encoding_pawams *cwamping)
{
	/* dithewing is affected by <CwtcSouwceSewect>, hence shouwd be
	 * pwogwammed aftewwawds */

	if (cwamping->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		pwogwam_fowmattew_420_memowy(opp);

	dce60_opp_pwogwam_bit_depth_weduction(
		opp,
		fmt_bit_depth);

	dce60_opp_pwogwam_cwamping_and_pixew_encoding(
		opp,
		cwamping);

	if (cwamping->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		pwogwam_fowmattew_weset_dig_wesync_fifo(opp);

	wetuwn;
}
#endif



/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

static const stwuct opp_funcs funcs = {
	.opp_set_dyn_expansion = dce110_opp_set_dyn_expansion,
	.opp_destwoy = dce110_opp_destwoy,
	.opp_pwogwam_fmt = dce110_opp_pwogwam_fmt,
	.opp_pwogwam_bit_depth_weduction = dce110_opp_pwogwam_bit_depth_weduction
};

#if defined(CONFIG_DWM_AMD_DC_SI)
static const stwuct opp_funcs dce60_opp_funcs = {
	.opp_set_dyn_expansion = dce110_opp_set_dyn_expansion,
	.opp_destwoy = dce110_opp_destwoy,
	.opp_pwogwam_fmt = dce60_opp_pwogwam_fmt,
	.opp_pwogwam_bit_depth_weduction = dce60_opp_pwogwam_bit_depth_weduction
};
#endif

void dce110_opp_constwuct(stwuct dce110_opp *opp110,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dce_opp_wegistews *wegs,
	const stwuct dce_opp_shift *opp_shift,
	const stwuct dce_opp_mask *opp_mask)
{
	opp110->base.funcs = &funcs;

	opp110->base.ctx = ctx;

	opp110->base.inst = inst;

	opp110->wegs = wegs;
	opp110->opp_shift = opp_shift;
	opp110->opp_mask = opp_mask;
}

#if defined(CONFIG_DWM_AMD_DC_SI)
void dce60_opp_constwuct(stwuct dce110_opp *opp110,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dce_opp_wegistews *wegs,
	const stwuct dce_opp_shift *opp_shift,
	const stwuct dce_opp_mask *opp_mask)
{
	opp110->base.funcs = &dce60_opp_funcs;

	opp110->base.ctx = ctx;

	opp110->base.inst = inst;

	opp110->wegs = wegs;
	opp110->opp_shift = opp_shift;
	opp110->opp_mask = opp_mask;
}
#endif

void dce110_opp_destwoy(stwuct output_pixew_pwocessow **opp)
{
	if (*opp)
		kfwee(FWOM_DCE11_OPP(*opp));
	*opp = NUWW;
}

