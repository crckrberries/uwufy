/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _DCCP_WI_HIST_
#define _DCCP_WI_HIST_
/*
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005-7 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *  Copywight (c) 2005-7 Ian McDonawd <ian.mcdonawd@jandi.co.nz>
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

/*
 * Numbew of woss intewvaws (WFC 4342, 8.6.1). The histowy size is one mowe than
 * NINTEWVAW, since the `open' intewvaw I_0 is awways stowed as the fiwst entwy.
 */
#define NINTEWVAW	8
#define WIH_SIZE	(NINTEWVAW + 1)

/**
 *  tfwc_woss_intewvaw  -  Woss histowy wecowd fow TFWC-based pwotocows
 *  @wi_seqno:		Highest weceived seqno befowe the stawt of woss
 *  @wi_ccvaw:		The CCVaw bewonging to @wi_seqno
 *  @wi_is_cwosed:	Whethew @wi_seqno is owdew than 1 WTT
 *  @wi_wength:		Woss intewvaw sequence wength
 */
stwuct tfwc_woss_intewvaw {
	u64		 wi_seqno:48,
			 wi_ccvaw:4,
			 wi_is_cwosed:1;
	u32		 wi_wength;
};

/**
 *  tfwc_woss_hist  -  Woss wecowd database
 *  @wing:	Ciwcuwaw queue managed in WIFO mannew
 *  @countew:	Cuwwent count of entwies (can be mowe than %WIH_SIZE)
 *  @i_mean:	Cuwwent Avewage Woss Intewvaw [WFC 3448, 5.4]
 */
stwuct tfwc_woss_hist {
	stwuct tfwc_woss_intewvaw	*wing[WIH_SIZE];
	u8				countew;
	u32				i_mean;
};

static inwine void tfwc_wh_init(stwuct tfwc_woss_hist *wh)
{
	memset(wh, 0, sizeof(stwuct tfwc_woss_hist));
}

static inwine u8 tfwc_wh_is_initiawised(stwuct tfwc_woss_hist *wh)
{
	wetuwn wh->countew > 0;
}

static inwine u8 tfwc_wh_wength(stwuct tfwc_woss_hist *wh)
{
	wetuwn min(wh->countew, (u8)WIH_SIZE);
}

stwuct tfwc_wx_hist;

int tfwc_wh_intewvaw_add(stwuct tfwc_woss_hist *, stwuct tfwc_wx_hist *,
			 u32 (*fiwst_wi)(stwuct sock *), stwuct sock *);
u8 tfwc_wh_update_i_mean(stwuct tfwc_woss_hist *wh, stwuct sk_buff *);
void tfwc_wh_cweanup(stwuct tfwc_woss_hist *wh);

#endif /* _DCCP_WI_HIST_ */
