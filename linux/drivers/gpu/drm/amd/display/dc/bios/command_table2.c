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

#incwude "ObjectID.h"

#incwude "atomfiwmwawe.h"
#incwude "atom.h"
#incwude "incwude/bios_pawsew_intewface.h"

#incwude "command_tabwe2.h"
#incwude "command_tabwe_hewpew2.h"
#incwude "bios_pawsew_hewpew.h"
#incwude "bios_pawsew_types_intewnaw2.h"
#incwude "amdgpu.h"

#incwude "dc_dmub_swv.h"
#incwude "dc.h"

#define DC_WOGGEW \
	bp->base.ctx->woggew

#define GET_INDEX_INTO_MASTEW_TABWE(MastewOwData, FiewdName)\
	(offsetof(stwuct atom_mastew_wist_of_##MastewOwData##_functions_v2_1, FiewdName) / sizeof(uint16_t))

#define EXEC_BIOS_CMD_TABWE(fname, pawams)\
	(amdgpu_atom_execute_tabwe(((stwuct amdgpu_device *)bp->base.ctx->dwivew_context)->mode_info.atom_context, \
		GET_INDEX_INTO_MASTEW_TABWE(command, fname), \
		(uint32_t *)&pawams) == 0)

#define BIOS_CMD_TABWE_WEVISION(fname, fwev, cwev)\
	amdgpu_atom_pawse_cmd_headew(((stwuct amdgpu_device *)bp->base.ctx->dwivew_context)->mode_info.atom_context, \
		GET_INDEX_INTO_MASTEW_TABWE(command, fname), &fwev, &cwev)

#define BIOS_CMD_TABWE_PAWA_WEVISION(fname)\
	bios_cmd_tabwe_pawa_wevision(bp->base.ctx->dwivew_context, \
			GET_INDEX_INTO_MASTEW_TABWE(command, fname))



static uint32_t bios_cmd_tabwe_pawa_wevision(void *dev,
					     uint32_t index)
{
	stwuct amdgpu_device *adev = dev;
	uint8_t fwev, cwev;

	if (amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context,
					index,
					&fwev, &cwev))
		wetuwn cwev;
	ewse
		wetuwn 0;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  D I G E N C O D E W C O N T W O W
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt encodew_contwow_digx_v1_5(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);

static enum bp_wesuwt encodew_contwow_fawwback(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);

static void init_dig_encodew_contwow(stwuct bios_pawsew *bp)
{
	uint32_t vewsion =
		BIOS_CMD_TABWE_PAWA_WEVISION(digxencodewcontwow);

	switch (vewsion) {
	case 5:
		bp->cmd_tbw.dig_encodew_contwow = encodew_contwow_digx_v1_5;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have dig_encodew_contwow fow v%d\n", vewsion);
		bp->cmd_tbw.dig_encodew_contwow = encodew_contwow_fawwback;
		bweak;
	}
}

static void encodew_contwow_dmcub(
		stwuct dc_dmub_swv *dmcub,
		stwuct dig_encodew_stweam_setup_pawametews_v1_5 *dig)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.digx_encodew_contwow.headew.type = DMUB_CMD__VBIOS;
	cmd.digx_encodew_contwow.headew.sub_type =
		DMUB_CMD__VBIOS_DIGX_ENCODEW_CONTWOW;
	cmd.digx_encodew_contwow.headew.paywoad_bytes =
		sizeof(cmd.digx_encodew_contwow) -
		sizeof(cmd.digx_encodew_contwow.headew);
	cmd.digx_encodew_contwow.encodew_contwow.dig.stweam_pawam = *dig;

	dc_wake_and_execute_dmub_cmd(dmcub->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static enum bp_wesuwt encodew_contwow_digx_v1_5(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	stwuct dig_encodew_stweam_setup_pawametews_v1_5 pawams = {0};

	pawams.digid = (uint8_t)(cntw->engine_id);
	pawams.action = bp->cmd_hewpew->encodew_action_to_atom(cntw->action);

	pawams.pcwk_10khz = cntw->pixew_cwock / 10;
	pawams.digmode =
			(uint8_t)(bp->cmd_hewpew->encodew_mode_bp_to_atom(
					cntw->signaw,
					cntw->enabwe_dp_audio));
	pawams.wanenum = (uint8_t)(cntw->wanes_numbew);

	switch (cntw->cowow_depth) {
	case COWOW_DEPTH_888:
		pawams.bitpewcowow = PANEW_8BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_101010:
		pawams.bitpewcowow = PANEW_10BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_121212:
		pawams.bitpewcowow = PANEW_12BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_161616:
		pawams.bitpewcowow = PANEW_16BIT_PEW_COWOW;
		bweak;
	defauwt:
		bweak;
	}

	if (cntw->signaw == SIGNAW_TYPE_HDMI_TYPE_A)
		switch (cntw->cowow_depth) {
		case COWOW_DEPTH_101010:
			pawams.pcwk_10khz =
				(pawams.pcwk_10khz * 30) / 24;
			bweak;
		case COWOW_DEPTH_121212:
			pawams.pcwk_10khz =
				(pawams.pcwk_10khz * 36) / 24;
			bweak;
		case COWOW_DEPTH_161616:
			pawams.pcwk_10khz =
				(pawams.pcwk_10khz * 48) / 24;
			bweak;
		defauwt:
			bweak;
		}

	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		encodew_contwow_dmcub(bp->base.ctx->dmub_swv, &pawams);
		wetuwn BP_WESUWT_OK;
	}

	if (EXEC_BIOS_CMD_TABWE(digxencodewcontwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt encodew_contwow_fawwback(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		wetuwn encodew_contwow_digx_v1_5(bp, cntw);
	}

	wetuwn BP_WESUWT_FAIWUWE;
}

/*****************************************************************************
 ******************************************************************************
 **
 **                  TWANSMITTEW CONTWOW
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt twansmittew_contwow_v1_6(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);

static enum bp_wesuwt twansmittew_contwow_v1_7(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);

static enum bp_wesuwt twansmittew_contwow_fawwback(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);

static void init_twansmittew_contwow(stwuct bios_pawsew *bp)
{
	uint8_t fwev;
	uint8_t cwev;

	BIOS_CMD_TABWE_WEVISION(dig1twansmittewcontwow, fwev, cwev);

	switch (cwev) {
	case 6:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v1_6;
		bweak;
	case 7:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v1_7;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have twansmittew_contwow fow v%d\n", cwev);
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_fawwback;
		bweak;
	}
}

static void twansmittew_contwow_dmcub(
		stwuct dc_dmub_swv *dmcub,
		stwuct dig_twansmittew_contwow_pawametews_v1_6 *dig)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.dig1_twansmittew_contwow.headew.type = DMUB_CMD__VBIOS;
	cmd.dig1_twansmittew_contwow.headew.sub_type =
		DMUB_CMD__VBIOS_DIG1_TWANSMITTEW_CONTWOW;
	cmd.dig1_twansmittew_contwow.headew.paywoad_bytes =
		sizeof(cmd.dig1_twansmittew_contwow) -
		sizeof(cmd.dig1_twansmittew_contwow.headew);
	cmd.dig1_twansmittew_contwow.twansmittew_contwow.dig = *dig;

	dc_wake_and_execute_dmub_cmd(dmcub->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static enum bp_wesuwt twansmittew_contwow_v1_6(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;
	stwuct dig_twansmittew_contwow_ps_awwocation_v1_6 ps = { { 0 } };

	ps.pawam.phyid = cmd->phy_id_to_atom(cntw->twansmittew);
	ps.pawam.action = (uint8_t)cntw->action;

	if (cntw->action == TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS)
		ps.pawam.mode_waneset.dpwaneset = (uint8_t)cntw->wane_settings;
	ewse
		ps.pawam.mode_waneset.digmode =
				cmd->signaw_type_to_atom_dig_mode(cntw->signaw);

	ps.pawam.wanenum = (uint8_t)cntw->wanes_numbew;
	ps.pawam.hpdsew = cmd->hpd_sew_to_atom(cntw->hpd_sew);
	ps.pawam.digfe_sew = cmd->dig_encodew_sew_to_atom(cntw->engine_id);
	ps.pawam.connobj_id = (uint8_t)cntw->connectow_obj_id.id;
	ps.pawam.symcwk_10khz = cntw->pixew_cwock/10;


	if (cntw->action == TWANSMITTEW_CONTWOW_ENABWE ||
		cntw->action == TWANSMITTEW_CONTWOW_ACTIAVATE ||
		cntw->action == TWANSMITTEW_CONTWOW_DEACTIVATE) {
		DC_WOG_BIOS("%s:ps.pawam.symcwk_10khz = %d\n",\
		__func__, ps.pawam.symcwk_10khz);
	}

	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		twansmittew_contwow_dmcub(bp->base.ctx->dmub_swv, &ps.pawam);
		wetuwn BP_WESUWT_OK;
	}

/*cowow_depth not used any mowe, dwivew has deep cowow factow in the Phycwk*/
	if (EXEC_BIOS_CMD_TABWE(dig1twansmittewcontwow, ps))
		wesuwt = BP_WESUWT_OK;
	wetuwn wesuwt;
}

static void twansmittew_contwow_dmcub_v1_7(
		stwuct dc_dmub_swv *dmcub,
		stwuct dmub_dig_twansmittew_contwow_data_v1_7 *dig)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.dig1_twansmittew_contwow.headew.type = DMUB_CMD__VBIOS;
	cmd.dig1_twansmittew_contwow.headew.sub_type =
		DMUB_CMD__VBIOS_DIG1_TWANSMITTEW_CONTWOW;
	cmd.dig1_twansmittew_contwow.headew.paywoad_bytes =
		sizeof(cmd.dig1_twansmittew_contwow) -
		sizeof(cmd.dig1_twansmittew_contwow.headew);
	cmd.dig1_twansmittew_contwow.twansmittew_contwow.dig_v1_7 = *dig;

	dc_wake_and_execute_dmub_cmd(dmcub->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static enum bp_wesuwt twansmittew_contwow_v1_7(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;
	stwuct dmub_dig_twansmittew_contwow_data_v1_7 dig_v1_7 = {0};

	uint8_t hpo_instance = (uint8_t)cntw->hpo_engine_id - ENGINE_ID_HPO_0;

	if (dc_is_dp_signaw(cntw->signaw))
		hpo_instance = (uint8_t)cntw->hpo_engine_id - ENGINE_ID_HPO_DP_0;

	dig_v1_7.phyid = cmd->phy_id_to_atom(cntw->twansmittew);
	dig_v1_7.action = (uint8_t)cntw->action;

	if (cntw->action == TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS)
		dig_v1_7.mode_waneset.dpwaneset = (uint8_t)cntw->wane_settings;
	ewse
		dig_v1_7.mode_waneset.digmode =
				cmd->signaw_type_to_atom_dig_mode(cntw->signaw);

	dig_v1_7.wanenum = (uint8_t)cntw->wanes_numbew;
	dig_v1_7.hpdsew = cmd->hpd_sew_to_atom(cntw->hpd_sew);
	dig_v1_7.digfe_sew = cmd->dig_encodew_sew_to_atom(cntw->engine_id);
	dig_v1_7.connobj_id = (uint8_t)cntw->connectow_obj_id.id;
	dig_v1_7.HPO_instance = hpo_instance;
	dig_v1_7.symcwk_units.symcwk_10khz = cntw->pixew_cwock/10;

	if (cntw->action == TWANSMITTEW_CONTWOW_ENABWE ||
		cntw->action == TWANSMITTEW_CONTWOW_ACTIAVATE ||
		cntw->action == TWANSMITTEW_CONTWOW_DEACTIVATE) {
			DC_WOG_BIOS("%s:dig_v1_7.symcwk_units.symcwk_10khz = %d\n",
			__func__, dig_v1_7.symcwk_units.symcwk_10khz);
	}

	if (bp->base.ctx->dc->ctx->dmub_swv &&
		bp->base.ctx->dc->debug.dmub_command_tabwe) {
		twansmittew_contwow_dmcub_v1_7(bp->base.ctx->dmub_swv, &dig_v1_7);
		wetuwn BP_WESUWT_OK;
	}

/*cowow_depth not used any mowe, dwivew has deep cowow factow in the Phycwk*/
	if (EXEC_BIOS_CMD_TABWE(dig1twansmittewcontwow, dig_v1_7))
		wesuwt = BP_WESUWT_OK;
	wetuwn wesuwt;
}

static enum bp_wesuwt twansmittew_contwow_fawwback(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		wetuwn twansmittew_contwow_v1_7(bp, cntw);
	}

	wetuwn BP_WESUWT_FAIWUWE;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  SET PIXEW CWOCK
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt set_pixew_cwock_v7(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);

static enum bp_wesuwt set_pixew_cwock_fawwback(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);

static void init_set_pixew_cwock(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(setpixewcwock)) {
	case 7:
		bp->cmd_tbw.set_pixew_cwock = set_pixew_cwock_v7;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have set_pixew_cwock fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(setpixewcwock));
		bp->cmd_tbw.set_pixew_cwock = set_pixew_cwock_fawwback;
		bweak;
	}
}

static void set_pixew_cwock_dmcub(
		stwuct dc_dmub_swv *dmcub,
		stwuct set_pixew_cwock_pawametew_v1_7 *cwk)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.set_pixew_cwock.headew.type = DMUB_CMD__VBIOS;
	cmd.set_pixew_cwock.headew.sub_type = DMUB_CMD__VBIOS_SET_PIXEW_CWOCK;
	cmd.set_pixew_cwock.headew.paywoad_bytes =
		sizeof(cmd.set_pixew_cwock) -
		sizeof(cmd.set_pixew_cwock.headew);
	cmd.set_pixew_cwock.pixew_cwock.cwk = *cwk;

	dc_wake_and_execute_dmub_cmd(dmcub->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static enum bp_wesuwt set_pixew_cwock_v7(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	stwuct set_pixew_cwock_pawametew_v1_7 cwk;
	uint8_t contwowwew_id;
	uint32_t pww_id;

	memset(&cwk, 0, sizeof(cwk));

	if (bp->cmd_hewpew->cwock_souwce_id_to_atom(bp_pawams->pww_id, &pww_id)
			&& bp->cmd_hewpew->contwowwew_id_to_atom(bp_pawams->
					contwowwew_id, &contwowwew_id)) {
		/* Note: VBIOS stiww wants to use ucCWTC name which is now
		 * 1 byte in UWONG
		 *typedef stwuct _CWTC_PIXEW_CWOCK_FWEQ
		 *{
		 * tawget the pixew cwock to dwive the CWTC timing.
		 * UWONG uwPixewCwock:24;
		 * 0 means disabwe PPWW/DCPWW. Expanded to 24 bits compawing to
		 * pwevious vewsion.
		 * ATOM_CWTC1~6, indicate the CWTC contwowwew to
		 * UWONG ucCWTC:8;
		 * dwive the pixew cwock. not used fow DCPWW case.
		 *}CWTC_PIXEW_CWOCK_FWEQ;
		 *union
		 *{
		 * pixew cwock and CWTC id fwequency
		 * CWTC_PIXEW_CWOCK_FWEQ uwCwtcPcwkFweq;
		 * UWONG uwDispEngCwkFweq; dispcwk fwequency
		 *};
		 */
		cwk.cwtc_id = contwowwew_id;
		cwk.pww_id = (uint8_t) pww_id;
		cwk.encodewobjid =
			bp->cmd_hewpew->encodew_id_to_atom(
				daw_gwaphics_object_id_get_encodew_id(
					bp_pawams->encodew_object_id));

		cwk.encodew_mode = (uint8_t) bp->
			cmd_hewpew->encodew_mode_bp_to_atom(
				bp_pawams->signaw_type, fawse);

		cwk.pixcwk_100hz = cpu_to_we32(bp_pawams->tawget_pixew_cwock_100hz);

		cwk.deep_cowow_watio =
			(uint8_t) bp->cmd_hewpew->
				twansmittew_cowow_depth_to_atom(
					bp_pawams->cowow_depth);

		DC_WOG_BIOS("%s:pwogwam dispway cwock = %d, tg = %d, pww = %d, "\
				"cowowDepth = %d\n", __func__,
				bp_pawams->tawget_pixew_cwock_100hz, (int)contwowwew_id,
				pww_id, bp_pawams->cowow_depth);

		if (bp_pawams->fwags.FOWCE_PWOGWAMMING_OF_PWW)
			cwk.miscinfo |= PIXEW_CWOCK_V7_MISC_FOWCE_PWOG_PPWW;

		if (bp_pawams->fwags.PWOGWAM_PHY_PWW_ONWY)
			cwk.miscinfo |= PIXEW_CWOCK_V7_MISC_PWOG_PHYPWW;

		if (bp_pawams->fwags.SUPPOWT_YUV_420)
			cwk.miscinfo |= PIXEW_CWOCK_V7_MISC_YUV420_MODE;

		if (bp_pawams->fwags.SET_XTAWIN_WEF_SWC)
			cwk.miscinfo |= PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_XTAWIN;

		if (bp_pawams->fwags.SET_GENWOCK_WEF_DIV_SWC)
			cwk.miscinfo |= PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_GENWK;

		if (bp_pawams->signaw_type == SIGNAW_TYPE_DVI_DUAW_WINK)
			cwk.miscinfo |= PIXEW_CWOCK_V7_MISC_DVI_DUAWWINK_EN;

		if (bp->base.ctx->dc->ctx->dmub_swv &&
		    bp->base.ctx->dc->debug.dmub_command_tabwe) {
			set_pixew_cwock_dmcub(bp->base.ctx->dmub_swv, &cwk);
			wetuwn BP_WESUWT_OK;
		}

		if (EXEC_BIOS_CMD_TABWE(setpixewcwock, cwk))
			wesuwt = BP_WESUWT_OK;
	}
	wetuwn wesuwt;
}

static enum bp_wesuwt set_pixew_cwock_fawwback(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		wetuwn set_pixew_cwock_v7(bp, bp_pawams);
	}

	wetuwn BP_WESUWT_FAIWUWE;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  SET CWTC TIMING
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt set_cwtc_using_dtd_timing_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams);

static void init_set_cwtc_timing(stwuct bios_pawsew *bp)
{
	uint32_t dtd_vewsion =
			BIOS_CMD_TABWE_PAWA_WEVISION(setcwtc_usingdtdtiming);

	switch (dtd_vewsion) {
	case 3:
		bp->cmd_tbw.set_cwtc_timing =
			set_cwtc_using_dtd_timing_v3;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have set_cwtc_timing fow v%d\n", dtd_vewsion);
		bp->cmd_tbw.set_cwtc_timing = NUWW;
		bweak;
	}
}

static enum bp_wesuwt set_cwtc_using_dtd_timing_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	stwuct set_cwtc_using_dtd_timing_pawametews pawams = {0};
	uint8_t atom_contwowwew_id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(
			bp_pawams->contwowwew_id, &atom_contwowwew_id))
		pawams.cwtc_id = atom_contwowwew_id;

	/* bios usH_Size wants h addwessabwe size */
	pawams.h_size = cpu_to_we16((uint16_t)bp_pawams->h_addwessabwe);
	/* bios usH_Bwanking_Time wants bowdews incwuded in bwanking */
	pawams.h_bwanking_time =
			cpu_to_we16((uint16_t)(bp_pawams->h_totaw -
					bp_pawams->h_addwessabwe));
	/* bios usV_Size wants v addwessabwe size */
	pawams.v_size = cpu_to_we16((uint16_t)bp_pawams->v_addwessabwe);
	/* bios usV_Bwanking_Time wants bowdews incwuded in bwanking */
	pawams.v_bwanking_time =
			cpu_to_we16((uint16_t)(bp_pawams->v_totaw -
					bp_pawams->v_addwessabwe));
	/* bios usHSyncOffset is the offset fwom the end of h addwessabwe,
	 * ouw howizontawSyncStawt is the offset fwom the beginning
	 * of h addwessabwe
	 */
	pawams.h_syncoffset =
			cpu_to_we16((uint16_t)(bp_pawams->h_sync_stawt -
					bp_pawams->h_addwessabwe));
	pawams.h_syncwidth = cpu_to_we16((uint16_t)bp_pawams->h_sync_width);
	/* bios usHSyncOffset is the offset fwom the end of v addwessabwe,
	 * ouw vewticawSyncStawt is the offset fwom the beginning of
	 * v addwessabwe
	 */
	pawams.v_syncoffset =
			cpu_to_we16((uint16_t)(bp_pawams->v_sync_stawt -
					bp_pawams->v_addwessabwe));
	pawams.v_syncwidth = cpu_to_we16((uint16_t)bp_pawams->v_sync_width);

	/* we assume that ovewscan fwom owiginaw timing does not get biggew
	 * than 255
	 * we wiww pwogwam aww the bowdews in the Set CWTC Ovewscan caww bewow
	 */

	if (bp_pawams->fwags.HSYNC_POSITIVE_POWAWITY == 0)
		pawams.modemiscinfo =
				cpu_to_we16(we16_to_cpu(pawams.modemiscinfo) |
						ATOM_HSYNC_POWAWITY);

	if (bp_pawams->fwags.VSYNC_POSITIVE_POWAWITY == 0)
		pawams.modemiscinfo =
				cpu_to_we16(we16_to_cpu(pawams.modemiscinfo) |
						ATOM_VSYNC_POWAWITY);

	if (bp_pawams->fwags.INTEWWACE)	{
		pawams.modemiscinfo =
				cpu_to_we16(we16_to_cpu(pawams.modemiscinfo) |
						ATOM_INTEWWACE);

		/* owiginaw DAW code has this condition to appwy this
		 * fow non-TV/CV onwy
		 * due to compwex MV testing fow possibwe impact
		 * if ( pACPawametews->signaw != SignawType_YPbPw &&
		 *  pACPawametews->signaw != SignawType_Composite &&
		 *  pACPawametews->signaw != SignawType_SVideo)
		 */
		{
			/* HW wiww deduct 0.5 wine fwom 2nd feiwd.
			 * i.e. fow 1080i, it is 2 wines fow 1st fiewd,
			 * 2.5 wines fow the 2nd feiwd. we need input as 5
			 * instead of 4.
			 * but it is 4 eithew fwom Edid data (spec CEA 861)
			 * ow CEA timing tabwe.
			 */
			we16_add_cpu(&pawams.v_syncoffset, 1);
		}
	}

	if (bp_pawams->fwags.HOWZ_COUNT_BY_TWO)
		pawams.modemiscinfo =
			cpu_to_we16(we16_to_cpu(pawams.modemiscinfo) |
					0x100); /* ATOM_DOUBWE_CWOCK_MODE */

	if (EXEC_BIOS_CMD_TABWE(setcwtc_usingdtdtiming, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  ENABWE CWTC
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt enabwe_cwtc_v1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id contwowwew_id,
	boow enabwe);

static void init_enabwe_cwtc(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(enabwecwtc)) {
	case 1:
		bp->cmd_tbw.enabwe_cwtc = enabwe_cwtc_v1;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have enabwe_cwtc fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(enabwecwtc));
		bp->cmd_tbw.enabwe_cwtc = NUWW;
		bweak;
	}
}

static enum bp_wesuwt enabwe_cwtc_v1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id contwowwew_id,
	boow enabwe)
{
	boow wesuwt = BP_WESUWT_FAIWUWE;
	stwuct enabwe_cwtc_pawametews pawams = {0};
	uint8_t id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(contwowwew_id, &id))
		pawams.cwtc_id = id;
	ewse
		wetuwn BP_WESUWT_BADINPUT;

	if (enabwe)
		pawams.enabwe = ATOM_ENABWE;
	ewse
		pawams.enabwe = ATOM_DISABWE;

	if (EXEC_BIOS_CMD_TABWE(enabwecwtc, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  DISPWAY PWW
 **
 ******************************************************************************
 *****************************************************************************/



/******************************************************************************
 ******************************************************************************
 **
 **                  EXTEWNAW ENCODEW CONTWOW
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt extewnaw_encodew_contwow_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_extewnaw_encodew_contwow *cntw);

static void init_extewnaw_encodew_contwow(
	stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(extewnawencodewcontwow)) {
	case 3:
		bp->cmd_tbw.extewnaw_encodew_contwow =
				extewnaw_encodew_contwow_v3;
		bweak;
	defauwt:
		bp->cmd_tbw.extewnaw_encodew_contwow = NUWW;
		bweak;
	}
}

static enum bp_wesuwt extewnaw_encodew_contwow_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_extewnaw_encodew_contwow *cntw)
{
	/* TODO */
	wetuwn BP_WESUWT_OK;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  ENABWE DISPWAY POWEW GATING
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt enabwe_disp_powew_gating_v2_1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id cwtc_id,
	enum bp_pipe_contwow_action action);

static enum bp_wesuwt enabwe_disp_powew_gating_fawwback(
	stwuct bios_pawsew *bp,
	enum contwowwew_id cwtc_id,
	enum bp_pipe_contwow_action action);

static void init_enabwe_disp_powew_gating(
	stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(enabwedisppowewgating)) {
	case 1:
		bp->cmd_tbw.enabwe_disp_powew_gating =
				enabwe_disp_powew_gating_v2_1;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't enabwe_disp_powew_gating enabwe_cwtc fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(enabwedisppowewgating));
		bp->cmd_tbw.enabwe_disp_powew_gating = enabwe_disp_powew_gating_fawwback;
		bweak;
	}
}

static void enabwe_disp_powew_gating_dmcub(
	stwuct dc_dmub_swv *dmcub,
	stwuct enabwe_disp_powew_gating_pawametews_v2_1 *pww)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.enabwe_disp_powew_gating.headew.type = DMUB_CMD__VBIOS;
	cmd.enabwe_disp_powew_gating.headew.sub_type =
		DMUB_CMD__VBIOS_ENABWE_DISP_POWEW_GATING;
	cmd.enabwe_disp_powew_gating.headew.paywoad_bytes =
		sizeof(cmd.enabwe_disp_powew_gating) -
		sizeof(cmd.enabwe_disp_powew_gating.headew);
	cmd.enabwe_disp_powew_gating.powew_gating.pww = *pww;

	dc_wake_and_execute_dmub_cmd(dmcub->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static enum bp_wesuwt enabwe_disp_powew_gating_v2_1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id cwtc_id,
	enum bp_pipe_contwow_action action)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;


	stwuct enabwe_disp_powew_gating_ps_awwocation ps = { { 0 } };
	uint8_t atom_cwtc_id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(cwtc_id, &atom_cwtc_id))
		ps.pawam.disp_pipe_id = atom_cwtc_id;
	ewse
		wetuwn BP_WESUWT_BADINPUT;

	ps.pawam.enabwe =
		bp->cmd_hewpew->disp_powew_gating_action_to_atom(action);

	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		enabwe_disp_powew_gating_dmcub(bp->base.ctx->dmub_swv,
					       &ps.pawam);
		wetuwn BP_WESUWT_OK;
	}

	if (EXEC_BIOS_CMD_TABWE(enabwedisppowewgating, ps.pawam))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt enabwe_disp_powew_gating_fawwback(
	stwuct bios_pawsew *bp,
	enum contwowwew_id cwtc_id,
	enum bp_pipe_contwow_action action)
{
	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		wetuwn enabwe_disp_powew_gating_v2_1(bp, cwtc_id, action);
	}

	wetuwn BP_WESUWT_FAIWUWE;
}

/******************************************************************************
*******************************************************************************
 **
 **                  SET DCE CWOCK
 **
*******************************************************************************
*******************************************************************************/

static enum bp_wesuwt set_dce_cwock_v2_1(
	stwuct bios_pawsew *bp,
	stwuct bp_set_dce_cwock_pawametews *bp_pawams);

static void init_set_dce_cwock(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(setdcecwock)) {
	case 1:
		bp->cmd_tbw.set_dce_cwock = set_dce_cwock_v2_1;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have set_dce_cwock fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(setdcecwock));
		bp->cmd_tbw.set_dce_cwock = NUWW;
		bweak;
	}
}

static enum bp_wesuwt set_dce_cwock_v2_1(
	stwuct bios_pawsew *bp,
	stwuct bp_set_dce_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	stwuct set_dce_cwock_ps_awwocation_v2_1 pawams;
	uint32_t atom_pww_id;
	uint32_t atom_cwock_type;
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;

	memset(&pawams, 0, sizeof(pawams));

	if (!cmd->cwock_souwce_id_to_atom(bp_pawams->pww_id, &atom_pww_id) ||
			!cmd->dc_cwock_type_to_atom(bp_pawams->cwock_type,
					&atom_cwock_type))
		wetuwn BP_WESUWT_BADINPUT;

	pawams.pawam.dcecwkswc  = atom_pww_id;
	pawams.pawam.dcecwktype = atom_cwock_type;

	if (bp_pawams->cwock_type == DCECWOCK_TYPE_DPWEFCWK) {
		if (bp_pawams->fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.pawam.dcecwkfwag |=
					DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENWK;

		if (bp_pawams->fwags.USE_PCIE_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.pawam.dcecwkfwag |=
					DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_PCIE;

		if (bp_pawams->fwags.USE_XTAWIN_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.pawam.dcecwkfwag |=
					DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_XTAWIN;

		if (bp_pawams->fwags.USE_GENEWICA_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.pawam.dcecwkfwag |=
					DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENEWICA;
	} ewse
		/* onwy pwogwam cwock fwequency if dispway cwock is used;
		 * VBIOS wiww pwogwam DPWEFCWK
		 * We need to convewt fwom KHz units into 10KHz units
		 */
		pawams.pawam.dcecwk_10khz = cpu_to_we32(
				bp_pawams->tawget_cwock_fwequency / 10);
	DC_WOG_BIOS("%s:tawget_cwock_fwequency = %d"\
			"cwock_type = %d \n", __func__,\
			bp_pawams->tawget_cwock_fwequency,\
			bp_pawams->cwock_type);

	if (EXEC_BIOS_CMD_TABWE(setdcecwock, pawams)) {
		/* Convewt fwom 10KHz units back to KHz */
		bp_pawams->tawget_cwock_fwequency = we32_to_cpu(
				pawams.pawam.dcecwk_10khz) * 10;
		wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}


/******************************************************************************
 ******************************************************************************
 **
 **                  GET SMU CWOCK INFO
 **
 ******************************************************************************
 *****************************************************************************/

static unsigned int get_smu_cwock_info_v3_1(stwuct bios_pawsew *bp, uint8_t id);

static void init_get_smu_cwock_info(stwuct bios_pawsew *bp)
{
	/* TODO add switch fow tabwe vwsion */
	bp->cmd_tbw.get_smu_cwock_info = get_smu_cwock_info_v3_1;

}

static unsigned int get_smu_cwock_info_v3_1(stwuct bios_pawsew *bp, uint8_t id)
{
	stwuct atom_get_smu_cwock_info_pawametews_v3_1 smu_input = {0};
	stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 smu_output;

	smu_input.command = GET_SMU_CWOCK_INFO_V3_1_GET_PWWVCO_FWEQ;
	smu_input.syspww_id = id;

	/* Get Specific Cwock */
	if (EXEC_BIOS_CMD_TABWE(getsmucwockinfo, smu_input)) {
		memmove(&smu_output, &smu_input, sizeof(
			stwuct atom_get_smu_cwock_info_pawametews_v3_1));
		wetuwn smu_output.atom_smu_outputcwkfweq.syspwwvcofweq_10khz;
	}

	wetuwn 0;
}

/******************************************************************************
 ******************************************************************************
 **
 **                  WVTMA CONTWOW
 **
 ******************************************************************************
 *****************************************************************************/

static enum bp_wesuwt enabwe_wvtma_contwow(
	stwuct bios_pawsew *bp,
	uint8_t uc_pww_on,
	uint8_t pwwseq_instance,
	uint8_t bypass_panew_contwow_wait);

static void init_enabwe_wvtma_contwow(stwuct bios_pawsew *bp)
{
	/* TODO add switch fow tabwe vwsion */
	bp->cmd_tbw.enabwe_wvtma_contwow = enabwe_wvtma_contwow;

}

static void enabwe_wvtma_contwow_dmcub(
	stwuct dc_dmub_swv *dmcub,
	uint8_t uc_pww_on,
	uint8_t pwwseq_instance,
	uint8_t bypass_panew_contwow_wait)
{

	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.wvtma_contwow.headew.type = DMUB_CMD__VBIOS;
	cmd.wvtma_contwow.headew.sub_type =
			DMUB_CMD__VBIOS_WVTMA_CONTWOW;
	cmd.wvtma_contwow.data.uc_pww_action =
			uc_pww_on;
	cmd.wvtma_contwow.data.pwwseq_inst =
			pwwseq_instance;
	cmd.wvtma_contwow.data.bypass_panew_contwow_wait =
			bypass_panew_contwow_wait;
	dc_wake_and_execute_dmub_cmd(dmcub->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

static enum bp_wesuwt enabwe_wvtma_contwow(
	stwuct bios_pawsew *bp,
	uint8_t uc_pww_on,
	uint8_t pwwseq_instance,
	uint8_t bypass_panew_contwow_wait)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	if (bp->base.ctx->dc->ctx->dmub_swv &&
	    bp->base.ctx->dc->debug.dmub_command_tabwe) {
		enabwe_wvtma_contwow_dmcub(bp->base.ctx->dmub_swv,
				uc_pww_on,
				pwwseq_instance,
				bypass_panew_contwow_wait);
		wetuwn BP_WESUWT_OK;
	}
	wetuwn wesuwt;
}

void daw_fiwmwawe_pawsew_init_cmd_tbw(stwuct bios_pawsew *bp)
{
	init_dig_encodew_contwow(bp);
	init_twansmittew_contwow(bp);
	init_set_pixew_cwock(bp);

	init_set_cwtc_timing(bp);

	init_enabwe_cwtc(bp);

	init_extewnaw_encodew_contwow(bp);
	init_enabwe_disp_powew_gating(bp);
	init_set_dce_cwock(bp);
	init_get_smu_cwock_info(bp);

	init_enabwe_wvtma_contwow(bp);
}
