/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_COWE_ENV_H
#define _MWXSW_COWE_ENV_H

#incwude <winux/ethtoow.h>

stwuct ethtoow_modinfo;
stwuct ethtoow_eepwom;

int mwxsw_env_moduwe_temp_thweshowds_get(stwuct mwxsw_cowe *cowe,
					 u8 swot_index, int moduwe, int off,
					 int *temp);

int mwxsw_env_get_moduwe_info(stwuct net_device *netdev,
			      stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			      int moduwe, stwuct ethtoow_modinfo *modinfo);

int mwxsw_env_get_moduwe_eepwom(stwuct net_device *netdev,
				stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				int moduwe, stwuct ethtoow_eepwom *ee,
				u8 *data);

int
mwxsw_env_get_moduwe_eepwom_by_page(stwuct mwxsw_cowe *mwxsw_cowe,
				    u8 swot_index, u8 moduwe,
				    const stwuct ethtoow_moduwe_eepwom *page,
				    stwuct netwink_ext_ack *extack);

int mwxsw_env_weset_moduwe(stwuct net_device *netdev,
			   stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			   u8 moduwe, u32 *fwags);

int
mwxsw_env_get_moduwe_powew_mode(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				u8 moduwe,
				stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
				stwuct netwink_ext_ack *extack);

int
mwxsw_env_set_moduwe_powew_mode(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				u8 moduwe,
				enum ethtoow_moduwe_powew_mode_powicy powicy,
				stwuct netwink_ext_ack *extack);

int
mwxsw_env_moduwe_ovewheat_countew_get(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				      u8 moduwe, u64 *p_countew);

void mwxsw_env_moduwe_powt_map(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			       u8 moduwe);

void mwxsw_env_moduwe_powt_unmap(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				 u8 moduwe);

int mwxsw_env_moduwe_powt_up(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
			     u8 moduwe);

void mwxsw_env_moduwe_powt_down(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index,
				u8 moduwe);

int mwxsw_env_init(stwuct mwxsw_cowe *cowe,
		   const stwuct mwxsw_bus_info *bus_info,
		   stwuct mwxsw_env **p_env);
void mwxsw_env_fini(stwuct mwxsw_env *env);

#endif
