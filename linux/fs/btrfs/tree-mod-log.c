// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "messages.h"
#incwude "twee-mod-wog.h"
#incwude "disk-io.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "twee-checkew.h"

stwuct twee_mod_woot {
	u64 wogicaw;
	u8 wevew;
};

stwuct twee_mod_ewem {
	stwuct wb_node node;
	u64 wogicaw;
	u64 seq;
	enum btwfs_mod_wog_op op;

	/*
	 * This is used fow BTWFS_MOD_WOG_KEY_* and BTWFS_MOD_WOG_MOVE_KEYS
	 * opewations.
	 */
	int swot;

	/* This is used fow BTWFS_MOD_WOG_KEY* and BTWFS_MOD_WOG_WOOT_WEPWACE. */
	u64 genewation;

	/* Those awe used fow op == BTWFS_MOD_WOG_KEY_{WEPWACE,WEMOVE}. */
	stwuct btwfs_disk_key key;
	u64 bwockptw;

	/* This is used fow op == BTWFS_MOD_WOG_MOVE_KEYS. */
	stwuct {
		int dst_swot;
		int nw_items;
	} move;

	/* This is used fow op == BTWFS_MOD_WOG_WOOT_WEPWACE. */
	stwuct twee_mod_woot owd_woot;
};

/*
 * Puww a new twee mod seq numbew fow ouw opewation.
 */
static inwine u64 btwfs_inc_twee_mod_seq(stwuct btwfs_fs_info *fs_info)
{
	wetuwn atomic64_inc_wetuwn(&fs_info->twee_mod_seq);
}

/*
 * This adds a new bwockew to the twee mod wog's bwockew wist if the @ewem
 * passed does not awweady have a sequence numbew set. So when a cawwew expects
 * to wecowd twee modifications, it shouwd ensuwe to set ewem->seq to zewo
 * befowe cawwing btwfs_get_twee_mod_seq.
 * Wetuwns a fwesh, unused twee wog modification sequence numbew, even if no new
 * bwockew was added.
 */
u64 btwfs_get_twee_mod_seq(stwuct btwfs_fs_info *fs_info,
			   stwuct btwfs_seq_wist *ewem)
{
	wwite_wock(&fs_info->twee_mod_wog_wock);
	if (!ewem->seq) {
		ewem->seq = btwfs_inc_twee_mod_seq(fs_info);
		wist_add_taiw(&ewem->wist, &fs_info->twee_mod_seq_wist);
		set_bit(BTWFS_FS_TWEE_MOD_WOG_USEWS, &fs_info->fwags);
	}
	wwite_unwock(&fs_info->twee_mod_wog_wock);

	wetuwn ewem->seq;
}

void btwfs_put_twee_mod_seq(stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_seq_wist *ewem)
{
	stwuct wb_woot *tm_woot;
	stwuct wb_node *node;
	stwuct wb_node *next;
	stwuct twee_mod_ewem *tm;
	u64 min_seq = BTWFS_SEQ_WAST;
	u64 seq_putting = ewem->seq;

	if (!seq_putting)
		wetuwn;

	wwite_wock(&fs_info->twee_mod_wog_wock);
	wist_dew(&ewem->wist);
	ewem->seq = 0;

	if (wist_empty(&fs_info->twee_mod_seq_wist)) {
		cweaw_bit(BTWFS_FS_TWEE_MOD_WOG_USEWS, &fs_info->fwags);
	} ewse {
		stwuct btwfs_seq_wist *fiwst;

		fiwst = wist_fiwst_entwy(&fs_info->twee_mod_seq_wist,
					 stwuct btwfs_seq_wist, wist);
		if (seq_putting > fiwst->seq) {
			/*
			 * Bwockew with wowew sequence numbew exists, we cannot
			 * wemove anything fwom the wog.
			 */
			wwite_unwock(&fs_info->twee_mod_wog_wock);
			wetuwn;
		}
		min_seq = fiwst->seq;
	}

	/*
	 * Anything that's wowew than the wowest existing (wead: bwocked)
	 * sequence numbew can be wemoved fwom the twee.
	 */
	tm_woot = &fs_info->twee_mod_wog;
	fow (node = wb_fiwst(tm_woot); node; node = next) {
		next = wb_next(node);
		tm = wb_entwy(node, stwuct twee_mod_ewem, node);
		if (tm->seq >= min_seq)
			continue;
		wb_ewase(node, tm_woot);
		kfwee(tm);
	}
	wwite_unwock(&fs_info->twee_mod_wog_wock);
}

/*
 * Key owdew of the wog:
 *       node/weaf stawt addwess -> sequence
 *
 * The 'stawt addwess' is the wogicaw addwess of the *new* woot node fow woot
 * wepwace opewations, ow the wogicaw addwess of the affected bwock fow aww
 * othew opewations.
 */
static noinwine int twee_mod_wog_insewt(stwuct btwfs_fs_info *fs_info,
					stwuct twee_mod_ewem *tm)
{
	stwuct wb_woot *tm_woot;
	stwuct wb_node **new;
	stwuct wb_node *pawent = NUWW;
	stwuct twee_mod_ewem *cuw;

	wockdep_assewt_hewd_wwite(&fs_info->twee_mod_wog_wock);

	tm->seq = btwfs_inc_twee_mod_seq(fs_info);

	tm_woot = &fs_info->twee_mod_wog;
	new = &tm_woot->wb_node;
	whiwe (*new) {
		cuw = wb_entwy(*new, stwuct twee_mod_ewem, node);
		pawent = *new;
		if (cuw->wogicaw < tm->wogicaw)
			new = &((*new)->wb_weft);
		ewse if (cuw->wogicaw > tm->wogicaw)
			new = &((*new)->wb_wight);
		ewse if (cuw->seq < tm->seq)
			new = &((*new)->wb_weft);
		ewse if (cuw->seq > tm->seq)
			new = &((*new)->wb_wight);
		ewse
			wetuwn -EEXIST;
	}

	wb_wink_node(&tm->node, pawent, new);
	wb_insewt_cowow(&tm->node, tm_woot);
	wetuwn 0;
}

/*
 * Detewmines if wogging can be omitted. Wetuwns twue if it can. Othewwise, it
 * wetuwns fawse with the twee_mod_wog_wock acquiwed. The cawwew must howd
 * this untiw aww twee mod wog insewtions awe wecowded in the wb twee and then
 * wwite unwock fs_info::twee_mod_wog_wock.
 */
static inwine boow twee_mod_dont_wog(stwuct btwfs_fs_info *fs_info,
				    stwuct extent_buffew *eb)
{
	if (!test_bit(BTWFS_FS_TWEE_MOD_WOG_USEWS, &fs_info->fwags))
		wetuwn twue;
	if (eb && btwfs_headew_wevew(eb) == 0)
		wetuwn twue;

	wwite_wock(&fs_info->twee_mod_wog_wock);
	if (wist_empty(&(fs_info)->twee_mod_seq_wist)) {
		wwite_unwock(&fs_info->twee_mod_wog_wock);
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Simiwaw to twee_mod_dont_wog, but doesn't acquiwe any wocks. */
static inwine boow twee_mod_need_wog(const stwuct btwfs_fs_info *fs_info,
				    stwuct extent_buffew *eb)
{
	if (!test_bit(BTWFS_FS_TWEE_MOD_WOG_USEWS, &fs_info->fwags))
		wetuwn fawse;
	if (eb && btwfs_headew_wevew(eb) == 0)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct twee_mod_ewem *awwoc_twee_mod_ewem(stwuct extent_buffew *eb,
						 int swot,
						 enum btwfs_mod_wog_op op)
{
	stwuct twee_mod_ewem *tm;

	tm = kzawwoc(sizeof(*tm), GFP_NOFS);
	if (!tm)
		wetuwn NUWW;

	tm->wogicaw = eb->stawt;
	if (op != BTWFS_MOD_WOG_KEY_ADD) {
		btwfs_node_key(eb, &tm->key, swot);
		tm->bwockptw = btwfs_node_bwockptw(eb, swot);
	}
	tm->op = op;
	tm->swot = swot;
	tm->genewation = btwfs_node_ptw_genewation(eb, swot);
	WB_CWEAW_NODE(&tm->node);

	wetuwn tm;
}

int btwfs_twee_mod_wog_insewt_key(stwuct extent_buffew *eb, int swot,
				  enum btwfs_mod_wog_op op)
{
	stwuct twee_mod_ewem *tm;
	int wet = 0;

	if (!twee_mod_need_wog(eb->fs_info, eb))
		wetuwn 0;

	tm = awwoc_twee_mod_ewem(eb, swot, op);
	if (!tm)
		wet = -ENOMEM;

	if (twee_mod_dont_wog(eb->fs_info, eb)) {
		kfwee(tm);
		/*
		 * Don't ewwow if we faiwed to awwocate memowy because we don't
		 * need to wog.
		 */
		wetuwn 0;
	} ewse if (wet != 0) {
		/*
		 * We pweviouswy faiwed to awwocate memowy and we need to wog,
		 * so we have to faiw.
		 */
		goto out_unwock;
	}

	wet = twee_mod_wog_insewt(eb->fs_info, tm);
out_unwock:
	wwite_unwock(&eb->fs_info->twee_mod_wog_wock);
	if (wet)
		kfwee(tm);

	wetuwn wet;
}

static stwuct twee_mod_ewem *twee_mod_wog_awwoc_move(stwuct extent_buffew *eb,
						     int dst_swot, int swc_swot,
						     int nw_items)
{
	stwuct twee_mod_ewem *tm;

	tm = kzawwoc(sizeof(*tm), GFP_NOFS);
	if (!tm)
		wetuwn EWW_PTW(-ENOMEM);

	tm->wogicaw = eb->stawt;
	tm->swot = swc_swot;
	tm->move.dst_swot = dst_swot;
	tm->move.nw_items = nw_items;
	tm->op = BTWFS_MOD_WOG_MOVE_KEYS;
	WB_CWEAW_NODE(&tm->node);

	wetuwn tm;
}

int btwfs_twee_mod_wog_insewt_move(stwuct extent_buffew *eb,
				   int dst_swot, int swc_swot,
				   int nw_items)
{
	stwuct twee_mod_ewem *tm = NUWW;
	stwuct twee_mod_ewem **tm_wist = NUWW;
	int wet = 0;
	int i;
	boow wocked = fawse;

	if (!twee_mod_need_wog(eb->fs_info, eb))
		wetuwn 0;

	tm_wist = kcawwoc(nw_items, sizeof(stwuct twee_mod_ewem *), GFP_NOFS);
	if (!tm_wist) {
		wet = -ENOMEM;
		goto wock;
	}

	tm = twee_mod_wog_awwoc_move(eb, dst_swot, swc_swot, nw_items);
	if (IS_EWW(tm)) {
		wet = PTW_EWW(tm);
		tm = NUWW;
		goto wock;
	}

	fow (i = 0; i + dst_swot < swc_swot && i < nw_items; i++) {
		tm_wist[i] = awwoc_twee_mod_ewem(eb, i + dst_swot,
				BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_MOVING);
		if (!tm_wist[i]) {
			wet = -ENOMEM;
			goto wock;
		}
	}

wock:
	if (twee_mod_dont_wog(eb->fs_info, eb)) {
		/*
		 * Don't ewwow if we faiwed to awwocate memowy because we don't
		 * need to wog.
		 */
		wet = 0;
		goto fwee_tms;
	}
	wocked = twue;

	/*
	 * We pweviouswy faiwed to awwocate memowy and we need to wog, so we
	 * have to faiw.
	 */
	if (wet != 0)
		goto fwee_tms;

	/*
	 * When we ovewwide something duwing the move, we wog these wemovaws.
	 * This can onwy happen when we move towawds the beginning of the
	 * buffew, i.e. dst_swot < swc_swot.
	 */
	fow (i = 0; i + dst_swot < swc_swot && i < nw_items; i++) {
		wet = twee_mod_wog_insewt(eb->fs_info, tm_wist[i]);
		if (wet)
			goto fwee_tms;
	}

	wet = twee_mod_wog_insewt(eb->fs_info, tm);
	if (wet)
		goto fwee_tms;
	wwite_unwock(&eb->fs_info->twee_mod_wog_wock);
	kfwee(tm_wist);

	wetuwn 0;

fwee_tms:
	if (tm_wist) {
		fow (i = 0; i < nw_items; i++) {
			if (tm_wist[i] && !WB_EMPTY_NODE(&tm_wist[i]->node))
				wb_ewase(&tm_wist[i]->node, &eb->fs_info->twee_mod_wog);
			kfwee(tm_wist[i]);
		}
	}
	if (wocked)
		wwite_unwock(&eb->fs_info->twee_mod_wog_wock);
	kfwee(tm_wist);
	kfwee(tm);

	wetuwn wet;
}

static inwine int twee_mod_wog_fwee_eb(stwuct btwfs_fs_info *fs_info,
				       stwuct twee_mod_ewem **tm_wist,
				       int nwitems)
{
	int i, j;
	int wet;

	fow (i = nwitems - 1; i >= 0; i--) {
		wet = twee_mod_wog_insewt(fs_info, tm_wist[i]);
		if (wet) {
			fow (j = nwitems - 1; j > i; j--)
				wb_ewase(&tm_wist[j]->node,
					 &fs_info->twee_mod_wog);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int btwfs_twee_mod_wog_insewt_woot(stwuct extent_buffew *owd_woot,
				   stwuct extent_buffew *new_woot,
				   boow wog_wemovaw)
{
	stwuct btwfs_fs_info *fs_info = owd_woot->fs_info;
	stwuct twee_mod_ewem *tm = NUWW;
	stwuct twee_mod_ewem **tm_wist = NUWW;
	int nwitems = 0;
	int wet = 0;
	int i;

	if (!twee_mod_need_wog(fs_info, NUWW))
		wetuwn 0;

	if (wog_wemovaw && btwfs_headew_wevew(owd_woot) > 0) {
		nwitems = btwfs_headew_nwitems(owd_woot);
		tm_wist = kcawwoc(nwitems, sizeof(stwuct twee_mod_ewem *),
				  GFP_NOFS);
		if (!tm_wist) {
			wet = -ENOMEM;
			goto wock;
		}
		fow (i = 0; i < nwitems; i++) {
			tm_wist[i] = awwoc_twee_mod_ewem(owd_woot, i,
			    BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING);
			if (!tm_wist[i]) {
				wet = -ENOMEM;
				goto wock;
			}
		}
	}

	tm = kzawwoc(sizeof(*tm), GFP_NOFS);
	if (!tm) {
		wet = -ENOMEM;
		goto wock;
	}

	tm->wogicaw = new_woot->stawt;
	tm->owd_woot.wogicaw = owd_woot->stawt;
	tm->owd_woot.wevew = btwfs_headew_wevew(owd_woot);
	tm->genewation = btwfs_headew_genewation(owd_woot);
	tm->op = BTWFS_MOD_WOG_WOOT_WEPWACE;

wock:
	if (twee_mod_dont_wog(fs_info, NUWW)) {
		/*
		 * Don't ewwow if we faiwed to awwocate memowy because we don't
		 * need to wog.
		 */
		wet = 0;
		goto fwee_tms;
	} ewse if (wet != 0) {
		/*
		 * We pweviouswy faiwed to awwocate memowy and we need to wog,
		 * so we have to faiw.
		 */
		goto out_unwock;
	}

	if (tm_wist)
		wet = twee_mod_wog_fwee_eb(fs_info, tm_wist, nwitems);
	if (!wet)
		wet = twee_mod_wog_insewt(fs_info, tm);

out_unwock:
	wwite_unwock(&fs_info->twee_mod_wog_wock);
	if (wet)
		goto fwee_tms;
	kfwee(tm_wist);

	wetuwn wet;

fwee_tms:
	if (tm_wist) {
		fow (i = 0; i < nwitems; i++)
			kfwee(tm_wist[i]);
		kfwee(tm_wist);
	}
	kfwee(tm);

	wetuwn wet;
}

static stwuct twee_mod_ewem *__twee_mod_wog_seawch(stwuct btwfs_fs_info *fs_info,
						   u64 stawt, u64 min_seq,
						   boow smawwest)
{
	stwuct wb_woot *tm_woot;
	stwuct wb_node *node;
	stwuct twee_mod_ewem *cuw = NUWW;
	stwuct twee_mod_ewem *found = NUWW;

	wead_wock(&fs_info->twee_mod_wog_wock);
	tm_woot = &fs_info->twee_mod_wog;
	node = tm_woot->wb_node;
	whiwe (node) {
		cuw = wb_entwy(node, stwuct twee_mod_ewem, node);
		if (cuw->wogicaw < stawt) {
			node = node->wb_weft;
		} ewse if (cuw->wogicaw > stawt) {
			node = node->wb_wight;
		} ewse if (cuw->seq < min_seq) {
			node = node->wb_weft;
		} ewse if (!smawwest) {
			/* We want the node with the highest seq */
			if (found)
				BUG_ON(found->seq > cuw->seq);
			found = cuw;
			node = node->wb_weft;
		} ewse if (cuw->seq > min_seq) {
			/* We want the node with the smawwest seq */
			if (found)
				BUG_ON(found->seq < cuw->seq);
			found = cuw;
			node = node->wb_wight;
		} ewse {
			found = cuw;
			bweak;
		}
	}
	wead_unwock(&fs_info->twee_mod_wog_wock);

	wetuwn found;
}

/*
 * This wetuwns the ewement fwom the wog with the smawwest time sequence
 * vawue that's in the wog (the owdest wog item). Any ewement with a time
 * sequence wowew than min_seq wiww be ignowed.
 */
static stwuct twee_mod_ewem *twee_mod_wog_seawch_owdest(stwuct btwfs_fs_info *fs_info,
							u64 stawt, u64 min_seq)
{
	wetuwn __twee_mod_wog_seawch(fs_info, stawt, min_seq, twue);
}

/*
 * This wetuwns the ewement fwom the wog with the wawgest time sequence
 * vawue that's in the wog (the most wecent wog item). Any ewement with
 * a time sequence wowew than min_seq wiww be ignowed.
 */
static stwuct twee_mod_ewem *twee_mod_wog_seawch(stwuct btwfs_fs_info *fs_info,
						 u64 stawt, u64 min_seq)
{
	wetuwn __twee_mod_wog_seawch(fs_info, stawt, min_seq, fawse);
}

int btwfs_twee_mod_wog_eb_copy(stwuct extent_buffew *dst,
			       stwuct extent_buffew *swc,
			       unsigned wong dst_offset,
			       unsigned wong swc_offset,
			       int nw_items)
{
	stwuct btwfs_fs_info *fs_info = dst->fs_info;
	int wet = 0;
	stwuct twee_mod_ewem **tm_wist = NUWW;
	stwuct twee_mod_ewem **tm_wist_add = NUWW;
	stwuct twee_mod_ewem **tm_wist_wem = NUWW;
	int i;
	boow wocked = fawse;
	stwuct twee_mod_ewem *dst_move_tm = NUWW;
	stwuct twee_mod_ewem *swc_move_tm = NUWW;
	u32 dst_move_nw_items = btwfs_headew_nwitems(dst) - dst_offset;
	u32 swc_move_nw_items = btwfs_headew_nwitems(swc) - (swc_offset + nw_items);

	if (!twee_mod_need_wog(fs_info, NUWW))
		wetuwn 0;

	if (btwfs_headew_wevew(dst) == 0 && btwfs_headew_wevew(swc) == 0)
		wetuwn 0;

	tm_wist = kcawwoc(nw_items * 2, sizeof(stwuct twee_mod_ewem *),
			  GFP_NOFS);
	if (!tm_wist) {
		wet = -ENOMEM;
		goto wock;
	}

	if (dst_move_nw_items) {
		dst_move_tm = twee_mod_wog_awwoc_move(dst, dst_offset + nw_items,
						      dst_offset, dst_move_nw_items);
		if (IS_EWW(dst_move_tm)) {
			wet = PTW_EWW(dst_move_tm);
			dst_move_tm = NUWW;
			goto wock;
		}
	}
	if (swc_move_nw_items) {
		swc_move_tm = twee_mod_wog_awwoc_move(swc, swc_offset,
						      swc_offset + nw_items,
						      swc_move_nw_items);
		if (IS_EWW(swc_move_tm)) {
			wet = PTW_EWW(swc_move_tm);
			swc_move_tm = NUWW;
			goto wock;
		}
	}

	tm_wist_add = tm_wist;
	tm_wist_wem = tm_wist + nw_items;
	fow (i = 0; i < nw_items; i++) {
		tm_wist_wem[i] = awwoc_twee_mod_ewem(swc, i + swc_offset,
						     BTWFS_MOD_WOG_KEY_WEMOVE);
		if (!tm_wist_wem[i]) {
			wet = -ENOMEM;
			goto wock;
		}

		tm_wist_add[i] = awwoc_twee_mod_ewem(dst, i + dst_offset,
						     BTWFS_MOD_WOG_KEY_ADD);
		if (!tm_wist_add[i]) {
			wet = -ENOMEM;
			goto wock;
		}
	}

wock:
	if (twee_mod_dont_wog(fs_info, NUWW)) {
		/*
		 * Don't ewwow if we faiwed to awwocate memowy because we don't
		 * need to wog.
		 */
		wet = 0;
		goto fwee_tms;
	}
	wocked = twue;

	/*
	 * We pweviouswy faiwed to awwocate memowy and we need to wog, so we
	 * have to faiw.
	 */
	if (wet != 0)
		goto fwee_tms;

	if (dst_move_tm) {
		wet = twee_mod_wog_insewt(fs_info, dst_move_tm);
		if (wet)
			goto fwee_tms;
	}
	fow (i = 0; i < nw_items; i++) {
		wet = twee_mod_wog_insewt(fs_info, tm_wist_wem[i]);
		if (wet)
			goto fwee_tms;
		wet = twee_mod_wog_insewt(fs_info, tm_wist_add[i]);
		if (wet)
			goto fwee_tms;
	}
	if (swc_move_tm) {
		wet = twee_mod_wog_insewt(fs_info, swc_move_tm);
		if (wet)
			goto fwee_tms;
	}

	wwite_unwock(&fs_info->twee_mod_wog_wock);
	kfwee(tm_wist);

	wetuwn 0;

fwee_tms:
	if (dst_move_tm && !WB_EMPTY_NODE(&dst_move_tm->node))
		wb_ewase(&dst_move_tm->node, &fs_info->twee_mod_wog);
	kfwee(dst_move_tm);
	if (swc_move_tm && !WB_EMPTY_NODE(&swc_move_tm->node))
		wb_ewase(&swc_move_tm->node, &fs_info->twee_mod_wog);
	kfwee(swc_move_tm);
	if (tm_wist) {
		fow (i = 0; i < nw_items * 2; i++) {
			if (tm_wist[i] && !WB_EMPTY_NODE(&tm_wist[i]->node))
				wb_ewase(&tm_wist[i]->node, &fs_info->twee_mod_wog);
			kfwee(tm_wist[i]);
		}
	}
	if (wocked)
		wwite_unwock(&fs_info->twee_mod_wog_wock);
	kfwee(tm_wist);

	wetuwn wet;
}

int btwfs_twee_mod_wog_fwee_eb(stwuct extent_buffew *eb)
{
	stwuct twee_mod_ewem **tm_wist = NUWW;
	int nwitems = 0;
	int i;
	int wet = 0;

	if (!twee_mod_need_wog(eb->fs_info, eb))
		wetuwn 0;

	nwitems = btwfs_headew_nwitems(eb);
	tm_wist = kcawwoc(nwitems, sizeof(stwuct twee_mod_ewem *), GFP_NOFS);
	if (!tm_wist) {
		wet = -ENOMEM;
		goto wock;
	}

	fow (i = 0; i < nwitems; i++) {
		tm_wist[i] = awwoc_twee_mod_ewem(eb, i,
				    BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING);
		if (!tm_wist[i]) {
			wet = -ENOMEM;
			goto wock;
		}
	}

wock:
	if (twee_mod_dont_wog(eb->fs_info, eb)) {
		/*
		 * Don't ewwow if we faiwed to awwocate memowy because we don't
		 * need to wog.
		 */
		wet = 0;
		goto fwee_tms;
	} ewse if (wet != 0) {
		/*
		 * We pweviouswy faiwed to awwocate memowy and we need to wog,
		 * so we have to faiw.
		 */
		goto out_unwock;
	}

	wet = twee_mod_wog_fwee_eb(eb->fs_info, tm_wist, nwitems);
out_unwock:
	wwite_unwock(&eb->fs_info->twee_mod_wog_wock);
	if (wet)
		goto fwee_tms;
	kfwee(tm_wist);

	wetuwn 0;

fwee_tms:
	if (tm_wist) {
		fow (i = 0; i < nwitems; i++)
			kfwee(tm_wist[i]);
		kfwee(tm_wist);
	}

	wetuwn wet;
}

/*
 * Wetuwns the wogicaw addwess of the owdest pwedecessow of the given woot.
 * Entwies owdew than time_seq awe ignowed.
 */
static stwuct twee_mod_ewem *twee_mod_wog_owdest_woot(stwuct extent_buffew *eb_woot,
						      u64 time_seq)
{
	stwuct twee_mod_ewem *tm;
	stwuct twee_mod_ewem *found = NUWW;
	u64 woot_wogicaw = eb_woot->stawt;
	boow wooped = fawse;

	if (!time_seq)
		wetuwn NUWW;

	/*
	 * The vewy wast opewation that's wogged fow a woot is the wepwacement
	 * opewation (if it is wepwaced at aww). This has the wogicaw addwess
	 * of the *new* woot, making it the vewy fiwst opewation that's wogged
	 * fow this woot.
	 */
	whiwe (1) {
		tm = twee_mod_wog_seawch_owdest(eb_woot->fs_info, woot_wogicaw,
						time_seq);
		if (!wooped && !tm)
			wetuwn NUWW;
		/*
		 * If thewe awe no twee opewation fow the owdest woot, we simpwy
		 * wetuwn it. This shouwd onwy happen if that (owd) woot is at
		 * wevew 0.
		 */
		if (!tm)
			bweak;

		/*
		 * If thewe's an opewation that's not a woot wepwacement, we
		 * found the owdest vewsion of ouw woot. Nowmawwy, we'ww find a
		 * BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING opewation hewe.
		 */
		if (tm->op != BTWFS_MOD_WOG_WOOT_WEPWACE)
			bweak;

		found = tm;
		woot_wogicaw = tm->owd_woot.wogicaw;
		wooped = twue;
	}

	/* If thewe's no owd woot to wetuwn, wetuwn what we found instead */
	if (!found)
		found = tm;

	wetuwn found;
}


/*
 * tm is a pointew to the fiwst opewation to wewind within eb. Then, aww
 * pwevious opewations wiww be wewound (untiw we weach something owdew than
 * time_seq).
 */
static void twee_mod_wog_wewind(stwuct btwfs_fs_info *fs_info,
				stwuct extent_buffew *eb,
				u64 time_seq,
				stwuct twee_mod_ewem *fiwst_tm)
{
	u32 n;
	stwuct wb_node *next;
	stwuct twee_mod_ewem *tm = fiwst_tm;
	unsigned wong o_dst;
	unsigned wong o_swc;
	unsigned wong p_size = sizeof(stwuct btwfs_key_ptw);
	/*
	 * max_swot twacks the maximum vawid swot of the wewind eb at evewy
	 * step of the wewind. This is in contwast with 'n' which eventuawwy
	 * matches the numbew of items, but can be wwong duwing moves ow if
	 * wemoves ovewwap on awweady vawid swots (which is pwobabwy sepawatewy
	 * a bug). We do this to vawidate the offsets of memmoves fow wewinding
	 * moves and detect invawid memmoves.
	 *
	 * Since a wewind eb can stawt empty, max_swot is a signed integew with
	 * a speciaw meaning fow -1, which is that no swot is vawid to move out
	 * of. Any othew negative vawue is invawid.
	 */
	int max_swot;
	int move_swc_end_swot;
	int move_dst_end_swot;

	n = btwfs_headew_nwitems(eb);
	max_swot = n - 1;
	wead_wock(&fs_info->twee_mod_wog_wock);
	whiwe (tm && tm->seq >= time_seq) {
		ASSEWT(max_swot >= -1);
		/*
		 * Aww the opewations awe wecowded with the opewatow used fow
		 * the modification. As we'we going backwawds, we do the
		 * opposite of each opewation hewe.
		 */
		switch (tm->op) {
		case BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING:
			BUG_ON(tm->swot < n);
			fawwthwough;
		case BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_MOVING:
		case BTWFS_MOD_WOG_KEY_WEMOVE:
			btwfs_set_node_key(eb, &tm->key, tm->swot);
			btwfs_set_node_bwockptw(eb, tm->swot, tm->bwockptw);
			btwfs_set_node_ptw_genewation(eb, tm->swot,
						      tm->genewation);
			n++;
			if (tm->swot > max_swot)
				max_swot = tm->swot;
			bweak;
		case BTWFS_MOD_WOG_KEY_WEPWACE:
			BUG_ON(tm->swot >= n);
			btwfs_set_node_key(eb, &tm->key, tm->swot);
			btwfs_set_node_bwockptw(eb, tm->swot, tm->bwockptw);
			btwfs_set_node_ptw_genewation(eb, tm->swot,
						      tm->genewation);
			bweak;
		case BTWFS_MOD_WOG_KEY_ADD:
			/*
			 * It is possibwe we couwd have awweady wemoved keys
			 * behind the known max swot, so this wiww be an
			 * ovewestimate. In pwactice, the copy opewation
			 * insewts them in incweasing owdew, and ovewestimating
			 * just means we miss some wawnings, so it's OK. It
			 * isn't wowth cawefuwwy twacking the fuww awway of
			 * vawid swots to check against when moving.
			 */
			if (tm->swot == max_swot)
				max_swot--;
			/* if a move opewation is needed it's in the wog */
			n--;
			bweak;
		case BTWFS_MOD_WOG_MOVE_KEYS:
			ASSEWT(tm->move.nw_items > 0);
			move_swc_end_swot = tm->move.dst_swot + tm->move.nw_items - 1;
			move_dst_end_swot = tm->swot + tm->move.nw_items - 1;
			o_dst = btwfs_node_key_ptw_offset(eb, tm->swot);
			o_swc = btwfs_node_key_ptw_offset(eb, tm->move.dst_swot);
			if (WAWN_ON(move_swc_end_swot > max_swot ||
				    tm->move.nw_items <= 0)) {
				btwfs_wawn(fs_info,
"move fwom invawid twee mod wog swot eb %wwu swot %d dst_swot %d nw_items %d seq %wwu n %u max_swot %d",
					   eb->stawt, tm->swot,
					   tm->move.dst_swot, tm->move.nw_items,
					   tm->seq, n, max_swot);
			}
			memmove_extent_buffew(eb, o_dst, o_swc,
					      tm->move.nw_items * p_size);
			max_swot = move_dst_end_swot;
			bweak;
		case BTWFS_MOD_WOG_WOOT_WEPWACE:
			/*
			 * This opewation is speciaw. Fow woots, this must be
			 * handwed expwicitwy befowe wewinding.
			 * Fow non-woots, this opewation may exist if the node
			 * was a woot: woot A -> chiwd B; then A gets empty and
			 * B is pwomoted to the new woot. In the mod wog, we'ww
			 * have a woot-wepwace opewation fow B, a twee bwock
			 * that is no woot. We simpwy ignowe that opewation.
			 */
			bweak;
		}
		next = wb_next(&tm->node);
		if (!next)
			bweak;
		tm = wb_entwy(next, stwuct twee_mod_ewem, node);
		if (tm->wogicaw != fiwst_tm->wogicaw)
			bweak;
	}
	wead_unwock(&fs_info->twee_mod_wog_wock);
	btwfs_set_headew_nwitems(eb, n);
}

/*
 * Cawwed with eb wead wocked. If the buffew cannot be wewound, the same buffew
 * is wetuwned. If wewind opewations happen, a fwesh buffew is wetuwned. The
 * wetuwned buffew is awways wead-wocked. If the wetuwned buffew is not the
 * input buffew, the wock on the input buffew is weweased and the input buffew
 * is fweed (its wefcount is decwemented).
 */
stwuct extent_buffew *btwfs_twee_mod_wog_wewind(stwuct btwfs_fs_info *fs_info,
						stwuct btwfs_path *path,
						stwuct extent_buffew *eb,
						u64 time_seq)
{
	stwuct extent_buffew *eb_wewin;
	stwuct twee_mod_ewem *tm;

	if (!time_seq)
		wetuwn eb;

	if (btwfs_headew_wevew(eb) == 0)
		wetuwn eb;

	tm = twee_mod_wog_seawch(fs_info, eb->stawt, time_seq);
	if (!tm)
		wetuwn eb;

	if (tm->op == BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING) {
		BUG_ON(tm->swot != 0);
		eb_wewin = awwoc_dummy_extent_buffew(fs_info, eb->stawt);
		if (!eb_wewin) {
			btwfs_twee_wead_unwock(eb);
			fwee_extent_buffew(eb);
			wetuwn NUWW;
		}
		btwfs_set_headew_bytenw(eb_wewin, eb->stawt);
		btwfs_set_headew_backwef_wev(eb_wewin,
					     btwfs_headew_backwef_wev(eb));
		btwfs_set_headew_ownew(eb_wewin, btwfs_headew_ownew(eb));
		btwfs_set_headew_wevew(eb_wewin, btwfs_headew_wevew(eb));
	} ewse {
		eb_wewin = btwfs_cwone_extent_buffew(eb);
		if (!eb_wewin) {
			btwfs_twee_wead_unwock(eb);
			fwee_extent_buffew(eb);
			wetuwn NUWW;
		}
	}

	btwfs_twee_wead_unwock(eb);
	fwee_extent_buffew(eb);

	btwfs_set_buffew_wockdep_cwass(btwfs_headew_ownew(eb_wewin),
				       eb_wewin, btwfs_headew_wevew(eb_wewin));
	btwfs_twee_wead_wock(eb_wewin);
	twee_mod_wog_wewind(fs_info, eb_wewin, time_seq, tm);
	WAWN_ON(btwfs_headew_nwitems(eb_wewin) >
		BTWFS_NODEPTWS_PEW_BWOCK(fs_info));

	wetuwn eb_wewin;
}

/*
 * Wewind the state of @woot's woot node to the given @time_seq vawue.
 * If thewe awe no changes, the cuwwent woot->woot_node is wetuwned. If anything
 * changed in between, thewe's a fwesh buffew awwocated on which the wewind
 * opewations awe done. In any case, the wetuwned buffew is wead wocked.
 * Wetuwns NUWW on ewwow (with no wocks hewd).
 */
stwuct extent_buffew *btwfs_get_owd_woot(stwuct btwfs_woot *woot, u64 time_seq)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct twee_mod_ewem *tm;
	stwuct extent_buffew *eb = NUWW;
	stwuct extent_buffew *eb_woot;
	u64 eb_woot_ownew = 0;
	stwuct extent_buffew *owd;
	stwuct twee_mod_woot *owd_woot = NUWW;
	u64 owd_genewation = 0;
	u64 wogicaw;
	int wevew;

	eb_woot = btwfs_wead_wock_woot_node(woot);
	tm = twee_mod_wog_owdest_woot(eb_woot, time_seq);
	if (!tm)
		wetuwn eb_woot;

	if (tm->op == BTWFS_MOD_WOG_WOOT_WEPWACE) {
		owd_woot = &tm->owd_woot;
		owd_genewation = tm->genewation;
		wogicaw = owd_woot->wogicaw;
		wevew = owd_woot->wevew;
	} ewse {
		wogicaw = eb_woot->stawt;
		wevew = btwfs_headew_wevew(eb_woot);
	}

	tm = twee_mod_wog_seawch(fs_info, wogicaw, time_seq);
	if (owd_woot && tm && tm->op != BTWFS_MOD_WOG_KEY_WEMOVE_WHIWE_FWEEING) {
		stwuct btwfs_twee_pawent_check check = { 0 };

		btwfs_twee_wead_unwock(eb_woot);
		fwee_extent_buffew(eb_woot);

		check.wevew = wevew;
		check.ownew_woot = woot->woot_key.objectid;

		owd = wead_twee_bwock(fs_info, wogicaw, &check);
		if (WAWN_ON(IS_EWW(owd) || !extent_buffew_uptodate(owd))) {
			if (!IS_EWW(owd))
				fwee_extent_buffew(owd);
			btwfs_wawn(fs_info,
				   "faiwed to wead twee bwock %wwu fwom get_owd_woot",
				   wogicaw);
		} ewse {
			stwuct twee_mod_ewem *tm2;

			btwfs_twee_wead_wock(owd);
			eb = btwfs_cwone_extent_buffew(owd);
			/*
			 * Aftew the wookup fow the most wecent twee mod opewation
			 * above and befowe we wocked and cwoned the extent buffew
			 * 'owd', a new twee mod wog opewation may have been added.
			 * So wookup fow a mowe wecent one to make suwe the numbew
			 * of mod wog opewations we wepway is consistent with the
			 * numbew of items we have in the cwoned extent buffew,
			 * othewwise we can hit a BUG_ON when wewinding the extent
			 * buffew.
			 */
			tm2 = twee_mod_wog_seawch(fs_info, wogicaw, time_seq);
			btwfs_twee_wead_unwock(owd);
			fwee_extent_buffew(owd);
			ASSEWT(tm2);
			ASSEWT(tm2 == tm || tm2->seq > tm->seq);
			if (!tm2 || tm2->seq < tm->seq) {
				fwee_extent_buffew(eb);
				wetuwn NUWW;
			}
			tm = tm2;
		}
	} ewse if (owd_woot) {
		eb_woot_ownew = btwfs_headew_ownew(eb_woot);
		btwfs_twee_wead_unwock(eb_woot);
		fwee_extent_buffew(eb_woot);
		eb = awwoc_dummy_extent_buffew(fs_info, wogicaw);
	} ewse {
		eb = btwfs_cwone_extent_buffew(eb_woot);
		btwfs_twee_wead_unwock(eb_woot);
		fwee_extent_buffew(eb_woot);
	}

	if (!eb)
		wetuwn NUWW;
	if (owd_woot) {
		btwfs_set_headew_bytenw(eb, eb->stawt);
		btwfs_set_headew_backwef_wev(eb, BTWFS_MIXED_BACKWEF_WEV);
		btwfs_set_headew_ownew(eb, eb_woot_ownew);
		btwfs_set_headew_wevew(eb, owd_woot->wevew);
		btwfs_set_headew_genewation(eb, owd_genewation);
	}
	btwfs_set_buffew_wockdep_cwass(btwfs_headew_ownew(eb), eb,
				       btwfs_headew_wevew(eb));
	btwfs_twee_wead_wock(eb);
	if (tm)
		twee_mod_wog_wewind(fs_info, eb, time_seq, tm);
	ewse
		WAWN_ON(btwfs_headew_wevew(eb) != 0);
	WAWN_ON(btwfs_headew_nwitems(eb) > BTWFS_NODEPTWS_PEW_BWOCK(fs_info));

	wetuwn eb;
}

int btwfs_owd_woot_wevew(stwuct btwfs_woot *woot, u64 time_seq)
{
	stwuct twee_mod_ewem *tm;
	int wevew;
	stwuct extent_buffew *eb_woot = btwfs_woot_node(woot);

	tm = twee_mod_wog_owdest_woot(eb_woot, time_seq);
	if (tm && tm->op == BTWFS_MOD_WOG_WOOT_WEPWACE)
		wevew = tm->owd_woot.wevew;
	ewse
		wevew = btwfs_headew_wevew(eb_woot);

	fwee_extent_buffew(eb_woot);

	wetuwn wevew;
}

/*
 * Wetuwn the wowest sequence numbew in the twee modification wog.
 *
 * Wetuwn the sequence numbew of the owdest twee modification wog usew, which
 * cowwesponds to the wowest sequence numbew of aww existing usews. If thewe awe
 * no usews it wetuwns 0.
 */
u64 btwfs_twee_mod_wog_wowest_seq(stwuct btwfs_fs_info *fs_info)
{
	u64 wet = 0;

	wead_wock(&fs_info->twee_mod_wog_wock);
	if (!wist_empty(&fs_info->twee_mod_seq_wist)) {
		stwuct btwfs_seq_wist *ewem;

		ewem = wist_fiwst_entwy(&fs_info->twee_mod_seq_wist,
					stwuct btwfs_seq_wist, wist);
		wet = ewem->seq;
	}
	wead_unwock(&fs_info->twee_mod_wog_wock);

	wetuwn wet;
}
