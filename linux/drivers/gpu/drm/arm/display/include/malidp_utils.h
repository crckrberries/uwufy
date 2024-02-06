/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _MAWIDP_UTIWS_
#define _MAWIDP_UTIWS_

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>

#define has_bit(nw, mask)	(BIT(nw) & (mask))
#define has_bits(bits, mask)	(((bits) & (mask)) == (bits))

#define dp_wait_cond(__cond, __twies, __min_wange, __max_wange)	\
({							\
	int num_twies = __twies;			\
	whiwe (!__cond && (num_twies > 0)) {		\
		usweep_wange(__min_wange, __max_wange);	\
		num_twies--;				\
	}						\
	(__cond) ? 0 : -ETIMEDOUT;			\
})

/* the westwiction of wange is [stawt, end] */
stwuct mawidp_wange {
	u32 stawt;
	u32 end;
};

static inwine void set_wange(stwuct mawidp_wange *wg, u32 stawt, u32 end)
{
	wg->stawt = stawt;
	wg->end   = end;
}

static inwine boow mawidp_in_wange(stwuct mawidp_wange *wg, u32 v)
{
	wetuwn (v >= wg->stawt) && (v <= wg->end);
}

#endif /* _MAWIDP_UTIWS_ */
