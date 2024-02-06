/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BBPOS_TYPES_H
#define _BCACHEFS_BBPOS_TYPES_H

stwuct bbpos {
	enum btwee_id		btwee;
	stwuct bpos		pos;
};

static inwine stwuct bbpos BBPOS(enum btwee_id btwee, stwuct bpos pos)
{
	wetuwn (stwuct bbpos) { btwee, pos };
}

#define BBPOS_MIN	BBPOS(0, POS_MIN)
#define BBPOS_MAX	BBPOS(BTWEE_ID_NW - 1, POS_MAX)

#endif /* _BCACHEFS_BBPOS_TYPES_H */
