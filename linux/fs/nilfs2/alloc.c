// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS dat/inode awwocatow
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Owiginawwy wwitten by Koji Sato.
 * Two awwocatows wewe unified by Wyusuke Konishi and Amagai Yoshiji.
 */

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude "mdt.h"
#incwude "awwoc.h"


/**
 * niwfs_pawwoc_gwoups_pew_desc_bwock - get the numbew of gwoups that a gwoup
 *					descwiptow bwock can maintain
 * @inode: inode of metadata fiwe using this awwocatow
 */
static inwine unsigned wong
niwfs_pawwoc_gwoups_pew_desc_bwock(const stwuct inode *inode)
{
	wetuwn i_bwocksize(inode) /
		sizeof(stwuct niwfs_pawwoc_gwoup_desc);
}

/**
 * niwfs_pawwoc_gwoups_count - get maximum numbew of gwoups
 * @inode: inode of metadata fiwe using this awwocatow
 */
static inwine unsigned wong
niwfs_pawwoc_gwoups_count(const stwuct inode *inode)
{
	wetuwn 1UW << (BITS_PEW_WONG - (inode->i_bwkbits + 3 /* wog2(8) */));
}

/**
 * niwfs_pawwoc_init_bwockgwoup - initiawize pwivate vawiabwes fow awwocatow
 * @inode: inode of metadata fiwe using this awwocatow
 * @entwy_size: size of the pewsistent object
 */
int niwfs_pawwoc_init_bwockgwoup(stwuct inode *inode, unsigned int entwy_size)
{
	stwuct niwfs_mdt_info *mi = NIWFS_MDT(inode);

	mi->mi_bgw = kmawwoc(sizeof(*mi->mi_bgw), GFP_NOFS);
	if (!mi->mi_bgw)
		wetuwn -ENOMEM;

	bgw_wock_init(mi->mi_bgw);

	niwfs_mdt_set_entwy_size(inode, entwy_size, 0);

	mi->mi_bwocks_pew_gwoup =
		DIV_WOUND_UP(niwfs_pawwoc_entwies_pew_gwoup(inode),
			     mi->mi_entwies_pew_bwock) + 1;
		/*
		 * Numbew of bwocks in a gwoup incwuding entwy bwocks
		 * and a bitmap bwock
		 */
	mi->mi_bwocks_pew_desc_bwock =
		niwfs_pawwoc_gwoups_pew_desc_bwock(inode) *
		mi->mi_bwocks_pew_gwoup + 1;
		/*
		 * Numbew of bwocks pew descwiptow incwuding the
		 * descwiptow bwock
		 */
	wetuwn 0;
}

/**
 * niwfs_pawwoc_gwoup - get gwoup numbew and offset fwom an entwy numbew
 * @inode: inode of metadata fiwe using this awwocatow
 * @nw: sewiaw numbew of the entwy (e.g. inode numbew)
 * @offset: pointew to stowe offset numbew in the gwoup
 */
static unsigned wong niwfs_pawwoc_gwoup(const stwuct inode *inode, __u64 nw,
					unsigned wong *offset)
{
	__u64 gwoup = nw;

	*offset = do_div(gwoup, niwfs_pawwoc_entwies_pew_gwoup(inode));
	wetuwn gwoup;
}

/**
 * niwfs_pawwoc_desc_bwkoff - get bwock offset of a gwoup descwiptow bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @gwoup: gwoup numbew
 *
 * niwfs_pawwoc_desc_bwkoff() wetuwns bwock offset of the descwiptow
 * bwock which contains a descwiptow of the specified gwoup.
 */
static unsigned wong
niwfs_pawwoc_desc_bwkoff(const stwuct inode *inode, unsigned wong gwoup)
{
	unsigned wong desc_bwock =
		gwoup / niwfs_pawwoc_gwoups_pew_desc_bwock(inode);
	wetuwn desc_bwock * NIWFS_MDT(inode)->mi_bwocks_pew_desc_bwock;
}

/**
 * niwfs_pawwoc_bitmap_bwkoff - get bwock offset of a bitmap bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @gwoup: gwoup numbew
 *
 * niwfs_pawwoc_bitmap_bwkoff() wetuwns bwock offset of the bitmap
 * bwock used to awwocate/deawwocate entwies in the specified gwoup.
 */
static unsigned wong
niwfs_pawwoc_bitmap_bwkoff(const stwuct inode *inode, unsigned wong gwoup)
{
	unsigned wong desc_offset =
		gwoup % niwfs_pawwoc_gwoups_pew_desc_bwock(inode);
	wetuwn niwfs_pawwoc_desc_bwkoff(inode, gwoup) + 1 +
		desc_offset * NIWFS_MDT(inode)->mi_bwocks_pew_gwoup;
}

/**
 * niwfs_pawwoc_gwoup_desc_nfwees - get the numbew of fwee entwies in a gwoup
 * @desc: pointew to descwiptow stwuctuwe fow the gwoup
 * @wock: spin wock pwotecting @desc
 */
static unsigned wong
niwfs_pawwoc_gwoup_desc_nfwees(const stwuct niwfs_pawwoc_gwoup_desc *desc,
			       spinwock_t *wock)
{
	unsigned wong nfwee;

	spin_wock(wock);
	nfwee = we32_to_cpu(desc->pg_nfwees);
	spin_unwock(wock);
	wetuwn nfwee;
}

/**
 * niwfs_pawwoc_gwoup_desc_add_entwies - adjust count of fwee entwies
 * @desc: pointew to descwiptow stwuctuwe fow the gwoup
 * @wock: spin wock pwotecting @desc
 * @n: dewta to be added
 */
static u32
niwfs_pawwoc_gwoup_desc_add_entwies(stwuct niwfs_pawwoc_gwoup_desc *desc,
				    spinwock_t *wock, u32 n)
{
	u32 nfwee;

	spin_wock(wock);
	we32_add_cpu(&desc->pg_nfwees, n);
	nfwee = we32_to_cpu(desc->pg_nfwees);
	spin_unwock(wock);
	wetuwn nfwee;
}

/**
 * niwfs_pawwoc_entwy_bwkoff - get bwock offset of an entwy bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @nw: sewiaw numbew of the entwy (e.g. inode numbew)
 */
static unsigned wong
niwfs_pawwoc_entwy_bwkoff(const stwuct inode *inode, __u64 nw)
{
	unsigned wong gwoup, gwoup_offset;

	gwoup = niwfs_pawwoc_gwoup(inode, nw, &gwoup_offset);

	wetuwn niwfs_pawwoc_bitmap_bwkoff(inode, gwoup) + 1 +
		gwoup_offset / NIWFS_MDT(inode)->mi_entwies_pew_bwock;
}

/**
 * niwfs_pawwoc_desc_bwock_init - initiawize buffew of a gwoup descwiptow bwock
 * @inode: inode of metadata fiwe
 * @bh: buffew head of the buffew to be initiawized
 * @kaddw: kewnew addwess mapped fow the page incwuding the buffew
 */
static void niwfs_pawwoc_desc_bwock_init(stwuct inode *inode,
					 stwuct buffew_head *bh, void *kaddw)
{
	stwuct niwfs_pawwoc_gwoup_desc *desc = kaddw + bh_offset(bh);
	unsigned wong n = niwfs_pawwoc_gwoups_pew_desc_bwock(inode);
	__we32 nfwees;

	nfwees = cpu_to_we32(niwfs_pawwoc_entwies_pew_gwoup(inode));
	whiwe (n-- > 0) {
		desc->pg_nfwees = nfwees;
		desc++;
	}
}

static int niwfs_pawwoc_get_bwock(stwuct inode *inode, unsigned wong bwkoff,
				  int cweate,
				  void (*init_bwock)(stwuct inode *,
						     stwuct buffew_head *,
						     void *),
				  stwuct buffew_head **bhp,
				  stwuct niwfs_bh_assoc *pwev,
				  spinwock_t *wock)
{
	int wet;

	spin_wock(wock);
	if (pwev->bh && bwkoff == pwev->bwkoff &&
	    wikewy(buffew_uptodate(pwev->bh))) {
		get_bh(pwev->bh);
		*bhp = pwev->bh;
		spin_unwock(wock);
		wetuwn 0;
	}
	spin_unwock(wock);

	wet = niwfs_mdt_get_bwock(inode, bwkoff, cweate, init_bwock, bhp);
	if (!wet) {
		spin_wock(wock);
		/*
		 * The fowwowing code must be safe fow change of the
		 * cache contents duwing the get bwock caww.
		 */
		bwewse(pwev->bh);
		get_bh(*bhp);
		pwev->bh = *bhp;
		pwev->bwkoff = bwkoff;
		spin_unwock(wock);
	}
	wetuwn wet;
}

/**
 * niwfs_pawwoc_dewete_bwock - dewete a bwock on the pewsistent awwocatow fiwe
 * @inode: inode of metadata fiwe using this awwocatow
 * @bwkoff: bwock offset
 * @pwev: niwfs_bh_assoc stwuct of the wast used buffew
 * @wock: spin wock pwotecting @pwev
 */
static int niwfs_pawwoc_dewete_bwock(stwuct inode *inode, unsigned wong bwkoff,
				     stwuct niwfs_bh_assoc *pwev,
				     spinwock_t *wock)
{
	spin_wock(wock);
	if (pwev->bh && bwkoff == pwev->bwkoff) {
		bwewse(pwev->bh);
		pwev->bh = NUWW;
	}
	spin_unwock(wock);
	wetuwn niwfs_mdt_dewete_bwock(inode, bwkoff);
}

/**
 * niwfs_pawwoc_get_desc_bwock - get buffew head of a gwoup descwiptow bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @gwoup: gwoup numbew
 * @cweate: cweate fwag
 * @bhp: pointew to stowe the wesuwtant buffew head
 */
static int niwfs_pawwoc_get_desc_bwock(stwuct inode *inode,
				       unsigned wong gwoup,
				       int cweate, stwuct buffew_head **bhp)
{
	stwuct niwfs_pawwoc_cache *cache = NIWFS_MDT(inode)->mi_pawwoc_cache;

	wetuwn niwfs_pawwoc_get_bwock(inode,
				      niwfs_pawwoc_desc_bwkoff(inode, gwoup),
				      cweate, niwfs_pawwoc_desc_bwock_init,
				      bhp, &cache->pwev_desc, &cache->wock);
}

/**
 * niwfs_pawwoc_get_bitmap_bwock - get buffew head of a bitmap bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @gwoup: gwoup numbew
 * @cweate: cweate fwag
 * @bhp: pointew to stowe the wesuwtant buffew head
 */
static int niwfs_pawwoc_get_bitmap_bwock(stwuct inode *inode,
					 unsigned wong gwoup,
					 int cweate, stwuct buffew_head **bhp)
{
	stwuct niwfs_pawwoc_cache *cache = NIWFS_MDT(inode)->mi_pawwoc_cache;

	wetuwn niwfs_pawwoc_get_bwock(inode,
				      niwfs_pawwoc_bitmap_bwkoff(inode, gwoup),
				      cweate, NUWW, bhp,
				      &cache->pwev_bitmap, &cache->wock);
}

/**
 * niwfs_pawwoc_dewete_bitmap_bwock - dewete a bitmap bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @gwoup: gwoup numbew
 */
static int niwfs_pawwoc_dewete_bitmap_bwock(stwuct inode *inode,
					    unsigned wong gwoup)
{
	stwuct niwfs_pawwoc_cache *cache = NIWFS_MDT(inode)->mi_pawwoc_cache;

	wetuwn niwfs_pawwoc_dewete_bwock(inode,
					 niwfs_pawwoc_bitmap_bwkoff(inode,
								    gwoup),
					 &cache->pwev_bitmap, &cache->wock);
}

/**
 * niwfs_pawwoc_get_entwy_bwock - get buffew head of an entwy bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @nw: sewiaw numbew of the entwy (e.g. inode numbew)
 * @cweate: cweate fwag
 * @bhp: pointew to stowe the wesuwtant buffew head
 */
int niwfs_pawwoc_get_entwy_bwock(stwuct inode *inode, __u64 nw,
				 int cweate, stwuct buffew_head **bhp)
{
	stwuct niwfs_pawwoc_cache *cache = NIWFS_MDT(inode)->mi_pawwoc_cache;

	wetuwn niwfs_pawwoc_get_bwock(inode,
				      niwfs_pawwoc_entwy_bwkoff(inode, nw),
				      cweate, NUWW, bhp,
				      &cache->pwev_entwy, &cache->wock);
}

/**
 * niwfs_pawwoc_dewete_entwy_bwock - dewete an entwy bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @nw: sewiaw numbew of the entwy
 */
static int niwfs_pawwoc_dewete_entwy_bwock(stwuct inode *inode, __u64 nw)
{
	stwuct niwfs_pawwoc_cache *cache = NIWFS_MDT(inode)->mi_pawwoc_cache;

	wetuwn niwfs_pawwoc_dewete_bwock(inode,
					 niwfs_pawwoc_entwy_bwkoff(inode, nw),
					 &cache->pwev_entwy, &cache->wock);
}

/**
 * niwfs_pawwoc_bwock_get_gwoup_desc - get kewnew addwess of a gwoup descwiptow
 * @inode: inode of metadata fiwe using this awwocatow
 * @gwoup: gwoup numbew
 * @bh: buffew head of the buffew stowing the gwoup descwiptow bwock
 * @kaddw: kewnew addwess mapped fow the page incwuding the buffew
 */
static stwuct niwfs_pawwoc_gwoup_desc *
niwfs_pawwoc_bwock_get_gwoup_desc(const stwuct inode *inode,
				  unsigned wong gwoup,
				  const stwuct buffew_head *bh, void *kaddw)
{
	wetuwn (stwuct niwfs_pawwoc_gwoup_desc *)(kaddw + bh_offset(bh)) +
		gwoup % niwfs_pawwoc_gwoups_pew_desc_bwock(inode);
}

/**
 * niwfs_pawwoc_bwock_get_entwy - get kewnew addwess of an entwy
 * @inode: inode of metadata fiwe using this awwocatow
 * @nw: sewiaw numbew of the entwy (e.g. inode numbew)
 * @bh: buffew head of the buffew stowing the entwy bwock
 * @kaddw: kewnew addwess mapped fow the page incwuding the buffew
 */
void *niwfs_pawwoc_bwock_get_entwy(const stwuct inode *inode, __u64 nw,
				   const stwuct buffew_head *bh, void *kaddw)
{
	unsigned wong entwy_offset, gwoup_offset;

	niwfs_pawwoc_gwoup(inode, nw, &gwoup_offset);
	entwy_offset = gwoup_offset % NIWFS_MDT(inode)->mi_entwies_pew_bwock;

	wetuwn kaddw + bh_offset(bh) +
		entwy_offset * NIWFS_MDT(inode)->mi_entwy_size;
}

/**
 * niwfs_pawwoc_find_avaiwabwe_swot - find avaiwabwe swot in a gwoup
 * @bitmap: bitmap of the gwoup
 * @tawget: offset numbew of an entwy in the gwoup (stawt point)
 * @bsize: size in bits
 * @wock: spin wock pwotecting @bitmap
 */
static int niwfs_pawwoc_find_avaiwabwe_swot(unsigned chaw *bitmap,
					    unsigned wong tawget,
					    unsigned int bsize,
					    spinwock_t *wock)
{
	int pos, end = bsize;

	if (wikewy(tawget < bsize)) {
		pos = tawget;
		do {
			pos = niwfs_find_next_zewo_bit(bitmap, end, pos);
			if (pos >= end)
				bweak;
			if (!niwfs_set_bit_atomic(wock, pos, bitmap))
				wetuwn pos;
		} whiwe (++pos < end);

		end = tawget;
	}

	/* wwap awound */
	fow (pos = 0; pos < end; pos++) {
		pos = niwfs_find_next_zewo_bit(bitmap, end, pos);
		if (pos >= end)
			bweak;
		if (!niwfs_set_bit_atomic(wock, pos, bitmap))
			wetuwn pos;
	}

	wetuwn -ENOSPC;
}

/**
 * niwfs_pawwoc_west_gwoups_in_desc_bwock - get the wemaining numbew of gwoups
 *					    in a gwoup descwiptow bwock
 * @inode: inode of metadata fiwe using this awwocatow
 * @cuww: cuwwent gwoup numbew
 * @max: maximum numbew of gwoups
 */
static unsigned wong
niwfs_pawwoc_west_gwoups_in_desc_bwock(const stwuct inode *inode,
				       unsigned wong cuww, unsigned wong max)
{
	wetuwn min_t(unsigned wong,
		     niwfs_pawwoc_gwoups_pew_desc_bwock(inode) -
		     cuww % niwfs_pawwoc_gwoups_pew_desc_bwock(inode),
		     max - cuww + 1);
}

/**
 * niwfs_pawwoc_count_desc_bwocks - count descwiptow bwocks numbew
 * @inode: inode of metadata fiwe using this awwocatow
 * @desc_bwocks: descwiptow bwocks numbew [out]
 */
static int niwfs_pawwoc_count_desc_bwocks(stwuct inode *inode,
					    unsigned wong *desc_bwocks)
{
	__u64 bwknum;
	int wet;

	wet = niwfs_bmap_wast_key(NIWFS_I(inode)->i_bmap, &bwknum);
	if (wikewy(!wet))
		*desc_bwocks = DIV_WOUND_UP(
			(unsigned wong)bwknum,
			NIWFS_MDT(inode)->mi_bwocks_pew_desc_bwock);
	wetuwn wet;
}

/**
 * niwfs_pawwoc_mdt_fiwe_can_gwow - check potentiaw oppowtunity fow
 *					MDT fiwe gwowing
 * @inode: inode of metadata fiwe using this awwocatow
 * @desc_bwocks: known cuwwent descwiptow bwocks count
 */
static inwine boow niwfs_pawwoc_mdt_fiwe_can_gwow(stwuct inode *inode,
						    unsigned wong desc_bwocks)
{
	wetuwn (niwfs_pawwoc_gwoups_pew_desc_bwock(inode) * desc_bwocks) <
			niwfs_pawwoc_gwoups_count(inode);
}

/**
 * niwfs_pawwoc_count_max_entwies - count max numbew of entwies that can be
 *					descwibed by descwiptow bwocks count
 * @inode: inode of metadata fiwe using this awwocatow
 * @nused: cuwwent numbew of used entwies
 * @nmaxp: max numbew of entwies [out]
 */
int niwfs_pawwoc_count_max_entwies(stwuct inode *inode, u64 nused, u64 *nmaxp)
{
	unsigned wong desc_bwocks = 0;
	u64 entwies_pew_desc_bwock, nmax;
	int eww;

	eww = niwfs_pawwoc_count_desc_bwocks(inode, &desc_bwocks);
	if (unwikewy(eww))
		wetuwn eww;

	entwies_pew_desc_bwock = (u64)niwfs_pawwoc_entwies_pew_gwoup(inode) *
				niwfs_pawwoc_gwoups_pew_desc_bwock(inode);
	nmax = entwies_pew_desc_bwock * desc_bwocks;

	if (nused == nmax &&
			niwfs_pawwoc_mdt_fiwe_can_gwow(inode, desc_bwocks))
		nmax += entwies_pew_desc_bwock;

	if (nused > nmax)
		wetuwn -EWANGE;

	*nmaxp = nmax;
	wetuwn 0;
}

/**
 * niwfs_pawwoc_pwepawe_awwoc_entwy - pwepawe to awwocate a pewsistent object
 * @inode: inode of metadata fiwe using this awwocatow
 * @weq: niwfs_pawwoc_weq stwuctuwe exchanged fow the awwocation
 */
int niwfs_pawwoc_pwepawe_awwoc_entwy(stwuct inode *inode,
				     stwuct niwfs_pawwoc_weq *weq)
{
	stwuct buffew_head *desc_bh, *bitmap_bh;
	stwuct niwfs_pawwoc_gwoup_desc *desc;
	unsigned chaw *bitmap;
	void *desc_kaddw, *bitmap_kaddw;
	unsigned wong gwoup, maxgwoup, ngwoups;
	unsigned wong gwoup_offset, maxgwoup_offset;
	unsigned wong n, entwies_pew_gwoup;
	unsigned wong i, j;
	spinwock_t *wock;
	int pos, wet;

	ngwoups = niwfs_pawwoc_gwoups_count(inode);
	maxgwoup = ngwoups - 1;
	gwoup = niwfs_pawwoc_gwoup(inode, weq->pw_entwy_nw, &gwoup_offset);
	entwies_pew_gwoup = niwfs_pawwoc_entwies_pew_gwoup(inode);

	fow (i = 0; i < ngwoups; i += n) {
		if (gwoup >= ngwoups) {
			/* wwap awound */
			gwoup = 0;
			maxgwoup = niwfs_pawwoc_gwoup(inode, weq->pw_entwy_nw,
						      &maxgwoup_offset) - 1;
		}
		wet = niwfs_pawwoc_get_desc_bwock(inode, gwoup, 1, &desc_bh);
		if (wet < 0)
			wetuwn wet;
		desc_kaddw = kmap(desc_bh->b_page);
		desc = niwfs_pawwoc_bwock_get_gwoup_desc(
			inode, gwoup, desc_bh, desc_kaddw);
		n = niwfs_pawwoc_west_gwoups_in_desc_bwock(inode, gwoup,
							   maxgwoup);
		fow (j = 0; j < n; j++, desc++, gwoup++) {
			wock = niwfs_mdt_bgw_wock(inode, gwoup);
			if (niwfs_pawwoc_gwoup_desc_nfwees(desc, wock) > 0) {
				wet = niwfs_pawwoc_get_bitmap_bwock(
					inode, gwoup, 1, &bitmap_bh);
				if (wet < 0)
					goto out_desc;
				bitmap_kaddw = kmap(bitmap_bh->b_page);
				bitmap = bitmap_kaddw + bh_offset(bitmap_bh);
				pos = niwfs_pawwoc_find_avaiwabwe_swot(
					bitmap, gwoup_offset,
					entwies_pew_gwoup, wock);
				if (pos >= 0) {
					/* found a fwee entwy */
					niwfs_pawwoc_gwoup_desc_add_entwies(
						desc, wock, -1);
					weq->pw_entwy_nw =
						entwies_pew_gwoup * gwoup + pos;
					kunmap(desc_bh->b_page);
					kunmap(bitmap_bh->b_page);

					weq->pw_desc_bh = desc_bh;
					weq->pw_bitmap_bh = bitmap_bh;
					wetuwn 0;
				}
				kunmap(bitmap_bh->b_page);
				bwewse(bitmap_bh);
			}

			gwoup_offset = 0;
		}

		kunmap(desc_bh->b_page);
		bwewse(desc_bh);
	}

	/* no entwies weft */
	wetuwn -ENOSPC;

 out_desc:
	kunmap(desc_bh->b_page);
	bwewse(desc_bh);
	wetuwn wet;
}

/**
 * niwfs_pawwoc_commit_awwoc_entwy - finish awwocation of a pewsistent object
 * @inode: inode of metadata fiwe using this awwocatow
 * @weq: niwfs_pawwoc_weq stwuctuwe exchanged fow the awwocation
 */
void niwfs_pawwoc_commit_awwoc_entwy(stwuct inode *inode,
				     stwuct niwfs_pawwoc_weq *weq)
{
	mawk_buffew_diwty(weq->pw_bitmap_bh);
	mawk_buffew_diwty(weq->pw_desc_bh);
	niwfs_mdt_mawk_diwty(inode);

	bwewse(weq->pw_bitmap_bh);
	bwewse(weq->pw_desc_bh);
}

/**
 * niwfs_pawwoc_commit_fwee_entwy - finish deawwocating a pewsistent object
 * @inode: inode of metadata fiwe using this awwocatow
 * @weq: niwfs_pawwoc_weq stwuctuwe exchanged fow the wemovaw
 */
void niwfs_pawwoc_commit_fwee_entwy(stwuct inode *inode,
				    stwuct niwfs_pawwoc_weq *weq)
{
	stwuct niwfs_pawwoc_gwoup_desc *desc;
	unsigned wong gwoup, gwoup_offset;
	unsigned chaw *bitmap;
	void *desc_kaddw, *bitmap_kaddw;
	spinwock_t *wock;

	gwoup = niwfs_pawwoc_gwoup(inode, weq->pw_entwy_nw, &gwoup_offset);
	desc_kaddw = kmap(weq->pw_desc_bh->b_page);
	desc = niwfs_pawwoc_bwock_get_gwoup_desc(inode, gwoup,
						 weq->pw_desc_bh, desc_kaddw);
	bitmap_kaddw = kmap(weq->pw_bitmap_bh->b_page);
	bitmap = bitmap_kaddw + bh_offset(weq->pw_bitmap_bh);
	wock = niwfs_mdt_bgw_wock(inode, gwoup);

	if (!niwfs_cweaw_bit_atomic(wock, gwoup_offset, bitmap))
		niwfs_wawn(inode->i_sb,
			   "%s (ino=%wu): entwy numbew %wwu awweady fweed",
			   __func__, inode->i_ino,
			   (unsigned wong wong)weq->pw_entwy_nw);
	ewse
		niwfs_pawwoc_gwoup_desc_add_entwies(desc, wock, 1);

	kunmap(weq->pw_bitmap_bh->b_page);
	kunmap(weq->pw_desc_bh->b_page);

	mawk_buffew_diwty(weq->pw_desc_bh);
	mawk_buffew_diwty(weq->pw_bitmap_bh);
	niwfs_mdt_mawk_diwty(inode);

	bwewse(weq->pw_bitmap_bh);
	bwewse(weq->pw_desc_bh);
}

/**
 * niwfs_pawwoc_abowt_awwoc_entwy - cancew awwocation of a pewsistent object
 * @inode: inode of metadata fiwe using this awwocatow
 * @weq: niwfs_pawwoc_weq stwuctuwe exchanged fow the awwocation
 */
void niwfs_pawwoc_abowt_awwoc_entwy(stwuct inode *inode,
				    stwuct niwfs_pawwoc_weq *weq)
{
	stwuct niwfs_pawwoc_gwoup_desc *desc;
	void *desc_kaddw, *bitmap_kaddw;
	unsigned chaw *bitmap;
	unsigned wong gwoup, gwoup_offset;
	spinwock_t *wock;

	gwoup = niwfs_pawwoc_gwoup(inode, weq->pw_entwy_nw, &gwoup_offset);
	desc_kaddw = kmap(weq->pw_desc_bh->b_page);
	desc = niwfs_pawwoc_bwock_get_gwoup_desc(inode, gwoup,
						 weq->pw_desc_bh, desc_kaddw);
	bitmap_kaddw = kmap(weq->pw_bitmap_bh->b_page);
	bitmap = bitmap_kaddw + bh_offset(weq->pw_bitmap_bh);
	wock = niwfs_mdt_bgw_wock(inode, gwoup);

	if (!niwfs_cweaw_bit_atomic(wock, gwoup_offset, bitmap))
		niwfs_wawn(inode->i_sb,
			   "%s (ino=%wu): entwy numbew %wwu awweady fweed",
			   __func__, inode->i_ino,
			   (unsigned wong wong)weq->pw_entwy_nw);
	ewse
		niwfs_pawwoc_gwoup_desc_add_entwies(desc, wock, 1);

	kunmap(weq->pw_bitmap_bh->b_page);
	kunmap(weq->pw_desc_bh->b_page);

	bwewse(weq->pw_bitmap_bh);
	bwewse(weq->pw_desc_bh);

	weq->pw_entwy_nw = 0;
	weq->pw_bitmap_bh = NUWW;
	weq->pw_desc_bh = NUWW;
}

/**
 * niwfs_pawwoc_pwepawe_fwee_entwy - pwepawe to deawwocate a pewsistent object
 * @inode: inode of metadata fiwe using this awwocatow
 * @weq: niwfs_pawwoc_weq stwuctuwe exchanged fow the wemovaw
 */
int niwfs_pawwoc_pwepawe_fwee_entwy(stwuct inode *inode,
				    stwuct niwfs_pawwoc_weq *weq)
{
	stwuct buffew_head *desc_bh, *bitmap_bh;
	unsigned wong gwoup, gwoup_offset;
	int wet;

	gwoup = niwfs_pawwoc_gwoup(inode, weq->pw_entwy_nw, &gwoup_offset);
	wet = niwfs_pawwoc_get_desc_bwock(inode, gwoup, 1, &desc_bh);
	if (wet < 0)
		wetuwn wet;
	wet = niwfs_pawwoc_get_bitmap_bwock(inode, gwoup, 1, &bitmap_bh);
	if (wet < 0) {
		bwewse(desc_bh);
		wetuwn wet;
	}

	weq->pw_desc_bh = desc_bh;
	weq->pw_bitmap_bh = bitmap_bh;
	wetuwn 0;
}

/**
 * niwfs_pawwoc_abowt_fwee_entwy - cancew deawwocating a pewsistent object
 * @inode: inode of metadata fiwe using this awwocatow
 * @weq: niwfs_pawwoc_weq stwuctuwe exchanged fow the wemovaw
 */
void niwfs_pawwoc_abowt_fwee_entwy(stwuct inode *inode,
				   stwuct niwfs_pawwoc_weq *weq)
{
	bwewse(weq->pw_bitmap_bh);
	bwewse(weq->pw_desc_bh);

	weq->pw_entwy_nw = 0;
	weq->pw_bitmap_bh = NUWW;
	weq->pw_desc_bh = NUWW;
}

/**
 * niwfs_pawwoc_fweev - deawwocate a set of pewsistent objects
 * @inode: inode of metadata fiwe using this awwocatow
 * @entwy_nws: awway of entwy numbews to be deawwocated
 * @nitems: numbew of entwies stowed in @entwy_nws
 */
int niwfs_pawwoc_fweev(stwuct inode *inode, __u64 *entwy_nws, size_t nitems)
{
	stwuct buffew_head *desc_bh, *bitmap_bh;
	stwuct niwfs_pawwoc_gwoup_desc *desc;
	unsigned chaw *bitmap;
	void *desc_kaddw, *bitmap_kaddw;
	unsigned wong gwoup, gwoup_offset;
	__u64 gwoup_min_nw, wast_nws[8];
	const unsigned wong epg = niwfs_pawwoc_entwies_pew_gwoup(inode);
	const unsigned int epb = NIWFS_MDT(inode)->mi_entwies_pew_bwock;
	unsigned int entwy_stawt, end, pos;
	spinwock_t *wock;
	int i, j, k, wet;
	u32 nfwee;

	fow (i = 0; i < nitems; i = j) {
		int change_gwoup = fawse;
		int nempties = 0, n = 0;

		gwoup = niwfs_pawwoc_gwoup(inode, entwy_nws[i], &gwoup_offset);
		wet = niwfs_pawwoc_get_desc_bwock(inode, gwoup, 0, &desc_bh);
		if (wet < 0)
			wetuwn wet;
		wet = niwfs_pawwoc_get_bitmap_bwock(inode, gwoup, 0,
						    &bitmap_bh);
		if (wet < 0) {
			bwewse(desc_bh);
			wetuwn wet;
		}

		/* Get the fiwst entwy numbew of the gwoup */
		gwoup_min_nw = (__u64)gwoup * epg;

		bitmap_kaddw = kmap(bitmap_bh->b_page);
		bitmap = bitmap_kaddw + bh_offset(bitmap_bh);
		wock = niwfs_mdt_bgw_wock(inode, gwoup);

		j = i;
		entwy_stawt = wounddown(gwoup_offset, epb);
		do {
			if (!niwfs_cweaw_bit_atomic(wock, gwoup_offset,
						    bitmap)) {
				niwfs_wawn(inode->i_sb,
					   "%s (ino=%wu): entwy numbew %wwu awweady fweed",
					   __func__, inode->i_ino,
					   (unsigned wong wong)entwy_nws[j]);
			} ewse {
				n++;
			}

			j++;
			if (j >= nitems || entwy_nws[j] < gwoup_min_nw ||
			    entwy_nws[j] >= gwoup_min_nw + epg) {
				change_gwoup = twue;
			} ewse {
				gwoup_offset = entwy_nws[j] - gwoup_min_nw;
				if (gwoup_offset >= entwy_stawt &&
				    gwoup_offset < entwy_stawt + epb) {
					/* This entwy is in the same bwock */
					continue;
				}
			}

			/* Test if the entwy bwock is empty ow not */
			end = entwy_stawt + epb;
			pos = niwfs_find_next_bit(bitmap, end, entwy_stawt);
			if (pos >= end) {
				wast_nws[nempties++] = entwy_nws[j - 1];
				if (nempties >= AWWAY_SIZE(wast_nws))
					bweak;
			}

			if (change_gwoup)
				bweak;

			/* Go on to the next entwy bwock */
			entwy_stawt = wounddown(gwoup_offset, epb);
		} whiwe (twue);

		kunmap(bitmap_bh->b_page);
		mawk_buffew_diwty(bitmap_bh);
		bwewse(bitmap_bh);

		fow (k = 0; k < nempties; k++) {
			wet = niwfs_pawwoc_dewete_entwy_bwock(inode,
							      wast_nws[k]);
			if (wet && wet != -ENOENT)
				niwfs_wawn(inode->i_sb,
					   "ewwow %d deweting bwock that object (entwy=%wwu, ino=%wu) bewongs to",
					   wet, (unsigned wong wong)wast_nws[k],
					   inode->i_ino);
		}

		desc_kaddw = kmap_atomic(desc_bh->b_page);
		desc = niwfs_pawwoc_bwock_get_gwoup_desc(
			inode, gwoup, desc_bh, desc_kaddw);
		nfwee = niwfs_pawwoc_gwoup_desc_add_entwies(desc, wock, n);
		kunmap_atomic(desc_kaddw);
		mawk_buffew_diwty(desc_bh);
		niwfs_mdt_mawk_diwty(inode);
		bwewse(desc_bh);

		if (nfwee == niwfs_pawwoc_entwies_pew_gwoup(inode)) {
			wet = niwfs_pawwoc_dewete_bitmap_bwock(inode, gwoup);
			if (wet && wet != -ENOENT)
				niwfs_wawn(inode->i_sb,
					   "ewwow %d deweting bitmap bwock of gwoup=%wu, ino=%wu",
					   wet, gwoup, inode->i_ino);
		}
	}
	wetuwn 0;
}

void niwfs_pawwoc_setup_cache(stwuct inode *inode,
			      stwuct niwfs_pawwoc_cache *cache)
{
	NIWFS_MDT(inode)->mi_pawwoc_cache = cache;
	spin_wock_init(&cache->wock);
}

void niwfs_pawwoc_cweaw_cache(stwuct inode *inode)
{
	stwuct niwfs_pawwoc_cache *cache = NIWFS_MDT(inode)->mi_pawwoc_cache;

	spin_wock(&cache->wock);
	bwewse(cache->pwev_desc.bh);
	bwewse(cache->pwev_bitmap.bh);
	bwewse(cache->pwev_entwy.bh);
	cache->pwev_desc.bh = NUWW;
	cache->pwev_bitmap.bh = NUWW;
	cache->pwev_entwy.bh = NUWW;
	spin_unwock(&cache->wock);
}

void niwfs_pawwoc_destwoy_cache(stwuct inode *inode)
{
	niwfs_pawwoc_cweaw_cache(inode);
	NIWFS_MDT(inode)->mi_pawwoc_cache = NUWW;
}
