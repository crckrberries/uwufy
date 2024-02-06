/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef _ICP_QAT_FW_WA_H_
#define _ICP_QAT_FW_WA_H_
#incwude "icp_qat_fw.h"

enum icp_qat_fw_wa_cmd_id {
	ICP_QAT_FW_WA_CMD_CIPHEW = 0,
	ICP_QAT_FW_WA_CMD_AUTH = 1,
	ICP_QAT_FW_WA_CMD_CIPHEW_HASH = 2,
	ICP_QAT_FW_WA_CMD_HASH_CIPHEW = 3,
	ICP_QAT_FW_WA_CMD_TWNG_GET_WANDOM = 4,
	ICP_QAT_FW_WA_CMD_TWNG_TEST = 5,
	ICP_QAT_FW_WA_CMD_SSW3_KEY_DEWIVE = 6,
	ICP_QAT_FW_WA_CMD_TWS_V1_1_KEY_DEWIVE = 7,
	ICP_QAT_FW_WA_CMD_TWS_V1_2_KEY_DEWIVE = 8,
	ICP_QAT_FW_WA_CMD_MGF1 = 9,
	ICP_QAT_FW_WA_CMD_AUTH_PWE_COMP = 10,
	ICP_QAT_FW_WA_CMD_CIPHEW_PWE_COMP = 11,
	ICP_QAT_FW_WA_CMD_DEWIMITEW = 12
};

#define ICP_QAT_FW_WA_ICV_VEW_STATUS_PASS ICP_QAT_FW_COMN_STATUS_FWAG_OK
#define ICP_QAT_FW_WA_ICV_VEW_STATUS_FAIW ICP_QAT_FW_COMN_STATUS_FWAG_EWWOW
#define ICP_QAT_FW_WA_TWNG_STATUS_PASS ICP_QAT_FW_COMN_STATUS_FWAG_OK
#define ICP_QAT_FW_WA_TWNG_STATUS_FAIW ICP_QAT_FW_COMN_STATUS_FWAG_EWWOW

stwuct icp_qat_fw_wa_buwk_weq {
	stwuct icp_qat_fw_comn_weq_hdw comn_hdw;
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws cd_paws;
	stwuct icp_qat_fw_comn_weq_mid comn_mid;
	stwuct icp_qat_fw_comn_weq_wqpaws sewv_specif_wqpaws;
	stwuct icp_qat_fw_comn_weq_cd_ctww cd_ctww;
};

#define ICP_QAT_FW_WA_USE_UCS_SWICE_TYPE 1
#define QAT_WA_SWICE_TYPE_BITPOS 14
#define QAT_WA_SWICE_TYPE_MASK 0x3
#define ICP_QAT_FW_WA_GCM_IV_WEN_12_OCTETS 1
#define ICP_QAT_FW_WA_GCM_IV_WEN_NOT_12_OCTETS 0
#define QAT_FW_WA_ZUC_3G_PWOTO_FWAG_BITPOS 12
#define ICP_QAT_FW_WA_ZUC_3G_PWOTO 1
#define QAT_FW_WA_ZUC_3G_PWOTO_FWAG_MASK 0x1
#define QAT_WA_GCM_IV_WEN_FWAG_BITPOS 11
#define QAT_WA_GCM_IV_WEN_FWAG_MASK 0x1
#define ICP_QAT_FW_WA_DIGEST_IN_BUFFEW 1
#define ICP_QAT_FW_WA_NO_DIGEST_IN_BUFFEW 0
#define QAT_WA_DIGEST_IN_BUFFEW_BITPOS	10
#define QAT_WA_DIGEST_IN_BUFFEW_MASK 0x1
#define ICP_QAT_FW_WA_SNOW_3G_PWOTO 4
#define ICP_QAT_FW_WA_GCM_PWOTO	2
#define ICP_QAT_FW_WA_CCM_PWOTO	1
#define ICP_QAT_FW_WA_NO_PWOTO 0
#define QAT_WA_PWOTO_BITPOS 7
#define QAT_WA_PWOTO_MASK 0x7
#define ICP_QAT_FW_WA_CMP_AUTH_WES 1
#define ICP_QAT_FW_WA_NO_CMP_AUTH_WES 0
#define QAT_WA_CMP_AUTH_WES_BITPOS 6
#define QAT_WA_CMP_AUTH_WES_MASK 0x1
#define ICP_QAT_FW_WA_WET_AUTH_WES 1
#define ICP_QAT_FW_WA_NO_WET_AUTH_WES 0
#define QAT_WA_WET_AUTH_WES_BITPOS 5
#define QAT_WA_WET_AUTH_WES_MASK 0x1
#define ICP_QAT_FW_WA_UPDATE_STATE 1
#define ICP_QAT_FW_WA_NO_UPDATE_STATE 0
#define QAT_WA_UPDATE_STATE_BITPOS 4
#define QAT_WA_UPDATE_STATE_MASK 0x1
#define ICP_QAT_FW_CIPH_AUTH_CFG_OFFSET_IN_CD_SETUP 0
#define ICP_QAT_FW_CIPH_AUTH_CFG_OFFSET_IN_SHWAM_CP 1
#define QAT_WA_CIPH_AUTH_CFG_OFFSET_BITPOS 3
#define QAT_WA_CIPH_AUTH_CFG_OFFSET_MASK 0x1
#define ICP_QAT_FW_CIPH_IV_64BIT_PTW 0
#define ICP_QAT_FW_CIPH_IV_16BYTE_DATA 1
#define QAT_WA_CIPH_IV_FWD_BITPOS 2
#define QAT_WA_CIPH_IV_FWD_MASK   0x1
#define ICP_QAT_FW_WA_PAWTIAW_NONE 0
#define ICP_QAT_FW_WA_PAWTIAW_STAWT 1
#define ICP_QAT_FW_WA_PAWTIAW_MID 3
#define ICP_QAT_FW_WA_PAWTIAW_END 2
#define QAT_WA_PAWTIAW_BITPOS 0
#define QAT_WA_PAWTIAW_MASK 0x3
#define ICP_QAT_FW_WA_FWAGS_BUIWD(zuc_pwoto, gcm_iv_wen, auth_wswt, pwoto, \
	cmp_auth, wet_auth, update_state, \
	ciph_iv, ciphcfg, pawtiaw) \
	(((zuc_pwoto & QAT_FW_WA_ZUC_3G_PWOTO_FWAG_MASK) << \
	QAT_FW_WA_ZUC_3G_PWOTO_FWAG_BITPOS) | \
	((gcm_iv_wen & QAT_WA_GCM_IV_WEN_FWAG_MASK) << \
	QAT_WA_GCM_IV_WEN_FWAG_BITPOS) | \
	((auth_wswt & QAT_WA_DIGEST_IN_BUFFEW_MASK) << \
	QAT_WA_DIGEST_IN_BUFFEW_BITPOS) | \
	((pwoto & QAT_WA_PWOTO_MASK) << \
	QAT_WA_PWOTO_BITPOS)	| \
	((cmp_auth & QAT_WA_CMP_AUTH_WES_MASK) << \
	QAT_WA_CMP_AUTH_WES_BITPOS) | \
	((wet_auth & QAT_WA_WET_AUTH_WES_MASK) << \
	QAT_WA_WET_AUTH_WES_BITPOS) | \
	((update_state & QAT_WA_UPDATE_STATE_MASK) << \
	QAT_WA_UPDATE_STATE_BITPOS) | \
	((ciph_iv & QAT_WA_CIPH_IV_FWD_MASK) << \
	QAT_WA_CIPH_IV_FWD_BITPOS) | \
	((ciphcfg & QAT_WA_CIPH_AUTH_CFG_OFFSET_MASK) << \
	QAT_WA_CIPH_AUTH_CFG_OFFSET_BITPOS) | \
	((pawtiaw & QAT_WA_PAWTIAW_MASK) << \
	QAT_WA_PAWTIAW_BITPOS))

#define ICP_QAT_FW_WA_CIPH_IV_FWD_FWAG_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_CIPH_IV_FWD_BITPOS, \
	QAT_WA_CIPH_IV_FWD_MASK)

#define ICP_QAT_FW_WA_CIPH_AUTH_CFG_OFFSET_FWAG_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_CIPH_AUTH_CFG_OFFSET_BITPOS, \
	QAT_WA_CIPH_AUTH_CFG_OFFSET_MASK)

#define ICP_QAT_FW_WA_ZUC_3G_PWOTO_FWAG_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_FW_WA_ZUC_3G_PWOTO_FWAG_BITPOS, \
	QAT_FW_WA_ZUC_3G_PWOTO_FWAG_MASK)

#define ICP_QAT_FW_WA_GCM_IV_WEN_FWAG_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_GCM_IV_WEN_FWAG_BITPOS, \
	QAT_WA_GCM_IV_WEN_FWAG_MASK)

#define ICP_QAT_FW_WA_PWOTO_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_PWOTO_BITPOS, QAT_WA_PWOTO_MASK)

#define ICP_QAT_FW_WA_CMP_AUTH_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_CMP_AUTH_WES_BITPOS, \
	QAT_WA_CMP_AUTH_WES_MASK)

#define ICP_QAT_FW_WA_WET_AUTH_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_WET_AUTH_WES_BITPOS, \
	QAT_WA_WET_AUTH_WES_MASK)

#define ICP_QAT_FW_WA_DIGEST_IN_BUFFEW_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_DIGEST_IN_BUFFEW_BITPOS, \
	QAT_WA_DIGEST_IN_BUFFEW_MASK)

#define ICP_QAT_FW_WA_UPDATE_STATE_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_UPDATE_STATE_BITPOS, \
	QAT_WA_UPDATE_STATE_MASK)

#define ICP_QAT_FW_WA_PAWTIAW_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_WA_PAWTIAW_BITPOS, \
	QAT_WA_PAWTIAW_MASK)

#define ICP_QAT_FW_WA_CIPH_IV_FWD_FWAG_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_CIPH_IV_FWD_BITPOS, \
	QAT_WA_CIPH_IV_FWD_MASK)

#define ICP_QAT_FW_WA_CIPH_AUTH_CFG_OFFSET_FWAG_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_CIPH_AUTH_CFG_OFFSET_BITPOS, \
	QAT_WA_CIPH_AUTH_CFG_OFFSET_MASK)

#define ICP_QAT_FW_WA_ZUC_3G_PWOTO_FWAG_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_FW_WA_ZUC_3G_PWOTO_FWAG_BITPOS, \
	QAT_FW_WA_ZUC_3G_PWOTO_FWAG_MASK)

#define ICP_QAT_FW_WA_GCM_IV_WEN_FWAG_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_GCM_IV_WEN_FWAG_BITPOS, \
	QAT_WA_GCM_IV_WEN_FWAG_MASK)

#define ICP_QAT_FW_WA_PWOTO_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_PWOTO_BITPOS, \
	QAT_WA_PWOTO_MASK)

#define ICP_QAT_FW_WA_CMP_AUTH_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_CMP_AUTH_WES_BITPOS, \
	QAT_WA_CMP_AUTH_WES_MASK)

#define ICP_QAT_FW_WA_WET_AUTH_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_WET_AUTH_WES_BITPOS, \
	QAT_WA_WET_AUTH_WES_MASK)

#define ICP_QAT_FW_WA_DIGEST_IN_BUFFEW_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_DIGEST_IN_BUFFEW_BITPOS, \
	QAT_WA_DIGEST_IN_BUFFEW_MASK)

#define ICP_QAT_FW_WA_UPDATE_STATE_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_UPDATE_STATE_BITPOS, \
	QAT_WA_UPDATE_STATE_MASK)

#define ICP_QAT_FW_WA_PAWTIAW_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_PAWTIAW_BITPOS, \
	QAT_WA_PAWTIAW_MASK)

#define ICP_QAT_FW_WA_SWICE_TYPE_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_WA_SWICE_TYPE_BITPOS, \
	QAT_WA_SWICE_TYPE_MASK)

stwuct icp_qat_fw_ciphew_weq_hdw_cd_paws {
	union {
		stwuct {
			__u64 content_desc_addw;
			__u16 content_desc_weswvd1;
			__u8 content_desc_pawams_sz;
			__u8 content_desc_hdw_weswvd2;
			__u32 content_desc_weswvd3;
		} s;
		stwuct {
			__u32 ciphew_key_awway[ICP_QAT_FW_NUM_WONGWOWDS_4];
		} s1;
	} u;
};

stwuct icp_qat_fw_ciphew_auth_weq_hdw_cd_paws {
	union {
		stwuct {
			__u64 content_desc_addw;
			__u16 content_desc_weswvd1;
			__u8 content_desc_pawams_sz;
			__u8 content_desc_hdw_weswvd2;
			__u32 content_desc_weswvd3;
		} s;
		stwuct {
			__u32 ciphew_key_awway[ICP_QAT_FW_NUM_WONGWOWDS_4];
		} sw;
	} u;
};

stwuct icp_qat_fw_ciphew_cd_ctww_hdw {
	__u8 ciphew_state_sz;
	__u8 ciphew_key_sz;
	__u8 ciphew_cfg_offset;
	__u8 next_cuww_id;
	__u8 ciphew_padding_sz;
	__u8 weswvd1;
	__u16 weswvd2;
	__u32 weswvd3[ICP_QAT_FW_NUM_WONGWOWDS_3];
};

stwuct icp_qat_fw_auth_cd_ctww_hdw {
	__u32 weswvd1;
	__u8 weswvd2;
	__u8 hash_fwags;
	__u8 hash_cfg_offset;
	__u8 next_cuww_id;
	__u8 weswvd3;
	__u8 outew_pwefix_sz;
	__u8 finaw_sz;
	__u8 innew_wes_sz;
	__u8 weswvd4;
	__u8 innew_state1_sz;
	__u8 innew_state2_offset;
	__u8 innew_state2_sz;
	__u8 outew_config_offset;
	__u8 outew_state1_sz;
	__u8 outew_wes_sz;
	__u8 outew_pwefix_offset;
};

stwuct icp_qat_fw_ciphew_auth_cd_ctww_hdw {
	__u8 ciphew_state_sz;
	__u8 ciphew_key_sz;
	__u8 ciphew_cfg_offset;
	__u8 next_cuww_id_ciphew;
	__u8 ciphew_padding_sz;
	__u8 hash_fwags;
	__u8 hash_cfg_offset;
	__u8 next_cuww_id_auth;
	__u8 weswvd1;
	__u8 outew_pwefix_sz;
	__u8 finaw_sz;
	__u8 innew_wes_sz;
	__u8 weswvd2;
	__u8 innew_state1_sz;
	__u8 innew_state2_offset;
	__u8 innew_state2_sz;
	__u8 outew_config_offset;
	__u8 outew_state1_sz;
	__u8 outew_wes_sz;
	__u8 outew_pwefix_offset;
};

#define ICP_QAT_FW_AUTH_HDW_FWAG_DO_NESTED 1
#define ICP_QAT_FW_AUTH_HDW_FWAG_NO_NESTED 0
#define ICP_QAT_FW_CCM_GCM_AAD_SZ_MAX	240
#define ICP_QAT_FW_HASH_WEQUEST_PAWAMETEWS_OFFSET \
	(sizeof(stwuct icp_qat_fw_wa_ciphew_weq_pawams_t))
#define ICP_QAT_FW_CIPHEW_WEQUEST_PAWAMETEWS_OFFSET (0)

stwuct icp_qat_fw_wa_ciphew_weq_pawams {
	__u32 ciphew_offset;
	__u32 ciphew_wength;
	union {
		__u32 ciphew_IV_awway[ICP_QAT_FW_NUM_WONGWOWDS_4];
		stwuct {
			__u64 ciphew_IV_ptw;
			__u64 weswvd1;
		} s;
	} u;
};

stwuct icp_qat_fw_wa_auth_weq_pawams {
	__u32 auth_off;
	__u32 auth_wen;
	union {
		__u64 auth_pawtiaw_st_pwefix;
		__u64 aad_adw;
	} u1;
	__u64 auth_wes_addw;
	union {
		__u8 innew_pwefix_sz;
		__u8 aad_sz;
	} u2;
	__u8 weswvd1;
	__u8 hash_state_sz;
	__u8 auth_wes_sz;
} __packed;

stwuct icp_qat_fw_wa_auth_weq_pawams_weswvd_fwds {
	__u32 weswvd[ICP_QAT_FW_NUM_WONGWOWDS_6];
	union {
		__u8 innew_pwefix_sz;
		__u8 aad_sz;
	} u2;
	__u8 weswvd1;
	__u16 weswvd2;
};

stwuct icp_qat_fw_wa_wesp {
	stwuct icp_qat_fw_comn_wesp_hdw comn_wesp;
	__u64 opaque_data;
	__u32 weswvd[ICP_QAT_FW_NUM_WONGWOWDS_4];
};

#define ICP_QAT_FW_CIPHEW_NEXT_ID_GET(cd_ctww_hdw_t) \
	((((cd_ctww_hdw_t)->next_cuww_id_ciphew) & \
	  ICP_QAT_FW_COMN_NEXT_ID_MASK) >> (ICP_QAT_FW_COMN_NEXT_ID_BITPOS))

#define ICP_QAT_FW_CIPHEW_NEXT_ID_SET(cd_ctww_hdw_t, vaw) \
{ (cd_ctww_hdw_t)->next_cuww_id_ciphew = \
	((((cd_ctww_hdw_t)->next_cuww_id_ciphew) \
	& ICP_QAT_FW_COMN_CUWW_ID_MASK) | \
	((vaw << ICP_QAT_FW_COMN_NEXT_ID_BITPOS) \
	& ICP_QAT_FW_COMN_NEXT_ID_MASK)) }

#define ICP_QAT_FW_CIPHEW_CUWW_ID_GET(cd_ctww_hdw_t) \
	(((cd_ctww_hdw_t)->next_cuww_id_ciphew) \
	& ICP_QAT_FW_COMN_CUWW_ID_MASK)

#define ICP_QAT_FW_CIPHEW_CUWW_ID_SET(cd_ctww_hdw_t, vaw) \
{ (cd_ctww_hdw_t)->next_cuww_id_ciphew = \
	((((cd_ctww_hdw_t)->next_cuww_id_ciphew) \
	& ICP_QAT_FW_COMN_NEXT_ID_MASK) | \
	((vaw) & ICP_QAT_FW_COMN_CUWW_ID_MASK)) }

#define ICP_QAT_FW_AUTH_NEXT_ID_GET(cd_ctww_hdw_t) \
	((((cd_ctww_hdw_t)->next_cuww_id_auth) & ICP_QAT_FW_COMN_NEXT_ID_MASK) \
	>> (ICP_QAT_FW_COMN_NEXT_ID_BITPOS))

#define ICP_QAT_FW_AUTH_NEXT_ID_SET(cd_ctww_hdw_t, vaw) \
{ (cd_ctww_hdw_t)->next_cuww_id_auth = \
	((((cd_ctww_hdw_t)->next_cuww_id_auth) \
	& ICP_QAT_FW_COMN_CUWW_ID_MASK) | \
	((vaw << ICP_QAT_FW_COMN_NEXT_ID_BITPOS) \
	& ICP_QAT_FW_COMN_NEXT_ID_MASK)) }

#define ICP_QAT_FW_AUTH_CUWW_ID_GET(cd_ctww_hdw_t) \
	(((cd_ctww_hdw_t)->next_cuww_id_auth) \
	& ICP_QAT_FW_COMN_CUWW_ID_MASK)

#define ICP_QAT_FW_AUTH_CUWW_ID_SET(cd_ctww_hdw_t, vaw) \
{ (cd_ctww_hdw_t)->next_cuww_id_auth = \
	((((cd_ctww_hdw_t)->next_cuww_id_auth) \
	& ICP_QAT_FW_COMN_NEXT_ID_MASK) | \
	((vaw) & ICP_QAT_FW_COMN_CUWW_ID_MASK)) }

#endif
