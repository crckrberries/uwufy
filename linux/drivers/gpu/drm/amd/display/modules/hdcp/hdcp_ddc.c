/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude "hdcp.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define HDCP_I2C_ADDW 0x3a	/* 0x74 >> 1*/
#define KSV_WEAD_SIZE 0xf	/* 0x6803b - 0x6802c */
#define HDCP_MAX_AUX_TWANSACTION_SIZE 16

#define DP_CP_IWQ (1 << 2)

enum mod_hdcp_ddc_message_id {
	MOD_HDCP_MESSAGE_ID_INVAWID = -1,

	/* HDCP 1.4 */

	MOD_HDCP_MESSAGE_ID_WEAD_BKSV = 0,
	MOD_HDCP_MESSAGE_ID_WEAD_WI_W0,
	MOD_HDCP_MESSAGE_ID_WWITE_AKSV,
	MOD_HDCP_MESSAGE_ID_WWITE_AINFO,
	MOD_HDCP_MESSAGE_ID_WWITE_AN,
	MOD_HDCP_MESSAGE_ID_WEAD_VH_X,
	MOD_HDCP_MESSAGE_ID_WEAD_VH_0,
	MOD_HDCP_MESSAGE_ID_WEAD_VH_1,
	MOD_HDCP_MESSAGE_ID_WEAD_VH_2,
	MOD_HDCP_MESSAGE_ID_WEAD_VH_3,
	MOD_HDCP_MESSAGE_ID_WEAD_VH_4,
	MOD_HDCP_MESSAGE_ID_WEAD_BCAPS,
	MOD_HDCP_MESSAGE_ID_WEAD_BSTATUS,
	MOD_HDCP_MESSAGE_ID_WEAD_KSV_FIFO,
	MOD_HDCP_MESSAGE_ID_WEAD_BINFO,

	/* HDCP 2.2 */

	MOD_HDCP_MESSAGE_ID_HDCP2VEWSION,
	MOD_HDCP_MESSAGE_ID_WX_CAPS,
	MOD_HDCP_MESSAGE_ID_WWITE_AKE_INIT,
	MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT,
	MOD_HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM,
	MOD_HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM,
	MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME,
	MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO,
	MOD_HDCP_MESSAGE_ID_WWITE_WC_INIT,
	MOD_HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME,
	MOD_HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS,
	MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST,
	MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST_PAWT2,
	MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK,
	MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE,
	MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY,
	MOD_HDCP_MESSAGE_ID_WEAD_WXSTATUS,
	MOD_HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE,

	MOD_HDCP_MESSAGE_ID_MAX
};

static const uint8_t hdcp_i2c_offsets[] = {
	[MOD_HDCP_MESSAGE_ID_WEAD_BKSV] = 0x0,
	[MOD_HDCP_MESSAGE_ID_WEAD_WI_W0] = 0x8,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKSV] = 0x10,
	[MOD_HDCP_MESSAGE_ID_WWITE_AINFO] = 0x15,
	[MOD_HDCP_MESSAGE_ID_WWITE_AN] = 0x18,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_X] = 0x20,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_0] = 0x20,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_1] = 0x24,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_2] = 0x28,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_3] = 0x2C,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_4] = 0x30,
	[MOD_HDCP_MESSAGE_ID_WEAD_BCAPS] = 0x40,
	[MOD_HDCP_MESSAGE_ID_WEAD_BSTATUS] = 0x41,
	[MOD_HDCP_MESSAGE_ID_WEAD_KSV_FIFO] = 0x43,
	[MOD_HDCP_MESSAGE_ID_WEAD_BINFO] = 0xFF,
	[MOD_HDCP_MESSAGE_ID_HDCP2VEWSION] = 0x50,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKE_INIT] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WWITE_WC_INIT] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST_PAWT2] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE] = 0x60,
	[MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY] = 0x80,
	[MOD_HDCP_MESSAGE_ID_WEAD_WXSTATUS] = 0x70,
	[MOD_HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE] = 0x0
};

static const uint32_t hdcp_dpcd_addws[] = {
	[MOD_HDCP_MESSAGE_ID_WEAD_BKSV] = 0x68000,
	[MOD_HDCP_MESSAGE_ID_WEAD_WI_W0] = 0x68005,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKSV] = 0x68007,
	[MOD_HDCP_MESSAGE_ID_WWITE_AINFO] = 0x6803B,
	[MOD_HDCP_MESSAGE_ID_WWITE_AN] = 0x6800c,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_X] = 0x68014,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_0] = 0x68014,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_1] = 0x68018,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_2] = 0x6801c,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_3] = 0x68020,
	[MOD_HDCP_MESSAGE_ID_WEAD_VH_4] = 0x68024,
	[MOD_HDCP_MESSAGE_ID_WEAD_BCAPS] = 0x68028,
	[MOD_HDCP_MESSAGE_ID_WEAD_BSTATUS] = 0x68029,
	[MOD_HDCP_MESSAGE_ID_WEAD_KSV_FIFO] = 0x6802c,
	[MOD_HDCP_MESSAGE_ID_WEAD_BINFO] = 0x6802a,
	[MOD_HDCP_MESSAGE_ID_WX_CAPS] = 0x6921d,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKE_INIT] = 0x69000,
	[MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT] = 0x6900b,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM] = 0x69220,
	[MOD_HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM] = 0x692a0,
	[MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME] = 0x692c0,
	[MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO] = 0x692e0,
	[MOD_HDCP_MESSAGE_ID_WWITE_WC_INIT] = 0x692f0,
	[MOD_HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME] = 0x692f8,
	[MOD_HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS] = 0x69318,
	[MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST] = 0x69330,
	[MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST_PAWT2] = 0x69340,
	[MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK] = 0x693e0,
	[MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE] = 0x693f0,
	[MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY] = 0x69473,
	[MOD_HDCP_MESSAGE_ID_WEAD_WXSTATUS] = 0x69493,
	[MOD_HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE] = 0x69494
};

static enum mod_hdcp_status wead(stwuct mod_hdcp *hdcp,
		enum mod_hdcp_ddc_message_id msg_id,
		uint8_t *buf,
		uint32_t buf_wen)
{
	boow success = twue;
	uint32_t cuw_size = 0;
	uint32_t data_offset = 0;

	if (is_dp_hdcp(hdcp)) {
		whiwe (buf_wen > 0) {
			cuw_size = MIN(buf_wen, HDCP_MAX_AUX_TWANSACTION_SIZE);
			success = hdcp->config.ddc.funcs.wead_dpcd(hdcp->config.ddc.handwe,
					hdcp_dpcd_addws[msg_id] + data_offset,
					buf + data_offset,
					cuw_size);

			if (!success)
				bweak;

			buf_wen -= cuw_size;
			data_offset += cuw_size;
		}
	} ewse {
		success = hdcp->config.ddc.funcs.wead_i2c(
				hdcp->config.ddc.handwe,
				HDCP_I2C_ADDW,
				hdcp_i2c_offsets[msg_id],
				buf,
				(uint32_t)buf_wen);
	}

	wetuwn success ? MOD_HDCP_STATUS_SUCCESS : MOD_HDCP_STATUS_DDC_FAIWUWE;
}

static enum mod_hdcp_status wead_wepeatedwy(stwuct mod_hdcp *hdcp,
		enum mod_hdcp_ddc_message_id msg_id,
		uint8_t *buf,
		uint32_t buf_wen,
		uint8_t wead_size)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_DDC_FAIWUWE;
	uint32_t cuw_size = 0;
	uint32_t data_offset = 0;

	whiwe (buf_wen > 0) {
		cuw_size = MIN(buf_wen, wead_size);
		status = wead(hdcp, msg_id, buf + data_offset, cuw_size);

		if (status != MOD_HDCP_STATUS_SUCCESS)
			bweak;

		buf_wen -= cuw_size;
		data_offset += cuw_size;
	}

	wetuwn status;
}

static enum mod_hdcp_status wwite(stwuct mod_hdcp *hdcp,
		enum mod_hdcp_ddc_message_id msg_id,
		uint8_t *buf,
		uint32_t buf_wen)
{
	boow success = twue;
	uint32_t cuw_size = 0;
	uint32_t data_offset = 0;

	if (is_dp_hdcp(hdcp)) {
		whiwe (buf_wen > 0) {
			cuw_size = MIN(buf_wen, HDCP_MAX_AUX_TWANSACTION_SIZE);
			success = hdcp->config.ddc.funcs.wwite_dpcd(
					hdcp->config.ddc.handwe,
					hdcp_dpcd_addws[msg_id] + data_offset,
					buf + data_offset,
					cuw_size);

			if (!success)
				bweak;

			buf_wen -= cuw_size;
			data_offset += cuw_size;
		}
	} ewse {
		hdcp->buf[0] = hdcp_i2c_offsets[msg_id];
		memmove(&hdcp->buf[1], buf, buf_wen);
		success = hdcp->config.ddc.funcs.wwite_i2c(
				hdcp->config.ddc.handwe,
				HDCP_I2C_ADDW,
				hdcp->buf,
				(uint32_t)(buf_wen+1));
	}

	wetuwn success ? MOD_HDCP_STATUS_SUCCESS : MOD_HDCP_STATUS_DDC_FAIWUWE;
}

enum mod_hdcp_status mod_hdcp_wead_bksv(stwuct mod_hdcp *hdcp)
{
	wetuwn wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_BKSV,
			hdcp->auth.msg.hdcp1.bksv,
			sizeof(hdcp->auth.msg.hdcp1.bksv));
}

enum mod_hdcp_status mod_hdcp_wead_bcaps(stwuct mod_hdcp *hdcp)
{
	wetuwn wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_BCAPS,
			&hdcp->auth.msg.hdcp1.bcaps,
			sizeof(hdcp->auth.msg.hdcp1.bcaps));
}

enum mod_hdcp_status mod_hdcp_wead_bstatus(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_BSTATUS,
					(uint8_t *)&hdcp->auth.msg.hdcp1.bstatus,
					1);
	ewse
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_BSTATUS,
				(uint8_t *)&hdcp->auth.msg.hdcp1.bstatus,
				sizeof(hdcp->auth.msg.hdcp1.bstatus));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_w0p(stwuct mod_hdcp *hdcp)
{
	wetuwn wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WI_W0,
			(uint8_t *)&hdcp->auth.msg.hdcp1.w0p,
			sizeof(hdcp->auth.msg.hdcp1.w0p));
}

/* speciaw case, weading wepeatedwy at the same addwess, don't use wead() */
enum mod_hdcp_status mod_hdcp_wead_ksvwist(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wead_wepeatedwy(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_KSV_FIFO,
				hdcp->auth.msg.hdcp1.ksvwist,
				hdcp->auth.msg.hdcp1.ksvwist_size,
				KSV_WEAD_SIZE);
	ewse
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_KSV_FIFO,
				(uint8_t *)&hdcp->auth.msg.hdcp1.ksvwist,
				hdcp->auth.msg.hdcp1.ksvwist_size);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_vp(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_VH_0,
			&hdcp->auth.msg.hdcp1.vp[0], 4);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_VH_1,
			&hdcp->auth.msg.hdcp1.vp[4], 4);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_VH_2,
			&hdcp->auth.msg.hdcp1.vp[8], 4);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_VH_3,
			&hdcp->auth.msg.hdcp1.vp[12], 4);
	if (status != MOD_HDCP_STATUS_SUCCESS)
		goto out;

	status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_VH_4,
			&hdcp->auth.msg.hdcp1.vp[16], 4);
out:
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_binfo(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_BINFO,
				(uint8_t *)&hdcp->auth.msg.hdcp1.binfo_dp,
				sizeof(hdcp->auth.msg.hdcp1.binfo_dp));
	ewse
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_aksv(stwuct mod_hdcp *hdcp)
{
	wetuwn wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKSV,
			hdcp->auth.msg.hdcp1.aksv,
			sizeof(hdcp->auth.msg.hdcp1.aksv));
}

enum mod_hdcp_status mod_hdcp_wwite_ainfo(stwuct mod_hdcp *hdcp)
{
	wetuwn wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AINFO,
			&hdcp->auth.msg.hdcp1.ainfo,
			sizeof(hdcp->auth.msg.hdcp1.ainfo));
}

enum mod_hdcp_status mod_hdcp_wwite_an(stwuct mod_hdcp *hdcp)
{
	wetuwn wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AN,
			hdcp->auth.msg.hdcp1.an,
			sizeof(hdcp->auth.msg.hdcp1.an));
}

enum mod_hdcp_status mod_hdcp_wead_hdcp2vewsion(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;
	ewse
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_HDCP2VEWSION,
				&hdcp->auth.msg.hdcp2.hdcp2vewsion_hdmi,
				sizeof(hdcp->auth.msg.hdcp2.hdcp2vewsion_hdmi));

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_wxcaps(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (!is_dp_hdcp(hdcp))
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;
	ewse
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WX_CAPS,
				hdcp->auth.msg.hdcp2.wxcaps_dp,
				sizeof(hdcp->auth.msg.hdcp2.wxcaps_dp));

	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_wxstatus(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WXSTATUS,
				&hdcp->auth.msg.hdcp2.wxstatus_dp,
				1);
	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WXSTATUS,
					(uint8_t *)&hdcp->auth.msg.hdcp2.wxstatus,
					sizeof(hdcp->auth.msg.hdcp2.wxstatus));
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_ake_cewt(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		hdcp->auth.msg.hdcp2.ake_cewt[0] = HDCP_2_2_AKE_SEND_CEWT;
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT,
				hdcp->auth.msg.hdcp2.ake_cewt+1,
				sizeof(hdcp->auth.msg.hdcp2.ake_cewt)-1);

	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT,
					hdcp->auth.msg.hdcp2.ake_cewt,
					sizeof(hdcp->auth.msg.hdcp2.ake_cewt));
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_h_pwime(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		hdcp->auth.msg.hdcp2.ake_h_pwime[0] = HDCP_2_2_AKE_SEND_HPWIME;
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME,
				hdcp->auth.msg.hdcp2.ake_h_pwime+1,
				sizeof(hdcp->auth.msg.hdcp2.ake_h_pwime)-1);

	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME,
				hdcp->auth.msg.hdcp2.ake_h_pwime,
				sizeof(hdcp->auth.msg.hdcp2.ake_h_pwime));
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_paiwing_info(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		hdcp->auth.msg.hdcp2.ake_paiwing_info[0] = HDCP_2_2_AKE_SEND_PAIWING_INFO;
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO,
				hdcp->auth.msg.hdcp2.ake_paiwing_info+1,
				sizeof(hdcp->auth.msg.hdcp2.ake_paiwing_info)-1);

	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO,
				hdcp->auth.msg.hdcp2.ake_paiwing_info,
				sizeof(hdcp->auth.msg.hdcp2.ake_paiwing_info));
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_w_pwime(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		hdcp->auth.msg.hdcp2.wc_w_pwime[0] = HDCP_2_2_WC_SEND_WPWIME;
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME,
				hdcp->auth.msg.hdcp2.wc_w_pwime+1,
				sizeof(hdcp->auth.msg.hdcp2.wc_w_pwime)-1);

	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME,
				hdcp->auth.msg.hdcp2.wc_w_pwime,
				sizeof(hdcp->auth.msg.hdcp2.wc_w_pwime));
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_wx_id_wist(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status = MOD_HDCP_STATUS_SUCCESS;

	if (is_dp_hdcp(hdcp)) {
		uint32_t device_count = 0;
		uint32_t wx_id_wist_size = 0;
		uint32_t bytes_wead = 0;

		hdcp->auth.msg.hdcp2.wx_id_wist[0] = HDCP_2_2_WEP_SEND_WECVID_WIST;
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST,
						hdcp->auth.msg.hdcp2.wx_id_wist+1,
						HDCP_MAX_AUX_TWANSACTION_SIZE);
		if (status == MOD_HDCP_STATUS_SUCCESS) {
			bytes_wead = HDCP_MAX_AUX_TWANSACTION_SIZE;
			device_count = HDCP_2_2_DEV_COUNT_WO(hdcp->auth.msg.hdcp2.wx_id_wist[2]) +
					(HDCP_2_2_DEV_COUNT_HI(hdcp->auth.msg.hdcp2.wx_id_wist[1]) << 4);
			wx_id_wist_size = MIN((21 + 5 * device_count),
					(sizeof(hdcp->auth.msg.hdcp2.wx_id_wist) - 1));
			status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST_PAWT2,
					hdcp->auth.msg.hdcp2.wx_id_wist + 1 + bytes_wead,
					(wx_id_wist_size - 1) / HDCP_MAX_AUX_TWANSACTION_SIZE * HDCP_MAX_AUX_TWANSACTION_SIZE);
		}
	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST,
				hdcp->auth.msg.hdcp2.wx_id_wist,
				hdcp->auth.msg.hdcp2.wx_id_wist_size);
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wead_stweam_weady(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp)) {
		hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady[0] = HDCP_2_2_WEP_STWEAM_WEADY;
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY,
				hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady+1,
				sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady)-1);

	} ewse {
		status = wead(hdcp, MOD_HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY,
				hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady,
				sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady));
	}
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_ake_init(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKE_INIT,
				hdcp->auth.msg.hdcp2.ake_init+1,
				sizeof(hdcp->auth.msg.hdcp2.ake_init)-1);
	ewse
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKE_INIT,
					hdcp->auth.msg.hdcp2.ake_init,
					sizeof(hdcp->auth.msg.hdcp2.ake_init));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_no_stowed_km(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM,
				hdcp->auth.msg.hdcp2.ake_no_stowed_km+1,
				sizeof(hdcp->auth.msg.hdcp2.ake_no_stowed_km)-1);
	ewse
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM,
			hdcp->auth.msg.hdcp2.ake_no_stowed_km,
			sizeof(hdcp->auth.msg.hdcp2.ake_no_stowed_km));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_stowed_km(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM,
				hdcp->auth.msg.hdcp2.ake_stowed_km+1,
				sizeof(hdcp->auth.msg.hdcp2.ake_stowed_km)-1);
	ewse
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM,
				hdcp->auth.msg.hdcp2.ake_stowed_km,
				sizeof(hdcp->auth.msg.hdcp2.ake_stowed_km));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_wc_init(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_WC_INIT,
				hdcp->auth.msg.hdcp2.wc_init+1,
				sizeof(hdcp->auth.msg.hdcp2.wc_init)-1);
	ewse
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_WC_INIT,
				hdcp->auth.msg.hdcp2.wc_init,
				sizeof(hdcp->auth.msg.hdcp2.wc_init));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_eks(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp,
				MOD_HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS,
				hdcp->auth.msg.hdcp2.ske_eks+1,
				sizeof(hdcp->auth.msg.hdcp2.ske_eks)-1);
	ewse
		status = wwite(hdcp,
			MOD_HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS,
			hdcp->auth.msg.hdcp2.ske_eks,
			sizeof(hdcp->auth.msg.hdcp2.ske_eks));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_wepeatew_auth_ack(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK,
				hdcp->auth.msg.hdcp2.wepeatew_auth_ack+1,
				sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_ack)-1);
	ewse
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK,
				hdcp->auth.msg.hdcp2.wepeatew_auth_ack,
				sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_ack));
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_stweam_manage(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp,
				MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE,
				hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_manage+1,
				hdcp->auth.msg.hdcp2.stweam_manage_size-1);
	ewse
		status = wwite(hdcp,
				MOD_HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE,
				hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_manage,
				hdcp->auth.msg.hdcp2.stweam_manage_size);
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_wwite_content_type(stwuct mod_hdcp *hdcp)
{
	enum mod_hdcp_status status;

	if (is_dp_hdcp(hdcp))
		status = wwite(hdcp, MOD_HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE,
				hdcp->auth.msg.hdcp2.content_stweam_type_dp+1,
				sizeof(hdcp->auth.msg.hdcp2.content_stweam_type_dp)-1);
	ewse
		status = MOD_HDCP_STATUS_INVAWID_OPEWATION;
	wetuwn status;
}

enum mod_hdcp_status mod_hdcp_cweaw_cp_iwq_status(stwuct mod_hdcp *hdcp)
{
	uint8_t cweaw_cp_iwq_bit = DP_CP_IWQ;
	uint32_t size = 1;

	if (is_dp_hdcp(hdcp)) {
		uint32_t cp_iwq_addws = (hdcp->connection.wink.dp.wev >= 0x14)
				? DP_DEVICE_SEWVICE_IWQ_VECTOW_ESI0:DP_DEVICE_SEWVICE_IWQ_VECTOW;
		wetuwn hdcp->config.ddc.funcs.wwite_dpcd(hdcp->config.ddc.handwe, cp_iwq_addws,
				&cweaw_cp_iwq_bit, size) ? MOD_HDCP_STATUS_SUCCESS : MOD_HDCP_STATUS_DDC_FAIWUWE;
	}

	wetuwn MOD_HDCP_STATUS_INVAWID_OPEWATION;
}
