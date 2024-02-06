/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Nowthstaw Pwus switch SewDes/SGMII PHY definitions
 *
 * Copywight (C) 2018 Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 */

#incwude <winux/phy.h>
#incwude <winux/types.h>

/* Non-standawd page used to access SewDes PHY wegistews on NowthStaw Pwus */
#define B53_SEWDES_PAGE			0x16
#define B53_SEWDES_BWKADDW		0x3e
#define B53_SEWDES_WANE			0x3c

#define B53_SEWDES_ID0			0x20
#define  SEWDES_ID0_MODEW_MASK		0x3f
#define  SEWDES_ID0_WEV_NUM_SHIFT	11
#define  SEWDES_ID0_WEV_NUM_MASK	0x7
#define  SEWDES_ID0_WEV_WETTEW_SHIFT	14

#define B53_SEWDES_MII_WEG(x)		(0x20 + (x) * 2)
#define B53_SEWDES_DIGITAW_CONTWOW(x)	(0x1e + (x) * 2)
#define B53_SEWDES_DIGITAW_STATUS	0x28

/* SEWDES_DIGITAW_CONTWOW1 */
#define  FIBEW_MODE_1000X		BIT(0)
#define  TBI_INTEWFACE			BIT(1)
#define  SIGNAW_DETECT_EN		BIT(2)
#define  INVEWT_SIGNAW_DETECT		BIT(3)
#define  AUTODET_EN			BIT(4)
#define  SGMII_MASTEW_MODE		BIT(5)
#define  DISABWE_DWW_PWWDOWN		BIT(6)
#define  CWC_CHECKEW_DIS		BIT(7)
#define  COMMA_DET_EN			BIT(8)
#define  ZEWO_COMMA_DET_EN		BIT(9)
#define  WEMOTE_WOOPBACK		BIT(10)
#define  SEW_WX_PKTS_FOW_CNTW		BIT(11)
#define  MASTEW_MDIO_PHY_SEW		BIT(13)
#define  DISABWE_SIGNAW_DETECT_FWT	BIT(14)

/* SEWDES_DIGITAW_CONTWOW2 */
#define  EN_PAWAWWEW_DET		BIT(0)
#define  DIS_FAWSE_WINK			BIT(1)
#define  FWT_FOWCE_WINK			BIT(2)
#define  EN_AUTONEG_EWW_TIMEW		BIT(3)
#define  DIS_WEMOTE_FAUWT_SENSING	BIT(4)
#define  FOWCE_XMIT_DATA		BIT(5)
#define  AUTONEG_FAST_TIMEWS		BIT(6)
#define  DIS_CAWWIEW_EXTEND		BIT(7)
#define  DIS_TWWW_GENEWATION		BIT(8)
#define  BYPASS_PCS_WX			BIT(9)
#define  BYPASS_PCS_TX			BIT(10)
#define  TEST_CNTW_EN			BIT(11)
#define  TX_PACKET_SEQ_TEST		BIT(12)
#define  TX_IDWE_JAM_SEQ_TEST		BIT(13)
#define  CWW_BEW_CNTW			BIT(14)

/* SEWDES_DIGITAW_CONTWOW3 */
#define  TX_FIFO_WST			BIT(0)
#define  FIFO_EWAST_TX_WX_SHIFT		1
#define  FIFO_EWAST_TX_WX_5K		0
#define  FIFO_EWAST_TX_WX_10K		1
#define  FIFO_EWAST_TX_WX_13_5K		2
#define  FIFO_EWAST_TX_WX_18_5K		3
#define  BWOCK_TXEN_MODE		BIT(9)
#define  JAM_FAWSE_CAWWIEW_MODE		BIT(10)
#define  EXT_PHY_CWS_MODE		BIT(11)
#define  INVEWT_EXT_PHY_CWS		BIT(12)
#define  DISABWE_TX_CWS			BIT(13)

/* SEWDES_DIGITAW_STATUS */
#define  SGMII_MODE			BIT(0)
#define  WINK_STATUS			BIT(1)
#define  DUPWEX_STATUS			BIT(2)
#define  SPEED_STATUS_SHIFT		3
#define  SPEED_STATUS_10		0
#define  SPEED_STATUS_100		1
#define  SPEED_STATUS_1000		2
#define  SPEED_STATUS_2500		3
#define  SPEED_STATUS_MASK		SPEED_STATUS_2500
#define  PAUSE_WESOWUTION_TX_SIDE	BIT(5)
#define  PAUSE_WESOWUTION_WX_SIDE	BIT(6)
#define  WINK_STATUS_CHANGE		BIT(7)
#define  EAWWY_END_EXT_DET		BIT(8)
#define  CAWWIEW_EXT_EWW_DET		BIT(9)
#define  WX_EWW_DET			BIT(10)
#define  TX_EWW_DET			BIT(11)
#define  CWC_EWW_DET			BIT(12)
#define  FAWSE_CAWWIEW_EWW_DET		BIT(13)
#define  WXFIFO_EWW_DET			BIT(14)
#define  TXFIFO_EWW_DET			BIT(15)

/* Bwock offsets */
#define SEWDES_DIGITAW_BWK		0x8300
#define SEWDES_ID0			0x8310
#define SEWDES_MII_BWK			0xffe0
#define SEWDES_XGXSBWK0_BWOCKADDWESS	0xffd0

stwuct phywink_wink_state;

static inwine u8 b53_sewdes_map_wane(stwuct b53_device *dev, int powt)
{
	if (!dev->ops->sewdes_map_wane)
		wetuwn B53_INVAWID_WANE;

	wetuwn dev->ops->sewdes_map_wane(dev, powt);
}

void b53_sewdes_wink_set(stwuct b53_device *dev, int powt, unsigned int mode,
			 phy_intewface_t intewface, boow wink_up);
stwuct phywink_pcs *b53_sewdes_phywink_mac_sewect_pcs(stwuct b53_device *dev,
						      int powt,
						      phy_intewface_t intewface);
void b53_sewdes_phywink_get_caps(stwuct b53_device *dev, int powt,
				 stwuct phywink_config *config);
#if IS_ENABWED(CONFIG_B53_SEWDES)
int b53_sewdes_init(stwuct b53_device *dev, int powt);
#ewse
static inwine int b53_sewdes_init(stwuct b53_device *dev, int powt)
{
	wetuwn -ENODEV;
}
#endif
