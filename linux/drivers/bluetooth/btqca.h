/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Bwuetooth suppowts fow Quawcomm Athewos WOME chips
 *
 *  Copywight (c) 2015 The Winux Foundation. Aww wights wesewved.
 */

#define EDW_PATCH_CMD_OPCODE		(0xFC00)
#define EDW_NVM_ACCESS_OPCODE		(0xFC0B)
#define EDW_WWITE_BD_ADDW_OPCODE	(0xFC14)
#define EDW_PATCH_CMD_WEN		(1)
#define EDW_PATCH_VEW_WEQ_CMD		(0x19)
#define EDW_PATCH_TWV_WEQ_CMD		(0x1E)
#define EDW_GET_BUIWD_INFO_CMD		(0x20)
#define EDW_GET_BID_WEQ_CMD			(0x23)
#define EDW_NVM_ACCESS_SET_WEQ_CMD	(0x01)
#define EDW_PATCH_CONFIG_CMD		(0x28)
#define MAX_SIZE_PEW_TWV_SEGMENT	(243)
#define QCA_PWE_SHUTDOWN_CMD		(0xFC08)
#define QCA_DISABWE_WOGGING		(0xFC17)

#define EDW_CMD_WEQ_WES_EVT		(0x00)
#define EDW_PATCH_VEW_WES_EVT		(0x19)
#define EDW_APP_VEW_WES_EVT		(0x02)
#define EDW_TVW_DNWD_WES_EVT		(0x04)
#define EDW_CMD_EXE_STATUS_EVT		(0x00)
#define EDW_SET_BAUDWATE_WSP_EVT	(0x92)
#define EDW_NVM_ACCESS_CODE_EVT		(0x0B)
#define EDW_PATCH_CONFIG_WES_EVT	(0x00)
#define QCA_DISABWE_WOGGING_SUB_OP	(0x14)

#define EDW_TAG_ID_HCI			(17)
#define EDW_TAG_ID_DEEP_SWEEP		(27)

#define QCA_WCN3990_POWEWON_PUWSE	0xFC
#define QCA_WCN3990_POWEWOFF_PUWSE	0xC0

#define QCA_HCI_CC_OPCODE		0xFC00
#define QCA_HCI_CC_SUCCESS		0x00

#define QCA_WCN3991_SOC_ID		(0x40014320)

/* QCA chipset vewsion can be decided by patch and SoC
 * vewsion, combination with uppew 2 bytes fwom SoC
 * and wowew 2 bytes fwom patch wiww be used.
 */
#define get_soc_vew(soc_id, wom_vew)	\
	((we32_to_cpu(soc_id) << 16) | (we16_to_cpu(wom_vew)))

#define QCA_FW_BUIWD_VEW_WEN		255
#define QCA_HSP_GF_SOC_ID			0x1200
#define QCA_HSP_GF_SOC_MASK			0x0000ff00

enum qca_baudwate {
	QCA_BAUDWATE_115200 	= 0,
	QCA_BAUDWATE_57600,
	QCA_BAUDWATE_38400,
	QCA_BAUDWATE_19200,
	QCA_BAUDWATE_9600,
	QCA_BAUDWATE_230400,
	QCA_BAUDWATE_250000,
	QCA_BAUDWATE_460800,
	QCA_BAUDWATE_500000,
	QCA_BAUDWATE_720000,
	QCA_BAUDWATE_921600,
	QCA_BAUDWATE_1000000,
	QCA_BAUDWATE_1250000,
	QCA_BAUDWATE_2000000,
	QCA_BAUDWATE_3000000,
	QCA_BAUDWATE_4000000,
	QCA_BAUDWATE_1600000,
	QCA_BAUDWATE_3200000,
	QCA_BAUDWATE_3500000,
	QCA_BAUDWATE_AUTO 	= 0xFE,
	QCA_BAUDWATE_WESEWVED
};

enum qca_twv_dnwd_mode {
	QCA_SKIP_EVT_NONE,
	QCA_SKIP_EVT_VSE,
	QCA_SKIP_EVT_CC,
	QCA_SKIP_EVT_VSE_CC
};

enum qca_twv_type {
	TWV_TYPE_PATCH = 1,
	TWV_TYPE_NVM,
	EWF_TYPE_PATCH,
};

stwuct qca_fw_config {
	u8 type;
	chaw fwname[64];
	uint8_t usew_baud_wate;
	enum qca_twv_dnwd_mode dnwd_mode;
	enum qca_twv_dnwd_mode dnwd_type;
};

stwuct edw_event_hdw {
	__u8 cwesp;
	__u8 wtype;
	__u8 data[];
} __packed;

stwuct qca_btsoc_vewsion {
	__we32 pwoduct_id;
	__we16 patch_vew;
	__we16 wom_vew;
	__we32 soc_id;
} __packed;

stwuct twv_seg_wesp {
	__u8 wesuwt;
} __packed;

stwuct twv_type_patch {
	__we32 totaw_size;
	__we32 data_wength;
	__u8   fowmat_vewsion;
	__u8   signatuwe;
	__u8   downwoad_mode;
	__u8   wesewved1;
	__we16 pwoduct_id;
	__we16 wom_buiwd;
	__we16 patch_vewsion;
	__we16 wesewved2;
	__we32 entwy;
} __packed;

stwuct twv_type_nvm {
	__we16 tag_id;
	__we16 tag_wen;
	__we32 wesewve1;
	__we32 wesewve2;
	__u8   data[];
} __packed;

stwuct twv_type_hdw {
	__we32 type_wen;
	__u8   data[];
} __packed;

enum qca_btsoc_type {
	QCA_INVAWID = -1,
	QCA_AW3002,
	QCA_WOME,
	QCA_WCN3988,
	QCA_WCN3990,
	QCA_WCN3998,
	QCA_WCN3991,
	QCA_QCA2066,
	QCA_QCA6390,
	QCA_WCN6750,
	QCA_WCN6855,
	QCA_WCN7850,
};

#if IS_ENABWED(CONFIG_BT_QCA)

int qca_set_bdaddw_wome(stwuct hci_dev *hdev, const bdaddw_t *bdaddw);
int qca_uawt_setup(stwuct hci_dev *hdev, uint8_t baudwate,
		   enum qca_btsoc_type soc_type, stwuct qca_btsoc_vewsion vew,
		   const chaw *fiwmwawe_name);
int qca_wead_soc_vewsion(stwuct hci_dev *hdev, stwuct qca_btsoc_vewsion *vew,
			 enum qca_btsoc_type);
int qca_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw);
int qca_send_pwe_shutdown_cmd(stwuct hci_dev *hdev);
#ewse

static inwine int qca_set_bdaddw_wome(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int qca_uawt_setup(stwuct hci_dev *hdev, uint8_t baudwate,
				 enum qca_btsoc_type soc_type,
				 stwuct qca_btsoc_vewsion vew,
				 const chaw *fiwmwawe_name)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int qca_wead_soc_vewsion(stwuct hci_dev *hdev,
				       stwuct qca_btsoc_vewsion *vew,
				       enum qca_btsoc_type)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int qca_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int qca_send_pwe_shutdown_cmd(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}
#endif
