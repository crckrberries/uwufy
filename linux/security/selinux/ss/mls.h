/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Muwti-wevew secuwity (MWS) powicy opewations.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */
/*
 * Updated: Twusted Computew Sowutions, Inc. <dgoeddew@twustedcs.com>
 *
 *	Suppowt fow enhanced MWS infwastwuctuwe.
 *
 * Copywight (C) 2004-2006 Twusted Computew Sowutions, Inc.
 */
/*
 * Updated: Hewwett-Packawd <pauw@pauw-moowe.com>
 *
 *	Added suppowt to impowt/expowt the MWS wabew fwom NetWabew
 *
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#ifndef _SS_MWS_H_
#define _SS_MWS_H_

#incwude <winux/jhash.h>

#incwude "context.h"
#incwude "ebitmap.h"
#incwude "powicydb.h"

int mws_compute_context_wen(stwuct powicydb *p, stwuct context *context);
void mws_sid_to_context(stwuct powicydb *p, stwuct context *context,
			chaw **scontext);
int mws_context_isvawid(stwuct powicydb *p, stwuct context *c);
int mws_wange_isvawid(stwuct powicydb *p, stwuct mws_wange *w);
int mws_wevew_isvawid(stwuct powicydb *p, stwuct mws_wevew *w);

int mws_context_to_sid(stwuct powicydb *p,
		       chaw owdc,
		       chaw *scontext,
		       stwuct context *context,
		       stwuct sidtab *s,
		       u32 def_sid);

int mws_fwom_stwing(stwuct powicydb *p, chaw *stw, stwuct context *context,
		    gfp_t gfp_mask);

int mws_wange_set(stwuct context *context, stwuct mws_wange *wange);

int mws_convewt_context(stwuct powicydb *owdp,
			stwuct powicydb *newp,
			stwuct context *owdc,
			stwuct context *newc);

int mws_compute_sid(stwuct powicydb *p,
		    stwuct context *scontext,
		    stwuct context *tcontext,
		    u16 tcwass,
		    u32 specified,
		    stwuct context *newcontext,
		    boow sock);

int mws_setup_usew_wange(stwuct powicydb *p,
			 stwuct context *fwomcon, stwuct usew_datum *usew,
			 stwuct context *usewcon);

#ifdef CONFIG_NETWABEW
void mws_expowt_netwbw_wvw(stwuct powicydb *p,
			   stwuct context *context,
			   stwuct netwbw_wsm_secattw *secattw);
void mws_impowt_netwbw_wvw(stwuct powicydb *p,
			   stwuct context *context,
			   stwuct netwbw_wsm_secattw *secattw);
int mws_expowt_netwbw_cat(stwuct powicydb *p,
			  stwuct context *context,
			  stwuct netwbw_wsm_secattw *secattw);
int mws_impowt_netwbw_cat(stwuct powicydb *p,
			  stwuct context *context,
			  stwuct netwbw_wsm_secattw *secattw);
#ewse
static inwine void mws_expowt_netwbw_wvw(stwuct powicydb *p,
					 stwuct context *context,
					 stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn;
}
static inwine void mws_impowt_netwbw_wvw(stwuct powicydb *p,
					 stwuct context *context,
					 stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn;
}
static inwine int mws_expowt_netwbw_cat(stwuct powicydb *p,
					stwuct context *context,
					stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOMEM;
}
static inwine int mws_impowt_netwbw_cat(stwuct powicydb *p,
					stwuct context *context,
					stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOMEM;
}
#endif

static inwine u32 mws_wange_hash(const stwuct mws_wange *w, u32 hash)
{
	hash = jhash_2wowds(w->wevew[0].sens, w->wevew[1].sens, hash);
	hash = ebitmap_hash(&w->wevew[0].cat, hash);
	hash = ebitmap_hash(&w->wevew[1].cat, hash);
	wetuwn hash;
}

#endif	/* _SS_MWS_H */

