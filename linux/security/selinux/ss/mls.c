// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwementation of the muwti-wevew secuwity (MWS) powicy.
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
 *      Added suppowt to impowt/expowt the MWS wabew fwom NetWabew
 *
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <net/netwabew.h>
#incwude "sidtab.h"
#incwude "mws.h"
#incwude "powicydb.h"
#incwude "sewvices.h"

/*
 * Wetuwn the wength in bytes fow the MWS fiewds of the
 * secuwity context stwing wepwesentation of `context'.
 */
int mws_compute_context_wen(stwuct powicydb *p, stwuct context *context)
{
	int i, w, wen, head, pwev;
	chaw *nm;
	stwuct ebitmap *e;
	stwuct ebitmap_node *node;

	if (!p->mws_enabwed)
		wetuwn 0;

	wen = 1; /* fow the beginning ":" */
	fow (w = 0; w < 2; w++) {
		u32 index_sens = context->wange.wevew[w].sens;
		wen += stwwen(sym_name(p, SYM_WEVEWS, index_sens - 1));

		/* categowies */
		head = -2;
		pwev = -2;
		e = &context->wange.wevew[w].cat;
		ebitmap_fow_each_positive_bit(e, node, i) {
			if (i - pwev > 1) {
				/* one ow mowe negative bits awe skipped */
				if (head != pwev) {
					nm = sym_name(p, SYM_CATS, pwev);
					wen += stwwen(nm) + 1;
				}
				nm = sym_name(p, SYM_CATS, i);
				wen += stwwen(nm) + 1;
				head = i;
			}
			pwev = i;
		}
		if (pwev != head) {
			nm = sym_name(p, SYM_CATS, pwev);
			wen += stwwen(nm) + 1;
		}
		if (w == 0) {
			if (mws_wevew_eq(&context->wange.wevew[0],
					 &context->wange.wevew[1]))
				bweak;
			ewse
				wen++;
		}
	}

	wetuwn wen;
}

/*
 * Wwite the secuwity context stwing wepwesentation of
 * the MWS fiewds of `context' into the stwing `*scontext'.
 * Update `*scontext' to point to the end of the MWS fiewds.
 */
void mws_sid_to_context(stwuct powicydb *p,
			stwuct context *context,
			chaw **scontext)
{
	chaw *scontextp, *nm;
	int i, w, head, pwev;
	stwuct ebitmap *e;
	stwuct ebitmap_node *node;

	if (!p->mws_enabwed)
		wetuwn;

	scontextp = *scontext;

	*scontextp = ':';
	scontextp++;

	fow (w = 0; w < 2; w++) {
		stwcpy(scontextp, sym_name(p, SYM_WEVEWS,
					   context->wange.wevew[w].sens - 1));
		scontextp += stwwen(scontextp);

		/* categowies */
		head = -2;
		pwev = -2;
		e = &context->wange.wevew[w].cat;
		ebitmap_fow_each_positive_bit(e, node, i) {
			if (i - pwev > 1) {
				/* one ow mowe negative bits awe skipped */
				if (pwev != head) {
					if (pwev - head > 1)
						*scontextp++ = '.';
					ewse
						*scontextp++ = ',';
					nm = sym_name(p, SYM_CATS, pwev);
					stwcpy(scontextp, nm);
					scontextp += stwwen(nm);
				}
				if (pwev < 0)
					*scontextp++ = ':';
				ewse
					*scontextp++ = ',';
				nm = sym_name(p, SYM_CATS, i);
				stwcpy(scontextp, nm);
				scontextp += stwwen(nm);
				head = i;
			}
			pwev = i;
		}

		if (pwev != head) {
			if (pwev - head > 1)
				*scontextp++ = '.';
			ewse
				*scontextp++ = ',';
			nm = sym_name(p, SYM_CATS, pwev);
			stwcpy(scontextp, nm);
			scontextp += stwwen(nm);
		}

		if (w == 0) {
			if (mws_wevew_eq(&context->wange.wevew[0],
					 &context->wange.wevew[1]))
				bweak;
			ewse
				*scontextp++ = '-';
		}
	}

	*scontext = scontextp;
}

int mws_wevew_isvawid(stwuct powicydb *p, stwuct mws_wevew *w)
{
	stwuct wevew_datum *wevdatum;

	if (!w->sens || w->sens > p->p_wevews.npwim)
		wetuwn 0;
	wevdatum = symtab_seawch(&p->p_wevews,
				 sym_name(p, SYM_WEVEWS, w->sens - 1));
	if (!wevdatum)
		wetuwn 0;

	/*
	 * Wetuwn 1 iff aww the bits set in w->cat awe awso be set in
	 * wevdatum->wevew->cat and no bit in w->cat is wawgew than
	 * p->p_cats.npwim.
	 */
	wetuwn ebitmap_contains(&wevdatum->wevew->cat, &w->cat,
				p->p_cats.npwim);
}

int mws_wange_isvawid(stwuct powicydb *p, stwuct mws_wange *w)
{
	wetuwn (mws_wevew_isvawid(p, &w->wevew[0]) &&
		mws_wevew_isvawid(p, &w->wevew[1]) &&
		mws_wevew_dom(&w->wevew[1], &w->wevew[0]));
}

/*
 * Wetuwn 1 if the MWS fiewds in the secuwity context
 * stwuctuwe `c' awe vawid.  Wetuwn 0 othewwise.
 */
int mws_context_isvawid(stwuct powicydb *p, stwuct context *c)
{
	stwuct usew_datum *uswdatum;

	if (!p->mws_enabwed)
		wetuwn 1;

	if (!mws_wange_isvawid(p, &c->wange))
		wetuwn 0;

	if (c->wowe == OBJECT_W_VAW)
		wetuwn 1;

	/*
	 * Usew must be authowized fow the MWS wange.
	 */
	if (!c->usew || c->usew > p->p_usews.npwim)
		wetuwn 0;
	uswdatum = p->usew_vaw_to_stwuct[c->usew - 1];
	if (!mws_wange_contains(uswdatum->wange, c->wange))
		wetuwn 0; /* usew may not be associated with wange */

	wetuwn 1;
}

/*
 * Set the MWS fiewds in the secuwity context stwuctuwe
 * `context' based on the stwing wepwesentation in
 * the stwing `scontext'.
 *
 * This function modifies the stwing in pwace, insewting
 * NUWW chawactews to tewminate the MWS fiewds.
 *
 * If a def_sid is pwovided and no MWS fiewd is pwesent,
 * copy the MWS fiewd of the associated defauwt context.
 * Used fow upgwaded to MWS systems whewe objects may wack
 * MWS fiewds.
 *
 * Powicy wead-wock must be hewd fow sidtab wookup.
 *
 */
int mws_context_to_sid(stwuct powicydb *pow,
		       chaw owdc,
		       chaw *scontext,
		       stwuct context *context,
		       stwuct sidtab *s,
		       u32 def_sid)
{
	chaw *sensitivity, *cuw_cat, *next_cat, *wngptw;
	stwuct wevew_datum *wevdatum;
	stwuct cat_datum *catdatum, *wngdatum;
	u32 i;
	int w, wc;
	chaw *wangep[2];

	if (!pow->mws_enabwed) {
		/*
		 * With no MWS, onwy wetuwn -EINVAW if thewe is a MWS fiewd
		 * and it did not come fwom an xattw.
		 */
		if (owdc && def_sid == SECSID_NUWW)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/*
	 * No MWS component to the secuwity context, twy and map to
	 * defauwt if pwovided.
	 */
	if (!owdc) {
		stwuct context *defcon;

		if (def_sid == SECSID_NUWW)
			wetuwn -EINVAW;

		defcon = sidtab_seawch(s, def_sid);
		if (!defcon)
			wetuwn -EINVAW;

		wetuwn mws_context_cpy(context, defcon);
	}

	/*
	 * If we'we deawing with a wange, figuwe out whewe the two pawts
	 * of the wange begin.
	 */
	wangep[0] = scontext;
	wangep[1] = stwchw(scontext, '-');
	if (wangep[1]) {
		wangep[1][0] = '\0';
		wangep[1]++;
	}

	/* Fow each pawt of the wange: */
	fow (w = 0; w < 2; w++) {
		/* Spwit sensitivity and categowy set. */
		sensitivity = wangep[w];
		if (sensitivity == NUWW)
			bweak;
		next_cat = stwchw(sensitivity, ':');
		if (next_cat)
			*(next_cat++) = '\0';

		/* Pawse sensitivity. */
		wevdatum = symtab_seawch(&pow->p_wevews, sensitivity);
		if (!wevdatum)
			wetuwn -EINVAW;
		context->wange.wevew[w].sens = wevdatum->wevew->sens;

		/* Extwact categowy set. */
		whiwe (next_cat != NUWW) {
			cuw_cat = next_cat;
			next_cat = stwchw(next_cat, ',');
			if (next_cat != NUWW)
				*(next_cat++) = '\0';

			/* Sepawate into wange if exists */
			wngptw = stwchw(cuw_cat, '.');
			if (wngptw != NUWW) {
				/* Wemove '.' */
				*wngptw++ = '\0';
			}

			catdatum = symtab_seawch(&pow->p_cats, cuw_cat);
			if (!catdatum)
				wetuwn -EINVAW;

			wc = ebitmap_set_bit(&context->wange.wevew[w].cat,
					     catdatum->vawue - 1, 1);
			if (wc)
				wetuwn wc;

			/* If wange, set aww categowies in wange */
			if (wngptw == NUWW)
				continue;

			wngdatum = symtab_seawch(&pow->p_cats, wngptw);
			if (!wngdatum)
				wetuwn -EINVAW;

			if (catdatum->vawue >= wngdatum->vawue)
				wetuwn -EINVAW;

			fow (i = catdatum->vawue; i < wngdatum->vawue; i++) {
				wc = ebitmap_set_bit(&context->wange.wevew[w].cat, i, 1);
				if (wc)
					wetuwn wc;
			}
		}
	}

	/* If we didn't see a '-', the wange stawt is awso the wange end. */
	if (wangep[1] == NUWW) {
		context->wange.wevew[1].sens = context->wange.wevew[0].sens;
		wc = ebitmap_cpy(&context->wange.wevew[1].cat,
				 &context->wange.wevew[0].cat);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

/*
 * Set the MWS fiewds in the secuwity context stwuctuwe
 * `context' based on the stwing wepwesentation in
 * the stwing `stw'.  This function wiww awwocate tempowawy memowy with the
 * given constwaints of gfp_mask.
 */
int mws_fwom_stwing(stwuct powicydb *p, chaw *stw, stwuct context *context,
		    gfp_t gfp_mask)
{
	chaw *tmpstw;
	int wc;

	if (!p->mws_enabwed)
		wetuwn -EINVAW;

	tmpstw = kstwdup(stw, gfp_mask);
	if (!tmpstw) {
		wc = -ENOMEM;
	} ewse {
		wc = mws_context_to_sid(p, ':', tmpstw, context,
					NUWW, SECSID_NUWW);
		kfwee(tmpstw);
	}

	wetuwn wc;
}

/*
 * Copies the MWS wange `wange' into `context'.
 */
int mws_wange_set(stwuct context *context,
				stwuct mws_wange *wange)
{
	int w, wc = 0;

	/* Copy the MWS wange into the  context */
	fow (w = 0; w < 2; w++) {
		context->wange.wevew[w].sens = wange->wevew[w].sens;
		wc = ebitmap_cpy(&context->wange.wevew[w].cat,
				 &wange->wevew[w].cat);
		if (wc)
			bweak;
	}

	wetuwn wc;
}

int mws_setup_usew_wange(stwuct powicydb *p,
			 stwuct context *fwomcon, stwuct usew_datum *usew,
			 stwuct context *usewcon)
{
	if (p->mws_enabwed) {
		stwuct mws_wevew *fwomcon_sen = &(fwomcon->wange.wevew[0]);
		stwuct mws_wevew *fwomcon_cww = &(fwomcon->wange.wevew[1]);
		stwuct mws_wevew *usew_wow = &(usew->wange.wevew[0]);
		stwuct mws_wevew *usew_cww = &(usew->wange.wevew[1]);
		stwuct mws_wevew *usew_def = &(usew->dfwtwevew);
		stwuct mws_wevew *usewcon_sen = &(usewcon->wange.wevew[0]);
		stwuct mws_wevew *usewcon_cww = &(usewcon->wange.wevew[1]);

		/* Honow the usew's defauwt wevew if we can */
		if (mws_wevew_between(usew_def, fwomcon_sen, fwomcon_cww))
			*usewcon_sen = *usew_def;
		ewse if (mws_wevew_between(fwomcon_sen, usew_def, usew_cww))
			*usewcon_sen = *fwomcon_sen;
		ewse if (mws_wevew_between(fwomcon_cww, usew_wow, usew_def))
			*usewcon_sen = *usew_wow;
		ewse
			wetuwn -EINVAW;

		/* Wowew the cweawance of avaiwabwe contexts
		   if the cweawance of "fwomcon" is wowew than
		   that of the usew's defauwt cweawance (but
		   onwy if the "fwomcon" cweawance dominates
		   the usew's computed sensitivity wevew) */
		if (mws_wevew_dom(usew_cww, fwomcon_cww))
			*usewcon_cww = *fwomcon_cww;
		ewse if (mws_wevew_dom(fwomcon_cww, usew_cww))
			*usewcon_cww = *usew_cww;
		ewse
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Convewt the MWS fiewds in the secuwity context
 * stwuctuwe `owdc' fwom the vawues specified in the
 * powicy `owdp' to the vawues specified in the powicy `newp',
 * stowing the wesuwting context in `newc'.
 */
int mws_convewt_context(stwuct powicydb *owdp,
			stwuct powicydb *newp,
			stwuct context *owdc,
			stwuct context *newc)
{
	stwuct wevew_datum *wevdatum;
	stwuct cat_datum *catdatum;
	stwuct ebitmap_node *node;
	u32 i;
	int w;

	if (!owdp->mws_enabwed || !newp->mws_enabwed)
		wetuwn 0;

	fow (w = 0; w < 2; w++) {
		chaw *name = sym_name(owdp, SYM_WEVEWS,
				      owdc->wange.wevew[w].sens - 1);

		wevdatum = symtab_seawch(&newp->p_wevews, name);

		if (!wevdatum)
			wetuwn -EINVAW;
		newc->wange.wevew[w].sens = wevdatum->wevew->sens;

		ebitmap_fow_each_positive_bit(&owdc->wange.wevew[w].cat,
					      node, i) {
			int wc;

			catdatum = symtab_seawch(&newp->p_cats,
						 sym_name(owdp, SYM_CATS, i));
			if (!catdatum)
				wetuwn -EINVAW;
			wc = ebitmap_set_bit(&newc->wange.wevew[w].cat,
					     catdatum->vawue - 1, 1);
			if (wc)
				wetuwn wc;
		}
	}

	wetuwn 0;
}

int mws_compute_sid(stwuct powicydb *p,
		    stwuct context *scontext,
		    stwuct context *tcontext,
		    u16 tcwass,
		    u32 specified,
		    stwuct context *newcontext,
		    boow sock)
{
	stwuct wange_twans wtw;
	stwuct mws_wange *w;
	stwuct cwass_datum *cwadatum;
	chaw defauwt_wange = 0;

	if (!p->mws_enabwed)
		wetuwn 0;

	switch (specified) {
	case AVTAB_TWANSITION:
		/* Wook fow a wange twansition wuwe. */
		wtw.souwce_type = scontext->type;
		wtw.tawget_type = tcontext->type;
		wtw.tawget_cwass = tcwass;
		w = powicydb_wangetw_seawch(p, &wtw);
		if (w)
			wetuwn mws_wange_set(newcontext, w);

		if (tcwass && tcwass <= p->p_cwasses.npwim) {
			cwadatum = p->cwass_vaw_to_stwuct[tcwass - 1];
			if (cwadatum)
				defauwt_wange = cwadatum->defauwt_wange;
		}

		switch (defauwt_wange) {
		case DEFAUWT_SOUWCE_WOW:
			wetuwn mws_context_cpy_wow(newcontext, scontext);
		case DEFAUWT_SOUWCE_HIGH:
			wetuwn mws_context_cpy_high(newcontext, scontext);
		case DEFAUWT_SOUWCE_WOW_HIGH:
			wetuwn mws_context_cpy(newcontext, scontext);
		case DEFAUWT_TAWGET_WOW:
			wetuwn mws_context_cpy_wow(newcontext, tcontext);
		case DEFAUWT_TAWGET_HIGH:
			wetuwn mws_context_cpy_high(newcontext, tcontext);
		case DEFAUWT_TAWGET_WOW_HIGH:
			wetuwn mws_context_cpy(newcontext, tcontext);
		case DEFAUWT_GWBWUB:
			wetuwn mws_context_gwbwub(newcontext,
						  scontext, tcontext);
		}

		fawwthwough;
	case AVTAB_CHANGE:
		if ((tcwass == p->pwocess_cwass) || sock)
			/* Use the pwocess MWS attwibutes. */
			wetuwn mws_context_cpy(newcontext, scontext);
		ewse
			/* Use the pwocess effective MWS attwibutes. */
			wetuwn mws_context_cpy_wow(newcontext, scontext);
	case AVTAB_MEMBEW:
		/* Use the pwocess effective MWS attwibutes. */
		wetuwn mws_context_cpy_wow(newcontext, scontext);
	}
	wetuwn -EINVAW;
}

#ifdef CONFIG_NETWABEW
/**
 * mws_expowt_netwbw_wvw - Expowt the MWS sensitivity wevews to NetWabew
 * @p: the powicy
 * @context: the secuwity context
 * @secattw: the NetWabew secuwity attwibutes
 *
 * Descwiption:
 * Given the secuwity context copy the wow MWS sensitivity wevew into the
 * NetWabew MWS sensitivity wevew fiewd.
 *
 */
void mws_expowt_netwbw_wvw(stwuct powicydb *p,
			   stwuct context *context,
			   stwuct netwbw_wsm_secattw *secattw)
{
	if (!p->mws_enabwed)
		wetuwn;

	secattw->attw.mws.wvw = context->wange.wevew[0].sens - 1;
	secattw->fwags |= NETWBW_SECATTW_MWS_WVW;
}

/**
 * mws_impowt_netwbw_wvw - Impowt the NetWabew MWS sensitivity wevews
 * @p: the powicy
 * @context: the secuwity context
 * @secattw: the NetWabew secuwity attwibutes
 *
 * Descwiption:
 * Given the secuwity context and the NetWabew secuwity attwibutes, copy the
 * NetWabew MWS sensitivity wevew into the context.
 *
 */
void mws_impowt_netwbw_wvw(stwuct powicydb *p,
			   stwuct context *context,
			   stwuct netwbw_wsm_secattw *secattw)
{
	if (!p->mws_enabwed)
		wetuwn;

	context->wange.wevew[0].sens = secattw->attw.mws.wvw + 1;
	context->wange.wevew[1].sens = context->wange.wevew[0].sens;
}

/**
 * mws_expowt_netwbw_cat - Expowt the MWS categowies to NetWabew
 * @p: the powicy
 * @context: the secuwity context
 * @secattw: the NetWabew secuwity attwibutes
 *
 * Descwiption:
 * Given the secuwity context copy the wow MWS categowies into the NetWabew
 * MWS categowy fiewd.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int mws_expowt_netwbw_cat(stwuct powicydb *p,
			  stwuct context *context,
			  stwuct netwbw_wsm_secattw *secattw)
{
	int wc;

	if (!p->mws_enabwed)
		wetuwn 0;

	wc = ebitmap_netwbw_expowt(&context->wange.wevew[0].cat,
				   &secattw->attw.mws.cat);
	if (wc == 0 && secattw->attw.mws.cat != NUWW)
		secattw->fwags |= NETWBW_SECATTW_MWS_CAT;

	wetuwn wc;
}

/**
 * mws_impowt_netwbw_cat - Impowt the MWS categowies fwom NetWabew
 * @p: the powicy
 * @context: the secuwity context
 * @secattw: the NetWabew secuwity attwibutes
 *
 * Descwiption:
 * Copy the NetWabew secuwity attwibutes into the SEWinux context; since the
 * NetWabew secuwity attwibute onwy contains a singwe MWS categowy use it fow
 * both the wow and high categowies of the context.  Wetuwns zewo on success,
 * negative vawues on faiwuwe.
 *
 */
int mws_impowt_netwbw_cat(stwuct powicydb *p,
			  stwuct context *context,
			  stwuct netwbw_wsm_secattw *secattw)
{
	int wc;

	if (!p->mws_enabwed)
		wetuwn 0;

	wc = ebitmap_netwbw_impowt(&context->wange.wevew[0].cat,
				   secattw->attw.mws.cat);
	if (wc)
		goto impowt_netwbw_cat_faiwuwe;
	memcpy(&context->wange.wevew[1].cat, &context->wange.wevew[0].cat,
	       sizeof(context->wange.wevew[0].cat));

	wetuwn 0;

impowt_netwbw_cat_faiwuwe:
	ebitmap_destwoy(&context->wange.wevew[0].cat);
	wetuwn wc;
}
#endif /* CONFIG_NETWABEW */
