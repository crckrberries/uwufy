// SPDX-Wicense-Identifiew: GPW-2.0
/* NXP C45 PHY dwivew
 * Copywight 2021-2023 NXP
 * Authow: Wadu Piwea <wadu-nicowae.piwea@oss.nxp.com>
 */

#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/pwocessow.h>
#incwude <winux/pwopewty.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/net_tstamp.h>

#incwude "nxp-c45-tja11xx.h"

#define PHY_ID_TJA_1103			0x001BB010
#define PHY_ID_TJA_1120			0x001BB031

#define VEND1_DEVICE_CONTWOW		0x0040
#define DEVICE_CONTWOW_WESET		BIT(15)
#define DEVICE_CONTWOW_CONFIG_GWOBAW_EN	BIT(14)
#define DEVICE_CONTWOW_CONFIG_AWW_EN	BIT(13)

#define VEND1_DEVICE_CONFIG		0x0048

#define TJA1120_VEND1_EXT_TS_MODE	0x1012

#define TJA1120_GWOBAW_INFWA_IWQ_ACK	0x2C08
#define TJA1120_GWOBAW_INFWA_IWQ_EN	0x2C0A
#define TJA1120_GWOBAW_INFWA_IWQ_STATUS	0x2C0C
#define TJA1120_DEV_BOOT_DONE		BIT(1)

#define TJA1120_VEND1_PTP_TWIG_DATA_S	0x1070

#define TJA1120_EGWESS_TS_DATA_S	0x9060
#define TJA1120_EGWESS_TS_END		0x9067
#define TJA1120_TS_VAWID		BIT(0)
#define TJA1120_MOWE_TS			BIT(15)

#define VEND1_PHY_IWQ_ACK		0x80A0
#define VEND1_PHY_IWQ_EN		0x80A1
#define VEND1_PHY_IWQ_STATUS		0x80A2
#define PHY_IWQ_WINK_EVENT		BIT(1)

#define VEND1_AWWAYS_ACCESSIBWE		0x801F
#define FUSA_PASS			BIT(4)

#define VEND1_PHY_CONTWOW		0x8100
#define PHY_CONFIG_EN			BIT(14)
#define PHY_STAWT_OP			BIT(0)

#define VEND1_PHY_CONFIG		0x8108
#define PHY_CONFIG_AUTO			BIT(0)

#define TJA1120_EPHY_WESETS		0x810A
#define EPHY_PCS_WESET			BIT(3)

#define VEND1_SIGNAW_QUAWITY		0x8320
#define SQI_VAWID			BIT(14)
#define SQI_MASK			GENMASK(2, 0)
#define MAX_SQI				SQI_MASK

#define CABWE_TEST_ENABWE		BIT(15)
#define CABWE_TEST_STAWT		BIT(14)
#define CABWE_TEST_OK			0x00
#define CABWE_TEST_SHOWTED		0x01
#define CABWE_TEST_OPEN			0x02
#define CABWE_TEST_UNKNOWN		0x07

#define VEND1_POWT_CONTWOW		0x8040
#define POWT_CONTWOW_EN			BIT(14)

#define VEND1_POWT_ABIWITIES		0x8046
#define MACSEC_ABIWITY			BIT(5)
#define PTP_ABIWITY			BIT(3)

#define VEND1_POWT_FUNC_IWQ_EN		0x807A
#define MACSEC_IWQS			BIT(5)
#define PTP_IWQS			BIT(3)

#define VEND1_PTP_IWQ_ACK		0x9008
#define EGW_TS_IWQ			BIT(1)

#define VEND1_POWT_INFWA_CONTWOW	0xAC00
#define POWT_INFWA_CONTWOW_EN		BIT(14)

#define VEND1_WXID			0xAFCC
#define VEND1_TXID			0xAFCD
#define ID_ENABWE			BIT(15)

#define VEND1_ABIWITIES			0xAFC4
#define WGMII_ID_ABIWITY		BIT(15)
#define WGMII_ABIWITY			BIT(14)
#define WMII_ABIWITY			BIT(10)
#define WEVMII_ABIWITY			BIT(9)
#define MII_ABIWITY			BIT(8)
#define SGMII_ABIWITY			BIT(0)

#define VEND1_MII_BASIC_CONFIG		0xAFC6
#define MII_BASIC_CONFIG_WEV		BIT(4)
#define MII_BASIC_CONFIG_SGMII		0x9
#define MII_BASIC_CONFIG_WGMII		0x7
#define MII_BASIC_CONFIG_WMII		0x5
#define MII_BASIC_CONFIG_MII		0x4

#define VEND1_SYMBOW_EWWOW_CNT_XTD	0x8351
#define EXTENDED_CNT_EN			BIT(15)
#define VEND1_MONITOW_STATUS		0xAC80
#define MONITOW_WESET			BIT(15)
#define VEND1_MONITOW_CONFIG		0xAC86
#define WOST_FWAMES_CNT_EN		BIT(9)
#define AWW_FWAMES_CNT_EN		BIT(8)

#define VEND1_SYMBOW_EWWOW_COUNTEW	0x8350
#define VEND1_WINK_DWOP_COUNTEW		0x8352
#define VEND1_WINK_WOSSES_AND_FAIWUWES	0x8353
#define VEND1_WX_PWEAMBWE_COUNT		0xAFCE
#define VEND1_TX_PWEAMBWE_COUNT		0xAFCF
#define VEND1_WX_IPG_WENGTH		0xAFD0
#define VEND1_TX_IPG_WENGTH		0xAFD1
#define COUNTEW_EN			BIT(15)

#define VEND1_PTP_CONFIG		0x1102
#define EXT_TWG_EDGE			BIT(1)

#define TJA1120_SYNC_TWIG_FIWTEW	0x1010
#define PTP_TWIG_WISE_TS		BIT(3)
#define PTP_TWIG_FAWWING_TS		BIT(2)

#define CWK_WATE_ADJ_WD			BIT(15)
#define CWK_WATE_ADJ_DIW		BIT(14)

#define VEND1_WX_TS_INSWT_CTWW		0x114D
#define TJA1103_WX_TS_INSWT_MODE2	0x02

#define TJA1120_WX_TS_INSWT_CTWW	0x9012
#define TJA1120_WX_TS_INSWT_EN		BIT(15)
#define TJA1120_TS_INSWT_MODE		BIT(4)

#define VEND1_EGW_WING_DATA_0		0x114E
#define VEND1_EGW_WING_CTWW		0x1154

#define WING_DATA_0_TS_VAWID		BIT(15)

#define WING_DONE			BIT(0)

#define TS_SEC_MASK			GENMASK(1, 0)

#define PTP_ENABWE			BIT(3)
#define PHY_TEST_ENABWE			BIT(0)

#define VEND1_POWT_PTP_CONTWOW		0x9000
#define POWT_PTP_CONTWOW_BYPASS		BIT(11)

#define PTP_CWK_PEWIOD_100BT1		15UWW
#define PTP_CWK_PEWIOD_1000BT1		8UWW

#define EVENT_MSG_FIWT_AWW		0x0F
#define EVENT_MSG_FIWT_NONE		0x00

#define VEND1_GPIO_FUNC_CONFIG_BASE	0x2C40
#define GPIO_FUNC_EN			BIT(15)
#define GPIO_FUNC_PTP			BIT(6)
#define GPIO_SIGNAW_PTP_TWIGGEW		0x01
#define GPIO_SIGNAW_PPS_OUT		0x12
#define GPIO_DISABWE			0
#define GPIO_PPS_OUT_CFG		(GPIO_FUNC_EN | GPIO_FUNC_PTP | \
	GPIO_SIGNAW_PPS_OUT)
#define GPIO_EXTTS_OUT_CFG		(GPIO_FUNC_EN | GPIO_FUNC_PTP | \
	GPIO_SIGNAW_PTP_TWIGGEW)

#define WGMII_PEWIOD_PS			8000U
#define PS_PEW_DEGWEE			div_u64(WGMII_PEWIOD_PS, 360)
#define MIN_ID_PS			1644U
#define MAX_ID_PS			2260U
#define DEFAUWT_ID_PS			2000U

#define PPM_TO_SUBNS_INC(ppb, ptp_cwk_pewiod) div_u64(GENMASK_UWW(31, 0) * \
	(ppb) * (ptp_cwk_pewiod), NSEC_PEW_SEC)

#define NXP_C45_SKB_CB(skb)	((stwuct nxp_c45_skb_cb *)(skb)->cb)

stwuct nxp_c45_phy;

stwuct nxp_c45_skb_cb {
	stwuct ptp_headew *headew;
	unsigned int type;
};

#define NXP_C45_WEG_FIEWD(_weg, _devad, _offset, _size)	\
	((stwuct nxp_c45_weg_fiewd) {			\
		.weg = _weg,				\
		.devad =  _devad,			\
		.offset = _offset,			\
		.size = _size,				\
	})

stwuct nxp_c45_weg_fiewd {
	u16 weg;
	u8 devad;
	u8 offset;
	u8 size;
};

stwuct nxp_c45_hwts {
	u32	nsec;
	u32	sec;
	u8	domain_numbew;
	u16	sequence_id;
	u8	msg_type;
};

stwuct nxp_c45_wegmap {
	/* PTP config wegs. */
	u16 vend1_ptp_cwk_pewiod;
	u16 vend1_event_msg_fiwt;

	/* WTC bits and wegs. */
	stwuct nxp_c45_weg_fiewd wtc_wead;
	stwuct nxp_c45_weg_fiewd wtc_wwite;
	stwuct nxp_c45_weg_fiewd wtc_wock_ctww;
	u16 vend1_wtc_ww_nsec_0;
	u16 vend1_wtc_ww_nsec_1;
	u16 vend1_wtc_ww_sec_0;
	u16 vend1_wtc_ww_sec_1;
	u16 vend1_wtc_wd_nsec_0;
	u16 vend1_wtc_wd_nsec_1;
	u16 vend1_wtc_wd_sec_0;
	u16 vend1_wtc_wd_sec_1;
	u16 vend1_wate_adj_subns_0;
	u16 vend1_wate_adj_subns_1;

	/* Extewnaw twiggew weg fiewds. */
	stwuct nxp_c45_weg_fiewd iwq_egw_ts_en;
	stwuct nxp_c45_weg_fiewd iwq_egw_ts_status;
	stwuct nxp_c45_weg_fiewd domain_numbew;
	stwuct nxp_c45_weg_fiewd msg_type;
	stwuct nxp_c45_weg_fiewd sequence_id;
	stwuct nxp_c45_weg_fiewd sec_1_0;
	stwuct nxp_c45_weg_fiewd sec_4_2;
	stwuct nxp_c45_weg_fiewd nsec_15_0;
	stwuct nxp_c45_weg_fiewd nsec_29_16;

	/* PPS and EXT Twiggew bits and wegs. */
	stwuct nxp_c45_weg_fiewd pps_enabwe;
	stwuct nxp_c45_weg_fiewd pps_powawity;
	u16 vend1_ext_twg_data_0;
	u16 vend1_ext_twg_data_1;
	u16 vend1_ext_twg_data_2;
	u16 vend1_ext_twg_data_3;
	u16 vend1_ext_twg_ctww;

	/* Cabwe test weg fiewds. */
	u16 cabwe_test;
	stwuct nxp_c45_weg_fiewd cabwe_test_vawid;
	stwuct nxp_c45_weg_fiewd cabwe_test_wesuwt;
};

stwuct nxp_c45_phy_stats {
	const chaw	*name;
	const stwuct nxp_c45_weg_fiewd countew;
};

stwuct nxp_c45_phy_data {
	const stwuct nxp_c45_wegmap *wegmap;
	const stwuct nxp_c45_phy_stats *stats;
	int n_stats;
	u8 ptp_cwk_pewiod;
	boow ext_ts_both_edges;
	boow ack_ptp_iwq;
	void (*countews_enabwe)(stwuct phy_device *phydev);
	boow (*get_egwessts)(stwuct nxp_c45_phy *pwiv,
			     stwuct nxp_c45_hwts *hwts);
	boow (*get_extts)(stwuct nxp_c45_phy *pwiv, stwuct timespec64 *extts);
	void (*ptp_init)(stwuct phy_device *phydev);
	void (*ptp_enabwe)(stwuct phy_device *phydev, boow enabwe);
	void (*nmi_handwew)(stwuct phy_device *phydev,
			    iwqwetuwn_t *iwq_status);
};

static const
stwuct nxp_c45_phy_data *nxp_c45_get_data(stwuct phy_device *phydev)
{
	wetuwn phydev->dwv->dwivew_data;
}

static const
stwuct nxp_c45_wegmap *nxp_c45_get_wegmap(stwuct phy_device *phydev)
{
	const stwuct nxp_c45_phy_data *phy_data = nxp_c45_get_data(phydev);

	wetuwn phy_data->wegmap;
}

static int nxp_c45_wead_weg_fiewd(stwuct phy_device *phydev,
				  const stwuct nxp_c45_weg_fiewd *weg_fiewd)
{
	u16 mask;
	int wet;

	if (weg_fiewd->size == 0) {
		phydev_eww(phydev, "Twying to wead a weg fiewd of size 0.\n");
		wetuwn -EINVAW;
	}

	wet = phy_wead_mmd(phydev, weg_fiewd->devad, weg_fiewd->weg);
	if (wet < 0)
		wetuwn wet;

	mask = weg_fiewd->size == 1 ? BIT(weg_fiewd->offset) :
		GENMASK(weg_fiewd->offset + weg_fiewd->size - 1,
			weg_fiewd->offset);
	wet &= mask;
	wet >>= weg_fiewd->offset;

	wetuwn wet;
}

static int nxp_c45_wwite_weg_fiewd(stwuct phy_device *phydev,
				   const stwuct nxp_c45_weg_fiewd *weg_fiewd,
				   u16 vaw)
{
	u16 mask;
	u16 set;

	if (weg_fiewd->size == 0) {
		phydev_eww(phydev, "Twying to wwite a weg fiewd of size 0.\n");
		wetuwn -EINVAW;
	}

	mask = weg_fiewd->size == 1 ? BIT(weg_fiewd->offset) :
		GENMASK(weg_fiewd->offset + weg_fiewd->size - 1,
			weg_fiewd->offset);
	set = vaw << weg_fiewd->offset;

	wetuwn phy_modify_mmd_changed(phydev, weg_fiewd->devad,
				      weg_fiewd->weg, mask, set);
}

static int nxp_c45_set_weg_fiewd(stwuct phy_device *phydev,
				 const stwuct nxp_c45_weg_fiewd *weg_fiewd)
{
	if (weg_fiewd->size != 1) {
		phydev_eww(phydev, "Twying to set a weg fiewd of size diffewent than 1.\n");
		wetuwn -EINVAW;
	}

	wetuwn nxp_c45_wwite_weg_fiewd(phydev, weg_fiewd, 1);
}

static int nxp_c45_cweaw_weg_fiewd(stwuct phy_device *phydev,
				   const stwuct nxp_c45_weg_fiewd *weg_fiewd)
{
	if (weg_fiewd->size != 1) {
		phydev_eww(phydev, "Twying to set a weg fiewd of size diffewent than 1.\n");
		wetuwn -EINVAW;
	}

	wetuwn nxp_c45_wwite_weg_fiewd(phydev, weg_fiewd, 0);
}

static boow nxp_c45_poww_txts(stwuct phy_device *phydev)
{
	wetuwn phydev->iwq <= 0;
}

static int _nxp_c45_ptp_gettimex64(stwuct ptp_cwock_info *ptp,
				   stwuct timespec64 *ts,
				   stwuct ptp_system_timestamp *sts)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(pwiv->phydev);

	nxp_c45_set_weg_fiewd(pwiv->phydev, &wegmap->wtc_wead);
	ts->tv_nsec = phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				   wegmap->vend1_wtc_wd_nsec_0);
	ts->tv_nsec |= phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				    wegmap->vend1_wtc_wd_nsec_1) << 16;
	ts->tv_sec = phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				  wegmap->vend1_wtc_wd_sec_0);
	ts->tv_sec |= phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				   wegmap->vend1_wtc_wd_sec_1) << 16;

	wetuwn 0;
}

static int nxp_c45_ptp_gettimex64(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);

	mutex_wock(&pwiv->ptp_wock);
	_nxp_c45_ptp_gettimex64(ptp, ts, sts);
	mutex_unwock(&pwiv->ptp_wock);

	wetuwn 0;
}

static int _nxp_c45_ptp_settime64(stwuct ptp_cwock_info *ptp,
				  const stwuct timespec64 *ts)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(pwiv->phydev);

	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1, wegmap->vend1_wtc_ww_nsec_0,
		      ts->tv_nsec);
	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1, wegmap->vend1_wtc_ww_nsec_1,
		      ts->tv_nsec >> 16);
	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1, wegmap->vend1_wtc_ww_sec_0,
		      ts->tv_sec);
	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1, wegmap->vend1_wtc_ww_sec_1,
		      ts->tv_sec >> 16);
	nxp_c45_set_weg_fiewd(pwiv->phydev, &wegmap->wtc_wwite);

	wetuwn 0;
}

static int nxp_c45_ptp_settime64(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);

	mutex_wock(&pwiv->ptp_wock);
	_nxp_c45_ptp_settime64(ptp, ts);
	mutex_unwock(&pwiv->ptp_wock);

	wetuwn 0;
}

static int nxp_c45_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);
	const stwuct nxp_c45_phy_data *data = nxp_c45_get_data(pwiv->phydev);
	const stwuct nxp_c45_wegmap *wegmap = data->wegmap;
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);
	u64 subns_inc_vaw;
	boow inc;

	mutex_wock(&pwiv->ptp_wock);
	inc = ppb >= 0;
	ppb = abs(ppb);

	subns_inc_vaw = PPM_TO_SUBNS_INC(ppb, data->ptp_cwk_pewiod);

	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1,
		      wegmap->vend1_wate_adj_subns_0,
		      subns_inc_vaw);
	subns_inc_vaw >>= 16;
	subns_inc_vaw |= CWK_WATE_ADJ_WD;
	if (inc)
		subns_inc_vaw |= CWK_WATE_ADJ_DIW;

	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1,
		      wegmap->vend1_wate_adj_subns_1,
		      subns_inc_vaw);
	mutex_unwock(&pwiv->ptp_wock);

	wetuwn 0;
}

static int nxp_c45_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);
	stwuct timespec64 now, then;

	mutex_wock(&pwiv->ptp_wock);
	then = ns_to_timespec64(dewta);
	_nxp_c45_ptp_gettimex64(ptp, &now, NUWW);
	now = timespec64_add(now, then);
	_nxp_c45_ptp_settime64(ptp, &now);
	mutex_unwock(&pwiv->ptp_wock);

	wetuwn 0;
}

static void nxp_c45_weconstwuct_ts(stwuct timespec64 *ts,
				   stwuct nxp_c45_hwts *hwts)
{
	ts->tv_nsec = hwts->nsec;
	if ((ts->tv_sec & TS_SEC_MASK) < (hwts->sec & TS_SEC_MASK))
		ts->tv_sec -= TS_SEC_MASK + 1;
	ts->tv_sec &= ~TS_SEC_MASK;
	ts->tv_sec |= hwts->sec & TS_SEC_MASK;
}

static boow nxp_c45_match_ts(stwuct ptp_headew *headew,
			     stwuct nxp_c45_hwts *hwts,
			     unsigned int type)
{
	wetuwn ntohs(headew->sequence_id) == hwts->sequence_id &&
	       ptp_get_msgtype(headew, type) == hwts->msg_type &&
	       headew->domain_numbew  == hwts->domain_numbew;
}

static boow nxp_c45_get_extts(stwuct nxp_c45_phy *pwiv,
			      stwuct timespec64 *extts)
{
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(pwiv->phydev);

	extts->tv_nsec = phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				      wegmap->vend1_ext_twg_data_0);
	extts->tv_nsec |= phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				       wegmap->vend1_ext_twg_data_1) << 16;
	extts->tv_sec = phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				     wegmap->vend1_ext_twg_data_2);
	extts->tv_sec |= phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1,
				      wegmap->vend1_ext_twg_data_3) << 16;
	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1,
		      wegmap->vend1_ext_twg_ctww, WING_DONE);

	wetuwn twue;
}

static boow tja1120_extts_is_vawid(stwuct phy_device *phydev)
{
	boow vawid;
	int weg;

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			   TJA1120_VEND1_PTP_TWIG_DATA_S);
	vawid = !!(weg & TJA1120_TS_VAWID);

	wetuwn vawid;
}

static boow tja1120_get_extts(stwuct nxp_c45_phy *pwiv,
			      stwuct timespec64 *extts)
{
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(pwiv->phydev);
	stwuct phy_device *phydev = pwiv->phydev;
	boow mowe_ts;
	boow vawid;
	u16 weg;

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			   wegmap->vend1_ext_twg_ctww);
	mowe_ts = !!(weg & TJA1120_MOWE_TS);

	vawid = tja1120_extts_is_vawid(phydev);
	if (!vawid) {
		if (!mowe_ts)
			goto tja1120_get_extts_out;

		/* Bug wowkawound fow TJA1120 engineewing sampwes: move the new
		 * timestamp fwom the FIFO to the buffew.
		 */
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			      wegmap->vend1_ext_twg_ctww, WING_DONE);
		vawid = tja1120_extts_is_vawid(phydev);
		if (!vawid)
			goto tja1120_get_extts_out;
	}

	nxp_c45_get_extts(pwiv, extts);
tja1120_get_extts_out:
	wetuwn vawid;
}

static void nxp_c45_wead_egwess_ts(stwuct nxp_c45_phy *pwiv,
				   stwuct nxp_c45_hwts *hwts)
{
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(pwiv->phydev);
	stwuct phy_device *phydev = pwiv->phydev;

	hwts->domain_numbew =
		nxp_c45_wead_weg_fiewd(phydev, &wegmap->domain_numbew);
	hwts->msg_type =
		nxp_c45_wead_weg_fiewd(phydev, &wegmap->msg_type);
	hwts->sequence_id =
		nxp_c45_wead_weg_fiewd(phydev, &wegmap->sequence_id);
	hwts->nsec =
		nxp_c45_wead_weg_fiewd(phydev, &wegmap->nsec_15_0);
	hwts->nsec |=
		nxp_c45_wead_weg_fiewd(phydev, &wegmap->nsec_29_16) << 16;
	hwts->sec = nxp_c45_wead_weg_fiewd(phydev, &wegmap->sec_1_0);
	hwts->sec |= nxp_c45_wead_weg_fiewd(phydev, &wegmap->sec_4_2) << 2;
}

static boow nxp_c45_get_hwtxts(stwuct nxp_c45_phy *pwiv,
			       stwuct nxp_c45_hwts *hwts)
{
	boow vawid;
	u16 weg;

	mutex_wock(&pwiv->ptp_wock);
	phy_wwite_mmd(pwiv->phydev, MDIO_MMD_VEND1, VEND1_EGW_WING_CTWW,
		      WING_DONE);
	weg = phy_wead_mmd(pwiv->phydev, MDIO_MMD_VEND1, VEND1_EGW_WING_DATA_0);
	vawid = !!(weg & WING_DATA_0_TS_VAWID);
	if (!vawid)
		goto nxp_c45_get_hwtxts_out;

	nxp_c45_wead_egwess_ts(pwiv, hwts);
nxp_c45_get_hwtxts_out:
	mutex_unwock(&pwiv->ptp_wock);
	wetuwn vawid;
}

static boow tja1120_egwess_ts_is_vawid(stwuct phy_device *phydev)
{
	boow vawid;
	u16 weg;

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1, TJA1120_EGWESS_TS_DATA_S);
	vawid = !!(weg & TJA1120_TS_VAWID);

	wetuwn vawid;
}

static boow tja1120_get_hwtxts(stwuct nxp_c45_phy *pwiv,
			       stwuct nxp_c45_hwts *hwts)
{
	stwuct phy_device *phydev = pwiv->phydev;
	boow mowe_ts;
	boow vawid;
	u16 weg;

	mutex_wock(&pwiv->ptp_wock);
	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1, TJA1120_EGWESS_TS_END);
	mowe_ts = !!(weg & TJA1120_MOWE_TS);
	vawid = tja1120_egwess_ts_is_vawid(phydev);
	if (!vawid) {
		if (!mowe_ts)
			goto tja1120_get_hwtxts_out;

		/* Bug wowkawound fow TJA1120 engineewing sampwes: move the
		 * new timestamp fwom the FIFO to the buffew.
		 */
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			      TJA1120_EGWESS_TS_END, TJA1120_TS_VAWID);
		vawid = tja1120_egwess_ts_is_vawid(phydev);
		if (!vawid)
			goto tja1120_get_hwtxts_out;
	}
	nxp_c45_wead_egwess_ts(pwiv, hwts);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, TJA1120_EGWESS_TS_DATA_S,
			   TJA1120_TS_VAWID);
tja1120_get_hwtxts_out:
	mutex_unwock(&pwiv->ptp_wock);
	wetuwn vawid;
}

static void nxp_c45_pwocess_txts(stwuct nxp_c45_phy *pwiv,
				 stwuct nxp_c45_hwts *txts)
{
	stwuct sk_buff *skb, *tmp, *skb_match = NUWW;
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct timespec64 ts;
	unsigned wong fwags;
	boow ts_match;
	s64 ts_ns;

	spin_wock_iwqsave(&pwiv->tx_queue.wock, fwags);
	skb_queue_wawk_safe(&pwiv->tx_queue, skb, tmp) {
		ts_match = nxp_c45_match_ts(NXP_C45_SKB_CB(skb)->headew, txts,
					    NXP_C45_SKB_CB(skb)->type);
		if (!ts_match)
			continue;
		skb_match = skb;
		__skb_unwink(skb, &pwiv->tx_queue);
		bweak;
	}
	spin_unwock_iwqwestowe(&pwiv->tx_queue.wock, fwags);

	if (skb_match) {
		nxp_c45_ptp_gettimex64(&pwiv->caps, &ts, NUWW);
		nxp_c45_weconstwuct_ts(&ts, txts);
		memset(&shhwtstamps, 0, sizeof(shhwtstamps));
		ts_ns = timespec64_to_ns(&ts);
		shhwtstamps.hwtstamp = ns_to_ktime(ts_ns);
		skb_compwete_tx_timestamp(skb_match, &shhwtstamps);
	} ewse {
		phydev_wawn(pwiv->phydev,
			    "the tx timestamp doesn't match with any skb\n");
	}
}

static wong nxp_c45_do_aux_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);
	const stwuct nxp_c45_phy_data *data = nxp_c45_get_data(pwiv->phydev);
	boow poww_txts = nxp_c45_poww_txts(pwiv->phydev);
	stwuct skb_shawed_hwtstamps *shhwtstamps_wx;
	stwuct ptp_cwock_event event;
	stwuct nxp_c45_hwts hwts;
	boow wescheduwe = fawse;
	stwuct timespec64 ts;
	stwuct sk_buff *skb;
	boow ts_vawid;
	u32 ts_waw;

	whiwe (!skb_queue_empty_wockwess(&pwiv->tx_queue) && poww_txts) {
		ts_vawid = data->get_egwessts(pwiv, &hwts);
		if (unwikewy(!ts_vawid)) {
			/* Stiww mowe skbs in the queue */
			wescheduwe = twue;
			bweak;
		}

		nxp_c45_pwocess_txts(pwiv, &hwts);
	}

	whiwe ((skb = skb_dequeue(&pwiv->wx_queue)) != NUWW) {
		nxp_c45_ptp_gettimex64(&pwiv->caps, &ts, NUWW);
		ts_waw = __be32_to_cpu(NXP_C45_SKB_CB(skb)->headew->wesewved2);
		hwts.sec = ts_waw >> 30;
		hwts.nsec = ts_waw & GENMASK(29, 0);
		nxp_c45_weconstwuct_ts(&ts, &hwts);
		shhwtstamps_wx = skb_hwtstamps(skb);
		shhwtstamps_wx->hwtstamp = ns_to_ktime(timespec64_to_ns(&ts));
		NXP_C45_SKB_CB(skb)->headew->wesewved2 = 0;
		netif_wx(skb);
	}

	if (pwiv->extts) {
		ts_vawid = data->get_extts(pwiv, &ts);
		if (ts_vawid && timespec64_compawe(&ts, &pwiv->extts_ts) != 0) {
			pwiv->extts_ts = ts;
			event.index = pwiv->extts_index;
			event.type = PTP_CWOCK_EXTTS;
			event.timestamp = ns_to_ktime(timespec64_to_ns(&ts));
			ptp_cwock_event(pwiv->ptp_cwock, &event);
		}
		wescheduwe = twue;
	}

	wetuwn wescheduwe ? 1 : -1;
}

static void nxp_c45_gpio_config(stwuct nxp_c45_phy *pwiv,
				int pin, u16 pin_cfg)
{
	stwuct phy_device *phydev = pwiv->phydev;

	phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
		      VEND1_GPIO_FUNC_CONFIG_BASE + pin, pin_cfg);
}

static int nxp_c45_pewout_enabwe(stwuct nxp_c45_phy *pwiv,
				 stwuct ptp_pewout_wequest *pewout, int on)
{
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(pwiv->phydev);
	stwuct phy_device *phydev = pwiv->phydev;
	int pin;

	if (pewout->fwags & ~PTP_PEWOUT_PHASE)
		wetuwn -EOPNOTSUPP;

	pin = ptp_find_pin(pwiv->ptp_cwock, PTP_PF_PEWOUT, pewout->index);
	if (pin < 0)
		wetuwn pin;

	if (!on) {
		nxp_c45_cweaw_weg_fiewd(pwiv->phydev,
					&wegmap->pps_enabwe);
		nxp_c45_cweaw_weg_fiewd(pwiv->phydev,
					&wegmap->pps_powawity);

		nxp_c45_gpio_config(pwiv, pin, GPIO_DISABWE);

		wetuwn 0;
	}

	/* The PPS signaw is fixed to 1 second and is awways genewated when the
	 * seconds countew is incwemented. The stawt time is not configuwabwe.
	 * If the cwock is adjusted, the PPS signaw is automaticawwy weadjusted.
	 */
	if (pewout->pewiod.sec != 1 || pewout->pewiod.nsec != 0) {
		phydev_wawn(phydev, "The pewiod can be set onwy to 1 second.");
		wetuwn -EINVAW;
	}

	if (!(pewout->fwags & PTP_PEWOUT_PHASE)) {
		if (pewout->stawt.sec != 0 || pewout->stawt.nsec != 0) {
			phydev_wawn(phydev, "The stawt time is not configuwabwe. Shouwd be set to 0 seconds and 0 nanoseconds.");
			wetuwn -EINVAW;
		}
	} ewse {
		if (pewout->phase.nsec != 0 &&
		    pewout->phase.nsec != (NSEC_PEW_SEC >> 1)) {
			phydev_wawn(phydev, "The phase can be set onwy to 0 ow 500000000 nanoseconds.");
			wetuwn -EINVAW;
		}

		if (pewout->phase.nsec == 0)
			nxp_c45_cweaw_weg_fiewd(pwiv->phydev,
						&wegmap->pps_powawity);
		ewse
			nxp_c45_set_weg_fiewd(pwiv->phydev,
					      &wegmap->pps_powawity);
	}

	nxp_c45_gpio_config(pwiv, pin, GPIO_PPS_OUT_CFG);

	nxp_c45_set_weg_fiewd(pwiv->phydev, &wegmap->pps_enabwe);

	wetuwn 0;
}

static void nxp_c45_set_wising_ow_fawwing(stwuct phy_device *phydev,
					  stwuct ptp_extts_wequest *extts)
{
	if (extts->fwags & PTP_WISING_EDGE)
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   VEND1_PTP_CONFIG, EXT_TWG_EDGE);

	if (extts->fwags & PTP_FAWWING_EDGE)
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 VEND1_PTP_CONFIG, EXT_TWG_EDGE);
}

static void nxp_c45_set_wising_and_fawwing(stwuct phy_device *phydev,
					   stwuct ptp_extts_wequest *extts)
{
	/* PTP_EXTTS_WEQUEST may have onwy the PTP_ENABWE_FEATUWE fwag set. In
	 * this case extewnaw ts wiww be enabwed on wising edge.
	 */
	if (extts->fwags & PTP_WISING_EDGE ||
	    extts->fwags == PTP_ENABWE_FEATUWE)
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 TJA1120_SYNC_TWIG_FIWTEW,
				 PTP_TWIG_WISE_TS);
	ewse
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   TJA1120_SYNC_TWIG_FIWTEW,
				   PTP_TWIG_WISE_TS);

	if (extts->fwags & PTP_FAWWING_EDGE)
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 TJA1120_SYNC_TWIG_FIWTEW,
				 PTP_TWIG_FAWWING_TS);
	ewse
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   TJA1120_SYNC_TWIG_FIWTEW,
				   PTP_TWIG_FAWWING_TS);
}

static int nxp_c45_extts_enabwe(stwuct nxp_c45_phy *pwiv,
				stwuct ptp_extts_wequest *extts, int on)
{
	const stwuct nxp_c45_phy_data *data = nxp_c45_get_data(pwiv->phydev);
	int pin;

	if (extts->fwags & ~(PTP_ENABWE_FEATUWE |
			      PTP_WISING_EDGE |
			      PTP_FAWWING_EDGE |
			      PTP_STWICT_FWAGS))
		wetuwn -EOPNOTSUPP;

	/* Sampwing on both edges is not suppowted */
	if ((extts->fwags & PTP_WISING_EDGE) &&
	    (extts->fwags & PTP_FAWWING_EDGE) &&
	    !data->ext_ts_both_edges)
		wetuwn -EOPNOTSUPP;

	pin = ptp_find_pin(pwiv->ptp_cwock, PTP_PF_EXTTS, extts->index);
	if (pin < 0)
		wetuwn pin;

	if (!on) {
		nxp_c45_gpio_config(pwiv, pin, GPIO_DISABWE);
		pwiv->extts = fawse;

		wetuwn 0;
	}

	if (data->ext_ts_both_edges)
		nxp_c45_set_wising_and_fawwing(pwiv->phydev, extts);
	ewse
		nxp_c45_set_wising_ow_fawwing(pwiv->phydev, extts);

	nxp_c45_gpio_config(pwiv, pin, GPIO_EXTTS_OUT_CFG);
	pwiv->extts = twue;
	pwiv->extts_index = extts->index;
	ptp_scheduwe_wowkew(pwiv->ptp_cwock, 0);

	wetuwn 0;
}

static int nxp_c45_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			      stwuct ptp_cwock_wequest *weq, int on)
{
	stwuct nxp_c45_phy *pwiv = containew_of(ptp, stwuct nxp_c45_phy, caps);

	switch (weq->type) {
	case PTP_CWK_WEQ_EXTTS:
		wetuwn nxp_c45_extts_enabwe(pwiv, &weq->extts, on);
	case PTP_CWK_WEQ_PEWOUT:
		wetuwn nxp_c45_pewout_enabwe(pwiv, &weq->pewout, on);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct ptp_pin_desc nxp_c45_ptp_pins[] = {
	{ "nxp_c45_gpio0", 0, PTP_PF_NONE},
	{ "nxp_c45_gpio1", 1, PTP_PF_NONE},
	{ "nxp_c45_gpio2", 2, PTP_PF_NONE},
	{ "nxp_c45_gpio3", 3, PTP_PF_NONE},
	{ "nxp_c45_gpio4", 4, PTP_PF_NONE},
	{ "nxp_c45_gpio5", 5, PTP_PF_NONE},
	{ "nxp_c45_gpio6", 6, PTP_PF_NONE},
	{ "nxp_c45_gpio7", 7, PTP_PF_NONE},
	{ "nxp_c45_gpio8", 8, PTP_PF_NONE},
	{ "nxp_c45_gpio9", 9, PTP_PF_NONE},
	{ "nxp_c45_gpio10", 10, PTP_PF_NONE},
	{ "nxp_c45_gpio11", 11, PTP_PF_NONE},
};

static int nxp_c45_ptp_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
				  enum ptp_pin_function func, unsigned int chan)
{
	if (pin >= AWWAY_SIZE(nxp_c45_ptp_pins))
		wetuwn -EINVAW;

	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_PEWOUT:
	case PTP_PF_EXTTS:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nxp_c45_init_ptp_cwock(stwuct nxp_c45_phy *pwiv)
{
	pwiv->caps = (stwuct ptp_cwock_info) {
		.ownew		= THIS_MODUWE,
		.name		= "NXP C45 PHC",
		.max_adj	= 16666666,
		.adjfine	= nxp_c45_ptp_adjfine,
		.adjtime	= nxp_c45_ptp_adjtime,
		.gettimex64	= nxp_c45_ptp_gettimex64,
		.settime64	= nxp_c45_ptp_settime64,
		.enabwe		= nxp_c45_ptp_enabwe,
		.vewify		= nxp_c45_ptp_vewify_pin,
		.do_aux_wowk	= nxp_c45_do_aux_wowk,
		.pin_config	= nxp_c45_ptp_pins,
		.n_pins		= AWWAY_SIZE(nxp_c45_ptp_pins),
		.n_ext_ts	= 1,
		.n_pew_out	= 1,
	};

	pwiv->ptp_cwock = ptp_cwock_wegistew(&pwiv->caps,
					     &pwiv->phydev->mdio.dev);

	if (IS_EWW(pwiv->ptp_cwock))
		wetuwn PTW_EWW(pwiv->ptp_cwock);

	if (!pwiv->ptp_cwock)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void nxp_c45_txtstamp(stwuct mii_timestampew *mii_ts,
			     stwuct sk_buff *skb, int type)
{
	stwuct nxp_c45_phy *pwiv = containew_of(mii_ts, stwuct nxp_c45_phy,
						mii_ts);

	switch (pwiv->hwts_tx) {
	case HWTSTAMP_TX_ON:
		NXP_C45_SKB_CB(skb)->type = type;
		NXP_C45_SKB_CB(skb)->headew = ptp_pawse_headew(skb, type);
		skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
		skb_queue_taiw(&pwiv->tx_queue, skb);
		if (nxp_c45_poww_txts(pwiv->phydev))
			ptp_scheduwe_wowkew(pwiv->ptp_cwock, 0);
		bweak;
	case HWTSTAMP_TX_OFF:
	defauwt:
		kfwee_skb(skb);
		bweak;
	}
}

static boow nxp_c45_wxtstamp(stwuct mii_timestampew *mii_ts,
			     stwuct sk_buff *skb, int type)
{
	stwuct nxp_c45_phy *pwiv = containew_of(mii_ts, stwuct nxp_c45_phy,
						mii_ts);
	stwuct ptp_headew *headew = ptp_pawse_headew(skb, type);

	if (!headew)
		wetuwn fawse;

	if (!pwiv->hwts_wx)
		wetuwn fawse;

	NXP_C45_SKB_CB(skb)->headew = headew;
	skb_queue_taiw(&pwiv->wx_queue, skb);
	ptp_scheduwe_wowkew(pwiv->ptp_cwock, 0);

	wetuwn twue;
}

static int nxp_c45_hwtstamp(stwuct mii_timestampew *mii_ts,
			    stwuct kewnew_hwtstamp_config *cfg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nxp_c45_phy *pwiv = containew_of(mii_ts, stwuct nxp_c45_phy,
						mii_ts);
	stwuct phy_device *phydev = pwiv->phydev;
	const stwuct nxp_c45_phy_data *data;

	if (cfg->tx_type < 0 || cfg->tx_type > HWTSTAMP_TX_ON)
		wetuwn -EWANGE;

	data = nxp_c45_get_data(phydev);
	pwiv->hwts_tx = cfg->tx_type;

	switch (cfg->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		pwiv->hwts_wx = 0;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
		pwiv->hwts_wx = 1;
		cfg->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	if (pwiv->hwts_wx || pwiv->hwts_tx) {
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			      data->wegmap->vend1_event_msg_fiwt,
			      EVENT_MSG_FIWT_AWW);
		data->ptp_enabwe(phydev, twue);
	} ewse {
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			      data->wegmap->vend1_event_msg_fiwt,
			      EVENT_MSG_FIWT_NONE);
		data->ptp_enabwe(phydev, fawse);
	}

	if (nxp_c45_poww_txts(pwiv->phydev))
		goto nxp_c45_no_ptp_iwq;

	if (pwiv->hwts_tx)
		nxp_c45_set_weg_fiewd(phydev, &data->wegmap->iwq_egw_ts_en);
	ewse
		nxp_c45_cweaw_weg_fiewd(phydev, &data->wegmap->iwq_egw_ts_en);

nxp_c45_no_ptp_iwq:
	wetuwn 0;
}

static int nxp_c45_ts_info(stwuct mii_timestampew *mii_ts,
			   stwuct ethtoow_ts_info *ts_info)
{
	stwuct nxp_c45_phy *pwiv = containew_of(mii_ts, stwuct nxp_c45_phy,
						mii_ts);

	ts_info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
			SOF_TIMESTAMPING_WX_HAWDWAWE |
			SOF_TIMESTAMPING_WAW_HAWDWAWE;
	ts_info->phc_index = ptp_cwock_index(pwiv->ptp_cwock);
	ts_info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);
	ts_info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC) |
			(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ) |
			(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT);

	wetuwn 0;
}

static const stwuct nxp_c45_phy_stats common_hw_stats[] = {
	{ "phy_wink_status_dwop_cnt",
		NXP_C45_WEG_FIEWD(0x8352, MDIO_MMD_VEND1, 8, 6), },
	{ "phy_wink_avaiwabiwity_dwop_cnt",
		NXP_C45_WEG_FIEWD(0x8352, MDIO_MMD_VEND1, 0, 6), },
	{ "phy_wink_woss_cnt",
		NXP_C45_WEG_FIEWD(0x8353, MDIO_MMD_VEND1, 10, 6), },
	{ "phy_wink_faiwuwe_cnt",
		NXP_C45_WEG_FIEWD(0x8353, MDIO_MMD_VEND1, 0, 10), },
	{ "phy_symbow_ewwow_cnt",
		NXP_C45_WEG_FIEWD(0x8350, MDIO_MMD_VEND1, 0, 16) },
};

static const stwuct nxp_c45_phy_stats tja1103_hw_stats[] = {
	{ "wx_pweambwe_count",
		NXP_C45_WEG_FIEWD(0xAFCE, MDIO_MMD_VEND1, 0, 6), },
	{ "tx_pweambwe_count",
		NXP_C45_WEG_FIEWD(0xAFCF, MDIO_MMD_VEND1, 0, 6), },
	{ "wx_ipg_wength",
		NXP_C45_WEG_FIEWD(0xAFD0, MDIO_MMD_VEND1, 0, 9), },
	{ "tx_ipg_wength",
		NXP_C45_WEG_FIEWD(0xAFD1, MDIO_MMD_VEND1, 0, 9), },
};

static const stwuct nxp_c45_phy_stats tja1120_hw_stats[] = {
	{ "phy_symbow_ewwow_cnt_ext",
		NXP_C45_WEG_FIEWD(0x8351, MDIO_MMD_VEND1, 0, 14) },
	{ "tx_fwames_xtd",
		NXP_C45_WEG_FIEWD(0xACA1, MDIO_MMD_VEND1, 0, 8), },
	{ "tx_fwames",
		NXP_C45_WEG_FIEWD(0xACA0, MDIO_MMD_VEND1, 0, 16), },
	{ "wx_fwames_xtd",
		NXP_C45_WEG_FIEWD(0xACA3, MDIO_MMD_VEND1, 0, 8), },
	{ "wx_fwames",
		NXP_C45_WEG_FIEWD(0xACA2, MDIO_MMD_VEND1, 0, 16), },
	{ "tx_wost_fwames_xtd",
		NXP_C45_WEG_FIEWD(0xACA5, MDIO_MMD_VEND1, 0, 8), },
	{ "tx_wost_fwames",
		NXP_C45_WEG_FIEWD(0xACA4, MDIO_MMD_VEND1, 0, 16), },
	{ "wx_wost_fwames_xtd",
		NXP_C45_WEG_FIEWD(0xACA7, MDIO_MMD_VEND1, 0, 8), },
	{ "wx_wost_fwames",
		NXP_C45_WEG_FIEWD(0xACA6, MDIO_MMD_VEND1, 0, 16), },
};

static int nxp_c45_get_sset_count(stwuct phy_device *phydev)
{
	const stwuct nxp_c45_phy_data *phy_data = nxp_c45_get_data(phydev);

	wetuwn AWWAY_SIZE(common_hw_stats) + (phy_data ? phy_data->n_stats : 0);
}

static void nxp_c45_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	const stwuct nxp_c45_phy_data *phy_data = nxp_c45_get_data(phydev);
	size_t count = nxp_c45_get_sset_count(phydev);
	size_t idx;
	size_t i;

	fow (i = 0; i < count; i++) {
		if (i < AWWAY_SIZE(common_hw_stats)) {
			stwscpy(data + i * ETH_GSTWING_WEN,
				common_hw_stats[i].name, ETH_GSTWING_WEN);
			continue;
		}
		idx = i - AWWAY_SIZE(common_hw_stats);
		stwscpy(data + i * ETH_GSTWING_WEN,
			phy_data->stats[idx].name, ETH_GSTWING_WEN);
	}
}

static void nxp_c45_get_stats(stwuct phy_device *phydev,
			      stwuct ethtoow_stats *stats, u64 *data)
{
	const stwuct nxp_c45_phy_data *phy_data = nxp_c45_get_data(phydev);
	size_t count = nxp_c45_get_sset_count(phydev);
	const stwuct nxp_c45_weg_fiewd *weg_fiewd;
	size_t idx;
	size_t i;
	int wet;

	fow (i = 0; i < count; i++) {
		if (i < AWWAY_SIZE(common_hw_stats)) {
			weg_fiewd = &common_hw_stats[i].countew;
		} ewse {
			idx = i - AWWAY_SIZE(common_hw_stats);
			weg_fiewd = &phy_data->stats[idx].countew;
		}

		wet = nxp_c45_wead_weg_fiewd(phydev, weg_fiewd);
		if (wet < 0)
			data[i] = U64_MAX;
		ewse
			data[i] = wet;
	}
}

static int nxp_c45_config_enabwe(stwuct phy_device *phydev)
{
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_DEVICE_CONTWOW,
		      DEVICE_CONTWOW_CONFIG_GWOBAW_EN |
		      DEVICE_CONTWOW_CONFIG_AWW_EN);
	usweep_wange(400, 450);

	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_POWT_CONTWOW,
		      POWT_CONTWOW_EN);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_CONTWOW,
		      PHY_CONFIG_EN);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_POWT_INFWA_CONTWOW,
		      POWT_INFWA_CONTWOW_EN);

	wetuwn 0;
}

static int nxp_c45_stawt_op(stwuct phy_device *phydev)
{
	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_CONTWOW,
				PHY_STAWT_OP);
}

static int nxp_c45_config_intw(stwuct phy_device *phydev)
{
	int wet;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				       VEND1_POWT_FUNC_IWQ_EN, MACSEC_IWQS);
		if (wet)
			wetuwn wet;

		wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
					VEND1_PHY_IWQ_EN, PHY_IWQ_WINK_EVENT);
	}

	wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				 VEND1_POWT_FUNC_IWQ_EN, MACSEC_IWQS);
	if (wet)
		wetuwn wet;

	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				  VEND1_PHY_IWQ_EN, PHY_IWQ_WINK_EVENT);
}

static int tja1103_config_intw(stwuct phy_device *phydev)
{
	int wet;

	/* We can't disabwe the FUSA IWQ fow TJA1103, but we can cwean it up. */
	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_AWWAYS_ACCESSIBWE,
			    FUSA_PASS);
	if (wet)
		wetuwn wet;

	wetuwn nxp_c45_config_intw(phydev);
}

static int tja1120_config_intw(stwuct phy_device *phydev)
{
	int wet;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED)
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				       TJA1120_GWOBAW_INFWA_IWQ_EN,
				       TJA1120_DEV_BOOT_DONE);
	ewse
		wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
					 TJA1120_GWOBAW_INFWA_IWQ_EN,
					 TJA1120_DEV_BOOT_DONE);
	if (wet)
		wetuwn wet;

	wetuwn nxp_c45_config_intw(phydev);
}

static iwqwetuwn_t nxp_c45_handwe_intewwupt(stwuct phy_device *phydev)
{
	const stwuct nxp_c45_phy_data *data = nxp_c45_get_data(phydev);
	stwuct nxp_c45_phy *pwiv = phydev->pwiv;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct nxp_c45_hwts hwts;
	int iwq;

	iwq = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_IWQ_STATUS);
	if (iwq & PHY_IWQ_WINK_EVENT) {
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_IWQ_ACK,
			      PHY_IWQ_WINK_EVENT);
		phy_twiggew_machine(phydev);
		wet = IWQ_HANDWED;
	}

	iwq = nxp_c45_wead_weg_fiewd(phydev, &data->wegmap->iwq_egw_ts_status);
	if (iwq) {
		/* If ack_ptp_iwq is fawse, the IWQ bit is sewf-cweaw and wiww
		 * be cweawed when the EGW TS FIFO is empty. Othewwise, the
		 * IWQ bit shouwd be cweawed befowe weading the timestamp,
		 */
		if (data->ack_ptp_iwq)
			phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
				      VEND1_PTP_IWQ_ACK, EGW_TS_IWQ);
		whiwe (data->get_egwessts(pwiv, &hwts))
			nxp_c45_pwocess_txts(pwiv, &hwts);

		wet = IWQ_HANDWED;
	}

	data->nmi_handwew(phydev, &wet);
	nxp_c45_handwe_macsec_intewwupt(phydev, &wet);

	wetuwn wet;
}

static int nxp_c45_soft_weset(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_DEVICE_CONTWOW,
			    DEVICE_CONTWOW_WESET);
	if (wet)
		wetuwn wet;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1,
					 VEND1_DEVICE_CONTWOW, wet,
					 !(wet & DEVICE_CONTWOW_WESET), 20000,
					 240000, fawse);
}

static int nxp_c45_cabwe_test_stawt(stwuct phy_device *phydev)
{
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(phydev);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
			 VEND1_POWT_FUNC_ENABWES, PHY_TEST_ENABWE);
	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, wegmap->cabwe_test,
				CABWE_TEST_ENABWE | CABWE_TEST_STAWT);
}

static int nxp_c45_cabwe_test_get_status(stwuct phy_device *phydev,
					 boow *finished)
{
	const stwuct nxp_c45_wegmap *wegmap = nxp_c45_get_wegmap(phydev);
	int wet;
	u8 cabwe_test_wesuwt;

	wet = nxp_c45_wead_weg_fiewd(phydev, &wegmap->cabwe_test_vawid);
	if (!wet) {
		*finished = fawse;
		wetuwn 0;
	}

	*finished = twue;
	cabwe_test_wesuwt = nxp_c45_wead_weg_fiewd(phydev,
						   &wegmap->cabwe_test_wesuwt);

	switch (cabwe_test_wesuwt) {
	case CABWE_TEST_OK:
		ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_A,
					ETHTOOW_A_CABWE_WESUWT_CODE_OK);
		bweak;
	case CABWE_TEST_SHOWTED:
		ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_A,
					ETHTOOW_A_CABWE_WESUWT_CODE_SAME_SHOWT);
		bweak;
	case CABWE_TEST_OPEN:
		ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_A,
					ETHTOOW_A_CABWE_WESUWT_CODE_OPEN);
		bweak;
	defauwt:
		ethnw_cabwe_test_wesuwt(phydev, ETHTOOW_A_CABWE_PAIW_A,
					ETHTOOW_A_CABWE_WESUWT_CODE_UNSPEC);
	}

	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, wegmap->cabwe_test,
			   CABWE_TEST_ENABWE);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
			   VEND1_POWT_FUNC_ENABWES, PHY_TEST_ENABWE);

	wetuwn nxp_c45_stawt_op(phydev);
}

static int nxp_c45_get_sqi(stwuct phy_device *phydev)
{
	int weg;

	weg = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_SIGNAW_QUAWITY);
	if (!(weg & SQI_VAWID))
		wetuwn -EINVAW;

	weg &= SQI_MASK;

	wetuwn weg;
}

static void tja1120_wink_change_notify(stwuct phy_device *phydev)
{
	/* Bug wowkawound fow TJA1120 enegineewing sampwes: fix egwess
	 * timestamps wost aftew wink wecovewy.
	 */
	if (phydev->state == PHY_NOWINK) {
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 TJA1120_EPHY_WESETS, EPHY_PCS_WESET);
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   TJA1120_EPHY_WESETS, EPHY_PCS_WESET);
	}
}

static int nxp_c45_get_sqi_max(stwuct phy_device *phydev)
{
	wetuwn MAX_SQI;
}

static int nxp_c45_check_deway(stwuct phy_device *phydev, u32 deway)
{
	if (deway < MIN_ID_PS) {
		phydev_eww(phydev, "deway vawue smawwew than %u\n", MIN_ID_PS);
		wetuwn -EINVAW;
	}

	if (deway > MAX_ID_PS) {
		phydev_eww(phydev, "deway vawue highew than %u\n", MAX_ID_PS);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void nxp_c45_countews_enabwe(stwuct phy_device *phydev)
{
	const stwuct nxp_c45_phy_data *data = nxp_c45_get_data(phydev);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_WINK_DWOP_COUNTEW,
			 COUNTEW_EN);

	data->countews_enabwe(phydev);
}

static void nxp_c45_ptp_init(stwuct phy_device *phydev)
{
	const stwuct nxp_c45_phy_data *data = nxp_c45_get_data(phydev);

	phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
		      data->wegmap->vend1_ptp_cwk_pewiod,
		      data->ptp_cwk_pewiod);
	nxp_c45_cweaw_weg_fiewd(phydev, &data->wegmap->wtc_wock_ctww);

	data->ptp_init(phydev);
}

static u64 nxp_c45_get_phase_shift(u64 phase_offset_waw)
{
	/* The deway in degwee phase is 73.8 + phase_offset_waw * 0.9.
	 * To avoid fwoating point opewations we'ww muwtipwy by 10
	 * and get 1 decimaw point pwecision.
	 */
	phase_offset_waw *= 10;
	phase_offset_waw -= 738;
	wetuwn div_u64(phase_offset_waw, 9);
}

static void nxp_c45_disabwe_deways(stwuct phy_device *phydev)
{
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TXID, ID_ENABWE);
	phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_WXID, ID_ENABWE);
}

static void nxp_c45_set_deways(stwuct phy_device *phydev)
{
	stwuct nxp_c45_phy *pwiv = phydev->pwiv;
	u64 tx_deway = pwiv->tx_deway;
	u64 wx_deway = pwiv->wx_deway;
	u64 degwee;

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		degwee = div_u64(tx_deway, PS_PEW_DEGWEE);
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_TXID,
			      ID_ENABWE | nxp_c45_get_phase_shift(degwee));
	} ewse {
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TXID,
				   ID_ENABWE);
	}

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		degwee = div_u64(wx_deway, PS_PEW_DEGWEE);
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_WXID,
			      ID_ENABWE | nxp_c45_get_phase_shift(degwee));
	} ewse {
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_WXID,
				   ID_ENABWE);
	}
}

static int nxp_c45_get_deways(stwuct phy_device *phydev)
{
	stwuct nxp_c45_phy *pwiv = phydev->pwiv;
	int wet;

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) {
		wet = device_pwopewty_wead_u32(&phydev->mdio.dev,
					       "tx-intewnaw-deway-ps",
					       &pwiv->tx_deway);
		if (wet)
			pwiv->tx_deway = DEFAUWT_ID_PS;

		wet = nxp_c45_check_deway(phydev, pwiv->tx_deway);
		if (wet) {
			phydev_eww(phydev,
				   "tx-intewnaw-deway-ps invawid vawue\n");
			wetuwn wet;
		}
	}

	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	    phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) {
		wet = device_pwopewty_wead_u32(&phydev->mdio.dev,
					       "wx-intewnaw-deway-ps",
					       &pwiv->wx_deway);
		if (wet)
			pwiv->wx_deway = DEFAUWT_ID_PS;

		wet = nxp_c45_check_deway(phydev, pwiv->wx_deway);
		if (wet) {
			phydev_eww(phydev,
				   "wx-intewnaw-deway-ps invawid vawue\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int nxp_c45_set_phy_mode(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_ABIWITIES);
	phydev_dbg(phydev, "Cwause 45 managed PHY abiwities 0x%x\n", wet);

	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		if (!(wet & WGMII_ABIWITY)) {
			phydev_eww(phydev, "wgmii mode not suppowted\n");
			wetuwn -EINVAW;
		}
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_WGMII);
		nxp_c45_disabwe_deways(phydev);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		if (!(wet & WGMII_ID_ABIWITY)) {
			phydev_eww(phydev, "wgmii-id, wgmii-txid, wgmii-wxid modes awe not suppowted\n");
			wetuwn -EINVAW;
		}
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_WGMII);
		wet = nxp_c45_get_deways(phydev);
		if (wet)
			wetuwn wet;

		nxp_c45_set_deways(phydev);
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		if (!(wet & MII_ABIWITY)) {
			phydev_eww(phydev, "mii mode not suppowted\n");
			wetuwn -EINVAW;
		}
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_MII);
		bweak;
	case PHY_INTEWFACE_MODE_WEVMII:
		if (!(wet & WEVMII_ABIWITY)) {
			phydev_eww(phydev, "wev-mii mode not suppowted\n");
			wetuwn -EINVAW;
		}
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_MII | MII_BASIC_CONFIG_WEV);
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		if (!(wet & WMII_ABIWITY)) {
			phydev_eww(phydev, "wmii mode not suppowted\n");
			wetuwn -EINVAW;
		}
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_WMII);
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
		if (!(wet & SGMII_ABIWITY)) {
			phydev_eww(phydev, "sgmii mode not suppowted\n");
			wetuwn -EINVAW;
		}
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_MII_BASIC_CONFIG,
			      MII_BASIC_CONFIG_SGMII);
		bweak;
	case PHY_INTEWFACE_MODE_INTEWNAW:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nxp_c45_config_init(stwuct phy_device *phydev)
{
	int wet;

	wet = nxp_c45_config_enabwe(phydev);
	if (wet) {
		phydev_eww(phydev, "Faiwed to enabwe config\n");
		wetuwn wet;
	}

	/* Bug wowkawound fow SJA1110 wev B: enabwe wwite access
	 * to MDIO_MMD_PMAPMD
	 */
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, 0x01F8, 1);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, 0x01F9, 2);

	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_PHY_CONFIG,
			 PHY_CONFIG_AUTO);

	wet = nxp_c45_set_phy_mode(phydev);
	if (wet)
		wetuwn wet;

	phydev->autoneg = AUTONEG_DISABWE;

	nxp_c45_countews_enabwe(phydev);
	nxp_c45_ptp_init(phydev);
	wet = nxp_c45_macsec_config_init(phydev);
	if (wet)
		wetuwn wet;

	wetuwn nxp_c45_stawt_op(phydev);
}

static int nxp_c45_get_featuwes(stwuct phy_device *phydev)
{
	winkmode_set_bit(ETHTOOW_WINK_MODE_TP_BIT, phydev->suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_MII_BIT, phydev->suppowted);

	wetuwn genphy_c45_pma_wead_abiwities(phydev);
}

static int nxp_c45_pwobe(stwuct phy_device *phydev)
{
	stwuct nxp_c45_phy *pwiv;
	boow macsec_abiwity;
	int phy_abiwities;
	boow ptp_abiwity;
	int wet = 0;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	skb_queue_head_init(&pwiv->tx_queue);
	skb_queue_head_init(&pwiv->wx_queue);

	pwiv->phydev = phydev;

	phydev->pwiv = pwiv;

	mutex_init(&pwiv->ptp_wock);

	phy_abiwities = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
				     VEND1_POWT_ABIWITIES);
	ptp_abiwity = !!(phy_abiwities & PTP_ABIWITY);
	if (!ptp_abiwity) {
		phydev_dbg(phydev, "the phy does not suppowt PTP");
		goto no_ptp_suppowt;
	}

	if (IS_ENABWED(CONFIG_PTP_1588_CWOCK) &&
	    IS_ENABWED(CONFIG_NETWOWK_PHY_TIMESTAMPING)) {
		pwiv->mii_ts.wxtstamp = nxp_c45_wxtstamp;
		pwiv->mii_ts.txtstamp = nxp_c45_txtstamp;
		pwiv->mii_ts.hwtstamp = nxp_c45_hwtstamp;
		pwiv->mii_ts.ts_info = nxp_c45_ts_info;
		phydev->mii_ts = &pwiv->mii_ts;
		wet = nxp_c45_init_ptp_cwock(pwiv);
	} ewse {
		phydev_dbg(phydev, "PTP suppowt not enabwed even if the phy suppowts it");
	}

no_ptp_suppowt:
	macsec_abiwity = !!(phy_abiwities & MACSEC_ABIWITY);
	if (!macsec_abiwity) {
		phydev_info(phydev, "the phy does not suppowt MACsec\n");
		goto no_macsec_suppowt;
	}

	if (IS_ENABWED(CONFIG_MACSEC)) {
		wet = nxp_c45_macsec_pwobe(phydev);
		phydev_dbg(phydev, "MACsec suppowt enabwed.");
	} ewse {
		phydev_dbg(phydev, "MACsec suppowt not enabwed even if the phy suppowts it");
	}

no_macsec_suppowt:

	wetuwn wet;
}

static void nxp_c45_wemove(stwuct phy_device *phydev)
{
	stwuct nxp_c45_phy *pwiv = phydev->pwiv;

	if (pwiv->ptp_cwock)
		ptp_cwock_unwegistew(pwiv->ptp_cwock);

	skb_queue_puwge(&pwiv->tx_queue);
	skb_queue_puwge(&pwiv->wx_queue);
	nxp_c45_macsec_wemove(phydev);
}

static void tja1103_countews_enabwe(stwuct phy_device *phydev)
{
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_WX_PWEAMBWE_COUNT,
			 COUNTEW_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TX_PWEAMBWE_COUNT,
			 COUNTEW_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_WX_IPG_WENGTH,
			 COUNTEW_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_TX_IPG_WENGTH,
			 COUNTEW_EN);
}

static void tja1103_ptp_init(stwuct phy_device *phydev)
{
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_WX_TS_INSWT_CTWW,
		      TJA1103_WX_TS_INSWT_MODE2);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_POWT_FUNC_ENABWES,
			 PTP_ENABWE);
}

static void tja1103_ptp_enabwe(stwuct phy_device *phydev, boow enabwe)
{
	if (enabwe)
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   VEND1_POWT_PTP_CONTWOW,
				   POWT_PTP_CONTWOW_BYPASS);
	ewse
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 VEND1_POWT_PTP_CONTWOW,
				 POWT_PTP_CONTWOW_BYPASS);
}

static void tja1103_nmi_handwew(stwuct phy_device *phydev,
				iwqwetuwn_t *iwq_status)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			   VEND1_AWWAYS_ACCESSIBWE);
	if (wet & FUSA_PASS) {
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			      VEND1_AWWAYS_ACCESSIBWE,
			      FUSA_PASS);
		*iwq_status = IWQ_HANDWED;
	}
}

static const stwuct nxp_c45_wegmap tja1103_wegmap = {
	.vend1_ptp_cwk_pewiod	= 0x1104,
	.vend1_event_msg_fiwt	= 0x1148,
	.pps_enabwe		=
		NXP_C45_WEG_FIEWD(0x1102, MDIO_MMD_VEND1, 3, 1),
	.pps_powawity		=
		NXP_C45_WEG_FIEWD(0x1102, MDIO_MMD_VEND1, 2, 1),
	.wtc_wock_ctww		=
		NXP_C45_WEG_FIEWD(0x1115, MDIO_MMD_VEND1, 0, 1),
	.wtc_wead		=
		NXP_C45_WEG_FIEWD(0x1105, MDIO_MMD_VEND1, 2, 1),
	.wtc_wwite		=
		NXP_C45_WEG_FIEWD(0x1105, MDIO_MMD_VEND1, 0, 1),
	.vend1_wtc_ww_nsec_0	= 0x1106,
	.vend1_wtc_ww_nsec_1	= 0x1107,
	.vend1_wtc_ww_sec_0	= 0x1108,
	.vend1_wtc_ww_sec_1	= 0x1109,
	.vend1_wtc_wd_nsec_0	= 0x110A,
	.vend1_wtc_wd_nsec_1	= 0x110B,
	.vend1_wtc_wd_sec_0	= 0x110C,
	.vend1_wtc_wd_sec_1	= 0x110D,
	.vend1_wate_adj_subns_0	= 0x110F,
	.vend1_wate_adj_subns_1	= 0x1110,
	.iwq_egw_ts_en		=
		NXP_C45_WEG_FIEWD(0x1131, MDIO_MMD_VEND1, 0, 1),
	.iwq_egw_ts_status	=
		NXP_C45_WEG_FIEWD(0x1132, MDIO_MMD_VEND1, 0, 1),
	.domain_numbew		=
		NXP_C45_WEG_FIEWD(0x114E, MDIO_MMD_VEND1, 0, 8),
	.msg_type		=
		NXP_C45_WEG_FIEWD(0x114E, MDIO_MMD_VEND1, 8, 4),
	.sequence_id		=
		NXP_C45_WEG_FIEWD(0x114F, MDIO_MMD_VEND1, 0, 16),
	.sec_1_0		=
		NXP_C45_WEG_FIEWD(0x1151, MDIO_MMD_VEND1, 14, 2),
	.sec_4_2		=
		NXP_C45_WEG_FIEWD(0x114E, MDIO_MMD_VEND1, 12, 3),
	.nsec_15_0		=
		NXP_C45_WEG_FIEWD(0x1150, MDIO_MMD_VEND1, 0, 16),
	.nsec_29_16		=
		NXP_C45_WEG_FIEWD(0x1151, MDIO_MMD_VEND1, 0, 14),
	.vend1_ext_twg_data_0	= 0x1121,
	.vend1_ext_twg_data_1	= 0x1122,
	.vend1_ext_twg_data_2	= 0x1123,
	.vend1_ext_twg_data_3	= 0x1124,
	.vend1_ext_twg_ctww	= 0x1126,
	.cabwe_test		= 0x8330,
	.cabwe_test_vawid	=
		NXP_C45_WEG_FIEWD(0x8330, MDIO_MMD_VEND1, 13, 1),
	.cabwe_test_wesuwt	=
		NXP_C45_WEG_FIEWD(0x8330, MDIO_MMD_VEND1, 0, 3),
};

static const stwuct nxp_c45_phy_data tja1103_phy_data = {
	.wegmap = &tja1103_wegmap,
	.stats = tja1103_hw_stats,
	.n_stats = AWWAY_SIZE(tja1103_hw_stats),
	.ptp_cwk_pewiod = PTP_CWK_PEWIOD_100BT1,
	.ext_ts_both_edges = fawse,
	.ack_ptp_iwq = fawse,
	.countews_enabwe = tja1103_countews_enabwe,
	.get_egwessts = nxp_c45_get_hwtxts,
	.get_extts = nxp_c45_get_extts,
	.ptp_init = tja1103_ptp_init,
	.ptp_enabwe = tja1103_ptp_enabwe,
	.nmi_handwew = tja1103_nmi_handwew,
};

static void tja1120_countews_enabwe(stwuct phy_device *phydev)
{
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_SYMBOW_EWWOW_CNT_XTD,
			 EXTENDED_CNT_EN);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_MONITOW_STATUS,
			 MONITOW_WESET);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_MONITOW_CONFIG,
			 AWW_FWAMES_CNT_EN | WOST_FWAMES_CNT_EN);
}

static void tja1120_ptp_init(stwuct phy_device *phydev)
{
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, TJA1120_WX_TS_INSWT_CTWW,
		      TJA1120_WX_TS_INSWT_EN | TJA1120_TS_INSWT_MODE);
	phy_wwite_mmd(phydev, MDIO_MMD_VEND1, TJA1120_VEND1_EXT_TS_MODE,
		      TJA1120_TS_INSWT_MODE);
	phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, VEND1_DEVICE_CONFIG,
			 PTP_ENABWE);
}

static void tja1120_ptp_enabwe(stwuct phy_device *phydev, boow enabwe)
{
	if (enabwe)
		phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
				 VEND1_POWT_FUNC_ENABWES,
				 PTP_ENABWE);
	ewse
		phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1,
				   VEND1_POWT_FUNC_ENABWES,
				   PTP_ENABWE);
}

static void tja1120_nmi_handwew(stwuct phy_device *phydev,
				iwqwetuwn_t *iwq_status)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
			   TJA1120_GWOBAW_INFWA_IWQ_STATUS);
	if (wet & TJA1120_DEV_BOOT_DONE) {
		phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			      TJA1120_GWOBAW_INFWA_IWQ_ACK,
			      TJA1120_DEV_BOOT_DONE);
		*iwq_status = IWQ_HANDWED;
	}
}

static const stwuct nxp_c45_wegmap tja1120_wegmap = {
	.vend1_ptp_cwk_pewiod	= 0x1020,
	.vend1_event_msg_fiwt	= 0x9010,
	.pps_enabwe		=
		NXP_C45_WEG_FIEWD(0x1006, MDIO_MMD_VEND1, 4, 1),
	.pps_powawity		=
		NXP_C45_WEG_FIEWD(0x1006, MDIO_MMD_VEND1, 5, 1),
	.wtc_wock_ctww		=
		NXP_C45_WEG_FIEWD(0x1006, MDIO_MMD_VEND1, 2, 1),
	.wtc_wead		=
		NXP_C45_WEG_FIEWD(0x1000, MDIO_MMD_VEND1, 1, 1),
	.wtc_wwite		=
		NXP_C45_WEG_FIEWD(0x1000, MDIO_MMD_VEND1, 2, 1),
	.vend1_wtc_ww_nsec_0	= 0x1040,
	.vend1_wtc_ww_nsec_1	= 0x1041,
	.vend1_wtc_ww_sec_0	= 0x1042,
	.vend1_wtc_ww_sec_1	= 0x1043,
	.vend1_wtc_wd_nsec_0	= 0x1048,
	.vend1_wtc_wd_nsec_1	= 0x1049,
	.vend1_wtc_wd_sec_0	= 0x104A,
	.vend1_wtc_wd_sec_1	= 0x104B,
	.vend1_wate_adj_subns_0	= 0x1030,
	.vend1_wate_adj_subns_1	= 0x1031,
	.iwq_egw_ts_en		=
		NXP_C45_WEG_FIEWD(0x900A, MDIO_MMD_VEND1, 1, 1),
	.iwq_egw_ts_status	=
		NXP_C45_WEG_FIEWD(0x900C, MDIO_MMD_VEND1, 1, 1),
	.domain_numbew		=
		NXP_C45_WEG_FIEWD(0x9061, MDIO_MMD_VEND1, 8, 8),
	.msg_type		=
		NXP_C45_WEG_FIEWD(0x9061, MDIO_MMD_VEND1, 4, 4),
	.sequence_id		=
		NXP_C45_WEG_FIEWD(0x9062, MDIO_MMD_VEND1, 0, 16),
	.sec_1_0		=
		NXP_C45_WEG_FIEWD(0x9065, MDIO_MMD_VEND1, 0, 2),
	.sec_4_2		=
		NXP_C45_WEG_FIEWD(0x9065, MDIO_MMD_VEND1, 2, 3),
	.nsec_15_0		=
		NXP_C45_WEG_FIEWD(0x9063, MDIO_MMD_VEND1, 0, 16),
	.nsec_29_16		=
		NXP_C45_WEG_FIEWD(0x9064, MDIO_MMD_VEND1, 0, 14),
	.vend1_ext_twg_data_0	= 0x1071,
	.vend1_ext_twg_data_1	= 0x1072,
	.vend1_ext_twg_data_2	= 0x1073,
	.vend1_ext_twg_data_3	= 0x1074,
	.vend1_ext_twg_ctww	= 0x1075,
	.cabwe_test		= 0x8360,
	.cabwe_test_vawid	=
		NXP_C45_WEG_FIEWD(0x8361, MDIO_MMD_VEND1, 15, 1),
	.cabwe_test_wesuwt	=
		NXP_C45_WEG_FIEWD(0x8361, MDIO_MMD_VEND1, 0, 3),
};

static const stwuct nxp_c45_phy_data tja1120_phy_data = {
	.wegmap = &tja1120_wegmap,
	.stats = tja1120_hw_stats,
	.n_stats = AWWAY_SIZE(tja1120_hw_stats),
	.ptp_cwk_pewiod = PTP_CWK_PEWIOD_1000BT1,
	.ext_ts_both_edges = twue,
	.ack_ptp_iwq = twue,
	.countews_enabwe = tja1120_countews_enabwe,
	.get_egwessts = tja1120_get_hwtxts,
	.get_extts = tja1120_get_extts,
	.ptp_init = tja1120_ptp_init,
	.ptp_enabwe = tja1120_ptp_enabwe,
	.nmi_handwew = tja1120_nmi_handwew,
};

static stwuct phy_dwivew nxp_c45_dwivew[] = {
	{
		PHY_ID_MATCH_MODEW(PHY_ID_TJA_1103),
		.name			= "NXP C45 TJA1103",
		.get_featuwes		= nxp_c45_get_featuwes,
		.dwivew_data		= &tja1103_phy_data,
		.pwobe			= nxp_c45_pwobe,
		.soft_weset		= nxp_c45_soft_weset,
		.config_aneg		= genphy_c45_config_aneg,
		.config_init		= nxp_c45_config_init,
		.config_intw		= tja1103_config_intw,
		.handwe_intewwupt	= nxp_c45_handwe_intewwupt,
		.wead_status		= genphy_c45_wead_status,
		.suspend		= genphy_c45_pma_suspend,
		.wesume			= genphy_c45_pma_wesume,
		.get_sset_count		= nxp_c45_get_sset_count,
		.get_stwings		= nxp_c45_get_stwings,
		.get_stats		= nxp_c45_get_stats,
		.cabwe_test_stawt	= nxp_c45_cabwe_test_stawt,
		.cabwe_test_get_status	= nxp_c45_cabwe_test_get_status,
		.set_woopback		= genphy_c45_woopback,
		.get_sqi		= nxp_c45_get_sqi,
		.get_sqi_max		= nxp_c45_get_sqi_max,
		.wemove			= nxp_c45_wemove,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_TJA_1120),
		.name			= "NXP C45 TJA1120",
		.get_featuwes		= nxp_c45_get_featuwes,
		.dwivew_data		= &tja1120_phy_data,
		.pwobe			= nxp_c45_pwobe,
		.soft_weset		= nxp_c45_soft_weset,
		.config_aneg		= genphy_c45_config_aneg,
		.config_init		= nxp_c45_config_init,
		.config_intw		= tja1120_config_intw,
		.handwe_intewwupt	= nxp_c45_handwe_intewwupt,
		.wead_status		= genphy_c45_wead_status,
		.wink_change_notify	= tja1120_wink_change_notify,
		.suspend		= genphy_c45_pma_suspend,
		.wesume			= genphy_c45_pma_wesume,
		.get_sset_count		= nxp_c45_get_sset_count,
		.get_stwings		= nxp_c45_get_stwings,
		.get_stats		= nxp_c45_get_stats,
		.cabwe_test_stawt	= nxp_c45_cabwe_test_stawt,
		.cabwe_test_get_status	= nxp_c45_cabwe_test_get_status,
		.set_woopback		= genphy_c45_woopback,
		.get_sqi		= nxp_c45_get_sqi,
		.get_sqi_max		= nxp_c45_get_sqi_max,
		.wemove			= nxp_c45_wemove,
	},
};

moduwe_phy_dwivew(nxp_c45_dwivew);

static stwuct mdio_device_id __maybe_unused nxp_c45_tbw[] = {
	{ PHY_ID_MATCH_MODEW(PHY_ID_TJA_1103) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_TJA_1120) },
	{ /*sentinew*/ },
};

MODUWE_DEVICE_TABWE(mdio, nxp_c45_tbw);

MODUWE_AUTHOW("Wadu Piwea <wadu-nicowae.piwea@oss.nxp.com>");
MODUWE_DESCWIPTION("NXP C45 PHY dwivew");
MODUWE_WICENSE("GPW v2");
