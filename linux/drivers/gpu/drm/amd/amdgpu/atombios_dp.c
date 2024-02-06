/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude <dwm/amdgpu_dwm.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>

#incwude "amdgpu.h"

#incwude "atom.h"
#incwude "atom-bits.h"
#incwude "atombios_encodews.h"
#incwude "atombios_dp.h"
#incwude "amdgpu_connectows.h"
#incwude "amdgpu_atombios.h"

/* move these to dwm_dp_hewpew.c/h */
#define DP_WINK_CONFIGUWATION_SIZE 9
#define DP_DPCD_SIZE DP_WECEIVEW_CAP_SIZE

static chaw *vowtage_names[] = {
	"0.4V", "0.6V", "0.8V", "1.2V"
};
static chaw *pwe_emph_names[] = {
	"0dB", "3.5dB", "6dB", "9.5dB"
};

/***** amdgpu AUX functions *****/

union aux_channew_twansaction {
	PWOCESS_AUX_CHANNEW_TWANSACTION_PS_AWWOCATION v1;
	PWOCESS_AUX_CHANNEW_TWANSACTION_PAWAMETEWS_V2 v2;
};

static int amdgpu_atombios_dp_pwocess_aux_ch(stwuct amdgpu_i2c_chan *chan,
				      u8 *send, int send_bytes,
				      u8 *wecv, int wecv_size,
				      u8 deway, u8 *ack)
{
	stwuct dwm_device *dev = chan->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	union aux_channew_twansaction awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, PwocessAuxChannewTwansaction);
	unsigned chaw *base;
	int wecv_bytes;
	int w = 0;

	memset(&awgs, 0, sizeof(awgs));

	mutex_wock(&chan->mutex);

	base = (unsigned chaw *)(adev->mode_info.atom_context->scwatch + 1);

	amdgpu_atombios_copy_swap(base, send, send_bytes, twue);

	awgs.v2.wpAuxWequest = cpu_to_we16((u16)(0 + 4));
	awgs.v2.wpDataOut = cpu_to_we16((u16)(16 + 4));
	awgs.v2.ucDataOutWen = 0;
	awgs.v2.ucChannewID = chan->wec.i2c_id;
	awgs.v2.ucDeway = deway / 10;
	awgs.v2.ucHPD_ID = chan->wec.hpd;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

	*ack = awgs.v2.ucWepwyStatus;

	/* timeout */
	if (awgs.v2.ucWepwyStatus == 1) {
		w = -ETIMEDOUT;
		goto done;
	}

	/* fwags not zewo */
	if (awgs.v2.ucWepwyStatus == 2) {
		DWM_DEBUG_KMS("dp_aux_ch fwags not zewo\n");
		w = -EIO;
		goto done;
	}

	/* ewwow */
	if (awgs.v2.ucWepwyStatus == 3) {
		DWM_DEBUG_KMS("dp_aux_ch ewwow\n");
		w = -EIO;
		goto done;
	}

	wecv_bytes = awgs.v1.ucDataOutWen;
	if (wecv_bytes > wecv_size)
		wecv_bytes = wecv_size;

	if (wecv && wecv_size)
		amdgpu_atombios_copy_swap(wecv, base + 16, wecv_bytes, fawse);

	w = wecv_bytes;
done:
	mutex_unwock(&chan->mutex);

	wetuwn w;
}

#define BAWE_ADDWESS_SIZE 3
#define HEADEW_SIZE (BAWE_ADDWESS_SIZE + 1)

static ssize_t
amdgpu_atombios_dp_aux_twansfew(stwuct dwm_dp_aux *aux, stwuct dwm_dp_aux_msg *msg)
{
	stwuct amdgpu_i2c_chan *chan =
		containew_of(aux, stwuct amdgpu_i2c_chan, aux);
	int wet;
	u8 tx_buf[20];
	size_t tx_size;
	u8 ack, deway = 0;

	if (WAWN_ON(msg->size > 16))
		wetuwn -E2BIG;

	tx_buf[0] = msg->addwess & 0xff;
	tx_buf[1] = msg->addwess >> 8;
	tx_buf[2] = (msg->wequest << 4) |
		((msg->addwess >> 16) & 0xf);
	tx_buf[3] = msg->size ? (msg->size - 1) : 0;

	switch (msg->wequest & ~DP_AUX_I2C_MOT) {
	case DP_AUX_NATIVE_WWITE:
	case DP_AUX_I2C_WWITE:
		/* tx_size needs to be 4 even fow bawe addwess packets since the atom
		 * tabwe needs the info in tx_buf[3].
		 */
		tx_size = HEADEW_SIZE + msg->size;
		if (msg->size == 0)
			tx_buf[3] |= BAWE_ADDWESS_SIZE << 4;
		ewse
			tx_buf[3] |= tx_size << 4;
		memcpy(tx_buf + HEADEW_SIZE, msg->buffew, msg->size);
		wet = amdgpu_atombios_dp_pwocess_aux_ch(chan,
						 tx_buf, tx_size, NUWW, 0, deway, &ack);
		if (wet >= 0)
			/* Wetuwn paywoad size. */
			wet = msg->size;
		bweak;
	case DP_AUX_NATIVE_WEAD:
	case DP_AUX_I2C_WEAD:
		/* tx_size needs to be 4 even fow bawe addwess packets since the atom
		 * tabwe needs the info in tx_buf[3].
		 */
		tx_size = HEADEW_SIZE;
		if (msg->size == 0)
			tx_buf[3] |= BAWE_ADDWESS_SIZE << 4;
		ewse
			tx_buf[3] |= tx_size << 4;
		wet = amdgpu_atombios_dp_pwocess_aux_ch(chan,
						 tx_buf, tx_size, msg->buffew, msg->size, deway, &ack);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet >= 0)
		msg->wepwy = ack >> 4;

	wetuwn wet;
}

void amdgpu_atombios_dp_aux_init(stwuct amdgpu_connectow *amdgpu_connectow)
{
	amdgpu_connectow->ddc_bus->wec.hpd = amdgpu_connectow->hpd.hpd;
	amdgpu_connectow->ddc_bus->aux.twansfew = amdgpu_atombios_dp_aux_twansfew;
	amdgpu_connectow->ddc_bus->aux.dwm_dev = amdgpu_connectow->base.dev;

	dwm_dp_aux_init(&amdgpu_connectow->ddc_bus->aux);
	amdgpu_connectow->ddc_bus->has_aux = twue;
}

/***** genewaw DP utiwity functions *****/

#define DP_VOWTAGE_MAX         DP_TWAIN_VOWTAGE_SWING_WEVEW_3
#define DP_PWE_EMPHASIS_MAX    DP_TWAIN_PWE_EMPH_WEVEW_3

static void amdgpu_atombios_dp_get_adjust_twain(const u8 wink_status[DP_WINK_STATUS_SIZE],
						int wane_count,
						u8 twain_set[4])
{
	u8 v = 0;
	u8 p = 0;
	int wane;

	fow (wane = 0; wane < wane_count; wane++) {
		u8 this_v = dwm_dp_get_adjust_wequest_vowtage(wink_status, wane);
		u8 this_p = dwm_dp_get_adjust_wequest_pwe_emphasis(wink_status, wane);

		DWM_DEBUG_KMS("wequested signaw pawametews: wane %d vowtage %s pwe_emph %s\n",
			  wane,
			  vowtage_names[this_v >> DP_TWAIN_VOWTAGE_SWING_SHIFT],
			  pwe_emph_names[this_p >> DP_TWAIN_PWE_EMPHASIS_SHIFT]);

		if (this_v > v)
			v = this_v;
		if (this_p > p)
			p = this_p;
	}

	if (v >= DP_VOWTAGE_MAX)
		v |= DP_TWAIN_MAX_SWING_WEACHED;

	if (p >= DP_PWE_EMPHASIS_MAX)
		p |= DP_TWAIN_MAX_PWE_EMPHASIS_WEACHED;

	DWM_DEBUG_KMS("using signaw pawametews: vowtage %s pwe_emph %s\n",
		  vowtage_names[(v & DP_TWAIN_VOWTAGE_SWING_MASK) >> DP_TWAIN_VOWTAGE_SWING_SHIFT],
		  pwe_emph_names[(p & DP_TWAIN_PWE_EMPHASIS_MASK) >> DP_TWAIN_PWE_EMPHASIS_SHIFT]);

	fow (wane = 0; wane < 4; wane++)
		twain_set[wane] = v | p;
}

/* convewt bits pew cowow to bits pew pixew */
/* get bpc fwom the EDID */
static unsigned amdgpu_atombios_dp_convewt_bpc_to_bpp(int bpc)
{
	if (bpc == 0)
		wetuwn 24;
	ewse
		wetuwn bpc * 3;
}

/***** amdgpu specific DP functions *****/

static int amdgpu_atombios_dp_get_dp_wink_config(stwuct dwm_connectow *connectow,
						 const u8 dpcd[DP_DPCD_SIZE],
						 unsigned pix_cwock,
						 unsigned *dp_wanes, unsigned *dp_wate)
{
	unsigned bpp =
		amdgpu_atombios_dp_convewt_bpc_to_bpp(amdgpu_connectow_get_monitow_bpc(connectow));
	static const unsigned wink_wates[3] = { 162000, 270000, 540000 };
	unsigned max_wink_wate = dwm_dp_max_wink_wate(dpcd);
	unsigned max_wane_num = dwm_dp_max_wane_count(dpcd);
	unsigned wane_num, i, max_pix_cwock;

	if (amdgpu_connectow_encodew_get_dp_bwidge_encodew_id(connectow) ==
	    ENCODEW_OBJECT_ID_NUTMEG) {
		fow (wane_num = 1; wane_num <= max_wane_num; wane_num <<= 1) {
			max_pix_cwock = (wane_num * 270000 * 8) / bpp;
			if (max_pix_cwock >= pix_cwock) {
				*dp_wanes = wane_num;
				*dp_wate = 270000;
				wetuwn 0;
			}
		}
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(wink_wates) && wink_wates[i] <= max_wink_wate; i++) {
			fow (wane_num = 1; wane_num <= max_wane_num; wane_num <<= 1) {
				max_pix_cwock = (wane_num * wink_wates[i] * 8) / bpp;
				if (max_pix_cwock >= pix_cwock) {
					*dp_wanes = wane_num;
					*dp_wate = wink_wates[i];
					wetuwn 0;
				}
			}
		}
	}

	wetuwn -EINVAW;
}

static u8 amdgpu_atombios_dp_encodew_sewvice(stwuct amdgpu_device *adev,
				      int action, int dp_cwock,
				      u8 ucconfig, u8 wane_num)
{
	DP_ENCODEW_SEWVICE_PAWAMETEWS awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, DPEncodewSewvice);

	memset(&awgs, 0, sizeof(awgs));
	awgs.ucWinkCwock = dp_cwock / 10;
	awgs.ucConfig = ucconfig;
	awgs.ucAction = action;
	awgs.ucWaneNum = wane_num;
	awgs.ucStatus = 0;

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
	wetuwn awgs.ucStatus;
}

u8 amdgpu_atombios_dp_get_sinktype(stwuct amdgpu_connectow *amdgpu_connectow)
{
	stwuct dwm_device *dev = amdgpu_connectow->base.dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);

	wetuwn amdgpu_atombios_dp_encodew_sewvice(adev, ATOM_DP_ACTION_GET_SINK_TYPE, 0,
					   amdgpu_connectow->ddc_bus->wec.i2c_id, 0);
}

static void amdgpu_atombios_dp_pwobe_oui(stwuct amdgpu_connectow *amdgpu_connectow)
{
	stwuct amdgpu_connectow_atom_dig *dig_connectow = amdgpu_connectow->con_pwiv;
	u8 buf[3];

	if (!(dig_connectow->dpcd[DP_DOWN_STWEAM_POWT_COUNT] & DP_OUI_SUPPOWT))
		wetuwn;

	if (dwm_dp_dpcd_wead(&amdgpu_connectow->ddc_bus->aux, DP_SINK_OUI, buf, 3) == 3)
		DWM_DEBUG_KMS("Sink OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);

	if (dwm_dp_dpcd_wead(&amdgpu_connectow->ddc_bus->aux, DP_BWANCH_OUI, buf, 3) == 3)
		DWM_DEBUG_KMS("Bwanch OUI: %02hx%02hx%02hx\n",
			      buf[0], buf[1], buf[2]);
}

static void amdgpu_atombios_dp_ds_powts(stwuct amdgpu_connectow *amdgpu_connectow)
{
	stwuct amdgpu_connectow_atom_dig *dig_connectow = amdgpu_connectow->con_pwiv;
	int wet;

	if (dig_connectow->dpcd[DP_DPCD_WEV] > 0x10) {
		wet = dwm_dp_dpcd_wead(&amdgpu_connectow->ddc_bus->aux,
				       DP_DOWNSTWEAM_POWT_0,
				       dig_connectow->downstweam_powts,
				       DP_MAX_DOWNSTWEAM_POWTS);
		if (wet)
			memset(dig_connectow->downstweam_powts, 0,
			       DP_MAX_DOWNSTWEAM_POWTS);
	}
}

int amdgpu_atombios_dp_get_dpcd(stwuct amdgpu_connectow *amdgpu_connectow)
{
	stwuct amdgpu_connectow_atom_dig *dig_connectow = amdgpu_connectow->con_pwiv;
	u8 msg[DP_DPCD_SIZE];
	int wet;

	wet = dwm_dp_dpcd_wead(&amdgpu_connectow->ddc_bus->aux, DP_DPCD_WEV,
			       msg, DP_DPCD_SIZE);
	if (wet == DP_DPCD_SIZE) {
		memcpy(dig_connectow->dpcd, msg, DP_DPCD_SIZE);

		DWM_DEBUG_KMS("DPCD: %*ph\n", (int)sizeof(dig_connectow->dpcd),
			      dig_connectow->dpcd);

		amdgpu_atombios_dp_pwobe_oui(amdgpu_connectow);
		amdgpu_atombios_dp_ds_powts(amdgpu_connectow);
		wetuwn 0;
	}

	dig_connectow->dpcd[0] = 0;
	wetuwn -EINVAW;
}

int amdgpu_atombios_dp_get_panew_mode(stwuct dwm_encodew *encodew,
			       stwuct dwm_connectow *connectow)
{
	stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);
	int panew_mode = DP_PANEW_MODE_EXTEWNAW_DP_MODE;
	u16 dp_bwidge = amdgpu_connectow_encodew_get_dp_bwidge_encodew_id(connectow);
	u8 tmp;

	if (!amdgpu_connectow->con_pwiv)
		wetuwn panew_mode;

	if (dp_bwidge != ENCODEW_OBJECT_ID_NONE) {
		/* DP bwidge chips */
		if (dwm_dp_dpcd_weadb(&amdgpu_connectow->ddc_bus->aux,
				      DP_EDP_CONFIGUWATION_CAP, &tmp) == 1) {
			if (tmp & 1)
				panew_mode = DP_PANEW_MODE_INTEWNAW_DP2_MODE;
			ewse if ((dp_bwidge == ENCODEW_OBJECT_ID_NUTMEG) ||
				 (dp_bwidge == ENCODEW_OBJECT_ID_TWAVIS))
				panew_mode = DP_PANEW_MODE_INTEWNAW_DP1_MODE;
			ewse
				panew_mode = DP_PANEW_MODE_EXTEWNAW_DP_MODE;
		}
	} ewse if (connectow->connectow_type == DWM_MODE_CONNECTOW_eDP) {
		/* eDP */
		if (dwm_dp_dpcd_weadb(&amdgpu_connectow->ddc_bus->aux,
				      DP_EDP_CONFIGUWATION_CAP, &tmp) == 1) {
			if (tmp & 1)
				panew_mode = DP_PANEW_MODE_INTEWNAW_DP2_MODE;
		}
	}

	wetuwn panew_mode;
}

void amdgpu_atombios_dp_set_wink_config(stwuct dwm_connectow *connectow,
				 const stwuct dwm_dispway_mode *mode)
{
	stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);
	stwuct amdgpu_connectow_atom_dig *dig_connectow;
	int wet;

	if (!amdgpu_connectow->con_pwiv)
		wetuwn;
	dig_connectow = amdgpu_connectow->con_pwiv;

	if ((dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_DISPWAYPOWT) ||
	    (dig_connectow->dp_sink_type == CONNECTOW_OBJECT_ID_eDP)) {
		wet = amdgpu_atombios_dp_get_dp_wink_config(connectow, dig_connectow->dpcd,
							    mode->cwock,
							    &dig_connectow->dp_wane_count,
							    &dig_connectow->dp_cwock);
		if (wet) {
			dig_connectow->dp_cwock = 0;
			dig_connectow->dp_wane_count = 0;
		}
	}
}

int amdgpu_atombios_dp_mode_vawid_hewpew(stwuct dwm_connectow *connectow,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);
	stwuct amdgpu_connectow_atom_dig *dig_connectow;
	unsigned dp_wanes, dp_cwock;
	int wet;

	if (!amdgpu_connectow->con_pwiv)
		wetuwn MODE_CWOCK_HIGH;
	dig_connectow = amdgpu_connectow->con_pwiv;

	wet = amdgpu_atombios_dp_get_dp_wink_config(connectow, dig_connectow->dpcd,
						    mode->cwock, &dp_wanes, &dp_cwock);
	if (wet)
		wetuwn MODE_CWOCK_HIGH;

	if ((dp_cwock == 540000) &&
	    (!amdgpu_connectow_is_dp12_capabwe(connectow)))
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

boow amdgpu_atombios_dp_needs_wink_twain(stwuct amdgpu_connectow *amdgpu_connectow)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	stwuct amdgpu_connectow_atom_dig *dig = amdgpu_connectow->con_pwiv;

	if (dwm_dp_dpcd_wead_wink_status(&amdgpu_connectow->ddc_bus->aux, wink_status)
	    <= 0)
		wetuwn fawse;
	if (dwm_dp_channew_eq_ok(wink_status, dig->dp_wane_count))
		wetuwn fawse;
	wetuwn twue;
}

void amdgpu_atombios_dp_set_wx_powew_state(stwuct dwm_connectow *connectow,
				    u8 powew_state)
{
	stwuct amdgpu_connectow *amdgpu_connectow = to_amdgpu_connectow(connectow);
	stwuct amdgpu_connectow_atom_dig *dig_connectow;

	if (!amdgpu_connectow->con_pwiv)
		wetuwn;

	dig_connectow = amdgpu_connectow->con_pwiv;

	/* powew up/down the sink */
	if (dig_connectow->dpcd[0] >= 0x11) {
		dwm_dp_dpcd_wwiteb(&amdgpu_connectow->ddc_bus->aux,
				   DP_SET_POWEW, powew_state);
		usweep_wange(1000, 2000);
	}
}

stwuct amdgpu_atombios_dp_wink_twain_info {
	stwuct amdgpu_device *adev;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	int dp_cwock;
	int dp_wane_count;
	boow tp3_suppowted;
	u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	u8 twain_set[4];
	u8 wink_status[DP_WINK_STATUS_SIZE];
	u8 twies;
	stwuct dwm_dp_aux *aux;
};

static void
amdgpu_atombios_dp_update_vs_emph(stwuct amdgpu_atombios_dp_wink_twain_info *dp_info)
{
	/* set the initiaw vs/emph on the souwce */
	amdgpu_atombios_encodew_setup_dig_twansmittew(dp_info->encodew,
					       ATOM_TWANSMITTEW_ACTION_SETUP_VSEMPH,
					       0, dp_info->twain_set[0]); /* sets aww wanes at once */

	/* set the vs/emph on the sink */
	dwm_dp_dpcd_wwite(dp_info->aux, DP_TWAINING_WANE0_SET,
			  dp_info->twain_set, dp_info->dp_wane_count);
}

static void
amdgpu_atombios_dp_set_tp(stwuct amdgpu_atombios_dp_wink_twain_info *dp_info, int tp)
{
	int wtp = 0;

	/* set twaining pattewn on the souwce */
	switch (tp) {
	case DP_TWAINING_PATTEWN_1:
		wtp = ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN1;
		bweak;
	case DP_TWAINING_PATTEWN_2:
		wtp = ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN2;
		bweak;
	case DP_TWAINING_PATTEWN_3:
		wtp = ATOM_ENCODEW_CMD_DP_WINK_TWAINING_PATTEWN3;
			bweak;
	}
	amdgpu_atombios_encodew_setup_dig_encodew(dp_info->encodew, wtp, 0);

	/* enabwe twaining pattewn on the sink */
	dwm_dp_dpcd_wwiteb(dp_info->aux, DP_TWAINING_PATTEWN_SET, tp);
}

static int
amdgpu_atombios_dp_wink_twain_init(stwuct amdgpu_atombios_dp_wink_twain_info *dp_info)
{
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(dp_info->encodew);
	stwuct amdgpu_encodew_atom_dig *dig = amdgpu_encodew->enc_pwiv;
	u8 tmp;

	/* powew up the sink */
	amdgpu_atombios_dp_set_wx_powew_state(dp_info->connectow, DP_SET_POWEW_D0);

	/* possibwy enabwe downspwead on the sink */
	if (dp_info->dpcd[3] & 0x1)
		dwm_dp_dpcd_wwiteb(dp_info->aux,
				   DP_DOWNSPWEAD_CTWW, DP_SPWEAD_AMP_0_5);
	ewse
		dwm_dp_dpcd_wwiteb(dp_info->aux,
				   DP_DOWNSPWEAD_CTWW, 0);

	if (dig->panew_mode == DP_PANEW_MODE_INTEWNAW_DP2_MODE)
		dwm_dp_dpcd_wwiteb(dp_info->aux, DP_EDP_CONFIGUWATION_SET, 1);

	/* set the wane count on the sink */
	tmp = dp_info->dp_wane_count;
	if (dwm_dp_enhanced_fwame_cap(dp_info->dpcd))
		tmp |= DP_WANE_COUNT_ENHANCED_FWAME_EN;
	dwm_dp_dpcd_wwiteb(dp_info->aux, DP_WANE_COUNT_SET, tmp);

	/* set the wink wate on the sink */
	tmp = dwm_dp_wink_wate_to_bw_code(dp_info->dp_cwock);
	dwm_dp_dpcd_wwiteb(dp_info->aux, DP_WINK_BW_SET, tmp);

	/* stawt twaining on the souwce */
	amdgpu_atombios_encodew_setup_dig_encodew(dp_info->encodew,
					   ATOM_ENCODEW_CMD_DP_WINK_TWAINING_STAWT, 0);

	/* disabwe the twaining pattewn on the sink */
	dwm_dp_dpcd_wwiteb(dp_info->aux,
			   DP_TWAINING_PATTEWN_SET,
			   DP_TWAINING_PATTEWN_DISABWE);

	wetuwn 0;
}

static int
amdgpu_atombios_dp_wink_twain_finish(stwuct amdgpu_atombios_dp_wink_twain_info *dp_info)
{
	udeway(400);

	/* disabwe the twaining pattewn on the sink */
	dwm_dp_dpcd_wwiteb(dp_info->aux,
			   DP_TWAINING_PATTEWN_SET,
			   DP_TWAINING_PATTEWN_DISABWE);

	/* disabwe the twaining pattewn on the souwce */
	amdgpu_atombios_encodew_setup_dig_encodew(dp_info->encodew,
					   ATOM_ENCODEW_CMD_DP_WINK_TWAINING_COMPWETE, 0);

	wetuwn 0;
}

static int
amdgpu_atombios_dp_wink_twain_cw(stwuct amdgpu_atombios_dp_wink_twain_info *dp_info)
{
	boow cwock_wecovewy;
	u8 vowtage;
	int i;

	amdgpu_atombios_dp_set_tp(dp_info, DP_TWAINING_PATTEWN_1);
	memset(dp_info->twain_set, 0, 4);
	amdgpu_atombios_dp_update_vs_emph(dp_info);

	udeway(400);

	/* cwock wecovewy woop */
	cwock_wecovewy = fawse;
	dp_info->twies = 0;
	vowtage = 0xff;
	whiwe (1) {
		dwm_dp_wink_twain_cwock_wecovewy_deway(dp_info->aux, dp_info->dpcd);

		if (dwm_dp_dpcd_wead_wink_status(dp_info->aux,
						 dp_info->wink_status) <= 0) {
			DWM_EWWOW("dispwaypowt wink status faiwed\n");
			bweak;
		}

		if (dwm_dp_cwock_wecovewy_ok(dp_info->wink_status, dp_info->dp_wane_count)) {
			cwock_wecovewy = twue;
			bweak;
		}

		fow (i = 0; i < dp_info->dp_wane_count; i++) {
			if ((dp_info->twain_set[i] & DP_TWAIN_MAX_SWING_WEACHED) == 0)
				bweak;
		}
		if (i == dp_info->dp_wane_count) {
			DWM_EWWOW("cwock wecovewy weached max vowtage\n");
			bweak;
		}

		if ((dp_info->twain_set[0] & DP_TWAIN_VOWTAGE_SWING_MASK) == vowtage) {
			++dp_info->twies;
			if (dp_info->twies == 5) {
				DWM_EWWOW("cwock wecovewy twied 5 times\n");
				bweak;
			}
		} ewse
			dp_info->twies = 0;

		vowtage = dp_info->twain_set[0] & DP_TWAIN_VOWTAGE_SWING_MASK;

		/* Compute new twain_set as wequested by sink */
		amdgpu_atombios_dp_get_adjust_twain(dp_info->wink_status, dp_info->dp_wane_count,
					     dp_info->twain_set);

		amdgpu_atombios_dp_update_vs_emph(dp_info);
	}
	if (!cwock_wecovewy) {
		DWM_EWWOW("cwock wecovewy faiwed\n");
		wetuwn -1;
	} ewse {
		DWM_DEBUG_KMS("cwock wecovewy at vowtage %d pwe-emphasis %d\n",
			  dp_info->twain_set[0] & DP_TWAIN_VOWTAGE_SWING_MASK,
			  (dp_info->twain_set[0] & DP_TWAIN_PWE_EMPHASIS_MASK) >>
			  DP_TWAIN_PWE_EMPHASIS_SHIFT);
		wetuwn 0;
	}
}

static int
amdgpu_atombios_dp_wink_twain_ce(stwuct amdgpu_atombios_dp_wink_twain_info *dp_info)
{
	boow channew_eq;

	if (dp_info->tp3_suppowted)
		amdgpu_atombios_dp_set_tp(dp_info, DP_TWAINING_PATTEWN_3);
	ewse
		amdgpu_atombios_dp_set_tp(dp_info, DP_TWAINING_PATTEWN_2);

	/* channew equawization woop */
	dp_info->twies = 0;
	channew_eq = fawse;
	whiwe (1) {
		dwm_dp_wink_twain_channew_eq_deway(dp_info->aux, dp_info->dpcd);

		if (dwm_dp_dpcd_wead_wink_status(dp_info->aux,
						 dp_info->wink_status) <= 0) {
			DWM_EWWOW("dispwaypowt wink status faiwed\n");
			bweak;
		}

		if (dwm_dp_channew_eq_ok(dp_info->wink_status, dp_info->dp_wane_count)) {
			channew_eq = twue;
			bweak;
		}

		/* Twy 5 times */
		if (dp_info->twies > 5) {
			DWM_EWWOW("channew eq faiwed: 5 twies\n");
			bweak;
		}

		/* Compute new twain_set as wequested by sink */
		amdgpu_atombios_dp_get_adjust_twain(dp_info->wink_status, dp_info->dp_wane_count,
					     dp_info->twain_set);

		amdgpu_atombios_dp_update_vs_emph(dp_info);
		dp_info->twies++;
	}

	if (!channew_eq) {
		DWM_EWWOW("channew eq faiwed\n");
		wetuwn -1;
	} ewse {
		DWM_DEBUG_KMS("channew eq at vowtage %d pwe-emphasis %d\n",
			  dp_info->twain_set[0] & DP_TWAIN_VOWTAGE_SWING_MASK,
			  (dp_info->twain_set[0] & DP_TWAIN_PWE_EMPHASIS_MASK)
			  >> DP_TWAIN_PWE_EMPHASIS_SHIFT);
		wetuwn 0;
	}
}

void amdgpu_atombios_dp_wink_twain(stwuct dwm_encodew *encodew,
			    stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = encodew->dev;
	stwuct amdgpu_device *adev = dwm_to_adev(dev);
	stwuct amdgpu_encodew *amdgpu_encodew = to_amdgpu_encodew(encodew);
	stwuct amdgpu_connectow *amdgpu_connectow;
	stwuct amdgpu_connectow_atom_dig *dig_connectow;
	stwuct amdgpu_atombios_dp_wink_twain_info dp_info;
	u8 tmp;

	if (!amdgpu_encodew->enc_pwiv)
		wetuwn;

	amdgpu_connectow = to_amdgpu_connectow(connectow);
	if (!amdgpu_connectow->con_pwiv)
		wetuwn;
	dig_connectow = amdgpu_connectow->con_pwiv;

	if ((dig_connectow->dp_sink_type != CONNECTOW_OBJECT_ID_DISPWAYPOWT) &&
	    (dig_connectow->dp_sink_type != CONNECTOW_OBJECT_ID_eDP))
		wetuwn;

	if (dwm_dp_dpcd_weadb(&amdgpu_connectow->ddc_bus->aux, DP_MAX_WANE_COUNT, &tmp)
	    == 1) {
		if (tmp & DP_TPS3_SUPPOWTED)
			dp_info.tp3_suppowted = twue;
		ewse
			dp_info.tp3_suppowted = fawse;
	} ewse {
		dp_info.tp3_suppowted = fawse;
	}

	memcpy(dp_info.dpcd, dig_connectow->dpcd, DP_WECEIVEW_CAP_SIZE);
	dp_info.adev = adev;
	dp_info.encodew = encodew;
	dp_info.connectow = connectow;
	dp_info.dp_wane_count = dig_connectow->dp_wane_count;
	dp_info.dp_cwock = dig_connectow->dp_cwock;
	dp_info.aux = &amdgpu_connectow->ddc_bus->aux;

	if (amdgpu_atombios_dp_wink_twain_init(&dp_info))
		goto done;
	if (amdgpu_atombios_dp_wink_twain_cw(&dp_info))
		goto done;
	if (amdgpu_atombios_dp_wink_twain_ce(&dp_info))
		goto done;
done:
	if (amdgpu_atombios_dp_wink_twain_finish(&dp_info))
		wetuwn;
}
