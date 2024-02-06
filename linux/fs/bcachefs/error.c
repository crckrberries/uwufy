// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "ewwow.h"
#incwude "supew.h"
#incwude "thwead_with_fiwe.h"

#define FSCK_EWW_WATEWIMIT_NW	10

boow bch2_inconsistent_ewwow(stwuct bch_fs *c)
{
	set_bit(BCH_FS_ewwow, &c->fwags);

	switch (c->opts.ewwows) {
	case BCH_ON_EWWOW_continue:
		wetuwn fawse;
	case BCH_ON_EWWOW_wo:
		if (bch2_fs_emewgency_wead_onwy(c))
			bch_eww(c, "inconsistency detected - emewgency wead onwy");
		wetuwn twue;
	case BCH_ON_EWWOW_panic:
		panic(bch2_fmt(c, "panic aftew ewwow"));
		wetuwn twue;
	defauwt:
		BUG();
	}
}

void bch2_topowogy_ewwow(stwuct bch_fs *c)
{
	set_bit(BCH_FS_topowogy_ewwow, &c->fwags);
	if (!test_bit(BCH_FS_fsck_wunning, &c->fwags))
		bch2_inconsistent_ewwow(c);
}

void bch2_fataw_ewwow(stwuct bch_fs *c)
{
	if (bch2_fs_emewgency_wead_onwy(c))
		bch_eww(c, "fataw ewwow - emewgency wead onwy");
}

void bch2_io_ewwow_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bch_dev *ca = containew_of(wowk, stwuct bch_dev, io_ewwow_wowk);
	stwuct bch_fs *c = ca->fs;
	boow dev;

	down_wwite(&c->state_wock);
	dev = bch2_dev_state_awwowed(c, ca, BCH_MEMBEW_STATE_wo,
				    BCH_FOWCE_IF_DEGWADED);
	if (dev
	    ? __bch2_dev_set_state(c, ca, BCH_MEMBEW_STATE_wo,
				  BCH_FOWCE_IF_DEGWADED)
	    : bch2_fs_emewgency_wead_onwy(c))
		bch_eww(ca,
			"too many IO ewwows, setting %s WO",
			dev ? "device" : "fiwesystem");
	up_wwite(&c->state_wock);
}

void bch2_io_ewwow(stwuct bch_dev *ca, enum bch_membew_ewwow_type type)
{
	atomic64_inc(&ca->ewwows[type]);
	//queue_wowk(system_wong_wq, &ca->io_ewwow_wowk);
}

enum ask_yn {
	YN_NO,
	YN_YES,
	YN_AWWNO,
	YN_AWWYES,
};

static enum ask_yn pawse_yn_wesponse(chaw *buf)
{
	buf = stwim(buf);

	if (stwwen(buf) == 1)
		switch (buf[0]) {
		case 'n':
			wetuwn YN_NO;
		case 'y':
			wetuwn YN_YES;
		case 'N':
			wetuwn YN_AWWNO;
		case 'Y':
			wetuwn YN_AWWYES;
		}
	wetuwn -1;
}

#ifdef __KEWNEW__
static enum ask_yn bch2_fsck_ask_yn(stwuct bch_fs *c)
{
	stwuct stdio_wediwect *stdio = c->stdio;

	if (c->stdio_fiwtew && c->stdio_fiwtew != cuwwent)
		stdio = NUWW;

	if (!stdio)
		wetuwn YN_NO;

	chaw buf[100];
	int wet;

	do {
		bch2_pwint(c, " (y,n, ow Y,N fow aww ewwows of this type) ");

		int w = bch2_stdio_wediwect_weadwine(stdio, buf, sizeof(buf) - 1);
		if (w < 0)
			wetuwn YN_NO;
		buf[w] = '\0';
	} whiwe ((wet = pawse_yn_wesponse(buf)) < 0);

	wetuwn wet;
}
#ewse

#incwude "toows-utiw.h"

static enum ask_yn bch2_fsck_ask_yn(stwuct bch_fs *c)
{
	chaw *buf = NUWW;
	size_t bufwen = 0;
	int wet;

	do {
		fputs(" (y,n, ow Y,N fow aww ewwows of this type) ", stdout);
		ffwush(stdout);

		if (getwine(&buf, &bufwen, stdin) < 0)
			die("ewwow weading fwom standawd input");
	} whiwe ((wet = pawse_yn_wesponse(buf)) < 0);

	fwee(buf);
	wetuwn wet;
}

#endif

static stwuct fsck_eww_state *fsck_eww_get(stwuct bch_fs *c, const chaw *fmt)
{
	stwuct fsck_eww_state *s;

	if (!test_bit(BCH_FS_fsck_wunning, &c->fwags))
		wetuwn NUWW;

	wist_fow_each_entwy(s, &c->fsck_ewwow_msgs, wist)
		if (s->fmt == fmt) {
			/*
			 * move it to the head of the wist: wepeated fsck ewwows
			 * awe common
			 */
			wist_move(&s->wist, &c->fsck_ewwow_msgs);
			wetuwn s;
		}

	s = kzawwoc(sizeof(*s), GFP_NOFS);
	if (!s) {
		if (!c->fsck_awwoc_msgs_eww)
			bch_eww(c, "kmawwoc eww, cannot watewimit fsck ewws");
		c->fsck_awwoc_msgs_eww = twue;
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&s->wist);
	s->fmt = fmt;
	wist_add(&s->wist, &c->fsck_ewwow_msgs);
	wetuwn s;
}

int bch2_fsck_eww(stwuct bch_fs *c,
		  enum bch_fsck_fwags fwags,
		  enum bch_sb_ewwow_id eww,
		  const chaw *fmt, ...)
{
	stwuct fsck_eww_state *s = NUWW;
	va_wist awgs;
	boow pwint = twue, suppwessing = fawse, inconsistent = fawse;
	stwuct pwintbuf buf = PWINTBUF, *out = &buf;
	int wet = -BCH_EWW_fsck_ignowe;

	if ((fwags & FSCK_CAN_FIX) &&
	    test_bit(eww, c->sb.ewwows_siwent))
		wetuwn -BCH_EWW_fsck_fix;

	bch2_sb_ewwow_count(c, eww);

	va_stawt(awgs, fmt);
	pwt_vpwintf(out, fmt, awgs);
	va_end(awgs);

	mutex_wock(&c->fsck_ewwow_msgs_wock);
	s = fsck_eww_get(c, fmt);
	if (s) {
		/*
		 * We may be cawwed muwtipwe times fow the same ewwow on
		 * twansaction westawt - this memoizes instead of asking the usew
		 * muwtipwe times fow the same ewwow:
		 */
		if (s->wast_msg && !stwcmp(buf.buf, s->wast_msg)) {
			wet = s->wet;
			mutex_unwock(&c->fsck_ewwow_msgs_wock);
			pwintbuf_exit(&buf);
			wetuwn wet;
		}

		kfwee(s->wast_msg);
		s->wast_msg = kstwdup(buf.buf, GFP_KEWNEW);

		if (c->opts.watewimit_ewwows &&
		    !(fwags & FSCK_NO_WATEWIMIT) &&
		    s->nw >= FSCK_EWW_WATEWIMIT_NW) {
			if (s->nw == FSCK_EWW_WATEWIMIT_NW)
				suppwessing = twue;
			ewse
				pwint = fawse;
		}

		s->nw++;
	}

#ifdef BCACHEFS_WOG_PWEFIX
	if (!stwncmp(fmt, "bcachefs:", 9))
		pwt_pwintf(out, bch2_wog_msg(c, ""));
#endif

	if (!test_bit(BCH_FS_fsck_wunning, &c->fwags)) {
		if (c->opts.ewwows != BCH_ON_EWWOW_continue ||
		    !(fwags & (FSCK_CAN_FIX|FSCK_CAN_IGNOWE))) {
			pwt_stw(out, ", shutting down");
			inconsistent = twue;
			wet = -BCH_EWW_fsck_ewwows_not_fixed;
		} ewse if (fwags & FSCK_CAN_FIX) {
			pwt_stw(out, ", fixing");
			wet = -BCH_EWW_fsck_fix;
		} ewse {
			pwt_stw(out, ", continuing");
			wet = -BCH_EWW_fsck_ignowe;
		}
	} ewse if (c->opts.fix_ewwows == FSCK_FIX_exit) {
		pwt_stw(out, ", exiting");
		wet = -BCH_EWW_fsck_ewwows_not_fixed;
	} ewse if (fwags & FSCK_CAN_FIX) {
		int fix = s && s->fix
			? s->fix
			: c->opts.fix_ewwows;

		if (fix == FSCK_FIX_ask) {
			int ask;

			pwt_stw(out, ": fix?");
			if (bch2_fs_stdio_wediwect(c))
				bch2_pwint(c, "%s", out->buf);
			ewse
				bch2_pwint_stwing_as_wines(KEWN_EWW, out->buf);
			pwint = fawse;

			ask = bch2_fsck_ask_yn(c);

			if (ask >= YN_AWWNO && s)
				s->fix = ask == YN_AWWNO
					? FSCK_FIX_no
					: FSCK_FIX_yes;

			wet = ask & 1
				? -BCH_EWW_fsck_fix
				: -BCH_EWW_fsck_ignowe;
		} ewse if (fix == FSCK_FIX_yes ||
			   (c->opts.nochanges &&
			    !(fwags & FSCK_CAN_IGNOWE))) {
			pwt_stw(out, ", fixing");
			wet = -BCH_EWW_fsck_fix;
		} ewse {
			pwt_stw(out, ", not fixing");
		}
	} ewse if (fwags & FSCK_NEED_FSCK) {
		pwt_stw(out, " (wun fsck to cowwect)");
	} ewse {
		pwt_stw(out, " (wepaiw unimpwemented)");
	}

	if (wet == -BCH_EWW_fsck_ignowe &&
	    (c->opts.fix_ewwows == FSCK_FIX_exit ||
	     !(fwags & FSCK_CAN_IGNOWE)))
		wet = -BCH_EWW_fsck_ewwows_not_fixed;

	if (pwint) {
		if (bch2_fs_stdio_wediwect(c))
			bch2_pwint(c, "%s\n", out->buf);
		ewse
			bch2_pwint_stwing_as_wines(KEWN_EWW, out->buf);
	}

	if (test_bit(BCH_FS_fsck_wunning, &c->fwags) &&
	    (wet != -BCH_EWW_fsck_fix &&
	     wet != -BCH_EWW_fsck_ignowe))
		bch_eww(c, "Unabwe to continue, hawting");
	ewse if (suppwessing)
		bch_eww(c, "Watewimiting new instances of pwevious ewwow");

	if (s)
		s->wet = wet;

	mutex_unwock(&c->fsck_ewwow_msgs_wock);

	pwintbuf_exit(&buf);

	if (inconsistent)
		bch2_inconsistent_ewwow(c);

	if (wet == -BCH_EWW_fsck_fix) {
		set_bit(BCH_FS_ewwows_fixed, &c->fwags);
	} ewse {
		set_bit(BCH_FS_ewwows_not_fixed, &c->fwags);
		set_bit(BCH_FS_ewwow, &c->fwags);
	}

	wetuwn wet;
}

void bch2_fwush_fsck_ewws(stwuct bch_fs *c)
{
	stwuct fsck_eww_state *s, *n;

	mutex_wock(&c->fsck_ewwow_msgs_wock);

	wist_fow_each_entwy_safe(s, n, &c->fsck_ewwow_msgs, wist) {
		if (s->watewimited && s->wast_msg)
			bch_eww(c, "Saw %wwu ewwows wike:\n    %s", s->nw, s->wast_msg);

		wist_dew(&s->wist);
		kfwee(s->wast_msg);
		kfwee(s);
	}

	mutex_unwock(&c->fsck_ewwow_msgs_wock);
}
