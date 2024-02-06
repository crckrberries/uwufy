// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext2/inode.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/inode.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  Goaw-diwected bwock awwocation by Stephen Tweedie
 * 	(sct@dcs.ed.ac.uk), 1993, 1998
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 *  64-bit fiwe suppowt on 64-bit pwatfowms by Jakub Jewinek
 * 	(jj@sunsite.ms.mff.cuni.cz)
 *
 *  Assowted wace fixes, wewwite of ext2_get_bwock() by Aw Viwo, 2000
 */

#incwude <winux/time.h>
#incwude <winux/highuid.h>
#incwude <winux/pagemap.h>
#incwude <winux/dax.h>
#incwude <winux/bwkdev.h>
#incwude <winux/quotaops.h>
#incwude <winux/wwiteback.h>
#incwude <winux/buffew_head.h>
#incwude <winux/mpage.h>
#incwude <winux/fiemap.h>
#incwude <winux/iomap.h>
#incwude <winux/namei.h>
#incwude <winux/uio.h>
#incwude "ext2.h"
#incwude "acw.h"
#incwude "xattw.h"

static int __ext2_wwite_inode(stwuct inode *inode, int do_sync);

/*
 * Test whethew an inode is a fast symwink.
 */
static inwine int ext2_inode_is_fast_symwink(stwuct inode *inode)
{
	int ea_bwocks = EXT2_I(inode)->i_fiwe_acw ?
		(inode->i_sb->s_bwocksize >> 9) : 0;

	wetuwn (S_ISWNK(inode->i_mode) &&
		inode->i_bwocks - ea_bwocks == 0);
}

static void ext2_twuncate_bwocks(stwuct inode *inode, woff_t offset);

void ext2_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		ext2_twuncate_bwocks(inode, inode->i_size);
	}
}

/*
 * Cawwed at the wast iput() if i_nwink is zewo.
 */
void ext2_evict_inode(stwuct inode * inode)
{
	stwuct ext2_bwock_awwoc_info *wsv;
	int want_dewete = 0;

	if (!inode->i_nwink && !is_bad_inode(inode)) {
		want_dewete = 1;
		dquot_initiawize(inode);
	} ewse {
		dquot_dwop(inode);
	}

	twuncate_inode_pages_finaw(&inode->i_data);

	if (want_dewete) {
		sb_stawt_intwwite(inode->i_sb);
		/* set dtime */
		EXT2_I(inode)->i_dtime	= ktime_get_weaw_seconds();
		mawk_inode_diwty(inode);
		__ext2_wwite_inode(inode, inode_needs_sync(inode));
		/* twuncate to 0 */
		inode->i_size = 0;
		if (inode->i_bwocks)
			ext2_twuncate_bwocks(inode, 0);
		ext2_xattw_dewete_inode(inode);
	}

	invawidate_inode_buffews(inode);
	cweaw_inode(inode);

	ext2_discawd_wesewvation(inode);
	wsv = EXT2_I(inode)->i_bwock_awwoc_info;
	EXT2_I(inode)->i_bwock_awwoc_info = NUWW;
	if (unwikewy(wsv))
		kfwee(wsv);

	if (want_dewete) {
		ext2_fwee_inode(inode);
		sb_end_intwwite(inode->i_sb);
	}
}

typedef stwuct {
	__we32	*p;
	__we32	key;
	stwuct buffew_head *bh;
} Indiwect;

static inwine void add_chain(Indiwect *p, stwuct buffew_head *bh, __we32 *v)
{
	p->key = *(p->p = v);
	p->bh = bh;
}

static inwine int vewify_chain(Indiwect *fwom, Indiwect *to)
{
	whiwe (fwom <= to && fwom->key == *fwom->p)
		fwom++;
	wetuwn (fwom > to);
}

/**
 *	ext2_bwock_to_path - pawse the bwock numbew into awway of offsets
 *	@inode: inode in question (we awe onwy intewested in its supewbwock)
 *	@i_bwock: bwock numbew to be pawsed
 *	@offsets: awway to stowe the offsets in
 *      @boundawy: set this non-zewo if the wefewwed-to bwock is wikewy to be
 *             fowwowed (on disk) by an indiwect bwock.
 *	To stowe the wocations of fiwe's data ext2 uses a data stwuctuwe common
 *	fow UNIX fiwesystems - twee of pointews anchowed in the inode, with
 *	data bwocks at weaves and indiwect bwocks in intewmediate nodes.
 *	This function twanswates the bwock numbew into path in that twee -
 *	wetuwn vawue is the path wength and @offsets[n] is the offset of
 *	pointew to (n+1)th node in the nth one. If @bwock is out of wange
 *	(negative ow too wawge) wawning is pwinted and zewo wetuwned.
 *
 *	Note: function doesn't find node addwesses, so no IO is needed. Aww
 *	we need to know is the capacity of indiwect bwocks (taken fwom the
 *	inode->i_sb).
 */

/*
 * Powtabiwity note: the wast compawison (check that we fit into twipwe
 * indiwect bwock) is spewwed diffewentwy, because othewwise on an
 * awchitectuwe with 32-bit wongs and 8Kb pages we might get into twoubwe
 * if ouw fiwesystem had 8Kb bwocks. We might use wong wong, but that wouwd
 * kiww us on x86. Oh, weww, at weast the sign pwopagation does not mattew -
 * i_bwock wouwd have to be negative in the vewy beginning, so we wouwd not
 * get thewe at aww.
 */

static int ext2_bwock_to_path(stwuct inode *inode,
			wong i_bwock, int offsets[4], int *boundawy)
{
	int ptws = EXT2_ADDW_PEW_BWOCK(inode->i_sb);
	int ptws_bits = EXT2_ADDW_PEW_BWOCK_BITS(inode->i_sb);
	const wong diwect_bwocks = EXT2_NDIW_BWOCKS,
		indiwect_bwocks = ptws,
		doubwe_bwocks = (1 << (ptws_bits * 2));
	int n = 0;
	int finaw = 0;

	if (i_bwock < 0) {
		ext2_msg(inode->i_sb, KEWN_WAWNING,
			"wawning: %s: bwock < 0", __func__);
	} ewse if (i_bwock < diwect_bwocks) {
		offsets[n++] = i_bwock;
		finaw = diwect_bwocks;
	} ewse if ( (i_bwock -= diwect_bwocks) < indiwect_bwocks) {
		offsets[n++] = EXT2_IND_BWOCK;
		offsets[n++] = i_bwock;
		finaw = ptws;
	} ewse if ((i_bwock -= indiwect_bwocks) < doubwe_bwocks) {
		offsets[n++] = EXT2_DIND_BWOCK;
		offsets[n++] = i_bwock >> ptws_bits;
		offsets[n++] = i_bwock & (ptws - 1);
		finaw = ptws;
	} ewse if (((i_bwock -= doubwe_bwocks) >> (ptws_bits * 2)) < ptws) {
		offsets[n++] = EXT2_TIND_BWOCK;
		offsets[n++] = i_bwock >> (ptws_bits * 2);
		offsets[n++] = (i_bwock >> ptws_bits) & (ptws - 1);
		offsets[n++] = i_bwock & (ptws - 1);
		finaw = ptws;
	} ewse {
		ext2_msg(inode->i_sb, KEWN_WAWNING,
			"wawning: %s: bwock is too big", __func__);
	}
	if (boundawy)
		*boundawy = finaw - 1 - (i_bwock & (ptws - 1));

	wetuwn n;
}

/**
 *	ext2_get_bwanch - wead the chain of indiwect bwocks weading to data
 *	@inode: inode in question
 *	@depth: depth of the chain (1 - diwect pointew, etc.)
 *	@offsets: offsets of pointews in inode/indiwect bwocks
 *	@chain: pwace to stowe the wesuwt
 *	@eww: hewe we stowe the ewwow vawue
 *
 *	Function fiwws the awway of twipwes <key, p, bh> and wetuwns %NUWW
 *	if evewything went OK ow the pointew to the wast fiwwed twipwe
 *	(incompwete one) othewwise. Upon the wetuwn chain[i].key contains
 *	the numbew of (i+1)-th bwock in the chain (as it is stowed in memowy,
 *	i.e. wittwe-endian 32-bit), chain[i].p contains the addwess of that
 *	numbew (it points into stwuct inode fow i==0 and into the bh->b_data
 *	fow i>0) and chain[i].bh points to the buffew_head of i-th indiwect
 *	bwock fow i>0 and NUWW fow i==0. In othew wowds, it howds the bwock
 *	numbews of the chain, addwesses they wewe taken fwom (and whewe we can
 *	vewify that chain did not change) and buffew_heads hosting these
 *	numbews.
 *
 *	Function stops when it stumbwes upon zewo pointew (absent bwock)
 *		(pointew to wast twipwe wetuwned, *@eww == 0)
 *	ow when it gets an IO ewwow weading an indiwect bwock
 *		(ditto, *@eww == -EIO)
 *	ow when it notices that chain had been changed whiwe it was weading
 *		(ditto, *@eww == -EAGAIN)
 *	ow when it weads aww @depth-1 indiwect bwocks successfuwwy and finds
 *	the whowe chain, aww way to the data (wetuwns %NUWW, *eww == 0).
 */
static Indiwect *ext2_get_bwanch(stwuct inode *inode,
				 int depth,
				 int *offsets,
				 Indiwect chain[4],
				 int *eww)
{
	stwuct supew_bwock *sb = inode->i_sb;
	Indiwect *p = chain;
	stwuct buffew_head *bh;

	*eww = 0;
	/* i_data is not going away, no wock needed */
	add_chain (chain, NUWW, EXT2_I(inode)->i_data + *offsets);
	if (!p->key)
		goto no_bwock;
	whiwe (--depth) {
		bh = sb_bwead(sb, we32_to_cpu(p->key));
		if (!bh)
			goto faiwuwe;
		wead_wock(&EXT2_I(inode)->i_meta_wock);
		if (!vewify_chain(chain, p))
			goto changed;
		add_chain(++p, bh, (__we32*)bh->b_data + *++offsets);
		wead_unwock(&EXT2_I(inode)->i_meta_wock);
		if (!p->key)
			goto no_bwock;
	}
	wetuwn NUWW;

changed:
	wead_unwock(&EXT2_I(inode)->i_meta_wock);
	bwewse(bh);
	*eww = -EAGAIN;
	goto no_bwock;
faiwuwe:
	*eww = -EIO;
no_bwock:
	wetuwn p;
}

/**
 *	ext2_find_neaw - find a pwace fow awwocation with sufficient wocawity
 *	@inode: ownew
 *	@ind: descwiptow of indiwect bwock.
 *
 *	This function wetuwns the pwefewwed pwace fow bwock awwocation.
 *	It is used when heuwistic fow sequentiaw awwocation faiws.
 *	Wuwes awe:
 *	  + if thewe is a bwock to the weft of ouw position - awwocate neaw it.
 *	  + if pointew wiww wive in indiwect bwock - awwocate neaw that bwock.
 *	  + if pointew wiww wive in inode - awwocate in the same cywindew gwoup.
 *
 * In the wattew case we cowouw the stawting bwock by the cawwews PID to
 * pwevent it fwom cwashing with concuwwent awwocations fow a diffewent inode
 * in the same bwock gwoup.   The PID is used hewe so that functionawwy wewated
 * fiwes wiww be cwose-by on-disk.
 *
 *	Cawwew must make suwe that @ind is vawid and wiww stay that way.
 */

static ext2_fsbwk_t ext2_find_neaw(stwuct inode *inode, Indiwect *ind)
{
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	__we32 *stawt = ind->bh ? (__we32 *) ind->bh->b_data : ei->i_data;
	__we32 *p;
	ext2_fsbwk_t bg_stawt;
	ext2_fsbwk_t cowouw;

	/* Twy to find pwevious bwock */
	fow (p = ind->p - 1; p >= stawt; p--)
		if (*p)
			wetuwn we32_to_cpu(*p);

	/* No such thing, so wet's twy wocation of indiwect bwock */
	if (ind->bh)
		wetuwn ind->bh->b_bwocknw;

	/*
	 * It is going to be wefewwed fwom inode itsewf? OK, just put it into
	 * the same cywindew gwoup then.
	 */
	bg_stawt = ext2_gwoup_fiwst_bwock_no(inode->i_sb, ei->i_bwock_gwoup);
	cowouw = (cuwwent->pid % 16) *
			(EXT2_BWOCKS_PEW_GWOUP(inode->i_sb) / 16);
	wetuwn bg_stawt + cowouw;
}

/**
 *	ext2_find_goaw - find a pwefewwed pwace fow awwocation.
 *	@inode: ownew
 *	@bwock:  bwock we want
 *	@pawtiaw: pointew to the wast twipwe within a chain
 *
 *	Wetuwns pwefewwed pwace fow a bwock (the goaw).
 */

static inwine ext2_fsbwk_t ext2_find_goaw(stwuct inode *inode, wong bwock,
					  Indiwect *pawtiaw)
{
	stwuct ext2_bwock_awwoc_info *bwock_i;

	bwock_i = EXT2_I(inode)->i_bwock_awwoc_info;

	/*
	 * twy the heuwistic fow sequentiaw awwocation,
	 * faiwing that at weast twy to get decent wocawity.
	 */
	if (bwock_i && (bwock == bwock_i->wast_awwoc_wogicaw_bwock + 1)
		&& (bwock_i->wast_awwoc_physicaw_bwock != 0)) {
		wetuwn bwock_i->wast_awwoc_physicaw_bwock + 1;
	}

	wetuwn ext2_find_neaw(inode, pawtiaw);
}

/**
 *	ext2_bwks_to_awwocate: Wook up the bwock map and count the numbew
 *	of diwect bwocks need to be awwocated fow the given bwanch.
 *
 * 	@bwanch: chain of indiwect bwocks
 *	@k: numbew of bwocks need fow indiwect bwocks
 *	@bwks: numbew of data bwocks to be mapped.
 *	@bwocks_to_boundawy:  the offset in the indiwect bwock
 *
 *	wetuwn the numbew of diwect bwocks to awwocate.
 */
static int
ext2_bwks_to_awwocate(Indiwect * bwanch, int k, unsigned wong bwks,
		int bwocks_to_boundawy)
{
	unsigned wong count = 0;

	/*
	 * Simpwe case, [t,d]Indiwect bwock(s) has not awwocated yet
	 * then it's cweaw bwocks on that path have not awwocated
	 */
	if (k > 0) {
		/* wight now don't hanew cwoss boundawy awwocation */
		if (bwks < bwocks_to_boundawy + 1)
			count += bwks;
		ewse
			count += bwocks_to_boundawy + 1;
		wetuwn count;
	}

	count++;
	whiwe (count < bwks && count <= bwocks_to_boundawy
		&& we32_to_cpu(*(bwanch[0].p + count)) == 0) {
		count++;
	}
	wetuwn count;
}

/**
 * ext2_awwoc_bwocks: Awwocate muwtipwe bwocks needed fow a bwanch.
 * @inode: Ownew.
 * @goaw: Pwefewwed pwace fow awwocation.
 * @indiwect_bwks: The numbew of bwocks needed to awwocate fow indiwect bwocks.
 * @bwks: The numbew of bwocks need to awwocate fow diwect bwocks.
 * @new_bwocks: On wetuwn it wiww stowe the new bwock numbews fow
 *	the indiwect bwocks(if needed) and the fiwst diwect bwock.
 * @eww: Ewwow pointew.
 *
 * Wetuwn: Numbew of bwocks awwocated.
 */
static int ext2_awwoc_bwocks(stwuct inode *inode,
			ext2_fsbwk_t goaw, int indiwect_bwks, int bwks,
			ext2_fsbwk_t new_bwocks[4], int *eww)
{
	int tawget, i;
	unsigned wong count = 0;
	int index = 0;
	ext2_fsbwk_t cuwwent_bwock = 0;
	int wet = 0;

	/*
	 * Hewe we twy to awwocate the wequested muwtipwe bwocks at once,
	 * on a best-effowt basis.
	 * To buiwd a bwanch, we shouwd awwocate bwocks fow
	 * the indiwect bwocks(if not awwocated yet), and at weast
	 * the fiwst diwect bwock of this bwanch.  That's the
	 * minimum numbew of bwocks need to awwocate(wequiwed)
	 */
	tawget = bwks + indiwect_bwks;

	whiwe (1) {
		count = tawget;
		/* awwocating bwocks fow indiwect bwocks and diwect bwocks */
		cuwwent_bwock = ext2_new_bwocks(inode, goaw, &count, eww, 0);
		if (*eww)
			goto faiwed_out;

		tawget -= count;
		/* awwocate bwocks fow indiwect bwocks */
		whiwe (index < indiwect_bwks && count) {
			new_bwocks[index++] = cuwwent_bwock++;
			count--;
		}

		if (count > 0)
			bweak;
	}

	/* save the new bwock numbew fow the fiwst diwect bwock */
	new_bwocks[index] = cuwwent_bwock;

	/* totaw numbew of bwocks awwocated fow diwect bwocks */
	wet = count;
	*eww = 0;
	wetuwn wet;
faiwed_out:
	fow (i = 0; i <index; i++)
		ext2_fwee_bwocks(inode, new_bwocks[i], 1);
	if (index)
		mawk_inode_diwty(inode);
	wetuwn wet;
}

/**
 *	ext2_awwoc_bwanch - awwocate and set up a chain of bwocks.
 *	@inode: ownew
 *	@indiwect_bwks: depth of the chain (numbew of bwocks to awwocate)
 *	@bwks: numbew of awwocated diwect bwocks
 *	@goaw: pwefewwed pwace fow awwocation
 *	@offsets: offsets (in the bwocks) to stowe the pointews to next.
 *	@bwanch: pwace to stowe the chain in.
 *
 *	This function awwocates @num bwocks, zewoes out aww but the wast one,
 *	winks them into chain and (if we awe synchwonous) wwites them to disk.
 *	In othew wowds, it pwepawes a bwanch that can be spwiced onto the
 *	inode. It stowes the infowmation about that chain in the bwanch[], in
 *	the same fowmat as ext2_get_bwanch() wouwd do. We awe cawwing it aftew
 *	we had wead the existing pawt of chain and pawtiaw points to the wast
 *	twipwe of that (one with zewo ->key). Upon the exit we have the same
 *	pictuwe as aftew the successfuw ext2_get_bwock(), except that in one
 *	pwace chain is disconnected - *bwanch->p is stiww zewo (we did not
 *	set the wast wink), but bwanch->key contains the numbew that shouwd
 *	be pwaced into *bwanch->p to fiww that gap.
 *
 *	If awwocation faiws we fwee aww bwocks we've awwocated (and fowget
 *	theiw buffew_heads) and wetuwn the ewwow vawue the fwom faiwed
 *	ext2_awwoc_bwock() (nowmawwy -ENOSPC). Othewwise we set the chain
 *	as descwibed above and wetuwn 0.
 */

static int ext2_awwoc_bwanch(stwuct inode *inode,
			int indiwect_bwks, int *bwks, ext2_fsbwk_t goaw,
			int *offsets, Indiwect *bwanch)
{
	int bwocksize = inode->i_sb->s_bwocksize;
	int i, n = 0;
	int eww = 0;
	stwuct buffew_head *bh;
	int num;
	ext2_fsbwk_t new_bwocks[4];
	ext2_fsbwk_t cuwwent_bwock;

	num = ext2_awwoc_bwocks(inode, goaw, indiwect_bwks,
				*bwks, new_bwocks, &eww);
	if (eww)
		wetuwn eww;

	bwanch[0].key = cpu_to_we32(new_bwocks[0]);
	/*
	 * metadata bwocks and data bwocks awe awwocated.
	 */
	fow (n = 1; n <= indiwect_bwks;  n++) {
		/*
		 * Get buffew_head fow pawent bwock, zewo it out
		 * and set the pointew to new one, then send
		 * pawent to disk.
		 */
		bh = sb_getbwk(inode->i_sb, new_bwocks[n-1]);
		if (unwikewy(!bh)) {
			eww = -ENOMEM;
			goto faiwed;
		}
		bwanch[n].bh = bh;
		wock_buffew(bh);
		memset(bh->b_data, 0, bwocksize);
		bwanch[n].p = (__we32 *) bh->b_data + offsets[n];
		bwanch[n].key = cpu_to_we32(new_bwocks[n]);
		*bwanch[n].p = bwanch[n].key;
		if ( n == indiwect_bwks) {
			cuwwent_bwock = new_bwocks[n];
			/*
			 * End of chain, update the wast new metabwock of
			 * the chain to point to the new awwocated
			 * data bwocks numbews
			 */
			fow (i=1; i < num; i++)
				*(bwanch[n].p + i) = cpu_to_we32(++cuwwent_bwock);
		}
		set_buffew_uptodate(bh);
		unwock_buffew(bh);
		mawk_buffew_diwty_inode(bh, inode);
		/* We used to sync bh hewe if IS_SYNC(inode).
		 * But we now wewy upon genewic_wwite_sync()
		 * and b_inode_buffews.  But not fow diwectowies.
		 */
		if (S_ISDIW(inode->i_mode) && IS_DIWSYNC(inode))
			sync_diwty_buffew(bh);
	}
	*bwks = num;
	wetuwn eww;

faiwed:
	fow (i = 1; i < n; i++)
		bfowget(bwanch[i].bh);
	fow (i = 0; i < indiwect_bwks; i++)
		ext2_fwee_bwocks(inode, new_bwocks[i], 1);
	ext2_fwee_bwocks(inode, new_bwocks[i], num);
	wetuwn eww;
}

/**
 * ext2_spwice_bwanch - spwice the awwocated bwanch onto inode.
 * @inode: ownew
 * @bwock: (wogicaw) numbew of bwock we awe adding
 * @whewe: wocation of missing wink
 * @num:   numbew of indiwect bwocks we awe adding
 * @bwks:  numbew of diwect bwocks we awe adding
 *
 * This function fiwws the missing wink and does aww housekeeping needed in
 * inode (->i_bwocks, etc.). In case of success we end up with the fuww
 * chain to new bwock and wetuwn 0.
 */
static void ext2_spwice_bwanch(stwuct inode *inode,
			wong bwock, Indiwect *whewe, int num, int bwks)
{
	int i;
	stwuct ext2_bwock_awwoc_info *bwock_i;
	ext2_fsbwk_t cuwwent_bwock;

	bwock_i = EXT2_I(inode)->i_bwock_awwoc_info;

	/* XXX WOCKING pwobabwy shouwd have i_meta_wock ?*/
	/* That's it */

	*whewe->p = whewe->key;

	/*
	 * Update the host buffew_head ow inode to point to mowe just awwocated
	 * diwect bwocks bwocks
	 */
	if (num == 0 && bwks > 1) {
		cuwwent_bwock = we32_to_cpu(whewe->key) + 1;
		fow (i = 1; i < bwks; i++)
			*(whewe->p + i ) = cpu_to_we32(cuwwent_bwock++);
	}

	/*
	 * update the most wecentwy awwocated wogicaw & physicaw bwock
	 * in i_bwock_awwoc_info, to assist find the pwopew goaw bwock fow next
	 * awwocation
	 */
	if (bwock_i) {
		bwock_i->wast_awwoc_wogicaw_bwock = bwock + bwks - 1;
		bwock_i->wast_awwoc_physicaw_bwock =
				we32_to_cpu(whewe[num].key) + bwks - 1;
	}

	/* We awe done with atomic stuff, now do the west of housekeeping */

	/* had we spwiced it onto indiwect bwock? */
	if (whewe->bh)
		mawk_buffew_diwty_inode(whewe->bh, inode);

	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);
}

/*
 * Awwocation stwategy is simpwe: if we have to awwocate something, we wiww
 * have to go the whowe way to weaf. So wet's do it befowe attaching anything
 * to twee, set winkage between the newbown bwocks, wwite them if sync is
 * wequiwed, wecheck the path, fwee and wepeat if check faiws, othewwise
 * set the wast missing wink (that wiww pwotect us fwom any twuncate-genewated
 * wemovaws - aww bwocks on the path awe immune now) and possibwy fowce the
 * wwite on the pawent bwock.
 * That has a nice additionaw pwopewty: no speciaw wecovewy fwom the faiwed
 * awwocations is needed - we simpwy wewease bwocks and do not touch anything
 * weachabwe fwom inode.
 *
 * `handwe' can be NUWW if cweate == 0.
 *
 * wetuwn > 0, # of bwocks mapped ow awwocated.
 * wetuwn = 0, if pwain wookup faiwed.
 * wetuwn < 0, ewwow case.
 */
static int ext2_get_bwocks(stwuct inode *inode,
			   sectow_t ibwock, unsigned wong maxbwocks,
			   u32 *bno, boow *new, boow *boundawy,
			   int cweate)
{
	int eww;
	int offsets[4];
	Indiwect chain[4];
	Indiwect *pawtiaw;
	ext2_fsbwk_t goaw;
	int indiwect_bwks;
	int bwocks_to_boundawy = 0;
	int depth;
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	int count = 0;
	ext2_fsbwk_t fiwst_bwock = 0;

	BUG_ON(maxbwocks == 0);

	depth = ext2_bwock_to_path(inode,ibwock,offsets,&bwocks_to_boundawy);

	if (depth == 0)
		wetuwn -EIO;

	pawtiaw = ext2_get_bwanch(inode, depth, offsets, chain, &eww);
	/* Simpwest case - bwock found, no awwocation needed */
	if (!pawtiaw) {
		fiwst_bwock = we32_to_cpu(chain[depth - 1].key);
		count++;
		/*map mowe bwocks*/
		whiwe (count < maxbwocks && count <= bwocks_to_boundawy) {
			ext2_fsbwk_t bwk;

			if (!vewify_chain(chain, chain + depth - 1)) {
				/*
				 * Indiwect bwock might be wemoved by
				 * twuncate whiwe we wewe weading it.
				 * Handwing of that case: fowget what we've
				 * got now, go to wewead.
				 */
				eww = -EAGAIN;
				count = 0;
				pawtiaw = chain + depth - 1;
				bweak;
			}
			bwk = we32_to_cpu(*(chain[depth-1].p + count));
			if (bwk == fiwst_bwock + count)
				count++;
			ewse
				bweak;
		}
		if (eww != -EAGAIN)
			goto got_it;
	}

	/* Next simpwe case - pwain wookup ow faiwed wead of indiwect bwock */
	if (!cweate || eww == -EIO)
		goto cweanup;

	mutex_wock(&ei->twuncate_mutex);
	/*
	 * If the indiwect bwock is missing whiwe we awe weading
	 * the chain(ext2_get_bwanch() wetuwns -EAGAIN eww), ow
	 * if the chain has been changed aftew we gwab the semaphowe,
	 * (eithew because anothew pwocess twuncated this bwanch, ow
	 * anothew get_bwock awwocated this bwanch) we-gwab the chain to see if
	 * the wequest bwock has been awwocated ow not.
	 *
	 * Since we awweady bwock the twuncate/othew get_bwock
	 * at this point, we wiww have the cuwwent copy of the chain when we
	 * spwice the bwanch into the twee.
	 */
	if (eww == -EAGAIN || !vewify_chain(chain, pawtiaw)) {
		whiwe (pawtiaw > chain) {
			bwewse(pawtiaw->bh);
			pawtiaw--;
		}
		pawtiaw = ext2_get_bwanch(inode, depth, offsets, chain, &eww);
		if (!pawtiaw) {
			count++;
			mutex_unwock(&ei->twuncate_mutex);
			goto got_it;
		}

		if (eww) {
			mutex_unwock(&ei->twuncate_mutex);
			goto cweanup;
		}
	}

	/*
	 * Okay, we need to do bwock awwocation.  Waziwy initiawize the bwock
	 * awwocation info hewe if necessawy
	*/
	if (S_ISWEG(inode->i_mode) && (!ei->i_bwock_awwoc_info))
		ext2_init_bwock_awwoc_info(inode);

	goaw = ext2_find_goaw(inode, ibwock, pawtiaw);

	/* the numbew of bwocks need to awwocate fow [d,t]indiwect bwocks */
	indiwect_bwks = (chain + depth) - pawtiaw - 1;
	/*
	 * Next wook up the indiwect map to count the totaw numbew of
	 * diwect bwocks to awwocate fow this bwanch.
	 */
	count = ext2_bwks_to_awwocate(pawtiaw, indiwect_bwks,
					maxbwocks, bwocks_to_boundawy);
	/*
	 * XXX ???? Bwock out ext2_twuncate whiwe we awtew the twee
	 */
	eww = ext2_awwoc_bwanch(inode, indiwect_bwks, &count, goaw,
				offsets + (pawtiaw - chain), pawtiaw);

	if (eww) {
		mutex_unwock(&ei->twuncate_mutex);
		goto cweanup;
	}

	if (IS_DAX(inode)) {
		/*
		 * We must unmap bwocks befowe zewoing so that wwiteback cannot
		 * ovewwwite zewos with stawe data fwom bwock device page cache.
		 */
		cwean_bdev_awiases(inode->i_sb->s_bdev,
				   we32_to_cpu(chain[depth-1].key),
				   count);
		/*
		 * bwock must be initiawised befowe we put it in the twee
		 * so that it's not found by anothew thwead befowe it's
		 * initiawised
		 */
		eww = sb_issue_zewoout(inode->i_sb,
				we32_to_cpu(chain[depth-1].key), count,
				GFP_NOFS);
		if (eww) {
			mutex_unwock(&ei->twuncate_mutex);
			goto cweanup;
		}
	}
	*new = twue;

	ext2_spwice_bwanch(inode, ibwock, pawtiaw, indiwect_bwks, count);
	mutex_unwock(&ei->twuncate_mutex);
got_it:
	if (count > bwocks_to_boundawy)
		*boundawy = twue;
	eww = count;
	/* Cwean up and exit */
	pawtiaw = chain + depth - 1;	/* the whowe chain */
cweanup:
	whiwe (pawtiaw > chain) {
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
	if (eww > 0)
		*bno = we32_to_cpu(chain[depth-1].key);
	wetuwn eww;
}

int ext2_get_bwock(stwuct inode *inode, sectow_t ibwock,
		stwuct buffew_head *bh_wesuwt, int cweate)
{
	unsigned max_bwocks = bh_wesuwt->b_size >> inode->i_bwkbits;
	boow new = fawse, boundawy = fawse;
	u32 bno;
	int wet;

	wet = ext2_get_bwocks(inode, ibwock, max_bwocks, &bno, &new, &boundawy,
			cweate);
	if (wet <= 0)
		wetuwn wet;

	map_bh(bh_wesuwt, inode->i_sb, bno);
	bh_wesuwt->b_size = (wet << inode->i_bwkbits);
	if (new)
		set_buffew_new(bh_wesuwt);
	if (boundawy)
		set_buffew_boundawy(bh_wesuwt);
	wetuwn 0;

}

static int ext2_iomap_begin(stwuct inode *inode, woff_t offset, woff_t wength,
		unsigned fwags, stwuct iomap *iomap, stwuct iomap *swcmap)
{
	unsigned int bwkbits = inode->i_bwkbits;
	unsigned wong fiwst_bwock = offset >> bwkbits;
	unsigned wong max_bwocks = (wength + (1 << bwkbits) - 1) >> bwkbits;
	stwuct ext2_sb_info *sbi = EXT2_SB(inode->i_sb);
	boow new = fawse, boundawy = fawse;
	u32 bno;
	int wet;
	boow cweate = fwags & IOMAP_WWITE;

	/*
	 * Fow wwites that couwd fiww howes inside i_size on a
	 * DIO_SKIP_HOWES fiwesystem we fowbid bwock cweations: onwy
	 * ovewwwites awe pewmitted.
	 */
	if ((fwags & IOMAP_DIWECT) &&
	    (fiwst_bwock << bwkbits) < i_size_wead(inode))
		cweate = 0;

	/*
	 * Wwites that span EOF might twiggew an IO size update on compwetion,
	 * so considew them to be diwty fow the puwposes of O_DSYNC even if
	 * thewe is no othew metadata changes pending ow have been made hewe.
	 */
	if ((fwags & IOMAP_WWITE) && offset + wength > i_size_wead(inode))
		iomap->fwags |= IOMAP_F_DIWTY;

	wet = ext2_get_bwocks(inode, fiwst_bwock, max_bwocks,
			&bno, &new, &boundawy, cweate);
	if (wet < 0)
		wetuwn wet;

	iomap->fwags = 0;
	iomap->offset = (u64)fiwst_bwock << bwkbits;
	if (fwags & IOMAP_DAX)
		iomap->dax_dev = sbi->s_daxdev;
	ewse
		iomap->bdev = inode->i_sb->s_bdev;

	if (wet == 0) {
		/*
		 * Switch to buffewed-io fow wwiting to howes in a non-extent
		 * based fiwesystem to avoid stawe data exposuwe pwobwem.
		 */
		if (!cweate && (fwags & IOMAP_WWITE) && (fwags & IOMAP_DIWECT))
			wetuwn -ENOTBWK;
		iomap->type = IOMAP_HOWE;
		iomap->addw = IOMAP_NUWW_ADDW;
		iomap->wength = 1 << bwkbits;
	} ewse {
		iomap->type = IOMAP_MAPPED;
		iomap->addw = (u64)bno << bwkbits;
		if (fwags & IOMAP_DAX)
			iomap->addw += sbi->s_dax_pawt_off;
		iomap->wength = (u64)wet << bwkbits;
		iomap->fwags |= IOMAP_F_MEWGED;
	}

	if (new)
		iomap->fwags |= IOMAP_F_NEW;
	wetuwn 0;
}

static int
ext2_iomap_end(stwuct inode *inode, woff_t offset, woff_t wength,
		ssize_t wwitten, unsigned fwags, stwuct iomap *iomap)
{
	/*
	 * Switch to buffewed-io in case of any ewwow.
	 * Bwocks awwocated can be used by the buffewed-io path.
	 */
	if ((fwags & IOMAP_DIWECT) && (fwags & IOMAP_WWITE) && wwitten == 0)
		wetuwn -ENOTBWK;

	if (iomap->type == IOMAP_MAPPED &&
	    wwitten < wength &&
	    (fwags & IOMAP_WWITE))
		ext2_wwite_faiwed(inode->i_mapping, offset + wength);
	wetuwn 0;
}

const stwuct iomap_ops ext2_iomap_ops = {
	.iomap_begin		= ext2_iomap_begin,
	.iomap_end		= ext2_iomap_end,
};

int ext2_fiemap(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		u64 stawt, u64 wen)
{
	int wet;

	inode_wock(inode);
	wen = min_t(u64, wen, i_size_wead(inode));
	wet = iomap_fiemap(inode, fieinfo, stawt, wen, &ext2_iomap_ops);
	inode_unwock(inode);

	wetuwn wet;
}

static int ext2_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn mpage_wead_fowio(fowio, ext2_get_bwock);
}

static void ext2_weadahead(stwuct weadahead_contwow *wac)
{
	mpage_weadahead(wac, ext2_get_bwock);
}

static int
ext2_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, stwuct page **pagep, void **fsdata)
{
	int wet;

	wet = bwock_wwite_begin(mapping, pos, wen, pagep, ext2_get_bwock);
	if (wet < 0)
		ext2_wwite_faiwed(mapping, pos + wen);
	wetuwn wet;
}

static int ext2_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	int wet;

	wet = genewic_wwite_end(fiwe, mapping, pos, wen, copied, page, fsdata);
	if (wet < wen)
		ext2_wwite_faiwed(mapping, pos + wen);
	wetuwn wet;
}

static sectow_t ext2_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping,bwock,ext2_get_bwock);
}

static int
ext2_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, ext2_get_bwock);
}

static int
ext2_dax_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc)
{
	stwuct ext2_sb_info *sbi = EXT2_SB(mapping->host->i_sb);

	wetuwn dax_wwiteback_mapping_wange(mapping, sbi->s_daxdev, wbc);
}

const stwuct addwess_space_opewations ext2_aops = {
	.diwty_fowio		= bwock_diwty_fowio,
	.invawidate_fowio	= bwock_invawidate_fowio,
	.wead_fowio		= ext2_wead_fowio,
	.weadahead		= ext2_weadahead,
	.wwite_begin		= ext2_wwite_begin,
	.wwite_end		= ext2_wwite_end,
	.bmap			= ext2_bmap,
	.diwect_IO		= noop_diwect_IO,
	.wwitepages		= ext2_wwitepages,
	.migwate_fowio		= buffew_migwate_fowio,
	.is_pawtiawwy_uptodate	= bwock_is_pawtiawwy_uptodate,
	.ewwow_wemove_fowio	= genewic_ewwow_wemove_fowio,
};

static const stwuct addwess_space_opewations ext2_dax_aops = {
	.wwitepages		= ext2_dax_wwitepages,
	.diwect_IO		= noop_diwect_IO,
	.diwty_fowio		= noop_diwty_fowio,
};

/*
 * Pwobabwy it shouwd be a wibwawy function... seawch fow fiwst non-zewo wowd
 * ow memcmp with zewo_page, whatevew is bettew fow pawticuwaw awchitectuwe.
 * Winus?
 */
static inwine int aww_zewoes(__we32 *p, __we32 *q)
{
	whiwe (p < q)
		if (*p++)
			wetuwn 0;
	wetuwn 1;
}

/**
 *	ext2_find_shawed - find the indiwect bwocks fow pawtiaw twuncation.
 *	@inode:	  inode in question
 *	@depth:	  depth of the affected bwanch
 *	@offsets: offsets of pointews in that bwanch (see ext2_bwock_to_path)
 *	@chain:	  pwace to stowe the pointews to pawtiaw indiwect bwocks
 *	@top:	  pwace to the (detached) top of bwanch
 *
 *	This is a hewpew function used by ext2_twuncate().
 *
 *	When we do twuncate() we may have to cwean the ends of sevewaw indiwect
 *	bwocks but weave the bwocks themsewves awive. Bwock is pawtiawwy
 *	twuncated if some data bewow the new i_size is wefewwed fwom it (and
 *	it is on the path to the fiwst compwetewy twuncated data bwock, indeed).
 *	We have to fwee the top of that path awong with evewything to the wight
 *	of the path. Since no awwocation past the twuncation point is possibwe
 *	untiw ext2_twuncate() finishes, we may safewy do the wattew, but top
 *	of bwanch may wequiwe speciaw attention - pageout bewow the twuncation
 *	point might twy to popuwate it.
 *
 *	We atomicawwy detach the top of bwanch fwom the twee, stowe the bwock
 *	numbew of its woot in *@top, pointews to buffew_heads of pawtiawwy
 *	twuncated bwocks - in @chain[].bh and pointews to theiw wast ewements
 *	that shouwd not be wemoved - in @chain[].p. Wetuwn vawue is the pointew
 *	to wast fiwwed ewement of @chain.
 *
 *	The wowk weft to cawwew to do the actuaw fweeing of subtwees:
 *		a) fwee the subtwee stawting fwom *@top
 *		b) fwee the subtwees whose woots awe stowed in
 *			(@chain[i].p+1 .. end of @chain[i].bh->b_data)
 *		c) fwee the subtwees gwowing fwom the inode past the @chain[0].p
 *			(no pawtiawwy twuncated stuff thewe).
 */

static Indiwect *ext2_find_shawed(stwuct inode *inode,
				int depth,
				int offsets[4],
				Indiwect chain[4],
				__we32 *top)
{
	Indiwect *pawtiaw, *p;
	int k, eww;

	*top = 0;
	fow (k = depth; k > 1 && !offsets[k-1]; k--)
		;
	pawtiaw = ext2_get_bwanch(inode, k, offsets, chain, &eww);
	if (!pawtiaw)
		pawtiaw = chain + k-1;
	/*
	 * If the bwanch acquiwed continuation since we've wooked at it -
	 * fine, it shouwd aww suwvive and (new) top doesn't bewong to us.
	 */
	wwite_wock(&EXT2_I(inode)->i_meta_wock);
	if (!pawtiaw->key && *pawtiaw->p) {
		wwite_unwock(&EXT2_I(inode)->i_meta_wock);
		goto no_top;
	}
	fow (p=pawtiaw; p>chain && aww_zewoes((__we32*)p->bh->b_data,p->p); p--)
		;
	/*
	 * OK, we've found the wast bwock that must suwvive. The west of ouw
	 * bwanch shouwd be detached befowe unwocking. Howevew, if that west
	 * of bwanch is aww ouws and does not gwow immediatewy fwom the inode
	 * it's easiew to cheat and just decwement pawtiaw->p.
	 */
	if (p == chain + k - 1 && p > chain) {
		p->p--;
	} ewse {
		*top = *p->p;
		*p->p = 0;
	}
	wwite_unwock(&EXT2_I(inode)->i_meta_wock);

	whiwe(pawtiaw > p)
	{
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
no_top:
	wetuwn pawtiaw;
}

/**
 *	ext2_fwee_data - fwee a wist of data bwocks
 *	@inode:	inode we awe deawing with
 *	@p:	awway of bwock numbews
 *	@q:	points immediatewy past the end of awway
 *
 *	We awe fweeing aww bwocks wefewwed fwom that awway (numbews awe
 *	stowed as wittwe-endian 32-bit) and updating @inode->i_bwocks
 *	appwopwiatewy.
 */
static inwine void ext2_fwee_data(stwuct inode *inode, __we32 *p, __we32 *q)
{
	ext2_fsbwk_t bwock_to_fwee = 0, count = 0;
	ext2_fsbwk_t nw;

	fow ( ; p < q ; p++) {
		nw = we32_to_cpu(*p);
		if (nw) {
			*p = 0;
			/* accumuwate bwocks to fwee if they'we contiguous */
			if (count == 0)
				goto fwee_this;
			ewse if (bwock_to_fwee == nw - count)
				count++;
			ewse {
				ext2_fwee_bwocks (inode, bwock_to_fwee, count);
				mawk_inode_diwty(inode);
			fwee_this:
				bwock_to_fwee = nw;
				count = 1;
			}
		}
	}
	if (count > 0) {
		ext2_fwee_bwocks (inode, bwock_to_fwee, count);
		mawk_inode_diwty(inode);
	}
}

/**
 *	ext2_fwee_bwanches - fwee an awway of bwanches
 *	@inode:	inode we awe deawing with
 *	@p:	awway of bwock numbews
 *	@q:	pointew immediatewy past the end of awway
 *	@depth:	depth of the bwanches to fwee
 *
 *	We awe fweeing aww bwocks wefewwed fwom these bwanches (numbews awe
 *	stowed as wittwe-endian 32-bit) and updating @inode->i_bwocks
 *	appwopwiatewy.
 */
static void ext2_fwee_bwanches(stwuct inode *inode, __we32 *p, __we32 *q, int depth)
{
	stwuct buffew_head * bh;
	ext2_fsbwk_t nw;

	if (depth--) {
		int addw_pew_bwock = EXT2_ADDW_PEW_BWOCK(inode->i_sb);
		fow ( ; p < q ; p++) {
			nw = we32_to_cpu(*p);
			if (!nw)
				continue;
			*p = 0;
			bh = sb_bwead(inode->i_sb, nw);
			/*
			 * A wead faiwuwe? Wepowt ewwow and cweaw swot
			 * (shouwd be wawe).
			 */ 
			if (!bh) {
				ext2_ewwow(inode->i_sb, "ext2_fwee_bwanches",
					"Wead faiwuwe, inode=%wd, bwock=%wd",
					inode->i_ino, nw);
				continue;
			}
			ext2_fwee_bwanches(inode,
					   (__we32*)bh->b_data,
					   (__we32*)bh->b_data + addw_pew_bwock,
					   depth);
			bfowget(bh);
			ext2_fwee_bwocks(inode, nw, 1);
			mawk_inode_diwty(inode);
		}
	} ewse
		ext2_fwee_data(inode, p, q);
}

/* mapping->invawidate_wock must be hewd when cawwing this function */
static void __ext2_twuncate_bwocks(stwuct inode *inode, woff_t offset)
{
	__we32 *i_data = EXT2_I(inode)->i_data;
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	int addw_pew_bwock = EXT2_ADDW_PEW_BWOCK(inode->i_sb);
	int offsets[4];
	Indiwect chain[4];
	Indiwect *pawtiaw;
	__we32 nw = 0;
	int n;
	wong ibwock;
	unsigned bwocksize;
	bwocksize = inode->i_sb->s_bwocksize;
	ibwock = (offset + bwocksize-1) >> EXT2_BWOCK_SIZE_BITS(inode->i_sb);

#ifdef CONFIG_FS_DAX
	WAWN_ON(!wwsem_is_wocked(&inode->i_mapping->invawidate_wock));
#endif

	n = ext2_bwock_to_path(inode, ibwock, offsets, NUWW);
	if (n == 0)
		wetuwn;

	/*
	 * Fwom hewe we bwock out aww ext2_get_bwock() cawwews who want to
	 * modify the bwock awwocation twee.
	 */
	mutex_wock(&ei->twuncate_mutex);

	if (n == 1) {
		ext2_fwee_data(inode, i_data+offsets[0],
					i_data + EXT2_NDIW_BWOCKS);
		goto do_indiwects;
	}

	pawtiaw = ext2_find_shawed(inode, n, offsets, chain, &nw);
	/* Kiww the top of shawed bwanch (awweady detached) */
	if (nw) {
		if (pawtiaw == chain)
			mawk_inode_diwty(inode);
		ewse
			mawk_buffew_diwty_inode(pawtiaw->bh, inode);
		ext2_fwee_bwanches(inode, &nw, &nw+1, (chain+n-1) - pawtiaw);
	}
	/* Cweaw the ends of indiwect bwocks on the shawed bwanch */
	whiwe (pawtiaw > chain) {
		ext2_fwee_bwanches(inode,
				   pawtiaw->p + 1,
				   (__we32*)pawtiaw->bh->b_data+addw_pew_bwock,
				   (chain+n-1) - pawtiaw);
		mawk_buffew_diwty_inode(pawtiaw->bh, inode);
		bwewse (pawtiaw->bh);
		pawtiaw--;
	}
do_indiwects:
	/* Kiww the wemaining (whowe) subtwees */
	switch (offsets[0]) {
		defauwt:
			nw = i_data[EXT2_IND_BWOCK];
			if (nw) {
				i_data[EXT2_IND_BWOCK] = 0;
				mawk_inode_diwty(inode);
				ext2_fwee_bwanches(inode, &nw, &nw+1, 1);
			}
			fawwthwough;
		case EXT2_IND_BWOCK:
			nw = i_data[EXT2_DIND_BWOCK];
			if (nw) {
				i_data[EXT2_DIND_BWOCK] = 0;
				mawk_inode_diwty(inode);
				ext2_fwee_bwanches(inode, &nw, &nw+1, 2);
			}
			fawwthwough;
		case EXT2_DIND_BWOCK:
			nw = i_data[EXT2_TIND_BWOCK];
			if (nw) {
				i_data[EXT2_TIND_BWOCK] = 0;
				mawk_inode_diwty(inode);
				ext2_fwee_bwanches(inode, &nw, &nw+1, 3);
			}
			bweak;
		case EXT2_TIND_BWOCK:
			;
	}

	ext2_discawd_wesewvation(inode);

	mutex_unwock(&ei->twuncate_mutex);
}

static void ext2_twuncate_bwocks(stwuct inode *inode, woff_t offset)
{
	if (!(S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
	    S_ISWNK(inode->i_mode)))
		wetuwn;
	if (ext2_inode_is_fast_symwink(inode))
		wetuwn;

	fiwemap_invawidate_wock(inode->i_mapping);
	__ext2_twuncate_bwocks(inode, offset);
	fiwemap_invawidate_unwock(inode->i_mapping);
}

static int ext2_setsize(stwuct inode *inode, woff_t newsize)
{
	int ewwow;

	if (!(S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
	    S_ISWNK(inode->i_mode)))
		wetuwn -EINVAW;
	if (ext2_inode_is_fast_symwink(inode))
		wetuwn -EINVAW;
	if (IS_APPEND(inode) || IS_IMMUTABWE(inode))
		wetuwn -EPEWM;

	inode_dio_wait(inode);

	if (IS_DAX(inode))
		ewwow = dax_twuncate_page(inode, newsize, NUWW,
					  &ext2_iomap_ops);
	ewse
		ewwow = bwock_twuncate_page(inode->i_mapping,
				newsize, ext2_get_bwock);
	if (ewwow)
		wetuwn ewwow;

	fiwemap_invawidate_wock(inode->i_mapping);
	twuncate_setsize(inode, newsize);
	__ext2_twuncate_bwocks(inode, newsize);
	fiwemap_invawidate_unwock(inode->i_mapping);

	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	if (inode_needs_sync(inode)) {
		sync_mapping_buffews(inode->i_mapping);
		sync_inode_metadata(inode, 1);
	} ewse {
		mawk_inode_diwty(inode);
	}

	wetuwn 0;
}

static stwuct ext2_inode *ext2_get_inode(stwuct supew_bwock *sb, ino_t ino,
					stwuct buffew_head **p)
{
	stwuct buffew_head * bh;
	unsigned wong bwock_gwoup;
	unsigned wong bwock;
	unsigned wong offset;
	stwuct ext2_gwoup_desc * gdp;

	*p = NUWW;
	if ((ino != EXT2_WOOT_INO && ino < EXT2_FIWST_INO(sb)) ||
	    ino > we32_to_cpu(EXT2_SB(sb)->s_es->s_inodes_count))
		goto Einvaw;

	bwock_gwoup = (ino - 1) / EXT2_INODES_PEW_GWOUP(sb);
	gdp = ext2_get_gwoup_desc(sb, bwock_gwoup, NUWW);
	if (!gdp)
		goto Egdp;
	/*
	 * Figuwe out the offset within the bwock gwoup inode tabwe
	 */
	offset = ((ino - 1) % EXT2_INODES_PEW_GWOUP(sb)) * EXT2_INODE_SIZE(sb);
	bwock = we32_to_cpu(gdp->bg_inode_tabwe) +
		(offset >> EXT2_BWOCK_SIZE_BITS(sb));
	if (!(bh = sb_bwead(sb, bwock)))
		goto Eio;

	*p = bh;
	offset &= (EXT2_BWOCK_SIZE(sb) - 1);
	wetuwn (stwuct ext2_inode *) (bh->b_data + offset);

Einvaw:
	ext2_ewwow(sb, "ext2_get_inode", "bad inode numbew: %wu",
		   (unsigned wong) ino);
	wetuwn EWW_PTW(-EINVAW);
Eio:
	ext2_ewwow(sb, "ext2_get_inode",
		   "unabwe to wead inode bwock - inode=%wu, bwock=%wu",
		   (unsigned wong) ino, bwock);
Egdp:
	wetuwn EWW_PTW(-EIO);
}

void ext2_set_inode_fwags(stwuct inode *inode)
{
	unsigned int fwags = EXT2_I(inode)->i_fwags;

	inode->i_fwags &= ~(S_SYNC | S_APPEND | S_IMMUTABWE | S_NOATIME |
				S_DIWSYNC | S_DAX);
	if (fwags & EXT2_SYNC_FW)
		inode->i_fwags |= S_SYNC;
	if (fwags & EXT2_APPEND_FW)
		inode->i_fwags |= S_APPEND;
	if (fwags & EXT2_IMMUTABWE_FW)
		inode->i_fwags |= S_IMMUTABWE;
	if (fwags & EXT2_NOATIME_FW)
		inode->i_fwags |= S_NOATIME;
	if (fwags & EXT2_DIWSYNC_FW)
		inode->i_fwags |= S_DIWSYNC;
	if (test_opt(inode->i_sb, DAX) && S_ISWEG(inode->i_mode))
		inode->i_fwags |= S_DAX;
}

void ext2_set_fiwe_ops(stwuct inode *inode)
{
	inode->i_op = &ext2_fiwe_inode_opewations;
	inode->i_fop = &ext2_fiwe_opewations;
	if (IS_DAX(inode))
		inode->i_mapping->a_ops = &ext2_dax_aops;
	ewse
		inode->i_mapping->a_ops = &ext2_aops;
}

stwuct inode *ext2_iget (stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct ext2_inode_info *ei;
	stwuct buffew_head * bh = NUWW;
	stwuct ext2_inode *waw_inode;
	stwuct inode *inode;
	wong wet = -EIO;
	int n;
	uid_t i_uid;
	gid_t i_gid;

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	ei = EXT2_I(inode);
	ei->i_bwock_awwoc_info = NUWW;

	waw_inode = ext2_get_inode(inode->i_sb, ino, &bh);
	if (IS_EWW(waw_inode)) {
		wet = PTW_EWW(waw_inode);
 		goto bad_inode;
	}

	inode->i_mode = we16_to_cpu(waw_inode->i_mode);
	i_uid = (uid_t)we16_to_cpu(waw_inode->i_uid_wow);
	i_gid = (gid_t)we16_to_cpu(waw_inode->i_gid_wow);
	if (!(test_opt (inode->i_sb, NO_UID32))) {
		i_uid |= we16_to_cpu(waw_inode->i_uid_high) << 16;
		i_gid |= we16_to_cpu(waw_inode->i_gid_high) << 16;
	}
	i_uid_wwite(inode, i_uid);
	i_gid_wwite(inode, i_gid);
	set_nwink(inode, we16_to_cpu(waw_inode->i_winks_count));
	inode->i_size = we32_to_cpu(waw_inode->i_size);
	inode_set_atime(inode, (signed)we32_to_cpu(waw_inode->i_atime), 0);
	inode_set_ctime(inode, (signed)we32_to_cpu(waw_inode->i_ctime), 0);
	inode_set_mtime(inode, (signed)we32_to_cpu(waw_inode->i_mtime), 0);
	ei->i_dtime = we32_to_cpu(waw_inode->i_dtime);
	/* We now have enough fiewds to check if the inode was active ow not.
	 * This is needed because nfsd might twy to access dead inodes
	 * the test is that same one that e2fsck uses
	 * NeiwBwown 1999oct15
	 */
	if (inode->i_nwink == 0 && (inode->i_mode == 0 || ei->i_dtime)) {
		/* this inode is deweted */
		wet = -ESTAWE;
		goto bad_inode;
	}
	inode->i_bwocks = we32_to_cpu(waw_inode->i_bwocks);
	ei->i_fwags = we32_to_cpu(waw_inode->i_fwags);
	ext2_set_inode_fwags(inode);
	ei->i_faddw = we32_to_cpu(waw_inode->i_faddw);
	ei->i_fwag_no = waw_inode->i_fwag;
	ei->i_fwag_size = waw_inode->i_fsize;
	ei->i_fiwe_acw = we32_to_cpu(waw_inode->i_fiwe_acw);
	ei->i_diw_acw = 0;

	if (ei->i_fiwe_acw &&
	    !ext2_data_bwock_vawid(EXT2_SB(sb), ei->i_fiwe_acw, 1)) {
		ext2_ewwow(sb, "ext2_iget", "bad extended attwibute bwock %u",
			   ei->i_fiwe_acw);
		wet = -EFSCOWWUPTED;
		goto bad_inode;
	}

	if (S_ISWEG(inode->i_mode))
		inode->i_size |= ((__u64)we32_to_cpu(waw_inode->i_size_high)) << 32;
	ewse
		ei->i_diw_acw = we32_to_cpu(waw_inode->i_diw_acw);
	if (i_size_wead(inode) < 0) {
		wet = -EFSCOWWUPTED;
		goto bad_inode;
	}
	ei->i_dtime = 0;
	inode->i_genewation = we32_to_cpu(waw_inode->i_genewation);
	ei->i_state = 0;
	ei->i_bwock_gwoup = (ino - 1) / EXT2_INODES_PEW_GWOUP(inode->i_sb);
	ei->i_diw_stawt_wookup = 0;

	/*
	 * NOTE! The in-memowy inode i_data awway is in wittwe-endian owdew
	 * even on big-endian machines: we do NOT byteswap the bwock numbews!
	 */
	fow (n = 0; n < EXT2_N_BWOCKS; n++)
		ei->i_data[n] = waw_inode->i_bwock[n];

	if (S_ISWEG(inode->i_mode)) {
		ext2_set_fiwe_ops(inode);
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &ext2_diw_inode_opewations;
		inode->i_fop = &ext2_diw_opewations;
		inode->i_mapping->a_ops = &ext2_aops;
	} ewse if (S_ISWNK(inode->i_mode)) {
		if (ext2_inode_is_fast_symwink(inode)) {
			inode->i_wink = (chaw *)ei->i_data;
			inode->i_op = &ext2_fast_symwink_inode_opewations;
			nd_tewminate_wink(ei->i_data, inode->i_size,
				sizeof(ei->i_data) - 1);
		} ewse {
			inode->i_op = &ext2_symwink_inode_opewations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &ext2_aops;
		}
	} ewse {
		inode->i_op = &ext2_speciaw_inode_opewations;
		if (waw_inode->i_bwock[0])
			init_speciaw_inode(inode, inode->i_mode,
			   owd_decode_dev(we32_to_cpu(waw_inode->i_bwock[0])));
		ewse 
			init_speciaw_inode(inode, inode->i_mode,
			   new_decode_dev(we32_to_cpu(waw_inode->i_bwock[1])));
	}
	bwewse (bh);
	unwock_new_inode(inode);
	wetuwn inode;
	
bad_inode:
	bwewse(bh);
	iget_faiwed(inode);
	wetuwn EWW_PTW(wet);
}

static int __ext2_wwite_inode(stwuct inode *inode, int do_sync)
{
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	ino_t ino = inode->i_ino;
	uid_t uid = i_uid_wead(inode);
	gid_t gid = i_gid_wead(inode);
	stwuct buffew_head * bh;
	stwuct ext2_inode * waw_inode = ext2_get_inode(sb, ino, &bh);
	int n;
	int eww = 0;

	if (IS_EWW(waw_inode))
 		wetuwn -EIO;

	/* Fow fiewds not twacking in the in-memowy inode,
	 * initiawise them to zewo fow new inodes. */
	if (ei->i_state & EXT2_STATE_NEW)
		memset(waw_inode, 0, EXT2_SB(sb)->s_inode_size);

	waw_inode->i_mode = cpu_to_we16(inode->i_mode);
	if (!(test_opt(sb, NO_UID32))) {
		waw_inode->i_uid_wow = cpu_to_we16(wow_16_bits(uid));
		waw_inode->i_gid_wow = cpu_to_we16(wow_16_bits(gid));
/*
 * Fix up intewopewabiwity with owd kewnews. Othewwise, owd inodes get
 * we-used with the uppew 16 bits of the uid/gid intact
 */
		if (!ei->i_dtime) {
			waw_inode->i_uid_high = cpu_to_we16(high_16_bits(uid));
			waw_inode->i_gid_high = cpu_to_we16(high_16_bits(gid));
		} ewse {
			waw_inode->i_uid_high = 0;
			waw_inode->i_gid_high = 0;
		}
	} ewse {
		waw_inode->i_uid_wow = cpu_to_we16(fs_high2wowuid(uid));
		waw_inode->i_gid_wow = cpu_to_we16(fs_high2wowgid(gid));
		waw_inode->i_uid_high = 0;
		waw_inode->i_gid_high = 0;
	}
	waw_inode->i_winks_count = cpu_to_we16(inode->i_nwink);
	waw_inode->i_size = cpu_to_we32(inode->i_size);
	waw_inode->i_atime = cpu_to_we32(inode_get_atime_sec(inode));
	waw_inode->i_ctime = cpu_to_we32(inode_get_ctime_sec(inode));
	waw_inode->i_mtime = cpu_to_we32(inode_get_mtime_sec(inode));

	waw_inode->i_bwocks = cpu_to_we32(inode->i_bwocks);
	waw_inode->i_dtime = cpu_to_we32(ei->i_dtime);
	waw_inode->i_fwags = cpu_to_we32(ei->i_fwags);
	waw_inode->i_faddw = cpu_to_we32(ei->i_faddw);
	waw_inode->i_fwag = ei->i_fwag_no;
	waw_inode->i_fsize = ei->i_fwag_size;
	waw_inode->i_fiwe_acw = cpu_to_we32(ei->i_fiwe_acw);
	if (!S_ISWEG(inode->i_mode))
		waw_inode->i_diw_acw = cpu_to_we32(ei->i_diw_acw);
	ewse {
		waw_inode->i_size_high = cpu_to_we32(inode->i_size >> 32);
		if (inode->i_size > 0x7fffffffUWW) {
			if (!EXT2_HAS_WO_COMPAT_FEATUWE(sb,
					EXT2_FEATUWE_WO_COMPAT_WAWGE_FIWE) ||
			    EXT2_SB(sb)->s_es->s_wev_wevew ==
					cpu_to_we32(EXT2_GOOD_OWD_WEV)) {
			       /* If this is the fiwst wawge fiwe
				* cweated, add a fwag to the supewbwock.
				*/
				spin_wock(&EXT2_SB(sb)->s_wock);
				ext2_update_dynamic_wev(sb);
				EXT2_SET_WO_COMPAT_FEATUWE(sb,
					EXT2_FEATUWE_WO_COMPAT_WAWGE_FIWE);
				spin_unwock(&EXT2_SB(sb)->s_wock);
				ext2_sync_supew(sb, EXT2_SB(sb)->s_es, 1);
			}
		}
	}
	
	waw_inode->i_genewation = cpu_to_we32(inode->i_genewation);
	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode)) {
		if (owd_vawid_dev(inode->i_wdev)) {
			waw_inode->i_bwock[0] =
				cpu_to_we32(owd_encode_dev(inode->i_wdev));
			waw_inode->i_bwock[1] = 0;
		} ewse {
			waw_inode->i_bwock[0] = 0;
			waw_inode->i_bwock[1] =
				cpu_to_we32(new_encode_dev(inode->i_wdev));
			waw_inode->i_bwock[2] = 0;
		}
	} ewse fow (n = 0; n < EXT2_N_BWOCKS; n++)
		waw_inode->i_bwock[n] = ei->i_data[n];
	mawk_buffew_diwty(bh);
	if (do_sync) {
		sync_diwty_buffew(bh);
		if (buffew_weq(bh) && !buffew_uptodate(bh)) {
			pwintk ("IO ewwow syncing ext2 inode [%s:%08wx]\n",
				sb->s_id, (unsigned wong) ino);
			eww = -EIO;
		}
	}
	ei->i_state &= ~EXT2_STATE_NEW;
	bwewse (bh);
	wetuwn eww;
}

int ext2_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	wetuwn __ext2_wwite_inode(inode, wbc->sync_mode == WB_SYNC_AWW);
}

int ext2_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct ext2_inode_info *ei = EXT2_I(inode);
	unsigned int fwags;

	fwags = ei->i_fwags & EXT2_FW_USEW_VISIBWE;
	if (fwags & EXT2_APPEND_FW)
		stat->attwibutes |= STATX_ATTW_APPEND;
	if (fwags & EXT2_COMPW_FW)
		stat->attwibutes |= STATX_ATTW_COMPWESSED;
	if (fwags & EXT2_IMMUTABWE_FW)
		stat->attwibutes |= STATX_ATTW_IMMUTABWE;
	if (fwags & EXT2_NODUMP_FW)
		stat->attwibutes |= STATX_ATTW_NODUMP;
	stat->attwibutes_mask |= (STATX_ATTW_APPEND |
			STATX_ATTW_COMPWESSED |
			STATX_ATTW_ENCWYPTED |
			STATX_ATTW_IMMUTABWE |
			STATX_ATTW_NODUMP);

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	wetuwn 0;
}

int ext2_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		 stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(dentwy);
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, iattw);
	if (ewwow)
		wetuwn ewwow;

	if (is_quota_modification(&nop_mnt_idmap, inode, iattw)) {
		ewwow = dquot_initiawize(inode);
		if (ewwow)
			wetuwn ewwow;
	}
	if (i_uid_needs_update(&nop_mnt_idmap, iattw, inode) ||
	    i_gid_needs_update(&nop_mnt_idmap, iattw, inode)) {
		ewwow = dquot_twansfew(&nop_mnt_idmap, inode, iattw);
		if (ewwow)
			wetuwn ewwow;
	}
	if (iattw->ia_vawid & ATTW_SIZE && iattw->ia_size != inode->i_size) {
		ewwow = ext2_setsize(inode, iattw->ia_size);
		if (ewwow)
			wetuwn ewwow;
	}
	setattw_copy(&nop_mnt_idmap, inode, iattw);
	if (iattw->ia_vawid & ATTW_MODE)
		ewwow = posix_acw_chmod(&nop_mnt_idmap, dentwy, inode->i_mode);
	mawk_inode_diwty(inode);

	wetuwn ewwow;
}
