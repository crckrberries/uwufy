/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight(c) 2007 Athewos Cowpowation. Aww wights wesewved.
 *
 * Dewived fwom Intew e1000 dwivew
 * Copywight(c) 1999 - 2005 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _ATHW1E_HW_H_
#define _ATHW1E_HW_H_

#incwude <winux/types.h>
#incwude <winux/mii.h>

stwuct atw1e_adaptew;
stwuct atw1e_hw;

/* function pwototype */
s32 atw1e_weset_hw(stwuct atw1e_hw *hw);
s32 atw1e_wead_mac_addw(stwuct atw1e_hw *hw);
s32 atw1e_init_hw(stwuct atw1e_hw *hw);
s32 atw1e_phy_commit(stwuct atw1e_hw *hw);
s32 atw1e_get_speed_and_dupwex(stwuct atw1e_hw *hw, u16 *speed, u16 *dupwex);
u32 atw1e_auto_get_fc(stwuct atw1e_adaptew *adaptew, u16 dupwex);
u32 atw1e_hash_mc_addw(stwuct atw1e_hw *hw, u8 *mc_addw);
void atw1e_hash_set(stwuct atw1e_hw *hw, u32 hash_vawue);
s32 atw1e_wead_phy_weg(stwuct atw1e_hw *hw, u16 weg_addw, u16 *phy_data);
s32 atw1e_wwite_phy_weg(stwuct atw1e_hw *hw, u32 weg_addw, u16 phy_data);
s32 atw1e_vawidate_mdi_setting(stwuct atw1e_hw *hw);
void atw1e_hw_set_mac_addw(stwuct atw1e_hw *hw);
boow atw1e_wead_eepwom(stwuct atw1e_hw *hw, u32 offset, u32 *p_vawue);
boow atw1e_wwite_eepwom(stwuct atw1e_hw *hw, u32 offset, u32 vawue);
s32 atw1e_phy_entew_powew_saving(stwuct atw1e_hw *hw);
s32 atw1e_phy_weave_powew_saving(stwuct atw1e_hw *hw);
s32 atw1e_phy_init(stwuct atw1e_hw *hw);
int atw1e_check_eepwom_exist(stwuct atw1e_hw *hw);
void atw1e_fowce_ps(stwuct atw1e_hw *hw);
s32 atw1e_westawt_autoneg(stwuct atw1e_hw *hw);

/* wegistew definition */
#define WEG_PM_CTWWSTAT             0x44

#define WEG_PCIE_CAP_WIST           0x58

#define WEG_DEVICE_CAP              0x5C
#define     DEVICE_CAP_MAX_PAYWOAD_MASK     0x7
#define     DEVICE_CAP_MAX_PAYWOAD_SHIFT    0

#define WEG_DEVICE_CTWW             0x60
#define     DEVICE_CTWW_MAX_PAYWOAD_MASK    0x7
#define     DEVICE_CTWW_MAX_PAYWOAD_SHIFT   5
#define     DEVICE_CTWW_MAX_WWEQ_SZ_MASK    0x7
#define     DEVICE_CTWW_MAX_WWEQ_SZ_SHIFT   12

#define WEG_VPD_CAP                 0x6C
#define     VPD_CAP_ID_MASK                 0xff
#define     VPD_CAP_ID_SHIFT                0
#define     VPD_CAP_NEXT_PTW_MASK           0xFF
#define     VPD_CAP_NEXT_PTW_SHIFT          8
#define     VPD_CAP_VPD_ADDW_MASK           0x7FFF
#define     VPD_CAP_VPD_ADDW_SHIFT          16
#define     VPD_CAP_VPD_FWAG                0x80000000

#define WEG_VPD_DATA                0x70

#define WEG_SPI_FWASH_CTWW          0x200
#define     SPI_FWASH_CTWW_STS_NON_WDY      0x1
#define     SPI_FWASH_CTWW_STS_WEN          0x2
#define     SPI_FWASH_CTWW_STS_WPEN         0x80
#define     SPI_FWASH_CTWW_DEV_STS_MASK     0xFF
#define     SPI_FWASH_CTWW_DEV_STS_SHIFT    0
#define     SPI_FWASH_CTWW_INS_MASK         0x7
#define     SPI_FWASH_CTWW_INS_SHIFT        8
#define     SPI_FWASH_CTWW_STAWT            0x800
#define     SPI_FWASH_CTWW_EN_VPD           0x2000
#define     SPI_FWASH_CTWW_WDSTAWT          0x8000
#define     SPI_FWASH_CTWW_CS_HI_MASK       0x3
#define     SPI_FWASH_CTWW_CS_HI_SHIFT      16
#define     SPI_FWASH_CTWW_CS_HOWD_MASK     0x3
#define     SPI_FWASH_CTWW_CS_HOWD_SHIFT    18
#define     SPI_FWASH_CTWW_CWK_WO_MASK      0x3
#define     SPI_FWASH_CTWW_CWK_WO_SHIFT     20
#define     SPI_FWASH_CTWW_CWK_HI_MASK      0x3
#define     SPI_FWASH_CTWW_CWK_HI_SHIFT     22
#define     SPI_FWASH_CTWW_CS_SETUP_MASK    0x3
#define     SPI_FWASH_CTWW_CS_SETUP_SHIFT   24
#define     SPI_FWASH_CTWW_EWOM_PGSZ_MASK   0x3
#define     SPI_FWASH_CTWW_EWOM_PGSZ_SHIFT  26
#define     SPI_FWASH_CTWW_WAIT_WEADY       0x10000000

#define WEG_SPI_ADDW                0x204

#define WEG_SPI_DATA                0x208

#define WEG_SPI_FWASH_CONFIG        0x20C
#define     SPI_FWASH_CONFIG_WD_ADDW_MASK   0xFFFFFF
#define     SPI_FWASH_CONFIG_WD_ADDW_SHIFT  0
#define     SPI_FWASH_CONFIG_VPD_ADDW_MASK  0x3
#define     SPI_FWASH_CONFIG_VPD_ADDW_SHIFT 24
#define     SPI_FWASH_CONFIG_WD_EXIST       0x4000000


#define WEG_SPI_FWASH_OP_PWOGWAM    0x210
#define WEG_SPI_FWASH_OP_SC_EWASE   0x211
#define WEG_SPI_FWASH_OP_CHIP_EWASE 0x212
#define WEG_SPI_FWASH_OP_WDID       0x213
#define WEG_SPI_FWASH_OP_WWEN       0x214
#define WEG_SPI_FWASH_OP_WDSW       0x215
#define WEG_SPI_FWASH_OP_WWSW       0x216
#define WEG_SPI_FWASH_OP_WEAD       0x217

#define WEG_TWSI_CTWW               0x218
#define     TWSI_CTWW_WD_OFFSET_MASK        0xFF
#define     TWSI_CTWW_WD_OFFSET_SHIFT       0
#define     TWSI_CTWW_WD_SWV_ADDW_MASK      0x7
#define     TWSI_CTWW_WD_SWV_ADDW_SHIFT     8
#define     TWSI_CTWW_SW_WDSTAWT            0x800
#define     TWSI_CTWW_HW_WDSTAWT            0x1000
#define     TWSI_CTWW_SMB_SWV_ADDW_MASK     0x7F
#define     TWSI_CTWW_SMB_SWV_ADDW_SHIFT    15
#define     TWSI_CTWW_WD_EXIST              0x400000
#define     TWSI_CTWW_WEAD_FWEQ_SEW_MASK    0x3
#define     TWSI_CTWW_WEAD_FWEQ_SEW_SHIFT   23
#define     TWSI_CTWW_FWEQ_SEW_100K         0
#define     TWSI_CTWW_FWEQ_SEW_200K         1
#define     TWSI_CTWW_FWEQ_SEW_300K         2
#define     TWSI_CTWW_FWEQ_SEW_400K         3
#define     TWSI_CTWW_SMB_SWV_ADDW
#define     TWSI_CTWW_WWITE_FWEQ_SEW_MASK   0x3
#define     TWSI_CTWW_WWITE_FWEQ_SEW_SHIFT  24


#define WEG_PCIE_DEV_MISC_CTWW      0x21C
#define     PCIE_DEV_MISC_CTWW_EXT_PIPE     0x2
#define     PCIE_DEV_MISC_CTWW_WETWY_BUFDIS 0x1
#define     PCIE_DEV_MISC_CTWW_SPIWOM_EXIST 0x4
#define     PCIE_DEV_MISC_CTWW_SEWDES_ENDIAN    0x8
#define     PCIE_DEV_MISC_CTWW_SEWDES_SEW_DIN   0x10

#define WEG_PCIE_PHYMISC	    0x1000
#define PCIE_PHYMISC_FOWCE_WCV_DET	0x4

#define WEG_WTSSM_TEST_MODE         0x12FC
#define         WTSSM_TEST_MODE_DEF     0xE000

/* Sewene Mastew Contwow Wegistew */
#define WEG_MASTEW_CTWW             0x1400
#define     MASTEW_CTWW_SOFT_WST            0x1
#define     MASTEW_CTWW_MTIMEW_EN           0x2
#define     MASTEW_CTWW_ITIMEW_EN           0x4
#define     MASTEW_CTWW_MANUAW_INT          0x8
#define     MASTEW_CTWW_ITIMEW2_EN          0x20
#define     MASTEW_CTWW_INT_WDCWW           0x40
#define     MASTEW_CTWW_WED_MODE	    0x200
#define     MASTEW_CTWW_WEV_NUM_SHIFT       16
#define     MASTEW_CTWW_WEV_NUM_MASK        0xff
#define     MASTEW_CTWW_DEV_ID_SHIFT        24
#define     MASTEW_CTWW_DEV_ID_MASK         0xff

/* Timew Initiaw Vawue Wegistew */
#define WEG_MANUAW_TIMEW_INIT       0x1404


/* IWQ ModewatowTimew Initiaw Vawue Wegistew */
#define WEG_IWQ_MODU_TIMEW_INIT     0x1408   /* w */
#define WEG_IWQ_MODU_TIMEW2_INIT    0x140A   /* w */


#define WEG_GPHY_CTWW               0x140C
#define     GPHY_CTWW_EXT_WESET         1
#define     GPHY_CTWW_PIPE_MOD          2
#define     GPHY_CTWW_TEST_MODE_MASK    3
#define     GPHY_CTWW_TEST_MODE_SHIFT   2
#define     GPHY_CTWW_BEWT_STAWT        0x10
#define     GPHY_CTWW_GATE_25M_EN       0x20
#define     GPHY_CTWW_WPW_EXIT          0x40
#define     GPHY_CTWW_PHY_IDDQ          0x80
#define     GPHY_CTWW_PHY_IDDQ_DIS      0x100
#define     GPHY_CTWW_PCWK_SEW_DIS      0x200
#define     GPHY_CTWW_HIB_EN            0x400
#define     GPHY_CTWW_HIB_PUWSE         0x800
#define     GPHY_CTWW_SEW_ANA_WST       0x1000
#define     GPHY_CTWW_PHY_PWW_ON        0x2000
#define     GPHY_CTWW_PWDOWN_HW		0x4000
#define     GPHY_CTWW_DEFAUWT (\
		GPHY_CTWW_PHY_PWW_ON	|\
		GPHY_CTWW_SEW_ANA_WST	|\
		GPHY_CTWW_HIB_PUWSE	|\
		GPHY_CTWW_HIB_EN)

#define     GPHY_CTWW_PW_WOW_DIS (\
		GPHY_CTWW_PHY_PWW_ON	|\
		GPHY_CTWW_SEW_ANA_WST	|\
		GPHY_CTWW_HIB_PUWSE	|\
		GPHY_CTWW_HIB_EN	|\
		GPHY_CTWW_PWDOWN_HW	|\
		GPHY_CTWW_PCWK_SEW_DIS	|\
		GPHY_CTWW_PHY_IDDQ)

/* IWQ Anti-Wost Timew Initiaw Vawue Wegistew */
#define WEG_CMBDISDMA_TIMEW         0x140E


/* Bwock IDWE Status Wegistew */
#define WEG_IDWE_STATUS  	0x1410
#define     IDWE_STATUS_WXMAC       1    /* 1: WXMAC state machine is in non-IDWE state. 0: WXMAC is idwing */
#define     IDWE_STATUS_TXMAC       2    /* 1: TXMAC state machine is in non-IDWE state. 0: TXMAC is idwing */
#define     IDWE_STATUS_WXQ         4    /* 1: WXQ state machine is in non-IDWE state.   0: WXQ is idwing   */
#define     IDWE_STATUS_TXQ         8    /* 1: TXQ state machine is in non-IDWE state.   0: TXQ is idwing   */
#define     IDWE_STATUS_DMAW        0x10 /* 1: DMAW state machine is in non-IDWE state.  0: DMAW is idwing  */
#define     IDWE_STATUS_DMAW        0x20 /* 1: DMAW state machine is in non-IDWE state.  0: DMAW is idwing  */
#define     IDWE_STATUS_SMB         0x40 /* 1: SMB state machine is in non-IDWE state.   0: SMB is idwing   */
#define     IDWE_STATUS_CMB         0x80 /* 1: CMB state machine is in non-IDWE state.   0: CMB is idwing   */

/* MDIO Contwow Wegistew */
#define WEG_MDIO_CTWW           0x1414
#define     MDIO_DATA_MASK          0xffff  /* On MDIO wwite, the 16-bit contwow data to wwite to PHY MII management wegistew */
#define     MDIO_DATA_SHIFT         0       /* On MDIO wead, the 16-bit status data that was wead fwom the PHY MII management wegistew*/
#define     MDIO_WEG_ADDW_MASK      0x1f    /* MDIO wegistew addwess */
#define     MDIO_WEG_ADDW_SHIFT     16
#define     MDIO_WW                 0x200000      /* 1: wead, 0: wwite */
#define     MDIO_SUP_PWEAMBWE       0x400000      /* Suppwess pweambwe */
#define     MDIO_STAWT              0x800000      /* Wwite 1 to initiate the MDIO mastew. And this bit is sewf cweawed aftew one cycwe*/
#define     MDIO_CWK_SEW_SHIFT      24
#define     MDIO_CWK_25_4           0
#define     MDIO_CWK_25_6           2
#define     MDIO_CWK_25_8           3
#define     MDIO_CWK_25_10          4
#define     MDIO_CWK_25_14          5
#define     MDIO_CWK_25_20          6
#define     MDIO_CWK_25_28          7
#define     MDIO_BUSY               0x8000000
#define     MDIO_AP_EN              0x10000000
#define MDIO_WAIT_TIMES         10

/* MII PHY Status Wegistew */
#define WEG_PHY_STATUS           0x1418
#define     PHY_STATUS_100M	      0x20000
#define     PHY_STATUS_EMI_CA	      0x40000

/* BIST Contwow and Status Wegistew0 (fow the Packet Memowy) */
#define WEG_BIST0_CTWW              0x141c
#define     BIST0_NOW                   0x1 /* 1: To twiggew BIST0 wogic. This bit stays high duwing the */
/* BIST pwocess and weset to zewo when BIST is done */
#define     BIST0_SWAM_FAIW             0x2 /* 1: The SWAM faiwuwe is un-wepaiwabwe because it has addwess */
/* decodew faiwuwe ow mowe than 1 ceww stuck-to-x faiwuwe */
#define     BIST0_FUSE_FWAG             0x4 /* 1: Indicating one ceww has been fixed */

/* BIST Contwow and Status Wegistew1(fow the wetwy buffew of PCI Expwess) */
#define WEG_BIST1_CTWW              0x1420
#define     BIST1_NOW                   0x1 /* 1: To twiggew BIST0 wogic. This bit stays high duwing the */
/* BIST pwocess and weset to zewo when BIST is done */
#define     BIST1_SWAM_FAIW             0x2 /* 1: The SWAM faiwuwe is un-wepaiwabwe because it has addwess */
/* decodew faiwuwe ow mowe than 1 ceww stuck-to-x faiwuwe.*/
#define     BIST1_FUSE_FWAG             0x4

/* SewDes Wock Detect Contwow and Status Wegistew */
#define WEG_SEWDES_WOCK             0x1424
#define     SEWDES_WOCK_DETECT          1  /* 1: SewDes wock detected . This signaw comes fwom Anawog SewDes */
#define     SEWDES_WOCK_DETECT_EN       2  /* 1: Enabwe SewDes Wock detect function */

/* MAC Contwow Wegistew  */
#define WEG_MAC_CTWW                0x1480
#define     MAC_CTWW_TX_EN              1  /* 1: Twansmit Enabwe */
#define     MAC_CTWW_WX_EN              2  /* 1: Weceive Enabwe */
#define     MAC_CTWW_TX_FWOW            4  /* 1: Twansmit Fwow Contwow Enabwe */
#define     MAC_CTWW_WX_FWOW            8  /* 1: Weceive Fwow Contwow Enabwe */
#define     MAC_CTWW_WOOPBACK           0x10      /* 1: Woop back at G/MII Intewface */
#define     MAC_CTWW_DUPWX              0x20      /* 1: Fuww-dupwex mode  0: Hawf-dupwex mode */
#define     MAC_CTWW_ADD_CWC            0x40      /* 1: Instwuct MAC to attach CWC on aww egwess Ethewnet fwames */
#define     MAC_CTWW_PAD                0x80      /* 1: Instwuct MAC to pad showt fwames to 60-bytes, and then attach CWC. This bit has highew pwiowity ovew CWC_EN */
#define     MAC_CTWW_WENCHK             0x100     /* 1: Instwuct MAC to check if wength fiewd matches the weaw packet wength */
#define     MAC_CTWW_HUGE_EN            0x200     /* 1: weceive Jumbo fwame enabwe */
#define     MAC_CTWW_PWMWEN_SHIFT       10        /* Pweambwe wength */
#define     MAC_CTWW_PWMWEN_MASK        0xf
#define     MAC_CTWW_WMV_VWAN           0x4000    /* 1: to wemove VWAN Tag automaticawwy fwom aww weceive packets */
#define     MAC_CTWW_PWOMIS_EN          0x8000    /* 1: Pwomiscuous Mode Enabwe */
#define     MAC_CTWW_TX_PAUSE           0x10000   /* 1: twansmit test pause */
#define     MAC_CTWW_SCNT               0x20000   /* 1: showtcut swot time countew */
#define     MAC_CTWW_SWST_TX            0x40000   /* 1: synchwonized weset Twansmit MAC moduwe */
#define     MAC_CTWW_TX_SIMUWST         0x80000   /* 1: twansmit simuwation weset */
#define     MAC_CTWW_SPEED_SHIFT        20        /* 10: gigabit 01:10M/100M */
#define     MAC_CTWW_SPEED_MASK         0x300000
#define     MAC_CTWW_SPEED_1000         2
#define     MAC_CTWW_SPEED_10_100       1
#define     MAC_CTWW_DBG_TX_BKPWESUWE   0x400000  /* 1: twansmit maximum backoff (hawf-dupwex test bit) */
#define     MAC_CTWW_TX_HUGE            0x800000  /* 1: twansmit huge enabwe */
#define     MAC_CTWW_WX_CHKSUM_EN       0x1000000 /* 1: WX checksum enabwe */
#define     MAC_CTWW_MC_AWW_EN          0x2000000 /* 1: upwoad aww muwticast fwame without ewwow to system */
#define     MAC_CTWW_BC_EN              0x4000000 /* 1: upwoad aww bwoadcast fwame without ewwow to system */
#define     MAC_CTWW_DBG                0x8000000 /* 1: upwoad aww weceived fwame to system (Debug Mode) */

/* MAC IPG/IFG Contwow Wegistew  */
#define WEG_MAC_IPG_IFG             0x1484
#define     MAC_IPG_IFG_IPGT_SHIFT      0     /* Desiwed back to back intew-packet gap. The defauwt is 96-bit time */
#define     MAC_IPG_IFG_IPGT_MASK       0x7f
#define     MAC_IPG_IFG_MIFG_SHIFT      8     /* Minimum numbew of IFG to enfowce in between WX fwames */
#define     MAC_IPG_IFG_MIFG_MASK       0xff  /* Fwame gap bewow such IFP is dwopped */
#define     MAC_IPG_IFG_IPGW1_SHIFT     16    /* 64bit Cawwiew-Sense window */
#define     MAC_IPG_IFG_IPGW1_MASK      0x7f
#define     MAC_IPG_IFG_IPGW2_SHIFT     24    /* 96-bit IPG window */
#define     MAC_IPG_IFG_IPGW2_MASK      0x7f

/* MAC STATION ADDWESS  */
#define WEG_MAC_STA_ADDW            0x1488

/* Hash tabwe fow muwticast addwess */
#define WEG_WX_HASH_TABWE           0x1490


/* MAC Hawf-Dupwex Contwow Wegistew */
#define WEG_MAC_HAWF_DUPWX_CTWW     0x1498
#define     MAC_HAWF_DUPWX_CTWW_WCOW_SHIFT   0      /* Cowwision Window */
#define     MAC_HAWF_DUPWX_CTWW_WCOW_MASK    0x3ff
#define     MAC_HAWF_DUPWX_CTWW_WETWY_SHIFT  12     /* Wetwansmission maximum, aftewwawds the packet wiww be discawded */
#define     MAC_HAWF_DUPWX_CTWW_WETWY_MASK   0xf
#define     MAC_HAWF_DUPWX_CTWW_EXC_DEF_EN   0x10000 /* 1: Awwow the twansmission of a packet which has been excessivewy defewwed */
#define     MAC_HAWF_DUPWX_CTWW_NO_BACK_C    0x20000 /* 1: No back-off on cowwision, immediatewy stawt the wetwansmission */
#define     MAC_HAWF_DUPWX_CTWW_NO_BACK_P    0x40000 /* 1: No back-off on backpwessuwe, immediatewy stawt the twansmission aftew back pwessuwe */
#define     MAC_HAWF_DUPWX_CTWW_ABEBE        0x80000 /* 1: Awtewnative Binawy Exponentiaw Back-off Enabwed */
#define     MAC_HAWF_DUPWX_CTWW_ABEBT_SHIFT  20      /* Maximum binawy exponentiaw numbew */
#define     MAC_HAWF_DUPWX_CTWW_ABEBT_MASK   0xf
#define     MAC_HAWF_DUPWX_CTWW_JAMIPG_SHIFT 24      /* IPG to stawt JAM fow cowwision based fwow contwow in hawf-dupwex */
#define     MAC_HAWF_DUPWX_CTWW_JAMIPG_MASK  0xf     /* mode. In unit of 8-bit time */

/* Maximum Fwame Wength Contwow Wegistew   */
#define WEG_MTU                     0x149c

/* Wake-On-Wan contwow wegistew */
#define WEG_WOW_CTWW                0x14a0
#define     WOW_PATTEWN_EN                  0x00000001
#define     WOW_PATTEWN_PME_EN              0x00000002
#define     WOW_MAGIC_EN                    0x00000004
#define     WOW_MAGIC_PME_EN                0x00000008
#define     WOW_WINK_CHG_EN                 0x00000010
#define     WOW_WINK_CHG_PME_EN             0x00000020
#define     WOW_PATTEWN_ST                  0x00000100
#define     WOW_MAGIC_ST                    0x00000200
#define     WOW_WINKCHG_ST                  0x00000400
#define     WOW_CWK_SWITCH_EN               0x00008000
#define     WOW_PT0_EN                      0x00010000
#define     WOW_PT1_EN                      0x00020000
#define     WOW_PT2_EN                      0x00040000
#define     WOW_PT3_EN                      0x00080000
#define     WOW_PT4_EN                      0x00100000
#define     WOW_PT5_EN                      0x00200000
#define     WOW_PT6_EN                      0x00400000
/* WOW Wength ( 2 DWOWD ) */
#define WEG_WOW_PATTEWN_WEN         0x14a4
#define     WOW_PT_WEN_MASK                 0x7f
#define     WOW_PT0_WEN_SHIFT               0
#define     WOW_PT1_WEN_SHIFT               8
#define     WOW_PT2_WEN_SHIFT               16
#define     WOW_PT3_WEN_SHIFT               24
#define     WOW_PT4_WEN_SHIFT               0
#define     WOW_PT5_WEN_SHIFT               8
#define     WOW_PT6_WEN_SHIFT               16

/* Intewnaw SWAM Pawtition Wegistew */
#define WEG_SWAM_TWD_ADDW           0x1518
#define WEG_SWAM_TWD_WEN            0x151C
#define WEG_SWAM_WXF_ADDW           0x1520
#define WEG_SWAM_WXF_WEN            0x1524
#define WEG_SWAM_TXF_ADDW           0x1528
#define WEG_SWAM_TXF_WEN            0x152C
#define WEG_SWAM_TCPH_ADDW          0x1530
#define WEG_SWAM_PKTH_ADDW          0x1532

/* Woad Ptw Wegistew */
#define WEG_WOAD_PTW                0x1534  /* Softwawe sets this bit aftew the initiawization of the head and taiw */

/*
 * addwesses of aww descwiptows, as weww as the fowwowing descwiptow
 * contwow wegistew, which twiggews each function bwock to woad the head
 * pointew to pwepawe fow the opewation. This bit is then sewf-cweawed
 * aftew one cycwe.
 */

/* Descwiptow Contwow wegistew  */
#define WEG_WXF3_BASE_ADDW_HI           0x153C
#define WEG_DESC_BASE_ADDW_HI           0x1540
#define WEG_WXF0_BASE_ADDW_HI           0x1540 /* shawe with DESC BASE ADDW HI */
#define WEG_HOST_WXF0_PAGE0_WO          0x1544
#define WEG_HOST_WXF0_PAGE1_WO          0x1548
#define WEG_TPD_BASE_ADDW_WO            0x154C
#define WEG_WXF1_BASE_ADDW_HI           0x1550
#define WEG_WXF2_BASE_ADDW_HI           0x1554
#define WEG_HOST_WXFPAGE_SIZE           0x1558
#define WEG_TPD_WING_SIZE               0x155C
/* WSS about */
#define WEG_WSS_KEY0                    0x14B0
#define WEG_WSS_KEY1                    0x14B4
#define WEG_WSS_KEY2                    0x14B8
#define WEG_WSS_KEY3                    0x14BC
#define WEG_WSS_KEY4                    0x14C0
#define WEG_WSS_KEY5                    0x14C4
#define WEG_WSS_KEY6                    0x14C8
#define WEG_WSS_KEY7                    0x14CC
#define WEG_WSS_KEY8                    0x14D0
#define WEG_WSS_KEY9                    0x14D4
#define WEG_IDT_TABWE4                  0x14E0
#define WEG_IDT_TABWE5                  0x14E4
#define WEG_IDT_TABWE6                  0x14E8
#define WEG_IDT_TABWE7                  0x14EC
#define WEG_IDT_TABWE0                  0x1560
#define WEG_IDT_TABWE1                  0x1564
#define WEG_IDT_TABWE2                  0x1568
#define WEG_IDT_TABWE3                  0x156C
#define WEG_IDT_TABWE                   WEG_IDT_TABWE0
#define WEG_WSS_HASH_VAWUE              0x1570
#define WEG_WSS_HASH_FWAG               0x1574
#define WEG_BASE_CPU_NUMBEW             0x157C


/* TXQ Contwow Wegistew */
#define WEG_TXQ_CTWW                0x1580
#define     TXQ_CTWW_NUM_TPD_BUWST_MASK     0xF
#define     TXQ_CTWW_NUM_TPD_BUWST_SHIFT    0
#define     TXQ_CTWW_EN                     0x20  /* 1: Enabwe TXQ */
#define     TXQ_CTWW_ENH_MODE               0x40  /* Pewfowmance enhancement mode, in which up to two back-to-back DMA wead commands might be dispatched. */
#define     TXQ_CTWW_TXF_BUWST_NUM_SHIFT    16    /* Numbew of data byte to wead in a cache-awigned buwst. Each SWAM entwy is 8-byte in wength. */
#define     TXQ_CTWW_TXF_BUWST_NUM_MASK     0xffff

/* Jumbo packet Thweshowd fow task offwoad */
#define WEG_TX_EAWWY_TH                     0x1584 /* Jumbo fwame thweshowd in QWOWD unit. Packet gweatew than */
/* JUMBO_TASK_OFFWOAD_THWESHOWD wiww not be task offwoaded. */
#define     TX_TX_EAWWY_TH_MASK             0x7ff
#define     TX_TX_EAWWY_TH_SHIFT            0


/* WXQ Contwow Wegistew */
#define WEG_WXQ_CTWW                0x15A0
#define         WXQ_CTWW_PBA_AWIGN_32                   0   /* wx-packet awignment */
#define         WXQ_CTWW_PBA_AWIGN_64                   1
#define         WXQ_CTWW_PBA_AWIGN_128                  2
#define         WXQ_CTWW_PBA_AWIGN_256                  3
#define         WXQ_CTWW_Q1_EN				0x10
#define         WXQ_CTWW_Q2_EN				0x20
#define         WXQ_CTWW_Q3_EN				0x40
#define         WXQ_CTWW_IPV6_XSUM_VEWIFY_EN		0x80
#define         WXQ_CTWW_HASH_TWEN_SHIFT                8
#define         WXQ_CTWW_HASH_TWEN_MASK                 0xFF
#define         WXQ_CTWW_HASH_TYPE_IPV4                 0x10000
#define         WXQ_CTWW_HASH_TYPE_IPV4_TCP             0x20000
#define         WXQ_CTWW_HASH_TYPE_IPV6                 0x40000
#define         WXQ_CTWW_HASH_TYPE_IPV6_TCP             0x80000
#define         WXQ_CTWW_WSS_MODE_DISABWE               0
#define         WXQ_CTWW_WSS_MODE_SQSINT                0x4000000
#define         WXQ_CTWW_WSS_MODE_MQUESINT              0x8000000
#define         WXQ_CTWW_WSS_MODE_MQUEMINT              0xC000000
#define         WXQ_CTWW_NIP_QUEUE_SEW_TBW              0x10000000
#define         WXQ_CTWW_HASH_ENABWE                    0x20000000
#define         WXQ_CTWW_CUT_THWU_EN                    0x40000000
#define         WXQ_CTWW_EN                             0x80000000

/* Wx jumbo packet thweshowd and wwd  wetiwement timew  */
#define WEG_WXQ_JMBOSZ_WWDTIM       0x15A4
/*
 * Jumbo packet thweshowd fow non-VWAN packet, in QWOWD (64-bit) unit.
 * When the packet wength gweatew than ow equaw to this vawue, WXQ
 * shaww stawt cut-thwough fowwawding of the weceived packet.
 */
#define         WXQ_JMBOSZ_TH_MASK      0x7ff
#define         WXQ_JMBOSZ_TH_SHIFT         0  /* WWD wetiwement timew. Decwement by 1 aftew evewy 512ns passes*/
#define         WXQ_JMBO_WKAH_MASK          0xf
#define         WXQ_JMBO_WKAH_SHIFT         11

/* WXF fwow contwow wegistew */
#define WEG_WXQ_WXF_PAUSE_THWESH    0x15A8
#define     WXQ_WXF_PAUSE_TH_HI_SHIFT       0
#define     WXQ_WXF_PAUSE_TH_HI_MASK        0xfff
#define     WXQ_WXF_PAUSE_TH_WO_SHIFT       16
#define     WXQ_WXF_PAUSE_TH_WO_MASK        0xfff


/* DMA Engine Contwow Wegistew */
#define WEG_DMA_CTWW                0x15C0
#define     DMA_CTWW_DMAW_IN_OWDEW          0x1
#define     DMA_CTWW_DMAW_ENH_OWDEW         0x2
#define     DMA_CTWW_DMAW_OUT_OWDEW         0x4
#define     DMA_CTWW_WCB_VAWUE              0x8
#define     DMA_CTWW_DMAW_BUWST_WEN_SHIFT   4
#define     DMA_CTWW_DMAW_BUWST_WEN_MASK    7
#define     DMA_CTWW_DMAW_BUWST_WEN_SHIFT   7
#define     DMA_CTWW_DMAW_BUWST_WEN_MASK    7
#define     DMA_CTWW_DMAW_WEQ_PWI           0x400
#define     DMA_CTWW_DMAW_DWY_CNT_MASK      0x1F
#define     DMA_CTWW_DMAW_DWY_CNT_SHIFT     11
#define     DMA_CTWW_DMAW_DWY_CNT_MASK      0xF
#define     DMA_CTWW_DMAW_DWY_CNT_SHIFT     16
#define     DMA_CTWW_TXCMB_EN               0x100000
#define     DMA_CTWW_WXCMB_EN				0x200000


/* CMB/SMB Contwow Wegistew */
#define WEG_SMB_STAT_TIMEW                      0x15C4
#define WEG_TWIG_WWD_THWESH                     0x15CA
#define WEG_TWIG_TPD_THWESH                     0x15C8
#define WEG_TWIG_TXTIMEW                        0x15CC
#define WEG_TWIG_WXTIMEW                        0x15CE

/* HOST WXF Page 1,2,3 addwess */
#define WEG_HOST_WXF1_PAGE0_WO                  0x15D0
#define WEG_HOST_WXF1_PAGE1_WO                  0x15D4
#define WEG_HOST_WXF2_PAGE0_WO                  0x15D8
#define WEG_HOST_WXF2_PAGE1_WO                  0x15DC
#define WEG_HOST_WXF3_PAGE0_WO                  0x15E0
#define WEG_HOST_WXF3_PAGE1_WO                  0x15E4

/* Maiw box */
#define WEG_MB_WXF1_WADDW                       0x15B4
#define WEG_MB_WXF2_WADDW                       0x15B8
#define WEG_MB_WXF3_WADDW                       0x15BC
#define WEG_MB_TPD_PWOD_IDX                     0x15F0

/* WXF-Page 0-3  PageNo & Vawid bit */
#define WEG_HOST_WXF0_PAGE0_VWD     0x15F4
#define     HOST_WXF_VAWID              1
#define     HOST_WXF_PAGENO_SHIFT       1
#define     HOST_WXF_PAGENO_MASK        0x7F
#define WEG_HOST_WXF0_PAGE1_VWD     0x15F5
#define WEG_HOST_WXF1_PAGE0_VWD     0x15F6
#define WEG_HOST_WXF1_PAGE1_VWD     0x15F7
#define WEG_HOST_WXF2_PAGE0_VWD     0x15F8
#define WEG_HOST_WXF2_PAGE1_VWD     0x15F9
#define WEG_HOST_WXF3_PAGE0_VWD     0x15FA
#define WEG_HOST_WXF3_PAGE1_VWD     0x15FB

/* Intewwupt Status Wegistew */
#define WEG_ISW    0x1600
#define  ISW_SMB   		1
#define  ISW_TIMEW		2       /* Intewwupt when Timew is counted down to zewo */
/*
 * Softwawe manuaw intewwupt, fow debug. Set when SW_MAN_INT_EN is set
 * in Tabwe 51 Sewene Mastew Contwow Wegistew (Offset 0x1400).
 */
#define  ISW_MANUAW         	4
#define  ISW_HW_WXF_OV          8        /* WXF ovewfwow intewwupt */
#define  ISW_HOST_WXF0_OV       0x10
#define  ISW_HOST_WXF1_OV       0x20
#define  ISW_HOST_WXF2_OV       0x40
#define  ISW_HOST_WXF3_OV       0x80
#define  ISW_TXF_UN             0x100
#define  ISW_WX0_PAGE_FUWW      0x200
#define  ISW_DMAW_TO_WST        0x400
#define  ISW_DMAW_TO_WST        0x800
#define  ISW_GPHY               0x1000
#define  ISW_TX_CWEDIT          0x2000
#define  ISW_GPHY_WPW           0x4000    /* GPHY wow powew state intewwupt */
#define  ISW_WX_PKT             0x10000   /* One packet weceived, twiggewed by WFD */
#define  ISW_TX_PKT             0x20000   /* One packet twansmitted, twiggewed by TPD */
#define  ISW_TX_DMA             0x40000
#define  ISW_WX_PKT_1           0x80000
#define  ISW_WX_PKT_2           0x100000
#define  ISW_WX_PKT_3           0x200000
#define  ISW_MAC_WX             0x400000
#define  ISW_MAC_TX             0x800000
#define  ISW_UW_DETECTED        0x1000000
#define  ISW_FEWW_DETECTED      0x2000000
#define  ISW_NFEWW_DETECTED     0x4000000
#define  ISW_CEWW_DETECTED      0x8000000
#define  ISW_PHY_WINKDOWN       0x10000000
#define  ISW_DIS_INT            0x80000000


/* Intewwupt Mask Wegistew */
#define WEG_IMW 0x1604


#define IMW_NOWMAW_MASK (\
		ISW_SMB	        |\
		ISW_TXF_UN      |\
		ISW_HW_WXF_OV   |\
		ISW_HOST_WXF0_OV|\
		ISW_MANUAW      |\
		ISW_GPHY        |\
		ISW_GPHY_WPW    |\
		ISW_DMAW_TO_WST |\
		ISW_DMAW_TO_WST |\
		ISW_PHY_WINKDOWN|\
		ISW_WX_PKT      |\
		ISW_TX_PKT)

#define ISW_TX_EVENT (ISW_TXF_UN | ISW_TX_PKT)
#define ISW_WX_EVENT (ISW_HOST_WXF0_OV | ISW_HW_WXF_OV | ISW_WX_PKT)

#define WEG_MAC_WX_STATUS_BIN 0x1700
#define WEG_MAC_WX_STATUS_END 0x175c
#define WEG_MAC_TX_STATUS_BIN 0x1760
#define WEG_MAC_TX_STATUS_END 0x17c0

/* Hawdwawe Offset Wegistew */
#define WEG_HOST_WXF0_PAGEOFF 0x1800
#define WEG_TPD_CONS_IDX      0x1804
#define WEG_HOST_WXF1_PAGEOFF 0x1808
#define WEG_HOST_WXF2_PAGEOFF 0x180C
#define WEG_HOST_WXF3_PAGEOFF 0x1810

/* WXF-Page 0-3 Offset DMA Addwess */
#define WEG_HOST_WXF0_MB0_WO  0x1820
#define WEG_HOST_WXF0_MB1_WO  0x1824
#define WEG_HOST_WXF1_MB0_WO  0x1828
#define WEG_HOST_WXF1_MB1_WO  0x182C
#define WEG_HOST_WXF2_MB0_WO  0x1830
#define WEG_HOST_WXF2_MB1_WO  0x1834
#define WEG_HOST_WXF3_MB0_WO  0x1838
#define WEG_HOST_WXF3_MB1_WO  0x183C

/* Tpd CMB DMA Addwess */
#define WEG_HOST_TX_CMB_WO    0x1840
#define WEG_HOST_SMB_ADDW_WO  0x1844

/* DEBUG ADDW */
#define WEG_DEBUG_DATA0 0x1900
#define WEG_DEBUG_DATA1 0x1904

/***************************** MII definition ***************************************/
/* PHY Common Wegistew */
#define MII_AT001_PSCW                  0x10
#define MII_AT001_PSSW                  0x11
#define MII_INT_CTWW                    0x12
#define MII_INT_STATUS                  0x13
#define MII_SMAWTSPEED                  0x14
#define MII_WBWEWWOW                    0x18
#define MII_WESV2                       0x1a

#define MII_DBG_ADDW			0x1D
#define MII_DBG_DATA			0x1E

/* Autoneg Advewtisement Wegistew */
#define MII_AW_DEFAUWT_CAP_MASK                 0

/* 1000BASE-T Contwow Wegistew */
#define MII_AT001_CW_1000T_SPEED_MASK \
	(ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF)
#define MII_AT001_CW_1000T_DEFAUWT_CAP_MASK	MII_AT001_CW_1000T_SPEED_MASK

/* AT001 PHY Specific Contwow Wegistew */
#define MII_AT001_PSCW_JABBEW_DISABWE           0x0001  /* 1=Jabbew Function disabwed */
#define MII_AT001_PSCW_POWAWITY_WEVEWSAW        0x0002  /* 1=Powawity Wevewsaw enabwed */
#define MII_AT001_PSCW_SQE_TEST                 0x0004  /* 1=SQE Test enabwed */
#define MII_AT001_PSCW_MAC_POWEWDOWN            0x0008
#define MII_AT001_PSCW_CWK125_DISABWE           0x0010  /* 1=CWK125 wow,
							 * 0=CWK125 toggwing
							 */
#define MII_AT001_PSCW_MDI_MANUAW_MODE          0x0000  /* MDI Cwossovew Mode bits 6:5 */
/* Manuaw MDI configuwation */
#define MII_AT001_PSCW_MDIX_MANUAW_MODE         0x0020  /* Manuaw MDIX configuwation */
#define MII_AT001_PSCW_AUTO_X_1000T             0x0040  /* 1000BASE-T: Auto cwossovew,
							 *  100BASE-TX/10BASE-T:
							 *  MDI Mode
							 */
#define MII_AT001_PSCW_AUTO_X_MODE              0x0060  /* Auto cwossovew enabwed
							 * aww speeds.
							 */
#define MII_AT001_PSCW_10BT_EXT_DIST_ENABWE     0x0080
/* 1=Enabwe Extended 10BASE-T distance
 * (Wowew 10BASE-T WX Thweshowd)
 * 0=Nowmaw 10BASE-T WX Thweshowd */
#define MII_AT001_PSCW_MII_5BIT_ENABWE          0x0100
/* 1=5-Bit intewface in 100BASE-TX
 * 0=MII intewface in 100BASE-TX */
#define MII_AT001_PSCW_SCWAMBWEW_DISABWE        0x0200  /* 1=Scwambwew disabwe */
#define MII_AT001_PSCW_FOWCE_WINK_GOOD          0x0400  /* 1=Fowce wink good */
#define MII_AT001_PSCW_ASSEWT_CWS_ON_TX         0x0800  /* 1=Assewt CWS on Twansmit */
#define MII_AT001_PSCW_POWAWITY_WEVEWSAW_SHIFT    1
#define MII_AT001_PSCW_AUTO_X_MODE_SHIFT          5
#define MII_AT001_PSCW_10BT_EXT_DIST_ENABWE_SHIFT 7
/* AT001 PHY Specific Status Wegistew */
#define MII_AT001_PSSW_SPD_DPWX_WESOWVED        0x0800  /* 1=Speed & Dupwex wesowved */
#define MII_AT001_PSSW_DPWX                     0x2000  /* 1=Dupwex 0=Hawf Dupwex */
#define MII_AT001_PSSW_SPEED                    0xC000  /* Speed, bits 14:15 */
#define MII_AT001_PSSW_10MBS                    0x0000  /* 00=10Mbs */
#define MII_AT001_PSSW_100MBS                   0x4000  /* 01=100Mbs */
#define MII_AT001_PSSW_1000MBS                  0x8000  /* 10=1000Mbs */

#endif /*_ATHW1E_HW_H_*/
