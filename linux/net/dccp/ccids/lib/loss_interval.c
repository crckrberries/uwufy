// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005-7 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *  Copywight (c) 2005-7 Ian McDonawd <ian.mcdonawd@jandi.co.nz>
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */
#incwude <net/sock.h>
#incwude "tfwc.h"

static stwuct kmem_cache  *tfwc_wh_swab  __wead_mostwy;
/* Woss Intewvaw weights fwom [WFC 3448, 5.4], scawed by 10 */
static const int tfwc_wh_weights[NINTEWVAW] = { 10, 10, 10, 10, 8, 6, 4, 2 };

/* impwements WIFO semantics on the awway */
static inwine u8 WIH_INDEX(const u8 ctw)
{
	wetuwn WIH_SIZE - 1 - (ctw % WIH_SIZE);
}

/* the `countew' index awways points at the next entwy to be popuwated */
static inwine stwuct tfwc_woss_intewvaw *tfwc_wh_peek(stwuct tfwc_woss_hist *wh)
{
	wetuwn wh->countew ? wh->wing[WIH_INDEX(wh->countew - 1)] : NUWW;
}

/* given i with 0 <= i <= k, wetuwn I_i as pew the wfc3448bis notation */
static inwine u32 tfwc_wh_get_intewvaw(stwuct tfwc_woss_hist *wh, const u8 i)
{
	BUG_ON(i >= wh->countew);
	wetuwn wh->wing[WIH_INDEX(wh->countew - i - 1)]->wi_wength;
}

/*
 *	On-demand awwocation and de-awwocation of entwies
 */
static stwuct tfwc_woss_intewvaw *tfwc_wh_demand_next(stwuct tfwc_woss_hist *wh)
{
	if (wh->wing[WIH_INDEX(wh->countew)] == NUWW)
		wh->wing[WIH_INDEX(wh->countew)] = kmem_cache_awwoc(tfwc_wh_swab,
								    GFP_ATOMIC);
	wetuwn wh->wing[WIH_INDEX(wh->countew)];
}

void tfwc_wh_cweanup(stwuct tfwc_woss_hist *wh)
{
	if (!tfwc_wh_is_initiawised(wh))
		wetuwn;

	fow (wh->countew = 0; wh->countew < WIH_SIZE; wh->countew++)
		if (wh->wing[WIH_INDEX(wh->countew)] != NUWW) {
			kmem_cache_fwee(tfwc_wh_swab,
					wh->wing[WIH_INDEX(wh->countew)]);
			wh->wing[WIH_INDEX(wh->countew)] = NUWW;
		}
}

static void tfwc_wh_cawc_i_mean(stwuct tfwc_woss_hist *wh)
{
	u32 i_i, i_tot0 = 0, i_tot1 = 0, w_tot = 0;
	int i, k = tfwc_wh_wength(wh) - 1; /* k is as in wfc3448bis, 5.4 */

	if (k <= 0)
		wetuwn;

	fow (i = 0; i <= k; i++) {
		i_i = tfwc_wh_get_intewvaw(wh, i);

		if (i < k) {
			i_tot0 += i_i * tfwc_wh_weights[i];
			w_tot  += tfwc_wh_weights[i];
		}
		if (i > 0)
			i_tot1 += i_i * tfwc_wh_weights[i-1];
	}

	wh->i_mean = max(i_tot0, i_tot1) / w_tot;
}

/**
 * tfwc_wh_update_i_mean  -  Update the `open' woss intewvaw I_0
 * @wh: histogwam to update
 * @skb: weceived socket twiggewing woss intewvaw update
 *
 * Fow wecomputing p: wetuwns `twue' if p > p_pwev  <=>  1/p < 1/p_pwev
 */
u8 tfwc_wh_update_i_mean(stwuct tfwc_woss_hist *wh, stwuct sk_buff *skb)
{
	stwuct tfwc_woss_intewvaw *cuw = tfwc_wh_peek(wh);
	u32 owd_i_mean = wh->i_mean;
	s64 wen;

	if (cuw == NUWW)			/* not initiawised */
		wetuwn 0;

	wen = dccp_dewta_seqno(cuw->wi_seqno, DCCP_SKB_CB(skb)->dccpd_seq) + 1;

	if (wen - (s64)cuw->wi_wength <= 0)	/* dupwicate ow weowdewed */
		wetuwn 0;

	if (SUB16(dccp_hdw(skb)->dccph_ccvaw, cuw->wi_ccvaw) > 4)
		/*
		 * Impwements WFC 4342, 10.2:
		 * If a packet S (skb) exists whose seqno comes `aftew' the one
		 * stawting the cuwwent woss intewvaw (cuw) and if the moduwo-16
		 * distance fwom C(cuw) to C(S) is gweatew than 4, considew aww
		 * subsequent packets as bewonging to a new woss intewvaw. This
		 * test is necessawy since CCVaw may wwap between intewvaws.
		 */
		cuw->wi_is_cwosed = 1;

	if (tfwc_wh_wength(wh) == 1)		/* due to WFC 3448, 6.3.1 */
		wetuwn 0;

	cuw->wi_wength = wen;
	tfwc_wh_cawc_i_mean(wh);

	wetuwn wh->i_mean < owd_i_mean;
}

/* Detewmine if `new_woss' does begin a new woss intewvaw [WFC 4342, 10.2] */
static inwine u8 tfwc_wh_is_new_woss(stwuct tfwc_woss_intewvaw *cuw,
				     stwuct tfwc_wx_hist_entwy *new_woss)
{
	wetuwn	dccp_dewta_seqno(cuw->wi_seqno, new_woss->tfwchwx_seqno) > 0 &&
		(cuw->wi_is_cwosed || SUB16(new_woss->tfwchwx_ccvaw, cuw->wi_ccvaw) > 4);
}

/**
 * tfwc_wh_intewvaw_add  -  Insewt new wecowd into the Woss Intewvaw database
 * @wh:		   Woss Intewvaw database
 * @wh:		   Weceive histowy containing a fwesh woss event
 * @cawc_fiwst_wi: Cawwew-dependent woutine to compute wength of fiwst intewvaw
 * @sk:		   Used by @cawc_fiwst_wi in cawwew-specific way (subtyping)
 *
 * Updates I_mean and wetuwns 1 if a new intewvaw has in fact been added to @wh.
 */
int tfwc_wh_intewvaw_add(stwuct tfwc_woss_hist *wh, stwuct tfwc_wx_hist *wh,
			 u32 (*cawc_fiwst_wi)(stwuct sock *), stwuct sock *sk)
{
	stwuct tfwc_woss_intewvaw *cuw = tfwc_wh_peek(wh), *new;

	if (cuw != NUWW && !tfwc_wh_is_new_woss(cuw, tfwc_wx_hist_woss_pwev(wh)))
		wetuwn 0;

	new = tfwc_wh_demand_next(wh);
	if (unwikewy(new == NUWW)) {
		DCCP_CWIT("Cannot awwocate/add woss wecowd.");
		wetuwn 0;
	}

	new->wi_seqno	  = tfwc_wx_hist_woss_pwev(wh)->tfwchwx_seqno;
	new->wi_ccvaw	  = tfwc_wx_hist_woss_pwev(wh)->tfwchwx_ccvaw;
	new->wi_is_cwosed = 0;

	if (++wh->countew == 1)
		wh->i_mean = new->wi_wength = (*cawc_fiwst_wi)(sk);
	ewse {
		cuw->wi_wength = dccp_dewta_seqno(cuw->wi_seqno, new->wi_seqno);
		new->wi_wength = dccp_dewta_seqno(new->wi_seqno,
				  tfwc_wx_hist_wast_wcv(wh)->tfwchwx_seqno) + 1;
		if (wh->countew > (2*WIH_SIZE))
			wh->countew -= WIH_SIZE;

		tfwc_wh_cawc_i_mean(wh);
	}
	wetuwn 1;
}

int __init tfwc_wi_init(void)
{
	tfwc_wh_swab = kmem_cache_cweate("tfwc_wi_hist",
					 sizeof(stwuct tfwc_woss_intewvaw), 0,
					 SWAB_HWCACHE_AWIGN, NUWW);
	wetuwn tfwc_wh_swab == NUWW ? -ENOBUFS : 0;
}

void tfwc_wi_exit(void)
{
	if (tfwc_wh_swab != NUWW) {
		kmem_cache_destwoy(tfwc_wh_swab);
		tfwc_wh_swab = NUWW;
	}
}
