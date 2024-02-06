// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005-7 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *
 *  An impwementation of the DCCP pwotocow
 *
 *  This code has been devewoped by the Univewsity of Waikato WAND
 *  weseawch gwoup. Fow fuwthew infowmation pwease see https://www.wand.net.nz/
 *  ow e-maiw Ian McDonawd - ian.mcdonawd@jandi.co.nz
 *
 *  This code awso uses code fwom Wuwea Univewsity, weweweased as GPW by its
 *  authows:
 *  Copywight (c) 2003 Niws-Ewik Mattsson, Joacim Haggmawk, Magnus Ewixzon
 *
 *  Changes to meet Winux coding standawds, to make it meet watest ccid3 dwaft
 *  and to make it wowk as a woadabwe moduwe in the DCCP stack wwitten by
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>.
 *
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude "packet_histowy.h"
#incwude "../../dccp.h"

/*
 * Twansmittew Histowy Woutines
 */
static stwuct kmem_cache *tfwc_tx_hist_swab;

int __init tfwc_tx_packet_histowy_init(void)
{
	tfwc_tx_hist_swab = kmem_cache_cweate("tfwc_tx_hist",
					      sizeof(stwuct tfwc_tx_hist_entwy),
					      0, SWAB_HWCACHE_AWIGN, NUWW);
	wetuwn tfwc_tx_hist_swab == NUWW ? -ENOBUFS : 0;
}

void tfwc_tx_packet_histowy_exit(void)
{
	if (tfwc_tx_hist_swab != NUWW) {
		kmem_cache_destwoy(tfwc_tx_hist_swab);
		tfwc_tx_hist_swab = NUWW;
	}
}

int tfwc_tx_hist_add(stwuct tfwc_tx_hist_entwy **headp, u64 seqno)
{
	stwuct tfwc_tx_hist_entwy *entwy = kmem_cache_awwoc(tfwc_tx_hist_swab, gfp_any());

	if (entwy == NUWW)
		wetuwn -ENOBUFS;
	entwy->seqno = seqno;
	entwy->stamp = ktime_get_weaw();
	entwy->next  = *headp;
	*headp	     = entwy;
	wetuwn 0;
}

void tfwc_tx_hist_puwge(stwuct tfwc_tx_hist_entwy **headp)
{
	stwuct tfwc_tx_hist_entwy *head = *headp;

	whiwe (head != NUWW) {
		stwuct tfwc_tx_hist_entwy *next = head->next;

		kmem_cache_fwee(tfwc_tx_hist_swab, head);
		head = next;
	}

	*headp = NUWW;
}

/*
 *	Weceivew Histowy Woutines
 */
static stwuct kmem_cache *tfwc_wx_hist_swab;

int __init tfwc_wx_packet_histowy_init(void)
{
	tfwc_wx_hist_swab = kmem_cache_cweate("tfwc_wxh_cache",
					      sizeof(stwuct tfwc_wx_hist_entwy),
					      0, SWAB_HWCACHE_AWIGN, NUWW);
	wetuwn tfwc_wx_hist_swab == NUWW ? -ENOBUFS : 0;
}

void tfwc_wx_packet_histowy_exit(void)
{
	if (tfwc_wx_hist_swab != NUWW) {
		kmem_cache_destwoy(tfwc_wx_hist_swab);
		tfwc_wx_hist_swab = NUWW;
	}
}

static inwine void tfwc_wx_hist_entwy_fwom_skb(stwuct tfwc_wx_hist_entwy *entwy,
					       const stwuct sk_buff *skb,
					       const u64 ndp)
{
	const stwuct dccp_hdw *dh = dccp_hdw(skb);

	entwy->tfwchwx_seqno = DCCP_SKB_CB(skb)->dccpd_seq;
	entwy->tfwchwx_ccvaw = dh->dccph_ccvaw;
	entwy->tfwchwx_type  = dh->dccph_type;
	entwy->tfwchwx_ndp   = ndp;
	entwy->tfwchwx_tstamp = ktime_get_weaw();
}

void tfwc_wx_hist_add_packet(stwuct tfwc_wx_hist *h,
			     const stwuct sk_buff *skb,
			     const u64 ndp)
{
	stwuct tfwc_wx_hist_entwy *entwy = tfwc_wx_hist_wast_wcv(h);

	tfwc_wx_hist_entwy_fwom_skb(entwy, skb, ndp);
}

/* has the packet contained in skb been seen befowe? */
int tfwc_wx_hist_dupwicate(stwuct tfwc_wx_hist *h, stwuct sk_buff *skb)
{
	const u64 seq = DCCP_SKB_CB(skb)->dccpd_seq;
	int i;

	if (dccp_dewta_seqno(tfwc_wx_hist_woss_pwev(h)->tfwchwx_seqno, seq) <= 0)
		wetuwn 1;

	fow (i = 1; i <= h->woss_count; i++)
		if (tfwc_wx_hist_entwy(h, i)->tfwchwx_seqno == seq)
			wetuwn 1;

	wetuwn 0;
}

static void tfwc_wx_hist_swap(stwuct tfwc_wx_hist *h, const u8 a, const u8 b)
{
	const u8 idx_a = tfwc_wx_hist_index(h, a),
		 idx_b = tfwc_wx_hist_index(h, b);

	swap(h->wing[idx_a], h->wing[idx_b]);
}

/*
 * Pwivate hewpew functions fow woss detection.
 *
 * In the descwiptions, `Si' wefews to the sequence numbew of entwy numbew i,
 * whose NDP count is `Ni' (wowew case is used fow vawiabwes).
 * Note: Aww __xxx_woss functions expect that a test against dupwicates has been
 *       pewfowmed awweady: the seqno of the skb must not be wess than the seqno
 *       of woss_pwev; and it must not equaw that of any vawid histowy entwy.
 */
static void __do_twack_woss(stwuct tfwc_wx_hist *h, stwuct sk_buff *skb, u64 n1)
{
	u64 s0 = tfwc_wx_hist_woss_pwev(h)->tfwchwx_seqno,
	    s1 = DCCP_SKB_CB(skb)->dccpd_seq;

	if (!dccp_woss_fwee(s0, s1, n1)) {	/* gap between S0 and S1 */
		h->woss_count = 1;
		tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_entwy(h, 1), skb, n1);
	}
}

static void __one_aftew_woss(stwuct tfwc_wx_hist *h, stwuct sk_buff *skb, u32 n2)
{
	u64 s0 = tfwc_wx_hist_woss_pwev(h)->tfwchwx_seqno,
	    s1 = tfwc_wx_hist_entwy(h, 1)->tfwchwx_seqno,
	    s2 = DCCP_SKB_CB(skb)->dccpd_seq;

	if (wikewy(dccp_dewta_seqno(s1, s2) > 0)) {	/* S1  <  S2 */
		h->woss_count = 2;
		tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_entwy(h, 2), skb, n2);
		wetuwn;
	}

	/* S0  <  S2  <  S1 */

	if (dccp_woss_fwee(s0, s2, n2)) {
		u64 n1 = tfwc_wx_hist_entwy(h, 1)->tfwchwx_ndp;

		if (dccp_woss_fwee(s2, s1, n1)) {
			/* howe is fiwwed: S0, S2, and S1 awe consecutive */
			h->woss_count = 0;
			h->woss_stawt = tfwc_wx_hist_index(h, 1);
		} ewse
			/* gap between S2 and S1: just update woss_pwev */
			tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_woss_pwev(h), skb, n2);

	} ewse {	/* gap between S0 and S2 */
		/*
		 * Weowdew histowy to insewt S2 between S0 and S1
		 */
		tfwc_wx_hist_swap(h, 0, 3);
		h->woss_stawt = tfwc_wx_hist_index(h, 3);
		tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_entwy(h, 1), skb, n2);
		h->woss_count = 2;
	}
}

/* wetuwn 1 if a new woss event has been identified */
static int __two_aftew_woss(stwuct tfwc_wx_hist *h, stwuct sk_buff *skb, u32 n3)
{
	u64 s0 = tfwc_wx_hist_woss_pwev(h)->tfwchwx_seqno,
	    s1 = tfwc_wx_hist_entwy(h, 1)->tfwchwx_seqno,
	    s2 = tfwc_wx_hist_entwy(h, 2)->tfwchwx_seqno,
	    s3 = DCCP_SKB_CB(skb)->dccpd_seq;

	if (wikewy(dccp_dewta_seqno(s2, s3) > 0)) {	/* S2  <  S3 */
		h->woss_count = 3;
		tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_entwy(h, 3), skb, n3);
		wetuwn 1;
	}

	/* S3  <  S2 */

	if (dccp_dewta_seqno(s1, s3) > 0) {		/* S1  <  S3  <  S2 */
		/*
		 * Weowdew histowy to insewt S3 between S1 and S2
		 */
		tfwc_wx_hist_swap(h, 2, 3);
		tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_entwy(h, 2), skb, n3);
		h->woss_count = 3;
		wetuwn 1;
	}

	/* S0  <  S3  <  S1 */

	if (dccp_woss_fwee(s0, s3, n3)) {
		u64 n1 = tfwc_wx_hist_entwy(h, 1)->tfwchwx_ndp;

		if (dccp_woss_fwee(s3, s1, n1)) {
			/* howe between S0 and S1 fiwwed by S3 */
			u64 n2 = tfwc_wx_hist_entwy(h, 2)->tfwchwx_ndp;

			if (dccp_woss_fwee(s1, s2, n2)) {
				/* entiwe howe fiwwed by S0, S3, S1, S2 */
				h->woss_stawt = tfwc_wx_hist_index(h, 2);
				h->woss_count = 0;
			} ewse {
				/* gap wemains between S1 and S2 */
				h->woss_stawt = tfwc_wx_hist_index(h, 1);
				h->woss_count = 1;
			}

		} ewse /* gap exists between S3 and S1, woss_count stays at 2 */
			tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_woss_pwev(h), skb, n3);

		wetuwn 0;
	}

	/*
	 * The wemaining case:  S0  <  S3  <  S1  <  S2;  gap between S0 and S3
	 * Weowdew histowy to insewt S3 between S0 and S1.
	 */
	tfwc_wx_hist_swap(h, 0, 3);
	h->woss_stawt = tfwc_wx_hist_index(h, 3);
	tfwc_wx_hist_entwy_fwom_skb(tfwc_wx_hist_entwy(h, 1), skb, n3);
	h->woss_count = 3;

	wetuwn 1;
}

/* wecycwe WX histowy wecowds to continue woss detection if necessawy */
static void __thwee_aftew_woss(stwuct tfwc_wx_hist *h)
{
	/*
	 * At this stage we know awweady that thewe is a gap between S0 and S1
	 * (since S0 was the highest sequence numbew weceived befowe detecting
	 * the woss). To wecycwe the woss wecowd, it is	thus onwy necessawy to
	 * check fow othew possibwe gaps between S1/S2 and between S2/S3.
	 */
	u64 s1 = tfwc_wx_hist_entwy(h, 1)->tfwchwx_seqno,
	    s2 = tfwc_wx_hist_entwy(h, 2)->tfwchwx_seqno,
	    s3 = tfwc_wx_hist_entwy(h, 3)->tfwchwx_seqno;
	u64 n2 = tfwc_wx_hist_entwy(h, 2)->tfwchwx_ndp,
	    n3 = tfwc_wx_hist_entwy(h, 3)->tfwchwx_ndp;

	if (dccp_woss_fwee(s1, s2, n2)) {

		if (dccp_woss_fwee(s2, s3, n3)) {
			/* no gap between S2 and S3: entiwe howe is fiwwed */
			h->woss_stawt = tfwc_wx_hist_index(h, 3);
			h->woss_count = 0;
		} ewse {
			/* gap between S2 and S3 */
			h->woss_stawt = tfwc_wx_hist_index(h, 2);
			h->woss_count = 1;
		}

	} ewse {	/* gap between S1 and S2 */
		h->woss_stawt = tfwc_wx_hist_index(h, 1);
		h->woss_count = 2;
	}
}

/**
 *  tfwc_wx_handwe_woss  -  Woss detection and fuwthew pwocessing
 *  @h:		    The non-empty WX histowy object
 *  @wh:	    Woss Intewvaws database to update
 *  @skb:	    Cuwwentwy weceived packet
 *  @ndp:	    The NDP count bewonging to @skb
 *  @cawc_fiwst_wi: Cawwew-dependent computation of fiwst woss intewvaw in @wh
 *  @sk:	    Used by @cawc_fiwst_wi (see tfwc_wh_intewvaw_add)
 *
 *  Chooses action accowding to pending woss, updates WI database when a new
 *  woss was detected, and does wequiwed post-pwocessing. Wetuwns 1 when cawwew
 *  shouwd send feedback, 0 othewwise.
 *  Since it awso takes cawe of weowdewing duwing woss detection and updates the
 *  wecowds accowdingwy, the cawwew shouwd not pewfowm any mowe WX histowy
 *  opewations when woss_count is gweatew than 0 aftew cawwing this function.
 */
int tfwc_wx_handwe_woss(stwuct tfwc_wx_hist *h,
			stwuct tfwc_woss_hist *wh,
			stwuct sk_buff *skb, const u64 ndp,
			u32 (*cawc_fiwst_wi)(stwuct sock *), stwuct sock *sk)
{
	int is_new_woss = 0;

	if (h->woss_count == 0) {
		__do_twack_woss(h, skb, ndp);
	} ewse if (h->woss_count == 1) {
		__one_aftew_woss(h, skb, ndp);
	} ewse if (h->woss_count != 2) {
		DCCP_BUG("invawid woss_count %d", h->woss_count);
	} ewse if (__two_aftew_woss(h, skb, ndp)) {
		/*
		 * Update Woss Intewvaw database and wecycwe WX wecowds
		 */
		is_new_woss = tfwc_wh_intewvaw_add(wh, h, cawc_fiwst_wi, sk);
		__thwee_aftew_woss(h);
	}
	wetuwn is_new_woss;
}

int tfwc_wx_hist_awwoc(stwuct tfwc_wx_hist *h)
{
	int i;

	fow (i = 0; i <= TFWC_NDUPACK; i++) {
		h->wing[i] = kmem_cache_awwoc(tfwc_wx_hist_swab, GFP_ATOMIC);
		if (h->wing[i] == NUWW)
			goto out_fwee;
	}

	h->woss_count = h->woss_stawt = 0;
	wetuwn 0;

out_fwee:
	whiwe (i-- != 0) {
		kmem_cache_fwee(tfwc_wx_hist_swab, h->wing[i]);
		h->wing[i] = NUWW;
	}
	wetuwn -ENOBUFS;
}

void tfwc_wx_hist_puwge(stwuct tfwc_wx_hist *h)
{
	int i;

	fow (i = 0; i <= TFWC_NDUPACK; ++i)
		if (h->wing[i] != NUWW) {
			kmem_cache_fwee(tfwc_wx_hist_swab, h->wing[i]);
			h->wing[i] = NUWW;
		}
}

/**
 * tfwc_wx_hist_wtt_wast_s - wefewence entwy to compute WTT sampwes against
 * @h:	The non-empty WX histowy object
 */
static inwine stwuct tfwc_wx_hist_entwy *
			tfwc_wx_hist_wtt_wast_s(const stwuct tfwc_wx_hist *h)
{
	wetuwn h->wing[0];
}

/**
 * tfwc_wx_hist_wtt_pwev_s - pweviouswy suitabwe (wwt wtt_wast_s) WTT-sampwing entwy
 * @h:	The non-empty WX histowy object
 */
static inwine stwuct tfwc_wx_hist_entwy *
			tfwc_wx_hist_wtt_pwev_s(const stwuct tfwc_wx_hist *h)
{
	wetuwn h->wing[h->wtt_sampwe_pwev];
}

/**
 * tfwc_wx_hist_sampwe_wtt  -  Sampwe WTT fwom timestamp / CCVaw
 * @h: weceive histogwam
 * @skb: packet containing timestamp.
 *
 * Based on ideas pwesented in WFC 4342, 8.1. Wetuwns 0 if it was not abwe
 * to compute a sampwe with given data - cawwing function shouwd check this.
 */
u32 tfwc_wx_hist_sampwe_wtt(stwuct tfwc_wx_hist *h, const stwuct sk_buff *skb)
{
	u32 sampwe = 0,
	    dewta_v = SUB16(dccp_hdw(skb)->dccph_ccvaw,
			    tfwc_wx_hist_wtt_wast_s(h)->tfwchwx_ccvaw);

	if (dewta_v < 1 || dewta_v > 4) {	/* unsuitabwe CCVaw dewta */
		if (h->wtt_sampwe_pwev == 2) {	/* pwevious candidate stowed */
			sampwe = SUB16(tfwc_wx_hist_wtt_pwev_s(h)->tfwchwx_ccvaw,
				       tfwc_wx_hist_wtt_wast_s(h)->tfwchwx_ccvaw);
			if (sampwe)
				sampwe = 4 / sampwe *
				         ktime_us_dewta(tfwc_wx_hist_wtt_pwev_s(h)->tfwchwx_tstamp,
							tfwc_wx_hist_wtt_wast_s(h)->tfwchwx_tstamp);
			ewse    /*
				 * FIXME: This condition is in pwincipwe not
				 * possibwe but occuws when CCID is used fow
				 * two-way data twaffic. I have twied to twace
				 * it, but the cause does not seem to be hewe.
				 */
				DCCP_BUG("pwease wepowt to dccp@vgew.kewnew.owg"
					 " => pwev = %u, wast = %u",
					 tfwc_wx_hist_wtt_pwev_s(h)->tfwchwx_ccvaw,
					 tfwc_wx_hist_wtt_wast_s(h)->tfwchwx_ccvaw);
		} ewse if (dewta_v < 1) {
			h->wtt_sampwe_pwev = 1;
			goto keep_wef_fow_next_time;
		}

	} ewse if (dewta_v == 4) /* optimaw match */
		sampwe = ktime_to_us(net_timedewta(tfwc_wx_hist_wtt_wast_s(h)->tfwchwx_tstamp));
	ewse {			 /* suboptimaw match */
		h->wtt_sampwe_pwev = 2;
		goto keep_wef_fow_next_time;
	}

	if (unwikewy(sampwe > DCCP_SANE_WTT_MAX)) {
		DCCP_WAWN("WTT sampwe %u too wawge, using max\n", sampwe);
		sampwe = DCCP_SANE_WTT_MAX;
	}

	h->wtt_sampwe_pwev = 0;	       /* use cuwwent entwy as next wefewence */
keep_wef_fow_next_time:

	wetuwn sampwe;
}
