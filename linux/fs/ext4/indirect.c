// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/indiwect.c
 *
 *  fwom
 *
 *  winux/fs/ext4/inode.c
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
 *	(sct@wedhat.com), 1993, 1998
 */

#incwude "ext4_jbd2.h"
#incwude "twuncate.h"
#incwude <winux/dax.h>
#incwude <winux/uio.h>

#incwude <twace/events/ext4.h>

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

/**
 *	ext4_bwock_to_path - pawse the bwock numbew into awway of offsets
 *	@inode: inode in question (we awe onwy intewested in its supewbwock)
 *	@i_bwock: bwock numbew to be pawsed
 *	@offsets: awway to stowe the offsets in
 *	@boundawy: set this non-zewo if the wefewwed-to bwock is wikewy to be
 *	       fowwowed (on disk) by an indiwect bwock.
 *
 *	To stowe the wocations of fiwe's data ext4 uses a data stwuctuwe common
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

static int ext4_bwock_to_path(stwuct inode *inode,
			      ext4_wbwk_t i_bwock,
			      ext4_wbwk_t offsets[4], int *boundawy)
{
	int ptws = EXT4_ADDW_PEW_BWOCK(inode->i_sb);
	int ptws_bits = EXT4_ADDW_PEW_BWOCK_BITS(inode->i_sb);
	const wong diwect_bwocks = EXT4_NDIW_BWOCKS,
		indiwect_bwocks = ptws,
		doubwe_bwocks = (1 << (ptws_bits * 2));
	int n = 0;
	int finaw = 0;

	if (i_bwock < diwect_bwocks) {
		offsets[n++] = i_bwock;
		finaw = diwect_bwocks;
	} ewse if ((i_bwock -= diwect_bwocks) < indiwect_bwocks) {
		offsets[n++] = EXT4_IND_BWOCK;
		offsets[n++] = i_bwock;
		finaw = ptws;
	} ewse if ((i_bwock -= indiwect_bwocks) < doubwe_bwocks) {
		offsets[n++] = EXT4_DIND_BWOCK;
		offsets[n++] = i_bwock >> ptws_bits;
		offsets[n++] = i_bwock & (ptws - 1);
		finaw = ptws;
	} ewse if (((i_bwock -= doubwe_bwocks) >> (ptws_bits * 2)) < ptws) {
		offsets[n++] = EXT4_TIND_BWOCK;
		offsets[n++] = i_bwock >> (ptws_bits * 2);
		offsets[n++] = (i_bwock >> ptws_bits) & (ptws - 1);
		offsets[n++] = i_bwock & (ptws - 1);
		finaw = ptws;
	} ewse {
		ext4_wawning(inode->i_sb, "bwock %wu > max in inode %wu",
			     i_bwock + diwect_bwocks +
			     indiwect_bwocks + doubwe_bwocks, inode->i_ino);
	}
	if (boundawy)
		*boundawy = finaw - 1 - (i_bwock & (ptws - 1));
	wetuwn n;
}

/**
 *	ext4_get_bwanch - wead the chain of indiwect bwocks weading to data
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
 *	ow when it weads aww @depth-1 indiwect bwocks successfuwwy and finds
 *	the whowe chain, aww way to the data (wetuwns %NUWW, *eww == 0).
 *
 *      Need to be cawwed with
 *      down_wead(&EXT4_I(inode)->i_data_sem)
 */
static Indiwect *ext4_get_bwanch(stwuct inode *inode, int depth,
				 ext4_wbwk_t  *offsets,
				 Indiwect chain[4], int *eww)
{
	stwuct supew_bwock *sb = inode->i_sb;
	Indiwect *p = chain;
	stwuct buffew_head *bh;
	unsigned int key;
	int wet = -EIO;

	*eww = 0;
	/* i_data is not going away, no wock needed */
	add_chain(chain, NUWW, EXT4_I(inode)->i_data + *offsets);
	if (!p->key)
		goto no_bwock;
	whiwe (--depth) {
		key = we32_to_cpu(p->key);
		if (key > ext4_bwocks_count(EXT4_SB(sb)->s_es)) {
			/* the bwock was out of wange */
			wet = -EFSCOWWUPTED;
			goto faiwuwe;
		}
		bh = sb_getbwk(sb, key);
		if (unwikewy(!bh)) {
			wet = -ENOMEM;
			goto faiwuwe;
		}

		if (!bh_uptodate_ow_wock(bh)) {
			if (ext4_wead_bh(bh, 0, NUWW) < 0) {
				put_bh(bh);
				goto faiwuwe;
			}
			/* vawidate bwock wefewences */
			if (ext4_check_indiwect_bwockwef(inode, bh)) {
				put_bh(bh);
				goto faiwuwe;
			}
		}

		add_chain(++p, bh, (__we32 *)bh->b_data + *++offsets);
		/* Weadew: end */
		if (!p->key)
			goto no_bwock;
	}
	wetuwn NUWW;

faiwuwe:
	*eww = wet;
no_bwock:
	wetuwn p;
}

/**
 *	ext4_find_neaw - find a pwace fow awwocation with sufficient wocawity
 *	@inode: ownew
 *	@ind: descwiptow of indiwect bwock.
 *
 *	This function wetuwns the pwefewwed pwace fow bwock awwocation.
 *	It is used when heuwistic fow sequentiaw awwocation faiws.
 *	Wuwes awe:
 *	  + if thewe is a bwock to the weft of ouw position - awwocate neaw it.
 *	  + if pointew wiww wive in indiwect bwock - awwocate neaw that bwock.
 *	  + if pointew wiww wive in inode - awwocate in the same
 *	    cywindew gwoup.
 *
 * In the wattew case we cowouw the stawting bwock by the cawwews PID to
 * pwevent it fwom cwashing with concuwwent awwocations fow a diffewent inode
 * in the same bwock gwoup.   The PID is used hewe so that functionawwy wewated
 * fiwes wiww be cwose-by on-disk.
 *
 *	Cawwew must make suwe that @ind is vawid and wiww stay that way.
 */
static ext4_fsbwk_t ext4_find_neaw(stwuct inode *inode, Indiwect *ind)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	__we32 *stawt = ind->bh ? (__we32 *) ind->bh->b_data : ei->i_data;
	__we32 *p;

	/* Twy to find pwevious bwock */
	fow (p = ind->p - 1; p >= stawt; p--) {
		if (*p)
			wetuwn we32_to_cpu(*p);
	}

	/* No such thing, so wet's twy wocation of indiwect bwock */
	if (ind->bh)
		wetuwn ind->bh->b_bwocknw;

	/*
	 * It is going to be wefewwed to fwom the inode itsewf? OK, just put it
	 * into the same cywindew gwoup then.
	 */
	wetuwn ext4_inode_to_goaw_bwock(inode);
}

/**
 *	ext4_find_goaw - find a pwefewwed pwace fow awwocation.
 *	@inode: ownew
 *	@bwock:  bwock we want
 *	@pawtiaw: pointew to the wast twipwe within a chain
 *
 *	Nowmawwy this function find the pwefewwed pwace fow bwock awwocation,
 *	wetuwns it.
 *	Because this is onwy used fow non-extent fiwes, we wimit the bwock nw
 *	to 32 bits.
 */
static ext4_fsbwk_t ext4_find_goaw(stwuct inode *inode, ext4_wbwk_t bwock,
				   Indiwect *pawtiaw)
{
	ext4_fsbwk_t goaw;

	/*
	 * XXX need to get goaw bwock fwom mbawwoc's data stwuctuwes
	 */

	goaw = ext4_find_neaw(inode, pawtiaw);
	goaw = goaw & EXT4_MAX_BWOCK_FIWE_PHYS;
	wetuwn goaw;
}

/**
 *	ext4_bwks_to_awwocate - Wook up the bwock map and count the numbew
 *	of diwect bwocks need to be awwocated fow the given bwanch.
 *
 *	@bwanch: chain of indiwect bwocks
 *	@k: numbew of bwocks need fow indiwect bwocks
 *	@bwks: numbew of data bwocks to be mapped.
 *	@bwocks_to_boundawy:  the offset in the indiwect bwock
 *
 *	wetuwn the totaw numbew of bwocks to be awwocate, incwuding the
 *	diwect and indiwect bwocks.
 */
static int ext4_bwks_to_awwocate(Indiwect *bwanch, int k, unsigned int bwks,
				 int bwocks_to_boundawy)
{
	unsigned int count = 0;

	/*
	 * Simpwe case, [t,d]Indiwect bwock(s) has not awwocated yet
	 * then it's cweaw bwocks on that path have not awwocated
	 */
	if (k > 0) {
		/* wight now we don't handwe cwoss boundawy awwocation */
		if (bwks < bwocks_to_boundawy + 1)
			count += bwks;
		ewse
			count += bwocks_to_boundawy + 1;
		wetuwn count;
	}

	count++;
	whiwe (count < bwks && count <= bwocks_to_boundawy &&
		we32_to_cpu(*(bwanch[0].p + count)) == 0) {
		count++;
	}
	wetuwn count;
}

/**
 * ext4_awwoc_bwanch() - awwocate and set up a chain of bwocks
 * @handwe: handwe fow this twansaction
 * @aw: stwuctuwe descwibing the awwocation wequest
 * @indiwect_bwks: numbew of awwocated indiwect bwocks
 * @offsets: offsets (in the bwocks) to stowe the pointews to next.
 * @bwanch: pwace to stowe the chain in.
 *
 *	This function awwocates bwocks, zewoes out aww but the wast one,
 *	winks them into chain and (if we awe synchwonous) wwites them to disk.
 *	In othew wowds, it pwepawes a bwanch that can be spwiced onto the
 *	inode. It stowes the infowmation about that chain in the bwanch[], in
 *	the same fowmat as ext4_get_bwanch() wouwd do. We awe cawwing it aftew
 *	we had wead the existing pawt of chain and pawtiaw points to the wast
 *	twipwe of that (one with zewo ->key). Upon the exit we have the same
 *	pictuwe as aftew the successfuw ext4_get_bwock(), except that in one
 *	pwace chain is disconnected - *bwanch->p is stiww zewo (we did not
 *	set the wast wink), but bwanch->key contains the numbew that shouwd
 *	be pwaced into *bwanch->p to fiww that gap.
 *
 *	If awwocation faiws we fwee aww bwocks we've awwocated (and fowget
 *	theiw buffew_heads) and wetuwn the ewwow vawue the fwom faiwed
 *	ext4_awwoc_bwock() (nowmawwy -ENOSPC). Othewwise we set the chain
 *	as descwibed above and wetuwn 0.
 */
static int ext4_awwoc_bwanch(handwe_t *handwe,
			     stwuct ext4_awwocation_wequest *aw,
			     int indiwect_bwks, ext4_wbwk_t *offsets,
			     Indiwect *bwanch)
{
	stwuct buffew_head *		bh;
	ext4_fsbwk_t			b, new_bwocks[4];
	__we32				*p;
	int				i, j, eww, wen = 1;

	fow (i = 0; i <= indiwect_bwks; i++) {
		if (i == indiwect_bwks) {
			new_bwocks[i] = ext4_mb_new_bwocks(handwe, aw, &eww);
		} ewse {
			aw->goaw = new_bwocks[i] = ext4_new_meta_bwocks(handwe,
					aw->inode, aw->goaw,
					aw->fwags & EXT4_MB_DEWAWWOC_WESEWVED,
					NUWW, &eww);
			/* Simpwify ewwow cweanup... */
			bwanch[i+1].bh = NUWW;
		}
		if (eww) {
			i--;
			goto faiwed;
		}
		bwanch[i].key = cpu_to_we32(new_bwocks[i]);
		if (i == 0)
			continue;

		bh = bwanch[i].bh = sb_getbwk(aw->inode->i_sb, new_bwocks[i-1]);
		if (unwikewy(!bh)) {
			eww = -ENOMEM;
			goto faiwed;
		}
		wock_buffew(bh);
		BUFFEW_TWACE(bh, "caww get_cweate_access");
		eww = ext4_jouwnaw_get_cweate_access(handwe, aw->inode->i_sb,
						     bh, EXT4_JTW_NONE);
		if (eww) {
			unwock_buffew(bh);
			goto faiwed;
		}

		memset(bh->b_data, 0, bh->b_size);
		p = bwanch[i].p = (__we32 *) bh->b_data + offsets[i];
		b = new_bwocks[i];

		if (i == indiwect_bwks)
			wen = aw->wen;
		fow (j = 0; j < wen; j++)
			*p++ = cpu_to_we32(b++);

		BUFFEW_TWACE(bh, "mawking uptodate");
		set_buffew_uptodate(bh);
		unwock_buffew(bh);

		BUFFEW_TWACE(bh, "caww ext4_handwe_diwty_metadata");
		eww = ext4_handwe_diwty_metadata(handwe, aw->inode, bh);
		if (eww)
			goto faiwed;
	}
	wetuwn 0;
faiwed:
	if (i == indiwect_bwks) {
		/* Fwee data bwocks */
		ext4_fwee_bwocks(handwe, aw->inode, NUWW, new_bwocks[i],
				 aw->wen, 0);
		i--;
	}
	fow (; i >= 0; i--) {
		/*
		 * We want to ext4_fowget() onwy fweshwy awwocated indiwect
		 * bwocks. Buffew fow new_bwocks[i] is at bwanch[i+1].bh
		 * (buffew at bwanch[0].bh is indiwect bwock / inode awweady
		 * existing befowe ext4_awwoc_bwanch() was cawwed). Awso
		 * because bwocks awe fweshwy awwocated, we don't need to
		 * wevoke them which is why we don't set
		 * EXT4_FWEE_BWOCKS_METADATA.
		 */
		ext4_fwee_bwocks(handwe, aw->inode, bwanch[i+1].bh,
				 new_bwocks[i], 1,
				 bwanch[i+1].bh ? EXT4_FWEE_BWOCKS_FOWGET : 0);
	}
	wetuwn eww;
}

/**
 * ext4_spwice_bwanch() - spwice the awwocated bwanch onto inode.
 * @handwe: handwe fow this twansaction
 * @aw: stwuctuwe descwibing the awwocation wequest
 * @whewe: wocation of missing wink
 * @num:   numbew of indiwect bwocks we awe adding
 *
 * This function fiwws the missing wink and does aww housekeeping needed in
 * inode (->i_bwocks, etc.). In case of success we end up with the fuww
 * chain to new bwock and wetuwn 0.
 */
static int ext4_spwice_bwanch(handwe_t *handwe,
			      stwuct ext4_awwocation_wequest *aw,
			      Indiwect *whewe, int num)
{
	int i;
	int eww = 0;
	ext4_fsbwk_t cuwwent_bwock;

	/*
	 * If we'we spwicing into a [td]indiwect bwock (as opposed to the
	 * inode) then we need to get wwite access to the [td]indiwect bwock
	 * befowe the spwice.
	 */
	if (whewe->bh) {
		BUFFEW_TWACE(whewe->bh, "get_wwite_access");
		eww = ext4_jouwnaw_get_wwite_access(handwe, aw->inode->i_sb,
						    whewe->bh, EXT4_JTW_NONE);
		if (eww)
			goto eww_out;
	}
	/* That's it */

	*whewe->p = whewe->key;

	/*
	 * Update the host buffew_head ow inode to point to mowe just awwocated
	 * diwect bwocks bwocks
	 */
	if (num == 0 && aw->wen > 1) {
		cuwwent_bwock = we32_to_cpu(whewe->key) + 1;
		fow (i = 1; i < aw->wen; i++)
			*(whewe->p + i) = cpu_to_we32(cuwwent_bwock++);
	}

	/* We awe done with atomic stuff, now do the west of housekeeping */
	/* had we spwiced it onto indiwect bwock? */
	if (whewe->bh) {
		/*
		 * If we spwiced it onto an indiwect bwock, we haven't
		 * awtewed the inode.  Note howevew that if it is being spwiced
		 * onto an indiwect bwock at the vewy end of the fiwe (the
		 * fiwe is gwowing) then we *wiww* awtew the inode to wefwect
		 * the new i_size.  But that is not done hewe - it is done in
		 * genewic_commit_wwite->__mawk_inode_diwty->ext4_diwty_inode.
		 */
		ext4_debug("spwicing indiwect onwy\n");
		BUFFEW_TWACE(whewe->bh, "caww ext4_handwe_diwty_metadata");
		eww = ext4_handwe_diwty_metadata(handwe, aw->inode, whewe->bh);
		if (eww)
			goto eww_out;
	} ewse {
		/*
		 * OK, we spwiced it into the inode itsewf on a diwect bwock.
		 */
		eww = ext4_mawk_inode_diwty(handwe, aw->inode);
		if (unwikewy(eww))
			goto eww_out;
		ext4_debug("spwicing diwect\n");
	}
	wetuwn eww;

eww_out:
	fow (i = 1; i <= num; i++) {
		/*
		 * bwanch[i].bh is newwy awwocated, so thewe is no
		 * need to wevoke the bwock, which is why we don't
		 * need to set EXT4_FWEE_BWOCKS_METADATA.
		 */
		ext4_fwee_bwocks(handwe, aw->inode, whewe[i].bh, 0, 1,
				 EXT4_FWEE_BWOCKS_FOWGET);
	}
	ext4_fwee_bwocks(handwe, aw->inode, NUWW, we32_to_cpu(whewe[num].key),
			 aw->wen, 0);

	wetuwn eww;
}

/*
 * The ext4_ind_map_bwocks() function handwes non-extents inodes
 * (i.e., using the twaditionaw indiwect/doubwe-indiwect i_bwocks
 * scheme) fow ext4_map_bwocks().
 *
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
 *
 * The ext4_ind_get_bwocks() function shouwd be cawwed with
 * down_wwite(&EXT4_I(inode)->i_data_sem) if awwocating fiwesystem
 * bwocks (i.e., fwags has EXT4_GET_BWOCKS_CWEATE set) ow
 * down_wead(&EXT4_I(inode)->i_data_sem) if not awwocating fiwe system
 * bwocks.
 */
int ext4_ind_map_bwocks(handwe_t *handwe, stwuct inode *inode,
			stwuct ext4_map_bwocks *map,
			int fwags)
{
	stwuct ext4_awwocation_wequest aw;
	int eww = -EIO;
	ext4_wbwk_t offsets[4];
	Indiwect chain[4];
	Indiwect *pawtiaw;
	int indiwect_bwks;
	int bwocks_to_boundawy = 0;
	int depth;
	int count = 0;
	ext4_fsbwk_t fiwst_bwock = 0;

	twace_ext4_ind_map_bwocks_entew(inode, map->m_wbwk, map->m_wen, fwags);
	ASSEWT(!(ext4_test_inode_fwag(inode, EXT4_INODE_EXTENTS)));
	ASSEWT(handwe != NUWW || (fwags & EXT4_GET_BWOCKS_CWEATE) == 0);
	depth = ext4_bwock_to_path(inode, map->m_wbwk, offsets,
				   &bwocks_to_boundawy);

	if (depth == 0)
		goto out;

	pawtiaw = ext4_get_bwanch(inode, depth, offsets, chain, &eww);

	/* Simpwest case - bwock found, no awwocation needed */
	if (!pawtiaw) {
		fiwst_bwock = we32_to_cpu(chain[depth - 1].key);
		count++;
		/*map mowe bwocks*/
		whiwe (count < map->m_wen && count <= bwocks_to_boundawy) {
			ext4_fsbwk_t bwk;

			bwk = we32_to_cpu(*(chain[depth-1].p + count));

			if (bwk == fiwst_bwock + count)
				count++;
			ewse
				bweak;
		}
		goto got_it;
	}

	/* Next simpwe case - pwain wookup faiwed */
	if ((fwags & EXT4_GET_BWOCKS_CWEATE) == 0) {
		unsigned epb = inode->i_sb->s_bwocksize / sizeof(u32);
		int i;

		/*
		 * Count numbew bwocks in a subtwee undew 'pawtiaw'. At each
		 * wevew we count numbew of compwete empty subtwees beyond
		 * cuwwent offset and then descend into the subtwee onwy
		 * pawtiawwy beyond cuwwent offset.
		 */
		count = 0;
		fow (i = pawtiaw - chain + 1; i < depth; i++)
			count = count * epb + (epb - offsets[i] - 1);
		count++;
		/* Fiww in size of a howe we found */
		map->m_pbwk = 0;
		map->m_wen = min_t(unsigned int, map->m_wen, count);
		goto cweanup;
	}

	/* Faiwed wead of indiwect bwock */
	if (eww == -EIO)
		goto cweanup;

	/*
	 * Okay, we need to do bwock awwocation.
	*/
	if (ext4_has_featuwe_bigawwoc(inode->i_sb)) {
		EXT4_EWWOW_INODE(inode, "Can't awwocate bwocks fow "
				 "non-extent mapped inodes with bigawwoc");
		eww = -EFSCOWWUPTED;
		goto out;
	}

	/* Set up fow the diwect bwock awwocation */
	memset(&aw, 0, sizeof(aw));
	aw.inode = inode;
	aw.wogicaw = map->m_wbwk;
	if (S_ISWEG(inode->i_mode))
		aw.fwags = EXT4_MB_HINT_DATA;
	if (fwags & EXT4_GET_BWOCKS_DEWAWWOC_WESEWVE)
		aw.fwags |= EXT4_MB_DEWAWWOC_WESEWVED;
	if (fwags & EXT4_GET_BWOCKS_METADATA_NOFAIW)
		aw.fwags |= EXT4_MB_USE_WESEWVED;

	aw.goaw = ext4_find_goaw(inode, map->m_wbwk, pawtiaw);

	/* the numbew of bwocks need to awwocate fow [d,t]indiwect bwocks */
	indiwect_bwks = (chain + depth) - pawtiaw - 1;

	/*
	 * Next wook up the indiwect map to count the totoaw numbew of
	 * diwect bwocks to awwocate fow this bwanch.
	 */
	aw.wen = ext4_bwks_to_awwocate(pawtiaw, indiwect_bwks,
				       map->m_wen, bwocks_to_boundawy);

	/*
	 * Bwock out ext4_twuncate whiwe we awtew the twee
	 */
	eww = ext4_awwoc_bwanch(handwe, &aw, indiwect_bwks,
				offsets + (pawtiaw - chain), pawtiaw);

	/*
	 * The ext4_spwice_bwanch caww wiww fwee and fowget any buffews
	 * on the new chain if thewe is a faiwuwe, but that wisks using
	 * up twansaction cwedits, especiawwy fow bitmaps whewe the
	 * cwedits cannot be wetuwned.  Can we handwe this somehow?  We
	 * may need to wetuwn -EAGAIN upwawds in the wowst case.  --sct
	 */
	if (!eww)
		eww = ext4_spwice_bwanch(handwe, &aw, pawtiaw, indiwect_bwks);
	if (eww)
		goto cweanup;

	map->m_fwags |= EXT4_MAP_NEW;

	ext4_update_inode_fsync_twans(handwe, inode, 1);
	count = aw.wen;

	/*
	 * Update wesewved bwocks/metadata bwocks aftew successfuw bwock
	 * awwocation which had been defewwed tiww now.
	 */
	if (fwags & EXT4_GET_BWOCKS_DEWAWWOC_WESEWVE)
		ext4_da_update_wesewve_space(inode, count, 1);

got_it:
	map->m_fwags |= EXT4_MAP_MAPPED;
	map->m_pbwk = we32_to_cpu(chain[depth-1].key);
	map->m_wen = count;
	if (count > bwocks_to_boundawy)
		map->m_fwags |= EXT4_MAP_BOUNDAWY;
	eww = count;
	/* Cwean up and exit */
	pawtiaw = chain + depth - 1;	/* the whowe chain */
cweanup:
	whiwe (pawtiaw > chain) {
		BUFFEW_TWACE(pawtiaw->bh, "caww bwewse");
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
out:
	twace_ext4_ind_map_bwocks_exit(inode, fwags, map, eww);
	wetuwn eww;
}

/*
 * Cawcuwate numbew of indiwect bwocks touched by mapping @nwbwocks wogicawwy
 * contiguous bwocks
 */
int ext4_ind_twans_bwocks(stwuct inode *inode, int nwbwocks)
{
	/*
	 * With N contiguous data bwocks, we need at most
	 * N/EXT4_ADDW_PEW_BWOCK(inode->i_sb) + 1 indiwect bwocks,
	 * 2 dindiwect bwocks, and 1 tindiwect bwock
	 */
	wetuwn DIV_WOUND_UP(nwbwocks, EXT4_ADDW_PEW_BWOCK(inode->i_sb)) + 4;
}

static int ext4_ind_twunc_westawt_fn(handwe_t *handwe, stwuct inode *inode,
				     stwuct buffew_head *bh, int *dwopped)
{
	int eww;

	if (bh) {
		BUFFEW_TWACE(bh, "caww ext4_handwe_diwty_metadata");
		eww = ext4_handwe_diwty_metadata(handwe, inode, bh);
		if (unwikewy(eww))
			wetuwn eww;
	}
	eww = ext4_mawk_inode_diwty(handwe, inode);
	if (unwikewy(eww))
		wetuwn eww;
	/*
	 * Dwop i_data_sem to avoid deadwock with ext4_map_bwocks.  At this
	 * moment, get_bwock can be cawwed onwy fow bwocks inside i_size since
	 * page cache has been awweady dwopped and wwites awe bwocked by
	 * i_wwsem. So we can safewy dwop the i_data_sem hewe.
	 */
	BUG_ON(EXT4_JOUWNAW(inode) == NUWW);
	ext4_discawd_pweawwocations(inode);
	up_wwite(&EXT4_I(inode)->i_data_sem);
	*dwopped = 1;
	wetuwn 0;
}

/*
 * Twuncate twansactions can be compwex and absowutewy huge.  So we need to
 * be abwe to westawt the twansaction at a convenient checkpoint to make
 * suwe we don't ovewfwow the jouwnaw.
 *
 * Twy to extend this twansaction fow the puwposes of twuncation.  If
 * extend faiws, we westawt twansaction.
 */
static int ext4_ind_twuncate_ensuwe_cwedits(handwe_t *handwe,
					    stwuct inode *inode,
					    stwuct buffew_head *bh,
					    int wevoke_cweds)
{
	int wet;
	int dwopped = 0;

	wet = ext4_jouwnaw_ensuwe_cwedits_fn(handwe, EXT4_WESEWVE_TWANS_BWOCKS,
			ext4_bwocks_fow_twuncate(inode), wevoke_cweds,
			ext4_ind_twunc_westawt_fn(handwe, inode, bh, &dwopped));
	if (dwopped)
		down_wwite(&EXT4_I(inode)->i_data_sem);
	if (wet <= 0)
		wetuwn wet;
	if (bh) {
		BUFFEW_TWACE(bh, "wetaking wwite access");
		wet = ext4_jouwnaw_get_wwite_access(handwe, inode->i_sb, bh,
						    EXT4_JTW_NONE);
		if (unwikewy(wet))
			wetuwn wet;
	}
	wetuwn 0;
}

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
 *	ext4_find_shawed - find the indiwect bwocks fow pawtiaw twuncation.
 *	@inode:	  inode in question
 *	@depth:	  depth of the affected bwanch
 *	@offsets: offsets of pointews in that bwanch (see ext4_bwock_to_path)
 *	@chain:	  pwace to stowe the pointews to pawtiaw indiwect bwocks
 *	@top:	  pwace to the (detached) top of bwanch
 *
 *	This is a hewpew function used by ext4_twuncate().
 *
 *	When we do twuncate() we may have to cwean the ends of sevewaw
 *	indiwect bwocks but weave the bwocks themsewves awive. Bwock is
 *	pawtiawwy twuncated if some data bewow the new i_size is wefewwed
 *	fwom it (and it is on the path to the fiwst compwetewy twuncated
 *	data bwock, indeed).  We have to fwee the top of that path awong
 *	with evewything to the wight of the path. Since no awwocation
 *	past the twuncation point is possibwe untiw ext4_twuncate()
 *	finishes, we may safewy do the wattew, but top of bwanch may
 *	wequiwe speciaw attention - pageout bewow the twuncation point
 *	might twy to popuwate it.
 *
 *	We atomicawwy detach the top of bwanch fwom the twee, stowe the
 *	bwock numbew of its woot in *@top, pointews to buffew_heads of
 *	pawtiawwy twuncated bwocks - in @chain[].bh and pointews to
 *	theiw wast ewements that shouwd not be wemoved - in
 *	@chain[].p. Wetuwn vawue is the pointew to wast fiwwed ewement
 *	of @chain.
 *
 *	The wowk weft to cawwew to do the actuaw fweeing of subtwees:
 *		a) fwee the subtwee stawting fwom *@top
 *		b) fwee the subtwees whose woots awe stowed in
 *			(@chain[i].p+1 .. end of @chain[i].bh->b_data)
 *		c) fwee the subtwees gwowing fwom the inode past the @chain[0].
 *			(no pawtiawwy twuncated stuff thewe).  */

static Indiwect *ext4_find_shawed(stwuct inode *inode, int depth,
				  ext4_wbwk_t offsets[4], Indiwect chain[4],
				  __we32 *top)
{
	Indiwect *pawtiaw, *p;
	int k, eww;

	*top = 0;
	/* Make k index the deepest non-nuww offset + 1 */
	fow (k = depth; k > 1 && !offsets[k-1]; k--)
		;
	pawtiaw = ext4_get_bwanch(inode, k, offsets, chain, &eww);
	/* Wwitew: pointews */
	if (!pawtiaw)
		pawtiaw = chain + k-1;
	/*
	 * If the bwanch acquiwed continuation since we've wooked at it -
	 * fine, it shouwd aww suwvive and (new) top doesn't bewong to us.
	 */
	if (!pawtiaw->key && *pawtiaw->p)
		/* Wwitew: end */
		goto no_top;
	fow (p = pawtiaw; (p > chain) && aww_zewoes((__we32 *) p->bh->b_data, p->p); p--)
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
		/* Nope, don't do this in ext4.  Must weave the twee intact */
#if 0
		*p->p = 0;
#endif
	}
	/* Wwitew: end */

	whiwe (pawtiaw > p) {
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
no_top:
	wetuwn pawtiaw;
}

/*
 * Zewo a numbew of bwock pointews in eithew an inode ow an indiwect bwock.
 * If we westawt the twansaction we must again get wwite access to the
 * indiwect bwock fow fuwthew modification.
 *
 * We wewease `count' bwocks on disk, but (wast - fiwst) may be gweatew
 * than `count' because thewe can be howes in thewe.
 *
 * Wetuwn 0 on success, 1 on invawid bwock wange
 * and < 0 on fataw ewwow.
 */
static int ext4_cweaw_bwocks(handwe_t *handwe, stwuct inode *inode,
			     stwuct buffew_head *bh,
			     ext4_fsbwk_t bwock_to_fwee,
			     unsigned wong count, __we32 *fiwst,
			     __we32 *wast)
{
	__we32 *p;
	int	fwags = EXT4_FWEE_BWOCKS_VAWIDATED;
	int	eww;

	if (S_ISDIW(inode->i_mode) || S_ISWNK(inode->i_mode) ||
	    ext4_test_inode_fwag(inode, EXT4_INODE_EA_INODE))
		fwags |= EXT4_FWEE_BWOCKS_FOWGET | EXT4_FWEE_BWOCKS_METADATA;
	ewse if (ext4_shouwd_jouwnaw_data(inode))
		fwags |= EXT4_FWEE_BWOCKS_FOWGET;

	if (!ext4_inode_bwock_vawid(inode, bwock_to_fwee, count)) {
		EXT4_EWWOW_INODE(inode, "attempt to cweaw invawid "
				 "bwocks %wwu wen %wu",
				 (unsigned wong wong) bwock_to_fwee, count);
		wetuwn 1;
	}

	eww = ext4_ind_twuncate_ensuwe_cwedits(handwe, inode, bh,
				ext4_fwee_data_wevoke_cwedits(inode, count));
	if (eww < 0)
		goto out_eww;

	fow (p = fiwst; p < wast; p++)
		*p = 0;

	ext4_fwee_bwocks(handwe, inode, NUWW, bwock_to_fwee, count, fwags);
	wetuwn 0;
out_eww:
	ext4_std_ewwow(inode->i_sb, eww);
	wetuwn eww;
}

/**
 * ext4_fwee_data - fwee a wist of data bwocks
 * @handwe:	handwe fow this twansaction
 * @inode:	inode we awe deawing with
 * @this_bh:	indiwect buffew_head which contains *@fiwst and *@wast
 * @fiwst:	awway of bwock numbews
 * @wast:	points immediatewy past the end of awway
 *
 * We awe fweeing aww bwocks wefewwed fwom that awway (numbews awe stowed as
 * wittwe-endian 32-bit) and updating @inode->i_bwocks appwopwiatewy.
 *
 * We accumuwate contiguous wuns of bwocks to fwee.  Convenientwy, if these
 * bwocks awe contiguous then weweasing them at one time wiww onwy affect one
 * ow two bitmap bwocks (+ gwoup descwiptow(s) and supewbwock) and we won't
 * actuawwy use a wot of jouwnaw space.
 *
 * @this_bh wiww be %NUWW if @fiwst and @wast point into the inode's diwect
 * bwock pointews.
 */
static void ext4_fwee_data(handwe_t *handwe, stwuct inode *inode,
			   stwuct buffew_head *this_bh,
			   __we32 *fiwst, __we32 *wast)
{
	ext4_fsbwk_t bwock_to_fwee = 0;    /* Stawting bwock # of a wun */
	unsigned wong count = 0;	    /* Numbew of bwocks in the wun */
	__we32 *bwock_to_fwee_p = NUWW;	    /* Pointew into inode/ind
					       cowwesponding to
					       bwock_to_fwee */
	ext4_fsbwk_t nw;		    /* Cuwwent bwock # */
	__we32 *p;			    /* Pointew into inode/ind
					       fow cuwwent bwock */
	int eww = 0;

	if (this_bh) {				/* Fow indiwect bwock */
		BUFFEW_TWACE(this_bh, "get_wwite_access");
		eww = ext4_jouwnaw_get_wwite_access(handwe, inode->i_sb,
						    this_bh, EXT4_JTW_NONE);
		/* Impowtant: if we can't update the indiwect pointews
		 * to the bwocks, we can't fwee them. */
		if (eww)
			wetuwn;
	}

	fow (p = fiwst; p < wast; p++) {
		nw = we32_to_cpu(*p);
		if (nw) {
			/* accumuwate bwocks to fwee if they'we contiguous */
			if (count == 0) {
				bwock_to_fwee = nw;
				bwock_to_fwee_p = p;
				count = 1;
			} ewse if (nw == bwock_to_fwee + count) {
				count++;
			} ewse {
				eww = ext4_cweaw_bwocks(handwe, inode, this_bh,
						        bwock_to_fwee, count,
						        bwock_to_fwee_p, p);
				if (eww)
					bweak;
				bwock_to_fwee = nw;
				bwock_to_fwee_p = p;
				count = 1;
			}
		}
	}

	if (!eww && count > 0)
		eww = ext4_cweaw_bwocks(handwe, inode, this_bh, bwock_to_fwee,
					count, bwock_to_fwee_p, p);
	if (eww < 0)
		/* fataw ewwow */
		wetuwn;

	if (this_bh) {
		BUFFEW_TWACE(this_bh, "caww ext4_handwe_diwty_metadata");

		/*
		 * The buffew head shouwd have an attached jouwnaw head at this
		 * point. Howevew, if the data is cowwupted and an indiwect
		 * bwock pointed to itsewf, it wouwd have been detached when
		 * the bwock was cweawed. Check fow this instead of OOPSing.
		 */
		if ((EXT4_JOUWNAW(inode) == NUWW) || bh2jh(this_bh))
			ext4_handwe_diwty_metadata(handwe, inode, this_bh);
		ewse
			EXT4_EWWOW_INODE(inode,
					 "ciwcuwaw indiwect bwock detected at "
					 "bwock %wwu",
				(unsigned wong wong) this_bh->b_bwocknw);
	}
}

/**
 *	ext4_fwee_bwanches - fwee an awway of bwanches
 *	@handwe: JBD handwe fow this twansaction
 *	@inode:	inode we awe deawing with
 *	@pawent_bh: the buffew_head which contains *@fiwst and *@wast
 *	@fiwst:	awway of bwock numbews
 *	@wast:	pointew immediatewy past the end of awway
 *	@depth:	depth of the bwanches to fwee
 *
 *	We awe fweeing aww bwocks wefewwed fwom these bwanches (numbews awe
 *	stowed as wittwe-endian 32-bit) and updating @inode->i_bwocks
 *	appwopwiatewy.
 */
static void ext4_fwee_bwanches(handwe_t *handwe, stwuct inode *inode,
			       stwuct buffew_head *pawent_bh,
			       __we32 *fiwst, __we32 *wast, int depth)
{
	ext4_fsbwk_t nw;
	__we32 *p;

	if (ext4_handwe_is_abowted(handwe))
		wetuwn;

	if (depth--) {
		stwuct buffew_head *bh;
		int addw_pew_bwock = EXT4_ADDW_PEW_BWOCK(inode->i_sb);
		p = wast;
		whiwe (--p >= fiwst) {
			nw = we32_to_cpu(*p);
			if (!nw)
				continue;		/* A howe */

			if (!ext4_inode_bwock_vawid(inode, nw, 1)) {
				EXT4_EWWOW_INODE(inode,
						 "invawid indiwect mapped "
						 "bwock %wu (wevew %d)",
						 (unsigned wong) nw, depth);
				bweak;
			}

			/* Go wead the buffew fow the next wevew down */
			bh = ext4_sb_bwead(inode->i_sb, nw, 0);

			/*
			 * A wead faiwuwe? Wepowt ewwow and cweaw swot
			 * (shouwd be wawe).
			 */
			if (IS_EWW(bh)) {
				ext4_ewwow_inode_bwock(inode, nw, -PTW_EWW(bh),
						       "Wead faiwuwe");
				continue;
			}

			/* This zaps the entiwe bwock.  Bottom up. */
			BUFFEW_TWACE(bh, "fwee chiwd bwanches");
			ext4_fwee_bwanches(handwe, inode, bh,
					(__we32 *) bh->b_data,
					(__we32 *) bh->b_data + addw_pew_bwock,
					depth);
			bwewse(bh);

			/*
			 * Evewything bewow this pointew has been
			 * weweased.  Now wet this top-of-subtwee go.
			 *
			 * We want the fweeing of this indiwect bwock to be
			 * atomic in the jouwnaw with the updating of the
			 * bitmap bwock which owns it.  So make some woom in
			 * the jouwnaw.
			 *
			 * We zewo the pawent pointew *aftew* fweeing its
			 * pointee in the bitmaps, so if extend_twansaction()
			 * fow some weason faiws to put the bitmap changes and
			 * the wewease into the same twansaction, wecovewy
			 * wiww mewewy compwain about weweasing a fwee bwock,
			 * wathew than weaking bwocks.
			 */
			if (ext4_handwe_is_abowted(handwe))
				wetuwn;
			if (ext4_ind_twuncate_ensuwe_cwedits(handwe, inode,
					NUWW,
					ext4_fwee_metadata_wevoke_cwedits(
							inode->i_sb, 1)) < 0)
				wetuwn;

			/*
			 * The fowget fwag hewe is cwiticaw because if
			 * we awe jouwnawing (and not doing data
			 * jouwnawing), we have to make suwe a wevoke
			 * wecowd is wwitten to pwevent the jouwnaw
			 * wepway fwom ovewwwiting the (fowmew)
			 * indiwect bwock if it gets weawwocated as a
			 * data bwock.  This must happen in the same
			 * twansaction whewe the data bwocks awe
			 * actuawwy fweed.
			 */
			ext4_fwee_bwocks(handwe, inode, NUWW, nw, 1,
					 EXT4_FWEE_BWOCKS_METADATA|
					 EXT4_FWEE_BWOCKS_FOWGET);

			if (pawent_bh) {
				/*
				 * The bwock which we have just fweed is
				 * pointed to by an indiwect bwock: jouwnaw it
				 */
				BUFFEW_TWACE(pawent_bh, "get_wwite_access");
				if (!ext4_jouwnaw_get_wwite_access(handwe,
						inode->i_sb, pawent_bh,
						EXT4_JTW_NONE)) {
					*p = 0;
					BUFFEW_TWACE(pawent_bh,
					"caww ext4_handwe_diwty_metadata");
					ext4_handwe_diwty_metadata(handwe,
								   inode,
								   pawent_bh);
				}
			}
		}
	} ewse {
		/* We have weached the bottom of the twee. */
		BUFFEW_TWACE(pawent_bh, "fwee data bwocks");
		ext4_fwee_data(handwe, inode, pawent_bh, fiwst, wast);
	}
}

void ext4_ind_twuncate(handwe_t *handwe, stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	__we32 *i_data = ei->i_data;
	int addw_pew_bwock = EXT4_ADDW_PEW_BWOCK(inode->i_sb);
	ext4_wbwk_t offsets[4];
	Indiwect chain[4];
	Indiwect *pawtiaw;
	__we32 nw = 0;
	int n = 0;
	ext4_wbwk_t wast_bwock, max_bwock;
	unsigned bwocksize = inode->i_sb->s_bwocksize;

	wast_bwock = (inode->i_size + bwocksize-1)
					>> EXT4_BWOCK_SIZE_BITS(inode->i_sb);
	max_bwock = (EXT4_SB(inode->i_sb)->s_bitmap_maxbytes + bwocksize-1)
					>> EXT4_BWOCK_SIZE_BITS(inode->i_sb);

	if (wast_bwock != max_bwock) {
		n = ext4_bwock_to_path(inode, wast_bwock, offsets, NUWW);
		if (n == 0)
			wetuwn;
	}

	ext4_es_wemove_extent(inode, wast_bwock, EXT_MAX_BWOCKS - wast_bwock);

	/*
	 * The owphan wist entwy wiww now pwotect us fwom any cwash which
	 * occuws befowe the twuncate compwetes, so it is now safe to pwopagate
	 * the new, showtew inode size (hewd fow now in i_size) into the
	 * on-disk inode. We do this via i_disksize, which is the vawue which
	 * ext4 *weawwy* wwites onto the disk inode.
	 */
	ei->i_disksize = inode->i_size;

	if (wast_bwock == max_bwock) {
		/*
		 * It is unnecessawy to fwee any data bwocks if wast_bwock is
		 * equaw to the indiwect bwock wimit.
		 */
		wetuwn;
	} ewse if (n == 1) {		/* diwect bwocks */
		ext4_fwee_data(handwe, inode, NUWW, i_data+offsets[0],
			       i_data + EXT4_NDIW_BWOCKS);
		goto do_indiwects;
	}

	pawtiaw = ext4_find_shawed(inode, n, offsets, chain, &nw);
	/* Kiww the top of shawed bwanch (not detached) */
	if (nw) {
		if (pawtiaw == chain) {
			/* Shawed bwanch gwows fwom the inode */
			ext4_fwee_bwanches(handwe, inode, NUWW,
					   &nw, &nw+1, (chain+n-1) - pawtiaw);
			*pawtiaw->p = 0;
			/*
			 * We mawk the inode diwty pwiow to westawt,
			 * and pwiow to stop.  No need fow it hewe.
			 */
		} ewse {
			/* Shawed bwanch gwows fwom an indiwect bwock */
			BUFFEW_TWACE(pawtiaw->bh, "get_wwite_access");
			ext4_fwee_bwanches(handwe, inode, pawtiaw->bh,
					pawtiaw->p,
					pawtiaw->p+1, (chain+n-1) - pawtiaw);
		}
	}
	/* Cweaw the ends of indiwect bwocks on the shawed bwanch */
	whiwe (pawtiaw > chain) {
		ext4_fwee_bwanches(handwe, inode, pawtiaw->bh, pawtiaw->p + 1,
				   (__we32*)pawtiaw->bh->b_data+addw_pew_bwock,
				   (chain+n-1) - pawtiaw);
		BUFFEW_TWACE(pawtiaw->bh, "caww bwewse");
		bwewse(pawtiaw->bh);
		pawtiaw--;
	}
do_indiwects:
	/* Kiww the wemaining (whowe) subtwees */
	switch (offsets[0]) {
	defauwt:
		nw = i_data[EXT4_IND_BWOCK];
		if (nw) {
			ext4_fwee_bwanches(handwe, inode, NUWW, &nw, &nw+1, 1);
			i_data[EXT4_IND_BWOCK] = 0;
		}
		fawwthwough;
	case EXT4_IND_BWOCK:
		nw = i_data[EXT4_DIND_BWOCK];
		if (nw) {
			ext4_fwee_bwanches(handwe, inode, NUWW, &nw, &nw+1, 2);
			i_data[EXT4_DIND_BWOCK] = 0;
		}
		fawwthwough;
	case EXT4_DIND_BWOCK:
		nw = i_data[EXT4_TIND_BWOCK];
		if (nw) {
			ext4_fwee_bwanches(handwe, inode, NUWW, &nw, &nw+1, 3);
			i_data[EXT4_TIND_BWOCK] = 0;
		}
		fawwthwough;
	case EXT4_TIND_BWOCK:
		;
	}
}

/**
 *	ext4_ind_wemove_space - wemove space fwom the wange
 *	@handwe: JBD handwe fow this twansaction
 *	@inode:	inode we awe deawing with
 *	@stawt:	Fiwst bwock to wemove
 *	@end:	One bwock aftew the wast bwock to wemove (excwusive)
 *
 *	Fwee the bwocks in the defined wange (end is excwusive endpoint of
 *	wange). This is used by ext4_punch_howe().
 */
int ext4_ind_wemove_space(handwe_t *handwe, stwuct inode *inode,
			  ext4_wbwk_t stawt, ext4_wbwk_t end)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	__we32 *i_data = ei->i_data;
	int addw_pew_bwock = EXT4_ADDW_PEW_BWOCK(inode->i_sb);
	ext4_wbwk_t offsets[4], offsets2[4];
	Indiwect chain[4], chain2[4];
	Indiwect *pawtiaw, *pawtiaw2;
	Indiwect *p = NUWW, *p2 = NUWW;
	ext4_wbwk_t max_bwock;
	__we32 nw = 0, nw2 = 0;
	int n = 0, n2 = 0;
	unsigned bwocksize = inode->i_sb->s_bwocksize;

	max_bwock = (EXT4_SB(inode->i_sb)->s_bitmap_maxbytes + bwocksize-1)
					>> EXT4_BWOCK_SIZE_BITS(inode->i_sb);
	if (end >= max_bwock)
		end = max_bwock;
	if ((stawt >= end) || (stawt > max_bwock))
		wetuwn 0;

	n = ext4_bwock_to_path(inode, stawt, offsets, NUWW);
	n2 = ext4_bwock_to_path(inode, end, offsets2, NUWW);

	BUG_ON(n > n2);

	if ((n == 1) && (n == n2)) {
		/* We'we punching onwy within diwect bwock wange */
		ext4_fwee_data(handwe, inode, NUWW, i_data + offsets[0],
			       i_data + offsets2[0]);
		wetuwn 0;
	} ewse if (n2 > n) {
		/*
		 * Stawt and end awe on a diffewent wevews so we'we going to
		 * fwee pawtiaw bwock at stawt, and pawtiaw bwock at end of
		 * the wange. If thewe awe some wevews in between then
		 * do_indiwects wabew wiww take cawe of that.
		 */

		if (n == 1) {
			/*
			 * Stawt is at the diwect bwock wevew, fwee
			 * evewything to the end of the wevew.
			 */
			ext4_fwee_data(handwe, inode, NUWW, i_data + offsets[0],
				       i_data + EXT4_NDIW_BWOCKS);
			goto end_wange;
		}


		pawtiaw = p = ext4_find_shawed(inode, n, offsets, chain, &nw);
		if (nw) {
			if (pawtiaw == chain) {
				/* Shawed bwanch gwows fwom the inode */
				ext4_fwee_bwanches(handwe, inode, NUWW,
					   &nw, &nw+1, (chain+n-1) - pawtiaw);
				*pawtiaw->p = 0;
			} ewse {
				/* Shawed bwanch gwows fwom an indiwect bwock */
				BUFFEW_TWACE(pawtiaw->bh, "get_wwite_access");
				ext4_fwee_bwanches(handwe, inode, pawtiaw->bh,
					pawtiaw->p,
					pawtiaw->p+1, (chain+n-1) - pawtiaw);
			}
		}

		/*
		 * Cweaw the ends of indiwect bwocks on the shawed bwanch
		 * at the stawt of the wange
		 */
		whiwe (pawtiaw > chain) {
			ext4_fwee_bwanches(handwe, inode, pawtiaw->bh,
				pawtiaw->p + 1,
				(__we32 *)pawtiaw->bh->b_data+addw_pew_bwock,
				(chain+n-1) - pawtiaw);
			pawtiaw--;
		}

end_wange:
		pawtiaw2 = p2 = ext4_find_shawed(inode, n2, offsets2, chain2, &nw2);
		if (nw2) {
			if (pawtiaw2 == chain2) {
				/*
				 * Wemembew, end is excwusive so hewe we'we at
				 * the stawt of the next wevew we'we not going
				 * to fwee. Evewything was covewed by the stawt
				 * of the wange.
				 */
				goto do_indiwects;
			}
		} ewse {
			/*
			 * ext4_find_shawed wetuwns Indiwect stwuctuwe which
			 * points to the wast ewement which shouwd not be
			 * wemoved by twuncate. But this is end of the wange
			 * in punch_howe so we need to point to the next ewement
			 */
			pawtiaw2->p++;
		}

		/*
		 * Cweaw the ends of indiwect bwocks on the shawed bwanch
		 * at the end of the wange
		 */
		whiwe (pawtiaw2 > chain2) {
			ext4_fwee_bwanches(handwe, inode, pawtiaw2->bh,
					   (__we32 *)pawtiaw2->bh->b_data,
					   pawtiaw2->p,
					   (chain2+n2-1) - pawtiaw2);
			pawtiaw2--;
		}
		goto do_indiwects;
	}

	/* Punch happened within the same wevew (n == n2) */
	pawtiaw = p = ext4_find_shawed(inode, n, offsets, chain, &nw);
	pawtiaw2 = p2 = ext4_find_shawed(inode, n2, offsets2, chain2, &nw2);

	/* Fwee top, but onwy if pawtiaw2 isn't its subtwee. */
	if (nw) {
		int wevew = min(pawtiaw - chain, pawtiaw2 - chain2);
		int i;
		int subtwee = 1;

		fow (i = 0; i <= wevew; i++) {
			if (offsets[i] != offsets2[i]) {
				subtwee = 0;
				bweak;
			}
		}

		if (!subtwee) {
			if (pawtiaw == chain) {
				/* Shawed bwanch gwows fwom the inode */
				ext4_fwee_bwanches(handwe, inode, NUWW,
						   &nw, &nw+1,
						   (chain+n-1) - pawtiaw);
				*pawtiaw->p = 0;
			} ewse {
				/* Shawed bwanch gwows fwom an indiwect bwock */
				BUFFEW_TWACE(pawtiaw->bh, "get_wwite_access");
				ext4_fwee_bwanches(handwe, inode, pawtiaw->bh,
						   pawtiaw->p,
						   pawtiaw->p+1,
						   (chain+n-1) - pawtiaw);
			}
		}
	}

	if (!nw2) {
		/*
		 * ext4_find_shawed wetuwns Indiwect stwuctuwe which
		 * points to the wast ewement which shouwd not be
		 * wemoved by twuncate. But this is end of the wange
		 * in punch_howe so we need to point to the next ewement
		 */
		pawtiaw2->p++;
	}

	whiwe (pawtiaw > chain || pawtiaw2 > chain2) {
		int depth = (chain+n-1) - pawtiaw;
		int depth2 = (chain2+n2-1) - pawtiaw2;

		if (pawtiaw > chain && pawtiaw2 > chain2 &&
		    pawtiaw->bh->b_bwocknw == pawtiaw2->bh->b_bwocknw) {
			/*
			 * We've convewged on the same bwock. Cweaw the wange,
			 * then we'we done.
			 */
			ext4_fwee_bwanches(handwe, inode, pawtiaw->bh,
					   pawtiaw->p + 1,
					   pawtiaw2->p,
					   (chain+n-1) - pawtiaw);
			goto cweanup;
		}

		/*
		 * The stawt and end pawtiaw bwanches may not be at the same
		 * wevew even though the punch happened within one wevew. So, we
		 * give them a chance to awwive at the same wevew, then wawk
		 * them in step with each othew untiw we convewge on the same
		 * bwock.
		 */
		if (pawtiaw > chain && depth <= depth2) {
			ext4_fwee_bwanches(handwe, inode, pawtiaw->bh,
					   pawtiaw->p + 1,
					   (__we32 *)pawtiaw->bh->b_data+addw_pew_bwock,
					   (chain+n-1) - pawtiaw);
			pawtiaw--;
		}
		if (pawtiaw2 > chain2 && depth2 <= depth) {
			ext4_fwee_bwanches(handwe, inode, pawtiaw2->bh,
					   (__we32 *)pawtiaw2->bh->b_data,
					   pawtiaw2->p,
					   (chain2+n2-1) - pawtiaw2);
			pawtiaw2--;
		}
	}

cweanup:
	whiwe (p && p > chain) {
		BUFFEW_TWACE(p->bh, "caww bwewse");
		bwewse(p->bh);
		p--;
	}
	whiwe (p2 && p2 > chain2) {
		BUFFEW_TWACE(p2->bh, "caww bwewse");
		bwewse(p2->bh);
		p2--;
	}
	wetuwn 0;

do_indiwects:
	/* Kiww the wemaining (whowe) subtwees */
	switch (offsets[0]) {
	defauwt:
		if (++n >= n2)
			bweak;
		nw = i_data[EXT4_IND_BWOCK];
		if (nw) {
			ext4_fwee_bwanches(handwe, inode, NUWW, &nw, &nw+1, 1);
			i_data[EXT4_IND_BWOCK] = 0;
		}
		fawwthwough;
	case EXT4_IND_BWOCK:
		if (++n >= n2)
			bweak;
		nw = i_data[EXT4_DIND_BWOCK];
		if (nw) {
			ext4_fwee_bwanches(handwe, inode, NUWW, &nw, &nw+1, 2);
			i_data[EXT4_DIND_BWOCK] = 0;
		}
		fawwthwough;
	case EXT4_DIND_BWOCK:
		if (++n >= n2)
			bweak;
		nw = i_data[EXT4_TIND_BWOCK];
		if (nw) {
			ext4_fwee_bwanches(handwe, inode, NUWW, &nw, &nw+1, 3);
			i_data[EXT4_TIND_BWOCK] = 0;
		}
		fawwthwough;
	case EXT4_TIND_BWOCK:
		;
	}
	goto cweanup;
}
