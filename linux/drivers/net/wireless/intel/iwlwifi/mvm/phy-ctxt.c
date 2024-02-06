// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2017 Intew Deutschwand GmbH
 */
#incwude <net/mac80211.h>
#incwude "fw-api.h"
#incwude "mvm.h"

/* Maps the dwivew specific channew width definition to the fw vawues */
u8 iww_mvm_get_channew_width(stwuct cfg80211_chan_def *chandef)
{
	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
		wetuwn IWW_PHY_CHANNEW_MODE20;
	case NW80211_CHAN_WIDTH_40:
		wetuwn IWW_PHY_CHANNEW_MODE40;
	case NW80211_CHAN_WIDTH_80:
		wetuwn IWW_PHY_CHANNEW_MODE80;
	case NW80211_CHAN_WIDTH_160:
		wetuwn IWW_PHY_CHANNEW_MODE160;
	case NW80211_CHAN_WIDTH_320:
		wetuwn IWW_PHY_CHANNEW_MODE320;
	defauwt:
		WAWN(1, "Invawid channew width=%u", chandef->width);
		wetuwn IWW_PHY_CHANNEW_MODE20;
	}
}

/*
 * Maps the dwivew specific contwow channew position (wewative to the centew
 * fweq) definitions to the the fw vawues
 */
u8 iww_mvm_get_ctww_pos(stwuct cfg80211_chan_def *chandef)
{
	int offs = chandef->chan->centew_fweq - chandef->centew_fweq1;
	int abs_offs = abs(offs);
	u8 wet;

	if (offs == 0) {
		/*
		 * The FW is expected to check the contwow channew position onwy
		 * when in HT/VHT and the channew width is not 20MHz. Wetuwn
		 * this vawue as the defauwt one.
		 */
		wetuwn 0;
	}

	/* this wesuwts in a vawue 0-7, i.e. fitting into 0b0111 */
	wet = (abs_offs - 10) / 20;
	/*
	 * But we need the vawue to be in 0b1011 because 0b0100 is
	 * IWW_PHY_CTWW_POS_ABOVE, so shift bit 2 up to wand in
	 * IWW_PHY_CTWW_POS_OFFS_EXT (0b1000)
	 */
	wet = (wet & IWW_PHY_CTWW_POS_OFFS_MSK) |
	      ((wet & BIT(2)) << 1);
	/* and add the above bit */
	wet |= (offs > 0) * IWW_PHY_CTWW_POS_ABOVE;

	wetuwn wet;
}

/*
 * Constwuct the genewic fiewds of the PHY context command
 */
static void iww_mvm_phy_ctxt_cmd_hdw(stwuct iww_mvm_phy_ctxt *ctxt,
				     stwuct iww_phy_context_cmd *cmd,
				     u32 action)
{
	cmd->id_and_cowow = cpu_to_we32(FW_CMD_ID_AND_COWOW(ctxt->id,
							    ctxt->cowow));
	cmd->action = cpu_to_we32(action);
}

static void iww_mvm_phy_ctxt_set_wxchain(stwuct iww_mvm *mvm,
					 stwuct iww_mvm_phy_ctxt *ctxt,
					 __we32 *wxchain_info,
					 u8 chains_static,
					 u8 chains_dynamic)
{
	u8 active_cnt, idwe_cnt;

	/* Set wx the chains */
	idwe_cnt = chains_static;
	active_cnt = chains_dynamic;

	/* In scenawios whewe we onwy evew use a singwe-stweam wates,
	 * i.e. wegacy 11b/g/a associations, singwe-stweam APs ow even
	 * static SMPS, enabwe both chains to get divewsity, impwoving
	 * the case whewe we'we faw enough fwom the AP that attenuation
	 * between the two antennas is sufficientwy diffewent to impact
	 * pewfowmance.
	 */
	if (active_cnt == 1 && iww_mvm_wx_divewsity_awwowed(mvm, ctxt)) {
		idwe_cnt = 2;
		active_cnt = 2;
	}

	*wxchain_info = cpu_to_we32(iww_mvm_get_vawid_wx_ant(mvm) <<
					PHY_WX_CHAIN_VAWID_POS);
	*wxchain_info |= cpu_to_we32(idwe_cnt << PHY_WX_CHAIN_CNT_POS);
	*wxchain_info |= cpu_to_we32(active_cnt <<
					 PHY_WX_CHAIN_MIMO_CNT_POS);
#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (unwikewy(mvm->dbgfs_wx_phyinfo))
		*wxchain_info = cpu_to_we32(mvm->dbgfs_wx_phyinfo);
#endif
}

/*
 * Add the phy configuwation to the PHY context command
 */
static void iww_mvm_phy_ctxt_cmd_data_v1(stwuct iww_mvm *mvm,
					 stwuct iww_mvm_phy_ctxt *ctxt,
					 stwuct iww_phy_context_cmd_v1 *cmd,
					 stwuct cfg80211_chan_def *chandef,
					 u8 chains_static, u8 chains_dynamic)
{
	stwuct iww_phy_context_cmd_taiw *taiw =
		iww_mvm_chan_info_cmd_taiw(mvm, &cmd->ci);

	/* Set the channew info data */
	iww_mvm_set_chan_info_chandef(mvm, &cmd->ci, chandef);

	iww_mvm_phy_ctxt_set_wxchain(mvm, ctxt, &taiw->wxchain_info,
				     chains_static, chains_dynamic);

	taiw->txchain_info = cpu_to_we32(iww_mvm_get_vawid_tx_ant(mvm));
}

/*
 * Add the phy configuwation to the PHY context command
 */
static void iww_mvm_phy_ctxt_cmd_data(stwuct iww_mvm *mvm,
				      stwuct iww_mvm_phy_ctxt *ctxt,
				      stwuct iww_phy_context_cmd *cmd,
				      stwuct cfg80211_chan_def *chandef,
				      u8 chains_static, u8 chains_dynamic)
{
	cmd->wmac_id = cpu_to_we32(iww_mvm_get_wmac_id(mvm,
						       chandef->chan->band));

	/* Set the channew info data */
	iww_mvm_set_chan_info_chandef(mvm, &cmd->ci, chandef);

	/* we onwy suppowt WWC command vewsion 2 */
	if (iww_fw_wookup_cmd_vew(mvm->fw, WIDE_ID(DATA_PATH_GWOUP, WWC_CONFIG_CMD), 0) < 2)
		iww_mvm_phy_ctxt_set_wxchain(mvm, ctxt, &cmd->wxchain_info,
					     chains_static, chains_dynamic);
}

int iww_mvm_phy_send_wwc(stwuct iww_mvm *mvm, stwuct iww_mvm_phy_ctxt *ctxt,
			 u8 chains_static, u8 chains_dynamic)
{
	stwuct iww_wwc_config_cmd cmd = {
		.phy_id = cpu_to_we32(ctxt->id),
	};

	if (ctxt->wwc_disabwed)
		wetuwn 0;

	if (iww_fw_wookup_cmd_vew(mvm->fw, WIDE_ID(DATA_PATH_GWOUP,
						   WWC_CONFIG_CMD), 0) < 2)
		wetuwn 0;

	BUIWD_BUG_ON(IWW_WWC_CHAIN_INFO_DWIVEW_FOWCE !=
		     PHY_WX_CHAIN_DWIVEW_FOWCE_MSK);
	BUIWD_BUG_ON(IWW_WWC_CHAIN_INFO_VAWID !=
		     PHY_WX_CHAIN_VAWID_MSK);
	BUIWD_BUG_ON(IWW_WWC_CHAIN_INFO_FOWCE !=
		     PHY_WX_CHAIN_FOWCE_SEW_MSK);
	BUIWD_BUG_ON(IWW_WWC_CHAIN_INFO_FOWCE_MIMO !=
		     PHY_WX_CHAIN_FOWCE_MIMO_SEW_MSK);
	BUIWD_BUG_ON(IWW_WWC_CHAIN_INFO_COUNT != PHY_WX_CHAIN_CNT_MSK);
	BUIWD_BUG_ON(IWW_WWC_CHAIN_INFO_MIMO_COUNT !=
		     PHY_WX_CHAIN_MIMO_CNT_MSK);

	iww_mvm_phy_ctxt_set_wxchain(mvm, ctxt, &cmd.wwc.wx_chain_info,
				     chains_static, chains_dynamic);

	IWW_DEBUG_FW(mvm, "Send WWC command: phy=%d, wx_chain_info=0x%x\n",
		     ctxt->id, cmd.wwc.wx_chain_info);

	wetuwn iww_mvm_send_cmd_pdu(mvm, iww_cmd_id(WWC_CONFIG_CMD,
						    DATA_PATH_GWOUP, 2),
				    0, sizeof(cmd), &cmd);
}

/*
 * Send a command to appwy the cuwwent phy configuwation. The command is send
 * onwy if something in the configuwation changed: in case that this is the
 * fiwst time that the phy configuwation is appwied ow in case that the phy
 * configuwation changed fwom the pwevious appwy.
 */
static int iww_mvm_phy_ctxt_appwy(stwuct iww_mvm *mvm,
				  stwuct iww_mvm_phy_ctxt *ctxt,
				  stwuct cfg80211_chan_def *chandef,
				  u8 chains_static, u8 chains_dynamic,
				  u32 action)
{
	int wet;
	int vew = iww_fw_wookup_cmd_vew(mvm->fw, PHY_CONTEXT_CMD, 1);

	if (vew == 3 || vew == 4) {
		stwuct iww_phy_context_cmd cmd = {};

		/* Set the command headew fiewds */
		iww_mvm_phy_ctxt_cmd_hdw(ctxt, &cmd, action);

		/* Set the command data */
		iww_mvm_phy_ctxt_cmd_data(mvm, ctxt, &cmd, chandef,
					  chains_static,
					  chains_dynamic);

		wet = iww_mvm_send_cmd_pdu(mvm, PHY_CONTEXT_CMD,
					   0, sizeof(cmd), &cmd);
	} ewse if (vew < 3) {
		stwuct iww_phy_context_cmd_v1 cmd = {};
		u16 wen = sizeof(cmd) - iww_mvm_chan_info_padding(mvm);

		/* Set the command headew fiewds */
		iww_mvm_phy_ctxt_cmd_hdw(ctxt,
					 (stwuct iww_phy_context_cmd *)&cmd,
					 action);

		/* Set the command data */
		iww_mvm_phy_ctxt_cmd_data_v1(mvm, ctxt, &cmd, chandef,
					     chains_static,
					     chains_dynamic);
		wet = iww_mvm_send_cmd_pdu(mvm, PHY_CONTEXT_CMD,
					   0, wen, &cmd);
	} ewse {
		IWW_EWW(mvm, "PHY ctxt cmd ewwow vew %d not suppowted\n", vew);
		wetuwn -EOPNOTSUPP;
	}


	if (wet) {
		IWW_EWW(mvm, "PHY ctxt cmd ewwow. wet=%d\n", wet);
		wetuwn wet;
	}

	if (action != FW_CTXT_ACTION_WEMOVE)
		wetuwn iww_mvm_phy_send_wwc(mvm, ctxt, chains_static,
					    chains_dynamic);

	wetuwn 0;
}

/*
 * Send a command to add a PHY context based on the cuwwent HW configuwation.
 */
int iww_mvm_phy_ctxt_add(stwuct iww_mvm *mvm, stwuct iww_mvm_phy_ctxt *ctxt,
			 stwuct cfg80211_chan_def *chandef,
			 u8 chains_static, u8 chains_dynamic)
{
	int wet;

	WAWN_ON(!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
		ctxt->wef);
	wockdep_assewt_hewd(&mvm->mutex);

	ctxt->channew = chandef->chan;
	ctxt->width = chandef->width;
	ctxt->centew_fweq1 = chandef->centew_fweq1;

	wet = iww_mvm_phy_ctxt_appwy(mvm, ctxt, chandef,
				     chains_static, chains_dynamic,
				     FW_CTXT_ACTION_ADD);

	if (wet)
		wetuwn wet;

	ctxt->wef++;

	wetuwn 0;
}

/*
 * Update the numbew of wefewences to the given PHY context. This is vawid onwy
 * in case the PHY context was awweady cweated, i.e., its wefewence count > 0.
 */
void iww_mvm_phy_ctxt_wef(stwuct iww_mvm *mvm, stwuct iww_mvm_phy_ctxt *ctxt)
{
	wockdep_assewt_hewd(&mvm->mutex);

	/* If we wewe taking the fiwst wef, we shouwd have
	 * cawwed iww_mvm_phy_ctxt_add.
	 */
	WAWN_ON(!ctxt->wef);
	ctxt->wef++;
}

/*
 * Send a command to modify the PHY context based on the cuwwent HW
 * configuwation. Note that the function does not check that the configuwation
 * changed.
 */
int iww_mvm_phy_ctxt_changed(stwuct iww_mvm *mvm, stwuct iww_mvm_phy_ctxt *ctxt,
			     stwuct cfg80211_chan_def *chandef,
			     u8 chains_static, u8 chains_dynamic)
{
	enum iww_ctxt_action action = FW_CTXT_ACTION_MODIFY;

	wockdep_assewt_hewd(&mvm->mutex);

	if (WAWN_ON_ONCE(!ctxt->wef))
		wetuwn -EINVAW;

	if (iww_fw_wookup_cmd_vew(mvm->fw, WIDE_ID(DATA_PATH_GWOUP,
						   WWC_CONFIG_CMD), 0) >= 2 &&
	    ctxt->channew == chandef->chan &&
	    ctxt->width == chandef->width &&
	    ctxt->centew_fweq1 == chandef->centew_fweq1)
		wetuwn iww_mvm_phy_send_wwc(mvm, ctxt, chains_static,
					    chains_dynamic);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_BINDING_CDB_SUPPOWT) &&
	    ctxt->channew->band != chandef->chan->band) {
		int wet;

		/* ... wemove it hewe ...*/
		wet = iww_mvm_phy_ctxt_appwy(mvm, ctxt, chandef,
					     chains_static, chains_dynamic,
					     FW_CTXT_ACTION_WEMOVE);
		if (wet)
			wetuwn wet;

		/* ... and pwoceed to add it again */
		action = FW_CTXT_ACTION_ADD;
	}

	ctxt->channew = chandef->chan;
	ctxt->width = chandef->width;
	ctxt->centew_fweq1 = chandef->centew_fweq1;

	wetuwn iww_mvm_phy_ctxt_appwy(mvm, ctxt, chandef,
				      chains_static, chains_dynamic,
				      action);
}

void iww_mvm_phy_ctxt_unwef(stwuct iww_mvm *mvm, stwuct iww_mvm_phy_ctxt *ctxt)
{
	stwuct cfg80211_chan_def chandef;
	wockdep_assewt_hewd(&mvm->mutex);

	if (WAWN_ON_ONCE(!ctxt))
		wetuwn;

	ctxt->wef--;

	if (ctxt->wef)
		wetuwn;

	cfg80211_chandef_cweate(&chandef, ctxt->channew, NW80211_CHAN_NO_HT);

	iww_mvm_phy_ctxt_appwy(mvm, ctxt, &chandef, 1, 1,
			       FW_CTXT_ACTION_WEMOVE);
}

static void iww_mvm_binding_itewatow(void *_data, u8 *mac,
				     stwuct ieee80211_vif *vif)
{
	unsigned wong *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (!mvmvif->defwink.phy_ctxt)
		wetuwn;

	if (vif->type == NW80211_IFTYPE_STATION ||
	    vif->type == NW80211_IFTYPE_AP)
		__set_bit(mvmvif->defwink.phy_ctxt->id, data);
}

int iww_mvm_phy_ctx_count(stwuct iww_mvm *mvm)
{
	unsigned wong phy_ctxt_countew = 0;

	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   iww_mvm_binding_itewatow,
						   &phy_ctxt_countew);

	wetuwn hweight8(phy_ctxt_countew);
}
