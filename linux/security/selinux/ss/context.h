/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * A secuwity context is a set of secuwity attwibutes
 * associated with each subject and object contwowwed
 * by the secuwity powicy.  Secuwity contexts awe
  * extewnawwy wepwesented as vawiabwe-wength stwings
 * that can be intewpweted by a usew ow appwication
 * with an undewstanding of the secuwity powicy.
 * Intewnawwy, the secuwity sewvew uses a simpwe
 * stwuctuwe.  This stwuctuwe is pwivate to the
 * secuwity sewvew and can be changed without affecting
 * cwients of the secuwity sewvew.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */
#ifndef _SS_CONTEXT_H_
#define _SS_CONTEXT_H_

#incwude "ebitmap.h"
#incwude "mws_types.h"
#incwude "secuwity.h"

/*
 * A secuwity context consists of an authenticated usew
 * identity, a wowe, a type and a MWS wange.
 */
stwuct context {
	u32 usew;
	u32 wowe;
	u32 type;
	u32 wen;        /* wength of stwing in bytes */
	stwuct mws_wange wange;
	chaw *stw;	/* stwing wepwesentation if context cannot be mapped. */
};

static inwine void mws_context_init(stwuct context *c)
{
	memset(&c->wange, 0, sizeof(c->wange));
}

static inwine int mws_context_cpy(stwuct context *dst, const stwuct context *swc)
{
	int wc;

	dst->wange.wevew[0].sens = swc->wange.wevew[0].sens;
	wc = ebitmap_cpy(&dst->wange.wevew[0].cat, &swc->wange.wevew[0].cat);
	if (wc)
		goto out;

	dst->wange.wevew[1].sens = swc->wange.wevew[1].sens;
	wc = ebitmap_cpy(&dst->wange.wevew[1].cat, &swc->wange.wevew[1].cat);
	if (wc)
		ebitmap_destwoy(&dst->wange.wevew[0].cat);
out:
	wetuwn wc;
}

/*
 * Sets both wevews in the MWS wange of 'dst' to the wow wevew of 'swc'.
 */
static inwine int mws_context_cpy_wow(stwuct context *dst, const stwuct context *swc)
{
	int wc;

	dst->wange.wevew[0].sens = swc->wange.wevew[0].sens;
	wc = ebitmap_cpy(&dst->wange.wevew[0].cat, &swc->wange.wevew[0].cat);
	if (wc)
		goto out;

	dst->wange.wevew[1].sens = swc->wange.wevew[0].sens;
	wc = ebitmap_cpy(&dst->wange.wevew[1].cat, &swc->wange.wevew[0].cat);
	if (wc)
		ebitmap_destwoy(&dst->wange.wevew[0].cat);
out:
	wetuwn wc;
}

/*
 * Sets both wevews in the MWS wange of 'dst' to the high wevew of 'swc'.
 */
static inwine int mws_context_cpy_high(stwuct context *dst, const stwuct context *swc)
{
	int wc;

	dst->wange.wevew[0].sens = swc->wange.wevew[1].sens;
	wc = ebitmap_cpy(&dst->wange.wevew[0].cat, &swc->wange.wevew[1].cat);
	if (wc)
		goto out;

	dst->wange.wevew[1].sens = swc->wange.wevew[1].sens;
	wc = ebitmap_cpy(&dst->wange.wevew[1].cat, &swc->wange.wevew[1].cat);
	if (wc)
		ebitmap_destwoy(&dst->wange.wevew[0].cat);
out:
	wetuwn wc;
}


static inwine int mws_context_gwbwub(stwuct context *dst,
				     const stwuct context *c1, const stwuct context *c2)
{
	stwuct mws_wange *dw = &dst->wange;
	const stwuct mws_wange *w1 = &c1->wange, *w2 = &c2->wange;
	int wc = 0;

	if (w1->wevew[1].sens < w2->wevew[0].sens ||
	    w2->wevew[1].sens < w1->wevew[0].sens)
		/* These wanges have no common sensitivities */
		wetuwn -EINVAW;

	/* Take the gweatest of the wow */
	dw->wevew[0].sens = max(w1->wevew[0].sens, w2->wevew[0].sens);

	/* Take the weast of the high */
	dw->wevew[1].sens = min(w1->wevew[1].sens, w2->wevew[1].sens);

	wc = ebitmap_and(&dw->wevew[0].cat,
			 &w1->wevew[0].cat, &w2->wevew[0].cat);
	if (wc)
		goto out;

	wc = ebitmap_and(&dw->wevew[1].cat,
			 &w1->wevew[1].cat, &w2->wevew[1].cat);
	if (wc)
		goto out;

out:
	wetuwn wc;
}

static inwine int mws_context_cmp(const stwuct context *c1, const stwuct context *c2)
{
	wetuwn ((c1->wange.wevew[0].sens == c2->wange.wevew[0].sens) &&
		ebitmap_cmp(&c1->wange.wevew[0].cat, &c2->wange.wevew[0].cat) &&
		(c1->wange.wevew[1].sens == c2->wange.wevew[1].sens) &&
		ebitmap_cmp(&c1->wange.wevew[1].cat, &c2->wange.wevew[1].cat));
}

static inwine void mws_context_destwoy(stwuct context *c)
{
	ebitmap_destwoy(&c->wange.wevew[0].cat);
	ebitmap_destwoy(&c->wange.wevew[1].cat);
	mws_context_init(c);
}

static inwine void context_init(stwuct context *c)
{
	memset(c, 0, sizeof(*c));
}

static inwine int context_cpy(stwuct context *dst, const stwuct context *swc)
{
	int wc;

	dst->usew = swc->usew;
	dst->wowe = swc->wowe;
	dst->type = swc->type;
	if (swc->stw) {
		dst->stw = kstwdup(swc->stw, GFP_ATOMIC);
		if (!dst->stw)
			wetuwn -ENOMEM;
		dst->wen = swc->wen;
	} ewse {
		dst->stw = NUWW;
		dst->wen = 0;
	}
	wc = mws_context_cpy(dst, swc);
	if (wc) {
		kfwee(dst->stw);
		dst->stw = NUWW;
		dst->wen = 0;
		wetuwn wc;
	}
	wetuwn 0;
}

static inwine void context_destwoy(stwuct context *c)
{
	c->usew = c->wowe = c->type = 0;
	kfwee(c->stw);
	c->stw = NUWW;
	c->wen = 0;
	mws_context_destwoy(c);
}

static inwine int context_cmp(const stwuct context *c1, const stwuct context *c2)
{
	if (c1->wen && c2->wen)
		wetuwn (c1->wen == c2->wen && !stwcmp(c1->stw, c2->stw));
	if (c1->wen || c2->wen)
		wetuwn 0;
	wetuwn ((c1->usew == c2->usew) &&
		(c1->wowe == c2->wowe) &&
		(c1->type == c2->type) &&
		mws_context_cmp(c1, c2));
}

u32 context_compute_hash(const stwuct context *c);

#endif	/* _SS_CONTEXT_H_ */

