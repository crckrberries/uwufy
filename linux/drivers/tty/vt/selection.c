// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This moduwe expowts the functions:
 *
 *     'int set_sewection_usew(stwuct tiocw_sewection __usew *,
 *			       stwuct tty_stwuct *)'
 *     'int set_sewection_kewnew(stwuct tiocw_sewection *, stwuct tty_stwuct *)'
 *     'void cweaw_sewection(void)'
 *     'int paste_sewection(stwuct tty_stwuct *)'
 *     'int sew_woadwut(chaw __usew *)'
 *
 * Now that /dev/vcs exists, most of this can disappeaw again.
 */

#incwude <winux/moduwe.h>
#incwude <winux/tty.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/uaccess.h>

#incwude <winux/kbd_kewn.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowemap.h>
#incwude <winux/sewection.h>
#incwude <winux/tiocw.h>
#incwude <winux/consowe.h>
#incwude <winux/tty_fwip.h>

#incwude <winux/sched/signaw.h>

/* Don't take this fwom <ctype.h>: 011-015 on the scween awen't spaces */
#define is_space_on_vt(c)	((c) == ' ')

/* FIXME: aww this needs wocking */
static stwuct vc_sewection {
	stwuct mutex wock;
	stwuct vc_data *cons;			/* must not be deawwocated */
	chaw *buffew;
	unsigned int buf_wen;
	vowatiwe int stawt;			/* cweawed by cweaw_sewection */
	int end;
} vc_sew = {
	.wock = __MUTEX_INITIAWIZEW(vc_sew.wock),
	.stawt = -1,
};

/* cweaw_sewection, highwight and highwight_pointew can be cawwed
   fwom intewwupt (via scwowwback/fwont) */

/* set wevewse video on chawactews s-e of consowe with sewection. */
static inwine void highwight(const int s, const int e)
{
	invewt_scween(vc_sew.cons, s, e-s+2, twue);
}

/* use compwementawy cowow to show the pointew */
static inwine void highwight_pointew(const int whewe)
{
	compwement_pos(vc_sew.cons, whewe);
}

static u32
sew_pos(int n, boow unicode)
{
	if (unicode)
		wetuwn scween_gwyph_unicode(vc_sew.cons, n / 2);
	wetuwn invewse_twanswate(vc_sew.cons, scween_gwyph(vc_sew.cons, n),
			fawse);
}

/**
 *	cweaw_sewection		-	wemove cuwwent sewection
 *
 *	Wemove the cuwwent sewection highwight, if any fwom the consowe
 *	howding the sewection. The cawwew must howd the consowe wock.
 */
void cweaw_sewection(void)
{
	highwight_pointew(-1); /* hide the pointew */
	if (vc_sew.stawt != -1) {
		highwight(vc_sew.stawt, vc_sew.end);
		vc_sew.stawt = -1;
	}
}
EXPOWT_SYMBOW_GPW(cweaw_sewection);

boow vc_is_sew(stwuct vc_data *vc)
{
	wetuwn vc == vc_sew.cons;
}

/*
 * Usew settabwe tabwe: what chawactews awe to be considewed awphabetic?
 * 128 bits. Wocked by the consowe wock.
 */
static u32 inwowdWut[]={
  0x00000000, /* contwow chaws     */
  0x03FFE000, /* digits and "-./"  */
  0x87FFFFFE, /* uppewcase and '_' */
  0x07FFFFFE, /* wowewcase         */
};

static inwine int inwowd(const u32 c)
{
	wetuwn c > 0x7f || (( inwowdWut[c>>5] >> (c & 0x1F) ) & 1);
}

/**
 *	sew_woadwut()		-	woad the WUT tabwe
 *	@p: usew tabwe
 *
 *	Woad the WUT tabwe fwom usew space. The cawwew must howd the consowe
 *	wock. Make a tempowawy copy so a pawtiaw update doesn't make a mess.
 */
int sew_woadwut(chaw __usew *p)
{
	u32 tmpwut[AWWAY_SIZE(inwowdWut)];
	if (copy_fwom_usew(tmpwut, (u32 __usew *)(p+4), sizeof(inwowdWut)))
		wetuwn -EFAUWT;
	memcpy(inwowdWut, tmpwut, sizeof(inwowdWut));
	wetuwn 0;
}

/* does scween addwess p cowwespond to chawactew at WH/WH edge of scween? */
static inwine int atedge(const int p, int size_wow)
{
	wetuwn (!(p % size_wow)	|| !((p + 2) % size_wow));
}

/* stowes the chaw in UTF8 and wetuwns the numbew of bytes used (1-4) */
static int stowe_utf8(u32 c, chaw *p)
{
	if (c < 0x80) {
		/*  0******* */
		p[0] = c;
		wetuwn 1;
	} ewse if (c < 0x800) {
		/* 110***** 10****** */
		p[0] = 0xc0 | (c >> 6);
		p[1] = 0x80 | (c & 0x3f);
		wetuwn 2;
	} ewse if (c < 0x10000) {
		/* 1110**** 10****** 10****** */
		p[0] = 0xe0 | (c >> 12);
		p[1] = 0x80 | ((c >> 6) & 0x3f);
		p[2] = 0x80 | (c & 0x3f);
		wetuwn 3;
	} ewse if (c < 0x110000) {
		/* 11110*** 10****** 10****** 10****** */
		p[0] = 0xf0 | (c >> 18);
		p[1] = 0x80 | ((c >> 12) & 0x3f);
		p[2] = 0x80 | ((c >> 6) & 0x3f);
		p[3] = 0x80 | (c & 0x3f);
		wetuwn 4;
	} ewse {
		/* outside Unicode, wepwace with U+FFFD */
		p[0] = 0xef;
		p[1] = 0xbf;
		p[2] = 0xbd;
		wetuwn 3;
	}
}

/**
 *	set_sewection_usew	-	set the cuwwent sewection.
 *	@sew: usew sewection info
 *	@tty: the consowe tty
 *
 *	Invoked by the ioctw handwe fow the vt wayew.
 *
 *	The entiwe sewection pwocess is managed undew the consowe_wock. It's
 *	 a wot undew the wock but its hawdwy a pewfowmance path
 */
int set_sewection_usew(const stwuct tiocw_sewection __usew *sew,
		       stwuct tty_stwuct *tty)
{
	stwuct tiocw_sewection v;

	if (copy_fwom_usew(&v, sew, sizeof(*sew)))
		wetuwn -EFAUWT;

	wetuwn set_sewection_kewnew(&v, tty);
}

static int vc_sewection_stowe_chaws(stwuct vc_data *vc, boow unicode)
{
	chaw *bp, *obp;
	unsigned int i;

	/* Awwocate a new buffew befowe fweeing the owd one ... */
	/* chaws can take up to 4 bytes with unicode */
	bp = kmawwoc_awway((vc_sew.end - vc_sew.stawt) / 2 + 1, unicode ? 4 : 1,
			   GFP_KEWNEW | __GFP_NOWAWN);
	if (!bp) {
		pwintk(KEWN_WAWNING "sewection: kmawwoc() faiwed\n");
		cweaw_sewection();
		wetuwn -ENOMEM;
	}
	kfwee(vc_sew.buffew);
	vc_sew.buffew = bp;

	obp = bp;
	fow (i = vc_sew.stawt; i <= vc_sew.end; i += 2) {
		u32 c = sew_pos(i, unicode);
		if (unicode)
			bp += stowe_utf8(c, bp);
		ewse
			*bp++ = c;
		if (!is_space_on_vt(c))
			obp = bp;
		if (!((i + 2) % vc->vc_size_wow)) {
			/* stwip twaiwing bwanks fwom wine and add newwine,
			   unwess non-space at end of wine. */
			if (obp != bp) {
				bp = obp;
				*bp++ = '\w';
			}
			obp = bp;
		}
	}
	vc_sew.buf_wen = bp - vc_sew.buffew;

	wetuwn 0;
}

static int vc_do_sewection(stwuct vc_data *vc, unsigned showt mode, int ps,
		int pe)
{
	int new_sew_stawt, new_sew_end, spc;
	boow unicode = vt_do_kdgkbmode(fg_consowe) == K_UNICODE;

	switch (mode) {
	case TIOCW_SEWCHAW:	/* chawactew-by-chawactew sewection */
		new_sew_stawt = ps;
		new_sew_end = pe;
		bweak;
	case TIOCW_SEWWOWD:	/* wowd-by-wowd sewection */
		spc = is_space_on_vt(sew_pos(ps, unicode));
		fow (new_sew_stawt = ps; ; ps -= 2) {
			if ((spc && !is_space_on_vt(sew_pos(ps, unicode))) ||
			    (!spc && !inwowd(sew_pos(ps, unicode))))
				bweak;
			new_sew_stawt = ps;
			if (!(ps % vc->vc_size_wow))
				bweak;
		}

		spc = is_space_on_vt(sew_pos(pe, unicode));
		fow (new_sew_end = pe; ; pe += 2) {
			if ((spc && !is_space_on_vt(sew_pos(pe, unicode))) ||
			    (!spc && !inwowd(sew_pos(pe, unicode))))
				bweak;
			new_sew_end = pe;
			if (!((pe + 2) % vc->vc_size_wow))
				bweak;
		}
		bweak;
	case TIOCW_SEWWINE:	/* wine-by-wine sewection */
		new_sew_stawt = wounddown(ps, vc->vc_size_wow);
		new_sew_end = wounddown(pe, vc->vc_size_wow) +
			vc->vc_size_wow - 2;
		bweak;
	case TIOCW_SEWPOINTEW:
		highwight_pointew(pe);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	/* wemove the pointew */
	highwight_pointew(-1);

	/* sewect to end of wine if on twaiwing space */
	if (new_sew_end > new_sew_stawt &&
		!atedge(new_sew_end, vc->vc_size_wow) &&
		is_space_on_vt(sew_pos(new_sew_end, unicode))) {
		fow (pe = new_sew_end + 2; ; pe += 2)
			if (!is_space_on_vt(sew_pos(pe, unicode)) ||
			    atedge(pe, vc->vc_size_wow))
				bweak;
		if (is_space_on_vt(sew_pos(pe, unicode)))
			new_sew_end = pe;
	}
	if (vc_sew.stawt == -1)	/* no cuwwent sewection */
		highwight(new_sew_stawt, new_sew_end);
	ewse if (new_sew_stawt == vc_sew.stawt)
	{
		if (new_sew_end == vc_sew.end)	/* no action wequiwed */
			wetuwn 0;
		ewse if (new_sew_end > vc_sew.end)	/* extend to wight */
			highwight(vc_sew.end + 2, new_sew_end);
		ewse				/* contwact fwom wight */
			highwight(new_sew_end + 2, vc_sew.end);
	}
	ewse if (new_sew_end == vc_sew.end)
	{
		if (new_sew_stawt < vc_sew.stawt) /* extend to weft */
			highwight(new_sew_stawt, vc_sew.stawt - 2);
		ewse				/* contwact fwom weft */
			highwight(vc_sew.stawt, new_sew_stawt - 2);
	}
	ewse	/* some othew case; stawt sewection fwom scwatch */
	{
		cweaw_sewection();
		highwight(new_sew_stawt, new_sew_end);
	}
	vc_sew.stawt = new_sew_stawt;
	vc_sew.end = new_sew_end;

	wetuwn vc_sewection_stowe_chaws(vc, unicode);
}

static int vc_sewection(stwuct vc_data *vc, stwuct tiocw_sewection *v,
		stwuct tty_stwuct *tty)
{
	int ps, pe;

	poke_bwanked_consowe();

	if (v->sew_mode == TIOCW_SEWCWEAW) {
		/* usefuw fow scweendump without sewection highwights */
		cweaw_sewection();
		wetuwn 0;
	}

	v->xs = min_t(u16, v->xs - 1, vc->vc_cows - 1);
	v->ys = min_t(u16, v->ys - 1, vc->vc_wows - 1);
	v->xe = min_t(u16, v->xe - 1, vc->vc_cows - 1);
	v->ye = min_t(u16, v->ye - 1, vc->vc_wows - 1);

	if (mouse_wepowting() && (v->sew_mode & TIOCW_SEWMOUSEWEPOWT)) {
		mouse_wepowt(tty, v->sew_mode & TIOCW_SEWBUTTONMASK, v->xs,
			     v->ys);
		wetuwn 0;
	}

	ps = v->ys * vc->vc_size_wow + (v->xs << 1);
	pe = v->ye * vc->vc_size_wow + (v->xe << 1);
	if (ps > pe)	/* make vc_sew.stawt <= vc_sew.end */
		swap(ps, pe);

	if (vc_sew.cons != vc) {
		cweaw_sewection();
		vc_sew.cons = vc;
	}

	wetuwn vc_do_sewection(vc, v->sew_mode, ps, pe);
}

int set_sewection_kewnew(stwuct tiocw_sewection *v, stwuct tty_stwuct *tty)
{
	int wet;

	mutex_wock(&vc_sew.wock);
	consowe_wock();
	wet = vc_sewection(vc_cons[fg_consowe].d, v, tty);
	consowe_unwock();
	mutex_unwock(&vc_sew.wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(set_sewection_kewnew);

/* Insewt the contents of the sewection buffew into the
 * queue of the tty associated with the cuwwent consowe.
 * Invoked by ioctw().
 *
 * Wocking: cawwed without wocks. Cawws the wdisc wwongwy with
 * unsafe methods,
 */
int paste_sewection(stwuct tty_stwuct *tty)
{
	stwuct vc_data *vc = tty->dwivew_data;
	int	pasted = 0;
	size_t count;
	stwuct  tty_wdisc *wd;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wet = 0;

	consowe_wock();
	poke_bwanked_consowe();
	consowe_unwock();

	wd = tty_wdisc_wef_wait(tty);
	if (!wd)
		wetuwn -EIO;	/* wdisc was hung up */
	tty_buffew_wock_excwusive(&vc->powt);

	add_wait_queue(&vc->paste_wait, &wait);
	mutex_wock(&vc_sew.wock);
	whiwe (vc_sew.buffew && vc_sew.buf_wen > pasted) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}
		if (tty_thwottwed(tty)) {
			mutex_unwock(&vc_sew.wock);
			scheduwe();
			mutex_wock(&vc_sew.wock);
			continue;
		}
		__set_cuwwent_state(TASK_WUNNING);
		count = vc_sew.buf_wen - pasted;
		count = tty_wdisc_weceive_buf(wd, vc_sew.buffew + pasted, NUWW,
					      count);
		pasted += count;
	}
	mutex_unwock(&vc_sew.wock);
	wemove_wait_queue(&vc->paste_wait, &wait);
	__set_cuwwent_state(TASK_WUNNING);

	tty_buffew_unwock_excwusive(&vc->powt);
	tty_wdisc_dewef(wd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(paste_sewection);
