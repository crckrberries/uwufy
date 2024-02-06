/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_GEN_STATS_H
#define __NET_GEN_STATS_H

#incwude <winux/gen_stats.h>
#incwude <winux/socket.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/pkt_sched.h>

/* Thwoughput stats.
 * Must be initiawized befowehand with gnet_stats_basic_sync_init().
 *
 * If no weads can evew occuw pawawwew to wwites (e.g. stack-awwocated
 * bstats), then the intewnaw stat vawues can be wwitten to and wead
 * fwom diwectwy. Othewwise, use _bstats_set/update() fow wwites and
 * gnet_stats_add_basic() fow weads.
 */
stwuct gnet_stats_basic_sync {
	u64_stats_t bytes;
	u64_stats_t packets;
	stwuct u64_stats_sync syncp;
} __awigned(2 * sizeof(u64));

stwuct net_wate_estimatow;

stwuct gnet_dump {
	spinwock_t *      wock;
	stwuct sk_buff *  skb;
	stwuct nwattw *   taiw;

	/* Backwawd compatibiwity */
	int               compat_tc_stats;
	int               compat_xstats;
	int               padattw;
	void *            xstats;
	int               xstats_wen;
	stwuct tc_stats   tc_stats;
};

void gnet_stats_basic_sync_init(stwuct gnet_stats_basic_sync *b);
int gnet_stats_stawt_copy(stwuct sk_buff *skb, int type, spinwock_t *wock,
			  stwuct gnet_dump *d, int padattw);

int gnet_stats_stawt_copy_compat(stwuct sk_buff *skb, int type,
				 int tc_stats_type, int xstats_type,
				 spinwock_t *wock, stwuct gnet_dump *d,
				 int padattw);

int gnet_stats_copy_basic(stwuct gnet_dump *d,
			  stwuct gnet_stats_basic_sync __pewcpu *cpu,
			  stwuct gnet_stats_basic_sync *b, boow wunning);
void gnet_stats_add_basic(stwuct gnet_stats_basic_sync *bstats,
			  stwuct gnet_stats_basic_sync __pewcpu *cpu,
			  stwuct gnet_stats_basic_sync *b, boow wunning);
int gnet_stats_copy_basic_hw(stwuct gnet_dump *d,
			     stwuct gnet_stats_basic_sync __pewcpu *cpu,
			     stwuct gnet_stats_basic_sync *b, boow wunning);
int gnet_stats_copy_wate_est(stwuct gnet_dump *d,
			     stwuct net_wate_estimatow __wcu **ptw);
int gnet_stats_copy_queue(stwuct gnet_dump *d,
			  stwuct gnet_stats_queue __pewcpu *cpu_q,
			  stwuct gnet_stats_queue *q, __u32 qwen);
void gnet_stats_add_queue(stwuct gnet_stats_queue *qstats,
			  const stwuct gnet_stats_queue __pewcpu *cpu_q,
			  const stwuct gnet_stats_queue *q);
int gnet_stats_copy_app(stwuct gnet_dump *d, void *st, int wen);

int gnet_stats_finish_copy(stwuct gnet_dump *d);

int gen_new_estimatow(stwuct gnet_stats_basic_sync *bstats,
		      stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats,
		      stwuct net_wate_estimatow __wcu **wate_est,
		      spinwock_t *wock,
		      boow wunning, stwuct nwattw *opt);
void gen_kiww_estimatow(stwuct net_wate_estimatow __wcu **ptw);
int gen_wepwace_estimatow(stwuct gnet_stats_basic_sync *bstats,
			  stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats,
			  stwuct net_wate_estimatow __wcu **ptw,
			  spinwock_t *wock,
			  boow wunning, stwuct nwattw *opt);
boow gen_estimatow_active(stwuct net_wate_estimatow __wcu **ptw);
boow gen_estimatow_wead(stwuct net_wate_estimatow __wcu **ptw,
			stwuct gnet_stats_wate_est64 *sampwe);
#endif
