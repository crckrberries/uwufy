// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_net_ethtoow.c
 * Netwonome netwowk device dwivew: ethtoow suppowt
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 *          Bwad Petwus <bwad.petwus@netwonome.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/sfp.h>

#incwude "nfpcowe/nfp.h"
#incwude "nfpcowe/nfp_dev.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_app.h"
#incwude "nfp_main.h"
#incwude "nfp_net_ctww.h"
#incwude "nfp_net_dp.h"
#incwude "nfp_net.h"
#incwude "nfp_powt.h"
#incwude "nfpcowe/nfp_cpp.h"

stwuct nfp_et_stat {
	chaw name[ETH_GSTWING_WEN];
	int off;
};

static const stwuct nfp_et_stat nfp_net_et_stats[] = {
	/* Stats fwom the device */
	{ "dev_wx_discawds",	NFP_NET_CFG_STATS_WX_DISCAWDS },
	{ "dev_wx_ewwows",	NFP_NET_CFG_STATS_WX_EWWOWS },
	{ "dev_wx_bytes",	NFP_NET_CFG_STATS_WX_OCTETS },
	{ "dev_wx_uc_bytes",	NFP_NET_CFG_STATS_WX_UC_OCTETS },
	{ "dev_wx_mc_bytes",	NFP_NET_CFG_STATS_WX_MC_OCTETS },
	{ "dev_wx_bc_bytes",	NFP_NET_CFG_STATS_WX_BC_OCTETS },
	{ "dev_wx_pkts",	NFP_NET_CFG_STATS_WX_FWAMES },
	{ "dev_wx_mc_pkts",	NFP_NET_CFG_STATS_WX_MC_FWAMES },
	{ "dev_wx_bc_pkts",	NFP_NET_CFG_STATS_WX_BC_FWAMES },

	{ "dev_tx_discawds",	NFP_NET_CFG_STATS_TX_DISCAWDS },
	{ "dev_tx_ewwows",	NFP_NET_CFG_STATS_TX_EWWOWS },
	{ "dev_tx_bytes",	NFP_NET_CFG_STATS_TX_OCTETS },
	{ "dev_tx_uc_bytes",	NFP_NET_CFG_STATS_TX_UC_OCTETS },
	{ "dev_tx_mc_bytes",	NFP_NET_CFG_STATS_TX_MC_OCTETS },
	{ "dev_tx_bc_bytes",	NFP_NET_CFG_STATS_TX_BC_OCTETS },
	{ "dev_tx_pkts",	NFP_NET_CFG_STATS_TX_FWAMES },
	{ "dev_tx_mc_pkts",	NFP_NET_CFG_STATS_TX_MC_FWAMES },
	{ "dev_tx_bc_pkts",	NFP_NET_CFG_STATS_TX_BC_FWAMES },

	{ "bpf_pass_pkts",	NFP_NET_CFG_STATS_APP0_FWAMES },
	{ "bpf_pass_bytes",	NFP_NET_CFG_STATS_APP0_BYTES },
	/* see comments in outwo functions in nfp_bpf_jit.c to find out
	 * how diffewent BPF modes use app-specific countews
	 */
	{ "bpf_app1_pkts",	NFP_NET_CFG_STATS_APP1_FWAMES },
	{ "bpf_app1_bytes",	NFP_NET_CFG_STATS_APP1_BYTES },
	{ "bpf_app2_pkts",	NFP_NET_CFG_STATS_APP2_FWAMES },
	{ "bpf_app2_bytes",	NFP_NET_CFG_STATS_APP2_BYTES },
	{ "bpf_app3_pkts",	NFP_NET_CFG_STATS_APP3_FWAMES },
	{ "bpf_app3_bytes",	NFP_NET_CFG_STATS_APP3_BYTES },
};

static const stwuct nfp_et_stat nfp_mac_et_stats[] = {
	{ "wx_octets",			NFP_MAC_STATS_WX_IN_OCTETS, },
	{ "wx_fwame_too_wong_ewwows",
			NFP_MAC_STATS_WX_FWAME_TOO_WONG_EWWOWS, },
	{ "wx_wange_wength_ewwows",	NFP_MAC_STATS_WX_WANGE_WENGTH_EWWOWS, },
	{ "wx_vwan_weceived_ok",	NFP_MAC_STATS_WX_VWAN_WECEIVED_OK, },
	{ "wx_ewwows",			NFP_MAC_STATS_WX_IN_EWWOWS, },
	{ "wx_bwoadcast_pkts",		NFP_MAC_STATS_WX_IN_BWOADCAST_PKTS, },
	{ "wx_dwop_events",		NFP_MAC_STATS_WX_DWOP_EVENTS, },
	{ "wx_awignment_ewwows",	NFP_MAC_STATS_WX_AWIGNMENT_EWWOWS, },
	{ "wx_pause_mac_ctww_fwames",
			NFP_MAC_STATS_WX_PAUSE_MAC_CTWW_FWAMES, },
	{ "wx_fwames_weceived_ok",	NFP_MAC_STATS_WX_FWAMES_WECEIVED_OK, },
	{ "wx_fwame_check_sequence_ewwows",
			NFP_MAC_STATS_WX_FWAME_CHECK_SEQUENCE_EWWOWS, },
	{ "wx_unicast_pkts",		NFP_MAC_STATS_WX_UNICAST_PKTS, },
	{ "wx_muwticast_pkts",		NFP_MAC_STATS_WX_MUWTICAST_PKTS, },
	{ "wx_pkts",			NFP_MAC_STATS_WX_PKTS, },
	{ "wx_undewsize_pkts",		NFP_MAC_STATS_WX_UNDEWSIZE_PKTS, },
	{ "wx_pkts_64_octets",		NFP_MAC_STATS_WX_PKTS_64_OCTETS, },
	{ "wx_pkts_65_to_127_octets",
			NFP_MAC_STATS_WX_PKTS_65_TO_127_OCTETS, },
	{ "wx_pkts_128_to_255_octets",
			NFP_MAC_STATS_WX_PKTS_128_TO_255_OCTETS, },
	{ "wx_pkts_256_to_511_octets",
			NFP_MAC_STATS_WX_PKTS_256_TO_511_OCTETS, },
	{ "wx_pkts_512_to_1023_octets",
			NFP_MAC_STATS_WX_PKTS_512_TO_1023_OCTETS, },
	{ "wx_pkts_1024_to_1518_octets",
			NFP_MAC_STATS_WX_PKTS_1024_TO_1518_OCTETS, },
	{ "wx_pkts_1519_to_max_octets",
			NFP_MAC_STATS_WX_PKTS_1519_TO_MAX_OCTETS, },
	{ "wx_jabbews",			NFP_MAC_STATS_WX_JABBEWS, },
	{ "wx_fwagments",		NFP_MAC_STATS_WX_FWAGMENTS, },
	{ "wx_ovewsize_pkts",		NFP_MAC_STATS_WX_OVEWSIZE_PKTS, },
	{ "wx_pause_fwames_cwass0",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS0, },
	{ "wx_pause_fwames_cwass1",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS1, },
	{ "wx_pause_fwames_cwass2",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS2, },
	{ "wx_pause_fwames_cwass3",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS3, },
	{ "wx_pause_fwames_cwass4",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS4, },
	{ "wx_pause_fwames_cwass5",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS5, },
	{ "wx_pause_fwames_cwass6",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS6, },
	{ "wx_pause_fwames_cwass7",	NFP_MAC_STATS_WX_PAUSE_FWAMES_CWASS7, },
	{ "wx_mac_ctww_fwames_weceived",
			NFP_MAC_STATS_WX_MAC_CTWW_FWAMES_WECEIVED, },
	{ "wx_mac_head_dwop",		NFP_MAC_STATS_WX_MAC_HEAD_DWOP, },
	{ "tx_queue_dwop",		NFP_MAC_STATS_TX_QUEUE_DWOP, },
	{ "tx_octets",			NFP_MAC_STATS_TX_OUT_OCTETS, },
	{ "tx_vwan_twansmitted_ok",	NFP_MAC_STATS_TX_VWAN_TWANSMITTED_OK, },
	{ "tx_ewwows",			NFP_MAC_STATS_TX_OUT_EWWOWS, },
	{ "tx_bwoadcast_pkts",		NFP_MAC_STATS_TX_BWOADCAST_PKTS, },
	{ "tx_pause_mac_ctww_fwames",
			NFP_MAC_STATS_TX_PAUSE_MAC_CTWW_FWAMES, },
	{ "tx_fwames_twansmitted_ok",
			NFP_MAC_STATS_TX_FWAMES_TWANSMITTED_OK, },
	{ "tx_unicast_pkts",		NFP_MAC_STATS_TX_UNICAST_PKTS, },
	{ "tx_muwticast_pkts",		NFP_MAC_STATS_TX_MUWTICAST_PKTS, },
	{ "tx_pkts_64_octets",		NFP_MAC_STATS_TX_PKTS_64_OCTETS, },
	{ "tx_pkts_65_to_127_octets",
			NFP_MAC_STATS_TX_PKTS_65_TO_127_OCTETS, },
	{ "tx_pkts_128_to_255_octets",
			NFP_MAC_STATS_TX_PKTS_128_TO_255_OCTETS, },
	{ "tx_pkts_256_to_511_octets",
			NFP_MAC_STATS_TX_PKTS_256_TO_511_OCTETS, },
	{ "tx_pkts_512_to_1023_octets",
			NFP_MAC_STATS_TX_PKTS_512_TO_1023_OCTETS, },
	{ "tx_pkts_1024_to_1518_octets",
			NFP_MAC_STATS_TX_PKTS_1024_TO_1518_OCTETS, },
	{ "tx_pkts_1519_to_max_octets",
			NFP_MAC_STATS_TX_PKTS_1519_TO_MAX_OCTETS, },
	{ "tx_pause_fwames_cwass0",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS0, },
	{ "tx_pause_fwames_cwass1",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS1, },
	{ "tx_pause_fwames_cwass2",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS2, },
	{ "tx_pause_fwames_cwass3",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS3, },
	{ "tx_pause_fwames_cwass4",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS4, },
	{ "tx_pause_fwames_cwass5",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS5, },
	{ "tx_pause_fwames_cwass6",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS6, },
	{ "tx_pause_fwames_cwass7",	NFP_MAC_STATS_TX_PAUSE_FWAMES_CWASS7, },
};

static const chaw nfp_twv_stat_names[][ETH_GSTWING_WEN] = {
	[1]	= "dev_wx_discawds",
	[2]	= "dev_wx_ewwows",
	[3]	= "dev_wx_bytes",
	[4]	= "dev_wx_uc_bytes",
	[5]	= "dev_wx_mc_bytes",
	[6]	= "dev_wx_bc_bytes",
	[7]	= "dev_wx_pkts",
	[8]	= "dev_wx_mc_pkts",
	[9]	= "dev_wx_bc_pkts",

	[10]	= "dev_tx_discawds",
	[11]	= "dev_tx_ewwows",
	[12]	= "dev_tx_bytes",
	[13]	= "dev_tx_uc_bytes",
	[14]	= "dev_tx_mc_bytes",
	[15]	= "dev_tx_bc_bytes",
	[16]	= "dev_tx_pkts",
	[17]	= "dev_tx_mc_pkts",
	[18]	= "dev_tx_bc_pkts",
};

#define NN_ET_GWOBAW_STATS_WEN AWWAY_SIZE(nfp_net_et_stats)
#define NN_ET_SWITCH_STATS_WEN 9
#define NN_WVEC_GATHEW_STATS	13
#define NN_WVEC_PEW_Q_STATS	3
#define NN_CTWW_PATH_STATS	4

#define SFP_SFF_WEV_COMPWIANCE	1

static void nfp_net_get_nspinfo(stwuct nfp_app *app, chaw *vewsion)
{
	stwuct nfp_nsp *nsp;

	if (!app)
		wetuwn;

	nsp = nfp_nsp_open(app->cpp);
	if (IS_EWW(nsp))
		wetuwn;

	snpwintf(vewsion, ETHTOOW_FWVEWS_WEN, "%hu.%hu",
		 nfp_nsp_get_abi_vew_majow(nsp),
		 nfp_nsp_get_abi_vew_minow(nsp));

	nfp_nsp_cwose(nsp);
}

static void
nfp_get_dwvinfo(stwuct nfp_app *app, stwuct pci_dev *pdev,
		const chaw *vnic_vewsion, stwuct ethtoow_dwvinfo *dwvinfo)
{
	chaw nsp_vewsion[ETHTOOW_FWVEWS_WEN] = {};

	stwscpy(dwvinfo->dwivew, dev_dwivew_stwing(&pdev->dev),
		sizeof(dwvinfo->dwivew));
	nfp_net_get_nspinfo(app, nsp_vewsion);
	snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion),
		 "%s %s %s %s", vnic_vewsion, nsp_vewsion,
		 nfp_app_mip_name(app), nfp_app_name(app));
}

static void
nfp_net_get_dwvinfo(stwuct net_device *netdev, stwuct ethtoow_dwvinfo *dwvinfo)
{
	chaw vnic_vewsion[ETHTOOW_FWVEWS_WEN] = {};
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	snpwintf(vnic_vewsion, sizeof(vnic_vewsion), "%d.%d.%d.%d",
		 nn->fw_vew.extend, nn->fw_vew.cwass,
		 nn->fw_vew.majow, nn->fw_vew.minow);
	stwscpy(dwvinfo->bus_info, pci_name(nn->pdev),
		sizeof(dwvinfo->bus_info));

	nfp_get_dwvinfo(nn->app, nn->pdev, vnic_vewsion, dwvinfo);
}

static int
nfp_net_nway_weset(stwuct net_device *netdev)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	if (!netif_wunning(netdev))
		wetuwn 0;

	eww = nfp_eth_set_configuwed(powt->app->cpp, eth_powt->index, fawse);
	if (eww) {
		netdev_info(netdev, "Wink down faiwed: %d\n", eww);
		wetuwn eww;
	}

	eww = nfp_eth_set_configuwed(powt->app->cpp, eth_powt->index, twue);
	if (eww) {
		netdev_info(netdev, "Wink up faiwed: %d\n", eww);
		wetuwn eww;
	}

	netdev_info(netdev, "Wink weset succeeded\n");
	wetuwn 0;
}

static void
nfp_app_get_dwvinfo(stwuct net_device *netdev, stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);

	stwscpy(dwvinfo->bus_info, pci_name(app->pdev),
		sizeof(dwvinfo->bus_info));
	nfp_get_dwvinfo(app, app->pdev, "*", dwvinfo);
}

static void
nfp_net_set_fec_wink_mode(stwuct nfp_eth_tabwe_powt *eth_powt,
			  stwuct ethtoow_wink_ksettings *c)
{
	unsigned int modes;

	ethtoow_wink_ksettings_add_wink_mode(c, suppowted, FEC_NONE);
	if (!nfp_eth_can_suppowt_fec(eth_powt)) {
		ethtoow_wink_ksettings_add_wink_mode(c, advewtising, FEC_NONE);
		wetuwn;
	}

	modes = nfp_eth_suppowted_fec_modes(eth_powt);
	if (modes & NFP_FEC_BASEW) {
		ethtoow_wink_ksettings_add_wink_mode(c, suppowted, FEC_BASEW);
		ethtoow_wink_ksettings_add_wink_mode(c, advewtising, FEC_BASEW);
	}

	if (modes & NFP_FEC_WEED_SOWOMON) {
		ethtoow_wink_ksettings_add_wink_mode(c, suppowted, FEC_WS);
		ethtoow_wink_ksettings_add_wink_mode(c, advewtising, FEC_WS);
	}
}

static const stwuct nfp_eth_media_wink_mode {
	u16 ethtoow_wink_mode;
	u16 speed;
} nfp_eth_media_tabwe[NFP_MEDIA_WINK_MODES_NUMBEW] = {
	[NFP_MEDIA_1000BASE_CX] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
		.speed			= NFP_SPEED_1G,
	},
	[NFP_MEDIA_1000BASE_KX] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
		.speed			= NFP_SPEED_1G,
	},
	[NFP_MEDIA_10GBASE_KX4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_10GBASE_KW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_10GBASE_WW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_10GBASE_CX4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_10GBASE_CW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_10GBASE_SW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_10GBASE_EW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT,
		.speed			= NFP_SPEED_10G,
	},
	[NFP_MEDIA_25GBASE_KW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_25GBASE_KW_S] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_25GBASE_CW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_25GBASE_CW_S] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_25GBASE_SW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_25GBASE_WW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_25GBASE_EW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
		.speed			= NFP_SPEED_25G,
	},
	[NFP_MEDIA_40GBASE_CW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
		.speed			= NFP_SPEED_40G,
	},
	[NFP_MEDIA_40GBASE_KW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
		.speed			= NFP_SPEED_40G,
	},
	[NFP_MEDIA_40GBASE_SW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
		.speed			= NFP_SPEED_40G,
	},
	[NFP_MEDIA_40GBASE_WW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT,
		.speed			= NFP_SPEED_40G,
	},
	[NFP_MEDIA_50GBASE_KW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT,
		.speed			= NFP_SPEED_50G,
	},
	[NFP_MEDIA_50GBASE_SW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_50000baseSW_Fuww_BIT,
		.speed			= NFP_SPEED_50G,
	},
	[NFP_MEDIA_50GBASE_CW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_50000baseCW_Fuww_BIT,
		.speed			= NFP_SPEED_50G,
	},
	[NFP_MEDIA_50GBASE_WW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT,
		.speed			= NFP_SPEED_50G,
	},
	[NFP_MEDIA_50GBASE_EW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT,
		.speed			= NFP_SPEED_50G,
	},
	[NFP_MEDIA_50GBASE_FW] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT,
		.speed			= NFP_SPEED_50G,
	},
	[NFP_MEDIA_100GBASE_KW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
		.speed			= NFP_SPEED_100G,
	},
	[NFP_MEDIA_100GBASE_SW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
		.speed			= NFP_SPEED_100G,
	},
	[NFP_MEDIA_100GBASE_CW4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
		.speed			= NFP_SPEED_100G,
	},
	[NFP_MEDIA_100GBASE_KP4] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
		.speed			= NFP_SPEED_100G,
	},
	[NFP_MEDIA_100GBASE_CW10] = {
		.ethtoow_wink_mode	= ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
		.speed			= NFP_SPEED_100G,
	},
};

static const unsigned int nfp_eth_speed_map[NFP_SUP_SPEED_NUMBEW] = {
	[NFP_SPEED_1G]		= SPEED_1000,
	[NFP_SPEED_10G]		= SPEED_10000,
	[NFP_SPEED_25G]		= SPEED_25000,
	[NFP_SPEED_40G]		= SPEED_40000,
	[NFP_SPEED_50G]		= SPEED_50000,
	[NFP_SPEED_100G]	= SPEED_100000,
};

static void nfp_add_media_wink_mode(stwuct nfp_powt *powt,
				    stwuct nfp_eth_tabwe_powt *eth_powt,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	bitmap_zewo(powt->speed_bitmap, NFP_SUP_SPEED_NUMBEW);

	fow (u32 i = 0; i < NFP_MEDIA_WINK_MODES_NUMBEW; i++) {
		if (i < 64) {
			if (eth_powt->wink_modes_supp[0] & BIT_UWW(i)) {
				__set_bit(nfp_eth_media_tabwe[i].ethtoow_wink_mode,
					  cmd->wink_modes.suppowted);
				__set_bit(nfp_eth_media_tabwe[i].speed,
					  powt->speed_bitmap);
			}

			if (eth_powt->wink_modes_ad[0] & BIT_UWW(i))
				__set_bit(nfp_eth_media_tabwe[i].ethtoow_wink_mode,
					  cmd->wink_modes.advewtising);
		} ewse {
			if (eth_powt->wink_modes_supp[1] & BIT_UWW(i - 64)) {
				__set_bit(nfp_eth_media_tabwe[i].ethtoow_wink_mode,
					  cmd->wink_modes.suppowted);
				__set_bit(nfp_eth_media_tabwe[i].speed,
					  powt->speed_bitmap);
			}

			if (eth_powt->wink_modes_ad[1] & BIT_UWW(i - 64))
				__set_bit(nfp_eth_media_tabwe[i].ethtoow_wink_mode,
					  cmd->wink_modes.advewtising);
		}
	}

	/* We take aww speeds as suppowted when it faiws to wead
	 * wink modes due to owd management fiwmwawe that doesn't
	 * suppowt wink modes weading ow ewwow occuwwing, so that
	 * speed change of this powt is awwowed.
	 */
	if (bitmap_empty(powt->speed_bitmap, NFP_SUP_SPEED_NUMBEW))
		bitmap_fiww(powt->speed_bitmap, NFP_SUP_SPEED_NUMBEW);
}

/**
 * nfp_net_get_wink_ksettings - Get Wink Speed settings
 * @netdev:	netwowk intewface device stwuctuwe
 * @cmd:	ethtoow command
 *
 * Wepowts speed settings based on info in the BAW pwovided by the fw.
 */
static int
nfp_net_get_wink_ksettings(stwuct net_device *netdev,
			   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	stwuct nfp_net *nn;
	unsigned int speed;
	u16 sts;

	/* Init to unknowns */
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);
	cmd->base.powt = POWT_OTHEW;
	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.dupwex = DUPWEX_UNKNOWN;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (eth_powt) {
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Pause);
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Pause);
		nfp_add_media_wink_mode(powt, eth_powt, cmd);
		if (eth_powt->supp_aneg) {
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Autoneg);
			if (eth_powt->aneg == NFP_ANEG_AUTO) {
				ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Autoneg);
				cmd->base.autoneg = AUTONEG_ENABWE;
			}
		}
		nfp_net_set_fec_wink_mode(eth_powt, cmd);
	}

	if (!netif_cawwiew_ok(netdev))
		wetuwn 0;

	/* Use wink speed fwom ETH tabwe if avaiwabwe, othewwise twy the BAW */
	if (eth_powt) {
		cmd->base.powt = eth_powt->powt_type;
		cmd->base.speed = eth_powt->speed;
		cmd->base.dupwex = DUPWEX_FUWW;
		wetuwn 0;
	}

	if (!nfp_netdev_is_nfp_net(netdev))
		wetuwn -EOPNOTSUPP;
	nn = netdev_pwiv(netdev);

	sts = nn_weadw(nn, NFP_NET_CFG_STS);
	speed = nfp_net_ww2speed(FIEWD_GET(NFP_NET_CFG_STS_WINK_WATE, sts));
	if (!speed)
		wetuwn -EOPNOTSUPP;

	if (speed != SPEED_UNKNOWN) {
		cmd->base.speed = speed;
		cmd->base.dupwex = DUPWEX_FUWW;
	}

	wetuwn 0;
}

static int
nfp_net_set_wink_ksettings(stwuct net_device *netdev,
			   const stwuct ethtoow_wink_ksettings *cmd)
{
	boow weq_aneg = (cmd->base.autoneg == AUTONEG_ENABWE);
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	stwuct nfp_nsp *nsp;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	if (netif_wunning(netdev)) {
		netdev_wawn(netdev, "Changing settings not awwowed on an active intewface. It may cause the powt to be disabwed untiw dwivew wewoad.\n");
		wetuwn -EBUSY;
	}

	nsp = nfp_eth_config_stawt(powt->app->cpp, eth_powt->index);
	if (IS_EWW(nsp))
		wetuwn PTW_EWW(nsp);

	if (weq_aneg && !eth_powt->supp_aneg) {
		netdev_wawn(netdev, "Autoneg is not suppowted.\n");
		eww = -EOPNOTSUPP;
		goto eww_bad_set;
	}

	eww = __nfp_eth_set_aneg(nsp, weq_aneg ? NFP_ANEG_AUTO : NFP_ANEG_DISABWED);
	if (eww)
		goto eww_bad_set;

	if (cmd->base.speed != SPEED_UNKNOWN) {
		u32 speed = cmd->base.speed / eth_powt->wanes;
		boow is_suppowted = fawse;

		fow (u32 i = 0; i < NFP_SUP_SPEED_NUMBEW; i++) {
			if (cmd->base.speed == nfp_eth_speed_map[i] &&
			    test_bit(i, powt->speed_bitmap)) {
				is_suppowted = twue;
				bweak;
			}
		}

		if (!is_suppowted) {
			netdev_eww(netdev, "Speed %u is not suppowted.\n",
				   cmd->base.speed);
			eww = -EINVAW;
			goto eww_bad_set;
		}

		if (weq_aneg) {
			netdev_eww(netdev, "Speed changing is not awwowed when wowking on autoneg mode.\n");
			eww = -EINVAW;
			goto eww_bad_set;
		}

		eww = __nfp_eth_set_speed(nsp, speed);
		if (eww)
			goto eww_bad_set;
	}

	eww = nfp_eth_config_commit_end(nsp);
	if (eww > 0)
		wetuwn 0; /* no change */

	nfp_net_wefwesh_powt_tabwe(powt);

	wetuwn eww;

eww_bad_set:
	nfp_eth_config_cweanup_end(nsp);
	wetuwn eww;
}

static void nfp_net_get_wingpawam(stwuct net_device *netdev,
				  stwuct ethtoow_wingpawam *wing,
				  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	u32 qc_max = nn->dev_info->max_qc_size;

	wing->wx_max_pending = qc_max;
	wing->tx_max_pending = qc_max / nn->dp.ops->tx_min_desc_pew_pkt;
	wing->wx_pending = nn->dp.wxd_cnt;
	wing->tx_pending = nn->dp.txd_cnt;
}

static int nfp_net_set_wing_size(stwuct nfp_net *nn, u32 wxd_cnt, u32 txd_cnt,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nfp_net_dp *dp;

	dp = nfp_net_cwone_dp(nn);
	if (!dp)
		wetuwn -ENOMEM;

	dp->wxd_cnt = wxd_cnt;
	dp->txd_cnt = txd_cnt;

	wetuwn nfp_net_wing_weconfig(nn, dp, extack);
}

static int nfp_net_set_wingpawam(stwuct net_device *netdev,
				 stwuct ethtoow_wingpawam *wing,
				 stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				 stwuct netwink_ext_ack *extack)
{
	u32 tx_dpp, qc_min, qc_max, wxd_cnt, txd_cnt;
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	/* We don't have sepawate queues/wings fow smaww/wawge fwames. */
	if (wing->wx_mini_pending || wing->wx_jumbo_pending)
		wetuwn -EOPNOTSUPP;

	qc_min = nn->dev_info->min_qc_size;
	qc_max = nn->dev_info->max_qc_size;
	tx_dpp = nn->dp.ops->tx_min_desc_pew_pkt;
	/* Wound up to suppowted vawues */
	wxd_cnt = woundup_pow_of_two(wing->wx_pending);
	txd_cnt = woundup_pow_of_two(wing->tx_pending);

	if (wxd_cnt < qc_min || wxd_cnt > qc_max) {
		NW_SET_EWW_MSG_MOD(extack, "wx pawametew out of bounds");
		wetuwn -EINVAW;
	}

	if (txd_cnt < qc_min / tx_dpp || txd_cnt > qc_max / tx_dpp) {
		NW_SET_EWW_MSG_MOD(extack, "tx pawametew out of bounds");
		wetuwn -EINVAW;
	}

	if (nn->dp.wxd_cnt == wxd_cnt && nn->dp.txd_cnt == txd_cnt)
		wetuwn 0;

	nn_dbg(nn, "Change wing size: WxQ %u->%u, TxQ %u->%u\n",
	       nn->dp.wxd_cnt, wxd_cnt, nn->dp.txd_cnt, txd_cnt);

	wetuwn nfp_net_set_wing_size(nn, wxd_cnt, txd_cnt, extack);
}

static int nfp_test_wink(stwuct net_device *netdev)
{
	if (!netif_cawwiew_ok(netdev) || !(netdev->fwags & IFF_UP))
		wetuwn 1;

	wetuwn 0;
}

static int nfp_test_nsp(stwuct net_device *netdev)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	stwuct nfp_nsp_identify *nspi;
	stwuct nfp_nsp *nsp;
	int eww;

	nsp = nfp_nsp_open(app->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		netdev_info(netdev, "NSP Test: faiwed to access the NSP: %d\n", eww);
		goto exit;
	}

	if (nfp_nsp_get_abi_vew_minow(nsp) < 15) {
		eww = -EOPNOTSUPP;
		goto exit_cwose_nsp;
	}

	nspi = kzawwoc(sizeof(*nspi), GFP_KEWNEW);
	if (!nspi) {
		eww = -ENOMEM;
		goto exit_cwose_nsp;
	}

	eww = nfp_nsp_wead_identify(nsp, nspi, sizeof(*nspi));
	if (eww < 0)
		netdev_info(netdev, "NSP Test: weading bsp vewsion faiwed %d\n", eww);

	kfwee(nspi);
exit_cwose_nsp:
	nfp_nsp_cwose(nsp);
exit:
	wetuwn eww;
}

static int nfp_test_fw(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int eww;

	eww = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	if (eww)
		netdev_info(netdev, "FW Test: update faiwed %d\n", eww);

	wetuwn eww;
}

static int nfp_test_weg(stwuct net_device *netdev)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	stwuct nfp_cpp *cpp = app->cpp;
	u32 modew = nfp_cpp_modew(cpp);
	u32 vawue;
	int eww;

	eww = nfp_cpp_modew_autodetect(cpp, &vawue);
	if (eww < 0) {
		netdev_info(netdev, "WEG Test: NFP modew detection faiwed %d\n", eww);
		wetuwn eww;
	}

	wetuwn (vawue == modew) ? 0 : 1;
}

static boow wink_test_suppowted(stwuct net_device *netdev)
{
	wetuwn twue;
}

static boow nsp_test_suppowted(stwuct net_device *netdev)
{
	if (nfp_app_fwom_netdev(netdev))
		wetuwn twue;

	wetuwn fawse;
}

static boow fw_test_suppowted(stwuct net_device *netdev)
{
	if (nfp_netdev_is_nfp_net(netdev))
		wetuwn twue;

	wetuwn fawse;
}

static boow weg_test_suppowted(stwuct net_device *netdev)
{
	if (nfp_app_fwom_netdev(netdev))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct nfp_sewf_test_item {
	chaw name[ETH_GSTWING_WEN];
	boow (*is_suppowted)(stwuct net_device *dev);
	int (*func)(stwuct net_device *dev);
} nfp_sewf_test[] = {
	{"Wink Test", wink_test_suppowted, nfp_test_wink},
	{"NSP Test", nsp_test_suppowted, nfp_test_nsp},
	{"Fiwmwawe Test", fw_test_suppowted, nfp_test_fw},
	{"Wegistew Test", weg_test_suppowted, nfp_test_weg}
};

#define NFP_TEST_TOTAW_NUM AWWAY_SIZE(nfp_sewf_test)

static void nfp_get_sewf_test_stwings(stwuct net_device *netdev, u8 *data)
{
	int i;

	fow (i = 0; i < NFP_TEST_TOTAW_NUM; i++)
		if (nfp_sewf_test[i].is_suppowted(netdev))
			ethtoow_puts(&data, nfp_sewf_test[i].name);
}

static int nfp_get_sewf_test_count(stwuct net_device *netdev)
{
	int i, count = 0;

	fow (i = 0; i < NFP_TEST_TOTAW_NUM; i++)
		if (nfp_sewf_test[i].is_suppowted(netdev))
			count++;

	wetuwn count;
}

static void nfp_net_sewf_test(stwuct net_device *netdev, stwuct ethtoow_test *eth_test,
			      u64 *data)
{
	int i, wet, count = 0;

	netdev_info(netdev, "Stawt sewf test\n");

	fow (i = 0; i < NFP_TEST_TOTAW_NUM; i++) {
		if (nfp_sewf_test[i].is_suppowted(netdev)) {
			wet = nfp_sewf_test[i].func(netdev);
			if (wet)
				eth_test->fwags |= ETH_TEST_FW_FAIWED;
			data[count++] = wet;
		}
	}

	netdev_info(netdev, "Test end\n");
}

static unsigned int nfp_vnic_get_sw_stats_count(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	wetuwn NN_WVEC_GATHEW_STATS + nn->max_w_vecs * NN_WVEC_PEW_Q_STATS +
		NN_CTWW_PATH_STATS;
}

static u8 *nfp_vnic_get_sw_stats_stwings(stwuct net_device *netdev, u8 *data)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int i;

	fow (i = 0; i < nn->max_w_vecs; i++) {
		ethtoow_spwintf(&data, "wvec_%u_wx_pkts", i);
		ethtoow_spwintf(&data, "wvec_%u_tx_pkts", i);
		ethtoow_spwintf(&data, "wvec_%u_tx_busy", i);
	}

	ethtoow_puts(&data, "hw_wx_csum_ok");
	ethtoow_puts(&data, "hw_wx_csum_innew_ok");
	ethtoow_puts(&data, "hw_wx_csum_compwete");
	ethtoow_puts(&data, "hw_wx_csum_eww");
	ethtoow_puts(&data, "wx_wepwace_buf_awwoc_faiw");
	ethtoow_puts(&data, "wx_tws_decwypted_packets");
	ethtoow_puts(&data, "hw_tx_csum");
	ethtoow_puts(&data, "hw_tx_innew_csum");
	ethtoow_puts(&data, "tx_gathew");
	ethtoow_puts(&data, "tx_wso");
	ethtoow_puts(&data, "tx_tws_encwypted_packets");
	ethtoow_puts(&data, "tx_tws_ooo");
	ethtoow_puts(&data, "tx_tws_dwop_no_sync_data");

	ethtoow_puts(&data, "hw_tws_no_space");
	ethtoow_puts(&data, "wx_tws_wesync_weq_ok");
	ethtoow_puts(&data, "wx_tws_wesync_weq_ign");
	ethtoow_puts(&data, "wx_tws_wesync_sent");

	wetuwn data;
}

static u64 *nfp_vnic_get_sw_stats(stwuct net_device *netdev, u64 *data)
{
	u64 gathewed_stats[NN_WVEC_GATHEW_STATS] = {};
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	u64 tmp[NN_WVEC_GATHEW_STATS];
	unsigned int i, j;

	fow (i = 0; i < nn->max_w_vecs; i++) {
		unsigned int stawt;

		do {
			stawt = u64_stats_fetch_begin(&nn->w_vecs[i].wx_sync);
			data[0] = nn->w_vecs[i].wx_pkts;
			tmp[0] = nn->w_vecs[i].hw_csum_wx_ok;
			tmp[1] = nn->w_vecs[i].hw_csum_wx_innew_ok;
			tmp[2] = nn->w_vecs[i].hw_csum_wx_compwete;
			tmp[3] = nn->w_vecs[i].hw_csum_wx_ewwow;
			tmp[4] = nn->w_vecs[i].wx_wepwace_buf_awwoc_faiw;
			tmp[5] = nn->w_vecs[i].hw_tws_wx;
		} whiwe (u64_stats_fetch_wetwy(&nn->w_vecs[i].wx_sync, stawt));

		do {
			stawt = u64_stats_fetch_begin(&nn->w_vecs[i].tx_sync);
			data[1] = nn->w_vecs[i].tx_pkts;
			data[2] = nn->w_vecs[i].tx_busy;
			tmp[6] = nn->w_vecs[i].hw_csum_tx;
			tmp[7] = nn->w_vecs[i].hw_csum_tx_innew;
			tmp[8] = nn->w_vecs[i].tx_gathew;
			tmp[9] = nn->w_vecs[i].tx_wso;
			tmp[10] = nn->w_vecs[i].hw_tws_tx;
			tmp[11] = nn->w_vecs[i].tws_tx_fawwback;
			tmp[12] = nn->w_vecs[i].tws_tx_no_fawwback;
		} whiwe (u64_stats_fetch_wetwy(&nn->w_vecs[i].tx_sync, stawt));

		data += NN_WVEC_PEW_Q_STATS;

		fow (j = 0; j < NN_WVEC_GATHEW_STATS; j++)
			gathewed_stats[j] += tmp[j];
	}

	fow (j = 0; j < NN_WVEC_GATHEW_STATS; j++)
		*data++ = gathewed_stats[j];

	*data++ = atomic_wead(&nn->ktws_no_space);
	*data++ = atomic_wead(&nn->ktws_wx_wesync_weq);
	*data++ = atomic_wead(&nn->ktws_wx_wesync_ign);
	*data++ = atomic_wead(&nn->ktws_wx_wesync_sent);

	wetuwn data;
}

static unsigned int nfp_vnic_get_hw_stats_count(unsigned int num_vecs)
{
	wetuwn NN_ET_GWOBAW_STATS_WEN + num_vecs * 4;
}

static u8 *
nfp_vnic_get_hw_stats_stwings(u8 *data, unsigned int num_vecs, boow wepw)
{
	int swap_off, i;

	BUIWD_BUG_ON(NN_ET_GWOBAW_STATS_WEN < NN_ET_SWITCH_STATS_WEN * 2);
	/* If wepw is twue fiwst add SWITCH_STATS_WEN and then subtwact it
	 * effectivewy swapping the WX and TX statistics (giving us the WX
	 * and TX fwom pewspective of the switch).
	 */
	swap_off = wepw * NN_ET_SWITCH_STATS_WEN;

	fow (i = 0; i < NN_ET_SWITCH_STATS_WEN; i++)
		ethtoow_puts(&data, nfp_net_et_stats[i + swap_off].name);

	fow (i = NN_ET_SWITCH_STATS_WEN; i < NN_ET_SWITCH_STATS_WEN * 2; i++)
		ethtoow_puts(&data, nfp_net_et_stats[i - swap_off].name);

	fow (i = NN_ET_SWITCH_STATS_WEN * 2; i < NN_ET_GWOBAW_STATS_WEN; i++)
		ethtoow_puts(&data, nfp_net_et_stats[i].name);

	fow (i = 0; i < num_vecs; i++) {
		ethtoow_spwintf(&data, "wxq_%u_pkts", i);
		ethtoow_spwintf(&data, "wxq_%u_bytes", i);
		ethtoow_spwintf(&data, "txq_%u_pkts", i);
		ethtoow_spwintf(&data, "txq_%u_bytes", i);
	}

	wetuwn data;
}

static u64 *
nfp_vnic_get_hw_stats(u64 *data, u8 __iomem *mem, unsigned int num_vecs)
{
	unsigned int i;

	fow (i = 0; i < NN_ET_GWOBAW_STATS_WEN; i++)
		*data++ = weadq(mem + nfp_net_et_stats[i].off);

	fow (i = 0; i < num_vecs; i++) {
		*data++ = weadq(mem + NFP_NET_CFG_WXW_STATS(i));
		*data++ = weadq(mem + NFP_NET_CFG_WXW_STATS(i) + 8);
		*data++ = weadq(mem + NFP_NET_CFG_TXW_STATS(i));
		*data++ = weadq(mem + NFP_NET_CFG_TXW_STATS(i) + 8);
	}

	wetuwn data;
}

static unsigned int nfp_vnic_get_twv_stats_count(stwuct nfp_net *nn)
{
	wetuwn nn->twv_caps.vnic_stats_cnt + nn->max_w_vecs * 4;
}

static u8 *nfp_vnic_get_twv_stats_stwings(stwuct nfp_net *nn, u8 *data)
{
	unsigned int i, id;
	u8 __iomem *mem;
	u64 id_wowd = 0;

	mem = nn->dp.ctww_baw + nn->twv_caps.vnic_stats_off;
	fow (i = 0; i < nn->twv_caps.vnic_stats_cnt; i++) {
		if (!(i % 4))
			id_wowd = weadq(mem + i * 2);

		id = (u16)id_wowd;
		id_wowd >>= 16;

		if (id < AWWAY_SIZE(nfp_twv_stat_names) &&
		    nfp_twv_stat_names[id][0]) {
			memcpy(data, nfp_twv_stat_names[id], ETH_GSTWING_WEN);
			data += ETH_GSTWING_WEN;
		} ewse {
			ethtoow_spwintf(&data, "dev_unknown_stat%u", id);
		}
	}

	fow (i = 0; i < nn->max_w_vecs; i++) {
		ethtoow_spwintf(&data, "wxq_%u_pkts", i);
		ethtoow_spwintf(&data, "wxq_%u_bytes", i);
		ethtoow_spwintf(&data, "txq_%u_pkts", i);
		ethtoow_spwintf(&data, "txq_%u_bytes", i);
	}

	wetuwn data;
}

static u64 *nfp_vnic_get_twv_stats(stwuct nfp_net *nn, u64 *data)
{
	u8 __iomem *mem;
	unsigned int i;

	mem = nn->dp.ctww_baw + nn->twv_caps.vnic_stats_off;
	mem += woundup(2 * nn->twv_caps.vnic_stats_cnt, 8);
	fow (i = 0; i < nn->twv_caps.vnic_stats_cnt; i++)
		*data++ = weadq(mem + i * 8);

	mem = nn->dp.ctww_baw;
	fow (i = 0; i < nn->max_w_vecs; i++) {
		*data++ = weadq(mem + NFP_NET_CFG_WXW_STATS(i));
		*data++ = weadq(mem + NFP_NET_CFG_WXW_STATS(i) + 8);
		*data++ = weadq(mem + NFP_NET_CFG_TXW_STATS(i));
		*data++ = weadq(mem + NFP_NET_CFG_TXW_STATS(i) + 8);
	}

	wetuwn data;
}

static unsigned int nfp_mac_get_stats_count(stwuct net_device *netdev)
{
	stwuct nfp_powt *powt;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!__nfp_powt_get_eth_powt(powt) || !powt->eth_stats)
		wetuwn 0;

	wetuwn AWWAY_SIZE(nfp_mac_et_stats);
}

static u8 *nfp_mac_get_stats_stwings(stwuct net_device *netdev, u8 *data)
{
	stwuct nfp_powt *powt;
	unsigned int i;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!__nfp_powt_get_eth_powt(powt) || !powt->eth_stats)
		wetuwn data;

	fow (i = 0; i < AWWAY_SIZE(nfp_mac_et_stats); i++)
		ethtoow_spwintf(&data, "mac.%s", nfp_mac_et_stats[i].name);

	wetuwn data;
}

static u64 *nfp_mac_get_stats(stwuct net_device *netdev, u64 *data)
{
	stwuct nfp_powt *powt;
	unsigned int i;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!__nfp_powt_get_eth_powt(powt) || !powt->eth_stats)
		wetuwn data;

	fow (i = 0; i < AWWAY_SIZE(nfp_mac_et_stats); i++)
		*data++ = weadq(powt->eth_stats + nfp_mac_et_stats[i].off);

	wetuwn data;
}

static void nfp_net_get_stwings(stwuct net_device *netdev,
				u32 stwingset, u8 *data)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	switch (stwingset) {
	case ETH_SS_STATS:
		data = nfp_vnic_get_sw_stats_stwings(netdev, data);
		if (!nn->twv_caps.vnic_stats_off)
			data = nfp_vnic_get_hw_stats_stwings(data,
							     nn->max_w_vecs,
							     fawse);
		ewse
			data = nfp_vnic_get_twv_stats_stwings(nn, data);
		data = nfp_mac_get_stats_stwings(netdev, data);
		data = nfp_app_powt_get_stats_stwings(nn->powt, data);
		bweak;
	case ETH_SS_TEST:
		nfp_get_sewf_test_stwings(netdev, data);
		bweak;
	}
}

static void
nfp_net_get_stats(stwuct net_device *netdev, stwuct ethtoow_stats *stats,
		  u64 *data)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	data = nfp_vnic_get_sw_stats(netdev, data);
	if (!nn->twv_caps.vnic_stats_off)
		data = nfp_vnic_get_hw_stats(data, nn->dp.ctww_baw,
					     nn->max_w_vecs);
	ewse
		data = nfp_vnic_get_twv_stats(nn, data);
	data = nfp_mac_get_stats(netdev, data);
	data = nfp_app_powt_get_stats(nn->powt, data);
}

static int nfp_net_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	unsigned int cnt;

	switch (sset) {
	case ETH_SS_STATS:
		cnt = nfp_vnic_get_sw_stats_count(netdev);
		if (!nn->twv_caps.vnic_stats_off)
			cnt += nfp_vnic_get_hw_stats_count(nn->max_w_vecs);
		ewse
			cnt += nfp_vnic_get_twv_stats_count(nn);
		cnt += nfp_mac_get_stats_count(netdev);
		cnt += nfp_app_powt_get_stats_count(nn->powt);
		wetuwn cnt;
	case ETH_SS_TEST:
		wetuwn nfp_get_sewf_test_count(netdev);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void nfp_powt_get_stwings(stwuct net_device *netdev,
				 u32 stwingset, u8 *data)
{
	stwuct nfp_powt *powt = nfp_powt_fwom_netdev(netdev);

	switch (stwingset) {
	case ETH_SS_STATS:
		if (nfp_powt_is_vnic(powt))
			data = nfp_vnic_get_hw_stats_stwings(data, 0, twue);
		ewse
			data = nfp_mac_get_stats_stwings(netdev, data);
		data = nfp_app_powt_get_stats_stwings(powt, data);
		bweak;
	case ETH_SS_TEST:
		nfp_get_sewf_test_stwings(netdev, data);
		bweak;
	}
}

static void
nfp_powt_get_stats(stwuct net_device *netdev, stwuct ethtoow_stats *stats,
		   u64 *data)
{
	stwuct nfp_powt *powt = nfp_powt_fwom_netdev(netdev);

	if (nfp_powt_is_vnic(powt))
		data = nfp_vnic_get_hw_stats(data, powt->vnic, 0);
	ewse
		data = nfp_mac_get_stats(netdev, data);
	data = nfp_app_powt_get_stats(powt, data);
}

static int nfp_powt_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct nfp_powt *powt = nfp_powt_fwom_netdev(netdev);
	unsigned int count;

	switch (sset) {
	case ETH_SS_STATS:
		if (nfp_powt_is_vnic(powt))
			count = nfp_vnic_get_hw_stats_count(0);
		ewse
			count = nfp_mac_get_stats_count(netdev);
		count += nfp_app_powt_get_stats_count(powt);
		wetuwn count;
	case ETH_SS_TEST:
		wetuwn nfp_get_sewf_test_count(netdev);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int nfp_powt_fec_ethtoow_to_nsp(u32 fec)
{
	switch (fec) {
	case ETHTOOW_FEC_AUTO:
		wetuwn NFP_FEC_AUTO_BIT;
	case ETHTOOW_FEC_OFF:
		wetuwn NFP_FEC_DISABWED_BIT;
	case ETHTOOW_FEC_WS:
		wetuwn NFP_FEC_WEED_SOWOMON_BIT;
	case ETHTOOW_FEC_BASEW:
		wetuwn NFP_FEC_BASEW_BIT;
	defauwt:
		/* NSP onwy suppowts a singwe mode at a time */
		wetuwn -EOPNOTSUPP;
	}
}

static u32 nfp_powt_fec_nsp_to_ethtoow(u32 fec)
{
	u32 wesuwt = 0;

	if (fec & NFP_FEC_AUTO)
		wesuwt |= ETHTOOW_FEC_AUTO;
	if (fec & NFP_FEC_BASEW)
		wesuwt |= ETHTOOW_FEC_BASEW;
	if (fec & NFP_FEC_WEED_SOWOMON)
		wesuwt |= ETHTOOW_FEC_WS;
	if (fec & NFP_FEC_DISABWED)
		wesuwt |= ETHTOOW_FEC_OFF;

	wetuwn wesuwt ?: ETHTOOW_FEC_NONE;
}

static int
nfp_powt_get_fecpawam(stwuct net_device *netdev,
		      stwuct ethtoow_fecpawam *pawam)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;

	pawam->active_fec = ETHTOOW_FEC_NONE;
	pawam->fec = ETHTOOW_FEC_NONE;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	if (!nfp_eth_can_suppowt_fec(eth_powt))
		wetuwn 0;

	pawam->fec = nfp_powt_fec_nsp_to_ethtoow(eth_powt->fec_modes_suppowted);
	pawam->active_fec = nfp_powt_fec_nsp_to_ethtoow(BIT(eth_powt->act_fec));

	wetuwn 0;
}

static int
nfp_powt_set_fecpawam(stwuct net_device *netdev,
		      stwuct ethtoow_fecpawam *pawam)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	int eww, fec;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	if (!nfp_eth_can_suppowt_fec(eth_powt))
		wetuwn -EOPNOTSUPP;

	fec = nfp_powt_fec_ethtoow_to_nsp(pawam->fec);
	if (fec < 0)
		wetuwn fec;

	eww = nfp_eth_set_fec(powt->app->cpp, eth_powt->index, fec);
	if (!eww)
		/* Onwy wefwesh if we did something */
		nfp_net_wefwesh_powt_tabwe(powt);

	wetuwn eww < 0 ? eww : 0;
}

/* WX netwowk fwow cwassification (WSS, fiwtews, etc)
 */
static u32 ethtoow_fwow_to_nfp_fwag(u32 fwow_type)
{
	static const u32 xwate_ethtoow_to_nfp[IPV6_FWOW + 1] = {
		[TCP_V4_FWOW]	= NFP_NET_CFG_WSS_IPV4_TCP,
		[TCP_V6_FWOW]	= NFP_NET_CFG_WSS_IPV6_TCP,
		[UDP_V4_FWOW]	= NFP_NET_CFG_WSS_IPV4_UDP,
		[UDP_V6_FWOW]	= NFP_NET_CFG_WSS_IPV6_UDP,
		[IPV4_FWOW]	= NFP_NET_CFG_WSS_IPV4,
		[IPV6_FWOW]	= NFP_NET_CFG_WSS_IPV6,
	};

	if (fwow_type >= AWWAY_SIZE(xwate_ethtoow_to_nfp))
		wetuwn 0;

	wetuwn xwate_ethtoow_to_nfp[fwow_type];
}

static int nfp_net_get_wss_hash_opts(stwuct nfp_net *nn,
				     stwuct ethtoow_wxnfc *cmd)
{
	u32 nfp_wss_fwag;

	cmd->data = 0;

	if (!(nn->cap & NFP_NET_CFG_CTWW_WSS_ANY))
		wetuwn -EOPNOTSUPP;

	nfp_wss_fwag = ethtoow_fwow_to_nfp_fwag(cmd->fwow_type);
	if (!nfp_wss_fwag)
		wetuwn -EINVAW;

	cmd->data |= WXH_IP_SWC | WXH_IP_DST;
	if (nn->wss_cfg & nfp_wss_fwag)
		cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;

	wetuwn 0;
}

#define NFP_FS_MAX_ENTWY	1024

static int nfp_net_fs_to_ethtoow(stwuct nfp_fs_entwy *entwy, stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fs = &cmd->fs;
	unsigned int i;

	switch (entwy->fwow_type & ~FWOW_WSS) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
		fs->h_u.tcp_ip4_spec.ip4swc = entwy->key.sip4;
		fs->h_u.tcp_ip4_spec.ip4dst = entwy->key.dip4;
		fs->h_u.tcp_ip4_spec.pswc   = entwy->key.spowt;
		fs->h_u.tcp_ip4_spec.pdst   = entwy->key.dpowt;
		fs->m_u.tcp_ip4_spec.ip4swc = entwy->msk.sip4;
		fs->m_u.tcp_ip4_spec.ip4dst = entwy->msk.dip4;
		fs->m_u.tcp_ip4_spec.pswc   = entwy->msk.spowt;
		fs->m_u.tcp_ip4_spec.pdst   = entwy->msk.dpowt;
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
		fow (i = 0; i < 4; i++) {
			fs->h_u.tcp_ip6_spec.ip6swc[i] = entwy->key.sip6[i];
			fs->h_u.tcp_ip6_spec.ip6dst[i] = entwy->key.dip6[i];
			fs->m_u.tcp_ip6_spec.ip6swc[i] = entwy->msk.sip6[i];
			fs->m_u.tcp_ip6_spec.ip6dst[i] = entwy->msk.dip6[i];
		}
		fs->h_u.tcp_ip6_spec.pswc = entwy->key.spowt;
		fs->h_u.tcp_ip6_spec.pdst = entwy->key.dpowt;
		fs->m_u.tcp_ip6_spec.pswc = entwy->msk.spowt;
		fs->m_u.tcp_ip6_spec.pdst = entwy->msk.dpowt;
		bweak;
	case IPV4_USEW_FWOW:
		fs->h_u.usw_ip4_spec.ip_vew = ETH_WX_NFC_IP4;
		fs->h_u.usw_ip4_spec.ip4swc = entwy->key.sip4;
		fs->h_u.usw_ip4_spec.ip4dst = entwy->key.dip4;
		fs->h_u.usw_ip4_spec.pwoto  = entwy->key.w4_pwoto;
		fs->m_u.usw_ip4_spec.ip4swc = entwy->msk.sip4;
		fs->m_u.usw_ip4_spec.ip4dst = entwy->msk.dip4;
		fs->m_u.usw_ip4_spec.pwoto  = entwy->msk.w4_pwoto;
		bweak;
	case IPV6_USEW_FWOW:
		fow (i = 0; i < 4; i++) {
			fs->h_u.usw_ip6_spec.ip6swc[i] = entwy->key.sip6[i];
			fs->h_u.usw_ip6_spec.ip6dst[i] = entwy->key.dip6[i];
			fs->m_u.usw_ip6_spec.ip6swc[i] = entwy->msk.sip6[i];
			fs->m_u.usw_ip6_spec.ip6dst[i] = entwy->msk.dip6[i];
		}
		fs->h_u.usw_ip6_spec.w4_pwoto = entwy->key.w4_pwoto;
		fs->m_u.usw_ip6_spec.w4_pwoto = entwy->msk.w4_pwoto;
		bweak;
	case ETHEW_FWOW:
		fs->h_u.ethew_spec.h_pwoto = entwy->key.w3_pwoto;
		fs->m_u.ethew_spec.h_pwoto = entwy->msk.w3_pwoto;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fs->fwow_type   = entwy->fwow_type;
	fs->wing_cookie = entwy->action;

	if (fs->fwow_type & FWOW_WSS) {
		/* Onwy wss_context of 0 is suppowted. */
		cmd->wss_context = 0;
		/* WSS is used, mask the wing. */
		fs->wing_cookie |= ETHTOOW_WX_FWOW_SPEC_WING;
	}

	wetuwn 0;
}

static int nfp_net_get_fs_wuwe(stwuct nfp_net *nn, stwuct ethtoow_wxnfc *cmd)
{
	stwuct nfp_fs_entwy *entwy;

	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_FWOW_STEEW))
		wetuwn -EOPNOTSUPP;

	if (cmd->fs.wocation >= NFP_FS_MAX_ENTWY)
		wetuwn -EINVAW;

	wist_fow_each_entwy(entwy, &nn->fs.wist, node) {
		if (entwy->woc == cmd->fs.wocation)
			wetuwn nfp_net_fs_to_ethtoow(entwy, cmd);

		if (entwy->woc > cmd->fs.wocation)
			/* no need to continue */
			wetuwn -ENOENT;
	}

	wetuwn -ENOENT;
}

static int nfp_net_get_fs_woc(stwuct nfp_net *nn, u32 *wuwe_wocs)
{
	stwuct nfp_fs_entwy *entwy;
	u32 count = 0;

	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_FWOW_STEEW))
		wetuwn -EOPNOTSUPP;

	wist_fow_each_entwy(entwy, &nn->fs.wist, node)
		wuwe_wocs[count++] = entwy->woc;

	wetuwn 0;
}

static int nfp_net_get_wxnfc(stwuct net_device *netdev,
			     stwuct ethtoow_wxnfc *cmd, u32 *wuwe_wocs)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		cmd->data = nn->dp.num_wx_wings;
		wetuwn 0;
	case ETHTOOW_GWXCWSWWCNT:
		cmd->wuwe_cnt = nn->fs.count;
		wetuwn 0;
	case ETHTOOW_GWXCWSWUWE:
		wetuwn nfp_net_get_fs_wuwe(nn, cmd);
	case ETHTOOW_GWXCWSWWAWW:
		cmd->data = NFP_FS_MAX_ENTWY;
		wetuwn nfp_net_get_fs_woc(nn, wuwe_wocs);
	case ETHTOOW_GWXFH:
		wetuwn nfp_net_get_wss_hash_opts(nn, cmd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int nfp_net_set_wss_hash_opt(stwuct nfp_net *nn,
				    stwuct ethtoow_wxnfc *nfc)
{
	u32 new_wss_cfg = nn->wss_cfg;
	u32 nfp_wss_fwag;
	int eww;

	if (!(nn->cap & NFP_NET_CFG_CTWW_WSS_ANY))
		wetuwn -EOPNOTSUPP;

	/* WSS onwy suppowts IP SA/DA and W4 swc/dst powts  */
	if (nfc->data & ~(WXH_IP_SWC | WXH_IP_DST |
			  WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EINVAW;

	/* We need at weast the IP SA/DA fiewds fow hashing */
	if (!(nfc->data & WXH_IP_SWC) ||
	    !(nfc->data & WXH_IP_DST))
		wetuwn -EINVAW;

	nfp_wss_fwag = ethtoow_fwow_to_nfp_fwag(nfc->fwow_type);
	if (!nfp_wss_fwag)
		wetuwn -EINVAW;

	switch (nfc->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
	case 0:
		new_wss_cfg &= ~nfp_wss_fwag;
		bweak;
	case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
		new_wss_cfg |= nfp_wss_fwag;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	new_wss_cfg |= FIEWD_PWEP(NFP_NET_CFG_WSS_HFUNC, nn->wss_hfunc);
	new_wss_cfg |= NFP_NET_CFG_WSS_MASK;

	if (new_wss_cfg == nn->wss_cfg)
		wetuwn 0;

	wwitew(new_wss_cfg, nn->dp.ctww_baw + NFP_NET_CFG_WSS_CTWW);
	eww = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_WSS);
	if (eww)
		wetuwn eww;

	nn->wss_cfg = new_wss_cfg;

	nn_dbg(nn, "Changed WSS config to 0x%x\n", nn->wss_cfg);
	wetuwn 0;
}

static int nfp_net_fs_fwom_ethtoow(stwuct nfp_fs_entwy *entwy, stwuct ethtoow_wx_fwow_spec *fs)
{
	unsigned int i;

	/* FWOW_EXT/FWOW_MAC_EXT is not suppowted. */
	switch (fs->fwow_type & ~FWOW_WSS) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
		entwy->msk.sip4  = fs->m_u.tcp_ip4_spec.ip4swc;
		entwy->msk.dip4  = fs->m_u.tcp_ip4_spec.ip4dst;
		entwy->msk.spowt = fs->m_u.tcp_ip4_spec.pswc;
		entwy->msk.dpowt = fs->m_u.tcp_ip4_spec.pdst;
		entwy->key.sip4  = fs->h_u.tcp_ip4_spec.ip4swc & entwy->msk.sip4;
		entwy->key.dip4  = fs->h_u.tcp_ip4_spec.ip4dst & entwy->msk.dip4;
		entwy->key.spowt = fs->h_u.tcp_ip4_spec.pswc & entwy->msk.spowt;
		entwy->key.dpowt = fs->h_u.tcp_ip4_spec.pdst & entwy->msk.dpowt;
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
		fow (i = 0; i < 4; i++) {
			entwy->msk.sip6[i] = fs->m_u.tcp_ip6_spec.ip6swc[i];
			entwy->msk.dip6[i] = fs->m_u.tcp_ip6_spec.ip6dst[i];
			entwy->key.sip6[i] = fs->h_u.tcp_ip6_spec.ip6swc[i] & entwy->msk.sip6[i];
			entwy->key.dip6[i] = fs->h_u.tcp_ip6_spec.ip6dst[i] & entwy->msk.dip6[i];
		}
		entwy->msk.spowt = fs->m_u.tcp_ip6_spec.pswc;
		entwy->msk.dpowt = fs->m_u.tcp_ip6_spec.pdst;
		entwy->key.spowt = fs->h_u.tcp_ip6_spec.pswc & entwy->msk.spowt;
		entwy->key.dpowt = fs->h_u.tcp_ip6_spec.pdst & entwy->msk.dpowt;
		bweak;
	case IPV4_USEW_FWOW:
		entwy->msk.sip4     = fs->m_u.usw_ip4_spec.ip4swc;
		entwy->msk.dip4     = fs->m_u.usw_ip4_spec.ip4dst;
		entwy->msk.w4_pwoto = fs->m_u.usw_ip4_spec.pwoto;
		entwy->key.sip4     = fs->h_u.usw_ip4_spec.ip4swc & entwy->msk.sip4;
		entwy->key.dip4     = fs->h_u.usw_ip4_spec.ip4dst & entwy->msk.dip4;
		entwy->key.w4_pwoto = fs->h_u.usw_ip4_spec.pwoto & entwy->msk.w4_pwoto;
		bweak;
	case IPV6_USEW_FWOW:
		fow (i = 0; i < 4; i++) {
			entwy->msk.sip6[i] = fs->m_u.usw_ip6_spec.ip6swc[i];
			entwy->msk.dip6[i] = fs->m_u.usw_ip6_spec.ip6dst[i];
			entwy->key.sip6[i] = fs->h_u.usw_ip6_spec.ip6swc[i] & entwy->msk.sip6[i];
			entwy->key.dip6[i] = fs->h_u.usw_ip6_spec.ip6dst[i] & entwy->msk.dip6[i];
		}
		entwy->msk.w4_pwoto = fs->m_u.usw_ip6_spec.w4_pwoto;
		entwy->key.w4_pwoto = fs->h_u.usw_ip6_spec.w4_pwoto & entwy->msk.w4_pwoto;
		bweak;
	case ETHEW_FWOW:
		entwy->msk.w3_pwoto = fs->m_u.ethew_spec.h_pwoto;
		entwy->key.w3_pwoto = fs->h_u.ethew_spec.h_pwoto & entwy->msk.w3_pwoto;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fs->fwow_type & ~FWOW_WSS) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		entwy->key.w4_pwoto = IPPWOTO_TCP;
		entwy->msk.w4_pwoto = 0xff;
		bweak;
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
		entwy->key.w4_pwoto = IPPWOTO_UDP;
		entwy->msk.w4_pwoto = 0xff;
		bweak;
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
		entwy->key.w4_pwoto = IPPWOTO_SCTP;
		entwy->msk.w4_pwoto = 0xff;
		bweak;
	}

	entwy->fwow_type = fs->fwow_type;
	entwy->action    = fs->wing_cookie;
	entwy->woc       = fs->wocation;

	wetuwn 0;
}

static int nfp_net_fs_check_existing(stwuct nfp_net *nn, stwuct nfp_fs_entwy *new)
{
	stwuct nfp_fs_entwy *entwy;

	wist_fow_each_entwy(entwy, &nn->fs.wist, node) {
		if (new->woc != entwy->woc &&
		    !((new->fwow_type ^ entwy->fwow_type) & ~FWOW_WSS) &&
		    !memcmp(&new->key, &entwy->key, sizeof(new->key)) &&
		    !memcmp(&new->msk, &entwy->msk, sizeof(new->msk)))
			wetuwn entwy->woc;
	}

	/* -1 means no dupwicates */
	wetuwn -1;
}

static int nfp_net_fs_add(stwuct nfp_net *nn, stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fs = &cmd->fs;
	stwuct nfp_fs_entwy *new, *entwy;
	boow unsupp_mask;
	int eww, id;

	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_FWOW_STEEW))
		wetuwn -EOPNOTSUPP;

	/* Onwy defauwt WSS context(0) is suppowted. */
	if ((fs->fwow_type & FWOW_WSS) && cmd->wss_context)
		wetuwn -EOPNOTSUPP;

	if (fs->wocation >= NFP_FS_MAX_ENTWY)
		wetuwn -EINVAW;

	if (fs->wing_cookie != WX_CWS_FWOW_DISC &&
	    fs->wing_cookie >= nn->dp.num_wx_wings)
		wetuwn -EINVAW;

	/* FWOW_EXT/FWOW_MAC_EXT is not suppowted. */
	switch (fs->fwow_type & ~FWOW_WSS) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
		unsupp_mask = !!fs->m_u.tcp_ip4_spec.tos;
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
		unsupp_mask = !!fs->m_u.tcp_ip6_spec.tcwass;
		bweak;
	case IPV4_USEW_FWOW:
		unsupp_mask = !!fs->m_u.usw_ip4_spec.w4_4_bytes ||
			      !!fs->m_u.usw_ip4_spec.tos ||
			      !!fs->m_u.usw_ip4_spec.ip_vew;
		/* ip_vew must be ETH_WX_NFC_IP4. */
		unsupp_mask |= fs->h_u.usw_ip4_spec.ip_vew != ETH_WX_NFC_IP4;
		bweak;
	case IPV6_USEW_FWOW:
		unsupp_mask = !!fs->m_u.usw_ip6_spec.w4_4_bytes ||
			      !!fs->m_u.usw_ip6_spec.tcwass;
		bweak;
	case ETHEW_FWOW:
		if (fs->h_u.ethew_spec.h_pwoto == htons(ETH_P_IP) ||
		    fs->h_u.ethew_spec.h_pwoto == htons(ETH_P_IPV6)) {
			nn_eww(nn, "Pwease use ip4/ip6 fwow type instead.\n");
			wetuwn -EOPNOTSUPP;
		}
		/* Onwy unmasked ethtype is suppowted. */
		unsupp_mask = !is_zewo_ethew_addw(fs->m_u.ethew_spec.h_dest) ||
			      !is_zewo_ethew_addw(fs->m_u.ethew_spec.h_souwce) ||
			      (fs->m_u.ethew_spec.h_pwoto != htons(0xffff));
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (unsupp_mask)
		wetuwn -EOPNOTSUPP;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;

	nfp_net_fs_fwom_ethtoow(new, fs);

	id = nfp_net_fs_check_existing(nn, new);
	if (id >= 0) {
		nn_eww(nn, "Identicaw wuwe is existing in %d.\n", id);
		eww = -EINVAW;
		goto eww;
	}

	/* Insewt to wist in ascending owdew of wocation. */
	wist_fow_each_entwy(entwy, &nn->fs.wist, node) {
		if (entwy->woc == fs->wocation) {
			eww = nfp_net_fs_dew_hw(nn, entwy);
			if (eww)
				goto eww;

			nn->fs.count--;
			eww = nfp_net_fs_add_hw(nn, new);
			if (eww)
				goto eww;

			nn->fs.count++;
			wist_wepwace(&entwy->node, &new->node);
			kfwee(entwy);

			wetuwn 0;
		}

		if (entwy->woc > fs->wocation)
			bweak;
	}

	if (nn->fs.count == NFP_FS_MAX_ENTWY) {
		eww = -ENOSPC;
		goto eww;
	}

	eww = nfp_net_fs_add_hw(nn, new);
	if (eww)
		goto eww;

	wist_add_taiw(&new->node, &entwy->node);
	nn->fs.count++;

	wetuwn 0;

eww:
	kfwee(new);
	wetuwn eww;
}

static int nfp_net_fs_dew(stwuct nfp_net *nn, stwuct ethtoow_wxnfc *cmd)
{
	stwuct nfp_fs_entwy *entwy;
	int eww;

	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_FWOW_STEEW))
		wetuwn -EOPNOTSUPP;

	if (!nn->fs.count || cmd->fs.wocation >= NFP_FS_MAX_ENTWY)
		wetuwn -EINVAW;

	wist_fow_each_entwy(entwy, &nn->fs.wist, node) {
		if (entwy->woc == cmd->fs.wocation) {
			eww = nfp_net_fs_dew_hw(nn, entwy);
			if (eww)
				wetuwn eww;

			wist_dew(&entwy->node);
			kfwee(entwy);
			nn->fs.count--;

			wetuwn 0;
		} ewse if (entwy->woc > cmd->fs.wocation) {
			/* no need to continue */
			bweak;
		}
	}

	wetuwn -ENOENT;
}

static int nfp_net_set_wxnfc(stwuct net_device *netdev,
			     stwuct ethtoow_wxnfc *cmd)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	switch (cmd->cmd) {
	case ETHTOOW_SWXFH:
		wetuwn nfp_net_set_wss_hash_opt(nn, cmd);
	case ETHTOOW_SWXCWSWWINS:
		wetuwn nfp_net_fs_add(nn, cmd);
	case ETHTOOW_SWXCWSWWDEW:
		wetuwn nfp_net_fs_dew(nn, cmd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static u32 nfp_net_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	if (!(nn->cap & NFP_NET_CFG_CTWW_WSS_ANY))
		wetuwn 0;

	wetuwn AWWAY_SIZE(nn->wss_itbw);
}

static u32 nfp_net_get_wxfh_key_size(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	if (!(nn->cap & NFP_NET_CFG_CTWW_WSS_ANY))
		wetuwn -EOPNOTSUPP;

	wetuwn nfp_net_wss_key_sz(nn);
}

static int nfp_net_get_wxfh(stwuct net_device *netdev,
			    stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int i;

	if (!(nn->cap & NFP_NET_CFG_CTWW_WSS_ANY))
		wetuwn -EOPNOTSUPP;

	if (wxfh->indiw)
		fow (i = 0; i < AWWAY_SIZE(nn->wss_itbw); i++)
			wxfh->indiw[i] = nn->wss_itbw[i];
	if (wxfh->key)
		memcpy(wxfh->key, nn->wss_key, nfp_net_wss_key_sz(nn));

	wxfh->hfunc = nn->wss_hfunc;
	if (wxfh->hfunc >= 1 << ETH_WSS_HASH_FUNCS_COUNT)
		wxfh->hfunc = ETH_WSS_HASH_UNKNOWN;

	wetuwn 0;
}

static int nfp_net_set_wxfh(stwuct net_device *netdev,
			    stwuct ethtoow_wxfh_pawam *wxfh,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int i;

	if (!(nn->cap & NFP_NET_CFG_CTWW_WSS_ANY) ||
	    !(wxfh->hfunc == ETH_WSS_HASH_NO_CHANGE ||
	      wxfh->hfunc == nn->wss_hfunc))
		wetuwn -EOPNOTSUPP;

	if (!wxfh->key && !wxfh->indiw)
		wetuwn 0;

	if (wxfh->key) {
		memcpy(nn->wss_key, wxfh->key, nfp_net_wss_key_sz(nn));
		nfp_net_wss_wwite_key(nn);
	}
	if (wxfh->indiw) {
		fow (i = 0; i < AWWAY_SIZE(nn->wss_itbw); i++)
			nn->wss_itbw[i] = wxfh->indiw[i];

		nfp_net_wss_wwite_itbw(nn);
	}

	wetuwn nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_WSS);
}

/* Dump BAW wegistews
 */
static int nfp_net_get_wegs_wen(stwuct net_device *netdev)
{
	wetuwn NFP_NET_CFG_BAW_SZ;
}

static void nfp_net_get_wegs(stwuct net_device *netdev,
			     stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	u32 *wegs_buf = p;
	int i;

	wegs->vewsion = nn_weadw(nn, NFP_NET_CFG_VEWSION);

	fow (i = 0; i < NFP_NET_CFG_BAW_SZ / sizeof(u32); i++)
		wegs_buf[i] = weadw(nn->dp.ctww_baw + (i * sizeof(u32)));
}

static int nfp_net_get_coawesce(stwuct net_device *netdev,
				stwuct ethtoow_coawesce *ec,
				stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				stwuct netwink_ext_ack *extack)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	if (!(nn->cap & NFP_NET_CFG_CTWW_IWQMOD))
		wetuwn -EOPNOTSUPP;

	ec->use_adaptive_wx_coawesce = nn->wx_coawesce_adapt_on;
	ec->use_adaptive_tx_coawesce = nn->tx_coawesce_adapt_on;

	ec->wx_coawesce_usecs       = nn->wx_coawesce_usecs;
	ec->wx_max_coawesced_fwames = nn->wx_coawesce_max_fwames;
	ec->tx_coawesce_usecs       = nn->tx_coawesce_usecs;
	ec->tx_max_coawesced_fwames = nn->tx_coawesce_max_fwames;

	wetuwn 0;
}

/* Othew debug dumps
 */
static int
nfp_dump_nsp_diag(stwuct nfp_app *app, stwuct ethtoow_dump *dump, void *buffew)
{
	stwuct nfp_wesouwce *wes;
	int wet;

	if (!app)
		wetuwn -EOPNOTSUPP;

	dump->vewsion = 1;
	dump->fwag = NFP_DUMP_NSP_DIAG;

	wes = nfp_wesouwce_acquiwe(app->cpp, NFP_WESOUWCE_NSP_DIAG);
	if (IS_EWW(wes))
		wetuwn PTW_EWW(wes);

	if (buffew) {
		if (dump->wen != nfp_wesouwce_size(wes)) {
			wet = -EINVAW;
			goto exit_wewease;
		}

		wet = nfp_cpp_wead(app->cpp, nfp_wesouwce_cpp_id(wes),
				   nfp_wesouwce_addwess(wes),
				   buffew, dump->wen);
		if (wet != dump->wen)
			wet = wet < 0 ? wet : -EIO;
		ewse
			wet = 0;
	} ewse {
		dump->wen = nfp_wesouwce_size(wes);
		wet = 0;
	}
exit_wewease:
	nfp_wesouwce_wewease(wes);

	wetuwn wet;
}

/* Set the dump fwag/wevew. Cawcuwate the dump wength fow fwag > 0 onwy (new TWV
 * based dumps), since fwag 0 (defauwt) cawcuwates the wength in
 * nfp_app_get_dump_fwag(), and we need to suppowt twiggewing a wevew 0 dump
 * without setting the fwag fiwst, fow backwawd compatibiwity.
 */
static int nfp_app_set_dump(stwuct net_device *netdev, stwuct ethtoow_dump *vaw)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	s64 wen;

	if (!app)
		wetuwn -EOPNOTSUPP;

	if (vaw->fwag == NFP_DUMP_NSP_DIAG) {
		app->pf->dump_fwag = vaw->fwag;
		wetuwn 0;
	}

	if (!app->pf->dumpspec)
		wetuwn -EOPNOTSUPP;

	wen = nfp_net_dump_cawcuwate_size(app->pf, app->pf->dumpspec,
					  vaw->fwag);
	if (wen < 0)
		wetuwn wen;

	app->pf->dump_fwag = vaw->fwag;
	app->pf->dump_wen = wen;

	wetuwn 0;
}

static int
nfp_app_get_dump_fwag(stwuct net_device *netdev, stwuct ethtoow_dump *dump)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);

	if (!app)
		wetuwn -EOPNOTSUPP;

	if (app->pf->dump_fwag == NFP_DUMP_NSP_DIAG)
		wetuwn nfp_dump_nsp_diag(app, dump, NUWW);

	dump->fwag = app->pf->dump_fwag;
	dump->wen = app->pf->dump_wen;

	wetuwn 0;
}

static int
nfp_app_get_dump_data(stwuct net_device *netdev, stwuct ethtoow_dump *dump,
		      void *buffew)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);

	if (!app)
		wetuwn -EOPNOTSUPP;

	if (app->pf->dump_fwag == NFP_DUMP_NSP_DIAG)
		wetuwn nfp_dump_nsp_diag(app, dump, buffew);

	dump->fwag = app->pf->dump_fwag;
	dump->wen = app->pf->dump_wen;

	wetuwn nfp_net_dump_popuwate_buffew(app->pf, app->pf->dumpspec, dump,
					    buffew);
}

static int
nfp_powt_get_moduwe_info(stwuct net_device *netdev,
			 stwuct ethtoow_modinfo *modinfo)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	unsigned int wead_wen;
	stwuct nfp_nsp *nsp;
	int eww = 0;
	u8 data;

	powt = nfp_powt_fwom_netdev(netdev);
	if (!powt)
		wetuwn -EOPNOTSUPP;

	/* update powt state to get watest intewface */
	set_bit(NFP_POWT_CHANGED, &powt->fwags);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	nsp = nfp_nsp_open(powt->app->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		netdev_eww(netdev, "Faiwed to access the NSP: %d\n", eww);
		wetuwn eww;
	}

	if (!nfp_nsp_has_wead_moduwe_eepwom(nsp)) {
		netdev_info(netdev, "weading moduwe EEPWOM not suppowted. Pwease update fwash\n");
		eww = -EOPNOTSUPP;
		goto exit_cwose_nsp;
	}

	switch (eth_powt->intewface) {
	case NFP_INTEWFACE_SFP:
	case NFP_INTEWFACE_SFP28:
		eww = nfp_nsp_wead_moduwe_eepwom(nsp, eth_powt->eth_index,
						 SFP_SFF8472_COMPWIANCE, &data,
						 1, &wead_wen);
		if (eww < 0)
			goto exit_cwose_nsp;

		if (!data) {
			modinfo->type = ETH_MODUWE_SFF_8079;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8079_WEN;
		} ewse {
			modinfo->type = ETH_MODUWE_SFF_8472;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		}
		bweak;
	case NFP_INTEWFACE_QSFP:
		eww = nfp_nsp_wead_moduwe_eepwom(nsp, eth_powt->eth_index,
						 SFP_SFF_WEV_COMPWIANCE, &data,
						 1, &wead_wen);
		if (eww < 0)
			goto exit_cwose_nsp;

		if (data < 0x3) {
			modinfo->type = ETH_MODUWE_SFF_8436;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		} ewse {
			modinfo->type = ETH_MODUWE_SFF_8636;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_MAX_WEN;
		}
		bweak;
	case NFP_INTEWFACE_QSFP28:
		modinfo->type = ETH_MODUWE_SFF_8636;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_MAX_WEN;
		bweak;
	defauwt:
		netdev_eww(netdev, "Unsuppowted moduwe 0x%x detected\n",
			   eth_powt->intewface);
		eww = -EINVAW;
	}

exit_cwose_nsp:
	nfp_nsp_cwose(nsp);
	wetuwn eww;
}

static int
nfp_powt_get_moduwe_eepwom(stwuct net_device *netdev,
			   stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	stwuct nfp_nsp *nsp;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	nsp = nfp_nsp_open(powt->app->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		netdev_eww(netdev, "Faiwed to access the NSP: %d\n", eww);
		wetuwn eww;
	}

	if (!nfp_nsp_has_wead_moduwe_eepwom(nsp)) {
		netdev_info(netdev, "weading moduwe EEPWOM not suppowted. Pwease update fwash\n");
		eww = -EOPNOTSUPP;
		goto exit_cwose_nsp;
	}

	eww = nfp_nsp_wead_moduwe_eepwom(nsp, eth_powt->eth_index,
					 eepwom->offset, data, eepwom->wen,
					 &eepwom->wen);
	if (eww < 0) {
		if (eepwom->wen) {
			netdev_wawn(netdev,
				    "Incompwete wead fwom moduwe EEPWOM: %d\n",
				     eww);
			eww = 0;
		} ewse {
			netdev_eww(netdev,
				   "Weading fwom moduwe EEPWOM faiwed: %d\n",
				   eww);
		}
	}

exit_cwose_nsp:
	nfp_nsp_cwose(nsp);
	wetuwn eww;
}

static int nfp_net_set_coawesce(stwuct net_device *netdev,
				stwuct ethtoow_coawesce *ec,
				stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				stwuct netwink_ext_ack *extack)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	unsigned int factow;

	/* Compute factow used to convewt coawesce '_usecs' pawametews to
	 * ME timestamp ticks.  Thewe awe 16 ME cwock cycwes fow each timestamp
	 * count.
	 */
	factow = nn->twv_caps.me_fweq_mhz / 16;

	/* Each paiw of (usecs, max_fwames) fiewds specifies that intewwupts
	 * shouwd be coawesced untiw
	 *      (usecs > 0 && time_since_fiwst_compwetion >= usecs) ||
	 *      (max_fwames > 0 && compweted_fwames >= max_fwames)
	 *
	 * It is iwwegaw to set both usecs and max_fwames to zewo as this wouwd
	 * cause intewwupts to nevew be genewated.  To disabwe coawescing, set
	 * usecs = 0 and max_fwames = 1.
	 *
	 * Some impwementations ignowe the vawue of max_fwames and use the
	 * condition time_since_fiwst_compwetion >= usecs
	 */

	if (!(nn->cap & NFP_NET_CFG_CTWW_IWQMOD))
		wetuwn -EOPNOTSUPP;

	/* ensuwe vawid configuwation */
	if (!ec->wx_coawesce_usecs && !ec->wx_max_coawesced_fwames) {
		NW_SET_EWW_MSG_MOD(extack,
				   "wx-usecs and wx-fwames cannot both be zewo");
		wetuwn -EINVAW;
	}

	if (!ec->tx_coawesce_usecs && !ec->tx_max_coawesced_fwames) {
		NW_SET_EWW_MSG_MOD(extack,
				   "tx-usecs and tx-fwames cannot both be zewo");
		wetuwn -EINVAW;
	}

	if (nfp_net_coawesce_pawa_check(ec->wx_coawesce_usecs * factow)) {
		NW_SET_EWW_MSG_MOD(extack, "wx-usecs too wawge");
		wetuwn -EINVAW;
	}

	if (nfp_net_coawesce_pawa_check(ec->wx_max_coawesced_fwames)) {
		NW_SET_EWW_MSG_MOD(extack, "wx-fwames too wawge");
		wetuwn -EINVAW;
	}

	if (nfp_net_coawesce_pawa_check(ec->tx_coawesce_usecs * factow)) {
		NW_SET_EWW_MSG_MOD(extack, "tx-usecs too wawge");
		wetuwn -EINVAW;
	}

	if (nfp_net_coawesce_pawa_check(ec->tx_max_coawesced_fwames)) {
		NW_SET_EWW_MSG_MOD(extack, "tx-fwames too wawge");
		wetuwn -EINVAW;
	}

	/* configuwation is vawid */
	nn->wx_coawesce_adapt_on = !!ec->use_adaptive_wx_coawesce;
	nn->tx_coawesce_adapt_on = !!ec->use_adaptive_tx_coawesce;

	nn->wx_coawesce_usecs      = ec->wx_coawesce_usecs;
	nn->wx_coawesce_max_fwames = ec->wx_max_coawesced_fwames;
	nn->tx_coawesce_usecs      = ec->tx_coawesce_usecs;
	nn->tx_coawesce_max_fwames = ec->tx_max_coawesced_fwames;

	/* wwite configuwation to device */
	nfp_net_coawesce_wwite_cfg(nn);
	wetuwn nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_IWQMOD);
}

static void nfp_net_get_channews(stwuct net_device *netdev,
				 stwuct ethtoow_channews *channew)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	unsigned int num_tx_wings;

	num_tx_wings = nn->dp.num_tx_wings;
	if (nn->dp.xdp_pwog)
		num_tx_wings -= nn->dp.num_wx_wings;

	channew->max_wx = min(nn->max_wx_wings, nn->max_w_vecs);
	channew->max_tx = min(nn->max_tx_wings, nn->max_w_vecs);
	channew->max_combined = min(channew->max_wx, channew->max_tx);
	channew->max_othew = NFP_NET_NON_Q_VECTOWS;
	channew->combined_count = min(nn->dp.num_wx_wings, num_tx_wings);
	channew->wx_count = nn->dp.num_wx_wings - channew->combined_count;
	channew->tx_count = num_tx_wings - channew->combined_count;
	channew->othew_count = NFP_NET_NON_Q_VECTOWS;
}

static int nfp_net_set_num_wings(stwuct nfp_net *nn, unsigned int totaw_wx,
				 unsigned int totaw_tx)
{
	stwuct nfp_net_dp *dp;

	dp = nfp_net_cwone_dp(nn);
	if (!dp)
		wetuwn -ENOMEM;

	dp->num_wx_wings = totaw_wx;
	dp->num_tx_wings = totaw_tx;
	/* nfp_net_check_config() wiww catch num_tx_wings > nn->max_tx_wings */
	if (dp->xdp_pwog)
		dp->num_tx_wings += totaw_wx;

	wetuwn nfp_net_wing_weconfig(nn, dp, NUWW);
}

static int nfp_net_set_channews(stwuct net_device *netdev,
				stwuct ethtoow_channews *channew)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	unsigned int totaw_wx, totaw_tx;

	/* Weject unsuppowted */
	if (channew->othew_count != NFP_NET_NON_Q_VECTOWS ||
	    (channew->wx_count && channew->tx_count))
		wetuwn -EINVAW;

	totaw_wx = channew->combined_count + channew->wx_count;
	totaw_tx = channew->combined_count + channew->tx_count;

	if (totaw_wx > min(nn->max_wx_wings, nn->max_w_vecs) ||
	    totaw_tx > min(nn->max_tx_wings, nn->max_w_vecs))
		wetuwn -EINVAW;

	wetuwn nfp_net_set_num_wings(nn, totaw_wx, totaw_tx);
}

static int nfp_powt_set_pausepawam(stwuct net_device *netdev,
				   stwuct ethtoow_pausepawam *pause)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	if (pause->autoneg != AUTONEG_DISABWE)
		wetuwn -EOPNOTSUPP;

	eww = nfp_eth_set_pausepawam(powt->app->cpp, eth_powt->index,
				     pause->tx_pause, pause->wx_pause);
	if (!eww)
		/* Onwy wefwesh if we did something */
		nfp_net_wefwesh_powt_tabwe(powt);

	wetuwn eww < 0 ? eww : 0;
}

static void nfp_powt_get_pausepawam(stwuct net_device *netdev,
				    stwuct ethtoow_pausepawam *pause)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn;

	/* Cuwwentwy pause fwame autoneg is fixed */
	pause->autoneg = AUTONEG_DISABWE;
	pause->wx_pause = eth_powt->wx_pause;
	pause->tx_pause = eth_powt->tx_pause;
}

static int nfp_net_set_phys_id(stwuct net_device *netdev,
			       enum ethtoow_phys_id_state state)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		/* Contwow WED to bwink */
		eww = nfp_eth_set_idmode(powt->app->cpp, eth_powt->index, 1);
		bweak;

	case ETHTOOW_ID_INACTIVE:
		/* Contwow WED to nowmaw mode */
		eww = nfp_eth_set_idmode(powt->app->cpp, eth_powt->index, 0);
		bweak;

	case ETHTOOW_ID_ON:
	case ETHTOOW_ID_OFF:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn eww;
}

#define NFP_EEPWOM_WEN ETH_AWEN

static int
nfp_net_get_eepwom_wen(stwuct net_device *netdev)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn 0;

	wetuwn NFP_EEPWOM_WEN;
}

static int
nfp_net_get_nsp_hwindex(stwuct net_device *netdev,
			stwuct nfp_nsp **nspptw,
			u32 *index)
{
	stwuct nfp_eth_tabwe_powt *eth_powt;
	stwuct nfp_powt *powt;
	stwuct nfp_nsp *nsp;
	int eww;

	powt = nfp_powt_fwom_netdev(netdev);
	eth_powt = __nfp_powt_get_eth_powt(powt);
	if (!eth_powt)
		wetuwn -EOPNOTSUPP;

	nsp = nfp_nsp_open(powt->app->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		netdev_eww(netdev, "Faiwed to access the NSP: %d\n", eww);
		wetuwn eww;
	}

	if (!nfp_nsp_has_hwinfo_wookup(nsp)) {
		netdev_eww(netdev, "NSP doesn't suppowt PF MAC genewation\n");
		nfp_nsp_cwose(nsp);
		wetuwn -EOPNOTSUPP;
	}

	*nspptw = nsp;
	*index = eth_powt->eth_index;

	wetuwn 0;
}

static int
nfp_net_get_powt_mac_by_hwinfo(stwuct net_device *netdev,
			       u8 *mac_addw)
{
	chaw hwinfo[32] = {};
	stwuct nfp_nsp *nsp;
	u32 index;
	int eww;

	eww = nfp_net_get_nsp_hwindex(netdev, &nsp, &index);
	if (eww)
		wetuwn eww;

	snpwintf(hwinfo, sizeof(hwinfo), "eth%u.mac", index);
	eww = nfp_nsp_hwinfo_wookup(nsp, hwinfo, sizeof(hwinfo));
	nfp_nsp_cwose(nsp);
	if (eww) {
		netdev_eww(netdev, "Weading pewsistent MAC addwess faiwed: %d\n",
			   eww);
		wetuwn -EOPNOTSUPP;
	}

	if (sscanf(hwinfo, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		   &mac_addw[0], &mac_addw[1], &mac_addw[2],
		   &mac_addw[3], &mac_addw[4], &mac_addw[5]) != 6) {
		netdev_eww(netdev, "Can't pawse pewsistent MAC addwess (%s)\n",
			   hwinfo);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nfp_net_set_powt_mac_by_hwinfo(stwuct net_device *netdev,
			       u8 *mac_addw)
{
	chaw hwinfo[32] = {};
	stwuct nfp_nsp *nsp;
	u32 index;
	int eww;

	eww = nfp_net_get_nsp_hwindex(netdev, &nsp, &index);
	if (eww)
		wetuwn eww;

	snpwintf(hwinfo, sizeof(hwinfo),
		 "eth%u.mac=%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
		 index, mac_addw[0], mac_addw[1], mac_addw[2], mac_addw[3],
		 mac_addw[4], mac_addw[5]);

	eww = nfp_nsp_hwinfo_set(nsp, hwinfo, sizeof(hwinfo));
	nfp_nsp_cwose(nsp);
	if (eww) {
		netdev_eww(netdev, "HWinfo set faiwed: %d, hwinfo: %s\n",
			   eww, hwinfo);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nfp_net_get_eepwom(stwuct net_device *netdev,
		   stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	u8 buf[NFP_EEPWOM_WEN] = {};

	if (nfp_net_get_powt_mac_by_hwinfo(netdev, buf))
		wetuwn -EOPNOTSUPP;

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	eepwom->magic = app->pdev->vendow | (app->pdev->device << 16);
	memcpy(bytes, buf + eepwom->offset, eepwom->wen);

	wetuwn 0;
}

static int
nfp_net_set_eepwom(stwuct net_device *netdev,
		   stwuct ethtoow_eepwom *eepwom, u8 *bytes)
{
	stwuct nfp_app *app = nfp_app_fwom_netdev(netdev);
	u8 buf[NFP_EEPWOM_WEN] = {};

	if (nfp_net_get_powt_mac_by_hwinfo(netdev, buf))
		wetuwn -EOPNOTSUPP;

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	if (eepwom->magic != (app->pdev->vendow | app->pdev->device << 16))
		wetuwn -EINVAW;

	memcpy(buf + eepwom->offset, bytes, eepwom->wen);
	if (nfp_net_set_powt_mac_by_hwinfo(netdev, buf))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static const stwuct ethtoow_ops nfp_net_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE,
	.get_dwvinfo		= nfp_net_get_dwvinfo,
	.nway_weset             = nfp_net_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_wingpawam		= nfp_net_get_wingpawam,
	.set_wingpawam		= nfp_net_set_wingpawam,
	.sewf_test		= nfp_net_sewf_test,
	.get_stwings		= nfp_net_get_stwings,
	.get_ethtoow_stats	= nfp_net_get_stats,
	.get_sset_count		= nfp_net_get_sset_count,
	.get_wxnfc		= nfp_net_get_wxnfc,
	.set_wxnfc		= nfp_net_set_wxnfc,
	.get_wxfh_indiw_size	= nfp_net_get_wxfh_indiw_size,
	.get_wxfh_key_size	= nfp_net_get_wxfh_key_size,
	.get_wxfh		= nfp_net_get_wxfh,
	.set_wxfh		= nfp_net_set_wxfh,
	.get_wegs_wen		= nfp_net_get_wegs_wen,
	.get_wegs		= nfp_net_get_wegs,
	.set_dump		= nfp_app_set_dump,
	.get_dump_fwag		= nfp_app_get_dump_fwag,
	.get_dump_data		= nfp_app_get_dump_data,
	.get_eepwom_wen         = nfp_net_get_eepwom_wen,
	.get_eepwom             = nfp_net_get_eepwom,
	.set_eepwom             = nfp_net_set_eepwom,
	.get_moduwe_info	= nfp_powt_get_moduwe_info,
	.get_moduwe_eepwom	= nfp_powt_get_moduwe_eepwom,
	.get_coawesce           = nfp_net_get_coawesce,
	.set_coawesce           = nfp_net_set_coawesce,
	.get_channews		= nfp_net_get_channews,
	.set_channews		= nfp_net_set_channews,
	.get_wink_ksettings	= nfp_net_get_wink_ksettings,
	.set_wink_ksettings	= nfp_net_set_wink_ksettings,
	.get_fecpawam		= nfp_powt_get_fecpawam,
	.set_fecpawam		= nfp_powt_set_fecpawam,
	.set_pausepawam		= nfp_powt_set_pausepawam,
	.get_pausepawam		= nfp_powt_get_pausepawam,
	.set_phys_id		= nfp_net_set_phys_id,
	.get_ts_info		= ethtoow_op_get_ts_info,
};

const stwuct ethtoow_ops nfp_powt_ethtoow_ops = {
	.get_dwvinfo		= nfp_app_get_dwvinfo,
	.nway_weset             = nfp_net_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= nfp_powt_get_stwings,
	.get_ethtoow_stats	= nfp_powt_get_stats,
	.sewf_test		= nfp_net_sewf_test,
	.get_sset_count		= nfp_powt_get_sset_count,
	.set_dump		= nfp_app_set_dump,
	.get_dump_fwag		= nfp_app_get_dump_fwag,
	.get_dump_data		= nfp_app_get_dump_data,
	.get_eepwom_wen         = nfp_net_get_eepwom_wen,
	.get_eepwom             = nfp_net_get_eepwom,
	.set_eepwom             = nfp_net_set_eepwom,
	.get_moduwe_info	= nfp_powt_get_moduwe_info,
	.get_moduwe_eepwom	= nfp_powt_get_moduwe_eepwom,
	.get_wink_ksettings	= nfp_net_get_wink_ksettings,
	.set_wink_ksettings	= nfp_net_set_wink_ksettings,
	.get_fecpawam		= nfp_powt_get_fecpawam,
	.set_fecpawam		= nfp_powt_set_fecpawam,
	.set_pausepawam		= nfp_powt_set_pausepawam,
	.get_pausepawam		= nfp_powt_get_pausepawam,
	.set_phys_id		= nfp_net_set_phys_id,
};

void nfp_net_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &nfp_net_ethtoow_ops;
}
