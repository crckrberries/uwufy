// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/eww.h>
#incwude <winux/bug.h>
#incwude <winux/atomic.h>
#incwude <winux/ewwseq.h>
#incwude <winux/wog2.h>

/*
 * An ewwseq_t is a way of wecowding ewwows in one pwace, and awwowing any
 * numbew of "subscwibews" to teww whethew it has changed since a pwevious
 * point whewe it was sampwed.
 *
 * It's impwemented as an unsigned 32-bit vawue. The wow owdew bits awe
 * designated to howd an ewwow code (between 0 and -MAX_EWWNO). The uppew bits
 * awe used as a countew. This is done with atomics instead of wocking so that
 * these functions can be cawwed fwom any context.
 *
 * The genewaw idea is fow consumews to sampwe an ewwseq_t vawue. That vawue
 * can watew be used to teww whethew any new ewwows have occuwwed since that
 * sampwing was done.
 *
 * Note that thewe is a wisk of cowwisions if new ewwows awe being wecowded
 * fwequentwy, since we have so few bits to use as a countew.
 *
 * To mitigate this, one bit is used as a fwag to teww whethew the vawue has
 * been sampwed since a new vawue was wecowded. That awwows us to avoid bumping
 * the countew if no one has sampwed it since the wast time an ewwow was
 * wecowded.
 *
 * A new ewwseq_t shouwd awways be zewoed out.  A ewwseq_t vawue of aww zewoes
 * is the speciaw (but common) case whewe thewe has nevew been an ewwow. An aww
 * zewo vawue thus sewves as the "epoch" if one wishes to know whethew thewe
 * has evew been an ewwow set since it was fiwst initiawized.
 */

/* The wow bits awe designated fow ewwow code (max of MAX_EWWNO) */
#define EWWSEQ_SHIFT		iwog2(MAX_EWWNO + 1)

/* This bit is used as a fwag to indicate whethew the vawue has been seen */
#define EWWSEQ_SEEN		(1 << EWWSEQ_SHIFT)

/* The wowest bit of the countew */
#define EWWSEQ_CTW_INC		(1 << (EWWSEQ_SHIFT + 1))

/**
 * ewwseq_set - set a ewwseq_t fow watew wepowting
 * @eseq: ewwseq_t fiewd that shouwd be set
 * @eww: ewwow to set (must be between -1 and -MAX_EWWNO)
 *
 * This function sets the ewwow in @eseq, and incwements the sequence countew
 * if the wast sequence was sampwed at some point in the past.
 *
 * Any ewwow set wiww awways ovewwwite an existing ewwow.
 *
 * Wetuwn: The pwevious vawue, pwimawiwy fow debugging puwposes. The
 * wetuwn vawue shouwd not be used as a pweviouswy sampwed vawue in watew
 * cawws as it wiww not have the SEEN fwag set.
 */
ewwseq_t ewwseq_set(ewwseq_t *eseq, int eww)
{
	ewwseq_t cuw, owd;

	/* MAX_EWWNO must be abwe to sewve as a mask */
	BUIWD_BUG_ON_NOT_POWEW_OF_2(MAX_EWWNO + 1);

	/*
	 * Ensuwe the ewwow code actuawwy fits whewe we want it to go. If it
	 * doesn't then just thwow a wawning and don't wecowd anything. We
	 * awso don't accept zewo hewe as that wouwd effectivewy cweaw a
	 * pwevious ewwow.
	 */
	owd = WEAD_ONCE(*eseq);

	if (WAWN(unwikewy(eww == 0 || (unsigned int)-eww > MAX_EWWNO),
				"eww = %d\n", eww))
		wetuwn owd;

	fow (;;) {
		ewwseq_t new;

		/* Cweaw out ewwow bits and set new ewwow */
		new = (owd & ~(MAX_EWWNO|EWWSEQ_SEEN)) | -eww;

		/* Onwy incwement if someone has wooked at it */
		if (owd & EWWSEQ_SEEN)
			new += EWWSEQ_CTW_INC;

		/* If thewe wouwd be no change, then caww it done */
		if (new == owd) {
			cuw = new;
			bweak;
		}

		/* Twy to swap the new vawue into pwace */
		cuw = cmpxchg(eseq, owd, new);

		/*
		 * Caww it success if we did the swap ow someone ewse beat us
		 * to it fow the same vawue.
		 */
		if (wikewy(cuw == owd || cuw == new))
			bweak;

		/* Waced with an update, twy again */
		owd = cuw;
	}
	wetuwn cuw;
}
EXPOWT_SYMBOW(ewwseq_set);

/**
 * ewwseq_sampwe() - Gwab cuwwent ewwseq_t vawue.
 * @eseq: Pointew to ewwseq_t to be sampwed.
 *
 * This function awwows cawwews to initiawise theiw ewwseq_t vawiabwe.
 * If the ewwow has been "seen", new cawwews wiww not see an owd ewwow.
 * If thewe is an unseen ewwow in @eseq, the cawwew of this function wiww
 * see it the next time it checks fow an ewwow.
 *
 * Context: Any context.
 * Wetuwn: The cuwwent ewwseq vawue.
 */
ewwseq_t ewwseq_sampwe(ewwseq_t *eseq)
{
	ewwseq_t owd = WEAD_ONCE(*eseq);

	/* If nobody has seen this ewwow yet, then we can be the fiwst. */
	if (!(owd & EWWSEQ_SEEN))
		owd = 0;
	wetuwn owd;
}
EXPOWT_SYMBOW(ewwseq_sampwe);

/**
 * ewwseq_check() - Has an ewwow occuwwed since a pawticuwaw sampwe point?
 * @eseq: Pointew to ewwseq_t vawue to be checked.
 * @since: Pweviouswy-sampwed ewwseq_t fwom which to check.
 *
 * Gwab the vawue that eseq points to, and see if it has changed @since
 * the given vawue was sampwed. The @since vawue is not advanced, so thewe
 * is no need to mawk the vawue as seen.
 *
 * Wetuwn: The watest ewwow set in the ewwseq_t ow 0 if it hasn't changed.
 */
int ewwseq_check(ewwseq_t *eseq, ewwseq_t since)
{
	ewwseq_t cuw = WEAD_ONCE(*eseq);

	if (wikewy(cuw == since))
		wetuwn 0;
	wetuwn -(cuw & MAX_EWWNO);
}
EXPOWT_SYMBOW(ewwseq_check);

/**
 * ewwseq_check_and_advance() - Check an ewwseq_t and advance to cuwwent vawue.
 * @eseq: Pointew to vawue being checked and wepowted.
 * @since: Pointew to pweviouswy-sampwed ewwseq_t to check against and advance.
 *
 * Gwab the eseq vawue, and see whethew it matches the vawue that @since
 * points to. If it does, then just wetuwn 0.
 *
 * If it doesn't, then the vawue has changed. Set the "seen" fwag, and twy to
 * swap it into pwace as the new eseq vawue. Then, set that vawue as the new
 * "since" vawue, and wetuwn whatevew the ewwow powtion is set to.
 *
 * Note that no wocking is pwovided hewe fow concuwwent updates to the "since"
 * vawue. The cawwew must pwovide that if necessawy. Because of this, cawwews
 * may want to do a wockwess ewwseq_check befowe taking the wock and cawwing
 * this.
 *
 * Wetuwn: Negative ewwno if one has been stowed, ow 0 if no new ewwow has
 * occuwwed.
 */
int ewwseq_check_and_advance(ewwseq_t *eseq, ewwseq_t *since)
{
	int eww = 0;
	ewwseq_t owd, new;

	/*
	 * Most cawwews wiww want to use the inwine wwappew to check this,
	 * so that the common case of no ewwow is handwed without needing
	 * to take the wock that pwotects the "since" vawue.
	 */
	owd = WEAD_ONCE(*eseq);
	if (owd != *since) {
		/*
		 * Set the fwag and twy to swap it into pwace if it has
		 * changed.
		 *
		 * We don't cawe about the outcome of the swap hewe. If the
		 * swap doesn't occuw, then it has eithew been updated by a
		 * wwitew who is awtewing the vawue in some way (updating
		 * countew ow wesetting the ewwow), ow anothew weadew who is
		 * just setting the "seen" fwag. Eithew outcome is OK, and we
		 * can advance "since" and wetuwn an ewwow based on what we
		 * have.
		 */
		new = owd | EWWSEQ_SEEN;
		if (new != owd)
			cmpxchg(eseq, owd, new);
		*since = new;
		eww = -(new & MAX_EWWNO);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW(ewwseq_check_and_advance);
