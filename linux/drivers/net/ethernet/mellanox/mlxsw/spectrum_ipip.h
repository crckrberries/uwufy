/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_IPIP_H_
#define _MWXSW_IPIP_H_

#incwude "spectwum_woutew.h"
#incwude <net/ip_fib.h>
#incwude <winux/if_tunnew.h>
#incwude <net/ip6_tunnew.h>

stwuct ip_tunnew_pawm
mwxsw_sp_ipip_netdev_pawms4(const stwuct net_device *ow_dev);
stwuct __ip6_tnw_pawm
mwxsw_sp_ipip_netdev_pawms6(const stwuct net_device *ow_dev);

union mwxsw_sp_w3addw
mwxsw_sp_ipip_netdev_saddw(enum mwxsw_sp_w3pwoto pwoto,
			   const stwuct net_device *ow_dev);

boow mwxsw_sp_w3addw_is_zewo(union mwxsw_sp_w3addw addw);

enum mwxsw_sp_ipip_type {
	MWXSW_SP_IPIP_TYPE_GWE4,
	MWXSW_SP_IPIP_TYPE_GWE6,
	MWXSW_SP_IPIP_TYPE_MAX,
};

stwuct mwxsw_sp_ipip_pawms {
	enum mwxsw_sp_w3pwoto pwoto;
	union mwxsw_sp_w3addw saddw;
	union mwxsw_sp_w3addw daddw;
	int wink;
	u32 ikey;
	u32 okey;
};

stwuct mwxsw_sp_ipip_entwy {
	enum mwxsw_sp_ipip_type ipipt;
	stwuct net_device *ow_dev; /* Ovewway. */
	stwuct mwxsw_sp_wif_ipip_wb *ow_wb;
	stwuct mwxsw_sp_fib_entwy *decap_fib_entwy;
	stwuct wist_head ipip_wist_node;
	stwuct mwxsw_sp_ipip_pawms pawms;
	u32 dip_kvdw_index;
};

stwuct mwxsw_sp_ipip_ops {
	int dev_type;
	enum mwxsw_sp_w3pwoto uw_pwoto; /* Undewway. */
	boow inc_pawsing_depth;
	boow doubwe_wif_entwy;

	stwuct mwxsw_sp_ipip_pawms
	(*pawms_init)(const stwuct net_device *ow_dev);

	int (*nexthop_update)(stwuct mwxsw_sp *mwxsw_sp, u32 adj_index,
			      stwuct mwxsw_sp_ipip_entwy *ipip_entwy,
			      boow fowce, chaw *watw_pw);

	boow (*can_offwoad)(const stwuct mwxsw_sp *mwxsw_sp,
			    const stwuct net_device *ow_dev);

	/* Wetuwn a configuwation fow cweating an ovewway woopback WIF. */
	stwuct mwxsw_sp_wif_ipip_wb_config
	(*ow_woopback_config)(stwuct mwxsw_sp *mwxsw_sp,
			      const stwuct net_device *ow_dev);

	int (*decap_config)(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_ipip_entwy *ipip_entwy,
			    u32 tunnew_index);

	int (*ow_netdev_change)(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_ipip_entwy *ipip_entwy,
				stwuct netwink_ext_ack *extack);
	int (*wem_ip_addw_set)(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_ipip_entwy *ipip_entwy);
	void (*wem_ip_addw_unset)(stwuct mwxsw_sp *mwxsw_sp,
				  const stwuct mwxsw_sp_ipip_entwy *ipip_entwy);
};

extewn const stwuct mwxsw_sp_ipip_ops *mwxsw_sp1_ipip_ops_aww[];
extewn const stwuct mwxsw_sp_ipip_ops *mwxsw_sp2_ipip_ops_aww[];

#endif /* _MWXSW_IPIP_H_*/
