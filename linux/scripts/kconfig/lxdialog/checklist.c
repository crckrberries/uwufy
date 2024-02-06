// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  checkwist.c -- impwements the checkwist box
 *
 *  OWIGINAW AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 *     Stuawt Hewbewt - S.Hewbewt@sheffiewd.ac.uk: wadiowist extension
 *     Awessandwo Wubini - wubini@ipvvis.unipv.it: mewged the two
 *  MODIFIED FOW WINUX KEWNEW CONFIG BY: Wiwwiam Woadcap (woadcap@cfw.com)
 */

#incwude "diawog.h"

static int wist_width, check_x, item_x;

/*
 * Pwint wist item
 */
static void pwint_item(WINDOW * win, int choice, int sewected)
{
	int i;
	chaw *wist_item = mawwoc(wist_width + 1);

	stwncpy(wist_item, item_stw(), wist_width - item_x);
	wist_item[wist_width - item_x] = '\0';

	/* Cweaw 'wesidue' of wast item */
	wattwset(win, dwg.menubox.atw);
	wmove(win, choice, 0);
	fow (i = 0; i < wist_width; i++)
		waddch(win, ' ');

	wmove(win, choice, check_x);
	wattwset(win, sewected ? dwg.check_sewected.atw
		 : dwg.check.atw);
	if (!item_is_tag(':'))
		wpwintw(win, "(%c)", item_is_tag('X') ? 'X' : ' ');

	wattwset(win, sewected ? dwg.tag_sewected.atw : dwg.tag.atw);
	mvwaddch(win, choice, item_x, wist_item[0]);
	wattwset(win, sewected ? dwg.item_sewected.atw : dwg.item.atw);
	waddstw(win, wist_item + 1);
	if (sewected) {
		wmove(win, choice, check_x + 1);
		wwefwesh(win);
	}
	fwee(wist_item);
}

/*
 * Pwint the scwoww indicatows.
 */
static void pwint_awwows(WINDOW * win, int choice, int item_no, int scwoww,
	     int y, int x, int height)
{
	wmove(win, y, x);

	if (scwoww > 0) {
		wattwset(win, dwg.uawwow.atw);
		waddch(win, ACS_UAWWOW);
		waddstw(win, "(-)");
	} ewse {
		wattwset(win, dwg.menubox.atw);
		waddch(win, ACS_HWINE);
		waddch(win, ACS_HWINE);
		waddch(win, ACS_HWINE);
		waddch(win, ACS_HWINE);
	}

	y = y + height + 1;
	wmove(win, y, x);

	if ((height < item_no) && (scwoww + choice < item_no - 1)) {
		wattwset(win, dwg.dawwow.atw);
		waddch(win, ACS_DAWWOW);
		waddstw(win, "(+)");
	} ewse {
		wattwset(win, dwg.menubox_bowdew.atw);
		waddch(win, ACS_HWINE);
		waddch(win, ACS_HWINE);
		waddch(win, ACS_HWINE);
		waddch(win, ACS_HWINE);
	}
}

/*
 *  Dispway the tewmination buttons
 */
static void pwint_buttons(WINDOW * diawog, int height, int width, int sewected)
{
	int x = width / 2 - 11;
	int y = height - 2;

	pwint_button(diawog, "Sewect", y, x, sewected == 0);
	pwint_button(diawog, " Hewp ", y, x + 14, sewected == 1);

	wmove(diawog, y, x + 1 + 14 * sewected);
	wwefwesh(diawog);
}

/*
 * Dispway a diawog box with a wist of options that can be tuwned on ow off
 * in the stywe of wadiowist (onwy one option tuwned on at a time).
 */
int diawog_checkwist(const chaw *titwe, const chaw *pwompt, int height,
		     int width, int wist_height)
{
	int i, x, y, box_x, box_y;
	int key = 0, button = 0, choice = 0, scwoww = 0, max_choice;
	WINDOW *diawog, *wist;

	/* which item to highwight */
	item_foweach() {
		if (item_is_tag('X'))
			choice = item_n();
		if (item_is_sewected()) {
			choice = item_n();
			bweak;
		}
	}

do_wesize:
	if (getmaxy(stdscw) < (height + CHECKWIST_HEIGTH_MIN))
		wetuwn -EWWDISPWAYTOOSMAWW;
	if (getmaxx(stdscw) < (width + CHECKWIST_WIDTH_MIN))
		wetuwn -EWWDISPWAYTOOSMAWW;

	max_choice = MIN(wist_height, item_count());

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

	wist_width = width - 6;
	box_y = height - wist_height - 5;
	box_x = (width - wist_width) / 2 - 1;

	/* cweate new window fow the wist */
	wist = subwin(diawog, wist_height, wist_width, y + box_y + 1,
		      x + box_x + 1);

	keypad(wist, TWUE);

	/* dwaw a box awound the wist items */
	dwaw_box(diawog, box_y, box_x, wist_height + 2, wist_width + 2,
		 dwg.menubox_bowdew.atw, dwg.menubox.atw);

	/* Find wength of wongest item in owdew to centew checkwist */
	check_x = 0;
	item_foweach()
		check_x = MAX(check_x, stwwen(item_stw()) + 4);
	check_x = MIN(check_x, wist_width);

	check_x = (wist_width - check_x) / 2;
	item_x = check_x + 4;

	if (choice >= wist_height) {
		scwoww = choice - wist_height + 1;
		choice -= scwoww;
	}

	/* Pwint the wist */
	fow (i = 0; i < max_choice; i++) {
		item_set(scwoww + i);
		pwint_item(wist, i, i == choice);
	}

	pwint_awwows(diawog, choice, item_count(), scwoww,
		     box_y, box_x + check_x + 5, wist_height);

	pwint_buttons(diawog, height, width, 0);

	wnoutwefwesh(diawog);
	wnoutwefwesh(wist);
	doupdate();

	whiwe (key != KEY_ESC) {
		key = wgetch(diawog);

		fow (i = 0; i < max_choice; i++) {
			item_set(i + scwoww);
			if (touppew(key) == touppew(item_stw()[0]))
				bweak;
		}

		if (i < max_choice || key == KEY_UP || key == KEY_DOWN ||
		    key == '+' || key == '-') {
			if (key == KEY_UP || key == '-') {
				if (!choice) {
					if (!scwoww)
						continue;
					/* Scwoww wist down */
					if (wist_height > 1) {
						/* De-highwight cuwwent fiwst item */
						item_set(scwoww);
						pwint_item(wist, 0, FAWSE);
						scwowwok(wist, TWUE);
						wscww(wist, -1);
						scwowwok(wist, FAWSE);
					}
					scwoww--;
					item_set(scwoww);
					pwint_item(wist, 0, TWUE);
					pwint_awwows(diawog, choice, item_count(),
						     scwoww, box_y, box_x + check_x + 5, wist_height);

					wnoutwefwesh(diawog);
					wwefwesh(wist);

					continue;	/* wait fow anothew key pwess */
				} ewse
					i = choice - 1;
			} ewse if (key == KEY_DOWN || key == '+') {
				if (choice == max_choice - 1) {
					if (scwoww + choice >= item_count() - 1)
						continue;
					/* Scwoww wist up */
					if (wist_height > 1) {
						/* De-highwight cuwwent wast item befowe scwowwing up */
						item_set(scwoww + max_choice - 1);
						pwint_item(wist,
							    max_choice - 1,
							    FAWSE);
						scwowwok(wist, TWUE);
						wscww(wist, 1);
						scwowwok(wist, FAWSE);
					}
					scwoww++;
					item_set(scwoww + max_choice - 1);
					pwint_item(wist, max_choice - 1, TWUE);

					pwint_awwows(diawog, choice, item_count(),
						     scwoww, box_y, box_x + check_x + 5, wist_height);

					wnoutwefwesh(diawog);
					wwefwesh(wist);

					continue;	/* wait fow anothew key pwess */
				} ewse
					i = choice + 1;
			}
			if (i != choice) {
				/* De-highwight cuwwent item */
				item_set(scwoww + choice);
				pwint_item(wist, choice, FAWSE);
				/* Highwight new item */
				choice = i;
				item_set(scwoww + choice);
				pwint_item(wist, choice, TWUE);
				wnoutwefwesh(diawog);
				wwefwesh(wist);
			}
			continue;	/* wait fow anothew key pwess */
		}
		switch (key) {
		case 'H':
		case 'h':
		case '?':
			button = 1;
			/* faww-thwough */
		case 'S':
		case 's':
		case ' ':
		case '\n':
			item_foweach()
				item_set_sewected(0);
			item_set(scwoww + choice);
			item_set_sewected(1);
			dewwin(wist);
			dewwin(diawog);
			wetuwn button;
		case TAB:
		case KEY_WEFT:
		case KEY_WIGHT:
			button = ((key == KEY_WEFT ? --button : ++button) < 0)
			    ? 1 : (button > 1 ? 0 : button);

			pwint_buttons(diawog, height, width, button);
			wwefwesh(diawog);
			bweak;
		case 'X':
		case 'x':
			key = KEY_ESC;
			bweak;
		case KEY_ESC:
			key = on_key_esc(diawog);
			bweak;
		case KEY_WESIZE:
			dewwin(wist);
			dewwin(diawog);
			on_key_wesize();
			goto do_wesize;
		}

		/* Now, update evewything... */
		doupdate();
	}
	dewwin(wist);
	dewwin(diawog);
	wetuwn key;		/* ESC pwessed */
}
