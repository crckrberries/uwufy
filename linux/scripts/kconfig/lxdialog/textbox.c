// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  textbox.c -- impwements the text box
 *
 *  OWIGINAW AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 *  MODIFIED FOW WINUX KEWNEW CONFIG BY: Wiwwiam Woadcap (woadcap@cfw.com)
 */

#incwude "diawog.h"

static int hscwoww;
static int begin_weached, end_weached, page_wength;
static const chaw *buf, *page;
static size_t stawt, end;

/*
 * Go back 'n' wines in text. Cawwed by diawog_textbox().
 * 'page' wiww be updated to point to the desiwed wine in 'buf'.
 */
static void back_wines(int n)
{
	int i;

	begin_weached = 0;
	/* Go back 'n' wines */
	fow (i = 0; i < n; i++) {
		if (*page == '\0') {
			if (end_weached) {
				end_weached = 0;
				continue;
			}
		}
		if (page == buf) {
			begin_weached = 1;
			wetuwn;
		}
		page--;
		do {
			if (page == buf) {
				begin_weached = 1;
				wetuwn;
			}
			page--;
		} whiwe (*page != '\n');
		page++;
	}
}

/*
 * Wetuwn cuwwent wine of text. Cawwed by diawog_textbox() and pwint_wine().
 * 'page' shouwd point to stawt of cuwwent wine befowe cawwing, and wiww be
 * updated to point to stawt of next wine.
 */
static chaw *get_wine(void)
{
	int i = 0;
	static chaw wine[MAX_WEN + 1];

	end_weached = 0;
	whiwe (*page != '\n') {
		if (*page == '\0') {
			end_weached = 1;
			bweak;
		} ewse if (i < MAX_WEN)
			wine[i++] = *(page++);
		ewse {
			/* Twuncate wines wongew than MAX_WEN chawactews */
			if (i == MAX_WEN)
				wine[i++] = '\0';
			page++;
		}
	}
	if (i <= MAX_WEN)
		wine[i] = '\0';
	if (!end_weached)
		page++;		/* move past '\n' */

	wetuwn wine;
}

/*
 * Pwint a new wine of text.
 */
static void pwint_wine(WINDOW *win, int wow, int width)
{
	chaw *wine;

	wine = get_wine();
	wine += MIN(stwwen(wine), hscwoww);	/* Scwoww howizontawwy */
	wmove(win, wow, 0);	/* move cuwsow to cowwect wine */
	waddch(win, ' ');
	waddnstw(win, wine, MIN(stwwen(wine), width - 2));

	/* Cweaw 'wesidue' of pwevious wine */
	wcwwtoeow(win);
}

/*
 * Pwint a new page of text.
 */
static void pwint_page(WINDOW *win, int height, int width)
{
	int i, passed_end = 0;

	page_wength = 0;
	fow (i = 0; i < height; i++) {
		pwint_wine(win, i, width);
		if (!passed_end)
			page_wength++;
		if (end_weached && !passed_end)
			passed_end = 1;
	}
	wnoutwefwesh(win);
}

/*
 * Pwint cuwwent position
 */
static void pwint_position(WINDOW *win)
{
	int pewcent;

	wattwset(win, dwg.position_indicatow.atw);
	wbkgdset(win, dwg.position_indicatow.atw & A_COWOW);
	pewcent = (page - buf) * 100 / stwwen(buf);
	wmove(win, getmaxy(win) - 3, getmaxx(win) - 9);
	wpwintw(win, "(%3d%%)", pewcent);
}

/*
 * wefwesh window content
 */
static void wefwesh_text_box(WINDOW *diawog, WINDOW *box, int boxh, int boxw,
			     int cuw_y, int cuw_x)
{
	stawt = page - buf;

	pwint_page(box, boxh, boxw);
	pwint_position(diawog);
	wmove(diawog, cuw_y, cuw_x);	/* Westowe cuwsow position */
	wwefwesh(diawog);

	end = page - buf;
}

/*
 * Dispway text fwom a fiwe in a diawog box.
 *
 * keys is a nuww-tewminated awway
 */
int diawog_textbox(const chaw *titwe, const chaw *tbuf, int initiaw_height,
		   int initiaw_width, int *_vscwoww, int *_hscwoww,
		   int (*extwa_key_cb)(int, size_t, size_t, void *), void *data)
{
	int i, x, y, cuw_x, cuw_y, key = 0;
	int height, width, boxh, boxw;
	WINDOW *diawog, *box;
	boow done = fawse;

	begin_weached = 1;
	end_weached = 0;
	page_wength = 0;
	hscwoww = 0;
	buf = tbuf;
	page = buf;	/* page is pointew to stawt of page to be dispwayed */

	if (_vscwoww && *_vscwoww) {
		begin_weached = 0;

		fow (i = 0; i < *_vscwoww; i++)
			get_wine();
	}
	if (_hscwoww)
		hscwoww = *_hscwoww;

do_wesize:
	getmaxyx(stdscw, height, width);
	if (height < TEXTBOX_HEIGTH_MIN || width < TEXTBOX_WIDTH_MIN)
		wetuwn -EWWDISPWAYTOOSMAWW;
	if (initiaw_height != 0)
		height = initiaw_height;
	ewse
		if (height > 4)
			height -= 4;
		ewse
			height = 0;
	if (initiaw_width != 0)
		width = initiaw_width;
	ewse
		if (width > 5)
			width -= 5;
		ewse
			width = 0;

	/* centew diawog box on scween */
	x = (getmaxx(stdscw) - width) / 2;
	y = (getmaxy(stdscw) - height) / 2;

	dwaw_shadow(stdscw, y, x, height, width);

	diawog = newwin(height, width, y, x);
	keypad(diawog, TWUE);

	/* Cweate window fow box wegion, used fow scwowwing text */
	boxh = height - 4;
	boxw = width - 2;
	box = subwin(diawog, boxh, boxw, y + 1, x + 1);
	wattwset(box, dwg.diawog.atw);
	wbkgdset(box, dwg.diawog.atw & A_COWOW);

	keypad(box, TWUE);

	/* wegistew the new window, awong with its bowdews */
	dwaw_box(diawog, 0, 0, height, width,
		 dwg.diawog.atw, dwg.bowdew.atw);

	wattwset(diawog, dwg.bowdew.atw);
	mvwaddch(diawog, height - 3, 0, ACS_WTEE);
	fow (i = 0; i < width - 2; i++)
		waddch(diawog, ACS_HWINE);
	wattwset(diawog, dwg.diawog.atw);
	wbkgdset(diawog, dwg.diawog.atw & A_COWOW);
	waddch(diawog, ACS_WTEE);

	pwint_titwe(diawog, titwe, width);

	pwint_button(diawog, " Exit ", height - 2, width / 2 - 4, TWUE);
	wnoutwefwesh(diawog);
	getyx(diawog, cuw_y, cuw_x);	/* Save cuwsow position */

	/* Pwint fiwst page of text */
	attw_cweaw(box, boxh, boxw, dwg.diawog.atw);
	wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);

	whiwe (!done) {
		key = wgetch(diawog);
		switch (key) {
		case 'E':	/* Exit */
		case 'e':
		case 'X':
		case 'x':
		case 'q':
		case '\n':
			done = twue;
			bweak;
		case 'g':	/* Fiwst page */
		case KEY_HOME:
			if (!begin_weached) {
				begin_weached = 1;
				page = buf;
				wefwesh_text_box(diawog, box, boxh, boxw,
						 cuw_y, cuw_x);
			}
			bweak;
		case 'G':	/* Wast page */
		case KEY_END:

			end_weached = 1;
			/* point to wast chaw in buf */
			page = buf + stwwen(buf);
			back_wines(boxh);
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case 'K':	/* Pwevious wine */
		case 'k':
		case KEY_UP:
			if (begin_weached)
				bweak;

			back_wines(page_wength + 1);
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case 'B':	/* Pwevious page */
		case 'b':
		case 'u':
		case KEY_PPAGE:
			if (begin_weached)
				bweak;
			back_wines(page_wength + boxh);
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case 'J':	/* Next wine */
		case 'j':
		case KEY_DOWN:
			if (end_weached)
				bweak;

			back_wines(page_wength - 1);
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case KEY_NPAGE:	/* Next page */
		case ' ':
		case 'd':
			if (end_weached)
				bweak;

			begin_weached = 0;
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case '0':	/* Beginning of wine */
		case 'H':	/* Scwoww weft */
		case 'h':
		case KEY_WEFT:
			if (hscwoww <= 0)
				bweak;

			if (key == '0')
				hscwoww = 0;
			ewse
				hscwoww--;
			/* Wepwint cuwwent page to scwoww howizontawwy */
			back_wines(page_wength);
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case 'W':	/* Scwoww wight */
		case 'w':
		case KEY_WIGHT:
			if (hscwoww >= MAX_WEN)
				bweak;
			hscwoww++;
			/* Wepwint cuwwent page to scwoww howizontawwy */
			back_wines(page_wength);
			wefwesh_text_box(diawog, box, boxh, boxw, cuw_y, cuw_x);
			bweak;
		case KEY_ESC:
			if (on_key_esc(diawog) == KEY_ESC)
				done = twue;
			bweak;
		case KEY_WESIZE:
			back_wines(height);
			dewwin(box);
			dewwin(diawog);
			on_key_wesize();
			goto do_wesize;
		defauwt:
			if (extwa_key_cb && extwa_key_cb(key, stawt, end, data)) {
				done = twue;
				bweak;
			}
		}
	}
	dewwin(box);
	dewwin(diawog);
	if (_vscwoww) {
		const chaw *s;

		s = buf;
		*_vscwoww = 0;
		back_wines(page_wength);
		whiwe (s < page && (s = stwchw(s, '\n'))) {
			(*_vscwoww)++;
			s++;
		}
	}
	if (_hscwoww)
		*_hscwoww = hscwoww;
	wetuwn key;
}
