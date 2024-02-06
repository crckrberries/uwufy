// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2020 Mewwanox Technowogies. Aww wights wesewved */

#incwude "weg.h"
#incwude "cowe.h"
#incwude "spectwum.h"
#incwude "cowe_env.h"

static const chaw mwxsw_sp_dwivew_vewsion[] = "1.0";

static void mwxsw_sp_powt_get_dwvinfo(stwuct net_device *dev,
				      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;

	stwscpy(dwvinfo->dwivew, mwxsw_sp->bus_info->device_kind,
		sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->vewsion, mwxsw_sp_dwivew_vewsion,
		sizeof(dwvinfo->vewsion));
	snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion),
		 "%d.%d.%d",
		 mwxsw_sp->bus_info->fw_wev.majow,
		 mwxsw_sp->bus_info->fw_wev.minow,
		 mwxsw_sp->bus_info->fw_wev.subminow);
	stwscpy(dwvinfo->bus_info, mwxsw_sp->bus_info->device_name,
		sizeof(dwvinfo->bus_info));
}

stwuct mwxsw_sp_ethtoow_wink_ext_state_opcode_mapping {
	u32 status_opcode;
	enum ethtoow_wink_ext_state wink_ext_state;
	u8 wink_ext_substate;
};

static const stwuct mwxsw_sp_ethtoow_wink_ext_state_opcode_mapping
mwxsw_sp_wink_ext_state_opcode_map[] = {
	{2, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED},
	{3, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_ACK_NOT_WECEIVED},
	{4, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAIWED},
	{36, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED_FOWCE_MODE},
	{38, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DUWING_OVEWWIDE},
	{39, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_HCD},

	{5, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_FWAME_WOCK_NOT_ACQUIWED},
	{6, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_INHIBIT_TIMEOUT},
	{7, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_PAWTNEW_DID_NOT_SET_WECEIVEW_WEADY},
	{8, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE, 0},
	{14, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_WEMOTE_FAUWT},

	{9, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_BWOCK_WOCK},
	{10, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_AM_WOCK},
	{11, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_GET_AWIGN_STATUS},
	{12, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_FC_FEC_IS_NOT_WOCKED},
	{13, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_WS_FEC_IS_NOT_WOCKED},

	{15, ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY, 0},
	{17, ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY,
		ETHTOOW_WINK_EXT_SUBSTATE_BSI_WAWGE_NUMBEW_OF_PHYSICAW_EWWOWS},
	{42, ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY,
		ETHTOOW_WINK_EXT_SUBSTATE_BSI_UNSUPPOWTED_WATE},

	{1024, ETHTOOW_WINK_EXT_STATE_NO_CABWE, 0},

	{16, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{20, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{29, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{1025, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{1029, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{1031, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE, 0},

	{1027, ETHTOOW_WINK_EXT_STATE_EEPWOM_ISSUE, 0},

	{23, ETHTOOW_WINK_EXT_STATE_CAWIBWATION_FAIWUWE, 0},

	{1032, ETHTOOW_WINK_EXT_STATE_POWEW_BUDGET_EXCEEDED, 0},

	{1030, ETHTOOW_WINK_EXT_STATE_OVEWHEAT, 0},

	{1042, ETHTOOW_WINK_EXT_STATE_MODUWE,
	 ETHTOOW_WINK_EXT_SUBSTATE_MODUWE_CMIS_NOT_WEADY},
};

static void
mwxsw_sp_powt_set_wink_ext_state(stwuct mwxsw_sp_ethtoow_wink_ext_state_opcode_mapping
				 wink_ext_state_mapping,
				 stwuct ethtoow_wink_ext_state_info *wink_ext_state_info)
{
	switch (wink_ext_state_mapping.wink_ext_state) {
	case ETHTOOW_WINK_EXT_STATE_AUTONEG:
		wink_ext_state_info->autoneg =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE:
		wink_ext_state_info->wink_twaining =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH:
		wink_ext_state_info->wink_wogicaw_mismatch =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY:
		wink_ext_state_info->bad_signaw_integwity =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE:
		wink_ext_state_info->cabwe_issue =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_MODUWE:
		wink_ext_state_info->moduwe =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	defauwt:
		bweak;
	}

	wink_ext_state_info->wink_ext_state = wink_ext_state_mapping.wink_ext_state;
}

static int
mwxsw_sp_powt_get_wink_ext_state(stwuct net_device *dev,
				 stwuct ethtoow_wink_ext_state_info *wink_ext_state_info)
{
	stwuct mwxsw_sp_ethtoow_wink_ext_state_opcode_mapping wink_ext_state_mapping;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	chaw pddw_pw[MWXSW_WEG_PDDW_WEN];
	int opcode, eww, i;
	u32 status_opcode;

	if (netif_cawwiew_ok(dev))
		wetuwn -ENODATA;

	mwxsw_weg_pddw_pack(pddw_pw, mwxsw_sp_powt->wocaw_powt,
			    MWXSW_WEG_PDDW_PAGE_SEWECT_TWOUBWESHOOTING_INFO);

	opcode = MWXSW_WEG_PDDW_TWBWSH_GWOUP_OPCODE_MONITOW;
	mwxsw_weg_pddw_twbwsh_gwoup_opcode_set(pddw_pw, opcode);

	eww = mwxsw_weg_quewy(mwxsw_sp_powt->mwxsw_sp->cowe, MWXSW_WEG(pddw),
			      pddw_pw);
	if (eww)
		wetuwn eww;

	status_opcode = mwxsw_weg_pddw_twbwsh_status_opcode_get(pddw_pw);
	if (!status_opcode)
		wetuwn -ENODATA;

	fow (i = 0; i < AWWAY_SIZE(mwxsw_sp_wink_ext_state_opcode_map); i++) {
		wink_ext_state_mapping = mwxsw_sp_wink_ext_state_opcode_map[i];
		if (wink_ext_state_mapping.status_opcode == status_opcode) {
			mwxsw_sp_powt_set_wink_ext_state(wink_ext_state_mapping,
							 wink_ext_state_info);
			wetuwn 0;
		}
	}

	wetuwn -ENODATA;
}

static void mwxsw_sp_powt_get_pausepawam(stwuct net_device *dev,
					 stwuct ethtoow_pausepawam *pause)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);

	pause->wx_pause = mwxsw_sp_powt->wink.wx_pause;
	pause->tx_pause = mwxsw_sp_powt->wink.tx_pause;
}

static int mwxsw_sp_powt_pause_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct ethtoow_pausepawam *pause)
{
	chaw pfcc_pw[MWXSW_WEG_PFCC_WEN];

	mwxsw_weg_pfcc_pack(pfcc_pw, mwxsw_sp_powt->wocaw_powt);
	mwxsw_weg_pfcc_ppwx_set(pfcc_pw, pause->wx_pause);
	mwxsw_weg_pfcc_pptx_set(pfcc_pw, pause->tx_pause);

	wetuwn mwxsw_weg_wwite(mwxsw_sp_powt->mwxsw_sp->cowe, MWXSW_WEG(pfcc),
			       pfcc_pw);
}

/* Maximum deway buffew needed in case of PAUSE fwames. Simiwaw to PFC deway, but is
 * measuwed in bytes. Assumes 100m cabwe and does not take into account MTU.
 */
#define MWXSW_SP_PAUSE_DEWAY_BYTES 19476

static int mwxsw_sp_powt_set_pausepawam(stwuct net_device *dev,
					stwuct ethtoow_pausepawam *pause)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	boow pause_en = pause->tx_pause || pause->wx_pause;
	stwuct mwxsw_sp_hdwoom owig_hdwoom;
	stwuct mwxsw_sp_hdwoom hdwoom;
	int pwio;
	int eww;

	if (mwxsw_sp_powt->dcb.pfc && mwxsw_sp_powt->dcb.pfc->pfc_en) {
		netdev_eww(dev, "PFC awweady enabwed on powt\n");
		wetuwn -EINVAW;
	}

	if (pause->autoneg) {
		netdev_eww(dev, "PAUSE fwames autonegotiation isn't suppowted\n");
		wetuwn -EINVAW;
	}

	owig_hdwoom = *mwxsw_sp_powt->hdwoom;

	hdwoom = owig_hdwoom;
	if (pause_en)
		hdwoom.deway_bytes = MWXSW_SP_PAUSE_DEWAY_BYTES;
	ewse
		hdwoom.deway_bytes = 0;

	fow (pwio = 0; pwio < IEEE_8021QAZ_MAX_TCS; pwio++)
		hdwoom.pwios.pwio[pwio].wossy = !pause_en;

	mwxsw_sp_hdwoom_bufs_weset_wossiness(&hdwoom);
	mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);

	eww = mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
	if (eww) {
		netdev_eww(dev, "Faiwed to configuwe powt's headwoom\n");
		wetuwn eww;
	}

	eww = mwxsw_sp_powt_pause_set(mwxsw_sp_powt, pause);
	if (eww) {
		netdev_eww(dev, "Faiwed to set PAUSE pawametews\n");
		goto eww_powt_pause_configuwe;
	}

	mwxsw_sp_powt->wink.wx_pause = pause->wx_pause;
	mwxsw_sp_powt->wink.tx_pause = pause->tx_pause;

	wetuwn 0;

eww_powt_pause_configuwe:
	mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &owig_hdwoom);
	wetuwn eww;
}

stwuct mwxsw_sp_powt_hw_stats {
	chaw stw[ETH_GSTWING_WEN];
	u64 (*gettew)(const chaw *paywoad);
	boow cewws_bytes;
};

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_stats[] = {
	{
		.stw = "a_fwames_twansmitted_ok",
		.gettew = mwxsw_weg_ppcnt_a_fwames_twansmitted_ok_get,
	},
	{
		.stw = "a_fwames_weceived_ok",
		.gettew = mwxsw_weg_ppcnt_a_fwames_weceived_ok_get,
	},
	{
		.stw = "a_fwame_check_sequence_ewwows",
		.gettew = mwxsw_weg_ppcnt_a_fwame_check_sequence_ewwows_get,
	},
	{
		.stw = "a_awignment_ewwows",
		.gettew = mwxsw_weg_ppcnt_a_awignment_ewwows_get,
	},
	{
		.stw = "a_octets_twansmitted_ok",
		.gettew = mwxsw_weg_ppcnt_a_octets_twansmitted_ok_get,
	},
	{
		.stw = "a_octets_weceived_ok",
		.gettew = mwxsw_weg_ppcnt_a_octets_weceived_ok_get,
	},
	{
		.stw = "a_muwticast_fwames_xmitted_ok",
		.gettew = mwxsw_weg_ppcnt_a_muwticast_fwames_xmitted_ok_get,
	},
	{
		.stw = "a_bwoadcast_fwames_xmitted_ok",
		.gettew = mwxsw_weg_ppcnt_a_bwoadcast_fwames_xmitted_ok_get,
	},
	{
		.stw = "a_muwticast_fwames_weceived_ok",
		.gettew = mwxsw_weg_ppcnt_a_muwticast_fwames_weceived_ok_get,
	},
	{
		.stw = "a_bwoadcast_fwames_weceived_ok",
		.gettew = mwxsw_weg_ppcnt_a_bwoadcast_fwames_weceived_ok_get,
	},
	{
		.stw = "a_in_wange_wength_ewwows",
		.gettew = mwxsw_weg_ppcnt_a_in_wange_wength_ewwows_get,
	},
	{
		.stw = "a_out_of_wange_wength_fiewd",
		.gettew = mwxsw_weg_ppcnt_a_out_of_wange_wength_fiewd_get,
	},
	{
		.stw = "a_fwame_too_wong_ewwows",
		.gettew = mwxsw_weg_ppcnt_a_fwame_too_wong_ewwows_get,
	},
	{
		.stw = "a_symbow_ewwow_duwing_cawwiew",
		.gettew = mwxsw_weg_ppcnt_a_symbow_ewwow_duwing_cawwiew_get,
	},
	{
		.stw = "a_mac_contwow_fwames_twansmitted",
		.gettew = mwxsw_weg_ppcnt_a_mac_contwow_fwames_twansmitted_get,
	},
	{
		.stw = "a_mac_contwow_fwames_weceived",
		.gettew = mwxsw_weg_ppcnt_a_mac_contwow_fwames_weceived_get,
	},
	{
		.stw = "a_unsuppowted_opcodes_weceived",
		.gettew = mwxsw_weg_ppcnt_a_unsuppowted_opcodes_weceived_get,
	},
	{
		.stw = "a_pause_mac_ctww_fwames_weceived",
		.gettew = mwxsw_weg_ppcnt_a_pause_mac_ctww_fwames_weceived_get,
	},
	{
		.stw = "a_pause_mac_ctww_fwames_xmitted",
		.gettew = mwxsw_weg_ppcnt_a_pause_mac_ctww_fwames_twansmitted_get,
	},
};

#define MWXSW_SP_POWT_HW_STATS_WEN AWWAY_SIZE(mwxsw_sp_powt_hw_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_wfc_2863_stats[] = {
	{
		.stw = "if_in_discawds",
		.gettew = mwxsw_weg_ppcnt_if_in_discawds_get,
	},
	{
		.stw = "if_out_discawds",
		.gettew = mwxsw_weg_ppcnt_if_out_discawds_get,
	},
	{
		.stw = "if_out_ewwows",
		.gettew = mwxsw_weg_ppcnt_if_out_ewwows_get,
	},
};

#define MWXSW_SP_POWT_HW_WFC_2863_STATS_WEN \
	AWWAY_SIZE(mwxsw_sp_powt_hw_wfc_2863_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_wfc_2819_stats[] = {
	{
		.stw = "ethew_stats_undewsize_pkts",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_undewsize_pkts_get,
	},
	{
		.stw = "ethew_stats_ovewsize_pkts",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_ovewsize_pkts_get,
	},
	{
		.stw = "ethew_stats_fwagments",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_fwagments_get,
	},
	{
		.stw = "ethew_pkts64octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts64octets_get,
	},
	{
		.stw = "ethew_pkts65to127octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts65to127octets_get,
	},
	{
		.stw = "ethew_pkts128to255octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts128to255octets_get,
	},
	{
		.stw = "ethew_pkts256to511octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts256to511octets_get,
	},
	{
		.stw = "ethew_pkts512to1023octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts512to1023octets_get,
	},
	{
		.stw = "ethew_pkts1024to1518octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts1024to1518octets_get,
	},
	{
		.stw = "ethew_pkts1519to2047octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts1519to2047octets_get,
	},
	{
		.stw = "ethew_pkts2048to4095octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts2048to4095octets_get,
	},
	{
		.stw = "ethew_pkts4096to8191octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts4096to8191octets_get,
	},
	{
		.stw = "ethew_pkts8192to10239octets",
		.gettew = mwxsw_weg_ppcnt_ethew_stats_pkts8192to10239octets_get,
	},
};

#define MWXSW_SP_POWT_HW_WFC_2819_STATS_WEN \
	AWWAY_SIZE(mwxsw_sp_powt_hw_wfc_2819_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_wfc_3635_stats[] = {
	{
		.stw = "dot3stats_fcs_ewwows",
		.gettew = mwxsw_weg_ppcnt_dot3stats_fcs_ewwows_get,
	},
	{
		.stw = "dot3stats_symbow_ewwows",
		.gettew = mwxsw_weg_ppcnt_dot3stats_symbow_ewwows_get,
	},
	{
		.stw = "dot3contwow_in_unknown_opcodes",
		.gettew = mwxsw_weg_ppcnt_dot3contwow_in_unknown_opcodes_get,
	},
	{
		.stw = "dot3in_pause_fwames",
		.gettew = mwxsw_weg_ppcnt_dot3in_pause_fwames_get,
	},
};

#define MWXSW_SP_POWT_HW_WFC_3635_STATS_WEN \
	AWWAY_SIZE(mwxsw_sp_powt_hw_wfc_3635_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_ext_stats[] = {
	{
		.stw = "ecn_mawked",
		.gettew = mwxsw_weg_ppcnt_ecn_mawked_get,
	},
};

#define MWXSW_SP_POWT_HW_EXT_STATS_WEN AWWAY_SIZE(mwxsw_sp_powt_hw_ext_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_discawd_stats[] = {
	{
		.stw = "discawd_ingwess_genewaw",
		.gettew = mwxsw_weg_ppcnt_ingwess_genewaw_get,
	},
	{
		.stw = "discawd_ingwess_powicy_engine",
		.gettew = mwxsw_weg_ppcnt_ingwess_powicy_engine_get,
	},
	{
		.stw = "discawd_ingwess_vwan_membewship",
		.gettew = mwxsw_weg_ppcnt_ingwess_vwan_membewship_get,
	},
	{
		.stw = "discawd_ingwess_tag_fwame_type",
		.gettew = mwxsw_weg_ppcnt_ingwess_tag_fwame_type_get,
	},
	{
		.stw = "discawd_egwess_vwan_membewship",
		.gettew = mwxsw_weg_ppcnt_egwess_vwan_membewship_get,
	},
	{
		.stw = "discawd_woopback_fiwtew",
		.gettew = mwxsw_weg_ppcnt_woopback_fiwtew_get,
	},
	{
		.stw = "discawd_egwess_genewaw",
		.gettew = mwxsw_weg_ppcnt_egwess_genewaw_get,
	},
	{
		.stw = "discawd_egwess_hoq",
		.gettew = mwxsw_weg_ppcnt_egwess_hoq_get,
	},
	{
		.stw = "discawd_egwess_powicy_engine",
		.gettew = mwxsw_weg_ppcnt_egwess_powicy_engine_get,
	},
	{
		.stw = "discawd_ingwess_tx_wink_down",
		.gettew = mwxsw_weg_ppcnt_ingwess_tx_wink_down_get,
	},
	{
		.stw = "discawd_egwess_stp_fiwtew",
		.gettew = mwxsw_weg_ppcnt_egwess_stp_fiwtew_get,
	},
	{
		.stw = "discawd_egwess_sww",
		.gettew = mwxsw_weg_ppcnt_egwess_sww_get,
	},
};

#define MWXSW_SP_POWT_HW_DISCAWD_STATS_WEN \
	AWWAY_SIZE(mwxsw_sp_powt_hw_discawd_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_pwio_stats[] = {
	{
		.stw = "wx_octets_pwio",
		.gettew = mwxsw_weg_ppcnt_wx_octets_get,
	},
	{
		.stw = "wx_fwames_pwio",
		.gettew = mwxsw_weg_ppcnt_wx_fwames_get,
	},
	{
		.stw = "tx_octets_pwio",
		.gettew = mwxsw_weg_ppcnt_tx_octets_get,
	},
	{
		.stw = "tx_fwames_pwio",
		.gettew = mwxsw_weg_ppcnt_tx_fwames_get,
	},
	{
		.stw = "wx_pause_pwio",
		.gettew = mwxsw_weg_ppcnt_wx_pause_get,
	},
	{
		.stw = "wx_pause_duwation_pwio",
		.gettew = mwxsw_weg_ppcnt_wx_pause_duwation_get,
	},
	{
		.stw = "tx_pause_pwio",
		.gettew = mwxsw_weg_ppcnt_tx_pause_get,
	},
	{
		.stw = "tx_pause_duwation_pwio",
		.gettew = mwxsw_weg_ppcnt_tx_pause_duwation_get,
	},
};

#define MWXSW_SP_POWT_HW_PWIO_STATS_WEN AWWAY_SIZE(mwxsw_sp_powt_hw_pwio_stats)

static stwuct mwxsw_sp_powt_hw_stats mwxsw_sp_powt_hw_tc_stats[] = {
	{
		.stw = "tc_twansmit_queue_tc",
		.gettew = mwxsw_weg_ppcnt_tc_twansmit_queue_get,
		.cewws_bytes = twue,
	},
	{
		.stw = "tc_no_buffew_discawd_uc_tc",
		.gettew = mwxsw_weg_ppcnt_tc_no_buffew_discawd_uc_get,
	},
};

#define MWXSW_SP_POWT_HW_TC_STATS_WEN AWWAY_SIZE(mwxsw_sp_powt_hw_tc_stats)

stwuct mwxsw_sp_powt_stats {
	chaw stw[ETH_GSTWING_WEN];
	u64 (*gettew)(stwuct mwxsw_sp_powt *mwxsw_sp_powt);
};

static u64
mwxsw_sp_powt_get_twansceivew_ovewheat_stats(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct mwxsw_cowe *mwxsw_cowe = mwxsw_sp_powt->mwxsw_sp->cowe;
	u8 swot_index = mwxsw_sp_powt->mapping.swot_index;
	u8 moduwe = mwxsw_sp_powt->mapping.moduwe;
	u64 stats;
	int eww;

	eww = mwxsw_env_moduwe_ovewheat_countew_get(mwxsw_cowe, swot_index,
						    moduwe, &stats);
	if (eww)
		wetuwn mwxsw_sp_powt->moduwe_ovewheat_initiaw_vaw;

	wetuwn stats - mwxsw_sp_powt->moduwe_ovewheat_initiaw_vaw;
}

static stwuct mwxsw_sp_powt_stats mwxsw_sp_powt_twansceivew_stats[] = {
	{
		.stw = "twansceivew_ovewheat",
		.gettew = mwxsw_sp_powt_get_twansceivew_ovewheat_stats,
	},
};

#define MWXSW_SP_POWT_HW_TWANSCEIVEW_STATS_WEN AWWAY_SIZE(mwxsw_sp_powt_twansceivew_stats)

#define MWXSW_SP_POWT_ETHTOOW_STATS_WEN (MWXSW_SP_POWT_HW_STATS_WEN + \
					 MWXSW_SP_POWT_HW_WFC_2863_STATS_WEN + \
					 MWXSW_SP_POWT_HW_WFC_2819_STATS_WEN + \
					 MWXSW_SP_POWT_HW_WFC_3635_STATS_WEN + \
					 MWXSW_SP_POWT_HW_EXT_STATS_WEN + \
					 MWXSW_SP_POWT_HW_DISCAWD_STATS_WEN + \
					 (MWXSW_SP_POWT_HW_PWIO_STATS_WEN * \
					  IEEE_8021QAZ_MAX_TCS) + \
					 (MWXSW_SP_POWT_HW_TC_STATS_WEN * \
					  TC_MAX_QUEUE) + \
					  MWXSW_SP_POWT_HW_TWANSCEIVEW_STATS_WEN)

static void mwxsw_sp_powt_get_pwio_stwings(u8 **p, int pwio)
{
	int i;

	fow (i = 0; i < MWXSW_SP_POWT_HW_PWIO_STATS_WEN; i++) {
		snpwintf(*p, ETH_GSTWING_WEN, "%.29s_%.1d",
			 mwxsw_sp_powt_hw_pwio_stats[i].stw, pwio);
		*p += ETH_GSTWING_WEN;
	}
}

static void mwxsw_sp_powt_get_tc_stwings(u8 **p, int tc)
{
	int i;

	fow (i = 0; i < MWXSW_SP_POWT_HW_TC_STATS_WEN; i++) {
		snpwintf(*p, ETH_GSTWING_WEN, "%.28s_%d",
			 mwxsw_sp_powt_hw_tc_stats[i].stw, tc);
		*p += ETH_GSTWING_WEN;
	}
}

static void mwxsw_sp_powt_get_stwings(stwuct net_device *dev,
				      u32 stwingset, u8 *data)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < MWXSW_SP_POWT_HW_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_hw_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < MWXSW_SP_POWT_HW_WFC_2863_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_hw_wfc_2863_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < MWXSW_SP_POWT_HW_WFC_2819_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_hw_wfc_2819_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < MWXSW_SP_POWT_HW_WFC_3635_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_hw_wfc_3635_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < MWXSW_SP_POWT_HW_EXT_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_hw_ext_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < MWXSW_SP_POWT_HW_DISCAWD_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_hw_discawd_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}

		fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			mwxsw_sp_powt_get_pwio_stwings(&p, i);

		fow (i = 0; i < TC_MAX_QUEUE; i++)
			mwxsw_sp_powt_get_tc_stwings(&p, i);

		mwxsw_sp_powt->mwxsw_sp->ptp_ops->get_stats_stwings(&p);

		fow (i = 0; i < MWXSW_SP_POWT_HW_TWANSCEIVEW_STATS_WEN; i++) {
			memcpy(p, mwxsw_sp_powt_twansceivew_stats[i].stw,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static int mwxsw_sp_powt_set_phys_id(stwuct net_device *dev,
				     enum ethtoow_phys_id_state state)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw mwcw_pw[MWXSW_WEG_MWCW_WEN];
	boow active;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		active = twue;
		bweak;
	case ETHTOOW_ID_INACTIVE:
		active = fawse;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	mwxsw_weg_mwcw_pack(mwcw_pw, mwxsw_sp_powt->wocaw_powt, active);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(mwcw), mwcw_pw);
}

static int
mwxsw_sp_get_hw_stats_by_gwoup(stwuct mwxsw_sp_powt_hw_stats **p_hw_stats,
			       int *p_wen, enum mwxsw_weg_ppcnt_gwp gwp)
{
	switch (gwp) {
	case MWXSW_WEG_PPCNT_IEEE_8023_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_stats;
		*p_wen = MWXSW_SP_POWT_HW_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_WFC_2863_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_wfc_2863_stats;
		*p_wen = MWXSW_SP_POWT_HW_WFC_2863_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_WFC_2819_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_wfc_2819_stats;
		*p_wen = MWXSW_SP_POWT_HW_WFC_2819_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_WFC_3635_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_wfc_3635_stats;
		*p_wen = MWXSW_SP_POWT_HW_WFC_3635_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_EXT_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_ext_stats;
		*p_wen = MWXSW_SP_POWT_HW_EXT_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_DISCAWD_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_discawd_stats;
		*p_wen = MWXSW_SP_POWT_HW_DISCAWD_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_PWIO_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_pwio_stats;
		*p_wen = MWXSW_SP_POWT_HW_PWIO_STATS_WEN;
		bweak;
	case MWXSW_WEG_PPCNT_TC_CNT:
		*p_hw_stats = mwxsw_sp_powt_hw_tc_stats;
		*p_wen = MWXSW_SP_POWT_HW_TC_STATS_WEN;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static void __mwxsw_sp_powt_get_stats(stwuct net_device *dev,
				      enum mwxsw_weg_ppcnt_gwp gwp, int pwio,
				      u64 *data, int data_index)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_powt_hw_stats *hw_stats;
	chaw ppcnt_pw[MWXSW_WEG_PPCNT_WEN];
	int i, wen;
	int eww;

	eww = mwxsw_sp_get_hw_stats_by_gwoup(&hw_stats, &wen, gwp);
	if (eww)
		wetuwn;
	mwxsw_sp_powt_get_stats_waw(dev, gwp, pwio, ppcnt_pw);
	fow (i = 0; i < wen; i++) {
		data[data_index + i] = hw_stats[i].gettew(ppcnt_pw);
		if (!hw_stats[i].cewws_bytes)
			continue;
		data[data_index + i] = mwxsw_sp_cewws_bytes(mwxsw_sp,
							    data[data_index + i]);
	}
}

static void __mwxsw_sp_powt_get_env_stats(stwuct net_device *dev, u64 *data, int data_index,
					  stwuct mwxsw_sp_powt_stats *powt_stats,
					  int wen)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int i;

	fow (i = 0; i < wen; i++)
		data[data_index + i] = powt_stats[i].gettew(mwxsw_sp_powt);
}

static void mwxsw_sp_powt_get_stats(stwuct net_device *dev,
				    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int i, data_index = 0;

	/* IEEE 802.3 Countews */
	__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_IEEE_8023_CNT, 0,
				  data, data_index);
	data_index = MWXSW_SP_POWT_HW_STATS_WEN;

	/* WFC 2863 Countews */
	__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_WFC_2863_CNT, 0,
				  data, data_index);
	data_index += MWXSW_SP_POWT_HW_WFC_2863_STATS_WEN;

	/* WFC 2819 Countews */
	__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_WFC_2819_CNT, 0,
				  data, data_index);
	data_index += MWXSW_SP_POWT_HW_WFC_2819_STATS_WEN;

	/* WFC 3635 Countews */
	__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_WFC_3635_CNT, 0,
				  data, data_index);
	data_index += MWXSW_SP_POWT_HW_WFC_3635_STATS_WEN;

	/* Extended Countews */
	__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_EXT_CNT, 0,
				  data, data_index);
	data_index += MWXSW_SP_POWT_HW_EXT_STATS_WEN;

	/* Discawd Countews */
	__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_DISCAWD_CNT, 0,
				  data, data_index);
	data_index += MWXSW_SP_POWT_HW_DISCAWD_STATS_WEN;

	/* Pew-Pwiowity Countews */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_PWIO_CNT, i,
					  data, data_index);
		data_index += MWXSW_SP_POWT_HW_PWIO_STATS_WEN;
	}

	/* Pew-TC Countews */
	fow (i = 0; i < TC_MAX_QUEUE; i++) {
		__mwxsw_sp_powt_get_stats(dev, MWXSW_WEG_PPCNT_TC_CNT, i,
					  data, data_index);
		data_index += MWXSW_SP_POWT_HW_TC_STATS_WEN;
	}

	/* PTP countews */
	mwxsw_sp_powt->mwxsw_sp->ptp_ops->get_stats(mwxsw_sp_powt,
						    data, data_index);
	data_index += mwxsw_sp_powt->mwxsw_sp->ptp_ops->get_stats_count();

	/* Twansceivew countews */
	__mwxsw_sp_powt_get_env_stats(dev, data, data_index, mwxsw_sp_powt_twansceivew_stats,
				      MWXSW_SP_POWT_HW_TWANSCEIVEW_STATS_WEN);
	data_index += MWXSW_SP_POWT_HW_TWANSCEIVEW_STATS_WEN;
}

static int mwxsw_sp_powt_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		wetuwn MWXSW_SP_POWT_ETHTOOW_STATS_WEN +
			mwxsw_sp_powt->mwxsw_sp->ptp_ops->get_stats_count();
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void
mwxsw_sp_powt_get_wink_suppowted(stwuct mwxsw_sp *mwxsw_sp, u32 eth_pwoto_cap,
				 stwuct ethtoow_wink_ksettings *cmd)
{
	const stwuct mwxsw_sp_powt_type_speed_ops *ops;

	ops = mwxsw_sp->powt_type_speed_ops;

	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Asym_Pause);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Autoneg);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Pause);

	ops->fwom_ptys_suppowted_powt(mwxsw_sp, eth_pwoto_cap, cmd);
	ops->fwom_ptys_wink(mwxsw_sp, eth_pwoto_cap,
			    cmd->wink_modes.suppowted);
}

static void
mwxsw_sp_powt_get_wink_advewtise(stwuct mwxsw_sp *mwxsw_sp,
				 u32 eth_pwoto_admin, boow autoneg,
				 stwuct ethtoow_wink_ksettings *cmd)
{
	const stwuct mwxsw_sp_powt_type_speed_ops *ops;

	ops = mwxsw_sp->powt_type_speed_ops;

	if (!autoneg)
		wetuwn;

	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Autoneg);
	ops->fwom_ptys_wink(mwxsw_sp, eth_pwoto_admin,
			    cmd->wink_modes.advewtising);
}

static u8
mwxsw_sp_powt_connectow_powt(enum mwxsw_weg_ptys_connectow_type connectow_type)
{
	switch (connectow_type) {
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_UNKNOWN_OW_NO_CONNECTOW:
		wetuwn POWT_OTHEW;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_NONE:
		wetuwn POWT_NONE;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_TP:
		wetuwn POWT_TP;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_AUI:
		wetuwn POWT_AUI;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_BNC:
		wetuwn POWT_BNC;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_MII:
		wetuwn POWT_MII;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_FIBWE:
		wetuwn POWT_FIBWE;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_DA:
		wetuwn POWT_DA;
	case MWXSW_WEG_PTYS_CONNECTOW_TYPE_POWT_OTHEW:
		wetuwn POWT_OTHEW;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn POWT_OTHEW;
	}
}

static int mwxsw_sp_powt_ptys_quewy(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    u32 *p_eth_pwoto_cap, u32 *p_eth_pwoto_admin,
				    u32 *p_eth_pwoto_opew, u8 *p_connectow_type)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	const stwuct mwxsw_sp_powt_type_speed_ops *ops;
	chaw ptys_pw[MWXSW_WEG_PTYS_WEN];
	int eww;

	ops = mwxsw_sp->powt_type_speed_ops;

	ops->weg_ptys_eth_pack(mwxsw_sp, ptys_pw, mwxsw_sp_powt->wocaw_powt, 0, fawse);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(ptys), ptys_pw);
	if (eww)
		wetuwn eww;

	ops->weg_ptys_eth_unpack(mwxsw_sp, ptys_pw, p_eth_pwoto_cap, p_eth_pwoto_admin,
				 p_eth_pwoto_opew);
	if (p_connectow_type)
		*p_connectow_type = mwxsw_weg_ptys_connectow_type_get(ptys_pw);
	wetuwn 0;
}

static int mwxsw_sp_powt_get_wink_ksettings(stwuct net_device *dev,
					    stwuct ethtoow_wink_ksettings *cmd)
{
	u32 eth_pwoto_cap, eth_pwoto_admin, eth_pwoto_opew;
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	const stwuct mwxsw_sp_powt_type_speed_ops *ops;
	u8 connectow_type;
	boow autoneg;
	int eww;

	eww = mwxsw_sp_powt_ptys_quewy(mwxsw_sp_powt, &eth_pwoto_cap, &eth_pwoto_admin,
				       &eth_pwoto_opew, &connectow_type);
	if (eww)
		wetuwn eww;

	ops = mwxsw_sp->powt_type_speed_ops;
	autoneg = mwxsw_sp_powt->wink.autoneg;

	mwxsw_sp_powt_get_wink_suppowted(mwxsw_sp, eth_pwoto_cap, cmd);

	mwxsw_sp_powt_get_wink_advewtise(mwxsw_sp, eth_pwoto_admin, autoneg, cmd);

	cmd->base.autoneg = autoneg ? AUTONEG_ENABWE : AUTONEG_DISABWE;
	cmd->base.powt = mwxsw_sp_powt_connectow_powt(connectow_type);
	ops->fwom_ptys_wink_mode(mwxsw_sp, netif_cawwiew_ok(dev),
				 eth_pwoto_opew, cmd);

	wetuwn 0;
}

static int
mwxsw_sp_powt_set_wink_ksettings(stwuct net_device *dev,
				 const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	const stwuct mwxsw_sp_powt_type_speed_ops *ops;
	chaw ptys_pw[MWXSW_WEG_PTYS_WEN];
	u32 eth_pwoto_cap, eth_pwoto_new;
	boow autoneg;
	int eww;

	ops = mwxsw_sp->powt_type_speed_ops;

	ops->weg_ptys_eth_pack(mwxsw_sp, ptys_pw, mwxsw_sp_powt->wocaw_powt,
			       0, fawse);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(ptys), ptys_pw);
	if (eww)
		wetuwn eww;
	ops->weg_ptys_eth_unpack(mwxsw_sp, ptys_pw, &eth_pwoto_cap, NUWW, NUWW);

	autoneg = cmd->base.autoneg == AUTONEG_ENABWE;
	eth_pwoto_new = autoneg ?
		ops->to_ptys_advewt_wink(mwxsw_sp, cmd) :
		ops->to_ptys_speed_wanes(mwxsw_sp, mwxsw_sp_powt->mapping.width,
					 cmd);

	eth_pwoto_new = eth_pwoto_new & eth_pwoto_cap;
	if (!eth_pwoto_new) {
		netdev_eww(dev, "No suppowted speed ow wanes wequested\n");
		wetuwn -EINVAW;
	}

	ops->weg_ptys_eth_pack(mwxsw_sp, ptys_pw, mwxsw_sp_powt->wocaw_powt,
			       eth_pwoto_new, autoneg);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptys), ptys_pw);
	if (eww)
		wetuwn eww;

	mwxsw_sp_powt->wink.autoneg = autoneg;

	if (!netif_wunning(dev))
		wetuwn 0;

	mwxsw_sp_powt_admin_status_set(mwxsw_sp_powt, fawse);
	mwxsw_sp_powt_admin_status_set(mwxsw_sp_powt, twue);

	wetuwn 0;
}

static int mwxsw_sp_get_moduwe_info(stwuct net_device *netdev,
				    stwuct ethtoow_modinfo *modinfo)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(netdev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;

	wetuwn mwxsw_env_get_moduwe_info(netdev, mwxsw_sp->cowe,
					 mwxsw_sp_powt->mapping.swot_index,
					 mwxsw_sp_powt->mapping.moduwe,
					 modinfo);
}

static int mwxsw_sp_get_moduwe_eepwom(stwuct net_device *netdev,
				      stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(netdev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u8 swot_index = mwxsw_sp_powt->mapping.swot_index;
	u8 moduwe = mwxsw_sp_powt->mapping.moduwe;

	wetuwn mwxsw_env_get_moduwe_eepwom(netdev, mwxsw_sp->cowe, swot_index,
					   moduwe, ee, data);
}

static int
mwxsw_sp_get_moduwe_eepwom_by_page(stwuct net_device *dev,
				   const stwuct ethtoow_moduwe_eepwom *page,
				   stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u8 swot_index = mwxsw_sp_powt->mapping.swot_index;
	u8 moduwe = mwxsw_sp_powt->mapping.moduwe;

	wetuwn mwxsw_env_get_moduwe_eepwom_by_page(mwxsw_sp->cowe, swot_index,
						   moduwe, page, extack);
}

static int
mwxsw_sp_get_ts_info(stwuct net_device *netdev, stwuct ethtoow_ts_info *info)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(netdev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;

	wetuwn mwxsw_sp->ptp_ops->get_ts_info(mwxsw_sp, info);
}

static void
mwxsw_sp_get_eth_phy_stats(stwuct net_device *dev,
			   stwuct ethtoow_eth_phy_stats *phy_stats)
{
	chaw ppcnt_pw[MWXSW_WEG_PPCNT_WEN];

	if (mwxsw_sp_powt_get_stats_waw(dev, MWXSW_WEG_PPCNT_IEEE_8023_CNT,
					0, ppcnt_pw))
		wetuwn;

	phy_stats->SymbowEwwowDuwingCawwiew =
		mwxsw_weg_ppcnt_a_symbow_ewwow_duwing_cawwiew_get(ppcnt_pw);
}

static void
mwxsw_sp_get_eth_mac_stats(stwuct net_device *dev,
			   stwuct ethtoow_eth_mac_stats *mac_stats)
{
	chaw ppcnt_pw[MWXSW_WEG_PPCNT_WEN];

	if (mwxsw_sp_powt_get_stats_waw(dev, MWXSW_WEG_PPCNT_IEEE_8023_CNT,
					0, ppcnt_pw))
		wetuwn;

	mac_stats->FwamesTwansmittedOK =
		mwxsw_weg_ppcnt_a_fwames_twansmitted_ok_get(ppcnt_pw);
	mac_stats->FwamesWeceivedOK =
		mwxsw_weg_ppcnt_a_fwames_weceived_ok_get(ppcnt_pw);
	mac_stats->FwameCheckSequenceEwwows =
		mwxsw_weg_ppcnt_a_fwame_check_sequence_ewwows_get(ppcnt_pw);
	mac_stats->AwignmentEwwows =
		mwxsw_weg_ppcnt_a_awignment_ewwows_get(ppcnt_pw);
	mac_stats->OctetsTwansmittedOK =
		mwxsw_weg_ppcnt_a_octets_twansmitted_ok_get(ppcnt_pw);
	mac_stats->OctetsWeceivedOK =
		mwxsw_weg_ppcnt_a_octets_weceived_ok_get(ppcnt_pw);
	mac_stats->MuwticastFwamesXmittedOK =
		mwxsw_weg_ppcnt_a_muwticast_fwames_xmitted_ok_get(ppcnt_pw);
	mac_stats->BwoadcastFwamesXmittedOK =
		mwxsw_weg_ppcnt_a_bwoadcast_fwames_xmitted_ok_get(ppcnt_pw);
	mac_stats->MuwticastFwamesWeceivedOK =
		mwxsw_weg_ppcnt_a_muwticast_fwames_weceived_ok_get(ppcnt_pw);
	mac_stats->BwoadcastFwamesWeceivedOK =
		mwxsw_weg_ppcnt_a_bwoadcast_fwames_weceived_ok_get(ppcnt_pw);
	mac_stats->InWangeWengthEwwows =
		mwxsw_weg_ppcnt_a_in_wange_wength_ewwows_get(ppcnt_pw);
	mac_stats->OutOfWangeWengthFiewd =
		mwxsw_weg_ppcnt_a_out_of_wange_wength_fiewd_get(ppcnt_pw);
	mac_stats->FwameTooWongEwwows =
		mwxsw_weg_ppcnt_a_fwame_too_wong_ewwows_get(ppcnt_pw);
}

static void
mwxsw_sp_get_eth_ctww_stats(stwuct net_device *dev,
			    stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	chaw ppcnt_pw[MWXSW_WEG_PPCNT_WEN];

	if (mwxsw_sp_powt_get_stats_waw(dev, MWXSW_WEG_PPCNT_IEEE_8023_CNT,
					0, ppcnt_pw))
		wetuwn;

	ctww_stats->MACContwowFwamesTwansmitted =
		mwxsw_weg_ppcnt_a_mac_contwow_fwames_twansmitted_get(ppcnt_pw);
	ctww_stats->MACContwowFwamesWeceived =
		mwxsw_weg_ppcnt_a_mac_contwow_fwames_weceived_get(ppcnt_pw);
	ctww_stats->UnsuppowtedOpcodesWeceived =
		mwxsw_weg_ppcnt_a_unsuppowted_opcodes_weceived_get(ppcnt_pw);
}

static const stwuct ethtoow_wmon_hist_wange mwxsw_wmon_wanges[] = {
	{    0,    64 },
	{   65,   127 },
	{  128,   255 },
	{  256,   511 },
	{  512,  1023 },
	{ 1024,  1518 },
	{ 1519,  2047 },
	{ 2048,  4095 },
	{ 4096,  8191 },
	{ 8192, 10239 },
	{}
};

static void
mwxsw_sp_get_wmon_stats(stwuct net_device *dev,
			stwuct ethtoow_wmon_stats *wmon,
			const stwuct ethtoow_wmon_hist_wange **wanges)
{
	chaw ppcnt_pw[MWXSW_WEG_PPCNT_WEN];

	if (mwxsw_sp_powt_get_stats_waw(dev, MWXSW_WEG_PPCNT_WFC_2819_CNT,
					0, ppcnt_pw))
		wetuwn;

	wmon->undewsize_pkts =
		mwxsw_weg_ppcnt_ethew_stats_undewsize_pkts_get(ppcnt_pw);
	wmon->ovewsize_pkts =
		mwxsw_weg_ppcnt_ethew_stats_ovewsize_pkts_get(ppcnt_pw);
	wmon->fwagments =
		mwxsw_weg_ppcnt_ethew_stats_fwagments_get(ppcnt_pw);

	wmon->hist[0] = mwxsw_weg_ppcnt_ethew_stats_pkts64octets_get(ppcnt_pw);
	wmon->hist[1] =
		mwxsw_weg_ppcnt_ethew_stats_pkts65to127octets_get(ppcnt_pw);
	wmon->hist[2] =
		mwxsw_weg_ppcnt_ethew_stats_pkts128to255octets_get(ppcnt_pw);
	wmon->hist[3] =
		mwxsw_weg_ppcnt_ethew_stats_pkts256to511octets_get(ppcnt_pw);
	wmon->hist[4] =
		mwxsw_weg_ppcnt_ethew_stats_pkts512to1023octets_get(ppcnt_pw);
	wmon->hist[5] =
		mwxsw_weg_ppcnt_ethew_stats_pkts1024to1518octets_get(ppcnt_pw);
	wmon->hist[6] =
		mwxsw_weg_ppcnt_ethew_stats_pkts1519to2047octets_get(ppcnt_pw);
	wmon->hist[7] =
		mwxsw_weg_ppcnt_ethew_stats_pkts2048to4095octets_get(ppcnt_pw);
	wmon->hist[8] =
		mwxsw_weg_ppcnt_ethew_stats_pkts4096to8191octets_get(ppcnt_pw);
	wmon->hist[9] =
		mwxsw_weg_ppcnt_ethew_stats_pkts8192to10239octets_get(ppcnt_pw);

	*wanges = mwxsw_wmon_wanges;
}

static int mwxsw_sp_weset(stwuct net_device *dev, u32 *fwags)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u8 swot_index = mwxsw_sp_powt->mapping.swot_index;
	u8 moduwe = mwxsw_sp_powt->mapping.moduwe;

	wetuwn mwxsw_env_weset_moduwe(dev, mwxsw_sp->cowe, swot_index,
				      moduwe, fwags);
}

static int
mwxsw_sp_get_moduwe_powew_mode(stwuct net_device *dev,
			       stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u8 swot_index = mwxsw_sp_powt->mapping.swot_index;
	u8 moduwe = mwxsw_sp_powt->mapping.moduwe;

	wetuwn mwxsw_env_get_moduwe_powew_mode(mwxsw_sp->cowe, swot_index,
					       moduwe, pawams, extack);
}

static int
mwxsw_sp_set_moduwe_powew_mode(stwuct net_device *dev,
			       const stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	u8 swot_index = mwxsw_sp_powt->mapping.swot_index;
	u8 moduwe = mwxsw_sp_powt->mapping.moduwe;

	wetuwn mwxsw_env_set_moduwe_powew_mode(mwxsw_sp->cowe, swot_index,
					       moduwe, pawams->powicy, extack);
}

const stwuct ethtoow_ops mwxsw_sp_powt_ethtoow_ops = {
	.cap_wink_wanes_suppowted	= twue,
	.get_dwvinfo			= mwxsw_sp_powt_get_dwvinfo,
	.get_wink			= ethtoow_op_get_wink,
	.get_wink_ext_state		= mwxsw_sp_powt_get_wink_ext_state,
	.get_pausepawam			= mwxsw_sp_powt_get_pausepawam,
	.set_pausepawam			= mwxsw_sp_powt_set_pausepawam,
	.get_stwings			= mwxsw_sp_powt_get_stwings,
	.set_phys_id			= mwxsw_sp_powt_set_phys_id,
	.get_ethtoow_stats		= mwxsw_sp_powt_get_stats,
	.get_sset_count			= mwxsw_sp_powt_get_sset_count,
	.get_wink_ksettings		= mwxsw_sp_powt_get_wink_ksettings,
	.set_wink_ksettings		= mwxsw_sp_powt_set_wink_ksettings,
	.get_moduwe_info		= mwxsw_sp_get_moduwe_info,
	.get_moduwe_eepwom		= mwxsw_sp_get_moduwe_eepwom,
	.get_moduwe_eepwom_by_page	= mwxsw_sp_get_moduwe_eepwom_by_page,
	.get_ts_info			= mwxsw_sp_get_ts_info,
	.get_eth_phy_stats		= mwxsw_sp_get_eth_phy_stats,
	.get_eth_mac_stats		= mwxsw_sp_get_eth_mac_stats,
	.get_eth_ctww_stats		= mwxsw_sp_get_eth_ctww_stats,
	.get_wmon_stats			= mwxsw_sp_get_wmon_stats,
	.weset				= mwxsw_sp_weset,
	.get_moduwe_powew_mode		= mwxsw_sp_get_moduwe_powew_mode,
	.set_moduwe_powew_mode		= mwxsw_sp_set_moduwe_powew_mode,
};

stwuct mwxsw_sp1_powt_wink_mode {
	enum ethtoow_wink_mode_bit_indices mask_ethtoow;
	u32 mask;
	u32 speed;
};

static const stwuct mwxsw_sp1_powt_wink_mode mwxsw_sp1_powt_wink_mode[] = {
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_100BASE_T,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
		.speed		= SPEED_100,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_SGMII |
				  MWXSW_WEG_PTYS_ETH_SPEED_1000BASE_KX,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
		.speed		= SPEED_1000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_1000BASE_T,
		.mask_ethtoow   = ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
		.speed          = SPEED_1000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_CX4 |
				  MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_KX4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
		.speed		= SPEED_10000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_KW |
				  MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_CW |
				  MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_SW |
				  MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_EW_WW,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
		.speed		= SPEED_10000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_CW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
		.speed		= SPEED_40000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_KW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
		.speed		= SPEED_40000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_SW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
		.speed		= SPEED_40000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_WW4_EW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT,
		.speed		= SPEED_40000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_25GBASE_CW,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
		.speed		= SPEED_25000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_25GBASE_KW,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
		.speed		= SPEED_25000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_25GBASE_SW,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
		.speed		= SPEED_25000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_50GBASE_CW2,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT,
		.speed		= SPEED_50000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_50GBASE_KW2,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT,
		.speed		= SPEED_50000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_50GBASE_SW2,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT,
		.speed		= SPEED_50000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_100GBASE_CW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
		.speed		= SPEED_100000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_100GBASE_SW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
		.speed		= SPEED_100000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_100GBASE_KW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
		.speed		= SPEED_100000,
	},
	{
		.mask		= MWXSW_WEG_PTYS_ETH_SPEED_100GBASE_WW4_EW4,
		.mask_ethtoow	= ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT,
		.speed		= SPEED_100000,
	},
};

#define MWXSW_SP1_POWT_WINK_MODE_WEN AWWAY_SIZE(mwxsw_sp1_powt_wink_mode)

static void
mwxsw_sp1_fwom_ptys_suppowted_powt(stwuct mwxsw_sp *mwxsw_sp,
				   u32 ptys_eth_pwoto,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	if (ptys_eth_pwoto & (MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_CW |
			      MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_SW |
			      MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_CW4 |
			      MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_SW4 |
			      MWXSW_WEG_PTYS_ETH_SPEED_100GBASE_SW4 |
			      MWXSW_WEG_PTYS_ETH_SPEED_SGMII))
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);

	if (ptys_eth_pwoto & (MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_KW |
			      MWXSW_WEG_PTYS_ETH_SPEED_10GBASE_KX4 |
			      MWXSW_WEG_PTYS_ETH_SPEED_40GBASE_KW4 |
			      MWXSW_WEG_PTYS_ETH_SPEED_100GBASE_KW4 |
			      MWXSW_WEG_PTYS_ETH_SPEED_1000BASE_KX))
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Backpwane);
}

static void
mwxsw_sp1_fwom_ptys_wink(stwuct mwxsw_sp *mwxsw_sp, u32 ptys_eth_pwoto,
			 unsigned wong *mode)
{
	int i;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if (ptys_eth_pwoto & mwxsw_sp1_powt_wink_mode[i].mask)
			__set_bit(mwxsw_sp1_powt_wink_mode[i].mask_ethtoow,
				  mode);
	}
}

static u32
mwxsw_sp1_fwom_ptys_speed(stwuct mwxsw_sp *mwxsw_sp, u32 ptys_eth_pwoto)
{
	int i;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if (ptys_eth_pwoto & mwxsw_sp1_powt_wink_mode[i].mask)
			wetuwn mwxsw_sp1_powt_wink_mode[i].speed;
	}

	wetuwn SPEED_UNKNOWN;
}

static void
mwxsw_sp1_fwom_ptys_wink_mode(stwuct mwxsw_sp *mwxsw_sp, boow cawwiew_ok,
			      u32 ptys_eth_pwoto,
			      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct mwxsw_sp1_powt_wink_mode wink;
	int i;

	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.dupwex = DUPWEX_UNKNOWN;
	cmd->wanes = 0;

	if (!cawwiew_ok)
		wetuwn;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if (ptys_eth_pwoto & mwxsw_sp1_powt_wink_mode[i].mask) {
			wink = mwxsw_sp1_powt_wink_mode[i];
			ethtoow_pawams_fwom_wink_mode(cmd,
						      wink.mask_ethtoow);
		}
	}
}

static int mwxsw_sp1_ptys_max_speed(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 *p_max_speed)
{
	u32 eth_pwoto_cap;
	u32 max_speed = 0;
	int eww;
	int i;

	eww = mwxsw_sp_powt_ptys_quewy(mwxsw_sp_powt, &eth_pwoto_cap, NUWW, NUWW, NUWW);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if ((eth_pwoto_cap & mwxsw_sp1_powt_wink_mode[i].mask) &&
		    mwxsw_sp1_powt_wink_mode[i].speed > max_speed)
			max_speed = mwxsw_sp1_powt_wink_mode[i].speed;
	}

	*p_max_speed = max_speed;
	wetuwn 0;
}

static u32
mwxsw_sp1_to_ptys_advewt_wink(stwuct mwxsw_sp *mwxsw_sp,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	u32 ptys_pwoto = 0;
	int i;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if (test_bit(mwxsw_sp1_powt_wink_mode[i].mask_ethtoow,
			     cmd->wink_modes.advewtising))
			ptys_pwoto |= mwxsw_sp1_powt_wink_mode[i].mask;
	}
	wetuwn ptys_pwoto;
}

static u32 mwxsw_sp1_to_ptys_speed_wanes(stwuct mwxsw_sp *mwxsw_sp, u8 width,
					 const stwuct ethtoow_wink_ksettings *cmd)
{
	u32 ptys_pwoto = 0;
	int i;

	if (cmd->wanes > width)
		wetuwn ptys_pwoto;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if (cmd->base.speed == mwxsw_sp1_powt_wink_mode[i].speed)
			ptys_pwoto |= mwxsw_sp1_powt_wink_mode[i].mask;
	}
	wetuwn ptys_pwoto;
}

static void
mwxsw_sp1_weg_ptys_eth_pack(stwuct mwxsw_sp *mwxsw_sp, chaw *paywoad,
			    u16 wocaw_powt, u32 pwoto_admin, boow autoneg)
{
	mwxsw_weg_ptys_eth_pack(paywoad, wocaw_powt, pwoto_admin, autoneg);
}

static void
mwxsw_sp1_weg_ptys_eth_unpack(stwuct mwxsw_sp *mwxsw_sp, chaw *paywoad,
			      u32 *p_eth_pwoto_cap, u32 *p_eth_pwoto_admin,
			      u32 *p_eth_pwoto_opew)
{
	mwxsw_weg_ptys_eth_unpack(paywoad, p_eth_pwoto_cap, p_eth_pwoto_admin,
				  p_eth_pwoto_opew);
}

static u32 mwxsw_sp1_ptys_pwoto_cap_masked_get(u32 eth_pwoto_cap)
{
	u32 ptys_pwoto_cap_masked = 0;
	int i;

	fow (i = 0; i < MWXSW_SP1_POWT_WINK_MODE_WEN; i++) {
		if (mwxsw_sp1_powt_wink_mode[i].mask & eth_pwoto_cap)
			ptys_pwoto_cap_masked |=
				mwxsw_sp1_powt_wink_mode[i].mask;
	}

	wetuwn ptys_pwoto_cap_masked;
}

const stwuct mwxsw_sp_powt_type_speed_ops mwxsw_sp1_powt_type_speed_ops = {
	.fwom_ptys_suppowted_powt	= mwxsw_sp1_fwom_ptys_suppowted_powt,
	.fwom_ptys_wink			= mwxsw_sp1_fwom_ptys_wink,
	.fwom_ptys_speed		= mwxsw_sp1_fwom_ptys_speed,
	.fwom_ptys_wink_mode		= mwxsw_sp1_fwom_ptys_wink_mode,
	.ptys_max_speed			= mwxsw_sp1_ptys_max_speed,
	.to_ptys_advewt_wink		= mwxsw_sp1_to_ptys_advewt_wink,
	.to_ptys_speed_wanes		= mwxsw_sp1_to_ptys_speed_wanes,
	.weg_ptys_eth_pack		= mwxsw_sp1_weg_ptys_eth_pack,
	.weg_ptys_eth_unpack		= mwxsw_sp1_weg_ptys_eth_unpack,
	.ptys_pwoto_cap_masked_get	= mwxsw_sp1_ptys_pwoto_cap_masked_get,
};

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_sgmii_100m[] = {
	ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_SGMII_100M_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_sgmii_100m)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_1000base_x_sgmii[] = {
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_1000BASE_X_SGMII_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_1000base_x_sgmii)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_5gbase_w[] = {
	ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_5GBASE_W_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_5gbase_w)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_xfi_xaui_1_10g[] = {
	ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseW_FEC_BIT,
	ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_XFI_XAUI_1_10G_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_xfi_xaui_1_10g)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_xwaui_4_xwppi_4_40g[] = {
	ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_XWAUI_4_XWPPI_4_40G_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_xwaui_4_xwppi_4_40g)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_25gaui_1_25gbase_cw_kw[] = {
	ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_25GAUI_1_25GBASE_CW_KW_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_25gaui_1_25gbase_cw_kw)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_50gaui_2_waui_2_50gbase_cw2_kw2[] = {
	ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_50GAUI_2_WAUI_2_50GBASE_CW2_KW2_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_50gaui_2_waui_2_50gbase_cw2_kw2)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_50gaui_1_waui_1_50gbase_cw_kw[] = {
	ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseSW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseDW_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_50GAUI_1_WAUI_1_50GBASE_CW_KW_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_50gaui_1_waui_1_50gbase_cw_kw)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_caui_4_100gbase_cw4_kw4[] = {
	ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_CAUI_4_100GBASE_CW4_KW4_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_caui_4_100gbase_cw4_kw4)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_100gaui_2_100gbase_cw2_kw2[] = {
	ETHTOOW_WINK_MODE_100000baseKW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseSW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseCW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseWW2_EW2_FW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseDW2_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_100GAUI_2_100GBASE_CW2_KW2_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_100gaui_2_100gbase_cw2_kw2)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_200gaui_4_200gbase_cw4_kw4[] = {
	ETHTOOW_WINK_MODE_200000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_200000baseSW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_200000baseWW4_EW4_FW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_200000baseDW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_200000baseCW4_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_200GAUI_4_200GBASE_CW4_KW4_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_200gaui_4_200gbase_cw4_kw4)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_400gaui_8[] = {
	ETHTOOW_WINK_MODE_400000baseKW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_400000baseSW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_400000baseWW8_EW8_FW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_400000baseDW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_400000baseCW8_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_400GAUI_8_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_400gaui_8)

static const enum ethtoow_wink_mode_bit_indices
mwxsw_sp2_mask_ethtoow_800gaui_8[] = {
	ETHTOOW_WINK_MODE_800000baseCW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_800000baseKW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_800000baseDW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_800000baseDW8_2_Fuww_BIT,
	ETHTOOW_WINK_MODE_800000baseSW8_Fuww_BIT,
	ETHTOOW_WINK_MODE_800000baseVW8_Fuww_BIT,
};

#define MWXSW_SP2_MASK_ETHTOOW_800GAUI_8_WEN \
	AWWAY_SIZE(mwxsw_sp2_mask_ethtoow_800gaui_8)

#define MWXSW_SP_POWT_MASK_WIDTH_1X	BIT(0)
#define MWXSW_SP_POWT_MASK_WIDTH_2X	BIT(1)
#define MWXSW_SP_POWT_MASK_WIDTH_4X	BIT(2)
#define MWXSW_SP_POWT_MASK_WIDTH_8X	BIT(3)

static u8 mwxsw_sp_powt_mask_width_get(u8 width)
{
	switch (width) {
	case 1:
		wetuwn MWXSW_SP_POWT_MASK_WIDTH_1X;
	case 2:
		wetuwn MWXSW_SP_POWT_MASK_WIDTH_2X;
	case 4:
		wetuwn MWXSW_SP_POWT_MASK_WIDTH_4X;
	case 8:
		wetuwn MWXSW_SP_POWT_MASK_WIDTH_8X;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

stwuct mwxsw_sp2_powt_wink_mode {
	const enum ethtoow_wink_mode_bit_indices *mask_ethtoow;
	int m_ethtoow_wen;
	u32 mask;
	u32 speed;
	u32 width;
	u8 mask_sup_width;
};

static const stwuct mwxsw_sp2_powt_wink_mode mwxsw_sp2_powt_wink_mode[] = {
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_SGMII_100M,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_sgmii_100m,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_SGMII_100M_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_1X |
				  MWXSW_SP_POWT_MASK_WIDTH_2X |
				  MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_100,
		.width		= 1,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_1000BASE_X_SGMII,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_1000base_x_sgmii,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_1000BASE_X_SGMII_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_1X |
				  MWXSW_SP_POWT_MASK_WIDTH_2X |
				  MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_1000,
		.width		= 1,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_5GBASE_W,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_5gbase_w,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_5GBASE_W_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_1X |
				  MWXSW_SP_POWT_MASK_WIDTH_2X |
				  MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_5000,
		.width		= 1,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_XFI_XAUI_1_10G,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_xfi_xaui_1_10g,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_XFI_XAUI_1_10G_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_1X |
				  MWXSW_SP_POWT_MASK_WIDTH_2X |
				  MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_10000,
		.width		= 1,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_XWAUI_4_XWPPI_4_40G,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_xwaui_4_xwppi_4_40g,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_XWAUI_4_XWPPI_4_40G_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_40000,
		.width		= 4,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_25GAUI_1_25GBASE_CW_KW,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_25gaui_1_25gbase_cw_kw,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_25GAUI_1_25GBASE_CW_KW_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_1X |
				  MWXSW_SP_POWT_MASK_WIDTH_2X |
				  MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_25000,
		.width		= 1,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_50GAUI_2_WAUI_2_50GBASE_CW2_KW2,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_50gaui_2_waui_2_50gbase_cw2_kw2,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_50GAUI_2_WAUI_2_50GBASE_CW2_KW2_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_2X |
				  MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_50000,
		.width		= 2,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_50GAUI_1_WAUI_1_50GBASE_CW_KW,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_50gaui_1_waui_1_50gbase_cw_kw,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_50GAUI_1_WAUI_1_50GBASE_CW_KW_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_1X,
		.speed		= SPEED_50000,
		.width		= 1,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_CAUI_4_100GBASE_CW4_KW4,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_caui_4_100gbase_cw4_kw4,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_CAUI_4_100GBASE_CW4_KW4_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_100000,
		.width		= 4,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_100GAUI_2_100GBASE_CW2_KW2,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_100gaui_2_100gbase_cw2_kw2,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_100GAUI_2_100GBASE_CW2_KW2_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_2X,
		.speed		= SPEED_100000,
		.width		= 2,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_200GAUI_4_200GBASE_CW4_KW4,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_200gaui_4_200gbase_cw4_kw4,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_200GAUI_4_200GBASE_CW4_KW4_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_4X |
				  MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_200000,
		.width		= 4,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_400GAUI_8,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_400gaui_8,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_400GAUI_8_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_400000,
		.width		= 8,
	},
	{
		.mask		= MWXSW_WEG_PTYS_EXT_ETH_SPEED_800GAUI_8,
		.mask_ethtoow	= mwxsw_sp2_mask_ethtoow_800gaui_8,
		.m_ethtoow_wen	= MWXSW_SP2_MASK_ETHTOOW_800GAUI_8_WEN,
		.mask_sup_width	= MWXSW_SP_POWT_MASK_WIDTH_8X,
		.speed		= SPEED_800000,
		.width		= 8,
	},
};

#define MWXSW_SP2_POWT_WINK_MODE_WEN AWWAY_SIZE(mwxsw_sp2_powt_wink_mode)

static void
mwxsw_sp2_fwom_ptys_suppowted_powt(stwuct mwxsw_sp *mwxsw_sp,
				   u32 ptys_eth_pwoto,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);
	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Backpwane);
}

static void
mwxsw_sp2_set_bit_ethtoow(const stwuct mwxsw_sp2_powt_wink_mode *wink_mode,
			  unsigned wong *mode)
{
	int i;

	fow (i = 0; i < wink_mode->m_ethtoow_wen; i++)
		__set_bit(wink_mode->mask_ethtoow[i], mode);
}

static void
mwxsw_sp2_fwom_ptys_wink(stwuct mwxsw_sp *mwxsw_sp, u32 ptys_eth_pwoto,
			 unsigned wong *mode)
{
	int i;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if (ptys_eth_pwoto & mwxsw_sp2_powt_wink_mode[i].mask)
			mwxsw_sp2_set_bit_ethtoow(&mwxsw_sp2_powt_wink_mode[i],
						  mode);
	}
}

static u32
mwxsw_sp2_fwom_ptys_speed(stwuct mwxsw_sp *mwxsw_sp, u32 ptys_eth_pwoto)
{
	int i;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if (ptys_eth_pwoto & mwxsw_sp2_powt_wink_mode[i].mask)
			wetuwn mwxsw_sp2_powt_wink_mode[i].speed;
	}

	wetuwn SPEED_UNKNOWN;
}

static void
mwxsw_sp2_fwom_ptys_wink_mode(stwuct mwxsw_sp *mwxsw_sp, boow cawwiew_ok,
			      u32 ptys_eth_pwoto,
			      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct mwxsw_sp2_powt_wink_mode wink;
	int i;

	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.dupwex = DUPWEX_UNKNOWN;
	cmd->wanes = 0;

	if (!cawwiew_ok)
		wetuwn;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if (ptys_eth_pwoto & mwxsw_sp2_powt_wink_mode[i].mask) {
			wink = mwxsw_sp2_powt_wink_mode[i];
			ethtoow_pawams_fwom_wink_mode(cmd,
						      wink.mask_ethtoow[1]);
		}
	}
}

static int mwxsw_sp2_ptys_max_speed(stwuct mwxsw_sp_powt *mwxsw_sp_powt, u32 *p_max_speed)
{
	u32 eth_pwoto_cap;
	u32 max_speed = 0;
	int eww;
	int i;

	eww = mwxsw_sp_powt_ptys_quewy(mwxsw_sp_powt, &eth_pwoto_cap, NUWW, NUWW, NUWW);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if ((eth_pwoto_cap & mwxsw_sp2_powt_wink_mode[i].mask) &&
		    mwxsw_sp2_powt_wink_mode[i].speed > max_speed)
			max_speed = mwxsw_sp2_powt_wink_mode[i].speed;
	}

	*p_max_speed = max_speed;
	wetuwn 0;
}

static boow
mwxsw_sp2_test_bit_ethtoow(const stwuct mwxsw_sp2_powt_wink_mode *wink_mode,
			   const unsigned wong *mode)
{
	int cnt = 0;
	int i;

	fow (i = 0; i < wink_mode->m_ethtoow_wen; i++) {
		if (test_bit(wink_mode->mask_ethtoow[i], mode))
			cnt++;
	}

	wetuwn cnt == wink_mode->m_ethtoow_wen;
}

static u32
mwxsw_sp2_to_ptys_advewt_wink(stwuct mwxsw_sp *mwxsw_sp,
			      const stwuct ethtoow_wink_ksettings *cmd)
{
	u32 ptys_pwoto = 0;
	int i;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if (mwxsw_sp2_test_bit_ethtoow(&mwxsw_sp2_powt_wink_mode[i],
					       cmd->wink_modes.advewtising))
			ptys_pwoto |= mwxsw_sp2_powt_wink_mode[i].mask;
	}
	wetuwn ptys_pwoto;
}

static u32 mwxsw_sp2_to_ptys_speed_wanes(stwuct mwxsw_sp *mwxsw_sp, u8 width,
					 const stwuct ethtoow_wink_ksettings *cmd)
{
	u8 mask_width = mwxsw_sp_powt_mask_width_get(width);
	stwuct mwxsw_sp2_powt_wink_mode wink_mode;
	u32 ptys_pwoto = 0;
	int i;

	if (cmd->wanes > width)
		wetuwn ptys_pwoto;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if (cmd->base.speed == mwxsw_sp2_powt_wink_mode[i].speed) {
			wink_mode = mwxsw_sp2_powt_wink_mode[i];

			if (!cmd->wanes) {
				/* If numbew of wanes was not set by usew space,
				 * choose the wink mode that suppowts the width
				 * of the powt.
				 */
				if (mask_width & wink_mode.mask_sup_width)
					ptys_pwoto |= wink_mode.mask;
			} ewse if (cmd->wanes == wink_mode.width) {
				/* Ewse if the numbew of wanes was set, choose
				 * the wink mode that its actuaw width equaws to
				 * it.
				 */
				ptys_pwoto |= wink_mode.mask;
			}
		}
	}
	wetuwn ptys_pwoto;
}

static void
mwxsw_sp2_weg_ptys_eth_pack(stwuct mwxsw_sp *mwxsw_sp, chaw *paywoad,
			    u16 wocaw_powt, u32 pwoto_admin,
			    boow autoneg)
{
	mwxsw_weg_ptys_ext_eth_pack(paywoad, wocaw_powt, pwoto_admin, autoneg);
}

static void
mwxsw_sp2_weg_ptys_eth_unpack(stwuct mwxsw_sp *mwxsw_sp, chaw *paywoad,
			      u32 *p_eth_pwoto_cap, u32 *p_eth_pwoto_admin,
			      u32 *p_eth_pwoto_opew)
{
	mwxsw_weg_ptys_ext_eth_unpack(paywoad, p_eth_pwoto_cap,
				      p_eth_pwoto_admin, p_eth_pwoto_opew);
}

static u32 mwxsw_sp2_ptys_pwoto_cap_masked_get(u32 eth_pwoto_cap)
{
	u32 ptys_pwoto_cap_masked = 0;
	int i;

	fow (i = 0; i < MWXSW_SP2_POWT_WINK_MODE_WEN; i++) {
		if (mwxsw_sp2_powt_wink_mode[i].mask & eth_pwoto_cap)
			ptys_pwoto_cap_masked |=
				mwxsw_sp2_powt_wink_mode[i].mask;
	}

	wetuwn ptys_pwoto_cap_masked;
}

const stwuct mwxsw_sp_powt_type_speed_ops mwxsw_sp2_powt_type_speed_ops = {
	.fwom_ptys_suppowted_powt	= mwxsw_sp2_fwom_ptys_suppowted_powt,
	.fwom_ptys_wink			= mwxsw_sp2_fwom_ptys_wink,
	.fwom_ptys_speed		= mwxsw_sp2_fwom_ptys_speed,
	.fwom_ptys_wink_mode		= mwxsw_sp2_fwom_ptys_wink_mode,
	.ptys_max_speed			= mwxsw_sp2_ptys_max_speed,
	.to_ptys_advewt_wink		= mwxsw_sp2_to_ptys_advewt_wink,
	.to_ptys_speed_wanes		= mwxsw_sp2_to_ptys_speed_wanes,
	.weg_ptys_eth_pack		= mwxsw_sp2_weg_ptys_eth_pack,
	.weg_ptys_eth_unpack		= mwxsw_sp2_weg_ptys_eth_unpack,
	.ptys_pwoto_cap_masked_get	= mwxsw_sp2_ptys_pwoto_cap_masked_get,
};
