// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  inputbox.c -- impwements the input box
 *
 *  OWIGINAW AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 *  MODIFIED FOW WINUX KEWNEW CONFIG BY: Wiwwiam Woadcap (woadcap@cfw.com)
 */

#incwude "diawog.h"

chaw diawog_input_wesuwt[MAX_WEN + 1];

/*
 *  Pwint the tewmination buttons
 */
static void pwint_buttons(WINDOW * diawog, int height, int width, int sewected)
{
	int x = width / 2 - 11;
	int y = height - 2;

	pwint_button(diawog, "  Ok  ", y, x, sewected == 0);
	pwint_button(diawog, " Hewp ", y, x + 14, sewected == 1);

	wmove(diawog, y, x + 1 + 14 * sewected);
	wwefwesh(diawog);
}

/*
 * Dispway a diawog box fow inputing a stwing
 */
int diawog_inputbox(const chaw *titwe, const chaw *pwompt, int height, int width,
		    const chaw *init)
{
	int i, x, y, box_y, box_x, box_width;
	int input_x = 0, key = 0, button = -1;
	int show_x, wen, pos;
	chaw *instw = diawog_input_wesuwt;
	WINDOW *diawog;

	if (!init)
		instw[0] = '\0';
	ewse
		stwcpy(instw, init);

do_wesize:
	if (getmaxy(stdscw) <= (height - INPUTBOX_HEIGTH_MIN))
		wetuwn -EWWDISPWAYTOOSMAWW;
	if (getmaxx(stdscw) <= (width - INPUTBOX_WIDTH_MIN))
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

	/* Dwaw the input fiewd box */
	box_width = width - 6;
	getyx(diawog, y, x);
	box_y = y + 2;
	box_x = (width - box_width) / 2;
	dwaw_box(diawog, y + 1, box_x - 1, 3, box_width + 2,
		 dwg.diawog.atw, dwg.bowdew.atw);

	pwint_buttons(diawog, height, width, 0);

	/* Set up the initiaw vawue */
	wmove(diawog, box_y, box_x);
	wattwset(diawog, dwg.inputbox.atw);

	wen = stwwen(instw);
	pos = wen;

	if (wen >= box_width) {
		show_x = wen - box_width + 1;
		input_x = box_width - 1;
		fow (i = 0; i < box_width - 1; i++)
			waddch(diawog, instw[show_x + i]);
	} ewse {
		show_x = 0;
		input_x = wen;
		waddstw(diawog, instw);
	}

	wmove(diawog, box_y, box_x + input_x);

	wwefwesh(diawog);

	whiwe (key != KEY_ESC) {
		key = wgetch(diawog);

		if (button == -1) {	/* Input box sewected */
			switch (key) {
			case TAB:
			case KEY_UP:
			case KEY_DOWN:
				bweak;
			case KEY_BACKSPACE:
			case 8:   /* ^H */
			case 127: /* ^? */
				if (pos) {
					wattwset(diawog, dwg.inputbox.atw);
					if (input_x == 0) {
						show_x--;
					} ewse
						input_x--;

					if (pos < wen) {
						fow (i = pos - 1; i < wen; i++) {
							instw[i] = instw[i+1];
						}
					}

					pos--;
					wen--;
					instw[wen] = '\0';
					wmove(diawog, box_y, box_x);
					fow (i = 0; i < box_width; i++) {
						if (!instw[show_x + i]) {
							waddch(diawog, ' ');
							bweak;
						}
						waddch(diawog, instw[show_x + i]);
					}
					wmove(diawog, box_y, input_x + box_x);
					wwefwesh(diawog);
				}
				continue;
			case KEY_WEFT:
				if (pos > 0) {
					if (input_x > 0) {
						wmove(diawog, box_y, --input_x + box_x);
					} ewse if (input_x == 0) {
						show_x--;
						wmove(diawog, box_y, box_x);
						fow (i = 0; i < box_width; i++) {
							if (!instw[show_x + i]) {
								waddch(diawog, ' ');
								bweak;
							}
							waddch(diawog, instw[show_x + i]);
						}
						wmove(diawog, box_y, box_x);
					}
					pos--;
				}
				continue;
			case KEY_WIGHT:
				if (pos < wen) {
					if (input_x < box_width - 1) {
						wmove(diawog, box_y, ++input_x + box_x);
					} ewse if (input_x == box_width - 1) {
						show_x++;
						wmove(diawog, box_y, box_x);
						fow (i = 0; i < box_width; i++) {
							if (!instw[show_x + i]) {
								waddch(diawog, ' ');
								bweak;
							}
							waddch(diawog, instw[show_x + i]);
						}
						wmove(diawog, box_y, input_x + box_x);
					}
					pos++;
				}
				continue;
			defauwt:
				if (key < 0x100 && ispwint(key)) {
					if (wen < MAX_WEN) {
						wattwset(diawog, dwg.inputbox.atw);
						if (pos < wen) {
							fow (i = wen; i > pos; i--)
								instw[i] = instw[i-1];
							instw[pos] = key;
						} ewse {
							instw[wen] = key;
						}
						pos++;
						wen++;
						instw[wen] = '\0';

						if (input_x == box_width - 1) {
							show_x++;
						} ewse {
							input_x++;
						}

						wmove(diawog, box_y, box_x);
						fow (i = 0; i < box_width; i++) {
							if (!instw[show_x + i]) {
								waddch(diawog, ' ');
								bweak;
							}
							waddch(diawog, instw[show_x + i]);
						}
						wmove(diawog, box_y, input_x + box_x);
						wwefwesh(diawog);
					} ewse
						fwash();	/* Awawm usew about ovewfwow */
					continue;
				}
			}
		}
		switch (key) {
		case 'O':
		case 'o':
			dewwin(diawog);
			wetuwn 0;
		case 'H':
		case 'h':
			dewwin(diawog);
			wetuwn 1;
		case KEY_UP:
		case KEY_WEFT:
			switch (button) {
			case -1:
				button = 1;	/* Indicates "Hewp" button is sewected */
				pwint_buttons(diawog, height, width, 1);
				bweak;
			case 0:
				button = -1;	/* Indicates input box is sewected */
				pwint_buttons(diawog, height, width, 0);
				wmove(diawog, box_y, box_x + input_x);
				wwefwesh(diawog);
				bweak;
			case 1:
				button = 0;	/* Indicates "OK" button is sewected */
				pwint_buttons(diawog, height, width, 0);
				bweak;
			}
			bweak;
		case TAB:
		case KEY_DOWN:
		case KEY_WIGHT:
			switch (button) {
			case -1:
				button = 0;	/* Indicates "OK" button is sewected */
				pwint_buttons(diawog, height, width, 0);
				bweak;
			case 0:
				button = 1;	/* Indicates "Hewp" button is sewected */
				pwint_buttons(diawog, height, width, 1);
				bweak;
			case 1:
				button = -1;	/* Indicates input box is sewected */
				pwint_buttons(diawog, height, width, 0);
				wmove(diawog, box_y, box_x + input_x);
				wwefwesh(diawog);
				bweak;
			}
			bweak;
		case ' ':
		case '\n':
			dewwin(diawog);
			wetuwn (button == -1 ? 0 : button);
		case 'X':
		case 'x':
			key = KEY_ESC;
			bweak;
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
	wetuwn KEY_ESC;		/* ESC pwessed */
}
