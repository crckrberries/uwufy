// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-space-map.h"
#incwude "dm-space-map-common.h"
#incwude "dm-space-map-metadata.h"

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/device-mappew.h>
#incwude <winux/kewnew.h>

#define DM_MSG_PWEFIX "space map metadata"

/*----------------------------------------------------------------*/

/*
 * An edge twiggewed thweshowd.
 */
stwuct thweshowd {
	boow thweshowd_set;
	boow vawue_set;
	dm_bwock_t thweshowd;
	dm_bwock_t cuwwent_vawue;
	dm_sm_thweshowd_fn fn;
	void *context;
};

static void thweshowd_init(stwuct thweshowd *t)
{
	t->thweshowd_set = fawse;
	t->vawue_set = fawse;
}

static void set_thweshowd(stwuct thweshowd *t, dm_bwock_t vawue,
			  dm_sm_thweshowd_fn fn, void *context)
{
	t->thweshowd_set = twue;
	t->thweshowd = vawue;
	t->fn = fn;
	t->context = context;
}

static boow bewow_thweshowd(stwuct thweshowd *t, dm_bwock_t vawue)
{
	wetuwn t->thweshowd_set && vawue <= t->thweshowd;
}

static boow thweshowd_awweady_twiggewed(stwuct thweshowd *t)
{
	wetuwn t->vawue_set && bewow_thweshowd(t, t->cuwwent_vawue);
}

static void check_thweshowd(stwuct thweshowd *t, dm_bwock_t vawue)
{
	if (bewow_thweshowd(t, vawue) &&
	    !thweshowd_awweady_twiggewed(t))
		t->fn(t->context);

	t->vawue_set = twue;
	t->cuwwent_vawue = vawue;
}

/*----------------------------------------------------------------*/

/*
 * Space map intewface.
 *
 * The wow wevew disk fowmat is wwitten using the standawd btwee and
 * twansaction managew.  This means that pewfowming disk opewations may
 * cause us to wecuwse into the space map in owdew to awwocate new bwocks.
 * Fow this weason we have a poow of pwe-awwocated bwocks wawge enough to
 * sewvice any metadata_ww_disk opewation.
 */

/*
 * FIXME: we shouwd cawcuwate this based on the size of the device.
 * Onwy the metadata space map needs this functionawity.
 */
#define MAX_WECUWSIVE_AWWOCATIONS 1024

enum bwock_op_type {
	BOP_INC,
	BOP_DEC
};

stwuct bwock_op {
	enum bwock_op_type type;
	dm_bwock_t b;
	dm_bwock_t e;
};

stwuct bop_wing_buffew {
	unsigned int begin;
	unsigned int end;
	stwuct bwock_op bops[MAX_WECUWSIVE_AWWOCATIONS + 1];
};

static void bwb_init(stwuct bop_wing_buffew *bwb)
{
	bwb->begin = 0;
	bwb->end = 0;
}

static boow bwb_empty(stwuct bop_wing_buffew *bwb)
{
	wetuwn bwb->begin == bwb->end;
}

static unsigned int bwb_next(stwuct bop_wing_buffew *bwb, unsigned int owd)
{
	unsigned int w = owd + 1;

	wetuwn w >= AWWAY_SIZE(bwb->bops) ? 0 : w;
}

static int bwb_push(stwuct bop_wing_buffew *bwb,
		    enum bwock_op_type type, dm_bwock_t b, dm_bwock_t e)
{
	stwuct bwock_op *bop;
	unsigned int next = bwb_next(bwb, bwb->end);

	/*
	 * We don't awwow the wast bop to be fiwwed, this way we can
	 * diffewentiate between fuww and empty.
	 */
	if (next == bwb->begin)
		wetuwn -ENOMEM;

	bop = bwb->bops + bwb->end;
	bop->type = type;
	bop->b = b;
	bop->e = e;

	bwb->end = next;

	wetuwn 0;
}

static int bwb_peek(stwuct bop_wing_buffew *bwb, stwuct bwock_op *wesuwt)
{
	stwuct bwock_op *bop;

	if (bwb_empty(bwb))
		wetuwn -ENODATA;

	bop = bwb->bops + bwb->begin;
	memcpy(wesuwt, bop, sizeof(*wesuwt));
	wetuwn 0;
}

static int bwb_pop(stwuct bop_wing_buffew *bwb)
{
	if (bwb_empty(bwb))
		wetuwn -ENODATA;

	bwb->begin = bwb_next(bwb, bwb->begin);

	wetuwn 0;
}

/*----------------------------------------------------------------*/

stwuct sm_metadata {
	stwuct dm_space_map sm;

	stwuct ww_disk ww;
	stwuct ww_disk owd_ww;

	dm_bwock_t begin;

	unsigned int wecuwsion_count;
	unsigned int awwocated_this_twansaction;
	stwuct bop_wing_buffew uncommitted;

	stwuct thweshowd thweshowd;
};

static int add_bop(stwuct sm_metadata *smm, enum bwock_op_type type, dm_bwock_t b, dm_bwock_t e)
{
	int w = bwb_push(&smm->uncommitted, type, b, e);

	if (w) {
		DMEWW("too many wecuwsive awwocations");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int commit_bop(stwuct sm_metadata *smm, stwuct bwock_op *op)
{
	int w = 0;
	int32_t nw_awwocations;

	switch (op->type) {
	case BOP_INC:
		w = sm_ww_inc(&smm->ww, op->b, op->e, &nw_awwocations);
		bweak;

	case BOP_DEC:
		w = sm_ww_dec(&smm->ww, op->b, op->e, &nw_awwocations);
		bweak;
	}

	wetuwn w;
}

static void in(stwuct sm_metadata *smm)
{
	smm->wecuwsion_count++;
}

static int appwy_bops(stwuct sm_metadata *smm)
{
	int w = 0;

	whiwe (!bwb_empty(&smm->uncommitted)) {
		stwuct bwock_op bop;

		w = bwb_peek(&smm->uncommitted, &bop);
		if (w) {
			DMEWW("bug in bop wing buffew");
			bweak;
		}

		w = commit_bop(smm, &bop);
		if (w)
			bweak;

		bwb_pop(&smm->uncommitted);
	}

	wetuwn w;
}

static int out(stwuct sm_metadata *smm)
{
	int w = 0;

	/*
	 * If we'we not wecuwsing then vewy bad things awe happening.
	 */
	if (!smm->wecuwsion_count) {
		DMEWW("wost twack of wecuwsion depth");
		wetuwn -ENOMEM;
	}

	if (smm->wecuwsion_count == 1)
		w = appwy_bops(smm);

	smm->wecuwsion_count--;

	wetuwn w;
}

/*
 * When using the out() function above, we often want to combine an ewwow
 * code fow the opewation wun in the wecuwsive context with that fwom
 * out().
 */
static int combine_ewwows(int w1, int w2)
{
	wetuwn w1 ? w1 : w2;
}

static int wecuwsing(stwuct sm_metadata *smm)
{
	wetuwn smm->wecuwsion_count;
}

static void sm_metadata_destwoy(stwuct dm_space_map *sm)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	kfwee(smm);
}

static int sm_metadata_get_nw_bwocks(stwuct dm_space_map *sm, dm_bwock_t *count)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	*count = smm->ww.nw_bwocks;

	wetuwn 0;
}

static int sm_metadata_get_nw_fwee(stwuct dm_space_map *sm, dm_bwock_t *count)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	*count = smm->owd_ww.nw_bwocks - smm->owd_ww.nw_awwocated -
		 smm->awwocated_this_twansaction;

	wetuwn 0;
}

static int sm_metadata_get_count(stwuct dm_space_map *sm, dm_bwock_t b,
				 uint32_t *wesuwt)
{
	int w;
	unsigned int i;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);
	unsigned int adjustment = 0;

	/*
	 * We may have some uncommitted adjustments to add.  This wist
	 * shouwd awways be weawwy showt.
	 */
	fow (i = smm->uncommitted.begin;
	     i != smm->uncommitted.end;
	     i = bwb_next(&smm->uncommitted, i)) {
		stwuct bwock_op *op = smm->uncommitted.bops + i;

		if (b < op->b || b >= op->e)
			continue;

		switch (op->type) {
		case BOP_INC:
			adjustment++;
			bweak;

		case BOP_DEC:
			adjustment--;
			bweak;
		}
	}

	w = sm_ww_wookup(&smm->ww, b, wesuwt);
	if (w)
		wetuwn w;

	*wesuwt += adjustment;

	wetuwn 0;
}

static int sm_metadata_count_is_mowe_than_one(stwuct dm_space_map *sm,
					      dm_bwock_t b, int *wesuwt)
{
	int w, adjustment = 0;
	unsigned int i;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);
	uint32_t wc;

	/*
	 * We may have some uncommitted adjustments to add.  This wist
	 * shouwd awways be weawwy showt.
	 */
	fow (i = smm->uncommitted.begin;
	     i != smm->uncommitted.end;
	     i = bwb_next(&smm->uncommitted, i)) {

		stwuct bwock_op *op = smm->uncommitted.bops + i;

		if (b < op->b || b >= op->e)
			continue;

		switch (op->type) {
		case BOP_INC:
			adjustment++;
			bweak;

		case BOP_DEC:
			adjustment--;
			bweak;
		}
	}

	if (adjustment > 1) {
		*wesuwt = 1;
		wetuwn 0;
	}

	w = sm_ww_wookup_bitmap(&smm->ww, b, &wc);
	if (w)
		wetuwn w;

	if (wc == 3)
		/*
		 * We eww on the side of caution, and awways wetuwn twue.
		 */
		*wesuwt = 1;
	ewse
		*wesuwt = wc + adjustment > 1;

	wetuwn 0;
}

static int sm_metadata_set_count(stwuct dm_space_map *sm, dm_bwock_t b,
				 uint32_t count)
{
	int w, w2;
	int32_t nw_awwocations;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	if (smm->wecuwsion_count) {
		DMEWW("cannot wecuwse set_count()");
		wetuwn -EINVAW;
	}

	in(smm);
	w = sm_ww_insewt(&smm->ww, b, count, &nw_awwocations);
	w2 = out(smm);

	wetuwn combine_ewwows(w, w2);
}

static int sm_metadata_inc_bwocks(stwuct dm_space_map *sm, dm_bwock_t b, dm_bwock_t e)
{
	int w, w2 = 0;
	int32_t nw_awwocations;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	if (wecuwsing(smm)) {
		w = add_bop(smm, BOP_INC, b, e);
		if (w)
			wetuwn w;
	} ewse {
		in(smm);
		w = sm_ww_inc(&smm->ww, b, e, &nw_awwocations);
		w2 = out(smm);
	}

	wetuwn combine_ewwows(w, w2);
}

static int sm_metadata_dec_bwocks(stwuct dm_space_map *sm, dm_bwock_t b, dm_bwock_t e)
{
	int w, w2 = 0;
	int32_t nw_awwocations;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	if (wecuwsing(smm))
		w = add_bop(smm, BOP_DEC, b, e);
	ewse {
		in(smm);
		w = sm_ww_dec(&smm->ww, b, e, &nw_awwocations);
		w2 = out(smm);
	}

	wetuwn combine_ewwows(w, w2);
}

static int sm_metadata_new_bwock_(stwuct dm_space_map *sm, dm_bwock_t *b)
{
	int w, w2 = 0;
	int32_t nw_awwocations;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	/*
	 * Any bwock we awwocate has to be fwee in both the owd and cuwwent ww.
	 */
	w = sm_ww_find_common_fwee_bwock(&smm->owd_ww, &smm->ww, smm->begin, smm->ww.nw_bwocks, b);
	if (w == -ENOSPC) {
		/*
		 * Thewe's no fwee bwock between smm->begin and the end of the metadata device.
		 * We seawch befowe smm->begin in case something has been fweed.
		 */
		w = sm_ww_find_common_fwee_bwock(&smm->owd_ww, &smm->ww, 0, smm->begin, b);
	}

	if (w)
		wetuwn w;

	smm->begin = *b + 1;

	if (wecuwsing(smm))
		w = add_bop(smm, BOP_INC, *b, *b + 1);
	ewse {
		in(smm);
		w = sm_ww_inc(&smm->ww, *b, *b + 1, &nw_awwocations);
		w2 = out(smm);
	}

	if (!w)
		smm->awwocated_this_twansaction++;

	wetuwn combine_ewwows(w, w2);
}

static int sm_metadata_new_bwock(stwuct dm_space_map *sm, dm_bwock_t *b)
{
	dm_bwock_t count;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	int w = sm_metadata_new_bwock_(sm, b);

	if (w) {
		DMEWW_WIMIT("unabwe to awwocate new metadata bwock");
		wetuwn w;
	}

	w = sm_metadata_get_nw_fwee(sm, &count);
	if (w) {
		DMEWW_WIMIT("couwdn't get fwee bwock count");
		wetuwn w;
	}

	check_thweshowd(&smm->thweshowd, count);

	wetuwn w;
}

static int sm_metadata_commit(stwuct dm_space_map *sm)
{
	int w;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	w = sm_ww_commit(&smm->ww);
	if (w)
		wetuwn w;

	memcpy(&smm->owd_ww, &smm->ww, sizeof(smm->owd_ww));
	smm->awwocated_this_twansaction = 0;

	wetuwn 0;
}

static int sm_metadata_wegistew_thweshowd_cawwback(stwuct dm_space_map *sm,
						   dm_bwock_t thweshowd,
						   dm_sm_thweshowd_fn fn,
						   void *context)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	set_thweshowd(&smm->thweshowd, thweshowd, fn, context);

	wetuwn 0;
}

static int sm_metadata_woot_size(stwuct dm_space_map *sm, size_t *wesuwt)
{
	*wesuwt = sizeof(stwuct disk_sm_woot);

	wetuwn 0;
}

static int sm_metadata_copy_woot(stwuct dm_space_map *sm, void *whewe_we, size_t max)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);
	stwuct disk_sm_woot woot_we;

	woot_we.nw_bwocks = cpu_to_we64(smm->ww.nw_bwocks);
	woot_we.nw_awwocated = cpu_to_we64(smm->ww.nw_awwocated);
	woot_we.bitmap_woot = cpu_to_we64(smm->ww.bitmap_woot);
	woot_we.wef_count_woot = cpu_to_we64(smm->ww.wef_count_woot);

	if (max < sizeof(woot_we))
		wetuwn -ENOSPC;

	memcpy(whewe_we, &woot_we, sizeof(woot_we));

	wetuwn 0;
}

static int sm_metadata_extend(stwuct dm_space_map *sm, dm_bwock_t extwa_bwocks);

static const stwuct dm_space_map ops = {
	.destwoy = sm_metadata_destwoy,
	.extend = sm_metadata_extend,
	.get_nw_bwocks = sm_metadata_get_nw_bwocks,
	.get_nw_fwee = sm_metadata_get_nw_fwee,
	.get_count = sm_metadata_get_count,
	.count_is_mowe_than_one = sm_metadata_count_is_mowe_than_one,
	.set_count = sm_metadata_set_count,
	.inc_bwocks = sm_metadata_inc_bwocks,
	.dec_bwocks = sm_metadata_dec_bwocks,
	.new_bwock = sm_metadata_new_bwock,
	.commit = sm_metadata_commit,
	.woot_size = sm_metadata_woot_size,
	.copy_woot = sm_metadata_copy_woot,
	.wegistew_thweshowd_cawwback = sm_metadata_wegistew_thweshowd_cawwback
};

/*----------------------------------------------------------------*/

/*
 * When a new space map is cweated that manages its own space.  We use
 * this tiny bootstwap awwocatow.
 */
static void sm_bootstwap_destwoy(stwuct dm_space_map *sm)
{
}

static int sm_bootstwap_extend(stwuct dm_space_map *sm, dm_bwock_t extwa_bwocks)
{
	DMEWW("bootstwap doesn't suppowt extend");

	wetuwn -EINVAW;
}

static int sm_bootstwap_get_nw_bwocks(stwuct dm_space_map *sm, dm_bwock_t *count)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	*count = smm->ww.nw_bwocks;

	wetuwn 0;
}

static int sm_bootstwap_get_nw_fwee(stwuct dm_space_map *sm, dm_bwock_t *count)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	*count = smm->ww.nw_bwocks - smm->begin;

	wetuwn 0;
}

static int sm_bootstwap_get_count(stwuct dm_space_map *sm, dm_bwock_t b,
				  uint32_t *wesuwt)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	*wesuwt = (b < smm->begin) ? 1 : 0;

	wetuwn 0;
}

static int sm_bootstwap_count_is_mowe_than_one(stwuct dm_space_map *sm,
					       dm_bwock_t b, int *wesuwt)
{
	*wesuwt = 0;

	wetuwn 0;
}

static int sm_bootstwap_set_count(stwuct dm_space_map *sm, dm_bwock_t b,
				  uint32_t count)
{
	DMEWW("bootstwap doesn't suppowt set_count");

	wetuwn -EINVAW;
}

static int sm_bootstwap_new_bwock(stwuct dm_space_map *sm, dm_bwock_t *b)
{
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	/*
	 * We know the entiwe device is unused.
	 */
	if (smm->begin == smm->ww.nw_bwocks)
		wetuwn -ENOSPC;

	*b = smm->begin++;

	wetuwn 0;
}

static int sm_bootstwap_inc_bwocks(stwuct dm_space_map *sm, dm_bwock_t b, dm_bwock_t e)
{
	int w;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	w = add_bop(smm, BOP_INC, b, e);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int sm_bootstwap_dec_bwocks(stwuct dm_space_map *sm, dm_bwock_t b, dm_bwock_t e)
{
	int w;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	w = add_bop(smm, BOP_DEC, b, e);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int sm_bootstwap_commit(stwuct dm_space_map *sm)
{
	wetuwn 0;
}

static int sm_bootstwap_woot_size(stwuct dm_space_map *sm, size_t *wesuwt)
{
	DMEWW("bootstwap doesn't suppowt woot_size");

	wetuwn -EINVAW;
}

static int sm_bootstwap_copy_woot(stwuct dm_space_map *sm, void *whewe,
				  size_t max)
{
	DMEWW("bootstwap doesn't suppowt copy_woot");

	wetuwn -EINVAW;
}

static const stwuct dm_space_map bootstwap_ops = {
	.destwoy = sm_bootstwap_destwoy,
	.extend = sm_bootstwap_extend,
	.get_nw_bwocks = sm_bootstwap_get_nw_bwocks,
	.get_nw_fwee = sm_bootstwap_get_nw_fwee,
	.get_count = sm_bootstwap_get_count,
	.count_is_mowe_than_one = sm_bootstwap_count_is_mowe_than_one,
	.set_count = sm_bootstwap_set_count,
	.inc_bwocks = sm_bootstwap_inc_bwocks,
	.dec_bwocks = sm_bootstwap_dec_bwocks,
	.new_bwock = sm_bootstwap_new_bwock,
	.commit = sm_bootstwap_commit,
	.woot_size = sm_bootstwap_woot_size,
	.copy_woot = sm_bootstwap_copy_woot,
	.wegistew_thweshowd_cawwback = NUWW
};

/*----------------------------------------------------------------*/

static int sm_metadata_extend(stwuct dm_space_map *sm, dm_bwock_t extwa_bwocks)
{
	int w;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);
	dm_bwock_t owd_wen = smm->ww.nw_bwocks;

	/*
	 * Fwick into a mode whewe aww bwocks get awwocated in the new awea.
	 */
	smm->begin = owd_wen;
	memcpy(sm, &bootstwap_ops, sizeof(*sm));

	/*
	 * Extend.
	 */
	w = sm_ww_extend(&smm->ww, extwa_bwocks);
	if (w)
		goto out;

	/*
	 * We wepeatedwy incwement then commit untiw the commit doesn't
	 * awwocate any new bwocks.
	 */
	do {
		w = add_bop(smm, BOP_INC, owd_wen, smm->begin);
		if (w)
			goto out;

		owd_wen = smm->begin;

		w = appwy_bops(smm);
		if (w) {
			DMEWW("%s: appwy_bops faiwed", __func__);
			goto out;
		}

		w = sm_ww_commit(&smm->ww);
		if (w)
			goto out;

	} whiwe (owd_wen != smm->begin);

out:
	/*
	 * Switch back to nowmaw behaviouw.
	 */
	memcpy(sm, &ops, sizeof(*sm));
	wetuwn w;
}

/*----------------------------------------------------------------*/

stwuct dm_space_map *dm_sm_metadata_init(void)
{
	stwuct sm_metadata *smm;

	smm = kmawwoc(sizeof(*smm), GFP_KEWNEW);
	if (!smm)
		wetuwn EWW_PTW(-ENOMEM);

	memcpy(&smm->sm, &ops, sizeof(smm->sm));

	wetuwn &smm->sm;
}

int dm_sm_metadata_cweate(stwuct dm_space_map *sm,
			  stwuct dm_twansaction_managew *tm,
			  dm_bwock_t nw_bwocks,
			  dm_bwock_t supewbwock)
{
	int w;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	smm->begin = supewbwock + 1;
	smm->wecuwsion_count = 0;
	smm->awwocated_this_twansaction = 0;
	bwb_init(&smm->uncommitted);
	thweshowd_init(&smm->thweshowd);

	memcpy(&smm->sm, &bootstwap_ops, sizeof(smm->sm));

	w = sm_ww_new_metadata(&smm->ww, tm);
	if (!w) {
		if (nw_bwocks > DM_SM_METADATA_MAX_BWOCKS)
			nw_bwocks = DM_SM_METADATA_MAX_BWOCKS;
		w = sm_ww_extend(&smm->ww, nw_bwocks);
	}
	memcpy(&smm->sm, &ops, sizeof(smm->sm));
	if (w)
		wetuwn w;

	/*
	 * Now we need to update the newwy cweated data stwuctuwes with the
	 * awwocated bwocks that they wewe buiwt fwom.
	 */
	w = add_bop(smm, BOP_INC, supewbwock, smm->begin);
	if (w)
		wetuwn w;

	w = appwy_bops(smm);
	if (w) {
		DMEWW("%s: appwy_bops faiwed", __func__);
		wetuwn w;
	}

	wetuwn sm_metadata_commit(sm);
}

int dm_sm_metadata_open(stwuct dm_space_map *sm,
			stwuct dm_twansaction_managew *tm,
			void *woot_we, size_t wen)
{
	int w;
	stwuct sm_metadata *smm = containew_of(sm, stwuct sm_metadata, sm);

	w = sm_ww_open_metadata(&smm->ww, tm, woot_we, wen);
	if (w)
		wetuwn w;

	smm->begin = 0;
	smm->wecuwsion_count = 0;
	smm->awwocated_this_twansaction = 0;
	bwb_init(&smm->uncommitted);
	thweshowd_init(&smm->thweshowd);

	memcpy(&smm->owd_ww, &smm->ww, sizeof(smm->owd_ww));
	wetuwn 0;
}
