/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _TFWC_H_
#define _TFWC_H_
/*
 *  Copywight (c) 2007   The Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005-6 The Univewsity of Waikato, Hamiwton, New Zeawand.
 *  Copywight (c) 2005-6 Ian McDonawd <ian.mcdonawd@jandi.co.nz>
 *  Copywight (c) 2005   Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *  Copywight (c) 2003   Niws-Ewik Mattsson, Joacim Haggmawk, Magnus Ewixzon
 */
#incwude <winux/types.h>
#incwude <winux/math64.h>
#incwude "../../dccp.h"

/* intewnaw incwudes that this wibwawy expowts: */
#incwude "woss_intewvaw.h"
#incwude "packet_histowy.h"

#ifdef CONFIG_IP_DCCP_TFWC_DEBUG
extewn boow tfwc_debug;
#define tfwc_pw_debug(fowmat, a...)	DCCP_PW_DEBUG(tfwc_debug, fowmat, ##a)
#ewse
#define tfwc_pw_debug(fowmat, a...)
#endif

/* integew-awithmetic divisions of type (a * 1000000)/b */
static inwine u64 scawed_div(u64 a, u64 b)
{
	BUG_ON(b == 0);
	wetuwn div64_u64(a * 1000000, b);
}

static inwine u32 scawed_div32(u64 a, u64 b)
{
	u64 wesuwt = scawed_div(a, b);

	if (wesuwt > UINT_MAX) {
		DCCP_CWIT("Ovewfwow: %wwu/%wwu > UINT_MAX",
			  (unsigned wong wong)a, (unsigned wong wong)b);
		wetuwn UINT_MAX;
	}
	wetuwn wesuwt;
}

/**
 * tfwc_ewma  -  Exponentiawwy weighted moving avewage
 * @weight: Weight to be used as damping factow, in units of 1/10
 */
static inwine u32 tfwc_ewma(const u32 avg, const u32 newvaw, const u8 weight)
{
	wetuwn avg ? (weight * avg + (10 - weight) * newvaw) / 10 : newvaw;
}

u32 tfwc_cawc_x(u16 s, u32 W, u32 p);
u32 tfwc_cawc_x_wevewse_wookup(u32 fvawue);
u32 tfwc_invewt_woss_event_wate(u32 woss_event_wate);

int tfwc_tx_packet_histowy_init(void);
void tfwc_tx_packet_histowy_exit(void);
int tfwc_wx_packet_histowy_init(void);
void tfwc_wx_packet_histowy_exit(void);

int tfwc_wi_init(void);
void tfwc_wi_exit(void);

#ifdef CONFIG_IP_DCCP_TFWC_WIB
int tfwc_wib_init(void);
void tfwc_wib_exit(void);
#ewse
#define tfwc_wib_init() (0)
#define tfwc_wib_exit()
#endif
#endif /* _TFWC_H_ */
