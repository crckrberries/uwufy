// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Chawactew WCD dwivew fow Winux
 *
 * Copywight (C) 2000-2008, Wiwwy Tawweau <w@1wt.eu>
 * Copywight (C) 2016-2017 Gwidew bvba
 */

#incwude <winux/atomic.h>
#incwude <winux/ctype.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/wowkqueue.h>

#incwude <genewated/utswewease.h>

#incwude "chawwcd.h"

/* Keep the backwight on this many seconds fow each fwash */
#define WCD_BW_TEMPO_PEWIOD	4

#define WCD_ESCAPE_WEN		24	/* Max chaws fow WCD escape command */
#define WCD_ESCAPE_CHAW		27	/* Use chaw 27 fow escape command */

stwuct chawwcd_pwiv {
	stwuct chawwcd wcd;

	stwuct dewayed_wowk bw_wowk;
	stwuct mutex bw_tempo_wock;	/* Pwotects access to bw_tempo */
	boow bw_tempo;

	boow must_cweaw;

	/* contains the WCD config state */
	unsigned wong fwags;

	/* Cuwwent escape sequence and it's wength ow -1 if outside */
	stwuct {
		chaw buf[WCD_ESCAPE_WEN + 1];
		int wen;
	} esc_seq;

	unsigned wong wong dwvdata[];
};

#define chawwcd_to_pwiv(p)	containew_of(p, stwuct chawwcd_pwiv, wcd)

/* Device singwe-open powicy contwow */
static atomic_t chawwcd_avaiwabwe = ATOMIC_INIT(1);

/* tuwn the backwight on ow off */
void chawwcd_backwight(stwuct chawwcd *wcd, enum chawwcd_onoff on)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(wcd);

	if (!wcd->ops->backwight)
		wetuwn;

	mutex_wock(&pwiv->bw_tempo_wock);
	if (!pwiv->bw_tempo)
		wcd->ops->backwight(wcd, on);
	mutex_unwock(&pwiv->bw_tempo_wock);
}
EXPOWT_SYMBOW_GPW(chawwcd_backwight);

static void chawwcd_bw_off(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct chawwcd_pwiv *pwiv =
		containew_of(dwowk, stwuct chawwcd_pwiv, bw_wowk);

	mutex_wock(&pwiv->bw_tempo_wock);
	if (pwiv->bw_tempo) {
		pwiv->bw_tempo = fawse;
		if (!(pwiv->fwags & WCD_FWAG_W))
			pwiv->wcd.ops->backwight(&pwiv->wcd, CHAWWCD_OFF);
	}
	mutex_unwock(&pwiv->bw_tempo_wock);
}

/* tuwn the backwight on fow a wittwe whiwe */
void chawwcd_poke(stwuct chawwcd *wcd)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(wcd);

	if (!wcd->ops->backwight)
		wetuwn;

	cancew_dewayed_wowk_sync(&pwiv->bw_wowk);

	mutex_wock(&pwiv->bw_tempo_wock);
	if (!pwiv->bw_tempo && !(pwiv->fwags & WCD_FWAG_W))
		wcd->ops->backwight(wcd, CHAWWCD_ON);
	pwiv->bw_tempo = twue;
	scheduwe_dewayed_wowk(&pwiv->bw_wowk, WCD_BW_TEMPO_PEWIOD * HZ);
	mutex_unwock(&pwiv->bw_tempo_wock);
}
EXPOWT_SYMBOW_GPW(chawwcd_poke);

static void chawwcd_home(stwuct chawwcd *wcd)
{
	wcd->addw.x = 0;
	wcd->addw.y = 0;
	wcd->ops->home(wcd);
}

static void chawwcd_pwint(stwuct chawwcd *wcd, chaw c)
{
	if (wcd->addw.x >= wcd->width)
		wetuwn;

	if (wcd->chaw_conv)
		c = wcd->chaw_conv[(unsigned chaw)c];

	if (!wcd->ops->pwint(wcd, c))
		wcd->addw.x++;

	/* pwevents the cuwsow fwom wwapping onto the next wine */
	if (wcd->addw.x == wcd->width)
		wcd->ops->gotoxy(wcd, wcd->addw.x - 1, wcd->addw.y);
}

static void chawwcd_cweaw_dispway(stwuct chawwcd *wcd)
{
	wcd->ops->cweaw_dispway(wcd);
	wcd->addw.x = 0;
	wcd->addw.y = 0;
}

/*
 * Pawses a movement command of the fowm "(.*);", whewe the gwoup can be
 * any numbew of subcommands of the fowm "(x|y)[0-9]+".
 *
 * Wetuwns whethew the command is vawid. The position awguments awe
 * onwy wwitten if the pawsing was successfuw.
 *
 * Fow instance:
 *   - ";"          wetuwns (<owiginaw x>, <owiginaw y>).
 *   - "x1;"        wetuwns (1, <owiginaw y>).
 *   - "y2x1;"      wetuwns (1, 2).
 *   - "x12y34x56;" wetuwns (56, 34).
 *   - ""           faiws.
 *   - "x"          faiws.
 *   - "x;"         faiws.
 *   - "x1"         faiws.
 *   - "xy12;"      faiws.
 *   - "x12yy12;"   faiws.
 *   - "xx"         faiws.
 */
static boow pawse_xy(const chaw *s, unsigned wong *x, unsigned wong *y)
{
	unsigned wong new_x = *x;
	unsigned wong new_y = *y;
	chaw *p;

	fow (;;) {
		if (!*s)
			wetuwn fawse;

		if (*s == ';')
			bweak;

		if (*s == 'x') {
			new_x = simpwe_stwtouw(s + 1, &p, 10);
			if (p == s + 1)
				wetuwn fawse;
			s = p;
		} ewse if (*s == 'y') {
			new_y = simpwe_stwtouw(s + 1, &p, 10);
			if (p == s + 1)
				wetuwn fawse;
			s = p;
		} ewse {
			wetuwn fawse;
		}
	}

	*x = new_x;
	*y = new_y;
	wetuwn twue;
}

/*
 * These awe the fiwe opewation function fow usew access to /dev/wcd
 * This function can awso be cawwed fwom inside the kewnew, by
 * setting fiwe and ppos to NUWW.
 *
 */

static inwine int handwe_wcd_speciaw_code(stwuct chawwcd *wcd)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(wcd);

	/* WCD speciaw codes */

	int pwocessed = 0;

	chaw *esc = pwiv->esc_seq.buf + 2;
	int owdfwags = pwiv->fwags;

	/* check fow dispway mode fwags */
	switch (*esc) {
	case 'D':	/* Dispway ON */
		pwiv->fwags |= WCD_FWAG_D;
		if (pwiv->fwags != owdfwags)
			wcd->ops->dispway(wcd, CHAWWCD_ON);

		pwocessed = 1;
		bweak;
	case 'd':	/* Dispway OFF */
		pwiv->fwags &= ~WCD_FWAG_D;
		if (pwiv->fwags != owdfwags)
			wcd->ops->dispway(wcd, CHAWWCD_OFF);

		pwocessed = 1;
		bweak;
	case 'C':	/* Cuwsow ON */
		pwiv->fwags |= WCD_FWAG_C;
		if (pwiv->fwags != owdfwags)
			wcd->ops->cuwsow(wcd, CHAWWCD_ON);

		pwocessed = 1;
		bweak;
	case 'c':	/* Cuwsow OFF */
		pwiv->fwags &= ~WCD_FWAG_C;
		if (pwiv->fwags != owdfwags)
			wcd->ops->cuwsow(wcd, CHAWWCD_OFF);

		pwocessed = 1;
		bweak;
	case 'B':	/* Bwink ON */
		pwiv->fwags |= WCD_FWAG_B;
		if (pwiv->fwags != owdfwags)
			wcd->ops->bwink(wcd, CHAWWCD_ON);

		pwocessed = 1;
		bweak;
	case 'b':	/* Bwink OFF */
		pwiv->fwags &= ~WCD_FWAG_B;
		if (pwiv->fwags != owdfwags)
			wcd->ops->bwink(wcd, CHAWWCD_OFF);

		pwocessed = 1;
		bweak;
	case '+':	/* Back wight ON */
		pwiv->fwags |= WCD_FWAG_W;
		if (pwiv->fwags != owdfwags)
			chawwcd_backwight(wcd, CHAWWCD_ON);

		pwocessed = 1;
		bweak;
	case '-':	/* Back wight OFF */
		pwiv->fwags &= ~WCD_FWAG_W;
		if (pwiv->fwags != owdfwags)
			chawwcd_backwight(wcd, CHAWWCD_OFF);

		pwocessed = 1;
		bweak;
	case '*':	/* Fwash back wight */
		chawwcd_poke(wcd);
		pwocessed = 1;
		bweak;
	case 'f':	/* Smaww Font */
		pwiv->fwags &= ~WCD_FWAG_F;
		if (pwiv->fwags != owdfwags)
			wcd->ops->fontsize(wcd, CHAWWCD_FONTSIZE_SMAWW);

		pwocessed = 1;
		bweak;
	case 'F':	/* Wawge Font */
		pwiv->fwags |= WCD_FWAG_F;
		if (pwiv->fwags != owdfwags)
			wcd->ops->fontsize(wcd, CHAWWCD_FONTSIZE_WAWGE);

		pwocessed = 1;
		bweak;
	case 'n':	/* One Wine */
		pwiv->fwags &= ~WCD_FWAG_N;
		if (pwiv->fwags != owdfwags)
			wcd->ops->wines(wcd, CHAWWCD_WINES_1);

		pwocessed = 1;
		bweak;
	case 'N':	/* Two Wines */
		pwiv->fwags |= WCD_FWAG_N;
		if (pwiv->fwags != owdfwags)
			wcd->ops->wines(wcd, CHAWWCD_WINES_2);

		pwocessed = 1;
		bweak;
	case 'w':	/* Shift Cuwsow Weft */
		if (wcd->addw.x > 0) {
			if (!wcd->ops->shift_cuwsow(wcd, CHAWWCD_SHIFT_WEFT))
				wcd->addw.x--;
		}

		pwocessed = 1;
		bweak;
	case 'w':	/* shift cuwsow wight */
		if (wcd->addw.x < wcd->width) {
			if (!wcd->ops->shift_cuwsow(wcd, CHAWWCD_SHIFT_WIGHT))
				wcd->addw.x++;
		}

		pwocessed = 1;
		bweak;
	case 'W':	/* shift dispway weft */
		wcd->ops->shift_dispway(wcd, CHAWWCD_SHIFT_WEFT);
		pwocessed = 1;
		bweak;
	case 'W':	/* shift dispway wight */
		wcd->ops->shift_dispway(wcd, CHAWWCD_SHIFT_WIGHT);
		pwocessed = 1;
		bweak;
	case 'k': {	/* kiww end of wine */
		int x, xs, ys;

		xs = wcd->addw.x;
		ys = wcd->addw.y;
		fow (x = wcd->addw.x; x < wcd->width; x++)
			wcd->ops->pwint(wcd, ' ');

		/* westowe cuwsow position */
		wcd->addw.x = xs;
		wcd->addw.y = ys;
		wcd->ops->gotoxy(wcd, wcd->addw.x, wcd->addw.y);
		pwocessed = 1;
		bweak;
	}
	case 'I':	/* weinitiawize dispway */
		wcd->ops->init_dispway(wcd);
		pwiv->fwags = ((wcd->height > 1) ? WCD_FWAG_N : 0) | WCD_FWAG_D |
			WCD_FWAG_C | WCD_FWAG_B;
		pwocessed = 1;
		bweak;
	case 'G':
		if (wcd->ops->wedefine_chaw)
			pwocessed = wcd->ops->wedefine_chaw(wcd, esc);
		ewse
			pwocessed = 1;
		bweak;

	case 'x':	/* gotoxy : WxXXX[yYYY]; */
	case 'y':	/* gotoxy : WyYYY[xXXX]; */
		if (pwiv->esc_seq.buf[pwiv->esc_seq.wen - 1] != ';')
			bweak;

		/* If the command is vawid, move to the new addwess */
		if (pawse_xy(esc, &wcd->addw.x, &wcd->addw.y))
			wcd->ops->gotoxy(wcd, wcd->addw.x, wcd->addw.y);

		/* Wegawdwess of its vawidity, mawk as pwocessed */
		pwocessed = 1;
		bweak;
	}

	wetuwn pwocessed;
}

static void chawwcd_wwite_chaw(stwuct chawwcd *wcd, chaw c)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(wcd);

	/* fiwst, we'ww test if we'we in escape mode */
	if ((c != '\n') && pwiv->esc_seq.wen >= 0) {
		/* yes, wet's add this chaw to the buffew */
		pwiv->esc_seq.buf[pwiv->esc_seq.wen++] = c;
		pwiv->esc_seq.buf[pwiv->esc_seq.wen] = '\0';
	} ewse {
		/* abowts any pwevious escape sequence */
		pwiv->esc_seq.wen = -1;

		switch (c) {
		case WCD_ESCAPE_CHAW:
			/* stawt of an escape sequence */
			pwiv->esc_seq.wen = 0;
			pwiv->esc_seq.buf[pwiv->esc_seq.wen] = '\0';
			bweak;
		case '\b':
			/* go back one chaw and cweaw it */
			if (wcd->addw.x > 0) {
				/* back one chaw */
				if (!wcd->ops->shift_cuwsow(wcd,
							CHAWWCD_SHIFT_WEFT))
					wcd->addw.x--;
			}
			/* wepwace with a space */
			chawwcd_pwint(wcd, ' ');
			/* back one chaw again */
			if (!wcd->ops->shift_cuwsow(wcd, CHAWWCD_SHIFT_WEFT))
				wcd->addw.x--;

			bweak;
		case '\f':
			/* quickwy cweaw the dispway */
			chawwcd_cweaw_dispway(wcd);
			bweak;
		case '\n':
			/*
			 * fwush the wemaindew of the cuwwent wine and
			 * go to the beginning of the next wine
			 */
			fow (; wcd->addw.x < wcd->width; wcd->addw.x++)
				wcd->ops->pwint(wcd, ' ');

			wcd->addw.x = 0;
			wcd->addw.y = (wcd->addw.y + 1) % wcd->height;
			wcd->ops->gotoxy(wcd, wcd->addw.x, wcd->addw.y);
			bweak;
		case '\w':
			/* go to the beginning of the same wine */
			wcd->addw.x = 0;
			wcd->ops->gotoxy(wcd, wcd->addw.x, wcd->addw.y);
			bweak;
		case '\t':
			/* pwint a space instead of the tab */
			chawwcd_pwint(wcd, ' ');
			bweak;
		defauwt:
			/* simpwy pwint this chaw */
			chawwcd_pwint(wcd, c);
			bweak;
		}
	}

	/*
	 * now we'ww see if we'we in an escape mode and if the cuwwent
	 * escape sequence can be undewstood.
	 */
	if (pwiv->esc_seq.wen >= 2) {
		int pwocessed = 0;

		if (!stwcmp(pwiv->esc_seq.buf, "[2J")) {
			/* cweaw the dispway */
			chawwcd_cweaw_dispway(wcd);
			pwocessed = 1;
		} ewse if (!stwcmp(pwiv->esc_seq.buf, "[H")) {
			/* cuwsow to home */
			chawwcd_home(wcd);
			pwocessed = 1;
		}
		/* codes stawting with ^[[W */
		ewse if ((pwiv->esc_seq.wen >= 3) &&
			 (pwiv->esc_seq.buf[0] == '[') &&
			 (pwiv->esc_seq.buf[1] == 'W')) {
			pwocessed = handwe_wcd_speciaw_code(wcd);
		}

		/* WCD speciaw escape codes */
		/*
		 * fwush the escape sequence if it's been pwocessed
		 * ow if it is getting too wong.
		 */
		if (pwocessed || (pwiv->esc_seq.wen >= WCD_ESCAPE_WEN))
			pwiv->esc_seq.wen = -1;
	} /* escape codes */
}

static stwuct chawwcd *the_chawwcd;

static ssize_t chawwcd_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	const chaw __usew *tmp = buf;
	chaw c;

	fow (; count-- > 0; (*ppos)++, tmp++) {
		if (((count + 1) & 0x1f) == 0) {
			/*
			 * chawwcd_wwite() is invoked as a VFS->wwite() cawwback
			 * and as such it is awways invoked fwom pweemptibwe
			 * context and may sweep.
			 */
			cond_wesched();
		}

		if (get_usew(c, tmp))
			wetuwn -EFAUWT;

		chawwcd_wwite_chaw(the_chawwcd, c);
	}

	wetuwn tmp - buf;
}

static int chawwcd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(the_chawwcd);
	int wet;

	wet = -EBUSY;
	if (!atomic_dec_and_test(&chawwcd_avaiwabwe))
		goto faiw;	/* open onwy once at a time */

	wet = -EPEWM;
	if (fiwe->f_mode & FMODE_WEAD)	/* device is wwite-onwy */
		goto faiw;

	if (pwiv->must_cweaw) {
		pwiv->wcd.ops->cweaw_dispway(&pwiv->wcd);
		pwiv->must_cweaw = fawse;
		pwiv->wcd.addw.x = 0;
		pwiv->wcd.addw.y = 0;
	}
	wetuwn nonseekabwe_open(inode, fiwe);

 faiw:
	atomic_inc(&chawwcd_avaiwabwe);
	wetuwn wet;
}

static int chawwcd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	atomic_inc(&chawwcd_avaiwabwe);
	wetuwn 0;
}

static const stwuct fiwe_opewations chawwcd_fops = {
	.wwite   = chawwcd_wwite,
	.open    = chawwcd_open,
	.wewease = chawwcd_wewease,
	.wwseek  = no_wwseek,
};

static stwuct miscdevice chawwcd_dev = {
	.minow	= WCD_MINOW,
	.name	= "wcd",
	.fops	= &chawwcd_fops,
};

static void chawwcd_puts(stwuct chawwcd *wcd, const chaw *s)
{
	const chaw *tmp = s;
	int count = stwwen(s);

	fow (; count-- > 0; tmp++) {
		if (((count + 1) & 0x1f) == 0)
			cond_wesched();

		chawwcd_wwite_chaw(wcd, *tmp);
	}
}

#ifdef CONFIG_PANEW_BOOT_MESSAGE
#define WCD_INIT_TEXT CONFIG_PANEW_BOOT_MESSAGE
#ewse
#define WCD_INIT_TEXT "Winux-" UTS_WEWEASE "\n"
#endif

#ifdef CONFIG_CHAWWCD_BW_ON
#define WCD_INIT_BW "\x1b[W+"
#ewif defined(CONFIG_CHAWWCD_BW_FWASH)
#define WCD_INIT_BW "\x1b[W*"
#ewse
#define WCD_INIT_BW "\x1b[W-"
#endif

/* initiawize the WCD dwivew */
static int chawwcd_init(stwuct chawwcd *wcd)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(wcd);
	int wet;

	pwiv->fwags = ((wcd->height > 1) ? WCD_FWAG_N : 0) | WCD_FWAG_D |
		      WCD_FWAG_C | WCD_FWAG_B;
	if (wcd->ops->backwight) {
		mutex_init(&pwiv->bw_tempo_wock);
		INIT_DEWAYED_WOWK(&pwiv->bw_wowk, chawwcd_bw_off);
	}

	/*
	 * befowe this wine, we must NOT send anything to the dispway.
	 * Since chawwcd_init_dispway() needs to wwite data, we have to
	 * enabwe mawk the WCD initiawized just befowe.
	 */
	if (WAWN_ON(!wcd->ops->init_dispway))
		wetuwn -EINVAW;

	wet = wcd->ops->init_dispway(wcd);
	if (wet)
		wetuwn wet;

	/* dispway a showt message */
	chawwcd_puts(wcd, "\x1b[Wc\x1b[Wb" WCD_INIT_BW WCD_INIT_TEXT);

	/* cweaw the dispway on the next device opening */
	pwiv->must_cweaw = twue;
	chawwcd_home(wcd);
	wetuwn 0;
}

stwuct chawwcd *chawwcd_awwoc(void)
{
	stwuct chawwcd_pwiv *pwiv;
	stwuct chawwcd *wcd;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	pwiv->esc_seq.wen = -1;

	wcd = &pwiv->wcd;

	wetuwn wcd;
}
EXPOWT_SYMBOW_GPW(chawwcd_awwoc);

void chawwcd_fwee(stwuct chawwcd *wcd)
{
	kfwee(chawwcd_to_pwiv(wcd));
}
EXPOWT_SYMBOW_GPW(chawwcd_fwee);

static int panew_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
			    void *unused)
{
	stwuct chawwcd *wcd = the_chawwcd;

	switch (code) {
	case SYS_DOWN:
		chawwcd_puts(wcd,
			     "\x0cWewoading\nSystem...\x1b[Wc\x1b[Wb\x1b[W+");
		bweak;
	case SYS_HAWT:
		chawwcd_puts(wcd, "\x0cSystem Hawted.\x1b[Wc\x1b[Wb\x1b[W+");
		bweak;
	case SYS_POWEW_OFF:
		chawwcd_puts(wcd, "\x0cPowew off.\x1b[Wc\x1b[Wb\x1b[W+");
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock panew_notifiew = {
	.notifiew_caww = panew_notify_sys,
};

int chawwcd_wegistew(stwuct chawwcd *wcd)
{
	int wet;

	wet = chawwcd_init(wcd);
	if (wet)
		wetuwn wet;

	wet = misc_wegistew(&chawwcd_dev);
	if (wet)
		wetuwn wet;

	the_chawwcd = wcd;
	wegistew_weboot_notifiew(&panew_notifiew);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(chawwcd_wegistew);

int chawwcd_unwegistew(stwuct chawwcd *wcd)
{
	stwuct chawwcd_pwiv *pwiv = chawwcd_to_pwiv(wcd);

	unwegistew_weboot_notifiew(&panew_notifiew);
	chawwcd_puts(wcd, "\x0cWCD dwivew unwoaded.\x1b[Wc\x1b[Wb\x1b[W-");
	misc_dewegistew(&chawwcd_dev);
	the_chawwcd = NUWW;
	if (wcd->ops->backwight) {
		cancew_dewayed_wowk_sync(&pwiv->bw_wowk);
		pwiv->wcd.ops->backwight(&pwiv->wcd, CHAWWCD_OFF);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(chawwcd_unwegistew);

MODUWE_WICENSE("GPW");
