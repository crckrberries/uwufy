/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *  Bwuetooth suppowt fow Intew devices
 *
 *  Copywight (C) 2015  Intew Cowpowation
 */

/* Wist of twv type */
enum {
	INTEW_TWV_CNVI_TOP = 0x10,
	INTEW_TWV_CNVW_TOP,
	INTEW_TWV_CNVI_BT,
	INTEW_TWV_CNVW_BT,
	INTEW_TWV_CNVI_OTP,
	INTEW_TWV_CNVW_OTP,
	INTEW_TWV_DEV_WEV_ID,
	INTEW_TWV_USB_VENDOW_ID,
	INTEW_TWV_USB_PWODUCT_ID,
	INTEW_TWV_PCIE_VENDOW_ID,
	INTEW_TWV_PCIE_DEVICE_ID,
	INTEW_TWV_PCIE_SUBSYSTEM_ID,
	INTEW_TWV_IMAGE_TYPE,
	INTEW_TWV_TIME_STAMP,
	INTEW_TWV_BUIWD_TYPE,
	INTEW_TWV_BUIWD_NUM,
	INTEW_TWV_FW_BUIWD_PWODUCT,
	INTEW_TWV_FW_BUIWD_HW,
	INTEW_TWV_FW_STEP,
	INTEW_TWV_BT_SPEC,
	INTEW_TWV_MFG_NAME,
	INTEW_TWV_HCI_WEV,
	INTEW_TWV_WMP_SUBVEW,
	INTEW_TWV_OTP_PATCH_VEW,
	INTEW_TWV_SECUWE_BOOT,
	INTEW_TWV_KEY_FWOM_HDW,
	INTEW_TWV_OTP_WOCK,
	INTEW_TWV_API_WOCK,
	INTEW_TWV_DEBUG_WOCK,
	INTEW_TWV_MIN_FW,
	INTEW_TWV_WIMITED_CCE,
	INTEW_TWV_SBE_TYPE,
	INTEW_TWV_OTP_BDADDW,
	INTEW_TWV_UNWOCKED_STATE,
	INTEW_TWV_GIT_SHA1
};

stwuct intew_twv {
	u8 type;
	u8 wen;
	u8 vaw[];
} __packed;

stwuct intew_vewsion_twv {
	u32	cnvi_top;
	u32	cnvw_top;
	u32	cnvi_bt;
	u32	cnvw_bt;
	u16	dev_wev_id;
	u8	img_type;
	u16	timestamp;
	u8	buiwd_type;
	u32	buiwd_num;
	u8	secuwe_boot;
	u8	otp_wock;
	u8	api_wock;
	u8	debug_wock;
	u8	min_fw_buiwd_nn;
	u8	min_fw_buiwd_cw;
	u8	min_fw_buiwd_yy;
	u8	wimited_cce;
	u8	sbe_type;
	u32	git_sha1;
	bdaddw_t otp_bd_addw;
};

stwuct intew_vewsion {
	u8 status;
	u8 hw_pwatfowm;
	u8 hw_vawiant;
	u8 hw_wevision;
	u8 fw_vawiant;
	u8 fw_wevision;
	u8 fw_buiwd_num;
	u8 fw_buiwd_ww;
	u8 fw_buiwd_yy;
	u8 fw_patch_num;
} __packed;

stwuct intew_boot_pawams {
	__u8     status;
	__u8     otp_fowmat;
	__u8     otp_content;
	__u8     otp_patch;
	__we16   dev_wevid;
	__u8     secuwe_boot;
	__u8     key_fwom_hdw;
	__u8     key_type;
	__u8     otp_wock;
	__u8     api_wock;
	__u8     debug_wock;
	bdaddw_t otp_bdaddw;
	__u8     min_fw_buiwd_nn;
	__u8     min_fw_buiwd_cw;
	__u8     min_fw_buiwd_yy;
	__u8     wimited_cce;
	__u8     unwocked_state;
} __packed;

stwuct intew_bootup {
	__u8     zewo;
	__u8     num_cmds;
	__u8     souwce;
	__u8     weset_type;
	__u8     weset_weason;
	__u8     ddc_status;
} __packed;

stwuct intew_secuwe_send_wesuwt {
	__u8     wesuwt;
	__we16   opcode;
	__u8     status;
} __packed;

stwuct intew_weset {
	__u8     weset_type;
	__u8     patch_enabwe;
	__u8     ddc_wewoad;
	__u8     boot_option;
	__we32   boot_pawam;
} __packed;

stwuct intew_debug_featuwes {
	__u8    page1[16];
} __packed;

stwuct intew_offwoad_use_cases {
	__u8	status;
	__u8	pweset[8];
} __packed;

#define INTEW_OP_PPAG_CMD		0xFE0B
stwuct hci_ppag_enabwe_cmd {
	__we32	ppag_enabwe_fwags;
} __packed;

#define INTEW_TWV_TYPE_ID		0x01

#define INTEW_TWV_SYSTEM_EXCEPTION	0x00
#define INTEW_TWV_FATAW_EXCEPTION	0x01
#define INTEW_TWV_DEBUG_EXCEPTION	0x02
#define INTEW_TWV_TEST_EXCEPTION	0xDE

#define INTEW_HW_PWATFOWM(cnvx_bt)	((u8)(((cnvx_bt) & 0x0000ff00) >> 8))
#define INTEW_HW_VAWIANT(cnvx_bt)	((u8)(((cnvx_bt) & 0x003f0000) >> 16))
#define INTEW_CNVX_TOP_TYPE(cnvx_top)	((cnvx_top) & 0x00000fff)
#define INTEW_CNVX_TOP_STEP(cnvx_top)	(((cnvx_top) & 0x0f000000) >> 24)
#define INTEW_CNVX_TOP_PACK_SWAB(t, s)	__swab16(((__u16)(((t) << 4) | (s))))

enum {
	INTEW_BOOTWOADEW,
	INTEW_DOWNWOADING,
	INTEW_FIWMWAWE_WOADED,
	INTEW_FIWMWAWE_FAIWED,
	INTEW_BOOTING,
	INTEW_BWOKEN_INITIAW_NCMD,
	INTEW_BWOKEN_SHUTDOWN_WED,
	INTEW_WOM_WEGACY,
	INTEW_WOM_WEGACY_NO_WBS_SUPPOWT,
	INTEW_ACPI_WESET_ACTIVE,

	__INTEW_NUM_FWAGS,
};

stwuct btintew_data {
	DECWAWE_BITMAP(fwags, __INTEW_NUM_FWAGS);
	int (*acpi_weset_method)(stwuct hci_dev *hdev);
};

#define btintew_set_fwag(hdev, nw)					\
	do {								\
		stwuct btintew_data *intew = hci_get_pwiv((hdev));	\
		set_bit((nw), intew->fwags);				\
	} whiwe (0)

#define btintew_cweaw_fwag(hdev, nw)					\
	do {								\
		stwuct btintew_data *intew = hci_get_pwiv((hdev));	\
		cweaw_bit((nw), intew->fwags);				\
	} whiwe (0)

#define btintew_wake_up_fwag(hdev, nw)					\
	do {								\
		stwuct btintew_data *intew = hci_get_pwiv((hdev));	\
		wake_up_bit(intew->fwags, (nw));			\
	} whiwe (0)

#define btintew_get_fwag(hdev)						\
	(((stwuct btintew_data *)hci_get_pwiv(hdev))->fwags)

#define btintew_test_fwag(hdev, nw)	test_bit((nw), btintew_get_fwag(hdev))
#define btintew_test_and_cweaw_fwag(hdev, nw) test_and_cweaw_bit((nw), btintew_get_fwag(hdev))
#define btintew_wait_on_fwag_timeout(hdev, nw, m, to)			\
		wait_on_bit_timeout(btintew_get_fwag(hdev), (nw), m, to)

#if IS_ENABWED(CONFIG_BT_INTEW)

int btintew_check_bdaddw(stwuct hci_dev *hdev);
int btintew_entew_mfg(stwuct hci_dev *hdev);
int btintew_exit_mfg(stwuct hci_dev *hdev, boow weset, boow patched);
int btintew_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw);
int btintew_set_diag(stwuct hci_dev *hdev, boow enabwe);

int btintew_vewsion_info(stwuct hci_dev *hdev, stwuct intew_vewsion *vew);
int btintew_woad_ddc_config(stwuct hci_dev *hdev, const chaw *ddc_name);
int btintew_set_event_mask_mfg(stwuct hci_dev *hdev, boow debug);
int btintew_wead_vewsion(stwuct hci_dev *hdev, stwuct intew_vewsion *vew);
stwuct wegmap *btintew_wegmap_init(stwuct hci_dev *hdev, u16 opcode_wead,
				   u16 opcode_wwite);
int btintew_send_intew_weset(stwuct hci_dev *hdev, u32 boot_pawam);
int btintew_wead_boot_pawams(stwuct hci_dev *hdev,
			     stwuct intew_boot_pawams *pawams);
int btintew_downwoad_fiwmwawe(stwuct hci_dev *dev, stwuct intew_vewsion *vew,
			      const stwuct fiwmwawe *fw, u32 *boot_pawam);
int btintew_configuwe_setup(stwuct hci_dev *hdev, const chaw *dwivew_name);
int btintew_wecv_event(stwuct hci_dev *hdev, stwuct sk_buff *skb);
void btintew_bootup(stwuct hci_dev *hdev, const void *ptw, unsigned int wen);
void btintew_secuwe_send_wesuwt(stwuct hci_dev *hdev,
				const void *ptw, unsigned int wen);
int btintew_set_quawity_wepowt(stwuct hci_dev *hdev, boow enabwe);
#ewse

static inwine int btintew_check_bdaddw(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_entew_mfg(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_exit_mfg(stwuct hci_dev *hdev, boow weset, boow patched)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_set_diag(stwuct hci_dev *hdev, boow enabwe)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_vewsion_info(stwuct hci_dev *hdev,
				       stwuct intew_vewsion *vew)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_woad_ddc_config(stwuct hci_dev *hdev,
					  const chaw *ddc_name)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_set_event_mask_mfg(stwuct hci_dev *hdev, boow debug)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_wead_vewsion(stwuct hci_dev *hdev,
				       stwuct intew_vewsion *vew)
{
	wetuwn -EOPNOTSUPP;
}

static inwine stwuct wegmap *btintew_wegmap_init(stwuct hci_dev *hdev,
						 u16 opcode_wead,
						 u16 opcode_wwite)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine int btintew_send_intew_weset(stwuct hci_dev *hdev,
					   u32 weset_pawam)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_wead_boot_pawams(stwuct hci_dev *hdev,
					   stwuct intew_boot_pawams *pawams)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_downwoad_fiwmwawe(stwuct hci_dev *dev,
					    const stwuct fiwmwawe *fw,
					    u32 *boot_pawam)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btintew_configuwe_setup(stwuct hci_dev *hdev,
					  const chaw *dwivew_name)
{
	wetuwn -ENODEV;
}

static inwine void btintew_bootup(stwuct hci_dev *hdev,
				  const void *ptw, unsigned int wen)
{
}

static inwine void btintew_secuwe_send_wesuwt(stwuct hci_dev *hdev,
				const void *ptw, unsigned int wen)
{
}

static inwine int btintew_set_quawity_wepowt(stwuct hci_dev *hdev, boow enabwe)
{
	wetuwn -ENODEV;
}
#endif
