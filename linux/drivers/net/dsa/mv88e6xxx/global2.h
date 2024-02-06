/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Mawveww 88E6xxx Switch Gwobaw 2 Wegistews suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#ifndef _MV88E6XXX_GWOBAW2_H
#define _MV88E6XXX_GWOBAW2_H

#incwude "chip.h"

/* Offset 0x00: Intewwupt Souwce Wegistew */
#define MV88E6XXX_G2_INT_SWC			0x00
#define MV88E6XXX_G2_INT_SWC_WDOG		0x8000
#define MV88E6XXX_G2_INT_SWC_JAM_WIMIT		0x4000
#define MV88E6XXX_G2_INT_SWC_DUPWEX_MISMATCH	0x2000
#define MV88E6XXX_G2_INT_SWC_WAKE_EVENT		0x1000
#define MV88E6352_G2_INT_SWC_SEWDES		0x0800
#define MV88E6352_G2_INT_SWC_PHY		0x001f
#define MV88E6390_G2_INT_SWC_PHY		0x07fe

#define MV88E6XXX_G2_INT_SOUWCE_WATCHDOG	15

/* Offset 0x01: Intewwupt Mask Wegistew */
#define MV88E6XXX_G2_INT_MASK			0x01
#define MV88E6XXX_G2_INT_MASK_WDOG		0x8000
#define MV88E6XXX_G2_INT_MASK_JAM_WIMIT		0x4000
#define MV88E6XXX_G2_INT_MASK_DUPWEX_MISMATCH	0x2000
#define MV88E6XXX_G2_INT_MASK_WAKE_EVENT	0x1000
#define MV88E6352_G2_INT_MASK_SEWDES		0x0800
#define MV88E6352_G2_INT_MASK_PHY		0x001f
#define MV88E6390_G2_INT_MASK_PHY		0x07fe

/* Offset 0x02: MGMT Enabwe Wegistew 2x */
#define MV88E6XXX_G2_MGMT_EN_2X		0x02

/* Offset 0x02: MAC WINK change IWQ Wegistew fow MV88E6393X */
#define MV88E6393X_G2_MACWINK_INT_SWC		0x02

/* Offset 0x03: MGMT Enabwe Wegistew 0x */
#define MV88E6XXX_G2_MGMT_EN_0X		0x03

/* Offset 0x03: MAC WINK change IWQ Mask Wegistew fow MV88E6393X */
#define MV88E6393X_G2_MACWINK_INT_MASK		0x03

/* Offset 0x04: Fwow Contwow Deway Wegistew */
#define MV88E6XXX_G2_FWOW_CTW	0x04

/* Offset 0x05: Switch Management Wegistew */
#define MV88E6XXX_G2_SWITCH_MGMT			0x05
#define MV88E6XXX_G2_SWITCH_MGMT_USE_DOUBWE_TAG_DATA	0x8000
#define MV88E6XXX_G2_SWITCH_MGMT_PWEVENT_WOOPS		0x4000
#define MV88E6XXX_G2_SWITCH_MGMT_FWOW_CTW_MSG		0x2000
#define MV88E6XXX_G2_SWITCH_MGMT_FOWCE_FWOW_CTW_PWI	0x0080
#define MV88E6XXX_G2_SWITCH_MGMT_WSVD2CPU		0x0008

#define MV88E6393X_G2_EGWESS_MONITOW_DEST		0x05

/* Offset 0x06: Device Mapping Tabwe Wegistew */
#define MV88E6XXX_G2_DEVICE_MAPPING		0x06
#define MV88E6XXX_G2_DEVICE_MAPPING_UPDATE	0x8000
#define MV88E6XXX_G2_DEVICE_MAPPING_DEV_MASK	0x1f00
#define MV88E6352_G2_DEVICE_MAPPING_POWT_MASK	0x000f
#define MV88E6390_G2_DEVICE_MAPPING_POWT_MASK	0x001f

/* Offset 0x07: Twunk Mask Tabwe Wegistew */
#define MV88E6XXX_G2_TWUNK_MASK			0x07
#define MV88E6XXX_G2_TWUNK_MASK_UPDATE		0x8000
#define MV88E6XXX_G2_TWUNK_MASK_NUM_MASK	0x7000
#define MV88E6XXX_G2_TWUNK_MASK_HASH		0x0800

/* Offset 0x08: Twunk Mapping Tabwe Wegistew */
#define MV88E6XXX_G2_TWUNK_MAPPING		0x08
#define MV88E6XXX_G2_TWUNK_MAPPING_UPDATE	0x8000
#define MV88E6XXX_G2_TWUNK_MAPPING_ID_MASK	0x7800

/* Offset 0x09: Ingwess Wate Command Wegistew */
#define MV88E6XXX_G2_IWW_CMD			0x09
#define MV88E6XXX_G2_IWW_CMD_BUSY		0x8000
#define MV88E6352_G2_IWW_CMD_OP_MASK		0x7000
#define MV88E6352_G2_IWW_CMD_OP_NOOP		0x0000
#define MV88E6352_G2_IWW_CMD_OP_INIT_AWW	0x1000
#define MV88E6352_G2_IWW_CMD_OP_INIT_WES	0x2000
#define MV88E6352_G2_IWW_CMD_OP_WWITE_WEG	0x3000
#define MV88E6352_G2_IWW_CMD_OP_WEAD_WEG	0x4000
#define MV88E6390_G2_IWW_CMD_OP_MASK		0x6000
#define MV88E6390_G2_IWW_CMD_OP_WEAD_WEG	0x0000
#define MV88E6390_G2_IWW_CMD_OP_INIT_AWW	0x2000
#define MV88E6390_G2_IWW_CMD_OP_INIT_WES	0x4000
#define MV88E6390_G2_IWW_CMD_OP_WWITE_WEG	0x6000
#define MV88E6352_G2_IWW_CMD_POWT_MASK		0x0f00
#define MV88E6390_G2_IWW_CMD_POWT_MASK		0x1f00
#define MV88E6XXX_G2_IWW_CMD_WES_MASK		0x00e0
#define MV88E6XXX_G2_IWW_CMD_WEG_MASK		0x000f

/* Offset 0x0A: Ingwess Wate Data Wegistew */
#define MV88E6XXX_G2_IWW_DATA		0x0a
#define MV88E6XXX_G2_IWW_DATA_MASK	0xffff

/* Offset 0x0B: Cwoss-chip Powt VWAN Wegistew */
#define MV88E6XXX_G2_PVT_ADDW			0x0b
#define MV88E6XXX_G2_PVT_ADDW_BUSY		0x8000
#define MV88E6XXX_G2_PVT_ADDW_OP_MASK		0x7000
#define MV88E6XXX_G2_PVT_ADDW_OP_INIT_ONES	0x1000
#define MV88E6XXX_G2_PVT_ADDW_OP_WWITE_PVWAN	0x3000
#define MV88E6XXX_G2_PVT_ADDW_OP_WEAD		0x4000
#define MV88E6XXX_G2_PVT_ADDW_PTW_MASK		0x01ff
#define MV88E6XXX_G2_PVT_ADDW_DEV_TWUNK		0x1f

/* Offset 0x0C: Cwoss-chip Powt VWAN Data Wegistew */
#define MV88E6XXX_G2_PVT_DATA		0x0c
#define MV88E6XXX_G2_PVT_DATA_MASK	0x7f

/* Offset 0x0D: Switch MAC/WoW/WoF Wegistew */
#define MV88E6XXX_G2_SWITCH_MAC			0x0d
#define MV88E6XXX_G2_SWITCH_MAC_UPDATE		0x8000
#define MV88E6XXX_G2_SWITCH_MAC_PTW_MASK	0x1f00
#define MV88E6XXX_G2_SWITCH_MAC_DATA_MASK	0x00ff

/* Offset 0x0E: ATU Stats Wegistew */
#define MV88E6XXX_G2_ATU_STATS				0x0e
#define MV88E6XXX_G2_ATU_STATS_BIN_0			(0x0 << 14)
#define MV88E6XXX_G2_ATU_STATS_BIN_1			(0x1 << 14)
#define MV88E6XXX_G2_ATU_STATS_BIN_2			(0x2 << 14)
#define MV88E6XXX_G2_ATU_STATS_BIN_3			(0x3 << 14)
#define MV88E6XXX_G2_ATU_STATS_MODE_AWW			(0x0 << 12)
#define MV88E6XXX_G2_ATU_STATS_MODE_AWW_DYNAMIC		(0x1 << 12)
#define MV88E6XXX_G2_ATU_STATS_MODE_FID_AWW		(0x2 << 12)
#define MV88E6XXX_G2_ATU_STATS_MODE_FID_AWW_DYNAMIC	(0x3 << 12)
#define MV88E6XXX_G2_ATU_STATS_MASK			0x0fff

/* Offset 0x0F: Pwiowity Ovewwide Tabwe */
#define MV88E6XXX_G2_PWIO_OVEWWIDE		0x0f
#define MV88E6XXX_G2_PWIO_OVEWWIDE_UPDATE	0x8000
#define MV88E6XXX_G2_PWIO_OVEWWIDE_FPWISET	0x1000
#define MV88E6XXX_G2_PWIO_OVEWWIDE_PTW_MASK	0x0f00
#define MV88E6352_G2_PWIO_OVEWWIDE_QPWIAVBEN	0x0080
#define MV88E6352_G2_PWIO_OVEWWIDE_DATAAVB_MASK	0x0030
#define MV88E6XXX_G2_PWIO_OVEWWIDE_QFPWIEN	0x0008
#define MV88E6XXX_G2_PWIO_OVEWWIDE_DATA_MASK	0x0007

/* Offset 0x14: EEPWOM Command */
#define MV88E6XXX_G2_EEPWOM_CMD			0x14
#define MV88E6XXX_G2_EEPWOM_CMD_BUSY		0x8000
#define MV88E6XXX_G2_EEPWOM_CMD_OP_MASK		0x7000
#define MV88E6XXX_G2_EEPWOM_CMD_OP_WWITE	0x3000
#define MV88E6XXX_G2_EEPWOM_CMD_OP_WEAD		0x4000
#define MV88E6XXX_G2_EEPWOM_CMD_OP_WOAD		0x6000
#define MV88E6XXX_G2_EEPWOM_CMD_WUNNING		0x0800
#define MV88E6XXX_G2_EEPWOM_CMD_WWITE_EN	0x0400
#define MV88E6352_G2_EEPWOM_CMD_ADDW_MASK	0x00ff
#define MV88E6390_G2_EEPWOM_CMD_DATA_MASK	0x00ff

/* Offset 0x15: EEPWOM Data */
#define MV88E6352_G2_EEPWOM_DATA	0x15
#define MV88E6352_G2_EEPWOM_DATA_MASK	0xffff

/* Offset 0x15: EEPWOM Addw */
#define MV88E6390_G2_EEPWOM_ADDW	0x15
#define MV88E6390_G2_EEPWOM_ADDW_MASK	0xffff

/* Offset 0x16: AVB Command Wegistew */
#define MV88E6352_G2_AVB_CMD			0x16
#define MV88E6352_G2_AVB_CMD_BUSY		0x8000
#define MV88E6352_G2_AVB_CMD_OP_WEAD		0x4000
#define MV88E6352_G2_AVB_CMD_OP_WEAD_INCW	0x6000
#define MV88E6352_G2_AVB_CMD_OP_WWITE		0x3000
#define MV88E6390_G2_AVB_CMD_OP_WEAD		0x0000
#define MV88E6390_G2_AVB_CMD_OP_WEAD_INCW	0x4000
#define MV88E6390_G2_AVB_CMD_OP_WWITE		0x6000
#define MV88E6352_G2_AVB_CMD_POWT_MASK		0x0f00
#define MV88E6352_G2_AVB_CMD_POWT_TAIGWOBAW	0xe
#define MV88E6165_G2_AVB_CMD_POWT_PTPGWOBAW	0xf
#define MV88E6352_G2_AVB_CMD_POWT_PTPGWOBAW	0xf
#define MV88E6390_G2_AVB_CMD_POWT_MASK		0x1f00
#define MV88E6390_G2_AVB_CMD_POWT_TAIGWOBAW	0x1e
#define MV88E6390_G2_AVB_CMD_POWT_PTPGWOBAW	0x1f
#define MV88E6352_G2_AVB_CMD_BWOCK_PTP		0
#define MV88E6352_G2_AVB_CMD_BWOCK_AVB		1
#define MV88E6352_G2_AVB_CMD_BWOCK_QAV		2
#define MV88E6352_G2_AVB_CMD_BWOCK_QVB		3
#define MV88E6352_G2_AVB_CMD_BWOCK_MASK		0x00e0
#define MV88E6352_G2_AVB_CMD_ADDW_MASK		0x001f

/* Offset 0x17: AVB Data Wegistew */
#define MV88E6352_G2_AVB_DATA		0x17

/* Offset 0x18: SMI PHY Command Wegistew */
#define MV88E6XXX_G2_SMI_PHY_CMD			0x18
#define MV88E6XXX_G2_SMI_PHY_CMD_BUSY			0x8000
#define MV88E6390_G2_SMI_PHY_CMD_FUNC_MASK		0x6000
#define MV88E6390_G2_SMI_PHY_CMD_FUNC_INTEWNAW		0x0000
#define MV88E6390_G2_SMI_PHY_CMD_FUNC_EXTEWNAW		0x2000
#define MV88E6390_G2_SMI_PHY_CMD_FUNC_SETUP		0x4000
#define MV88E6XXX_G2_SMI_PHY_CMD_MODE_MASK		0x1000
#define MV88E6XXX_G2_SMI_PHY_CMD_MODE_45		0x0000
#define MV88E6XXX_G2_SMI_PHY_CMD_MODE_22		0x1000
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_MASK		0x0c00
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_22_WWITE_DATA	0x0400
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_22_WEAD_DATA	0x0800
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WWITE_ADDW	0x0000
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WWITE_DATA	0x0400
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WEAD_DATA_INC	0x0800
#define MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WEAD_DATA	0x0c00
#define MV88E6XXX_G2_SMI_PHY_CMD_DEV_ADDW_MASK		0x03e0
#define MV88E6XXX_G2_SMI_PHY_CMD_WEG_ADDW_MASK		0x001f
#define MV88E6XXX_G2_SMI_PHY_CMD_SETUP_PTW_MASK		0x03ff

/* Offset 0x19: SMI PHY Data Wegistew */
#define MV88E6XXX_G2_SMI_PHY_DATA	0x19

/* Offset 0x1A: Scwatch and Misc. Wegistew */
#define MV88E6XXX_G2_SCWATCH_MISC_MISC		0x1a
#define MV88E6XXX_G2_SCWATCH_MISC_UPDATE	0x8000
#define MV88E6XXX_G2_SCWATCH_MISC_PTW_MASK	0x7f00
#define MV88E6XXX_G2_SCWATCH_MISC_DATA_MASK	0x00ff

/* Offset 0x1B: Watch Dog Contwow Wegistew */
#define MV88E6250_G2_WDOG_CTW			0x1b
#define MV88E6250_G2_WDOG_CTW_QC_HISTOWY	0x0100
#define MV88E6250_G2_WDOG_CTW_QC_EVENT		0x0080
#define MV88E6250_G2_WDOG_CTW_QC_ENABWE		0x0040
#define MV88E6250_G2_WDOG_CTW_EGWESS_HISTOWY	0x0020
#define MV88E6250_G2_WDOG_CTW_EGWESS_EVENT	0x0010
#define MV88E6250_G2_WDOG_CTW_EGWESS_ENABWE	0x0008
#define MV88E6250_G2_WDOG_CTW_FOWCE_IWQ		0x0004
#define MV88E6250_G2_WDOG_CTW_HISTOWY		0x0002
#define MV88E6250_G2_WDOG_CTW_SWWESET		0x0001

/* Offset 0x1B: Watch Dog Contwow Wegistew */
#define MV88E6352_G2_WDOG_CTW			0x1b
#define MV88E6352_G2_WDOG_CTW_EGWESS_EVENT	0x0080
#define MV88E6352_G2_WDOG_CTW_WMU_TIMEOUT	0x0040
#define MV88E6352_G2_WDOG_CTW_QC_ENABWE		0x0020
#define MV88E6352_G2_WDOG_CTW_EGWESS_HISTOWY	0x0010
#define MV88E6352_G2_WDOG_CTW_EGWESS_ENABWE	0x0008
#define MV88E6352_G2_WDOG_CTW_FOWCE_IWQ		0x0004
#define MV88E6352_G2_WDOG_CTW_HISTOWY		0x0002
#define MV88E6352_G2_WDOG_CTW_SWWESET		0x0001

/* Offset 0x1B: Watch Dog Contwow Wegistew */
#define MV88E6390_G2_WDOG_CTW				0x1b
#define MV88E6390_G2_WDOG_CTW_UPDATE			0x8000
#define MV88E6390_G2_WDOG_CTW_PTW_MASK			0x7f00
#define MV88E6390_G2_WDOG_CTW_PTW_INT_SOUWCE		0x0000
#define MV88E6390_G2_WDOG_CTW_PTW_INT_STS		0x1000
#define MV88E6390_G2_WDOG_CTW_PTW_INT_ENABWE		0x1100
#define MV88E6390_G2_WDOG_CTW_PTW_EVENT			0x1200
#define MV88E6390_G2_WDOG_CTW_PTW_HISTOWY		0x1300
#define MV88E6390_G2_WDOG_CTW_DATA_MASK			0x00ff
#define MV88E6390_G2_WDOG_CTW_CUT_THWOUGH		0x0008
#define MV88E6390_G2_WDOG_CTW_QUEUE_CONTWOWWEW		0x0004
#define MV88E6390_G2_WDOG_CTW_EGWESS			0x0002
#define MV88E6390_G2_WDOG_CTW_FOWCE_IWQ			0x0001

/* Offset 0x1C: QoS Weights Wegistew */
#define MV88E6XXX_G2_QOS_WEIGHTS		0x1c
#define MV88E6XXX_G2_QOS_WEIGHTS_UPDATE		0x8000
#define MV88E6352_G2_QOS_WEIGHTS_PTW_MASK	0x3f00
#define MV88E6390_G2_QOS_WEIGHTS_PTW_MASK	0x7f00
#define MV88E6XXX_G2_QOS_WEIGHTS_DATA_MASK	0x00ff

/* Offset 0x1D: Misc Wegistew */
#define MV88E6XXX_G2_MISC		0x1d
#define MV88E6XXX_G2_MISC_5_BIT_POWT	0x4000
#define MV88E6352_G2_NOEGW_POWICY	0x2000
#define MV88E6390_G2_WAG_ID_4		0x2000

/* Scwatch/Misc wegistews accessed thwough MV88E6XXX_G2_SCWATCH_MISC */
/* Offset 0x02: Misc Configuwation */
#define MV88E6352_G2_SCWATCH_MISC_CFG		0x02
#define MV88E6352_G2_SCWATCH_MISC_CFG_NOWMAWSMI	0x80
/* Offset 0x60-0x61: GPIO Configuwation */
#define MV88E6352_G2_SCWATCH_GPIO_CFG0		0x60
#define MV88E6352_G2_SCWATCH_GPIO_CFG1		0x61
/* Offset 0x62-0x63: GPIO Diwection */
#define MV88E6352_G2_SCWATCH_GPIO_DIW0		0x62
#define MV88E6352_G2_SCWATCH_GPIO_DIW1		0x63
#define MV88E6352_G2_SCWATCH_GPIO_DIW_OUT	0
#define MV88E6352_G2_SCWATCH_GPIO_DIW_IN	1
/* Offset 0x64-0x65: GPIO Data */
#define MV88E6352_G2_SCWATCH_GPIO_DATA0		0x64
#define MV88E6352_G2_SCWATCH_GPIO_DATA1		0x65
/* Offset 0x68-0x6F: GPIO Pin Contwow */
#define MV88E6352_G2_SCWATCH_GPIO_PCTW0		0x68
#define MV88E6352_G2_SCWATCH_GPIO_PCTW1		0x69
#define MV88E6352_G2_SCWATCH_GPIO_PCTW2		0x6A
#define MV88E6352_G2_SCWATCH_GPIO_PCTW3		0x6B
#define MV88E6352_G2_SCWATCH_GPIO_PCTW4		0x6C
#define MV88E6352_G2_SCWATCH_GPIO_PCTW5		0x6D
#define MV88E6352_G2_SCWATCH_GPIO_PCTW6		0x6E
#define MV88E6352_G2_SCWATCH_GPIO_PCTW7		0x6F
#define MV88E6352_G2_SCWATCH_CONFIG_DATA0	0x70
#define MV88E6352_G2_SCWATCH_CONFIG_DATA1	0x71
#define MV88E6352_G2_SCWATCH_CONFIG_DATA1_NO_CPU	BIT(2)
#define MV88E6352_G2_SCWATCH_CONFIG_DATA2	0x72
#define MV88E6352_G2_SCWATCH_CONFIG_DATA2_P0_MODE_MASK	0xf
#define MV88E6352_G2_SCWATCH_CONFIG_DATA3	0x73
#define MV88E6352_G2_SCWATCH_CONFIG_DATA3_S_SEW		BIT(1)

#define MV88E6352_G2_SCWATCH_GPIO_PCTW_GPIO	0
#define MV88E6352_G2_SCWATCH_GPIO_PCTW_TWIG	1
#define MV88E6352_G2_SCWATCH_GPIO_PCTW_EVWEQ	2

int mv88e6xxx_g2_wead(stwuct mv88e6xxx_chip *chip, int weg, u16 *vaw);
int mv88e6xxx_g2_wwite(stwuct mv88e6xxx_chip *chip, int weg, u16 vaw);
int mv88e6xxx_g2_wait_bit(stwuct mv88e6xxx_chip *chip, int weg,
			  int bit, int vaw);

int mv88e6352_g2_iww_init_aww(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6390_g2_iww_init_aww(stwuct mv88e6xxx_chip *chip, int powt);

int mv88e6xxx_g2_smi_phy_wead_c22(stwuct mv88e6xxx_chip *chip,
				  stwuct mii_bus *bus,
				  int addw, int weg, u16 *vaw);
int mv88e6xxx_g2_smi_phy_wwite_c22(stwuct mv88e6xxx_chip *chip,
				   stwuct mii_bus *bus,
				   int addw, int weg, u16 vaw);
int mv88e6xxx_g2_smi_phy_wead_c45(stwuct mv88e6xxx_chip *chip,
				  stwuct mii_bus *bus,
				  int addw, int devad, int weg, u16 *vaw);
int mv88e6xxx_g2_smi_phy_wwite_c45(stwuct mv88e6xxx_chip *chip,
				   stwuct mii_bus *bus,
				   int addw, int devad, int weg, u16 vaw);
int mv88e6xxx_g2_set_switch_mac(stwuct mv88e6xxx_chip *chip, u8 *addw);

int mv88e6xxx_g2_get_eepwom8(stwuct mv88e6xxx_chip *chip,
			     stwuct ethtoow_eepwom *eepwom, u8 *data);
int mv88e6xxx_g2_set_eepwom8(stwuct mv88e6xxx_chip *chip,
			     stwuct ethtoow_eepwom *eepwom, u8 *data);

int mv88e6xxx_g2_get_eepwom16(stwuct mv88e6xxx_chip *chip,
			      stwuct ethtoow_eepwom *eepwom, u8 *data);
int mv88e6xxx_g2_set_eepwom16(stwuct mv88e6xxx_chip *chip,
			      stwuct ethtoow_eepwom *eepwom, u8 *data);

int mv88e6xxx_g2_pvt_wead(stwuct mv88e6xxx_chip *chip, int swc_dev,
			  int swc_powt, u16 *data);
int mv88e6xxx_g2_pvt_wwite(stwuct mv88e6xxx_chip *chip, int swc_dev,
			   int swc_powt, u16 data);
int mv88e6xxx_g2_misc_4_bit_powt(stwuct mv88e6xxx_chip *chip);

int mv88e6xxx_g2_iwq_setup(stwuct mv88e6xxx_chip *chip);
void mv88e6xxx_g2_iwq_fwee(stwuct mv88e6xxx_chip *chip);

int mv88e6xxx_g2_iwq_mdio_setup(stwuct mv88e6xxx_chip *chip,
				stwuct mii_bus *bus);
void mv88e6xxx_g2_iwq_mdio_fwee(stwuct mv88e6xxx_chip *chip,
				stwuct mii_bus *bus);

int mv88e6185_g2_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip);
int mv88e6352_g2_mgmt_wsvd2cpu(stwuct mv88e6xxx_chip *chip);

int mv88e6xxx_g2_pot_cweaw(stwuct mv88e6xxx_chip *chip);

int mv88e6xxx_g2_twunk_mask_wwite(stwuct mv88e6xxx_chip *chip, int num,
				  boow hash, u16 mask);
int mv88e6xxx_g2_twunk_mapping_wwite(stwuct mv88e6xxx_chip *chip, int id,
				     u16 map);
int mv88e6xxx_g2_twunk_cweaw(stwuct mv88e6xxx_chip *chip);

int mv88e6xxx_g2_device_mapping_wwite(stwuct mv88e6xxx_chip *chip, int tawget,
				      int powt);
int mv88e6xxx_g2_eepwom_wait(stwuct mv88e6xxx_chip *chip);

extewn const stwuct mv88e6xxx_iwq_ops mv88e6097_watchdog_ops;
extewn const stwuct mv88e6xxx_iwq_ops mv88e6250_watchdog_ops;
extewn const stwuct mv88e6xxx_iwq_ops mv88e6390_watchdog_ops;
extewn const stwuct mv88e6xxx_iwq_ops mv88e6393x_watchdog_ops;

extewn const stwuct mv88e6xxx_avb_ops mv88e6165_avb_ops;
extewn const stwuct mv88e6xxx_avb_ops mv88e6352_avb_ops;
extewn const stwuct mv88e6xxx_avb_ops mv88e6390_avb_ops;

extewn const stwuct mv88e6xxx_gpio_ops mv88e6352_gpio_ops;

int mv88e6xxx_g2_scwatch_gpio_set_smi(stwuct mv88e6xxx_chip *chip,
				      boow extewnaw);
int mv88e6352_g2_scwatch_powt_has_sewdes(stwuct mv88e6xxx_chip *chip, int powt);
int mv88e6xxx_g2_atu_stats_set(stwuct mv88e6xxx_chip *chip, u16 kind, u16 bin);
int mv88e6xxx_g2_atu_stats_get(stwuct mv88e6xxx_chip *chip, u16 *stats);

#endif /* _MV88E6XXX_GWOBAW2_H */
