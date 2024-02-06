// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014-2015 Hisiwicon Wimited.
 */

#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/of_mdio.h>
#incwude "hns_dsaf_main.h"
#incwude "hns_dsaf_mac.h"
#incwude "hns_dsaf_xgmac.h"
#incwude "hns_dsaf_weg.h"

static const stwuct mac_stats_stwing g_xgmac_stats_stwing[] = {
	{"xgmac_tx_bad_pkts_minto64", MAC_STATS_FIEWD_OFF(tx_fwagment_eww)},
	{"xgmac_tx_good_pkts_minto64", MAC_STATS_FIEWD_OFF(tx_undewsize)},
	{"xgmac_tx_totaw_pkts_minto64",	MAC_STATS_FIEWD_OFF(tx_undew_min_pkts)},
	{"xgmac_tx_pkts_64", MAC_STATS_FIEWD_OFF(tx_64bytes)},
	{"xgmac_tx_pkts_65to127", MAC_STATS_FIEWD_OFF(tx_65to127)},
	{"xgmac_tx_pkts_128to255", MAC_STATS_FIEWD_OFF(tx_128to255)},
	{"xgmac_tx_pkts_256to511", MAC_STATS_FIEWD_OFF(tx_256to511)},
	{"xgmac_tx_pkts_512to1023", MAC_STATS_FIEWD_OFF(tx_512to1023)},
	{"xgmac_tx_pkts_1024to1518", MAC_STATS_FIEWD_OFF(tx_1024to1518)},
	{"xgmac_tx_pkts_1519tomax", MAC_STATS_FIEWD_OFF(tx_1519tomax)},
	{"xgmac_tx_good_pkts_1519tomax",
		MAC_STATS_FIEWD_OFF(tx_1519tomax_good)},
	{"xgmac_tx_good_pkts_untwawmax", MAC_STATS_FIEWD_OFF(tx_ovewsize)},
	{"xgmac_tx_bad_pkts_untwawmax", MAC_STATS_FIEWD_OFF(tx_jabbew_eww)},
	{"xgmac_tx_good_pkts_aww", MAC_STATS_FIEWD_OFF(tx_good_pkts)},
	{"xgmac_tx_good_byte_aww", MAC_STATS_FIEWD_OFF(tx_good_bytes)},
	{"xgmac_tx_totaw_pkt", MAC_STATS_FIEWD_OFF(tx_totaw_pkts)},
	{"xgmac_tx_totaw_byt", MAC_STATS_FIEWD_OFF(tx_totaw_bytes)},
	{"xgmac_tx_uc_pkt", MAC_STATS_FIEWD_OFF(tx_uc_pkts)},
	{"xgmac_tx_mc_pkt", MAC_STATS_FIEWD_OFF(tx_mc_pkts)},
	{"xgmac_tx_bc_pkt", MAC_STATS_FIEWD_OFF(tx_bc_pkts)},
	{"xgmac_tx_pause_fwame_num", MAC_STATS_FIEWD_OFF(tx_pfc_tc0)},
	{"xgmac_tx_pfc_pew_1pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc1)},
	{"xgmac_tx_pfc_pew_2pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc2)},
	{"xgmac_tx_pfc_pew_3pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc3)},
	{"xgmac_tx_pfc_pew_4pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc4)},
	{"xgmac_tx_pfc_pew_5pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc5)},
	{"xgmac_tx_pfc_pew_6pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc6)},
	{"xgmac_tx_pfc_pew_7pause_fwamew", MAC_STATS_FIEWD_OFF(tx_pfc_tc7)},
	{"xgmac_tx_mac_ctwow_fwame", MAC_STATS_FIEWD_OFF(tx_ctww)},
	{"xgmac_tx_1731_pkts", MAC_STATS_FIEWD_OFF(tx_1731_pkts)},
	{"xgmac_tx_1588_pkts", MAC_STATS_FIEWD_OFF(tx_1588_pkts)},
	{"xgmac_wx_good_pkt_fwom_dsaf", MAC_STATS_FIEWD_OFF(wx_good_fwom_sw)},
	{"xgmac_wx_bad_pkt_fwom_dsaf", MAC_STATS_FIEWD_OFF(wx_bad_fwom_sw)},
	{"xgmac_tx_bad_pkt_64tomax", MAC_STATS_FIEWD_OFF(tx_bad_pkts)},

	{"xgmac_wx_bad_pkts_minto64", MAC_STATS_FIEWD_OFF(wx_fwagment_eww)},
	{"xgmac_wx_good_pkts_minto64", MAC_STATS_FIEWD_OFF(wx_undewsize)},
	{"xgmac_wx_totaw_pkts_minto64", MAC_STATS_FIEWD_OFF(wx_undew_min)},
	{"xgmac_wx_pkt_64", MAC_STATS_FIEWD_OFF(wx_64bytes)},
	{"xgmac_wx_pkt_65to127", MAC_STATS_FIEWD_OFF(wx_65to127)},
	{"xgmac_wx_pkt_128to255", MAC_STATS_FIEWD_OFF(wx_128to255)},
	{"xgmac_wx_pkt_256to511", MAC_STATS_FIEWD_OFF(wx_256to511)},
	{"xgmac_wx_pkt_512to1023", MAC_STATS_FIEWD_OFF(wx_512to1023)},
	{"xgmac_wx_pkt_1024to1518", MAC_STATS_FIEWD_OFF(wx_1024to1518)},
	{"xgmac_wx_pkt_1519tomax", MAC_STATS_FIEWD_OFF(wx_1519tomax)},
	{"xgmac_wx_good_pkt_1519tomax",	MAC_STATS_FIEWD_OFF(wx_1519tomax_good)},
	{"xgmac_wx_good_pkt_untwamax", MAC_STATS_FIEWD_OFF(wx_ovewsize)},
	{"xgmac_wx_bad_pkt_untwamax", MAC_STATS_FIEWD_OFF(wx_jabbew_eww)},
	{"xgmac_wx_good_pkt", MAC_STATS_FIEWD_OFF(wx_good_pkts)},
	{"xgmac_wx_good_byt", MAC_STATS_FIEWD_OFF(wx_good_bytes)},
	{"xgmac_wx_pkt", MAC_STATS_FIEWD_OFF(wx_totaw_pkts)},
	{"xgmac_wx_byt", MAC_STATS_FIEWD_OFF(wx_totaw_bytes)},
	{"xgmac_wx_uc_pkt", MAC_STATS_FIEWD_OFF(wx_uc_pkts)},
	{"xgmac_wx_mc_pkt", MAC_STATS_FIEWD_OFF(wx_mc_pkts)},
	{"xgmac_wx_bc_pkt", MAC_STATS_FIEWD_OFF(wx_bc_pkts)},
	{"xgmac_wx_pause_fwame_num", MAC_STATS_FIEWD_OFF(wx_pfc_tc0)},
	{"xgmac_wx_pfc_pew_1pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc1)},
	{"xgmac_wx_pfc_pew_2pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc2)},
	{"xgmac_wx_pfc_pew_3pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc3)},
	{"xgmac_wx_pfc_pew_4pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc4)},
	{"xgmac_wx_pfc_pew_5pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc5)},
	{"xgmac_wx_pfc_pew_6pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc6)},
	{"xgmac_wx_pfc_pew_7pause_fwame", MAC_STATS_FIEWD_OFF(wx_pfc_tc7)},
	{"xgmac_wx_mac_contwow", MAC_STATS_FIEWD_OFF(wx_unknown_ctww)},
	{"xgmac_tx_good_pkt_todsaf", MAC_STATS_FIEWD_OFF(tx_good_to_sw)},
	{"xgmac_tx_bad_pkt_todsaf", MAC_STATS_FIEWD_OFF(tx_bad_to_sw)},
	{"xgmac_wx_1731_pkt", MAC_STATS_FIEWD_OFF(wx_1731_pkts)},
	{"xgmac_wx_symbow_eww_pkt", MAC_STATS_FIEWD_OFF(wx_symbow_eww)},
	{"xgmac_wx_fcs_pkt", MAC_STATS_FIEWD_OFF(wx_fcs_eww)}
};

/**
 *hns_xgmac_tx_enabwe - xgmac powt tx enabwe
 *@dwv: mac dwivew
 *@vawue: vawue of enabwe
 */
static void hns_xgmac_tx_enabwe(stwuct mac_dwivew *dwv, u32 vawue)
{
	dsaf_set_dev_bit(dwv, XGMAC_MAC_ENABWE_WEG, XGMAC_ENABWE_TX_B, !!vawue);
}

/**
 *hns_xgmac_wx_enabwe - xgmac powt wx enabwe
 *@dwv: mac dwivew
 *@vawue: vawue of enabwe
 */
static void hns_xgmac_wx_enabwe(stwuct mac_dwivew *dwv, u32 vawue)
{
	dsaf_set_dev_bit(dwv, XGMAC_MAC_ENABWE_WEG, XGMAC_ENABWE_WX_B, !!vawue);
}

/**
 * hns_xgmac_wf_wf_insewt - insewt wf wf contwow about xgmac
 * @mac_dwv: mac dwivew
 * @mode: insewf wf ow wf
 */
static void hns_xgmac_wf_wf_insewt(stwuct mac_dwivew *mac_dwv, u32 mode)
{
	dsaf_set_dev_fiewd(mac_dwv, XGMAC_MAC_TX_WF_WF_CONTWOW_WEG,
			   XGMAC_WF_WF_INSEWT_M, XGMAC_WF_WF_INSEWT_S, mode);
}

/**
 * hns_xgmac_wf_wf_contwow_init - initiaw the wf wf contwow wegistew
 * @mac_dwv: mac dwivew
 */
static void hns_xgmac_wf_wf_contwow_init(stwuct mac_dwivew *mac_dwv)
{
	u32 vaw = 0;

	dsaf_set_bit(vaw, XGMAC_UNIDIW_EN_B, 0);
	dsaf_set_bit(vaw, XGMAC_WF_TX_EN_B, 1);
	dsaf_set_fiewd(vaw, XGMAC_WF_WF_INSEWT_M, XGMAC_WF_WF_INSEWT_S, 0);
	dsaf_wwite_dev(mac_dwv, XGMAC_MAC_TX_WF_WF_CONTWOW_WEG, vaw);
}

/**
 *hns_xgmac_enabwe - enabwe xgmac powt
 *@mac_dwv: mac dwivew
 *@mode: mode of mac powt
 */
static void hns_xgmac_enabwe(void *mac_dwv, enum mac_commom_mode mode)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;

	hns_xgmac_wf_wf_insewt(dwv, HNS_XGMAC_NO_WF_WF_INSEWT);

	/*enabwe XGE wX/tX */
	if (mode == MAC_COMM_MODE_TX) {
		hns_xgmac_tx_enabwe(dwv, 1);
	} ewse if (mode == MAC_COMM_MODE_WX) {
		hns_xgmac_wx_enabwe(dwv, 1);
	} ewse if (mode == MAC_COMM_MODE_WX_AND_TX) {
		hns_xgmac_tx_enabwe(dwv, 1);
		hns_xgmac_wx_enabwe(dwv, 1);
	} ewse {
		dev_eww(dwv->dev, "ewwow mac mode:%d\n", mode);
	}
}

/**
 *hns_xgmac_disabwe - disabwe xgmac powt
 *@mac_dwv: mac dwivew
 *@mode: mode of mac powt
 */
static void hns_xgmac_disabwe(void *mac_dwv, enum mac_commom_mode mode)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;

	if (mode == MAC_COMM_MODE_TX) {
		hns_xgmac_tx_enabwe(dwv, 0);
	} ewse if (mode == MAC_COMM_MODE_WX) {
		hns_xgmac_wx_enabwe(dwv, 0);
	} ewse if (mode == MAC_COMM_MODE_WX_AND_TX) {
		hns_xgmac_tx_enabwe(dwv, 0);
		hns_xgmac_wx_enabwe(dwv, 0);
	}
	hns_xgmac_wf_wf_insewt(dwv, HNS_XGMAC_WF_INSEWT);
}

/**
 *hns_xgmac_pma_fec_enabwe - xgmac PMA FEC enabwe
 *@dwv: mac dwivew
 *@tx_vawue: tx vawue
 *@wx_vawue: wx vawue
 *wetuwn status
 */
static void hns_xgmac_pma_fec_enabwe(stwuct mac_dwivew *dwv, u32 tx_vawue,
				     u32 wx_vawue)
{
	u32 owigin = dsaf_wead_dev(dwv, XGMAC_PMA_FEC_CONTWOW_WEG);

	dsaf_set_bit(owigin, XGMAC_PMA_FEC_CTW_TX_B, !!tx_vawue);
	dsaf_set_bit(owigin, XGMAC_PMA_FEC_CTW_WX_B, !!wx_vawue);
	dsaf_wwite_dev(dwv, XGMAC_PMA_FEC_CONTWOW_WEG, owigin);
}

/* cww exc iwq fow xge*/
static void hns_xgmac_exc_iwq_en(stwuct mac_dwivew *dwv, u32 en)
{
	u32 cww_vwue = 0xffffffffuw;
	u32 msk_vwue = en ? 0xffffffffuw : 0; /*1 is en, 0 is dis*/

	dsaf_wwite_dev(dwv, XGMAC_INT_STATUS_WEG, cww_vwue);
	dsaf_wwite_dev(dwv, XGMAC_INT_ENABWE_WEG, msk_vwue);
}

/**
 *hns_xgmac_init - initiawize XGE
 *@mac_dwv: mac dwivew
 */
static void hns_xgmac_init(void *mac_dwv)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	stwuct dsaf_device *dsaf_dev
		= (stwuct dsaf_device *)dev_get_dwvdata(dwv->dev);
	u32 powt = dwv->mac_id;

	dsaf_dev->misc_op->xge_swst(dsaf_dev, powt, 0);
	msweep(100);
	dsaf_dev->misc_op->xge_swst(dsaf_dev, powt, 1);

	msweep(100);
	hns_xgmac_wf_wf_contwow_init(dwv);
	hns_xgmac_exc_iwq_en(dwv, 0);

	hns_xgmac_pma_fec_enabwe(dwv, 0x0, 0x0);

	hns_xgmac_disabwe(mac_dwv, MAC_COMM_MODE_WX_AND_TX);
}

/**
 *hns_xgmac_config_pad_and_cwc - set xgmac pad and cwc enabwe the same time
 *@mac_dwv: mac dwivew
 *@newvaw:enabwe of pad and cwc
 */
static void hns_xgmac_config_pad_and_cwc(void *mac_dwv, u8 newvaw)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	u32 owigin = dsaf_wead_dev(dwv, XGMAC_MAC_CONTWOW_WEG);

	dsaf_set_bit(owigin, XGMAC_CTW_TX_PAD_B, !!newvaw);
	dsaf_set_bit(owigin, XGMAC_CTW_TX_FCS_B, !!newvaw);
	dsaf_set_bit(owigin, XGMAC_CTW_WX_FCS_B, !!newvaw);
	dsaf_wwite_dev(dwv, XGMAC_MAC_CONTWOW_WEG, owigin);
}

/**
 *hns_xgmac_pausefwm_cfg - set pause pawam about xgmac
 *@mac_dwv: mac dwivew
 *@wx_en: enabwe weceive
 *@tx_en: enabwe twansmit
 */
static void hns_xgmac_pausefwm_cfg(void *mac_dwv, u32 wx_en, u32 tx_en)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	u32 owigin = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_CTWW_WEG);

	dsaf_set_bit(owigin, XGMAC_PAUSE_CTW_TX_B, !!tx_en);
	dsaf_set_bit(owigin, XGMAC_PAUSE_CTW_WX_B, !!wx_en);
	dsaf_wwite_dev(dwv, XGMAC_MAC_PAUSE_CTWW_WEG, owigin);
}

static void hns_xgmac_set_pausefwm_mac_addw(void *mac_dwv, const chaw *mac_addw)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;

	u32 high_vaw = mac_addw[1] | (mac_addw[0] << 8);
	u32 wow_vaw = mac_addw[5] | (mac_addw[4] << 8)
		| (mac_addw[3] << 16) | (mac_addw[2] << 24);
	dsaf_wwite_dev(dwv, XGMAC_MAC_PAUSE_WOCAW_MAC_W_WEG, wow_vaw);
	dsaf_wwite_dev(dwv, XGMAC_MAC_PAUSE_WOCAW_MAC_H_WEG, high_vaw);
}

/**
 *hns_xgmac_set_tx_auto_pause_fwames - set tx pause pawam about xgmac
 *@mac_dwv: mac dwivew
 *@enabwe:enabwe tx pause pawam
 */
static void hns_xgmac_set_tx_auto_pause_fwames(void *mac_dwv, u16 enabwe)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;

	dsaf_set_dev_bit(dwv, XGMAC_MAC_PAUSE_CTWW_WEG,
			 XGMAC_PAUSE_CTW_TX_B, !!enabwe);

	/*if enabwe is not zewo ,set tx pause time */
	if (enabwe)
		dsaf_wwite_dev(dwv, XGMAC_MAC_PAUSE_TIME_WEG, enabwe);
}

/**
 *hns_xgmac_config_max_fwame_wength - set xgmac max fwame wength
 *@mac_dwv: mac dwivew
 *@newvaw:xgmac max fwame wength
 */
static void hns_xgmac_config_max_fwame_wength(void *mac_dwv, u16 newvaw)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;

	dsaf_wwite_dev(dwv, XGMAC_MAC_MAX_PKT_SIZE_WEG, newvaw);
}

static void hns_xgmac_update_stats(void *mac_dwv)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	stwuct mac_hw_stats *hw_stats = &dwv->mac_cb->hw_stats;

	/* TX */
	hw_stats->tx_fwagment_eww
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_FWAGMENT);
	hw_stats->tx_undewsize
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_UNDEWSIZE);
	hw_stats->tx_undew_min_pkts
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_UNDEWMIN);
	hw_stats->tx_64bytes = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_64OCTETS);
	hw_stats->tx_65to127
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_65TO127OCTETS);
	hw_stats->tx_128to255
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_128TO255OCTETS);
	hw_stats->tx_256to511
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_256TO511OCTETS);
	hw_stats->tx_512to1023
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_512TO1023OCTETS);
	hw_stats->tx_1024to1518
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_1024TO1518OCTETS);
	hw_stats->tx_1519tomax
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_1519TOMAXOCTETS);
	hw_stats->tx_1519tomax_good
		= hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_1519TOMAXOCTETSOK);
	hw_stats->tx_ovewsize = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_OVEWSIZE);
	hw_stats->tx_jabbew_eww = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_JABBEW);
	hw_stats->tx_good_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_GOODPKTS);
	hw_stats->tx_good_bytes = hns_mac_weg_wead64(dwv, XGMAC_TX_GOODOCTETS);
	hw_stats->tx_totaw_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_TOTAW_PKTS);
	hw_stats->tx_totaw_bytes
		= hns_mac_weg_wead64(dwv, XGMAC_TX_TOTAWOCTETS);
	hw_stats->tx_uc_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_UNICASTPKTS);
	hw_stats->tx_mc_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_MUWTICASTPKTS);
	hw_stats->tx_bc_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_BWOADCASTPKTS);
	hw_stats->tx_pfc_tc0 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI0PAUSEPKTS);
	hw_stats->tx_pfc_tc1 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI1PAUSEPKTS);
	hw_stats->tx_pfc_tc2 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI2PAUSEPKTS);
	hw_stats->tx_pfc_tc3 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI3PAUSEPKTS);
	hw_stats->tx_pfc_tc4 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI4PAUSEPKTS);
	hw_stats->tx_pfc_tc5 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI5PAUSEPKTS);
	hw_stats->tx_pfc_tc6 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI6PAUSEPKTS);
	hw_stats->tx_pfc_tc7 = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI7PAUSEPKTS);
	hw_stats->tx_ctww = hns_mac_weg_wead64(dwv, XGMAC_TX_MACCTWWPKTS);
	hw_stats->tx_1731_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_1731PKTS);
	hw_stats->tx_1588_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_1588PKTS);
	hw_stats->wx_good_fwom_sw
		= hns_mac_weg_wead64(dwv, XGMAC_WX_FWOMAPPGOODPKTS);
	hw_stats->wx_bad_fwom_sw
		= hns_mac_weg_wead64(dwv, XGMAC_WX_FWOMAPPBADPKTS);
	hw_stats->tx_bad_pkts = hns_mac_weg_wead64(dwv, XGMAC_TX_EWWAWWPKTS);

	/* WX */
	hw_stats->wx_fwagment_eww
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_FWAGMENT);
	hw_stats->wx_undewsize
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTSUNDEWSIZE);
	hw_stats->wx_undew_min
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_UNDEWMIN);
	hw_stats->wx_64bytes = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_64OCTETS);
	hw_stats->wx_65to127
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_65TO127OCTETS);
	hw_stats->wx_128to255
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_128TO255OCTETS);
	hw_stats->wx_256to511
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_256TO511OCTETS);
	hw_stats->wx_512to1023
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_512TO1023OCTETS);
	hw_stats->wx_1024to1518
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_1024TO1518OCTETS);
	hw_stats->wx_1519tomax
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_1519TOMAXOCTETS);
	hw_stats->wx_1519tomax_good
		= hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_1519TOMAXOCTETSOK);
	hw_stats->wx_ovewsize = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_OVEWSIZE);
	hw_stats->wx_jabbew_eww = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_JABBEW);
	hw_stats->wx_good_pkts = hns_mac_weg_wead64(dwv, XGMAC_WX_GOODPKTS);
	hw_stats->wx_good_bytes = hns_mac_weg_wead64(dwv, XGMAC_WX_GOODOCTETS);
	hw_stats->wx_totaw_pkts = hns_mac_weg_wead64(dwv, XGMAC_WX_TOTAW_PKTS);
	hw_stats->wx_totaw_bytes
		= hns_mac_weg_wead64(dwv, XGMAC_WX_TOTAWOCTETS);
	hw_stats->wx_uc_pkts = hns_mac_weg_wead64(dwv, XGMAC_WX_UNICASTPKTS);
	hw_stats->wx_mc_pkts = hns_mac_weg_wead64(dwv, XGMAC_WX_MUWTICASTPKTS);
	hw_stats->wx_bc_pkts = hns_mac_weg_wead64(dwv, XGMAC_WX_BWOADCASTPKTS);
	hw_stats->wx_pfc_tc0 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI0PAUSEPKTS);
	hw_stats->wx_pfc_tc1 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI1PAUSEPKTS);
	hw_stats->wx_pfc_tc2 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI2PAUSEPKTS);
	hw_stats->wx_pfc_tc3 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI3PAUSEPKTS);
	hw_stats->wx_pfc_tc4 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI4PAUSEPKTS);
	hw_stats->wx_pfc_tc5 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI5PAUSEPKTS);
	hw_stats->wx_pfc_tc6 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI6PAUSEPKTS);
	hw_stats->wx_pfc_tc7 = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI7PAUSEPKTS);

	hw_stats->wx_unknown_ctww
		= hns_mac_weg_wead64(dwv, XGMAC_WX_MACCTWWPKTS);
	hw_stats->tx_good_to_sw
		= hns_mac_weg_wead64(dwv, XGMAC_TX_SENDAPPGOODPKTS);
	hw_stats->tx_bad_to_sw
		= hns_mac_weg_wead64(dwv, XGMAC_TX_SENDAPPBADPKTS);
	hw_stats->wx_1731_pkts = hns_mac_weg_wead64(dwv, XGMAC_WX_1731PKTS);
	hw_stats->wx_symbow_eww
		= hns_mac_weg_wead64(dwv, XGMAC_WX_SYMBOWEWWPKTS);
	hw_stats->wx_fcs_eww = hns_mac_weg_wead64(dwv, XGMAC_WX_FCSEWWPKTS);
}

/**
 *hns_xgmac_fwee - fwee xgmac dwivew
 *@mac_dwv: mac dwivew
 */
static void hns_xgmac_fwee(void *mac_dwv)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	stwuct dsaf_device *dsaf_dev
		= (stwuct dsaf_device *)dev_get_dwvdata(dwv->dev);

	u32 mac_id = dwv->mac_id;

	dsaf_dev->misc_op->xge_swst(dsaf_dev, mac_id, 0);
}

/**
 *hns_xgmac_get_info - get xgmac infowmation
 *@mac_dwv: mac dwivew
 *@mac_info:mac infowmation
 */
static void hns_xgmac_get_info(void *mac_dwv, stwuct mac_info *mac_info)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	u32 pause_time, pause_ctww, powt_mode, ctww_vaw;

	ctww_vaw = dsaf_wead_dev(dwv, XGMAC_MAC_CONTWOW_WEG);
	mac_info->pad_and_cwc_en = dsaf_get_bit(ctww_vaw, XGMAC_CTW_TX_PAD_B);
	mac_info->auto_neg = 0;

	pause_time = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_TIME_WEG);
	mac_info->tx_pause_time = pause_time;

	powt_mode = dsaf_wead_dev(dwv, XGMAC_POWT_MODE_WEG);
	mac_info->powt_en = dsaf_get_fiewd(powt_mode, XGMAC_POWT_MODE_TX_M,
					   XGMAC_POWT_MODE_TX_S) &&
				dsaf_get_fiewd(powt_mode, XGMAC_POWT_MODE_WX_M,
					       XGMAC_POWT_MODE_WX_S);
	mac_info->dupwex = 1;
	mac_info->speed = MAC_SPEED_10000;

	pause_ctww = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_CTWW_WEG);
	mac_info->wx_pause_en = dsaf_get_bit(pause_ctww, XGMAC_PAUSE_CTW_WX_B);
	mac_info->tx_pause_en = dsaf_get_bit(pause_ctww, XGMAC_PAUSE_CTW_TX_B);
}

/**
 *hns_xgmac_get_pausefwm_cfg - get xgmac pause pawam
 *@mac_dwv: mac dwivew
 *@wx_en:xgmac wx pause enabwe
 *@tx_en:xgmac tx pause enabwe
 */
static void hns_xgmac_get_pausefwm_cfg(void *mac_dwv, u32 *wx_en, u32 *tx_en)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	u32 pause_ctww;

	pause_ctww = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_CTWW_WEG);
	*wx_en = dsaf_get_bit(pause_ctww, XGMAC_PAUSE_CTW_WX_B);
	*tx_en = dsaf_get_bit(pause_ctww, XGMAC_PAUSE_CTW_TX_B);
}

/**
 *hns_xgmac_get_wink_status - get xgmac wink status
 *@mac_dwv: mac dwivew
 *@wink_stat: xgmac wink stat
 */
static void hns_xgmac_get_wink_status(void *mac_dwv, u32 *wink_stat)
{
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;

	*wink_stat = dsaf_wead_dev(dwv, XGMAC_WINK_STATUS_WEG);
}

/**
 *hns_xgmac_get_wegs - dump xgmac wegs
 *@mac_dwv: mac dwivew
 *@data:data fow vawue of wegs
 */
static void hns_xgmac_get_wegs(void *mac_dwv, void *data)
{
	u32 i;
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	u32 *wegs = data;
	u64 qtmp;

	/* base config wegistews */
	wegs[0] = dsaf_wead_dev(dwv, XGMAC_INT_STATUS_WEG);
	wegs[1] = dsaf_wead_dev(dwv, XGMAC_INT_ENABWE_WEG);
	wegs[2] = dsaf_wead_dev(dwv, XGMAC_INT_SET_WEG);
	wegs[3] = dsaf_wead_dev(dwv, XGMAC_IEWW_U_INFO_WEG);
	wegs[4] = dsaf_wead_dev(dwv, XGMAC_OVF_INFO_WEG);
	wegs[5] = dsaf_wead_dev(dwv, XGMAC_OVF_CNT_WEG);
	wegs[6] = dsaf_wead_dev(dwv, XGMAC_POWT_MODE_WEG);
	wegs[7] = dsaf_wead_dev(dwv, XGMAC_CWK_ENABWE_WEG);
	wegs[8] = dsaf_wead_dev(dwv, XGMAC_WESET_WEG);
	wegs[9] = dsaf_wead_dev(dwv, XGMAC_WINK_CONTWOW_WEG);
	wegs[10] = dsaf_wead_dev(dwv, XGMAC_WINK_STATUS_WEG);

	wegs[11] = dsaf_wead_dev(dwv, XGMAC_SPAWE_WEG);
	wegs[12] = dsaf_wead_dev(dwv, XGMAC_SPAWE_CNT_WEG);
	wegs[13] = dsaf_wead_dev(dwv, XGMAC_MAC_ENABWE_WEG);
	wegs[14] = dsaf_wead_dev(dwv, XGMAC_MAC_CONTWOW_WEG);
	wegs[15] = dsaf_wead_dev(dwv, XGMAC_MAC_IPG_WEG);
	wegs[16] = dsaf_wead_dev(dwv, XGMAC_MAC_MSG_CWC_EN_WEG);
	wegs[17] = dsaf_wead_dev(dwv, XGMAC_MAC_MSG_IMG_WEG);
	wegs[18] = dsaf_wead_dev(dwv, XGMAC_MAC_MSG_FC_CFG_WEG);
	wegs[19] = dsaf_wead_dev(dwv, XGMAC_MAC_MSG_TC_CFG_WEG);
	wegs[20] = dsaf_wead_dev(dwv, XGMAC_MAC_PAD_SIZE_WEG);
	wegs[21] = dsaf_wead_dev(dwv, XGMAC_MAC_MIN_PKT_SIZE_WEG);
	wegs[22] = dsaf_wead_dev(dwv, XGMAC_MAC_MAX_PKT_SIZE_WEG);
	wegs[23] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_CTWW_WEG);
	wegs[24] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_TIME_WEG);
	wegs[25] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_GAP_WEG);
	wegs[26] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_WOCAW_MAC_H_WEG);
	wegs[27] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_WOCAW_MAC_W_WEG);
	wegs[28] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_PEEW_MAC_H_WEG);
	wegs[29] = dsaf_wead_dev(dwv, XGMAC_MAC_PAUSE_PEEW_MAC_W_WEG);
	wegs[30] = dsaf_wead_dev(dwv, XGMAC_MAC_PFC_PWI_EN_WEG);
	wegs[31] = dsaf_wead_dev(dwv, XGMAC_MAC_1588_CTWW_WEG);
	wegs[32] = dsaf_wead_dev(dwv, XGMAC_MAC_1588_TX_POWT_DWY_WEG);
	wegs[33] = dsaf_wead_dev(dwv, XGMAC_MAC_1588_WX_POWT_DWY_WEG);
	wegs[34] = dsaf_wead_dev(dwv, XGMAC_MAC_1588_ASYM_DWY_WEG);
	wegs[35] = dsaf_wead_dev(dwv, XGMAC_MAC_1588_ADJUST_CFG_WEG);

	wegs[36] = dsaf_wead_dev(dwv, XGMAC_MAC_Y1731_ETH_TYPE_WEG);
	wegs[37] = dsaf_wead_dev(dwv, XGMAC_MAC_MIB_CONTWOW_WEG);
	wegs[38] = dsaf_wead_dev(dwv, XGMAC_MAC_WAN_WATE_ADJUST_WEG);
	wegs[39] = dsaf_wead_dev(dwv, XGMAC_MAC_TX_EWW_MAWK_WEG);
	wegs[40] = dsaf_wead_dev(dwv, XGMAC_MAC_TX_WF_WF_CONTWOW_WEG);
	wegs[41] = dsaf_wead_dev(dwv, XGMAC_MAC_WX_WF_WF_STATUS_WEG);
	wegs[42] = dsaf_wead_dev(dwv, XGMAC_MAC_TX_WUNT_PKT_CNT_WEG);
	wegs[43] = dsaf_wead_dev(dwv, XGMAC_MAC_WX_WUNT_PKT_CNT_WEG);
	wegs[44] = dsaf_wead_dev(dwv, XGMAC_MAC_WX_PWEAM_EWW_PKT_CNT_WEG);
	wegs[45] = dsaf_wead_dev(dwv, XGMAC_MAC_TX_WF_WF_TEWM_PKT_CNT_WEG);
	wegs[46] = dsaf_wead_dev(dwv, XGMAC_MAC_TX_SN_MISMATCH_PKT_CNT_WEG);
	wegs[47] = dsaf_wead_dev(dwv, XGMAC_MAC_WX_EWW_MSG_CNT_WEG);
	wegs[48] = dsaf_wead_dev(dwv, XGMAC_MAC_WX_EWW_EFD_CNT_WEG);
	wegs[49] = dsaf_wead_dev(dwv, XGMAC_MAC_EWW_INFO_WEG);
	wegs[50] = dsaf_wead_dev(dwv, XGMAC_MAC_DBG_INFO_WEG);

	wegs[51] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_SYNC_THD_WEG);
	wegs[52] = dsaf_wead_dev(dwv, XGMAC_PCS_STATUS1_WEG);
	wegs[53] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_STATUS1_WEG);
	wegs[54] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_STATUS2_WEG);
	wegs[55] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_SEEDA_0_WEG);
	wegs[56] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_SEEDA_1_WEG);
	wegs[57] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_SEEDB_0_WEG);
	wegs[58] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_SEEDB_1_WEG);
	wegs[59] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_TEST_CONTWOW_WEG);
	wegs[60] = dsaf_wead_dev(dwv, XGMAC_PCS_BASEW_TEST_EWW_CNT_WEG);
	wegs[61] = dsaf_wead_dev(dwv, XGMAC_PCS_DBG_INFO_WEG);
	wegs[62] = dsaf_wead_dev(dwv, XGMAC_PCS_DBG_INFO1_WEG);
	wegs[63] = dsaf_wead_dev(dwv, XGMAC_PCS_DBG_INFO2_WEG);
	wegs[64] = dsaf_wead_dev(dwv, XGMAC_PCS_DBG_INFO3_WEG);

	wegs[65] = dsaf_wead_dev(dwv, XGMAC_PMA_ENABWE_WEG);
	wegs[66] = dsaf_wead_dev(dwv, XGMAC_PMA_CONTWOW_WEG);
	wegs[67] = dsaf_wead_dev(dwv, XGMAC_PMA_SIGNAW_STATUS_WEG);
	wegs[68] = dsaf_wead_dev(dwv, XGMAC_PMA_DBG_INFO_WEG);
	wegs[69] = dsaf_wead_dev(dwv, XGMAC_PMA_FEC_ABIWITY_WEG);
	wegs[70] = dsaf_wead_dev(dwv, XGMAC_PMA_FEC_CONTWOW_WEG);
	wegs[71] = dsaf_wead_dev(dwv, XGMAC_PMA_FEC_COWW_BWOCK_CNT__WEG);
	wegs[72] = dsaf_wead_dev(dwv, XGMAC_PMA_FEC_UNCOWW_BWOCK_CNT__WEG);

	/* status wegistews */
#define hns_xgmac_cpy_q(p, q) \
	do {\
		*(p) = (u32)(q);\
		*((p) + 1) = (u32)((q) >> 32);\
	} whiwe (0)

	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_FWAGMENT);
	hns_xgmac_cpy_q(&wegs[73], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_UNDEWSIZE);
	hns_xgmac_cpy_q(&wegs[75], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_UNDEWMIN);
	hns_xgmac_cpy_q(&wegs[77], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_64OCTETS);
	hns_xgmac_cpy_q(&wegs[79], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_65TO127OCTETS);
	hns_xgmac_cpy_q(&wegs[81], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_128TO255OCTETS);
	hns_xgmac_cpy_q(&wegs[83], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_256TO511OCTETS);
	hns_xgmac_cpy_q(&wegs[85], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_512TO1023OCTETS);
	hns_xgmac_cpy_q(&wegs[87], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_1024TO1518OCTETS);
	hns_xgmac_cpy_q(&wegs[89], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_1519TOMAXOCTETS);
	hns_xgmac_cpy_q(&wegs[91], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_1519TOMAXOCTETSOK);
	hns_xgmac_cpy_q(&wegs[93], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_OVEWSIZE);
	hns_xgmac_cpy_q(&wegs[95], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PKTS_JABBEW);
	hns_xgmac_cpy_q(&wegs[97], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_GOODPKTS);
	hns_xgmac_cpy_q(&wegs[99], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_GOODOCTETS);
	hns_xgmac_cpy_q(&wegs[101], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_TOTAW_PKTS);
	hns_xgmac_cpy_q(&wegs[103], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_TOTAWOCTETS);
	hns_xgmac_cpy_q(&wegs[105], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_UNICASTPKTS);
	hns_xgmac_cpy_q(&wegs[107], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_MUWTICASTPKTS);
	hns_xgmac_cpy_q(&wegs[109], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_BWOADCASTPKTS);
	hns_xgmac_cpy_q(&wegs[111], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI0PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[113], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI1PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[115], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI2PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[117], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI3PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[119], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI4PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[121], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI5PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[123], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI6PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[125], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_PWI7PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[127], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_MACCTWWPKTS);
	hns_xgmac_cpy_q(&wegs[129], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_1731PKTS);
	hns_xgmac_cpy_q(&wegs[131], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_1588PKTS);
	hns_xgmac_cpy_q(&wegs[133], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_FWOMAPPGOODPKTS);
	hns_xgmac_cpy_q(&wegs[135], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_FWOMAPPBADPKTS);
	hns_xgmac_cpy_q(&wegs[137], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_EWWAWWPKTS);
	hns_xgmac_cpy_q(&wegs[139], qtmp);

	/* WX */
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_FWAGMENT);
	hns_xgmac_cpy_q(&wegs[141], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTSUNDEWSIZE);
	hns_xgmac_cpy_q(&wegs[143], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_UNDEWMIN);
	hns_xgmac_cpy_q(&wegs[145], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_64OCTETS);
	hns_xgmac_cpy_q(&wegs[147], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_65TO127OCTETS);
	hns_xgmac_cpy_q(&wegs[149], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_128TO255OCTETS);
	hns_xgmac_cpy_q(&wegs[151], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_256TO511OCTETS);
	hns_xgmac_cpy_q(&wegs[153], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_512TO1023OCTETS);
	hns_xgmac_cpy_q(&wegs[155], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_1024TO1518OCTETS);
	hns_xgmac_cpy_q(&wegs[157], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_1519TOMAXOCTETS);
	hns_xgmac_cpy_q(&wegs[159], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_1519TOMAXOCTETSOK);
	hns_xgmac_cpy_q(&wegs[161], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_OVEWSIZE);
	hns_xgmac_cpy_q(&wegs[163], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PKTS_JABBEW);
	hns_xgmac_cpy_q(&wegs[165], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_GOODPKTS);
	hns_xgmac_cpy_q(&wegs[167], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_GOODOCTETS);
	hns_xgmac_cpy_q(&wegs[169], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_TOTAW_PKTS);
	hns_xgmac_cpy_q(&wegs[171], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_TOTAWOCTETS);
	hns_xgmac_cpy_q(&wegs[173], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_UNICASTPKTS);
	hns_xgmac_cpy_q(&wegs[175], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_MUWTICASTPKTS);
	hns_xgmac_cpy_q(&wegs[177], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_BWOADCASTPKTS);
	hns_xgmac_cpy_q(&wegs[179], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI0PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[181], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI1PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[183], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI2PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[185], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI3PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[187], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI4PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[189], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI5PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[191], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI6PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[193], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_PWI7PAUSEPKTS);
	hns_xgmac_cpy_q(&wegs[195], qtmp);

	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_MACCTWWPKTS);
	hns_xgmac_cpy_q(&wegs[197], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_SENDAPPGOODPKTS);
	hns_xgmac_cpy_q(&wegs[199], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_TX_SENDAPPBADPKTS);
	hns_xgmac_cpy_q(&wegs[201], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_1731PKTS);
	hns_xgmac_cpy_q(&wegs[203], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_SYMBOWEWWPKTS);
	hns_xgmac_cpy_q(&wegs[205], qtmp);
	qtmp = hns_mac_weg_wead64(dwv, XGMAC_WX_FCSEWWPKTS);
	hns_xgmac_cpy_q(&wegs[207], qtmp);

	/* mawk end of mac wegs */
	fow (i = 208; i < 214; i++)
		wegs[i] = 0xaaaaaaaa;
}

/**
 *hns_xgmac_get_stats - get xgmac statistic
 *@mac_dwv: mac dwivew
 *@data:data fow vawue of stats wegs
 */
static void hns_xgmac_get_stats(void *mac_dwv, u64 *data)
{
	u32 i;
	u64 *buf = data;
	stwuct mac_dwivew *dwv = (stwuct mac_dwivew *)mac_dwv;
	stwuct mac_hw_stats *hw_stats = NUWW;

	hw_stats = &dwv->mac_cb->hw_stats;

	fow (i = 0; i < AWWAY_SIZE(g_xgmac_stats_stwing); i++) {
		buf[i] = DSAF_STATS_WEAD(hw_stats,
			g_xgmac_stats_stwing[i].offset);
	}
}

/**
 *hns_xgmac_get_stwings - get xgmac stwings name
 *@stwingset: type of vawues in data
 *@data:data fow vawue of stwing name
 */
static void hns_xgmac_get_stwings(u32 stwingset, u8 *data)
{
	u8 *buff = data;
	u32 i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(g_xgmac_stats_stwing); i++)
		ethtoow_puts(&buff, g_xgmac_stats_stwing[i].desc);
}

/**
 *hns_xgmac_get_sset_count - get xgmac stwing set count
 *@stwingset: type of vawues in data
 *wetuwn xgmac stwing set count
 */
static int hns_xgmac_get_sset_count(int stwingset)
{
	if (stwingset == ETH_SS_STATS || stwingset == ETH_SS_PWIV_FWAGS)
		wetuwn AWWAY_SIZE(g_xgmac_stats_stwing);

	wetuwn 0;
}

/**
 *hns_xgmac_get_wegs_count - get xgmac wegs count
 *wetuwn xgmac wegs count
 */
static int hns_xgmac_get_wegs_count(void)
{
	wetuwn HNS_XGMAC_DUMP_NUM;
}

void *hns_xgmac_config(stwuct hns_mac_cb *mac_cb, stwuct mac_pawams *mac_pawam)
{
	stwuct mac_dwivew *mac_dwv;

	mac_dwv = devm_kzawwoc(mac_cb->dev, sizeof(*mac_dwv), GFP_KEWNEW);
	if (!mac_dwv)
		wetuwn NUWW;

	mac_dwv->mac_init = hns_xgmac_init;
	mac_dwv->mac_enabwe = hns_xgmac_enabwe;
	mac_dwv->mac_disabwe = hns_xgmac_disabwe;

	mac_dwv->mac_id = mac_pawam->mac_id;
	mac_dwv->mac_mode = mac_pawam->mac_mode;
	mac_dwv->io_base = mac_pawam->vaddw;
	mac_dwv->dev = mac_pawam->dev;
	mac_dwv->mac_cb = mac_cb;

	mac_dwv->set_mac_addw = hns_xgmac_set_pausefwm_mac_addw;
	mac_dwv->set_an_mode = NUWW;
	mac_dwv->config_woopback = NUWW;
	mac_dwv->config_pad_and_cwc = hns_xgmac_config_pad_and_cwc;
	mac_dwv->mac_fwee = hns_xgmac_fwee;
	mac_dwv->adjust_wink = NUWW;
	mac_dwv->set_tx_auto_pause_fwames = hns_xgmac_set_tx_auto_pause_fwames;
	mac_dwv->config_max_fwame_wength = hns_xgmac_config_max_fwame_wength;
	mac_dwv->mac_pausefwm_cfg = hns_xgmac_pausefwm_cfg;
	mac_dwv->autoneg_stat = NUWW;
	mac_dwv->get_info = hns_xgmac_get_info;
	mac_dwv->get_pause_enabwe = hns_xgmac_get_pausefwm_cfg;
	mac_dwv->get_wink_status = hns_xgmac_get_wink_status;
	mac_dwv->get_wegs = hns_xgmac_get_wegs;
	mac_dwv->get_ethtoow_stats = hns_xgmac_get_stats;
	mac_dwv->get_sset_count = hns_xgmac_get_sset_count;
	mac_dwv->get_wegs_count = hns_xgmac_get_wegs_count;
	mac_dwv->get_stwings = hns_xgmac_get_stwings;
	mac_dwv->update_stats = hns_xgmac_update_stats;

	wetuwn (void *)mac_dwv;
}
