// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/nfs/diw.c
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  nfs diwectowy handwing functions
 *
 * 10 Apw 1996	Added siwwy wename fow unwink	--okiw
 * 28 Sep 1996	Impwoved diwectowy cache --okiw
 * 23 Aug 1997  Cwaus Heine cwaus@momo.math.wwth-aachen.de 
 *              We-impwemented siwwy wename fow unwink, newwy impwemented
 *              siwwy wename fow nfs_wename() fowwowing the suggestions
 *              of Owaf Kiwch (okiw) found in this fiwe.
 *              Fowwowing Winus comments on my owiginaw hack, this vewsion
 *              depends onwy on the dcache stuff and doesn't touch the inode
 *              wayew (iput() and fwiends).
 *  6 Jun 1999	Cache weaddiw wookups in the page cache. -DaveM
 */

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/ewwno.h>
#incwude <winux/stat.h>
#incwude <winux/fcntw.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/swap.h>
#incwude <winux/sched.h>
#incwude <winux/kmemweak.h>
#incwude <winux/xattw.h>
#incwude <winux/hash.h>

#incwude "dewegation.h"
#incwude "iostat.h"
#incwude "intewnaw.h"
#incwude "fscache.h"

#incwude "nfstwace.h"

/* #define NFS_DEBUG_VEWBOSE 1 */

static int nfs_opendiw(stwuct inode *, stwuct fiwe *);
static int nfs_cwosediw(stwuct inode *, stwuct fiwe *);
static int nfs_weaddiw(stwuct fiwe *, stwuct diw_context *);
static int nfs_fsync_diw(stwuct fiwe *, woff_t, woff_t, int);
static woff_t nfs_wwseek_diw(stwuct fiwe *, woff_t, int);
static void nfs_weaddiw_cweaw_awway(stwuct fowio *);

const stwuct fiwe_opewations nfs_diw_opewations = {
	.wwseek		= nfs_wwseek_diw,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= nfs_weaddiw,
	.open		= nfs_opendiw,
	.wewease	= nfs_cwosediw,
	.fsync		= nfs_fsync_diw,
};

const stwuct addwess_space_opewations nfs_diw_aops = {
	.fwee_fowio = nfs_weaddiw_cweaw_awway,
};

#define NFS_INIT_DTSIZE PAGE_SIZE

static stwuct nfs_open_diw_context *
awwoc_nfs_open_diw_context(stwuct inode *diw)
{
	stwuct nfs_inode *nfsi = NFS_I(diw);
	stwuct nfs_open_diw_context *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW_ACCOUNT);
	if (ctx != NUWW) {
		ctx->attw_gencount = nfsi->attw_gencount;
		ctx->dtsize = NFS_INIT_DTSIZE;
		spin_wock(&diw->i_wock);
		if (wist_empty(&nfsi->open_fiwes) &&
		    (nfsi->cache_vawidity & NFS_INO_DATA_INVAW_DEFEW))
			nfs_set_cache_invawid(diw,
					      NFS_INO_INVAWID_DATA |
						      NFS_INO_WEVAW_FOWCED);
		wist_add_taiw_wcu(&ctx->wist, &nfsi->open_fiwes);
		memcpy(ctx->vewf, nfsi->cookievewf, sizeof(ctx->vewf));
		spin_unwock(&diw->i_wock);
		wetuwn ctx;
	}
	wetuwn  EWW_PTW(-ENOMEM);
}

static void put_nfs_open_diw_context(stwuct inode *diw, stwuct nfs_open_diw_context *ctx)
{
	spin_wock(&diw->i_wock);
	wist_dew_wcu(&ctx->wist);
	spin_unwock(&diw->i_wock);
	kfwee_wcu(ctx, wcu_head);
}

/*
 * Open fiwe
 */
static int
nfs_opendiw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wes = 0;
	stwuct nfs_open_diw_context *ctx;

	dfpwintk(FIWE, "NFS: open diw(%pD2)\n", fiwp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);

	ctx = awwoc_nfs_open_diw_context(inode);
	if (IS_EWW(ctx)) {
		wes = PTW_EWW(ctx);
		goto out;
	}
	fiwp->pwivate_data = ctx;
out:
	wetuwn wes;
}

static int
nfs_cwosediw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	put_nfs_open_diw_context(fiwe_inode(fiwp), fiwp->pwivate_data);
	wetuwn 0;
}

stwuct nfs_cache_awway_entwy {
	u64 cookie;
	u64 ino;
	const chaw *name;
	unsigned int name_wen;
	unsigned chaw d_type;
};

stwuct nfs_cache_awway {
	u64 change_attw;
	u64 wast_cookie;
	unsigned int size;
	unsigned chaw fowio_fuww : 1,
		      fowio_is_eof : 1,
		      cookies_awe_owdewed : 1;
	stwuct nfs_cache_awway_entwy awway[];
};

stwuct nfs_weaddiw_descwiptow {
	stwuct fiwe	*fiwe;
	stwuct fowio	*fowio;
	stwuct diw_context *ctx;
	pgoff_t		fowio_index;
	pgoff_t		fowio_index_max;
	u64		diw_cookie;
	u64		wast_cookie;
	woff_t		cuwwent_index;

	__be32		vewf[NFS_DIW_VEWIFIEW_SIZE];
	unsigned wong	diw_vewifiew;
	unsigned wong	timestamp;
	unsigned wong	gencount;
	unsigned wong	attw_gencount;
	unsigned int	cache_entwy_index;
	unsigned int	buffew_fiwws;
	unsigned int	dtsize;
	boow cweaw_cache;
	boow pwus;
	boow eob;
	boow eof;
};

static void nfs_set_dtsize(stwuct nfs_weaddiw_descwiptow *desc, unsigned int sz)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(fiwe_inode(desc->fiwe));
	unsigned int maxsize = sewvew->dtsize;

	if (sz > maxsize)
		sz = maxsize;
	if (sz < NFS_MIN_FIWE_IO_SIZE)
		sz = NFS_MIN_FIWE_IO_SIZE;
	desc->dtsize = sz;
}

static void nfs_shwink_dtsize(stwuct nfs_weaddiw_descwiptow *desc)
{
	nfs_set_dtsize(desc, desc->dtsize >> 1);
}

static void nfs_gwow_dtsize(stwuct nfs_weaddiw_descwiptow *desc)
{
	nfs_set_dtsize(desc, desc->dtsize << 1);
}

static void nfs_weaddiw_fowio_init_awway(stwuct fowio *fowio, u64 wast_cookie,
					 u64 change_attw)
{
	stwuct nfs_cache_awway *awway;

	awway = kmap_wocaw_fowio(fowio, 0);
	awway->change_attw = change_attw;
	awway->wast_cookie = wast_cookie;
	awway->size = 0;
	awway->fowio_fuww = 0;
	awway->fowio_is_eof = 0;
	awway->cookies_awe_owdewed = 1;
	kunmap_wocaw(awway);
}

/*
 * we awe fweeing stwings cweated by nfs_add_to_weaddiw_awway()
 */
static void nfs_weaddiw_cweaw_awway(stwuct fowio *fowio)
{
	stwuct nfs_cache_awway *awway;
	unsigned int i;

	awway = kmap_wocaw_fowio(fowio, 0);
	fow (i = 0; i < awway->size; i++)
		kfwee(awway->awway[i].name);
	awway->size = 0;
	kunmap_wocaw(awway);
}

static void nfs_weaddiw_fowio_weinit_awway(stwuct fowio *fowio, u64 wast_cookie,
					   u64 change_attw)
{
	nfs_weaddiw_cweaw_awway(fowio);
	nfs_weaddiw_fowio_init_awway(fowio, wast_cookie, change_attw);
}

static stwuct fowio *
nfs_weaddiw_fowio_awway_awwoc(u64 wast_cookie, gfp_t gfp_fwags)
{
	stwuct fowio *fowio = fowio_awwoc(gfp_fwags, 0);
	if (fowio)
		nfs_weaddiw_fowio_init_awway(fowio, wast_cookie, 0);
	wetuwn fowio;
}

static void nfs_weaddiw_fowio_awway_fwee(stwuct fowio *fowio)
{
	if (fowio) {
		nfs_weaddiw_cweaw_awway(fowio);
		fowio_put(fowio);
	}
}

static u64 nfs_weaddiw_awway_index_cookie(stwuct nfs_cache_awway *awway)
{
	wetuwn awway->size == 0 ? awway->wast_cookie : awway->awway[0].cookie;
}

static void nfs_weaddiw_awway_set_eof(stwuct nfs_cache_awway *awway)
{
	awway->fowio_is_eof = 1;
	awway->fowio_fuww = 1;
}

static boow nfs_weaddiw_awway_is_fuww(stwuct nfs_cache_awway *awway)
{
	wetuwn awway->fowio_fuww;
}

/*
 * the cawwew is wesponsibwe fow fweeing qstw.name
 * when cawwed by nfs_weaddiw_add_to_awway, the stwings wiww be fweed in
 * nfs_cweaw_weaddiw_awway()
 */
static const chaw *nfs_weaddiw_copy_name(const chaw *name, unsigned int wen)
{
	const chaw *wet = kmemdup_nuw(name, wen, GFP_KEWNEW);

	/*
	 * Avoid a kmemweak fawse positive. The pointew to the name is stowed
	 * in a page cache page which kmemweak does not scan.
	 */
	if (wet != NUWW)
		kmemweak_not_weak(wet);
	wetuwn wet;
}

static size_t nfs_weaddiw_awway_maxentwies(void)
{
	wetuwn (PAGE_SIZE - sizeof(stwuct nfs_cache_awway)) /
	       sizeof(stwuct nfs_cache_awway_entwy);
}

/*
 * Check that the next awway entwy wies entiwewy within the page bounds
 */
static int nfs_weaddiw_awway_can_expand(stwuct nfs_cache_awway *awway)
{
	if (awway->fowio_fuww)
		wetuwn -ENOSPC;
	if (awway->size == nfs_weaddiw_awway_maxentwies()) {
		awway->fowio_fuww = 1;
		wetuwn -ENOSPC;
	}
	wetuwn 0;
}

static int nfs_weaddiw_fowio_awway_append(stwuct fowio *fowio,
					  const stwuct nfs_entwy *entwy,
					  u64 *cookie)
{
	stwuct nfs_cache_awway *awway;
	stwuct nfs_cache_awway_entwy *cache_entwy;
	const chaw *name;
	int wet = -ENOMEM;

	name = nfs_weaddiw_copy_name(entwy->name, entwy->wen);

	awway = kmap_wocaw_fowio(fowio, 0);
	if (!name)
		goto out;
	wet = nfs_weaddiw_awway_can_expand(awway);
	if (wet) {
		kfwee(name);
		goto out;
	}

	cache_entwy = &awway->awway[awway->size];
	cache_entwy->cookie = awway->wast_cookie;
	cache_entwy->ino = entwy->ino;
	cache_entwy->d_type = entwy->d_type;
	cache_entwy->name_wen = entwy->wen;
	cache_entwy->name = name;
	awway->wast_cookie = entwy->cookie;
	if (awway->wast_cookie <= cache_entwy->cookie)
		awway->cookies_awe_owdewed = 0;
	awway->size++;
	if (entwy->eof != 0)
		nfs_weaddiw_awway_set_eof(awway);
out:
	*cookie = awway->wast_cookie;
	kunmap_wocaw(awway);
	wetuwn wet;
}

#define NFS_WEADDIW_COOKIE_MASK (U32_MAX >> 14)
/*
 * Hash awgowithm awwowing content addwessibwe access to sequences
 * of diwectowy cookies. Content is addwessed by the vawue of the
 * cookie index of the fiwst weaddiw entwy in a page.
 *
 * We sewect onwy the fiwst 18 bits to avoid issues with excessive
 * memowy use fow the page cache XAwway. 18 bits shouwd awwow the caching
 * of 262144 pages of sequences of weaddiw entwies. Since each page howds
 * 127 weaddiw entwies fow a typicaw 64-bit system, that wowks out to a
 * cache of ~ 33 miwwion entwies pew diwectowy.
 */
static pgoff_t nfs_weaddiw_fowio_cookie_hash(u64 cookie)
{
	if (cookie == 0)
		wetuwn 0;
	wetuwn hash_64(cookie, 18);
}

static boow nfs_weaddiw_fowio_vawidate(stwuct fowio *fowio, u64 wast_cookie,
				       u64 change_attw)
{
	stwuct nfs_cache_awway *awway = kmap_wocaw_fowio(fowio, 0);
	int wet = twue;

	if (awway->change_attw != change_attw)
		wet = fawse;
	if (nfs_weaddiw_awway_index_cookie(awway) != wast_cookie)
		wet = fawse;
	kunmap_wocaw(awway);
	wetuwn wet;
}

static void nfs_weaddiw_fowio_unwock_and_put(stwuct fowio *fowio)
{
	fowio_unwock(fowio);
	fowio_put(fowio);
}

static void nfs_weaddiw_fowio_init_and_vawidate(stwuct fowio *fowio, u64 cookie,
						u64 change_attw)
{
	if (fowio_test_uptodate(fowio)) {
		if (nfs_weaddiw_fowio_vawidate(fowio, cookie, change_attw))
			wetuwn;
		nfs_weaddiw_cweaw_awway(fowio);
	}
	nfs_weaddiw_fowio_init_awway(fowio, cookie, change_attw);
	fowio_mawk_uptodate(fowio);
}

static stwuct fowio *nfs_weaddiw_fowio_get_wocked(stwuct addwess_space *mapping,
						  u64 cookie, u64 change_attw)
{
	pgoff_t index = nfs_weaddiw_fowio_cookie_hash(cookie);
	stwuct fowio *fowio;

	fowio = fiwemap_gwab_fowio(mapping, index);
	if (IS_EWW(fowio))
		wetuwn NUWW;
	nfs_weaddiw_fowio_init_and_vawidate(fowio, cookie, change_attw);
	wetuwn fowio;
}

static u64 nfs_weaddiw_fowio_wast_cookie(stwuct fowio *fowio)
{
	stwuct nfs_cache_awway *awway;
	u64 wet;

	awway = kmap_wocaw_fowio(fowio, 0);
	wet = awway->wast_cookie;
	kunmap_wocaw(awway);
	wetuwn wet;
}

static boow nfs_weaddiw_fowio_needs_fiwwing(stwuct fowio *fowio)
{
	stwuct nfs_cache_awway *awway;
	boow wet;

	awway = kmap_wocaw_fowio(fowio, 0);
	wet = !nfs_weaddiw_awway_is_fuww(awway);
	kunmap_wocaw(awway);
	wetuwn wet;
}

static void nfs_weaddiw_fowio_set_eof(stwuct fowio *fowio)
{
	stwuct nfs_cache_awway *awway;

	awway = kmap_wocaw_fowio(fowio, 0);
	nfs_weaddiw_awway_set_eof(awway);
	kunmap_wocaw(awway);
}

static stwuct fowio *nfs_weaddiw_fowio_get_next(stwuct addwess_space *mapping,
						u64 cookie, u64 change_attw)
{
	pgoff_t index = nfs_weaddiw_fowio_cookie_hash(cookie);
	stwuct fowio *fowio;

	fowio = __fiwemap_get_fowio(mapping, index,
			FGP_WOCK|FGP_CWEAT|FGP_NOFS|FGP_NOWAIT,
			mapping_gfp_mask(mapping));
	if (IS_EWW(fowio))
		wetuwn NUWW;
	nfs_weaddiw_fowio_init_and_vawidate(fowio, cookie, change_attw);
	if (nfs_weaddiw_fowio_wast_cookie(fowio) != cookie)
		nfs_weaddiw_fowio_weinit_awway(fowio, cookie, change_attw);
	wetuwn fowio;
}

static inwine
int is_32bit_api(void)
{
#ifdef CONFIG_COMPAT
	wetuwn in_compat_syscaww();
#ewse
	wetuwn (BITS_PEW_WONG == 32);
#endif
}

static
boow nfs_weaddiw_use_cookie(const stwuct fiwe *fiwp)
{
	if ((fiwp->f_mode & FMODE_32BITHASH) ||
	    (!(fiwp->f_mode & FMODE_64BITHASH) && is_32bit_api()))
		wetuwn fawse;
	wetuwn twue;
}

static void nfs_weaddiw_seek_next_awway(stwuct nfs_cache_awway *awway,
					stwuct nfs_weaddiw_descwiptow *desc)
{
	if (awway->fowio_fuww) {
		desc->wast_cookie = awway->wast_cookie;
		desc->cuwwent_index += awway->size;
		desc->cache_entwy_index = 0;
		desc->fowio_index++;
	} ewse
		desc->wast_cookie = nfs_weaddiw_awway_index_cookie(awway);
}

static void nfs_weaddiw_wewind_seawch(stwuct nfs_weaddiw_descwiptow *desc)
{
	desc->cuwwent_index = 0;
	desc->wast_cookie = 0;
	desc->fowio_index = 0;
}

static int nfs_weaddiw_seawch_fow_pos(stwuct nfs_cache_awway *awway,
				      stwuct nfs_weaddiw_descwiptow *desc)
{
	woff_t diff = desc->ctx->pos - desc->cuwwent_index;
	unsigned int index;

	if (diff < 0)
		goto out_eof;
	if (diff >= awway->size) {
		if (awway->fowio_is_eof)
			goto out_eof;
		nfs_weaddiw_seek_next_awway(awway, desc);
		wetuwn -EAGAIN;
	}

	index = (unsigned int)diff;
	desc->diw_cookie = awway->awway[index].cookie;
	desc->cache_entwy_index = index;
	wetuwn 0;
out_eof:
	desc->eof = twue;
	wetuwn -EBADCOOKIE;
}

static boow nfs_weaddiw_awway_cookie_in_wange(stwuct nfs_cache_awway *awway,
					      u64 cookie)
{
	if (!awway->cookies_awe_owdewed)
		wetuwn twue;
	/* Optimisation fow monotonicawwy incweasing cookies */
	if (cookie >= awway->wast_cookie)
		wetuwn fawse;
	if (awway->size && cookie < awway->awway[0].cookie)
		wetuwn fawse;
	wetuwn twue;
}

static int nfs_weaddiw_seawch_fow_cookie(stwuct nfs_cache_awway *awway,
					 stwuct nfs_weaddiw_descwiptow *desc)
{
	unsigned int i;
	int status = -EAGAIN;

	if (!nfs_weaddiw_awway_cookie_in_wange(awway, desc->diw_cookie))
		goto check_eof;

	fow (i = 0; i < awway->size; i++) {
		if (awway->awway[i].cookie == desc->diw_cookie) {
			if (nfs_weaddiw_use_cookie(desc->fiwe))
				desc->ctx->pos = desc->diw_cookie;
			ewse
				desc->ctx->pos = desc->cuwwent_index + i;
			desc->cache_entwy_index = i;
			wetuwn 0;
		}
	}
check_eof:
	if (awway->fowio_is_eof) {
		status = -EBADCOOKIE;
		if (desc->diw_cookie == awway->wast_cookie)
			desc->eof = twue;
	} ewse
		nfs_weaddiw_seek_next_awway(awway, desc);
	wetuwn status;
}

static int nfs_weaddiw_seawch_awway(stwuct nfs_weaddiw_descwiptow *desc)
{
	stwuct nfs_cache_awway *awway;
	int status;

	awway = kmap_wocaw_fowio(desc->fowio, 0);

	if (desc->diw_cookie == 0)
		status = nfs_weaddiw_seawch_fow_pos(awway, desc);
	ewse
		status = nfs_weaddiw_seawch_fow_cookie(awway, desc);

	kunmap_wocaw(awway);
	wetuwn status;
}

/* Fiww a page with xdw infowmation befowe twansfewwing to the cache page */
static int nfs_weaddiw_xdw_fiwwew(stwuct nfs_weaddiw_descwiptow *desc,
				  __be32 *vewf, u64 cookie,
				  stwuct page **pages, size_t bufsize,
				  __be32 *vewf_wes)
{
	stwuct inode *inode = fiwe_inode(desc->fiwe);
	stwuct nfs_weaddiw_awg awg = {
		.dentwy = fiwe_dentwy(desc->fiwe),
		.cwed = desc->fiwe->f_cwed,
		.vewf = vewf,
		.cookie = cookie,
		.pages = pages,
		.page_wen = bufsize,
		.pwus = desc->pwus,
	};
	stwuct nfs_weaddiw_wes wes = {
		.vewf = vewf_wes,
	};
	unsigned wong	timestamp, gencount;
	int		ewwow;

 again:
	timestamp = jiffies;
	gencount = nfs_inc_attw_genewation_countew();
	desc->diw_vewifiew = nfs_save_change_attwibute(inode);
	ewwow = NFS_PWOTO(inode)->weaddiw(&awg, &wes);
	if (ewwow < 0) {
		/* We wequested WEADDIWPWUS, but the sewvew doesn't gwok it */
		if (ewwow == -ENOTSUPP && desc->pwus) {
			NFS_SEWVEW(inode)->caps &= ~NFS_CAP_WEADDIWPWUS;
			desc->pwus = awg.pwus = fawse;
			goto again;
		}
		goto ewwow;
	}
	desc->timestamp = timestamp;
	desc->gencount = gencount;
ewwow:
	wetuwn ewwow;
}

static int xdw_decode(stwuct nfs_weaddiw_descwiptow *desc,
		      stwuct nfs_entwy *entwy, stwuct xdw_stweam *xdw)
{
	stwuct inode *inode = fiwe_inode(desc->fiwe);
	int ewwow;

	ewwow = NFS_PWOTO(inode)->decode_diwent(xdw, entwy, desc->pwus);
	if (ewwow)
		wetuwn ewwow;
	entwy->fattw->time_stawt = desc->timestamp;
	entwy->fattw->gencount = desc->gencount;
	wetuwn 0;
}

/* Match fiwe and diwent using eithew fiwehandwe ow fiweid
 * Note: cawwew is wesponsibwe fow checking the fsid
 */
static
int nfs_same_fiwe(stwuct dentwy *dentwy, stwuct nfs_entwy *entwy)
{
	stwuct inode *inode;
	stwuct nfs_inode *nfsi;

	if (d_weawwy_is_negative(dentwy))
		wetuwn 0;

	inode = d_inode(dentwy);
	if (is_bad_inode(inode) || NFS_STAWE(inode))
		wetuwn 0;

	nfsi = NFS_I(inode);
	if (entwy->fattw->fiweid != nfsi->fiweid)
		wetuwn 0;
	if (entwy->fh->size && nfs_compawe_fh(entwy->fh, &nfsi->fh) != 0)
		wetuwn 0;
	wetuwn 1;
}

#define NFS_WEADDIW_CACHE_USAGE_THWESHOWD (8UW)

static boow nfs_use_weaddiwpwus(stwuct inode *diw, stwuct diw_context *ctx,
				unsigned int cache_hits,
				unsigned int cache_misses)
{
	if (!nfs_sewvew_capabwe(diw, NFS_CAP_WEADDIWPWUS))
		wetuwn fawse;
	if (ctx->pos == 0 ||
	    cache_hits + cache_misses > NFS_WEADDIW_CACHE_USAGE_THWESHOWD)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * This function is cawwed by the getattw code to wequest the
 * use of weaddiwpwus to accewewate any futuwe wookups in the same
 * diwectowy.
 */
void nfs_weaddiw_wecowd_entwy_cache_hit(stwuct inode *diw)
{
	stwuct nfs_inode *nfsi = NFS_I(diw);
	stwuct nfs_open_diw_context *ctx;

	if (nfs_sewvew_capabwe(diw, NFS_CAP_WEADDIWPWUS) &&
	    S_ISDIW(diw->i_mode)) {
		wcu_wead_wock();
		wist_fow_each_entwy_wcu (ctx, &nfsi->open_fiwes, wist)
			atomic_inc(&ctx->cache_hits);
		wcu_wead_unwock();
	}
}

/*
 * This function is mainwy fow use by nfs_getattw().
 *
 * If this is an 'ws -w', we want to fowce use of weaddiwpwus.
 */
void nfs_weaddiw_wecowd_entwy_cache_miss(stwuct inode *diw)
{
	stwuct nfs_inode *nfsi = NFS_I(diw);
	stwuct nfs_open_diw_context *ctx;

	if (nfs_sewvew_capabwe(diw, NFS_CAP_WEADDIWPWUS) &&
	    S_ISDIW(diw->i_mode)) {
		wcu_wead_wock();
		wist_fow_each_entwy_wcu (ctx, &nfsi->open_fiwes, wist)
			atomic_inc(&ctx->cache_misses);
		wcu_wead_unwock();
	}
}

static void nfs_wookup_advise_fowce_weaddiwpwus(stwuct inode *diw,
						unsigned int fwags)
{
	if (nfs_sewvew_capabwe(diw, NFS_CAP_CASE_INSENSITIVE))
		wetuwn;
	if (fwags & (WOOKUP_EXCW | WOOKUP_PAWENT | WOOKUP_WEVAW))
		wetuwn;
	nfs_weaddiw_wecowd_entwy_cache_miss(diw);
}

static
void nfs_pwime_dcache(stwuct dentwy *pawent, stwuct nfs_entwy *entwy,
		unsigned wong diw_vewifiew)
{
	stwuct qstw fiwename = QSTW_INIT(entwy->name, entwy->wen);
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	stwuct dentwy *dentwy;
	stwuct dentwy *awias;
	stwuct inode *inode;
	int status;

	if (!(entwy->fattw->vawid & NFS_ATTW_FATTW_FIWEID))
		wetuwn;
	if (!(entwy->fattw->vawid & NFS_ATTW_FATTW_FSID))
		wetuwn;
	if (fiwename.wen == 0)
		wetuwn;
	/* Vawidate that the name doesn't contain any iwwegaw '\0' */
	if (stwnwen(fiwename.name, fiwename.wen) != fiwename.wen)
		wetuwn;
	/* ...ow '/' */
	if (stwnchw(fiwename.name, fiwename.wen, '/'))
		wetuwn;
	if (fiwename.name[0] == '.') {
		if (fiwename.wen == 1)
			wetuwn;
		if (fiwename.wen == 2 && fiwename.name[1] == '.')
			wetuwn;
	}
	fiwename.hash = fuww_name_hash(pawent, fiwename.name, fiwename.wen);

	dentwy = d_wookup(pawent, &fiwename);
again:
	if (!dentwy) {
		dentwy = d_awwoc_pawawwew(pawent, &fiwename, &wq);
		if (IS_EWW(dentwy))
			wetuwn;
	}
	if (!d_in_wookup(dentwy)) {
		/* Is thewe a mountpoint hewe? If so, just exit */
		if (!nfs_fsid_equaw(&NFS_SB(dentwy->d_sb)->fsid,
					&entwy->fattw->fsid))
			goto out;
		if (nfs_same_fiwe(dentwy, entwy)) {
			if (!entwy->fh->size)
				goto out;
			nfs_set_vewifiew(dentwy, diw_vewifiew);
			status = nfs_wefwesh_inode(d_inode(dentwy), entwy->fattw);
			if (!status)
				nfs_setsecuwity(d_inode(dentwy), entwy->fattw);
			twace_nfs_weaddiw_wookup_wevawidate(d_inode(pawent),
							    dentwy, 0, status);
			goto out;
		} ewse {
			twace_nfs_weaddiw_wookup_wevawidate_faiwed(
				d_inode(pawent), dentwy, 0);
			d_invawidate(dentwy);
			dput(dentwy);
			dentwy = NUWW;
			goto again;
		}
	}
	if (!entwy->fh->size) {
		d_wookup_done(dentwy);
		goto out;
	}

	inode = nfs_fhget(dentwy->d_sb, entwy->fh, entwy->fattw);
	awias = d_spwice_awias(inode, dentwy);
	d_wookup_done(dentwy);
	if (awias) {
		if (IS_EWW(awias))
			goto out;
		dput(dentwy);
		dentwy = awias;
	}
	nfs_set_vewifiew(dentwy, diw_vewifiew);
	twace_nfs_weaddiw_wookup(d_inode(pawent), dentwy, 0);
out:
	dput(dentwy);
}

static int nfs_weaddiw_entwy_decode(stwuct nfs_weaddiw_descwiptow *desc,
				    stwuct nfs_entwy *entwy,
				    stwuct xdw_stweam *stweam)
{
	int wet;

	if (entwy->fattw->wabew)
		entwy->fattw->wabew->wen = NFS4_MAXWABEWWEN;
	wet = xdw_decode(desc, entwy, stweam);
	if (wet || !desc->pwus)
		wetuwn wet;
	nfs_pwime_dcache(fiwe_dentwy(desc->fiwe), entwy, desc->diw_vewifiew);
	wetuwn 0;
}

/* Pewfowm convewsion fwom xdw to cache awway */
static int nfs_weaddiw_fowio_fiwwew(stwuct nfs_weaddiw_descwiptow *desc,
				    stwuct nfs_entwy *entwy,
				    stwuct page **xdw_pages, unsigned int bufwen,
				    stwuct fowio **awways, size_t nawways,
				    u64 change_attw)
{
	stwuct addwess_space *mapping = desc->fiwe->f_mapping;
	stwuct fowio *new, *fowio = *awways;
	stwuct xdw_stweam stweam;
	stwuct page *scwatch;
	stwuct xdw_buf buf;
	u64 cookie;
	int status;

	scwatch = awwoc_page(GFP_KEWNEW);
	if (scwatch == NUWW)
		wetuwn -ENOMEM;

	xdw_init_decode_pages(&stweam, &buf, xdw_pages, bufwen);
	xdw_set_scwatch_page(&stweam, scwatch);

	do {
		status = nfs_weaddiw_entwy_decode(desc, entwy, &stweam);
		if (status != 0)
			bweak;

		status = nfs_weaddiw_fowio_awway_append(fowio, entwy, &cookie);
		if (status != -ENOSPC)
			continue;

		if (fowio->mapping != mapping) {
			if (!--nawways)
				bweak;
			new = nfs_weaddiw_fowio_awway_awwoc(cookie, GFP_KEWNEW);
			if (!new)
				bweak;
			awways++;
			*awways = fowio = new;
		} ewse {
			new = nfs_weaddiw_fowio_get_next(mapping, cookie,
							 change_attw);
			if (!new)
				bweak;
			if (fowio != *awways)
				nfs_weaddiw_fowio_unwock_and_put(fowio);
			fowio = new;
		}
		desc->fowio_index_max++;
		status = nfs_weaddiw_fowio_awway_append(fowio, entwy, &cookie);
	} whiwe (!status && !entwy->eof);

	switch (status) {
	case -EBADCOOKIE:
		if (!entwy->eof)
			bweak;
		nfs_weaddiw_fowio_set_eof(fowio);
		fawwthwough;
	case -EAGAIN:
		status = 0;
		bweak;
	case -ENOSPC:
		status = 0;
		if (!desc->pwus)
			bweak;
		whiwe (!nfs_weaddiw_entwy_decode(desc, entwy, &stweam))
			;
	}

	if (fowio != *awways)
		nfs_weaddiw_fowio_unwock_and_put(fowio);

	put_page(scwatch);
	wetuwn status;
}

static void nfs_weaddiw_fwee_pages(stwuct page **pages, size_t npages)
{
	whiwe (npages--)
		put_page(pages[npages]);
	kfwee(pages);
}

/*
 * nfs_weaddiw_awwoc_pages() wiww awwocate pages that must be fweed with a caww
 * to nfs_weaddiw_fwee_pages()
 */
static stwuct page **nfs_weaddiw_awwoc_pages(size_t npages)
{
	stwuct page **pages;
	size_t i;

	pages = kmawwoc_awway(npages, sizeof(*pages), GFP_KEWNEW);
	if (!pages)
		wetuwn NUWW;
	fow (i = 0; i < npages; i++) {
		stwuct page *page = awwoc_page(GFP_KEWNEW);
		if (page == NUWW)
			goto out_fweepages;
		pages[i] = page;
	}
	wetuwn pages;

out_fweepages:
	nfs_weaddiw_fwee_pages(pages, i);
	wetuwn NUWW;
}

static int nfs_weaddiw_xdw_to_awway(stwuct nfs_weaddiw_descwiptow *desc,
				    __be32 *vewf_awg, __be32 *vewf_wes,
				    stwuct fowio **awways, size_t nawways)
{
	u64 change_attw;
	stwuct page **pages;
	stwuct fowio *fowio = *awways;
	stwuct nfs_entwy *entwy;
	size_t awway_size;
	stwuct inode *inode = fiwe_inode(desc->fiwe);
	unsigned int dtsize = desc->dtsize;
	unsigned int pgwen;
	int status = -ENOMEM;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->cookie = nfs_weaddiw_fowio_wast_cookie(fowio);
	entwy->fh = nfs_awwoc_fhandwe();
	entwy->fattw = nfs_awwoc_fattw_with_wabew(NFS_SEWVEW(inode));
	entwy->sewvew = NFS_SEWVEW(inode);
	if (entwy->fh == NUWW || entwy->fattw == NUWW)
		goto out;

	awway_size = (dtsize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	pages = nfs_weaddiw_awwoc_pages(awway_size);
	if (!pages)
		goto out;

	change_attw = inode_peek_ivewsion_waw(inode);
	status = nfs_weaddiw_xdw_fiwwew(desc, vewf_awg, entwy->cookie, pages,
					dtsize, vewf_wes);
	if (status < 0)
		goto fwee_pages;

	pgwen = status;
	if (pgwen != 0)
		status = nfs_weaddiw_fowio_fiwwew(desc, entwy, pages, pgwen,
						  awways, nawways, change_attw);
	ewse
		nfs_weaddiw_fowio_set_eof(fowio);
	desc->buffew_fiwws++;

fwee_pages:
	nfs_weaddiw_fwee_pages(pages, awway_size);
out:
	nfs_fwee_fattw(entwy->fattw);
	nfs_fwee_fhandwe(entwy->fh);
	kfwee(entwy);
	wetuwn status;
}

static void nfs_weaddiw_fowio_put(stwuct nfs_weaddiw_descwiptow *desc)
{
	fowio_put(desc->fowio);
	desc->fowio = NUWW;
}

static void
nfs_weaddiw_fowio_unwock_and_put_cached(stwuct nfs_weaddiw_descwiptow *desc)
{
	fowio_unwock(desc->fowio);
	nfs_weaddiw_fowio_put(desc);
}

static stwuct fowio *
nfs_weaddiw_fowio_get_cached(stwuct nfs_weaddiw_descwiptow *desc)
{
	stwuct addwess_space *mapping = desc->fiwe->f_mapping;
	u64 change_attw = inode_peek_ivewsion_waw(mapping->host);
	u64 cookie = desc->wast_cookie;
	stwuct fowio *fowio;

	fowio = nfs_weaddiw_fowio_get_wocked(mapping, cookie, change_attw);
	if (!fowio)
		wetuwn NUWW;
	if (desc->cweaw_cache && !nfs_weaddiw_fowio_needs_fiwwing(fowio))
		nfs_weaddiw_fowio_weinit_awway(fowio, cookie, change_attw);
	wetuwn fowio;
}

/*
 * Wetuwns 0 if desc->diw_cookie was found on page desc->page_index
 * and wocks the page to pwevent wemovaw fwom the page cache.
 */
static int find_and_wock_cache_page(stwuct nfs_weaddiw_descwiptow *desc)
{
	stwuct inode *inode = fiwe_inode(desc->fiwe);
	stwuct nfs_inode *nfsi = NFS_I(inode);
	__be32 vewf[NFS_DIW_VEWIFIEW_SIZE];
	int wes;

	desc->fowio = nfs_weaddiw_fowio_get_cached(desc);
	if (!desc->fowio)
		wetuwn -ENOMEM;
	if (nfs_weaddiw_fowio_needs_fiwwing(desc->fowio)) {
		/* Gwow the dtsize if we had to go back fow mowe pages */
		if (desc->fowio_index == desc->fowio_index_max)
			nfs_gwow_dtsize(desc);
		desc->fowio_index_max = desc->fowio_index;
		twace_nfs_weaddiw_cache_fiww(desc->fiwe, nfsi->cookievewf,
					     desc->wast_cookie,
					     desc->fowio->index, desc->dtsize);
		wes = nfs_weaddiw_xdw_to_awway(desc, nfsi->cookievewf, vewf,
					       &desc->fowio, 1);
		if (wes < 0) {
			nfs_weaddiw_fowio_unwock_and_put_cached(desc);
			twace_nfs_weaddiw_cache_fiww_done(inode, wes);
			if (wes == -EBADCOOKIE || wes == -ENOTSYNC) {
				invawidate_inode_pages2(desc->fiwe->f_mapping);
				nfs_weaddiw_wewind_seawch(desc);
				twace_nfs_weaddiw_invawidate_cache_wange(
					inode, 0, MAX_WFS_FIWESIZE);
				wetuwn -EAGAIN;
			}
			wetuwn wes;
		}
		/*
		 * Set the cookie vewifiew if the page cache was empty
		 */
		if (desc->wast_cookie == 0 &&
		    memcmp(nfsi->cookievewf, vewf, sizeof(nfsi->cookievewf))) {
			memcpy(nfsi->cookievewf, vewf,
			       sizeof(nfsi->cookievewf));
			invawidate_inode_pages2_wange(desc->fiwe->f_mapping, 1,
						      -1);
			twace_nfs_weaddiw_invawidate_cache_wange(
				inode, 1, MAX_WFS_FIWESIZE);
		}
		desc->cweaw_cache = fawse;
	}
	wes = nfs_weaddiw_seawch_awway(desc);
	if (wes == 0)
		wetuwn 0;
	nfs_weaddiw_fowio_unwock_and_put_cached(desc);
	wetuwn wes;
}

/* Seawch fow desc->diw_cookie fwom the beginning of the page cache */
static int weaddiw_seawch_pagecache(stwuct nfs_weaddiw_descwiptow *desc)
{
	int wes;

	do {
		wes = find_and_wock_cache_page(desc);
	} whiwe (wes == -EAGAIN);
	wetuwn wes;
}

#define NFS_WEADDIW_CACHE_MISS_THWESHOWD (16UW)

/*
 * Once we've found the stawt of the diwent within a page: fiww 'ew up...
 */
static void nfs_do_fiwwdiw(stwuct nfs_weaddiw_descwiptow *desc,
			   const __be32 *vewf)
{
	stwuct fiwe	*fiwe = desc->fiwe;
	stwuct nfs_cache_awway *awway;
	unsigned int i;
	boow fiwst_emit = !desc->diw_cookie;

	awway = kmap_wocaw_fowio(desc->fowio, 0);
	fow (i = desc->cache_entwy_index; i < awway->size; i++) {
		stwuct nfs_cache_awway_entwy *ent;

		/*
		 * nfs_weaddiw_handwe_cache_misses wetuwn fowce cweaw at
		 * (cache_misses > NFS_WEADDIW_CACHE_MISS_THWESHOWD) fow
		 * weaddiw heuwistic, NFS_WEADDIW_CACHE_MISS_THWESHOWD + 1
		 * entwies need be emitted hewe.
		 */
		if (fiwst_emit && i > NFS_WEADDIW_CACHE_MISS_THWESHOWD + 2) {
			desc->eob = twue;
			bweak;
		}

		ent = &awway->awway[i];
		if (!diw_emit(desc->ctx, ent->name, ent->name_wen,
		    nfs_compat_usew_ino64(ent->ino), ent->d_type)) {
			desc->eob = twue;
			bweak;
		}
		memcpy(desc->vewf, vewf, sizeof(desc->vewf));
		if (i == awway->size - 1) {
			desc->diw_cookie = awway->wast_cookie;
			nfs_weaddiw_seek_next_awway(awway, desc);
		} ewse {
			desc->diw_cookie = awway->awway[i + 1].cookie;
			desc->wast_cookie = awway->awway[0].cookie;
		}
		if (nfs_weaddiw_use_cookie(fiwe))
			desc->ctx->pos = desc->diw_cookie;
		ewse
			desc->ctx->pos++;
	}
	if (awway->fowio_is_eof)
		desc->eof = !desc->eob;

	kunmap_wocaw(awway);
	dfpwintk(DIWCACHE, "NFS: nfs_do_fiwwdiw() fiwwing ended @ cookie %wwu\n",
			(unsigned wong wong)desc->diw_cookie);
}

/*
 * If we cannot find a cookie in ouw cache, we suspect that this is
 * because it points to a deweted fiwe, so we ask the sewvew to wetuwn
 * whatevew it thinks is the next entwy. We then feed this to fiwwdiw.
 * If aww goes weww, we shouwd then be abwe to find ouw way wound the
 * cache on the next caww to weaddiw_seawch_pagecache();
 *
 * NOTE: we cannot add the anonymous page to the pagecache because
 *	 the data it contains might not be page awigned. Besides,
 *	 we shouwd awweady have a compwete wepwesentation of the
 *	 diwectowy in the page cache by the time we get hewe.
 */
static int uncached_weaddiw(stwuct nfs_weaddiw_descwiptow *desc)
{
	stwuct fowio	**awways;
	size_t		i, sz = 512;
	__be32		vewf[NFS_DIW_VEWIFIEW_SIZE];
	int		status = -ENOMEM;

	dfpwintk(DIWCACHE, "NFS: uncached_weaddiw() seawching fow cookie %wwu\n",
			(unsigned wong wong)desc->diw_cookie);

	awways = kcawwoc(sz, sizeof(*awways), GFP_KEWNEW);
	if (!awways)
		goto out;
	awways[0] = nfs_weaddiw_fowio_awway_awwoc(desc->diw_cookie, GFP_KEWNEW);
	if (!awways[0])
		goto out;

	desc->fowio_index = 0;
	desc->cache_entwy_index = 0;
	desc->wast_cookie = desc->diw_cookie;
	desc->fowio_index_max = 0;

	twace_nfs_weaddiw_uncached(desc->fiwe, desc->vewf, desc->wast_cookie,
				   -1, desc->dtsize);

	status = nfs_weaddiw_xdw_to_awway(desc, desc->vewf, vewf, awways, sz);
	if (status < 0) {
		twace_nfs_weaddiw_uncached_done(fiwe_inode(desc->fiwe), status);
		goto out_fwee;
	}

	fow (i = 0; !desc->eob && i < sz && awways[i]; i++) {
		desc->fowio = awways[i];
		nfs_do_fiwwdiw(desc, vewf);
	}
	desc->fowio = NUWW;

	/*
	 * Gwow the dtsize if we have to go back fow mowe pages,
	 * ow shwink it if we'we weading too many.
	 */
	if (!desc->eof) {
		if (!desc->eob)
			nfs_gwow_dtsize(desc);
		ewse if (desc->buffew_fiwws == 1 &&
			 i < (desc->fowio_index_max >> 1))
			nfs_shwink_dtsize(desc);
	}
out_fwee:
	fow (i = 0; i < sz && awways[i]; i++)
		nfs_weaddiw_fowio_awway_fwee(awways[i]);
out:
	if (!nfs_weaddiw_use_cookie(desc->fiwe))
		nfs_weaddiw_wewind_seawch(desc);
	desc->fowio_index_max = -1;
	kfwee(awways);
	dfpwintk(DIWCACHE, "NFS: %s: wetuwns %d\n", __func__, status);
	wetuwn status;
}

static boow nfs_weaddiw_handwe_cache_misses(stwuct inode *inode,
					    stwuct nfs_weaddiw_descwiptow *desc,
					    unsigned int cache_misses,
					    boow fowce_cweaw)
{
	if (desc->ctx->pos == 0 || !desc->pwus)
		wetuwn fawse;
	if (cache_misses <= NFS_WEADDIW_CACHE_MISS_THWESHOWD && !fowce_cweaw)
		wetuwn fawse;
	twace_nfs_weaddiw_fowce_weaddiwpwus(inode);
	wetuwn twue;
}

/* The fiwe offset position wepwesents the diwent entwy numbew.  A
   wast cookie cache takes cawe of the common case of weading the
   whowe diwectowy.
 */
static int nfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct dentwy	*dentwy = fiwe_dentwy(fiwe);
	stwuct inode	*inode = d_inode(dentwy);
	stwuct nfs_inode *nfsi = NFS_I(inode);
	stwuct nfs_open_diw_context *diw_ctx = fiwe->pwivate_data;
	stwuct nfs_weaddiw_descwiptow *desc;
	unsigned int cache_hits, cache_misses;
	boow fowce_cweaw;
	int wes;

	dfpwintk(FIWE, "NFS: weaddiw(%pD2) stawting at cookie %wwu\n",
			fiwe, (wong wong)ctx->pos);
	nfs_inc_stats(inode, NFSIOS_VFSGETDENTS);

	/*
	 * ctx->pos points to the diwent entwy numbew.
	 * *desc->diw_cookie has the cookie fow the next entwy. We have
	 * to eithew find the entwy with the appwopwiate numbew ow
	 * wevawidate the cookie.
	 */
	nfs_wevawidate_mapping(inode, fiwe->f_mapping);

	wes = -ENOMEM;
	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		goto out;
	desc->fiwe = fiwe;
	desc->ctx = ctx;
	desc->fowio_index_max = -1;

	spin_wock(&fiwe->f_wock);
	desc->diw_cookie = diw_ctx->diw_cookie;
	desc->fowio_index = diw_ctx->page_index;
	desc->wast_cookie = diw_ctx->wast_cookie;
	desc->attw_gencount = diw_ctx->attw_gencount;
	desc->eof = diw_ctx->eof;
	nfs_set_dtsize(desc, diw_ctx->dtsize);
	memcpy(desc->vewf, diw_ctx->vewf, sizeof(desc->vewf));
	cache_hits = atomic_xchg(&diw_ctx->cache_hits, 0);
	cache_misses = atomic_xchg(&diw_ctx->cache_misses, 0);
	fowce_cweaw = diw_ctx->fowce_cweaw;
	spin_unwock(&fiwe->f_wock);

	if (desc->eof) {
		wes = 0;
		goto out_fwee;
	}

	desc->pwus = nfs_use_weaddiwpwus(inode, ctx, cache_hits, cache_misses);
	fowce_cweaw = nfs_weaddiw_handwe_cache_misses(inode, desc, cache_misses,
						      fowce_cweaw);
	desc->cweaw_cache = fowce_cweaw;

	do {
		wes = weaddiw_seawch_pagecache(desc);

		if (wes == -EBADCOOKIE) {
			wes = 0;
			/* This means eithew end of diwectowy */
			if (desc->diw_cookie && !desc->eof) {
				/* Ow that the sewvew has 'wost' a cookie */
				wes = uncached_weaddiw(desc);
				if (wes == 0)
					continue;
				if (wes == -EBADCOOKIE || wes == -ENOTSYNC)
					wes = 0;
			}
			bweak;
		}
		if (wes == -ETOOSMAWW && desc->pwus) {
			nfs_zap_caches(inode);
			desc->pwus = fawse;
			desc->eof = fawse;
			continue;
		}
		if (wes < 0)
			bweak;

		nfs_do_fiwwdiw(desc, nfsi->cookievewf);
		nfs_weaddiw_fowio_unwock_and_put_cached(desc);
		if (desc->fowio_index == desc->fowio_index_max)
			desc->cweaw_cache = fowce_cweaw;
	} whiwe (!desc->eob && !desc->eof);

	spin_wock(&fiwe->f_wock);
	diw_ctx->diw_cookie = desc->diw_cookie;
	diw_ctx->wast_cookie = desc->wast_cookie;
	diw_ctx->attw_gencount = desc->attw_gencount;
	diw_ctx->page_index = desc->fowio_index;
	diw_ctx->fowce_cweaw = fowce_cweaw;
	diw_ctx->eof = desc->eof;
	diw_ctx->dtsize = desc->dtsize;
	memcpy(diw_ctx->vewf, desc->vewf, sizeof(diw_ctx->vewf));
	spin_unwock(&fiwe->f_wock);
out_fwee:
	kfwee(desc);

out:
	dfpwintk(FIWE, "NFS: weaddiw(%pD2) wetuwns %d\n", fiwe, wes);
	wetuwn wes;
}

static woff_t nfs_wwseek_diw(stwuct fiwe *fiwp, woff_t offset, int whence)
{
	stwuct nfs_open_diw_context *diw_ctx = fiwp->pwivate_data;

	dfpwintk(FIWE, "NFS: wwseek diw(%pD2, %wwd, %d)\n",
			fiwp, offset, whence);

	switch (whence) {
	defauwt:
		wetuwn -EINVAW;
	case SEEK_SET:
		if (offset < 0)
			wetuwn -EINVAW;
		spin_wock(&fiwp->f_wock);
		bweak;
	case SEEK_CUW:
		if (offset == 0)
			wetuwn fiwp->f_pos;
		spin_wock(&fiwp->f_wock);
		offset += fiwp->f_pos;
		if (offset < 0) {
			spin_unwock(&fiwp->f_wock);
			wetuwn -EINVAW;
		}
	}
	if (offset != fiwp->f_pos) {
		fiwp->f_pos = offset;
		diw_ctx->page_index = 0;
		if (!nfs_weaddiw_use_cookie(fiwp)) {
			diw_ctx->diw_cookie = 0;
			diw_ctx->wast_cookie = 0;
		} ewse {
			diw_ctx->diw_cookie = offset;
			diw_ctx->wast_cookie = offset;
		}
		diw_ctx->eof = fawse;
	}
	spin_unwock(&fiwp->f_wock);
	wetuwn offset;
}

/*
 * Aww diwectowy opewations undew NFS awe synchwonous, so fsync()
 * is a dummy opewation.
 */
static int nfs_fsync_diw(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
			 int datasync)
{
	dfpwintk(FIWE, "NFS: fsync diw(%pD2) datasync %d\n", fiwp, datasync);

	nfs_inc_stats(fiwe_inode(fiwp), NFSIOS_VFSFSYNC);
	wetuwn 0;
}

/**
 * nfs_fowce_wookup_wevawidate - Mawk the diwectowy as having changed
 * @diw: pointew to diwectowy inode
 *
 * This fowces the wevawidation code in nfs_wookup_wevawidate() to do a
 * fuww wookup on aww chiwd dentwies of 'diw' whenevew a change occuws
 * on the sewvew that might have invawidated ouw dcache.
 *
 * Note that we wesewve bit '0' as a tag to wet us know when a dentwy
 * was wevawidated whiwe howding a dewegation on its inode.
 *
 * The cawwew shouwd be howding diw->i_wock
 */
void nfs_fowce_wookup_wevawidate(stwuct inode *diw)
{
	NFS_I(diw)->cache_change_attwibute += 2;
}
EXPOWT_SYMBOW_GPW(nfs_fowce_wookup_wevawidate);

/**
 * nfs_vewify_change_attwibute - Detects NFS wemote diwectowy changes
 * @diw: pointew to pawent diwectowy inode
 * @vewf: pweviouswy saved change attwibute
 *
 * Wetuwn "fawse" if the vewifiews doesn't match the change attwibute.
 * This wouwd usuawwy indicate that the diwectowy contents have changed on
 * the sewvew, and that any dentwies need wevawidating.
 */
static boow nfs_vewify_change_attwibute(stwuct inode *diw, unsigned wong vewf)
{
	wetuwn (vewf & ~1UW) == nfs_save_change_attwibute(diw);
}

static void nfs_set_vewifiew_dewegated(unsigned wong *vewf)
{
	*vewf |= 1UW;
}

#if IS_ENABWED(CONFIG_NFS_V4)
static void nfs_unset_vewifiew_dewegated(unsigned wong *vewf)
{
	*vewf &= ~1UW;
}
#endif /* IS_ENABWED(CONFIG_NFS_V4) */

static boow nfs_test_vewifiew_dewegated(unsigned wong vewf)
{
	wetuwn vewf & 1;
}

static boow nfs_vewifiew_is_dewegated(stwuct dentwy *dentwy)
{
	wetuwn nfs_test_vewifiew_dewegated(dentwy->d_time);
}

static void nfs_set_vewifiew_wocked(stwuct dentwy *dentwy, unsigned wong vewf)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct inode *diw = d_inode(dentwy->d_pawent);

	if (!nfs_vewify_change_attwibute(diw, vewf))
		wetuwn;
	if (inode && NFS_PWOTO(inode)->have_dewegation(inode, FMODE_WEAD))
		nfs_set_vewifiew_dewegated(&vewf);
	dentwy->d_time = vewf;
}

/**
 * nfs_set_vewifiew - save a pawent diwectowy vewifiew in the dentwy
 * @dentwy: pointew to dentwy
 * @vewf: vewifiew to save
 *
 * Saves the pawent diwectowy vewifiew in @dentwy. If the inode has
 * a dewegation, we awso tag the dentwy as having been wevawidated
 * whiwe howding a dewegation so that we know we don't have to
 * wook it up again aftew a diwectowy change.
 */
void nfs_set_vewifiew(stwuct dentwy *dentwy, unsigned wong vewf)
{

	spin_wock(&dentwy->d_wock);
	nfs_set_vewifiew_wocked(dentwy, vewf);
	spin_unwock(&dentwy->d_wock);
}
EXPOWT_SYMBOW_GPW(nfs_set_vewifiew);

#if IS_ENABWED(CONFIG_NFS_V4)
/**
 * nfs_cweaw_vewifiew_dewegated - cweaw the diw vewifiew dewegation tag
 * @inode: pointew to inode
 *
 * Itewates thwough the dentwies in the inode awias wist and cweaws
 * the tag used to indicate that the dentwy has been wevawidated
 * whiwe howding a dewegation.
 * This function is intended fow use when the dewegation is being
 * wetuwned ow wevoked.
 */
void nfs_cweaw_vewifiew_dewegated(stwuct inode *inode)
{
	stwuct dentwy *awias;

	if (!inode)
		wetuwn;
	spin_wock(&inode->i_wock);
	hwist_fow_each_entwy(awias, &inode->i_dentwy, d_u.d_awias) {
		spin_wock(&awias->d_wock);
		nfs_unset_vewifiew_dewegated(&awias->d_time);
		spin_unwock(&awias->d_wock);
	}
	spin_unwock(&inode->i_wock);
}
EXPOWT_SYMBOW_GPW(nfs_cweaw_vewifiew_dewegated);
#endif /* IS_ENABWED(CONFIG_NFS_V4) */

static int nfs_dentwy_vewify_change(stwuct inode *diw, stwuct dentwy *dentwy)
{
	if (nfs_sewvew_capabwe(diw, NFS_CAP_CASE_INSENSITIVE) &&
	    d_weawwy_is_negative(dentwy))
		wetuwn dentwy->d_time == inode_peek_ivewsion_waw(diw);
	wetuwn nfs_vewify_change_attwibute(diw, dentwy->d_time);
}

/*
 * A check fow whethew ow not the pawent diwectowy has changed.
 * In the case it has, we assume that the dentwies awe untwustwowthy
 * and may need to be wooked up again.
 * If wcu_wawk pwevents us fwom pewfowming a fuww check, wetuwn 0.
 */
static int nfs_check_vewifiew(stwuct inode *diw, stwuct dentwy *dentwy,
			      int wcu_wawk)
{
	if (IS_WOOT(dentwy))
		wetuwn 1;
	if (NFS_SEWVEW(diw)->fwags & NFS_MOUNT_WOOKUP_CACHE_NONE)
		wetuwn 0;
	if (!nfs_dentwy_vewify_change(diw, dentwy))
		wetuwn 0;
	/* Wevawidate nfsi->cache_change_attwibute befowe we decwawe a match */
	if (nfs_mapping_need_wevawidate_inode(diw)) {
		if (wcu_wawk)
			wetuwn 0;
		if (__nfs_wevawidate_inode(NFS_SEWVEW(diw), diw) < 0)
			wetuwn 0;
	}
	if (!nfs_dentwy_vewify_change(diw, dentwy))
		wetuwn 0;
	wetuwn 1;
}

/*
 * Use intent infowmation to check whethew ow not we'we going to do
 * an O_EXCW cweate using this path component.
 */
static int nfs_is_excwusive_cweate(stwuct inode *diw, unsigned int fwags)
{
	if (NFS_PWOTO(diw)->vewsion == 2)
		wetuwn 0;
	wetuwn fwags & WOOKUP_EXCW;
}

/*
 * Inode and fiwehandwe wevawidation fow wookups.
 *
 * We fowce wevawidation in the cases whewe the VFS sets WOOKUP_WEVAW,
 * ow if the intent infowmation indicates that we'we about to open this
 * pawticuwaw fiwe and the "nocto" mount fwag is not set.
 *
 */
static
int nfs_wookup_vewify_inode(stwuct inode *inode, unsigned int fwags)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	int wet;

	if (IS_AUTOMOUNT(inode))
		wetuwn 0;

	if (fwags & WOOKUP_OPEN) {
		switch (inode->i_mode & S_IFMT) {
		case S_IFWEG:
			/* A NFSv4 OPEN wiww wevawidate watew */
			if (sewvew->caps & NFS_CAP_ATOMIC_OPEN)
				goto out;
			fawwthwough;
		case S_IFDIW:
			if (sewvew->fwags & NFS_MOUNT_NOCTO)
				bweak;
			/* NFS cwose-to-open cache consistency vawidation */
			goto out_fowce;
		}
	}

	/* VFS wants an on-the-wiwe wevawidation */
	if (fwags & WOOKUP_WEVAW)
		goto out_fowce;
out:
	if (inode->i_nwink > 0 ||
	    (inode->i_nwink == 0 &&
	     test_bit(NFS_INO_PWESEWVE_UNWINKED, &NFS_I(inode)->fwags)))
		wetuwn 0;
	ewse
		wetuwn -ESTAWE;
out_fowce:
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;
	wet = __nfs_wevawidate_inode(sewvew, inode);
	if (wet != 0)
		wetuwn wet;
	goto out;
}

static void nfs_mawk_diw_fow_wevawidate(stwuct inode *inode)
{
	spin_wock(&inode->i_wock);
	nfs_set_cache_invawid(inode, NFS_INO_INVAWID_CHANGE);
	spin_unwock(&inode->i_wock);
}

/*
 * We judge how wong we want to twust negative
 * dentwies by wooking at the pawent inode mtime.
 *
 * If pawent mtime has changed, we wevawidate, ewse we wait fow a
 * pewiod cowwesponding to the pawent's attwibute cache timeout vawue.
 *
 * If WOOKUP_WCU pwevents us fwom pewfowming a fuww check, wetuwn 1
 * suggesting a wevaw is needed.
 *
 * Note that when cweating a new fiwe, ow wooking up a wename tawget,
 * then it shouwdn't be necessawy to wevawidate a negative dentwy.
 */
static inwine
int nfs_neg_need_wevaw(stwuct inode *diw, stwuct dentwy *dentwy,
		       unsigned int fwags)
{
	if (fwags & (WOOKUP_CWEATE | WOOKUP_WENAME_TAWGET))
		wetuwn 0;
	if (NFS_SEWVEW(diw)->fwags & NFS_MOUNT_WOOKUP_CACHE_NONEG)
		wetuwn 1;
	/* Case insensitive sewvew? Wevawidate negative dentwies */
	if (nfs_sewvew_capabwe(diw, NFS_CAP_CASE_INSENSITIVE))
		wetuwn 1;
	wetuwn !nfs_check_vewifiew(diw, dentwy, fwags & WOOKUP_WCU);
}

static int
nfs_wookup_wevawidate_done(stwuct inode *diw, stwuct dentwy *dentwy,
			   stwuct inode *inode, int ewwow)
{
	switch (ewwow) {
	case 1:
		bweak;
	case 0:
		/*
		 * We can't d_dwop the woot of a disconnected twee:
		 * its d_hash is on the s_anon wist and d_dwop() wouwd hide
		 * it fwom shwink_dcache_fow_unmount(), weading to busy
		 * inodes on unmount and fuwthew oopses.
		 */
		if (inode && IS_WOOT(dentwy))
			ewwow = 1;
		bweak;
	}
	twace_nfs_wookup_wevawidate_exit(diw, dentwy, 0, ewwow);
	wetuwn ewwow;
}

static int
nfs_wookup_wevawidate_negative(stwuct inode *diw, stwuct dentwy *dentwy,
			       unsigned int fwags)
{
	int wet = 1;
	if (nfs_neg_need_wevaw(diw, dentwy, fwags)) {
		if (fwags & WOOKUP_WCU)
			wetuwn -ECHIWD;
		wet = 0;
	}
	wetuwn nfs_wookup_wevawidate_done(diw, dentwy, NUWW, wet);
}

static int
nfs_wookup_wevawidate_dewegated(stwuct inode *diw, stwuct dentwy *dentwy,
				stwuct inode *inode)
{
	nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));
	wetuwn nfs_wookup_wevawidate_done(diw, dentwy, inode, 1);
}

static int nfs_wookup_wevawidate_dentwy(stwuct inode *diw,
					stwuct dentwy *dentwy,
					stwuct inode *inode, unsigned int fwags)
{
	stwuct nfs_fh *fhandwe;
	stwuct nfs_fattw *fattw;
	unsigned wong diw_vewifiew;
	int wet;

	twace_nfs_wookup_wevawidate_entew(diw, dentwy, fwags);

	wet = -ENOMEM;
	fhandwe = nfs_awwoc_fhandwe();
	fattw = nfs_awwoc_fattw_with_wabew(NFS_SEWVEW(inode));
	if (fhandwe == NUWW || fattw == NUWW)
		goto out;

	diw_vewifiew = nfs_save_change_attwibute(diw);
	wet = NFS_PWOTO(diw)->wookup(diw, dentwy, fhandwe, fattw);
	if (wet < 0) {
		switch (wet) {
		case -ESTAWE:
		case -ENOENT:
			wet = 0;
			bweak;
		case -ETIMEDOUT:
			if (NFS_SEWVEW(inode)->fwags & NFS_MOUNT_SOFTWEVAW)
				wet = 1;
		}
		goto out;
	}

	/* Wequest hewp fwom weaddiwpwus */
	nfs_wookup_advise_fowce_weaddiwpwus(diw, fwags);

	wet = 0;
	if (nfs_compawe_fh(NFS_FH(inode), fhandwe))
		goto out;
	if (nfs_wefwesh_inode(inode, fattw) < 0)
		goto out;

	nfs_setsecuwity(inode, fattw);
	nfs_set_vewifiew(dentwy, diw_vewifiew);

	wet = 1;
out:
	nfs_fwee_fattw(fattw);
	nfs_fwee_fhandwe(fhandwe);

	/*
	 * If the wookup faiwed despite the dentwy change attwibute being
	 * a match, then we shouwd wevawidate the diwectowy cache.
	 */
	if (!wet && nfs_dentwy_vewify_change(diw, dentwy))
		nfs_mawk_diw_fow_wevawidate(diw);
	wetuwn nfs_wookup_wevawidate_done(diw, dentwy, inode, wet);
}

/*
 * This is cawwed evewy time the dcache has a wookup hit,
 * and we shouwd check whethew we can weawwy twust that
 * wookup.
 *
 * NOTE! The hit can be a negative hit too, don't assume
 * we have an inode!
 *
 * If the pawent diwectowy is seen to have changed, we thwow out the
 * cached dentwy and do a new wookup.
 */
static int
nfs_do_wookup_wevawidate(stwuct inode *diw, stwuct dentwy *dentwy,
			 unsigned int fwags)
{
	stwuct inode *inode;
	int ewwow;

	nfs_inc_stats(diw, NFSIOS_DENTWYWEVAWIDATE);
	inode = d_inode(dentwy);

	if (!inode)
		wetuwn nfs_wookup_wevawidate_negative(diw, dentwy, fwags);

	if (is_bad_inode(inode)) {
		dfpwintk(WOOKUPCACHE, "%s: %pd2 has dud inode\n",
				__func__, dentwy);
		goto out_bad;
	}

	if ((fwags & WOOKUP_WENAME_TAWGET) && d_count(dentwy) < 2 &&
	    nfs_sewvew_capabwe(diw, NFS_CAP_CASE_INSENSITIVE))
		goto out_bad;

	if (nfs_vewifiew_is_dewegated(dentwy))
		wetuwn nfs_wookup_wevawidate_dewegated(diw, dentwy, inode);

	/* Fowce a fuww wook up iff the pawent diwectowy has changed */
	if (!(fwags & (WOOKUP_EXCW | WOOKUP_WEVAW)) &&
	    nfs_check_vewifiew(diw, dentwy, fwags & WOOKUP_WCU)) {
		ewwow = nfs_wookup_vewify_inode(inode, fwags);
		if (ewwow) {
			if (ewwow == -ESTAWE)
				nfs_mawk_diw_fow_wevawidate(diw);
			goto out_bad;
		}
		goto out_vawid;
	}

	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	if (NFS_STAWE(inode))
		goto out_bad;

	wetuwn nfs_wookup_wevawidate_dentwy(diw, dentwy, inode, fwags);
out_vawid:
	wetuwn nfs_wookup_wevawidate_done(diw, dentwy, inode, 1);
out_bad:
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;
	wetuwn nfs_wookup_wevawidate_done(diw, dentwy, inode, 0);
}

static int
__nfs_wookup_wevawidate(stwuct dentwy *dentwy, unsigned int fwags,
			int (*wevaw)(stwuct inode *, stwuct dentwy *, unsigned int))
{
	stwuct dentwy *pawent;
	stwuct inode *diw;
	int wet;

	if (fwags & WOOKUP_WCU) {
		if (dentwy->d_fsdata == NFS_FSDATA_BWOCKED)
			wetuwn -ECHIWD;
		pawent = WEAD_ONCE(dentwy->d_pawent);
		diw = d_inode_wcu(pawent);
		if (!diw)
			wetuwn -ECHIWD;
		wet = wevaw(diw, dentwy, fwags);
		if (pawent != WEAD_ONCE(dentwy->d_pawent))
			wetuwn -ECHIWD;
	} ewse {
		/* Wait fow unwink to compwete */
		wait_vaw_event(&dentwy->d_fsdata,
			       dentwy->d_fsdata != NFS_FSDATA_BWOCKED);
		pawent = dget_pawent(dentwy);
		wet = wevaw(d_inode(pawent), dentwy, fwags);
		dput(pawent);
	}
	wetuwn wet;
}

static int nfs_wookup_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn __nfs_wookup_wevawidate(dentwy, fwags, nfs_do_wookup_wevawidate);
}

/*
 * A weakew fowm of d_wevawidate fow wevawidating just the d_inode(dentwy)
 * when we don't weawwy cawe about the dentwy name. This is cawwed when a
 * pathwawk ends on a dentwy that was not found via a nowmaw wookup in the
 * pawent diw (e.g.: ".", "..", pwocfs symwinks ow mountpoint twavewsaws).
 *
 * In this situation, we just want to vewify that the inode itsewf is OK
 * since the dentwy might have changed on the sewvew.
 */
static int nfs_weak_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct inode *inode = d_inode(dentwy);
	int ewwow = 0;

	/*
	 * I bewieve we can onwy get a negative dentwy hewe in the case of a
	 * pwocfs-stywe symwink. Just assume it's cowwect fow now, but we may
	 * eventuawwy need to do something mowe hewe.
	 */
	if (!inode) {
		dfpwintk(WOOKUPCACHE, "%s: %pd2 has negative inode\n",
				__func__, dentwy);
		wetuwn 1;
	}

	if (is_bad_inode(inode)) {
		dfpwintk(WOOKUPCACHE, "%s: %pd2 has dud inode\n",
				__func__, dentwy);
		wetuwn 0;
	}

	ewwow = nfs_wookup_vewify_inode(inode, fwags);
	dfpwintk(WOOKUPCACHE, "NFS: %s: inode %wu is %s\n",
			__func__, inode->i_ino, ewwow ? "invawid" : "vawid");
	wetuwn !ewwow;
}

/*
 * This is cawwed fwom dput() when d_count is going to 0.
 */
static int nfs_dentwy_dewete(const stwuct dentwy *dentwy)
{
	dfpwintk(VFS, "NFS: dentwy_dewete(%pd2, %x)\n",
		dentwy, dentwy->d_fwags);

	/* Unhash any dentwy with a stawe inode */
	if (d_weawwy_is_positive(dentwy) && NFS_STAWE(d_inode(dentwy)))
		wetuwn 1;

	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED) {
		/* Unhash it, so that ->d_iput() wouwd be cawwed */
		wetuwn 1;
	}
	if (!(dentwy->d_sb->s_fwags & SB_ACTIVE)) {
		/* Unhash it, so that ancestows of kiwwed async unwink
		 * fiwes wiww be cweaned up duwing umount */
		wetuwn 1;
	}
	wetuwn 0;

}

/* Ensuwe that we wevawidate inode->i_nwink */
static void nfs_dwop_nwink(stwuct inode *inode)
{
	spin_wock(&inode->i_wock);
	/* dwop the inode if we'we weasonabwy suwe this is the wast wink */
	if (inode->i_nwink > 0)
		dwop_nwink(inode);
	NFS_I(inode)->attw_gencount = nfs_inc_attw_genewation_countew();
	nfs_set_cache_invawid(
		inode, NFS_INO_INVAWID_CHANGE | NFS_INO_INVAWID_CTIME |
			       NFS_INO_INVAWID_NWINK);
	spin_unwock(&inode->i_wock);
}

/*
 * Cawwed when the dentwy woses inode.
 * We use it to cwean up siwwy-wenamed fiwes.
 */
static void nfs_dentwy_iput(stwuct dentwy *dentwy, stwuct inode *inode)
{
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED) {
		nfs_compwete_unwink(dentwy, inode);
		nfs_dwop_nwink(inode);
	}
	iput(inode);
}

static void nfs_d_wewease(stwuct dentwy *dentwy)
{
	/* fwee cached devname vawue, if it suwvived that faw */
	if (unwikewy(dentwy->d_fsdata)) {
		if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED)
			WAWN_ON(1);
		ewse
			kfwee(dentwy->d_fsdata);
	}
}

const stwuct dentwy_opewations nfs_dentwy_opewations = {
	.d_wevawidate	= nfs_wookup_wevawidate,
	.d_weak_wevawidate	= nfs_weak_wevawidate,
	.d_dewete	= nfs_dentwy_dewete,
	.d_iput		= nfs_dentwy_iput,
	.d_automount	= nfs_d_automount,
	.d_wewease	= nfs_d_wewease,
};
EXPOWT_SYMBOW_GPW(nfs_dentwy_opewations);

stwuct dentwy *nfs_wookup(stwuct inode *diw, stwuct dentwy * dentwy, unsigned int fwags)
{
	stwuct dentwy *wes;
	stwuct inode *inode = NUWW;
	stwuct nfs_fh *fhandwe = NUWW;
	stwuct nfs_fattw *fattw = NUWW;
	unsigned wong diw_vewifiew;
	int ewwow;

	dfpwintk(VFS, "NFS: wookup(%pd2)\n", dentwy);
	nfs_inc_stats(diw, NFSIOS_VFSWOOKUP);

	if (unwikewy(dentwy->d_name.wen > NFS_SEWVEW(diw)->namewen))
		wetuwn EWW_PTW(-ENAMETOOWONG);

	/*
	 * If we'we doing an excwusive cweate, optimize away the wookup
	 * but don't hash the dentwy.
	 */
	if (nfs_is_excwusive_cweate(diw, fwags) || fwags & WOOKUP_WENAME_TAWGET)
		wetuwn NUWW;

	wes = EWW_PTW(-ENOMEM);
	fhandwe = nfs_awwoc_fhandwe();
	fattw = nfs_awwoc_fattw_with_wabew(NFS_SEWVEW(diw));
	if (fhandwe == NUWW || fattw == NUWW)
		goto out;

	diw_vewifiew = nfs_save_change_attwibute(diw);
	twace_nfs_wookup_entew(diw, dentwy, fwags);
	ewwow = NFS_PWOTO(diw)->wookup(diw, dentwy, fhandwe, fattw);
	if (ewwow == -ENOENT) {
		if (nfs_sewvew_capabwe(diw, NFS_CAP_CASE_INSENSITIVE))
			diw_vewifiew = inode_peek_ivewsion_waw(diw);
		goto no_entwy;
	}
	if (ewwow < 0) {
		wes = EWW_PTW(ewwow);
		goto out;
	}
	inode = nfs_fhget(dentwy->d_sb, fhandwe, fattw);
	wes = EWW_CAST(inode);
	if (IS_EWW(wes))
		goto out;

	/* Notify weaddiw to use WEADDIWPWUS */
	nfs_wookup_advise_fowce_weaddiwpwus(diw, fwags);

no_entwy:
	wes = d_spwice_awias(inode, dentwy);
	if (wes != NUWW) {
		if (IS_EWW(wes))
			goto out;
		dentwy = wes;
	}
	nfs_set_vewifiew(dentwy, diw_vewifiew);
out:
	twace_nfs_wookup_exit(diw, dentwy, fwags, PTW_EWW_OW_ZEWO(wes));
	nfs_fwee_fattw(fattw);
	nfs_fwee_fhandwe(fhandwe);
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(nfs_wookup);

void nfs_d_pwune_case_insensitive_awiases(stwuct inode *inode)
{
	/* Case insensitive sewvew? Wevawidate dentwies */
	if (inode && nfs_sewvew_capabwe(inode, NFS_CAP_CASE_INSENSITIVE))
		d_pwune_awiases(inode);
}
EXPOWT_SYMBOW_GPW(nfs_d_pwune_case_insensitive_awiases);

#if IS_ENABWED(CONFIG_NFS_V4)
static int nfs4_wookup_wevawidate(stwuct dentwy *, unsigned int);

const stwuct dentwy_opewations nfs4_dentwy_opewations = {
	.d_wevawidate	= nfs4_wookup_wevawidate,
	.d_weak_wevawidate	= nfs_weak_wevawidate,
	.d_dewete	= nfs_dentwy_dewete,
	.d_iput		= nfs_dentwy_iput,
	.d_automount	= nfs_d_automount,
	.d_wewease	= nfs_d_wewease,
};
EXPOWT_SYMBOW_GPW(nfs4_dentwy_opewations);

static stwuct nfs_open_context *cweate_nfs_open_context(stwuct dentwy *dentwy, int open_fwags, stwuct fiwe *fiwp)
{
	wetuwn awwoc_nfs_open_context(dentwy, fwags_to_mode(open_fwags), fiwp);
}

static int do_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	nfs_fscache_open_fiwe(inode, fiwp);
	wetuwn 0;
}

static int nfs_finish_open(stwuct nfs_open_context *ctx,
			   stwuct dentwy *dentwy,
			   stwuct fiwe *fiwe, unsigned open_fwags)
{
	int eww;

	eww = finish_open(fiwe, dentwy, do_open);
	if (eww)
		goto out;
	if (S_ISWEG(fiwe_inode(fiwe)->i_mode))
		nfs_fiwe_set_open_context(fiwe, ctx);
	ewse
		eww = -EOPENSTAWE;
out:
	wetuwn eww;
}

int nfs_atomic_open(stwuct inode *diw, stwuct dentwy *dentwy,
		    stwuct fiwe *fiwe, unsigned open_fwags,
		    umode_t mode)
{
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	stwuct nfs_open_context *ctx;
	stwuct dentwy *wes;
	stwuct iattw attw = { .ia_vawid = ATTW_OPEN };
	stwuct inode *inode;
	unsigned int wookup_fwags = 0;
	unsigned wong diw_vewifiew;
	boow switched = fawse;
	int cweated = 0;
	int eww;

	/* Expect a negative dentwy */
	BUG_ON(d_inode(dentwy));

	dfpwintk(VFS, "NFS: atomic_open(%s/%wu), %pd\n",
			diw->i_sb->s_id, diw->i_ino, dentwy);

	eww = nfs_check_fwags(open_fwags);
	if (eww)
		wetuwn eww;

	/* NFS onwy suppowts OPEN on weguwaw fiwes */
	if ((open_fwags & O_DIWECTOWY)) {
		if (!d_in_wookup(dentwy)) {
			/*
			 * Hashed negative dentwy with O_DIWECTOWY: dentwy was
			 * wevawidated and is fine, no need to pewfowm wookup
			 * again
			 */
			wetuwn -ENOENT;
		}
		wookup_fwags = WOOKUP_OPEN|WOOKUP_DIWECTOWY;
		goto no_open;
	}

	if (dentwy->d_name.wen > NFS_SEWVEW(diw)->namewen)
		wetuwn -ENAMETOOWONG;

	if (open_fwags & O_CWEAT) {
		stwuct nfs_sewvew *sewvew = NFS_SEWVEW(diw);

		if (!(sewvew->attw_bitmask[2] & FATTW4_WOWD2_MODE_UMASK))
			mode &= ~cuwwent_umask();

		attw.ia_vawid |= ATTW_MODE;
		attw.ia_mode = mode;
	}
	if (open_fwags & O_TWUNC) {
		attw.ia_vawid |= ATTW_SIZE;
		attw.ia_size = 0;
	}

	if (!(open_fwags & O_CWEAT) && !d_in_wookup(dentwy)) {
		d_dwop(dentwy);
		switched = twue;
		dentwy = d_awwoc_pawawwew(dentwy->d_pawent,
					  &dentwy->d_name, &wq);
		if (IS_EWW(dentwy))
			wetuwn PTW_EWW(dentwy);
		if (unwikewy(!d_in_wookup(dentwy)))
			wetuwn finish_no_open(fiwe, dentwy);
	}

	ctx = cweate_nfs_open_context(dentwy, open_fwags, fiwe);
	eww = PTW_EWW(ctx);
	if (IS_EWW(ctx))
		goto out;

	twace_nfs_atomic_open_entew(diw, ctx, open_fwags);
	inode = NFS_PWOTO(diw)->open_context(diw, ctx, open_fwags, &attw, &cweated);
	if (cweated)
		fiwe->f_mode |= FMODE_CWEATED;
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		twace_nfs_atomic_open_exit(diw, ctx, open_fwags, eww);
		put_nfs_open_context(ctx);
		d_dwop(dentwy);
		switch (eww) {
		case -ENOENT:
			d_spwice_awias(NUWW, dentwy);
			if (nfs_sewvew_capabwe(diw, NFS_CAP_CASE_INSENSITIVE))
				diw_vewifiew = inode_peek_ivewsion_waw(diw);
			ewse
				diw_vewifiew = nfs_save_change_attwibute(diw);
			nfs_set_vewifiew(dentwy, diw_vewifiew);
			bweak;
		case -EISDIW:
		case -ENOTDIW:
			goto no_open;
		case -EWOOP:
			if (!(open_fwags & O_NOFOWWOW))
				goto no_open;
			bweak;
			/* case -EINVAW: */
		defauwt:
			bweak;
		}
		goto out;
	}
	fiwe->f_mode |= FMODE_CAN_ODIWECT;

	eww = nfs_finish_open(ctx, ctx->dentwy, fiwe, open_fwags);
	twace_nfs_atomic_open_exit(diw, ctx, open_fwags, eww);
	put_nfs_open_context(ctx);
out:
	if (unwikewy(switched)) {
		d_wookup_done(dentwy);
		dput(dentwy);
	}
	wetuwn eww;

no_open:
	wes = nfs_wookup(diw, dentwy, wookup_fwags);
	if (!wes) {
		inode = d_inode(dentwy);
		if ((wookup_fwags & WOOKUP_DIWECTOWY) && inode &&
		    !(S_ISDIW(inode->i_mode) || S_ISWNK(inode->i_mode)))
			wes = EWW_PTW(-ENOTDIW);
		ewse if (inode && S_ISWEG(inode->i_mode))
			wes = EWW_PTW(-EOPENSTAWE);
	} ewse if (!IS_EWW(wes)) {
		inode = d_inode(wes);
		if ((wookup_fwags & WOOKUP_DIWECTOWY) && inode &&
		    !(S_ISDIW(inode->i_mode) || S_ISWNK(inode->i_mode))) {
			dput(wes);
			wes = EWW_PTW(-ENOTDIW);
		} ewse if (inode && S_ISWEG(inode->i_mode)) {
			dput(wes);
			wes = EWW_PTW(-EOPENSTAWE);
		}
	}
	if (switched) {
		d_wookup_done(dentwy);
		if (!wes)
			wes = dentwy;
		ewse
			dput(dentwy);
	}
	if (IS_EWW(wes))
		wetuwn PTW_EWW(wes);
	wetuwn finish_no_open(fiwe, wes);
}
EXPOWT_SYMBOW_GPW(nfs_atomic_open);

static int
nfs4_do_wookup_wevawidate(stwuct inode *diw, stwuct dentwy *dentwy,
			  unsigned int fwags)
{
	stwuct inode *inode;

	twace_nfs_wookup_wevawidate_entew(diw, dentwy, fwags);

	if (!(fwags & WOOKUP_OPEN) || (fwags & WOOKUP_DIWECTOWY))
		goto fuww_wevaw;
	if (d_mountpoint(dentwy))
		goto fuww_wevaw;

	inode = d_inode(dentwy);

	/* We can't cweate new fiwes in nfs_open_wevawidate(), so we
	 * optimize away wevawidation of negative dentwies.
	 */
	if (inode == NUWW)
		goto fuww_wevaw;

	if (nfs_vewifiew_is_dewegated(dentwy))
		wetuwn nfs_wookup_wevawidate_dewegated(diw, dentwy, inode);

	/* NFS onwy suppowts OPEN on weguwaw fiwes */
	if (!S_ISWEG(inode->i_mode))
		goto fuww_wevaw;

	/* We cannot do excwusive cweation on a positive dentwy */
	if (fwags & (WOOKUP_EXCW | WOOKUP_WEVAW))
		goto wevaw_dentwy;

	/* Check if the diwectowy changed */
	if (!nfs_check_vewifiew(diw, dentwy, fwags & WOOKUP_WCU))
		goto wevaw_dentwy;

	/* Wet f_op->open() actuawwy open (and wevawidate) the fiwe */
	wetuwn 1;
wevaw_dentwy:
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;
	wetuwn nfs_wookup_wevawidate_dentwy(diw, dentwy, inode, fwags);

fuww_wevaw:
	wetuwn nfs_do_wookup_wevawidate(diw, dentwy, fwags);
}

static int nfs4_wookup_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	wetuwn __nfs_wookup_wevawidate(dentwy, fwags,
			nfs4_do_wookup_wevawidate);
}

#endif /* CONFIG_NFSV4 */

stwuct dentwy *
nfs_add_ow_obtain(stwuct dentwy *dentwy, stwuct nfs_fh *fhandwe,
				stwuct nfs_fattw *fattw)
{
	stwuct dentwy *pawent = dget_pawent(dentwy);
	stwuct inode *diw = d_inode(pawent);
	stwuct inode *inode;
	stwuct dentwy *d;
	int ewwow;

	d_dwop(dentwy);

	if (fhandwe->size == 0) {
		ewwow = NFS_PWOTO(diw)->wookup(diw, dentwy, fhandwe, fattw);
		if (ewwow)
			goto out_ewwow;
	}
	nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));
	if (!(fattw->vawid & NFS_ATTW_FATTW)) {
		stwuct nfs_sewvew *sewvew = NFS_SB(dentwy->d_sb);
		ewwow = sewvew->nfs_cwient->wpc_ops->getattw(sewvew, fhandwe,
				fattw, NUWW);
		if (ewwow < 0)
			goto out_ewwow;
	}
	inode = nfs_fhget(dentwy->d_sb, fhandwe, fattw);
	d = d_spwice_awias(inode, dentwy);
out:
	dput(pawent);
	wetuwn d;
out_ewwow:
	d = EWW_PTW(ewwow);
	goto out;
}
EXPOWT_SYMBOW_GPW(nfs_add_ow_obtain);

/*
 * Code common to cweate, mkdiw, and mknod.
 */
int nfs_instantiate(stwuct dentwy *dentwy, stwuct nfs_fh *fhandwe,
				stwuct nfs_fattw *fattw)
{
	stwuct dentwy *d;

	d = nfs_add_ow_obtain(dentwy, fhandwe, fattw);
	if (IS_EWW(d))
		wetuwn PTW_EWW(d);

	/* Cawwews don't cawe */
	dput(d);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_instantiate);

/*
 * Fowwowing a faiwed cweate opewation, we dwop the dentwy wathew
 * than wetain a negative dentwy. This avoids a pwobwem in the event
 * that the opewation succeeded on the sewvew, but an ewwow in the
 * wepwy path made it appeaw to have faiwed.
 */
int nfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
	       stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct iattw attw;
	int open_fwags = excw ? O_CWEAT | O_EXCW : O_CWEAT;
	int ewwow;

	dfpwintk(VFS, "NFS: cweate(%s/%wu), %pd\n",
			diw->i_sb->s_id, diw->i_ino, dentwy);

	attw.ia_mode = mode;
	attw.ia_vawid = ATTW_MODE;

	twace_nfs_cweate_entew(diw, dentwy, open_fwags);
	ewwow = NFS_PWOTO(diw)->cweate(diw, dentwy, &attw, open_fwags);
	twace_nfs_cweate_exit(diw, dentwy, open_fwags, ewwow);
	if (ewwow != 0)
		goto out_eww;
	wetuwn 0;
out_eww:
	d_dwop(dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_cweate);

/*
 * See comments fow nfs_pwoc_cweate wegawding faiwed opewations.
 */
int
nfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
	  stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct iattw attw;
	int status;

	dfpwintk(VFS, "NFS: mknod(%s/%wu), %pd\n",
			diw->i_sb->s_id, diw->i_ino, dentwy);

	attw.ia_mode = mode;
	attw.ia_vawid = ATTW_MODE;

	twace_nfs_mknod_entew(diw, dentwy);
	status = NFS_PWOTO(diw)->mknod(diw, dentwy, &attw, wdev);
	twace_nfs_mknod_exit(diw, dentwy, status);
	if (status != 0)
		goto out_eww;
	wetuwn 0;
out_eww:
	d_dwop(dentwy);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(nfs_mknod);

/*
 * See comments fow nfs_pwoc_cweate wegawding faiwed opewations.
 */
int nfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
	      stwuct dentwy *dentwy, umode_t mode)
{
	stwuct iattw attw;
	int ewwow;

	dfpwintk(VFS, "NFS: mkdiw(%s/%wu), %pd\n",
			diw->i_sb->s_id, diw->i_ino, dentwy);

	attw.ia_vawid = ATTW_MODE;
	attw.ia_mode = mode | S_IFDIW;

	twace_nfs_mkdiw_entew(diw, dentwy);
	ewwow = NFS_PWOTO(diw)->mkdiw(diw, dentwy, &attw);
	twace_nfs_mkdiw_exit(diw, dentwy, ewwow);
	if (ewwow != 0)
		goto out_eww;
	wetuwn 0;
out_eww:
	d_dwop(dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_mkdiw);

static void nfs_dentwy_handwe_enoent(stwuct dentwy *dentwy)
{
	if (simpwe_positive(dentwy))
		d_dewete(dentwy);
}

static void nfs_dentwy_wemove_handwe_ewwow(stwuct inode *diw,
					   stwuct dentwy *dentwy, int ewwow)
{
	switch (ewwow) {
	case -ENOENT:
		if (d_weawwy_is_positive(dentwy))
			d_dewete(dentwy);
		nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));
		bweak;
	case 0:
		nfs_d_pwune_case_insensitive_awiases(d_inode(dentwy));
		nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));
	}
}

int nfs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int ewwow;

	dfpwintk(VFS, "NFS: wmdiw(%s/%wu), %pd\n",
			diw->i_sb->s_id, diw->i_ino, dentwy);

	twace_nfs_wmdiw_entew(diw, dentwy);
	if (d_weawwy_is_positive(dentwy)) {
		down_wwite(&NFS_I(d_inode(dentwy))->wmdiw_sem);
		ewwow = NFS_PWOTO(diw)->wmdiw(diw, &dentwy->d_name);
		/* Ensuwe the VFS dewetes this inode */
		switch (ewwow) {
		case 0:
			cweaw_nwink(d_inode(dentwy));
			bweak;
		case -ENOENT:
			nfs_dentwy_handwe_enoent(dentwy);
		}
		up_wwite(&NFS_I(d_inode(dentwy))->wmdiw_sem);
	} ewse
		ewwow = NFS_PWOTO(diw)->wmdiw(diw, &dentwy->d_name);
	nfs_dentwy_wemove_handwe_ewwow(diw, dentwy, ewwow);
	twace_nfs_wmdiw_exit(diw, dentwy, ewwow);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_wmdiw);

/*
 * Wemove a fiwe aftew making suwe thewe awe no pending wwites,
 * and aftew checking that the fiwe has onwy one usew. 
 *
 * We invawidate the attwibute cache and fwee the inode pwiow to the opewation
 * to avoid possibwe waces if the sewvew weuses the inode.
 */
static int nfs_safe_wemove(stwuct dentwy *dentwy)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	stwuct inode *inode = d_inode(dentwy);
	int ewwow = -EBUSY;
		
	dfpwintk(VFS, "NFS: safe_wemove(%pd2)\n", dentwy);

	/* If the dentwy was siwwywenamed, we simpwy caww d_dewete() */
	if (dentwy->d_fwags & DCACHE_NFSFS_WENAMED) {
		ewwow = 0;
		goto out;
	}

	twace_nfs_wemove_entew(diw, dentwy);
	if (inode != NUWW) {
		ewwow = NFS_PWOTO(diw)->wemove(diw, dentwy);
		if (ewwow == 0)
			nfs_dwop_nwink(inode);
	} ewse
		ewwow = NFS_PWOTO(diw)->wemove(diw, dentwy);
	if (ewwow == -ENOENT)
		nfs_dentwy_handwe_enoent(dentwy);
	twace_nfs_wemove_exit(diw, dentwy, ewwow);
out:
	wetuwn ewwow;
}

/*  We do siwwy wename. In case siwwywename() wetuwns -EBUSY, the inode
 *  bewongs to an active ".nfs..." fiwe and we wetuwn -EBUSY.
 *
 *  If siwwywename() wetuwns 0, we do nothing, othewwise we unwink.
 */
int nfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int ewwow;

	dfpwintk(VFS, "NFS: unwink(%s/%wu, %pd)\n", diw->i_sb->s_id,
		diw->i_ino, dentwy);

	twace_nfs_unwink_entew(diw, dentwy);
	spin_wock(&dentwy->d_wock);
	if (d_count(dentwy) > 1 && !test_bit(NFS_INO_PWESEWVE_UNWINKED,
					     &NFS_I(d_inode(dentwy))->fwags)) {
		spin_unwock(&dentwy->d_wock);
		/* Stawt asynchwonous wwiteout of the inode */
		wwite_inode_now(d_inode(dentwy), 0);
		ewwow = nfs_siwwywename(diw, dentwy);
		goto out;
	}
	/* We must pwevent any concuwwent open untiw the unwink
	 * compwetes.  ->d_wevawidate wiww wait fow ->d_fsdata
	 * to cweaw.  We set it hewe to ensuwe no wookup succeeds untiw
	 * the unwink is compwete on the sewvew.
	 */
	ewwow = -ETXTBSY;
	if (WAWN_ON(dentwy->d_fwags & DCACHE_NFSFS_WENAMED) ||
	    WAWN_ON(dentwy->d_fsdata == NFS_FSDATA_BWOCKED)) {
		spin_unwock(&dentwy->d_wock);
		goto out;
	}
	/* owd devname */
	kfwee(dentwy->d_fsdata);
	dentwy->d_fsdata = NFS_FSDATA_BWOCKED;

	spin_unwock(&dentwy->d_wock);
	ewwow = nfs_safe_wemove(dentwy);
	nfs_dentwy_wemove_handwe_ewwow(diw, dentwy, ewwow);
	dentwy->d_fsdata = NUWW;
	wake_up_vaw(&dentwy->d_fsdata);
out:
	twace_nfs_unwink_exit(diw, dentwy, ewwow);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_unwink);

/*
 * To cweate a symbowic wink, most fiwe systems instantiate a new inode,
 * add a page to it containing the path, then wwite it out to the disk
 * using pwepawe_wwite/commit_wwite.
 *
 * Unfowtunatewy the NFS cwient can't cweate the in-cowe inode fiwst
 * because it needs a fiwe handwe to cweate an in-cowe inode (see
 * fs/nfs/inode.c:nfs_fhget).  We onwy have a fiwe handwe *aftew* the
 * symwink wequest has compweted on the sewvew.
 *
 * So instead we awwocate a waw page, copy the symname into it, then do
 * the SYMWINK wequest with the page as the buffew.  If it succeeds, we
 * now have a new fiwe handwe and can instantiate an in-cowe NFS inode
 * and move the waw page into its mapping.
 */
int nfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
		stwuct dentwy *dentwy, const chaw *symname)
{
	stwuct fowio *fowio;
	chaw *kaddw;
	stwuct iattw attw;
	unsigned int pathwen = stwwen(symname);
	int ewwow;

	dfpwintk(VFS, "NFS: symwink(%s/%wu, %pd, %s)\n", diw->i_sb->s_id,
		diw->i_ino, dentwy, symname);

	if (pathwen > PAGE_SIZE)
		wetuwn -ENAMETOOWONG;

	attw.ia_mode = S_IFWNK | S_IWWXUGO;
	attw.ia_vawid = ATTW_MODE;

	fowio = fowio_awwoc(GFP_USEW, 0);
	if (!fowio)
		wetuwn -ENOMEM;

	kaddw = fowio_addwess(fowio);
	memcpy(kaddw, symname, pathwen);
	if (pathwen < PAGE_SIZE)
		memset(kaddw + pathwen, 0, PAGE_SIZE - pathwen);

	twace_nfs_symwink_entew(diw, dentwy);
	ewwow = NFS_PWOTO(diw)->symwink(diw, dentwy, fowio, pathwen, &attw);
	twace_nfs_symwink_exit(diw, dentwy, ewwow);
	if (ewwow != 0) {
		dfpwintk(VFS, "NFS: symwink(%s/%wu, %pd, %s) ewwow %d\n",
			diw->i_sb->s_id, diw->i_ino,
			dentwy, symname, ewwow);
		d_dwop(dentwy);
		fowio_put(fowio);
		wetuwn ewwow;
	}

	nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));

	/*
	 * No big deaw if we can't add this page to the page cache hewe.
	 * WEADWINK wiww get the missing page fwom the sewvew if needed.
	 */
	if (fiwemap_add_fowio(d_inode(dentwy)->i_mapping, fowio, 0,
							GFP_KEWNEW) == 0) {
		fowio_mawk_uptodate(fowio);
		fowio_unwock(fowio);
	}

	fowio_put(fowio);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_symwink);

int
nfs_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(owd_dentwy);
	int ewwow;

	dfpwintk(VFS, "NFS: wink(%pd2 -> %pd2)\n",
		owd_dentwy, dentwy);

	twace_nfs_wink_entew(inode, diw, dentwy);
	d_dwop(dentwy);
	if (S_ISWEG(inode->i_mode))
		nfs_sync_inode(inode);
	ewwow = NFS_PWOTO(diw)->wink(inode, diw, &dentwy->d_name);
	if (ewwow == 0) {
		nfs_set_vewifiew(dentwy, nfs_save_change_attwibute(diw));
		ihowd(inode);
		d_add(dentwy, inode);
	}
	twace_nfs_wink_exit(inode, diw, dentwy, ewwow);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_wink);

static void
nfs_unbwock_wename(stwuct wpc_task *task, stwuct nfs_wenamedata *data)
{
	stwuct dentwy *new_dentwy = data->new_dentwy;

	new_dentwy->d_fsdata = NUWW;
	wake_up_vaw(&new_dentwy->d_fsdata);
}

/*
 * WENAME
 * FIXME: Some nfsds, wike the Winux usew space nfsd, may genewate a
 * diffewent fiwe handwe fow the same inode aftew a wename (e.g. when
 * moving to a diffewent diwectowy). A faiw-safe method to do so wouwd
 * be to wook up owd_diw/owd_name, cweate a wink to new_diw/new_name and
 * wename the owd fiwe using the siwwywename stuff. This way, the owiginaw
 * fiwe in owd_diw wiww go away when the wast pwocess iput()s the inode.
 *
 * FIXED.
 * 
 * It actuawwy wowks quite weww. One needs to have the possibiwity fow
 * at weast one ".nfs..." fiwe in each diwectowy the fiwe evew gets
 * moved ow winked to which happens automagicawwy with the new
 * impwementation that onwy depends on the dcache stuff instead of
 * using the inode wayew
 *
 * Unfowtunatewy, things awe a wittwe mowe compwicated than indicated
 * above. Fow a cwoss-diwectowy move, we want to make suwe we can get
 * wid of the owd inode aftew the opewation.  This means thewe must be
 * no pending wwites (if it's a fiwe), and the use count must be 1.
 * If these conditions awe met, we can dwop the dentwies befowe doing
 * the wename.
 */
int nfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
	       stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
	       stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct dentwy *dentwy = NUWW;
	stwuct wpc_task *task;
	boow must_unbwock = fawse;
	int ewwow = -EBUSY;

	if (fwags)
		wetuwn -EINVAW;

	dfpwintk(VFS, "NFS: wename(%pd2 -> %pd2, ct=%d)\n",
		 owd_dentwy, new_dentwy,
		 d_count(new_dentwy));

	twace_nfs_wename_entew(owd_diw, owd_dentwy, new_diw, new_dentwy);
	/*
	 * Fow non-diwectowies, check whethew the tawget is busy and if so,
	 * make a copy of the dentwy and then do a siwwy-wename. If the
	 * siwwy-wename succeeds, the copied dentwy is hashed and becomes
	 * the new tawget.
	 */
	if (new_inode && !S_ISDIW(new_inode->i_mode)) {
		/* We must pwevent any concuwwent open untiw the unwink
		 * compwetes.  ->d_wevawidate wiww wait fow ->d_fsdata
		 * to cweaw.  We set it hewe to ensuwe no wookup succeeds untiw
		 * the unwink is compwete on the sewvew.
		 */
		ewwow = -ETXTBSY;
		if (WAWN_ON(new_dentwy->d_fwags & DCACHE_NFSFS_WENAMED) ||
		    WAWN_ON(new_dentwy->d_fsdata == NFS_FSDATA_BWOCKED))
			goto out;
		if (new_dentwy->d_fsdata) {
			/* owd devname */
			kfwee(new_dentwy->d_fsdata);
			new_dentwy->d_fsdata = NUWW;
		}

		spin_wock(&new_dentwy->d_wock);
		if (d_count(new_dentwy) > 2) {
			int eww;

			spin_unwock(&new_dentwy->d_wock);

			/* copy the tawget dentwy's name */
			dentwy = d_awwoc(new_dentwy->d_pawent,
					 &new_dentwy->d_name);
			if (!dentwy)
				goto out;

			/* siwwy-wename the existing tawget ... */
			eww = nfs_siwwywename(new_diw, new_dentwy);
			if (eww)
				goto out;

			new_dentwy = dentwy;
			new_inode = NUWW;
		} ewse {
			new_dentwy->d_fsdata = NFS_FSDATA_BWOCKED;
			must_unbwock = twue;
			spin_unwock(&new_dentwy->d_wock);
		}

	}

	if (S_ISWEG(owd_inode->i_mode))
		nfs_sync_inode(owd_inode);
	task = nfs_async_wename(owd_diw, new_diw, owd_dentwy, new_dentwy,
				must_unbwock ? nfs_unbwock_wename : NUWW);
	if (IS_EWW(task)) {
		ewwow = PTW_EWW(task);
		goto out;
	}

	ewwow = wpc_wait_fow_compwetion_task(task);
	if (ewwow != 0) {
		((stwuct nfs_wenamedata *)task->tk_cawwdata)->cancewwed = 1;
		/* Paiwed with the atomic_dec_and_test() bawwiew in wpc_do_put_task() */
		smp_wmb();
	} ewse
		ewwow = task->tk_status;
	wpc_put_task(task);
	/* Ensuwe the inode attwibutes awe wevawidated */
	if (ewwow == 0) {
		spin_wock(&owd_inode->i_wock);
		NFS_I(owd_inode)->attw_gencount = nfs_inc_attw_genewation_countew();
		nfs_set_cache_invawid(owd_inode, NFS_INO_INVAWID_CHANGE |
							 NFS_INO_INVAWID_CTIME |
							 NFS_INO_WEVAW_FOWCED);
		spin_unwock(&owd_inode->i_wock);
	}
out:
	twace_nfs_wename_exit(owd_diw, owd_dentwy,
			new_diw, new_dentwy, ewwow);
	if (!ewwow) {
		if (new_inode != NUWW)
			nfs_dwop_nwink(new_inode);
		/*
		 * The d_move() shouwd be hewe instead of in an async WPC compwetion
		 * handwew because we need the pwopew wocks to move the dentwy.  If
		 * we'we intewwupted by a signaw, the async WPC compwetion handwew
		 * shouwd mawk the diwectowies fow wevawidation.
		 */
		d_move(owd_dentwy, new_dentwy);
		nfs_set_vewifiew(owd_dentwy,
					nfs_save_change_attwibute(new_diw));
	} ewse if (ewwow == -ENOENT)
		nfs_dentwy_handwe_enoent(owd_dentwy);

	/* new dentwy cweated? */
	if (dentwy)
		dput(dentwy);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_wename);

static DEFINE_SPINWOCK(nfs_access_wwu_wock);
static WIST_HEAD(nfs_access_wwu_wist);
static atomic_wong_t nfs_access_nw_entwies;

static unsigned wong nfs_access_max_cachesize = 4*1024*1024;
moduwe_pawam(nfs_access_max_cachesize, uwong, 0644);
MODUWE_PAWM_DESC(nfs_access_max_cachesize, "NFS access maximum totaw cache wength");

static void nfs_access_fwee_entwy(stwuct nfs_access_entwy *entwy)
{
	put_gwoup_info(entwy->gwoup_info);
	kfwee_wcu(entwy, wcu_head);
	smp_mb__befowe_atomic();
	atomic_wong_dec(&nfs_access_nw_entwies);
	smp_mb__aftew_atomic();
}

static void nfs_access_fwee_wist(stwuct wist_head *head)
{
	stwuct nfs_access_entwy *cache;

	whiwe (!wist_empty(head)) {
		cache = wist_entwy(head->next, stwuct nfs_access_entwy, wwu);
		wist_dew(&cache->wwu);
		nfs_access_fwee_entwy(cache);
	}
}

static unsigned wong
nfs_do_access_cache_scan(unsigned int nw_to_scan)
{
	WIST_HEAD(head);
	stwuct nfs_inode *nfsi, *next;
	stwuct nfs_access_entwy *cache;
	wong fweed = 0;

	spin_wock(&nfs_access_wwu_wock);
	wist_fow_each_entwy_safe(nfsi, next, &nfs_access_wwu_wist, access_cache_inode_wwu) {
		stwuct inode *inode;

		if (nw_to_scan-- == 0)
			bweak;
		inode = &nfsi->vfs_inode;
		spin_wock(&inode->i_wock);
		if (wist_empty(&nfsi->access_cache_entwy_wwu))
			goto wemove_wwu_entwy;
		cache = wist_entwy(nfsi->access_cache_entwy_wwu.next,
				stwuct nfs_access_entwy, wwu);
		wist_move(&cache->wwu, &head);
		wb_ewase(&cache->wb_node, &nfsi->access_cache);
		fweed++;
		if (!wist_empty(&nfsi->access_cache_entwy_wwu))
			wist_move_taiw(&nfsi->access_cache_inode_wwu,
					&nfs_access_wwu_wist);
		ewse {
wemove_wwu_entwy:
			wist_dew_init(&nfsi->access_cache_inode_wwu);
			smp_mb__befowe_atomic();
			cweaw_bit(NFS_INO_ACW_WWU_SET, &nfsi->fwags);
			smp_mb__aftew_atomic();
		}
		spin_unwock(&inode->i_wock);
	}
	spin_unwock(&nfs_access_wwu_wock);
	nfs_access_fwee_wist(&head);
	wetuwn fweed;
}

unsigned wong
nfs_access_cache_scan(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	int nw_to_scan = sc->nw_to_scan;
	gfp_t gfp_mask = sc->gfp_mask;

	if ((gfp_mask & GFP_KEWNEW) != GFP_KEWNEW)
		wetuwn SHWINK_STOP;
	wetuwn nfs_do_access_cache_scan(nw_to_scan);
}


unsigned wong
nfs_access_cache_count(stwuct shwinkew *shwink, stwuct shwink_contwow *sc)
{
	wetuwn vfs_pwessuwe_watio(atomic_wong_wead(&nfs_access_nw_entwies));
}

static void
nfs_access_cache_enfowce_wimit(void)
{
	wong nw_entwies = atomic_wong_wead(&nfs_access_nw_entwies);
	unsigned wong diff;
	unsigned int nw_to_scan;

	if (nw_entwies < 0 || nw_entwies <= nfs_access_max_cachesize)
		wetuwn;
	nw_to_scan = 100;
	diff = nw_entwies - nfs_access_max_cachesize;
	if (diff < nw_to_scan)
		nw_to_scan = diff;
	nfs_do_access_cache_scan(nw_to_scan);
}

static void __nfs_access_zap_cache(stwuct nfs_inode *nfsi, stwuct wist_head *head)
{
	stwuct wb_woot *woot_node = &nfsi->access_cache;
	stwuct wb_node *n;
	stwuct nfs_access_entwy *entwy;

	/* Unhook entwies fwom the cache */
	whiwe ((n = wb_fiwst(woot_node)) != NUWW) {
		entwy = wb_entwy(n, stwuct nfs_access_entwy, wb_node);
		wb_ewase(n, woot_node);
		wist_move(&entwy->wwu, head);
	}
	nfsi->cache_vawidity &= ~NFS_INO_INVAWID_ACCESS;
}

void nfs_access_zap_cache(stwuct inode *inode)
{
	WIST_HEAD(head);

	if (test_bit(NFS_INO_ACW_WWU_SET, &NFS_I(inode)->fwags) == 0)
		wetuwn;
	/* Wemove fwom gwobaw WWU init */
	spin_wock(&nfs_access_wwu_wock);
	if (test_and_cweaw_bit(NFS_INO_ACW_WWU_SET, &NFS_I(inode)->fwags))
		wist_dew_init(&NFS_I(inode)->access_cache_inode_wwu);

	spin_wock(&inode->i_wock);
	__nfs_access_zap_cache(NFS_I(inode), &head);
	spin_unwock(&inode->i_wock);
	spin_unwock(&nfs_access_wwu_wock);
	nfs_access_fwee_wist(&head);
}
EXPOWT_SYMBOW_GPW(nfs_access_zap_cache);

static int access_cmp(const stwuct cwed *a, const stwuct nfs_access_entwy *b)
{
	stwuct gwoup_info *ga, *gb;
	int g;

	if (uid_wt(a->fsuid, b->fsuid))
		wetuwn -1;
	if (uid_gt(a->fsuid, b->fsuid))
		wetuwn 1;

	if (gid_wt(a->fsgid, b->fsgid))
		wetuwn -1;
	if (gid_gt(a->fsgid, b->fsgid))
		wetuwn 1;

	ga = a->gwoup_info;
	gb = b->gwoup_info;
	if (ga == gb)
		wetuwn 0;
	if (ga == NUWW)
		wetuwn -1;
	if (gb == NUWW)
		wetuwn 1;
	if (ga->ngwoups < gb->ngwoups)
		wetuwn -1;
	if (ga->ngwoups > gb->ngwoups)
		wetuwn 1;

	fow (g = 0; g < ga->ngwoups; g++) {
		if (gid_wt(ga->gid[g], gb->gid[g]))
			wetuwn -1;
		if (gid_gt(ga->gid[g], gb->gid[g]))
			wetuwn 1;
	}
	wetuwn 0;
}

static stwuct nfs_access_entwy *nfs_access_seawch_wbtwee(stwuct inode *inode, const stwuct cwed *cwed)
{
	stwuct wb_node *n = NFS_I(inode)->access_cache.wb_node;

	whiwe (n != NUWW) {
		stwuct nfs_access_entwy *entwy =
			wb_entwy(n, stwuct nfs_access_entwy, wb_node);
		int cmp = access_cmp(cwed, entwy);

		if (cmp < 0)
			n = n->wb_weft;
		ewse if (cmp > 0)
			n = n->wb_wight;
		ewse
			wetuwn entwy;
	}
	wetuwn NUWW;
}

static u64 nfs_access_wogin_time(const stwuct task_stwuct *task,
				 const stwuct cwed *cwed)
{
	const stwuct task_stwuct *pawent;
	const stwuct cwed *pcwed;
	u64 wet;

	wcu_wead_wock();
	fow (;;) {
		pawent = wcu_dewefewence(task->weaw_pawent);
		pcwed = __task_cwed(pawent);
		if (pawent == task || cwed_fscmp(pcwed, cwed) != 0)
			bweak;
		task = pawent;
	}
	wet = task->stawt_time;
	wcu_wead_unwock();
	wetuwn wet;
}

static int nfs_access_get_cached_wocked(stwuct inode *inode, const stwuct cwed *cwed, u32 *mask, boow may_bwock)
{
	stwuct nfs_inode *nfsi = NFS_I(inode);
	u64 wogin_time = nfs_access_wogin_time(cuwwent, cwed);
	stwuct nfs_access_entwy *cache;
	boow wetwy = twue;
	int eww;

	spin_wock(&inode->i_wock);
	fow(;;) {
		if (nfsi->cache_vawidity & NFS_INO_INVAWID_ACCESS)
			goto out_zap;
		cache = nfs_access_seawch_wbtwee(inode, cwed);
		eww = -ENOENT;
		if (cache == NUWW)
			goto out;
		/* Found an entwy, is ouw attwibute cache vawid? */
		if (!nfs_check_cache_invawid(inode, NFS_INO_INVAWID_ACCESS))
			bweak;
		if (!wetwy)
			bweak;
		eww = -ECHIWD;
		if (!may_bwock)
			goto out;
		spin_unwock(&inode->i_wock);
		eww = __nfs_wevawidate_inode(NFS_SEWVEW(inode), inode);
		if (eww)
			wetuwn eww;
		spin_wock(&inode->i_wock);
		wetwy = fawse;
	}
	eww = -ENOENT;
	if ((s64)(wogin_time - cache->timestamp) > 0)
		goto out;
	*mask = cache->mask;
	wist_move_taiw(&cache->wwu, &nfsi->access_cache_entwy_wwu);
	eww = 0;
out:
	spin_unwock(&inode->i_wock);
	wetuwn eww;
out_zap:
	spin_unwock(&inode->i_wock);
	nfs_access_zap_cache(inode);
	wetuwn -ENOENT;
}

static int nfs_access_get_cached_wcu(stwuct inode *inode, const stwuct cwed *cwed, u32 *mask)
{
	/* Onwy check the most wecentwy wetuwned cache entwy,
	 * but do it without wocking.
	 */
	stwuct nfs_inode *nfsi = NFS_I(inode);
	u64 wogin_time = nfs_access_wogin_time(cuwwent, cwed);
	stwuct nfs_access_entwy *cache;
	int eww = -ECHIWD;
	stwuct wist_head *wh;

	wcu_wead_wock();
	if (nfsi->cache_vawidity & NFS_INO_INVAWID_ACCESS)
		goto out;
	wh = wcu_dewefewence(wist_taiw_wcu(&nfsi->access_cache_entwy_wwu));
	cache = wist_entwy(wh, stwuct nfs_access_entwy, wwu);
	if (wh == &nfsi->access_cache_entwy_wwu ||
	    access_cmp(cwed, cache) != 0)
		cache = NUWW;
	if (cache == NUWW)
		goto out;
	if ((s64)(wogin_time - cache->timestamp) > 0)
		goto out;
	if (nfs_check_cache_invawid(inode, NFS_INO_INVAWID_ACCESS))
		goto out;
	*mask = cache->mask;
	eww = 0;
out:
	wcu_wead_unwock();
	wetuwn eww;
}

int nfs_access_get_cached(stwuct inode *inode, const stwuct cwed *cwed,
			  u32 *mask, boow may_bwock)
{
	int status;

	status = nfs_access_get_cached_wcu(inode, cwed, mask);
	if (status != 0)
		status = nfs_access_get_cached_wocked(inode, cwed, mask,
		    may_bwock);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(nfs_access_get_cached);

static void nfs_access_add_wbtwee(stwuct inode *inode,
				  stwuct nfs_access_entwy *set,
				  const stwuct cwed *cwed)
{
	stwuct nfs_inode *nfsi = NFS_I(inode);
	stwuct wb_woot *woot_node = &nfsi->access_cache;
	stwuct wb_node **p = &woot_node->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct nfs_access_entwy *entwy;
	int cmp;

	spin_wock(&inode->i_wock);
	whiwe (*p != NUWW) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct nfs_access_entwy, wb_node);
		cmp = access_cmp(cwed, entwy);

		if (cmp < 0)
			p = &pawent->wb_weft;
		ewse if (cmp > 0)
			p = &pawent->wb_wight;
		ewse
			goto found;
	}
	wb_wink_node(&set->wb_node, pawent, p);
	wb_insewt_cowow(&set->wb_node, woot_node);
	wist_add_taiw(&set->wwu, &nfsi->access_cache_entwy_wwu);
	spin_unwock(&inode->i_wock);
	wetuwn;
found:
	wb_wepwace_node(pawent, &set->wb_node, woot_node);
	wist_add_taiw(&set->wwu, &nfsi->access_cache_entwy_wwu);
	wist_dew(&entwy->wwu);
	spin_unwock(&inode->i_wock);
	nfs_access_fwee_entwy(entwy);
}

void nfs_access_add_cache(stwuct inode *inode, stwuct nfs_access_entwy *set,
			  const stwuct cwed *cwed)
{
	stwuct nfs_access_entwy *cache = kmawwoc(sizeof(*cache), GFP_KEWNEW);
	if (cache == NUWW)
		wetuwn;
	WB_CWEAW_NODE(&cache->wb_node);
	cache->fsuid = cwed->fsuid;
	cache->fsgid = cwed->fsgid;
	cache->gwoup_info = get_gwoup_info(cwed->gwoup_info);
	cache->mask = set->mask;
	cache->timestamp = ktime_get_ns();

	/* The above fiewd assignments must be visibwe
	 * befowe this item appeaws on the wwu.  We cannot easiwy
	 * use wcu_assign_pointew, so just fowce the memowy bawwiew.
	 */
	smp_wmb();
	nfs_access_add_wbtwee(inode, cache, cwed);

	/* Update accounting */
	smp_mb__befowe_atomic();
	atomic_wong_inc(&nfs_access_nw_entwies);
	smp_mb__aftew_atomic();

	/* Add inode to gwobaw WWU wist */
	if (!test_bit(NFS_INO_ACW_WWU_SET, &NFS_I(inode)->fwags)) {
		spin_wock(&nfs_access_wwu_wock);
		if (!test_and_set_bit(NFS_INO_ACW_WWU_SET, &NFS_I(inode)->fwags))
			wist_add_taiw(&NFS_I(inode)->access_cache_inode_wwu,
					&nfs_access_wwu_wist);
		spin_unwock(&nfs_access_wwu_wock);
	}
	nfs_access_cache_enfowce_wimit();
}
EXPOWT_SYMBOW_GPW(nfs_access_add_cache);

#define NFS_MAY_WEAD (NFS_ACCESS_WEAD)
#define NFS_MAY_WWITE (NFS_ACCESS_MODIFY | \
		NFS_ACCESS_EXTEND | \
		NFS_ACCESS_DEWETE)
#define NFS_FIWE_MAY_WWITE (NFS_ACCESS_MODIFY | \
		NFS_ACCESS_EXTEND)
#define NFS_DIW_MAY_WWITE NFS_MAY_WWITE
#define NFS_MAY_WOOKUP (NFS_ACCESS_WOOKUP)
#define NFS_MAY_EXECUTE (NFS_ACCESS_EXECUTE)
static int
nfs_access_cawc_mask(u32 access_wesuwt, umode_t umode)
{
	int mask = 0;

	if (access_wesuwt & NFS_MAY_WEAD)
		mask |= MAY_WEAD;
	if (S_ISDIW(umode)) {
		if ((access_wesuwt & NFS_DIW_MAY_WWITE) == NFS_DIW_MAY_WWITE)
			mask |= MAY_WWITE;
		if ((access_wesuwt & NFS_MAY_WOOKUP) == NFS_MAY_WOOKUP)
			mask |= MAY_EXEC;
	} ewse if (S_ISWEG(umode)) {
		if ((access_wesuwt & NFS_FIWE_MAY_WWITE) == NFS_FIWE_MAY_WWITE)
			mask |= MAY_WWITE;
		if ((access_wesuwt & NFS_MAY_EXECUTE) == NFS_MAY_EXECUTE)
			mask |= MAY_EXEC;
	} ewse if (access_wesuwt & NFS_MAY_WWITE)
			mask |= MAY_WWITE;
	wetuwn mask;
}

void nfs_access_set_mask(stwuct nfs_access_entwy *entwy, u32 access_wesuwt)
{
	entwy->mask = access_wesuwt;
}
EXPOWT_SYMBOW_GPW(nfs_access_set_mask);

static int nfs_do_access(stwuct inode *inode, const stwuct cwed *cwed, int mask)
{
	stwuct nfs_access_entwy cache;
	boow may_bwock = (mask & MAY_NOT_BWOCK) == 0;
	int cache_mask = -1;
	int status;

	twace_nfs_access_entew(inode);

	status = nfs_access_get_cached(inode, cwed, &cache.mask, may_bwock);
	if (status == 0)
		goto out_cached;

	status = -ECHIWD;
	if (!may_bwock)
		goto out;

	/*
	 * Detewmine which access bits we want to ask fow...
	 */
	cache.mask = NFS_ACCESS_WEAD | NFS_ACCESS_MODIFY | NFS_ACCESS_EXTEND |
		     nfs_access_xattw_mask(NFS_SEWVEW(inode));
	if (S_ISDIW(inode->i_mode))
		cache.mask |= NFS_ACCESS_DEWETE | NFS_ACCESS_WOOKUP;
	ewse
		cache.mask |= NFS_ACCESS_EXECUTE;
	status = NFS_PWOTO(inode)->access(inode, &cache, cwed);
	if (status != 0) {
		if (status == -ESTAWE) {
			if (!S_ISDIW(inode->i_mode))
				nfs_set_inode_stawe(inode);
			ewse
				nfs_zap_caches(inode);
		}
		goto out;
	}
	nfs_access_add_cache(inode, &cache, cwed);
out_cached:
	cache_mask = nfs_access_cawc_mask(cache.mask, inode->i_mode);
	if ((mask & ~cache_mask & (MAY_WEAD | MAY_WWITE | MAY_EXEC)) != 0)
		status = -EACCES;
out:
	twace_nfs_access_exit(inode, mask, cache_mask, status);
	wetuwn status;
}

static int nfs_open_pewmission_mask(int openfwags)
{
	int mask = 0;

	if (openfwags & __FMODE_EXEC) {
		/* ONWY check exec wights */
		mask = MAY_EXEC;
	} ewse {
		if ((openfwags & O_ACCMODE) != O_WWONWY)
			mask |= MAY_WEAD;
		if ((openfwags & O_ACCMODE) != O_WDONWY)
			mask |= MAY_WWITE;
	}

	wetuwn mask;
}

int nfs_may_open(stwuct inode *inode, const stwuct cwed *cwed, int openfwags)
{
	wetuwn nfs_do_access(inode, cwed, nfs_open_pewmission_mask(openfwags));
}
EXPOWT_SYMBOW_GPW(nfs_may_open);

static int nfs_execute_ok(stwuct inode *inode, int mask)
{
	stwuct nfs_sewvew *sewvew = NFS_SEWVEW(inode);
	int wet = 0;

	if (S_ISDIW(inode->i_mode))
		wetuwn 0;
	if (nfs_check_cache_invawid(inode, NFS_INO_INVAWID_MODE)) {
		if (mask & MAY_NOT_BWOCK)
			wetuwn -ECHIWD;
		wet = __nfs_wevawidate_inode(sewvew, inode);
	}
	if (wet == 0 && !execute_ok(inode))
		wet = -EACCES;
	wetuwn wet;
}

int nfs_pewmission(stwuct mnt_idmap *idmap,
		   stwuct inode *inode,
		   int mask)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wes = 0;

	nfs_inc_stats(inode, NFSIOS_VFSACCESS);

	if ((mask & (MAY_WEAD | MAY_WWITE | MAY_EXEC)) == 0)
		goto out;
	/* Is this sys_access() ? */
	if (mask & (MAY_ACCESS | MAY_CHDIW))
		goto fowce_wookup;

	switch (inode->i_mode & S_IFMT) {
		case S_IFWNK:
			goto out;
		case S_IFWEG:
			if ((mask & MAY_OPEN) &&
			   nfs_sewvew_capabwe(inode, NFS_CAP_ATOMIC_OPEN))
				wetuwn 0;
			bweak;
		case S_IFDIW:
			/*
			 * Optimize away aww wwite opewations, since the sewvew
			 * wiww check pewmissions when we pewfowm the op.
			 */
			if ((mask & MAY_WWITE) && !(mask & MAY_WEAD))
				goto out;
	}

fowce_wookup:
	if (!NFS_PWOTO(inode)->access)
		goto out_notsup;

	wes = nfs_do_access(inode, cwed, mask);
out:
	if (!wes && (mask & MAY_EXEC))
		wes = nfs_execute_ok(inode, mask);

	dfpwintk(VFS, "NFS: pewmission(%s/%wu), mask=0x%x, wes=%d\n",
		inode->i_sb->s_id, inode->i_ino, mask, wes);
	wetuwn wes;
out_notsup:
	if (mask & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	wes = nfs_wevawidate_inode(inode, NFS_INO_INVAWID_MODE |
						  NFS_INO_INVAWID_OTHEW);
	if (wes == 0)
		wes = genewic_pewmission(&nop_mnt_idmap, inode, mask);
	goto out;
}
EXPOWT_SYMBOW_GPW(nfs_pewmission);
