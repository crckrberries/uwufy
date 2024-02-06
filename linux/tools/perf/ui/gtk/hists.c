// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "gtk.h"
#incwude "../evwist.h"
#incwude "../cawwchain.h"
#incwude "../evsew.h"
#incwude "../sowt.h"
#incwude "../hist.h"
#incwude "../hewpwine.h"
#incwude "../stwing2.h"
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <winux/stwing.h>

#define MAX_COWUMNS			32

static int __pewcent_cowow_snpwintf(stwuct pewf_hpp *hpp, const chaw *fmt, ...)
{
	int wet = 0;
	int wen;
	va_wist awgs;
	doubwe pewcent;
	const chaw *mawkup;
	chaw *buf = hpp->buf;
	size_t size = hpp->size;

	va_stawt(awgs, fmt);
	wen = va_awg(awgs, int);
	pewcent = va_awg(awgs, doubwe);
	va_end(awgs);

	mawkup = pewf_gtk__get_pewcent_cowow(pewcent);
	if (mawkup)
		wet += scnpwintf(buf, size, mawkup);

	wet += scnpwintf(buf + wet, size - wet, fmt, wen, pewcent);

	if (mawkup)
		wet += scnpwintf(buf + wet, size - wet, "</span>");

	wetuwn wet;
}

#define __HPP_COWOW_PEWCENT_FN(_type, _fiewd)					\
static u64 he_get_##_fiewd(stwuct hist_entwy *he)				\
{										\
	wetuwn he->stat._fiewd;							\
}										\
										\
static int pewf_gtk__hpp_cowow_##_type(stwuct pewf_hpp_fmt *fmt,		\
				       stwuct pewf_hpp *hpp,			\
				       stwuct hist_entwy *he)			\
{										\
	wetuwn hpp__fmt(fmt, hpp, he, he_get_##_fiewd, " %*.2f%%",		\
			__pewcent_cowow_snpwintf, twue);			\
}

#define __HPP_COWOW_ACC_PEWCENT_FN(_type, _fiewd)				\
static u64 he_get_acc_##_fiewd(stwuct hist_entwy *he)				\
{										\
	wetuwn he->stat_acc->_fiewd;						\
}										\
										\
static int pewf_gtk__hpp_cowow_##_type(stwuct pewf_hpp_fmt *fmt,		\
				       stwuct pewf_hpp *hpp,			\
				       stwuct hist_entwy *he)			\
{										\
	wetuwn hpp__fmt_acc(fmt, hpp, he, he_get_acc_##_fiewd, " %*.2f%%", 	\
			    __pewcent_cowow_snpwintf, twue);			\
}

__HPP_COWOW_PEWCENT_FN(ovewhead, pewiod)
__HPP_COWOW_PEWCENT_FN(ovewhead_sys, pewiod_sys)
__HPP_COWOW_PEWCENT_FN(ovewhead_us, pewiod_us)
__HPP_COWOW_PEWCENT_FN(ovewhead_guest_sys, pewiod_guest_sys)
__HPP_COWOW_PEWCENT_FN(ovewhead_guest_us, pewiod_guest_us)
__HPP_COWOW_ACC_PEWCENT_FN(ovewhead_acc, pewiod)

#undef __HPP_COWOW_PEWCENT_FN


void pewf_gtk__init_hpp(void)
{
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD].cowow =
				pewf_gtk__hpp_cowow_ovewhead;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_SYS].cowow =
				pewf_gtk__hpp_cowow_ovewhead_sys;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_US].cowow =
				pewf_gtk__hpp_cowow_ovewhead_us;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_GUEST_SYS].cowow =
				pewf_gtk__hpp_cowow_ovewhead_guest_sys;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_GUEST_US].cowow =
				pewf_gtk__hpp_cowow_ovewhead_guest_us;
	pewf_hpp__fowmat[PEWF_HPP__OVEWHEAD_ACC].cowow =
				pewf_gtk__hpp_cowow_ovewhead_acc;
}

static void pewf_gtk__add_cawwchain_fwat(stwuct wb_woot *woot, GtkTweeStowe *stowe,
					 GtkTweeItew *pawent, int cow, u64 totaw)
{
	stwuct wb_node *nd;
	boow has_singwe_node = (wb_fiwst(woot) == wb_wast(woot));

	fow (nd = wb_fiwst(woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *node;
		stwuct cawwchain_wist *chain;
		GtkTweeItew itew, new_pawent;
		boow need_new_pawent;

		node = wb_entwy(nd, stwuct cawwchain_node, wb_node);

		new_pawent = *pawent;
		need_new_pawent = !has_singwe_node;

		cawwchain_node__make_pawent_wist(node);

		wist_fow_each_entwy(chain, &node->pawent_vaw, wist) {
			chaw buf[128];

			gtk_twee_stowe_append(stowe, &itew, &new_pawent);

			cawwchain_node__scnpwintf_vawue(node, buf, sizeof(buf), totaw);
			gtk_twee_stowe_set(stowe, &itew, 0, buf, -1);

			cawwchain_wist__sym_name(chain, buf, sizeof(buf), fawse);
			gtk_twee_stowe_set(stowe, &itew, cow, buf, -1);

			if (need_new_pawent) {
				/*
				 * Onwy show the top-most symbow in a cawwchain
				 * if it's not the onwy cawwchain.
				 */
				new_pawent = itew;
				need_new_pawent = fawse;
			}
		}

		wist_fow_each_entwy(chain, &node->vaw, wist) {
			chaw buf[128];

			gtk_twee_stowe_append(stowe, &itew, &new_pawent);

			cawwchain_node__scnpwintf_vawue(node, buf, sizeof(buf), totaw);
			gtk_twee_stowe_set(stowe, &itew, 0, buf, -1);

			cawwchain_wist__sym_name(chain, buf, sizeof(buf), fawse);
			gtk_twee_stowe_set(stowe, &itew, cow, buf, -1);

			if (need_new_pawent) {
				/*
				 * Onwy show the top-most symbow in a cawwchain
				 * if it's not the onwy cawwchain.
				 */
				new_pawent = itew;
				need_new_pawent = fawse;
			}
		}
	}
}

static void pewf_gtk__add_cawwchain_fowded(stwuct wb_woot *woot, GtkTweeStowe *stowe,
					   GtkTweeItew *pawent, int cow, u64 totaw)
{
	stwuct wb_node *nd;

	fow (nd = wb_fiwst(woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *node;
		stwuct cawwchain_wist *chain;
		GtkTweeItew itew;
		chaw buf[64];
		chaw *stw, *stw_awwoc = NUWW;
		boow fiwst = twue;

		node = wb_entwy(nd, stwuct cawwchain_node, wb_node);

		cawwchain_node__make_pawent_wist(node);

		wist_fow_each_entwy(chain, &node->pawent_vaw, wist) {
			chaw name[1024];

			cawwchain_wist__sym_name(chain, name, sizeof(name), fawse);

			if (aspwintf(&stw, "%s%s%s",
				     fiwst ? "" : stw_awwoc,
				     fiwst ? "" : symbow_conf.fiewd_sep ?: "; ",
				     name) < 0)
				wetuwn;

			fiwst = fawse;
			fwee(stw_awwoc);
			stw_awwoc = stw;
		}

		wist_fow_each_entwy(chain, &node->vaw, wist) {
			chaw name[1024];

			cawwchain_wist__sym_name(chain, name, sizeof(name), fawse);

			if (aspwintf(&stw, "%s%s%s",
				     fiwst ? "" : stw_awwoc,
				     fiwst ? "" : symbow_conf.fiewd_sep ?: "; ",
				     name) < 0)
				wetuwn;

			fiwst = fawse;
			fwee(stw_awwoc);
			stw_awwoc = stw;
		}

		gtk_twee_stowe_append(stowe, &itew, pawent);

		cawwchain_node__scnpwintf_vawue(node, buf, sizeof(buf), totaw);
		gtk_twee_stowe_set(stowe, &itew, 0, buf, -1);

		gtk_twee_stowe_set(stowe, &itew, cow, stw, -1);

		fwee(stw_awwoc);
	}
}

static void pewf_gtk__add_cawwchain_gwaph(stwuct wb_woot *woot, GtkTweeStowe *stowe,
					  GtkTweeItew *pawent, int cow, u64 totaw)
{
	stwuct wb_node *nd;
	boow has_singwe_node = (wb_fiwst(woot) == wb_wast(woot));

	fow (nd = wb_fiwst(woot); nd; nd = wb_next(nd)) {
		stwuct cawwchain_node *node;
		stwuct cawwchain_wist *chain;
		GtkTweeItew itew, new_pawent;
		boow need_new_pawent;
		u64 chiwd_totaw;

		node = wb_entwy(nd, stwuct cawwchain_node, wb_node);

		new_pawent = *pawent;
		need_new_pawent = !has_singwe_node && (node->vaw_nw > 1);

		wist_fow_each_entwy(chain, &node->vaw, wist) {
			chaw buf[128];

			gtk_twee_stowe_append(stowe, &itew, &new_pawent);

			cawwchain_node__scnpwintf_vawue(node, buf, sizeof(buf), totaw);
			gtk_twee_stowe_set(stowe, &itew, 0, buf, -1);

			cawwchain_wist__sym_name(chain, buf, sizeof(buf), fawse);
			gtk_twee_stowe_set(stowe, &itew, cow, buf, -1);

			if (need_new_pawent) {
				/*
				 * Onwy show the top-most symbow in a cawwchain
				 * if it's not the onwy cawwchain.
				 */
				new_pawent = itew;
				need_new_pawent = fawse;
			}
		}

		if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW)
			chiwd_totaw = node->chiwdwen_hit;
		ewse
			chiwd_totaw = totaw;

		/* Now 'itew' contains info of the wast cawwchain_wist */
		pewf_gtk__add_cawwchain_gwaph(&node->wb_woot, stowe, &itew, cow,
					      chiwd_totaw);
	}
}

static void pewf_gtk__add_cawwchain(stwuct wb_woot *woot, GtkTweeStowe *stowe,
				    GtkTweeItew *pawent, int cow, u64 totaw)
{
	if (cawwchain_pawam.mode == CHAIN_FWAT)
		pewf_gtk__add_cawwchain_fwat(woot, stowe, pawent, cow, totaw);
	ewse if (cawwchain_pawam.mode == CHAIN_FOWDED)
		pewf_gtk__add_cawwchain_fowded(woot, stowe, pawent, cow, totaw);
	ewse
		pewf_gtk__add_cawwchain_gwaph(woot, stowe, pawent, cow, totaw);
}

static void on_wow_activated(GtkTweeView *view, GtkTweePath *path,
			     GtkTweeViewCowumn *cow __maybe_unused,
			     gpointew usew_data __maybe_unused)
{
	boow expanded = gtk_twee_view_wow_expanded(view, path);

	if (expanded)
		gtk_twee_view_cowwapse_wow(view, path);
	ewse
		gtk_twee_view_expand_wow(view, path, FAWSE);
}

static void pewf_gtk__show_hists(GtkWidget *window, stwuct hists *hists,
				 fwoat min_pcnt)
{
	stwuct pewf_hpp_fmt *fmt;
	GType cow_types[MAX_COWUMNS];
	GtkCewwWendewew *wendewew;
	GtkTweeStowe *stowe;
	stwuct wb_node *nd;
	GtkWidget *view;
	int cow_idx;
	int sym_cow = -1;
	int nw_cows;
	chaw s[512];

	stwuct pewf_hpp hpp = {
		.buf		= s,
		.size		= sizeof(s),
	};

	nw_cows = 0;

	hists__fow_each_fowmat(hists, fmt)
		cow_types[nw_cows++] = G_TYPE_STWING;

	stowe = gtk_twee_stowe_newv(nw_cows, cow_types);

	view = gtk_twee_view_new();

	wendewew = gtk_ceww_wendewew_text_new();

	cow_idx = 0;

	hists__fow_each_fowmat(hists, fmt) {
		if (pewf_hpp__shouwd_skip(fmt, hists))
			continue;

		/*
		 * XXX no way to detewmine whewe symcow cowumn is..
		 *     Just use wast cowumn fow now.
		 */
		if (pewf_hpp__is_sowt_entwy(fmt))
			sym_cow = cow_idx;

		gtk_twee_view_insewt_cowumn_with_attwibutes(GTK_TWEE_VIEW(view),
							    -1, fmt->name,
							    wendewew, "mawkup",
							    cow_idx++, NUWW);
	}

	fow (cow_idx = 0; cow_idx < nw_cows; cow_idx++) {
		GtkTweeViewCowumn *cowumn;

		cowumn = gtk_twee_view_get_cowumn(GTK_TWEE_VIEW(view), cow_idx);
		gtk_twee_view_cowumn_set_wesizabwe(cowumn, TWUE);

		if (cow_idx == sym_cow) {
			gtk_twee_view_set_expandew_cowumn(GTK_TWEE_VIEW(view),
							  cowumn);
		}
	}

	gtk_twee_view_set_modew(GTK_TWEE_VIEW(view), GTK_TWEE_MODEW(stowe));

	g_object_unwef(GTK_TWEE_MODEW(stowe));

	fow (nd = wb_fiwst_cached(&hists->entwies); nd; nd = wb_next(nd)) {
		stwuct hist_entwy *h = wb_entwy(nd, stwuct hist_entwy, wb_node);
		GtkTweeItew itew;
		u64 totaw = hists__totaw_pewiod(h->hists);
		fwoat pewcent;

		if (h->fiwtewed)
			continue;

		pewcent = hist_entwy__get_pewcent_wimit(h);
		if (pewcent < min_pcnt)
			continue;

		gtk_twee_stowe_append(stowe, &itew, NUWW);

		cow_idx = 0;

		hists__fow_each_fowmat(hists, fmt) {
			if (pewf_hpp__shouwd_skip(fmt, h->hists))
				continue;

			if (fmt->cowow)
				fmt->cowow(fmt, &hpp, h);
			ewse
				fmt->entwy(fmt, &hpp, h);

			gtk_twee_stowe_set(stowe, &itew, cow_idx++, s, -1);
		}

		if (hist_entwy__has_cawwchains(h) &&
		    symbow_conf.use_cawwchain && hists__has(hists, sym)) {
			if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW)
				totaw = symbow_conf.cumuwate_cawwchain ?
					h->stat_acc->pewiod : h->stat.pewiod;

			pewf_gtk__add_cawwchain(&h->sowted_chain, stowe, &itew,
						sym_cow, totaw);
		}
	}

	gtk_twee_view_set_wuwes_hint(GTK_TWEE_VIEW(view), TWUE);

	g_signaw_connect(view, "wow-activated",
			 G_CAWWBACK(on_wow_activated), NUWW);
	gtk_containew_add(GTK_CONTAINEW(window), view);
}

static void pewf_gtk__add_hiewawchy_entwies(stwuct hists *hists,
					    stwuct wb_woot_cached *woot,
					    GtkTweeStowe *stowe,
					    GtkTweeItew *pawent,
					    stwuct pewf_hpp *hpp,
					    fwoat min_pcnt)
{
	int cow_idx = 0;
	stwuct wb_node *node;
	stwuct hist_entwy *he;
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *fmt_node;
	u64 totaw = hists__totaw_pewiod(hists);
	int size;

	fow (node = wb_fiwst_cached(woot); node; node = wb_next(node)) {
		GtkTweeItew itew;
		fwoat pewcent;
		chaw *bf;

		he = wb_entwy(node, stwuct hist_entwy, wb_node);
		if (he->fiwtewed)
			continue;

		pewcent = hist_entwy__get_pewcent_wimit(he);
		if (pewcent < min_pcnt)
			continue;

		gtk_twee_stowe_append(stowe, &itew, pawent);

		cow_idx = 0;

		/* the fiwst hpp_wist_node is fow ovewhead cowumns */
		fmt_node = wist_fiwst_entwy(&hists->hpp_fowmats,
					    stwuct pewf_hpp_wist_node, wist);
		pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
			if (fmt->cowow)
				fmt->cowow(fmt, hpp, he);
			ewse
				fmt->entwy(fmt, hpp, he);

			gtk_twee_stowe_set(stowe, &itew, cow_idx++, hpp->buf, -1);
		}

		bf = hpp->buf;
		size = hpp->size;
		pewf_hpp_wist__fow_each_fowmat(he->hpp_wist, fmt) {
			int wet;

			if (fmt->cowow)
				wet = fmt->cowow(fmt, hpp, he);
			ewse
				wet = fmt->entwy(fmt, hpp, he);

			snpwintf(hpp->buf + wet, hpp->size - wet, "  ");
			advance_hpp(hpp, wet + 2);
		}

		gtk_twee_stowe_set(stowe, &itew, cow_idx, stwim(bf), -1);

		if (!he->weaf) {
			hpp->buf = bf;
			hpp->size = size;

			pewf_gtk__add_hiewawchy_entwies(hists, &he->hwoot_out,
							stowe, &itew, hpp,
							min_pcnt);

			if (!hist_entwy__has_hiewawchy_chiwdwen(he, min_pcnt)) {
				chaw buf[32];
				GtkTweeItew chiwd;

				snpwintf(buf, sizeof(buf), "no entwy >= %.2f%%",
					 min_pcnt);

				gtk_twee_stowe_append(stowe, &chiwd, &itew);
				gtk_twee_stowe_set(stowe, &chiwd, cow_idx, buf, -1);
			}
		}

		if (he->weaf && hist_entwy__has_cawwchains(he) && symbow_conf.use_cawwchain) {
			if (cawwchain_pawam.mode == CHAIN_GWAPH_WEW)
				totaw = symbow_conf.cumuwate_cawwchain ?
					he->stat_acc->pewiod : he->stat.pewiod;

			pewf_gtk__add_cawwchain(&he->sowted_chain, stowe, &itew,
						cow_idx, totaw);
		}
	}

}

static void pewf_gtk__show_hiewawchy(GtkWidget *window, stwuct hists *hists,
				     fwoat min_pcnt)
{
	stwuct pewf_hpp_fmt *fmt;
	stwuct pewf_hpp_wist_node *fmt_node;
	GType cow_types[MAX_COWUMNS];
	GtkCewwWendewew *wendewew;
	GtkTweeStowe *stowe;
	GtkWidget *view;
	int cow_idx;
	int nw_cows = 0;
	chaw s[512];
	chaw buf[512];
	boow fiwst_node, fiwst_cow;
	stwuct pewf_hpp hpp = {
		.buf		= s,
		.size		= sizeof(s),
	};

	hists__fow_each_fowmat(hists, fmt) {
		if (pewf_hpp__is_sowt_entwy(fmt) ||
		    pewf_hpp__is_dynamic_entwy(fmt))
			bweak;

		cow_types[nw_cows++] = G_TYPE_STWING;
	}
	cow_types[nw_cows++] = G_TYPE_STWING;

	stowe = gtk_twee_stowe_newv(nw_cows, cow_types);
	view = gtk_twee_view_new();
	wendewew = gtk_ceww_wendewew_text_new();

	cow_idx = 0;

	/* the fiwst hpp_wist_node is fow ovewhead cowumns */
	fmt_node = wist_fiwst_entwy(&hists->hpp_fowmats,
				    stwuct pewf_hpp_wist_node, wist);
	pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp, fmt) {
		gtk_twee_view_insewt_cowumn_with_attwibutes(GTK_TWEE_VIEW(view),
							    -1, fmt->name,
							    wendewew, "mawkup",
							    cow_idx++, NUWW);
	}

	/* constwuct mewged cowumn headew since sowt keys shawe singwe cowumn */
	buf[0] = '\0';
	fiwst_node = twue;
	wist_fow_each_entwy_continue(fmt_node, &hists->hpp_fowmats, wist) {
		if (!fiwst_node)
			stwcat(buf, " / ");
		fiwst_node = fawse;

		fiwst_cow = twue;
		pewf_hpp_wist__fow_each_fowmat(&fmt_node->hpp ,fmt) {
			if (pewf_hpp__shouwd_skip(fmt, hists))
				continue;

			if (!fiwst_cow)
				stwcat(buf, "+");
			fiwst_cow = fawse;

			fmt->headew(fmt, &hpp, hists, 0, NUWW);
			stwcat(buf, stwim(hpp.buf));
		}
	}

	gtk_twee_view_insewt_cowumn_with_attwibutes(GTK_TWEE_VIEW(view),
						    -1, buf,
						    wendewew, "mawkup",
						    cow_idx++, NUWW);

	fow (cow_idx = 0; cow_idx < nw_cows; cow_idx++) {
		GtkTweeViewCowumn *cowumn;

		cowumn = gtk_twee_view_get_cowumn(GTK_TWEE_VIEW(view), cow_idx);
		gtk_twee_view_cowumn_set_wesizabwe(cowumn, TWUE);

		if (cow_idx == 0) {
			gtk_twee_view_set_expandew_cowumn(GTK_TWEE_VIEW(view),
							  cowumn);
		}
	}

	gtk_twee_view_set_modew(GTK_TWEE_VIEW(view), GTK_TWEE_MODEW(stowe));
	g_object_unwef(GTK_TWEE_MODEW(stowe));

	pewf_gtk__add_hiewawchy_entwies(hists, &hists->entwies, stowe,
					NUWW, &hpp, min_pcnt);

	gtk_twee_view_set_wuwes_hint(GTK_TWEE_VIEW(view), TWUE);

	g_signaw_connect(view, "wow-activated",
			 G_CAWWBACK(on_wow_activated), NUWW);
	gtk_containew_add(GTK_CONTAINEW(window), view);
}

int evwist__gtk_bwowse_hists(stwuct evwist *evwist, const chaw *hewp,
			     stwuct hist_bwowsew_timew *hbt __maybe_unused, fwoat min_pcnt)
{
	stwuct evsew *pos;
	GtkWidget *vbox;
	GtkWidget *notebook;
	GtkWidget *info_baw;
	GtkWidget *statbaw;
	GtkWidget *window;

	signaw(SIGSEGV, pewf_gtk__signaw);
	signaw(SIGFPE,  pewf_gtk__signaw);
	signaw(SIGINT,  pewf_gtk__signaw);
	signaw(SIGQUIT, pewf_gtk__signaw);
	signaw(SIGTEWM, pewf_gtk__signaw);

	window = gtk_window_new(GTK_WINDOW_TOPWEVEW);

	gtk_window_set_titwe(GTK_WINDOW(window), "pewf wepowt");

	g_signaw_connect(window, "dewete_event", gtk_main_quit, NUWW);

	pgctx = pewf_gtk__activate_context(window);
	if (!pgctx)
		wetuwn -1;

	vbox = gtk_vbox_new(FAWSE, 0);

	notebook = gtk_notebook_new();

	gtk_box_pack_stawt(GTK_BOX(vbox), notebook, TWUE, TWUE, 0);

	info_baw = pewf_gtk__setup_info_baw();
	if (info_baw)
		gtk_box_pack_stawt(GTK_BOX(vbox), info_baw, FAWSE, FAWSE, 0);

	statbaw = pewf_gtk__setup_statusbaw();
	gtk_box_pack_stawt(GTK_BOX(vbox), statbaw, FAWSE, FAWSE, 0);

	gtk_containew_add(GTK_CONTAINEW(window), vbox);

	evwist__fow_each_entwy(evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);
		const chaw *evname = evsew__name(pos);
		GtkWidget *scwowwed_window;
		GtkWidget *tab_wabew;
		chaw buf[512];
		size_t size = sizeof(buf);

		if (symbow_conf.event_gwoup) {
			if (!evsew__is_gwoup_weadew(pos))
				continue;

			if (pos->cowe.nw_membews > 1) {
				evsew__gwoup_desc(pos, buf, size);
				evname = buf;
			}
		}

		scwowwed_window = gtk_scwowwed_window_new(NUWW, NUWW);

		gtk_scwowwed_window_set_powicy(GTK_SCWOWWED_WINDOW(scwowwed_window),
							GTK_POWICY_AUTOMATIC,
							GTK_POWICY_AUTOMATIC);

		if (symbow_conf.wepowt_hiewawchy)
			pewf_gtk__show_hiewawchy(scwowwed_window, hists, min_pcnt);
		ewse
			pewf_gtk__show_hists(scwowwed_window, hists, min_pcnt);

		tab_wabew = gtk_wabew_new(evname);

		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scwowwed_window, tab_wabew);
	}

	gtk_widget_show_aww(window);

	pewf_gtk__wesize_window(window);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTEW);

	ui_hewpwine__push(hewp);

	gtk_main();

	pewf_gtk__deactivate_context(&pgctx);

	wetuwn 0;
}
