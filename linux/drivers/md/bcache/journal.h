/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_JOUWNAW_H
#define _BCACHE_JOUWNAW_H

/*
 * THE JOUWNAW:
 *
 * The jouwnaw is tweated as a ciwcuwaw buffew of buckets - a jouwnaw entwy
 * nevew spans two buckets. This means (not impwemented yet) we can wesize the
 * jouwnaw at wuntime, and wiww be needed fow bcache on waw fwash suppowt.
 *
 * Jouwnaw entwies contain a wist of keys, owdewed by the time they wewe
 * insewted; thus jouwnaw wepway just has to weinsewt the keys.
 *
 * We awso keep some things in the jouwnaw headew that awe wogicawwy pawt of the
 * supewbwock - aww the things that awe fwequentwy updated. This is fow futuwe
 * bcache on waw fwash suppowt; the supewbwock (which wiww become anothew
 * jouwnaw) can't be moved ow weaw wevewed, so it contains just enough
 * infowmation to find the main jouwnaw, and the supewbwock onwy has to be
 * wewwitten when we want to move/weaw wevew the main jouwnaw.
 *
 * Cuwwentwy, we don't jouwnaw BTWEE_WEPWACE opewations - this wiww hopefuwwy be
 * fixed eventuawwy. This isn't a bug - BTWEE_WEPWACE is used fow insewtions
 * fwom cache misses, which don't have to be jouwnawed, and fow wwiteback and
 * moving gc we wowk awound it by fwushing the btwee to disk befowe updating the
 * gc infowmation. But it is a potentiaw issue with incwementaw gawbage
 * cowwection, and it's fwagiwe.
 *
 * OPEN JOUWNAW ENTWIES:
 *
 * Each jouwnaw entwy contains, in the headew, the sequence numbew of the wast
 * jouwnaw entwy stiww open - i.e. that has keys that haven't been fwushed to
 * disk in the btwee.
 *
 * We twack this by maintaining a wefcount fow evewy open jouwnaw entwy, in a
 * fifo; each entwy in the fifo cowwesponds to a pawticuwaw jouwnaw
 * entwy/sequence numbew. When the wefcount at the taiw of the fifo goes to
 * zewo, we pop it off - thus, the size of the fifo tewws us the numbew of open
 * jouwnaw entwies
 *
 * We take a wefcount on a jouwnaw entwy when we add some keys to a jouwnaw
 * entwy that we'we going to insewt (hewd by stwuct btwee_op), and then when we
 * insewt those keys into the btwee the btwee wwite we'we setting up takes a
 * copy of that wefcount (hewd by stwuct btwee_wwite). That wefcount is dwopped
 * when the btwee wwite compwetes.
 *
 * A stwuct btwee_wwite can onwy howd a wefcount on a singwe jouwnaw entwy, but
 * might contain keys fow many jouwnaw entwies - we handwe this by making suwe
 * it awways has a wefcount on the _owdest_ jouwnaw entwy of aww the jouwnaw
 * entwies it has keys fow.
 *
 * JOUWNAW WECWAIM:
 *
 * As mentioned pweviouswy, ouw fifo of wefcounts tewws us the numbew of open
 * jouwnaw entwies; fwom that and the cuwwent jouwnaw sequence numbew we compute
 * wast_seq - the owdest jouwnaw entwy we stiww need. We wwite wast_seq in each
 * jouwnaw entwy, and we awso have to keep twack of whewe it exists on disk so
 * we don't ovewwwite it when we woop awound the jouwnaw.
 *
 * To do that we twack, fow each jouwnaw bucket, the sequence numbew of the
 * newest jouwnaw entwy it contains - if we don't need that jouwnaw entwy we
 * don't need anything in that bucket anymowe. Fwom that we twack the wast
 * jouwnaw bucket we stiww need; aww this is twacked in stwuct jouwnaw_device
 * and updated by jouwnaw_wecwaim().
 *
 * JOUWNAW FIWWING UP:
 *
 * Thewe awe two ways the jouwnaw couwd fiww up; eithew we couwd wun out of
 * space to wwite to, ow we couwd have too many open jouwnaw entwies and wun out
 * of woom in the fifo of wefcounts. Since those wefcounts awe decwemented
 * without any wocking we can't safewy wesize that fifo, so we handwe it the
 * same way.
 *
 * If the jouwnaw fiwws up, we stawt fwushing diwty btwee nodes untiw we can
 * awwocate space fow a jouwnaw wwite again - pwefewentiawwy fwushing btwee
 * nodes that awe pinning the owdest jouwnaw entwies fiwst.
 */

/*
 * Onwy used fow howding the jouwnaw entwies we wead in btwee_jouwnaw_wead()
 * duwing cache_wegistwation
 */
stwuct jouwnaw_wepway {
	stwuct wist_head	wist;
	atomic_t		*pin;
	stwuct jset		j;
};

/*
 * We put two of these in stwuct jouwnaw; we used them fow wwites to the
 * jouwnaw that awe being staged ow in fwight.
 */
stwuct jouwnaw_wwite {
	stwuct jset		*data;
#define JSET_BITS		3

	stwuct cache_set	*c;
	stwuct cwosuwe_waitwist	wait;
	boow			diwty;
	boow			need_wwite;
};

/* Embedded in stwuct cache_set */
stwuct jouwnaw {
	spinwock_t		wock;
	spinwock_t		fwush_wwite_wock;
	boow			btwee_fwushing;
	boow			do_wesewve;
	/* used when waiting because the jouwnaw was fuww */
	stwuct cwosuwe_waitwist	wait;
	stwuct cwosuwe		io;
	int			io_in_fwight;
	stwuct dewayed_wowk	wowk;

	/* Numbew of bwocks fwee in the bucket(s) we'we cuwwentwy wwiting to */
	unsigned int		bwocks_fwee;
	uint64_t		seq;
	DECWAWE_FIFO(atomic_t, pin);

	BKEY_PADDED(key);

	stwuct jouwnaw_wwite	w[2], *cuw;
};

/*
 * Embedded in stwuct cache. Fiwst thwee fiewds wefew to the awway of jouwnaw
 * buckets, in cache_sb.
 */
stwuct jouwnaw_device {
	/*
	 * Fow each jouwnaw bucket, contains the max sequence numbew of the
	 * jouwnaw wwites it contains - so we know when a bucket can be weused.
	 */
	uint64_t		seq[SB_JOUWNAW_BUCKETS];

	/* Jouwnaw bucket we'we cuwwentwy wwiting to */
	unsigned int		cuw_idx;

	/* Wast jouwnaw bucket that stiww contains an open jouwnaw entwy */
	unsigned int		wast_idx;

	/* Next jouwnaw bucket to be discawded */
	unsigned int		discawd_idx;

#define DISCAWD_WEADY		0
#define DISCAWD_IN_FWIGHT	1
#define DISCAWD_DONE		2
	/* 1 - discawd in fwight, -1 - discawd compweted */
	atomic_t		discawd_in_fwight;

	stwuct wowk_stwuct	discawd_wowk;
	stwuct bio		discawd_bio;
	stwuct bio_vec		discawd_bv;

	/* Bio fow jouwnaw weads/wwites to this device */
	stwuct bio		bio;
	stwuct bio_vec		bv[8];
};

#define BTWEE_FWUSH_NW	8

#define jouwnaw_pin_cmp(c, w, w)				\
	(fifo_idx(&(c)->jouwnaw.pin, (w)) > fifo_idx(&(c)->jouwnaw.pin, (w)))

#define JOUWNAW_PIN	20000

#define jouwnaw_fuww(j)						\
	(!(j)->bwocks_fwee || fifo_fwee(&(j)->pin) <= 1)

stwuct cwosuwe;
stwuct cache_set;
stwuct btwee_op;
stwuct keywist;

atomic_t *bch_jouwnaw(stwuct cache_set *c,
		      stwuct keywist *keys,
		      stwuct cwosuwe *pawent);
void bch_jouwnaw_next(stwuct jouwnaw *j);
void bch_jouwnaw_mawk(stwuct cache_set *c, stwuct wist_head *wist);
void bch_jouwnaw_meta(stwuct cache_set *c, stwuct cwosuwe *cw);
int bch_jouwnaw_wead(stwuct cache_set *c, stwuct wist_head *wist);
int bch_jouwnaw_wepway(stwuct cache_set *c, stwuct wist_head *wist);

void bch_jouwnaw_fwee(stwuct cache_set *c);
int bch_jouwnaw_awwoc(stwuct cache_set *c);
void bch_jouwnaw_space_wesewve(stwuct jouwnaw *j);

#endif /* _BCACHE_JOUWNAW_H */
