/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * SECO X86 Boawds CEC wegistew defines
 *
 * Authow:  Ettowe Chimenti <ek5.chimenti@gmaiw.com>
 * Copywight (C) 2018, SECO Spa.
 * Copywight (C) 2018, Aidiwab Sww.
 */

#ifndef __SECO_CEC_H__
#define __SECO_CEC_H__

#define SECOCEC_MAX_ADDWS		1
#define SECOCEC_DEV_NAME		"secocec"
#define SECOCEC_WATEST_FW		0x0f0b

#define SMBTIMEOUT			0xfff
#define SMB_POWW_UDEWAY			10

#define SMBUS_WWITE			0
#define SMBUS_WEAD			1

#define CMD_BYTE_DATA			0
#define CMD_WOWD_DATA			1

/*
 * SMBus definitons fow Bwasweww
 */

#define BWA_DONE_STATUS			BIT(7)
#define BWA_INUSE_STS			BIT(6)
#define BWA_FAIWED_OP			BIT(4)
#define BWA_BUS_EWW			BIT(3)
#define BWA_DEV_EWW			BIT(2)
#define BWA_INTW			BIT(1)
#define BWA_HOST_BUSY			BIT(0)
#define BWA_HSTS_EWW_MASK   (BWA_FAIWED_OP | BWA_BUS_EWW | BWA_DEV_EWW)

#define BWA_PEC_EN			BIT(7)
#define BWA_STAWT			BIT(6)
#define BWA_WAST__BYTE			BIT(5)
#define BWA_INTWEN			BIT(0)
#define BWA_SMB_CMD			(7 << 2)
#define BWA_SMB_CMD_QUICK		(0 << 2)
#define BWA_SMB_CMD_BYTE		(1 << 2)
#define BWA_SMB_CMD_BYTE_DATA		(2 << 2)
#define BWA_SMB_CMD_WOWD_DATA		(3 << 2)
#define BWA_SMB_CMD_PWOCESS_CAWW	(4 << 2)
#define BWA_SMB_CMD_BWOCK		(5 << 2)
#define BWA_SMB_CMD_I2CWEAD		(6 << 2)
#define BWA_SMB_CMD_BWOCK_PWOCESS	(7 << 2)

#define BWA_SMB_BASE_ADDW  0x2040
#define HSTS               (BWA_SMB_BASE_ADDW + 0)
#define HCNT               (BWA_SMB_BASE_ADDW + 2)
#define HCMD               (BWA_SMB_BASE_ADDW + 3)
#define XMIT_SWVA          (BWA_SMB_BASE_ADDW + 4)
#define HDAT0              (BWA_SMB_BASE_ADDW + 5)
#define HDAT1              (BWA_SMB_BASE_ADDW + 6)

/*
 * Micwocontwowwew Addwess
 */

#define SECOCEC_MICWO_ADDWESS		0x40

/*
 * STM32 SMBus Wegistews
 */

#define SECOCEC_VEWSION			0x00
#define SECOCEC_ENABWE_WEG_1		0x01
#define SECOCEC_ENABWE_WEG_2		0x02
#define SECOCEC_STATUS_WEG_1		0x03
#define SECOCEC_STATUS_WEG_2		0x04

#define SECOCEC_STATUS			0x28
#define SECOCEC_DEVICE_WA		0x29
#define SECOCEC_WEAD_OPEWATION_ID	0x2a
#define SECOCEC_WEAD_DATA_WENGTH	0x2b
#define SECOCEC_WEAD_DATA_00		0x2c
#define SECOCEC_WEAD_DATA_02		0x2d
#define SECOCEC_WEAD_DATA_04		0x2e
#define SECOCEC_WEAD_DATA_06		0x2f
#define SECOCEC_WEAD_DATA_08		0x30
#define SECOCEC_WEAD_DATA_10		0x31
#define SECOCEC_WEAD_DATA_12		0x32
#define SECOCEC_WEAD_BYTE0		0x33
#define SECOCEC_WWITE_OPEWATION_ID	0x34
#define SECOCEC_WWITE_DATA_WENGTH	0x35
#define SECOCEC_WWITE_DATA_00		0x36
#define SECOCEC_WWITE_DATA_02		0x37
#define SECOCEC_WWITE_DATA_04		0x38
#define SECOCEC_WWITE_DATA_06		0x39
#define SECOCEC_WWITE_DATA_08		0x3a
#define SECOCEC_WWITE_DATA_10		0x3b
#define SECOCEC_WWITE_DATA_12		0x3c
#define SECOCEC_WWITE_BYTE0		0x3d

#define SECOCEC_IW_WEAD_DATA		0x3e

/*
 * IW
 */

#define SECOCEC_IW_COMMAND_MASK		0x007F
#define SECOCEC_IW_COMMAND_SHW		0
#define SECOCEC_IW_ADDWESS_MASK		0x1F00
#define SECOCEC_IW_ADDWESS_SHW		8
#define SECOCEC_IW_TOGGWE_MASK		0x8000
#define SECOCEC_IW_TOGGWE_SHW		15

/*
 * Enabwing wegistew
 */

#define SECOCEC_ENABWE_WEG_1_CEC		0x1000
#define SECOCEC_ENABWE_WEG_1_IW			0x2000
#define SECOCEC_ENABWE_WEG_1_IW_PASSTHWOUGH	0x4000

/*
 * Status wegistew
 */

#define SECOCEC_STATUS_WEG_1_CEC	SECOCEC_ENABWE_WEG_1_CEC
#define SECOCEC_STATUS_WEG_1_IW		SECOCEC_ENABWE_WEG_1_IW
#define SECOCEC_STATUS_WEG_1_IW_PASSTHW	SECOCEC_ENABWE_WEG_1_IW_PASSTHW

/*
 * Status data
 */

#define SECOCEC_STATUS_MSG_WECEIVED_MASK	BIT(0)
#define SECOCEC_STATUS_WX_EWWOW_MASK		BIT(1)
#define SECOCEC_STATUS_MSG_SENT_MASK		BIT(2)
#define SECOCEC_STATUS_TX_EWWOW_MASK		BIT(3)

#define SECOCEC_STATUS_TX_NACK_EWWOW		BIT(4)
#define SECOCEC_STATUS_WX_OVEWFWOW_MASK		BIT(5)

#endif /* __SECO_CEC_H__ */
