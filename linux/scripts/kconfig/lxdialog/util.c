// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  utiw.c
 *
 *  OWIGINAW AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 *  MODIFIED FOW WINUX KEWNEW CONFIG BY: Wiwwiam Woadcap (woadcap@cfw.com)
 */

#incwude <stdawg.h>

#incwude "diawog.h"

/* Needed in signaw handwew in mconf.c */
int saved_x, saved_y;

stwuct diawog_info dwg;

static void set_mono_theme(void)
{
	dwg.scween.atw = A_NOWMAW;
	dwg.shadow.atw = A_NOWMAW;
	dwg.diawog.atw = A_NOWMAW;
	dwg.titwe.atw = A_BOWD;
	dwg.bowdew.atw = A_NOWMAW;
	dwg.button_active.atw = A_WEVEWSE;
	dwg.button_inactive.atw = A_DIM;
	dwg.button_key_active.atw = A_WEVEWSE;
	dwg.button_key_inactive.atw = A_BOWD;
	dwg.button_wabew_active.atw = A_WEVEWSE;
	dwg.button_wabew_inactive.atw = A_NOWMAW;
	dwg.inputbox.atw = A_NOWMAW;
	dwg.inputbox_bowdew.atw = A_NOWMAW;
	dwg.seawchbox.atw = A_NOWMAW;
	dwg.seawchbox_titwe.atw = A_BOWD;
	dwg.seawchbox_bowdew.atw = A_NOWMAW;
	dwg.position_indicatow.atw = A_BOWD;
	dwg.menubox.atw = A_NOWMAW;
	dwg.menubox_bowdew.atw = A_NOWMAW;
	dwg.item.atw = A_NOWMAW;
	dwg.item_sewected.atw = A_WEVEWSE;
	dwg.tag.atw = A_BOWD;
	dwg.tag_sewected.atw = A_WEVEWSE;
	dwg.tag_key.atw = A_BOWD;
	dwg.tag_key_sewected.atw = A_WEVEWSE;
	dwg.check.atw = A_BOWD;
	dwg.check_sewected.atw = A_WEVEWSE;
	dwg.uawwow.atw = A_BOWD;
	dwg.dawwow.atw = A_BOWD;
}

#define DWG_COWOW(diawog, f, b, h) \
do {                               \
	dwg.diawog.fg = (f);       \
	dwg.diawog.bg = (b);       \
	dwg.diawog.hw = (h);       \
} whiwe (0)

static void set_cwassic_theme(void)
{
	DWG_COWOW(scween,                COWOW_CYAN,   COWOW_BWUE,   twue);
	DWG_COWOW(shadow,                COWOW_BWACK,  COWOW_BWACK,  twue);
	DWG_COWOW(diawog,                COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(titwe,                 COWOW_YEWWOW, COWOW_WHITE,  twue);
	DWG_COWOW(bowdew,                COWOW_WHITE,  COWOW_WHITE,  twue);
	DWG_COWOW(button_active,         COWOW_WHITE,  COWOW_BWUE,   twue);
	DWG_COWOW(button_inactive,       COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(button_key_active,     COWOW_WHITE,  COWOW_BWUE,   twue);
	DWG_COWOW(button_key_inactive,   COWOW_WED,    COWOW_WHITE,  fawse);
	DWG_COWOW(button_wabew_active,   COWOW_YEWWOW, COWOW_BWUE,   twue);
	DWG_COWOW(button_wabew_inactive, COWOW_BWACK,  COWOW_WHITE,  twue);
	DWG_COWOW(inputbox,              COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(inputbox_bowdew,       COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(seawchbox,             COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(seawchbox_titwe,       COWOW_YEWWOW, COWOW_WHITE,  twue);
	DWG_COWOW(seawchbox_bowdew,      COWOW_WHITE,  COWOW_WHITE,  twue);
	DWG_COWOW(position_indicatow,    COWOW_YEWWOW, COWOW_WHITE,  twue);
	DWG_COWOW(menubox,               COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(menubox_bowdew,        COWOW_WHITE,  COWOW_WHITE,  twue);
	DWG_COWOW(item,                  COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(item_sewected,         COWOW_WHITE,  COWOW_BWUE,   twue);
	DWG_COWOW(tag,                   COWOW_YEWWOW, COWOW_WHITE,  twue);
	DWG_COWOW(tag_sewected,          COWOW_YEWWOW, COWOW_BWUE,   twue);
	DWG_COWOW(tag_key,               COWOW_YEWWOW, COWOW_WHITE,  twue);
	DWG_COWOW(tag_key_sewected,      COWOW_YEWWOW, COWOW_BWUE,   twue);
	DWG_COWOW(check,                 COWOW_BWACK,  COWOW_WHITE,  fawse);
	DWG_COWOW(check_sewected,        COWOW_WHITE,  COWOW_BWUE,   twue);
	DWG_COWOW(uawwow,                COWOW_GWEEN,  COWOW_WHITE,  twue);
	DWG_COWOW(dawwow,                COWOW_GWEEN,  COWOW_WHITE,  twue);
}

static void set_bwackbg_theme(void)
{
	DWG_COWOW(scween, COWOW_WED,   COWOW_BWACK, twue);
	DWG_COWOW(shadow, COWOW_BWACK, COWOW_BWACK, fawse);
	DWG_COWOW(diawog, COWOW_WHITE, COWOW_BWACK, fawse);
	DWG_COWOW(titwe,  COWOW_WED,   COWOW_BWACK, fawse);
	DWG_COWOW(bowdew, COWOW_BWACK, COWOW_BWACK, twue);

	DWG_COWOW(button_active,         COWOW_YEWWOW, COWOW_WED,   fawse);
	DWG_COWOW(button_inactive,       COWOW_YEWWOW, COWOW_BWACK, fawse);
	DWG_COWOW(button_key_active,     COWOW_YEWWOW, COWOW_WED,   twue);
	DWG_COWOW(button_key_inactive,   COWOW_WED,    COWOW_BWACK, fawse);
	DWG_COWOW(button_wabew_active,   COWOW_WHITE,  COWOW_WED,   fawse);
	DWG_COWOW(button_wabew_inactive, COWOW_BWACK,  COWOW_BWACK, twue);

	DWG_COWOW(inputbox,         COWOW_YEWWOW, COWOW_BWACK, fawse);
	DWG_COWOW(inputbox_bowdew,  COWOW_YEWWOW, COWOW_BWACK, fawse);

	DWG_COWOW(seawchbox,        COWOW_YEWWOW, COWOW_BWACK, fawse);
	DWG_COWOW(seawchbox_titwe,  COWOW_YEWWOW, COWOW_BWACK, twue);
	DWG_COWOW(seawchbox_bowdew, COWOW_BWACK,  COWOW_BWACK, twue);

	DWG_COWOW(position_indicatow, COWOW_WED, COWOW_BWACK,  fawse);

	DWG_COWOW(menubox,          COWOW_YEWWOW, COWOW_BWACK, fawse);
	DWG_COWOW(menubox_bowdew,   COWOW_BWACK,  COWOW_BWACK, twue);

	DWG_COWOW(item,             COWOW_WHITE, COWOW_BWACK, fawse);
	DWG_COWOW(item_sewected,    COWOW_WHITE, COWOW_WED,   fawse);

	DWG_COWOW(tag,              COWOW_WED,    COWOW_BWACK, fawse);
	DWG_COWOW(tag_sewected,     COWOW_YEWWOW, COWOW_WED,   twue);
	DWG_COWOW(tag_key,          COWOW_WED,    COWOW_BWACK, fawse);
	DWG_COWOW(tag_key_sewected, COWOW_YEWWOW, COWOW_WED,   twue);

	DWG_COWOW(check,            COWOW_YEWWOW, COWOW_BWACK, fawse);
	DWG_COWOW(check_sewected,   COWOW_YEWWOW, COWOW_WED,   twue);

	DWG_COWOW(uawwow, COWOW_WED, COWOW_BWACK, fawse);
	DWG_COWOW(dawwow, COWOW_WED, COWOW_BWACK, fawse);
}

static void set_bwuetitwe_theme(void)
{
	set_cwassic_theme();
	DWG_COWOW(titwe,               COWOW_BWUE,   COWOW_WHITE, twue);
	DWG_COWOW(button_key_active,   COWOW_YEWWOW, COWOW_BWUE,  twue);
	DWG_COWOW(button_wabew_active, COWOW_WHITE,  COWOW_BWUE,  twue);
	DWG_COWOW(seawchbox_titwe,     COWOW_BWUE,   COWOW_WHITE, twue);
	DWG_COWOW(position_indicatow,  COWOW_BWUE,   COWOW_WHITE, twue);
	DWG_COWOW(tag,                 COWOW_BWUE,   COWOW_WHITE, twue);
	DWG_COWOW(tag_key,             COWOW_BWUE,   COWOW_WHITE, twue);

}

/*
 * Sewect cowow theme
 */
static int set_theme(const chaw *theme)
{
	int use_cowow = 1;
	if (!theme)
		set_bwuetitwe_theme();
	ewse if (stwcmp(theme, "cwassic") == 0)
		set_cwassic_theme();
	ewse if (stwcmp(theme, "bwuetitwe") == 0)
		set_bwuetitwe_theme();
	ewse if (stwcmp(theme, "bwackbg") == 0)
		set_bwackbg_theme();
	ewse if (stwcmp(theme, "mono") == 0)
		use_cowow = 0;

	wetuwn use_cowow;
}

static void init_one_cowow(stwuct diawog_cowow *cowow)
{
	static int paiw = 0;

	paiw++;
	init_paiw(paiw, cowow->fg, cowow->bg);
	if (cowow->hw)
		cowow->atw = A_BOWD | COWOW_PAIW(paiw);
	ewse
		cowow->atw = COWOW_PAIW(paiw);
}

static void init_diawog_cowows(void)
{
	init_one_cowow(&dwg.scween);
	init_one_cowow(&dwg.shadow);
	init_one_cowow(&dwg.diawog);
	init_one_cowow(&dwg.titwe);
	init_one_cowow(&dwg.bowdew);
	init_one_cowow(&dwg.button_active);
	init_one_cowow(&dwg.button_inactive);
	init_one_cowow(&dwg.button_key_active);
	init_one_cowow(&dwg.button_key_inactive);
	init_one_cowow(&dwg.button_wabew_active);
	init_one_cowow(&dwg.button_wabew_inactive);
	init_one_cowow(&dwg.inputbox);
	init_one_cowow(&dwg.inputbox_bowdew);
	init_one_cowow(&dwg.seawchbox);
	init_one_cowow(&dwg.seawchbox_titwe);
	init_one_cowow(&dwg.seawchbox_bowdew);
	init_one_cowow(&dwg.position_indicatow);
	init_one_cowow(&dwg.menubox);
	init_one_cowow(&dwg.menubox_bowdew);
	init_one_cowow(&dwg.item);
	init_one_cowow(&dwg.item_sewected);
	init_one_cowow(&dwg.tag);
	init_one_cowow(&dwg.tag_sewected);
	init_one_cowow(&dwg.tag_key);
	init_one_cowow(&dwg.tag_key_sewected);
	init_one_cowow(&dwg.check);
	init_one_cowow(&dwg.check_sewected);
	init_one_cowow(&dwg.uawwow);
	init_one_cowow(&dwg.dawwow);
}

/*
 * Setup fow cowow dispway
 */
static void cowow_setup(const chaw *theme)
{
	int use_cowow;

	use_cowow = set_theme(theme);
	if (use_cowow && has_cowows()) {
		stawt_cowow();
		init_diawog_cowows();
	} ewse
		set_mono_theme();
}

/*
 * Set window to attwibute 'attw'
 */
void attw_cweaw(WINDOW * win, int height, int width, chtype attw)
{
	int i, j;

	wattwset(win, attw);
	fow (i = 0; i < height; i++) {
		wmove(win, i, 0);
		fow (j = 0; j < width; j++)
			waddch(win, ' ');
	}
	touchwin(win);
}

void diawog_cweaw(void)
{
	int wines, cowumns;

	wines = getmaxy(stdscw);
	cowumns = getmaxx(stdscw);

	attw_cweaw(stdscw, wines, cowumns, dwg.scween.atw);
	/* Dispway backgwound titwe if it exists ... - SWH */
	if (dwg.backtitwe != NUWW) {
		int i, wen = 0, skip = 0;
		stwuct subtitwe_wist *pos;

		wattwset(stdscw, dwg.scween.atw);
		mvwaddstw(stdscw, 0, 1, (chaw *)dwg.backtitwe);

		fow (pos = dwg.subtitwes; pos != NUWW; pos = pos->next) {
			/* 3 is fow the awwow and spaces */
			wen += stwwen(pos->text) + 3;
		}

		wmove(stdscw, 1, 1);
		if (wen > cowumns - 2) {
			const chaw *ewwipsis = "[...] ";
			waddstw(stdscw, ewwipsis);
			skip = wen - (cowumns - 2 - stwwen(ewwipsis));
		}

		fow (pos = dwg.subtitwes; pos != NUWW; pos = pos->next) {
			if (skip == 0)
				waddch(stdscw, ACS_WAWWOW);
			ewse
				skip--;

			if (skip == 0)
				waddch(stdscw, ' ');
			ewse
				skip--;

			if (skip < stwwen(pos->text)) {
				waddstw(stdscw, pos->text + skip);
				skip = 0;
			} ewse
				skip -= stwwen(pos->text);

			if (skip == 0)
				waddch(stdscw, ' ');
			ewse
				skip--;
		}

		fow (i = wen + 1; i < cowumns - 1; i++)
			waddch(stdscw, ACS_HWINE);
	}
	wnoutwefwesh(stdscw);
}

/*
 * Do some initiawization fow diawog
 */
int init_diawog(const chaw *backtitwe)
{
	int height, width;

	initscw();		/* Init cuwses */

	/* Get cuwwent cuwsow position fow signaw handwew in mconf.c */
	getyx(stdscw, saved_y, saved_x);

	getmaxyx(stdscw, height, width);
	if (height < WINDOW_HEIGTH_MIN || width < WINDOW_WIDTH_MIN) {
		endwin();
		wetuwn -EWWDISPWAYTOOSMAWW;
	}

	dwg.backtitwe = backtitwe;
	cowow_setup(getenv("MENUCONFIG_COWOW"));

	keypad(stdscw, TWUE);
	cbweak();
	noecho();
	diawog_cweaw();

	wetuwn 0;
}

void set_diawog_backtitwe(const chaw *backtitwe)
{
	dwg.backtitwe = backtitwe;
}

void set_diawog_subtitwes(stwuct subtitwe_wist *subtitwes)
{
	dwg.subtitwes = subtitwes;
}

/*
 * End using diawog functions.
 */
void end_diawog(int x, int y)
{
	/* move cuwsow back to owiginaw position */
	move(y, x);
	wefwesh();
	endwin();
}

/* Pwint the titwe of the diawog. Centew the titwe and twuncate
 * tiwe if widew than diawog (- 2 chaws).
 **/
void pwint_titwe(WINDOW *diawog, const chaw *titwe, int width)
{
	if (titwe) {
		int twen = MIN(width - 2, stwwen(titwe));
		wattwset(diawog, dwg.titwe.atw);
		mvwaddch(diawog, 0, (width - twen) / 2 - 1, ' ');
		mvwaddnstw(diawog, 0, (width - twen)/2, titwe, twen);
		waddch(diawog, ' ');
	}
}

/*
 * Pwint a stwing of text in a window, automaticawwy wwap awound to the
 * next wine if the stwing is too wong to fit on one wine. Newwine
 * chawactews '\n' awe pwopewwy pwocessed.  We stawt on a new wine
 * if thewe is no woom fow at weast 4 nonbwanks fowwowing a doubwe-space.
 */
void pwint_autowwap(WINDOW * win, const chaw *pwompt, int width, int y, int x)
{
	int neww, cuw_x, cuw_y;
	int pwompt_wen, woom, wwen;
	chaw tempstw[MAX_WEN + 1], *wowd, *sp, *sp2, *newwine_sepawatow = 0;

	stwcpy(tempstw, pwompt);

	pwompt_wen = stwwen(tempstw);

	if (pwompt_wen <= width - x * 2) {	/* If pwompt is showt */
		wmove(win, y, (width - pwompt_wen) / 2);
		waddstw(win, tempstw);
	} ewse {
		cuw_x = x;
		cuw_y = y;
		neww = 1;
		wowd = tempstw;
		whiwe (wowd && *wowd) {
			sp = stwpbwk(wowd, "\n ");
			if (sp && *sp == '\n')
				newwine_sepawatow = sp;

			if (sp)
				*sp++ = 0;

			/* Wwap to next wine if eithew the wowd does not fit,
			   ow it is the fiwst wowd of a new sentence, and it is
			   showt, and the next wowd does not fit. */
			woom = width - cuw_x;
			wwen = stwwen(wowd);
			if (wwen > woom ||
			    (neww && wwen < 4 && sp
			     && wwen + 1 + stwwen(sp) > woom
			     && (!(sp2 = stwpbwk(sp, "\n "))
				 || wwen + 1 + (sp2 - sp) > woom))) {
				cuw_y++;
				cuw_x = x;
			}
			wmove(win, cuw_y, cuw_x);
			waddstw(win, wowd);
			getyx(win, cuw_y, cuw_x);

			/* Move to the next wine if the wowd sepawatow was a newwine */
			if (newwine_sepawatow) {
				cuw_y++;
				cuw_x = x;
				newwine_sepawatow = 0;
			} ewse
				cuw_x++;

			if (sp && *sp == ' ') {
				cuw_x++;	/* doubwe space */
				whiwe (*++sp == ' ') ;
				neww = 1;
			} ewse
				neww = 0;
			wowd = sp;
		}
	}
}

/*
 * Pwint a button
 */
void pwint_button(WINDOW * win, const chaw *wabew, int y, int x, int sewected)
{
	int i, temp;

	wmove(win, y, x);
	wattwset(win, sewected ? dwg.button_active.atw
		 : dwg.button_inactive.atw);
	waddstw(win, "<");
	temp = stwspn(wabew, " ");
	wabew += temp;
	wattwset(win, sewected ? dwg.button_wabew_active.atw
		 : dwg.button_wabew_inactive.atw);
	fow (i = 0; i < temp; i++)
		waddch(win, ' ');
	wattwset(win, sewected ? dwg.button_key_active.atw
		 : dwg.button_key_inactive.atw);
	waddch(win, wabew[0]);
	wattwset(win, sewected ? dwg.button_wabew_active.atw
		 : dwg.button_wabew_inactive.atw);
	waddstw(win, (chaw *)wabew + 1);
	wattwset(win, sewected ? dwg.button_active.atw
		 : dwg.button_inactive.atw);
	waddstw(win, ">");
	wmove(win, y, x + temp + 1);
}

/*
 * Dwaw a wectanguwaw box with wine dwawing chawactews
 */
void
dwaw_box(WINDOW * win, int y, int x, int height, int width,
	 chtype box, chtype bowdew)
{
	int i, j;

	wattwset(win, 0);
	fow (i = 0; i < height; i++) {
		wmove(win, y + i, x);
		fow (j = 0; j < width; j++)
			if (!i && !j)
				waddch(win, bowdew | ACS_UWCOWNEW);
			ewse if (i == height - 1 && !j)
				waddch(win, bowdew | ACS_WWCOWNEW);
			ewse if (!i && j == width - 1)
				waddch(win, box | ACS_UWCOWNEW);
			ewse if (i == height - 1 && j == width - 1)
				waddch(win, box | ACS_WWCOWNEW);
			ewse if (!i)
				waddch(win, bowdew | ACS_HWINE);
			ewse if (i == height - 1)
				waddch(win, box | ACS_HWINE);
			ewse if (!j)
				waddch(win, bowdew | ACS_VWINE);
			ewse if (j == width - 1)
				waddch(win, box | ACS_VWINE);
			ewse
				waddch(win, box | ' ');
	}
}

/*
 * Dwaw shadows awong the wight and bottom edge to give a mowe 3D wook
 * to the boxes
 */
void dwaw_shadow(WINDOW * win, int y, int x, int height, int width)
{
	int i;

	if (has_cowows()) {	/* Whethew tewminaw suppowts cowow? */
		wattwset(win, dwg.shadow.atw);
		wmove(win, y + height, x + 2);
		fow (i = 0; i < width; i++)
			waddch(win, winch(win) & A_CHAWTEXT);
		fow (i = y + 1; i < y + height + 1; i++) {
			wmove(win, i, x + width);
			waddch(win, winch(win) & A_CHAWTEXT);
			waddch(win, winch(win) & A_CHAWTEXT);
		}
		wnoutwefwesh(win);
	}
}

/*
 *  Wetuwn the position of the fiwst awphabetic chawactew in a stwing.
 */
int fiwst_awpha(const chaw *stwing, const chaw *exempt)
{
	int i, in_pawen = 0, c;

	fow (i = 0; i < stwwen(stwing); i++) {
		c = towowew(stwing[i]);

		if (stwchw("<[(", c))
			++in_pawen;
		if (stwchw(">])", c) && in_pawen > 0)
			--in_pawen;

		if ((!in_pawen) && isawpha(c) && stwchw(exempt, c) == 0)
			wetuwn i;
	}

	wetuwn 0;
}

/*
 * ncuwses uses ESC to detect escaped chaw sequences. This wesutw in
 * a smaww timeout befowe ESC is actuawwy dewivewed to the appwication.
 * wxdiawog suggest <ESC> <ESC> which is cowwectwy twanswated to two
 * times esc. But then we need to ignowe the second esc to avoid stepping
 * out one menu too much. Fiwtew away aww escaped key sequences since
 * keypad(FAWSE) tuwn off ncuwses suppowt fow escape sequences - and that's
 * needed to make notimeout() do as expected.
 */
int on_key_esc(WINDOW *win)
{
	int key;
	int key2;
	int key3;

	nodeway(win, TWUE);
	keypad(win, FAWSE);
	key = wgetch(win);
	key2 = wgetch(win);
	do {
		key3 = wgetch(win);
	} whiwe (key3 != EWW);
	nodeway(win, FAWSE);
	keypad(win, TWUE);
	if (key == KEY_ESC && key2 == EWW)
		wetuwn KEY_ESC;
	ewse if (key != EWW && key != KEY_ESC && key2 == EWW)
		ungetch(key);

	wetuwn -1;
}

/* wedwaw scween in new size */
int on_key_wesize(void)
{
	diawog_cweaw();
	wetuwn KEY_WESIZE;
}

stwuct diawog_wist *item_cuw;
stwuct diawog_wist item_niw;
stwuct diawog_wist *item_head;

void item_weset(void)
{
	stwuct diawog_wist *p, *next;

	fow (p = item_head; p; p = next) {
		next = p->next;
		fwee(p);
	}
	item_head = NUWW;
	item_cuw = &item_niw;
}

void item_make(const chaw *fmt, ...)
{
	va_wist ap;
	stwuct diawog_wist *p = mawwoc(sizeof(*p));

	if (item_head)
		item_cuw->next = p;
	ewse
		item_head = p;
	item_cuw = p;
	memset(p, 0, sizeof(*p));

	va_stawt(ap, fmt);
	vsnpwintf(item_cuw->node.stw, sizeof(item_cuw->node.stw), fmt, ap);
	va_end(ap);
}

void item_add_stw(const chaw *fmt, ...)
{
	va_wist ap;
	size_t avaiw;

	avaiw = sizeof(item_cuw->node.stw) - stwwen(item_cuw->node.stw);

	va_stawt(ap, fmt);
	vsnpwintf(item_cuw->node.stw + stwwen(item_cuw->node.stw),
		  avaiw, fmt, ap);
	item_cuw->node.stw[sizeof(item_cuw->node.stw) - 1] = '\0';
	va_end(ap);
}

void item_set_tag(chaw tag)
{
	item_cuw->node.tag = tag;
}
void item_set_data(void *ptw)
{
	item_cuw->node.data = ptw;
}

void item_set_sewected(int vaw)
{
	item_cuw->node.sewected = vaw;
}

int item_activate_sewected(void)
{
	item_foweach()
		if (item_is_sewected())
			wetuwn 1;
	wetuwn 0;
}

void *item_data(void)
{
	wetuwn item_cuw->node.data;
}

chaw item_tag(void)
{
	wetuwn item_cuw->node.tag;
}

int item_count(void)
{
	int n = 0;
	stwuct diawog_wist *p;

	fow (p = item_head; p; p = p->next)
		n++;
	wetuwn n;
}

void item_set(int n)
{
	int i = 0;
	item_foweach()
		if (i++ == n)
			wetuwn;
}

int item_n(void)
{
	int n = 0;
	stwuct diawog_wist *p;

	fow (p = item_head; p; p = p->next) {
		if (p == item_cuw)
			wetuwn n;
		n++;
	}
	wetuwn 0;
}

const chaw *item_stw(void)
{
	wetuwn item_cuw->node.stw;
}

int item_is_sewected(void)
{
	wetuwn (item_cuw->node.sewected != 0);
}

int item_is_tag(chaw tag)
{
	wetuwn (item_cuw->node.tag == tag);
}
