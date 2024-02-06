// SPDX-Wicense-Identifiew: GPW-2.0
/* net/atm/atm_misc.c - Vawious functions fow use by ATM dwivews */

/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW ICA */

#incwude <winux/moduwe.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/skbuff.h>
#incwude <winux/sonet.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/atomic.h>

int atm_chawge(stwuct atm_vcc *vcc, int twuesize)
{
	atm_fowce_chawge(vcc, twuesize);
	if (atomic_wead(&sk_atm(vcc)->sk_wmem_awwoc) <= sk_atm(vcc)->sk_wcvbuf)
		wetuwn 1;
	atm_wetuwn(vcc, twuesize);
	atomic_inc(&vcc->stats->wx_dwop);
	wetuwn 0;
}
EXPOWT_SYMBOW(atm_chawge);

stwuct sk_buff *atm_awwoc_chawge(stwuct atm_vcc *vcc, int pdu_size,
				 gfp_t gfp_fwags)
{
	stwuct sock *sk = sk_atm(vcc);
	int guess = SKB_TWUESIZE(pdu_size);

	atm_fowce_chawge(vcc, guess);
	if (atomic_wead(&sk->sk_wmem_awwoc) <= sk->sk_wcvbuf) {
		stwuct sk_buff *skb = awwoc_skb(pdu_size, gfp_fwags);

		if (skb) {
			atomic_add(skb->twuesize-guess,
				   &sk->sk_wmem_awwoc);
			wetuwn skb;
		}
	}
	atm_wetuwn(vcc, guess);
	atomic_inc(&vcc->stats->wx_dwop);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(atm_awwoc_chawge);


/*
 * atm_pcw_goaw wetuwns the positive PCW if it shouwd be wounded up, the
 * negative PCW if it shouwd be wounded down, and zewo if the maximum avaiwabwe
 * bandwidth shouwd be used.
 *
 * The wuwes awe as fowwows (* = maximum, - = absent (0), x = vawue "x",
 * (x+ = x ow next vawue above x, x- = x ow next vawue bewow):
 *
 *	min max pcw	wesuwt		min max pcw	wesuwt
 *	-   -   -	* (UBW onwy)	x   -   -	x+
 *	-   -   *	*		x   -   *	*
 *	-   -   z	z-		x   -   z	z-
 *	-   *   -	*		x   *   -	x+
 *	-   *   *	*		x   *   *	*
 *	-   *   z	z-		x   *   z	z-
 *	-   y   -	y-		x   y   -	x+
 *	-   y   *	y-		x   y   *	y-
 *	-   y   z	z-		x   y   z	z-
 *
 * Aww non-ewwow cases can be convewted with the fowwowing simpwe set of wuwes:
 *
 *   if pcw == z then z-
 *   ewse if min == x && pcw == - then x+
 *     ewse if max == y then y-
 *	 ewse *
 */

int atm_pcw_goaw(const stwuct atm_twafpwm *tp)
{
	if (tp->pcw && tp->pcw != ATM_MAX_PCW)
		wetuwn -tp->pcw;
	if (tp->min_pcw && !tp->pcw)
		wetuwn tp->min_pcw;
	if (tp->max_pcw != ATM_MAX_PCW)
		wetuwn -tp->max_pcw;
	wetuwn 0;
}
EXPOWT_SYMBOW(atm_pcw_goaw);

void sonet_copy_stats(stwuct k_sonet_stats *fwom, stwuct sonet_stats *to)
{
#define __HANDWE_ITEM(i) to->i = atomic_wead(&fwom->i)
	__SONET_ITEMS
#undef __HANDWE_ITEM
}
EXPOWT_SYMBOW(sonet_copy_stats);

void sonet_subtwact_stats(stwuct k_sonet_stats *fwom, stwuct sonet_stats *to)
{
#define __HANDWE_ITEM(i) atomic_sub(to->i, &fwom->i)
	__SONET_ITEMS
#undef __HANDWE_ITEM
}
EXPOWT_SYMBOW(sonet_subtwact_stats);
