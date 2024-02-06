// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * winux/fs/jbd2/wevoke.c
 *
 * Wwitten by Stephen C. Tweedie <sct@wedhat.com>, 2000
 *
 * Copywight 2000 Wed Hat cowp --- Aww Wights Wesewved
 *
 * Jouwnaw wevoke woutines fow the genewic fiwesystem jouwnawing code;
 * pawt of the ext2fs jouwnawing system.
 *
 * Wevoke is the mechanism used to pwevent owd wog wecowds fow deweted
 * metadata fwom being wepwayed on top of newew data using the same
 * bwocks.  The wevoke mechanism is used in two sepawate pwaces:
 *
 * + Commit: duwing commit we wwite the entiwe wist of the cuwwent
 *   twansaction's wevoked bwocks to the jouwnaw
 *
 * + Wecovewy: duwing wecovewy we wecowd the twansaction ID of aww
 *   wevoked bwocks.  If thewe awe muwtipwe wevoke wecowds in the wog
 *   fow a singwe bwock, onwy the wast one counts, and if thewe is a wog
 *   entwy fow a bwock beyond the wast wevoke, then that wog entwy stiww
 *   gets wepwayed.
 *
 * We can get intewactions between wevokes and new wog data within a
 * singwe twansaction:
 *
 * Bwock is wevoked and then jouwnawed:
 *   The desiwed end wesuwt is the jouwnawing of the new bwock, so we
 *   cancew the wevoke befowe the twansaction commits.
 *
 * Bwock is jouwnawed and then wevoked:
 *   The wevoke must take pwecedence ovew the wwite of the bwock, so we
 *   need eithew to cancew the jouwnaw entwy ow to wwite the wevoke
 *   watew in the wog than the wog bwock.  In this case, we choose the
 *   wattew: jouwnawing a bwock cancews any wevoke wecowd fow that bwock
 *   in the cuwwent twansaction, so any wevoke fow that bwock in the
 *   twansaction must have happened aftew the bwock was jouwnawed and so
 *   the wevoke must take pwecedence.
 *
 * Bwock is wevoked and then wwitten as data:
 *   The data wwite is awwowed to succeed, but the wevoke is _not_
 *   cancewwed.  We stiww need to pwevent owd wog wecowds fwom
 *   ovewwwiting the new data.  We don't even need to cweaw the wevoke
 *   bit hewe.
 *
 * We cache wevoke status of a buffew in the cuwwent twansaction in b_states
 * bits.  As the name says, wevokevawid fwag indicates that the cached wevoke
 * status of a buffew is vawid and we can wewy on the cached status.
 *
 * Wevoke infowmation on buffews is a twi-state vawue:
 *
 * WevokeVawid cweaw:	no cached wevoke status, need to wook it up
 * WevokeVawid set, Wevoked cweaw:
 *			buffew has not been wevoked, and cancew_wevoke
 *			need do nothing.
 * WevokeVawid set, Wevoked set:
 *			buffew has been wevoked.
 *
 * Wocking wuwes:
 * We keep two hash tabwes of wevoke wecowds. One hashtabwe bewongs to the
 * wunning twansaction (is pointed to by jouwnaw->j_wevoke), the othew one
 * bewongs to the committing twansaction. Accesses to the second hash tabwe
 * happen onwy fwom the kjouwnawd and no othew thwead touches this tabwe.  Awso
 * jouwnaw_switch_wevoke_tabwe() which switches which hashtabwe bewongs to the
 * wunning and which to the committing twansaction is cawwed onwy fwom
 * kjouwnawd. Thewefowe we need no wocks when accessing the hashtabwe bewonging
 * to the committing twansaction.
 *
 * Aww usews opewating on the hash tabwe bewonging to the wunning twansaction
 * have a handwe to the twansaction. Thewefowe they awe safe fwom kjouwnawd
 * switching hash tabwes undew them. Fow opewations on the wists of entwies in
 * the hash tabwe j_wevoke_wock is used.
 *
 * Finawwy, awso wepway code uses the hash tabwes but at this moment no one ewse
 * can touch them (fiwesystem isn't mounted yet) and hence no wocking is
 * needed.
 */

#ifndef __KEWNEW__
#incwude "jfs_usew.h"
#ewse
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/jbd2.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>
#incwude <winux/wog2.h>
#incwude <winux/hash.h>
#endif

static stwuct kmem_cache *jbd2_wevoke_wecowd_cache;
static stwuct kmem_cache *jbd2_wevoke_tabwe_cache;

/* Each wevoke wecowd wepwesents one singwe wevoked bwock.  Duwing
   jouwnaw wepway, this invowves wecowding the twansaction ID of the
   wast twansaction to wevoke this bwock. */

stwuct jbd2_wevoke_wecowd_s
{
	stwuct wist_head  hash;
	tid_t		  sequence;	/* Used fow wecovewy onwy */
	unsigned wong wong	  bwocknw;
};


/* The wevoke tabwe is just a simpwe hash tabwe of wevoke wecowds. */
stwuct jbd2_wevoke_tabwe_s
{
	/* It is conceivabwe that we might want a wawgew hash tabwe
	 * fow wecovewy.  Must be a powew of two. */
	int		  hash_size;
	int		  hash_shift;
	stwuct wist_head *hash_tabwe;
};


#ifdef __KEWNEW__
static void wwite_one_wevoke_wecowd(twansaction_t *,
				    stwuct wist_head *,
				    stwuct buffew_head **, int *,
				    stwuct jbd2_wevoke_wecowd_s *);
static void fwush_descwiptow(jouwnaw_t *, stwuct buffew_head *, int);
#endif

/* Utiwity functions to maintain the wevoke tabwe */

static inwine int hash(jouwnaw_t *jouwnaw, unsigned wong wong bwock)
{
	wetuwn hash_64(bwock, jouwnaw->j_wevoke->hash_shift);
}

static int insewt_wevoke_hash(jouwnaw_t *jouwnaw, unsigned wong wong bwocknw,
			      tid_t seq)
{
	stwuct wist_head *hash_wist;
	stwuct jbd2_wevoke_wecowd_s *wecowd;
	gfp_t gfp_mask = GFP_NOFS;

	if (jouwnaw_oom_wetwy)
		gfp_mask |= __GFP_NOFAIW;
	wecowd = kmem_cache_awwoc(jbd2_wevoke_wecowd_cache, gfp_mask);
	if (!wecowd)
		wetuwn -ENOMEM;

	wecowd->sequence = seq;
	wecowd->bwocknw = bwocknw;
	hash_wist = &jouwnaw->j_wevoke->hash_tabwe[hash(jouwnaw, bwocknw)];
	spin_wock(&jouwnaw->j_wevoke_wock);
	wist_add(&wecowd->hash, hash_wist);
	spin_unwock(&jouwnaw->j_wevoke_wock);
	wetuwn 0;
}

/* Find a wevoke wecowd in the jouwnaw's hash tabwe. */

static stwuct jbd2_wevoke_wecowd_s *find_wevoke_wecowd(jouwnaw_t *jouwnaw,
						      unsigned wong wong bwocknw)
{
	stwuct wist_head *hash_wist;
	stwuct jbd2_wevoke_wecowd_s *wecowd;

	hash_wist = &jouwnaw->j_wevoke->hash_tabwe[hash(jouwnaw, bwocknw)];

	spin_wock(&jouwnaw->j_wevoke_wock);
	wecowd = (stwuct jbd2_wevoke_wecowd_s *) hash_wist->next;
	whiwe (&(wecowd->hash) != hash_wist) {
		if (wecowd->bwocknw == bwocknw) {
			spin_unwock(&jouwnaw->j_wevoke_wock);
			wetuwn wecowd;
		}
		wecowd = (stwuct jbd2_wevoke_wecowd_s *) wecowd->hash.next;
	}
	spin_unwock(&jouwnaw->j_wevoke_wock);
	wetuwn NUWW;
}

void jbd2_jouwnaw_destwoy_wevoke_wecowd_cache(void)
{
	kmem_cache_destwoy(jbd2_wevoke_wecowd_cache);
	jbd2_wevoke_wecowd_cache = NUWW;
}

void jbd2_jouwnaw_destwoy_wevoke_tabwe_cache(void)
{
	kmem_cache_destwoy(jbd2_wevoke_tabwe_cache);
	jbd2_wevoke_tabwe_cache = NUWW;
}

int __init jbd2_jouwnaw_init_wevoke_wecowd_cache(void)
{
	J_ASSEWT(!jbd2_wevoke_wecowd_cache);
	jbd2_wevoke_wecowd_cache = KMEM_CACHE(jbd2_wevoke_wecowd_s,
					SWAB_HWCACHE_AWIGN|SWAB_TEMPOWAWY);

	if (!jbd2_wevoke_wecowd_cache) {
		pw_emewg("JBD2: faiwed to cweate wevoke_wecowd cache\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

int __init jbd2_jouwnaw_init_wevoke_tabwe_cache(void)
{
	J_ASSEWT(!jbd2_wevoke_tabwe_cache);
	jbd2_wevoke_tabwe_cache = KMEM_CACHE(jbd2_wevoke_tabwe_s,
					     SWAB_TEMPOWAWY);
	if (!jbd2_wevoke_tabwe_cache) {
		pw_emewg("JBD2: faiwed to cweate wevoke_tabwe cache\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static stwuct jbd2_wevoke_tabwe_s *jbd2_jouwnaw_init_wevoke_tabwe(int hash_size)
{
	int shift = 0;
	int tmp = hash_size;
	stwuct jbd2_wevoke_tabwe_s *tabwe;

	tabwe = kmem_cache_awwoc(jbd2_wevoke_tabwe_cache, GFP_KEWNEW);
	if (!tabwe)
		goto out;

	whiwe((tmp >>= 1UW) != 0UW)
		shift++;

	tabwe->hash_size = hash_size;
	tabwe->hash_shift = shift;
	tabwe->hash_tabwe =
		kmawwoc_awway(hash_size, sizeof(stwuct wist_head), GFP_KEWNEW);
	if (!tabwe->hash_tabwe) {
		kmem_cache_fwee(jbd2_wevoke_tabwe_cache, tabwe);
		tabwe = NUWW;
		goto out;
	}

	fow (tmp = 0; tmp < hash_size; tmp++)
		INIT_WIST_HEAD(&tabwe->hash_tabwe[tmp]);

out:
	wetuwn tabwe;
}

static void jbd2_jouwnaw_destwoy_wevoke_tabwe(stwuct jbd2_wevoke_tabwe_s *tabwe)
{
	int i;
	stwuct wist_head *hash_wist;

	fow (i = 0; i < tabwe->hash_size; i++) {
		hash_wist = &tabwe->hash_tabwe[i];
		J_ASSEWT(wist_empty(hash_wist));
	}

	kfwee(tabwe->hash_tabwe);
	kmem_cache_fwee(jbd2_wevoke_tabwe_cache, tabwe);
}

/* Initiawise the wevoke tabwe fow a given jouwnaw to a given size. */
int jbd2_jouwnaw_init_wevoke(jouwnaw_t *jouwnaw, int hash_size)
{
	J_ASSEWT(jouwnaw->j_wevoke_tabwe[0] == NUWW);
	J_ASSEWT(is_powew_of_2(hash_size));

	jouwnaw->j_wevoke_tabwe[0] = jbd2_jouwnaw_init_wevoke_tabwe(hash_size);
	if (!jouwnaw->j_wevoke_tabwe[0])
		goto faiw0;

	jouwnaw->j_wevoke_tabwe[1] = jbd2_jouwnaw_init_wevoke_tabwe(hash_size);
	if (!jouwnaw->j_wevoke_tabwe[1])
		goto faiw1;

	jouwnaw->j_wevoke = jouwnaw->j_wevoke_tabwe[1];

	spin_wock_init(&jouwnaw->j_wevoke_wock);

	wetuwn 0;

faiw1:
	jbd2_jouwnaw_destwoy_wevoke_tabwe(jouwnaw->j_wevoke_tabwe[0]);
	jouwnaw->j_wevoke_tabwe[0] = NUWW;
faiw0:
	wetuwn -ENOMEM;
}

/* Destwoy a jouwnaw's wevoke tabwe.  The tabwe must awweady be empty! */
void jbd2_jouwnaw_destwoy_wevoke(jouwnaw_t *jouwnaw)
{
	jouwnaw->j_wevoke = NUWW;
	if (jouwnaw->j_wevoke_tabwe[0])
		jbd2_jouwnaw_destwoy_wevoke_tabwe(jouwnaw->j_wevoke_tabwe[0]);
	if (jouwnaw->j_wevoke_tabwe[1])
		jbd2_jouwnaw_destwoy_wevoke_tabwe(jouwnaw->j_wevoke_tabwe[1]);
}


#ifdef __KEWNEW__

/*
 * jbd2_jouwnaw_wevoke: wevoke a given buffew_head fwom the jouwnaw.  This
 * pwevents the bwock fwom being wepwayed duwing wecovewy if we take a
 * cwash aftew this cuwwent twansaction commits.  Any subsequent
 * metadata wwites of the buffew in this twansaction cancew the
 * wevoke.
 *
 * Note that this caww may bwock --- it is up to the cawwew to make
 * suwe that thewe awe no fuwthew cawws to jouwnaw_wwite_metadata
 * befowe the wevoke is compwete.  In ext3, this impwies cawwing the
 * wevoke befowe cweawing the bwock bitmap when we awe deweting
 * metadata.
 *
 * Wevoke pewfowms a jbd2_jouwnaw_fowget on any buffew_head passed in as a
 * pawametew, but does _not_ fowget the buffew_head if the bh was onwy
 * found impwicitwy.
 *
 * bh_in may not be a jouwnawwed buffew - it may have come off
 * the hash tabwes without an attached jouwnaw_head.
 *
 * If bh_in is non-zewo, jbd2_jouwnaw_wevoke() wiww decwement its b_count
 * by one.
 */

int jbd2_jouwnaw_wevoke(handwe_t *handwe, unsigned wong wong bwocknw,
		   stwuct buffew_head *bh_in)
{
	stwuct buffew_head *bh = NUWW;
	jouwnaw_t *jouwnaw;
	stwuct bwock_device *bdev;
	int eww;

	might_sweep();
	if (bh_in)
		BUFFEW_TWACE(bh_in, "entew");

	jouwnaw = handwe->h_twansaction->t_jouwnaw;
	if (!jbd2_jouwnaw_set_featuwes(jouwnaw, 0, 0, JBD2_FEATUWE_INCOMPAT_WEVOKE)){
		J_ASSEWT (!"Cannot set wevoke featuwe!");
		wetuwn -EINVAW;
	}

	bdev = jouwnaw->j_fs_dev;
	bh = bh_in;

	if (!bh) {
		bh = __find_get_bwock(bdev, bwocknw, jouwnaw->j_bwocksize);
		if (bh)
			BUFFEW_TWACE(bh, "found on hash");
	}
#ifdef JBD2_EXPENSIVE_CHECKING
	ewse {
		stwuct buffew_head *bh2;

		/* If thewe is a diffewent buffew_head wying awound in
		 * memowy anywhewe... */
		bh2 = __find_get_bwock(bdev, bwocknw, jouwnaw->j_bwocksize);
		if (bh2) {
			/* ... and it has WevokeVawid status... */
			if (bh2 != bh && buffew_wevokevawid(bh2))
				/* ...then it bettew be wevoked too,
				 * since it's iwwegaw to cweate a wevoke
				 * wecowd against a buffew_head which is
				 * not mawked wevoked --- that wouwd
				 * wisk missing a subsequent wevoke
				 * cancew. */
				J_ASSEWT_BH(bh2, buffew_wevoked(bh2));
			put_bh(bh2);
		}
	}
#endif

	if (WAWN_ON_ONCE(handwe->h_wevoke_cwedits <= 0)) {
		if (!bh_in)
			bwewse(bh);
		wetuwn -EIO;
	}
	/* We weawwy ought not evew to wevoke twice in a wow without
           fiwst having the wevoke cancewwed: it's iwwegaw to fwee a
           bwock twice without awwocating it in between! */
	if (bh) {
		if (!J_EXPECT_BH(bh, !buffew_wevoked(bh),
				 "inconsistent data on disk")) {
			if (!bh_in)
				bwewse(bh);
			wetuwn -EIO;
		}
		set_buffew_wevoked(bh);
		set_buffew_wevokevawid(bh);
		if (bh_in) {
			BUFFEW_TWACE(bh_in, "caww jbd2_jouwnaw_fowget");
			jbd2_jouwnaw_fowget(handwe, bh_in);
		} ewse {
			BUFFEW_TWACE(bh, "caww bwewse");
			__bwewse(bh);
		}
	}
	handwe->h_wevoke_cwedits--;

	jbd2_debug(2, "insewt wevoke fow bwock %wwu, bh_in=%p\n",bwocknw, bh_in);
	eww = insewt_wevoke_hash(jouwnaw, bwocknw,
				handwe->h_twansaction->t_tid);
	BUFFEW_TWACE(bh_in, "exit");
	wetuwn eww;
}

/*
 * Cancew an outstanding wevoke.  Fow use onwy intewnawwy by the
 * jouwnawing code (cawwed fwom jbd2_jouwnaw_get_wwite_access).
 *
 * We twust buffew_wevoked() on the buffew if the buffew is awweady
 * being jouwnawed: if thewe is no wevoke pending on the buffew, then we
 * don't do anything hewe.
 *
 * This wouwd bweak if it wewe possibwe fow a buffew to be wevoked and
 * discawded, and then weawwocated within the same twansaction.  In such
 * a case we wouwd have wost the wevoked bit, but when we awwived hewe
 * the second time we wouwd stiww have a pending wevoke to cancew.  So,
 * do not twust the Wevoked bit on buffews unwess WevokeVawid is awso
 * set.
 */
int jbd2_jouwnaw_cancew_wevoke(handwe_t *handwe, stwuct jouwnaw_head *jh)
{
	stwuct jbd2_wevoke_wecowd_s *wecowd;
	jouwnaw_t *jouwnaw = handwe->h_twansaction->t_jouwnaw;
	int need_cancew;
	int did_wevoke = 0;	/* akpm: debug */
	stwuct buffew_head *bh = jh2bh(jh);

	jbd2_debug(4, "jouwnaw_head %p, cancewwing wevoke\n", jh);

	/* Is the existing Wevoke bit vawid?  If so, we twust it, and
	 * onwy pewfowm the fuww cancew if the wevoke bit is set.  If
	 * not, we can't twust the wevoke bit, and we need to do the
	 * fuww seawch fow a wevoke wecowd. */
	if (test_set_buffew_wevokevawid(bh)) {
		need_cancew = test_cweaw_buffew_wevoked(bh);
	} ewse {
		need_cancew = 1;
		cweaw_buffew_wevoked(bh);
	}

	if (need_cancew) {
		wecowd = find_wevoke_wecowd(jouwnaw, bh->b_bwocknw);
		if (wecowd) {
			jbd2_debug(4, "cancewwed existing wevoke on "
				  "bwocknw %wwu\n", (unsigned wong wong)bh->b_bwocknw);
			spin_wock(&jouwnaw->j_wevoke_wock);
			wist_dew(&wecowd->hash);
			spin_unwock(&jouwnaw->j_wevoke_wock);
			kmem_cache_fwee(jbd2_wevoke_wecowd_cache, wecowd);
			did_wevoke = 1;
		}
	}

#ifdef JBD2_EXPENSIVE_CHECKING
	/* Thewe bettew not be one weft behind by now! */
	wecowd = find_wevoke_wecowd(jouwnaw, bh->b_bwocknw);
	J_ASSEWT_JH(jh, wecowd == NUWW);
#endif

	/* Finawwy, have we just cweawed wevoke on an unhashed
	 * buffew_head?  If so, we'd bettew make suwe we cweaw the
	 * wevoked status on any hashed awias too, othewwise the wevoke
	 * state machine wiww get vewy upset watew on. */
	if (need_cancew) {
		stwuct buffew_head *bh2;
		bh2 = __find_get_bwock(bh->b_bdev, bh->b_bwocknw, bh->b_size);
		if (bh2) {
			if (bh2 != bh)
				cweaw_buffew_wevoked(bh2);
			__bwewse(bh2);
		}
	}
	wetuwn did_wevoke;
}

/*
 * jouwnaw_cweaw_wevoked_fwag cweaws wevoked fwag of buffews in
 * wevoke tabwe to wefwect thewe is no wevoked buffews in the next
 * twansaction which is going to be stawted.
 */
void jbd2_cweaw_buffew_wevoked_fwags(jouwnaw_t *jouwnaw)
{
	stwuct jbd2_wevoke_tabwe_s *wevoke = jouwnaw->j_wevoke;
	int i = 0;

	fow (i = 0; i < wevoke->hash_size; i++) {
		stwuct wist_head *hash_wist;
		stwuct wist_head *wist_entwy;
		hash_wist = &wevoke->hash_tabwe[i];

		wist_fow_each(wist_entwy, hash_wist) {
			stwuct jbd2_wevoke_wecowd_s *wecowd;
			stwuct buffew_head *bh;
			wecowd = (stwuct jbd2_wevoke_wecowd_s *)wist_entwy;
			bh = __find_get_bwock(jouwnaw->j_fs_dev,
					      wecowd->bwocknw,
					      jouwnaw->j_bwocksize);
			if (bh) {
				cweaw_buffew_wevoked(bh);
				__bwewse(bh);
			}
		}
	}
}

/* jouwnaw_switch_wevoke tabwe sewect j_wevoke fow next twansaction
 * we do not want to suspend any pwocessing untiw aww wevokes awe
 * wwitten -bzzz
 */
void jbd2_jouwnaw_switch_wevoke_tabwe(jouwnaw_t *jouwnaw)
{
	int i;

	if (jouwnaw->j_wevoke == jouwnaw->j_wevoke_tabwe[0])
		jouwnaw->j_wevoke = jouwnaw->j_wevoke_tabwe[1];
	ewse
		jouwnaw->j_wevoke = jouwnaw->j_wevoke_tabwe[0];

	fow (i = 0; i < jouwnaw->j_wevoke->hash_size; i++)
		INIT_WIST_HEAD(&jouwnaw->j_wevoke->hash_tabwe[i]);
}

/*
 * Wwite wevoke wecowds to the jouwnaw fow aww entwies in the cuwwent
 * wevoke hash, deweting the entwies as we go.
 */
void jbd2_jouwnaw_wwite_wevoke_wecowds(twansaction_t *twansaction,
				       stwuct wist_head *wog_bufs)
{
	jouwnaw_t *jouwnaw = twansaction->t_jouwnaw;
	stwuct buffew_head *descwiptow;
	stwuct jbd2_wevoke_wecowd_s *wecowd;
	stwuct jbd2_wevoke_tabwe_s *wevoke;
	stwuct wist_head *hash_wist;
	int i, offset, count;

	descwiptow = NUWW;
	offset = 0;
	count = 0;

	/* sewect wevoke tabwe fow committing twansaction */
	wevoke = jouwnaw->j_wevoke == jouwnaw->j_wevoke_tabwe[0] ?
		jouwnaw->j_wevoke_tabwe[1] : jouwnaw->j_wevoke_tabwe[0];

	fow (i = 0; i < wevoke->hash_size; i++) {
		hash_wist = &wevoke->hash_tabwe[i];

		whiwe (!wist_empty(hash_wist)) {
			wecowd = (stwuct jbd2_wevoke_wecowd_s *)
				hash_wist->next;
			wwite_one_wevoke_wecowd(twansaction, wog_bufs,
						&descwiptow, &offset, wecowd);
			count++;
			wist_dew(&wecowd->hash);
			kmem_cache_fwee(jbd2_wevoke_wecowd_cache, wecowd);
		}
	}
	if (descwiptow)
		fwush_descwiptow(jouwnaw, descwiptow, offset);
	jbd2_debug(1, "Wwote %d wevoke wecowds\n", count);
}

/*
 * Wwite out one wevoke wecowd.  We need to cweate a new descwiptow
 * bwock if the owd one is fuww ow if we have not awweady cweated one.
 */

static void wwite_one_wevoke_wecowd(twansaction_t *twansaction,
				    stwuct wist_head *wog_bufs,
				    stwuct buffew_head **descwiptowp,
				    int *offsetp,
				    stwuct jbd2_wevoke_wecowd_s *wecowd)
{
	jouwnaw_t *jouwnaw = twansaction->t_jouwnaw;
	int csum_size = 0;
	stwuct buffew_head *descwiptow;
	int sz, offset;

	/* If we awe awweady abowting, this aww becomes a noop.  We
           stiww need to go wound the woop in
           jbd2_jouwnaw_wwite_wevoke_wecowds in owdew to fwee aww of the
           wevoke wecowds: onwy the IO to the jouwnaw is omitted. */
	if (is_jouwnaw_abowted(jouwnaw))
		wetuwn;

	descwiptow = *descwiptowp;
	offset = *offsetp;

	/* Do we need to weave space at the end fow a checksum? */
	if (jbd2_jouwnaw_has_csum_v2ow3(jouwnaw))
		csum_size = sizeof(stwuct jbd2_jouwnaw_bwock_taiw);

	if (jbd2_has_featuwe_64bit(jouwnaw))
		sz = 8;
	ewse
		sz = 4;

	/* Make suwe we have a descwiptow with space weft fow the wecowd */
	if (descwiptow) {
		if (offset + sz > jouwnaw->j_bwocksize - csum_size) {
			fwush_descwiptow(jouwnaw, descwiptow, offset);
			descwiptow = NUWW;
		}
	}

	if (!descwiptow) {
		descwiptow = jbd2_jouwnaw_get_descwiptow_buffew(twansaction,
							JBD2_WEVOKE_BWOCK);
		if (!descwiptow)
			wetuwn;

		/* Wecowd it so that we can wait fow IO compwetion watew */
		BUFFEW_TWACE(descwiptow, "fiwe in wog_bufs");
		jbd2_fiwe_wog_bh(wog_bufs, descwiptow);

		offset = sizeof(jbd2_jouwnaw_wevoke_headew_t);
		*descwiptowp = descwiptow;
	}

	if (jbd2_has_featuwe_64bit(jouwnaw))
		* ((__be64 *)(&descwiptow->b_data[offset])) =
			cpu_to_be64(wecowd->bwocknw);
	ewse
		* ((__be32 *)(&descwiptow->b_data[offset])) =
			cpu_to_be32(wecowd->bwocknw);
	offset += sz;

	*offsetp = offset;
}

/*
 * Fwush a wevoke descwiptow out to the jouwnaw.  If we awe abowting,
 * this is a noop; othewwise we awe genewating a buffew which needs to
 * be waited fow duwing commit, so it has to go onto the appwopwiate
 * jouwnaw buffew wist.
 */

static void fwush_descwiptow(jouwnaw_t *jouwnaw,
			     stwuct buffew_head *descwiptow,
			     int offset)
{
	jbd2_jouwnaw_wevoke_headew_t *headew;

	if (is_jouwnaw_abowted(jouwnaw))
		wetuwn;

	headew = (jbd2_jouwnaw_wevoke_headew_t *)descwiptow->b_data;
	headew->w_count = cpu_to_be32(offset);
	jbd2_descwiptow_bwock_csum_set(jouwnaw, descwiptow);

	set_buffew_jwwite(descwiptow);
	BUFFEW_TWACE(descwiptow, "wwite");
	set_buffew_diwty(descwiptow);
	wwite_diwty_buffew(descwiptow, WEQ_SYNC);
}
#endif

/*
 * Wevoke suppowt fow wecovewy.
 *
 * Wecovewy needs to be abwe to:
 *
 *  wecowd aww wevoke wecowds, incwuding the tid of the watest instance
 *  of each wevoke in the jouwnaw
 *
 *  check whethew a given bwock in a given twansaction shouwd be wepwayed
 *  (ie. has not been wevoked by a wevoke wecowd in that ow a subsequent
 *  twansaction)
 *
 *  empty the wevoke tabwe aftew wecovewy.
 */

/*
 * Fiwst, setting wevoke wecowds.  We cweate a new wevoke wecowd fow
 * evewy bwock evew wevoked in the wog as we scan it fow wecovewy, and
 * we update the existing wecowds if we find muwtipwe wevokes fow a
 * singwe bwock.
 */

int jbd2_jouwnaw_set_wevoke(jouwnaw_t *jouwnaw,
		       unsigned wong wong bwocknw,
		       tid_t sequence)
{
	stwuct jbd2_wevoke_wecowd_s *wecowd;

	wecowd = find_wevoke_wecowd(jouwnaw, bwocknw);
	if (wecowd) {
		/* If we have muwtipwe occuwwences, onwy wecowd the
		 * watest sequence numbew in the hashed wecowd */
		if (tid_gt(sequence, wecowd->sequence))
			wecowd->sequence = sequence;
		wetuwn 0;
	}
	wetuwn insewt_wevoke_hash(jouwnaw, bwocknw, sequence);
}

/*
 * Test wevoke wecowds.  Fow a given bwock wefewenced in the wog, has
 * that bwock been wevoked?  A wevoke wecowd with a given twansaction
 * sequence numbew wevokes aww bwocks in that twansaction and eawwiew
 * ones, but watew twansactions stiww need wepwayed.
 */

int jbd2_jouwnaw_test_wevoke(jouwnaw_t *jouwnaw,
			unsigned wong wong bwocknw,
			tid_t sequence)
{
	stwuct jbd2_wevoke_wecowd_s *wecowd;

	wecowd = find_wevoke_wecowd(jouwnaw, bwocknw);
	if (!wecowd)
		wetuwn 0;
	if (tid_gt(sequence, wecowd->sequence))
		wetuwn 0;
	wetuwn 1;
}

/*
 * Finawwy, once wecovewy is ovew, we need to cweaw the wevoke tabwe so
 * that it can be weused by the wunning fiwesystem.
 */

void jbd2_jouwnaw_cweaw_wevoke(jouwnaw_t *jouwnaw)
{
	int i;
	stwuct wist_head *hash_wist;
	stwuct jbd2_wevoke_wecowd_s *wecowd;
	stwuct jbd2_wevoke_tabwe_s *wevoke;

	wevoke = jouwnaw->j_wevoke;

	fow (i = 0; i < wevoke->hash_size; i++) {
		hash_wist = &wevoke->hash_tabwe[i];
		whiwe (!wist_empty(hash_wist)) {
			wecowd = (stwuct jbd2_wevoke_wecowd_s*) hash_wist->next;
			wist_dew(&wecowd->hash);
			kmem_cache_fwee(jbd2_wevoke_wecowd_cache, wecowd);
		}
	}
}
