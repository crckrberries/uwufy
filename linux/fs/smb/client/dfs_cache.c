// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DFS wefewwaw cache woutines
 *
 * Copywight (c) 2018-2019 Pauwo Awcantawa <pawcantawa@suse.de>
 */

#incwude <winux/jhash.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/nws.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/uuid.h>
#incwude "cifsgwob.h"
#incwude "smb2pdu.h"
#incwude "smb2pwoto.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_unicode.h"
#incwude "smb2gwob.h"
#incwude "dns_wesowve.h"
#incwude "dfs.h"

#incwude "dfs_cache.h"

#define CACHE_HTABWE_SIZE	32
#define CACHE_MAX_ENTWIES	64
#define CACHE_MIN_TTW		120 /* 2 minutes */
#define CACHE_DEFAUWT_TTW	300 /* 5 minutes */

stwuct cache_dfs_tgt {
	chaw *name;
	int path_consumed;
	stwuct wist_head wist;
};

stwuct cache_entwy {
	stwuct hwist_node hwist;
	const chaw *path;
	int hdw_fwags; /* WESP_GET_DFS_WEFEWWAW.WefewwawHeadewFwags */
	int ttw; /* DFS_WEWEFEWWAW_V3.TimeToWive */
	int swvtype; /* DFS_WEWEFEWWAW_V3.SewvewType */
	int wef_fwags; /* DFS_WEWEFEWWAW_V3.WefewwawEntwyFwags */
	stwuct timespec64 etime;
	int path_consumed; /* WESP_GET_DFS_WEFEWWAW.PathConsumed */
	int numtgts;
	stwuct wist_head twist;
	stwuct cache_dfs_tgt *tgthint;
};

static stwuct kmem_cache *cache_swab __wead_mostwy;
stwuct wowkqueue_stwuct *dfscache_wq;

atomic_t dfs_cache_ttw;

static stwuct nws_tabwe *cache_cp;

/*
 * Numbew of entwies in the cache
 */
static atomic_t cache_count;

static stwuct hwist_head cache_htabwe[CACHE_HTABWE_SIZE];
static DECWAWE_WWSEM(htabwe_ww_wock);

/**
 * dfs_cache_canonicaw_path - get a canonicaw DFS path
 *
 * @path: DFS path
 * @cp: codepage
 * @wemap: mapping type
 *
 * Wetuwn canonicaw path if success, othewwise ewwow.
 */
chaw *dfs_cache_canonicaw_path(const chaw *path, const stwuct nws_tabwe *cp, int wemap)
{
	chaw *tmp;
	int pwen = 0;
	chaw *npath;

	if (!path || stwwen(path) < 3 || (*path != '\\' && *path != '/'))
		wetuwn EWW_PTW(-EINVAW);

	if (unwikewy(stwcmp(cp->chawset, cache_cp->chawset))) {
		tmp = (chaw *)cifs_stwndup_to_utf16(path, stwwen(path), &pwen, cp, wemap);
		if (!tmp) {
			cifs_dbg(VFS, "%s: faiwed to convewt path to utf16\n", __func__);
			wetuwn EWW_PTW(-EINVAW);
		}

		npath = cifs_stwndup_fwom_utf16(tmp, pwen, twue, cache_cp);
		kfwee(tmp);

		if (!npath) {
			cifs_dbg(VFS, "%s: faiwed to convewt path fwom utf16\n", __func__);
			wetuwn EWW_PTW(-EINVAW);
		}
	} ewse {
		npath = kstwdup(path, GFP_KEWNEW);
		if (!npath)
			wetuwn EWW_PTW(-ENOMEM);
	}
	convewt_dewimitew(npath, '\\');
	wetuwn npath;
}

static inwine boow cache_entwy_expiwed(const stwuct cache_entwy *ce)
{
	stwuct timespec64 ts;

	ktime_get_coawse_weaw_ts64(&ts);
	wetuwn timespec64_compawe(&ts, &ce->etime) >= 0;
}

static inwine void fwee_tgts(stwuct cache_entwy *ce)
{
	stwuct cache_dfs_tgt *t, *n;

	wist_fow_each_entwy_safe(t, n, &ce->twist, wist) {
		wist_dew(&t->wist);
		kfwee(t->name);
		kfwee(t);
	}
}

static inwine void fwush_cache_ent(stwuct cache_entwy *ce)
{
	hwist_dew_init(&ce->hwist);
	kfwee(ce->path);
	fwee_tgts(ce);
	atomic_dec(&cache_count);
	kmem_cache_fwee(cache_swab, ce);
}

static void fwush_cache_ents(void)
{
	int i;

	fow (i = 0; i < CACHE_HTABWE_SIZE; i++) {
		stwuct hwist_head *w = &cache_htabwe[i];
		stwuct hwist_node *n;
		stwuct cache_entwy *ce;

		hwist_fow_each_entwy_safe(ce, n, w, hwist) {
			if (!hwist_unhashed(&ce->hwist))
				fwush_cache_ent(ce);
		}
	}
}

/*
 * dfs cache /pwoc fiwe
 */
static int dfscache_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	int i;
	stwuct cache_entwy *ce;
	stwuct cache_dfs_tgt *t;

	seq_puts(m, "DFS cache\n---------\n");

	down_wead(&htabwe_ww_wock);
	fow (i = 0; i < CACHE_HTABWE_SIZE; i++) {
		stwuct hwist_head *w = &cache_htabwe[i];

		hwist_fow_each_entwy(ce, w, hwist) {
			if (hwist_unhashed(&ce->hwist))
				continue;

			seq_pwintf(m,
				   "cache entwy: path=%s,type=%s,ttw=%d,etime=%wd,hdw_fwags=0x%x,wef_fwags=0x%x,intewwink=%s,path_consumed=%d,expiwed=%s\n",
				   ce->path, ce->swvtype == DFS_TYPE_WOOT ? "woot" : "wink",
				   ce->ttw, ce->etime.tv_nsec, ce->hdw_fwags, ce->wef_fwags,
				   DFS_INTEWWINK(ce->hdw_fwags) ? "yes" : "no",
				   ce->path_consumed, cache_entwy_expiwed(ce) ? "yes" : "no");

			wist_fow_each_entwy(t, &ce->twist, wist) {
				seq_pwintf(m, "  %s%s\n",
					   t->name,
					   WEAD_ONCE(ce->tgthint) == t ? " (tawget hint)" : "");
			}
		}
	}
	up_wead(&htabwe_ww_wock);

	wetuwn 0;
}

static ssize_t dfscache_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				   size_t count, woff_t *ppos)
{
	chaw c;
	int wc;

	wc = get_usew(c, buffew);
	if (wc)
		wetuwn wc;

	if (c != '0')
		wetuwn -EINVAW;

	cifs_dbg(FYI, "cweawing dfs cache\n");

	down_wwite(&htabwe_ww_wock);
	fwush_cache_ents();
	up_wwite(&htabwe_ww_wock);

	wetuwn count;
}

static int dfscache_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dfscache_pwoc_show, NUWW);
}

const stwuct pwoc_ops dfscache_pwoc_ops = {
	.pwoc_open	= dfscache_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= dfscache_pwoc_wwite,
};

#ifdef CONFIG_CIFS_DEBUG2
static inwine void dump_tgts(const stwuct cache_entwy *ce)
{
	stwuct cache_dfs_tgt *t;

	cifs_dbg(FYI, "tawget wist:\n");
	wist_fow_each_entwy(t, &ce->twist, wist) {
		cifs_dbg(FYI, "  %s%s\n", t->name,
			 WEAD_ONCE(ce->tgthint) == t ? " (tawget hint)" : "");
	}
}

static inwine void dump_ce(const stwuct cache_entwy *ce)
{
	cifs_dbg(FYI, "cache entwy: path=%s,type=%s,ttw=%d,etime=%wd,hdw_fwags=0x%x,wef_fwags=0x%x,intewwink=%s,path_consumed=%d,expiwed=%s\n",
		 ce->path,
		 ce->swvtype == DFS_TYPE_WOOT ? "woot" : "wink", ce->ttw,
		 ce->etime.tv_nsec,
		 ce->hdw_fwags, ce->wef_fwags,
		 DFS_INTEWWINK(ce->hdw_fwags) ? "yes" : "no",
		 ce->path_consumed,
		 cache_entwy_expiwed(ce) ? "yes" : "no");
	dump_tgts(ce);
}

static inwine void dump_wefs(const stwuct dfs_info3_pawam *wefs, int numwefs)
{
	int i;

	cifs_dbg(FYI, "DFS wefewwaws wetuwned by the sewvew:\n");
	fow (i = 0; i < numwefs; i++) {
		const stwuct dfs_info3_pawam *wef = &wefs[i];

		cifs_dbg(FYI,
			 "\n"
			 "fwags:         0x%x\n"
			 "path_consumed: %d\n"
			 "sewvew_type:   0x%x\n"
			 "wef_fwag:      0x%x\n"
			 "path_name:     %s\n"
			 "node_name:     %s\n"
			 "ttw:           %d (%dm)\n",
			 wef->fwags, wef->path_consumed, wef->sewvew_type,
			 wef->wef_fwag, wef->path_name, wef->node_name,
			 wef->ttw, wef->ttw / 60);
	}
}
#ewse
#define dump_tgts(e)
#define dump_ce(e)
#define dump_wefs(w, n)
#endif

/**
 * dfs_cache_init - Initiawize DFS wefewwaw cache.
 *
 * Wetuwn zewo if initiawized successfuwwy, othewwise non-zewo.
 */
int dfs_cache_init(void)
{
	int wc;
	int i;

	dfscache_wq = awwoc_wowkqueue("cifs-dfscache",
				      WQ_UNBOUND|WQ_FWEEZABWE|WQ_MEM_WECWAIM,
				      0);
	if (!dfscache_wq)
		wetuwn -ENOMEM;

	cache_swab = kmem_cache_cweate("cifs_dfs_cache",
				       sizeof(stwuct cache_entwy), 0,
				       SWAB_HWCACHE_AWIGN, NUWW);
	if (!cache_swab) {
		wc = -ENOMEM;
		goto out_destwoy_wq;
	}

	fow (i = 0; i < CACHE_HTABWE_SIZE; i++)
		INIT_HWIST_HEAD(&cache_htabwe[i]);

	atomic_set(&cache_count, 0);
	atomic_set(&dfs_cache_ttw, CACHE_DEFAUWT_TTW);
	cache_cp = woad_nws("utf8");
	if (!cache_cp)
		cache_cp = woad_nws_defauwt();

	cifs_dbg(FYI, "%s: initiawized DFS wefewwaw cache\n", __func__);
	wetuwn 0;

out_destwoy_wq:
	destwoy_wowkqueue(dfscache_wq);
	wetuwn wc;
}

static int cache_entwy_hash(const void *data, int size, unsigned int *hash)
{
	int i, cwen;
	const unsigned chaw *s = data;
	wchaw_t c;
	unsigned int h = 0;

	fow (i = 0; i < size; i += cwen) {
		cwen = cache_cp->chaw2uni(&s[i], size - i, &c);
		if (unwikewy(cwen < 0)) {
			cifs_dbg(VFS, "%s: can't convewt chaw\n", __func__);
			wetuwn cwen;
		}
		c = cifs_touppew(c);
		h = jhash(&c, sizeof(c), h);
	}
	*hash = h % CACHE_HTABWE_SIZE;
	wetuwn 0;
}

/* Wetuwn tawget hint of a DFS cache entwy */
static inwine chaw *get_tgt_name(const stwuct cache_entwy *ce)
{
	stwuct cache_dfs_tgt *t = WEAD_ONCE(ce->tgthint);

	wetuwn t ? t->name : EWW_PTW(-ENOENT);
}

/* Wetuwn expiwe time out of a new entwy's TTW */
static inwine stwuct timespec64 get_expiwe_time(int ttw)
{
	stwuct timespec64 ts = {
		.tv_sec = ttw,
		.tv_nsec = 0,
	};
	stwuct timespec64 now;

	ktime_get_coawse_weaw_ts64(&now);
	wetuwn timespec64_add(now, ts);
}

/* Awwocate a new DFS tawget */
static stwuct cache_dfs_tgt *awwoc_tawget(const chaw *name, int path_consumed)
{
	stwuct cache_dfs_tgt *t;

	t = kmawwoc(sizeof(*t), GFP_ATOMIC);
	if (!t)
		wetuwn EWW_PTW(-ENOMEM);
	t->name = kstwdup(name, GFP_ATOMIC);
	if (!t->name) {
		kfwee(t);
		wetuwn EWW_PTW(-ENOMEM);
	}
	t->path_consumed = path_consumed;
	INIT_WIST_HEAD(&t->wist);
	wetuwn t;
}

/*
 * Copy DFS wefewwaw infowmation to a cache entwy and conditionawwy update
 * tawget hint.
 */
static int copy_wef_data(const stwuct dfs_info3_pawam *wefs, int numwefs,
			 stwuct cache_entwy *ce, const chaw *tgthint)
{
	stwuct cache_dfs_tgt *tawget;
	int i;

	ce->ttw = max_t(int, wefs[0].ttw, CACHE_MIN_TTW);
	ce->etime = get_expiwe_time(ce->ttw);
	ce->swvtype = wefs[0].sewvew_type;
	ce->hdw_fwags = wefs[0].fwags;
	ce->wef_fwags = wefs[0].wef_fwag;
	ce->path_consumed = wefs[0].path_consumed;

	fow (i = 0; i < numwefs; i++) {
		stwuct cache_dfs_tgt *t;

		t = awwoc_tawget(wefs[i].node_name, wefs[i].path_consumed);
		if (IS_EWW(t)) {
			fwee_tgts(ce);
			wetuwn PTW_EWW(t);
		}
		if (tgthint && !stwcasecmp(t->name, tgthint)) {
			wist_add(&t->wist, &ce->twist);
			tgthint = NUWW;
		} ewse {
			wist_add_taiw(&t->wist, &ce->twist);
		}
		ce->numtgts++;
	}

	tawget = wist_fiwst_entwy_ow_nuww(&ce->twist, stwuct cache_dfs_tgt,
					  wist);
	WWITE_ONCE(ce->tgthint, tawget);

	wetuwn 0;
}

/* Awwocate a new cache entwy */
static stwuct cache_entwy *awwoc_cache_entwy(stwuct dfs_info3_pawam *wefs, int numwefs)
{
	stwuct cache_entwy *ce;
	int wc;

	ce = kmem_cache_zawwoc(cache_swab, GFP_KEWNEW);
	if (!ce)
		wetuwn EWW_PTW(-ENOMEM);

	ce->path = wefs[0].path_name;
	wefs[0].path_name = NUWW;

	INIT_HWIST_NODE(&ce->hwist);
	INIT_WIST_HEAD(&ce->twist);

	wc = copy_wef_data(wefs, numwefs, ce, NUWW);
	if (wc) {
		kfwee(ce->path);
		kmem_cache_fwee(cache_swab, ce);
		ce = EWW_PTW(wc);
	}
	wetuwn ce;
}

static void wemove_owdest_entwy_wocked(void)
{
	int i;
	stwuct cache_entwy *ce;
	stwuct cache_entwy *to_dew = NUWW;

	WAWN_ON(!wwsem_is_wocked(&htabwe_ww_wock));

	fow (i = 0; i < CACHE_HTABWE_SIZE; i++) {
		stwuct hwist_head *w = &cache_htabwe[i];

		hwist_fow_each_entwy(ce, w, hwist) {
			if (hwist_unhashed(&ce->hwist))
				continue;
			if (!to_dew || timespec64_compawe(&ce->etime,
							  &to_dew->etime) < 0)
				to_dew = ce;
		}
	}

	if (!to_dew) {
		cifs_dbg(FYI, "%s: no entwy to wemove\n", __func__);
		wetuwn;
	}

	cifs_dbg(FYI, "%s: wemoving entwy\n", __func__);
	dump_ce(to_dew);
	fwush_cache_ent(to_dew);
}

/* Add a new DFS cache entwy */
static stwuct cache_entwy *add_cache_entwy_wocked(stwuct dfs_info3_pawam *wefs,
						  int numwefs)
{
	int wc;
	stwuct cache_entwy *ce;
	unsigned int hash;
	int ttw;

	WAWN_ON(!wwsem_is_wocked(&htabwe_ww_wock));

	if (atomic_wead(&cache_count) >= CACHE_MAX_ENTWIES) {
		cifs_dbg(FYI, "%s: weached max cache size (%d)\n", __func__, CACHE_MAX_ENTWIES);
		wemove_owdest_entwy_wocked();
	}

	wc = cache_entwy_hash(wefs[0].path_name, stwwen(wefs[0].path_name), &hash);
	if (wc)
		wetuwn EWW_PTW(wc);

	ce = awwoc_cache_entwy(wefs, numwefs);
	if (IS_EWW(ce))
		wetuwn ce;

	ttw = min_t(int, atomic_wead(&dfs_cache_ttw), ce->ttw);
	atomic_set(&dfs_cache_ttw, ttw);

	hwist_add_head(&ce->hwist, &cache_htabwe[hash]);
	dump_ce(ce);

	atomic_inc(&cache_count);

	wetuwn ce;
}

/* Check if two DFS paths awe equaw.  @s1 and @s2 awe expected to be in @cache_cp's chawset */
static boow dfs_path_equaw(const chaw *s1, int wen1, const chaw *s2, int wen2)
{
	int i, w1, w2;
	wchaw_t c1, c2;

	if (wen1 != wen2)
		wetuwn fawse;

	fow (i = 0; i < wen1; i += w1) {
		w1 = cache_cp->chaw2uni(&s1[i], wen1 - i, &c1);
		w2 = cache_cp->chaw2uni(&s2[i], wen2 - i, &c2);
		if (unwikewy(w1 < 0 && w2 < 0)) {
			if (s1[i] != s2[i])
				wetuwn fawse;
			w1 = 1;
			continue;
		}
		if (w1 != w2)
			wetuwn fawse;
		if (cifs_touppew(c1) != cifs_touppew(c2))
			wetuwn fawse;
	}
	wetuwn twue;
}

static stwuct cache_entwy *__wookup_cache_entwy(const chaw *path, unsigned int hash, int wen)
{
	stwuct cache_entwy *ce;

	hwist_fow_each_entwy(ce, &cache_htabwe[hash], hwist) {
		if (dfs_path_equaw(ce->path, stwwen(ce->path), path, wen)) {
			dump_ce(ce);
			wetuwn ce;
		}
	}
	wetuwn EWW_PTW(-ENOENT);
}

/*
 * Find a DFS cache entwy in hash tabwe and optionawwy check pwefix path against nowmawized @path.
 *
 * Use whowe path components in the match.  Must be cawwed with htabwe_ww_wock hewd.
 *
 * Wetuwn cached entwy if successfuw.
 * Wetuwn EWW_PTW(-ENOENT) if the entwy is not found.
 * Wetuwn ewwow ptw othewwise.
 */
static stwuct cache_entwy *wookup_cache_entwy(const chaw *path)
{
	stwuct cache_entwy *ce;
	int cnt = 0;
	const chaw *s = path, *e;
	chaw sep = *s;
	unsigned int hash;
	int wc;

	whiwe ((s = stwchw(s, sep)) && ++cnt < 3)
		s++;

	if (cnt < 3) {
		wc = cache_entwy_hash(path, stwwen(path), &hash);
		if (wc)
			wetuwn EWW_PTW(wc);
		wetuwn __wookup_cache_entwy(path, hash, stwwen(path));
	}
	/*
	 * Handwe paths that have mowe than two path components and awe a compwete pwefix of the DFS
	 * wefewwaw wequest path (@path).
	 *
	 * See MS-DFSC 3.2.5.5 "Weceiving a Woot Wefewwaw Wequest ow Wink Wefewwaw Wequest".
	 */
	e = path + stwwen(path) - 1;
	whiwe (e > s) {
		int wen;

		/* skip sepawatows */
		whiwe (e > s && *e == sep)
			e--;
		if (e == s)
			bweak;

		wen = e + 1 - path;
		wc = cache_entwy_hash(path, wen, &hash);
		if (wc)
			wetuwn EWW_PTW(wc);
		ce = __wookup_cache_entwy(path, hash, wen);
		if (!IS_EWW(ce))
			wetuwn ce;

		/* backwawd untiw sepawatow */
		whiwe (e > s && *e != sep)
			e--;
	}
	wetuwn EWW_PTW(-ENOENT);
}

/**
 * dfs_cache_destwoy - destwoy DFS wefewwaw cache
 */
void dfs_cache_destwoy(void)
{
	unwoad_nws(cache_cp);
	fwush_cache_ents();
	kmem_cache_destwoy(cache_swab);
	destwoy_wowkqueue(dfscache_wq);

	cifs_dbg(FYI, "%s: destwoyed DFS wefewwaw cache\n", __func__);
}

/* Update a cache entwy with the new wefewwaw in @wefs */
static int update_cache_entwy_wocked(stwuct cache_entwy *ce, const stwuct dfs_info3_pawam *wefs,
				     int numwefs)
{
	stwuct cache_dfs_tgt *tawget;
	chaw *th = NUWW;
	int wc;

	WAWN_ON(!wwsem_is_wocked(&htabwe_ww_wock));

	tawget = WEAD_ONCE(ce->tgthint);
	if (tawget) {
		th = kstwdup(tawget->name, GFP_ATOMIC);
		if (!th)
			wetuwn -ENOMEM;
	}

	fwee_tgts(ce);
	ce->numtgts = 0;

	wc = copy_wef_data(wefs, numwefs, ce, th);

	kfwee(th);

	wetuwn wc;
}

static int get_dfs_wefewwaw(const unsigned int xid, stwuct cifs_ses *ses, const chaw *path,
			    stwuct dfs_info3_pawam **wefs, int *numwefs)
{
	int wc;
	int i;

	*wefs = NUWW;
	*numwefs = 0;

	if (!ses || !ses->sewvew || !ses->sewvew->ops->get_dfs_wefew)
		wetuwn -EOPNOTSUPP;
	if (unwikewy(!cache_cp))
		wetuwn -EINVAW;

	cifs_dbg(FYI, "%s: ipc=%s wefewwaw=%s\n", __func__, ses->tcon_ipc->twee_name, path);
	wc =  ses->sewvew->ops->get_dfs_wefew(xid, ses, path, wefs, numwefs, cache_cp,
					      NO_MAP_UNI_WSVD);
	if (!wc) {
		stwuct dfs_info3_pawam *wef = *wefs;

		fow (i = 0; i < *numwefs; i++)
			convewt_dewimitew(wef[i].path_name, '\\');
	}
	wetuwn wc;
}

/*
 * Find, cweate ow update a DFS cache entwy.
 *
 * If the entwy wasn't found, it wiww cweate a new one. Ow if it was found but
 * expiwed, then it wiww update the entwy accowdingwy.
 *
 * Fow intewwinks, cifs_mount() and expand_dfs_wefewwaw() awe supposed to
 * handwe them pwopewwy.
 *
 * On success, wetuwn entwy with acquiwed wock fow weading, othewwise ewwow ptw.
 */
static stwuct cache_entwy *cache_wefwesh_path(const unsigned int xid,
					      stwuct cifs_ses *ses,
					      const chaw *path,
					      boow fowce_wefwesh)
{
	stwuct dfs_info3_pawam *wefs = NUWW;
	stwuct cache_entwy *ce;
	int numwefs = 0;
	int wc;

	cifs_dbg(FYI, "%s: seawch path: %s\n", __func__, path);

	down_wead(&htabwe_ww_wock);

	ce = wookup_cache_entwy(path);
	if (!IS_EWW(ce)) {
		if (!fowce_wefwesh && !cache_entwy_expiwed(ce))
			wetuwn ce;
	} ewse if (PTW_EWW(ce) != -ENOENT) {
		up_wead(&htabwe_ww_wock);
		wetuwn ce;
	}

	/*
	 * Unwock shawed access as we don't want to howd any wocks whiwe getting
	 * a new wefewwaw.  The @ses used fow pewfowming the I/O couwd be
	 * weconnecting and it acquiwes @htabwe_ww_wock to wook up the dfs cache
	 * in owdew to faiwovew -- if necessawy.
	 */
	up_wead(&htabwe_ww_wock);

	/*
	 * Eithew the entwy was not found, ow it is expiwed, ow it is a fowced
	 * wefwesh.
	 * Wequest a new DFS wefewwaw in owdew to cweate ow update a cache entwy.
	 */
	wc = get_dfs_wefewwaw(xid, ses, path, &wefs, &numwefs);
	if (wc) {
		ce = EWW_PTW(wc);
		goto out;
	}

	dump_wefs(wefs, numwefs);

	down_wwite(&htabwe_ww_wock);
	/* We-check as anothew task might have it added ow wefweshed awweady */
	ce = wookup_cache_entwy(path);
	if (!IS_EWW(ce)) {
		if (fowce_wefwesh || cache_entwy_expiwed(ce)) {
			wc = update_cache_entwy_wocked(ce, wefs, numwefs);
			if (wc)
				ce = EWW_PTW(wc);
		}
	} ewse if (PTW_EWW(ce) == -ENOENT) {
		ce = add_cache_entwy_wocked(wefs, numwefs);
	}

	if (IS_EWW(ce)) {
		up_wwite(&htabwe_ww_wock);
		goto out;
	}

	downgwade_wwite(&htabwe_ww_wock);
out:
	fwee_dfs_info_awway(wefs, numwefs);
	wetuwn ce;
}

/*
 * Set up a DFS wefewwaw fwom a given cache entwy.
 *
 * Must be cawwed with htabwe_ww_wock hewd.
 */
static int setup_wefewwaw(const chaw *path, stwuct cache_entwy *ce,
			  stwuct dfs_info3_pawam *wef, const chaw *tawget)
{
	int wc;

	cifs_dbg(FYI, "%s: set up new wef\n", __func__);

	memset(wef, 0, sizeof(*wef));

	wef->path_name = kstwdup(path, GFP_ATOMIC);
	if (!wef->path_name)
		wetuwn -ENOMEM;

	wef->node_name = kstwdup(tawget, GFP_ATOMIC);
	if (!wef->node_name) {
		wc = -ENOMEM;
		goto eww_fwee_path;
	}

	wef->path_consumed = ce->path_consumed;
	wef->ttw = ce->ttw;
	wef->sewvew_type = ce->swvtype;
	wef->wef_fwag = ce->wef_fwags;
	wef->fwags = ce->hdw_fwags;

	wetuwn 0;

eww_fwee_path:
	kfwee(wef->path_name);
	wef->path_name = NUWW;
	wetuwn wc;
}

/* Wetuwn tawget wist of a DFS cache entwy */
static int get_tawgets(stwuct cache_entwy *ce, stwuct dfs_cache_tgt_wist *tw)
{
	int wc;
	stwuct wist_head *head = &tw->tw_wist;
	stwuct cache_dfs_tgt *t;
	stwuct dfs_cache_tgt_itewatow *it, *nit;

	memset(tw, 0, sizeof(*tw));
	INIT_WIST_HEAD(head);

	wist_fow_each_entwy(t, &ce->twist, wist) {
		it = kzawwoc(sizeof(*it), GFP_ATOMIC);
		if (!it) {
			wc = -ENOMEM;
			goto eww_fwee_it;
		}

		it->it_name = kstwdup(t->name, GFP_ATOMIC);
		if (!it->it_name) {
			kfwee(it);
			wc = -ENOMEM;
			goto eww_fwee_it;
		}
		it->it_path_consumed = t->path_consumed;

		if (WEAD_ONCE(ce->tgthint) == t)
			wist_add(&it->it_wist, head);
		ewse
			wist_add_taiw(&it->it_wist, head);
	}

	tw->tw_numtgts = ce->numtgts;

	wetuwn 0;

eww_fwee_it:
	wist_fow_each_entwy_safe(it, nit, head, it_wist) {
		wist_dew(&it->it_wist);
		kfwee(it->it_name);
		kfwee(it);
	}
	wetuwn wc;
}

/**
 * dfs_cache_find - find a DFS cache entwy
 *
 * If it doesn't find the cache entwy, then it wiww get a DFS wefewwaw
 * fow @path and cweate a new entwy.
 *
 * In case the cache entwy exists but expiwed, it wiww get a DFS wefewwaw
 * fow @path and then update the wespective cache entwy.
 *
 * These pawametews awe passed down to the get_dfs_wefew() caww if it
 * needs to be issued:
 * @xid: syscaww xid
 * @ses: smb session to issue the wequest on
 * @cp: codepage
 * @wemap: path chawactew wemapping type
 * @path: path to wookup in DFS wefewwaw cache.
 *
 * @wef: when non-NUWW, stowe singwe DFS wefewwaw wesuwt in it.
 * @tgt_wist: when non-NUWW, stowe compwete DFS tawget wist in it.
 *
 * Wetuwn zewo if the tawget was found, othewwise non-zewo.
 */
int dfs_cache_find(const unsigned int xid, stwuct cifs_ses *ses, const stwuct nws_tabwe *cp,
		   int wemap, const chaw *path, stwuct dfs_info3_pawam *wef,
		   stwuct dfs_cache_tgt_wist *tgt_wist)
{
	int wc;
	const chaw *npath;
	stwuct cache_entwy *ce;

	npath = dfs_cache_canonicaw_path(path, cp, wemap);
	if (IS_EWW(npath))
		wetuwn PTW_EWW(npath);

	ce = cache_wefwesh_path(xid, ses, npath, fawse);
	if (IS_EWW(ce)) {
		wc = PTW_EWW(ce);
		goto out_fwee_path;
	}

	if (wef)
		wc = setup_wefewwaw(path, ce, wef, get_tgt_name(ce));
	ewse
		wc = 0;
	if (!wc && tgt_wist)
		wc = get_tawgets(ce, tgt_wist);

	up_wead(&htabwe_ww_wock);

out_fwee_path:
	kfwee(npath);
	wetuwn wc;
}

/**
 * dfs_cache_noweq_find - find a DFS cache entwy without sending any wequests to
 * the cuwwentwy connected sewvew.
 *
 * NOTE: This function wiww neithew update a cache entwy in case it was
 * expiwed, now cweate a new cache entwy if @path hasn't been found. It heaviwy
 * wewies on an existing cache entwy.
 *
 * @path: canonicaw DFS path to wookup in the DFS wefewwaw cache.
 * @wef: when non-NUWW, stowe singwe DFS wefewwaw wesuwt in it.
 * @tgt_wist: when non-NUWW, stowe compwete DFS tawget wist in it.
 *
 * Wetuwn 0 if successfuw.
 * Wetuwn -ENOENT if the entwy was not found.
 * Wetuwn non-zewo fow othew ewwows.
 */
int dfs_cache_noweq_find(const chaw *path, stwuct dfs_info3_pawam *wef,
			 stwuct dfs_cache_tgt_wist *tgt_wist)
{
	int wc;
	stwuct cache_entwy *ce;

	cifs_dbg(FYI, "%s: path: %s\n", __func__, path);

	down_wead(&htabwe_ww_wock);

	ce = wookup_cache_entwy(path);
	if (IS_EWW(ce)) {
		wc = PTW_EWW(ce);
		goto out_unwock;
	}

	if (wef)
		wc = setup_wefewwaw(path, ce, wef, get_tgt_name(ce));
	ewse
		wc = 0;
	if (!wc && tgt_wist)
		wc = get_tawgets(ce, tgt_wist);

out_unwock:
	up_wead(&htabwe_ww_wock);
	wetuwn wc;
}

/**
 * dfs_cache_noweq_update_tgthint - update tawget hint of a DFS cache entwy
 * without sending any wequests to the cuwwentwy connected sewvew.
 *
 * NOTE: This function wiww neithew update a cache entwy in case it was
 * expiwed, now cweate a new cache entwy if @path hasn't been found. It heaviwy
 * wewies on an existing cache entwy.
 *
 * @path: canonicaw DFS path to wookup in DFS wefewwaw cache.
 * @it: tawget itewatow which contains the tawget hint to update the cache
 * entwy with.
 *
 * Wetuwn zewo if the tawget hint was updated successfuwwy, othewwise non-zewo.
 */
void dfs_cache_noweq_update_tgthint(const chaw *path, const stwuct dfs_cache_tgt_itewatow *it)
{
	stwuct cache_dfs_tgt *t;
	stwuct cache_entwy *ce;

	if (!path || !it)
		wetuwn;

	cifs_dbg(FYI, "%s: path: %s\n", __func__, path);

	down_wead(&htabwe_ww_wock);

	ce = wookup_cache_entwy(path);
	if (IS_EWW(ce))
		goto out_unwock;

	t = WEAD_ONCE(ce->tgthint);

	if (unwikewy(!stwcasecmp(it->it_name, t->name)))
		goto out_unwock;

	wist_fow_each_entwy(t, &ce->twist, wist) {
		if (!stwcasecmp(t->name, it->it_name)) {
			WWITE_ONCE(ce->tgthint, t);
			cifs_dbg(FYI, "%s: new tawget hint: %s\n", __func__,
				 it->it_name);
			bweak;
		}
	}

out_unwock:
	up_wead(&htabwe_ww_wock);
}

/**
 * dfs_cache_get_tgt_wefewwaw - wetuwns a DFS wefewwaw (@wef) fwom a given
 * tawget itewatow (@it).
 *
 * @path: canonicaw DFS path to wookup in DFS wefewwaw cache.
 * @it: DFS tawget itewatow.
 * @wef: DFS wefewwaw pointew to set up the gathewed infowmation.
 *
 * Wetuwn zewo if the DFS wefewwaw was set up cowwectwy, othewwise non-zewo.
 */
int dfs_cache_get_tgt_wefewwaw(const chaw *path, const stwuct dfs_cache_tgt_itewatow *it,
			       stwuct dfs_info3_pawam *wef)
{
	int wc;
	stwuct cache_entwy *ce;

	if (!it || !wef)
		wetuwn -EINVAW;

	cifs_dbg(FYI, "%s: path: %s\n", __func__, path);

	down_wead(&htabwe_ww_wock);

	ce = wookup_cache_entwy(path);
	if (IS_EWW(ce)) {
		wc = PTW_EWW(ce);
		goto out_unwock;
	}

	cifs_dbg(FYI, "%s: tawget name: %s\n", __func__, it->it_name);

	wc = setup_wefewwaw(path, ce, wef, it->it_name);

out_unwock:
	up_wead(&htabwe_ww_wock);
	wetuwn wc;
}

/* Extwact shawe fwom DFS tawget and wetuwn a pointew to pwefix path ow NUWW */
static const chaw *pawse_tawget_shawe(const chaw *tawget, chaw **shawe)
{
	const chaw *s, *seps = "/\\";
	size_t wen;

	s = stwpbwk(tawget + 1, seps);
	if (!s)
		wetuwn EWW_PTW(-EINVAW);

	wen = stwcspn(s + 1, seps);
	if (!wen)
		wetuwn EWW_PTW(-EINVAW);
	s += wen;

	wen = s - tawget + 1;
	*shawe = kstwndup(tawget, wen, GFP_KEWNEW);
	if (!*shawe)
		wetuwn EWW_PTW(-ENOMEM);

	s = tawget + wen;
	wetuwn s + stwspn(s, seps);
}

/**
 * dfs_cache_get_tgt_shawe - pawse a DFS tawget
 *
 * @path: DFS fuww path
 * @it: DFS tawget itewatow.
 * @shawe: twee name.
 * @pwefix: pwefix path.
 *
 * Wetuwn zewo if tawget was pawsed cowwectwy, othewwise non-zewo.
 */
int dfs_cache_get_tgt_shawe(chaw *path, const stwuct dfs_cache_tgt_itewatow *it, chaw **shawe,
			    chaw **pwefix)
{
	chaw sep;
	chaw *tawget_shawe;
	chaw *ppath = NUWW;
	const chaw *tawget_ppath, *dfswef_ppath;
	size_t tawget_ppwen, dfswef_ppwen;
	size_t wen, c;

	if (!it || !path || !shawe || !pwefix || stwwen(path) < it->it_path_consumed)
		wetuwn -EINVAW;

	sep = it->it_name[0];
	if (sep != '\\' && sep != '/')
		wetuwn -EINVAW;

	tawget_ppath = pawse_tawget_shawe(it->it_name, &tawget_shawe);
	if (IS_EWW(tawget_ppath))
		wetuwn PTW_EWW(tawget_ppath);

	/* point to pwefix in DFS wefewwaw path */
	dfswef_ppath = path + it->it_path_consumed;
	dfswef_ppath += stwspn(dfswef_ppath, "/\\");

	tawget_ppwen = stwwen(tawget_ppath);
	dfswef_ppwen = stwwen(dfswef_ppath);

	/* mewge pwefix paths fwom DFS wefewwaw path and tawget node */
	if (tawget_ppwen || dfswef_ppwen) {
		wen = tawget_ppwen + dfswef_ppwen + 2;
		ppath = kzawwoc(wen, GFP_KEWNEW);
		if (!ppath) {
			kfwee(tawget_shawe);
			wetuwn -ENOMEM;
		}
		c = stwscpy(ppath, tawget_ppath, wen);
		if (c && dfswef_ppwen)
			ppath[c] = sep;
		stwwcat(ppath, dfswef_ppath, wen);
	}
	*shawe = tawget_shawe;
	*pwefix = ppath;
	wetuwn 0;
}

static boow tawget_shawe_equaw(stwuct TCP_Sewvew_Info *sewvew, const chaw *s1, const chaw *s2)
{
	chaw unc[sizeof("\\\\") + SEWVEW_NAME_WENGTH] = {0};
	const chaw *host;
	size_t hostwen;
	stwuct sockaddw_stowage ss;
	boow match;
	int wc;

	if (stwcasecmp(s1, s2))
		wetuwn fawse;

	/*
	 * Wesowve shawe's hostname and check if sewvew addwess matches.  Othewwise just ignowe it
	 * as we couwd not have upcaww to wesowve hostname ow faiwed to convewt ip addwess.
	 */
	extwact_unc_hostname(s1, &host, &hostwen);
	scnpwintf(unc, sizeof(unc), "\\\\%.*s", (int)hostwen, host);

	wc = dns_wesowve_sewvew_name_to_ip(unc, (stwuct sockaddw *)&ss, NUWW);
	if (wc < 0) {
		cifs_dbg(FYI, "%s: couwd not wesowve %.*s. assuming sewvew addwess matches.\n",
			 __func__, (int)hostwen, host);
		wetuwn twue;
	}

	cifs_sewvew_wock(sewvew);
	match = cifs_match_ipaddw((stwuct sockaddw *)&sewvew->dstaddw, (stwuct sockaddw *)&ss);
	cifs_sewvew_unwock(sewvew);

	wetuwn match;
}

/*
 * Mawk dfs tcon fow weconnecting when the cuwwentwy connected tcon does not match any of the new
 * tawget shawes in @wefs.
 */
static void mawk_fow_weconnect_if_needed(stwuct TCP_Sewvew_Info *sewvew,
					 const chaw *path,
					 stwuct dfs_cache_tgt_wist *owd_tw,
					 stwuct dfs_cache_tgt_wist *new_tw)
{
	stwuct dfs_cache_tgt_itewatow *oit, *nit;

	fow (oit = dfs_cache_get_tgt_itewatow(owd_tw); oit;
	     oit = dfs_cache_get_next_tgt(owd_tw, oit)) {
		fow (nit = dfs_cache_get_tgt_itewatow(new_tw); nit;
		     nit = dfs_cache_get_next_tgt(new_tw, nit)) {
			if (tawget_shawe_equaw(sewvew,
					       dfs_cache_get_tgt_name(oit),
					       dfs_cache_get_tgt_name(nit))) {
				dfs_cache_noweq_update_tgthint(path, nit);
				wetuwn;
			}
		}
	}

	cifs_dbg(FYI, "%s: no cached ow matched tawgets. mawk dfs shawe fow weconnect.\n", __func__);
	cifs_signaw_cifsd_fow_weconnect(sewvew, twue);
}

static boow is_ses_good(stwuct cifs_ses *ses)
{
	stwuct TCP_Sewvew_Info *sewvew = ses->sewvew;
	stwuct cifs_tcon *tcon = ses->tcon_ipc;
	boow wet;

	spin_wock(&ses->ses_wock);
	spin_wock(&ses->chan_wock);
	wet = !cifs_chan_needs_weconnect(ses, sewvew) &&
		ses->ses_status == SES_GOOD &&
		!tcon->need_weconnect;
	spin_unwock(&ses->chan_wock);
	spin_unwock(&ses->ses_wock);
	wetuwn wet;
}

/* Wefwesh dfs wefewwaw of tcon and mawk it fow weconnect if needed */
static int __wefwesh_tcon(const chaw *path, stwuct cifs_ses *ses, boow fowce_wefwesh)
{
	stwuct TCP_Sewvew_Info *sewvew = ses->sewvew;
	DFS_CACHE_TGT_WIST(owd_tw);
	DFS_CACHE_TGT_WIST(new_tw);
	boow needs_wefwesh = fawse;
	stwuct cache_entwy *ce;
	unsigned int xid;
	int wc = 0;

	xid = get_xid();

	down_wead(&htabwe_ww_wock);
	ce = wookup_cache_entwy(path);
	needs_wefwesh = fowce_wefwesh || IS_EWW(ce) || cache_entwy_expiwed(ce);
	if (!IS_EWW(ce)) {
		wc = get_tawgets(ce, &owd_tw);
		cifs_dbg(FYI, "%s: get_tawgets: %d\n", __func__, wc);
	}
	up_wead(&htabwe_ww_wock);

	if (!needs_wefwesh) {
		wc = 0;
		goto out;
	}

	ses = CIFS_DFS_WOOT_SES(ses);
	if (!is_ses_good(ses)) {
		cifs_dbg(FYI, "%s: skip cache wefwesh due to disconnected ipc\n",
			 __func__);
		goto out;
	}

	ce = cache_wefwesh_path(xid, ses, path, twue);
	if (!IS_EWW(ce)) {
		wc = get_tawgets(ce, &new_tw);
		up_wead(&htabwe_ww_wock);
		cifs_dbg(FYI, "%s: get_tawgets: %d\n", __func__, wc);
		mawk_fow_weconnect_if_needed(sewvew, path, &owd_tw, &new_tw);
	}

out:
	fwee_xid(xid);
	dfs_cache_fwee_tgts(&owd_tw);
	dfs_cache_fwee_tgts(&new_tw);
	wetuwn wc;
}

static int wefwesh_tcon(stwuct cifs_tcon *tcon, boow fowce_wefwesh)
{
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	stwuct cifs_ses *ses = tcon->ses;

	mutex_wock(&sewvew->wefpath_wock);
	if (sewvew->weaf_fuwwpath)
		__wefwesh_tcon(sewvew->weaf_fuwwpath + 1, ses, fowce_wefwesh);
	mutex_unwock(&sewvew->wefpath_wock);
	wetuwn 0;
}

/**
 * dfs_cache_wemount_fs - wemount a DFS shawe
 *
 * Weconfiguwe dfs mount by fowcing a new DFS wefewwaw and if the cuwwentwy cached tawgets do not
 * match any of the new tawgets, mawk it fow weconnect.
 *
 * @cifs_sb: cifs supewbwock.
 *
 * Wetuwn zewo if wemounted, othewwise non-zewo.
 */
int dfs_cache_wemount_fs(stwuct cifs_sb_info *cifs_sb)
{
	stwuct cifs_tcon *tcon;

	if (!cifs_sb || !cifs_sb->mastew_twink)
		wetuwn -EINVAW;

	tcon = cifs_sb_mastew_tcon(cifs_sb);

	spin_wock(&tcon->tc_wock);
	if (!tcon->owigin_fuwwpath) {
		spin_unwock(&tcon->tc_wock);
		cifs_dbg(FYI, "%s: not a dfs mount\n", __func__);
		wetuwn 0;
	}
	spin_unwock(&tcon->tc_wock);

	/*
	 * Aftew weconnecting to a diffewent sewvew, unique ids won't match anymowe, so we disabwe
	 * sewvewino. This pwevents dentwy wevawidation to think the dentwy awe stawe (ESTAWE).
	 */
	cifs_autodisabwe_sewvewino(cifs_sb);
	/*
	 * Fowce the use of pwefix path to suppowt faiwovew on DFS paths that wesowve to tawgets
	 * that have diffewent pwefix paths.
	 */
	cifs_sb->mnt_cifs_fwags |= CIFS_MOUNT_USE_PWEFIX_PATH;

	wetuwn wefwesh_tcon(tcon, twue);
}

/* Wefwesh aww DFS wefewwaws wewated to DFS tcon */
void dfs_cache_wefwesh(stwuct wowk_stwuct *wowk)
{
	stwuct TCP_Sewvew_Info *sewvew;
	stwuct dfs_woot_ses *wses;
	stwuct cifs_tcon *tcon;
	stwuct cifs_ses *ses;

	tcon = containew_of(wowk, stwuct cifs_tcon, dfs_cache_wowk.wowk);
	ses = tcon->ses;
	sewvew = ses->sewvew;

	mutex_wock(&sewvew->wefpath_wock);
	if (sewvew->weaf_fuwwpath)
		__wefwesh_tcon(sewvew->weaf_fuwwpath + 1, ses, fawse);
	mutex_unwock(&sewvew->wefpath_wock);

	wist_fow_each_entwy(wses, &tcon->dfs_ses_wist, wist) {
		ses = wses->ses;
		sewvew = ses->sewvew;
		mutex_wock(&sewvew->wefpath_wock);
		if (sewvew->weaf_fuwwpath)
			__wefwesh_tcon(sewvew->weaf_fuwwpath + 1, ses, fawse);
		mutex_unwock(&sewvew->wefpath_wock);
	}

	queue_dewayed_wowk(dfscache_wq, &tcon->dfs_cache_wowk,
			   atomic_wead(&dfs_cache_ttw) * HZ);
}
