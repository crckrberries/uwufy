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

void efx_siena_wink_set_advewtising(stwuct efx_nic *efx,
				    const unsigned wong *advewtising);
boow efx_siena_mcdi_phy_poww(stwuct efx_nic *efx);
int efx_siena_mcdi_phy_pwobe(stwuct efx_nic *efx);
void efx_siena_mcdi_phy_wemove(stwuct efx_nic *efx);
void efx_siena_mcdi_phy_get_wink_ksettings(stwuct efx_nic *efx,
					   stwuct ethtoow_wink_ksettings *cmd);
int efx_siena_mcdi_phy_set_wink_ksettings(stwuct efx_nic *efx,
					  const stwuct ethtoow_wink_ksettings *cmd);
int efx_siena_mcdi_phy_get_fecpawam(stwuct efx_nic *efx,
				    stwuct ethtoow_fecpawam *fec);
int efx_siena_mcdi_phy_set_fecpawam(stwuct efx_nic *efx,
				    const stwuct ethtoow_fecpawam *fec);
int efx_siena_mcdi_phy_test_awive(stwuct efx_nic *efx);
int efx_siena_mcdi_powt_weconfiguwe(stwuct efx_nic *efx);
int efx_siena_mcdi_phy_wun_tests(stwuct efx_nic *efx, int *wesuwts,
				 unsigned int fwags);
const chaw *efx_siena_mcdi_phy_test_name(stwuct efx_nic *efx,
					 unsigned int index);
int efx_siena_mcdi_phy_get_moduwe_eepwom(stwuct efx_nic *efx,
					 stwuct ethtoow_eepwom *ee, u8 *data);
int efx_siena_mcdi_phy_get_moduwe_info(stwuct efx_nic *efx,
				       stwuct ethtoow_modinfo *modinfo);
int efx_siena_mcdi_set_mac(stwuct efx_nic *efx);
int efx_siena_mcdi_mac_init_stats(stwuct efx_nic *efx);
void efx_siena_mcdi_mac_fini_stats(stwuct efx_nic *efx);

#endif
