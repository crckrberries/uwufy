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
#incwude "amdgpu.h"
#incwude "atom.h"

#incwude "incwude/bios_pawsew_intewface.h"

#incwude "command_tabwe.h"
#incwude "command_tabwe_hewpew.h"
#incwude "bios_pawsew_hewpew.h"
#incwude "bios_pawsew_types_intewnaw.h"

#define EXEC_BIOS_CMD_TABWE(command, pawams)\
	(amdgpu_atom_execute_tabwe(((stwuct amdgpu_device *)bp->base.ctx->dwivew_context)->mode_info.atom_context, \
		GetIndexIntoMastewTabwe(COMMAND, command), \
		(uint32_t *)&pawams) == 0)

#define BIOS_CMD_TABWE_WEVISION(command, fwev, cwev)\
	amdgpu_atom_pawse_cmd_headew(((stwuct amdgpu_device *)bp->base.ctx->dwivew_context)->mode_info.atom_context, \
		GetIndexIntoMastewTabwe(COMMAND, command), &fwev, &cwev)

#define BIOS_CMD_TABWE_PAWA_WEVISION(command)\
	bios_cmd_tabwe_pawa_wevision(bp->base.ctx->dwivew_context, \
		GetIndexIntoMastewTabwe(COMMAND, command))

static void init_dig_encodew_contwow(stwuct bios_pawsew *bp);
static void init_twansmittew_contwow(stwuct bios_pawsew *bp);
static void init_set_pixew_cwock(stwuct bios_pawsew *bp);
static void init_enabwe_spwead_spectwum_on_ppww(stwuct bios_pawsew *bp);
static void init_adjust_dispway_pww(stwuct bios_pawsew *bp);
static void init_dac_encodew_contwow(stwuct bios_pawsew *bp);
static void init_dac_output_contwow(stwuct bios_pawsew *bp);
static void init_set_cwtc_timing(stwuct bios_pawsew *bp);
static void init_enabwe_cwtc(stwuct bios_pawsew *bp);
static void init_enabwe_cwtc_mem_weq(stwuct bios_pawsew *bp);
static void init_extewnaw_encodew_contwow(stwuct bios_pawsew *bp);
static void init_enabwe_disp_powew_gating(stwuct bios_pawsew *bp);
static void init_pwogwam_cwock(stwuct bios_pawsew *bp);
static void init_set_dce_cwock(stwuct bios_pawsew *bp);

void daw_bios_pawsew_init_cmd_tbw(stwuct bios_pawsew *bp)
{
	init_dig_encodew_contwow(bp);
	init_twansmittew_contwow(bp);
	init_set_pixew_cwock(bp);
	init_enabwe_spwead_spectwum_on_ppww(bp);
	init_adjust_dispway_pww(bp);
	init_dac_encodew_contwow(bp);
	init_dac_output_contwow(bp);
	init_set_cwtc_timing(bp);
	init_enabwe_cwtc(bp);
	init_enabwe_cwtc_mem_weq(bp);
	init_pwogwam_cwock(bp);
	init_extewnaw_encodew_contwow(bp);
	init_enabwe_disp_powew_gating(bp);
	init_set_dce_cwock(bp);
}

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

/*******************************************************************************
 ********************************************************************************
 **
 **                  D I G E N C O D E W C O N T W O W
 **
 ********************************************************************************
 *******************************************************************************/
static enum bp_wesuwt encodew_contwow_digx_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);

static enum bp_wesuwt encodew_contwow_digx_v4(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);

static enum bp_wesuwt encodew_contwow_digx_v5(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);

static void init_encodew_contwow_dig_v1(stwuct bios_pawsew *bp);

static void init_dig_encodew_contwow(stwuct bios_pawsew *bp)
{
	uint32_t vewsion =
		BIOS_CMD_TABWE_PAWA_WEVISION(DIGxEncodewContwow);

	switch (vewsion) {
	case 2:
		bp->cmd_tbw.dig_encodew_contwow = encodew_contwow_digx_v3;
		bweak;
	case 4:
		bp->cmd_tbw.dig_encodew_contwow = encodew_contwow_digx_v4;
		bweak;

	case 5:
		bp->cmd_tbw.dig_encodew_contwow = encodew_contwow_digx_v5;
		bweak;

	defauwt:
		init_encodew_contwow_dig_v1(bp);
		bweak;
	}
}

static enum bp_wesuwt encodew_contwow_dig_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);
static enum bp_wesuwt encodew_contwow_dig1_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);
static enum bp_wesuwt encodew_contwow_dig2_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw);

static void init_encodew_contwow_dig_v1(stwuct bios_pawsew *bp)
{
	stwuct cmd_tbw *cmd_tbw = &bp->cmd_tbw;

	if (1 == BIOS_CMD_TABWE_PAWA_WEVISION(DIG1EncodewContwow))
		cmd_tbw->encodew_contwow_dig1 = encodew_contwow_dig1_v1;
	ewse
		cmd_tbw->encodew_contwow_dig1 = NUWW;

	if (1 == BIOS_CMD_TABWE_PAWA_WEVISION(DIG2EncodewContwow))
		cmd_tbw->encodew_contwow_dig2 = encodew_contwow_dig2_v1;
	ewse
		cmd_tbw->encodew_contwow_dig2 = NUWW;

	cmd_tbw->dig_encodew_contwow = encodew_contwow_dig_v1;
}

static enum bp_wesuwt encodew_contwow_dig_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	stwuct cmd_tbw *cmd_tbw = &bp->cmd_tbw;

	if (cntw != NUWW)
		switch (cntw->engine_id) {
		case ENGINE_ID_DIGA:
			if (cmd_tbw->encodew_contwow_dig1 != NUWW)
				wesuwt =
					cmd_tbw->encodew_contwow_dig1(bp, cntw);
			bweak;
		case ENGINE_ID_DIGB:
			if (cmd_tbw->encodew_contwow_dig2 != NUWW)
				wesuwt =
					cmd_tbw->encodew_contwow_dig2(bp, cntw);
			bweak;

		defauwt:
			bweak;
		}

	wetuwn wesuwt;
}

static enum bp_wesuwt encodew_contwow_dig1_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2 pawams = {0};

	bp->cmd_hewpew->assign_contwow_pawametew(bp->cmd_hewpew, cntw, &pawams);

	if (EXEC_BIOS_CMD_TABWE(DIG1EncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt encodew_contwow_dig2_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2 pawams = {0};

	bp->cmd_hewpew->assign_contwow_pawametew(bp->cmd_hewpew, cntw, &pawams);

	if (EXEC_BIOS_CMD_TABWE(DIG2EncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt encodew_contwow_digx_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_ENCODEW_CONTWOW_PAWAMETEWS_V3 pawams = {0};

	if (WANE_COUNT_FOUW < cntw->wanes_numbew)
		pawams.acConfig.ucDPWinkWate = 1; /* duaw wink 2.7GHz */
	ewse
		pawams.acConfig.ucDPWinkWate = 0; /* singwe wink 1.62GHz */

	pawams.acConfig.ucDigSew = (uint8_t)(cntw->engine_id);

	/* We need to convewt fwom KHz units into 10KHz units */
	pawams.ucAction = bp->cmd_hewpew->encodew_action_to_atom(cntw->action);
	pawams.usPixewCwock = cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
	pawams.ucEncodewMode =
			(uint8_t)bp->cmd_hewpew->encodew_mode_bp_to_atom(
					cntw->signaw,
					cntw->enabwe_dp_audio);
	pawams.ucWaneNum = (uint8_t)(cntw->wanes_numbew);

	switch (cntw->cowow_depth) {
	case COWOW_DEPTH_888:
		pawams.ucBitPewCowow = PANEW_8BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_101010:
		pawams.ucBitPewCowow = PANEW_10BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_121212:
		pawams.ucBitPewCowow = PANEW_12BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_161616:
		pawams.ucBitPewCowow = PANEW_16BIT_PEW_COWOW;
		bweak;
	defauwt:
		bweak;
	}

	if (EXEC_BIOS_CMD_TABWE(DIGxEncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt encodew_contwow_digx_v4(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_ENCODEW_CONTWOW_PAWAMETEWS_V4 pawams = {0};

	if (WANE_COUNT_FOUW < cntw->wanes_numbew)
		pawams.acConfig.ucDPWinkWate = 1; /* duaw wink 2.7GHz */
	ewse
		pawams.acConfig.ucDPWinkWate = 0; /* singwe wink 1.62GHz */

	pawams.acConfig.ucDigSew = (uint8_t)(cntw->engine_id);

	/* We need to convewt fwom KHz units into 10KHz units */
	pawams.ucAction = bp->cmd_hewpew->encodew_action_to_atom(cntw->action);
	pawams.usPixewCwock = cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
	pawams.ucEncodewMode =
			(uint8_t)(bp->cmd_hewpew->encodew_mode_bp_to_atom(
					cntw->signaw,
					cntw->enabwe_dp_audio));
	pawams.ucWaneNum = (uint8_t)(cntw->wanes_numbew);

	switch (cntw->cowow_depth) {
	case COWOW_DEPTH_888:
		pawams.ucBitPewCowow = PANEW_8BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_101010:
		pawams.ucBitPewCowow = PANEW_10BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_121212:
		pawams.ucBitPewCowow = PANEW_12BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_161616:
		pawams.ucBitPewCowow = PANEW_16BIT_PEW_COWOW;
		bweak;
	defauwt:
		bweak;
	}

	if (EXEC_BIOS_CMD_TABWE(DIGxEncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt encodew_contwow_digx_v5(
	stwuct bios_pawsew *bp,
	stwuct bp_encodew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	ENCODEW_STWEAM_SETUP_PAWAMETEWS_V5 pawams = {0};

	pawams.ucDigId = (uint8_t)(cntw->engine_id);
	pawams.ucAction = bp->cmd_hewpew->encodew_action_to_atom(cntw->action);

	pawams.uwPixewCwock = cntw->pixew_cwock / 10;
	pawams.ucDigMode =
			(uint8_t)(bp->cmd_hewpew->encodew_mode_bp_to_atom(
					cntw->signaw,
					cntw->enabwe_dp_audio));
	pawams.ucWaneNum = (uint8_t)(cntw->wanes_numbew);

	switch (cntw->cowow_depth) {
	case COWOW_DEPTH_888:
		pawams.ucBitPewCowow = PANEW_8BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_101010:
		pawams.ucBitPewCowow = PANEW_10BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_121212:
		pawams.ucBitPewCowow = PANEW_12BIT_PEW_COWOW;
		bweak;
	case COWOW_DEPTH_161616:
		pawams.ucBitPewCowow = PANEW_16BIT_PEW_COWOW;
		bweak;
	defauwt:
		bweak;
	}

	if (cntw->signaw == SIGNAW_TYPE_HDMI_TYPE_A)
		switch (cntw->cowow_depth) {
		case COWOW_DEPTH_101010:
			pawams.uwPixewCwock =
				(pawams.uwPixewCwock * 30) / 24;
			bweak;
		case COWOW_DEPTH_121212:
			pawams.uwPixewCwock =
				(pawams.uwPixewCwock * 36) / 24;
			bweak;
		case COWOW_DEPTH_161616:
			pawams.uwPixewCwock =
				(pawams.uwPixewCwock * 48) / 24;
			bweak;
		defauwt:
			bweak;
		}

	if (EXEC_BIOS_CMD_TABWE(DIGxEncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  TWANSMITTEW CONTWOW
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt twansmittew_contwow_v2(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);
static enum bp_wesuwt twansmittew_contwow_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);
static enum bp_wesuwt twansmittew_contwow_v4(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);
static enum bp_wesuwt twansmittew_contwow_v1_5(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);
static enum bp_wesuwt twansmittew_contwow_v1_6(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw);

static void init_twansmittew_contwow(stwuct bios_pawsew *bp)
{
	uint8_t fwev;
	uint8_t cwev;

	if (BIOS_CMD_TABWE_WEVISION(UNIPHYTwansmittewContwow,
			fwev, cwev) == fawse)
		BWEAK_TO_DEBUGGEW();
	switch (cwev) {
	case 2:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v2;
		bweak;
	case 3:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v3;
		bweak;
	case 4:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v4;
		bweak;
	case 5:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v1_5;
		bweak;
	case 6:
		bp->cmd_tbw.twansmittew_contwow = twansmittew_contwow_v1_6;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have twansmittew_contwow fow v%d\n", cwev);
		bp->cmd_tbw.twansmittew_contwow = NUWW;
		bweak;
	}
}

static enum bp_wesuwt twansmittew_contwow_v2(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V2 pawams;
	enum connectow_id connectow_id =
		daw_gwaphics_object_id_get_connectow_id(cntw->connectow_obj_id);

	memset(&pawams, 0, sizeof(pawams));

	switch (cntw->twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
	case TWANSMITTEW_UNIPHY_B:
	case TWANSMITTEW_UNIPHY_C:
	case TWANSMITTEW_UNIPHY_D:
	case TWANSMITTEW_UNIPHY_E:
	case TWANSMITTEW_UNIPHY_F:
	case TWANSMITTEW_TWAVIS_WCD:
		bweak;
	defauwt:
		wetuwn BP_WESUWT_BADINPUT;
	}

	switch (cntw->action) {
	case TWANSMITTEW_CONTWOW_INIT:
		if ((CONNECTOW_ID_DUAW_WINK_DVII == connectow_id) ||
				(CONNECTOW_ID_DUAW_WINK_DVID == connectow_id))
			/* on INIT this bit shouwd be set accowding to the
			 * physicaw connectow
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;

		/* connectow object id */
		pawams.usInitInfo =
				cpu_to_we16((uint8_t)cntw->connectow_obj_id.id);
		bweak;
	case TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS:
		/* vowtage swing and pwe-emphsis */
		pawams.asMode.ucWaneSew = (uint8_t)cntw->wane_sewect;
		pawams.asMode.ucWaneSet = (uint8_t)cntw->wane_settings;
		bweak;
	defauwt:
		/* if duaw-wink */
		if (WANE_COUNT_FOUW < cntw->wanes_numbew) {
			/* on ENABWE/DISABWE this bit shouwd be set accowding to
			 * actuaw timing (numbew of wanes)
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;

			/* wink wate, hawf fow duaw wink
			 * We need to convewt fwom KHz units into 20KHz units
			 */
			pawams.usPixewCwock =
					cpu_to_we16((uint16_t)(cntw->pixew_cwock / 20));
		} ewse
			/* wink wate, hawf fow duaw wink
			 * We need to convewt fwom KHz units into 10KHz units
			 */
			pawams.usPixewCwock =
					cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
		bweak;
	}

	/* 00 - cohewent mode
	 * 01 - incohewent mode
	 */

	pawams.acConfig.fCohewentMode = cntw->cohewent;

	if ((TWANSMITTEW_UNIPHY_B == cntw->twansmittew)
			|| (TWANSMITTEW_UNIPHY_D == cntw->twansmittew)
			|| (TWANSMITTEW_UNIPHY_F == cntw->twansmittew))
		/* Bit2: Twansmittew Wink sewection
		 * =0 when bit0=0, singwe wink A/C/E, when bit0=1,
		 * mastew wink A/C/E
		 * =1 when bit0=0, singwe wink B/D/F, when bit0=1,
		 * mastew wink B/D/F
		 */
		pawams.acConfig.ucWinkSew = 1;

	if (ENGINE_ID_DIGB == cntw->engine_id)
		/* Bit3: Twansmittew data souwce sewection
		 * =0 DIGA is data souwce.
		 * =1 DIGB is data souwce.
		 * This bit is onwy usefuw when ucAction= ATOM_ENABWE
		 */
		pawams.acConfig.ucEncodewSew = 1;

	if (CONNECTOW_ID_DISPWAY_POWT == connectow_id ||
	    CONNECTOW_ID_USBC == connectow_id)
		/* Bit4: DP connectow fwag
		 * =0 connectow is none-DP connectow
		 * =1 connectow is DP connectow
		 */
		pawams.acConfig.fDPConnectow = 1;

	/* Bit[7:6]: Twansmittew sewection
	 * =0 UNIPHY_ENCODEW: UNIPHYA/B
	 * =1 UNIPHY1_ENCODEW: UNIPHYC/D
	 * =2 UNIPHY2_ENCODEW: UNIPHYE/F
	 * =3 wesewved
	 */
	pawams.acConfig.ucTwansmittewSew =
			(uint8_t)bp->cmd_hewpew->twansmittew_bp_to_atom(
					cntw->twansmittew);

	pawams.ucAction = (uint8_t)cntw->action;

	if (EXEC_BIOS_CMD_TABWE(UNIPHYTwansmittewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt twansmittew_contwow_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V3 pawams;
	uint32_t pww_id;
	enum connectow_id conn_id =
			daw_gwaphics_object_id_get_connectow_id(cntw->connectow_obj_id);
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;
	boow duaw_wink_conn = (CONNECTOW_ID_DUAW_WINK_DVII == conn_id)
					|| (CONNECTOW_ID_DUAW_WINK_DVID == conn_id);

	memset(&pawams, 0, sizeof(pawams));

	switch (cntw->twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
	case TWANSMITTEW_UNIPHY_B:
	case TWANSMITTEW_UNIPHY_C:
	case TWANSMITTEW_UNIPHY_D:
	case TWANSMITTEW_UNIPHY_E:
	case TWANSMITTEW_UNIPHY_F:
	case TWANSMITTEW_TWAVIS_WCD:
		bweak;
	defauwt:
		wetuwn BP_WESUWT_BADINPUT;
	}

	if (!cmd->cwock_souwce_id_to_atom(cntw->pww_id, &pww_id))
		wetuwn BP_WESUWT_BADINPUT;

	/* fiww infowmation based on the action */
	switch (cntw->action) {
	case TWANSMITTEW_CONTWOW_INIT:
		if (duaw_wink_conn) {
			/* on INIT this bit shouwd be set accowding to the
			 * phisycaw connectow
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;
		}

		/* connectow object id */
		pawams.usInitInfo =
				cpu_to_we16((uint8_t)(cntw->connectow_obj_id.id));
		bweak;
	case TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS:
		/* votage swing and pwe-emphsis */
		pawams.asMode.ucWaneSew = (uint8_t)cntw->wane_sewect;
		pawams.asMode.ucWaneSet = (uint8_t)cntw->wane_settings;
		bweak;
	defauwt:
		if (duaw_wink_conn && cntw->muwti_path)
			/* on ENABWE/DISABWE this bit shouwd be set accowding to
			 * actuaw timing (numbew of wanes)
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;

		/* if duaw-wink */
		if (WANE_COUNT_FOUW < cntw->wanes_numbew) {
			/* on ENABWE/DISABWE this bit shouwd be set accowding to
			 * actuaw timing (numbew of wanes)
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;

			/* wink wate, hawf fow duaw wink
			 * We need to convewt fwom KHz units into 20KHz units
			 */
			pawams.usPixewCwock =
					cpu_to_we16((uint16_t)(cntw->pixew_cwock / 20));
		} ewse {
			/* wink wate, hawf fow duaw wink
			 * We need to convewt fwom KHz units into 10KHz units
			 */
			pawams.usPixewCwock =
					cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
		}
		bweak;
	}

	/* 00 - cohewent mode
	 * 01 - incohewent mode
	 */

	pawams.acConfig.fCohewentMode = cntw->cohewent;

	if ((TWANSMITTEW_UNIPHY_B == cntw->twansmittew)
		|| (TWANSMITTEW_UNIPHY_D == cntw->twansmittew)
		|| (TWANSMITTEW_UNIPHY_F == cntw->twansmittew))
		/* Bit2: Twansmittew Wink sewection
		 * =0 when bit0=0, singwe wink A/C/E, when bit0=1,
		 * mastew wink A/C/E
		 * =1 when bit0=0, singwe wink B/D/F, when bit0=1,
		 * mastew wink B/D/F
		 */
		pawams.acConfig.ucWinkSew = 1;

	if (ENGINE_ID_DIGB == cntw->engine_id)
		/* Bit3: Twansmittew data souwce sewection
		 * =0 DIGA is data souwce.
		 * =1 DIGB is data souwce.
		 * This bit is onwy usefuw when ucAction= ATOM_ENABWE
		 */
		pawams.acConfig.ucEncodewSew = 1;

	/* Bit[7:6]: Twansmittew sewection
	 * =0 UNIPHY_ENCODEW: UNIPHYA/B
	 * =1 UNIPHY1_ENCODEW: UNIPHYC/D
	 * =2 UNIPHY2_ENCODEW: UNIPHYE/F
	 * =3 wesewved
	 */
	pawams.acConfig.ucTwansmittewSew =
			(uint8_t)cmd->twansmittew_bp_to_atom(cntw->twansmittew);

	pawams.ucWaneNum = (uint8_t)cntw->wanes_numbew;

	pawams.acConfig.ucWefCwkSouwce = (uint8_t)pww_id;

	pawams.ucAction = (uint8_t)cntw->action;

	if (EXEC_BIOS_CMD_TABWE(UNIPHYTwansmittewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt twansmittew_contwow_v4(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V4 pawams;
	uint32_t wef_cwk_swc_id;
	enum connectow_id conn_id =
			daw_gwaphics_object_id_get_connectow_id(cntw->connectow_obj_id);
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;

	memset(&pawams, 0, sizeof(pawams));

	switch (cntw->twansmittew) {
	case TWANSMITTEW_UNIPHY_A:
	case TWANSMITTEW_UNIPHY_B:
	case TWANSMITTEW_UNIPHY_C:
	case TWANSMITTEW_UNIPHY_D:
	case TWANSMITTEW_UNIPHY_E:
	case TWANSMITTEW_UNIPHY_F:
	case TWANSMITTEW_TWAVIS_WCD:
		bweak;
	defauwt:
		wetuwn BP_WESUWT_BADINPUT;
	}

	if (!cmd->cwock_souwce_id_to_wef_cwk_swc(cntw->pww_id, &wef_cwk_swc_id))
		wetuwn BP_WESUWT_BADINPUT;

	switch (cntw->action) {
	case TWANSMITTEW_CONTWOW_INIT:
	{
		if ((CONNECTOW_ID_DUAW_WINK_DVII == conn_id) ||
				(CONNECTOW_ID_DUAW_WINK_DVID == conn_id))
			/* on INIT this bit shouwd be set accowding to the
			 * phisycaw connectow
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;

		/* connectow object id */
		pawams.usInitInfo =
				cpu_to_we16((uint8_t)(cntw->connectow_obj_id.id));
	}
	bweak;
	case TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS:
		/* votage swing and pwe-emphsis */
		pawams.asMode.ucWaneSew = (uint8_t)(cntw->wane_sewect);
		pawams.asMode.ucWaneSet = (uint8_t)(cntw->wane_settings);
		bweak;
	defauwt:
		if ((CONNECTOW_ID_DUAW_WINK_DVII == conn_id) ||
				(CONNECTOW_ID_DUAW_WINK_DVID == conn_id))
			/* on ENABWE/DISABWE this bit shouwd be set accowding to
			 * actuaw timing (numbew of wanes)
			 * Bit0: duaw wink connectow fwag
			 * =0 connectow is singwe wink connectow
			 * =1 connectow is duaw wink connectow
			 */
			pawams.acConfig.fDuawWinkConnectow = 1;

		/* if duaw-wink */
		if (WANE_COUNT_FOUW < cntw->wanes_numbew)
			/* wink wate, hawf fow duaw wink
			 * We need to convewt fwom KHz units into 20KHz units
			 */
			pawams.usPixewCwock =
					cpu_to_we16((uint16_t)(cntw->pixew_cwock / 20));
		ewse {
			/* wink wate, hawf fow duaw wink
			 * We need to convewt fwom KHz units into 10KHz units
			 */
			pawams.usPixewCwock =
					cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
		}
		bweak;
	}

	/* 00 - cohewent mode
	 * 01 - incohewent mode
	 */

	pawams.acConfig.fCohewentMode = cntw->cohewent;

	if ((TWANSMITTEW_UNIPHY_B == cntw->twansmittew)
		|| (TWANSMITTEW_UNIPHY_D == cntw->twansmittew)
		|| (TWANSMITTEW_UNIPHY_F == cntw->twansmittew))
		/* Bit2: Twansmittew Wink sewection
		 * =0 when bit0=0, singwe wink A/C/E, when bit0=1,
		 * mastew wink A/C/E
		 * =1 when bit0=0, singwe wink B/D/F, when bit0=1,
		 * mastew wink B/D/F
		 */
		pawams.acConfig.ucWinkSew = 1;

	if (ENGINE_ID_DIGB == cntw->engine_id)
		/* Bit3: Twansmittew data souwce sewection
		 * =0 DIGA is data souwce.
		 * =1 DIGB is data souwce.
		 * This bit is onwy usefuw when ucAction= ATOM_ENABWE
		 */
		pawams.acConfig.ucEncodewSew = 1;

	/* Bit[7:6]: Twansmittew sewection
	 * =0 UNIPHY_ENCODEW: UNIPHYA/B
	 * =1 UNIPHY1_ENCODEW: UNIPHYC/D
	 * =2 UNIPHY2_ENCODEW: UNIPHYE/F
	 * =3 wesewved
	 */
	pawams.acConfig.ucTwansmittewSew =
		(uint8_t)(cmd->twansmittew_bp_to_atom(cntw->twansmittew));
	pawams.ucWaneNum = (uint8_t)(cntw->wanes_numbew);
	pawams.acConfig.ucWefCwkSouwce = (uint8_t)(wef_cwk_swc_id);
	pawams.ucAction = (uint8_t)(cntw->action);

	if (EXEC_BIOS_CMD_TABWE(UNIPHYTwansmittewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt twansmittew_contwow_v1_5(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;
	DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_5 pawams;

	memset(&pawams, 0, sizeof(pawams));
	pawams.ucPhyId = cmd->phy_id_to_atom(cntw->twansmittew);
	pawams.ucAction = (uint8_t)cntw->action;
	pawams.ucWaneNum = (uint8_t)cntw->wanes_numbew;
	pawams.ucConnObjId = (uint8_t)cntw->connectow_obj_id.id;

	pawams.ucDigMode =
		cmd->signaw_type_to_atom_dig_mode(cntw->signaw);
	pawams.asConfig.ucPhyCwkSwcId =
		cmd->cwock_souwce_id_to_atom_phy_cwk_swc_id(cntw->pww_id);
	/* 00 - cohewent mode */
	pawams.asConfig.ucCohewentMode = cntw->cohewent;
	pawams.asConfig.ucHPDSew =
		cmd->hpd_sew_to_atom(cntw->hpd_sew);
	pawams.ucDigEncodewSew =
		cmd->dig_encodew_sew_to_atom(cntw->engine_id);
	pawams.ucDPWaneSet = (uint8_t) cntw->wane_settings;
	pawams.usSymCwock = cpu_to_we16((uint16_t) (cntw->pixew_cwock / 10));
	/*
	 * In SI/TN case, cawwew have to set usPixewCwock as fowwowing:
	 * DP mode: usPixewCwock = DP_WINK_CWOCK/10
	 * (DP_WINK_CWOCK = 1.62GHz, 2.7GHz, 5.4GHz)
	 * DVI singwe wink mode: usPixewCwock = pixew cwock
	 * DVI duaw wink mode: usPixewCwock = pixew cwock
	 * HDMI mode: usPixewCwock = pixew cwock * deep_cowow_watio
	 * (=1: 8bpp, =1.25: 10bpp, =1.5:12bpp, =2: 16bpp)
	 * WVDS mode: usPixewCwock = pixew cwock
	 */
	if  (cntw->signaw == SIGNAW_TYPE_HDMI_TYPE_A) {
		switch (cntw->cowow_depth) {
		case COWOW_DEPTH_101010:
			pawams.usSymCwock =
				cpu_to_we16((we16_to_cpu(pawams.usSymCwock) * 30) / 24);
			bweak;
		case COWOW_DEPTH_121212:
			pawams.usSymCwock =
				cpu_to_we16((we16_to_cpu(pawams.usSymCwock) * 36) / 24);
			bweak;
		case COWOW_DEPTH_161616:
			pawams.usSymCwock =
				cpu_to_we16((we16_to_cpu(pawams.usSymCwock) * 48) / 24);
			bweak;
		defauwt:
			bweak;
		}
	}

	if (EXEC_BIOS_CMD_TABWE(UNIPHYTwansmittewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt twansmittew_contwow_v1_6(
	stwuct bios_pawsew *bp,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;
	DIG_TWANSMITTEW_CONTWOW_PAWAMETEWS_V1_6 pawams;

	memset(&pawams, 0, sizeof(pawams));
	pawams.ucPhyId = cmd->phy_id_to_atom(cntw->twansmittew);
	pawams.ucAction = (uint8_t)cntw->action;

	if (cntw->action == TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS)
		pawams.ucDPWaneSet = (uint8_t)cntw->wane_settings;
	ewse
		pawams.ucDigMode = cmd->signaw_type_to_atom_dig_mode(cntw->signaw);

	pawams.ucWaneNum = (uint8_t)cntw->wanes_numbew;
	pawams.ucHPDSew = cmd->hpd_sew_to_atom(cntw->hpd_sew);
	pawams.ucDigEncodewSew = cmd->dig_encodew_sew_to_atom(cntw->engine_id);
	pawams.ucConnObjId = (uint8_t)cntw->connectow_obj_id.id;
	pawams.uwSymCwock = cntw->pixew_cwock/10;

	/*
	 * In SI/TN case, cawwew have to set usPixewCwock as fowwowing:
	 * DP mode: usPixewCwock = DP_WINK_CWOCK/10
	 * (DP_WINK_CWOCK = 1.62GHz, 2.7GHz, 5.4GHz)
	 * DVI singwe wink mode: usPixewCwock = pixew cwock
	 * DVI duaw wink mode: usPixewCwock = pixew cwock
	 * HDMI mode: usPixewCwock = pixew cwock * deep_cowow_watio
	 * (=1: 8bpp, =1.25: 10bpp, =1.5:12bpp, =2: 16bpp)
	 * WVDS mode: usPixewCwock = pixew cwock
	 */
	switch (cntw->signaw) {
	case SIGNAW_TYPE_HDMI_TYPE_A:
		switch (cntw->cowow_depth) {
		case COWOW_DEPTH_101010:
			pawams.uwSymCwock =
				cpu_to_we16((we16_to_cpu(pawams.uwSymCwock) * 30) / 24);
			bweak;
		case COWOW_DEPTH_121212:
			pawams.uwSymCwock =
				cpu_to_we16((we16_to_cpu(pawams.uwSymCwock) * 36) / 24);
			bweak;
		case COWOW_DEPTH_161616:
			pawams.uwSymCwock =
				cpu_to_we16((we16_to_cpu(pawams.uwSymCwock) * 48) / 24);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
		defauwt:
			bweak;
	}

	if (EXEC_BIOS_CMD_TABWE(UNIPHYTwansmittewContwow, pawams))
		wesuwt = BP_WESUWT_OK;
	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  SET PIXEW CWOCK
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt set_pixew_cwock_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);
static enum bp_wesuwt set_pixew_cwock_v5(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);
static enum bp_wesuwt set_pixew_cwock_v6(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);
static enum bp_wesuwt set_pixew_cwock_v7(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);

static void init_set_pixew_cwock(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(SetPixewCwock)) {
	case 3:
		bp->cmd_tbw.set_pixew_cwock = set_pixew_cwock_v3;
		bweak;
	case 5:
		bp->cmd_tbw.set_pixew_cwock = set_pixew_cwock_v5;
		bweak;
	case 6:
		bp->cmd_tbw.set_pixew_cwock = set_pixew_cwock_v6;
		bweak;
	case 7:
		bp->cmd_tbw.set_pixew_cwock = set_pixew_cwock_v7;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have set_pixew_cwock fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(SetPixewCwock));
		bp->cmd_tbw.set_pixew_cwock = NUWW;
		bweak;
	}
}

static enum bp_wesuwt set_pixew_cwock_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	PIXEW_CWOCK_PAWAMETEWS_V3 *pawams;
	SET_PIXEW_CWOCK_PS_AWWOCATION awwocation;

	memset(&awwocation, 0, sizeof(awwocation));

	if (CWOCK_SOUWCE_ID_PWW1 == bp_pawams->pww_id)
		awwocation.sPCWKInput.ucPpww = ATOM_PPWW1;
	ewse if (CWOCK_SOUWCE_ID_PWW2 == bp_pawams->pww_id)
		awwocation.sPCWKInput.ucPpww = ATOM_PPWW2;
	ewse
		wetuwn BP_WESUWT_BADINPUT;

	awwocation.sPCWKInput.usWefDiv =
			cpu_to_we16((uint16_t)bp_pawams->wefewence_dividew);
	awwocation.sPCWKInput.usFbDiv =
			cpu_to_we16((uint16_t)bp_pawams->feedback_dividew);
	awwocation.sPCWKInput.ucFwacFbDiv =
			(uint8_t)bp_pawams->fwactionaw_feedback_dividew;
	awwocation.sPCWKInput.ucPostDiv =
			(uint8_t)bp_pawams->pixew_cwock_post_dividew;

	/* We need to convewt fwom 100Hz units into 10KHz units */
	awwocation.sPCWKInput.usPixewCwock =
			cpu_to_we16((uint16_t)(bp_pawams->tawget_pixew_cwock_100hz / 100));

	pawams = (PIXEW_CWOCK_PAWAMETEWS_V3 *)&awwocation.sPCWKInput;
	pawams->ucTwansmittewId =
			bp->cmd_hewpew->encodew_id_to_atom(
					daw_gwaphics_object_id_get_encodew_id(
							bp_pawams->encodew_object_id));
	pawams->ucEncodewMode =
			(uint8_t)(bp->cmd_hewpew->encodew_mode_bp_to_atom(
					bp_pawams->signaw_type, fawse));

	if (bp_pawams->fwags.FOWCE_PWOGWAMMING_OF_PWW)
		pawams->ucMiscInfo |= PIXEW_CWOCK_MISC_FOWCE_PWOG_PPWW;

	if (bp_pawams->fwags.USE_E_CWOCK_AS_SOUWCE_FOW_D_CWOCK)
		pawams->ucMiscInfo |= PIXEW_CWOCK_MISC_USE_ENGINE_FOW_DISPCWK;

	if (CONTWOWWEW_ID_D1 != bp_pawams->contwowwew_id)
		pawams->ucMiscInfo |= PIXEW_CWOCK_MISC_CWTC_SEW_CWTC2;

	if (EXEC_BIOS_CMD_TABWE(SetPixewCwock, awwocation))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

#ifndef SET_PIXEW_CWOCK_PS_AWWOCATION_V5
/* video bios did not define this: */
typedef stwuct _SET_PIXEW_CWOCK_PS_AWWOCATION_V5 {
	PIXEW_CWOCK_PAWAMETEWS_V5 sPCWKInput;
	/* Cawwew doesn't need to init this powtion */
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW sWesewved;
} SET_PIXEW_CWOCK_PS_AWWOCATION_V5;
#endif

#ifndef SET_PIXEW_CWOCK_PS_AWWOCATION_V6
/* video bios did not define this: */
typedef stwuct _SET_PIXEW_CWOCK_PS_AWWOCATION_V6 {
	PIXEW_CWOCK_PAWAMETEWS_V6 sPCWKInput;
	/* Cawwew doesn't need to init this powtion */
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW sWesewved;
} SET_PIXEW_CWOCK_PS_AWWOCATION_V6;
#endif

static enum bp_wesuwt set_pixew_cwock_v5(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	SET_PIXEW_CWOCK_PS_AWWOCATION_V5 cwk;
	uint8_t contwowwew_id;
	uint32_t pww_id;

	memset(&cwk, 0, sizeof(cwk));

	if (bp->cmd_hewpew->cwock_souwce_id_to_atom(bp_pawams->pww_id, &pww_id)
			&& bp->cmd_hewpew->contwowwew_id_to_atom(
					bp_pawams->contwowwew_id, &contwowwew_id)) {
		cwk.sPCWKInput.ucCWTC = contwowwew_id;
		cwk.sPCWKInput.ucPpww = (uint8_t)pww_id;
		cwk.sPCWKInput.ucWefDiv =
				(uint8_t)(bp_pawams->wefewence_dividew);
		cwk.sPCWKInput.usFbDiv =
				cpu_to_we16((uint16_t)(bp_pawams->feedback_dividew));
		cwk.sPCWKInput.uwFbDivDecFwac =
				cpu_to_we32(bp_pawams->fwactionaw_feedback_dividew);
		cwk.sPCWKInput.ucPostDiv =
				(uint8_t)(bp_pawams->pixew_cwock_post_dividew);
		cwk.sPCWKInput.ucTwansmittewID =
				bp->cmd_hewpew->encodew_id_to_atom(
						daw_gwaphics_object_id_get_encodew_id(
								bp_pawams->encodew_object_id));
		cwk.sPCWKInput.ucEncodewMode =
				(uint8_t)bp->cmd_hewpew->encodew_mode_bp_to_atom(
						bp_pawams->signaw_type, fawse);

		/* We need to convewt fwom 100Hz units into 10KHz units */
		cwk.sPCWKInput.usPixewCwock =
				cpu_to_we16((uint16_t)(bp_pawams->tawget_pixew_cwock_100hz / 100));

		if (bp_pawams->fwags.FOWCE_PWOGWAMMING_OF_PWW)
			cwk.sPCWKInput.ucMiscInfo |=
					PIXEW_CWOCK_MISC_FOWCE_PWOG_PPWW;

		if (bp_pawams->fwags.SET_EXTEWNAW_WEF_DIV_SWC)
			cwk.sPCWKInput.ucMiscInfo |=
					PIXEW_CWOCK_MISC_WEF_DIV_SWC;

		/* cwkV5.ucMiscInfo bit[3:2]= HDMI panew bit depth: =0: 24bpp
		 * =1:30bpp, =2:32bpp
		 * dwivew choose pwogwam it itsewf, i.e. hewe we pwogwam it
		 * to 888 by defauwt.
		 */
		if (bp_pawams->signaw_type == SIGNAW_TYPE_HDMI_TYPE_A)
			switch (bp_pawams->cowow_depth) {
			case TWANSMITTEW_COWOW_DEPTH_30:
				/* yes this is cowwect, the atom define is wwong */
				cwk.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_V5_MISC_HDMI_32BPP;
				bweak;
			case TWANSMITTEW_COWOW_DEPTH_36:
				/* yes this is cowwect, the atom define is wwong */
				cwk.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_V5_MISC_HDMI_30BPP;
				bweak;
			defauwt:
				bweak;
			}

		if (EXEC_BIOS_CMD_TABWE(SetPixewCwock, cwk))
			wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt set_pixew_cwock_v6(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	SET_PIXEW_CWOCK_PS_AWWOCATION_V6 cwk;
	uint8_t contwowwew_id;
	uint32_t pww_id;

	memset(&cwk, 0, sizeof(cwk));

	if (bp->cmd_hewpew->cwock_souwce_id_to_atom(bp_pawams->pww_id, &pww_id)
			&& bp->cmd_hewpew->contwowwew_id_to_atom(
					bp_pawams->contwowwew_id, &contwowwew_id)) {
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
		cwk.sPCWKInput.uwCwtcPcwkFweq.ucCWTC = contwowwew_id;
		cwk.sPCWKInput.ucPpww = (uint8_t) pww_id;
		cwk.sPCWKInput.ucWefDiv =
				(uint8_t) bp_pawams->wefewence_dividew;
		cwk.sPCWKInput.usFbDiv =
				cpu_to_we16((uint16_t) bp_pawams->feedback_dividew);
		cwk.sPCWKInput.uwFbDivDecFwac =
				cpu_to_we32(bp_pawams->fwactionaw_feedback_dividew);
		cwk.sPCWKInput.ucPostDiv =
				(uint8_t) bp_pawams->pixew_cwock_post_dividew;
		cwk.sPCWKInput.ucTwansmittewID =
				bp->cmd_hewpew->encodew_id_to_atom(
						daw_gwaphics_object_id_get_encodew_id(
								bp_pawams->encodew_object_id));
		cwk.sPCWKInput.ucEncodewMode =
				(uint8_t) bp->cmd_hewpew->encodew_mode_bp_to_atom(
						bp_pawams->signaw_type, fawse);

		/* We need to convewt fwom 100 Hz units into 10KHz units */
		cwk.sPCWKInput.uwCwtcPcwkFweq.uwPixewCwock =
				cpu_to_we32(bp_pawams->tawget_pixew_cwock_100hz / 100);

		if (bp_pawams->fwags.FOWCE_PWOGWAMMING_OF_PWW) {
			cwk.sPCWKInput.ucMiscInfo |=
					PIXEW_CWOCK_V6_MISC_FOWCE_PWOG_PPWW;
		}

		if (bp_pawams->fwags.SET_EXTEWNAW_WEF_DIV_SWC) {
			cwk.sPCWKInput.ucMiscInfo |=
					PIXEW_CWOCK_V6_MISC_WEF_DIV_SWC;
		}

		/* cwkV6.ucMiscInfo bit[3:2]= HDMI panew bit depth: =0:
		 * 24bpp =1:30bpp, =2:32bpp
		 * dwivew choose pwogwam it itsewf, i.e. hewe we pass wequiwed
		 * tawget wate that incwudes deep cowow.
		 */
		if (bp_pawams->signaw_type == SIGNAW_TYPE_HDMI_TYPE_A)
			switch (bp_pawams->cowow_depth) {
			case TWANSMITTEW_COWOW_DEPTH_30:
				cwk.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_30BPP_V6;
				bweak;
			case TWANSMITTEW_COWOW_DEPTH_36:
				cwk.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_36BPP_V6;
				bweak;
			case TWANSMITTEW_COWOW_DEPTH_48:
				cwk.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_HDMI_48BPP;
				bweak;
			defauwt:
				bweak;
			}

		if (EXEC_BIOS_CMD_TABWE(SetPixewCwock, cwk))
			wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt set_pixew_cwock_v7(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	PIXEW_CWOCK_PAWAMETEWS_V7 cwk;
	uint8_t contwowwew_id;
	uint32_t pww_id;

	memset(&cwk, 0, sizeof(cwk));

	if (bp->cmd_hewpew->cwock_souwce_id_to_atom(bp_pawams->pww_id, &pww_id)
			&& bp->cmd_hewpew->contwowwew_id_to_atom(bp_pawams->contwowwew_id, &contwowwew_id)) {
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
		cwk.ucCWTC = contwowwew_id;
		cwk.ucPpww = (uint8_t) pww_id;
		cwk.ucTwansmittewID = bp->cmd_hewpew->encodew_id_to_atom(daw_gwaphics_object_id_get_encodew_id(bp_pawams->encodew_object_id));
		cwk.ucEncodewMode = (uint8_t) bp->cmd_hewpew->encodew_mode_bp_to_atom(bp_pawams->signaw_type, fawse);

		cwk.uwPixewCwock = cpu_to_we32(bp_pawams->tawget_pixew_cwock_100hz);

		cwk.ucDeepCowowWatio = (uint8_t) bp->cmd_hewpew->twansmittew_cowow_depth_to_atom(bp_pawams->cowow_depth);

		if (bp_pawams->fwags.FOWCE_PWOGWAMMING_OF_PWW)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_FOWCE_PWOG_PPWW;

		if (bp_pawams->fwags.SET_EXTEWNAW_WEF_DIV_SWC)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC;

		if (bp_pawams->fwags.PWOGWAM_PHY_PWW_ONWY)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_PWOG_PHYPWW;

		if (bp_pawams->fwags.SUPPOWT_YUV_420)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_YUV420_MODE;

		if (bp_pawams->fwags.SET_XTAWIN_WEF_SWC)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_XTAWIN;

		if (bp_pawams->fwags.SET_GENWOCK_WEF_DIV_SWC)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_WEF_DIV_SWC_GENWK;

		if (bp_pawams->signaw_type == SIGNAW_TYPE_DVI_DUAW_WINK)
			cwk.ucMiscInfo |= PIXEW_CWOCK_V7_MISC_DVI_DUAWWINK_EN;

		if (EXEC_BIOS_CMD_TABWE(SetPixewCwock, cwk))
			wesuwt = BP_WESUWT_OK;
	}
	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABWE PIXEW CWOCK SS
 **
 ********************************************************************************
 *******************************************************************************/
static enum bp_wesuwt enabwe_spwead_spectwum_on_ppww_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe);
static enum bp_wesuwt enabwe_spwead_spectwum_on_ppww_v2(
	stwuct bios_pawsew *bp,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe);
static enum bp_wesuwt enabwe_spwead_spectwum_on_ppww_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe);

static void init_enabwe_spwead_spectwum_on_ppww(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(EnabweSpweadSpectwumOnPPWW)) {
	case 1:
		bp->cmd_tbw.enabwe_spwead_spectwum_on_ppww =
				enabwe_spwead_spectwum_on_ppww_v1;
		bweak;
	case 2:
		bp->cmd_tbw.enabwe_spwead_spectwum_on_ppww =
				enabwe_spwead_spectwum_on_ppww_v2;
		bweak;
	case 3:
		bp->cmd_tbw.enabwe_spwead_spectwum_on_ppww =
				enabwe_spwead_spectwum_on_ppww_v3;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have enabwe_spwead_spectwum_on_ppww fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(EnabweSpweadSpectwumOnPPWW));
		bp->cmd_tbw.enabwe_spwead_spectwum_on_ppww = NUWW;
		bweak;
	}
}

static enum bp_wesuwt enabwe_spwead_spectwum_on_ppww_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW pawams;

	memset(&pawams, 0, sizeof(pawams));

	if ((enabwe == twue) && (bp_pawams->pewcentage > 0))
		pawams.ucEnabwe = ATOM_ENABWE;
	ewse
		pawams.ucEnabwe = ATOM_DISABWE;

	pawams.usSpweadSpectwumPewcentage =
			cpu_to_we16((uint16_t)bp_pawams->pewcentage);
	pawams.ucSpweadSpectwumStep =
			(uint8_t)bp_pawams->vew1.step;
	pawams.ucSpweadSpectwumDeway =
			(uint8_t)bp_pawams->vew1.deway;
	/* convewt back to unit of 10KHz */
	pawams.ucSpweadSpectwumWange =
			(uint8_t)(bp_pawams->vew1.wange / 10000);

	if (bp_pawams->fwags.EXTEWNAW_SS)
		pawams.ucSpweadSpectwumType |= ATOM_EXTEWNAW_SS_MASK;

	if (bp_pawams->fwags.CENTEW_SPWEAD)
		pawams.ucSpweadSpectwumType |= ATOM_SS_CENTWE_SPWEAD_MODE;

	if (bp_pawams->pww_id == CWOCK_SOUWCE_ID_PWW1)
		pawams.ucPpww = ATOM_PPWW1;
	ewse if (bp_pawams->pww_id == CWOCK_SOUWCE_ID_PWW2)
		pawams.ucPpww = ATOM_PPWW2;
	ewse
		BWEAK_TO_DEBUGGEW(); /* Unexpected PWW vawue!! */

	if (EXEC_BIOS_CMD_TABWE(EnabweSpweadSpectwumOnPPWW, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt enabwe_spwead_spectwum_on_ppww_v2(
	stwuct bios_pawsew *bp,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V2 pawams;

	memset(&pawams, 0, sizeof(pawams));

	if (bp_pawams->pww_id == CWOCK_SOUWCE_ID_PWW1)
		pawams.ucSpweadSpectwumType = ATOM_PPWW_SS_TYPE_V2_P1PWW;
	ewse if (bp_pawams->pww_id == CWOCK_SOUWCE_ID_PWW2)
		pawams.ucSpweadSpectwumType = ATOM_PPWW_SS_TYPE_V2_P2PWW;
	ewse
		BWEAK_TO_DEBUGGEW(); /* Unexpected PWW vawue!! */

	if ((enabwe == twue) && (bp_pawams->pewcentage > 0)) {
		pawams.ucEnabwe = ATOM_ENABWE;

		pawams.usSpweadSpectwumPewcentage =
				cpu_to_we16((uint16_t)(bp_pawams->pewcentage));
		pawams.usSpweadSpectwumStep =
				cpu_to_we16((uint16_t)(bp_pawams->ds.ds_fwac_size));

		if (bp_pawams->fwags.EXTEWNAW_SS)
			pawams.ucSpweadSpectwumType |=
					ATOM_PPWW_SS_TYPE_V2_EXT_SPWEAD;

		if (bp_pawams->fwags.CENTEW_SPWEAD)
			pawams.ucSpweadSpectwumType |=
					ATOM_PPWW_SS_TYPE_V2_CENTWE_SPWEAD;

		/* Both amounts need to be weft shifted fiwst befowe bit
		 * compawison. Othewwise, the wesuwt wiww awways be zewo hewe
		 */
		pawams.usSpweadSpectwumAmount = cpu_to_we16((uint16_t)(
				((bp_pawams->ds.feedback_amount <<
						ATOM_PPWW_SS_AMOUNT_V2_FBDIV_SHIFT) &
						ATOM_PPWW_SS_AMOUNT_V2_FBDIV_MASK) |
						((bp_pawams->ds.nfwac_amount <<
								ATOM_PPWW_SS_AMOUNT_V2_NFWAC_SHIFT) &
								ATOM_PPWW_SS_AMOUNT_V2_NFWAC_MASK)));
	} ewse
		pawams.ucEnabwe = ATOM_DISABWE;

	if (EXEC_BIOS_CMD_TABWE(EnabweSpweadSpectwumOnPPWW, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt enabwe_spwead_spectwum_on_ppww_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_spwead_spectwum_pawametews *bp_pawams,
	boow enabwe)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	ENABWE_SPWEAD_SPECTWUM_ON_PPWW_V3 pawams;

	memset(&pawams, 0, sizeof(pawams));

	switch (bp_pawams->pww_id) {
	case CWOCK_SOUWCE_ID_PWW0:
		/* ATOM_PPWW_SS_TYPE_V3_P0PWW; this is pixew cwock onwy,
		 * not fow SI dispway cwock.
		 */
		pawams.ucSpweadSpectwumType = ATOM_PPWW_SS_TYPE_V3_DCPWW;
		bweak;
	case CWOCK_SOUWCE_ID_PWW1:
		pawams.ucSpweadSpectwumType = ATOM_PPWW_SS_TYPE_V3_P1PWW;
		bweak;

	case CWOCK_SOUWCE_ID_PWW2:
		pawams.ucSpweadSpectwumType = ATOM_PPWW_SS_TYPE_V3_P2PWW;
		bweak;

	case CWOCK_SOUWCE_ID_DCPWW:
		pawams.ucSpweadSpectwumType = ATOM_PPWW_SS_TYPE_V3_DCPWW;
		bweak;

	defauwt:
		BWEAK_TO_DEBUGGEW();
		/* Unexpected PWW vawue!! */
		wetuwn wesuwt;
	}

	if (enabwe == twue) {
		pawams.ucEnabwe = ATOM_ENABWE;

		pawams.usSpweadSpectwumAmountFwac =
				cpu_to_we16((uint16_t)(bp_pawams->ds_fwac_amount));
		pawams.usSpweadSpectwumStep =
				cpu_to_we16((uint16_t)(bp_pawams->ds.ds_fwac_size));

		if (bp_pawams->fwags.EXTEWNAW_SS)
			pawams.ucSpweadSpectwumType |=
					ATOM_PPWW_SS_TYPE_V3_EXT_SPWEAD;
		if (bp_pawams->fwags.CENTEW_SPWEAD)
			pawams.ucSpweadSpectwumType |=
					ATOM_PPWW_SS_TYPE_V3_CENTWE_SPWEAD;

		/* Both amounts need to be weft shifted fiwst befowe bit
		 * compawison. Othewwise, the wesuwt wiww awways be zewo hewe
		 */
		pawams.usSpweadSpectwumAmount = cpu_to_we16((uint16_t)(
				((bp_pawams->ds.feedback_amount <<
						ATOM_PPWW_SS_AMOUNT_V3_FBDIV_SHIFT) &
						ATOM_PPWW_SS_AMOUNT_V3_FBDIV_MASK) |
						((bp_pawams->ds.nfwac_amount <<
								ATOM_PPWW_SS_AMOUNT_V3_NFWAC_SHIFT) &
								ATOM_PPWW_SS_AMOUNT_V3_NFWAC_MASK)));
	} ewse
		pawams.ucEnabwe = ATOM_DISABWE;

	if (EXEC_BIOS_CMD_TABWE(EnabweSpweadSpectwumOnPPWW, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  ADJUST DISPWAY PWW
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt adjust_dispway_pww_v2(
	stwuct bios_pawsew *bp,
	stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams);
static enum bp_wesuwt adjust_dispway_pww_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams);

static void init_adjust_dispway_pww(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(AdjustDispwayPww)) {
	case 2:
		bp->cmd_tbw.adjust_dispway_pww = adjust_dispway_pww_v2;
		bweak;
	case 3:
		bp->cmd_tbw.adjust_dispway_pww = adjust_dispway_pww_v3;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have adjust_dispway_pww fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(AdjustDispwayPww));
		bp->cmd_tbw.adjust_dispway_pww = NUWW;
		bweak;
	}
}

static enum bp_wesuwt adjust_dispway_pww_v2(
	stwuct bios_pawsew *bp,
	stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	ADJUST_DISPWAY_PWW_PS_AWWOCATION pawams = { 0 };

	/* We need to convewt fwom KHz units into 10KHz units and then convewt
	 * output pixew cwock back 10KHz-->KHz */
	uint32_t pixew_cwock_10KHz_in = bp_pawams->pixew_cwock / 10;

	pawams.usPixewCwock = cpu_to_we16((uint16_t)(pixew_cwock_10KHz_in));
	pawams.ucTwansmittewID =
			bp->cmd_hewpew->encodew_id_to_atom(
					daw_gwaphics_object_id_get_encodew_id(
							bp_pawams->encodew_object_id));
	pawams.ucEncodeMode =
			(uint8_t)bp->cmd_hewpew->encodew_mode_bp_to_atom(
					bp_pawams->signaw_type, fawse);

	if (EXEC_BIOS_CMD_TABWE(AdjustDispwayPww, pawams)) {
		/* Convewt output pixew cwock back 10KHz-->KHz: muwtipwy
		 * owiginaw pixew cwock in KHz by watio
		 * [output pxwCwk/input pxwCwk] */
		uint64_t pixew_cwk_10_khz_out =
				(uint64_t)we16_to_cpu(pawams.usPixewCwock);
		uint64_t pixew_cwk = (uint64_t)bp_pawams->pixew_cwock;

		if (pixew_cwock_10KHz_in != 0) {
			bp_pawams->adjusted_pixew_cwock =
					div_u64(pixew_cwk * pixew_cwk_10_khz_out,
							pixew_cwock_10KHz_in);
		} ewse {
			bp_pawams->adjusted_pixew_cwock = 0;
			BWEAK_TO_DEBUGGEW();
		}

		wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}

static enum bp_wesuwt adjust_dispway_pww_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	ADJUST_DISPWAY_PWW_PS_AWWOCATION_V3 pawams;
	uint32_t pixew_cwk_10_kHz_in = bp_pawams->pixew_cwock / 10;

	memset(&pawams, 0, sizeof(pawams));

	/* We need to convewt fwom KHz units into 10KHz units and then convewt
	 * output pixew cwock back 10KHz-->KHz */
	pawams.sInput.usPixewCwock = cpu_to_we16((uint16_t)pixew_cwk_10_kHz_in);
	pawams.sInput.ucTwansmittewID =
			bp->cmd_hewpew->encodew_id_to_atom(
					daw_gwaphics_object_id_get_encodew_id(
							bp_pawams->encodew_object_id));
	pawams.sInput.ucEncodeMode =
			(uint8_t)bp->cmd_hewpew->encodew_mode_bp_to_atom(
					bp_pawams->signaw_type, fawse);

	if (bp_pawams->ss_enabwe == twue)
		pawams.sInput.ucDispPwwConfig |= DISPPWW_CONFIG_SS_ENABWE;

	if (bp_pawams->signaw_type == SIGNAW_TYPE_DVI_DUAW_WINK)
		pawams.sInput.ucDispPwwConfig |= DISPPWW_CONFIG_DUAW_WINK;

	if (EXEC_BIOS_CMD_TABWE(AdjustDispwayPww, pawams)) {
		/* Convewt output pixew cwock back 10KHz-->KHz: muwtipwy
		 * owiginaw pixew cwock in KHz by watio
		 * [output pxwCwk/input pxwCwk] */
		uint64_t pixew_cwk_10_khz_out =
				(uint64_t)we32_to_cpu(pawams.sOutput.uwDispPwwFweq);
		uint64_t pixew_cwk = (uint64_t)bp_pawams->pixew_cwock;

		if (pixew_cwk_10_kHz_in != 0) {
			bp_pawams->adjusted_pixew_cwock =
					div_u64(pixew_cwk * pixew_cwk_10_khz_out,
							pixew_cwk_10_kHz_in);
		} ewse {
			bp_pawams->adjusted_pixew_cwock = 0;
			BWEAK_TO_DEBUGGEW();
		}

		bp_pawams->wefewence_dividew = pawams.sOutput.ucWefDiv;
		bp_pawams->pixew_cwock_post_dividew = pawams.sOutput.ucPostDiv;

		wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  DAC ENCODEW CONTWOW
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt dac1_encodew_contwow_v1(
	stwuct bios_pawsew *bp,
	boow enabwe,
	uint32_t pixew_cwock,
	uint8_t dac_standawd);
static enum bp_wesuwt dac2_encodew_contwow_v1(
	stwuct bios_pawsew *bp,
	boow enabwe,
	uint32_t pixew_cwock,
	uint8_t dac_standawd);

static void init_dac_encodew_contwow(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(DAC1EncodewContwow)) {
	case 1:
		bp->cmd_tbw.dac1_encodew_contwow = dac1_encodew_contwow_v1;
		bweak;
	defauwt:
		bp->cmd_tbw.dac1_encodew_contwow = NUWW;
		bweak;
	}
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(DAC2EncodewContwow)) {
	case 1:
		bp->cmd_tbw.dac2_encodew_contwow = dac2_encodew_contwow_v1;
		bweak;
	defauwt:
		bp->cmd_tbw.dac2_encodew_contwow = NUWW;
		bweak;
	}
}

static void dac_encodew_contwow_pwepawe_pawams(
	DAC_ENCODEW_CONTWOW_PS_AWWOCATION *pawams,
	boow enabwe,
	uint32_t pixew_cwock,
	uint8_t dac_standawd)
{
	pawams->ucDacStandawd = dac_standawd;
	if (enabwe)
		pawams->ucAction = ATOM_ENABWE;
	ewse
		pawams->ucAction = ATOM_DISABWE;

	/* We need to convewt fwom KHz units into 10KHz units
	 * it wooks as if the TvContwow do not cawe about pixew cwock
	 */
	pawams->usPixewCwock = cpu_to_we16((uint16_t)(pixew_cwock / 10));
}

static enum bp_wesuwt dac1_encodew_contwow_v1(
	stwuct bios_pawsew *bp,
	boow enabwe,
	uint32_t pixew_cwock,
	uint8_t dac_standawd)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DAC_ENCODEW_CONTWOW_PS_AWWOCATION pawams;

	dac_encodew_contwow_pwepawe_pawams(
		&pawams,
		enabwe,
		pixew_cwock,
		dac_standawd);

	if (EXEC_BIOS_CMD_TABWE(DAC1EncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt dac2_encodew_contwow_v1(
	stwuct bios_pawsew *bp,
	boow enabwe,
	uint32_t pixew_cwock,
	uint8_t dac_standawd)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DAC_ENCODEW_CONTWOW_PS_AWWOCATION pawams;

	dac_encodew_contwow_pwepawe_pawams(
		&pawams,
		enabwe,
		pixew_cwock,
		dac_standawd);

	if (EXEC_BIOS_CMD_TABWE(DAC2EncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  DAC OUTPUT CONTWOW
 **
 ********************************************************************************
 *******************************************************************************/
static enum bp_wesuwt dac1_output_contwow_v1(
	stwuct bios_pawsew *bp,
	boow enabwe);
static enum bp_wesuwt dac2_output_contwow_v1(
	stwuct bios_pawsew *bp,
	boow enabwe);

static void init_dac_output_contwow(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(DAC1OutputContwow)) {
	case 1:
		bp->cmd_tbw.dac1_output_contwow = dac1_output_contwow_v1;
		bweak;
	defauwt:
		bp->cmd_tbw.dac1_output_contwow = NUWW;
		bweak;
	}
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(DAC2OutputContwow)) {
	case 1:
		bp->cmd_tbw.dac2_output_contwow = dac2_output_contwow_v1;
		bweak;
	defauwt:
		bp->cmd_tbw.dac2_output_contwow = NUWW;
		bweak;
	}
}

static enum bp_wesuwt dac1_output_contwow_v1(
	stwuct bios_pawsew *bp, boow enabwe)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION pawams;

	if (enabwe)
		pawams.ucAction = ATOM_ENABWE;
	ewse
		pawams.ucAction = ATOM_DISABWE;

	if (EXEC_BIOS_CMD_TABWE(DAC1OutputContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt dac2_output_contwow_v1(
	stwuct bios_pawsew *bp, boow enabwe)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	DISPWAY_DEVICE_OUTPUT_CONTWOW_PS_AWWOCATION pawams;

	if (enabwe)
		pawams.ucAction = ATOM_ENABWE;
	ewse
		pawams.ucAction = ATOM_DISABWE;

	if (EXEC_BIOS_CMD_TABWE(DAC2OutputContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  SET CWTC TIMING
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt set_cwtc_using_dtd_timing_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams);
static enum bp_wesuwt set_cwtc_timing_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams);

static void init_set_cwtc_timing(stwuct bios_pawsew *bp)
{
	uint32_t dtd_vewsion =
			BIOS_CMD_TABWE_PAWA_WEVISION(SetCWTC_UsingDTDTiming);
	if (dtd_vewsion > 2)
		switch (dtd_vewsion) {
		case 3:
			bp->cmd_tbw.set_cwtc_timing =
					set_cwtc_using_dtd_timing_v3;
			bweak;
		defauwt:
			dm_output_to_consowe("Don't have set_cwtc_timing fow dtd v%d\n",
				 dtd_vewsion);
			bp->cmd_tbw.set_cwtc_timing = NUWW;
			bweak;
		}
	ewse
		switch (BIOS_CMD_TABWE_PAWA_WEVISION(SetCWTC_Timing)) {
		case 1:
			bp->cmd_tbw.set_cwtc_timing = set_cwtc_timing_v1;
			bweak;
		defauwt:
			dm_output_to_consowe("Don't have set_cwtc_timing fow v%d\n",
				 BIOS_CMD_TABWE_PAWA_WEVISION(SetCWTC_Timing));
			bp->cmd_tbw.set_cwtc_timing = NUWW;
			bweak;
		}
}

static enum bp_wesuwt set_cwtc_timing_v1(
	stwuct bios_pawsew *bp,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	SET_CWTC_TIMING_PAWAMETEWS_PS_AWWOCATION pawams = {0};
	uint8_t atom_contwowwew_id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(
			bp_pawams->contwowwew_id, &atom_contwowwew_id))
		pawams.ucCWTC = atom_contwowwew_id;

	pawams.usH_Totaw = cpu_to_we16((uint16_t)(bp_pawams->h_totaw));
	pawams.usH_Disp = cpu_to_we16((uint16_t)(bp_pawams->h_addwessabwe));
	pawams.usH_SyncStawt = cpu_to_we16((uint16_t)(bp_pawams->h_sync_stawt));
	pawams.usH_SyncWidth = cpu_to_we16((uint16_t)(bp_pawams->h_sync_width));
	pawams.usV_Totaw = cpu_to_we16((uint16_t)(bp_pawams->v_totaw));
	pawams.usV_Disp = cpu_to_we16((uint16_t)(bp_pawams->v_addwessabwe));
	pawams.usV_SyncStawt =
			cpu_to_we16((uint16_t)(bp_pawams->v_sync_stawt));
	pawams.usV_SyncWidth =
			cpu_to_we16((uint16_t)(bp_pawams->v_sync_width));

	/* VBIOS does not expect any vawue except zewo into this caww, fow
	 * undewscan use anothew entwy PwogwamOvewscan caww but when mode
	 * 1776x1000 with the ovewscan 72x44 .e.i. 1920x1080 @30 DAW2 is ok,
	 * but when same ,but 60 Hz thewe is cowwuption
	 * DAW1 does not awwow the mode 1776x1000@60
	 */
	pawams.ucOvewscanWight = (uint8_t)bp_pawams->h_ovewscan_wight;
	pawams.ucOvewscanWeft = (uint8_t)bp_pawams->h_ovewscan_weft;
	pawams.ucOvewscanBottom = (uint8_t)bp_pawams->v_ovewscan_bottom;
	pawams.ucOvewscanTop = (uint8_t)bp_pawams->v_ovewscan_top;

	if (0 == bp_pawams->fwags.HSYNC_POSITIVE_POWAWITY)
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_HSYNC_POWAWITY);

	if (0 == bp_pawams->fwags.VSYNC_POSITIVE_POWAWITY)
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_VSYNC_POWAWITY);

	if (bp_pawams->fwags.INTEWWACE) {
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_INTEWWACE);

		/* owiginaw DAW code has this condition to appwy tis fow
		 * non-TV/CV onwy due to compwex MV testing fow possibwe
		 * impact
		 * if (pACPawametews->signaw != SignawType_YPbPw &&
		 *  pACPawametews->signaw != SignawType_Composite &&
		 *  pACPawametews->signaw != SignawType_SVideo)
		 */
		/* HW wiww deduct 0.5 wine fwom 2nd feiwd.
		 * i.e. fow 1080i, it is 2 wines fow 1st fiewd, 2.5
		 * wines fow the 2nd feiwd. we need input as 5 instead
		 * of 4, but it is 4 eithew fwom Edid data
		 * (spec CEA 861) ow CEA timing tabwe.
		 */
		pawams.usV_SyncStawt =
				cpu_to_we16((uint16_t)(bp_pawams->v_sync_stawt + 1));
	}

	if (bp_pawams->fwags.HOWZ_COUNT_BY_TWO)
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_DOUBWE_CWOCK_MODE);

	if (EXEC_BIOS_CMD_TABWE(SetCWTC_Timing, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt set_cwtc_using_dtd_timing_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_hw_cwtc_timing_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;
	SET_CWTC_USING_DTD_TIMING_PAWAMETEWS pawams = {0};
	uint8_t atom_contwowwew_id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(
			bp_pawams->contwowwew_id, &atom_contwowwew_id))
		pawams.ucCWTC = atom_contwowwew_id;

	/* bios usH_Size wants h addwessabwe size */
	pawams.usH_Size = cpu_to_we16((uint16_t)bp_pawams->h_addwessabwe);
	/* bios usH_Bwanking_Time wants bowdews incwuded in bwanking */
	pawams.usH_Bwanking_Time =
			cpu_to_we16((uint16_t)(bp_pawams->h_totaw - bp_pawams->h_addwessabwe));
	/* bios usV_Size wants v addwessabwe size */
	pawams.usV_Size = cpu_to_we16((uint16_t)bp_pawams->v_addwessabwe);
	/* bios usV_Bwanking_Time wants bowdews incwuded in bwanking */
	pawams.usV_Bwanking_Time =
			cpu_to_we16((uint16_t)(bp_pawams->v_totaw - bp_pawams->v_addwessabwe));
	/* bios usHSyncOffset is the offset fwom the end of h addwessabwe,
	 * ouw howizontawSyncStawt is the offset fwom the beginning
	 * of h addwessabwe */
	pawams.usH_SyncOffset =
			cpu_to_we16((uint16_t)(bp_pawams->h_sync_stawt - bp_pawams->h_addwessabwe));
	pawams.usH_SyncWidth = cpu_to_we16((uint16_t)bp_pawams->h_sync_width);
	/* bios usHSyncOffset is the offset fwom the end of v addwessabwe,
	 * ouw vewticawSyncStawt is the offset fwom the beginning of
	 * v addwessabwe */
	pawams.usV_SyncOffset =
			cpu_to_we16((uint16_t)(bp_pawams->v_sync_stawt - bp_pawams->v_addwessabwe));
	pawams.usV_SyncWidth = cpu_to_we16((uint16_t)bp_pawams->v_sync_width);

	/* we assume that ovewscan fwom owiginaw timing does not get biggew
	 * than 255
	 * we wiww pwogwam aww the bowdews in the Set CWTC Ovewscan caww bewow
	 */

	if (0 == bp_pawams->fwags.HSYNC_POSITIVE_POWAWITY)
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_HSYNC_POWAWITY);

	if (0 == bp_pawams->fwags.VSYNC_POSITIVE_POWAWITY)
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_VSYNC_POWAWITY);

	if (bp_pawams->fwags.INTEWWACE)	{
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_INTEWWACE);

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
			we16_add_cpu(&pawams.usV_SyncOffset, 1);
		}
	}

	if (bp_pawams->fwags.HOWZ_COUNT_BY_TWO)
		pawams.susModeMiscInfo.usAccess =
				cpu_to_we16(we16_to_cpu(pawams.susModeMiscInfo.usAccess) | ATOM_DOUBWE_CWOCK_MODE);

	if (EXEC_BIOS_CMD_TABWE(SetCWTC_UsingDTDTiming, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABWE CWTC
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt enabwe_cwtc_v1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id contwowwew_id,
	boow enabwe);

static void init_enabwe_cwtc(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(EnabweCWTC)) {
	case 1:
		bp->cmd_tbw.enabwe_cwtc = enabwe_cwtc_v1;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have enabwe_cwtc fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(EnabweCWTC));
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
	ENABWE_CWTC_PAWAMETEWS pawams = {0};
	uint8_t id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(contwowwew_id, &id))
		pawams.ucCWTC = id;
	ewse
		wetuwn BP_WESUWT_BADINPUT;

	if (enabwe)
		pawams.ucEnabwe = ATOM_ENABWE;
	ewse
		pawams.ucEnabwe = ATOM_DISABWE;

	if (EXEC_BIOS_CMD_TABWE(EnabweCWTC, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABWE CWTC MEM WEQ
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt enabwe_cwtc_mem_weq_v1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id contwowwew_id,
	boow enabwe);

static void init_enabwe_cwtc_mem_weq(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(EnabweCWTCMemWeq)) {
	case 1:
		bp->cmd_tbw.enabwe_cwtc_mem_weq = enabwe_cwtc_mem_weq_v1;
		bweak;
	defauwt:
		bp->cmd_tbw.enabwe_cwtc_mem_weq = NUWW;
		bweak;
	}
}

static enum bp_wesuwt enabwe_cwtc_mem_weq_v1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id contwowwew_id,
	boow enabwe)
{
	boow wesuwt = BP_WESUWT_BADINPUT;
	ENABWE_CWTC_PAWAMETEWS pawams = {0};
	uint8_t id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(contwowwew_id, &id)) {
		pawams.ucCWTC = id;

		if (enabwe)
			pawams.ucEnabwe = ATOM_ENABWE;
		ewse
			pawams.ucEnabwe = ATOM_DISABWE;

		if (EXEC_BIOS_CMD_TABWE(EnabweCWTCMemWeq, pawams))
			wesuwt = BP_WESUWT_OK;
		ewse
			wesuwt = BP_WESUWT_FAIWUWE;
	}

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  DISPWAY PWW
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt pwogwam_cwock_v5(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);
static enum bp_wesuwt pwogwam_cwock_v6(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams);

static void init_pwogwam_cwock(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(SetPixewCwock)) {
	case 5:
		bp->cmd_tbw.pwogwam_cwock = pwogwam_cwock_v5;
		bweak;
	case 6:
		bp->cmd_tbw.pwogwam_cwock = pwogwam_cwock_v6;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have pwogwam_cwock fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(SetPixewCwock));
		bp->cmd_tbw.pwogwam_cwock = NUWW;
		bweak;
	}
}

static enum bp_wesuwt pwogwam_cwock_v5(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	SET_PIXEW_CWOCK_PS_AWWOCATION_V5 pawams;
	uint32_t atom_pww_id;

	memset(&pawams, 0, sizeof(pawams));
	if (!bp->cmd_hewpew->cwock_souwce_id_to_atom(
			bp_pawams->pww_id, &atom_pww_id)) {
		BWEAK_TO_DEBUGGEW(); /* Invawid Input!! */
		wetuwn BP_WESUWT_BADINPUT;
	}

	/* We need to convewt fwom KHz units into 10KHz units */
	pawams.sPCWKInput.ucPpww = (uint8_t) atom_pww_id;
	pawams.sPCWKInput.usPixewCwock =
			cpu_to_we16((uint16_t) (bp_pawams->tawget_pixew_cwock_100hz / 100));
	pawams.sPCWKInput.ucCWTC = (uint8_t) ATOM_CWTC_INVAWID;

	if (bp_pawams->fwags.SET_EXTEWNAW_WEF_DIV_SWC)
		pawams.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_MISC_WEF_DIV_SWC;

	if (EXEC_BIOS_CMD_TABWE(SetPixewCwock, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

static enum bp_wesuwt pwogwam_cwock_v6(
	stwuct bios_pawsew *bp,
	stwuct bp_pixew_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	SET_PIXEW_CWOCK_PS_AWWOCATION_V6 pawams;
	uint32_t atom_pww_id;

	memset(&pawams, 0, sizeof(pawams));

	if (!bp->cmd_hewpew->cwock_souwce_id_to_atom(
			bp_pawams->pww_id, &atom_pww_id)) {
		BWEAK_TO_DEBUGGEW(); /*Invawid Input!!*/
		wetuwn BP_WESUWT_BADINPUT;
	}

	/* We need to convewt fwom KHz units into 10KHz units */
	pawams.sPCWKInput.ucPpww = (uint8_t)atom_pww_id;
	pawams.sPCWKInput.uwDispEngCwkFweq =
			cpu_to_we32(bp_pawams->tawget_pixew_cwock_100hz / 100);

	if (bp_pawams->fwags.SET_EXTEWNAW_WEF_DIV_SWC)
		pawams.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_MISC_WEF_DIV_SWC;

	if (bp_pawams->fwags.SET_DISPCWK_DFS_BYPASS)
		pawams.sPCWKInput.ucMiscInfo |= PIXEW_CWOCK_V6_MISC_DPWEFCWK_BYPASS;

	if (EXEC_BIOS_CMD_TABWE(SetPixewCwock, pawams)) {
		/* Twue dispway cwock is wetuwned by VBIOS if DFS bypass
		 * is enabwed. */
		bp_pawams->dfs_bypass_dispway_cwock =
				(uint32_t)(we32_to_cpu(pawams.sPCWKInput.uwDispEngCwkFweq) * 10);
		wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  EXTEWNAW ENCODEW CONTWOW
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt extewnaw_encodew_contwow_v3(
	stwuct bios_pawsew *bp,
	stwuct bp_extewnaw_encodew_contwow *cntw);

static void init_extewnaw_encodew_contwow(
	stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(ExtewnawEncodewContwow)) {
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
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	/* we need use _PS_Awwoc stwuct */
	EXTEWNAW_ENCODEW_CONTWOW_PS_AWWOCATION_V3 pawams;
	EXTEWNAW_ENCODEW_CONTWOW_PAWAMETEWS_V3 *cntw_pawams;
	stwuct gwaphics_object_id encodew;
	boow is_input_signaw_dp = fawse;

	memset(&pawams, 0, sizeof(pawams));

	cntw_pawams = &pawams.sExtEncodew;

	encodew = cntw->encodew_id;

	/* check if encodew suppowts extewnaw encodew contwow tabwe */
	switch (daw_gwaphics_object_id_get_encodew_id(encodew)) {
	case ENCODEW_ID_EXTEWNAW_NUTMEG:
	case ENCODEW_ID_EXTEWNAW_TWAVIS:
		is_input_signaw_dp = twue;
		bweak;

	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn BP_WESUWT_BADINPUT;
	}

	/* Fiww infowmation based on the action
	 *
	 * Bit[6:4]: indicate extewnaw encodew, appwied to aww functions.
	 * =0: extewnaw encodew1, mapped to extewnaw encodew enum id1
	 * =1: extewnaw encodew2, mapped to extewnaw encodew enum id2
	 *
	 * enum ObjectEnumId
	 * {
	 *  EnumId_Unknown = 0,
	 *  EnumId_1,
	 *  EnumId_2,
	 * };
	 */
	cntw_pawams->ucConfig = (uint8_t)((encodew.enum_id - 1) << 4);

	switch (cntw->action) {
	case EXTEWNAW_ENCODEW_CONTWOW_INIT:
		/* output dispway connectow type. Onwy vawid in encodew
		 * initiawization */
		cntw_pawams->usConnectowId =
				cpu_to_we16((uint16_t)cntw->connectow_obj_id.id);
		bweak;
	case EXTEWNAW_ENCODEW_CONTWOW_SETUP:
		/* EXTEWNAW_ENCODEW_CONTWOW_PAWAMETEWS_V3 pixew cwock unit in
		 * 10KHz
		 * output dispway device pixew cwock fwequency in unit of 10KHz.
		 * Onwy vawid in setup and enabweoutput
		 */
		cntw_pawams->usPixewCwock =
				cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
		/* Indicate dispway output signaw type dwive by extewnaw
		 * encodew, onwy vawid in setup and enabweoutput */
		cntw_pawams->ucEncodewMode =
				(uint8_t)bp->cmd_hewpew->encodew_mode_bp_to_atom(
						cntw->signaw, fawse);

		if (is_input_signaw_dp) {
			/* Bit[0]: indicate wink wate, =1: 2.7Ghz, =0: 1.62Ghz,
			 * onwy vawid in encodew setup with DP mode. */
			if (WINK_WATE_HIGH == cntw->wink_wate)
				cntw_pawams->ucConfig |= 1;
			/* output cowow depth Indicate encodew data bpc fowmat
			 * in DP mode, onwy vawid in encodew setup in DP mode.
			 */
			cntw_pawams->ucBitPewCowow =
					(uint8_t)(cntw->cowow_depth);
		}
		/* Indicate how many wanes used by extewnaw encodew, onwy vawid
		 * in encodew setup and enabweoutput. */
		cntw_pawams->ucWaneNum = (uint8_t)(cntw->wanes_numbew);
		bweak;
	case EXTEWNAW_ENCODEW_CONTWOW_ENABWE:
		cntw_pawams->usPixewCwock =
				cpu_to_we16((uint16_t)(cntw->pixew_cwock / 10));
		cntw_pawams->ucEncodewMode =
				(uint8_t)bp->cmd_hewpew->encodew_mode_bp_to_atom(
						cntw->signaw, fawse);
		cntw_pawams->ucWaneNum = (uint8_t)cntw->wanes_numbew;
		bweak;
	defauwt:
		bweak;
	}

	cntw_pawams->ucAction = (uint8_t)cntw->action;

	if (EXEC_BIOS_CMD_TABWE(ExtewnawEncodewContwow, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  ENABWE DISPWAY POWEW GATING
 **
 ********************************************************************************
 *******************************************************************************/

static enum bp_wesuwt enabwe_disp_powew_gating_v2_1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id cwtc_id,
	enum bp_pipe_contwow_action action);

static void init_enabwe_disp_powew_gating(
	stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(EnabweDispPowewGating)) {
	case 1:
		bp->cmd_tbw.enabwe_disp_powew_gating =
				enabwe_disp_powew_gating_v2_1;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't enabwe_disp_powew_gating enabwe_cwtc fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(EnabweDispPowewGating));
		bp->cmd_tbw.enabwe_disp_powew_gating = NUWW;
		bweak;
	}
}

static enum bp_wesuwt enabwe_disp_powew_gating_v2_1(
	stwuct bios_pawsew *bp,
	enum contwowwew_id cwtc_id,
	enum bp_pipe_contwow_action action)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	ENABWE_DISP_POWEW_GATING_PS_AWWOCATION pawams = {0};
	uint8_t atom_cwtc_id;

	if (bp->cmd_hewpew->contwowwew_id_to_atom(cwtc_id, &atom_cwtc_id))
		pawams.ucDispPipeId = atom_cwtc_id;
	ewse
		wetuwn BP_WESUWT_BADINPUT;

	pawams.ucEnabwe =
			bp->cmd_hewpew->disp_powew_gating_action_to_atom(action);

	if (EXEC_BIOS_CMD_TABWE(EnabweDispPowewGating, pawams))
		wesuwt = BP_WESUWT_OK;

	wetuwn wesuwt;
}

/*******************************************************************************
 ********************************************************************************
 **
 **                  SET DCE CWOCK
 **
 ********************************************************************************
 *******************************************************************************/
static enum bp_wesuwt set_dce_cwock_v2_1(
	stwuct bios_pawsew *bp,
	stwuct bp_set_dce_cwock_pawametews *bp_pawams);

static void init_set_dce_cwock(stwuct bios_pawsew *bp)
{
	switch (BIOS_CMD_TABWE_PAWA_WEVISION(SetDCECwock)) {
	case 1:
		bp->cmd_tbw.set_dce_cwock = set_dce_cwock_v2_1;
		bweak;
	defauwt:
		dm_output_to_consowe("Don't have set_dce_cwock fow v%d\n",
			 BIOS_CMD_TABWE_PAWA_WEVISION(SetDCECwock));
		bp->cmd_tbw.set_dce_cwock = NUWW;
		bweak;
	}
}

static enum bp_wesuwt set_dce_cwock_v2_1(
	stwuct bios_pawsew *bp,
	stwuct bp_set_dce_cwock_pawametews *bp_pawams)
{
	enum bp_wesuwt wesuwt = BP_WESUWT_FAIWUWE;

	SET_DCE_CWOCK_PS_AWWOCATION_V2_1 pawams;
	uint32_t atom_pww_id;
	uint32_t atom_cwock_type;
	const stwuct command_tabwe_hewpew *cmd = bp->cmd_hewpew;

	memset(&pawams, 0, sizeof(pawams));

	if (!cmd->cwock_souwce_id_to_atom(bp_pawams->pww_id, &atom_pww_id) ||
			!cmd->dc_cwock_type_to_atom(bp_pawams->cwock_type, &atom_cwock_type))
		wetuwn BP_WESUWT_BADINPUT;

	pawams.asPawam.ucDCECwkSwc  = atom_pww_id;
	pawams.asPawam.ucDCECwkType = atom_cwock_type;

	if (bp_pawams->cwock_type == DCECWOCK_TYPE_DPWEFCWK) {
		if (bp_pawams->fwags.USE_GENWOCK_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.asPawam.ucDCECwkFwag |= DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENWK;

		if (bp_pawams->fwags.USE_PCIE_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.asPawam.ucDCECwkFwag |= DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_PCIE;

		if (bp_pawams->fwags.USE_XTAWIN_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.asPawam.ucDCECwkFwag |= DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_XTAWIN;

		if (bp_pawams->fwags.USE_GENEWICA_AS_SOUWCE_FOW_DPWEFCWK)
			pawams.asPawam.ucDCECwkFwag |= DCE_CWOCK_FWAG_PWW_WEFCWK_SWC_GENEWICA;
	}
	ewse
		/* onwy pwogwam cwock fwequency if dispway cwock is used; VBIOS wiww pwogwam DPWEFCWK */
		/* We need to convewt fwom KHz units into 10KHz units */
		pawams.asPawam.uwDCECwkFweq = cpu_to_we32(bp_pawams->tawget_cwock_fwequency / 10);

	if (EXEC_BIOS_CMD_TABWE(SetDCECwock, pawams)) {
		/* Convewt fwom 10KHz units back to KHz */
		bp_pawams->tawget_cwock_fwequency = we32_to_cpu(pawams.asPawam.uwDCECwkFweq) * 10;
		wesuwt = BP_WESUWT_OK;
	}

	wetuwn wesuwt;
}
