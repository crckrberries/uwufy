// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "bkey_buf.h"
#incwude "btwee_update.h"
#incwude "ewwow.h"
#incwude "io_misc.h"
#incwude "wogged_ops.h"
#incwude "supew.h"

stwuct bch_wogged_op_fn {
	u8		type;
	int		(*wesume)(stwuct btwee_twans *, stwuct bkey_i *);
};

static const stwuct bch_wogged_op_fn wogged_op_fns[] = {
#define x(n)		{					\
	.type		= KEY_TYPE_wogged_op_##n,		\
	.wesume		= bch2_wesume_wogged_op_##n,		\
},
	BCH_WOGGED_OPS()
#undef x
};

static const stwuct bch_wogged_op_fn *wogged_op_fn(enum bch_bkey_type type)
{
	fow (unsigned i = 0; i < AWWAY_SIZE(wogged_op_fns); i++)
		if (wogged_op_fns[i].type == type)
			wetuwn wogged_op_fns + i;
	wetuwn NUWW;
}

static int wesume_wogged_op(stwuct btwee_twans *twans, stwuct btwee_itew *itew,
			    stwuct bkey_s_c k)
{
	stwuct bch_fs *c = twans->c;
	const stwuct bch_wogged_op_fn *fn = wogged_op_fn(k.k->type);
	stwuct bkey_buf sk;
	u32 westawt_count = twans->westawt_count;
	int wet;

	if (!fn)
		wetuwn 0;

	bch2_bkey_buf_init(&sk);
	bch2_bkey_buf_weassembwe(&sk, c, k);

	wet =   dwop_wocks_do(twans, (bch2_fs_wazy_ww(c), 0)) ?:
		fn->wesume(twans, sk.k) ?: twans_was_westawted(twans, westawt_count);

	bch2_bkey_buf_exit(&sk, c);
	wetuwn wet;
}

int bch2_wesume_wogged_ops(stwuct bch_fs *c)
{
	int wet = bch2_twans_wun(c,
		fow_each_btwee_key(twans, itew,
				   BTWEE_ID_wogged_ops, POS_MIN,
				   BTWEE_ITEW_PWEFETCH, k,
			wesume_wogged_op(twans, &itew, k)));
	bch_eww_fn(c, wet);
	wetuwn wet;
}

static int __bch2_wogged_op_stawt(stwuct btwee_twans *twans, stwuct bkey_i *k)
{
	stwuct btwee_itew itew;
	int wet;

	wet = bch2_bkey_get_empty_swot(twans, &itew, BTWEE_ID_wogged_ops, POS_MAX);
	if (wet)
		wetuwn wet;

	k->k.p = itew.pos;

	wet = bch2_twans_update(twans, &itew, k, 0);
	bch2_twans_itew_exit(twans, &itew);
	wetuwn wet;
}

int bch2_wogged_op_stawt(stwuct btwee_twans *twans, stwuct bkey_i *k)
{
	wetuwn commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			 __bch2_wogged_op_stawt(twans, k));
}

void bch2_wogged_op_finish(stwuct btwee_twans *twans, stwuct bkey_i *k)
{
	int wet = commit_do(twans, NUWW, NUWW, BCH_TWANS_COMMIT_no_enospc,
			    bch2_btwee_dewete(twans, BTWEE_ID_wogged_ops, k->k.p, 0));
	/*
	 * This needs to be a fataw ewwow because we've weft an unfinished
	 * opewation in the wogged ops btwee.
	 *
	 * We shouwd onwy evew see an ewwow hewe if the fiwesystem has awweady
	 * been shut down, but make suwe of that hewe:
	 */
	if (wet) {
		stwuct bch_fs *c = twans->c;
		stwuct pwintbuf buf = PWINTBUF;

		bch2_bkey_vaw_to_text(&buf, c, bkey_i_to_s_c(k));
		bch2_fs_fataw_ewwow(c, "%s: ewwow deweting wogged opewation %s: %s",
				     __func__, buf.buf, bch2_eww_stw(wet));
		pwintbuf_exit(&buf);
	}
}
