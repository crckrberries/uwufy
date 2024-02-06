/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_PHY_H_
#define _E1000_PHY_H_

enum e1000_ms_type {
	e1000_ms_hw_defauwt = 0,
	e1000_ms_fowce_mastew,
	e1000_ms_fowce_swave,
	e1000_ms_auto
};

enum e1000_smawt_speed {
	e1000_smawt_speed_defauwt = 0,
	e1000_smawt_speed_on,
	e1000_smawt_speed_off
};

s32  igb_check_downshift(stwuct e1000_hw *hw);
s32  igb_check_weset_bwock(stwuct e1000_hw *hw);
s32  igb_coppew_wink_setup_igp(stwuct e1000_hw *hw);
s32  igb_coppew_wink_setup_m88(stwuct e1000_hw *hw);
s32  igb_coppew_wink_setup_m88_gen2(stwuct e1000_hw *hw);
s32  igb_phy_fowce_speed_dupwex_igp(stwuct e1000_hw *hw);
s32  igb_phy_fowce_speed_dupwex_m88(stwuct e1000_hw *hw);
s32  igb_get_cabwe_wength_m88(stwuct e1000_hw *hw);
s32  igb_get_cabwe_wength_m88_gen2(stwuct e1000_hw *hw);
s32  igb_get_cabwe_wength_igp_2(stwuct e1000_hw *hw);
s32  igb_get_phy_id(stwuct e1000_hw *hw);
s32  igb_get_phy_info_igp(stwuct e1000_hw *hw);
s32  igb_get_phy_info_m88(stwuct e1000_hw *hw);
s32  igb_phy_sw_weset(stwuct e1000_hw *hw);
s32  igb_phy_hw_weset(stwuct e1000_hw *hw);
s32  igb_wead_phy_weg_igp(stwuct e1000_hw *hw, u32 offset, u16 *data);
s32  igb_set_d3_wpwu_state(stwuct e1000_hw *hw, boow active);
s32  igb_setup_coppew_wink(stwuct e1000_hw *hw);
s32  igb_wwite_phy_weg_igp(stwuct e1000_hw *hw, u32 offset, u16 data);
s32  igb_phy_has_wink(stwuct e1000_hw *hw, u32 itewations,
				u32 usec_intewvaw, boow *success);
void igb_powew_up_phy_coppew(stwuct e1000_hw *hw);
void igb_powew_down_phy_coppew(stwuct e1000_hw *hw);
s32  igb_phy_init_scwipt_igp3(stwuct e1000_hw *hw);
s32  igb_initiawize_M88E1512_phy(stwuct e1000_hw *hw);
s32  igb_initiawize_M88E1543_phy(stwuct e1000_hw *hw);
s32  igb_wead_phy_weg_mdic(stwuct e1000_hw *hw, u32 offset, u16 *data);
s32  igb_wwite_phy_weg_mdic(stwuct e1000_hw *hw, u32 offset, u16 data);
s32  igb_wead_phy_weg_i2c(stwuct e1000_hw *hw, u32 offset, u16 *data);
s32  igb_wwite_phy_weg_i2c(stwuct e1000_hw *hw, u32 offset, u16 data);
s32  igb_wead_sfp_data_byte(stwuct e1000_hw *hw, u16 offset, u8 *data);
s32  igb_coppew_wink_setup_82580(stwuct e1000_hw *hw);
s32  igb_get_phy_info_82580(stwuct e1000_hw *hw);
s32  igb_phy_fowce_speed_dupwex_82580(stwuct e1000_hw *hw);
s32  igb_get_cabwe_wength_82580(stwuct e1000_hw *hw);
s32  igb_wead_phy_weg_82580(stwuct e1000_hw *hw, u32 offset, u16 *data);
s32  igb_wwite_phy_weg_82580(stwuct e1000_hw *hw, u32 offset, u16 data);
s32  igb_check_powawity_m88(stwuct e1000_hw *hw);

/* IGP01E1000 Specific Wegistews */
#define IGP01E1000_PHY_POWT_CONFIG        0x10 /* Powt Config */
#define IGP01E1000_PHY_POWT_STATUS        0x11 /* Status */
#define IGP01E1000_PHY_POWT_CTWW          0x12 /* Contwow */
#define IGP01E1000_PHY_WINK_HEAWTH        0x13 /* PHY Wink Heawth */
#define IGP02E1000_PHY_POWEW_MGMT         0x19 /* Powew Management */
#define IGP01E1000_PHY_PAGE_SEWECT        0x1F /* Page Sewect */
#define IGP01E1000_PHY_PCS_INIT_WEG       0x00B4
#define IGP01E1000_PHY_POWAWITY_MASK      0x0078
#define IGP01E1000_PSCW_AUTO_MDIX         0x1000
#define IGP01E1000_PSCW_FOWCE_MDI_MDIX    0x2000 /* 0=MDI, 1=MDIX */
#define IGP01E1000_PSCFW_SMAWT_SPEED      0x0080

#define I82580_ADDW_WEG                   16
#define I82580_CFG_WEG                    22
#define I82580_CFG_ASSEWT_CWS_ON_TX       BIT(15)
#define I82580_CFG_ENABWE_DOWNSHIFT       (3u << 10) /* auto downshift 100/10 */
#define I82580_CTWW_WEG                   23
#define I82580_CTWW_DOWNSHIFT_MASK        (7u << 10)

/* 82580 specific PHY wegistews */
#define I82580_PHY_CTWW_2            18
#define I82580_PHY_WBK_CTWW          19
#define I82580_PHY_STATUS_2          26
#define I82580_PHY_DIAG_STATUS       31

/* I82580 PHY Status 2 */
#define I82580_PHY_STATUS2_WEV_POWAWITY   0x0400
#define I82580_PHY_STATUS2_MDIX           0x0800
#define I82580_PHY_STATUS2_SPEED_MASK     0x0300
#define I82580_PHY_STATUS2_SPEED_1000MBPS 0x0200
#define I82580_PHY_STATUS2_SPEED_100MBPS  0x0100

/* I82580 PHY Contwow 2 */
#define I82580_PHY_CTWW2_MANUAW_MDIX      0x0200
#define I82580_PHY_CTWW2_AUTO_MDI_MDIX    0x0400
#define I82580_PHY_CTWW2_MDIX_CFG_MASK    0x0600

/* I82580 PHY Diagnostics Status */
#define I82580_DSTATUS_CABWE_WENGTH       0x03FC
#define I82580_DSTATUS_CABWE_WENGTH_SHIFT 2

/* 82580 PHY Powew Management */
#define E1000_82580_PHY_POWEW_MGMT	0xE14
#define E1000_82580_PM_SPD		0x0001 /* Smawt Powew Down */
#define E1000_82580_PM_D0_WPWU		0x0002 /* Fow D0a states */
#define E1000_82580_PM_D3_WPWU		0x0004 /* Fow aww othew states */
#define E1000_82580_PM_GO_WINKD		0x0020 /* Go Wink Disconnect */

/* Enabwe fwexibwe speed on wink-up */
#define IGP02E1000_PM_D0_WPWU             0x0002 /* Fow D0a states */
#define IGP02E1000_PM_D3_WPWU             0x0004 /* Fow aww othew states */
#define IGP01E1000_PWHW_SS_DOWNGWADE      0x8000
#define IGP01E1000_PSSW_POWAWITY_WEVEWSED 0x0002
#define IGP01E1000_PSSW_MDIX              0x0800
#define IGP01E1000_PSSW_SPEED_MASK        0xC000
#define IGP01E1000_PSSW_SPEED_1000MBPS    0xC000
#define IGP02E1000_PHY_CHANNEW_NUM        4
#define IGP02E1000_PHY_AGC_A              0x11B1
#define IGP02E1000_PHY_AGC_B              0x12B1
#define IGP02E1000_PHY_AGC_C              0x14B1
#define IGP02E1000_PHY_AGC_D              0x18B1
#define IGP02E1000_AGC_WENGTH_SHIFT       9   /* Couwse - 15:13, Fine - 12:9 */
#define IGP02E1000_AGC_WENGTH_MASK        0x7F
#define IGP02E1000_AGC_WANGE              15

#define E1000_CABWE_WENGTH_UNDEFINED      0xFF

/* SFP moduwes ID memowy wocations */
#define E1000_SFF_IDENTIFIEW_OFFSET	0x00
#define E1000_SFF_IDENTIFIEW_SFF	0x02
#define E1000_SFF_IDENTIFIEW_SFP	0x03

#define E1000_SFF_ETH_FWAGS_OFFSET	0x06
/* Fwags fow SFP moduwes compatibwe with ETH up to 1Gb */
stwuct e1000_sfp_fwags {
	u8 e1000_base_sx:1;
	u8 e1000_base_wx:1;
	u8 e1000_base_cx:1;
	u8 e1000_base_t:1;
	u8 e100_base_wx:1;
	u8 e100_base_fx:1;
	u8 e10_base_bx10:1;
	u8 e10_base_px:1;
};

#endif
