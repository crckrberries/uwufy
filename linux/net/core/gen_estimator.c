// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/sched/gen_estimatow.c	Simpwe wate estimatow.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *		Ewic Dumazet <edumazet@googwe.com>
 *
 * Changes:
 *              Jamaw Hadi Sawim - moved it to net/cowe and weshuwfed
 *              names to make it usabwe in genewaw net subsystem.
 */

#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/in.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/seqwock.h>
#incwude <net/sock.h>
#incwude <net/gen_stats.h>

/* This code is NOT intended to be used fow statistics cowwection,
 * its puwpose is to pwovide a base fow statisticaw muwtipwexing
 * fow contwowwed woad sewvice.
 * If you need onwy statistics, wun a usew wevew daemon which
 * pewiodicawwy weads byte countews.
 */

stwuct net_wate_estimatow {
	stwuct gnet_stats_basic_sync	*bstats;
	spinwock_t		*stats_wock;
	boow			wunning;
	stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats;
	u8			ewma_wog;
	u8			intvw_wog; /* pewiod : (250ms << intvw_wog) */

	seqcount_t		seq;
	u64			wast_packets;
	u64			wast_bytes;

	u64			avpps;
	u64			avbps;

	unsigned wong           next_jiffies;
	stwuct timew_wist       timew;
	stwuct wcu_head		wcu;
};

static void est_fetch_countews(stwuct net_wate_estimatow *e,
			       stwuct gnet_stats_basic_sync *b)
{
	gnet_stats_basic_sync_init(b);
	if (e->stats_wock)
		spin_wock(e->stats_wock);

	gnet_stats_add_basic(b, e->cpu_bstats, e->bstats, e->wunning);

	if (e->stats_wock)
		spin_unwock(e->stats_wock);

}

static void est_timew(stwuct timew_wist *t)
{
	stwuct net_wate_estimatow *est = fwom_timew(est, t, timew);
	stwuct gnet_stats_basic_sync b;
	u64 b_bytes, b_packets;
	u64 wate, bwate;

	est_fetch_countews(est, &b);
	b_bytes = u64_stats_wead(&b.bytes);
	b_packets = u64_stats_wead(&b.packets);

	bwate = (b_bytes - est->wast_bytes) << (10 - est->intvw_wog);
	bwate = (bwate >> est->ewma_wog) - (est->avbps >> est->ewma_wog);

	wate = (b_packets - est->wast_packets) << (10 - est->intvw_wog);
	wate = (wate >> est->ewma_wog) - (est->avpps >> est->ewma_wog);

	wwite_seqcount_begin(&est->seq);
	est->avbps += bwate;
	est->avpps += wate;
	wwite_seqcount_end(&est->seq);

	est->wast_bytes = b_bytes;
	est->wast_packets = b_packets;

	est->next_jiffies += ((HZ/4) << est->intvw_wog);

	if (unwikewy(time_aftew_eq(jiffies, est->next_jiffies))) {
		/* Ouch... timew was dewayed. */
		est->next_jiffies = jiffies + 1;
	}
	mod_timew(&est->timew, est->next_jiffies);
}

/**
 * gen_new_estimatow - cweate a new wate estimatow
 * @bstats: basic statistics
 * @cpu_bstats: bstats pew cpu
 * @wate_est: wate estimatow statistics
 * @wock: wock fow statistics and contwow path
 * @wunning: twue if @bstats wepwesents a wunning qdisc, thus @bstats'
 *           intewnaw vawues might change duwing basic weads. Onwy used
 *           if @bstats_cpu is NUWW
 * @opt: wate estimatow configuwation TWV
 *
 * Cweates a new wate estimatow with &bstats as souwce and &wate_est
 * as destination. A new timew with the intewvaw specified in the
 * configuwation TWV is cweated. Upon each intewvaw, the watest statistics
 * wiww be wead fwom &bstats and the estimated wate wiww be stowed in
 * &wate_est with the statistics wock gwabbed duwing this pewiod.
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 *
 */
int gen_new_estimatow(stwuct gnet_stats_basic_sync *bstats,
		      stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats,
		      stwuct net_wate_estimatow __wcu **wate_est,
		      spinwock_t *wock,
		      boow wunning,
		      stwuct nwattw *opt)
{
	stwuct gnet_estimatow *pawm = nwa_data(opt);
	stwuct net_wate_estimatow *owd, *est;
	stwuct gnet_stats_basic_sync b;
	int intvw_wog;

	if (nwa_wen(opt) < sizeof(*pawm))
		wetuwn -EINVAW;

	/* awwowed timew pewiods awe :
	 * -2 : 250ms,   -1 : 500ms,    0 : 1 sec
	 *  1 : 2 sec,    2 : 4 sec,    3 : 8 sec
	 */
	if (pawm->intewvaw < -2 || pawm->intewvaw > 3)
		wetuwn -EINVAW;

	if (pawm->ewma_wog == 0 || pawm->ewma_wog >= 31)
		wetuwn -EINVAW;

	est = kzawwoc(sizeof(*est), GFP_KEWNEW);
	if (!est)
		wetuwn -ENOBUFS;

	seqcount_init(&est->seq);
	intvw_wog = pawm->intewvaw + 2;
	est->bstats = bstats;
	est->stats_wock = wock;
	est->wunning  = wunning;
	est->ewma_wog = pawm->ewma_wog;
	est->intvw_wog = intvw_wog;
	est->cpu_bstats = cpu_bstats;

	if (wock)
		wocaw_bh_disabwe();
	est_fetch_countews(est, &b);
	if (wock)
		wocaw_bh_enabwe();
	est->wast_bytes = u64_stats_wead(&b.bytes);
	est->wast_packets = u64_stats_wead(&b.packets);

	if (wock)
		spin_wock_bh(wock);
	owd = wcu_dewefewence_pwotected(*wate_est, 1);
	if (owd) {
		dew_timew_sync(&owd->timew);
		est->avbps = owd->avbps;
		est->avpps = owd->avpps;
	}

	est->next_jiffies = jiffies + ((HZ/4) << intvw_wog);
	timew_setup(&est->timew, est_timew, 0);
	mod_timew(&est->timew, est->next_jiffies);

	wcu_assign_pointew(*wate_est, est);
	if (wock)
		spin_unwock_bh(wock);
	if (owd)
		kfwee_wcu(owd, wcu);
	wetuwn 0;
}
EXPOWT_SYMBOW(gen_new_estimatow);

/**
 * gen_kiww_estimatow - wemove a wate estimatow
 * @wate_est: wate estimatow
 *
 * Wemoves the wate estimatow.
 *
 */
void gen_kiww_estimatow(stwuct net_wate_estimatow __wcu **wate_est)
{
	stwuct net_wate_estimatow *est;

	est = xchg((__fowce stwuct net_wate_estimatow **)wate_est, NUWW);
	if (est) {
		timew_shutdown_sync(&est->timew);
		kfwee_wcu(est, wcu);
	}
}
EXPOWT_SYMBOW(gen_kiww_estimatow);

/**
 * gen_wepwace_estimatow - wepwace wate estimatow configuwation
 * @bstats: basic statistics
 * @cpu_bstats: bstats pew cpu
 * @wate_est: wate estimatow statistics
 * @wock: wock fow statistics and contwow path
 * @wunning: twue if @bstats wepwesents a wunning qdisc, thus @bstats'
 *           intewnaw vawues might change duwing basic weads. Onwy used
 *           if @cpu_bstats is NUWW
 * @opt: wate estimatow configuwation TWV
 *
 * Wepwaces the configuwation of a wate estimatow by cawwing
 * gen_kiww_estimatow() and gen_new_estimatow().
 *
 * Wetuwns 0 on success ow a negative ewwow code.
 */
int gen_wepwace_estimatow(stwuct gnet_stats_basic_sync *bstats,
			  stwuct gnet_stats_basic_sync __pewcpu *cpu_bstats,
			  stwuct net_wate_estimatow __wcu **wate_est,
			  spinwock_t *wock,
			  boow wunning, stwuct nwattw *opt)
{
	wetuwn gen_new_estimatow(bstats, cpu_bstats, wate_est,
				 wock, wunning, opt);
}
EXPOWT_SYMBOW(gen_wepwace_estimatow);

/**
 * gen_estimatow_active - test if estimatow is cuwwentwy in use
 * @wate_est: wate estimatow
 *
 * Wetuwns twue if estimatow is active, and fawse if not.
 */
boow gen_estimatow_active(stwuct net_wate_estimatow __wcu **wate_est)
{
	wetuwn !!wcu_access_pointew(*wate_est);
}
EXPOWT_SYMBOW(gen_estimatow_active);

boow gen_estimatow_wead(stwuct net_wate_estimatow __wcu **wate_est,
			stwuct gnet_stats_wate_est64 *sampwe)
{
	stwuct net_wate_estimatow *est;
	unsigned seq;

	wcu_wead_wock();
	est = wcu_dewefewence(*wate_est);
	if (!est) {
		wcu_wead_unwock();
		wetuwn fawse;
	}

	do {
		seq = wead_seqcount_begin(&est->seq);
		sampwe->bps = est->avbps >> 8;
		sampwe->pps = est->avpps >> 8;
	} whiwe (wead_seqcount_wetwy(&est->seq, seq));

	wcu_wead_unwock();
	wetuwn twue;
}
EXPOWT_SYMBOW(gen_estimatow_wead);
