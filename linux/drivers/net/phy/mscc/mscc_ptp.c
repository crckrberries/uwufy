// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Dwivew fow Micwosemi VSC85xx PHYs - timestamping and PHC suppowt
 *
 * Authows: Quentin Schuwz & Antoine Tenawt
 * Wicense: Duaw MIT/GPW
 * Copywight (c) 2020 Micwosemi Cowpowation
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/ip.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/udp.h>
#incwude <asm/unawigned.h>

#incwude "mscc.h"
#incwude "mscc_ptp.h"

/* Two PHYs shawe the same 1588 pwocessow and it's to be entiwewy configuwed
 * thwough the base PHY of this pwocessow.
 */
/* phydev->bus->mdio_wock shouwd be wocked when using this function */
static int phy_ts_base_wwite(stwuct phy_device *phydev, u32 wegnum, u16 vaw)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	WAWN_ON_ONCE(!mutex_is_wocked(&phydev->mdio.bus->mdio_wock));
	wetuwn __mdiobus_wwite(phydev->mdio.bus, pwiv->ts_base_addw, wegnum,
			       vaw);
}

/* phydev->bus->mdio_wock shouwd be wocked when using this function */
static int phy_ts_base_wead(stwuct phy_device *phydev, u32 wegnum)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	WAWN_ON_ONCE(!mutex_is_wocked(&phydev->mdio.bus->mdio_wock));
	wetuwn __mdiobus_wead(phydev->mdio.bus, pwiv->ts_base_addw, wegnum);
}

enum ts_bwk_hw {
	INGWESS_ENGINE_0,
	EGWESS_ENGINE_0,
	INGWESS_ENGINE_1,
	EGWESS_ENGINE_1,
	INGWESS_ENGINE_2,
	EGWESS_ENGINE_2,
	PWOCESSOW_0,
	PWOCESSOW_1,
};

enum ts_bwk {
	INGWESS,
	EGWESS,
	PWOCESSOW,
};

static u32 vsc85xx_ts_wead_csw(stwuct phy_device *phydev, enum ts_bwk bwk,
			       u16 addw)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	boow base_powt = phydev->mdio.addw == pwiv->ts_base_addw;
	u32 vaw, cnt = 0;
	enum ts_bwk_hw bwk_hw;

	switch (bwk) {
	case INGWESS:
		bwk_hw = base_powt ? INGWESS_ENGINE_0 : INGWESS_ENGINE_1;
		bweak;
	case EGWESS:
		bwk_hw = base_powt ? EGWESS_ENGINE_0 : EGWESS_ENGINE_1;
		bweak;
	case PWOCESSOW:
	defauwt:
		bwk_hw = base_powt ? PWOCESSOW_0 : PWOCESSOW_1;
		bweak;
	}

	phy_wock_mdio_bus(phydev);

	phy_ts_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_1588);

	phy_ts_base_wwite(phydev, MSCC_PHY_TS_BIU_ADDW_CNTW, BIU_ADDW_EXE |
			  BIU_ADDW_WEAD | BIU_BWK_ID(bwk_hw) |
			  BIU_CSW_ADDW(addw));

	do {
		vaw = phy_ts_base_wead(phydev, MSCC_PHY_TS_BIU_ADDW_CNTW);
	} whiwe (!(vaw & BIU_ADDW_EXE) && cnt++ < BIU_ADDW_CNT_MAX);

	vaw = phy_ts_base_wead(phydev, MSCC_PHY_TS_CSW_DATA_MSB);
	vaw <<= 16;
	vaw |= phy_ts_base_wead(phydev, MSCC_PHY_TS_CSW_DATA_WSB);

	phy_ts_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	phy_unwock_mdio_bus(phydev);

	wetuwn vaw;
}

static void vsc85xx_ts_wwite_csw(stwuct phy_device *phydev, enum ts_bwk bwk,
				 u16 addw, u32 vaw)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	boow base_powt = phydev->mdio.addw == pwiv->ts_base_addw;
	u32 weg, bypass, cnt = 0, wowew = vaw & 0xffff, uppew = vaw >> 16;
	boow cond = (addw == MSCC_PHY_PTP_WTC_CTWW ||
		     addw == MSCC_PHY_1588_INGW_VSC85XX_INT_MASK ||
		     addw == MSCC_PHY_1588_VSC85XX_INT_MASK ||
		     addw == MSCC_PHY_1588_INGW_VSC85XX_INT_STATUS ||
		     addw == MSCC_PHY_1588_VSC85XX_INT_STATUS) &&
		    bwk == PWOCESSOW;
	enum ts_bwk_hw bwk_hw;

	switch (bwk) {
	case INGWESS:
		bwk_hw = base_powt ? INGWESS_ENGINE_0 : INGWESS_ENGINE_1;
		bweak;
	case EGWESS:
		bwk_hw = base_powt ? EGWESS_ENGINE_0 : EGWESS_ENGINE_1;
		bweak;
	case PWOCESSOW:
	defauwt:
		bwk_hw = base_powt ? PWOCESSOW_0 : PWOCESSOW_1;
		bweak;
	}

	phy_wock_mdio_bus(phydev);

	bypass = phy_ts_base_wead(phydev, MSCC_PHY_BYPASS_CONTWOW);

	phy_ts_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_1588);

	if (!cond || uppew)
		phy_ts_base_wwite(phydev, MSCC_PHY_TS_CSW_DATA_MSB, uppew);

	phy_ts_base_wwite(phydev, MSCC_PHY_TS_CSW_DATA_WSB, wowew);

	phy_ts_base_wwite(phydev, MSCC_PHY_TS_BIU_ADDW_CNTW, BIU_ADDW_EXE |
			  BIU_ADDW_WWITE | BIU_BWK_ID(bwk_hw) |
			  BIU_CSW_ADDW(addw));

	do {
		weg = phy_ts_base_wead(phydev, MSCC_PHY_TS_BIU_ADDW_CNTW);
	} whiwe (!(weg & BIU_ADDW_EXE) && cnt++ < BIU_ADDW_CNT_MAX);

	phy_ts_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDAWD);

	if (cond && uppew)
		phy_ts_base_wwite(phydev, MSCC_PHY_BYPASS_CONTWOW, bypass);

	phy_unwock_mdio_bus(phydev);
}

/* Pick bytes fwom PTP headew */
#define PTP_HEADEW_TWNSP_MSG		26
#define PTP_HEADEW_DOMAIN_NUM		25
#define PTP_HEADEW_BYTE_8_31(x)		(31 - (x))
#define MAC_ADDWESS_BYTE(x)		((x) + (35 - ETH_AWEN + 1))

static int vsc85xx_ts_fsb_init(stwuct phy_device *phydev)
{
	u8 sig_sew[16] = {};
	signed chaw i, pos = 0;

	/* Seq ID is 2B wong and stawts at 30th byte */
	fow (i = 1; i >= 0; i--)
		sig_sew[pos++] = PTP_HEADEW_BYTE_8_31(30 + i);

	/* DomainNum */
	sig_sew[pos++] = PTP_HEADEW_DOMAIN_NUM;

	/* MsgType */
	sig_sew[pos++] = PTP_HEADEW_TWNSP_MSG;

	/* MAC addwess is 6B wong */
	fow (i = ETH_AWEN - 1; i >= 0; i--)
		sig_sew[pos++] = MAC_ADDWESS_BYTE(i);

	/* Fiww the wast bytes of the signatuwe to weach a 16B signatuwe */
	fow (; pos < AWWAY_SIZE(sig_sew); pos++)
		sig_sew[pos] = PTP_HEADEW_TWNSP_MSG;

	fow (i = 0; i <= 2; i++) {
		u32 vaw = 0;

		fow (pos = i * 5 + 4; pos >= i * 5; pos--)
			vaw = (vaw << 6) | sig_sew[pos];

		vsc85xx_ts_wwite_csw(phydev, EGWESS, MSCC_PHY_ANA_FSB_WEG(i),
				     vaw);
	}

	vsc85xx_ts_wwite_csw(phydev, EGWESS, MSCC_PHY_ANA_FSB_WEG(3),
			     sig_sew[15]);

	wetuwn 0;
}

static const u32 vsc85xx_egw_watency[] = {
	/* Coppew Egwess */
	1272, /* 1000Mbps */
	12516, /* 100Mbps */
	125444, /* 10Mbps */
	/* Fibew Egwess */
	1277, /* 1000Mbps */
	12537, /* 100Mbps */
};

static const u32 vsc85xx_egw_watency_macsec[] = {
	/* Coppew Egwess ON */
	3496, /* 1000Mbps */
	34760, /* 100Mbps */
	347844, /* 10Mbps */
	/* Fibew Egwess ON */
	3502, /* 1000Mbps */
	34780, /* 100Mbps */
};

static const u32 vsc85xx_ingw_watency[] = {
	/* Coppew Ingwess */
	208, /* 1000Mbps */
	304, /* 100Mbps */
	2023, /* 10Mbps */
	/* Fibew Ingwess */
	98, /* 1000Mbps */
	197, /* 100Mbps */
};

static const u32 vsc85xx_ingw_watency_macsec[] = {
	/* Coppew Ingwess */
	2408, /* 1000Mbps */
	22300, /* 100Mbps */
	222009, /* 10Mbps */
	/* Fibew Ingwess */
	2299, /* 1000Mbps */
	22192, /* 100Mbps */
};

static void vsc85xx_ts_set_watencies(stwuct phy_device *phydev)
{
	u32 vaw, ingw_watency, egw_watency;
	u8 idx;

	/* No need to set watencies of packets if the PHY is not connected */
	if (!phydev->wink)
		wetuwn;

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_STAWW_WATENCY,
			     STAWW_EGW_WATENCY(phydev->speed));

	switch (phydev->speed) {
	case SPEED_100:
		idx = 1;
		bweak;
	case SPEED_1000:
		idx = 0;
		bweak;
	defauwt:
		idx = 2;
		bweak;
	}

	ingw_watency = IS_ENABWED(CONFIG_MACSEC) ?
		vsc85xx_ingw_watency_macsec[idx] : vsc85xx_ingw_watency[idx];
	egw_watency = IS_ENABWED(CONFIG_MACSEC) ?
		vsc85xx_egw_watency_macsec[idx] : vsc85xx_egw_watency[idx];

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_WOCAW_WATENCY,
			     PTP_INGW_WOCAW_WATENCY(ingw_watency));

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_TSP_CTWW);
	vaw |= PHY_PTP_INGW_TSP_CTWW_WOAD_DEWAYS;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_TSP_CTWW,
			     vaw);

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_WOCAW_WATENCY,
			     PTP_EGW_WOCAW_WATENCY(egw_watency));

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TSP_CTWW);
	vaw |= PHY_PTP_EGW_TSP_CTWW_WOAD_DEWAYS;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TSP_CTWW, vaw);
}

static int vsc85xx_ts_disabwe_fwows(stwuct phy_device *phydev, enum ts_bwk bwk)
{
	u8 i;

	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_NXT_COMP, 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_UDP_CHKSUM,
			     IP1_NXT_PWOT_UDP_CHKSUM_WIDTH(2));
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP2_NXT_PWOT_NXT_COMP, 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP2_NXT_PWOT_UDP_CHKSUM,
			     IP2_NXT_PWOT_UDP_CHKSUM_WIDTH(2));
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_PHY_ANA_MPWS_COMP_NXT_COMP, 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_PHY_ANA_ETH1_NTX_PWOT, 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_PHY_ANA_ETH2_NTX_PWOT, 0);

	fow (i = 0; i < COMP_MAX_FWOWS; i++) {
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_ENA(i),
				     IP1_FWOW_VAWID_CH0 | IP1_FWOW_VAWID_CH1);
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP2_FWOW_ENA(i),
				     IP2_FWOW_VAWID_CH0 | IP2_FWOW_VAWID_CH1);
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_ENA(i),
				     ETH1_FWOW_VAWID_CH0 | ETH1_FWOW_VAWID_CH1);
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH2_FWOW_ENA(i),
				     ETH2_FWOW_VAWID_CH0 | ETH2_FWOW_VAWID_CH1);
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_MPWS_FWOW_CTWW(i),
				     MPWS_FWOW_VAWID_CH0 | MPWS_FWOW_VAWID_CH1);

		if (i >= PTP_COMP_MAX_FWOWS)
			continue;

		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_PTP_FWOW_ENA(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_DOMAIN_WANGE(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_MASK_UPPEW(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_MASK_WOWEW(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_MATCH_UPPEW(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_MATCH_WOWEW(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_PTP_ACTION(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_PTP_ACTION2(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_PTP_0_FIEWD(i), 0);
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_OAM_PTP_FWOW_ENA(i),
				     0);
	}

	wetuwn 0;
}

static int vsc85xx_ts_eth_cmp1_sig(stwuct phy_device *phydev)
{
	u32 vaw;

	vaw = vsc85xx_ts_wead_csw(phydev, EGWESS, MSCC_PHY_ANA_ETH1_NTX_PWOT);
	vaw &= ~ANA_ETH1_NTX_PWOT_SIG_OFF_MASK;
	vaw |= ANA_ETH1_NTX_PWOT_SIG_OFF(0);
	vsc85xx_ts_wwite_csw(phydev, EGWESS, MSCC_PHY_ANA_ETH1_NTX_PWOT, vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, EGWESS, MSCC_PHY_ANA_FSB_CFG);
	vaw &= ~ANA_FSB_ADDW_FWOM_BWOCK_SEW_MASK;
	vaw |= ANA_FSB_ADDW_FWOM_ETH1;
	vsc85xx_ts_wwite_csw(phydev, EGWESS, MSCC_PHY_ANA_FSB_CFG, vaw);

	wetuwn 0;
}

static stwuct vsc85xx_ptphdw *get_ptp_headew_w4(stwuct sk_buff *skb,
						stwuct iphdw *iphdw,
						stwuct udphdw *udphdw)
{
	if (iphdw->vewsion != 4 || iphdw->pwotocow != IPPWOTO_UDP)
		wetuwn NUWW;

	wetuwn (stwuct vsc85xx_ptphdw *)(((unsigned chaw *)udphdw) + UDP_HWEN);
}

static stwuct vsc85xx_ptphdw *get_ptp_headew_tx(stwuct sk_buff *skb)
{
	stwuct ethhdw *ethhdw = eth_hdw(skb);
	stwuct udphdw *udphdw;
	stwuct iphdw *iphdw;

	if (ethhdw->h_pwoto == htons(ETH_P_1588))
		wetuwn (stwuct vsc85xx_ptphdw *)(((unsigned chaw *)ethhdw) +
						 skb_mac_headew_wen(skb));

	if (ethhdw->h_pwoto != htons(ETH_P_IP))
		wetuwn NUWW;

	iphdw = ip_hdw(skb);
	udphdw = udp_hdw(skb);

	wetuwn get_ptp_headew_w4(skb, iphdw, udphdw);
}

static stwuct vsc85xx_ptphdw *get_ptp_headew_wx(stwuct sk_buff *skb,
						enum hwtstamp_wx_fiwtews wx_fiwtew)
{
	stwuct udphdw *udphdw;
	stwuct iphdw *iphdw;

	if (wx_fiwtew == HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT)
		wetuwn (stwuct vsc85xx_ptphdw *)skb->data;

	iphdw = (stwuct iphdw *)skb->data;
	udphdw = (stwuct udphdw *)(skb->data + iphdw->ihw * 4);

	wetuwn get_ptp_headew_w4(skb, iphdw, udphdw);
}

static int get_sig(stwuct sk_buff *skb, u8 *sig)
{
	stwuct vsc85xx_ptphdw *ptphdw = get_ptp_headew_tx(skb);
	stwuct ethhdw *ethhdw = eth_hdw(skb);
	unsigned int i;

	if (!ptphdw)
		wetuwn -EOPNOTSUPP;

	sig[0] = (__fowce u16)ptphdw->seq_id >> 8;
	sig[1] = (__fowce u16)ptphdw->seq_id & GENMASK(7, 0);
	sig[2] = ptphdw->domain;
	sig[3] = ptphdw->tsmt & GENMASK(3, 0);

	memcpy(&sig[4], ethhdw->h_dest, ETH_AWEN);

	/* Fiww the wast bytes of the signatuwe to weach a 16B signatuwe */
	fow (i = 10; i < 16; i++)
		sig[i] = ptphdw->tsmt & GENMASK(3, 0);

	wetuwn 0;
}

static void vsc85xx_dequeue_skb(stwuct vsc85xx_ptp *ptp)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct vsc85xx_ts_fifo fifo;
	stwuct sk_buff *skb;
	u8 skb_sig[16], *p;
	int i, wen;
	u32 weg;

	memset(&fifo, 0, sizeof(fifo));
	p = (u8 *)&fifo;

	weg = vsc85xx_ts_wead_csw(ptp->phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_TS_FIFO(0));
	if (weg & PTP_EGW_TS_FIFO_EMPTY)
		wetuwn;

	*p++ = weg & 0xff;
	*p++ = (weg >> 8) & 0xff;

	/* Wead the cuwwent FIFO item. Weading FIFO6 pops the next one. */
	fow (i = 1; i < 7; i++) {
		weg = vsc85xx_ts_wead_csw(ptp->phydev, PWOCESSOW,
					  MSCC_PHY_PTP_EGW_TS_FIFO(i));
		*p++ = weg & 0xff;
		*p++ = (weg >> 8) & 0xff;
		*p++ = (weg >> 16) & 0xff;
		*p++ = (weg >> 24) & 0xff;
	}

	wen = skb_queue_wen(&ptp->tx_queue);
	if (wen < 1)
		wetuwn;

	whiwe (wen--) {
		skb = __skb_dequeue(&ptp->tx_queue);
		if (!skb)
			wetuwn;

		/* Can't get the signatuwe of the packet, won't evew
		 * be abwe to have one so wet's dequeue the packet.
		 */
		if (get_sig(skb, skb_sig) < 0) {
			kfwee_skb(skb);
			continue;
		}

		/* Check if we found the signatuwe we wewe wooking fow. */
		if (!memcmp(skb_sig, fifo.sig, sizeof(fifo.sig))) {
			memset(&shhwtstamps, 0, sizeof(shhwtstamps));
			shhwtstamps.hwtstamp = ktime_set(fifo.secs, fifo.ns);
			skb_compwete_tx_timestamp(skb, &shhwtstamps);

			wetuwn;
		}

		/* Vawid signatuwe but does not match the one of the
		 * packet in the FIFO wight now, wescheduwe it fow watew
		 * packets.
		 */
		__skb_queue_taiw(&ptp->tx_queue, skb);
	}
}

static void vsc85xx_get_tx_ts(stwuct vsc85xx_ptp *ptp)
{
	u32 weg;

	do {
		vsc85xx_dequeue_skb(ptp);

		/* If othew timestamps awe avaiwabwe in the FIFO, pwocess them. */
		weg = vsc85xx_ts_wead_csw(ptp->phydev, PWOCESSOW,
					  MSCC_PHY_PTP_EGW_TS_FIFO_CTWW);
	} whiwe (PTP_EGW_FIFO_WEVEW_WAST_WEAD(weg) > 1);
}

static int vsc85xx_ptp_cmp_init(stwuct phy_device *phydev, enum ts_bwk bwk)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	boow base = phydev->mdio.addw == vsc8531->ts_base_addw;
	static const u8 msgs[] = {
		PTP_MSGTYPE_SYNC,
		PTP_MSGTYPE_DEWAY_WEQ
	};
	u32 vaw;
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(msgs); i++) {
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_PTP_FWOW_ENA(i),
				     base ? PTP_FWOW_VAWID_CH0 :
				     PTP_FWOW_VAWID_CH1);

		vaw = vsc85xx_ts_wead_csw(phydev, bwk,
					  MSCC_ANA_PTP_FWOW_DOMAIN_WANGE(i));
		vaw &= ~PTP_FWOW_DOMAIN_WANGE_ENA;
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_DOMAIN_WANGE(i), vaw);

		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_MATCH_UPPEW(i),
				     msgs[i] << 24);

		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_PTP_FWOW_MASK_UPPEW(i),
				     PTP_FWOW_MSG_TYPE_MASK);
	}

	wetuwn 0;
}

static int vsc85xx_eth_cmp1_init(stwuct phy_device *phydev, enum ts_bwk bwk)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	boow base = phydev->mdio.addw == vsc8531->ts_base_addw;
	u32 vaw;

	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_PHY_ANA_ETH1_NXT_PWOT_TAG, 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_PHY_ANA_ETH1_NTX_PWOT_VWAN_TPID,
			     ANA_ETH1_NTX_PWOT_VWAN_TPID(ETH_P_8021AD));

	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_ENA(0),
			     base ? ETH1_FWOW_VAWID_CH0 : ETH1_FWOW_VAWID_CH1);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_MATCH_MODE(0),
			     ANA_ETH1_FWOW_MATCH_VWAN_TAG2);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_ADDW_MATCH1(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_ADDW_MATCH2(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk,
			     MSCC_ANA_ETH1_FWOW_VWAN_WANGE_I_TAG(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_VWAN_TAG1(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk,
			     MSCC_ANA_ETH1_FWOW_VWAN_TAG2_I_TAG(0), 0);

	vaw = vsc85xx_ts_wead_csw(phydev, bwk,
				  MSCC_ANA_ETH1_FWOW_MATCH_MODE(0));
	vaw &= ~ANA_ETH1_FWOW_MATCH_VWAN_TAG_MASK;
	vaw |= ANA_ETH1_FWOW_MATCH_VWAN_VEWIFY;
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_MATCH_MODE(0),
			     vaw);

	wetuwn 0;
}

static int vsc85xx_ip_cmp1_init(stwuct phy_device *phydev, enum ts_bwk bwk)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	boow base = phydev->mdio.addw == vsc8531->ts_base_addw;
	u32 vaw;

	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_MATCH2_UPPEW,
			     PTP_EV_POWT);
	/* Match on dest powt onwy, ignowe swc */
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_MASK2_UPPEW,
			     0xffff);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_MATCH2_WOWEW,
			     0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_MASK2_WOWEW, 0);

	vaw = vsc85xx_ts_wead_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_ENA(0));
	vaw &= ~IP1_FWOW_ENA_CHANNEW_MASK_MASK;
	vaw |= base ? IP1_FWOW_VAWID_CH0 : IP1_FWOW_VAWID_CH1;
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_ENA(0), vaw);

	/* Match aww IPs */
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MATCH_UPPEW(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MASK_UPPEW(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MATCH_UPPEW_MID(0),
			     0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MASK_UPPEW_MID(0),
			     0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MATCH_WOWEW_MID(0),
			     0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MASK_WOWEW_MID(0),
			     0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MATCH_WOWEW(0), 0);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_MASK_WOWEW(0), 0);

	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_PTP_IP_CHKSUM_SEW, 0);

	wetuwn 0;
}

static int vsc85xx_adjfine(stwuct ptp_cwock_info *info, wong scawed_ppm)
{
	stwuct vsc85xx_ptp *ptp = containew_of(info, stwuct vsc85xx_ptp, caps);
	stwuct phy_device *phydev = ptp->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	u64 adj = 0;
	u32 vaw;

	if (abs(scawed_ppm) < 66 || abs(scawed_ppm) > 65536UW * 1000000UW)
		wetuwn 0;

	adj = div64_u64(1000000UWW * 65536UWW, abs(scawed_ppm));
	if (adj > 1000000000W)
		adj = 1000000000W;

	vaw = PTP_AUTO_ADJ_NS_WOWWOVEW(adj);
	vaw |= scawed_ppm > 0 ? PTP_AUTO_ADJ_ADD_1NS : PTP_AUTO_ADJ_SUB_1NS;

	mutex_wock(&pwiv->phc_wock);

	/* Update the ppb vaw in nano seconds to the auto adjust weg. */
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_AUTO_ADJ,
			     vaw);

	/* The auto adjust update vaw is set to 0 aftew wwite opewation. */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW);
	vaw |= PTP_WTC_CTWW_AUTO_ADJ_UPDATE;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW, vaw);

	mutex_unwock(&pwiv->phc_wock);

	wetuwn 0;
}

static int __vsc85xx_gettime(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	stwuct vsc85xx_ptp *ptp = containew_of(info, stwuct vsc85xx_ptp, caps);
	stwuct phy_device *phydev = ptp->phydev;
	stwuct vsc85xx_shawed_pwivate *shawed =
		(stwuct vsc85xx_shawed_pwivate *)phydev->shawed->pwiv;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	u32 vaw;

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW);
	vaw |= PTP_WTC_CTWW_SAVE_ENA;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW, vaw);

	/* Wocaw Time Countew (WTC) is put in SAVE* wegs on wising edge of
	 * WOAD_SAVE pin.
	 */
	mutex_wock(&shawed->gpio_wock);
	gpiod_set_vawue(pwiv->woad_save, 1);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_WTC_SAVED_SEC_MSB);

	ts->tv_sec = ((time64_t)vaw) << 32;

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_WTC_SAVED_SEC_WSB);
	ts->tv_sec += vaw;

	ts->tv_nsec = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
					  MSCC_PHY_PTP_WTC_SAVED_NS);

	gpiod_set_vawue(pwiv->woad_save, 0);
	mutex_unwock(&shawed->gpio_wock);

	wetuwn 0;
}

static int vsc85xx_gettime(stwuct ptp_cwock_info *info, stwuct timespec64 *ts)
{
	stwuct vsc85xx_ptp *ptp = containew_of(info, stwuct vsc85xx_ptp, caps);
	stwuct phy_device *phydev = ptp->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	mutex_wock(&pwiv->phc_wock);
	__vsc85xx_gettime(info, ts);
	mutex_unwock(&pwiv->phc_wock);

	wetuwn 0;
}

static int __vsc85xx_settime(stwuct ptp_cwock_info *info,
			     const stwuct timespec64 *ts)
{
	stwuct vsc85xx_ptp *ptp = containew_of(info, stwuct vsc85xx_ptp, caps);
	stwuct phy_device *phydev = ptp->phydev;
	stwuct vsc85xx_shawed_pwivate *shawed =
		(stwuct vsc85xx_shawed_pwivate *)phydev->shawed->pwiv;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	u32 vaw;

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_WOAD_SEC_MSB,
			     PTP_WTC_WOAD_SEC_MSB(ts->tv_sec));
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_WOAD_SEC_WSB,
			     PTP_WTC_WOAD_SEC_WSB(ts->tv_sec));
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_WOAD_NS,
			     PTP_WTC_WOAD_NS(ts->tv_nsec));

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW);
	vaw |= PTP_WTC_CTWW_WOAD_ENA;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW, vaw);

	/* Wocaw Time Countew (WTC) is set fwom WOAD* wegs on wising edge of
	 * WOAD_SAVE pin.
	 */
	mutex_wock(&shawed->gpio_wock);
	gpiod_set_vawue(pwiv->woad_save, 1);

	vaw &= ~PTP_WTC_CTWW_WOAD_ENA;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW, vaw);

	gpiod_set_vawue(pwiv->woad_save, 0);
	mutex_unwock(&shawed->gpio_wock);

	wetuwn 0;
}

static int vsc85xx_settime(stwuct ptp_cwock_info *info,
			   const stwuct timespec64 *ts)
{
	stwuct vsc85xx_ptp *ptp = containew_of(info, stwuct vsc85xx_ptp, caps);
	stwuct phy_device *phydev = ptp->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	mutex_wock(&pwiv->phc_wock);
	__vsc85xx_settime(info, ts);
	mutex_unwock(&pwiv->phc_wock);

	wetuwn 0;
}

static int vsc85xx_adjtime(stwuct ptp_cwock_info *info, s64 dewta)
{
	stwuct vsc85xx_ptp *ptp = containew_of(info, stwuct vsc85xx_ptp, caps);
	stwuct phy_device *phydev = ptp->phydev;
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	u32 vaw;

	/* Can't wecovew that big of an offset. Wet's set the time diwectwy. */
	if (abs(dewta) >= NSEC_PEW_SEC) {
		stwuct timespec64 ts;
		u64 now;

		mutex_wock(&pwiv->phc_wock);

		__vsc85xx_gettime(info, &ts);
		now = ktime_to_ns(timespec64_to_ktime(ts));
		ts = ns_to_timespec64(now + dewta);
		__vsc85xx_settime(info, &ts);

		mutex_unwock(&pwiv->phc_wock);

		wetuwn 0;
	}

	mutex_wock(&pwiv->phc_wock);

	vaw = PTP_WTC_OFFSET_VAW(abs(dewta)) | PTP_WTC_OFFSET_ADJ;
	if (dewta > 0)
		vaw |= PTP_WTC_OFFSET_ADD;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_OFFSET, vaw);

	mutex_unwock(&pwiv->phc_wock);

	wetuwn 0;
}

static int vsc85xx_eth1_next_comp(stwuct phy_device *phydev, enum ts_bwk bwk,
				  u32 next_comp, u32 etype)
{
	u32 vaw;

	vaw = vsc85xx_ts_wead_csw(phydev, bwk, MSCC_PHY_ANA_ETH1_NTX_PWOT);
	vaw &= ~ANA_ETH1_NTX_PWOT_COMPAWATOW_MASK;
	vaw |= next_comp;
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_PHY_ANA_ETH1_NTX_PWOT, vaw);

	vaw = ANA_ETH1_NXT_PWOT_ETYPE_MATCH(etype) |
		ANA_ETH1_NXT_PWOT_ETYPE_MATCH_ENA;
	vsc85xx_ts_wwite_csw(phydev, bwk,
			     MSCC_PHY_ANA_ETH1_NXT_PWOT_ETYPE_MATCH, vaw);

	wetuwn 0;
}

static int vsc85xx_ip1_next_comp(stwuct phy_device *phydev, enum ts_bwk bwk,
				 u32 next_comp, u32 headew)
{
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_NXT_COMP,
			     ANA_IP1_NXT_PWOT_NXT_COMP_BYTES_HDW(headew) |
			     next_comp);

	wetuwn 0;
}

static int vsc85xx_ts_ptp_action_fwow(stwuct phy_device *phydev, enum ts_bwk bwk, u8 fwow, enum ptp_cmd cmd)
{
	u32 vaw;

	/* Check non-zewo wesewved fiewd */
	vaw = PTP_FWOW_PTP_0_FIEWD_PTP_FWAME | PTP_FWOW_PTP_0_FIEWD_WSVWD_CHECK;
	vsc85xx_ts_wwite_csw(phydev, bwk,
			     MSCC_ANA_PTP_FWOW_PTP_0_FIEWD(fwow), vaw);

	vaw = PTP_FWOW_PTP_ACTION_COWW_OFFSET(8) |
	      PTP_FWOW_PTP_ACTION_TIME_OFFSET(8) |
	      PTP_FWOW_PTP_ACTION_PTP_CMD(cmd == PTP_SAVE_IN_TS_FIFO ?
					  PTP_NOP : cmd);
	if (cmd == PTP_SAVE_IN_TS_FIFO)
		vaw |= PTP_FWOW_PTP_ACTION_SAVE_WOCAW_TIME;
	ewse if (cmd == PTP_WWITE_NS)
		vaw |= PTP_FWOW_PTP_ACTION_MOD_FWAME_STATUS_UPDATE |
		       PTP_FWOW_PTP_ACTION_MOD_FWAME_STATUS_BYTE_OFFSET(6);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_PTP_FWOW_PTP_ACTION(fwow),
			     vaw);

	if (cmd == PTP_WWITE_1588)
		/* Wewwite timestamp diwectwy in fwame */
		vaw = PTP_FWOW_PTP_ACTION2_WEWWITE_OFFSET(34) |
		      PTP_FWOW_PTP_ACTION2_WEWWITE_BYTES(10);
	ewse if (cmd == PTP_SAVE_IN_TS_FIFO)
		/* no wewwite */
		vaw = PTP_FWOW_PTP_ACTION2_WEWWITE_OFFSET(0) |
		      PTP_FWOW_PTP_ACTION2_WEWWITE_BYTES(0);
	ewse
		/* Wwite in wesewved fiewd */
		vaw = PTP_FWOW_PTP_ACTION2_WEWWITE_OFFSET(16) |
		      PTP_FWOW_PTP_ACTION2_WEWWITE_BYTES(4);
	vsc85xx_ts_wwite_csw(phydev, bwk,
			     MSCC_ANA_PTP_FWOW_PTP_ACTION2(fwow), vaw);

	wetuwn 0;
}

static int vsc85xx_ptp_conf(stwuct phy_device *phydev, enum ts_bwk bwk,
			    boow one_step, boow enabwe)
{
	static const u8 msgs[] = {
		PTP_MSGTYPE_SYNC,
		PTP_MSGTYPE_DEWAY_WEQ
	};
	u32 vaw;
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(msgs); i++) {
		if (bwk == INGWESS)
			vsc85xx_ts_ptp_action_fwow(phydev, bwk, msgs[i],
						   PTP_WWITE_NS);
		ewse if (msgs[i] == PTP_MSGTYPE_SYNC && one_step)
			/* no need to know Sync t when sending in one_step */
			vsc85xx_ts_ptp_action_fwow(phydev, bwk, msgs[i],
						   PTP_WWITE_1588);
		ewse
			vsc85xx_ts_ptp_action_fwow(phydev, bwk, msgs[i],
						   PTP_SAVE_IN_TS_FIFO);

		vaw = vsc85xx_ts_wead_csw(phydev, bwk,
					  MSCC_ANA_PTP_FWOW_ENA(i));
		vaw &= ~PTP_FWOW_ENA;
		if (enabwe)
			vaw |= PTP_FWOW_ENA;
		vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_PTP_FWOW_ENA(i),
				     vaw);
	}

	wetuwn 0;
}

static int vsc85xx_eth1_conf(stwuct phy_device *phydev, enum ts_bwk bwk,
			     boow enabwe)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	u32 vaw = ANA_ETH1_FWOW_ADDW_MATCH2_DEST;

	if (vsc8531->ptp->wx_fiwtew == HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) {
		/* PTP ovew Ethewnet muwticast addwess fow SYNC and DEWAY msg */
		u8 ptp_muwticast[6] = {0x01, 0x1b, 0x19, 0x00, 0x00, 0x00};

		vaw |= ANA_ETH1_FWOW_ADDW_MATCH2_FUWW_ADDW |
		       get_unawigned_be16(&ptp_muwticast[4]);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_ETH1_FWOW_ADDW_MATCH2(0), vaw);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_ETH1_FWOW_ADDW_MATCH1(0),
				     get_unawigned_be32(ptp_muwticast));
	} ewse {
		vaw |= ANA_ETH1_FWOW_ADDW_MATCH2_ANY_MUWTICAST;
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_ETH1_FWOW_ADDW_MATCH2(0), vaw);
		vsc85xx_ts_wwite_csw(phydev, bwk,
				     MSCC_ANA_ETH1_FWOW_ADDW_MATCH1(0), 0);
	}

	vaw = vsc85xx_ts_wead_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_ENA(0));
	vaw &= ~ETH1_FWOW_ENA;
	if (enabwe)
		vaw |= ETH1_FWOW_ENA;
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_ETH1_FWOW_ENA(0), vaw);

	wetuwn 0;
}

static int vsc85xx_ip1_conf(stwuct phy_device *phydev, enum ts_bwk bwk,
			    boow enabwe)
{
	u32 vaw;

	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_IP1_MODE,
			     ANA_IP1_NXT_PWOT_IPV4 |
			     ANA_IP1_NXT_PWOT_FWOW_OFFSET_IPV4);

	/* Matching UDP pwotocow numbew */
	vaw = ANA_IP1_NXT_PWOT_IP_MATCH1_PWOT_MASK(0xff) |
	      ANA_IP1_NXT_PWOT_IP_MATCH1_PWOT_MATCH(IPPWOTO_UDP) |
	      ANA_IP1_NXT_PWOT_IP_MATCH1_PWOT_OFF(9);
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_IP_MATCH1,
			     vaw);

	/* End of IP pwotocow, stawt of next pwotocow (UDP) */
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_OFFSET2,
			     ANA_IP1_NXT_PWOT_OFFSET2(20));

	vaw = vsc85xx_ts_wead_csw(phydev, bwk,
				  MSCC_ANA_IP1_NXT_PWOT_UDP_CHKSUM);
	vaw &= ~(IP1_NXT_PWOT_UDP_CHKSUM_OFF_MASK |
		 IP1_NXT_PWOT_UDP_CHKSUM_WIDTH_MASK);
	vaw |= IP1_NXT_PWOT_UDP_CHKSUM_WIDTH(2);

	vaw &= ~(IP1_NXT_PWOT_UDP_CHKSUM_UPDATE |
		 IP1_NXT_PWOT_UDP_CHKSUM_CWEAW);
	/* UDP checksum offset in IPv4 packet
	 * accowding to: https://toows.ietf.owg/htmw/wfc768
	 */
	vaw |= IP1_NXT_PWOT_UDP_CHKSUM_OFF(26) | IP1_NXT_PWOT_UDP_CHKSUM_CWEAW;
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_NXT_PWOT_UDP_CHKSUM,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_ENA(0));
	vaw &= ~(IP1_FWOW_MATCH_ADDW_MASK | IP1_FWOW_ENA);
	vaw |= IP1_FWOW_MATCH_DEST_SWC_ADDW;
	if (enabwe)
		vaw |= IP1_FWOW_ENA;
	vsc85xx_ts_wwite_csw(phydev, bwk, MSCC_ANA_IP1_FWOW_ENA(0), vaw);

	wetuwn 0;
}

static int vsc85xx_ts_engine_init(stwuct phy_device *phydev, boow one_step)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	boow ptp_w4, base = phydev->mdio.addw == vsc8531->ts_base_addw;
	u8 eng_id = base ? 0 : 1;
	u32 vaw;

	ptp_w4 = vsc8531->ptp->wx_fiwtew == HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT;

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ANAWYZEW_MODE);
	/* Disabwe INGWESS and EGWESS so engine eng_id can be weconfiguwed */
	vaw &= ~(PTP_ANAWYZEW_MODE_EGW_ENA(BIT(eng_id)) |
		 PTP_ANAWYZEW_MODE_INGW_ENA(BIT(eng_id)));
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ANAWYZEW_MODE,
			     vaw);

	if (vsc8531->ptp->wx_fiwtew == HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) {
		vsc85xx_eth1_next_comp(phydev, INGWESS,
				       ANA_ETH1_NTX_PWOT_PTP_OAM, ETH_P_1588);
		vsc85xx_eth1_next_comp(phydev, EGWESS,
				       ANA_ETH1_NTX_PWOT_PTP_OAM, ETH_P_1588);
	} ewse {
		vsc85xx_eth1_next_comp(phydev, INGWESS,
				       ANA_ETH1_NTX_PWOT_IP_UDP_ACH_1,
				       ETH_P_IP);
		vsc85xx_eth1_next_comp(phydev, EGWESS,
				       ANA_ETH1_NTX_PWOT_IP_UDP_ACH_1,
				       ETH_P_IP);
		/* Headew wength of IPv[4/6] + UDP */
		vsc85xx_ip1_next_comp(phydev, INGWESS,
				      ANA_ETH1_NTX_PWOT_PTP_OAM, 28);
		vsc85xx_ip1_next_comp(phydev, EGWESS,
				      ANA_ETH1_NTX_PWOT_PTP_OAM, 28);
	}

	vsc85xx_eth1_conf(phydev, INGWESS,
			  vsc8531->ptp->wx_fiwtew != HWTSTAMP_FIWTEW_NONE);
	vsc85xx_ip1_conf(phydev, INGWESS,
			 ptp_w4 && vsc8531->ptp->wx_fiwtew != HWTSTAMP_FIWTEW_NONE);
	vsc85xx_ptp_conf(phydev, INGWESS, one_step,
			 vsc8531->ptp->wx_fiwtew != HWTSTAMP_FIWTEW_NONE);

	vsc85xx_eth1_conf(phydev, EGWESS,
			  vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF);
	vsc85xx_ip1_conf(phydev, EGWESS,
			 ptp_w4 && vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF);
	vsc85xx_ptp_conf(phydev, EGWESS, one_step,
			 vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF);

	vaw &= ~PTP_ANAWYZEW_MODE_EGW_ENA(BIT(eng_id));
	if (vsc8531->ptp->tx_type != HWTSTAMP_TX_OFF)
		vaw |= PTP_ANAWYZEW_MODE_EGW_ENA(BIT(eng_id));

	vaw &= ~PTP_ANAWYZEW_MODE_INGW_ENA(BIT(eng_id));
	if (vsc8531->ptp->wx_fiwtew != HWTSTAMP_FIWTEW_NONE)
		vaw |= PTP_ANAWYZEW_MODE_INGW_ENA(BIT(eng_id));

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ANAWYZEW_MODE,
			     vaw);

	wetuwn 0;
}

void vsc85xx_wink_change_notify(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	mutex_wock(&pwiv->ts_wock);
	vsc85xx_ts_set_watencies(phydev);
	mutex_unwock(&pwiv->ts_wock);
}

static void vsc85xx_ts_weset_fifo(stwuct phy_device *phydev)
{
	u32 vaw;

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_TS_FIFO_CTWW);
	vaw |= PTP_EGW_TS_FIFO_WESET;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TS_FIFO_CTWW,
			     vaw);

	vaw &= ~PTP_EGW_TS_FIFO_WESET;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TS_FIFO_CTWW,
			     vaw);
}

static int vsc85xx_hwtstamp(stwuct mii_timestampew *mii_ts,
			    stwuct kewnew_hwtstamp_config *cfg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct vsc8531_pwivate *vsc8531 =
		containew_of(mii_ts, stwuct vsc8531_pwivate, mii_ts);
	stwuct phy_device *phydev = vsc8531->ptp->phydev;
	boow one_step = fawse;
	u32 vaw;

	switch (cfg->tx_type) {
	case HWTSTAMP_TX_ONESTEP_SYNC:
		one_step = twue;
		bweak;
	case HWTSTAMP_TX_ON:
		bweak;
	case HWTSTAMP_TX_OFF:
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	vsc8531->ptp->tx_type = cfg->tx_type;

	switch (cfg->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		/* ETH->IP->UDP->PTP */
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		/* ETH->PTP */
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	vsc8531->ptp->wx_fiwtew = cfg->wx_fiwtew;

	mutex_wock(&vsc8531->ts_wock);

	__skb_queue_puwge(&vsc8531->ptp->tx_queue);
	__skb_queue_head_init(&vsc8531->ptp->tx_queue);

	/* Disabwe pwedictow whiwe configuwing the 1588 bwock */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_PWEDICTOW);
	vaw &= ~PTP_INGW_PWEDICTOW_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_PWEDICTOW,
			     vaw);
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_PWEDICTOW);
	vaw &= ~PTP_EGW_PWEDICTOW_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_PWEDICTOW,
			     vaw);

	/* Bypass egwess ow ingwess bwocks if timestamping isn't used */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_IFACE_CTWW);
	vaw &= ~(PTP_IFACE_CTWW_EGW_BYPASS | PTP_IFACE_CTWW_INGW_BYPASS);
	if (vsc8531->ptp->tx_type == HWTSTAMP_TX_OFF)
		vaw |= PTP_IFACE_CTWW_EGW_BYPASS;
	if (vsc8531->ptp->wx_fiwtew == HWTSTAMP_FIWTEW_NONE)
		vaw |= PTP_IFACE_CTWW_INGW_BYPASS;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_IFACE_CTWW, vaw);

	/* Wesetting FIFO so that it's empty aftew weconfiguwation */
	vsc85xx_ts_weset_fifo(phydev);

	vsc85xx_ts_engine_init(phydev, one_step);

	/* We-enabwe pwedictows now */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_PWEDICTOW);
	vaw |= PTP_INGW_PWEDICTOW_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_PWEDICTOW,
			     vaw);
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_PWEDICTOW);
	vaw |= PTP_EGW_PWEDICTOW_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_PWEDICTOW,
			     vaw);

	vsc8531->ptp->configuwed = 1;
	mutex_unwock(&vsc8531->ts_wock);

	wetuwn 0;
}

static int vsc85xx_ts_info(stwuct mii_timestampew *mii_ts,
			   stwuct ethtoow_ts_info *info)
{
	stwuct vsc8531_pwivate *vsc8531 =
		containew_of(mii_ts, stwuct vsc8531_pwivate, mii_ts);

	info->phc_index = ptp_cwock_index(vsc8531->ptp->ptp_cwock);
	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON) |
		(1 << HWTSTAMP_TX_ONESTEP_SYNC);
	info->wx_fiwtews =
		(1 << HWTSTAMP_FIWTEW_NONE) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT) |
		(1 << HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT);

	wetuwn 0;
}

static void vsc85xx_txtstamp(stwuct mii_timestampew *mii_ts,
			     stwuct sk_buff *skb, int type)
{
	stwuct vsc8531_pwivate *vsc8531 =
		containew_of(mii_ts, stwuct vsc8531_pwivate, mii_ts);

	if (!vsc8531->ptp->configuwed)
		wetuwn;

	if (vsc8531->ptp->tx_type == HWTSTAMP_TX_OFF) {
		kfwee_skb(skb);
		wetuwn;
	}

	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

	mutex_wock(&vsc8531->ts_wock);
	__skb_queue_taiw(&vsc8531->ptp->tx_queue, skb);
	mutex_unwock(&vsc8531->ts_wock);
}

static boow vsc85xx_wxtstamp(stwuct mii_timestampew *mii_ts,
			     stwuct sk_buff *skb, int type)
{
	stwuct vsc8531_pwivate *vsc8531 =
		containew_of(mii_ts, stwuct vsc8531_pwivate, mii_ts);
	stwuct skb_shawed_hwtstamps *shhwtstamps = NUWW;
	stwuct vsc85xx_ptphdw *ptphdw;
	stwuct timespec64 ts;
	unsigned wong ns;

	if (!vsc8531->ptp->configuwed)
		wetuwn fawse;

	if (vsc8531->ptp->wx_fiwtew == HWTSTAMP_FIWTEW_NONE ||
	    type == PTP_CWASS_NONE)
		wetuwn fawse;

	vsc85xx_gettime(&vsc8531->ptp->caps, &ts);

	ptphdw = get_ptp_headew_wx(skb, vsc8531->ptp->wx_fiwtew);
	if (!ptphdw)
		wetuwn fawse;

	shhwtstamps = skb_hwtstamps(skb);
	memset(shhwtstamps, 0, sizeof(stwuct skb_shawed_hwtstamps));

	ns = ntohw(ptphdw->wswvd2);

	/* nsec is in wesewved fiewd */
	if (ts.tv_nsec < ns)
		ts.tv_sec--;

	shhwtstamps->hwtstamp = ktime_set(ts.tv_sec, ns);
	netif_wx(skb);

	wetuwn twue;
}

static const stwuct ptp_cwock_info vsc85xx_cwk_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "VSC85xx timew",
	.max_adj	= S32_MAX,
	.n_awawm	= 0,
	.n_pins		= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= 0,
	.pps		= 0,
	.adjtime        = &vsc85xx_adjtime,
	.adjfine	= &vsc85xx_adjfine,
	.gettime64	= &vsc85xx_gettime,
	.settime64	= &vsc85xx_settime,
};

static stwuct vsc8531_pwivate *vsc8584_base_pwiv(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;

	if (vsc8531->ts_base_addw != phydev->mdio.addw) {
		stwuct mdio_device *dev;

		dev = phydev->mdio.bus->mdio_map[vsc8531->ts_base_addw];
		phydev = containew_of(dev, stwuct phy_device, mdio);

		wetuwn phydev->pwiv;
	}

	wetuwn vsc8531;
}

static boow vsc8584_is_1588_input_cwk_configuwed(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = vsc8584_base_pwiv(phydev);

	wetuwn vsc8531->input_cwk_init;
}

static void vsc8584_set_input_cwk_configuwed(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = vsc8584_base_pwiv(phydev);

	vsc8531->input_cwk_init = twue;
}

static int __vsc8584_init_ptp(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;
	static const u32 wtc_seq_e[] = { 0, 400000, 0, 0, 0 };
	static const u8  wtc_seq_a[] = { 8, 6, 5, 4, 2 };
	u32 vaw;

	if (!vsc8584_is_1588_input_cwk_configuwed(phydev)) {
		phy_wock_mdio_bus(phydev);

		/* 1588_DIFF_INPUT_CWK configuwation: Use an extewnaw cwock fow
		 * the WTC, as pew 3.13.29 in the VSC8584 datasheet.
		 */
		phy_ts_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
				  MSCC_PHY_PAGE_1588);
		phy_ts_base_wwite(phydev, 29, 0x7ae0);
		phy_ts_base_wwite(phydev, 30, 0xb71c);
		phy_ts_base_wwite(phydev, MSCC_EXT_PAGE_ACCESS,
				  MSCC_PHY_PAGE_STANDAWD);

		phy_unwock_mdio_bus(phydev);

		vsc8584_set_input_cwk_configuwed(phydev);
	}

	/* Disabwe pwedictow befowe configuwing the 1588 bwock */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_PWEDICTOW);
	vaw &= ~PTP_INGW_PWEDICTOW_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_PWEDICTOW,
			     vaw);
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_PWEDICTOW);
	vaw &= ~PTP_EGW_PWEDICTOW_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_PWEDICTOW,
			     vaw);

	/* By defauwt, the intewnaw cwock of fixed wate 250MHz is used */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW);
	vaw &= ~PTP_WTC_CTWW_CWK_SEW_MASK;
	vaw |= PTP_WTC_CTWW_CWK_SEW_INTEWNAW_250;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_CTWW, vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_SEQUENCE);
	vaw &= ~PTP_WTC_SEQUENCE_A_MASK;
	vaw |= PTP_WTC_SEQUENCE_A(wtc_seq_a[PHC_CWK_250MHZ]);
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_SEQUENCE, vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_SEQ);
	vaw &= ~(PTP_WTC_SEQ_EWW_MASK | PTP_WTC_SEQ_ADD_SUB);
	if (wtc_seq_e[PHC_CWK_250MHZ])
		vaw |= PTP_WTC_SEQ_ADD_SUB;
	vaw |= PTP_WTC_SEQ_EWW(wtc_seq_e[PHC_CWK_250MHZ]);
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_SEQ, vaw);

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_WTC_1PPS_WIDTH_ADJ,
			     PPS_WIDTH_ADJ);

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_DEWAY_FIFO,
			     IS_ENABWED(CONFIG_MACSEC) ?
			     PTP_INGW_DEWAY_FIFO_DEPTH_MACSEC :
			     PTP_INGW_DEWAY_FIFO_DEPTH_DEFAUWT);

	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_DEWAY_FIFO,
			     IS_ENABWED(CONFIG_MACSEC) ?
			     PTP_EGW_DEWAY_FIFO_DEPTH_MACSEC :
			     PTP_EGW_DEWAY_FIFO_DEPTH_DEFAUWT);

	/* Enabwe n-phase sampwew fow Vipew Wev-B */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ACCUW_CFG_STATUS);
	vaw &= ~(PTP_ACCUW_PPS_OUT_BYPASS | PTP_ACCUW_PPS_IN_BYPASS |
		 PTP_ACCUW_EGW_SOF_BYPASS | PTP_ACCUW_INGW_SOF_BYPASS |
		 PTP_ACCUW_WOAD_SAVE_BYPASS);
	vaw |= PTP_ACCUW_PPS_OUT_CAWIB_EWW | PTP_ACCUW_PPS_OUT_CAWIB_DONE |
	       PTP_ACCUW_PPS_IN_CAWIB_EWW | PTP_ACCUW_PPS_IN_CAWIB_DONE |
	       PTP_ACCUW_EGW_SOF_CAWIB_EWW | PTP_ACCUW_EGW_SOF_CAWIB_DONE |
	       PTP_ACCUW_INGW_SOF_CAWIB_EWW | PTP_ACCUW_INGW_SOF_CAWIB_DONE |
	       PTP_ACCUW_WOAD_SAVE_CAWIB_EWW | PTP_ACCUW_WOAD_SAVE_CAWIB_DONE;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ACCUW_CFG_STATUS,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ACCUW_CFG_STATUS);
	vaw |= PTP_ACCUW_CAWIB_TWIGG;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ACCUW_CFG_STATUS,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ACCUW_CFG_STATUS);
	vaw &= ~PTP_ACCUW_CAWIB_TWIGG;
	vaw |= PTP_ACCUW_PPS_OUT_CAWIB_EWW | PTP_ACCUW_PPS_OUT_CAWIB_DONE |
	       PTP_ACCUW_PPS_IN_CAWIB_EWW | PTP_ACCUW_PPS_IN_CAWIB_DONE |
	       PTP_ACCUW_EGW_SOF_CAWIB_EWW | PTP_ACCUW_EGW_SOF_CAWIB_DONE |
	       PTP_ACCUW_INGW_SOF_CAWIB_EWW | PTP_ACCUW_INGW_SOF_CAWIB_DONE |
	       PTP_ACCUW_WOAD_SAVE_CAWIB_EWW | PTP_ACCUW_WOAD_SAVE_CAWIB_DONE;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ACCUW_CFG_STATUS,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ACCUW_CFG_STATUS);
	vaw |= PTP_ACCUW_CAWIB_TWIGG;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ACCUW_CFG_STATUS,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ACCUW_CFG_STATUS);
	vaw &= ~PTP_ACCUW_CAWIB_TWIGG;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ACCUW_CFG_STATUS,
			     vaw);

	/* Do not access FIFO via SI */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_TSTAMP_FIFO_SI);
	vaw &= ~PTP_TSTAMP_FIFO_SI_EN;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_TSTAMP_FIFO_SI,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_WEWWITEW_CTWW);
	vaw &= ~PTP_INGW_WEWWITEW_WEDUCE_PWEAMBWE;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_WEWWITEW_CTWW,
			     vaw);
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_WEWWITEW_CTWW);
	vaw &= ~PTP_EGW_WEWWITEW_WEDUCE_PWEAMBWE;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_WEWWITEW_CTWW,
			     vaw);

	/* Put the fwag that indicates the fwame has been modified to bit 7 */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_WEWWITEW_CTWW);
	vaw |= PTP_INGW_WEWWITEW_FWAG_BIT_OFF(7) | PTP_INGW_WEWWITEW_FWAG_VAW;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_WEWWITEW_CTWW,
			     vaw);
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_WEWWITEW_CTWW);
	vaw |= PTP_EGW_WEWWITEW_FWAG_BIT_OFF(7);
	vaw &= ~PTP_EGW_WEWWITEW_FWAG_VAW;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_WEWWITEW_CTWW,
			     vaw);

	/* 30bit mode fow WX timestamp, onwy the nanoseconds awe kept in
	 * wesewved fiewd.
	 */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_INGW_TSP_CTWW);
	vaw |= PHY_PTP_INGW_TSP_CTWW_FWACT_NS;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_INGW_TSP_CTWW,
			     vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TSP_CTWW);
	vaw |= PHY_PTP_EGW_TSP_CTWW_FWACT_NS;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TSP_CTWW, vaw);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_SEWIAW_TOD_IFACE);
	vaw |= PTP_SEWIAW_TOD_IFACE_WS_AUTO_CWW;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_SEWIAW_TOD_IFACE,
			     vaw);

	vsc85xx_ts_fsb_init(phydev);

	/* Set the Egwess timestamp FIFO configuwation and status wegistew */
	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_EGW_TS_FIFO_CTWW);
	vaw &= ~(PTP_EGW_TS_FIFO_SIG_BYTES_MASK | PTP_EGW_TS_FIFO_THWESH_MASK);
	/* 16 bytes fow the signatuwe, 10 fow the timestamp in the TS FIFO */
	vaw |= PTP_EGW_TS_FIFO_SIG_BYTES(16) | PTP_EGW_TS_FIFO_THWESH(7);
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_EGW_TS_FIFO_CTWW,
			     vaw);

	vsc85xx_ts_weset_fifo(phydev);

	vaw = PTP_IFACE_CTWW_CWK_ENA;
	if (!IS_ENABWED(CONFIG_MACSEC))
		vaw |= PTP_IFACE_CTWW_GMII_PWOT;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_IFACE_CTWW, vaw);

	vsc85xx_ts_set_watencies(phydev);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_VEWSION_CODE);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_IFACE_CTWW);
	vaw |= PTP_IFACE_CTWW_EGW_BYPASS;
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_IFACE_CTWW, vaw);

	vsc85xx_ts_disabwe_fwows(phydev, EGWESS);
	vsc85xx_ts_disabwe_fwows(phydev, INGWESS);

	vaw = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				  MSCC_PHY_PTP_ANAWYZEW_MODE);
	/* Disabwe INGWESS and EGWESS so engine eng_id can be weconfiguwed */
	vaw &= ~(PTP_ANAWYZEW_MODE_EGW_ENA_MASK |
		 PTP_ANAWYZEW_MODE_INGW_ENA_MASK |
		 PTP_ANA_INGW_ENCAP_FWOW_MODE_MASK |
		 PTP_ANA_EGW_ENCAP_FWOW_MODE_MASK);
	/* Stwict matching in fwow (packets shouwd match fwows fwom the same
	 * index in aww enabwed compawatows (except PTP)).
	 */
	vaw |= PTP_ANA_SPWIT_ENCAP_FWOW | PTP_ANA_INGW_ENCAP_FWOW_MODE(0x7) |
	       PTP_ANA_EGW_ENCAP_FWOW_MODE(0x7);
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_PTP_ANAWYZEW_MODE,
			     vaw);

	/* Initiawized fow ingwess and egwess fwows:
	 * - The Ethewnet compawatow.
	 * - The IP compawatow.
	 * - The PTP compawatow.
	 */
	vsc85xx_eth_cmp1_init(phydev, INGWESS);
	vsc85xx_ip_cmp1_init(phydev, INGWESS);
	vsc85xx_ptp_cmp_init(phydev, INGWESS);
	vsc85xx_eth_cmp1_init(phydev, EGWESS);
	vsc85xx_ip_cmp1_init(phydev, EGWESS);
	vsc85xx_ptp_cmp_init(phydev, EGWESS);

	vsc85xx_ts_eth_cmp1_sig(phydev);

	vsc8531->mii_ts.wxtstamp = vsc85xx_wxtstamp;
	vsc8531->mii_ts.txtstamp = vsc85xx_txtstamp;
	vsc8531->mii_ts.hwtstamp = vsc85xx_hwtstamp;
	vsc8531->mii_ts.ts_info  = vsc85xx_ts_info;
	phydev->mii_ts = &vsc8531->mii_ts;

	memcpy(&vsc8531->ptp->caps, &vsc85xx_cwk_caps, sizeof(vsc85xx_cwk_caps));

	vsc8531->ptp->ptp_cwock = ptp_cwock_wegistew(&vsc8531->ptp->caps,
						     &phydev->mdio.dev);
	wetuwn PTW_EWW_OW_ZEWO(vsc8531->ptp->ptp_cwock);
}

void vsc8584_config_ts_intw(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;

	mutex_wock(&pwiv->ts_wock);
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW, MSCC_PHY_1588_VSC85XX_INT_MASK,
			     VSC85XX_1588_INT_MASK_MASK);
	mutex_unwock(&pwiv->ts_wock);
}

int vsc8584_ptp_init(stwuct phy_device *phydev)
{
	switch (phydev->phy_id & phydev->dwv->phy_id_mask) {
	case PHY_ID_VSC8572:
	case PHY_ID_VSC8574:
	case PHY_ID_VSC8575:
	case PHY_ID_VSC8582:
	case PHY_ID_VSC8584:
		wetuwn __vsc8584_init_ptp(phydev);
	}

	wetuwn 0;
}

iwqwetuwn_t vsc8584_handwe_ts_intewwupt(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *pwiv = phydev->pwiv;
	int wc;

	mutex_wock(&pwiv->ts_wock);
	wc = vsc85xx_ts_wead_csw(phydev, PWOCESSOW,
				 MSCC_PHY_1588_VSC85XX_INT_STATUS);
	/* Ack the PTP intewwupt */
	vsc85xx_ts_wwite_csw(phydev, PWOCESSOW,
			     MSCC_PHY_1588_VSC85XX_INT_STATUS, wc);

	if (!(wc & VSC85XX_1588_INT_MASK_MASK)) {
		mutex_unwock(&pwiv->ts_wock);
		wetuwn IWQ_NONE;
	}

	if (wc & VSC85XX_1588_INT_FIFO_ADD) {
		vsc85xx_get_tx_ts(pwiv->ptp);
	} ewse if (wc & VSC85XX_1588_INT_FIFO_OVEWFWOW) {
		__skb_queue_puwge(&pwiv->ptp->tx_queue);
		vsc85xx_ts_weset_fifo(phydev);
	}

	mutex_unwock(&pwiv->ts_wock);
	wetuwn IWQ_HANDWED;
}

int vsc8584_ptp_pwobe(stwuct phy_device *phydev)
{
	stwuct vsc8531_pwivate *vsc8531 = phydev->pwiv;

	vsc8531->ptp = devm_kzawwoc(&phydev->mdio.dev, sizeof(*vsc8531->ptp),
				    GFP_KEWNEW);
	if (!vsc8531->ptp)
		wetuwn -ENOMEM;

	mutex_init(&vsc8531->phc_wock);
	mutex_init(&vsc8531->ts_wock);

	/* Wetwieve the shawed woad/save GPIO. Wequest it as non excwusive as
	 * the same GPIO can be wequested by aww the PHYs of the same package.
	 * This GPIO must be used with the gpio_wock taken (the wock is shawed
	 * between aww PHYs).
	 */
	vsc8531->woad_save = devm_gpiod_get_optionaw(&phydev->mdio.dev, "woad-save",
						     GPIOD_FWAGS_BIT_NONEXCWUSIVE |
						     GPIOD_OUT_WOW);
	if (IS_EWW(vsc8531->woad_save)) {
		phydev_eww(phydev, "Can't get woad-save GPIO (%wd)\n",
			   PTW_EWW(vsc8531->woad_save));
		wetuwn PTW_EWW(vsc8531->woad_save);
	}

	vsc8531->ptp->phydev = phydev;

	wetuwn 0;
}

int vsc8584_ptp_pwobe_once(stwuct phy_device *phydev)
{
	stwuct vsc85xx_shawed_pwivate *shawed =
		(stwuct vsc85xx_shawed_pwivate *)phydev->shawed->pwiv;

	/* Initiawize shawed GPIO wock */
	mutex_init(&shawed->gpio_wock);

	wetuwn 0;
}
