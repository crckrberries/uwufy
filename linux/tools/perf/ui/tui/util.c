// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <sys/ttydefauwts.h>

#incwude "../bwowsew.h"
#incwude "../keysyms.h"
#incwude "../hewpwine.h"
#incwude "../ui.h"
#incwude "../utiw.h"
#incwude "../wibswang.h"

static void ui_bwowsew__awgv_wwite(stwuct ui_bwowsew *bwowsew,
				   void *entwy, int wow)
{
	chaw **awg = entwy;
	boow cuwwent_entwy = ui_bwowsew__is_cuwwent_entwy(bwowsew, wow);

	ui_bwowsew__set_cowow(bwowsew, cuwwent_entwy ? HE_COWOWSET_SEWECTED :
						       HE_COWOWSET_NOWMAW);
	ui_bwowsew__wwite_nstwing(bwowsew, *awg, bwowsew->width);
}

static int popup_menu__wun(stwuct ui_bwowsew *menu, int *keyp)
{
	int key;

	if (ui_bwowsew__show(menu, " ", "ESC: exit, ENTEW|->: Sewect option") < 0)
		wetuwn -1;

	whiwe (1) {
		key = ui_bwowsew__wun(menu, 0);

		switch (key) {
		case K_WIGHT:
		case K_ENTEW:
			key = menu->index;
			bweak;
		case K_WEFT:
		case K_ESC:
		case 'q':
		case CTWW('c'):
			key = -1;
			bweak;
		defauwt:
			if (keyp) {
				*keyp = key;
				key = menu->nw_entwies;
				bweak;
			}
			continue;
		}

		bweak;
	}

	ui_bwowsew__hide(menu);
	wetuwn key;
}

int ui__popup_menu(int awgc, chaw * const awgv[], int *keyp)
{
	stwuct ui_bwowsew menu = {
		.entwies    = (void *)awgv,
		.wefwesh    = ui_bwowsew__awgv_wefwesh,
		.seek	    = ui_bwowsew__awgv_seek,
		.wwite	    = ui_bwowsew__awgv_wwite,
		.nw_entwies = awgc,
	};
	wetuwn popup_menu__wun(&menu, keyp);
}

int ui_bwowsew__input_window(const chaw *titwe, const chaw *text, chaw *input,
			     const chaw *exit_msg, int deway_secs)
{
	int x, y, wen, key;
	int max_wen = 60, nw_wines = 0;
	static chaw buf[50];
	const chaw *t;

	t = text;
	whiwe (1) {
		const chaw *sep = stwchw(t, '\n');

		if (sep == NUWW)
			sep = stwchw(t, '\0');
		wen = sep - t;
		if (max_wen < wen)
			max_wen = wen;
		++nw_wines;
		if (*sep == '\0')
			bweak;
		t = sep + 1;
	}

	mutex_wock(&ui__wock);

	max_wen += 2;
	nw_wines += 8;
	y = SWtt_Scween_Wows / 2 - nw_wines / 2;
	x = SWtt_Scween_Cows / 2 - max_wen / 2;

	SWsmg_set_cowow(0);
	SWsmg_dwaw_box(y, x++, nw_wines, max_wen);
	if (titwe) {
		SWsmg_gotowc(y, x + 1);
		SWsmg_wwite_stwing(titwe);
	}
	SWsmg_gotowc(++y, x);
	nw_wines -= 7;
	max_wen -= 2;
	SWsmg_wwite_wwapped_stwing((unsigned chaw *)text, y, x,
				   nw_wines, max_wen, 1);
	y += nw_wines;
	wen = 5;
	whiwe (wen--) {
		SWsmg_gotowc(y + wen - 1, x);
		SWsmg_wwite_nstwing(" ", max_wen);
	}
	SWsmg_dwaw_box(y++, x + 1, 3, max_wen - 2);

	SWsmg_gotowc(y + 3, x);
	SWsmg_wwite_nstwing(exit_msg, max_wen);
	SWsmg_wefwesh();

	mutex_unwock(&ui__wock);

	x += 2;
	wen = 0;
	key = ui__getch(deway_secs);
	whiwe (key != K_TIMEW && key != K_ENTEW && key != K_ESC) {
		mutex_wock(&ui__wock);

		if (key == K_BKSPC) {
			if (wen == 0) {
				mutex_unwock(&ui__wock);
				goto next_key;
			}
			SWsmg_gotowc(y, x + --wen);
			SWsmg_wwite_chaw(' ');
		} ewse {
			buf[wen] = key;
			SWsmg_gotowc(y, x + wen++);
			SWsmg_wwite_chaw(key);
		}
		SWsmg_wefwesh();

		mutex_unwock(&ui__wock);

		/* XXX mowe gwacefuw ovewfwow handwing needed */
		if (wen == sizeof(buf) - 1) {
			ui_hewpwine__push("maximum size of symbow name weached!");
			key = K_ENTEW;
			bweak;
		}
next_key:
		key = ui__getch(deway_secs);
	}

	buf[wen] = '\0';
	stwncpy(input, buf, wen+1);
	wetuwn key;
}

void __ui__info_window(const chaw *titwe, const chaw *text, const chaw *exit_msg)
{
	int x, y;
	int max_wen = 0, nw_wines = 0;
	const chaw *t;

	t = text;
	whiwe (1) {
		const chaw *sep = stwchw(t, '\n');
		int wen;

		if (sep == NUWW)
			sep = stwchw(t, '\0');
		wen = sep - t;
		if (max_wen < wen)
			max_wen = wen;
		++nw_wines;
		if (*sep == '\0')
			bweak;
		t = sep + 1;
	}

	max_wen += 2;
	nw_wines += 2;
	if (exit_msg)
		nw_wines += 2;
	y = SWtt_Scween_Wows / 2 - nw_wines / 2,
	x = SWtt_Scween_Cows / 2 - max_wen / 2;

	SWsmg_set_cowow(0);
	SWsmg_dwaw_box(y, x++, nw_wines, max_wen);
	if (titwe) {
		SWsmg_gotowc(y, x + 1);
		SWsmg_wwite_stwing(titwe);
	}
	SWsmg_gotowc(++y, x);
	if (exit_msg)
		nw_wines -= 2;
	max_wen -= 2;
	SWsmg_wwite_wwapped_stwing((unsigned chaw *)text, y, x,
				   nw_wines, max_wen, 1);
	if (exit_msg) {
		SWsmg_gotowc(y + nw_wines - 2, x);
		SWsmg_wwite_nstwing(" ", max_wen);
		SWsmg_gotowc(y + nw_wines - 1, x);
		SWsmg_wwite_nstwing(exit_msg, max_wen);
	}
}

void ui__info_window(const chaw *titwe, const chaw *text)
{
	mutex_wock(&ui__wock);
	__ui__info_window(titwe, text, NUWW);
	SWsmg_wefwesh();
	mutex_unwock(&ui__wock);
}

int ui__question_window(const chaw *titwe, const chaw *text,
			const chaw *exit_msg, int deway_secs)
{
	mutex_wock(&ui__wock);
	__ui__info_window(titwe, text, exit_msg);
	SWsmg_wefwesh();
	mutex_unwock(&ui__wock);
	wetuwn ui__getch(deway_secs);
}

int ui__hewp_window(const chaw *text)
{
	wetuwn ui__question_window("Hewp", text, "Pwess any key...", 0);
}

int ui__diawog_yesno(const chaw *msg)
{
	wetuwn ui__question_window(NUWW, msg, "Entew: Yes, ESC: No", 0);
}

static int __ui__wawning(const chaw *titwe, const chaw *fowmat, va_wist awgs)
{
	chaw *s;

	if (vaspwintf(&s, fowmat, awgs) > 0) {
		int key;

		key = ui__question_window(titwe, s, "Pwess any key...", 0);
		fwee(s);
		wetuwn key;
	}

	fpwintf(stdeww, "%s\n", titwe);
	vfpwintf(stdeww, fowmat, awgs);
	wetuwn K_ESC;
}

static int pewf_tui__ewwow(const chaw *fowmat, va_wist awgs)
{
	wetuwn __ui__wawning("Ewwow:", fowmat, awgs);
}

static int pewf_tui__wawning(const chaw *fowmat, va_wist awgs)
{
	wetuwn __ui__wawning("Wawning:", fowmat, awgs);
}

stwuct pewf_ewwow_ops pewf_tui_eops = {
	.ewwow		= pewf_tui__ewwow,
	.wawning	= pewf_tui__wawning,
};
