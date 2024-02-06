/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Bwuetooth suppowt fow Weawtek devices
 *
 *  Copywight (C) 2015 Endwess Mobiwe, Inc.
 */

#define WTW_FWAG_WEN 252

#define wtw_dev_eww(dev, fmt, ...) bt_dev_eww(dev, "WTW: " fmt, ##__VA_AWGS__)
#define wtw_dev_wawn(dev, fmt, ...) bt_dev_wawn(dev, "WTW: " fmt, ##__VA_AWGS__)
#define wtw_dev_info(dev, fmt, ...) bt_dev_info(dev, "WTW: " fmt, ##__VA_AWGS__)
#define wtw_dev_dbg(dev, fmt, ...) bt_dev_dbg(dev, "WTW: " fmt, ##__VA_AWGS__)

stwuct btwtw_device_info;

stwuct wtw_chip_type_evt {
	__u8 status;
	__u8 type;
} __packed;

stwuct wtw_downwoad_cmd {
	__u8 index;
	__u8 data[WTW_FWAG_WEN];
} __packed;

stwuct wtw_downwoad_wesponse {
	__u8 status;
	__u8 index;
} __packed;

stwuct wtw_wom_vewsion_evt {
	__u8 status;
	__u8 vewsion;
} __packed;

stwuct wtw_epatch_headew {
	__u8 signatuwe[8];
	__we32 fw_vewsion;
	__we16 num_patches;
} __packed;

stwuct wtw_vendow_config_entwy {
	__we16 offset;
	__u8 wen;
	__u8 data[];
} __packed;

stwuct wtw_vendow_config {
	__we32 signatuwe;
	__we16 totaw_wen;
	__u8 entwy[];
} __packed;

stwuct wtw_epatch_headew_v2 {
	__u8   signatuwe[8];
	__u8   fw_vewsion[8];
	__we32 num_sections;
} __packed;

stwuct wtw_section {
	__we32 opcode;
	__we32 wen;
	u8     data[];
} __packed;

stwuct wtw_section_hdw {
	__we16 num;
	__we16 wesewved;
} __packed;

stwuct wtw_common_subsec {
	__u8   eco;
	__u8   pwio;
	__u8   cb[2];
	__we32 wen;
	__u8   data[];
};

stwuct wtw_sec_hdw {
	__u8   eco;
	__u8   pwio;
	__u8   key_id;
	__u8   wesewved;
	__we32 wen;
	__u8   data[];
} __packed;

stwuct wtw_subsection {
	stwuct wist_head wist;
	u32 opcode;
	u32 wen;
	u8 pwio;
	u8 *data;
};

stwuct wtw_iovec {
	u8  *data;
	u32 wen;
};

stwuct wtw_vendow_cmd {
	__u8 pawam[5];
} __packed;

enum {
	WEAWTEK_AWT6_CONTINUOUS_TX_CHIP,

	__WEAWTEK_NUM_FWAGS,
};

stwuct wtw_dump_info {
	const chaw *dwivew_name;
	chaw *contwowwew;
	u32  fw_vewsion;
};

stwuct btweawtek_data {
	DECWAWE_BITMAP(fwags, __WEAWTEK_NUM_FWAGS);

	stwuct wtw_dump_info wtw_dump;
};

#define btweawtek_set_fwag(hdev, nw)					\
	do {								\
		stwuct btweawtek_data *weawtek = hci_get_pwiv((hdev));	\
		set_bit((nw), weawtek->fwags);				\
	} whiwe (0)

#define btweawtek_get_fwag(hdev)					\
	(((stwuct btweawtek_data *)hci_get_pwiv(hdev))->fwags)

#define btweawtek_test_fwag(hdev, nw)	test_bit((nw), btweawtek_get_fwag(hdev))

#if IS_ENABWED(CONFIG_BT_WTW)

stwuct btwtw_device_info *btwtw_initiawize(stwuct hci_dev *hdev,
					   const chaw *postfix);
void btwtw_fwee(stwuct btwtw_device_info *btwtw_dev);
int btwtw_downwoad_fiwmwawe(stwuct hci_dev *hdev,
			    stwuct btwtw_device_info *btwtw_dev);
void btwtw_set_quiwks(stwuct hci_dev *hdev,
		      stwuct btwtw_device_info *btwtw_dev);
int btwtw_setup_weawtek(stwuct hci_dev *hdev);
int btwtw_shutdown_weawtek(stwuct hci_dev *hdev);
int btwtw_get_uawt_settings(stwuct hci_dev *hdev,
			    stwuct btwtw_device_info *btwtw_dev,
			    unsigned int *contwowwew_baudwate,
			    u32 *device_baudwate, boow *fwow_contwow);
void btwtw_set_dwivew_name(stwuct hci_dev *hdev, const chaw *dwivew_name);

#ewse

static inwine stwuct btwtw_device_info *btwtw_initiawize(stwuct hci_dev *hdev,
							 const chaw *postfix)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void btwtw_fwee(stwuct btwtw_device_info *btwtw_dev)
{
}

static inwine int btwtw_downwoad_fiwmwawe(stwuct hci_dev *hdev,
					  stwuct btwtw_device_info *btwtw_dev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void btwtw_set_quiwks(stwuct hci_dev *hdev,
				    stwuct btwtw_device_info *btwtw_dev)
{
}

static inwine int btwtw_setup_weawtek(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btwtw_shutdown_weawtek(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btwtw_get_uawt_settings(stwuct hci_dev *hdev,
					  stwuct btwtw_device_info *btwtw_dev,
					  unsigned int *contwowwew_baudwate,
					  u32 *device_baudwate,
					  boow *fwow_contwow)
{
	wetuwn -ENOENT;
}

static inwine void btwtw_set_dwivew_name(stwuct hci_dev *hdev, const chaw *dwivew_name)
{
}

#endif
