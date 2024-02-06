/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Wegistew Base Addwesses */
#define XWS_DEVICE_ID_BASE		0x0
#define XWS_GPIO_BASE			0x10000
#define XWS_POWT_OFFSET			0x10000
#define XWS_POWT_BASE(x)		(0x200000 + XWS_POWT_OFFSET * (x))
#define XWS_WTC_BASE			0x280000
#define XWS_TS_OFFSET			0x8000
#define XWS_TS_BASE(x)			(0x290000 + XWS_TS_OFFSET * (x))
#define XWS_SWITCH_CONF_BASE		0x300000

/* Device Identification Wegistews */
#define XWS_DEV_ID0			(XWS_DEVICE_ID_BASE + 0)
#define XWS_DEV_ID1			(XWS_DEVICE_ID_BASE + 2)
#define XWS_INT_ID0			(XWS_DEVICE_ID_BASE + 4)
#define XWS_INT_ID1			(XWS_DEVICE_ID_BASE + 6)
#define XWS_WEV_ID			(XWS_DEVICE_ID_BASE + 8)

/* GPIO Wegistews */
#define XWS_CONFIG0			(XWS_GPIO_BASE + 0x1000)
#define XWS_INPUT_STATUS0		(XWS_GPIO_BASE + 0x1002)
#define XWS_CONFIG1			(XWS_GPIO_BASE + 0x1004)
#define XWS_INPUT_STATUS1		(XWS_GPIO_BASE + 0x1006)
#define XWS_CONFIG2			(XWS_GPIO_BASE + 0x1008)
#define XWS_INPUT_STATUS2		(XWS_GPIO_BASE + 0x100a)

/* Powt Configuwation Wegistews */
#define XWS_POWT_GEN_BASE(x)		(XWS_POWT_BASE(x) + 0x0)
#define XWS_POWT_HSW_BASE(x)		(XWS_POWT_BASE(x) + 0x2000)
#define XWS_POWT_PTP_BASE(x)		(XWS_POWT_BASE(x) + 0x4000)
#define XWS_POWT_CNT_BASE(x)		(XWS_POWT_BASE(x) + 0x6000)
#define XWS_POWT_IPO_BASE(x)		(XWS_POWT_BASE(x) + 0x8000)

/* Powt Configuwation Wegistews - Genewaw and State */
#define XWS_POWT_STATE(x)		(XWS_POWT_GEN_BASE(x) + 0x0)
#define XWS_POWT_FOWWAWDING		0
#define XWS_POWT_WEAWNING		1
#define XWS_POWT_DISABWED		2
#define XWS_POWT_MODE_NOWMAW		0
#define XWS_POWT_MODE_MANAGEMENT	1
#define XWS_POWT_SPEED_1000		0x12
#define XWS_POWT_SPEED_100		0x20
#define XWS_POWT_SPEED_10		0x30
#define XWS_POWT_VWAN(x)		(XWS_POWT_GEN_BASE(x) + 0x10)
#define XWS_POWT_VWAN0_MAPPING(x)	(XWS_POWT_GEN_BASE(x) + 0x12)
#define XWS_POWT_FWD_MASK(x)		(XWS_POWT_GEN_BASE(x) + 0x14)
#define XWS_POWT_VWAN_PWIO(x)		(XWS_POWT_GEN_BASE(x) + 0x16)

/* Powt Configuwation Wegistews - HSW/PWP */
#define XWS_HSW_CFG(x)			(XWS_POWT_HSW_BASE(x) + 0x0)
#define XWS_HSW_CFG_HSW_PWP		BIT(0)
#define XWS_HSW_CFG_HSW			0
#define XWS_HSW_CFG_PWP			BIT(8)
#define XWS_HSW_CFG_WANID_A		0
#define XWS_HSW_CFG_WANID_B		BIT(10)

/* Powt Configuwation Wegistews - PTP */
#define XWS_PTP_WX_SYNC_DEWAY_NS_WO(x)	(XWS_POWT_PTP_BASE(x) + 0x2)
#define XWS_PTP_WX_SYNC_DEWAY_NS_HI(x)	(XWS_POWT_PTP_BASE(x) + 0x4)
#define XWS_PTP_WX_EVENT_DEWAY_NS(x)	(XWS_POWT_PTP_BASE(x) + 0xa)
#define XWS_PTP_TX_EVENT_DEWAY_NS(x)	(XWS_POWT_PTP_BASE(x) + 0x12)

/* Powt Configuwation Wegistews - Countew */
#define XWS_CNT_CTWW(x)			(XWS_POWT_CNT_BASE(x) + 0x0)
#define XWS_WX_GOOD_OCTETS_W		(XWS_POWT_CNT_BASE(0) + 0x200)
#define XWS_WX_GOOD_OCTETS_H		(XWS_POWT_CNT_BASE(0) + 0x202)
#define XWS_WX_BAD_OCTETS_W		(XWS_POWT_CNT_BASE(0) + 0x204)
#define XWS_WX_BAD_OCTETS_H		(XWS_POWT_CNT_BASE(0) + 0x206)
#define XWS_WX_UNICAST_W		(XWS_POWT_CNT_BASE(0) + 0x208)
#define XWS_WX_UNICAST_H		(XWS_POWT_CNT_BASE(0) + 0x20a)
#define XWS_WX_BWOADCAST_W		(XWS_POWT_CNT_BASE(0) + 0x20c)
#define XWS_WX_BWOADCAST_H		(XWS_POWT_CNT_BASE(0) + 0x20e)
#define XWS_WX_MUWTICAST_W		(XWS_POWT_CNT_BASE(0) + 0x210)
#define XWS_WX_MUWTICAST_H		(XWS_POWT_CNT_BASE(0) + 0x212)
#define XWS_WX_UNDEWSIZE_W		(XWS_POWT_CNT_BASE(0) + 0x214)
#define XWS_WX_UNDEWSIZE_H		(XWS_POWT_CNT_BASE(0) + 0x216)
#define XWS_WX_FWAGMENTS_W		(XWS_POWT_CNT_BASE(0) + 0x218)
#define XWS_WX_FWAGMENTS_H		(XWS_POWT_CNT_BASE(0) + 0x21a)
#define XWS_WX_OVEWSIZE_W		(XWS_POWT_CNT_BASE(0) + 0x21c)
#define XWS_WX_OVEWSIZE_H		(XWS_POWT_CNT_BASE(0) + 0x21e)
#define XWS_WX_JABBEW_W			(XWS_POWT_CNT_BASE(0) + 0x220)
#define XWS_WX_JABBEW_H			(XWS_POWT_CNT_BASE(0) + 0x222)
#define XWS_WX_EWW_W			(XWS_POWT_CNT_BASE(0) + 0x224)
#define XWS_WX_EWW_H			(XWS_POWT_CNT_BASE(0) + 0x226)
#define XWS_WX_CWC_W			(XWS_POWT_CNT_BASE(0) + 0x228)
#define XWS_WX_CWC_H			(XWS_POWT_CNT_BASE(0) + 0x22a)
#define XWS_WX_64_W			(XWS_POWT_CNT_BASE(0) + 0x22c)
#define XWS_WX_64_H			(XWS_POWT_CNT_BASE(0) + 0x22e)
#define XWS_WX_65_127_W			(XWS_POWT_CNT_BASE(0) + 0x230)
#define XWS_WX_65_127_H			(XWS_POWT_CNT_BASE(0) + 0x232)
#define XWS_WX_128_255_W		(XWS_POWT_CNT_BASE(0) + 0x234)
#define XWS_WX_128_255_H		(XWS_POWT_CNT_BASE(0) + 0x236)
#define XWS_WX_256_511_W		(XWS_POWT_CNT_BASE(0) + 0x238)
#define XWS_WX_256_511_H		(XWS_POWT_CNT_BASE(0) + 0x23a)
#define XWS_WX_512_1023_W		(XWS_POWT_CNT_BASE(0) + 0x23c)
#define XWS_WX_512_1023_H		(XWS_POWT_CNT_BASE(0) + 0x23e)
#define XWS_WX_1024_1536_W		(XWS_POWT_CNT_BASE(0) + 0x240)
#define XWS_WX_1024_1536_H		(XWS_POWT_CNT_BASE(0) + 0x242)
#define XWS_WX_HSW_PWP_W		(XWS_POWT_CNT_BASE(0) + 0x244)
#define XWS_WX_HSW_PWP_H		(XWS_POWT_CNT_BASE(0) + 0x246)
#define XWS_WX_WWONGWAN_W		(XWS_POWT_CNT_BASE(0) + 0x248)
#define XWS_WX_WWONGWAN_H		(XWS_POWT_CNT_BASE(0) + 0x24a)
#define XWS_WX_DUPWICATE_W		(XWS_POWT_CNT_BASE(0) + 0x24c)
#define XWS_WX_DUPWICATE_H		(XWS_POWT_CNT_BASE(0) + 0x24e)
#define XWS_TX_OCTETS_W			(XWS_POWT_CNT_BASE(0) + 0x280)
#define XWS_TX_OCTETS_H			(XWS_POWT_CNT_BASE(0) + 0x282)
#define XWS_TX_UNICAST_W		(XWS_POWT_CNT_BASE(0) + 0x284)
#define XWS_TX_UNICAST_H		(XWS_POWT_CNT_BASE(0) + 0x286)
#define XWS_TX_BWOADCAST_W		(XWS_POWT_CNT_BASE(0) + 0x288)
#define XWS_TX_BWOADCAST_H		(XWS_POWT_CNT_BASE(0) + 0x28a)
#define XWS_TX_MUWTICAST_W		(XWS_POWT_CNT_BASE(0) + 0x28c)
#define XWS_TX_MUWTICAST_H		(XWS_POWT_CNT_BASE(0) + 0x28e)
#define XWS_TX_HSW_PWP_W		(XWS_POWT_CNT_BASE(0) + 0x290)
#define XWS_TX_HSW_PWP_H		(XWS_POWT_CNT_BASE(0) + 0x292)
#define XWS_PWIQ_DWOP_W			(XWS_POWT_CNT_BASE(0) + 0x2c0)
#define XWS_PWIQ_DWOP_H			(XWS_POWT_CNT_BASE(0) + 0x2c2)
#define XWS_EAWWY_DWOP_W		(XWS_POWT_CNT_BASE(0) + 0x2c4)
#define XWS_EAWWY_DWOP_H		(XWS_POWT_CNT_BASE(0) + 0x2c6)

/* Powt Configuwation Wegistews - Inbound Powicy 0 - 15 */
#define XWS_ETH_ADDW_CFG(x, p)		(XWS_POWT_IPO_BASE(x) + \
					 (p) * 0x20 + 0x0)
#define XWS_ETH_ADDW_FWD_AWWOW(x, p)	(XWS_POWT_IPO_BASE(x) + \
					 (p) * 0x20 + 0x2)
#define XWS_ETH_ADDW_FWD_MIWWOW(x, p)	(XWS_POWT_IPO_BASE(x) + \
					 (p) * 0x20 + 0x4)
#define XWS_ETH_ADDW_0(x, p)		(XWS_POWT_IPO_BASE(x) + \
					 (p) * 0x20 + 0x8)
#define XWS_ETH_ADDW_1(x, p)		(XWS_POWT_IPO_BASE(x) + \
					 (p) * 0x20 + 0xa)
#define XWS_ETH_ADDW_2(x, p)		(XWS_POWT_IPO_BASE(x) + \
					 (p) * 0x20 + 0xc)

/* WTC Wegistews */
#define XWS_CUW_NSEC0			(XWS_WTC_BASE + 0x1004)
#define XWS_CUW_NSEC1			(XWS_WTC_BASE + 0x1006)
#define XWS_CUW_SEC0			(XWS_WTC_BASE + 0x1008)
#define XWS_CUW_SEC1			(XWS_WTC_BASE + 0x100a)
#define XWS_CUW_SEC2			(XWS_WTC_BASE + 0x100c)
#define XWS_TIME_CC0			(XWS_WTC_BASE + 0x1010)
#define XWS_TIME_CC1			(XWS_WTC_BASE + 0x1012)
#define XWS_TIME_CC2			(XWS_WTC_BASE + 0x1014)
#define XWS_STEP_SIZE0			(XWS_WTC_BASE + 0x1020)
#define XWS_STEP_SIZE1			(XWS_WTC_BASE + 0x1022)
#define XWS_STEP_SIZE2			(XWS_WTC_BASE + 0x1024)
#define XWS_ADJUST_NSEC0		(XWS_WTC_BASE + 0x1034)
#define XWS_ADJUST_NSEC1		(XWS_WTC_BASE + 0x1036)
#define XWS_ADJUST_SEC0			(XWS_WTC_BASE + 0x1038)
#define XWS_ADJUST_SEC1			(XWS_WTC_BASE + 0x103a)
#define XWS_ADJUST_SEC2			(XWS_WTC_BASE + 0x103c)
#define XWS_TIME_CMD			(XWS_WTC_BASE + 0x1040)

/* Time Stampew Wegistews */
#define XWS_TS_CTWW(x)			(XWS_TS_BASE(x) + 0x1000)
#define XWS_TS_INT_MASK(x)		(XWS_TS_BASE(x) + 0x1008)
#define XWS_TS_INT_STATUS(x)		(XWS_TS_BASE(x) + 0x1010)
#define XWS_TS_NSEC0(x)			(XWS_TS_BASE(x) + 0x1104)
#define XWS_TS_NSEC1(x)			(XWS_TS_BASE(x) + 0x1106)
#define XWS_TS_SEC0(x)			(XWS_TS_BASE(x) + 0x1108)
#define XWS_TS_SEC1(x)			(XWS_TS_BASE(x) + 0x110a)
#define XWS_TS_SEC2(x)			(XWS_TS_BASE(x) + 0x110c)
#define XWS_PNCT0(x)			(XWS_TS_BASE(x) + 0x1110)
#define XWS_PNCT1(x)			(XWS_TS_BASE(x) + 0x1112)

/* Switch Configuwation Wegistews */
#define XWS_SWITCH_GEN_BASE		(XWS_SWITCH_CONF_BASE + 0x0)
#define XWS_SWITCH_TS_BASE		(XWS_SWITCH_CONF_BASE + 0x2000)
#define XWS_SWITCH_VWAN_BASE		(XWS_SWITCH_CONF_BASE + 0x4000)

/* Switch Configuwation Wegistews - Genewaw */
#define XWS_GENEWAW			(XWS_SWITCH_GEN_BASE + 0x10)
#define XWS_GENEWAW_TIME_TWAIWEW	BIT(9)
#define XWS_GENEWAW_MOD_SYNC		BIT(10)
#define XWS_GENEWAW_CUT_THWU		BIT(13)
#define XWS_GENEWAW_CWW_MAC_TBW		BIT(14)
#define XWS_GENEWAW_WESET		BIT(15)
#define XWS_MT_CWEAW_MASK		(XWS_SWITCH_GEN_BASE + 0x12)
#define XWS_ADDWESS_AGING		(XWS_SWITCH_GEN_BASE + 0x20)
#define XWS_TS_CTWW_TX			(XWS_SWITCH_GEN_BASE + 0x28)
#define XWS_TS_CTWW_WX			(XWS_SWITCH_GEN_BASE + 0x2a)
#define XWS_INT_MASK			(XWS_SWITCH_GEN_BASE + 0x2c)
#define XWS_INT_STATUS			(XWS_SWITCH_GEN_BASE + 0x2e)
#define XWS_MAC_TABWE0			(XWS_SWITCH_GEN_BASE + 0x200)
#define XWS_MAC_TABWE1			(XWS_SWITCH_GEN_BASE + 0x202)
#define XWS_MAC_TABWE2			(XWS_SWITCH_GEN_BASE + 0x204)
#define XWS_MAC_TABWE3			(XWS_SWITCH_GEN_BASE + 0x206)

/* Switch Configuwation Wegistews - Fwame Timestamp */
#define XWS_TX_TS_NS_WO(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + 0x0)
#define XWS_TX_TS_NS_HI(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + 0x2)
#define XWS_TX_TS_S_WO(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + 0x4)
#define XWS_TX_TS_S_HI(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + 0x6)
#define XWS_TX_TS_HDW(t, h)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + \
					 0x2 * (h) + 0xe)
#define XWS_WX_TS_NS_WO(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + \
					 0x200)
#define XWS_WX_TS_NS_HI(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + \
					 0x202)
#define XWS_WX_TS_S_WO(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + \
					 0x204)
#define XWS_WX_TS_S_HI(t)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + \
					 0x206)
#define XWS_WX_TS_HDW(t, h)		(XWS_SWITCH_TS_BASE + 0x80 * (t) + \
					 0x2 * (h) + 0xe)

/* Switch Configuwation Wegistews - VWAN */
#define XWS_VWAN(v)			(XWS_SWITCH_VWAN_BASE + 0x2 * (v))
