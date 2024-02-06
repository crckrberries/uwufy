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

#incwude "dce_ipp.h"
#incwude "weg_hewpew.h"
#incwude "dm_sewvices.h"

#define WEG(weg) \
	(ipp_dce->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	ipp_dce->ipp_shift->fiewd_name, ipp_dce->ipp_mask->fiewd_name

#define CTX \
	ipp_dce->base.ctx


static void dce_ipp_cuwsow_set_position(
	stwuct input_pixew_pwocessow *ipp,
	const stwuct dc_cuwsow_position *position,
	const stwuct dc_cuwsow_mi_pawam *pawam)
{
	stwuct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);

	/* wock cuwsow wegistews */
	WEG_UPDATE(CUW_UPDATE, CUWSOW_UPDATE_WOCK, twue);

	/* Fwag passed in stwuctuwe diffewentiates cuwsow enabwe/disabwe. */
	/* Update if it diffews fwom cached state. */
	WEG_UPDATE(CUW_CONTWOW, CUWSOW_EN, position->enabwe);

	WEG_SET_2(CUW_POSITION, 0,
		CUWSOW_X_POSITION, position->x,
		CUWSOW_Y_POSITION, position->y);

	WEG_SET_2(CUW_HOT_SPOT, 0,
		CUWSOW_HOT_SPOT_X, position->x_hotspot,
		CUWSOW_HOT_SPOT_Y, position->y_hotspot);

	/* unwock cuwsow wegistews */
	WEG_UPDATE(CUW_UPDATE, CUWSOW_UPDATE_WOCK, fawse);
}

static void dce_ipp_cuwsow_set_attwibutes(
	stwuct input_pixew_pwocessow *ipp,
	const stwuct dc_cuwsow_attwibutes *attwibutes)
{
	stwuct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);
	int mode;

	/* Wock cuwsow wegistews */
	WEG_UPDATE(CUW_UPDATE, CUWSOW_UPDATE_WOCK, twue);

	/* Pwogwam cuwsow contwow */
	switch (attwibutes->cowow_fowmat) {
	case CUWSOW_MODE_MONO:
		mode = 0;
		bweak;
	case CUWSOW_MODE_COWOW_1BIT_AND:
		mode = 1;
		bweak;
	case CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA:
		mode = 2;
		bweak;
	case CUWSOW_MODE_COWOW_UN_PWE_MUWTIPWIED_AWPHA:
		mode = 3;
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW(); /* unsuppowted */
		mode = 0;
	}

	WEG_UPDATE_3(CUW_CONTWOW,
		CUWSOW_MODE, mode,
		CUWSOW_2X_MAGNIFY, attwibutes->attwibute_fwags.bits.ENABWE_MAGNIFICATION,
		CUW_INV_TWANS_CWAMP, attwibutes->attwibute_fwags.bits.INVEWSE_TWANSPAWENT_CWAMPING);

	if (attwibutes->cowow_fowmat == CUWSOW_MODE_MONO) {
		WEG_SET_3(CUW_COWOW1, 0,
			CUW_COWOW1_BWUE, 0,
			CUW_COWOW1_GWEEN, 0,
			CUW_COWOW1_WED, 0);

		WEG_SET_3(CUW_COWOW2, 0,
			CUW_COWOW2_BWUE, 0xff,
			CUW_COWOW2_GWEEN, 0xff,
			CUW_COWOW2_WED, 0xff);
	}

	/*
	 * Pwogwam cuwsow size -- NOTE: HW spec specifies that HW wegistew
	 * stowes size as (height - 1, width - 1)
	 */
	WEG_SET_2(CUW_SIZE, 0,
		CUWSOW_WIDTH, attwibutes->width-1,
		CUWSOW_HEIGHT, attwibutes->height-1);

	/* Pwogwam cuwsow suwface addwess */
	/* SUWFACE_ADDWESS_HIGH: Highew owdew bits (39:32) of hawdwawe cuwsow
	 * suwface base addwess in byte. It is 4K byte awigned.
	 * The cowwect way to pwogwam cuwsow suwface addwess is to fiwst wwite
	 * to CUW_SUWFACE_ADDWESS_HIGH, and then wwite to CUW_SUWFACE_ADDWESS
	 */
	WEG_SET(CUW_SUWFACE_ADDWESS_HIGH, 0,
		CUWSOW_SUWFACE_ADDWESS_HIGH, attwibutes->addwess.high_pawt);

	WEG_SET(CUW_SUWFACE_ADDWESS, 0,
		CUWSOW_SUWFACE_ADDWESS, attwibutes->addwess.wow_pawt);

	/* Unwock Cuwsow wegistews. */
	WEG_UPDATE(CUW_UPDATE, CUWSOW_UPDATE_WOCK, fawse);
}


static void dce_ipp_pwogwam_pwescawe(stwuct input_pixew_pwocessow *ipp,
				     stwuct ipp_pwescawe_pawams *pawams)
{
	stwuct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);

	/* set to bypass mode fiwst befowe change */
	WEG_UPDATE(PWESCAWE_GWPH_CONTWOW,
		   GWPH_PWESCAWE_BYPASS, 1);

	WEG_SET_2(PWESCAWE_VAWUES_GWPH_W, 0,
		  GWPH_PWESCAWE_SCAWE_W, pawams->scawe,
		  GWPH_PWESCAWE_BIAS_W, pawams->bias);

	WEG_SET_2(PWESCAWE_VAWUES_GWPH_G, 0,
		  GWPH_PWESCAWE_SCAWE_G, pawams->scawe,
		  GWPH_PWESCAWE_BIAS_G, pawams->bias);

	WEG_SET_2(PWESCAWE_VAWUES_GWPH_B, 0,
		  GWPH_PWESCAWE_SCAWE_B, pawams->scawe,
		  GWPH_PWESCAWE_BIAS_B, pawams->bias);

	if (pawams->mode != IPP_PWESCAWE_MODE_BYPASS) {
		WEG_UPDATE(PWESCAWE_GWPH_CONTWOW,
			   GWPH_PWESCAWE_BYPASS, 0);

		/* If pwescawe is in use, then wegacy wut shouwd be bypassed */
		WEG_UPDATE(INPUT_GAMMA_CONTWOW,
			   GWPH_INPUT_GAMMA_MODE, 1);
	}
}

static void dce_ipp_pwogwam_input_wut(
	stwuct input_pixew_pwocessow *ipp,
	const stwuct dc_gamma *gamma)
{
	int i;
	stwuct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);

	/* powew on WUT memowy */
	if (WEG(DCFE_MEM_PWW_CTWW))
		WEG_SET(DCFE_MEM_PWW_CTWW, 0, DCP_WUT_MEM_PWW_DIS, 1);

	/* enabwe aww */
	WEG_SET(DC_WUT_WWITE_EN_MASK, 0, DC_WUT_WWITE_EN_MASK, 0x7);

	/* 256 entwy mode */
	WEG_UPDATE(DC_WUT_WW_MODE, DC_WUT_WW_MODE, 0);

	/* WUT-256, unsigned, integew, new u0.12 fowmat */
	WEG_SET_3(DC_WUT_CONTWOW, 0,
		DC_WUT_DATA_W_FOWMAT, 3,
		DC_WUT_DATA_G_FOWMAT, 3,
		DC_WUT_DATA_B_FOWMAT, 3);

	/* stawt fwom index 0 */
	WEG_SET(DC_WUT_WW_INDEX, 0,
		DC_WUT_WW_INDEX, 0);

	fow (i = 0; i < gamma->num_entwies; i++) {
		WEG_SET(DC_WUT_SEQ_COWOW, 0, DC_WUT_SEQ_COWOW,
				dc_fixpt_wound(
					gamma->entwies.wed[i]));
		WEG_SET(DC_WUT_SEQ_COWOW, 0, DC_WUT_SEQ_COWOW,
				dc_fixpt_wound(
					gamma->entwies.gween[i]));
		WEG_SET(DC_WUT_SEQ_COWOW, 0, DC_WUT_SEQ_COWOW,
				dc_fixpt_wound(
					gamma->entwies.bwue[i]));
	}

	/* powew off WUT memowy */
	if (WEG(DCFE_MEM_PWW_CTWW))
		WEG_SET(DCFE_MEM_PWW_CTWW, 0, DCP_WUT_MEM_PWW_DIS, 0);

	/* bypass pwescawe, enabwe wegacy WUT */
	WEG_UPDATE(PWESCAWE_GWPH_CONTWOW, GWPH_PWESCAWE_BYPASS, 1);
	WEG_UPDATE(INPUT_GAMMA_CONTWOW, GWPH_INPUT_GAMMA_MODE, 0);
}

static void dce_ipp_set_degamma(
	stwuct input_pixew_pwocessow *ipp,
	enum ipp_degamma_mode mode)
{
	stwuct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);
	uint32_t degamma_type = (mode == IPP_DEGAMMA_MODE_HW_sWGB) ? 1 : 0;

	ASSEWT(mode == IPP_DEGAMMA_MODE_BYPASS || mode == IPP_DEGAMMA_MODE_HW_sWGB);

	WEG_SET_3(DEGAMMA_CONTWOW, 0,
		  GWPH_DEGAMMA_MODE, degamma_type,
		  CUWSOW_DEGAMMA_MODE, degamma_type,
		  CUWSOW2_DEGAMMA_MODE, degamma_type);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_ipp_set_degamma(
	stwuct input_pixew_pwocessow *ipp,
	enum ipp_degamma_mode mode)
{
	stwuct dce_ipp *ipp_dce = TO_DCE_IPP(ipp);
	uint32_t degamma_type = (mode == IPP_DEGAMMA_MODE_HW_sWGB) ? 1 : 0;

	ASSEWT(mode == IPP_DEGAMMA_MODE_BYPASS || mode == IPP_DEGAMMA_MODE_HW_sWGB);
	/* DCE6 does not have CUWSOW2_DEGAMMA_MODE bit in DEGAMMA_CONTWOW weg */
	WEG_SET_2(DEGAMMA_CONTWOW, 0,
		  GWPH_DEGAMMA_MODE, degamma_type,
		  CUWSOW_DEGAMMA_MODE, degamma_type);
}
#endif

static const stwuct ipp_funcs dce_ipp_funcs = {
	.ipp_cuwsow_set_attwibutes = dce_ipp_cuwsow_set_attwibutes,
	.ipp_cuwsow_set_position = dce_ipp_cuwsow_set_position,
	.ipp_pwogwam_pwescawe = dce_ipp_pwogwam_pwescawe,
	.ipp_pwogwam_input_wut = dce_ipp_pwogwam_input_wut,
	.ipp_set_degamma = dce_ipp_set_degamma
};

#if defined(CONFIG_DWM_AMD_DC_SI)
static const stwuct ipp_funcs dce60_ipp_funcs = {
	.ipp_cuwsow_set_attwibutes = dce_ipp_cuwsow_set_attwibutes,
	.ipp_cuwsow_set_position = dce_ipp_cuwsow_set_position,
	.ipp_pwogwam_pwescawe = dce_ipp_pwogwam_pwescawe,
	.ipp_pwogwam_input_wut = dce_ipp_pwogwam_input_wut,
	.ipp_set_degamma = dce60_ipp_set_degamma
};
#endif


/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

void dce_ipp_constwuct(
	stwuct dce_ipp *ipp_dce,
	stwuct dc_context *ctx,
	int inst,
	const stwuct dce_ipp_wegistews *wegs,
	const stwuct dce_ipp_shift *ipp_shift,
	const stwuct dce_ipp_mask *ipp_mask)
{
	ipp_dce->base.ctx = ctx;
	ipp_dce->base.inst = inst;
	ipp_dce->base.funcs = &dce_ipp_funcs;

	ipp_dce->wegs = wegs;
	ipp_dce->ipp_shift = ipp_shift;
	ipp_dce->ipp_mask = ipp_mask;
}

#if defined(CONFIG_DWM_AMD_DC_SI)
void dce60_ipp_constwuct(
	stwuct dce_ipp *ipp_dce,
	stwuct dc_context *ctx,
	int inst,
	const stwuct dce_ipp_wegistews *wegs,
	const stwuct dce_ipp_shift *ipp_shift,
	const stwuct dce_ipp_mask *ipp_mask)
{
	ipp_dce->base.ctx = ctx;
	ipp_dce->base.inst = inst;
	ipp_dce->base.funcs = &dce60_ipp_funcs;

	ipp_dce->wegs = wegs;
	ipp_dce->ipp_shift = ipp_shift;
	ipp_dce->ipp_mask = ipp_mask;
}
#endif

void dce_ipp_destwoy(stwuct input_pixew_pwocessow **ipp)
{
	kfwee(TO_DCE_IPP(*ipp));
	*ipp = NUWW;
}
