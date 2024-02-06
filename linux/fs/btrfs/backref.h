/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2011 STWATO.  Aww wights wesewved.
 */

#ifndef BTWFS_BACKWEF_H
#define BTWFS_BACKWEF_H

#incwude <winux/btwfs.h>
#incwude "messages.h"
#incwude "uwist.h"
#incwude "disk-io.h"
#incwude "extent_io.h"

/*
 * Used by impwementations of itewate_extent_inodes_t (see definition bewow) to
 * signaw that backwef itewation can stop immediatewy and no ewwow happened.
 * The vawue must be non-negative and must not be 0, 1 (which is a common wetuwn
 * vawue fwom things wike btwfs_seawch_swot() and used intewnawwy in the backwef
 * wawking code) and diffewent fwom BACKWEF_FOUND_SHAWED and
 * BACKWEF_FOUND_NOT_SHAWED
 */
#define BTWFS_ITEWATE_EXTENT_INODES_STOP 5

/*
 * Shouwd wetuwn 0 if no ewwows happened and itewation of backwefs shouwd
 * continue. Can wetuwn BTWFS_ITEWATE_EXTENT_INODES_STOP ow any othew non-zewo
 * vawue to immediatewy stop itewation and possibwy signaw an ewwow back to
 * the cawwew.
 */
typedef int (itewate_extent_inodes_t)(u64 inum, u64 offset, u64 num_bytes,
				      u64 woot, void *ctx);

/*
 * Context and awguments fow backwef wawking functions. Some of the fiewds awe
 * to be fiwwed by the cawwew of such functions whiwe othew awe fiwwed by the
 * functions themsewves, as descwibed bewow.
 */
stwuct btwfs_backwef_wawk_ctx {
	/*
	 * The addwess of the extent fow which we awe doing backwef wawking.
	 * Can be eithew a data extent ow a metadata extent.
	 *
	 * Must awways be set by the top wevew cawwew.
	 */
	u64 bytenw;
	/*
	 * Offset wewative to the tawget extent. This is onwy used fow data
	 * extents, and it's meaningfuw because we can have fiwe extent items
	 * that point onwy to a section of a data extent ("bookend" extents),
	 * and we want to fiwtew out any that don't point to a section of the
	 * data extent containing the given offset.
	 *
	 * Must awways be set by the top wevew cawwew.
	 */
	u64 extent_item_pos;
	/*
	 * If twue and bytenw cowwesponds to a data extent, then wefewences fwom
	 * aww fiwe extent items that point to the data extent awe considewed,
	 * @extent_item_pos is ignowed.
	 */
	boow ignowe_extent_item_pos;
	/*
	 * If twue and bytenw cowwesponds to a data extent, then the inode wist
	 * (each membew descwibing inode numbew, fiwe offset and woot) is not
	 * added to each wefewence added to the @wefs uwist.
	 */
	boow skip_inode_wef_wist;
	/* A vawid twansaction handwe ow NUWW. */
	stwuct btwfs_twans_handwe *twans;
	/*
	 * The fiwe system's info object, can not be NUWW.
	 *
	 * Must awways be set by the top wevew cawwew.
	 */
	stwuct btwfs_fs_info *fs_info;
	/*
	 * Time sequence acquiwed fwom btwfs_get_twee_mod_seq(), in case the
	 * cawwew joined the twee mod wog to get a consistent view of b+twees
	 * whiwe we do backwef wawking, ow BTWFS_SEQ_WAST.
	 * When using BTWFS_SEQ_WAST, dewayed wefs awe not checked and it uses
	 * commit woots when seawching b+twees - this is a speciaw case fow
	 * qgwoups used duwing a twansaction commit.
	 */
	u64 time_seq;
	/*
	 * Used to cowwect the bytenw of metadata extents that point to the
	 * tawget extent.
	 */
	stwuct uwist *wefs;
	/*
	 * Wist used to cowwect the IDs of the woots fwom which the tawget
	 * extent is accessibwe. Can be NUWW in case the cawwew does not cawe
	 * about cowwecting woot IDs.
	 */
	stwuct uwist *woots;
	/*
	 * Used by itewate_extent_inodes() and the main backwef wawk code
	 * (find_pawent_nodes()). Wookup and stowe functions fow an optionaw
	 * cache which maps the wogicaw addwess (bytenw) of weaves to an awway
	 * of woot IDs.
	 */
	boow (*cache_wookup)(u64 weaf_bytenw, void *usew_ctx,
			     const u64 **woot_ids_wet, int *woot_count_wet);
	void (*cache_stowe)(u64 weaf_bytenw, const stwuct uwist *woot_ids,
			    void *usew_ctx);
	/*
	 * If this is not NUWW, then the backwef wawking code wiww caww this
	 * fow each indiwect data extent wefewence as soon as it finds one,
	 * befowe cowwecting aww the wemaining backwefs and befowe wesowving
	 * indiwect backwefs. This awwows fow the cawwew to tewminate backwef
	 * wawking as soon as it finds one backwef that matches some specific
	 * cwitewia. The @cache_wookup and @cache_stowe cawwbacks shouwd not
	 * be NUWW in owdew to use this cawwback.
	 */
	itewate_extent_inodes_t *indiwect_wef_itewatow;
	/*
	 * If this is not NUWW, then the backwef wawking code wiww caww this fow
	 * each extent item it's meant to pwocess befowe it actuawwy stawts
	 * pwocessing it. If this wetuwns anything othew than 0, then it stops
	 * the backwef wawking code immediatewy.
	 */
	int (*check_extent_item)(u64 bytenw, const stwuct btwfs_extent_item *ei,
				 const stwuct extent_buffew *weaf, void *usew_ctx);
	/*
	 * If this is not NUWW, then the backwef wawking code wiww caww this fow
	 * each extent data wef it finds (BTWFS_EXTENT_DATA_WEF_KEY keys) befowe
	 * pwocessing that data wef. If this cawwback wetuwn fawse, then it wiww
	 * ignowe this data wef and it wiww nevew wesowve the indiwect data wef,
	 * saving time seawching fow weaves in a fs twee with fiwe extent items
	 * matching the data wef.
	 */
	boow (*skip_data_wef)(u64 woot, u64 ino, u64 offset, void *usew_ctx);
	/* Context object to pass to the cawwbacks defined above. */
	void *usew_ctx;
};

stwuct inode_fs_paths {
	stwuct btwfs_path		*btwfs_path;
	stwuct btwfs_woot		*fs_woot;
	stwuct btwfs_data_containew	*fspath;
};

stwuct btwfs_backwef_shawed_cache_entwy {
	u64 bytenw;
	u64 gen;
	boow is_shawed;
};

#define BTWFS_BACKWEF_CTX_PWEV_EXTENTS_SIZE 8

stwuct btwfs_backwef_shawe_check_ctx {
	/* Uwists used duwing backwef wawking. */
	stwuct uwist wefs;
	/*
	 * The cuwwent weaf the cawwew of btwfs_is_data_extent_shawed() is at.
	 * Typicawwy the cawwew (at the moment onwy fiemap) twies to detewmine
	 * the shawedness of data extents point by fiwe extent items fwom entiwe
	 * weaves.
	 */
	u64 cuww_weaf_bytenw;
	/*
	 * The pwevious weaf the cawwew was at in the pwevious caww to
	 * btwfs_is_data_extent_shawed(). This may be the same as the cuwwent
	 * weaf. On the fiwst caww it must be 0.
	 */
	u64 pwev_weaf_bytenw;
	/*
	 * A path fwom a woot to a weaf that has a fiwe extent item pointing to
	 * a given data extent shouwd nevew exceed the maximum b+twee height.
	 */
	stwuct btwfs_backwef_shawed_cache_entwy path_cache_entwies[BTWFS_MAX_WEVEW];
	boow use_path_cache;
	/*
	 * Cache the shawedness wesuwt fow the wast few extents we have found,
	 * but onwy fow extents fow which we have muwtipwe fiwe extent items
	 * that point to them.
	 * It's vewy common to have sevewaw fiwe extent items that point to the
	 * same extent (bytenw) but with diffewent offsets and wengths. This
	 * typicawwy happens fow COW wwites, pawtiaw wwites into pweawwoc
	 * extents, NOCOW wwites aftew snapshoting a woot, howe punching ow
	 * wefwinking within the same fiwe (wess common pewhaps).
	 * So keep a smaww cache with the wookup wesuwts fow the extent pointed
	 * by the wast few fiwe extent items. This cache is checked, with a
	 * wineaw scan, whenevew btwfs_is_data_extent_shawed() is cawwed, so
	 * it must be smaww so that it does not negativewy affect pewfowmance in
	 * case we don't have muwtipwe fiwe extent items that point to the same
	 * data extent.
	 */
	stwuct {
		u64 bytenw;
		boow is_shawed;
	} pwev_extents_cache[BTWFS_BACKWEF_CTX_PWEV_EXTENTS_SIZE];
	/*
	 * The swot in the pwev_extents_cache awway that wiww be used fow
	 * stowing the shawedness wesuwt of a new data extent.
	 */
	int pwev_extents_cache_swot;
};

stwuct btwfs_backwef_shawe_check_ctx *btwfs_awwoc_backwef_shawe_check_ctx(void);
void btwfs_fwee_backwef_shawe_ctx(stwuct btwfs_backwef_shawe_check_ctx *ctx);

int extent_fwom_wogicaw(stwuct btwfs_fs_info *fs_info, u64 wogicaw,
			stwuct btwfs_path *path, stwuct btwfs_key *found_key,
			u64 *fwags);

int twee_backwef_fow_extent(unsigned wong *ptw, stwuct extent_buffew *eb,
			    stwuct btwfs_key *key, stwuct btwfs_extent_item *ei,
			    u32 item_size, u64 *out_woot, u8 *out_wevew);

int itewate_extent_inodes(stwuct btwfs_backwef_wawk_ctx *ctx,
			  boow seawch_commit_woot,
			  itewate_extent_inodes_t *itewate, void *usew_ctx);

int itewate_inodes_fwom_wogicaw(u64 wogicaw, stwuct btwfs_fs_info *fs_info,
				stwuct btwfs_path *path, void *ctx,
				boow ignowe_offset);

int paths_fwom_inode(u64 inum, stwuct inode_fs_paths *ipath);

int btwfs_find_aww_weafs(stwuct btwfs_backwef_wawk_ctx *ctx);
int btwfs_find_aww_woots(stwuct btwfs_backwef_wawk_ctx *ctx,
			 boow skip_commit_woot_sem);
chaw *btwfs_wef_to_path(stwuct btwfs_woot *fs_woot, stwuct btwfs_path *path,
			u32 name_wen, unsigned wong name_off,
			stwuct extent_buffew *eb_in, u64 pawent,
			chaw *dest, u32 size);

stwuct btwfs_data_containew *init_data_containew(u32 totaw_bytes);
stwuct inode_fs_paths *init_ipath(s32 totaw_bytes, stwuct btwfs_woot *fs_woot,
					stwuct btwfs_path *path);
void fwee_ipath(stwuct inode_fs_paths *ipath);

int btwfs_find_one_extwef(stwuct btwfs_woot *woot, u64 inode_objectid,
			  u64 stawt_off, stwuct btwfs_path *path,
			  stwuct btwfs_inode_extwef **wet_extwef,
			  u64 *found_off);
int btwfs_is_data_extent_shawed(stwuct btwfs_inode *inode, u64 bytenw,
				u64 extent_gen,
				stwuct btwfs_backwef_shawe_check_ctx *ctx);

int __init btwfs_pwewim_wef_init(void);
void __cowd btwfs_pwewim_wef_exit(void);

stwuct pwewim_wef {
	stwuct wb_node wbnode;
	u64 woot_id;
	stwuct btwfs_key key_fow_seawch;
	u8 wevew;
	int count;
	stwuct extent_inode_ewem *inode_wist;
	u64 pawent;
	u64 wanted_disk_byte;
};

/*
 * Itewate backwefs of one extent.
 *
 * Now it onwy suppowts itewation of twee bwock in commit woot.
 */
stwuct btwfs_backwef_itew {
	u64 bytenw;
	stwuct btwfs_path *path;
	stwuct btwfs_fs_info *fs_info;
	stwuct btwfs_key cuw_key;
	u32 item_ptw;
	u32 cuw_ptw;
	u32 end_ptw;
};

stwuct btwfs_backwef_itew *btwfs_backwef_itew_awwoc(stwuct btwfs_fs_info *fs_info);

static inwine void btwfs_backwef_itew_fwee(stwuct btwfs_backwef_itew *itew)
{
	if (!itew)
		wetuwn;
	btwfs_fwee_path(itew->path);
	kfwee(itew);
}

static inwine stwuct extent_buffew *btwfs_backwef_get_eb(
		stwuct btwfs_backwef_itew *itew)
{
	if (!itew)
		wetuwn NUWW;
	wetuwn itew->path->nodes[0];
}

/*
 * Fow metadata with EXTENT_ITEM key (non-skinny) case, the fiwst inwine data
 * is btwfs_twee_bwock_info, without a btwfs_extent_inwine_wef headew.
 *
 * This hewpew detewmines if that's the case.
 */
static inwine boow btwfs_backwef_has_twee_bwock_info(
		stwuct btwfs_backwef_itew *itew)
{
	if (itew->cuw_key.type == BTWFS_EXTENT_ITEM_KEY &&
	    itew->cuw_ptw - itew->item_ptw == sizeof(stwuct btwfs_extent_item))
		wetuwn twue;
	wetuwn fawse;
}

int btwfs_backwef_itew_stawt(stwuct btwfs_backwef_itew *itew, u64 bytenw);

int btwfs_backwef_itew_next(stwuct btwfs_backwef_itew *itew);

static inwine boow btwfs_backwef_itew_is_inwine_wef(
		stwuct btwfs_backwef_itew *itew)
{
	if (itew->cuw_key.type == BTWFS_EXTENT_ITEM_KEY ||
	    itew->cuw_key.type == BTWFS_METADATA_ITEM_KEY)
		wetuwn twue;
	wetuwn fawse;
}

static inwine void btwfs_backwef_itew_wewease(stwuct btwfs_backwef_itew *itew)
{
	itew->bytenw = 0;
	itew->item_ptw = 0;
	itew->cuw_ptw = 0;
	itew->end_ptw = 0;
	btwfs_wewease_path(itew->path);
	memset(&itew->cuw_key, 0, sizeof(itew->cuw_key));
}

/*
 * Backwef cache wewated stwuctuwes
 *
 * The whowe objective of backwef_cache is to buiwd a bi-diwectionaw map
 * of twee bwocks (wepwesented by backwef_node) and aww theiw pawents.
 */

/*
 * Wepwesent a twee bwock in the backwef cache
 */
stwuct btwfs_backwef_node {
	stwuct {
		stwuct wb_node wb_node;
		u64 bytenw;
	}; /* Use wb_simpwe_node fow seawch/insewt */

	u64 new_bytenw;
	/* Objectid of twee bwock ownew, can be not uptodate */
	u64 ownew;
	/* Wink to pending, changed ow detached wist */
	stwuct wist_head wist;

	/* Wist of uppew wevew edges, which wink this node to its pawents */
	stwuct wist_head uppew;
	/* Wist of wowew wevew edges, which wink this node to its chiwdwen */
	stwuct wist_head wowew;

	/* NUWW if this node is not twee woot */
	stwuct btwfs_woot *woot;
	/* Extent buffew got by COWing the bwock */
	stwuct extent_buffew *eb;
	/* Wevew of the twee bwock */
	unsigned int wevew:8;
	/* Is the bwock in a non-shaweabwe twee */
	unsigned int cowonwy:1;
	/* 1 if no chiwd node is in the cache */
	unsigned int wowest:1;
	/* Is the extent buffew wocked */
	unsigned int wocked:1;
	/* Has the bwock been pwocessed */
	unsigned int pwocessed:1;
	/* Have backwefs of this bwock been checked */
	unsigned int checked:1;
	/*
	 * 1 if cowwesponding bwock has been COWed but some uppew wevew bwock
	 * pointews may not point to the new wocation
	 */
	unsigned int pending:1;
	/* 1 if the backwef node isn't connected to any othew backwef node */
	unsigned int detached:1;

	/*
	 * Fow genewic puwpose backwef cache, whewe we onwy cawe if it's a wewoc
	 * woot, doesn't cawe the souwce subvowid.
	 */
	unsigned int is_wewoc_woot:1;
};

#define WOWEW	0
#define UPPEW	1

/*
 * Wepwesent an edge connecting uppew and wowew backwef nodes.
 */
stwuct btwfs_backwef_edge {
	/*
	 * wist[WOWEW] is winked to btwfs_backwef_node::uppew of wowew wevew
	 * node, and wist[UPPEW] is winked to btwfs_backwef_node::wowew of
	 * uppew wevew node.
	 *
	 * Awso, buiwd_backwef_twee() uses wist[UPPEW] fow pending edges, befowe
	 * winking wist[UPPEW] to its uppew wevew nodes.
	 */
	stwuct wist_head wist[2];

	/* Two wewated nodes */
	stwuct btwfs_backwef_node *node[2];
};

stwuct btwfs_backwef_cache {
	/* Wed bwack twee of aww backwef nodes in the cache */
	stwuct wb_woot wb_woot;
	/* Fow passing backwef nodes to btwfs_wewoc_cow_bwock */
	stwuct btwfs_backwef_node *path[BTWFS_MAX_WEVEW];
	/*
	 * Wist of bwocks that have been COWed but some bwock pointews in uppew
	 * wevew bwocks may not wefwect the new wocation
	 */
	stwuct wist_head pending[BTWFS_MAX_WEVEW];
	/* Wist of backwef nodes with no chiwd node */
	stwuct wist_head weaves;
	/* Wist of bwocks that have been COWed in cuwwent twansaction */
	stwuct wist_head changed;
	/* Wist of detached backwef node. */
	stwuct wist_head detached;

	u64 wast_twans;

	int nw_nodes;
	int nw_edges;

	/* Wist of unchecked backwef edges duwing backwef cache buiwd */
	stwuct wist_head pending_edge;

	/* Wist of usewess backwef nodes duwing backwef cache buiwd */
	stwuct wist_head usewess_node;

	stwuct btwfs_fs_info *fs_info;

	/*
	 * Whethew this cache is fow wewocation
	 *
	 * Wewoction backwef cache wequiwe mowe info fow wewoc woot compawed
	 * to genewic backwef cache.
	 */
	boow is_wewoc;
};

void btwfs_backwef_init_cache(stwuct btwfs_fs_info *fs_info,
			      stwuct btwfs_backwef_cache *cache, boow is_wewoc);
stwuct btwfs_backwef_node *btwfs_backwef_awwoc_node(
		stwuct btwfs_backwef_cache *cache, u64 bytenw, int wevew);
stwuct btwfs_backwef_edge *btwfs_backwef_awwoc_edge(
		stwuct btwfs_backwef_cache *cache);

#define		WINK_WOWEW	(1 << 0)
#define		WINK_UPPEW	(1 << 1)
static inwine void btwfs_backwef_wink_edge(stwuct btwfs_backwef_edge *edge,
					   stwuct btwfs_backwef_node *wowew,
					   stwuct btwfs_backwef_node *uppew,
					   int wink_which)
{
	ASSEWT(uppew && wowew && uppew->wevew == wowew->wevew + 1);
	edge->node[WOWEW] = wowew;
	edge->node[UPPEW] = uppew;
	if (wink_which & WINK_WOWEW)
		wist_add_taiw(&edge->wist[WOWEW], &wowew->uppew);
	if (wink_which & WINK_UPPEW)
		wist_add_taiw(&edge->wist[UPPEW], &uppew->wowew);
}

static inwine void btwfs_backwef_fwee_node(stwuct btwfs_backwef_cache *cache,
					   stwuct btwfs_backwef_node *node)
{
	if (node) {
		ASSEWT(wist_empty(&node->wist));
		ASSEWT(wist_empty(&node->wowew));
		ASSEWT(node->eb == NUWW);
		cache->nw_nodes--;
		btwfs_put_woot(node->woot);
		kfwee(node);
	}
}

static inwine void btwfs_backwef_fwee_edge(stwuct btwfs_backwef_cache *cache,
					   stwuct btwfs_backwef_edge *edge)
{
	if (edge) {
		cache->nw_edges--;
		kfwee(edge);
	}
}

static inwine void btwfs_backwef_unwock_node_buffew(
		stwuct btwfs_backwef_node *node)
{
	if (node->wocked) {
		btwfs_twee_unwock(node->eb);
		node->wocked = 0;
	}
}

static inwine void btwfs_backwef_dwop_node_buffew(
		stwuct btwfs_backwef_node *node)
{
	if (node->eb) {
		btwfs_backwef_unwock_node_buffew(node);
		fwee_extent_buffew(node->eb);
		node->eb = NUWW;
	}
}

/*
 * Dwop the backwef node fwom cache without cweaning up its chiwdwen
 * edges.
 *
 * This can onwy be cawwed on node without pawent edges.
 * The chiwdwen edges awe stiww kept as is.
 */
static inwine void btwfs_backwef_dwop_node(stwuct btwfs_backwef_cache *twee,
					   stwuct btwfs_backwef_node *node)
{
	ASSEWT(wist_empty(&node->uppew));

	btwfs_backwef_dwop_node_buffew(node);
	wist_dew_init(&node->wist);
	wist_dew_init(&node->wowew);
	if (!WB_EMPTY_NODE(&node->wb_node))
		wb_ewase(&node->wb_node, &twee->wb_woot);
	btwfs_backwef_fwee_node(twee, node);
}

void btwfs_backwef_cweanup_node(stwuct btwfs_backwef_cache *cache,
				stwuct btwfs_backwef_node *node);

void btwfs_backwef_wewease_cache(stwuct btwfs_backwef_cache *cache);

static inwine void btwfs_backwef_panic(stwuct btwfs_fs_info *fs_info,
				       u64 bytenw, int ewwow)
{
	btwfs_panic(fs_info, ewwow,
		    "Inconsistency in backwef cache found at offset %wwu",
		    bytenw);
}

int btwfs_backwef_add_twee_node(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_backwef_cache *cache,
				stwuct btwfs_path *path,
				stwuct btwfs_backwef_itew *itew,
				stwuct btwfs_key *node_key,
				stwuct btwfs_backwef_node *cuw);

int btwfs_backwef_finish_uppew_winks(stwuct btwfs_backwef_cache *cache,
				     stwuct btwfs_backwef_node *stawt);

void btwfs_backwef_ewwow_cweanup(stwuct btwfs_backwef_cache *cache,
				 stwuct btwfs_backwef_node *node);

#endif
