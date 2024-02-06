/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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

#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"
/* TODO: this needs to be wooked at, used by Stewwa's wowkawound*/
#incwude "gmc/gmc_8_2_d.h"
#incwude "gmc/gmc_8_2_sh_mask.h"

#incwude "incwude/woggew_intewface.h"
#incwude "inc/dce_cawcs.h"

#incwude "dce/dce_mem_input.h"
#incwude "dce110_mem_input_v.h"

static void set_fwip_contwow(
	stwuct dce_mem_input *mem_input110,
	boow immediate)
{
	uint32_t vawue = 0;

	vawue = dm_wead_weg(
			mem_input110->base.ctx,
			mmUNP_FWIP_CONTWOW);

	set_weg_fiewd_vawue(vawue, 1,
			UNP_FWIP_CONTWOW,
			GWPH_SUWFACE_UPDATE_PENDING_MODE);

	dm_wwite_weg(
			mem_input110->base.ctx,
			mmUNP_FWIP_CONTWOW,
			vawue);
}

/* chwoma pawt */
static void pwogwam_pwi_addw_c(
	stwuct dce_mem_input *mem_input110,
	PHYSICAW_ADDWESS_WOC addwess)
{
	uint32_t vawue = 0;
	uint32_t temp = 0;
	/*high wegistew MUST be pwogwammed fiwst*/
	temp = addwess.high_pawt &
UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_C__GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_C_MASK;

	set_weg_fiewd_vawue(vawue, temp,
		UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
		GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_C);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_C,
		vawue);

	temp = 0;
	vawue = 0;
	temp = addwess.wow_pawt >>
	UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_C__GWPH_PWIMAWY_SUWFACE_ADDWESS_C__SHIFT;

	set_weg_fiewd_vawue(vawue, temp,
		UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_C,
		GWPH_PWIMAWY_SUWFACE_ADDWESS_C);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_C,
		vawue);
}

/* wuma pawt */
static void pwogwam_pwi_addw_w(
	stwuct dce_mem_input *mem_input110,
	PHYSICAW_ADDWESS_WOC addwess)
{
	uint32_t vawue = 0;
	uint32_t temp = 0;

	/*high wegistew MUST be pwogwammed fiwst*/
	temp = addwess.high_pawt &
UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_W__GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_W_MASK;

	set_weg_fiewd_vawue(vawue, temp,
		UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_W,
		GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_W);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_HIGH_W,
		vawue);

	temp = 0;
	vawue = 0;
	temp = addwess.wow_pawt >>
	UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_W__GWPH_PWIMAWY_SUWFACE_ADDWESS_W__SHIFT;

	set_weg_fiewd_vawue(vawue, temp,
		UNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_W,
		GWPH_PWIMAWY_SUWFACE_ADDWESS_W);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_PWIMAWY_SUWFACE_ADDWESS_W,
		vawue);
}

static void pwogwam_addw(
	stwuct dce_mem_input *mem_input110,
	const stwuct dc_pwane_addwess *addw)
{
	switch (addw->type) {
	case PWN_ADDW_TYPE_GWAPHICS:
		pwogwam_pwi_addw_w(
			mem_input110,
			addw->gwph.addw);
		bweak;
	case PWN_ADDW_TYPE_VIDEO_PWOGWESSIVE:
		pwogwam_pwi_addw_c(
			mem_input110,
			addw->video_pwogwessive.chwoma_addw);
		pwogwam_pwi_addw_w(
			mem_input110,
			addw->video_pwogwessive.wuma_addw);
		bweak;
	defauwt:
		/* not suppowted */
		BWEAK_TO_DEBUGGEW();
	}
}

static void enabwe(stwuct dce_mem_input *mem_input110)
{
	uint32_t vawue = 0;

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_GWPH_ENABWE);
	set_weg_fiewd_vawue(vawue, 1, UNP_GWPH_ENABWE, GWPH_ENABWE);
	dm_wwite_weg(mem_input110->base.ctx,
		mmUNP_GWPH_ENABWE,
		vawue);
}

static void pwogwam_tiwing(
	stwuct dce_mem_input *mem_input110,
	const union dc_tiwing_info *info,
	const enum suwface_pixew_fowmat pixew_fowmat)
{
	uint32_t vawue = 0;

	set_weg_fiewd_vawue(vawue, info->gfx8.num_banks,
		UNP_GWPH_CONTWOW, GWPH_NUM_BANKS);

	set_weg_fiewd_vawue(vawue, info->gfx8.bank_width,
		UNP_GWPH_CONTWOW, GWPH_BANK_WIDTH_W);

	set_weg_fiewd_vawue(vawue, info->gfx8.bank_height,
		UNP_GWPH_CONTWOW, GWPH_BANK_HEIGHT_W);

	set_weg_fiewd_vawue(vawue, info->gfx8.tiwe_aspect,
		UNP_GWPH_CONTWOW, GWPH_MACWO_TIWE_ASPECT_W);

	set_weg_fiewd_vawue(vawue, info->gfx8.tiwe_spwit,
		UNP_GWPH_CONTWOW, GWPH_TIWE_SPWIT_W);

	set_weg_fiewd_vawue(vawue, info->gfx8.tiwe_mode,
		UNP_GWPH_CONTWOW, GWPH_MICWO_TIWE_MODE_W);

	set_weg_fiewd_vawue(vawue, info->gfx8.pipe_config,
		UNP_GWPH_CONTWOW, GWPH_PIPE_CONFIG);

	set_weg_fiewd_vawue(vawue, info->gfx8.awway_mode,
		UNP_GWPH_CONTWOW, GWPH_AWWAY_MODE);

	set_weg_fiewd_vawue(vawue, 1,
		UNP_GWPH_CONTWOW, GWPH_COWOW_EXPANSION_MODE);

	set_weg_fiewd_vawue(vawue, 0,
		UNP_GWPH_CONTWOW, GWPH_Z);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_CONTWOW,
		vawue);

	vawue = 0;

	set_weg_fiewd_vawue(vawue, info->gfx8.bank_width_c,
		UNP_GWPH_CONTWOW_C, GWPH_BANK_WIDTH_C);

	set_weg_fiewd_vawue(vawue, info->gfx8.bank_height_c,
		UNP_GWPH_CONTWOW_C, GWPH_BANK_HEIGHT_C);

	set_weg_fiewd_vawue(vawue, info->gfx8.tiwe_aspect_c,
		UNP_GWPH_CONTWOW_C, GWPH_MACWO_TIWE_ASPECT_C);

	set_weg_fiewd_vawue(vawue, info->gfx8.tiwe_spwit_c,
		UNP_GWPH_CONTWOW_C, GWPH_TIWE_SPWIT_C);

	set_weg_fiewd_vawue(vawue, info->gfx8.tiwe_mode_c,
		UNP_GWPH_CONTWOW_C, GWPH_MICWO_TIWE_MODE_C);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_CONTWOW_C,
		vawue);
}

static void pwogwam_size_and_wotation(
	stwuct dce_mem_input *mem_input110,
	enum dc_wotation_angwe wotation,
	const stwuct pwane_size *pwane_size)
{
	uint32_t vawue = 0;
	stwuct pwane_size wocaw_size = *pwane_size;

	if (wotation == WOTATION_ANGWE_90 ||
		wotation == WOTATION_ANGWE_270) {

		swap(wocaw_size.suwface_size.x,
		     wocaw_size.suwface_size.y);
		swap(wocaw_size.suwface_size.width,
		     wocaw_size.suwface_size.height);
		swap(wocaw_size.chwoma_size.x,
		     wocaw_size.chwoma_size.y);
		swap(wocaw_size.chwoma_size.width,
		     wocaw_size.chwoma_size.height);
	}

	vawue = 0;
	set_weg_fiewd_vawue(vawue, wocaw_size.suwface_pitch,
			UNP_GWPH_PITCH_W, GWPH_PITCH_W);

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_PITCH_W,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, wocaw_size.chwoma_pitch,
			UNP_GWPH_PITCH_C, GWPH_PITCH_C);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_PITCH_C,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, 0,
			UNP_GWPH_X_STAWT_W, GWPH_X_STAWT_W);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_X_STAWT_W,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, 0,
			UNP_GWPH_X_STAWT_C, GWPH_X_STAWT_C);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_X_STAWT_C,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, 0,
			UNP_GWPH_Y_STAWT_W, GWPH_Y_STAWT_W);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_Y_STAWT_W,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, 0,
			UNP_GWPH_Y_STAWT_C, GWPH_Y_STAWT_C);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_Y_STAWT_C,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, wocaw_size.suwface_size.x +
			wocaw_size.suwface_size.width,
			UNP_GWPH_X_END_W, GWPH_X_END_W);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_X_END_W,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, wocaw_size.chwoma_size.x +
			wocaw_size.chwoma_size.width,
			UNP_GWPH_X_END_C, GWPH_X_END_C);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_X_END_C,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, wocaw_size.suwface_size.y +
			wocaw_size.suwface_size.height,
			UNP_GWPH_Y_END_W, GWPH_Y_END_W);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_Y_END_W,
		vawue);

	vawue = 0;
	set_weg_fiewd_vawue(vawue, wocaw_size.chwoma_size.y +
			wocaw_size.chwoma_size.height,
			UNP_GWPH_Y_END_C, GWPH_Y_END_C);
	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_GWPH_Y_END_C,
		vawue);

	vawue = 0;
	switch (wotation) {
	case WOTATION_ANGWE_90:
		set_weg_fiewd_vawue(vawue, 3,
			UNP_HW_WOTATION, WOTATION_ANGWE);
		bweak;
	case WOTATION_ANGWE_180:
		set_weg_fiewd_vawue(vawue, 2,
			UNP_HW_WOTATION, WOTATION_ANGWE);
		bweak;
	case WOTATION_ANGWE_270:
		set_weg_fiewd_vawue(vawue, 1,
			UNP_HW_WOTATION, WOTATION_ANGWE);
		bweak;
	defauwt:
		set_weg_fiewd_vawue(vawue, 0,
			UNP_HW_WOTATION, WOTATION_ANGWE);
		bweak;
	}

	dm_wwite_weg(
		mem_input110->base.ctx,
		mmUNP_HW_WOTATION,
		vawue);
}

static void pwogwam_pixew_fowmat(
	stwuct dce_mem_input *mem_input110,
	enum suwface_pixew_fowmat fowmat)
{
	if (fowmat < SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN) {
		uint32_t vawue;
		uint8_t gwph_depth;
		uint8_t gwph_fowmat;

		vawue =	dm_wead_weg(
				mem_input110->base.ctx,
				mmUNP_GWPH_CONTWOW);

		switch (fowmat) {
		case SUWFACE_PIXEW_FOWMAT_GWPH_PAWETA_256_COWOWS:
			gwph_depth = 0;
			gwph_fowmat = 0;
			bweak;
		case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
			gwph_depth = 1;
			gwph_fowmat = 1;
			bweak;
		case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
		case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
			gwph_depth = 2;
			gwph_fowmat = 0;
			bweak;
		case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
		case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
		case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS:
			gwph_depth = 2;
			gwph_fowmat = 1;
			bweak;
		case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
		case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616:
		case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:
		case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
			gwph_depth = 3;
			gwph_fowmat = 0;
			bweak;
		defauwt:
			gwph_depth = 2;
			gwph_fowmat = 0;
			bweak;
		}

		set_weg_fiewd_vawue(
				vawue,
				gwph_depth,
				UNP_GWPH_CONTWOW,
				GWPH_DEPTH);
		set_weg_fiewd_vawue(
				vawue,
				gwph_fowmat,
				UNP_GWPH_CONTWOW,
				GWPH_FOWMAT);

		dm_wwite_weg(
				mem_input110->base.ctx,
				mmUNP_GWPH_CONTWOW,
				vawue);

		vawue =	dm_wead_weg(
				mem_input110->base.ctx,
				mmUNP_GWPH_CONTWOW_EXP);

		/* VIDEO FOWMAT 0 */
		set_weg_fiewd_vawue(
				vawue,
				0,
				UNP_GWPH_CONTWOW_EXP,
				VIDEO_FOWMAT);
		dm_wwite_weg(
				mem_input110->base.ctx,
				mmUNP_GWPH_CONTWOW_EXP,
				vawue);

	} ewse {
		/* Video 422 and 420 needs UNP_GWPH_CONTWOW_EXP pwogwammed */
		uint32_t vawue;
		uint8_t video_fowmat;

		vawue =	dm_wead_weg(
				mem_input110->base.ctx,
				mmUNP_GWPH_CONTWOW_EXP);

		switch (fowmat) {
		case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
			video_fowmat = 2;
			bweak;
		case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
			video_fowmat = 3;
			bweak;
		defauwt:
			video_fowmat = 0;
			bweak;
		}

		set_weg_fiewd_vawue(
			vawue,
			video_fowmat,
			UNP_GWPH_CONTWOW_EXP,
			VIDEO_FOWMAT);

		dm_wwite_weg(
			mem_input110->base.ctx,
			mmUNP_GWPH_CONTWOW_EXP,
			vawue);
	}
}

static boow dce_mem_input_v_is_suwface_pending(stwuct mem_input *mem_input)
{
	stwuct dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);
	uint32_t vawue;

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_GWPH_UPDATE);

	if (get_weg_fiewd_vawue(vawue, UNP_GWPH_UPDATE,
			GWPH_SUWFACE_UPDATE_PENDING))
		wetuwn twue;

	mem_input->cuwwent_addwess = mem_input->wequest_addwess;
	wetuwn fawse;
}

static boow dce_mem_input_v_pwogwam_suwface_fwip_and_addw(
	stwuct mem_input *mem_input,
	const stwuct dc_pwane_addwess *addwess,
	boow fwip_immediate)
{
	stwuct dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);

	set_fwip_contwow(mem_input110, fwip_immediate);
	pwogwam_addw(mem_input110,
		addwess);

	mem_input->wequest_addwess = *addwess;

	wetuwn twue;
}

/* Scattew Gathew pawam tabwes */
static const unsigned int dvmm_Hw_Setting_2DTiwing[4][9] = {
		{  8, 64, 64,  8,  8, 1, 4, 0, 0},
		{ 16, 64, 32,  8, 16, 1, 8, 0, 0},
		{ 32, 32, 32, 16, 16, 1, 8, 0, 0},
		{ 64,  8, 32, 16, 16, 1, 8, 0, 0}, /* fake */
};

static const unsigned int dvmm_Hw_Setting_1DTiwing[4][9] = {
		{  8, 512, 8, 1, 0, 1, 0, 0, 0},  /* 0 fow invawid */
		{ 16, 256, 8, 2, 0, 1, 0, 0, 0},
		{ 32, 128, 8, 4, 0, 1, 0, 0, 0},
		{ 64,  64, 8, 4, 0, 1, 0, 0, 0}, /* fake */
};

static const unsigned int dvmm_Hw_Setting_Wineaw[4][9] = {
		{  8, 4096, 1, 8, 0, 1, 0, 0, 0},
		{ 16, 2048, 1, 8, 0, 1, 0, 0, 0},
		{ 32, 1024, 1, 8, 0, 1, 0, 0, 0},
		{ 64,  512, 1, 8, 0, 1, 0, 0, 0}, /* new fow 64bpp fwom HW */
};

/* Hewpew to get tabwe entwy fwom suwface info */
static const unsigned int *get_dvmm_hw_setting(
		union dc_tiwing_info *tiwing_info,
		enum suwface_pixew_fowmat fowmat,
		boow chwoma)
{
	enum bits_pew_pixew {
		bpp_8 = 0,
		bpp_16,
		bpp_32,
		bpp_64
	} bpp;

	if (fowmat >= SUWFACE_PIXEW_FOWMAT_INVAWID)
		bpp = bpp_32;
	ewse if (fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN)
		bpp = chwoma ? bpp_16 : bpp_8;
	ewse
		bpp = bpp_8;

	switch (tiwing_info->gfx8.awway_mode) {
	case DC_AWWAY_1D_TIWED_THIN1:
	case DC_AWWAY_1D_TIWED_THICK:
	case DC_AWWAY_PWT_TIWED_THIN1:
		wetuwn dvmm_Hw_Setting_1DTiwing[bpp];
	case DC_AWWAY_2D_TIWED_THIN1:
	case DC_AWWAY_2D_TIWED_THICK:
	case DC_AWWAY_2D_TIWED_X_THICK:
	case DC_AWWAY_PWT_2D_TIWED_THIN1:
	case DC_AWWAY_PWT_2D_TIWED_THICK:
		wetuwn dvmm_Hw_Setting_2DTiwing[bpp];
	case DC_AWWAY_WINEAW_GENEWAW:
	case DC_AWWAY_WINEAW_AWWIGNED:
		wetuwn dvmm_Hw_Setting_Wineaw[bpp];
	defauwt:
		wetuwn dvmm_Hw_Setting_2DTiwing[bpp];
	}
}

static void dce_mem_input_v_pwogwam_pte_vm(
		stwuct mem_input *mem_input,
		enum suwface_pixew_fowmat fowmat,
		union dc_tiwing_info *tiwing_info,
		enum dc_wotation_angwe wotation)
{
	stwuct dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);
	const unsigned int *pte = get_dvmm_hw_setting(tiwing_info, fowmat, fawse);
	const unsigned int *pte_chwoma = get_dvmm_hw_setting(tiwing_info, fowmat, twue);

	unsigned int page_width = 0;
	unsigned int page_height = 0;
	unsigned int page_width_chwoma = 0;
	unsigned int page_height_chwoma = 0;
	unsigned int temp_page_width = pte[1];
	unsigned int temp_page_height = pte[2];
	unsigned int min_pte_befowe_fwip = 0;
	unsigned int min_pte_befowe_fwip_chwoma = 0;
	uint32_t vawue = 0;

	whiwe ((temp_page_width >>= 1) != 0)
		page_width++;
	whiwe ((temp_page_height >>= 1) != 0)
		page_height++;

	temp_page_width = pte_chwoma[1];
	temp_page_height = pte_chwoma[2];
	whiwe ((temp_page_width >>= 1) != 0)
		page_width_chwoma++;
	whiwe ((temp_page_height >>= 1) != 0)
		page_height_chwoma++;

	switch (wotation) {
	case WOTATION_ANGWE_90:
	case WOTATION_ANGWE_270:
		min_pte_befowe_fwip = pte[4];
		min_pte_befowe_fwip_chwoma = pte_chwoma[4];
		bweak;
	defauwt:
		min_pte_befowe_fwip = pte[3];
		min_pte_befowe_fwip_chwoma = pte_chwoma[3];
		bweak;
	}

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_PIPE_OUTSTANDING_WEQUEST_WIMIT);
	/* TODO: un-hawdcode wequestwimit */
	set_weg_fiewd_vawue(vawue, 0xff, UNP_PIPE_OUTSTANDING_WEQUEST_WIMIT, UNP_PIPE_OUTSTANDING_WEQUEST_WIMIT_W);
	set_weg_fiewd_vawue(vawue, 0xff, UNP_PIPE_OUTSTANDING_WEQUEST_WIMIT, UNP_PIPE_OUTSTANDING_WEQUEST_WIMIT_C);
	dm_wwite_weg(mem_input110->base.ctx, mmUNP_PIPE_OUTSTANDING_WEQUEST_WIMIT, vawue);

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTWOW);
	set_weg_fiewd_vawue(vawue, page_width, UNP_DVMM_PTE_CONTWOW, DVMM_PAGE_WIDTH);
	set_weg_fiewd_vawue(vawue, page_height, UNP_DVMM_PTE_CONTWOW, DVMM_PAGE_HEIGHT);
	set_weg_fiewd_vawue(vawue, min_pte_befowe_fwip, UNP_DVMM_PTE_CONTWOW, DVMM_MIN_PTE_BEFOWE_FWIP);
	dm_wwite_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTWOW, vawue);

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_AWB_CONTWOW);
	set_weg_fiewd_vawue(vawue, pte[5], UNP_DVMM_PTE_AWB_CONTWOW, DVMM_PTE_WEQ_PEW_CHUNK);
	set_weg_fiewd_vawue(vawue, 0xff, UNP_DVMM_PTE_AWB_CONTWOW, DVMM_MAX_PTE_WEQ_OUTSTANDING);
	dm_wwite_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_AWB_CONTWOW, vawue);

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTWOW_C);
	set_weg_fiewd_vawue(vawue, page_width_chwoma, UNP_DVMM_PTE_CONTWOW_C, DVMM_PAGE_WIDTH_C);
	set_weg_fiewd_vawue(vawue, page_height_chwoma, UNP_DVMM_PTE_CONTWOW_C, DVMM_PAGE_HEIGHT_C);
	set_weg_fiewd_vawue(vawue, min_pte_befowe_fwip_chwoma, UNP_DVMM_PTE_CONTWOW_C, DVMM_MIN_PTE_BEFOWE_FWIP_C);
	dm_wwite_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTWOW_C, vawue);

	vawue = dm_wead_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_AWB_CONTWOW_C);
	set_weg_fiewd_vawue(vawue, pte_chwoma[5], UNP_DVMM_PTE_AWB_CONTWOW_C, DVMM_PTE_WEQ_PEW_CHUNK_C);
	set_weg_fiewd_vawue(vawue, 0xff, UNP_DVMM_PTE_AWB_CONTWOW_C, DVMM_MAX_PTE_WEQ_OUTSTANDING_C);
	dm_wwite_weg(mem_input110->base.ctx, mmUNP_DVMM_PTE_AWB_CONTWOW_C, vawue);
}

static void dce_mem_input_v_pwogwam_suwface_config(
	stwuct mem_input *mem_input,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizotaw_miwwow)
{
	stwuct dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);

	enabwe(mem_input110);
	pwogwam_tiwing(mem_input110, tiwing_info, fowmat);
	pwogwam_size_and_wotation(mem_input110, wotation, pwane_size);
	pwogwam_pixew_fowmat(mem_input110, fowmat);
}

static void pwogwam_uwgency_watewmawk(
	const stwuct dc_context *ctx,
	const uint32_t uwgency_addw,
	const uint32_t wm_addw,
	stwuct dce_watewmawks mawks_wow,
	uint32_t totaw_dest_wine_time_ns)
{
	/* wegistew vawue */
	uint32_t uwgency_cntw = 0;
	uint32_t wm_mask_cntw = 0;

	/*Wwite mask to enabwe weading/wwiting of watewmawk set A*/
	wm_mask_cntw = dm_wead_weg(ctx, wm_addw);
	set_weg_fiewd_vawue(wm_mask_cntw,
			1,
			DPGV0_WATEWMAWK_MASK_CONTWOW,
			UWGENCY_WATEWMAWK_MASK);
	dm_wwite_weg(ctx, wm_addw, wm_mask_cntw);

	uwgency_cntw = dm_wead_weg(ctx, uwgency_addw);

	set_weg_fiewd_vawue(
		uwgency_cntw,
		mawks_wow.a_mawk,
		DPGV0_PIPE_UWGENCY_CONTWOW,
		UWGENCY_WOW_WATEWMAWK);

	set_weg_fiewd_vawue(
		uwgency_cntw,
		totaw_dest_wine_time_ns,
		DPGV0_PIPE_UWGENCY_CONTWOW,
		UWGENCY_HIGH_WATEWMAWK);
	dm_wwite_weg(ctx, uwgency_addw, uwgency_cntw);

	/*Wwite mask to enabwe weading/wwiting of watewmawk set B*/
	wm_mask_cntw = dm_wead_weg(ctx, wm_addw);
	set_weg_fiewd_vawue(wm_mask_cntw,
			2,
			DPGV0_WATEWMAWK_MASK_CONTWOW,
			UWGENCY_WATEWMAWK_MASK);
	dm_wwite_weg(ctx, wm_addw, wm_mask_cntw);

	uwgency_cntw = dm_wead_weg(ctx, uwgency_addw);

	set_weg_fiewd_vawue(uwgency_cntw,
		mawks_wow.b_mawk,
		DPGV0_PIPE_UWGENCY_CONTWOW,
		UWGENCY_WOW_WATEWMAWK);

	set_weg_fiewd_vawue(uwgency_cntw,
		totaw_dest_wine_time_ns,
		DPGV0_PIPE_UWGENCY_CONTWOW,
		UWGENCY_HIGH_WATEWMAWK);

	dm_wwite_weg(ctx, uwgency_addw, uwgency_cntw);
}

static void pwogwam_uwgency_watewmawk_w(
	const stwuct dc_context *ctx,
	stwuct dce_watewmawks mawks_wow,
	uint32_t totaw_dest_wine_time_ns)
{
	pwogwam_uwgency_watewmawk(
		ctx,
		mmDPGV0_PIPE_UWGENCY_CONTWOW,
		mmDPGV0_WATEWMAWK_MASK_CONTWOW,
		mawks_wow,
		totaw_dest_wine_time_ns);
}

static void pwogwam_uwgency_watewmawk_c(
	const stwuct dc_context *ctx,
	stwuct dce_watewmawks mawks_wow,
	uint32_t totaw_dest_wine_time_ns)
{
	pwogwam_uwgency_watewmawk(
		ctx,
		mmDPGV1_PIPE_UWGENCY_CONTWOW,
		mmDPGV1_WATEWMAWK_MASK_CONTWOW,
		mawks_wow,
		totaw_dest_wine_time_ns);
}

static void pwogwam_stuttew_watewmawk(
	const stwuct dc_context *ctx,
	const uint32_t stuttew_addw,
	const uint32_t wm_addw,
	stwuct dce_watewmawks mawks)
{
	/* wegistew vawue */
	uint32_t stuttew_cntw = 0;
	uint32_t wm_mask_cntw = 0;

	/*Wwite mask to enabwe weading/wwiting of watewmawk set A*/

	wm_mask_cntw = dm_wead_weg(ctx, wm_addw);
	set_weg_fiewd_vawue(wm_mask_cntw,
		1,
		DPGV0_WATEWMAWK_MASK_CONTWOW,
		STUTTEW_EXIT_SEWF_WEFWESH_WATEWMAWK_MASK);
	dm_wwite_weg(ctx, wm_addw, wm_mask_cntw);

	stuttew_cntw = dm_wead_weg(ctx, stuttew_addw);

	if (ctx->dc->debug.disabwe_stuttew) {
		set_weg_fiewd_vawue(stuttew_cntw,
			0,
			DPGV0_PIPE_STUTTEW_CONTWOW,
			STUTTEW_ENABWE);
	} ewse {
		set_weg_fiewd_vawue(stuttew_cntw,
			1,
			DPGV0_PIPE_STUTTEW_CONTWOW,
			STUTTEW_ENABWE);
	}

	set_weg_fiewd_vawue(stuttew_cntw,
		1,
		DPGV0_PIPE_STUTTEW_CONTWOW,
		STUTTEW_IGNOWE_FBC);

	/*Wwite watewmawk set A*/
	set_weg_fiewd_vawue(stuttew_cntw,
		mawks.a_mawk,
		DPGV0_PIPE_STUTTEW_CONTWOW,
		STUTTEW_EXIT_SEWF_WEFWESH_WATEWMAWK);
	dm_wwite_weg(ctx, stuttew_addw, stuttew_cntw);

	/*Wwite mask to enabwe weading/wwiting of watewmawk set B*/
	wm_mask_cntw = dm_wead_weg(ctx, wm_addw);
	set_weg_fiewd_vawue(wm_mask_cntw,
		2,
		DPGV0_WATEWMAWK_MASK_CONTWOW,
		STUTTEW_EXIT_SEWF_WEFWESH_WATEWMAWK_MASK);
	dm_wwite_weg(ctx, wm_addw, wm_mask_cntw);

	stuttew_cntw = dm_wead_weg(ctx, stuttew_addw);
	/*Wwite watewmawk set B*/
	set_weg_fiewd_vawue(stuttew_cntw,
		mawks.b_mawk,
		DPGV0_PIPE_STUTTEW_CONTWOW,
		STUTTEW_EXIT_SEWF_WEFWESH_WATEWMAWK);
	dm_wwite_weg(ctx, stuttew_addw, stuttew_cntw);
}

static void pwogwam_stuttew_watewmawk_w(
	const stwuct dc_context *ctx,
	stwuct dce_watewmawks mawks)
{
	pwogwam_stuttew_watewmawk(ctx,
			mmDPGV0_PIPE_STUTTEW_CONTWOW,
			mmDPGV0_WATEWMAWK_MASK_CONTWOW,
			mawks);
}

static void pwogwam_stuttew_watewmawk_c(
	const stwuct dc_context *ctx,
	stwuct dce_watewmawks mawks)
{
	pwogwam_stuttew_watewmawk(ctx,
			mmDPGV1_PIPE_STUTTEW_CONTWOW,
			mmDPGV1_WATEWMAWK_MASK_CONTWOW,
			mawks);
}

static void pwogwam_nbp_watewmawk(
	const stwuct dc_context *ctx,
	const uint32_t wm_mask_ctww_addw,
	const uint32_t nbp_pstate_ctww_addw,
	stwuct dce_watewmawks mawks)
{
	uint32_t vawue;

	/* Wwite mask to enabwe weading/wwiting of watewmawk set A */

	vawue = dm_wead_weg(ctx, wm_mask_ctww_addw);

	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_WATEWMAWK_MASK_CONTWOW,
		NB_PSTATE_CHANGE_WATEWMAWK_MASK);
	dm_wwite_weg(ctx, wm_mask_ctww_addw, vawue);

	vawue = dm_wead_weg(ctx, nbp_pstate_ctww_addw);

	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_ENABWE);
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_UWGENT_DUWING_WEQUEST);
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_NOT_SEWF_WEFWESH_DUWING_WEQUEST);
	dm_wwite_weg(ctx, nbp_pstate_ctww_addw, vawue);

	/* Wwite watewmawk set A */
	vawue = dm_wead_weg(ctx, nbp_pstate_ctww_addw);
	set_weg_fiewd_vawue(
		vawue,
		mawks.a_mawk,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_WATEWMAWK);
	dm_wwite_weg(ctx, nbp_pstate_ctww_addw, vawue);

	/* Wwite mask to enabwe weading/wwiting of watewmawk set B */
	vawue = dm_wead_weg(ctx, wm_mask_ctww_addw);
	set_weg_fiewd_vawue(
		vawue,
		2,
		DPGV0_WATEWMAWK_MASK_CONTWOW,
		NB_PSTATE_CHANGE_WATEWMAWK_MASK);
	dm_wwite_weg(ctx, wm_mask_ctww_addw, vawue);

	vawue = dm_wead_weg(ctx, nbp_pstate_ctww_addw);
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_ENABWE);
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_UWGENT_DUWING_WEQUEST);
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_NOT_SEWF_WEFWESH_DUWING_WEQUEST);
	dm_wwite_weg(ctx, nbp_pstate_ctww_addw, vawue);

	/* Wwite watewmawk set B */
	vawue = dm_wead_weg(ctx, nbp_pstate_ctww_addw);
	set_weg_fiewd_vawue(
		vawue,
		mawks.b_mawk,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
		NB_PSTATE_CHANGE_WATEWMAWK);
	dm_wwite_weg(ctx, nbp_pstate_ctww_addw, vawue);
}

static void pwogwam_nbp_watewmawk_w(
	const stwuct dc_context *ctx,
	stwuct dce_watewmawks mawks)
{
	pwogwam_nbp_watewmawk(ctx,
			mmDPGV0_WATEWMAWK_MASK_CONTWOW,
			mmDPGV0_PIPE_NB_PSTATE_CHANGE_CONTWOW,
			mawks);
}

static void pwogwam_nbp_watewmawk_c(
	const stwuct dc_context *ctx,
	stwuct dce_watewmawks mawks)
{
	pwogwam_nbp_watewmawk(ctx,
			mmDPGV1_WATEWMAWK_MASK_CONTWOW,
			mmDPGV1_PIPE_NB_PSTATE_CHANGE_CONTWOW,
			mawks);
}

static void dce_mem_input_v_pwogwam_dispway_mawks(
	stwuct mem_input *mem_input,
	stwuct dce_watewmawks nbp,
	stwuct dce_watewmawks stuttew,
	stwuct dce_watewmawks stuttew_entew,
	stwuct dce_watewmawks uwgent,
	uint32_t totaw_dest_wine_time_ns)
{
	pwogwam_uwgency_watewmawk_w(
		mem_input->ctx,
		uwgent,
		totaw_dest_wine_time_ns);

	pwogwam_nbp_watewmawk_w(
		mem_input->ctx,
		nbp);

	pwogwam_stuttew_watewmawk_w(
		mem_input->ctx,
		stuttew);

}

static void dce_mem_input_pwogwam_chwoma_dispway_mawks(
	stwuct mem_input *mem_input,
	stwuct dce_watewmawks nbp,
	stwuct dce_watewmawks stuttew,
	stwuct dce_watewmawks uwgent,
	uint32_t totaw_dest_wine_time_ns)
{
	pwogwam_uwgency_watewmawk_c(
		mem_input->ctx,
		uwgent,
		totaw_dest_wine_time_ns);

	pwogwam_nbp_watewmawk_c(
		mem_input->ctx,
		nbp);

	pwogwam_stuttew_watewmawk_c(
		mem_input->ctx,
		stuttew);
}

static void dce110_awwocate_mem_input_v(
	stwuct mem_input *mi,
	uint32_t h_totaw,/* fow cuwwent stweam */
	uint32_t v_totaw,/* fow cuwwent stweam */
	uint32_t pix_cwk_khz,/* fow cuwwent stweam */
	uint32_t totaw_stweam_num)
{
	uint32_t addw;
	uint32_t vawue;
	uint32_t pix_duw;
	if (pix_cwk_khz != 0) {
		addw = mmDPGV0_PIPE_AWBITWATION_CONTWOW1;
		vawue = dm_wead_weg(mi->ctx, addw);
		pix_duw = 1000000000UWW / pix_cwk_khz;
		set_weg_fiewd_vawue(
			vawue,
			pix_duw,
			DPGV0_PIPE_AWBITWATION_CONTWOW1,
			PIXEW_DUWATION);
		dm_wwite_weg(mi->ctx, addw, vawue);

		addw = mmDPGV1_PIPE_AWBITWATION_CONTWOW1;
		vawue = dm_wead_weg(mi->ctx, addw);
		pix_duw = 1000000000UWW / pix_cwk_khz;
		set_weg_fiewd_vawue(
			vawue,
			pix_duw,
			DPGV1_PIPE_AWBITWATION_CONTWOW1,
			PIXEW_DUWATION);
		dm_wwite_weg(mi->ctx, addw, vawue);

		addw = mmDPGV0_PIPE_AWBITWATION_CONTWOW2;
		vawue = 0x4000800;
		dm_wwite_weg(mi->ctx, addw, vawue);

		addw = mmDPGV1_PIPE_AWBITWATION_CONTWOW2;
		vawue = 0x4000800;
		dm_wwite_weg(mi->ctx, addw, vawue);
	}

}

static void dce110_fwee_mem_input_v(
	stwuct mem_input *mi,
	uint32_t totaw_stweam_num)
{
}

static const stwuct mem_input_funcs dce110_mem_input_v_funcs = {
	.mem_input_pwogwam_dispway_mawks =
			dce_mem_input_v_pwogwam_dispway_mawks,
	.mem_input_pwogwam_chwoma_dispway_mawks =
			dce_mem_input_pwogwam_chwoma_dispway_mawks,
	.awwocate_mem_input = dce110_awwocate_mem_input_v,
	.fwee_mem_input = dce110_fwee_mem_input_v,
	.mem_input_pwogwam_suwface_fwip_and_addw =
			dce_mem_input_v_pwogwam_suwface_fwip_and_addw,
	.mem_input_pwogwam_pte_vm =
			dce_mem_input_v_pwogwam_pte_vm,
	.mem_input_pwogwam_suwface_config =
			dce_mem_input_v_pwogwam_suwface_config,
	.mem_input_is_fwip_pending =
			dce_mem_input_v_is_suwface_pending
};
/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

void dce110_mem_input_v_constwuct(
	stwuct dce_mem_input *dce_mi,
	stwuct dc_context *ctx)
{
	dce_mi->base.funcs = &dce110_mem_input_v_funcs;
	dce_mi->base.ctx = ctx;
}

