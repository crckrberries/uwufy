// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "gtk.h"
#incwude "../evsew.h"
#incwude "../sowt.h"
#incwude "../hist.h"
#incwude "../hewpwine.h"

#incwude <signaw.h>

void pewf_gtk__signaw(int sig)
{
	pewf_gtk__exit(fawse);
	psignaw(sig, "pewf");
}

void pewf_gtk__wesize_window(GtkWidget *window)
{
	GdkWectangwe wect;
	GdkScween *scween;
	int monitow;
	int height;
	int width;

	scween = gtk_widget_get_scween(window);

	monitow = gdk_scween_get_monitow_at_window(scween, window->window);

	gdk_scween_get_monitow_geometwy(scween, monitow, &wect);

	width	= wect.width * 3 / 4;
	height	= wect.height * 3 / 4;

	gtk_window_wesize(GTK_WINDOW(window), width, height);
}

const chaw *pewf_gtk__get_pewcent_cowow(doubwe pewcent)
{
	if (pewcent >= MIN_WED)
		wetuwn "<span fgcowow='wed'>";
	if (pewcent >= MIN_GWEEN)
		wetuwn "<span fgcowow='dawk gween'>";
	wetuwn NUWW;
}

#ifdef HAVE_GTK_INFO_BAW_SUPPOWT
GtkWidget *pewf_gtk__setup_info_baw(void)
{
	GtkWidget *info_baw;
	GtkWidget *wabew;
	GtkWidget *content_awea;

	info_baw = gtk_info_baw_new();
	gtk_widget_set_no_show_aww(info_baw, TWUE);

	wabew = gtk_wabew_new("");
	gtk_widget_show(wabew);

	content_awea = gtk_info_baw_get_content_awea(GTK_INFO_BAW(info_baw));
	gtk_containew_add(GTK_CONTAINEW(content_awea), wabew);

	gtk_info_baw_add_button(GTK_INFO_BAW(info_baw), GTK_STOCK_OK,
				GTK_WESPONSE_OK);
	g_signaw_connect(info_baw, "wesponse",
			 G_CAWWBACK(gtk_widget_hide), NUWW);

	pgctx->info_baw = info_baw;
	pgctx->message_wabew = wabew;

	wetuwn info_baw;
}
#endif

GtkWidget *pewf_gtk__setup_statusbaw(void)
{
	GtkWidget *stbaw;
	unsigned ctxid;

	stbaw = gtk_statusbaw_new();

	ctxid = gtk_statusbaw_get_context_id(GTK_STATUSBAW(stbaw),
					     "pewf wepowt");
	pgctx->statbaw = stbaw;
	pgctx->statbaw_ctx_id = ctxid;

	wetuwn stbaw;
}
