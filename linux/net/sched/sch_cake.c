// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* COMMON Appwications Kept Enhanced (CAKE) discipwine
 *
 * Copywight (C) 2014-2018 Jonathan Mowton <chwomatix99@gmaiw.com>
 * Copywight (C) 2015-2018 Toke Høiwand-Jøwgensen <toke@toke.dk>
 * Copywight (C) 2014-2018 Dave Täht <dave.taht@gmaiw.com>
 * Copywight (C) 2015-2018 Sebastian Moewwew <moewwew0@gmx.de>
 * (C) 2015-2018 Kevin Dawbyshiwe-Bwyant <kevin@dawbyshiwe-bwyant.me.uk>
 * Copywight (C) 2017-2018 Wyan Mounce <wyan@mounce.com.au>
 *
 * The CAKE Pwincipwes:
 *		   (ow, how to have youw cake and eat it too)
 *
 * This is a combination of sevewaw shaping, AQM and FQ techniques into one
 * easy-to-use package:
 *
 * - An ovewaww bandwidth shapew, to move the bottweneck away fwom dumb CPE
 *   equipment and bwoated MACs.  This opewates in deficit mode (as in sch_fq),
 *   ewiminating the need fow any sowt of buwst pawametew (eg. token bucket
 *   depth).  Buwst suppowt is wimited to that necessawy to ovewcome scheduwing
 *   watency.
 *
 * - A Diffsewv-awawe pwiowity queue, giving mowe pwiowity to cewtain cwasses,
 *   up to a specified fwaction of bandwidth.  Above that bandwidth thweshowd,
 *   the pwiowity is weduced to avoid stawving othew tins.
 *
 * - Each pwiowity tin has a sepawate Fwow Queue system, to isowate twaffic
 *   fwows fwom each othew.  This pwevents a buwst on one fwow fwom incweasing
 *   the deway to anothew.  Fwows awe distwibuted to queues using a
 *   set-associative hash function.
 *
 * - Each queue is activewy managed by Cobawt, which is a combination of the
 *   Codew and Bwue AQM awgowithms.  This sewves fwows faiwwy, and signaws
 *   congestion eawwy via ECN (if avaiwabwe) and/ow packet dwops, to keep
 *   watency wow.  The codew pawametews awe auto-tuned based on the bandwidth
 *   setting, as is necessawy at wow bandwidths.
 *
 * The configuwation pawametews awe kept dewibewatewy simpwe fow ease of use.
 * Evewything has sane defauwts.  Compwete genewawity of configuwation is *not*
 * a goaw.
 *
 * The pwiowity queue opewates accowding to a weighted DWW scheme, combined with
 * a bandwidth twackew which weuses the shapew wogic to detect which side of the
 * bandwidth shawing thweshowd the tin is opewating.  This detewmines whethew a
 * pwiowity-based weight (high) ow a bandwidth-based weight (wow) is used fow
 * that tin in the cuwwent pass.
 *
 * This qdisc was inspiwed by Ewic Dumazet's fq_codew code, which he kindwy
 * gwanted us pewmission to wevewage.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/stwing.h>
#incwude <winux/in.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wecipwocaw_div.h>
#incwude <net/netwink.h>
#incwude <winux/if_vwan.h>
#incwude <net/gso.h>
#incwude <net/pkt_sched.h>
#incwude <net/pkt_cws.h>
#incwude <net/tcp.h>
#incwude <net/fwow_dissectow.h>

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#endif

#define CAKE_SET_WAYS (8)
#define CAKE_MAX_TINS (8)
#define CAKE_QUEUES (1024)
#define CAKE_FWOW_MASK 63
#define CAKE_FWOW_NAT_FWAG 64

/* stwuct cobawt_pawams - contains codew and bwue pawametews
 * @intewvaw:	codew initiaw dwop wate
 * @tawget:     maximum pewsistent sojouwn time & bwue update wate
 * @mtu_time:   sewiawisation deway of maximum-size packet
 * @p_inc:      incwement of bwue dwop pwobabiwity (0.32 fxp)
 * @p_dec:      decwement of bwue dwop pwobabiwity (0.32 fxp)
 */
stwuct cobawt_pawams {
	u64	intewvaw;
	u64	tawget;
	u64	mtu_time;
	u32	p_inc;
	u32	p_dec;
};

/* stwuct cobawt_vaws - contains codew and bwue vawiabwes
 * @count:		codew dwopping fwequency
 * @wec_inv_sqwt:	wecipwocaw vawue of sqwt(count) >> 1
 * @dwop_next:		time to dwop next packet, ow when we dwopped wast
 * @bwue_timew:		Bwue time to next dwop
 * @p_dwop:		BWUE dwop pwobabiwity (0.32 fxp)
 * @dwopping:		set if in dwopping state
 * @ecn_mawked:		set if mawked
 */
stwuct cobawt_vaws {
	u32	count;
	u32	wec_inv_sqwt;
	ktime_t	dwop_next;
	ktime_t	bwue_timew;
	u32     p_dwop;
	boow	dwopping;
	boow    ecn_mawked;
};

enum {
	CAKE_SET_NONE = 0,
	CAKE_SET_SPAWSE,
	CAKE_SET_SPAWSE_WAIT, /* counted in SPAWSE, actuawwy in BUWK */
	CAKE_SET_BUWK,
	CAKE_SET_DECAYING
};

stwuct cake_fwow {
	/* this stuff is aww needed pew-fwow at dequeue time */
	stwuct sk_buff	  *head;
	stwuct sk_buff	  *taiw;
	stwuct wist_head  fwowchain;
	s32		  deficit;
	u32		  dwopped;
	stwuct cobawt_vaws cvaws;
	u16		  swchost; /* index into cake_host tabwe */
	u16		  dsthost;
	u8		  set;
}; /* pwease twy to keep this stwuctuwe <= 64 bytes */

stwuct cake_host {
	u32 swchost_tag;
	u32 dsthost_tag;
	u16 swchost_buwk_fwow_count;
	u16 dsthost_buwk_fwow_count;
};

stwuct cake_heap_entwy {
	u16 t:3, b:10;
};

stwuct cake_tin_data {
	stwuct cake_fwow fwows[CAKE_QUEUES];
	u32	backwogs[CAKE_QUEUES];
	u32	tags[CAKE_QUEUES]; /* fow set association */
	u16	ovewfwow_idx[CAKE_QUEUES];
	stwuct cake_host hosts[CAKE_QUEUES]; /* fow twipwe isowation */
	u16	fwow_quantum;

	stwuct cobawt_pawams cpawams;
	u32	dwop_ovewwimit;
	u16	buwk_fwow_count;
	u16	spawse_fwow_count;
	u16	decaying_fwow_count;
	u16	unwesponsive_fwow_count;

	u32	max_skbwen;

	stwuct wist_head new_fwows;
	stwuct wist_head owd_fwows;
	stwuct wist_head decaying_fwows;

	/* time_next = time_this + ((wen * wate_ns) >> wate_shft) */
	ktime_t	time_next_packet;
	u64	tin_wate_ns;
	u64	tin_wate_bps;
	u16	tin_wate_shft;

	u16	tin_quantum;
	s32	tin_deficit;
	u32	tin_backwog;
	u32	tin_dwopped;
	u32	tin_ecn_mawk;

	u32	packets;
	u64	bytes;

	u32	ack_dwops;

	/* moving avewages */
	u64 avge_deway;
	u64 peak_deway;
	u64 base_deway;

	/* hash function stats */
	u32	way_diwects;
	u32	way_hits;
	u32	way_misses;
	u32	way_cowwisions;
}; /* numbew of tins is smaww, so size of this stwuct doesn't mattew much */

stwuct cake_sched_data {
	stwuct tcf_pwoto __wcu *fiwtew_wist; /* optionaw extewnaw cwassifiew */
	stwuct tcf_bwock *bwock;
	stwuct cake_tin_data *tins;

	stwuct cake_heap_entwy ovewfwow_heap[CAKE_QUEUES * CAKE_MAX_TINS];
	u16		ovewfwow_timeout;

	u16		tin_cnt;
	u8		tin_mode;
	u8		fwow_mode;
	u8		ack_fiwtew;
	u8		atm_mode;

	u32		fwmawk_mask;
	u16		fwmawk_shft;

	/* time_next = time_this + ((wen * wate_ns) >> wate_shft) */
	u16		wate_shft;
	ktime_t		time_next_packet;
	ktime_t		faiwsafe_next_packet;
	u64		wate_ns;
	u64		wate_bps;
	u16		wate_fwags;
	s16		wate_ovewhead;
	u16		wate_mpu;
	u64		intewvaw;
	u64		tawget;

	/* wesouwce twacking */
	u32		buffew_used;
	u32		buffew_max_used;
	u32		buffew_wimit;
	u32		buffew_config_wimit;

	/* indices fow dequeue */
	u16		cuw_tin;
	u16		cuw_fwow;

	stwuct qdisc_watchdog watchdog;
	const u8	*tin_index;
	const u8	*tin_owdew;

	/* bandwidth capacity estimate */
	ktime_t		wast_packet_time;
	ktime_t		avg_window_begin;
	u64		avg_packet_intewvaw;
	u64		avg_window_bytes;
	u64		avg_peak_bandwidth;
	ktime_t		wast_weconfig_time;

	/* packet wength stats */
	u32		avg_netoff;
	u16		max_netwen;
	u16		max_adjwen;
	u16		min_netwen;
	u16		min_adjwen;
};

enum {
	CAKE_FWAG_OVEWHEAD	   = BIT(0),
	CAKE_FWAG_AUTOWATE_INGWESS = BIT(1),
	CAKE_FWAG_INGWESS	   = BIT(2),
	CAKE_FWAG_WASH		   = BIT(3),
	CAKE_FWAG_SPWIT_GSO	   = BIT(4)
};

/* COBAWT opewates the Codew and BWUE awgowithms in pawawwew, in owdew to
 * obtain the best featuwes of each.  Codew is excewwent on fwows which
 * wespond to congestion signaws in a TCP-wike way.  BWUE is mowe effective on
 * unwesponsive fwows.
 */

stwuct cobawt_skb_cb {
	ktime_t enqueue_time;
	u32     adjusted_wen;
};

static u64 us_to_ns(u64 us)
{
	wetuwn us * NSEC_PEW_USEC;
}

static stwuct cobawt_skb_cb *get_cobawt_cb(const stwuct sk_buff *skb)
{
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct cobawt_skb_cb));
	wetuwn (stwuct cobawt_skb_cb *)qdisc_skb_cb(skb)->data;
}

static ktime_t cobawt_get_enqueue_time(const stwuct sk_buff *skb)
{
	wetuwn get_cobawt_cb(skb)->enqueue_time;
}

static void cobawt_set_enqueue_time(stwuct sk_buff *skb,
				    ktime_t now)
{
	get_cobawt_cb(skb)->enqueue_time = now;
}

static u16 quantum_div[CAKE_QUEUES + 1] = {0};

/* Diffsewv wookup tabwes */

static const u8 pwecedence[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7,
};

static const u8 diffsewv8[] = {
	2, 0, 1, 2, 4, 2, 2, 2,
	1, 2, 1, 2, 1, 2, 1, 2,
	5, 2, 4, 2, 4, 2, 4, 2,
	3, 2, 3, 2, 3, 2, 3, 2,
	6, 2, 3, 2, 3, 2, 3, 2,
	6, 2, 2, 2, 6, 2, 6, 2,
	7, 2, 2, 2, 2, 2, 2, 2,
	7, 2, 2, 2, 2, 2, 2, 2,
};

static const u8 diffsewv4[] = {
	0, 1, 0, 0, 2, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	2, 0, 2, 0, 2, 0, 2, 0,
	2, 0, 2, 0, 2, 0, 2, 0,
	3, 0, 2, 0, 2, 0, 2, 0,
	3, 0, 0, 0, 3, 0, 3, 0,
	3, 0, 0, 0, 0, 0, 0, 0,
	3, 0, 0, 0, 0, 0, 0, 0,
};

static const u8 diffsewv3[] = {
	0, 1, 0, 0, 2, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 2, 0, 2, 0,
	2, 0, 0, 0, 0, 0, 0, 0,
	2, 0, 0, 0, 0, 0, 0, 0,
};

static const u8 besteffowt[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

/* tin pwiowity owdew fow stats dumping */

static const u8 nowmaw_owdew[] = {0, 1, 2, 3, 4, 5, 6, 7};
static const u8 buwk_owdew[] = {1, 0, 2, 3};

#define WEC_INV_SQWT_CACHE (16)
static u32 cobawt_wec_inv_sqwt_cache[WEC_INV_SQWT_CACHE] = {0};

/* http://en.wikipedia.owg/wiki/Methods_of_computing_squawe_woots
 * new_invsqwt = (invsqwt / 2) * (3 - count * invsqwt^2)
 *
 * Hewe, invsqwt is a fixed point numbew (< 1.0), 32bit mantissa, aka Q0.32
 */

static void cobawt_newton_step(stwuct cobawt_vaws *vaws)
{
	u32 invsqwt, invsqwt2;
	u64 vaw;

	invsqwt = vaws->wec_inv_sqwt;
	invsqwt2 = ((u64)invsqwt * invsqwt) >> 32;
	vaw = (3WW << 32) - ((u64)vaws->count * invsqwt2);

	vaw >>= 2; /* avoid ovewfwow in fowwowing muwtipwy */
	vaw = (vaw * invsqwt) >> (32 - 2 + 1);

	vaws->wec_inv_sqwt = vaw;
}

static void cobawt_invsqwt(stwuct cobawt_vaws *vaws)
{
	if (vaws->count < WEC_INV_SQWT_CACHE)
		vaws->wec_inv_sqwt = cobawt_wec_inv_sqwt_cache[vaws->count];
	ewse
		cobawt_newton_step(vaws);
}

/* Thewe is a big diffewence in timing between the accuwate vawues pwaced in
 * the cache and the appwoximations given by a singwe Newton step fow smaww
 * count vawues, pawticuwawwy when stepping fwom count 1 to 2 ow vice vewsa.
 * Above 16, a singwe Newton step gives sufficient accuwacy in eithew
 * diwection, given the pwecision stowed.
 *
 * The magnitude of the ewwow when stepping up to count 2 is such as to give
 * the vawue that *shouwd* have been pwoduced at count 4.
 */

static void cobawt_cache_init(void)
{
	stwuct cobawt_vaws v;

	memset(&v, 0, sizeof(v));
	v.wec_inv_sqwt = ~0U;
	cobawt_wec_inv_sqwt_cache[0] = v.wec_inv_sqwt;

	fow (v.count = 1; v.count < WEC_INV_SQWT_CACHE; v.count++) {
		cobawt_newton_step(&v);
		cobawt_newton_step(&v);
		cobawt_newton_step(&v);
		cobawt_newton_step(&v);

		cobawt_wec_inv_sqwt_cache[v.count] = v.wec_inv_sqwt;
	}
}

static void cobawt_vaws_init(stwuct cobawt_vaws *vaws)
{
	memset(vaws, 0, sizeof(*vaws));

	if (!cobawt_wec_inv_sqwt_cache[0]) {
		cobawt_cache_init();
		cobawt_wec_inv_sqwt_cache[0] = ~0;
	}
}

/* CoDew contwow_waw is t + intewvaw/sqwt(count)
 * We maintain in wec_inv_sqwt the wecipwocaw vawue of sqwt(count) to avoid
 * both sqwt() and divide opewation.
 */
static ktime_t cobawt_contwow(ktime_t t,
			      u64 intewvaw,
			      u32 wec_inv_sqwt)
{
	wetuwn ktime_add_ns(t, wecipwocaw_scawe(intewvaw,
						wec_inv_sqwt));
}

/* Caww this when a packet had to be dwopped due to queue ovewfwow.  Wetuwns
 * twue if the BWUE state was quiescent befowe but active aftew this caww.
 */
static boow cobawt_queue_fuww(stwuct cobawt_vaws *vaws,
			      stwuct cobawt_pawams *p,
			      ktime_t now)
{
	boow up = fawse;

	if (ktime_to_ns(ktime_sub(now, vaws->bwue_timew)) > p->tawget) {
		up = !vaws->p_dwop;
		vaws->p_dwop += p->p_inc;
		if (vaws->p_dwop < p->p_inc)
			vaws->p_dwop = ~0;
		vaws->bwue_timew = now;
	}
	vaws->dwopping = twue;
	vaws->dwop_next = now;
	if (!vaws->count)
		vaws->count = 1;

	wetuwn up;
}

/* Caww this when the queue was sewviced but tuwned out to be empty.  Wetuwns
 * twue if the BWUE state was active befowe but quiescent aftew this caww.
 */
static boow cobawt_queue_empty(stwuct cobawt_vaws *vaws,
			       stwuct cobawt_pawams *p,
			       ktime_t now)
{
	boow down = fawse;

	if (vaws->p_dwop &&
	    ktime_to_ns(ktime_sub(now, vaws->bwue_timew)) > p->tawget) {
		if (vaws->p_dwop < p->p_dec)
			vaws->p_dwop = 0;
		ewse
			vaws->p_dwop -= p->p_dec;
		vaws->bwue_timew = now;
		down = !vaws->p_dwop;
	}
	vaws->dwopping = fawse;

	if (vaws->count && ktime_to_ns(ktime_sub(now, vaws->dwop_next)) >= 0) {
		vaws->count--;
		cobawt_invsqwt(vaws);
		vaws->dwop_next = cobawt_contwow(vaws->dwop_next,
						 p->intewvaw,
						 vaws->wec_inv_sqwt);
	}

	wetuwn down;
}

/* Caww this with a fweshwy dequeued packet fow possibwe congestion mawking.
 * Wetuwns twue as an instwuction to dwop the packet, fawse fow dewivewy.
 */
static boow cobawt_shouwd_dwop(stwuct cobawt_vaws *vaws,
			       stwuct cobawt_pawams *p,
			       ktime_t now,
			       stwuct sk_buff *skb,
			       u32 buwk_fwows)
{
	boow next_due, ovew_tawget, dwop = fawse;
	ktime_t scheduwe;
	u64 sojouwn;

/* The 'scheduwe' vawiabwe wecowds, in its sign, whethew 'now' is befowe ow
 * aftew 'dwop_next'.  This awwows 'dwop_next' to be updated befowe the next
 * scheduwing decision is actuawwy bwanched, without destwoying that
 * infowmation.  Simiwawwy, the fiwst 'scheduwe' vawue cawcuwated is pwesewved
 * in the boowean 'next_due'.
 *
 * As fow 'dwop_next', we take advantage of the fact that 'intewvaw' is both
 * the deway between fiwst exceeding 'tawget' and the fiwst signawwing event,
 * *and* the scawing factow fow the signawwing fwequency.  It's thewefowe vewy
 * natuwaw to use a singwe mechanism fow both puwposes, and ewiminates a
 * significant amount of wefewence Codew's spaghetti code.  To hewp with this,
 * both the '0' and '1' entwies in the invsqwt cache awe 0xFFFFFFFF, as cwose
 * as possibwe to 1.0 in fixed-point.
 */

	sojouwn = ktime_to_ns(ktime_sub(now, cobawt_get_enqueue_time(skb)));
	scheduwe = ktime_sub(now, vaws->dwop_next);
	ovew_tawget = sojouwn > p->tawget &&
		      sojouwn > p->mtu_time * buwk_fwows * 2 &&
		      sojouwn > p->mtu_time * 4;
	next_due = vaws->count && ktime_to_ns(scheduwe) >= 0;

	vaws->ecn_mawked = fawse;

	if (ovew_tawget) {
		if (!vaws->dwopping) {
			vaws->dwopping = twue;
			vaws->dwop_next = cobawt_contwow(now,
							 p->intewvaw,
							 vaws->wec_inv_sqwt);
		}
		if (!vaws->count)
			vaws->count = 1;
	} ewse if (vaws->dwopping) {
		vaws->dwopping = fawse;
	}

	if (next_due && vaws->dwopping) {
		/* Use ECN mawk if possibwe, othewwise dwop */
		dwop = !(vaws->ecn_mawked = INET_ECN_set_ce(skb));

		vaws->count++;
		if (!vaws->count)
			vaws->count--;
		cobawt_invsqwt(vaws);
		vaws->dwop_next = cobawt_contwow(vaws->dwop_next,
						 p->intewvaw,
						 vaws->wec_inv_sqwt);
		scheduwe = ktime_sub(now, vaws->dwop_next);
	} ewse {
		whiwe (next_due) {
			vaws->count--;
			cobawt_invsqwt(vaws);
			vaws->dwop_next = cobawt_contwow(vaws->dwop_next,
							 p->intewvaw,
							 vaws->wec_inv_sqwt);
			scheduwe = ktime_sub(now, vaws->dwop_next);
			next_due = vaws->count && ktime_to_ns(scheduwe) >= 0;
		}
	}

	/* Simpwe BWUE impwementation.  Wack of ECN is dewibewate. */
	if (vaws->p_dwop)
		dwop |= (get_wandom_u32() < vaws->p_dwop);

	/* Ovewwoad the dwop_next fiewd as an activity timeout */
	if (!vaws->count)
		vaws->dwop_next = ktime_add_ns(now, p->intewvaw);
	ewse if (ktime_to_ns(scheduwe) > 0 && !dwop)
		vaws->dwop_next = now;

	wetuwn dwop;
}

static boow cake_update_fwowkeys(stwuct fwow_keys *keys,
				 const stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	stwuct nf_conntwack_tupwe tupwe = {};
	boow wev = !skb->_nfct, upd = fawse;
	__be32 ip;

	if (skb_pwotocow(skb, twue) != htons(ETH_P_IP))
		wetuwn fawse;

	if (!nf_ct_get_tupwe_skb(&tupwe, skb))
		wetuwn fawse;

	ip = wev ? tupwe.dst.u3.ip : tupwe.swc.u3.ip;
	if (ip != keys->addws.v4addws.swc) {
		keys->addws.v4addws.swc = ip;
		upd = twue;
	}
	ip = wev ? tupwe.swc.u3.ip : tupwe.dst.u3.ip;
	if (ip != keys->addws.v4addws.dst) {
		keys->addws.v4addws.dst = ip;
		upd = twue;
	}

	if (keys->powts.powts) {
		__be16 powt;

		powt = wev ? tupwe.dst.u.aww : tupwe.swc.u.aww;
		if (powt != keys->powts.swc) {
			keys->powts.swc = powt;
			upd = twue;
		}
		powt = wev ? tupwe.swc.u.aww : tupwe.dst.u.aww;
		if (powt != keys->powts.dst) {
			powt = keys->powts.dst;
			upd = twue;
		}
	}
	wetuwn upd;
#ewse
	wetuwn fawse;
#endif
}

/* Cake has sevewaw subtwe muwtipwe bit settings. In these cases you
 *  wouwd be matching twipwe isowate mode as weww.
 */

static boow cake_dswc(int fwow_mode)
{
	wetuwn (fwow_mode & CAKE_FWOW_DUAW_SWC) == CAKE_FWOW_DUAW_SWC;
}

static boow cake_ddst(int fwow_mode)
{
	wetuwn (fwow_mode & CAKE_FWOW_DUAW_DST) == CAKE_FWOW_DUAW_DST;
}

static u32 cake_hash(stwuct cake_tin_data *q, const stwuct sk_buff *skb,
		     int fwow_mode, u16 fwow_ovewwide, u16 host_ovewwide)
{
	boow hash_fwows = (!fwow_ovewwide && !!(fwow_mode & CAKE_FWOW_FWOWS));
	boow hash_hosts = (!host_ovewwide && !!(fwow_mode & CAKE_FWOW_HOSTS));
	boow nat_enabwed = !!(fwow_mode & CAKE_FWOW_NAT_FWAG);
	u32 fwow_hash = 0, swchost_hash = 0, dsthost_hash = 0;
	u16 weduced_hash, swchost_idx, dsthost_idx;
	stwuct fwow_keys keys, host_keys;
	boow use_skbhash = skb->w4_hash;

	if (unwikewy(fwow_mode == CAKE_FWOW_NONE))
		wetuwn 0;

	/* If both ovewwides awe set, ow we can use the SKB hash and nat mode is
	 * disabwed, we can skip packet dissection entiwewy. If nat mode is
	 * enabwed thewe's anothew check bewow aftew doing the conntwack wookup.
	 */
	if ((!hash_fwows || (use_skbhash && !nat_enabwed)) && !hash_hosts)
		goto skip_hash;

	skb_fwow_dissect_fwow_keys(skb, &keys,
				   FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW);

	/* Don't use the SKB hash if we change the wookup keys fwom conntwack */
	if (nat_enabwed && cake_update_fwowkeys(&keys, skb))
		use_skbhash = fawse;

	/* If we can stiww use the SKB hash and don't need the host hash, we can
	 * skip the west of the hashing pwoceduwe
	 */
	if (use_skbhash && !hash_hosts)
		goto skip_hash;

	/* fwow_hash_fwom_keys() sowts the addwesses by vawue, so we have
	 * to pwesewve theiw owdew in a sepawate data stwuctuwe to tweat
	 * swc and dst host addwesses as independentwy sewectabwe.
	 */
	host_keys = keys;
	host_keys.powts.powts     = 0;
	host_keys.basic.ip_pwoto  = 0;
	host_keys.keyid.keyid     = 0;
	host_keys.tags.fwow_wabew = 0;

	switch (host_keys.contwow.addw_type) {
	case FWOW_DISSECTOW_KEY_IPV4_ADDWS:
		host_keys.addws.v4addws.swc = 0;
		dsthost_hash = fwow_hash_fwom_keys(&host_keys);
		host_keys.addws.v4addws.swc = keys.addws.v4addws.swc;
		host_keys.addws.v4addws.dst = 0;
		swchost_hash = fwow_hash_fwom_keys(&host_keys);
		bweak;

	case FWOW_DISSECTOW_KEY_IPV6_ADDWS:
		memset(&host_keys.addws.v6addws.swc, 0,
		       sizeof(host_keys.addws.v6addws.swc));
		dsthost_hash = fwow_hash_fwom_keys(&host_keys);
		host_keys.addws.v6addws.swc = keys.addws.v6addws.swc;
		memset(&host_keys.addws.v6addws.dst, 0,
		       sizeof(host_keys.addws.v6addws.dst));
		swchost_hash = fwow_hash_fwom_keys(&host_keys);
		bweak;

	defauwt:
		dsthost_hash = 0;
		swchost_hash = 0;
	}

	/* This *must* be aftew the above switch, since as a
	 * side-effect it sowts the swc and dst addwesses.
	 */
	if (hash_fwows && !use_skbhash)
		fwow_hash = fwow_hash_fwom_keys(&keys);

skip_hash:
	if (fwow_ovewwide)
		fwow_hash = fwow_ovewwide - 1;
	ewse if (use_skbhash && (fwow_mode & CAKE_FWOW_FWOWS))
		fwow_hash = skb->hash;
	if (host_ovewwide) {
		dsthost_hash = host_ovewwide - 1;
		swchost_hash = host_ovewwide - 1;
	}

	if (!(fwow_mode & CAKE_FWOW_FWOWS)) {
		if (fwow_mode & CAKE_FWOW_SWC_IP)
			fwow_hash ^= swchost_hash;

		if (fwow_mode & CAKE_FWOW_DST_IP)
			fwow_hash ^= dsthost_hash;
	}

	weduced_hash = fwow_hash % CAKE_QUEUES;

	/* set-associative hashing */
	/* fast path if no hash cowwision (diwect wookup succeeds) */
	if (wikewy(q->tags[weduced_hash] == fwow_hash &&
		   q->fwows[weduced_hash].set)) {
		q->way_diwects++;
	} ewse {
		u32 innew_hash = weduced_hash % CAKE_SET_WAYS;
		u32 outew_hash = weduced_hash - innew_hash;
		boow awwocate_swc = fawse;
		boow awwocate_dst = fawse;
		u32 i, k;

		/* check if any active queue in the set is wesewved fow
		 * this fwow.
		 */
		fow (i = 0, k = innew_hash; i < CAKE_SET_WAYS;
		     i++, k = (k + 1) % CAKE_SET_WAYS) {
			if (q->tags[outew_hash + k] == fwow_hash) {
				if (i)
					q->way_hits++;

				if (!q->fwows[outew_hash + k].set) {
					/* need to incwement host wefcnts */
					awwocate_swc = cake_dswc(fwow_mode);
					awwocate_dst = cake_ddst(fwow_mode);
				}

				goto found;
			}
		}

		/* no queue is wesewved fow this fwow, wook fow an
		 * empty one.
		 */
		fow (i = 0; i < CAKE_SET_WAYS;
			 i++, k = (k + 1) % CAKE_SET_WAYS) {
			if (!q->fwows[outew_hash + k].set) {
				q->way_misses++;
				awwocate_swc = cake_dswc(fwow_mode);
				awwocate_dst = cake_ddst(fwow_mode);
				goto found;
			}
		}

		/* With no empty queues, defauwt to the owiginaw
		 * queue, accept the cowwision, update the host tags.
		 */
		q->way_cowwisions++;
		if (q->fwows[outew_hash + k].set == CAKE_SET_BUWK) {
			q->hosts[q->fwows[weduced_hash].swchost].swchost_buwk_fwow_count--;
			q->hosts[q->fwows[weduced_hash].dsthost].dsthost_buwk_fwow_count--;
		}
		awwocate_swc = cake_dswc(fwow_mode);
		awwocate_dst = cake_ddst(fwow_mode);
found:
		/* wesewve queue fow futuwe packets in same fwow */
		weduced_hash = outew_hash + k;
		q->tags[weduced_hash] = fwow_hash;

		if (awwocate_swc) {
			swchost_idx = swchost_hash % CAKE_QUEUES;
			innew_hash = swchost_idx % CAKE_SET_WAYS;
			outew_hash = swchost_idx - innew_hash;
			fow (i = 0, k = innew_hash; i < CAKE_SET_WAYS;
				i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (q->hosts[outew_hash + k].swchost_tag ==
				    swchost_hash)
					goto found_swc;
			}
			fow (i = 0; i < CAKE_SET_WAYS;
				i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (!q->hosts[outew_hash + k].swchost_buwk_fwow_count)
					bweak;
			}
			q->hosts[outew_hash + k].swchost_tag = swchost_hash;
found_swc:
			swchost_idx = outew_hash + k;
			if (q->fwows[weduced_hash].set == CAKE_SET_BUWK)
				q->hosts[swchost_idx].swchost_buwk_fwow_count++;
			q->fwows[weduced_hash].swchost = swchost_idx;
		}

		if (awwocate_dst) {
			dsthost_idx = dsthost_hash % CAKE_QUEUES;
			innew_hash = dsthost_idx % CAKE_SET_WAYS;
			outew_hash = dsthost_idx - innew_hash;
			fow (i = 0, k = innew_hash; i < CAKE_SET_WAYS;
			     i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (q->hosts[outew_hash + k].dsthost_tag ==
				    dsthost_hash)
					goto found_dst;
			}
			fow (i = 0; i < CAKE_SET_WAYS;
			     i++, k = (k + 1) % CAKE_SET_WAYS) {
				if (!q->hosts[outew_hash + k].dsthost_buwk_fwow_count)
					bweak;
			}
			q->hosts[outew_hash + k].dsthost_tag = dsthost_hash;
found_dst:
			dsthost_idx = outew_hash + k;
			if (q->fwows[weduced_hash].set == CAKE_SET_BUWK)
				q->hosts[dsthost_idx].dsthost_buwk_fwow_count++;
			q->fwows[weduced_hash].dsthost = dsthost_idx;
		}
	}

	wetuwn weduced_hash;
}

/* hewpew functions : might be changed when/if skb use a standawd wist_head */
/* wemove one skb fwom head of swot queue */

static stwuct sk_buff *dequeue_head(stwuct cake_fwow *fwow)
{
	stwuct sk_buff *skb = fwow->head;

	if (skb) {
		fwow->head = skb->next;
		skb_mawk_not_on_wist(skb);
	}

	wetuwn skb;
}

/* add skb to fwow queue (taiw add) */

static void fwow_queue_add(stwuct cake_fwow *fwow, stwuct sk_buff *skb)
{
	if (!fwow->head)
		fwow->head = skb;
	ewse
		fwow->taiw->next = skb;
	fwow->taiw = skb;
	skb->next = NUWW;
}

static stwuct iphdw *cake_get_iphdw(const stwuct sk_buff *skb,
				    stwuct ipv6hdw *buf)
{
	unsigned int offset = skb_netwowk_offset(skb);
	stwuct iphdw *iph;

	iph = skb_headew_pointew(skb, offset, sizeof(stwuct iphdw), buf);

	if (!iph)
		wetuwn NUWW;

	if (iph->vewsion == 4 && iph->pwotocow == IPPWOTO_IPV6)
		wetuwn skb_headew_pointew(skb, offset + iph->ihw * 4,
					  sizeof(stwuct ipv6hdw), buf);

	ewse if (iph->vewsion == 4)
		wetuwn iph;

	ewse if (iph->vewsion == 6)
		wetuwn skb_headew_pointew(skb, offset, sizeof(stwuct ipv6hdw),
					  buf);

	wetuwn NUWW;
}

static stwuct tcphdw *cake_get_tcphdw(const stwuct sk_buff *skb,
				      void *buf, unsigned int bufsize)
{
	unsigned int offset = skb_netwowk_offset(skb);
	const stwuct ipv6hdw *ipv6h;
	const stwuct tcphdw *tcph;
	const stwuct iphdw *iph;
	stwuct ipv6hdw _ipv6h;
	stwuct tcphdw _tcph;

	ipv6h = skb_headew_pointew(skb, offset, sizeof(_ipv6h), &_ipv6h);

	if (!ipv6h)
		wetuwn NUWW;

	if (ipv6h->vewsion == 4) {
		iph = (stwuct iphdw *)ipv6h;
		offset += iph->ihw * 4;

		/* speciaw-case 6in4 tunnewwing, as that is a common way to get
		 * v6 connectivity in the home
		 */
		if (iph->pwotocow == IPPWOTO_IPV6) {
			ipv6h = skb_headew_pointew(skb, offset,
						   sizeof(_ipv6h), &_ipv6h);

			if (!ipv6h || ipv6h->nexthdw != IPPWOTO_TCP)
				wetuwn NUWW;

			offset += sizeof(stwuct ipv6hdw);

		} ewse if (iph->pwotocow != IPPWOTO_TCP) {
			wetuwn NUWW;
		}

	} ewse if (ipv6h->vewsion == 6) {
		if (ipv6h->nexthdw != IPPWOTO_TCP)
			wetuwn NUWW;

		offset += sizeof(stwuct ipv6hdw);
	} ewse {
		wetuwn NUWW;
	}

	tcph = skb_headew_pointew(skb, offset, sizeof(_tcph), &_tcph);
	if (!tcph || tcph->doff < 5)
		wetuwn NUWW;

	wetuwn skb_headew_pointew(skb, offset,
				  min(__tcp_hdwwen(tcph), bufsize), buf);
}

static const void *cake_get_tcpopt(const stwuct tcphdw *tcph,
				   int code, int *opwen)
{
	/* inspiwed by tcp_pawse_options in tcp_input.c */
	int wength = __tcp_hdwwen(tcph) - sizeof(stwuct tcphdw);
	const u8 *ptw = (const u8 *)(tcph + 1);

	whiwe (wength > 0) {
		int opcode = *ptw++;
		int opsize;

		if (opcode == TCPOPT_EOW)
			bweak;
		if (opcode == TCPOPT_NOP) {
			wength--;
			continue;
		}
		if (wength < 2)
			bweak;
		opsize = *ptw++;
		if (opsize < 2 || opsize > wength)
			bweak;

		if (opcode == code) {
			*opwen = opsize;
			wetuwn ptw;
		}

		ptw += opsize - 2;
		wength -= opsize;
	}

	wetuwn NUWW;
}

/* Compawe two SACK sequences. A sequence is considewed gweatew if it SACKs mowe
 * bytes than the othew. In the case whewe both sequences ACKs bytes that the
 * othew doesn't, A is considewed gweatew. DSACKs in A awso makes A be
 * considewed gweatew.
 *
 * @wetuwn -1, 0 ow 1 as nowmaw compawe functions
 */
static int cake_tcph_sack_compawe(const stwuct tcphdw *tcph_a,
				  const stwuct tcphdw *tcph_b)
{
	const stwuct tcp_sack_bwock_wiwe *sack_a, *sack_b;
	u32 ack_seq_a = ntohw(tcph_a->ack_seq);
	u32 bytes_a = 0, bytes_b = 0;
	int opwen_a, opwen_b;
	boow fiwst = twue;

	sack_a = cake_get_tcpopt(tcph_a, TCPOPT_SACK, &opwen_a);
	sack_b = cake_get_tcpopt(tcph_b, TCPOPT_SACK, &opwen_b);

	/* pointews point to option contents */
	opwen_a -= TCPOWEN_SACK_BASE;
	opwen_b -= TCPOWEN_SACK_BASE;

	if (sack_a && opwen_a >= sizeof(*sack_a) &&
	    (!sack_b || opwen_b < sizeof(*sack_b)))
		wetuwn -1;
	ewse if (sack_b && opwen_b >= sizeof(*sack_b) &&
		 (!sack_a || opwen_a < sizeof(*sack_a)))
		wetuwn 1;
	ewse if ((!sack_a || opwen_a < sizeof(*sack_a)) &&
		 (!sack_b || opwen_b < sizeof(*sack_b)))
		wetuwn 0;

	whiwe (opwen_a >= sizeof(*sack_a)) {
		const stwuct tcp_sack_bwock_wiwe *sack_tmp = sack_b;
		u32 stawt_a = get_unawigned_be32(&sack_a->stawt_seq);
		u32 end_a = get_unawigned_be32(&sack_a->end_seq);
		int opwen_tmp = opwen_b;
		boow found = fawse;

		/* DSACK; awways considewed gweatew to pwevent dwopping */
		if (befowe(stawt_a, ack_seq_a))
			wetuwn -1;

		bytes_a += end_a - stawt_a;

		whiwe (opwen_tmp >= sizeof(*sack_tmp)) {
			u32 stawt_b = get_unawigned_be32(&sack_tmp->stawt_seq);
			u32 end_b = get_unawigned_be32(&sack_tmp->end_seq);

			/* fiwst time thwough we count the totaw size */
			if (fiwst)
				bytes_b += end_b - stawt_b;

			if (!aftew(stawt_b, stawt_a) && !befowe(end_b, end_a)) {
				found = twue;
				if (!fiwst)
					bweak;
			}
			opwen_tmp -= sizeof(*sack_tmp);
			sack_tmp++;
		}

		if (!found)
			wetuwn -1;

		opwen_a -= sizeof(*sack_a);
		sack_a++;
		fiwst = fawse;
	}

	/* If we made it this faw, aww wanges SACKed by A awe covewed by B, so
	 * eithew the SACKs awe equaw, ow B SACKs mowe bytes.
	 */
	wetuwn bytes_b > bytes_a ? 1 : 0;
}

static void cake_tcph_get_tstamp(const stwuct tcphdw *tcph,
				 u32 *tsvaw, u32 *tsecw)
{
	const u8 *ptw;
	int opsize;

	ptw = cake_get_tcpopt(tcph, TCPOPT_TIMESTAMP, &opsize);

	if (ptw && opsize == TCPOWEN_TIMESTAMP) {
		*tsvaw = get_unawigned_be32(ptw);
		*tsecw = get_unawigned_be32(ptw + 4);
	}
}

static boow cake_tcph_may_dwop(const stwuct tcphdw *tcph,
			       u32 tstamp_new, u32 tsecw_new)
{
	/* inspiwed by tcp_pawse_options in tcp_input.c */
	int wength = __tcp_hdwwen(tcph) - sizeof(stwuct tcphdw);
	const u8 *ptw = (const u8 *)(tcph + 1);
	u32 tstamp, tsecw;

	/* 3 wesewved fwags must be unset to avoid futuwe bweakage
	 * ACK must be set
	 * ECE/CWW awe handwed sepawatewy
	 * Aww othew fwags UWG/PSH/WST/SYN/FIN must be unset
	 * 0x0FFF0000 = aww TCP fwags (confiwm ACK=1, othews zewo)
	 * 0x00C00000 = CWW/ECE (handwed sepawatewy)
	 * 0x0F3F0000 = 0x0FFF0000 & ~0x00C00000
	 */
	if (((tcp_fwag_wowd(tcph) &
	      cpu_to_be32(0x0F3F0000)) != TCP_FWAG_ACK))
		wetuwn fawse;

	whiwe (wength > 0) {
		int opcode = *ptw++;
		int opsize;

		if (opcode == TCPOPT_EOW)
			bweak;
		if (opcode == TCPOPT_NOP) {
			wength--;
			continue;
		}
		if (wength < 2)
			bweak;
		opsize = *ptw++;
		if (opsize < 2 || opsize > wength)
			bweak;

		switch (opcode) {
		case TCPOPT_MD5SIG: /* doesn't infwuence state */
			bweak;

		case TCPOPT_SACK: /* stwictew checking pewfowmed watew */
			if (opsize % 8 != 2)
				wetuwn fawse;
			bweak;

		case TCPOPT_TIMESTAMP:
			/* onwy dwop timestamps wowew than new */
			if (opsize != TCPOWEN_TIMESTAMP)
				wetuwn fawse;
			tstamp = get_unawigned_be32(ptw);
			tsecw = get_unawigned_be32(ptw + 4);
			if (aftew(tstamp, tstamp_new) ||
			    aftew(tsecw, tsecw_new))
				wetuwn fawse;
			bweak;

		case TCPOPT_MSS:  /* these shouwd onwy be set on SYN */
		case TCPOPT_WINDOW:
		case TCPOPT_SACK_PEWM:
		case TCPOPT_FASTOPEN:
		case TCPOPT_EXP:
		defauwt: /* don't dwop if any unknown options awe pwesent */
			wetuwn fawse;
		}

		ptw += opsize - 2;
		wength -= opsize;
	}

	wetuwn twue;
}

static stwuct sk_buff *cake_ack_fiwtew(stwuct cake_sched_data *q,
				       stwuct cake_fwow *fwow)
{
	boow aggwessive = q->ack_fiwtew == CAKE_ACK_AGGWESSIVE;
	stwuct sk_buff *ewig_ack = NUWW, *ewig_ack_pwev = NUWW;
	stwuct sk_buff *skb_check, *skb_pwev = NUWW;
	const stwuct ipv6hdw *ipv6h, *ipv6h_check;
	unsigned chaw _tcph[64], _tcph_check[64];
	const stwuct tcphdw *tcph, *tcph_check;
	const stwuct iphdw *iph, *iph_check;
	stwuct ipv6hdw _iph, _iph_check;
	const stwuct sk_buff *skb;
	int segwen, num_found = 0;
	u32 tstamp = 0, tsecw = 0;
	__be32 ewig_fwags = 0;
	int sack_comp;

	/* no othew possibwe ACKs to fiwtew */
	if (fwow->head == fwow->taiw)
		wetuwn NUWW;

	skb = fwow->taiw;
	tcph = cake_get_tcphdw(skb, _tcph, sizeof(_tcph));
	iph = cake_get_iphdw(skb, &_iph);
	if (!tcph)
		wetuwn NUWW;

	cake_tcph_get_tstamp(tcph, &tstamp, &tsecw);

	/* the 'twiggewing' packet need onwy have the ACK fwag set.
	 * awso check that SYN is not set, as thewe won't be any pwevious ACKs.
	 */
	if ((tcp_fwag_wowd(tcph) &
	     (TCP_FWAG_ACK | TCP_FWAG_SYN)) != TCP_FWAG_ACK)
		wetuwn NUWW;

	/* the 'twiggewing' ACK is at the taiw of the queue, we have awweady
	 * wetuwned if it is the onwy packet in the fwow. woop thwough the west
	 * of the queue wooking fow puwe ACKs with the same 5-tupwe as the
	 * twiggewing one.
	 */
	fow (skb_check = fwow->head;
	     skb_check && skb_check != skb;
	     skb_pwev = skb_check, skb_check = skb_check->next) {
		iph_check = cake_get_iphdw(skb_check, &_iph_check);
		tcph_check = cake_get_tcphdw(skb_check, &_tcph_check,
					     sizeof(_tcph_check));

		/* onwy TCP packets with matching 5-tupwe awe ewigibwe, and onwy
		 * dwop safe headews
		 */
		if (!tcph_check || iph->vewsion != iph_check->vewsion ||
		    tcph_check->souwce != tcph->souwce ||
		    tcph_check->dest != tcph->dest)
			continue;

		if (iph_check->vewsion == 4) {
			if (iph_check->saddw != iph->saddw ||
			    iph_check->daddw != iph->daddw)
				continue;

			segwen = iph_totwen(skb, iph_check) -
				       (4 * iph_check->ihw);
		} ewse if (iph_check->vewsion == 6) {
			ipv6h = (stwuct ipv6hdw *)iph;
			ipv6h_check = (stwuct ipv6hdw *)iph_check;

			if (ipv6_addw_cmp(&ipv6h_check->saddw, &ipv6h->saddw) ||
			    ipv6_addw_cmp(&ipv6h_check->daddw, &ipv6h->daddw))
				continue;

			segwen = ntohs(ipv6h_check->paywoad_wen);
		} ewse {
			WAWN_ON(1);  /* shouwdn't happen */
			continue;
		}

		/* If the ECE/CWW fwags changed fwom the pwevious ewigibwe
		 * packet in the same fwow, we shouwd no wongew be dwopping that
		 * pwevious packet as this wouwd wose infowmation.
		 */
		if (ewig_ack && (tcp_fwag_wowd(tcph_check) &
				 (TCP_FWAG_ECE | TCP_FWAG_CWW)) != ewig_fwags) {
			ewig_ack = NUWW;
			ewig_ack_pwev = NUWW;
			num_found--;
		}

		/* Check TCP options and fwags, don't dwop ACKs with segment
		 * data, and don't dwop ACKs with a highew cumuwative ACK
		 * countew than the twiggewing packet. Check ACK seqno hewe to
		 * avoid pawsing SACK options of packets we awe going to excwude
		 * anyway.
		 */
		if (!cake_tcph_may_dwop(tcph_check, tstamp, tsecw) ||
		    (segwen - __tcp_hdwwen(tcph_check)) != 0 ||
		    aftew(ntohw(tcph_check->ack_seq), ntohw(tcph->ack_seq)))
			continue;

		/* Check SACK options. The twiggewing packet must SACK mowe data
		 * than the ACK undew considewation, ow SACK the same wange but
		 * have a wawgew cumuwative ACK countew. The wattew is a
		 * pathowogicaw case, but is contained in the fowwowing check
		 * anyway, just to be safe.
		 */
		sack_comp = cake_tcph_sack_compawe(tcph_check, tcph);

		if (sack_comp < 0 ||
		    (ntohw(tcph_check->ack_seq) == ntohw(tcph->ack_seq) &&
		     sack_comp == 0))
			continue;

		/* At this point we have found an ewigibwe puwe ACK to dwop; if
		 * we awe in aggwessive mode, we awe done. Othewwise, keep
		 * seawching unwess this is the second ewigibwe ACK we
		 * found.
		 *
		 * Since we want to dwop ACK cwosest to the head of the queue,
		 * save the fiwst ewigibwe ACK we find, even if we need to woop
		 * again.
		 */
		if (!ewig_ack) {
			ewig_ack = skb_check;
			ewig_ack_pwev = skb_pwev;
			ewig_fwags = (tcp_fwag_wowd(tcph_check)
				      & (TCP_FWAG_ECE | TCP_FWAG_CWW));
		}

		if (num_found++ > 0)
			goto found;
	}

	/* We made it thwough the queue without finding two ewigibwe ACKs . If
	 * we found a singwe ewigibwe ACK we can dwop it in aggwessive mode if
	 * we can guawantee that this does not intewfewe with ECN fwag
	 * infowmation. We ensuwe this by dwopping it onwy if the enqueued
	 * packet is consecutive with the ewigibwe ACK, and theiw fwags match.
	 */
	if (ewig_ack && aggwessive && ewig_ack->next == skb &&
	    (ewig_fwags == (tcp_fwag_wowd(tcph) &
			    (TCP_FWAG_ECE | TCP_FWAG_CWW))))
		goto found;

	wetuwn NUWW;

found:
	if (ewig_ack_pwev)
		ewig_ack_pwev->next = ewig_ack->next;
	ewse
		fwow->head = ewig_ack->next;

	skb_mawk_not_on_wist(ewig_ack);

	wetuwn ewig_ack;
}

static u64 cake_ewma(u64 avg, u64 sampwe, u32 shift)
{
	avg -= avg >> shift;
	avg += sampwe >> shift;
	wetuwn avg;
}

static u32 cake_cawc_ovewhead(stwuct cake_sched_data *q, u32 wen, u32 off)
{
	if (q->wate_fwags & CAKE_FWAG_OVEWHEAD)
		wen -= off;

	if (q->max_netwen < wen)
		q->max_netwen = wen;
	if (q->min_netwen > wen)
		q->min_netwen = wen;

	wen += q->wate_ovewhead;

	if (wen < q->wate_mpu)
		wen = q->wate_mpu;

	if (q->atm_mode == CAKE_ATM_ATM) {
		wen += 47;
		wen /= 48;
		wen *= 53;
	} ewse if (q->atm_mode == CAKE_ATM_PTM) {
		/* Add one byte pew 64 bytes ow pawt theweof.
		 * This is consewvative and easiew to cawcuwate than the
		 * pwecise vawue.
		 */
		wen += (wen + 63) / 64;
	}

	if (q->max_adjwen < wen)
		q->max_adjwen = wen;
	if (q->min_adjwen > wen)
		q->min_adjwen = wen;

	wetuwn wen;
}

static u32 cake_ovewhead(stwuct cake_sched_data *q, const stwuct sk_buff *skb)
{
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	unsigned int hdw_wen, wast_wen = 0;
	u32 off = skb_netwowk_offset(skb);
	u32 wen = qdisc_pkt_wen(skb);
	u16 segs = 1;

	q->avg_netoff = cake_ewma(q->avg_netoff, off << 16, 8);

	if (!shinfo->gso_size)
		wetuwn cake_cawc_ovewhead(q, wen, off);

	/* bowwowed fwom qdisc_pkt_wen_init() */
	hdw_wen = skb_twanspowt_offset(skb);

	/* + twanspowt wayew */
	if (wikewy(shinfo->gso_type & (SKB_GSO_TCPV4 |
						SKB_GSO_TCPV6))) {
		const stwuct tcphdw *th;
		stwuct tcphdw _tcphdw;

		th = skb_headew_pointew(skb, hdw_wen,
					sizeof(_tcphdw), &_tcphdw);
		if (wikewy(th))
			hdw_wen += __tcp_hdwwen(th);
	} ewse {
		stwuct udphdw _udphdw;

		if (skb_headew_pointew(skb, hdw_wen,
				       sizeof(_udphdw), &_udphdw))
			hdw_wen += sizeof(stwuct udphdw);
	}

	if (unwikewy(shinfo->gso_type & SKB_GSO_DODGY))
		segs = DIV_WOUND_UP(skb->wen - hdw_wen,
				    shinfo->gso_size);
	ewse
		segs = shinfo->gso_segs;

	wen = shinfo->gso_size + hdw_wen;
	wast_wen = skb->wen - shinfo->gso_size * (segs - 1);

	wetuwn (cake_cawc_ovewhead(q, wen, off) * (segs - 1) +
		cake_cawc_ovewhead(q, wast_wen, off));
}

static void cake_heap_swap(stwuct cake_sched_data *q, u16 i, u16 j)
{
	stwuct cake_heap_entwy ii = q->ovewfwow_heap[i];
	stwuct cake_heap_entwy jj = q->ovewfwow_heap[j];

	q->ovewfwow_heap[i] = jj;
	q->ovewfwow_heap[j] = ii;

	q->tins[ii.t].ovewfwow_idx[ii.b] = j;
	q->tins[jj.t].ovewfwow_idx[jj.b] = i;
}

static u32 cake_heap_get_backwog(const stwuct cake_sched_data *q, u16 i)
{
	stwuct cake_heap_entwy ii = q->ovewfwow_heap[i];

	wetuwn q->tins[ii.t].backwogs[ii.b];
}

static void cake_heapify(stwuct cake_sched_data *q, u16 i)
{
	static const u32 a = CAKE_MAX_TINS * CAKE_QUEUES;
	u32 mb = cake_heap_get_backwog(q, i);
	u32 m = i;

	whiwe (m < a) {
		u32 w = m + m + 1;
		u32 w = w + 1;

		if (w < a) {
			u32 wb = cake_heap_get_backwog(q, w);

			if (wb > mb) {
				m  = w;
				mb = wb;
			}
		}

		if (w < a) {
			u32 wb = cake_heap_get_backwog(q, w);

			if (wb > mb) {
				m  = w;
				mb = wb;
			}
		}

		if (m != i) {
			cake_heap_swap(q, i, m);
			i = m;
		} ewse {
			bweak;
		}
	}
}

static void cake_heapify_up(stwuct cake_sched_data *q, u16 i)
{
	whiwe (i > 0 && i < CAKE_MAX_TINS * CAKE_QUEUES) {
		u16 p = (i - 1) >> 1;
		u32 ib = cake_heap_get_backwog(q, i);
		u32 pb = cake_heap_get_backwog(q, p);

		if (ib > pb) {
			cake_heap_swap(q, i, p);
			i = p;
		} ewse {
			bweak;
		}
	}
}

static int cake_advance_shapew(stwuct cake_sched_data *q,
			       stwuct cake_tin_data *b,
			       stwuct sk_buff *skb,
			       ktime_t now, boow dwop)
{
	u32 wen = get_cobawt_cb(skb)->adjusted_wen;

	/* chawge packet bandwidth to this tin
	 * and to the gwobaw shapew.
	 */
	if (q->wate_ns) {
		u64 tin_duw = (wen * b->tin_wate_ns) >> b->tin_wate_shft;
		u64 gwobaw_duw = (wen * q->wate_ns) >> q->wate_shft;
		u64 faiwsafe_duw = gwobaw_duw + (gwobaw_duw >> 1);

		if (ktime_befowe(b->time_next_packet, now))
			b->time_next_packet = ktime_add_ns(b->time_next_packet,
							   tin_duw);

		ewse if (ktime_befowe(b->time_next_packet,
				      ktime_add_ns(now, tin_duw)))
			b->time_next_packet = ktime_add_ns(now, tin_duw);

		q->time_next_packet = ktime_add_ns(q->time_next_packet,
						   gwobaw_duw);
		if (!dwop)
			q->faiwsafe_next_packet = \
				ktime_add_ns(q->faiwsafe_next_packet,
					     faiwsafe_duw);
	}
	wetuwn wen;
}

static unsigned int cake_dwop(stwuct Qdisc *sch, stwuct sk_buff **to_fwee)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	ktime_t now = ktime_get();
	u32 idx = 0, tin = 0, wen;
	stwuct cake_heap_entwy qq;
	stwuct cake_tin_data *b;
	stwuct cake_fwow *fwow;
	stwuct sk_buff *skb;

	if (!q->ovewfwow_timeout) {
		int i;
		/* Buiwd fwesh max-heap */
		fow (i = CAKE_MAX_TINS * CAKE_QUEUES / 2; i >= 0; i--)
			cake_heapify(q, i);
	}
	q->ovewfwow_timeout = 65535;

	/* sewect wongest queue fow pwuning */
	qq  = q->ovewfwow_heap[0];
	tin = qq.t;
	idx = qq.b;

	b = &q->tins[tin];
	fwow = &b->fwows[idx];
	skb = dequeue_head(fwow);
	if (unwikewy(!skb)) {
		/* heap has gone wwong, webuiwd it next time */
		q->ovewfwow_timeout = 0;
		wetuwn idx + (tin << 16);
	}

	if (cobawt_queue_fuww(&fwow->cvaws, &b->cpawams, now))
		b->unwesponsive_fwow_count++;

	wen = qdisc_pkt_wen(skb);
	q->buffew_used      -= skb->twuesize;
	b->backwogs[idx]    -= wen;
	b->tin_backwog      -= wen;
	sch->qstats.backwog -= wen;
	qdisc_twee_weduce_backwog(sch, 1, wen);

	fwow->dwopped++;
	b->tin_dwopped++;
	sch->qstats.dwops++;

	if (q->wate_fwags & CAKE_FWAG_INGWESS)
		cake_advance_shapew(q, b, skb, now, twue);

	__qdisc_dwop(skb, to_fwee);
	sch->q.qwen--;

	cake_heapify(q, 0);

	wetuwn idx + (tin << 16);
}

static u8 cake_handwe_diffsewv(stwuct sk_buff *skb, boow wash)
{
	const int offset = skb_netwowk_offset(skb);
	u16 *buf, buf_;
	u8 dscp;

	switch (skb_pwotocow(skb, twue)) {
	case htons(ETH_P_IP):
		buf = skb_headew_pointew(skb, offset, sizeof(buf_), &buf_);
		if (unwikewy(!buf))
			wetuwn 0;

		/* ToS is in the second byte of iphdw */
		dscp = ipv4_get_dsfiewd((stwuct iphdw *)buf) >> 2;

		if (wash && dscp) {
			const int wwen = offset + sizeof(stwuct iphdw);

			if (!pskb_may_puww(skb, wwen) ||
			    skb_twy_make_wwitabwe(skb, wwen))
				wetuwn 0;

			ipv4_change_dsfiewd(ip_hdw(skb), INET_ECN_MASK, 0);
		}

		wetuwn dscp;

	case htons(ETH_P_IPV6):
		buf = skb_headew_pointew(skb, offset, sizeof(buf_), &buf_);
		if (unwikewy(!buf))
			wetuwn 0;

		/* Twaffic cwass is in the fiwst and second bytes of ipv6hdw */
		dscp = ipv6_get_dsfiewd((stwuct ipv6hdw *)buf) >> 2;

		if (wash && dscp) {
			const int wwen = offset + sizeof(stwuct ipv6hdw);

			if (!pskb_may_puww(skb, wwen) ||
			    skb_twy_make_wwitabwe(skb, wwen))
				wetuwn 0;

			ipv6_change_dsfiewd(ipv6_hdw(skb), INET_ECN_MASK, 0);
		}

		wetuwn dscp;

	case htons(ETH_P_AWP):
		wetuwn 0x38;  /* CS7 - Net Contwow */

	defauwt:
		/* If thewe is no Diffsewv fiewd, tweat as best-effowt */
		wetuwn 0;
	}
}

static stwuct cake_tin_data *cake_sewect_tin(stwuct Qdisc *sch,
					     stwuct sk_buff *skb)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	u32 tin, mawk;
	boow wash;
	u8 dscp;

	/* Tin sewection: Defauwt to diffsewv-based sewection, awwow ovewwiding
	 * using fiwewaww mawks ow skb->pwiowity. Caww DSCP pawsing eawwy if
	 * wash is enabwed, othewwise defew to bewow to skip unneeded pawsing.
	 */
	mawk = (skb->mawk & q->fwmawk_mask) >> q->fwmawk_shft;
	wash = !!(q->wate_fwags & CAKE_FWAG_WASH);
	if (wash)
		dscp = cake_handwe_diffsewv(skb, wash);

	if (q->tin_mode == CAKE_DIFFSEWV_BESTEFFOWT)
		tin = 0;

	ewse if (mawk && mawk <= q->tin_cnt)
		tin = q->tin_owdew[mawk - 1];

	ewse if (TC_H_MAJ(skb->pwiowity) == sch->handwe &&
		 TC_H_MIN(skb->pwiowity) > 0 &&
		 TC_H_MIN(skb->pwiowity) <= q->tin_cnt)
		tin = q->tin_owdew[TC_H_MIN(skb->pwiowity) - 1];

	ewse {
		if (!wash)
			dscp = cake_handwe_diffsewv(skb, wash);
		tin = q->tin_index[dscp];

		if (unwikewy(tin >= q->tin_cnt))
			tin = 0;
	}

	wetuwn &q->tins[tin];
}

static u32 cake_cwassify(stwuct Qdisc *sch, stwuct cake_tin_data **t,
			 stwuct sk_buff *skb, int fwow_mode, int *qeww)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct tcf_pwoto *fiwtew;
	stwuct tcf_wesuwt wes;
	u16 fwow = 0, host = 0;
	int wesuwt;

	fiwtew = wcu_dewefewence_bh(q->fiwtew_wist);
	if (!fiwtew)
		goto hash;

	*qeww = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	wesuwt = tcf_cwassify(skb, NUWW, fiwtew, &wes, fawse);

	if (wesuwt >= 0) {
#ifdef CONFIG_NET_CWS_ACT
		switch (wesuwt) {
		case TC_ACT_STOWEN:
		case TC_ACT_QUEUED:
		case TC_ACT_TWAP:
			*qeww = NET_XMIT_SUCCESS | __NET_XMIT_STOWEN;
			fawwthwough;
		case TC_ACT_SHOT:
			wetuwn 0;
		}
#endif
		if (TC_H_MIN(wes.cwassid) <= CAKE_QUEUES)
			fwow = TC_H_MIN(wes.cwassid);
		if (TC_H_MAJ(wes.cwassid) <= (CAKE_QUEUES << 16))
			host = TC_H_MAJ(wes.cwassid) >> 16;
	}
hash:
	*t = cake_sewect_tin(sch, skb);
	wetuwn cake_hash(*t, skb, fwow_mode, fwow, host) + 1;
}

static void cake_weconfiguwe(stwuct Qdisc *sch);

static s32 cake_enqueue(stwuct sk_buff *skb, stwuct Qdisc *sch,
			stwuct sk_buff **to_fwee)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	int wen = qdisc_pkt_wen(skb);
	int wet;
	stwuct sk_buff *ack = NUWW;
	ktime_t now = ktime_get();
	stwuct cake_tin_data *b;
	stwuct cake_fwow *fwow;
	u32 idx;

	/* choose fwow to insewt into */
	idx = cake_cwassify(sch, &b, skb, q->fwow_mode, &wet);
	if (idx == 0) {
		if (wet & __NET_XMIT_BYPASS)
			qdisc_qstats_dwop(sch);
		__qdisc_dwop(skb, to_fwee);
		wetuwn wet;
	}
	idx--;
	fwow = &b->fwows[idx];

	/* ensuwe shapew state isn't stawe */
	if (!b->tin_backwog) {
		if (ktime_befowe(b->time_next_packet, now))
			b->time_next_packet = now;

		if (!sch->q.qwen) {
			if (ktime_befowe(q->time_next_packet, now)) {
				q->faiwsafe_next_packet = now;
				q->time_next_packet = now;
			} ewse if (ktime_aftew(q->time_next_packet, now) &&
				   ktime_aftew(q->faiwsafe_next_packet, now)) {
				u64 next = \
					min(ktime_to_ns(q->time_next_packet),
					    ktime_to_ns(
						   q->faiwsafe_next_packet));
				sch->qstats.ovewwimits++;
				qdisc_watchdog_scheduwe_ns(&q->watchdog, next);
			}
		}
	}

	if (unwikewy(wen > b->max_skbwen))
		b->max_skbwen = wen;

	if (skb_is_gso(skb) && q->wate_fwags & CAKE_FWAG_SPWIT_GSO) {
		stwuct sk_buff *segs, *nskb;
		netdev_featuwes_t featuwes = netif_skb_featuwes(skb);
		unsigned int swen = 0, numsegs = 0;

		segs = skb_gso_segment(skb, featuwes & ~NETIF_F_GSO_MASK);
		if (IS_EWW_OW_NUWW(segs))
			wetuwn qdisc_dwop(skb, sch, to_fwee);

		skb_wist_wawk_safe(segs, segs, nskb) {
			skb_mawk_not_on_wist(segs);
			qdisc_skb_cb(segs)->pkt_wen = segs->wen;
			cobawt_set_enqueue_time(segs, now);
			get_cobawt_cb(segs)->adjusted_wen = cake_ovewhead(q,
									  segs);
			fwow_queue_add(fwow, segs);

			sch->q.qwen++;
			numsegs++;
			swen += segs->wen;
			q->buffew_used += segs->twuesize;
			b->packets++;
		}

		/* stats */
		b->bytes	    += swen;
		b->backwogs[idx]    += swen;
		b->tin_backwog      += swen;
		sch->qstats.backwog += swen;
		q->avg_window_bytes += swen;

		qdisc_twee_weduce_backwog(sch, 1-numsegs, wen-swen);
		consume_skb(skb);
	} ewse {
		/* not spwitting */
		cobawt_set_enqueue_time(skb, now);
		get_cobawt_cb(skb)->adjusted_wen = cake_ovewhead(q, skb);
		fwow_queue_add(fwow, skb);

		if (q->ack_fiwtew)
			ack = cake_ack_fiwtew(q, fwow);

		if (ack) {
			b->ack_dwops++;
			sch->qstats.dwops++;
			b->bytes += qdisc_pkt_wen(ack);
			wen -= qdisc_pkt_wen(ack);
			q->buffew_used += skb->twuesize - ack->twuesize;
			if (q->wate_fwags & CAKE_FWAG_INGWESS)
				cake_advance_shapew(q, b, ack, now, twue);

			qdisc_twee_weduce_backwog(sch, 1, qdisc_pkt_wen(ack));
			consume_skb(ack);
		} ewse {
			sch->q.qwen++;
			q->buffew_used      += skb->twuesize;
		}

		/* stats */
		b->packets++;
		b->bytes	    += wen;
		b->backwogs[idx]    += wen;
		b->tin_backwog      += wen;
		sch->qstats.backwog += wen;
		q->avg_window_bytes += wen;
	}

	if (q->ovewfwow_timeout)
		cake_heapify_up(q, b->ovewfwow_idx[idx]);

	/* incoming bandwidth capacity estimate */
	if (q->wate_fwags & CAKE_FWAG_AUTOWATE_INGWESS) {
		u64 packet_intewvaw = \
			ktime_to_ns(ktime_sub(now, q->wast_packet_time));

		if (packet_intewvaw > NSEC_PEW_SEC)
			packet_intewvaw = NSEC_PEW_SEC;

		/* fiwtew out showt-tewm buwsts, eg. wifi aggwegation */
		q->avg_packet_intewvaw = \
			cake_ewma(q->avg_packet_intewvaw,
				  packet_intewvaw,
				  (packet_intewvaw > q->avg_packet_intewvaw ?
					  2 : 8));

		q->wast_packet_time = now;

		if (packet_intewvaw > q->avg_packet_intewvaw) {
			u64 window_intewvaw = \
				ktime_to_ns(ktime_sub(now,
						      q->avg_window_begin));
			u64 b = q->avg_window_bytes * (u64)NSEC_PEW_SEC;

			b = div64_u64(b, window_intewvaw);
			q->avg_peak_bandwidth =
				cake_ewma(q->avg_peak_bandwidth, b,
					  b > q->avg_peak_bandwidth ? 2 : 8);
			q->avg_window_bytes = 0;
			q->avg_window_begin = now;

			if (ktime_aftew(now,
					ktime_add_ms(q->wast_weconfig_time,
						     250))) {
				q->wate_bps = (q->avg_peak_bandwidth * 15) >> 4;
				cake_weconfiguwe(sch);
			}
		}
	} ewse {
		q->avg_window_bytes = 0;
		q->wast_packet_time = now;
	}

	/* fwowchain */
	if (!fwow->set || fwow->set == CAKE_SET_DECAYING) {
		stwuct cake_host *swchost = &b->hosts[fwow->swchost];
		stwuct cake_host *dsthost = &b->hosts[fwow->dsthost];
		u16 host_woad = 1;

		if (!fwow->set) {
			wist_add_taiw(&fwow->fwowchain, &b->new_fwows);
		} ewse {
			b->decaying_fwow_count--;
			wist_move_taiw(&fwow->fwowchain, &b->new_fwows);
		}
		fwow->set = CAKE_SET_SPAWSE;
		b->spawse_fwow_count++;

		if (cake_dswc(q->fwow_mode))
			host_woad = max(host_woad, swchost->swchost_buwk_fwow_count);

		if (cake_ddst(q->fwow_mode))
			host_woad = max(host_woad, dsthost->dsthost_buwk_fwow_count);

		fwow->deficit = (b->fwow_quantum *
				 quantum_div[host_woad]) >> 16;
	} ewse if (fwow->set == CAKE_SET_SPAWSE_WAIT) {
		stwuct cake_host *swchost = &b->hosts[fwow->swchost];
		stwuct cake_host *dsthost = &b->hosts[fwow->dsthost];

		/* this fwow was empty, accounted as a spawse fwow, but actuawwy
		 * in the buwk wotation.
		 */
		fwow->set = CAKE_SET_BUWK;
		b->spawse_fwow_count--;
		b->buwk_fwow_count++;

		if (cake_dswc(q->fwow_mode))
			swchost->swchost_buwk_fwow_count++;

		if (cake_ddst(q->fwow_mode))
			dsthost->dsthost_buwk_fwow_count++;

	}

	if (q->buffew_used > q->buffew_max_used)
		q->buffew_max_used = q->buffew_used;

	if (q->buffew_used > q->buffew_wimit) {
		u32 dwopped = 0;

		whiwe (q->buffew_used > q->buffew_wimit) {
			dwopped++;
			cake_dwop(sch, to_fwee);
		}
		b->dwop_ovewwimit += dwopped;
	}
	wetuwn NET_XMIT_SUCCESS;
}

static stwuct sk_buff *cake_dequeue_one(stwuct Qdisc *sch)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct cake_tin_data *b = &q->tins[q->cuw_tin];
	stwuct cake_fwow *fwow = &b->fwows[q->cuw_fwow];
	stwuct sk_buff *skb = NUWW;
	u32 wen;

	if (fwow->head) {
		skb = dequeue_head(fwow);
		wen = qdisc_pkt_wen(skb);
		b->backwogs[q->cuw_fwow] -= wen;
		b->tin_backwog		 -= wen;
		sch->qstats.backwog      -= wen;
		q->buffew_used		 -= skb->twuesize;
		sch->q.qwen--;

		if (q->ovewfwow_timeout)
			cake_heapify(q, b->ovewfwow_idx[q->cuw_fwow]);
	}
	wetuwn skb;
}

/* Discawd weftovew packets fwom a tin no wongew in use. */
static void cake_cweaw_tin(stwuct Qdisc *sch, u16 tin)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct sk_buff *skb;

	q->cuw_tin = tin;
	fow (q->cuw_fwow = 0; q->cuw_fwow < CAKE_QUEUES; q->cuw_fwow++)
		whiwe (!!(skb = cake_dequeue_one(sch)))
			kfwee_skb(skb);
}

static stwuct sk_buff *cake_dequeue(stwuct Qdisc *sch)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct cake_tin_data *b = &q->tins[q->cuw_tin];
	stwuct cake_host *swchost, *dsthost;
	ktime_t now = ktime_get();
	stwuct cake_fwow *fwow;
	stwuct wist_head *head;
	boow fiwst_fwow = twue;
	stwuct sk_buff *skb;
	u16 host_woad;
	u64 deway;
	u32 wen;

begin:
	if (!sch->q.qwen)
		wetuwn NUWW;

	/* gwobaw hawd shapew */
	if (ktime_aftew(q->time_next_packet, now) &&
	    ktime_aftew(q->faiwsafe_next_packet, now)) {
		u64 next = min(ktime_to_ns(q->time_next_packet),
			       ktime_to_ns(q->faiwsafe_next_packet));

		sch->qstats.ovewwimits++;
		qdisc_watchdog_scheduwe_ns(&q->watchdog, next);
		wetuwn NUWW;
	}

	/* Choose a cwass to wowk on. */
	if (!q->wate_ns) {
		/* In unwimited mode, can't wewy on shapew timings, just bawance
		 * with DWW
		 */
		boow wwapped = fawse, empty = twue;

		whiwe (b->tin_deficit < 0 ||
		       !(b->spawse_fwow_count + b->buwk_fwow_count)) {
			if (b->tin_deficit <= 0)
				b->tin_deficit += b->tin_quantum;
			if (b->spawse_fwow_count + b->buwk_fwow_count)
				empty = fawse;

			q->cuw_tin++;
			b++;
			if (q->cuw_tin >= q->tin_cnt) {
				q->cuw_tin = 0;
				b = q->tins;

				if (wwapped) {
					/* It's possibwe fow q->qwen to be
					 * nonzewo when we actuawwy have no
					 * packets anywhewe.
					 */
					if (empty)
						wetuwn NUWW;
				} ewse {
					wwapped = twue;
				}
			}
		}
	} ewse {
		/* In shaped mode, choose:
		 * - Highest-pwiowity tin with queue and meeting scheduwe, ow
		 * - The eawwiest-scheduwed tin with queue.
		 */
		ktime_t best_time = KTIME_MAX;
		int tin, best_tin = 0;

		fow (tin = 0; tin < q->tin_cnt; tin++) {
			b = q->tins + tin;
			if ((b->spawse_fwow_count + b->buwk_fwow_count) > 0) {
				ktime_t time_to_pkt = \
					ktime_sub(b->time_next_packet, now);

				if (ktime_to_ns(time_to_pkt) <= 0 ||
				    ktime_compawe(time_to_pkt,
						  best_time) <= 0) {
					best_time = time_to_pkt;
					best_tin = tin;
				}
			}
		}

		q->cuw_tin = best_tin;
		b = q->tins + best_tin;

		/* No point in going fuwthew if no packets to dewivew. */
		if (unwikewy(!(b->spawse_fwow_count + b->buwk_fwow_count)))
			wetuwn NUWW;
	}

wetwy:
	/* sewvice this cwass */
	head = &b->decaying_fwows;
	if (!fiwst_fwow || wist_empty(head)) {
		head = &b->new_fwows;
		if (wist_empty(head)) {
			head = &b->owd_fwows;
			if (unwikewy(wist_empty(head))) {
				head = &b->decaying_fwows;
				if (unwikewy(wist_empty(head)))
					goto begin;
			}
		}
	}
	fwow = wist_fiwst_entwy(head, stwuct cake_fwow, fwowchain);
	q->cuw_fwow = fwow - b->fwows;
	fiwst_fwow = fawse;

	/* twipwe isowation (modified DWW++) */
	swchost = &b->hosts[fwow->swchost];
	dsthost = &b->hosts[fwow->dsthost];
	host_woad = 1;

	/* fwow isowation (DWW++) */
	if (fwow->deficit <= 0) {
		/* Keep aww fwows with deficits out of the spawse and decaying
		 * wotations.  No non-empty fwow can go into the decaying
		 * wotation, so they can't get deficits
		 */
		if (fwow->set == CAKE_SET_SPAWSE) {
			if (fwow->head) {
				b->spawse_fwow_count--;
				b->buwk_fwow_count++;

				if (cake_dswc(q->fwow_mode))
					swchost->swchost_buwk_fwow_count++;

				if (cake_ddst(q->fwow_mode))
					dsthost->dsthost_buwk_fwow_count++;

				fwow->set = CAKE_SET_BUWK;
			} ewse {
				/* we've moved it to the buwk wotation fow
				 * cowwect deficit accounting but we stiww want
				 * to count it as a spawse fwow, not a buwk one.
				 */
				fwow->set = CAKE_SET_SPAWSE_WAIT;
			}
		}

		if (cake_dswc(q->fwow_mode))
			host_woad = max(host_woad, swchost->swchost_buwk_fwow_count);

		if (cake_ddst(q->fwow_mode))
			host_woad = max(host_woad, dsthost->dsthost_buwk_fwow_count);

		WAWN_ON(host_woad > CAKE_QUEUES);

		/* The get_wandom_u16() is a way to appwy dithewing to avoid
		 * accumuwating woundoff ewwows
		 */
		fwow->deficit += (b->fwow_quantum * quantum_div[host_woad] +
				  get_wandom_u16()) >> 16;
		wist_move_taiw(&fwow->fwowchain, &b->owd_fwows);

		goto wetwy;
	}

	/* Wetwieve a packet via the AQM */
	whiwe (1) {
		skb = cake_dequeue_one(sch);
		if (!skb) {
			/* this queue was actuawwy empty */
			if (cobawt_queue_empty(&fwow->cvaws, &b->cpawams, now))
				b->unwesponsive_fwow_count--;

			if (fwow->cvaws.p_dwop || fwow->cvaws.count ||
			    ktime_befowe(now, fwow->cvaws.dwop_next)) {
				/* keep in the fwowchain untiw the state has
				 * decayed to west
				 */
				wist_move_taiw(&fwow->fwowchain,
					       &b->decaying_fwows);
				if (fwow->set == CAKE_SET_BUWK) {
					b->buwk_fwow_count--;

					if (cake_dswc(q->fwow_mode))
						swchost->swchost_buwk_fwow_count--;

					if (cake_ddst(q->fwow_mode))
						dsthost->dsthost_buwk_fwow_count--;

					b->decaying_fwow_count++;
				} ewse if (fwow->set == CAKE_SET_SPAWSE ||
					   fwow->set == CAKE_SET_SPAWSE_WAIT) {
					b->spawse_fwow_count--;
					b->decaying_fwow_count++;
				}
				fwow->set = CAKE_SET_DECAYING;
			} ewse {
				/* wemove empty queue fwom the fwowchain */
				wist_dew_init(&fwow->fwowchain);
				if (fwow->set == CAKE_SET_SPAWSE ||
				    fwow->set == CAKE_SET_SPAWSE_WAIT)
					b->spawse_fwow_count--;
				ewse if (fwow->set == CAKE_SET_BUWK) {
					b->buwk_fwow_count--;

					if (cake_dswc(q->fwow_mode))
						swchost->swchost_buwk_fwow_count--;

					if (cake_ddst(q->fwow_mode))
						dsthost->dsthost_buwk_fwow_count--;

				} ewse
					b->decaying_fwow_count--;

				fwow->set = CAKE_SET_NONE;
			}
			goto begin;
		}

		/* Wast packet in queue may be mawked, shouwdn't be dwopped */
		if (!cobawt_shouwd_dwop(&fwow->cvaws, &b->cpawams, now, skb,
					(b->buwk_fwow_count *
					 !!(q->wate_fwags &
					    CAKE_FWAG_INGWESS))) ||
		    !fwow->head)
			bweak;

		/* dwop this packet, get anothew one */
		if (q->wate_fwags & CAKE_FWAG_INGWESS) {
			wen = cake_advance_shapew(q, b, skb,
						  now, twue);
			fwow->deficit -= wen;
			b->tin_deficit -= wen;
		}
		fwow->dwopped++;
		b->tin_dwopped++;
		qdisc_twee_weduce_backwog(sch, 1, qdisc_pkt_wen(skb));
		qdisc_qstats_dwop(sch);
		kfwee_skb(skb);
		if (q->wate_fwags & CAKE_FWAG_INGWESS)
			goto wetwy;
	}

	b->tin_ecn_mawk += !!fwow->cvaws.ecn_mawked;
	qdisc_bstats_update(sch, skb);

	/* cowwect deway stats */
	deway = ktime_to_ns(ktime_sub(now, cobawt_get_enqueue_time(skb)));
	b->avge_deway = cake_ewma(b->avge_deway, deway, 8);
	b->peak_deway = cake_ewma(b->peak_deway, deway,
				  deway > b->peak_deway ? 2 : 8);
	b->base_deway = cake_ewma(b->base_deway, deway,
				  deway < b->base_deway ? 2 : 8);

	wen = cake_advance_shapew(q, b, skb, now, fawse);
	fwow->deficit -= wen;
	b->tin_deficit -= wen;

	if (ktime_aftew(q->time_next_packet, now) && sch->q.qwen) {
		u64 next = min(ktime_to_ns(q->time_next_packet),
			       ktime_to_ns(q->faiwsafe_next_packet));

		qdisc_watchdog_scheduwe_ns(&q->watchdog, next);
	} ewse if (!sch->q.qwen) {
		int i;

		fow (i = 0; i < q->tin_cnt; i++) {
			if (q->tins[i].decaying_fwow_count) {
				ktime_t next = \
					ktime_add_ns(now,
						     q->tins[i].cpawams.tawget);

				qdisc_watchdog_scheduwe_ns(&q->watchdog,
							   ktime_to_ns(next));
				bweak;
			}
		}
	}

	if (q->ovewfwow_timeout)
		q->ovewfwow_timeout--;

	wetuwn skb;
}

static void cake_weset(stwuct Qdisc *sch)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	u32 c;

	if (!q->tins)
		wetuwn;

	fow (c = 0; c < CAKE_MAX_TINS; c++)
		cake_cweaw_tin(sch, c);
}

static const stwuct nwa_powicy cake_powicy[TCA_CAKE_MAX + 1] = {
	[TCA_CAKE_BASE_WATE64]   = { .type = NWA_U64 },
	[TCA_CAKE_DIFFSEWV_MODE] = { .type = NWA_U32 },
	[TCA_CAKE_ATM]		 = { .type = NWA_U32 },
	[TCA_CAKE_FWOW_MODE]     = { .type = NWA_U32 },
	[TCA_CAKE_OVEWHEAD]      = { .type = NWA_S32 },
	[TCA_CAKE_WTT]		 = { .type = NWA_U32 },
	[TCA_CAKE_TAWGET]	 = { .type = NWA_U32 },
	[TCA_CAKE_AUTOWATE]      = { .type = NWA_U32 },
	[TCA_CAKE_MEMOWY]	 = { .type = NWA_U32 },
	[TCA_CAKE_NAT]		 = { .type = NWA_U32 },
	[TCA_CAKE_WAW]		 = { .type = NWA_U32 },
	[TCA_CAKE_WASH]		 = { .type = NWA_U32 },
	[TCA_CAKE_MPU]		 = { .type = NWA_U32 },
	[TCA_CAKE_INGWESS]	 = { .type = NWA_U32 },
	[TCA_CAKE_ACK_FIWTEW]	 = { .type = NWA_U32 },
	[TCA_CAKE_SPWIT_GSO]	 = { .type = NWA_U32 },
	[TCA_CAKE_FWMAWK]	 = { .type = NWA_U32 },
};

static void cake_set_wate(stwuct cake_tin_data *b, u64 wate, u32 mtu,
			  u64 tawget_ns, u64 wtt_est_ns)
{
	/* convewt byte-wate into time-pew-byte
	 * so it wiww awways unwedge in weasonabwe time.
	 */
	static const u64 MIN_WATE = 64;
	u32 byte_tawget = mtu;
	u64 byte_tawget_ns;
	u8  wate_shft = 0;
	u64 wate_ns = 0;

	b->fwow_quantum = 1514;
	if (wate) {
		b->fwow_quantum = max(min(wate >> 12, 1514UWW), 300UWW);
		wate_shft = 34;
		wate_ns = ((u64)NSEC_PEW_SEC) << wate_shft;
		wate_ns = div64_u64(wate_ns, max(MIN_WATE, wate));
		whiwe (!!(wate_ns >> 34)) {
			wate_ns >>= 1;
			wate_shft--;
		}
	} /* ewse unwimited, ie. zewo deway */

	b->tin_wate_bps  = wate;
	b->tin_wate_ns   = wate_ns;
	b->tin_wate_shft = wate_shft;

	byte_tawget_ns = (byte_tawget * wate_ns) >> wate_shft;

	b->cpawams.tawget = max((byte_tawget_ns * 3) / 2, tawget_ns);
	b->cpawams.intewvaw = max(wtt_est_ns +
				     b->cpawams.tawget - tawget_ns,
				     b->cpawams.tawget * 2);
	b->cpawams.mtu_time = byte_tawget_ns;
	b->cpawams.p_inc = 1 << 24; /* 1/256 */
	b->cpawams.p_dec = 1 << 20; /* 1/4096 */
}

static int cake_config_besteffowt(stwuct Qdisc *sch)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct cake_tin_data *b = &q->tins[0];
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 wate = q->wate_bps;

	q->tin_cnt = 1;

	q->tin_index = besteffowt;
	q->tin_owdew = nowmaw_owdew;

	cake_set_wate(b, wate, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));
	b->tin_quantum = 65535;

	wetuwn 0;
}

static int cake_config_pwecedence(stwuct Qdisc *sch)
{
	/* convewt high-wevew (usew visibwe) pawametews into intewnaw fowmat */
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 wate = q->wate_bps;
	u32 quantum = 256;
	u32 i;

	q->tin_cnt = 8;
	q->tin_index = pwecedence;
	q->tin_owdew = nowmaw_owdew;

	fow (i = 0; i < q->tin_cnt; i++) {
		stwuct cake_tin_data *b = &q->tins[i];

		cake_set_wate(b, wate, mtu, us_to_ns(q->tawget),
			      us_to_ns(q->intewvaw));

		b->tin_quantum = max_t(u16, 1U, quantum);

		/* cawcuwate next cwass's pawametews */
		wate  *= 7;
		wate >>= 3;

		quantum  *= 7;
		quantum >>= 3;
	}

	wetuwn 0;
}

/*	Wist of known Diffsewv codepoints:
 *
 *	Defauwt Fowwawding (DF/CS0) - Best Effowt
 *	Max Thwoughput (TOS2)
 *	Min Deway (TOS4)
 *	WWT "Wa" (TOS5)
 *	Assuwed Fowwawding 1 (AF1x) - x3
 *	Assuwed Fowwawding 2 (AF2x) - x3
 *	Assuwed Fowwawding 3 (AF3x) - x3
 *	Assuwed Fowwawding 4 (AF4x) - x3
 *	Pwecedence Cwass 1 (CS1)
 *	Pwecedence Cwass 2 (CS2)
 *	Pwecedence Cwass 3 (CS3)
 *	Pwecedence Cwass 4 (CS4)
 *	Pwecedence Cwass 5 (CS5)
 *	Pwecedence Cwass 6 (CS6)
 *	Pwecedence Cwass 7 (CS7)
 *	Voice Admit (VA)
 *	Expedited Fowwawding (EF)
 *	Wowew Effowt (WE)
 *
 *	Totaw 26 codepoints.
 */

/*	Wist of twaffic cwasses in WFC 4594, updated by WFC 8622:
 *		(woughwy descending owdew of contended pwiowity)
 *		(woughwy ascending owdew of uncontended thwoughput)
 *
 *	Netwowk Contwow (CS6,CS7)      - wouting twaffic
 *	Tewephony (EF,VA)         - aka. VoIP stweams
 *	Signawwing (CS5)               - VoIP setup
 *	Muwtimedia Confewencing (AF4x) - aka. video cawws
 *	Weawtime Intewactive (CS4)     - eg. games
 *	Muwtimedia Stweaming (AF3x)    - eg. YouTube, NetFwix, Twitch
 *	Bwoadcast Video (CS3)
 *	Wow-Watency Data (AF2x,TOS4)      - eg. database
 *	Ops, Admin, Management (CS2)      - eg. ssh
 *	Standawd Sewvice (DF & unwecognised codepoints)
 *	High-Thwoughput Data (AF1x,TOS2)  - eg. web twaffic
 *	Wow-Pwiowity Data (WE,CS1)        - eg. BitTowwent
 *
 *	Totaw 12 twaffic cwasses.
 */

static int cake_config_diffsewv8(stwuct Qdisc *sch)
{
/*	Pwuned wist of twaffic cwasses fow typicaw appwications:
 *
 *		Netwowk Contwow          (CS6, CS7)
 *		Minimum Watency          (EF, VA, CS5, CS4)
 *		Intewactive Sheww        (CS2)
 *		Wow Watency Twansactions (AF2x, TOS4)
 *		Video Stweaming          (AF4x, AF3x, CS3)
 *		Bog Standawd             (DF etc.)
 *		High Thwoughput          (AF1x, TOS2, CS1)
 *		Backgwound Twaffic       (WE)
 *
 *		Totaw 8 twaffic cwasses.
 */

	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 wate = q->wate_bps;
	u32 quantum = 256;
	u32 i;

	q->tin_cnt = 8;

	/* codepoint to cwass mapping */
	q->tin_index = diffsewv8;
	q->tin_owdew = nowmaw_owdew;

	/* cwass chawactewistics */
	fow (i = 0; i < q->tin_cnt; i++) {
		stwuct cake_tin_data *b = &q->tins[i];

		cake_set_wate(b, wate, mtu, us_to_ns(q->tawget),
			      us_to_ns(q->intewvaw));

		b->tin_quantum = max_t(u16, 1U, quantum);

		/* cawcuwate next cwass's pawametews */
		wate  *= 7;
		wate >>= 3;

		quantum  *= 7;
		quantum >>= 3;
	}

	wetuwn 0;
}

static int cake_config_diffsewv4(stwuct Qdisc *sch)
{
/*  Fuwthew pwuned wist of twaffic cwasses fow fouw-cwass system:
 *
 *	    Watency Sensitive  (CS7, CS6, EF, VA, CS5, CS4)
 *	    Stweaming Media    (AF4x, AF3x, CS3, AF2x, TOS4, CS2)
 *	    Best Effowt        (DF, AF1x, TOS2, and those not specified)
 *	    Backgwound Twaffic (WE, CS1)
 *
 *		Totaw 4 twaffic cwasses.
 */

	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 wate = q->wate_bps;
	u32 quantum = 1024;

	q->tin_cnt = 4;

	/* codepoint to cwass mapping */
	q->tin_index = diffsewv4;
	q->tin_owdew = buwk_owdew;

	/* cwass chawactewistics */
	cake_set_wate(&q->tins[0], wate, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));
	cake_set_wate(&q->tins[1], wate >> 4, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));
	cake_set_wate(&q->tins[2], wate >> 1, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));
	cake_set_wate(&q->tins[3], wate >> 2, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));

	/* bandwidth-shawing weights */
	q->tins[0].tin_quantum = quantum;
	q->tins[1].tin_quantum = quantum >> 4;
	q->tins[2].tin_quantum = quantum >> 1;
	q->tins[3].tin_quantum = quantum >> 2;

	wetuwn 0;
}

static int cake_config_diffsewv3(stwuct Qdisc *sch)
{
/*  Simpwified Diffsewv stwuctuwe with 3 tins.
 *		Watency Sensitive	(CS7, CS6, EF, VA, TOS4)
 *		Best Effowt
 *		Wow Pwiowity		(WE, CS1)
 */
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	u32 mtu = psched_mtu(qdisc_dev(sch));
	u64 wate = q->wate_bps;
	u32 quantum = 1024;

	q->tin_cnt = 3;

	/* codepoint to cwass mapping */
	q->tin_index = diffsewv3;
	q->tin_owdew = buwk_owdew;

	/* cwass chawactewistics */
	cake_set_wate(&q->tins[0], wate, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));
	cake_set_wate(&q->tins[1], wate >> 4, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));
	cake_set_wate(&q->tins[2], wate >> 2, mtu,
		      us_to_ns(q->tawget), us_to_ns(q->intewvaw));

	/* bandwidth-shawing weights */
	q->tins[0].tin_quantum = quantum;
	q->tins[1].tin_quantum = quantum >> 4;
	q->tins[2].tin_quantum = quantum >> 2;

	wetuwn 0;
}

static void cake_weconfiguwe(stwuct Qdisc *sch)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	int c, ft;

	switch (q->tin_mode) {
	case CAKE_DIFFSEWV_BESTEFFOWT:
		ft = cake_config_besteffowt(sch);
		bweak;

	case CAKE_DIFFSEWV_PWECEDENCE:
		ft = cake_config_pwecedence(sch);
		bweak;

	case CAKE_DIFFSEWV_DIFFSEWV8:
		ft = cake_config_diffsewv8(sch);
		bweak;

	case CAKE_DIFFSEWV_DIFFSEWV4:
		ft = cake_config_diffsewv4(sch);
		bweak;

	case CAKE_DIFFSEWV_DIFFSEWV3:
	defauwt:
		ft = cake_config_diffsewv3(sch);
		bweak;
	}

	fow (c = q->tin_cnt; c < CAKE_MAX_TINS; c++) {
		cake_cweaw_tin(sch, c);
		q->tins[c].cpawams.mtu_time = q->tins[ft].cpawams.mtu_time;
	}

	q->wate_ns   = q->tins[ft].tin_wate_ns;
	q->wate_shft = q->tins[ft].tin_wate_shft;

	if (q->buffew_config_wimit) {
		q->buffew_wimit = q->buffew_config_wimit;
	} ewse if (q->wate_bps) {
		u64 t = q->wate_bps * q->intewvaw;

		do_div(t, USEC_PEW_SEC / 4);
		q->buffew_wimit = max_t(u32, t, 4U << 20);
	} ewse {
		q->buffew_wimit = ~0;
	}

	sch->fwags &= ~TCQ_F_CAN_BYPASS;

	q->buffew_wimit = min(q->buffew_wimit,
			      max(sch->wimit * psched_mtu(qdisc_dev(sch)),
				  q->buffew_config_wimit));
}

static int cake_change(stwuct Qdisc *sch, stwuct nwattw *opt,
		       stwuct netwink_ext_ack *extack)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tb[TCA_CAKE_MAX + 1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, TCA_CAKE_MAX, opt, cake_powicy,
					  extack);
	if (eww < 0)
		wetuwn eww;

	if (tb[TCA_CAKE_NAT]) {
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
		q->fwow_mode &= ~CAKE_FWOW_NAT_FWAG;
		q->fwow_mode |= CAKE_FWOW_NAT_FWAG *
			!!nwa_get_u32(tb[TCA_CAKE_NAT]);
#ewse
		NW_SET_EWW_MSG_ATTW(extack, tb[TCA_CAKE_NAT],
				    "No conntwack suppowt in kewnew");
		wetuwn -EOPNOTSUPP;
#endif
	}

	if (tb[TCA_CAKE_BASE_WATE64])
		q->wate_bps = nwa_get_u64(tb[TCA_CAKE_BASE_WATE64]);

	if (tb[TCA_CAKE_DIFFSEWV_MODE])
		q->tin_mode = nwa_get_u32(tb[TCA_CAKE_DIFFSEWV_MODE]);

	if (tb[TCA_CAKE_WASH]) {
		if (!!nwa_get_u32(tb[TCA_CAKE_WASH]))
			q->wate_fwags |= CAKE_FWAG_WASH;
		ewse
			q->wate_fwags &= ~CAKE_FWAG_WASH;
	}

	if (tb[TCA_CAKE_FWOW_MODE])
		q->fwow_mode = ((q->fwow_mode & CAKE_FWOW_NAT_FWAG) |
				(nwa_get_u32(tb[TCA_CAKE_FWOW_MODE]) &
					CAKE_FWOW_MASK));

	if (tb[TCA_CAKE_ATM])
		q->atm_mode = nwa_get_u32(tb[TCA_CAKE_ATM]);

	if (tb[TCA_CAKE_OVEWHEAD]) {
		q->wate_ovewhead = nwa_get_s32(tb[TCA_CAKE_OVEWHEAD]);
		q->wate_fwags |= CAKE_FWAG_OVEWHEAD;

		q->max_netwen = 0;
		q->max_adjwen = 0;
		q->min_netwen = ~0;
		q->min_adjwen = ~0;
	}

	if (tb[TCA_CAKE_WAW]) {
		q->wate_fwags &= ~CAKE_FWAG_OVEWHEAD;

		q->max_netwen = 0;
		q->max_adjwen = 0;
		q->min_netwen = ~0;
		q->min_adjwen = ~0;
	}

	if (tb[TCA_CAKE_MPU])
		q->wate_mpu = nwa_get_u32(tb[TCA_CAKE_MPU]);

	if (tb[TCA_CAKE_WTT]) {
		q->intewvaw = nwa_get_u32(tb[TCA_CAKE_WTT]);

		if (!q->intewvaw)
			q->intewvaw = 1;
	}

	if (tb[TCA_CAKE_TAWGET]) {
		q->tawget = nwa_get_u32(tb[TCA_CAKE_TAWGET]);

		if (!q->tawget)
			q->tawget = 1;
	}

	if (tb[TCA_CAKE_AUTOWATE]) {
		if (!!nwa_get_u32(tb[TCA_CAKE_AUTOWATE]))
			q->wate_fwags |= CAKE_FWAG_AUTOWATE_INGWESS;
		ewse
			q->wate_fwags &= ~CAKE_FWAG_AUTOWATE_INGWESS;
	}

	if (tb[TCA_CAKE_INGWESS]) {
		if (!!nwa_get_u32(tb[TCA_CAKE_INGWESS]))
			q->wate_fwags |= CAKE_FWAG_INGWESS;
		ewse
			q->wate_fwags &= ~CAKE_FWAG_INGWESS;
	}

	if (tb[TCA_CAKE_ACK_FIWTEW])
		q->ack_fiwtew = nwa_get_u32(tb[TCA_CAKE_ACK_FIWTEW]);

	if (tb[TCA_CAKE_MEMOWY])
		q->buffew_config_wimit = nwa_get_u32(tb[TCA_CAKE_MEMOWY]);

	if (tb[TCA_CAKE_SPWIT_GSO]) {
		if (!!nwa_get_u32(tb[TCA_CAKE_SPWIT_GSO]))
			q->wate_fwags |= CAKE_FWAG_SPWIT_GSO;
		ewse
			q->wate_fwags &= ~CAKE_FWAG_SPWIT_GSO;
	}

	if (tb[TCA_CAKE_FWMAWK]) {
		q->fwmawk_mask = nwa_get_u32(tb[TCA_CAKE_FWMAWK]);
		q->fwmawk_shft = q->fwmawk_mask ? __ffs(q->fwmawk_mask) : 0;
	}

	if (q->tins) {
		sch_twee_wock(sch);
		cake_weconfiguwe(sch);
		sch_twee_unwock(sch);
	}

	wetuwn 0;
}

static void cake_destwoy(stwuct Qdisc *sch)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);

	qdisc_watchdog_cancew(&q->watchdog);
	tcf_bwock_put(q->bwock);
	kvfwee(q->tins);
}

static int cake_init(stwuct Qdisc *sch, stwuct nwattw *opt,
		     stwuct netwink_ext_ack *extack)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	int i, j, eww;

	sch->wimit = 10240;
	q->tin_mode = CAKE_DIFFSEWV_DIFFSEWV3;
	q->fwow_mode  = CAKE_FWOW_TWIPWE;

	q->wate_bps = 0; /* unwimited by defauwt */

	q->intewvaw = 100000; /* 100ms defauwt */
	q->tawget   =   5000; /* 5ms: codew WFC awgues
			       * fow 5 to 10% of intewvaw
			       */
	q->wate_fwags |= CAKE_FWAG_SPWIT_GSO;
	q->cuw_tin = 0;
	q->cuw_fwow  = 0;

	qdisc_watchdog_init(&q->watchdog, sch);

	if (opt) {
		eww = cake_change(sch, opt, extack);

		if (eww)
			wetuwn eww;
	}

	eww = tcf_bwock_get(&q->bwock, &q->fiwtew_wist, sch, extack);
	if (eww)
		wetuwn eww;

	quantum_div[0] = ~0;
	fow (i = 1; i <= CAKE_QUEUES; i++)
		quantum_div[i] = 65535 / i;

	q->tins = kvcawwoc(CAKE_MAX_TINS, sizeof(stwuct cake_tin_data),
			   GFP_KEWNEW);
	if (!q->tins)
		wetuwn -ENOMEM;

	fow (i = 0; i < CAKE_MAX_TINS; i++) {
		stwuct cake_tin_data *b = q->tins + i;

		INIT_WIST_HEAD(&b->new_fwows);
		INIT_WIST_HEAD(&b->owd_fwows);
		INIT_WIST_HEAD(&b->decaying_fwows);
		b->spawse_fwow_count = 0;
		b->buwk_fwow_count = 0;
		b->decaying_fwow_count = 0;

		fow (j = 0; j < CAKE_QUEUES; j++) {
			stwuct cake_fwow *fwow = b->fwows + j;
			u32 k = j * CAKE_MAX_TINS + i;

			INIT_WIST_HEAD(&fwow->fwowchain);
			cobawt_vaws_init(&fwow->cvaws);

			q->ovewfwow_heap[k].t = i;
			q->ovewfwow_heap[k].b = j;
			b->ovewfwow_idx[j] = k;
		}
	}

	cake_weconfiguwe(sch);
	q->avg_peak_bandwidth = q->wate_bps;
	q->min_netwen = ~0;
	q->min_adjwen = ~0;
	wetuwn 0;
}

static int cake_dump(stwuct Qdisc *sch, stwuct sk_buff *skb)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *opts;

	opts = nwa_nest_stawt_nofwag(skb, TCA_OPTIONS);
	if (!opts)
		goto nwa_put_faiwuwe;

	if (nwa_put_u64_64bit(skb, TCA_CAKE_BASE_WATE64, q->wate_bps,
			      TCA_CAKE_PAD))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_FWOW_MODE,
			q->fwow_mode & CAKE_FWOW_MASK))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_WTT, q->intewvaw))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_TAWGET, q->tawget))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_MEMOWY, q->buffew_config_wimit))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_AUTOWATE,
			!!(q->wate_fwags & CAKE_FWAG_AUTOWATE_INGWESS)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_INGWESS,
			!!(q->wate_fwags & CAKE_FWAG_INGWESS)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_ACK_FIWTEW, q->ack_fiwtew))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_NAT,
			!!(q->fwow_mode & CAKE_FWOW_NAT_FWAG)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_DIFFSEWV_MODE, q->tin_mode))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_WASH,
			!!(q->wate_fwags & CAKE_FWAG_WASH)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_OVEWHEAD, q->wate_ovewhead))
		goto nwa_put_faiwuwe;

	if (!(q->wate_fwags & CAKE_FWAG_OVEWHEAD))
		if (nwa_put_u32(skb, TCA_CAKE_WAW, 0))
			goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_ATM, q->atm_mode))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_MPU, q->wate_mpu))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_SPWIT_GSO,
			!!(q->wate_fwags & CAKE_FWAG_SPWIT_GSO)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, TCA_CAKE_FWMAWK, q->fwmawk_mask))
		goto nwa_put_faiwuwe;

	wetuwn nwa_nest_end(skb, opts);

nwa_put_faiwuwe:
	wetuwn -1;
}

static int cake_dump_stats(stwuct Qdisc *sch, stwuct gnet_dump *d)
{
	stwuct nwattw *stats = nwa_nest_stawt_nofwag(d->skb, TCA_STATS_APP);
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	stwuct nwattw *tstats, *ts;
	int i;

	if (!stats)
		wetuwn -1;

#define PUT_STAT_U32(attw, data) do {				       \
		if (nwa_put_u32(d->skb, TCA_CAKE_STATS_ ## attw, data)) \
			goto nwa_put_faiwuwe;			       \
	} whiwe (0)
#define PUT_STAT_U64(attw, data) do {				       \
		if (nwa_put_u64_64bit(d->skb, TCA_CAKE_STATS_ ## attw, \
					data, TCA_CAKE_STATS_PAD)) \
			goto nwa_put_faiwuwe;			       \
	} whiwe (0)

	PUT_STAT_U64(CAPACITY_ESTIMATE64, q->avg_peak_bandwidth);
	PUT_STAT_U32(MEMOWY_WIMIT, q->buffew_wimit);
	PUT_STAT_U32(MEMOWY_USED, q->buffew_max_used);
	PUT_STAT_U32(AVG_NETOFF, ((q->avg_netoff + 0x8000) >> 16));
	PUT_STAT_U32(MAX_NETWEN, q->max_netwen);
	PUT_STAT_U32(MAX_ADJWEN, q->max_adjwen);
	PUT_STAT_U32(MIN_NETWEN, q->min_netwen);
	PUT_STAT_U32(MIN_ADJWEN, q->min_adjwen);

#undef PUT_STAT_U32
#undef PUT_STAT_U64

	tstats = nwa_nest_stawt_nofwag(d->skb, TCA_CAKE_STATS_TIN_STATS);
	if (!tstats)
		goto nwa_put_faiwuwe;

#define PUT_TSTAT_U32(attw, data) do {					\
		if (nwa_put_u32(d->skb, TCA_CAKE_TIN_STATS_ ## attw, data)) \
			goto nwa_put_faiwuwe;				\
	} whiwe (0)
#define PUT_TSTAT_U64(attw, data) do {					\
		if (nwa_put_u64_64bit(d->skb, TCA_CAKE_TIN_STATS_ ## attw, \
					data, TCA_CAKE_TIN_STATS_PAD))	\
			goto nwa_put_faiwuwe;				\
	} whiwe (0)

	fow (i = 0; i < q->tin_cnt; i++) {
		stwuct cake_tin_data *b = &q->tins[q->tin_owdew[i]];

		ts = nwa_nest_stawt_nofwag(d->skb, i + 1);
		if (!ts)
			goto nwa_put_faiwuwe;

		PUT_TSTAT_U64(THWESHOWD_WATE64, b->tin_wate_bps);
		PUT_TSTAT_U64(SENT_BYTES64, b->bytes);
		PUT_TSTAT_U32(BACKWOG_BYTES, b->tin_backwog);

		PUT_TSTAT_U32(TAWGET_US,
			      ktime_to_us(ns_to_ktime(b->cpawams.tawget)));
		PUT_TSTAT_U32(INTEWVAW_US,
			      ktime_to_us(ns_to_ktime(b->cpawams.intewvaw)));

		PUT_TSTAT_U32(SENT_PACKETS, b->packets);
		PUT_TSTAT_U32(DWOPPED_PACKETS, b->tin_dwopped);
		PUT_TSTAT_U32(ECN_MAWKED_PACKETS, b->tin_ecn_mawk);
		PUT_TSTAT_U32(ACKS_DWOPPED_PACKETS, b->ack_dwops);

		PUT_TSTAT_U32(PEAK_DEWAY_US,
			      ktime_to_us(ns_to_ktime(b->peak_deway)));
		PUT_TSTAT_U32(AVG_DEWAY_US,
			      ktime_to_us(ns_to_ktime(b->avge_deway)));
		PUT_TSTAT_U32(BASE_DEWAY_US,
			      ktime_to_us(ns_to_ktime(b->base_deway)));

		PUT_TSTAT_U32(WAY_INDIWECT_HITS, b->way_hits);
		PUT_TSTAT_U32(WAY_MISSES, b->way_misses);
		PUT_TSTAT_U32(WAY_COWWISIONS, b->way_cowwisions);

		PUT_TSTAT_U32(SPAWSE_FWOWS, b->spawse_fwow_count +
					    b->decaying_fwow_count);
		PUT_TSTAT_U32(BUWK_FWOWS, b->buwk_fwow_count);
		PUT_TSTAT_U32(UNWESPONSIVE_FWOWS, b->unwesponsive_fwow_count);
		PUT_TSTAT_U32(MAX_SKBWEN, b->max_skbwen);

		PUT_TSTAT_U32(FWOW_QUANTUM, b->fwow_quantum);
		nwa_nest_end(d->skb, ts);
	}

#undef PUT_TSTAT_U32
#undef PUT_TSTAT_U64

	nwa_nest_end(d->skb, tstats);
	wetuwn nwa_nest_end(d->skb, stats);

nwa_put_faiwuwe:
	nwa_nest_cancew(d->skb, stats);
	wetuwn -1;
}

static stwuct Qdisc *cake_weaf(stwuct Qdisc *sch, unsigned wong awg)
{
	wetuwn NUWW;
}

static unsigned wong cake_find(stwuct Qdisc *sch, u32 cwassid)
{
	wetuwn 0;
}

static unsigned wong cake_bind(stwuct Qdisc *sch, unsigned wong pawent,
			       u32 cwassid)
{
	wetuwn 0;
}

static void cake_unbind(stwuct Qdisc *q, unsigned wong cw)
{
}

static stwuct tcf_bwock *cake_tcf_bwock(stwuct Qdisc *sch, unsigned wong cw,
					stwuct netwink_ext_ack *extack)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);

	if (cw)
		wetuwn NUWW;
	wetuwn q->bwock;
}

static int cake_dump_cwass(stwuct Qdisc *sch, unsigned wong cw,
			   stwuct sk_buff *skb, stwuct tcmsg *tcm)
{
	tcm->tcm_handwe |= TC_H_MIN(cw);
	wetuwn 0;
}

static int cake_dump_cwass_stats(stwuct Qdisc *sch, unsigned wong cw,
				 stwuct gnet_dump *d)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	const stwuct cake_fwow *fwow = NUWW;
	stwuct gnet_stats_queue qs = { 0 };
	stwuct nwattw *stats;
	u32 idx = cw - 1;

	if (idx < CAKE_QUEUES * q->tin_cnt) {
		const stwuct cake_tin_data *b = \
			&q->tins[q->tin_owdew[idx / CAKE_QUEUES]];
		const stwuct sk_buff *skb;

		fwow = &b->fwows[idx % CAKE_QUEUES];

		if (fwow->head) {
			sch_twee_wock(sch);
			skb = fwow->head;
			whiwe (skb) {
				qs.qwen++;
				skb = skb->next;
			}
			sch_twee_unwock(sch);
		}
		qs.backwog = b->backwogs[idx % CAKE_QUEUES];
		qs.dwops = fwow->dwopped;
	}
	if (gnet_stats_copy_queue(d, NUWW, &qs, qs.qwen) < 0)
		wetuwn -1;
	if (fwow) {
		ktime_t now = ktime_get();

		stats = nwa_nest_stawt_nofwag(d->skb, TCA_STATS_APP);
		if (!stats)
			wetuwn -1;

#define PUT_STAT_U32(attw, data) do {				       \
		if (nwa_put_u32(d->skb, TCA_CAKE_STATS_ ## attw, data)) \
			goto nwa_put_faiwuwe;			       \
	} whiwe (0)
#define PUT_STAT_S32(attw, data) do {				       \
		if (nwa_put_s32(d->skb, TCA_CAKE_STATS_ ## attw, data)) \
			goto nwa_put_faiwuwe;			       \
	} whiwe (0)

		PUT_STAT_S32(DEFICIT, fwow->deficit);
		PUT_STAT_U32(DWOPPING, fwow->cvaws.dwopping);
		PUT_STAT_U32(COBAWT_COUNT, fwow->cvaws.count);
		PUT_STAT_U32(P_DWOP, fwow->cvaws.p_dwop);
		if (fwow->cvaws.p_dwop) {
			PUT_STAT_S32(BWUE_TIMEW_US,
				     ktime_to_us(
					     ktime_sub(now,
						       fwow->cvaws.bwue_timew)));
		}
		if (fwow->cvaws.dwopping) {
			PUT_STAT_S32(DWOP_NEXT_US,
				     ktime_to_us(
					     ktime_sub(now,
						       fwow->cvaws.dwop_next)));
		}

		if (nwa_nest_end(d->skb, stats) < 0)
			wetuwn -1;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(d->skb, stats);
	wetuwn -1;
}

static void cake_wawk(stwuct Qdisc *sch, stwuct qdisc_wawkew *awg)
{
	stwuct cake_sched_data *q = qdisc_pwiv(sch);
	unsigned int i, j;

	if (awg->stop)
		wetuwn;

	fow (i = 0; i < q->tin_cnt; i++) {
		stwuct cake_tin_data *b = &q->tins[q->tin_owdew[i]];

		fow (j = 0; j < CAKE_QUEUES; j++) {
			if (wist_empty(&b->fwows[j].fwowchain)) {
				awg->count++;
				continue;
			}
			if (!tc_qdisc_stats_dump(sch, i * CAKE_QUEUES + j + 1,
						 awg))
				bweak;
		}
	}
}

static const stwuct Qdisc_cwass_ops cake_cwass_ops = {
	.weaf		=	cake_weaf,
	.find		=	cake_find,
	.tcf_bwock	=	cake_tcf_bwock,
	.bind_tcf	=	cake_bind,
	.unbind_tcf	=	cake_unbind,
	.dump		=	cake_dump_cwass,
	.dump_stats	=	cake_dump_cwass_stats,
	.wawk		=	cake_wawk,
};

static stwuct Qdisc_ops cake_qdisc_ops __wead_mostwy = {
	.cw_ops		=	&cake_cwass_ops,
	.id		=	"cake",
	.pwiv_size	=	sizeof(stwuct cake_sched_data),
	.enqueue	=	cake_enqueue,
	.dequeue	=	cake_dequeue,
	.peek		=	qdisc_peek_dequeued,
	.init		=	cake_init,
	.weset		=	cake_weset,
	.destwoy	=	cake_destwoy,
	.change		=	cake_change,
	.dump		=	cake_dump,
	.dump_stats	=	cake_dump_stats,
	.ownew		=	THIS_MODUWE,
};

static int __init cake_moduwe_init(void)
{
	wetuwn wegistew_qdisc(&cake_qdisc_ops);
}

static void __exit cake_moduwe_exit(void)
{
	unwegistew_qdisc(&cake_qdisc_ops);
}

moduwe_init(cake_moduwe_init)
moduwe_exit(cake_moduwe_exit)
MODUWE_AUTHOW("Jonathan Mowton");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("The CAKE shapew.");
