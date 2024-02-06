/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: 802.11ac
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_11AC_H_
#define _MWIFIEX_11AC_H_

#define VHT_CFG_2GHZ BIT(0)
#define VHT_CFG_5GHZ BIT(1)

enum vht_cfg_misc_config {
	VHT_CAP_TX_OPEWATION = 1,
	VHT_CAP_ASSOCIATION,
	VHT_CAP_UAP_ONWY
};

#define DEFAUWT_VHT_MCS_SET 0xfffa
#define DISABWE_VHT_MCS_SET 0xffff

#define VHT_BW_80_160_80P80 BIT(2)

int mwifiex_cmd_append_11ac_twv(stwuct mwifiex_pwivate *pwiv,
				stwuct mwifiex_bssdescwiptow *bss_desc,
				u8 **buffew);
int mwifiex_cmd_11ac_cfg(stwuct mwifiex_pwivate *pwiv,
			 stwuct host_cmd_ds_command *cmd, u16 cmd_action,
			 stwuct mwifiex_11ac_vht_cfg *cfg);
void mwifiex_fiww_vht_cap_twv(stwuct mwifiex_pwivate *pwiv,
			      stwuct ieee80211_vht_cap *vht_cap, u8 bands);
#endif /* _MWIFIEX_11AC_H_ */
