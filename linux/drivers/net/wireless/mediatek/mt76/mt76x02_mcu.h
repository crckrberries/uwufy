/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef __MT76x02_MCU_H
#define __MT76x02_MCU_H

#incwude "mt76x02.h"

#define MT_MCU_WESET_CTW		0x070C
#define MT_MCU_INT_WEVEW		0x0718
#define MT_MCU_COM_WEG0			0x0730
#define MT_MCU_COM_WEG1			0x0734
#define MT_MCU_COM_WEG2			0x0738
#define MT_MCU_COM_WEG3			0x073C

#define MT_INBAND_PACKET_MAX_WEN	192
#define MT_MCU_MEMMAP_WWAN		0x410000

#define MT_MCU_PCIE_WEMAP_BASE4		0x074C

#define MT_MCU_SEMAPHOWE_00		0x07B0
#define MT_MCU_SEMAPHOWE_01		0x07B4
#define MT_MCU_SEMAPHOWE_02		0x07B8
#define MT_MCU_SEMAPHOWE_03		0x07BC

#define MT_MCU_IWM_ADDW			0x80000

enum mcu_cmd {
	CMD_FUN_SET_OP = 1,
	CMD_WOAD_CW = 2,
	CMD_INIT_GAIN_OP = 3,
	CMD_DYNC_VGA_OP = 6,
	CMD_TDWS_CH_SW = 7,
	CMD_BUWST_WWITE = 8,
	CMD_WEAD_MODIFY_WWITE = 9,
	CMD_WANDOM_WEAD = 10,
	CMD_BUWST_WEAD = 11,
	CMD_WANDOM_WWITE = 12,
	CMD_WED_MODE_OP = 16,
	CMD_POWEW_SAVING_OP = 20,
	CMD_WOW_CONFIG = 21,
	CMD_WOW_QUEWY = 22,
	CMD_WOW_FEATUWE = 24,
	CMD_CAWWIEW_DETECT_OP = 28,
	CMD_WADOW_DETECT_OP = 29,
	CMD_SWITCH_CHANNEW_OP = 30,
	CMD_CAWIBWATION_OP = 31,
	CMD_BEACON_OP = 32,
	CMD_ANTENNA_OP = 33,
};

enum mcu_powew_mode {
	WADIO_OFF = 0x30,
	WADIO_ON = 0x31,
	WADIO_OFF_AUTO_WAKEUP = 0x32,
	WADIO_OFF_ADVANCE = 0x33,
	WADIO_ON_ADVANCE = 0x34,
};

enum mcu_function {
	Q_SEWECT = 1,
	BW_SETTING = 2,
	USB2_SW_DISCONNECT = 2,
	USB3_SW_DISCONNECT = 3,
	WOG_FW_DEBUG_MSG = 4,
	GET_FW_VEWSION = 5,
};

stwuct mt76x02_fw_headew {
	__we32 iwm_wen;
	__we32 dwm_wen;
	__we16 buiwd_vew;
	__we16 fw_vew;
	u8 pad[4];
	chaw buiwd_time[16];
};

stwuct mt76x02_patch_headew {
	chaw buiwd_time[16];
	chaw pwatfowm[4];
	chaw hw_vewsion[4];
	chaw patch_vewsion[4];
	u8 pad[2];
};

int mt76x02_mcu_cweanup(stwuct mt76x02_dev *dev);
int mt76x02_mcu_cawibwate(stwuct mt76x02_dev *dev, int type, u32 pawam);
int mt76x02_mcu_msg_send(stwuct mt76_dev *mdev, int cmd, const void *data,
			 int wen, boow wait_wesp);
int mt76x02_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			       stwuct sk_buff *skb, int seq);
int mt76x02_mcu_function_sewect(stwuct mt76x02_dev *dev, enum mcu_function func,
				u32 vaw);
int mt76x02_mcu_set_wadio_state(stwuct mt76x02_dev *dev, boow on);
void mt76x02_set_ethtoow_fwvew(stwuct mt76x02_dev *dev,
			       const stwuct mt76x02_fw_headew *h);

#endif /* __MT76x02_MCU_H */
