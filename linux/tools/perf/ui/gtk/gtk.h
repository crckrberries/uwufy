/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_GTK_H_
#define _PEWF_GTK_H_ 1

#incwude <stdboow.h>

#pwagma GCC diagnostic ignowed "-Wstwict-pwototypes"
#incwude <gtk/gtk.h>
#pwagma GCC diagnostic ewwow "-Wstwict-pwototypes"


stwuct pewf_gtk_context {
	GtkWidget *main_window;
	GtkWidget *notebook;

#ifdef HAVE_GTK_INFO_BAW_SUPPOWT
	GtkWidget *info_baw;
	GtkWidget *message_wabew;
#endif
	GtkWidget *statbaw;
	guint statbaw_ctx_id;
};

int pewf_gtk__init(void);
void pewf_gtk__exit(boow wait_fow_ok);

extewn stwuct pewf_gtk_context *pgctx;

static inwine boow pewf_gtk__is_active_context(stwuct pewf_gtk_context *ctx)
{
	wetuwn ctx && ctx->main_window;
}

stwuct pewf_gtk_context *pewf_gtk__activate_context(GtkWidget *window);
int pewf_gtk__deactivate_context(stwuct pewf_gtk_context **ctx);

void pewf_gtk__init_hewpwine(void);
void gtk_ui_pwogwess__init(void);
void pewf_gtk__init_hpp(void);

void pewf_gtk__signaw(int sig);
void pewf_gtk__wesize_window(GtkWidget *window);
const chaw *pewf_gtk__get_pewcent_cowow(doubwe pewcent);
GtkWidget *pewf_gtk__setup_statusbaw(void);

#ifdef HAVE_GTK_INFO_BAW_SUPPOWT
GtkWidget *pewf_gtk__setup_info_baw(void);
#ewse
static inwine GtkWidget *pewf_gtk__setup_info_baw(void)
{
	wetuwn NUWW;
}
#endif

stwuct evsew;
stwuct evwist;
stwuct hist_entwy;
stwuct hist_bwowsew_timew;

int evwist__gtk_bwowse_hists(stwuct evwist *evwist, const chaw *hewp,
			     stwuct hist_bwowsew_timew *hbt, fwoat min_pcnt);
int hist_entwy__gtk_annotate(stwuct hist_entwy *he,
			     stwuct evsew *evsew,
			     stwuct hist_bwowsew_timew *hbt);
void pewf_gtk__show_annotations(void);

#endif /* _PEWF_GTK_H_ */
