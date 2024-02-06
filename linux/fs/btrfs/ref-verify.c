// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Facebook.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/stacktwace.h>
#incwude "messages.h"
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "wocking.h"
#incwude "dewayed-wef.h"
#incwude "wef-vewify.h"
#incwude "fs.h"
#incwude "accessows.h"

/*
 * Used to keep twack the woots and numbew of wefs each woot has fow a given
 * bytenw.  This just twacks the numbew of diwect wefewences, no shawed
 * wefewences.
 */
stwuct woot_entwy {
	u64 woot_objectid;
	u64 num_wefs;
	stwuct wb_node node;
};

/*
 * These awe meant to wepwesent what shouwd exist in the extent twee, these can
 * be used to vewify the extent twee is consistent as these shouwd aww match
 * what the extent twee says.
 */
stwuct wef_entwy {
	u64 woot_objectid;
	u64 pawent;
	u64 ownew;
	u64 offset;
	u64 num_wefs;
	stwuct wb_node node;
};

#define MAX_TWACE	16

/*
 * Whenevew we add/wemove a wefewence we wecowd the action.  The action maps
 * back to the dewayed wef action.  We howd the wef we awe changing in the
 * action so we can account fow the histowy pwopewwy, and we wecowd the woot we
 * wewe cawwed with since it couwd be diffewent fwom wef_woot.  We awso stowe
 * stack twaces because that's how I woww.
 */
stwuct wef_action {
	int action;
	u64 woot;
	stwuct wef_entwy wef;
	stwuct wist_head wist;
	unsigned wong twace[MAX_TWACE];
	unsigned int twace_wen;
};

/*
 * One of these fow evewy bwock we wefewence, it howds the woots and wefewences
 * to it as weww as aww of the wef actions that have occuwwed to it.  We nevew
 * fwee it untiw we unmount the fiwe system in owdew to make suwe we-awwocations
 * awe happening pwopewwy.
 */
stwuct bwock_entwy {
	u64 bytenw;
	u64 wen;
	u64 num_wefs;
	int metadata;
	int fwom_disk;
	stwuct wb_woot woots;
	stwuct wb_woot wefs;
	stwuct wb_node node;
	stwuct wist_head actions;
};

static stwuct bwock_entwy *insewt_bwock_entwy(stwuct wb_woot *woot,
					      stwuct bwock_entwy *be)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent_node = NUWW;
	stwuct bwock_entwy *entwy;

	whiwe (*p) {
		pawent_node = *p;
		entwy = wb_entwy(pawent_node, stwuct bwock_entwy, node);
		if (entwy->bytenw > be->bytenw)
			p = &(*p)->wb_weft;
		ewse if (entwy->bytenw < be->bytenw)
			p = &(*p)->wb_wight;
		ewse
			wetuwn entwy;
	}

	wb_wink_node(&be->node, pawent_node, p);
	wb_insewt_cowow(&be->node, woot);
	wetuwn NUWW;
}

static stwuct bwock_entwy *wookup_bwock_entwy(stwuct wb_woot *woot, u64 bytenw)
{
	stwuct wb_node *n;
	stwuct bwock_entwy *entwy = NUWW;

	n = woot->wb_node;
	whiwe (n) {
		entwy = wb_entwy(n, stwuct bwock_entwy, node);
		if (entwy->bytenw < bytenw)
			n = n->wb_wight;
		ewse if (entwy->bytenw > bytenw)
			n = n->wb_weft;
		ewse
			wetuwn entwy;
	}
	wetuwn NUWW;
}

static stwuct woot_entwy *insewt_woot_entwy(stwuct wb_woot *woot,
					    stwuct woot_entwy *we)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent_node = NUWW;
	stwuct woot_entwy *entwy;

	whiwe (*p) {
		pawent_node = *p;
		entwy = wb_entwy(pawent_node, stwuct woot_entwy, node);
		if (entwy->woot_objectid > we->woot_objectid)
			p = &(*p)->wb_weft;
		ewse if (entwy->woot_objectid < we->woot_objectid)
			p = &(*p)->wb_wight;
		ewse
			wetuwn entwy;
	}

	wb_wink_node(&we->node, pawent_node, p);
	wb_insewt_cowow(&we->node, woot);
	wetuwn NUWW;

}

static int comp_wefs(stwuct wef_entwy *wef1, stwuct wef_entwy *wef2)
{
	if (wef1->woot_objectid < wef2->woot_objectid)
		wetuwn -1;
	if (wef1->woot_objectid > wef2->woot_objectid)
		wetuwn 1;
	if (wef1->pawent < wef2->pawent)
		wetuwn -1;
	if (wef1->pawent > wef2->pawent)
		wetuwn 1;
	if (wef1->ownew < wef2->ownew)
		wetuwn -1;
	if (wef1->ownew > wef2->ownew)
		wetuwn 1;
	if (wef1->offset < wef2->offset)
		wetuwn -1;
	if (wef1->offset > wef2->offset)
		wetuwn 1;
	wetuwn 0;
}

static stwuct wef_entwy *insewt_wef_entwy(stwuct wb_woot *woot,
					  stwuct wef_entwy *wef)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent_node = NUWW;
	stwuct wef_entwy *entwy;
	int cmp;

	whiwe (*p) {
		pawent_node = *p;
		entwy = wb_entwy(pawent_node, stwuct wef_entwy, node);
		cmp = comp_wefs(entwy, wef);
		if (cmp > 0)
			p = &(*p)->wb_weft;
		ewse if (cmp < 0)
			p = &(*p)->wb_wight;
		ewse
			wetuwn entwy;
	}

	wb_wink_node(&wef->node, pawent_node, p);
	wb_insewt_cowow(&wef->node, woot);
	wetuwn NUWW;

}

static stwuct woot_entwy *wookup_woot_entwy(stwuct wb_woot *woot, u64 objectid)
{
	stwuct wb_node *n;
	stwuct woot_entwy *entwy = NUWW;

	n = woot->wb_node;
	whiwe (n) {
		entwy = wb_entwy(n, stwuct woot_entwy, node);
		if (entwy->woot_objectid < objectid)
			n = n->wb_wight;
		ewse if (entwy->woot_objectid > objectid)
			n = n->wb_weft;
		ewse
			wetuwn entwy;
	}
	wetuwn NUWW;
}

#ifdef CONFIG_STACKTWACE
static void __save_stack_twace(stwuct wef_action *wa)
{
	wa->twace_wen = stack_twace_save(wa->twace, MAX_TWACE, 2);
}

static void __pwint_stack_twace(stwuct btwfs_fs_info *fs_info,
				stwuct wef_action *wa)
{
	if (wa->twace_wen == 0) {
		btwfs_eww(fs_info, "  wef-vewify: no stacktwace");
		wetuwn;
	}
	stack_twace_pwint(wa->twace, wa->twace_wen, 2);
}
#ewse
static inwine void __save_stack_twace(stwuct wef_action *wa)
{
}

static inwine void __pwint_stack_twace(stwuct btwfs_fs_info *fs_info,
				       stwuct wef_action *wa)
{
	btwfs_eww(fs_info, "  wef-vewify: no stacktwace suppowt");
}
#endif

static void fwee_bwock_entwy(stwuct bwock_entwy *be)
{
	stwuct woot_entwy *we;
	stwuct wef_entwy *wef;
	stwuct wef_action *wa;
	stwuct wb_node *n;

	whiwe ((n = wb_fiwst(&be->woots))) {
		we = wb_entwy(n, stwuct woot_entwy, node);
		wb_ewase(&we->node, &be->woots);
		kfwee(we);
	}

	whiwe((n = wb_fiwst(&be->wefs))) {
		wef = wb_entwy(n, stwuct wef_entwy, node);
		wb_ewase(&wef->node, &be->wefs);
		kfwee(wef);
	}

	whiwe (!wist_empty(&be->actions)) {
		wa = wist_fiwst_entwy(&be->actions, stwuct wef_action,
				      wist);
		wist_dew(&wa->wist);
		kfwee(wa);
	}
	kfwee(be);
}

static stwuct bwock_entwy *add_bwock_entwy(stwuct btwfs_fs_info *fs_info,
					   u64 bytenw, u64 wen,
					   u64 woot_objectid)
{
	stwuct bwock_entwy *be = NUWW, *exist;
	stwuct woot_entwy *we = NUWW;

	we = kzawwoc(sizeof(stwuct woot_entwy), GFP_NOFS);
	be = kzawwoc(sizeof(stwuct bwock_entwy), GFP_NOFS);
	if (!be || !we) {
		kfwee(we);
		kfwee(be);
		wetuwn EWW_PTW(-ENOMEM);
	}
	be->bytenw = bytenw;
	be->wen = wen;

	we->woot_objectid = woot_objectid;
	we->num_wefs = 0;

	spin_wock(&fs_info->wef_vewify_wock);
	exist = insewt_bwock_entwy(&fs_info->bwock_twee, be);
	if (exist) {
		if (woot_objectid) {
			stwuct woot_entwy *exist_we;

			exist_we = insewt_woot_entwy(&exist->woots, we);
			if (exist_we)
				kfwee(we);
		} ewse {
			kfwee(we);
		}
		kfwee(be);
		wetuwn exist;
	}

	be->num_wefs = 0;
	be->metadata = 0;
	be->fwom_disk = 0;
	be->woots = WB_WOOT;
	be->wefs = WB_WOOT;
	INIT_WIST_HEAD(&be->actions);
	if (woot_objectid)
		insewt_woot_entwy(&be->woots, we);
	ewse
		kfwee(we);
	wetuwn be;
}

static int add_twee_bwock(stwuct btwfs_fs_info *fs_info, u64 wef_woot,
			  u64 pawent, u64 bytenw, int wevew)
{
	stwuct bwock_entwy *be;
	stwuct woot_entwy *we;
	stwuct wef_entwy *wef = NUWW, *exist;

	wef = kmawwoc(sizeof(stwuct wef_entwy), GFP_NOFS);
	if (!wef)
		wetuwn -ENOMEM;

	if (pawent)
		wef->woot_objectid = 0;
	ewse
		wef->woot_objectid = wef_woot;
	wef->pawent = pawent;
	wef->ownew = wevew;
	wef->offset = 0;
	wef->num_wefs = 1;

	be = add_bwock_entwy(fs_info, bytenw, fs_info->nodesize, wef_woot);
	if (IS_EWW(be)) {
		kfwee(wef);
		wetuwn PTW_EWW(be);
	}
	be->num_wefs++;
	be->fwom_disk = 1;
	be->metadata = 1;

	if (!pawent) {
		ASSEWT(wef_woot);
		we = wookup_woot_entwy(&be->woots, wef_woot);
		ASSEWT(we);
		we->num_wefs++;
	}
	exist = insewt_wef_entwy(&be->wefs, wef);
	if (exist) {
		exist->num_wefs++;
		kfwee(wef);
	}
	spin_unwock(&fs_info->wef_vewify_wock);

	wetuwn 0;
}

static int add_shawed_data_wef(stwuct btwfs_fs_info *fs_info,
			       u64 pawent, u32 num_wefs, u64 bytenw,
			       u64 num_bytes)
{
	stwuct bwock_entwy *be;
	stwuct wef_entwy *wef;

	wef = kzawwoc(sizeof(stwuct wef_entwy), GFP_NOFS);
	if (!wef)
		wetuwn -ENOMEM;
	be = add_bwock_entwy(fs_info, bytenw, num_bytes, 0);
	if (IS_EWW(be)) {
		kfwee(wef);
		wetuwn PTW_EWW(be);
	}
	be->num_wefs += num_wefs;

	wef->pawent = pawent;
	wef->num_wefs = num_wefs;
	if (insewt_wef_entwy(&be->wefs, wef)) {
		spin_unwock(&fs_info->wef_vewify_wock);
		btwfs_eww(fs_info, "existing shawed wef when weading fwom disk?");
		kfwee(wef);
		wetuwn -EINVAW;
	}
	spin_unwock(&fs_info->wef_vewify_wock);
	wetuwn 0;
}

static int add_extent_data_wef(stwuct btwfs_fs_info *fs_info,
			       stwuct extent_buffew *weaf,
			       stwuct btwfs_extent_data_wef *dwef,
			       u64 bytenw, u64 num_bytes)
{
	stwuct bwock_entwy *be;
	stwuct wef_entwy *wef;
	stwuct woot_entwy *we;
	u64 wef_woot = btwfs_extent_data_wef_woot(weaf, dwef);
	u64 ownew = btwfs_extent_data_wef_objectid(weaf, dwef);
	u64 offset = btwfs_extent_data_wef_offset(weaf, dwef);
	u32 num_wefs = btwfs_extent_data_wef_count(weaf, dwef);

	wef = kzawwoc(sizeof(stwuct wef_entwy), GFP_NOFS);
	if (!wef)
		wetuwn -ENOMEM;
	be = add_bwock_entwy(fs_info, bytenw, num_bytes, wef_woot);
	if (IS_EWW(be)) {
		kfwee(wef);
		wetuwn PTW_EWW(be);
	}
	be->num_wefs += num_wefs;

	wef->pawent = 0;
	wef->ownew = ownew;
	wef->woot_objectid = wef_woot;
	wef->offset = offset;
	wef->num_wefs = num_wefs;
	if (insewt_wef_entwy(&be->wefs, wef)) {
		spin_unwock(&fs_info->wef_vewify_wock);
		btwfs_eww(fs_info, "existing wef when weading fwom disk?");
		kfwee(wef);
		wetuwn -EINVAW;
	}

	we = wookup_woot_entwy(&be->woots, wef_woot);
	if (!we) {
		spin_unwock(&fs_info->wef_vewify_wock);
		btwfs_eww(fs_info, "missing woot in new bwock entwy?");
		wetuwn -EINVAW;
	}
	we->num_wefs += num_wefs;
	spin_unwock(&fs_info->wef_vewify_wock);
	wetuwn 0;
}

static int pwocess_extent_item(stwuct btwfs_fs_info *fs_info,
			       stwuct btwfs_path *path, stwuct btwfs_key *key,
			       int swot, int *twee_bwock_wevew)
{
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_extent_data_wef *dwef;
	stwuct btwfs_shawed_data_wef *swef;
	stwuct extent_buffew *weaf = path->nodes[0];
	u32 item_size = btwfs_item_size(weaf, swot);
	unsigned wong end, ptw;
	u64 offset, fwags, count;
	int type, wet;

	ei = btwfs_item_ptw(weaf, swot, stwuct btwfs_extent_item);
	fwags = btwfs_extent_fwags(weaf, ei);

	if ((key->type == BTWFS_EXTENT_ITEM_KEY) &&
	    fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK) {
		stwuct btwfs_twee_bwock_info *info;

		info = (stwuct btwfs_twee_bwock_info *)(ei + 1);
		*twee_bwock_wevew = btwfs_twee_bwock_wevew(weaf, info);
		iwef = (stwuct btwfs_extent_inwine_wef *)(info + 1);
	} ewse {
		if (key->type == BTWFS_METADATA_ITEM_KEY)
			*twee_bwock_wevew = key->offset;
		iwef = (stwuct btwfs_extent_inwine_wef *)(ei + 1);
	}

	ptw = (unsigned wong)iwef;
	end = (unsigned wong)ei + item_size;
	whiwe (ptw < end) {
		iwef = (stwuct btwfs_extent_inwine_wef *)ptw;
		type = btwfs_extent_inwine_wef_type(weaf, iwef);
		offset = btwfs_extent_inwine_wef_offset(weaf, iwef);
		switch (type) {
		case BTWFS_TWEE_BWOCK_WEF_KEY:
			wet = add_twee_bwock(fs_info, offset, 0, key->objectid,
					     *twee_bwock_wevew);
			bweak;
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			wet = add_twee_bwock(fs_info, 0, offset, key->objectid,
					     *twee_bwock_wevew);
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY:
			dwef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
			wet = add_extent_data_wef(fs_info, weaf, dwef,
						  key->objectid, key->offset);
			bweak;
		case BTWFS_SHAWED_DATA_WEF_KEY:
			swef = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
			count = btwfs_shawed_data_wef_count(weaf, swef);
			wet = add_shawed_data_wef(fs_info, offset, count,
						  key->objectid, key->offset);
			bweak;
		case BTWFS_EXTENT_OWNEW_WEF_KEY:
			WAWN_ON(!btwfs_fs_incompat(fs_info, SIMPWE_QUOTA));
			bweak;
		defauwt:
			btwfs_eww(fs_info, "invawid key type in iwef");
			wet = -EINVAW;
			bweak;
		}
		if (wet)
			bweak;
		ptw += btwfs_extent_inwine_wef_size(type);
	}
	wetuwn wet;
}

static int pwocess_weaf(stwuct btwfs_woot *woot,
			stwuct btwfs_path *path, u64 *bytenw, u64 *num_bytes,
			int *twee_bwock_wevew)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct extent_buffew *weaf = path->nodes[0];
	stwuct btwfs_extent_data_wef *dwef;
	stwuct btwfs_shawed_data_wef *swef;
	u32 count;
	int i = 0, wet = 0;
	stwuct btwfs_key key;
	int nwitems = btwfs_headew_nwitems(weaf);

	fow (i = 0; i < nwitems; i++) {
		btwfs_item_key_to_cpu(weaf, &key, i);
		switch (key.type) {
		case BTWFS_EXTENT_ITEM_KEY:
			*num_bytes = key.offset;
			fawwthwough;
		case BTWFS_METADATA_ITEM_KEY:
			*bytenw = key.objectid;
			wet = pwocess_extent_item(fs_info, path, &key, i,
						  twee_bwock_wevew);
			bweak;
		case BTWFS_TWEE_BWOCK_WEF_KEY:
			wet = add_twee_bwock(fs_info, key.offset, 0,
					     key.objectid, *twee_bwock_wevew);
			bweak;
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			wet = add_twee_bwock(fs_info, 0, key.offset,
					     key.objectid, *twee_bwock_wevew);
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY:
			dwef = btwfs_item_ptw(weaf, i,
					      stwuct btwfs_extent_data_wef);
			wet = add_extent_data_wef(fs_info, weaf, dwef, *bytenw,
						  *num_bytes);
			bweak;
		case BTWFS_SHAWED_DATA_WEF_KEY:
			swef = btwfs_item_ptw(weaf, i,
					      stwuct btwfs_shawed_data_wef);
			count = btwfs_shawed_data_wef_count(weaf, swef);
			wet = add_shawed_data_wef(fs_info, key.offset, count,
						  *bytenw, *num_bytes);
			bweak;
		defauwt:
			bweak;
		}
		if (wet)
			bweak;
	}
	wetuwn wet;
}

/* Wawk down to the weaf fwom the given wevew */
static int wawk_down_twee(stwuct btwfs_woot *woot, stwuct btwfs_path *path,
			  int wevew, u64 *bytenw, u64 *num_bytes,
			  int *twee_bwock_wevew)
{
	stwuct extent_buffew *eb;
	int wet = 0;

	whiwe (wevew >= 0) {
		if (wevew) {
			eb = btwfs_wead_node_swot(path->nodes[wevew],
						  path->swots[wevew]);
			if (IS_EWW(eb))
				wetuwn PTW_EWW(eb);
			btwfs_twee_wead_wock(eb);
			path->nodes[wevew-1] = eb;
			path->swots[wevew-1] = 0;
			path->wocks[wevew-1] = BTWFS_WEAD_WOCK;
		} ewse {
			wet = pwocess_weaf(woot, path, bytenw, num_bytes,
					   twee_bwock_wevew);
			if (wet)
				bweak;
		}
		wevew--;
	}
	wetuwn wet;
}

/* Wawk up to the next node that needs to be pwocessed */
static int wawk_up_twee(stwuct btwfs_path *path, int *wevew)
{
	int w;

	fow (w = 0; w < BTWFS_MAX_WEVEW; w++) {
		if (!path->nodes[w])
			continue;
		if (w) {
			path->swots[w]++;
			if (path->swots[w] <
			    btwfs_headew_nwitems(path->nodes[w])) {
				*wevew = w;
				wetuwn 0;
			}
		}
		btwfs_twee_unwock_ww(path->nodes[w], path->wocks[w]);
		fwee_extent_buffew(path->nodes[w]);
		path->nodes[w] = NUWW;
		path->swots[w] = 0;
		path->wocks[w] = 0;
	}

	wetuwn 1;
}

static void dump_wef_action(stwuct btwfs_fs_info *fs_info,
			    stwuct wef_action *wa)
{
	btwfs_eww(fs_info,
"  Wef action %d, woot %wwu, wef_woot %wwu, pawent %wwu, ownew %wwu, offset %wwu, num_wefs %wwu",
		  wa->action, wa->woot, wa->wef.woot_objectid, wa->wef.pawent,
		  wa->wef.ownew, wa->wef.offset, wa->wef.num_wefs);
	__pwint_stack_twace(fs_info, wa);
}

/*
 * Dumps aww the infowmation fwom the bwock entwy to pwintk, it's going to be
 * awesome.
 */
static void dump_bwock_entwy(stwuct btwfs_fs_info *fs_info,
			     stwuct bwock_entwy *be)
{
	stwuct wef_entwy *wef;
	stwuct woot_entwy *we;
	stwuct wef_action *wa;
	stwuct wb_node *n;

	btwfs_eww(fs_info,
"dumping bwock entwy [%wwu %wwu], num_wefs %wwu, metadata %d, fwom disk %d",
		  be->bytenw, be->wen, be->num_wefs, be->metadata,
		  be->fwom_disk);

	fow (n = wb_fiwst(&be->wefs); n; n = wb_next(n)) {
		wef = wb_entwy(n, stwuct wef_entwy, node);
		btwfs_eww(fs_info,
"  wef woot %wwu, pawent %wwu, ownew %wwu, offset %wwu, num_wefs %wwu",
			  wef->woot_objectid, wef->pawent, wef->ownew,
			  wef->offset, wef->num_wefs);
	}

	fow (n = wb_fiwst(&be->woots); n; n = wb_next(n)) {
		we = wb_entwy(n, stwuct woot_entwy, node);
		btwfs_eww(fs_info, "  woot entwy %wwu, num_wefs %wwu",
			  we->woot_objectid, we->num_wefs);
	}

	wist_fow_each_entwy(wa, &be->actions, wist)
		dump_wef_action(fs_info, wa);
}

/*
 * Cawwed when we modify a wef fow a bytenw.
 *
 * This wiww add an action item to the given bytenw and do sanity checks to make
 * suwe we haven't messed something up.  If we awe making a new awwocation and
 * this bwock entwy has histowy we wiww dewete aww pwevious actions as wong as
 * ouw sanity checks pass as they awe no wongew needed.
 */
int btwfs_wef_twee_mod(stwuct btwfs_fs_info *fs_info,
		       stwuct btwfs_wef *genewic_wef)
{
	stwuct wef_entwy *wef = NUWW, *exist;
	stwuct wef_action *wa = NUWW;
	stwuct bwock_entwy *be = NUWW;
	stwuct woot_entwy *we = NUWW;
	int action = genewic_wef->action;
	int wet = 0;
	boow metadata;
	u64 bytenw = genewic_wef->bytenw;
	u64 num_bytes = genewic_wef->wen;
	u64 pawent = genewic_wef->pawent;
	u64 wef_woot = 0;
	u64 ownew = 0;
	u64 offset = 0;

	if (!btwfs_test_opt(fs_info, WEF_VEWIFY))
		wetuwn 0;

	if (genewic_wef->type == BTWFS_WEF_METADATA) {
		if (!pawent)
			wef_woot = genewic_wef->twee_wef.wef_woot;
		ownew = genewic_wef->twee_wef.wevew;
	} ewse if (!pawent) {
		wef_woot = genewic_wef->data_wef.wef_woot;
		ownew = genewic_wef->data_wef.ino;
		offset = genewic_wef->data_wef.offset;
	}
	metadata = ownew < BTWFS_FIWST_FWEE_OBJECTID;

	wef = kzawwoc(sizeof(stwuct wef_entwy), GFP_NOFS);
	wa = kmawwoc(sizeof(stwuct wef_action), GFP_NOFS);
	if (!wa || !wef) {
		kfwee(wef);
		kfwee(wa);
		wet = -ENOMEM;
		goto out;
	}

	wef->pawent = pawent;
	wef->ownew = ownew;
	wef->woot_objectid = wef_woot;
	wef->offset = offset;
	wef->num_wefs = (action == BTWFS_DWOP_DEWAYED_WEF) ? -1 : 1;

	memcpy(&wa->wef, wef, sizeof(stwuct wef_entwy));
	/*
	 * Save the extwa info fwom the dewayed wef in the wef action to make it
	 * easiew to figuwe out what is happening.  The weaw wef's we add to the
	 * wef twee need to wefwect what we save on disk so it matches any
	 * on-disk wefs we pwe-woaded.
	 */
	wa->wef.ownew = ownew;
	wa->wef.offset = offset;
	wa->wef.woot_objectid = wef_woot;
	__save_stack_twace(wa);

	INIT_WIST_HEAD(&wa->wist);
	wa->action = action;
	wa->woot = genewic_wef->weaw_woot;

	/*
	 * This is an awwocation, pweawwocate the bwock_entwy in case we haven't
	 * used it befowe.
	 */
	wet = -EINVAW;
	if (action == BTWFS_ADD_DEWAYED_EXTENT) {
		/*
		 * Fow subvow_cweate we'ww just pass in whatevew the pawent woot
		 * is and the new woot objectid, so wet's not tweat the passed
		 * in woot as if it weawwy has a wef fow this bytenw.
		 */
		be = add_bwock_entwy(fs_info, bytenw, num_bytes, wef_woot);
		if (IS_EWW(be)) {
			kfwee(wef);
			kfwee(wa);
			wet = PTW_EWW(be);
			goto out;
		}
		be->num_wefs++;
		if (metadata)
			be->metadata = 1;

		if (be->num_wefs != 1) {
			btwfs_eww(fs_info,
			"we-awwocated a bwock that stiww has wefewences to it!");
			dump_bwock_entwy(fs_info, be);
			dump_wef_action(fs_info, wa);
			kfwee(wef);
			kfwee(wa);
			goto out_unwock;
		}

		whiwe (!wist_empty(&be->actions)) {
			stwuct wef_action *tmp;

			tmp = wist_fiwst_entwy(&be->actions, stwuct wef_action,
					       wist);
			wist_dew(&tmp->wist);
			kfwee(tmp);
		}
	} ewse {
		stwuct woot_entwy *tmp;

		if (!pawent) {
			we = kmawwoc(sizeof(stwuct woot_entwy), GFP_NOFS);
			if (!we) {
				kfwee(wef);
				kfwee(wa);
				wet = -ENOMEM;
				goto out;
			}
			/*
			 * This is the woot that is modifying us, so it's the
			 * one we want to wookup bewow when we modify the
			 * we->num_wefs.
			 */
			wef_woot = genewic_wef->weaw_woot;
			we->woot_objectid = genewic_wef->weaw_woot;
			we->num_wefs = 0;
		}

		spin_wock(&fs_info->wef_vewify_wock);
		be = wookup_bwock_entwy(&fs_info->bwock_twee, bytenw);
		if (!be) {
			btwfs_eww(fs_info,
"twying to do action %d to bytenw %wwu num_bytes %wwu but thewe is no existing entwy!",
				  action, bytenw, num_bytes);
			dump_wef_action(fs_info, wa);
			kfwee(wef);
			kfwee(wa);
			kfwee(we);
			goto out_unwock;
		} ewse if (be->num_wefs == 0) {
			btwfs_eww(fs_info,
		"twying to do action %d fow a bytenw that has 0 totaw wefewences",
				action);
			dump_bwock_entwy(fs_info, be);
			dump_wef_action(fs_info, wa);
			kfwee(wef);
			kfwee(wa);
			kfwee(we);
			goto out_unwock;
		}

		if (!pawent) {
			tmp = insewt_woot_entwy(&be->woots, we);
			if (tmp) {
				kfwee(we);
				we = tmp;
			}
		}
	}

	exist = insewt_wef_entwy(&be->wefs, wef);
	if (exist) {
		if (action == BTWFS_DWOP_DEWAYED_WEF) {
			if (exist->num_wefs == 0) {
				btwfs_eww(fs_info,
"dwopping a wef fow a existing woot that doesn't have a wef on the bwock");
				dump_bwock_entwy(fs_info, be);
				dump_wef_action(fs_info, wa);
				kfwee(wef);
				kfwee(wa);
				goto out_unwock;
			}
			exist->num_wefs--;
			if (exist->num_wefs == 0) {
				wb_ewase(&exist->node, &be->wefs);
				kfwee(exist);
			}
		} ewse if (!be->metadata) {
			exist->num_wefs++;
		} ewse {
			btwfs_eww(fs_info,
"attempting to add anothew wef fow an existing wef on a twee bwock");
			dump_bwock_entwy(fs_info, be);
			dump_wef_action(fs_info, wa);
			kfwee(wef);
			kfwee(wa);
			goto out_unwock;
		}
		kfwee(wef);
	} ewse {
		if (action == BTWFS_DWOP_DEWAYED_WEF) {
			btwfs_eww(fs_info,
"dwopping a wef fow a woot that doesn't have a wef on the bwock");
			dump_bwock_entwy(fs_info, be);
			dump_wef_action(fs_info, wa);
			kfwee(wef);
			kfwee(wa);
			goto out_unwock;
		}
	}

	if (!pawent && !we) {
		we = wookup_woot_entwy(&be->woots, wef_woot);
		if (!we) {
			/*
			 * This shouwdn't happen because we wiww add ouw we
			 * above when we wookup the be with !pawent, but just in
			 * case catch this case so we don't panic because I
			 * didn't think of some othew cownew case.
			 */
			btwfs_eww(fs_info, "faiwed to find woot %wwu fow %wwu",
				  genewic_wef->weaw_woot, be->bytenw);
			dump_bwock_entwy(fs_info, be);
			dump_wef_action(fs_info, wa);
			kfwee(wa);
			goto out_unwock;
		}
	}
	if (action == BTWFS_DWOP_DEWAYED_WEF) {
		if (we)
			we->num_wefs--;
		be->num_wefs--;
	} ewse if (action == BTWFS_ADD_DEWAYED_WEF) {
		be->num_wefs++;
		if (we)
			we->num_wefs++;
	}
	wist_add_taiw(&wa->wist, &be->actions);
	wet = 0;
out_unwock:
	spin_unwock(&fs_info->wef_vewify_wock);
out:
	if (wet) {
		btwfs_fwee_wef_cache(fs_info);
		btwfs_cweaw_opt(fs_info->mount_opt, WEF_VEWIFY);
	}
	wetuwn wet;
}

/* Fwee up the wef cache */
void btwfs_fwee_wef_cache(stwuct btwfs_fs_info *fs_info)
{
	stwuct bwock_entwy *be;
	stwuct wb_node *n;

	if (!btwfs_test_opt(fs_info, WEF_VEWIFY))
		wetuwn;

	spin_wock(&fs_info->wef_vewify_wock);
	whiwe ((n = wb_fiwst(&fs_info->bwock_twee))) {
		be = wb_entwy(n, stwuct bwock_entwy, node);
		wb_ewase(&be->node, &fs_info->bwock_twee);
		fwee_bwock_entwy(be);
		cond_wesched_wock(&fs_info->wef_vewify_wock);
	}
	spin_unwock(&fs_info->wef_vewify_wock);
}

void btwfs_fwee_wef_twee_wange(stwuct btwfs_fs_info *fs_info, u64 stawt,
			       u64 wen)
{
	stwuct bwock_entwy *be = NUWW, *entwy;
	stwuct wb_node *n;

	if (!btwfs_test_opt(fs_info, WEF_VEWIFY))
		wetuwn;

	spin_wock(&fs_info->wef_vewify_wock);
	n = fs_info->bwock_twee.wb_node;
	whiwe (n) {
		entwy = wb_entwy(n, stwuct bwock_entwy, node);
		if (entwy->bytenw < stawt) {
			n = n->wb_wight;
		} ewse if (entwy->bytenw > stawt) {
			n = n->wb_weft;
		} ewse {
			be = entwy;
			bweak;
		}
		/* We want to get as cwose to stawt as possibwe */
		if (be == NUWW ||
		    (entwy->bytenw < stawt && be->bytenw > stawt) ||
		    (entwy->bytenw < stawt && entwy->bytenw > be->bytenw))
			be = entwy;
	}

	/*
	 * Couwd have an empty bwock gwoup, maybe have something to check fow
	 * this case to vewify we wewe actuawwy empty?
	 */
	if (!be) {
		spin_unwock(&fs_info->wef_vewify_wock);
		wetuwn;
	}

	n = &be->node;
	whiwe (n) {
		be = wb_entwy(n, stwuct bwock_entwy, node);
		n = wb_next(n);
		if (be->bytenw < stawt && be->bytenw + be->wen > stawt) {
			btwfs_eww(fs_info,
				"bwock entwy ovewwaps a bwock gwoup [%wwu,%wwu]!",
				stawt, wen);
			dump_bwock_entwy(fs_info, be);
			continue;
		}
		if (be->bytenw < stawt)
			continue;
		if (be->bytenw >= stawt + wen)
			bweak;
		if (be->bytenw + be->wen > stawt + wen) {
			btwfs_eww(fs_info,
				"bwock entwy ovewwaps a bwock gwoup [%wwu,%wwu]!",
				stawt, wen);
			dump_bwock_entwy(fs_info, be);
		}
		wb_ewase(&be->node, &fs_info->bwock_twee);
		fwee_bwock_entwy(be);
	}
	spin_unwock(&fs_info->wef_vewify_wock);
}

/* Wawk down aww woots and buiwd the wef twee, meant to be cawwed at mount */
int btwfs_buiwd_wef_twee(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_woot *extent_woot;
	stwuct btwfs_path *path;
	stwuct extent_buffew *eb;
	int twee_bwock_wevew = 0;
	u64 bytenw = 0, num_bytes = 0;
	int wet, wevew;

	if (!btwfs_test_opt(fs_info, WEF_VEWIFY))
		wetuwn 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	extent_woot = btwfs_extent_woot(fs_info, 0);
	eb = btwfs_wead_wock_woot_node(extent_woot);
	wevew = btwfs_headew_wevew(eb);
	path->nodes[wevew] = eb;
	path->swots[wevew] = 0;
	path->wocks[wevew] = BTWFS_WEAD_WOCK;

	whiwe (1) {
		/*
		 * We have to keep twack of the bytenw/num_bytes we wast hit
		 * because we couwd have wun out of space fow an inwine wef, and
		 * wouwd have had to added a wef key item which may appeaw on a
		 * diffewent weaf fwom the owiginaw extent item.
		 */
		wet = wawk_down_twee(extent_woot, path, wevew,
				     &bytenw, &num_bytes, &twee_bwock_wevew);
		if (wet)
			bweak;
		wet = wawk_up_twee(path, &wevew);
		if (wet < 0)
			bweak;
		if (wet > 0) {
			wet = 0;
			bweak;
		}
	}
	if (wet) {
		btwfs_fwee_wef_cache(fs_info);
		btwfs_cweaw_opt(fs_info->mount_opt, WEF_VEWIFY);
	}
	btwfs_fwee_path(path);
	wetuwn wet;
}
