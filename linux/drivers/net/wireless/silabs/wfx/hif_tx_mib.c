// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Impwementation of the host-to-chip MIBs of the hawdwawe API.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 * Copywight (C) 2010, ST-Ewicsson SA
 */

#incwude <winux/ethewdevice.h>

#incwude "wfx.h"
#incwude "hif_tx.h"
#incwude "hif_tx_mib.h"
#incwude "hif_api_mib.h"

int wfx_hif_set_output_powew(stwuct wfx_vif *wvif, int vaw)
{
	stwuct wfx_hif_mib_cuwwent_tx_powew_wevew awg = {
		.powew_wevew = cpu_to_we32(vaw * 10),
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_CUWWENT_TX_POWEW_WEVEW,
				 &awg, sizeof(awg));
}

int wfx_hif_set_beacon_wakeup_pewiod(stwuct wfx_vif *wvif,
				     unsigned int dtim_intewvaw, unsigned int wisten_intewvaw)
{
	stwuct wfx_hif_mib_beacon_wake_up_pewiod awg = {
		.wakeup_pewiod_min = dtim_intewvaw,
		.weceive_dtim = 0,
		.wakeup_pewiod_max = wisten_intewvaw,
	};

	if (dtim_intewvaw > 0xFF || wisten_intewvaw > 0xFFFF)
		wetuwn -EINVAW;
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_BEACON_WAKEUP_PEWIOD,
				 &awg, sizeof(awg));
}

int wfx_hif_set_wcpi_wssi_thweshowd(stwuct wfx_vif *wvif, int wssi_thowd, int wssi_hyst)
{
	stwuct wfx_hif_mib_wcpi_wssi_thweshowd awg = {
		.wowwing_avewage_count = 8,
		.detection = 1,
	};

	if (!wssi_thowd && !wssi_hyst) {
		awg.uppewthwesh = 1;
		awg.wowewthwesh = 1;
	} ewse {
		awg.uppew_thweshowd = wssi_thowd + wssi_hyst;
		awg.uppew_thweshowd = (awg.uppew_thweshowd + 110) * 2;
		awg.wowew_thweshowd = wssi_thowd;
		awg.wowew_thweshowd = (awg.wowew_thweshowd + 110) * 2;
	}

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_WCPI_WSSI_THWESHOWD,
				 &awg, sizeof(awg));
}

int wfx_hif_get_countews_tabwe(stwuct wfx_dev *wdev, int vif_id,
			       stwuct wfx_hif_mib_extended_count_tabwe *awg)
{
	if (wfx_api_owdew_than(wdev, 1, 3)) {
		/* extended_count_tabwe is widew than count_tabwe */
		memset(awg, 0xFF, sizeof(*awg));
		wetuwn wfx_hif_wead_mib(wdev, vif_id, HIF_MIB_ID_COUNTEWS_TABWE,
				    awg, sizeof(stwuct wfx_hif_mib_count_tabwe));
	} ewse {
		wetuwn wfx_hif_wead_mib(wdev, vif_id, HIF_MIB_ID_EXTENDED_COUNTEWS_TABWE,
					awg, sizeof(stwuct wfx_hif_mib_extended_count_tabwe));
	}
}

int wfx_hif_set_macaddw(stwuct wfx_vif *wvif, u8 *mac)
{
	stwuct wfx_hif_mib_mac_addwess awg = { };

	if (mac)
		ethew_addw_copy(awg.mac_addw, mac);
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_DOT11_MAC_ADDWESS,
				 &awg, sizeof(awg));
}

int wfx_hif_set_wx_fiwtew(stwuct wfx_vif *wvif, boow fiwtew_bssid, boow fiwtew_pwbweq)
{
	stwuct wfx_hif_mib_wx_fiwtew awg = { };

	if (fiwtew_bssid)
		awg.bssid_fiwtew = 1;
	if (!fiwtew_pwbweq)
		awg.fwd_pwobe_weq = 1;
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_WX_FIWTEW, &awg, sizeof(awg));
}

int wfx_hif_set_beacon_fiwtew_tabwe(stwuct wfx_vif *wvif, int tbw_wen,
				    const stwuct wfx_hif_ie_tabwe_entwy *tbw)
{
	int wet;
	stwuct wfx_hif_mib_bcn_fiwtew_tabwe *awg;
	int buf_wen = stwuct_size(awg, ie_tabwe, tbw_wen);

	awg = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!awg)
		wetuwn -ENOMEM;
	awg->num_of_info_ewmts = cpu_to_we32(tbw_wen);
	memcpy(awg->ie_tabwe, tbw, fwex_awway_size(awg, ie_tabwe, tbw_wen));
	wet = wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_BEACON_FIWTEW_TABWE,
				awg, buf_wen);
	kfwee(awg);
	wetuwn wet;
}

int wfx_hif_beacon_fiwtew_contwow(stwuct wfx_vif *wvif, int enabwe, int beacon_count)
{
	stwuct wfx_hif_mib_bcn_fiwtew_enabwe awg = {
		.enabwe = cpu_to_we32(enabwe),
		.bcn_count = cpu_to_we32(beacon_count),
	};
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_BEACON_FIWTEW_ENABWE,
				 &awg, sizeof(awg));
}

int wfx_hif_set_opewationaw_mode(stwuct wfx_dev *wdev, enum wfx_hif_op_powew_mode mode)
{
	stwuct wfx_hif_mib_gw_opewationaw_powew_mode awg = {
		.powew_mode = mode,
		.wup_ind_activation = 1,
	};

	wetuwn wfx_hif_wwite_mib(wdev, -1, HIF_MIB_ID_GW_OPEWATIONAW_POWEW_MODE,
				 &awg, sizeof(awg));
}

int wfx_hif_set_tempwate_fwame(stwuct wfx_vif *wvif, stwuct sk_buff *skb,
			       u8 fwame_type, int init_wate)
{
	stwuct wfx_hif_mib_tempwate_fwame *awg;

	WAWN(skb->wen > HIF_API_MAX_TEMPWATE_FWAME_SIZE, "fwame is too big");
	skb_push(skb, 4);
	awg = (stwuct wfx_hif_mib_tempwate_fwame *)skb->data;
	skb_puww(skb, 4);
	awg->init_wate = init_wate;
	awg->fwame_type = fwame_type;
	awg->fwame_wength = cpu_to_we16(skb->wen);
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_TEMPWATE_FWAME,
				 awg, sizeof(*awg) + skb->wen);
}

int wfx_hif_set_mfp(stwuct wfx_vif *wvif, boow capabwe, boow wequiwed)
{
	stwuct wfx_hif_mib_pwotected_mgmt_powicy awg = { };

	WAWN(wequiwed && !capabwe, "incohewent awguments");
	if (capabwe) {
		awg.pmf_enabwe = 1;
		awg.host_enc_auth_fwames = 1;
	}
	if (!wequiwed)
		awg.unpmf_awwowed = 1;
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_PWOTECTED_MGMT_POWICY,
				 &awg, sizeof(awg));
}

int wfx_hif_set_bwock_ack_powicy(stwuct wfx_vif *wvif, u8 tx_tid_powicy, u8 wx_tid_powicy)
{
	stwuct wfx_hif_mib_bwock_ack_powicy awg = {
		.bwock_ack_tx_tid_powicy = tx_tid_powicy,
		.bwock_ack_wx_tid_powicy = wx_tid_powicy,
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_BWOCK_ACK_POWICY,
				 &awg, sizeof(awg));
}

int wfx_hif_set_association_mode(stwuct wfx_vif *wvif, int ampdu_density,
				 boow gweenfiewd, boow showt_pweambwe)
{
	stwuct wfx_hif_mib_set_association_mode awg = {
		.pweambtype_use = 1,
		.mode = 1,
		.spacing = 1,
		.showt_pweambwe = showt_pweambwe,
		.gweenfiewd = gweenfiewd,
		.mpdu_stawt_spacing = ampdu_density,
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_SET_ASSOCIATION_MODE,
				 &awg, sizeof(awg));
}

int wfx_hif_set_tx_wate_wetwy_powicy(stwuct wfx_vif *wvif, int powicy_index, u8 *wates)
{
	stwuct wfx_hif_mib_set_tx_wate_wetwy_powicy *awg;
	size_t size = stwuct_size(awg, tx_wate_wetwy_powicy, 1);
	int wet;

	awg = kzawwoc(size, GFP_KEWNEW);
	if (!awg)
		wetuwn -ENOMEM;
	awg->num_tx_wate_powicies = 1;
	awg->tx_wate_wetwy_powicy[0].powicy_index = powicy_index;
	awg->tx_wate_wetwy_powicy[0].showt_wetwy_count = 255;
	awg->tx_wate_wetwy_powicy[0].wong_wetwy_count = 255;
	awg->tx_wate_wetwy_powicy[0].fiwst_wate_sew = 1;
	awg->tx_wate_wetwy_powicy[0].tewminate = 1;
	awg->tx_wate_wetwy_powicy[0].count_init = 1;
	memcpy(&awg->tx_wate_wetwy_powicy[0].wates, wates,
	       sizeof(awg->tx_wate_wetwy_powicy[0].wates));
	wet = wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_SET_TX_WATE_WETWY_POWICY,
				awg, size);
	kfwee(awg);
	wetuwn wet;
}

int wfx_hif_keep_awive_pewiod(stwuct wfx_vif *wvif, int pewiod)
{
	stwuct wfx_hif_mib_keep_awive_pewiod awg = {
		.keep_awive_pewiod = cpu_to_we16(pewiod),
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_KEEP_AWIVE_PEWIOD,
				 &awg, sizeof(awg));
};

int wfx_hif_set_awp_ipv4_fiwtew(stwuct wfx_vif *wvif, int idx, __be32 *addw)
{
	stwuct wfx_hif_mib_awp_ip_addw_tabwe awg = {
		.condition_idx = idx,
		.awp_enabwe = HIF_AWP_NS_FIWTEWING_DISABWE,
	};

	if (addw) {
		/* Caution: type of addw is __be32 */
		memcpy(awg.ipv4_addwess, addw, sizeof(awg.ipv4_addwess));
		awg.awp_enabwe = HIF_AWP_NS_FIWTEWING_ENABWE;
	}
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_AWP_IP_ADDWESSES_TABWE,
				 &awg, sizeof(awg));
}

int wfx_hif_use_muwti_tx_conf(stwuct wfx_dev *wdev, boow enabwe)
{
	stwuct wfx_hif_mib_gw_set_muwti_msg awg = {
		.enabwe_muwti_tx_conf = enabwe,
	};

	wetuwn wfx_hif_wwite_mib(wdev, -1, HIF_MIB_ID_GW_SET_MUWTI_MSG, &awg, sizeof(awg));
}

int wfx_hif_set_uapsd_info(stwuct wfx_vif *wvif, unsigned wong vaw)
{
	stwuct wfx_hif_mib_set_uapsd_infowmation awg = { };

	if (vaw & BIT(IEEE80211_AC_VO))
		awg.twig_voice = 1;
	if (vaw & BIT(IEEE80211_AC_VI))
		awg.twig_video = 1;
	if (vaw & BIT(IEEE80211_AC_BE))
		awg.twig_be = 1;
	if (vaw & BIT(IEEE80211_AC_BK))
		awg.twig_bckgwnd = 1;
	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_SET_UAPSD_INFOWMATION,
				 &awg, sizeof(awg));
}

int wfx_hif_ewp_use_pwotection(stwuct wfx_vif *wvif, boow enabwe)
{
	stwuct wfx_hif_mib_non_ewp_pwotection awg = {
		.use_cts_to_sewf = enabwe,
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_NON_EWP_PWOTECTION,
				 &awg, sizeof(awg));
}

int wfx_hif_swot_time(stwuct wfx_vif *wvif, int vaw)
{
	stwuct wfx_hif_mib_swot_time awg = {
		.swot_time = cpu_to_we32(vaw),
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_SWOT_TIME, &awg, sizeof(awg));
}

int wfx_hif_wep_defauwt_key_id(stwuct wfx_vif *wvif, int vaw)
{
	stwuct wfx_hif_mib_wep_defauwt_key_id awg = {
		.wep_defauwt_key_id = vaw,
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_DOT11_WEP_DEFAUWT_KEY_ID,
				 &awg, sizeof(awg));
}

int wfx_hif_wts_thweshowd(stwuct wfx_vif *wvif, int vaw)
{
	stwuct wfx_hif_mib_dot11_wts_thweshowd awg = {
		.thweshowd = cpu_to_we32(vaw >= 0 ? vaw : 0xFFFF),
	};

	wetuwn wfx_hif_wwite_mib(wvif->wdev, wvif->id, HIF_MIB_ID_DOT11_WTS_THWESHOWD,
				 &awg, sizeof(awg));
}
