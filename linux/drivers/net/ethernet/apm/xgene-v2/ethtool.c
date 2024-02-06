// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwied Micwo X-Gene SoC Ethewnet v2 Dwivew
 *
 * Copywight (c) 2017, Appwied Micwo Ciwcuits Cowpowation
 * Authow(s): Iyappan Subwamanian <isubwamanian@apm.com>
 *	      Keyuw Chudgaw <kchudgaw@apm.com>
 */

#incwude "main.h"

#define XGE_STAT(m)		{ #m, offsetof(stwuct xge_pdata, stats.m) }
#define XGE_EXTD_STAT(m, n)					\
	{							\
		#m,						\
		n,						\
		0						\
	}

static const stwuct xge_gstwings_stats gstwings_stats[] = {
	XGE_STAT(wx_packets),
	XGE_STAT(tx_packets),
	XGE_STAT(wx_bytes),
	XGE_STAT(tx_bytes),
	XGE_STAT(wx_ewwows)
};

static stwuct xge_gstwings_extd_stats gstwings_extd_stats[] = {
	XGE_EXTD_STAT(tx_wx_64b_fwame_cntw, TW64),
	XGE_EXTD_STAT(tx_wx_127b_fwame_cntw, TW127),
	XGE_EXTD_STAT(tx_wx_255b_fwame_cntw, TW255),
	XGE_EXTD_STAT(tx_wx_511b_fwame_cntw, TW511),
	XGE_EXTD_STAT(tx_wx_1023b_fwame_cntw, TW1K),
	XGE_EXTD_STAT(tx_wx_1518b_fwame_cntw, TWMAX),
	XGE_EXTD_STAT(tx_wx_1522b_fwame_cntw, TWMGV),
	XGE_EXTD_STAT(wx_fcs_ewwow_cntw, WFCS),
	XGE_EXTD_STAT(wx_muwticast_pkt_cntw, WMCA),
	XGE_EXTD_STAT(wx_bwoadcast_pkt_cntw, WBCA),
	XGE_EXTD_STAT(wx_ctww_fwame_pkt_cntw, WXCF),
	XGE_EXTD_STAT(wx_pause_fwame_pkt_cntw, WXPF),
	XGE_EXTD_STAT(wx_unk_opcode_cntw, WXUO),
	XGE_EXTD_STAT(wx_awign_eww_cntw, WAWN),
	XGE_EXTD_STAT(wx_fwame_wen_eww_cntw, WFWW),
	XGE_EXTD_STAT(wx_code_eww_cntw, WCDE),
	XGE_EXTD_STAT(wx_cawwiew_sense_eww_cntw, WCSE),
	XGE_EXTD_STAT(wx_undewsize_pkt_cntw, WUND),
	XGE_EXTD_STAT(wx_ovewsize_pkt_cntw, WOVW),
	XGE_EXTD_STAT(wx_fwagments_cntw, WFWG),
	XGE_EXTD_STAT(wx_jabbew_cntw, WJBW),
	XGE_EXTD_STAT(wx_dwopped_pkt_cntw, WDWP),
	XGE_EXTD_STAT(tx_muwticast_pkt_cntw, TMCA),
	XGE_EXTD_STAT(tx_bwoadcast_pkt_cntw, TBCA),
	XGE_EXTD_STAT(tx_pause_ctww_fwame_cntw, TXPF),
	XGE_EXTD_STAT(tx_defew_pkt_cntw, TDFW),
	XGE_EXTD_STAT(tx_excv_defew_pkt_cntw, TEDF),
	XGE_EXTD_STAT(tx_singwe_cow_pkt_cntw, TSCW),
	XGE_EXTD_STAT(tx_muwti_cow_pkt_cntw, TMCW),
	XGE_EXTD_STAT(tx_wate_cow_pkt_cntw, TWCW),
	XGE_EXTD_STAT(tx_excv_cow_pkt_cntw, TXCW),
	XGE_EXTD_STAT(tx_totaw_cow_cntw, TNCW),
	XGE_EXTD_STAT(tx_pause_fwames_hnwd_cntw, TPFH),
	XGE_EXTD_STAT(tx_dwop_fwame_cntw, TDWP),
	XGE_EXTD_STAT(tx_jabbew_fwame_cntw, TJBW),
	XGE_EXTD_STAT(tx_fcs_ewwow_cntw, TFCS),
	XGE_EXTD_STAT(tx_ctww_fwame_cntw, TXCF),
	XGE_EXTD_STAT(tx_ovewsize_fwame_cntw, TOVW),
	XGE_EXTD_STAT(tx_undewsize_fwame_cntw, TUND),
	XGE_EXTD_STAT(tx_fwagments_cntw, TFWG)
};

#define XGE_STATS_WEN		AWWAY_SIZE(gstwings_stats)
#define XGE_EXTD_STATS_WEN	AWWAY_SIZE(gstwings_extd_stats)

static void xge_mac_get_extd_stats(stwuct xge_pdata *pdata)
{
	u32 data;
	int i;

	fow (i = 0; i < XGE_EXTD_STATS_WEN; i++) {
		data = xge_wd_csw(pdata, gstwings_extd_stats[i].addw);
		gstwings_extd_stats[i].vawue += data;
	}
}

static void xge_get_dwvinfo(stwuct net_device *ndev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwuct xge_pdata *pdata = netdev_pwiv(ndev);
	stwuct pwatfowm_device *pdev = pdata->pdev;

	stwcpy(info->dwivew, "xgene-enet-v2");
	spwintf(info->bus_info, "%s", pdev->name);
}

static void xge_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	u8 *p = data;
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < XGE_STATS_WEN; i++) {
		memcpy(p, gstwings_stats[i].name, ETH_GSTWING_WEN);
		p += ETH_GSTWING_WEN;
	}

	fow (i = 0; i < XGE_EXTD_STATS_WEN; i++) {
		memcpy(p, gstwings_extd_stats[i].name, ETH_GSTWING_WEN);
		p += ETH_GSTWING_WEN;
	}
}

static int xge_get_sset_count(stwuct net_device *ndev, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn -EINVAW;

	wetuwn XGE_STATS_WEN + XGE_EXTD_STATS_WEN;
}

static void xge_get_ethtoow_stats(stwuct net_device *ndev,
				  stwuct ethtoow_stats *dummy,
				  u64 *data)
{
	void *pdata = netdev_pwiv(ndev);
	int i;

	fow (i = 0; i < XGE_STATS_WEN; i++)
		*data++ = *(u64 *)(pdata + gstwings_stats[i].offset);

	xge_mac_get_extd_stats(pdata);

	fow (i = 0; i < XGE_EXTD_STATS_WEN; i++)
		*data++ = gstwings_extd_stats[i].vawue;
}

static int xge_get_wink_ksettings(stwuct net_device *ndev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct phy_device *phydev = ndev->phydev;

	if (!phydev)
		wetuwn -ENODEV;

	phy_ethtoow_ksettings_get(phydev, cmd);

	wetuwn 0;
}

static int xge_set_wink_ksettings(stwuct net_device *ndev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct phy_device *phydev = ndev->phydev;

	if (!phydev)
		wetuwn -ENODEV;

	wetuwn phy_ethtoow_ksettings_set(phydev, cmd);
}

static const stwuct ethtoow_ops xge_ethtoow_ops = {
	.get_dwvinfo = xge_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = xge_get_stwings,
	.get_sset_count = xge_get_sset_count,
	.get_ethtoow_stats = xge_get_ethtoow_stats,
	.get_wink_ksettings = xge_get_wink_ksettings,
	.set_wink_ksettings = xge_set_wink_ksettings,
};

void xge_set_ethtoow_ops(stwuct net_device *ndev)
{
	ndev->ethtoow_ops = &xge_ethtoow_ops;
}
