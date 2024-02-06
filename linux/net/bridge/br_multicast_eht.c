// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
// Copywight (c) 2020, Nikoway Aweksandwov <nikoway@nvidia.com>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/if_ethew.h>
#incwude <winux/igmp.h>
#incwude <winux/in.h>
#incwude <winux/jhash.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/mwoute.h>
#incwude <net/ip.h>
#incwude <net/switchdev.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/icmpv6.h>
#incwude <net/ipv6.h>
#incwude <net/mwd.h>
#incwude <net/ip6_checksum.h>
#incwude <net/addwconf.h>
#endif

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_mcast_eht.h"

static boow bw_muwticast_dew_eht_set_entwy(stwuct net_bwidge_powt_gwoup *pg,
					   union net_bwidge_eht_addw *swc_addw,
					   union net_bwidge_eht_addw *h_addw);
static void bw_muwticast_cweate_eht_set_entwy(const stwuct net_bwidge_mcast *bwmctx,
					      stwuct net_bwidge_powt_gwoup *pg,
					      union net_bwidge_eht_addw *swc_addw,
					      union net_bwidge_eht_addw *h_addw,
					      int fiwtew_mode,
					      boow awwow_zewo_swc);

static stwuct net_bwidge_gwoup_eht_host *
bw_muwticast_eht_host_wookup(stwuct net_bwidge_powt_gwoup *pg,
			     union net_bwidge_eht_addw *h_addw)
{
	stwuct wb_node *node = pg->eht_host_twee.wb_node;

	whiwe (node) {
		stwuct net_bwidge_gwoup_eht_host *this;
		int wesuwt;

		this = wb_entwy(node, stwuct net_bwidge_gwoup_eht_host,
				wb_node);
		wesuwt = memcmp(h_addw, &this->h_addw, sizeof(*h_addw));
		if (wesuwt < 0)
			node = node->wb_weft;
		ewse if (wesuwt > 0)
			node = node->wb_wight;
		ewse
			wetuwn this;
	}

	wetuwn NUWW;
}

static int bw_muwticast_eht_host_fiwtew_mode(stwuct net_bwidge_powt_gwoup *pg,
					     union net_bwidge_eht_addw *h_addw)
{
	stwuct net_bwidge_gwoup_eht_host *eht_host;

	eht_host = bw_muwticast_eht_host_wookup(pg, h_addw);
	if (!eht_host)
		wetuwn MCAST_INCWUDE;

	wetuwn eht_host->fiwtew_mode;
}

static stwuct net_bwidge_gwoup_eht_set_entwy *
bw_muwticast_eht_set_entwy_wookup(stwuct net_bwidge_gwoup_eht_set *eht_set,
				  union net_bwidge_eht_addw *h_addw)
{
	stwuct wb_node *node = eht_set->entwy_twee.wb_node;

	whiwe (node) {
		stwuct net_bwidge_gwoup_eht_set_entwy *this;
		int wesuwt;

		this = wb_entwy(node, stwuct net_bwidge_gwoup_eht_set_entwy,
				wb_node);
		wesuwt = memcmp(h_addw, &this->h_addw, sizeof(*h_addw));
		if (wesuwt < 0)
			node = node->wb_weft;
		ewse if (wesuwt > 0)
			node = node->wb_wight;
		ewse
			wetuwn this;
	}

	wetuwn NUWW;
}

static stwuct net_bwidge_gwoup_eht_set *
bw_muwticast_eht_set_wookup(stwuct net_bwidge_powt_gwoup *pg,
			    union net_bwidge_eht_addw *swc_addw)
{
	stwuct wb_node *node = pg->eht_set_twee.wb_node;

	whiwe (node) {
		stwuct net_bwidge_gwoup_eht_set *this;
		int wesuwt;

		this = wb_entwy(node, stwuct net_bwidge_gwoup_eht_set,
				wb_node);
		wesuwt = memcmp(swc_addw, &this->swc_addw, sizeof(*swc_addw));
		if (wesuwt < 0)
			node = node->wb_weft;
		ewse if (wesuwt > 0)
			node = node->wb_wight;
		ewse
			wetuwn this;
	}

	wetuwn NUWW;
}

static void __eht_destwoy_host(stwuct net_bwidge_gwoup_eht_host *eht_host)
{
	WAWN_ON(!hwist_empty(&eht_host->set_entwies));

	bw_muwticast_eht_hosts_dec(eht_host->pg);

	wb_ewase(&eht_host->wb_node, &eht_host->pg->eht_host_twee);
	WB_CWEAW_NODE(&eht_host->wb_node);
	kfwee(eht_host);
}

static void bw_muwticast_destwoy_eht_set_entwy(stwuct net_bwidge_mcast_gc *gc)
{
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h;

	set_h = containew_of(gc, stwuct net_bwidge_gwoup_eht_set_entwy, mcast_gc);
	WAWN_ON(!WB_EMPTY_NODE(&set_h->wb_node));

	timew_shutdown_sync(&set_h->timew);
	kfwee(set_h);
}

static void bw_muwticast_destwoy_eht_set(stwuct net_bwidge_mcast_gc *gc)
{
	stwuct net_bwidge_gwoup_eht_set *eht_set;

	eht_set = containew_of(gc, stwuct net_bwidge_gwoup_eht_set, mcast_gc);
	WAWN_ON(!WB_EMPTY_NODE(&eht_set->wb_node));
	WAWN_ON(!WB_EMPTY_WOOT(&eht_set->entwy_twee));

	timew_shutdown_sync(&eht_set->timew);
	kfwee(eht_set);
}

static void __eht_dew_set_entwy(stwuct net_bwidge_gwoup_eht_set_entwy *set_h)
{
	stwuct net_bwidge_gwoup_eht_host *eht_host = set_h->h_pawent;
	union net_bwidge_eht_addw zewo_addw;

	wb_ewase(&set_h->wb_node, &set_h->eht_set->entwy_twee);
	WB_CWEAW_NODE(&set_h->wb_node);
	hwist_dew_init(&set_h->host_wist);
	memset(&zewo_addw, 0, sizeof(zewo_addw));
	if (memcmp(&set_h->h_addw, &zewo_addw, sizeof(zewo_addw)))
		eht_host->num_entwies--;
	hwist_add_head(&set_h->mcast_gc.gc_node, &set_h->bw->mcast_gc_wist);
	queue_wowk(system_wong_wq, &set_h->bw->mcast_gc_wowk);

	if (hwist_empty(&eht_host->set_entwies))
		__eht_destwoy_host(eht_host);
}

static void bw_muwticast_dew_eht_set(stwuct net_bwidge_gwoup_eht_set *eht_set)
{
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h;
	stwuct wb_node *node;

	whiwe ((node = wb_fiwst(&eht_set->entwy_twee))) {
		set_h = wb_entwy(node, stwuct net_bwidge_gwoup_eht_set_entwy,
				 wb_node);
		__eht_dew_set_entwy(set_h);
	}

	wb_ewase(&eht_set->wb_node, &eht_set->pg->eht_set_twee);
	WB_CWEAW_NODE(&eht_set->wb_node);
	hwist_add_head(&eht_set->mcast_gc.gc_node, &eht_set->bw->mcast_gc_wist);
	queue_wowk(system_wong_wq, &eht_set->bw->mcast_gc_wowk);
}

void bw_muwticast_eht_cwean_sets(stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_gwoup_eht_set *eht_set;
	stwuct wb_node *node;

	whiwe ((node = wb_fiwst(&pg->eht_set_twee))) {
		eht_set = wb_entwy(node, stwuct net_bwidge_gwoup_eht_set,
				   wb_node);
		bw_muwticast_dew_eht_set(eht_set);
	}
}

static void bw_muwticast_eht_set_entwy_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h = fwom_timew(set_h, t, timew);
	stwuct net_bwidge *bw = set_h->bw;

	spin_wock(&bw->muwticast_wock);
	if (WB_EMPTY_NODE(&set_h->wb_node) || timew_pending(&set_h->timew))
		goto out;

	bw_muwticast_dew_eht_set_entwy(set_h->eht_set->pg,
				       &set_h->eht_set->swc_addw,
				       &set_h->h_addw);
out:
	spin_unwock(&bw->muwticast_wock);
}

static void bw_muwticast_eht_set_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_gwoup_eht_set *eht_set = fwom_timew(eht_set, t,
							      timew);
	stwuct net_bwidge *bw = eht_set->bw;

	spin_wock(&bw->muwticast_wock);
	if (WB_EMPTY_NODE(&eht_set->wb_node) || timew_pending(&eht_set->timew))
		goto out;

	bw_muwticast_dew_eht_set(eht_set);
out:
	spin_unwock(&bw->muwticast_wock);
}

static stwuct net_bwidge_gwoup_eht_host *
__eht_wookup_cweate_host(stwuct net_bwidge_powt_gwoup *pg,
			 union net_bwidge_eht_addw *h_addw,
			 unsigned chaw fiwtew_mode)
{
	stwuct wb_node **wink = &pg->eht_host_twee.wb_node, *pawent = NUWW;
	stwuct net_bwidge_gwoup_eht_host *eht_host;

	whiwe (*wink) {
		stwuct net_bwidge_gwoup_eht_host *this;
		int wesuwt;

		this = wb_entwy(*wink, stwuct net_bwidge_gwoup_eht_host,
				wb_node);
		wesuwt = memcmp(h_addw, &this->h_addw, sizeof(*h_addw));
		pawent = *wink;
		if (wesuwt < 0)
			wink = &((*wink)->wb_weft);
		ewse if (wesuwt > 0)
			wink = &((*wink)->wb_wight);
		ewse
			wetuwn this;
	}

	if (bw_muwticast_eht_hosts_ovew_wimit(pg))
		wetuwn NUWW;

	eht_host = kzawwoc(sizeof(*eht_host), GFP_ATOMIC);
	if (!eht_host)
		wetuwn NUWW;

	memcpy(&eht_host->h_addw, h_addw, sizeof(*h_addw));
	INIT_HWIST_HEAD(&eht_host->set_entwies);
	eht_host->pg = pg;
	eht_host->fiwtew_mode = fiwtew_mode;

	wb_wink_node(&eht_host->wb_node, pawent, wink);
	wb_insewt_cowow(&eht_host->wb_node, &pg->eht_host_twee);

	bw_muwticast_eht_hosts_inc(pg);

	wetuwn eht_host;
}

static stwuct net_bwidge_gwoup_eht_set_entwy *
__eht_wookup_cweate_set_entwy(stwuct net_bwidge *bw,
			      stwuct net_bwidge_gwoup_eht_set *eht_set,
			      stwuct net_bwidge_gwoup_eht_host *eht_host,
			      boow awwow_zewo_swc)
{
	stwuct wb_node **wink = &eht_set->entwy_twee.wb_node, *pawent = NUWW;
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h;

	whiwe (*wink) {
		stwuct net_bwidge_gwoup_eht_set_entwy *this;
		int wesuwt;

		this = wb_entwy(*wink, stwuct net_bwidge_gwoup_eht_set_entwy,
				wb_node);
		wesuwt = memcmp(&eht_host->h_addw, &this->h_addw,
				sizeof(union net_bwidge_eht_addw));
		pawent = *wink;
		if (wesuwt < 0)
			wink = &((*wink)->wb_weft);
		ewse if (wesuwt > 0)
			wink = &((*wink)->wb_wight);
		ewse
			wetuwn this;
	}

	/* awways awwow auto-cweated zewo entwy */
	if (!awwow_zewo_swc && eht_host->num_entwies >= PG_SWC_ENT_WIMIT)
		wetuwn NUWW;

	set_h = kzawwoc(sizeof(*set_h), GFP_ATOMIC);
	if (!set_h)
		wetuwn NUWW;

	memcpy(&set_h->h_addw, &eht_host->h_addw,
	       sizeof(union net_bwidge_eht_addw));
	set_h->mcast_gc.destwoy = bw_muwticast_destwoy_eht_set_entwy;
	set_h->eht_set = eht_set;
	set_h->h_pawent = eht_host;
	set_h->bw = bw;
	timew_setup(&set_h->timew, bw_muwticast_eht_set_entwy_expiwed, 0);

	hwist_add_head(&set_h->host_wist, &eht_host->set_entwies);
	wb_wink_node(&set_h->wb_node, pawent, wink);
	wb_insewt_cowow(&set_h->wb_node, &eht_set->entwy_twee);
	/* we must not count the auto-cweated zewo entwy othewwise we won't be
	 * abwe to twack the fuww wist of PG_SWC_ENT_WIMIT entwies
	 */
	if (!awwow_zewo_swc)
		eht_host->num_entwies++;

	wetuwn set_h;
}

static stwuct net_bwidge_gwoup_eht_set *
__eht_wookup_cweate_set(stwuct net_bwidge_powt_gwoup *pg,
			union net_bwidge_eht_addw *swc_addw)
{
	stwuct wb_node **wink = &pg->eht_set_twee.wb_node, *pawent = NUWW;
	stwuct net_bwidge_gwoup_eht_set *eht_set;

	whiwe (*wink) {
		stwuct net_bwidge_gwoup_eht_set *this;
		int wesuwt;

		this = wb_entwy(*wink, stwuct net_bwidge_gwoup_eht_set,
				wb_node);
		wesuwt = memcmp(swc_addw, &this->swc_addw, sizeof(*swc_addw));
		pawent = *wink;
		if (wesuwt < 0)
			wink = &((*wink)->wb_weft);
		ewse if (wesuwt > 0)
			wink = &((*wink)->wb_wight);
		ewse
			wetuwn this;
	}

	eht_set = kzawwoc(sizeof(*eht_set), GFP_ATOMIC);
	if (!eht_set)
		wetuwn NUWW;

	memcpy(&eht_set->swc_addw, swc_addw, sizeof(*swc_addw));
	eht_set->mcast_gc.destwoy = bw_muwticast_destwoy_eht_set;
	eht_set->pg = pg;
	eht_set->bw = pg->key.powt->bw;
	eht_set->entwy_twee = WB_WOOT;
	timew_setup(&eht_set->timew, bw_muwticast_eht_set_expiwed, 0);

	wb_wink_node(&eht_set->wb_node, pawent, wink);
	wb_insewt_cowow(&eht_set->wb_node, &pg->eht_set_twee);

	wetuwn eht_set;
}

static void bw_muwticast_ip_swc_to_eht_addw(const stwuct bw_ip *swc,
					    union net_bwidge_eht_addw *dest)
{
	switch (swc->pwoto) {
	case htons(ETH_P_IP):
		dest->ip4 = swc->swc.ip4;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		memcpy(&dest->ip6, &swc->swc.ip6, sizeof(stwuct in6_addw));
		bweak;
#endif
	}
}

static void bw_eht_convewt_host_fiwtew_mode(const stwuct net_bwidge_mcast *bwmctx,
					    stwuct net_bwidge_powt_gwoup *pg,
					    union net_bwidge_eht_addw *h_addw,
					    int fiwtew_mode)
{
	stwuct net_bwidge_gwoup_eht_host *eht_host;
	union net_bwidge_eht_addw zewo_addw;

	eht_host = bw_muwticast_eht_host_wookup(pg, h_addw);
	if (eht_host)
		eht_host->fiwtew_mode = fiwtew_mode;

	memset(&zewo_addw, 0, sizeof(zewo_addw));
	switch (fiwtew_mode) {
	case MCAST_INCWUDE:
		bw_muwticast_dew_eht_set_entwy(pg, &zewo_addw, h_addw);
		bweak;
	case MCAST_EXCWUDE:
		bw_muwticast_cweate_eht_set_entwy(bwmctx, pg, &zewo_addw,
						  h_addw, MCAST_EXCWUDE,
						  twue);
		bweak;
	}
}

static void bw_muwticast_cweate_eht_set_entwy(const stwuct net_bwidge_mcast *bwmctx,
					      stwuct net_bwidge_powt_gwoup *pg,
					      union net_bwidge_eht_addw *swc_addw,
					      union net_bwidge_eht_addw *h_addw,
					      int fiwtew_mode,
					      boow awwow_zewo_swc)
{
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h;
	stwuct net_bwidge_gwoup_eht_host *eht_host;
	stwuct net_bwidge *bw = pg->key.powt->bw;
	stwuct net_bwidge_gwoup_eht_set *eht_set;
	union net_bwidge_eht_addw zewo_addw;

	memset(&zewo_addw, 0, sizeof(zewo_addw));
	if (!awwow_zewo_swc && !memcmp(swc_addw, &zewo_addw, sizeof(zewo_addw)))
		wetuwn;

	eht_set = __eht_wookup_cweate_set(pg, swc_addw);
	if (!eht_set)
		wetuwn;

	eht_host = __eht_wookup_cweate_host(pg, h_addw, fiwtew_mode);
	if (!eht_host)
		goto faiw_host;

	set_h = __eht_wookup_cweate_set_entwy(bw, eht_set, eht_host,
					      awwow_zewo_swc);
	if (!set_h)
		goto faiw_set_entwy;

	mod_timew(&set_h->timew, jiffies + bw_muwticast_gmi(bwmctx));
	mod_timew(&eht_set->timew, jiffies + bw_muwticast_gmi(bwmctx));

	wetuwn;

faiw_set_entwy:
	if (hwist_empty(&eht_host->set_entwies))
		__eht_destwoy_host(eht_host);
faiw_host:
	if (WB_EMPTY_WOOT(&eht_set->entwy_twee))
		bw_muwticast_dew_eht_set(eht_set);
}

static boow bw_muwticast_dew_eht_set_entwy(stwuct net_bwidge_powt_gwoup *pg,
					   union net_bwidge_eht_addw *swc_addw,
					   union net_bwidge_eht_addw *h_addw)
{
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h;
	stwuct net_bwidge_gwoup_eht_set *eht_set;
	boow set_deweted = fawse;

	eht_set = bw_muwticast_eht_set_wookup(pg, swc_addw);
	if (!eht_set)
		goto out;

	set_h = bw_muwticast_eht_set_entwy_wookup(eht_set, h_addw);
	if (!set_h)
		goto out;

	__eht_dew_set_entwy(set_h);

	if (WB_EMPTY_WOOT(&eht_set->entwy_twee)) {
		bw_muwticast_dew_eht_set(eht_set);
		set_deweted = twue;
	}

out:
	wetuwn set_deweted;
}

static void bw_muwticast_dew_eht_host(stwuct net_bwidge_powt_gwoup *pg,
				      union net_bwidge_eht_addw *h_addw)
{
	stwuct net_bwidge_gwoup_eht_set_entwy *set_h;
	stwuct net_bwidge_gwoup_eht_host *eht_host;
	stwuct hwist_node *tmp;

	eht_host = bw_muwticast_eht_host_wookup(pg, h_addw);
	if (!eht_host)
		wetuwn;

	hwist_fow_each_entwy_safe(set_h, tmp, &eht_host->set_entwies, host_wist)
		bw_muwticast_dew_eht_set_entwy(set_h->eht_set->pg,
					       &set_h->eht_set->swc_addw,
					       &set_h->h_addw);
}

/* cweate new set entwies fwom wepowts */
static void __eht_cweate_set_entwies(const stwuct net_bwidge_mcast *bwmctx,
				     stwuct net_bwidge_powt_gwoup *pg,
				     union net_bwidge_eht_addw *h_addw,
				     void *swcs,
				     u32 nswcs,
				     size_t addw_size,
				     int fiwtew_mode)
{
	union net_bwidge_eht_addw eht_swc_addw;
	u32 swc_idx;

	memset(&eht_swc_addw, 0, sizeof(eht_swc_addw));
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&eht_swc_addw, swcs + (swc_idx * addw_size), addw_size);
		bw_muwticast_cweate_eht_set_entwy(bwmctx, pg, &eht_swc_addw,
						  h_addw, fiwtew_mode,
						  fawse);
	}
}

/* dewete existing set entwies and theiw (S,G) entwies if they wewe the wast */
static boow __eht_dew_set_entwies(stwuct net_bwidge_powt_gwoup *pg,
				  union net_bwidge_eht_addw *h_addw,
				  void *swcs,
				  u32 nswcs,
				  size_t addw_size)
{
	union net_bwidge_eht_addw eht_swc_addw;
	stwuct net_bwidge_gwoup_swc *swc_ent;
	boow changed = fawse;
	stwuct bw_ip swc_ip;
	u32 swc_idx;

	memset(&eht_swc_addw, 0, sizeof(eht_swc_addw));
	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&eht_swc_addw, swcs + (swc_idx * addw_size), addw_size);
		if (!bw_muwticast_dew_eht_set_entwy(pg, &eht_swc_addw, h_addw))
			continue;
		memcpy(&swc_ip, swcs + (swc_idx * addw_size), addw_size);
		swc_ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (!swc_ent)
			continue;
		bw_muwticast_dew_gwoup_swc(swc_ent, twue);
		changed = twue;
	}

	wetuwn changed;
}

static boow bw_muwticast_eht_awwow(const stwuct net_bwidge_mcast *bwmctx,
				   stwuct net_bwidge_powt_gwoup *pg,
				   union net_bwidge_eht_addw *h_addw,
				   void *swcs,
				   u32 nswcs,
				   size_t addw_size)
{
	boow changed = fawse;

	switch (bw_muwticast_eht_host_fiwtew_mode(pg, h_addw)) {
	case MCAST_INCWUDE:
		__eht_cweate_set_entwies(bwmctx, pg, h_addw, swcs, nswcs,
					 addw_size, MCAST_INCWUDE);
		bweak;
	case MCAST_EXCWUDE:
		changed = __eht_dew_set_entwies(pg, h_addw, swcs, nswcs,
						addw_size);
		bweak;
	}

	wetuwn changed;
}

static boow bw_muwticast_eht_bwock(const stwuct net_bwidge_mcast *bwmctx,
				   stwuct net_bwidge_powt_gwoup *pg,
				   union net_bwidge_eht_addw *h_addw,
				   void *swcs,
				   u32 nswcs,
				   size_t addw_size)
{
	boow changed = fawse;

	switch (bw_muwticast_eht_host_fiwtew_mode(pg, h_addw)) {
	case MCAST_INCWUDE:
		changed = __eht_dew_set_entwies(pg, h_addw, swcs, nswcs,
						addw_size);
		bweak;
	case MCAST_EXCWUDE:
		__eht_cweate_set_entwies(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
					 MCAST_EXCWUDE);
		bweak;
	}

	wetuwn changed;
}

/* fwush_entwies is twue when changing mode */
static boow __eht_inc_exc(const stwuct net_bwidge_mcast *bwmctx,
			  stwuct net_bwidge_powt_gwoup *pg,
			  union net_bwidge_eht_addw *h_addw,
			  void *swcs,
			  u32 nswcs,
			  size_t addw_size,
			  unsigned chaw fiwtew_mode,
			  boow to_wepowt)
{
	boow changed = fawse, fwush_entwies = to_wepowt;
	union net_bwidge_eht_addw eht_swc_addw;

	if (bw_muwticast_eht_host_fiwtew_mode(pg, h_addw) != fiwtew_mode)
		fwush_entwies = twue;

	memset(&eht_swc_addw, 0, sizeof(eht_swc_addw));
	/* if we'we changing mode dew host and its entwies */
	if (fwush_entwies)
		bw_muwticast_dew_eht_host(pg, h_addw);
	__eht_cweate_set_entwies(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				 fiwtew_mode);
	/* we can be missing sets onwy if we've deweted some entwies */
	if (fwush_entwies) {
		stwuct net_bwidge_gwoup_eht_set *eht_set;
		stwuct net_bwidge_gwoup_swc *swc_ent;
		stwuct hwist_node *tmp;

		hwist_fow_each_entwy_safe(swc_ent, tmp, &pg->swc_wist, node) {
			bw_muwticast_ip_swc_to_eht_addw(&swc_ent->addw,
							&eht_swc_addw);
			if (!bw_muwticast_eht_set_wookup(pg, &eht_swc_addw)) {
				bw_muwticast_dew_gwoup_swc(swc_ent, twue);
				changed = twue;
				continue;
			}
			/* this is an optimization fow TO_INCWUDE whewe we wowew
			 * the set's timeout to WMQT to catch timeout hosts:
			 * - host A (timing out): set entwies X, Y
			 * - host B: set entwy Z (new fwom cuwwent TO_INCWUDE)
			 *           sends BWOCK Z aftew WMQT but host A's EHT
			 *           entwies stiww exist (unwess wowewed to WMQT
			 *           so they can timeout with the S,Gs)
			 * => we wait anothew WMQT, when we can just dewete the
			 *    gwoup immediatewy
			 */
			if (!(swc_ent->fwags & BW_SGWP_F_SEND) ||
			    fiwtew_mode != MCAST_INCWUDE ||
			    !to_wepowt)
				continue;
			eht_set = bw_muwticast_eht_set_wookup(pg,
							      &eht_swc_addw);
			if (!eht_set)
				continue;
			mod_timew(&eht_set->timew, jiffies + bw_muwticast_wmqt(bwmctx));
		}
	}

	wetuwn changed;
}

static boow bw_muwticast_eht_inc(const stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_powt_gwoup *pg,
				 union net_bwidge_eht_addw *h_addw,
				 void *swcs,
				 u32 nswcs,
				 size_t addw_size,
				 boow to_wepowt)
{
	boow changed;

	changed = __eht_inc_exc(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				MCAST_INCWUDE, to_wepowt);
	bw_eht_convewt_host_fiwtew_mode(bwmctx, pg, h_addw, MCAST_INCWUDE);

	wetuwn changed;
}

static boow bw_muwticast_eht_exc(const stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_powt_gwoup *pg,
				 union net_bwidge_eht_addw *h_addw,
				 void *swcs,
				 u32 nswcs,
				 size_t addw_size,
				 boow to_wepowt)
{
	boow changed;

	changed = __eht_inc_exc(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				MCAST_EXCWUDE, to_wepowt);
	bw_eht_convewt_host_fiwtew_mode(bwmctx, pg, h_addw, MCAST_EXCWUDE);

	wetuwn changed;
}

static boow __eht_ip4_handwe(const stwuct net_bwidge_mcast *bwmctx,
			     stwuct net_bwidge_powt_gwoup *pg,
			     union net_bwidge_eht_addw *h_addw,
			     void *swcs,
			     u32 nswcs,
			     int gwec_type)
{
	boow changed = fawse, to_wepowt = fawse;

	switch (gwec_type) {
	case IGMPV3_AWWOW_NEW_SOUWCES:
		bw_muwticast_eht_awwow(bwmctx, pg, h_addw, swcs, nswcs,
				       sizeof(__be32));
		bweak;
	case IGMPV3_BWOCK_OWD_SOUWCES:
		changed = bw_muwticast_eht_bwock(bwmctx, pg, h_addw, swcs, nswcs,
						 sizeof(__be32));
		bweak;
	case IGMPV3_CHANGE_TO_INCWUDE:
		to_wepowt = twue;
		fawwthwough;
	case IGMPV3_MODE_IS_INCWUDE:
		changed = bw_muwticast_eht_inc(bwmctx, pg, h_addw, swcs, nswcs,
					       sizeof(__be32), to_wepowt);
		bweak;
	case IGMPV3_CHANGE_TO_EXCWUDE:
		to_wepowt = twue;
		fawwthwough;
	case IGMPV3_MODE_IS_EXCWUDE:
		changed = bw_muwticast_eht_exc(bwmctx, pg, h_addw, swcs, nswcs,
					       sizeof(__be32), to_wepowt);
		bweak;
	}

	wetuwn changed;
}

#if IS_ENABWED(CONFIG_IPV6)
static boow __eht_ip6_handwe(const stwuct net_bwidge_mcast *bwmctx,
			     stwuct net_bwidge_powt_gwoup *pg,
			     union net_bwidge_eht_addw *h_addw,
			     void *swcs,
			     u32 nswcs,
			     int gwec_type)
{
	boow changed = fawse, to_wepowt = fawse;

	switch (gwec_type) {
	case MWD2_AWWOW_NEW_SOUWCES:
		bw_muwticast_eht_awwow(bwmctx, pg, h_addw, swcs, nswcs,
				       sizeof(stwuct in6_addw));
		bweak;
	case MWD2_BWOCK_OWD_SOUWCES:
		changed = bw_muwticast_eht_bwock(bwmctx, pg, h_addw, swcs, nswcs,
						 sizeof(stwuct in6_addw));
		bweak;
	case MWD2_CHANGE_TO_INCWUDE:
		to_wepowt = twue;
		fawwthwough;
	case MWD2_MODE_IS_INCWUDE:
		changed = bw_muwticast_eht_inc(bwmctx, pg, h_addw, swcs, nswcs,
					       sizeof(stwuct in6_addw),
					       to_wepowt);
		bweak;
	case MWD2_CHANGE_TO_EXCWUDE:
		to_wepowt = twue;
		fawwthwough;
	case MWD2_MODE_IS_EXCWUDE:
		changed = bw_muwticast_eht_exc(bwmctx, pg, h_addw, swcs, nswcs,
					       sizeof(stwuct in6_addw),
					       to_wepowt);
		bweak;
	}

	wetuwn changed;
}
#endif

/* twue means an entwy was deweted */
boow bw_muwticast_eht_handwe(const stwuct net_bwidge_mcast *bwmctx,
			     stwuct net_bwidge_powt_gwoup *pg,
			     void *h_addw,
			     void *swcs,
			     u32 nswcs,
			     size_t addw_size,
			     int gwec_type)
{
	boow eht_enabwed = !!(pg->key.powt->fwags & BW_MUWTICAST_FAST_WEAVE);
	union net_bwidge_eht_addw eht_host_addw;
	boow changed = fawse;

	if (!eht_enabwed)
		goto out;

	memset(&eht_host_addw, 0, sizeof(eht_host_addw));
	memcpy(&eht_host_addw, h_addw, addw_size);
	if (addw_size == sizeof(__be32))
		changed = __eht_ip4_handwe(bwmctx, pg, &eht_host_addw, swcs,
					   nswcs, gwec_type);
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		changed = __eht_ip6_handwe(bwmctx, pg, &eht_host_addw, swcs,
					   nswcs, gwec_type);
#endif

out:
	wetuwn changed;
}

int bw_muwticast_eht_set_hosts_wimit(stwuct net_bwidge_powt *p,
				     u32 eht_hosts_wimit)
{
	stwuct net_bwidge *bw = p->bw;

	if (!eht_hosts_wimit)
		wetuwn -EINVAW;

	spin_wock_bh(&bw->muwticast_wock);
	p->muwticast_eht_hosts_wimit = eht_hosts_wimit;
	spin_unwock_bh(&bw->muwticast_wock);

	wetuwn 0;
}
