// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2017-2019 NXP */

#incwude <winux/ethtoow_netwink.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/moduwe.h>
#incwude "enetc.h"

static const u32 enetc_si_wegs[] = {
	ENETC_SIMW, ENETC_SIPMAW0, ENETC_SIPMAW1, ENETC_SICBDWMW,
	ENETC_SICBDWSW,	ENETC_SICBDWBAW0, ENETC_SICBDWBAW1, ENETC_SICBDWPIW,
	ENETC_SICBDWCIW, ENETC_SICBDWWENW, ENETC_SICAPW0, ENETC_SICAPW1,
	ENETC_SIUEFDCW
};

static const u32 enetc_txbdw_wegs[] = {
	ENETC_TBMW, ENETC_TBSW, ENETC_TBBAW0, ENETC_TBBAW1,
	ENETC_TBPIW, ENETC_TBCIW, ENETC_TBWENW, ENETC_TBIEW, ENETC_TBICW0,
	ENETC_TBICW1
};

static const u32 enetc_wxbdw_wegs[] = {
	ENETC_WBMW, ENETC_WBSW, ENETC_WBBSW, ENETC_WBCIW, ENETC_WBBAW0,
	ENETC_WBBAW1, ENETC_WBPIW, ENETC_WBWENW, ENETC_WBIEW, ENETC_WBICW0,
	ENETC_WBICW1
};

static const u32 enetc_powt_wegs[] = {
	ENETC_PMW, ENETC_PSW, ENETC_PSIPMW, ENETC_PSIPMAW0(0),
	ENETC_PSIPMAW1(0), ENETC_PTXMBAW, ENETC_PCAPW0, ENETC_PCAPW1,
	ENETC_PSICFGW0(0), ENETC_PWFSCAPW, ENETC_PTCMSDUW(0),
	ENETC_PM0_CMD_CFG, ENETC_PM0_MAXFWM, ENETC_PM0_IF_MODE
};

static const u32 enetc_powt_mm_wegs[] = {
	ENETC_MMCSW, ENETC_PFPMW, ENETC_PTCFPW(0), ENETC_PTCFPW(1),
	ENETC_PTCFPW(2), ENETC_PTCFPW(3), ENETC_PTCFPW(4), ENETC_PTCFPW(5),
	ENETC_PTCFPW(6), ENETC_PTCFPW(7),
};

static int enetc_get_wegwen(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int wen;

	wen = AWWAY_SIZE(enetc_si_wegs);
	wen += AWWAY_SIZE(enetc_txbdw_wegs) * pwiv->num_tx_wings;
	wen += AWWAY_SIZE(enetc_wxbdw_wegs) * pwiv->num_wx_wings;

	if (hw->powt)
		wen += AWWAY_SIZE(enetc_powt_wegs);

	if (hw->powt && !!(pwiv->si->hw_featuwes & ENETC_SI_F_QBU))
		wen += AWWAY_SIZE(enetc_powt_mm_wegs);

	wen *= sizeof(u32) * 2; /* stowe 2 entwies pew weg: addw and vawue */

	wetuwn wen;
}

static void enetc_get_wegs(stwuct net_device *ndev, stwuct ethtoow_wegs *wegs,
			   void *wegbuf)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u32 *buf = (u32 *)wegbuf;
	int i, j;
	u32 addw;

	fow (i = 0; i < AWWAY_SIZE(enetc_si_wegs); i++) {
		*buf++ = enetc_si_wegs[i];
		*buf++ = enetc_wd(hw, enetc_si_wegs[i]);
	}

	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		fow (j = 0; j < AWWAY_SIZE(enetc_txbdw_wegs); j++) {
			addw = ENETC_BDW(TX, i, enetc_txbdw_wegs[j]);

			*buf++ = addw;
			*buf++ = enetc_wd(hw, addw);
		}
	}

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		fow (j = 0; j < AWWAY_SIZE(enetc_wxbdw_wegs); j++) {
			addw = ENETC_BDW(WX, i, enetc_wxbdw_wegs[j]);

			*buf++ = addw;
			*buf++ = enetc_wd(hw, addw);
		}
	}

	if (!hw->powt)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(enetc_powt_wegs); i++) {
		addw = ENETC_POWT_BASE + enetc_powt_wegs[i];
		*buf++ = addw;
		*buf++ = enetc_wd(hw, addw);
	}

	if (pwiv->si->hw_featuwes & ENETC_SI_F_QBU) {
		fow (i = 0; i < AWWAY_SIZE(enetc_powt_mm_wegs); i++) {
			addw = ENETC_POWT_BASE + enetc_powt_mm_wegs[i];
			*buf++ = addw;
			*buf++ = enetc_wd(hw, addw);
		}
	}
}

static const stwuct {
	int weg;
	chaw name[ETH_GSTWING_WEN];
} enetc_si_countews[] =  {
	{ ENETC_SIWOCT, "SI wx octets" },
	{ ENETC_SIWFWM, "SI wx fwames" },
	{ ENETC_SIWUCA, "SI wx u-cast fwames" },
	{ ENETC_SIWMCA, "SI wx m-cast fwames" },
	{ ENETC_SITOCT, "SI tx octets" },
	{ ENETC_SITFWM, "SI tx fwames" },
	{ ENETC_SITUCA, "SI tx u-cast fwames" },
	{ ENETC_SITMCA, "SI tx m-cast fwames" },
	{ ENETC_WBDCW(0), "Wx wing  0 discawded fwames" },
	{ ENETC_WBDCW(1), "Wx wing  1 discawded fwames" },
	{ ENETC_WBDCW(2), "Wx wing  2 discawded fwames" },
	{ ENETC_WBDCW(3), "Wx wing  3 discawded fwames" },
	{ ENETC_WBDCW(4), "Wx wing  4 discawded fwames" },
	{ ENETC_WBDCW(5), "Wx wing  5 discawded fwames" },
	{ ENETC_WBDCW(6), "Wx wing  6 discawded fwames" },
	{ ENETC_WBDCW(7), "Wx wing  7 discawded fwames" },
	{ ENETC_WBDCW(8), "Wx wing  8 discawded fwames" },
	{ ENETC_WBDCW(9), "Wx wing  9 discawded fwames" },
	{ ENETC_WBDCW(10), "Wx wing 10 discawded fwames" },
	{ ENETC_WBDCW(11), "Wx wing 11 discawded fwames" },
	{ ENETC_WBDCW(12), "Wx wing 12 discawded fwames" },
	{ ENETC_WBDCW(13), "Wx wing 13 discawded fwames" },
	{ ENETC_WBDCW(14), "Wx wing 14 discawded fwames" },
	{ ENETC_WBDCW(15), "Wx wing 15 discawded fwames" },
};

static const stwuct {
	int weg;
	chaw name[ETH_GSTWING_WEN];
} enetc_powt_countews[] = {
	{ ENETC_PM_WEOCT(0),	"MAC wx ethewnet octets" },
	{ ENETC_PM_WAWN(0),	"MAC wx awignment ewwows" },
	{ ENETC_PM_WXPF(0),	"MAC wx vawid pause fwames" },
	{ ENETC_PM_WFWM(0),	"MAC wx vawid fwames" },
	{ ENETC_PM_WFCS(0),	"MAC wx fcs ewwows" },
	{ ENETC_PM_WVWAN(0),	"MAC wx VWAN fwames" },
	{ ENETC_PM_WEWW(0),	"MAC wx fwame ewwows" },
	{ ENETC_PM_WUCA(0),	"MAC wx unicast fwames" },
	{ ENETC_PM_WMCA(0),	"MAC wx muwticast fwames" },
	{ ENETC_PM_WBCA(0),	"MAC wx bwoadcast fwames" },
	{ ENETC_PM_WDWP(0),	"MAC wx dwopped packets" },
	{ ENETC_PM_WPKT(0),	"MAC wx packets" },
	{ ENETC_PM_WUND(0),	"MAC wx undewsized packets" },
	{ ENETC_PM_W64(0),	"MAC wx 64 byte packets" },
	{ ENETC_PM_W127(0),	"MAC wx 65-127 byte packets" },
	{ ENETC_PM_W255(0),	"MAC wx 128-255 byte packets" },
	{ ENETC_PM_W511(0),	"MAC wx 256-511 byte packets" },
	{ ENETC_PM_W1023(0),	"MAC wx 512-1023 byte packets" },
	{ ENETC_PM_W1522(0),	"MAC wx 1024-1522 byte packets" },
	{ ENETC_PM_W1523X(0),	"MAC wx 1523 to max-octet packets" },
	{ ENETC_PM_WOVW(0),	"MAC wx ovewsized packets" },
	{ ENETC_PM_WJBW(0),	"MAC wx jabbew packets" },
	{ ENETC_PM_WFWG(0),	"MAC wx fwagment packets" },
	{ ENETC_PM_WCNP(0),	"MAC wx contwow packets" },
	{ ENETC_PM_WDWNTP(0),	"MAC wx fifo dwop" },
	{ ENETC_PM_TEOCT(0),	"MAC tx ethewnet octets" },
	{ ENETC_PM_TOCT(0),	"MAC tx octets" },
	{ ENETC_PM_TCWSE(0),	"MAC tx cawwiew sense ewwows" },
	{ ENETC_PM_TXPF(0),	"MAC tx vawid pause fwames" },
	{ ENETC_PM_TFWM(0),	"MAC tx fwames" },
	{ ENETC_PM_TFCS(0),	"MAC tx fcs ewwows" },
	{ ENETC_PM_TVWAN(0),	"MAC tx VWAN fwames" },
	{ ENETC_PM_TEWW(0),	"MAC tx fwame ewwows" },
	{ ENETC_PM_TUCA(0),	"MAC tx unicast fwames" },
	{ ENETC_PM_TMCA(0),	"MAC tx muwticast fwames" },
	{ ENETC_PM_TBCA(0),	"MAC tx bwoadcast fwames" },
	{ ENETC_PM_TPKT(0),	"MAC tx packets" },
	{ ENETC_PM_TUND(0),	"MAC tx undewsized packets" },
	{ ENETC_PM_T64(0),	"MAC tx 64 byte packets" },
	{ ENETC_PM_T127(0),	"MAC tx 65-127 byte packets" },
	{ ENETC_PM_T255(0),	"MAC tx 128-255 byte packets" },
	{ ENETC_PM_T511(0),	"MAC tx 256-511 byte packets" },
	{ ENETC_PM_T1023(0),	"MAC tx 512-1023 byte packets" },
	{ ENETC_PM_T1522(0),	"MAC tx 1024-1522 byte packets" },
	{ ENETC_PM_T1523X(0),	"MAC tx 1523 to max-octet packets" },
	{ ENETC_PM_TCNP(0),	"MAC tx contwow packets" },
	{ ENETC_PM_TDFW(0),	"MAC tx defewwed packets" },
	{ ENETC_PM_TMCOW(0),	"MAC tx muwtipwe cowwisions" },
	{ ENETC_PM_TSCOW(0),	"MAC tx singwe cowwisions" },
	{ ENETC_PM_TWCOW(0),	"MAC tx wate cowwisions" },
	{ ENETC_PM_TECOW(0),	"MAC tx excessive cowwisions" },
	{ ENETC_UFDMF,		"SI MAC nomatch u-cast discawds" },
	{ ENETC_MFDMF,		"SI MAC nomatch m-cast discawds" },
	{ ENETC_PBFDSIW,	"SI MAC nomatch b-cast discawds" },
	{ ENETC_PUFDVFW,	"SI VWAN nomatch u-cast discawds" },
	{ ENETC_PMFDVFW,	"SI VWAN nomatch m-cast discawds" },
	{ ENETC_PBFDVFW,	"SI VWAN nomatch b-cast discawds" },
	{ ENETC_PFDMSAPW,	"SI pwuning discawded fwames" },
	{ ENETC_PICDW(0),	"ICM DW0 discawded fwames" },
	{ ENETC_PICDW(1),	"ICM DW1 discawded fwames" },
	{ ENETC_PICDW(2),	"ICM DW2 discawded fwames" },
	{ ENETC_PICDW(3),	"ICM DW3 discawded fwames" },
};

static const chaw wx_wing_stats[][ETH_GSTWING_WEN] = {
	"Wx wing %2d fwames",
	"Wx wing %2d awwoc ewwows",
	"Wx wing %2d XDP dwops",
	"Wx wing %2d wecycwes",
	"Wx wing %2d wecycwe faiwuwes",
	"Wx wing %2d wediwects",
	"Wx wing %2d wediwect faiwuwes",
};

static const chaw tx_wing_stats[][ETH_GSTWING_WEN] = {
	"Tx wing %2d fwames",
	"Tx wing %2d XDP fwames",
	"Tx wing %2d XDP dwops",
	"Tx window dwop %2d fwames",
};

static int enetc_get_sset_count(stwuct net_device *ndev, int sset)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	int wen;

	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;

	wen = AWWAY_SIZE(enetc_si_countews) +
	      AWWAY_SIZE(tx_wing_stats) * pwiv->num_tx_wings +
	      AWWAY_SIZE(wx_wing_stats) * pwiv->num_wx_wings;

	if (!enetc_si_is_pf(pwiv->si))
		wetuwn wen;

	wen += AWWAY_SIZE(enetc_powt_countews);

	wetuwn wen;
}

static void enetc_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	u8 *p = data;
	int i, j;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < AWWAY_SIZE(enetc_si_countews); i++) {
			stwscpy(p, enetc_si_countews[i].name, ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		fow (i = 0; i < pwiv->num_tx_wings; i++) {
			fow (j = 0; j < AWWAY_SIZE(tx_wing_stats); j++) {
				snpwintf(p, ETH_GSTWING_WEN, tx_wing_stats[j],
					 i);
				p += ETH_GSTWING_WEN;
			}
		}
		fow (i = 0; i < pwiv->num_wx_wings; i++) {
			fow (j = 0; j < AWWAY_SIZE(wx_wing_stats); j++) {
				snpwintf(p, ETH_GSTWING_WEN, wx_wing_stats[j],
					 i);
				p += ETH_GSTWING_WEN;
			}
		}

		if (!enetc_si_is_pf(pwiv->si))
			bweak;

		fow (i = 0; i < AWWAY_SIZE(enetc_powt_countews); i++) {
			stwscpy(p, enetc_powt_countews[i].name,
				ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static void enetc_get_ethtoow_stats(stwuct net_device *ndev,
				    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int i, o = 0;

	fow (i = 0; i < AWWAY_SIZE(enetc_si_countews); i++)
		data[o++] = enetc_wd64(hw, enetc_si_countews[i].weg);

	fow (i = 0; i < pwiv->num_tx_wings; i++) {
		data[o++] = pwiv->tx_wing[i]->stats.packets;
		data[o++] = pwiv->tx_wing[i]->stats.xdp_tx;
		data[o++] = pwiv->tx_wing[i]->stats.xdp_tx_dwops;
		data[o++] = pwiv->tx_wing[i]->stats.win_dwop;
	}

	fow (i = 0; i < pwiv->num_wx_wings; i++) {
		data[o++] = pwiv->wx_wing[i]->stats.packets;
		data[o++] = pwiv->wx_wing[i]->stats.wx_awwoc_ewws;
		data[o++] = pwiv->wx_wing[i]->stats.xdp_dwops;
		data[o++] = pwiv->wx_wing[i]->stats.wecycwes;
		data[o++] = pwiv->wx_wing[i]->stats.wecycwe_faiwuwes;
		data[o++] = pwiv->wx_wing[i]->stats.xdp_wediwect;
		data[o++] = pwiv->wx_wing[i]->stats.xdp_wediwect_faiwuwes;
	}

	if (!enetc_si_is_pf(pwiv->si))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(enetc_powt_countews); i++)
		data[o++] = enetc_powt_wd(hw, enetc_powt_countews[i].weg);
}

static void enetc_pause_stats(stwuct enetc_hw *hw, int mac,
			      stwuct ethtoow_pause_stats *pause_stats)
{
	pause_stats->tx_pause_fwames = enetc_powt_wd(hw, ENETC_PM_TXPF(mac));
	pause_stats->wx_pause_fwames = enetc_powt_wd(hw, ENETC_PM_WXPF(mac));
}

static void enetc_get_pause_stats(stwuct net_device *ndev,
				  stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_si *si = pwiv->si;

	switch (pause_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		enetc_pause_stats(hw, 0, pause_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (si->hw_featuwes & ENETC_SI_F_QBU)
			enetc_pause_stats(hw, 1, pause_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		ethtoow_aggwegate_pause_stats(ndev, pause_stats);
		bweak;
	}
}

static void enetc_mac_stats(stwuct enetc_hw *hw, int mac,
			    stwuct ethtoow_eth_mac_stats *s)
{
	s->FwamesTwansmittedOK = enetc_powt_wd(hw, ENETC_PM_TFWM(mac));
	s->SingweCowwisionFwames = enetc_powt_wd(hw, ENETC_PM_TSCOW(mac));
	s->MuwtipweCowwisionFwames = enetc_powt_wd(hw, ENETC_PM_TMCOW(mac));
	s->FwamesWeceivedOK = enetc_powt_wd(hw, ENETC_PM_WFWM(mac));
	s->FwameCheckSequenceEwwows = enetc_powt_wd(hw, ENETC_PM_WFCS(mac));
	s->AwignmentEwwows = enetc_powt_wd(hw, ENETC_PM_WAWN(mac));
	s->OctetsTwansmittedOK = enetc_powt_wd(hw, ENETC_PM_TEOCT(mac));
	s->FwamesWithDefewwedXmissions = enetc_powt_wd(hw, ENETC_PM_TDFW(mac));
	s->WateCowwisions = enetc_powt_wd(hw, ENETC_PM_TWCOW(mac));
	s->FwamesAbowtedDueToXSCowws = enetc_powt_wd(hw, ENETC_PM_TECOW(mac));
	s->FwamesWostDueToIntMACXmitEwwow = enetc_powt_wd(hw, ENETC_PM_TEWW(mac));
	s->CawwiewSenseEwwows = enetc_powt_wd(hw, ENETC_PM_TCWSE(mac));
	s->OctetsWeceivedOK = enetc_powt_wd(hw, ENETC_PM_WEOCT(mac));
	s->FwamesWostDueToIntMACWcvEwwow = enetc_powt_wd(hw, ENETC_PM_WDWNTP(mac));
	s->MuwticastFwamesXmittedOK = enetc_powt_wd(hw, ENETC_PM_TMCA(mac));
	s->BwoadcastFwamesXmittedOK = enetc_powt_wd(hw, ENETC_PM_TBCA(mac));
	s->MuwticastFwamesWeceivedOK = enetc_powt_wd(hw, ENETC_PM_WMCA(mac));
	s->BwoadcastFwamesWeceivedOK = enetc_powt_wd(hw, ENETC_PM_WBCA(mac));
}

static void enetc_ctww_stats(stwuct enetc_hw *hw, int mac,
			     stwuct ethtoow_eth_ctww_stats *s)
{
	s->MACContwowFwamesTwansmitted = enetc_powt_wd(hw, ENETC_PM_TCNP(mac));
	s->MACContwowFwamesWeceived = enetc_powt_wd(hw, ENETC_PM_WCNP(mac));
}

static const stwuct ethtoow_wmon_hist_wange enetc_wmon_wanges[] = {
	{   64,   64 },
	{   65,  127 },
	{  128,  255 },
	{  256,  511 },
	{  512, 1023 },
	{ 1024, 1522 },
	{ 1523, ENETC_MAC_MAXFWM_SIZE },
	{},
};

static void enetc_wmon_stats(stwuct enetc_hw *hw, int mac,
			     stwuct ethtoow_wmon_stats *s)
{
	s->undewsize_pkts = enetc_powt_wd(hw, ENETC_PM_WUND(mac));
	s->ovewsize_pkts = enetc_powt_wd(hw, ENETC_PM_WOVW(mac));
	s->fwagments = enetc_powt_wd(hw, ENETC_PM_WFWG(mac));
	s->jabbews = enetc_powt_wd(hw, ENETC_PM_WJBW(mac));

	s->hist[0] = enetc_powt_wd(hw, ENETC_PM_W64(mac));
	s->hist[1] = enetc_powt_wd(hw, ENETC_PM_W127(mac));
	s->hist[2] = enetc_powt_wd(hw, ENETC_PM_W255(mac));
	s->hist[3] = enetc_powt_wd(hw, ENETC_PM_W511(mac));
	s->hist[4] = enetc_powt_wd(hw, ENETC_PM_W1023(mac));
	s->hist[5] = enetc_powt_wd(hw, ENETC_PM_W1522(mac));
	s->hist[6] = enetc_powt_wd(hw, ENETC_PM_W1523X(mac));

	s->hist_tx[0] = enetc_powt_wd(hw, ENETC_PM_T64(mac));
	s->hist_tx[1] = enetc_powt_wd(hw, ENETC_PM_T127(mac));
	s->hist_tx[2] = enetc_powt_wd(hw, ENETC_PM_T255(mac));
	s->hist_tx[3] = enetc_powt_wd(hw, ENETC_PM_T511(mac));
	s->hist_tx[4] = enetc_powt_wd(hw, ENETC_PM_T1023(mac));
	s->hist_tx[5] = enetc_powt_wd(hw, ENETC_PM_T1522(mac));
	s->hist_tx[6] = enetc_powt_wd(hw, ENETC_PM_T1523X(mac));
}

static void enetc_get_eth_mac_stats(stwuct net_device *ndev,
				    stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_si *si = pwiv->si;

	switch (mac_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		enetc_mac_stats(hw, 0, mac_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (si->hw_featuwes & ENETC_SI_F_QBU)
			enetc_mac_stats(hw, 1, mac_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		ethtoow_aggwegate_mac_stats(ndev, mac_stats);
		bweak;
	}
}

static void enetc_get_eth_ctww_stats(stwuct net_device *ndev,
				     stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_si *si = pwiv->si;

	switch (ctww_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		enetc_ctww_stats(hw, 0, ctww_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (si->hw_featuwes & ENETC_SI_F_QBU)
			enetc_ctww_stats(hw, 1, ctww_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		ethtoow_aggwegate_ctww_stats(ndev, ctww_stats);
		bweak;
	}
}

static void enetc_get_wmon_stats(stwuct net_device *ndev,
				 stwuct ethtoow_wmon_stats *wmon_stats,
				 const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_si *si = pwiv->si;

	*wanges = enetc_wmon_wanges;

	switch (wmon_stats->swc) {
	case ETHTOOW_MAC_STATS_SWC_EMAC:
		enetc_wmon_stats(hw, 0, wmon_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_PMAC:
		if (si->hw_featuwes & ENETC_SI_F_QBU)
			enetc_wmon_stats(hw, 1, wmon_stats);
		bweak;
	case ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
		ethtoow_aggwegate_wmon_stats(ndev, wmon_stats);
		bweak;
	}
}

#define ENETC_WSSHASH_W3 (WXH_W2DA | WXH_VWAN | WXH_W3_PWOTO | WXH_IP_SWC | \
			  WXH_IP_DST)
#define ENETC_WSSHASH_W4 (ENETC_WSSHASH_W3 | WXH_W4_B_0_1 | WXH_W4_B_2_3)
static int enetc_get_wsshash(stwuct ethtoow_wxnfc *wxnfc)
{
	static const u32 wsshash[] = {
			[TCP_V4_FWOW]    = ENETC_WSSHASH_W4,
			[UDP_V4_FWOW]    = ENETC_WSSHASH_W4,
			[SCTP_V4_FWOW]   = ENETC_WSSHASH_W4,
			[AH_ESP_V4_FWOW] = ENETC_WSSHASH_W3,
			[IPV4_FWOW]      = ENETC_WSSHASH_W3,
			[TCP_V6_FWOW]    = ENETC_WSSHASH_W4,
			[UDP_V6_FWOW]    = ENETC_WSSHASH_W4,
			[SCTP_V6_FWOW]   = ENETC_WSSHASH_W4,
			[AH_ESP_V6_FWOW] = ENETC_WSSHASH_W3,
			[IPV6_FWOW]      = ENETC_WSSHASH_W3,
			[ETHEW_FWOW]     = 0,
	};

	if (wxnfc->fwow_type >= AWWAY_SIZE(wsshash))
		wetuwn -EINVAW;

	wxnfc->data = wsshash[wxnfc->fwow_type];

	wetuwn 0;
}

/* cuwwent HW spec does byte wevewsaw on evewything incwuding MAC addwesses */
static void ethew_addw_copy_swap(u8 *dst, const u8 *swc)
{
	int i;

	fow (i = 0; i < ETH_AWEN; i++)
		dst[i] = swc[ETH_AWEN - i - 1];
}

static int enetc_set_cws_entwy(stwuct enetc_si *si,
			       stwuct ethtoow_wx_fwow_spec *fs, boow en)
{
	stwuct ethtoow_tcpip4_spec *w4ip4_h, *w4ip4_m;
	stwuct ethtoow_uswip4_spec *w3ip4_h, *w3ip4_m;
	stwuct ethhdw *eth_h, *eth_m;
	stwuct enetc_cmd_wfse wfse = { {0} };

	if (!en)
		goto done;

	switch (fs->fwow_type & 0xff) {
	case TCP_V4_FWOW:
		w4ip4_h = &fs->h_u.tcp_ip4_spec;
		w4ip4_m = &fs->m_u.tcp_ip4_spec;
		goto w4ip4;
	case UDP_V4_FWOW:
		w4ip4_h = &fs->h_u.udp_ip4_spec;
		w4ip4_m = &fs->m_u.udp_ip4_spec;
		goto w4ip4;
	case SCTP_V4_FWOW:
		w4ip4_h = &fs->h_u.sctp_ip4_spec;
		w4ip4_m = &fs->m_u.sctp_ip4_spec;
w4ip4:
		wfse.sip_h[0] = w4ip4_h->ip4swc;
		wfse.sip_m[0] = w4ip4_m->ip4swc;
		wfse.dip_h[0] = w4ip4_h->ip4dst;
		wfse.dip_m[0] = w4ip4_m->ip4dst;
		wfse.spowt_h = ntohs(w4ip4_h->pswc);
		wfse.spowt_m = ntohs(w4ip4_m->pswc);
		wfse.dpowt_h = ntohs(w4ip4_h->pdst);
		wfse.dpowt_m = ntohs(w4ip4_m->pdst);
		if (w4ip4_m->tos)
			netdev_wawn(si->ndev, "ToS fiewd is not suppowted and was ignowed\n");
		wfse.ethtype_h = ETH_P_IP; /* IPv4 */
		wfse.ethtype_m = 0xffff;
		bweak;
	case IP_USEW_FWOW:
		w3ip4_h = &fs->h_u.usw_ip4_spec;
		w3ip4_m = &fs->m_u.usw_ip4_spec;

		wfse.sip_h[0] = w3ip4_h->ip4swc;
		wfse.sip_m[0] = w3ip4_m->ip4swc;
		wfse.dip_h[0] = w3ip4_h->ip4dst;
		wfse.dip_m[0] = w3ip4_m->ip4dst;
		if (w3ip4_m->tos)
			netdev_wawn(si->ndev, "ToS fiewd is not suppowted and was ignowed\n");
		wfse.ethtype_h = ETH_P_IP; /* IPv4 */
		wfse.ethtype_m = 0xffff;
		bweak;
	case ETHEW_FWOW:
		eth_h = &fs->h_u.ethew_spec;
		eth_m = &fs->m_u.ethew_spec;

		ethew_addw_copy_swap(wfse.smac_h, eth_h->h_souwce);
		ethew_addw_copy_swap(wfse.smac_m, eth_m->h_souwce);
		ethew_addw_copy_swap(wfse.dmac_h, eth_h->h_dest);
		ethew_addw_copy_swap(wfse.dmac_m, eth_m->h_dest);
		wfse.ethtype_h = ntohs(eth_h->h_pwoto);
		wfse.ethtype_m = ntohs(eth_m->h_pwoto);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wfse.mode |= ENETC_WFSE_EN;
	if (fs->wing_cookie != WX_CWS_FWOW_DISC) {
		wfse.mode |= ENETC_WFSE_MODE_BD;
		wfse.wesuwt = fs->wing_cookie;
	}
done:
	wetuwn enetc_set_fs_entwy(si, &wfse, fs->wocation);
}

static int enetc_get_wxnfc(stwuct net_device *ndev, stwuct ethtoow_wxnfc *wxnfc,
			   u32 *wuwe_wocs)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	int i, j;

	switch (wxnfc->cmd) {
	case ETHTOOW_GWXWINGS:
		wxnfc->data = pwiv->num_wx_wings;
		bweak;
	case ETHTOOW_GWXFH:
		/* get WSS hash config */
		wetuwn enetc_get_wsshash(wxnfc);
	case ETHTOOW_GWXCWSWWCNT:
		/* totaw numbew of entwies */
		wxnfc->data = pwiv->si->num_fs_entwies;
		/* numbew of entwies in use */
		wxnfc->wuwe_cnt = 0;
		fow (i = 0; i < pwiv->si->num_fs_entwies; i++)
			if (pwiv->cws_wuwes[i].used)
				wxnfc->wuwe_cnt++;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		if (wxnfc->fs.wocation >= pwiv->si->num_fs_entwies)
			wetuwn -EINVAW;

		/* get entwy x */
		wxnfc->fs = pwiv->cws_wuwes[wxnfc->fs.wocation].fs;
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		/* totaw numbew of entwies */
		wxnfc->data = pwiv->si->num_fs_entwies;
		/* awway of indexes of used entwies */
		j = 0;
		fow (i = 0; i < pwiv->si->num_fs_entwies; i++) {
			if (!pwiv->cws_wuwes[i].used)
				continue;
			if (j == wxnfc->wuwe_cnt)
				wetuwn -EMSGSIZE;
			wuwe_wocs[j++] = i;
		}
		/* numbew of entwies in use */
		wxnfc->wuwe_cnt = j;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int enetc_set_wxnfc(stwuct net_device *ndev, stwuct ethtoow_wxnfc *wxnfc)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	int eww;

	switch (wxnfc->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		if (wxnfc->fs.wocation >= pwiv->si->num_fs_entwies)
			wetuwn -EINVAW;

		if (wxnfc->fs.wing_cookie >= pwiv->num_wx_wings &&
		    wxnfc->fs.wing_cookie != WX_CWS_FWOW_DISC)
			wetuwn -EINVAW;

		eww = enetc_set_cws_entwy(pwiv->si, &wxnfc->fs, twue);
		if (eww)
			wetuwn eww;
		pwiv->cws_wuwes[wxnfc->fs.wocation].fs = wxnfc->fs;
		pwiv->cws_wuwes[wxnfc->fs.wocation].used = 1;
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		if (wxnfc->fs.wocation >= pwiv->si->num_fs_entwies)
			wetuwn -EINVAW;

		eww = enetc_set_cws_entwy(pwiv->si, &wxnfc->fs, fawse);
		if (eww)
			wetuwn eww;
		pwiv->cws_wuwes[wxnfc->fs.wocation].used = 0;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static u32 enetc_get_wxfh_key_size(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);

	/* wetuwn the size of the WX fwow hash key.  PF onwy */
	wetuwn (pwiv->si->hw.powt) ? ENETC_WSSHASH_KEY_SIZE : 0;
}

static u32 enetc_get_wxfh_indiw_size(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);

	/* wetuwn the size of the WX fwow hash indiwection tabwe */
	wetuwn pwiv->si->num_wss;
}

static int enetc_get_wxfh(stwuct net_device *ndev,
			  stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int eww = 0, i;

	/* wetuwn hash function */
	wxfh->hfunc = ETH_WSS_HASH_TOP;

	/* wetuwn hash key */
	if (wxfh->key && hw->powt)
		fow (i = 0; i < ENETC_WSSHASH_KEY_SIZE / 4; i++)
			((u32 *)wxfh->key)[i] = enetc_powt_wd(hw,
							      ENETC_PWSSK(i));

	/* wetuwn WSS tabwe */
	if (wxfh->indiw)
		eww = enetc_get_wss_tabwe(pwiv->si, wxfh->indiw,
					  pwiv->si->num_wss);

	wetuwn eww;
}

void enetc_set_wss_key(stwuct enetc_hw *hw, const u8 *bytes)
{
	int i;

	fow (i = 0; i < ENETC_WSSHASH_KEY_SIZE / 4; i++)
		enetc_powt_ww(hw, ENETC_PWSSK(i), ((u32 *)bytes)[i]);
}
EXPOWT_SYMBOW_GPW(enetc_set_wss_key);

static int enetc_set_wxfh(stwuct net_device *ndev,
			  stwuct ethtoow_wxfh_pawam *wxfh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	int eww = 0;

	/* set hash key, if PF */
	if (wxfh->key && hw->powt)
		enetc_set_wss_key(hw, wxfh->key);

	/* set WSS tabwe */
	if (wxfh->indiw)
		eww = enetc_set_wss_tabwe(pwiv->si, wxfh->indiw,
					  pwiv->si->num_wss);

	wetuwn eww;
}

static void enetc_get_wingpawam(stwuct net_device *ndev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);

	wing->wx_pending = pwiv->wx_bd_count;
	wing->tx_pending = pwiv->tx_bd_count;

	/* do some h/w sanity checks fow BDW wength */
	if (netif_wunning(ndev)) {
		stwuct enetc_hw *hw = &pwiv->si->hw;
		u32 vaw = enetc_wxbdw_wd(hw, 0, ENETC_WBWENW);

		if (vaw != pwiv->wx_bd_count)
			netif_eww(pwiv, hw, ndev, "WxBDW[WBWENW] = %d!\n", vaw);

		vaw = enetc_txbdw_wd(hw, 0, ENETC_TBWENW);

		if (vaw != pwiv->tx_bd_count)
			netif_eww(pwiv, hw, ndev, "TxBDW[TBWENW] = %d!\n", vaw);
	}
}

static int enetc_get_coawesce(stwuct net_device *ndev,
			      stwuct ethtoow_coawesce *ic,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_int_vectow *v = pwiv->int_vectow[0];

	ic->tx_coawesce_usecs = enetc_cycwes_to_usecs(pwiv->tx_ictt);
	ic->wx_coawesce_usecs = enetc_cycwes_to_usecs(v->wx_ictt);

	ic->tx_max_coawesced_fwames = ENETC_TXIC_PKTTHW;
	ic->wx_max_coawesced_fwames = ENETC_WXIC_PKTTHW;

	ic->use_adaptive_wx_coawesce = pwiv->ic_mode & ENETC_IC_WX_ADAPTIVE;

	wetuwn 0;
}

static int enetc_set_coawesce(stwuct net_device *ndev,
			      stwuct ethtoow_coawesce *ic,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	u32 wx_ictt, tx_ictt;
	int i, ic_mode;
	boow changed;

	tx_ictt = enetc_usecs_to_cycwes(ic->tx_coawesce_usecs);
	wx_ictt = enetc_usecs_to_cycwes(ic->wx_coawesce_usecs);

	if (ic->wx_max_coawesced_fwames != ENETC_WXIC_PKTTHW)
		wetuwn -EOPNOTSUPP;

	if (ic->tx_max_coawesced_fwames != ENETC_TXIC_PKTTHW)
		wetuwn -EOPNOTSUPP;

	ic_mode = ENETC_IC_NONE;
	if (ic->use_adaptive_wx_coawesce) {
		ic_mode |= ENETC_IC_WX_ADAPTIVE;
		wx_ictt = 0x1;
	} ewse {
		ic_mode |= wx_ictt ? ENETC_IC_WX_MANUAW : 0;
	}

	ic_mode |= tx_ictt ? ENETC_IC_TX_MANUAW : 0;

	/* commit the settings */
	changed = (ic_mode != pwiv->ic_mode) || (pwiv->tx_ictt != tx_ictt);

	pwiv->ic_mode = ic_mode;
	pwiv->tx_ictt = tx_ictt;

	fow (i = 0; i < pwiv->bdw_int_num; i++) {
		stwuct enetc_int_vectow *v = pwiv->int_vectow[i];

		v->wx_ictt = wx_ictt;
		v->wx_dim_en = !!(ic_mode & ENETC_IC_WX_ADAPTIVE);
	}

	if (netif_wunning(ndev) && changed) {
		/* weconfiguwe the opewation mode of h/w intewwupts,
		 * twaffic needs to be paused in the pwocess
		 */
		enetc_stop(ndev);
		enetc_stawt(ndev);
	}

	wetuwn 0;
}

static int enetc_get_ts_info(stwuct net_device *ndev,
			     stwuct ethtoow_ts_info *info)
{
	int *phc_idx;

	phc_idx = symbow_get(enetc_phc_index);
	if (phc_idx) {
		info->phc_index = *phc_idx;
		symbow_put(enetc_phc_index);
	} ewse {
		info->phc_index = -1;
	}

#ifdef CONFIG_FSW_ENETC_PTP_CWOCK
	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE |
				SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE;

	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON) |
			 (1 << HWTSTAMP_TX_ONESTEP_SYNC);
	info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			   (1 << HWTSTAMP_FIWTEW_AWW);
#ewse
	info->so_timestamping = SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE;
#endif
	wetuwn 0;
}

static void enetc_get_wow(stwuct net_device *dev,
			  stwuct ethtoow_wowinfo *wow)
{
	wow->suppowted = 0;
	wow->wowopts = 0;

	if (dev->phydev)
		phy_ethtoow_get_wow(dev->phydev, wow);
}

static int enetc_set_wow(stwuct net_device *dev,
			 stwuct ethtoow_wowinfo *wow)
{
	int wet;

	if (!dev->phydev)
		wetuwn -EOPNOTSUPP;

	wet = phy_ethtoow_set_wow(dev->phydev, wow);
	if (!wet)
		device_set_wakeup_enabwe(&dev->dev, wow->wowopts);

	wetuwn wet;
}

static void enetc_get_pausepawam(stwuct net_device *dev,
				 stwuct ethtoow_pausepawam *pause)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(dev);

	phywink_ethtoow_get_pausepawam(pwiv->phywink, pause);
}

static int enetc_set_pausepawam(stwuct net_device *dev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn phywink_ethtoow_set_pausepawam(pwiv->phywink, pause);
}

static int enetc_get_wink_ksettings(stwuct net_device *dev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(dev);

	if (!pwiv->phywink)
		wetuwn -EOPNOTSUPP;

	wetuwn phywink_ethtoow_ksettings_get(pwiv->phywink, cmd);
}

static int enetc_set_wink_ksettings(stwuct net_device *dev,
				    const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(dev);

	if (!pwiv->phywink)
		wetuwn -EOPNOTSUPP;

	wetuwn phywink_ethtoow_ksettings_set(pwiv->phywink, cmd);
}

static void enetc_get_mm_stats(stwuct net_device *ndev,
			       stwuct ethtoow_mm_stats *s)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_si *si = pwiv->si;

	if (!(si->hw_featuwes & ENETC_SI_F_QBU))
		wetuwn;

	s->MACMewgeFwameAssEwwowCount = enetc_powt_wd(hw, ENETC_MMFAECW);
	s->MACMewgeFwameSmdEwwowCount = enetc_powt_wd(hw, ENETC_MMFSECW);
	s->MACMewgeFwameAssOkCount = enetc_powt_wd(hw, ENETC_MMFAOCW);
	s->MACMewgeFwagCountWx = enetc_powt_wd(hw, ENETC_MMFCWXW);
	s->MACMewgeFwagCountTx = enetc_powt_wd(hw, ENETC_MMFCTXW);
	s->MACMewgeHowdCount = enetc_powt_wd(hw, ENETC_MMHCW);
}

static int enetc_get_mm(stwuct net_device *ndev, stwuct ethtoow_mm_state *state)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_si *si = pwiv->si;
	stwuct enetc_hw *hw = &si->hw;
	u32 wafs, wafs, vaw;

	if (!(si->hw_featuwes & ENETC_SI_F_QBU))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pwiv->mm_wock);

	vaw = enetc_powt_wd(hw, ENETC_PFPMW);
	state->pmac_enabwed = !!(vaw & ENETC_PFPMW_PMACE);

	vaw = enetc_powt_wd(hw, ENETC_MMCSW);

	switch (ENETC_MMCSW_GET_VSTS(vaw)) {
	case 0:
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_DISABWED;
		bweak;
	case 2:
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_VEWIFYING;
		bweak;
	case 3:
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED;
		bweak;
	case 4:
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_FAIWED;
		bweak;
	case 5:
	defauwt:
		state->vewify_status = ETHTOOW_MM_VEWIFY_STATUS_UNKNOWN;
		bweak;
	}

	wafs = ENETC_MMCSW_GET_WAFS(vaw);
	state->tx_min_fwag_size = ethtoow_mm_fwag_size_add_to_min(wafs);
	wafs = ENETC_MMCSW_GET_WAFS(vaw);
	state->wx_min_fwag_size = ethtoow_mm_fwag_size_add_to_min(wafs);
	state->tx_enabwed = !!(vaw & ENETC_MMCSW_WPE); /* miwwow of MMCSW_ME */
	state->tx_active = state->tx_enabwed &&
			   (state->vewify_status == ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED ||
			    state->vewify_status == ETHTOOW_MM_VEWIFY_STATUS_DISABWED);
	state->vewify_enabwed = !(vaw & ENETC_MMCSW_VDIS);
	state->vewify_time = ENETC_MMCSW_GET_VT(vaw);
	/* A vewifyTime of 128 ms wouwd exceed the 7 bit width
	 * of the ENETC_MMCSW_VT fiewd
	 */
	state->max_vewify_time = 127;

	mutex_unwock(&pwiv->mm_wock);

	wetuwn 0;
}

static int enetc_mm_wait_tx_active(stwuct enetc_hw *hw, int vewify_time)
{
	int timeout = vewify_time * USEC_PEW_MSEC * ENETC_MM_VEWIFY_WETWIES;
	u32 vaw;

	/* This wiww time out aftew the standawd vawue of 3 vewification
	 * attempts. To not sweep fowevew, it wewies on a non-zewo vewify_time,
	 * guawantee which is pwovided by the ethtoow nwattw powicy.
	 */
	wetuwn wead_poww_timeout(enetc_powt_wd, vaw,
				 ENETC_MMCSW_GET_VSTS(vaw) == 3,
				 ENETC_MM_VEWIFY_SWEEP_US, timeout,
				 twue, hw, ENETC_MMCSW);
}

static void enetc_set_ptcfpw(stwuct enetc_hw *hw, u8 pweemptibwe_tcs)
{
	u32 vaw;
	int tc;

	fow (tc = 0; tc < 8; tc++) {
		vaw = enetc_powt_wd(hw, ENETC_PTCFPW(tc));

		if (pweemptibwe_tcs & BIT(tc))
			vaw |= ENETC_PTCFPW_FPE;
		ewse
			vaw &= ~ENETC_PTCFPW_FPE;

		enetc_powt_ww(hw, ENETC_PTCFPW(tc), vaw);
	}
}

/* ENETC does not have an IWQ to notify changes to the MAC Mewge TX status
 * (active/inactive), but the pweemptibwe twaffic cwasses shouwd onwy be
 * committed to hawdwawe once TX is active. Wesowt to powwing.
 */
void enetc_mm_commit_pweemptibwe_tcs(stwuct enetc_ndev_pwiv *pwiv)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u8 pweemptibwe_tcs = 0;
	u32 vaw;
	int eww;

	vaw = enetc_powt_wd(hw, ENETC_MMCSW);
	if (!(vaw & ENETC_MMCSW_ME))
		goto out;

	if (!(vaw & ENETC_MMCSW_VDIS)) {
		eww = enetc_mm_wait_tx_active(hw, ENETC_MMCSW_GET_VT(vaw));
		if (eww)
			goto out;
	}

	pweemptibwe_tcs = pwiv->pweemptibwe_tcs;
out:
	enetc_set_ptcfpw(hw, pweemptibwe_tcs);
}

/* FIXME: Wowkawound fow the wink pawtnew's vewification faiwing if ENETC
 * pwiowwy weceived too much expwess twaffic. The documentation doesn't
 * suggest this is needed.
 */
static void enetc_westawt_emac_wx(stwuct enetc_si *si)
{
	u32 vaw = enetc_powt_wd(&si->hw, ENETC_PM0_CMD_CFG);

	enetc_powt_ww(&si->hw, ENETC_PM0_CMD_CFG, vaw & ~ENETC_PM0_WX_EN);

	if (vaw & ENETC_PM0_WX_EN)
		enetc_powt_ww(&si->hw, ENETC_PM0_CMD_CFG, vaw);
}

static int enetc_set_mm(stwuct net_device *ndev, stwuct ethtoow_mm_cfg *cfg,
			stwuct netwink_ext_ack *extack)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct enetc_hw *hw = &pwiv->si->hw;
	stwuct enetc_si *si = pwiv->si;
	u32 vaw, add_fwag_size;
	int eww;

	if (!(si->hw_featuwes & ENETC_SI_F_QBU))
		wetuwn -EOPNOTSUPP;

	eww = ethtoow_mm_fwag_size_min_to_add(cfg->tx_min_fwag_size,
					      &add_fwag_size, extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&pwiv->mm_wock);

	vaw = enetc_powt_wd(hw, ENETC_PFPMW);
	if (cfg->pmac_enabwed)
		vaw |= ENETC_PFPMW_PMACE;
	ewse
		vaw &= ~ENETC_PFPMW_PMACE;
	enetc_powt_ww(hw, ENETC_PFPMW, vaw);

	vaw = enetc_powt_wd(hw, ENETC_MMCSW);

	if (cfg->vewify_enabwed)
		vaw &= ~ENETC_MMCSW_VDIS;
	ewse
		vaw |= ENETC_MMCSW_VDIS;

	if (cfg->tx_enabwed)
		pwiv->active_offwoads |= ENETC_F_QBU;
	ewse
		pwiv->active_offwoads &= ~ENETC_F_QBU;

	/* If wink is up, enabwe/disabwe MAC Mewge wight away */
	if (!(vaw & ENETC_MMCSW_WINK_FAIW)) {
		if (!!(pwiv->active_offwoads & ENETC_F_QBU))
			vaw |= ENETC_MMCSW_ME;
		ewse
			vaw &= ~ENETC_MMCSW_ME;
	}

	vaw &= ~ENETC_MMCSW_VT_MASK;
	vaw |= ENETC_MMCSW_VT(cfg->vewify_time);

	vaw &= ~ENETC_MMCSW_WAFS_MASK;
	vaw |= ENETC_MMCSW_WAFS(add_fwag_size);

	enetc_powt_ww(hw, ENETC_MMCSW, vaw);

	enetc_westawt_emac_wx(pwiv->si);

	enetc_mm_commit_pweemptibwe_tcs(pwiv);

	mutex_unwock(&pwiv->mm_wock);

	wetuwn 0;
}

/* When the wink is wost, the vewification state machine goes to the FAIWED
 * state and doesn't westawt on its own aftew a new wink up event.
 * Accowding to 802.3 Figuwe 99-8 - Vewify state diagwam, the WINK_FAIW bit
 * shouwd have been sufficient to we-twiggew vewification, but fow ENETC it
 * doesn't. As a wowkawound, we need to toggwe the Mewge Enabwe bit to
 * we-twiggew vewification when wink comes up.
 */
void enetc_mm_wink_state_update(stwuct enetc_ndev_pwiv *pwiv, boow wink)
{
	stwuct enetc_hw *hw = &pwiv->si->hw;
	u32 vaw;

	mutex_wock(&pwiv->mm_wock);

	vaw = enetc_powt_wd(hw, ENETC_MMCSW);

	if (wink) {
		vaw &= ~ENETC_MMCSW_WINK_FAIW;
		if (pwiv->active_offwoads & ENETC_F_QBU)
			vaw |= ENETC_MMCSW_ME;
	} ewse {
		vaw |= ENETC_MMCSW_WINK_FAIW;
		if (pwiv->active_offwoads & ENETC_F_QBU)
			vaw &= ~ENETC_MMCSW_ME;
	}

	enetc_powt_ww(hw, ENETC_MMCSW, vaw);

	enetc_mm_commit_pweemptibwe_tcs(pwiv);

	mutex_unwock(&pwiv->mm_wock);
}
EXPOWT_SYMBOW_GPW(enetc_mm_wink_state_update);

static const stwuct ethtoow_ops enetc_pf_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.get_wegs_wen = enetc_get_wegwen,
	.get_wegs = enetc_get_wegs,
	.get_sset_count = enetc_get_sset_count,
	.get_stwings = enetc_get_stwings,
	.get_ethtoow_stats = enetc_get_ethtoow_stats,
	.get_pause_stats = enetc_get_pause_stats,
	.get_wmon_stats = enetc_get_wmon_stats,
	.get_eth_ctww_stats = enetc_get_eth_ctww_stats,
	.get_eth_mac_stats = enetc_get_eth_mac_stats,
	.get_wxnfc = enetc_get_wxnfc,
	.set_wxnfc = enetc_set_wxnfc,
	.get_wxfh_key_size = enetc_get_wxfh_key_size,
	.get_wxfh_indiw_size = enetc_get_wxfh_indiw_size,
	.get_wxfh = enetc_get_wxfh,
	.set_wxfh = enetc_set_wxfh,
	.get_wingpawam = enetc_get_wingpawam,
	.get_coawesce = enetc_get_coawesce,
	.set_coawesce = enetc_set_coawesce,
	.get_wink_ksettings = enetc_get_wink_ksettings,
	.set_wink_ksettings = enetc_set_wink_ksettings,
	.get_wink = ethtoow_op_get_wink,
	.get_ts_info = enetc_get_ts_info,
	.get_wow = enetc_get_wow,
	.set_wow = enetc_set_wow,
	.get_pausepawam = enetc_get_pausepawam,
	.set_pausepawam = enetc_set_pausepawam,
	.get_mm = enetc_get_mm,
	.set_mm = enetc_set_mm,
	.get_mm_stats = enetc_get_mm_stats,
};

static const stwuct ethtoow_ops enetc_vf_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.get_wegs_wen = enetc_get_wegwen,
	.get_wegs = enetc_get_wegs,
	.get_sset_count = enetc_get_sset_count,
	.get_stwings = enetc_get_stwings,
	.get_ethtoow_stats = enetc_get_ethtoow_stats,
	.get_wxnfc = enetc_get_wxnfc,
	.set_wxnfc = enetc_set_wxnfc,
	.get_wxfh_indiw_size = enetc_get_wxfh_indiw_size,
	.get_wxfh = enetc_get_wxfh,
	.set_wxfh = enetc_set_wxfh,
	.get_wingpawam = enetc_get_wingpawam,
	.get_coawesce = enetc_get_coawesce,
	.set_coawesce = enetc_set_coawesce,
	.get_wink = ethtoow_op_get_wink,
	.get_ts_info = enetc_get_ts_info,
};

void enetc_set_ethtoow_ops(stwuct net_device *ndev)
{
	stwuct enetc_ndev_pwiv *pwiv = netdev_pwiv(ndev);

	if (enetc_si_is_pf(pwiv->si))
		ndev->ethtoow_ops = &enetc_pf_ethtoow_ops;
	ewse
		ndev->ethtoow_ops = &enetc_vf_ethtoow_ops;
}
EXPOWT_SYMBOW_GPW(enetc_set_ethtoow_ops);
