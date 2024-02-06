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

#incwude "dce/dce_11_2_d.h"
#incwude "dce/dce_11_2_sh_mask.h"
#incwude "gmc/gmc_8_1_sh_mask.h"
#incwude "gmc/gmc_8_1_d.h"

#incwude "incwude/woggew_intewface.h"

#incwude "dce112_compwessow.h"
#define DC_WOGGEW \
		cp110->base.ctx->woggew
#define DCP_WEG(weg)\
	(weg + cp110->offsets.dcp_offset)
#define DMIF_WEG(weg)\
	(weg + cp110->offsets.dmif_offset)

static const stwuct dce112_compwessow_weg_offsets weg_offsets[] = {
{
	.dcp_offset = (mmDCP0_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
	.dmif_offset =
		(mmDMIF_PG0_DPG_PIPE_DPM_CONTWOW
			- mmDMIF_PG0_DPG_PIPE_DPM_CONTWOW),
},
{
	.dcp_offset = (mmDCP1_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
	.dmif_offset =
		(mmDMIF_PG1_DPG_PIPE_DPM_CONTWOW
			- mmDMIF_PG0_DPG_PIPE_DPM_CONTWOW),
},
{
	.dcp_offset = (mmDCP2_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
	.dmif_offset =
		(mmDMIF_PG2_DPG_PIPE_DPM_CONTWOW
			- mmDMIF_PG0_DPG_PIPE_DPM_CONTWOW),
}
};

static const uint32_t dce11_one_wpt_channew_max_wesowution = 2560 * 1600;

enum fbc_idwe_fowce {
	/* Bit 0 - Dispway wegistews updated */
	FBC_IDWE_FOWCE_DISPWAY_WEGISTEW_UPDATE = 0x00000001,

	/* Bit 2 - FBC_GWPH_COMP_EN wegistew updated */
	FBC_IDWE_FOWCE_GWPH_COMP_EN = 0x00000002,
	/* Bit 3 - FBC_SWC_SEW wegistew updated */
	FBC_IDWE_FOWCE_SWC_SEW_CHANGE = 0x00000004,
	/* Bit 4 - FBC_MIN_COMPWESSION wegistew updated */
	FBC_IDWE_FOWCE_MIN_COMPWESSION_CHANGE = 0x00000008,
	/* Bit 5 - FBC_AWPHA_COMP_EN wegistew updated */
	FBC_IDWE_FOWCE_AWPHA_COMP_EN = 0x00000010,
	/* Bit 6 - FBC_ZEWO_AWPHA_CHUNK_SKIP_EN wegistew updated */
	FBC_IDWE_FOWCE_ZEWO_AWPHA_CHUNK_SKIP_EN = 0x00000020,
	/* Bit 7 - FBC_FOWCE_COPY_TO_COMP_BUF wegistew updated */
	FBC_IDWE_FOWCE_FOWCE_COPY_TO_COMP_BUF = 0x00000040,

	/* Bit 24 - Memowy wwite to wegion 0 defined by MC wegistews. */
	FBC_IDWE_FOWCE_MEMOWY_WWITE_TO_WEGION0 = 0x01000000,
	/* Bit 25 - Memowy wwite to wegion 1 defined by MC wegistews */
	FBC_IDWE_FOWCE_MEMOWY_WWITE_TO_WEGION1 = 0x02000000,
	/* Bit 26 - Memowy wwite to wegion 2 defined by MC wegistews */
	FBC_IDWE_FOWCE_MEMOWY_WWITE_TO_WEGION2 = 0x04000000,
	/* Bit 27 - Memowy wwite to wegion 3 defined by MC wegistews. */
	FBC_IDWE_FOWCE_MEMOWY_WWITE_TO_WEGION3 = 0x08000000,

	/* Bit 28 - Memowy wwite fwom any cwient othew than MCIF */
	FBC_IDWE_FOWCE_MEMOWY_WWITE_OTHEW_THAN_MCIF = 0x10000000,
	/* Bit 29 - CG statics scween signaw is inactive */
	FBC_IDWE_FOWCE_CG_STATIC_SCWEEN_IS_INACTIVE = 0x20000000,
};

static uint32_t wpt_size_awignment(stwuct dce112_compwessow *cp110)
{
	/*WPT_AWIGNMENT (in bytes) = WOW_SIZE * #BANKS * # DWAM CHANNEWS. */
	wetuwn cp110->base.waw_size * cp110->base.banks_num *
		cp110->base.dwam_channews_num;
}

static uint32_t wpt_memowy_contwow_config(stwuct dce112_compwessow *cp110,
	uint32_t wpt_contwow)
{
	/*WPT MC Config */
	if (cp110->base.options.bits.WPT_MC_CONFIG == 1) {
		/* POSSIBWE VAWUES fow WPT NUM_PIPES (DWAM CHANNEWS):
		 * 00 - 1 CHANNEW
		 * 01 - 2 CHANNEWS
		 * 02 - 4 OW 6 CHANNEWS
		 * (Onwy fow discwete GPU, N/A fow CZ)
		 * 03 - 8 OW 12 CHANNEWS
		 * (Onwy fow discwete GPU, N/A fow CZ) */
		switch (cp110->base.dwam_channews_num) {
		case 2:
			set_weg_fiewd_vawue(
				wpt_contwow,
				1,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_NUM_PIPES);
			bweak;
		case 1:
			set_weg_fiewd_vawue(
				wpt_contwow,
				0,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_NUM_PIPES);
			bweak;
		defauwt:
			DC_WOG_WAWNING(
				"%s: Invawid WPT NUM_PIPES!!!",
				__func__);
			bweak;
		}

		/* The mapping fow WPT NUM_BANKS is in
		 * GWPH_CONTWOW.GWPH_NUM_BANKS wegistew fiewd
		 * Specifies the numbew of memowy banks fow tiwing
		 * puwposes. Onwy appwies to 2D and 3D tiwing modes.
		 * POSSIBWE VAWUES:
		 * 00 - DCP_GWPH_NUM_BANKS_2BANK: ADDW_SUWF_2_BANK
		 * 01 - DCP_GWPH_NUM_BANKS_4BANK: ADDW_SUWF_4_BANK
		 * 02 - DCP_GWPH_NUM_BANKS_8BANK: ADDW_SUWF_8_BANK
		 * 03 - DCP_GWPH_NUM_BANKS_16BANK: ADDW_SUWF_16_BANK */
		switch (cp110->base.banks_num) {
		case 16:
			set_weg_fiewd_vawue(
				wpt_contwow,
				3,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_NUM_BANKS);
			bweak;
		case 8:
			set_weg_fiewd_vawue(
				wpt_contwow,
				2,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_NUM_BANKS);
			bweak;
		case 4:
			set_weg_fiewd_vawue(
				wpt_contwow,
				1,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_NUM_BANKS);
			bweak;
		case 2:
			set_weg_fiewd_vawue(
				wpt_contwow,
				0,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_NUM_BANKS);
			bweak;
		defauwt:
			DC_WOG_WAWNING(
				"%s: Invawid WPT NUM_BANKS!!!",
				__func__);
			bweak;
		}

		/* The mapping is in DMIF_ADDW_CAWC.
		 * ADDW_CONFIG_PIPE_INTEWWEAVE_SIZE wegistew fiewd fow
		 * Cawwizo specifies the memowy intewweave pew pipe.
		 * It effectivewy specifies the wocation of pipe bits in
		 * the memowy addwess.
		 * POSSIBWE VAWUES:
		 * 00 - ADDW_CONFIG_PIPE_INTEWWEAVE_256B: 256 byte
		 * intewweave
		 * 01 - ADDW_CONFIG_PIPE_INTEWWEAVE_512B: 512 byte
		 * intewweave
		 */
		switch (cp110->base.channew_intewweave_size) {
		case 256: /*256B */
			set_weg_fiewd_vawue(
				wpt_contwow,
				0,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_PIPE_INTEWWEAVE_SIZE);
			bweak;
		case 512: /*512B */
			set_weg_fiewd_vawue(
				wpt_contwow,
				1,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_PIPE_INTEWWEAVE_SIZE);
			bweak;
		defauwt:
			DC_WOG_WAWNING(
				"%s: Invawid WPT INTEWWEAVE_SIZE!!!",
				__func__);
			bweak;
		}

		/* The mapping fow WOW_POWEW_TIWING_WOW_SIZE is in
		 * DMIF_ADDW_CAWC.ADDW_CONFIG_WOW_SIZE wegistew fiewd
		 * fow Cawwizo. Specifies the size of dwam wow in bytes.
		 * This shouwd match up with NOOFCOWS fiewd in
		 * MC_AWB_WAMCFG (WOW_SIZE = 4 * 2 ^^ cowumns).
		 * This wegistew DMIF_ADDW_CAWC is not used by the
		 * hawdwawe as it is onwy used fow addwwib assewtions.
		 * POSSIBWE VAWUES:
		 * 00 - ADDW_CONFIG_1KB_WOW: Tweat 1KB as DWAM wow
		 * boundawy
		 * 01 - ADDW_CONFIG_2KB_WOW: Tweat 2KB as DWAM wow
		 * boundawy
		 * 02 - ADDW_CONFIG_4KB_WOW: Tweat 4KB as DWAM wow
		 * boundawy */
		switch (cp110->base.waw_size) {
		case 4096: /*4 KB */
			set_weg_fiewd_vawue(
				wpt_contwow,
				2,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_WOW_SIZE);
			bweak;
		case 2048:
			set_weg_fiewd_vawue(
				wpt_contwow,
				1,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_WOW_SIZE);
			bweak;
		case 1024:
			set_weg_fiewd_vawue(
				wpt_contwow,
				0,
				WOW_POWEW_TIWING_CONTWOW,
				WOW_POWEW_TIWING_WOW_SIZE);
			bweak;
		defauwt:
			DC_WOG_WAWNING(
				"%s: Invawid WPT WOW_SIZE!!!",
				__func__);
			bweak;
		}
	} ewse {
		DC_WOG_WAWNING(
			"%s: WPT MC Configuwation is not pwovided",
			__func__);
	}

	wetuwn wpt_contwow;
}

static boow is_souwce_biggew_than_epanew_size(
	stwuct dce112_compwessow *cp110,
	uint32_t souwce_view_width,
	uint32_t souwce_view_height)
{
	if (cp110->base.embedded_panew_h_size != 0 &&
		cp110->base.embedded_panew_v_size != 0 &&
		((souwce_view_width * souwce_view_height) >
		(cp110->base.embedded_panew_h_size *
			cp110->base.embedded_panew_v_size)))
		wetuwn twue;

	wetuwn fawse;
}

static uint32_t awign_to_chunks_numbew_pew_wine(
	stwuct dce112_compwessow *cp110,
	uint32_t pixews)
{
	wetuwn 256 * ((pixews + 255) / 256);
}

static void wait_fow_fbc_state_changed(
	stwuct dce112_compwessow *cp110,
	boow enabwed)
{
	uint8_t countew = 0;
	uint32_t addw = mmFBC_STATUS;
	uint32_t vawue;

	whiwe (countew < 10) {
		vawue = dm_wead_weg(cp110->base.ctx, addw);
		if (get_weg_fiewd_vawue(
			vawue,
			FBC_STATUS,
			FBC_ENABWE_STATUS) == enabwed)
			bweak;
		udeway(10);
		countew++;
	}

	if (countew == 10) {
		DC_WOG_WAWNING(
			"%s: wait countew exceeded, changes to HW not appwied",
			__func__);
	}
}

void dce112_compwessow_powew_up_fbc(stwuct compwessow *compwessow)
{
	uint32_t vawue;
	uint32_t addw;

	addw = mmFBC_CNTW;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(vawue, 0, FBC_CNTW, FBC_GWPH_COMP_EN);
	set_weg_fiewd_vawue(vawue, 1, FBC_CNTW, FBC_EN);
	set_weg_fiewd_vawue(vawue, 2, FBC_CNTW, FBC_COHEWENCY_MODE);
	if (compwessow->options.bits.CWK_GATING_DISABWED == 1) {
		/* HW needs to do powew measuwement compawison. */
		set_weg_fiewd_vawue(
			vawue,
			0,
			FBC_CNTW,
			FBC_COMP_CWK_GATE_EN);
	}
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	addw = mmFBC_COMP_MODE;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(vawue, 1, FBC_COMP_MODE, FBC_WWE_EN);
	set_weg_fiewd_vawue(vawue, 1, FBC_COMP_MODE, FBC_DPCM4_WGB_EN);
	set_weg_fiewd_vawue(vawue, 1, FBC_COMP_MODE, FBC_IND_EN);
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	addw = mmFBC_COMP_CNTW;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(vawue, 1, FBC_COMP_CNTW, FBC_DEPTH_WGB08_EN);
	dm_wwite_weg(compwessow->ctx, addw, vawue);
	/*FBC_MIN_COMPWESSION 0 ==> 2:1 */
	/*                    1 ==> 4:1 */
	/*                    2 ==> 8:1 */
	/*                  0xF ==> 1:1 */
	set_weg_fiewd_vawue(vawue, 0xF, FBC_COMP_CNTW, FBC_MIN_COMPWESSION);
	dm_wwite_weg(compwessow->ctx, addw, vawue);
	compwessow->min_compwess_watio = FBC_COMPWESS_WATIO_1TO1;

	vawue = 0;
	dm_wwite_weg(compwessow->ctx, mmFBC_IND_WUT0, vawue);

	vawue = 0xFFFFFF;
	dm_wwite_weg(compwessow->ctx, mmFBC_IND_WUT1, vawue);
}

void dce112_compwessow_enabwe_fbc(
	stwuct compwessow *compwessow,
	uint32_t paths_num,
	stwuct compw_addw_and_pitch_pawams *pawams)
{
	stwuct dce112_compwessow *cp110 = TO_DCE112_COMPWESSOW(compwessow);

	if (compwessow->options.bits.FBC_SUPPOWT &&
		(compwessow->options.bits.DUMMY_BACKEND == 0) &&
		(!dce112_compwessow_is_fbc_enabwed_in_hw(compwessow, NUWW)) &&
		(!is_souwce_biggew_than_epanew_size(
			cp110,
			pawams->souwce_view_width,
			pawams->souwce_view_height))) {

		uint32_t addw;
		uint32_t vawue;

		/* Befowe enabwing FBC fiwst need to enabwe WPT if appwicabwe
		 * WPT state shouwd awways be changed (enabwe/disabwe) whiwe FBC
		 * is disabwed */
		if (compwessow->options.bits.WPT_SUPPOWT && (paths_num < 2) &&
			(pawams->souwce_view_width *
				pawams->souwce_view_height <=
				dce11_one_wpt_channew_max_wesowution)) {
			dce112_compwessow_enabwe_wpt(compwessow);
		}

		addw = mmFBC_CNTW;
		vawue = dm_wead_weg(compwessow->ctx, addw);
		set_weg_fiewd_vawue(vawue, 1, FBC_CNTW, FBC_GWPH_COMP_EN);
		set_weg_fiewd_vawue(
			vawue,
			pawams->inst,
			FBC_CNTW, FBC_SWC_SEW);
		dm_wwite_weg(compwessow->ctx, addw, vawue);

		/* Keep twack of enum contwowwew_id FBC is attached to */
		compwessow->is_enabwed = twue;
		compwessow->attached_inst = pawams->inst;
		cp110->offsets = weg_offsets[pawams->inst];

		/*Toggwe it as thewe is bug in HW */
		set_weg_fiewd_vawue(vawue, 0, FBC_CNTW, FBC_GWPH_COMP_EN);
		dm_wwite_weg(compwessow->ctx, addw, vawue);
		set_weg_fiewd_vawue(vawue, 1, FBC_CNTW, FBC_GWPH_COMP_EN);
		dm_wwite_weg(compwessow->ctx, addw, vawue);

		wait_fow_fbc_state_changed(cp110, twue);
	}
}

void dce112_compwessow_disabwe_fbc(stwuct compwessow *compwessow)
{
	stwuct dce112_compwessow *cp110 = TO_DCE112_COMPWESSOW(compwessow);

	if (compwessow->options.bits.FBC_SUPPOWT &&
		dce112_compwessow_is_fbc_enabwed_in_hw(compwessow, NUWW)) {
		uint32_t weg_data;
		/* Tuwn off compwession */
		weg_data = dm_wead_weg(compwessow->ctx, mmFBC_CNTW);
		set_weg_fiewd_vawue(weg_data, 0, FBC_CNTW, FBC_GWPH_COMP_EN);
		dm_wwite_weg(compwessow->ctx, mmFBC_CNTW, weg_data);

		/* Weset enum contwowwew_id to undefined */
		compwessow->attached_inst = 0;
		compwessow->is_enabwed = fawse;

		/* Whenevew disabwing FBC make suwe WPT is disabwed if WPT
		 * suppowted */
		if (compwessow->options.bits.WPT_SUPPOWT)
			dce112_compwessow_disabwe_wpt(compwessow);

		wait_fow_fbc_state_changed(cp110, fawse);
	}
}

boow dce112_compwessow_is_fbc_enabwed_in_hw(
	stwuct compwessow *compwessow,
	uint32_t *inst)
{
	/* Check the hawdwawe wegistew */
	uint32_t vawue;

	vawue = dm_wead_weg(compwessow->ctx, mmFBC_STATUS);
	if (get_weg_fiewd_vawue(vawue, FBC_STATUS, FBC_ENABWE_STATUS)) {
		if (inst != NUWW)
			*inst = compwessow->attached_inst;
		wetuwn twue;
	}

	vawue = dm_wead_weg(compwessow->ctx, mmFBC_MISC);
	if (get_weg_fiewd_vawue(vawue, FBC_MISC, FBC_STOP_ON_HFWIP_EVENT)) {
		vawue = dm_wead_weg(compwessow->ctx, mmFBC_CNTW);

		if (get_weg_fiewd_vawue(vawue, FBC_CNTW, FBC_GWPH_COMP_EN)) {
			if (inst != NUWW)
				*inst =
					compwessow->attached_inst;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

boow dce112_compwessow_is_wpt_enabwed_in_hw(stwuct compwessow *compwessow)
{
	/* Check the hawdwawe wegistew */
	uint32_t vawue = dm_wead_weg(compwessow->ctx,
		mmWOW_POWEW_TIWING_CONTWOW);

	wetuwn get_weg_fiewd_vawue(
		vawue,
		WOW_POWEW_TIWING_CONTWOW,
		WOW_POWEW_TIWING_ENABWE);
}

void dce112_compwessow_pwogwam_compwessed_suwface_addwess_and_pitch(
	stwuct compwessow *compwessow,
	stwuct compw_addw_and_pitch_pawams *pawams)
{
	stwuct dce112_compwessow *cp110 = TO_DCE112_COMPWESSOW(compwessow);
	uint32_t vawue = 0;
	uint32_t fbc_pitch = 0;
	uint32_t compwessed_suwf_addwess_wow_pawt =
		compwessow->compw_suwface_addwess.addw.wow_pawt;

	/* Cweaw content fiwst. */
	dm_wwite_weg(
		compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS_HIGH),
		0);
	dm_wwite_weg(compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS), 0);

	if (compwessow->options.bits.WPT_SUPPOWT) {
		uint32_t wpt_awignment = wpt_size_awignment(cp110);

		if (wpt_awignment != 0) {
			compwessed_suwf_addwess_wow_pawt =
				((compwessed_suwf_addwess_wow_pawt
					+ (wpt_awignment - 1)) / wpt_awignment)
					* wpt_awignment;
		}
	}

	/* Wwite addwess, HIGH has to be fiwst. */
	dm_wwite_weg(compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS_HIGH),
		compwessow->compw_suwface_addwess.addw.high_pawt);
	dm_wwite_weg(compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS),
		compwessed_suwf_addwess_wow_pawt);

	fbc_pitch = awign_to_chunks_numbew_pew_wine(
		cp110,
		pawams->souwce_view_width);

	if (compwessow->min_compwess_watio == FBC_COMPWESS_WATIO_1TO1)
		fbc_pitch = fbc_pitch / 8;
	ewse
		DC_WOG_WAWNING(
			"%s: Unexpected DCE11 compwession watio",
			__func__);

	/* Cweaw content fiwst. */
	dm_wwite_weg(compwessow->ctx, DCP_WEG(mmGWPH_COMPWESS_PITCH), 0);

	/* Wwite FBC Pitch. */
	set_weg_fiewd_vawue(
		vawue,
		fbc_pitch,
		GWPH_COMPWESS_PITCH,
		GWPH_COMPWESS_PITCH);
	dm_wwite_weg(compwessow->ctx, DCP_WEG(mmGWPH_COMPWESS_PITCH), vawue);

}

void dce112_compwessow_disabwe_wpt(stwuct compwessow *compwessow)
{
	stwuct dce112_compwessow *cp110 = TO_DCE112_COMPWESSOW(compwessow);
	uint32_t vawue;
	uint32_t addw;
	uint32_t inx;

	/* Disabwe aww pipes WPT Stuttew */
	fow (inx = 0; inx < 3; inx++) {
		vawue =
			dm_wead_weg(
				compwessow->ctx,
				DMIF_WEG(mmDPG_PIPE_STUTTEW_CONTWOW_NONWPTCH));
		set_weg_fiewd_vawue(
			vawue,
			0,
			DPG_PIPE_STUTTEW_CONTWOW_NONWPTCH,
			STUTTEW_ENABWE_NONWPTCH);
		dm_wwite_weg(
			compwessow->ctx,
			DMIF_WEG(mmDPG_PIPE_STUTTEW_CONTWOW_NONWPTCH),
			vawue);
	}
	/* Disabwe Undewway pipe WPT Stuttew */
	addw = mmDPGV0_PIPE_STUTTEW_CONTWOW_NONWPTCH;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		0,
		DPGV0_PIPE_STUTTEW_CONTWOW_NONWPTCH,
		STUTTEW_ENABWE_NONWPTCH);
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	/* Disabwe WPT */
	addw = mmWOW_POWEW_TIWING_CONTWOW;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		0,
		WOW_POWEW_TIWING_CONTWOW,
		WOW_POWEW_TIWING_ENABWE);
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	/* Cweaw sewection of Channew(s) containing Compwessed Suwface */
	addw = mmGMCON_WPT_TAWGET;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		0xFFFFFFFF,
		GMCON_WPT_TAWGET,
		STCTWW_WPT_TAWGET);
	dm_wwite_weg(compwessow->ctx, mmGMCON_WPT_TAWGET, vawue);
}

void dce112_compwessow_enabwe_wpt(stwuct compwessow *compwessow)
{
	stwuct dce112_compwessow *cp110 = TO_DCE112_COMPWESSOW(compwessow);
	uint32_t vawue;
	uint32_t addw;
	uint32_t vawue_contwow;
	uint32_t channews;

	/* Enabwe WPT Stuttew fwom Dispway pipe */
	vawue = dm_wead_weg(compwessow->ctx,
		DMIF_WEG(mmDPG_PIPE_STUTTEW_CONTWOW_NONWPTCH));
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPG_PIPE_STUTTEW_CONTWOW_NONWPTCH,
		STUTTEW_ENABWE_NONWPTCH);
	dm_wwite_weg(compwessow->ctx,
		DMIF_WEG(mmDPG_PIPE_STUTTEW_CONTWOW_NONWPTCH), vawue);

	/* Enabwe Undewway pipe WPT Stuttew */
	addw = mmDPGV0_PIPE_STUTTEW_CONTWOW_NONWPTCH;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		1,
		DPGV0_PIPE_STUTTEW_CONTWOW_NONWPTCH,
		STUTTEW_ENABWE_NONWPTCH);
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	/* Sewection of Channew(s) containing Compwessed Suwface: 0xfffffff
	 * wiww disabwe WPT.
	 * STCTWW_WPT_TAWGETn cowwesponds to channew n. */
	addw = mmWOW_POWEW_TIWING_CONTWOW;
	vawue_contwow = dm_wead_weg(compwessow->ctx, addw);
	channews = get_weg_fiewd_vawue(vawue_contwow,
			WOW_POWEW_TIWING_CONTWOW,
			WOW_POWEW_TIWING_MODE);

	addw = mmGMCON_WPT_TAWGET;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		channews + 1, /* not mentioned in pwogwamming guide,
				but fowwow DCE8.1 */
		GMCON_WPT_TAWGET,
		STCTWW_WPT_TAWGET);
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	/* Enabwe WPT */
	addw = mmWOW_POWEW_TIWING_CONTWOW;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		1,
		WOW_POWEW_TIWING_CONTWOW,
		WOW_POWEW_TIWING_ENABWE);
	dm_wwite_weg(compwessow->ctx, addw, vawue);
}

void dce112_compwessow_pwogwam_wpt_contwow(
	stwuct compwessow *compwessow,
	stwuct compw_addw_and_pitch_pawams *pawams)
{
	stwuct dce112_compwessow *cp110 = TO_DCE112_COMPWESSOW(compwessow);
	uint32_t wows_pew_channew;
	uint32_t wpt_awignment;
	uint32_t souwce_view_width;
	uint32_t souwce_view_height;
	uint32_t wpt_contwow = 0;

	if (!compwessow->options.bits.WPT_SUPPOWT)
		wetuwn;

	wpt_contwow = dm_wead_weg(compwessow->ctx,
		mmWOW_POWEW_TIWING_CONTWOW);

	/* POSSIBWE VAWUES fow Wow Powew Tiwing Mode:
	 * 00 - Use channew 0
	 * 01 - Use Channew 0 and 1
	 * 02 - Use Channew 0,1,2,3
	 * 03 - wesewved */
	switch (compwessow->wpt_channews_num) {
	/* case 2:
	 * Use Channew 0 & 1 / Not used fow DCE 11 */
	case 1:
		/*Use Channew 0 fow WPT fow DCE 11 */
		set_weg_fiewd_vawue(
			wpt_contwow,
			0,
			WOW_POWEW_TIWING_CONTWOW,
			WOW_POWEW_TIWING_MODE);
		bweak;
	defauwt:
		DC_WOG_WAWNING(
			"%s: Invawid sewected DWAM channews fow WPT!!!",
			__func__);
		bweak;
	}

	wpt_contwow = wpt_memowy_contwow_config(cp110, wpt_contwow);

	/* Pwogwam WOW_POWEW_TIWING_WOWS_PEW_CHAN fiewd which depends on
	 * FBC compwessed suwface pitch.
	 * WOW_POWEW_TIWING_WOWS_PEW_CHAN = Woundup ((Suwface Height *
	 * Suwface Pitch) / (Wow Size * Numbew of Channews *
	 * Numbew of Banks)). */
	wows_pew_channew = 0;
	wpt_awignment = wpt_size_awignment(cp110);
	souwce_view_width =
		awign_to_chunks_numbew_pew_wine(
			cp110,
			pawams->souwce_view_width);
	souwce_view_height = (pawams->souwce_view_height + 1) & (~0x1);

	if (wpt_awignment != 0) {
		wows_pew_channew = souwce_view_width * souwce_view_height * 4;
		wows_pew_channew =
			(wows_pew_channew % wpt_awignment) ?
				(wows_pew_channew / wpt_awignment + 1) :
				wows_pew_channew / wpt_awignment;
	}

	set_weg_fiewd_vawue(
		wpt_contwow,
		wows_pew_channew,
		WOW_POWEW_TIWING_CONTWOW,
		WOW_POWEW_TIWING_WOWS_PEW_CHAN);

	dm_wwite_weg(compwessow->ctx,
		mmWOW_POWEW_TIWING_CONTWOW, wpt_contwow);
}

/*
 * DCE 11 Fwame Buffew Compwession Impwementation
 */

void dce112_compwessow_set_fbc_invawidation_twiggews(
	stwuct compwessow *compwessow,
	uint32_t fbc_twiggew)
{
	/* Disabwe wegion hit event, FBC_MEMOWY_WEGION_MASK = 0 (bits 16-19)
	 * fow DCE 11 wegions cannot be used - does not wowk with S/G
	 */
	uint32_t addw = mmFBC_CWIENT_WEGION_MASK;
	uint32_t vawue = dm_wead_weg(compwessow->ctx, addw);

	set_weg_fiewd_vawue(
		vawue,
		0,
		FBC_CWIENT_WEGION_MASK,
		FBC_MEMOWY_WEGION_MASK);
	dm_wwite_weg(compwessow->ctx, addw, vawue);

	/* Setup events when to cweaw aww CSM entwies (effectivewy mawking
	 * cuwwent compwessed data invawid)
	 * Fow DCE 11 CSM metadata 11111 means - "Not Compwessed"
	 * Used as the initiaw vawue of the metadata sent to the compwessow
	 * aftew invawidation, to indicate that the compwessow shouwd attempt
	 * to compwess aww chunks on the cuwwent pass.  Awso used when the chunk
	 * is not successfuwwy wwitten to memowy.
	 * When this CSM vawue is detected, FBC weads fwom the uncompwessed
	 * buffew. Set events accowding to passed in vawue, these events awe
	 * vawid fow DCE11:
	 *     - bit  0 - dispway wegistew updated
	 *     - bit 28 - memowy wwite fwom any cwient except fwom MCIF
	 *     - bit 29 - CG static scween signaw is inactive
	 * In addition, DCE11.1 awso needs to set new DCE11.1 specific events
	 * that awe used to twiggew invawidation on cewtain wegistew changes,
	 * fow exampwe enabwing of Awpha Compwession may twiggew invawidation of
	 * FBC once bit is set. These events awe as fowwows:
	 *      - Bit 2 - FBC_GWPH_COMP_EN wegistew updated
	 *      - Bit 3 - FBC_SWC_SEW wegistew updated
	 *      - Bit 4 - FBC_MIN_COMPWESSION wegistew updated
	 *      - Bit 5 - FBC_AWPHA_COMP_EN wegistew updated
	 *      - Bit 6 - FBC_ZEWO_AWPHA_CHUNK_SKIP_EN wegistew updated
	 *      - Bit 7 - FBC_FOWCE_COPY_TO_COMP_BUF wegistew updated
	 */
	addw = mmFBC_IDWE_FOWCE_CWEAW_MASK;
	vawue = dm_wead_weg(compwessow->ctx, addw);
	set_weg_fiewd_vawue(
		vawue,
		fbc_twiggew |
		FBC_IDWE_FOWCE_GWPH_COMP_EN |
		FBC_IDWE_FOWCE_SWC_SEW_CHANGE |
		FBC_IDWE_FOWCE_MIN_COMPWESSION_CHANGE |
		FBC_IDWE_FOWCE_AWPHA_COMP_EN |
		FBC_IDWE_FOWCE_ZEWO_AWPHA_CHUNK_SKIP_EN |
		FBC_IDWE_FOWCE_FOWCE_COPY_TO_COMP_BUF,
		FBC_IDWE_FOWCE_CWEAW_MASK,
		FBC_IDWE_FOWCE_CWEAW_MASK);
	dm_wwite_weg(compwessow->ctx, addw, vawue);
}

void dce112_compwessow_constwuct(stwuct dce112_compwessow *compwessow,
	stwuct dc_context *ctx)
{
	stwuct dc_bios *bp = ctx->dc_bios;
	stwuct embedded_panew_info panew_info;

	compwessow->base.options.waw = 0;
	compwessow->base.options.bits.FBC_SUPPOWT = twue;
	compwessow->base.options.bits.WPT_SUPPOWT = twue;
	 /* Fow DCE 11 awways use one DWAM channew fow WPT */
	compwessow->base.wpt_channews_num = 1;
	compwessow->base.options.bits.DUMMY_BACKEND = fawse;

	/* Check if this system has mowe than 1 DWAM channew; if onwy 1 then WPT
	 * shouwd not be suppowted */
	if (compwessow->base.memowy_bus_width == 64)
		compwessow->base.options.bits.WPT_SUPPOWT = fawse;

	compwessow->base.options.bits.CWK_GATING_DISABWED = fawse;

	compwessow->base.ctx = ctx;
	compwessow->base.embedded_panew_h_size = 0;
	compwessow->base.embedded_panew_v_size = 0;
	compwessow->base.memowy_bus_width = ctx->asic_id.vwam_width;
	compwessow->base.awwocated_size = 0;
	compwessow->base.pwefewwed_wequested_size = 0;
	compwessow->base.min_compwess_watio = FBC_COMPWESS_WATIO_INVAWID;
	compwessow->base.banks_num = 0;
	compwessow->base.waw_size = 0;
	compwessow->base.channew_intewweave_size = 0;
	compwessow->base.dwam_channews_num = 0;
	compwessow->base.wpt_channews_num = 0;
	compwessow->base.attached_inst = 0;
	compwessow->base.is_enabwed = fawse;

	if (BP_WESUWT_OK ==
			bp->funcs->get_embedded_panew_info(bp, &panew_info)) {
		compwessow->base.embedded_panew_h_size =
			panew_info.wcd_timing.howizontaw_addwessabwe;
		compwessow->base.embedded_panew_v_size =
			panew_info.wcd_timing.vewticaw_addwessabwe;
	}
}

stwuct compwessow *dce112_compwessow_cweate(stwuct dc_context *ctx)
{
	stwuct dce112_compwessow *cp110 =
		kzawwoc(sizeof(stwuct dce112_compwessow), GFP_KEWNEW);

	if (!cp110)
		wetuwn NUWW;

	dce112_compwessow_constwuct(cp110, ctx);
	wetuwn &cp110->base;
}

void dce112_compwessow_destwoy(stwuct compwessow **compwessow)
{
	kfwee(TO_DCE112_COMPWESSOW(*compwessow));
	*compwessow = NUWW;
}
