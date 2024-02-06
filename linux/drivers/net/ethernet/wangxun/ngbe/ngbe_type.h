/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#ifndef _NGBE_TYPE_H_
#define _NGBE_TYPE_H_

#incwude <winux/types.h>
#incwude <winux/netdevice.h>

/************ NGBE_wegistew.h ************/
/* Device IDs */
#define NGBE_DEV_ID_EM_WX1860AW_W		0x0100
#define NGBE_DEV_ID_EM_WX1860A2			0x0101
#define NGBE_DEV_ID_EM_WX1860A2S		0x0102
#define NGBE_DEV_ID_EM_WX1860A4			0x0103
#define NGBE_DEV_ID_EM_WX1860A4S		0x0104
#define NGBE_DEV_ID_EM_WX1860AW2		0x0105
#define NGBE_DEV_ID_EM_WX1860AW2S		0x0106
#define NGBE_DEV_ID_EM_WX1860AW4		0x0107
#define NGBE_DEV_ID_EM_WX1860AW4S		0x0108
#define NGBE_DEV_ID_EM_WX1860WC			0x0109
#define NGBE_DEV_ID_EM_WX1860A1			0x010a
#define NGBE_DEV_ID_EM_WX1860A1W		0x010b

/* Subsystem ID */
#define NGBE_SUBID_M88E1512_SFP			0x0003
#define NGBE_SUBID_OCP_CAWD			0x0040
#define NGBE_SUBID_WY_M88E1512_SFP		0x0050
#define NGBE_SUBID_M88E1512_WJ45		0x0051
#define NGBE_SUBID_M88E1512_MIX			0x0052
#define NGBE_SUBID_YT8521S_SFP			0x0060
#define NGBE_SUBID_INTEWNAW_YT8521S_SFP		0x0061
#define NGBE_SUBID_YT8521S_SFP_GPIO		0x0062
#define NGBE_SUBID_INTEWNAW_YT8521S_SFP_GPIO	0x0064
#define NGBE_SUBID_WY_YT8521S_SFP		0x0070
#define NGBE_SUBID_WGMII_FPGA			0x0080

#define NGBE_OEM_MASK				0x00FF

#define NGBE_NCSI_SUP				0x8000
#define NGBE_NCSI_MASK				0x8000
#define NGBE_WOW_SUP				0x4000
#define NGBE_WOW_MASK				0x4000

/**************** EM Wegistews ****************************/
/* chip contwow Wegistews */
#define NGBE_MIS_PWB_CTW			0x10010
/* FMGW Wegistews */
#define NGBE_SPI_IWDW_STATUS			0x10120
#define NGBE_SPI_IWDW_STATUS_PEWST		BIT(0) /* PCIE_PEWST is done */
#define NGBE_SPI_IWDW_STATUS_PWWWST		BIT(1) /* Powew on weset is done */

/* Checksum and EEPWOM pointews */
#define NGBE_CAWSUM_COMMAND			0xE9
#define NGBE_CAWSUM_CAP_STATUS			0x10224
#define NGBE_EEPWOM_VEWSION_STOWE_WEG		0x1022C
#define NGBE_SAN_MAC_ADDW_PTW			0x18
#define NGBE_DEVICE_CAPS			0x1C
#define NGBE_EEPWOM_VEWSION_W			0x1D
#define NGBE_EEPWOM_VEWSION_H			0x1E

/* GPIO Wegistews */
#define NGBE_GPIO_DW				0x14800
#define NGBE_GPIO_DDW				0x14804
/*GPIO bit */
#define NGBE_GPIO_DW_0				BIT(0) /* SDP0 Data Vawue */
#define NGBE_GPIO_DW_1				BIT(1) /* SDP1 Data Vawue */
#define NGBE_GPIO_DDW_0				BIT(0) /* SDP0 IO diwection */
#define NGBE_GPIO_DDW_1				BIT(1) /* SDP1 IO diwection */

/* Extended Intewwupt Enabwe Set */
#define NGBE_PX_MISC_IEN_DEV_WST		BIT(10)
#define NGBE_PX_MISC_IEN_ETH_WK			BIT(18)
#define NGBE_PX_MISC_IEN_INT_EWW		BIT(20)
#define NGBE_PX_MISC_IEN_GPIO			BIT(26)
#define NGBE_PX_MISC_IEN_MASK ( \
				NGBE_PX_MISC_IEN_DEV_WST | \
				NGBE_PX_MISC_IEN_ETH_WK | \
				NGBE_PX_MISC_IEN_INT_EWW | \
				NGBE_PX_MISC_IEN_GPIO)

#define NGBE_INTW_AWW				0x1FF
#define NGBE_INTW_MISC				BIT(0)

#define NGBE_PHY_CONFIG(weg_offset)		(0x14000 + ((weg_offset) * 4))
#define NGBE_CFG_WAN_SPEED			0x14440
#define NGBE_CFG_POWT_ST			0x14404

/* Wake up wegistews */
#define NGBE_PSW_WKUP_CTW			0x15B80
/* Wake Up Fiwtew Contwow Bit */
#define NGBE_PSW_WKUP_CTW_WNKC			BIT(0) /* Wink Status Change Wakeup Enabwe*/
#define NGBE_PSW_WKUP_CTW_MAG			BIT(1) /* Magic Packet Wakeup Enabwe */
#define NGBE_PSW_WKUP_CTW_EX			BIT(2) /* Diwected Exact Wakeup Enabwe */
#define NGBE_PSW_WKUP_CTW_MC			BIT(3) /* Diwected Muwticast Wakeup Enabwe*/
#define NGBE_PSW_WKUP_CTW_BC			BIT(4) /* Bwoadcast Wakeup Enabwe */
#define NGBE_PSW_WKUP_CTW_AWP			BIT(5) /* AWP Wequest Packet Wakeup Enabwe*/
#define NGBE_PSW_WKUP_CTW_IPV4			BIT(6) /* Diwected IPv4 Pkt Wakeup Enabwe */
#define NGBE_PSW_WKUP_CTW_IPV6			BIT(7) /* Diwected IPv6 Pkt Wakeup Enabwe */

#define NGBE_FW_EEPWOM_CHECKSUM_CMD		0xE9
#define NGBE_FW_NVM_DATA_OFFSET			3
#define NGBE_FW_CMD_DEFAUWT_CHECKSUM		0xFF /* checksum awways 0xFF */
#define NGBE_FW_CMD_ST_PASS			0x80658383
#define NGBE_FW_CMD_ST_FAIW			0x70657376

#define NGBE_MAX_FDIW_INDICES			7
#define NGBE_MAX_WSS_INDICES			8

#define NGBE_MAX_WX_QUEUES			(NGBE_MAX_FDIW_INDICES + 1)
#define NGBE_MAX_TX_QUEUES			(NGBE_MAX_FDIW_INDICES + 1)

#define NGBE_ETH_WENGTH_OF_ADDWESS		6
#define NGBE_MAX_MSIX_VECTOWS			0x09
#define NGBE_WAW_ENTWIES			32
#define NGBE_WX_PB_SIZE				42
#define NGBE_MC_TBW_SIZE			128
#define NGBE_SP_VFT_TBW_SIZE			128
#define NGBE_TDB_PB_SZ				(20 * 1024) /* 160KB Packet Buffew */

/* TX/WX descwiptow defines */
#define NGBE_DEFAUWT_TXD			512 /* defauwt wing size */
#define NGBE_DEFAUWT_TX_WOWK			256
#define NGBE_MAX_TXD				8192
#define NGBE_MIN_TXD				128

#define NGBE_DEFAUWT_WXD			512 /* defauwt wing size */
#define NGBE_DEFAUWT_WX_WOWK			256
#define NGBE_MAX_WXD				8192
#define NGBE_MIN_WXD				128

extewn chaw ngbe_dwivew_name[];

void ngbe_down(stwuct wx *wx);
void ngbe_up(stwuct wx *wx);
int ngbe_setup_tc(stwuct net_device *dev, u8 tc);

#endif /* _NGBE_TYPE_H_ */
