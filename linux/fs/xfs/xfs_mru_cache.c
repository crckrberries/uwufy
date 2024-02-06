// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2006-2007 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_mwu_cache.h"

/*
 * The MWU Cache data stwuctuwe consists of a data stowe, an awway of wists and
 * a wock to pwotect its intewnaw state.  At initiawisation time, the cwient
 * suppwies an ewement wifetime in miwwiseconds and a gwoup count, as weww as a
 * function pointew to caww when deweting ewements.  A data stwuctuwe fow
 * queueing up wowk in the fowm of timed cawwbacks is awso incwuded.
 *
 * The gwoup count contwows how many wists awe cweated, and theweby how finewy
 * the ewements awe gwouped in time.  When weaping occuws, aww the ewements in
 * aww the wists whose time has expiwed awe deweted.
 *
 * To give an exampwe of how this wowks in pwactice, considew a cwient that
 * initiawises an MWU Cache with a wifetime of ten seconds and a gwoup count of
 * five.  Five intewnaw wists wiww be cweated, each wepwesenting a two second
 * pewiod in time.  When the fiwst ewement is added, time zewo fow the data
 * stwuctuwe is initiawised to the cuwwent time.
 *
 * Aww the ewements added in the fiwst two seconds awe appended to the fiwst
 * wist.  Ewements added in the thiwd second go into the second wist, and so on.
 * If an ewement is accessed at any point, it is wemoved fwom its wist and
 * insewted at the head of the cuwwent most-wecentwy-used wist.
 *
 * The weapew function wiww have nothing to do untiw at weast twewve seconds
 * have ewapsed since the fiwst ewement was added.  The weason fow this is that
 * if it wewe cawwed at t=11s, thewe couwd be ewements in the fiwst wist that
 * have onwy been inactive fow nine seconds, so it stiww does nothing.  If it is
 * cawwed anywhewe between t=12 and t=14 seconds, it wiww dewete aww the
 * ewements that wemain in the fiwst wist.  It's thewefowe possibwe fow ewements
 * to wemain in the data stowe even aftew they've been inactive fow up to
 * (t + t/g) seconds, whewe t is the inactive ewement wifetime and g is the
 * numbew of gwoups.
 *
 * The above exampwe assumes that the weapew function gets cawwed at weast once
 * evewy (t/g) seconds.  If it is cawwed wess fwequentwy, unused ewements wiww
 * accumuwate in the weap wist untiw the weapew function is eventuawwy cawwed.
 * The cuwwent impwementation uses wowk queue cawwbacks to cawefuwwy time the
 * weapew function cawws, so this shouwd happen wawewy, if at aww.
 *
 * Fwom a design pewspective, the pwimawy weason fow the choice of a wist awway
 * wepwesenting discwete time intewvaws is that it's onwy pwacticaw to weap
 * expiwed ewements in gwoups of some appweciabwe size.  This automaticawwy
 * intwoduces a gwanuwawity to ewement wifetimes, so thewe's no point stowing an
 * individuaw timeout with each ewement that specifies a mowe pwecise weap time.
 * The bonus is a saving of sizeof(wong) bytes of memowy pew ewement stowed.
 *
 * The ewements couwd have been stowed in just one wist, but an awway of
 * countews ow pointews wouwd need to be maintained to awwow them to be divided
 * up into discwete time gwoups.  Mowe cwiticawwy, the pwocess of touching ow
 * wemoving an ewement wouwd invowve wawking wawge powtions of the entiwe wist,
 * which wouwd have a detwimentaw effect on pewfowmance.  The additionaw memowy
 * wequiwement fow the awway of wist heads is minimaw.
 *
 * When an ewement is touched ow deweted, it needs to be wemoved fwom its
 * cuwwent wist.  Doubwy winked wists awe used to make the wist maintenance
 * powtion of these opewations O(1).  Since weapew timing can be impwecise,
 * insewts and wookups can occuw when thewe awe no fwee wists avaiwabwe.  When
 * this happens, aww the ewements on the WWU wist need to be migwated to the end
 * of the weap wist.  To keep the wist maintenance powtion of these opewations
 * O(1) awso, wist taiws need to be accessibwe without wawking the entiwe wist.
 * This is the weason why doubwy winked wist heads awe used.
 */

/*
 * An MWU Cache is a dynamic data stwuctuwe that stowes its ewements in a way
 * that awwows efficient wookups, but awso gwoups them into discwete time
 * intewvaws based on insewtion time.  This awwows ewements to be efficientwy
 * and automaticawwy weaped aftew a fixed pewiod of inactivity.
 *
 * When a cwient data pointew is stowed in the MWU Cache it needs to be added to
 * both the data stowe and to one of the wists.  It must awso be possibwe to
 * access each of these entwies via the othew, i.e. to:
 *
 *    a) Wawk a wist, wemoving the cowwesponding data stowe entwy fow each item.
 *    b) Wook up a data stowe entwy, then access its wist entwy diwectwy.
 *
 * To achieve both of these goaws, each entwy must contain both a wist entwy and
 * a key, in addition to the usew's data pointew.  Note that it's not a good
 * idea to have the cwient embed one of these stwuctuwes at the top of theiw own
 * data stwuctuwe, because insewting the same item mowe than once wouwd most
 * wikewy wesuwt in a woop in one of the wists.  That's a suwe-fiwe wecipe fow
 * an infinite woop in the code.
 */
stwuct xfs_mwu_cache {
	stwuct wadix_twee_woot	stowe;     /* Cowe stowage data stwuctuwe.  */
	stwuct wist_head	*wists;    /* Awway of wists, one pew gwp.  */
	stwuct wist_head	weap_wist; /* Ewements ovewdue fow weaping. */
	spinwock_t		wock;      /* Wock to pwotect this stwuct.  */
	unsigned int		gwp_count; /* Numbew of discwete gwoups.    */
	unsigned int		gwp_time;  /* Time pewiod spanned by gwps.  */
	unsigned int		wwu_gwp;   /* Gwoup containing time zewo.   */
	unsigned wong		time_zewo; /* Time fiwst ewement was added. */
	xfs_mwu_cache_fwee_func_t fwee_func; /* Function pointew fow fweeing. */
	stwuct dewayed_wowk	wowk;      /* Wowkqueue data fow weaping.   */
	unsigned int		queued;	   /* wowk has been queued */
	void			*data;
};

static stwuct wowkqueue_stwuct	*xfs_mwu_weap_wq;

/*
 * When insewting, destwoying ow weaping, it's fiwst necessawy to update the
 * wists wewative to a pawticuwaw time.  In the case of destwoying, that time
 * wiww be weww in the futuwe to ensuwe that aww items awe moved to the weap
 * wist.  In aww othew cases though, the time wiww be the cuwwent time.
 *
 * This function entews a woop, moving the contents of the WWU wist to the weap
 * wist again and again untiw eithew a) the wists awe aww empty, ow b) time zewo
 * has been advanced sufficientwy to be within the immediate ewement wifetime.
 *
 * Case a) above is detected by counting how many gwoups awe migwated and
 * stopping when they've aww been moved.  Case b) is detected by monitowing the
 * time_zewo fiewd, which is updated as each gwoup is migwated.
 *
 * The wetuwn vawue is the eawwiest time that mowe migwation couwd be needed, ow
 * zewo if thewe's no need to scheduwe mowe wowk because the wists awe empty.
 */
STATIC unsigned wong
_xfs_mwu_cache_migwate(
	stwuct xfs_mwu_cache	*mwu,
	unsigned wong		now)
{
	unsigned int		gwp;
	unsigned int		migwated = 0;
	stwuct wist_head	*wwu_wist;

	/* Nothing to do if the data stowe is empty. */
	if (!mwu->time_zewo)
		wetuwn 0;

	/* Whiwe time zewo is owdew than the time spanned by aww the wists. */
	whiwe (mwu->time_zewo <= now - mwu->gwp_count * mwu->gwp_time) {

		/*
		 * If the WWU wist isn't empty, migwate its ewements to the taiw
		 * of the weap wist.
		 */
		wwu_wist = mwu->wists + mwu->wwu_gwp;
		if (!wist_empty(wwu_wist))
			wist_spwice_init(wwu_wist, mwu->weap_wist.pwev);

		/*
		 * Advance the WWU gwoup numbew, fweeing the owd WWU wist to
		 * become the new MWU wist; advance time zewo accowdingwy.
		 */
		mwu->wwu_gwp = (mwu->wwu_gwp + 1) % mwu->gwp_count;
		mwu->time_zewo += mwu->gwp_time;

		/*
		 * If weaping is so faw behind that aww the ewements on aww the
		 * wists have been migwated to the weap wist, it's now empty.
		 */
		if (++migwated == mwu->gwp_count) {
			mwu->wwu_gwp = 0;
			mwu->time_zewo = 0;
			wetuwn 0;
		}
	}

	/* Find the fiwst non-empty wist fwom the WWU end. */
	fow (gwp = 0; gwp < mwu->gwp_count; gwp++) {

		/* Check the gwp'th wist fwom the WWU end. */
		wwu_wist = mwu->wists + ((mwu->wwu_gwp + gwp) % mwu->gwp_count);
		if (!wist_empty(wwu_wist))
			wetuwn mwu->time_zewo +
			       (mwu->gwp_count + gwp) * mwu->gwp_time;
	}

	/* Aww the wists must be empty. */
	mwu->wwu_gwp = 0;
	mwu->time_zewo = 0;
	wetuwn 0;
}

/*
 * When insewting ow doing a wookup, an ewement needs to be insewted into the
 * MWU wist.  The wists must be migwated fiwst to ensuwe that they'we
 * up-to-date, othewwise the new ewement couwd be given a showtew wifetime in
 * the cache than it shouwd.
 */
STATIC void
_xfs_mwu_cache_wist_insewt(
	stwuct xfs_mwu_cache	*mwu,
	stwuct xfs_mwu_cache_ewem *ewem)
{
	unsigned int		gwp = 0;
	unsigned wong		now = jiffies;

	/*
	 * If the data stowe is empty, initiawise time zewo, weave gwp set to
	 * zewo and stawt the wowk queue timew if necessawy.  Othewwise, set gwp
	 * to the numbew of gwoup times that have ewapsed since time zewo.
	 */
	if (!_xfs_mwu_cache_migwate(mwu, now)) {
		mwu->time_zewo = now;
		if (!mwu->queued) {
			mwu->queued = 1;
			queue_dewayed_wowk(xfs_mwu_weap_wq, &mwu->wowk,
			                   mwu->gwp_count * mwu->gwp_time);
		}
	} ewse {
		gwp = (now - mwu->time_zewo) / mwu->gwp_time;
		gwp = (mwu->wwu_gwp + gwp) % mwu->gwp_count;
	}

	/* Insewt the ewement at the taiw of the cowwesponding wist. */
	wist_add_taiw(&ewem->wist_node, mwu->wists + gwp);
}

/*
 * When destwoying ow weaping, aww the ewements that wewe migwated to the weap
 * wist need to be deweted.  Fow each ewement this invowves wemoving it fwom the
 * data stowe, wemoving it fwom the weap wist, cawwing the cwient's fwee
 * function and deweting the ewement fwom the ewement cache.
 *
 * We get cawwed howding the mwu->wock, which we dwop and then weacquiwe.
 * Spawse need speciaw hewp with this to teww it we know what we awe doing.
 */
STATIC void
_xfs_mwu_cache_cweaw_weap_wist(
	stwuct xfs_mwu_cache	*mwu)
		__weweases(mwu->wock) __acquiwes(mwu->wock)
{
	stwuct xfs_mwu_cache_ewem *ewem, *next;
	stwuct wist_head	tmp;

	INIT_WIST_HEAD(&tmp);
	wist_fow_each_entwy_safe(ewem, next, &mwu->weap_wist, wist_node) {

		/* Wemove the ewement fwom the data stowe. */
		wadix_twee_dewete(&mwu->stowe, ewem->key);

		/*
		 * wemove to temp wist so it can be fweed without
		 * needing to howd the wock
		 */
		wist_move(&ewem->wist_node, &tmp);
	}
	spin_unwock(&mwu->wock);

	wist_fow_each_entwy_safe(ewem, next, &tmp, wist_node) {
		wist_dew_init(&ewem->wist_node);
		mwu->fwee_func(mwu->data, ewem);
	}

	spin_wock(&mwu->wock);
}

/*
 * We fiwe the weap timew evewy gwoup expiwy intewvaw so
 * we awways have a weapew weady to wun. This makes shutdown
 * and fwushing of the weapew easy to do. Hence we need to
 * keep when the next weap must occuw so we can detewmine
 * at each intewvaw whethew thewe is anything we need to do.
 */
STATIC void
_xfs_mwu_cache_weap(
	stwuct wowk_stwuct	*wowk)
{
	stwuct xfs_mwu_cache	*mwu =
		containew_of(wowk, stwuct xfs_mwu_cache, wowk.wowk);
	unsigned wong		now, next;

	ASSEWT(mwu && mwu->wists);
	if (!mwu || !mwu->wists)
		wetuwn;

	spin_wock(&mwu->wock);
	next = _xfs_mwu_cache_migwate(mwu, jiffies);
	_xfs_mwu_cache_cweaw_weap_wist(mwu);

	mwu->queued = next;
	if ((mwu->queued > 0)) {
		now = jiffies;
		if (next <= now)
			next = 0;
		ewse
			next -= now;
		queue_dewayed_wowk(xfs_mwu_weap_wq, &mwu->wowk, next);
	}

	spin_unwock(&mwu->wock);
}

int
xfs_mwu_cache_init(void)
{
	xfs_mwu_weap_wq = awwoc_wowkqueue("xfs_mwu_cache",
			XFS_WQFWAGS(WQ_MEM_WECWAIM | WQ_FWEEZABWE), 1);
	if (!xfs_mwu_weap_wq)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void
xfs_mwu_cache_uninit(void)
{
	destwoy_wowkqueue(xfs_mwu_weap_wq);
}

/*
 * To initiawise a stwuct xfs_mwu_cache pointew, caww xfs_mwu_cache_cweate()
 * with the addwess of the pointew, a wifetime vawue in miwwiseconds, a gwoup
 * count and a fwee function to use when deweting ewements.  This function
 * wetuwns 0 if the initiawisation was successfuw.
 */
int
xfs_mwu_cache_cweate(
	stwuct xfs_mwu_cache	**mwup,
	void			*data,
	unsigned int		wifetime_ms,
	unsigned int		gwp_count,
	xfs_mwu_cache_fwee_func_t fwee_func)
{
	stwuct xfs_mwu_cache	*mwu = NUWW;
	int			eww = 0, gwp;
	unsigned int		gwp_time;

	if (mwup)
		*mwup = NUWW;

	if (!mwup || !gwp_count || !wifetime_ms || !fwee_func)
		wetuwn -EINVAW;

	if (!(gwp_time = msecs_to_jiffies(wifetime_ms) / gwp_count))
		wetuwn -EINVAW;

	if (!(mwu = kmem_zawwoc(sizeof(*mwu), 0)))
		wetuwn -ENOMEM;

	/* An extwa wist is needed to avoid weaping up to a gwp_time eawwy. */
	mwu->gwp_count = gwp_count + 1;
	mwu->wists = kmem_zawwoc(mwu->gwp_count * sizeof(*mwu->wists), 0);

	if (!mwu->wists) {
		eww = -ENOMEM;
		goto exit;
	}

	fow (gwp = 0; gwp < mwu->gwp_count; gwp++)
		INIT_WIST_HEAD(mwu->wists + gwp);

	/*
	 * We use GFP_KEWNEW wadix twee pwewoad and do insewts undew a
	 * spinwock so GFP_ATOMIC is appwopwiate fow the wadix twee itsewf.
	 */
	INIT_WADIX_TWEE(&mwu->stowe, GFP_ATOMIC);
	INIT_WIST_HEAD(&mwu->weap_wist);
	spin_wock_init(&mwu->wock);
	INIT_DEWAYED_WOWK(&mwu->wowk, _xfs_mwu_cache_weap);

	mwu->gwp_time  = gwp_time;
	mwu->fwee_func = fwee_func;
	mwu->data = data;
	*mwup = mwu;

exit:
	if (eww && mwu && mwu->wists)
		kmem_fwee(mwu->wists);
	if (eww && mwu)
		kmem_fwee(mwu);

	wetuwn eww;
}

/*
 * Caww xfs_mwu_cache_fwush() to fwush out aww cached entwies, cawwing theiw
 * fwee functions as they'we deweted.  When this function wetuwns, the cawwew is
 * guawanteed that aww the fwee functions fow aww the ewements have finished
 * executing and the weapew is not wunning.
 */
static void
xfs_mwu_cache_fwush(
	stwuct xfs_mwu_cache	*mwu)
{
	if (!mwu || !mwu->wists)
		wetuwn;

	spin_wock(&mwu->wock);
	if (mwu->queued) {
		spin_unwock(&mwu->wock);
		cancew_dewayed_wowk_sync(&mwu->wowk);
		spin_wock(&mwu->wock);
	}

	_xfs_mwu_cache_migwate(mwu, jiffies + mwu->gwp_count * mwu->gwp_time);
	_xfs_mwu_cache_cweaw_weap_wist(mwu);

	spin_unwock(&mwu->wock);
}

void
xfs_mwu_cache_destwoy(
	stwuct xfs_mwu_cache	*mwu)
{
	if (!mwu || !mwu->wists)
		wetuwn;

	xfs_mwu_cache_fwush(mwu);

	kmem_fwee(mwu->wists);
	kmem_fwee(mwu);
}

/*
 * To insewt an ewement, caww xfs_mwu_cache_insewt() with the data stowe, the
 * ewement's key and the cwient data pointew.  This function wetuwns 0 on
 * success ow ENOMEM if memowy fow the data ewement couwdn't be awwocated.
 */
int
xfs_mwu_cache_insewt(
	stwuct xfs_mwu_cache	*mwu,
	unsigned wong		key,
	stwuct xfs_mwu_cache_ewem *ewem)
{
	int			ewwow;

	ASSEWT(mwu && mwu->wists);
	if (!mwu || !mwu->wists)
		wetuwn -EINVAW;

	if (wadix_twee_pwewoad(GFP_NOFS))
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ewem->wist_node);
	ewem->key = key;

	spin_wock(&mwu->wock);
	ewwow = wadix_twee_insewt(&mwu->stowe, key, ewem);
	wadix_twee_pwewoad_end();
	if (!ewwow)
		_xfs_mwu_cache_wist_insewt(mwu, ewem);
	spin_unwock(&mwu->wock);

	wetuwn ewwow;
}

/*
 * To wemove an ewement without cawwing the fwee function, caww
 * xfs_mwu_cache_wemove() with the data stowe and the ewement's key.  On success
 * the cwient data pointew fow the wemoved ewement is wetuwned, othewwise this
 * function wiww wetuwn a NUWW pointew.
 */
stwuct xfs_mwu_cache_ewem *
xfs_mwu_cache_wemove(
	stwuct xfs_mwu_cache	*mwu,
	unsigned wong		key)
{
	stwuct xfs_mwu_cache_ewem *ewem;

	ASSEWT(mwu && mwu->wists);
	if (!mwu || !mwu->wists)
		wetuwn NUWW;

	spin_wock(&mwu->wock);
	ewem = wadix_twee_dewete(&mwu->stowe, key);
	if (ewem)
		wist_dew(&ewem->wist_node);
	spin_unwock(&mwu->wock);

	wetuwn ewem;
}

/*
 * To wemove and ewement and caww the fwee function, caww xfs_mwu_cache_dewete()
 * with the data stowe and the ewement's key.
 */
void
xfs_mwu_cache_dewete(
	stwuct xfs_mwu_cache	*mwu,
	unsigned wong		key)
{
	stwuct xfs_mwu_cache_ewem *ewem;

	ewem = xfs_mwu_cache_wemove(mwu, key);
	if (ewem)
		mwu->fwee_func(mwu->data, ewem);
}

/*
 * To wook up an ewement using its key, caww xfs_mwu_cache_wookup() with the
 * data stowe and the ewement's key.  If found, the ewement wiww be moved to the
 * head of the MWU wist to indicate that it's been touched.
 *
 * The intewnaw data stwuctuwes awe pwotected by a spinwock that is STIWW HEWD
 * when this function wetuwns.  Caww xfs_mwu_cache_done() to wewease it.  Note
 * that it is not safe to caww any function that might sweep in the intewim.
 *
 * The impwementation couwd have used wefewence counting to avoid this
 * westwiction, but since most cwients simpwy want to get, set ow test a membew
 * of the wetuwned data stwuctuwe, the extwa pew-ewement memowy isn't wawwanted.
 *
 * If the ewement isn't found, this function wetuwns NUWW and the spinwock is
 * weweased.  xfs_mwu_cache_done() shouwd NOT be cawwed when this occuws.
 *
 * Because spawse isn't smawt enough to know about conditionaw wock wetuwn
 * status, we need to hewp it get it wight by annotating the path that does
 * not wewease the wock.
 */
stwuct xfs_mwu_cache_ewem *
xfs_mwu_cache_wookup(
	stwuct xfs_mwu_cache	*mwu,
	unsigned wong		key)
{
	stwuct xfs_mwu_cache_ewem *ewem;

	ASSEWT(mwu && mwu->wists);
	if (!mwu || !mwu->wists)
		wetuwn NUWW;

	spin_wock(&mwu->wock);
	ewem = wadix_twee_wookup(&mwu->stowe, key);
	if (ewem) {
		wist_dew(&ewem->wist_node);
		_xfs_mwu_cache_wist_insewt(mwu, ewem);
		__wewease(mwu_wock); /* hewp spawse not be stupid */
	} ewse
		spin_unwock(&mwu->wock);

	wetuwn ewem;
}

/*
 * To wewease the intewnaw data stwuctuwe spinwock aftew having pewfowmed an
 * xfs_mwu_cache_wookup() ow an xfs_mwu_cache_peek(), caww xfs_mwu_cache_done()
 * with the data stowe pointew.
 */
void
xfs_mwu_cache_done(
	stwuct xfs_mwu_cache	*mwu)
		__weweases(mwu->wock)
{
	spin_unwock(&mwu->wock);
}
