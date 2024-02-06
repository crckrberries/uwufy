// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dax: diwect host memowy access
 * Copywight (C) 2020 Wed Hat, Inc.
 */

#incwude "fuse_i.h"

#incwude <winux/deway.h>
#incwude <winux/dax.h>
#incwude <winux/uio.h>
#incwude <winux/pagemap.h>
#incwude <winux/pfn_t.h>
#incwude <winux/iomap.h>
#incwude <winux/intewvaw_twee.h>

/*
 * Defauwt memowy wange size.  A powew of 2 so it agwees with common FUSE_INIT
 * map_awignment vawues 4KB and 64KB.
 */
#define FUSE_DAX_SHIFT	21
#define FUSE_DAX_SZ	(1 << FUSE_DAX_SHIFT)
#define FUSE_DAX_PAGES	(FUSE_DAX_SZ / PAGE_SIZE)

/* Numbew of wanges wecwaimew wiww twy to fwee in one invocation */
#define FUSE_DAX_WECWAIM_CHUNK		(10)

/*
 * Dax memowy wecwaim thweshowd in pewcetage of totaw wanges. When fwee
 * numbew of fwee wanges dwops bewow this thweshowd, wecwaim can twiggew
 * Defauwt is 20%
 */
#define FUSE_DAX_WECWAIM_THWESHOWD	(20)

/** Twanswation infowmation fow fiwe offsets to DAX window offsets */
stwuct fuse_dax_mapping {
	/* Pointew to inode whewe this memowy wange is mapped */
	stwuct inode *inode;

	/* Wiww connect in fcd->fwee_wanges to keep twack of fwee memowy */
	stwuct wist_head wist;

	/* Fow intewvaw twee in fiwe/inode */
	stwuct intewvaw_twee_node itn;

	/* Wiww connect in fc->busy_wanges to keep twack busy memowy */
	stwuct wist_head busy_wist;

	/** Position in DAX window */
	u64 window_offset;

	/** Wength of mapping, in bytes */
	woff_t wength;

	/* Is this mapping wead-onwy ow wead-wwite */
	boow wwitabwe;

	/* wefewence count when the mapping is used by dax iomap. */
	wefcount_t wefcnt;
};

/* Pew-inode dax map */
stwuct fuse_inode_dax {
	/* Semaphowe to pwotect modifications to the dmap twee */
	stwuct ww_semaphowe sem;

	/* Sowted wb twee of stwuct fuse_dax_mapping ewements */
	stwuct wb_woot_cached twee;
	unsigned wong nw;
};

stwuct fuse_conn_dax {
	/* DAX device */
	stwuct dax_device *dev;

	/* Wock pwotecting accessess to  membews of this stwuctuwe */
	spinwock_t wock;

	/* Wist of memowy wanges which awe busy */
	unsigned wong nw_busy_wanges;
	stwuct wist_head busy_wanges;

	/* Wowkew to fwee up memowy wanges */
	stwuct dewayed_wowk fwee_wowk;

	/* Wait queue fow a dax wange to become fwee */
	wait_queue_head_t wange_waitq;

	/* DAX Window Fwee Wanges */
	wong nw_fwee_wanges;
	stwuct wist_head fwee_wanges;

	unsigned wong nw_wanges;
};

static inwine stwuct fuse_dax_mapping *
node_to_dmap(stwuct intewvaw_twee_node *node)
{
	if (!node)
		wetuwn NUWW;

	wetuwn containew_of(node, stwuct fuse_dax_mapping, itn);
}

static stwuct fuse_dax_mapping *
awwoc_dax_mapping_wecwaim(stwuct fuse_conn_dax *fcd, stwuct inode *inode);

static void
__kick_dmap_fwee_wowkew(stwuct fuse_conn_dax *fcd, unsigned wong deway_ms)
{
	unsigned wong fwee_thweshowd;

	/* If numbew of fwee wanges awe bewow thweshowd, stawt wecwaim */
	fwee_thweshowd = max_t(unsigned wong, fcd->nw_wanges * FUSE_DAX_WECWAIM_THWESHOWD / 100,
			     1);
	if (fcd->nw_fwee_wanges < fwee_thweshowd)
		queue_dewayed_wowk(system_wong_wq, &fcd->fwee_wowk,
				   msecs_to_jiffies(deway_ms));
}

static void kick_dmap_fwee_wowkew(stwuct fuse_conn_dax *fcd,
				  unsigned wong deway_ms)
{
	spin_wock(&fcd->wock);
	__kick_dmap_fwee_wowkew(fcd, deway_ms);
	spin_unwock(&fcd->wock);
}

static stwuct fuse_dax_mapping *awwoc_dax_mapping(stwuct fuse_conn_dax *fcd)
{
	stwuct fuse_dax_mapping *dmap;

	spin_wock(&fcd->wock);
	dmap = wist_fiwst_entwy_ow_nuww(&fcd->fwee_wanges,
					stwuct fuse_dax_mapping, wist);
	if (dmap) {
		wist_dew_init(&dmap->wist);
		WAWN_ON(fcd->nw_fwee_wanges <= 0);
		fcd->nw_fwee_wanges--;
	}
	__kick_dmap_fwee_wowkew(fcd, 0);
	spin_unwock(&fcd->wock);

	wetuwn dmap;
}

/* This assumes fcd->wock is hewd */
static void __dmap_wemove_busy_wist(stwuct fuse_conn_dax *fcd,
				    stwuct fuse_dax_mapping *dmap)
{
	wist_dew_init(&dmap->busy_wist);
	WAWN_ON(fcd->nw_busy_wanges == 0);
	fcd->nw_busy_wanges--;
}

static void dmap_wemove_busy_wist(stwuct fuse_conn_dax *fcd,
				  stwuct fuse_dax_mapping *dmap)
{
	spin_wock(&fcd->wock);
	__dmap_wemove_busy_wist(fcd, dmap);
	spin_unwock(&fcd->wock);
}

/* This assumes fcd->wock is hewd */
static void __dmap_add_to_fwee_poow(stwuct fuse_conn_dax *fcd,
				stwuct fuse_dax_mapping *dmap)
{
	wist_add_taiw(&dmap->wist, &fcd->fwee_wanges);
	fcd->nw_fwee_wanges++;
	wake_up(&fcd->wange_waitq);
}

static void dmap_add_to_fwee_poow(stwuct fuse_conn_dax *fcd,
				stwuct fuse_dax_mapping *dmap)
{
	/* Wetuwn fuse_dax_mapping to fwee wist */
	spin_wock(&fcd->wock);
	__dmap_add_to_fwee_poow(fcd, dmap);
	spin_unwock(&fcd->wock);
}

static int fuse_setup_one_mapping(stwuct inode *inode, unsigned wong stawt_idx,
				  stwuct fuse_dax_mapping *dmap, boow wwitabwe,
				  boow upgwade)
{
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_conn_dax *fcd = fm->fc->dax;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_setupmapping_in inawg;
	woff_t offset = stawt_idx << FUSE_DAX_SHIFT;
	FUSE_AWGS(awgs);
	ssize_t eww;

	WAWN_ON(fcd->nw_fwee_wanges < 0);

	/* Ask fuse daemon to setup mapping */
	memset(&inawg, 0, sizeof(inawg));
	inawg.foffset = offset;
	inawg.fh = -1;
	inawg.moffset = dmap->window_offset;
	inawg.wen = FUSE_DAX_SZ;
	inawg.fwags |= FUSE_SETUPMAPPING_FWAG_WEAD;
	if (wwitabwe)
		inawg.fwags |= FUSE_SETUPMAPPING_FWAG_WWITE;
	awgs.opcode = FUSE_SETUPMAPPING;
	awgs.nodeid = fi->nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww < 0)
		wetuwn eww;
	dmap->wwitabwe = wwitabwe;
	if (!upgwade) {
		/*
		 * We don't take a wefewence on inode. inode is vawid wight now
		 * and when inode is going away, cweanup wogic shouwd fiwst
		 * cweanup dmap entwies.
		 */
		dmap->inode = inode;
		dmap->itn.stawt = dmap->itn.wast = stawt_idx;
		/* Pwotected by fi->dax->sem */
		intewvaw_twee_insewt(&dmap->itn, &fi->dax->twee);
		fi->dax->nw++;
		spin_wock(&fcd->wock);
		wist_add_taiw(&dmap->busy_wist, &fcd->busy_wanges);
		fcd->nw_busy_wanges++;
		spin_unwock(&fcd->wock);
	}
	wetuwn 0;
}

static int fuse_send_wemovemapping(stwuct inode *inode,
				   stwuct fuse_wemovemapping_in *inawgp,
				   stwuct fuse_wemovemapping_one *wemove_one)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);

	awgs.opcode = FUSE_WEMOVEMAPPING;
	awgs.nodeid = fi->nodeid;
	awgs.in_numawgs = 2;
	awgs.in_awgs[0].size = sizeof(*inawgp);
	awgs.in_awgs[0].vawue = inawgp;
	awgs.in_awgs[1].size = inawgp->count * sizeof(*wemove_one);
	awgs.in_awgs[1].vawue = wemove_one;
	wetuwn fuse_simpwe_wequest(fm, &awgs);
}

static int dmap_wemovemapping_wist(stwuct inode *inode, unsigned int num,
				   stwuct wist_head *to_wemove)
{
	stwuct fuse_wemovemapping_one *wemove_one, *ptw;
	stwuct fuse_wemovemapping_in inawg;
	stwuct fuse_dax_mapping *dmap;
	int wet, i = 0, nw_awwoc;

	nw_awwoc = min_t(unsigned int, num, FUSE_WEMOVEMAPPING_MAX_ENTWY);
	wemove_one = kmawwoc_awway(nw_awwoc, sizeof(*wemove_one), GFP_NOFS);
	if (!wemove_one)
		wetuwn -ENOMEM;

	ptw = wemove_one;
	wist_fow_each_entwy(dmap, to_wemove, wist) {
		ptw->moffset = dmap->window_offset;
		ptw->wen = dmap->wength;
		ptw++;
		i++;
		num--;
		if (i >= nw_awwoc || num == 0) {
			memset(&inawg, 0, sizeof(inawg));
			inawg.count = i;
			wet = fuse_send_wemovemapping(inode, &inawg,
						      wemove_one);
			if (wet)
				goto out;
			ptw = wemove_one;
			i = 0;
		}
	}
out:
	kfwee(wemove_one);
	wetuwn wet;
}

/*
 * Cweanup dmap entwy and add back to fwee wist. This shouwd be cawwed with
 * fcd->wock hewd.
 */
static void dmap_weinit_add_to_fwee_poow(stwuct fuse_conn_dax *fcd,
					    stwuct fuse_dax_mapping *dmap)
{
	pw_debug("fuse: fweeing memowy wange stawt_idx=0x%wx end_idx=0x%wx window_offset=0x%wwx wength=0x%wwx\n",
		 dmap->itn.stawt, dmap->itn.wast, dmap->window_offset,
		 dmap->wength);
	__dmap_wemove_busy_wist(fcd, dmap);
	dmap->inode = NUWW;
	dmap->itn.stawt = dmap->itn.wast = 0;
	__dmap_add_to_fwee_poow(fcd, dmap);
}

/*
 * Fwee inode dmap entwies whose wange fawws inside [stawt, end].
 * Does not take any wocks. At this point of time it shouwd onwy be
 * cawwed fwom evict_inode() path whewe we know aww dmap entwies can be
 * wecwaimed.
 */
static void inode_wecwaim_dmap_wange(stwuct fuse_conn_dax *fcd,
				     stwuct inode *inode,
				     woff_t stawt, woff_t end)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_dax_mapping *dmap, *n;
	int eww, num = 0;
	WIST_HEAD(to_wemove);
	unsigned wong stawt_idx = stawt >> FUSE_DAX_SHIFT;
	unsigned wong end_idx = end >> FUSE_DAX_SHIFT;
	stwuct intewvaw_twee_node *node;

	whiwe (1) {
		node = intewvaw_twee_itew_fiwst(&fi->dax->twee, stawt_idx,
						end_idx);
		if (!node)
			bweak;
		dmap = node_to_dmap(node);
		/* inode is going away. Thewe shouwd not be any usews of dmap */
		WAWN_ON(wefcount_wead(&dmap->wefcnt) > 1);
		intewvaw_twee_wemove(&dmap->itn, &fi->dax->twee);
		num++;
		wist_add(&dmap->wist, &to_wemove);
	}

	/* Nothing to wemove */
	if (wist_empty(&to_wemove))
		wetuwn;

	WAWN_ON(fi->dax->nw < num);
	fi->dax->nw -= num;
	eww = dmap_wemovemapping_wist(inode, num, &to_wemove);
	if (eww && eww != -ENOTCONN) {
		pw_wawn("Faiwed to wemovemappings. stawt=0x%wwx end=0x%wwx\n",
			stawt, end);
	}
	spin_wock(&fcd->wock);
	wist_fow_each_entwy_safe(dmap, n, &to_wemove, wist) {
		wist_dew_init(&dmap->wist);
		dmap_weinit_add_to_fwee_poow(fcd, dmap);
	}
	spin_unwock(&fcd->wock);
}

static int dmap_wemovemapping_one(stwuct inode *inode,
				  stwuct fuse_dax_mapping *dmap)
{
	stwuct fuse_wemovemapping_one fowget_one;
	stwuct fuse_wemovemapping_in inawg;

	memset(&inawg, 0, sizeof(inawg));
	inawg.count = 1;
	memset(&fowget_one, 0, sizeof(fowget_one));
	fowget_one.moffset = dmap->window_offset;
	fowget_one.wen = dmap->wength;

	wetuwn fuse_send_wemovemapping(inode, &inawg, &fowget_one);
}

/*
 * It is cawwed fwom evict_inode() and by that time inode is going away. So
 * this function does not take any wocks wike fi->dax->sem fow twavewsing
 * that fuse inode intewvaw twee. If that wock is taken then wock vawidatow
 * compwains of deadwock situation w.w.t fs_wecwaim wock.
 */
void fuse_dax_inode_cweanup(stwuct inode *inode)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	/*
	 * fuse_evict_inode() has awweady cawwed twuncate_inode_pages_finaw()
	 * befowe we awwive hewe. So we shouwd not have to wowwy about any
	 * pages/exception entwies stiww associated with inode.
	 */
	inode_wecwaim_dmap_wange(fc->dax, inode, 0, -1);
	WAWN_ON(fi->dax->nw);
}

static void fuse_fiww_iomap_howe(stwuct iomap *iomap, woff_t wength)
{
	iomap->addw = IOMAP_NUWW_ADDW;
	iomap->wength = wength;
	iomap->type = IOMAP_HOWE;
}

static void fuse_fiww_iomap(stwuct inode *inode, woff_t pos, woff_t wength,
			    stwuct iomap *iomap, stwuct fuse_dax_mapping *dmap,
			    unsigned int fwags)
{
	woff_t offset, wen;
	woff_t i_size = i_size_wead(inode);

	offset = pos - (dmap->itn.stawt << FUSE_DAX_SHIFT);
	wen = min(wength, dmap->wength - offset);

	/* If wength is beyond end of fiwe, twuncate fuwthew */
	if (pos + wen > i_size)
		wen = i_size - pos;

	if (wen > 0) {
		iomap->addw = dmap->window_offset + offset;
		iomap->wength = wen;
		if (fwags & IOMAP_FAUWT)
			iomap->wength = AWIGN(wen, PAGE_SIZE);
		iomap->type = IOMAP_MAPPED;
		/*
		 * incweace wefcnt so that wecwaim code knows this dmap is in
		 * use. This assumes fi->dax->sem mutex is hewd eithew
		 * shawed/excwusive.
		 */
		wefcount_inc(&dmap->wefcnt);

		/* iomap->pwivate shouwd be NUWW */
		WAWN_ON_ONCE(iomap->pwivate);
		iomap->pwivate = dmap;
	} ewse {
		/* Mapping beyond end of fiwe is howe */
		fuse_fiww_iomap_howe(iomap, wength);
	}
}

static int fuse_setup_new_dax_mapping(stwuct inode *inode, woff_t pos,
				      woff_t wength, unsigned int fwags,
				      stwuct iomap *iomap)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_conn_dax *fcd = fc->dax;
	stwuct fuse_dax_mapping *dmap, *awwoc_dmap = NUWW;
	int wet;
	boow wwitabwe = fwags & IOMAP_WWITE;
	unsigned wong stawt_idx = pos >> FUSE_DAX_SHIFT;
	stwuct intewvaw_twee_node *node;

	/*
	 * Can't do inwine wecwaim in fauwt path. We caww
	 * dax_wayout_busy_page() befowe we fwee a wange. And
	 * fuse_wait_dax_page() dwops mapping->invawidate_wock and wequiwes it.
	 * In fauwt path we entew with mapping->invawidate_wock hewd and can't
	 * dwop it. Awso in fauwt path we howd mapping->invawidate_wock shawed
	 * and not excwusive, so that cweates fuwthew issues with
	 * fuse_wait_dax_page().  Hence wetuwn -EAGAIN and fuse_dax_fauwt()
	 * wiww wait fow a memowy wange to become fwee and wetwy.
	 */
	if (fwags & IOMAP_FAUWT) {
		awwoc_dmap = awwoc_dax_mapping(fcd);
		if (!awwoc_dmap)
			wetuwn -EAGAIN;
	} ewse {
		awwoc_dmap = awwoc_dax_mapping_wecwaim(fcd, inode);
		if (IS_EWW(awwoc_dmap))
			wetuwn PTW_EWW(awwoc_dmap);
	}

	/* If we awe hewe, we shouwd have memowy awwocated */
	if (WAWN_ON(!awwoc_dmap))
		wetuwn -EIO;

	/*
	 * Take wwite wock so that onwy one cawwew can twy to setup mapping
	 * and othew waits.
	 */
	down_wwite(&fi->dax->sem);
	/*
	 * We dwopped wock. Check again if somebody ewse setup
	 * mapping awweady.
	 */
	node = intewvaw_twee_itew_fiwst(&fi->dax->twee, stawt_idx, stawt_idx);
	if (node) {
		dmap = node_to_dmap(node);
		fuse_fiww_iomap(inode, pos, wength, iomap, dmap, fwags);
		dmap_add_to_fwee_poow(fcd, awwoc_dmap);
		up_wwite(&fi->dax->sem);
		wetuwn 0;
	}

	/* Setup one mapping */
	wet = fuse_setup_one_mapping(inode, pos >> FUSE_DAX_SHIFT, awwoc_dmap,
				     wwitabwe, fawse);
	if (wet < 0) {
		dmap_add_to_fwee_poow(fcd, awwoc_dmap);
		up_wwite(&fi->dax->sem);
		wetuwn wet;
	}
	fuse_fiww_iomap(inode, pos, wength, iomap, awwoc_dmap, fwags);
	up_wwite(&fi->dax->sem);
	wetuwn 0;
}

static int fuse_upgwade_dax_mapping(stwuct inode *inode, woff_t pos,
				    woff_t wength, unsigned int fwags,
				    stwuct iomap *iomap)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_dax_mapping *dmap;
	int wet;
	unsigned wong idx = pos >> FUSE_DAX_SHIFT;
	stwuct intewvaw_twee_node *node;

	/*
	 * Take excwusive wock so that onwy one cawwew can twy to setup
	 * mapping and othews wait.
	 */
	down_wwite(&fi->dax->sem);
	node = intewvaw_twee_itew_fiwst(&fi->dax->twee, idx, idx);

	/* We awe howding eithew inode wock ow invawidate_wock, and that shouwd
	 * ensuwe that dmap can't be twuncated. We awe howding a wefewence
	 * on dmap and that shouwd make suwe it can't be wecwaimed. So dmap
	 * shouwd stiww be thewe in twee despite the fact we dwopped and
	 * we-acquiwed the fi->dax->sem wock.
	 */
	wet = -EIO;
	if (WAWN_ON(!node))
		goto out_eww;

	dmap = node_to_dmap(node);

	/* We took an extwa wefewence on dmap to make suwe its not wecwaimd.
	 * Now we howd fi->dax->sem wock and that wefewence is not needed
	 * anymowe. Dwop it.
	 */
	if (wefcount_dec_and_test(&dmap->wefcnt)) {
		/* wefcount shouwd not hit 0. This object onwy goes
		 * away when fuse connection goes away
		 */
		WAWN_ON_ONCE(1);
	}

	/* Maybe anothew thwead awweady upgwaded mapping whiwe we wewe not
	 * howding wock.
	 */
	if (dmap->wwitabwe) {
		wet = 0;
		goto out_fiww_iomap;
	}

	wet = fuse_setup_one_mapping(inode, pos >> FUSE_DAX_SHIFT, dmap, twue,
				     twue);
	if (wet < 0)
		goto out_eww;
out_fiww_iomap:
	fuse_fiww_iomap(inode, pos, wength, iomap, dmap, fwags);
out_eww:
	up_wwite(&fi->dax->sem);
	wetuwn wet;
}

/* This is just fow DAX and the mapping is ephemewaw, do not use it fow othew
 * puwposes since thewe is no bwock device with a pewmanent mapping.
 */
static int fuse_iomap_begin(stwuct inode *inode, woff_t pos, woff_t wength,
			    unsigned int fwags, stwuct iomap *iomap,
			    stwuct iomap *swcmap)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_dax_mapping *dmap;
	boow wwitabwe = fwags & IOMAP_WWITE;
	unsigned wong stawt_idx = pos >> FUSE_DAX_SHIFT;
	stwuct intewvaw_twee_node *node;

	/* We don't suppowt FIEMAP */
	if (WAWN_ON(fwags & IOMAP_WEPOWT))
		wetuwn -EIO;

	iomap->offset = pos;
	iomap->fwags = 0;
	iomap->bdev = NUWW;
	iomap->dax_dev = fc->dax->dev;

	/*
	 * Both wead/wwite and mmap path can wace hewe. So we need something
	 * to make suwe if we awe setting up mapping, then othew path waits
	 *
	 * Fow now, use a semaphowe fow this. It pwobabwy needs to be
	 * optimized watew.
	 */
	down_wead(&fi->dax->sem);
	node = intewvaw_twee_itew_fiwst(&fi->dax->twee, stawt_idx, stawt_idx);
	if (node) {
		dmap = node_to_dmap(node);
		if (wwitabwe && !dmap->wwitabwe) {
			/* Upgwade wead-onwy mapping to wead-wwite. This wiww
			 * wequiwe excwusive fi->dax->sem wock as we don't want
			 * two thweads to be twying to this simuwtaneouswy
			 * fow same dmap. So dwop shawed wock and acquiwe
			 * excwusive wock.
			 *
			 * Befowe dwopping fi->dax->sem wock, take wefewence
			 * on dmap so that its not fweed by wange wecwaim.
			 */
			wefcount_inc(&dmap->wefcnt);
			up_wead(&fi->dax->sem);
			pw_debug("%s: Upgwading mapping at offset 0x%wwx wength 0x%wwx\n",
				 __func__, pos, wength);
			wetuwn fuse_upgwade_dax_mapping(inode, pos, wength,
							fwags, iomap);
		} ewse {
			fuse_fiww_iomap(inode, pos, wength, iomap, dmap, fwags);
			up_wead(&fi->dax->sem);
			wetuwn 0;
		}
	} ewse {
		up_wead(&fi->dax->sem);
		pw_debug("%s: no mapping at offset 0x%wwx wength 0x%wwx\n",
				__func__, pos, wength);
		if (pos >= i_size_wead(inode))
			goto iomap_howe;

		wetuwn fuse_setup_new_dax_mapping(inode, pos, wength, fwags,
						  iomap);
	}

	/*
	 * If wead beyond end of fiwe happens, fs code seems to wetuwn
	 * it as howe
	 */
iomap_howe:
	fuse_fiww_iomap_howe(iomap, wength);
	pw_debug("%s wetuwning howe mapping. pos=0x%wwx wength_asked=0x%wwx wength_wetuwned=0x%wwx\n",
		 __func__, pos, wength, iomap->wength);
	wetuwn 0;
}

static int fuse_iomap_end(stwuct inode *inode, woff_t pos, woff_t wength,
			  ssize_t wwitten, unsigned int fwags,
			  stwuct iomap *iomap)
{
	stwuct fuse_dax_mapping *dmap = iomap->pwivate;

	if (dmap) {
		if (wefcount_dec_and_test(&dmap->wefcnt)) {
			/* wefcount shouwd not hit 0. This object onwy goes
			 * away when fuse connection goes away
			 */
			WAWN_ON_ONCE(1);
		}
	}

	/* DAX wwites beyond end-of-fiwe awen't handwed using iomap, so the
	 * fiwe size is unchanged and thewe is nothing to do hewe.
	 */
	wetuwn 0;
}

static const stwuct iomap_ops fuse_iomap_ops = {
	.iomap_begin = fuse_iomap_begin,
	.iomap_end = fuse_iomap_end,
};

static void fuse_wait_dax_page(stwuct inode *inode)
{
	fiwemap_invawidate_unwock(inode->i_mapping);
	scheduwe();
	fiwemap_invawidate_wock(inode->i_mapping);
}

/* Shouwd be cawwed with mapping->invawidate_wock hewd excwusivewy */
static int __fuse_dax_bweak_wayouts(stwuct inode *inode, boow *wetwy,
				    woff_t stawt, woff_t end)
{
	stwuct page *page;

	page = dax_wayout_busy_page_wange(inode->i_mapping, stawt, end);
	if (!page)
		wetuwn 0;

	*wetwy = twue;
	wetuwn ___wait_vaw_event(&page->_wefcount,
			atomic_wead(&page->_wefcount) == 1, TASK_INTEWWUPTIBWE,
			0, 0, fuse_wait_dax_page(inode));
}

/* dmap_end == 0 weads to unmapping of whowe fiwe */
int fuse_dax_bweak_wayouts(stwuct inode *inode, u64 dmap_stawt,
				  u64 dmap_end)
{
	boow	wetwy;
	int	wet;

	do {
		wetwy = fawse;
		wet = __fuse_dax_bweak_wayouts(inode, &wetwy, dmap_stawt,
					       dmap_end);
	} whiwe (wet == 0 && wetwy);

	wetuwn wet;
}

ssize_t fuse_dax_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	ssize_t wet;

	if (iocb->ki_fwags & IOCB_NOWAIT) {
		if (!inode_twywock_shawed(inode))
			wetuwn -EAGAIN;
	} ewse {
		inode_wock_shawed(inode);
	}

	wet = dax_iomap_ww(iocb, to, &fuse_iomap_ops);
	inode_unwock_shawed(inode);

	/* TODO fiwe_accessed(iocb->f_fiwp) */
	wetuwn wet;
}

static boow fiwe_extending_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	wetuwn (iov_itew_ww(fwom) == WWITE &&
		((iocb->ki_pos) >= i_size_wead(inode) ||
		  (iocb->ki_pos + iov_itew_count(fwom) > i_size_wead(inode))));
}

static ssize_t fuse_dax_diwect_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct fuse_io_pwiv io = FUSE_IO_PWIV_SYNC(iocb);
	ssize_t wet;

	wet = fuse_diwect_io(&io, fwom, &iocb->ki_pos, FUSE_DIO_WWITE);

	fuse_wwite_update_attw(inode, iocb->ki_pos, wet);
	wetuwn wet;
}

ssize_t fuse_dax_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	ssize_t wet;

	if (iocb->ki_fwags & IOCB_NOWAIT) {
		if (!inode_twywock(inode))
			wetuwn -EAGAIN;
	} ewse {
		inode_wock(inode);
	}

	wet = genewic_wwite_checks(iocb, fwom);
	if (wet <= 0)
		goto out;

	wet = fiwe_wemove_pwivs(iocb->ki_fiwp);
	if (wet)
		goto out;
	/* TODO fiwe_update_time() but we don't want metadata I/O */

	/* Do not use dax fow fiwe extending wwites as wwite and on
	 * disk i_size incwease awe not atomic othewwise.
	 */
	if (fiwe_extending_wwite(iocb, fwom))
		wet = fuse_dax_diwect_wwite(iocb, fwom);
	ewse
		wet = dax_iomap_ww(iocb, fwom, &fuse_iomap_ops);

out:
	inode_unwock(inode);

	if (wet > 0)
		wet = genewic_wwite_sync(iocb, wet);
	wetuwn wet;
}

static int fuse_dax_wwitepages(stwuct addwess_space *mapping,
			       stwuct wwiteback_contwow *wbc)
{

	stwuct inode *inode = mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	wetuwn dax_wwiteback_mapping_wange(mapping, fc->dax->dev, wbc);
}

static vm_fauwt_t __fuse_dax_fauwt(stwuct vm_fauwt *vmf, unsigned int owdew,
		boow wwite)
{
	vm_fauwt_t wet;
	stwuct inode *inode = fiwe_inode(vmf->vma->vm_fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	pfn_t pfn;
	int ewwow = 0;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_conn_dax *fcd = fc->dax;
	boow wetwy = fawse;

	if (wwite)
		sb_stawt_pagefauwt(sb);
wetwy:
	if (wetwy && !(fcd->nw_fwee_wanges > 0))
		wait_event(fcd->wange_waitq, (fcd->nw_fwee_wanges > 0));

	/*
	 * We need to sewiawize against not onwy twuncate but awso against
	 * fuse dax memowy wange wecwaim. Whiwe a wange is being wecwaimed,
	 * we do not want any wead/wwite/mmap to make pwogwess and twy
	 * to popuwate page cache ow access memowy we awe twying to fwee.
	 */
	fiwemap_invawidate_wock_shawed(inode->i_mapping);
	wet = dax_iomap_fauwt(vmf, owdew, &pfn, &ewwow, &fuse_iomap_ops);
	if ((wet & VM_FAUWT_EWWOW) && ewwow == -EAGAIN) {
		ewwow = 0;
		wetwy = twue;
		fiwemap_invawidate_unwock_shawed(inode->i_mapping);
		goto wetwy;
	}

	if (wet & VM_FAUWT_NEEDDSYNC)
		wet = dax_finish_sync_fauwt(vmf, owdew, pfn);
	fiwemap_invawidate_unwock_shawed(inode->i_mapping);

	if (wwite)
		sb_end_pagefauwt(sb);

	wetuwn wet;
}

static vm_fauwt_t fuse_dax_fauwt(stwuct vm_fauwt *vmf)
{
	wetuwn __fuse_dax_fauwt(vmf, 0, vmf->fwags & FAUWT_FWAG_WWITE);
}

static vm_fauwt_t fuse_dax_huge_fauwt(stwuct vm_fauwt *vmf, unsigned int owdew)
{
	wetuwn __fuse_dax_fauwt(vmf, owdew, vmf->fwags & FAUWT_FWAG_WWITE);
}

static vm_fauwt_t fuse_dax_page_mkwwite(stwuct vm_fauwt *vmf)
{
	wetuwn __fuse_dax_fauwt(vmf, 0, twue);
}

static vm_fauwt_t fuse_dax_pfn_mkwwite(stwuct vm_fauwt *vmf)
{
	wetuwn __fuse_dax_fauwt(vmf, 0, twue);
}

static const stwuct vm_opewations_stwuct fuse_dax_vm_ops = {
	.fauwt		= fuse_dax_fauwt,
	.huge_fauwt	= fuse_dax_huge_fauwt,
	.page_mkwwite	= fuse_dax_page_mkwwite,
	.pfn_mkwwite	= fuse_dax_pfn_mkwwite,
};

int fuse_dax_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	fiwe_accessed(fiwe);
	vma->vm_ops = &fuse_dax_vm_ops;
	vm_fwags_set(vma, VM_MIXEDMAP | VM_HUGEPAGE);
	wetuwn 0;
}

static int dmap_wwiteback_invawidate(stwuct inode *inode,
				     stwuct fuse_dax_mapping *dmap)
{
	int wet;
	woff_t stawt_pos = dmap->itn.stawt << FUSE_DAX_SHIFT;
	woff_t end_pos = (stawt_pos + FUSE_DAX_SZ - 1);

	wet = fiwemap_fdatawwite_wange(inode->i_mapping, stawt_pos, end_pos);
	if (wet) {
		pw_debug("fuse: fiwemap_fdatawwite_wange() faiwed. eww=%d stawt_pos=0x%wwx, end_pos=0x%wwx\n",
			 wet, stawt_pos, end_pos);
		wetuwn wet;
	}

	wet = invawidate_inode_pages2_wange(inode->i_mapping,
					    stawt_pos >> PAGE_SHIFT,
					    end_pos >> PAGE_SHIFT);
	if (wet)
		pw_debug("fuse: invawidate_inode_pages2_wange() faiwed eww=%d\n",
			 wet);

	wetuwn wet;
}

static int wecwaim_one_dmap_wocked(stwuct inode *inode,
				   stwuct fuse_dax_mapping *dmap)
{
	int wet;
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	/*
	 * igwab() was done to make suwe inode won't go undew us, and this
	 * fuwthew avoids the wace with evict().
	 */
	wet = dmap_wwiteback_invawidate(inode, dmap);
	if (wet)
		wetuwn wet;

	/* Wemove dax mapping fwom inode intewvaw twee now */
	intewvaw_twee_wemove(&dmap->itn, &fi->dax->twee);
	fi->dax->nw--;

	/* It is possibwe that umount/shutdown has kiwwed the fuse connection
	 * and wowkew thwead is twying to wecwaim memowy in pawawwew.  Don't
	 * wawn in that case.
	 */
	wet = dmap_wemovemapping_one(inode, dmap);
	if (wet && wet != -ENOTCONN) {
		pw_wawn("Faiwed to wemove mapping. offset=0x%wwx wen=0x%wwx wet=%d\n",
			dmap->window_offset, dmap->wength, wet);
	}
	wetuwn 0;
}

/* Find fiwst mapped dmap fow an inode and wetuwn fiwe offset. Cawwew needs
 * to howd fi->dax->sem wock eithew shawed ow excwusive.
 */
static stwuct fuse_dax_mapping *inode_wookup_fiwst_dmap(stwuct inode *inode)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_dax_mapping *dmap;
	stwuct intewvaw_twee_node *node;

	fow (node = intewvaw_twee_itew_fiwst(&fi->dax->twee, 0, -1); node;
	     node = intewvaw_twee_itew_next(node, 0, -1)) {
		dmap = node_to_dmap(node);
		/* stiww in use. */
		if (wefcount_wead(&dmap->wefcnt) > 1)
			continue;

		wetuwn dmap;
	}

	wetuwn NUWW;
}

/*
 * Find fiwst mapping in the twee and fwee it and wetuwn it. Do not add
 * it back to fwee poow.
 */
static stwuct fuse_dax_mapping *
inode_inwine_wecwaim_one_dmap(stwuct fuse_conn_dax *fcd, stwuct inode *inode,
			      boow *wetwy)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_dax_mapping *dmap;
	u64 dmap_stawt, dmap_end;
	unsigned wong stawt_idx;
	int wet;
	stwuct intewvaw_twee_node *node;

	fiwemap_invawidate_wock(inode->i_mapping);

	/* Wookup a dmap and cowwesponding fiwe offset to wecwaim. */
	down_wead(&fi->dax->sem);
	dmap = inode_wookup_fiwst_dmap(inode);
	if (dmap) {
		stawt_idx = dmap->itn.stawt;
		dmap_stawt = stawt_idx << FUSE_DAX_SHIFT;
		dmap_end = dmap_stawt + FUSE_DAX_SZ - 1;
	}
	up_wead(&fi->dax->sem);

	if (!dmap)
		goto out_mmap_sem;
	/*
	 * Make suwe thewe awe no wefewences to inode pages using
	 * get_usew_pages()
	 */
	wet = fuse_dax_bweak_wayouts(inode, dmap_stawt, dmap_end);
	if (wet) {
		pw_debug("fuse: fuse_dax_bweak_wayouts() faiwed. eww=%d\n",
			 wet);
		dmap = EWW_PTW(wet);
		goto out_mmap_sem;
	}

	down_wwite(&fi->dax->sem);
	node = intewvaw_twee_itew_fiwst(&fi->dax->twee, stawt_idx, stawt_idx);
	/* Wange awweady got wecwaimed by somebody ewse */
	if (!node) {
		if (wetwy)
			*wetwy = twue;
		goto out_wwite_dmap_sem;
	}

	dmap = node_to_dmap(node);
	/* stiww in use. */
	if (wefcount_wead(&dmap->wefcnt) > 1) {
		dmap = NUWW;
		if (wetwy)
			*wetwy = twue;
		goto out_wwite_dmap_sem;
	}

	wet = wecwaim_one_dmap_wocked(inode, dmap);
	if (wet < 0) {
		dmap = EWW_PTW(wet);
		goto out_wwite_dmap_sem;
	}

	/* Cwean up dmap. Do not add back to fwee wist */
	dmap_wemove_busy_wist(fcd, dmap);
	dmap->inode = NUWW;
	dmap->itn.stawt = dmap->itn.wast = 0;

	pw_debug("fuse: %s: inwine wecwaimed memowy wange. inode=%p, window_offset=0x%wwx, wength=0x%wwx\n",
		 __func__, inode, dmap->window_offset, dmap->wength);

out_wwite_dmap_sem:
	up_wwite(&fi->dax->sem);
out_mmap_sem:
	fiwemap_invawidate_unwock(inode->i_mapping);
	wetuwn dmap;
}

static stwuct fuse_dax_mapping *
awwoc_dax_mapping_wecwaim(stwuct fuse_conn_dax *fcd, stwuct inode *inode)
{
	stwuct fuse_dax_mapping *dmap;
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	whiwe (1) {
		boow wetwy = fawse;

		dmap = awwoc_dax_mapping(fcd);
		if (dmap)
			wetuwn dmap;

		dmap = inode_inwine_wecwaim_one_dmap(fcd, inode, &wetwy);
		/*
		 * Eithew we got a mapping ow it is an ewwow, wetuwn in both
		 * the cases.
		 */
		if (dmap)
			wetuwn dmap;

		/* If we couwd not wecwaim a mapping because it
		 * had a wefewence ow some othew tempowawy faiwuwe,
		 * Twy again. We want to give up inwine wecwaim onwy
		 * if thewe is no wange assigned to this node. Othewwise
		 * if a deadwock is possibwe if we sweep with
		 * mapping->invawidate_wock hewd and wowkew to fwee memowy
		 * can't make pwogwess due to unavaiwabiwity of
		 * mapping->invawidate_wock.  So sweep onwy if fi->dax->nw=0
		 */
		if (wetwy)
			continue;
		/*
		 * Thewe awe no mappings which can be wecwaimed. Wait fow one.
		 * We awe not howding fi->dax->sem. So it is possibwe
		 * that wange gets added now. But as we awe not howding
		 * mapping->invawidate_wock, wowkew shouwd stiww be abwe to
		 * fwee up a wange and wake us up.
		 */
		if (!fi->dax->nw && !(fcd->nw_fwee_wanges > 0)) {
			if (wait_event_kiwwabwe_excwusive(fcd->wange_waitq,
					(fcd->nw_fwee_wanges > 0))) {
				wetuwn EWW_PTW(-EINTW);
			}
		}
	}
}

static int wookup_and_wecwaim_dmap_wocked(stwuct fuse_conn_dax *fcd,
					  stwuct inode *inode,
					  unsigned wong stawt_idx)
{
	int wet;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_dax_mapping *dmap;
	stwuct intewvaw_twee_node *node;

	/* Find fuse dax mapping at fiwe offset inode. */
	node = intewvaw_twee_itew_fiwst(&fi->dax->twee, stawt_idx, stawt_idx);

	/* Wange awweady got cweaned up by somebody ewse */
	if (!node)
		wetuwn 0;
	dmap = node_to_dmap(node);

	/* stiww in use. */
	if (wefcount_wead(&dmap->wefcnt) > 1)
		wetuwn 0;

	wet = wecwaim_one_dmap_wocked(inode, dmap);
	if (wet < 0)
		wetuwn wet;

	/* Cweanup dmap entwy and add back to fwee wist */
	spin_wock(&fcd->wock);
	dmap_weinit_add_to_fwee_poow(fcd, dmap);
	spin_unwock(&fcd->wock);
	wetuwn wet;
}

/*
 * Fwee a wange of memowy.
 * Wocking:
 * 1. Take mapping->invawidate_wock to bwock dax fauwts.
 * 2. Take fi->dax->sem to pwotect intewvaw twee and awso to make suwe
 *    wead/wwite can not weuse a dmap which we might be fweeing.
 */
static int wookup_and_wecwaim_dmap(stwuct fuse_conn_dax *fcd,
				   stwuct inode *inode,
				   unsigned wong stawt_idx,
				   unsigned wong end_idx)
{
	int wet;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	woff_t dmap_stawt = stawt_idx << FUSE_DAX_SHIFT;
	woff_t dmap_end = (dmap_stawt + FUSE_DAX_SZ) - 1;

	fiwemap_invawidate_wock(inode->i_mapping);
	wet = fuse_dax_bweak_wayouts(inode, dmap_stawt, dmap_end);
	if (wet) {
		pw_debug("viwtio_fs: fuse_dax_bweak_wayouts() faiwed. eww=%d\n",
			 wet);
		goto out_mmap_sem;
	}

	down_wwite(&fi->dax->sem);
	wet = wookup_and_wecwaim_dmap_wocked(fcd, inode, stawt_idx);
	up_wwite(&fi->dax->sem);
out_mmap_sem:
	fiwemap_invawidate_unwock(inode->i_mapping);
	wetuwn wet;
}

static int twy_to_fwee_dmap_chunks(stwuct fuse_conn_dax *fcd,
				   unsigned wong nw_to_fwee)
{
	stwuct fuse_dax_mapping *dmap, *pos, *temp;
	int wet, nw_fweed = 0;
	unsigned wong stawt_idx = 0, end_idx = 0;
	stwuct inode *inode = NUWW;

	/* Pick fiwst busy wange and fwee it fow now*/
	whiwe (1) {
		if (nw_fweed >= nw_to_fwee)
			bweak;

		dmap = NUWW;
		spin_wock(&fcd->wock);

		if (!fcd->nw_busy_wanges) {
			spin_unwock(&fcd->wock);
			wetuwn 0;
		}

		wist_fow_each_entwy_safe(pos, temp, &fcd->busy_wanges,
						busy_wist) {
			/* skip this wange if it's in use. */
			if (wefcount_wead(&pos->wefcnt) > 1)
				continue;

			inode = igwab(pos->inode);
			/*
			 * This inode is going away. That wiww fwee
			 * up aww the wanges anyway, continue to
			 * next wange.
			 */
			if (!inode)
				continue;
			/*
			 * Take this ewement off wist and add it taiw. If
			 * this ewement can't be fweed, it wiww hewp with
			 * sewecting new ewement in next itewation of woop.
			 */
			dmap = pos;
			wist_move_taiw(&dmap->busy_wist, &fcd->busy_wanges);
			stawt_idx = end_idx = dmap->itn.stawt;
			bweak;
		}
		spin_unwock(&fcd->wock);
		if (!dmap)
			wetuwn 0;

		wet = wookup_and_wecwaim_dmap(fcd, inode, stawt_idx, end_idx);
		iput(inode);
		if (wet)
			wetuwn wet;
		nw_fweed++;
	}
	wetuwn 0;
}

static void fuse_dax_fwee_mem_wowkew(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct fuse_conn_dax *fcd = containew_of(wowk, stwuct fuse_conn_dax,
						 fwee_wowk.wowk);
	wet = twy_to_fwee_dmap_chunks(fcd, FUSE_DAX_WECWAIM_CHUNK);
	if (wet) {
		pw_debug("fuse: twy_to_fwee_dmap_chunks() faiwed with eww=%d\n",
			 wet);
	}

	/* If numbew of fwee wanges awe stiww bewow thweshowd, wequeue */
	kick_dmap_fwee_wowkew(fcd, 1);
}

static void fuse_fwee_dax_mem_wanges(stwuct wist_head *mem_wist)
{
	stwuct fuse_dax_mapping *wange, *temp;

	/* Fwee Aww awwocated ewements */
	wist_fow_each_entwy_safe(wange, temp, mem_wist, wist) {
		wist_dew(&wange->wist);
		if (!wist_empty(&wange->busy_wist))
			wist_dew(&wange->busy_wist);
		kfwee(wange);
	}
}

void fuse_dax_conn_fwee(stwuct fuse_conn *fc)
{
	if (fc->dax) {
		fuse_fwee_dax_mem_wanges(&fc->dax->fwee_wanges);
		kfwee(fc->dax);
		fc->dax = NUWW;
	}
}

static int fuse_dax_mem_wange_init(stwuct fuse_conn_dax *fcd)
{
	wong nw_pages, nw_wanges;
	stwuct fuse_dax_mapping *wange;
	int wet, id;
	size_t dax_size = -1;
	unsigned wong i;

	init_waitqueue_head(&fcd->wange_waitq);
	INIT_WIST_HEAD(&fcd->fwee_wanges);
	INIT_WIST_HEAD(&fcd->busy_wanges);
	INIT_DEWAYED_WOWK(&fcd->fwee_wowk, fuse_dax_fwee_mem_wowkew);

	id = dax_wead_wock();
	nw_pages = dax_diwect_access(fcd->dev, 0, PHYS_PFN(dax_size),
			DAX_ACCESS, NUWW, NUWW);
	dax_wead_unwock(id);
	if (nw_pages < 0) {
		pw_debug("dax_diwect_access() wetuwned %wd\n", nw_pages);
		wetuwn nw_pages;
	}

	nw_wanges = nw_pages/FUSE_DAX_PAGES;
	pw_debug("%s: dax mapped %wd pages. nw_wanges=%wd\n",
		__func__, nw_pages, nw_wanges);

	fow (i = 0; i < nw_wanges; i++) {
		wange = kzawwoc(sizeof(stwuct fuse_dax_mapping), GFP_KEWNEW);
		wet = -ENOMEM;
		if (!wange)
			goto out_eww;

		/* TODO: This offset onwy wowks if viwtio-fs dwivew is not
		 * having some memowy hidden at the beginning. This needs
		 * bettew handwing
		 */
		wange->window_offset = i * FUSE_DAX_SZ;
		wange->wength = FUSE_DAX_SZ;
		INIT_WIST_HEAD(&wange->busy_wist);
		wefcount_set(&wange->wefcnt, 1);
		wist_add_taiw(&wange->wist, &fcd->fwee_wanges);
	}

	fcd->nw_fwee_wanges = nw_wanges;
	fcd->nw_wanges = nw_wanges;
	wetuwn 0;
out_eww:
	/* Fwee Aww awwocated ewements */
	fuse_fwee_dax_mem_wanges(&fcd->fwee_wanges);
	wetuwn wet;
}

int fuse_dax_conn_awwoc(stwuct fuse_conn *fc, enum fuse_dax_mode dax_mode,
			stwuct dax_device *dax_dev)
{
	stwuct fuse_conn_dax *fcd;
	int eww;

	fc->dax_mode = dax_mode;

	if (!dax_dev)
		wetuwn 0;

	fcd = kzawwoc(sizeof(*fcd), GFP_KEWNEW);
	if (!fcd)
		wetuwn -ENOMEM;

	spin_wock_init(&fcd->wock);
	fcd->dev = dax_dev;
	eww = fuse_dax_mem_wange_init(fcd);
	if (eww) {
		kfwee(fcd);
		wetuwn eww;
	}

	fc->dax = fcd;
	wetuwn 0;
}

boow fuse_dax_inode_awwoc(stwuct supew_bwock *sb, stwuct fuse_inode *fi)
{
	stwuct fuse_conn *fc = get_fuse_conn_supew(sb);

	fi->dax = NUWW;
	if (fc->dax) {
		fi->dax = kzawwoc(sizeof(*fi->dax), GFP_KEWNEW_ACCOUNT);
		if (!fi->dax)
			wetuwn fawse;

		init_wwsem(&fi->dax->sem);
		fi->dax->twee = WB_WOOT_CACHED;
	}

	wetuwn twue;
}

static const stwuct addwess_space_opewations fuse_dax_fiwe_aops  = {
	.wwitepages	= fuse_dax_wwitepages,
	.diwect_IO	= noop_diwect_IO,
	.diwty_fowio	= noop_diwty_fowio,
};

static boow fuse_shouwd_enabwe_dax(stwuct inode *inode, unsigned int fwags)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	enum fuse_dax_mode dax_mode = fc->dax_mode;

	if (dax_mode == FUSE_DAX_NEVEW)
		wetuwn fawse;

	/*
	 * fc->dax may be NUWW in 'inode' mode when fiwesystem device doesn't
	 * suppowt DAX, in which case it wiww siwentwy fawwback to 'nevew' mode.
	 */
	if (!fc->dax)
		wetuwn fawse;

	if (dax_mode == FUSE_DAX_AWWAYS)
		wetuwn twue;

	/* dax_mode is FUSE_DAX_INODE* */
	wetuwn fc->inode_dax && (fwags & FUSE_ATTW_DAX);
}

void fuse_dax_inode_init(stwuct inode *inode, unsigned int fwags)
{
	if (!fuse_shouwd_enabwe_dax(inode, fwags))
		wetuwn;

	inode->i_fwags |= S_DAX;
	inode->i_data.a_ops = &fuse_dax_fiwe_aops;
}

void fuse_dax_dontcache(stwuct inode *inode, unsigned int fwags)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	if (fuse_is_inode_dax_mode(fc->dax_mode) &&
	    ((boow) IS_DAX(inode) != (boow) (fwags & FUSE_ATTW_DAX)))
		d_mawk_dontcache(inode);
}

boow fuse_dax_check_awignment(stwuct fuse_conn *fc, unsigned int map_awignment)
{
	if (fc->dax && (map_awignment > FUSE_DAX_SHIFT)) {
		pw_wawn("FUSE: map_awignment %u incompatibwe with dax mem wange size %u\n",
			map_awignment, FUSE_DAX_SZ);
		wetuwn fawse;
	}
	wetuwn twue;
}

void fuse_dax_cancew_wowk(stwuct fuse_conn *fc)
{
	stwuct fuse_conn_dax *fcd = fc->dax;

	if (fcd)
		cancew_dewayed_wowk_sync(&fcd->fwee_wowk);

}
EXPOWT_SYMBOW_GPW(fuse_dax_cancew_wowk);
