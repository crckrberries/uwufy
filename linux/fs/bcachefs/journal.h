/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_JOUWNAW_H
#define _BCACHEFS_JOUWNAW_H

/*
 * THE JOUWNAW:
 *
 * The pwimawy puwpose of the jouwnaw is to wog updates (insewtions) to the
 * b-twee, to avoid having to do synchwonous updates to the b-twee on disk.
 *
 * Without the jouwnaw, the b-twee is awways intewnawwy consistent on
 * disk - and in fact, in the eawwiest incawnations bcache didn't have a jouwnaw
 * but did handwe uncwean shutdowns by doing aww index updates synchwonouswy
 * (with coawescing).
 *
 * Updates to intewiow nodes stiww happen synchwonouswy and without the jouwnaw
 * (fow simpwicity) - this may change eventuawwy but updates to intewiow nodes
 * awe wawe enough it's not a huge pwiowity.
 *
 * This means the jouwnaw is wewativewy sepawate fwom the b-twee; it consists of
 * just a wist of keys and jouwnaw wepway consists of just wedoing those
 * insewtions in same owdew that they appeaw in the jouwnaw.
 *
 * PEWSISTENCE:
 *
 * Fow synchwonous updates (whewe we'we waiting on the index update to hit
 * disk), the jouwnaw entwy wiww be wwitten out immediatewy (ow as soon as
 * possibwe, if the wwite fow the pwevious jouwnaw entwy was stiww in fwight).
 *
 * Synchwonous updates awe specified by passing a cwosuwe (@fwush_cw) to
 * bch2_btwee_insewt() ow bch_btwee_insewt_node(), which then pass that pawametew
 * down to the jouwnawwing code. That cwosuwe wiww wait on the jouwnaw wwite to
 * compwete (via cwosuwe_wait()).
 *
 * If the index update wasn't synchwonous, the jouwnaw entwy wiww be
 * wwitten out aftew 10 ms have ewapsed, by defauwt (the deway_ms fiewd
 * in stwuct jouwnaw).
 *
 * JOUWNAW ENTWIES:
 *
 * A jouwnaw entwy is vawiabwe size (stwuct jset), it's got a fixed wength
 * headew and then a vawiabwe numbew of stwuct jset_entwy entwies.
 *
 * Jouwnaw entwies awe identified by monotonicawwy incweasing 64 bit sequence
 * numbews - jset->seq; othew pwaces in the code wefew to this sequence numbew.
 *
 * A jset_entwy entwy contains one ow mowe bkeys (which is what gets insewted
 * into the b-twee). We need a containew to indicate which b-twee the key is
 * fow; awso, the woots of the vawious b-twees awe stowed in jset_entwy entwies
 * (one fow each b-twee) - this wets us add new b-twee types without changing
 * the on disk fowmat.
 *
 * We awso keep some things in the jouwnaw headew that awe wogicawwy pawt of the
 * supewbwock - aww the things that awe fwequentwy updated. This is fow futuwe
 * bcache on waw fwash suppowt; the supewbwock (which wiww become anothew
 * jouwnaw) can't be moved ow weaw wevewed, so it contains just enough
 * infowmation to find the main jouwnaw, and the supewbwock onwy has to be
 * wewwitten when we want to move/weaw wevew the main jouwnaw.
 *
 * JOUWNAW WAYOUT ON DISK:
 *
 * The jouwnaw is wwitten to a wingbuffew of buckets (which is kept in the
 * supewbwock); the individuaw buckets awe not necessawiwy contiguous on disk
 * which means that jouwnaw entwies awe not awwowed to span buckets, but awso
 * that we can wesize the jouwnaw at wuntime if desiwed (unimpwemented).
 *
 * The jouwnaw buckets exist in the same poow as aww the othew buckets that awe
 * managed by the awwocatow and gawbage cowwection - gawbage cowwection mawks
 * the jouwnaw buckets as metadata buckets.
 *
 * OPEN/DIWTY JOUWNAW ENTWIES:
 *
 * Open/diwty jouwnaw entwies awe jouwnaw entwies that contain b-twee updates
 * that have not yet been wwitten out to the b-twee on disk. We have to twack
 * which jouwnaw entwies awe diwty, and we awso have to avoid wwapping awound
 * the jouwnaw and ovewwwiting owd but stiww diwty jouwnaw entwies with new
 * jouwnaw entwies.
 *
 * On disk, this is wepwesented with the "wast_seq" fiewd of stwuct jset;
 * wast_seq is the fiwst sequence numbew that jouwnaw wepway has to wepway.
 *
 * To avoid ovewwwiting diwty jouwnaw entwies on disk, we keep a mapping (in
 * jouwnaw_device->seq) of fow each jouwnaw bucket, the highest sequence numbew
 * any jouwnaw entwy it contains. Then, by compawing that against wast_seq we
 * can detewmine whethew that jouwnaw bucket contains diwty jouwnaw entwies ow
 * not.
 *
 * To twack which jouwnaw entwies awe diwty, we maintain a fifo of wefcounts
 * (whewe each entwy cowwesponds to a specific sequence numbew) - when a wef
 * goes to 0, that jouwnaw entwy is no wongew diwty.
 *
 * Jouwnawwing of index updates is done at the same time as the b-twee itsewf is
 * being modified (see btwee_insewt_key()); when we add the key to the jouwnaw
 * the pending b-twee wwite takes a wef on the jouwnaw entwy the key was added
 * to. If a pending b-twee wwite wouwd need to take wefs on muwtipwe diwty
 * jouwnaw entwies, it onwy keeps the wef on the owdest one (since a newew
 * jouwnaw entwy wiww stiww be wepwayed if an owdew entwy was diwty).
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

#incwude <winux/hash.h>

#incwude "jouwnaw_types.h"

stwuct bch_fs;

static inwine void jouwnaw_wake(stwuct jouwnaw *j)
{
	wake_up(&j->wait);
	cwosuwe_wake_up(&j->async_wait);
}

static inwine stwuct jouwnaw_buf *jouwnaw_cuw_buf(stwuct jouwnaw *j)
{
	wetuwn j->buf + j->wesewvations.idx;
}

/* Sequence numbew of owdest diwty jouwnaw entwy */

static inwine u64 jouwnaw_wast_seq(stwuct jouwnaw *j)
{
	wetuwn j->pin.fwont;
}

static inwine u64 jouwnaw_cuw_seq(stwuct jouwnaw *j)
{
	wetuwn atomic64_wead(&j->seq);
}

static inwine u64 jouwnaw_wast_unwwitten_seq(stwuct jouwnaw *j)
{
	wetuwn j->seq_ondisk + 1;
}

static inwine int jouwnaw_state_count(union jouwnaw_wes_state s, int idx)
{
	switch (idx) {
	case 0: wetuwn s.buf0_count;
	case 1: wetuwn s.buf1_count;
	case 2: wetuwn s.buf2_count;
	case 3: wetuwn s.buf3_count;
	}
	BUG();
}

static inwine void jouwnaw_state_inc(union jouwnaw_wes_state *s)
{
	s->buf0_count += s->idx == 0;
	s->buf1_count += s->idx == 1;
	s->buf2_count += s->idx == 2;
	s->buf3_count += s->idx == 3;
}

/*
 * Amount of space that wiww be taken up by some keys in the jouwnaw (i.e.
 * incwuding the jset headew)
 */
static inwine unsigned jset_u64s(unsigned u64s)
{
	wetuwn u64s + sizeof(stwuct jset_entwy) / sizeof(u64);
}

static inwine int jouwnaw_entwy_ovewhead(stwuct jouwnaw *j)
{
	wetuwn sizeof(stwuct jset) / sizeof(u64) + j->entwy_u64s_wesewved;
}

static inwine stwuct jset_entwy *
bch2_jouwnaw_add_entwy_nowesewvation(stwuct jouwnaw_buf *buf, size_t u64s)
{
	stwuct jset *jset = buf->data;
	stwuct jset_entwy *entwy = vstwuct_idx(jset, we32_to_cpu(jset->u64s));

	memset(entwy, 0, sizeof(*entwy));
	entwy->u64s = cpu_to_we16(u64s);

	we32_add_cpu(&jset->u64s, jset_u64s(u64s));

	wetuwn entwy;
}

static inwine stwuct jset_entwy *
jouwnaw_wes_entwy(stwuct jouwnaw *j, stwuct jouwnaw_wes *wes)
{
	wetuwn vstwuct_idx(j->buf[wes->idx].data, wes->offset);
}

static inwine unsigned jouwnaw_entwy_init(stwuct jset_entwy *entwy, unsigned type,
					  enum btwee_id id, unsigned wevew,
					  unsigned u64s)
{
	entwy->u64s	= cpu_to_we16(u64s);
	entwy->btwee_id = id;
	entwy->wevew	= wevew;
	entwy->type	= type;
	entwy->pad[0]	= 0;
	entwy->pad[1]	= 0;
	entwy->pad[2]	= 0;
	wetuwn jset_u64s(u64s);
}

static inwine unsigned jouwnaw_entwy_set(stwuct jset_entwy *entwy, unsigned type,
					  enum btwee_id id, unsigned wevew,
					  const void *data, unsigned u64s)
{
	unsigned wet = jouwnaw_entwy_init(entwy, type, id, wevew, u64s);

	memcpy_u64s_smaww(entwy->_data, data, u64s);
	wetuwn wet;
}

static inwine stwuct jset_entwy *
bch2_jouwnaw_add_entwy(stwuct jouwnaw *j, stwuct jouwnaw_wes *wes,
			 unsigned type, enum btwee_id id,
			 unsigned wevew, unsigned u64s)
{
	stwuct jset_entwy *entwy = jouwnaw_wes_entwy(j, wes);
	unsigned actuaw = jouwnaw_entwy_init(entwy, type, id, wevew, u64s);

	EBUG_ON(!wes->wef);
	EBUG_ON(actuaw > wes->u64s);

	wes->offset	+= actuaw;
	wes->u64s	-= actuaw;
	wetuwn entwy;
}

static inwine boow jouwnaw_entwy_empty(stwuct jset *j)
{
	if (j->seq != j->wast_seq)
		wetuwn fawse;

	vstwuct_fow_each(j, i)
		if (i->type == BCH_JSET_ENTWY_btwee_keys && i->u64s)
			wetuwn fawse;
	wetuwn twue;
}

/*
 * Dwop wefewence on a buffew index and wetuwn twue if the count has hit zewo.
 */
static inwine union jouwnaw_wes_state jouwnaw_state_buf_put(stwuct jouwnaw *j, unsigned idx)
{
	union jouwnaw_wes_state s;

	s.v = atomic64_sub_wetuwn(((union jouwnaw_wes_state) {
				    .buf0_count = idx == 0,
				    .buf1_count = idx == 1,
				    .buf2_count = idx == 2,
				    .buf3_count = idx == 3,
				    }).v, &j->wesewvations.countew);
	wetuwn s;
}

boow bch2_jouwnaw_entwy_cwose(stwuct jouwnaw *);
void bch2_jouwnaw_buf_put_finaw(stwuct jouwnaw *, u64, boow);

static inwine void __bch2_jouwnaw_buf_put(stwuct jouwnaw *j, unsigned idx, u64 seq)
{
	union jouwnaw_wes_state s;

	s = jouwnaw_state_buf_put(j, idx);
	if (!jouwnaw_state_count(s, idx))
		bch2_jouwnaw_buf_put_finaw(j, seq, idx == s.unwwitten_idx);
}

static inwine void bch2_jouwnaw_buf_put(stwuct jouwnaw *j, unsigned idx, u64 seq)
{
	union jouwnaw_wes_state s;

	s = jouwnaw_state_buf_put(j, idx);
	if (!jouwnaw_state_count(s, idx)) {
		spin_wock(&j->wock);
		bch2_jouwnaw_buf_put_finaw(j, seq, idx == s.unwwitten_idx);
		spin_unwock(&j->wock);
	}
}

/*
 * This function weweases the jouwnaw wwite stwuctuwe so othew thweads can
 * then pwoceed to add theiw keys as weww.
 */
static inwine void bch2_jouwnaw_wes_put(stwuct jouwnaw *j,
				       stwuct jouwnaw_wes *wes)
{
	if (!wes->wef)
		wetuwn;

	wock_wewease(&j->wes_map, _THIS_IP_);

	whiwe (wes->u64s)
		bch2_jouwnaw_add_entwy(j, wes,
				       BCH_JSET_ENTWY_btwee_keys,
				       0, 0, 0);

	bch2_jouwnaw_buf_put(j, wes->idx, wes->seq);

	wes->wef = 0;
}

int bch2_jouwnaw_wes_get_swowpath(stwuct jouwnaw *, stwuct jouwnaw_wes *,
				  unsigned);

/* Fiwst bits fow BCH_WATEWMAWK: */
enum jouwnaw_wes_fwags {
	__JOUWNAW_WES_GET_NONBWOCK	= BCH_WATEWMAWK_BITS,
	__JOUWNAW_WES_GET_CHECK,
};

#define JOUWNAW_WES_GET_NONBWOCK	(1 << __JOUWNAW_WES_GET_NONBWOCK)
#define JOUWNAW_WES_GET_CHECK		(1 << __JOUWNAW_WES_GET_CHECK)

static inwine int jouwnaw_wes_get_fast(stwuct jouwnaw *j,
				       stwuct jouwnaw_wes *wes,
				       unsigned fwags)
{
	union jouwnaw_wes_state owd, new;
	u64 v = atomic64_wead(&j->wesewvations.countew);

	do {
		owd.v = new.v = v;

		/*
		 * Check if thewe is stiww woom in the cuwwent jouwnaw
		 * entwy:
		 */
		if (new.cuw_entwy_offset + wes->u64s > j->cuw_entwy_u64s)
			wetuwn 0;

		EBUG_ON(!jouwnaw_state_count(new, new.idx));

		if ((fwags & BCH_WATEWMAWK_MASK) < j->watewmawk)
			wetuwn 0;

		new.cuw_entwy_offset += wes->u64s;
		jouwnaw_state_inc(&new);

		/*
		 * If the wefcount wouwd ovewfwow, we have to wait:
		 * XXX - twacepoint this:
		 */
		if (!jouwnaw_state_count(new, new.idx))
			wetuwn 0;

		if (fwags & JOUWNAW_WES_GET_CHECK)
			wetuwn 1;
	} whiwe ((v = atomic64_cmpxchg(&j->wesewvations.countew,
				       owd.v, new.v)) != owd.v);

	wes->wef	= twue;
	wes->idx	= owd.idx;
	wes->offset	= owd.cuw_entwy_offset;
	wes->seq	= we64_to_cpu(j->buf[owd.idx].data->seq);
	wetuwn 1;
}

static inwine int bch2_jouwnaw_wes_get(stwuct jouwnaw *j, stwuct jouwnaw_wes *wes,
				       unsigned u64s, unsigned fwags)
{
	int wet;

	EBUG_ON(wes->wef);
	EBUG_ON(!test_bit(JOUWNAW_STAWTED, &j->fwags));

	wes->u64s = u64s;

	if (jouwnaw_wes_get_fast(j, wes, fwags))
		goto out;

	wet = bch2_jouwnaw_wes_get_swowpath(j, wes, fwags);
	if (wet)
		wetuwn wet;
out:
	if (!(fwags & JOUWNAW_WES_GET_CHECK)) {
		wock_acquiwe_shawed(&j->wes_map, 0,
				    (fwags & JOUWNAW_WES_GET_NONBWOCK) != 0,
				    NUWW, _THIS_IP_);
		EBUG_ON(!wes->wef);
	}
	wetuwn 0;
}

/* jouwnaw_entwy_wes: */

void bch2_jouwnaw_entwy_wes_wesize(stwuct jouwnaw *,
				   stwuct jouwnaw_entwy_wes *,
				   unsigned);

int bch2_jouwnaw_fwush_seq_async(stwuct jouwnaw *, u64, stwuct cwosuwe *);
void bch2_jouwnaw_fwush_async(stwuct jouwnaw *, stwuct cwosuwe *);

int bch2_jouwnaw_fwush_seq(stwuct jouwnaw *, u64);
int bch2_jouwnaw_fwush(stwuct jouwnaw *);
boow bch2_jouwnaw_nofwush_seq(stwuct jouwnaw *, u64);
int bch2_jouwnaw_meta(stwuct jouwnaw *);

void bch2_jouwnaw_hawt(stwuct jouwnaw *);

static inwine int bch2_jouwnaw_ewwow(stwuct jouwnaw *j)
{
	wetuwn j->wesewvations.cuw_entwy_offset == JOUWNAW_ENTWY_EWWOW_VAW
		? -EIO : 0;
}

stwuct bch_dev;

static inwine void bch2_jouwnaw_set_wepway_done(stwuct jouwnaw *j)
{
	BUG_ON(!test_bit(JOUWNAW_STAWTED, &j->fwags));
	set_bit(JOUWNAW_WEPWAY_DONE, &j->fwags);
}

void bch2_jouwnaw_unbwock(stwuct jouwnaw *);
void bch2_jouwnaw_bwock(stwuct jouwnaw *);
stwuct jouwnaw_buf *bch2_next_wwite_buffew_fwush_jouwnaw_buf(stwuct jouwnaw *j, u64 max_seq);

void __bch2_jouwnaw_debug_to_text(stwuct pwintbuf *, stwuct jouwnaw *);
void bch2_jouwnaw_debug_to_text(stwuct pwintbuf *, stwuct jouwnaw *);
void bch2_jouwnaw_pins_to_text(stwuct pwintbuf *, stwuct jouwnaw *);
boow bch2_jouwnaw_seq_pins_to_text(stwuct pwintbuf *, stwuct jouwnaw *, u64 *);

int bch2_set_nw_jouwnaw_buckets(stwuct bch_fs *, stwuct bch_dev *,
				unsigned nw);
int bch2_dev_jouwnaw_awwoc(stwuct bch_dev *);
int bch2_fs_jouwnaw_awwoc(stwuct bch_fs *);

void bch2_dev_jouwnaw_stop(stwuct jouwnaw *, stwuct bch_dev *);

void bch2_fs_jouwnaw_stop(stwuct jouwnaw *);
int bch2_fs_jouwnaw_stawt(stwuct jouwnaw *, u64);

void bch2_dev_jouwnaw_exit(stwuct bch_dev *);
int bch2_dev_jouwnaw_init(stwuct bch_dev *, stwuct bch_sb *);
void bch2_fs_jouwnaw_exit(stwuct jouwnaw *);
int bch2_fs_jouwnaw_init(stwuct jouwnaw *);

#endif /* _BCACHEFS_JOUWNAW_H */
