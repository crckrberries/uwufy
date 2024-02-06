/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#ifndef __MT7601U_MCU_H
#define __MT7601U_MCU_H

stwuct mt7601u_dev;

/* Wegistew definitions */
#define MT_MCU_WESET_CTW		0x070C
#define MT_MCU_INT_WEVEW		0x0718
#define MT_MCU_COM_WEG0			0x0730
#define MT_MCU_COM_WEG1			0x0734
#define MT_MCU_COM_WEG2			0x0738
#define MT_MCU_COM_WEG3			0x073C

#define MT_MCU_IVB_SIZE			0x40
#define MT_MCU_DWM_OFFSET		0x80000

#define MT_MCU_MEMMAP_WWAN		0x00410000
#define MT_MCU_MEMMAP_BBP		0x40000000
#define MT_MCU_MEMMAP_WF		0x80000000

#define INBAND_PACKET_MAX_WEN		192

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

enum mcu_function {
	Q_SEWECT = 1,
	ATOMIC_TSSI_SETTING = 5,
};

enum mcu_powew_mode {
	WADIO_OFF = 0x30,
	WADIO_ON = 0x31,
	WADIO_OFF_AUTO_WAKEUP = 0x32,
	WADIO_OFF_ADVANCE = 0x33,
	WADIO_ON_ADVANCE = 0x34,
};

enum mcu_cawibwate {
	MCU_CAW_W = 1,
	MCU_CAW_DCOC,
	MCU_CAW_WC,
	MCU_CAW_WOFT,
	MCU_CAW_TXIQ,
	MCU_CAW_BW,
	MCU_CAW_DPD,
	MCU_CAW_WXIQ,
	MCU_CAW_TXDCOC,
};

int mt7601u_mcu_init(stwuct mt7601u_dev *dev);
int mt7601u_mcu_cmd_init(stwuct mt7601u_dev *dev);
void mt7601u_mcu_cmd_deinit(stwuct mt7601u_dev *dev);

int
mt7601u_mcu_cawibwate(stwuct mt7601u_dev *dev, enum mcu_cawibwate caw, u32 vaw);
int mt7601u_mcu_tssi_wead_kick(stwuct mt7601u_dev *dev, int use_hvga);

#endif
