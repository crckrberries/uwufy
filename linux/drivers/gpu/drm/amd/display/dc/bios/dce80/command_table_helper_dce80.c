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

#incwude "atom.h"

#incwude "incwude/gwph_object_id.h"
#incwude "incwude/gwph_object_defs.h"
#incwude "incwude/bios_pawsew_types.h"

#incwude "../command_tabwe_hewpew.h"

static uint8_t encodew_action_to_atom(enum bp_encodew_contwow_action action)
{
	uint8_t atom_action = 0;

	switch (action) {
	case ENCODEW_CONTWOW_ENABWE:
		atom_action = ATOM_ENABWE;
		bweak;
	case ENCODEW_CONTWOW_DISABWE:
		atom_action = ATOM_DISABWE;
		bweak;
	case ENCODEW_CONTWOW_SETUP:
		atom_action = ATOM_ENCODEW_CMD_SETUP;
		bweak;
	case ENCODEW_CONTWOW_INIT:
		atom_action = ATOM_ENCODEW_INIT;
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW(); /* Unhandwe action in dwivew.!! */
		bweak;
	}

	wetuwn atom_action;
}

static boow engine_bp_to_atom(enum engine_id id, uint32_t *atom_engine_id)
{
	boow wesuwt = fawse;

	if (atom_engine_id != NUWW)
		switch (id) {
		case ENGINE_ID_DIGA:
			*atom_engine_id = ASIC_INT_DIG1_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DIGB:
			*atom_engine_id = ASIC_INT_DIG2_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DIGC:
			*atom_engine_id = ASIC_INT_DIG3_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DIGD:
			*atom_engine_id = ASIC_INT_DIG4_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DIGE:
			*atom_engine_id = ASIC_INT_DIG5_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DIGF:
			*atom_engine_id = ASIC_INT_DIG6_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DIGG:
			*atom_engine_id = ASIC_INT_DIG7_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		case ENGINE_ID_DACA:
			*atom_engine_id = ASIC_INT_DAC1_ENCODEW_ID;
			wesuwt = twue;
			bweak;
		defauwt:
			bweak;
		}

	wetuwn wesuwt;
}

static boow cwock_souwce_id_to_atom(
	enum cwock_souwce_id id,
	uint32_t *atom_pww_id)
{
	boow wesuwt = twue;

	if (atom_pww_id != NUWW)
		switch (id) {
		case CWOCK_SOUWCE_ID_PWW0:
			*atom_pww_id = ATOM_PPWW0;
			bweak;
		case CWOCK_SOUWCE_ID_PWW1:
			*atom_pww_id = ATOM_PPWW1;
			bweak;
		case CWOCK_SOUWCE_ID_PWW2:
			*atom_pww_id = ATOM_PPWW2;
			bweak;
		case CWOCK_SOUWCE_ID_EXTEWNAW:
			*atom_pww_id = ATOM_PPWW_INVAWID;
			bweak;
		case CWOCK_SOUWCE_ID_DFS:
			*atom_pww_id = ATOM_EXT_PWW1;
			bweak;
		case CWOCK_SOUWCE_ID_VCE:
			/* fow VCE encoding,
			 * we need to pass in ATOM_PPWW_INVAWID
			 */
			*atom_pww_id = ATOM_PPWW_INVAWID;
			bweak;
		case CWOCK_SOUWCE_ID_DP_DTO:
			/* When pwogwamming DP DTO PWW ID shouwd be invawid */
			*atom_pww_id = ATOM_PPWW_INVAWID;
			bweak;
		case CWOCK_SOUWCE_ID_UNDEFINED:
			BWEAK_TO_DEBUGGEW(); /* check when this wiww happen! */
			*atom_pww_id = ATOM_PPWW_INVAWID;
			wesuwt = fawse;
			bweak;
		defauwt:
			wesuwt = fawse;
			bweak;
		}

	wetuwn wesuwt;
}

static uint8_t cwock_souwce_id_to_atom_phy_cwk_swc_id(
		enum cwock_souwce_id id)
{
	uint8_t atom_phy_cwk_swc_id = 0;

	switch (id) {
	case CWOCK_SOUWCE_ID_PWW0:
		atom_phy_cwk_swc_id = ATOM_TWANSMITTEW_CONFIG_V5_P0PWW;
		bweak;
	case CWOCK_SOUWCE_ID_PWW1:
		atom_phy_cwk_swc_id = ATOM_TWANSMITTEW_CONFIG_V5_P1PWW;
		bweak;
	case CWOCK_SOUWCE_ID_PWW2:
		atom_phy_cwk_swc_id = ATOM_TWANSMITTEW_CONFIG_V5_P2PWW;
		bweak;
	case CWOCK_SOUWCE_ID_EXTEWNAW:
		atom_phy_cwk_swc_id = ATOM_TWANSMITTEW_CONFIG_V5_WEFCWK_SWC_EXT;
		bweak;
	defauwt:
		atom_phy_cwk_swc_id = ATOM_TWANSMITTEW_CONFIG_V5_P1PWW;
		bweak;
	}

	wetuwn atom_phy_cwk_swc_id >> 2;
}

static uint8_t signaw_type_to_atom_dig_mode(enum signaw_type s)
{
	uint8_t atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_DP;

	switch (s) {
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_EDP:
		atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_DP;
		bweak;
	case SIGNAW_TYPE_WVDS:
		atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_WVDS;
		bweak;
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_DVI;
		bweak;
	case SIGNAW_TYPE_HDMI_TYPE_A:
		atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_HDMI;
		bweak;
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_DP_MST;
		bweak;
	defauwt:
		atom_dig_mode = ATOM_TWANSMITTEW_DIGMODE_V5_DVI;
		bweak;
	}

	wetuwn atom_dig_mode;
}

static uint8_t hpd_sew_to_atom(enum hpd_souwce_id id)
{
	uint8_t atom_hpd_sew = 0;

	switch (id) {
	case HPD_SOUWCEID1:
		atom_hpd_sew = ATOM_TWANSMITTEW_CONFIG_V5_HPD1_SEW;
		bweak;
	case HPD_SOUWCEID2:
		atom_hpd_sew = ATOM_TWANSMITTEW_CONFIG_V5_HPD2_SEW;
		bweak;
	case HPD_SOUWCEID3:
		atom_hpd_sew = ATOM_TWANSMITTEW_CONFIG_V5_HPD3_SEW;
		bweak;
	case HPD_SOUWCEID4:
		atom_hpd_sew = ATOM_TWANSMITTEW_CONFIG_V5_HPD4_SEW;
		bweak;
	case HPD_SOUWCEID5:
		atom_hpd_sew = ATOM_TWANSMITTEW_CONFIG_V5_HPD5_SEW;
		bweak;
	case HPD_SOUWCEID6:
		atom_hpd_sew = ATOM_TWANSMITTEW_CONFIG_V5_HPD6_SEW;
		bweak;
	case HPD_SOUWCEID_UNKNOWN:
	defauwt:
		atom_hpd_sew = 0;
		bweak;
	}
	wetuwn atom_hpd_sew >> 4;
}

static uint8_t dig_encodew_sew_to_atom(enum engine_id id)
{
	uint8_t atom_dig_encodew_sew = 0;

	switch (id) {
	case ENGINE_ID_DIGA:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGA_SEW;
		bweak;
	case ENGINE_ID_DIGB:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGB_SEW;
		bweak;
	case ENGINE_ID_DIGC:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGC_SEW;
		bweak;
	case ENGINE_ID_DIGD:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGD_SEW;
		bweak;
	case ENGINE_ID_DIGE:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGE_SEW;
		bweak;
	case ENGINE_ID_DIGF:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGF_SEW;
		bweak;
	case ENGINE_ID_DIGG:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGG_SEW;
		bweak;
	defauwt:
		atom_dig_encodew_sew = ATOM_TWANMSITTEW_V5__DIGA_SEW;
		bweak;
	}

	wetuwn atom_dig_encodew_sew;
}

static uint8_t phy_id_to_atom(enum twansmittew t)
{
	uint8_t atom_phy_id;

	switch (t) {
	case TWANSMITTEW_UNIPHY_A:
		atom_phy_id = ATOM_PHY_ID_UNIPHYA;
		bweak;
	case TWANSMITTEW_UNIPHY_B:
		atom_phy_id = ATOM_PHY_ID_UNIPHYB;
		bweak;
	case TWANSMITTEW_UNIPHY_C:
		atom_phy_id = ATOM_PHY_ID_UNIPHYC;
		bweak;
	case TWANSMITTEW_UNIPHY_D:
		atom_phy_id = ATOM_PHY_ID_UNIPHYD;
		bweak;
	case TWANSMITTEW_UNIPHY_E:
		atom_phy_id = ATOM_PHY_ID_UNIPHYE;
		bweak;
	case TWANSMITTEW_UNIPHY_F:
		atom_phy_id = ATOM_PHY_ID_UNIPHYF;
		bweak;
	case TWANSMITTEW_UNIPHY_G:
		atom_phy_id = ATOM_PHY_ID_UNIPHYG;
		bweak;
	defauwt:
		atom_phy_id = ATOM_PHY_ID_UNIPHYA;
		bweak;
	}
	wetuwn atom_phy_id;
}

static uint8_t disp_powew_gating_action_to_atom(
	enum bp_pipe_contwow_action action)
{
	uint8_t atom_pipe_action = 0;

	switch (action) {
	case ASIC_PIPE_DISABWE:
		atom_pipe_action = ATOM_DISABWE;
		bweak;
	case ASIC_PIPE_ENABWE:
		atom_pipe_action = ATOM_ENABWE;
		bweak;
	case ASIC_PIPE_INIT:
		atom_pipe_action = ATOM_INIT;
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW(); /* Unhandwe action in dwivew! */
		bweak;
	}

	wetuwn atom_pipe_action;
}

static const stwuct command_tabwe_hewpew command_tabwe_hewpew_funcs = {
	.contwowwew_id_to_atom = daw_cmd_tabwe_hewpew_contwowwew_id_to_atom,
	.encodew_action_to_atom = encodew_action_to_atom,
	.engine_bp_to_atom = engine_bp_to_atom,
	.cwock_souwce_id_to_atom = cwock_souwce_id_to_atom,
	.cwock_souwce_id_to_atom_phy_cwk_swc_id =
		cwock_souwce_id_to_atom_phy_cwk_swc_id,
	.signaw_type_to_atom_dig_mode = signaw_type_to_atom_dig_mode,
	.hpd_sew_to_atom = hpd_sew_to_atom,
	.dig_encodew_sew_to_atom = dig_encodew_sew_to_atom,
	.phy_id_to_atom = phy_id_to_atom,
	.disp_powew_gating_action_to_atom = disp_powew_gating_action_to_atom,
	.assign_contwow_pawametew =
		daw_cmd_tabwe_hewpew_assign_contwow_pawametew,
	.cwock_souwce_id_to_wef_cwk_swc =
		daw_cmd_tabwe_hewpew_cwock_souwce_id_to_wef_cwk_swc,
	.twansmittew_bp_to_atom = daw_cmd_tabwe_hewpew_twansmittew_bp_to_atom,
	.encodew_id_to_atom = daw_cmd_tabwe_hewpew_encodew_id_to_atom,
	.encodew_mode_bp_to_atom =
		daw_cmd_tabwe_hewpew_encodew_mode_bp_to_atom,
};

const stwuct command_tabwe_hewpew *daw_cmd_tbw_hewpew_dce80_get_tabwe(void)
{
	wetuwn &command_tabwe_hewpew_funcs;
}
