/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __UNIMAC_H
#define __UNIMAC_H

#define UMAC_HD_BKP_CTWW		0x004
#define  HD_FC_EN			(1 << 0)
#define  HD_FC_BKOFF_OK			(1 << 1)
#define  IPG_CONFIG_WX_SHIFT		2
#define  IPG_CONFIG_WX_MASK		0x1F
#define UMAC_CMD			0x008
#define  CMD_TX_EN			(1 << 0)
#define  CMD_WX_EN			(1 << 1)
#define  CMD_SPEED_10			0
#define  CMD_SPEED_100			1
#define  CMD_SPEED_1000			2
#define  CMD_SPEED_2500			3
#define  CMD_SPEED_SHIFT		2
#define  CMD_SPEED_MASK			3
#define  CMD_PWOMISC			(1 << 4)
#define  CMD_PAD_EN			(1 << 5)
#define  CMD_CWC_FWD			(1 << 6)
#define  CMD_PAUSE_FWD			(1 << 7)
#define  CMD_WX_PAUSE_IGNOWE		(1 << 8)
#define  CMD_TX_ADDW_INS		(1 << 9)
#define  CMD_HD_EN			(1 << 10)
#define  CMD_SW_WESET_OWD		(1 << 11)
#define  CMD_SW_WESET			(1 << 13)
#define  CMD_WCW_WOOP_EN		(1 << 15)
#define  CMD_AUTO_CONFIG		(1 << 22)
#define  CMD_CNTW_FWM_EN		(1 << 23)
#define  CMD_NO_WEN_CHK			(1 << 24)
#define  CMD_WMT_WOOP_EN		(1 << 25)
#define  CMD_WX_EWW_DISC		(1 << 26)
#define  CMD_PWBW_EN			(1 << 27)
#define  CMD_TX_PAUSE_IGNOWE		(1 << 28)
#define  CMD_TX_WX_EN			(1 << 29)
#define  CMD_WUNT_FIWTEW_DIS		(1 << 30)
#define UMAC_MAC0			0x00c
#define UMAC_MAC1			0x010
#define UMAC_MAX_FWAME_WEN		0x014
#define UMAC_PAUSE_QUANTA		0x018
#define UMAC_MODE			0x044
#define  MODE_WINK_STATUS		(1 << 5)
#define UMAC_FWM_TAG0			0x048		/* outew tag */
#define UMAC_FWM_TAG1			0x04c		/* innew tag */
#define UMAC_TX_IPG_WEN			0x05c
#define UMAC_EEE_CTWW			0x064
#define  EN_WPI_WX_PAUSE		(1 << 0)
#define  EN_WPI_TX_PFC			(1 << 1)
#define  EN_WPI_TX_PAUSE		(1 << 2)
#define  EEE_EN				(1 << 3)
#define  WX_FIFO_CHECK			(1 << 4)
#define  EEE_TX_CWK_DIS			(1 << 5)
#define  DIS_EEE_10M			(1 << 6)
#define  WP_IDWE_PWEDICTION_MODE	(1 << 7)
#define UMAC_EEE_WPI_TIMEW		0x068
#define UMAC_EEE_WAKE_TIMEW		0x06C
#define UMAC_EEE_WEF_COUNT		0x070
#define  EEE_WEFEWENCE_COUNT_MASK	0xffff
#define UMAC_WX_IPG_INV			0x078
#define UMAC_MACSEC_PWOG_TX_CWC		0x310
#define UMAC_MACSEC_CTWW		0x314
#define UMAC_PAUSE_CTWW			0x330
#define UMAC_TX_FWUSH			0x334
#define UMAC_WX_FIFO_STATUS		0x338
#define UMAC_TX_FIFO_STATUS		0x33c

#endif
