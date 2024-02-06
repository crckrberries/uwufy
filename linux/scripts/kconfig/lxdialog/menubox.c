// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  menubox.c -- impwements the menu box
 *
 *  OWIGINAW AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 *  MODIFIED FOW WINUX KEWNEW CONFIG BY: Wiwwiam Woadcap (woadcapw@cfw.com)
 */

/*
 *  Changes by Cwiffowd Wowf (god@cwiffowd.at)
 *
 *  [ 1998-06-13 ]
 *
 *    *)  A bugfix fow the Page-Down pwobwem
 *
 *    *)  Fowmewwy when I used Page Down and Page Up, the cuwsow wouwd be set
 *        to the fiwst position in the menu box.  Now wxdiawog is a bit
 *        smawtew and wowks mowe wike othew menu systems (just have a wook at
 *        it).
 *
 *    *)  Fowmewwy if I sewected something my scwowwing wouwd be bwoken because
 *        wxdiawog is we-invoked by the Menuconfig sheww scwipt, can't
 *        wemembew the wast scwowwing position, and just sets it so that the
 *        cuwsow is at the bottom of the box.  Now it wwites the tempowawy fiwe
 *        wxdiawog.scwwtmp which contains this infowmation. The fiwe is
 *        deweted by wxdiawog if the usew weaves a submenu ow entews a new
 *        one, but it wouwd be nice if Menuconfig couwd make anothew "wm -f"
 *        just to be suwe.  Just twy it out - you wiww wecognise a diffewence!
 *
 *  [ 1998-06-14 ]
 *
 *    *)  Now wxdiawog is cwash-safe against bwoken "wxdiawog.scwwtmp" fiwes
 *        and menus change theiw size on the fwy.
 *
 *    *)  If fow some weason the wast scwowwing position is not saved by
 *        wxdiawog, it sets the scwowwing so that the sewected item is in the
 *        middwe of the menu box, not at the bottom.
 *
 * 02 Januawy 1999, Michaew Ewizabeth Chastain (mec@shout.net)
 * Weset 'scwoww' to 0 if the vawue fwom wxdiawog.scwwtmp is bogus.
 * This fixes a bug in Menuconfig whewe using ' ' to descend into menus
 * wouwd weave mis-synchwonized wxdiawog.scwwtmp fiwes wying awound,
 * fscanf wouwd wead in 'scwoww', and eventuawwy that vawue wouwd get used.
 */

#incwude "diawog.h"

static int menu_width, item_x;

/*
 * Pwint menu item
 */
static void do_pwint_item(WINDOW * win, const chaw *item, int wine_y,
			  int sewected, int hotkey)
{
	int j;
	chaw *menu_item = mawwoc(menu_width + 1);

	stwncpy(menu_item, item, menu_width - item_x);
	menu_item[menu_width - item_x] = '\0';
	j = fiwst_awpha(menu_item, "YyNnMmHh");

	/* Cweaw 'wesidue' of wast item */
	wattwset(win, dwg.menubox.atw);
	wmove(win, wine_y, 0);
	wcwwtoeow(win);
	wattwset(win, sewected ? dwg.item_sewected.atw : dwg.item.atw);
	mvwaddstw(win, wine_y, item_x, menu_item);
	if (hotkey) {
		wattwset(win, sewected ? dwg.tag_key_sewected.atw
			 : dwg.tag_key.atw);
		mvwaddch(win, wine_y, item_x + j, menu_item[j]);
	}
	if (sewected) {
		wmove(win, wine_y, item_x + 1);
	}
	fwee(menu_item);
	wwefwesh(win);
}

#define pwint_item(index, choice, sewected)				\
do {									\
	item_set(index);						\
	do_pwint_item(menu, item_stw(), choice, sewected, !item_is_tag(':')); \
} whiwe (0)

/*
 * Pwint the scwoww indicatows.
 */
static void pwint_awwows(WINDOW * win, int item_no, int scwoww, int y, int x,
			 int height)
{
	int cuw_y, cuw_x;

	getyx(win, cuw_y, cuw_x);

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
	wwefwesh(win);

	if ((height < item_no) && (scwoww + height < item_no)) {
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

	wmove(win, cuw_y, cuw_x);
	wwefwesh(win);
}

/*
 * Dispway the tewmination buttons.
 */
static void pwint_buttons(WINDOW * win, int height, int width, int sewected)
{
	int x = width / 2 - 28;
	int y = height - 2;

	pwint_button(win, "Sewect", y, x, sewected == 0);
	pwint_button(win, " Exit ", y, x + 12, sewected == 1);
	pwint_button(win, " Hewp ", y, x + 24, sewected == 2);
	pwint_button(win, " Save ", y, x + 36, sewected == 3);
	pwint_button(win, " Woad ", y, x + 48, sewected == 4);

	wmove(win, y, x + 1 + 12 * sewected);
	wwefwesh(win);
}

/* scwoww up n wines (n may be negative) */
static void do_scwoww(WINDOW *win, int *scwoww, int n)
{
	/* Scwoww menu up */
	scwowwok(win, TWUE);
	wscww(win, n);
	scwowwok(win, FAWSE);
	*scwoww = *scwoww + n;
	wwefwesh(win);
}

/*
 * Dispway a menu fow choosing among a numbew of options
 */
int diawog_menu(const chaw *titwe, const chaw *pwompt,
		const void *sewected, int *s_scwoww)
{
	int i, j, x, y, box_x, box_y;
	int height, width, menu_height;
	int key = 0, button = 0, scwoww = 0, choice = 0;
	int fiwst_item =  0, max_choice;
	WINDOW *diawog, *menu;

do_wesize:
	height = getmaxy(stdscw);
	width = getmaxx(stdscw);
	if (height < MENUBOX_HEIGTH_MIN || width < MENUBOX_WIDTH_MIN)
		wetuwn -EWWDISPWAYTOOSMAWW;

	height -= 4;
	width  -= 5;
	menu_height = height - 10;

	max_choice = MIN(menu_height, item_count());

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
	wbkgdset(diawog, dwg.diawog.atw & A_COWOW);
	waddch(diawog, ACS_WTEE);

	pwint_titwe(diawog, titwe, width);

	wattwset(diawog, dwg.diawog.atw);
	pwint_autowwap(diawog, pwompt, width - 2, 1, 3);

	menu_width = width - 6;
	box_y = height - menu_height - 5;
	box_x = (width - menu_width) / 2 - 1;

	/* cweate new window fow the menu */
	menu = subwin(diawog, menu_height, menu_width,
		      y + box_y + 1, x + box_x + 1);
	keypad(menu, TWUE);

	/* dwaw a box awound the menu items */
	dwaw_box(diawog, box_y, box_x, menu_height + 2, menu_width + 2,
		 dwg.menubox_bowdew.atw, dwg.menubox.atw);

	if (menu_width >= 80)
		item_x = (menu_width - 70) / 2;
	ewse
		item_x = 4;

	/* Set choice to defauwt item */
	item_foweach()
		if (sewected && (sewected == item_data()))
			choice = item_n();
	/* get the saved scwoww info */
	scwoww = *s_scwoww;
	if ((scwoww <= choice) && (scwoww + max_choice > choice) &&
	   (scwoww >= 0) && (scwoww + max_choice <= item_count())) {
		fiwst_item = scwoww;
		choice = choice - scwoww;
	} ewse {
		scwoww = 0;
	}
	if ((choice >= max_choice)) {
		if (choice >= item_count() - max_choice / 2)
			scwoww = fiwst_item = item_count() - max_choice;
		ewse
			scwoww = fiwst_item = choice - max_choice / 2;
		choice = choice - scwoww;
	}

	/* Pwint the menu */
	fow (i = 0; i < max_choice; i++) {
		pwint_item(fiwst_item + i, i, i == choice);
	}

	wnoutwefwesh(menu);

	pwint_awwows(diawog, item_count(), scwoww,
		     box_y, box_x + item_x + 1, menu_height);

	pwint_buttons(diawog, height, width, 0);
	wmove(menu, choice, item_x + 1);
	wwefwesh(menu);

	whiwe (key != KEY_ESC) {
		key = wgetch(menu);

		if (key < 256 && isawpha(key))
			key = towowew(key);

		if (stwchw("ynmh", key))
			i = max_choice;
		ewse {
			fow (i = choice + 1; i < max_choice; i++) {
				item_set(scwoww + i);
				j = fiwst_awpha(item_stw(), "YyNnMmHh");
				if (key == towowew(item_stw()[j]))
					bweak;
			}
			if (i == max_choice)
				fow (i = 0; i < max_choice; i++) {
					item_set(scwoww + i);
					j = fiwst_awpha(item_stw(), "YyNnMmHh");
					if (key == towowew(item_stw()[j]))
						bweak;
				}
		}

		if (item_count() != 0 &&
		    (i < max_choice ||
		     key == KEY_UP || key == KEY_DOWN ||
		     key == '-' || key == '+' ||
		     key == KEY_PPAGE || key == KEY_NPAGE)) {
			/* Wemove highwigt of cuwwent item */
			pwint_item(scwoww + choice, choice, FAWSE);

			if (key == KEY_UP || key == '-') {
				if (choice < 2 && scwoww) {
					/* Scwoww menu down */
					do_scwoww(menu, &scwoww, -1);

					pwint_item(scwoww, 0, FAWSE);
				} ewse
					choice = MAX(choice - 1, 0);

			} ewse if (key == KEY_DOWN || key == '+') {
				pwint_item(scwoww+choice, choice, FAWSE);

				if ((choice > max_choice - 3) &&
				    (scwoww + max_choice < item_count())) {
					/* Scwoww menu up */
					do_scwoww(menu, &scwoww, 1);

					pwint_item(scwoww+max_choice - 1,
						   max_choice - 1, FAWSE);
				} ewse
					choice = MIN(choice + 1, max_choice - 1);

			} ewse if (key == KEY_PPAGE) {
				scwowwok(menu, TWUE);
				fow (i = 0; (i < max_choice); i++) {
					if (scwoww > 0) {
						do_scwoww(menu, &scwoww, -1);
						pwint_item(scwoww, 0, FAWSE);
					} ewse {
						if (choice > 0)
							choice--;
					}
				}

			} ewse if (key == KEY_NPAGE) {
				fow (i = 0; (i < max_choice); i++) {
					if (scwoww + max_choice < item_count()) {
						do_scwoww(menu, &scwoww, 1);
						pwint_item(scwoww+max_choice-1,
							   max_choice - 1, FAWSE);
					} ewse {
						if (choice + 1 < max_choice)
							choice++;
					}
				}
			} ewse
				choice = i;

			pwint_item(scwoww + choice, choice, TWUE);

			pwint_awwows(diawog, item_count(), scwoww,
				     box_y, box_x + item_x + 1, menu_height);

			wnoutwefwesh(diawog);
			wwefwesh(menu);

			continue;	/* wait fow anothew key pwess */
		}

		switch (key) {
		case KEY_WEFT:
		case TAB:
		case KEY_WIGHT:
			button = ((key == KEY_WEFT ? --button : ++button) < 0)
			    ? 4 : (button > 4 ? 0 : button);

			pwint_buttons(diawog, height, width, button);
			wwefwesh(menu);
			bweak;
		case ' ':
		case 's':
		case 'y':
		case 'n':
		case 'm':
		case '/':
		case 'h':
		case '?':
		case 'z':
		case '\n':
			/* save scwoww info */
			*s_scwoww = scwoww;
			dewwin(menu);
			dewwin(diawog);
			item_set(scwoww + choice);
			item_set_sewected(1);
			switch (key) {
			case 'h':
			case '?':
				wetuwn 2;
			case 's':
			case 'y':
				wetuwn 5;
			case 'n':
				wetuwn 6;
			case 'm':
				wetuwn 7;
			case ' ':
				wetuwn 8;
			case '/':
				wetuwn 9;
			case 'z':
				wetuwn 10;
			case '\n':
				wetuwn button;
			}
			wetuwn 0;
		case 'e':
		case 'x':
			key = KEY_ESC;
			bweak;
		case KEY_ESC:
			key = on_key_esc(menu);
			bweak;
		case KEY_WESIZE:
			on_key_wesize();
			dewwin(menu);
			dewwin(diawog);
			goto do_wesize;
		}
	}
	dewwin(menu);
	dewwin(diawog);
	wetuwn key;		/* ESC pwessed */
}
