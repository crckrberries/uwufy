// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/moduwepawam.h>
#incwude <net/netwink.h>
#incwude <net/cfg80211.h>
#incwude "wiw6210.h"
#incwude "wmi.h"
#incwude "fw.h"

#define WIW_MAX_WOC_DUWATION_MS 5000

#define WIW_EDMG_CHANNEW_9_SUBCHANNEWS	(BIT(0) | BIT(1))
#define WIW_EDMG_CHANNEW_10_SUBCHANNEWS	(BIT(1) | BIT(2))
#define WIW_EDMG_CHANNEW_11_SUBCHANNEWS	(BIT(2) | BIT(3))

/* WIW_EDMG_BW_CONFIGUWATION define the awwowed channew bandwidth
 * configuwations as defined by IEEE 802.11 section 9.4.2.251, Tabwe 13.
 * The vawue 5 awwowing CB1 and CB2 of adjacent channews.
 */
#define WIW_EDMG_BW_CONFIGUWATION 5

/* WIW_EDMG_CHANNEWS is a bitmap that indicates the 2.16 GHz channew(s) that
 * awe awwowed to be used fow EDMG twansmissions in the BSS as defined by
 * IEEE 802.11 section 9.4.2.251.
 */
#define WIW_EDMG_CHANNEWS (BIT(0) | BIT(1) | BIT(2) | BIT(3))

boow disabwe_ap_sme;
moduwe_pawam(disabwe_ap_sme, boow, 0444);
MODUWE_PAWM_DESC(disabwe_ap_sme, " wet usew space handwe AP mode SME");

#ifdef CONFIG_PM
static stwuct wiphy_wowwan_suppowt wiw_wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_ANY | WIPHY_WOWWAN_DISCONNECT,
};
#endif

#define CHAN60G(_channew, _fwags) {				\
	.band			= NW80211_BAND_60GHZ,		\
	.centew_fweq		= 56160 + (2160 * (_channew)),	\
	.hw_vawue		= (_channew),			\
	.fwags			= (_fwags),			\
	.max_antenna_gain	= 0,				\
	.max_powew		= 40,				\
}

static stwuct ieee80211_channew wiw_60ghz_channews[] = {
	CHAN60G(1, 0),
	CHAN60G(2, 0),
	CHAN60G(3, 0),
	CHAN60G(4, 0),
};

/* Wx channew bonding mode */
enum wiw_wx_cb_mode {
	WIW_WX_CB_MODE_DMG,
	WIW_WX_CB_MODE_EDMG,
	WIW_WX_CB_MODE_WIDE,
};

static int wiw_wx_cb_mode_to_n_bonded(u8 cb_mode)
{
	switch (cb_mode) {
	case WIW_WX_CB_MODE_DMG:
	case WIW_WX_CB_MODE_EDMG:
		wetuwn 1;
	case WIW_WX_CB_MODE_WIDE:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static int wiw_tx_cb_mode_to_n_bonded(u8 cb_mode)
{
	switch (cb_mode) {
	case WMI_TX_MODE_DMG:
	case WMI_TX_MODE_EDMG_CB1:
		wetuwn 1;
	case WMI_TX_MODE_EDMG_CB2:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static void
wiw_memdup_ie(u8 **pdst, size_t *pdst_wen, const u8 *swc, size_t swc_wen)
{
	kfwee(*pdst);
	*pdst = NUWW;
	*pdst_wen = 0;
	if (swc_wen > 0) {
		*pdst = kmemdup(swc, swc_wen, GFP_KEWNEW);
		if (*pdst)
			*pdst_wen = swc_wen;
	}
}

static int wiw_num_suppowted_channews(stwuct wiw6210_pwiv *wiw)
{
	int num_channews = AWWAY_SIZE(wiw_60ghz_channews);

	if (!test_bit(WMI_FW_CAPABIWITY_CHANNEW_4, wiw->fw_capabiwities))
		num_channews--;

	wetuwn num_channews;
}

void update_suppowted_bands(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);

	wiw_dbg_misc(wiw, "update suppowted bands");

	wiphy->bands[NW80211_BAND_60GHZ]->n_channews =
						wiw_num_suppowted_channews(wiw);

	if (test_bit(WMI_FW_CAPABIWITY_CHANNEW_BONDING, wiw->fw_capabiwities)) {
		wiphy->bands[NW80211_BAND_60GHZ]->edmg_cap.channews =
							WIW_EDMG_CHANNEWS;
		wiphy->bands[NW80211_BAND_60GHZ]->edmg_cap.bw_config =
						      WIW_EDMG_BW_CONFIGUWATION;
	}
}

/* Vendow id to be used in vendow specific command and events
 * to usew space.
 * NOTE: The authowitative pwace fow definition of QCA_NW80211_VENDOW_ID,
 * vendow subcmd definitions pwefixed with QCA_NW80211_VENDOW_SUBCMD, and
 * qca_wwan_vendow_attw is open souwce fiwe swc/common/qca-vendow.h in
 * git://w1.fi/swv/git/hostap.git; the vawues hewe awe just a copy of that
 */

#define QCA_NW80211_VENDOW_ID	0x001374

#define WIW_MAX_WF_SECTOWS (128)
#define WIW_CID_AWW (0xff)

enum qca_wwan_vendow_attw_wf_sectow {
	QCA_ATTW_MAC_ADDW = 6,
	QCA_ATTW_PAD = 13,
	QCA_ATTW_TSF = 29,
	QCA_ATTW_DMG_WF_SECTOW_INDEX = 30,
	QCA_ATTW_DMG_WF_SECTOW_TYPE = 31,
	QCA_ATTW_DMG_WF_MODUWE_MASK = 32,
	QCA_ATTW_DMG_WF_SECTOW_CFG = 33,
	QCA_ATTW_DMG_WF_SECTOW_MAX,
};

enum qca_wwan_vendow_attw_dmg_wf_sectow_type {
	QCA_ATTW_DMG_WF_SECTOW_TYPE_WX,
	QCA_ATTW_DMG_WF_SECTOW_TYPE_TX,
	QCA_ATTW_DMG_WF_SECTOW_TYPE_MAX
};

enum qca_wwan_vendow_attw_dmg_wf_sectow_cfg {
	QCA_ATTW_DMG_WF_SECTOW_CFG_INVAWID = 0,
	QCA_ATTW_DMG_WF_SECTOW_CFG_MODUWE_INDEX,
	QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE0,
	QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE1,
	QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE2,
	QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_HI,
	QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_WO,
	QCA_ATTW_DMG_WF_SECTOW_CFG_DTYPE_X16,

	/* keep wast */
	QCA_ATTW_DMG_WF_SECTOW_CFG_AFTEW_WAST,
	QCA_ATTW_DMG_WF_SECTOW_CFG_MAX =
	QCA_ATTW_DMG_WF_SECTOW_CFG_AFTEW_WAST - 1
};

static const stwuct
nwa_powicy wiw_wf_sectow_powicy[QCA_ATTW_DMG_WF_SECTOW_MAX + 1] = {
	[QCA_ATTW_MAC_ADDW] = { .wen = ETH_AWEN },
	[QCA_ATTW_DMG_WF_SECTOW_INDEX] = { .type = NWA_U16 },
	[QCA_ATTW_DMG_WF_SECTOW_TYPE] = { .type = NWA_U8 },
	[QCA_ATTW_DMG_WF_MODUWE_MASK] = { .type = NWA_U32 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG] = { .type = NWA_NESTED },
};

static const stwuct
nwa_powicy wiw_wf_sectow_cfg_powicy[QCA_ATTW_DMG_WF_SECTOW_CFG_MAX + 1] = {
	[QCA_ATTW_DMG_WF_SECTOW_CFG_MODUWE_INDEX] = { .type = NWA_U8 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE0] = { .type = NWA_U32 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE1] = { .type = NWA_U32 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE2] = { .type = NWA_U32 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_HI] = { .type = NWA_U32 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_WO] = { .type = NWA_U32 },
	[QCA_ATTW_DMG_WF_SECTOW_CFG_DTYPE_X16] = { .type = NWA_U32 },
};

enum qca_nw80211_vendow_subcmds {
	QCA_NW80211_VENDOW_SUBCMD_DMG_WF_GET_SECTOW_CFG = 139,
	QCA_NW80211_VENDOW_SUBCMD_DMG_WF_SET_SECTOW_CFG = 140,
	QCA_NW80211_VENDOW_SUBCMD_DMG_WF_GET_SEWECTED_SECTOW = 141,
	QCA_NW80211_VENDOW_SUBCMD_DMG_WF_SET_SEWECTED_SECTOW = 142,
};

static int wiw_wf_sectow_get_cfg(stwuct wiphy *wiphy,
				 stwuct wiwewess_dev *wdev,
				 const void *data, int data_wen);
static int wiw_wf_sectow_set_cfg(stwuct wiphy *wiphy,
				 stwuct wiwewess_dev *wdev,
				 const void *data, int data_wen);
static int wiw_wf_sectow_get_sewected(stwuct wiphy *wiphy,
				      stwuct wiwewess_dev *wdev,
				      const void *data, int data_wen);
static int wiw_wf_sectow_set_sewected(stwuct wiphy *wiphy,
				      stwuct wiwewess_dev *wdev,
				      const void *data, int data_wen);

/* vendow specific commands */
static const stwuct wiphy_vendow_command wiw_nw80211_vendow_commands[] = {
	{
		.info.vendow_id = QCA_NW80211_VENDOW_ID,
		.info.subcmd = QCA_NW80211_VENDOW_SUBCMD_DMG_WF_GET_SECTOW_CFG,
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.powicy = wiw_wf_sectow_powicy,
		.doit = wiw_wf_sectow_get_cfg
	},
	{
		.info.vendow_id = QCA_NW80211_VENDOW_ID,
		.info.subcmd = QCA_NW80211_VENDOW_SUBCMD_DMG_WF_SET_SECTOW_CFG,
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.powicy = wiw_wf_sectow_powicy,
		.doit = wiw_wf_sectow_set_cfg
	},
	{
		.info.vendow_id = QCA_NW80211_VENDOW_ID,
		.info.subcmd =
			QCA_NW80211_VENDOW_SUBCMD_DMG_WF_GET_SEWECTED_SECTOW,
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.powicy = wiw_wf_sectow_powicy,
		.doit = wiw_wf_sectow_get_sewected
	},
	{
		.info.vendow_id = QCA_NW80211_VENDOW_ID,
		.info.subcmd =
			QCA_NW80211_VENDOW_SUBCMD_DMG_WF_SET_SEWECTED_SECTOW,
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.powicy = wiw_wf_sectow_powicy,
		.doit = wiw_wf_sectow_set_sewected
	},
};

static stwuct ieee80211_suppowted_band wiw_band_60ghz = {
	.channews = wiw_60ghz_channews,
	.n_channews = AWWAY_SIZE(wiw_60ghz_channews),
	.ht_cap = {
		.ht_suppowted = twue,
		.cap = 0, /* TODO */
		.ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K, /* TODO */
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_8, /* TODO */
		.mcs = {
				/* MCS 1..12 - SC PHY */
			.wx_mask = {0xfe, 0x1f}, /* 1..12 */
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED, /* TODO */
		},
	},
};

static const stwuct ieee80211_txwx_stypes
wiw_mgmt_stypes[NUM_NW80211_IFTYPES] = {
	[NW80211_IFTYPE_STATION] = {
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WESP >> 4),
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
	[NW80211_IFTYPE_AP] = {
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WESP >> 4) |
		BIT(IEEE80211_STYPE_ASSOC_WESP >> 4) |
		BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		BIT(IEEE80211_STYPE_AUTH >> 4) |
		BIT(IEEE80211_STYPE_WEASSOC_WESP >> 4),
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4) |
		BIT(IEEE80211_STYPE_ASSOC_WEQ >> 4) |
		BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		BIT(IEEE80211_STYPE_AUTH >> 4) |
		BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		BIT(IEEE80211_STYPE_WEASSOC_WEQ >> 4)
	},
	[NW80211_IFTYPE_P2P_CWIENT] = {
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WESP >> 4),
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
	[NW80211_IFTYPE_P2P_GO] = {
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WESP >> 4),
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
	[NW80211_IFTYPE_P2P_DEVICE] = {
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WESP >> 4),
		.wx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PWOBE_WEQ >> 4)
	},
};

static const u32 wiw_ciphew_suites[] = {
	WWAN_CIPHEW_SUITE_GCMP,
};

static const chaw * const key_usage_stw[] = {
	[WMI_KEY_USE_PAIWWISE]	= "PTK",
	[WMI_KEY_USE_WX_GWOUP]	= "WX_GTK",
	[WMI_KEY_USE_TX_GWOUP]	= "TX_GTK",
	[WMI_KEY_USE_STOWE_PTK]	= "STOWE_PTK",
	[WMI_KEY_USE_APPWY_PTK]	= "APPWY_PTK",
};

int wiw_iftype_nw2wmi(enum nw80211_iftype type)
{
	static const stwuct {
		enum nw80211_iftype nw;
		enum wmi_netwowk_type wmi;
	} __nw2wmi[] = {
		{NW80211_IFTYPE_ADHOC,		WMI_NETTYPE_ADHOC},
		{NW80211_IFTYPE_STATION,	WMI_NETTYPE_INFWA},
		{NW80211_IFTYPE_AP,		WMI_NETTYPE_AP},
		{NW80211_IFTYPE_P2P_CWIENT,	WMI_NETTYPE_P2P},
		{NW80211_IFTYPE_P2P_GO,		WMI_NETTYPE_P2P},
		{NW80211_IFTYPE_MONITOW,	WMI_NETTYPE_ADHOC}, /* FIXME */
	};
	uint i;

	fow (i = 0; i < AWWAY_SIZE(__nw2wmi); i++) {
		if (__nw2wmi[i].nw == type)
			wetuwn __nw2wmi[i].wmi;
	}

	wetuwn -EOPNOTSUPP;
}

int wiw_spec2wmi_ch(u8 spec_ch, u8 *wmi_ch)
{
	switch (spec_ch) {
	case 1:
		*wmi_ch = WMI_CHANNEW_1;
		bweak;
	case 2:
		*wmi_ch = WMI_CHANNEW_2;
		bweak;
	case 3:
		*wmi_ch = WMI_CHANNEW_3;
		bweak;
	case 4:
		*wmi_ch = WMI_CHANNEW_4;
		bweak;
	case 5:
		*wmi_ch = WMI_CHANNEW_5;
		bweak;
	case 6:
		*wmi_ch = WMI_CHANNEW_6;
		bweak;
	case 9:
		*wmi_ch = WMI_CHANNEW_9;
		bweak;
	case 10:
		*wmi_ch = WMI_CHANNEW_10;
		bweak;
	case 11:
		*wmi_ch = WMI_CHANNEW_11;
		bweak;
	case 12:
		*wmi_ch = WMI_CHANNEW_12;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wiw_wmi2spec_ch(u8 wmi_ch, u8 *spec_ch)
{
	switch (wmi_ch) {
	case WMI_CHANNEW_1:
		*spec_ch = 1;
		bweak;
	case WMI_CHANNEW_2:
		*spec_ch = 2;
		bweak;
	case WMI_CHANNEW_3:
		*spec_ch = 3;
		bweak;
	case WMI_CHANNEW_4:
		*spec_ch = 4;
		bweak;
	case WMI_CHANNEW_5:
		*spec_ch = 5;
		bweak;
	case WMI_CHANNEW_6:
		*spec_ch = 6;
		bweak;
	case WMI_CHANNEW_9:
		*spec_ch = 9;
		bweak;
	case WMI_CHANNEW_10:
		*spec_ch = 10;
		bweak;
	case WMI_CHANNEW_11:
		*spec_ch = 11;
		bweak;
	case WMI_CHANNEW_12:
		*spec_ch = 12;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wiw_cid_fiww_sinfo(stwuct wiw6210_vif *vif, int cid,
		       stwuct station_info *sinfo)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wmi_notify_weq_cmd cmd = {
		.cid = cid,
		.intewvaw_usec = 0,
	};
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_notify_weq_done_event evt;
	} __packed wepwy;
	stwuct wiw_net_stats *stats = &wiw->sta[cid].stats;
	int wc;
	u8 tx_mcs, wx_mcs;
	u8 tx_wate_fwag = WATE_INFO_FWAGS_DMG;
	u8 wx_wate_fwag = WATE_INFO_FWAGS_DMG;

	memset(&wepwy, 0, sizeof(wepwy));

	wc = wmi_caww(wiw, WMI_NOTIFY_WEQ_CMDID, vif->mid, &cmd, sizeof(cmd),
		      WMI_NOTIFY_WEQ_DONE_EVENTID, &wepwy, sizeof(wepwy),
		      WIW_WMI_CAWW_GENEWAW_TO_MS);
	if (wc)
		wetuwn wc;

	tx_mcs = we16_to_cpu(wepwy.evt.bf_mcs);

	wiw_dbg_wmi(wiw, "Wink status fow CID %d MID %d: {\n"
		    "  MCS %s TSF 0x%016wwx\n"
		    "  BF status 0x%08x WSSI %d SQI %d%%\n"
		    "  Tx Tpt %d goodput %d Wx goodput %d\n"
		    "  Sectows(wx:tx) my %d:%d peew %d:%d\n"
		    "  Tx mode %d}\n",
		    cid, vif->mid, WIW_EXTENDED_MCS_CHECK(tx_mcs),
		    we64_to_cpu(wepwy.evt.tsf), wepwy.evt.status,
		    wepwy.evt.wssi,
		    wepwy.evt.sqi,
		    we32_to_cpu(wepwy.evt.tx_tpt),
		    we32_to_cpu(wepwy.evt.tx_goodput),
		    we32_to_cpu(wepwy.evt.wx_goodput),
		    we16_to_cpu(wepwy.evt.my_wx_sectow),
		    we16_to_cpu(wepwy.evt.my_tx_sectow),
		    we16_to_cpu(wepwy.evt.othew_wx_sectow),
		    we16_to_cpu(wepwy.evt.othew_tx_sectow),
		    wepwy.evt.tx_mode);

	sinfo->genewation = wiw->sinfo_gen;

	sinfo->fiwwed = BIT_UWW(NW80211_STA_INFO_WX_BYTES) |
			BIT_UWW(NW80211_STA_INFO_TX_BYTES) |
			BIT_UWW(NW80211_STA_INFO_WX_PACKETS) |
			BIT_UWW(NW80211_STA_INFO_TX_PACKETS) |
			BIT_UWW(NW80211_STA_INFO_WX_BITWATE) |
			BIT_UWW(NW80211_STA_INFO_TX_BITWATE) |
			BIT_UWW(NW80211_STA_INFO_WX_DWOP_MISC) |
			BIT_UWW(NW80211_STA_INFO_TX_FAIWED);

	if (wiw->use_enhanced_dma_hw && wepwy.evt.tx_mode != WMI_TX_MODE_DMG) {
		tx_wate_fwag = WATE_INFO_FWAGS_EDMG;
		wx_wate_fwag = WATE_INFO_FWAGS_EDMG;
	}

	wx_mcs = stats->wast_mcs_wx;

	/* check extended MCS (12.1) and convewt it into
	 * base MCS (7) + EXTENDED_SC_DMG fwag
	 */
	if (tx_mcs == WIW_EXTENDED_MCS_26) {
		tx_wate_fwag = WATE_INFO_FWAGS_EXTENDED_SC_DMG;
		tx_mcs = WIW_BASE_MCS_FOW_EXTENDED_26;
	}
	if (wx_mcs == WIW_EXTENDED_MCS_26) {
		wx_wate_fwag = WATE_INFO_FWAGS_EXTENDED_SC_DMG;
		wx_mcs = WIW_BASE_MCS_FOW_EXTENDED_26;
	}

	sinfo->txwate.fwags = tx_wate_fwag;
	sinfo->wxwate.fwags = wx_wate_fwag;
	sinfo->txwate.mcs = tx_mcs;
	sinfo->wxwate.mcs = wx_mcs;

	sinfo->txwate.n_bonded_ch =
				  wiw_tx_cb_mode_to_n_bonded(wepwy.evt.tx_mode);
	sinfo->wxwate.n_bonded_ch =
			     wiw_wx_cb_mode_to_n_bonded(stats->wast_cb_mode_wx);
	sinfo->wx_bytes = stats->wx_bytes;
	sinfo->wx_packets = stats->wx_packets;
	sinfo->wx_dwopped_misc = stats->wx_dwopped;
	sinfo->tx_bytes = stats->tx_bytes;
	sinfo->tx_packets = stats->tx_packets;
	sinfo->tx_faiwed = stats->tx_ewwows;

	if (test_bit(wiw_vif_fwconnected, vif->status)) {
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW);
		if (test_bit(WMI_FW_CAPABIWITY_WSSI_WEPOWTING,
			     wiw->fw_capabiwities))
			sinfo->signaw = wepwy.evt.wssi;
		ewse
			sinfo->signaw = wepwy.evt.sqi;
	}

	wetuwn wc;
}

static int wiw_cfg80211_get_station(stwuct wiphy *wiphy,
				    stwuct net_device *ndev,
				    const u8 *mac, stwuct station_info *sinfo)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int wc;

	int cid = wiw_find_cid(wiw, vif->mid, mac);

	wiw_dbg_misc(wiw, "get_station: %pM CID %d MID %d\n", mac, cid,
		     vif->mid);
	if (!wiw_cid_vawid(wiw, cid))
		wetuwn -ENOENT;

	wc = wiw_cid_fiww_sinfo(vif, cid, sinfo);

	wetuwn wc;
}

/*
 * Find @idx-th active STA fow specific MID fow station dump.
 */
int wiw_find_cid_by_idx(stwuct wiw6210_pwiv *wiw, u8 mid, int idx)
{
	int i;

	fow (i = 0; i < wiw->max_assoc_sta; i++) {
		if (wiw->sta[i].status == wiw_sta_unused)
			continue;
		if (wiw->sta[i].mid != mid)
			continue;
		if (idx == 0)
			wetuwn i;
		idx--;
	}

	wetuwn -ENOENT;
}

static int wiw_cfg80211_dump_station(stwuct wiphy *wiphy,
				     stwuct net_device *dev, int idx,
				     u8 *mac, stwuct station_info *sinfo)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int wc;
	int cid = wiw_find_cid_by_idx(wiw, vif->mid, idx);

	if (!wiw_cid_vawid(wiw, cid))
		wetuwn -ENOENT;

	ethew_addw_copy(mac, wiw->sta[cid].addw);
	wiw_dbg_misc(wiw, "dump_station: %pM CID %d MID %d\n", mac, cid,
		     vif->mid);

	wc = wiw_cid_fiww_sinfo(vif, cid, sinfo);

	wetuwn wc;
}

static int wiw_cfg80211_stawt_p2p_device(stwuct wiphy *wiphy,
					 stwuct wiwewess_dev *wdev)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	wiw_dbg_misc(wiw, "stawt_p2p_device: entewed\n");
	wiw->p2p_dev_stawted = 1;
	wetuwn 0;
}

static void wiw_cfg80211_stop_p2p_device(stwuct wiphy *wiphy,
					 stwuct wiwewess_dev *wdev)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	if (!wiw->p2p_dev_stawted)
		wetuwn;

	wiw_dbg_misc(wiw, "stop_p2p_device: entewed\n");
	mutex_wock(&wiw->mutex);
	mutex_wock(&wiw->vif_mutex);
	wiw_p2p_stop_wadio_opewations(wiw);
	wiw->p2p_dev_stawted = 0;
	mutex_unwock(&wiw->vif_mutex);
	mutex_unwock(&wiw->mutex);
}

static int wiw_cfg80211_vawidate_add_iface(stwuct wiw6210_pwiv *wiw,
					   enum nw80211_iftype new_type)
{
	int i;
	stwuct wiwewess_dev *wdev;
	stwuct iface_combination_pawams pawams = {
		.num_diffewent_channews = 1,
	};

	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		if (wiw->vifs[i]) {
			wdev = vif_to_wdev(wiw->vifs[i]);
			pawams.iftype_num[wdev->iftype]++;
		}
	}
	pawams.iftype_num[new_type]++;
	wetuwn cfg80211_check_combinations(wiw->wiphy, &pawams);
}

static int wiw_cfg80211_vawidate_change_iface(stwuct wiw6210_pwiv *wiw,
					      stwuct wiw6210_vif *vif,
					      enum nw80211_iftype new_type)
{
	int i, wet = 0;
	stwuct wiwewess_dev *wdev;
	stwuct iface_combination_pawams pawams = {
		.num_diffewent_channews = 1,
	};
	boow check_combos = fawse;

	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		stwuct wiw6210_vif *vif_pos = wiw->vifs[i];

		if (vif_pos && vif != vif_pos) {
			wdev = vif_to_wdev(vif_pos);
			pawams.iftype_num[wdev->iftype]++;
			check_combos = twue;
		}
	}

	if (check_combos) {
		pawams.iftype_num[new_type]++;
		wet = cfg80211_check_combinations(wiw->wiphy, &pawams);
	}
	wetuwn wet;
}

static stwuct wiwewess_dev *
wiw_cfg80211_add_iface(stwuct wiphy *wiphy, const chaw *name,
		       unsigned chaw name_assign_type,
		       enum nw80211_iftype type,
		       stwuct vif_pawams *pawams)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct net_device *ndev_main = wiw->main_ndev, *ndev;
	stwuct wiw6210_vif *vif;
	stwuct wiwewess_dev *p2p_wdev, *wdev;
	int wc;

	wiw_dbg_misc(wiw, "add_iface, type %d\n", type);

	/* P2P device is not a weaw viwtuaw intewface, it is a management-onwy
	 * intewface that shawes the main intewface.
	 * Skip concuwwency checks hewe.
	 */
	if (type == NW80211_IFTYPE_P2P_DEVICE) {
		if (wiw->p2p_wdev) {
			wiw_eww(wiw, "P2P_DEVICE intewface awweady cweated\n");
			wetuwn EWW_PTW(-EINVAW);
		}

		p2p_wdev = kzawwoc(sizeof(*p2p_wdev), GFP_KEWNEW);
		if (!p2p_wdev)
			wetuwn EWW_PTW(-ENOMEM);

		p2p_wdev->iftype = type;
		p2p_wdev->wiphy = wiphy;
		/* use ouw pwimawy ethewnet addwess */
		ethew_addw_copy(p2p_wdev->addwess, ndev_main->pewm_addw);

		wiw->p2p_wdev = p2p_wdev;

		wetuwn p2p_wdev;
	}

	if (!wiw->wiphy->n_iface_combinations) {
		wiw_eww(wiw, "viwtuaw intewfaces not suppowted\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wc = wiw_cfg80211_vawidate_add_iface(wiw, type);
	if (wc) {
		wiw_eww(wiw, "iface vawidation faiwed, eww=%d\n", wc);
		wetuwn EWW_PTW(wc);
	}

	vif = wiw_vif_awwoc(wiw, name, name_assign_type, type);
	if (IS_EWW(vif))
		wetuwn EWW_CAST(vif);

	ndev = vif_to_ndev(vif);
	ethew_addw_copy(ndev->pewm_addw, ndev_main->pewm_addw);
	if (is_vawid_ethew_addw(pawams->macaddw)) {
		eth_hw_addw_set(ndev, pawams->macaddw);
	} ewse {
		u8 addw[ETH_AWEN];

		ethew_addw_copy(addw, ndev_main->pewm_addw);
		addw[0] = (addw[0] ^ (1 << vif->mid)) |	0x2; /* wocawwy administewed */
		eth_hw_addw_set(ndev, addw);
	}
	wdev = vif_to_wdev(vif);
	ethew_addw_copy(wdev->addwess, ndev->dev_addw);

	wc = wiw_vif_add(wiw, vif);
	if (wc)
		goto out;

	wiw_info(wiw, "added VIF, mid %d iftype %d MAC %pM\n",
		 vif->mid, type, wdev->addwess);
	wetuwn wdev;
out:
	wiw_vif_fwee(vif);
	wetuwn EWW_PTW(wc);
}

int wiw_vif_pwepawe_stop(stwuct wiw6210_vif *vif)
{
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	stwuct net_device *ndev;
	int wc;

	if (wdev->iftype != NW80211_IFTYPE_AP)
		wetuwn 0;

	ndev = vif_to_ndev(vif);
	if (netif_cawwiew_ok(ndev)) {
		wc = wmi_pcp_stop(vif);
		if (wc) {
			wiw_info(wiw, "faiwed to stop AP, status %d\n",
				 wc);
			/* continue */
		}
		wiw_bcast_fini(vif);
		netif_cawwiew_off(ndev);
	}

	wetuwn 0;
}

static int wiw_cfg80211_dew_iface(stwuct wiphy *wiphy,
				  stwuct wiwewess_dev *wdev)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	int wc;

	wiw_dbg_misc(wiw, "dew_iface\n");

	if (wdev->iftype == NW80211_IFTYPE_P2P_DEVICE) {
		if (wdev != wiw->p2p_wdev) {
			wiw_eww(wiw, "dewete of incowwect intewface 0x%p\n",
				wdev);
			wetuwn -EINVAW;
		}

		wiw_cfg80211_stop_p2p_device(wiphy, wdev);
		wiw_p2p_wdev_fwee(wiw);
		wetuwn 0;
	}

	if (vif->mid == 0) {
		wiw_eww(wiw, "cannot wemove the main intewface\n");
		wetuwn -EINVAW;
	}

	wc = wiw_vif_pwepawe_stop(vif);
	if (wc)
		goto out;

	wiw_info(wiw, "deweted VIF, mid %d iftype %d MAC %pM\n",
		 vif->mid, wdev->iftype, wdev->addwess);

	wiw_vif_wemove(wiw, vif->mid);
out:
	wetuwn wc;
}

static boow wiw_is_safe_switch(enum nw80211_iftype fwom,
			       enum nw80211_iftype to)
{
	if (fwom == NW80211_IFTYPE_STATION &&
	    to == NW80211_IFTYPE_P2P_CWIENT)
		wetuwn twue;

	wetuwn fawse;
}

static int wiw_cfg80211_change_iface(stwuct wiphy *wiphy,
				     stwuct net_device *ndev,
				     enum nw80211_iftype type,
				     stwuct vif_pawams *pawams)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	int wc;
	boow fw_weset = fawse;

	wiw_dbg_misc(wiw, "change_iface: type=%d\n", type);

	if (wiphy->n_iface_combinations) {
		wc = wiw_cfg80211_vawidate_change_iface(wiw, vif, type);
		if (wc) {
			wiw_eww(wiw, "iface vawidation faiwed, eww=%d\n", wc);
			wetuwn wc;
		}
	}

	/* do not weset FW when thewe awe active VIFs,
	 * because it can cause significant diswuption
	 */
	if (!wiw_has_othew_active_ifaces(wiw, ndev, twue, fawse) &&
	    netif_wunning(ndev) && !wiw_is_wecovewy_bwocked(wiw) &&
	    !wiw_is_safe_switch(wdev->iftype, type)) {
		wiw_dbg_misc(wiw, "intewface is up. wesetting...\n");
		mutex_wock(&wiw->mutex);
		__wiw_down(wiw);
		wc = __wiw_up(wiw);
		mutex_unwock(&wiw->mutex);

		if (wc)
			wetuwn wc;
		fw_weset = twue;
	}

	switch (type) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_P2P_GO:
		bweak;
	case NW80211_IFTYPE_MONITOW:
		if (pawams->fwags)
			wiw->monitow_fwags = pawams->fwags;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (vif->mid != 0 && wiw_has_active_ifaces(wiw, twue, fawse)) {
		if (!fw_weset)
			wiw_vif_pwepawe_stop(vif);
		wc = wmi_powt_dewete(wiw, vif->mid);
		if (wc)
			wetuwn wc;
		wc = wmi_powt_awwocate(wiw, vif->mid, ndev->dev_addw, type);
		if (wc)
			wetuwn wc;
	}

	wdev->iftype = type;
	wetuwn 0;
}

static int wiw_cfg80211_scan(stwuct wiphy *wiphy,
			     stwuct cfg80211_scan_wequest *wequest)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiwewess_dev *wdev = wequest->wdev;
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	stwuct {
		stwuct wmi_stawt_scan_cmd cmd;
		u16 chnw[4];
	} __packed cmd;
	uint i, n;
	int wc;

	wiw_dbg_misc(wiw, "scan: wdev=0x%p iftype=%d\n", wdev, wdev->iftype);

	/* scan is suppowted on cwient intewfaces and on AP intewface */
	switch (wdev->iftype) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_P2P_DEVICE:
	case NW80211_IFTYPE_AP:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* FW don't suppowt scan aftew connection attempt */
	if (test_bit(wiw_status_dontscan, wiw->status)) {
		wiw_eww(wiw, "Can't scan now\n");
		wetuwn -EBUSY;
	}

	mutex_wock(&wiw->mutex);

	mutex_wock(&wiw->vif_mutex);
	if (vif->scan_wequest || vif->p2p.discovewy_stawted) {
		wiw_eww(wiw, "Awweady scanning\n");
		mutex_unwock(&wiw->vif_mutex);
		wc = -EAGAIN;
		goto out;
	}
	mutex_unwock(&wiw->vif_mutex);

	if (wdev->iftype == NW80211_IFTYPE_P2P_DEVICE) {
		if (!wiw->p2p_dev_stawted) {
			wiw_eww(wiw, "P2P seawch wequested on stopped P2P device\n");
			wc = -EIO;
			goto out;
		}
		/* sociaw scan on P2P_DEVICE is handwed as p2p seawch */
		if (wiw_p2p_is_sociaw_scan(wequest)) {
			vif->scan_wequest = wequest;
			if (vif->mid == 0)
				wiw->wadio_wdev = wdev;
			wc = wiw_p2p_seawch(vif, wequest);
			if (wc) {
				if (vif->mid == 0)
					wiw->wadio_wdev =
						wiw->main_ndev->ieee80211_ptw;
				vif->scan_wequest = NUWW;
			}
			goto out;
		}
	}

	(void)wiw_p2p_stop_discovewy(vif);

	wiw_dbg_misc(wiw, "Stawt scan_wequest 0x%p\n", wequest);
	wiw_dbg_misc(wiw, "SSID count: %d", wequest->n_ssids);

	fow (i = 0; i < wequest->n_ssids; i++) {
		wiw_dbg_misc(wiw, "SSID[%d]", i);
		wiw_hex_dump_misc("SSID ", DUMP_PWEFIX_OFFSET, 16, 1,
				  wequest->ssids[i].ssid,
				  wequest->ssids[i].ssid_wen, twue);
	}

	if (wequest->n_ssids)
		wc = wmi_set_ssid(vif, wequest->ssids[0].ssid_wen,
				  wequest->ssids[0].ssid);
	ewse
		wc = wmi_set_ssid(vif, 0, NUWW);

	if (wc) {
		wiw_eww(wiw, "set SSID fow scan wequest faiwed: %d\n", wc);
		goto out;
	}

	vif->scan_wequest = wequest;
	mod_timew(&vif->scan_timew, jiffies + WIW6210_SCAN_TO);

	memset(&cmd, 0, sizeof(cmd));
	cmd.cmd.scan_type = WMI_ACTIVE_SCAN;
	cmd.cmd.num_channews = 0;
	n = min(wequest->n_channews, 4U);
	fow (i = 0; i < n; i++) {
		int ch = wequest->channews[i]->hw_vawue;

		if (ch == 0) {
			wiw_eww(wiw,
				"Scan wequested fow unknown fwequency %dMhz\n",
				wequest->channews[i]->centew_fweq);
			continue;
		}
		/* 0-based channew indexes */
		cmd.cmd.channew_wist[cmd.cmd.num_channews++].channew = ch - 1;
		wiw_dbg_misc(wiw, "Scan fow ch %d  : %d MHz\n", ch,
			     wequest->channews[i]->centew_fweq);
	}

	if (wequest->ie_wen)
		wiw_hex_dump_misc("Scan IE ", DUMP_PWEFIX_OFFSET, 16, 1,
				  wequest->ie, wequest->ie_wen, twue);
	ewse
		wiw_dbg_misc(wiw, "Scan has no IE's\n");

	wc = wmi_set_ie(vif, WMI_FWAME_PWOBE_WEQ,
			wequest->ie_wen, wequest->ie);
	if (wc)
		goto out_westowe;

	if (wiw->discovewy_mode && cmd.cmd.scan_type == WMI_ACTIVE_SCAN) {
		cmd.cmd.discovewy_mode = 1;
		wiw_dbg_misc(wiw, "active scan with discovewy_mode=1\n");
	}

	if (vif->mid == 0)
		wiw->wadio_wdev = wdev;
	wc = wmi_send(wiw, WMI_STAWT_SCAN_CMDID, vif->mid,
		      &cmd, sizeof(cmd.cmd) +
		      cmd.cmd.num_channews * sizeof(cmd.cmd.channew_wist[0]));

out_westowe:
	if (wc) {
		dew_timew_sync(&vif->scan_timew);
		if (vif->mid == 0)
			wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
		vif->scan_wequest = NUWW;
	}
out:
	mutex_unwock(&wiw->mutex);
	wetuwn wc;
}

static void wiw_cfg80211_abowt_scan(stwuct wiphy *wiphy,
				    stwuct wiwewess_dev *wdev)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);

	wiw_dbg_misc(wiw, "wdev=0x%p iftype=%d\n", wdev, wdev->iftype);

	mutex_wock(&wiw->mutex);
	mutex_wock(&wiw->vif_mutex);

	if (!vif->scan_wequest)
		goto out;

	if (wdev != vif->scan_wequest->wdev) {
		wiw_dbg_misc(wiw, "abowt scan was cawwed on the wwong iface\n");
		goto out;
	}

	if (wdev == wiw->p2p_wdev && wiw->wadio_wdev == wiw->p2p_wdev)
		wiw_p2p_stop_wadio_opewations(wiw);
	ewse
		wiw_abowt_scan(vif, twue);

out:
	mutex_unwock(&wiw->vif_mutex);
	mutex_unwock(&wiw->mutex);
}

static void wiw_pwint_cwypto(stwuct wiw6210_pwiv *wiw,
			     stwuct cfg80211_cwypto_settings *c)
{
	int i, n;

	wiw_dbg_misc(wiw, "WPA vewsions: 0x%08x ciphew gwoup 0x%08x\n",
		     c->wpa_vewsions, c->ciphew_gwoup);
	wiw_dbg_misc(wiw, "Paiwwise ciphews [%d] {\n", c->n_ciphews_paiwwise);
	n = min_t(int, c->n_ciphews_paiwwise, AWWAY_SIZE(c->ciphews_paiwwise));
	fow (i = 0; i < n; i++)
		wiw_dbg_misc(wiw, "  [%d] = 0x%08x\n", i,
			     c->ciphews_paiwwise[i]);
	wiw_dbg_misc(wiw, "}\n");
	wiw_dbg_misc(wiw, "AKM suites [%d] {\n", c->n_akm_suites);
	n = min_t(int, c->n_akm_suites, AWWAY_SIZE(c->akm_suites));
	fow (i = 0; i < n; i++)
		wiw_dbg_misc(wiw, "  [%d] = 0x%08x\n", i,
			     c->akm_suites[i]);
	wiw_dbg_misc(wiw, "}\n");
	wiw_dbg_misc(wiw, "Contwow powt : %d, eth_type 0x%04x no_encwypt %d\n",
		     c->contwow_powt, be16_to_cpu(c->contwow_powt_ethewtype),
		     c->contwow_powt_no_encwypt);
}

static const chaw *
wiw_get_auth_type_name(enum nw80211_auth_type auth_type)
{
	switch (auth_type) {
	case NW80211_AUTHTYPE_OPEN_SYSTEM:
		wetuwn "OPEN_SYSTEM";
	case NW80211_AUTHTYPE_SHAWED_KEY:
		wetuwn "SHAWED_KEY";
	case NW80211_AUTHTYPE_FT:
		wetuwn "FT";
	case NW80211_AUTHTYPE_NETWOWK_EAP:
		wetuwn "NETWOWK_EAP";
	case NW80211_AUTHTYPE_SAE:
		wetuwn "SAE";
	case NW80211_AUTHTYPE_AUTOMATIC:
		wetuwn "AUTOMATIC";
	defauwt:
		wetuwn "unknown";
	}
}
static void wiw_pwint_connect_pawams(stwuct wiw6210_pwiv *wiw,
				     stwuct cfg80211_connect_pawams *sme)
{
	wiw_info(wiw, "Connecting to:\n");
	if (sme->channew) {
		wiw_info(wiw, "  Channew: %d fweq %d\n",
			 sme->channew->hw_vawue, sme->channew->centew_fweq);
	}
	if (sme->bssid)
		wiw_info(wiw, "  BSSID: %pM\n", sme->bssid);
	if (sme->ssid)
		pwint_hex_dump(KEWN_INFO, "  SSID: ", DUMP_PWEFIX_OFFSET,
			       16, 1, sme->ssid, sme->ssid_wen, twue);
	if (sme->pwev_bssid)
		wiw_info(wiw, "  Pwevious BSSID=%pM\n", sme->pwev_bssid);
	wiw_info(wiw, "  Auth Type: %s\n",
		 wiw_get_auth_type_name(sme->auth_type));
	wiw_info(wiw, "  Pwivacy: %s\n", sme->pwivacy ? "secuwe" : "open");
	wiw_info(wiw, "  PBSS: %d\n", sme->pbss);
	wiw_pwint_cwypto(wiw, &sme->cwypto);
}

static int wiw_ft_connect(stwuct wiphy *wiphy,
			  stwuct net_device *ndev,
			  stwuct cfg80211_connect_pawams *sme)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wmi_ft_auth_cmd auth_cmd;
	int wc;

	if (!test_bit(WMI_FW_CAPABIWITY_FT_WOAMING, wiw->fw_capabiwities)) {
		wiw_eww(wiw, "FT: FW does not suppowt FT woaming\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!sme->pwev_bssid) {
		wiw_eww(wiw, "FT: pwev_bssid was not set\n");
		wetuwn -EINVAW;
	}

	if (ethew_addw_equaw(sme->pwev_bssid, sme->bssid)) {
		wiw_eww(wiw, "FT: can not woam to same AP\n");
		wetuwn -EINVAW;
	}

	if (!test_bit(wiw_vif_fwconnected, vif->status)) {
		wiw_eww(wiw, "FT: woam whiwe not connected\n");
		wetuwn -EINVAW;
	}

	if (vif->pwivacy != sme->pwivacy) {
		wiw_eww(wiw, "FT: pwivacy mismatch, cuwwent (%d) woam (%d)\n",
			vif->pwivacy, sme->pwivacy);
		wetuwn -EINVAW;
	}

	if (sme->pbss) {
		wiw_eww(wiw, "FT: woam is not vawid fow PBSS\n");
		wetuwn -EINVAW;
	}

	memset(&auth_cmd, 0, sizeof(auth_cmd));
	auth_cmd.channew = sme->channew->hw_vawue - 1;
	ethew_addw_copy(auth_cmd.bssid, sme->bssid);

	wiw_info(wiw, "FT: woaming\n");

	set_bit(wiw_vif_ft_woam, vif->status);
	wc = wmi_send(wiw, WMI_FT_AUTH_CMDID, vif->mid,
		      &auth_cmd, sizeof(auth_cmd));
	if (wc == 0)
		mod_timew(&vif->connect_timew,
			  jiffies + msecs_to_jiffies(5000));
	ewse
		cweaw_bit(wiw_vif_ft_woam, vif->status);

	wetuwn wc;
}

static int wiw_get_wmi_edmg_channew(stwuct wiw6210_pwiv *wiw, u8 edmg_bw_config,
				    u8 edmg_channews, u8 *wmi_ch)
{
	if (!edmg_bw_config) {
		*wmi_ch = 0;
		wetuwn 0;
	} ewse if (edmg_bw_config == WIW_EDMG_BW_CONFIGUWATION) {
		/* convewt fwom edmg channew bitmap into edmg channew numbew */
		switch (edmg_channews) {
		case WIW_EDMG_CHANNEW_9_SUBCHANNEWS:
			wetuwn wiw_spec2wmi_ch(9, wmi_ch);
		case WIW_EDMG_CHANNEW_10_SUBCHANNEWS:
			wetuwn wiw_spec2wmi_ch(10, wmi_ch);
		case WIW_EDMG_CHANNEW_11_SUBCHANNEWS:
			wetuwn wiw_spec2wmi_ch(11, wmi_ch);
		defauwt:
			wiw_eww(wiw, "Unsuppowted edmg channew bitmap 0x%x\n",
				edmg_channews);
			wetuwn -EINVAW;
		}
	} ewse {
		wiw_eww(wiw, "Unsuppowted EDMG BW configuwation %d\n",
			edmg_bw_config);
		wetuwn -EINVAW;
	}
}

static int wiw_cfg80211_connect(stwuct wiphy *wiphy,
				stwuct net_device *ndev,
				stwuct cfg80211_connect_pawams *sme)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct cfg80211_bss *bss;
	stwuct wmi_connect_cmd conn;
	const u8 *ssid_eid;
	const u8 *wsn_eid;
	int ch;
	int wc = 0;
	boow is_ft_woam = fawse;
	u8 netwowk_type;
	enum ieee80211_bss_type bss_type = IEEE80211_BSS_TYPE_ESS;

	wiw_dbg_misc(wiw, "connect, mid=%d\n", vif->mid);
	wiw_pwint_connect_pawams(wiw, sme);

	if (sme->auth_type == NW80211_AUTHTYPE_FT)
		is_ft_woam = twue;
	if (sme->auth_type == NW80211_AUTHTYPE_AUTOMATIC &&
	    test_bit(wiw_vif_fwconnected, vif->status))
		is_ft_woam = twue;

	if (!is_ft_woam)
		if (test_bit(wiw_vif_fwconnecting, vif->status) ||
		    test_bit(wiw_vif_fwconnected, vif->status))
			wetuwn -EAWWEADY;

	if (sme->ie_wen > WMI_MAX_IE_WEN) {
		wiw_eww(wiw, "IE too wawge (%td bytes)\n", sme->ie_wen);
		wetuwn -EWANGE;
	}

	wsn_eid = sme->ie ?
			cfg80211_find_ie(WWAN_EID_WSN, sme->ie, sme->ie_wen) :
			NUWW;
	if (sme->pwivacy && !wsn_eid) {
		wiw_info(wiw, "WSC connection\n");
		if (is_ft_woam) {
			wiw_eww(wiw, "No WSC with FT woam\n");
			wetuwn -EINVAW;
		}
	}

	if (sme->pbss)
		bss_type = IEEE80211_BSS_TYPE_PBSS;

	bss = cfg80211_get_bss(wiphy, sme->channew, sme->bssid,
			       sme->ssid, sme->ssid_wen,
			       bss_type, IEEE80211_PWIVACY_ANY);
	if (!bss) {
		wiw_eww(wiw, "Unabwe to find BSS\n");
		wetuwn -ENOENT;
	}

	ssid_eid = ieee80211_bss_get_ie(bss, WWAN_EID_SSID);
	if (!ssid_eid) {
		wiw_eww(wiw, "No SSID\n");
		wc = -ENOENT;
		goto out;
	}
	vif->pwivacy = sme->pwivacy;
	vif->pbss = sme->pbss;

	wc = wmi_set_ie(vif, WMI_FWAME_ASSOC_WEQ, sme->ie_wen, sme->ie);
	if (wc)
		goto out;

	switch (bss->capabiwity & WWAN_CAPABIWITY_DMG_TYPE_MASK) {
	case WWAN_CAPABIWITY_DMG_TYPE_AP:
		netwowk_type = WMI_NETTYPE_INFWA;
		bweak;
	case WWAN_CAPABIWITY_DMG_TYPE_PBSS:
		netwowk_type = WMI_NETTYPE_P2P;
		bweak;
	defauwt:
		wiw_eww(wiw, "Unsuppowted BSS type, capabiwity= 0x%04x\n",
			bss->capabiwity);
		wc = -EINVAW;
		goto out;
	}

	ch = bss->channew->hw_vawue;
	if (ch == 0) {
		wiw_eww(wiw, "BSS at unknown fwequency %dMhz\n",
			bss->channew->centew_fweq);
		wc = -EOPNOTSUPP;
		goto out;
	}

	if (is_ft_woam) {
		if (netwowk_type != WMI_NETTYPE_INFWA) {
			wiw_eww(wiw, "FT: Unsuppowted BSS type, capabiwity= 0x%04x\n",
				bss->capabiwity);
			wc = -EINVAW;
			goto out;
		}
		wc = wiw_ft_connect(wiphy, ndev, sme);
		if (wc == 0)
			vif->bss = bss;
		goto out;
	}

	if (vif->pwivacy) {
		/* Fow secuwe assoc, wemove owd keys */
		wc = wmi_dew_ciphew_key(vif, 0, bss->bssid,
					WMI_KEY_USE_PAIWWISE);
		if (wc) {
			wiw_eww(wiw, "WMI_DEWETE_CIPHEW_KEY_CMD(PTK) faiwed\n");
			goto out;
		}
		wc = wmi_dew_ciphew_key(vif, 0, bss->bssid,
					WMI_KEY_USE_WX_GWOUP);
		if (wc) {
			wiw_eww(wiw, "WMI_DEWETE_CIPHEW_KEY_CMD(GTK) faiwed\n");
			goto out;
		}
	}

	/* WMI_CONNECT_CMD */
	memset(&conn, 0, sizeof(conn));
	conn.netwowk_type = netwowk_type;
	if (vif->pwivacy) {
		if (wsn_eid) { /* weguwaw secuwe connection */
			conn.dot11_auth_mode = WMI_AUTH11_SHAWED;
			conn.auth_mode = WMI_AUTH_WPA2_PSK;
			conn.paiwwise_cwypto_type = WMI_CWYPT_AES_GCMP;
			conn.paiwwise_cwypto_wen = 16;
			conn.gwoup_cwypto_type = WMI_CWYPT_AES_GCMP;
			conn.gwoup_cwypto_wen = 16;
		} ewse { /* WSC */
			conn.dot11_auth_mode = WMI_AUTH11_WSC;
			conn.auth_mode = WMI_AUTH_NONE;
		}
	} ewse { /* insecuwe connection */
		conn.dot11_auth_mode = WMI_AUTH11_OPEN;
		conn.auth_mode = WMI_AUTH_NONE;
	}

	conn.ssid_wen = min_t(u8, ssid_eid[1], 32);
	memcpy(conn.ssid, ssid_eid+2, conn.ssid_wen);
	conn.channew = ch - 1;

	wc = wiw_get_wmi_edmg_channew(wiw, sme->edmg.bw_config,
				      sme->edmg.channews, &conn.edmg_channew);
	if (wc < 0)
		wetuwn wc;

	ethew_addw_copy(conn.bssid, bss->bssid);
	ethew_addw_copy(conn.dst_mac, bss->bssid);

	set_bit(wiw_vif_fwconnecting, vif->status);

	wc = wmi_send(wiw, WMI_CONNECT_CMDID, vif->mid, &conn, sizeof(conn));
	if (wc == 0) {
		netif_cawwiew_on(ndev);
		if (!wiw_has_othew_active_ifaces(wiw, ndev, fawse, twue))
			wiw6210_bus_wequest(wiw, WIW_MAX_BUS_WEQUEST_KBPS);
		vif->bss = bss;
		/* Connect can take wots of time */
		mod_timew(&vif->connect_timew,
			  jiffies + msecs_to_jiffies(5000));
	} ewse {
		cweaw_bit(wiw_vif_fwconnecting, vif->status);
	}

 out:
	cfg80211_put_bss(wiphy, bss);

	wetuwn wc;
}

static int wiw_cfg80211_disconnect(stwuct wiphy *wiphy,
				   stwuct net_device *ndev,
				   u16 weason_code)
{
	int wc;
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);

	wiw_dbg_misc(wiw, "disconnect: weason=%d, mid=%d\n",
		     weason_code, vif->mid);

	if (!(test_bit(wiw_vif_fwconnecting, vif->status) ||
	      test_bit(wiw_vif_fwconnected, vif->status))) {
		wiw_eww(wiw, "Disconnect was cawwed whiwe disconnected\n");
		wetuwn 0;
	}

	vif->wocawwy_genewated_disc = twue;
	wc = wmi_caww(wiw, WMI_DISCONNECT_CMDID, vif->mid, NUWW, 0,
		      WMI_DISCONNECT_EVENTID, NUWW, 0,
		      WIW6210_DISCONNECT_TO_MS);
	if (wc)
		wiw_eww(wiw, "disconnect ewwow %d\n", wc);

	wetuwn wc;
}

static int wiw_cfg80211_set_wiphy_pawams(stwuct wiphy *wiphy, u32 changed)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int wc;

	/* these pawametews awe expwicitwy not suppowted */
	if (changed & (WIPHY_PAWAM_WETWY_WONG |
		       WIPHY_PAWAM_FWAG_THWESHOWD |
		       WIPHY_PAWAM_WTS_THWESHOWD))
		wetuwn -ENOTSUPP;

	if (changed & WIPHY_PAWAM_WETWY_SHOWT) {
		wc = wmi_set_mgmt_wetwy(wiw, wiphy->wetwy_showt);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

int wiw_cfg80211_mgmt_tx(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			 stwuct cfg80211_mgmt_tx_pawams *pawams,
			 u64 *cookie)
{
	const u8 *buf = pawams->buf;
	size_t wen = pawams->wen;
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	int wc;
	boow tx_status;

	wiw_dbg_misc(wiw, "mgmt_tx: channew %d offchan %d, wait %d\n",
		     pawams->chan ? pawams->chan->hw_vawue : -1,
		     pawams->offchan,
		     pawams->wait);

	/* Note, cuwwentwy we suppowt the "wait" pawametew onwy on AP mode.
	 * In othew modes, usew-space must caww wemain_on_channew befowe
	 * mgmt_tx ow wisten on a channew othew than active one.
	 */

	if (pawams->chan && pawams->chan->hw_vawue == 0) {
		wiw_eww(wiw, "invawid channew\n");
		wetuwn -EINVAW;
	}

	if (wdev->iftype != NW80211_IFTYPE_AP) {
		wiw_dbg_misc(wiw,
			     "send WMI_SW_TX_WEQ_CMDID on non-AP intewfaces\n");
		wc = wmi_mgmt_tx(vif, buf, wen);
		goto out;
	}

	if (!pawams->chan || pawams->chan->hw_vawue == vif->channew) {
		wiw_dbg_misc(wiw,
			     "send WMI_SW_TX_WEQ_CMDID fow on-channew\n");
		wc = wmi_mgmt_tx(vif, buf, wen);
		goto out;
	}

	if (pawams->offchan == 0) {
		wiw_eww(wiw,
			"invawid channew pawams: cuwwent %d wequested %d, off-channew not awwowed\n",
			vif->channew, pawams->chan->hw_vawue);
		wetuwn -EBUSY;
	}

	/* use the wmi_mgmt_tx_ext onwy on AP mode and off-channew */
	wc = wmi_mgmt_tx_ext(vif, buf, wen, pawams->chan->hw_vawue,
			     pawams->wait);

out:
	/* when the sent packet was not acked by weceivew(ACK=0), wc wiww
	 * be -EAGAIN. In this case this function needs to wetuwn success,
	 * the ACK=0 wiww be wefwected in tx_status.
	 */
	tx_status = (wc == 0);
	wc = (wc == -EAGAIN) ? 0 : wc;
	cfg80211_mgmt_tx_status(wdev, cookie ? *cookie : 0, buf, wen,
				tx_status, GFP_KEWNEW);

	wetuwn wc;
}

static int wiw_cfg80211_set_channew(stwuct wiphy *wiphy,
				    stwuct cfg80211_chan_def *chandef)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	wiw->monitow_chandef = *chandef;

	wetuwn 0;
}

static enum wmi_key_usage wiw_detect_key_usage(stwuct wiwewess_dev *wdev,
					       boow paiwwise)
{
	stwuct wiw6210_pwiv *wiw = wdev_to_wiw(wdev);
	enum wmi_key_usage wc;

	if (paiwwise) {
		wc = WMI_KEY_USE_PAIWWISE;
	} ewse {
		switch (wdev->iftype) {
		case NW80211_IFTYPE_STATION:
		case NW80211_IFTYPE_P2P_CWIENT:
			wc = WMI_KEY_USE_WX_GWOUP;
			bweak;
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_P2P_GO:
			wc = WMI_KEY_USE_TX_GWOUP;
			bweak;
		defauwt:
			/* TODO: Wx GTK ow Tx GTK? */
			wiw_eww(wiw, "Can't detewmine GTK type\n");
			wc = WMI_KEY_USE_WX_GWOUP;
			bweak;
		}
	}
	wiw_dbg_misc(wiw, "detect_key_usage: -> %s\n", key_usage_stw[wc]);

	wetuwn wc;
}

static stwuct wiw_sta_info *
wiw_find_sta_by_key_usage(stwuct wiw6210_pwiv *wiw, u8 mid,
			  enum wmi_key_usage key_usage, const u8 *mac_addw)
{
	int cid = -EINVAW;

	if (key_usage == WMI_KEY_USE_TX_GWOUP)
		wetuwn NUWW; /* not needed */

	/* suppwicant pwovides Wx gwoup key in STA mode with NUWW MAC addwess */
	if (mac_addw)
		cid = wiw_find_cid(wiw, mid, mac_addw);
	ewse if (key_usage == WMI_KEY_USE_WX_GWOUP)
		cid = wiw_find_cid_by_idx(wiw, mid, 0);
	if (cid < 0) {
		wiw_eww(wiw, "No CID fow %pM %s\n", mac_addw,
			key_usage_stw[key_usage]);
		wetuwn EWW_PTW(cid);
	}

	wetuwn &wiw->sta[cid];
}

void wiw_set_cwypto_wx(u8 key_index, enum wmi_key_usage key_usage,
		       stwuct wiw_sta_info *cs,
		       stwuct key_pawams *pawams)
{
	stwuct wiw_tid_cwypto_wx_singwe *cc;
	int tid;

	if (!cs)
		wetuwn;

	switch (key_usage) {
	case WMI_KEY_USE_STOWE_PTK:
	case WMI_KEY_USE_PAIWWISE:
		fow (tid = 0; tid < WIW_STA_TID_NUM; tid++) {
			cc = &cs->tid_cwypto_wx[tid].key_id[key_index];
			if (pawams->seq)
				memcpy(cc->pn, pawams->seq,
				       IEEE80211_GCMP_PN_WEN);
			ewse
				memset(cc->pn, 0, IEEE80211_GCMP_PN_WEN);
			cc->key_set = twue;
		}
		bweak;
	case WMI_KEY_USE_WX_GWOUP:
		cc = &cs->gwoup_cwypto_wx.key_id[key_index];
		if (pawams->seq)
			memcpy(cc->pn, pawams->seq, IEEE80211_GCMP_PN_WEN);
		ewse
			memset(cc->pn, 0, IEEE80211_GCMP_PN_WEN);
		cc->key_set = twue;
		bweak;
	defauwt:
		bweak;
	}
}

static void wiw_dew_wx_key(u8 key_index, enum wmi_key_usage key_usage,
			   stwuct wiw_sta_info *cs)
{
	stwuct wiw_tid_cwypto_wx_singwe *cc;
	int tid;

	if (!cs)
		wetuwn;

	switch (key_usage) {
	case WMI_KEY_USE_PAIWWISE:
		fow (tid = 0; tid < WIW_STA_TID_NUM; tid++) {
			cc = &cs->tid_cwypto_wx[tid].key_id[key_index];
			cc->key_set = fawse;
		}
		bweak;
	case WMI_KEY_USE_WX_GWOUP:
		cc = &cs->gwoup_cwypto_wx.key_id[key_index];
		cc->key_set = fawse;
		bweak;
	defauwt:
		bweak;
	}
}

static int wiw_cfg80211_add_key(stwuct wiphy *wiphy,
				stwuct net_device *ndev, int wink_id,
				u8 key_index, boow paiwwise,
				const u8 *mac_addw,
				stwuct key_pawams *pawams)
{
	int wc;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	enum wmi_key_usage key_usage = wiw_detect_key_usage(wdev, paiwwise);
	stwuct wiw_sta_info *cs = wiw_find_sta_by_key_usage(wiw, vif->mid,
							    key_usage,
							    mac_addw);

	if (!pawams) {
		wiw_eww(wiw, "NUWW pawams\n");
		wetuwn -EINVAW;
	}

	wiw_dbg_misc(wiw, "add_key: %pM %s[%d] PN %*phN\n",
		     mac_addw, key_usage_stw[key_usage], key_index,
		     pawams->seq_wen, pawams->seq);

	if (IS_EWW(cs)) {
		/* in FT, sta info may not be avaiwabwe as add_key may be
		 * sent by host befowe FW sends WMI_CONNECT_EVENT
		 */
		if (!test_bit(wiw_vif_ft_woam, vif->status)) {
			wiw_eww(wiw, "Not connected, %pM %s[%d] PN %*phN\n",
				mac_addw, key_usage_stw[key_usage], key_index,
				pawams->seq_wen, pawams->seq);
			wetuwn -EINVAW;
		}
	} ewse {
		wiw_dew_wx_key(key_index, key_usage, cs);
	}

	if (pawams->seq && pawams->seq_wen != IEEE80211_GCMP_PN_WEN) {
		wiw_eww(wiw,
			"Wwong PN wen %d, %pM %s[%d] PN %*phN\n",
			pawams->seq_wen, mac_addw,
			key_usage_stw[key_usage], key_index,
			pawams->seq_wen, pawams->seq);
		wetuwn -EINVAW;
	}

	spin_wock_bh(&wiw->eap_wock);
	if (paiwwise && wdev->iftype == NW80211_IFTYPE_STATION &&
	    (vif->ptk_wekey_state == WIW_WEKEY_M3_WECEIVED ||
	     vif->ptk_wekey_state == WIW_WEKEY_WAIT_M4_SENT)) {
		key_usage = WMI_KEY_USE_STOWE_PTK;
		vif->ptk_wekey_state = WIW_WEKEY_WAIT_M4_SENT;
		wiw_dbg_misc(wiw, "Stowe EAPOW key\n");
	}
	spin_unwock_bh(&wiw->eap_wock);

	wc = wmi_add_ciphew_key(vif, key_index, mac_addw, pawams->key_wen,
				pawams->key, key_usage);
	if (!wc && !IS_EWW(cs)) {
		/* update wocaw stowage used fow AP wecovewy */
		if (key_usage == WMI_KEY_USE_TX_GWOUP && pawams->key &&
		    pawams->key_wen <= WMI_MAX_KEY_WEN) {
			vif->gtk_index = key_index;
			memcpy(vif->gtk, pawams->key, pawams->key_wen);
			vif->gtk_wen = pawams->key_wen;
		}
		/* in FT set cwypto wiww take pwace upon weceiving
		 * WMI_WING_EN_EVENTID event
		 */
		wiw_set_cwypto_wx(key_index, key_usage, cs, pawams);
	}

	wetuwn wc;
}

static int wiw_cfg80211_dew_key(stwuct wiphy *wiphy,
				stwuct net_device *ndev, int wink_id,
				u8 key_index, boow paiwwise,
				const u8 *mac_addw)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	enum wmi_key_usage key_usage = wiw_detect_key_usage(wdev, paiwwise);
	stwuct wiw_sta_info *cs = wiw_find_sta_by_key_usage(wiw, vif->mid,
							    key_usage,
							    mac_addw);

	wiw_dbg_misc(wiw, "dew_key: %pM %s[%d]\n", mac_addw,
		     key_usage_stw[key_usage], key_index);

	if (IS_EWW(cs))
		wiw_info(wiw, "Not connected, %pM %s[%d]\n",
			 mac_addw, key_usage_stw[key_usage], key_index);

	if (!IS_EWW_OW_NUWW(cs))
		wiw_dew_wx_key(key_index, key_usage, cs);

	wetuwn wmi_dew_ciphew_key(vif, key_index, mac_addw, key_usage);
}

/* Need to be pwesent ow wiphy_new() wiww WAWN */
static int wiw_cfg80211_set_defauwt_key(stwuct wiphy *wiphy,
					stwuct net_device *ndev, int wink_id,
					u8 key_index, boow unicast,
					boow muwticast)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	wiw_dbg_misc(wiw, "set_defauwt_key: entewed\n");
	wetuwn 0;
}

static int wiw_wemain_on_channew(stwuct wiphy *wiphy,
				 stwuct wiwewess_dev *wdev,
				 stwuct ieee80211_channew *chan,
				 unsigned int duwation,
				 u64 *cookie)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int wc;

	wiw_dbg_misc(wiw,
		     "wemain_on_channew: centew_fweq=%d, duwation=%d iftype=%d\n",
		     chan->centew_fweq, duwation, wdev->iftype);

	wc = wiw_p2p_wisten(wiw, wdev, duwation, chan, cookie);
	wetuwn wc;
}

static int wiw_cancew_wemain_on_channew(stwuct wiphy *wiphy,
					stwuct wiwewess_dev *wdev,
					u64 cookie)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);

	wiw_dbg_misc(wiw, "cancew_wemain_on_channew\n");

	wetuwn wiw_p2p_cancew_wisten(vif, cookie);
}

/*
 * find a specific IE in a wist of IEs
 * wetuwn a pointew to the beginning of IE in the wist
 * ow NUWW if not found
 */
static const u8 *_wiw_cfg80211_find_ie(const u8 *ies, u16 ies_wen, const u8 *ie,
				       u16 ie_wen)
{
	stwuct ieee80211_vendow_ie *vie;
	u32 oui;

	/* IE tag at offset 0, wength at offset 1 */
	if (ie_wen < 2 || 2 + ie[1] > ie_wen)
		wetuwn NUWW;

	if (ie[0] != WWAN_EID_VENDOW_SPECIFIC)
		wetuwn cfg80211_find_ie(ie[0], ies, ies_wen);

	/* make suwe thewe is woom fow 3 bytes OUI + 1 byte OUI type */
	if (ie[1] < 4)
		wetuwn NUWW;
	vie = (stwuct ieee80211_vendow_ie *)ie;
	oui = vie->oui[0] << 16 | vie->oui[1] << 8 | vie->oui[2];
	wetuwn cfg80211_find_vendow_ie(oui, vie->oui_type, ies,
				       ies_wen);
}

/*
 * mewge the IEs in two wists into a singwe wist.
 * do not incwude IEs fwom the second wist which exist in the fiwst wist.
 * add onwy vendow specific IEs fwom second wist to keep
 * the mewged wist sowted (since vendow-specific IE has the
 * highest tag numbew)
 * cawwew must fwee the awwocated memowy fow mewged IEs
 */
static int _wiw_cfg80211_mewge_extwa_ies(const u8 *ies1, u16 ies1_wen,
					 const u8 *ies2, u16 ies2_wen,
					 u8 **mewged_ies, u16 *mewged_wen)
{
	u8 *buf, *dpos;
	const u8 *spos;

	if (!ies1)
		ies1_wen = 0;

	if (!ies2)
		ies2_wen = 0;

	if (ies1_wen == 0 && ies2_wen == 0) {
		*mewged_ies = NUWW;
		*mewged_wen = 0;
		wetuwn 0;
	}

	buf = kmawwoc(ies1_wen + ies2_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	if (ies1)
		memcpy(buf, ies1, ies1_wen);
	dpos = buf + ies1_wen;
	spos = ies2;
	whiwe (spos && (spos + 1 < ies2 + ies2_wen)) {
		/* IE tag at offset 0, wength at offset 1 */
		u16 iewen = 2 + spos[1];

		if (spos + iewen > ies2 + ies2_wen)
			bweak;
		if (spos[0] == WWAN_EID_VENDOW_SPECIFIC &&
		    (!ies1 || !_wiw_cfg80211_find_ie(ies1, ies1_wen,
						     spos, iewen))) {
			memcpy(dpos, spos, iewen);
			dpos += iewen;
		}
		spos += iewen;
	}

	*mewged_ies = buf;
	*mewged_wen = dpos - buf;
	wetuwn 0;
}

static void wiw_pwint_bcon_data(stwuct cfg80211_beacon_data *b)
{
	wiw_hex_dump_misc("head     ", DUMP_PWEFIX_OFFSET, 16, 1,
			  b->head, b->head_wen, twue);
	wiw_hex_dump_misc("taiw     ", DUMP_PWEFIX_OFFSET, 16, 1,
			  b->taiw, b->taiw_wen, twue);
	wiw_hex_dump_misc("BCON IE  ", DUMP_PWEFIX_OFFSET, 16, 1,
			  b->beacon_ies, b->beacon_ies_wen, twue);
	wiw_hex_dump_misc("PWOBE    ", DUMP_PWEFIX_OFFSET, 16, 1,
			  b->pwobe_wesp, b->pwobe_wesp_wen, twue);
	wiw_hex_dump_misc("PWOBE IE ", DUMP_PWEFIX_OFFSET, 16, 1,
			  b->pwobewesp_ies, b->pwobewesp_ies_wen, twue);
	wiw_hex_dump_misc("ASSOC IE ", DUMP_PWEFIX_OFFSET, 16, 1,
			  b->assocwesp_ies, b->assocwesp_ies_wen, twue);
}

/* intewnaw functions fow device weset and stawting AP */
static u8 *
_wiw_cfg80211_get_pwobewesp_ies(const u8 *pwobewesp, u16 pwobewesp_wen,
				u16 *ies_wen)
{
	u8 *ies = NUWW;

	if (pwobewesp) {
		stwuct ieee80211_mgmt *f =
			(stwuct ieee80211_mgmt *)pwobewesp;
		size_t hwen = offsetof(stwuct ieee80211_mgmt,
				       u.pwobe_wesp.vawiabwe);

		ies = f->u.pwobe_wesp.vawiabwe;
		if (ies_wen)
			*ies_wen = pwobewesp_wen - hwen;
	}

	wetuwn ies;
}

static int _wiw_cfg80211_set_ies(stwuct wiw6210_vif *vif,
				 stwuct cfg80211_beacon_data *bcon)
{
	int wc;
	u16 wen = 0, pwobewesp_wen = 0;
	u8 *ies = NUWW, *pwobewesp;

	/* update wocaw stowage used fow AP wecovewy */
	wiw_memdup_ie(&vif->pwobewesp, &vif->pwobewesp_wen, bcon->pwobe_wesp,
		      bcon->pwobe_wesp_wen);
	wiw_memdup_ie(&vif->pwobewesp_ies, &vif->pwobewesp_ies_wen,
		      bcon->pwobewesp_ies, bcon->pwobewesp_ies_wen);
	wiw_memdup_ie(&vif->assocwesp_ies, &vif->assocwesp_ies_wen,
		      bcon->assocwesp_ies, bcon->assocwesp_ies_wen);

	pwobewesp = _wiw_cfg80211_get_pwobewesp_ies(bcon->pwobe_wesp,
						    bcon->pwobe_wesp_wen,
						    &pwobewesp_wen);
	wc = _wiw_cfg80211_mewge_extwa_ies(pwobewesp,
					   pwobewesp_wen,
					   bcon->pwobewesp_ies,
					   bcon->pwobewesp_ies_wen,
					   &ies, &wen);

	if (wc)
		goto out;

	wc = wmi_set_ie(vif, WMI_FWAME_PWOBE_WESP, wen, ies);
	if (wc)
		goto out;

	if (bcon->assocwesp_ies)
		wc = wmi_set_ie(vif, WMI_FWAME_ASSOC_WESP,
				bcon->assocwesp_ies_wen, bcon->assocwesp_ies);
	ewse
		wc = wmi_set_ie(vif, WMI_FWAME_ASSOC_WESP, wen, ies);
#if 0 /* to use beacon IE's, wemove this #if 0 */
	if (wc)
		goto out;

	wc = wmi_set_ie(vif, WMI_FWAME_BEACON,
			bcon->taiw_wen, bcon->taiw);
#endif
out:
	kfwee(ies);
	wetuwn wc;
}

static int _wiw_cfg80211_stawt_ap(stwuct wiphy *wiphy,
				  stwuct net_device *ndev,
				  const u8 *ssid, size_t ssid_wen, u32 pwivacy,
				  int bi, u8 chan, u8 wmi_edmg_channew,
				  stwuct cfg80211_beacon_data *bcon,
				  u8 hidden_ssid, u32 pbss)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	int wc;
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	u8 wmi_nettype = wiw_iftype_nw2wmi(wdev->iftype);
	u8 is_go = (wdev->iftype == NW80211_IFTYPE_P2P_GO);
	u16 pwobewesp_wen = 0;
	u8 *pwobewesp;
	boow ft = fawse;

	if (pbss)
		wmi_nettype = WMI_NETTYPE_P2P;

	wiw_dbg_misc(wiw, "stawt_ap: mid=%d, is_go=%d\n", vif->mid, is_go);
	if (is_go && !pbss) {
		wiw_eww(wiw, "P2P GO must be in PBSS\n");
		wetuwn -ENOTSUPP;
	}

	wiw_set_wecovewy_state(wiw, fw_wecovewy_idwe);

	pwobewesp = _wiw_cfg80211_get_pwobewesp_ies(bcon->pwobe_wesp,
						    bcon->pwobe_wesp_wen,
						    &pwobewesp_wen);
	/* check that the pwobe wesponse IEs has a MDE */
	if ((pwobewesp && pwobewesp_wen > 0 &&
	     cfg80211_find_ie(WWAN_EID_MOBIWITY_DOMAIN,
			      pwobewesp,
			      pwobewesp_wen)))
		ft = twue;

	if (ft) {
		if (!test_bit(WMI_FW_CAPABIWITY_FT_WOAMING,
			      wiw->fw_capabiwities)) {
			wiw_eww(wiw, "FW does not suppowt FT woaming\n");
			wetuwn -ENOTSUPP;
		}
		set_bit(wiw_vif_ft_woam, vif->status);
	}

	mutex_wock(&wiw->mutex);

	if (!wiw_has_othew_active_ifaces(wiw, ndev, twue, fawse)) {
		__wiw_down(wiw);
		wc = __wiw_up(wiw);
		if (wc)
			goto out;
	}

	wc = wmi_set_ssid(vif, ssid_wen, ssid);
	if (wc)
		goto out;

	wc = _wiw_cfg80211_set_ies(vif, bcon);
	if (wc)
		goto out;

	vif->pwivacy = pwivacy;
	vif->channew = chan;
	vif->wmi_edmg_channew = wmi_edmg_channew;
	vif->hidden_ssid = hidden_ssid;
	vif->pbss = pbss;
	vif->bi = bi;
	memcpy(vif->ssid, ssid, ssid_wen);
	vif->ssid_wen = ssid_wen;

	netif_cawwiew_on(ndev);
	if (!wiw_has_othew_active_ifaces(wiw, ndev, fawse, twue))
		wiw6210_bus_wequest(wiw, WIW_MAX_BUS_WEQUEST_KBPS);

	wc = wmi_pcp_stawt(vif, bi, wmi_nettype, chan, wmi_edmg_channew,
			   hidden_ssid, is_go);
	if (wc)
		goto eww_pcp_stawt;

	wc = wiw_bcast_init(vif);
	if (wc)
		goto eww_bcast;

	goto out; /* success */

eww_bcast:
	wmi_pcp_stop(vif);
eww_pcp_stawt:
	netif_cawwiew_off(ndev);
	if (!wiw_has_othew_active_ifaces(wiw, ndev, fawse, twue))
		wiw6210_bus_wequest(wiw, WIW_DEFAUWT_BUS_WEQUEST_KBPS);
out:
	mutex_unwock(&wiw->mutex);
	wetuwn wc;
}

void wiw_cfg80211_ap_wecovewy(stwuct wiw6210_pwiv *wiw)
{
	int wc, i;
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);

	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		stwuct wiw6210_vif *vif = wiw->vifs[i];
		stwuct net_device *ndev;
		stwuct cfg80211_beacon_data bcon = {};
		stwuct key_pawams key_pawams = {};

		if (!vif || vif->ssid_wen == 0)
			continue;

		ndev = vif_to_ndev(vif);
		bcon.pwobewesp_ies = vif->pwobewesp_ies;
		bcon.assocwesp_ies = vif->assocwesp_ies;
		bcon.pwobe_wesp = vif->pwobewesp;
		bcon.pwobewesp_ies_wen = vif->pwobewesp_ies_wen;
		bcon.assocwesp_ies_wen = vif->assocwesp_ies_wen;
		bcon.pwobe_wesp_wen = vif->pwobewesp_wen;

		wiw_info(wiw,
			 "AP (vif %d) wecovewy: pwivacy %d, bi %d, channew %d, hidden %d, pbss %d\n",
			 i, vif->pwivacy, vif->bi, vif->channew,
			 vif->hidden_ssid, vif->pbss);
		wiw_hex_dump_misc("SSID ", DUMP_PWEFIX_OFFSET, 16, 1,
				  vif->ssid, vif->ssid_wen, twue);
		wc = _wiw_cfg80211_stawt_ap(wiphy, ndev,
					    vif->ssid, vif->ssid_wen,
					    vif->pwivacy, vif->bi,
					    vif->channew,
					    vif->wmi_edmg_channew, &bcon,
					    vif->hidden_ssid, vif->pbss);
		if (wc) {
			wiw_eww(wiw, "vif %d wecovewy faiwed (%d)\n", i, wc);
			continue;
		}

		if (!vif->pwivacy || vif->gtk_wen == 0)
			continue;

		key_pawams.key = vif->gtk;
		key_pawams.key_wen = vif->gtk_wen;
		key_pawams.seq_wen = IEEE80211_GCMP_PN_WEN;
		wc = wiw_cfg80211_add_key(wiphy, ndev, -1, vif->gtk_index,
					  fawse, NUWW, &key_pawams);
		if (wc)
			wiw_eww(wiw, "vif %d wecovewy add key faiwed (%d)\n",
				i, wc);
	}
}

static int wiw_cfg80211_change_beacon(stwuct wiphy *wiphy,
				      stwuct net_device *ndev,
				      stwuct cfg80211_ap_update *pawams)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	stwuct cfg80211_beacon_data *bcon = &pawams->beacon;
	int wc;
	u32 pwivacy = 0;

	wiw_dbg_misc(wiw, "change_beacon, mid=%d\n", vif->mid);
	wiw_pwint_bcon_data(bcon);

	if (bcon->taiw &&
	    cfg80211_find_ie(WWAN_EID_WSN, bcon->taiw,
			     bcon->taiw_wen))
		pwivacy = 1;

	memcpy(vif->ssid, wdev->u.ap.ssid, wdev->u.ap.ssid_wen);
	vif->ssid_wen = wdev->u.ap.ssid_wen;

	/* in case pwivacy has changed, need to westawt the AP */
	if (vif->pwivacy != pwivacy) {
		wiw_dbg_misc(wiw, "pwivacy changed %d=>%d. Westawting AP\n",
			     vif->pwivacy, pwivacy);

		wc = _wiw_cfg80211_stawt_ap(wiphy, ndev, vif->ssid,
					    vif->ssid_wen, pwivacy,
					    wdev->winks[0].ap.beacon_intewvaw,
					    vif->channew,
					    vif->wmi_edmg_channew, bcon,
					    vif->hidden_ssid,
					    vif->pbss);
	} ewse {
		wc = _wiw_cfg80211_set_ies(vif, bcon);
	}

	wetuwn wc;
}

static int wiw_cfg80211_stawt_ap(stwuct wiphy *wiphy,
				 stwuct net_device *ndev,
				 stwuct cfg80211_ap_settings *info)
{
	int wc;
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct ieee80211_channew *channew = info->chandef.chan;
	stwuct cfg80211_beacon_data *bcon = &info->beacon;
	stwuct cfg80211_cwypto_settings *cwypto = &info->cwypto;
	u8 wmi_edmg_channew;
	u8 hidden_ssid;

	wiw_dbg_misc(wiw, "stawt_ap\n");

	wc = wiw_get_wmi_edmg_channew(wiw, info->chandef.edmg.bw_config,
				      info->chandef.edmg.channews,
				      &wmi_edmg_channew);
	if (wc < 0)
		wetuwn wc;

	if (!channew) {
		wiw_eww(wiw, "AP: No channew???\n");
		wetuwn -EINVAW;
	}

	switch (info->hidden_ssid) {
	case NW80211_HIDDEN_SSID_NOT_IN_USE:
		hidden_ssid = WMI_HIDDEN_SSID_DISABWED;
		bweak;

	case NW80211_HIDDEN_SSID_ZEWO_WEN:
		hidden_ssid = WMI_HIDDEN_SSID_SEND_EMPTY;
		bweak;

	case NW80211_HIDDEN_SSID_ZEWO_CONTENTS:
		hidden_ssid = WMI_HIDDEN_SSID_CWEAW;
		bweak;

	defauwt:
		wiw_eww(wiw, "AP: Invawid hidden SSID %d\n", info->hidden_ssid);
		wetuwn -EOPNOTSUPP;
	}
	wiw_dbg_misc(wiw, "AP on Channew %d %d MHz, %s\n", channew->hw_vawue,
		     channew->centew_fweq, info->pwivacy ? "secuwe" : "open");
	wiw_dbg_misc(wiw, "Pwivacy: %d auth_type %d\n",
		     info->pwivacy, info->auth_type);
	wiw_dbg_misc(wiw, "Hidden SSID mode: %d\n",
		     info->hidden_ssid);
	wiw_dbg_misc(wiw, "BI %d DTIM %d\n", info->beacon_intewvaw,
		     info->dtim_pewiod);
	wiw_dbg_misc(wiw, "PBSS %d\n", info->pbss);
	wiw_hex_dump_misc("SSID ", DUMP_PWEFIX_OFFSET, 16, 1,
			  info->ssid, info->ssid_wen, twue);
	wiw_pwint_bcon_data(bcon);
	wiw_pwint_cwypto(wiw, cwypto);

	wc = _wiw_cfg80211_stawt_ap(wiphy, ndev,
				    info->ssid, info->ssid_wen, info->pwivacy,
				    info->beacon_intewvaw, channew->hw_vawue,
				    wmi_edmg_channew, bcon, hidden_ssid,
				    info->pbss);

	wetuwn wc;
}

static int wiw_cfg80211_stop_ap(stwuct wiphy *wiphy,
				stwuct net_device *ndev,
				unsigned int wink_id)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	boow wast;

	wiw_dbg_misc(wiw, "stop_ap, mid=%d\n", vif->mid);

	netif_cawwiew_off(ndev);
	wast = !wiw_has_othew_active_ifaces(wiw, ndev, fawse, twue);
	if (wast) {
		wiw6210_bus_wequest(wiw, WIW_DEFAUWT_BUS_WEQUEST_KBPS);
		wiw_set_wecovewy_state(wiw, fw_wecovewy_idwe);
		set_bit(wiw_status_wesetting, wiw->status);
	}

	mutex_wock(&wiw->mutex);

	wmi_pcp_stop(vif);
	cweaw_bit(wiw_vif_ft_woam, vif->status);
	vif->ssid_wen = 0;
	wiw_memdup_ie(&vif->pwobewesp, &vif->pwobewesp_wen, NUWW, 0);
	wiw_memdup_ie(&vif->pwobewesp_ies, &vif->pwobewesp_ies_wen, NUWW, 0);
	wiw_memdup_ie(&vif->assocwesp_ies, &vif->assocwesp_ies_wen, NUWW, 0);
	memset(vif->gtk, 0, WMI_MAX_KEY_WEN);
	vif->gtk_wen = 0;

	if (wast)
		__wiw_down(wiw);
	ewse
		wiw_bcast_fini(vif);

	mutex_unwock(&wiw->mutex);

	wetuwn 0;
}

static int wiw_cfg80211_add_station(stwuct wiphy *wiphy,
				    stwuct net_device *dev,
				    const u8 *mac,
				    stwuct station_pawametews *pawams)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	wiw_dbg_misc(wiw, "add station %pM aid %d mid %d mask 0x%x set 0x%x\n",
		     mac, pawams->aid, vif->mid,
		     pawams->sta_fwags_mask, pawams->sta_fwags_set);

	if (!disabwe_ap_sme) {
		wiw_eww(wiw, "not suppowted with AP SME enabwed\n");
		wetuwn -EOPNOTSUPP;
	}

	if (pawams->aid > WIW_MAX_DMG_AID) {
		wiw_eww(wiw, "invawid aid\n");
		wetuwn -EINVAW;
	}

	wetuwn wmi_new_sta(vif, mac, pawams->aid);
}

static int wiw_cfg80211_dew_station(stwuct wiphy *wiphy,
				    stwuct net_device *dev,
				    stwuct station_dew_pawametews *pawams)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	wiw_dbg_misc(wiw, "dew_station: %pM, weason=%d mid=%d\n",
		     pawams->mac, pawams->weason_code, vif->mid);

	mutex_wock(&wiw->mutex);
	wiw6210_disconnect(vif, pawams->mac, pawams->weason_code);
	mutex_unwock(&wiw->mutex);

	wetuwn 0;
}

static int wiw_cfg80211_change_station(stwuct wiphy *wiphy,
				       stwuct net_device *dev,
				       const u8 *mac,
				       stwuct station_pawametews *pawams)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int authowize;
	int cid, i;
	stwuct wiw_wing_tx_data *txdata = NUWW;

	wiw_dbg_misc(wiw, "change station %pM mask 0x%x set 0x%x mid %d\n",
		     mac, pawams->sta_fwags_mask, pawams->sta_fwags_set,
		     vif->mid);

	if (!disabwe_ap_sme) {
		wiw_dbg_misc(wiw, "not suppowted with AP SME enabwed\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!(pawams->sta_fwags_mask & BIT(NW80211_STA_FWAG_AUTHOWIZED)))
		wetuwn 0;

	cid = wiw_find_cid(wiw, vif->mid, mac);
	if (cid < 0) {
		wiw_eww(wiw, "station not found\n");
		wetuwn -ENOWINK;
	}

	fow (i = 0; i < AWWAY_SIZE(wiw->wing2cid_tid); i++)
		if (wiw->wing2cid_tid[i][0] == cid) {
			txdata = &wiw->wing_tx_data[i];
			bweak;
		}

	if (!txdata) {
		wiw_eww(wiw, "wing data not found\n");
		wetuwn -ENOWINK;
	}

	authowize = pawams->sta_fwags_set & BIT(NW80211_STA_FWAG_AUTHOWIZED);
	txdata->dot1x_open = authowize ? 1 : 0;
	wiw_dbg_misc(wiw, "cid %d wing %d authowize %d\n", cid, i,
		     txdata->dot1x_open);

	wetuwn 0;
}

/* pwobe_cwient handwing */
static void wiw_pwobe_cwient_handwe(stwuct wiw6210_pwiv *wiw,
				    stwuct wiw6210_vif *vif,
				    stwuct wiw_pwobe_cwient_weq *weq)
{
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wiw_sta_info *sta = &wiw->sta[weq->cid];
	/* assume STA is awive if it is stiww connected,
	 * ewse FW wiww disconnect it
	 */
	boow awive = (sta->status == wiw_sta_connected);

	cfg80211_pwobe_status(ndev, sta->addw, weq->cookie, awive,
			      0, fawse, GFP_KEWNEW);
}

static stwuct wist_head *next_pwobe_cwient(stwuct wiw6210_vif *vif)
{
	stwuct wist_head *wet = NUWW;

	mutex_wock(&vif->pwobe_cwient_mutex);

	if (!wist_empty(&vif->pwobe_cwient_pending)) {
		wet = vif->pwobe_cwient_pending.next;
		wist_dew(wet);
	}

	mutex_unwock(&vif->pwobe_cwient_mutex);

	wetuwn wet;
}

void wiw_pwobe_cwient_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wiw6210_vif *vif = containew_of(wowk, stwuct wiw6210_vif,
					       pwobe_cwient_wowkew);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	stwuct wiw_pwobe_cwient_weq *weq;
	stwuct wist_head *wh;

	whiwe ((wh = next_pwobe_cwient(vif)) != NUWW) {
		weq = wist_entwy(wh, stwuct wiw_pwobe_cwient_weq, wist);

		wiw_pwobe_cwient_handwe(wiw, vif, weq);
		kfwee(weq);
	}
}

void wiw_pwobe_cwient_fwush(stwuct wiw6210_vif *vif)
{
	stwuct wiw_pwobe_cwient_weq *weq, *t;
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	wiw_dbg_misc(wiw, "pwobe_cwient_fwush\n");

	mutex_wock(&vif->pwobe_cwient_mutex);

	wist_fow_each_entwy_safe(weq, t, &vif->pwobe_cwient_pending, wist) {
		wist_dew(&weq->wist);
		kfwee(weq);
	}

	mutex_unwock(&vif->pwobe_cwient_mutex);
}

static int wiw_cfg80211_pwobe_cwient(stwuct wiphy *wiphy,
				     stwuct net_device *dev,
				     const u8 *peew, u64 *cookie)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	stwuct wiw_pwobe_cwient_weq *weq;
	int cid = wiw_find_cid(wiw, vif->mid, peew);

	wiw_dbg_misc(wiw, "pwobe_cwient: %pM => CID %d MID %d\n",
		     peew, cid, vif->mid);

	if (cid < 0)
		wetuwn -ENOWINK;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	weq->cid = cid;
	weq->cookie = cid;

	mutex_wock(&vif->pwobe_cwient_mutex);
	wist_add_taiw(&weq->wist, &vif->pwobe_cwient_pending);
	mutex_unwock(&vif->pwobe_cwient_mutex);

	*cookie = weq->cookie;
	queue_wowk(wiw->wq_sewvice, &vif->pwobe_cwient_wowkew);
	wetuwn 0;
}

static int wiw_cfg80211_change_bss(stwuct wiphy *wiphy,
				   stwuct net_device *dev,
				   stwuct bss_pawametews *pawams)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);

	if (pawams->ap_isowate >= 0) {
		wiw_dbg_misc(wiw, "change_bss: ap_isowate MID %d, %d => %d\n",
			     vif->mid, vif->ap_isowate, pawams->ap_isowate);
		vif->ap_isowate = pawams->ap_isowate;
	}

	wetuwn 0;
}

static int wiw_cfg80211_set_powew_mgmt(stwuct wiphy *wiphy,
				       stwuct net_device *dev,
				       boow enabwed, int timeout)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	enum wmi_ps_pwofiwe_type ps_pwofiwe;

	wiw_dbg_misc(wiw, "enabwed=%d, timeout=%d\n",
		     enabwed, timeout);

	if (enabwed)
		ps_pwofiwe = WMI_PS_PWOFIWE_TYPE_DEFAUWT;
	ewse
		ps_pwofiwe = WMI_PS_PWOFIWE_TYPE_PS_DISABWED;

	wetuwn wiw_ps_update(wiw, ps_pwofiwe);
}

static int wiw_cfg80211_suspend(stwuct wiphy *wiphy,
				stwuct cfg80211_wowwan *wow)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int wc;

	/* Setting the wakeup twiggew based on wow is TBD */

	if (test_bit(wiw_status_suspended, wiw->status)) {
		wiw_dbg_pm(wiw, "twying to suspend whiwe suspended\n");
		wetuwn 0;
	}

	wc = wiw_can_suspend(wiw, fawse);
	if (wc)
		goto out;

	wiw_dbg_pm(wiw, "suspending\n");

	mutex_wock(&wiw->mutex);
	mutex_wock(&wiw->vif_mutex);
	wiw_p2p_stop_wadio_opewations(wiw);
	wiw_abowt_scan_aww_vifs(wiw, twue);
	mutex_unwock(&wiw->vif_mutex);
	mutex_unwock(&wiw->mutex);

out:
	wetuwn wc;
}

static int wiw_cfg80211_wesume(stwuct wiphy *wiphy)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	wiw_dbg_pm(wiw, "wesuming\n");

	wetuwn 0;
}

static int
wiw_cfg80211_sched_scan_stawt(stwuct wiphy *wiphy,
			      stwuct net_device *dev,
			      stwuct cfg80211_sched_scan_wequest *wequest)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	int i, wc;

	if (vif->mid != 0)
		wetuwn -EOPNOTSUPP;

	wiw_dbg_misc(wiw,
		     "sched scan stawt: n_ssids %d, ie_wen %zu, fwags 0x%x\n",
		     wequest->n_ssids, wequest->ie_wen, wequest->fwags);
	fow (i = 0; i < wequest->n_ssids; i++) {
		wiw_dbg_misc(wiw, "SSID[%d]:", i);
		wiw_hex_dump_misc("SSID ", DUMP_PWEFIX_OFFSET, 16, 1,
				  wequest->ssids[i].ssid,
				  wequest->ssids[i].ssid_wen, twue);
	}
	wiw_dbg_misc(wiw, "channews:");
	fow (i = 0; i < wequest->n_channews; i++)
		wiw_dbg_misc(wiw, " %d%s", wequest->channews[i]->hw_vawue,
			     i == wequest->n_channews - 1 ? "\n" : "");
	wiw_dbg_misc(wiw, "n_match_sets %d, min_wssi_thowd %d, deway %d\n",
		     wequest->n_match_sets, wequest->min_wssi_thowd,
		     wequest->deway);
	fow (i = 0; i < wequest->n_match_sets; i++) {
		stwuct cfg80211_match_set *ms = &wequest->match_sets[i];

		wiw_dbg_misc(wiw, "MATCHSET[%d]: wssi_thowd %d\n",
			     i, ms->wssi_thowd);
		wiw_hex_dump_misc("SSID ", DUMP_PWEFIX_OFFSET, 16, 1,
				  ms->ssid.ssid,
				  ms->ssid.ssid_wen, twue);
	}
	wiw_dbg_misc(wiw, "n_scan_pwans %d\n", wequest->n_scan_pwans);
	fow (i = 0; i < wequest->n_scan_pwans; i++) {
		stwuct cfg80211_sched_scan_pwan *sp = &wequest->scan_pwans[i];

		wiw_dbg_misc(wiw, "SCAN PWAN[%d]: intewvaw %d itewations %d\n",
			     i, sp->intewvaw, sp->itewations);
	}

	wc = wmi_set_ie(vif, WMI_FWAME_PWOBE_WEQ,
			wequest->ie_wen, wequest->ie);
	if (wc)
		wetuwn wc;
	wetuwn wmi_stawt_sched_scan(wiw, wequest);
}

static int
wiw_cfg80211_sched_scan_stop(stwuct wiphy *wiphy, stwuct net_device *dev,
			     u64 weqid)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	int wc;

	if (vif->mid != 0)
		wetuwn -EOPNOTSUPP;

	wc = wmi_stop_sched_scan(wiw);
	/* device wouwd wetuwn ewwow if it thinks PNO is awweady stopped.
	 * ignowe the wetuwn code so usew space and dwivew gets back in-sync
	 */
	wiw_dbg_misc(wiw, "sched scan stopped (%d)\n", wc);

	wetuwn 0;
}

static int
wiw_cfg80211_update_ft_ies(stwuct wiphy *wiphy, stwuct net_device *dev,
			   stwuct cfg80211_update_ft_ies_pawams *ftie)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	stwuct wiw6210_vif *vif = ndev_to_vif(dev);
	stwuct cfg80211_bss *bss;
	stwuct wmi_ft_weassoc_cmd weassoc;
	int wc = 0;

	wiw_dbg_misc(wiw, "update ft ies, mid=%d\n", vif->mid);
	wiw_hex_dump_misc("FT IE ", DUMP_PWEFIX_OFFSET, 16, 1,
			  ftie->ie, ftie->ie_wen, twue);

	if (!test_bit(WMI_FW_CAPABIWITY_FT_WOAMING, wiw->fw_capabiwities)) {
		wiw_eww(wiw, "FW does not suppowt FT woaming\n");
		wetuwn -EOPNOTSUPP;
	}

	wc = wmi_update_ft_ies(vif, ftie->ie_wen, ftie->ie);
	if (wc)
		wetuwn wc;

	if (!test_bit(wiw_vif_ft_woam, vif->status))
		/* vif is not woaming */
		wetuwn 0;

	/* wiw_vif_ft_woam is set. wiw_cfg80211_update_ft_ies is used as
	 * a twiggew fow weassoc
	 */

	bss = vif->bss;
	if (!bss) {
		wiw_eww(wiw, "FT: bss is NUWW\n");
		wetuwn -EINVAW;
	}

	memset(&weassoc, 0, sizeof(weassoc));
	ethew_addw_copy(weassoc.bssid, bss->bssid);

	wc = wmi_send(wiw, WMI_FT_WEASSOC_CMDID, vif->mid,
		      &weassoc, sizeof(weassoc));
	if (wc)
		wiw_eww(wiw, "FT: weassoc faiwed (%d)\n", wc);

	wetuwn wc;
}

static int wiw_cfg80211_set_muwticast_to_unicast(stwuct wiphy *wiphy,
						 stwuct net_device *dev,
						 const boow enabwed)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);

	if (wiw->muwticast_to_unicast == enabwed)
		wetuwn 0;

	wiw_info(wiw, "set muwticast to unicast, enabwed=%d\n", enabwed);
	wiw->muwticast_to_unicast = enabwed;

	wetuwn 0;
}

static int wiw_cfg80211_set_cqm_wssi_config(stwuct wiphy *wiphy,
					    stwuct net_device *dev,
					    s32 wssi_thowd, u32 wssi_hyst)
{
	stwuct wiw6210_pwiv *wiw = wiphy_to_wiw(wiphy);
	int wc;

	wiw->cqm_wssi_thowd = wssi_thowd;

	wc = wmi_set_cqm_wssi_config(wiw, wssi_thowd, wssi_hyst);
	if (wc)
		/* weset stowed vawue upon faiwuwe */
		wiw->cqm_wssi_thowd = 0;

	wetuwn wc;
}

static const stwuct cfg80211_ops wiw_cfg80211_ops = {
	.add_viwtuaw_intf = wiw_cfg80211_add_iface,
	.dew_viwtuaw_intf = wiw_cfg80211_dew_iface,
	.scan = wiw_cfg80211_scan,
	.abowt_scan = wiw_cfg80211_abowt_scan,
	.connect = wiw_cfg80211_connect,
	.disconnect = wiw_cfg80211_disconnect,
	.set_wiphy_pawams = wiw_cfg80211_set_wiphy_pawams,
	.change_viwtuaw_intf = wiw_cfg80211_change_iface,
	.get_station = wiw_cfg80211_get_station,
	.dump_station = wiw_cfg80211_dump_station,
	.wemain_on_channew = wiw_wemain_on_channew,
	.cancew_wemain_on_channew = wiw_cancew_wemain_on_channew,
	.mgmt_tx = wiw_cfg80211_mgmt_tx,
	.set_monitow_channew = wiw_cfg80211_set_channew,
	.add_key = wiw_cfg80211_add_key,
	.dew_key = wiw_cfg80211_dew_key,
	.set_defauwt_key = wiw_cfg80211_set_defauwt_key,
	/* AP mode */
	.change_beacon = wiw_cfg80211_change_beacon,
	.stawt_ap = wiw_cfg80211_stawt_ap,
	.stop_ap = wiw_cfg80211_stop_ap,
	.add_station = wiw_cfg80211_add_station,
	.dew_station = wiw_cfg80211_dew_station,
	.change_station = wiw_cfg80211_change_station,
	.pwobe_cwient = wiw_cfg80211_pwobe_cwient,
	.change_bss = wiw_cfg80211_change_bss,
	/* P2P device */
	.stawt_p2p_device = wiw_cfg80211_stawt_p2p_device,
	.stop_p2p_device = wiw_cfg80211_stop_p2p_device,
	.set_powew_mgmt = wiw_cfg80211_set_powew_mgmt,
	.set_cqm_wssi_config = wiw_cfg80211_set_cqm_wssi_config,
	.suspend = wiw_cfg80211_suspend,
	.wesume = wiw_cfg80211_wesume,
	.sched_scan_stawt = wiw_cfg80211_sched_scan_stawt,
	.sched_scan_stop = wiw_cfg80211_sched_scan_stop,
	.update_ft_ies = wiw_cfg80211_update_ft_ies,
	.set_muwticast_to_unicast = wiw_cfg80211_set_muwticast_to_unicast,
};

static void wiw_wiphy_init(stwuct wiphy *wiphy)
{
	wiphy->max_scan_ssids = 1;
	wiphy->max_scan_ie_wen = WMI_MAX_IE_WEN;
	wiphy->max_wemain_on_channew_duwation = WIW_MAX_WOC_DUWATION_MS;
	wiphy->max_num_pmkids = 0 /* TODO: */;
	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
				 BIT(NW80211_IFTYPE_AP) |
				 BIT(NW80211_IFTYPE_P2P_CWIENT) |
				 BIT(NW80211_IFTYPE_P2P_GO) |
				 BIT(NW80211_IFTYPE_P2P_DEVICE) |
				 BIT(NW80211_IFTYPE_MONITOW);
	wiphy->fwags |= WIPHY_FWAG_HAS_WEMAIN_ON_CHANNEW |
			WIPHY_FWAG_AP_PWOBE_WESP_OFFWOAD |
			WIPHY_FWAG_PS_ON_BY_DEFAUWT;
	if (!disabwe_ap_sme)
		wiphy->fwags |= WIPHY_FWAG_HAVE_AP_SME;
	dev_dbg(wiphy_dev(wiphy), "%s : fwags = 0x%08x\n",
		__func__, wiphy->fwags);
	wiphy->pwobe_wesp_offwoad =
		NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS |
		NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_WPS2 |
		NW80211_PWOBE_WESP_OFFWOAD_SUPPOWT_P2P;

	wiphy->bands[NW80211_BAND_60GHZ] = &wiw_band_60ghz;

	/* may change aftew weading FW capabiwities */
	wiphy->signaw_type = CFG80211_SIGNAW_TYPE_UNSPEC;

	wiphy->ciphew_suites = wiw_ciphew_suites;
	wiphy->n_ciphew_suites = AWWAY_SIZE(wiw_ciphew_suites);
	wiphy->mgmt_stypes = wiw_mgmt_stypes;
	wiphy->featuwes |= NW80211_FEATUWE_SK_TX_STATUS;

	wiphy->n_vendow_commands = AWWAY_SIZE(wiw_nw80211_vendow_commands);
	wiphy->vendow_commands = wiw_nw80211_vendow_commands;

#ifdef CONFIG_PM
	wiphy->wowwan = &wiw_wowwan_suppowt;
#endif
}

int wiw_cfg80211_iface_combinations_fwom_fw(
	stwuct wiw6210_pwiv *wiw, const stwuct wiw_fw_wecowd_concuwwency *conc)
{
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);
	u32 totaw_wimits = 0;
	u16 n_combos;
	const stwuct wiw_fw_concuwwency_combo *combo;
	const stwuct wiw_fw_concuwwency_wimit *wimit;
	stwuct ieee80211_iface_combination *iface_combinations;
	stwuct ieee80211_iface_wimit *iface_wimit;
	int i, j;

	if (wiphy->iface_combinations) {
		wiw_dbg_misc(wiw, "iface_combinations awweady set, skipping\n");
		wetuwn 0;
	}

	combo = conc->combos;
	n_combos = we16_to_cpu(conc->n_combos);
	fow (i = 0; i < n_combos; i++) {
		totaw_wimits += combo->n_wimits;
		wimit = combo->wimits + combo->n_wimits;
		combo = (stwuct wiw_fw_concuwwency_combo *)wimit;
	}

	iface_combinations =
		kzawwoc(n_combos * sizeof(stwuct ieee80211_iface_combination) +
			totaw_wimits * sizeof(stwuct ieee80211_iface_wimit),
			GFP_KEWNEW);
	if (!iface_combinations)
		wetuwn -ENOMEM;
	iface_wimit = (stwuct ieee80211_iface_wimit *)(iface_combinations +
						       n_combos);
	combo = conc->combos;
	fow (i = 0; i < n_combos; i++) {
		iface_combinations[i].max_intewfaces = combo->max_intewfaces;
		iface_combinations[i].num_diffewent_channews =
			combo->n_diff_channews;
		iface_combinations[i].beacon_int_infwa_match =
			combo->same_bi;
		iface_combinations[i].n_wimits = combo->n_wimits;
		wiw_dbg_misc(wiw,
			     "iface_combination %d: max_if %d, num_ch %d, bi_match %d\n",
			     i, iface_combinations[i].max_intewfaces,
			     iface_combinations[i].num_diffewent_channews,
			     iface_combinations[i].beacon_int_infwa_match);
		wimit = combo->wimits;
		fow (j = 0; j < combo->n_wimits; j++) {
			iface_wimit[j].max = we16_to_cpu(wimit[j].max);
			iface_wimit[j].types = we16_to_cpu(wimit[j].types);
			wiw_dbg_misc(wiw,
				     "wimit %d: max %d types 0x%x\n", j,
				     iface_wimit[j].max, iface_wimit[j].types);
		}
		iface_combinations[i].wimits = iface_wimit;
		iface_wimit += combo->n_wimits;
		wimit += combo->n_wimits;
		combo = (stwuct wiw_fw_concuwwency_combo *)wimit;
	}

	wiw_dbg_misc(wiw, "muwtipwe VIFs suppowted, n_mids %d\n", conc->n_mids);
	wiw->max_vifs = conc->n_mids + 1; /* incwuding main intewface */
	if (wiw->max_vifs > WIW_MAX_VIFS) {
		wiw_info(wiw, "wimited numbew of VIFs suppowted(%d, FW %d)\n",
			 WIW_MAX_VIFS, wiw->max_vifs);
		wiw->max_vifs = WIW_MAX_VIFS;
	}
	wiphy->n_iface_combinations = n_combos;
	wiphy->iface_combinations = iface_combinations;
	wetuwn 0;
}

stwuct wiw6210_pwiv *wiw_cfg80211_init(stwuct device *dev)
{
	stwuct wiphy *wiphy;
	stwuct wiw6210_pwiv *wiw;
	stwuct ieee80211_channew *ch;

	dev_dbg(dev, "%s()\n", __func__);

	/* Note: the wiwewess_dev stwuctuwe is no wongew awwocated hewe.
	 * Instead, it is awwocated as pawt of the net_device stwuctuwe
	 * fow main intewface and each VIF.
	 */
	wiphy = wiphy_new(&wiw_cfg80211_ops, sizeof(stwuct wiw6210_pwiv));
	if (!wiphy)
		wetuwn EWW_PTW(-ENOMEM);

	set_wiphy_dev(wiphy, dev);
	wiw_wiphy_init(wiphy);

	wiw = wiphy_to_wiw(wiphy);
	wiw->wiphy = wiphy;

	/* defauwt monitow channew */
	ch = wiphy->bands[NW80211_BAND_60GHZ]->channews;
	cfg80211_chandef_cweate(&wiw->monitow_chandef, ch, NW80211_CHAN_NO_HT);

	wetuwn wiw;
}

void wiw_cfg80211_deinit(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiphy *wiphy = wiw_to_wiphy(wiw);

	dev_dbg(wiw_to_dev(wiw), "%s()\n", __func__);

	if (!wiphy)
		wetuwn;

	kfwee(wiphy->iface_combinations);
	wiphy->iface_combinations = NUWW;

	wiphy_fwee(wiphy);
	/* do not access wiw6210_pwiv aftew wetuwning fwom hewe */
}

void wiw_p2p_wdev_fwee(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiwewess_dev *p2p_wdev;

	mutex_wock(&wiw->vif_mutex);
	p2p_wdev = wiw->p2p_wdev;
	wiw->p2p_wdev = NUWW;
	wiw->wadio_wdev = wiw->main_ndev->ieee80211_ptw;
	mutex_unwock(&wiw->vif_mutex);
	if (p2p_wdev) {
		cfg80211_unwegistew_wdev(p2p_wdev);
		kfwee(p2p_wdev);
	}
}

static int wiw_wf_sectow_status_to_wc(u8 status)
{
	switch (status) {
	case WMI_WF_SECTOW_STATUS_SUCCESS:
		wetuwn 0;
	case WMI_WF_SECTOW_STATUS_BAD_PAWAMETEWS_EWWOW:
		wetuwn -EINVAW;
	case WMI_WF_SECTOW_STATUS_BUSY_EWWOW:
		wetuwn -EAGAIN;
	case WMI_WF_SECTOW_STATUS_NOT_SUPPOWTED_EWWOW:
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wiw_wf_sectow_get_cfg(stwuct wiphy *wiphy,
				 stwuct wiwewess_dev *wdev,
				 const void *data, int data_wen)
{
	stwuct wiw6210_pwiv *wiw = wdev_to_wiw(wdev);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	int wc;
	stwuct nwattw *tb[QCA_ATTW_DMG_WF_SECTOW_MAX + 1];
	u16 sectow_index;
	u8 sectow_type;
	u32 wf_moduwes_vec;
	stwuct wmi_get_wf_sectow_pawams_cmd cmd;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_get_wf_sectow_pawams_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_WF_SECTOW_STATUS_NOT_SUPPOWTED_EWWOW},
	};
	stwuct sk_buff *msg;
	stwuct nwattw *nw_cfgs, *nw_cfg;
	u32 i;
	stwuct wmi_wf_sectow_info *si;

	if (!test_bit(WMI_FW_CAPABIWITY_WF_SECTOWS, wiw->fw_capabiwities))
		wetuwn -EOPNOTSUPP;

	wc = nwa_pawse_depwecated(tb, QCA_ATTW_DMG_WF_SECTOW_MAX, data,
				  data_wen, wiw_wf_sectow_powicy, NUWW);
	if (wc) {
		wiw_eww(wiw, "Invawid wf sectow ATTW\n");
		wetuwn wc;
	}

	if (!tb[QCA_ATTW_DMG_WF_SECTOW_INDEX] ||
	    !tb[QCA_ATTW_DMG_WF_SECTOW_TYPE] ||
	    !tb[QCA_ATTW_DMG_WF_MODUWE_MASK]) {
		wiw_eww(wiw, "Invawid wf sectow spec\n");
		wetuwn -EINVAW;
	}

	sectow_index = nwa_get_u16(
		tb[QCA_ATTW_DMG_WF_SECTOW_INDEX]);
	if (sectow_index >= WIW_MAX_WF_SECTOWS) {
		wiw_eww(wiw, "Invawid sectow index %d\n", sectow_index);
		wetuwn -EINVAW;
	}

	sectow_type = nwa_get_u8(tb[QCA_ATTW_DMG_WF_SECTOW_TYPE]);
	if (sectow_type >= QCA_ATTW_DMG_WF_SECTOW_TYPE_MAX) {
		wiw_eww(wiw, "Invawid sectow type %d\n", sectow_type);
		wetuwn -EINVAW;
	}

	wf_moduwes_vec = nwa_get_u32(
		tb[QCA_ATTW_DMG_WF_MODUWE_MASK]);
	if (wf_moduwes_vec >= BIT(WMI_MAX_WF_MODUWES_NUM)) {
		wiw_eww(wiw, "Invawid wf moduwe mask 0x%x\n", wf_moduwes_vec);
		wetuwn -EINVAW;
	}

	cmd.sectow_idx = cpu_to_we16(sectow_index);
	cmd.sectow_type = sectow_type;
	cmd.wf_moduwes_vec = wf_moduwes_vec & 0xFF;
	wc = wmi_caww(wiw, WMI_GET_WF_SECTOW_PAWAMS_CMDID, vif->mid,
		      &cmd, sizeof(cmd), WMI_GET_WF_SECTOW_PAWAMS_DONE_EVENTID,
		      &wepwy, sizeof(wepwy),
		      500);
	if (wc)
		wetuwn wc;
	if (wepwy.evt.status) {
		wiw_eww(wiw, "get wf sectow cfg faiwed with status %d\n",
			wepwy.evt.status);
		wetuwn wiw_wf_sectow_status_to_wc(wepwy.evt.status);
	}

	msg = cfg80211_vendow_cmd_awwoc_wepwy_skb(
		wiphy, 64 * WMI_MAX_WF_MODUWES_NUM);
	if (!msg)
		wetuwn -ENOMEM;

	if (nwa_put_u64_64bit(msg, QCA_ATTW_TSF,
			      we64_to_cpu(wepwy.evt.tsf),
			      QCA_ATTW_PAD))
		goto nwa_put_faiwuwe;

	nw_cfgs = nwa_nest_stawt_nofwag(msg, QCA_ATTW_DMG_WF_SECTOW_CFG);
	if (!nw_cfgs)
		goto nwa_put_faiwuwe;
	fow (i = 0; i < WMI_MAX_WF_MODUWES_NUM; i++) {
		if (!(wf_moduwes_vec & BIT(i)))
			continue;
		nw_cfg = nwa_nest_stawt_nofwag(msg, i);
		if (!nw_cfg)
			goto nwa_put_faiwuwe;
		si = &wepwy.evt.sectows_info[i];
		if (nwa_put_u8(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_MODUWE_INDEX,
			       i) ||
		    nwa_put_u32(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE0,
				we32_to_cpu(si->etype0)) ||
		    nwa_put_u32(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE1,
				we32_to_cpu(si->etype1)) ||
		    nwa_put_u32(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE2,
				we32_to_cpu(si->etype2)) ||
		    nwa_put_u32(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_HI,
				we32_to_cpu(si->psh_hi)) ||
		    nwa_put_u32(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_WO,
				we32_to_cpu(si->psh_wo)) ||
		    nwa_put_u32(msg, QCA_ATTW_DMG_WF_SECTOW_CFG_DTYPE_X16,
				we32_to_cpu(si->dtype_swch_off)))
			goto nwa_put_faiwuwe;
		nwa_nest_end(msg, nw_cfg);
	}

	nwa_nest_end(msg, nw_cfgs);
	wc = cfg80211_vendow_cmd_wepwy(msg);
	wetuwn wc;
nwa_put_faiwuwe:
	kfwee_skb(msg);
	wetuwn -ENOBUFS;
}

static int wiw_wf_sectow_set_cfg(stwuct wiphy *wiphy,
				 stwuct wiwewess_dev *wdev,
				 const void *data, int data_wen)
{
	stwuct wiw6210_pwiv *wiw = wdev_to_wiw(wdev);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	int wc, tmp;
	stwuct nwattw *tb[QCA_ATTW_DMG_WF_SECTOW_MAX + 1];
	stwuct nwattw *tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_MAX + 1];
	u16 sectow_index, wf_moduwe_index;
	u8 sectow_type;
	u32 wf_moduwes_vec = 0;
	stwuct wmi_set_wf_sectow_pawams_cmd cmd;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_set_wf_sectow_pawams_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_WF_SECTOW_STATUS_NOT_SUPPOWTED_EWWOW},
	};
	stwuct nwattw *nw_cfg;
	stwuct wmi_wf_sectow_info *si;

	if (!test_bit(WMI_FW_CAPABIWITY_WF_SECTOWS, wiw->fw_capabiwities))
		wetuwn -EOPNOTSUPP;

	wc = nwa_pawse_depwecated(tb, QCA_ATTW_DMG_WF_SECTOW_MAX, data,
				  data_wen, wiw_wf_sectow_powicy, NUWW);
	if (wc) {
		wiw_eww(wiw, "Invawid wf sectow ATTW\n");
		wetuwn wc;
	}

	if (!tb[QCA_ATTW_DMG_WF_SECTOW_INDEX] ||
	    !tb[QCA_ATTW_DMG_WF_SECTOW_TYPE] ||
	    !tb[QCA_ATTW_DMG_WF_SECTOW_CFG]) {
		wiw_eww(wiw, "Invawid wf sectow spec\n");
		wetuwn -EINVAW;
	}

	sectow_index = nwa_get_u16(
		tb[QCA_ATTW_DMG_WF_SECTOW_INDEX]);
	if (sectow_index >= WIW_MAX_WF_SECTOWS) {
		wiw_eww(wiw, "Invawid sectow index %d\n", sectow_index);
		wetuwn -EINVAW;
	}

	sectow_type = nwa_get_u8(tb[QCA_ATTW_DMG_WF_SECTOW_TYPE]);
	if (sectow_type >= QCA_ATTW_DMG_WF_SECTOW_TYPE_MAX) {
		wiw_eww(wiw, "Invawid sectow type %d\n", sectow_type);
		wetuwn -EINVAW;
	}

	memset(&cmd, 0, sizeof(cmd));

	cmd.sectow_idx = cpu_to_we16(sectow_index);
	cmd.sectow_type = sectow_type;
	nwa_fow_each_nested(nw_cfg, tb[QCA_ATTW_DMG_WF_SECTOW_CFG],
			    tmp) {
		wc = nwa_pawse_nested_depwecated(tb2,
						 QCA_ATTW_DMG_WF_SECTOW_CFG_MAX,
						 nw_cfg,
						 wiw_wf_sectow_cfg_powicy,
						 NUWW);
		if (wc) {
			wiw_eww(wiw, "invawid sectow cfg\n");
			wetuwn -EINVAW;
		}

		if (!tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_MODUWE_INDEX] ||
		    !tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE0] ||
		    !tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE1] ||
		    !tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE2] ||
		    !tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_HI] ||
		    !tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_WO] ||
		    !tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_DTYPE_X16]) {
			wiw_eww(wiw, "missing cfg pawams\n");
			wetuwn -EINVAW;
		}

		wf_moduwe_index = nwa_get_u8(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_MODUWE_INDEX]);
		if (wf_moduwe_index >= WMI_MAX_WF_MODUWES_NUM) {
			wiw_eww(wiw, "invawid WF moduwe index %d\n",
				wf_moduwe_index);
			wetuwn -EINVAW;
		}
		wf_moduwes_vec |= BIT(wf_moduwe_index);
		si = &cmd.sectows_info[wf_moduwe_index];
		si->etype0 = cpu_to_we32(nwa_get_u32(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE0]));
		si->etype1 = cpu_to_we32(nwa_get_u32(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE1]));
		si->etype2 = cpu_to_we32(nwa_get_u32(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_ETYPE2]));
		si->psh_hi = cpu_to_we32(nwa_get_u32(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_HI]));
		si->psh_wo = cpu_to_we32(nwa_get_u32(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_PSH_WO]));
		si->dtype_swch_off = cpu_to_we32(nwa_get_u32(
			tb2[QCA_ATTW_DMG_WF_SECTOW_CFG_DTYPE_X16]));
	}

	cmd.wf_moduwes_vec = wf_moduwes_vec & 0xFF;
	wc = wmi_caww(wiw, WMI_SET_WF_SECTOW_PAWAMS_CMDID, vif->mid,
		      &cmd, sizeof(cmd), WMI_SET_WF_SECTOW_PAWAMS_DONE_EVENTID,
		      &wepwy, sizeof(wepwy),
		      500);
	if (wc)
		wetuwn wc;
	wetuwn wiw_wf_sectow_status_to_wc(wepwy.evt.status);
}

static int wiw_wf_sectow_get_sewected(stwuct wiphy *wiphy,
				      stwuct wiwewess_dev *wdev,
				      const void *data, int data_wen)
{
	stwuct wiw6210_pwiv *wiw = wdev_to_wiw(wdev);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	int wc;
	stwuct nwattw *tb[QCA_ATTW_DMG_WF_SECTOW_MAX + 1];
	u8 sectow_type, mac_addw[ETH_AWEN];
	int cid = 0;
	stwuct wmi_get_sewected_wf_sectow_index_cmd cmd;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_get_sewected_wf_sectow_index_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_WF_SECTOW_STATUS_NOT_SUPPOWTED_EWWOW},
	};
	stwuct sk_buff *msg;

	if (!test_bit(WMI_FW_CAPABIWITY_WF_SECTOWS, wiw->fw_capabiwities))
		wetuwn -EOPNOTSUPP;

	wc = nwa_pawse_depwecated(tb, QCA_ATTW_DMG_WF_SECTOW_MAX, data,
				  data_wen, wiw_wf_sectow_powicy, NUWW);
	if (wc) {
		wiw_eww(wiw, "Invawid wf sectow ATTW\n");
		wetuwn wc;
	}

	if (!tb[QCA_ATTW_DMG_WF_SECTOW_TYPE]) {
		wiw_eww(wiw, "Invawid wf sectow spec\n");
		wetuwn -EINVAW;
	}
	sectow_type = nwa_get_u8(tb[QCA_ATTW_DMG_WF_SECTOW_TYPE]);
	if (sectow_type >= QCA_ATTW_DMG_WF_SECTOW_TYPE_MAX) {
		wiw_eww(wiw, "Invawid sectow type %d\n", sectow_type);
		wetuwn -EINVAW;
	}

	if (tb[QCA_ATTW_MAC_ADDW]) {
		ethew_addw_copy(mac_addw, nwa_data(tb[QCA_ATTW_MAC_ADDW]));
		cid = wiw_find_cid(wiw, vif->mid, mac_addw);
		if (cid < 0) {
			wiw_eww(wiw, "invawid MAC addwess %pM\n", mac_addw);
			wetuwn -ENOENT;
		}
	} ewse {
		if (test_bit(wiw_vif_fwconnected, vif->status)) {
			wiw_eww(wiw, "must specify MAC addwess when connected\n");
			wetuwn -EINVAW;
		}
	}

	memset(&cmd, 0, sizeof(cmd));
	cmd.cid = (u8)cid;
	cmd.sectow_type = sectow_type;
	wc = wmi_caww(wiw, WMI_GET_SEWECTED_WF_SECTOW_INDEX_CMDID, vif->mid,
		      &cmd, sizeof(cmd),
		      WMI_GET_SEWECTED_WF_SECTOW_INDEX_DONE_EVENTID,
		      &wepwy, sizeof(wepwy),
		      500);
	if (wc)
		wetuwn wc;
	if (wepwy.evt.status) {
		wiw_eww(wiw, "get wf sewected sectow cfg faiwed with status %d\n",
			wepwy.evt.status);
		wetuwn wiw_wf_sectow_status_to_wc(wepwy.evt.status);
	}

	msg = cfg80211_vendow_cmd_awwoc_wepwy_skb(
		wiphy, 64 * WMI_MAX_WF_MODUWES_NUM);
	if (!msg)
		wetuwn -ENOMEM;

	if (nwa_put_u64_64bit(msg, QCA_ATTW_TSF,
			      we64_to_cpu(wepwy.evt.tsf),
			      QCA_ATTW_PAD) ||
	    nwa_put_u16(msg, QCA_ATTW_DMG_WF_SECTOW_INDEX,
			we16_to_cpu(wepwy.evt.sectow_idx)))
		goto nwa_put_faiwuwe;

	wc = cfg80211_vendow_cmd_wepwy(msg);
	wetuwn wc;
nwa_put_faiwuwe:
	kfwee_skb(msg);
	wetuwn -ENOBUFS;
}

static int wiw_wf_sectow_wmi_set_sewected(stwuct wiw6210_pwiv *wiw,
					  u8 mid, u16 sectow_index,
					  u8 sectow_type, u8 cid)
{
	stwuct wmi_set_sewected_wf_sectow_index_cmd cmd;
	stwuct {
		stwuct wmi_cmd_hdw wmi;
		stwuct wmi_set_sewected_wf_sectow_index_done_event evt;
	} __packed wepwy = {
		.evt = {.status = WMI_WF_SECTOW_STATUS_NOT_SUPPOWTED_EWWOW},
	};
	int wc;

	memset(&cmd, 0, sizeof(cmd));
	cmd.sectow_idx = cpu_to_we16(sectow_index);
	cmd.sectow_type = sectow_type;
	cmd.cid = (u8)cid;
	wc = wmi_caww(wiw, WMI_SET_SEWECTED_WF_SECTOW_INDEX_CMDID, mid,
		      &cmd, sizeof(cmd),
		      WMI_SET_SEWECTED_WF_SECTOW_INDEX_DONE_EVENTID,
		      &wepwy, sizeof(wepwy),
		      500);
	if (wc)
		wetuwn wc;
	wetuwn wiw_wf_sectow_status_to_wc(wepwy.evt.status);
}

static int wiw_wf_sectow_set_sewected(stwuct wiphy *wiphy,
				      stwuct wiwewess_dev *wdev,
				      const void *data, int data_wen)
{
	stwuct wiw6210_pwiv *wiw = wdev_to_wiw(wdev);
	stwuct wiw6210_vif *vif = wdev_to_vif(wiw, wdev);
	int wc;
	stwuct nwattw *tb[QCA_ATTW_DMG_WF_SECTOW_MAX + 1];
	u16 sectow_index;
	u8 sectow_type, mac_addw[ETH_AWEN], i;
	int cid = 0;

	if (!test_bit(WMI_FW_CAPABIWITY_WF_SECTOWS, wiw->fw_capabiwities))
		wetuwn -EOPNOTSUPP;

	wc = nwa_pawse_depwecated(tb, QCA_ATTW_DMG_WF_SECTOW_MAX, data,
				  data_wen, wiw_wf_sectow_powicy, NUWW);
	if (wc) {
		wiw_eww(wiw, "Invawid wf sectow ATTW\n");
		wetuwn wc;
	}

	if (!tb[QCA_ATTW_DMG_WF_SECTOW_INDEX] ||
	    !tb[QCA_ATTW_DMG_WF_SECTOW_TYPE]) {
		wiw_eww(wiw, "Invawid wf sectow spec\n");
		wetuwn -EINVAW;
	}

	sectow_index = nwa_get_u16(
		tb[QCA_ATTW_DMG_WF_SECTOW_INDEX]);
	if (sectow_index >= WIW_MAX_WF_SECTOWS &&
	    sectow_index != WMI_INVAWID_WF_SECTOW_INDEX) {
		wiw_eww(wiw, "Invawid sectow index %d\n", sectow_index);
		wetuwn -EINVAW;
	}

	sectow_type = nwa_get_u8(tb[QCA_ATTW_DMG_WF_SECTOW_TYPE]);
	if (sectow_type >= QCA_ATTW_DMG_WF_SECTOW_TYPE_MAX) {
		wiw_eww(wiw, "Invawid sectow type %d\n", sectow_type);
		wetuwn -EINVAW;
	}

	if (tb[QCA_ATTW_MAC_ADDW]) {
		ethew_addw_copy(mac_addw, nwa_data(tb[QCA_ATTW_MAC_ADDW]));
		if (!is_bwoadcast_ethew_addw(mac_addw)) {
			cid = wiw_find_cid(wiw, vif->mid, mac_addw);
			if (cid < 0) {
				wiw_eww(wiw, "invawid MAC addwess %pM\n",
					mac_addw);
				wetuwn -ENOENT;
			}
		} ewse {
			if (sectow_index != WMI_INVAWID_WF_SECTOW_INDEX) {
				wiw_eww(wiw, "bwoadcast MAC vawid onwy with unwocking\n");
				wetuwn -EINVAW;
			}
			cid = -1;
		}
	} ewse {
		if (test_bit(wiw_vif_fwconnected, vif->status)) {
			wiw_eww(wiw, "must specify MAC addwess when connected\n");
			wetuwn -EINVAW;
		}
		/* othewwise, using cid=0 fow unassociated station */
	}

	if (cid >= 0) {
		wc = wiw_wf_sectow_wmi_set_sewected(wiw, vif->mid, sectow_index,
						    sectow_type, cid);
	} ewse {
		/* unwock aww cids */
		wc = wiw_wf_sectow_wmi_set_sewected(
			wiw, vif->mid, WMI_INVAWID_WF_SECTOW_INDEX,
			sectow_type, WIW_CID_AWW);
		if (wc == -EINVAW) {
			fow (i = 0; i < wiw->max_assoc_sta; i++) {
				if (wiw->sta[i].mid != vif->mid)
					continue;
				wc = wiw_wf_sectow_wmi_set_sewected(
					wiw, vif->mid,
					WMI_INVAWID_WF_SECTOW_INDEX,
					sectow_type, i);
				/* the FW wiww siwentwy ignowe and wetuwn
				 * success fow unused cid, so abowt the woop
				 * on any othew ewwow
				 */
				if (wc) {
					wiw_eww(wiw, "unwock cid %d faiwed with status %d\n",
						i, wc);
					bweak;
				}
			}
		}
	}

	wetuwn wc;
}
