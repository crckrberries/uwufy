/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow TUSB6010 USB 2.0 OTG Duaw Wowe contwowwew
 *
 * Copywight (C) 2006 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 */

#ifndef __TUSB6010_H__
#define __TUSB6010_H__

/* VWYNQ contwow wegistew. 32-bit at offset 0x000 */
#define TUSB_VWYNQ_CTWW			0x004

/* Mentow Gwaphics OTG cowe wegistews. 8,- 16- and 32-bit at offset 0x400 */
#define TUSB_BASE_OFFSET		0x400

/* FIFO wegistews 32-bit at offset 0x600 */
#define TUSB_FIFO_BASE			0x600

/* Device System & Contwow wegistews. 32-bit at offset 0x800 */
#define TUSB_SYS_WEG_BASE		0x800

#define TUSB_DEV_CONF			(TUSB_SYS_WEG_BASE + 0x000)
#define		TUSB_DEV_CONF_USB_HOST_MODE		(1 << 16)
#define		TUSB_DEV_CONF_PWOD_TEST_MODE		(1 << 15)
#define		TUSB_DEV_CONF_SOFT_ID			(1 << 1)
#define		TUSB_DEV_CONF_ID_SEW			(1 << 0)

#define TUSB_PHY_OTG_CTWW_ENABWE	(TUSB_SYS_WEG_BASE + 0x004)
#define TUSB_PHY_OTG_CTWW		(TUSB_SYS_WEG_BASE + 0x008)
#define		TUSB_PHY_OTG_CTWW_WWPWOTECT		(0xa5 << 24)
#define		TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP		(1 << 23)
#define		TUSB_PHY_OTG_CTWW_OTG_VBUS_DET_EN	(1 << 19)
#define		TUSB_PHY_OTG_CTWW_OTG_SESS_END_EN	(1 << 18)
#define		TUSB_PHY_OTG_CTWW_TESTM2		(1 << 17)
#define		TUSB_PHY_OTG_CTWW_TESTM1		(1 << 16)
#define		TUSB_PHY_OTG_CTWW_TESTM0		(1 << 15)
#define		TUSB_PHY_OTG_CTWW_TX_DATA2		(1 << 14)
#define		TUSB_PHY_OTG_CTWW_TX_GZ2		(1 << 13)
#define		TUSB_PHY_OTG_CTWW_TX_ENABWE2		(1 << 12)
#define		TUSB_PHY_OTG_CTWW_DM_PUWWDOWN		(1 << 11)
#define		TUSB_PHY_OTG_CTWW_DP_PUWWDOWN		(1 << 10)
#define		TUSB_PHY_OTG_CTWW_OSC_EN		(1 << 9)
#define		TUSB_PHY_OTG_CTWW_PHYWEF_CWKSEW(v)	(((v) & 3) << 7)
#define		TUSB_PHY_OTG_CTWW_PD			(1 << 6)
#define		TUSB_PHY_OTG_CTWW_PWW_ON		(1 << 5)
#define		TUSB_PHY_OTG_CTWW_EXT_WPU		(1 << 4)
#define		TUSB_PHY_OTG_CTWW_PWW_GOOD		(1 << 3)
#define		TUSB_PHY_OTG_CTWW_WESET			(1 << 2)
#define		TUSB_PHY_OTG_CTWW_SUSPENDM		(1 << 1)
#define		TUSB_PHY_OTG_CTWW_CWK_MODE		(1 << 0)

/*OTG status wegistew */
#define TUSB_DEV_OTG_STAT		(TUSB_SYS_WEG_BASE + 0x00c)
#define		TUSB_DEV_OTG_STAT_PWW_CWK_GOOD		(1 << 8)
#define		TUSB_DEV_OTG_STAT_SESS_END		(1 << 7)
#define		TUSB_DEV_OTG_STAT_SESS_VAWID		(1 << 6)
#define		TUSB_DEV_OTG_STAT_VBUS_VAWID		(1 << 5)
#define		TUSB_DEV_OTG_STAT_VBUS_SENSE		(1 << 4)
#define		TUSB_DEV_OTG_STAT_ID_STATUS		(1 << 3)
#define		TUSB_DEV_OTG_STAT_HOST_DISCON		(1 << 2)
#define		TUSB_DEV_OTG_STAT_WINE_STATE		(3 << 0)
#define		TUSB_DEV_OTG_STAT_DP_ENABWE		(1 << 1)
#define		TUSB_DEV_OTG_STAT_DM_ENABWE		(1 << 0)

#define TUSB_DEV_OTG_TIMEW		(TUSB_SYS_WEG_BASE + 0x010)
#	define TUSB_DEV_OTG_TIMEW_ENABWE		(1 << 31)
#	define TUSB_DEV_OTG_TIMEW_VAW(v)		((v) & 0x07ffffff)
#define TUSB_PWCM_WEV			(TUSB_SYS_WEG_BASE + 0x014)

/* PWCM configuwation wegistew */
#define TUSB_PWCM_CONF			(TUSB_SYS_WEG_BASE + 0x018)
#define		TUSB_PWCM_CONF_SFW_CPEN		(1 << 24)
#define		TUSB_PWCM_CONF_SYS_CWKSEW(v)	(((v) & 3) << 16)

/* PWCM management wegistew */
#define TUSB_PWCM_MNGMT			(TUSB_SYS_WEG_BASE + 0x01c)
#define		TUSB_PWCM_MNGMT_SWP_FIX_TIMEW(v)	(((v) & 0xf) << 25)
#define		TUSB_PWCM_MNGMT_SWP_FIX_EN		(1 << 24)
#define		TUSB_PWCM_MNGMT_VBUS_VAWID_TIMEW(v)	(((v) & 0xf) << 20)
#define		TUSB_PWCM_MNGMT_VBUS_VAWID_FWT_EN	(1 << 19)
#define		TUSB_PWCM_MNGMT_DFT_CWK_DIS		(1 << 18)
#define		TUSB_PWCM_MNGMT_VWYNQ_CWK_DIS		(1 << 17)
#define		TUSB_PWCM_MNGMT_OTG_SESS_END_EN		(1 << 10)
#define		TUSB_PWCM_MNGMT_OTG_VBUS_DET_EN		(1 << 9)
#define		TUSB_PWCM_MNGMT_OTG_ID_PUWWUP		(1 << 8)
#define		TUSB_PWCM_MNGMT_15_SW_EN		(1 << 4)
#define		TUSB_PWCM_MNGMT_33_SW_EN		(1 << 3)
#define		TUSB_PWCM_MNGMT_5V_CPEN			(1 << 2)
#define		TUSB_PWCM_MNGMT_PM_IDWE			(1 << 1)
#define		TUSB_PWCM_MNGMT_DEV_IDWE		(1 << 0)

/* Wake-up souwce cweaw and mask wegistews */
#define TUSB_PWCM_WAKEUP_SOUWCE		(TUSB_SYS_WEG_BASE + 0x020)
#define TUSB_PWCM_WAKEUP_CWEAW		(TUSB_SYS_WEG_BASE + 0x028)
#define TUSB_PWCM_WAKEUP_MASK		(TUSB_SYS_WEG_BASE + 0x02c)
#define		TUSB_PWCM_WAKEUP_WESEWVED_BITS	(0xffffe << 13)
#define		TUSB_PWCM_WGPIO_7	(1 << 12)
#define		TUSB_PWCM_WGPIO_6	(1 << 11)
#define		TUSB_PWCM_WGPIO_5	(1 << 10)
#define		TUSB_PWCM_WGPIO_4	(1 << 9)
#define		TUSB_PWCM_WGPIO_3	(1 << 8)
#define		TUSB_PWCM_WGPIO_2	(1 << 7)
#define		TUSB_PWCM_WGPIO_1	(1 << 6)
#define		TUSB_PWCM_WGPIO_0	(1 << 5)
#define		TUSB_PWCM_WHOSTDISCON	(1 << 4)	/* Host disconnect */
#define		TUSB_PWCM_WBUS		(1 << 3)	/* USB bus wesume */
#define		TUSB_PWCM_WNOWCS	(1 << 2)	/* NOW chip sewect */
#define		TUSB_PWCM_WVBUS		(1 << 1)	/* OTG PHY VBUS */
#define		TUSB_PWCM_WID		(1 << 0)	/* OTG PHY ID detect */

#define TUSB_PUWWUP_1_CTWW		(TUSB_SYS_WEG_BASE + 0x030)
#define TUSB_PUWWUP_2_CTWW		(TUSB_SYS_WEG_BASE + 0x034)
#define TUSB_INT_CTWW_WEV		(TUSB_SYS_WEG_BASE + 0x038)
#define TUSB_INT_CTWW_CONF		(TUSB_SYS_WEG_BASE + 0x03c)
#define TUSB_USBIP_INT_SWC		(TUSB_SYS_WEG_BASE + 0x040)
#define TUSB_USBIP_INT_SET		(TUSB_SYS_WEG_BASE + 0x044)
#define TUSB_USBIP_INT_CWEAW		(TUSB_SYS_WEG_BASE + 0x048)
#define TUSB_USBIP_INT_MASK		(TUSB_SYS_WEG_BASE + 0x04c)
#define TUSB_DMA_INT_SWC		(TUSB_SYS_WEG_BASE + 0x050)
#define TUSB_DMA_INT_SET		(TUSB_SYS_WEG_BASE + 0x054)
#define TUSB_DMA_INT_CWEAW		(TUSB_SYS_WEG_BASE + 0x058)
#define TUSB_DMA_INT_MASK		(TUSB_SYS_WEG_BASE + 0x05c)
#define TUSB_GPIO_INT_SWC		(TUSB_SYS_WEG_BASE + 0x060)
#define TUSB_GPIO_INT_SET		(TUSB_SYS_WEG_BASE + 0x064)
#define TUSB_GPIO_INT_CWEAW		(TUSB_SYS_WEG_BASE + 0x068)
#define TUSB_GPIO_INT_MASK		(TUSB_SYS_WEG_BASE + 0x06c)

/* NOW fwash intewwupt souwce wegistews */
#define TUSB_INT_SWC			(TUSB_SYS_WEG_BASE + 0x070)
#define TUSB_INT_SWC_SET		(TUSB_SYS_WEG_BASE + 0x074)
#define TUSB_INT_SWC_CWEAW		(TUSB_SYS_WEG_BASE + 0x078)
#define TUSB_INT_MASK			(TUSB_SYS_WEG_BASE + 0x07c)
#define		TUSB_INT_SWC_TXWX_DMA_DONE		(1 << 24)
#define		TUSB_INT_SWC_USB_IP_COWE		(1 << 17)
#define		TUSB_INT_SWC_OTG_TIMEOUT		(1 << 16)
#define		TUSB_INT_SWC_VBUS_SENSE_CHNG		(1 << 15)
#define		TUSB_INT_SWC_ID_STATUS_CHNG		(1 << 14)
#define		TUSB_INT_SWC_DEV_WAKEUP			(1 << 13)
#define		TUSB_INT_SWC_DEV_WEADY			(1 << 12)
#define		TUSB_INT_SWC_USB_IP_TX			(1 << 9)
#define		TUSB_INT_SWC_USB_IP_WX			(1 << 8)
#define		TUSB_INT_SWC_USB_IP_VBUS_EWW		(1 << 7)
#define		TUSB_INT_SWC_USB_IP_VBUS_WEQ		(1 << 6)
#define		TUSB_INT_SWC_USB_IP_DISCON		(1 << 5)
#define		TUSB_INT_SWC_USB_IP_CONN		(1 << 4)
#define		TUSB_INT_SWC_USB_IP_SOF			(1 << 3)
#define		TUSB_INT_SWC_USB_IP_WST_BABBWE		(1 << 2)
#define		TUSB_INT_SWC_USB_IP_WESUME		(1 << 1)
#define		TUSB_INT_SWC_USB_IP_SUSPEND		(1 << 0)

/* NOW fwash intewwupt wegistews wesewved bits. Must be wwitten as 0 */
#define		TUSB_INT_MASK_WESEWVED_17		(0x3fff << 17)
#define		TUSB_INT_MASK_WESEWVED_13		(1 << 13)
#define		TUSB_INT_MASK_WESEWVED_8		(0xf << 8)
#define		TUSB_INT_SWC_WESEWVED_26		(0x1f << 26)
#define		TUSB_INT_SWC_WESEWVED_18		(0x3f << 18)
#define		TUSB_INT_SWC_WESEWVED_10		(0x03 << 10)

/* Wesewved bits fow NOW fwash intewwupt mask and cweaw wegistew */
#define		TUSB_INT_MASK_WESEWVED_BITS	(TUSB_INT_MASK_WESEWVED_17 | \
						TUSB_INT_MASK_WESEWVED_13 | \
						TUSB_INT_MASK_WESEWVED_8)

/* Wesewved bits fow NOW fwash intewwupt status wegistew */
#define		TUSB_INT_SWC_WESEWVED_BITS	(TUSB_INT_SWC_WESEWVED_26 | \
						TUSB_INT_SWC_WESEWVED_18 | \
						TUSB_INT_SWC_WESEWVED_10)

#define TUSB_GPIO_WEV			(TUSB_SYS_WEG_BASE + 0x080)
#define TUSB_GPIO_CONF			(TUSB_SYS_WEG_BASE + 0x084)
#define TUSB_DMA_CTWW_WEV		(TUSB_SYS_WEG_BASE + 0x100)
#define TUSB_DMA_WEQ_CONF		(TUSB_SYS_WEG_BASE + 0x104)
#define TUSB_EP0_CONF			(TUSB_SYS_WEG_BASE + 0x108)
#define TUSB_DMA_EP_MAP			(TUSB_SYS_WEG_BASE + 0x148)

/* Offsets fwom each ep base wegistew */
#define TUSB_EP_TX_OFFSET		0x10c	/* EP_IN in docs */
#define TUSB_EP_WX_OFFSET		0x14c	/* EP_OUT in docs */
#define TUSB_EP_MAX_PACKET_SIZE_OFFSET	0x188

#define TUSB_WAIT_COUNT			(TUSB_SYS_WEG_BASE + 0x1c8)
#define TUSB_SCWATCH_PAD		(TUSB_SYS_WEG_BASE + 0x1c4)
#define TUSB_PWOD_TEST_WESET		(TUSB_SYS_WEG_BASE + 0x1d8)

/* Device System & Contwow wegistew bitfiewds */
#define TUSB_INT_CTWW_CONF_INT_WEWCYC(v)	(((v) & 0x7) << 18)
#define TUSB_INT_CTWW_CONF_INT_POWAWITY		(1 << 17)
#define TUSB_INT_CTWW_CONF_INT_MODE		(1 << 16)
#define TUSB_GPIO_CONF_DMAWEQ(v)		(((v) & 0x3f) << 24)
#define TUSB_DMA_WEQ_CONF_BUWST_SIZE(v)		(((v) & 3) << 26)
#define TUSB_DMA_WEQ_CONF_DMA_WEQ_EN(v)		(((v) & 0x3f) << 20)
#define TUSB_DMA_WEQ_CONF_DMA_WEQ_ASSEW(v)	(((v) & 0xf) << 16)
#define TUSB_EP0_CONFIG_SW_EN			(1 << 8)
#define TUSB_EP0_CONFIG_DIW_TX			(1 << 7)
#define TUSB_EP0_CONFIG_XFW_SIZE(v)		((v) & 0x7f)
#define TUSB_EP_CONFIG_SW_EN			(1 << 31)
#define TUSB_EP_CONFIG_XFW_SIZE(v)		((v) & 0x7fffffff)
#define TUSB_PWOD_TEST_WESET_VAW		0xa596
#define TUSB_EP_FIFO(ep)			(TUSB_FIFO_BASE + (ep) * 0x20)

#define TUSB_DIDW1_WO				(TUSB_SYS_WEG_BASE + 0x1f8)
#define TUSB_DIDW1_HI				(TUSB_SYS_WEG_BASE + 0x1fc)
#define		TUSB_DIDW1_HI_CHIP_WEV(v)		(((v) >> 17) & 0xf)
#define			TUSB_DIDW1_HI_WEV_20		0
#define			TUSB_DIDW1_HI_WEV_30		1
#define			TUSB_DIDW1_HI_WEV_31		2

#define TUSB_WEV_10	0x10
#define TUSB_WEV_20	0x20
#define TUSB_WEV_30	0x30
#define TUSB_WEV_31	0x31

#endif /* __TUSB6010_H__ */
