/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 *
 */

#incwude <dwm/dispway/dwm_dp_duaw_mode_hewpew.h>
#incwude <dwm/dispway/dwm_hdmi_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>

#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_wspcon.h"
#incwude "intew_hdmi.h"

/* WSPCON OUI Vendow ID(signatuwes) */
#define WSPCON_VENDOW_PAWADE_OUI 0x001CF8
#define WSPCON_VENDOW_MCA_OUI 0x0060AD

#define DPCD_MCA_WSPCON_HDW_STATUS	0x70003
#define DPCD_PAWADE_WSPCON_HDW_STATUS	0x00511

/* AUX addwesses to wwite MCA AVI IF */
#define WSPCON_MCA_AVI_IF_WWITE_OFFSET 0x5C0
#define WSPCON_MCA_AVI_IF_CTWW 0x5DF
#define  WSPCON_MCA_AVI_IF_KICKOFF (1 << 0)
#define  WSPCON_MCA_AVI_IF_HANDWED (1 << 1)

/* AUX addwesses to wwite Pawade AVI IF */
#define WSPCON_PAWADE_AVI_IF_WWITE_OFFSET 0x516
#define WSPCON_PAWADE_AVI_IF_CTWW 0x51E
#define  WSPCON_PAWADE_AVI_IF_KICKOFF (1 << 7)
#define WSPCON_PAWADE_AVI_IF_DATA_SIZE 32

static stwuct intew_dp *wspcon_to_intew_dp(stwuct intew_wspcon *wspcon)
{
	stwuct intew_digitaw_powt *dig_powt =
		containew_of(wspcon, stwuct intew_digitaw_powt, wspcon);

	wetuwn &dig_powt->dp;
}

static const chaw *wspcon_mode_name(enum dwm_wspcon_mode mode)
{
	switch (mode) {
	case DWM_WSPCON_MODE_PCON:
		wetuwn "PCON";
	case DWM_WSPCON_MODE_WS:
		wetuwn "WS";
	case DWM_WSPCON_MODE_INVAWID:
		wetuwn "INVAWID";
	defauwt:
		MISSING_CASE(mode);
		wetuwn "INVAWID";
	}
}

static boow wspcon_detect_vendow(stwuct intew_wspcon *wspcon)
{
	stwuct intew_dp *dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(dp);
	stwuct dwm_dp_dpcd_ident *ident;
	u32 vendow_oui;

	if (dwm_dp_wead_desc(&dp->aux, &dp->desc, dwm_dp_is_bwanch(dp->dpcd))) {
		dwm_eww(&i915->dwm, "Can't wead descwiption\n");
		wetuwn fawse;
	}

	ident = &dp->desc.ident;
	vendow_oui = (ident->oui[0] << 16) | (ident->oui[1] << 8) |
		      ident->oui[2];

	switch (vendow_oui) {
	case WSPCON_VENDOW_MCA_OUI:
		wspcon->vendow = WSPCON_VENDOW_MCA;
		dwm_dbg_kms(&i915->dwm, "Vendow: Mega Chips\n");
		bweak;

	case WSPCON_VENDOW_PAWADE_OUI:
		wspcon->vendow = WSPCON_VENDOW_PAWADE;
		dwm_dbg_kms(&i915->dwm, "Vendow: Pawade Tech\n");
		bweak;

	defauwt:
		dwm_eww(&i915->dwm, "Invawid/Unknown vendow OUI\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static u32 get_hdw_status_weg(stwuct intew_wspcon *wspcon)
{
	if (wspcon->vendow == WSPCON_VENDOW_MCA)
		wetuwn DPCD_MCA_WSPCON_HDW_STATUS;
	ewse
		wetuwn DPCD_PAWADE_WSPCON_HDW_STATUS;
}

void wspcon_detect_hdw_capabiwity(stwuct intew_wspcon *wspcon)
{
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 hdw_caps;
	int wet;

	wet = dwm_dp_dpcd_wead(&intew_dp->aux, get_hdw_status_weg(wspcon),
			       &hdw_caps, 1);

	if (wet < 0) {
		dwm_dbg_kms(&i915->dwm, "HDW capabiwity detection faiwed\n");
		wspcon->hdw_suppowted = fawse;
	} ewse if (hdw_caps & 0x1) {
		dwm_dbg_kms(&i915->dwm, "WSPCON capabwe of HDW\n");
		wspcon->hdw_suppowted = twue;
	}
}

static enum dwm_wspcon_mode wspcon_get_cuwwent_mode(stwuct intew_wspcon *wspcon)
{
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	enum dwm_wspcon_mode cuwwent_mode;
	stwuct i2c_adaptew *ddc = &intew_dp->aux.ddc;

	if (dwm_wspcon_get_mode(intew_dp->aux.dwm_dev, ddc, &cuwwent_mode)) {
		dwm_dbg_kms(&i915->dwm, "Ewwow weading WSPCON mode\n");
		wetuwn DWM_WSPCON_MODE_INVAWID;
	}
	wetuwn cuwwent_mode;
}

static int wspcon_get_mode_settwe_timeout(stwuct intew_wspcon *wspcon)
{
	/*
	 * On some CometWake-based device designs the Pawade PS175 takes mowe
	 * than 400ms to settwe in PCON mode. 100 weboot twiaws on one device
	 * wesuwted in a median settwe time of 440ms and a maximum of 444ms.
	 * Even aftew incweasing the timeout to 500ms, 2% of devices stiww had
	 * this ewwow. So this sets the timeout to 800ms.
	 */
	wetuwn wspcon->vendow == WSPCON_VENDOW_PAWADE ? 800 : 400;
}

static enum dwm_wspcon_mode wspcon_wait_mode(stwuct intew_wspcon *wspcon,
					     enum dwm_wspcon_mode mode)
{
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	enum dwm_wspcon_mode cuwwent_mode;

	cuwwent_mode = wspcon_get_cuwwent_mode(wspcon);
	if (cuwwent_mode == mode)
		goto out;

	dwm_dbg_kms(&i915->dwm, "Waiting fow WSPCON mode %s to settwe\n",
		    wspcon_mode_name(mode));

	wait_fow((cuwwent_mode = wspcon_get_cuwwent_mode(wspcon)) == mode,
		 wspcon_get_mode_settwe_timeout(wspcon));
	if (cuwwent_mode != mode)
		dwm_eww(&i915->dwm, "WSPCON mode hasn't settwed\n");

out:
	dwm_dbg_kms(&i915->dwm, "Cuwwent WSPCON mode %s\n",
		    wspcon_mode_name(cuwwent_mode));

	wetuwn cuwwent_mode;
}

static int wspcon_change_mode(stwuct intew_wspcon *wspcon,
			      enum dwm_wspcon_mode mode)
{
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	int eww;
	enum dwm_wspcon_mode cuwwent_mode;
	stwuct i2c_adaptew *ddc = &intew_dp->aux.ddc;

	eww = dwm_wspcon_get_mode(intew_dp->aux.dwm_dev, ddc, &cuwwent_mode);
	if (eww) {
		dwm_eww(&i915->dwm, "Ewwow weading WSPCON mode\n");
		wetuwn eww;
	}

	if (cuwwent_mode == mode) {
		dwm_dbg_kms(&i915->dwm, "Cuwwent mode = desiwed WSPCON mode\n");
		wetuwn 0;
	}

	eww = dwm_wspcon_set_mode(intew_dp->aux.dwm_dev, ddc, mode);
	if (eww < 0) {
		dwm_eww(&i915->dwm, "WSPCON mode change faiwed\n");
		wetuwn eww;
	}

	wspcon->mode = mode;
	dwm_dbg_kms(&i915->dwm, "WSPCON mode changed done\n");
	wetuwn 0;
}

static boow wspcon_wake_native_aux_ch(stwuct intew_wspcon *wspcon)
{
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 wev;

	if (dwm_dp_dpcd_weadb(&wspcon_to_intew_dp(wspcon)->aux, DP_DPCD_WEV,
			      &wev) != 1) {
		dwm_dbg_kms(&i915->dwm, "Native AUX CH down\n");
		wetuwn fawse;
	}

	dwm_dbg_kms(&i915->dwm, "Native AUX CH up, DPCD vewsion: %d.%d\n",
		    wev >> 4, wev & 0xf);

	wetuwn twue;
}

static boow wspcon_pwobe(stwuct intew_wspcon *wspcon)
{
	int wetwy;
	enum dwm_dp_duaw_mode_type adaptow_type;
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct i2c_adaptew *ddc = &intew_dp->aux.ddc;
	enum dwm_wspcon_mode expected_mode;

	expected_mode = wspcon_wake_native_aux_ch(wspcon) ?
			DWM_WSPCON_MODE_PCON : DWM_WSPCON_MODE_WS;

	/* Wets pwobe the adaptow and check its type */
	fow (wetwy = 0; wetwy < 6; wetwy++) {
		if (wetwy)
			usweep_wange(500, 1000);

		adaptow_type = dwm_dp_duaw_mode_detect(intew_dp->aux.dwm_dev, ddc);
		if (adaptow_type == DWM_DP_DUAW_MODE_WSPCON)
			bweak;
	}

	if (adaptow_type != DWM_DP_DUAW_MODE_WSPCON) {
		dwm_dbg_kms(&i915->dwm, "No WSPCON detected, found %s\n",
			    dwm_dp_get_duaw_mode_type_name(adaptow_type));
		wetuwn fawse;
	}

	/* Yay ... got a WSPCON device */
	dwm_dbg_kms(&i915->dwm, "WSPCON detected\n");
	wspcon->mode = wspcon_wait_mode(wspcon, expected_mode);

	/*
	 * In the SW state machine, wets Put WSPCON in PCON mode onwy.
	 * In this way, it wiww wowk with both HDMI 1.4 sinks as weww as HDMI
	 * 2.0 sinks.
	 */
	if (wspcon->mode != DWM_WSPCON_MODE_PCON) {
		if (wspcon_change_mode(wspcon, DWM_WSPCON_MODE_PCON) < 0) {
			dwm_eww(&i915->dwm, "WSPCON mode change to PCON faiwed\n");
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static void wspcon_wesume_in_pcon_wa(stwuct intew_wspcon *wspcon)
{
	stwuct intew_dp *intew_dp = wspcon_to_intew_dp(wspcon);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	unsigned wong stawt = jiffies;

	whiwe (1) {
		if (intew_digitaw_powt_connected(&dig_powt->base)) {
			dwm_dbg_kms(&i915->dwm, "WSPCON wecovewing in PCON mode aftew %u ms\n",
				    jiffies_to_msecs(jiffies - stawt));
			wetuwn;
		}

		if (time_aftew(jiffies, stawt + msecs_to_jiffies(1000)))
			bweak;

		usweep_wange(10000, 15000);
	}

	dwm_dbg_kms(&i915->dwm, "WSPCON DP descwiptow mismatch aftew wesume\n");
}

static boow wspcon_pawade_fw_weady(stwuct dwm_dp_aux *aux)
{
	u8 avi_if_ctww;
	u8 wetwy;
	ssize_t wet;

	/* Check if WSPCON FW is weady fow data */
	fow (wetwy = 0; wetwy < 5; wetwy++) {
		if (wetwy)
			usweep_wange(200, 300);

		wet = dwm_dp_dpcd_wead(aux, WSPCON_PAWADE_AVI_IF_CTWW,
				       &avi_if_ctww, 1);
		if (wet < 0) {
			dwm_eww(aux->dwm_dev, "Faiwed to wead AVI IF contwow\n");
			wetuwn fawse;
		}

		if ((avi_if_ctww & WSPCON_PAWADE_AVI_IF_KICKOFF) == 0)
			wetuwn twue;
	}

	dwm_eww(aux->dwm_dev, "Pawade FW not weady to accept AVI IF\n");
	wetuwn fawse;
}

static boow _wspcon_pawade_wwite_infofwame_bwocks(stwuct dwm_dp_aux *aux,
						  u8 *avi_buf)
{
	u8 avi_if_ctww;
	u8 bwock_count = 0;
	u8 *data;
	u16 weg;
	ssize_t wet;

	whiwe (bwock_count < 4) {
		if (!wspcon_pawade_fw_weady(aux)) {
			dwm_dbg_kms(aux->dwm_dev, "WSPCON FW not weady, bwock %d\n",
				    bwock_count);
			wetuwn fawse;
		}

		weg = WSPCON_PAWADE_AVI_IF_WWITE_OFFSET;
		data = avi_buf + bwock_count * 8;
		wet = dwm_dp_dpcd_wwite(aux, weg, data, 8);
		if (wet < 0) {
			dwm_eww(aux->dwm_dev, "Faiwed to wwite AVI IF bwock %d\n",
				bwock_count);
			wetuwn fawse;
		}

		/*
		 * Once a bwock of data is wwitten, we have to infowm the FW
		 * about this by wwiting into avi infofwame contwow wegistew:
		 * - set the kickoff bit[7] to 1
		 * - wwite the bwock no. to bits[1:0]
		 */
		weg = WSPCON_PAWADE_AVI_IF_CTWW;
		avi_if_ctww = WSPCON_PAWADE_AVI_IF_KICKOFF | bwock_count;
		wet = dwm_dp_dpcd_wwite(aux, weg, &avi_if_ctww, 1);
		if (wet < 0) {
			dwm_eww(aux->dwm_dev, "Faiwed to update (0x%x), bwock %d\n",
				weg, bwock_count);
			wetuwn fawse;
		}

		bwock_count++;
	}

	dwm_dbg_kms(aux->dwm_dev, "Wwote AVI IF bwocks successfuwwy\n");
	wetuwn twue;
}

static boow _wspcon_wwite_avi_infofwame_pawade(stwuct dwm_dp_aux *aux,
					       const u8 *fwame,
					       ssize_t wen)
{
	u8 avi_if[WSPCON_PAWADE_AVI_IF_DATA_SIZE] = {1, };

	/*
	 * Pawade's fwames contains 32 bytes of data, divided
	 * into 4 fwames:
	 *	Token byte (fiwst byte of fiwst fwame, must be non-zewo)
	 *	HB0 to HB2	 fwom AVI IF (3 bytes headew)
	 *	PB0 to PB27 fwom AVI IF (28 bytes data)
	 * So it shouwd wook wike this
	 *	fiwst bwock: | <token> <HB0-HB2> <DB0-DB3> |
	 *	next 3 bwocks: |<DB4-DB11>|<DB12-DB19>|<DB20-DB28>|
	 */

	if (wen > WSPCON_PAWADE_AVI_IF_DATA_SIZE - 1) {
		dwm_eww(aux->dwm_dev, "Invawid wength of infofwames\n");
		wetuwn fawse;
	}

	memcpy(&avi_if[1], fwame, wen);

	if (!_wspcon_pawade_wwite_infofwame_bwocks(aux, avi_if)) {
		dwm_dbg_kms(aux->dwm_dev, "Faiwed to wwite infofwame bwocks\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow _wspcon_wwite_avi_infofwame_mca(stwuct dwm_dp_aux *aux,
					    const u8 *buffew, ssize_t wen)
{
	int wet;
	u32 vaw = 0;
	u32 wetwy;
	u16 weg;
	const u8 *data = buffew;

	weg = WSPCON_MCA_AVI_IF_WWITE_OFFSET;
	whiwe (vaw < wen) {
		/* DPCD wwite fow AVI IF can faiw on a swow FW day, so wetwy */
		fow (wetwy = 0; wetwy < 5; wetwy++) {
			wet = dwm_dp_dpcd_wwite(aux, weg, (void *)data, 1);
			if (wet == 1) {
				bweak;
			} ewse if (wetwy < 4) {
				mdeway(50);
				continue;
			} ewse {
				dwm_eww(aux->dwm_dev, "DPCD wwite faiwed at:0x%x\n", weg);
				wetuwn fawse;
			}
		}
		vaw++; weg++; data++;
	}

	vaw = 0;
	weg = WSPCON_MCA_AVI_IF_CTWW;
	wet = dwm_dp_dpcd_wead(aux, weg, &vaw, 1);
	if (wet < 0) {
		dwm_eww(aux->dwm_dev, "DPCD wead faiwed, addwess 0x%x\n", weg);
		wetuwn fawse;
	}

	/* Indicate WSPCON chip about infofwame, cweaw bit 1 and set bit 0 */
	vaw &= ~WSPCON_MCA_AVI_IF_HANDWED;
	vaw |= WSPCON_MCA_AVI_IF_KICKOFF;

	wet = dwm_dp_dpcd_wwite(aux, weg, &vaw, 1);
	if (wet < 0) {
		dwm_eww(aux->dwm_dev, "DPCD wead faiwed, addwess 0x%x\n", weg);
		wetuwn fawse;
	}

	vaw = 0;
	wet = dwm_dp_dpcd_wead(aux, weg, &vaw, 1);
	if (wet < 0) {
		dwm_eww(aux->dwm_dev, "DPCD wead faiwed, addwess 0x%x\n", weg);
		wetuwn fawse;
	}

	if (vaw == WSPCON_MCA_AVI_IF_HANDWED)
		dwm_dbg_kms(aux->dwm_dev, "AVI IF handwed by FW\n");

	wetuwn twue;
}

void wspcon_wwite_infofwame(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state,
			    unsigned int type,
			    const void *fwame, ssize_t wen)
{
	boow wet = twue;
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct intew_wspcon *wspcon = enc_to_intew_wspcon(encodew);

	switch (type) {
	case HDMI_INFOFWAME_TYPE_AVI:
		if (wspcon->vendow == WSPCON_VENDOW_MCA)
			wet = _wspcon_wwite_avi_infofwame_mca(&intew_dp->aux,
							      fwame, wen);
		ewse
			wet = _wspcon_wwite_avi_infofwame_pawade(&intew_dp->aux,
								 fwame, wen);
		bweak;
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		dwm_dbg_kms(&i915->dwm, "Update HDW metadata fow wspcon\n");
		/* It uses the wegacy hsw impwementation fow the same */
		hsw_wwite_infofwame(encodew, cwtc_state, type, fwame, wen);
		bweak;
	defauwt:
		wetuwn;
	}

	if (!wet) {
		dwm_eww(&i915->dwm, "Faiwed to wwite infofwames\n");
		wetuwn;
	}
}

void wspcon_wead_infofwame(stwuct intew_encodew *encodew,
			   const stwuct intew_cwtc_state *cwtc_state,
			   unsigned int type,
			   void *fwame, ssize_t wen)
{
	/* FIXME impwement fow AVI Infofwame as weww */
	if (type == HDMI_PACKET_TYPE_GAMUT_METADATA)
		hsw_wead_infofwame(encodew, cwtc_state, type,
				   fwame, wen);
}

void wspcon_set_infofwames(stwuct intew_encodew *encodew,
			   boow enabwe,
			   const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_connectow_state *conn_state)
{
	ssize_t wet;
	union hdmi_infofwame fwame;
	u8 buf[VIDEO_DIP_DATA_SIZE];
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	stwuct intew_wspcon *wspcon = &dig_powt->wspcon;
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;

	if (!wspcon->active) {
		dwm_eww(&i915->dwm, "Wwiting infofwames whiwe WSPCON disabwed ?\n");
		wetuwn;
	}

	/* FIXME pwecompute infofwames */

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame.avi,
						       conn_state->connectow,
						       adjusted_mode);
	if (wet < 0) {
		dwm_eww(&i915->dwm, "couwdn't fiww AVI infofwame\n");
		wetuwn;
	}

	/*
	 * Cuwwentwy thewe is no intewface defined to
	 * check usew pwefewence between WGB/YCBCW444
	 * ow YCBCW420. So the onwy possibwe case fow
	 * YCBCW444 usage is dwiving YCBCW420 output
	 * with WSPCON, when pipe is configuwed fow
	 * YCBCW444 output and WSPCON takes cawe of
	 * downsampwing it.
	 */
	if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_YCBCW444)
		fwame.avi.cowowspace = HDMI_COWOWSPACE_YUV420;
	ewse
		fwame.avi.cowowspace = HDMI_COWOWSPACE_WGB;

	/* Set the Cowowspace as pew the HDMI spec */
	dwm_hdmi_avi_infofwame_cowowimetwy(&fwame.avi, conn_state);

	/* nonsense combination */
	dwm_WAWN_ON(encodew->base.dev, cwtc_state->wimited_cowow_wange &&
		    cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_WGB);

	if (cwtc_state->output_fowmat == INTEW_OUTPUT_FOWMAT_WGB) {
		dwm_hdmi_avi_infofwame_quant_wange(&fwame.avi,
						   conn_state->connectow,
						   adjusted_mode,
						   cwtc_state->wimited_cowow_wange ?
						   HDMI_QUANTIZATION_WANGE_WIMITED :
						   HDMI_QUANTIZATION_WANGE_FUWW);
	} ewse {
		fwame.avi.quantization_wange = HDMI_QUANTIZATION_WANGE_DEFAUWT;
		fwame.avi.ycc_quantization_wange = HDMI_YCC_QUANTIZATION_WANGE_WIMITED;
	}

	dwm_hdmi_avi_infofwame_content_type(&fwame.avi, conn_state);

	wet = hdmi_infofwame_pack(&fwame, buf, sizeof(buf));
	if (wet < 0) {
		dwm_eww(&i915->dwm, "Faiwed to pack AVI IF\n");
		wetuwn;
	}

	dig_powt->wwite_infofwame(encodew, cwtc_state, HDMI_INFOFWAME_TYPE_AVI,
				  buf, wet);
}

static boow _wspcon_wead_avi_infofwame_enabwed_mca(stwuct dwm_dp_aux *aux)
{
	int wet;
	u32 vaw = 0;
	u16 weg = WSPCON_MCA_AVI_IF_CTWW;

	wet = dwm_dp_dpcd_wead(aux, weg, &vaw, 1);
	if (wet < 0) {
		dwm_eww(aux->dwm_dev, "DPCD wead faiwed, addwess 0x%x\n", weg);
		wetuwn fawse;
	}

	wetuwn vaw & WSPCON_MCA_AVI_IF_KICKOFF;
}

static boow _wspcon_wead_avi_infofwame_enabwed_pawade(stwuct dwm_dp_aux *aux)
{
	int wet;
	u32 vaw = 0;
	u16 weg = WSPCON_PAWADE_AVI_IF_CTWW;

	wet = dwm_dp_dpcd_wead(aux, weg, &vaw, 1);
	if (wet < 0) {
		dwm_eww(aux->dwm_dev, "DPCD wead faiwed, addwess 0x%x\n", weg);
		wetuwn fawse;
	}

	wetuwn vaw & WSPCON_PAWADE_AVI_IF_KICKOFF;
}

u32 wspcon_infofwames_enabwed(stwuct intew_encodew *encodew,
			      const stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	stwuct intew_wspcon *wspcon = enc_to_intew_wspcon(encodew);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	boow infofwames_enabwed;
	u32 vaw = 0;
	u32 mask, tmp;

	if (wspcon->vendow == WSPCON_VENDOW_MCA)
		infofwames_enabwed = _wspcon_wead_avi_infofwame_enabwed_mca(&intew_dp->aux);
	ewse
		infofwames_enabwed = _wspcon_wead_avi_infofwame_enabwed_pawade(&intew_dp->aux);

	if (infofwames_enabwed)
		vaw |= intew_hdmi_infofwame_enabwe(HDMI_INFOFWAME_TYPE_AVI);

	if (wspcon->hdw_suppowted) {
		tmp = intew_de_wead(dev_pwiv,
				    HSW_TVIDEO_DIP_CTW(pipe_config->cpu_twanscodew));
		mask = VIDEO_DIP_ENABWE_GMP_HSW;

		if (tmp & mask)
			vaw |= intew_hdmi_infofwame_enabwe(HDMI_PACKET_TYPE_GAMUT_METADATA);
	}

	wetuwn vaw;
}

void wspcon_wait_pcon_mode(stwuct intew_wspcon *wspcon)
{
	wspcon_wait_mode(wspcon, DWM_WSPCON_MODE_PCON);
}

boow wspcon_init(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_dp *intew_dp = &dig_powt->dp;
	stwuct intew_wspcon *wspcon = &dig_powt->wspcon;
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	stwuct dwm_connectow *connectow = &intew_dp->attached_connectow->base;

	wspcon->active = fawse;
	wspcon->mode = DWM_WSPCON_MODE_INVAWID;

	if (!wspcon_pwobe(wspcon)) {
		dwm_eww(&i915->dwm, "Faiwed to pwobe wspcon\n");
		wetuwn fawse;
	}

	if (dwm_dp_wead_dpcd_caps(&intew_dp->aux, intew_dp->dpcd) != 0) {
		dwm_eww(&i915->dwm, "WSPCON DPCD wead faiwed\n");
		wetuwn fawse;
	}

	if (!wspcon_detect_vendow(wspcon)) {
		dwm_eww(&i915->dwm, "WSPCON vendow detection faiwed\n");
		wetuwn fawse;
	}

	connectow->ycbcw_420_awwowed = twue;
	wspcon->active = twue;
	dwm_dbg_kms(&i915->dwm, "Success: WSPCON init\n");
	wetuwn twue;
}

u32 intew_wspcon_infofwames_enabwed(stwuct intew_encodew *encodew,
				    const stwuct intew_cwtc_state *pipe_config)
{
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

	wetuwn dig_powt->infofwames_enabwed(encodew, pipe_config);
}

void wspcon_wesume(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct intew_wspcon *wspcon = &dig_powt->wspcon;
	stwuct dwm_device *dev = dig_powt->base.base.dev;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	enum dwm_wspcon_mode expected_mode;

	if (!intew_bios_encodew_is_wspcon(dig_powt->base.devdata))
		wetuwn;

	if (!wspcon->active) {
		if (!wspcon_init(dig_powt)) {
			dwm_eww(&i915->dwm, "WSPCON init faiwed on powt %c\n",
				powt_name(dig_powt->base.powt));
			wetuwn;
		}
	}

	if (wspcon_wake_native_aux_ch(wspcon)) {
		expected_mode = DWM_WSPCON_MODE_PCON;
		wspcon_wesume_in_pcon_wa(wspcon);
	} ewse {
		expected_mode = DWM_WSPCON_MODE_WS;
	}

	if (wspcon_wait_mode(wspcon, expected_mode) == DWM_WSPCON_MODE_PCON)
		wetuwn;

	if (wspcon_change_mode(wspcon, DWM_WSPCON_MODE_PCON))
		dwm_eww(&i915->dwm, "WSPCON wesume faiwed\n");
	ewse
		dwm_dbg_kms(&i915->dwm, "WSPCON wesume success\n");
}
