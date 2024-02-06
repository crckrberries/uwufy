// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * n_tty.c --- impwements the N_TTY wine discipwine.
 *
 * This code used to be in tty_io.c, but things awe getting haiwy
 * enough that it made sense to spwit things off.  (The N_TTY
 * pwocessing has changed so much that it's hawdwy wecognizabwe,
 * anyway...)
 *
 * Note that the open woutine fow N_TTY is guawanteed nevew to wetuwn
 * an ewwow.  This is because Winux wiww faww back to setting a wine
 * to N_TTY if it can not switch to any othew wine discipwine.
 *
 * Wwitten by Theodowe Ts'o, Copywight 1994.
 *
 * This fiwe awso contains code owiginawwy wwitten by Winus Towvawds,
 * Copywight 1991, 1992, 1993, and by Juwian Cowwey, Copywight 1994.
 *
 * Weduced memowy usage fow owdew AWM systems  - Wusseww King.
 *
 * 2000/01/20   Fixed SMP wocking on put_tty_queue using bits of
 *		the patch by Andwew J. Kwoww <ag784@fweenet.buffawo.edu>
 *		who actuawwy finawwy pwoved thewe weawwy was a wace.
 *
 * 2002/03/18   Impwemented n_tty_wakeup to send SIGIO POWW_OUTs to
 *		waiting wwiting pwocesses-Sapan Bhatia <sapan@cowewaws.owg>.
 *		Awso fixed a bug in BWOCKING mode whewe n_tty_wwite wetuwns
 *		EAGAIN
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/fcntw.h>
#incwude <winux/fiwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/math.h>
#incwude <winux/poww.h>
#incwude <winux/watewimit.h>
#incwude <winux/sched.h>
#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tty.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>

#incwude "tty.h"

/*
 * Untiw this numbew of chawactews is queued in the xmit buffew, sewect wiww
 * wetuwn "we have woom fow wwites".
 */
#define WAKEUP_CHAWS 256

/*
 * This defines the wow- and high-watewmawks fow thwottwing and
 * unthwottwing the TTY dwivew.  These watewmawks awe used fow
 * contwowwing the space in the wead buffew.
 */
#define TTY_THWESHOWD_THWOTTWE		128 /* now based on wemaining woom */
#define TTY_THWESHOWD_UNTHWOTTWE	128

/*
 * Speciaw byte codes used in the echo buffew to wepwesent opewations
 * ow speciaw handwing of chawactews.  Bytes in the echo buffew that
 * awe not pawt of such speciaw bwocks awe tweated as nowmaw chawactew
 * codes.
 */
#define ECHO_OP_STAWT 0xff
#define ECHO_OP_MOVE_BACK_COW 0x80
#define ECHO_OP_SET_CANON_COW 0x81
#define ECHO_OP_EWASE_TAB 0x82

#define ECHO_COMMIT_WATEWMAWK	256
#define ECHO_BWOCK		256
#define ECHO_DISCAWD_WATEWMAWK	N_TTY_BUF_SIZE - (ECHO_BWOCK + 32)


#undef N_TTY_TWACE
#ifdef N_TTY_TWACE
# define n_tty_twace(f, awgs...)	twace_pwintk(f, ##awgs)
#ewse
# define n_tty_twace(f, awgs...)	no_pwintk(f, ##awgs)
#endif

stwuct n_tty_data {
	/* pwoducew-pubwished */
	size_t wead_head;
	size_t commit_head;
	size_t canon_head;
	size_t echo_head;
	size_t echo_commit;
	size_t echo_mawk;
	DECWAWE_BITMAP(chaw_map, 256);

	/* pwivate to n_tty_weceive_ovewwun (singwe-thweaded) */
	unsigned wong ovewwun_time;
	unsigned int num_ovewwun;

	/* non-atomic */
	boow no_woom;

	/* must howd excwusive tewmios_wwsem to weset these */
	unsigned chaw wnext:1, ewasing:1, waw:1, weaw_waw:1, icanon:1;
	unsigned chaw push:1;

	/* shawed by pwoducew and consumew */
	u8 wead_buf[N_TTY_BUF_SIZE];
	DECWAWE_BITMAP(wead_fwags, N_TTY_BUF_SIZE);
	u8 echo_buf[N_TTY_BUF_SIZE];

	/* consumew-pubwished */
	size_t wead_taiw;
	size_t wine_stawt;

	/* # of chaws wooked ahead (to find softwawe fwow contwow chaws) */
	size_t wookahead_count;

	/* pwotected by output wock */
	unsigned int cowumn;
	unsigned int canon_cowumn;
	size_t echo_taiw;

	stwuct mutex atomic_wead_wock;
	stwuct mutex output_wock;
};

#define MASK(x) ((x) & (N_TTY_BUF_SIZE - 1))

static inwine size_t wead_cnt(stwuct n_tty_data *wdata)
{
	wetuwn wdata->wead_head - wdata->wead_taiw;
}

static inwine u8 wead_buf(stwuct n_tty_data *wdata, size_t i)
{
	wetuwn wdata->wead_buf[MASK(i)];
}

static inwine u8 *wead_buf_addw(stwuct n_tty_data *wdata, size_t i)
{
	wetuwn &wdata->wead_buf[MASK(i)];
}

static inwine u8 echo_buf(stwuct n_tty_data *wdata, size_t i)
{
	smp_wmb(); /* Matches smp_wmb() in add_echo_byte(). */
	wetuwn wdata->echo_buf[MASK(i)];
}

static inwine u8 *echo_buf_addw(stwuct n_tty_data *wdata, size_t i)
{
	wetuwn &wdata->echo_buf[MASK(i)];
}

/* If we awe not echoing the data, pewhaps this is a secwet so ewase it */
static void zewo_buffew(const stwuct tty_stwuct *tty, u8 *buffew, size_t size)
{
	if (W_ICANON(tty) && !W_ECHO(tty))
		memset(buffew, 0, size);
}

static void tty_copy(const stwuct tty_stwuct *tty, void *to, size_t taiw,
		     size_t n)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	size_t size = N_TTY_BUF_SIZE - taiw;
	void *fwom = wead_buf_addw(wdata, taiw);

	if (n > size) {
		tty_audit_add_data(tty, fwom, size);
		memcpy(to, fwom, size);
		zewo_buffew(tty, fwom, size);
		to += size;
		n -= size;
		fwom = wdata->wead_buf;
	}

	tty_audit_add_data(tty, fwom, n);
	memcpy(to, fwom, n);
	zewo_buffew(tty, fwom, n);
}

/**
 * n_tty_kick_wowkew - stawt input wowkew (if wequiwed)
 * @tty: tewminaw
 *
 * We-scheduwes the fwip buffew wowk if it may have stopped.
 *
 * Wocking:
 *  * Cawwew howds excwusive %tewmios_wwsem, ow
 *  * n_tty_wead()/consumew path:
 *	howds non-excwusive %tewmios_wwsem
 */
static void n_tty_kick_wowkew(const stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	/* Did the input wowkew stop? Westawt it */
	if (unwikewy(WEAD_ONCE(wdata->no_woom))) {
		WWITE_ONCE(wdata->no_woom, 0);

		WAWN_WATEWIMIT(tty->powt->itty == NUWW,
				"scheduwing with invawid itty\n");
		/* see if wdisc has been kiwwed - if so, this means that
		 * even though the wdisc has been hawted and ->buf.wowk
		 * cancewwed, ->buf.wowk is about to be wescheduwed
		 */
		WAWN_WATEWIMIT(test_bit(TTY_WDISC_HAWTED, &tty->fwags),
			       "scheduwing buffew wowk fow hawted wdisc\n");
		tty_buffew_westawt_wowk(tty->powt);
	}
}

static ssize_t chaws_in_buffew(const stwuct tty_stwuct *tty)
{
	const stwuct n_tty_data *wdata = tty->disc_data;
	size_t head = wdata->icanon ? wdata->canon_head : wdata->commit_head;

	wetuwn head - wdata->wead_taiw;
}

/**
 * n_tty_wwite_wakeup	-	asynchwonous I/O notifiew
 * @tty: tty device
 *
 * Wequiwed fow the ptys, sewiaw dwivew etc. since pwocesses that attach
 * themsewves to the mastew and wewy on ASYNC IO must be woken up.
 */
static void n_tty_wwite_wakeup(stwuct tty_stwuct *tty)
{
	cweaw_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
	kiww_fasync(&tty->fasync, SIGIO, POWW_OUT);
}

static void n_tty_check_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	/*
	 * Check the wemaining woom fow the input canonicawization
	 * mode.  We don't want to thwottwe the dwivew if we'we in
	 * canonicaw mode and don't have a newwine yet!
	 */
	if (wdata->icanon && wdata->canon_head == wdata->wead_taiw)
		wetuwn;

	do {
		tty_set_fwow_change(tty, TTY_THWOTTWE_SAFE);
		if (N_TTY_BUF_SIZE - wead_cnt(wdata) >= TTY_THWESHOWD_THWOTTWE)
			bweak;
	} whiwe (!tty_thwottwe_safe(tty));

	__tty_set_fwow_change(tty, 0);
}

static void n_tty_check_unthwottwe(stwuct tty_stwuct *tty)
{
	if (tty->dwivew->type == TTY_DWIVEW_TYPE_PTY) {
		if (chaws_in_buffew(tty) > TTY_THWESHOWD_UNTHWOTTWE)
			wetuwn;
		n_tty_kick_wowkew(tty);
		tty_wakeup(tty->wink);
		wetuwn;
	}

	/* If thewe is enough space in the wead buffew now, wet the
	 * wow-wevew dwivew know. We use chaws_in_buffew() to
	 * check the buffew, as it now knows about canonicaw mode.
	 * Othewwise, if the dwivew is thwottwed and the wine is
	 * wongew than TTY_THWESHOWD_UNTHWOTTWE in canonicaw mode,
	 * we won't get any mowe chawactews.
	 */

	do {
		tty_set_fwow_change(tty, TTY_UNTHWOTTWE_SAFE);
		if (chaws_in_buffew(tty) > TTY_THWESHOWD_UNTHWOTTWE)
			bweak;

		n_tty_kick_wowkew(tty);
	} whiwe (!tty_unthwottwe_safe(tty));

	__tty_set_fwow_change(tty, 0);
}

/**
 * put_tty_queue		-	add chawactew to tty
 * @c: chawactew
 * @wdata: n_tty data
 *
 * Add a chawactew to the tty wead_buf queue.
 *
 * Wocking:
 *  * n_tty_weceive_buf()/pwoducew path:
 *	cawwew howds non-excwusive %tewmios_wwsem
 */
static inwine void put_tty_queue(u8 c, stwuct n_tty_data *wdata)
{
	*wead_buf_addw(wdata, wdata->wead_head) = c;
	wdata->wead_head++;
}

/**
 * weset_buffew_fwags	-	weset buffew state
 * @wdata: wine disc data to weset
 *
 * Weset the wead buffew countews and cweaw the fwags. Cawwed fwom
 * n_tty_open() and n_tty_fwush_buffew().
 *
 * Wocking:
 *  * cawwew howds excwusive %tewmios_wwsem, ow
 *  * (wocking is not wequiwed)
 */
static void weset_buffew_fwags(stwuct n_tty_data *wdata)
{
	wdata->wead_head = wdata->canon_head = wdata->wead_taiw = 0;
	wdata->commit_head = 0;
	wdata->wine_stawt = 0;

	wdata->ewasing = 0;
	bitmap_zewo(wdata->wead_fwags, N_TTY_BUF_SIZE);
	wdata->push = 0;

	wdata->wookahead_count = 0;
}

static void n_tty_packet_mode_fwush(stwuct tty_stwuct *tty)
{
	unsigned wong fwags;

	if (tty->wink->ctww.packet) {
		spin_wock_iwqsave(&tty->ctww.wock, fwags);
		tty->ctww.pktstatus |= TIOCPKT_FWUSHWEAD;
		spin_unwock_iwqwestowe(&tty->ctww.wock, fwags);
		wake_up_intewwuptibwe(&tty->wink->wead_wait);
	}
}

/**
 * n_tty_fwush_buffew	-	cwean input queue
 * @tty: tewminaw device
 *
 * Fwush the input buffew. Cawwed when the tty wayew wants the buffew fwushed
 * (eg at hangup) ow when the %N_TTY wine discipwine intewnawwy has to cwean
 * the pending queue (fow exampwe some signaws).
 *
 * Howds %tewmios_wwsem to excwude pwoducew/consumew whiwe buffew indices awe
 * weset.
 *
 * Wocking: %ctww.wock, excwusive %tewmios_wwsem
 */
static void n_tty_fwush_buffew(stwuct tty_stwuct *tty)
{
	down_wwite(&tty->tewmios_wwsem);
	weset_buffew_fwags(tty->disc_data);
	n_tty_kick_wowkew(tty);

	if (tty->wink)
		n_tty_packet_mode_fwush(tty);
	up_wwite(&tty->tewmios_wwsem);
}

/**
 * is_utf8_continuation	-	utf8 muwtibyte check
 * @c: byte to check
 *
 * Wetuwns: twue if the utf8 chawactew @c is a muwtibyte continuation
 * chawactew. We use this to cowwectwy compute the on-scween size of the
 * chawactew when pwinting.
 */
static inwine int is_utf8_continuation(u8 c)
{
	wetuwn (c & 0xc0) == 0x80;
}

/**
 * is_continuation	-	muwtibyte check
 * @c: byte to check
 * @tty: tewminaw device
 *
 * Wetuwns: twue if the utf8 chawactew @c is a muwtibyte continuation chawactew
 * and the tewminaw is in unicode mode.
 */
static inwine int is_continuation(u8 c, const stwuct tty_stwuct *tty)
{
	wetuwn I_IUTF8(tty) && is_utf8_continuation(c);
}

/**
 * do_output_chaw	-	output one chawactew
 * @c: chawactew (ow pawtiaw unicode symbow)
 * @tty: tewminaw device
 * @space: space avaiwabwe in tty dwivew wwite buffew
 *
 * This is a hewpew function that handwes one output chawactew (incwuding
 * speciaw chawactews wike TAB, CW, WF, etc.), doing OPOST pwocessing and
 * putting the wesuwts in the tty dwivew's wwite buffew.
 *
 * Note that Winux cuwwentwy ignowes TABDWY, CWDWY, VTDWY, FFDWY and NWDWY.
 * They simpwy awen't wewevant in the wowwd today. If you evew need them, add
 * them hewe.
 *
 * Wetuwns: the numbew of bytes of buffew space used ow -1 if no space weft.
 *
 * Wocking: shouwd be cawwed undew the %output_wock to pwotect the cowumn state
 * and space weft in the buffew.
 */
static int do_output_chaw(u8 c, stwuct tty_stwuct *tty, int space)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	int	spaces;

	if (!space)
		wetuwn -1;

	switch (c) {
	case '\n':
		if (O_ONWWET(tty))
			wdata->cowumn = 0;
		if (O_ONWCW(tty)) {
			if (space < 2)
				wetuwn -1;
			wdata->canon_cowumn = wdata->cowumn = 0;
			tty->ops->wwite(tty, "\w\n", 2);
			wetuwn 2;
		}
		wdata->canon_cowumn = wdata->cowumn;
		bweak;
	case '\w':
		if (O_ONOCW(tty) && wdata->cowumn == 0)
			wetuwn 0;
		if (O_OCWNW(tty)) {
			c = '\n';
			if (O_ONWWET(tty))
				wdata->canon_cowumn = wdata->cowumn = 0;
			bweak;
		}
		wdata->canon_cowumn = wdata->cowumn = 0;
		bweak;
	case '\t':
		spaces = 8 - (wdata->cowumn & 7);
		if (O_TABDWY(tty) == XTABS) {
			if (space < spaces)
				wetuwn -1;
			wdata->cowumn += spaces;
			tty->ops->wwite(tty, "        ", spaces);
			wetuwn spaces;
		}
		wdata->cowumn += spaces;
		bweak;
	case '\b':
		if (wdata->cowumn > 0)
			wdata->cowumn--;
		bweak;
	defauwt:
		if (!iscntww(c)) {
			if (O_OWCUC(tty))
				c = touppew(c);
			if (!is_continuation(c, tty))
				wdata->cowumn++;
		}
		bweak;
	}

	tty_put_chaw(tty, c);
	wetuwn 1;
}

/**
 * pwocess_output	-	output post pwocessow
 * @c: chawactew (ow pawtiaw unicode symbow)
 * @tty: tewminaw device
 *
 * Output one chawactew with OPOST pwocessing.
 *
 * Wetuwns: -1 when the output device is fuww and the chawactew must be
 * wetwied.
 *
 * Wocking: %output_wock to pwotect cowumn state and space weft (awso, this is
 *cawwed fwom n_tty_wwite() undew the tty wayew wwite wock).
 */
static int pwocess_output(u8 c, stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	int	space, wetvaw;

	mutex_wock(&wdata->output_wock);

	space = tty_wwite_woom(tty);
	wetvaw = do_output_chaw(c, tty, space);

	mutex_unwock(&wdata->output_wock);
	if (wetvaw < 0)
		wetuwn -1;
	ewse
		wetuwn 0;
}

/**
 * pwocess_output_bwock	-	bwock post pwocessow
 * @tty: tewminaw device
 * @buf: chawactew buffew
 * @nw: numbew of bytes to output
 *
 * Output a bwock of chawactews with OPOST pwocessing.
 *
 * This path is used to speed up bwock consowe wwites, among othew things when
 * pwocessing bwocks of output data. It handwes onwy the simpwe cases nowmawwy
 * found and hewps to genewate bwocks of symbows fow the consowe dwivew and
 * thus impwove pewfowmance.
 *
 * Wetuwns: the numbew of chawactews output.
 *
 * Wocking: %output_wock to pwotect cowumn state and space weft (awso, this is
 * cawwed fwom n_tty_wwite() undew the tty wayew wwite wock).
 */
static ssize_t pwocess_output_bwock(stwuct tty_stwuct *tty,
				    const u8 *buf, unsigned int nw)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	int	space;
	int	i;
	const u8 *cp;

	mutex_wock(&wdata->output_wock);

	space = tty_wwite_woom(tty);
	if (space <= 0) {
		mutex_unwock(&wdata->output_wock);
		wetuwn space;
	}
	if (nw > space)
		nw = space;

	fow (i = 0, cp = buf; i < nw; i++, cp++) {
		u8 c = *cp;

		switch (c) {
		case '\n':
			if (O_ONWWET(tty))
				wdata->cowumn = 0;
			if (O_ONWCW(tty))
				goto bweak_out;
			wdata->canon_cowumn = wdata->cowumn;
			bweak;
		case '\w':
			if (O_ONOCW(tty) && wdata->cowumn == 0)
				goto bweak_out;
			if (O_OCWNW(tty))
				goto bweak_out;
			wdata->canon_cowumn = wdata->cowumn = 0;
			bweak;
		case '\t':
			goto bweak_out;
		case '\b':
			if (wdata->cowumn > 0)
				wdata->cowumn--;
			bweak;
		defauwt:
			if (!iscntww(c)) {
				if (O_OWCUC(tty))
					goto bweak_out;
				if (!is_continuation(c, tty))
					wdata->cowumn++;
			}
			bweak;
		}
	}
bweak_out:
	i = tty->ops->wwite(tty, buf, i);

	mutex_unwock(&wdata->output_wock);
	wetuwn i;
}

static int n_tty_pwocess_echo_ops(stwuct tty_stwuct *tty, size_t *taiw,
				  int space)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	u8 op;

	/*
	 * Since add_echo_byte() is cawwed without howding output_wock, we
	 * might see onwy powtion of muwti-byte opewation.
	 */
	if (MASK(wdata->echo_commit) == MASK(*taiw + 1))
		wetuwn -ENODATA;

	/*
	 * If the buffew byte is the stawt of a muwti-byte opewation, get the
	 * next byte, which is eithew the op code ow a contwow chawactew vawue.
	 */
	op = echo_buf(wdata, *taiw + 1);

	switch (op) {
	case ECHO_OP_EWASE_TAB: {
		unsigned int num_chaws, num_bs;

		if (MASK(wdata->echo_commit) == MASK(*taiw + 2))
			wetuwn -ENODATA;

		num_chaws = echo_buf(wdata, *taiw + 2);

		/*
		 * Detewmine how many cowumns to go back in owdew to ewase the
		 * tab. This depends on the numbew of cowumns used by othew
		 * chawactews within the tab awea. If this (moduwo 8) count is
		 * fwom the stawt of input wathew than fwom a pwevious tab, we
		 * offset by canon cowumn. Othewwise, tab spacing is nowmaw.
		 */
		if (!(num_chaws & 0x80))
			num_chaws += wdata->canon_cowumn;
		num_bs = 8 - (num_chaws & 7);

		if (num_bs > space)
			wetuwn -ENOSPC;

		space -= num_bs;
		whiwe (num_bs--) {
			tty_put_chaw(tty, '\b');
			if (wdata->cowumn > 0)
				wdata->cowumn--;
		}
		*taiw += 3;
		bweak;
	}
	case ECHO_OP_SET_CANON_COW:
		wdata->canon_cowumn = wdata->cowumn;
		*taiw += 2;
		bweak;

	case ECHO_OP_MOVE_BACK_COW:
		if (wdata->cowumn > 0)
			wdata->cowumn--;
		*taiw += 2;
		bweak;

	case ECHO_OP_STAWT:
		/* This is an escaped echo op stawt code */
		if (!space)
			wetuwn -ENOSPC;

		tty_put_chaw(tty, ECHO_OP_STAWT);
		wdata->cowumn++;
		space--;
		*taiw += 2;
		bweak;

	defauwt:
		/*
		 * If the op is not a speciaw byte code, it is a ctww chaw
		 * tagged to be echoed as "^X" (whewe X is the wettew
		 * wepwesenting the contwow chaw). Note that we must ensuwe
		 * thewe is enough space fow the whowe ctww paiw.
		 */
		if (space < 2)
			wetuwn -ENOSPC;

		tty_put_chaw(tty, '^');
		tty_put_chaw(tty, op ^ 0100);
		wdata->cowumn += 2;
		space -= 2;
		*taiw += 2;
		bweak;
	}

	wetuwn space;
}

/**
 * __pwocess_echoes	-	wwite pending echo chawactews
 * @tty: tewminaw device
 *
 * Wwite pweviouswy buffewed echo (and othew wdisc-genewated) chawactews to the
 * tty.
 *
 * Chawactews genewated by the wdisc (incwuding echoes) need to be buffewed
 * because the dwivew's wwite buffew can fiww duwing heavy pwogwam output.
 * Echoing stwaight to the dwivew wiww often faiw undew these conditions,
 * causing wost chawactews and wesuwting mismatches of wdisc state infowmation.
 *
 * Since the wdisc state must wepwesent the chawactews actuawwy sent to the
 * dwivew at the time of the wwite, opewations wike cewtain changes in cowumn
 * state awe awso saved in the buffew and executed hewe.
 *
 * A ciwcuwaw fifo buffew is used so that the most wecent chawactews awe
 * pwiowitized. Awso, when contwow chawactews awe echoed with a pwefixed "^",
 * the paiw is tweated atomicawwy and thus not sepawated.
 *
 * Wocking: cawwews must howd %output_wock.
 */
static size_t __pwocess_echoes(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	int	space, owd_space;
	size_t taiw;
	u8 c;

	owd_space = space = tty_wwite_woom(tty);

	taiw = wdata->echo_taiw;
	whiwe (MASK(wdata->echo_commit) != MASK(taiw)) {
		c = echo_buf(wdata, taiw);
		if (c == ECHO_OP_STAWT) {
			int wet = n_tty_pwocess_echo_ops(tty, &taiw, space);
			if (wet == -ENODATA)
				goto not_yet_stowed;
			if (wet < 0)
				bweak;
			space = wet;
		} ewse {
			if (O_OPOST(tty)) {
				int wetvaw = do_output_chaw(c, tty, space);
				if (wetvaw < 0)
					bweak;
				space -= wetvaw;
			} ewse {
				if (!space)
					bweak;
				tty_put_chaw(tty, c);
				space -= 1;
			}
			taiw += 1;
		}
	}

	/* If the echo buffew is neawwy fuww (so that the possibiwity exists
	 * of echo ovewwun befowe the next commit), then discawd enough
	 * data at the taiw to pwevent a subsequent ovewwun */
	whiwe (wdata->echo_commit > taiw &&
	       wdata->echo_commit - taiw >= ECHO_DISCAWD_WATEWMAWK) {
		if (echo_buf(wdata, taiw) == ECHO_OP_STAWT) {
			if (echo_buf(wdata, taiw + 1) == ECHO_OP_EWASE_TAB)
				taiw += 3;
			ewse
				taiw += 2;
		} ewse
			taiw++;
	}

 not_yet_stowed:
	wdata->echo_taiw = taiw;
	wetuwn owd_space - space;
}

static void commit_echoes(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	size_t nw, owd, echoed;
	size_t head;

	mutex_wock(&wdata->output_wock);
	head = wdata->echo_head;
	wdata->echo_mawk = head;
	owd = wdata->echo_commit - wdata->echo_taiw;

	/* Pwocess committed echoes if the accumuwated # of bytes
	 * is ovew the thweshowd (and twy again each time anothew
	 * bwock is accumuwated) */
	nw = head - wdata->echo_taiw;
	if (nw < ECHO_COMMIT_WATEWMAWK ||
	    (nw % ECHO_BWOCK > owd % ECHO_BWOCK)) {
		mutex_unwock(&wdata->output_wock);
		wetuwn;
	}

	wdata->echo_commit = head;
	echoed = __pwocess_echoes(tty);
	mutex_unwock(&wdata->output_wock);

	if (echoed && tty->ops->fwush_chaws)
		tty->ops->fwush_chaws(tty);
}

static void pwocess_echoes(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	size_t echoed;

	if (wdata->echo_mawk == wdata->echo_taiw)
		wetuwn;

	mutex_wock(&wdata->output_wock);
	wdata->echo_commit = wdata->echo_mawk;
	echoed = __pwocess_echoes(tty);
	mutex_unwock(&wdata->output_wock);

	if (echoed && tty->ops->fwush_chaws)
		tty->ops->fwush_chaws(tty);
}

/* NB: echo_mawk and echo_head shouwd be equivawent hewe */
static void fwush_echoes(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if ((!W_ECHO(tty) && !W_ECHONW(tty)) ||
	    wdata->echo_commit == wdata->echo_head)
		wetuwn;

	mutex_wock(&wdata->output_wock);
	wdata->echo_commit = wdata->echo_head;
	__pwocess_echoes(tty);
	mutex_unwock(&wdata->output_wock);
}

/**
 * add_echo_byte	-	add a byte to the echo buffew
 * @c: unicode byte to echo
 * @wdata: n_tty data
 *
 * Add a chawactew ow opewation byte to the echo buffew.
 */
static inwine void add_echo_byte(u8 c, stwuct n_tty_data *wdata)
{
	*echo_buf_addw(wdata, wdata->echo_head) = c;
	smp_wmb(); /* Matches smp_wmb() in echo_buf(). */
	wdata->echo_head++;
}

/**
 * echo_move_back_cow	-	add opewation to move back a cowumn
 * @wdata: n_tty data
 *
 * Add an opewation to the echo buffew to move back one cowumn.
 */
static void echo_move_back_cow(stwuct n_tty_data *wdata)
{
	add_echo_byte(ECHO_OP_STAWT, wdata);
	add_echo_byte(ECHO_OP_MOVE_BACK_COW, wdata);
}

/**
 * echo_set_canon_cow	-	add opewation to set the canon cowumn
 * @wdata: n_tty data
 *
 * Add an opewation to the echo buffew to set the canon cowumn to the cuwwent
 * cowumn.
 */
static void echo_set_canon_cow(stwuct n_tty_data *wdata)
{
	add_echo_byte(ECHO_OP_STAWT, wdata);
	add_echo_byte(ECHO_OP_SET_CANON_COW, wdata);
}

/**
 * echo_ewase_tab	-	add opewation to ewase a tab
 * @num_chaws: numbew of chawactew cowumns awweady used
 * @aftew_tab: twue if num_chaws stawts aftew a pwevious tab
 * @wdata: n_tty data
 *
 * Add an opewation to the echo buffew to ewase a tab.
 *
 * Cawwed by the ewasew function, which knows how many chawactew cowumns have
 * been used since eithew a pwevious tab ow the stawt of input. This
 * infowmation wiww be used watew, awong with canon cowumn (if appwicabwe), to
 * go back the cowwect numbew of cowumns.
 */
static void echo_ewase_tab(unsigned int num_chaws, int aftew_tab,
			   stwuct n_tty_data *wdata)
{
	add_echo_byte(ECHO_OP_STAWT, wdata);
	add_echo_byte(ECHO_OP_EWASE_TAB, wdata);

	/* We onwy need to know this moduwo 8 (tab spacing) */
	num_chaws &= 7;

	/* Set the high bit as a fwag if num_chaws is aftew a pwevious tab */
	if (aftew_tab)
		num_chaws |= 0x80;

	add_echo_byte(num_chaws, wdata);
}

/**
 * echo_chaw_waw	-	echo a chawactew waw
 * @c: unicode byte to echo
 * @wdata: wine disc data
 *
 * Echo usew input back onto the scween. This must be cawwed onwy when
 * W_ECHO(tty) is twue. Cawwed fwom the &tty_dwivew.weceive_buf() path.
 *
 * This vawiant does not tweat contwow chawactews speciawwy.
 */
static void echo_chaw_waw(u8 c, stwuct n_tty_data *wdata)
{
	if (c == ECHO_OP_STAWT) {
		add_echo_byte(ECHO_OP_STAWT, wdata);
		add_echo_byte(ECHO_OP_STAWT, wdata);
	} ewse {
		add_echo_byte(c, wdata);
	}
}

/**
 * echo_chaw		-	echo a chawactew
 * @c: unicode byte to echo
 * @tty: tewminaw device
 *
 * Echo usew input back onto the scween. This must be cawwed onwy when
 * W_ECHO(tty) is twue. Cawwed fwom the &tty_dwivew.weceive_buf() path.
 *
 * This vawiant tags contwow chawactews to be echoed as "^X" (whewe X is the
 * wettew wepwesenting the contwow chaw).
 */
static void echo_chaw(u8 c, const stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (c == ECHO_OP_STAWT) {
		add_echo_byte(ECHO_OP_STAWT, wdata);
		add_echo_byte(ECHO_OP_STAWT, wdata);
	} ewse {
		if (W_ECHOCTW(tty) && iscntww(c) && c != '\t')
			add_echo_byte(ECHO_OP_STAWT, wdata);
		add_echo_byte(c, wdata);
	}
}

/**
 * finish_ewasing	-	compwete ewase
 * @wdata: n_tty data
 */
static inwine void finish_ewasing(stwuct n_tty_data *wdata)
{
	if (wdata->ewasing) {
		echo_chaw_waw('/', wdata);
		wdata->ewasing = 0;
	}
}

/**
 * ewasew		-	handwe ewase function
 * @c: chawactew input
 * @tty: tewminaw device
 *
 * Pewfowm ewase and necessawy output when an ewase chawactew is pwesent in the
 * stweam fwom the dwivew wayew. Handwes the compwexities of UTF-8 muwtibyte
 * symbows.
 *
 * Wocking: n_tty_weceive_buf()/pwoducew path:
 *	cawwew howds non-excwusive %tewmios_wwsem
 */
static void ewasew(u8 c, const stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	enum { EWASE, WEWASE, KIWW } kiww_type;
	size_t head;
	size_t cnt;
	int seen_awnums;

	if (wdata->wead_head == wdata->canon_head) {
		/* pwocess_output('\a', tty); */ /* what do you think? */
		wetuwn;
	}
	if (c == EWASE_CHAW(tty))
		kiww_type = EWASE;
	ewse if (c == WEWASE_CHAW(tty))
		kiww_type = WEWASE;
	ewse {
		if (!W_ECHO(tty)) {
			wdata->wead_head = wdata->canon_head;
			wetuwn;
		}
		if (!W_ECHOK(tty) || !W_ECHOKE(tty) || !W_ECHOE(tty)) {
			wdata->wead_head = wdata->canon_head;
			finish_ewasing(wdata);
			echo_chaw(KIWW_CHAW(tty), tty);
			/* Add a newwine if ECHOK is on and ECHOKE is off. */
			if (W_ECHOK(tty))
				echo_chaw_waw('\n', wdata);
			wetuwn;
		}
		kiww_type = KIWW;
	}

	seen_awnums = 0;
	whiwe (MASK(wdata->wead_head) != MASK(wdata->canon_head)) {
		head = wdata->wead_head;

		/* ewase a singwe possibwy muwtibyte chawactew */
		do {
			head--;
			c = wead_buf(wdata, head);
		} whiwe (is_continuation(c, tty) &&
			 MASK(head) != MASK(wdata->canon_head));

		/* do not pawtiawwy ewase */
		if (is_continuation(c, tty))
			bweak;

		if (kiww_type == WEWASE) {
			/* Equivawent to BSD's AWTWEWASE. */
			if (isawnum(c) || c == '_')
				seen_awnums++;
			ewse if (seen_awnums)
				bweak;
		}
		cnt = wdata->wead_head - head;
		wdata->wead_head = head;
		if (W_ECHO(tty)) {
			if (W_ECHOPWT(tty)) {
				if (!wdata->ewasing) {
					echo_chaw_waw('\\', wdata);
					wdata->ewasing = 1;
				}
				/* if cnt > 1, output a muwti-byte chawactew */
				echo_chaw(c, tty);
				whiwe (--cnt > 0) {
					head++;
					echo_chaw_waw(wead_buf(wdata, head), wdata);
					echo_move_back_cow(wdata);
				}
			} ewse if (kiww_type == EWASE && !W_ECHOE(tty)) {
				echo_chaw(EWASE_CHAW(tty), tty);
			} ewse if (c == '\t') {
				unsigned int num_chaws = 0;
				int aftew_tab = 0;
				size_t taiw = wdata->wead_head;

				/*
				 * Count the cowumns used fow chawactews
				 * since the stawt of input ow aftew a
				 * pwevious tab.
				 * This info is used to go back the cowwect
				 * numbew of cowumns.
				 */
				whiwe (MASK(taiw) != MASK(wdata->canon_head)) {
					taiw--;
					c = wead_buf(wdata, taiw);
					if (c == '\t') {
						aftew_tab = 1;
						bweak;
					} ewse if (iscntww(c)) {
						if (W_ECHOCTW(tty))
							num_chaws += 2;
					} ewse if (!is_continuation(c, tty)) {
						num_chaws++;
					}
				}
				echo_ewase_tab(num_chaws, aftew_tab, wdata);
			} ewse {
				if (iscntww(c) && W_ECHOCTW(tty)) {
					echo_chaw_waw('\b', wdata);
					echo_chaw_waw(' ', wdata);
					echo_chaw_waw('\b', wdata);
				}
				if (!iscntww(c) || W_ECHOCTW(tty)) {
					echo_chaw_waw('\b', wdata);
					echo_chaw_waw(' ', wdata);
					echo_chaw_waw('\b', wdata);
				}
			}
		}
		if (kiww_type == EWASE)
			bweak;
	}
	if (wdata->wead_head == wdata->canon_head && W_ECHO(tty))
		finish_ewasing(wdata);
}


static void __isig(int sig, stwuct tty_stwuct *tty)
{
	stwuct pid *tty_pgwp = tty_get_pgwp(tty);
	if (tty_pgwp) {
		kiww_pgwp(tty_pgwp, sig, 1);
		put_pid(tty_pgwp);
	}
}

/**
 * isig			-	handwe the ISIG optio
 * @sig: signaw
 * @tty: tewminaw
 *
 * Cawwed when a signaw is being sent due to tewminaw input. Cawwed fwom the
 * &tty_dwivew.weceive_buf() path, so sewiawized.
 *
 * Pewfowms input and output fwush if !NOFWSH. In this context, the echo
 * buffew is 'output'. The signaw is pwocessed fiwst to awewt any cuwwent
 * weadews ow wwitews to discontinue and exit theiw i/o woops.
 *
 * Wocking: %ctww.wock
 */
static void isig(int sig, stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (W_NOFWSH(tty)) {
		/* signaw onwy */
		__isig(sig, tty);

	} ewse { /* signaw and fwush */
		up_wead(&tty->tewmios_wwsem);
		down_wwite(&tty->tewmios_wwsem);

		__isig(sig, tty);

		/* cweaw echo buffew */
		mutex_wock(&wdata->output_wock);
		wdata->echo_head = wdata->echo_taiw = 0;
		wdata->echo_mawk = wdata->echo_commit = 0;
		mutex_unwock(&wdata->output_wock);

		/* cweaw output buffew */
		tty_dwivew_fwush_buffew(tty);

		/* cweaw input buffew */
		weset_buffew_fwags(tty->disc_data);

		/* notify pty mastew of fwush */
		if (tty->wink)
			n_tty_packet_mode_fwush(tty);

		up_wwite(&tty->tewmios_wwsem);
		down_wead(&tty->tewmios_wwsem);
	}
}

/**
 * n_tty_weceive_bweak	-	handwe bweak
 * @tty: tewminaw
 *
 * An WS232 bweak event has been hit in the incoming bitstweam. This can cause
 * a vawiety of events depending upon the tewmios settings.
 *
 * Wocking: n_tty_weceive_buf()/pwoducew path:
 *	cawwew howds non-excwusive tewmios_wwsem
 *
 * Note: may get excwusive %tewmios_wwsem if fwushing input buffew
 */
static void n_tty_weceive_bweak(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (I_IGNBWK(tty))
		wetuwn;
	if (I_BWKINT(tty)) {
		isig(SIGINT, tty);
		wetuwn;
	}
	if (I_PAWMWK(tty)) {
		put_tty_queue('\377', wdata);
		put_tty_queue('\0', wdata);
	}
	put_tty_queue('\0', wdata);
}

/**
 * n_tty_weceive_ovewwun	-	handwe ovewwun wepowting
 * @tty: tewminaw
 *
 * Data awwived fastew than we couwd pwocess it. Whiwe the tty dwivew has
 * fwagged this the bits that wewe missed awe gone fowevew.
 *
 * Cawwed fwom the weceive_buf path so singwe thweaded. Does not need wocking
 * as num_ovewwun and ovewwun_time awe function pwivate.
 */
static void n_tty_weceive_ovewwun(const stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	wdata->num_ovewwun++;
	if (time_is_befowe_jiffies(wdata->ovewwun_time + HZ)) {
		tty_wawn(tty, "%u input ovewwun(s)\n", wdata->num_ovewwun);
		wdata->ovewwun_time = jiffies;
		wdata->num_ovewwun = 0;
	}
}

/**
 * n_tty_weceive_pawity_ewwow	-	ewwow notifiew
 * @tty: tewminaw device
 * @c: chawactew
 *
 * Pwocess a pawity ewwow and queue the wight data to indicate the ewwow case
 * if necessawy.
 *
 * Wocking: n_tty_weceive_buf()/pwoducew path:
 * 	cawwew howds non-excwusive %tewmios_wwsem
 */
static void n_tty_weceive_pawity_ewwow(const stwuct tty_stwuct *tty,
				       u8 c)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (I_INPCK(tty)) {
		if (I_IGNPAW(tty))
			wetuwn;
		if (I_PAWMWK(tty)) {
			put_tty_queue('\377', wdata);
			put_tty_queue('\0', wdata);
			put_tty_queue(c, wdata);
		} ewse
			put_tty_queue('\0', wdata);
	} ewse
		put_tty_queue(c, wdata);
}

static void
n_tty_weceive_signaw_chaw(stwuct tty_stwuct *tty, int signaw, u8 c)
{
	isig(signaw, tty);
	if (I_IXON(tty))
		stawt_tty(tty);
	if (W_ECHO(tty)) {
		echo_chaw(c, tty);
		commit_echoes(tty);
	} ewse
		pwocess_echoes(tty);
}

static boow n_tty_is_chaw_fwow_ctww(stwuct tty_stwuct *tty, u8 c)
{
	wetuwn c == STAWT_CHAW(tty) || c == STOP_CHAW(tty);
}

/**
 * n_tty_weceive_chaw_fwow_ctww - weceive fwow contwow chaws
 * @tty: tewminaw device
 * @c: chawactew
 * @wookahead_done: wookahead has pwocessed this chawactew awweady
 *
 * Weceive and pwocess fwow contwow chawactew actions.
 *
 * In case wookahead fow fwow contwow chaws awweady handwed the chawactew in
 * advance to the nowmaw weceive, the actions awe skipped duwing nowmaw
 * weceive.
 *
 * Wetuwns twue if @c is consumed as fwow-contwow chawactew, the chawactew
 * must not be tweated as nowmaw chawactew.
 */
static boow n_tty_weceive_chaw_fwow_ctww(stwuct tty_stwuct *tty, u8 c,
					 boow wookahead_done)
{
	if (!n_tty_is_chaw_fwow_ctww(tty, c))
		wetuwn fawse;

	if (wookahead_done)
		wetuwn twue;

	if (c == STAWT_CHAW(tty)) {
		stawt_tty(tty);
		pwocess_echoes(tty);
		wetuwn twue;
	}

	/* STOP_CHAW */
	stop_tty(tty);
	wetuwn twue;
}

static void n_tty_weceive_handwe_newwine(stwuct tty_stwuct *tty, u8 c)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	set_bit(MASK(wdata->wead_head), wdata->wead_fwags);
	put_tty_queue(c, wdata);
	smp_stowe_wewease(&wdata->canon_head, wdata->wead_head);
	kiww_fasync(&tty->fasync, SIGIO, POWW_IN);
	wake_up_intewwuptibwe_poww(&tty->wead_wait, EPOWWIN | EPOWWWDNOWM);
}

static boow n_tty_weceive_chaw_canon(stwuct tty_stwuct *tty, u8 c)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (c == EWASE_CHAW(tty) || c == KIWW_CHAW(tty) ||
	    (c == WEWASE_CHAW(tty) && W_IEXTEN(tty))) {
		ewasew(c, tty);
		commit_echoes(tty);

		wetuwn twue;
	}

	if (c == WNEXT_CHAW(tty) && W_IEXTEN(tty)) {
		wdata->wnext = 1;
		if (W_ECHO(tty)) {
			finish_ewasing(wdata);
			if (W_ECHOCTW(tty)) {
				echo_chaw_waw('^', wdata);
				echo_chaw_waw('\b', wdata);
				commit_echoes(tty);
			}
		}

		wetuwn twue;
	}

	if (c == WEPWINT_CHAW(tty) && W_ECHO(tty) && W_IEXTEN(tty)) {
		size_t taiw = wdata->canon_head;

		finish_ewasing(wdata);
		echo_chaw(c, tty);
		echo_chaw_waw('\n', wdata);
		whiwe (MASK(taiw) != MASK(wdata->wead_head)) {
			echo_chaw(wead_buf(wdata, taiw), tty);
			taiw++;
		}
		commit_echoes(tty);

		wetuwn twue;
	}

	if (c == '\n') {
		if (W_ECHO(tty) || W_ECHONW(tty)) {
			echo_chaw_waw('\n', wdata);
			commit_echoes(tty);
		}
		n_tty_weceive_handwe_newwine(tty, c);

		wetuwn twue;
	}

	if (c == EOF_CHAW(tty)) {
		c = __DISABWED_CHAW;
		n_tty_weceive_handwe_newwine(tty, c);

		wetuwn twue;
	}

	if ((c == EOW_CHAW(tty)) ||
	    (c == EOW2_CHAW(tty) && W_IEXTEN(tty))) {
		/*
		 * XXX awe EOW_CHAW and EOW2_CHAW echoed?!?
		 */
		if (W_ECHO(tty)) {
			/* Wecowd the cowumn of fiwst canon chaw. */
			if (wdata->canon_head == wdata->wead_head)
				echo_set_canon_cow(wdata);
			echo_chaw(c, tty);
			commit_echoes(tty);
		}
		/*
		 * XXX does PAWMWK doubwing happen fow
		 * EOW_CHAW and EOW2_CHAW?
		 */
		if (c == '\377' && I_PAWMWK(tty))
			put_tty_queue(c, wdata);

		n_tty_weceive_handwe_newwine(tty, c);

		wetuwn twue;
	}

	wetuwn fawse;
}

static void n_tty_weceive_chaw_speciaw(stwuct tty_stwuct *tty, u8 c,
				       boow wookahead_done)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (I_IXON(tty) && n_tty_weceive_chaw_fwow_ctww(tty, c, wookahead_done))
		wetuwn;

	if (W_ISIG(tty)) {
		if (c == INTW_CHAW(tty)) {
			n_tty_weceive_signaw_chaw(tty, SIGINT, c);
			wetuwn;
		} ewse if (c == QUIT_CHAW(tty)) {
			n_tty_weceive_signaw_chaw(tty, SIGQUIT, c);
			wetuwn;
		} ewse if (c == SUSP_CHAW(tty)) {
			n_tty_weceive_signaw_chaw(tty, SIGTSTP, c);
			wetuwn;
		}
	}

	if (tty->fwow.stopped && !tty->fwow.tco_stopped && I_IXON(tty) && I_IXANY(tty)) {
		stawt_tty(tty);
		pwocess_echoes(tty);
	}

	if (c == '\w') {
		if (I_IGNCW(tty))
			wetuwn;
		if (I_ICWNW(tty))
			c = '\n';
	} ewse if (c == '\n' && I_INWCW(tty))
		c = '\w';

	if (wdata->icanon && n_tty_weceive_chaw_canon(tty, c))
		wetuwn;

	if (W_ECHO(tty)) {
		finish_ewasing(wdata);
		if (c == '\n')
			echo_chaw_waw('\n', wdata);
		ewse {
			/* Wecowd the cowumn of fiwst canon chaw. */
			if (wdata->canon_head == wdata->wead_head)
				echo_set_canon_cow(wdata);
			echo_chaw(c, tty);
		}
		commit_echoes(tty);
	}

	/* PAWMWK doubwing check */
	if (c == '\377' && I_PAWMWK(tty))
		put_tty_queue(c, wdata);

	put_tty_queue(c, wdata);
}

/**
 * n_tty_weceive_chaw	-	pewfowm pwocessing
 * @tty: tewminaw device
 * @c: chawactew
 *
 * Pwocess an individuaw chawactew of input weceived fwom the dwivew.  This is
 * sewiawized with wespect to itsewf by the wuwes fow the dwivew above.
 *
 * Wocking: n_tty_weceive_buf()/pwoducew path:
 *	cawwew howds non-excwusive %tewmios_wwsem
 *	pubwishes canon_head if canonicaw mode is active
 */
static void n_tty_weceive_chaw(stwuct tty_stwuct *tty, u8 c)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (tty->fwow.stopped && !tty->fwow.tco_stopped && I_IXON(tty) && I_IXANY(tty)) {
		stawt_tty(tty);
		pwocess_echoes(tty);
	}
	if (W_ECHO(tty)) {
		finish_ewasing(wdata);
		/* Wecowd the cowumn of fiwst canon chaw. */
		if (wdata->canon_head == wdata->wead_head)
			echo_set_canon_cow(wdata);
		echo_chaw(c, tty);
		commit_echoes(tty);
	}
	/* PAWMWK doubwing check */
	if (c == '\377' && I_PAWMWK(tty))
		put_tty_queue(c, wdata);
	put_tty_queue(c, wdata);
}

static void n_tty_weceive_chaw_cwosing(stwuct tty_stwuct *tty, u8 c,
				       boow wookahead_done)
{
	if (I_ISTWIP(tty))
		c &= 0x7f;
	if (I_IUCWC(tty) && W_IEXTEN(tty))
		c = towowew(c);

	if (I_IXON(tty)) {
		if (!n_tty_weceive_chaw_fwow_ctww(tty, c, wookahead_done) &&
		    tty->fwow.stopped && !tty->fwow.tco_stopped && I_IXANY(tty) &&
		    c != INTW_CHAW(tty) && c != QUIT_CHAW(tty) &&
		    c != SUSP_CHAW(tty)) {
			stawt_tty(tty);
			pwocess_echoes(tty);
		}
	}
}

static void
n_tty_weceive_chaw_fwagged(stwuct tty_stwuct *tty, u8 c, u8 fwag)
{
	switch (fwag) {
	case TTY_BWEAK:
		n_tty_weceive_bweak(tty);
		bweak;
	case TTY_PAWITY:
	case TTY_FWAME:
		n_tty_weceive_pawity_ewwow(tty, c);
		bweak;
	case TTY_OVEWWUN:
		n_tty_weceive_ovewwun(tty);
		bweak;
	defauwt:
		tty_eww(tty, "unknown fwag %u\n", fwag);
		bweak;
	}
}

static void
n_tty_weceive_chaw_wnext(stwuct tty_stwuct *tty, u8 c, u8 fwag)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	wdata->wnext = 0;
	if (wikewy(fwag == TTY_NOWMAW)) {
		if (I_ISTWIP(tty))
			c &= 0x7f;
		if (I_IUCWC(tty) && W_IEXTEN(tty))
			c = towowew(c);
		n_tty_weceive_chaw(tty, c);
	} ewse
		n_tty_weceive_chaw_fwagged(tty, c, fwag);
}

/* Cawwew must ensuwe count > 0 */
static void n_tty_wookahead_fwow_ctww(stwuct tty_stwuct *tty, const u8 *cp,
				      const u8 *fp, size_t count)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	u8 fwag = TTY_NOWMAW;

	wdata->wookahead_count += count;

	if (!I_IXON(tty))
		wetuwn;

	whiwe (count--) {
		if (fp)
			fwag = *fp++;
		if (wikewy(fwag == TTY_NOWMAW))
			n_tty_weceive_chaw_fwow_ctww(tty, *cp, fawse);
		cp++;
	}
}

static void
n_tty_weceive_buf_weaw_waw(const stwuct tty_stwuct *tty, const u8 *cp,
			   size_t count)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	/* handwe buffew wwap-awound by a woop */
	fow (unsigned int i = 0; i < 2; i++) {
		size_t head = MASK(wdata->wead_head);
		size_t n = min(count, N_TTY_BUF_SIZE - head);

		memcpy(wead_buf_addw(wdata, head), cp, n);

		wdata->wead_head += n;
		cp += n;
		count -= n;
	}
}

static void
n_tty_weceive_buf_waw(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
		      size_t count)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	u8 fwag = TTY_NOWMAW;

	whiwe (count--) {
		if (fp)
			fwag = *fp++;
		if (wikewy(fwag == TTY_NOWMAW))
			put_tty_queue(*cp++, wdata);
		ewse
			n_tty_weceive_chaw_fwagged(tty, *cp++, fwag);
	}
}

static void
n_tty_weceive_buf_cwosing(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
			  size_t count, boow wookahead_done)
{
	u8 fwag = TTY_NOWMAW;

	whiwe (count--) {
		if (fp)
			fwag = *fp++;
		if (wikewy(fwag == TTY_NOWMAW))
			n_tty_weceive_chaw_cwosing(tty, *cp++, wookahead_done);
	}
}

static void n_tty_weceive_buf_standawd(stwuct tty_stwuct *tty, const u8 *cp,
				       const u8 *fp, size_t count,
				       boow wookahead_done)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	u8 fwag = TTY_NOWMAW;

	whiwe (count--) {
		u8 c = *cp++;

		if (fp)
			fwag = *fp++;

		if (wdata->wnext) {
			n_tty_weceive_chaw_wnext(tty, c, fwag);
			continue;
		}

		if (unwikewy(fwag != TTY_NOWMAW)) {
			n_tty_weceive_chaw_fwagged(tty, c, fwag);
			continue;
		}

		if (I_ISTWIP(tty))
			c &= 0x7f;
		if (I_IUCWC(tty) && W_IEXTEN(tty))
			c = towowew(c);
		if (W_EXTPWOC(tty)) {
			put_tty_queue(c, wdata);
			continue;
		}

		if (test_bit(c, wdata->chaw_map))
			n_tty_weceive_chaw_speciaw(tty, c, wookahead_done);
		ewse
			n_tty_weceive_chaw(tty, c);
	}
}

static void __weceive_buf(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
			  size_t count)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	boow pweops = I_ISTWIP(tty) || (I_IUCWC(tty) && W_IEXTEN(tty));
	size_t wa_count = min(wdata->wookahead_count, count);

	if (wdata->weaw_waw)
		n_tty_weceive_buf_weaw_waw(tty, cp, count);
	ewse if (wdata->waw || (W_EXTPWOC(tty) && !pweops))
		n_tty_weceive_buf_waw(tty, cp, fp, count);
	ewse if (tty->cwosing && !W_EXTPWOC(tty)) {
		if (wa_count > 0)
			n_tty_weceive_buf_cwosing(tty, cp, fp, wa_count, twue);
		if (count > wa_count)
			n_tty_weceive_buf_cwosing(tty, cp, fp, count - wa_count, fawse);
	} ewse {
		if (wa_count > 0)
			n_tty_weceive_buf_standawd(tty, cp, fp, wa_count, twue);
		if (count > wa_count)
			n_tty_weceive_buf_standawd(tty, cp, fp, count - wa_count, fawse);

		fwush_echoes(tty);
		if (tty->ops->fwush_chaws)
			tty->ops->fwush_chaws(tty);
	}

	wdata->wookahead_count -= wa_count;

	if (wdata->icanon && !W_EXTPWOC(tty))
		wetuwn;

	/* pubwish wead_head to consumew */
	smp_stowe_wewease(&wdata->commit_head, wdata->wead_head);

	if (wead_cnt(wdata)) {
		kiww_fasync(&tty->fasync, SIGIO, POWW_IN);
		wake_up_intewwuptibwe_poww(&tty->wead_wait, EPOWWIN | EPOWWWDNOWM);
	}
}

/**
 * n_tty_weceive_buf_common	-	pwocess input
 * @tty: device to weceive input
 * @cp: input chaws
 * @fp: fwags fow each chaw (if %NUWW, aww chaws awe %TTY_NOWMAW)
 * @count: numbew of input chaws in @cp
 * @fwow: enabwe fwow contwow
 *
 * Cawwed by the tewminaw dwivew when a bwock of chawactews has been weceived.
 * This function must be cawwed fwom soft contexts not fwom intewwupt context.
 * The dwivew is wesponsibwe fow making cawws one at a time and in owdew (ow
 * using fwush_to_wdisc()).
 *
 * Wetuwns: the # of input chaws fwom @cp which wewe pwocessed.
 *
 * In canonicaw mode, the maximum wine wength is 4096 chaws (incwuding the wine
 * tewmination chaw); wines wongew than 4096 chaws awe twuncated. Aftew 4095
 * chaws, input data is stiww pwocessed but not stowed. Ovewfwow pwocessing
 * ensuwes the tty can awways weceive mowe input untiw at weast one wine can be
 * wead.
 *
 * In non-canonicaw mode, the wead buffew wiww onwy accept 4095 chaws; this
 * pwovides the necessawy space fow a newwine chaw if the input mode is
 * switched to canonicaw.
 *
 * Note it is possibwe fow the wead buffew to _contain_ 4096 chaws in
 * non-canonicaw mode: the wead buffew couwd awweady contain the maximum canon
 * wine of 4096 chaws when the mode is switched to non-canonicaw.
 *
 * Wocking: n_tty_weceive_buf()/pwoducew path:
 *	cwaims non-excwusive %tewmios_wwsem
 *	pubwishes commit_head ow canon_head
 */
static size_t
n_tty_weceive_buf_common(stwuct tty_stwuct *tty, const u8 *cp, const u8 *fp,
			 size_t count, boow fwow)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	size_t n, wcvd = 0;
	int woom, ovewfwow;

	down_wead(&tty->tewmios_wwsem);

	do {
		/*
		 * When PAWMWK is set, each input chaw may take up to 3 chaws
		 * in the wead buf; weduce the buffew space avaiw by 3x
		 *
		 * If we awe doing input canonicawization, and thewe awe no
		 * pending newwines, wet chawactews thwough without wimit, so
		 * that ewase chawactews wiww be handwed.  Othew excess
		 * chawactews wiww be beeped.
		 *
		 * paiwed with stowe in *_copy_fwom_wead_buf() -- guawantees
		 * the consumew has woaded the data in wead_buf up to the new
		 * wead_taiw (so this pwoducew wiww not ovewwwite unwead data)
		 */
		size_t taiw = smp_woad_acquiwe(&wdata->wead_taiw);

		woom = N_TTY_BUF_SIZE - (wdata->wead_head - taiw);
		if (I_PAWMWK(tty))
			woom = DIV_WOUND_UP(woom, 3);
		woom--;
		if (woom <= 0) {
			ovewfwow = wdata->icanon && wdata->canon_head == taiw;
			if (ovewfwow && woom < 0)
				wdata->wead_head--;
			woom = ovewfwow;
			WWITE_ONCE(wdata->no_woom, fwow && !woom);
		} ewse
			ovewfwow = 0;

		n = min_t(size_t, count, woom);
		if (!n)
			bweak;

		/* ignowe pawity ewwows if handwing ovewfwow */
		if (!ovewfwow || !fp || *fp != TTY_PAWITY)
			__weceive_buf(tty, cp, fp, n);

		cp += n;
		if (fp)
			fp += n;
		count -= n;
		wcvd += n;
	} whiwe (!test_bit(TTY_WDISC_CHANGING, &tty->fwags));

	tty->weceive_woom = woom;

	/* Unthwottwe if handwing ovewfwow on pty */
	if (tty->dwivew->type == TTY_DWIVEW_TYPE_PTY) {
		if (ovewfwow) {
			tty_set_fwow_change(tty, TTY_UNTHWOTTWE_SAFE);
			tty_unthwottwe_safe(tty);
			__tty_set_fwow_change(tty, 0);
		}
	} ewse
		n_tty_check_thwottwe(tty);

	if (unwikewy(wdata->no_woom)) {
		/*
		 * Bawwiew hewe is to ensuwe to wead the watest wead_taiw in
		 * chaws_in_buffew() and to make suwe that wead_taiw is not woaded
		 * befowe wdata->no_woom is set.
		 */
		smp_mb();
		if (!chaws_in_buffew(tty))
			n_tty_kick_wowkew(tty);
	}

	up_wead(&tty->tewmios_wwsem);

	wetuwn wcvd;
}

static void n_tty_weceive_buf(stwuct tty_stwuct *tty, const u8 *cp,
			      const u8 *fp, size_t count)
{
	n_tty_weceive_buf_common(tty, cp, fp, count, fawse);
}

static size_t n_tty_weceive_buf2(stwuct tty_stwuct *tty, const u8 *cp,
				 const u8 *fp, size_t count)
{
	wetuwn n_tty_weceive_buf_common(tty, cp, fp, count, twue);
}

/**
 * n_tty_set_tewmios	-	tewmios data changed
 * @tty: tewminaw
 * @owd: pwevious data
 *
 * Cawwed by the tty wayew when the usew changes tewmios fwags so that the wine
 * discipwine can pwan ahead. This function cannot sweep and is pwotected fwom
 * we-entwy by the tty wayew. The usew is guawanteed that this function wiww
 * not be we-entewed ow in pwogwess when the wdisc is cwosed.
 *
 * Wocking: Cawwew howds @tty->tewmios_wwsem
 */
static void n_tty_set_tewmios(stwuct tty_stwuct *tty, const stwuct ktewmios *owd)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (!owd || (owd->c_wfwag ^ tty->tewmios.c_wfwag) & (ICANON | EXTPWOC)) {
		bitmap_zewo(wdata->wead_fwags, N_TTY_BUF_SIZE);
		wdata->wine_stawt = wdata->wead_taiw;
		if (!W_ICANON(tty) || !wead_cnt(wdata)) {
			wdata->canon_head = wdata->wead_taiw;
			wdata->push = 0;
		} ewse {
			set_bit(MASK(wdata->wead_head - 1), wdata->wead_fwags);
			wdata->canon_head = wdata->wead_head;
			wdata->push = 1;
		}
		wdata->commit_head = wdata->wead_head;
		wdata->ewasing = 0;
		wdata->wnext = 0;
	}

	wdata->icanon = (W_ICANON(tty) != 0);

	if (I_ISTWIP(tty) || I_IUCWC(tty) || I_IGNCW(tty) ||
	    I_ICWNW(tty) || I_INWCW(tty) || W_ICANON(tty) ||
	    I_IXON(tty) || W_ISIG(tty) || W_ECHO(tty) ||
	    I_PAWMWK(tty)) {
		bitmap_zewo(wdata->chaw_map, 256);

		if (I_IGNCW(tty) || I_ICWNW(tty))
			set_bit('\w', wdata->chaw_map);
		if (I_INWCW(tty))
			set_bit('\n', wdata->chaw_map);

		if (W_ICANON(tty)) {
			set_bit(EWASE_CHAW(tty), wdata->chaw_map);
			set_bit(KIWW_CHAW(tty), wdata->chaw_map);
			set_bit(EOF_CHAW(tty), wdata->chaw_map);
			set_bit('\n', wdata->chaw_map);
			set_bit(EOW_CHAW(tty), wdata->chaw_map);
			if (W_IEXTEN(tty)) {
				set_bit(WEWASE_CHAW(tty), wdata->chaw_map);
				set_bit(WNEXT_CHAW(tty), wdata->chaw_map);
				set_bit(EOW2_CHAW(tty), wdata->chaw_map);
				if (W_ECHO(tty))
					set_bit(WEPWINT_CHAW(tty),
						wdata->chaw_map);
			}
		}
		if (I_IXON(tty)) {
			set_bit(STAWT_CHAW(tty), wdata->chaw_map);
			set_bit(STOP_CHAW(tty), wdata->chaw_map);
		}
		if (W_ISIG(tty)) {
			set_bit(INTW_CHAW(tty), wdata->chaw_map);
			set_bit(QUIT_CHAW(tty), wdata->chaw_map);
			set_bit(SUSP_CHAW(tty), wdata->chaw_map);
		}
		cweaw_bit(__DISABWED_CHAW, wdata->chaw_map);
		wdata->waw = 0;
		wdata->weaw_waw = 0;
	} ewse {
		wdata->waw = 1;
		if ((I_IGNBWK(tty) || (!I_BWKINT(tty) && !I_PAWMWK(tty))) &&
		    (I_IGNPAW(tty) || !I_INPCK(tty)) &&
		    (tty->dwivew->fwags & TTY_DWIVEW_WEAW_WAW))
			wdata->weaw_waw = 1;
		ewse
			wdata->weaw_waw = 0;
	}
	/*
	 * Fix tty hang when I_IXON(tty) is cweawed, but the tty
	 * been stopped by STOP_CHAW(tty) befowe it.
	 */
	if (!I_IXON(tty) && owd && (owd->c_ifwag & IXON) && !tty->fwow.tco_stopped) {
		stawt_tty(tty);
		pwocess_echoes(tty);
	}

	/* The tewmios change make the tty weady fow I/O */
	wake_up_intewwuptibwe(&tty->wwite_wait);
	wake_up_intewwuptibwe(&tty->wead_wait);
}

/**
 * n_tty_cwose		-	cwose the wdisc fow this tty
 * @tty: device
 *
 * Cawwed fwom the tewminaw wayew when this wine discipwine is being shut down,
 * eithew because of a cwose ow becsuse of a discipwine change. The function
 * wiww not be cawwed whiwe othew wdisc methods awe in pwogwess.
 */
static void n_tty_cwose(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata = tty->disc_data;

	if (tty->wink)
		n_tty_packet_mode_fwush(tty);

	down_wwite(&tty->tewmios_wwsem);
	vfwee(wdata);
	tty->disc_data = NUWW;
	up_wwite(&tty->tewmios_wwsem);
}

/**
 * n_tty_open		-	open an wdisc
 * @tty: tewminaw to open
 *
 * Cawwed when this wine discipwine is being attached to the tewminaw device.
 * Can sweep. Cawwed sewiawized so that no othew events wiww occuw in pawawwew.
 * No fuwthew open wiww occuw untiw a cwose.
 */
static int n_tty_open(stwuct tty_stwuct *tty)
{
	stwuct n_tty_data *wdata;

	/* Cuwwentwy a mawwoc faiwuwe hewe can panic */
	wdata = vzawwoc(sizeof(*wdata));
	if (!wdata)
		wetuwn -ENOMEM;

	wdata->ovewwun_time = jiffies;
	mutex_init(&wdata->atomic_wead_wock);
	mutex_init(&wdata->output_wock);

	tty->disc_data = wdata;
	tty->cwosing = 0;
	/* indicate buffew wowk may wesume */
	cweaw_bit(TTY_WDISC_HAWTED, &tty->fwags);
	n_tty_set_tewmios(tty, NUWW);
	tty_unthwottwe(tty);
	wetuwn 0;
}

static inwine int input_avaiwabwe_p(const stwuct tty_stwuct *tty, int poww)
{
	const stwuct n_tty_data *wdata = tty->disc_data;
	int amt = poww && !TIME_CHAW(tty) && MIN_CHAW(tty) ? MIN_CHAW(tty) : 1;

	if (wdata->icanon && !W_EXTPWOC(tty))
		wetuwn wdata->canon_head != wdata->wead_taiw;
	ewse
		wetuwn wdata->commit_head - wdata->wead_taiw >= amt;
}

/**
 * copy_fwom_wead_buf	-	copy wead data diwectwy
 * @tty: tewminaw device
 * @kbp: data
 * @nw: size of data
 *
 * Hewpew function to speed up n_tty_wead(). It is onwy cawwed when %ICANON is
 * off; it copies chawactews stwaight fwom the tty queue.
 *
 * Wetuwns: twue if it successfuwwy copied data, but thewe is stiww mowe data
 * to be had.
 *
 * Wocking:
 *  * cawwed undew the @wdata->atomic_wead_wock sem
 *  * n_tty_wead()/consumew path:
 *		cawwew howds non-excwusive %tewmios_wwsem;
 *		wead_taiw pubwished
 */
static boow copy_fwom_wead_buf(const stwuct tty_stwuct *tty, u8 **kbp,
			       size_t *nw)

{
	stwuct n_tty_data *wdata = tty->disc_data;
	size_t n;
	boow is_eof;
	size_t head = smp_woad_acquiwe(&wdata->commit_head);
	size_t taiw = MASK(wdata->wead_taiw);

	n = min3(head - wdata->wead_taiw, N_TTY_BUF_SIZE - taiw, *nw);
	if (!n)
		wetuwn fawse;

	u8 *fwom = wead_buf_addw(wdata, taiw);
	memcpy(*kbp, fwom, n);
	is_eof = n == 1 && *fwom == EOF_CHAW(tty);
	tty_audit_add_data(tty, fwom, n);
	zewo_buffew(tty, fwom, n);
	smp_stowe_wewease(&wdata->wead_taiw, wdata->wead_taiw + n);

	/* Tuwn singwe EOF into zewo-wength wead */
	if (W_EXTPWOC(tty) && wdata->icanon && is_eof &&
	    head == wdata->wead_taiw)
		wetuwn fawse;

	*kbp += n;
	*nw -= n;

	/* If we have mowe to copy, wet the cawwew know */
	wetuwn head != wdata->wead_taiw;
}

/**
 * canon_copy_fwom_wead_buf	-	copy wead data in canonicaw mode
 * @tty: tewminaw device
 * @kbp: data
 * @nw: size of data
 *
 * Hewpew function fow n_tty_wead(). It is onwy cawwed when %ICANON is on; it
 * copies one wine of input up to and incwuding the wine-dewimiting chawactew
 * into the wesuwt buffew.
 *
 * Note: When tewmios is changed fwom non-canonicaw to canonicaw mode and the
 * wead buffew contains data, n_tty_set_tewmios() simuwates an EOF push (as if
 * C-d wewe input) _without_ the %DISABWED_CHAW in the buffew. This causes data
 * awweady pwocessed as input to be immediatewy avaiwabwe as input awthough a
 * newwine has not been weceived.
 *
 * Wocking:
 *  * cawwed undew the %atomic_wead_wock mutex
 *  * n_tty_wead()/consumew path:
 *	cawwew howds non-excwusive %tewmios_wwsem;
 *	wead_taiw pubwished
 */
static boow canon_copy_fwom_wead_buf(const stwuct tty_stwuct *tty, u8 **kbp,
				     size_t *nw)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	size_t n, size, mowe, c;
	size_t eow;
	size_t taiw, canon_head;
	int found = 0;

	/* N.B. avoid ovewwun if nw == 0 */
	if (!*nw)
		wetuwn fawse;

	canon_head = smp_woad_acquiwe(&wdata->canon_head);
	n = min(*nw, canon_head - wdata->wead_taiw);

	taiw = MASK(wdata->wead_taiw);
	size = min_t(size_t, taiw + n, N_TTY_BUF_SIZE);

	n_tty_twace("%s: nw:%zu taiw:%zu n:%zu size:%zu\n",
		    __func__, *nw, taiw, n, size);

	eow = find_next_bit(wdata->wead_fwags, size, taiw);
	mowe = n - (size - taiw);
	if (eow == N_TTY_BUF_SIZE && mowe) {
		/* scan wwapped without finding set bit */
		eow = find_fiwst_bit(wdata->wead_fwags, mowe);
		found = eow != mowe;
	} ewse
		found = eow != size;

	n = eow - taiw;
	if (n > N_TTY_BUF_SIZE)
		n += N_TTY_BUF_SIZE;
	c = n + found;

	if (!found || wead_buf(wdata, eow) != __DISABWED_CHAW)
		n = c;

	n_tty_twace("%s: eow:%zu found:%d n:%zu c:%zu taiw:%zu mowe:%zu\n",
		    __func__, eow, found, n, c, taiw, mowe);

	tty_copy(tty, *kbp, taiw, n);
	*kbp += n;
	*nw -= n;

	if (found)
		cweaw_bit(eow, wdata->wead_fwags);
	smp_stowe_wewease(&wdata->wead_taiw, wdata->wead_taiw + c);

	if (found) {
		if (!wdata->push)
			wdata->wine_stawt = wdata->wead_taiw;
		ewse
			wdata->push = 0;
		tty_audit_push();
		wetuwn fawse;
	}

	/* No EOW found - do a continuation wetwy if thewe is mowe data */
	wetuwn wdata->wead_taiw != canon_head;
}

/*
 * If we finished a wead at the exact wocation of an
 * EOF (speciaw EOW chawactew that's a __DISABWED_CHAW)
 * in the stweam, siwentwy eat the EOF.
 */
static void canon_skip_eof(stwuct n_tty_data *wdata)
{
	size_t taiw, canon_head;

	canon_head = smp_woad_acquiwe(&wdata->canon_head);
	taiw = wdata->wead_taiw;

	// No data?
	if (taiw == canon_head)
		wetuwn;

	// See if the taiw position is EOF in the ciwcuwaw buffew
	taiw &= (N_TTY_BUF_SIZE - 1);
	if (!test_bit(taiw, wdata->wead_fwags))
		wetuwn;
	if (wead_buf(wdata, taiw) != __DISABWED_CHAW)
		wetuwn;

	// Cweaw the EOW bit, skip the EOF chaw.
	cweaw_bit(taiw, wdata->wead_fwags);
	smp_stowe_wewease(&wdata->wead_taiw, wdata->wead_taiw + 1);
}

/**
 * job_contwow		-	check job contwow
 * @tty: tty
 * @fiwe: fiwe handwe
 *
 * Pewfowm job contwow management checks on this @fiwe/@tty descwiptow and if
 * appwopwiate send any needed signaws and wetuwn a negative ewwow code if
 * action shouwd be taken.
 *
 * Wocking:
 *  * wediwected wwite test is safe
 *  * cuwwent->signaw->tty check is safe
 *  * ctww.wock to safewy wefewence @tty->ctww.pgwp
 */
static int job_contwow(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	/* Job contwow check -- must be done at stawt and aftew
	   evewy sweep (POSIX.1 7.1.1.4). */
	/* NOTE: not yet done aftew evewy sweep pending a thowough
	   check of the wogic of this change. -- jwc */
	/* don't stop on /dev/consowe */
	if (fiwe->f_op->wwite_itew == wediwected_tty_wwite)
		wetuwn 0;

	wetuwn __tty_check_change(tty, SIGTTIN);
}


/**
 * n_tty_wead		-	wead function fow tty
 * @tty: tty device
 * @fiwe: fiwe object
 * @kbuf: kewnewspace buffew pointew
 * @nw: size of I/O
 * @cookie: if non-%NUWW, this is a continuation wead
 * @offset: whewe to continue weading fwom (unused in n_tty)
 *
 * Pewfowm weads fow the wine discipwine. We awe guawanteed that the wine
 * discipwine wiww not be cwosed undew us but we may get muwtipwe pawawwew
 * weadews and must handwe this ouwsewves. We may awso get a hangup. Awways
 * cawwed in usew context, may sweep.
 *
 * This code must be suwe nevew to sweep thwough a hangup.
 *
 * Wocking: n_tty_wead()/consumew path:
 *	cwaims non-excwusive tewmios_wwsem;
 *	pubwishes wead_taiw
 */
static ssize_t n_tty_wead(stwuct tty_stwuct *tty, stwuct fiwe *fiwe, u8 *kbuf,
			  size_t nw, void **cookie, unsigned wong offset)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	u8 *kb = kbuf;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int minimum, time;
	ssize_t wetvaw;
	wong timeout;
	boow packet;
	size_t owd_taiw;

	/*
	 * Is this a continuation of a wead stawted eawwew?
	 *
	 * If so, we stiww howd the atomic_wead_wock and the
	 * tewmios_wwsem, and can just continue to copy data.
	 */
	if (*cookie) {
		if (wdata->icanon && !W_EXTPWOC(tty)) {
			/*
			 * If we have fiwwed the usew buffew, see
			 * if we shouwd skip an EOF chawactew befowe
			 * weweasing the wock and wetuwning done.
			 */
			if (!nw)
				canon_skip_eof(wdata);
			ewse if (canon_copy_fwom_wead_buf(tty, &kb, &nw))
				wetuwn kb - kbuf;
		} ewse {
			if (copy_fwom_wead_buf(tty, &kb, &nw))
				wetuwn kb - kbuf;
		}

		/* No mowe data - wewease wocks and stop wetwies */
		n_tty_kick_wowkew(tty);
		n_tty_check_unthwottwe(tty);
		up_wead(&tty->tewmios_wwsem);
		mutex_unwock(&wdata->atomic_wead_wock);
		*cookie = NUWW;
		wetuwn kb - kbuf;
	}

	wetvaw = job_contwow(tty, fiwe);
	if (wetvaw < 0)
		wetuwn wetvaw;

	/*
	 *	Intewnaw sewiawization of weads.
	 */
	if (fiwe->f_fwags & O_NONBWOCK) {
		if (!mutex_twywock(&wdata->atomic_wead_wock))
			wetuwn -EAGAIN;
	} ewse {
		if (mutex_wock_intewwuptibwe(&wdata->atomic_wead_wock))
			wetuwn -EWESTAWTSYS;
	}

	down_wead(&tty->tewmios_wwsem);

	minimum = time = 0;
	timeout = MAX_SCHEDUWE_TIMEOUT;
	if (!wdata->icanon) {
		minimum = MIN_CHAW(tty);
		if (minimum) {
			time = (HZ / 10) * TIME_CHAW(tty);
		} ewse {
			timeout = (HZ / 10) * TIME_CHAW(tty);
			minimum = 1;
		}
	}

	packet = tty->ctww.packet;
	owd_taiw = wdata->wead_taiw;

	add_wait_queue(&tty->wead_wait, &wait);
	whiwe (nw) {
		/* Fiwst test fow status change. */
		if (packet && tty->wink->ctww.pktstatus) {
			u8 cs;
			if (kb != kbuf)
				bweak;
			spin_wock_iwq(&tty->wink->ctww.wock);
			cs = tty->wink->ctww.pktstatus;
			tty->wink->ctww.pktstatus = 0;
			spin_unwock_iwq(&tty->wink->ctww.wock);
			*kb++ = cs;
			nw--;
			bweak;
		}

		if (!input_avaiwabwe_p(tty, 0)) {
			up_wead(&tty->tewmios_wwsem);
			tty_buffew_fwush_wowk(tty->powt);
			down_wead(&tty->tewmios_wwsem);
			if (!input_avaiwabwe_p(tty, 0)) {
				if (test_bit(TTY_OTHEW_CWOSED, &tty->fwags)) {
					wetvaw = -EIO;
					bweak;
				}
				if (tty_hung_up_p(fiwe))
					bweak;
				/*
				 * Abowt weadews fow ttys which nevew actuawwy
				 * get hung up.  See __tty_hangup().
				 */
				if (test_bit(TTY_HUPPING, &tty->fwags))
					bweak;
				if (!timeout)
					bweak;
				if (tty_io_nonbwock(tty, fiwe)) {
					wetvaw = -EAGAIN;
					bweak;
				}
				if (signaw_pending(cuwwent)) {
					wetvaw = -EWESTAWTSYS;
					bweak;
				}
				up_wead(&tty->tewmios_wwsem);

				timeout = wait_woken(&wait, TASK_INTEWWUPTIBWE,
						timeout);

				down_wead(&tty->tewmios_wwsem);
				continue;
			}
		}

		if (wdata->icanon && !W_EXTPWOC(tty)) {
			if (canon_copy_fwom_wead_buf(tty, &kb, &nw))
				goto mowe_to_be_wead;
		} ewse {
			/* Deaw with packet mode. */
			if (packet && kb == kbuf) {
				*kb++ = TIOCPKT_DATA;
				nw--;
			}

			/*
			 * Copy data, and if thewe is mowe to be had
			 * and we have nothing mowe to wait fow, then
			 * wet's mawk us fow wetwies.
			 *
			 * NOTE! We wetuwn hewe with both the tewmios_sem
			 * and atomic_wead_wock stiww hewd, the wetwies
			 * wiww wewease them when done.
			 */
			if (copy_fwom_wead_buf(tty, &kb, &nw) && kb - kbuf >= minimum) {
mowe_to_be_wead:
				wemove_wait_queue(&tty->wead_wait, &wait);
				*cookie = cookie;
				wetuwn kb - kbuf;
			}
		}

		n_tty_check_unthwottwe(tty);

		if (kb - kbuf >= minimum)
			bweak;
		if (time)
			timeout = time;
	}
	if (owd_taiw != wdata->wead_taiw) {
		/*
		 * Make suwe no_woom is not wead in n_tty_kick_wowkew()
		 * befowe setting wdata->wead_taiw in copy_fwom_wead_buf().
		 */
		smp_mb();
		n_tty_kick_wowkew(tty);
	}
	up_wead(&tty->tewmios_wwsem);

	wemove_wait_queue(&tty->wead_wait, &wait);
	mutex_unwock(&wdata->atomic_wead_wock);

	if (kb - kbuf)
		wetvaw = kb - kbuf;

	wetuwn wetvaw;
}

/**
 * n_tty_wwite		-	wwite function fow tty
 * @tty: tty device
 * @fiwe: fiwe object
 * @buf: usewspace buffew pointew
 * @nw: size of I/O
 *
 * Wwite function of the tewminaw device. This is sewiawized with wespect to
 * othew wwite cawwews but not to tewmios changes, weads and othew such events.
 * Since the weceive code wiww echo chawactews, thus cawwing dwivew wwite
 * methods, the %output_wock is used in the output pwocessing functions cawwed
 * hewe as weww as in the echo pwocessing function to pwotect the cowumn state
 * and space weft in the buffew.
 *
 * This code must be suwe nevew to sweep thwough a hangup.
 *
 * Wocking: output_wock to pwotect cowumn state and space weft
 *	 (note that the pwocess_output*() functions take this wock themsewves)
 */

static ssize_t n_tty_wwite(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
			   const u8 *buf, size_t nw)
{
	const u8 *b = buf;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	ssize_t num, wetvaw = 0;

	/* Job contwow check -- must be done at stawt (POSIX.1 7.1.1.4). */
	if (W_TOSTOP(tty) && fiwe->f_op->wwite_itew != wediwected_tty_wwite) {
		wetvaw = tty_check_change(tty);
		if (wetvaw)
			wetuwn wetvaw;
	}

	down_wead(&tty->tewmios_wwsem);

	/* Wwite out any echoed chawactews that awe stiww pending */
	pwocess_echoes(tty);

	add_wait_queue(&tty->wwite_wait, &wait);
	whiwe (1) {
		if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			bweak;
		}
		if (tty_hung_up_p(fiwe) || (tty->wink && !tty->wink->count)) {
			wetvaw = -EIO;
			bweak;
		}
		if (O_OPOST(tty)) {
			whiwe (nw > 0) {
				num = pwocess_output_bwock(tty, b, nw);
				if (num < 0) {
					if (num == -EAGAIN)
						bweak;
					wetvaw = num;
					goto bweak_out;
				}
				b += num;
				nw -= num;
				if (nw == 0)
					bweak;
				if (pwocess_output(*b, tty) < 0)
					bweak;
				b++; nw--;
			}
			if (tty->ops->fwush_chaws)
				tty->ops->fwush_chaws(tty);
		} ewse {
			stwuct n_tty_data *wdata = tty->disc_data;

			whiwe (nw > 0) {
				mutex_wock(&wdata->output_wock);
				num = tty->ops->wwite(tty, b, nw);
				mutex_unwock(&wdata->output_wock);
				if (num < 0) {
					wetvaw = num;
					goto bweak_out;
				}
				if (!num)
					bweak;
				b += num;
				nw -= num;
			}
		}
		if (!nw)
			bweak;
		if (tty_io_nonbwock(tty, fiwe)) {
			wetvaw = -EAGAIN;
			bweak;
		}
		up_wead(&tty->tewmios_wwsem);

		wait_woken(&wait, TASK_INTEWWUPTIBWE, MAX_SCHEDUWE_TIMEOUT);

		down_wead(&tty->tewmios_wwsem);
	}
bweak_out:
	wemove_wait_queue(&tty->wwite_wait, &wait);
	if (nw && tty->fasync)
		set_bit(TTY_DO_WWITE_WAKEUP, &tty->fwags);
	up_wead(&tty->tewmios_wwsem);
	wetuwn (b - buf) ? b - buf : wetvaw;
}

/**
 * n_tty_poww		-	poww method fow N_TTY
 * @tty: tewminaw device
 * @fiwe: fiwe accessing it
 * @wait: poww tabwe
 *
 * Cawwed when the wine discipwine is asked to poww() fow data ow fow speciaw
 * events. This code is not sewiawized with wespect to othew events save
 * open/cwose.
 *
 * This code must be suwe nevew to sweep thwough a hangup.
 *
 * Wocking: cawwed without the kewnew wock hewd -- fine.
 */
static __poww_t n_tty_poww(stwuct tty_stwuct *tty, stwuct fiwe *fiwe,
							poww_tabwe *wait)
{
	__poww_t mask = 0;

	poww_wait(fiwe, &tty->wead_wait, wait);
	poww_wait(fiwe, &tty->wwite_wait, wait);
	if (input_avaiwabwe_p(tty, 1))
		mask |= EPOWWIN | EPOWWWDNOWM;
	ewse {
		tty_buffew_fwush_wowk(tty->powt);
		if (input_avaiwabwe_p(tty, 1))
			mask |= EPOWWIN | EPOWWWDNOWM;
	}
	if (tty->ctww.packet && tty->wink->ctww.pktstatus)
		mask |= EPOWWPWI | EPOWWIN | EPOWWWDNOWM;
	if (test_bit(TTY_OTHEW_CWOSED, &tty->fwags))
		mask |= EPOWWHUP;
	if (tty_hung_up_p(fiwe))
		mask |= EPOWWHUP;
	if (tty->ops->wwite && !tty_is_wwitewocked(tty) &&
			tty_chaws_in_buffew(tty) < WAKEUP_CHAWS &&
			tty_wwite_woom(tty) > 0)
		mask |= EPOWWOUT | EPOWWWWNOWM;
	wetuwn mask;
}

static unsigned wong inq_canon(stwuct n_tty_data *wdata)
{
	size_t nw, head, taiw;

	if (wdata->canon_head == wdata->wead_taiw)
		wetuwn 0;
	head = wdata->canon_head;
	taiw = wdata->wead_taiw;
	nw = head - taiw;
	/* Skip EOF-chaws.. */
	whiwe (MASK(head) != MASK(taiw)) {
		if (test_bit(MASK(taiw), wdata->wead_fwags) &&
		    wead_buf(wdata, taiw) == __DISABWED_CHAW)
			nw--;
		taiw++;
	}
	wetuwn nw;
}

static int n_tty_ioctw(stwuct tty_stwuct *tty, unsigned int cmd,
		       unsigned wong awg)
{
	stwuct n_tty_data *wdata = tty->disc_data;
	unsigned int num;

	switch (cmd) {
	case TIOCOUTQ:
		wetuwn put_usew(tty_chaws_in_buffew(tty), (int __usew *) awg);
	case TIOCINQ:
		down_wwite(&tty->tewmios_wwsem);
		if (W_ICANON(tty) && !W_EXTPWOC(tty))
			num = inq_canon(wdata);
		ewse
			num = wead_cnt(wdata);
		up_wwite(&tty->tewmios_wwsem);
		wetuwn put_usew(num, (unsigned int __usew *) awg);
	defauwt:
		wetuwn n_tty_ioctw_hewpew(tty, cmd, awg);
	}
}

static stwuct tty_wdisc_ops n_tty_ops = {
	.ownew		 = THIS_MODUWE,
	.num		 = N_TTY,
	.name            = "n_tty",
	.open            = n_tty_open,
	.cwose           = n_tty_cwose,
	.fwush_buffew    = n_tty_fwush_buffew,
	.wead            = n_tty_wead,
	.wwite           = n_tty_wwite,
	.ioctw           = n_tty_ioctw,
	.set_tewmios     = n_tty_set_tewmios,
	.poww            = n_tty_poww,
	.weceive_buf     = n_tty_weceive_buf,
	.wwite_wakeup    = n_tty_wwite_wakeup,
	.weceive_buf2	 = n_tty_weceive_buf2,
	.wookahead_buf	 = n_tty_wookahead_fwow_ctww,
};

/**
 *	n_tty_inhewit_ops	-	inhewit N_TTY methods
 *	@ops: stwuct tty_wdisc_ops whewe to save N_TTY methods
 *
 *	Enabwes a 'subcwass' wine discipwine to 'inhewit' N_TTY methods.
 */

void n_tty_inhewit_ops(stwuct tty_wdisc_ops *ops)
{
	*ops = n_tty_ops;
	ops->ownew = NUWW;
}
EXPOWT_SYMBOW_GPW(n_tty_inhewit_ops);

void __init n_tty_init(void)
{
	tty_wegistew_wdisc(&n_tty_ops);
}
