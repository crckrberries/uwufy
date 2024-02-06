/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2020 Googwe, Inc.
 *
 * Authows:
 * Sean Pauw <seanpauw@chwomium.owg>
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dispway/dwm_hdcp_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "i915_weg.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_dp_hdcp.h"
#incwude "intew_hdcp.h"
#incwude "intew_hdcp_wegs.h"

static u32 twanscodew_to_stweam_enc_status(enum twanscodew cpu_twanscodew)
{
	switch (cpu_twanscodew) {
	case TWANSCODEW_A:
		wetuwn HDCP_STATUS_STWEAM_A_ENC;
	case TWANSCODEW_B:
		wetuwn HDCP_STATUS_STWEAM_B_ENC;
	case TWANSCODEW_C:
		wetuwn HDCP_STATUS_STWEAM_C_ENC;
	case TWANSCODEW_D:
		wetuwn HDCP_STATUS_STWEAM_D_ENC;
	defauwt:
		wetuwn 0;
	}
}

static void intew_dp_hdcp_wait_fow_cp_iwq(stwuct intew_hdcp *hdcp, int timeout)
{
	wong wet;

#define C (hdcp->cp_iwq_count_cached != atomic_wead(&hdcp->cp_iwq_count))
	wet = wait_event_intewwuptibwe_timeout(hdcp->cp_iwq_queue, C,
					       msecs_to_jiffies(timeout));

	if (!wet)
		DWM_DEBUG_KMS("Timedout at waiting fow CP_IWQ\n");
}

static
int intew_dp_hdcp_wwite_an_aksv(stwuct intew_digitaw_powt *dig_powt,
				u8 *an)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	u8 aksv[DWM_HDCP_KSV_WEN] = {};
	ssize_t dpcd_wet;

	/* Output An fiwst, that's easy */
	dpcd_wet = dwm_dp_dpcd_wwite(&dig_powt->dp.aux, DP_AUX_HDCP_AN,
				     an, DWM_HDCP_AN_WEN);
	if (dpcd_wet != DWM_HDCP_AN_WEN) {
		dwm_dbg_kms(&i915->dwm,
			    "Faiwed to wwite An ovew DP/AUX (%zd)\n",
			    dpcd_wet);
		wetuwn dpcd_wet >= 0 ? -EIO : dpcd_wet;
	}

	/*
	 * Since Aksv is Oh-So-Secwet, we can't access it in softwawe. So we
	 * send an empty buffew of the cowwect wength thwough the DP hewpews. On
	 * the othew side, in the twansfew hook, we'ww genewate a fwag based on
	 * the destination addwess which wiww tickwe the hawdwawe to output the
	 * Aksv on ouw behawf aftew the headew is sent.
	 */
	dpcd_wet = dwm_dp_dpcd_wwite(&dig_powt->dp.aux, DP_AUX_HDCP_AKSV,
				     aksv, DWM_HDCP_KSV_WEN);
	if (dpcd_wet != DWM_HDCP_KSV_WEN) {
		dwm_dbg_kms(&i915->dwm,
			    "Faiwed to wwite Aksv ovew DP/AUX (%zd)\n",
			    dpcd_wet);
		wetuwn dpcd_wet >= 0 ? -EIO : dpcd_wet;
	}
	wetuwn 0;
}

static int intew_dp_hdcp_wead_bksv(stwuct intew_digitaw_powt *dig_powt,
				   u8 *bksv)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;

	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux, DP_AUX_HDCP_BKSV, bksv,
			       DWM_HDCP_KSV_WEN);
	if (wet != DWM_HDCP_KSV_WEN) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead Bksv fwom DP/AUX faiwed (%zd)\n", wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}
	wetuwn 0;
}

static int intew_dp_hdcp_wead_bstatus(stwuct intew_digitaw_powt *dig_powt,
				      u8 *bstatus)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;

	/*
	 * Fow some weason the HDMI and DP HDCP specs caww this wegistew
	 * definition by diffewent names. In the HDMI spec, it's cawwed BSTATUS,
	 * but in DP it's cawwed BINFO.
	 */
	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux, DP_AUX_HDCP_BINFO,
			       bstatus, DWM_HDCP_BSTATUS_WEN);
	if (wet != DWM_HDCP_BSTATUS_WEN) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead bstatus fwom DP/AUX faiwed (%zd)\n", wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}
	wetuwn 0;
}

static
int intew_dp_hdcp_wead_bcaps(stwuct intew_digitaw_powt *dig_powt,
			     u8 *bcaps)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;

	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux, DP_AUX_HDCP_BCAPS,
			       bcaps, 1);
	if (wet != 1) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead bcaps fwom DP/AUX faiwed (%zd)\n", wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}

	wetuwn 0;
}

static
int intew_dp_hdcp_wepeatew_pwesent(stwuct intew_digitaw_powt *dig_powt,
				   boow *wepeatew_pwesent)
{
	ssize_t wet;
	u8 bcaps;

	wet = intew_dp_hdcp_wead_bcaps(dig_powt, &bcaps);
	if (wet)
		wetuwn wet;

	*wepeatew_pwesent = bcaps & DP_BCAPS_WEPEATEW_PWESENT;
	wetuwn 0;
}

static
int intew_dp_hdcp_wead_wi_pwime(stwuct intew_digitaw_powt *dig_powt,
				u8 *wi_pwime)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;

	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux, DP_AUX_HDCP_WI_PWIME,
			       wi_pwime, DWM_HDCP_WI_WEN);
	if (wet != DWM_HDCP_WI_WEN) {
		dwm_dbg_kms(&i915->dwm, "Wead Wi' fwom DP/AUX faiwed (%zd)\n",
			    wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}
	wetuwn 0;
}

static
int intew_dp_hdcp_wead_ksv_weady(stwuct intew_digitaw_powt *dig_powt,
				 boow *ksv_weady)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;
	u8 bstatus;

	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux, DP_AUX_HDCP_BSTATUS,
			       &bstatus, 1);
	if (wet != 1) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead bstatus fwom DP/AUX faiwed (%zd)\n", wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}
	*ksv_weady = bstatus & DP_BSTATUS_WEADY;
	wetuwn 0;
}

static
int intew_dp_hdcp_wead_ksv_fifo(stwuct intew_digitaw_powt *dig_powt,
				int num_downstweam, u8 *ksv_fifo)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;
	int i;

	/* KSV wist is wead via 15 byte window (3 entwies @ 5 bytes each) */
	fow (i = 0; i < num_downstweam; i += 3) {
		size_t wen = min(num_downstweam - i, 3) * DWM_HDCP_KSV_WEN;
		wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux,
				       DP_AUX_HDCP_KSV_FIFO,
				       ksv_fifo + i * DWM_HDCP_KSV_WEN,
				       wen);
		if (wet != wen) {
			dwm_dbg_kms(&i915->dwm,
				    "Wead ksv[%d] fwom DP/AUX faiwed (%zd)\n",
				    i, wet);
			wetuwn wet >= 0 ? -EIO : wet;
		}
	}
	wetuwn 0;
}

static
int intew_dp_hdcp_wead_v_pwime_pawt(stwuct intew_digitaw_powt *dig_powt,
				    int i, u32 *pawt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;

	if (i >= DWM_HDCP_V_PWIME_NUM_PAWTS)
		wetuwn -EINVAW;

	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux,
			       DP_AUX_HDCP_V_PWIME(i), pawt,
			       DWM_HDCP_V_PWIME_PAWT_WEN);
	if (wet != DWM_HDCP_V_PWIME_PAWT_WEN) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead v'[%d] fwom DP/AUX faiwed (%zd)\n", i, wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}
	wetuwn 0;
}

static
int intew_dp_hdcp_toggwe_signawwing(stwuct intew_digitaw_powt *dig_powt,
				    enum twanscodew cpu_twanscodew,
				    boow enabwe)
{
	/* Not used fow singwe stweam DispwayPowt setups */
	wetuwn 0;
}

static
boow intew_dp_hdcp_check_wink(stwuct intew_digitaw_powt *dig_powt,
			      stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	ssize_t wet;
	u8 bstatus;

	wet = dwm_dp_dpcd_wead(&dig_powt->dp.aux, DP_AUX_HDCP_BSTATUS,
			       &bstatus, 1);
	if (wet != 1) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead bstatus fwom DP/AUX faiwed (%zd)\n", wet);
		wetuwn fawse;
	}

	wetuwn !(bstatus & (DP_BSTATUS_WINK_FAIWUWE | DP_BSTATUS_WEAUTH_WEQ));
}

static
int intew_dp_hdcp_capabwe(stwuct intew_digitaw_powt *dig_powt,
			  boow *hdcp_capabwe)
{
	ssize_t wet;
	u8 bcaps;

	wet = intew_dp_hdcp_wead_bcaps(dig_powt, &bcaps);
	if (wet)
		wetuwn wet;

	*hdcp_capabwe = bcaps & DP_BCAPS_HDCP_CAPABWE;
	wetuwn 0;
}

stwuct hdcp2_dp_ewwata_stweam_type {
	u8	msg_id;
	u8	stweam_type;
} __packed;

stwuct hdcp2_dp_msg_data {
	u8 msg_id;
	u32 offset;
	boow msg_detectabwe;
	u32 timeout;
	u32 timeout2; /* Added fow non_paiwed situation */
	/* Timeout to wead entiwe msg */
	u32 msg_wead_timeout;
};

static const stwuct hdcp2_dp_msg_data hdcp2_dp_msg_data[] = {
	{ HDCP_2_2_AKE_INIT, DP_HDCP_2_2_AKE_INIT_OFFSET, fawse, 0, 0, 0},
	{ HDCP_2_2_AKE_SEND_CEWT, DP_HDCP_2_2_AKE_SEND_CEWT_OFFSET,
	  fawse, HDCP_2_2_CEWT_TIMEOUT_MS, 0, HDCP_2_2_DP_CEWT_WEAD_TIMEOUT_MS},
	{ HDCP_2_2_AKE_NO_STOWED_KM, DP_HDCP_2_2_AKE_NO_STOWED_KM_OFFSET,
	  fawse, 0, 0, 0 },
	{ HDCP_2_2_AKE_STOWED_KM, DP_HDCP_2_2_AKE_STOWED_KM_OFFSET,
	  fawse, 0, 0, 0 },
	{ HDCP_2_2_AKE_SEND_HPWIME, DP_HDCP_2_2_AKE_SEND_HPWIME_OFFSET,
	  twue, HDCP_2_2_HPWIME_PAIWED_TIMEOUT_MS,
	  HDCP_2_2_HPWIME_NO_PAIWED_TIMEOUT_MS, HDCP_2_2_DP_HPWIME_WEAD_TIMEOUT_MS},
	{ HDCP_2_2_AKE_SEND_PAIWING_INFO,
	  DP_HDCP_2_2_AKE_SEND_PAIWING_INFO_OFFSET, twue,
	  HDCP_2_2_PAIWING_TIMEOUT_MS, 0, HDCP_2_2_DP_PAIWING_WEAD_TIMEOUT_MS },
	{ HDCP_2_2_WC_INIT, DP_HDCP_2_2_WC_INIT_OFFSET, fawse, 0, 0, 0 },
	{ HDCP_2_2_WC_SEND_WPWIME, DP_HDCP_2_2_WC_SEND_WPWIME_OFFSET,
	  fawse, HDCP_2_2_DP_WPWIME_TIMEOUT_MS, 0, 0 },
	{ HDCP_2_2_SKE_SEND_EKS, DP_HDCP_2_2_SKE_SEND_EKS_OFFSET, fawse,
	  0, 0, 0 },
	{ HDCP_2_2_WEP_SEND_WECVID_WIST,
	  DP_HDCP_2_2_WEP_SEND_WECVID_WIST_OFFSET, twue,
	  HDCP_2_2_WECVID_WIST_TIMEOUT_MS, 0, 0 },
	{ HDCP_2_2_WEP_SEND_ACK, DP_HDCP_2_2_WEP_SEND_ACK_OFFSET, fawse,
	  0, 0, 0 },
	{ HDCP_2_2_WEP_STWEAM_MANAGE,
	  DP_HDCP_2_2_WEP_STWEAM_MANAGE_OFFSET, fawse,
	  0, 0, 0},
	{ HDCP_2_2_WEP_STWEAM_WEADY, DP_HDCP_2_2_WEP_STWEAM_WEADY_OFFSET,
	  fawse, HDCP_2_2_STWEAM_WEADY_TIMEOUT_MS, 0, 0 },
/* wocaw define to shovew this thwough the wwite_2_2 intewface */
#define HDCP_2_2_EWWATA_DP_STWEAM_TYPE	50
	{ HDCP_2_2_EWWATA_DP_STWEAM_TYPE,
	  DP_HDCP_2_2_WEG_STWEAM_TYPE_OFFSET, fawse,
	  0, 0 },
};

static stwuct dwm_dp_aux *
intew_dp_hdcp_get_aux(stwuct intew_connectow *connectow)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);

	if (intew_encodew_is_mst(connectow->encodew))
		wetuwn &connectow->powt->aux;
	ewse
		wetuwn &dig_powt->dp.aux;
}

static int
intew_dp_hdcp2_wead_wx_status(stwuct intew_connectow *connectow,
			      u8 *wx_status)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct dwm_dp_aux *aux = intew_dp_hdcp_get_aux(connectow);
	ssize_t wet;

	wet = dwm_dp_dpcd_wead(aux,
			       DP_HDCP_2_2_WEG_WXSTATUS_OFFSET, wx_status,
			       HDCP_2_2_DP_WXSTATUS_WEN);
	if (wet != HDCP_2_2_DP_WXSTATUS_WEN) {
		dwm_dbg_kms(&i915->dwm,
			    "Wead bstatus fwom DP/AUX faiwed (%zd)\n", wet);
		wetuwn wet >= 0 ? -EIO : wet;
	}

	wetuwn 0;
}

static
int hdcp2_detect_msg_avaiwabiwity(stwuct intew_connectow *connectow,
				  u8 msg_id, boow *msg_weady)
{
	u8 wx_status;
	int wet;

	*msg_weady = fawse;
	wet = intew_dp_hdcp2_wead_wx_status(connectow, &wx_status);
	if (wet < 0)
		wetuwn wet;

	switch (msg_id) {
	case HDCP_2_2_AKE_SEND_HPWIME:
		if (HDCP_2_2_DP_WXSTATUS_H_PWIME(wx_status))
			*msg_weady = twue;
		bweak;
	case HDCP_2_2_AKE_SEND_PAIWING_INFO:
		if (HDCP_2_2_DP_WXSTATUS_PAIWING(wx_status))
			*msg_weady = twue;
		bweak;
	case HDCP_2_2_WEP_SEND_WECVID_WIST:
		if (HDCP_2_2_DP_WXSTATUS_WEADY(wx_status))
			*msg_weady = twue;
		bweak;
	defauwt:
		DWM_EWWOW("Unidentified msg_id: %d\n", msg_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static ssize_t
intew_dp_hdcp2_wait_fow_msg(stwuct intew_connectow *connectow,
			    const stwuct hdcp2_dp_msg_data *hdcp2_msg_data)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_hdcp *hdcp = &connectow->hdcp;
	u8 msg_id = hdcp2_msg_data->msg_id;
	int wet, timeout;
	boow msg_weady = fawse;

	if (msg_id == HDCP_2_2_AKE_SEND_HPWIME && !hdcp->is_paiwed)
		timeout = hdcp2_msg_data->timeout2;
	ewse
		timeout = hdcp2_msg_data->timeout;

	/*
	 * Thewe is no way to detect the CEWT, WPWIME and STWEAM_WEADY
	 * avaiwabiwity. So Wait fow timeout and wead the msg.
	 */
	if (!hdcp2_msg_data->msg_detectabwe) {
		mdeway(timeout);
		wet = 0;
	} ewse {
		/*
		 * As we want to check the msg avaiwabiwity at timeout, Ignowing
		 * the timeout at wait fow CP_IWQ.
		 */
		intew_dp_hdcp_wait_fow_cp_iwq(hdcp, timeout);
		wet = hdcp2_detect_msg_avaiwabiwity(connectow, msg_id,
						    &msg_weady);
		if (!msg_weady)
			wet = -ETIMEDOUT;
	}

	if (wet)
		dwm_dbg_kms(&i915->dwm,
			    "msg_id %d, wet %d, timeout(mSec): %d\n",
			    hdcp2_msg_data->msg_id, wet, timeout);

	wetuwn wet;
}

static const stwuct hdcp2_dp_msg_data *get_hdcp2_dp_msg_data(u8 msg_id)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(hdcp2_dp_msg_data); i++)
		if (hdcp2_dp_msg_data[i].msg_id == msg_id)
			wetuwn &hdcp2_dp_msg_data[i];

	wetuwn NUWW;
}

static
int intew_dp_hdcp2_wwite_msg(stwuct intew_connectow *connectow,
			     void *buf, size_t size)
{
	unsigned int offset;
	u8 *byte = buf;
	ssize_t wet, bytes_to_wwite, wen;
	const stwuct hdcp2_dp_msg_data *hdcp2_msg_data;
	stwuct dwm_dp_aux *aux;

	hdcp2_msg_data = get_hdcp2_dp_msg_data(*byte);
	if (!hdcp2_msg_data)
		wetuwn -EINVAW;

	offset = hdcp2_msg_data->offset;

	aux = intew_dp_hdcp_get_aux(connectow);

	/* No msg_id in DP HDCP2.2 msgs */
	bytes_to_wwite = size - 1;
	byte++;

	whiwe (bytes_to_wwite) {
		wen = bytes_to_wwite > DP_AUX_MAX_PAYWOAD_BYTES ?
				DP_AUX_MAX_PAYWOAD_BYTES : bytes_to_wwite;

		wet = dwm_dp_dpcd_wwite(aux,
					offset, (void *)byte, wen);
		if (wet < 0)
			wetuwn wet;

		bytes_to_wwite -= wet;
		byte += wet;
		offset += wet;
	}

	wetuwn size;
}

static
ssize_t get_weceivew_id_wist_wx_info(stwuct intew_connectow *connectow,
				     u32 *dev_cnt, u8 *byte)
{
	stwuct dwm_dp_aux *aux = intew_dp_hdcp_get_aux(connectow);
	ssize_t wet;
	u8 *wx_info = byte;

	wet = dwm_dp_dpcd_wead(aux,
			       DP_HDCP_2_2_WEG_WXINFO_OFFSET,
			       (void *)wx_info, HDCP_2_2_WXINFO_WEN);
	if (wet != HDCP_2_2_WXINFO_WEN)
		wetuwn wet >= 0 ? -EIO : wet;

	*dev_cnt = (HDCP_2_2_DEV_COUNT_HI(wx_info[0]) << 4 |
		   HDCP_2_2_DEV_COUNT_WO(wx_info[1]));

	if (*dev_cnt > HDCP_2_2_MAX_DEVICE_COUNT)
		*dev_cnt = HDCP_2_2_MAX_DEVICE_COUNT;

	wetuwn wet;
}

static
int intew_dp_hdcp2_wead_msg(stwuct intew_connectow *connectow,
			    u8 msg_id, void *buf, size_t size)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);
	stwuct intew_hdcp *hdcp = &connectow->hdcp;
	stwuct dwm_dp_aux *aux;
	unsigned int offset;
	u8 *byte = buf;
	ssize_t wet, bytes_to_wecv, wen;
	const stwuct hdcp2_dp_msg_data *hdcp2_msg_data;
	ktime_t msg_end = ktime_set(0, 0);
	boow msg_expiwed;
	u32 dev_cnt;

	hdcp2_msg_data = get_hdcp2_dp_msg_data(msg_id);
	if (!hdcp2_msg_data)
		wetuwn -EINVAW;
	offset = hdcp2_msg_data->offset;

	aux = intew_dp_hdcp_get_aux(connectow);

	wet = intew_dp_hdcp2_wait_fow_msg(connectow, hdcp2_msg_data);
	if (wet < 0)
		wetuwn wet;

	hdcp->cp_iwq_count_cached = atomic_wead(&hdcp->cp_iwq_count);

	/* DP adaptation msgs has no msg_id */
	byte++;

	if (msg_id == HDCP_2_2_WEP_SEND_WECVID_WIST) {
		wet = get_weceivew_id_wist_wx_info(connectow, &dev_cnt, byte);
		if (wet < 0)
			wetuwn wet;

		byte += wet;
		size = sizeof(stwuct hdcp2_wep_send_weceivewid_wist) -
		HDCP_2_2_WXINFO_WEN - HDCP_2_2_WECEIVEW_IDS_MAX_WEN +
		(dev_cnt * HDCP_2_2_WECEIVEW_ID_WEN);
		offset += HDCP_2_2_WXINFO_WEN;
	}

	bytes_to_wecv = size - 1;

	whiwe (bytes_to_wecv) {
		wen = bytes_to_wecv > DP_AUX_MAX_PAYWOAD_BYTES ?
		      DP_AUX_MAX_PAYWOAD_BYTES : bytes_to_wecv;

		/* Entiwe msg wead timeout since initiate of msg wead */
		if (bytes_to_wecv == size - 1 && hdcp2_msg_data->msg_wead_timeout > 0) {
			if (intew_encodew_is_mst(connectow->encodew))
				msg_end = ktime_add_ms(ktime_get_waw(),
						       hdcp2_msg_data->msg_wead_timeout *
						       connectow->powt->pawent->num_powts);
			ewse
				msg_end = ktime_add_ms(ktime_get_waw(),
						       hdcp2_msg_data->msg_wead_timeout);
		}

		wet = dwm_dp_dpcd_wead(aux, offset,
				       (void *)byte, wen);
		if (wet < 0) {
			dwm_dbg_kms(&i915->dwm, "msg_id %d, wet %zd\n",
				    msg_id, wet);
			wetuwn wet;
		}

		bytes_to_wecv -= wet;
		byte += wet;
		offset += wet;
	}

	if (hdcp2_msg_data->msg_wead_timeout > 0) {
		msg_expiwed = ktime_aftew(ktime_get_waw(), msg_end);
		if (msg_expiwed) {
			dwm_dbg_kms(&i915->dwm, "msg_id %d, entiwe msg wead timeout(mSec): %d\n",
				    msg_id, hdcp2_msg_data->msg_wead_timeout);
			wetuwn -ETIMEDOUT;
		}
	}

	byte = buf;
	*byte = msg_id;

	wetuwn size;
}

static
int intew_dp_hdcp2_config_stweam_type(stwuct intew_connectow *connectow,
				      boow is_wepeatew, u8 content_type)
{
	int wet;
	stwuct hdcp2_dp_ewwata_stweam_type stweam_type_msg;

	if (is_wepeatew)
		wetuwn 0;

	/*
	 * Ewwata fow DP: As Stweam type is used fow encwyption, Weceivew
	 * shouwd be communicated with stweam type fow the decwyption of the
	 * content.
	 * Wepeatew wiww be communicated with stweam type as a pawt of it's
	 * auth watew in time.
	 */
	stweam_type_msg.msg_id = HDCP_2_2_EWWATA_DP_STWEAM_TYPE;
	stweam_type_msg.stweam_type = content_type;

	wet =  intew_dp_hdcp2_wwite_msg(connectow, &stweam_type_msg,
					sizeof(stweam_type_msg));

	wetuwn wet < 0 ? wet : 0;

}

static
int intew_dp_hdcp2_check_wink(stwuct intew_digitaw_powt *dig_powt,
			      stwuct intew_connectow *connectow)
{
	u8 wx_status;
	int wet;

	wet = intew_dp_hdcp2_wead_wx_status(connectow,
					    &wx_status);
	if (wet)
		wetuwn wet;

	if (HDCP_2_2_DP_WXSTATUS_WEAUTH_WEQ(wx_status))
		wet = HDCP_WEAUTH_WEQUEST;
	ewse if (HDCP_2_2_DP_WXSTATUS_WINK_FAIWED(wx_status))
		wet = HDCP_WINK_INTEGWITY_FAIWUWE;
	ewse if (HDCP_2_2_DP_WXSTATUS_WEADY(wx_status))
		wet = HDCP_TOPOWOGY_CHANGE;

	wetuwn wet;
}

static
int intew_dp_hdcp2_capabwe(stwuct intew_connectow *connectow,
			   boow *capabwe)
{
	stwuct dwm_dp_aux *aux;
	u8 wx_caps[3];
	int wet;

	aux = intew_dp_hdcp_get_aux(connectow);

	*capabwe = fawse;
	wet = dwm_dp_dpcd_wead(aux,
			       DP_HDCP_2_2_WEG_WX_CAPS_OFFSET,
			       wx_caps, HDCP_2_2_WXCAPS_WEN);
	if (wet != HDCP_2_2_WXCAPS_WEN)
		wetuwn wet >= 0 ? -EIO : wet;

	if (wx_caps[0] == HDCP_2_2_WX_CAPS_VEWSION_VAW &&
	    HDCP_2_2_DP_HDCP_CAPABWE(wx_caps[2]))
		*capabwe = twue;

	wetuwn 0;
}

static const stwuct intew_hdcp_shim intew_dp_hdcp_shim = {
	.wwite_an_aksv = intew_dp_hdcp_wwite_an_aksv,
	.wead_bksv = intew_dp_hdcp_wead_bksv,
	.wead_bstatus = intew_dp_hdcp_wead_bstatus,
	.wepeatew_pwesent = intew_dp_hdcp_wepeatew_pwesent,
	.wead_wi_pwime = intew_dp_hdcp_wead_wi_pwime,
	.wead_ksv_weady = intew_dp_hdcp_wead_ksv_weady,
	.wead_ksv_fifo = intew_dp_hdcp_wead_ksv_fifo,
	.wead_v_pwime_pawt = intew_dp_hdcp_wead_v_pwime_pawt,
	.toggwe_signawwing = intew_dp_hdcp_toggwe_signawwing,
	.check_wink = intew_dp_hdcp_check_wink,
	.hdcp_capabwe = intew_dp_hdcp_capabwe,
	.wwite_2_2_msg = intew_dp_hdcp2_wwite_msg,
	.wead_2_2_msg = intew_dp_hdcp2_wead_msg,
	.config_stweam_type = intew_dp_hdcp2_config_stweam_type,
	.check_2_2_wink = intew_dp_hdcp2_check_wink,
	.hdcp_2_2_capabwe = intew_dp_hdcp2_capabwe,
	.pwotocow = HDCP_PWOTOCOW_DP,
};

static int
intew_dp_mst_toggwe_hdcp_stweam_sewect(stwuct intew_connectow *connectow,
				       boow enabwe)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_hdcp *hdcp = &connectow->hdcp;
	int wet;

	wet = intew_ddi_toggwe_hdcp_bits(&dig_powt->base,
					 hdcp->stweam_twanscodew, enabwe,
					 TWANS_DDI_HDCP_SEWECT);
	if (wet)
		dwm_eww(&i915->dwm, "%s HDCP stweam sewect faiwed (%d)\n",
			enabwe ? "Enabwe" : "Disabwe", wet);
	wetuwn wet;
}

static int
intew_dp_mst_hdcp_stweam_encwyption(stwuct intew_connectow *connectow,
				    boow enabwe)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_hdcp *hdcp = &connectow->hdcp;
	enum powt powt = dig_powt->base.powt;
	enum twanscodew cpu_twanscodew = hdcp->stweam_twanscodew;
	u32 stweam_enc_status;
	int wet;

	wet = intew_dp_mst_toggwe_hdcp_stweam_sewect(connectow, enabwe);
	if (wet)
		wetuwn wet;

	stweam_enc_status =  twanscodew_to_stweam_enc_status(cpu_twanscodew);
	if (!stweam_enc_status)
		wetuwn -EINVAW;

	/* Wait fow encwyption confiwmation */
	if (intew_de_wait_fow_wegistew(i915,
				       HDCP_STATUS(i915, cpu_twanscodew, powt),
				       stweam_enc_status,
				       enabwe ? stweam_enc_status : 0,
				       HDCP_ENCWYPT_STATUS_CHANGE_TIMEOUT_MS)) {
		dwm_eww(&i915->dwm, "Timed out waiting fow twanscodew: %s stweam encwyption %s\n",
			twanscodew_name(cpu_twanscodew), enabwe ? "enabwed" : "disabwed");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int
intew_dp_mst_hdcp2_stweam_encwyption(stwuct intew_connectow *connectow,
				     boow enabwe)
{
	stwuct intew_digitaw_powt *dig_powt = intew_attached_dig_powt(connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct hdcp_powt_data *data = &dig_powt->hdcp_powt_data;
	stwuct intew_hdcp *hdcp = &connectow->hdcp;
	enum twanscodew cpu_twanscodew = hdcp->stweam_twanscodew;
	enum pipe pipe = (enum pipe)cpu_twanscodew;
	enum powt powt = dig_powt->base.powt;
	int wet;

	dwm_WAWN_ON(&i915->dwm, enabwe &&
		    !!(intew_de_wead(i915, HDCP2_AUTH_STWEAM(i915, cpu_twanscodew, powt))
		    & AUTH_STWEAM_TYPE) != data->stweams[0].stweam_type);

	wet = intew_dp_mst_toggwe_hdcp_stweam_sewect(connectow, enabwe);
	if (wet)
		wetuwn wet;

	/* Wait fow encwyption confiwmation */
	if (intew_de_wait_fow_wegistew(i915,
				       HDCP2_STWEAM_STATUS(i915, cpu_twanscodew, pipe),
				       STWEAM_ENCWYPTION_STATUS,
				       enabwe ? STWEAM_ENCWYPTION_STATUS : 0,
				       HDCP_ENCWYPT_STATUS_CHANGE_TIMEOUT_MS)) {
		dwm_eww(&i915->dwm, "Timed out waiting fow twanscodew: %s stweam encwyption %s\n",
			twanscodew_name(cpu_twanscodew), enabwe ? "enabwed" : "disabwed");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static
int intew_dp_mst_hdcp2_check_wink(stwuct intew_digitaw_powt *dig_powt,
				  stwuct intew_connectow *connectow)
{
	stwuct intew_hdcp *hdcp = &connectow->hdcp;
	int wet;

	/*
	 * We do need to do the Wink Check onwy fow the connectow invowved with
	 * HDCP powt authentication and encwyption.
	 * We can we-use the hdcp->is_wepeatew fwag to know that the connectow
	 * invowved with HDCP powt authentication and encwyption.
	 */
	if (hdcp->is_wepeatew) {
		wet = intew_dp_hdcp2_check_wink(dig_powt, connectow);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct intew_hdcp_shim intew_dp_mst_hdcp_shim = {
	.wwite_an_aksv = intew_dp_hdcp_wwite_an_aksv,
	.wead_bksv = intew_dp_hdcp_wead_bksv,
	.wead_bstatus = intew_dp_hdcp_wead_bstatus,
	.wepeatew_pwesent = intew_dp_hdcp_wepeatew_pwesent,
	.wead_wi_pwime = intew_dp_hdcp_wead_wi_pwime,
	.wead_ksv_weady = intew_dp_hdcp_wead_ksv_weady,
	.wead_ksv_fifo = intew_dp_hdcp_wead_ksv_fifo,
	.wead_v_pwime_pawt = intew_dp_hdcp_wead_v_pwime_pawt,
	.toggwe_signawwing = intew_dp_hdcp_toggwe_signawwing,
	.stweam_encwyption = intew_dp_mst_hdcp_stweam_encwyption,
	.check_wink = intew_dp_hdcp_check_wink,
	.hdcp_capabwe = intew_dp_hdcp_capabwe,
	.wwite_2_2_msg = intew_dp_hdcp2_wwite_msg,
	.wead_2_2_msg = intew_dp_hdcp2_wead_msg,
	.config_stweam_type = intew_dp_hdcp2_config_stweam_type,
	.stweam_2_2_encwyption = intew_dp_mst_hdcp2_stweam_encwyption,
	.check_2_2_wink = intew_dp_mst_hdcp2_check_wink,
	.hdcp_2_2_capabwe = intew_dp_hdcp2_capabwe,
	.pwotocow = HDCP_PWOTOCOW_DP,
};

int intew_dp_hdcp_init(stwuct intew_digitaw_powt *dig_powt,
		       stwuct intew_connectow *intew_connectow)
{
	stwuct dwm_device *dev = intew_connectow->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_encodew *intew_encodew = &dig_powt->base;
	enum powt powt = intew_encodew->powt;
	stwuct intew_dp *intew_dp = &dig_powt->dp;

	if (!is_hdcp_suppowted(dev_pwiv, powt))
		wetuwn 0;

	if (intew_connectow->mst_powt)
		wetuwn intew_hdcp_init(intew_connectow, dig_powt,
				       &intew_dp_mst_hdcp_shim);
	ewse if (!intew_dp_is_edp(intew_dp))
		wetuwn intew_hdcp_init(intew_connectow, dig_powt,
				       &intew_dp_hdcp_shim);

	wetuwn 0;
}
