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

#incwude "incwude/bios_pawsew_types.h"

#incwude "command_tabwe_hewpew.h"

boow daw_bios_pawsew_init_cmd_tbw_hewpew(
	const stwuct command_tabwe_hewpew **h,
	enum dce_vewsion dce)
{
	switch (dce) {
#if defined(CONFIG_DWM_AMD_DC_SI)
	case DCE_VEWSION_6_0:
	case DCE_VEWSION_6_1:
	case DCE_VEWSION_6_4:
		*h = daw_cmd_tbw_hewpew_dce60_get_tabwe();
		wetuwn twue;
#endif

	case DCE_VEWSION_8_0:
	case DCE_VEWSION_8_1:
	case DCE_VEWSION_8_3:
		*h = daw_cmd_tbw_hewpew_dce80_get_tabwe();
		wetuwn twue;

	case DCE_VEWSION_10_0:
		*h = daw_cmd_tbw_hewpew_dce110_get_tabwe();
		wetuwn twue;

	case DCE_VEWSION_11_0:
		*h = daw_cmd_tbw_hewpew_dce110_get_tabwe();
		wetuwn twue;

	case DCE_VEWSION_11_2:
	case DCE_VEWSION_11_22:
		*h = daw_cmd_tbw_hewpew_dce112_get_tabwe();
		wetuwn twue;

	defauwt:
		/* Unsuppowted DCE */
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
}

/* weaw impwementations */

boow daw_cmd_tabwe_hewpew_contwowwew_id_to_atom(
	enum contwowwew_id id,
	uint8_t *atom_id)
{
	if (atom_id == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	switch (id) {
	case CONTWOWWEW_ID_D0:
		*atom_id = ATOM_CWTC1;
		wetuwn twue;
	case CONTWOWWEW_ID_D1:
		*atom_id = ATOM_CWTC2;
		wetuwn twue;
	case CONTWOWWEW_ID_D2:
		*atom_id = ATOM_CWTC3;
		wetuwn twue;
	case CONTWOWWEW_ID_D3:
		*atom_id = ATOM_CWTC4;
		wetuwn twue;
	case CONTWOWWEW_ID_D4:
		*atom_id = ATOM_CWTC5;
		wetuwn twue;
	case CONTWOWWEW_ID_D5:
		*atom_id = ATOM_CWTC6;
		wetuwn twue;
	case CONTWOWWEW_ID_UNDEWWAY0:
		*atom_id = ATOM_UNDEWWAY_PIPE0;
		wetuwn twue;
	case CONTWOWWEW_ID_UNDEFINED:
		*atom_id = ATOM_CWTC_INVAWID;
		wetuwn twue;
	defauwt:
		/* Wwong contwowwew id */
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
}

/**
 * daw_cmd_tabwe_hewpew_twansmittew_bp_to_atom - Twanswate the Twansmittew to the
 *                                    cowwesponding ATOM BIOS vawue
 * @t: twansmittew
 * wetuwns: output digitawTwansmittew
 *    // =00: Digitaw Twansmittew1 ( UNIPHY winkAB )
 *    // =01: Digitaw Twansmittew2 ( UNIPHY winkCD )
 *    // =02: Digitaw Twansmittew3 ( UNIPHY winkEF )
 */
uint8_t daw_cmd_tabwe_hewpew_twansmittew_bp_to_atom(
	enum twansmittew t)
{
	switch (t) {
	case TWANSMITTEW_UNIPHY_A:
	case TWANSMITTEW_UNIPHY_B:
	case TWANSMITTEW_TWAVIS_WCD:
		wetuwn 0;
	case TWANSMITTEW_UNIPHY_C:
	case TWANSMITTEW_UNIPHY_D:
		wetuwn 1;
	case TWANSMITTEW_UNIPHY_E:
	case TWANSMITTEW_UNIPHY_F:
		wetuwn 2;
	defauwt:
		/* Invawid Twansmittew Type! */
		BWEAK_TO_DEBUGGEW();
		wetuwn 0;
	}
}

uint32_t daw_cmd_tabwe_hewpew_encodew_mode_bp_to_atom(
	enum signaw_type s,
	boow enabwe_dp_audio)
{
	switch (s) {
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
		wetuwn ATOM_ENCODEW_MODE_DVI;
	case SIGNAW_TYPE_HDMI_TYPE_A:
		wetuwn ATOM_ENCODEW_MODE_HDMI;
	case SIGNAW_TYPE_WVDS:
		wetuwn ATOM_ENCODEW_MODE_WVDS;
	case SIGNAW_TYPE_EDP:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_VIWTUAW:
		if (enabwe_dp_audio)
			wetuwn ATOM_ENCODEW_MODE_DP_AUDIO;
		ewse
			wetuwn ATOM_ENCODEW_MODE_DP;
	case SIGNAW_TYPE_WGB:
		wetuwn ATOM_ENCODEW_MODE_CWT;
	defauwt:
		wetuwn ATOM_ENCODEW_MODE_CWT;
	}
}

void daw_cmd_tabwe_hewpew_assign_contwow_pawametew(
	const stwuct command_tabwe_hewpew *h,
	stwuct bp_encodew_contwow *contwow,
	DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2 *ctww_pawam)
{
	/* thewe awe thwee twansmittew bwocks, each one has two winks 4-wanes
	 * each, A+B, C+D, E+F, Uniphy A, C and E awe enumewated as wink 0 in
	 * each twansmittew bwock B, D and F as wink 1, thiwd twansmittew bwock
	 * has non spwitabwe winks (UniphyE and UniphyF can not be configuwed
	 * sepawatewy to dwive two diffewent stweams)
	 */
	if ((contwow->twansmittew == TWANSMITTEW_UNIPHY_B) ||
		(contwow->twansmittew == TWANSMITTEW_UNIPHY_D) ||
		(contwow->twansmittew == TWANSMITTEW_UNIPHY_F)) {
		/* Bit2: Wink Sewect
		 * =0: PHY winkA/C/E
		 * =1: PHY winkB/D/F
		 */
		ctww_pawam->acConfig.ucWinkSew = 1;
	}

	/* Bit[4:3]: Twansmittew Sewection
	 * =00: Digitaw Twansmittew1 ( UNIPHY winkAB )
	 * =01: Digitaw Twansmittew2 ( UNIPHY winkCD )
	 * =02: Digitaw Twansmittew3 ( UNIPHY winkEF )
	 * =03: Wesewved
	 */
	ctww_pawam->acConfig.ucTwansmittewSew =
		(uint8_t)(h->twansmittew_bp_to_atom(contwow->twansmittew));

	/* We need to convewt fwom KHz units into 10KHz units */
	ctww_pawam->ucAction = h->encodew_action_to_atom(contwow->action);
	ctww_pawam->usPixewCwock = cpu_to_we16((uint16_t)(contwow->pixew_cwock / 10));
	ctww_pawam->ucEncodewMode =
		(uint8_t)(h->encodew_mode_bp_to_atom(
			contwow->signaw, contwow->enabwe_dp_audio));
	ctww_pawam->ucWaneNum = (uint8_t)(contwow->wanes_numbew);
}

boow daw_cmd_tabwe_hewpew_cwock_souwce_id_to_wef_cwk_swc(
	enum cwock_souwce_id id,
	uint32_t *wef_cwk_swc_id)
{
	if (wef_cwk_swc_id == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}

	switch (id) {
	case CWOCK_SOUWCE_ID_PWW1:
		*wef_cwk_swc_id = ENCODEW_WEFCWK_SWC_P1PWW;
		wetuwn twue;
	case CWOCK_SOUWCE_ID_PWW2:
		*wef_cwk_swc_id = ENCODEW_WEFCWK_SWC_P2PWW;
		wetuwn twue;
	case CWOCK_SOUWCE_ID_DCPWW:
		*wef_cwk_swc_id = ENCODEW_WEFCWK_SWC_DCPWW;
		wetuwn twue;
	case CWOCK_SOUWCE_ID_EXTEWNAW:
		*wef_cwk_swc_id = ENCODEW_WEFCWK_SWC_EXTCWK;
		wetuwn twue;
	case CWOCK_SOUWCE_ID_UNDEFINED:
		*wef_cwk_swc_id = ENCODEW_WEFCWK_SWC_INVAWID;
		wetuwn twue;
	defauwt:
		/* Unsuppowted cwock souwce id */
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
}

uint8_t daw_cmd_tabwe_hewpew_encodew_id_to_atom(
	enum encodew_id id)
{
	switch (id) {
	case ENCODEW_ID_INTEWNAW_WVDS:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_WVDS;
	case ENCODEW_ID_INTEWNAW_TMDS1:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_TMDS1;
	case ENCODEW_ID_INTEWNAW_TMDS2:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_TMDS2;
	case ENCODEW_ID_INTEWNAW_DAC1:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_DAC1;
	case ENCODEW_ID_INTEWNAW_DAC2:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_DAC2;
	case ENCODEW_ID_INTEWNAW_WVTM1:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_WVTM1;
	case ENCODEW_ID_INTEWNAW_HDMI:
		wetuwn ENCODEW_OBJECT_ID_HDMI_INTEWNAW;
	case ENCODEW_ID_EXTEWNAW_TWAVIS:
		wetuwn ENCODEW_OBJECT_ID_TWAVIS;
	case ENCODEW_ID_EXTEWNAW_NUTMEG:
		wetuwn ENCODEW_OBJECT_ID_NUTMEG;
	case ENCODEW_ID_INTEWNAW_KWDSCP_TMDS1:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_TMDS1;
	case ENCODEW_ID_INTEWNAW_KWDSCP_DAC1:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC1;
	case ENCODEW_ID_INTEWNAW_KWDSCP_DAC2:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_DAC2;
	case ENCODEW_ID_EXTEWNAW_MVPU_FPGA:
		wetuwn ENCODEW_OBJECT_ID_MVPU_FPGA;
	case ENCODEW_ID_INTEWNAW_DDI:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_DDI;
	case ENCODEW_ID_INTEWNAW_UNIPHY:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY;
	case ENCODEW_ID_INTEWNAW_KWDSCP_WVTMA:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_KWDSCP_WVTMA;
	case ENCODEW_ID_INTEWNAW_UNIPHY1:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY1;
	case ENCODEW_ID_INTEWNAW_UNIPHY2:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY2;
	case ENCODEW_ID_INTEWNAW_UNIPHY3:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_UNIPHY3;
	case ENCODEW_ID_INTEWNAW_WIWEWESS:
		wetuwn ENCODEW_OBJECT_ID_INTEWNAW_VCE;
	case ENCODEW_ID_UNKNOWN:
		wetuwn ENCODEW_OBJECT_ID_NONE;
	defauwt:
		/* Invawid encodew id */
		BWEAK_TO_DEBUGGEW();
		wetuwn ENCODEW_OBJECT_ID_NONE;
	}
}
