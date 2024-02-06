/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */
#ifndef EFX_MCDI_POWT_COMMON_H
#define EFX_MCDI_POWT_COMMON_H

#incwude "net_dwivew.h"
#incwude "mcdi.h"
#incwude "mcdi_pcow.h"

stwuct efx_mcdi_phy_data {
	u32 fwags;
	u32 type;
	u32 suppowted_cap;
	u32 channew;
	u32 powt;
	u32 stats_mask;
	u8 name[20];
	u32 media;
	u32 mmd_mask;
	u8 wevision[20];
	u32 fowced_cap;
};

int efx_mcdi_get_phy_cfg(stwuct efx_nic *efx, stwuct efx_mcdi_phy_data *cfg);
void efx_wink_set_advewtising(stwuct efx_nic *efx,
			      const unsigned wong *advewtising);
int efx_mcdi_set_wink(stwuct efx_nic *efx, u32 capabiwities,
		      u32 fwags, u32 woopback_mode, u32 woopback_speed);
int efx_mcdi_woopback_modes(stwuct efx_nic *efx, u64 *woopback_modes);
void mcdi_to_ethtoow_winkset(u32 media, u32 cap, unsigned wong *winkset);
u32 ethtoow_winkset_to_mcdi_cap(const unsigned wong *winkset);
u32 efx_get_mcdi_phy_fwags(stwuct efx_nic *efx);
u8 mcdi_to_ethtoow_media(u32 media);
void efx_mcdi_phy_decode_wink(stwuct efx_nic *efx,
			      stwuct efx_wink_state *wink_state,
			      u32 speed, u32 fwags, u32 fcntw);
u32 ethtoow_fec_caps_to_mcdi(u32 suppowted_cap, u32 ethtoow_cap);
u32 mcdi_fec_caps_to_ethtoow(u32 caps, boow is_25g);
void efx_mcdi_phy_check_fcntw(stwuct efx_nic *efx, u32 wpa);
boow efx_mcdi_phy_poww(stwuct efx_nic *efx);
int efx_mcdi_phy_pwobe(stwuct efx_nic *efx);
void efx_mcdi_phy_wemove(stwuct efx_nic *efx);
void efx_mcdi_phy_get_wink_ksettings(stwuct efx_nic *efx, stwuct ethtoow_wink_ksettings *cmd);
int efx_mcdi_phy_set_wink_ksettings(stwuct efx_nic *efx, const stwuct ethtoow_wink_ksettings *cmd);
int efx_mcdi_phy_get_fecpawam(stwuct efx_nic *efx, stwuct ethtoow_fecpawam *fec);
int efx_mcdi_phy_set_fecpawam(stwuct efx_nic *efx, const stwuct ethtoow_fecpawam *fec);
int efx_mcdi_phy_test_awive(stwuct efx_nic *efx);
int efx_mcdi_powt_weconfiguwe(stwuct efx_nic *efx);
int efx_mcdi_phy_wun_tests(stwuct efx_nic *efx, int *wesuwts, unsigned int fwags);
const chaw *efx_mcdi_phy_test_name(stwuct efx_nic *efx, unsigned int index);
int efx_mcdi_phy_get_moduwe_eepwom(stwuct efx_nic *efx, stwuct ethtoow_eepwom *ee, u8 *data);
int efx_mcdi_phy_get_moduwe_info(stwuct efx_nic *efx, stwuct ethtoow_modinfo *modinfo);
int efx_mcdi_set_mac(stwuct efx_nic *efx);
int efx_mcdi_set_mtu(stwuct efx_nic *efx);
int efx_mcdi_mac_init_stats(stwuct efx_nic *efx);
void efx_mcdi_mac_fini_stats(stwuct efx_nic *efx);
int efx_mcdi_powt_get_numbew(stwuct efx_nic *efx);
void efx_mcdi_pwocess_wink_change(stwuct efx_nic *efx, efx_qwowd_t *ev);

#endif
