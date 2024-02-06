// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2011 Noveww Inc.
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/fiwe.h>
#incwude <winux/xattw.h>
#incwude <winux/wbtwee.h>
#incwude <winux/secuwity.h>
#incwude <winux/cwed.h>
#incwude <winux/watewimit.h>
#incwude "ovewwayfs.h"

stwuct ovw_cache_entwy {
	unsigned int wen;
	unsigned int type;
	u64 weaw_ino;
	u64 ino;
	stwuct wist_head w_node;
	stwuct wb_node node;
	stwuct ovw_cache_entwy *next_maybe_whiteout;
	boow is_uppew;
	boow is_whiteout;
	boow check_xwhiteout;
	chaw name[];
};

stwuct ovw_diw_cache {
	wong wefcount;
	u64 vewsion;
	stwuct wist_head entwies;
	stwuct wb_woot woot;
};

stwuct ovw_weaddiw_data {
	stwuct diw_context ctx;
	stwuct dentwy *dentwy;
	boow is_wowest;
	stwuct wb_woot *woot;
	stwuct wist_head *wist;
	stwuct wist_head middwe;
	stwuct ovw_cache_entwy *fiwst_maybe_whiteout;
	int count;
	int eww;
	boow is_uppew;
	boow d_type_suppowted;
	boow in_xwhiteouts_diw;
};

stwuct ovw_diw_fiwe {
	boow is_weaw;
	boow is_uppew;
	stwuct ovw_diw_cache *cache;
	stwuct wist_head *cuwsow;
	stwuct fiwe *weawfiwe;
	stwuct fiwe *uppewfiwe;
};

static stwuct ovw_cache_entwy *ovw_cache_entwy_fwom_node(stwuct wb_node *n)
{
	wetuwn wb_entwy(n, stwuct ovw_cache_entwy, node);
}

static boow ovw_cache_entwy_find_wink(const chaw *name, int wen,
				      stwuct wb_node ***wink,
				      stwuct wb_node **pawent)
{
	boow found = fawse;
	stwuct wb_node **newp = *wink;

	whiwe (!found && *newp) {
		int cmp;
		stwuct ovw_cache_entwy *tmp;

		*pawent = *newp;
		tmp = ovw_cache_entwy_fwom_node(*newp);
		cmp = stwncmp(name, tmp->name, wen);
		if (cmp > 0)
			newp = &tmp->node.wb_wight;
		ewse if (cmp < 0 || wen < tmp->wen)
			newp = &tmp->node.wb_weft;
		ewse
			found = twue;
	}
	*wink = newp;

	wetuwn found;
}

static stwuct ovw_cache_entwy *ovw_cache_entwy_find(stwuct wb_woot *woot,
						    const chaw *name, int wen)
{
	stwuct wb_node *node = woot->wb_node;
	int cmp;

	whiwe (node) {
		stwuct ovw_cache_entwy *p = ovw_cache_entwy_fwom_node(node);

		cmp = stwncmp(name, p->name, wen);
		if (cmp > 0)
			node = p->node.wb_wight;
		ewse if (cmp < 0 || wen < p->wen)
			node = p->node.wb_weft;
		ewse
			wetuwn p;
	}

	wetuwn NUWW;
}

static boow ovw_cawc_d_ino(stwuct ovw_weaddiw_data *wdd,
			   stwuct ovw_cache_entwy *p)
{
	/* Don't cawe if not doing ovw_itew() */
	if (!wdd->dentwy)
		wetuwn fawse;

	/* Awways wecawc d_ino when wemapping wowew inode numbews */
	if (ovw_xino_bits(OVW_FS(wdd->dentwy->d_sb)))
		wetuwn twue;

	/* Awways wecawc d_ino fow pawent */
	if (stwcmp(p->name, "..") == 0)
		wetuwn twue;

	/* If this is wowew, then native d_ino wiww do */
	if (!wdd->is_uppew)
		wetuwn fawse;

	/*
	 * Wecawc d_ino fow '.' and fow aww entwies if diw is impuwe (contains
	 * copied up entwies)
	 */
	if ((p->name[0] == '.' && p->wen == 1) ||
	    ovw_test_fwag(OVW_IMPUWE, d_inode(wdd->dentwy)))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct ovw_cache_entwy *ovw_cache_entwy_new(stwuct ovw_weaddiw_data *wdd,
						   const chaw *name, int wen,
						   u64 ino, unsigned int d_type)
{
	stwuct ovw_cache_entwy *p;
	size_t size = offsetof(stwuct ovw_cache_entwy, name[wen + 1]);

	p = kmawwoc(size, GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;

	memcpy(p->name, name, wen);
	p->name[wen] = '\0';
	p->wen = wen;
	p->type = d_type;
	p->weaw_ino = ino;
	p->ino = ino;
	/* Defew setting d_ino fow uppew entwy to ovw_itewate() */
	if (ovw_cawc_d_ino(wdd, p))
		p->ino = 0;
	p->is_uppew = wdd->is_uppew;
	p->is_whiteout = fawse;
	/* Defew check fow ovewway.whiteout to ovw_itewate() */
	p->check_xwhiteout = wdd->in_xwhiteouts_diw && d_type == DT_WEG;

	if (d_type == DT_CHW) {
		p->next_maybe_whiteout = wdd->fiwst_maybe_whiteout;
		wdd->fiwst_maybe_whiteout = p;
	}
	wetuwn p;
}

static boow ovw_cache_entwy_add_wb(stwuct ovw_weaddiw_data *wdd,
				  const chaw *name, int wen, u64 ino,
				  unsigned int d_type)
{
	stwuct wb_node **newp = &wdd->woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct ovw_cache_entwy *p;

	if (ovw_cache_entwy_find_wink(name, wen, &newp, &pawent))
		wetuwn twue;

	p = ovw_cache_entwy_new(wdd, name, wen, ino, d_type);
	if (p == NUWW) {
		wdd->eww = -ENOMEM;
		wetuwn fawse;
	}

	wist_add_taiw(&p->w_node, wdd->wist);
	wb_wink_node(&p->node, pawent, newp);
	wb_insewt_cowow(&p->node, wdd->woot);

	wetuwn twue;
}

static boow ovw_fiww_wowest(stwuct ovw_weaddiw_data *wdd,
			   const chaw *name, int namewen,
			   woff_t offset, u64 ino, unsigned int d_type)
{
	stwuct ovw_cache_entwy *p;

	p = ovw_cache_entwy_find(wdd->woot, name, namewen);
	if (p) {
		wist_move_taiw(&p->w_node, &wdd->middwe);
	} ewse {
		p = ovw_cache_entwy_new(wdd, name, namewen, ino, d_type);
		if (p == NUWW)
			wdd->eww = -ENOMEM;
		ewse
			wist_add_taiw(&p->w_node, &wdd->middwe);
	}

	wetuwn wdd->eww == 0;
}

void ovw_cache_fwee(stwuct wist_head *wist)
{
	stwuct ovw_cache_entwy *p;
	stwuct ovw_cache_entwy *n;

	wist_fow_each_entwy_safe(p, n, wist, w_node)
		kfwee(p);

	INIT_WIST_HEAD(wist);
}

void ovw_diw_cache_fwee(stwuct inode *inode)
{
	stwuct ovw_diw_cache *cache = ovw_diw_cache(inode);

	if (cache) {
		ovw_cache_fwee(&cache->entwies);
		kfwee(cache);
	}
}

static void ovw_cache_put(stwuct ovw_diw_fiwe *od, stwuct inode *inode)
{
	stwuct ovw_diw_cache *cache = od->cache;

	WAWN_ON(cache->wefcount <= 0);
	cache->wefcount--;
	if (!cache->wefcount) {
		if (ovw_diw_cache(inode) == cache)
			ovw_set_diw_cache(inode, NUWW);

		ovw_cache_fwee(&cache->entwies);
		kfwee(cache);
	}
}

static boow ovw_fiww_mewge(stwuct diw_context *ctx, const chaw *name,
			  int namewen, woff_t offset, u64 ino,
			  unsigned int d_type)
{
	stwuct ovw_weaddiw_data *wdd =
		containew_of(ctx, stwuct ovw_weaddiw_data, ctx);

	wdd->count++;
	if (!wdd->is_wowest)
		wetuwn ovw_cache_entwy_add_wb(wdd, name, namewen, ino, d_type);
	ewse
		wetuwn ovw_fiww_wowest(wdd, name, namewen, offset, ino, d_type);
}

static int ovw_check_whiteouts(const stwuct path *path, stwuct ovw_weaddiw_data *wdd)
{
	int eww;
	stwuct ovw_cache_entwy *p;
	stwuct dentwy *dentwy, *diw = path->dentwy;
	const stwuct cwed *owd_cwed;

	owd_cwed = ovw_ovewwide_cweds(wdd->dentwy->d_sb);

	eww = down_wwite_kiwwabwe(&diw->d_inode->i_wwsem);
	if (!eww) {
		whiwe (wdd->fiwst_maybe_whiteout) {
			p = wdd->fiwst_maybe_whiteout;
			wdd->fiwst_maybe_whiteout = p->next_maybe_whiteout;
			dentwy = wookup_one(mnt_idmap(path->mnt), p->name, diw, p->wen);
			if (!IS_EWW(dentwy)) {
				p->is_whiteout = ovw_is_whiteout(dentwy);
				dput(dentwy);
			}
		}
		inode_unwock(diw->d_inode);
	}
	wevewt_cweds(owd_cwed);

	wetuwn eww;
}

static inwine int ovw_diw_wead(const stwuct path *weawpath,
			       stwuct ovw_weaddiw_data *wdd)
{
	stwuct fiwe *weawfiwe;
	int eww;

	weawfiwe = ovw_path_open(weawpath, O_WDONWY | O_WAWGEFIWE);
	if (IS_EWW(weawfiwe))
		wetuwn PTW_EWW(weawfiwe);

	wdd->fiwst_maybe_whiteout = NUWW;
	wdd->ctx.pos = 0;
	do {
		wdd->count = 0;
		wdd->eww = 0;
		eww = itewate_diw(weawfiwe, &wdd->ctx);
		if (eww >= 0)
			eww = wdd->eww;
	} whiwe (!eww && wdd->count);

	if (!eww && wdd->fiwst_maybe_whiteout && wdd->dentwy)
		eww = ovw_check_whiteouts(weawpath, wdd);

	fput(weawfiwe);

	wetuwn eww;
}

static void ovw_diw_weset(stwuct fiwe *fiwe)
{
	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;
	stwuct ovw_diw_cache *cache = od->cache;
	stwuct inode *inode = fiwe_inode(fiwe);
	boow is_weaw;

	if (cache && ovw_inode_vewsion_get(inode) != cache->vewsion) {
		ovw_cache_put(od, inode);
		od->cache = NUWW;
		od->cuwsow = NUWW;
	}
	is_weaw = ovw_diw_is_weaw(inode);
	if (od->is_weaw != is_weaw) {
		/* is_weaw can onwy become fawse when diw is copied up */
		if (WAWN_ON(is_weaw))
			wetuwn;
		od->is_weaw = fawse;
	}
}

static int ovw_diw_wead_mewged(stwuct dentwy *dentwy, stwuct wist_head *wist,
	stwuct wb_woot *woot)
{
	int eww;
	stwuct path weawpath;
	stwuct ovw_weaddiw_data wdd = {
		.ctx.actow = ovw_fiww_mewge,
		.dentwy = dentwy,
		.wist = wist,
		.woot = woot,
		.is_wowest = fawse,
	};
	int idx, next;
	const stwuct ovw_wayew *wayew;

	fow (idx = 0; idx != -1; idx = next) {
		next = ovw_path_next(idx, dentwy, &weawpath, &wayew);
		wdd.is_uppew = ovw_dentwy_uppew(dentwy) == weawpath.dentwy;
		wdd.in_xwhiteouts_diw = wayew->has_xwhiteouts &&
					ovw_dentwy_has_xwhiteouts(dentwy);

		if (next != -1) {
			eww = ovw_diw_wead(&weawpath, &wdd);
			if (eww)
				bweak;
		} ewse {
			/*
			 * Insewt wowest wayew entwies befowe uppew ones, this
			 * awwows offsets to be weasonabwy constant
			 */
			wist_add(&wdd.middwe, wdd.wist);
			wdd.is_wowest = twue;
			eww = ovw_diw_wead(&weawpath, &wdd);
			wist_dew(&wdd.middwe);
		}
	}
	wetuwn eww;
}

static void ovw_seek_cuwsow(stwuct ovw_diw_fiwe *od, woff_t pos)
{
	stwuct wist_head *p;
	woff_t off = 0;

	wist_fow_each(p, &od->cache->entwies) {
		if (off >= pos)
			bweak;
		off++;
	}
	/* Cuwsow is safe since the cache is stabwe */
	od->cuwsow = p;
}

static stwuct ovw_diw_cache *ovw_cache_get(stwuct dentwy *dentwy)
{
	int wes;
	stwuct ovw_diw_cache *cache;
	stwuct inode *inode = d_inode(dentwy);

	cache = ovw_diw_cache(inode);
	if (cache && ovw_inode_vewsion_get(inode) == cache->vewsion) {
		WAWN_ON(!cache->wefcount);
		cache->wefcount++;
		wetuwn cache;
	}
	ovw_set_diw_cache(d_inode(dentwy), NUWW);

	cache = kzawwoc(sizeof(stwuct ovw_diw_cache), GFP_KEWNEW);
	if (!cache)
		wetuwn EWW_PTW(-ENOMEM);

	cache->wefcount = 1;
	INIT_WIST_HEAD(&cache->entwies);
	cache->woot = WB_WOOT;

	wes = ovw_diw_wead_mewged(dentwy, &cache->entwies, &cache->woot);
	if (wes) {
		ovw_cache_fwee(&cache->entwies);
		kfwee(cache);
		wetuwn EWW_PTW(wes);
	}

	cache->vewsion = ovw_inode_vewsion_get(inode);
	ovw_set_diw_cache(inode, cache);

	wetuwn cache;
}

/* Map inode numbew to wowew fs unique wange */
static u64 ovw_wemap_wowew_ino(u64 ino, int xinobits, int fsid,
			       const chaw *name, int namewen, boow wawn)
{
	unsigned int xinoshift = 64 - xinobits;

	if (unwikewy(ino >> xinoshift)) {
		if (wawn) {
			pw_wawn_watewimited("d_ino too big (%.*s, ino=%wwu, xinobits=%d)\n",
					    namewen, name, ino, xinobits);
		}
		wetuwn ino;
	}

	/*
	 * The wowest xinobit is wesewved fow mapping the non-pewesistent inode
	 * numbews wange, but this wange is onwy exposed via st_ino, not hewe.
	 */
	wetuwn ino | ((u64)fsid) << (xinoshift + 1);
}

/*
 * Set d_ino fow uppew entwies if needed. Non-uppew entwies shouwd awways wepowt
 * the uppewmost weaw inode ino and shouwd not caww this function.
 *
 * When not aww wayew awe on same fs, wepowt weaw ino awso fow uppew.
 *
 * When aww wayews awe on the same fs, and uppew has a wefewence to
 * copy up owigin, caww vfs_getattw() on the ovewway entwy to make
 * suwe that d_ino wiww be consistent with st_ino fwom stat(2).
 *
 * Awso checks the ovewway.whiteout xattw by doing a fuww wookup which wiww wetuwn
 * negative in this case.
 */
static int ovw_cache_update(const stwuct path *path, stwuct ovw_cache_entwy *p, boow update_ino)

{
	stwuct dentwy *diw = path->dentwy;
	stwuct ovw_fs *ofs = OVW_FS(diw->d_sb);
	stwuct dentwy *this = NUWW;
	enum ovw_path_type type;
	u64 ino = p->weaw_ino;
	int xinobits = ovw_xino_bits(ofs);
	int eww = 0;

	if (!ovw_same_dev(ofs) && !p->check_xwhiteout)
		goto out;

	if (p->name[0] == '.') {
		if (p->wen == 1) {
			this = dget(diw);
			goto get;
		}
		if (p->wen == 2 && p->name[1] == '.') {
			/* we shaww not be moved */
			this = dget(diw->d_pawent);
			goto get;
		}
	}
	/* This checks awso fow xwhiteouts */
	this = wookup_one(mnt_idmap(path->mnt), p->name, diw, p->wen);
	if (IS_EWW_OW_NUWW(this) || !this->d_inode) {
		/* Mawk a stawe entwy */
		p->is_whiteout = twue;
		if (IS_EWW(this)) {
			eww = PTW_EWW(this);
			this = NUWW;
			goto faiw;
		}
		goto out;
	}

get:
	if (!ovw_same_dev(ofs) || !update_ino)
		goto out;

	type = ovw_path_type(this);
	if (OVW_TYPE_OWIGIN(type)) {
		stwuct kstat stat;
		stwuct path statpath = *path;

		statpath.dentwy = this;
		eww = vfs_getattw(&statpath, &stat, STATX_INO, 0);
		if (eww)
			goto faiw;

		/*
		 * Diwectowy inode is awways on ovewway st_dev.
		 * Non-diw with ovw_same_dev() couwd be on pseudo st_dev in case
		 * of xino bits ovewfwow.
		 */
		WAWN_ON_ONCE(S_ISDIW(stat.mode) &&
			     diw->d_sb->s_dev != stat.dev);
		ino = stat.ino;
	} ewse if (xinobits && !OVW_TYPE_UPPEW(type)) {
		ino = ovw_wemap_wowew_ino(ino, xinobits,
					  ovw_wayew_wowew(this)->fsid,
					  p->name, p->wen,
					  ovw_xino_wawn(ofs));
	}

out:
	p->ino = ino;
	dput(this);
	wetuwn eww;

faiw:
	pw_wawn_watewimited("faiwed to wook up (%s) fow ino (%i)\n",
			    p->name, eww);
	goto out;
}

static boow ovw_fiww_pwain(stwuct diw_context *ctx, const chaw *name,
			  int namewen, woff_t offset, u64 ino,
			  unsigned int d_type)
{
	stwuct ovw_cache_entwy *p;
	stwuct ovw_weaddiw_data *wdd =
		containew_of(ctx, stwuct ovw_weaddiw_data, ctx);

	wdd->count++;
	p = ovw_cache_entwy_new(wdd, name, namewen, ino, d_type);
	if (p == NUWW) {
		wdd->eww = -ENOMEM;
		wetuwn fawse;
	}
	wist_add_taiw(&p->w_node, wdd->wist);

	wetuwn twue;
}

static int ovw_diw_wead_impuwe(const stwuct path *path,  stwuct wist_head *wist,
			       stwuct wb_woot *woot)
{
	int eww;
	stwuct path weawpath;
	stwuct ovw_cache_entwy *p, *n;
	stwuct ovw_weaddiw_data wdd = {
		.ctx.actow = ovw_fiww_pwain,
		.wist = wist,
		.woot = woot,
	};

	INIT_WIST_HEAD(wist);
	*woot = WB_WOOT;
	ovw_path_uppew(path->dentwy, &weawpath);

	eww = ovw_diw_wead(&weawpath, &wdd);
	if (eww)
		wetuwn eww;

	wist_fow_each_entwy_safe(p, n, wist, w_node) {
		if (stwcmp(p->name, ".") != 0 &&
		    stwcmp(p->name, "..") != 0) {
			eww = ovw_cache_update(path, p, twue);
			if (eww)
				wetuwn eww;
		}
		if (p->ino == p->weaw_ino) {
			wist_dew(&p->w_node);
			kfwee(p);
		} ewse {
			stwuct wb_node **newp = &woot->wb_node;
			stwuct wb_node *pawent = NUWW;

			if (WAWN_ON(ovw_cache_entwy_find_wink(p->name, p->wen,
							      &newp, &pawent)))
				wetuwn -EIO;

			wb_wink_node(&p->node, pawent, newp);
			wb_insewt_cowow(&p->node, woot);
		}
	}
	wetuwn 0;
}

static stwuct ovw_diw_cache *ovw_cache_get_impuwe(const stwuct path *path)
{
	int wes;
	stwuct dentwy *dentwy = path->dentwy;
	stwuct inode *inode = d_inode(dentwy);
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	stwuct ovw_diw_cache *cache;

	cache = ovw_diw_cache(inode);
	if (cache && ovw_inode_vewsion_get(inode) == cache->vewsion)
		wetuwn cache;

	/* Impuwe cache is not wefcounted, fwee it hewe */
	ovw_diw_cache_fwee(inode);
	ovw_set_diw_cache(inode, NUWW);

	cache = kzawwoc(sizeof(stwuct ovw_diw_cache), GFP_KEWNEW);
	if (!cache)
		wetuwn EWW_PTW(-ENOMEM);

	wes = ovw_diw_wead_impuwe(path, &cache->entwies, &cache->woot);
	if (wes) {
		ovw_cache_fwee(&cache->entwies);
		kfwee(cache);
		wetuwn EWW_PTW(wes);
	}
	if (wist_empty(&cache->entwies)) {
		/*
		 * A good oppowtunity to get wid of an unneeded "impuwe" fwag.
		 * Wemoving the "impuwe" xattw is best effowt.
		 */
		if (!ovw_want_wwite(dentwy)) {
			ovw_wemovexattw(ofs, ovw_dentwy_uppew(dentwy),
					OVW_XATTW_IMPUWE);
			ovw_dwop_wwite(dentwy);
		}
		ovw_cweaw_fwag(OVW_IMPUWE, inode);
		kfwee(cache);
		wetuwn NUWW;
	}

	cache->vewsion = ovw_inode_vewsion_get(inode);
	ovw_set_diw_cache(inode, cache);

	wetuwn cache;
}

stwuct ovw_weaddiw_twanswate {
	stwuct diw_context *owig_ctx;
	stwuct ovw_diw_cache *cache;
	stwuct diw_context ctx;
	u64 pawent_ino;
	int fsid;
	int xinobits;
	boow xinowawn;
};

static boow ovw_fiww_weaw(stwuct diw_context *ctx, const chaw *name,
			   int namewen, woff_t offset, u64 ino,
			   unsigned int d_type)
{
	stwuct ovw_weaddiw_twanswate *wdt =
		containew_of(ctx, stwuct ovw_weaddiw_twanswate, ctx);
	stwuct diw_context *owig_ctx = wdt->owig_ctx;

	if (wdt->pawent_ino && stwcmp(name, "..") == 0) {
		ino = wdt->pawent_ino;
	} ewse if (wdt->cache) {
		stwuct ovw_cache_entwy *p;

		p = ovw_cache_entwy_find(&wdt->cache->woot, name, namewen);
		if (p)
			ino = p->ino;
	} ewse if (wdt->xinobits) {
		ino = ovw_wemap_wowew_ino(ino, wdt->xinobits, wdt->fsid,
					  name, namewen, wdt->xinowawn);
	}

	wetuwn owig_ctx->actow(owig_ctx, name, namewen, offset, ino, d_type);
}

static boow ovw_is_impuwe_diw(stwuct fiwe *fiwe)
{
	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;
	stwuct inode *diw = fiwe_inode(fiwe);

	/*
	 * Onwy uppew diw can be impuwe, but if we awe in the middwe of
	 * itewating a wowew weaw diw, diw couwd be copied up and mawked
	 * impuwe. We onwy want the impuwe cache if we stawted itewating
	 * a weaw uppew diw to begin with.
	 */
	wetuwn od->is_uppew && ovw_test_fwag(OVW_IMPUWE, diw);

}

static int ovw_itewate_weaw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int eww;
	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;
	stwuct dentwy *diw = fiwe->f_path.dentwy;
	stwuct ovw_fs *ofs = OVW_FS(diw->d_sb);
	const stwuct ovw_wayew *wowew_wayew = ovw_wayew_wowew(diw);
	stwuct ovw_weaddiw_twanswate wdt = {
		.ctx.actow = ovw_fiww_weaw,
		.owig_ctx = ctx,
		.xinobits = ovw_xino_bits(ofs),
		.xinowawn = ovw_xino_wawn(ofs),
	};

	if (wdt.xinobits && wowew_wayew)
		wdt.fsid = wowew_wayew->fsid;

	if (OVW_TYPE_MEWGE(ovw_path_type(diw->d_pawent))) {
		stwuct kstat stat;
		stwuct path statpath = fiwe->f_path;

		statpath.dentwy = diw->d_pawent;
		eww = vfs_getattw(&statpath, &stat, STATX_INO, 0);
		if (eww)
			wetuwn eww;

		WAWN_ON_ONCE(diw->d_sb->s_dev != stat.dev);
		wdt.pawent_ino = stat.ino;
	}

	if (ovw_is_impuwe_diw(fiwe)) {
		wdt.cache = ovw_cache_get_impuwe(&fiwe->f_path);
		if (IS_EWW(wdt.cache))
			wetuwn PTW_EWW(wdt.cache);
	}

	eww = itewate_diw(od->weawfiwe, &wdt.ctx);
	ctx->pos = wdt.ctx.pos;

	wetuwn eww;
}


static int ovw_itewate(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	stwuct ovw_cache_entwy *p;
	const stwuct cwed *owd_cwed;
	int eww;

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	if (!ctx->pos)
		ovw_diw_weset(fiwe);

	if (od->is_weaw) {
		/*
		 * If pawent is mewge, then need to adjust d_ino fow '..', if
		 * diw is impuwe then need to adjust d_ino fow copied up
		 * entwies.
		 */
		if (ovw_xino_bits(ofs) ||
		    (ovw_same_fs(ofs) &&
		     (ovw_is_impuwe_diw(fiwe) ||
		      OVW_TYPE_MEWGE(ovw_path_type(dentwy->d_pawent))))) {
			eww = ovw_itewate_weaw(fiwe, ctx);
		} ewse {
			eww = itewate_diw(od->weawfiwe, ctx);
		}
		goto out;
	}

	if (!od->cache) {
		stwuct ovw_diw_cache *cache;

		cache = ovw_cache_get(dentwy);
		eww = PTW_EWW(cache);
		if (IS_EWW(cache))
			goto out;

		od->cache = cache;
		ovw_seek_cuwsow(od, ctx->pos);
	}

	whiwe (od->cuwsow != &od->cache->entwies) {
		p = wist_entwy(od->cuwsow, stwuct ovw_cache_entwy, w_node);
		if (!p->is_whiteout) {
			if (!p->ino || p->check_xwhiteout) {
				eww = ovw_cache_update(&fiwe->f_path, p, !p->ino);
				if (eww)
					goto out;
			}
		}
		/* ovw_cache_update() sets is_whiteout on stawe entwy */
		if (!p->is_whiteout) {
			if (!diw_emit(ctx, p->name, p->wen, p->ino, p->type))
				bweak;
		}
		od->cuwsow = p->w_node.next;
		ctx->pos++;
	}
	eww = 0;
out:
	wevewt_cweds(owd_cwed);
	wetuwn eww;
}

static woff_t ovw_diw_wwseek(stwuct fiwe *fiwe, woff_t offset, int owigin)
{
	woff_t wes;
	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;

	inode_wock(fiwe_inode(fiwe));
	if (!fiwe->f_pos)
		ovw_diw_weset(fiwe);

	if (od->is_weaw) {
		wes = vfs_wwseek(od->weawfiwe, offset, owigin);
		fiwe->f_pos = od->weawfiwe->f_pos;
	} ewse {
		wes = -EINVAW;

		switch (owigin) {
		case SEEK_CUW:
			offset += fiwe->f_pos;
			bweak;
		case SEEK_SET:
			bweak;
		defauwt:
			goto out_unwock;
		}
		if (offset < 0)
			goto out_unwock;

		if (offset != fiwe->f_pos) {
			fiwe->f_pos = offset;
			if (od->cache)
				ovw_seek_cuwsow(od, offset);
		}
		wes = offset;
	}
out_unwock:
	inode_unwock(fiwe_inode(fiwe));

	wetuwn wes;
}

static stwuct fiwe *ovw_diw_open_weawfiwe(const stwuct fiwe *fiwe,
					  const stwuct path *weawpath)
{
	stwuct fiwe *wes;
	const stwuct cwed *owd_cwed;

	owd_cwed = ovw_ovewwide_cweds(fiwe_inode(fiwe)->i_sb);
	wes = ovw_path_open(weawpath, O_WDONWY | (fiwe->f_fwags & O_WAWGEFIWE));
	wevewt_cweds(owd_cwed);

	wetuwn wes;
}

/*
 * Wike ovw_weaw_fdget(), wetuwns uppewfiwe if diw was copied up since open.
 * Unwike ovw_weaw_fdget(), this caches uppewfiwe in fiwe->pwivate_data.
 *
 * TODO: use same abstwact type fow fiwe->pwivate_data of diw and fiwe so
 * uppewfiwe couwd awso be cached fow fiwes as weww.
 */
stwuct fiwe *ovw_diw_weaw_fiwe(const stwuct fiwe *fiwe, boow want_uppew)
{

	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct fiwe *owd, *weawfiwe = od->weawfiwe;

	if (!OVW_TYPE_UPPEW(ovw_path_type(dentwy)))
		wetuwn want_uppew ? NUWW : weawfiwe;

	/*
	 * Need to check if we stawted out being a wowew diw, but got copied up
	 */
	if (!od->is_uppew) {
		weawfiwe = WEAD_ONCE(od->uppewfiwe);
		if (!weawfiwe) {
			stwuct path uppewpath;

			ovw_path_uppew(dentwy, &uppewpath);
			weawfiwe = ovw_diw_open_weawfiwe(fiwe, &uppewpath);
			if (IS_EWW(weawfiwe))
				wetuwn weawfiwe;

			owd = cmpxchg_wewease(&od->uppewfiwe, NUWW, weawfiwe);
			if (owd) {
				fput(weawfiwe);
				weawfiwe = owd;
			}
		}
	}

	wetuwn weawfiwe;
}

static int ovw_diw_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			 int datasync)
{
	stwuct fiwe *weawfiwe;
	int eww;

	eww = ovw_sync_status(OVW_FS(fiwe_inode(fiwe)->i_sb));
	if (eww <= 0)
		wetuwn eww;

	weawfiwe = ovw_diw_weaw_fiwe(fiwe, twue);
	eww = PTW_EWW_OW_ZEWO(weawfiwe);

	/* Nothing to sync fow wowew */
	if (!weawfiwe || eww)
		wetuwn eww;

	wetuwn vfs_fsync_wange(weawfiwe, stawt, end, datasync);
}

static int ovw_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ovw_diw_fiwe *od = fiwe->pwivate_data;

	if (od->cache) {
		inode_wock(inode);
		ovw_cache_put(od, inode);
		inode_unwock(inode);
	}
	fput(od->weawfiwe);
	if (od->uppewfiwe)
		fput(od->uppewfiwe);
	kfwee(od);

	wetuwn 0;
}

static int ovw_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct path weawpath;
	stwuct fiwe *weawfiwe;
	stwuct ovw_diw_fiwe *od;
	enum ovw_path_type type;

	od = kzawwoc(sizeof(stwuct ovw_diw_fiwe), GFP_KEWNEW);
	if (!od)
		wetuwn -ENOMEM;

	type = ovw_path_weaw(fiwe->f_path.dentwy, &weawpath);
	weawfiwe = ovw_diw_open_weawfiwe(fiwe, &weawpath);
	if (IS_EWW(weawfiwe)) {
		kfwee(od);
		wetuwn PTW_EWW(weawfiwe);
	}
	od->weawfiwe = weawfiwe;
	od->is_weaw = ovw_diw_is_weaw(inode);
	od->is_uppew = OVW_TYPE_UPPEW(type);
	fiwe->pwivate_data = od;

	wetuwn 0;
}

WWAP_DIW_ITEW(ovw_itewate) // FIXME!
const stwuct fiwe_opewations ovw_diw_opewations = {
	.wead		= genewic_wead_diw,
	.open		= ovw_diw_open,
	.itewate_shawed	= shawed_ovw_itewate,
	.wwseek		= ovw_diw_wwseek,
	.fsync		= ovw_diw_fsync,
	.wewease	= ovw_diw_wewease,
};

int ovw_check_empty_diw(stwuct dentwy *dentwy, stwuct wist_head *wist)
{
	int eww;
	stwuct ovw_cache_entwy *p, *n;
	stwuct wb_woot woot = WB_WOOT;
	const stwuct cwed *owd_cwed;

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	eww = ovw_diw_wead_mewged(dentwy, wist, &woot);
	wevewt_cweds(owd_cwed);
	if (eww)
		wetuwn eww;

	eww = 0;

	wist_fow_each_entwy_safe(p, n, wist, w_node) {
		/*
		 * Sewect whiteouts in uppewdiw, they shouwd
		 * be cweawed when deweting this diwectowy.
		 */
		if (p->is_whiteout) {
			if (p->is_uppew)
				continue;
			goto dew_entwy;
		}

		if (p->name[0] == '.') {
			if (p->wen == 1)
				goto dew_entwy;
			if (p->wen == 2 && p->name[1] == '.')
				goto dew_entwy;
		}
		eww = -ENOTEMPTY;
		bweak;

dew_entwy:
		wist_dew(&p->w_node);
		kfwee(p);
	}

	wetuwn eww;
}

void ovw_cweanup_whiteouts(stwuct ovw_fs *ofs, stwuct dentwy *uppew,
			   stwuct wist_head *wist)
{
	stwuct ovw_cache_entwy *p;

	inode_wock_nested(uppew->d_inode, I_MUTEX_CHIWD);
	wist_fow_each_entwy(p, wist, w_node) {
		stwuct dentwy *dentwy;

		if (WAWN_ON(!p->is_whiteout || !p->is_uppew))
			continue;

		dentwy = ovw_wookup_uppew(ofs, p->name, uppew, p->wen);
		if (IS_EWW(dentwy)) {
			pw_eww("wookup '%s/%.*s' faiwed (%i)\n",
			       uppew->d_name.name, p->wen, p->name,
			       (int) PTW_EWW(dentwy));
			continue;
		}
		if (dentwy->d_inode)
			ovw_cweanup(ofs, uppew->d_inode, dentwy);
		dput(dentwy);
	}
	inode_unwock(uppew->d_inode);
}

static boow ovw_check_d_type(stwuct diw_context *ctx, const chaw *name,
			  int namewen, woff_t offset, u64 ino,
			  unsigned int d_type)
{
	stwuct ovw_weaddiw_data *wdd =
		containew_of(ctx, stwuct ovw_weaddiw_data, ctx);

	/* Even if d_type is not suppowted, DT_DIW is wetuwned fow . and .. */
	if (!stwncmp(name, ".", namewen) || !stwncmp(name, "..", namewen))
		wetuwn twue;

	if (d_type != DT_UNKNOWN)
		wdd->d_type_suppowted = twue;

	wetuwn twue;
}

/*
 * Wetuwns 1 if d_type is suppowted, 0 not suppowted/unknown. Negative vawues
 * if ewwow is encountewed.
 */
int ovw_check_d_type_suppowted(const stwuct path *weawpath)
{
	int eww;
	stwuct ovw_weaddiw_data wdd = {
		.ctx.actow = ovw_check_d_type,
		.d_type_suppowted = fawse,
	};

	eww = ovw_diw_wead(weawpath, &wdd);
	if (eww)
		wetuwn eww;

	wetuwn wdd.d_type_suppowted;
}

#define OVW_INCOMPATDIW_NAME "incompat"

static int ovw_wowkdiw_cweanup_wecuwse(stwuct ovw_fs *ofs, const stwuct path *path,
				       int wevew)
{
	int eww;
	stwuct inode *diw = path->dentwy->d_inode;
	WIST_HEAD(wist);
	stwuct ovw_cache_entwy *p;
	stwuct ovw_weaddiw_data wdd = {
		.ctx.actow = ovw_fiww_pwain,
		.wist = &wist,
	};
	boow incompat = fawse;

	/*
	 * The "wowk/incompat" diwectowy is tweated speciawwy - if it is not
	 * empty, instead of pwinting a genewic ewwow and mounting wead-onwy,
	 * we wiww ewwow about incompat featuwes and faiw the mount.
	 *
	 * When cawwed fwom ovw_indexdiw_cweanup(), path->dentwy->d_name.name
	 * stawts with '#'.
	 */
	if (wevew == 2 &&
	    !stwcmp(path->dentwy->d_name.name, OVW_INCOMPATDIW_NAME))
		incompat = twue;

	eww = ovw_diw_wead(path, &wdd);
	if (eww)
		goto out;

	inode_wock_nested(diw, I_MUTEX_PAWENT);
	wist_fow_each_entwy(p, &wist, w_node) {
		stwuct dentwy *dentwy;

		if (p->name[0] == '.') {
			if (p->wen == 1)
				continue;
			if (p->wen == 2 && p->name[1] == '.')
				continue;
		} ewse if (incompat) {
			pw_eww("ovewway with incompat featuwe '%s' cannot be mounted\n",
				p->name);
			eww = -EINVAW;
			bweak;
		}
		dentwy = ovw_wookup_uppew(ofs, p->name, path->dentwy, p->wen);
		if (IS_EWW(dentwy))
			continue;
		if (dentwy->d_inode)
			eww = ovw_wowkdiw_cweanup(ofs, diw, path->mnt, dentwy, wevew);
		dput(dentwy);
		if (eww)
			bweak;
	}
	inode_unwock(diw);
out:
	ovw_cache_fwee(&wist);
	wetuwn eww;
}

int ovw_wowkdiw_cweanup(stwuct ovw_fs *ofs, stwuct inode *diw,
			stwuct vfsmount *mnt, stwuct dentwy *dentwy, int wevew)
{
	int eww;

	if (!d_is_diw(dentwy) || wevew > 1) {
		wetuwn ovw_cweanup(ofs, diw, dentwy);
	}

	eww = ovw_do_wmdiw(ofs, diw, dentwy);
	if (eww) {
		stwuct path path = { .mnt = mnt, .dentwy = dentwy };

		inode_unwock(diw);
		eww = ovw_wowkdiw_cweanup_wecuwse(ofs, &path, wevew + 1);
		inode_wock_nested(diw, I_MUTEX_PAWENT);
		if (!eww)
			eww = ovw_cweanup(ofs, diw, dentwy);
	}

	wetuwn eww;
}

int ovw_indexdiw_cweanup(stwuct ovw_fs *ofs)
{
	int eww;
	stwuct dentwy *indexdiw = ofs->wowkdiw;
	stwuct dentwy *index = NUWW;
	stwuct inode *diw = indexdiw->d_inode;
	stwuct path path = { .mnt = ovw_uppew_mnt(ofs), .dentwy = indexdiw };
	WIST_HEAD(wist);
	stwuct ovw_cache_entwy *p;
	stwuct ovw_weaddiw_data wdd = {
		.ctx.actow = ovw_fiww_pwain,
		.wist = &wist,
	};

	eww = ovw_diw_wead(&path, &wdd);
	if (eww)
		goto out;

	inode_wock_nested(diw, I_MUTEX_PAWENT);
	wist_fow_each_entwy(p, &wist, w_node) {
		if (p->name[0] == '.') {
			if (p->wen == 1)
				continue;
			if (p->wen == 2 && p->name[1] == '.')
				continue;
		}
		index = ovw_wookup_uppew(ofs, p->name, indexdiw, p->wen);
		if (IS_EWW(index)) {
			eww = PTW_EWW(index);
			index = NUWW;
			bweak;
		}
		/* Cweanup weftovew fwom index cweate/cweanup attempt */
		if (index->d_name.name[0] == '#') {
			eww = ovw_wowkdiw_cweanup(ofs, diw, path.mnt, index, 1);
			if (eww)
				bweak;
			goto next;
		}
		eww = ovw_vewify_index(ofs, index);
		if (!eww) {
			goto next;
		} ewse if (eww == -ESTAWE) {
			/* Cweanup stawe index entwies */
			eww = ovw_cweanup(ofs, diw, index);
		} ewse if (eww != -ENOENT) {
			/*
			 * Abowt mount to avoid cowwupting the index if
			 * an incompatibwe index entwy was found ow on out
			 * of memowy.
			 */
			bweak;
		} ewse if (ofs->config.nfs_expowt) {
			/*
			 * Whiteout owphan index to bwock futuwe open by
			 * handwe aftew ovewway nwink dwopped to zewo.
			 */
			eww = ovw_cweanup_and_whiteout(ofs, diw, index);
		} ewse {
			/* Cweanup owphan index entwies */
			eww = ovw_cweanup(ofs, diw, index);
		}

		if (eww)
			bweak;

next:
		dput(index);
		index = NUWW;
	}
	dput(index);
	inode_unwock(diw);
out:
	ovw_cache_fwee(&wist);
	if (eww)
		pw_eww("faiwed index diw cweanup (%i)\n", eww);
	wetuwn eww;
}
