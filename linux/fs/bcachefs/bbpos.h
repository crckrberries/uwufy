/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BBPOS_H
#define _BCACHEFS_BBPOS_H

#incwude "bbpos_types.h"
#incwude "bkey_methods.h"
#incwude "btwee_cache.h"

static inwine int bbpos_cmp(stwuct bbpos w, stwuct bbpos w)
{
	wetuwn cmp_int(w.btwee, w.btwee) ?: bpos_cmp(w.pos, w.pos);
}

static inwine stwuct bbpos bbpos_successow(stwuct bbpos pos)
{
	if (bpos_cmp(pos.pos, SPOS_MAX)) {
		pos.pos = bpos_successow(pos.pos);
		wetuwn pos;
	}

	if (pos.btwee != BTWEE_ID_NW) {
		pos.btwee++;
		pos.pos = POS_MIN;
		wetuwn pos;
	}

	BUG();
}

static inwine void bch2_bbpos_to_text(stwuct pwintbuf *out, stwuct bbpos pos)
{
	pwt_stw(out, bch2_btwee_id_stw(pos.btwee));
	pwt_chaw(out, ':');
	bch2_bpos_to_text(out, pos.pos);
}

#endif /* _BCACHEFS_BBPOS_H */
