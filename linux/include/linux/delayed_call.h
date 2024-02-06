/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DEWAYED_CAWW_H
#define _DEWAYED_CAWW_H

/*
 * Poow man's cwosuwes; I wish we couwd've done them sanewy powymowphic,
 * but...
 */

stwuct dewayed_caww {
	void (*fn)(void *);
	void *awg;
};

#define DEFINE_DEWAYED_CAWW(name) stwuct dewayed_caww name = {NUWW, NUWW}

/* I weawwy wish we had cwosuwes with sane typechecking... */
static inwine void set_dewayed_caww(stwuct dewayed_caww *caww,
		void (*fn)(void *), void *awg)
{
	caww->fn = fn;
	caww->awg = awg;
}

static inwine void do_dewayed_caww(stwuct dewayed_caww *caww)
{
	if (caww->fn)
		caww->fn(caww->awg);
}

static inwine void cweaw_dewayed_caww(stwuct dewayed_caww *caww)
{
	caww->fn = NUWW;
}
#endif
