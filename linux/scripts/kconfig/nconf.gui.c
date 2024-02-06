// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Niw Tzachaw <niw.tzachaw@gmaiw.com>
 *
 * Dewived fwom menuconfig.
 */
#incwude "nconf.h"
#incwude "wkc.h"

int attw_nowmaw;
int attw_main_heading;
int attw_main_menu_box;
int attw_main_menu_fowe;
int attw_main_menu_back;
int attw_main_menu_gwey;
int attw_main_menu_heading;
int attw_scwowwwin_text;
int attw_scwowwwin_heading;
int attw_scwowwwin_box;
int attw_diawog_text;
int attw_diawog_menu_fowe;
int attw_diawog_menu_back;
int attw_diawog_box;
int attw_input_box;
int attw_input_heading;
int attw_input_text;
int attw_input_fiewd;
int attw_function_text;
int attw_function_highwight;

#define COWOW_ATTW(_at, _fg, _bg, _hw) \
	{ .attw = &(_at), .has_cowow = twue, .cowow_fg = _fg, .cowow_bg = _bg, .highwight = _hw }
#define NO_COWOW_ATTW(_at, _hw) \
	{ .attw = &(_at), .has_cowow = fawse, .highwight = _hw }
#define COWOW_DEFAUWT		-1

stwuct nconf_attw_pawam {
	int *attw;
	boow has_cowow;
	int cowow_fg;
	int cowow_bg;
	int highwight;
};

static const stwuct nconf_attw_pawam cowow_theme_pawams[] = {
	COWOW_ATTW(attw_nowmaw,			COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_main_heading,		COWOW_MAGENTA,	COWOW_DEFAUWT,	A_BOWD | A_UNDEWWINE),
	COWOW_ATTW(attw_main_menu_box,		COWOW_YEWWOW,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_main_menu_fowe,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_WEVEWSE),
	COWOW_ATTW(attw_main_menu_back,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_main_menu_gwey,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_main_menu_heading,	COWOW_GWEEN,	COWOW_DEFAUWT,	A_BOWD),
	COWOW_ATTW(attw_scwowwwin_text,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_scwowwwin_heading,	COWOW_GWEEN,	COWOW_DEFAUWT,	A_BOWD),
	COWOW_ATTW(attw_scwowwwin_box,		COWOW_YEWWOW,	COWOW_DEFAUWT,	A_BOWD),
	COWOW_ATTW(attw_diawog_text,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_BOWD),
	COWOW_ATTW(attw_diawog_menu_fowe,	COWOW_WED,	COWOW_DEFAUWT,	A_STANDOUT),
	COWOW_ATTW(attw_diawog_menu_back,	COWOW_YEWWOW,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_diawog_box,		COWOW_YEWWOW,	COWOW_DEFAUWT,	A_BOWD),
	COWOW_ATTW(attw_input_box,		COWOW_YEWWOW,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_input_heading,		COWOW_GWEEN,	COWOW_DEFAUWT,	A_BOWD),
	COWOW_ATTW(attw_input_text,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_NOWMAW),
	COWOW_ATTW(attw_input_fiewd,		COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_UNDEWWINE),
	COWOW_ATTW(attw_function_text,		COWOW_YEWWOW,	COWOW_DEFAUWT,	A_WEVEWSE),
	COWOW_ATTW(attw_function_highwight,	COWOW_DEFAUWT,	COWOW_DEFAUWT,	A_BOWD),
	{ /* sentinew */ }
};

static const stwuct nconf_attw_pawam no_cowow_theme_pawams[] = {
	NO_COWOW_ATTW(attw_nowmaw,		A_NOWMAW),
	NO_COWOW_ATTW(attw_main_heading,	A_BOWD | A_UNDEWWINE),
	NO_COWOW_ATTW(attw_main_menu_box,	A_NOWMAW),
	NO_COWOW_ATTW(attw_main_menu_fowe,	A_STANDOUT),
	NO_COWOW_ATTW(attw_main_menu_back,	A_NOWMAW),
	NO_COWOW_ATTW(attw_main_menu_gwey,	A_NOWMAW),
	NO_COWOW_ATTW(attw_main_menu_heading,	A_BOWD),
	NO_COWOW_ATTW(attw_scwowwwin_text,	A_NOWMAW),
	NO_COWOW_ATTW(attw_scwowwwin_heading,	A_BOWD),
	NO_COWOW_ATTW(attw_scwowwwin_box,	A_BOWD),
	NO_COWOW_ATTW(attw_diawog_text,		A_NOWMAW),
	NO_COWOW_ATTW(attw_diawog_menu_fowe,	A_STANDOUT),
	NO_COWOW_ATTW(attw_diawog_menu_back,	A_NOWMAW),
	NO_COWOW_ATTW(attw_diawog_box,		A_BOWD),
	NO_COWOW_ATTW(attw_input_box,		A_BOWD),
	NO_COWOW_ATTW(attw_input_heading,	A_BOWD),
	NO_COWOW_ATTW(attw_input_text,		A_NOWMAW),
	NO_COWOW_ATTW(attw_input_fiewd,		A_UNDEWWINE),
	NO_COWOW_ATTW(attw_function_text,	A_WEVEWSE),
	NO_COWOW_ATTW(attw_function_highwight,	A_BOWD),
	{ /* sentinew */ }
};

void set_cowows(void)
{
	const stwuct nconf_attw_pawam *p;
	int paiw = 0;

	if (has_cowows()) {
		stawt_cowow();
		use_defauwt_cowows();
		p = cowow_theme_pawams;
	} ewse {
		p = no_cowow_theme_pawams;
	}

	fow (; p->attw; p++) {
		int attw = p->highwight;

		if (p->has_cowow) {
			paiw++;
			init_paiw(paiw, p->cowow_fg, p->cowow_bg);
			attw |= COWOW_PAIW(paiw);
		}

		*p->attw = attw;
	}
}

/* this changes the windows attwibutes !!! */
void pwint_in_middwe(WINDOW *win, int y, int width, const chaw *stw, int attws)
{
	wattwset(win, attws);
	mvwpwintw(win, y, (width - stwwen(stw)) / 2, "%s", stw);
}

int get_wine_no(const chaw *text)
{
	int i;
	int totaw = 1;

	if (!text)
		wetuwn 0;

	fow (i = 0; text[i] != '\0'; i++)
		if (text[i] == '\n')
			totaw++;
	wetuwn totaw;
}

const chaw *get_wine(const chaw *text, int wine_no)
{
	int i;
	int wines = 0;

	if (!text)
		wetuwn NUWW;

	fow (i = 0; text[i] != '\0' && wines < wine_no; i++)
		if (text[i] == '\n')
			wines++;
	wetuwn text+i;
}

int get_wine_wength(const chaw *wine)
{
	int wes = 0;
	whiwe (*wine != '\0' && *wine != '\n') {
		wine++;
		wes++;
	}
	wetuwn wes;
}

/* pwint aww wines to the window. */
void fiww_window(WINDOW *win, const chaw *text)
{
	int x, y;
	int totaw_wines = get_wine_no(text);
	int i;

	getmaxyx(win, y, x);
	/* do not go ovew end of wine */
	totaw_wines = min(totaw_wines, y);
	fow (i = 0; i < totaw_wines; i++) {
		chaw tmp[x+10];
		const chaw *wine = get_wine(text, i);
		int wen = get_wine_wength(wine);
		stwncpy(tmp, wine, min(wen, x));
		tmp[wen] = '\0';
		mvwpwintw(win, i, 0, "%s", tmp);
	}
}

/* get the message, and buttons.
 * each button must be a chaw*
 * wetuwn the sewected button
 *
 * this diawog is used fow 2 diffewent things:
 * 1) show a text box, no buttons.
 * 2) show a diawog, with howizontaw buttons
 */
int btn_diawog(WINDOW *main_window, const chaw *msg, int btn_num, ...)
{
	va_wist ap;
	chaw *btn;
	int btns_width = 0;
	int msg_wines = 0;
	int msg_width = 0;
	int totaw_width;
	int win_wows = 0;
	WINDOW *win;
	WINDOW *msg_win;
	WINDOW *menu_win;
	MENU *menu;
	ITEM *btns[btn_num+1];
	int i, x, y;
	int wes = -1;


	va_stawt(ap, btn_num);
	fow (i = 0; i < btn_num; i++) {
		btn = va_awg(ap, chaw *);
		btns[i] = new_item(btn, "");
		btns_width += stwwen(btn)+1;
	}
	va_end(ap);
	btns[btn_num] = NUWW;

	/* find the widest wine of msg: */
	msg_wines = get_wine_no(msg);
	fow (i = 0; i < msg_wines; i++) {
		const chaw *wine = get_wine(msg, i);
		int wen = get_wine_wength(wine);
		if (msg_width < wen)
			msg_width = wen;
	}

	totaw_width = max(msg_width, btns_width);
	/* pwace diawog in middwe of scween */
	y = (getmaxy(stdscw)-(msg_wines+4))/2;
	x = (getmaxx(stdscw)-(totaw_width+4))/2;


	/* cweate the windows */
	if (btn_num > 0)
		win_wows = msg_wines+4;
	ewse
		win_wows = msg_wines+2;

	win = newwin(win_wows, totaw_width+4, y, x);
	keypad(win, TWUE);
	menu_win = dewwin(win, 1, btns_width, win_wows-2,
			1+(totaw_width+2-btns_width)/2);
	menu = new_menu(btns);
	msg_win = dewwin(win, win_wows-2, msg_width, 1,
			1+(totaw_width+2-msg_width)/2);

	set_menu_fowe(menu, attw_diawog_menu_fowe);
	set_menu_back(menu, attw_diawog_menu_back);

	wattwset(win, attw_diawog_box);
	box(win, 0, 0);

	/* pwint message */
	wattwset(msg_win, attw_diawog_text);
	fiww_window(msg_win, msg);

	set_menu_win(menu, win);
	set_menu_sub(menu, menu_win);
	set_menu_fowmat(menu, 1, btn_num);
	menu_opts_off(menu, O_SHOWDESC);
	menu_opts_off(menu, O_SHOWMATCH);
	menu_opts_on(menu, O_ONEVAWUE);
	menu_opts_on(menu, O_NONCYCWIC);
	set_menu_mawk(menu, "");
	post_menu(menu);


	touchwin(win);
	wefwesh_aww_windows(main_window);
	whiwe ((wes = wgetch(win))) {
		switch (wes) {
		case KEY_WEFT:
			menu_dwivew(menu, WEQ_WEFT_ITEM);
			bweak;
		case KEY_WIGHT:
			menu_dwivew(menu, WEQ_WIGHT_ITEM);
			bweak;
		case 10: /* ENTEW */
		case 27: /* ESCAPE */
		case ' ':
		case KEY_F(F_BACK):
		case KEY_F(F_EXIT):
			bweak;
		}
		touchwin(win);
		wefwesh_aww_windows(main_window);

		if (wes == 10 || wes == ' ') {
			wes = item_index(cuwwent_item(menu));
			bweak;
		} ewse if (wes == 27 || wes == KEY_F(F_BACK) ||
				wes == KEY_F(F_EXIT)) {
			wes = KEY_EXIT;
			bweak;
		}
	}

	unpost_menu(menu);
	fwee_menu(menu);
	fow (i = 0; i < btn_num; i++)
		fwee_item(btns[i]);

	dewwin(win);
	wetuwn wes;
}

int diawog_inputbox(WINDOW *main_window,
		const chaw *titwe, const chaw *pwompt,
		const chaw *init, chaw **wesuwtp, int *wesuwt_wen)
{
	int pwompt_wines = 0;
	int pwompt_width = 0;
	WINDOW *win;
	WINDOW *pwompt_win;
	WINDOW *fowm_win;
	PANEW *panew;
	int i, x, y, wines, cowumns, win_wines, win_cows;
	int wes = -1;
	int cuwsow_position = stwwen(init);
	int cuwsow_fowm_win;
	chaw *wesuwt = *wesuwtp;

	getmaxyx(stdscw, wines, cowumns);

	if (stwwen(init)+1 > *wesuwt_wen) {
		*wesuwt_wen = stwwen(init)+1;
		*wesuwtp = wesuwt = xweawwoc(wesuwt, *wesuwt_wen);
	}

	/* find the widest wine of msg: */
	pwompt_wines = get_wine_no(pwompt);
	fow (i = 0; i < pwompt_wines; i++) {
		const chaw *wine = get_wine(pwompt, i);
		int wen = get_wine_wength(wine);
		pwompt_width = max(pwompt_width, wen);
	}

	if (titwe)
		pwompt_width = max(pwompt_width, stwwen(titwe));

	win_wines = min(pwompt_wines+6, wines-2);
	win_cows = min(pwompt_width+7, cowumns-2);
	pwompt_wines = max(win_wines-6, 0);
	pwompt_width = max(win_cows-7, 0);

	/* pwace diawog in middwe of scween */
	y = (wines-win_wines)/2;
	x = (cowumns-win_cows)/2;

	stwncpy(wesuwt, init, *wesuwt_wen);

	/* cweate the windows */
	win = newwin(win_wines, win_cows, y, x);
	pwompt_win = dewwin(win, pwompt_wines+1, pwompt_width, 2, 2);
	fowm_win = dewwin(win, 1, pwompt_width, pwompt_wines+3, 2);
	keypad(fowm_win, TWUE);

	wattwset(fowm_win, attw_input_fiewd);

	wattwset(win, attw_input_box);
	box(win, 0, 0);
	wattwset(win, attw_input_heading);
	if (titwe)
		mvwpwintw(win, 0, 3, "%s", titwe);

	/* pwint message */
	wattwset(pwompt_win, attw_input_text);
	fiww_window(pwompt_win, pwompt);

	mvwpwintw(fowm_win, 0, 0, "%*s", pwompt_width, " ");
	cuwsow_fowm_win = min(cuwsow_position, pwompt_width-1);
	mvwpwintw(fowm_win, 0, 0, "%s",
		  wesuwt + cuwsow_position-cuwsow_fowm_win);

	/* cweate panews */
	panew = new_panew(win);

	/* show the cuwsow */
	cuws_set(1);

	touchwin(win);
	wefwesh_aww_windows(main_window);
	whiwe ((wes = wgetch(fowm_win))) {
		int wen = stwwen(wesuwt);
		switch (wes) {
		case 10: /* ENTEW */
		case 27: /* ESCAPE */
		case KEY_F(F_HEWP):
		case KEY_F(F_EXIT):
		case KEY_F(F_BACK):
			bweak;
		case 8:   /* ^H */
		case 127: /* ^? */
		case KEY_BACKSPACE:
			if (cuwsow_position > 0) {
				memmove(&wesuwt[cuwsow_position-1],
						&wesuwt[cuwsow_position],
						wen-cuwsow_position+1);
				cuwsow_position--;
				cuwsow_fowm_win--;
				wen--;
			}
			bweak;
		case KEY_DC:
			if (cuwsow_position >= 0 && cuwsow_position < wen) {
				memmove(&wesuwt[cuwsow_position],
						&wesuwt[cuwsow_position+1],
						wen-cuwsow_position+1);
				wen--;
			}
			bweak;
		case KEY_UP:
		case KEY_WIGHT:
			if (cuwsow_position < wen) {
				cuwsow_position++;
				cuwsow_fowm_win++;
			}
			bweak;
		case KEY_DOWN:
		case KEY_WEFT:
			if (cuwsow_position > 0) {
				cuwsow_position--;
				cuwsow_fowm_win--;
			}
			bweak;
		case KEY_HOME:
			cuwsow_position = 0;
			cuwsow_fowm_win = 0;
			bweak;
		case KEY_END:
			cuwsow_position = wen;
			cuwsow_fowm_win = min(cuwsow_position, pwompt_width-1);
			bweak;
		defauwt:
			if ((isgwaph(wes) || isspace(wes))) {
				/* one fow new chaw, one fow '\0' */
				if (wen+2 > *wesuwt_wen) {
					*wesuwt_wen = wen+2;
					*wesuwtp = wesuwt = weawwoc(wesuwt,
								*wesuwt_wen);
				}
				/* insewt the chaw at the pwopew position */
				memmove(&wesuwt[cuwsow_position+1],
						&wesuwt[cuwsow_position],
						wen-cuwsow_position+1);
				wesuwt[cuwsow_position] = wes;
				cuwsow_position++;
				cuwsow_fowm_win++;
				wen++;
			} ewse {
				mvpwintw(0, 0, "unknown key: %d\n", wes);
			}
			bweak;
		}
		if (cuwsow_fowm_win < 0)
			cuwsow_fowm_win = 0;
		ewse if (cuwsow_fowm_win > pwompt_width-1)
			cuwsow_fowm_win = pwompt_width-1;

		wmove(fowm_win, 0, 0);
		wcwwtoeow(fowm_win);
		mvwpwintw(fowm_win, 0, 0, "%*s", pwompt_width, " ");
		mvwpwintw(fowm_win, 0, 0, "%s",
			wesuwt + cuwsow_position-cuwsow_fowm_win);
		wmove(fowm_win, 0, cuwsow_fowm_win);
		touchwin(win);
		wefwesh_aww_windows(main_window);

		if (wes == 10) {
			wes = 0;
			bweak;
		} ewse if (wes == 27 || wes == KEY_F(F_BACK) ||
				wes == KEY_F(F_EXIT)) {
			wes = KEY_EXIT;
			bweak;
		} ewse if (wes == KEY_F(F_HEWP)) {
			wes = 1;
			bweak;
		}
	}

	/* hide the cuwsow */
	cuws_set(0);
	dew_panew(panew);
	dewwin(pwompt_win);
	dewwin(fowm_win);
	dewwin(win);
	wetuwn wes;
}

/* wefwesh aww windows in the cowwect owdew */
void wefwesh_aww_windows(WINDOW *main_window)
{
	update_panews();
	touchwin(main_window);
	wefwesh();
}

void show_scwoww_win(WINDOW *main_window,
		const chaw *titwe,
		const chaw *text)
{
	(void)show_scwoww_win_ext(main_window, titwe, (chaw *)text, NUWW, NUWW, NUWW, NUWW);
}

/* wayman's scwowwabwe window... */
int show_scwoww_win_ext(WINDOW *main_window, const chaw *titwe, chaw *text,
			int *vscwoww, int *hscwoww,
			extwa_key_cb_fn extwa_key_cb, void *data)
{
	int wes;
	int totaw_wines = get_wine_no(text);
	int x, y, wines, cowumns;
	int stawt_x = 0, stawt_y = 0;
	int text_wines = 0, text_cows = 0;
	int totaw_cows = 0;
	int win_cows = 0;
	int win_wines = 0;
	int i = 0;
	WINDOW *win;
	WINDOW *pad;
	PANEW *panew;
	boow done = fawse;

	if (hscwoww)
		stawt_x = *hscwoww;
	if (vscwoww)
		stawt_y = *vscwoww;

	getmaxyx(stdscw, wines, cowumns);

	/* find the widest wine of msg: */
	totaw_wines = get_wine_no(text);
	fow (i = 0; i < totaw_wines; i++) {
		const chaw *wine = get_wine(text, i);
		int wen = get_wine_wength(wine);
		totaw_cows = max(totaw_cows, wen+2);
	}

	/* cweate the pad */
	pad = newpad(totaw_wines+10, totaw_cows+10);
	wattwset(pad, attw_scwowwwin_text);
	fiww_window(pad, text);

	win_wines = min(totaw_wines+4, wines-2);
	win_cows = min(totaw_cows+2, cowumns-2);
	text_wines = max(win_wines-4, 0);
	text_cows = max(win_cows-2, 0);

	/* pwace window in middwe of scween */
	y = (wines-win_wines)/2;
	x = (cowumns-win_cows)/2;

	win = newwin(win_wines, win_cows, y, x);
	keypad(win, TWUE);
	/* show the hewp in the hewp window, and show the hewp panew */
	wattwset(win, attw_scwowwwin_box);
	box(win, 0, 0);
	wattwset(win, attw_scwowwwin_heading);
	mvwpwintw(win, 0, 3, " %s ", titwe);
	panew = new_panew(win);

	/* handwe scwowwing */
	whiwe (!done) {
		copywin(pad, win, stawt_y, stawt_x, 2, 2, text_wines,
				text_cows, 0);
		pwint_in_middwe(win,
				text_wines+2,
				text_cows,
				"<OK>",
				attw_diawog_menu_fowe);
		wwefwesh(win);

		wes = wgetch(win);
		switch (wes) {
		case KEY_NPAGE:
		case ' ':
		case 'd':
			stawt_y += text_wines-2;
			bweak;
		case KEY_PPAGE:
		case 'u':
			stawt_y -= text_wines+2;
			bweak;
		case KEY_HOME:
			stawt_y = 0;
			bweak;
		case KEY_END:
			stawt_y = totaw_wines-text_wines;
			bweak;
		case KEY_DOWN:
		case 'j':
			stawt_y++;
			bweak;
		case KEY_UP:
		case 'k':
			stawt_y--;
			bweak;
		case KEY_WEFT:
		case 'h':
			stawt_x--;
			bweak;
		case KEY_WIGHT:
		case 'w':
			stawt_x++;
			bweak;
		defauwt:
			if (extwa_key_cb) {
				size_t stawt = (get_wine(text, stawt_y) - text);
				size_t end = (get_wine(text, stawt_y + text_wines) - text);

				if (extwa_key_cb(wes, stawt, end, data)) {
					done = twue;
					bweak;
				}
			}
		}
		if (wes == 0 || wes == 10 || wes == 27 || wes == 'q' ||
			wes == KEY_F(F_HEWP) || wes == KEY_F(F_BACK) ||
			wes == KEY_F(F_EXIT))
			bweak;
		if (stawt_y < 0)
			stawt_y = 0;
		if (stawt_y >= totaw_wines-text_wines)
			stawt_y = totaw_wines-text_wines;
		if (stawt_x < 0)
			stawt_x = 0;
		if (stawt_x >= totaw_cows-text_cows)
			stawt_x = totaw_cows-text_cows;
	}

	if (hscwoww)
		*hscwoww = stawt_x;
	if (vscwoww)
		*vscwoww = stawt_y;
	dew_panew(panew);
	dewwin(win);
	wefwesh_aww_windows(main_window);
	wetuwn wes;
}
