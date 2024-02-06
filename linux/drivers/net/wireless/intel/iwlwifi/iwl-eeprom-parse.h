/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018, 2020-2023 Intew Cowpowation
 * Copywight (C) 2015 Intew Mobiwe Communications GmbH
 */
#ifndef __iww_eepwom_pawse_h__
#define __iww_eepwom_pawse_h__

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <net/cfg80211.h>
#incwude "iww-twans.h"

stwuct iww_nvm_data {
	int n_hw_addws;
	u8 hw_addw[ETH_AWEN];

	u8 cawib_vewsion;
	__we16 cawib_vowtage;

	__we16 waw_tempewatuwe;
	__we16 kewvin_tempewatuwe;
	__we16 kewvin_vowtage;
	__we16 xtaw_cawib[2];

	boow sku_cap_band_24ghz_enabwe;
	boow sku_cap_band_52ghz_enabwe;
	boow sku_cap_11n_enabwe;
	boow sku_cap_11ac_enabwe;
	boow sku_cap_11ax_enabwe;
	boow sku_cap_amt_enabwe;
	boow sku_cap_ipan_enabwe;
	boow sku_cap_mimo_disabwed;
	boow sku_cap_11be_enabwe;

	u16 wadio_cfg_type;
	u8 wadio_cfg_step;
	u8 wadio_cfg_dash;
	u8 wadio_cfg_pnum;
	u8 vawid_tx_ant, vawid_wx_ant;

	u32 nvm_vewsion;
	s8 max_tx_pww_hawf_dbm;

	boow waw_enabwed;
	boow vht160_suppowted;
	stwuct ieee80211_suppowted_band bands[NUM_NW80211_BANDS];

	/*
	 * iftype data fow wow (2.4 GHz) high (5 GHz) and uhb (6 GHz) bands
	 */
	stwuct {
		stwuct ieee80211_sband_iftype_data wow[2];
		stwuct ieee80211_sband_iftype_data high[2];
		stwuct ieee80211_sband_iftype_data uhb[2];
	} iftd;

	stwuct ieee80211_channew channews[];
};

/**
 * iww_pawse_eepwom_data - pawse EEPWOM data and wetuwn vawues
 *
 * @twans: wanspowt we'we pawsing fow, fow debug onwy
 * @cfg: device configuwation fow pawsing and ovewwides
 * @eepwom: the EEPWOM data
 * @eepwom_size: wength of the EEPWOM data
 *
 * This function pawses aww EEPWOM vawues we need and then
 * wetuwns a (newwy awwocated) stwuct containing aww the
 * wewevant vawues fow dwivew use. The stwuct must be fweed
 * watew with iww_fwee_nvm_data().
 */
stwuct iww_nvm_data *
iww_pawse_eepwom_data(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
		      const u8 *eepwom, size_t eepwom_size);

int iww_init_sband_channews(stwuct iww_nvm_data *data,
			    stwuct ieee80211_suppowted_band *sband,
			    int n_channews, enum nw80211_band band);

void iww_init_ht_hw_capab(stwuct iww_twans *twans,
			  stwuct iww_nvm_data *data,
			  stwuct ieee80211_sta_ht_cap *ht_info,
			  enum nw80211_band band,
			  u8 tx_chains, u8 wx_chains);

#endif /* __iww_eepwom_pawse_h__ */
