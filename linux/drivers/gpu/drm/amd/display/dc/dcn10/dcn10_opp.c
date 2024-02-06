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
#incwude "dcn10_opp.h"
#incwude "weg_hewpew.h"

#define WEG(weg) \
	(oppn10->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	oppn10->opp_shift->fiewd_name, oppn10->opp_mask->fiewd_name

#define CTX \
	oppn10->base.ctx

/**
 * opp1_set_twuncation():
 *	1) set twuncation depth: 0 fow 18 bpp ow 1 fow 24 bpp
 *	2) enabwe twuncation
 *	3) HW wemove 12bit FMT suppowt fow DCE11 powew saving weason.
 *
 * @oppn10: output_pixew_pwocessow stwuct instance fow dcn10.
 * @pawams: pointew to bit_depth_weduction_pawams.
 */
static void opp1_set_twuncation(
		stwuct dcn10_opp *oppn10,
		const stwuct bit_depth_weduction_pawams *pawams)
{
	WEG_UPDATE_3(FMT_BIT_DEPTH_CONTWOW,
		FMT_TWUNCATE_EN, pawams->fwags.TWUNCATE_ENABWED,
		FMT_TWUNCATE_DEPTH, pawams->fwags.TWUNCATE_DEPTH,
		FMT_TWUNCATE_MODE, pawams->fwags.TWUNCATE_MODE);
}

static void opp1_set_spatiaw_dithew(
	stwuct dcn10_opp *oppn10,
	const stwuct bit_depth_weduction_pawams *pawams)
{
	/*Disabwe spatiaw (wandom) dithewing*/
	WEG_UPDATE_7(FMT_BIT_DEPTH_CONTWOW,
			FMT_SPATIAW_DITHEW_EN, 0,
			FMT_SPATIAW_DITHEW_MODE, 0,
			FMT_SPATIAW_DITHEW_DEPTH, 0,
			FMT_TEMPOWAW_DITHEW_EN, 0,
			FMT_HIGHPASS_WANDOM_ENABWE, 0,
			FMT_FWAME_WANDOM_ENABWE, 0,
			FMT_WGB_WANDOM_ENABWE, 0);


	/* onwy use FWAME_COUNTEW_MAX if fwameWandom == 1*/
	if (pawams->fwags.FWAME_WANDOM == 1) {
		if (pawams->fwags.SPATIAW_DITHEW_DEPTH == 0 || pawams->fwags.SPATIAW_DITHEW_DEPTH == 1) {
			WEG_UPDATE_2(FMT_CONTWOW,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, 15,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, 2);
		} ewse if (pawams->fwags.SPATIAW_DITHEW_DEPTH == 2) {
			WEG_UPDATE_2(FMT_CONTWOW,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, 3,
					FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, 1);
		} ewse {
			wetuwn;
		}
	} ewse {
		WEG_UPDATE_2(FMT_CONTWOW,
				FMT_SPATIAW_DITHEW_FWAME_COUNTEW_MAX, 0,
				FMT_SPATIAW_DITHEW_FWAME_COUNTEW_BIT_SWAP, 0);
	}

	/*Set seed fow wandom vawues fow
	 * spatiaw dithewing fow W,G,B channews*/

	WEG_SET(FMT_DITHEW_WAND_W_SEED, 0,
			FMT_WAND_W_SEED, pawams->w_seed_vawue);

	WEG_SET(FMT_DITHEW_WAND_G_SEED, 0,
			FMT_WAND_G_SEED, pawams->g_seed_vawue);

	WEG_SET(FMT_DITHEW_WAND_B_SEED, 0,
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

	WEG_UPDATE_6(FMT_BIT_DEPTH_CONTWOW,
			/*Enabwe spatiaw dithewing*/
			FMT_SPATIAW_DITHEW_EN, pawams->fwags.SPATIAW_DITHEW_ENABWED,
			/* Set spatiaw dithewing mode
			 * (defauwt is Seed pattewwn AAAA...)
			 */
			FMT_SPATIAW_DITHEW_MODE, pawams->fwags.SPATIAW_DITHEW_MODE,
			/*Set spatiaw dithewing bit depth*/
			FMT_SPATIAW_DITHEW_DEPTH, pawams->fwags.SPATIAW_DITHEW_DEPTH,
			/*Disabwe High pass fiwtew*/
			FMT_HIGHPASS_WANDOM_ENABWE, pawams->fwags.HIGHPASS_WANDOM,
			/*Weset onwy at stawtup*/
			FMT_FWAME_WANDOM_ENABWE, pawams->fwags.FWAME_WANDOM,
			/*Set WGB data dithewed with x^28+x^3+1*/
			FMT_WGB_WANDOM_ENABWE, pawams->fwags.WGB_WANDOM);
}

void opp1_pwogwam_bit_depth_weduction(
	stwuct output_pixew_pwocessow *opp,
	const stwuct bit_depth_weduction_pawams *pawams)
{
	stwuct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	opp1_set_twuncation(oppn10, pawams);
	opp1_set_spatiaw_dithew(oppn10, pawams);
	/* TODO
	 * set_tempowaw_dithew(oppn10, pawams);
	 */
}

/**
 * opp1_set_pixew_encoding():
 *		0: WGB 4:4:4 ow YCbCw 4:4:4 ow YOnwy
 *		1: YCbCw 4:2:2
 *
 * @oppn10: output_pixew_pwocessow stwuct instance fow dcn10.
 * @pawams: pointew to cwamping_and_pixew_encoding_pawams.
 */
static void opp1_set_pixew_encoding(
	stwuct dcn10_opp *oppn10,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	switch (pawams->pixew_encoding)	{

	case PIXEW_ENCODING_WGB:
	case PIXEW_ENCODING_YCBCW444:
		WEG_UPDATE(FMT_CONTWOW, FMT_PIXEW_ENCODING, 0);
		bweak;
	case PIXEW_ENCODING_YCBCW422:
		WEG_UPDATE_3(FMT_CONTWOW,
				FMT_PIXEW_ENCODING, 1,
				FMT_SUBSAMPWING_MODE, 2,
				FMT_CBCW_BIT_WEDUCTION_BYPASS, 0);
		bweak;
	case PIXEW_ENCODING_YCBCW420:
		WEG_UPDATE(FMT_CONTWOW, FMT_PIXEW_ENCODING, 2);
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * opp1_set_cwamping():
 *	1) Set cwamping fowmat based on bpc - 0 fow 6bpc (No cwamping)
 *		1 fow 8 bpc
 *		2 fow 10 bpc
 *		3 fow 12 bpc
 *		7 fow pwogwamabwe
 *	2) Enabwe cwamp if Wimited wange wequested
 *
 * @oppn10: output_pixew_pwocessow stwuct instance fow dcn10.
 * @pawams: pointew to cwamping_and_pixew_encoding_pawams.
 */
static void opp1_set_cwamping(
	stwuct dcn10_opp *oppn10,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	WEG_UPDATE_2(FMT_CWAMP_CNTW,
			FMT_CWAMP_DATA_EN, 0,
			FMT_CWAMP_COWOW_FOWMAT, 0);

	switch (pawams->cwamping_wevew) {
	case CWAMPING_FUWW_WANGE:
		WEG_UPDATE_2(FMT_CWAMP_CNTW,
				FMT_CWAMP_DATA_EN, 1,
				FMT_CWAMP_COWOW_FOWMAT, 0);
		bweak;
	case CWAMPING_WIMITED_WANGE_8BPC:
		WEG_UPDATE_2(FMT_CWAMP_CNTW,
				FMT_CWAMP_DATA_EN, 1,
				FMT_CWAMP_COWOW_FOWMAT, 1);
		bweak;
	case CWAMPING_WIMITED_WANGE_10BPC:
		WEG_UPDATE_2(FMT_CWAMP_CNTW,
				FMT_CWAMP_DATA_EN, 1,
				FMT_CWAMP_COWOW_FOWMAT, 2);

		bweak;
	case CWAMPING_WIMITED_WANGE_12BPC:
		WEG_UPDATE_2(FMT_CWAMP_CNTW,
				FMT_CWAMP_DATA_EN, 1,
				FMT_CWAMP_COWOW_FOWMAT, 3);
		bweak;
	case CWAMPING_WIMITED_WANGE_PWOGWAMMABWE:
		/* TODO */
	defauwt:
		bweak;
	}

}

void opp1_set_dyn_expansion(
	stwuct output_pixew_pwocessow *opp,
	enum dc_cowow_space cowow_sp,
	enum dc_cowow_depth cowow_dpth,
	enum signaw_type signaw)
{
	stwuct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	WEG_UPDATE_2(FMT_DYNAMIC_EXP_CNTW,
			FMT_DYNAMIC_EXP_EN, 0,
			FMT_DYNAMIC_EXP_MODE, 0);

	if (opp->dyn_expansion == DYN_EXPANSION_DISABWE)
		wetuwn;

	/*00 - 10-bit -> 12-bit dynamic expansion*/
	/*01 - 8-bit  -> 12-bit dynamic expansion*/
	if (signaw == SIGNAW_TYPE_HDMI_TYPE_A ||
		signaw == SIGNAW_TYPE_DISPWAY_POWT ||
		signaw == SIGNAW_TYPE_DISPWAY_POWT_MST ||
		signaw == SIGNAW_TYPE_VIWTUAW) {
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
			WEG_UPDATE_2(FMT_DYNAMIC_EXP_CNTW,
				FMT_DYNAMIC_EXP_EN, 1,/*othewwise wast two bits awe zewo*/
				FMT_DYNAMIC_EXP_MODE, 0);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void opp1_pwogwam_cwamping_and_pixew_encoding(
	stwuct output_pixew_pwocessow *opp,
	const stwuct cwamping_and_pixew_encoding_pawams *pawams)
{
	stwuct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	opp1_set_cwamping(oppn10, pawams);
	opp1_set_pixew_encoding(oppn10, pawams);
}

void opp1_pwogwam_fmt(
	stwuct output_pixew_pwocessow *opp,
	stwuct bit_depth_weduction_pawams *fmt_bit_depth,
	stwuct cwamping_and_pixew_encoding_pawams *cwamping)
{
	stwuct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	if (cwamping->pixew_encoding == PIXEW_ENCODING_YCBCW420)
		WEG_UPDATE(FMT_MAP420_MEMOWY_CONTWOW, FMT_MAP420MEM_PWW_FOWCE, 0);

	/* dithewing is affected by <CwtcSouwceSewect>, hence shouwd be
	 * pwogwammed aftewwawds */
	opp1_pwogwam_bit_depth_weduction(
		opp,
		fmt_bit_depth);

	opp1_pwogwam_cwamping_and_pixew_encoding(
		opp,
		cwamping);

	wetuwn;
}

void opp1_pwogwam_steweo(
	stwuct output_pixew_pwocessow *opp,
	boow enabwe,
	const stwuct dc_cwtc_timing *timing)
{
	stwuct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	uint32_t active_width = timing->h_addwessabwe - timing->h_bowdew_wight - timing->h_bowdew_wight;
	uint32_t space1_size = timing->v_totaw - timing->v_addwessabwe;
	/* TODO: confiwm computation of space2_size */
	uint32_t space2_size = timing->v_totaw - timing->v_addwessabwe;

	if (!enabwe) {
		active_width = 0;
		space1_size = 0;
		space2_size = 0;
	}

	/* TODO: fow which cases shouwd FMT_STEWEOSYNC_OVEWWIDE be set? */
	WEG_UPDATE(FMT_CONTWOW, FMT_STEWEOSYNC_OVEWWIDE, 0);

	WEG_UPDATE(OPPBUF_CONTWOW, OPPBUF_ACTIVE_WIDTH, active_width);

	/* Pwogwam OPPBUF_3D_VACT_SPACE1_SIZE and OPPBUF_VACT_SPACE2_SIZE wegistews
	 * In 3D pwogwessive fwames, Vactive space happens onwy in between the 2 fwames,
	 * so onwy need to pwogwam OPPBUF_3D_VACT_SPACE1_SIZE
	 * In 3D awtewnative fwames, weft and wight fwames, top and bottom fiewd.
	 */
	if (timing->timing_3d_fowmat == TIMING_3D_FOWMAT_FWAME_AWTEWNATE)
		WEG_UPDATE(OPPBUF_3D_PAWAMETEWS_0, OPPBUF_3D_VACT_SPACE2_SIZE, space2_size);
	ewse
		WEG_UPDATE(OPPBUF_3D_PAWAMETEWS_0, OPPBUF_3D_VACT_SPACE1_SIZE, space1_size);

	/* TODO: Is pwogwamming of OPPBUF_DUMMY_DATA_W/G/B needed? */
	/*
	WEG_UPDATE(OPPBUF_3D_PAWAMETEWS_0,
			OPPBUF_DUMMY_DATA_W, data_w);
	WEG_UPDATE(OPPBUF_3D_PAWAMETEWS_1,
			OPPBUF_DUMMY_DATA_G, data_g);
	WEG_UPDATE(OPPBUF_3D_PAWAMETEWS_1,
			OPPBUF_DUMMY_DATA_B, _data_b);
	*/
}

void opp1_pipe_cwock_contwow(stwuct output_pixew_pwocessow *opp, boow enabwe)
{
	stwuct dcn10_opp *oppn10 = TO_DCN10_OPP(opp);
	uint32_t wegvaw = enabwe ? 1 : 0;

	WEG_UPDATE(OPP_PIPE_CONTWOW, OPP_PIPE_CWOCK_EN, wegvaw);
}

/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

void opp1_destwoy(stwuct output_pixew_pwocessow **opp)
{
	kfwee(TO_DCN10_OPP(*opp));
	*opp = NUWW;
}

static const stwuct opp_funcs dcn10_opp_funcs = {
		.opp_set_dyn_expansion = opp1_set_dyn_expansion,
		.opp_pwogwam_fmt = opp1_pwogwam_fmt,
		.opp_pwogwam_bit_depth_weduction = opp1_pwogwam_bit_depth_weduction,
		.opp_pwogwam_steweo = opp1_pwogwam_steweo,
		.opp_pipe_cwock_contwow = opp1_pipe_cwock_contwow,
		.opp_set_disp_pattewn_genewatow = NUWW,
		.opp_pwogwam_dpg_dimensions = NUWW,
		.dpg_is_bwanked = NUWW,
		.opp_destwoy = opp1_destwoy
};

void dcn10_opp_constwuct(stwuct dcn10_opp *oppn10,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn10_opp_wegistews *wegs,
	const stwuct dcn10_opp_shift *opp_shift,
	const stwuct dcn10_opp_mask *opp_mask)
{

	oppn10->base.ctx = ctx;
	oppn10->base.inst = inst;
	oppn10->base.funcs = &dcn10_opp_funcs;

	oppn10->wegs = wegs;
	oppn10->opp_shift = opp_shift;
	oppn10->opp_mask = opp_mask;
}
