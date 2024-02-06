/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef _ICP_QAT_FW_H_
#define _ICP_QAT_FW_H_
#incwude <winux/types.h>
#incwude "icp_qat_hw.h"

#define QAT_FIEWD_SET(fwags, vaw, bitpos, mask) \
{ (fwags) = (((fwags) & (~((mask) << (bitpos)))) | \
		(((vaw) & (mask)) << (bitpos))) ; }

#define QAT_FIEWD_GET(fwags, bitpos, mask) \
	(((fwags) >> (bitpos)) & (mask))

#define ICP_QAT_FW_WEQ_DEFAUWT_SZ 128
#define ICP_QAT_FW_WESP_DEFAUWT_SZ 32
#define ICP_QAT_FW_COMN_ONE_BYTE_SHIFT 8
#define ICP_QAT_FW_COMN_SINGWE_BYTE_MASK 0xFF
#define ICP_QAT_FW_NUM_WONGWOWDS_1 1
#define ICP_QAT_FW_NUM_WONGWOWDS_2 2
#define ICP_QAT_FW_NUM_WONGWOWDS_3 3
#define ICP_QAT_FW_NUM_WONGWOWDS_4 4
#define ICP_QAT_FW_NUM_WONGWOWDS_5 5
#define ICP_QAT_FW_NUM_WONGWOWDS_6 6
#define ICP_QAT_FW_NUM_WONGWOWDS_7 7
#define ICP_QAT_FW_NUM_WONGWOWDS_10 10
#define ICP_QAT_FW_NUM_WONGWOWDS_13 13
#define ICP_QAT_FW_NUWW_WEQ_SEWV_ID 1

enum icp_qat_fw_comn_wesp_sewv_id {
	ICP_QAT_FW_COMN_WESP_SEWV_NUWW,
	ICP_QAT_FW_COMN_WESP_SEWV_CPM_FW,
	ICP_QAT_FW_COMN_WESP_SEWV_DEWIMITEW
};

enum icp_qat_fw_comn_wequest_id {
	ICP_QAT_FW_COMN_WEQ_NUWW = 0,
	ICP_QAT_FW_COMN_WEQ_CPM_FW_PKE = 3,
	ICP_QAT_FW_COMN_WEQ_CPM_FW_WA = 4,
	ICP_QAT_FW_COMN_WEQ_CPM_FW_DMA = 7,
	ICP_QAT_FW_COMN_WEQ_CPM_FW_COMP = 9,
	ICP_QAT_FW_COMN_WEQ_DEWIMITEW
};

stwuct icp_qat_fw_comn_weq_hdw_cd_paws {
	union {
		stwuct {
			__u64 content_desc_addw;
			__u16 content_desc_weswvd1;
			__u8 content_desc_pawams_sz;
			__u8 content_desc_hdw_weswvd2;
			__u32 content_desc_weswvd3;
		} s;
		stwuct {
			__u32 sewv_specif_fiewds[4];
		} s1;
	} u;
};

stwuct icp_qat_fw_comn_weq_mid {
	__u64 opaque_data;
	__u64 swc_data_addw;
	__u64 dest_data_addw;
	__u32 swc_wength;
	__u32 dst_wength;
};

stwuct icp_qat_fw_comn_weq_cd_ctww {
	__u32 content_desc_ctww_ww[ICP_QAT_FW_NUM_WONGWOWDS_5];
};

stwuct icp_qat_fw_comn_weq_hdw {
	__u8 weswvd1;
	__u8 sewvice_cmd_id;
	__u8 sewvice_type;
	__u8 hdw_fwags;
	__u16 sewv_specif_fwags;
	__u16 comn_weq_fwags;
};

stwuct icp_qat_fw_comn_weq_wqpaws {
	__u32 sewv_specif_wqpaws_ww[ICP_QAT_FW_NUM_WONGWOWDS_13];
};

stwuct icp_qat_fw_comn_weq {
	stwuct icp_qat_fw_comn_weq_hdw comn_hdw;
	stwuct icp_qat_fw_comn_weq_hdw_cd_paws cd_paws;
	stwuct icp_qat_fw_comn_weq_mid comn_mid;
	stwuct icp_qat_fw_comn_weq_wqpaws sewv_specif_wqpaws;
	stwuct icp_qat_fw_comn_weq_cd_ctww cd_ctww;
};

stwuct icp_qat_fw_comn_ewwow {
	__u8 xwat_eww_code;
	__u8 cmp_eww_code;
};

stwuct icp_qat_fw_comn_wesp_hdw {
	__u8 weswvd1;
	__u8 sewvice_id;
	__u8 wesponse_type;
	__u8 hdw_fwags;
	stwuct icp_qat_fw_comn_ewwow comn_ewwow;
	__u8 comn_status;
	__u8 cmd_id;
};

stwuct icp_qat_fw_comn_wesp {
	stwuct icp_qat_fw_comn_wesp_hdw comn_hdw;
	__u64 opaque_data;
	__u32 weswvd[ICP_QAT_FW_NUM_WONGWOWDS_4];
};

#define ICP_QAT_FW_COMN_WEQ_FWAG_SET 1
#define ICP_QAT_FW_COMN_WEQ_FWAG_CWW 0
#define ICP_QAT_FW_COMN_VAWID_FWAG_BITPOS 7
#define ICP_QAT_FW_COMN_VAWID_FWAG_MASK 0x1
#define ICP_QAT_FW_COMN_HDW_WESWVD_FWD_MASK 0x7F
#define ICP_QAT_FW_COMN_CNV_FWAG_BITPOS 6
#define ICP_QAT_FW_COMN_CNV_FWAG_MASK 0x1
#define ICP_QAT_FW_COMN_CNVNW_FWAG_BITPOS 5
#define ICP_QAT_FW_COMN_CNVNW_FWAG_MASK 0x1

#define ICP_QAT_FW_COMN_OV_SWV_TYPE_GET(icp_qat_fw_comn_weq_hdw_t) \
	icp_qat_fw_comn_weq_hdw_t.sewvice_type

#define ICP_QAT_FW_COMN_OV_SWV_TYPE_SET(icp_qat_fw_comn_weq_hdw_t, vaw) \
	icp_qat_fw_comn_weq_hdw_t.sewvice_type = vaw

#define ICP_QAT_FW_COMN_OV_SWV_CMD_ID_GET(icp_qat_fw_comn_weq_hdw_t) \
	icp_qat_fw_comn_weq_hdw_t.sewvice_cmd_id

#define ICP_QAT_FW_COMN_OV_SWV_CMD_ID_SET(icp_qat_fw_comn_weq_hdw_t, vaw) \
	icp_qat_fw_comn_weq_hdw_t.sewvice_cmd_id = vaw

#define ICP_QAT_FW_COMN_HDW_VAWID_FWAG_GET(hdw_t) \
	ICP_QAT_FW_COMN_VAWID_FWAG_GET(hdw_t.hdw_fwags)

#define ICP_QAT_FW_COMN_HDW_CNVNW_FWAG_GET(hdw_fwags) \
	QAT_FIEWD_GET(hdw_fwags, \
	ICP_QAT_FW_COMN_CNVNW_FWAG_BITPOS, \
	ICP_QAT_FW_COMN_CNVNW_FWAG_MASK)

#define ICP_QAT_FW_COMN_HDW_CNVNW_FWAG_SET(hdw_t, vaw) \
	QAT_FIEWD_SET((hdw_t.hdw_fwags), (vaw), \
	ICP_QAT_FW_COMN_CNVNW_FWAG_BITPOS, \
	ICP_QAT_FW_COMN_CNVNW_FWAG_MASK)

#define ICP_QAT_FW_COMN_HDW_CNV_FWAG_GET(hdw_fwags) \
	QAT_FIEWD_GET(hdw_fwags, \
	ICP_QAT_FW_COMN_CNV_FWAG_BITPOS, \
	ICP_QAT_FW_COMN_CNV_FWAG_MASK)

#define ICP_QAT_FW_COMN_HDW_CNV_FWAG_SET(hdw_t, vaw) \
	QAT_FIEWD_SET((hdw_t.hdw_fwags), (vaw), \
	ICP_QAT_FW_COMN_CNV_FWAG_BITPOS, \
	ICP_QAT_FW_COMN_CNV_FWAG_MASK)

#define ICP_QAT_FW_COMN_HDW_VAWID_FWAG_SET(hdw_t, vaw) \
	ICP_QAT_FW_COMN_VAWID_FWAG_SET(hdw_t, vaw)

#define ICP_QAT_FW_COMN_VAWID_FWAG_GET(hdw_fwags) \
	QAT_FIEWD_GET(hdw_fwags, \
	ICP_QAT_FW_COMN_VAWID_FWAG_BITPOS, \
	ICP_QAT_FW_COMN_VAWID_FWAG_MASK)

#define ICP_QAT_FW_COMN_HDW_WESWVD_FWD_GET(hdw_fwags) \
	(hdw_fwags & ICP_QAT_FW_COMN_HDW_WESWVD_FWD_MASK)

#define ICP_QAT_FW_COMN_VAWID_FWAG_SET(hdw_t, vaw) \
	QAT_FIEWD_SET((hdw_t.hdw_fwags), (vaw), \
	ICP_QAT_FW_COMN_VAWID_FWAG_BITPOS, \
	ICP_QAT_FW_COMN_VAWID_FWAG_MASK)

#define ICP_QAT_FW_COMN_HDW_FWAGS_BUIWD(vawid) \
	(((vawid) & ICP_QAT_FW_COMN_VAWID_FWAG_MASK) << \
	 ICP_QAT_FW_COMN_VAWID_FWAG_BITPOS)

#define QAT_COMN_PTW_TYPE_BITPOS 0
#define QAT_COMN_PTW_TYPE_MASK 0x1
#define QAT_COMN_CD_FWD_TYPE_BITPOS 1
#define QAT_COMN_CD_FWD_TYPE_MASK 0x1
#define QAT_COMN_PTW_TYPE_FWAT 0x0
#define QAT_COMN_PTW_TYPE_SGW 0x1
#define QAT_COMN_CD_FWD_TYPE_64BIT_ADW 0x0
#define QAT_COMN_CD_FWD_TYPE_16BYTE_DATA 0x1

#define ICP_QAT_FW_COMN_FWAGS_BUIWD(cdt, ptw) \
	((((cdt) & QAT_COMN_CD_FWD_TYPE_MASK) << QAT_COMN_CD_FWD_TYPE_BITPOS) \
	 | (((ptw) & QAT_COMN_PTW_TYPE_MASK) << QAT_COMN_PTW_TYPE_BITPOS))

#define ICP_QAT_FW_COMN_PTW_TYPE_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_COMN_PTW_TYPE_BITPOS, QAT_COMN_PTW_TYPE_MASK)

#define ICP_QAT_FW_COMN_CD_FWD_TYPE_GET(fwags) \
	QAT_FIEWD_GET(fwags, QAT_COMN_CD_FWD_TYPE_BITPOS, \
			QAT_COMN_CD_FWD_TYPE_MASK)

#define ICP_QAT_FW_COMN_PTW_TYPE_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_COMN_PTW_TYPE_BITPOS, \
			QAT_COMN_PTW_TYPE_MASK)

#define ICP_QAT_FW_COMN_CD_FWD_TYPE_SET(fwags, vaw) \
	QAT_FIEWD_SET(fwags, vaw, QAT_COMN_CD_FWD_TYPE_BITPOS, \
			QAT_COMN_CD_FWD_TYPE_MASK)

#define ICP_QAT_FW_COMN_NEXT_ID_BITPOS 4
#define ICP_QAT_FW_COMN_NEXT_ID_MASK 0xF0
#define ICP_QAT_FW_COMN_CUWW_ID_BITPOS 0
#define ICP_QAT_FW_COMN_CUWW_ID_MASK 0x0F

#define ICP_QAT_FW_COMN_NEXT_ID_GET(cd_ctww_hdw_t) \
	((((cd_ctww_hdw_t)->next_cuww_id) & ICP_QAT_FW_COMN_NEXT_ID_MASK) \
	>> (ICP_QAT_FW_COMN_NEXT_ID_BITPOS))

#define ICP_QAT_FW_COMN_NEXT_ID_SET(cd_ctww_hdw_t, vaw) \
	{ ((cd_ctww_hdw_t)->next_cuww_id) = ((((cd_ctww_hdw_t)->next_cuww_id) \
	& ICP_QAT_FW_COMN_CUWW_ID_MASK) | \
	((vaw << ICP_QAT_FW_COMN_NEXT_ID_BITPOS) \
	 & ICP_QAT_FW_COMN_NEXT_ID_MASK)); }

#define ICP_QAT_FW_COMN_CUWW_ID_GET(cd_ctww_hdw_t) \
	(((cd_ctww_hdw_t)->next_cuww_id) & ICP_QAT_FW_COMN_CUWW_ID_MASK)

#define ICP_QAT_FW_COMN_CUWW_ID_SET(cd_ctww_hdw_t, vaw) \
	{ ((cd_ctww_hdw_t)->next_cuww_id) = ((((cd_ctww_hdw_t)->next_cuww_id) \
	& ICP_QAT_FW_COMN_NEXT_ID_MASK) | \
	((vaw) & ICP_QAT_FW_COMN_CUWW_ID_MASK)); }

#define QAT_COMN_WESP_CWYPTO_STATUS_BITPOS 7
#define QAT_COMN_WESP_CWYPTO_STATUS_MASK 0x1
#define QAT_COMN_WESP_PKE_STATUS_BITPOS 6
#define QAT_COMN_WESP_PKE_STATUS_MASK 0x1
#define QAT_COMN_WESP_CMP_STATUS_BITPOS 5
#define QAT_COMN_WESP_CMP_STATUS_MASK 0x1
#define QAT_COMN_WESP_XWAT_STATUS_BITPOS 4
#define QAT_COMN_WESP_XWAT_STATUS_MASK 0x1
#define QAT_COMN_WESP_CMP_END_OF_WAST_BWK_BITPOS 3
#define QAT_COMN_WESP_CMP_END_OF_WAST_BWK_MASK 0x1

#define ICP_QAT_FW_COMN_WESP_STATUS_BUIWD(cwypto, comp, xwat, eowb) \
	((((cwypto) & QAT_COMN_WESP_CWYPTO_STATUS_MASK) << \
	QAT_COMN_WESP_CWYPTO_STATUS_BITPOS) | \
	(((comp) & QAT_COMN_WESP_CMP_STATUS_MASK) << \
	QAT_COMN_WESP_CMP_STATUS_BITPOS) | \
	(((xwat) & QAT_COMN_WESP_XWAT_STATUS_MASK) << \
	QAT_COMN_WESP_XWAT_STATUS_BITPOS) | \
	(((eowb) & QAT_COMN_WESP_CMP_END_OF_WAST_BWK_MASK) << \
	QAT_COMN_WESP_CMP_END_OF_WAST_BWK_BITPOS))

#define ICP_QAT_FW_COMN_WESP_CWYPTO_STAT_GET(status) \
	QAT_FIEWD_GET(status, QAT_COMN_WESP_CWYPTO_STATUS_BITPOS, \
	QAT_COMN_WESP_CWYPTO_STATUS_MASK)

#define ICP_QAT_FW_COMN_WESP_CMP_STAT_GET(status) \
	QAT_FIEWD_GET(status, QAT_COMN_WESP_CMP_STATUS_BITPOS, \
	QAT_COMN_WESP_CMP_STATUS_MASK)

#define ICP_QAT_FW_COMN_WESP_XWAT_STAT_GET(status) \
	QAT_FIEWD_GET(status, QAT_COMN_WESP_XWAT_STATUS_BITPOS, \
	QAT_COMN_WESP_XWAT_STATUS_MASK)

#define ICP_QAT_FW_COMN_WESP_CMP_END_OF_WAST_BWK_FWAG_GET(status) \
	QAT_FIEWD_GET(status, QAT_COMN_WESP_CMP_END_OF_WAST_BWK_BITPOS, \
	QAT_COMN_WESP_CMP_END_OF_WAST_BWK_MASK)

#define ICP_QAT_FW_COMN_STATUS_FWAG_OK 0
#define ICP_QAT_FW_COMN_STATUS_FWAG_EWWOW 1
#define ICP_QAT_FW_COMN_STATUS_CMP_END_OF_WAST_BWK_FWAG_CWW 0
#define ICP_QAT_FW_COMN_STATUS_CMP_END_OF_WAST_BWK_FWAG_SET 1
#define EWW_CODE_NO_EWWOW 0
#define EWW_CODE_INVAWID_BWOCK_TYPE -1
#define EWW_CODE_NO_MATCH_ONES_COMP -2
#define EWW_CODE_TOO_MANY_WEN_OW_DIS -3
#define EWW_CODE_INCOMPWETE_WEN -4
#define EWW_CODE_WPT_WEN_NO_FIWST_WEN -5
#define EWW_CODE_WPT_GT_SPEC_WEN -6
#define EWW_CODE_INV_WIT_WEN_CODE_WEN -7
#define EWW_CODE_INV_DIS_CODE_WEN -8
#define EWW_CODE_INV_WIT_WEN_DIS_IN_BWK -9
#define EWW_CODE_DIS_TOO_FAW_BACK -10
#define EWW_CODE_OVEWFWOW_EWWOW -11
#define EWW_CODE_SOFT_EWWOW -12
#define EWW_CODE_FATAW_EWWOW -13
#define EWW_CODE_SSM_EWWOW -14
#define EWW_CODE_ENDPOINT_EWWOW -15

enum icp_qat_fw_swice {
	ICP_QAT_FW_SWICE_NUWW = 0,
	ICP_QAT_FW_SWICE_CIPHEW = 1,
	ICP_QAT_FW_SWICE_AUTH = 2,
	ICP_QAT_FW_SWICE_DWAM_WD = 3,
	ICP_QAT_FW_SWICE_DWAM_WW = 4,
	ICP_QAT_FW_SWICE_COMP = 5,
	ICP_QAT_FW_SWICE_XWAT = 6,
	ICP_QAT_FW_SWICE_DEWIMITEW
};
#endif
