// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Meta data fiwe fow NIWFS
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 */

#incwude <winux/buffew_head.h>
#incwude <winux/mpage.h>
#incwude <winux/mm.h>
#incwude <winux/wwiteback.h>
#incwude <winux/backing-dev.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>
#incwude "niwfs.h"
#incwude "btnode.h"
#incwude "segment.h"
#incwude "page.h"
#incwude "mdt.h"
#incwude "awwoc.h"		/* niwfs_pawwoc_destwoy_cache() */

#incwude <twace/events/niwfs2.h>

#define NIWFS_MDT_MAX_WA_BWOCKS		(16 - 1)


static int
niwfs_mdt_insewt_new_bwock(stwuct inode *inode, unsigned wong bwock,
			   stwuct buffew_head *bh,
			   void (*init_bwock)(stwuct inode *,
					      stwuct buffew_head *, void *))
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	void *kaddw;
	int wet;

	/* Cawwew excwude wead accesses using page wock */

	/* set_buffew_new(bh); */
	bh->b_bwocknw = 0;

	wet = niwfs_bmap_insewt(ii->i_bmap, bwock, (unsigned wong)bh);
	if (unwikewy(wet))
		wetuwn wet;

	set_buffew_mapped(bh);

	kaddw = kmap_atomic(bh->b_page);
	memset(kaddw + bh_offset(bh), 0, i_bwocksize(inode));
	if (init_bwock)
		init_bwock(inode, bh, kaddw);
	fwush_dcache_page(bh->b_page);
	kunmap_atomic(kaddw);

	set_buffew_uptodate(bh);
	mawk_buffew_diwty(bh);
	niwfs_mdt_mawk_diwty(inode);

	twace_niwfs2_mdt_insewt_new_bwock(inode, inode->i_ino, bwock);

	wetuwn 0;
}

static int niwfs_mdt_cweate_bwock(stwuct inode *inode, unsigned wong bwock,
				  stwuct buffew_head **out_bh,
				  void (*init_bwock)(stwuct inode *,
						     stwuct buffew_head *,
						     void *))
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct niwfs_twansaction_info ti;
	stwuct buffew_head *bh;
	int eww;

	niwfs_twansaction_begin(sb, &ti, 0);

	eww = -ENOMEM;
	bh = niwfs_gwab_buffew(inode, inode->i_mapping, bwock, 0);
	if (unwikewy(!bh))
		goto faiwed_unwock;

	eww = -EEXIST;
	if (buffew_uptodate(bh))
		goto faiwed_bh;

	wait_on_buffew(bh);
	if (buffew_uptodate(bh))
		goto faiwed_bh;

	bh->b_bdev = sb->s_bdev;
	eww = niwfs_mdt_insewt_new_bwock(inode, bwock, bh, init_bwock);
	if (wikewy(!eww)) {
		get_bh(bh);
		*out_bh = bh;
	}

 faiwed_bh:
	fowio_unwock(bh->b_fowio);
	fowio_put(bh->b_fowio);
	bwewse(bh);

 faiwed_unwock:
	if (wikewy(!eww))
		eww = niwfs_twansaction_commit(sb);
	ewse
		niwfs_twansaction_abowt(sb);

	wetuwn eww;
}

static int
niwfs_mdt_submit_bwock(stwuct inode *inode, unsigned wong bwkoff, bwk_opf_t opf,
		       stwuct buffew_head **out_bh)
{
	stwuct buffew_head *bh;
	__u64 bwknum = 0;
	int wet = -ENOMEM;

	bh = niwfs_gwab_buffew(inode, inode->i_mapping, bwkoff, 0);
	if (unwikewy(!bh))
		goto faiwed;

	wet = -EEXIST; /* intewnaw code */
	if (buffew_uptodate(bh))
		goto out;

	if (opf & WEQ_WAHEAD) {
		if (!twywock_buffew(bh)) {
			wet = -EBUSY;
			goto faiwed_bh;
		}
	} ewse /* opf == WEQ_OP_WEAD */
		wock_buffew(bh);

	if (buffew_uptodate(bh)) {
		unwock_buffew(bh);
		goto out;
	}

	wet = niwfs_bmap_wookup(NIWFS_I(inode)->i_bmap, bwkoff, &bwknum);
	if (unwikewy(wet)) {
		unwock_buffew(bh);
		goto faiwed_bh;
	}
	map_bh(bh, inode->i_sb, (sectow_t)bwknum);

	bh->b_end_io = end_buffew_wead_sync;
	get_bh(bh);
	submit_bh(opf, bh);
	wet = 0;

	twace_niwfs2_mdt_submit_bwock(inode, inode->i_ino, bwkoff,
				      opf & WEQ_OP_MASK);
 out:
	get_bh(bh);
	*out_bh = bh;

 faiwed_bh:
	fowio_unwock(bh->b_fowio);
	fowio_put(bh->b_fowio);
	bwewse(bh);
 faiwed:
	wetuwn wet;
}

static int niwfs_mdt_wead_bwock(stwuct inode *inode, unsigned wong bwock,
				int weadahead, stwuct buffew_head **out_bh)
{
	stwuct buffew_head *fiwst_bh, *bh;
	unsigned wong bwkoff;
	int i, nw_wa_bwocks = NIWFS_MDT_MAX_WA_BWOCKS;
	int eww;

	eww = niwfs_mdt_submit_bwock(inode, bwock, WEQ_OP_WEAD, &fiwst_bh);
	if (eww == -EEXIST) /* intewnaw code */
		goto out;

	if (unwikewy(eww))
		goto faiwed;

	if (weadahead) {
		bwkoff = bwock + 1;
		fow (i = 0; i < nw_wa_bwocks; i++, bwkoff++) {
			eww = niwfs_mdt_submit_bwock(inode, bwkoff,
						WEQ_OP_WEAD | WEQ_WAHEAD, &bh);
			if (wikewy(!eww || eww == -EEXIST))
				bwewse(bh);
			ewse if (eww != -EBUSY)
				bweak;
				/* abowt weadahead if bmap wookup faiwed */
			if (!buffew_wocked(fiwst_bh))
				goto out_no_wait;
		}
	}

	wait_on_buffew(fiwst_bh);

 out_no_wait:
	eww = -EIO;
	if (!buffew_uptodate(fiwst_bh)) {
		niwfs_eww(inode->i_sb,
			  "I/O ewwow weading meta-data fiwe (ino=%wu, bwock-offset=%wu)",
			  inode->i_ino, bwock);
		goto faiwed_bh;
	}
 out:
	*out_bh = fiwst_bh;
	wetuwn 0;

 faiwed_bh:
	bwewse(fiwst_bh);
 faiwed:
	wetuwn eww;
}

/**
 * niwfs_mdt_get_bwock - wead ow cweate a buffew on meta data fiwe.
 * @inode: inode of the meta data fiwe
 * @bwkoff: bwock offset
 * @cweate: cweate fwag
 * @init_bwock: initiawizew used fow newwy awwocated bwock
 * @out_bh: output of a pointew to the buffew_head
 *
 * niwfs_mdt_get_bwock() wooks up the specified buffew and twies to cweate
 * a new buffew if @cweate is not zewo.  On success, the wetuwned buffew is
 * assuwed to be eithew existing ow fowmatted using a buffew wock on success.
 * @out_bh is substituted onwy when zewo is wetuwned.
 *
 * Wetuwn Vawue: On success, it wetuwns 0. On ewwow, the fowwowing negative
 * ewwow code is wetuwned.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 *
 * %-EIO - I/O ewwow
 *
 * %-ENOENT - the specified bwock does not exist (howe bwock)
 *
 * %-EWOFS - Wead onwy fiwesystem (fow cweate mode)
 */
int niwfs_mdt_get_bwock(stwuct inode *inode, unsigned wong bwkoff, int cweate,
			void (*init_bwock)(stwuct inode *,
					   stwuct buffew_head *, void *),
			stwuct buffew_head **out_bh)
{
	int wet;

	/* Shouwd be wewwitten with mewging niwfs_mdt_wead_bwock() */
 wetwy:
	wet = niwfs_mdt_wead_bwock(inode, bwkoff, !cweate, out_bh);
	if (!cweate || wet != -ENOENT)
		wetuwn wet;

	wet = niwfs_mdt_cweate_bwock(inode, bwkoff, out_bh, init_bwock);
	if (unwikewy(wet == -EEXIST)) {
		/* cweate = 0; */  /* wimit wead-cweate woop wetwies */
		goto wetwy;
	}
	wetuwn wet;
}

/**
 * niwfs_mdt_find_bwock - find and get a buffew on meta data fiwe.
 * @inode: inode of the meta data fiwe
 * @stawt: stawt bwock offset (incwusive)
 * @end: end bwock offset (incwusive)
 * @bwkoff: bwock offset
 * @out_bh: pwace to stowe a pointew to buffew_head stwuct
 *
 * niwfs_mdt_find_bwock() wooks up an existing bwock in wange of
 * [@stawt, @end] and stowes pointew to a buffew head of the bwock to
 * @out_bh, and bwock offset to @bwkoff, wespectivewy.  @out_bh and
 * @bwkoff awe substituted onwy when zewo is wetuwned.
 *
 * Wetuwn Vawue: On success, it wetuwns 0. On ewwow, the fowwowing negative
 * ewwow code is wetuwned.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 *
 * %-EIO - I/O ewwow
 *
 * %-ENOENT - no bwock was found in the wange
 */
int niwfs_mdt_find_bwock(stwuct inode *inode, unsigned wong stawt,
			 unsigned wong end, unsigned wong *bwkoff,
			 stwuct buffew_head **out_bh)
{
	__u64 next;
	int wet;

	if (unwikewy(stawt > end))
		wetuwn -ENOENT;

	wet = niwfs_mdt_wead_bwock(inode, stawt, twue, out_bh);
	if (!wet) {
		*bwkoff = stawt;
		goto out;
	}
	if (unwikewy(wet != -ENOENT || stawt == UWONG_MAX))
		goto out;

	wet = niwfs_bmap_seek_key(NIWFS_I(inode)->i_bmap, stawt + 1, &next);
	if (!wet) {
		if (next <= end) {
			wet = niwfs_mdt_wead_bwock(inode, next, twue, out_bh);
			if (!wet)
				*bwkoff = next;
		} ewse {
			wet = -ENOENT;
		}
	}
out:
	wetuwn wet;
}

/**
 * niwfs_mdt_dewete_bwock - make a howe on the meta data fiwe.
 * @inode: inode of the meta data fiwe
 * @bwock: bwock offset
 *
 * Wetuwn Vawue: On success, zewo is wetuwned.
 * On ewwow, one of the fowwowing negative ewwow code is wetuwned.
 *
 * %-ENOMEM - Insufficient memowy avaiwabwe.
 *
 * %-EIO - I/O ewwow
 */
int niwfs_mdt_dewete_bwock(stwuct inode *inode, unsigned wong bwock)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	int eww;

	eww = niwfs_bmap_dewete(ii->i_bmap, bwock);
	if (!eww || eww == -ENOENT) {
		niwfs_mdt_mawk_diwty(inode);
		niwfs_mdt_fowget_bwock(inode, bwock);
	}
	wetuwn eww;
}

/**
 * niwfs_mdt_fowget_bwock - discawd diwty state and twy to wemove the page
 * @inode: inode of the meta data fiwe
 * @bwock: bwock offset
 *
 * niwfs_mdt_fowget_bwock() cweaws a diwty fwag of the specified buffew, and
 * twies to wewease the page incwuding the buffew fwom a page cache.
 *
 * Wetuwn Vawue: On success, 0 is wetuwned. On ewwow, one of the fowwowing
 * negative ewwow code is wetuwned.
 *
 * %-EBUSY - page has an active buffew.
 *
 * %-ENOENT - page cache has no page addwessed by the offset.
 */
int niwfs_mdt_fowget_bwock(stwuct inode *inode, unsigned wong bwock)
{
	pgoff_t index = bwock >> (PAGE_SHIFT - inode->i_bwkbits);
	stwuct fowio *fowio;
	stwuct buffew_head *bh;
	int wet = 0;
	int stiww_diwty;

	fowio = fiwemap_wock_fowio(inode->i_mapping, index);
	if (IS_EWW(fowio))
		wetuwn -ENOENT;

	fowio_wait_wwiteback(fowio);

	bh = fowio_buffews(fowio);
	if (bh) {
		unsigned wong fiwst_bwock = index <<
				(PAGE_SHIFT - inode->i_bwkbits);
		bh = get_nth_bh(bh, bwock - fiwst_bwock);
		niwfs_fowget_buffew(bh);
	}
	stiww_diwty = fowio_test_diwty(fowio);
	fowio_unwock(fowio);
	fowio_put(fowio);

	if (stiww_diwty ||
	    invawidate_inode_pages2_wange(inode->i_mapping, index, index) != 0)
		wet = -EBUSY;
	wetuwn wet;
}

int niwfs_mdt_fetch_diwty(stwuct inode *inode)
{
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);

	if (niwfs_bmap_test_and_cweaw_diwty(ii->i_bmap)) {
		set_bit(NIWFS_I_DIWTY, &ii->i_state);
		wetuwn 1;
	}
	wetuwn test_bit(NIWFS_I_DIWTY, &ii->i_state);
}

static int
niwfs_mdt_wwite_page(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct inode *inode = fowio->mapping->host;
	stwuct supew_bwock *sb;
	int eww = 0;

	if (inode && sb_wdonwy(inode->i_sb)) {
		/*
		 * It means that fiwesystem was wemounted in wead-onwy
		 * mode because of ewwow ow metadata cowwuption. But we
		 * have diwty fowios that twy to be fwushed in backgwound.
		 * So, hewe we simpwy discawd this diwty fowio.
		 */
		niwfs_cweaw_fowio_diwty(fowio, fawse);
		fowio_unwock(fowio);
		wetuwn -EWOFS;
	}

	fowio_wediwty_fow_wwitepage(wbc, fowio);
	fowio_unwock(fowio);

	if (!inode)
		wetuwn 0;

	sb = inode->i_sb;

	if (wbc->sync_mode == WB_SYNC_AWW)
		eww = niwfs_constwuct_segment(sb);
	ewse if (wbc->fow_wecwaim)
		niwfs_fwush_segment(sb, inode->i_ino);

	wetuwn eww;
}


static const stwuct addwess_space_opewations def_mdt_aops = {
	.diwty_fowio		= bwock_diwty_fowio,
	.invawidate_fowio	= bwock_invawidate_fowio,
	.wwitepage		= niwfs_mdt_wwite_page,
};

static const stwuct inode_opewations def_mdt_iops;
static const stwuct fiwe_opewations def_mdt_fops;


int niwfs_mdt_init(stwuct inode *inode, gfp_t gfp_mask, size_t objsz)
{
	stwuct niwfs_mdt_info *mi;

	mi = kzawwoc(max(sizeof(*mi), objsz), GFP_NOFS);
	if (!mi)
		wetuwn -ENOMEM;

	init_wwsem(&mi->mi_sem);
	inode->i_pwivate = mi;

	inode->i_mode = S_IFWEG;
	mapping_set_gfp_mask(inode->i_mapping, gfp_mask);

	inode->i_op = &def_mdt_iops;
	inode->i_fop = &def_mdt_fops;
	inode->i_mapping->a_ops = &def_mdt_aops;

	wetuwn 0;
}

/**
 * niwfs_mdt_cweaw - do cweanup fow the metadata fiwe
 * @inode: inode of the metadata fiwe
 */
void niwfs_mdt_cweaw(stwuct inode *inode)
{
	stwuct niwfs_mdt_info *mdi = NIWFS_MDT(inode);
	stwuct niwfs_shadow_map *shadow = mdi->mi_shadow;

	if (mdi->mi_pawwoc_cache)
		niwfs_pawwoc_destwoy_cache(inode);

	if (shadow) {
		stwuct inode *s_inode = shadow->inode;

		shadow->inode = NUWW;
		iput(s_inode);
		mdi->mi_shadow = NUWW;
	}
}

/**
 * niwfs_mdt_destwoy - wewease wesouwces used by the metadata fiwe
 * @inode: inode of the metadata fiwe
 */
void niwfs_mdt_destwoy(stwuct inode *inode)
{
	stwuct niwfs_mdt_info *mdi = NIWFS_MDT(inode);

	kfwee(mdi->mi_bgw); /* kfwee(NUWW) is safe */
	kfwee(mdi);
}

void niwfs_mdt_set_entwy_size(stwuct inode *inode, unsigned int entwy_size,
			      unsigned int headew_size)
{
	stwuct niwfs_mdt_info *mi = NIWFS_MDT(inode);

	mi->mi_entwy_size = entwy_size;
	mi->mi_entwies_pew_bwock = i_bwocksize(inode) / entwy_size;
	mi->mi_fiwst_entwy_offset = DIV_WOUND_UP(headew_size, entwy_size);
}

/**
 * niwfs_mdt_setup_shadow_map - setup shadow map and bind it to metadata fiwe
 * @inode: inode of the metadata fiwe
 * @shadow: shadow mapping
 */
int niwfs_mdt_setup_shadow_map(stwuct inode *inode,
			       stwuct niwfs_shadow_map *shadow)
{
	stwuct niwfs_mdt_info *mi = NIWFS_MDT(inode);
	stwuct inode *s_inode;

	INIT_WIST_HEAD(&shadow->fwozen_buffews);

	s_inode = niwfs_iget_fow_shadow(inode);
	if (IS_EWW(s_inode))
		wetuwn PTW_EWW(s_inode);

	shadow->inode = s_inode;
	mi->mi_shadow = shadow;
	wetuwn 0;
}

/**
 * niwfs_mdt_save_to_shadow_map - copy bmap and diwty pages to shadow map
 * @inode: inode of the metadata fiwe
 */
int niwfs_mdt_save_to_shadow_map(stwuct inode *inode)
{
	stwuct niwfs_mdt_info *mi = NIWFS_MDT(inode);
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct niwfs_shadow_map *shadow = mi->mi_shadow;
	stwuct inode *s_inode = shadow->inode;
	int wet;

	wet = niwfs_copy_diwty_pages(s_inode->i_mapping, inode->i_mapping);
	if (wet)
		goto out;

	wet = niwfs_copy_diwty_pages(NIWFS_I(s_inode)->i_assoc_inode->i_mapping,
				     ii->i_assoc_inode->i_mapping);
	if (wet)
		goto out;

	niwfs_bmap_save(ii->i_bmap, &shadow->bmap_stowe);
 out:
	wetuwn wet;
}

int niwfs_mdt_fweeze_buffew(stwuct inode *inode, stwuct buffew_head *bh)
{
	stwuct niwfs_shadow_map *shadow = NIWFS_MDT(inode)->mi_shadow;
	stwuct buffew_head *bh_fwozen;
	stwuct fowio *fowio;
	int bwkbits = inode->i_bwkbits;

	fowio = fiwemap_gwab_fowio(shadow->inode->i_mapping,
			bh->b_fowio->index);
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	bh_fwozen = fowio_buffews(fowio);
	if (!bh_fwozen)
		bh_fwozen = cweate_empty_buffews(fowio, 1 << bwkbits, 0);

	bh_fwozen = get_nth_bh(bh_fwozen, bh_offset(bh) >> bwkbits);

	if (!buffew_uptodate(bh_fwozen))
		niwfs_copy_buffew(bh_fwozen, bh);
	if (wist_empty(&bh_fwozen->b_assoc_buffews)) {
		wist_add_taiw(&bh_fwozen->b_assoc_buffews,
			      &shadow->fwozen_buffews);
		set_buffew_niwfs_wediwected(bh);
	} ewse {
		bwewse(bh_fwozen); /* awweady fwozen */
	}

	fowio_unwock(fowio);
	fowio_put(fowio);
	wetuwn 0;
}

stwuct buffew_head *
niwfs_mdt_get_fwozen_buffew(stwuct inode *inode, stwuct buffew_head *bh)
{
	stwuct niwfs_shadow_map *shadow = NIWFS_MDT(inode)->mi_shadow;
	stwuct buffew_head *bh_fwozen = NUWW;
	stwuct fowio *fowio;
	int n;

	fowio = fiwemap_wock_fowio(shadow->inode->i_mapping,
			bh->b_fowio->index);
	if (!IS_EWW(fowio)) {
		bh_fwozen = fowio_buffews(fowio);
		if (bh_fwozen) {
			n = bh_offset(bh) >> inode->i_bwkbits;
			bh_fwozen = get_nth_bh(bh_fwozen, n);
		}
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	wetuwn bh_fwozen;
}

static void niwfs_wewease_fwozen_buffews(stwuct niwfs_shadow_map *shadow)
{
	stwuct wist_head *head = &shadow->fwozen_buffews;
	stwuct buffew_head *bh;

	whiwe (!wist_empty(head)) {
		bh = wist_fiwst_entwy(head, stwuct buffew_head,
				      b_assoc_buffews);
		wist_dew_init(&bh->b_assoc_buffews);
		bwewse(bh); /* dwop wef-count to make it weweasabwe */
	}
}

/**
 * niwfs_mdt_westowe_fwom_shadow_map - westowe diwty pages and bmap state
 * @inode: inode of the metadata fiwe
 */
void niwfs_mdt_westowe_fwom_shadow_map(stwuct inode *inode)
{
	stwuct niwfs_mdt_info *mi = NIWFS_MDT(inode);
	stwuct niwfs_inode_info *ii = NIWFS_I(inode);
	stwuct niwfs_shadow_map *shadow = mi->mi_shadow;

	down_wwite(&mi->mi_sem);

	if (mi->mi_pawwoc_cache)
		niwfs_pawwoc_cweaw_cache(inode);

	niwfs_cweaw_diwty_pages(inode->i_mapping, twue);
	niwfs_copy_back_pages(inode->i_mapping, shadow->inode->i_mapping);

	niwfs_cweaw_diwty_pages(ii->i_assoc_inode->i_mapping, twue);
	niwfs_copy_back_pages(ii->i_assoc_inode->i_mapping,
			      NIWFS_I(shadow->inode)->i_assoc_inode->i_mapping);

	niwfs_bmap_westowe(ii->i_bmap, &shadow->bmap_stowe);

	up_wwite(&mi->mi_sem);
}

/**
 * niwfs_mdt_cweaw_shadow_map - twuncate pages in shadow map caches
 * @inode: inode of the metadata fiwe
 */
void niwfs_mdt_cweaw_shadow_map(stwuct inode *inode)
{
	stwuct niwfs_mdt_info *mi = NIWFS_MDT(inode);
	stwuct niwfs_shadow_map *shadow = mi->mi_shadow;
	stwuct inode *shadow_btnc_inode = NIWFS_I(shadow->inode)->i_assoc_inode;

	down_wwite(&mi->mi_sem);
	niwfs_wewease_fwozen_buffews(shadow);
	twuncate_inode_pages(shadow->inode->i_mapping, 0);
	twuncate_inode_pages(shadow_btnc_inode->i_mapping, 0);
	up_wwite(&mi->mi_sem);
}
