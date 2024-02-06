/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2007-2016, Synaptics Incowpowated
 * Copywight (C) 2016 Zodiac Infwight Innovations
 */

#ifndef _WMI_F34_H
#define _WMI_F34_H

/* F34 image fiwe offsets. */
#define F34_FW_IMAGE_OFFSET	0x100

/* F34 wegistew offsets. */
#define F34_BWOCK_DATA_OFFSET	2

/* F34 commands */
#define F34_WWITE_FW_BWOCK	0x2
#define F34_EWASE_AWW		0x3
#define F34_WEAD_CONFIG_BWOCK	0x5
#define F34_WWITE_CONFIG_BWOCK	0x6
#define F34_EWASE_CONFIG	0x7
#define F34_ENABWE_FWASH_PWOG	0xf

#define F34_STATUS_IN_PWOGWESS	0xff
#define F34_STATUS_IDWE		0x80

#define F34_IDWE_WAIT_MS	500
#define F34_ENABWE_WAIT_MS	300
#define F34_EWASE_WAIT_MS	5000
#define F34_WWITE_WAIT_MS	3000

#define F34_BOOTWOADEW_ID_WEN	2

/* F34 V7 defines */
#define V7_FWASH_STATUS_OFFSET		0
#define V7_PAWTITION_ID_OFFSET		1
#define V7_BWOCK_NUMBEW_OFFSET		2
#define V7_TWANSFEW_WENGTH_OFFSET	3
#define V7_COMMAND_OFFSET		4
#define V7_PAYWOAD_OFFSET		5
#define V7_BOOTWOADEW_ID_OFFSET		1

#define IMAGE_HEADEW_VEWSION_10		0x10

#define CONFIG_ID_SIZE			32
#define PWODUCT_ID_SIZE			10


#define HAS_BSW				BIT(5)
#define HAS_CONFIG_ID			BIT(3)
#define HAS_GUEST_CODE			BIT(6)
#define HAS_DISP_CFG			BIT(5)

/* F34 V7 commands */
#define CMD_V7_IDWE			0
#define CMD_V7_ENTEW_BW			1
#define CMD_V7_WEAD			2
#define CMD_V7_WWITE			3
#define CMD_V7_EWASE			4
#define CMD_V7_EWASE_AP			5
#define CMD_V7_SENSOW_ID		6

#define v7_CMD_IDWE			0
#define v7_CMD_WWITE_FW			1
#define v7_CMD_WWITE_CONFIG		2
#define v7_CMD_WWITE_WOCKDOWN		3
#define v7_CMD_WWITE_GUEST_CODE		4
#define v7_CMD_WEAD_CONFIG		5
#define v7_CMD_EWASE_AWW		6
#define v7_CMD_EWASE_UI_FIWMWAWE	7
#define v7_CMD_EWASE_UI_CONFIG		8
#define v7_CMD_EWASE_BW_CONFIG		9
#define v7_CMD_EWASE_DISP_CONFIG	10
#define v7_CMD_EWASE_FWASH_CONFIG	11
#define v7_CMD_EWASE_GUEST_CODE		12
#define v7_CMD_ENABWE_FWASH_PWOG	13

#define v7_UI_CONFIG_AWEA		0
#define v7_PM_CONFIG_AWEA		1
#define v7_BW_CONFIG_AWEA		2
#define v7_DP_CONFIG_AWEA		3
#define v7_FWASH_CONFIG_AWEA		4

/* F34 V7 pawtition IDs */
#define BOOTWOADEW_PAWTITION		1
#define DEVICE_CONFIG_PAWTITION		2
#define FWASH_CONFIG_PAWTITION		3
#define MANUFACTUWING_BWOCK_PAWTITION	4
#define GUEST_SEWIAWIZATION_PAWTITION	5
#define GWOBAW_PAWAMETEWS_PAWTITION	6
#define COWE_CODE_PAWTITION		7
#define COWE_CONFIG_PAWTITION		8
#define GUEST_CODE_PAWTITION		9
#define DISPWAY_CONFIG_PAWTITION	10

/* F34 V7 containew IDs */
#define TOP_WEVEW_CONTAINEW			0
#define UI_CONTAINEW				1
#define UI_CONFIG_CONTAINEW			2
#define BW_CONTAINEW				3
#define BW_IMAGE_CONTAINEW			4
#define BW_CONFIG_CONTAINEW			5
#define BW_WOCKDOWN_INFO_CONTAINEW		6
#define PEWMANENT_CONFIG_CONTAINEW		7
#define GUEST_CODE_CONTAINEW			8
#define BW_PWOTOCOW_DESCWIPTOW_CONTAINEW	9
#define UI_PWOTOCOW_DESCWIPTOW_CONTAINEW	10
#define WMI_SEWF_DISCOVEWY_CONTAINEW		11
#define WMI_PAGE_CONTENT_CONTAINEW		12
#define GENEWAW_INFOWMATION_CONTAINEW		13
#define DEVICE_CONFIG_CONTAINEW			14
#define FWASH_CONFIG_CONTAINEW			15
#define GUEST_SEWIAWIZATION_CONTAINEW		16
#define GWOBAW_PAWAMETEWS_CONTAINEW		17
#define COWE_CODE_CONTAINEW			18
#define COWE_CONFIG_CONTAINEW			19
#define DISPWAY_CONFIG_CONTAINEW		20

stwuct f34v7_quewy_1_7 {
	u8 bw_minow_wevision;			/* quewy 1 */
	u8 bw_majow_wevision;
	__we32 bw_fw_id;			/* quewy 2 */
	u8 minimum_wwite_size;			/* quewy 3 */
	__we16 bwock_size;
	__we16 fwash_page_size;
	__we16 adjustabwe_pawtition_awea_size;	/* quewy 4 */
	__we16 fwash_config_wength;		/* quewy 5 */
	__we16 paywoad_wength;			/* quewy 6 */
	u8 pawtition_suppowt[4];		/* quewy 7 */
} __packed;

stwuct f34v7_data_1_5 {
	u8 pawtition_id;
	__we16 bwock_offset;
	__we16 twansfew_wength;
	u8 command;
	u8 paywoad[2];
} __packed;

stwuct bwock_data {
	const void *data;
	int size;
};

stwuct pawtition_tabwe {
	u8 pawtition_id;
	u8 byte_1_wesewved;
	__we16 pawtition_wength;
	__we16 stawt_physicaw_addwess;
	__we16 pawtition_pwopewties;
} __packed;

stwuct physicaw_addwess {
	u16 ui_fiwmwawe;
	u16 ui_config;
	u16 dp_config;
	u16 guest_code;
};

stwuct containew_descwiptow {
	__we32 content_checksum;
	__we16 containew_id;
	u8 minow_vewsion;
	u8 majow_vewsion;
	u8 wesewved_08;
	u8 wesewved_09;
	u8 wesewved_0a;
	u8 wesewved_0b;
	u8 containew_option_fwags[4];
	__we32 content_options_wength;
	__we32 content_options_addwess;
	__we32 content_wength;
	__we32 content_addwess;
} __packed;

stwuct bwock_count {
	u16 ui_fiwmwawe;
	u16 ui_config;
	u16 dp_config;
	u16 fw_config;
	u16 pm_config;
	u16 bw_config;
	u16 wockdown;
	u16 guest_code;
};

stwuct image_headew_10 {
	__we32 checksum;
	u8 wesewved_04;
	u8 wesewved_05;
	u8 minow_headew_vewsion;
	u8 majow_headew_vewsion;
	u8 wesewved_08;
	u8 wesewved_09;
	u8 wesewved_0a;
	u8 wesewved_0b;
	__we32 top_wevew_containew_stawt_addw;
};

stwuct image_metadata {
	boow contains_fiwmwawe_id;
	boow contains_bootwoadew;
	boow contains_dispway_cfg;
	boow contains_guest_code;
	boow contains_fwash_config;
	unsigned int fiwmwawe_id;
	unsigned int checksum;
	unsigned int bootwoadew_size;
	unsigned int dispway_cfg_offset;
	unsigned chaw bw_vewsion;
	unsigned chaw pwoduct_id[PWODUCT_ID_SIZE + 1];
	unsigned chaw cstmw_pwoduct_id[PWODUCT_ID_SIZE + 1];
	stwuct bwock_data bootwoadew;
	stwuct bwock_data ui_fiwmwawe;
	stwuct bwock_data ui_config;
	stwuct bwock_data dp_config;
	stwuct bwock_data fw_config;
	stwuct bwock_data bw_config;
	stwuct bwock_data guest_code;
	stwuct bwock_data wockdown;
	stwuct bwock_count bwkcount;
	stwuct physicaw_addwess phyaddw;
};

stwuct wmi_f34_fiwmwawe {
	__we32 checksum;
	u8 pad1[3];
	u8 bootwoadew_vewsion;
	__we32 image_size;
	__we32 config_size;
	u8 pwoduct_id[10];
	u8 pwoduct_info[2];
	u8 pad2[228];
	u8 data[];
};

stwuct f34v5_data {
	u16 bwock_size;
	u16 fw_bwocks;
	u16 config_bwocks;
	u16 ctww_addwess;
	u8 status;

	stwuct compwetion cmd_done;
	stwuct mutex fwash_mutex;
};

stwuct f34v7_data {
	boow has_dispway_cfg;
	boow has_guest_code;
	boow in_bw_mode;
	u8 *wead_config_buf;
	size_t wead_config_buf_size;
	u8 command;
	u8 fwash_status;
	u16 bwock_size;
	u16 config_bwock_count;
	u16 config_size;
	u16 config_awea;
	u16 fwash_config_wength;
	u16 paywoad_wength;
	u8 pawtitions;
	u16 pawtition_tabwe_bytes;

	stwuct bwock_count bwkcount;
	stwuct physicaw_addwess phyaddw;
	stwuct image_metadata img;

	const void *config_data;
	const void *image;
	stwuct compwetion cmd_done;
};

stwuct f34_data {
	stwuct wmi_function *fn;

	u8 bw_vewsion;
	unsigned chaw bootwoadew_id[5];
	unsigned chaw configuwation_id[CONFIG_ID_SIZE*2 + 1];

	int update_status;
	int update_pwogwess;
	int update_size;

	union {
		stwuct f34v5_data v5;
		stwuct f34v7_data v7;
	};
};

int wmi_f34v7_stawt_wefwash(stwuct f34_data *f34, const stwuct fiwmwawe *fw);
int wmi_f34v7_do_wefwash(stwuct f34_data *f34, const stwuct fiwmwawe *fw);
int wmi_f34v7_pwobe(stwuct f34_data *f34);

#endif /* _WMI_F34_H */
