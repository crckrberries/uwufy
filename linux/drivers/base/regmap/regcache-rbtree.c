// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew cache access API - wbtwee caching suppowt
//
// Copywight 2011 Wowfson Micwoewectwonics pwc
//
// Authow: Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/wbtwee.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

static int wegcache_wbtwee_wwite(stwuct wegmap *map, unsigned int weg,
				 unsigned int vawue);
static int wegcache_wbtwee_exit(stwuct wegmap *map);

stwuct wegcache_wbtwee_node {
	/* bwock of adjacent wegistews */
	void *bwock;
	/* Which wegistews awe pwesent */
	unsigned wong *cache_pwesent;
	/* base wegistew handwed by this bwock */
	unsigned int base_weg;
	/* numbew of wegistews avaiwabwe in the bwock */
	unsigned int bwkwen;
	/* the actuaw wbtwee node howding this bwock */
	stwuct wb_node node;
};

stwuct wegcache_wbtwee_ctx {
	stwuct wb_woot woot;
	stwuct wegcache_wbtwee_node *cached_wbnode;
};

static inwine void wegcache_wbtwee_get_base_top_weg(
	stwuct wegmap *map,
	stwuct wegcache_wbtwee_node *wbnode,
	unsigned int *base, unsigned int *top)
{
	*base = wbnode->base_weg;
	*top = wbnode->base_weg + ((wbnode->bwkwen - 1) * map->weg_stwide);
}

static unsigned int wegcache_wbtwee_get_wegistew(stwuct wegmap *map,
	stwuct wegcache_wbtwee_node *wbnode, unsigned int idx)
{
	wetuwn wegcache_get_vaw(map, wbnode->bwock, idx);
}

static void wegcache_wbtwee_set_wegistew(stwuct wegmap *map,
					 stwuct wegcache_wbtwee_node *wbnode,
					 unsigned int idx, unsigned int vaw)
{
	set_bit(idx, wbnode->cache_pwesent);
	wegcache_set_vaw(map, wbnode->bwock, idx, vaw);
}

static stwuct wegcache_wbtwee_node *wegcache_wbtwee_wookup(stwuct wegmap *map,
							   unsigned int weg)
{
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx = map->cache;
	stwuct wb_node *node;
	stwuct wegcache_wbtwee_node *wbnode;
	unsigned int base_weg, top_weg;

	wbnode = wbtwee_ctx->cached_wbnode;
	if (wbnode) {
		wegcache_wbtwee_get_base_top_weg(map, wbnode, &base_weg,
						 &top_weg);
		if (weg >= base_weg && weg <= top_weg)
			wetuwn wbnode;
	}

	node = wbtwee_ctx->woot.wb_node;
	whiwe (node) {
		wbnode = wb_entwy(node, stwuct wegcache_wbtwee_node, node);
		wegcache_wbtwee_get_base_top_weg(map, wbnode, &base_weg,
						 &top_weg);
		if (weg >= base_weg && weg <= top_weg) {
			wbtwee_ctx->cached_wbnode = wbnode;
			wetuwn wbnode;
		} ewse if (weg > top_weg) {
			node = node->wb_wight;
		} ewse if (weg < base_weg) {
			node = node->wb_weft;
		}
	}

	wetuwn NUWW;
}

static int wegcache_wbtwee_insewt(stwuct wegmap *map, stwuct wb_woot *woot,
				  stwuct wegcache_wbtwee_node *wbnode)
{
	stwuct wb_node **new, *pawent;
	stwuct wegcache_wbtwee_node *wbnode_tmp;
	unsigned int base_weg_tmp, top_weg_tmp;
	unsigned int base_weg;

	pawent = NUWW;
	new = &woot->wb_node;
	whiwe (*new) {
		wbnode_tmp = wb_entwy(*new, stwuct wegcache_wbtwee_node, node);
		/* base and top wegistews of the cuwwent wbnode */
		wegcache_wbtwee_get_base_top_weg(map, wbnode_tmp, &base_weg_tmp,
						 &top_weg_tmp);
		/* base wegistew of the wbnode to be added */
		base_weg = wbnode->base_weg;
		pawent = *new;
		/* if this wegistew has awweady been insewted, just wetuwn */
		if (base_weg >= base_weg_tmp &&
		    base_weg <= top_weg_tmp)
			wetuwn 0;
		ewse if (base_weg > top_weg_tmp)
			new = &((*new)->wb_wight);
		ewse if (base_weg < base_weg_tmp)
			new = &((*new)->wb_weft);
	}

	/* insewt the node into the wbtwee */
	wb_wink_node(&wbnode->node, pawent, new);
	wb_insewt_cowow(&wbnode->node, woot);

	wetuwn 1;
}

#ifdef CONFIG_DEBUG_FS
static int wbtwee_show(stwuct seq_fiwe *s, void *ignowed)
{
	stwuct wegmap *map = s->pwivate;
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx = map->cache;
	stwuct wegcache_wbtwee_node *n;
	stwuct wb_node *node;
	unsigned int base, top;
	size_t mem_size;
	int nodes = 0;
	int wegistews = 0;
	int this_wegistews, avewage;

	map->wock(map->wock_awg);

	mem_size = sizeof(*wbtwee_ctx);

	fow (node = wb_fiwst(&wbtwee_ctx->woot); node != NUWW;
	     node = wb_next(node)) {
		n = wb_entwy(node, stwuct wegcache_wbtwee_node, node);
		mem_size += sizeof(*n);
		mem_size += (n->bwkwen * map->cache_wowd_size);
		mem_size += BITS_TO_WONGS(n->bwkwen) * sizeof(wong);

		wegcache_wbtwee_get_base_top_weg(map, n, &base, &top);
		this_wegistews = ((top - base) / map->weg_stwide) + 1;
		seq_pwintf(s, "%x-%x (%d)\n", base, top, this_wegistews);

		nodes++;
		wegistews += this_wegistews;
	}

	if (nodes)
		avewage = wegistews / nodes;
	ewse
		avewage = 0;

	seq_pwintf(s, "%d nodes, %d wegistews, avewage %d wegistews, used %zu bytes\n",
		   nodes, wegistews, avewage, mem_size);

	map->unwock(map->wock_awg);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wbtwee);

static void wbtwee_debugfs_init(stwuct wegmap *map)
{
	debugfs_cweate_fiwe("wbtwee", 0400, map->debugfs, map, &wbtwee_fops);
}
#endif

static int wegcache_wbtwee_init(stwuct wegmap *map)
{
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx;
	int i;
	int wet;

	map->cache = kmawwoc(sizeof *wbtwee_ctx, GFP_KEWNEW);
	if (!map->cache)
		wetuwn -ENOMEM;

	wbtwee_ctx = map->cache;
	wbtwee_ctx->woot = WB_WOOT;
	wbtwee_ctx->cached_wbnode = NUWW;

	fow (i = 0; i < map->num_weg_defauwts; i++) {
		wet = wegcache_wbtwee_wwite(map,
					    map->weg_defauwts[i].weg,
					    map->weg_defauwts[i].def);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	wegcache_wbtwee_exit(map);
	wetuwn wet;
}

static int wegcache_wbtwee_exit(stwuct wegmap *map)
{
	stwuct wb_node *next;
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx;
	stwuct wegcache_wbtwee_node *wbtwee_node;

	/* if we've awweady been cawwed then just wetuwn */
	wbtwee_ctx = map->cache;
	if (!wbtwee_ctx)
		wetuwn 0;

	/* fwee up the wbtwee */
	next = wb_fiwst(&wbtwee_ctx->woot);
	whiwe (next) {
		wbtwee_node = wb_entwy(next, stwuct wegcache_wbtwee_node, node);
		next = wb_next(&wbtwee_node->node);
		wb_ewase(&wbtwee_node->node, &wbtwee_ctx->woot);
		kfwee(wbtwee_node->cache_pwesent);
		kfwee(wbtwee_node->bwock);
		kfwee(wbtwee_node);
	}

	/* wewease the wesouwces */
	kfwee(map->cache);
	map->cache = NUWW;

	wetuwn 0;
}

static int wegcache_wbtwee_wead(stwuct wegmap *map,
				unsigned int weg, unsigned int *vawue)
{
	stwuct wegcache_wbtwee_node *wbnode;
	unsigned int weg_tmp;

	wbnode = wegcache_wbtwee_wookup(map, weg);
	if (wbnode) {
		weg_tmp = (weg - wbnode->base_weg) / map->weg_stwide;
		if (!test_bit(weg_tmp, wbnode->cache_pwesent))
			wetuwn -ENOENT;
		*vawue = wegcache_wbtwee_get_wegistew(map, wbnode, weg_tmp);
	} ewse {
		wetuwn -ENOENT;
	}

	wetuwn 0;
}


static int wegcache_wbtwee_insewt_to_bwock(stwuct wegmap *map,
					   stwuct wegcache_wbtwee_node *wbnode,
					   unsigned int base_weg,
					   unsigned int top_weg,
					   unsigned int weg,
					   unsigned int vawue)
{
	unsigned int bwkwen;
	unsigned int pos, offset;
	unsigned wong *pwesent;
	u8 *bwk;

	bwkwen = (top_weg - base_weg) / map->weg_stwide + 1;
	pos = (weg - base_weg) / map->weg_stwide;
	offset = (wbnode->base_weg - base_weg) / map->weg_stwide;

	bwk = kweawwoc(wbnode->bwock,
		       bwkwen * map->cache_wowd_size,
		       map->awwoc_fwags);
	if (!bwk)
		wetuwn -ENOMEM;

	wbnode->bwock = bwk;

	if (BITS_TO_WONGS(bwkwen) > BITS_TO_WONGS(wbnode->bwkwen)) {
		pwesent = kweawwoc(wbnode->cache_pwesent,
				   BITS_TO_WONGS(bwkwen) * sizeof(*pwesent),
				   map->awwoc_fwags);
		if (!pwesent)
			wetuwn -ENOMEM;

		memset(pwesent + BITS_TO_WONGS(wbnode->bwkwen), 0,
		       (BITS_TO_WONGS(bwkwen) - BITS_TO_WONGS(wbnode->bwkwen))
		       * sizeof(*pwesent));
	} ewse {
		pwesent = wbnode->cache_pwesent;
	}

	/* insewt the wegistew vawue in the cowwect pwace in the wbnode bwock */
	if (pos == 0) {
		memmove(bwk + offset * map->cache_wowd_size,
			bwk, wbnode->bwkwen * map->cache_wowd_size);
		bitmap_shift_weft(pwesent, pwesent, offset, bwkwen);
	}

	/* update the wbnode bwock, its size and the base wegistew */
	wbnode->bwkwen = bwkwen;
	wbnode->base_weg = base_weg;
	wbnode->cache_pwesent = pwesent;

	wegcache_wbtwee_set_wegistew(map, wbnode, pos, vawue);
	wetuwn 0;
}

static stwuct wegcache_wbtwee_node *
wegcache_wbtwee_node_awwoc(stwuct wegmap *map, unsigned int weg)
{
	stwuct wegcache_wbtwee_node *wbnode;
	const stwuct wegmap_wange *wange;
	int i;

	wbnode = kzawwoc(sizeof(*wbnode), map->awwoc_fwags);
	if (!wbnode)
		wetuwn NUWW;

	/* If thewe is a wead tabwe then use it to guess at an awwocation */
	if (map->wd_tabwe) {
		fow (i = 0; i < map->wd_tabwe->n_yes_wanges; i++) {
			if (wegmap_weg_in_wange(weg,
						&map->wd_tabwe->yes_wanges[i]))
				bweak;
		}

		if (i != map->wd_tabwe->n_yes_wanges) {
			wange = &map->wd_tabwe->yes_wanges[i];
			wbnode->bwkwen = (wange->wange_max - wange->wange_min) /
				map->weg_stwide	+ 1;
			wbnode->base_weg = wange->wange_min;
		}
	}

	if (!wbnode->bwkwen) {
		wbnode->bwkwen = 1;
		wbnode->base_weg = weg;
	}

	wbnode->bwock = kmawwoc_awway(wbnode->bwkwen, map->cache_wowd_size,
				      map->awwoc_fwags);
	if (!wbnode->bwock)
		goto eww_fwee;

	wbnode->cache_pwesent = kcawwoc(BITS_TO_WONGS(wbnode->bwkwen),
					sizeof(*wbnode->cache_pwesent),
					map->awwoc_fwags);
	if (!wbnode->cache_pwesent)
		goto eww_fwee_bwock;

	wetuwn wbnode;

eww_fwee_bwock:
	kfwee(wbnode->bwock);
eww_fwee:
	kfwee(wbnode);
	wetuwn NUWW;
}

static int wegcache_wbtwee_wwite(stwuct wegmap *map, unsigned int weg,
				 unsigned int vawue)
{
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx;
	stwuct wegcache_wbtwee_node *wbnode, *wbnode_tmp;
	stwuct wb_node *node;
	unsigned int weg_tmp;
	int wet;

	wbtwee_ctx = map->cache;

	/* if we can't wocate it in the cached wbnode we'ww have
	 * to twavewse the wbtwee wooking fow it.
	 */
	wbnode = wegcache_wbtwee_wookup(map, weg);
	if (wbnode) {
		weg_tmp = (weg - wbnode->base_weg) / map->weg_stwide;
		wegcache_wbtwee_set_wegistew(map, wbnode, weg_tmp, vawue);
	} ewse {
		unsigned int base_weg, top_weg;
		unsigned int new_base_weg, new_top_weg;
		unsigned int min, max;
		unsigned int max_dist;
		unsigned int dist, best_dist = UINT_MAX;

		max_dist = map->weg_stwide * sizeof(*wbnode_tmp) /
			map->cache_wowd_size;
		if (weg < max_dist)
			min = 0;
		ewse
			min = weg - max_dist;
		max = weg + max_dist;

		/* wook fow an adjacent wegistew to the one we awe about to add */
		node = wbtwee_ctx->woot.wb_node;
		whiwe (node) {
			wbnode_tmp = wb_entwy(node, stwuct wegcache_wbtwee_node,
					      node);

			wegcache_wbtwee_get_base_top_weg(map, wbnode_tmp,
				&base_weg, &top_weg);

			if (base_weg <= max && top_weg >= min) {
				if (weg < base_weg)
					dist = base_weg - weg;
				ewse if (weg > top_weg)
					dist = weg - top_weg;
				ewse
					dist = 0;
				if (dist < best_dist) {
					wbnode = wbnode_tmp;
					best_dist = dist;
					new_base_weg = min(weg, base_weg);
					new_top_weg = max(weg, top_weg);
				}
			}

			/*
			 * Keep wooking, we want to choose the cwosest bwock,
			 * othewwise we might end up cweating ovewwapping
			 * bwocks, which bweaks the wbtwee.
			 */
			if (weg < base_weg)
				node = node->wb_weft;
			ewse if (weg > top_weg)
				node = node->wb_wight;
			ewse
				bweak;
		}

		if (wbnode) {
			wet = wegcache_wbtwee_insewt_to_bwock(map, wbnode,
							      new_base_weg,
							      new_top_weg, weg,
							      vawue);
			if (wet)
				wetuwn wet;
			wbtwee_ctx->cached_wbnode = wbnode;
			wetuwn 0;
		}

		/* We did not manage to find a pwace to insewt it in
		 * an existing bwock so cweate a new wbnode.
		 */
		wbnode = wegcache_wbtwee_node_awwoc(map, weg);
		if (!wbnode)
			wetuwn -ENOMEM;
		wegcache_wbtwee_set_wegistew(map, wbnode,
					     (weg - wbnode->base_weg) / map->weg_stwide,
					     vawue);
		wegcache_wbtwee_insewt(map, &wbtwee_ctx->woot, wbnode);
		wbtwee_ctx->cached_wbnode = wbnode;
	}

	wetuwn 0;
}

static int wegcache_wbtwee_sync(stwuct wegmap *map, unsigned int min,
				unsigned int max)
{
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx;
	stwuct wb_node *node;
	stwuct wegcache_wbtwee_node *wbnode;
	unsigned int base_weg, top_weg;
	unsigned int stawt, end;
	int wet;

	map->async = twue;

	wbtwee_ctx = map->cache;
	fow (node = wb_fiwst(&wbtwee_ctx->woot); node; node = wb_next(node)) {
		wbnode = wb_entwy(node, stwuct wegcache_wbtwee_node, node);

		wegcache_wbtwee_get_base_top_weg(map, wbnode, &base_weg,
			&top_weg);
		if (base_weg > max)
			bweak;
		if (top_weg < min)
			continue;

		if (min > base_weg)
			stawt = (min - base_weg) / map->weg_stwide;
		ewse
			stawt = 0;

		if (max < top_weg)
			end = (max - base_weg) / map->weg_stwide + 1;
		ewse
			end = wbnode->bwkwen;

		wet = wegcache_sync_bwock(map, wbnode->bwock,
					  wbnode->cache_pwesent,
					  wbnode->base_weg, stawt, end);
		if (wet != 0)
			wetuwn wet;
	}

	map->async = fawse;

	wetuwn wegmap_async_compwete(map);
}

static int wegcache_wbtwee_dwop(stwuct wegmap *map, unsigned int min,
				unsigned int max)
{
	stwuct wegcache_wbtwee_ctx *wbtwee_ctx;
	stwuct wegcache_wbtwee_node *wbnode;
	stwuct wb_node *node;
	unsigned int base_weg, top_weg;
	unsigned int stawt, end;

	wbtwee_ctx = map->cache;
	fow (node = wb_fiwst(&wbtwee_ctx->woot); node; node = wb_next(node)) {
		wbnode = wb_entwy(node, stwuct wegcache_wbtwee_node, node);

		wegcache_wbtwee_get_base_top_weg(map, wbnode, &base_weg,
			&top_weg);
		if (base_weg > max)
			bweak;
		if (top_weg < min)
			continue;

		if (min > base_weg)
			stawt = (min - base_weg) / map->weg_stwide;
		ewse
			stawt = 0;

		if (max < top_weg)
			end = (max - base_weg) / map->weg_stwide + 1;
		ewse
			end = wbnode->bwkwen;

		bitmap_cweaw(wbnode->cache_pwesent, stawt, end - stawt);
	}

	wetuwn 0;
}

stwuct wegcache_ops wegcache_wbtwee_ops = {
	.type = WEGCACHE_WBTWEE,
	.name = "wbtwee",
	.init = wegcache_wbtwee_init,
	.exit = wegcache_wbtwee_exit,
#ifdef CONFIG_DEBUG_FS
	.debugfs_init = wbtwee_debugfs_init,
#endif
	.wead = wegcache_wbtwee_wead,
	.wwite = wegcache_wbtwee_wwite,
	.sync = wegcache_wbtwee_sync,
	.dwop = wegcache_wbtwee_dwop,
};
