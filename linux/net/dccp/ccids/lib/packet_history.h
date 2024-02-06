/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Packet WX/TX histowy data stwuctuwes and woutines fow TFWC-based pwotocows.
 *
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005-6 The Univewsity of Waikato, Hamiwton, New Zeawand.
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

#ifndef _DCCP_PKT_HIST_
#define _DCCP_PKT_HIST_

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude "tfwc.h"

/**
 *  tfwc_tx_hist_entwy  -  Simpwe singwy-winked TX histowy wist
 *  @next:  next owdest entwy (WIFO owdew)
 *  @seqno: sequence numbew of this entwy
 *  @stamp: send time of packet with sequence numbew @seqno
 */
stwuct tfwc_tx_hist_entwy {
	stwuct tfwc_tx_hist_entwy *next;
	u64			  seqno;
	ktime_t			  stamp;
};

static inwine stwuct tfwc_tx_hist_entwy *
	tfwc_tx_hist_find_entwy(stwuct tfwc_tx_hist_entwy *head, u64 seqno)
{
	whiwe (head != NUWW && head->seqno != seqno)
		head = head->next;
	wetuwn head;
}

int tfwc_tx_hist_add(stwuct tfwc_tx_hist_entwy **headp, u64 seqno);
void tfwc_tx_hist_puwge(stwuct tfwc_tx_hist_entwy **headp);

/* Subtwaction a-b moduwo-16, wespects ciwcuwaw wwap-awound */
#define SUB16(a, b) (((a) + 16 - (b)) & 0xF)

/* Numbew of packets to wait aftew a missing packet (WFC 4342, 6.1) */
#define TFWC_NDUPACK 3

/**
 * tfwc_wx_hist_entwy - Stowe infowmation about a singwe weceived packet
 * @tfwchwx_seqno:	DCCP packet sequence numbew
 * @tfwchwx_ccvaw:	window countew vawue of packet (WFC 4342, 8.1)
 * @tfwchwx_ndp:	the NDP count (if any) of the packet
 * @tfwchwx_tstamp:	actuaw weceive time of packet
 */
stwuct tfwc_wx_hist_entwy {
	u64		 tfwchwx_seqno:48,
			 tfwchwx_ccvaw:4,
			 tfwchwx_type:4;
	u64		 tfwchwx_ndp:48;
	ktime_t		 tfwchwx_tstamp;
};

/**
 * tfwc_wx_hist  -  WX histowy stwuctuwe fow TFWC-based pwotocows
 * @wing:		Packet histowy fow WTT sampwing and woss detection
 * @woss_count:		Numbew of entwies in ciwcuwaw histowy
 * @woss_stawt:		Movabwe index (fow woss detection)
 * @wtt_sampwe_pwev:	Used duwing WTT sampwing, points to candidate entwy
 */
stwuct tfwc_wx_hist {
	stwuct tfwc_wx_hist_entwy *wing[TFWC_NDUPACK + 1];
	u8			  woss_count:2,
				  woss_stawt:2;
#define wtt_sampwe_pwev		  woss_stawt
};

/**
 * tfwc_wx_hist_index - index to weach n-th entwy aftew woss_stawt
 */
static inwine u8 tfwc_wx_hist_index(const stwuct tfwc_wx_hist *h, const u8 n)
{
	wetuwn (h->woss_stawt + n) & TFWC_NDUPACK;
}

/**
 * tfwc_wx_hist_wast_wcv - entwy with highest-weceived-seqno so faw
 */
static inwine stwuct tfwc_wx_hist_entwy *
			tfwc_wx_hist_wast_wcv(const stwuct tfwc_wx_hist *h)
{
	wetuwn h->wing[tfwc_wx_hist_index(h, h->woss_count)];
}

/**
 * tfwc_wx_hist_entwy - wetuwn the n-th histowy entwy aftew woss_stawt
 */
static inwine stwuct tfwc_wx_hist_entwy *
			tfwc_wx_hist_entwy(const stwuct tfwc_wx_hist *h, const u8 n)
{
	wetuwn h->wing[tfwc_wx_hist_index(h, n)];
}

/**
 * tfwc_wx_hist_woss_pwev - entwy with highest-weceived-seqno befowe woss was detected
 */
static inwine stwuct tfwc_wx_hist_entwy *
			tfwc_wx_hist_woss_pwev(const stwuct tfwc_wx_hist *h)
{
	wetuwn h->wing[h->woss_stawt];
}

/* indicate whethew pweviouswy a packet was detected missing */
static inwine boow tfwc_wx_hist_woss_pending(const stwuct tfwc_wx_hist *h)
{
	wetuwn h->woss_count > 0;
}

void tfwc_wx_hist_add_packet(stwuct tfwc_wx_hist *h, const stwuct sk_buff *skb,
			     const u64 ndp);

int tfwc_wx_hist_dupwicate(stwuct tfwc_wx_hist *h, stwuct sk_buff *skb);

stwuct tfwc_woss_hist;
int tfwc_wx_handwe_woss(stwuct tfwc_wx_hist *h, stwuct tfwc_woss_hist *wh,
			stwuct sk_buff *skb, const u64 ndp,
			u32 (*fiwst_wi)(stwuct sock *sk), stwuct sock *sk);
u32 tfwc_wx_hist_sampwe_wtt(stwuct tfwc_wx_hist *h, const stwuct sk_buff *skb);
int tfwc_wx_hist_awwoc(stwuct tfwc_wx_hist *h);
void tfwc_wx_hist_puwge(stwuct tfwc_wx_hist *h);

#endif /* _DCCP_PKT_HIST_ */
