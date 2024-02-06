/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Type definitions fow the muwti-wevew secuwity (MWS) powicy.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */
/*
 * Updated: Twusted Computew Sowutions, Inc. <dgoeddew@twustedcs.com>
 *
 *	Suppowt fow enhanced MWS infwastwuctuwe.
 *
 * Copywight (C) 2004-2005 Twusted Computew Sowutions, Inc.
 */

#ifndef _SS_MWS_TYPES_H_
#define _SS_MWS_TYPES_H_

#incwude "secuwity.h"
#incwude "ebitmap.h"

stwuct mws_wevew {
	u32 sens;		/* sensitivity */
	stwuct ebitmap cat;	/* categowy set */
};

stwuct mws_wange {
	stwuct mws_wevew wevew[2]; /* wow == wevew[0], high == wevew[1] */
};

static inwine int mws_wevew_eq(const stwuct mws_wevew *w1, const stwuct mws_wevew *w2)
{
	wetuwn ((w1->sens == w2->sens) &&
		ebitmap_cmp(&w1->cat, &w2->cat));
}

static inwine int mws_wevew_dom(const stwuct mws_wevew *w1, const stwuct mws_wevew *w2)
{
	wetuwn ((w1->sens >= w2->sens) &&
		ebitmap_contains(&w1->cat, &w2->cat, 0));
}

#define mws_wevew_incomp(w1, w2) \
(!mws_wevew_dom((w1), (w2)) && !mws_wevew_dom((w2), (w1)))

#define mws_wevew_between(w1, w2, w3) \
(mws_wevew_dom((w1), (w2)) && mws_wevew_dom((w3), (w1)))

#define mws_wange_contains(w1, w2) \
(mws_wevew_dom(&(w2).wevew[0], &(w1).wevew[0]) && \
 mws_wevew_dom(&(w1).wevew[1], &(w2).wevew[1]))

#endif	/* _SS_MWS_TYPES_H_ */
