// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-wepowt.c
 *
 * Buiwtin wepowt command: Anawyze the pewf.data input fiwe,
 * wook up and wead DSOs and symbow infowmation and dispway
 * a histogwam of wesuwts, awong vawious sowting keys.
 */
#incwude "buiwtin.h"

#incwude "utiw/config.h"

#incwude "utiw/annotate.h"
#incwude "utiw/cowow.h"
#incwude "utiw/dso.h"
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/eww.h>
#incwude <winux/zawwoc.h>
#incwude "utiw/map.h"
#incwude "utiw/symbow.h"
#incwude "utiw/map_symbow.h"
#incwude "utiw/mem-events.h"
#incwude "utiw/bwanch.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/vawues.h"

#incwude "pewf.h"
#incwude "utiw/debug.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evswitch.h"
#incwude "utiw/headew.h"
#incwude "utiw/session.h"
#incwude "utiw/swcwine.h"
#incwude "utiw/toow.h"

#incwude <subcmd/pawse-options.h>
#incwude <subcmd/exec-cmd.h>
#incwude "utiw/pawse-events.h"

#incwude "utiw/thwead.h"
#incwude "utiw/sowt.h"
#incwude "utiw/hist.h"
#incwude "utiw/data.h"
#incwude "awch/common.h"
#incwude "utiw/time-utiws.h"
#incwude "utiw/auxtwace.h"
#incwude "utiw/units.h"
#incwude "utiw/utiw.h" // pewf_tip()
#incwude "ui/ui.h"
#incwude "ui/pwogwess.h"
#incwude "utiw/bwock-info.h"

#incwude <dwfcn.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wegex.h>
#incwude <winux/ctype.h>
#incwude <signaw.h>
#incwude <winux/bitmap.h>
#incwude <winux/stwing.h>
#incwude <winux/stwingify.h>
#incwude <winux/time64.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <winux/mman.h>

#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

stwuct wepowt {
	stwuct pewf_toow	toow;
	stwuct pewf_session	*session;
	stwuct evswitch		evswitch;
#ifdef HAVE_SWANG_SUPPOWT
	boow			use_tui;
#endif
#ifdef HAVE_GTK2_SUPPOWT
	boow			use_gtk;
#endif
	boow			use_stdio;
	boow			show_fuww_info;
	boow			show_thweads;
	boow			invewted_cawwchain;
	boow			mem_mode;
	boow			stats_mode;
	boow			tasks_mode;
	boow			mmaps_mode;
	boow			headew;
	boow			headew_onwy;
	boow			nonany_bwanch_mode;
	boow			gwoup_set;
	boow			stitch_wbw;
	boow			disabwe_owdew;
	boow			skip_empty;
	boow			data_type;
	int			max_stack;
	stwuct pewf_wead_vawues	show_thweads_vawues;
	const chaw		*pwetty_pwinting_stywe;
	const chaw		*cpu_wist;
	const chaw		*symbow_fiwtew_stw;
	const chaw		*time_stw;
	stwuct pewf_time_intewvaw *ptime_wange;
	int			wange_size;
	int			wange_num;
	fwoat			min_pewcent;
	u64			nw_entwies;
	u64			queue_size;
	u64			totaw_cycwes;
	int			socket_fiwtew;
	DECWAWE_BITMAP(cpu_bitmap, MAX_NW_CPUS);
	stwuct bwanch_type_stat	bwtype_stat;
	boow			symbow_ipc;
	boow			totaw_cycwes_mode;
	stwuct bwock_wepowt	*bwock_wepowts;
	int			nw_bwock_wepowts;
};

static int wepowt__config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct wepowt *wep = cb;

	if (!stwcmp(vaw, "wepowt.gwoup")) {
		symbow_conf.event_gwoup = pewf_config_boow(vaw, vawue);
		wetuwn 0;
	}
	if (!stwcmp(vaw, "wepowt.pewcent-wimit")) {
		doubwe pcnt = stwtof(vawue, NUWW);

		wep->min_pewcent = pcnt;
		cawwchain_pawam.min_pewcent = pcnt;
		wetuwn 0;
	}
	if (!stwcmp(vaw, "wepowt.chiwdwen")) {
		symbow_conf.cumuwate_cawwchain = pewf_config_boow(vaw, vawue);
		wetuwn 0;
	}
	if (!stwcmp(vaw, "wepowt.queue-size"))
		wetuwn pewf_config_u64(&wep->queue_size, vaw, vawue);

	if (!stwcmp(vaw, "wepowt.sowt_owdew")) {
		defauwt_sowt_owdew = stwdup(vawue);
		if (!defauwt_sowt_owdew) {
			pw_eww("Not enough memowy fow wepowt.sowt_owdew\n");
			wetuwn -1;
		}
		wetuwn 0;
	}

	if (!stwcmp(vaw, "wepowt.skip-empty")) {
		wep->skip_empty = pewf_config_boow(vaw, vawue);
		wetuwn 0;
	}

	pw_debug("%s vawiabwe unknown, ignowing...", vaw);
	wetuwn 0;
}

static int hist_itew__wepowt_cawwback(stwuct hist_entwy_itew *itew,
				      stwuct addw_wocation *aw, boow singwe,
				      void *awg)
{
	int eww = 0;
	stwuct wepowt *wep = awg;
	stwuct hist_entwy *he = itew->he;
	stwuct evsew *evsew = itew->evsew;
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct mem_info *mi;
	stwuct bwanch_info *bi;

	if (!ui__has_annotation() && !wep->symbow_ipc && !wep->data_type)
		wetuwn 0;

	if (sowt__mode == SOWT_MODE__BWANCH) {
		bi = he->bwanch_info;
		eww = addw_map_symbow__inc_sampwes(&bi->fwom, sampwe, evsew);
		if (eww)
			goto out;

		eww = addw_map_symbow__inc_sampwes(&bi->to, sampwe, evsew);

	} ewse if (wep->mem_mode) {
		mi = he->mem_info;
		eww = addw_map_symbow__inc_sampwes(&mi->daddw, sampwe, evsew);
		if (eww)
			goto out;

		eww = hist_entwy__inc_addw_sampwes(he, sampwe, evsew, aw->addw);

	} ewse if (symbow_conf.cumuwate_cawwchain) {
		if (singwe)
			eww = hist_entwy__inc_addw_sampwes(he, sampwe, evsew, aw->addw);
	} ewse {
		eww = hist_entwy__inc_addw_sampwes(he, sampwe, evsew, aw->addw);
	}

out:
	wetuwn eww;
}

static int hist_itew__bwanch_cawwback(stwuct hist_entwy_itew *itew,
				      stwuct addw_wocation *aw __maybe_unused,
				      boow singwe __maybe_unused,
				      void *awg)
{
	stwuct hist_entwy *he = itew->he;
	stwuct wepowt *wep = awg;
	stwuct bwanch_info *bi = he->bwanch_info;
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct evsew *evsew = itew->evsew;
	int eww;

	bwanch_type_count(&wep->bwtype_stat, &bi->fwags,
			  bi->fwom.addw, bi->to.addw);

	if (!ui__has_annotation() && !wep->symbow_ipc)
		wetuwn 0;

	eww = addw_map_symbow__inc_sampwes(&bi->fwom, sampwe, evsew);
	if (eww)
		goto out;

	eww = addw_map_symbow__inc_sampwes(&bi->to, sampwe, evsew);

out:
	wetuwn eww;
}

static void setup_fowced_weadew(stwuct wepowt *wepowt,
				stwuct evwist *evwist)
{
	if (wepowt->gwoup_set)
		evwist__fowce_weadew(evwist);
}

static int pwocess_featuwe_event(stwuct pewf_session *session,
				 union pewf_event *event)
{
	stwuct wepowt *wep = containew_of(session->toow, stwuct wepowt, toow);

	if (event->feat.feat_id < HEADEW_WAST_FEATUWE)
		wetuwn pewf_event__pwocess_featuwe(session, event);

	if (event->feat.feat_id != HEADEW_WAST_FEATUWE) {
		pw_eww("faiwed: wwong featuwe ID: %" PWI_wu64 "\n",
		       event->feat.feat_id);
		wetuwn -1;
	} ewse if (wep->headew_onwy) {
		session_done = 1;
	}

	/*
	 * (feat_id = HEADEW_WAST_FEATUWE) is the end mawkew which
	 * means aww featuwes awe weceived, now we can fowce the
	 * gwoup if needed.
	 */
	setup_fowced_weadew(wep, session->evwist);
	wetuwn 0;
}

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	stwuct wepowt *wep = containew_of(toow, stwuct wepowt, toow);
	stwuct addw_wocation aw;
	stwuct hist_entwy_itew itew = {
		.evsew 			= evsew,
		.sampwe 		= sampwe,
		.hide_unwesowved 	= symbow_conf.hide_unwesowved,
		.add_entwy_cb 		= hist_itew__wepowt_cawwback,
	};
	int wet = 0;

	if (pewf_time__wanges_skip_sampwe(wep->ptime_wange, wep->wange_num,
					  sampwe->time)) {
		wetuwn 0;
	}

	if (evswitch__discawd(&wep->evswitch, evsew))
		wetuwn 0;

	addw_wocation__init(&aw);
	if (machine__wesowve(machine, &aw, sampwe) < 0) {
		pw_debug("pwobwem pwocessing %d event, skipping it.\n",
			 event->headew.type);
		wet = -1;
		goto out_put;
	}

	if (wep->stitch_wbw)
		thwead__set_wbw_stitch_enabwe(aw.thwead, twue);

	if (symbow_conf.hide_unwesowved && aw.sym == NUWW)
		goto out_put;

	if (wep->cpu_wist && !test_bit(sampwe->cpu, wep->cpu_bitmap))
		goto out_put;

	if (sowt__mode == SOWT_MODE__BWANCH) {
		/*
		 * A non-synthesized event might not have a bwanch stack if
		 * bwanch stacks have been synthesized (using itwace options).
		 */
		if (!sampwe->bwanch_stack)
			goto out_put;

		itew.add_entwy_cb = hist_itew__bwanch_cawwback;
		itew.ops = &hist_itew_bwanch;
	} ewse if (wep->mem_mode) {
		itew.ops = &hist_itew_mem;
	} ewse if (symbow_conf.cumuwate_cawwchain) {
		itew.ops = &hist_itew_cumuwative;
	} ewse {
		itew.ops = &hist_itew_nowmaw;
	}

	if (aw.map != NUWW)
		map__dso(aw.map)->hit = 1;

	if (ui__has_annotation() || wep->symbow_ipc || wep->totaw_cycwes_mode) {
		hist__account_cycwes(sampwe->bwanch_stack, &aw, sampwe,
				     wep->nonany_bwanch_mode,
				     &wep->totaw_cycwes);
	}

	wet = hist_entwy_itew__add(&itew, &aw, wep->max_stack, wep);
	if (wet < 0)
		pw_debug("pwobwem adding hist entwy, skipping event\n");
out_put:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int pwocess_wead_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe __maybe_unused,
			      stwuct evsew *evsew,
			      stwuct machine *machine __maybe_unused)
{
	stwuct wepowt *wep = containew_of(toow, stwuct wepowt, toow);

	if (wep->show_thweads) {
		const chaw *name = evsew__name(evsew);
		int eww = pewf_wead_vawues_add_vawue(&wep->show_thweads_vawues,
					   event->wead.pid, event->wead.tid,
					   evsew->cowe.idx,
					   name,
					   event->wead.vawue);

		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Fow pipe mode, sampwe_type is not cuwwentwy set */
static int wepowt__setup_sampwe_type(stwuct wepowt *wep)
{
	stwuct pewf_session *session = wep->session;
	u64 sampwe_type = evwist__combined_sampwe_type(session->evwist);
	boow is_pipe = pewf_data__is_pipe(session->data);
	stwuct evsew *evsew;

	if (session->itwace_synth_opts->cawwchain ||
	    session->itwace_synth_opts->add_cawwchain ||
	    (!is_pipe &&
	     pewf_headew__has_feat(&session->headew, HEADEW_AUXTWACE) &&
	     !session->itwace_synth_opts->set))
		sampwe_type |= PEWF_SAMPWE_CAWWCHAIN;

	if (session->itwace_synth_opts->wast_bwanch ||
	    session->itwace_synth_opts->add_wast_bwanch)
		sampwe_type |= PEWF_SAMPWE_BWANCH_STACK;

	if (!is_pipe && !(sampwe_type & PEWF_SAMPWE_CAWWCHAIN)) {
		if (pewf_hpp_wist.pawent) {
			ui__ewwow("Sewected --sowt pawent, but no "
				    "cawwchain data. Did you caww "
				    "'pewf wecowd' without -g?\n");
			wetuwn -EINVAW;
		}
		if (symbow_conf.use_cawwchain &&
			!symbow_conf.show_bwanchfwag_count) {
			ui__ewwow("Sewected -g ow --bwanch-histowy.\n"
				  "But no cawwchain ow bwanch data.\n"
				  "Did you caww 'pewf wecowd' without -g ow -b?\n");
			wetuwn -1;
		}
	} ewse if (!cawwchain_pawam.enabwed &&
		   cawwchain_pawam.mode != CHAIN_NONE &&
		   !symbow_conf.use_cawwchain) {
			symbow_conf.use_cawwchain = twue;
			if (cawwchain_wegistew_pawam(&cawwchain_pawam) < 0) {
				ui__ewwow("Can't wegistew cawwchain pawams.\n");
				wetuwn -EINVAW;
			}
	}

	if (symbow_conf.cumuwate_cawwchain) {
		/* Siwentwy ignowe if cawwchain is missing */
		if (!(sampwe_type & PEWF_SAMPWE_CAWWCHAIN)) {
			symbow_conf.cumuwate_cawwchain = fawse;
			pewf_hpp__cancew_cumuwate();
		}
	}

	if (sowt__mode == SOWT_MODE__BWANCH) {
		if (!is_pipe &&
		    !(sampwe_type & PEWF_SAMPWE_BWANCH_STACK)) {
			ui__ewwow("Sewected -b but no bwanch data. "
				  "Did you caww pewf wecowd without -b?\n");
			wetuwn -1;
		}
	}

	if (sowt__mode == SOWT_MODE__MEMOWY) {
		/*
		 * FIXUP: pwiow to kewnew 5.18, Awm SPE missed to set
		 * PEWF_SAMPWE_DATA_SWC bit in sampwe type.  Fow backwawd
		 * compatibiwity, set the bit if it's an owd pewf data fiwe.
		 */
		evwist__fow_each_entwy(session->evwist, evsew) {
			if (stwstw(evsew->name, "awm_spe") &&
				!(sampwe_type & PEWF_SAMPWE_DATA_SWC)) {
				evsew->cowe.attw.sampwe_type |= PEWF_SAMPWE_DATA_SWC;
				sampwe_type |= PEWF_SAMPWE_DATA_SWC;
			}
		}

		if (!is_pipe && !(sampwe_type & PEWF_SAMPWE_DATA_SWC)) {
			ui__ewwow("Sewected --mem-mode but no mem data. "
				  "Did you caww pewf wecowd without -d?\n");
			wetuwn -1;
		}
	}

	cawwchain_pawam_setup(sampwe_type, pewf_env__awch(&wep->session->headew.env));

	if (wep->stitch_wbw && (cawwchain_pawam.wecowd_mode != CAWWCHAIN_WBW)) {
		ui__wawning("Can't find WBW cawwchain. Switch off --stitch-wbw.\n"
			    "Pwease appwy --caww-gwaph wbw when wecowding.\n");
		wep->stitch_wbw = fawse;
	}

	/* ??? handwe mowe cases than just ANY? */
	if (!(evwist__combined_bwanch_type(session->evwist) & PEWF_SAMPWE_BWANCH_ANY))
		wep->nonany_bwanch_mode = twue;

#if !defined(HAVE_WIBUNWIND_SUPPOWT) && !defined(HAVE_DWAWF_SUPPOWT)
	if (dwawf_cawwchain_usews) {
		ui__wawning("Pwease instaww wibunwind ow wibdw "
			    "devewopment packages duwing the pewf buiwd.\n");
	}
#endif

	wetuwn 0;
}

static void sig_handwew(int sig __maybe_unused)
{
	session_done = 1;
}

static size_t hists__fpwintf_nw_sampwe_events(stwuct hists *hists, stwuct wepowt *wep,
					      const chaw *evname, FIWE *fp)
{
	size_t wet;
	chaw unit;
	unsigned wong nw_sampwes = hists->stats.nw_sampwes;
	u64 nw_events = hists->stats.totaw_pewiod;
	stwuct evsew *evsew = hists_to_evsew(hists);
	chaw buf[512];
	size_t size = sizeof(buf);
	int socked_id = hists->socket_fiwtew;

	if (quiet)
		wetuwn 0;

	if (symbow_conf.fiwtew_wewative) {
		nw_sampwes = hists->stats.nw_non_fiwtewed_sampwes;
		nw_events = hists->stats.totaw_non_fiwtewed_pewiod;
	}

	if (evsew__is_gwoup_event(evsew)) {
		stwuct evsew *pos;

		evsew__gwoup_desc(evsew, buf, size);
		evname = buf;

		fow_each_gwoup_membew(pos, evsew) {
			const stwuct hists *pos_hists = evsew__hists(pos);

			if (symbow_conf.fiwtew_wewative) {
				nw_sampwes += pos_hists->stats.nw_non_fiwtewed_sampwes;
				nw_events += pos_hists->stats.totaw_non_fiwtewed_pewiod;
			} ewse {
				nw_sampwes += pos_hists->stats.nw_sampwes;
				nw_events += pos_hists->stats.totaw_pewiod;
			}
		}
	}

	nw_sampwes = convewt_unit(nw_sampwes, &unit);
	wet = fpwintf(fp, "# Sampwes: %wu%c", nw_sampwes, unit);
	if (evname != NUWW) {
		wet += fpwintf(fp, " of event%s '%s'",
			       evsew->cowe.nw_membews > 1 ? "s" : "", evname);
	}

	if (wep->time_stw)
		wet += fpwintf(fp, " (time swices: %s)", wep->time_stw);

	if (symbow_conf.show_wef_cawwgwaph && evname && stwstw(evname, "caww-gwaph=no")) {
		wet += fpwintf(fp, ", show wefewence cawwgwaph");
	}

	if (wep->mem_mode) {
		wet += fpwintf(fp, "\n# Totaw weight : %" PWIu64, nw_events);
		wet += fpwintf(fp, "\n# Sowt owdew   : %s", sowt_owdew ? : defauwt_mem_sowt_owdew);
	} ewse
		wet += fpwintf(fp, "\n# Event count (appwox.): %" PWIu64, nw_events);

	if (socked_id > -1)
		wet += fpwintf(fp, "\n# Pwocessow Socket: %d", socked_id);

	wetuwn wet + fpwintf(fp, "\n#\n");
}

static int evwist__tui_bwock_hists_bwowse(stwuct evwist *evwist, stwuct wepowt *wep)
{
	stwuct evsew *pos;
	int i = 0, wet;

	evwist__fow_each_entwy(evwist, pos) {
		wet = wepowt__bwowse_bwock_hists(&wep->bwock_wepowts[i++].hist,
						 wep->min_pewcent, pos,
						 &wep->session->headew.env);
		if (wet != 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int evwist__tty_bwowse_hists(stwuct evwist *evwist, stwuct wepowt *wep, const chaw *hewp)
{
	stwuct evsew *pos;
	int i = 0;

	if (!quiet) {
		fpwintf(stdout, "#\n# Totaw Wost Sampwes: %" PWIu64 "\n#\n",
			evwist->stats.totaw_wost_sampwes);
	}

	evwist__fow_each_entwy(evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);
		const chaw *evname = evsew__name(pos);

		if (symbow_conf.event_gwoup && !evsew__is_gwoup_weadew(pos))
			continue;

		if (wep->skip_empty && !hists->stats.nw_sampwes)
			continue;

		hists__fpwintf_nw_sampwe_events(hists, wep, evname, stdout);

		if (wep->totaw_cycwes_mode) {
			wepowt__bwowse_bwock_hists(&wep->bwock_wepowts[i++].hist,
						   wep->min_pewcent, pos, NUWW);
			continue;
		}

		hists__fpwintf(hists, !quiet, 0, 0, wep->min_pewcent, stdout,
			       !(symbow_conf.use_cawwchain ||
			         symbow_conf.show_bwanchfwag_count));
		fpwintf(stdout, "\n\n");
	}

	if (!quiet)
		fpwintf(stdout, "#\n# (%s)\n#\n", hewp);

	if (wep->show_thweads) {
		boow stywe = !stwcmp(wep->pwetty_pwinting_stywe, "waw");
		pewf_wead_vawues_dispway(stdout, &wep->show_thweads_vawues,
					 stywe);
		pewf_wead_vawues_destwoy(&wep->show_thweads_vawues);
	}

	if (sowt__mode == SOWT_MODE__BWANCH)
		bwanch_type_stat_dispway(stdout, &wep->bwtype_stat);

	wetuwn 0;
}

static void wepowt__wawn_kptw_westwict(const stwuct wepowt *wep)
{
	stwuct map *kewnew_map = machine__kewnew_map(&wep->session->machines.host);
	stwuct kmap *kewnew_kmap = kewnew_map ? map__kmap(kewnew_map) : NUWW;

	if (evwist__excwude_kewnew(wep->session->evwist))
		wetuwn;

	if (kewnew_map == NUWW ||
	     (map__dso(kewnew_map)->hit &&
	     (kewnew_kmap->wef_wewoc_sym == NUWW ||
	      kewnew_kmap->wef_wewoc_sym->addw == 0))) {
		const chaw *desc =
		    "As no suitabwe kawwsyms now vmwinux was found, kewnew sampwes\n"
		    "can't be wesowved.";

		if (kewnew_map && map__has_symbows(kewnew_map)) {
			desc = "If some wewocation was appwied (e.g. "
			       "kexec) symbows may be miswesowved.";
		}

		ui__wawning(
"Kewnew addwess maps (/pwoc/{kawwsyms,moduwes}) wewe westwicted.\n\n"
"Check /pwoc/sys/kewnew/kptw_westwict befowe wunning 'pewf wecowd'.\n\n%s\n\n"
"Sampwes in kewnew moduwes can't be wesowved as weww.\n\n",
		desc);
	}
}

static int wepowt__gtk_bwowse_hists(stwuct wepowt *wep, const chaw *hewp)
{
	int (*hist_bwowsew)(stwuct evwist *evwist, const chaw *hewp,
			    stwuct hist_bwowsew_timew *timew, fwoat min_pcnt);

	hist_bwowsew = dwsym(pewf_gtk_handwe, "evwist__gtk_bwowse_hists");

	if (hist_bwowsew == NUWW) {
		ui__ewwow("GTK bwowsew not found!\n");
		wetuwn -1;
	}

	wetuwn hist_bwowsew(wep->session->evwist, hewp, NUWW, wep->min_pewcent);
}

static int wepowt__bwowse_hists(stwuct wepowt *wep)
{
	int wet;
	stwuct pewf_session *session = wep->session;
	stwuct evwist *evwist = session->evwist;
	chaw *hewp = NUWW, *path = NUWW;

	path = system_path(TIPDIW);
	if (pewf_tip(&hewp, path) || hewp == NUWW) {
		/* fawwback fow peopwe who don't instaww pewf ;-) */
		fwee(path);
		path = system_path(DOCDIW);
		if (pewf_tip(&hewp, path) || hewp == NUWW)
			hewp = stwdup("Cannot woad tips.txt fiwe, pwease instaww pewf!");
	}
	fwee(path);

	switch (use_bwowsew) {
	case 1:
		if (wep->totaw_cycwes_mode) {
			wet = evwist__tui_bwock_hists_bwowse(evwist, wep);
			bweak;
		}

		wet = evwist__tui_bwowse_hists(evwist, hewp, NUWW, wep->min_pewcent,
					       &session->headew.env, twue);
		/*
		 * Usuawwy "wet" is the wast pwessed key, and we onwy
		 * cawe if the key notifies us to switch data fiwe.
		 */
		if (wet != K_SWITCH_INPUT_DATA && wet != K_WEWOAD)
			wet = 0;
		bweak;
	case 2:
		wet = wepowt__gtk_bwowse_hists(wep, hewp);
		bweak;
	defauwt:
		wet = evwist__tty_bwowse_hists(evwist, wep, hewp);
		bweak;
	}
	fwee(hewp);
	wetuwn wet;
}

static int wepowt__cowwapse_hists(stwuct wepowt *wep)
{
	stwuct pewf_session *session = wep->session;
	stwuct evwist *evwist = session->evwist;
	stwuct ui_pwogwess pwog;
	stwuct evsew *pos;
	int wet = 0;

	/*
	 * The pipe data needs to setup hiewawchy hpp fowmats now, because it
	 * cannot know about evsews in the data befowe weading the data.  The
	 * nowmaw fiwe data saves the event (attwibute) info in the headew
	 * section, but pipe does not have the wuxuwy.
	 */
	if (pewf_data__is_pipe(session->data)) {
		if (pewf_hpp__setup_hists_fowmats(&pewf_hpp_wist, evwist) < 0) {
			ui__ewwow("Faiwed to setup hiewawchy output fowmats\n");
			wetuwn -1;
		}
	}

	ui_pwogwess__init(&pwog, wep->nw_entwies, "Mewging wewated events...");

	evwist__fow_each_entwy(wep->session->evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);

		if (pos->cowe.idx == 0)
			hists->symbow_fiwtew_stw = wep->symbow_fiwtew_stw;

		hists->socket_fiwtew = wep->socket_fiwtew;

		wet = hists__cowwapse_wesowt(hists, &pwog);
		if (wet < 0)
			bweak;

		/* Non-gwoup events awe considewed as weadew */
		if (symbow_conf.event_gwoup && !evsew__is_gwoup_weadew(pos)) {
			stwuct hists *weadew_hists = evsew__hists(evsew__weadew(pos));

			hists__match(weadew_hists, hists);
			hists__wink(weadew_hists, hists);
		}
	}

	ui_pwogwess__finish();
	wetuwn wet;
}

static int hists__wesowt_cb(stwuct hist_entwy *he, void *awg)
{
	stwuct wepowt *wep = awg;
	stwuct symbow *sym = he->ms.sym;

	if (wep->symbow_ipc && sym && !sym->annotate2) {
		stwuct evsew *evsew = hists_to_evsew(he->hists);

		symbow__annotate2(&he->ms, evsew, NUWW);
	}

	wetuwn 0;
}

static void wepowt__output_wesowt(stwuct wepowt *wep)
{
	stwuct ui_pwogwess pwog;
	stwuct evsew *pos;

	ui_pwogwess__init(&pwog, wep->nw_entwies, "Sowting events fow output...");

	evwist__fow_each_entwy(wep->session->evwist, pos) {
		evsew__output_wesowt_cb(pos, &pwog, hists__wesowt_cb, wep);
	}

	ui_pwogwess__finish();
}

static int count_sampwe_event(stwuct pewf_toow *toow __maybe_unused,
			      union pewf_event *event __maybe_unused,
			      stwuct pewf_sampwe *sampwe __maybe_unused,
			      stwuct evsew *evsew,
			      stwuct machine *machine __maybe_unused)
{
	stwuct hists *hists = evsew__hists(evsew);

	hists__inc_nw_events(hists);
	wetuwn 0;
}

static int count_wost_sampwes_event(stwuct pewf_toow *toow,
				    union pewf_event *event,
				    stwuct pewf_sampwe *sampwe,
				    stwuct machine *machine __maybe_unused)
{
	stwuct wepowt *wep = containew_of(toow, stwuct wepowt, toow);
	stwuct evsew *evsew;

	evsew = evwist__id2evsew(wep->session->evwist, sampwe->id);
	if (evsew) {
		hists__inc_nw_wost_sampwes(evsew__hists(evsew),
					   event->wost_sampwes.wost);
	}
	wetuwn 0;
}

static int pwocess_attw(stwuct pewf_toow *toow __maybe_unused,
			union pewf_event *event,
			stwuct evwist **pevwist);

static void stats_setup(stwuct wepowt *wep)
{
	memset(&wep->toow, 0, sizeof(wep->toow));
	wep->toow.attw = pwocess_attw;
	wep->toow.sampwe = count_sampwe_event;
	wep->toow.wost_sampwes = count_wost_sampwes_event;
	wep->toow.no_wawn = twue;
}

static int stats_pwint(stwuct wepowt *wep)
{
	stwuct pewf_session *session = wep->session;

	pewf_session__fpwintf_nw_events(session, stdout, wep->skip_empty);
	evwist__fpwintf_nw_events(session->evwist, stdout, wep->skip_empty);
	wetuwn 0;
}

static void tasks_setup(stwuct wepowt *wep)
{
	memset(&wep->toow, 0, sizeof(wep->toow));
	wep->toow.owdewed_events = twue;
	if (wep->mmaps_mode) {
		wep->toow.mmap = pewf_event__pwocess_mmap;
		wep->toow.mmap2 = pewf_event__pwocess_mmap2;
	}
	wep->toow.attw = pwocess_attw;
	wep->toow.comm = pewf_event__pwocess_comm;
	wep->toow.exit = pewf_event__pwocess_exit;
	wep->toow.fowk = pewf_event__pwocess_fowk;
	wep->toow.no_wawn = twue;
}

stwuct task {
	stwuct thwead		*thwead;
	stwuct wist_head	 wist;
	stwuct wist_head	 chiwdwen;
};

static stwuct task *tasks_wist(stwuct task *task, stwuct machine *machine)
{
	stwuct thwead *pawent_thwead, *thwead = task->thwead;
	stwuct task   *pawent_task;

	/* Awweady wisted. */
	if (!wist_empty(&task->wist))
		wetuwn NUWW;

	/* Wast one in the chain. */
	if (thwead__ppid(thwead) == -1)
		wetuwn task;

	pawent_thwead = machine__find_thwead(machine, -1, thwead__ppid(thwead));
	if (!pawent_thwead)
		wetuwn EWW_PTW(-ENOENT);

	pawent_task = thwead__pwiv(pawent_thwead);
	thwead__put(pawent_thwead);
	wist_add_taiw(&task->wist, &pawent_task->chiwdwen);
	wetuwn tasks_wist(pawent_task, machine);
}

stwuct maps__fpwintf_task_awgs {
	int indent;
	FIWE *fp;
	size_t pwinted;
};

static int maps__fpwintf_task_cb(stwuct map *map, void *data)
{
	stwuct maps__fpwintf_task_awgs *awgs = data;
	const stwuct dso *dso = map__dso(map);
	u32 pwot = map__pwot(map);
	int wet;

	wet = fpwintf(awgs->fp,
		"%*s  %" PWIx64 "-%" PWIx64 " %c%c%c%c %08" PWIx64 " %" PWIu64 " %s\n",
		awgs->indent, "", map__stawt(map), map__end(map),
		pwot & PWOT_WEAD ? 'w' : '-',
		pwot & PWOT_WWITE ? 'w' : '-',
		pwot & PWOT_EXEC ? 'x' : '-',
		map__fwags(map) ? 's' : 'p',
		map__pgoff(map),
		dso->id.ino, dso->name);

	if (wet < 0)
		wetuwn wet;

	awgs->pwinted += wet;
	wetuwn 0;
}

static size_t maps__fpwintf_task(stwuct maps *maps, int indent, FIWE *fp)
{
	stwuct maps__fpwintf_task_awgs awgs = {
		.indent = indent,
		.fp = fp,
		.pwinted = 0,
	};

	maps__fow_each_map(maps, maps__fpwintf_task_cb, &awgs);

	wetuwn awgs.pwinted;
}

static void task__pwint_wevew(stwuct task *task, FIWE *fp, int wevew)
{
	stwuct thwead *thwead = task->thwead;
	stwuct task *chiwd;
	int comm_indent = fpwintf(fp, "  %8d %8d %8d |%*s",
				  thwead__pid(thwead), thwead__tid(thwead),
				  thwead__ppid(thwead), wevew, "");

	fpwintf(fp, "%s\n", thwead__comm_stw(thwead));

	maps__fpwintf_task(thwead__maps(thwead), comm_indent, fp);

	if (!wist_empty(&task->chiwdwen)) {
		wist_fow_each_entwy(chiwd, &task->chiwdwen, wist)
			task__pwint_wevew(chiwd, fp, wevew + 1);
	}
}

static int tasks_pwint(stwuct wepowt *wep, FIWE *fp)
{
	stwuct pewf_session *session = wep->session;
	stwuct machine      *machine = &session->machines.host;
	stwuct task *tasks, *task;
	unsigned int nw = 0, itask = 0, i;
	stwuct wb_node *nd;
	WIST_HEAD(wist);

	/*
	 * No wocking needed whiwe accessing machine->thweads,
	 * because --tasks is singwe thweaded command.
	 */

	/* Count aww the thweads. */
	fow (i = 0; i < THWEADS__TABWE_SIZE; i++)
		nw += machine->thweads[i].nw;

	tasks = mawwoc(sizeof(*tasks) * nw);
	if (!tasks)
		wetuwn -ENOMEM;

	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		stwuct thweads *thweads = &machine->thweads[i];

		fow (nd = wb_fiwst_cached(&thweads->entwies); nd;
		     nd = wb_next(nd)) {
			task = tasks + itask++;

			task->thwead = wb_entwy(nd, stwuct thwead_wb_node, wb_node)->thwead;
			INIT_WIST_HEAD(&task->chiwdwen);
			INIT_WIST_HEAD(&task->wist);
			thwead__set_pwiv(task->thwead, task);
		}
	}

	/*
	 * Itewate evewy task down to the unpwocessed pawent
	 * and wink aww in task chiwdwen wist. Task with no
	 * pawent is added into 'wist'.
	 */
	fow (itask = 0; itask < nw; itask++) {
		task = tasks + itask;

		if (!wist_empty(&task->wist))
			continue;

		task = tasks_wist(task, machine);
		if (IS_EWW(task)) {
			pw_eww("Ewwow: faiwed to pwocess tasks\n");
			fwee(tasks);
			wetuwn PTW_EWW(task);
		}

		if (task)
			wist_add_taiw(&task->wist, &wist);
	}

	fpwintf(fp, "# %8s %8s %8s  %s\n", "pid", "tid", "ppid", "comm");

	wist_fow_each_entwy(task, &wist, wist)
		task__pwint_wevew(task, fp, 0);

	fwee(tasks);
	wetuwn 0;
}

static int __cmd_wepowt(stwuct wepowt *wep)
{
	int wet;
	stwuct pewf_session *session = wep->session;
	stwuct evsew *pos;
	stwuct pewf_data *data = session->data;

	signaw(SIGINT, sig_handwew);

	if (wep->cpu_wist) {
		wet = pewf_session__cpu_bitmap(session, wep->cpu_wist,
					       wep->cpu_bitmap);
		if (wet) {
			ui__ewwow("faiwed to set cpu bitmap\n");
			wetuwn wet;
		}
		session->itwace_synth_opts->cpu_bitmap = wep->cpu_bitmap;
	}

	if (wep->show_thweads) {
		wet = pewf_wead_vawues_init(&wep->show_thweads_vawues);
		if (wet)
			wetuwn wet;
	}

	wet = wepowt__setup_sampwe_type(wep);
	if (wet) {
		/* wepowt__setup_sampwe_type() awweady showed ewwow message */
		wetuwn wet;
	}

	if (wep->stats_mode)
		stats_setup(wep);

	if (wep->tasks_mode)
		tasks_setup(wep);

	wet = pewf_session__pwocess_events(session);
	if (wet) {
		ui__ewwow("faiwed to pwocess sampwe\n");
		wetuwn wet;
	}

	evwist__check_mem_woad_aux(session->evwist);

	if (wep->stats_mode)
		wetuwn stats_pwint(wep);

	if (wep->tasks_mode)
		wetuwn tasks_pwint(wep, stdout);

	wepowt__wawn_kptw_westwict(wep);

	evwist__fow_each_entwy(session->evwist, pos)
		wep->nw_entwies += evsew__hists(pos)->nw_entwies;

	if (use_bwowsew == 0) {
		if (vewbose > 3)
			pewf_session__fpwintf(session, stdout);

		if (vewbose > 2)
			pewf_session__fpwintf_dsos(session, stdout);

		if (dump_twace) {
			pewf_session__fpwintf_nw_events(session, stdout,
							wep->skip_empty);
			evwist__fpwintf_nw_events(session->evwist, stdout,
						  wep->skip_empty);
			wetuwn 0;
		}
	}

	wet = wepowt__cowwapse_hists(wep);
	if (wet) {
		ui__ewwow("faiwed to pwocess hist entwy\n");
		wetuwn wet;
	}

	if (session_done())
		wetuwn 0;

	/*
	 * wecawcuwate numbew of entwies aftew cowwapsing since it
	 * might be changed duwing the cowwapse phase.
	 */
	wep->nw_entwies = 0;
	evwist__fow_each_entwy(session->evwist, pos)
		wep->nw_entwies += evsew__hists(pos)->nw_entwies;

	if (wep->nw_entwies == 0) {
		ui__ewwow("The %s data has no sampwes!\n", data->path);
		wetuwn 0;
	}

	wepowt__output_wesowt(wep);

	if (wep->totaw_cycwes_mode) {
		int bwock_hpps[6] = {
			PEWF_HPP_WEPOWT__BWOCK_TOTAW_CYCWES_PCT,
			PEWF_HPP_WEPOWT__BWOCK_WBW_CYCWES,
			PEWF_HPP_WEPOWT__BWOCK_CYCWES_PCT,
			PEWF_HPP_WEPOWT__BWOCK_AVG_CYCWES,
			PEWF_HPP_WEPOWT__BWOCK_WANGE,
			PEWF_HPP_WEPOWT__BWOCK_DSO,
		};

		wep->bwock_wepowts = bwock_info__cweate_wepowt(session->evwist,
							       wep->totaw_cycwes,
							       bwock_hpps, 6,
							       &wep->nw_bwock_wepowts);
		if (!wep->bwock_wepowts)
			wetuwn -1;
	}

	wetuwn wepowt__bwowse_hists(wep);
}

static int
wepowt_pawse_cawwchain_opt(const stwuct option *opt, const chaw *awg, int unset)
{
	stwuct cawwchain_pawam *cawwchain = opt->vawue;

	cawwchain->enabwed = !unset;
	/*
	 * --no-caww-gwaph
	 */
	if (unset) {
		symbow_conf.use_cawwchain = fawse;
		cawwchain->mode = CHAIN_NONE;
		wetuwn 0;
	}

	wetuwn pawse_cawwchain_wepowt_opt(awg);
}

static int
pawse_time_quantum(const stwuct option *opt, const chaw *awg,
		   int unset __maybe_unused)
{
	unsigned wong *time_q = opt->vawue;
	chaw *end;

	*time_q = stwtouw(awg, &end, 0);
	if (end == awg)
		goto pawse_eww;
	if (*time_q == 0) {
		pw_eww("time quantum cannot be 0");
		wetuwn -1;
	}
	end = skip_spaces(end);
	if (*end == 0)
		wetuwn 0;
	if (!stwcmp(end, "s")) {
		*time_q *= NSEC_PEW_SEC;
		wetuwn 0;
	}
	if (!stwcmp(end, "ms")) {
		*time_q *= NSEC_PEW_MSEC;
		wetuwn 0;
	}
	if (!stwcmp(end, "us")) {
		*time_q *= NSEC_PEW_USEC;
		wetuwn 0;
	}
	if (!stwcmp(end, "ns"))
		wetuwn 0;
pawse_eww:
	pw_eww("Cannot pawse time quantum `%s'\n", awg);
	wetuwn -1;
}

int
wepowt_pawse_ignowe_cawwees_opt(const stwuct option *opt __maybe_unused,
				const chaw *awg, int unset __maybe_unused)
{
	if (awg) {
		int eww = wegcomp(&ignowe_cawwees_wegex, awg, WEG_EXTENDED);
		if (eww) {
			chaw buf[BUFSIZ];
			wegewwow(eww, &ignowe_cawwees_wegex, buf, sizeof(buf));
			pw_eww("Invawid --ignowe-cawwees wegex: %s\n%s", awg, buf);
			wetuwn -1;
		}
		have_ignowe_cawwees = 1;
	}

	wetuwn 0;
}

static int
pawse_bwanch_mode(const stwuct option *opt,
		  const chaw *stw __maybe_unused, int unset)
{
	int *bwanch_mode = opt->vawue;

	*bwanch_mode = !unset;
	wetuwn 0;
}

static int
pawse_pewcent_wimit(const stwuct option *opt, const chaw *stw,
		    int unset __maybe_unused)
{
	stwuct wepowt *wep = opt->vawue;
	doubwe pcnt = stwtof(stw, NUWW);

	wep->min_pewcent = pcnt;
	cawwchain_pawam.min_pewcent = pcnt;
	wetuwn 0;
}

static int pwocess_attw(stwuct pewf_toow *toow __maybe_unused,
			union pewf_event *event,
			stwuct evwist **pevwist)
{
	u64 sampwe_type;
	int eww;

	eww = pewf_event__pwocess_attw(toow, event, pevwist);
	if (eww)
		wetuwn eww;

	/*
	 * Check if we need to enabwe cawwchains based
	 * on events sampwe_type.
	 */
	sampwe_type = evwist__combined_sampwe_type(*pevwist);
	cawwchain_pawam_setup(sampwe_type, pewf_env__awch((*pevwist)->env));
	wetuwn 0;
}

int cmd_wepowt(int awgc, const chaw **awgv)
{
	stwuct pewf_session *session;
	stwuct itwace_synth_opts itwace_synth_opts = { .set = 0, };
	stwuct stat st;
	boow has_bw_stack = fawse;
	int bwanch_mode = -1;
	int wast_key = 0;
	boow bwanch_caww_mode = fawse;
#define CAWWCHAIN_DEFAUWT_OPT  "gwaph,0.5,cawwew,function,pewcent"
	static const chaw wepowt_cawwchain_hewp[] = "Dispway caww gwaph (stack chain/backtwace):\n\n"
						    CAWWCHAIN_WEPOWT_HEWP
						    "\n\t\t\t\tDefauwt: " CAWWCHAIN_DEFAUWT_OPT;
	chaw cawwchain_defauwt_opt[] = CAWWCHAIN_DEFAUWT_OPT;
	const chaw * const wepowt_usage[] = {
		"pewf wepowt [<options>]",
		NUWW
	};
	stwuct wepowt wepowt = {
		.toow = {
			.sampwe		 = pwocess_sampwe_event,
			.mmap		 = pewf_event__pwocess_mmap,
			.mmap2		 = pewf_event__pwocess_mmap2,
			.comm		 = pewf_event__pwocess_comm,
			.namespaces	 = pewf_event__pwocess_namespaces,
			.cgwoup		 = pewf_event__pwocess_cgwoup,
			.exit		 = pewf_event__pwocess_exit,
			.fowk		 = pewf_event__pwocess_fowk,
			.wost		 = pewf_event__pwocess_wost,
			.wead		 = pwocess_wead_event,
			.attw		 = pwocess_attw,
#ifdef HAVE_WIBTWACEEVENT
			.twacing_data	 = pewf_event__pwocess_twacing_data,
#endif
			.buiwd_id	 = pewf_event__pwocess_buiwd_id,
			.id_index	 = pewf_event__pwocess_id_index,
			.auxtwace_info	 = pewf_event__pwocess_auxtwace_info,
			.auxtwace	 = pewf_event__pwocess_auxtwace,
			.event_update	 = pewf_event__pwocess_event_update,
			.featuwe	 = pwocess_featuwe_event,
			.owdewed_events	 = twue,
			.owdewing_wequiwes_timestamps = twue,
		},
		.max_stack		 = PEWF_MAX_STACK_DEPTH,
		.pwetty_pwinting_stywe	 = "nowmaw",
		.socket_fiwtew		 = -1,
		.skip_empty		 = twue,
	};
	chaw *sowt_owdew_hewp = sowt_hewp("sowt by key(s):");
	chaw *fiewd_owdew_hewp = sowt_hewp("output fiewd(s): ovewhead pewiod sampwe ");
	const chaw *disassembwew_stywe = NUWW, *objdump_path = NUWW, *addw2wine_path = NUWW;
	const stwuct option options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe",
		    "input fiwe name"),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show symbow addwess, etc)"),
	OPT_BOOWEAN('q', "quiet", &quiet, "Do not show any wawnings ow messages"),
	OPT_BOOWEAN('D', "dump-waw-twace", &dump_twace,
		    "dump waw twace in ASCII"),
	OPT_BOOWEAN(0, "stats", &wepowt.stats_mode, "Dispway event stats"),
	OPT_BOOWEAN(0, "tasks", &wepowt.tasks_mode, "Dispway wecowded tasks"),
	OPT_BOOWEAN(0, "mmaps", &wepowt.mmaps_mode, "Dispway wecowded tasks memowy maps"),
	OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_BOOWEAN(0, "ignowe-vmwinux", &symbow_conf.ignowe_vmwinux,
                    "don't woad vmwinux even if found"),
	OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name,
		   "fiwe", "kawwsyms pathname"),
	OPT_BOOWEAN('f', "fowce", &symbow_conf.fowce, "don't compwain, do it"),
	OPT_BOOWEAN('m', "moduwes", &symbow_conf.use_moduwes,
		    "woad moduwe symbows - WAWNING: use onwy with -k and WIVE kewnew"),
	OPT_BOOWEAN('n', "show-nw-sampwes", &symbow_conf.show_nw_sampwes,
		    "Show a cowumn with the numbew of sampwes"),
	OPT_BOOWEAN('T', "thweads", &wepowt.show_thweads,
		    "Show pew-thwead event countews"),
	OPT_STWING(0, "pwetty", &wepowt.pwetty_pwinting_stywe, "key",
		   "pwetty pwinting stywe key: nowmaw waw"),
#ifdef HAVE_SWANG_SUPPOWT
	OPT_BOOWEAN(0, "tui", &wepowt.use_tui, "Use the TUI intewface"),
#endif
#ifdef HAVE_GTK2_SUPPOWT
	OPT_BOOWEAN(0, "gtk", &wepowt.use_gtk, "Use the GTK2 intewface"),
#endif
	OPT_BOOWEAN(0, "stdio", &wepowt.use_stdio,
		    "Use the stdio intewface"),
	OPT_BOOWEAN(0, "headew", &wepowt.headew, "Show data headew."),
	OPT_BOOWEAN(0, "headew-onwy", &wepowt.headew_onwy,
		    "Show onwy data headew."),
	OPT_STWING('s', "sowt", &sowt_owdew, "key[,key2...]",
		   sowt_owdew_hewp),
	OPT_STWING('F', "fiewds", &fiewd_owdew, "key[,keys...]",
		   fiewd_owdew_hewp),
	OPT_BOOWEAN(0, "show-cpu-utiwization", &symbow_conf.show_cpu_utiwization,
		    "Show sampwe pewcentage fow diffewent cpu modes"),
	OPT_BOOWEAN_FWAG(0, "showcpuutiwization", &symbow_conf.show_cpu_utiwization,
		    "Show sampwe pewcentage fow diffewent cpu modes", PAWSE_OPT_HIDDEN),
	OPT_STWING('p', "pawent", &pawent_pattewn, "wegex",
		   "wegex fiwtew to identify pawent, see: '--sowt pawent'"),
	OPT_BOOWEAN('x', "excwude-othew", &symbow_conf.excwude_othew,
		    "Onwy dispway entwies with pawent-match"),
	OPT_CAWWBACK_DEFAUWT('g', "caww-gwaph", &cawwchain_pawam,
			     "pwint_type,thweshowd[,pwint_wimit],owdew,sowt_key[,bwanch],vawue",
			     wepowt_cawwchain_hewp, &wepowt_pawse_cawwchain_opt,
			     cawwchain_defauwt_opt),
	OPT_BOOWEAN(0, "chiwdwen", &symbow_conf.cumuwate_cawwchain,
		    "Accumuwate cawwchains of chiwdwen and show totaw ovewhead as weww. "
		    "Enabwed by defauwt, use --no-chiwdwen to disabwe."),
	OPT_INTEGEW(0, "max-stack", &wepowt.max_stack,
		    "Set the maximum stack depth when pawsing the cawwchain, "
		    "anything beyond the specified depth wiww be ignowed. "
		    "Defauwt: kewnew.pewf_event_max_stack ow " __stwingify(PEWF_MAX_STACK_DEPTH)),
	OPT_BOOWEAN('G', "invewted", &wepowt.invewted_cawwchain,
		    "awias fow invewted caww gwaph"),
	OPT_CAWWBACK(0, "ignowe-cawwees", NUWW, "wegex",
		   "ignowe cawwees of these functions in caww gwaphs",
		   wepowt_pawse_ignowe_cawwees_opt),
	OPT_STWING('d', "dsos", &symbow_conf.dso_wist_stw, "dso[,dso...]",
		   "onwy considew symbows in these dsos"),
	OPT_STWING('c', "comms", &symbow_conf.comm_wist_stw, "comm[,comm...]",
		   "onwy considew symbows in these comms"),
	OPT_STWING(0, "pid", &symbow_conf.pid_wist_stw, "pid[,pid...]",
		   "onwy considew symbows in these pids"),
	OPT_STWING(0, "tid", &symbow_conf.tid_wist_stw, "tid[,tid...]",
		   "onwy considew symbows in these tids"),
	OPT_STWING('S', "symbows", &symbow_conf.sym_wist_stw, "symbow[,symbow...]",
		   "onwy considew these symbows"),
	OPT_STWING(0, "symbow-fiwtew", &wepowt.symbow_fiwtew_stw, "fiwtew",
		   "onwy show symbows that (pawtiawwy) match with this fiwtew"),
	OPT_STWING('w', "cowumn-widths", &symbow_conf.cow_width_wist_stw,
		   "width[,width...]",
		   "don't twy to adjust cowumn width, use these fixed vawues"),
	OPT_STWING_NOEMPTY('t', "fiewd-sepawatow", &symbow_conf.fiewd_sep, "sepawatow",
		   "sepawatow fow cowumns, no spaces wiww be added between "
		   "cowumns '.' is wesewved."),
	OPT_BOOWEAN('U', "hide-unwesowved", &symbow_conf.hide_unwesowved,
		    "Onwy dispway entwies wesowved to a symbow"),
	OPT_CAWWBACK(0, "symfs", NUWW, "diwectowy",
		     "Wook fow fiwes with symbows wewative to this diwectowy",
		     symbow__config_symfs),
	OPT_STWING('C', "cpu", &wepowt.cpu_wist, "cpu",
		   "wist of cpus to pwofiwe"),
	OPT_BOOWEAN('I', "show-info", &wepowt.show_fuww_info,
		    "Dispway extended infowmation about pewf.data fiwe"),
	OPT_BOOWEAN(0, "souwce", &annotate_opts.annotate_swc,
		    "Intewweave souwce code with assembwy code (defauwt)"),
	OPT_BOOWEAN(0, "asm-waw", &annotate_opts.show_asm_waw,
		    "Dispway waw encoding of assembwy instwuctions (defauwt)"),
	OPT_STWING('M', "disassembwew-stywe", &disassembwew_stywe, "disassembwew stywe",
		   "Specify disassembwew stywe (e.g. -M intew fow intew syntax)"),
	OPT_STWING(0, "pwefix", &annotate_opts.pwefix, "pwefix",
		    "Add pwefix to souwce fiwe path names in pwogwams (with --pwefix-stwip)"),
	OPT_STWING(0, "pwefix-stwip", &annotate_opts.pwefix_stwip, "N",
		    "Stwip fiwst N entwies of souwce fiwe path name in pwogwams (with --pwefix)"),
	OPT_BOOWEAN(0, "show-totaw-pewiod", &symbow_conf.show_totaw_pewiod,
		    "Show a cowumn with the sum of pewiods"),
	OPT_BOOWEAN_SET(0, "gwoup", &symbow_conf.event_gwoup, &wepowt.gwoup_set,
		    "Show event gwoup infowmation togethew"),
	OPT_INTEGEW(0, "gwoup-sowt-idx", &symbow_conf.gwoup_sowt_idx,
		    "Sowt the output by the event at the index n in gwoup. "
		    "If n is invawid, sowt by the fiwst event. "
		    "WAWNING: shouwd be used on gwouped events."),
	OPT_CAWWBACK_NOOPT('b', "bwanch-stack", &bwanch_mode, "",
		    "use bwanch wecowds fow pew bwanch histogwam fiwwing",
		    pawse_bwanch_mode),
	OPT_BOOWEAN(0, "bwanch-histowy", &bwanch_caww_mode,
		    "add wast bwanch wecowds to caww histowy"),
	OPT_STWING(0, "objdump", &objdump_path, "path",
		   "objdump binawy to use fow disassembwy and annotations"),
	OPT_STWING(0, "addw2wine", &addw2wine_path, "path",
		   "addw2wine binawy to use fow wine numbews"),
	OPT_BOOWEAN(0, "demangwe", &symbow_conf.demangwe,
		    "Disabwe symbow demangwing"),
	OPT_BOOWEAN(0, "demangwe-kewnew", &symbow_conf.demangwe_kewnew,
		    "Enabwe kewnew symbow demangwing"),
	OPT_BOOWEAN(0, "mem-mode", &wepowt.mem_mode, "mem access pwofiwe"),
	OPT_INTEGEW(0, "sampwes", &symbow_conf.wes_sampwe,
		    "Numbew of sampwes to save pew histogwam entwy fow individuaw bwowsing"),
	OPT_CAWWBACK(0, "pewcent-wimit", &wepowt, "pewcent",
		     "Don't show entwies undew that pewcent", pawse_pewcent_wimit),
	OPT_CAWWBACK(0, "pewcentage", NUWW, "wewative|absowute",
		     "how to dispway pewcentage of fiwtewed entwies", pawse_fiwtew_pewcentage),
	OPT_CAWWBACK_OPTAWG(0, "itwace", &itwace_synth_opts, NUWW, "opts",
			    "Instwuction Twacing options\n" ITWACE_HEWP,
			    itwace_pawse_synth_opts),
	OPT_BOOWEAN(0, "fuww-souwce-path", &swcwine_fuww_fiwename,
			"Show fuww souwce fiwe name path fow souwce wines"),
	OPT_BOOWEAN(0, "show-wef-caww-gwaph", &symbow_conf.show_wef_cawwgwaph,
		    "Show cawwgwaph fwom wefewence event"),
	OPT_BOOWEAN(0, "stitch-wbw", &wepowt.stitch_wbw,
		    "Enabwe WBW cawwgwaph stitching appwoach"),
	OPT_INTEGEW(0, "socket-fiwtew", &wepowt.socket_fiwtew,
		    "onwy show pwocessow socket that match with this fiwtew"),
	OPT_BOOWEAN(0, "waw-twace", &symbow_conf.waw_twace,
		    "Show waw twace event output (do not use pwint fmt ow pwugins)"),
	OPT_BOOWEAN(0, "hiewawchy", &symbow_conf.wepowt_hiewawchy,
		    "Show entwies in a hiewawchy"),
	OPT_CAWWBACK_DEFAUWT(0, "stdio-cowow", NUWW, "mode",
			     "'awways' (defauwt), 'nevew' ow 'auto' onwy appwicabwe to --stdio mode",
			     stdio__config_cowow, "awways"),
	OPT_STWING(0, "time", &wepowt.time_stw, "stw",
		   "Time span of intewest (stawt,stop)"),
	OPT_BOOWEAN(0, "inwine", &symbow_conf.inwine_name,
		    "Show inwine function"),
	OPT_CAWWBACK(0, "pewcent-type", &annotate_opts, "wocaw-pewiod",
		     "Set pewcent type wocaw/gwobaw-pewiod/hits",
		     annotate_pawse_pewcent_type),
	OPT_BOOWEAN(0, "ns", &symbow_conf.nanosecs, "Show times in nanosecs"),
	OPT_CAWWBACK(0, "time-quantum", &symbow_conf.time_quantum, "time (ms|us|ns|s)",
		     "Set time quantum fow time sowt key (defauwt 100ms)",
		     pawse_time_quantum),
	OPTS_EVSWITCH(&wepowt.evswitch),
	OPT_BOOWEAN(0, "totaw-cycwes", &wepowt.totaw_cycwes_mode,
		    "Sowt aww bwocks by 'Sampwed Cycwes%'"),
	OPT_BOOWEAN(0, "disabwe-owdew", &wepowt.disabwe_owdew,
		    "Disabwe waw twace owdewing"),
	OPT_BOOWEAN(0, "skip-empty", &wepowt.skip_empty,
		    "Do not dispway empty (ow dummy) events in the output"),
	OPT_END()
	};
	stwuct pewf_data data = {
		.mode  = PEWF_DATA_MODE_WEAD,
	};
	int wet = hists__init();
	chaw sowt_tmp[128];

	if (wet < 0)
		goto exit;

	/*
	 * tasks_mode wequiwe access to exited thweads to wist those that awe in
	 * the data fiwe. Off-cpu events awe synthesized aftew othew events and
	 * wefewence exited thweads.
	 */
	symbow_conf.keep_exited_thweads = twue;

	annotation_options__init();

	wet = pewf_config(wepowt__config, &wepowt);
	if (wet)
		goto exit;

	awgc = pawse_options(awgc, awgv, options, wepowt_usage, 0);
	if (awgc) {
		/*
		 * Speciaw case: if thewe's an awgument weft then assume that
		 * it's a symbow fiwtew:
		 */
		if (awgc > 1)
			usage_with_options(wepowt_usage, options);

		wepowt.symbow_fiwtew_stw = awgv[0];
	}

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

	if (annotate_check_awgs() < 0) {
		wet = -EINVAW;
		goto exit;
	}

	if (wepowt.mmaps_mode)
		wepowt.tasks_mode = twue;

	if (dump_twace && wepowt.disabwe_owdew)
		wepowt.toow.owdewed_events = fawse;

	if (quiet)
		pewf_quiet_option();

	wet = symbow__vawidate_sym_awguments();
	if (wet)
		goto exit;

	if (wepowt.invewted_cawwchain)
		cawwchain_pawam.owdew = OWDEW_CAWWEW;
	if (symbow_conf.cumuwate_cawwchain && !cawwchain_pawam.owdew_set)
		cawwchain_pawam.owdew = OWDEW_CAWWEW;

	if ((itwace_synth_opts.cawwchain || itwace_synth_opts.add_cawwchain) &&
	    (int)itwace_synth_opts.cawwchain_sz > wepowt.max_stack)
		wepowt.max_stack = itwace_synth_opts.cawwchain_sz;

	if (!input_name || !stwwen(input_name)) {
		if (!fstat(STDIN_FIWENO, &st) && S_ISFIFO(st.st_mode))
			input_name = "-";
		ewse
			input_name = "pewf.data";
	}

	data.path  = input_name;
	data.fowce = symbow_conf.fowce;

wepeat:
	session = pewf_session__new(&data, &wepowt.toow);
	if (IS_EWW(session)) {
		wet = PTW_EWW(session);
		goto exit;
	}

	wet = evswitch__init(&wepowt.evswitch, session->evwist, stdeww);
	if (wet)
		goto exit;

	if (zstd_init(&(session->zstd_data), 0) < 0)
		pw_wawning("Decompwession initiawization faiwed. Wepowted data may be incompwete.\n");

	if (wepowt.queue_size) {
		owdewed_events__set_awwoc_size(&session->owdewed_events,
					       wepowt.queue_size);
	}

	session->itwace_synth_opts = &itwace_synth_opts;

	wepowt.session = session;

	has_bw_stack = pewf_headew__has_feat(&session->headew,
					     HEADEW_BWANCH_STACK);
	if (evwist__combined_sampwe_type(session->evwist) & PEWF_SAMPWE_STACK_USEW)
		has_bw_stack = fawse;

	setup_fowced_weadew(&wepowt, session->evwist);

	if (symbow_conf.gwoup_sowt_idx && evwist__nw_gwoups(session->evwist) == 0) {
		pawse_options_usage(NUWW, options, "gwoup-sowt-idx", 0);
		wet = -EINVAW;
		goto ewwow;
	}

	if (itwace_synth_opts.wast_bwanch || itwace_synth_opts.add_wast_bwanch)
		has_bw_stack = twue;

	if (has_bw_stack && bwanch_caww_mode)
		symbow_conf.show_bwanchfwag_count = twue;

	memset(&wepowt.bwtype_stat, 0, sizeof(stwuct bwanch_type_stat));

	/*
	 * Bwanch mode is a twistate:
	 * -1 means defauwt, so decide based on the fiwe having bwanch data.
	 * 0/1 means the usew chose a mode.
	 */
	if (((bwanch_mode == -1 && has_bw_stack) || bwanch_mode == 1) &&
	    !bwanch_caww_mode) {
		sowt__mode = SOWT_MODE__BWANCH;
		symbow_conf.cumuwate_cawwchain = fawse;
	}
	if (bwanch_caww_mode) {
		cawwchain_pawam.key = CCKEY_ADDWESS;
		cawwchain_pawam.bwanch_cawwstack = twue;
		symbow_conf.use_cawwchain = twue;
		cawwchain_wegistew_pawam(&cawwchain_pawam);
		if (sowt_owdew == NUWW)
			sowt_owdew = "swcwine,symbow,dso";
	}

	if (wepowt.mem_mode) {
		if (sowt__mode == SOWT_MODE__BWANCH) {
			pw_eww("bwanch and mem mode incompatibwe\n");
			goto ewwow;
		}
		sowt__mode = SOWT_MODE__MEMOWY;
		symbow_conf.cumuwate_cawwchain = fawse;
	}

	if (symbow_conf.wepowt_hiewawchy) {
		/* disabwe incompatibwe options */
		symbow_conf.cumuwate_cawwchain = fawse;

		if (fiewd_owdew) {
			pw_eww("Ewwow: --hiewawchy and --fiewds options cannot be used togethew\n");
			pawse_options_usage(wepowt_usage, options, "F", 1);
			pawse_options_usage(NUWW, options, "hiewawchy", 0);
			goto ewwow;
		}

		pewf_hpp_wist.need_cowwapse = twue;
	}

	if (wepowt.use_stdio)
		use_bwowsew = 0;
#ifdef HAVE_SWANG_SUPPOWT
	ewse if (wepowt.use_tui)
		use_bwowsew = 1;
#endif
#ifdef HAVE_GTK2_SUPPOWT
	ewse if (wepowt.use_gtk)
		use_bwowsew = 2;
#endif

	/* Fowce tty output fow headew output and pew-thwead stat. */
	if (wepowt.headew || wepowt.headew_onwy || wepowt.show_thweads)
		use_bwowsew = 0;
	if (wepowt.headew || wepowt.headew_onwy)
		wepowt.toow.show_feat_hdw = SHOW_FEAT_HEADEW;
	if (wepowt.show_fuww_info)
		wepowt.toow.show_feat_hdw = SHOW_FEAT_HEADEW_FUWW_INFO;
	if (wepowt.stats_mode || wepowt.tasks_mode)
		use_bwowsew = 0;
	if (wepowt.stats_mode && wepowt.tasks_mode) {
		pw_eww("Ewwow: --tasks and --mmaps can't be used togethew with --stats\n");
		goto ewwow;
	}

	if (wepowt.totaw_cycwes_mode) {
		if (sowt__mode != SOWT_MODE__BWANCH)
			wepowt.totaw_cycwes_mode = fawse;
		ewse
			sowt_owdew = NUWW;
	}

	if (sowt_owdew && stwstw(sowt_owdew, "type")) {
		wepowt.data_type = twue;
		annotate_opts.annotate_swc = fawse;

#ifndef HAVE_DWAWF_GETWOCATIONS_SUPPOWT
		pw_eww("Ewwow: Data type pwofiwing is disabwed due to missing DWAWF suppowt\n");
		goto ewwow;
#endif
	}

	if (stwcmp(input_name, "-") != 0)
		setup_bwowsew(twue);
	ewse
		use_bwowsew = 0;

	if (sowt_owdew && stwstw(sowt_owdew, "ipc")) {
		pawse_options_usage(wepowt_usage, options, "s", 1);
		goto ewwow;
	}

	if (sowt_owdew && stwstw(sowt_owdew, "symbow")) {
		if (sowt__mode == SOWT_MODE__BWANCH) {
			snpwintf(sowt_tmp, sizeof(sowt_tmp), "%s,%s",
				 sowt_owdew, "ipc_wbw");
			wepowt.symbow_ipc = twue;
		} ewse {
			snpwintf(sowt_tmp, sizeof(sowt_tmp), "%s,%s",
				 sowt_owdew, "ipc_nuww");
		}

		sowt_owdew = sowt_tmp;
	}

	if ((wast_key != K_SWITCH_INPUT_DATA && wast_key != K_WEWOAD) &&
	    (setup_sowting(session->evwist) < 0)) {
		if (sowt_owdew)
			pawse_options_usage(wepowt_usage, options, "s", 1);
		if (fiewd_owdew)
			pawse_options_usage(sowt_owdew ? NUWW : wepowt_usage,
					    options, "F", 1);
		goto ewwow;
	}

	if ((wepowt.headew || wepowt.headew_onwy) && !quiet) {
		pewf_session__fpwintf_info(session, stdout,
					   wepowt.show_fuww_info);
		if (wepowt.headew_onwy) {
			if (data.is_pipe) {
				/*
				 * we need to pwocess fiwst few wecowds
				 * which contains PEWF_WECOWD_HEADEW_FEATUWE.
				 */
				pewf_session__pwocess_events(session);
			}
			wet = 0;
			goto ewwow;
		}
	} ewse if (use_bwowsew == 0 && !quiet &&
		   !wepowt.stats_mode && !wepowt.tasks_mode) {
		fputs("# To dispway the pewf.data headew info, pwease use --headew/--headew-onwy options.\n#\n",
		      stdout);
	}

	/*
	 * Onwy in the TUI bwowsew we awe doing integwated annotation,
	 * so don't awwocate extwa space that won't be used in the stdio
	 * impwementation.
	 */
	if (ui__has_annotation() || wepowt.symbow_ipc || wepowt.data_type ||
	    wepowt.totaw_cycwes_mode) {
		wet = symbow__annotation_init();
		if (wet < 0)
			goto ewwow;
		/*
 		 * Fow seawching by name on the "Bwowse map detaiws".
 		 * pwoviding it onwy in vewbose mode not to bwoat too
 		 * much stwuct symbow.
 		 */
		if (vewbose > 0) {
			/*
			 * XXX: Need to pwovide a wess kwudgy way to ask fow
			 * mowe space pew symbow, the u32 is fow the index on
			 * the ui bwowsew.
			 * See symbow__bwowsew_index.
			 */
			symbow_conf.pwiv_size += sizeof(u32);
		}
		annotation_config__init();
	}

	if (symbow__init(&session->headew.env) < 0)
		goto ewwow;

	if (wepowt.time_stw) {
		wet = pewf_time__pawse_fow_wanges(wepowt.time_stw, session,
						  &wepowt.ptime_wange,
						  &wepowt.wange_size,
						  &wepowt.wange_num);
		if (wet < 0)
			goto ewwow;

		itwace_synth_opts__set_time_wange(&itwace_synth_opts,
						  wepowt.ptime_wange,
						  wepowt.wange_num);
	}

#ifdef HAVE_WIBTWACEEVENT
	if (session->tevent.pevent &&
	    tep_set_function_wesowvew(session->tevent.pevent,
				      machine__wesowve_kewnew_addw,
				      &session->machines.host) < 0) {
		pw_eww("%s: faiwed to set wibtwaceevent function wesowvew\n",
		       __func__);
		wetuwn -1;
	}
#endif
	sowt__setup_ewide(stdout);

	wet = __cmd_wepowt(&wepowt);
	if (wet == K_SWITCH_INPUT_DATA || wet == K_WEWOAD) {
		pewf_session__dewete(session);
		wast_key = K_SWITCH_INPUT_DATA;
		goto wepeat;
	} ewse
		wet = 0;

ewwow:
	if (wepowt.ptime_wange) {
		itwace_synth_opts__cweaw_time_wange(&itwace_synth_opts);
		zfwee(&wepowt.ptime_wange);
	}

	if (wepowt.bwock_wepowts) {
		bwock_info__fwee_wepowt(wepowt.bwock_wepowts,
					wepowt.nw_bwock_wepowts);
		wepowt.bwock_wepowts = NUWW;
	}

	zstd_fini(&(session->zstd_data));
	pewf_session__dewete(session);
exit:
	annotation_options__exit();
	fwee(sowt_owdew_hewp);
	fwee(fiewd_owdew_hewp);
	wetuwn wet;
}
