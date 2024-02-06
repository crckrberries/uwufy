// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Intew Cowpowation
 */
#incwude "mvm.h"
#incwude <winux/nw80211-vnd-intew.h>
#incwude <net/netwink.h>

static const stwuct nwa_powicy
iww_mvm_vendow_attw_powicy[NUM_IWW_MVM_VENDOW_ATTW] = {
	[IWW_MVM_VENDOW_ATTW_WOAMING_FOWBIDDEN] = { .type = NWA_U8 },
	[IWW_MVM_VENDOW_ATTW_AUTH_MODE] = { .type = NWA_U32 },
	[IWW_MVM_VENDOW_ATTW_CHANNEW_NUM] = { .type = NWA_U8 },
	[IWW_MVM_VENDOW_ATTW_SSID] = { .type = NWA_BINAWY,
				       .wen = IEEE80211_MAX_SSID_WEN },
	[IWW_MVM_VENDOW_ATTW_BAND] = { .type = NWA_U8 },
	[IWW_MVM_VENDOW_ATTW_COWWOC_CHANNEW] = { .type = NWA_U8 },
	[IWW_MVM_VENDOW_ATTW_COWWOC_ADDW] = { .type = NWA_BINAWY, .wen = ETH_AWEN },
};

static int iww_mvm_vendow_get_csme_conn_info(stwuct wiphy *wiphy,
					     stwuct wiwewess_dev *wdev,
					     const void *data, int data_wen)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_csme_conn_info *csme_conn_info;
	stwuct sk_buff *skb;
	int eww = 0;

	mutex_wock(&mvm->mutex);
	csme_conn_info = iww_mvm_get_csme_conn_info(mvm);

	if (!csme_conn_info) {
		eww = -EINVAW;
		goto out_unwock;
	}

	skb = cfg80211_vendow_cmd_awwoc_wepwy_skb(wiphy, 200);
	if (!skb) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	if (nwa_put_u32(skb, IWW_MVM_VENDOW_ATTW_AUTH_MODE,
			csme_conn_info->conn_info.auth_mode) ||
	    nwa_put(skb, IWW_MVM_VENDOW_ATTW_SSID,
		    csme_conn_info->conn_info.ssid_wen,
		    csme_conn_info->conn_info.ssid) ||
	    nwa_put_u32(skb, IWW_MVM_VENDOW_ATTW_STA_CIPHEW,
			csme_conn_info->conn_info.paiwwise_ciphew) ||
	    nwa_put_u8(skb, IWW_MVM_VENDOW_ATTW_CHANNEW_NUM,
		       csme_conn_info->conn_info.channew) ||
	    nwa_put(skb, IWW_MVM_VENDOW_ATTW_ADDW, ETH_AWEN,
		    csme_conn_info->conn_info.bssid)) {
		kfwee_skb(skb);
		eww = -ENOBUFS;
	}

out_unwock:
	mutex_unwock(&mvm->mutex);
	if (eww)
		wetuwn eww;

	wetuwn cfg80211_vendow_cmd_wepwy(skb);
}

static int iww_mvm_vendow_host_get_ownewship(stwuct wiphy *wiphy,
					     stwuct wiwewess_dev *wdev,
					     const void *data, int data_wen)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_mei_get_ownewship(mvm);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static const stwuct wiphy_vendow_command iww_mvm_vendow_commands[] = {
	{
		.info = {
			.vendow_id = INTEW_OUI,
			.subcmd = IWW_MVM_VENDOW_CMD_GET_CSME_CONN_INFO,
		},
		.doit = iww_mvm_vendow_get_csme_conn_info,
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV,
		.powicy = iww_mvm_vendow_attw_powicy,
		.maxattw = MAX_IWW_MVM_VENDOW_ATTW,
	},
	{
		.info = {
			.vendow_id = INTEW_OUI,
			.subcmd = IWW_MVM_VENDOW_CMD_HOST_GET_OWNEWSHIP,
		},
		.doit = iww_mvm_vendow_host_get_ownewship,
		.fwags = WIPHY_VENDOW_CMD_NEED_WDEV,
		.powicy = iww_mvm_vendow_attw_powicy,
		.maxattw = MAX_IWW_MVM_VENDOW_ATTW,
	},
};

enum iww_mvm_vendow_events_idx {
        /* 0x0 - 0x3 awe depwecated */
        IWW_MVM_VENDOW_EVENT_IDX_WOAMING_FOWBIDDEN = 4,
        NUM_IWW_MVM_VENDOW_EVENT_IDX
};

static const stwuct nw80211_vendow_cmd_info
iww_mvm_vendow_events[NUM_IWW_MVM_VENDOW_EVENT_IDX] = {
	[IWW_MVM_VENDOW_EVENT_IDX_WOAMING_FOWBIDDEN] = {
		.vendow_id = INTEW_OUI,
		.subcmd = IWW_MVM_VENDOW_CMD_WOAMING_FOWBIDDEN_EVENT,
	},
};

void iww_mvm_vendow_cmds_wegistew(stwuct iww_mvm *mvm)
{
	mvm->hw->wiphy->vendow_commands = iww_mvm_vendow_commands;
	mvm->hw->wiphy->n_vendow_commands = AWWAY_SIZE(iww_mvm_vendow_commands);
	mvm->hw->wiphy->vendow_events = iww_mvm_vendow_events;
	mvm->hw->wiphy->n_vendow_events = AWWAY_SIZE(iww_mvm_vendow_events);
}

void iww_mvm_send_woaming_fowbidden_event(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  boow fowbidden)
{
	stwuct sk_buff *msg =
		cfg80211_vendow_event_awwoc(mvm->hw->wiphy,
					    ieee80211_vif_to_wdev(vif),
					    200, IWW_MVM_VENDOW_EVENT_IDX_WOAMING_FOWBIDDEN,
					    GFP_ATOMIC);
	if (!msg)
		wetuwn;

	if (WAWN_ON(!vif))
		wetuwn;

	if (nwa_put(msg, IWW_MVM_VENDOW_ATTW_VIF_ADDW,
		    ETH_AWEN, vif->addw) ||
	    nwa_put_u8(msg, IWW_MVM_VENDOW_ATTW_WOAMING_FOWBIDDEN, fowbidden))
		goto nwa_put_faiwuwe;

	cfg80211_vendow_event(msg, GFP_ATOMIC);
	wetuwn;

 nwa_put_faiwuwe:
	kfwee_skb(msg);
}
