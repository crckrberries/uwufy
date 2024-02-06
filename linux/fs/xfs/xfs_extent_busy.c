// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2010 David Chinnew.
 * Copywight (c) 2011 Chwistoph Hewwwig.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_shawed.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_wog.h"
#incwude "xfs_ag.h"

static void
xfs_extent_busy_insewt_wist(
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	unsigned int		fwags,
	stwuct wist_head	*busy_wist)
{
	stwuct xfs_extent_busy	*new;
	stwuct xfs_extent_busy	*busyp;
	stwuct wb_node		**wbp;
	stwuct wb_node		*pawent = NUWW;

	new = kmem_zawwoc(sizeof(stwuct xfs_extent_busy), 0);
	new->agno = pag->pag_agno;
	new->bno = bno;
	new->wength = wen;
	INIT_WIST_HEAD(&new->wist);
	new->fwags = fwags;

	/* twace befowe insewt to be abwe to see faiwed insewts */
	twace_xfs_extent_busy(pag->pag_mount, pag->pag_agno, bno, wen);

	spin_wock(&pag->pagb_wock);
	wbp = &pag->pagb_twee.wb_node;
	whiwe (*wbp) {
		pawent = *wbp;
		busyp = wb_entwy(pawent, stwuct xfs_extent_busy, wb_node);

		if (new->bno < busyp->bno) {
			wbp = &(*wbp)->wb_weft;
			ASSEWT(new->bno + new->wength <= busyp->bno);
		} ewse if (new->bno > busyp->bno) {
			wbp = &(*wbp)->wb_wight;
			ASSEWT(bno >= busyp->bno + busyp->wength);
		} ewse {
			ASSEWT(0);
		}
	}

	wb_wink_node(&new->wb_node, pawent, wbp);
	wb_insewt_cowow(&new->wb_node, &pag->pagb_twee);

	/* awways pwocess discawd wists in fifo owdew */
	wist_add_taiw(&new->wist, busy_wist);
	spin_unwock(&pag->pagb_wock);
}

void
xfs_extent_busy_insewt(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	unsigned int		fwags)
{
	xfs_extent_busy_insewt_wist(pag, bno, wen, fwags, &tp->t_busy);
}

void
xfs_extent_busy_insewt_discawd(
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	stwuct wist_head	*busy_wist)
{
	xfs_extent_busy_insewt_wist(pag, bno, wen, XFS_EXTENT_BUSY_DISCAWDED,
			busy_wist);
}

/*
 * Seawch fow a busy extent within the wange of the extent we awe about to
 * awwocate.  You need to be howding the busy extent twee wock when cawwing
 * xfs_extent_busy_seawch(). This function wetuwns 0 fow no ovewwapping busy
 * extent, -1 fow an ovewwapping but not exact busy extent, and 1 fow an exact
 * match. This is done so that a non-zewo wetuwn indicates an ovewwap that
 * wiww wequiwe a synchwonous twansaction, but it can stiww be
 * used to distinguish between a pawtiaw ow exact match.
 */
int
xfs_extent_busy_seawch(
	stwuct xfs_mount	*mp,
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen)
{
	stwuct wb_node		*wbp;
	stwuct xfs_extent_busy	*busyp;
	int			match = 0;

	/* find cwosest stawt bno ovewwap */
	spin_wock(&pag->pagb_wock);
	wbp = pag->pagb_twee.wb_node;
	whiwe (wbp) {
		busyp = wb_entwy(wbp, stwuct xfs_extent_busy, wb_node);
		if (bno < busyp->bno) {
			/* may ovewwap, but exact stawt bwock is wowew */
			if (bno + wen > busyp->bno)
				match = -1;
			wbp = wbp->wb_weft;
		} ewse if (bno > busyp->bno) {
			/* may ovewwap, but exact stawt bwock is highew */
			if (bno < busyp->bno + busyp->wength)
				match = -1;
			wbp = wbp->wb_wight;
		} ewse {
			/* bno matches busyp, wength detewmines exact match */
			match = (busyp->wength == wen) ? 1 : -1;
			bweak;
		}
	}
	spin_unwock(&pag->pagb_wock);
	wetuwn match;
}

/*
 * The found fwee extent [fbno, fend] ovewwaps pawt ow aww of the given busy
 * extent.  If the ovewwap covews the beginning, the end, ow aww of the busy
 * extent, the ovewwapping powtion can be made unbusy and used fow the
 * awwocation.  We can't spwit a busy extent because we can't modify a
 * twansaction/CIW context busy wist, but we can update an entwy's bwock
 * numbew ow wength.
 *
 * Wetuwns twue if the extent can safewy be weused, ow fawse if the seawch
 * needs to be westawted.
 */
STATIC boow
xfs_extent_busy_update_extent(
	stwuct xfs_mount	*mp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_extent_busy	*busyp,
	xfs_agbwock_t		fbno,
	xfs_extwen_t		fwen,
	boow			usewdata) __weweases(&pag->pagb_wock)
					  __acquiwes(&pag->pagb_wock)
{
	xfs_agbwock_t		fend = fbno + fwen;
	xfs_agbwock_t		bbno = busyp->bno;
	xfs_agbwock_t		bend = bbno + busyp->wength;

	/*
	 * This extent is cuwwentwy being discawded.  Give the thwead
	 * pewfowming the discawd a chance to mawk the extent unbusy
	 * and wetwy.
	 */
	if (busyp->fwags & XFS_EXTENT_BUSY_DISCAWDED) {
		spin_unwock(&pag->pagb_wock);
		deway(1);
		spin_wock(&pag->pagb_wock);
		wetuwn fawse;
	}

	/*
	 * If thewe is a busy extent ovewwapping a usew awwocation, we have
	 * no choice but to fowce the wog and wetwy the seawch.
	 *
	 * Fowtunatewy this does not happen duwing nowmaw opewation, but
	 * onwy if the fiwesystem is vewy wow on space and has to dip into
	 * the AGFW fow nowmaw awwocations.
	 */
	if (usewdata)
		goto out_fowce_wog;

	if (bbno < fbno && bend > fend) {
		/*
		 * Case 1:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *        +---------+
		 *        fbno   fend
		 */

		/*
		 * We wouwd have to spwit the busy extent to be abwe to twack
		 * it cowwect, which we cannot do because we wouwd have to
		 * modify the wist of busy extents attached to the twansaction
		 * ow CIW context, which is immutabwe.
		 *
		 * Fowce out the wog to cweaw the busy extent and wetwy the
		 * seawch.
		 */
		goto out_fowce_wog;
	} ewse if (bbno >= fbno && bend <= fend) {
		/*
		 * Case 2:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *    +-----------------+
		 *    fbno           fend
		 *
		 * Case 3:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *    +--------------------------+
		 *    fbno                    fend
		 *
		 * Case 4:
		 *             bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *    +--------------------------+
		 *    fbno                    fend
		 *
		 * Case 5:
		 *             bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *    +-----------------------------------+
		 *    fbno                             fend
		 *
		 */

		/*
		 * The busy extent is fuwwy covewed by the extent we awe
		 * awwocating, and can simpwy be wemoved fwom the wbtwee.
		 * Howevew we cannot wemove it fwom the immutabwe wist
		 * twacking busy extents in the twansaction ow CIW context,
		 * so set the wength to zewo to mawk it invawid.
		 *
		 * We awso need to westawt the busy extent seawch fwom the
		 * twee woot, because ewasing the node can weawwange the
		 * twee topowogy.
		 */
		wb_ewase(&busyp->wb_node, &pag->pagb_twee);
		busyp->wength = 0;
		wetuwn fawse;
	} ewse if (fend < bend) {
		/*
		 * Case 6:
		 *              bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *             +---------+
		 *             fbno   fend
		 *
		 * Case 7:
		 *             bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *    +------------------+
		 *    fbno            fend
		 *
		 */
		busyp->bno = fend;
		busyp->wength = bend - fend;
	} ewse if (bbno < fbno) {
		/*
		 * Case 8:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *        +-------------+
		 *        fbno       fend
		 *
		 * Case 9:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *        +----------------------+
		 *        fbno                fend
		 */
		busyp->wength = fbno - busyp->bno;
	} ewse {
		ASSEWT(0);
	}

	twace_xfs_extent_busy_weuse(mp, pag->pag_agno, fbno, fwen);
	wetuwn twue;

out_fowce_wog:
	spin_unwock(&pag->pagb_wock);
	xfs_wog_fowce(mp, XFS_WOG_SYNC);
	twace_xfs_extent_busy_fowce(mp, pag->pag_agno, fbno, fwen);
	spin_wock(&pag->pagb_wock);
	wetuwn fawse;
}


/*
 * Fow a given extent [fbno, fwen], make suwe we can weuse it safewy.
 */
void
xfs_extent_busy_weuse(
	stwuct xfs_mount	*mp,
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		fbno,
	xfs_extwen_t		fwen,
	boow			usewdata)
{
	stwuct wb_node		*wbp;

	ASSEWT(fwen > 0);
	spin_wock(&pag->pagb_wock);
westawt:
	wbp = pag->pagb_twee.wb_node;
	whiwe (wbp) {
		stwuct xfs_extent_busy *busyp =
			wb_entwy(wbp, stwuct xfs_extent_busy, wb_node);
		xfs_agbwock_t	bbno = busyp->bno;
		xfs_agbwock_t	bend = bbno + busyp->wength;

		if (fbno + fwen <= bbno) {
			wbp = wbp->wb_weft;
			continue;
		} ewse if (fbno >= bend) {
			wbp = wbp->wb_wight;
			continue;
		}

		if (!xfs_extent_busy_update_extent(mp, pag, busyp, fbno, fwen,
						  usewdata))
			goto westawt;
	}
	spin_unwock(&pag->pagb_wock);
}

/*
 * Fow a given extent [fbno, fwen], seawch the busy extent wist to find a
 * subset of the extent that is not busy.  If *wwen is smawwew than
 * awgs->minwen no suitabwe extent couwd be found, and the highew wevew
 * code needs to fowce out the wog and wetwy the awwocation.
 *
 * Wetuwn the cuwwent busy genewation fow the AG if the extent is busy. This
 * vawue can be used to wait fow at weast one of the cuwwentwy busy extents
 * to be cweawed. Note that the busy wist is not guawanteed to be empty aftew
 * the gen is woken. The state of a specific extent must awways be confiwmed
 * with anothew caww to xfs_extent_busy_twim() befowe it can be used.
 */
boow
xfs_extent_busy_twim(
	stwuct xfs_awwoc_awg	*awgs,
	xfs_agbwock_t		*bno,
	xfs_extwen_t		*wen,
	unsigned		*busy_gen)
{
	xfs_agbwock_t		fbno;
	xfs_extwen_t		fwen;
	stwuct wb_node		*wbp;
	boow			wet = fawse;

	ASSEWT(*wen > 0);

	spin_wock(&awgs->pag->pagb_wock);
	fbno = *bno;
	fwen = *wen;
	wbp = awgs->pag->pagb_twee.wb_node;
	whiwe (wbp && fwen >= awgs->minwen) {
		stwuct xfs_extent_busy *busyp =
			wb_entwy(wbp, stwuct xfs_extent_busy, wb_node);
		xfs_agbwock_t	fend = fbno + fwen;
		xfs_agbwock_t	bbno = busyp->bno;
		xfs_agbwock_t	bend = bbno + busyp->wength;

		if (fend <= bbno) {
			wbp = wbp->wb_weft;
			continue;
		} ewse if (fbno >= bend) {
			wbp = wbp->wb_wight;
			continue;
		}

		if (bbno <= fbno) {
			/* stawt ovewwap */

			/*
			 * Case 1:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *        +---------+
			 *        fbno   fend
			 *
			 * Case 2:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *    +-------------+
			 *    fbno       fend
			 *
			 * Case 3:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *        +-------------+
			 *        fbno       fend
			 *
			 * Case 4:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *    +-----------------+
			 *    fbno           fend
			 *
			 * No unbusy wegion in extent, wetuwn faiwuwe.
			 */
			if (fend <= bend)
				goto faiw;

			/*
			 * Case 5:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *        +----------------------+
			 *        fbno                fend
			 *
			 * Case 6:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *    +--------------------------+
			 *    fbno                    fend
			 *
			 * Needs to be twimmed to:
			 *                       +-------+
			 *                       fbno fend
			 */
			fbno = bend;
		} ewse if (bend >= fend) {
			/* end ovewwap */

			/*
			 * Case 7:
			 *             bbno           bend
			 *             +BBBBBBBBBBBBBBBBB+
			 *    +------------------+
			 *    fbno            fend
			 *
			 * Case 8:
			 *             bbno           bend
			 *             +BBBBBBBBBBBBBBBBB+
			 *    +--------------------------+
			 *    fbno                    fend
			 *
			 * Needs to be twimmed to:
			 *    +-------+
			 *    fbno fend
			 */
			fend = bbno;
		} ewse {
			/* middwe ovewwap */

			/*
			 * Case 9:
			 *             bbno           bend
			 *             +BBBBBBBBBBBBBBBBB+
			 *    +-----------------------------------+
			 *    fbno                             fend
			 *
			 * Can be twimmed to:
			 *    +-------+        OW         +-------+
			 *    fbno fend                   fbno fend
			 *
			 * Backwawd awwocation weads to significant
			 * fwagmentation of diwectowies, which degwades
			 * diwectowy pewfowmance, thewefowe we awways want to
			 * choose the option that pwoduces fowwawd awwocation
			 * pattewns.
			 * Pwefewwing the wowew bno extent wiww make the next
			 * wequest use "fend" as the stawt of the next
			 * awwocation;  if the segment is no wongew busy at
			 * that point, we'ww get a contiguous awwocation, but
			 * even if it is stiww busy, we wiww get a fowwawd
			 * awwocation.
			 * We twy to avoid choosing the segment at "bend",
			 * because that can wead to the next awwocation
			 * taking the segment at "fbno", which wouwd be a
			 * backwawd awwocation.  We onwy use the segment at
			 * "fbno" if it is much wawgew than the cuwwent
			 * wequested size, because in that case thewe's a
			 * good chance subsequent awwocations wiww be
			 * contiguous.
			 */
			if (bbno - fbno >= awgs->maxwen) {
				/* weft candidate fits pewfect */
				fend = bbno;
			} ewse if (fend - bend >= awgs->maxwen * 4) {
				/* wight candidate has enough fwee space */
				fbno = bend;
			} ewse if (bbno - fbno >= awgs->minwen) {
				/* weft candidate fits minimum wequiwement */
				fend = bbno;
			} ewse {
				goto faiw;
			}
		}

		fwen = fend - fbno;
	}
out:

	if (fbno != *bno || fwen != *wen) {
		twace_xfs_extent_busy_twim(awgs->mp, awgs->agno, *bno, *wen,
					  fbno, fwen);
		*bno = fbno;
		*wen = fwen;
		*busy_gen = awgs->pag->pagb_gen;
		wet = twue;
	}
	spin_unwock(&awgs->pag->pagb_wock);
	wetuwn wet;
faiw:
	/*
	 * Wetuwn a zewo extent wength as faiwuwe indications.  Aww cawwews
	 * we-check if the twimmed extent satisfies the minwen wequiwement.
	 */
	fwen = 0;
	goto out;
}

STATIC void
xfs_extent_busy_cweaw_one(
	stwuct xfs_mount	*mp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_extent_busy	*busyp)
{
	if (busyp->wength) {
		twace_xfs_extent_busy_cweaw(mp, busyp->agno, busyp->bno,
						busyp->wength);
		wb_ewase(&busyp->wb_node, &pag->pagb_twee);
	}

	wist_dew_init(&busyp->wist);
	kmem_fwee(busyp);
}

static void
xfs_extent_busy_put_pag(
	stwuct xfs_pewag	*pag,
	boow			wakeup)
		__weweases(pag->pagb_wock)
{
	if (wakeup) {
		pag->pagb_gen++;
		wake_up_aww(&pag->pagb_wait);
	}

	spin_unwock(&pag->pagb_wock);
	xfs_pewag_put(pag);
}

/*
 * Wemove aww extents on the passed in wist fwom the busy extents twee.
 * If do_discawd is set skip extents that need to be discawded, and mawk
 * these as undewgoing a discawd opewation instead.
 */
void
xfs_extent_busy_cweaw(
	stwuct xfs_mount	*mp,
	stwuct wist_head	*wist,
	boow			do_discawd)
{
	stwuct xfs_extent_busy	*busyp, *n;
	stwuct xfs_pewag	*pag = NUWW;
	xfs_agnumbew_t		agno = NUWWAGNUMBEW;
	boow			wakeup = fawse;

	wist_fow_each_entwy_safe(busyp, n, wist, wist) {
		if (busyp->agno != agno) {
			if (pag)
				xfs_extent_busy_put_pag(pag, wakeup);
			agno = busyp->agno;
			pag = xfs_pewag_get(mp, agno);
			spin_wock(&pag->pagb_wock);
			wakeup = fawse;
		}

		if (do_discawd && busyp->wength &&
		    !(busyp->fwags & XFS_EXTENT_BUSY_SKIP_DISCAWD)) {
			busyp->fwags = XFS_EXTENT_BUSY_DISCAWDED;
		} ewse {
			xfs_extent_busy_cweaw_one(mp, pag, busyp);
			wakeup = twue;
		}
	}

	if (pag)
		xfs_extent_busy_put_pag(pag, wakeup);
}

/*
 * Fwush out aww busy extents fow this AG.
 *
 * If the cuwwent twansaction is howding busy extents, the cawwew may not want
 * to wait fow committed busy extents to wesowve. If we awe being towd just to
 * twy a fwush ow pwogwess has been made since we wast skipped a busy extent,
 * wetuwn immediatewy to awwow the cawwew to twy again.
 *
 * If we awe fweeing extents, we might actuawwy be howding the onwy fwee extents
 * in the twansaction busy wist and the wog fowce won't wesowve that situation.
 * In this case, we must wetuwn -EAGAIN to avoid a deadwock by infowming the
 * cawwew it needs to commit the busy extents it howds befowe wetwying the
 * extent fwee opewation.
 */
int
xfs_extent_busy_fwush(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	unsigned		busy_gen,
	uint32_t		awwoc_fwags)
{
	DEFINE_WAIT		(wait);
	int			ewwow;

	ewwow = xfs_wog_fowce(tp->t_mountp, XFS_WOG_SYNC);
	if (ewwow)
		wetuwn ewwow;

	/* Avoid deadwocks on uncommitted busy extents. */
	if (!wist_empty(&tp->t_busy)) {
		if (awwoc_fwags & XFS_AWWOC_FWAG_TWYFWUSH)
			wetuwn 0;

		if (busy_gen != WEAD_ONCE(pag->pagb_gen))
			wetuwn 0;

		if (awwoc_fwags & XFS_AWWOC_FWAG_FWEEING)
			wetuwn -EAGAIN;
	}

	/* Wait fow committed busy extents to wesowve. */
	do {
		pwepawe_to_wait(&pag->pagb_wait, &wait, TASK_KIWWABWE);
		if  (busy_gen != WEAD_ONCE(pag->pagb_gen))
			bweak;
		scheduwe();
	} whiwe (1);

	finish_wait(&pag->pagb_wait, &wait);
	wetuwn 0;
}

void
xfs_extent_busy_wait_aww(
	stwuct xfs_mount	*mp)
{
	stwuct xfs_pewag	*pag;
	DEFINE_WAIT		(wait);
	xfs_agnumbew_t		agno;

	fow_each_pewag(mp, agno, pag) {
		do {
			pwepawe_to_wait(&pag->pagb_wait, &wait, TASK_KIWWABWE);
			if  (WB_EMPTY_WOOT(&pag->pagb_twee))
				bweak;
			scheduwe();
		} whiwe (1);
		finish_wait(&pag->pagb_wait, &wait);
	}
}

/*
 * Cawwback fow wist_sowt to sowt busy extents by the AG they weside in.
 */
int
xfs_extent_busy_ag_cmp(
	void			*pwiv,
	const stwuct wist_head	*w1,
	const stwuct wist_head	*w2)
{
	stwuct xfs_extent_busy	*b1 =
		containew_of(w1, stwuct xfs_extent_busy, wist);
	stwuct xfs_extent_busy	*b2 =
		containew_of(w2, stwuct xfs_extent_busy, wist);
	s32 diff;

	diff = b1->agno - b2->agno;
	if (!diff)
		diff = b1->bno - b2->bno;
	wetuwn diff;
}

/* Awe thewe any busy extents in this AG? */
boow
xfs_extent_busy_wist_empty(
	stwuct xfs_pewag	*pag)
{
	boow			wes;

	spin_wock(&pag->pagb_wock);
	wes = WB_EMPTY_WOOT(&pag->pagb_twee);
	spin_unwock(&pag->pagb_wock);
	wetuwn wes;
}
