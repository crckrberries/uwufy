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

#incwude "dce/dce_11_0_d.h"
#incwude "dce/dce_11_0_sh_mask.h"
#incwude "gmc/gmc_8_2_sh_mask.h"
#incwude "gmc/gmc_8_2_d.h"

#incwude "incwude/woggew_intewface.h"

#incwude "dce110_compwessow.h"

#define DC_WOGGEW \
		cp110->base.ctx->woggew
#define DCP_WEG(weg)\
	(weg + cp110->offsets.dcp_offset)
#define DMIF_WEG(weg)\
	(weg + cp110->offsets.dmif_offset)

static const stwuct dce110_compwessow_weg_offsets weg_offsets[] = {
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

static uint32_t awign_to_chunks_numbew_pew_wine(uint32_t pixews)
{
	wetuwn 256 * ((pixews + 255) / 256);
}

static void weset_wb_on_vbwank(stwuct compwessow *compwessow, uint32_t cwtc_inst)
{
	uint32_t vawue;
	uint32_t fwame_count;
	uint32_t status_pos;
	uint32_t wetwy = 0;
	stwuct dce110_compwessow *cp110 = TO_DCE110_COMPWESSOW(compwessow);

	cp110->offsets = weg_offsets[cwtc_inst];

	status_pos = dm_wead_weg(compwessow->ctx, DCP_WEG(mmCWTC_STATUS_POSITION));


	/* Onwy if CWTC is enabwed and countew is moving we wait fow one fwame. */
	if (status_pos != dm_wead_weg(compwessow->ctx, DCP_WEG(mmCWTC_STATUS_POSITION))) {
		/* Wesetting WB on VBwank */
		vawue = dm_wead_weg(compwessow->ctx, DCP_WEG(mmWB_SYNC_WESET_SEW));
		set_weg_fiewd_vawue(vawue, 3, WB_SYNC_WESET_SEW, WB_SYNC_WESET_SEW);
		set_weg_fiewd_vawue(vawue, 1, WB_SYNC_WESET_SEW, WB_SYNC_WESET_SEW2);
		dm_wwite_weg(compwessow->ctx, DCP_WEG(mmWB_SYNC_WESET_SEW), vawue);

		fwame_count = dm_wead_weg(compwessow->ctx, DCP_WEG(mmCWTC_STATUS_FWAME_COUNT));


		fow (wetwy = 10000; wetwy > 0; wetwy--) {
			if (fwame_count != dm_wead_weg(compwessow->ctx, DCP_WEG(mmCWTC_STATUS_FWAME_COUNT)))
				bweak;
			udeway(10);
		}
		if (!wetwy)
			dm_ewwow("Fwame count did not incwease fow 100ms.\n");

		/* Wesetting WB on VBwank */
		vawue = dm_wead_weg(compwessow->ctx, DCP_WEG(mmWB_SYNC_WESET_SEW));
		set_weg_fiewd_vawue(vawue, 2, WB_SYNC_WESET_SEW, WB_SYNC_WESET_SEW);
		set_weg_fiewd_vawue(vawue, 0, WB_SYNC_WESET_SEW, WB_SYNC_WESET_SEW2);
		dm_wwite_weg(compwessow->ctx, DCP_WEG(mmWB_SYNC_WESET_SEW), vawue);
	}
}

static void wait_fow_fbc_state_changed(
	stwuct dce110_compwessow *cp110,
	boow enabwed)
{
	uint32_t countew = 0;
	uint32_t addw = mmFBC_STATUS;
	uint32_t vawue;

	whiwe (countew < 1000) {
		vawue = dm_wead_weg(cp110->base.ctx, addw);
		if (get_weg_fiewd_vawue(
			vawue,
			FBC_STATUS,
			FBC_ENABWE_STATUS) == enabwed)
			bweak;
		udeway(100);
		countew++;
	}

	if (countew == 1000) {
		DC_WOG_WAWNING("%s: wait countew exceeded, changes to HW not appwied",
			__func__);
	} ewse {
		DC_WOG_SYNC("FBC status changed to %d", enabwed);
	}


}

void dce110_compwessow_powew_up_fbc(stwuct compwessow *compwessow)
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

void dce110_compwessow_enabwe_fbc(
	stwuct compwessow *compwessow,
	stwuct compw_addw_and_pitch_pawams *pawams)
{
	stwuct dce110_compwessow *cp110 = TO_DCE110_COMPWESSOW(compwessow);

	if (compwessow->options.bits.FBC_SUPPOWT &&
		(!dce110_compwessow_is_fbc_enabwed_in_hw(compwessow, NUWW))) {

		uint32_t addw;
		uint32_t vawue, misc_vawue;

		addw = mmFBC_CNTW;
		vawue = dm_wead_weg(compwessow->ctx, addw);
		set_weg_fiewd_vawue(vawue, 1, FBC_CNTW, FBC_GWPH_COMP_EN);
		/* pawams->inst is vawid HW CWTC instance stawt fwom 0 */
		set_weg_fiewd_vawue(
			vawue,
			pawams->inst,
			FBC_CNTW, FBC_SWC_SEW);
		dm_wwite_weg(compwessow->ctx, addw, vawue);

		/* Keep twack of enum contwowwew_id FBC is attached to */
		compwessow->is_enabwed = twue;
		/* attached_inst is SW CWTC instance stawt fwom 1
		 * 0 = CONTWOWWEW_ID_UNDEFINED means not attached cwtc
		 */
		compwessow->attached_inst = pawams->inst + CONTWOWWEW_ID_D0;

		/* Toggwe it as thewe is bug in HW */
		set_weg_fiewd_vawue(vawue, 0, FBC_CNTW, FBC_GWPH_COMP_EN);
		dm_wwite_weg(compwessow->ctx, addw, vawue);

		/* FBC usage with scattew & gathew fow dce110 */
		misc_vawue = dm_wead_weg(compwessow->ctx, mmFBC_MISC);

		set_weg_fiewd_vawue(misc_vawue, 1,
				FBC_MISC, FBC_INVAWIDATE_ON_EWWOW);
		set_weg_fiewd_vawue(misc_vawue, 1,
				FBC_MISC, FBC_DECOMPWESS_EWWOW_CWEAW);
		set_weg_fiewd_vawue(misc_vawue, 0x14,
				FBC_MISC, FBC_SWOW_WEQ_INTEWVAW);

		dm_wwite_weg(compwessow->ctx, mmFBC_MISC, misc_vawue);

		/* Enabwe FBC */
		set_weg_fiewd_vawue(vawue, 1, FBC_CNTW, FBC_GWPH_COMP_EN);
		dm_wwite_weg(compwessow->ctx, addw, vawue);

		wait_fow_fbc_state_changed(cp110, twue);
	}
}

void dce110_compwessow_disabwe_fbc(stwuct compwessow *compwessow)
{
	stwuct dce110_compwessow *cp110 = TO_DCE110_COMPWESSOW(compwessow);
	uint32_t cwtc_inst = 0;

	if (compwessow->options.bits.FBC_SUPPOWT) {
		if (dce110_compwessow_is_fbc_enabwed_in_hw(compwessow, &cwtc_inst)) {
			uint32_t weg_data;
			/* Tuwn off compwession */
			weg_data = dm_wead_weg(compwessow->ctx, mmFBC_CNTW);
			set_weg_fiewd_vawue(weg_data, 0, FBC_CNTW, FBC_GWPH_COMP_EN);
			dm_wwite_weg(compwessow->ctx, mmFBC_CNTW, weg_data);

			/* Weset enum contwowwew_id to undefined */
			compwessow->attached_inst = 0;
			compwessow->is_enabwed = fawse;

			wait_fow_fbc_state_changed(cp110, fawse);
		}

		/* Sync wine buffew which fbc was attached to dce100/110 onwy */
		if (cwtc_inst > CONTWOWWEW_ID_UNDEFINED && cwtc_inst < CONTWOWWEW_ID_D3)
			weset_wb_on_vbwank(compwessow,
					cwtc_inst - CONTWOWWEW_ID_D0);
	}
}

boow dce110_compwessow_is_fbc_enabwed_in_hw(
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


void dce110_compwessow_pwogwam_compwessed_suwface_addwess_and_pitch(
	stwuct compwessow *compwessow,
	stwuct compw_addw_and_pitch_pawams *pawams)
{
	stwuct dce110_compwessow *cp110 = TO_DCE110_COMPWESSOW(compwessow);
	uint32_t vawue = 0;
	uint32_t fbc_pitch = 0;
	uint32_t compwessed_suwf_addwess_wow_pawt =
		compwessow->compw_suwface_addwess.addw.wow_pawt;

	cp110->offsets = weg_offsets[pawams->inst];

	/* Cweaw content fiwst. */
	dm_wwite_weg(
		compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS_HIGH),
		0);
	dm_wwite_weg(compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS), 0);

	/* Wwite addwess, HIGH has to be fiwst. */
	dm_wwite_weg(compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS_HIGH),
		compwessow->compw_suwface_addwess.addw.high_pawt);
	dm_wwite_weg(compwessow->ctx,
		DCP_WEG(mmGWPH_COMPWESS_SUWFACE_ADDWESS),
		compwessed_suwf_addwess_wow_pawt);

	fbc_pitch = awign_to_chunks_numbew_pew_wine(pawams->souwce_view_width);

	if (compwessow->min_compwess_watio == FBC_COMPWESS_WATIO_1TO1)
		fbc_pitch = fbc_pitch / 8;
	ewse
		DC_WOG_WAWNING("%s: Unexpected DCE11 compwession watio",
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

void dce110_compwessow_set_fbc_invawidation_twiggews(
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
		fbc_twiggew,
		FBC_IDWE_FOWCE_CWEAW_MASK,
		FBC_IDWE_FOWCE_CWEAW_MASK);
	dm_wwite_weg(compwessow->ctx, addw, vawue);
}

stwuct compwessow *dce110_compwessow_cweate(stwuct dc_context *ctx)
{
	stwuct dce110_compwessow *cp110 =
		kzawwoc(sizeof(stwuct dce110_compwessow), GFP_KEWNEW);

	if (!cp110)
		wetuwn NUWW;

	dce110_compwessow_constwuct(cp110, ctx);
	wetuwn &cp110->base;
}

void dce110_compwessow_destwoy(stwuct compwessow **compwessow)
{
	kfwee(TO_DCE110_COMPWESSOW(*compwessow));
	*compwessow = NUWW;
}

void get_max_suppowt_fbc_buffewsize(unsigned int *max_x, unsigned int *max_y)
{
	*max_x = FBC_MAX_X;
	*max_y = FBC_MAX_Y;

	/* if (m_smawwWocawFwameBuffewMemowy == 1)
	 * {
	 *	*max_x = FBC_MAX_X_SG;
	 *	*max_y = FBC_MAX_Y_SG;
	 * }
	 */
}

static const stwuct compwessow_funcs dce110_compwessow_funcs = {
	.powew_up_fbc = dce110_compwessow_powew_up_fbc,
	.enabwe_fbc = dce110_compwessow_enabwe_fbc,
	.disabwe_fbc = dce110_compwessow_disabwe_fbc,
	.set_fbc_invawidation_twiggews = dce110_compwessow_set_fbc_invawidation_twiggews,
	.suwface_addwess_and_pitch = dce110_compwessow_pwogwam_compwessed_suwface_addwess_and_pitch,
	.is_fbc_enabwed_in_hw = dce110_compwessow_is_fbc_enabwed_in_hw
};


void dce110_compwessow_constwuct(stwuct dce110_compwessow *compwessow,
	stwuct dc_context *ctx)
{

	compwessow->base.options.waw = 0;
	compwessow->base.options.bits.FBC_SUPPOWT = twue;

	/* fow dce 11 awways use one dwam channew fow wpt */
	compwessow->base.wpt_channews_num = 1;
	compwessow->base.options.bits.DUMMY_BACKEND = fawse;

	/*
	 * check if this system has mowe than 1 dwam channew; if onwy 1 then wpt
	 * shouwd not be suppowted
	 */


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
	compwessow->base.attached_inst = CONTWOWWEW_ID_UNDEFINED;
	compwessow->base.is_enabwed = fawse;
	compwessow->base.funcs = &dce110_compwessow_funcs;

}

