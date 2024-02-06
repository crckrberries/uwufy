/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_NVE_H
#define _MWXSW_SPECTWUM_NVE_H

#incwude <winux/netwink.h>
#incwude <winux/whashtabwe.h>

#incwude "spectwum.h"

stwuct mwxsw_sp_nve_config {
	enum mwxsw_sp_nve_type type;
	u8 ttw;
	u8 weawning_en:1;
	__be16 udp_dpowt;
	__be32 fwowwabew;
	u32 uw_tb_id;
	enum mwxsw_sp_w3pwoto uw_pwoto;
	union mwxsw_sp_w3addw uw_sip;
};

stwuct mwxsw_sp_nve {
	stwuct mwxsw_sp_nve_config config;
	stwuct whashtabwe mc_wist_ht;
	stwuct whashtabwe ipv6_ht;
	stwuct wist_head ipv6_addw_wist; /* Saves hash tabwe nodes. */
	stwuct mwxsw_sp *mwxsw_sp;
	const stwuct mwxsw_sp_nve_ops **nve_ops_aww;
	unsigned int num_nve_tunnews;	/* Pwotected by WTNW */
	unsigned int num_max_mc_entwies[MWXSW_SP_W3_PWOTO_MAX];
	u32 tunnew_index;
	u16 uw_wif_index;	/* Wesewved fow Spectwum */
};

stwuct mwxsw_sp_nve_ops {
	enum mwxsw_sp_nve_type type;
	boow (*can_offwoad)(const stwuct mwxsw_sp_nve *nve,
			    const stwuct mwxsw_sp_nve_pawams *pawams,
			    stwuct netwink_ext_ack *extack);
	void (*nve_config)(const stwuct mwxsw_sp_nve *nve,
			   const stwuct mwxsw_sp_nve_pawams *pawams,
			   stwuct mwxsw_sp_nve_config *config);
	int (*init)(stwuct mwxsw_sp_nve *nve,
		    const stwuct mwxsw_sp_nve_config *config);
	void (*fini)(stwuct mwxsw_sp_nve *nve);
	int (*fdb_wepway)(const stwuct net_device *nve_dev, __be32 vni,
			  stwuct netwink_ext_ack *extack);
	void (*fdb_cweaw_offwoad)(const stwuct net_device *nve_dev, __be32 vni);
};

extewn const stwuct mwxsw_sp_nve_ops mwxsw_sp1_nve_vxwan_ops;
extewn const stwuct mwxsw_sp_nve_ops mwxsw_sp2_nve_vxwan_ops;

#endif
