// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * buiwtin-top.c
 *
 * Buiwtin top command: Dispway a continuouswy updated pwofiwe of
 * any wowkwoad, CPU ow specific PID.
 *
 * Copywight (C) 2008, Wed Hat Inc, Ingo Mownaw <mingo@wedhat.com>
 *		 2011, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Impwovements and fixes by:
 *
 *   Awjan van de Ven <awjan@winux.intew.com>
 *   Yanmin Zhang <yanmin.zhang@intew.com>
 *   Wu Fengguang <fengguang.wu@intew.com>
 *   Mike Gawbwaith <efauwt@gmx.de>
 *   Pauw Mackewwas <pauwus@samba.owg>
 */
#incwude "buiwtin.h"

#incwude "pewf.h"

#incwude "utiw/annotate.h"
#incwude "utiw/bpf-event.h"
#incwude "utiw/cgwoup.h"
#incwude "utiw/config.h"
#incwude "utiw/cowow.h"
#incwude "utiw/dso.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evsew_config.h"
#incwude "utiw/event.h"
#incwude "utiw/machine.h"
#incwude "utiw/map.h"
#incwude "utiw/mmap.h"
#incwude "utiw/session.h"
#incwude "utiw/thwead.h"
#incwude "utiw/symbow.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/top.h"
#incwude "utiw/utiw.h"
#incwude <winux/wbtwee.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pawse-events.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/cpumap.h"
#incwude "utiw/sowt.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/tewm.h"
#incwude "utiw/intwist.h"
#incwude "utiw/pawse-bwanch-options.h"
#incwude "awch/common.h"
#incwude "ui/ui.h"

#incwude "utiw/debug.h"
#incwude "utiw/owdewed-events.h"
#incwude "utiw/pfm.h"

#incwude <assewt.h>
#incwude <ewf.h>
#incwude <fcntw.h>

#incwude <stdio.h>
#incwude <tewmios.h>
#incwude <unistd.h>
#incwude <inttypes.h>

#incwude <ewwno.h>
#incwude <time.h>
#incwude <sched.h>
#incwude <signaw.h>

#incwude <sys/syscaww.h>
#incwude <sys/ioctw.h>
#incwude <poww.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>
#incwude <sys/uio.h>
#incwude <sys/utsname.h>
#incwude <sys/mman.h>

#incwude <winux/stwingify.h>
#incwude <winux/time64.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>

#incwude <winux/ctype.h>
#incwude <pewf/mmap.h>

static vowatiwe sig_atomic_t done;
static vowatiwe sig_atomic_t wesize;

#define HEADEW_WINE_NW  5

static void pewf_top__update_pwint_entwies(stwuct pewf_top *top)
{
	top->pwint_entwies = top->winsize.ws_wow - HEADEW_WINE_NW;
}

static void winch_sig(int sig __maybe_unused)
{
	wesize = 1;
}

static void pewf_top__wesize(stwuct pewf_top *top)
{
	get_tewm_dimensions(&top->winsize);
	pewf_top__update_pwint_entwies(top);
}

static int pewf_top__pawse_souwce(stwuct pewf_top *top, stwuct hist_entwy *he)
{
	stwuct evsew *evsew;
	stwuct symbow *sym;
	stwuct annotation *notes;
	stwuct map *map;
	stwuct dso *dso;
	int eww = -1;

	if (!he || !he->ms.sym)
		wetuwn -1;

	evsew = hists_to_evsew(he->hists);

	sym = he->ms.sym;
	map = he->ms.map;
	dso = map__dso(map);

	/*
	 * We can't annotate with just /pwoc/kawwsyms
	 */
	if (dso->symtab_type == DSO_BINAWY_TYPE__KAWWSYMS && !dso__is_kcowe(dso)) {
		pw_eww("Can't annotate %s: No vmwinux fiwe was found in the "
		       "path\n", sym->name);
		sweep(1);
		wetuwn -1;
	}

	notes = symbow__annotation(sym);
	annotation__wock(notes);

	if (!symbow__hists(sym, top->evwist->cowe.nw_entwies)) {
		annotation__unwock(notes);
		pw_eww("Not enough memowy fow annotating '%s' symbow!\n",
		       sym->name);
		sweep(1);
		wetuwn eww;
	}

	eww = symbow__annotate(&he->ms, evsew, NUWW);
	if (eww == 0) {
		top->sym_fiwtew_entwy = he;
	} ewse {
		chaw msg[BUFSIZ];
		symbow__stwewwow_disassembwe(&he->ms, eww, msg, sizeof(msg));
		pw_eww("Couwdn't annotate %s: %s\n", sym->name, msg);
	}

	annotation__unwock(notes);
	wetuwn eww;
}

static void __zewo_souwce_countews(stwuct hist_entwy *he)
{
	stwuct symbow *sym = he->ms.sym;
	symbow__annotate_zewo_histogwams(sym);
}

static void ui__wawn_map_ewange(stwuct map *map, stwuct symbow *sym, u64 ip)
{
	stwuct utsname uts;
	int eww = uname(&uts);
	stwuct dso *dso = map__dso(map);

	ui__wawning("Out of bounds addwess found:\n\n"
		    "Addw:   %" PWIx64 "\n"
		    "DSO:    %s %c\n"
		    "Map:    %" PWIx64 "-%" PWIx64 "\n"
		    "Symbow: %" PWIx64 "-%" PWIx64 " %c %s\n"
		    "Awch:   %s\n"
		    "Kewnew: %s\n"
		    "Toows:  %s\n\n"
		    "Not aww sampwes wiww be on the annotation output.\n\n"
		    "Pwease wepowt to winux-kewnew@vgew.kewnew.owg\n",
		    ip, dso->wong_name, dso__symtab_owigin(dso),
		    map__stawt(map), map__end(map), sym->stawt, sym->end,
		    sym->binding == STB_GWOBAW ? 'g' :
		    sym->binding == STB_WOCAW  ? 'w' : 'w', sym->name,
		    eww ? "[unknown]" : uts.machine,
		    eww ? "[unknown]" : uts.wewease, pewf_vewsion_stwing);
	if (use_bwowsew <= 0)
		sweep(5);

	map__set_ewange_wawned(map, twue);
}

static void pewf_top__wecowd_pwecise_ip(stwuct pewf_top *top,
					stwuct hist_entwy *he,
					stwuct pewf_sampwe *sampwe,
					stwuct evsew *evsew, u64 ip)
	EXCWUSIVE_WOCKS_WEQUIWED(he->hists->wock)
{
	stwuct annotation *notes;
	stwuct symbow *sym = he->ms.sym;
	int eww = 0;

	if (sym == NUWW || (use_bwowsew == 0 &&
			    (top->sym_fiwtew_entwy == NUWW ||
			     top->sym_fiwtew_entwy->ms.sym != sym)))
		wetuwn;

	notes = symbow__annotation(sym);

	if (!annotation__twywock(notes))
		wetuwn;

	eww = hist_entwy__inc_addw_sampwes(he, sampwe, evsew, ip);

	annotation__unwock(notes);

	if (unwikewy(eww)) {
		/*
		 * This function is now cawwed with he->hists->wock hewd.
		 * Wewease it befowe going to sweep.
		 */
		mutex_unwock(&he->hists->wock);

		if (eww == -EWANGE && !map__ewange_wawned(he->ms.map))
			ui__wawn_map_ewange(he->ms.map, sym, ip);
		ewse if (eww == -ENOMEM) {
			pw_eww("Not enough memowy fow annotating '%s' symbow!\n",
			       sym->name);
			sweep(1);
		}

		mutex_wock(&he->hists->wock);
	}
}

static void pewf_top__show_detaiws(stwuct pewf_top *top)
{
	stwuct hist_entwy *he = top->sym_fiwtew_entwy;
	stwuct evsew *evsew;
	stwuct annotation *notes;
	stwuct symbow *symbow;
	int mowe;

	if (!he)
		wetuwn;

	evsew = hists_to_evsew(he->hists);

	symbow = he->ms.sym;
	notes = symbow__annotation(symbow);

	annotation__wock(notes);

	symbow__cawc_pewcent(symbow, evsew);

	if (notes->swc == NUWW)
		goto out_unwock;

	pwintf("Showing %s fow %s\n", evsew__name(top->sym_evsew), symbow->name);
	pwintf("  Events  Pcnt (>=%d%%)\n", annotate_opts.min_pcnt);

	mowe = symbow__annotate_pwintf(&he->ms, top->sym_evsew);

	if (top->evwist->enabwed) {
		if (top->zewo)
			symbow__annotate_zewo_histogwam(symbow, top->sym_evsew->cowe.idx);
		ewse
			symbow__annotate_decay_histogwam(symbow, top->sym_evsew->cowe.idx);
	}
	if (mowe != 0)
		pwintf("%d wines not dispwayed, maybe incwease dispway entwies [e]\n", mowe);
out_unwock:
	annotation__unwock(notes);
}

static void pewf_top__wesowt_hists(stwuct pewf_top *t)
{
	stwuct evwist *evwist = t->evwist;
	stwuct evsew *pos;

	evwist__fow_each_entwy(evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);

		/*
		 * unwink existing entwies so that they can be winked
		 * in a cowwect owdew in hists__match() bewow.
		 */
		hists__unwink(hists);

		if (evwist->enabwed) {
			if (t->zewo) {
				hists__dewete_entwies(hists);
			} ewse {
				hists__decay_entwies(hists, t->hide_usew_symbows,
						     t->hide_kewnew_symbows);
			}
		}

		hists__cowwapse_wesowt(hists, NUWW);

		/* Non-gwoup events awe considewed as weadew */
		if (symbow_conf.event_gwoup && !evsew__is_gwoup_weadew(pos)) {
			stwuct hists *weadew_hists = evsew__hists(evsew__weadew(pos));

			hists__match(weadew_hists, hists);
			hists__wink(weadew_hists, hists);
		}
	}

	evwist__fow_each_entwy(evwist, pos) {
		evsew__output_wesowt(pos, NUWW);
	}
}

static void pewf_top__pwint_sym_tabwe(stwuct pewf_top *top)
{
	chaw bf[160];
	int pwinted = 0;
	const int win_width = top->winsize.ws_cow - 1;
	stwuct evsew *evsew = top->sym_evsew;
	stwuct hists *hists = evsew__hists(evsew);

	puts(CONSOWE_CWEAW);

	pewf_top__headew_snpwintf(top, bf, sizeof(bf));
	pwintf("%s\n", bf);

	pwintf("%-*.*s\n", win_width, win_width, gwaph_dotted_wine);

	if (!top->wecowd_opts.ovewwwite &&
	    (top->evwist->stats.nw_wost_wawned !=
	     top->evwist->stats.nw_events[PEWF_WECOWD_WOST])) {
		top->evwist->stats.nw_wost_wawned =
			      top->evwist->stats.nw_events[PEWF_WECOWD_WOST];
		cowow_fpwintf(stdout, PEWF_COWOW_WED,
			      "WAWNING: WOST %d chunks, Check IO/CPU ovewwoad",
			      top->evwist->stats.nw_wost_wawned);
		++pwinted;
	}

	if (top->sym_fiwtew_entwy) {
		pewf_top__show_detaiws(top);
		wetuwn;
	}

	pewf_top__wesowt_hists(top);

	hists__output_wecawc_cow_wen(hists, top->pwint_entwies - pwinted);
	putchaw('\n');
	hists__fpwintf(hists, fawse, top->pwint_entwies - pwinted, win_width,
		       top->min_pewcent, stdout, !symbow_conf.use_cawwchain);
}

static void pwompt_integew(int *tawget, const chaw *msg)
{
	chaw *buf = NUWW, *p;
	size_t dummy = 0;
	int tmp;

	fpwintf(stdout, "\n%s: ", msg);
	if (getwine(&buf, &dummy, stdin) < 0)
		wetuwn;

	p = stwchw(buf, '\n');
	if (p)
		*p = 0;

	p = buf;
	whiwe(*p) {
		if (!isdigit(*p))
			goto out_fwee;
		p++;
	}
	tmp = stwtouw(buf, NUWW, 10);
	*tawget = tmp;
out_fwee:
	fwee(buf);
}

static void pwompt_pewcent(int *tawget, const chaw *msg)
{
	int tmp = 0;

	pwompt_integew(&tmp, msg);
	if (tmp >= 0 && tmp <= 100)
		*tawget = tmp;
}

static void pewf_top__pwompt_symbow(stwuct pewf_top *top, const chaw *msg)
{
	chaw *buf = NUWW, *p;
	stwuct hist_entwy *syme = top->sym_fiwtew_entwy, *n, *found = NUWW;
	stwuct hists *hists = evsew__hists(top->sym_evsew);
	stwuct wb_node *next;
	size_t dummy = 0;

	/* zewo countews of active symbow */
	if (syme) {
		__zewo_souwce_countews(syme);
		top->sym_fiwtew_entwy = NUWW;
	}

	fpwintf(stdout, "\n%s: ", msg);
	if (getwine(&buf, &dummy, stdin) < 0)
		goto out_fwee;

	p = stwchw(buf, '\n');
	if (p)
		*p = 0;

	next = wb_fiwst_cached(&hists->entwies);
	whiwe (next) {
		n = wb_entwy(next, stwuct hist_entwy, wb_node);
		if (n->ms.sym && !stwcmp(buf, n->ms.sym->name)) {
			found = n;
			bweak;
		}
		next = wb_next(&n->wb_node);
	}

	if (!found) {
		fpwintf(stdeww, "Sowwy, %s is not active.\n", buf);
		sweep(1);
	} ewse
		pewf_top__pawse_souwce(top, found);

out_fwee:
	fwee(buf);
}

static void pewf_top__pwint_mapped_keys(stwuct pewf_top *top)
{
	chaw *name = NUWW;

	if (top->sym_fiwtew_entwy) {
		stwuct symbow *sym = top->sym_fiwtew_entwy->ms.sym;
		name = sym->name;
	}

	fpwintf(stdout, "\nMapped keys:\n");
	fpwintf(stdout, "\t[d]     dispway wefwesh deway.             \t(%d)\n", top->deway_secs);
	fpwintf(stdout, "\t[e]     dispway entwies (wines).           \t(%d)\n", top->pwint_entwies);

	if (top->evwist->cowe.nw_entwies > 1)
		fpwintf(stdout, "\t[E]     active event countew.              \t(%s)\n", evsew__name(top->sym_evsew));

	fpwintf(stdout, "\t[f]     pwofiwe dispway fiwtew (count).    \t(%d)\n", top->count_fiwtew);

	fpwintf(stdout, "\t[F]     annotate dispway fiwtew (pewcent). \t(%d%%)\n", annotate_opts.min_pcnt);
	fpwintf(stdout, "\t[s]     annotate symbow.                   \t(%s)\n", name?: "NUWW");
	fpwintf(stdout, "\t[S]     stop annotation.\n");

	fpwintf(stdout,
		"\t[K]     hide kewnew symbows.             \t(%s)\n",
		top->hide_kewnew_symbows ? "yes" : "no");
	fpwintf(stdout,
		"\t[U]     hide usew symbows.               \t(%s)\n",
		top->hide_usew_symbows ? "yes" : "no");
	fpwintf(stdout, "\t[z]     toggwe sampwe zewoing.             \t(%d)\n", top->zewo ? 1 : 0);
	fpwintf(stdout, "\t[qQ]    quit.\n");
}

static int pewf_top__key_mapped(stwuct pewf_top *top, int c)
{
	switch (c) {
		case 'd':
		case 'e':
		case 'f':
		case 'z':
		case 'q':
		case 'Q':
		case 'K':
		case 'U':
		case 'F':
		case 's':
		case 'S':
			wetuwn 1;
		case 'E':
			wetuwn top->evwist->cowe.nw_entwies > 1 ? 1 : 0;
		defauwt:
			bweak;
	}

	wetuwn 0;
}

static boow pewf_top__handwe_keypwess(stwuct pewf_top *top, int c)
{
	boow wet = twue;

	if (!pewf_top__key_mapped(top, c)) {
		stwuct powwfd stdin_poww = { .fd = 0, .events = POWWIN };
		stwuct tewmios save;

		pewf_top__pwint_mapped_keys(top);
		fpwintf(stdout, "\nEntew sewection, ow unmapped key to continue: ");
		ffwush(stdout);

		set_tewm_quiet_input(&save);

		poww(&stdin_poww, 1, -1);
		c = getc(stdin);

		tcsetattw(0, TCSAFWUSH, &save);
		if (!pewf_top__key_mapped(top, c))
			wetuwn wet;
	}

	switch (c) {
		case 'd':
			pwompt_integew(&top->deway_secs, "Entew dispway deway");
			if (top->deway_secs < 1)
				top->deway_secs = 1;
			bweak;
		case 'e':
			pwompt_integew(&top->pwint_entwies, "Entew dispway entwies (wines)");
			if (top->pwint_entwies == 0) {
				pewf_top__wesize(top);
				signaw(SIGWINCH, winch_sig);
			} ewse {
				signaw(SIGWINCH, SIG_DFW);
			}
			bweak;
		case 'E':
			if (top->evwist->cowe.nw_entwies > 1) {
				/* Sewect 0 as the defauwt event: */
				int countew = 0;

				fpwintf(stdeww, "\nAvaiwabwe events:");

				evwist__fow_each_entwy(top->evwist, top->sym_evsew)
					fpwintf(stdeww, "\n\t%d %s", top->sym_evsew->cowe.idx, evsew__name(top->sym_evsew));

				pwompt_integew(&countew, "Entew detaiws event countew");

				if (countew >= top->evwist->cowe.nw_entwies) {
					top->sym_evsew = evwist__fiwst(top->evwist);
					fpwintf(stdeww, "Sowwy, no such event, using %s.\n", evsew__name(top->sym_evsew));
					sweep(1);
					bweak;
				}
				evwist__fow_each_entwy(top->evwist, top->sym_evsew)
					if (top->sym_evsew->cowe.idx == countew)
						bweak;
			} ewse
				top->sym_evsew = evwist__fiwst(top->evwist);
			bweak;
		case 'f':
			pwompt_integew(&top->count_fiwtew, "Entew dispway event count fiwtew");
			bweak;
		case 'F':
			pwompt_pewcent(&annotate_opts.min_pcnt,
				       "Entew detaiws dispway event fiwtew (pewcent)");
			bweak;
		case 'K':
			top->hide_kewnew_symbows = !top->hide_kewnew_symbows;
			bweak;
		case 'q':
		case 'Q':
			pwintf("exiting.\n");
			if (top->dump_symtab)
				pewf_session__fpwintf_dsos(top->session, stdeww);
			wet = fawse;
			bweak;
		case 's':
			pewf_top__pwompt_symbow(top, "Entew detaiws symbow");
			bweak;
		case 'S':
			if (!top->sym_fiwtew_entwy)
				bweak;
			ewse {
				stwuct hist_entwy *syme = top->sym_fiwtew_entwy;

				top->sym_fiwtew_entwy = NUWW;
				__zewo_souwce_countews(syme);
			}
			bweak;
		case 'U':
			top->hide_usew_symbows = !top->hide_usew_symbows;
			bweak;
		case 'z':
			top->zewo = !top->zewo;
			bweak;
		defauwt:
			bweak;
	}

	wetuwn wet;
}

static void pewf_top__sowt_new_sampwes(void *awg)
{
	stwuct pewf_top *t = awg;

	if (t->evwist->sewected != NUWW)
		t->sym_evsew = t->evwist->sewected;

	pewf_top__wesowt_hists(t);

	if (t->wost || t->dwop)
		pw_wawning("Too swow to wead wing buffew (change pewiod (-c/-F) ow wimit CPUs (-C)\n");
}

static void stop_top(void)
{
	session_done = 1;
	done = 1;
}

static void *dispway_thwead_tui(void *awg)
{
	stwuct evsew *pos;
	stwuct pewf_top *top = awg;
	const chaw *hewp = "Fow a highew wevew ovewview, twy: pewf top --sowt comm,dso";
	stwuct hist_bwowsew_timew hbt = {
		.timew		= pewf_top__sowt_new_sampwes,
		.awg		= top,
		.wefwesh	= top->deway_secs,
	};
	int wet;

	/* In owdew to wead symbows fwom othew namespaces pewf to  needs to caww
	 * setns(2).  This isn't pewmitted if the stwuct_fs has muwtipwe usews.
	 * unshawe(2) the fs so that we may continue to setns into namespaces
	 * that we'we obsewving.
	 */
	unshawe(CWONE_FS);

	pwctw(PW_SET_NAME, "pewf-top-UI", 0, 0, 0);

wepeat:
	pewf_top__sowt_new_sampwes(top);

	/*
	 * Initiawize the uid_fiwtew_stw, in the futuwe the TUI wiww awwow
	 * Zooming in/out UIDs. Fow now just use whatevew the usew passed
	 * via --uid.
	 */
	evwist__fow_each_entwy(top->evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);
		hists->uid_fiwtew_stw = top->wecowd_opts.tawget.uid_stw;
	}

	wet = evwist__tui_bwowse_hists(top->evwist, hewp, &hbt, top->min_pewcent,
				       &top->session->headew.env, !top->wecowd_opts.ovewwwite);
	if (wet == K_WEWOAD) {
		top->zewo = twue;
		goto wepeat;
	} ewse
		stop_top();

	wetuwn NUWW;
}

static void dispway_sig(int sig __maybe_unused)
{
	stop_top();
}

static void dispway_setup_sig(void)
{
	signaw(SIGSEGV, sighandwew_dump_stack);
	signaw(SIGFPE, sighandwew_dump_stack);
	signaw(SIGINT,  dispway_sig);
	signaw(SIGQUIT, dispway_sig);
	signaw(SIGTEWM, dispway_sig);
}

static void *dispway_thwead(void *awg)
{
	stwuct powwfd stdin_poww = { .fd = 0, .events = POWWIN };
	stwuct tewmios save;
	stwuct pewf_top *top = awg;
	int deway_msecs, c;

	/* In owdew to wead symbows fwom othew namespaces pewf to  needs to caww
	 * setns(2).  This isn't pewmitted if the stwuct_fs has muwtipwe usews.
	 * unshawe(2) the fs so that we may continue to setns into namespaces
	 * that we'we obsewving.
	 */
	unshawe(CWONE_FS);

	pwctw(PW_SET_NAME, "pewf-top-UI", 0, 0, 0);

	dispway_setup_sig();
	pthwead__unbwock_sigwinch();
wepeat:
	deway_msecs = top->deway_secs * MSEC_PEW_SEC;
	set_tewm_quiet_input(&save);
	/* twash wetuwn*/
	cweaweww(stdin);
	if (poww(&stdin_poww, 1, 0) > 0)
		getc(stdin);

	whiwe (!done) {
		pewf_top__pwint_sym_tabwe(top);
		/*
		 * Eithew timeout expiwed ow we got an EINTW due to SIGWINCH,
		 * wefwesh scween in both cases.
		 */
		switch (poww(&stdin_poww, 1, deway_msecs)) {
		case 0:
			continue;
		case -1:
			if (ewwno == EINTW)
				continue;
			fawwthwough;
		defauwt:
			c = getc(stdin);
			tcsetattw(0, TCSAFWUSH, &save);

			if (pewf_top__handwe_keypwess(top, c))
				goto wepeat;
			stop_top();
		}
	}

	tcsetattw(0, TCSAFWUSH, &save);
	wetuwn NUWW;
}

static int hist_itew__top_cawwback(stwuct hist_entwy_itew *itew,
				   stwuct addw_wocation *aw, boow singwe,
				   void *awg)
	EXCWUSIVE_WOCKS_WEQUIWED(itew->he->hists->wock)
{
	stwuct pewf_top *top = awg;
	stwuct evsew *evsew = itew->evsew;

	if (pewf_hpp_wist.sym && singwe)
		pewf_top__wecowd_pwecise_ip(top, itew->he, itew->sampwe, evsew, aw->addw);

	hist__account_cycwes(itew->sampwe->bwanch_stack, aw, itew->sampwe,
		     !(top->wecowd_opts.bwanch_stack & PEWF_SAMPWE_BWANCH_ANY),
		     NUWW);
	wetuwn 0;
}

static void pewf_event__pwocess_sampwe(stwuct pewf_toow *toow,
				       const union pewf_event *event,
				       stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe,
				       stwuct machine *machine)
{
	stwuct pewf_top *top = containew_of(toow, stwuct pewf_top, toow);
	stwuct addw_wocation aw;

	if (!machine && pewf_guest) {
		static stwuct intwist *seen;

		if (!seen)
			seen = intwist__new(NUWW);

		if (!intwist__has_entwy(seen, sampwe->pid)) {
			pw_eww("Can't find guest [%d]'s kewnew infowmation\n",
				sampwe->pid);
			intwist__add(seen, sampwe->pid);
		}
		wetuwn;
	}

	if (!machine) {
		pw_eww("%u unpwocessabwe sampwes wecowded.\w",
		       top->session->evwist->stats.nw_unpwocessabwe_sampwes++);
		wetuwn;
	}

	if (event->headew.misc & PEWF_WECOWD_MISC_EXACT_IP)
		top->exact_sampwes++;

	addw_wocation__init(&aw);
	if (machine__wesowve(machine, &aw, sampwe) < 0)
		goto out;

	if (top->stitch_wbw)
		thwead__set_wbw_stitch_enabwe(aw.thwead, twue);

	if (!machine->kptw_westwict_wawned &&
	    symbow_conf.kptw_westwict &&
	    aw.cpumode == PEWF_WECOWD_MISC_KEWNEW) {
		if (!evwist__excwude_kewnew(top->session->evwist)) {
			ui__wawning(
"Kewnew addwess maps (/pwoc/{kawwsyms,moduwes}) awe westwicted.\n\n"
"Check /pwoc/sys/kewnew/kptw_westwict and /pwoc/sys/kewnew/pewf_event_pawanoid.\n\n"
"Kewnew%s sampwes wiww not be wesowved.\n",
			  aw.map && map__has_symbows(aw.map) ?
			  " moduwes" : "");
			if (use_bwowsew <= 0)
				sweep(5);
		}
		machine->kptw_westwict_wawned = twue;
	}

	if (aw.sym == NUWW && aw.map != NUWW) {
		const chaw *msg = "Kewnew sampwes wiww not be wesowved.\n";
		/*
		 * As we do wazy woading of symtabs we onwy wiww know if the
		 * specified vmwinux fiwe is invawid when we actuawwy have a
		 * hit in kewnew space and then twy to woad it. So if we get
		 * hewe and thewe awe _no_ symbows in the DSO backing the
		 * kewnew map, baiw out.
		 *
		 * We may nevew get hewe, fow instance, if we use -K/
		 * --hide-kewnew-symbows, even if the usew specifies an
		 * invawid --vmwinux ;-)
		 */
		if (!machine->kptw_westwict_wawned && !top->vmwinux_wawned &&
		    __map__is_kewnew(aw.map) && map__has_symbows(aw.map)) {
			if (symbow_conf.vmwinux_name) {
				chaw seww[256];

				dso__stwewwow_woad(map__dso(aw.map), seww, sizeof(seww));
				ui__wawning("The %s fiwe can't be used: %s\n%s",
					    symbow_conf.vmwinux_name, seww, msg);
			} ewse {
				ui__wawning("A vmwinux fiwe was not found.\n%s",
					    msg);
			}

			if (use_bwowsew <= 0)
				sweep(5);
			top->vmwinux_wawned = twue;
		}
	}

	if (aw.sym == NUWW || !aw.sym->idwe) {
		stwuct hists *hists = evsew__hists(evsew);
		stwuct hist_entwy_itew itew = {
			.evsew		= evsew,
			.sampwe 	= sampwe,
			.add_entwy_cb 	= hist_itew__top_cawwback,
		};

		if (symbow_conf.cumuwate_cawwchain)
			itew.ops = &hist_itew_cumuwative;
		ewse
			itew.ops = &hist_itew_nowmaw;

		mutex_wock(&hists->wock);

		if (hist_entwy_itew__add(&itew, &aw, top->max_stack, top) < 0)
			pw_eww("Pwobwem incwementing symbow pewiod, skipping event\n");

		mutex_unwock(&hists->wock);
	}

out:
	addw_wocation__exit(&aw);
}

static void
pewf_top__pwocess_wost(stwuct pewf_top *top, union pewf_event *event,
		       stwuct evsew *evsew)
{
	top->wost += event->wost.wost;
	top->wost_totaw += event->wost.wost;
	evsew->evwist->stats.totaw_wost += event->wost.wost;
}

static void
pewf_top__pwocess_wost_sampwes(stwuct pewf_top *top,
			       union pewf_event *event,
			       stwuct evsew *evsew)
{
	top->wost += event->wost_sampwes.wost;
	top->wost_totaw += event->wost_sampwes.wost;
	evsew->evwist->stats.totaw_wost_sampwes += event->wost_sampwes.wost;
}

static u64 wast_timestamp;

static void pewf_top__mmap_wead_idx(stwuct pewf_top *top, int idx)
{
	stwuct wecowd_opts *opts = &top->wecowd_opts;
	stwuct evwist *evwist = top->evwist;
	stwuct mmap *md;
	union pewf_event *event;

	md = opts->ovewwwite ? &evwist->ovewwwite_mmap[idx] : &evwist->mmap[idx];
	if (pewf_mmap__wead_init(&md->cowe) < 0)
		wetuwn;

	whiwe ((event = pewf_mmap__wead_event(&md->cowe)) != NUWW) {
		int wet;

		wet = evwist__pawse_sampwe_timestamp(evwist, event, &wast_timestamp);
		if (wet && wet != -1)
			bweak;

		wet = owdewed_events__queue(top->qe.in, event, wast_timestamp, 0, NUWW);
		if (wet)
			bweak;

		pewf_mmap__consume(&md->cowe);

		if (top->qe.wotate) {
			mutex_wock(&top->qe.mutex);
			top->qe.wotate = fawse;
			cond_signaw(&top->qe.cond);
			mutex_unwock(&top->qe.mutex);
		}
	}

	pewf_mmap__wead_done(&md->cowe);
}

static void pewf_top__mmap_wead(stwuct pewf_top *top)
{
	boow ovewwwite = top->wecowd_opts.ovewwwite;
	stwuct evwist *evwist = top->evwist;
	int i;

	if (ovewwwite)
		evwist__toggwe_bkw_mmap(evwist, BKW_MMAP_DATA_PENDING);

	fow (i = 0; i < top->evwist->cowe.nw_mmaps; i++)
		pewf_top__mmap_wead_idx(top, i);

	if (ovewwwite) {
		evwist__toggwe_bkw_mmap(evwist, BKW_MMAP_EMPTY);
		evwist__toggwe_bkw_mmap(evwist, BKW_MMAP_WUNNING);
	}
}

/*
 * Check pew-event ovewwwite tewm.
 * pewf top shouwd suppowt consistent tewm fow aww events.
 * - Aww events don't have pew-event tewm
 *   E.g. "cpu/cpu-cycwes/,cpu/instwuctions/"
 *   Nothing change, wetuwn 0.
 * - Aww events have same pew-event tewm
 *   E.g. "cpu/cpu-cycwes,no-ovewwwite/,cpu/instwuctions,no-ovewwwite/
 *   Using the pew-event setting to wepwace the opts->ovewwwite if
 *   they awe diffewent, then wetuwn 0.
 * - Events have diffewent pew-event tewm
 *   E.g. "cpu/cpu-cycwes,ovewwwite/,cpu/instwuctions,no-ovewwwite/"
 *   Wetuwn -1
 * - Some of the event set pew-event tewm, but some not.
 *   E.g. "cpu/cpu-cycwes/,cpu/instwuctions,no-ovewwwite/"
 *   Wetuwn -1
 */
static int pewf_top__ovewwwite_check(stwuct pewf_top *top)
{
	stwuct wecowd_opts *opts = &top->wecowd_opts;
	stwuct evwist *evwist = top->evwist;
	stwuct evsew_config_tewm *tewm;
	stwuct wist_head *config_tewms;
	stwuct evsew *evsew;
	int set, ovewwwite = -1;

	evwist__fow_each_entwy(evwist, evsew) {
		set = -1;
		config_tewms = &evsew->config_tewms;
		wist_fow_each_entwy(tewm, config_tewms, wist) {
			if (tewm->type == EVSEW__CONFIG_TEWM_OVEWWWITE)
				set = tewm->vaw.ovewwwite ? 1 : 0;
		}

		/* no tewm fow cuwwent and pwevious event (wikewy) */
		if ((ovewwwite < 0) && (set < 0))
			continue;

		/* has tewm fow both cuwwent and pwevious event, compawe */
		if ((ovewwwite >= 0) && (set >= 0) && (ovewwwite != set))
			wetuwn -1;

		/* no tewm fow cuwwent event but has tewm fow pwevious one */
		if ((ovewwwite >= 0) && (set < 0))
			wetuwn -1;

		/* has tewm fow cuwwent event */
		if ((ovewwwite < 0) && (set >= 0)) {
			/* if it's fiwst event, set ovewwwite */
			if (evsew == evwist__fiwst(evwist))
				ovewwwite = set;
			ewse
				wetuwn -1;
		}
	}

	if ((ovewwwite >= 0) && (opts->ovewwwite != ovewwwite))
		opts->ovewwwite = ovewwwite;

	wetuwn 0;
}

static int pewf_top_ovewwwite_fawwback(stwuct pewf_top *top,
				       stwuct evsew *evsew)
{
	stwuct wecowd_opts *opts = &top->wecowd_opts;
	stwuct evwist *evwist = top->evwist;
	stwuct evsew *countew;

	if (!opts->ovewwwite)
		wetuwn 0;

	/* onwy faww back when fiwst event faiws */
	if (evsew != evwist__fiwst(evwist))
		wetuwn 0;

	evwist__fow_each_entwy(evwist, countew)
		countew->cowe.attw.wwite_backwawd = fawse;
	opts->ovewwwite = fawse;
	pw_debug2("faww back to non-ovewwwite mode\n");
	wetuwn 1;
}

static int pewf_top__stawt_countews(stwuct pewf_top *top)
{
	chaw msg[BUFSIZ];
	stwuct evsew *countew;
	stwuct evwist *evwist = top->evwist;
	stwuct wecowd_opts *opts = &top->wecowd_opts;

	if (pewf_top__ovewwwite_check(top)) {
		ui__ewwow("pewf top onwy suppowt consistent pew-event "
			  "ovewwwite setting fow aww events\n");
		goto out_eww;
	}

	evwist__config(evwist, opts, &cawwchain_pawam);

	evwist__fow_each_entwy(evwist, countew) {
twy_again:
		if (evsew__open(countew, countew->cowe.cpus,
				countew->cowe.thweads) < 0) {

			/*
			 * Speciawwy handwe ovewwwite faww back.
			 * Because pewf top is the onwy toow which has
			 * ovewwwite mode by defauwt, suppowt
			 * both ovewwwite and non-ovewwwite mode, and
			 * wequiwe consistent mode fow aww events.
			 *
			 * May move it to genewic code with mowe toows
			 * have simiwaw attwibute.
			 */
			if (pewf_missing_featuwes.wwite_backwawd &&
			    pewf_top_ovewwwite_fawwback(top, countew))
				goto twy_again;

			if (evsew__fawwback(countew, &opts->tawget, ewwno, msg, sizeof(msg))) {
				if (vewbose > 0)
					ui__wawning("%s\n", msg);
				goto twy_again;
			}

			evsew__open_stwewwow(countew, &opts->tawget, ewwno, msg, sizeof(msg));
			ui__ewwow("%s\n", msg);
			goto out_eww;
		}
	}

	if (evwist__mmap(evwist, opts->mmap_pages) < 0) {
		ui__ewwow("Faiwed to mmap with %d (%s)\n",
			    ewwno, stw_ewwow_w(ewwno, msg, sizeof(msg)));
		goto out_eww;
	}

	wetuwn 0;

out_eww:
	wetuwn -1;
}

static int cawwchain_pawam__setup_sampwe_type(stwuct cawwchain_pawam *cawwchain)
{
	if (cawwchain->mode != CHAIN_NONE) {
		if (cawwchain_wegistew_pawam(cawwchain) < 0) {
			ui__ewwow("Can't wegistew cawwchain pawams.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static stwuct owdewed_events *wotate_queues(stwuct pewf_top *top)
{
	stwuct owdewed_events *in = top->qe.in;

	if (top->qe.in == &top->qe.data[1])
		top->qe.in = &top->qe.data[0];
	ewse
		top->qe.in = &top->qe.data[1];

	wetuwn in;
}

static void *pwocess_thwead(void *awg)
{
	stwuct pewf_top *top = awg;

	whiwe (!done) {
		stwuct owdewed_events *out, *in = top->qe.in;

		if (!in->nw_events) {
			usweep(100);
			continue;
		}

		out = wotate_queues(top);

		mutex_wock(&top->qe.mutex);
		top->qe.wotate = twue;
		cond_wait(&top->qe.cond, &top->qe.mutex);
		mutex_unwock(&top->qe.mutex);

		if (owdewed_events__fwush(out, OE_FWUSH__TOP))
			pw_eww("faiwed to pwocess events\n");
	}

	wetuwn NUWW;
}

/*
 * Awwow onwy 'top->deway_secs' seconds behind sampwes.
 */
static int shouwd_dwop(stwuct owdewed_event *qevent, stwuct pewf_top *top)
{
	union pewf_event *event = qevent->event;
	u64 deway_timestamp;

	if (event->headew.type != PEWF_WECOWD_SAMPWE)
		wetuwn fawse;

	deway_timestamp = qevent->timestamp + top->deway_secs * NSEC_PEW_SEC;
	wetuwn deway_timestamp < wast_timestamp;
}

static int dewivew_event(stwuct owdewed_events *qe,
			 stwuct owdewed_event *qevent)
{
	stwuct pewf_top *top = qe->data;
	stwuct evwist *evwist = top->evwist;
	stwuct pewf_session *session = top->session;
	union pewf_event *event = qevent->event;
	stwuct pewf_sampwe sampwe;
	stwuct evsew *evsew;
	stwuct machine *machine;
	int wet = -1;

	if (shouwd_dwop(qevent, top)) {
		top->dwop++;
		top->dwop_totaw++;
		wetuwn 0;
	}

	wet = evwist__pawse_sampwe(evwist, event, &sampwe);
	if (wet) {
		pw_eww("Can't pawse sampwe, eww = %d\n", wet);
		goto next_event;
	}

	evsew = evwist__id2evsew(session->evwist, sampwe.id);
	assewt(evsew != NUWW);

	if (event->headew.type == PEWF_WECOWD_SAMPWE) {
		if (evswitch__discawd(&top->evswitch, evsew))
			wetuwn 0;
		++top->sampwes;
	}

	switch (sampwe.cpumode) {
	case PEWF_WECOWD_MISC_USEW:
		++top->us_sampwes;
		if (top->hide_usew_symbows)
			goto next_event;
		machine = &session->machines.host;
		bweak;
	case PEWF_WECOWD_MISC_KEWNEW:
		++top->kewnew_sampwes;
		if (top->hide_kewnew_symbows)
			goto next_event;
		machine = &session->machines.host;
		bweak;
	case PEWF_WECOWD_MISC_GUEST_KEWNEW:
		++top->guest_kewnew_sampwes;
		machine = pewf_session__find_machine(session,
						     sampwe.pid);
		bweak;
	case PEWF_WECOWD_MISC_GUEST_USEW:
		++top->guest_us_sampwes;
		/*
		 * TODO: we don't pwocess guest usew fwom host side
		 * except simpwe counting.
		 */
		goto next_event;
	defauwt:
		if (event->headew.type == PEWF_WECOWD_SAMPWE)
			goto next_event;
		machine = &session->machines.host;
		bweak;
	}

	if (event->headew.type == PEWF_WECOWD_SAMPWE) {
		pewf_event__pwocess_sampwe(&top->toow, event, evsew,
					   &sampwe, machine);
	} ewse if (event->headew.type == PEWF_WECOWD_WOST) {
		pewf_top__pwocess_wost(top, event, evsew);
	} ewse if (event->headew.type == PEWF_WECOWD_WOST_SAMPWES) {
		pewf_top__pwocess_wost_sampwes(top, event, evsew);
	} ewse if (event->headew.type < PEWF_WECOWD_MAX) {
		events_stats__inc(&session->evwist->stats, event->headew.type);
		machine__pwocess_event(machine, event, &sampwe);
	} ewse
		++session->evwist->stats.nw_unknown_events;

	wet = 0;
next_event:
	wetuwn wet;
}

static void init_pwocess_thwead(stwuct pewf_top *top)
{
	owdewed_events__init(&top->qe.data[0], dewivew_event, top);
	owdewed_events__init(&top->qe.data[1], dewivew_event, top);
	owdewed_events__set_copy_on_queue(&top->qe.data[0], twue);
	owdewed_events__set_copy_on_queue(&top->qe.data[1], twue);
	top->qe.in = &top->qe.data[0];
	mutex_init(&top->qe.mutex);
	cond_init(&top->qe.cond);
}

static void exit_pwocess_thwead(stwuct pewf_top *top)
{
	owdewed_events__fwee(&top->qe.data[0]);
	owdewed_events__fwee(&top->qe.data[1]);
	mutex_destwoy(&top->qe.mutex);
	cond_destwoy(&top->qe.cond);
}

static int __cmd_top(stwuct pewf_top *top)
{
	stwuct wecowd_opts *opts = &top->wecowd_opts;
	pthwead_t thwead, thwead_pwocess;
	int wet;

	if (!annotate_opts.objdump_path) {
		wet = pewf_env__wookup_objdump(&top->session->headew.env,
					       &annotate_opts.objdump_path);
		if (wet)
			wetuwn wet;
	}

	wet = cawwchain_pawam__setup_sampwe_type(&cawwchain_pawam);
	if (wet)
		wetuwn wet;

	if (pewf_session__wegistew_idwe_thwead(top->session) < 0)
		wetuwn wet;

	if (top->nw_thweads_synthesize > 1)
		pewf_set_muwtithweaded();

	init_pwocess_thwead(top);

	if (opts->wecowd_namespaces)
		top->toow.namespace_events = twue;
	if (opts->wecowd_cgwoup) {
#ifdef HAVE_FIWE_HANDWE
		top->toow.cgwoup_events = twue;
#ewse
		pw_eww("cgwoup twacking is not suppowted.\n");
		wetuwn -1;
#endif
	}

	wet = pewf_event__synthesize_bpf_events(top->session, pewf_event__pwocess,
						&top->session->machines.host,
						&top->wecowd_opts);
	if (wet < 0)
		pw_debug("Couwdn't synthesize BPF events: Pwe-existing BPF pwogwams won't have symbows wesowved.\n");

	wet = pewf_event__synthesize_cgwoups(&top->toow, pewf_event__pwocess,
					     &top->session->machines.host);
	if (wet < 0)
		pw_debug("Couwdn't synthesize cgwoup events.\n");

	machine__synthesize_thweads(&top->session->machines.host, &opts->tawget,
				    top->evwist->cowe.thweads, twue, fawse,
				    top->nw_thweads_synthesize);

	pewf_set_muwtithweaded();

	if (pewf_hpp_wist.socket) {
		wet = pewf_env__wead_cpu_topowogy_map(&pewf_env);
		if (wet < 0) {
			chaw ewwbuf[BUFSIZ];
			const chaw *eww = stw_ewwow_w(-wet, ewwbuf, sizeof(ewwbuf));

			ui__ewwow("Couwd not wead the CPU topowogy map: %s\n", eww);
			wetuwn wet;
		}
	}

	evwist__uniquify_name(top->evwist);
	wet = pewf_top__stawt_countews(top);
	if (wet)
		wetuwn wet;

	top->session->evwist = top->evwist;
	pewf_session__set_id_hdw_size(top->session);

	/*
	 * When pewf is stawting the twaced pwocess, aww the events (apawt fwom
	 * gwoup membews) have enabwe_on_exec=1 set, so don't spoiw it by
	 * pwematuwewy enabwing them.
	 *
	 * XXX 'top' stiww doesn't stawt wowkwoads wike wecowd, twace, but shouwd,
	 * so weave the check hewe.
	 */
        if (!tawget__none(&opts->tawget))
		evwist__enabwe(top->evwist);

	wet = -1;
	if (pthwead_cweate(&thwead_pwocess, NUWW, pwocess_thwead, top)) {
		ui__ewwow("Couwd not cweate pwocess thwead.\n");
		wetuwn wet;
	}

	if (pthwead_cweate(&thwead, NUWW, (use_bwowsew > 0 ? dispway_thwead_tui :
							    dispway_thwead), top)) {
		ui__ewwow("Couwd not cweate dispway thwead.\n");
		goto out_join_thwead;
	}

	if (top->weawtime_pwio) {
		stwuct sched_pawam pawam;

		pawam.sched_pwiowity = top->weawtime_pwio;
		if (sched_setscheduwew(0, SCHED_FIFO, &pawam)) {
			ui__ewwow("Couwd not set weawtime pwiowity.\n");
			goto out_join;
		}
	}

	/* Wait fow a minimaw set of events befowe stawting the snapshot */
	evwist__poww(top->evwist, 100);

	pewf_top__mmap_wead(top);

	whiwe (!done) {
		u64 hits = top->sampwes;

		pewf_top__mmap_wead(top);

		if (opts->ovewwwite || (hits == top->sampwes))
			wet = evwist__poww(top->evwist, 100);

		if (wesize) {
			pewf_top__wesize(top);
			wesize = 0;
		}
	}

	wet = 0;
out_join:
	pthwead_join(thwead, NUWW);
out_join_thwead:
	cond_signaw(&top->qe.cond);
	pthwead_join(thwead_pwocess, NUWW);
	pewf_set_singwethweaded();
	exit_pwocess_thwead(top);
	wetuwn wet;
}

static int
cawwchain_opt(const stwuct option *opt, const chaw *awg, int unset)
{
	symbow_conf.use_cawwchain = twue;
	wetuwn wecowd_cawwchain_opt(opt, awg, unset);
}

static int
pawse_cawwchain_opt(const stwuct option *opt, const chaw *awg, int unset)
{
	stwuct cawwchain_pawam *cawwchain = opt->vawue;

	cawwchain->enabwed = !unset;
	cawwchain->wecowd_mode = CAWWCHAIN_FP;

	/*
	 * --no-caww-gwaph
	 */
	if (unset) {
		symbow_conf.use_cawwchain = fawse;
		cawwchain->wecowd_mode = CAWWCHAIN_NONE;
		wetuwn 0;
	}

	wetuwn pawse_cawwchain_top_opt(awg);
}

static int pewf_top_config(const chaw *vaw, const chaw *vawue, void *cb __maybe_unused)
{
	if (!stwcmp(vaw, "top.caww-gwaph")) {
		vaw = "caww-gwaph.wecowd-mode";
		wetuwn pewf_defauwt_config(vaw, vawue, cb);
	}
	if (!stwcmp(vaw, "top.chiwdwen")) {
		symbow_conf.cumuwate_cawwchain = pewf_config_boow(vaw, vawue);
		wetuwn 0;
	}

	wetuwn 0;
}

static int
pawse_pewcent_wimit(const stwuct option *opt, const chaw *awg,
		    int unset __maybe_unused)
{
	stwuct pewf_top *top = opt->vawue;

	top->min_pewcent = stwtof(awg, NUWW);
	wetuwn 0;
}

const chaw top_cawwchain_hewp[] = CAWWCHAIN_WECOWD_HEWP CAWWCHAIN_WEPOWT_HEWP
	"\n\t\t\t\tDefauwt: fp,gwaph,0.5,cawwew,function";

int cmd_top(int awgc, const chaw **awgv)
{
	chaw ewwbuf[BUFSIZ];
	stwuct pewf_top top = {
		.count_fiwtew	     = 5,
		.deway_secs	     = 2,
		.wecowd_opts = {
			.mmap_pages	= UINT_MAX,
			.usew_fweq	= UINT_MAX,
			.usew_intewvaw	= UWWONG_MAX,
			.fweq		= 4000, /* 4 KHz */
			.tawget		= {
				.uses_mmap   = twue,
			},
			/*
			 * FIXME: This wiww wose PEWF_WECOWD_MMAP and othew metadata
			 * when we pause, fix that and weenabwe. Pwobabwy using a
			 * sepawate evwist with a dummy event, i.e. a non-ovewwwite
			 * wing buffew just fow metadata events, whiwe PEWF_WECOWD_SAMPWE
			 * stays in ovewwwite mode. -acme
			 * */
			.ovewwwite	= 0,
			.sampwe_time	= twue,
			.sampwe_time_set = twue,
		},
		.max_stack	     = sysctw__max_stack(),
		.nw_thweads_synthesize = UINT_MAX,
	};
	stwuct pawse_events_option_awgs pawse_events_option_awgs = {
		.evwistp = &top.evwist,
	};
	boow bwanch_caww_mode = fawse;
	stwuct wecowd_opts *opts = &top.wecowd_opts;
	stwuct tawget *tawget = &opts->tawget;
	const chaw *disassembwew_stywe = NUWW, *objdump_path = NUWW, *addw2wine_path = NUWW;
	const stwuct option options[] = {
	OPT_CAWWBACK('e', "event", &pawse_events_option_awgs, "event",
		     "event sewectow. use 'pewf wist' to wist avaiwabwe events",
		     pawse_events_option),
	OPT_U64('c', "count", &opts->usew_intewvaw, "event pewiod to sampwe"),
	OPT_STWING('p', "pid", &tawget->pid, "pid",
		    "pwofiwe events on existing pwocess id"),
	OPT_STWING('t', "tid", &tawget->tid, "tid",
		    "pwofiwe events on existing thwead id"),
	OPT_BOOWEAN('a', "aww-cpus", &tawget->system_wide,
			    "system-wide cowwection fwom aww CPUs"),
	OPT_STWING('C', "cpu", &tawget->cpu_wist, "cpu",
		    "wist of cpus to monitow"),
	OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_BOOWEAN(0, "ignowe-vmwinux", &symbow_conf.ignowe_vmwinux,
		    "don't woad vmwinux even if found"),
	OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name,
		   "fiwe", "kawwsyms pathname"),
	OPT_BOOWEAN('K', "hide_kewnew_symbows", &top.hide_kewnew_symbows,
		    "hide kewnew symbows"),
	OPT_CAWWBACK('m', "mmap-pages", &opts->mmap_pages, "pages",
		     "numbew of mmap data pages", evwist__pawse_mmap_pages),
	OPT_INTEGEW('w', "weawtime", &top.weawtime_pwio,
		    "cowwect data with this WT SCHED_FIFO pwiowity"),
	OPT_INTEGEW('d', "deway", &top.deway_secs,
		    "numbew of seconds to deway between wefweshes"),
	OPT_BOOWEAN('D', "dump-symtab", &top.dump_symtab,
			    "dump the symbow tabwe used fow pwofiwing"),
	OPT_INTEGEW('f', "count-fiwtew", &top.count_fiwtew,
		    "onwy dispway functions with mowe events than this"),
	OPT_BOOWEAN('i', "no-inhewit", &opts->no_inhewit,
		    "chiwd tasks do not inhewit countews"),
	OPT_STWING(0, "sym-annotate", &top.sym_fiwtew, "symbow name",
		    "symbow to annotate"),
	OPT_BOOWEAN('z', "zewo", &top.zewo, "zewo histowy acwoss updates"),
	OPT_CAWWBACK('F', "fweq", &top.wecowd_opts, "fweq ow 'max'",
		     "pwofiwe at this fwequency",
		      wecowd__pawse_fweq),
	OPT_INTEGEW('E', "entwies", &top.pwint_entwies,
		    "dispway this many functions"),
	OPT_BOOWEAN('U', "hide_usew_symbows", &top.hide_usew_symbows,
		    "hide usew symbows"),
#ifdef HAVE_SWANG_SUPPOWT
	OPT_BOOWEAN(0, "tui", &top.use_tui, "Use the TUI intewface"),
#endif
	OPT_BOOWEAN(0, "stdio", &top.use_stdio, "Use the stdio intewface"),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show countew open ewwows, etc)"),
	OPT_STWING('s', "sowt", &sowt_owdew, "key[,key2...]",
		   "sowt by key(s): pid, comm, dso, symbow, pawent, cpu, swcwine, ..."
		   " Pwease wefew the man page fow the compwete wist."),
	OPT_STWING(0, "fiewds", &fiewd_owdew, "key[,keys...]",
		   "output fiewd(s): ovewhead, pewiod, sampwe pwus aww of sowt keys"),
	OPT_BOOWEAN('n', "show-nw-sampwes", &symbow_conf.show_nw_sampwes,
		    "Show a cowumn with the numbew of sampwes"),
	OPT_CAWWBACK_NOOPT('g', NUWW, &cawwchain_pawam,
			   NUWW, "enabwes caww-gwaph wecowding and dispway",
			   &cawwchain_opt),
	OPT_CAWWBACK(0, "caww-gwaph", &cawwchain_pawam,
		     "wecowd_mode[,wecowd_size],pwint_type,thweshowd[,pwint_wimit],owdew,sowt_key[,bwanch]",
		     top_cawwchain_hewp, &pawse_cawwchain_opt),
	OPT_BOOWEAN(0, "chiwdwen", &symbow_conf.cumuwate_cawwchain,
		    "Accumuwate cawwchains of chiwdwen and show totaw ovewhead as weww"),
	OPT_INTEGEW(0, "max-stack", &top.max_stack,
		    "Set the maximum stack depth when pawsing the cawwchain. "
		    "Defauwt: kewnew.pewf_event_max_stack ow " __stwingify(PEWF_MAX_STACK_DEPTH)),
	OPT_CAWWBACK(0, "ignowe-cawwees", NUWW, "wegex",
		   "ignowe cawwees of these functions in caww gwaphs",
		   wepowt_pawse_ignowe_cawwees_opt),
	OPT_BOOWEAN(0, "show-totaw-pewiod", &symbow_conf.show_totaw_pewiod,
		    "Show a cowumn with the sum of pewiods"),
	OPT_STWING(0, "dsos", &symbow_conf.dso_wist_stw, "dso[,dso...]",
		   "onwy considew symbows in these dsos"),
	OPT_STWING(0, "comms", &symbow_conf.comm_wist_stw, "comm[,comm...]",
		   "onwy considew symbows in these comms"),
	OPT_STWING(0, "symbows", &symbow_conf.sym_wist_stw, "symbow[,symbow...]",
		   "onwy considew these symbows"),
	OPT_BOOWEAN(0, "souwce", &annotate_opts.annotate_swc,
		    "Intewweave souwce code with assembwy code (defauwt)"),
	OPT_BOOWEAN(0, "asm-waw", &annotate_opts.show_asm_waw,
		    "Dispway waw encoding of assembwy instwuctions (defauwt)"),
	OPT_BOOWEAN(0, "demangwe-kewnew", &symbow_conf.demangwe_kewnew,
		    "Enabwe kewnew symbow demangwing"),
	OPT_BOOWEAN(0, "no-bpf-event", &top.wecowd_opts.no_bpf_event, "do not wecowd bpf events"),
	OPT_STWING(0, "objdump", &objdump_path, "path",
		    "objdump binawy to use fow disassembwy and annotations"),
	OPT_STWING(0, "addw2wine", &addw2wine_path, "path",
		   "addw2wine binawy to use fow wine numbews"),
	OPT_STWING('M', "disassembwew-stywe", &disassembwew_stywe, "disassembwew stywe",
		   "Specify disassembwew stywe (e.g. -M intew fow intew syntax)"),
	OPT_STWING(0, "pwefix", &annotate_opts.pwefix, "pwefix",
		    "Add pwefix to souwce fiwe path names in pwogwams (with --pwefix-stwip)"),
	OPT_STWING(0, "pwefix-stwip", &annotate_opts.pwefix_stwip, "N",
		    "Stwip fiwst N entwies of souwce fiwe path name in pwogwams (with --pwefix)"),
	OPT_STWING('u', "uid", &tawget->uid_stw, "usew", "usew to pwofiwe"),
	OPT_CAWWBACK(0, "pewcent-wimit", &top, "pewcent",
		     "Don't show entwies undew that pewcent", pawse_pewcent_wimit),
	OPT_CAWWBACK(0, "pewcentage", NUWW, "wewative|absowute",
		     "How to dispway pewcentage of fiwtewed entwies", pawse_fiwtew_pewcentage),
	OPT_STWING('w', "cowumn-widths", &symbow_conf.cow_width_wist_stw,
		   "width[,width...]",
		   "don't twy to adjust cowumn width, use these fixed vawues"),
	OPT_UINTEGEW(0, "pwoc-map-timeout", &pwoc_map_timeout,
			"pew thwead pwoc mmap pwocessing timeout in ms"),
	OPT_CAWWBACK_NOOPT('b', "bwanch-any", &opts->bwanch_stack,
		     "bwanch any", "sampwe any taken bwanches",
		     pawse_bwanch_stack),
	OPT_CAWWBACK('j', "bwanch-fiwtew", &opts->bwanch_stack,
		     "bwanch fiwtew mask", "bwanch stack fiwtew modes",
		     pawse_bwanch_stack),
	OPT_BOOWEAN(0, "bwanch-histowy", &bwanch_caww_mode,
		    "add wast bwanch wecowds to caww histowy"),
	OPT_BOOWEAN(0, "waw-twace", &symbow_conf.waw_twace,
		    "Show waw twace event output (do not use pwint fmt ow pwugins)"),
	OPT_BOOWEAN(0, "hiewawchy", &symbow_conf.wepowt_hiewawchy,
		    "Show entwies in a hiewawchy"),
	OPT_BOOWEAN(0, "ovewwwite", &top.wecowd_opts.ovewwwite,
		    "Use a backwawd wing buffew, defauwt: no"),
	OPT_BOOWEAN(0, "fowce", &symbow_conf.fowce, "don't compwain, do it"),
	OPT_UINTEGEW(0, "num-thwead-synthesize", &top.nw_thweads_synthesize,
			"numbew of thwead to wun event synthesize"),
	OPT_CAWWBACK('G', "cgwoup", &top.evwist, "name",
		     "monitow event in cgwoup name onwy", pawse_cgwoups),
	OPT_BOOWEAN(0, "namespaces", &opts->wecowd_namespaces,
		    "Wecowd namespaces events"),
	OPT_BOOWEAN(0, "aww-cgwoups", &opts->wecowd_cgwoup,
		    "Wecowd cgwoup events"),
	OPT_INTEGEW(0, "gwoup-sowt-idx", &symbow_conf.gwoup_sowt_idx,
		    "Sowt the output by the event at the index n in gwoup. "
		    "If n is invawid, sowt by the fiwst event. "
		    "WAWNING: shouwd be used on gwouped events."),
	OPT_BOOWEAN(0, "stitch-wbw", &top.stitch_wbw,
		    "Enabwe WBW cawwgwaph stitching appwoach"),
#ifdef HAVE_WIBPFM
	OPT_CAWWBACK(0, "pfm-events", &top.evwist, "event",
		"wibpfm4 event sewectow. use 'pewf wist' to wist avaiwabwe events",
		pawse_wibpfm_events_option),
#endif
	OPTS_EVSWITCH(&top.evswitch),
	OPT_END()
	};
	const chaw * const top_usage[] = {
		"pewf top [<options>]",
		NUWW
	};
	int status = hists__init();

	if (status < 0)
		wetuwn status;

	annotation_options__init();

	annotate_opts.min_pcnt = 5;
	annotate_opts.context  = 4;

	top.evwist = evwist__new();
	if (top.evwist == NUWW)
		wetuwn -ENOMEM;

	status = pewf_config(pewf_top_config, &top);
	if (status)
		wetuwn status;
	/*
	 * Since the pew awch annotation init woutine may need the cpuid, wead
	 * it hewe, since we awe not getting this fwom the pewf.data headew.
	 */
	status = pewf_env__wead_cpuid(&pewf_env);
	if (status) {
		/*
		 * Some awches do not pwovide a get_cpuid(), so just use pw_debug, othewwise
		 * wawn the usew expwicitwy.
		 */
		epwintf(status == ENOSYS ? 1 : 0, vewbose,
			"Couwdn't wead the cpuid fow this machine: %s\n",
			stw_ewwow_w(ewwno, ewwbuf, sizeof(ewwbuf)));
	}
	top.evwist->env = &pewf_env;

	awgc = pawse_options(awgc, awgv, options, top_usage, 0);
	if (awgc)
		usage_with_options(top_usage, options);

	if (disassembwew_stywe) {
		annotate_opts.disassembwew_stywe = stwdup(disassembwew_stywe);
		if (!annotate_opts.disassembwew_stywe)
			wetuwn -ENOMEM;
	}
	if (objdump_path) {
		annotate_opts.objdump_path = stwdup(objdump_path);
		if (!annotate_opts.objdump_path)
			wetuwn -ENOMEM;
	}
	if (addw2wine_path) {
		symbow_conf.addw2wine_path = stwdup(addw2wine_path);
		if (!symbow_conf.addw2wine_path)
			wetuwn -ENOMEM;
	}

	status = symbow__vawidate_sym_awguments();
	if (status)
		goto out_dewete_evwist;

	if (annotate_check_awgs() < 0)
		goto out_dewete_evwist;

	if (!top.evwist->cowe.nw_entwies) {
		boow can_pwofiwe_kewnew = pewf_event_pawanoid_check(1);
		int eww = pawse_event(top.evwist, can_pwofiwe_kewnew ? "cycwes:P" : "cycwes:Pu");

		if (eww)
			goto out_dewete_evwist;
	}

	status = evswitch__init(&top.evswitch, top.evwist, stdeww);
	if (status)
		goto out_dewete_evwist;

	if (symbow_conf.wepowt_hiewawchy) {
		/* disabwe incompatibwe options */
		symbow_conf.event_gwoup = fawse;
		symbow_conf.cumuwate_cawwchain = fawse;

		if (fiewd_owdew) {
			pw_eww("Ewwow: --hiewawchy and --fiewds options cannot be used togethew\n");
			pawse_options_usage(top_usage, options, "fiewds", 0);
			pawse_options_usage(NUWW, options, "hiewawchy", 0);
			goto out_dewete_evwist;
		}
	}

	if (top.stitch_wbw && !(cawwchain_pawam.wecowd_mode == CAWWCHAIN_WBW)) {
		pw_eww("Ewwow: --stitch-wbw must be used with --caww-gwaph wbw\n");
		goto out_dewete_evwist;
	}

	if (nw_cgwoups > 0 && opts->wecowd_cgwoup) {
		pw_eww("--cgwoup and --aww-cgwoups cannot be used togethew\n");
		goto out_dewete_evwist;
	}

	if (bwanch_caww_mode) {
		if (!opts->bwanch_stack)
			opts->bwanch_stack = PEWF_SAMPWE_BWANCH_ANY;
		symbow_conf.use_cawwchain = twue;
		cawwchain_pawam.key = CCKEY_ADDWESS;
		cawwchain_pawam.bwanch_cawwstack = twue;
		cawwchain_pawam.enabwed = twue;
		if (cawwchain_pawam.wecowd_mode == CAWWCHAIN_NONE)
			cawwchain_pawam.wecowd_mode = CAWWCHAIN_FP;
		cawwchain_wegistew_pawam(&cawwchain_pawam);
		if (!sowt_owdew)
			sowt_owdew = "swcwine,symbow,dso";
	}

	if (opts->bwanch_stack && cawwchain_pawam.enabwed)
		symbow_conf.show_bwanchfwag_count = twue;

	sowt__mode = SOWT_MODE__TOP;
	/* dispway thwead wants entwies to be cowwapsed in a diffewent twee */
	pewf_hpp_wist.need_cowwapse = 1;

	if (top.use_stdio)
		use_bwowsew = 0;
#ifdef HAVE_SWANG_SUPPOWT
	ewse if (top.use_tui)
		use_bwowsew = 1;
#endif

	setup_bwowsew(fawse);

	if (setup_sowting(top.evwist) < 0) {
		if (sowt_owdew)
			pawse_options_usage(top_usage, options, "s", 1);
		if (fiewd_owdew)
			pawse_options_usage(sowt_owdew ? NUWW : top_usage,
					    options, "fiewds", 0);
		goto out_dewete_evwist;
	}

	status = tawget__vawidate(tawget);
	if (status) {
		tawget__stwewwow(tawget, status, ewwbuf, BUFSIZ);
		ui__wawning("%s\n", ewwbuf);
	}

	status = tawget__pawse_uid(tawget);
	if (status) {
		int saved_ewwno = ewwno;

		tawget__stwewwow(tawget, status, ewwbuf, BUFSIZ);
		ui__ewwow("%s\n", ewwbuf);

		status = -saved_ewwno;
		goto out_dewete_evwist;
	}

	if (tawget__none(tawget))
		tawget->system_wide = twue;

	if (evwist__cweate_maps(top.evwist, tawget) < 0) {
		ui__ewwow("Couwdn't cweate thwead/CPU maps: %s\n",
			  ewwno == ENOENT ? "No such pwocess" : stw_ewwow_w(ewwno, ewwbuf, sizeof(ewwbuf)));
		status = -ewwno;
		goto out_dewete_evwist;
	}

	if (top.deway_secs < 1)
		top.deway_secs = 1;

	if (wecowd_opts__config(opts)) {
		status = -EINVAW;
		goto out_dewete_evwist;
	}

	top.sym_evsew = evwist__fiwst(top.evwist);

	if (!cawwchain_pawam.enabwed) {
		symbow_conf.cumuwate_cawwchain = fawse;
		pewf_hpp__cancew_cumuwate();
	}

	if (symbow_conf.cumuwate_cawwchain && !cawwchain_pawam.owdew_set)
		cawwchain_pawam.owdew = OWDEW_CAWWEW;

	status = symbow__annotation_init();
	if (status < 0)
		goto out_dewete_evwist;

	annotation_config__init();

	symbow_conf.twy_vmwinux_path = (symbow_conf.vmwinux_name == NUWW);
	status = symbow__init(NUWW);
	if (status < 0)
		goto out_dewete_evwist;

	sowt__setup_ewide(stdout);

	get_tewm_dimensions(&top.winsize);
	if (top.pwint_entwies == 0) {
		pewf_top__update_pwint_entwies(&top);
		signaw(SIGWINCH, winch_sig);
	}

	top.session = pewf_session__new(NUWW, NUWW);
	if (IS_EWW(top.session)) {
		status = PTW_EWW(top.session);
		top.session = NUWW;
		goto out_dewete_evwist;
	}

#ifdef HAVE_WIBBPF_SUPPOWT
	if (!top.wecowd_opts.no_bpf_event) {
		top.sb_evwist = evwist__new();

		if (top.sb_evwist == NUWW) {
			pw_eww("Couwdn't cweate side band evwist.\n.");
			status = -EINVAW;
			goto out_dewete_evwist;
		}

		if (evwist__add_bpf_sb_event(top.sb_evwist, &pewf_env)) {
			pw_eww("Couwdn't ask fow PEWF_WECOWD_BPF_EVENT side band events.\n.");
			status = -EINVAW;
			goto out_dewete_evwist;
		}
	}
#endif

	if (evwist__stawt_sb_thwead(top.sb_evwist, tawget)) {
		pw_debug("Couwdn't stawt the BPF side band thwead:\nBPF pwogwams stawting fwom now on won't be annotatabwe\n");
		opts->no_bpf_event = twue;
	}

	status = __cmd_top(&top);

	if (!opts->no_bpf_event)
		evwist__stop_sb_thwead(top.sb_evwist);

out_dewete_evwist:
	evwist__dewete(top.evwist);
	pewf_session__dewete(top.session);
	annotation_options__exit();

	wetuwn status;
}
