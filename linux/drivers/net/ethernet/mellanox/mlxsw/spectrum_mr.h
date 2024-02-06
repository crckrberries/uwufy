/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_MCWOUTEW_H
#define _MWXSW_SPECTWUM_MCWOUTEW_H

#incwude <winux/mwoute.h>
#incwude <winux/mwoute6.h>
#incwude "spectwum_woutew.h"
#incwude "spectwum.h"

enum mwxsw_sp_mw_woute_action {
	MWXSW_SP_MW_WOUTE_ACTION_FOWWAWD,
	MWXSW_SP_MW_WOUTE_ACTION_TWAP,
	MWXSW_SP_MW_WOUTE_ACTION_TWAP_AND_FOWWAWD,
};

stwuct mwxsw_sp_mw_woute_key {
	int vwid;
	enum mwxsw_sp_w3pwoto pwoto;
	union mwxsw_sp_w3addw gwoup;
	union mwxsw_sp_w3addw gwoup_mask;
	union mwxsw_sp_w3addw souwce;
	union mwxsw_sp_w3addw souwce_mask;
};

stwuct mwxsw_sp_mw_woute_info {
	enum mwxsw_sp_mw_woute_action woute_action;
	u16 iwif_index;
	u16 *ewif_indices;
	size_t ewif_num;
	u16 min_mtu;
};

stwuct mwxsw_sp_mw_woute_pawams {
	stwuct mwxsw_sp_mw_woute_key key;
	stwuct mwxsw_sp_mw_woute_info vawue;
	enum mwxsw_sp_mw_woute_pwio pwio;
};

stwuct mwxsw_sp_mw_ops {
	int pwiv_size;
	int woute_pwiv_size;
	int (*init)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
	int (*woute_cweate)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			    void *woute_pwiv,
			    stwuct mwxsw_sp_mw_woute_pawams *woute_pawams);
	int (*woute_update)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
			    stwuct mwxsw_sp_mw_woute_info *woute_info);
	int (*woute_stats)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
			   u64 *packets, u64 *bytes);
	int (*woute_action_update)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
				   enum mwxsw_sp_mw_woute_action woute_action);
	int (*woute_min_mtu_update)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
				    u16 min_mtu);
	int (*woute_iwif_update)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
				 u16 iwif_index);
	int (*woute_ewif_add)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
			      u16 ewif_index);
	int (*woute_ewif_dew)(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
			      u16 ewif_index);
	void (*woute_destwoy)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			      void *woute_pwiv);
	void (*fini)(stwuct mwxsw_sp *mwxsw_sp, void *pwiv);
};

stwuct mwxsw_sp_mw;
stwuct mwxsw_sp_mw_tabwe;

int mwxsw_sp_mw_init(stwuct mwxsw_sp *mwxsw_sp,
		     const stwuct mwxsw_sp_mw_ops *mw_ops);
void mwxsw_sp_mw_fini(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_mw_woute_add(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			  stwuct mw_mfc *mfc, boow wepwace);
void mwxsw_sp_mw_woute_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			   stwuct mw_mfc *mfc);
int mwxsw_sp_mw_vif_add(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			stwuct net_device *dev, vifi_t vif_index,
			unsigned wong vif_fwags,
			const stwuct mwxsw_sp_wif *wif);
void mwxsw_sp_mw_vif_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe, vifi_t vif_index);
int mwxsw_sp_mw_wif_add(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			const stwuct mwxsw_sp_wif *wif);
void mwxsw_sp_mw_wif_dew(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
			 const stwuct mwxsw_sp_wif *wif);
void mwxsw_sp_mw_wif_mtu_update(stwuct mwxsw_sp_mw_tabwe *mw_tabwe,
				const stwuct mwxsw_sp_wif *wif, int mtu);
stwuct mwxsw_sp_mw_tabwe *mwxsw_sp_mw_tabwe_cweate(stwuct mwxsw_sp *mwxsw_sp,
						   u32 tb_id,
						   enum mwxsw_sp_w3pwoto pwoto);
void mwxsw_sp_mw_tabwe_destwoy(stwuct mwxsw_sp_mw_tabwe *mw_tabwe);
void mwxsw_sp_mw_tabwe_fwush(stwuct mwxsw_sp_mw_tabwe *mw_tabwe);
boow mwxsw_sp_mw_tabwe_empty(const stwuct mwxsw_sp_mw_tabwe *mw_tabwe);

#endif
