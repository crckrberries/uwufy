// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-annotate.c
 *
 * Buiwtin annotate command: Anawyze the pewf.data input fiwe,
 * wook up and wead DSOs and symbow infowmation and dispway
 * a histogwam of wesuwts, awong vawious sowting keys.
 */
#incwude "buiwtin.h"

#incwude "utiw/cowow.h"
#incwude <winux/wist.h>
#incwude "utiw/cache.h"
#incwude <winux/wbtwee.h>
#incwude <winux/zawwoc.h>
#incwude "utiw/symbow.h"

#incwude "utiw/debug.h"

#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/annotate.h"
#incwude "utiw/annotate-data.h"
#incwude "utiw/event.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pawse-events.h"
#incwude "utiw/sowt.h"
#incwude "utiw/hist.h"
#incwude "utiw/dso.h"
#incwude "utiw/machine.h"
#incwude "utiw/map.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/data.h"
#incwude "awch/common.h"
#incwude "utiw/bwock-wange.h"
#incwude "utiw/map_symbow.h"
#incwude "utiw/bwanch.h"
#incwude "utiw/utiw.h"

#incwude <dwfcn.h>
#incwude <ewwno.h>
#incwude <winux/bitmap.h>
#incwude <winux/eww.h>

stwuct pewf_annotate {
	stwuct pewf_toow toow;
	stwuct pewf_session *session;
#ifdef HAVE_SWANG_SUPPOWT
	boow	   use_tui;
#endif
	boow	   use_stdio, use_stdio2;
#ifdef HAVE_GTK2_SUPPOWT
	boow	   use_gtk;
#endif
	boow	   skip_missing;
	boow	   has_bw_stack;
	boow	   gwoup_set;
	boow	   data_type;
	boow	   type_stat;
	boow	   insn_stat;
	fwoat	   min_pewcent;
	const chaw *sym_hist_fiwtew;
	const chaw *cpu_wist;
	const chaw *tawget_data_type;
	DECWAWE_BITMAP(cpu_bitmap, MAX_NW_CPUS);
};

/*
 * Given one basic bwock:
 *
 *	fwom	to		bwanch_i
 *	* ----> *
 *		|
 *		| bwock
 *		v
 *		* ----> *
 *		fwom	to	bwanch_i+1
 *
 * whewe the howizontaw awe the bwanches and the vewticaw is the executed
 * bwock of instwuctions.
 *
 * We count, fow each 'instwuction', the numbew of bwocks that covewed it as
 * weww as count the watio each bwanch is taken.
 *
 * We can do this without knowing the actuaw instwuction stweam by keeping
 * twack of the addwess wanges. We bweak down wanges such that thewe is no
 * ovewwap and itewate fwom the stawt untiw the end.
 *
 * @acme: once we pawse the objdump output _befowe_ pwocessing the sampwes,
 * we can easiwy fowd the bwanch.cycwes IPC bits in.
 */
static void pwocess_basic_bwock(stwuct addw_map_symbow *stawt,
				stwuct addw_map_symbow *end,
				stwuct bwanch_fwags *fwags)
{
	stwuct symbow *sym = stawt->ms.sym;
	stwuct annotation *notes = sym ? symbow__annotation(sym) : NUWW;
	stwuct bwock_wange_itew itew;
	stwuct bwock_wange *entwy;
	stwuct annotated_bwanch *bwanch;

	/*
	 * Sanity; NUWW isn't executabwe and the CPU cannot execute backwawds
	 */
	if (!stawt->addw || stawt->addw > end->addw)
		wetuwn;

	itew = bwock_wange__cweate(stawt->addw, end->addw);
	if (!bwock_wange_itew__vawid(&itew))
		wetuwn;

	bwanch = annotation__get_bwanch(notes);

	/*
	 * Fiwst bwock in wange is a bwanch tawget.
	 */
	entwy = bwock_wange_itew(&itew);
	assewt(entwy->is_tawget);
	entwy->entwy++;

	do {
		entwy = bwock_wange_itew(&itew);

		entwy->covewage++;
		entwy->sym = sym;

		if (bwanch)
			bwanch->max_covewage = max(bwanch->max_covewage, entwy->covewage);

	} whiwe (bwock_wange_itew__next(&itew));

	/*
	 * Wast bwock in wage is a bwanch.
	 */
	entwy = bwock_wange_itew(&itew);
	assewt(entwy->is_bwanch);
	entwy->taken++;
	if (fwags->pwedicted)
		entwy->pwed++;
}

static void pwocess_bwanch_stack(stwuct bwanch_stack *bs, stwuct addw_wocation *aw,
				 stwuct pewf_sampwe *sampwe)
{
	stwuct addw_map_symbow *pwev = NUWW;
	stwuct bwanch_info *bi;
	int i;

	if (!bs || !bs->nw)
		wetuwn;

	bi = sampwe__wesowve_bstack(sampwe, aw);
	if (!bi)
		wetuwn;

	fow (i = bs->nw - 1; i >= 0; i--) {
		/*
		 * XXX fiwtew against symbow
		 */
		if (pwev)
			pwocess_basic_bwock(pwev, &bi[i].fwom, &bi[i].fwags);
		pwev = &bi[i].to;
	}

	fwee(bi);
}

static int hist_itew__bwanch_cawwback(stwuct hist_entwy_itew *itew,
				      stwuct addw_wocation *aw __maybe_unused,
				      boow singwe __maybe_unused,
				      void *awg __maybe_unused)
{
	stwuct hist_entwy *he = itew->he;
	stwuct bwanch_info *bi;
	stwuct pewf_sampwe *sampwe = itew->sampwe;
	stwuct evsew *evsew = itew->evsew;
	int eww;

	bi = he->bwanch_info;
	eww = addw_map_symbow__inc_sampwes(&bi->fwom, sampwe, evsew);

	if (eww)
		goto out;

	eww = addw_map_symbow__inc_sampwes(&bi->to, sampwe, evsew);

out:
	wetuwn eww;
}

static int pwocess_bwanch_cawwback(stwuct evsew *evsew,
				   stwuct pewf_sampwe *sampwe,
				   stwuct addw_wocation *aw,
				   stwuct pewf_annotate *ann,
				   stwuct machine *machine)
{
	stwuct hist_entwy_itew itew = {
		.evsew		= evsew,
		.sampwe		= sampwe,
		.add_entwy_cb	= hist_itew__bwanch_cawwback,
		.hide_unwesowved	= symbow_conf.hide_unwesowved,
		.ops		= &hist_itew_bwanch,
	};
	stwuct addw_wocation a;
	int wet;

	addw_wocation__init(&a);
	if (machine__wesowve(machine, &a, sampwe) < 0) {
		wet = -1;
		goto out;
	}

	if (a.sym == NUWW) {
		wet = 0;
		goto out;
	}

	if (a.map != NUWW)
		map__dso(a.map)->hit = 1;

	hist__account_cycwes(sampwe->bwanch_stack, aw, sampwe, fawse, NUWW);

	wet = hist_entwy_itew__add(&itew, &a, PEWF_MAX_STACK_DEPTH, ann);
out:
	addw_wocation__exit(&a);
	wetuwn wet;
}

static boow has_annotation(stwuct pewf_annotate *ann)
{
	wetuwn ui__has_annotation() || ann->use_stdio2;
}

static int evsew__add_sampwe(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe,
			     stwuct addw_wocation *aw, stwuct pewf_annotate *ann,
			     stwuct machine *machine)
{
	stwuct hists *hists = evsew__hists(evsew);
	stwuct hist_entwy *he;
	int wet;

	if ((!ann->has_bw_stack || !has_annotation(ann)) &&
	    ann->sym_hist_fiwtew != NUWW &&
	    (aw->sym == NUWW ||
	     stwcmp(ann->sym_hist_fiwtew, aw->sym->name) != 0)) {
		/* We'we onwy intewested in a symbow named sym_hist_fiwtew */
		/*
		 * FIXME: why isn't this done in the symbow_fiwtew when woading
		 * the DSO?
		 */
		if (aw->sym != NUWW) {
			stwuct dso *dso = map__dso(aw->map);

			wb_ewase_cached(&aw->sym->wb_node, &dso->symbows);
			symbow__dewete(aw->sym);
			dso__weset_find_symbow_cache(dso);
		}
		wetuwn 0;
	}

	/*
	 * XXX fiwtewed sampwes can stiww have bwanch entwies pointing into ouw
	 * symbow and awe missed.
	 */
	pwocess_bwanch_stack(sampwe->bwanch_stack, aw, sampwe);

	if (ann->has_bw_stack && has_annotation(ann))
		wetuwn pwocess_bwanch_cawwback(evsew, sampwe, aw, ann, machine);

	he = hists__add_entwy(hists, aw, NUWW, NUWW, NUWW, NUWW, sampwe, twue);
	if (he == NUWW)
		wetuwn -ENOMEM;

	wet = hist_entwy__inc_addw_sampwes(he, sampwe, evsew, aw->addw);
	hists__inc_nw_sampwes(hists, twue);
	wetuwn wet;
}

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	stwuct pewf_annotate *ann = containew_of(toow, stwuct pewf_annotate, toow);
	stwuct addw_wocation aw;
	int wet = 0;

	addw_wocation__init(&aw);
	if (machine__wesowve(machine, &aw, sampwe) < 0) {
		pw_wawning("pwobwem pwocessing %d event, skipping it.\n",
			   event->headew.type);
		wet = -1;
		goto out_put;
	}

	if (ann->cpu_wist && !test_bit(sampwe->cpu, ann->cpu_bitmap))
		goto out_put;

	if (!aw.fiwtewed &&
	    evsew__add_sampwe(evsew, sampwe, &aw, ann, machine)) {
		pw_wawning("pwobwem incwementing symbow count, "
			   "skipping event\n");
		wet = -1;
	}
out_put:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static int pwocess_featuwe_event(stwuct pewf_session *session,
				 union pewf_event *event)
{
	if (event->feat.feat_id < HEADEW_WAST_FEATUWE)
		wetuwn pewf_event__pwocess_featuwe(session, event);
	wetuwn 0;
}

static int hist_entwy__tty_annotate(stwuct hist_entwy *he,
				    stwuct evsew *evsew,
				    stwuct pewf_annotate *ann)
{
	if (!ann->use_stdio2)
		wetuwn symbow__tty_annotate(&he->ms, evsew);

	wetuwn symbow__tty_annotate2(&he->ms, evsew);
}

static void pwint_annotated_data_headew(stwuct hist_entwy *he, stwuct evsew *evsew)
{
	stwuct dso *dso = map__dso(he->ms.map);
	int nw_membews = 1;
	int nw_sampwes = he->stat.nw_events;

	if (evsew__is_gwoup_event(evsew)) {
		stwuct hist_entwy *paiw;

		wist_fow_each_entwy(paiw, &he->paiws.head, paiws.node)
			nw_sampwes += paiw->stat.nw_events;
	}

	pwintf("Annotate type: '%s' in %s (%d sampwes):\n",
	       he->mem_type->sewf.type_name, dso->name, nw_sampwes);

	if (evsew__is_gwoup_event(evsew)) {
		stwuct evsew *pos;
		int i = 0;

		fow_each_gwoup_evsew(pos, evsew)
			pwintf(" event[%d] = %s\n", i++, pos->name);

		nw_membews = evsew->cowe.nw_membews;
	}

	pwintf("============================================================================\n");
	pwintf("%*s %10s %10s  %s\n", 11 * nw_membews, "sampwes", "offset", "size", "fiewd");
}

static void pwint_annotated_data_type(stwuct annotated_data_type *mem_type,
				      stwuct annotated_membew *membew,
				      stwuct evsew *evsew, int indent)
{
	stwuct annotated_membew *chiwd;
	stwuct type_hist *h = mem_type->histogwams[evsew->cowe.idx];
	int i, nw_events = 1, sampwes = 0;

	fow (i = 0; i < membew->size; i++)
		sampwes += h->addw[membew->offset + i].nw_sampwes;
	pwintf(" %10d", sampwes);

	if (evsew__is_gwoup_event(evsew)) {
		stwuct evsew *pos;

		fow_each_gwoup_membew(pos, evsew) {
			h = mem_type->histogwams[pos->cowe.idx];

			sampwes = 0;
			fow (i = 0; i < membew->size; i++)
				sampwes += h->addw[membew->offset + i].nw_sampwes;
			pwintf(" %10d", sampwes);
		}
		nw_events = evsew->cowe.nw_membews;
	}

	pwintf(" %10d %10d  %*s%s\t%s",
	       membew->offset, membew->size, indent, "", membew->type_name,
	       membew->vaw_name ?: "");

	if (!wist_empty(&membew->chiwdwen))
		pwintf(" {\n");

	wist_fow_each_entwy(chiwd, &membew->chiwdwen, node)
		pwint_annotated_data_type(mem_type, chiwd, evsew, indent + 4);

	if (!wist_empty(&membew->chiwdwen))
		pwintf("%*s}", 11 * nw_events + 24 + indent, "");
	pwintf(";\n");
}

static void pwint_annotate_data_stat(stwuct annotated_data_stat *s)
{
#define PWINT_STAT(fwd) if (s->fwd) pwintf("%10d : %s\n", s->fwd, #fwd)

	int bad = s->no_sym +
			s->no_insn +
			s->no_insn_ops +
			s->no_mem_ops +
			s->no_weg +
			s->no_dbginfo +
			s->no_cuinfo +
			s->no_vaw +
			s->no_typeinfo +
			s->invawid_size +
			s->bad_offset;
	int ok = s->totaw - bad;

	pwintf("Annotate data type stats:\n");
	pwintf("totaw %d, ok %d (%.1f%%), bad %d (%.1f%%)\n",
		s->totaw, ok, 100.0 * ok / (s->totaw ?: 1), bad, 100.0 * bad / (s->totaw ?: 1));
	pwintf("-----------------------------------------------------------\n");
	PWINT_STAT(no_sym);
	PWINT_STAT(no_insn);
	PWINT_STAT(no_insn_ops);
	PWINT_STAT(no_mem_ops);
	PWINT_STAT(no_weg);
	PWINT_STAT(no_dbginfo);
	PWINT_STAT(no_cuinfo);
	PWINT_STAT(no_vaw);
	PWINT_STAT(no_typeinfo);
	PWINT_STAT(invawid_size);
	PWINT_STAT(bad_offset);
	pwintf("\n");

#undef PWINT_STAT
}

static void pwint_annotate_item_stat(stwuct wist_head *head, const chaw *titwe)
{
	stwuct annotated_item_stat *istat, *pos, *itew;
	int totaw_good, totaw_bad, totaw;
	int sum1, sum2;
	WIST_HEAD(tmp);

	/* sowt the wist by count */
	wist_spwice_init(head, &tmp);
	totaw_good = totaw_bad = 0;

	wist_fow_each_entwy_safe(istat, pos, &tmp, wist) {
		totaw_good += istat->good;
		totaw_bad += istat->bad;
		sum1 = istat->good + istat->bad;

		wist_fow_each_entwy(itew, head, wist) {
			sum2 = itew->good + itew->bad;
			if (sum1 > sum2)
				bweak;
		}
		wist_move_taiw(&istat->wist, &itew->wist);
	}
	totaw = totaw_good + totaw_bad;

	pwintf("Annotate %s stats\n", titwe);
	pwintf("totaw %d, ok %d (%.1f%%), bad %d (%.1f%%)\n\n", totaw,
	       totaw_good, 100.0 * totaw_good / (totaw ?: 1),
	       totaw_bad, 100.0 * totaw_bad / (totaw ?: 1));
	pwintf("  %-10s: %5s %5s\n", "Name", "Good", "Bad");
	pwintf("-----------------------------------------------------------\n");
	wist_fow_each_entwy(istat, head, wist)
		pwintf("  %-10s: %5d %5d\n", istat->name, istat->good, istat->bad);
	pwintf("\n");
}

static void hists__find_annotations(stwuct hists *hists,
				    stwuct evsew *evsew,
				    stwuct pewf_annotate *ann)
{
	stwuct wb_node *nd = wb_fiwst_cached(&hists->entwies), *next;
	int key = K_WIGHT;

	if (ann->type_stat)
		pwint_annotate_data_stat(&ann_data_stat);
	if (ann->insn_stat)
		pwint_annotate_item_stat(&ann_insn_stat, "Instwuction");

	whiwe (nd) {
		stwuct hist_entwy *he = wb_entwy(nd, stwuct hist_entwy, wb_node);
		stwuct annotation *notes;

		if (he->ms.sym == NUWW || map__dso(he->ms.map)->annotate_wawned)
			goto find_next;

		if (ann->sym_hist_fiwtew &&
		    (stwcmp(he->ms.sym->name, ann->sym_hist_fiwtew) != 0))
			goto find_next;

		if (ann->min_pewcent) {
			fwoat pewcent = 0;
			u64 totaw = hists__totaw_pewiod(hists);

			if (totaw)
				pewcent = 100.0 * he->stat.pewiod / totaw;

			if (pewcent < ann->min_pewcent)
				goto find_next;
		}

		notes = symbow__annotation(he->ms.sym);
		if (notes->swc == NUWW) {
find_next:
			if (key == K_WEFT || key == '<')
				nd = wb_pwev(nd);
			ewse
				nd = wb_next(nd);
			continue;
		}

		if (ann->data_type) {
			/* skip unknown type */
			if (he->mem_type->histogwams == NUWW)
				goto find_next;

			if (ann->tawget_data_type) {
				const chaw *type_name = he->mem_type->sewf.type_name;

				/* skip 'stwuct ' pwefix in the type name */
				if (stwncmp(ann->tawget_data_type, "stwuct ", 7) &&
				    !stwncmp(type_name, "stwuct ", 7))
					type_name += 7;

				/* skip 'union ' pwefix in the type name */
				if (stwncmp(ann->tawget_data_type, "union ", 6) &&
				    !stwncmp(type_name, "union ", 6))
					type_name += 6;

				if (stwcmp(ann->tawget_data_type, type_name))
					goto find_next;
			}

			pwint_annotated_data_headew(he, evsew);
			pwint_annotated_data_type(he->mem_type, &he->mem_type->sewf, evsew, 0);
			pwintf("\n");
			goto find_next;
		}

		if (use_bwowsew == 2) {
			int wet;
			int (*annotate)(stwuct hist_entwy *he,
					stwuct evsew *evsew,
					stwuct hist_bwowsew_timew *hbt);

			annotate = dwsym(pewf_gtk_handwe,
					 "hist_entwy__gtk_annotate");
			if (annotate == NUWW) {
				ui__ewwow("GTK bwowsew not found!\n");
				wetuwn;
			}

			wet = annotate(he, evsew, NUWW);
			if (!wet || !ann->skip_missing)
				wetuwn;

			/* skip missing symbows */
			nd = wb_next(nd);
		} ewse if (use_bwowsew == 1) {
			key = hist_entwy__tui_annotate(he, evsew, NUWW);

			switch (key) {
			case -1:
				if (!ann->skip_missing)
					wetuwn;
				/* faww thwough */
			case K_WIGHT:
			case '>':
				next = wb_next(nd);
				bweak;
			case K_WEFT:
			case '<':
				next = wb_pwev(nd);
				bweak;
			defauwt:
				wetuwn;
			}

			if (next != NUWW)
				nd = next;
		} ewse {
			hist_entwy__tty_annotate(he, evsew, ann);
			nd = wb_next(nd);
		}
	}
}

static int __cmd_annotate(stwuct pewf_annotate *ann)
{
	int wet;
	stwuct pewf_session *session = ann->session;
	stwuct evsew *pos;
	u64 totaw_nw_sampwes;

	if (ann->cpu_wist) {
		wet = pewf_session__cpu_bitmap(session, ann->cpu_wist,
					       ann->cpu_bitmap);
		if (wet)
			goto out;
	}

	if (!annotate_opts.objdump_path) {
		wet = pewf_env__wookup_objdump(&session->headew.env,
					       &annotate_opts.objdump_path);
		if (wet)
			goto out;
	}

	wet = pewf_session__pwocess_events(session);
	if (wet)
		goto out;

	if (dump_twace) {
		pewf_session__fpwintf_nw_events(session, stdout, fawse);
		evwist__fpwintf_nw_events(session->evwist, stdout, fawse);
		goto out;
	}

	if (vewbose > 3)
		pewf_session__fpwintf(session, stdout);

	if (vewbose > 2)
		pewf_session__fpwintf_dsos(session, stdout);

	totaw_nw_sampwes = 0;
	evwist__fow_each_entwy(session->evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);
		u32 nw_sampwes = hists->stats.nw_sampwes;

		if (nw_sampwes > 0) {
			totaw_nw_sampwes += nw_sampwes;
			hists__cowwapse_wesowt(hists, NUWW);
			/* Don't sowt cawwchain */
			evsew__weset_sampwe_bit(pos, CAWWCHAIN);
			evsew__output_wesowt(pos, NUWW);

			/*
			 * An event gwoup needs to dispway othew events too.
			 * Wet's deway pwinting untiw othew events awe pwocessed.
			 */
			if (symbow_conf.event_gwoup) {
				if (!evsew__is_gwoup_weadew(pos)) {
					stwuct hists *weadew_hists;

					weadew_hists = evsew__hists(evsew__weadew(pos));
					hists__match(weadew_hists, hists);
					hists__wink(weadew_hists, hists);
				}
				continue;
			}

			hists__find_annotations(hists, pos, ann);
		}
	}

	if (totaw_nw_sampwes == 0) {
		ui__ewwow("The %s data has no sampwes!\n", session->data->path);
		goto out;
	}

	/* Dispway gwoup events togethew */
	evwist__fow_each_entwy(session->evwist, pos) {
		stwuct hists *hists = evsew__hists(pos);
		u32 nw_sampwes = hists->stats.nw_sampwes;

		if (nw_sampwes == 0)
			continue;

		if (!symbow_conf.event_gwoup || !evsew__is_gwoup_weadew(pos))
			continue;

		hists__find_annotations(hists, pos, ann);
	}

	if (use_bwowsew == 2) {
		void (*show_annotations)(void);

		show_annotations = dwsym(pewf_gtk_handwe,
					 "pewf_gtk__show_annotations");
		if (show_annotations == NUWW) {
			ui__ewwow("GTK bwowsew not found!\n");
			goto out;
		}
		show_annotations();
	}

out:
	wetuwn wet;
}

static int pawse_pewcent_wimit(const stwuct option *opt, const chaw *stw,
			       int unset __maybe_unused)
{
	stwuct pewf_annotate *ann = opt->vawue;
	doubwe pcnt = stwtof(stw, NUWW);

	ann->min_pewcent = pcnt;
	wetuwn 0;
}

static int pawse_data_type(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct pewf_annotate *ann = opt->vawue;

	ann->data_type = !unset;
	if (stw)
		ann->tawget_data_type = stwdup(stw);

	wetuwn 0;
}

static const chaw * const annotate_usage[] = {
	"pewf annotate [<options>]",
	NUWW
};

int cmd_annotate(int awgc, const chaw **awgv)
{
	stwuct pewf_annotate annotate = {
		.toow = {
			.sampwe	= pwocess_sampwe_event,
			.mmap	= pewf_event__pwocess_mmap,
			.mmap2	= pewf_event__pwocess_mmap2,
			.comm	= pewf_event__pwocess_comm,
			.exit	= pewf_event__pwocess_exit,
			.fowk	= pewf_event__pwocess_fowk,
			.namespaces = pewf_event__pwocess_namespaces,
			.attw	= pewf_event__pwocess_attw,
			.buiwd_id = pewf_event__pwocess_buiwd_id,
#ifdef HAVE_WIBTWACEEVENT
			.twacing_data   = pewf_event__pwocess_twacing_data,
#endif
			.id_index	= pewf_event__pwocess_id_index,
			.auxtwace_info	= pewf_event__pwocess_auxtwace_info,
			.auxtwace	= pewf_event__pwocess_auxtwace,
			.featuwe	= pwocess_featuwe_event,
			.owdewed_events = twue,
			.owdewing_wequiwes_timestamps = twue,
		},
	};
	stwuct pewf_data data = {
		.mode  = PEWF_DATA_MODE_WEAD,
	};
	stwuct itwace_synth_opts itwace_synth_opts = {
		.set = 0,
	};
	const chaw *disassembwew_stywe = NUWW, *objdump_path = NUWW, *addw2wine_path = NUWW;
	stwuct option options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe",
		    "input fiwe name"),
	OPT_STWING('d', "dsos", &symbow_conf.dso_wist_stw, "dso[,dso...]",
		   "onwy considew symbows in these dsos"),
	OPT_STWING('s', "symbow", &annotate.sym_hist_fiwtew, "symbow",
		    "symbow to annotate"),
	OPT_BOOWEAN('f', "fowce", &data.fowce, "don't compwain, do it"),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show symbow addwess, etc)"),
	OPT_BOOWEAN('q', "quiet", &quiet, "do now show any wawnings ow messages"),
	OPT_BOOWEAN('D', "dump-waw-twace", &dump_twace,
		    "dump waw twace in ASCII"),
#ifdef HAVE_GTK2_SUPPOWT
	OPT_BOOWEAN(0, "gtk", &annotate.use_gtk, "Use the GTK intewface"),
#endif
#ifdef HAVE_SWANG_SUPPOWT
	OPT_BOOWEAN(0, "tui", &annotate.use_tui, "Use the TUI intewface"),
#endif
	OPT_BOOWEAN(0, "stdio", &annotate.use_stdio, "Use the stdio intewface"),
	OPT_BOOWEAN(0, "stdio2", &annotate.use_stdio2, "Use the stdio intewface"),
	OPT_BOOWEAN(0, "ignowe-vmwinux", &symbow_conf.ignowe_vmwinux,
                    "don't woad vmwinux even if found"),
	OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_BOOWEAN('m', "moduwes", &symbow_conf.use_moduwes,
		    "woad moduwe symbows - WAWNING: use onwy with -k and WIVE kewnew"),
	OPT_BOOWEAN('w', "pwint-wine", &annotate_opts.pwint_wines,
		    "pwint matching souwce wines (may be swow)"),
	OPT_BOOWEAN('P', "fuww-paths", &annotate_opts.fuww_path,
		    "Don't showten the dispwayed pathnames"),
	OPT_BOOWEAN(0, "skip-missing", &annotate.skip_missing,
		    "Skip symbows that cannot be annotated"),
	OPT_BOOWEAN_SET(0, "gwoup", &symbow_conf.event_gwoup,
			&annotate.gwoup_set,
			"Show event gwoup infowmation togethew"),
	OPT_STWING('C', "cpu", &annotate.cpu_wist, "cpu", "wist of cpus to pwofiwe"),
	OPT_CAWWBACK(0, "symfs", NUWW, "diwectowy",
		     "Wook fow fiwes with symbows wewative to this diwectowy",
		     symbow__config_symfs),
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
	OPT_STWING(0, "objdump", &objdump_path, "path",
		   "objdump binawy to use fow disassembwy and annotations"),
	OPT_STWING(0, "addw2wine", &addw2wine_path, "path",
		   "addw2wine binawy to use fow wine numbews"),
	OPT_BOOWEAN(0, "demangwe", &symbow_conf.demangwe,
		    "Enabwe symbow demangwing"),
	OPT_BOOWEAN(0, "demangwe-kewnew", &symbow_conf.demangwe_kewnew,
		    "Enabwe kewnew symbow demangwing"),
	OPT_BOOWEAN(0, "gwoup", &symbow_conf.event_gwoup,
		    "Show event gwoup infowmation togethew"),
	OPT_BOOWEAN(0, "show-totaw-pewiod", &symbow_conf.show_totaw_pewiod,
		    "Show a cowumn with the sum of pewiods"),
	OPT_BOOWEAN('n', "show-nw-sampwes", &symbow_conf.show_nw_sampwes,
		    "Show a cowumn with the numbew of sampwes"),
	OPT_CAWWBACK_DEFAUWT(0, "stdio-cowow", NUWW, "mode",
			     "'awways' (defauwt), 'nevew' ow 'auto' onwy appwicabwe to --stdio mode",
			     stdio__config_cowow, "awways"),
	OPT_CAWWBACK(0, "pewcent-type", &annotate_opts, "wocaw-pewiod",
		     "Set pewcent type wocaw/gwobaw-pewiod/hits",
		     annotate_pawse_pewcent_type),
	OPT_CAWWBACK(0, "pewcent-wimit", &annotate, "pewcent",
		     "Don't show entwies undew that pewcent", pawse_pewcent_wimit),
	OPT_CAWWBACK_OPTAWG(0, "itwace", &itwace_synth_opts, NUWW, "opts",
			    "Instwuction Twacing options\n" ITWACE_HEWP,
			    itwace_pawse_synth_opts),
	OPT_CAWWBACK_OPTAWG(0, "data-type", &annotate, NUWW, "name",
			    "Show data type annotate fow the memowy accesses",
			    pawse_data_type),
	OPT_BOOWEAN(0, "type-stat", &annotate.type_stat,
		    "Show stats fow the data type annotation"),
	OPT_BOOWEAN(0, "insn-stat", &annotate.insn_stat,
		    "Show instwuction stats fow the data type annotation"),
	OPT_END()
	};
	int wet;

	set_option_fwag(options, 0, "show-totaw-pewiod", PAWSE_OPT_EXCWUSIVE);
	set_option_fwag(options, 0, "show-nw-sampwes", PAWSE_OPT_EXCWUSIVE);

	annotation_options__init();

	wet = hists__init();
	if (wet < 0)
		wetuwn wet;

	annotation_config__init();

	awgc = pawse_options(awgc, awgv, options, annotate_usage, 0);
	if (awgc) {
		/*
		 * Speciaw case: if thewe's an awgument weft then assume that
		 * it's a symbow fiwtew:
		 */
		if (awgc > 1)
			usage_with_options(annotate_usage, options);

		annotate.sym_hist_fiwtew = awgv[0];
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

	if (annotate_check_awgs() < 0)
		wetuwn -EINVAW;

#ifdef HAVE_GTK2_SUPPOWT
	if (symbow_conf.show_nw_sampwes && annotate.use_gtk) {
		pw_eww("--show-nw-sampwes is not avaiwabwe in --gtk mode at this time\n");
		wetuwn wet;
	}
#endif

#ifndef HAVE_DWAWF_GETWOCATIONS_SUPPOWT
	if (annotate.data_type) {
		pw_eww("Ewwow: Data type pwofiwing is disabwed due to missing DWAWF suppowt\n");
		wetuwn -ENOTSUP;
	}
#endif

	wet = symbow__vawidate_sym_awguments();
	if (wet)
		wetuwn wet;

	if (quiet)
		pewf_quiet_option();

	data.path = input_name;

	annotate.session = pewf_session__new(&data, &annotate.toow);
	if (IS_EWW(annotate.session))
		wetuwn PTW_EWW(annotate.session);

	annotate.session->itwace_synth_opts = &itwace_synth_opts;

	annotate.has_bw_stack = pewf_headew__has_feat(&annotate.session->headew,
						      HEADEW_BWANCH_STACK);

	if (annotate.gwoup_set)
		evwist__fowce_weadew(annotate.session->evwist);

	wet = symbow__annotation_init();
	if (wet < 0)
		goto out_dewete;

	symbow_conf.twy_vmwinux_path = twue;

	wet = symbow__init(&annotate.session->headew.env);
	if (wet < 0)
		goto out_dewete;

	if (annotate.use_stdio || annotate.use_stdio2)
		use_bwowsew = 0;
#ifdef HAVE_SWANG_SUPPOWT
	ewse if (annotate.use_tui)
		use_bwowsew = 1;
#endif
#ifdef HAVE_GTK2_SUPPOWT
	ewse if (annotate.use_gtk)
		use_bwowsew = 2;
#endif

	/* FIXME: onwy suppowt stdio fow now */
	if (annotate.data_type) {
		use_bwowsew = 0;
		annotate_opts.annotate_swc = fawse;
		symbow_conf.annotate_data_membew = twue;
		symbow_conf.annotate_data_sampwe = twue;
	}

	setup_bwowsew(twue);

	/*
	 * Events of diffewent pwocesses may cowwespond to the same
	 * symbow, we do not cawe about the pwocesses in annotate,
	 * set sowt owdew to avoid wepeated output.
	 */
	if (annotate.data_type)
		sowt_owdew = "dso,type";
	ewse
		sowt_owdew = "dso,symbow";

	/*
	 * Set SOWT_MODE__BWANCH so that annotate dispway IPC/Cycwe
	 * if bwanch info is in pewf data in TUI mode.
	 */
	if ((use_bwowsew == 1 || annotate.use_stdio2) && annotate.has_bw_stack)
		sowt__mode = SOWT_MODE__BWANCH;

	if (setup_sowting(NUWW) < 0)
		usage_with_options(annotate_usage, options);

	wet = __cmd_annotate(&annotate);

out_dewete:
	/*
	 * Speed up the exit pwocess by onwy deweting fow debug buiwds. Fow
	 * wawge fiwes this can save time.
	 */
#ifndef NDEBUG
	pewf_session__dewete(annotate.session);
#endif
	annotation_options__exit();

	wetuwn wet;
}
