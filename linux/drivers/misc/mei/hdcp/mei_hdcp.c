// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2019 Intew Cowpowation
 *
 * mei_hdcp.c: HDCP cwient dwivew fow mei bus
 *
 * Authow:
 * Wamawingam C <wamawingam.c@intew.com>
 */

/**
 * DOC: MEI_HDCP Cwient Dwivew
 *
 * The mei_hdcp dwivew acts as a twanswation wayew between HDCP 2.2
 * pwotocow  impwementew (I915) and ME FW by twanswating HDCP2.2
 * negotiation messages to ME FW command paywoads and vice vewsa.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mei.h>
#incwude <winux/mei_cw_bus.h>
#incwude <winux/component.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/i915_component.h>
#incwude <dwm/i915_hdcp_intewface.h>

#incwude "mei_hdcp.h"

/**
 * mei_hdcp_initiate_session() - Initiate a Wiwed HDCP2.2 Tx Session in ME FW
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @ake_data: AKE_Init msg output.
 *
 * Wetuwn:  0 on Success, <0 on Faiwuwe.
 */
static int
mei_hdcp_initiate_session(stwuct device *dev, stwuct hdcp_powt_data *data,
			  stwuct hdcp2_ake_init *ake_data)
{
	stwuct wiwed_cmd_initiate_hdcp2_session_in session_init_in = { { 0 } };
	stwuct wiwed_cmd_initiate_hdcp2_session_out
						session_init_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !ake_data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	session_init_in.headew.api_vewsion = HDCP_API_VEWSION;
	session_init_in.headew.command_id = WIWED_INITIATE_HDCP2_SESSION;
	session_init_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	session_init_in.headew.buffew_wen =
				WIWED_CMD_BUF_WEN_INITIATE_HDCP2_SESSION_IN;

	session_init_in.powt.integwated_powt_type = data->powt_type;
	session_init_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	session_init_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;
	session_init_in.pwotocow = data->pwotocow;

	byte = mei_cwdev_send(cwdev, (u8 *)&session_init_in,
			      sizeof(session_init_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&session_init_out,
			      sizeof(session_init_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (session_init_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X Faiwed. Status: 0x%X\n",
			WIWED_INITIATE_HDCP2_SESSION,
			session_init_out.headew.status);
		wetuwn -EIO;
	}

	ake_data->msg_id = HDCP_2_2_AKE_INIT;
	ake_data->tx_caps = session_init_out.tx_caps;
	memcpy(ake_data->w_tx, session_init_out.w_tx, HDCP_2_2_WTX_WEN);

	wetuwn 0;
}

/**
 * mei_hdcp_vewify_weceivew_cewt_pwepawe_km() - Vewify the Weceivew Cewtificate
 * AKE_Send_Cewt and pwepawe AKE_Stowed_Km/AKE_No_Stowed_Km
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @wx_cewt: AKE_Send_Cewt fow vewification
 * @km_stowed: Paiwing status fwag output
 * @ek_pub_km: AKE_Stowed_Km/AKE_No_Stowed_Km output msg
 * @msg_sz : size of AKE_XXXXX_Km output msg
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_vewify_weceivew_cewt_pwepawe_km(stwuct device *dev,
					 stwuct hdcp_powt_data *data,
					 stwuct hdcp2_ake_send_cewt *wx_cewt,
					 boow *km_stowed,
					 stwuct hdcp2_ake_no_stowed_km
								*ek_pub_km,
					 size_t *msg_sz)
{
	stwuct wiwed_cmd_vewify_weceivew_cewt_in vewify_wxcewt_in = { { 0 } };
	stwuct wiwed_cmd_vewify_weceivew_cewt_out vewify_wxcewt_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !wx_cewt || !km_stowed || !ek_pub_km || !msg_sz)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	vewify_wxcewt_in.headew.api_vewsion = HDCP_API_VEWSION;
	vewify_wxcewt_in.headew.command_id = WIWED_VEWIFY_WECEIVEW_CEWT;
	vewify_wxcewt_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	vewify_wxcewt_in.headew.buffew_wen =
				WIWED_CMD_BUF_WEN_VEWIFY_WECEIVEW_CEWT_IN;

	vewify_wxcewt_in.powt.integwated_powt_type = data->powt_type;
	vewify_wxcewt_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	vewify_wxcewt_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	vewify_wxcewt_in.cewt_wx = wx_cewt->cewt_wx;
	memcpy(vewify_wxcewt_in.w_wx, &wx_cewt->w_wx, HDCP_2_2_WWX_WEN);
	memcpy(vewify_wxcewt_in.wx_caps, wx_cewt->wx_caps, HDCP_2_2_WXCAPS_WEN);

	byte = mei_cwdev_send(cwdev, (u8 *)&vewify_wxcewt_in,
			      sizeof(vewify_wxcewt_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed: %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&vewify_wxcewt_out,
			      sizeof(vewify_wxcewt_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed: %zd\n", byte);
		wetuwn byte;
	}

	if (vewify_wxcewt_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X Faiwed. Status: 0x%X\n",
			WIWED_VEWIFY_WECEIVEW_CEWT,
			vewify_wxcewt_out.headew.status);
		wetuwn -EIO;
	}

	*km_stowed = !!vewify_wxcewt_out.km_stowed;
	if (vewify_wxcewt_out.km_stowed) {
		ek_pub_km->msg_id = HDCP_2_2_AKE_STOWED_KM;
		*msg_sz = sizeof(stwuct hdcp2_ake_stowed_km);
	} ewse {
		ek_pub_km->msg_id = HDCP_2_2_AKE_NO_STOWED_KM;
		*msg_sz = sizeof(stwuct hdcp2_ake_no_stowed_km);
	}

	memcpy(ek_pub_km->e_kpub_km, &vewify_wxcewt_out.ekm_buff,
	       sizeof(vewify_wxcewt_out.ekm_buff));

	wetuwn 0;
}

/**
 * mei_hdcp_vewify_hpwime() - Vewify AKE_Send_H_pwime at ME FW.
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @wx_hpwime: AKE_Send_H_pwime msg fow ME FW vewification
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_vewify_hpwime(stwuct device *dev, stwuct hdcp_powt_data *data,
		       stwuct hdcp2_ake_send_hpwime *wx_hpwime)
{
	stwuct wiwed_cmd_ake_send_hpwime_in send_hpwime_in = { { 0 } };
	stwuct wiwed_cmd_ake_send_hpwime_out send_hpwime_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !wx_hpwime)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	send_hpwime_in.headew.api_vewsion = HDCP_API_VEWSION;
	send_hpwime_in.headew.command_id = WIWED_AKE_SEND_HPWIME;
	send_hpwime_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	send_hpwime_in.headew.buffew_wen = WIWED_CMD_BUF_WEN_AKE_SEND_HPWIME_IN;

	send_hpwime_in.powt.integwated_powt_type = data->powt_type;
	send_hpwime_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	send_hpwime_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	memcpy(send_hpwime_in.h_pwime, wx_hpwime->h_pwime,
	       HDCP_2_2_H_PWIME_WEN);

	byte = mei_cwdev_send(cwdev, (u8 *)&send_hpwime_in,
			      sizeof(send_hpwime_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&send_hpwime_out,
			      sizeof(send_hpwime_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (send_hpwime_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X Faiwed. Status: 0x%X\n",
			WIWED_AKE_SEND_HPWIME, send_hpwime_out.headew.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * mei_hdcp_stowe_paiwing_info() - Stowe paiwing info weceived at ME FW
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @paiwing_info: AKE_Send_Paiwing_Info msg input to ME FW
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_stowe_paiwing_info(stwuct device *dev, stwuct hdcp_powt_data *data,
			    stwuct hdcp2_ake_send_paiwing_info *paiwing_info)
{
	stwuct wiwed_cmd_ake_send_paiwing_info_in paiwing_info_in = { { 0 } };
	stwuct wiwed_cmd_ake_send_paiwing_info_out paiwing_info_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !paiwing_info)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	paiwing_info_in.headew.api_vewsion = HDCP_API_VEWSION;
	paiwing_info_in.headew.command_id = WIWED_AKE_SEND_PAIWING_INFO;
	paiwing_info_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	paiwing_info_in.headew.buffew_wen =
					WIWED_CMD_BUF_WEN_SEND_PAIWING_INFO_IN;

	paiwing_info_in.powt.integwated_powt_type = data->powt_type;
	paiwing_info_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	paiwing_info_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	memcpy(paiwing_info_in.e_kh_km, paiwing_info->e_kh_km,
	       HDCP_2_2_E_KH_KM_WEN);

	byte = mei_cwdev_send(cwdev, (u8 *)&paiwing_info_in,
			      sizeof(paiwing_info_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&paiwing_info_out,
			      sizeof(paiwing_info_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (paiwing_info_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X faiwed. Status: 0x%X\n",
			WIWED_AKE_SEND_PAIWING_INFO,
			paiwing_info_out.headew.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * mei_hdcp_initiate_wocawity_check() - Pwepawe WC_Init
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @wc_init_data: WC_Init msg output
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_initiate_wocawity_check(stwuct device *dev,
				 stwuct hdcp_powt_data *data,
				 stwuct hdcp2_wc_init *wc_init_data)
{
	stwuct wiwed_cmd_init_wocawity_check_in wc_init_in = { { 0 } };
	stwuct wiwed_cmd_init_wocawity_check_out wc_init_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !wc_init_data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	wc_init_in.headew.api_vewsion = HDCP_API_VEWSION;
	wc_init_in.headew.command_id = WIWED_INIT_WOCAWITY_CHECK;
	wc_init_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	wc_init_in.headew.buffew_wen = WIWED_CMD_BUF_WEN_INIT_WOCAWITY_CHECK_IN;

	wc_init_in.powt.integwated_powt_type = data->powt_type;
	wc_init_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	wc_init_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	byte = mei_cwdev_send(cwdev, (u8 *)&wc_init_in, sizeof(wc_init_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&wc_init_out, sizeof(wc_init_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (wc_init_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X Faiwed. status: 0x%X\n",
			WIWED_INIT_WOCAWITY_CHECK, wc_init_out.headew.status);
		wetuwn -EIO;
	}

	wc_init_data->msg_id = HDCP_2_2_WC_INIT;
	memcpy(wc_init_data->w_n, wc_init_out.w_n, HDCP_2_2_WN_WEN);

	wetuwn 0;
}

/**
 * mei_hdcp_vewify_wpwime() - Vewify wpwime.
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @wx_wpwime: WC_Send_W_pwime msg fow ME FW vewification
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_vewify_wpwime(stwuct device *dev, stwuct hdcp_powt_data *data,
		       stwuct hdcp2_wc_send_wpwime *wx_wpwime)
{
	stwuct wiwed_cmd_vawidate_wocawity_in vewify_wpwime_in = { { 0 } };
	stwuct wiwed_cmd_vawidate_wocawity_out vewify_wpwime_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !wx_wpwime)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	vewify_wpwime_in.headew.api_vewsion = HDCP_API_VEWSION;
	vewify_wpwime_in.headew.command_id = WIWED_VAWIDATE_WOCAWITY;
	vewify_wpwime_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	vewify_wpwime_in.headew.buffew_wen =
					WIWED_CMD_BUF_WEN_VAWIDATE_WOCAWITY_IN;

	vewify_wpwime_in.powt.integwated_powt_type = data->powt_type;
	vewify_wpwime_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	vewify_wpwime_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	memcpy(vewify_wpwime_in.w_pwime, wx_wpwime->w_pwime,
	       HDCP_2_2_W_PWIME_WEN);

	byte = mei_cwdev_send(cwdev, (u8 *)&vewify_wpwime_in,
			      sizeof(vewify_wpwime_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&vewify_wpwime_out,
			      sizeof(vewify_wpwime_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (vewify_wpwime_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X faiwed. status: 0x%X\n",
			WIWED_VAWIDATE_WOCAWITY,
			vewify_wpwime_out.headew.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * mei_hdcp_get_session_key() - Pwepawe SKE_Send_Eks.
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @ske_data: SKE_Send_Eks msg output fwom ME FW.
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int mei_hdcp_get_session_key(stwuct device *dev,
				    stwuct hdcp_powt_data *data,
				    stwuct hdcp2_ske_send_eks *ske_data)
{
	stwuct wiwed_cmd_get_session_key_in get_skey_in = { { 0 } };
	stwuct wiwed_cmd_get_session_key_out get_skey_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data || !ske_data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	get_skey_in.headew.api_vewsion = HDCP_API_VEWSION;
	get_skey_in.headew.command_id = WIWED_GET_SESSION_KEY;
	get_skey_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	get_skey_in.headew.buffew_wen = WIWED_CMD_BUF_WEN_GET_SESSION_KEY_IN;

	get_skey_in.powt.integwated_powt_type = data->powt_type;
	get_skey_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	get_skey_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	byte = mei_cwdev_send(cwdev, (u8 *)&get_skey_in, sizeof(get_skey_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&get_skey_out, sizeof(get_skey_out));

	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (get_skey_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X faiwed. status: 0x%X\n",
			WIWED_GET_SESSION_KEY, get_skey_out.headew.status);
		wetuwn -EIO;
	}

	ske_data->msg_id = HDCP_2_2_SKE_SEND_EKS;
	memcpy(ske_data->e_dkey_ks, get_skey_out.e_dkey_ks,
	       HDCP_2_2_E_DKEY_KS_WEN);
	memcpy(ske_data->wiv, get_skey_out.w_iv, HDCP_2_2_WIV_WEN);

	wetuwn 0;
}

/**
 * mei_hdcp_wepeatew_check_fwow_pwepawe_ack() - Vawidate the Downstweam topowogy
 * and pwepawe wep_ack.
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @wep_topowogy: Weceivew ID Wist to be vawidated
 * @wep_send_ack : wepeatew ack fwom ME FW.
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_wepeatew_check_fwow_pwepawe_ack(stwuct device *dev,
					 stwuct hdcp_powt_data *data,
					 stwuct hdcp2_wep_send_weceivewid_wist
							*wep_topowogy,
					 stwuct hdcp2_wep_send_ack
							*wep_send_ack)
{
	stwuct wiwed_cmd_vewify_wepeatew_in vewify_wepeatew_in = { { 0 } };
	stwuct wiwed_cmd_vewify_wepeatew_out vewify_wepeatew_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !wep_topowogy || !wep_send_ack || !data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	vewify_wepeatew_in.headew.api_vewsion = HDCP_API_VEWSION;
	vewify_wepeatew_in.headew.command_id = WIWED_VEWIFY_WEPEATEW;
	vewify_wepeatew_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	vewify_wepeatew_in.headew.buffew_wen =
					WIWED_CMD_BUF_WEN_VEWIFY_WEPEATEW_IN;

	vewify_wepeatew_in.powt.integwated_powt_type = data->powt_type;
	vewify_wepeatew_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	vewify_wepeatew_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	memcpy(vewify_wepeatew_in.wx_info, wep_topowogy->wx_info,
	       HDCP_2_2_WXINFO_WEN);
	memcpy(vewify_wepeatew_in.seq_num_v, wep_topowogy->seq_num_v,
	       HDCP_2_2_SEQ_NUM_WEN);
	memcpy(vewify_wepeatew_in.v_pwime, wep_topowogy->v_pwime,
	       HDCP_2_2_V_PWIME_HAWF_WEN);
	memcpy(vewify_wepeatew_in.weceivew_ids, wep_topowogy->weceivew_ids,
	       HDCP_2_2_WECEIVEW_IDS_MAX_WEN);

	byte = mei_cwdev_send(cwdev, (u8 *)&vewify_wepeatew_in,
			      sizeof(vewify_wepeatew_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&vewify_wepeatew_out,
			      sizeof(vewify_wepeatew_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (vewify_wepeatew_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X faiwed. status: 0x%X\n",
			WIWED_VEWIFY_WEPEATEW,
			vewify_wepeatew_out.headew.status);
		wetuwn -EIO;
	}

	memcpy(wep_send_ack->v, vewify_wepeatew_out.v,
	       HDCP_2_2_V_PWIME_HAWF_WEN);
	wep_send_ack->msg_id = HDCP_2_2_WEP_SEND_ACK;

	wetuwn 0;
}

/**
 * mei_hdcp_vewify_mpwime() - Vewify mpwime.
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 * @stweam_weady: WepeatewAuth_Stweam_Weady msg fow ME FW vewification.
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int mei_hdcp_vewify_mpwime(stwuct device *dev,
				  stwuct hdcp_powt_data *data,
				  stwuct hdcp2_wep_stweam_weady *stweam_weady)
{
	stwuct wiwed_cmd_wepeatew_auth_stweam_weq_in *vewify_mpwime_in;
	stwuct wiwed_cmd_wepeatew_auth_stweam_weq_out
					vewify_mpwime_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;
	size_t cmd_size;

	if (!dev || !stweam_weady || !data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	cmd_size = stwuct_size(vewify_mpwime_in, stweams, data->k);
	if (cmd_size == SIZE_MAX)
		wetuwn -EINVAW;

	vewify_mpwime_in = kzawwoc(cmd_size, GFP_KEWNEW);
	if (!vewify_mpwime_in)
		wetuwn -ENOMEM;

	vewify_mpwime_in->headew.api_vewsion = HDCP_API_VEWSION;
	vewify_mpwime_in->headew.command_id = WIWED_WEPEATEW_AUTH_STWEAM_WEQ;
	vewify_mpwime_in->headew.status = FW_HDCP_STATUS_SUCCESS;
	vewify_mpwime_in->headew.buffew_wen = cmd_size  - sizeof(vewify_mpwime_in->headew);

	vewify_mpwime_in->powt.integwated_powt_type = data->powt_type;
	vewify_mpwime_in->powt.physicaw_powt = (u8)data->hdcp_ddi;
	vewify_mpwime_in->powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	memcpy(vewify_mpwime_in->m_pwime, stweam_weady->m_pwime, HDCP_2_2_MPWIME_WEN);
	dwm_hdcp_cpu_to_be24(vewify_mpwime_in->seq_num_m, data->seq_num_m);

	memcpy(vewify_mpwime_in->stweams, data->stweams,
	       awway_size(data->k, sizeof(*data->stweams)));

	vewify_mpwime_in->k = cpu_to_be16(data->k);

	byte = mei_cwdev_send(cwdev, (u8 *)vewify_mpwime_in, cmd_size);
	kfwee(vewify_mpwime_in);
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&vewify_mpwime_out,
			      sizeof(vewify_mpwime_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (vewify_mpwime_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X faiwed. status: 0x%X\n",
			WIWED_WEPEATEW_AUTH_STWEAM_WEQ,
			vewify_mpwime_out.headew.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * mei_hdcp_enabwe_authentication() - Mawk a powt as authenticated
 * thwough ME FW
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int mei_hdcp_enabwe_authentication(stwuct device *dev,
					  stwuct hdcp_powt_data *data)
{
	stwuct wiwed_cmd_enabwe_auth_in enabwe_auth_in = { { 0 } };
	stwuct wiwed_cmd_enabwe_auth_out enabwe_auth_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	enabwe_auth_in.headew.api_vewsion = HDCP_API_VEWSION;
	enabwe_auth_in.headew.command_id = WIWED_ENABWE_AUTH;
	enabwe_auth_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	enabwe_auth_in.headew.buffew_wen = WIWED_CMD_BUF_WEN_ENABWE_AUTH_IN;

	enabwe_auth_in.powt.integwated_powt_type = data->powt_type;
	enabwe_auth_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	enabwe_auth_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;
	enabwe_auth_in.stweam_type = data->stweams[0].stweam_type;

	byte = mei_cwdev_send(cwdev, (u8 *)&enabwe_auth_in,
			      sizeof(enabwe_auth_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&enabwe_auth_out,
			      sizeof(enabwe_auth_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (enabwe_auth_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "ME cmd 0x%08X faiwed. status: 0x%X\n",
			WIWED_ENABWE_AUTH, enabwe_auth_out.headew.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * mei_hdcp_cwose_session() - Cwose the Wiwed HDCP Tx session of ME FW pew powt.
 * This awso disabwes the authenticated state of the powt.
 * @dev: device cowwesponding to the mei_cw_device
 * @data: Intew HW specific hdcp data
 *
 * Wetuwn: 0 on Success, <0 on Faiwuwe
 */
static int
mei_hdcp_cwose_session(stwuct device *dev, stwuct hdcp_powt_data *data)
{
	stwuct wiwed_cmd_cwose_session_in session_cwose_in = { { 0 } };
	stwuct wiwed_cmd_cwose_session_out session_cwose_out = { { 0 } };
	stwuct mei_cw_device *cwdev;
	ssize_t byte;

	if (!dev || !data)
		wetuwn -EINVAW;

	cwdev = to_mei_cw_device(dev);

	session_cwose_in.headew.api_vewsion = HDCP_API_VEWSION;
	session_cwose_in.headew.command_id = WIWED_CWOSE_SESSION;
	session_cwose_in.headew.status = FW_HDCP_STATUS_SUCCESS;
	session_cwose_in.headew.buffew_wen =
				WIWED_CMD_BUF_WEN_CWOSE_SESSION_IN;

	session_cwose_in.powt.integwated_powt_type = data->powt_type;
	session_cwose_in.powt.physicaw_powt = (u8)data->hdcp_ddi;
	session_cwose_in.powt.attached_twanscodew = (u8)data->hdcp_twanscodew;

	byte = mei_cwdev_send(cwdev, (u8 *)&session_cwose_in,
			      sizeof(session_cwose_in));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_send faiwed. %zd\n", byte);
		wetuwn byte;
	}

	byte = mei_cwdev_wecv(cwdev, (u8 *)&session_cwose_out,
			      sizeof(session_cwose_out));
	if (byte < 0) {
		dev_dbg(dev, "mei_cwdev_wecv faiwed. %zd\n", byte);
		wetuwn byte;
	}

	if (session_cwose_out.headew.status != FW_HDCP_STATUS_SUCCESS) {
		dev_dbg(dev, "Session Cwose Faiwed. status: 0x%X\n",
			session_cwose_out.headew.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct i915_hdcp_ops mei_hdcp_ops = {
	.ownew = THIS_MODUWE,
	.initiate_hdcp2_session = mei_hdcp_initiate_session,
	.vewify_weceivew_cewt_pwepawe_km =
				mei_hdcp_vewify_weceivew_cewt_pwepawe_km,
	.vewify_hpwime = mei_hdcp_vewify_hpwime,
	.stowe_paiwing_info = mei_hdcp_stowe_paiwing_info,
	.initiate_wocawity_check = mei_hdcp_initiate_wocawity_check,
	.vewify_wpwime = mei_hdcp_vewify_wpwime,
	.get_session_key = mei_hdcp_get_session_key,
	.wepeatew_check_fwow_pwepawe_ack =
				mei_hdcp_wepeatew_check_fwow_pwepawe_ack,
	.vewify_mpwime = mei_hdcp_vewify_mpwime,
	.enabwe_hdcp_authentication = mei_hdcp_enabwe_authentication,
	.cwose_hdcp_session = mei_hdcp_cwose_session,
};

static int mei_component_mastew_bind(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct i915_hdcp_awbitew *comp_awbitew = mei_cwdev_get_dwvdata(cwdev);
	int wet;

	dev_dbg(dev, "%s\n", __func__);
	comp_awbitew->ops = &mei_hdcp_ops;
	comp_awbitew->hdcp_dev = dev;
	wet = component_bind_aww(dev, comp_awbitew);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void mei_component_mastew_unbind(stwuct device *dev)
{
	stwuct mei_cw_device *cwdev = to_mei_cw_device(dev);
	stwuct i915_hdcp_awbitew *comp_awbitew = mei_cwdev_get_dwvdata(cwdev);

	dev_dbg(dev, "%s\n", __func__);
	component_unbind_aww(dev, comp_awbitew);
}

static const stwuct component_mastew_ops mei_component_mastew_ops = {
	.bind = mei_component_mastew_bind,
	.unbind = mei_component_mastew_unbind,
};

/**
 * mei_hdcp_component_match - compawe function fow matching mei hdcp.
 *
 *    The function checks if the dwivew is i915, the subcomponent is HDCP
 *    and the gwand pawent of hdcp and the pawent of i915 awe the same
 *    PCH device.
 *
 * @dev: mastew device
 * @subcomponent: subcomponent to match (I915_COMPONENT_HDCP)
 * @data: compawe data (mei hdcp device)
 *
 * Wetuwn:
 * * 1 - if components match
 * * 0 - othewwise
 */
static int mei_hdcp_component_match(stwuct device *dev, int subcomponent,
				    void *data)
{
	stwuct device *base = data;

	if (!dev->dwivew || stwcmp(dev->dwivew->name, "i915") ||
	    subcomponent != I915_COMPONENT_HDCP)
		wetuwn 0;

	base = base->pawent;
	if (!base)
		wetuwn 0;

	base = base->pawent;
	dev = dev->pawent;

	wetuwn (base && dev && dev == base);
}

static int mei_hdcp_pwobe(stwuct mei_cw_device *cwdev,
			  const stwuct mei_cw_device_id *id)
{
	stwuct i915_hdcp_awbitew *comp_awbitew;
	stwuct component_match *mastew_match;
	int wet;

	wet = mei_cwdev_enabwe(cwdev);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "mei_cwdev_enabwe Faiwed. %d\n", wet);
		goto enabwe_eww_exit;
	}

	comp_awbitew = kzawwoc(sizeof(*comp_awbitew), GFP_KEWNEW);
	if (!comp_awbitew) {
		wet = -ENOMEM;
		goto eww_exit;
	}

	mastew_match = NUWW;
	component_match_add_typed(&cwdev->dev, &mastew_match,
				  mei_hdcp_component_match, &cwdev->dev);
	if (IS_EWW_OW_NUWW(mastew_match)) {
		wet = -ENOMEM;
		goto eww_exit;
	}

	mei_cwdev_set_dwvdata(cwdev, comp_awbitew);
	wet = component_mastew_add_with_match(&cwdev->dev,
					      &mei_component_mastew_ops,
					      mastew_match);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "Mastew comp add faiwed %d\n", wet);
		goto eww_exit;
	}

	wetuwn 0;

eww_exit:
	mei_cwdev_set_dwvdata(cwdev, NUWW);
	kfwee(comp_awbitew);
	mei_cwdev_disabwe(cwdev);
enabwe_eww_exit:
	wetuwn wet;
}

static void mei_hdcp_wemove(stwuct mei_cw_device *cwdev)
{
	stwuct i915_hdcp_awbitew *comp_awbitew = mei_cwdev_get_dwvdata(cwdev);
	int wet;

	component_mastew_dew(&cwdev->dev, &mei_component_mastew_ops);
	kfwee(comp_awbitew);
	mei_cwdev_set_dwvdata(cwdev, NUWW);

	wet = mei_cwdev_disabwe(cwdev);
	if (wet)
		dev_wawn(&cwdev->dev, "mei_cwdev_disabwe() faiwed\n");
}

#define MEI_UUID_HDCP UUID_WE(0xB638AB7E, 0x94E2, 0x4EA2, 0xA5, \
			      0x52, 0xD1, 0xC5, 0x4B, 0x62, 0x7F, 0x04)

static const stwuct mei_cw_device_id mei_hdcp_tbw[] = {
	{ .uuid = MEI_UUID_HDCP, .vewsion = MEI_CW_VEWSION_ANY },
	{ }
};
MODUWE_DEVICE_TABWE(mei, mei_hdcp_tbw);

static stwuct mei_cw_dwivew mei_hdcp_dwivew = {
	.id_tabwe = mei_hdcp_tbw,
	.name = KBUIWD_MODNAME,
	.pwobe = mei_hdcp_pwobe,
	.wemove	= mei_hdcp_wemove,
};

moduwe_mei_cw_dwivew(mei_hdcp_dwivew);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MEI HDCP");
