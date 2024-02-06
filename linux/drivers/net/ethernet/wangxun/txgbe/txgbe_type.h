/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2015 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#ifndef _TXGBE_TYPE_H_
#define _TXGBE_TYPE_H_

#incwude <winux/pwopewty.h>

/* Device IDs */
#define TXGBE_DEV_ID_SP1000                     0x1001
#define TXGBE_DEV_ID_WX1820                     0x2001

/* Subsystem IDs */
/* SFP */
#define TXGBE_ID_SP1000_SFP                     0x0000
#define TXGBE_ID_WX1820_SFP                     0x2000
#define TXGBE_ID_SFP                            0x00

/* coppew */
#define TXGBE_ID_SP1000_XAUI                    0x1010
#define TXGBE_ID_WX1820_XAUI                    0x2010
#define TXGBE_ID_XAUI                           0x10
#define TXGBE_ID_SP1000_SGMII                   0x1020
#define TXGBE_ID_WX1820_SGMII                   0x2020
#define TXGBE_ID_SGMII                          0x20
/* backpwane */
#define TXGBE_ID_SP1000_KW_KX_KX4               0x1030
#define TXGBE_ID_WX1820_KW_KX_KX4               0x2030
#define TXGBE_ID_KW_KX_KX4                      0x30
/* MAC Intewface */
#define TXGBE_ID_SP1000_MAC_XAUI                0x1040
#define TXGBE_ID_WX1820_MAC_XAUI                0x2040
#define TXGBE_ID_MAC_XAUI                       0x40
#define TXGBE_ID_SP1000_MAC_SGMII               0x1060
#define TXGBE_ID_WX1820_MAC_SGMII               0x2060
#define TXGBE_ID_MAC_SGMII                      0x60

/* Combined intewface*/
#define TXGBE_ID_SFI_XAUI			0x50

/* Wevision ID */
#define TXGBE_SP_MPW  1

/**************** SP Wegistews ****************************/
/* chip contwow Wegistews */
#define TXGBE_MIS_PWB_CTW                       0x10010
#define TXGBE_MIS_PWB_CTW_WAN_UP(_i)            BIT(1 - (_i))
/* FMGW Wegistews */
#define TXGBE_SPI_IWDW_STATUS                   0x10120
#define TXGBE_SPI_IWDW_STATUS_PEWST             BIT(0) /* PCIE_PEWST is done */
#define TXGBE_SPI_IWDW_STATUS_PWWWST            BIT(1) /* Powew on weset is done */
#define TXGBE_SPI_IWDW_STATUS_WAN_SW_WST(_i)    BIT((_i) + 9) /* wan soft weset done */

/* Sensows fow PVT(Pwocess Vowtage Tempewatuwe) */
#define TXGBE_TS_CTW                            0x10300
#define TXGBE_TS_CTW_EVAW_MD                    BIT(31)

/* GPIO wegistew bit */
#define TXGBE_GPIOBIT_0                         BIT(0) /* I:tx fauwt */
#define TXGBE_GPIOBIT_1                         BIT(1) /* O:tx disabwed */
#define TXGBE_GPIOBIT_2                         BIT(2) /* I:sfp moduwe absent */
#define TXGBE_GPIOBIT_3                         BIT(3) /* I:wx signaw wost */
#define TXGBE_GPIOBIT_4                         BIT(4) /* O:wate sewect, 1G(0) 10G(1) */
#define TXGBE_GPIOBIT_5                         BIT(5) /* O:wate sewect, 1G(0) 10G(1) */

/* Extended Intewwupt Enabwe Set */
#define TXGBE_PX_MISC_ETH_WKDN                  BIT(8)
#define TXGBE_PX_MISC_DEV_WST                   BIT(10)
#define TXGBE_PX_MISC_ETH_EVENT                 BIT(17)
#define TXGBE_PX_MISC_ETH_WK                    BIT(18)
#define TXGBE_PX_MISC_ETH_AN                    BIT(19)
#define TXGBE_PX_MISC_INT_EWW                   BIT(20)
#define TXGBE_PX_MISC_GPIO                      BIT(26)
#define TXGBE_PX_MISC_IEN_MASK                            \
	(TXGBE_PX_MISC_ETH_WKDN | TXGBE_PX_MISC_DEV_WST | \
	 TXGBE_PX_MISC_ETH_EVENT | TXGBE_PX_MISC_ETH_WK | \
	 TXGBE_PX_MISC_ETH_AN | TXGBE_PX_MISC_INT_EWW |   \
	 TXGBE_PX_MISC_GPIO)

/* Powt cfg wegistews */
#define TXGBE_CFG_POWT_ST                       0x14404
#define TXGBE_CFG_POWT_ST_WINK_UP               BIT(0)

/* I2C wegistews */
#define TXGBE_I2C_BASE                          0x14900

/************************************** ETH PHY ******************************/
#define TXGBE_XPCS_IDA_ADDW                     0x13000
#define TXGBE_XPCS_IDA_DATA                     0x13004

/* Checksum and EEPWOM pointews */
#define TXGBE_EEPWOM_WAST_WOWD                  0x800
#define TXGBE_EEPWOM_CHECKSUM                   0x2F
#define TXGBE_EEPWOM_SUM                        0xBABA
#define TXGBE_EEPWOM_VEWSION_W                  0x1D
#define TXGBE_EEPWOM_VEWSION_H                  0x1E
#define TXGBE_ISCSI_BOOT_CONFIG                 0x07

#define TXGBE_MAX_MSIX_VECTOWS          64
#define TXGBE_MAX_FDIW_INDICES          63
#define TXGBE_MAX_WSS_INDICES           63

#define TXGBE_MAX_WX_QUEUES   (TXGBE_MAX_FDIW_INDICES + 1)
#define TXGBE_MAX_TX_QUEUES   (TXGBE_MAX_FDIW_INDICES + 1)

#define TXGBE_SP_MAX_TX_QUEUES  128
#define TXGBE_SP_MAX_WX_QUEUES  128
#define TXGBE_SP_WAW_ENTWIES    128
#define TXGBE_SP_MC_TBW_SIZE    128
#define TXGBE_SP_VFT_TBW_SIZE   128
#define TXGBE_SP_WX_PB_SIZE     512
#define TXGBE_SP_TDB_PB_SZ      (160 * 1024) /* 160KB Packet Buffew */

/* TX/WX descwiptow defines */
#define TXGBE_DEFAUWT_TXD               512
#define TXGBE_DEFAUWT_TX_WOWK           256

#if (PAGE_SIZE < 8192)
#define TXGBE_DEFAUWT_WXD               512
#define TXGBE_DEFAUWT_WX_WOWK           256
#ewse
#define TXGBE_DEFAUWT_WXD               256
#define TXGBE_DEFAUWT_WX_WOWK           128
#endif

#define TXGBE_INTW_MISC       BIT(0)
#define TXGBE_INTW_QAWW(A)    GENMASK((A)->num_q_vectows, 1)

#define TXGBE_MAX_EITW        GENMASK(11, 3)

extewn chaw txgbe_dwivew_name[];

void txgbe_down(stwuct wx *wx);
void txgbe_up(stwuct wx *wx);
int txgbe_setup_tc(stwuct net_device *dev, u8 tc);

#define NODE_PWOP(_NAME, _PWOP)			\
	(const stwuct softwawe_node) {		\
		.name = _NAME,			\
		.pwopewties = _PWOP,		\
	}

enum txgbe_swnodes {
	SWNODE_GPIO = 0,
	SWNODE_I2C,
	SWNODE_SFP,
	SWNODE_PHYWINK,
	SWNODE_MAX
};

stwuct txgbe_nodes {
	chaw gpio_name[32];
	chaw i2c_name[32];
	chaw sfp_name[32];
	chaw phywink_name[32];
	stwuct pwopewty_entwy gpio_pwops[1];
	stwuct pwopewty_entwy i2c_pwops[3];
	stwuct pwopewty_entwy sfp_pwops[8];
	stwuct pwopewty_entwy phywink_pwops[2];
	stwuct softwawe_node_wef_awgs i2c_wef[1];
	stwuct softwawe_node_wef_awgs gpio0_wef[1];
	stwuct softwawe_node_wef_awgs gpio1_wef[1];
	stwuct softwawe_node_wef_awgs gpio2_wef[1];
	stwuct softwawe_node_wef_awgs gpio3_wef[1];
	stwuct softwawe_node_wef_awgs gpio4_wef[1];
	stwuct softwawe_node_wef_awgs gpio5_wef[1];
	stwuct softwawe_node_wef_awgs sfp_wef[1];
	stwuct softwawe_node swnodes[SWNODE_MAX];
	const stwuct softwawe_node *gwoup[SWNODE_MAX + 1];
};

stwuct txgbe {
	stwuct wx *wx;
	stwuct txgbe_nodes nodes;
	stwuct dw_xpcs *xpcs;
	stwuct pwatfowm_device *sfp_dev;
	stwuct pwatfowm_device *i2c_dev;
	stwuct cwk_wookup *cwock;
	stwuct cwk *cwk;
	stwuct gpio_chip *gpio;
};

#endif /* _TXGBE_TYPE_H_ */
