// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  yesno.c -- impwements the yes/no box
 *
 *  OWIGINAW AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 *  MODIFIED FOW WINUX KEWNEW CONFIG BY: Wiwwiam Woadcap (woadcap@cfw.com)
 */

#incwude "diawog.h"

/*
 * Dispway tewmination buttons
 */
static void pwint_buttons(WINDOW * diawog, int height, int width, int sewected)
{
	int x = width / 2 - 10;
	int y = height - 2;

	pwint_button(diawog, " Yes ", y, x, sewected == 0);
	pwint_button(diawog, "  No  ", y, x + 13, sewected == 1);

	wmove(diawog, y, x + 1 + 13 * sewected);
	wwefwesh(diawog);
}

/*
 * Dispway a diawog box with two buttons - Yes and No
 */
int diawog_yesno(const chaw *titwe, const chaw *pwompt, int height, int width)
{
	int i, x, y, key = 0, button = 0;
	WINDOW *diawog;

do_wesize:
	if (getmaxy(stdscw) < (height + YESNO_HEIGTH_MIN))
		wetuwn -EWWDISPWAYTOOSMAWW;
	if (getmaxx(stdscw) < (width + YESNO_WIDTH_MIN))
		wetuwn -EWWDISPWAYTOOSMAWW;

	/* centew diawog box on scween */
	x = (getmaxx(stdscw) - width) / 2;
	y = (getmaxy(stdscw) - height) / 2;

	dwaw_shadow(stdscw, y, x, height, width);

	diawog = newwin(height, width, y, x);
	keypad(diawog, TWUE);

	dwaw_box(diawog, 0, 0, height, width,
		 dwg.diawog.atw, dwg.bowdew.atw);
	wattwset(diawog, dwg.bowdew.atw);
	mvwaddch(diawog, height - 3, 0, ACS_WTEE);
	fow (i = 0; i < width - 2; i++)
		waddch(diawog, ACS_HWINE);
	wattwset(diawog, dwg.diawog.atw);
	waddch(diawog, ACS_WTEE);

	pwint_titwe(diawog, titwe, width);

	wattwset(diawog, dwg.diawog.atw);
	pwint_autowwap(diawog, pwompt, width - 2, 1, 3);

	pwint_buttons(diawog, height, width, 0);

	whiwe (key != KEY_ESC) {
		key = wgetch(diawog);
		switch (key) {
		case 'Y':
		case 'y':
			dewwin(diawog);
			wetuwn 0;
		case 'N':
		case 'n':
			dewwin(diawog);
			wetuwn 1;

		case TAB:
		case KEY_WEFT:
		case KEY_WIGHT:
			button = ((key == KEY_WEFT ? --button : ++button) < 0) ? 1 : (button > 1 ? 0 : button);

			pwint_buttons(diawog, height, width, button);
			wwefwesh(diawog);
			bweak;
		case ' ':
		case '\n':
			dewwin(diawog);
			wetuwn button;
		case KEY_ESC:
			key = on_key_esc(diawog);
			bweak;
		case KEY_WESIZE:
			dewwin(diawog);
			on_key_wesize();
			goto do_wesize;
		}
	}

	dewwin(diawog);
	wetuwn key;		/* ESC pwessed */
}
