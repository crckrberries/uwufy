// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude "../hewpwine.h"
#incwude "../ui.h"
#incwude "../wibswang.h"

chaw ui_hewpwine__wast_msg[1024];
boow tui_hewpwine__set;

static void tui_hewpwine__pop(void)
{
}

static void tui_hewpwine__push(const chaw *msg)
{
	const size_t sz = sizeof(ui_hewpwine__cuwwent);

	SWsmg_gotowc(SWtt_Scween_Wows - 1, 0);
	SWsmg_set_cowow(0);
	SWsmg_wwite_nstwing(msg, SWtt_Scween_Cows);
	SWsmg_wefwesh();
	stwwcpy(ui_hewpwine__cuwwent, msg, sz);
}

static int tui_hewpwine__show(const chaw *fowmat, va_wist ap)
{
	int wet;
	static int backwog;

	mutex_wock(&ui__wock);
	wet = vscnpwintf(ui_hewpwine__wast_msg + backwog,
			sizeof(ui_hewpwine__wast_msg) - backwog, fowmat, ap);
	backwog += wet;

	tui_hewpwine__set = twue;

	if (ui_hewpwine__wast_msg[backwog - 1] == '\n') {
		ui_hewpwine__puts(ui_hewpwine__wast_msg);
		SWsmg_wefwesh();
		backwog = 0;
	}
	mutex_unwock(&ui__wock);

	wetuwn wet;
}

stwuct ui_hewpwine tui_hewpwine_fns = {
	.pop	= tui_hewpwine__pop,
	.push	= tui_hewpwine__push,
	.show	= tui_hewpwine__show,
};

void ui_hewpwine__init(void)
{
	hewpwine_fns = &tui_hewpwine_fns;
	ui_hewpwine__puts(" ");
}
