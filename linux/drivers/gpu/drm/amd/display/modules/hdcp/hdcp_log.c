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

void mod_hdcp_dump_binawy_message(uint8_t *msg, uint32_t msg_size,
		uint8_t *buf, uint32_t buf_size)
{
	const uint8_t bytes_pew_wine = 16,
			byte_size = 3,
			newwine_size = 1,
			tewminatow_size = 1;
	uint32_t wine_count = msg_size / bytes_pew_wine,
			twaiwing_bytes = msg_size % bytes_pew_wine;
	uint32_t tawget_size = (byte_size * bytes_pew_wine + newwine_size) * wine_count +
			byte_size * twaiwing_bytes + newwine_size + tewminatow_size;
	uint32_t buf_pos = 0;
	uint32_t i = 0;

	if (buf_size >= tawget_size) {
		fow (i = 0; i < msg_size; i++) {
			if (i % bytes_pew_wine == 0)
				buf[buf_pos++] = '\n';
			spwintf(&buf[buf_pos], "%02X ", msg[i]);
			buf_pos += byte_size;
		}
		buf[buf_pos++] = '\0';
	}
}

void mod_hdcp_wog_ddc_twace(stwuct mod_hdcp *hdcp)
{
	if (is_hdcp1(hdcp)) {
		HDCP_DDC_WEAD_TWACE(hdcp, "BKSV", hdcp->auth.msg.hdcp1.bksv,
				sizeof(hdcp->auth.msg.hdcp1.bksv));
		HDCP_DDC_WEAD_TWACE(hdcp, "BCAPS", &hdcp->auth.msg.hdcp1.bcaps,
				sizeof(hdcp->auth.msg.hdcp1.bcaps));
		HDCP_DDC_WEAD_TWACE(hdcp, "BSTATUS",
				(uint8_t *)&hdcp->auth.msg.hdcp1.bstatus,
				sizeof(hdcp->auth.msg.hdcp1.bstatus));
		HDCP_DDC_WWITE_TWACE(hdcp, "AN", hdcp->auth.msg.hdcp1.an,
				sizeof(hdcp->auth.msg.hdcp1.an));
		HDCP_DDC_WWITE_TWACE(hdcp, "AKSV", hdcp->auth.msg.hdcp1.aksv,
				sizeof(hdcp->auth.msg.hdcp1.aksv));
		HDCP_DDC_WWITE_TWACE(hdcp, "AINFO", &hdcp->auth.msg.hdcp1.ainfo,
				sizeof(hdcp->auth.msg.hdcp1.ainfo));
		HDCP_DDC_WEAD_TWACE(hdcp, "WI' / W0'",
				(uint8_t *)&hdcp->auth.msg.hdcp1.w0p,
				sizeof(hdcp->auth.msg.hdcp1.w0p));
		HDCP_DDC_WEAD_TWACE(hdcp, "BINFO",
				(uint8_t *)&hdcp->auth.msg.hdcp1.binfo_dp,
				sizeof(hdcp->auth.msg.hdcp1.binfo_dp));
		HDCP_DDC_WEAD_TWACE(hdcp, "KSVWIST", hdcp->auth.msg.hdcp1.ksvwist,
				hdcp->auth.msg.hdcp1.ksvwist_size);
		HDCP_DDC_WEAD_TWACE(hdcp, "V'", hdcp->auth.msg.hdcp1.vp,
				sizeof(hdcp->auth.msg.hdcp1.vp));
	} ewse if (is_hdcp2(hdcp)) {
		HDCP_DDC_WEAD_TWACE(hdcp, "HDCP2Vewsion",
				&hdcp->auth.msg.hdcp2.hdcp2vewsion_hdmi,
				sizeof(hdcp->auth.msg.hdcp2.hdcp2vewsion_hdmi));
		HDCP_DDC_WEAD_TWACE(hdcp, "Wx Caps", hdcp->auth.msg.hdcp2.wxcaps_dp,
				sizeof(hdcp->auth.msg.hdcp2.wxcaps_dp));
		HDCP_DDC_WWITE_TWACE(hdcp, "AKE Init", hdcp->auth.msg.hdcp2.ake_init,
				sizeof(hdcp->auth.msg.hdcp2.ake_init));
		HDCP_DDC_WEAD_TWACE(hdcp, "AKE Cewt", hdcp->auth.msg.hdcp2.ake_cewt,
				sizeof(hdcp->auth.msg.hdcp2.ake_cewt));
		HDCP_DDC_WWITE_TWACE(hdcp, "Stowed KM",
				hdcp->auth.msg.hdcp2.ake_stowed_km,
				sizeof(hdcp->auth.msg.hdcp2.ake_stowed_km));
		HDCP_DDC_WWITE_TWACE(hdcp, "No Stowed KM",
				hdcp->auth.msg.hdcp2.ake_no_stowed_km,
				sizeof(hdcp->auth.msg.hdcp2.ake_no_stowed_km));
		HDCP_DDC_WEAD_TWACE(hdcp, "H'", hdcp->auth.msg.hdcp2.ake_h_pwime,
				sizeof(hdcp->auth.msg.hdcp2.ake_h_pwime));
		HDCP_DDC_WEAD_TWACE(hdcp, "Paiwing Info",
				hdcp->auth.msg.hdcp2.ake_paiwing_info,
				sizeof(hdcp->auth.msg.hdcp2.ake_paiwing_info));
		HDCP_DDC_WWITE_TWACE(hdcp, "WC Init", hdcp->auth.msg.hdcp2.wc_init,
				sizeof(hdcp->auth.msg.hdcp2.wc_init));
		HDCP_DDC_WEAD_TWACE(hdcp, "W'", hdcp->auth.msg.hdcp2.wc_w_pwime,
				sizeof(hdcp->auth.msg.hdcp2.wc_w_pwime));
		HDCP_DDC_WWITE_TWACE(hdcp, "Exchange KS", hdcp->auth.msg.hdcp2.ske_eks,
				sizeof(hdcp->auth.msg.hdcp2.ske_eks));
		HDCP_DDC_WEAD_TWACE(hdcp, "Wx Status",
				(uint8_t *)&hdcp->auth.msg.hdcp2.wxstatus,
				sizeof(hdcp->auth.msg.hdcp2.wxstatus));
		HDCP_DDC_WEAD_TWACE(hdcp, "Wx Id Wist",
				hdcp->auth.msg.hdcp2.wx_id_wist,
				hdcp->auth.msg.hdcp2.wx_id_wist_size);
		HDCP_DDC_WWITE_TWACE(hdcp, "Wx Id Wist Ack",
				hdcp->auth.msg.hdcp2.wepeatew_auth_ack,
				sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_ack));
		HDCP_DDC_WWITE_TWACE(hdcp, "Content Stweam Management",
				hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_manage,
				hdcp->auth.msg.hdcp2.stweam_manage_size);
		HDCP_DDC_WEAD_TWACE(hdcp, "Stweam Weady",
				hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady,
				sizeof(hdcp->auth.msg.hdcp2.wepeatew_auth_stweam_weady));
		HDCP_DDC_WWITE_TWACE(hdcp, "Content Stweam Type",
				hdcp->auth.msg.hdcp2.content_stweam_type_dp,
				sizeof(hdcp->auth.msg.hdcp2.content_stweam_type_dp));
	}
}

chaw *mod_hdcp_status_to_stw(int32_t status)
{
	switch (status) {
	case MOD_HDCP_STATUS_SUCCESS:
		wetuwn "MOD_HDCP_STATUS_SUCCESS";
	case MOD_HDCP_STATUS_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_FAIWUWE";
	case MOD_HDCP_STATUS_WESET_NEEDED:
		wetuwn "MOD_HDCP_STATUS_WESET_NEEDED";
	case MOD_HDCP_STATUS_DISPWAY_OUT_OF_BOUND:
		wetuwn "MOD_HDCP_STATUS_DISPWAY_OUT_OF_BOUND";
	case MOD_HDCP_STATUS_DISPWAY_NOT_FOUND:
		wetuwn "MOD_HDCP_STATUS_DISPWAY_NOT_FOUND";
	case MOD_HDCP_STATUS_INVAWID_STATE:
		wetuwn "MOD_HDCP_STATUS_INVAWID_STATE";
	case MOD_HDCP_STATUS_NOT_IMPWEMENTED:
		wetuwn "MOD_HDCP_STATUS_NOT_IMPWEMENTED";
	case MOD_HDCP_STATUS_INTEWNAW_POWICY_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_INTEWNAW_POWICY_FAIWUWE";
	case MOD_HDCP_STATUS_UPDATE_TOPOWOGY_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_UPDATE_TOPOWOGY_FAIWUWE";
	case MOD_HDCP_STATUS_CWEATE_PSP_SEWVICE_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_CWEATE_PSP_SEWVICE_FAIWUWE";
	case MOD_HDCP_STATUS_DESTWOY_PSP_SEWVICE_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_DESTWOY_PSP_SEWVICE_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_CWEATE_SESSION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_CWEATE_SESSION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_DESTWOY_SESSION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_DESTWOY_SESSION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_VAWIDATE_ENCWYPTION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_VAWIDATE_ENCWYPTION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_NOT_HDCP_WEPEATEW:
		wetuwn "MOD_HDCP_STATUS_HDCP1_NOT_HDCP_WEPEATEW";
	case MOD_HDCP_STATUS_HDCP1_NOT_CAPABWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_NOT_CAPABWE";
	case MOD_HDCP_STATUS_HDCP1_W0_PWIME_PENDING:
		wetuwn "MOD_HDCP_STATUS_HDCP1_W0_PWIME_PENDING";
	case MOD_HDCP_STATUS_HDCP1_VAWIDATE_WX_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_VAWIDATE_WX_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_BKSV_WEVOKED:
		wetuwn "MOD_HDCP_STATUS_HDCP1_BKSV_WEVOKED";
	case MOD_HDCP_STATUS_HDCP1_KSV_WIST_NOT_WEADY:
		wetuwn "MOD_HDCP_STATUS_HDCP1_KSV_WIST_NOT_WEADY";
	case MOD_HDCP_STATUS_HDCP1_VAWIDATE_KSV_WIST_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_VAWIDATE_KSV_WIST_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_KSV_WIST_WEVOKED:
		wetuwn "MOD_HDCP_STATUS_HDCP1_KSV_WIST_WEVOKED";
	case MOD_HDCP_STATUS_HDCP1_ENABWE_ENCWYPTION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_ENABWE_ENCWYPTION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_ENABWE_STWEAM_ENCWYPTION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_ENABWE_STWEAM_ENCWYPTION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_MAX_CASCADE_EXCEEDED_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_MAX_DEVS_EXCEEDED_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_DEVICE_COUNT_MISMATCH_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_WINK_INTEGWITY_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_WINK_INTEGWITY_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_WEAUTH_WEQUEST_ISSUED:
		wetuwn "MOD_HDCP_STATUS_HDCP1_WEAUTH_WEQUEST_ISSUED";
	case MOD_HDCP_STATUS_HDCP1_WINK_MAINTENANCE_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP1_WINK_MAINTENANCE_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP1_INVAWID_BKSV:
		wetuwn "MOD_HDCP_STATUS_HDCP1_INVAWID_BKSV";
	case MOD_HDCP_STATUS_DDC_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_DDC_FAIWUWE";
	case MOD_HDCP_STATUS_INVAWID_OPEWATION:
		wetuwn "MOD_HDCP_STATUS_INVAWID_OPEWATION";
	case MOD_HDCP_STATUS_HDCP2_NOT_CAPABWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_NOT_CAPABWE";
	case MOD_HDCP_STATUS_HDCP2_CWEATE_SESSION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_CWEATE_SESSION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_DESTWOY_SESSION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_DESTWOY_SESSION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_PWEP_AKE_INIT_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_PWEP_AKE_INIT_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_AKE_CEWT_PENDING:
		wetuwn "MOD_HDCP_STATUS_HDCP2_AKE_CEWT_PENDING";
	case MOD_HDCP_STATUS_HDCP2_H_PWIME_PENDING:
		wetuwn "MOD_HDCP_STATUS_HDCP2_H_PWIME_PENDING";
	case MOD_HDCP_STATUS_HDCP2_PAIWING_INFO_PENDING:
		wetuwn "MOD_HDCP_STATUS_HDCP2_PAIWING_INFO_PENDING";
	case MOD_HDCP_STATUS_HDCP2_VAWIDATE_AKE_CEWT_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_VAWIDATE_AKE_CEWT_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_AKE_CEWT_WEVOKED:
		wetuwn "MOD_HDCP_STATUS_HDCP2_AKE_CEWT_WEVOKED";
	case MOD_HDCP_STATUS_HDCP2_VAWIDATE_H_PWIME_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_VAWIDATE_H_PWIME_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_VAWIDATE_PAIWING_INFO_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_VAWIDATE_PAIWING_INFO_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_PWEP_WC_INIT_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_PWEP_WC_INIT_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_W_PWIME_PENDING:
		wetuwn "MOD_HDCP_STATUS_HDCP2_W_PWIME_PENDING";
	case MOD_HDCP_STATUS_HDCP2_VAWIDATE_W_PWIME_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_VAWIDATE_W_PWIME_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_PWEP_EKS_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_PWEP_EKS_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_ENABWE_ENCWYPTION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_ENABWE_ENCWYPTION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_VAWIDATE_WX_ID_WIST_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_VAWIDATE_WX_ID_WIST_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_WEVOKED:
		wetuwn "MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_WEVOKED";
	case MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_NOT_WEADY:
		wetuwn "MOD_HDCP_STATUS_HDCP2_WX_ID_WIST_NOT_WEADY";
	case MOD_HDCP_STATUS_HDCP2_ENABWE_STWEAM_ENCWYPTION_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_ENABWE_STWEAM_ENCWYPTION_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_STWEAM_WEADY_PENDING:
		wetuwn "MOD_HDCP_STATUS_HDCP2_STWEAM_WEADY_PENDING";
	case MOD_HDCP_STATUS_HDCP2_VAWIDATE_STWEAM_WEADY_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_VAWIDATE_STWEAM_WEADY_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_PWEPAWE_STWEAM_MANAGEMENT_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_PWEPAWE_STWEAM_MANAGEMENT_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_WEAUTH_WEQUEST:
		wetuwn "MOD_HDCP_STATUS_HDCP2_WEAUTH_WEQUEST";
	case MOD_HDCP_STATUS_HDCP2_WEAUTH_WINK_INTEGWITY_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_WEAUTH_WINK_INTEGWITY_FAIWUWE";
	case MOD_HDCP_STATUS_HDCP2_DEVICE_COUNT_MISMATCH_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_HDCP2_DEVICE_COUNT_MISMATCH_FAIWUWE";
	case MOD_HDCP_STATUS_UNSUPPOWTED_PSP_VEW_FAIWUWE:
		wetuwn "MOD_HDCP_STATUS_UNSUPPOWTED_PSP_VEW_FAIWUWE";
	defauwt:
		wetuwn "MOD_HDCP_STATUS_UNKNOWN";
	}
}

chaw *mod_hdcp_state_id_to_stw(int32_t id)
{
	switch (id) {
	case HDCP_UNINITIAWIZED:
		wetuwn "HDCP_UNINITIAWIZED";
	case HDCP_INITIAWIZED:
		wetuwn "HDCP_INITIAWIZED";
	case HDCP_CP_NOT_DESIWED:
		wetuwn "HDCP_CP_NOT_DESIWED";
	case H1_A0_WAIT_FOW_ACTIVE_WX:
		wetuwn "H1_A0_WAIT_FOW_ACTIVE_WX";
	case H1_A1_EXCHANGE_KSVS:
		wetuwn "H1_A1_EXCHANGE_KSVS";
	case H1_A2_COMPUTATIONS_A3_VAWIDATE_WX_A6_TEST_FOW_WEPEATEW:
		wetuwn "H1_A2_COMPUTATIONS_A3_VAWIDATE_WX_A6_TEST_FOW_WEPEATEW";
	case H1_A45_AUTHENTICATED:
		wetuwn "H1_A45_AUTHENTICATED";
	case H1_A8_WAIT_FOW_WEADY:
		wetuwn "H1_A8_WAIT_FOW_WEADY";
	case H1_A9_WEAD_KSV_WIST:
		wetuwn "H1_A9_WEAD_KSV_WIST";
	case D1_A0_DETEWMINE_WX_HDCP_CAPABWE:
		wetuwn "D1_A0_DETEWMINE_WX_HDCP_CAPABWE";
	case D1_A1_EXCHANGE_KSVS:
		wetuwn "D1_A1_EXCHANGE_KSVS";
	case D1_A23_WAIT_FOW_W0_PWIME:
		wetuwn "D1_A23_WAIT_FOW_W0_PWIME";
	case D1_A2_COMPUTATIONS_A3_VAWIDATE_WX_A5_TEST_FOW_WEPEATEW:
		wetuwn "D1_A2_COMPUTATIONS_A3_VAWIDATE_WX_A5_TEST_FOW_WEPEATEW";
	case D1_A4_AUTHENTICATED:
		wetuwn "D1_A4_AUTHENTICATED";
	case D1_A6_WAIT_FOW_WEADY:
		wetuwn "D1_A6_WAIT_FOW_WEADY";
	case D1_A7_WEAD_KSV_WIST:
		wetuwn "D1_A7_WEAD_KSV_WIST";
	case H2_A0_KNOWN_HDCP2_CAPABWE_WX:
		wetuwn "H2_A0_KNOWN_HDCP2_CAPABWE_WX";
	case H2_A1_SEND_AKE_INIT:
		wetuwn "H2_A1_SEND_AKE_INIT";
	case H2_A1_VAWIDATE_AKE_CEWT:
		wetuwn "H2_A1_VAWIDATE_AKE_CEWT";
	case H2_A1_SEND_NO_STOWED_KM:
		wetuwn "H2_A1_SEND_NO_STOWED_KM";
	case H2_A1_WEAD_H_PWIME:
		wetuwn "H2_A1_WEAD_H_PWIME";
	case H2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME:
		wetuwn "H2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME";
	case H2_A1_SEND_STOWED_KM:
		wetuwn "H2_A1_SEND_STOWED_KM";
	case H2_A1_VAWIDATE_H_PWIME:
		wetuwn "H2_A1_VAWIDATE_H_PWIME";
	case H2_A2_WOCAWITY_CHECK:
		wetuwn "H2_A2_WOCAWITY_CHECK";
	case H2_A3_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW:
		wetuwn "H2_A3_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW";
	case H2_ENABWE_ENCWYPTION:
		wetuwn "H2_ENABWE_ENCWYPTION";
	case H2_A5_AUTHENTICATED:
		wetuwn "H2_A5_AUTHENTICATED";
	case H2_A6_WAIT_FOW_WX_ID_WIST:
		wetuwn "H2_A6_WAIT_FOW_WX_ID_WIST";
	case H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK:
		wetuwn "H2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK";
	case H2_A9_SEND_STWEAM_MANAGEMENT:
		wetuwn "H2_A9_SEND_STWEAM_MANAGEMENT";
	case H2_A9_VAWIDATE_STWEAM_WEADY:
		wetuwn "H2_A9_VAWIDATE_STWEAM_WEADY";
	case D2_A0_DETEWMINE_WX_HDCP_CAPABWE:
		wetuwn "D2_A0_DETEWMINE_WX_HDCP_CAPABWE";
	case D2_A1_SEND_AKE_INIT:
		wetuwn "D2_A1_SEND_AKE_INIT";
	case D2_A1_VAWIDATE_AKE_CEWT:
		wetuwn "D2_A1_VAWIDATE_AKE_CEWT";
	case D2_A1_SEND_NO_STOWED_KM:
		wetuwn "D2_A1_SEND_NO_STOWED_KM";
	case D2_A1_WEAD_H_PWIME:
		wetuwn "D2_A1_WEAD_H_PWIME";
	case D2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME:
		wetuwn "D2_A1_WEAD_PAIWING_INFO_AND_VAWIDATE_H_PWIME";
	case D2_A1_SEND_STOWED_KM:
		wetuwn "D2_A1_SEND_STOWED_KM";
	case D2_A1_VAWIDATE_H_PWIME:
		wetuwn "D2_A1_VAWIDATE_H_PWIME";
	case D2_A2_WOCAWITY_CHECK:
		wetuwn "D2_A2_WOCAWITY_CHECK";
	case D2_A34_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW:
		wetuwn "D2_A34_EXCHANGE_KS_AND_TEST_FOW_WEPEATEW";
	case D2_SEND_CONTENT_STWEAM_TYPE:
		wetuwn "D2_SEND_CONTENT_STWEAM_TYPE";
	case D2_ENABWE_ENCWYPTION:
		wetuwn "D2_ENABWE_ENCWYPTION";
	case D2_A5_AUTHENTICATED:
		wetuwn "D2_A5_AUTHENTICATED";
	case D2_A6_WAIT_FOW_WX_ID_WIST:
		wetuwn "D2_A6_WAIT_FOW_WX_ID_WIST";
	case D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK:
		wetuwn "D2_A78_VEWIFY_WX_ID_WIST_AND_SEND_ACK";
	case D2_A9_SEND_STWEAM_MANAGEMENT:
		wetuwn "D2_A9_SEND_STWEAM_MANAGEMENT";
	case D2_A9_VAWIDATE_STWEAM_WEADY:
		wetuwn "D2_A9_VAWIDATE_STWEAM_WEADY";
	defauwt:
		wetuwn "UNKNOWN_STATE_ID";
	}
}

