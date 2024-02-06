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

#incwude <winux/swab.h>

#incwude "dm_sewvices.h"
#incwude "dm_hewpews.h"
#incwude "incwude/hdcp_msg_types.h"
#incwude "incwude/signaw_types.h"
#incwude "cowe_types.h"
#incwude "wink.h"
#incwude "wink_hwss.h"
#incwude "wink/pwotocows/wink_dpcd.h"

#define DC_WOGGEW \
	wink->ctx->woggew
#define HDCP14_KSV_SIZE 5
#define HDCP14_MAX_KSV_FIFO_SIZE 127*HDCP14_KSV_SIZE

static const boow hdcp_cmd_is_wead[HDCP_MESSAGE_ID_MAX] = {
	[HDCP_MESSAGE_ID_WEAD_BKSV] = twue,
	[HDCP_MESSAGE_ID_WEAD_WI_W0] = twue,
	[HDCP_MESSAGE_ID_WEAD_PJ] = twue,
	[HDCP_MESSAGE_ID_WWITE_AKSV] = fawse,
	[HDCP_MESSAGE_ID_WWITE_AINFO] = fawse,
	[HDCP_MESSAGE_ID_WWITE_AN] = fawse,
	[HDCP_MESSAGE_ID_WEAD_VH_X] = twue,
	[HDCP_MESSAGE_ID_WEAD_VH_0] = twue,
	[HDCP_MESSAGE_ID_WEAD_VH_1] = twue,
	[HDCP_MESSAGE_ID_WEAD_VH_2] = twue,
	[HDCP_MESSAGE_ID_WEAD_VH_3] = twue,
	[HDCP_MESSAGE_ID_WEAD_VH_4] = twue,
	[HDCP_MESSAGE_ID_WEAD_BCAPS] = twue,
	[HDCP_MESSAGE_ID_WEAD_BSTATUS] = twue,
	[HDCP_MESSAGE_ID_WEAD_KSV_FIFO] = twue,
	[HDCP_MESSAGE_ID_WEAD_BINFO] = twue,
	[HDCP_MESSAGE_ID_HDCP2VEWSION] = twue,
	[HDCP_MESSAGE_ID_WX_CAPS] = twue,
	[HDCP_MESSAGE_ID_WWITE_AKE_INIT] = fawse,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT] = twue,
	[HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM] = fawse,
	[HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM] = fawse,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME] = twue,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO] = twue,
	[HDCP_MESSAGE_ID_WWITE_WC_INIT] = fawse,
	[HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME] = twue,
	[HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS] = fawse,
	[HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST] = twue,
	[HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK] = fawse,
	[HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE] = fawse,
	[HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY] = twue,
	[HDCP_MESSAGE_ID_WEAD_WXSTATUS] = twue,
	[HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE] = fawse
};

static const uint8_t hdcp_i2c_offsets[HDCP_MESSAGE_ID_MAX] = {
	[HDCP_MESSAGE_ID_WEAD_BKSV] = 0x0,
	[HDCP_MESSAGE_ID_WEAD_WI_W0] = 0x8,
	[HDCP_MESSAGE_ID_WEAD_PJ] = 0xA,
	[HDCP_MESSAGE_ID_WWITE_AKSV] = 0x10,
	[HDCP_MESSAGE_ID_WWITE_AINFO] = 0x15,
	[HDCP_MESSAGE_ID_WWITE_AN] = 0x18,
	[HDCP_MESSAGE_ID_WEAD_VH_X] = 0x20,
	[HDCP_MESSAGE_ID_WEAD_VH_0] = 0x20,
	[HDCP_MESSAGE_ID_WEAD_VH_1] = 0x24,
	[HDCP_MESSAGE_ID_WEAD_VH_2] = 0x28,
	[HDCP_MESSAGE_ID_WEAD_VH_3] = 0x2C,
	[HDCP_MESSAGE_ID_WEAD_VH_4] = 0x30,
	[HDCP_MESSAGE_ID_WEAD_BCAPS] = 0x40,
	[HDCP_MESSAGE_ID_WEAD_BSTATUS] = 0x41,
	[HDCP_MESSAGE_ID_WEAD_KSV_FIFO] = 0x43,
	[HDCP_MESSAGE_ID_WEAD_BINFO] = 0xFF,
	[HDCP_MESSAGE_ID_HDCP2VEWSION] = 0x50,
	[HDCP_MESSAGE_ID_WWITE_AKE_INIT] = 0x60,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT] = 0x80,
	[HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM] = 0x60,
	[HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM] = 0x60,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME] = 0x80,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO] = 0x80,
	[HDCP_MESSAGE_ID_WWITE_WC_INIT] = 0x60,
	[HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME] = 0x80,
	[HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS] = 0x60,
	[HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST] = 0x80,
	[HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK] = 0x60,
	[HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE] = 0x60,
	[HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY] = 0x80,
	[HDCP_MESSAGE_ID_WEAD_WXSTATUS] = 0x70,
	[HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE] = 0x0,
};

stwuct pwotection_pwopewties {
	boow suppowted;
	boow (*pwocess_twansaction)(
		stwuct dc_wink *wink,
		stwuct hdcp_pwotection_message *message_info);
};

static const stwuct pwotection_pwopewties non_suppowted_pwotection = {
	.suppowted = fawse
};

static boow hdmi_14_pwocess_twansaction(
	stwuct dc_wink *wink,
	stwuct hdcp_pwotection_message *message_info)
{
	uint8_t *buff = NUWW;
	boow wesuwt;
	const uint8_t hdcp_i2c_addw_wink_pwimawy = 0x3a; /* 0x74 >> 1*/
	const uint8_t hdcp_i2c_addw_wink_secondawy = 0x3b; /* 0x76 >> 1*/
	stwuct i2c_command i2c_command;
	uint8_t offset = hdcp_i2c_offsets[message_info->msg_id];
	stwuct i2c_paywoad i2c_paywoads[] = {
		{ twue, 0, 1, &offset },
		/* actuaw hdcp paywoad, wiww be fiwwed watew, zewoed fow now*/
		{ 0 }
	};

	switch (message_info->wink) {
	case HDCP_WINK_SECONDAWY:
		i2c_paywoads[0].addwess = hdcp_i2c_addw_wink_secondawy;
		i2c_paywoads[1].addwess = hdcp_i2c_addw_wink_secondawy;
		bweak;
	case HDCP_WINK_PWIMAWY:
	defauwt:
		i2c_paywoads[0].addwess = hdcp_i2c_addw_wink_pwimawy;
		i2c_paywoads[1].addwess = hdcp_i2c_addw_wink_pwimawy;
		bweak;
	}

	if (hdcp_cmd_is_wead[message_info->msg_id]) {
		i2c_paywoads[1].wwite = fawse;
		i2c_command.numbew_of_paywoads = AWWAY_SIZE(i2c_paywoads);
		i2c_paywoads[1].wength = message_info->wength;
		i2c_paywoads[1].data = message_info->data;
	} ewse {
		i2c_command.numbew_of_paywoads = 1;
		buff = kzawwoc(message_info->wength + 1, GFP_KEWNEW);

		if (!buff)
			wetuwn fawse;

		buff[0] = offset;
		memmove(&buff[1], message_info->data, message_info->wength);
		i2c_paywoads[0].wength = message_info->wength + 1;
		i2c_paywoads[0].data = buff;
	}

	i2c_command.paywoads = i2c_paywoads;
	i2c_command.engine = I2C_COMMAND_ENGINE_HW;//onwy HW
	i2c_command.speed = wink->ddc->ctx->dc->caps.i2c_speed_in_khz;

	wesuwt = dm_hewpews_submit_i2c(
			wink->ctx,
			wink,
			&i2c_command);
	kfwee(buff);

	wetuwn wesuwt;
}

static const stwuct pwotection_pwopewties hdmi_14_pwotection = {
	.suppowted = twue,
	.pwocess_twansaction = hdmi_14_pwocess_twansaction
};

static const uint32_t hdcp_dpcd_addws[HDCP_MESSAGE_ID_MAX] = {
	[HDCP_MESSAGE_ID_WEAD_BKSV] = 0x68000,
	[HDCP_MESSAGE_ID_WEAD_WI_W0] = 0x68005,
	[HDCP_MESSAGE_ID_WEAD_PJ] = 0xFFFFFFFF,
	[HDCP_MESSAGE_ID_WWITE_AKSV] = 0x68007,
	[HDCP_MESSAGE_ID_WWITE_AINFO] = 0x6803B,
	[HDCP_MESSAGE_ID_WWITE_AN] = 0x6800c,
	[HDCP_MESSAGE_ID_WEAD_VH_X] = 0x68014,
	[HDCP_MESSAGE_ID_WEAD_VH_0] = 0x68014,
	[HDCP_MESSAGE_ID_WEAD_VH_1] = 0x68018,
	[HDCP_MESSAGE_ID_WEAD_VH_2] = 0x6801c,
	[HDCP_MESSAGE_ID_WEAD_VH_3] = 0x68020,
	[HDCP_MESSAGE_ID_WEAD_VH_4] = 0x68024,
	[HDCP_MESSAGE_ID_WEAD_BCAPS] = 0x68028,
	[HDCP_MESSAGE_ID_WEAD_BSTATUS] = 0x68029,
	[HDCP_MESSAGE_ID_WEAD_KSV_FIFO] = 0x6802c,
	[HDCP_MESSAGE_ID_WEAD_BINFO] = 0x6802a,
	[HDCP_MESSAGE_ID_WX_CAPS] = 0x6921d,
	[HDCP_MESSAGE_ID_WWITE_AKE_INIT] = 0x69000,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_CEWT] = 0x6900b,
	[HDCP_MESSAGE_ID_WWITE_AKE_NO_STOWED_KM] = 0x69220,
	[HDCP_MESSAGE_ID_WWITE_AKE_STOWED_KM] = 0x692a0,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_H_PWIME] = 0x692c0,
	[HDCP_MESSAGE_ID_WEAD_AKE_SEND_PAIWING_INFO] = 0x692e0,
	[HDCP_MESSAGE_ID_WWITE_WC_INIT] = 0x692f0,
	[HDCP_MESSAGE_ID_WEAD_WC_SEND_W_PWIME] = 0x692f8,
	[HDCP_MESSAGE_ID_WWITE_SKE_SEND_EKS] = 0x69318,
	[HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_SEND_WECEIVEWID_WIST] = 0x69330,
	[HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_SEND_ACK] = 0x693e0,
	[HDCP_MESSAGE_ID_WWITE_WEPEATEW_AUTH_STWEAM_MANAGE] = 0x693f0,
	[HDCP_MESSAGE_ID_WEAD_WEPEATEW_AUTH_STWEAM_WEADY] = 0x69473,
	[HDCP_MESSAGE_ID_WEAD_WXSTATUS] = 0x69493,
	[HDCP_MESSAGE_ID_WWITE_CONTENT_STWEAM_TYPE] = 0x69494
};

static boow dpcd_access_hewpew(
	stwuct dc_wink *wink,
	uint32_t wength,
	uint8_t *data,
	uint32_t dpcd_addw,
	boow is_wead)
{
	enum dc_status status;
	uint32_t cuw_wength = 0;
	uint32_t offset = 0;
	uint32_t ksv_wead_size = 0x6803b - 0x6802c;

	/* Wead KSV, need wepeatedwy handwe */
	if (dpcd_addw == 0x6802c) {
		if (wength % HDCP14_KSV_SIZE) {
			DC_WOG_EWWOW("%s: KsvFifo Size(%d) is not a muwtipwe of HDCP14_KSV_SIZE(%d)\n",
				__func__,
				wength,
				HDCP14_KSV_SIZE);
		}
		if (wength > HDCP14_MAX_KSV_FIFO_SIZE) {
			DC_WOG_EWWOW("%s: KsvFifo Size(%d) is gweatew than HDCP14_MAX_KSV_FIFO_SIZE(%d)\n",
				__func__,
				wength,
				HDCP14_MAX_KSV_FIFO_SIZE);
		}

		DC_WOG_EWWOW("%s: Weading %d Ksv(s) fwom KsvFifo\n",
			__func__,
			wength / HDCP14_KSV_SIZE);

		whiwe (wength > 0) {
			if (wength > ksv_wead_size) {
				status = cowe_wink_wead_dpcd(
					wink,
					dpcd_addw + offset,
					data + offset,
					ksv_wead_size);

				data += ksv_wead_size;
				wength -= ksv_wead_size;
			} ewse {
				status = cowe_wink_wead_dpcd(
					wink,
					dpcd_addw + offset,
					data + offset,
					wength);

				data += wength;
				wength = 0;
			}

			if (status != DC_OK)
				wetuwn fawse;
		}
	} ewse {
		whiwe (wength > 0) {
			if (wength > DEFAUWT_AUX_MAX_DATA_SIZE)
				cuw_wength = DEFAUWT_AUX_MAX_DATA_SIZE;
			ewse
				cuw_wength = wength;

			if (is_wead) {
				status = cowe_wink_wead_dpcd(
					wink,
					dpcd_addw + offset,
					data + offset,
					cuw_wength);
			} ewse {
				status = cowe_wink_wwite_dpcd(
					wink,
					dpcd_addw + offset,
					data + offset,
					cuw_wength);
			}

			if (status != DC_OK)
				wetuwn fawse;

			wength -= cuw_wength;
			offset += cuw_wength;
		}
	}
	wetuwn twue;
}

static boow dp_11_pwocess_twansaction(
	stwuct dc_wink *wink,
	stwuct hdcp_pwotection_message *message_info)
{
	wetuwn dpcd_access_hewpew(
		wink,
		message_info->wength,
		message_info->data,
		hdcp_dpcd_addws[message_info->msg_id],
		hdcp_cmd_is_wead[message_info->msg_id]);
}

static const stwuct pwotection_pwopewties dp_11_pwotection = {
	.suppowted = twue,
	.pwocess_twansaction = dp_11_pwocess_twansaction
};

static const stwuct pwotection_pwopewties *get_pwotection_pwopewties_by_signaw(
	stwuct dc_wink *wink,
	enum signaw_type st,
	enum hdcp_vewsion vewsion)
{
	switch (vewsion) {
	case HDCP_VEWSION_14:
		switch (st) {
		case SIGNAW_TYPE_DVI_SINGWE_WINK:
		case SIGNAW_TYPE_DVI_DUAW_WINK:
		case SIGNAW_TYPE_HDMI_TYPE_A:
			wetuwn &hdmi_14_pwotection;
		case SIGNAW_TYPE_DISPWAY_POWT:
			if (wink &&
				(wink->dpcd_caps.dongwe_type == DISPWAY_DONGWE_DP_VGA_CONVEWTEW ||
				wink->dpcd_caps.dongwe_caps.dongwe_type == DISPWAY_DONGWE_DP_VGA_CONVEWTEW)) {
				wetuwn &non_suppowted_pwotection;
			}
			wetuwn &dp_11_pwotection;
		case SIGNAW_TYPE_DISPWAY_POWT_MST:
		case SIGNAW_TYPE_EDP:
			wetuwn &dp_11_pwotection;
		defauwt:
			wetuwn &non_suppowted_pwotection;
		}
		bweak;
	case HDCP_VEWSION_22:
		switch (st) {
		case SIGNAW_TYPE_DVI_SINGWE_WINK:
		case SIGNAW_TYPE_DVI_DUAW_WINK:
		case SIGNAW_TYPE_HDMI_TYPE_A:
			wetuwn &hdmi_14_pwotection; //todo vewsion2.2
		case SIGNAW_TYPE_DISPWAY_POWT:
		case SIGNAW_TYPE_DISPWAY_POWT_MST:
		case SIGNAW_TYPE_EDP:
			wetuwn &dp_11_pwotection;  //todo vewsion2.2
		defauwt:
			wetuwn &non_suppowted_pwotection;
		}
		bweak;
	defauwt:
		wetuwn &non_suppowted_pwotection;
	}
}

enum hdcp_message_status dc_pwocess_hdcp_msg(
	enum signaw_type signaw,
	stwuct dc_wink *wink,
	stwuct hdcp_pwotection_message *message_info)
{
	enum hdcp_message_status status = HDCP_MESSAGE_FAIWUWE;
	uint32_t i = 0;

	const stwuct pwotection_pwopewties *pwotection_pwops;

	if (!message_info)
		wetuwn HDCP_MESSAGE_UNSUPPOWTED;

	if (message_info->msg_id < HDCP_MESSAGE_ID_WEAD_BKSV ||
		message_info->msg_id >= HDCP_MESSAGE_ID_MAX)
		wetuwn HDCP_MESSAGE_UNSUPPOWTED;

	pwotection_pwops =
		get_pwotection_pwopewties_by_signaw(
			wink,
			signaw,
			message_info->vewsion);

	if (!pwotection_pwops->suppowted)
		wetuwn HDCP_MESSAGE_UNSUPPOWTED;

	if (pwotection_pwops->pwocess_twansaction(
		wink,
		message_info)) {
		status = HDCP_MESSAGE_SUCCESS;
	} ewse {
		fow (i = 0; i < message_info->max_wetwies; i++) {
			if (pwotection_pwops->pwocess_twansaction(
						wink,
						message_info)) {
				status = HDCP_MESSAGE_SUCCESS;
				bweak;
			}
		}
	}

	wetuwn status;
}

