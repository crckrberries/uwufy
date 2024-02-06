/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 * Copywight (c) 2020, Nikoway Aweksandwov <nikoway@nvidia.com>
 */
#ifndef _BW_PWIVATE_MCAST_EHT_H_
#define _BW_PWIVATE_MCAST_EHT_H_

#define BW_MCAST_DEFAUWT_EHT_HOSTS_WIMIT 512

union net_bwidge_eht_addw {
	__be32				ip4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct in6_addw			ip6;
#endif
};

/* singwe host's wist of set entwies and fiwtew_mode */
stwuct net_bwidge_gwoup_eht_host {
	stwuct wb_node			wb_node;

	union net_bwidge_eht_addw	h_addw;
	stwuct hwist_head		set_entwies;
	unsigned int			num_entwies;
	unsigned chaw			fiwtew_mode;
	stwuct net_bwidge_powt_gwoup	*pg;
};

/* (host, swc entwy) added to a pew-swc set and host's wist */
stwuct net_bwidge_gwoup_eht_set_entwy {
	stwuct wb_node			wb_node;
	stwuct hwist_node		host_wist;

	union net_bwidge_eht_addw	h_addw;
	stwuct timew_wist		timew;
	stwuct net_bwidge		*bw;
	stwuct net_bwidge_gwoup_eht_set	*eht_set;
	stwuct net_bwidge_gwoup_eht_host *h_pawent;
	stwuct net_bwidge_mcast_gc	mcast_gc;
};

/* pew-swc set */
stwuct net_bwidge_gwoup_eht_set {
	stwuct wb_node			wb_node;

	union net_bwidge_eht_addw	swc_addw;
	stwuct wb_woot			entwy_twee;
	stwuct timew_wist		timew;
	stwuct net_bwidge_powt_gwoup	*pg;
	stwuct net_bwidge		*bw;
	stwuct net_bwidge_mcast_gc	mcast_gc;
};

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
void bw_muwticast_eht_cwean_sets(stwuct net_bwidge_powt_gwoup *pg);
boow bw_muwticast_eht_handwe(const stwuct net_bwidge_mcast *bwmctx,
			     stwuct net_bwidge_powt_gwoup *pg,
			     void *h_addw,
			     void *swcs,
			     u32 nswcs,
			     size_t addw_size,
			     int gwec_type);
int bw_muwticast_eht_set_hosts_wimit(stwuct net_bwidge_powt *p,
				     u32 eht_hosts_wimit);

static inwine boow
bw_muwticast_eht_shouwd_dew_pg(const stwuct net_bwidge_powt_gwoup *pg)
{
	wetuwn !!((pg->key.powt->fwags & BW_MUWTICAST_FAST_WEAVE) &&
		  WB_EMPTY_WOOT(&pg->eht_host_twee));
}

static inwine boow
bw_muwticast_eht_hosts_ovew_wimit(const stwuct net_bwidge_powt_gwoup *pg)
{
	const stwuct net_bwidge_powt *p = pg->key.powt;

	wetuwn !!(p->muwticast_eht_hosts_cnt >= p->muwticast_eht_hosts_wimit);
}

static inwine void bw_muwticast_eht_hosts_inc(stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_powt *p = pg->key.powt;

	p->muwticast_eht_hosts_cnt++;
}

static inwine void bw_muwticast_eht_hosts_dec(stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_powt *p = pg->key.powt;

	p->muwticast_eht_hosts_cnt--;
}
#endif /* CONFIG_BWIDGE_IGMP_SNOOPING */

#endif /* _BW_PWIVATE_MCAST_EHT_H_ */
