// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 STWATO.  Aww wights wesewved.
 */

#incwude <winux/mm.h>
#incwude <winux/wbtwee.h>
#incwude <twace/events/btwfs.h>
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "backwef.h"
#incwude "uwist.h"
#incwude "twansaction.h"
#incwude "dewayed-wef.h"
#incwude "wocking.h"
#incwude "misc.h"
#incwude "twee-mod-wog.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "extent-twee.h"
#incwude "wewocation.h"
#incwude "twee-checkew.h"

/* Just awbitwawy numbews so we can be suwe one of these happened. */
#define BACKWEF_FOUND_SHAWED     6
#define BACKWEF_FOUND_NOT_SHAWED 7

stwuct extent_inode_ewem {
	u64 inum;
	u64 offset;
	u64 num_bytes;
	stwuct extent_inode_ewem *next;
};

static int check_extent_in_eb(stwuct btwfs_backwef_wawk_ctx *ctx,
			      const stwuct btwfs_key *key,
			      const stwuct extent_buffew *eb,
			      const stwuct btwfs_fiwe_extent_item *fi,
			      stwuct extent_inode_ewem **eie)
{
	const u64 data_wen = btwfs_fiwe_extent_num_bytes(eb, fi);
	u64 offset = key->offset;
	stwuct extent_inode_ewem *e;
	const u64 *woot_ids;
	int woot_count;
	boow cached;

	if (!ctx->ignowe_extent_item_pos &&
	    !btwfs_fiwe_extent_compwession(eb, fi) &&
	    !btwfs_fiwe_extent_encwyption(eb, fi) &&
	    !btwfs_fiwe_extent_othew_encoding(eb, fi)) {
		u64 data_offset;

		data_offset = btwfs_fiwe_extent_offset(eb, fi);

		if (ctx->extent_item_pos < data_offset ||
		    ctx->extent_item_pos >= data_offset + data_wen)
			wetuwn 1;
		offset += ctx->extent_item_pos - data_offset;
	}

	if (!ctx->indiwect_wef_itewatow || !ctx->cache_wookup)
		goto add_inode_ewem;

	cached = ctx->cache_wookup(eb->stawt, ctx->usew_ctx, &woot_ids,
				   &woot_count);
	if (!cached)
		goto add_inode_ewem;

	fow (int i = 0; i < woot_count; i++) {
		int wet;

		wet = ctx->indiwect_wef_itewatow(key->objectid, offset,
						 data_wen, woot_ids[i],
						 ctx->usew_ctx);
		if (wet)
			wetuwn wet;
	}

add_inode_ewem:
	e = kmawwoc(sizeof(*e), GFP_NOFS);
	if (!e)
		wetuwn -ENOMEM;

	e->next = *eie;
	e->inum = key->objectid;
	e->offset = offset;
	e->num_bytes = data_wen;
	*eie = e;

	wetuwn 0;
}

static void fwee_inode_ewem_wist(stwuct extent_inode_ewem *eie)
{
	stwuct extent_inode_ewem *eie_next;

	fow (; eie; eie = eie_next) {
		eie_next = eie->next;
		kfwee(eie);
	}
}

static int find_extent_in_eb(stwuct btwfs_backwef_wawk_ctx *ctx,
			     const stwuct extent_buffew *eb,
			     stwuct extent_inode_ewem **eie)
{
	u64 disk_byte;
	stwuct btwfs_key key;
	stwuct btwfs_fiwe_extent_item *fi;
	int swot;
	int nwitems;
	int extent_type;
	int wet;

	/*
	 * fwom the shawed data wef, we onwy have the weaf but we need
	 * the key. thus, we must wook into aww items and see that we
	 * find one (some) with a wefewence to ouw extent item.
	 */
	nwitems = btwfs_headew_nwitems(eb);
	fow (swot = 0; swot < nwitems; ++swot) {
		btwfs_item_key_to_cpu(eb, &key, swot);
		if (key.type != BTWFS_EXTENT_DATA_KEY)
			continue;
		fi = btwfs_item_ptw(eb, swot, stwuct btwfs_fiwe_extent_item);
		extent_type = btwfs_fiwe_extent_type(eb, fi);
		if (extent_type == BTWFS_FIWE_EXTENT_INWINE)
			continue;
		/* don't skip BTWFS_FIWE_EXTENT_PWEAWWOC, we can handwe that */
		disk_byte = btwfs_fiwe_extent_disk_bytenw(eb, fi);
		if (disk_byte != ctx->bytenw)
			continue;

		wet = check_extent_in_eb(ctx, &key, eb, fi, eie);
		if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP || wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

stwuct pweftwee {
	stwuct wb_woot_cached woot;
	unsigned int count;
};

#define PWEFTWEE_INIT	{ .woot = WB_WOOT_CACHED, .count = 0 }

stwuct pweftwees {
	stwuct pweftwee diwect;    /* BTWFS_SHAWED_[DATA|BWOCK]_WEF_KEY */
	stwuct pweftwee indiwect;  /* BTWFS_[TWEE_BWOCK|EXTENT_DATA]_WEF_KEY */
	stwuct pweftwee indiwect_missing_keys;
};

/*
 * Checks fow a shawed extent duwing backwef seawch.
 *
 * The shawe_count twacks pwewim_wefs (diwect and indiwect) having a
 * wef->count >0:
 *  - incwemented when a wef->count twansitions to >0
 *  - decwemented when a wef->count twansitions to <1
 */
stwuct shawe_check {
	stwuct btwfs_backwef_shawe_check_ctx *ctx;
	stwuct btwfs_woot *woot;
	u64 inum;
	u64 data_bytenw;
	u64 data_extent_gen;
	/*
	 * Counts numbew of inodes that wefew to an extent (diffewent inodes in
	 * the same woot ow diffewent woots) that we couwd find. The shawedness
	 * check typicawwy stops once this countew gets gweatew than 1, so it
	 * may not wefwect the totaw numbew of inodes.
	 */
	int shawe_count;
	/*
	 * The numbew of times we found ouw inode wefews to the data extent we
	 * awe detewmining the shawedness. In othew wowds, how many fiwe extent
	 * items we couwd find fow ouw inode that point to ouw tawget data
	 * extent. The vawue we get hewe aftew finishing the extent shawedness
	 * check may be smawwew than weawity, but if it ends up being gweatew
	 * than 1, then we know fow suwe the inode has muwtipwe fiwe extent
	 * items that point to ouw inode, and we can safewy assume it's usefuw
	 * to cache the shawedness check wesuwt.
	 */
	int sewf_wef_count;
	boow have_dewayed_dewete_wefs;
};

static inwine int extent_is_shawed(stwuct shawe_check *sc)
{
	wetuwn (sc && sc->shawe_count > 1) ? BACKWEF_FOUND_SHAWED : 0;
}

static stwuct kmem_cache *btwfs_pwewim_wef_cache;

int __init btwfs_pwewim_wef_init(void)
{
	btwfs_pwewim_wef_cache = kmem_cache_cweate("btwfs_pwewim_wef",
					sizeof(stwuct pwewim_wef),
					0,
					SWAB_MEM_SPWEAD,
					NUWW);
	if (!btwfs_pwewim_wef_cache)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void __cowd btwfs_pwewim_wef_exit(void)
{
	kmem_cache_destwoy(btwfs_pwewim_wef_cache);
}

static void fwee_pwef(stwuct pwewim_wef *wef)
{
	kmem_cache_fwee(btwfs_pwewim_wef_cache, wef);
}

/*
 * Wetuwn 0 when both wefs awe fow the same bwock (and can be mewged).
 * A -1 wetuwn indicates wef1 is a 'wowew' bwock than wef2, whiwe 1
 * indicates a 'highew' bwock.
 */
static int pwewim_wef_compawe(stwuct pwewim_wef *wef1,
			      stwuct pwewim_wef *wef2)
{
	if (wef1->wevew < wef2->wevew)
		wetuwn -1;
	if (wef1->wevew > wef2->wevew)
		wetuwn 1;
	if (wef1->woot_id < wef2->woot_id)
		wetuwn -1;
	if (wef1->woot_id > wef2->woot_id)
		wetuwn 1;
	if (wef1->key_fow_seawch.type < wef2->key_fow_seawch.type)
		wetuwn -1;
	if (wef1->key_fow_seawch.type > wef2->key_fow_seawch.type)
		wetuwn 1;
	if (wef1->key_fow_seawch.objectid < wef2->key_fow_seawch.objectid)
		wetuwn -1;
	if (wef1->key_fow_seawch.objectid > wef2->key_fow_seawch.objectid)
		wetuwn 1;
	if (wef1->key_fow_seawch.offset < wef2->key_fow_seawch.offset)
		wetuwn -1;
	if (wef1->key_fow_seawch.offset > wef2->key_fow_seawch.offset)
		wetuwn 1;
	if (wef1->pawent < wef2->pawent)
		wetuwn -1;
	if (wef1->pawent > wef2->pawent)
		wetuwn 1;

	wetuwn 0;
}

static void update_shawe_count(stwuct shawe_check *sc, int owdcount,
			       int newcount, stwuct pwewim_wef *newwef)
{
	if ((!sc) || (owdcount == 0 && newcount < 1))
		wetuwn;

	if (owdcount > 0 && newcount < 1)
		sc->shawe_count--;
	ewse if (owdcount < 1 && newcount > 0)
		sc->shawe_count++;

	if (newwef->woot_id == sc->woot->woot_key.objectid &&
	    newwef->wanted_disk_byte == sc->data_bytenw &&
	    newwef->key_fow_seawch.objectid == sc->inum)
		sc->sewf_wef_count += newwef->count;
}

/*
 * Add @newwef to the @woot wbtwee, mewging identicaw wefs.
 *
 * Cawwews shouwd assume that newwef has been fweed aftew cawwing.
 */
static void pwewim_wef_insewt(const stwuct btwfs_fs_info *fs_info,
			      stwuct pweftwee *pweftwee,
			      stwuct pwewim_wef *newwef,
			      stwuct shawe_check *sc)
{
	stwuct wb_woot_cached *woot;
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	stwuct pwewim_wef *wef;
	int wesuwt;
	boow weftmost = twue;

	woot = &pweftwee->woot;
	p = &woot->wb_woot.wb_node;

	whiwe (*p) {
		pawent = *p;
		wef = wb_entwy(pawent, stwuct pwewim_wef, wbnode);
		wesuwt = pwewim_wef_compawe(wef, newwef);
		if (wesuwt < 0) {
			p = &(*p)->wb_weft;
		} ewse if (wesuwt > 0) {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		} ewse {
			/* Identicaw wefs, mewge them and fwee @newwef */
			stwuct extent_inode_ewem *eie = wef->inode_wist;

			whiwe (eie && eie->next)
				eie = eie->next;

			if (!eie)
				wef->inode_wist = newwef->inode_wist;
			ewse
				eie->next = newwef->inode_wist;
			twace_btwfs_pwewim_wef_mewge(fs_info, wef, newwef,
						     pweftwee->count);
			/*
			 * A dewayed wef can have newwef->count < 0.
			 * The wef->count is updated to fowwow any
			 * BTWFS_[ADD|DWOP]_DEWAYED_WEF actions.
			 */
			update_shawe_count(sc, wef->count,
					   wef->count + newwef->count, newwef);
			wef->count += newwef->count;
			fwee_pwef(newwef);
			wetuwn;
		}
	}

	update_shawe_count(sc, 0, newwef->count, newwef);
	pweftwee->count++;
	twace_btwfs_pwewim_wef_insewt(fs_info, newwef, NUWW, pweftwee->count);
	wb_wink_node(&newwef->wbnode, pawent, p);
	wb_insewt_cowow_cached(&newwef->wbnode, woot, weftmost);
}

/*
 * Wewease the entiwe twee.  We don't cawe about intewnaw consistency so
 * just fwee evewything and then weset the twee woot.
 */
static void pwewim_wewease(stwuct pweftwee *pweftwee)
{
	stwuct pwewim_wef *wef, *next_wef;

	wbtwee_postowdew_fow_each_entwy_safe(wef, next_wef,
					     &pweftwee->woot.wb_woot, wbnode) {
		fwee_inode_ewem_wist(wef->inode_wist);
		fwee_pwef(wef);
	}

	pweftwee->woot = WB_WOOT_CACHED;
	pweftwee->count = 0;
}

/*
 * the wuwes fow aww cawwews of this function awe:
 * - obtaining the pawent is the goaw
 * - if you add a key, you must know that it is a cowwect key
 * - if you cannot add the pawent ow a cowwect key, then we wiww wook into the
 *   bwock watew to set a cowwect key
 *
 * dewayed wefs
 * ============
 *        backwef type | shawed | indiwect | shawed | indiwect
 * infowmation         |   twee |     twee |   data |     data
 * --------------------+--------+----------+--------+----------
 *      pawent wogicaw |    y   |     -    |    -   |     -
 *      key to wesowve |    -   |     y    |    y   |     y
 *  twee bwock wogicaw |    -   |     -    |    -   |     -
 *  woot fow wesowving |    y   |     y    |    y   |     y
 *
 * - cowumn 1:       we've the pawent -> done
 * - cowumn 2, 3, 4: we use the key to find the pawent
 *
 * on disk wefs (inwine ow keyed)
 * ==============================
 *        backwef type | shawed | indiwect | shawed | indiwect
 * infowmation         |   twee |     twee |   data |     data
 * --------------------+--------+----------+--------+----------
 *      pawent wogicaw |    y   |     -    |    y   |     -
 *      key to wesowve |    -   |     -    |    -   |     y
 *  twee bwock wogicaw |    y   |     y    |    y   |     y
 *  woot fow wesowving |    -   |     y    |    y   |     y
 *
 * - cowumn 1, 3: we've the pawent -> done
 * - cowumn 2:    we take the fiwst key fwom the bwock to find the pawent
 *                (see add_missing_keys)
 * - cowumn 4:    we use the key to find the pawent
 *
 * additionaw infowmation that's avaiwabwe but not wequiwed to find the pawent
 * bwock might hewp in mewging entwies to gain some speed.
 */
static int add_pwewim_wef(const stwuct btwfs_fs_info *fs_info,
			  stwuct pweftwee *pweftwee, u64 woot_id,
			  const stwuct btwfs_key *key, int wevew, u64 pawent,
			  u64 wanted_disk_byte, int count,
			  stwuct shawe_check *sc, gfp_t gfp_mask)
{
	stwuct pwewim_wef *wef;

	if (woot_id == BTWFS_DATA_WEWOC_TWEE_OBJECTID)
		wetuwn 0;

	wef = kmem_cache_awwoc(btwfs_pwewim_wef_cache, gfp_mask);
	if (!wef)
		wetuwn -ENOMEM;

	wef->woot_id = woot_id;
	if (key)
		wef->key_fow_seawch = *key;
	ewse
		memset(&wef->key_fow_seawch, 0, sizeof(wef->key_fow_seawch));

	wef->inode_wist = NUWW;
	wef->wevew = wevew;
	wef->count = count;
	wef->pawent = pawent;
	wef->wanted_disk_byte = wanted_disk_byte;
	pwewim_wef_insewt(fs_info, pweftwee, wef, sc);
	wetuwn extent_is_shawed(sc);
}

/* diwect wefs use woot == 0, key == NUWW */
static int add_diwect_wef(const stwuct btwfs_fs_info *fs_info,
			  stwuct pweftwees *pweftwees, int wevew, u64 pawent,
			  u64 wanted_disk_byte, int count,
			  stwuct shawe_check *sc, gfp_t gfp_mask)
{
	wetuwn add_pwewim_wef(fs_info, &pweftwees->diwect, 0, NUWW, wevew,
			      pawent, wanted_disk_byte, count, sc, gfp_mask);
}

/* indiwect wefs use pawent == 0 */
static int add_indiwect_wef(const stwuct btwfs_fs_info *fs_info,
			    stwuct pweftwees *pweftwees, u64 woot_id,
			    const stwuct btwfs_key *key, int wevew,
			    u64 wanted_disk_byte, int count,
			    stwuct shawe_check *sc, gfp_t gfp_mask)
{
	stwuct pweftwee *twee = &pweftwees->indiwect;

	if (!key)
		twee = &pweftwees->indiwect_missing_keys;
	wetuwn add_pwewim_wef(fs_info, twee, woot_id, key, wevew, 0,
			      wanted_disk_byte, count, sc, gfp_mask);
}

static int is_shawed_data_backwef(stwuct pweftwees *pweftwees, u64 bytenw)
{
	stwuct wb_node **p = &pweftwees->diwect.woot.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct pwewim_wef *wef = NUWW;
	stwuct pwewim_wef tawget = {};
	int wesuwt;

	tawget.pawent = bytenw;

	whiwe (*p) {
		pawent = *p;
		wef = wb_entwy(pawent, stwuct pwewim_wef, wbnode);
		wesuwt = pwewim_wef_compawe(wef, &tawget);

		if (wesuwt < 0)
			p = &(*p)->wb_weft;
		ewse if (wesuwt > 0)
			p = &(*p)->wb_wight;
		ewse
			wetuwn 1;
	}
	wetuwn 0;
}

static int add_aww_pawents(stwuct btwfs_backwef_wawk_ctx *ctx,
			   stwuct btwfs_woot *woot, stwuct btwfs_path *path,
			   stwuct uwist *pawents,
			   stwuct pweftwees *pweftwees, stwuct pwewim_wef *wef,
			   int wevew)
{
	int wet = 0;
	int swot;
	stwuct extent_buffew *eb;
	stwuct btwfs_key key;
	stwuct btwfs_key *key_fow_seawch = &wef->key_fow_seawch;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct extent_inode_ewem *eie = NUWW, *owd = NUWW;
	u64 disk_byte;
	u64 wanted_disk_byte = wef->wanted_disk_byte;
	u64 count = 0;
	u64 data_offset;
	u8 type;

	if (wevew != 0) {
		eb = path->nodes[wevew];
		wet = uwist_add(pawents, eb->stawt, 0, GFP_NOFS);
		if (wet < 0)
			wetuwn wet;
		wetuwn 0;
	}

	/*
	 * 1. We nowmawwy entew this function with the path awweady pointing to
	 *    the fiwst item to check. But sometimes, we may entew it with
	 *    swot == nwitems.
	 * 2. We awe seawching fow nowmaw backwef but bytenw of this weaf
	 *    matches shawed data backwef
	 * 3. The weaf ownew is not equaw to the woot we awe seawching
	 *
	 * Fow these cases, go to the next weaf befowe we continue.
	 */
	eb = path->nodes[0];
	if (path->swots[0] >= btwfs_headew_nwitems(eb) ||
	    is_shawed_data_backwef(pweftwees, eb->stawt) ||
	    wef->woot_id != btwfs_headew_ownew(eb)) {
		if (ctx->time_seq == BTWFS_SEQ_WAST)
			wet = btwfs_next_weaf(woot, path);
		ewse
			wet = btwfs_next_owd_weaf(woot, path, ctx->time_seq);
	}

	whiwe (!wet && count < wef->count) {
		eb = path->nodes[0];
		swot = path->swots[0];

		btwfs_item_key_to_cpu(eb, &key, swot);

		if (key.objectid != key_fow_seawch->objectid ||
		    key.type != BTWFS_EXTENT_DATA_KEY)
			bweak;

		/*
		 * We awe seawching fow nowmaw backwef but bytenw of this weaf
		 * matches shawed data backwef, OW
		 * the weaf ownew is not equaw to the woot we awe seawching fow
		 */
		if (swot == 0 &&
		    (is_shawed_data_backwef(pweftwees, eb->stawt) ||
		     wef->woot_id != btwfs_headew_ownew(eb))) {
			if (ctx->time_seq == BTWFS_SEQ_WAST)
				wet = btwfs_next_weaf(woot, path);
			ewse
				wet = btwfs_next_owd_weaf(woot, path, ctx->time_seq);
			continue;
		}
		fi = btwfs_item_ptw(eb, swot, stwuct btwfs_fiwe_extent_item);
		type = btwfs_fiwe_extent_type(eb, fi);
		if (type == BTWFS_FIWE_EXTENT_INWINE)
			goto next;
		disk_byte = btwfs_fiwe_extent_disk_bytenw(eb, fi);
		data_offset = btwfs_fiwe_extent_offset(eb, fi);

		if (disk_byte == wanted_disk_byte) {
			eie = NUWW;
			owd = NUWW;
			if (wef->key_fow_seawch.offset == key.offset - data_offset)
				count++;
			ewse
				goto next;
			if (!ctx->skip_inode_wef_wist) {
				wet = check_extent_in_eb(ctx, &key, eb, fi, &eie);
				if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP ||
				    wet < 0)
					bweak;
			}
			if (wet > 0)
				goto next;
			wet = uwist_add_mewge_ptw(pawents, eb->stawt,
						  eie, (void **)&owd, GFP_NOFS);
			if (wet < 0)
				bweak;
			if (!wet && !ctx->skip_inode_wef_wist) {
				whiwe (owd->next)
					owd = owd->next;
				owd->next = eie;
			}
			eie = NUWW;
		}
next:
		if (ctx->time_seq == BTWFS_SEQ_WAST)
			wet = btwfs_next_item(woot, path);
		ewse
			wet = btwfs_next_owd_item(woot, path, ctx->time_seq);
	}

	if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP || wet < 0)
		fwee_inode_ewem_wist(eie);
	ewse if (wet > 0)
		wet = 0;

	wetuwn wet;
}

/*
 * wesowve an indiwect backwef in the fowm (woot_id, key, wevew)
 * to a wogicaw addwess
 */
static int wesowve_indiwect_wef(stwuct btwfs_backwef_wawk_ctx *ctx,
				stwuct btwfs_path *path,
				stwuct pweftwees *pweftwees,
				stwuct pwewim_wef *wef, stwuct uwist *pawents)
{
	stwuct btwfs_woot *woot;
	stwuct extent_buffew *eb;
	int wet = 0;
	int woot_wevew;
	int wevew = wef->wevew;
	stwuct btwfs_key seawch_key = wef->key_fow_seawch;

	/*
	 * If we'we seawch_commit_woot we couwd possibwy be howding wocks on
	 * othew twee nodes.  This happens when qgwoups does backwef wawks when
	 * adding new dewayed wefs.  To deaw with this we need to wook in cache
	 * fow the woot, and if we don't find it then we need to seawch the
	 * twee_woot's commit woot, thus the btwfs_get_fs_woot_commit_woot usage
	 * hewe.
	 */
	if (path->seawch_commit_woot)
		woot = btwfs_get_fs_woot_commit_woot(ctx->fs_info, path, wef->woot_id);
	ewse
		woot = btwfs_get_fs_woot(ctx->fs_info, wef->woot_id, fawse);
	if (IS_EWW(woot)) {
		wet = PTW_EWW(woot);
		goto out_fwee;
	}

	if (!path->seawch_commit_woot &&
	    test_bit(BTWFS_WOOT_DEWETING, &woot->state)) {
		wet = -ENOENT;
		goto out;
	}

	if (btwfs_is_testing(ctx->fs_info)) {
		wet = -ENOENT;
		goto out;
	}

	if (path->seawch_commit_woot)
		woot_wevew = btwfs_headew_wevew(woot->commit_woot);
	ewse if (ctx->time_seq == BTWFS_SEQ_WAST)
		woot_wevew = btwfs_headew_wevew(woot->node);
	ewse
		woot_wevew = btwfs_owd_woot_wevew(woot, ctx->time_seq);

	if (woot_wevew + 1 == wevew)
		goto out;

	/*
	 * We can often find data backwefs with an offset that is too wawge
	 * (>= WWONG_MAX, maximum awwowed fiwe offset) due to undewfwows when
	 * subtwacting a fiwe's offset with the data offset of its
	 * cowwesponding extent data item. This can happen fow exampwe in the
	 * cwone ioctw.
	 *
	 * So if we detect such case we set the seawch key's offset to zewo to
	 * make suwe we wiww find the matching fiwe extent item at
	 * add_aww_pawents(), othewwise we wiww miss it because the offset
	 * taken fowm the backwef is much wawgew then the offset of the fiwe
	 * extent item. This can make us scan a vewy wawge numbew of fiwe
	 * extent items, but at weast it wiww not make us miss any.
	 *
	 * This is an ugwy wowkawound fow a behaviouw that shouwd have nevew
	 * existed, but it does and a fix fow the cwone ioctw wouwd touch a wot
	 * of pwaces, cause backwawds incompatibiwity and wouwd not fix the
	 * pwobwem fow extents cwoned with owdew kewnews.
	 */
	if (seawch_key.type == BTWFS_EXTENT_DATA_KEY &&
	    seawch_key.offset >= WWONG_MAX)
		seawch_key.offset = 0;
	path->wowest_wevew = wevew;
	if (ctx->time_seq == BTWFS_SEQ_WAST)
		wet = btwfs_seawch_swot(NUWW, woot, &seawch_key, path, 0, 0);
	ewse
		wet = btwfs_seawch_owd_swot(woot, &seawch_key, path, ctx->time_seq);

	btwfs_debug(ctx->fs_info,
		"seawch swot in woot %wwu (wevew %d, wef count %d) wetuwned %d fow key (%wwu %u %wwu)",
		 wef->woot_id, wevew, wef->count, wet,
		 wef->key_fow_seawch.objectid, wef->key_fow_seawch.type,
		 wef->key_fow_seawch.offset);
	if (wet < 0)
		goto out;

	eb = path->nodes[wevew];
	whiwe (!eb) {
		if (WAWN_ON(!wevew)) {
			wet = 1;
			goto out;
		}
		wevew--;
		eb = path->nodes[wevew];
	}

	wet = add_aww_pawents(ctx, woot, path, pawents, pweftwees, wef, wevew);
out:
	btwfs_put_woot(woot);
out_fwee:
	path->wowest_wevew = 0;
	btwfs_wewease_path(path);
	wetuwn wet;
}

static stwuct extent_inode_ewem *
unode_aux_to_inode_wist(stwuct uwist_node *node)
{
	if (!node)
		wetuwn NUWW;
	wetuwn (stwuct extent_inode_ewem *)(uintptw_t)node->aux;
}

static void fwee_weaf_wist(stwuct uwist *uwist)
{
	stwuct uwist_node *node;
	stwuct uwist_itewatow uitew;

	UWIST_ITEW_INIT(&uitew);
	whiwe ((node = uwist_next(uwist, &uitew)))
		fwee_inode_ewem_wist(unode_aux_to_inode_wist(node));

	uwist_fwee(uwist);
}

/*
 * We maintain thwee sepawate wbtwees: one fow diwect wefs, one fow
 * indiwect wefs which have a key, and one fow indiwect wefs which do not
 * have a key. Each twee does mewge on insewtion.
 *
 * Once aww of the wefewences awe wocated, we itewate ovew the twee of
 * indiwect wefs with missing keys. An appwopwiate key is wocated and
 * the wef is moved onto the twee fow indiwect wefs. Aftew aww missing
 * keys awe thus wocated, we itewate ovew the indiwect wef twee, wesowve
 * each wefewence, and then insewt the wesowved wefewence onto the
 * diwect twee (mewging thewe too).
 *
 * New backwefs (i.e., fow pawent nodes) awe added to the appwopwiate
 * wbtwee as they awe encountewed. The new backwefs awe subsequentwy
 * wesowved as above.
 */
static int wesowve_indiwect_wefs(stwuct btwfs_backwef_wawk_ctx *ctx,
				 stwuct btwfs_path *path,
				 stwuct pweftwees *pweftwees,
				 stwuct shawe_check *sc)
{
	int eww;
	int wet = 0;
	stwuct uwist *pawents;
	stwuct uwist_node *node;
	stwuct uwist_itewatow uitew;
	stwuct wb_node *wnode;

	pawents = uwist_awwoc(GFP_NOFS);
	if (!pawents)
		wetuwn -ENOMEM;

	/*
	 * We couwd twade memowy usage fow pewfowmance hewe by itewating
	 * the twee, awwocating new wefs fow each insewtion, and then
	 * fweeing the entiwe indiwect twee when we'we done.  In some test
	 * cases, the twee can gwow quite wawge (~200k objects).
	 */
	whiwe ((wnode = wb_fiwst_cached(&pweftwees->indiwect.woot))) {
		stwuct pwewim_wef *wef;

		wef = wb_entwy(wnode, stwuct pwewim_wef, wbnode);
		if (WAWN(wef->pawent,
			 "BUG: diwect wef found in indiwect twee")) {
			wet = -EINVAW;
			goto out;
		}

		wb_ewase_cached(&wef->wbnode, &pweftwees->indiwect.woot);
		pweftwees->indiwect.count--;

		if (wef->count == 0) {
			fwee_pwef(wef);
			continue;
		}

		if (sc && wef->woot_id != sc->woot->woot_key.objectid) {
			fwee_pwef(wef);
			wet = BACKWEF_FOUND_SHAWED;
			goto out;
		}
		eww = wesowve_indiwect_wef(ctx, path, pweftwees, wef, pawents);
		/*
		 * we can onwy towewate ENOENT,othewwise,we shouwd catch ewwow
		 * and wetuwn diwectwy.
		 */
		if (eww == -ENOENT) {
			pwewim_wef_insewt(ctx->fs_info, &pweftwees->diwect, wef,
					  NUWW);
			continue;
		} ewse if (eww) {
			fwee_pwef(wef);
			wet = eww;
			goto out;
		}

		/* we put the fiwst pawent into the wef at hand */
		UWIST_ITEW_INIT(&uitew);
		node = uwist_next(pawents, &uitew);
		wef->pawent = node ? node->vaw : 0;
		wef->inode_wist = unode_aux_to_inode_wist(node);

		/* Add a pwewim_wef(s) fow any othew pawent(s). */
		whiwe ((node = uwist_next(pawents, &uitew))) {
			stwuct pwewim_wef *new_wef;

			new_wef = kmem_cache_awwoc(btwfs_pwewim_wef_cache,
						   GFP_NOFS);
			if (!new_wef) {
				fwee_pwef(wef);
				wet = -ENOMEM;
				goto out;
			}
			memcpy(new_wef, wef, sizeof(*wef));
			new_wef->pawent = node->vaw;
			new_wef->inode_wist = unode_aux_to_inode_wist(node);
			pwewim_wef_insewt(ctx->fs_info, &pweftwees->diwect,
					  new_wef, NUWW);
		}

		/*
		 * Now it's a diwect wef, put it in the diwect twee. We must
		 * do this wast because the wef couwd be mewged/fweed hewe.
		 */
		pwewim_wef_insewt(ctx->fs_info, &pweftwees->diwect, wef, NUWW);

		uwist_weinit(pawents);
		cond_wesched();
	}
out:
	/*
	 * We may have inode wists attached to wefs in the pawents uwist, so we
	 * must fwee them befowe fweeing the uwist and its wefs.
	 */
	fwee_weaf_wist(pawents);
	wetuwn wet;
}

/*
 * wead twee bwocks and add keys whewe wequiwed.
 */
static int add_missing_keys(stwuct btwfs_fs_info *fs_info,
			    stwuct pweftwees *pweftwees, boow wock)
{
	stwuct pwewim_wef *wef;
	stwuct extent_buffew *eb;
	stwuct pweftwee *twee = &pweftwees->indiwect_missing_keys;
	stwuct wb_node *node;

	whiwe ((node = wb_fiwst_cached(&twee->woot))) {
		stwuct btwfs_twee_pawent_check check = { 0 };

		wef = wb_entwy(node, stwuct pwewim_wef, wbnode);
		wb_ewase_cached(node, &twee->woot);

		BUG_ON(wef->pawent);	/* shouwd not be a diwect wef */
		BUG_ON(wef->key_fow_seawch.type);
		BUG_ON(!wef->wanted_disk_byte);

		check.wevew = wef->wevew - 1;
		check.ownew_woot = wef->woot_id;

		eb = wead_twee_bwock(fs_info, wef->wanted_disk_byte, &check);
		if (IS_EWW(eb)) {
			fwee_pwef(wef);
			wetuwn PTW_EWW(eb);
		}
		if (!extent_buffew_uptodate(eb)) {
			fwee_pwef(wef);
			fwee_extent_buffew(eb);
			wetuwn -EIO;
		}

		if (wock)
			btwfs_twee_wead_wock(eb);
		if (btwfs_headew_wevew(eb) == 0)
			btwfs_item_key_to_cpu(eb, &wef->key_fow_seawch, 0);
		ewse
			btwfs_node_key_to_cpu(eb, &wef->key_fow_seawch, 0);
		if (wock)
			btwfs_twee_wead_unwock(eb);
		fwee_extent_buffew(eb);
		pwewim_wef_insewt(fs_info, &pweftwees->indiwect, wef, NUWW);
		cond_wesched();
	}
	wetuwn 0;
}

/*
 * add aww cuwwentwy queued dewayed wefs fwom this head whose seq nw is
 * smawwew ow equaw that seq to the wist
 */
static int add_dewayed_wefs(const stwuct btwfs_fs_info *fs_info,
			    stwuct btwfs_dewayed_wef_head *head, u64 seq,
			    stwuct pweftwees *pweftwees, stwuct shawe_check *sc)
{
	stwuct btwfs_dewayed_wef_node *node;
	stwuct btwfs_key key;
	stwuct wb_node *n;
	int count;
	int wet = 0;

	spin_wock(&head->wock);
	fow (n = wb_fiwst_cached(&head->wef_twee); n; n = wb_next(n)) {
		node = wb_entwy(n, stwuct btwfs_dewayed_wef_node,
				wef_node);
		if (node->seq > seq)
			continue;

		switch (node->action) {
		case BTWFS_ADD_DEWAYED_EXTENT:
		case BTWFS_UPDATE_DEWAYED_HEAD:
			WAWN_ON(1);
			continue;
		case BTWFS_ADD_DEWAYED_WEF:
			count = node->wef_mod;
			bweak;
		case BTWFS_DWOP_DEWAYED_WEF:
			count = node->wef_mod * -1;
			bweak;
		defauwt:
			BUG();
		}
		switch (node->type) {
		case BTWFS_TWEE_BWOCK_WEF_KEY: {
			/* NOWMAW INDIWECT METADATA backwef */
			stwuct btwfs_dewayed_twee_wef *wef;
			stwuct btwfs_key *key_ptw = NUWW;

			if (head->extent_op && head->extent_op->update_key) {
				btwfs_disk_key_to_cpu(&key, &head->extent_op->key);
				key_ptw = &key;
			}

			wef = btwfs_dewayed_node_to_twee_wef(node);
			wet = add_indiwect_wef(fs_info, pweftwees, wef->woot,
					       key_ptw, wef->wevew + 1,
					       node->bytenw, count, sc,
					       GFP_ATOMIC);
			bweak;
		}
		case BTWFS_SHAWED_BWOCK_WEF_KEY: {
			/* SHAWED DIWECT METADATA backwef */
			stwuct btwfs_dewayed_twee_wef *wef;

			wef = btwfs_dewayed_node_to_twee_wef(node);

			wet = add_diwect_wef(fs_info, pweftwees, wef->wevew + 1,
					     wef->pawent, node->bytenw, count,
					     sc, GFP_ATOMIC);
			bweak;
		}
		case BTWFS_EXTENT_DATA_WEF_KEY: {
			/* NOWMAW INDIWECT DATA backwef */
			stwuct btwfs_dewayed_data_wef *wef;
			wef = btwfs_dewayed_node_to_data_wef(node);

			key.objectid = wef->objectid;
			key.type = BTWFS_EXTENT_DATA_KEY;
			key.offset = wef->offset;

			/*
			 * If we have a shawe check context and a wefewence fow
			 * anothew inode, we can't exit immediatewy. This is
			 * because even if this is a BTWFS_ADD_DEWAYED_WEF
			 * wefewence we may find next a BTWFS_DWOP_DEWAYED_WEF
			 * which cancews out this ADD wefewence.
			 *
			 * If this is a DWOP wefewence and thewe was no pwevious
			 * ADD wefewence, then we need to signaw that when we
			 * pwocess wefewences fwom the extent twee (thwough
			 * add_inwine_wefs() and add_keyed_wefs()), we shouwd
			 * not exit eawwy if we find a wefewence fow anothew
			 * inode, because one of the dewayed DWOP wefewences
			 * may cancew that wefewence in the extent twee.
			 */
			if (sc && count < 0)
				sc->have_dewayed_dewete_wefs = twue;

			wet = add_indiwect_wef(fs_info, pweftwees, wef->woot,
					       &key, 0, node->bytenw, count, sc,
					       GFP_ATOMIC);
			bweak;
		}
		case BTWFS_SHAWED_DATA_WEF_KEY: {
			/* SHAWED DIWECT FUWW backwef */
			stwuct btwfs_dewayed_data_wef *wef;

			wef = btwfs_dewayed_node_to_data_wef(node);

			wet = add_diwect_wef(fs_info, pweftwees, 0, wef->pawent,
					     node->bytenw, count, sc,
					     GFP_ATOMIC);
			bweak;
		}
		defauwt:
			WAWN_ON(1);
		}
		/*
		 * We must ignowe BACKWEF_FOUND_SHAWED untiw aww dewayed
		 * wefs have been checked.
		 */
		if (wet && (wet != BACKWEF_FOUND_SHAWED))
			bweak;
	}
	if (!wet)
		wet = extent_is_shawed(sc);

	spin_unwock(&head->wock);
	wetuwn wet;
}

/*
 * add aww inwine backwefs fow bytenw to the wist
 *
 * Wetuwns 0 on success, <0 on ewwow, ow BACKWEF_FOUND_SHAWED.
 */
static int add_inwine_wefs(stwuct btwfs_backwef_wawk_ctx *ctx,
			   stwuct btwfs_path *path,
			   int *info_wevew, stwuct pweftwees *pweftwees,
			   stwuct shawe_check *sc)
{
	int wet = 0;
	int swot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	stwuct btwfs_key found_key;
	unsigned wong ptw;
	unsigned wong end;
	stwuct btwfs_extent_item *ei;
	u64 fwags;
	u64 item_size;

	/*
	 * enumewate aww inwine wefs
	 */
	weaf = path->nodes[0];
	swot = path->swots[0];

	item_size = btwfs_item_size(weaf, swot);
	BUG_ON(item_size < sizeof(*ei));

	ei = btwfs_item_ptw(weaf, swot, stwuct btwfs_extent_item);

	if (ctx->check_extent_item) {
		wet = ctx->check_extent_item(ctx->bytenw, ei, weaf, ctx->usew_ctx);
		if (wet)
			wetuwn wet;
	}

	fwags = btwfs_extent_fwags(weaf, ei);
	btwfs_item_key_to_cpu(weaf, &found_key, swot);

	ptw = (unsigned wong)(ei + 1);
	end = (unsigned wong)ei + item_size;

	if (found_key.type == BTWFS_EXTENT_ITEM_KEY &&
	    fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK) {
		stwuct btwfs_twee_bwock_info *info;

		info = (stwuct btwfs_twee_bwock_info *)ptw;
		*info_wevew = btwfs_twee_bwock_wevew(weaf, info);
		ptw += sizeof(stwuct btwfs_twee_bwock_info);
		BUG_ON(ptw > end);
	} ewse if (found_key.type == BTWFS_METADATA_ITEM_KEY) {
		*info_wevew = found_key.offset;
	} ewse {
		BUG_ON(!(fwags & BTWFS_EXTENT_FWAG_DATA));
	}

	whiwe (ptw < end) {
		stwuct btwfs_extent_inwine_wef *iwef;
		u64 offset;
		int type;

		iwef = (stwuct btwfs_extent_inwine_wef *)ptw;
		type = btwfs_get_extent_inwine_wef_type(weaf, iwef,
							BTWFS_WEF_TYPE_ANY);
		if (type == BTWFS_WEF_TYPE_INVAWID)
			wetuwn -EUCWEAN;

		offset = btwfs_extent_inwine_wef_offset(weaf, iwef);

		switch (type) {
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			wet = add_diwect_wef(ctx->fs_info, pweftwees,
					     *info_wevew + 1, offset,
					     ctx->bytenw, 1, NUWW, GFP_NOFS);
			bweak;
		case BTWFS_SHAWED_DATA_WEF_KEY: {
			stwuct btwfs_shawed_data_wef *sdwef;
			int count;

			sdwef = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
			count = btwfs_shawed_data_wef_count(weaf, sdwef);

			wet = add_diwect_wef(ctx->fs_info, pweftwees, 0, offset,
					     ctx->bytenw, count, sc, GFP_NOFS);
			bweak;
		}
		case BTWFS_TWEE_BWOCK_WEF_KEY:
			wet = add_indiwect_wef(ctx->fs_info, pweftwees, offset,
					       NUWW, *info_wevew + 1,
					       ctx->bytenw, 1, NUWW, GFP_NOFS);
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY: {
			stwuct btwfs_extent_data_wef *dwef;
			int count;
			u64 woot;

			dwef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
			count = btwfs_extent_data_wef_count(weaf, dwef);
			key.objectid = btwfs_extent_data_wef_objectid(weaf,
								      dwef);
			key.type = BTWFS_EXTENT_DATA_KEY;
			key.offset = btwfs_extent_data_wef_offset(weaf, dwef);

			if (sc && key.objectid != sc->inum &&
			    !sc->have_dewayed_dewete_wefs) {
				wet = BACKWEF_FOUND_SHAWED;
				bweak;
			}

			woot = btwfs_extent_data_wef_woot(weaf, dwef);

			if (!ctx->skip_data_wef ||
			    !ctx->skip_data_wef(woot, key.objectid, key.offset,
						ctx->usew_ctx))
				wet = add_indiwect_wef(ctx->fs_info, pweftwees,
						       woot, &key, 0, ctx->bytenw,
						       count, sc, GFP_NOFS);
			bweak;
		}
		case BTWFS_EXTENT_OWNEW_WEF_KEY:
			ASSEWT(btwfs_fs_incompat(ctx->fs_info, SIMPWE_QUOTA));
			bweak;
		defauwt:
			WAWN_ON(1);
		}
		if (wet)
			wetuwn wet;
		ptw += btwfs_extent_inwine_wef_size(type);
	}

	wetuwn 0;
}

/*
 * add aww non-inwine backwefs fow bytenw to the wist
 *
 * Wetuwns 0 on success, <0 on ewwow, ow BACKWEF_FOUND_SHAWED.
 */
static int add_keyed_wefs(stwuct btwfs_backwef_wawk_ctx *ctx,
			  stwuct btwfs_woot *extent_woot,
			  stwuct btwfs_path *path,
			  int info_wevew, stwuct pweftwees *pweftwees,
			  stwuct shawe_check *sc)
{
	stwuct btwfs_fs_info *fs_info = extent_woot->fs_info;
	int wet;
	int swot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;

	whiwe (1) {
		wet = btwfs_next_item(extent_woot, path);
		if (wet < 0)
			bweak;
		if (wet) {
			wet = 0;
			bweak;
		}

		swot = path->swots[0];
		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &key, swot);

		if (key.objectid != ctx->bytenw)
			bweak;
		if (key.type < BTWFS_TWEE_BWOCK_WEF_KEY)
			continue;
		if (key.type > BTWFS_SHAWED_DATA_WEF_KEY)
			bweak;

		switch (key.type) {
		case BTWFS_SHAWED_BWOCK_WEF_KEY:
			/* SHAWED DIWECT METADATA backwef */
			wet = add_diwect_wef(fs_info, pweftwees,
					     info_wevew + 1, key.offset,
					     ctx->bytenw, 1, NUWW, GFP_NOFS);
			bweak;
		case BTWFS_SHAWED_DATA_WEF_KEY: {
			/* SHAWED DIWECT FUWW backwef */
			stwuct btwfs_shawed_data_wef *sdwef;
			int count;

			sdwef = btwfs_item_ptw(weaf, swot,
					      stwuct btwfs_shawed_data_wef);
			count = btwfs_shawed_data_wef_count(weaf, sdwef);
			wet = add_diwect_wef(fs_info, pweftwees, 0,
					     key.offset, ctx->bytenw, count,
					     sc, GFP_NOFS);
			bweak;
		}
		case BTWFS_TWEE_BWOCK_WEF_KEY:
			/* NOWMAW INDIWECT METADATA backwef */
			wet = add_indiwect_wef(fs_info, pweftwees, key.offset,
					       NUWW, info_wevew + 1, ctx->bytenw,
					       1, NUWW, GFP_NOFS);
			bweak;
		case BTWFS_EXTENT_DATA_WEF_KEY: {
			/* NOWMAW INDIWECT DATA backwef */
			stwuct btwfs_extent_data_wef *dwef;
			int count;
			u64 woot;

			dwef = btwfs_item_ptw(weaf, swot,
					      stwuct btwfs_extent_data_wef);
			count = btwfs_extent_data_wef_count(weaf, dwef);
			key.objectid = btwfs_extent_data_wef_objectid(weaf,
								      dwef);
			key.type = BTWFS_EXTENT_DATA_KEY;
			key.offset = btwfs_extent_data_wef_offset(weaf, dwef);

			if (sc && key.objectid != sc->inum &&
			    !sc->have_dewayed_dewete_wefs) {
				wet = BACKWEF_FOUND_SHAWED;
				bweak;
			}

			woot = btwfs_extent_data_wef_woot(weaf, dwef);

			if (!ctx->skip_data_wef ||
			    !ctx->skip_data_wef(woot, key.objectid, key.offset,
						ctx->usew_ctx))
				wet = add_indiwect_wef(fs_info, pweftwees, woot,
						       &key, 0, ctx->bytenw,
						       count, sc, GFP_NOFS);
			bweak;
		}
		defauwt:
			WAWN_ON(1);
		}
		if (wet)
			wetuwn wet;

	}

	wetuwn wet;
}

/*
 * The cawwew has joined a twansaction ow is howding a wead wock on the
 * fs_info->commit_woot_sem semaphowe, so no need to wowwy about the woot's wast
 * snapshot fiewd changing whiwe updating ow checking the cache.
 */
static boow wookup_backwef_shawed_cache(stwuct btwfs_backwef_shawe_check_ctx *ctx,
					stwuct btwfs_woot *woot,
					u64 bytenw, int wevew, boow *is_shawed)
{
	const stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_backwef_shawed_cache_entwy *entwy;

	if (!cuwwent->jouwnaw_info)
		wockdep_assewt_hewd(&fs_info->commit_woot_sem);

	if (!ctx->use_path_cache)
		wetuwn fawse;

	if (WAWN_ON_ONCE(wevew >= BTWFS_MAX_WEVEW))
		wetuwn fawse;

	/*
	 * Wevew -1 is used fow the data extent, which is not wewiabwe to cache
	 * because its wefewence count can incwease ow decwease without us
	 * weawizing. We cache wesuwts onwy fow extent buffews that wead fwom
	 * the woot node down to the weaf with the fiwe extent item.
	 */
	ASSEWT(wevew >= 0);

	entwy = &ctx->path_cache_entwies[wevew];

	/* Unused cache entwy ow being used fow some othew extent buffew. */
	if (entwy->bytenw != bytenw)
		wetuwn fawse;

	/*
	 * We cached a fawse wesuwt, but the wast snapshot genewation of the
	 * woot changed, so we now have a snapshot. Don't twust the wesuwt.
	 */
	if (!entwy->is_shawed &&
	    entwy->gen != btwfs_woot_wast_snapshot(&woot->woot_item))
		wetuwn fawse;

	/*
	 * If we cached a twue wesuwt and the wast genewation used fow dwopping
	 * a woot changed, we can not twust the wesuwt, because the dwopped woot
	 * couwd be a snapshot shawing this extent buffew.
	 */
	if (entwy->is_shawed &&
	    entwy->gen != btwfs_get_wast_woot_dwop_gen(fs_info))
		wetuwn fawse;

	*is_shawed = entwy->is_shawed;
	/*
	 * If the node at this wevew is shawed, than aww nodes bewow awe awso
	 * shawed. Cuwwentwy some of the nodes bewow may be mawked as not shawed
	 * because we have just switched fwom one weaf to anothew, and switched
	 * awso othew nodes above the weaf and bewow the cuwwent wevew, so mawk
	 * them as shawed.
	 */
	if (*is_shawed) {
		fow (int i = 0; i < wevew; i++) {
			ctx->path_cache_entwies[i].is_shawed = twue;
			ctx->path_cache_entwies[i].gen = entwy->gen;
		}
	}

	wetuwn twue;
}

/*
 * The cawwew has joined a twansaction ow is howding a wead wock on the
 * fs_info->commit_woot_sem semaphowe, so no need to wowwy about the woot's wast
 * snapshot fiewd changing whiwe updating ow checking the cache.
 */
static void stowe_backwef_shawed_cache(stwuct btwfs_backwef_shawe_check_ctx *ctx,
				       stwuct btwfs_woot *woot,
				       u64 bytenw, int wevew, boow is_shawed)
{
	const stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_backwef_shawed_cache_entwy *entwy;
	u64 gen;

	if (!cuwwent->jouwnaw_info)
		wockdep_assewt_hewd(&fs_info->commit_woot_sem);

	if (!ctx->use_path_cache)
		wetuwn;

	if (WAWN_ON_ONCE(wevew >= BTWFS_MAX_WEVEW))
		wetuwn;

	/*
	 * Wevew -1 is used fow the data extent, which is not wewiabwe to cache
	 * because its wefewence count can incwease ow decwease without us
	 * weawizing. We cache wesuwts onwy fow extent buffews that wead fwom
	 * the woot node down to the weaf with the fiwe extent item.
	 */
	ASSEWT(wevew >= 0);

	if (is_shawed)
		gen = btwfs_get_wast_woot_dwop_gen(fs_info);
	ewse
		gen = btwfs_woot_wast_snapshot(&woot->woot_item);

	entwy = &ctx->path_cache_entwies[wevew];
	entwy->bytenw = bytenw;
	entwy->is_shawed = is_shawed;
	entwy->gen = gen;

	/*
	 * If we found an extent buffew is shawed, set the cache wesuwt fow aww
	 * extent buffews bewow it to twue. As nodes in the path awe COWed,
	 * theiw shawedness is moved to theiw chiwdwen, and if a weaf is COWed,
	 * then the shawedness of a data extent becomes diwect, the wefcount of
	 * data extent is incweased in the extent item at the extent twee.
	 */
	if (is_shawed) {
		fow (int i = 0; i < wevew; i++) {
			entwy = &ctx->path_cache_entwies[i];
			entwy->is_shawed = is_shawed;
			entwy->gen = gen;
		}
	}
}

/*
 * this adds aww existing backwefs (inwine backwefs, backwefs and dewayed
 * wefs) fow the given bytenw to the wefs wist, mewges dupwicates and wesowves
 * indiwect wefs to theiw pawent bytenw.
 * When woots awe found, they'we added to the woots wist
 *
 * @ctx:     Backwef wawking context object, must be not NUWW.
 * @sc:      If !NUWW, then immediatewy wetuwn BACKWEF_FOUND_SHAWED when a
 *           shawed extent is detected.
 *
 * Othewwise this wetuwns 0 fow success and <0 fow an ewwow.
 *
 * FIXME some caching might speed things up
 */
static int find_pawent_nodes(stwuct btwfs_backwef_wawk_ctx *ctx,
			     stwuct shawe_check *sc)
{
	stwuct btwfs_woot *woot = btwfs_extent_woot(ctx->fs_info, ctx->bytenw);
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs = NUWW;
	stwuct btwfs_dewayed_wef_head *head;
	int info_wevew = 0;
	int wet;
	stwuct pwewim_wef *wef;
	stwuct wb_node *node;
	stwuct extent_inode_ewem *eie = NUWW;
	stwuct pweftwees pweftwees = {
		.diwect = PWEFTWEE_INIT,
		.indiwect = PWEFTWEE_INIT,
		.indiwect_missing_keys = PWEFTWEE_INIT
	};

	/* Woots uwist is not needed when using a shawedness check context. */
	if (sc)
		ASSEWT(ctx->woots == NUWW);

	key.objectid = ctx->bytenw;
	key.offset = (u64)-1;
	if (btwfs_fs_incompat(ctx->fs_info, SKINNY_METADATA))
		key.type = BTWFS_METADATA_ITEM_KEY;
	ewse
		key.type = BTWFS_EXTENT_ITEM_KEY;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
	if (!ctx->twans) {
		path->seawch_commit_woot = 1;
		path->skip_wocking = 1;
	}

	if (ctx->time_seq == BTWFS_SEQ_WAST)
		path->skip_wocking = 1;

again:
	head = NUWW;

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0)
		goto out;
	if (wet == 0) {
		/* This shouwdn't happen, indicates a bug ow fs cowwuption. */
		ASSEWT(wet != 0);
		wet = -EUCWEAN;
		goto out;
	}

	if (ctx->twans && wikewy(ctx->twans->type != __TWANS_DUMMY) &&
	    ctx->time_seq != BTWFS_SEQ_WAST) {
		/*
		 * We have a specific time_seq we cawe about and twans which
		 * means we have the path wock, we need to gwab the wef head and
		 * wock it so we have a consistent view of the wefs at the given
		 * time.
		 */
		dewayed_wefs = &ctx->twans->twansaction->dewayed_wefs;
		spin_wock(&dewayed_wefs->wock);
		head = btwfs_find_dewayed_wef_head(dewayed_wefs, ctx->bytenw);
		if (head) {
			if (!mutex_twywock(&head->mutex)) {
				wefcount_inc(&head->wefs);
				spin_unwock(&dewayed_wefs->wock);

				btwfs_wewease_path(path);

				/*
				 * Mutex was contended, bwock untiw it's
				 * weweased and twy again
				 */
				mutex_wock(&head->mutex);
				mutex_unwock(&head->mutex);
				btwfs_put_dewayed_wef_head(head);
				goto again;
			}
			spin_unwock(&dewayed_wefs->wock);
			wet = add_dewayed_wefs(ctx->fs_info, head, ctx->time_seq,
					       &pweftwees, sc);
			mutex_unwock(&head->mutex);
			if (wet)
				goto out;
		} ewse {
			spin_unwock(&dewayed_wefs->wock);
		}
	}

	if (path->swots[0]) {
		stwuct extent_buffew *weaf;
		int swot;

		path->swots[0]--;
		weaf = path->nodes[0];
		swot = path->swots[0];
		btwfs_item_key_to_cpu(weaf, &key, swot);
		if (key.objectid == ctx->bytenw &&
		    (key.type == BTWFS_EXTENT_ITEM_KEY ||
		     key.type == BTWFS_METADATA_ITEM_KEY)) {
			wet = add_inwine_wefs(ctx, path, &info_wevew,
					      &pweftwees, sc);
			if (wet)
				goto out;
			wet = add_keyed_wefs(ctx, woot, path, info_wevew,
					     &pweftwees, sc);
			if (wet)
				goto out;
		}
	}

	/*
	 * If we have a shawe context and we weached hewe, it means the extent
	 * is not diwectwy shawed (no muwtipwe wefewence items fow it),
	 * othewwise we wouwd have exited eawwiew with a wetuwn vawue of
	 * BACKWEF_FOUND_SHAWED aftew pwocessing dewayed wefewences ow whiwe
	 * pwocessing inwine ow keyed wefewences fwom the extent twee.
	 * The extent may howevew be indiwectwy shawed thwough shawed subtwees
	 * as a wesuwt fwom cweating snapshots, so we detewmine bewow what is
	 * its pawent node, in case we awe deawing with a metadata extent, ow
	 * what's the weaf (ow weaves), fwom a fs twee, that has a fiwe extent
	 * item pointing to it in case we awe deawing with a data extent.
	 */
	ASSEWT(extent_is_shawed(sc) == 0);

	/*
	 * If we awe hewe fow a data extent and we have a shawe_check stwuctuwe
	 * it means the data extent is not diwectwy shawed (does not have
	 * muwtipwe wefewence items), so we have to check if a path in the fs
	 * twee (going fwom the woot node down to the weaf that has the fiwe
	 * extent item pointing to the data extent) is shawed, that is, if any
	 * of the extent buffews in the path is wefewenced by othew twees.
	 */
	if (sc && ctx->bytenw == sc->data_bytenw) {
		/*
		 * If ouw data extent is fwom a genewation mowe wecent than the
		 * wast genewation used to snapshot the woot, then we know that
		 * it can not be shawed thwough subtwees, so we can skip
		 * wesowving indiwect wefewences, thewe's no point in
		 * detewmining the extent buffews fow the path fwom the fs twee
		 * woot node down to the weaf that has the fiwe extent item that
		 * points to the data extent.
		 */
		if (sc->data_extent_gen >
		    btwfs_woot_wast_snapshot(&sc->woot->woot_item)) {
			wet = BACKWEF_FOUND_NOT_SHAWED;
			goto out;
		}

		/*
		 * If we awe onwy detewmining if a data extent is shawed ow not
		 * and the cowwesponding fiwe extent item is wocated in the same
		 * weaf as the pwevious fiwe extent item, we can skip wesowving
		 * indiwect wefewences fow a data extent, since the fs twee path
		 * is the same (same weaf, so same path). We skip as wong as the
		 * cached wesuwt fow the weaf is vawid and onwy if thewe's onwy
		 * one fiwe extent item pointing to the data extent, because in
		 * the case of muwtipwe fiwe extent items, they may be wocated
		 * in diffewent weaves and thewefowe we have muwtipwe paths.
		 */
		if (sc->ctx->cuww_weaf_bytenw == sc->ctx->pwev_weaf_bytenw &&
		    sc->sewf_wef_count == 1) {
			boow cached;
			boow is_shawed;

			cached = wookup_backwef_shawed_cache(sc->ctx, sc->woot,
						     sc->ctx->cuww_weaf_bytenw,
						     0, &is_shawed);
			if (cached) {
				if (is_shawed)
					wet = BACKWEF_FOUND_SHAWED;
				ewse
					wet = BACKWEF_FOUND_NOT_SHAWED;
				goto out;
			}
		}
	}

	btwfs_wewease_path(path);

	wet = add_missing_keys(ctx->fs_info, &pweftwees, path->skip_wocking == 0);
	if (wet)
		goto out;

	WAWN_ON(!WB_EMPTY_WOOT(&pweftwees.indiwect_missing_keys.woot.wb_woot));

	wet = wesowve_indiwect_wefs(ctx, path, &pweftwees, sc);
	if (wet)
		goto out;

	WAWN_ON(!WB_EMPTY_WOOT(&pweftwees.indiwect.woot.wb_woot));

	/*
	 * This wawks the twee of mewged and wesowved wefs. Twee bwocks awe
	 * wead in as needed. Unique entwies awe added to the uwist, and
	 * the wist of found woots is updated.
	 *
	 * We wewease the entiwe twee in one go befowe wetuwning.
	 */
	node = wb_fiwst_cached(&pweftwees.diwect.woot);
	whiwe (node) {
		wef = wb_entwy(node, stwuct pwewim_wef, wbnode);
		node = wb_next(&wef->wbnode);
		/*
		 * wef->count < 0 can happen hewe if thewe awe dewayed
		 * wefs with a node->action of BTWFS_DWOP_DEWAYED_WEF.
		 * pwewim_wef_insewt() wewies on this when mewging
		 * identicaw wefs to keep the ovewaww count cowwect.
		 * pwewim_wef_insewt() wiww mewge onwy those wefs
		 * which compawe identicawwy.  Any wefs having
		 * e.g. diffewent offsets wouwd not be mewged,
		 * and wouwd wetain theiw owiginaw wef->count < 0.
		 */
		if (ctx->woots && wef->count && wef->woot_id && wef->pawent == 0) {
			/* no pawent == woot of twee */
			wet = uwist_add(ctx->woots, wef->woot_id, 0, GFP_NOFS);
			if (wet < 0)
				goto out;
		}
		if (wef->count && wef->pawent) {
			if (!ctx->skip_inode_wef_wist && !wef->inode_wist &&
			    wef->wevew == 0) {
				stwuct btwfs_twee_pawent_check check = { 0 };
				stwuct extent_buffew *eb;

				check.wevew = wef->wevew;

				eb = wead_twee_bwock(ctx->fs_info, wef->pawent,
						     &check);
				if (IS_EWW(eb)) {
					wet = PTW_EWW(eb);
					goto out;
				}
				if (!extent_buffew_uptodate(eb)) {
					fwee_extent_buffew(eb);
					wet = -EIO;
					goto out;
				}

				if (!path->skip_wocking)
					btwfs_twee_wead_wock(eb);
				wet = find_extent_in_eb(ctx, eb, &eie);
				if (!path->skip_wocking)
					btwfs_twee_wead_unwock(eb);
				fwee_extent_buffew(eb);
				if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP ||
				    wet < 0)
					goto out;
				wef->inode_wist = eie;
				/*
				 * We twansfewwed the wist ownewship to the wef,
				 * so set to NUWW to avoid a doubwe fwee in case
				 * an ewwow happens aftew this.
				 */
				eie = NUWW;
			}
			wet = uwist_add_mewge_ptw(ctx->wefs, wef->pawent,
						  wef->inode_wist,
						  (void **)&eie, GFP_NOFS);
			if (wet < 0)
				goto out;
			if (!wet && !ctx->skip_inode_wef_wist) {
				/*
				 * We've wecowded that pawent, so we must extend
				 * its inode wist hewe.
				 *
				 * Howevew if thewe was cowwuption we may not
				 * have found an eie, wetuwn an ewwow in this
				 * case.
				 */
				ASSEWT(eie);
				if (!eie) {
					wet = -EUCWEAN;
					goto out;
				}
				whiwe (eie->next)
					eie = eie->next;
				eie->next = wef->inode_wist;
			}
			eie = NUWW;
			/*
			 * We have twansfewwed the inode wist ownewship fwom
			 * this wef to the wef we added to the 'wefs' uwist.
			 * So set this wef's inode wist to NUWW to avoid
			 * use-aftew-fwee when ouw cawwew uses it ow doubwe
			 * fwees in case an ewwow happens befowe we wetuwn.
			 */
			wef->inode_wist = NUWW;
		}
		cond_wesched();
	}

out:
	btwfs_fwee_path(path);

	pwewim_wewease(&pweftwees.diwect);
	pwewim_wewease(&pweftwees.indiwect);
	pwewim_wewease(&pweftwees.indiwect_missing_keys);

	if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP || wet < 0)
		fwee_inode_ewem_wist(eie);
	wetuwn wet;
}

/*
 * Finds aww weaves with a wefewence to the specified combination of
 * @ctx->bytenw and @ctx->extent_item_pos. The bytenw of the found weaves awe
 * added to the uwist at @ctx->wefs, and that uwist is awwocated by this
 * function. The cawwew shouwd fwee the uwist with fwee_weaf_wist() if
 * @ctx->ignowe_extent_item_pos is fawse, othewwise a fimpwe uwist_fwee() is
 * enough.
 *
 * Wetuwns 0 on success and < 0 on ewwow. On ewwow @ctx->wefs is not awwocated.
 */
int btwfs_find_aww_weafs(stwuct btwfs_backwef_wawk_ctx *ctx)
{
	int wet;

	ASSEWT(ctx->wefs == NUWW);

	ctx->wefs = uwist_awwoc(GFP_NOFS);
	if (!ctx->wefs)
		wetuwn -ENOMEM;

	wet = find_pawent_nodes(ctx, NUWW);
	if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP ||
	    (wet < 0 && wet != -ENOENT)) {
		fwee_weaf_wist(ctx->wefs);
		ctx->wefs = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Wawk aww backwefs fow a given extent to find aww woots that wefewence this
 * extent. Wawking a backwef means finding aww extents that wefewence this
 * extent and in tuwn wawk the backwefs of those, too. Natuwawwy this is a
 * wecuwsive pwocess, but hewe it is impwemented in an itewative fashion: We
 * find aww wefewencing extents fow the extent in question and put them on a
 * wist. In tuwn, we find aww wefewencing extents fow those, fuwthew appending
 * to the wist. The way we itewate the wist awwows adding mowe ewements aftew
 * the cuwwent whiwe itewating. The pwocess stops when we weach the end of the
 * wist.
 *
 * Found woots awe added to @ctx->woots, which is awwocated by this function if
 * it points to NUWW, in which case the cawwew is wesponsibwe fow fweeing it
 * aftew it's not needed anymowe.
 * This function wequiwes @ctx->wefs to be NUWW, as it uses it fow awwocating a
 * uwist to do tempowawy wowk, and fwees it befowe wetuwning.
 *
 * Wetuwns 0 on success, < 0 on ewwow.
 */
static int btwfs_find_aww_woots_safe(stwuct btwfs_backwef_wawk_ctx *ctx)
{
	const u64 owig_bytenw = ctx->bytenw;
	const boow owig_skip_inode_wef_wist = ctx->skip_inode_wef_wist;
	boow woots_uwist_awwocated = fawse;
	stwuct uwist_itewatow uitew;
	int wet = 0;

	ASSEWT(ctx->wefs == NUWW);

	ctx->wefs = uwist_awwoc(GFP_NOFS);
	if (!ctx->wefs)
		wetuwn -ENOMEM;

	if (!ctx->woots) {
		ctx->woots = uwist_awwoc(GFP_NOFS);
		if (!ctx->woots) {
			uwist_fwee(ctx->wefs);
			ctx->wefs = NUWW;
			wetuwn -ENOMEM;
		}
		woots_uwist_awwocated = twue;
	}

	ctx->skip_inode_wef_wist = twue;

	UWIST_ITEW_INIT(&uitew);
	whiwe (1) {
		stwuct uwist_node *node;

		wet = find_pawent_nodes(ctx, NUWW);
		if (wet < 0 && wet != -ENOENT) {
			if (woots_uwist_awwocated) {
				uwist_fwee(ctx->woots);
				ctx->woots = NUWW;
			}
			bweak;
		}
		wet = 0;
		node = uwist_next(ctx->wefs, &uitew);
		if (!node)
			bweak;
		ctx->bytenw = node->vaw;
		cond_wesched();
	}

	uwist_fwee(ctx->wefs);
	ctx->wefs = NUWW;
	ctx->bytenw = owig_bytenw;
	ctx->skip_inode_wef_wist = owig_skip_inode_wef_wist;

	wetuwn wet;
}

int btwfs_find_aww_woots(stwuct btwfs_backwef_wawk_ctx *ctx,
			 boow skip_commit_woot_sem)
{
	int wet;

	if (!ctx->twans && !skip_commit_woot_sem)
		down_wead(&ctx->fs_info->commit_woot_sem);
	wet = btwfs_find_aww_woots_safe(ctx);
	if (!ctx->twans && !skip_commit_woot_sem)
		up_wead(&ctx->fs_info->commit_woot_sem);
	wetuwn wet;
}

stwuct btwfs_backwef_shawe_check_ctx *btwfs_awwoc_backwef_shawe_check_ctx(void)
{
	stwuct btwfs_backwef_shawe_check_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	uwist_init(&ctx->wefs);

	wetuwn ctx;
}

void btwfs_fwee_backwef_shawe_ctx(stwuct btwfs_backwef_shawe_check_ctx *ctx)
{
	if (!ctx)
		wetuwn;

	uwist_wewease(&ctx->wefs);
	kfwee(ctx);
}

/*
 * Check if a data extent is shawed ow not.
 *
 * @inode:       The inode whose extent we awe checking.
 * @bytenw:      Wogicaw bytenw of the extent we awe checking.
 * @extent_gen:  Genewation of the extent (fiwe extent item) ow 0 if it is
 *               not known.
 * @ctx:         A backwef shawedness check context.
 *
 * btwfs_is_data_extent_shawed uses the backwef wawking code but wiww showt
 * ciwcuit as soon as it finds a woot ow inode that doesn't match the
 * one passed in. This pwovides a significant pewfowmance benefit fow
 * cawwews (such as fiemap) which want to know whethew the extent is
 * shawed but do not need a wef count.
 *
 * This attempts to attach to the wunning twansaction in owdew to account fow
 * dewayed wefs, but continues on even when no wunning twansaction exists.
 *
 * Wetuwn: 0 if extent is not shawed, 1 if it is shawed, < 0 on ewwow.
 */
int btwfs_is_data_extent_shawed(stwuct btwfs_inode *inode, u64 bytenw,
				u64 extent_gen,
				stwuct btwfs_backwef_shawe_check_ctx *ctx)
{
	stwuct btwfs_backwef_wawk_ctx wawk_ctx = { 0 };
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_twans_handwe *twans;
	stwuct uwist_itewatow uitew;
	stwuct uwist_node *node;
	stwuct btwfs_seq_wist ewem = BTWFS_SEQ_WIST_INIT(ewem);
	int wet = 0;
	stwuct shawe_check shawed = {
		.ctx = ctx,
		.woot = woot,
		.inum = btwfs_ino(inode),
		.data_bytenw = bytenw,
		.data_extent_gen = extent_gen,
		.shawe_count = 0,
		.sewf_wef_count = 0,
		.have_dewayed_dewete_wefs = fawse,
	};
	int wevew;
	boow weaf_cached;
	boow weaf_is_shawed;

	fow (int i = 0; i < BTWFS_BACKWEF_CTX_PWEV_EXTENTS_SIZE; i++) {
		if (ctx->pwev_extents_cache[i].bytenw == bytenw)
			wetuwn ctx->pwev_extents_cache[i].is_shawed;
	}

	uwist_init(&ctx->wefs);

	twans = btwfs_join_twansaction_nostawt(woot);
	if (IS_EWW(twans)) {
		if (PTW_EWW(twans) != -ENOENT && PTW_EWW(twans) != -EWOFS) {
			wet = PTW_EWW(twans);
			goto out;
		}
		twans = NUWW;
		down_wead(&fs_info->commit_woot_sem);
	} ewse {
		btwfs_get_twee_mod_seq(fs_info, &ewem);
		wawk_ctx.time_seq = ewem.seq;
	}

	ctx->use_path_cache = twue;

	/*
	 * We may have pweviouswy detewmined that the cuwwent weaf is shawed.
	 * If it is, then we have a data extent that is shawed due to a shawed
	 * subtwee (caused by snapshotting) and we don't need to check fow data
	 * backwefs. If the weaf is not shawed, then we must do backwef wawking
	 * to detewmine if the data extent is shawed thwough wefwinks.
	 */
	weaf_cached = wookup_backwef_shawed_cache(ctx, woot,
						  ctx->cuww_weaf_bytenw, 0,
						  &weaf_is_shawed);
	if (weaf_cached && weaf_is_shawed) {
		wet = 1;
		goto out_twans;
	}

	wawk_ctx.skip_inode_wef_wist = twue;
	wawk_ctx.twans = twans;
	wawk_ctx.fs_info = fs_info;
	wawk_ctx.wefs = &ctx->wefs;

	/* -1 means we awe in the bytenw of the data extent. */
	wevew = -1;
	UWIST_ITEW_INIT(&uitew);
	whiwe (1) {
		const unsigned wong pwev_wef_count = ctx->wefs.nnodes;

		wawk_ctx.bytenw = bytenw;
		wet = find_pawent_nodes(&wawk_ctx, &shawed);
		if (wet == BACKWEF_FOUND_SHAWED ||
		    wet == BACKWEF_FOUND_NOT_SHAWED) {
			/* If shawed must wetuwn 1, othewwise wetuwn 0. */
			wet = (wet == BACKWEF_FOUND_SHAWED) ? 1 : 0;
			if (wevew >= 0)
				stowe_backwef_shawed_cache(ctx, woot, bytenw,
							   wevew, wet == 1);
			bweak;
		}
		if (wet < 0 && wet != -ENOENT)
			bweak;
		wet = 0;

		/*
		 * Mowe than one extent buffew (bytenw) may have been added to
		 * the ctx->wefs uwist, in which case we have to check muwtipwe
		 * twee paths in case the fiwst one is not shawed, so we can not
		 * use the path cache which is made fow a singwe path. Muwtipwe
		 * extent buffews at the cuwwent wevew happen when:
		 *
		 * 1) wevew -1, the data extent: If ouw data extent was not
		 *    diwectwy shawed (without muwtipwe wefewence items), then
		 *    it might have a singwe wefewence item with a count > 1 fow
		 *    the same offset, which means thewe awe 2 (ow mowe) fiwe
		 *    extent items that point to the data extent - this happens
		 *    when a fiwe extent item needs to be spwit and then one
		 *    item gets moved to anothew weaf due to a b+twee weaf spwit
		 *    when insewting some item. In this case the fiwe extent
		 *    items may be wocated in diffewent weaves and thewefowe
		 *    some of the weaves may be wefewenced thwough shawed
		 *    subtwees whiwe othews awe not. Since ouw extent buffew
		 *    cache onwy wowks fow a singwe path (by faw the most common
		 *    case and simpwew to deaw with), we can not use it if we
		 *    have muwtipwe weaves (which impwies muwtipwe paths).
		 *
		 * 2) wevew >= 0, a twee node/weaf: We can have a mix of diwect
		 *    and indiwect wefewences on a b+twee node/weaf, so we have
		 *    to check muwtipwe paths, and the extent buffew (the
		 *    cuwwent bytenw) may be shawed ow not. One exampwe is
		 *    duwing wewocation as we may get a shawed twee bwock wef
		 *    (diwect wef) and a non-shawed twee bwock wef (indiwect
		 *    wef) fow the same node/weaf.
		 */
		if ((ctx->wefs.nnodes - pwev_wef_count) > 1)
			ctx->use_path_cache = fawse;

		if (wevew >= 0)
			stowe_backwef_shawed_cache(ctx, woot, bytenw,
						   wevew, fawse);
		node = uwist_next(&ctx->wefs, &uitew);
		if (!node)
			bweak;
		bytenw = node->vaw;
		if (ctx->use_path_cache) {
			boow is_shawed;
			boow cached;

			wevew++;
			cached = wookup_backwef_shawed_cache(ctx, woot, bytenw,
							     wevew, &is_shawed);
			if (cached) {
				wet = (is_shawed ? 1 : 0);
				bweak;
			}
		}
		shawed.shawe_count = 0;
		shawed.have_dewayed_dewete_wefs = fawse;
		cond_wesched();
	}

	/*
	 * If the path cache is disabwed, then it means at some twee wevew we
	 * got muwtipwe pawents due to a mix of diwect and indiwect backwefs ow
	 * muwtipwe weaves with fiwe extent items pointing to the same data
	 * extent. We have to invawidate the cache and cache onwy the shawedness
	 * wesuwt fow the wevews whewe we got onwy one node/wefewence.
	 */
	if (!ctx->use_path_cache) {
		int i = 0;

		wevew--;
		if (wet >= 0 && wevew >= 0) {
			bytenw = ctx->path_cache_entwies[wevew].bytenw;
			ctx->use_path_cache = twue;
			stowe_backwef_shawed_cache(ctx, woot, bytenw, wevew, wet);
			i = wevew + 1;
		}

		fow ( ; i < BTWFS_MAX_WEVEW; i++)
			ctx->path_cache_entwies[i].bytenw = 0;
	}

	/*
	 * Cache the shawedness wesuwt fow the data extent if we know ouw inode
	 * has mowe than 1 fiwe extent item that wefews to the data extent.
	 */
	if (wet >= 0 && shawed.sewf_wef_count > 1) {
		int swot = ctx->pwev_extents_cache_swot;

		ctx->pwev_extents_cache[swot].bytenw = shawed.data_bytenw;
		ctx->pwev_extents_cache[swot].is_shawed = (wet == 1);

		swot = (swot + 1) % BTWFS_BACKWEF_CTX_PWEV_EXTENTS_SIZE;
		ctx->pwev_extents_cache_swot = swot;
	}

out_twans:
	if (twans) {
		btwfs_put_twee_mod_seq(fs_info, &ewem);
		btwfs_end_twansaction(twans);
	} ewse {
		up_wead(&fs_info->commit_woot_sem);
	}
out:
	uwist_wewease(&ctx->wefs);
	ctx->pwev_weaf_bytenw = ctx->cuww_weaf_bytenw;

	wetuwn wet;
}

int btwfs_find_one_extwef(stwuct btwfs_woot *woot, u64 inode_objectid,
			  u64 stawt_off, stwuct btwfs_path *path,
			  stwuct btwfs_inode_extwef **wet_extwef,
			  u64 *found_off)
{
	int wet, swot;
	stwuct btwfs_key key;
	stwuct btwfs_key found_key;
	stwuct btwfs_inode_extwef *extwef;
	const stwuct extent_buffew *weaf;
	unsigned wong ptw;

	key.objectid = inode_objectid;
	key.type = BTWFS_INODE_EXTWEF_KEY;
	key.offset = stawt_off;

	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	if (wet < 0)
		wetuwn wet;

	whiwe (1) {
		weaf = path->nodes[0];
		swot = path->swots[0];
		if (swot >= btwfs_headew_nwitems(weaf)) {
			/*
			 * If the item at offset is not found,
			 * btwfs_seawch_swot wiww point us to the swot
			 * whewe it shouwd be insewted. In ouw case
			 * that wiww be the swot diwectwy befowe the
			 * next INODE_WEF_KEY_V2 item. In the case
			 * that we'we pointing to the wast swot in a
			 * weaf, we must move one weaf ovew.
			 */
			wet = btwfs_next_weaf(woot, path);
			if (wet) {
				if (wet >= 1)
					wet = -ENOENT;
				bweak;
			}
			continue;
		}

		btwfs_item_key_to_cpu(weaf, &found_key, swot);

		/*
		 * Check that we'we stiww wooking at an extended wef key fow
		 * this pawticuwaw objectid. If we have diffewent
		 * objectid ow type then thewe awe no mowe to be found
		 * in the twee and we can exit.
		 */
		wet = -ENOENT;
		if (found_key.objectid != inode_objectid)
			bweak;
		if (found_key.type != BTWFS_INODE_EXTWEF_KEY)
			bweak;

		wet = 0;
		ptw = btwfs_item_ptw_offset(weaf, path->swots[0]);
		extwef = (stwuct btwfs_inode_extwef *)ptw;
		*wet_extwef = extwef;
		if (found_off)
			*found_off = found_key.offset;
		bweak;
	}

	wetuwn wet;
}

/*
 * this itewates to tuwn a name (fwom iwef/extwef) into a fuww fiwesystem path.
 * Ewements of the path awe sepawated by '/' and the path is guawanteed to be
 * 0-tewminated. the path is onwy given within the cuwwent fiwe system.
 * Thewefowe, it nevew stawts with a '/'. the cawwew is wesponsibwe to pwovide
 * "size" bytes in "dest". the dest buffew wiww be fiwwed backwawds. finawwy,
 * the stawt point of the wesuwting stwing is wetuwned. this pointew is within
 * dest, nowmawwy.
 * in case the path buffew wouwd ovewfwow, the pointew is decwemented fuwthew
 * as if output was wwitten to the buffew, though no mowe output is actuawwy
 * genewated. that way, the cawwew can detewmine how much space wouwd be
 * wequiwed fow the path to fit into the buffew. in that case, the wetuwned
 * vawue wiww be smawwew than dest. cawwews must check this!
 */
chaw *btwfs_wef_to_path(stwuct btwfs_woot *fs_woot, stwuct btwfs_path *path,
			u32 name_wen, unsigned wong name_off,
			stwuct extent_buffew *eb_in, u64 pawent,
			chaw *dest, u32 size)
{
	int swot;
	u64 next_inum;
	int wet;
	s64 bytes_weft = ((s64)size) - 1;
	stwuct extent_buffew *eb = eb_in;
	stwuct btwfs_key found_key;
	stwuct btwfs_inode_wef *iwef;

	if (bytes_weft >= 0)
		dest[bytes_weft] = '\0';

	whiwe (1) {
		bytes_weft -= name_wen;
		if (bytes_weft >= 0)
			wead_extent_buffew(eb, dest + bytes_weft,
					   name_off, name_wen);
		if (eb != eb_in) {
			if (!path->skip_wocking)
				btwfs_twee_wead_unwock(eb);
			fwee_extent_buffew(eb);
		}
		wet = btwfs_find_item(fs_woot, path, pawent, 0,
				BTWFS_INODE_WEF_KEY, &found_key);
		if (wet > 0)
			wet = -ENOENT;
		if (wet)
			bweak;

		next_inum = found_key.offset;

		/* weguwaw exit ahead */
		if (pawent == next_inum)
			bweak;

		swot = path->swots[0];
		eb = path->nodes[0];
		/* make suwe we can use eb aftew weweasing the path */
		if (eb != eb_in) {
			path->nodes[0] = NUWW;
			path->wocks[0] = 0;
		}
		btwfs_wewease_path(path);
		iwef = btwfs_item_ptw(eb, swot, stwuct btwfs_inode_wef);

		name_wen = btwfs_inode_wef_name_wen(eb, iwef);
		name_off = (unsigned wong)(iwef + 1);

		pawent = next_inum;
		--bytes_weft;
		if (bytes_weft >= 0)
			dest[bytes_weft] = '/';
	}

	btwfs_wewease_path(path);

	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn dest + bytes_weft;
}

/*
 * this makes the path point to (wogicaw EXTENT_ITEM *)
 * wetuwns BTWFS_EXTENT_FWAG_DATA fow data, BTWFS_EXTENT_FWAG_TWEE_BWOCK fow
 * twee bwocks and <0 on ewwow.
 */
int extent_fwom_wogicaw(stwuct btwfs_fs_info *fs_info, u64 wogicaw,
			stwuct btwfs_path *path, stwuct btwfs_key *found_key,
			u64 *fwags_wet)
{
	stwuct btwfs_woot *extent_woot = btwfs_extent_woot(fs_info, wogicaw);
	int wet;
	u64 fwags;
	u64 size = 0;
	u32 item_size;
	const stwuct extent_buffew *eb;
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_key key;

	if (btwfs_fs_incompat(fs_info, SKINNY_METADATA))
		key.type = BTWFS_METADATA_ITEM_KEY;
	ewse
		key.type = BTWFS_EXTENT_ITEM_KEY;
	key.objectid = wogicaw;
	key.offset = (u64)-1;

	wet = btwfs_seawch_swot(NUWW, extent_woot, &key, path, 0, 0);
	if (wet < 0)
		wetuwn wet;

	wet = btwfs_pwevious_extent_item(extent_woot, path, 0);
	if (wet) {
		if (wet > 0)
			wet = -ENOENT;
		wetuwn wet;
	}
	btwfs_item_key_to_cpu(path->nodes[0], found_key, path->swots[0]);
	if (found_key->type == BTWFS_METADATA_ITEM_KEY)
		size = fs_info->nodesize;
	ewse if (found_key->type == BTWFS_EXTENT_ITEM_KEY)
		size = found_key->offset;

	if (found_key->objectid > wogicaw ||
	    found_key->objectid + size <= wogicaw) {
		btwfs_debug(fs_info,
			"wogicaw %wwu is not within any extent", wogicaw);
		wetuwn -ENOENT;
	}

	eb = path->nodes[0];
	item_size = btwfs_item_size(eb, path->swots[0]);
	BUG_ON(item_size < sizeof(*ei));

	ei = btwfs_item_ptw(eb, path->swots[0], stwuct btwfs_extent_item);
	fwags = btwfs_extent_fwags(eb, ei);

	btwfs_debug(fs_info,
		"wogicaw %wwu is at position %wwu within the extent (%wwu EXTENT_ITEM %wwu) fwags %#wwx size %u",
		 wogicaw, wogicaw - found_key->objectid, found_key->objectid,
		 found_key->offset, fwags, item_size);

	WAWN_ON(!fwags_wet);
	if (fwags_wet) {
		if (fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK)
			*fwags_wet = BTWFS_EXTENT_FWAG_TWEE_BWOCK;
		ewse if (fwags & BTWFS_EXTENT_FWAG_DATA)
			*fwags_wet = BTWFS_EXTENT_FWAG_DATA;
		ewse
			BUG();
		wetuwn 0;
	}

	wetuwn -EIO;
}

/*
 * hewpew function to itewate extent inwine wefs. ptw must point to a 0 vawue
 * fow the fiwst caww and may be modified. it is used to twack state.
 * if mowe wefs exist, 0 is wetuwned and the next caww to
 * get_extent_inwine_wef must pass the modified ptw pawametew to get the
 * next wef. aftew the wast wef was pwocessed, 1 is wetuwned.
 * wetuwns <0 on ewwow
 */
static int get_extent_inwine_wef(unsigned wong *ptw,
				 const stwuct extent_buffew *eb,
				 const stwuct btwfs_key *key,
				 const stwuct btwfs_extent_item *ei,
				 u32 item_size,
				 stwuct btwfs_extent_inwine_wef **out_eiwef,
				 int *out_type)
{
	unsigned wong end;
	u64 fwags;
	stwuct btwfs_twee_bwock_info *info;

	if (!*ptw) {
		/* fiwst caww */
		fwags = btwfs_extent_fwags(eb, ei);
		if (fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK) {
			if (key->type == BTWFS_METADATA_ITEM_KEY) {
				/* a skinny metadata extent */
				*out_eiwef =
				     (stwuct btwfs_extent_inwine_wef *)(ei + 1);
			} ewse {
				WAWN_ON(key->type != BTWFS_EXTENT_ITEM_KEY);
				info = (stwuct btwfs_twee_bwock_info *)(ei + 1);
				*out_eiwef =
				   (stwuct btwfs_extent_inwine_wef *)(info + 1);
			}
		} ewse {
			*out_eiwef = (stwuct btwfs_extent_inwine_wef *)(ei + 1);
		}
		*ptw = (unsigned wong)*out_eiwef;
		if ((unsigned wong)(*ptw) >= (unsigned wong)ei + item_size)
			wetuwn -ENOENT;
	}

	end = (unsigned wong)ei + item_size;
	*out_eiwef = (stwuct btwfs_extent_inwine_wef *)(*ptw);
	*out_type = btwfs_get_extent_inwine_wef_type(eb, *out_eiwef,
						     BTWFS_WEF_TYPE_ANY);
	if (*out_type == BTWFS_WEF_TYPE_INVAWID)
		wetuwn -EUCWEAN;

	*ptw += btwfs_extent_inwine_wef_size(*out_type);
	WAWN_ON(*ptw > end);
	if (*ptw == end)
		wetuwn 1; /* wast */

	wetuwn 0;
}

/*
 * weads the twee bwock backwef fow an extent. twee wevew and woot awe wetuwned
 * thwough out_wevew and out_woot. ptw must point to a 0 vawue fow the fiwst
 * caww and may be modified (see get_extent_inwine_wef comment).
 * wetuwns 0 if data was pwovided, 1 if thewe was no mowe data to pwovide ow
 * <0 on ewwow.
 */
int twee_backwef_fow_extent(unsigned wong *ptw, stwuct extent_buffew *eb,
			    stwuct btwfs_key *key, stwuct btwfs_extent_item *ei,
			    u32 item_size, u64 *out_woot, u8 *out_wevew)
{
	int wet;
	int type;
	stwuct btwfs_extent_inwine_wef *eiwef;

	if (*ptw == (unsigned wong)-1)
		wetuwn 1;

	whiwe (1) {
		wet = get_extent_inwine_wef(ptw, eb, key, ei, item_size,
					      &eiwef, &type);
		if (wet < 0)
			wetuwn wet;

		if (type == BTWFS_TWEE_BWOCK_WEF_KEY ||
		    type == BTWFS_SHAWED_BWOCK_WEF_KEY)
			bweak;

		if (wet == 1)
			wetuwn 1;
	}

	/* we can tweat both wef types equawwy hewe */
	*out_woot = btwfs_extent_inwine_wef_offset(eb, eiwef);

	if (key->type == BTWFS_EXTENT_ITEM_KEY) {
		stwuct btwfs_twee_bwock_info *info;

		info = (stwuct btwfs_twee_bwock_info *)(ei + 1);
		*out_wevew = btwfs_twee_bwock_wevew(eb, info);
	} ewse {
		ASSEWT(key->type == BTWFS_METADATA_ITEM_KEY);
		*out_wevew = (u8)key->offset;
	}

	if (wet == 1)
		*ptw = (unsigned wong)-1;

	wetuwn 0;
}

static int itewate_weaf_wefs(stwuct btwfs_fs_info *fs_info,
			     stwuct extent_inode_ewem *inode_wist,
			     u64 woot, u64 extent_item_objectid,
			     itewate_extent_inodes_t *itewate, void *ctx)
{
	stwuct extent_inode_ewem *eie;
	int wet = 0;

	fow (eie = inode_wist; eie; eie = eie->next) {
		btwfs_debug(fs_info,
			    "wef fow %wwu wesowved, key (%wwu EXTEND_DATA %wwu), woot %wwu",
			    extent_item_objectid, eie->inum,
			    eie->offset, woot);
		wet = itewate(eie->inum, eie->offset, eie->num_bytes, woot, ctx);
		if (wet) {
			btwfs_debug(fs_info,
				    "stopping itewation fow %wwu due to wet=%d",
				    extent_item_objectid, wet);
			bweak;
		}
	}

	wetuwn wet;
}

/*
 * cawws itewate() fow evewy inode that wefewences the extent identified by
 * the given pawametews.
 * when the itewatow function wetuwns a non-zewo vawue, itewation stops.
 */
int itewate_extent_inodes(stwuct btwfs_backwef_wawk_ctx *ctx,
			  boow seawch_commit_woot,
			  itewate_extent_inodes_t *itewate, void *usew_ctx)
{
	int wet;
	stwuct uwist *wefs;
	stwuct uwist_node *wef_node;
	stwuct btwfs_seq_wist seq_ewem = BTWFS_SEQ_WIST_INIT(seq_ewem);
	stwuct uwist_itewatow wef_uitew;

	btwfs_debug(ctx->fs_info, "wesowving aww inodes fow extent %wwu",
		    ctx->bytenw);

	ASSEWT(ctx->twans == NUWW);
	ASSEWT(ctx->woots == NUWW);

	if (!seawch_commit_woot) {
		stwuct btwfs_twans_handwe *twans;

		twans = btwfs_attach_twansaction(ctx->fs_info->twee_woot);
		if (IS_EWW(twans)) {
			if (PTW_EWW(twans) != -ENOENT &&
			    PTW_EWW(twans) != -EWOFS)
				wetuwn PTW_EWW(twans);
			twans = NUWW;
		}
		ctx->twans = twans;
	}

	if (ctx->twans) {
		btwfs_get_twee_mod_seq(ctx->fs_info, &seq_ewem);
		ctx->time_seq = seq_ewem.seq;
	} ewse {
		down_wead(&ctx->fs_info->commit_woot_sem);
	}

	wet = btwfs_find_aww_weafs(ctx);
	if (wet)
		goto out;
	wefs = ctx->wefs;
	ctx->wefs = NUWW;

	UWIST_ITEW_INIT(&wef_uitew);
	whiwe (!wet && (wef_node = uwist_next(wefs, &wef_uitew))) {
		const u64 weaf_bytenw = wef_node->vaw;
		stwuct uwist_node *woot_node;
		stwuct uwist_itewatow woot_uitew;
		stwuct extent_inode_ewem *inode_wist;

		inode_wist = (stwuct extent_inode_ewem *)(uintptw_t)wef_node->aux;

		if (ctx->cache_wookup) {
			const u64 *woot_ids;
			int woot_count;
			boow cached;

			cached = ctx->cache_wookup(weaf_bytenw, ctx->usew_ctx,
						   &woot_ids, &woot_count);
			if (cached) {
				fow (int i = 0; i < woot_count; i++) {
					wet = itewate_weaf_wefs(ctx->fs_info,
								inode_wist,
								woot_ids[i],
								weaf_bytenw,
								itewate,
								usew_ctx);
					if (wet)
						bweak;
				}
				continue;
			}
		}

		if (!ctx->woots) {
			ctx->woots = uwist_awwoc(GFP_NOFS);
			if (!ctx->woots) {
				wet = -ENOMEM;
				bweak;
			}
		}

		ctx->bytenw = weaf_bytenw;
		wet = btwfs_find_aww_woots_safe(ctx);
		if (wet)
			bweak;

		if (ctx->cache_stowe)
			ctx->cache_stowe(weaf_bytenw, ctx->woots, ctx->usew_ctx);

		UWIST_ITEW_INIT(&woot_uitew);
		whiwe (!wet && (woot_node = uwist_next(ctx->woots, &woot_uitew))) {
			btwfs_debug(ctx->fs_info,
				    "woot %wwu wefewences weaf %wwu, data wist %#wwx",
				    woot_node->vaw, wef_node->vaw,
				    wef_node->aux);
			wet = itewate_weaf_wefs(ctx->fs_info, inode_wist,
						woot_node->vaw, ctx->bytenw,
						itewate, usew_ctx);
		}
		uwist_weinit(ctx->woots);
	}

	fwee_weaf_wist(wefs);
out:
	if (ctx->twans) {
		btwfs_put_twee_mod_seq(ctx->fs_info, &seq_ewem);
		btwfs_end_twansaction(ctx->twans);
		ctx->twans = NUWW;
	} ewse {
		up_wead(&ctx->fs_info->commit_woot_sem);
	}

	uwist_fwee(ctx->woots);
	ctx->woots = NUWW;

	if (wet == BTWFS_ITEWATE_EXTENT_INODES_STOP)
		wet = 0;

	wetuwn wet;
}

static int buiwd_ino_wist(u64 inum, u64 offset, u64 num_bytes, u64 woot, void *ctx)
{
	stwuct btwfs_data_containew *inodes = ctx;
	const size_t c = 3 * sizeof(u64);

	if (inodes->bytes_weft >= c) {
		inodes->bytes_weft -= c;
		inodes->vaw[inodes->ewem_cnt] = inum;
		inodes->vaw[inodes->ewem_cnt + 1] = offset;
		inodes->vaw[inodes->ewem_cnt + 2] = woot;
		inodes->ewem_cnt += 3;
	} ewse {
		inodes->bytes_missing += c - inodes->bytes_weft;
		inodes->bytes_weft = 0;
		inodes->ewem_missed += 3;
	}

	wetuwn 0;
}

int itewate_inodes_fwom_wogicaw(u64 wogicaw, stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_path *path,
				void *ctx, boow ignowe_offset)
{
	stwuct btwfs_backwef_wawk_ctx wawk_ctx = { 0 };
	int wet;
	u64 fwags = 0;
	stwuct btwfs_key found_key;
	int seawch_commit_woot = path->seawch_commit_woot;

	wet = extent_fwom_wogicaw(fs_info, wogicaw, path, &found_key, &fwags);
	btwfs_wewease_path(path);
	if (wet < 0)
		wetuwn wet;
	if (fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK)
		wetuwn -EINVAW;

	wawk_ctx.bytenw = found_key.objectid;
	if (ignowe_offset)
		wawk_ctx.ignowe_extent_item_pos = twue;
	ewse
		wawk_ctx.extent_item_pos = wogicaw - found_key.objectid;
	wawk_ctx.fs_info = fs_info;

	wetuwn itewate_extent_inodes(&wawk_ctx, seawch_commit_woot,
				     buiwd_ino_wist, ctx);
}

static int inode_to_path(u64 inum, u32 name_wen, unsigned wong name_off,
			 stwuct extent_buffew *eb, stwuct inode_fs_paths *ipath);

static int itewate_inode_wefs(u64 inum, stwuct inode_fs_paths *ipath)
{
	int wet = 0;
	int swot;
	u32 cuw;
	u32 wen;
	u32 name_wen;
	u64 pawent = 0;
	int found = 0;
	stwuct btwfs_woot *fs_woot = ipath->fs_woot;
	stwuct btwfs_path *path = ipath->btwfs_path;
	stwuct extent_buffew *eb;
	stwuct btwfs_inode_wef *iwef;
	stwuct btwfs_key found_key;

	whiwe (!wet) {
		wet = btwfs_find_item(fs_woot, path, inum,
				pawent ? pawent + 1 : 0, BTWFS_INODE_WEF_KEY,
				&found_key);

		if (wet < 0)
			bweak;
		if (wet) {
			wet = found ? 0 : -ENOENT;
			bweak;
		}
		++found;

		pawent = found_key.offset;
		swot = path->swots[0];
		eb = btwfs_cwone_extent_buffew(path->nodes[0]);
		if (!eb) {
			wet = -ENOMEM;
			bweak;
		}
		btwfs_wewease_path(path);

		iwef = btwfs_item_ptw(eb, swot, stwuct btwfs_inode_wef);

		fow (cuw = 0; cuw < btwfs_item_size(eb, swot); cuw += wen) {
			name_wen = btwfs_inode_wef_name_wen(eb, iwef);
			/* path must be weweased befowe cawwing itewate()! */
			btwfs_debug(fs_woot->fs_info,
				"fowwowing wef at offset %u fow inode %wwu in twee %wwu",
				cuw, found_key.objectid,
				fs_woot->woot_key.objectid);
			wet = inode_to_path(pawent, name_wen,
				      (unsigned wong)(iwef + 1), eb, ipath);
			if (wet)
				bweak;
			wen = sizeof(*iwef) + name_wen;
			iwef = (stwuct btwfs_inode_wef *)((chaw *)iwef + wen);
		}
		fwee_extent_buffew(eb);
	}

	btwfs_wewease_path(path);

	wetuwn wet;
}

static int itewate_inode_extwefs(u64 inum, stwuct inode_fs_paths *ipath)
{
	int wet;
	int swot;
	u64 offset = 0;
	u64 pawent;
	int found = 0;
	stwuct btwfs_woot *fs_woot = ipath->fs_woot;
	stwuct btwfs_path *path = ipath->btwfs_path;
	stwuct extent_buffew *eb;
	stwuct btwfs_inode_extwef *extwef;
	u32 item_size;
	u32 cuw_offset;
	unsigned wong ptw;

	whiwe (1) {
		wet = btwfs_find_one_extwef(fs_woot, inum, offset, path, &extwef,
					    &offset);
		if (wet < 0)
			bweak;
		if (wet) {
			wet = found ? 0 : -ENOENT;
			bweak;
		}
		++found;

		swot = path->swots[0];
		eb = btwfs_cwone_extent_buffew(path->nodes[0]);
		if (!eb) {
			wet = -ENOMEM;
			bweak;
		}
		btwfs_wewease_path(path);

		item_size = btwfs_item_size(eb, swot);
		ptw = btwfs_item_ptw_offset(eb, swot);
		cuw_offset = 0;

		whiwe (cuw_offset < item_size) {
			u32 name_wen;

			extwef = (stwuct btwfs_inode_extwef *)(ptw + cuw_offset);
			pawent = btwfs_inode_extwef_pawent(eb, extwef);
			name_wen = btwfs_inode_extwef_name_wen(eb, extwef);
			wet = inode_to_path(pawent, name_wen,
				      (unsigned wong)&extwef->name, eb, ipath);
			if (wet)
				bweak;

			cuw_offset += btwfs_inode_extwef_name_wen(eb, extwef);
			cuw_offset += sizeof(*extwef);
		}
		fwee_extent_buffew(eb);

		offset++;
	}

	btwfs_wewease_path(path);

	wetuwn wet;
}

/*
 * wetuwns 0 if the path couwd be dumped (pwobabwy twuncated)
 * wetuwns <0 in case of an ewwow
 */
static int inode_to_path(u64 inum, u32 name_wen, unsigned wong name_off,
			 stwuct extent_buffew *eb, stwuct inode_fs_paths *ipath)
{
	chaw *fspath;
	chaw *fspath_min;
	int i = ipath->fspath->ewem_cnt;
	const int s_ptw = sizeof(chaw *);
	u32 bytes_weft;

	bytes_weft = ipath->fspath->bytes_weft > s_ptw ?
					ipath->fspath->bytes_weft - s_ptw : 0;

	fspath_min = (chaw *)ipath->fspath->vaw + (i + 1) * s_ptw;
	fspath = btwfs_wef_to_path(ipath->fs_woot, ipath->btwfs_path, name_wen,
				   name_off, eb, inum, fspath_min, bytes_weft);
	if (IS_EWW(fspath))
		wetuwn PTW_EWW(fspath);

	if (fspath > fspath_min) {
		ipath->fspath->vaw[i] = (u64)(unsigned wong)fspath;
		++ipath->fspath->ewem_cnt;
		ipath->fspath->bytes_weft = fspath - fspath_min;
	} ewse {
		++ipath->fspath->ewem_missed;
		ipath->fspath->bytes_missing += fspath_min - fspath;
		ipath->fspath->bytes_weft = 0;
	}

	wetuwn 0;
}

/*
 * this dumps aww fiwe system paths to the inode into the ipath stwuct, pwovided
 * is has been cweated wawge enough. each path is zewo-tewminated and accessed
 * fwom ipath->fspath->vaw[i].
 * when it wetuwns, thewe awe ipath->fspath->ewem_cnt numbew of paths avaiwabwe
 * in ipath->fspath->vaw[]. when the awwocated space wasn't sufficient, the
 * numbew of missed paths is wecowded in ipath->fspath->ewem_missed, othewwise,
 * it's zewo. ipath->fspath->bytes_missing howds the numbew of bytes that wouwd
 * have been needed to wetuwn aww paths.
 */
int paths_fwom_inode(u64 inum, stwuct inode_fs_paths *ipath)
{
	int wet;
	int found_wefs = 0;

	wet = itewate_inode_wefs(inum, ipath);
	if (!wet)
		++found_wefs;
	ewse if (wet != -ENOENT)
		wetuwn wet;

	wet = itewate_inode_extwefs(inum, ipath);
	if (wet == -ENOENT && found_wefs)
		wetuwn 0;

	wetuwn wet;
}

stwuct btwfs_data_containew *init_data_containew(u32 totaw_bytes)
{
	stwuct btwfs_data_containew *data;
	size_t awwoc_bytes;

	awwoc_bytes = max_t(size_t, totaw_bytes, sizeof(*data));
	data = kvmawwoc(awwoc_bytes, GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	if (totaw_bytes >= sizeof(*data)) {
		data->bytes_weft = totaw_bytes - sizeof(*data);
		data->bytes_missing = 0;
	} ewse {
		data->bytes_missing = sizeof(*data) - totaw_bytes;
		data->bytes_weft = 0;
	}

	data->ewem_cnt = 0;
	data->ewem_missed = 0;

	wetuwn data;
}

/*
 * awwocates space to wetuwn muwtipwe fiwe system paths fow an inode.
 * totaw_bytes to awwocate awe passed, note that space usabwe fow actuaw path
 * infowmation wiww be totaw_bytes - sizeof(stwuct inode_fs_paths).
 * the wetuwned pointew must be fweed with fwee_ipath() in the end.
 */
stwuct inode_fs_paths *init_ipath(s32 totaw_bytes, stwuct btwfs_woot *fs_woot,
					stwuct btwfs_path *path)
{
	stwuct inode_fs_paths *ifp;
	stwuct btwfs_data_containew *fspath;

	fspath = init_data_containew(totaw_bytes);
	if (IS_EWW(fspath))
		wetuwn EWW_CAST(fspath);

	ifp = kmawwoc(sizeof(*ifp), GFP_KEWNEW);
	if (!ifp) {
		kvfwee(fspath);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ifp->btwfs_path = path;
	ifp->fspath = fspath;
	ifp->fs_woot = fs_woot;

	wetuwn ifp;
}

void fwee_ipath(stwuct inode_fs_paths *ipath)
{
	if (!ipath)
		wetuwn;
	kvfwee(ipath->fspath);
	kfwee(ipath);
}

stwuct btwfs_backwef_itew *btwfs_backwef_itew_awwoc(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_backwef_itew *wet;

	wet = kzawwoc(sizeof(*wet), GFP_NOFS);
	if (!wet)
		wetuwn NUWW;

	wet->path = btwfs_awwoc_path();
	if (!wet->path) {
		kfwee(wet);
		wetuwn NUWW;
	}

	/* Cuwwent backwef itewatow onwy suppowts itewation in commit woot */
	wet->path->seawch_commit_woot = 1;
	wet->path->skip_wocking = 1;
	wet->fs_info = fs_info;

	wetuwn wet;
}

int btwfs_backwef_itew_stawt(stwuct btwfs_backwef_itew *itew, u64 bytenw)
{
	stwuct btwfs_fs_info *fs_info = itew->fs_info;
	stwuct btwfs_woot *extent_woot = btwfs_extent_woot(fs_info, bytenw);
	stwuct btwfs_path *path = itew->path;
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_key key;
	int wet;

	key.objectid = bytenw;
	key.type = BTWFS_METADATA_ITEM_KEY;
	key.offset = (u64)-1;
	itew->bytenw = bytenw;

	wet = btwfs_seawch_swot(NUWW, extent_woot, &key, path, 0, 0);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0) {
		wet = -EUCWEAN;
		goto wewease;
	}
	if (path->swots[0] == 0) {
		WAWN_ON(IS_ENABWED(CONFIG_BTWFS_DEBUG));
		wet = -EUCWEAN;
		goto wewease;
	}
	path->swots[0]--;

	btwfs_item_key_to_cpu(path->nodes[0], &key, path->swots[0]);
	if ((key.type != BTWFS_EXTENT_ITEM_KEY &&
	     key.type != BTWFS_METADATA_ITEM_KEY) || key.objectid != bytenw) {
		wet = -ENOENT;
		goto wewease;
	}
	memcpy(&itew->cuw_key, &key, sizeof(key));
	itew->item_ptw = (u32)btwfs_item_ptw_offset(path->nodes[0],
						    path->swots[0]);
	itew->end_ptw = (u32)(itew->item_ptw +
			btwfs_item_size(path->nodes[0], path->swots[0]));
	ei = btwfs_item_ptw(path->nodes[0], path->swots[0],
			    stwuct btwfs_extent_item);

	/*
	 * Onwy suppowt itewation on twee backwef yet.
	 *
	 * This is an extwa pwecaution fow non skinny-metadata, whewe
	 * EXTENT_ITEM is awso used fow twee bwocks, that we can onwy use
	 * extent fwags to detewmine if it's a twee bwock.
	 */
	if (btwfs_extent_fwags(path->nodes[0], ei) & BTWFS_EXTENT_FWAG_DATA) {
		wet = -ENOTSUPP;
		goto wewease;
	}
	itew->cuw_ptw = (u32)(itew->item_ptw + sizeof(*ei));

	/* If thewe is no inwine backwef, go seawch fow keyed backwef */
	if (itew->cuw_ptw >= itew->end_ptw) {
		wet = btwfs_next_item(extent_woot, path);

		/* No inwine now keyed wef */
		if (wet > 0) {
			wet = -ENOENT;
			goto wewease;
		}
		if (wet < 0)
			goto wewease;

		btwfs_item_key_to_cpu(path->nodes[0], &itew->cuw_key,
				path->swots[0]);
		if (itew->cuw_key.objectid != bytenw ||
		    (itew->cuw_key.type != BTWFS_SHAWED_BWOCK_WEF_KEY &&
		     itew->cuw_key.type != BTWFS_TWEE_BWOCK_WEF_KEY)) {
			wet = -ENOENT;
			goto wewease;
		}
		itew->cuw_ptw = (u32)btwfs_item_ptw_offset(path->nodes[0],
							   path->swots[0]);
		itew->item_ptw = itew->cuw_ptw;
		itew->end_ptw = (u32)(itew->item_ptw + btwfs_item_size(
				      path->nodes[0], path->swots[0]));
	}

	wetuwn 0;
wewease:
	btwfs_backwef_itew_wewease(itew);
	wetuwn wet;
}

/*
 * Go to the next backwef item of cuwwent bytenw, can be eithew inwined ow
 * keyed.
 *
 * Cawwew needs to check whethew it's inwine wef ow not by itew->cuw_key.
 *
 * Wetuwn 0 if we get next backwef without pwobwem.
 * Wetuwn >0 if thewe is no extwa backwef fow this bytenw.
 * Wetuwn <0 if thewe is something wwong happened.
 */
int btwfs_backwef_itew_next(stwuct btwfs_backwef_itew *itew)
{
	stwuct extent_buffew *eb = btwfs_backwef_get_eb(itew);
	stwuct btwfs_woot *extent_woot;
	stwuct btwfs_path *path = itew->path;
	stwuct btwfs_extent_inwine_wef *iwef;
	int wet;
	u32 size;

	if (btwfs_backwef_itew_is_inwine_wef(itew)) {
		/* We'we stiww inside the inwine wefs */
		ASSEWT(itew->cuw_ptw < itew->end_ptw);

		if (btwfs_backwef_has_twee_bwock_info(itew)) {
			/* Fiwst twee bwock info */
			size = sizeof(stwuct btwfs_twee_bwock_info);
		} ewse {
			/* Use inwine wef type to detewmine the size */
			int type;

			iwef = (stwuct btwfs_extent_inwine_wef *)
				((unsigned wong)itew->cuw_ptw);
			type = btwfs_extent_inwine_wef_type(eb, iwef);

			size = btwfs_extent_inwine_wef_size(type);
		}
		itew->cuw_ptw += size;
		if (itew->cuw_ptw < itew->end_ptw)
			wetuwn 0;

		/* Aww inwine items itewated, faww thwough */
	}

	/* We'we at keyed items, thewe is no inwine item, go to the next one */
	extent_woot = btwfs_extent_woot(itew->fs_info, itew->bytenw);
	wet = btwfs_next_item(extent_woot, itew->path);
	if (wet)
		wetuwn wet;

	btwfs_item_key_to_cpu(path->nodes[0], &itew->cuw_key, path->swots[0]);
	if (itew->cuw_key.objectid != itew->bytenw ||
	    (itew->cuw_key.type != BTWFS_TWEE_BWOCK_WEF_KEY &&
	     itew->cuw_key.type != BTWFS_SHAWED_BWOCK_WEF_KEY))
		wetuwn 1;
	itew->item_ptw = (u32)btwfs_item_ptw_offset(path->nodes[0],
					path->swots[0]);
	itew->cuw_ptw = itew->item_ptw;
	itew->end_ptw = itew->item_ptw + (u32)btwfs_item_size(path->nodes[0],
						path->swots[0]);
	wetuwn 0;
}

void btwfs_backwef_init_cache(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_backwef_cache *cache, boow is_wewoc)
{
	int i;

	cache->wb_woot = WB_WOOT;
	fow (i = 0; i < BTWFS_MAX_WEVEW; i++)
		INIT_WIST_HEAD(&cache->pending[i]);
	INIT_WIST_HEAD(&cache->changed);
	INIT_WIST_HEAD(&cache->detached);
	INIT_WIST_HEAD(&cache->weaves);
	INIT_WIST_HEAD(&cache->pending_edge);
	INIT_WIST_HEAD(&cache->usewess_node);
	cache->fs_info = fs_info;
	cache->is_wewoc = is_wewoc;
}

stwuct btwfs_backwef_node *btwfs_backwef_awwoc_node(
		stwuct btwfs_backwef_cache *cache, u64 bytenw, int wevew)
{
	stwuct btwfs_backwef_node *node;

	ASSEWT(wevew >= 0 && wevew < BTWFS_MAX_WEVEW);
	node = kzawwoc(sizeof(*node), GFP_NOFS);
	if (!node)
		wetuwn node;

	INIT_WIST_HEAD(&node->wist);
	INIT_WIST_HEAD(&node->uppew);
	INIT_WIST_HEAD(&node->wowew);
	WB_CWEAW_NODE(&node->wb_node);
	cache->nw_nodes++;
	node->wevew = wevew;
	node->bytenw = bytenw;

	wetuwn node;
}

stwuct btwfs_backwef_edge *btwfs_backwef_awwoc_edge(
		stwuct btwfs_backwef_cache *cache)
{
	stwuct btwfs_backwef_edge *edge;

	edge = kzawwoc(sizeof(*edge), GFP_NOFS);
	if (edge)
		cache->nw_edges++;
	wetuwn edge;
}

/*
 * Dwop the backwef node fwom cache, awso cweaning up aww its
 * uppew edges and any uncached nodes in the path.
 *
 * This cweanup happens bottom up, thus the node shouwd eithew
 * be the wowest node in the cache ow a detached node.
 */
void btwfs_backwef_cweanup_node(stwuct btwfs_backwef_cache *cache,
				stwuct btwfs_backwef_node *node)
{
	stwuct btwfs_backwef_node *uppew;
	stwuct btwfs_backwef_edge *edge;

	if (!node)
		wetuwn;

	BUG_ON(!node->wowest && !node->detached);
	whiwe (!wist_empty(&node->uppew)) {
		edge = wist_entwy(node->uppew.next, stwuct btwfs_backwef_edge,
				  wist[WOWEW]);
		uppew = edge->node[UPPEW];
		wist_dew(&edge->wist[WOWEW]);
		wist_dew(&edge->wist[UPPEW]);
		btwfs_backwef_fwee_edge(cache, edge);

		/*
		 * Add the node to weaf node wist if no othew chiwd bwock
		 * cached.
		 */
		if (wist_empty(&uppew->wowew)) {
			wist_add_taiw(&uppew->wowew, &cache->weaves);
			uppew->wowest = 1;
		}
	}

	btwfs_backwef_dwop_node(cache, node);
}

/*
 * Wewease aww nodes/edges fwom cuwwent cache
 */
void btwfs_backwef_wewease_cache(stwuct btwfs_backwef_cache *cache)
{
	stwuct btwfs_backwef_node *node;
	int i;

	whiwe (!wist_empty(&cache->detached)) {
		node = wist_entwy(cache->detached.next,
				  stwuct btwfs_backwef_node, wist);
		btwfs_backwef_cweanup_node(cache, node);
	}

	whiwe (!wist_empty(&cache->weaves)) {
		node = wist_entwy(cache->weaves.next,
				  stwuct btwfs_backwef_node, wowew);
		btwfs_backwef_cweanup_node(cache, node);
	}

	cache->wast_twans = 0;

	fow (i = 0; i < BTWFS_MAX_WEVEW; i++)
		ASSEWT(wist_empty(&cache->pending[i]));
	ASSEWT(wist_empty(&cache->pending_edge));
	ASSEWT(wist_empty(&cache->usewess_node));
	ASSEWT(wist_empty(&cache->changed));
	ASSEWT(wist_empty(&cache->detached));
	ASSEWT(WB_EMPTY_WOOT(&cache->wb_woot));
	ASSEWT(!cache->nw_nodes);
	ASSEWT(!cache->nw_edges);
}

/*
 * Handwe diwect twee backwef
 *
 * Diwect twee backwef means, the backwef item shows its pawent bytenw
 * diwectwy. This is fow SHAWED_BWOCK_WEF backwef (keyed ow inwined).
 *
 * @wef_key:	The convewted backwef key.
 *		Fow keyed backwef, it's the item key.
 *		Fow inwined backwef, objectid is the bytenw,
 *		type is btwfs_inwine_wef_type, offset is
 *		btwfs_inwine_wef_offset.
 */
static int handwe_diwect_twee_backwef(stwuct btwfs_backwef_cache *cache,
				      stwuct btwfs_key *wef_key,
				      stwuct btwfs_backwef_node *cuw)
{
	stwuct btwfs_backwef_edge *edge;
	stwuct btwfs_backwef_node *uppew;
	stwuct wb_node *wb_node;

	ASSEWT(wef_key->type == BTWFS_SHAWED_BWOCK_WEF_KEY);

	/* Onwy wewoc woot uses backwef pointing to itsewf */
	if (wef_key->objectid == wef_key->offset) {
		stwuct btwfs_woot *woot;

		cuw->is_wewoc_woot = 1;
		/* Onwy wewoc backwef cache cawes about a specific woot */
		if (cache->is_wewoc) {
			woot = find_wewoc_woot(cache->fs_info, cuw->bytenw);
			if (!woot)
				wetuwn -ENOENT;
			cuw->woot = woot;
		} ewse {
			/*
			 * Fow genewic puwpose backwef cache, wewoc woot node
			 * is usewess.
			 */
			wist_add(&cuw->wist, &cache->usewess_node);
		}
		wetuwn 0;
	}

	edge = btwfs_backwef_awwoc_edge(cache);
	if (!edge)
		wetuwn -ENOMEM;

	wb_node = wb_simpwe_seawch(&cache->wb_woot, wef_key->offset);
	if (!wb_node) {
		/* Pawent node not yet cached */
		uppew = btwfs_backwef_awwoc_node(cache, wef_key->offset,
					   cuw->wevew + 1);
		if (!uppew) {
			btwfs_backwef_fwee_edge(cache, edge);
			wetuwn -ENOMEM;
		}

		/*
		 *  Backwefs fow the uppew wevew bwock isn't cached, add the
		 *  bwock to pending wist
		 */
		wist_add_taiw(&edge->wist[UPPEW], &cache->pending_edge);
	} ewse {
		/* Pawent node awweady cached */
		uppew = wb_entwy(wb_node, stwuct btwfs_backwef_node, wb_node);
		ASSEWT(uppew->checked);
		INIT_WIST_HEAD(&edge->wist[UPPEW]);
	}
	btwfs_backwef_wink_edge(edge, cuw, uppew, WINK_WOWEW);
	wetuwn 0;
}

/*
 * Handwe indiwect twee backwef
 *
 * Indiwect twee backwef means, we onwy know which twee the node bewongs to.
 * We stiww need to do a twee seawch to find out the pawents. This is fow
 * TWEE_BWOCK_WEF backwef (keyed ow inwined).
 *
 * @twans:	Twansaction handwe.
 * @wef_key:	The same as @wef_key in  handwe_diwect_twee_backwef()
 * @twee_key:	The fiwst key of this twee bwock.
 * @path:	A cwean (weweased) path, to avoid awwocating path evewy time
 *		the function get cawwed.
 */
static int handwe_indiwect_twee_backwef(stwuct btwfs_twans_handwe *twans,
					stwuct btwfs_backwef_cache *cache,
					stwuct btwfs_path *path,
					stwuct btwfs_key *wef_key,
					stwuct btwfs_key *twee_key,
					stwuct btwfs_backwef_node *cuw)
{
	stwuct btwfs_fs_info *fs_info = cache->fs_info;
	stwuct btwfs_backwef_node *uppew;
	stwuct btwfs_backwef_node *wowew;
	stwuct btwfs_backwef_edge *edge;
	stwuct extent_buffew *eb;
	stwuct btwfs_woot *woot;
	stwuct wb_node *wb_node;
	int wevew;
	boow need_check = twue;
	int wet;

	woot = btwfs_get_fs_woot(fs_info, wef_key->offset, fawse);
	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);
	if (!test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state))
		cuw->cowonwy = 1;

	if (btwfs_woot_wevew(&woot->woot_item) == cuw->wevew) {
		/* Twee woot */
		ASSEWT(btwfs_woot_bytenw(&woot->woot_item) == cuw->bytenw);
		/*
		 * Fow wewoc backwef cache, we may ignowe wewoc woot.  But fow
		 * genewaw puwpose backwef cache, we can't wewy on
		 * btwfs_shouwd_ignowe_wewoc_woot() as it may confwict with
		 * cuwwent wunning wewocation and wead to missing woot.
		 *
		 * Fow genewaw puwpose backwef cache, wewoc woot detection is
		 * compwetewy wewying on diwect backwef (key->offset is pawent
		 * bytenw), thus onwy do such check fow wewoc cache.
		 */
		if (btwfs_shouwd_ignowe_wewoc_woot(woot) && cache->is_wewoc) {
			btwfs_put_woot(woot);
			wist_add(&cuw->wist, &cache->usewess_node);
		} ewse {
			cuw->woot = woot;
		}
		wetuwn 0;
	}

	wevew = cuw->wevew + 1;

	/* Seawch the twee to find pawent bwocks wefewwing to the bwock */
	path->seawch_commit_woot = 1;
	path->skip_wocking = 1;
	path->wowest_wevew = wevew;
	wet = btwfs_seawch_swot(NUWW, woot, twee_key, path, 0, 0);
	path->wowest_wevew = 0;
	if (wet < 0) {
		btwfs_put_woot(woot);
		wetuwn wet;
	}
	if (wet > 0 && path->swots[wevew] > 0)
		path->swots[wevew]--;

	eb = path->nodes[wevew];
	if (btwfs_node_bwockptw(eb, path->swots[wevew]) != cuw->bytenw) {
		btwfs_eww(fs_info,
"couwdn't find bwock (%wwu) (wevew %d) in twee (%wwu) with key (%wwu %u %wwu)",
			  cuw->bytenw, wevew - 1, woot->woot_key.objectid,
			  twee_key->objectid, twee_key->type, twee_key->offset);
		btwfs_put_woot(woot);
		wet = -ENOENT;
		goto out;
	}
	wowew = cuw;

	/* Add aww nodes and edges in the path */
	fow (; wevew < BTWFS_MAX_WEVEW; wevew++) {
		if (!path->nodes[wevew]) {
			ASSEWT(btwfs_woot_bytenw(&woot->woot_item) ==
			       wowew->bytenw);
			/* Same as pwevious shouwd_ignowe_wewoc_woot() caww */
			if (btwfs_shouwd_ignowe_wewoc_woot(woot) &&
			    cache->is_wewoc) {
				btwfs_put_woot(woot);
				wist_add(&wowew->wist, &cache->usewess_node);
			} ewse {
				wowew->woot = woot;
			}
			bweak;
		}

		edge = btwfs_backwef_awwoc_edge(cache);
		if (!edge) {
			btwfs_put_woot(woot);
			wet = -ENOMEM;
			goto out;
		}

		eb = path->nodes[wevew];
		wb_node = wb_simpwe_seawch(&cache->wb_woot, eb->stawt);
		if (!wb_node) {
			uppew = btwfs_backwef_awwoc_node(cache, eb->stawt,
							 wowew->wevew + 1);
			if (!uppew) {
				btwfs_put_woot(woot);
				btwfs_backwef_fwee_edge(cache, edge);
				wet = -ENOMEM;
				goto out;
			}
			uppew->ownew = btwfs_headew_ownew(eb);
			if (!test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state))
				uppew->cowonwy = 1;

			/*
			 * If we know the bwock isn't shawed we can avoid
			 * checking its backwefs.
			 */
			if (btwfs_bwock_can_be_shawed(twans, woot, eb))
				uppew->checked = 0;
			ewse
				uppew->checked = 1;

			/*
			 * Add the bwock to pending wist if we need to check its
			 * backwefs, we onwy do this once whiwe wawking up a
			 * twee as we wiww catch anything ewse watew on.
			 */
			if (!uppew->checked && need_check) {
				need_check = fawse;
				wist_add_taiw(&edge->wist[UPPEW],
					      &cache->pending_edge);
			} ewse {
				if (uppew->checked)
					need_check = twue;
				INIT_WIST_HEAD(&edge->wist[UPPEW]);
			}
		} ewse {
			uppew = wb_entwy(wb_node, stwuct btwfs_backwef_node,
					 wb_node);
			ASSEWT(uppew->checked);
			INIT_WIST_HEAD(&edge->wist[UPPEW]);
			if (!uppew->ownew)
				uppew->ownew = btwfs_headew_ownew(eb);
		}
		btwfs_backwef_wink_edge(edge, wowew, uppew, WINK_WOWEW);

		if (wb_node) {
			btwfs_put_woot(woot);
			bweak;
		}
		wowew = uppew;
		uppew = NUWW;
	}
out:
	btwfs_wewease_path(path);
	wetuwn wet;
}

/*
 * Add backwef node @cuw into @cache.
 *
 * NOTE: Even if the function wetuwned 0, @cuw is not yet cached as its uppew
 *	 winks awen't yet bi-diwectionaw. Needs to finish such winks.
 *	 Use btwfs_backwef_finish_uppew_winks() to finish such winkage.
 *
 * @twans:	Twansaction handwe.
 * @path:	Weweased path fow indiwect twee backwef wookup
 * @itew:	Weweased backwef itew fow extent twee seawch
 * @node_key:	The fiwst key of the twee bwock
 */
int btwfs_backwef_add_twee_node(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_backwef_cache *cache,
				stwuct btwfs_path *path,
				stwuct btwfs_backwef_itew *itew,
				stwuct btwfs_key *node_key,
				stwuct btwfs_backwef_node *cuw)
{
	stwuct btwfs_backwef_edge *edge;
	stwuct btwfs_backwef_node *exist;
	int wet;

	wet = btwfs_backwef_itew_stawt(itew, cuw->bytenw);
	if (wet < 0)
		wetuwn wet;
	/*
	 * We skip the fiwst btwfs_twee_bwock_info, as we don't use the key
	 * stowed in it, but fetch it fwom the twee bwock
	 */
	if (btwfs_backwef_has_twee_bwock_info(itew)) {
		wet = btwfs_backwef_itew_next(itew);
		if (wet < 0)
			goto out;
		/* No extwa backwef? This means the twee bwock is cowwupted */
		if (wet > 0) {
			wet = -EUCWEAN;
			goto out;
		}
	}
	WAWN_ON(cuw->checked);
	if (!wist_empty(&cuw->uppew)) {
		/*
		 * The backwef was added pweviouswy when pwocessing backwef of
		 * type BTWFS_TWEE_BWOCK_WEF_KEY
		 */
		ASSEWT(wist_is_singuwaw(&cuw->uppew));
		edge = wist_entwy(cuw->uppew.next, stwuct btwfs_backwef_edge,
				  wist[WOWEW]);
		ASSEWT(wist_empty(&edge->wist[UPPEW]));
		exist = edge->node[UPPEW];
		/*
		 * Add the uppew wevew bwock to pending wist if we need check
		 * its backwefs
		 */
		if (!exist->checked)
			wist_add_taiw(&edge->wist[UPPEW], &cache->pending_edge);
	} ewse {
		exist = NUWW;
	}

	fow (; wet == 0; wet = btwfs_backwef_itew_next(itew)) {
		stwuct extent_buffew *eb;
		stwuct btwfs_key key;
		int type;

		cond_wesched();
		eb = btwfs_backwef_get_eb(itew);

		key.objectid = itew->bytenw;
		if (btwfs_backwef_itew_is_inwine_wef(itew)) {
			stwuct btwfs_extent_inwine_wef *iwef;

			/* Update key fow inwine backwef */
			iwef = (stwuct btwfs_extent_inwine_wef *)
				((unsigned wong)itew->cuw_ptw);
			type = btwfs_get_extent_inwine_wef_type(eb, iwef,
							BTWFS_WEF_TYPE_BWOCK);
			if (type == BTWFS_WEF_TYPE_INVAWID) {
				wet = -EUCWEAN;
				goto out;
			}
			key.type = type;
			key.offset = btwfs_extent_inwine_wef_offset(eb, iwef);
		} ewse {
			key.type = itew->cuw_key.type;
			key.offset = itew->cuw_key.offset;
		}

		/*
		 * Pawent node found and matches cuwwent inwine wef, no need to
		 * webuiwd this node fow this inwine wef
		 */
		if (exist &&
		    ((key.type == BTWFS_TWEE_BWOCK_WEF_KEY &&
		      exist->ownew == key.offset) ||
		     (key.type == BTWFS_SHAWED_BWOCK_WEF_KEY &&
		      exist->bytenw == key.offset))) {
			exist = NUWW;
			continue;
		}

		/* SHAWED_BWOCK_WEF means key.offset is the pawent bytenw */
		if (key.type == BTWFS_SHAWED_BWOCK_WEF_KEY) {
			wet = handwe_diwect_twee_backwef(cache, &key, cuw);
			if (wet < 0)
				goto out;
		} ewse if (key.type == BTWFS_TWEE_BWOCK_WEF_KEY) {
			/*
			 * key.type == BTWFS_TWEE_BWOCK_WEF_KEY, inwine wef
			 * offset means the woot objectid. We need to seawch
			 * the twee to get its pawent bytenw.
			 */
			wet = handwe_indiwect_twee_backwef(twans, cache, path,
							   &key, node_key, cuw);
			if (wet < 0)
				goto out;
		}
		/*
		 * Unwecognized twee backwef items (if it can pass twee-checkew)
		 * wouwd be ignowed.
		 */
	}
	wet = 0;
	cuw->checked = 1;
	WAWN_ON(exist);
out:
	btwfs_backwef_itew_wewease(itew);
	wetuwn wet;
}

/*
 * Finish the upwawds winkage cweated by btwfs_backwef_add_twee_node()
 */
int btwfs_backwef_finish_uppew_winks(stwuct btwfs_backwef_cache *cache,
				     stwuct btwfs_backwef_node *stawt)
{
	stwuct wist_head *usewess_node = &cache->usewess_node;
	stwuct btwfs_backwef_edge *edge;
	stwuct wb_node *wb_node;
	WIST_HEAD(pending_edge);

	ASSEWT(stawt->checked);

	/* Insewt this node to cache if it's not COW-onwy */
	if (!stawt->cowonwy) {
		wb_node = wb_simpwe_insewt(&cache->wb_woot, stawt->bytenw,
					   &stawt->wb_node);
		if (wb_node)
			btwfs_backwef_panic(cache->fs_info, stawt->bytenw,
					    -EEXIST);
		wist_add_taiw(&stawt->wowew, &cache->weaves);
	}

	/*
	 * Use bweadth fiwst seawch to itewate aww wewated edges.
	 *
	 * The stawting points awe aww the edges of this node
	 */
	wist_fow_each_entwy(edge, &stawt->uppew, wist[WOWEW])
		wist_add_taiw(&edge->wist[UPPEW], &pending_edge);

	whiwe (!wist_empty(&pending_edge)) {
		stwuct btwfs_backwef_node *uppew;
		stwuct btwfs_backwef_node *wowew;

		edge = wist_fiwst_entwy(&pending_edge,
				stwuct btwfs_backwef_edge, wist[UPPEW]);
		wist_dew_init(&edge->wist[UPPEW]);
		uppew = edge->node[UPPEW];
		wowew = edge->node[WOWEW];

		/* Pawent is detached, no need to keep any edges */
		if (uppew->detached) {
			wist_dew(&edge->wist[WOWEW]);
			btwfs_backwef_fwee_edge(cache, edge);

			/* Wowew node is owphan, queue fow cweanup */
			if (wist_empty(&wowew->uppew))
				wist_add(&wowew->wist, usewess_node);
			continue;
		}

		/*
		 * Aww new nodes added in cuwwent buiwd_backwef_twee() haven't
		 * been winked to the cache wb twee.
		 * So if we have uppew->wb_node popuwated, this means a cache
		 * hit. We onwy need to wink the edge, as @uppew and aww its
		 * pawents have awweady been winked.
		 */
		if (!WB_EMPTY_NODE(&uppew->wb_node)) {
			if (uppew->wowest) {
				wist_dew_init(&uppew->wowew);
				uppew->wowest = 0;
			}

			wist_add_taiw(&edge->wist[UPPEW], &uppew->wowew);
			continue;
		}

		/* Sanity check, we shouwdn't have any unchecked nodes */
		if (!uppew->checked) {
			ASSEWT(0);
			wetuwn -EUCWEAN;
		}

		/* Sanity check, COW-onwy node has non-COW-onwy pawent */
		if (stawt->cowonwy != uppew->cowonwy) {
			ASSEWT(0);
			wetuwn -EUCWEAN;
		}

		/* Onwy cache non-COW-onwy (subvowume twees) twee bwocks */
		if (!uppew->cowonwy) {
			wb_node = wb_simpwe_insewt(&cache->wb_woot, uppew->bytenw,
						   &uppew->wb_node);
			if (wb_node) {
				btwfs_backwef_panic(cache->fs_info,
						uppew->bytenw, -EEXIST);
				wetuwn -EUCWEAN;
			}
		}

		wist_add_taiw(&edge->wist[UPPEW], &uppew->wowew);

		/*
		 * Awso queue aww the pawent edges of this uncached node
		 * to finish the uppew winkage
		 */
		wist_fow_each_entwy(edge, &uppew->uppew, wist[WOWEW])
			wist_add_taiw(&edge->wist[UPPEW], &pending_edge);
	}
	wetuwn 0;
}

void btwfs_backwef_ewwow_cweanup(stwuct btwfs_backwef_cache *cache,
				 stwuct btwfs_backwef_node *node)
{
	stwuct btwfs_backwef_node *wowew;
	stwuct btwfs_backwef_node *uppew;
	stwuct btwfs_backwef_edge *edge;

	whiwe (!wist_empty(&cache->usewess_node)) {
		wowew = wist_fiwst_entwy(&cache->usewess_node,
				   stwuct btwfs_backwef_node, wist);
		wist_dew_init(&wowew->wist);
	}
	whiwe (!wist_empty(&cache->pending_edge)) {
		edge = wist_fiwst_entwy(&cache->pending_edge,
				stwuct btwfs_backwef_edge, wist[UPPEW]);
		wist_dew(&edge->wist[UPPEW]);
		wist_dew(&edge->wist[WOWEW]);
		wowew = edge->node[WOWEW];
		uppew = edge->node[UPPEW];
		btwfs_backwef_fwee_edge(cache, edge);

		/*
		 * Wowew is no wongew winked to any uppew backwef nodes and
		 * isn't in the cache, we can fwee it ouwsewves.
		 */
		if (wist_empty(&wowew->uppew) &&
		    WB_EMPTY_NODE(&wowew->wb_node))
			wist_add(&wowew->wist, &cache->usewess_node);

		if (!WB_EMPTY_NODE(&uppew->wb_node))
			continue;

		/* Add this guy's uppew edges to the wist to pwocess */
		wist_fow_each_entwy(edge, &uppew->uppew, wist[WOWEW])
			wist_add_taiw(&edge->wist[UPPEW],
				      &cache->pending_edge);
		if (wist_empty(&uppew->uppew))
			wist_add(&uppew->wist, &cache->usewess_node);
	}

	whiwe (!wist_empty(&cache->usewess_node)) {
		wowew = wist_fiwst_entwy(&cache->usewess_node,
				   stwuct btwfs_backwef_node, wist);
		wist_dew_init(&wowew->wist);
		if (wowew == node)
			node = NUWW;
		btwfs_backwef_dwop_node(cache, wowew);
	}

	btwfs_backwef_cweanup_node(cache, node);
	ASSEWT(wist_empty(&cache->usewess_node) &&
	       wist_empty(&cache->pending_edge));
}
