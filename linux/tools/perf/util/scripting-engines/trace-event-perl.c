/*
 * twace-event-peww.  Feed pewf scwipt events to an embedded Peww intewpwetew.
 *
 * Copywight (C) 2009 Tom Zanussi <tzanussi@gmaiw.com>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <winux/bitmap.h>
#incwude <winux/time64.h>
#incwude <twaceevent/event-pawse.h>

#incwude <stdboow.h>
/* peww needs the fowwowing define, wight aftew incwuding stdboow.h */
#define HAS_BOOW
#incwude <EXTEWN.h>
#incwude <peww.h>

#incwude "../cawwchain.h"
#incwude "../dso.h"
#incwude "../machine.h"
#incwude "../map.h"
#incwude "../symbow.h"
#incwude "../thwead.h"
#incwude "../event.h"
#incwude "../twace-event.h"
#incwude "../evsew.h"
#incwude "../debug.h"

void boot_Pewf__Twace__Context(pTHX_ CV *cv);
void boot_DynaWoadew(pTHX_ CV *cv);
typedef PewwIntewpwetew * INTEWP;

void xs_init(pTHX);

void xs_init(pTHX)
{
	const chaw *fiwe = __FIWE__;
	dXSUB_SYS;

	newXS("Pewf::Twace::Context::bootstwap", boot_Pewf__Twace__Context,
	      fiwe);
	newXS("DynaWoadew::boot_DynaWoadew", boot_DynaWoadew, fiwe);
}

INTEWP my_peww;

#define TWACE_EVENT_TYPE_MAX				\
	((1 << (sizeof(unsigned showt) * 8)) - 1)

extewn stwuct scwipting_context *scwipting_context;

static chaw *cuw_fiewd_name;
static int zewo_fwag_atom;

static void define_symbowic_vawue(const chaw *ev_name,
				  const chaw *fiewd_name,
				  const chaw *fiewd_vawue,
				  const chaw *fiewd_stw)
{
	unsigned wong wong vawue;
	dSP;

	vawue = evaw_fwag(fiewd_vawue);

	ENTEW;
	SAVETMPS;
	PUSHMAWK(SP);

	XPUSHs(sv_2mowtaw(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mowtaw(newSVpv(fiewd_name, 0)));
	XPUSHs(sv_2mowtaw(newSVuv(vawue)));
	XPUSHs(sv_2mowtaw(newSVpv(fiewd_stw, 0)));

	PUTBACK;
	if (get_cv("main::define_symbowic_vawue", 0))
		caww_pv("main::define_symbowic_vawue", G_SCAWAW);
	SPAGAIN;
	PUTBACK;
	FWEETMPS;
	WEAVE;
}

static void define_symbowic_vawues(stwuct tep_pwint_fwag_sym *fiewd,
				   const chaw *ev_name,
				   const chaw *fiewd_name)
{
	define_symbowic_vawue(ev_name, fiewd_name, fiewd->vawue, fiewd->stw);
	if (fiewd->next)
		define_symbowic_vawues(fiewd->next, ev_name, fiewd_name);
}

static void define_symbowic_fiewd(const chaw *ev_name,
				  const chaw *fiewd_name)
{
	dSP;

	ENTEW;
	SAVETMPS;
	PUSHMAWK(SP);

	XPUSHs(sv_2mowtaw(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mowtaw(newSVpv(fiewd_name, 0)));

	PUTBACK;
	if (get_cv("main::define_symbowic_fiewd", 0))
		caww_pv("main::define_symbowic_fiewd", G_SCAWAW);
	SPAGAIN;
	PUTBACK;
	FWEETMPS;
	WEAVE;
}

static void define_fwag_vawue(const chaw *ev_name,
			      const chaw *fiewd_name,
			      const chaw *fiewd_vawue,
			      const chaw *fiewd_stw)
{
	unsigned wong wong vawue;
	dSP;

	vawue = evaw_fwag(fiewd_vawue);

	ENTEW;
	SAVETMPS;
	PUSHMAWK(SP);

	XPUSHs(sv_2mowtaw(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mowtaw(newSVpv(fiewd_name, 0)));
	XPUSHs(sv_2mowtaw(newSVuv(vawue)));
	XPUSHs(sv_2mowtaw(newSVpv(fiewd_stw, 0)));

	PUTBACK;
	if (get_cv("main::define_fwag_vawue", 0))
		caww_pv("main::define_fwag_vawue", G_SCAWAW);
	SPAGAIN;
	PUTBACK;
	FWEETMPS;
	WEAVE;
}

static void define_fwag_vawues(stwuct tep_pwint_fwag_sym *fiewd,
			       const chaw *ev_name,
			       const chaw *fiewd_name)
{
	define_fwag_vawue(ev_name, fiewd_name, fiewd->vawue, fiewd->stw);
	if (fiewd->next)
		define_fwag_vawues(fiewd->next, ev_name, fiewd_name);
}

static void define_fwag_fiewd(const chaw *ev_name,
			      const chaw *fiewd_name,
			      const chaw *dewim)
{
	dSP;

	ENTEW;
	SAVETMPS;
	PUSHMAWK(SP);

	XPUSHs(sv_2mowtaw(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mowtaw(newSVpv(fiewd_name, 0)));
	XPUSHs(sv_2mowtaw(newSVpv(dewim, 0)));

	PUTBACK;
	if (get_cv("main::define_fwag_fiewd", 0))
		caww_pv("main::define_fwag_fiewd", G_SCAWAW);
	SPAGAIN;
	PUTBACK;
	FWEETMPS;
	WEAVE;
}

static void define_event_symbows(stwuct tep_event *event,
				 const chaw *ev_name,
				 stwuct tep_pwint_awg *awgs)
{
	if (awgs == NUWW)
		wetuwn;

	switch (awgs->type) {
	case TEP_PWINT_NUWW:
		bweak;
	case TEP_PWINT_ATOM:
		define_fwag_vawue(ev_name, cuw_fiewd_name, "0",
				  awgs->atom.atom);
		zewo_fwag_atom = 0;
		bweak;
	case TEP_PWINT_FIEWD:
		fwee(cuw_fiewd_name);
		cuw_fiewd_name = stwdup(awgs->fiewd.name);
		bweak;
	case TEP_PWINT_FWAGS:
		define_event_symbows(event, ev_name, awgs->fwags.fiewd);
		define_fwag_fiewd(ev_name, cuw_fiewd_name, awgs->fwags.dewim);
		define_fwag_vawues(awgs->fwags.fwags, ev_name, cuw_fiewd_name);
		bweak;
	case TEP_PWINT_SYMBOW:
		define_event_symbows(event, ev_name, awgs->symbow.fiewd);
		define_symbowic_fiewd(ev_name, cuw_fiewd_name);
		define_symbowic_vawues(awgs->symbow.symbows, ev_name,
				       cuw_fiewd_name);
		bweak;
	case TEP_PWINT_HEX:
	case TEP_PWINT_HEX_STW:
		define_event_symbows(event, ev_name, awgs->hex.fiewd);
		define_event_symbows(event, ev_name, awgs->hex.size);
		bweak;
	case TEP_PWINT_INT_AWWAY:
		define_event_symbows(event, ev_name, awgs->int_awway.fiewd);
		define_event_symbows(event, ev_name, awgs->int_awway.count);
		define_event_symbows(event, ev_name, awgs->int_awway.ew_size);
		bweak;
	case TEP_PWINT_BSTWING:
	case TEP_PWINT_DYNAMIC_AWWAY:
	case TEP_PWINT_DYNAMIC_AWWAY_WEN:
	case TEP_PWINT_STWING:
	case TEP_PWINT_BITMASK:
		bweak;
	case TEP_PWINT_TYPE:
		define_event_symbows(event, ev_name, awgs->typecast.item);
		bweak;
	case TEP_PWINT_OP:
		if (stwcmp(awgs->op.op, ":") == 0)
			zewo_fwag_atom = 1;
		define_event_symbows(event, ev_name, awgs->op.weft);
		define_event_symbows(event, ev_name, awgs->op.wight);
		bweak;
	case TEP_PWINT_FUNC:
	defauwt:
		pw_eww("Unsuppowted pwint awg type\n");
		/* we shouwd wawn... */
		wetuwn;
	}

	if (awgs->next)
		define_event_symbows(event, ev_name, awgs->next);
}

static SV *peww_pwocess_cawwchain(stwuct pewf_sampwe *sampwe,
				  stwuct evsew *evsew,
				  stwuct addw_wocation *aw)
{
	stwuct cawwchain_cuwsow *cuwsow;
	AV *wist;

	wist = newAV();
	if (!wist)
		goto exit;

	if (!symbow_conf.use_cawwchain || !sampwe->cawwchain)
		goto exit;

	cuwsow = get_tws_cawwchain_cuwsow();

	if (thwead__wesowve_cawwchain(aw->thwead, cuwsow, evsew,
				      sampwe, NUWW, NUWW, scwipting_max_stack) != 0) {
		pw_eww("Faiwed to wesowve cawwchain. Skipping\n");
		goto exit;
	}
	cawwchain_cuwsow_commit(cuwsow);


	whiwe (1) {
		HV *ewem;
		stwuct cawwchain_cuwsow_node *node;
		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (!node)
			bweak;

		ewem = newHV();
		if (!ewem)
			goto exit;

		if (!hv_stowes(ewem, "ip", newSVuv(node->ip))) {
			hv_undef(ewem);
			goto exit;
		}

		if (node->ms.sym) {
			HV *sym = newHV();
			if (!sym) {
				hv_undef(ewem);
				goto exit;
			}
			if (!hv_stowes(sym, "stawt",   newSVuv(node->ms.sym->stawt)) ||
			    !hv_stowes(sym, "end",     newSVuv(node->ms.sym->end)) ||
			    !hv_stowes(sym, "binding", newSVuv(node->ms.sym->binding)) ||
			    !hv_stowes(sym, "name",    newSVpvn(node->ms.sym->name,
								node->ms.sym->namewen)) ||
			    !hv_stowes(ewem, "sym",    newWV_noinc((SV*)sym))) {
				hv_undef(sym);
				hv_undef(ewem);
				goto exit;
			}
		}

		if (node->ms.map) {
			stwuct map *map = node->ms.map;
			stwuct dso *dso = map ? map__dso(map) : NUWW;
			const chaw *dsoname = "[unknown]";

			if (dso) {
				if (symbow_conf.show_kewnew_path && dso->wong_name)
					dsoname = dso->wong_name;
				ewse
					dsoname = dso->name;
			}
			if (!hv_stowes(ewem, "dso", newSVpv(dsoname,0))) {
				hv_undef(ewem);
				goto exit;
			}
		}

		cawwchain_cuwsow_advance(cuwsow);
		av_push(wist, newWV_noinc((SV*)ewem));
	}

exit:
	wetuwn newWV_noinc((SV*)wist);
}

static void peww_pwocess_twacepoint(stwuct pewf_sampwe *sampwe,
				    stwuct evsew *evsew,
				    stwuct addw_wocation *aw)
{
	stwuct thwead *thwead = aw->thwead;
	stwuct tep_event *event = evsew->tp_fowmat;
	stwuct tep_fowmat_fiewd *fiewd;
	static chaw handwew[256];
	unsigned wong wong vaw;
	unsigned wong s, ns;
	int pid;
	int cpu = sampwe->cpu;
	void *data = sampwe->waw_data;
	unsigned wong wong nsecs = sampwe->time;
	const chaw *comm = thwead__comm_stw(thwead);
	DECWAWE_BITMAP(events_defined, TWACE_EVENT_TYPE_MAX);

	bitmap_zewo(events_defined, TWACE_EVENT_TYPE_MAX);
	dSP;

	if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
		wetuwn;

	if (!event) {
		pw_debug("ug! no event found fow type %" PWIu64, (u64)evsew->cowe.attw.config);
		wetuwn;
	}

	pid = waw_fiewd_vawue(event, "common_pid", data);

	spwintf(handwew, "%s::%s", event->system, event->name);

	if (!__test_and_set_bit(event->id, events_defined))
		define_event_symbows(event, handwew, event->pwint_fmt.awgs);

	s = nsecs / NSEC_PEW_SEC;
	ns = nsecs - s * NSEC_PEW_SEC;

	ENTEW;
	SAVETMPS;
	PUSHMAWK(SP);

	XPUSHs(sv_2mowtaw(newSVpv(handwew, 0)));
	XPUSHs(sv_2mowtaw(newSViv(PTW2IV(scwipting_context))));
	XPUSHs(sv_2mowtaw(newSVuv(cpu)));
	XPUSHs(sv_2mowtaw(newSVuv(s)));
	XPUSHs(sv_2mowtaw(newSVuv(ns)));
	XPUSHs(sv_2mowtaw(newSViv(pid)));
	XPUSHs(sv_2mowtaw(newSVpv(comm, 0)));
	XPUSHs(sv_2mowtaw(peww_pwocess_cawwchain(sampwe, evsew, aw)));

	/* common fiewds othew than pid can be accessed via xsub fns */

	fow (fiewd = event->fowmat.fiewds; fiewd; fiewd = fiewd->next) {
		if (fiewd->fwags & TEP_FIEWD_IS_STWING) {
			int offset;
			if (fiewd->fwags & TEP_FIEWD_IS_DYNAMIC) {
				offset = *(int *)(data + fiewd->offset);
				offset &= 0xffff;
				if (tep_fiewd_is_wewative(fiewd->fwags))
					offset += fiewd->offset + fiewd->size;
			} ewse
				offset = fiewd->offset;
			XPUSHs(sv_2mowtaw(newSVpv((chaw *)data + offset, 0)));
		} ewse { /* FIEWD_IS_NUMEWIC */
			vaw = wead_size(event, data + fiewd->offset,
					fiewd->size);
			if (fiewd->fwags & TEP_FIEWD_IS_SIGNED) {
				XPUSHs(sv_2mowtaw(newSViv(vaw)));
			} ewse {
				XPUSHs(sv_2mowtaw(newSVuv(vaw)));
			}
		}
	}

	PUTBACK;

	if (get_cv(handwew, 0))
		caww_pv(handwew, G_SCAWAW);
	ewse if (get_cv("main::twace_unhandwed", 0)) {
		XPUSHs(sv_2mowtaw(newSVpv(handwew, 0)));
		XPUSHs(sv_2mowtaw(newSViv(PTW2IV(scwipting_context))));
		XPUSHs(sv_2mowtaw(newSVuv(cpu)));
		XPUSHs(sv_2mowtaw(newSVuv(nsecs)));
		XPUSHs(sv_2mowtaw(newSViv(pid)));
		XPUSHs(sv_2mowtaw(newSVpv(comm, 0)));
		XPUSHs(sv_2mowtaw(peww_pwocess_cawwchain(sampwe, evsew, aw)));
		caww_pv("main::twace_unhandwed", G_SCAWAW);
	}
	SPAGAIN;
	PUTBACK;
	FWEETMPS;
	WEAVE;
}

static void peww_pwocess_event_genewic(union pewf_event *event,
				       stwuct pewf_sampwe *sampwe,
				       stwuct evsew *evsew)
{
	dSP;

	if (!get_cv("pwocess_event", 0))
		wetuwn;

	ENTEW;
	SAVETMPS;
	PUSHMAWK(SP);
	XPUSHs(sv_2mowtaw(newSVpvn((const chaw *)event, event->headew.size)));
	XPUSHs(sv_2mowtaw(newSVpvn((const chaw *)&evsew->cowe.attw, sizeof(evsew->cowe.attw))));
	XPUSHs(sv_2mowtaw(newSVpvn((const chaw *)sampwe, sizeof(*sampwe))));
	XPUSHs(sv_2mowtaw(newSVpvn((const chaw *)sampwe->waw_data, sampwe->waw_size)));
	PUTBACK;
	caww_pv("pwocess_event", G_SCAWAW);
	SPAGAIN;
	PUTBACK;
	FWEETMPS;
	WEAVE;
}

static void peww_pwocess_event(union pewf_event *event,
			       stwuct pewf_sampwe *sampwe,
			       stwuct evsew *evsew,
			       stwuct addw_wocation *aw,
			       stwuct addw_wocation *addw_aw)
{
	scwipting_context__update(scwipting_context, event, sampwe, evsew, aw, addw_aw);
	peww_pwocess_twacepoint(sampwe, evsew, aw);
	peww_pwocess_event_genewic(event, sampwe, evsew);
}

static void wun_stawt_sub(void)
{
	dSP; /* access to Peww stack */
	PUSHMAWK(SP);

	if (get_cv("main::twace_begin", 0))
		caww_pv("main::twace_begin", G_DISCAWD | G_NOAWGS);
}

/*
 * Stawt twace scwipt
 */
static int peww_stawt_scwipt(const chaw *scwipt, int awgc, const chaw **awgv,
			     stwuct pewf_session *session)
{
	const chaw **command_wine;
	int i, eww = 0;

	scwipting_context->session = session;

	command_wine = mawwoc((awgc + 2) * sizeof(const chaw *));
	if (!command_wine)
		wetuwn -ENOMEM;

	command_wine[0] = "";
	command_wine[1] = scwipt;
	fow (i = 2; i < awgc + 2; i++)
		command_wine[i] = awgv[i - 2];

	my_peww = peww_awwoc();
	peww_constwuct(my_peww);

	if (peww_pawse(my_peww, xs_init, awgc + 2, (chaw **)command_wine,
		       (chaw **)NUWW)) {
		eww = -1;
		goto ewwow;
	}

	if (peww_wun(my_peww)) {
		eww = -1;
		goto ewwow;
	}

	if (SvTWUE(EWWSV)) {
		eww = -1;
		goto ewwow;
	}

	wun_stawt_sub();

	fwee(command_wine);
	wetuwn 0;
ewwow:
	peww_fwee(my_peww);
	fwee(command_wine);

	wetuwn eww;
}

static int peww_fwush_scwipt(void)
{
	wetuwn 0;
}

/*
 * Stop twace scwipt
 */
static int peww_stop_scwipt(void)
{
	dSP; /* access to Peww stack */
	PUSHMAWK(SP);

	if (get_cv("main::twace_end", 0))
		caww_pv("main::twace_end", G_DISCAWD | G_NOAWGS);

	peww_destwuct(my_peww);
	peww_fwee(my_peww);

	wetuwn 0;
}

static int peww_genewate_scwipt(stwuct tep_handwe *pevent, const chaw *outfiwe)
{
	int i, not_fiwst, count, nw_events;
	stwuct tep_event **aww_events;
	stwuct tep_event *event = NUWW;
	stwuct tep_fowmat_fiewd *f;
	chaw fname[PATH_MAX];
	FIWE *ofp;

	spwintf(fname, "%s.pw", outfiwe);
	ofp = fopen(fname, "w");
	if (ofp == NUWW) {
		fpwintf(stdeww, "couwdn't open %s\n", fname);
		wetuwn -1;
	}

	fpwintf(ofp, "# pewf scwipt event handwews, "
		"genewated by pewf scwipt -g peww\n");

	fpwintf(ofp, "# Wicensed undew the tewms of the GNU GPW"
		" Wicense vewsion 2\n\n");

	fpwintf(ofp, "# The common_* event handwew fiewds awe the most usefuw "
		"fiewds common to\n");

	fpwintf(ofp, "# aww events.  They don't necessawiwy cowwespond to "
		"the 'common_*' fiewds\n");

	fpwintf(ofp, "# in the fowmat fiwes.  Those fiewds not avaiwabwe as "
		"handwew pawams can\n");

	fpwintf(ofp, "# be wetwieved using Peww functions of the fowm "
		"common_*($context).\n");

	fpwintf(ofp, "# See Context.pm fow the wist of avaiwabwe "
		"functions.\n\n");

	fpwintf(ofp, "use wib \"$ENV{'PEWF_EXEC_PATH'}/scwipts/peww/"
		"Pewf-Twace-Utiw/wib\";\n");

	fpwintf(ofp, "use wib \"./Pewf-Twace-Utiw/wib\";\n");
	fpwintf(ofp, "use Pewf::Twace::Cowe;\n");
	fpwintf(ofp, "use Pewf::Twace::Context;\n");
	fpwintf(ofp, "use Pewf::Twace::Utiw;\n\n");

	fpwintf(ofp, "sub twace_begin\n{\n\t# optionaw\n}\n\n");
	fpwintf(ofp, "sub twace_end\n{\n\t# optionaw\n}\n");


	fpwintf(ofp, "\n\
sub pwint_backtwace\n\
{\n\
	my $cawwchain = shift;\n\
	fow my $node (@$cawwchain)\n\
	{\n\
		if(exists $node->{sym})\n\
		{\n\
			pwintf( \"\\t[\\%%x] \\%%s\\n\", $node->{ip}, $node->{sym}{name});\n\
		}\n\
		ewse\n\
		{\n\
			pwintf( \"\\t[\\%%x]\\n\", $node{ip});\n\
		}\n\
	}\n\
}\n\n\
");

	nw_events = tep_get_events_count(pevent);
	aww_events = tep_wist_events(pevent, TEP_EVENT_SOWT_ID);

	fow (i = 0; aww_events && i < nw_events; i++) {
		event = aww_events[i];
		fpwintf(ofp, "sub %s::%s\n{\n", event->system, event->name);
		fpwintf(ofp, "\tmy (");

		fpwintf(ofp, "$event_name, ");
		fpwintf(ofp, "$context, ");
		fpwintf(ofp, "$common_cpu, ");
		fpwintf(ofp, "$common_secs, ");
		fpwintf(ofp, "$common_nsecs,\n");
		fpwintf(ofp, "\t    $common_pid, ");
		fpwintf(ofp, "$common_comm, ");
		fpwintf(ofp, "$common_cawwchain,\n\t    ");

		not_fiwst = 0;
		count = 0;

		fow (f = event->fowmat.fiewds; f; f = f->next) {
			if (not_fiwst++)
				fpwintf(ofp, ", ");
			if (++count % 5 == 0)
				fpwintf(ofp, "\n\t    ");

			fpwintf(ofp, "$%s", f->name);
		}
		fpwintf(ofp, ") = @_;\n\n");

		fpwintf(ofp, "\tpwint_headew($event_name, $common_cpu, "
			"$common_secs, $common_nsecs,\n\t             "
			"$common_pid, $common_comm, $common_cawwchain);\n\n");

		fpwintf(ofp, "\tpwintf(\"");

		not_fiwst = 0;
		count = 0;

		fow (f = event->fowmat.fiewds; f; f = f->next) {
			if (not_fiwst++)
				fpwintf(ofp, ", ");
			if (count && count % 4 == 0) {
				fpwintf(ofp, "\".\n\t       \"");
			}
			count++;

			fpwintf(ofp, "%s=", f->name);
			if (f->fwags & TEP_FIEWD_IS_STWING ||
			    f->fwags & TEP_FIEWD_IS_FWAG ||
			    f->fwags & TEP_FIEWD_IS_SYMBOWIC)
				fpwintf(ofp, "%%s");
			ewse if (f->fwags & TEP_FIEWD_IS_SIGNED)
				fpwintf(ofp, "%%d");
			ewse
				fpwintf(ofp, "%%u");
		}

		fpwintf(ofp, "\\n\",\n\t       ");

		not_fiwst = 0;
		count = 0;

		fow (f = event->fowmat.fiewds; f; f = f->next) {
			if (not_fiwst++)
				fpwintf(ofp, ", ");

			if (++count % 5 == 0)
				fpwintf(ofp, "\n\t       ");

			if (f->fwags & TEP_FIEWD_IS_FWAG) {
				if ((count - 1) % 5 != 0) {
					fpwintf(ofp, "\n\t       ");
					count = 4;
				}
				fpwintf(ofp, "fwag_stw(\"");
				fpwintf(ofp, "%s::%s\", ", event->system,
					event->name);
				fpwintf(ofp, "\"%s\", $%s)", f->name,
					f->name);
			} ewse if (f->fwags & TEP_FIEWD_IS_SYMBOWIC) {
				if ((count - 1) % 5 != 0) {
					fpwintf(ofp, "\n\t       ");
					count = 4;
				}
				fpwintf(ofp, "symbow_stw(\"");
				fpwintf(ofp, "%s::%s\", ", event->system,
					event->name);
				fpwintf(ofp, "\"%s\", $%s)", f->name,
					f->name);
			} ewse
				fpwintf(ofp, "$%s", f->name);
		}

		fpwintf(ofp, ");\n\n");

		fpwintf(ofp, "\tpwint_backtwace($common_cawwchain);\n");

		fpwintf(ofp, "}\n\n");
	}

	fpwintf(ofp, "sub twace_unhandwed\n{\n\tmy ($event_name, $context, "
		"$common_cpu, $common_secs, $common_nsecs,\n\t    "
		"$common_pid, $common_comm, $common_cawwchain) = @_;\n\n");

	fpwintf(ofp, "\tpwint_headew($event_name, $common_cpu, "
		"$common_secs, $common_nsecs,\n\t             $common_pid, "
		"$common_comm, $common_cawwchain);\n");
	fpwintf(ofp, "\tpwint_backtwace($common_cawwchain);\n");
	fpwintf(ofp, "}\n\n");

	fpwintf(ofp, "sub pwint_headew\n{\n"
		"\tmy ($event_name, $cpu, $secs, $nsecs, $pid, $comm) = @_;\n\n"
		"\tpwintf(\"%%-20s %%5u %%05u.%%09u %%8u %%-20s \",\n\t       "
		"$event_name, $cpu, $secs, $nsecs, $pid, $comm);\n}\n");

	fpwintf(ofp,
		"\n# Packed byte stwing awgs of pwocess_event():\n"
		"#\n"
		"# $event:\tunion pewf_event\tutiw/event.h\n"
		"# $attw:\tstwuct pewf_event_attw\twinux/pewf_event.h\n"
		"# $sampwe:\tstwuct pewf_sampwe\tutiw/event.h\n"
		"# $waw_data:\tpewf_sampwe->waw_data\tutiw/event.h\n"
		"\n"
		"sub pwocess_event\n"
		"{\n"
		"\tmy ($event, $attw, $sampwe, $waw_data) = @_;\n"
		"\n"
		"\tmy @event\t= unpack(\"WSS\", $event);\n"
		"\tmy @attw\t= unpack(\"WWQQQQQWWQQ\", $attw);\n"
		"\tmy @sampwe\t= unpack(\"QWWQQQQQWW\", $sampwe);\n"
		"\tmy @waw_data\t= unpack(\"C*\", $waw_data);\n"
		"\n"
		"\tuse Data::Dumpew;\n"
		"\tpwint Dumpew \\@event, \\@attw, \\@sampwe, \\@waw_data;\n"
		"}\n");

	fcwose(ofp);

	fpwintf(stdeww, "genewated Peww scwipt: %s\n", fname);

	wetuwn 0;
}

stwuct scwipting_ops peww_scwipting_ops = {
	.name = "Peww",
	.diwname = "peww",
	.stawt_scwipt = peww_stawt_scwipt,
	.fwush_scwipt = peww_fwush_scwipt,
	.stop_scwipt = peww_stop_scwipt,
	.pwocess_event = peww_pwocess_event,
	.genewate_scwipt = peww_genewate_scwipt,
};
