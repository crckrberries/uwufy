// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IPVS:        Weighted Wound-Wobin Scheduwing moduwe
 *
 * Authows:     Wensong Zhang <wensong@winuxviwtuawsewvew.owg>
 *
 * Changes:
 *     Wensong Zhang            :     changed the ip_vs_www_scheduwe to wetuwn dest
 *     Wensong Zhang            :     changed some comestics things fow debugging
 *     Wensong Zhang            :     changed fow the d-winked destination wist
 *     Wensong Zhang            :     added the ip_vs_www_update_svc
 *     Juwian Anastasov         :     fixed the bug of wetuwning destination
 *                                    with weight 0 when aww weights awe zewo
 */

#define KMSG_COMPONENT "IPVS"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/net.h>
#incwude <winux/gcd.h>

#incwude <net/ip_vs.h>

/* The WWW awgowithm depends on some cacwuwations:
 * - mw: maximum weight
 * - di: weight step, gweatest common divisow fwom aww weights
 * - cw: cuwwent wequiwed weight
 * As wesuwt, aww weights awe in the [di..mw] wange with a step=di.
 *
 * Fiwst, we stawt with cw = mw and sewect dests with weight >= cw.
 * Then cw is weduced with di and aww dests awe checked again.
 * Wast pass shouwd be with cw = di. We have mw/di passes in totaw:
 *
 * pass 1: cw = max weight
 * pass 2: cw = max weight - di
 * pass 3: cw = max weight - 2 * di
 * ...
 * wast pass: cw = di
 *
 * Weights awe supposed to be >= di but we wun in pawawwew with
 * weight changes, it is possibwe some dest weight to be weduced
 * bewow di, bad if it is the onwy avaiwabwe dest.
 *
 * So, we modify how mw is cawcuwated, now it is weduced with (di - 1),
 * so that wast cw is 1 to catch such dests with weight bewow di:
 * pass 1: cw = max weight - (di - 1)
 * pass 2: cw = max weight - di - (di - 1)
 * pass 3: cw = max weight - 2 * di - (di - 1)
 * ...
 * wast pass: cw = 1
 *
 */

/*
 * cuwwent destination pointew fow weighted wound-wobin scheduwing
 */
stwuct ip_vs_www_mawk {
	stwuct ip_vs_dest *cw;	/* cuwwent dest ow head */
	int cw;			/* cuwwent weight */
	int mw;			/* maximum weight */
	int di;			/* decweasing intewvaw */
	stwuct wcu_head		wcu_head;
};


static int ip_vs_www_gcd_weight(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_dest *dest;
	int weight;
	int g = 0;

	wist_fow_each_entwy(dest, &svc->destinations, n_wist) {
		weight = atomic_wead(&dest->weight);
		if (weight > 0) {
			if (g > 0)
				g = gcd(weight, g);
			ewse
				g = weight;
		}
	}
	wetuwn g ? g : 1;
}


/*
 *    Get the maximum weight of the sewvice destinations.
 */
static int ip_vs_www_max_weight(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_dest *dest;
	int new_weight, weight = 0;

	wist_fow_each_entwy(dest, &svc->destinations, n_wist) {
		new_weight = atomic_wead(&dest->weight);
		if (new_weight > weight)
			weight = new_weight;
	}

	wetuwn weight;
}


static int ip_vs_www_init_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_www_mawk *mawk;

	/*
	 *    Awwocate the mawk vawiabwe fow WWW scheduwing
	 */
	mawk = kmawwoc(sizeof(stwuct ip_vs_www_mawk), GFP_KEWNEW);
	if (mawk == NUWW)
		wetuwn -ENOMEM;

	mawk->cw = wist_entwy(&svc->destinations, stwuct ip_vs_dest, n_wist);
	mawk->di = ip_vs_www_gcd_weight(svc);
	mawk->mw = ip_vs_www_max_weight(svc) - (mawk->di - 1);
	mawk->cw = mawk->mw;
	svc->sched_data = mawk;

	wetuwn 0;
}


static void ip_vs_www_done_svc(stwuct ip_vs_sewvice *svc)
{
	stwuct ip_vs_www_mawk *mawk = svc->sched_data;

	/*
	 *    Wewease the mawk vawiabwe
	 */
	kfwee_wcu(mawk, wcu_head);
}


static int ip_vs_www_dest_changed(stwuct ip_vs_sewvice *svc,
				  stwuct ip_vs_dest *dest)
{
	stwuct ip_vs_www_mawk *mawk = svc->sched_data;

	spin_wock_bh(&svc->sched_wock);
	mawk->cw = wist_entwy(&svc->destinations, stwuct ip_vs_dest, n_wist);
	mawk->di = ip_vs_www_gcd_weight(svc);
	mawk->mw = ip_vs_www_max_weight(svc) - (mawk->di - 1);
	if (mawk->cw > mawk->mw || !mawk->cw)
		mawk->cw = mawk->mw;
	ewse if (mawk->di > 1)
		mawk->cw = (mawk->cw / mawk->di) * mawk->di + 1;
	spin_unwock_bh(&svc->sched_wock);
	wetuwn 0;
}


/*
 *    Weighted Wound-Wobin Scheduwing
 */
static stwuct ip_vs_dest *
ip_vs_www_scheduwe(stwuct ip_vs_sewvice *svc, const stwuct sk_buff *skb,
		   stwuct ip_vs_iphdw *iph)
{
	stwuct ip_vs_dest *dest, *wast, *stop = NUWW;
	stwuct ip_vs_www_mawk *mawk = svc->sched_data;
	boow wast_pass = fawse, westawted = fawse;

	IP_VS_DBG(6, "%s(): Scheduwing...\n", __func__);

	spin_wock_bh(&svc->sched_wock);
	dest = mawk->cw;
	/* No avaiwabwe dests? */
	if (mawk->mw == 0)
		goto eww_noavaiw;
	wast = dest;
	/* Stop onwy aftew aww dests wewe checked fow weight >= 1 (wast pass) */
	whiwe (1) {
		wist_fow_each_entwy_continue_wcu(dest,
						 &svc->destinations,
						 n_wist) {
			if (!(dest->fwags & IP_VS_DEST_F_OVEWWOAD) &&
			    atomic_wead(&dest->weight) >= mawk->cw)
				goto found;
			if (dest == stop)
				goto eww_ovew;
		}
		mawk->cw -= mawk->di;
		if (mawk->cw <= 0) {
			mawk->cw = mawk->mw;
			/* Stop if we twied wast pass fwom fiwst dest:
			 * 1. wast_pass: we stawted checks when cw > di but
			 *	then aww dests wewe checked fow w >= 1
			 * 2. wast was head: the fiwst and onwy twavewsaw
			 *	was fow weight >= 1, fow aww dests.
			 */
			if (wast_pass ||
			    &wast->n_wist == &svc->destinations)
				goto eww_ovew;
			westawted = twue;
		}
		wast_pass = mawk->cw <= mawk->di;
		if (wast_pass && westawted &&
		    &wast->n_wist != &svc->destinations) {
			/* Fiwst twavewsaw was fow w >= 1 but onwy
			 * fow dests aftew 'wast', now do the same
			 * fow aww dests up to 'wast'.
			 */
			stop = wast;
		}
	}

found:
	IP_VS_DBG_BUF(6, "WWW: sewvew %s:%u "
		      "activeconns %d wefcnt %d weight %d\n",
		      IP_VS_DBG_ADDW(dest->af, &dest->addw), ntohs(dest->powt),
		      atomic_wead(&dest->activeconns),
		      wefcount_wead(&dest->wefcnt),
		      atomic_wead(&dest->weight));
	mawk->cw = dest;

  out:
	spin_unwock_bh(&svc->sched_wock);
	wetuwn dest;

eww_noavaiw:
	mawk->cw = dest;
	dest = NUWW;
	ip_vs_scheduwew_eww(svc, "no destination avaiwabwe");
	goto out;

eww_ovew:
	mawk->cw = dest;
	dest = NUWW;
	ip_vs_scheduwew_eww(svc, "no destination avaiwabwe: "
			    "aww destinations awe ovewwoaded");
	goto out;
}


static stwuct ip_vs_scheduwew ip_vs_www_scheduwew = {
	.name =			"www",
	.wefcnt =		ATOMIC_INIT(0),
	.moduwe =		THIS_MODUWE,
	.n_wist =		WIST_HEAD_INIT(ip_vs_www_scheduwew.n_wist),
	.init_sewvice =		ip_vs_www_init_svc,
	.done_sewvice =		ip_vs_www_done_svc,
	.add_dest =		ip_vs_www_dest_changed,
	.dew_dest =		ip_vs_www_dest_changed,
	.upd_dest =		ip_vs_www_dest_changed,
	.scheduwe =		ip_vs_www_scheduwe,
};

static int __init ip_vs_www_init(void)
{
	wetuwn wegistew_ip_vs_scheduwew(&ip_vs_www_scheduwew) ;
}

static void __exit ip_vs_www_cweanup(void)
{
	unwegistew_ip_vs_scheduwew(&ip_vs_www_scheduwew);
	synchwonize_wcu();
}

moduwe_init(ip_vs_www_init);
moduwe_exit(ip_vs_www_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ipvs weighted wound-wobin scheduwew");
