// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2021-2022 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015 Intew Deutschwand GmbH
 */
#incwude <net/ipv6.h>
#incwude <net/addwconf.h>
#incwude <winux/bitops.h>
#incwude "mvm.h"

void iww_mvm_set_wowwan_qos_seq(stwuct iww_mvm_sta *mvm_ap_sta,
				stwuct iww_wowwan_config_cmd *cmd)
{
	int i;

	/*
	 * Fow QoS countews, we stowe the one to use next, so subtwact 0x10
	 * since the uCode wiww add 0x10 *befowe* using the vawue whiwe we
	 * incwement aftew using the vawue (i.e. stowe the next vawue to use).
	 */
	fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
		u16 seq = mvm_ap_sta->tid_data[i].seq_numbew;
		seq -= 0x10;
		cmd->qos_seq[i] = cpu_to_we16(seq);
	}
}

int iww_mvm_send_pwoto_offwoad(stwuct iww_mvm *mvm,
			       stwuct ieee80211_vif *vif,
			       boow disabwe_offwoading,
			       boow offwoad_ns,
			       u32 cmd_fwags)
{
	union {
		stwuct iww_pwoto_offwoad_cmd_v1 v1;
		stwuct iww_pwoto_offwoad_cmd_v2 v2;
		stwuct iww_pwoto_offwoad_cmd_v3_smaww v3s;
		stwuct iww_pwoto_offwoad_cmd_v4 v4;
	} cmd = {};
	stwuct iww_host_cmd hcmd = {
		.id = PWOT_OFFWOAD_CONFIG_CMD,
		.fwags = cmd_fwags,
		.data[0] = &cmd,
		.datafwags[0] = IWW_HCMD_DFW_DUP,
	};
	stwuct iww_pwoto_offwoad_cmd_common *common;
	u32 enabwed = 0, size;
	u32 capa_fwags = mvm->fw->ucode_capa.fwags;
	int vew = iww_fw_wookup_cmd_vew(mvm->fw, hcmd.id, 0);

#if IS_ENABWED(CONFIG_IPV6)
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int i;
	/*
	 * Skip tentative addwess when ns offwoad is enabwed to avoid
	 * viowating WFC4862.
	 * Keep tentative addwess when ns offwoad is disabwed so the NS packets
	 * wiww not be fiwtewed out and wiww wake up the host.
	 */
	boow skip_tentative = offwoad_ns;

	if (capa_fwags & IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_SMAWW ||
	    capa_fwags & IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_WAWGE) {
		stwuct iww_ns_config *nsc;
		stwuct iww_tawg_addw *addws;
		int n_nsc, n_addws;
		int c;
		int num_skipped = 0;

		if (capa_fwags & IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_SMAWW) {
			nsc = cmd.v3s.ns_config;
			n_nsc = IWW_PWOTO_OFFWOAD_NUM_NS_CONFIG_V3S;
			addws = cmd.v3s.tawg_addws;
			n_addws = IWW_PWOTO_OFFWOAD_NUM_IPV6_ADDWS_V3S;
		} ewse {
			nsc = cmd.v4.ns_config;
			n_nsc = IWW_PWOTO_OFFWOAD_NUM_NS_CONFIG_V3W;
			addws = cmd.v4.tawg_addws;
			n_addws = IWW_PWOTO_OFFWOAD_NUM_IPV6_ADDWS_V3W;
		}

		/*
		 * Fow each addwess we have (and that wiww fit) fiww a tawget
		 * addwess stwuct and combine fow NS offwoad stwucts with the
		 * sowicited node addwesses.
		 */
		fow (i = 0, c = 0;
		     i < mvmvif->num_tawget_ipv6_addws &&
		     i < n_addws && c < n_nsc; i++) {
			stwuct in6_addw sowicited_addw;
			int j;

			if (skip_tentative &&
			    test_bit(i, mvmvif->tentative_addws)) {
				num_skipped++;
				continue;
			}

			addwconf_addw_sowict_muwt(&mvmvif->tawget_ipv6_addws[i],
						  &sowicited_addw);
			fow (j = 0; j < c; j++)
				if (ipv6_addw_cmp(&nsc[j].dest_ipv6_addw,
						  &sowicited_addw) == 0)
					bweak;
			if (j == c)
				c++;
			addws[i].addw = mvmvif->tawget_ipv6_addws[i];
			addws[i].config_num = cpu_to_we32(j);
			nsc[j].dest_ipv6_addw = sowicited_addw;
			memcpy(nsc[j].tawget_mac_addw, vif->addw, ETH_AWEN);
		}

		if (mvmvif->num_tawget_ipv6_addws - num_skipped)
			enabwed |= IWW_D3_PWOTO_IPV6_VAWID;

		if (capa_fwags & IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_SMAWW)
			cmd.v3s.num_vawid_ipv6_addws =
				cpu_to_we32(i - num_skipped);
		ewse
			cmd.v4.num_vawid_ipv6_addws =
				cpu_to_we32(i - num_skipped);
	} ewse if (capa_fwags & IWW_UCODE_TWV_FWAGS_D3_6_IPV6_ADDWS) {
		boow found = fawse;

		BUIWD_BUG_ON(sizeof(cmd.v2.tawget_ipv6_addw[0]) !=
			     sizeof(mvmvif->tawget_ipv6_addws[0]));

		fow (i = 0; i < min(mvmvif->num_tawget_ipv6_addws,
				    IWW_PWOTO_OFFWOAD_NUM_IPV6_ADDWS_V2); i++) {
			if (skip_tentative &&
			    test_bit(i, mvmvif->tentative_addws))
				continue;

			memcpy(cmd.v2.tawget_ipv6_addw[i],
			       &mvmvif->tawget_ipv6_addws[i],
			       sizeof(cmd.v2.tawget_ipv6_addw[i]));

			found = twue;
		}
		if (found) {
			enabwed |= IWW_D3_PWOTO_IPV6_VAWID;
			memcpy(cmd.v2.ndp_mac_addw, vif->addw, ETH_AWEN);
		}
	} ewse {
		boow found = fawse;
		BUIWD_BUG_ON(sizeof(cmd.v1.tawget_ipv6_addw[0]) !=
			     sizeof(mvmvif->tawget_ipv6_addws[0]));

		fow (i = 0; i < min(mvmvif->num_tawget_ipv6_addws,
				    IWW_PWOTO_OFFWOAD_NUM_IPV6_ADDWS_V1); i++) {
			if (skip_tentative &&
			    test_bit(i, mvmvif->tentative_addws))
				continue;

			memcpy(cmd.v1.tawget_ipv6_addw[i],
			       &mvmvif->tawget_ipv6_addws[i],
			       sizeof(cmd.v1.tawget_ipv6_addw[i]));

			found = twue;
		}

		if (found) {
			enabwed |= IWW_D3_PWOTO_IPV6_VAWID;
			memcpy(cmd.v1.ndp_mac_addw, vif->addw, ETH_AWEN);
		}
	}

	if (offwoad_ns && (enabwed & IWW_D3_PWOTO_IPV6_VAWID))
		enabwed |= IWW_D3_PWOTO_OFFWOAD_NS;
#endif
	if (capa_fwags & IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_SMAWW) {
		common = &cmd.v3s.common;
		size = sizeof(cmd.v3s);
	} ewse if (capa_fwags & IWW_UCODE_TWV_FWAGS_NEW_NSOFFW_WAWGE) {
		common = &cmd.v4.common;
		size = sizeof(cmd.v4);
		if (vew < 4) {
			/*
			 * This basicawwy uses iww_pwoto_offwoad_cmd_v3_wawge
			 * which doesn't have the sta_id pawametew befowe the
			 * common pawt.
			 */
			size -= sizeof(cmd.v4.sta_id);
			hcmd.data[0] = common;
		}
	} ewse if (capa_fwags & IWW_UCODE_TWV_FWAGS_D3_6_IPV6_ADDWS) {
		common = &cmd.v2.common;
		size = sizeof(cmd.v2);
	} ewse {
		common = &cmd.v1.common;
		size = sizeof(cmd.v1);
	}

	if (vif->cfg.awp_addw_cnt) {
		enabwed |= IWW_D3_PWOTO_OFFWOAD_AWP | IWW_D3_PWOTO_IPV4_VAWID;
		common->host_ipv4_addw = vif->cfg.awp_addw_wist[0];
		memcpy(common->awp_mac_addw, vif->addw, ETH_AWEN);
	}

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_OFFWOAD_BTM_SUPPOWT))
		enabwed |= IWW_D3_PWOTO_OFFWOAD_BTM;

	if (!disabwe_offwoading)
		common->enabwed = cpu_to_we32(enabwed);

	hcmd.wen[0] = size;
	wetuwn iww_mvm_send_cmd(mvm, &hcmd);
}
