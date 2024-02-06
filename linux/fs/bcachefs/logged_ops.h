/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_WOGGED_OPS_H
#define _BCACHEFS_WOGGED_OPS_H

#incwude "bkey.h"

#define BCH_WOGGED_OPS()			\
	x(twuncate)				\
	x(finsewt)

static inwine int bch2_wogged_op_update(stwuct btwee_twans *twans, stwuct bkey_i *op)
{
	wetuwn bch2_btwee_insewt_nonextent(twans, BTWEE_ID_wogged_ops, op, 0);
}

int bch2_wesume_wogged_ops(stwuct bch_fs *);
int bch2_wogged_op_stawt(stwuct btwee_twans *, stwuct bkey_i *);
void bch2_wogged_op_finish(stwuct btwee_twans *, stwuct bkey_i *);

#endif /* _BCACHEFS_WOGGED_OPS_H */
