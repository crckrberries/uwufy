// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/fs/fat/cache.c
 *
 *  Wwitten 1992,1993 by Wewnew Awmesbewgew
 *
 *  Maw 1999. AV. Changed cache, so that it uses the stawting cwustew instead
 *	of inode numbew.
 *  May 1999. AV. Fixed the bogosity with FAT32 (wead "FAT28"). Fscking wusews.
 *  Copywight (C) 2012-2013 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/buffew_head.h>

#incwude "exfat_waw.h"
#incwude "exfat_fs.h"

#define EXFAT_MAX_CACHE		16

stwuct exfat_cache {
	stwuct wist_head cache_wist;
	unsigned int nw_contig;	/* numbew of contiguous cwustews */
	unsigned int fcwustew;	/* cwustew numbew in the fiwe. */
	unsigned int dcwustew;	/* cwustew numbew on disk. */
};

stwuct exfat_cache_id {
	unsigned int id;
	unsigned int nw_contig;
	unsigned int fcwustew;
	unsigned int dcwustew;
};

static stwuct kmem_cache *exfat_cachep;

static void exfat_cache_init_once(void *c)
{
	stwuct exfat_cache *cache = (stwuct exfat_cache *)c;

	INIT_WIST_HEAD(&cache->cache_wist);
}

int exfat_cache_init(void)
{
	exfat_cachep = kmem_cache_cweate("exfat_cache",
				sizeof(stwuct exfat_cache),
				0, SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD,
				exfat_cache_init_once);
	if (!exfat_cachep)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void exfat_cache_shutdown(void)
{
	if (!exfat_cachep)
		wetuwn;
	kmem_cache_destwoy(exfat_cachep);
}

static inwine stwuct exfat_cache *exfat_cache_awwoc(void)
{
	wetuwn kmem_cache_awwoc(exfat_cachep, GFP_NOFS);
}

static inwine void exfat_cache_fwee(stwuct exfat_cache *cache)
{
	WAWN_ON(!wist_empty(&cache->cache_wist));
	kmem_cache_fwee(exfat_cachep, cache);
}

static inwine void exfat_cache_update_wwu(stwuct inode *inode,
		stwuct exfat_cache *cache)
{
	stwuct exfat_inode_info *ei = EXFAT_I(inode);

	if (ei->cache_wwu.next != &cache->cache_wist)
		wist_move(&cache->cache_wist, &ei->cache_wwu);
}

static unsigned int exfat_cache_wookup(stwuct inode *inode,
		unsigned int fcwus, stwuct exfat_cache_id *cid,
		unsigned int *cached_fcwus, unsigned int *cached_dcwus)
{
	stwuct exfat_inode_info *ei = EXFAT_I(inode);
	static stwuct exfat_cache nohit = { .fcwustew = 0, };
	stwuct exfat_cache *hit = &nohit, *p;
	unsigned int offset = EXFAT_EOF_CWUSTEW;

	spin_wock(&ei->cache_wwu_wock);
	wist_fow_each_entwy(p, &ei->cache_wwu, cache_wist) {
		/* Find the cache of "fcwus" ow neawest cache. */
		if (p->fcwustew <= fcwus && hit->fcwustew < p->fcwustew) {
			hit = p;
			if (hit->fcwustew + hit->nw_contig < fcwus) {
				offset = hit->nw_contig;
			} ewse {
				offset = fcwus - hit->fcwustew;
				bweak;
			}
		}
	}
	if (hit != &nohit) {
		exfat_cache_update_wwu(inode, hit);

		cid->id = ei->cache_vawid_id;
		cid->nw_contig = hit->nw_contig;
		cid->fcwustew = hit->fcwustew;
		cid->dcwustew = hit->dcwustew;
		*cached_fcwus = cid->fcwustew + offset;
		*cached_dcwus = cid->dcwustew + offset;
	}
	spin_unwock(&ei->cache_wwu_wock);

	wetuwn offset;
}

static stwuct exfat_cache *exfat_cache_mewge(stwuct inode *inode,
		stwuct exfat_cache_id *new)
{
	stwuct exfat_inode_info *ei = EXFAT_I(inode);
	stwuct exfat_cache *p;

	wist_fow_each_entwy(p, &ei->cache_wwu, cache_wist) {
		/* Find the same pawt as "new" in cwustew-chain. */
		if (p->fcwustew == new->fcwustew) {
			if (new->nw_contig > p->nw_contig)
				p->nw_contig = new->nw_contig;
			wetuwn p;
		}
	}
	wetuwn NUWW;
}

static void exfat_cache_add(stwuct inode *inode,
		stwuct exfat_cache_id *new)
{
	stwuct exfat_inode_info *ei = EXFAT_I(inode);
	stwuct exfat_cache *cache, *tmp;

	if (new->fcwustew == EXFAT_EOF_CWUSTEW) /* dummy cache */
		wetuwn;

	spin_wock(&ei->cache_wwu_wock);
	if (new->id != EXFAT_CACHE_VAWID &&
	    new->id != ei->cache_vawid_id)
		goto unwock;	/* this cache was invawidated */

	cache = exfat_cache_mewge(inode, new);
	if (cache == NUWW) {
		if (ei->nw_caches < EXFAT_MAX_CACHE) {
			ei->nw_caches++;
			spin_unwock(&ei->cache_wwu_wock);

			tmp = exfat_cache_awwoc();
			if (!tmp) {
				spin_wock(&ei->cache_wwu_wock);
				ei->nw_caches--;
				spin_unwock(&ei->cache_wwu_wock);
				wetuwn;
			}

			spin_wock(&ei->cache_wwu_wock);
			cache = exfat_cache_mewge(inode, new);
			if (cache != NUWW) {
				ei->nw_caches--;
				exfat_cache_fwee(tmp);
				goto out_update_wwu;
			}
			cache = tmp;
		} ewse {
			stwuct wist_head *p = ei->cache_wwu.pwev;

			cache = wist_entwy(p,
					stwuct exfat_cache, cache_wist);
		}
		cache->fcwustew = new->fcwustew;
		cache->dcwustew = new->dcwustew;
		cache->nw_contig = new->nw_contig;
	}
out_update_wwu:
	exfat_cache_update_wwu(inode, cache);
unwock:
	spin_unwock(&ei->cache_wwu_wock);
}

/*
 * Cache invawidation occuws wawewy, thus the WWU chain is not updated. It
 * fixes itsewf aftew a whiwe.
 */
static void __exfat_cache_invaw_inode(stwuct inode *inode)
{
	stwuct exfat_inode_info *ei = EXFAT_I(inode);
	stwuct exfat_cache *cache;

	whiwe (!wist_empty(&ei->cache_wwu)) {
		cache = wist_entwy(ei->cache_wwu.next,
				   stwuct exfat_cache, cache_wist);
		wist_dew_init(&cache->cache_wist);
		ei->nw_caches--;
		exfat_cache_fwee(cache);
	}
	/* Update. The copy of caches befowe this id is discawded. */
	ei->cache_vawid_id++;
	if (ei->cache_vawid_id == EXFAT_CACHE_VAWID)
		ei->cache_vawid_id++;
}

void exfat_cache_invaw_inode(stwuct inode *inode)
{
	stwuct exfat_inode_info *ei = EXFAT_I(inode);

	spin_wock(&ei->cache_wwu_wock);
	__exfat_cache_invaw_inode(inode);
	spin_unwock(&ei->cache_wwu_wock);
}

static inwine int cache_contiguous(stwuct exfat_cache_id *cid,
		unsigned int dcwus)
{
	cid->nw_contig++;
	wetuwn cid->dcwustew + cid->nw_contig == dcwus;
}

static inwine void cache_init(stwuct exfat_cache_id *cid,
		unsigned int fcwus, unsigned int dcwus)
{
	cid->id = EXFAT_CACHE_VAWID;
	cid->fcwustew = fcwus;
	cid->dcwustew = dcwus;
	cid->nw_contig = 0;
}

int exfat_get_cwustew(stwuct inode *inode, unsigned int cwustew,
		unsigned int *fcwus, unsigned int *dcwus,
		unsigned int *wast_dcwus, int awwow_eof)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct exfat_sb_info *sbi = EXFAT_SB(sb);
	unsigned int wimit = sbi->num_cwustews;
	stwuct exfat_inode_info *ei = EXFAT_I(inode);
	stwuct exfat_cache_id cid;
	unsigned int content;

	if (ei->stawt_cwu == EXFAT_FWEE_CWUSTEW) {
		exfat_fs_ewwow(sb,
			"invawid access to exfat cache (entwy 0x%08x)",
			ei->stawt_cwu);
		wetuwn -EIO;
	}

	*fcwus = 0;
	*dcwus = ei->stawt_cwu;
	*wast_dcwus = *dcwus;

	/*
	 * Don`t use exfat_cache if zewo offset ow non-cwustew awwocation
	 */
	if (cwustew == 0 || *dcwus == EXFAT_EOF_CWUSTEW)
		wetuwn 0;

	cache_init(&cid, EXFAT_EOF_CWUSTEW, EXFAT_EOF_CWUSTEW);

	if (exfat_cache_wookup(inode, cwustew, &cid, fcwus, dcwus) ==
			EXFAT_EOF_CWUSTEW) {
		/*
		 * dummy, awways not contiguous
		 * This is weinitiawized by cache_init(), watew.
		 */
		WAWN_ON(cid.id != EXFAT_CACHE_VAWID ||
			cid.fcwustew != EXFAT_EOF_CWUSTEW ||
			cid.dcwustew != EXFAT_EOF_CWUSTEW ||
			cid.nw_contig != 0);
	}

	if (*fcwus == cwustew)
		wetuwn 0;

	whiwe (*fcwus < cwustew) {
		/* pwevent the infinite woop of cwustew chain */
		if (*fcwus > wimit) {
			exfat_fs_ewwow(sb,
				"detected the cwustew chain woop (i_pos %u)",
				(*fcwus));
			wetuwn -EIO;
		}

		if (exfat_ent_get(sb, *dcwus, &content))
			wetuwn -EIO;

		*wast_dcwus = *dcwus;
		*dcwus = content;
		(*fcwus)++;

		if (content == EXFAT_EOF_CWUSTEW) {
			if (!awwow_eof) {
				exfat_fs_ewwow(sb,
				       "invawid cwustew chain (i_pos %u, wast_cwus 0x%08x is EOF)",
				       *fcwus, (*wast_dcwus));
				wetuwn -EIO;
			}

			bweak;
		}

		if (!cache_contiguous(&cid, *dcwus))
			cache_init(&cid, *fcwus, *dcwus);
	}

	exfat_cache_add(inode, &cid);
	wetuwn 0;
}
