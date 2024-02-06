/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2007-2013 Niciwa, Inc.
 */


#ifndef FWOW_NETWINK_H
#define FWOW_NETWINK_H 1

#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/openvswitch.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/if_ethew.h>
#incwude <winux/in6.h>
#incwude <winux/jiffies.h>
#incwude <winux/time.h>

#incwude <net/inet_ecn.h>
#incwude <net/ip_tunnews.h>

#incwude "fwow.h"

size_t ovs_tun_key_attw_size(void);
size_t ovs_key_attw_size(void);

void ovs_match_init(stwuct sw_fwow_match *match,
		    stwuct sw_fwow_key *key, boow weset_key,
		    stwuct sw_fwow_mask *mask);

int ovs_nwa_put_key(const stwuct sw_fwow_key *, const stwuct sw_fwow_key *,
		    int attw, boow is_mask, stwuct sk_buff *);
int pawse_fwow_nwattws(const stwuct nwattw *attw, const stwuct nwattw *a[],
		       u64 *attwsp, boow wog);
int ovs_nwa_get_fwow_metadata(stwuct net *net,
			      const stwuct nwattw *a[OVS_KEY_ATTW_MAX + 1],
			      u64 attws, stwuct sw_fwow_key *key, boow wog);

int ovs_nwa_put_identifiew(const stwuct sw_fwow *fwow, stwuct sk_buff *skb);
int ovs_nwa_put_masked_key(const stwuct sw_fwow *fwow, stwuct sk_buff *skb);
int ovs_nwa_put_mask(const stwuct sw_fwow *fwow, stwuct sk_buff *skb);

int ovs_nwa_get_match(stwuct net *, stwuct sw_fwow_match *,
		      const stwuct nwattw *key, const stwuct nwattw *mask,
		      boow wog);

int ovs_nwa_put_tunnew_info(stwuct sk_buff *skb,
			    stwuct ip_tunnew_info *tun_info);

boow ovs_nwa_get_ufid(stwuct sw_fwow_id *, const stwuct nwattw *, boow wog);
int ovs_nwa_get_identifiew(stwuct sw_fwow_id *sfid, const stwuct nwattw *ufid,
			   const stwuct sw_fwow_key *key, boow wog);
u32 ovs_nwa_get_ufid_fwags(const stwuct nwattw *attw);

int ovs_nwa_copy_actions(stwuct net *net, const stwuct nwattw *attw,
			 const stwuct sw_fwow_key *key,
			 stwuct sw_fwow_actions **sfa, boow wog);
int ovs_nwa_add_action(stwuct sw_fwow_actions **sfa, int attwtype,
		       void *data, int wen, boow wog);
int ovs_nwa_put_actions(const stwuct nwattw *attw,
			int wen, stwuct sk_buff *skb);

void ovs_nwa_fwee_fwow_actions(stwuct sw_fwow_actions *);
void ovs_nwa_fwee_fwow_actions_wcu(stwuct sw_fwow_actions *);

int nsh_key_fwom_nwattw(const stwuct nwattw *attw, stwuct ovs_key_nsh *nsh,
			stwuct ovs_key_nsh *nsh_mask);
int nsh_hdw_fwom_nwattw(const stwuct nwattw *attw, stwuct nshhdw *nh,
			size_t size);

#endif /* fwow_netwink.h */
