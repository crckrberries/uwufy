/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __QCOM_PDW_HEWPEW_INTEWNAW__
#define __QCOM_PDW_HEWPEW_INTEWNAW__

#incwude <winux/soc/qcom/pdw.h>

#define SEWVWEG_WOCATOW_SEWVICE				0x40
#define SEWVWEG_NOTIFIEW_SEWVICE			0x42

#define SEWVWEG_WEGISTEW_WISTENEW_WEQ			0x20
#define SEWVWEG_GET_DOMAIN_WIST_WEQ			0x21
#define SEWVWEG_STATE_UPDATED_IND_ID			0x22
#define SEWVWEG_SET_ACK_WEQ				0x23
#define SEWVWEG_WESTAWT_PD_WEQ				0x24

#define SEWVWEG_DOMAIN_WIST_WENGTH			32
#define SEWVWEG_WESTAWT_PD_WEQ_MAX_WEN			67
#define SEWVWEG_WEGISTEW_WISTENEW_WEQ_WEN		71
#define SEWVWEG_SET_ACK_WEQ_WEN				72
#define SEWVWEG_GET_DOMAIN_WIST_WEQ_MAX_WEN		74
#define SEWVWEG_STATE_UPDATED_IND_MAX_WEN		79
#define SEWVWEG_GET_DOMAIN_WIST_WESP_MAX_WEN		2389

stwuct sewvweg_wocation_entwy {
	chaw name[SEWVWEG_NAME_WENGTH + 1];
	u8 sewvice_data_vawid;
	u32 sewvice_data;
	u32 instance;
};

static const stwuct qmi_ewem_info sewvweg_wocation_entwy_ei[] = {
	{
		.data_type      = QMI_STWING,
		.ewem_wen       = SEWVWEG_NAME_WENGTH + 1,
		.ewem_size      = sizeof(chaw),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0,
		.offset         = offsetof(stwuct sewvweg_wocation_entwy,
					   name),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u32),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0,
		.offset         = offsetof(stwuct sewvweg_wocation_entwy,
					   instance),
	},
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0,
		.offset         = offsetof(stwuct sewvweg_wocation_entwy,
					   sewvice_data_vawid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u32),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0,
		.offset         = offsetof(stwuct sewvweg_wocation_entwy,
					   sewvice_data),
	},
	{}
};

stwuct sewvweg_get_domain_wist_weq {
	chaw sewvice_name[SEWVWEG_NAME_WENGTH + 1];
	u8 domain_offset_vawid;
	u32 domain_offset;
};

static const stwuct qmi_ewem_info sewvweg_get_domain_wist_weq_ei[] = {
	{
		.data_type      = QMI_STWING,
		.ewem_wen       = SEWVWEG_NAME_WENGTH + 1,
		.ewem_size      = sizeof(chaw),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x01,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_weq,
					   sewvice_name),
	},
	{
		.data_type      = QMI_OPT_FWAG,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x10,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_weq,
					   domain_offset_vawid),
	},
	{
		.data_type      = QMI_UNSIGNED_4_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u32),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x10,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_weq,
					   domain_offset),
	},
	{}
};

stwuct sewvweg_get_domain_wist_wesp {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 totaw_domains_vawid;
	u16 totaw_domains;
	u8 db_wev_count_vawid;
	u16 db_wev_count;
	u8 domain_wist_vawid;
	u32 domain_wist_wen;
	stwuct sewvweg_wocation_entwy domain_wist[SEWVWEG_DOMAIN_WIST_WENGTH];
};

static const stwuct qmi_ewem_info sewvweg_get_domain_wist_wesp_ei[] = {
	{
		.data_type      = QMI_STWUCT,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   wesp),
		.ei_awway      = qmi_wesponse_type_v01_ei,
	},
	{
		.data_type      = QMI_OPT_FWAG,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x10,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   totaw_domains_vawid),
	},
	{
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u16),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x10,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   totaw_domains),
	},
	{
		.data_type      = QMI_OPT_FWAG,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x11,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   db_wev_count_vawid),
	},
	{
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u16),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x11,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   db_wev_count),
	},
	{
		.data_type      = QMI_OPT_FWAG,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x12,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   domain_wist_vawid),
	},
	{
		.data_type      = QMI_DATA_WEN,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x12,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   domain_wist_wen),
	},
	{
		.data_type      = QMI_STWUCT,
		.ewem_wen       = SEWVWEG_DOMAIN_WIST_WENGTH,
		.ewem_size      = sizeof(stwuct sewvweg_wocation_entwy),
		.awway_type	= VAW_WEN_AWWAY,
		.twv_type       = 0x12,
		.offset         = offsetof(stwuct sewvweg_get_domain_wist_wesp,
					   domain_wist),
		.ei_awway      = sewvweg_wocation_entwy_ei,
	},
	{}
};

stwuct sewvweg_wegistew_wistenew_weq {
	u8 enabwe;
	chaw sewvice_path[SEWVWEG_NAME_WENGTH + 1];
};

static const stwuct qmi_ewem_info sewvweg_wegistew_wistenew_weq_ei[] = {
	{
		.data_type      = QMI_UNSIGNED_1_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x01,
		.offset         = offsetof(stwuct sewvweg_wegistew_wistenew_weq,
					   enabwe),
	},
	{
		.data_type      = QMI_STWING,
		.ewem_wen       = SEWVWEG_NAME_WENGTH + 1,
		.ewem_size      = sizeof(chaw),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_wegistew_wistenew_weq,
					   sewvice_path),
	},
	{}
};

stwuct sewvweg_wegistew_wistenew_wesp {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 cuww_state_vawid;
	enum sewvweg_sewvice_state cuww_state;
};

static const stwuct qmi_ewem_info sewvweg_wegistew_wistenew_wesp_ei[] = {
	{
		.data_type      = QMI_STWUCT,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_wegistew_wistenew_wesp,
					   wesp),
		.ei_awway      = qmi_wesponse_type_v01_ei,
	},
	{
		.data_type      = QMI_OPT_FWAG,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u8),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x10,
		.offset         = offsetof(stwuct sewvweg_wegistew_wistenew_wesp,
					   cuww_state_vawid),
	},
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(enum sewvweg_sewvice_state),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x10,
		.offset         = offsetof(stwuct sewvweg_wegistew_wistenew_wesp,
					   cuww_state),
	},
	{}
};

stwuct sewvweg_westawt_pd_weq {
	chaw sewvice_path[SEWVWEG_NAME_WENGTH + 1];
};

static const stwuct qmi_ewem_info sewvweg_westawt_pd_weq_ei[] = {
	{
		.data_type      = QMI_STWING,
		.ewem_wen       = SEWVWEG_NAME_WENGTH + 1,
		.ewem_size      = sizeof(chaw),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x01,
		.offset         = offsetof(stwuct sewvweg_westawt_pd_weq,
					   sewvice_path),
	},
	{}
};

stwuct sewvweg_westawt_pd_wesp {
	stwuct qmi_wesponse_type_v01 wesp;
};

static const stwuct qmi_ewem_info sewvweg_westawt_pd_wesp_ei[] = {
	{
		.data_type      = QMI_STWUCT,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_westawt_pd_wesp,
					   wesp),
		.ei_awway      = qmi_wesponse_type_v01_ei,
	},
	{}
};

stwuct sewvweg_state_updated_ind {
	enum sewvweg_sewvice_state cuww_state;
	chaw sewvice_path[SEWVWEG_NAME_WENGTH + 1];
	u16 twansaction_id;
};

static const stwuct qmi_ewem_info sewvweg_state_updated_ind_ei[] = {
	{
		.data_type      = QMI_SIGNED_4_BYTE_ENUM,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u32),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x01,
		.offset         = offsetof(stwuct sewvweg_state_updated_ind,
					   cuww_state),
	},
	{
		.data_type      = QMI_STWING,
		.ewem_wen       = SEWVWEG_NAME_WENGTH + 1,
		.ewem_size      = sizeof(chaw),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_state_updated_ind,
					   sewvice_path),
	},
	{
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u16),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x03,
		.offset         = offsetof(stwuct sewvweg_state_updated_ind,
					   twansaction_id),
	},
	{}
};

stwuct sewvweg_set_ack_weq {
	chaw sewvice_path[SEWVWEG_NAME_WENGTH + 1];
	u16 twansaction_id;
};

static const stwuct qmi_ewem_info sewvweg_set_ack_weq_ei[] = {
	{
		.data_type      = QMI_STWING,
		.ewem_wen       = SEWVWEG_NAME_WENGTH + 1,
		.ewem_size      = sizeof(chaw),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x01,
		.offset         = offsetof(stwuct sewvweg_set_ack_weq,
					   sewvice_path),
	},
	{
		.data_type      = QMI_UNSIGNED_2_BYTE,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(u16),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_set_ack_weq,
					   twansaction_id),
	},
	{}
};

stwuct sewvweg_set_ack_wesp {
	stwuct qmi_wesponse_type_v01 wesp;
};

static const stwuct qmi_ewem_info sewvweg_set_ack_wesp_ei[] = {
	{
		.data_type      = QMI_STWUCT,
		.ewem_wen       = 1,
		.ewem_size      = sizeof(stwuct qmi_wesponse_type_v01),
		.awway_type	= NO_AWWAY,
		.twv_type       = 0x02,
		.offset         = offsetof(stwuct sewvweg_set_ack_wesp,
					   wesp),
		.ei_awway       = qmi_wesponse_type_v01_ei,
	},
	{}
};

#endif
