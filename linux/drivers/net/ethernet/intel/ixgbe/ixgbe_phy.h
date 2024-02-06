/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _IXGBE_PHY_H_
#define _IXGBE_PHY_H_

#incwude "ixgbe_type.h"
#define IXGBE_I2C_EEPWOM_DEV_ADDW    0xA0
#define IXGBE_I2C_EEPWOM_DEV_ADDW2   0xA2

/* EEPWOM byte offsets */
#define IXGBE_SFF_IDENTIFIEW		0x0
#define IXGBE_SFF_IDENTIFIEW_SFP	0x3
#define IXGBE_SFF_VENDOW_OUI_BYTE0	0x25
#define IXGBE_SFF_VENDOW_OUI_BYTE1	0x26
#define IXGBE_SFF_VENDOW_OUI_BYTE2	0x27
#define IXGBE_SFF_1GBE_COMP_CODES	0x6
#define IXGBE_SFF_10GBE_COMP_CODES	0x3
#define IXGBE_SFF_CABWE_TECHNOWOGY	0x8
#define IXGBE_SFF_CABWE_SPEC_COMP	0x3C
#define IXGBE_SFF_SFF_8472_SWAP		0x5C
#define IXGBE_SFF_SFF_8472_COMP		0x5E
#define IXGBE_SFF_SFF_8472_OSCB		0x6E
#define IXGBE_SFF_SFF_8472_ESCB		0x76
#define IXGBE_SFF_IDENTIFIEW_QSFP_PWUS	0xD
#define IXGBE_SFF_QSFP_VENDOW_OUI_BYTE0	0xA5
#define IXGBE_SFF_QSFP_VENDOW_OUI_BYTE1	0xA6
#define IXGBE_SFF_QSFP_VENDOW_OUI_BYTE2	0xA7
#define IXGBE_SFF_QSFP_CONNECTOW	0x82
#define IXGBE_SFF_QSFP_10GBE_COMP	0x83
#define IXGBE_SFF_QSFP_1GBE_COMP	0x86
#define IXGBE_SFF_QSFP_CABWE_WENGTH	0x92
#define IXGBE_SFF_QSFP_DEVICE_TECH	0x93

/* Bitmasks */
#define IXGBE_SFF_DA_PASSIVE_CABWE		0x4
#define IXGBE_SFF_DA_ACTIVE_CABWE		0x8
#define IXGBE_SFF_DA_SPEC_ACTIVE_WIMITING	0x4
#define IXGBE_SFF_1GBASESX_CAPABWE		0x1
#define IXGBE_SFF_1GBASEWX_CAPABWE		0x2
#define IXGBE_SFF_1GBASET_CAPABWE		0x8
#define IXGBE_SFF_10GBASESW_CAPABWE		0x10
#define IXGBE_SFF_10GBASEWW_CAPABWE		0x20
#define IXGBE_SFF_SOFT_WS_SEWECT_MASK		0x8
#define IXGBE_SFF_SOFT_WS_SEWECT_10G		0x8
#define IXGBE_SFF_SOFT_WS_SEWECT_1G		0x0
#define IXGBE_SFF_ADDWESSING_MODE		0x4
#define IXGBE_SFF_DDM_IMPWEMENTED		0x40
#define IXGBE_SFF_QSFP_DA_ACTIVE_CABWE		0x1
#define IXGBE_SFF_QSFP_DA_PASSIVE_CABWE		0x8
#define IXGBE_SFF_QSFP_CONNECTOW_NOT_SEPAWABWE	0x23
#define IXGBE_SFF_QSFP_TWANSMITEW_850NM_VCSEW	0x0
#define IXGBE_I2C_EEPWOM_WEAD_MASK		0x100
#define IXGBE_I2C_EEPWOM_STATUS_MASK		0x3
#define IXGBE_I2C_EEPWOM_STATUS_NO_OPEWATION	0x0
#define IXGBE_I2C_EEPWOM_STATUS_PASS		0x1
#define IXGBE_I2C_EEPWOM_STATUS_FAIW		0x2
#define IXGBE_I2C_EEPWOM_STATUS_IN_PWOGWESS	0x3
#define IXGBE_CS4227				0xBE    /* CS4227 addwess */
#define IXGBE_CS4227_GWOBAW_ID_WSB		0
#define IXGBE_CS4227_GWOBAW_ID_MSB		1
#define IXGBE_CS4227_SCWATCH			2
#define IXGBE_CS4227_EFUSE_PDF_SKU		0x19F
#define IXGBE_CS4223_SKU_ID			0x0010  /* Quad powt */
#define IXGBE_CS4227_SKU_ID			0x0014  /* Duaw powt */
#define IXGBE_CS4227_WESET_PENDING		0x1357
#define IXGBE_CS4227_WESET_COMPWETE		0x5AA5
#define IXGBE_CS4227_WETWIES			15
#define IXGBE_CS4227_EFUSE_STATUS		0x0181
#define IXGBE_CS4227_WINE_SPAWE22_MSB		0x12AD	/* Weg to set speed */
#define IXGBE_CS4227_WINE_SPAWE24_WSB		0x12B0	/* Weg to set EDC */
#define IXGBE_CS4227_HOST_SPAWE22_MSB		0x1AAD	/* Weg to set speed */
#define IXGBE_CS4227_HOST_SPAWE24_WSB		0x1AB0	/* Weg to pwogwam EDC */
#define IXGBE_CS4227_EEPWOM_STATUS		0x5001
#define IXGBE_CS4227_EEPWOM_WOAD_OK		0x0001
#define IXGBE_CS4227_SPEED_1G			0x8000
#define IXGBE_CS4227_SPEED_10G			0
#define IXGBE_CS4227_EDC_MODE_CX1		0x0002
#define IXGBE_CS4227_EDC_MODE_SW		0x0004
#define IXGBE_CS4227_EDC_MODE_DIAG		0x0008
#define IXGBE_CS4227_WESET_HOWD			500	/* micwoseconds */
#define IXGBE_CS4227_WESET_DEWAY		500	/* miwwiseconds */
#define IXGBE_CS4227_CHECK_DEWAY		30	/* miwwiseconds */
#define IXGBE_PE				0xE0	/* Powt expandew addw */
#define IXGBE_PE_OUTPUT				1	/* Output weg offset */
#define IXGBE_PE_CONFIG				3	/* Config weg offset */
#define IXGBE_PE_BIT1				BIT(1)

/* Fwow contwow defines */
#define IXGBE_TAF_SYM_PAUSE                  0x400
#define IXGBE_TAF_ASM_PAUSE                  0x800

/* Bit-shift macwos */
#define IXGBE_SFF_VENDOW_OUI_BYTE0_SHIFT    24
#define IXGBE_SFF_VENDOW_OUI_BYTE1_SHIFT    16
#define IXGBE_SFF_VENDOW_OUI_BYTE2_SHIFT    8

/* Vendow OUIs: fowmat of OUI is 0x[byte0][byte1][byte2][00] */
#define IXGBE_SFF_VENDOW_OUI_TYCO     0x00407600
#define IXGBE_SFF_VENDOW_OUI_FTW      0x00906500
#define IXGBE_SFF_VENDOW_OUI_AVAGO    0x00176A00
#define IXGBE_SFF_VENDOW_OUI_INTEW    0x001B2100

/* I2C SDA and SCW timing pawametews fow standawd mode */
#define IXGBE_I2C_T_HD_STA  4
#define IXGBE_I2C_T_WOW     5
#define IXGBE_I2C_T_HIGH    4
#define IXGBE_I2C_T_SU_STA  5
#define IXGBE_I2C_T_HD_DATA 5
#define IXGBE_I2C_T_SU_DATA 1
#define IXGBE_I2C_T_WISE    1
#define IXGBE_I2C_T_FAWW    1
#define IXGBE_I2C_T_SU_STO  4
#define IXGBE_I2C_T_BUF     5

#define IXGBE_SFP_DETECT_WETWIES	2

#define IXGBE_TN_WASI_STATUS_WEG        0x9005
#define IXGBE_TN_WASI_STATUS_TEMP_AWAWM 0x0008

/* SFP+ SFF-8472 Compwiance code */
#define IXGBE_SFF_SFF_8472_UNSUP      0x00

s32 ixgbe_mii_bus_init(stwuct ixgbe_hw *hw);

s32 ixgbe_identify_phy_genewic(stwuct ixgbe_hw *hw);
s32 ixgbe_weset_phy_genewic(stwuct ixgbe_hw *hw);
s32 ixgbe_wead_phy_weg_genewic(stwuct ixgbe_hw *hw, u32 weg_addw,
			       u32 device_type, u16 *phy_data);
s32 ixgbe_wwite_phy_weg_genewic(stwuct ixgbe_hw *hw, u32 weg_addw,
				u32 device_type, u16 phy_data);
s32 ixgbe_wead_phy_weg_mdi(stwuct ixgbe_hw *hw, u32 weg_addw,
			   u32 device_type, u16 *phy_data);
s32 ixgbe_wwite_phy_weg_mdi(stwuct ixgbe_hw *hw, u32 weg_addw,
			    u32 device_type, u16 phy_data);
s32 ixgbe_setup_phy_wink_genewic(stwuct ixgbe_hw *hw);
s32 ixgbe_setup_phy_wink_speed_genewic(stwuct ixgbe_hw *hw,
				       ixgbe_wink_speed speed,
				       boow autoneg_wait_to_compwete);
s32 ixgbe_get_coppew_wink_capabiwities_genewic(stwuct ixgbe_hw *hw,
					       ixgbe_wink_speed *speed,
					       boow *autoneg);
boow ixgbe_check_weset_bwocked(stwuct ixgbe_hw *hw);

/* PHY specific */
s32 ixgbe_check_phy_wink_tnx(stwuct ixgbe_hw *hw,
			     ixgbe_wink_speed *speed,
			     boow *wink_up);
s32 ixgbe_setup_phy_wink_tnx(stwuct ixgbe_hw *hw);

s32 ixgbe_weset_phy_nw(stwuct ixgbe_hw *hw);
s32 ixgbe_set_coppew_phy_powew(stwuct ixgbe_hw *hw, boow on);
s32 ixgbe_identify_moduwe_genewic(stwuct ixgbe_hw *hw);
s32 ixgbe_identify_sfp_moduwe_genewic(stwuct ixgbe_hw *hw);
s32 ixgbe_get_sfp_init_sequence_offsets(stwuct ixgbe_hw *hw,
					u16 *wist_offset,
					u16 *data_offset);
boow ixgbe_tn_check_ovewtemp(stwuct ixgbe_hw *hw);
s32 ixgbe_wead_i2c_byte_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				u8 dev_addw, u8 *data);
s32 ixgbe_wead_i2c_byte_genewic_unwocked(stwuct ixgbe_hw *hw, u8 byte_offset,
					 u8 dev_addw, u8 *data);
s32 ixgbe_wwite_i2c_byte_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				 u8 dev_addw, u8 data);
s32 ixgbe_wwite_i2c_byte_genewic_unwocked(stwuct ixgbe_hw *hw, u8 byte_offset,
					  u8 dev_addw, u8 data);
s32 ixgbe_wead_i2c_eepwom_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				  u8 *eepwom_data);
s32 ixgbe_wead_i2c_sff8472_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				   u8 *sff8472_data);
s32 ixgbe_wwite_i2c_eepwom_genewic(stwuct ixgbe_hw *hw, u8 byte_offset,
				   u8 eepwom_data);
s32 ixgbe_wead_i2c_combined_genewic_int(stwuct ixgbe_hw *, u8 addw, u16 weg,
					u16 *vaw, boow wock);
s32 ixgbe_wwite_i2c_combined_genewic_int(stwuct ixgbe_hw *, u8 addw, u16 weg,
					 u16 vaw, boow wock);
#endif /* _IXGBE_PHY_H_ */
