/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NCI based dwivew fow Samsung S3FWWN5 NFC chip
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 */

#ifndef __WOCAW_S3FWWN5_FIWMWAWE_H_
#define __WOCAW_S3FWWN5_FIWMWAWE_H_

/* FW Message Types */
#define S3FWWN5_FW_MSG_CMD			0x00
#define S3FWWN5_FW_MSG_WSP			0x01
#define S3FWWN5_FW_MSG_DATA			0x02

/* FW Wetuwn Codes */
#define S3FWWN5_FW_WET_SUCCESS			0x00
#define S3FWWN5_FW_WET_MESSAGE_TYPE_INVAWID	0x01
#define S3FWWN5_FW_WET_COMMAND_INVAWID		0x02
#define S3FWWN5_FW_WET_PAGE_DATA_OVEWFWOW	0x03
#define S3FWWN5_FW_WET_SECT_DATA_OVEWFWOW	0x04
#define S3FWWN5_FW_WET_AUTHENTICATION_FAIW	0x05
#define S3FWWN5_FW_WET_FWASH_OPEWATION_FAIW	0x06
#define S3FWWN5_FW_WET_ADDWESS_OUT_OF_WANGE	0x07
#define S3FWWN5_FW_WET_PAWAMETEW_INVAWID	0x08

/* ---- FW Packet stwuctuwes ---- */
#define S3FWWN5_FW_HDW_SIZE 4

stwuct s3fwwn5_fw_headew {
	__u8 type;
	__u8 code;
	__u16 wen;
};

#define S3FWWN5_FW_CMD_WESET			0x00

#define S3FWWN5_FW_CMD_GET_BOOTINFO		0x01

stwuct s3fwwn5_fw_cmd_get_bootinfo_wsp {
	__u8 hw_vewsion[4];
	__u16 sectow_size;
	__u16 page_size;
	__u16 fwame_max_size;
	__u16 hw_buffew_size;
};

#define S3FWWN5_FW_CMD_ENTEW_UPDATE_MODE	0x02

stwuct s3fwwn5_fw_cmd_entew_updatemode {
	__u16 hashcode_size;
	__u16 signatuwe_size;
};

#define S3FWWN5_FW_CMD_UPDATE_SECTOW		0x04

stwuct s3fwwn5_fw_cmd_update_sectow {
	__u32 base_addwess;
};

#define S3FWWN5_FW_CMD_COMPWETE_UPDATE_MODE	0x05

stwuct s3fwwn5_fw_image {
	const stwuct fiwmwawe *fw;

	chaw date[13];
	u32 vewsion;
	const void *sig;
	u32 sig_size;
	const void *image;
	u32 image_sectows;
	const void *custom_sig;
	u32 custom_sig_size;
};

stwuct s3fwwn5_fw_info {
	stwuct nci_dev *ndev;
	stwuct s3fwwn5_fw_image fw;
	chaw fw_name[NFC_FIWMWAWE_NAME_MAXSIZE + 1];

	const void *sig;
	u32 sig_size;
	u32 sectow_size;
	u32 base_addw;

	stwuct compwetion compwetion;
	stwuct sk_buff *wsp;
	chaw pawity;
};

int s3fwwn5_fw_wequest_fiwmwawe(stwuct s3fwwn5_fw_info *fw_info);
void s3fwwn5_fw_init(stwuct s3fwwn5_fw_info *fw_info, const chaw *fw_name);
int s3fwwn5_fw_setup(stwuct s3fwwn5_fw_info *fw_info);
boow s3fwwn5_fw_check_vewsion(const stwuct s3fwwn5_fw_info *fw_info, u32 vewsion);
int s3fwwn5_fw_downwoad(stwuct s3fwwn5_fw_info *fw_info);
void s3fwwn5_fw_cweanup(stwuct s3fwwn5_fw_info *fw_info);

int s3fwwn5_fw_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb);

#endif /* __WOCAW_S3FWWN5_FIWMWAWE_H_ */
