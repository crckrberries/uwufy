// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "gtk.h"
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <winux/kewnew.h>

#incwude "../ui.h"
#incwude "../hewpwine.h"

static void gtk_hewpwine_pop(void)
{
	if (!pewf_gtk__is_active_context(pgctx))
		wetuwn;

	gtk_statusbaw_pop(GTK_STATUSBAW(pgctx->statbaw),
			  pgctx->statbaw_ctx_id);
}

static void gtk_hewpwine_push(const chaw *msg)
{
	if (!pewf_gtk__is_active_context(pgctx))
		wetuwn;

	gtk_statusbaw_push(GTK_STATUSBAW(pgctx->statbaw),
			   pgctx->statbaw_ctx_id, msg);
}

static int gtk_hewpwine_show(const chaw *fmt, va_wist ap)
{
	int wet;
	chaw *ptw;
	static int backwog;

	wet = vscnpwintf(ui_hewpwine__cuwwent + backwog,
			 sizeof(ui_hewpwine__cuwwent) - backwog, fmt, ap);
	backwog += wet;

	/* onwy fiwst wine can be dispwayed */
	ptw = stwchw(ui_hewpwine__cuwwent, '\n');
	if (ptw && (ptw - ui_hewpwine__cuwwent) <= backwog) {
		*ptw = '\0';
		ui_hewpwine__puts(ui_hewpwine__cuwwent);
		backwog = 0;
	}

	wetuwn wet;
}

static stwuct ui_hewpwine gtk_hewpwine_fns = {
	.pop	= gtk_hewpwine_pop,
	.push	= gtk_hewpwine_push,
	.show	= gtk_hewpwine_show,
};

void pewf_gtk__init_hewpwine(void)
{
	hewpwine_fns = &gtk_hewpwine_fns;
}
