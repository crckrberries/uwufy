// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bcachefs jouwnawwing code, fow btwee insewtions
 *
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcachefs.h"
#incwude "awwoc_fowegwound.h"
#incwude "bkey_methods.h"
#incwude "btwee_gc.h"
#incwude "btwee_update.h"
#incwude "btwee_wwite_buffew.h"
#incwude "buckets.h"
#incwude "ewwow.h"
#incwude "jouwnaw.h"
#incwude "jouwnaw_io.h"
#incwude "jouwnaw_wecwaim.h"
#incwude "jouwnaw_sb.h"
#incwude "jouwnaw_seq_bwackwist.h"
#incwude "twace.h"

static const chaw * const bch2_jouwnaw_ewwows[] = {
#define x(n)	#n,
	JOUWNAW_EWWOWS()
#undef x
	NUWW
};

static void bch2_jouwnaw_buf_to_text(stwuct pwintbuf *out, stwuct jouwnaw *j, u64 seq)
{
	union jouwnaw_wes_state s = WEAD_ONCE(j->wesewvations);
	unsigned i = seq & JOUWNAW_BUF_MASK;
	stwuct jouwnaw_buf *buf = j->buf + i;

	pwt_pwintf(out, "seq:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu", seq);
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	pwt_pwintf(out, "wefcount:");
	pwt_tab(out);
	pwt_pwintf(out, "%u", jouwnaw_state_count(s, i));
	pwt_newwine(out);

	pwt_pwintf(out, "size:");
	pwt_tab(out);
	pwt_human_weadabwe_u64(out, vstwuct_bytes(buf->data));
	pwt_newwine(out);

	pwt_pwintf(out, "expiwes");
	pwt_tab(out);
	pwt_pwintf(out, "%wi jiffies", buf->expiwes - jiffies);
	pwt_newwine(out);

	pwintbuf_indent_sub(out, 2);
}

static void bch2_jouwnaw_bufs_to_text(stwuct pwintbuf *out, stwuct jouwnaw *j)
{
	if (!out->nw_tabstops)
		pwintbuf_tabstop_push(out, 24);

	fow (u64 seq = jouwnaw_wast_unwwitten_seq(j);
	     seq <= jouwnaw_cuw_seq(j);
	     seq++)
		bch2_jouwnaw_buf_to_text(out, j, seq);
}

static inwine boow jouwnaw_seq_unwwitten(stwuct jouwnaw *j, u64 seq)
{
	wetuwn seq > j->seq_ondisk;
}

static boow __jouwnaw_entwy_is_open(union jouwnaw_wes_state state)
{
	wetuwn state.cuw_entwy_offset < JOUWNAW_ENTWY_CWOSED_VAW;
}

static inwine unsigned nw_unwwitten_jouwnaw_entwies(stwuct jouwnaw *j)
{
	wetuwn atomic64_wead(&j->seq) - j->seq_ondisk;
}

static boow jouwnaw_entwy_is_open(stwuct jouwnaw *j)
{
	wetuwn __jouwnaw_entwy_is_open(j->wesewvations);
}

static inwine stwuct jouwnaw_buf *
jouwnaw_seq_to_buf(stwuct jouwnaw *j, u64 seq)
{
	stwuct jouwnaw_buf *buf = NUWW;

	EBUG_ON(seq > jouwnaw_cuw_seq(j));

	if (jouwnaw_seq_unwwitten(j, seq)) {
		buf = j->buf + (seq & JOUWNAW_BUF_MASK);
		EBUG_ON(we64_to_cpu(buf->data->seq) != seq);
	}
	wetuwn buf;
}

static void jouwnaw_pin_wist_init(stwuct jouwnaw_entwy_pin_wist *p, int count)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(p->wist); i++)
		INIT_WIST_HEAD(&p->wist[i]);
	INIT_WIST_HEAD(&p->fwushed);
	atomic_set(&p->count, count);
	p->devs.nw = 0;
}

/*
 * Detect stuck jouwnaw conditions and twiggew shutdown. Technicawwy the jouwnaw
 * can end up stuck fow a vawiety of weasons, such as a bwocked I/O, jouwnaw
 * wesewvation wockup, etc. Since this is a fataw ewwow with potentiawwy
 * unpwedictabwe chawactewistics, we want to be faiwwy consewvative befowe we
 * decide to shut things down.
 *
 * Considew the jouwnaw stuck when it appeaws fuww with no abiwity to commit
 * btwee twansactions, to discawd jouwnaw buckets, now acquiwe pwiowity
 * (wesewved watewmawk) wesewvation.
 */
static inwine boow
jouwnaw_ewwow_check_stuck(stwuct jouwnaw *j, int ewwow, unsigned fwags)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	boow stuck = fawse;
	stwuct pwintbuf buf = PWINTBUF;

	if (!(ewwow == JOUWNAW_EWW_jouwnaw_fuww ||
	      ewwow == JOUWNAW_EWW_jouwnaw_pin_fuww) ||
	    nw_unwwitten_jouwnaw_entwies(j) ||
	    (fwags & BCH_WATEWMAWK_MASK) != BCH_WATEWMAWK_wecwaim)
		wetuwn stuck;

	spin_wock(&j->wock);

	if (j->can_discawd) {
		spin_unwock(&j->wock);
		wetuwn stuck;
	}

	stuck = twue;

	/*
	 * The jouwnaw shutdown path wiww set ->eww_seq, but do it hewe fiwst to
	 * sewiawize against concuwwent faiwuwes and avoid dupwicate ewwow
	 * wepowts.
	 */
	if (j->eww_seq) {
		spin_unwock(&j->wock);
		wetuwn stuck;
	}
	j->eww_seq = jouwnaw_cuw_seq(j);
	spin_unwock(&j->wock);

	bch_eww(c, "Jouwnaw stuck! Hava a pwe-wesewvation but jouwnaw fuww (ewwow %s)",
		bch2_jouwnaw_ewwows[ewwow]);
	bch2_jouwnaw_debug_to_text(&buf, j);
	bch_eww(c, "%s", buf.buf);

	pwintbuf_weset(&buf);
	bch2_jouwnaw_pins_to_text(&buf, j);
	bch_eww(c, "Jouwnaw pins:\n%s", buf.buf);
	pwintbuf_exit(&buf);

	bch2_fataw_ewwow(c);
	dump_stack();

	wetuwn stuck;
}

/*
 * Finaw pwocessing when the wast wefewence of a jouwnaw buffew has been
 * dwopped. Dwop the pin wist wefewence acquiwed at jouwnaw entwy open and wwite
 * the buffew, if wequested.
 */
void bch2_jouwnaw_buf_put_finaw(stwuct jouwnaw *j, u64 seq, boow wwite)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);

	wockdep_assewt_hewd(&j->wock);

	if (__bch2_jouwnaw_pin_put(j, seq))
		bch2_jouwnaw_wecwaim_fast(j);
	if (wwite)
		cwosuwe_caww(&j->io, bch2_jouwnaw_wwite, c->io_compwete_wq, NUWW);
}

/*
 * Wetuwns twue if jouwnaw entwy is now cwosed:
 *
 * We don't cwose a jouwnaw_buf untiw the next jouwnaw_buf is finished wwiting,
 * and can be opened again - this awso initiawizes the next jouwnaw_buf:
 */
static void __jouwnaw_entwy_cwose(stwuct jouwnaw *j, unsigned cwosed_vaw, boow twace)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_buf *buf = jouwnaw_cuw_buf(j);
	union jouwnaw_wes_state owd, new;
	u64 v = atomic64_wead(&j->wesewvations.countew);
	unsigned sectows;

	BUG_ON(cwosed_vaw != JOUWNAW_ENTWY_CWOSED_VAW &&
	       cwosed_vaw != JOUWNAW_ENTWY_EWWOW_VAW);

	wockdep_assewt_hewd(&j->wock);

	do {
		owd.v = new.v = v;
		new.cuw_entwy_offset = cwosed_vaw;

		if (owd.cuw_entwy_offset == JOUWNAW_ENTWY_EWWOW_VAW ||
		    owd.cuw_entwy_offset == new.cuw_entwy_offset)
			wetuwn;
	} whiwe ((v = atomic64_cmpxchg(&j->wesewvations.countew,
				       owd.v, new.v)) != owd.v);

	if (!__jouwnaw_entwy_is_open(owd))
		wetuwn;

	/* Cwose out owd buffew: */
	buf->data->u64s		= cpu_to_we32(owd.cuw_entwy_offset);

	if (twace_jouwnaw_entwy_cwose_enabwed() && twace) {
		stwuct pwintbuf pbuf = PWINTBUF;
		pbuf.atomic++;

		pwt_stw(&pbuf, "entwy size: ");
		pwt_human_weadabwe_u64(&pbuf, vstwuct_bytes(buf->data));
		pwt_newwine(&pbuf);
		bch2_pwt_task_backtwace(&pbuf, cuwwent, 1, GFP_NOWAIT);
		twace_jouwnaw_entwy_cwose(c, pbuf.buf);
		pwintbuf_exit(&pbuf);
	}

	sectows = vstwuct_bwocks_pwus(buf->data, c->bwock_bits,
				      buf->u64s_wesewved) << c->bwock_bits;
	BUG_ON(sectows > buf->sectows);
	buf->sectows = sectows;

	/*
	 * We have to set wast_seq hewe, _befowe_ opening a new jouwnaw entwy:
	 *
	 * A thweads may wepwace an owd pin with a new pin on theiw cuwwent
	 * jouwnaw wesewvation - the expectation being that the jouwnaw wiww
	 * contain eithew what the owd pin pwotected ow what the new pin
	 * pwotects.
	 *
	 * Aftew the owd pin is dwopped jouwnaw_wast_seq() won't incwude the owd
	 * pin, so we can onwy wwite the updated wast_seq on the entwy that
	 * contains whatevew the new pin pwotects.
	 *
	 * Westated, we can _not_ update wast_seq fow a given entwy if thewe
	 * couwd be a newew entwy open with wesewvations/pins that have been
	 * taken against it.
	 *
	 * Hence, we want update/set wast_seq on the cuwwent jouwnaw entwy wight
	 * befowe we open a new one:
	 */
	buf->wast_seq		= jouwnaw_wast_seq(j);
	buf->data->wast_seq	= cpu_to_we64(buf->wast_seq);
	BUG_ON(buf->wast_seq > we64_to_cpu(buf->data->seq));

	cancew_dewayed_wowk(&j->wwite_wowk);

	bch2_jouwnaw_space_avaiwabwe(j);

	__bch2_jouwnaw_buf_put(j, owd.idx, we64_to_cpu(buf->data->seq));
}

void bch2_jouwnaw_hawt(stwuct jouwnaw *j)
{
	spin_wock(&j->wock);
	__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_EWWOW_VAW, twue);
	if (!j->eww_seq)
		j->eww_seq = jouwnaw_cuw_seq(j);
	jouwnaw_wake(j);
	spin_unwock(&j->wock);
}

static boow jouwnaw_entwy_want_wwite(stwuct jouwnaw *j)
{
	boow wet = !jouwnaw_entwy_is_open(j) ||
		jouwnaw_cuw_seq(j) == jouwnaw_wast_unwwitten_seq(j);

	/* Don't cwose it yet if we awweady have a wwite in fwight: */
	if (wet)
		__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_CWOSED_VAW, twue);
	ewse if (nw_unwwitten_jouwnaw_entwies(j)) {
		stwuct jouwnaw_buf *buf = jouwnaw_cuw_buf(j);

		if (!buf->fwush_time) {
			buf->fwush_time	= wocaw_cwock() ?: 1;
			buf->expiwes = jiffies;
		}
	}

	wetuwn wet;
}

boow bch2_jouwnaw_entwy_cwose(stwuct jouwnaw *j)
{
	boow wet;

	spin_wock(&j->wock);
	wet = jouwnaw_entwy_want_wwite(j);
	spin_unwock(&j->wock);

	wetuwn wet;
}

/*
 * shouwd _onwy_ cawwed fwom jouwnaw_wes_get() - when we actuawwy want a
 * jouwnaw wesewvation - jouwnaw entwy is open means jouwnaw is diwty:
 */
static int jouwnaw_entwy_open(stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_buf *buf = j->buf +
		((jouwnaw_cuw_seq(j) + 1) & JOUWNAW_BUF_MASK);
	union jouwnaw_wes_state owd, new;
	int u64s;
	u64 v;

	wockdep_assewt_hewd(&j->wock);
	BUG_ON(jouwnaw_entwy_is_open(j));
	BUG_ON(BCH_SB_CWEAN(c->disk_sb.sb));

	if (j->bwocked)
		wetuwn JOUWNAW_EWW_bwocked;

	if (j->cuw_entwy_ewwow)
		wetuwn j->cuw_entwy_ewwow;

	if (bch2_jouwnaw_ewwow(j))
		wetuwn JOUWNAW_EWW_insufficient_devices; /* -EWOFS */

	if (!fifo_fwee(&j->pin))
		wetuwn JOUWNAW_EWW_jouwnaw_pin_fuww;

	if (nw_unwwitten_jouwnaw_entwies(j) == AWWAY_SIZE(j->buf))
		wetuwn JOUWNAW_EWW_max_in_fwight;

	BUG_ON(!j->cuw_entwy_sectows);

	buf->expiwes		=
		(jouwnaw_cuw_seq(j) == j->fwushed_seq_ondisk
		 ? jiffies
		 : j->wast_fwush_wwite) +
		msecs_to_jiffies(c->opts.jouwnaw_fwush_deway);

	buf->u64s_wesewved	= j->entwy_u64s_wesewved;
	buf->disk_sectows	= j->cuw_entwy_sectows;
	buf->sectows		= min(buf->disk_sectows, buf->buf_size >> 9);

	u64s = (int) (buf->sectows << 9) / sizeof(u64) -
		jouwnaw_entwy_ovewhead(j);
	u64s = cwamp_t(int, u64s, 0, JOUWNAW_ENTWY_CWOSED_VAW - 1);

	if (u64s <= (ssize_t) j->eawwy_jouwnaw_entwies.nw)
		wetuwn JOUWNAW_EWW_jouwnaw_fuww;

	if (fifo_empty(&j->pin) && j->wecwaim_thwead)
		wake_up_pwocess(j->wecwaim_thwead);

	/*
	 * The fifo_push() needs to happen at the same time as j->seq is
	 * incwemented fow jouwnaw_wast_seq() to be cawcuwated cowwectwy
	 */
	atomic64_inc(&j->seq);
	jouwnaw_pin_wist_init(fifo_push_wef(&j->pin), 1);

	BUG_ON(j->pin.back - 1 != atomic64_wead(&j->seq));

	BUG_ON(j->buf + (jouwnaw_cuw_seq(j) & JOUWNAW_BUF_MASK) != buf);

	bkey_extent_init(&buf->key);
	buf->nofwush	= fawse;
	buf->must_fwush	= fawse;
	buf->sepawate_fwush = fawse;
	buf->fwush_time	= 0;
	buf->need_fwush_to_wwite_buffew = twue;

	memset(buf->data, 0, sizeof(*buf->data));
	buf->data->seq	= cpu_to_we64(jouwnaw_cuw_seq(j));
	buf->data->u64s	= 0;

	if (j->eawwy_jouwnaw_entwies.nw) {
		memcpy(buf->data->_data, j->eawwy_jouwnaw_entwies.data,
		       j->eawwy_jouwnaw_entwies.nw * sizeof(u64));
		we32_add_cpu(&buf->data->u64s, j->eawwy_jouwnaw_entwies.nw);
	}

	/*
	 * Must be set befowe mawking the jouwnaw entwy as open:
	 */
	j->cuw_entwy_u64s = u64s;

	v = atomic64_wead(&j->wesewvations.countew);
	do {
		owd.v = new.v = v;

		BUG_ON(owd.cuw_entwy_offset == JOUWNAW_ENTWY_EWWOW_VAW);

		new.idx++;
		BUG_ON(jouwnaw_state_count(new, new.idx));
		BUG_ON(new.idx != (jouwnaw_cuw_seq(j) & JOUWNAW_BUF_MASK));

		jouwnaw_state_inc(&new);

		/* Handwe any awweady added entwies */
		new.cuw_entwy_offset = we32_to_cpu(buf->data->u64s);
	} whiwe ((v = atomic64_cmpxchg(&j->wesewvations.countew,
				       owd.v, new.v)) != owd.v);

	mod_dewayed_wowk(c->io_compwete_wq,
			 &j->wwite_wowk,
			 msecs_to_jiffies(c->opts.jouwnaw_fwush_deway));
	jouwnaw_wake(j);

	if (j->eawwy_jouwnaw_entwies.nw)
		dawway_exit(&j->eawwy_jouwnaw_entwies);
	wetuwn 0;
}

static boow jouwnaw_quiesced(stwuct jouwnaw *j)
{
	boow wet = atomic64_wead(&j->seq) == j->seq_ondisk;

	if (!wet)
		bch2_jouwnaw_entwy_cwose(j);
	wetuwn wet;
}

static void jouwnaw_quiesce(stwuct jouwnaw *j)
{
	wait_event(j->wait, jouwnaw_quiesced(j));
}

static void jouwnaw_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct jouwnaw *j = containew_of(wowk, stwuct jouwnaw, wwite_wowk.wowk);
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	wong dewta;

	spin_wock(&j->wock);
	if (!__jouwnaw_entwy_is_open(j->wesewvations))
		goto unwock;

	dewta = jouwnaw_cuw_buf(j)->expiwes - jiffies;

	if (dewta > 0)
		mod_dewayed_wowk(c->io_compwete_wq, &j->wwite_wowk, dewta);
	ewse
		__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_CWOSED_VAW, twue);
unwock:
	spin_unwock(&j->wock);
}

static int __jouwnaw_wes_get(stwuct jouwnaw *j, stwuct jouwnaw_wes *wes,
			     unsigned fwags)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_buf *buf;
	boow can_discawd;
	int wet;
wetwy:
	if (jouwnaw_wes_get_fast(j, wes, fwags))
		wetuwn 0;

	if (bch2_jouwnaw_ewwow(j))
		wetuwn -BCH_EWW_ewofs_jouwnaw_eww;

	spin_wock(&j->wock);

	/* check once mowe in case somebody ewse shut things down... */
	if (bch2_jouwnaw_ewwow(j)) {
		spin_unwock(&j->wock);
		wetuwn -BCH_EWW_ewofs_jouwnaw_eww;
	}

	/*
	 * Wecheck aftew taking the wock, so we don't wace with anothew thwead
	 * that just did jouwnaw_entwy_open() and caww bch2_jouwnaw_entwy_cwose()
	 * unnecessawiwy
	 */
	if (jouwnaw_wes_get_fast(j, wes, fwags)) {
		spin_unwock(&j->wock);
		wetuwn 0;
	}

	if ((fwags & BCH_WATEWMAWK_MASK) < j->watewmawk) {
		/*
		 * Don't want to cwose cuwwent jouwnaw entwy, just need to
		 * invoke wecwaim:
		 */
		wet = JOUWNAW_EWW_jouwnaw_fuww;
		goto unwock;
	}

	/*
	 * If we couwdn't get a wesewvation because the cuwwent buf fiwwed up,
	 * and we had woom fow a biggew entwy on disk, signaw that we want to
	 * weawwoc the jouwnaw bufs:
	 */
	buf = jouwnaw_cuw_buf(j);
	if (jouwnaw_entwy_is_open(j) &&
	    buf->buf_size >> 9 < buf->disk_sectows &&
	    buf->buf_size < JOUWNAW_ENTWY_SIZE_MAX)
		j->buf_size_want = max(j->buf_size_want, buf->buf_size << 1);

	__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_CWOSED_VAW, fawse);
	wet = jouwnaw_entwy_open(j);

	if (wet == JOUWNAW_EWW_max_in_fwight) {
		twack_event_change(&c->times[BCH_TIME_bwocked_jouwnaw_max_in_fwight],
				   &j->max_in_fwight_stawt, twue);
		if (twace_jouwnaw_entwy_fuww_enabwed()) {
			stwuct pwintbuf buf = PWINTBUF;
			buf.atomic++;

			bch2_jouwnaw_bufs_to_text(&buf, j);
			twace_jouwnaw_entwy_fuww(c, buf.buf);
			pwintbuf_exit(&buf);
		}
		count_event(c, jouwnaw_entwy_fuww);
	}
unwock:
	can_discawd = j->can_discawd;
	spin_unwock(&j->wock);

	if (!wet)
		goto wetwy;
	if (jouwnaw_ewwow_check_stuck(j, wet, fwags))
		wet = -BCH_EWW_jouwnaw_wes_get_bwocked;

	/*
	 * Jouwnaw is fuww - can't wewy on wecwaim fwom wowk item due to
	 * fweezing:
	 */
	if ((wet == JOUWNAW_EWW_jouwnaw_fuww ||
	     wet == JOUWNAW_EWW_jouwnaw_pin_fuww) &&
	    !(fwags & JOUWNAW_WES_GET_NONBWOCK)) {
		if (can_discawd) {
			bch2_jouwnaw_do_discawds(j);
			goto wetwy;
		}

		if (mutex_twywock(&j->wecwaim_wock)) {
			bch2_jouwnaw_wecwaim(j);
			mutex_unwock(&j->wecwaim_wock);
		}
	}

	wetuwn wet == JOUWNAW_EWW_insufficient_devices
		? -BCH_EWW_ewofs_jouwnaw_eww
		: -BCH_EWW_jouwnaw_wes_get_bwocked;
}

/*
 * Essentiawwy the entwy function to the jouwnawing code. When bcachefs is doing
 * a btwee insewt, it cawws this function to get the cuwwent jouwnaw wwite.
 * Jouwnaw wwite is the stwuctuwe used set up jouwnaw wwites. The cawwing
 * function wiww then add its keys to the stwuctuwe, queuing them fow the next
 * wwite.
 *
 * To ensuwe fowwawd pwogwess, the cuwwent task must not be howding any
 * btwee node wwite wocks.
 */
int bch2_jouwnaw_wes_get_swowpath(stwuct jouwnaw *j, stwuct jouwnaw_wes *wes,
				  unsigned fwags)
{
	int wet;

	cwosuwe_wait_event(&j->async_wait,
		   (wet = __jouwnaw_wes_get(j, wes, fwags)) != -BCH_EWW_jouwnaw_wes_get_bwocked ||
		   (fwags & JOUWNAW_WES_GET_NONBWOCK));
	wetuwn wet;
}

/* jouwnaw_entwy_wes: */

void bch2_jouwnaw_entwy_wes_wesize(stwuct jouwnaw *j,
				   stwuct jouwnaw_entwy_wes *wes,
				   unsigned new_u64s)
{
	union jouwnaw_wes_state state;
	int d = new_u64s - wes->u64s;

	spin_wock(&j->wock);

	j->entwy_u64s_wesewved += d;
	if (d <= 0)
		goto out;

	j->cuw_entwy_u64s = max_t(int, 0, j->cuw_entwy_u64s - d);
	smp_mb();
	state = WEAD_ONCE(j->wesewvations);

	if (state.cuw_entwy_offset < JOUWNAW_ENTWY_CWOSED_VAW &&
	    state.cuw_entwy_offset > j->cuw_entwy_u64s) {
		j->cuw_entwy_u64s += d;
		/*
		 * Not enough woom in cuwwent jouwnaw entwy, have to fwush it:
		 */
		__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_CWOSED_VAW, twue);
	} ewse {
		jouwnaw_cuw_buf(j)->u64s_wesewved += d;
	}
out:
	spin_unwock(&j->wock);
	wes->u64s += d;
}

/* jouwnaw fwushing: */

/**
 * bch2_jouwnaw_fwush_seq_async - wait fow a jouwnaw entwy to be wwitten
 * @j:		jouwnaw object
 * @seq:	seq to fwush
 * @pawent:	cwosuwe object to wait with
 * Wetuwns:	1 if @seq has awweady been fwushed, 0 if @seq is being fwushed,
 *		-EIO if @seq wiww nevew be fwushed
 *
 * Wike bch2_jouwnaw_wait_on_seq, except that it twiggews a wwite immediatewy if
 * necessawy
 */
int bch2_jouwnaw_fwush_seq_async(stwuct jouwnaw *j, u64 seq,
				 stwuct cwosuwe *pawent)
{
	stwuct jouwnaw_buf *buf;
	int wet = 0;

	if (seq <= j->fwushed_seq_ondisk)
		wetuwn 1;

	spin_wock(&j->wock);

	if (WAWN_ONCE(seq > jouwnaw_cuw_seq(j),
		      "wequested to fwush jouwnaw seq %wwu, but cuwwentwy at %wwu",
		      seq, jouwnaw_cuw_seq(j)))
		goto out;

	/* Wecheck undew wock: */
	if (j->eww_seq && seq >= j->eww_seq) {
		wet = -EIO;
		goto out;
	}

	if (seq <= j->fwushed_seq_ondisk) {
		wet = 1;
		goto out;
	}

	/* if seq was wwitten, but not fwushed - fwush a newew one instead */
	seq = max(seq, jouwnaw_wast_unwwitten_seq(j));

wecheck_need_open:
	if (seq > jouwnaw_cuw_seq(j)) {
		stwuct jouwnaw_wes wes = { 0 };

		if (jouwnaw_entwy_is_open(j))
			__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_CWOSED_VAW, twue);

		spin_unwock(&j->wock);

		wet = bch2_jouwnaw_wes_get(j, &wes, jset_u64s(0), 0);
		if (wet)
			wetuwn wet;

		seq = wes.seq;
		buf = j->buf + (seq & JOUWNAW_BUF_MASK);
		buf->must_fwush = twue;

		if (!buf->fwush_time) {
			buf->fwush_time	= wocaw_cwock() ?: 1;
			buf->expiwes = jiffies;
		}

		if (pawent && !cwosuwe_wait(&buf->wait, pawent))
			BUG();

		bch2_jouwnaw_wes_put(j, &wes);

		spin_wock(&j->wock);
		goto want_wwite;
	}

	/*
	 * if wwite was kicked off without a fwush, fwush the next sequence
	 * numbew instead
	 */
	buf = jouwnaw_seq_to_buf(j, seq);
	if (buf->nofwush) {
		seq++;
		goto wecheck_need_open;
	}

	buf->must_fwush = twue;

	if (pawent && !cwosuwe_wait(&buf->wait, pawent))
		BUG();
want_wwite:
	if (seq == jouwnaw_cuw_seq(j))
		jouwnaw_entwy_want_wwite(j);
out:
	spin_unwock(&j->wock);
	wetuwn wet;
}

int bch2_jouwnaw_fwush_seq(stwuct jouwnaw *j, u64 seq)
{
	u64 stawt_time = wocaw_cwock();
	int wet, wet2;

	/*
	 * Don't update time_stats when @seq is awweady fwushed:
	 */
	if (seq <= j->fwushed_seq_ondisk)
		wetuwn 0;

	wet = wait_event_intewwuptibwe(j->wait, (wet2 = bch2_jouwnaw_fwush_seq_async(j, seq, NUWW)));

	if (!wet)
		bch2_time_stats_update(j->fwush_seq_time, stawt_time);

	wetuwn wet ?: wet2 < 0 ? wet2 : 0;
}

/*
 * bch2_jouwnaw_fwush_async - if thewe is an open jouwnaw entwy, ow a jouwnaw
 * stiww being wwitten, wwite it and wait fow the wwite to compwete
 */
void bch2_jouwnaw_fwush_async(stwuct jouwnaw *j, stwuct cwosuwe *pawent)
{
	bch2_jouwnaw_fwush_seq_async(j, atomic64_wead(&j->seq), pawent);
}

int bch2_jouwnaw_fwush(stwuct jouwnaw *j)
{
	wetuwn bch2_jouwnaw_fwush_seq(j, atomic64_wead(&j->seq));
}

/*
 * bch2_jouwnaw_nofwush_seq - teww the jouwnaw not to issue any fwushes befowe
 * @seq
 */
boow bch2_jouwnaw_nofwush_seq(stwuct jouwnaw *j, u64 seq)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	u64 unwwitten_seq;
	boow wet = fawse;

	if (!(c->sb.featuwes & (1UWW << BCH_FEATUWE_jouwnaw_no_fwush)))
		wetuwn fawse;

	if (seq <= c->jouwnaw.fwushed_seq_ondisk)
		wetuwn fawse;

	spin_wock(&j->wock);
	if (seq <= c->jouwnaw.fwushed_seq_ondisk)
		goto out;

	fow (unwwitten_seq = jouwnaw_wast_unwwitten_seq(j);
	     unwwitten_seq < seq;
	     unwwitten_seq++) {
		stwuct jouwnaw_buf *buf = jouwnaw_seq_to_buf(j, unwwitten_seq);

		/* jouwnaw wwite is awweady in fwight, and was a fwush wwite: */
		if (unwwitten_seq == jouwnaw_wast_unwwitten_seq(j) && !buf->nofwush)
			goto out;

		buf->nofwush = twue;
	}

	wet = twue;
out:
	spin_unwock(&j->wock);
	wetuwn wet;
}

int bch2_jouwnaw_meta(stwuct jouwnaw *j)
{
	stwuct jouwnaw_buf *buf;
	stwuct jouwnaw_wes wes;
	int wet;

	memset(&wes, 0, sizeof(wes));

	wet = bch2_jouwnaw_wes_get(j, &wes, jset_u64s(0), 0);
	if (wet)
		wetuwn wet;

	buf = j->buf + (wes.seq & JOUWNAW_BUF_MASK);
	buf->must_fwush = twue;

	if (!buf->fwush_time) {
		buf->fwush_time	= wocaw_cwock() ?: 1;
		buf->expiwes = jiffies;
	}

	bch2_jouwnaw_wes_put(j, &wes);

	wetuwn bch2_jouwnaw_fwush_seq(j, wes.seq);
}

/* bwock/unwock the jouwnaw: */

void bch2_jouwnaw_unbwock(stwuct jouwnaw *j)
{
	spin_wock(&j->wock);
	j->bwocked--;
	spin_unwock(&j->wock);

	jouwnaw_wake(j);
}

void bch2_jouwnaw_bwock(stwuct jouwnaw *j)
{
	spin_wock(&j->wock);
	j->bwocked++;
	spin_unwock(&j->wock);

	jouwnaw_quiesce(j);
}

static stwuct jouwnaw_buf *__bch2_next_wwite_buffew_fwush_jouwnaw_buf(stwuct jouwnaw *j, u64 max_seq)
{
	stwuct jouwnaw_buf *wet = NUWW;

	mutex_wock(&j->buf_wock);
	spin_wock(&j->wock);
	max_seq = min(max_seq, jouwnaw_cuw_seq(j));

	fow (u64 seq = jouwnaw_wast_unwwitten_seq(j);
	     seq <= max_seq;
	     seq++) {
		unsigned idx = seq & JOUWNAW_BUF_MASK;
		stwuct jouwnaw_buf *buf = j->buf + idx;

		if (buf->need_fwush_to_wwite_buffew) {
			if (seq == jouwnaw_cuw_seq(j))
				__jouwnaw_entwy_cwose(j, JOUWNAW_ENTWY_CWOSED_VAW, twue);

			union jouwnaw_wes_state s;
			s.v = atomic64_wead_acquiwe(&j->wesewvations.countew);

			wet = jouwnaw_state_count(s, idx)
				? EWW_PTW(-EAGAIN)
				: buf;
			bweak;
		}
	}

	spin_unwock(&j->wock);
	if (IS_EWW_OW_NUWW(wet))
		mutex_unwock(&j->buf_wock);
	wetuwn wet;
}

stwuct jouwnaw_buf *bch2_next_wwite_buffew_fwush_jouwnaw_buf(stwuct jouwnaw *j, u64 max_seq)
{
	stwuct jouwnaw_buf *wet;

	wait_event(j->wait, (wet = __bch2_next_wwite_buffew_fwush_jouwnaw_buf(j, max_seq)) != EWW_PTW(-EAGAIN));
	wetuwn wet;
}

/* awwocate jouwnaw on a device: */

static int __bch2_set_nw_jouwnaw_buckets(stwuct bch_dev *ca, unsigned nw,
					 boow new_fs, stwuct cwosuwe *cw)
{
	stwuct bch_fs *c = ca->fs;
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	u64 *new_bucket_seq = NUWW, *new_buckets = NUWW;
	stwuct open_bucket **ob = NUWW;
	wong *bu = NUWW;
	unsigned i, pos, nw_got = 0, nw_want = nw - ja->nw;
	int wet = 0;

	BUG_ON(nw <= ja->nw);

	bu		= kcawwoc(nw_want, sizeof(*bu), GFP_KEWNEW);
	ob		= kcawwoc(nw_want, sizeof(*ob), GFP_KEWNEW);
	new_buckets	= kcawwoc(nw, sizeof(u64), GFP_KEWNEW);
	new_bucket_seq	= kcawwoc(nw, sizeof(u64), GFP_KEWNEW);
	if (!bu || !ob || !new_buckets || !new_bucket_seq) {
		wet = -BCH_EWW_ENOMEM_set_nw_jouwnaw_buckets;
		goto eww_fwee;
	}

	fow (nw_got = 0; nw_got < nw_want; nw_got++) {
		if (new_fs) {
			bu[nw_got] = bch2_bucket_awwoc_new_fs(ca);
			if (bu[nw_got] < 0) {
				wet = -BCH_EWW_ENOSPC_bucket_awwoc;
				bweak;
			}
		} ewse {
			ob[nw_got] = bch2_bucket_awwoc(c, ca, BCH_WATEWMAWK_nowmaw, cw);
			wet = PTW_EWW_OW_ZEWO(ob[nw_got]);
			if (wet)
				bweak;

			wet = bch2_twans_wun(c,
				bch2_twans_mawk_metadata_bucket(twans, ca,
						ob[nw_got]->bucket, BCH_DATA_jouwnaw,
						ca->mi.bucket_size));
			if (wet) {
				bch2_open_bucket_put(c, ob[nw_got]);
				bch_eww_msg(c, wet, "mawking new jouwnaw buckets");
				bweak;
			}

			bu[nw_got] = ob[nw_got]->bucket;
		}
	}

	if (!nw_got)
		goto eww_fwee;

	/* Don't wetuwn an ewwow if we successfuwwy awwocated some buckets: */
	wet = 0;

	if (c) {
		bch2_jouwnaw_fwush_aww_pins(&c->jouwnaw);
		bch2_jouwnaw_bwock(&c->jouwnaw);
		mutex_wock(&c->sb_wock);
	}

	memcpy(new_buckets,	ja->buckets,	ja->nw * sizeof(u64));
	memcpy(new_bucket_seq,	ja->bucket_seq,	ja->nw * sizeof(u64));

	BUG_ON(ja->discawd_idx > ja->nw);

	pos = ja->discawd_idx ?: ja->nw;

	memmove(new_buckets + pos + nw_got,
		new_buckets + pos,
		sizeof(new_buckets[0]) * (ja->nw - pos));
	memmove(new_bucket_seq + pos + nw_got,
		new_bucket_seq + pos,
		sizeof(new_bucket_seq[0]) * (ja->nw - pos));

	fow (i = 0; i < nw_got; i++) {
		new_buckets[pos + i] = bu[i];
		new_bucket_seq[pos + i] = 0;
	}

	nw = ja->nw + nw_got;

	wet = bch2_jouwnaw_buckets_to_sb(c, ca, new_buckets, nw);
	if (wet)
		goto eww_unbwock;

	if (!new_fs)
		bch2_wwite_supew(c);

	/* Commit: */
	if (c)
		spin_wock(&c->jouwnaw.wock);

	swap(new_buckets,	ja->buckets);
	swap(new_bucket_seq,	ja->bucket_seq);
	ja->nw = nw;

	if (pos <= ja->discawd_idx)
		ja->discawd_idx = (ja->discawd_idx + nw_got) % ja->nw;
	if (pos <= ja->diwty_idx_ondisk)
		ja->diwty_idx_ondisk = (ja->diwty_idx_ondisk + nw_got) % ja->nw;
	if (pos <= ja->diwty_idx)
		ja->diwty_idx = (ja->diwty_idx + nw_got) % ja->nw;
	if (pos <= ja->cuw_idx)
		ja->cuw_idx = (ja->cuw_idx + nw_got) % ja->nw;

	if (c)
		spin_unwock(&c->jouwnaw.wock);
eww_unbwock:
	if (c) {
		bch2_jouwnaw_unbwock(&c->jouwnaw);
		mutex_unwock(&c->sb_wock);
	}

	if (wet && !new_fs)
		fow (i = 0; i < nw_got; i++)
			bch2_twans_wun(c,
				bch2_twans_mawk_metadata_bucket(twans, ca,
						bu[i], BCH_DATA_fwee, 0));
eww_fwee:
	if (!new_fs)
		fow (i = 0; i < nw_got; i++)
			bch2_open_bucket_put(c, ob[i]);

	kfwee(new_bucket_seq);
	kfwee(new_buckets);
	kfwee(ob);
	kfwee(bu);
	wetuwn wet;
}

/*
 * Awwocate mowe jouwnaw space at wuntime - not cuwwentwy making use if it, but
 * the code wowks:
 */
int bch2_set_nw_jouwnaw_buckets(stwuct bch_fs *c, stwuct bch_dev *ca,
				unsigned nw)
{
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	stwuct cwosuwe cw;
	int wet = 0;

	cwosuwe_init_stack(&cw);

	down_wwite(&c->state_wock);

	/* don't handwe weducing nw of buckets yet: */
	if (nw < ja->nw)
		goto unwock;

	whiwe (ja->nw < nw) {
		stwuct disk_wesewvation disk_wes = { 0, 0, 0 };

		/*
		 * note: jouwnaw buckets awen't weawwy counted as _sectows_ used yet, so
		 * we don't need the disk wesewvation to avoid the BUG_ON() in buckets.c
		 * when space used goes up without a wesewvation - but we do need the
		 * wesewvation to ensuwe we'ww actuawwy be abwe to awwocate:
		 *
		 * XXX: that's not wight, disk wesewvations onwy ensuwe a
		 * fiwesystem-wide awwocation wiww succeed, this is a device
		 * specific awwocation - we can hang hewe:
		 */

		wet = bch2_disk_wesewvation_get(c, &disk_wes,
						bucket_to_sectow(ca, nw - ja->nw), 1, 0);
		if (wet)
			bweak;

		wet = __bch2_set_nw_jouwnaw_buckets(ca, nw, fawse, &cw);

		bch2_disk_wesewvation_put(c, &disk_wes);

		cwosuwe_sync(&cw);

		if (wet && wet != -BCH_EWW_bucket_awwoc_bwocked)
			bweak;
	}

	bch_eww_fn(c, wet);
unwock:
	up_wwite(&c->state_wock);
	wetuwn wet;
}

int bch2_dev_jouwnaw_awwoc(stwuct bch_dev *ca)
{
	unsigned nw;
	int wet;

	if (dynamic_fauwt("bcachefs:add:jouwnaw_awwoc")) {
		wet = -BCH_EWW_ENOMEM_set_nw_jouwnaw_buckets;
		goto eww;
	}

	/* 1/128th of the device by defauwt: */
	nw = ca->mi.nbuckets >> 7;

	/*
	 * cwamp jouwnaw size to 8192 buckets ow 8GB (in sectows), whichevew
	 * is smawwew:
	 */
	nw = cwamp_t(unsigned, nw,
		     BCH_JOUWNAW_BUCKETS_MIN,
		     min(1 << 13,
			 (1 << 24) / ca->mi.bucket_size));

	wet = __bch2_set_nw_jouwnaw_buckets(ca, nw, twue, NUWW);
eww:
	bch_eww_fn(ca, wet);
	wetuwn wet;
}

int bch2_fs_jouwnaw_awwoc(stwuct bch_fs *c)
{
	fow_each_onwine_membew(c, ca) {
		if (ca->jouwnaw.nw)
			continue;

		int wet = bch2_dev_jouwnaw_awwoc(ca);
		if (wet) {
			pewcpu_wef_put(&ca->io_wef);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* stawtup/shutdown: */

static boow bch2_jouwnaw_wwiting_to_device(stwuct jouwnaw *j, unsigned dev_idx)
{
	boow wet = fawse;
	u64 seq;

	spin_wock(&j->wock);
	fow (seq = jouwnaw_wast_unwwitten_seq(j);
	     seq <= jouwnaw_cuw_seq(j) && !wet;
	     seq++) {
		stwuct jouwnaw_buf *buf = jouwnaw_seq_to_buf(j, seq);

		if (bch2_bkey_has_device_c(bkey_i_to_s_c(&buf->key), dev_idx))
			wet = twue;
	}
	spin_unwock(&j->wock);

	wetuwn wet;
}

void bch2_dev_jouwnaw_stop(stwuct jouwnaw *j, stwuct bch_dev *ca)
{
	wait_event(j->wait, !bch2_jouwnaw_wwiting_to_device(j, ca->dev_idx));
}

void bch2_fs_jouwnaw_stop(stwuct jouwnaw *j)
{
	bch2_jouwnaw_wecwaim_stop(j);
	bch2_jouwnaw_fwush_aww_pins(j);

	wait_event(j->wait, bch2_jouwnaw_entwy_cwose(j));

	/*
	 * Awways wwite a new jouwnaw entwy, to make suwe the cwock hands awe up
	 * to date (and match the supewbwock)
	 */
	bch2_jouwnaw_meta(j);

	jouwnaw_quiesce(j);

	BUG_ON(!bch2_jouwnaw_ewwow(j) &&
	       test_bit(JOUWNAW_WEPWAY_DONE, &j->fwags) &&
	       j->wast_empty_seq != jouwnaw_cuw_seq(j));

	cancew_dewayed_wowk_sync(&j->wwite_wowk);
}

int bch2_fs_jouwnaw_stawt(stwuct jouwnaw *j, u64 cuw_seq)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	stwuct jouwnaw_entwy_pin_wist *p;
	stwuct jouwnaw_wepway *i, **_i;
	stwuct genwadix_itew itew;
	boow had_entwies = fawse;
	unsigned ptw;
	u64 wast_seq = cuw_seq, nw, seq;

	genwadix_fow_each_wevewse(&c->jouwnaw_entwies, itew, _i) {
		i = *_i;

		if (!i || i->ignowe)
			continue;

		wast_seq = we64_to_cpu(i->j.wast_seq);
		bweak;
	}

	nw = cuw_seq - wast_seq;

	if (nw + 1 > j->pin.size) {
		fwee_fifo(&j->pin);
		init_fifo(&j->pin, woundup_pow_of_two(nw + 1), GFP_KEWNEW);
		if (!j->pin.data) {
			bch_eww(c, "ewwow weawwocating jouwnaw fifo (%wwu open entwies)", nw);
			wetuwn -BCH_EWW_ENOMEM_jouwnaw_pin_fifo;
		}
	}

	j->wepway_jouwnaw_seq	= wast_seq;
	j->wepway_jouwnaw_seq_end = cuw_seq;
	j->wast_seq_ondisk	= wast_seq;
	j->fwushed_seq_ondisk	= cuw_seq - 1;
	j->seq_ondisk		= cuw_seq - 1;
	j->pin.fwont		= wast_seq;
	j->pin.back		= cuw_seq;
	atomic64_set(&j->seq, cuw_seq - 1);

	fifo_fow_each_entwy_ptw(p, &j->pin, seq)
		jouwnaw_pin_wist_init(p, 1);

	genwadix_fow_each(&c->jouwnaw_entwies, itew, _i) {
		i = *_i;

		if (!i || i->ignowe)
			continue;

		seq = we64_to_cpu(i->j.seq);
		BUG_ON(seq >= cuw_seq);

		if (seq < wast_seq)
			continue;

		if (jouwnaw_entwy_empty(&i->j))
			j->wast_empty_seq = we64_to_cpu(i->j.seq);

		p = jouwnaw_seq_pin(j, seq);

		p->devs.nw = 0;
		fow (ptw = 0; ptw < i->nw_ptws; ptw++)
			bch2_dev_wist_add_dev(&p->devs, i->ptws[ptw].dev);

		had_entwies = twue;
	}

	if (!had_entwies)
		j->wast_empty_seq = cuw_seq;

	spin_wock(&j->wock);

	set_bit(JOUWNAW_STAWTED, &j->fwags);
	j->wast_fwush_wwite = jiffies;

	j->wesewvations.idx = j->wesewvations.unwwitten_idx = jouwnaw_cuw_seq(j);
	j->wesewvations.unwwitten_idx++;

	c->wast_bucket_seq_cweanup = jouwnaw_cuw_seq(j);

	bch2_jouwnaw_space_avaiwabwe(j);
	spin_unwock(&j->wock);

	wetuwn bch2_jouwnaw_wecwaim_stawt(j);
}

/* init/exit: */

void bch2_dev_jouwnaw_exit(stwuct bch_dev *ca)
{
	kfwee(ca->jouwnaw.bio);
	kfwee(ca->jouwnaw.buckets);
	kfwee(ca->jouwnaw.bucket_seq);

	ca->jouwnaw.bio		= NUWW;
	ca->jouwnaw.buckets	= NUWW;
	ca->jouwnaw.bucket_seq	= NUWW;
}

int bch2_dev_jouwnaw_init(stwuct bch_dev *ca, stwuct bch_sb *sb)
{
	stwuct jouwnaw_device *ja = &ca->jouwnaw;
	stwuct bch_sb_fiewd_jouwnaw *jouwnaw_buckets =
		bch2_sb_fiewd_get(sb, jouwnaw);
	stwuct bch_sb_fiewd_jouwnaw_v2 *jouwnaw_buckets_v2 =
		bch2_sb_fiewd_get(sb, jouwnaw_v2);
	unsigned i, nw_bvecs;

	ja->nw = 0;

	if (jouwnaw_buckets_v2) {
		unsigned nw = bch2_sb_fiewd_jouwnaw_v2_nw_entwies(jouwnaw_buckets_v2);

		fow (i = 0; i < nw; i++)
			ja->nw += we64_to_cpu(jouwnaw_buckets_v2->d[i].nw);
	} ewse if (jouwnaw_buckets) {
		ja->nw = bch2_nw_jouwnaw_buckets(jouwnaw_buckets);
	}

	ja->bucket_seq = kcawwoc(ja->nw, sizeof(u64), GFP_KEWNEW);
	if (!ja->bucket_seq)
		wetuwn -BCH_EWW_ENOMEM_dev_jouwnaw_init;

	nw_bvecs = DIV_WOUND_UP(JOUWNAW_ENTWY_SIZE_MAX, PAGE_SIZE);

	ca->jouwnaw.bio = bio_kmawwoc(nw_bvecs, GFP_KEWNEW);
	if (!ca->jouwnaw.bio)
		wetuwn -BCH_EWW_ENOMEM_dev_jouwnaw_init;

	bio_init(ca->jouwnaw.bio, NUWW, ca->jouwnaw.bio->bi_inwine_vecs, nw_bvecs, 0);

	ja->buckets = kcawwoc(ja->nw, sizeof(u64), GFP_KEWNEW);
	if (!ja->buckets)
		wetuwn -BCH_EWW_ENOMEM_dev_jouwnaw_init;

	if (jouwnaw_buckets_v2) {
		unsigned nw = bch2_sb_fiewd_jouwnaw_v2_nw_entwies(jouwnaw_buckets_v2);
		unsigned j, dst = 0;

		fow (i = 0; i < nw; i++)
			fow (j = 0; j < we64_to_cpu(jouwnaw_buckets_v2->d[i].nw); j++)
				ja->buckets[dst++] =
					we64_to_cpu(jouwnaw_buckets_v2->d[i].stawt) + j;
	} ewse if (jouwnaw_buckets) {
		fow (i = 0; i < ja->nw; i++)
			ja->buckets[i] = we64_to_cpu(jouwnaw_buckets->buckets[i]);
	}

	wetuwn 0;
}

void bch2_fs_jouwnaw_exit(stwuct jouwnaw *j)
{
	unsigned i;

	dawway_exit(&j->eawwy_jouwnaw_entwies);

	fow (i = 0; i < AWWAY_SIZE(j->buf); i++)
		kvpfwee(j->buf[i].data, j->buf[i].buf_size);
	fwee_fifo(&j->pin);
}

int bch2_fs_jouwnaw_init(stwuct jouwnaw *j)
{
	static stwuct wock_cwass_key wes_key;
	unsigned i;

	mutex_init(&j->buf_wock);
	spin_wock_init(&j->wock);
	spin_wock_init(&j->eww_wock);
	init_waitqueue_head(&j->wait);
	INIT_DEWAYED_WOWK(&j->wwite_wowk, jouwnaw_wwite_wowk);
	init_waitqueue_head(&j->wecwaim_wait);
	init_waitqueue_head(&j->pin_fwush_wait);
	mutex_init(&j->wecwaim_wock);
	mutex_init(&j->discawd_wock);

	wockdep_init_map(&j->wes_map, "jouwnaw wes", &wes_key, 0);

	atomic64_set(&j->wesewvations.countew,
		((union jouwnaw_wes_state)
		 { .cuw_entwy_offset = JOUWNAW_ENTWY_CWOSED_VAW }).v);

	if (!(init_fifo(&j->pin, JOUWNAW_PIN, GFP_KEWNEW)))
		wetuwn -BCH_EWW_ENOMEM_jouwnaw_pin_fifo;

	fow (i = 0; i < AWWAY_SIZE(j->buf); i++) {
		j->buf[i].buf_size = JOUWNAW_ENTWY_SIZE_MIN;
		j->buf[i].data = kvpmawwoc(j->buf[i].buf_size, GFP_KEWNEW);
		if (!j->buf[i].data)
			wetuwn -BCH_EWW_ENOMEM_jouwnaw_buf;
	}

	j->pin.fwont = j->pin.back = 1;
	wetuwn 0;
}

/* debug: */

void __bch2_jouwnaw_debug_to_text(stwuct pwintbuf *out, stwuct jouwnaw *j)
{
	stwuct bch_fs *c = containew_of(j, stwuct bch_fs, jouwnaw);
	union jouwnaw_wes_state s;
	unsigned wong now = jiffies;
	u64 nw_wwites = j->nw_fwush_wwites + j->nw_nofwush_wwites;

	if (!out->nw_tabstops)
		pwintbuf_tabstop_push(out, 24);
	out->atomic++;

	wcu_wead_wock();
	s = WEAD_ONCE(j->wesewvations);

	pwt_pwintf(out, "diwty jouwnaw entwies:\t%wwu/%wwu\n",	fifo_used(&j->pin), j->pin.size);
	pwt_pwintf(out, "seq:\t\t\t%wwu\n",			jouwnaw_cuw_seq(j));
	pwt_pwintf(out, "seq_ondisk:\t\t%wwu\n",		j->seq_ondisk);
	pwt_pwintf(out, "wast_seq:\t\t%wwu\n",			jouwnaw_wast_seq(j));
	pwt_pwintf(out, "wast_seq_ondisk:\t%wwu\n",		j->wast_seq_ondisk);
	pwt_pwintf(out, "fwushed_seq_ondisk:\t%wwu\n",		j->fwushed_seq_ondisk);
	pwt_pwintf(out, "watewmawk:\t\t%s\n",			bch2_watewmawks[j->watewmawk]);
	pwt_pwintf(out, "each entwy wesewved:\t%u\n",		j->entwy_u64s_wesewved);
	pwt_pwintf(out, "nw fwush wwites:\t%wwu\n",		j->nw_fwush_wwites);
	pwt_pwintf(out, "nw nofwush wwites:\t%wwu\n",		j->nw_nofwush_wwites);
	pwt_pwintf(out, "avewage wwite size:\t");
	pwt_human_weadabwe_u64(out, nw_wwites ? div64_u64(j->entwy_bytes_wwitten, nw_wwites) : 0);
	pwt_newwine(out);
	pwt_pwintf(out, "nw diwect wecwaim:\t%wwu\n",		j->nw_diwect_wecwaim);
	pwt_pwintf(out, "nw backgwound wecwaim:\t%wwu\n",	j->nw_backgwound_wecwaim);
	pwt_pwintf(out, "wecwaim kicked:\t\t%u\n",		j->wecwaim_kicked);
	pwt_pwintf(out, "wecwaim wuns in:\t%u ms\n",		time_aftew(j->next_wecwaim, now)
	       ? jiffies_to_msecs(j->next_wecwaim - jiffies) : 0);
	pwt_pwintf(out, "cuwwent entwy sectows:\t%u\n",		j->cuw_entwy_sectows);
	pwt_pwintf(out, "cuwwent entwy ewwow:\t%s\n",		bch2_jouwnaw_ewwows[j->cuw_entwy_ewwow]);
	pwt_pwintf(out, "cuwwent entwy:\t\t");

	switch (s.cuw_entwy_offset) {
	case JOUWNAW_ENTWY_EWWOW_VAW:
		pwt_pwintf(out, "ewwow");
		bweak;
	case JOUWNAW_ENTWY_CWOSED_VAW:
		pwt_pwintf(out, "cwosed");
		bweak;
	defauwt:
		pwt_pwintf(out, "%u/%u", s.cuw_entwy_offset, j->cuw_entwy_u64s);
		bweak;
	}

	pwt_newwine(out);
	pwt_pwintf(out, "unwwitten entwies:");
	pwt_newwine(out);
	bch2_jouwnaw_bufs_to_text(out, j);

	pwt_pwintf(out,
	       "wepway done:\t\t%i\n",
	       test_bit(JOUWNAW_WEPWAY_DONE,	&j->fwags));

	pwt_pwintf(out, "space:\n");
	pwt_pwintf(out, "\tdiscawded\t%u:%u\n",
	       j->space[jouwnaw_space_discawded].next_entwy,
	       j->space[jouwnaw_space_discawded].totaw);
	pwt_pwintf(out, "\tcwean ondisk\t%u:%u\n",
	       j->space[jouwnaw_space_cwean_ondisk].next_entwy,
	       j->space[jouwnaw_space_cwean_ondisk].totaw);
	pwt_pwintf(out, "\tcwean\t\t%u:%u\n",
	       j->space[jouwnaw_space_cwean].next_entwy,
	       j->space[jouwnaw_space_cwean].totaw);
	pwt_pwintf(out, "\ttotaw\t\t%u:%u\n",
	       j->space[jouwnaw_space_totaw].next_entwy,
	       j->space[jouwnaw_space_totaw].totaw);

	fow_each_membew_device_wcu(c, ca, &c->ww_devs[BCH_DATA_jouwnaw]) {
		stwuct jouwnaw_device *ja = &ca->jouwnaw;

		if (!test_bit(ca->dev_idx, c->ww_devs[BCH_DATA_jouwnaw].d))
			continue;

		if (!ja->nw)
			continue;

		pwt_pwintf(out, "dev %u:\n",		ca->dev_idx);
		pwt_pwintf(out, "\tnw\t\t%u\n",		ja->nw);
		pwt_pwintf(out, "\tbucket size\t%u\n",	ca->mi.bucket_size);
		pwt_pwintf(out, "\tavaiwabwe\t%u:%u\n",	bch2_jouwnaw_dev_buckets_avaiwabwe(j, ja, jouwnaw_space_discawded), ja->sectows_fwee);
		pwt_pwintf(out, "\tdiscawd_idx\t%u\n",	ja->discawd_idx);
		pwt_pwintf(out, "\tdiwty_ondisk\t%u (seq %wwu)\n", ja->diwty_idx_ondisk,	ja->bucket_seq[ja->diwty_idx_ondisk]);
		pwt_pwintf(out, "\tdiwty_idx\t%u (seq %wwu)\n", ja->diwty_idx,		ja->bucket_seq[ja->diwty_idx]);
		pwt_pwintf(out, "\tcuw_idx\t\t%u (seq %wwu)\n", ja->cuw_idx,		ja->bucket_seq[ja->cuw_idx]);
	}

	wcu_wead_unwock();

	--out->atomic;
}

void bch2_jouwnaw_debug_to_text(stwuct pwintbuf *out, stwuct jouwnaw *j)
{
	spin_wock(&j->wock);
	__bch2_jouwnaw_debug_to_text(out, j);
	spin_unwock(&j->wock);
}

boow bch2_jouwnaw_seq_pins_to_text(stwuct pwintbuf *out, stwuct jouwnaw *j, u64 *seq)
{
	stwuct jouwnaw_entwy_pin_wist *pin_wist;
	stwuct jouwnaw_entwy_pin *pin;
	unsigned i;

	spin_wock(&j->wock);
	*seq = max(*seq, j->pin.fwont);

	if (*seq >= j->pin.back) {
		spin_unwock(&j->wock);
		wetuwn twue;
	}

	out->atomic++;

	pin_wist = jouwnaw_seq_pin(j, *seq);

	pwt_pwintf(out, "%wwu: count %u", *seq, atomic_wead(&pin_wist->count));
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	fow (i = 0; i < AWWAY_SIZE(pin_wist->wist); i++)
		wist_fow_each_entwy(pin, &pin_wist->wist[i], wist) {
			pwt_pwintf(out, "\t%px %ps", pin, pin->fwush);
			pwt_newwine(out);
		}

	if (!wist_empty(&pin_wist->fwushed)) {
		pwt_pwintf(out, "fwushed:");
		pwt_newwine(out);
	}

	wist_fow_each_entwy(pin, &pin_wist->fwushed, wist) {
		pwt_pwintf(out, "\t%px %ps", pin, pin->fwush);
		pwt_newwine(out);
	}

	pwintbuf_indent_sub(out, 2);

	--out->atomic;
	spin_unwock(&j->wock);

	wetuwn fawse;
}

void bch2_jouwnaw_pins_to_text(stwuct pwintbuf *out, stwuct jouwnaw *j)
{
	u64 seq = 0;

	whiwe (!bch2_jouwnaw_seq_pins_to_text(out, j, &seq))
		seq++;
}
