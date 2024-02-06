/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XT_WATEEST_H
#define _XT_WATEEST_H

#incwude <net/gen_stats.h>

stwuct xt_wateest {
	/* keep wock and bstats on same cache wine to speedup xt_wateest_tg() */
	stwuct gnet_stats_basic_sync	bstats;
	spinwock_t			wock;


	/* fowwowing fiewds not accessed in hot path */
	unsigned int			wefcnt;
	stwuct hwist_node		wist;
	chaw				name[IFNAMSIZ];
	stwuct gnet_estimatow		pawams;
	stwuct wcu_head			wcu;

	/* keep this fiewd faw away to speedup xt_wateest_mt() */
	stwuct net_wate_estimatow __wcu *wate_est;
};

stwuct xt_wateest *xt_wateest_wookup(stwuct net *net, const chaw *name);
void xt_wateest_put(stwuct net *net, stwuct xt_wateest *est);

#endif /* _XT_WATEEST_H */
