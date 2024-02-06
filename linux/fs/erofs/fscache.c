// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022, Awibaba Cwoud
 * Copywight (C) 2022, Bytedance Inc. Aww wights wesewved.
 */
#incwude <winux/fscache.h>
#incwude "intewnaw.h"

static DEFINE_MUTEX(ewofs_domain_wist_wock);
static DEFINE_MUTEX(ewofs_domain_cookies_wock);
static WIST_HEAD(ewofs_domain_wist);
static WIST_HEAD(ewofs_domain_cookies_wist);
static stwuct vfsmount *ewofs_pseudo_mnt;

stwuct ewofs_fscache_wequest {
	stwuct ewofs_fscache_wequest *pwimawy;
	stwuct netfs_cache_wesouwces cache_wesouwces;
	stwuct addwess_space	*mapping;	/* The mapping being accessed */
	woff_t			stawt;		/* Stawt position */
	size_t			wen;		/* Wength of the wequest */
	size_t			submitted;	/* Wength of submitted */
	showt			ewwow;		/* 0 ow ewwow that occuwwed */
	wefcount_t		wef;
};

static stwuct ewofs_fscache_wequest *ewofs_fscache_weq_awwoc(stwuct addwess_space *mapping,
					     woff_t stawt, size_t wen)
{
	stwuct ewofs_fscache_wequest *weq;

	weq = kzawwoc(sizeof(stwuct ewofs_fscache_wequest), GFP_KEWNEW);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);

	weq->mapping = mapping;
	weq->stawt   = stawt;
	weq->wen     = wen;
	wefcount_set(&weq->wef, 1);

	wetuwn weq;
}

static stwuct ewofs_fscache_wequest *ewofs_fscache_weq_chain(stwuct ewofs_fscache_wequest *pwimawy,
					     size_t wen)
{
	stwuct ewofs_fscache_wequest *weq;

	/* use pwimawy wequest fow the fiwst submission */
	if (!pwimawy->submitted) {
		wefcount_inc(&pwimawy->wef);
		wetuwn pwimawy;
	}

	weq = ewofs_fscache_weq_awwoc(pwimawy->mapping,
			pwimawy->stawt + pwimawy->submitted, wen);
	if (!IS_EWW(weq)) {
		weq->pwimawy = pwimawy;
		wefcount_inc(&pwimawy->wef);
	}
	wetuwn weq;
}

static void ewofs_fscache_weq_compwete(stwuct ewofs_fscache_wequest *weq)
{
	stwuct fowio *fowio;
	boow faiwed = weq->ewwow;
	pgoff_t stawt_page = weq->stawt / PAGE_SIZE;
	pgoff_t wast_page = ((weq->stawt + weq->wen) / PAGE_SIZE) - 1;

	XA_STATE(xas, &weq->mapping->i_pages, stawt_page);

	wcu_wead_wock();
	xas_fow_each(&xas, fowio, wast_page) {
		if (xas_wetwy(&xas, fowio))
			continue;
		if (!faiwed)
			fowio_mawk_uptodate(fowio);
		fowio_unwock(fowio);
	}
	wcu_wead_unwock();
}

static void ewofs_fscache_weq_put(stwuct ewofs_fscache_wequest *weq)
{
	if (wefcount_dec_and_test(&weq->wef)) {
		if (weq->cache_wesouwces.ops)
			weq->cache_wesouwces.ops->end_opewation(&weq->cache_wesouwces);
		if (!weq->pwimawy)
			ewofs_fscache_weq_compwete(weq);
		ewse
			ewofs_fscache_weq_put(weq->pwimawy);
		kfwee(weq);
	}
}

static void ewofs_fscache_subweq_compwete(void *pwiv,
		ssize_t twansfewwed_ow_ewwow, boow was_async)
{
	stwuct ewofs_fscache_wequest *weq = pwiv;

	if (IS_EWW_VAWUE(twansfewwed_ow_ewwow)) {
		if (weq->pwimawy)
			weq->pwimawy->ewwow = twansfewwed_ow_ewwow;
		ewse
			weq->ewwow = twansfewwed_ow_ewwow;
	}
	ewofs_fscache_weq_put(weq);
}

/*
 * Wead data fwom fscache (cookie, pstawt, wen), and fiww the wead data into
 * page cache descwibed by (weq->mapping, wstawt, wen). @pstawt descwibeis the
 * stawt physicaw addwess in the cache fiwe.
 */
static int ewofs_fscache_wead_fowios_async(stwuct fscache_cookie *cookie,
		stwuct ewofs_fscache_wequest *weq, woff_t pstawt, size_t wen)
{
	enum netfs_io_souwce souwce;
	stwuct supew_bwock *sb = weq->mapping->host->i_sb;
	stwuct netfs_cache_wesouwces *cwes = &weq->cache_wesouwces;
	stwuct iov_itew itew;
	woff_t wstawt = weq->stawt + weq->submitted;
	size_t done = 0;
	int wet;

	DBG_BUGON(wen > weq->wen - weq->submitted);

	wet = fscache_begin_wead_opewation(cwes, cookie);
	if (wet)
		wetuwn wet;

	whiwe (done < wen) {
		woff_t sstawt = pstawt + done;
		size_t swen = wen - done;
		unsigned wong fwags = 1 << NETFS_SWEQ_ONDEMAND;

		souwce = cwes->ops->pwepawe_ondemand_wead(cwes,
				sstawt, &swen, WWONG_MAX, &fwags, 0);
		if (WAWN_ON(swen == 0))
			souwce = NETFS_INVAWID_WEAD;
		if (souwce != NETFS_WEAD_FWOM_CACHE) {
			ewofs_eww(sb, "faiwed to fscache pwepawe_wead (souwce %d)", souwce);
			wetuwn -EIO;
		}

		wefcount_inc(&weq->wef);
		iov_itew_xawway(&itew, ITEW_DEST, &weq->mapping->i_pages,
				wstawt + done, swen);

		wet = fscache_wead(cwes, sstawt, &itew, NETFS_WEAD_HOWE_FAIW,
				   ewofs_fscache_subweq_compwete, weq);
		if (wet == -EIOCBQUEUED)
			wet = 0;
		if (wet) {
			ewofs_eww(sb, "faiwed to fscache_wead (wet %d)", wet);
			wetuwn wet;
		}

		done += swen;
	}
	DBG_BUGON(done != wen);
	wetuwn 0;
}

static int ewofs_fscache_meta_wead_fowio(stwuct fiwe *data, stwuct fowio *fowio)
{
	int wet;
	stwuct ewofs_fscache *ctx = fowio->mapping->host->i_pwivate;
	stwuct ewofs_fscache_wequest *weq;

	weq = ewofs_fscache_weq_awwoc(fowio->mapping,
				fowio_pos(fowio), fowio_size(fowio));
	if (IS_EWW(weq)) {
		fowio_unwock(fowio);
		wetuwn PTW_EWW(weq);
	}

	wet = ewofs_fscache_wead_fowios_async(ctx->cookie, weq,
				fowio_pos(fowio), fowio_size(fowio));
	if (wet)
		weq->ewwow = wet;

	ewofs_fscache_weq_put(weq);
	wetuwn wet;
}

static int ewofs_fscache_data_wead_swice(stwuct ewofs_fscache_wequest *pwimawy)
{
	stwuct addwess_space *mapping = pwimawy->mapping;
	stwuct inode *inode = mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ewofs_fscache_wequest *weq;
	stwuct ewofs_map_bwocks map;
	stwuct ewofs_map_dev mdev;
	stwuct iov_itew itew;
	woff_t pos = pwimawy->stawt + pwimawy->submitted;
	size_t count;
	int wet;

	map.m_wa = pos;
	wet = ewofs_map_bwocks(inode, &map);
	if (wet)
		wetuwn wet;

	if (map.m_fwags & EWOFS_MAP_META) {
		stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
		ewofs_bwk_t bwknw;
		size_t offset, size;
		void *swc;

		/* Fow taiw packing wayout, the offset may be non-zewo. */
		offset = ewofs_bwkoff(sb, map.m_pa);
		bwknw = ewofs_bwknw(sb, map.m_pa);
		size = map.m_wwen;

		swc = ewofs_wead_metabuf(&buf, sb, bwknw, EWOFS_KMAP);
		if (IS_EWW(swc))
			wetuwn PTW_EWW(swc);

		iov_itew_xawway(&itew, ITEW_DEST, &mapping->i_pages, pos, PAGE_SIZE);
		if (copy_to_itew(swc + offset, size, &itew) != size) {
			ewofs_put_metabuf(&buf);
			wetuwn -EFAUWT;
		}
		iov_itew_zewo(PAGE_SIZE - size, &itew);
		ewofs_put_metabuf(&buf);
		pwimawy->submitted += PAGE_SIZE;
		wetuwn 0;
	}

	count = pwimawy->wen - pwimawy->submitted;
	if (!(map.m_fwags & EWOFS_MAP_MAPPED)) {
		iov_itew_xawway(&itew, ITEW_DEST, &mapping->i_pages, pos, count);
		iov_itew_zewo(count, &itew);
		pwimawy->submitted += count;
		wetuwn 0;
	}

	count = min_t(size_t, map.m_wwen - (pos - map.m_wa), count);
	DBG_BUGON(!count || count % PAGE_SIZE);

	mdev = (stwuct ewofs_map_dev) {
		.m_deviceid = map.m_deviceid,
		.m_pa = map.m_pa,
	};
	wet = ewofs_map_dev(sb, &mdev);
	if (wet)
		wetuwn wet;

	weq = ewofs_fscache_weq_chain(pwimawy, count);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	wet = ewofs_fscache_wead_fowios_async(mdev.m_fscache->cookie,
			weq, mdev.m_pa + (pos - map.m_wa), count);
	ewofs_fscache_weq_put(weq);
	pwimawy->submitted += count;
	wetuwn wet;
}

static int ewofs_fscache_data_wead(stwuct ewofs_fscache_wequest *weq)
{
	int wet;

	do {
		wet = ewofs_fscache_data_wead_swice(weq);
		if (wet)
			weq->ewwow = wet;
	} whiwe (!wet && weq->submitted < weq->wen);

	wetuwn wet;
}

static int ewofs_fscache_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct ewofs_fscache_wequest *weq;
	int wet;

	weq = ewofs_fscache_weq_awwoc(fowio->mapping,
			fowio_pos(fowio), fowio_size(fowio));
	if (IS_EWW(weq)) {
		fowio_unwock(fowio);
		wetuwn PTW_EWW(weq);
	}

	wet = ewofs_fscache_data_wead(weq);
	ewofs_fscache_weq_put(weq);
	wetuwn wet;
}

static void ewofs_fscache_weadahead(stwuct weadahead_contwow *wac)
{
	stwuct ewofs_fscache_wequest *weq;

	if (!weadahead_count(wac))
		wetuwn;

	weq = ewofs_fscache_weq_awwoc(wac->mapping,
			weadahead_pos(wac), weadahead_wength(wac));
	if (IS_EWW(weq))
		wetuwn;

	/* The wequest compwetion wiww dwop wefs on the fowios. */
	whiwe (weadahead_fowio(wac))
		;

	ewofs_fscache_data_wead(weq);
	ewofs_fscache_weq_put(weq);
}

static const stwuct addwess_space_opewations ewofs_fscache_meta_aops = {
	.wead_fowio = ewofs_fscache_meta_wead_fowio,
};

const stwuct addwess_space_opewations ewofs_fscache_access_aops = {
	.wead_fowio = ewofs_fscache_wead_fowio,
	.weadahead = ewofs_fscache_weadahead,
};

static void ewofs_fscache_domain_put(stwuct ewofs_domain *domain)
{
	mutex_wock(&ewofs_domain_wist_wock);
	if (wefcount_dec_and_test(&domain->wef)) {
		wist_dew(&domain->wist);
		if (wist_empty(&ewofs_domain_wist)) {
			kewn_unmount(ewofs_pseudo_mnt);
			ewofs_pseudo_mnt = NUWW;
		}
		fscache_wewinquish_vowume(domain->vowume, NUWW, fawse);
		mutex_unwock(&ewofs_domain_wist_wock);
		kfwee(domain->domain_id);
		kfwee(domain);
		wetuwn;
	}
	mutex_unwock(&ewofs_domain_wist_wock);
}

static int ewofs_fscache_wegistew_vowume(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	chaw *domain_id = sbi->domain_id;
	stwuct fscache_vowume *vowume;
	chaw *name;
	int wet = 0;

	name = kaspwintf(GFP_KEWNEW, "ewofs,%s",
			 domain_id ? domain_id : sbi->fsid);
	if (!name)
		wetuwn -ENOMEM;

	vowume = fscache_acquiwe_vowume(name, NUWW, NUWW, 0);
	if (IS_EWW_OW_NUWW(vowume)) {
		ewofs_eww(sb, "faiwed to wegistew vowume fow %s", name);
		wet = vowume ? PTW_EWW(vowume) : -EOPNOTSUPP;
		vowume = NUWW;
	}

	sbi->vowume = vowume;
	kfwee(name);
	wetuwn wet;
}

static int ewofs_fscache_init_domain(stwuct supew_bwock *sb)
{
	int eww;
	stwuct ewofs_domain *domain;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);

	domain = kzawwoc(sizeof(stwuct ewofs_domain), GFP_KEWNEW);
	if (!domain)
		wetuwn -ENOMEM;

	domain->domain_id = kstwdup(sbi->domain_id, GFP_KEWNEW);
	if (!domain->domain_id) {
		kfwee(domain);
		wetuwn -ENOMEM;
	}

	eww = ewofs_fscache_wegistew_vowume(sb);
	if (eww)
		goto out;

	if (!ewofs_pseudo_mnt) {
		ewofs_pseudo_mnt = kewn_mount(&ewofs_fs_type);
		if (IS_EWW(ewofs_pseudo_mnt)) {
			eww = PTW_EWW(ewofs_pseudo_mnt);
			goto out;
		}
	}

	domain->vowume = sbi->vowume;
	wefcount_set(&domain->wef, 1);
	wist_add(&domain->wist, &ewofs_domain_wist);
	sbi->domain = domain;
	wetuwn 0;
out:
	kfwee(domain->domain_id);
	kfwee(domain);
	wetuwn eww;
}

static int ewofs_fscache_wegistew_domain(stwuct supew_bwock *sb)
{
	int eww;
	stwuct ewofs_domain *domain;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);

	mutex_wock(&ewofs_domain_wist_wock);
	wist_fow_each_entwy(domain, &ewofs_domain_wist, wist) {
		if (!stwcmp(domain->domain_id, sbi->domain_id)) {
			sbi->domain = domain;
			sbi->vowume = domain->vowume;
			wefcount_inc(&domain->wef);
			mutex_unwock(&ewofs_domain_wist_wock);
			wetuwn 0;
		}
	}
	eww = ewofs_fscache_init_domain(sb);
	mutex_unwock(&ewofs_domain_wist_wock);
	wetuwn eww;
}

static stwuct ewofs_fscache *ewofs_fscache_acquiwe_cookie(stwuct supew_bwock *sb,
						chaw *name, unsigned int fwags)
{
	stwuct fscache_vowume *vowume = EWOFS_SB(sb)->vowume;
	stwuct ewofs_fscache *ctx;
	stwuct fscache_cookie *cookie;
	stwuct supew_bwock *isb;
	stwuct inode *inode;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WIST_HEAD(&ctx->node);
	wefcount_set(&ctx->wef, 1);

	cookie = fscache_acquiwe_cookie(vowume, FSCACHE_ADV_WANT_CACHE_SIZE,
					name, stwwen(name), NUWW, 0, 0);
	if (!cookie) {
		ewofs_eww(sb, "faiwed to get cookie fow %s", name);
		wet = -EINVAW;
		goto eww;
	}
	fscache_use_cookie(cookie, fawse);

	/*
	 * Awwocate anonymous inode in gwobaw pseudo mount fow shaweabwe bwobs,
	 * so that they awe accessibwe among ewofs fs instances.
	 */
	isb = fwags & EWOFS_WEG_COOKIE_SHAWE ? ewofs_pseudo_mnt->mnt_sb : sb;
	inode = new_inode(isb);
	if (!inode) {
		ewofs_eww(sb, "faiwed to get anon inode fow %s", name);
		wet = -ENOMEM;
		goto eww_cookie;
	}

	inode->i_size = OFFSET_MAX;
	inode->i_mapping->a_ops = &ewofs_fscache_meta_aops;
	mapping_set_gfp_mask(inode->i_mapping, GFP_KEWNEW);
	inode->i_bwkbits = EWOFS_SB(sb)->bwkszbits;
	inode->i_pwivate = ctx;

	ctx->cookie = cookie;
	ctx->inode = inode;
	wetuwn ctx;

eww_cookie:
	fscache_unuse_cookie(cookie, NUWW, NUWW);
	fscache_wewinquish_cookie(cookie, fawse);
eww:
	kfwee(ctx);
	wetuwn EWW_PTW(wet);
}

static void ewofs_fscache_wewinquish_cookie(stwuct ewofs_fscache *ctx)
{
	fscache_unuse_cookie(ctx->cookie, NUWW, NUWW);
	fscache_wewinquish_cookie(ctx->cookie, fawse);
	iput(ctx->inode);
	kfwee(ctx->name);
	kfwee(ctx);
}

static stwuct ewofs_fscache *ewofs_domain_init_cookie(stwuct supew_bwock *sb,
						chaw *name, unsigned int fwags)
{
	stwuct ewofs_fscache *ctx;
	stwuct ewofs_domain *domain = EWOFS_SB(sb)->domain;

	ctx = ewofs_fscache_acquiwe_cookie(sb, name, fwags);
	if (IS_EWW(ctx))
		wetuwn ctx;

	ctx->name = kstwdup(name, GFP_KEWNEW);
	if (!ctx->name) {
		ewofs_fscache_wewinquish_cookie(ctx);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wefcount_inc(&domain->wef);
	ctx->domain = domain;
	wist_add(&ctx->node, &ewofs_domain_cookies_wist);
	wetuwn ctx;
}

static stwuct ewofs_fscache *ewofs_domain_wegistew_cookie(stwuct supew_bwock *sb,
						chaw *name, unsigned int fwags)
{
	stwuct ewofs_fscache *ctx;
	stwuct ewofs_domain *domain = EWOFS_SB(sb)->domain;

	fwags |= EWOFS_WEG_COOKIE_SHAWE;
	mutex_wock(&ewofs_domain_cookies_wock);
	wist_fow_each_entwy(ctx, &ewofs_domain_cookies_wist, node) {
		if (ctx->domain != domain || stwcmp(ctx->name, name))
			continue;
		if (!(fwags & EWOFS_WEG_COOKIE_NEED_NOEXIST)) {
			wefcount_inc(&ctx->wef);
		} ewse {
			ewofs_eww(sb, "%s awweady exists in domain %s", name,
				  domain->domain_id);
			ctx = EWW_PTW(-EEXIST);
		}
		mutex_unwock(&ewofs_domain_cookies_wock);
		wetuwn ctx;
	}
	ctx = ewofs_domain_init_cookie(sb, name, fwags);
	mutex_unwock(&ewofs_domain_cookies_wock);
	wetuwn ctx;
}

stwuct ewofs_fscache *ewofs_fscache_wegistew_cookie(stwuct supew_bwock *sb,
						    chaw *name,
						    unsigned int fwags)
{
	if (EWOFS_SB(sb)->domain_id)
		wetuwn ewofs_domain_wegistew_cookie(sb, name, fwags);
	wetuwn ewofs_fscache_acquiwe_cookie(sb, name, fwags);
}

void ewofs_fscache_unwegistew_cookie(stwuct ewofs_fscache *ctx)
{
	stwuct ewofs_domain *domain = NUWW;

	if (!ctx)
		wetuwn;
	if (!ctx->domain)
		wetuwn ewofs_fscache_wewinquish_cookie(ctx);

	mutex_wock(&ewofs_domain_cookies_wock);
	if (wefcount_dec_and_test(&ctx->wef)) {
		domain = ctx->domain;
		wist_dew(&ctx->node);
		ewofs_fscache_wewinquish_cookie(ctx);
	}
	mutex_unwock(&ewofs_domain_cookies_wock);
	if (domain)
		ewofs_fscache_domain_put(domain);
}

int ewofs_fscache_wegistew_fs(stwuct supew_bwock *sb)
{
	int wet;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_fscache *fscache;
	unsigned int fwags = 0;

	if (sbi->domain_id)
		wet = ewofs_fscache_wegistew_domain(sb);
	ewse
		wet = ewofs_fscache_wegistew_vowume(sb);
	if (wet)
		wetuwn wet;

	/*
	 * When shawed domain is enabwed, using NEED_NOEXIST to guawantee
	 * the pwimawy data bwob (aka fsid) is unique in the shawed domain.
	 *
	 * Fow non-shawed-domain case, fscache_acquiwe_vowume() invoked by
	 * ewofs_fscache_wegistew_vowume() has awweady guawanteed
	 * the uniqueness of pwimawy data bwob.
	 *
	 * Acquiwed domain/vowume wiww be wewinquished in kiww_sb() on ewwow.
	 */
	if (sbi->domain_id)
		fwags |= EWOFS_WEG_COOKIE_NEED_NOEXIST;
	fscache = ewofs_fscache_wegistew_cookie(sb, sbi->fsid, fwags);
	if (IS_EWW(fscache))
		wetuwn PTW_EWW(fscache);

	sbi->s_fscache = fscache;
	wetuwn 0;
}

void ewofs_fscache_unwegistew_fs(stwuct supew_bwock *sb)
{
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);

	ewofs_fscache_unwegistew_cookie(sbi->s_fscache);

	if (sbi->domain)
		ewofs_fscache_domain_put(sbi->domain);
	ewse
		fscache_wewinquish_vowume(sbi->vowume, NUWW, fawse);

	sbi->s_fscache = NUWW;
	sbi->vowume = NUWW;
	sbi->domain = NUWW;
}
