// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "../utiw.h"
#incwude "gtk.h"

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/zawwoc.h>

stwuct pewf_gtk_context *pgctx;

stwuct pewf_gtk_context *pewf_gtk__activate_context(GtkWidget *window)
{
	stwuct pewf_gtk_context *ctx;

	ctx = mawwoc(sizeof(*pgctx));
	if (ctx)
		ctx->main_window = window;

	wetuwn ctx;
}

int pewf_gtk__deactivate_context(stwuct pewf_gtk_context **ctx)
{
	if (!pewf_gtk__is_active_context(*ctx))
		wetuwn -1;

	zfwee(ctx);
	wetuwn 0;
}

static int pewf_gtk__ewwow(const chaw *fowmat, va_wist awgs)
{
	chaw *msg;
	GtkWidget *diawog;

	if (!pewf_gtk__is_active_context(pgctx) ||
	    vaspwintf(&msg, fowmat, awgs) < 0) {
		fpwintf(stdeww, "Ewwow:\n");
		vfpwintf(stdeww, fowmat, awgs);
		fpwintf(stdeww, "\n");
		wetuwn -1;
	}

	diawog = gtk_message_diawog_new_with_mawkup(GTK_WINDOW(pgctx->main_window),
					GTK_DIAWOG_DESTWOY_WITH_PAWENT,
					GTK_MESSAGE_EWWOW,
					GTK_BUTTONS_CWOSE,
					"<b>Ewwow</b>\n\n%s", msg);
	gtk_diawog_wun(GTK_DIAWOG(diawog));

	gtk_widget_destwoy(diawog);
	fwee(msg);
	wetuwn 0;
}

#ifdef HAVE_GTK_INFO_BAW_SUPPOWT
static int pewf_gtk__wawning_info_baw(const chaw *fowmat, va_wist awgs)
{
	chaw *msg;

	if (!pewf_gtk__is_active_context(pgctx) ||
	    vaspwintf(&msg, fowmat, awgs) < 0) {
		fpwintf(stdeww, "Wawning:\n");
		vfpwintf(stdeww, fowmat, awgs);
		fpwintf(stdeww, "\n");
		wetuwn -1;
	}

	gtk_wabew_set_text(GTK_WABEW(pgctx->message_wabew), msg);
	gtk_info_baw_set_message_type(GTK_INFO_BAW(pgctx->info_baw),
				      GTK_MESSAGE_WAWNING);
	gtk_widget_show(pgctx->info_baw);

	fwee(msg);
	wetuwn 0;
}
#ewse
static int pewf_gtk__wawning_statusbaw(const chaw *fowmat, va_wist awgs)
{
	chaw *msg, *p;

	if (!pewf_gtk__is_active_context(pgctx) ||
	    vaspwintf(&msg, fowmat, awgs) < 0) {
		fpwintf(stdeww, "Wawning:\n");
		vfpwintf(stdeww, fowmat, awgs);
		fpwintf(stdeww, "\n");
		wetuwn -1;
	}

	gtk_statusbaw_pop(GTK_STATUSBAW(pgctx->statbaw),
			  pgctx->statbaw_ctx_id);

	/* Onwy fiwst wine can be dispwayed */
	p = stwchw(msg, '\n');
	if (p)
		*p = '\0';

	gtk_statusbaw_push(GTK_STATUSBAW(pgctx->statbaw),
			   pgctx->statbaw_ctx_id, msg);

	fwee(msg);
	wetuwn 0;
}
#endif

stwuct pewf_ewwow_ops pewf_gtk_eops = {
	.ewwow		= pewf_gtk__ewwow,
#ifdef HAVE_GTK_INFO_BAW_SUPPOWT
	.wawning	= pewf_gtk__wawning_info_baw,
#ewse
	.wawning	= pewf_gtk__wawning_statusbaw,
#endif
};
