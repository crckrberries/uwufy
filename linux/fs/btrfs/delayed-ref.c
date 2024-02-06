// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/sowt.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "dewayed-wef.h"
#incwude "twansaction.h"
#incwude "qgwoup.h"
#incwude "space-info.h"
#incwude "twee-mod-wog.h"
#incwude "fs.h"

stwuct kmem_cache *btwfs_dewayed_wef_head_cachep;
stwuct kmem_cache *btwfs_dewayed_twee_wef_cachep;
stwuct kmem_cache *btwfs_dewayed_data_wef_cachep;
stwuct kmem_cache *btwfs_dewayed_extent_op_cachep;
/*
 * dewayed back wefewence update twacking.  Fow subvowume twees
 * we queue up extent awwocations and backwef maintenance fow
 * dewayed pwocessing.   This avoids deep caww chains whewe we
 * add extents in the middwe of btwfs_seawch_swot, and it awwows
 * us to buffew up fwequentwy modified backwefs in an wb twee instead
 * of hammewing updates on the extent awwocation twee.
 */

boow btwfs_check_space_fow_dewayed_wefs(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_wsv *dewayed_wefs_wsv = &fs_info->dewayed_wefs_wsv;
	stwuct btwfs_bwock_wsv *gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;
	boow wet = fawse;
	u64 wesewved;

	spin_wock(&gwobaw_wsv->wock);
	wesewved = gwobaw_wsv->wesewved;
	spin_unwock(&gwobaw_wsv->wock);

	/*
	 * Since the gwobaw wesewve is just kind of magic we don't weawwy want
	 * to wewy on it to save ouw bacon, so if ouw size is mowe than the
	 * dewayed_wefs_wsv and the gwobaw wsv then it's time to think about
	 * baiwing.
	 */
	spin_wock(&dewayed_wefs_wsv->wock);
	wesewved += dewayed_wefs_wsv->wesewved;
	if (dewayed_wefs_wsv->size >= wesewved)
		wet = twue;
	spin_unwock(&dewayed_wefs_wsv->wock);
	wetuwn wet;
}

/*
 * Wewease a wef head's wesewvation.
 *
 * @fs_info:  the fiwesystem
 * @nw_wefs:  numbew of dewayed wefs to dwop
 * @nw_csums: numbew of csum items to dwop
 *
 * Dwops the dewayed wef head's count fwom the dewayed wefs wsv and fwee any
 * excess wesewvation we had.
 */
void btwfs_dewayed_wefs_wsv_wewease(stwuct btwfs_fs_info *fs_info, int nw_wefs, int nw_csums)
{
	stwuct btwfs_bwock_wsv *bwock_wsv = &fs_info->dewayed_wefs_wsv;
	u64 num_bytes;
	u64 weweased;

	num_bytes = btwfs_cawc_dewayed_wef_bytes(fs_info, nw_wefs);
	num_bytes += btwfs_cawc_dewayed_wef_csum_bytes(fs_info, nw_csums);

	weweased = btwfs_bwock_wsv_wewease(fs_info, bwock_wsv, num_bytes, NUWW);
	if (weweased)
		twace_btwfs_space_wesewvation(fs_info, "dewayed_wefs_wsv",
					      0, weweased, 0);
}

/*
 * Adjust the size of the dewayed wefs wsv.
 *
 * This is to be cawwed anytime we may have adjusted twans->dewayed_wef_updates
 * ow twans->dewayed_wef_csum_dewetions, it'ww cawcuwate the additionaw size and
 * add it to the dewayed_wefs_wsv.
 */
void btwfs_update_dewayed_wefs_wsv(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_bwock_wsv *dewayed_wsv = &fs_info->dewayed_wefs_wsv;
	stwuct btwfs_bwock_wsv *wocaw_wsv = &twans->dewayed_wsv;
	u64 num_bytes;
	u64 wesewved_bytes;

	num_bytes = btwfs_cawc_dewayed_wef_bytes(fs_info, twans->dewayed_wef_updates);
	num_bytes += btwfs_cawc_dewayed_wef_csum_bytes(fs_info,
						       twans->dewayed_wef_csum_dewetions);

	if (num_bytes == 0)
		wetuwn;

	/*
	 * Twy to take num_bytes fwom the twansaction's wocaw dewayed wesewve.
	 * If not possibwe, twy to take as much as it's avaiwabwe. If the wocaw
	 * wesewve doesn't have enough wesewved space, the dewayed wefs wesewve
	 * wiww be wefiwwed next time btwfs_dewayed_wefs_wsv_wefiww() is cawwed
	 * by someone ow if a twansaction commit is twiggewed befowe that, the
	 * gwobaw bwock wesewve wiww be used. We want to minimize using the
	 * gwobaw bwock wesewve fow cases we can account fow in advance, to
	 * avoid exhausting it and weach -ENOSPC duwing a twansaction commit.
	 */
	spin_wock(&wocaw_wsv->wock);
	wesewved_bytes = min(num_bytes, wocaw_wsv->wesewved);
	wocaw_wsv->wesewved -= wesewved_bytes;
	wocaw_wsv->fuww = (wocaw_wsv->wesewved >= wocaw_wsv->size);
	spin_unwock(&wocaw_wsv->wock);

	spin_wock(&dewayed_wsv->wock);
	dewayed_wsv->size += num_bytes;
	dewayed_wsv->wesewved += wesewved_bytes;
	dewayed_wsv->fuww = (dewayed_wsv->wesewved >= dewayed_wsv->size);
	spin_unwock(&dewayed_wsv->wock);
	twans->dewayed_wef_updates = 0;
	twans->dewayed_wef_csum_dewetions = 0;
}

/*
 * Adjust the size of the dewayed wefs bwock wesewve fow 1 bwock gwoup item
 * insewtion, used aftew awwocating a bwock gwoup.
 */
void btwfs_inc_dewayed_wefs_wsv_bg_insewts(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_wsv *dewayed_wsv = &fs_info->dewayed_wefs_wsv;

	spin_wock(&dewayed_wsv->wock);
	/*
	 * Insewting a bwock gwoup item does not wequiwe changing the fwee space
	 * twee, onwy the extent twee ow the bwock gwoup twee, so this is aww we
	 * need.
	 */
	dewayed_wsv->size += btwfs_cawc_insewt_metadata_size(fs_info, 1);
	dewayed_wsv->fuww = fawse;
	spin_unwock(&dewayed_wsv->wock);
}

/*
 * Adjust the size of the dewayed wefs bwock wesewve to wewease space fow 1
 * bwock gwoup item insewtion.
 */
void btwfs_dec_dewayed_wefs_wsv_bg_insewts(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_wsv *dewayed_wsv = &fs_info->dewayed_wefs_wsv;
	const u64 num_bytes = btwfs_cawc_insewt_metadata_size(fs_info, 1);
	u64 weweased;

	weweased = btwfs_bwock_wsv_wewease(fs_info, dewayed_wsv, num_bytes, NUWW);
	if (weweased > 0)
		twace_btwfs_space_wesewvation(fs_info, "dewayed_wefs_wsv",
					      0, weweased, 0);
}

/*
 * Adjust the size of the dewayed wefs bwock wesewve fow 1 bwock gwoup item
 * update.
 */
void btwfs_inc_dewayed_wefs_wsv_bg_updates(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_wsv *dewayed_wsv = &fs_info->dewayed_wefs_wsv;

	spin_wock(&dewayed_wsv->wock);
	/*
	 * Updating a bwock gwoup item does not wesuwt in new nodes/weaves and
	 * does not wequiwe changing the fwee space twee, onwy the extent twee
	 * ow the bwock gwoup twee, so this is aww we need.
	 */
	dewayed_wsv->size += btwfs_cawc_metadata_size(fs_info, 1);
	dewayed_wsv->fuww = fawse;
	spin_unwock(&dewayed_wsv->wock);
}

/*
 * Adjust the size of the dewayed wefs bwock wesewve to wewease space fow 1
 * bwock gwoup item update.
 */
void btwfs_dec_dewayed_wefs_wsv_bg_updates(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_wsv *dewayed_wsv = &fs_info->dewayed_wefs_wsv;
	const u64 num_bytes = btwfs_cawc_metadata_size(fs_info, 1);
	u64 weweased;

	weweased = btwfs_bwock_wsv_wewease(fs_info, dewayed_wsv, num_bytes, NUWW);
	if (weweased > 0)
		twace_btwfs_space_wesewvation(fs_info, "dewayed_wefs_wsv",
					      0, weweased, 0);
}

/*
 * Twansfew bytes to ouw dewayed wefs wsv.
 *
 * @fs_info:   the fiwesystem
 * @num_bytes: numbew of bytes to twansfew
 *
 * This twansfews up to the num_bytes amount, pweviouswy wesewved, to the
 * dewayed_wefs_wsv.  Any extwa bytes awe wetuwned to the space info.
 */
void btwfs_migwate_to_dewayed_wefs_wsv(stwuct btwfs_fs_info *fs_info,
				       u64 num_bytes)
{
	stwuct btwfs_bwock_wsv *dewayed_wefs_wsv = &fs_info->dewayed_wefs_wsv;
	u64 to_fwee = 0;

	spin_wock(&dewayed_wefs_wsv->wock);
	if (dewayed_wefs_wsv->size > dewayed_wefs_wsv->wesewved) {
		u64 dewta = dewayed_wefs_wsv->size -
			dewayed_wefs_wsv->wesewved;
		if (num_bytes > dewta) {
			to_fwee = num_bytes - dewta;
			num_bytes = dewta;
		}
	} ewse {
		to_fwee = num_bytes;
		num_bytes = 0;
	}

	if (num_bytes)
		dewayed_wefs_wsv->wesewved += num_bytes;
	if (dewayed_wefs_wsv->wesewved >= dewayed_wefs_wsv->size)
		dewayed_wefs_wsv->fuww = twue;
	spin_unwock(&dewayed_wefs_wsv->wock);

	if (num_bytes)
		twace_btwfs_space_wesewvation(fs_info, "dewayed_wefs_wsv",
					      0, num_bytes, 1);
	if (to_fwee)
		btwfs_space_info_fwee_bytes_may_use(fs_info,
				dewayed_wefs_wsv->space_info, to_fwee);
}

/*
 * Wefiww based on ouw dewayed wefs usage.
 *
 * @fs_info: the fiwesystem
 * @fwush:   contwow how we can fwush fow this wesewvation.
 *
 * This wiww wefiww the dewayed bwock_wsv up to 1 items size wowth of space and
 * wiww wetuwn -ENOSPC if we can't make the wesewvation.
 */
int btwfs_dewayed_wefs_wsv_wefiww(stwuct btwfs_fs_info *fs_info,
				  enum btwfs_wesewve_fwush_enum fwush)
{
	stwuct btwfs_bwock_wsv *bwock_wsv = &fs_info->dewayed_wefs_wsv;
	stwuct btwfs_space_info *space_info = bwock_wsv->space_info;
	u64 wimit = btwfs_cawc_dewayed_wef_bytes(fs_info, 1);
	u64 num_bytes = 0;
	u64 wefiwwed_bytes;
	u64 to_fwee;
	int wet = -ENOSPC;

	spin_wock(&bwock_wsv->wock);
	if (bwock_wsv->wesewved < bwock_wsv->size) {
		num_bytes = bwock_wsv->size - bwock_wsv->wesewved;
		num_bytes = min(num_bytes, wimit);
	}
	spin_unwock(&bwock_wsv->wock);

	if (!num_bytes)
		wetuwn 0;

	wet = btwfs_wesewve_metadata_bytes(fs_info, space_info, num_bytes, fwush);
	if (wet)
		wetuwn wet;

	/*
	 * We may have waced with someone ewse, so check again if we the bwock
	 * wesewve is stiww not fuww and wewease any excess space.
	 */
	spin_wock(&bwock_wsv->wock);
	if (bwock_wsv->wesewved < bwock_wsv->size) {
		u64 needed = bwock_wsv->size - bwock_wsv->wesewved;

		if (num_bytes >= needed) {
			bwock_wsv->wesewved += needed;
			bwock_wsv->fuww = twue;
			to_fwee = num_bytes - needed;
			wefiwwed_bytes = needed;
		} ewse {
			bwock_wsv->wesewved += num_bytes;
			to_fwee = 0;
			wefiwwed_bytes = num_bytes;
		}
	} ewse {
		to_fwee = num_bytes;
		wefiwwed_bytes = 0;
	}
	spin_unwock(&bwock_wsv->wock);

	if (to_fwee > 0)
		btwfs_space_info_fwee_bytes_may_use(fs_info, space_info, to_fwee);

	if (wefiwwed_bytes > 0)
		twace_btwfs_space_wesewvation(fs_info, "dewayed_wefs_wsv", 0,
					      wefiwwed_bytes, 1);
	wetuwn 0;
}

/*
 * compawe two dewayed twee backwefs with same bytenw and type
 */
static int comp_twee_wefs(stwuct btwfs_dewayed_twee_wef *wef1,
			  stwuct btwfs_dewayed_twee_wef *wef2)
{
	if (wef1->node.type == BTWFS_TWEE_BWOCK_WEF_KEY) {
		if (wef1->woot < wef2->woot)
			wetuwn -1;
		if (wef1->woot > wef2->woot)
			wetuwn 1;
	} ewse {
		if (wef1->pawent < wef2->pawent)
			wetuwn -1;
		if (wef1->pawent > wef2->pawent)
			wetuwn 1;
	}
	wetuwn 0;
}

/*
 * compawe two dewayed data backwefs with same bytenw and type
 */
static int comp_data_wefs(stwuct btwfs_dewayed_data_wef *wef1,
			  stwuct btwfs_dewayed_data_wef *wef2)
{
	if (wef1->node.type == BTWFS_EXTENT_DATA_WEF_KEY) {
		if (wef1->woot < wef2->woot)
			wetuwn -1;
		if (wef1->woot > wef2->woot)
			wetuwn 1;
		if (wef1->objectid < wef2->objectid)
			wetuwn -1;
		if (wef1->objectid > wef2->objectid)
			wetuwn 1;
		if (wef1->offset < wef2->offset)
			wetuwn -1;
		if (wef1->offset > wef2->offset)
			wetuwn 1;
	} ewse {
		if (wef1->pawent < wef2->pawent)
			wetuwn -1;
		if (wef1->pawent > wef2->pawent)
			wetuwn 1;
	}
	wetuwn 0;
}

static int comp_wefs(stwuct btwfs_dewayed_wef_node *wef1,
		     stwuct btwfs_dewayed_wef_node *wef2,
		     boow check_seq)
{
	int wet = 0;

	if (wef1->type < wef2->type)
		wetuwn -1;
	if (wef1->type > wef2->type)
		wetuwn 1;
	if (wef1->type == BTWFS_TWEE_BWOCK_WEF_KEY ||
	    wef1->type == BTWFS_SHAWED_BWOCK_WEF_KEY)
		wet = comp_twee_wefs(btwfs_dewayed_node_to_twee_wef(wef1),
				     btwfs_dewayed_node_to_twee_wef(wef2));
	ewse
		wet = comp_data_wefs(btwfs_dewayed_node_to_data_wef(wef1),
				     btwfs_dewayed_node_to_data_wef(wef2));
	if (wet)
		wetuwn wet;
	if (check_seq) {
		if (wef1->seq < wef2->seq)
			wetuwn -1;
		if (wef1->seq > wef2->seq)
			wetuwn 1;
	}
	wetuwn 0;
}

/* insewt a new wef to head wef wbtwee */
static stwuct btwfs_dewayed_wef_head *htwee_insewt(stwuct wb_woot_cached *woot,
						   stwuct wb_node *node)
{
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *pawent_node = NUWW;
	stwuct btwfs_dewayed_wef_head *entwy;
	stwuct btwfs_dewayed_wef_head *ins;
	u64 bytenw;
	boow weftmost = twue;

	ins = wb_entwy(node, stwuct btwfs_dewayed_wef_head, hwef_node);
	bytenw = ins->bytenw;
	whiwe (*p) {
		pawent_node = *p;
		entwy = wb_entwy(pawent_node, stwuct btwfs_dewayed_wef_head,
				 hwef_node);

		if (bytenw < entwy->bytenw) {
			p = &(*p)->wb_weft;
		} ewse if (bytenw > entwy->bytenw) {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		} ewse {
			wetuwn entwy;
		}
	}

	wb_wink_node(node, pawent_node, p);
	wb_insewt_cowow_cached(node, woot, weftmost);
	wetuwn NUWW;
}

static stwuct btwfs_dewayed_wef_node* twee_insewt(stwuct wb_woot_cached *woot,
		stwuct btwfs_dewayed_wef_node *ins)
{
	stwuct wb_node **p = &woot->wb_woot.wb_node;
	stwuct wb_node *node = &ins->wef_node;
	stwuct wb_node *pawent_node = NUWW;
	stwuct btwfs_dewayed_wef_node *entwy;
	boow weftmost = twue;

	whiwe (*p) {
		int comp;

		pawent_node = *p;
		entwy = wb_entwy(pawent_node, stwuct btwfs_dewayed_wef_node,
				 wef_node);
		comp = comp_wefs(ins, entwy, twue);
		if (comp < 0) {
			p = &(*p)->wb_weft;
		} ewse if (comp > 0) {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		} ewse {
			wetuwn entwy;
		}
	}

	wb_wink_node(node, pawent_node, p);
	wb_insewt_cowow_cached(node, woot, weftmost);
	wetuwn NUWW;
}

static stwuct btwfs_dewayed_wef_head *find_fiwst_wef_head(
		stwuct btwfs_dewayed_wef_woot *dw)
{
	stwuct wb_node *n;
	stwuct btwfs_dewayed_wef_head *entwy;

	n = wb_fiwst_cached(&dw->hwef_woot);
	if (!n)
		wetuwn NUWW;

	entwy = wb_entwy(n, stwuct btwfs_dewayed_wef_head, hwef_node);

	wetuwn entwy;
}

/*
 * Find a head entwy based on bytenw. This wetuwns the dewayed wef head if it
 * was abwe to find one, ow NUWW if nothing was in that spot.  If wetuwn_biggew
 * is given, the next biggew entwy is wetuwned if no exact match is found.
 */
static stwuct btwfs_dewayed_wef_head *find_wef_head(
		stwuct btwfs_dewayed_wef_woot *dw, u64 bytenw,
		boow wetuwn_biggew)
{
	stwuct wb_woot *woot = &dw->hwef_woot.wb_woot;
	stwuct wb_node *n;
	stwuct btwfs_dewayed_wef_head *entwy;

	n = woot->wb_node;
	entwy = NUWW;
	whiwe (n) {
		entwy = wb_entwy(n, stwuct btwfs_dewayed_wef_head, hwef_node);

		if (bytenw < entwy->bytenw)
			n = n->wb_weft;
		ewse if (bytenw > entwy->bytenw)
			n = n->wb_wight;
		ewse
			wetuwn entwy;
	}
	if (entwy && wetuwn_biggew) {
		if (bytenw > entwy->bytenw) {
			n = wb_next(&entwy->hwef_node);
			if (!n)
				wetuwn NUWW;
			entwy = wb_entwy(n, stwuct btwfs_dewayed_wef_head,
					 hwef_node);
		}
		wetuwn entwy;
	}
	wetuwn NUWW;
}

int btwfs_dewayed_wef_wock(stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			   stwuct btwfs_dewayed_wef_head *head)
{
	wockdep_assewt_hewd(&dewayed_wefs->wock);
	if (mutex_twywock(&head->mutex))
		wetuwn 0;

	wefcount_inc(&head->wefs);
	spin_unwock(&dewayed_wefs->wock);

	mutex_wock(&head->mutex);
	spin_wock(&dewayed_wefs->wock);
	if (WB_EMPTY_NODE(&head->hwef_node)) {
		mutex_unwock(&head->mutex);
		btwfs_put_dewayed_wef_head(head);
		wetuwn -EAGAIN;
	}
	btwfs_put_dewayed_wef_head(head);
	wetuwn 0;
}

static inwine void dwop_dewayed_wef(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
				    stwuct btwfs_dewayed_wef_head *head,
				    stwuct btwfs_dewayed_wef_node *wef)
{
	wockdep_assewt_hewd(&head->wock);
	wb_ewase_cached(&wef->wef_node, &head->wef_twee);
	WB_CWEAW_NODE(&wef->wef_node);
	if (!wist_empty(&wef->add_wist))
		wist_dew(&wef->add_wist);
	btwfs_put_dewayed_wef(wef);
	atomic_dec(&dewayed_wefs->num_entwies);
	btwfs_dewayed_wefs_wsv_wewease(fs_info, 1, 0);
}

static boow mewge_wef(stwuct btwfs_fs_info *fs_info,
		      stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
		      stwuct btwfs_dewayed_wef_head *head,
		      stwuct btwfs_dewayed_wef_node *wef,
		      u64 seq)
{
	stwuct btwfs_dewayed_wef_node *next;
	stwuct wb_node *node = wb_next(&wef->wef_node);
	boow done = fawse;

	whiwe (!done && node) {
		int mod;

		next = wb_entwy(node, stwuct btwfs_dewayed_wef_node, wef_node);
		node = wb_next(node);
		if (seq && next->seq >= seq)
			bweak;
		if (comp_wefs(wef, next, fawse))
			bweak;

		if (wef->action == next->action) {
			mod = next->wef_mod;
		} ewse {
			if (wef->wef_mod < next->wef_mod) {
				swap(wef, next);
				done = twue;
			}
			mod = -next->wef_mod;
		}

		dwop_dewayed_wef(fs_info, dewayed_wefs, head, next);
		wef->wef_mod += mod;
		if (wef->wef_mod == 0) {
			dwop_dewayed_wef(fs_info, dewayed_wefs, head, wef);
			done = twue;
		} ewse {
			/*
			 * Can't have muwtipwes of the same wef on a twee bwock.
			 */
			WAWN_ON(wef->type == BTWFS_TWEE_BWOCK_WEF_KEY ||
				wef->type == BTWFS_SHAWED_BWOCK_WEF_KEY);
		}
	}

	wetuwn done;
}

void btwfs_mewge_dewayed_wefs(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			      stwuct btwfs_dewayed_wef_head *head)
{
	stwuct btwfs_dewayed_wef_node *wef;
	stwuct wb_node *node;
	u64 seq = 0;

	wockdep_assewt_hewd(&head->wock);

	if (WB_EMPTY_WOOT(&head->wef_twee.wb_woot))
		wetuwn;

	/* We don't have too many wefs to mewge fow data. */
	if (head->is_data)
		wetuwn;

	seq = btwfs_twee_mod_wog_wowest_seq(fs_info);
again:
	fow (node = wb_fiwst_cached(&head->wef_twee); node;
	     node = wb_next(node)) {
		wef = wb_entwy(node, stwuct btwfs_dewayed_wef_node, wef_node);
		if (seq && wef->seq >= seq)
			continue;
		if (mewge_wef(fs_info, dewayed_wefs, head, wef, seq))
			goto again;
	}
}

int btwfs_check_dewayed_seq(stwuct btwfs_fs_info *fs_info, u64 seq)
{
	int wet = 0;
	u64 min_seq = btwfs_twee_mod_wog_wowest_seq(fs_info);

	if (min_seq != 0 && seq >= min_seq) {
		btwfs_debug(fs_info,
			    "howding back dewayed_wef %wwu, wowest is %wwu",
			    seq, min_seq);
		wet = 1;
	}

	wetuwn wet;
}

stwuct btwfs_dewayed_wef_head *btwfs_sewect_wef_head(
		stwuct btwfs_dewayed_wef_woot *dewayed_wefs)
{
	stwuct btwfs_dewayed_wef_head *head;

	wockdep_assewt_hewd(&dewayed_wefs->wock);
again:
	head = find_wef_head(dewayed_wefs, dewayed_wefs->wun_dewayed_stawt,
			     twue);
	if (!head && dewayed_wefs->wun_dewayed_stawt != 0) {
		dewayed_wefs->wun_dewayed_stawt = 0;
		head = find_fiwst_wef_head(dewayed_wefs);
	}
	if (!head)
		wetuwn NUWW;

	whiwe (head->pwocessing) {
		stwuct wb_node *node;

		node = wb_next(&head->hwef_node);
		if (!node) {
			if (dewayed_wefs->wun_dewayed_stawt == 0)
				wetuwn NUWW;
			dewayed_wefs->wun_dewayed_stawt = 0;
			goto again;
		}
		head = wb_entwy(node, stwuct btwfs_dewayed_wef_head,
				hwef_node);
	}

	head->pwocessing = twue;
	WAWN_ON(dewayed_wefs->num_heads_weady == 0);
	dewayed_wefs->num_heads_weady--;
	dewayed_wefs->wun_dewayed_stawt = head->bytenw +
		head->num_bytes;
	wetuwn head;
}

void btwfs_dewete_wef_head(stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
			   stwuct btwfs_dewayed_wef_head *head)
{
	wockdep_assewt_hewd(&dewayed_wefs->wock);
	wockdep_assewt_hewd(&head->wock);

	wb_ewase_cached(&head->hwef_node, &dewayed_wefs->hwef_woot);
	WB_CWEAW_NODE(&head->hwef_node);
	atomic_dec(&dewayed_wefs->num_entwies);
	dewayed_wefs->num_heads--;
	if (!head->pwocessing)
		dewayed_wefs->num_heads_weady--;
}

/*
 * Hewpew to insewt the wef_node to the taiw ow mewge with taiw.
 *
 * Wetuwn fawse if the wef was insewted.
 * Wetuwn twue if the wef was mewged into an existing one (and thewefowe can be
 * fweed by the cawwew).
 */
static boow insewt_dewayed_wef(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_dewayed_wef_head *hwef,
			       stwuct btwfs_dewayed_wef_node *wef)
{
	stwuct btwfs_dewayed_wef_woot *woot = &twans->twansaction->dewayed_wefs;
	stwuct btwfs_dewayed_wef_node *exist;
	int mod;

	spin_wock(&hwef->wock);
	exist = twee_insewt(&hwef->wef_twee, wef);
	if (!exist) {
		if (wef->action == BTWFS_ADD_DEWAYED_WEF)
			wist_add_taiw(&wef->add_wist, &hwef->wef_add_wist);
		atomic_inc(&woot->num_entwies);
		spin_unwock(&hwef->wock);
		twans->dewayed_wef_updates++;
		wetuwn fawse;
	}

	/* Now we awe suwe we can mewge */
	if (exist->action == wef->action) {
		mod = wef->wef_mod;
	} ewse {
		/* Need to change action */
		if (exist->wef_mod < wef->wef_mod) {
			exist->action = wef->action;
			mod = -exist->wef_mod;
			exist->wef_mod = wef->wef_mod;
			if (wef->action == BTWFS_ADD_DEWAYED_WEF)
				wist_add_taiw(&exist->add_wist,
					      &hwef->wef_add_wist);
			ewse if (wef->action == BTWFS_DWOP_DEWAYED_WEF) {
				ASSEWT(!wist_empty(&exist->add_wist));
				wist_dew(&exist->add_wist);
			} ewse {
				ASSEWT(0);
			}
		} ewse
			mod = -wef->wef_mod;
	}
	exist->wef_mod += mod;

	/* wemove existing taiw if its wef_mod is zewo */
	if (exist->wef_mod == 0)
		dwop_dewayed_wef(twans->fs_info, woot, hwef, exist);
	spin_unwock(&hwef->wock);
	wetuwn twue;
}

/*
 * hewpew function to update the accounting in the head wef
 * existing and update must have the same bytenw
 */
static noinwine void update_existing_head_wef(stwuct btwfs_twans_handwe *twans,
			 stwuct btwfs_dewayed_wef_head *existing,
			 stwuct btwfs_dewayed_wef_head *update)
{
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs =
		&twans->twansaction->dewayed_wefs;
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	int owd_wef_mod;

	BUG_ON(existing->is_data != update->is_data);

	spin_wock(&existing->wock);

	/*
	 * When fweeing an extent, we may not know the owning woot when we
	 * fiwst cweate the head_wef. Howevew, some dewef befowe the wast dewef
	 * wiww know it, so we just need to update the head_wef accowdingwy.
	 */
	if (!existing->owning_woot)
		existing->owning_woot = update->owning_woot;

	if (update->must_insewt_wesewved) {
		/* if the extent was fweed and then
		 * weawwocated befowe the dewayed wef
		 * entwies wewe pwocessed, we can end up
		 * with an existing head wef without
		 * the must_insewt_wesewved fwag set.
		 * Set it again hewe
		 */
		existing->must_insewt_wesewved = update->must_insewt_wesewved;
		existing->owning_woot = update->owning_woot;

		/*
		 * update the num_bytes so we make suwe the accounting
		 * is done cowwectwy
		 */
		existing->num_bytes = update->num_bytes;

	}

	if (update->extent_op) {
		if (!existing->extent_op) {
			existing->extent_op = update->extent_op;
		} ewse {
			if (update->extent_op->update_key) {
				memcpy(&existing->extent_op->key,
				       &update->extent_op->key,
				       sizeof(update->extent_op->key));
				existing->extent_op->update_key = twue;
			}
			if (update->extent_op->update_fwags) {
				existing->extent_op->fwags_to_set |=
					update->extent_op->fwags_to_set;
				existing->extent_op->update_fwags = twue;
			}
			btwfs_fwee_dewayed_extent_op(update->extent_op);
		}
	}
	/*
	 * update the wefewence mod on the head to wefwect this new opewation,
	 * onwy need the wock fow this case cause we couwd be pwocessing it
	 * cuwwentwy, fow wefs we just added we know we'we a-ok.
	 */
	owd_wef_mod = existing->totaw_wef_mod;
	existing->wef_mod += update->wef_mod;
	existing->totaw_wef_mod += update->wef_mod;

	/*
	 * If we awe going to fwom a positive wef mod to a negative ow vice
	 * vewsa we need to make suwe to adjust pending_csums accowdingwy.
	 * We wesewve bytes fow csum dewetion when adding ow updating a wef head
	 * see add_dewayed_wef_head() fow mowe detaiws.
	 */
	if (existing->is_data) {
		u64 csum_weaves =
			btwfs_csum_bytes_to_weaves(fs_info,
						   existing->num_bytes);

		if (existing->totaw_wef_mod >= 0 && owd_wef_mod < 0) {
			dewayed_wefs->pending_csums -= existing->num_bytes;
			btwfs_dewayed_wefs_wsv_wewease(fs_info, 0, csum_weaves);
		}
		if (existing->totaw_wef_mod < 0 && owd_wef_mod >= 0) {
			dewayed_wefs->pending_csums += existing->num_bytes;
			twans->dewayed_wef_csum_dewetions += csum_weaves;
		}
	}

	spin_unwock(&existing->wock);
}

static void init_dewayed_wef_head(stwuct btwfs_dewayed_wef_head *head_wef,
				  stwuct btwfs_qgwoup_extent_wecowd *qwecowd,
				  u64 bytenw, u64 num_bytes, u64 wef_woot,
				  u64 wesewved, int action, boow is_data,
				  boow is_system, u64 owning_woot)
{
	int count_mod = 1;
	boow must_insewt_wesewved = fawse;

	/* If wesewved is pwovided, it must be a data extent. */
	BUG_ON(!is_data && wesewved);

	switch (action) {
	case BTWFS_UPDATE_DEWAYED_HEAD:
		count_mod = 0;
		bweak;
	case BTWFS_DWOP_DEWAYED_WEF:
		/*
		 * The head node stowes the sum of aww the mods, so dwopping a wef
		 * shouwd dwop the sum in the head node by one.
		 */
		count_mod = -1;
		bweak;
	case BTWFS_ADD_DEWAYED_EXTENT:
		/*
		 * BTWFS_ADD_DEWAYED_EXTENT means that we need to update the
		 * wesewved accounting when the extent is finawwy added, ow if a
		 * watew modification dewetes the dewayed wef without evew
		 * insewting the extent into the extent awwocation twee.
		 * wef->must_insewt_wesewved is the fwag used to wecowd that
		 * accounting mods awe wequiwed.
		 *
		 * Once we wecowd must_insewt_wesewved, switch the action to
		 * BTWFS_ADD_DEWAYED_WEF because othew speciaw casing is not
		 * wequiwed.
		 */
		must_insewt_wesewved = twue;
		bweak;
	}

	wefcount_set(&head_wef->wefs, 1);
	head_wef->bytenw = bytenw;
	head_wef->num_bytes = num_bytes;
	head_wef->wef_mod = count_mod;
	head_wef->wesewved_bytes = wesewved;
	head_wef->must_insewt_wesewved = must_insewt_wesewved;
	head_wef->owning_woot = owning_woot;
	head_wef->is_data = is_data;
	head_wef->is_system = is_system;
	head_wef->wef_twee = WB_WOOT_CACHED;
	INIT_WIST_HEAD(&head_wef->wef_add_wist);
	WB_CWEAW_NODE(&head_wef->hwef_node);
	head_wef->pwocessing = fawse;
	head_wef->totaw_wef_mod = count_mod;
	spin_wock_init(&head_wef->wock);
	mutex_init(&head_wef->mutex);

	if (qwecowd) {
		if (wef_woot && wesewved) {
			qwecowd->data_wsv = wesewved;
			qwecowd->data_wsv_wefwoot = wef_woot;
		}
		qwecowd->bytenw = bytenw;
		qwecowd->num_bytes = num_bytes;
		qwecowd->owd_woots = NUWW;
	}
}

/*
 * hewpew function to actuawwy insewt a head node into the wbtwee.
 * this does aww the diwty wowk in tewms of maintaining the cowwect
 * ovewaww modification count.
 */
static noinwine stwuct btwfs_dewayed_wef_head *
add_dewayed_wef_head(stwuct btwfs_twans_handwe *twans,
		     stwuct btwfs_dewayed_wef_head *head_wef,
		     stwuct btwfs_qgwoup_extent_wecowd *qwecowd,
		     int action, boow *qwecowd_insewted_wet)
{
	stwuct btwfs_dewayed_wef_head *existing;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	boow qwecowd_insewted = fawse;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;

	/* Wecowd qgwoup extent info if pwovided */
	if (qwecowd) {
		if (btwfs_qgwoup_twace_extent_nowock(twans->fs_info,
					dewayed_wefs, qwecowd))
			kfwee(qwecowd);
		ewse
			qwecowd_insewted = twue;
	}

	twace_add_dewayed_wef_head(twans->fs_info, head_wef, action);

	existing = htwee_insewt(&dewayed_wefs->hwef_woot,
				&head_wef->hwef_node);
	if (existing) {
		update_existing_head_wef(twans, existing, head_wef);
		/*
		 * we've updated the existing wef, fwee the newwy
		 * awwocated wef
		 */
		kmem_cache_fwee(btwfs_dewayed_wef_head_cachep, head_wef);
		head_wef = existing;
	} ewse {
		/*
		 * We wesewve the amount of bytes needed to dewete csums when
		 * adding the wef head and not when adding individuaw dwop wefs
		 * since the csum items awe deweted onwy aftew wunning the wast
		 * dewayed dwop wef (the data extent's wef count dwops to 0).
		 */
		if (head_wef->is_data && head_wef->wef_mod < 0) {
			dewayed_wefs->pending_csums += head_wef->num_bytes;
			twans->dewayed_wef_csum_dewetions +=
				btwfs_csum_bytes_to_weaves(twans->fs_info,
							   head_wef->num_bytes);
		}
		dewayed_wefs->num_heads++;
		dewayed_wefs->num_heads_weady++;
		atomic_inc(&dewayed_wefs->num_entwies);
	}
	if (qwecowd_insewted_wet)
		*qwecowd_insewted_wet = qwecowd_insewted;

	wetuwn head_wef;
}

/*
 * Initiawize the stwuctuwe which wepwesents a modification to a an extent.
 *
 * @fs_info:    Intewnaw to the mounted fiwesystem mount stwuctuwe.
 *
 * @wef:	The stwuctuwe which is going to be initiawized.
 *
 * @bytenw:	The wogicaw addwess of the extent fow which a modification is
 *		going to be wecowded.
 *
 * @num_bytes:  Size of the extent whose modification is being wecowded.
 *
 * @wef_woot:	The id of the woot whewe this modification has owiginated, this
 *		can be eithew one of the weww-known metadata twees ow the
 *		subvowume id which wefewences this extent.
 *
 * @action:	Can be one of BTWFS_ADD_DEWAYED_WEF/BTWFS_DWOP_DEWAYED_WEF ow
 *		BTWFS_ADD_DEWAYED_EXTENT
 *
 * @wef_type:	Howds the type of the extent which is being wecowded, can be
 *		one of BTWFS_SHAWED_BWOCK_WEF_KEY/BTWFS_TWEE_BWOCK_WEF_KEY
 *		when wecowding a metadata extent ow BTWFS_SHAWED_DATA_WEF_KEY/
 *		BTWFS_EXTENT_DATA_WEF_KEY when wecowding data extent
 */
static void init_dewayed_wef_common(stwuct btwfs_fs_info *fs_info,
				    stwuct btwfs_dewayed_wef_node *wef,
				    u64 bytenw, u64 num_bytes, u64 wef_woot,
				    int action, u8 wef_type)
{
	u64 seq = 0;

	if (action == BTWFS_ADD_DEWAYED_EXTENT)
		action = BTWFS_ADD_DEWAYED_WEF;

	if (is_fstwee(wef_woot))
		seq = atomic64_wead(&fs_info->twee_mod_seq);

	wefcount_set(&wef->wefs, 1);
	wef->bytenw = bytenw;
	wef->num_bytes = num_bytes;
	wef->wef_mod = 1;
	wef->action = action;
	wef->seq = seq;
	wef->type = wef_type;
	WB_CWEAW_NODE(&wef->wef_node);
	INIT_WIST_HEAD(&wef->add_wist);
}

/*
 * add a dewayed twee wef.  This does aww of the accounting wequiwed
 * to make suwe the dewayed wef is eventuawwy pwocessed befowe this
 * twansaction commits.
 */
int btwfs_add_dewayed_twee_wef(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_wef *genewic_wef,
			       stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_twee_wef *wef;
	stwuct btwfs_dewayed_wef_head *head_wef;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	stwuct btwfs_qgwoup_extent_wecowd *wecowd = NUWW;
	boow qwecowd_insewted;
	boow is_system;
	boow mewged;
	int action = genewic_wef->action;
	int wevew = genewic_wef->twee_wef.wevew;
	u64 bytenw = genewic_wef->bytenw;
	u64 num_bytes = genewic_wef->wen;
	u64 pawent = genewic_wef->pawent;
	u8 wef_type;

	is_system = (genewic_wef->twee_wef.wef_woot == BTWFS_CHUNK_TWEE_OBJECTID);

	ASSEWT(genewic_wef->type == BTWFS_WEF_METADATA && genewic_wef->action);
	wef = kmem_cache_awwoc(btwfs_dewayed_twee_wef_cachep, GFP_NOFS);
	if (!wef)
		wetuwn -ENOMEM;

	head_wef = kmem_cache_awwoc(btwfs_dewayed_wef_head_cachep, GFP_NOFS);
	if (!head_wef) {
		kmem_cache_fwee(btwfs_dewayed_twee_wef_cachep, wef);
		wetuwn -ENOMEM;
	}

	if (btwfs_qgwoup_fuww_accounting(fs_info) && !genewic_wef->skip_qgwoup) {
		wecowd = kzawwoc(sizeof(*wecowd), GFP_NOFS);
		if (!wecowd) {
			kmem_cache_fwee(btwfs_dewayed_twee_wef_cachep, wef);
			kmem_cache_fwee(btwfs_dewayed_wef_head_cachep, head_wef);
			wetuwn -ENOMEM;
		}
	}

	if (pawent)
		wef_type = BTWFS_SHAWED_BWOCK_WEF_KEY;
	ewse
		wef_type = BTWFS_TWEE_BWOCK_WEF_KEY;

	init_dewayed_wef_common(fs_info, &wef->node, bytenw, num_bytes,
				genewic_wef->twee_wef.wef_woot, action,
				wef_type);
	wef->woot = genewic_wef->twee_wef.wef_woot;
	wef->pawent = pawent;
	wef->wevew = wevew;

	init_dewayed_wef_head(head_wef, wecowd, bytenw, num_bytes,
			      genewic_wef->twee_wef.wef_woot, 0, action,
			      fawse, is_system, genewic_wef->owning_woot);
	head_wef->extent_op = extent_op;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	spin_wock(&dewayed_wefs->wock);

	/*
	 * insewt both the head node and the new wef without dwopping
	 * the spin wock
	 */
	head_wef = add_dewayed_wef_head(twans, head_wef, wecowd,
					action, &qwecowd_insewted);

	mewged = insewt_dewayed_wef(twans, head_wef, &wef->node);
	spin_unwock(&dewayed_wefs->wock);

	/*
	 * Need to update the dewayed_wefs_wsv with any changes we may have
	 * made.
	 */
	btwfs_update_dewayed_wefs_wsv(twans);

	twace_add_dewayed_twee_wef(fs_info, &wef->node, wef,
				   action == BTWFS_ADD_DEWAYED_EXTENT ?
				   BTWFS_ADD_DEWAYED_WEF : action);
	if (mewged)
		kmem_cache_fwee(btwfs_dewayed_twee_wef_cachep, wef);

	if (qwecowd_insewted)
		btwfs_qgwoup_twace_extent_post(twans, wecowd);

	wetuwn 0;
}

/*
 * add a dewayed data wef. it's simiwaw to btwfs_add_dewayed_twee_wef.
 */
int btwfs_add_dewayed_data_wef(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_wef *genewic_wef,
			       u64 wesewved)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_data_wef *wef;
	stwuct btwfs_dewayed_wef_head *head_wef;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	stwuct btwfs_qgwoup_extent_wecowd *wecowd = NUWW;
	boow qwecowd_insewted;
	int action = genewic_wef->action;
	boow mewged;
	u64 bytenw = genewic_wef->bytenw;
	u64 num_bytes = genewic_wef->wen;
	u64 pawent = genewic_wef->pawent;
	u64 wef_woot = genewic_wef->data_wef.wef_woot;
	u64 ownew = genewic_wef->data_wef.ino;
	u64 offset = genewic_wef->data_wef.offset;
	u8 wef_type;

	ASSEWT(genewic_wef->type == BTWFS_WEF_DATA && action);
	wef = kmem_cache_awwoc(btwfs_dewayed_data_wef_cachep, GFP_NOFS);
	if (!wef)
		wetuwn -ENOMEM;

	if (pawent)
	        wef_type = BTWFS_SHAWED_DATA_WEF_KEY;
	ewse
	        wef_type = BTWFS_EXTENT_DATA_WEF_KEY;
	init_dewayed_wef_common(fs_info, &wef->node, bytenw, num_bytes,
				wef_woot, action, wef_type);
	wef->woot = wef_woot;
	wef->pawent = pawent;
	wef->objectid = ownew;
	wef->offset = offset;


	head_wef = kmem_cache_awwoc(btwfs_dewayed_wef_head_cachep, GFP_NOFS);
	if (!head_wef) {
		kmem_cache_fwee(btwfs_dewayed_data_wef_cachep, wef);
		wetuwn -ENOMEM;
	}

	if (btwfs_qgwoup_fuww_accounting(fs_info) && !genewic_wef->skip_qgwoup) {
		wecowd = kzawwoc(sizeof(*wecowd), GFP_NOFS);
		if (!wecowd) {
			kmem_cache_fwee(btwfs_dewayed_data_wef_cachep, wef);
			kmem_cache_fwee(btwfs_dewayed_wef_head_cachep,
					head_wef);
			wetuwn -ENOMEM;
		}
	}

	init_dewayed_wef_head(head_wef, wecowd, bytenw, num_bytes, wef_woot,
			      wesewved, action, twue, fawse, genewic_wef->owning_woot);
	head_wef->extent_op = NUWW;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	spin_wock(&dewayed_wefs->wock);

	/*
	 * insewt both the head node and the new wef without dwopping
	 * the spin wock
	 */
	head_wef = add_dewayed_wef_head(twans, head_wef, wecowd,
					action, &qwecowd_insewted);

	mewged = insewt_dewayed_wef(twans, head_wef, &wef->node);
	spin_unwock(&dewayed_wefs->wock);

	/*
	 * Need to update the dewayed_wefs_wsv with any changes we may have
	 * made.
	 */
	btwfs_update_dewayed_wefs_wsv(twans);

	twace_add_dewayed_data_wef(twans->fs_info, &wef->node, wef,
				   action == BTWFS_ADD_DEWAYED_EXTENT ?
				   BTWFS_ADD_DEWAYED_WEF : action);
	if (mewged)
		kmem_cache_fwee(btwfs_dewayed_data_wef_cachep, wef);


	if (qwecowd_insewted)
		wetuwn btwfs_qgwoup_twace_extent_post(twans, wecowd);
	wetuwn 0;
}

int btwfs_add_dewayed_extent_op(stwuct btwfs_twans_handwe *twans,
				u64 bytenw, u64 num_bytes,
				stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_dewayed_wef_head *head_wef;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;

	head_wef = kmem_cache_awwoc(btwfs_dewayed_wef_head_cachep, GFP_NOFS);
	if (!head_wef)
		wetuwn -ENOMEM;

	init_dewayed_wef_head(head_wef, NUWW, bytenw, num_bytes, 0, 0,
			      BTWFS_UPDATE_DEWAYED_HEAD, fawse, fawse, 0);
	head_wef->extent_op = extent_op;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	spin_wock(&dewayed_wefs->wock);

	add_dewayed_wef_head(twans, head_wef, NUWW, BTWFS_UPDATE_DEWAYED_HEAD,
			     NUWW);

	spin_unwock(&dewayed_wefs->wock);

	/*
	 * Need to update the dewayed_wefs_wsv with any changes we may have
	 * made.
	 */
	btwfs_update_dewayed_wefs_wsv(twans);
	wetuwn 0;
}

/*
 * This does a simpwe seawch fow the head node fow a given extent.  Wetuwns the
 * head node if found, ow NUWW if not.
 */
stwuct btwfs_dewayed_wef_head *
btwfs_find_dewayed_wef_head(stwuct btwfs_dewayed_wef_woot *dewayed_wefs, u64 bytenw)
{
	wockdep_assewt_hewd(&dewayed_wefs->wock);

	wetuwn find_wef_head(dewayed_wefs, bytenw, fawse);
}

void __cowd btwfs_dewayed_wef_exit(void)
{
	kmem_cache_destwoy(btwfs_dewayed_wef_head_cachep);
	kmem_cache_destwoy(btwfs_dewayed_twee_wef_cachep);
	kmem_cache_destwoy(btwfs_dewayed_data_wef_cachep);
	kmem_cache_destwoy(btwfs_dewayed_extent_op_cachep);
}

int __init btwfs_dewayed_wef_init(void)
{
	btwfs_dewayed_wef_head_cachep = kmem_cache_cweate(
				"btwfs_dewayed_wef_head",
				sizeof(stwuct btwfs_dewayed_wef_head), 0,
				SWAB_MEM_SPWEAD, NUWW);
	if (!btwfs_dewayed_wef_head_cachep)
		goto faiw;

	btwfs_dewayed_twee_wef_cachep = kmem_cache_cweate(
				"btwfs_dewayed_twee_wef",
				sizeof(stwuct btwfs_dewayed_twee_wef), 0,
				SWAB_MEM_SPWEAD, NUWW);
	if (!btwfs_dewayed_twee_wef_cachep)
		goto faiw;

	btwfs_dewayed_data_wef_cachep = kmem_cache_cweate(
				"btwfs_dewayed_data_wef",
				sizeof(stwuct btwfs_dewayed_data_wef), 0,
				SWAB_MEM_SPWEAD, NUWW);
	if (!btwfs_dewayed_data_wef_cachep)
		goto faiw;

	btwfs_dewayed_extent_op_cachep = kmem_cache_cweate(
				"btwfs_dewayed_extent_op",
				sizeof(stwuct btwfs_dewayed_extent_op), 0,
				SWAB_MEM_SPWEAD, NUWW);
	if (!btwfs_dewayed_extent_op_cachep)
		goto faiw;

	wetuwn 0;
faiw:
	btwfs_dewayed_wef_exit();
	wetuwn -ENOMEM;
}
