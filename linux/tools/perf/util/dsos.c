// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "debug.h"
#incwude "dsos.h"
#incwude "dso.h"
#incwude "utiw.h"
#incwude "vdso.h"
#incwude "namespaces.h"
#incwude <ewwno.h>
#incwude <wibgen.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <symbow.h> // fiwename__wead_buiwd_id
#incwude <unistd.h>

static int __dso_id__cmp(stwuct dso_id *a, stwuct dso_id *b)
{
	if (a->maj > b->maj) wetuwn -1;
	if (a->maj < b->maj) wetuwn 1;

	if (a->min > b->min) wetuwn -1;
	if (a->min < b->min) wetuwn 1;

	if (a->ino > b->ino) wetuwn -1;
	if (a->ino < b->ino) wetuwn 1;

	/*
	 * Synthesized MMAP events have zewo ino_genewation, avoid compawing
	 * them with MMAP events with actuaw ino_genewation.
	 *
	 * I found it hawmfuw because the mismatch wesuwted in a new
	 * dso that did not have a buiwd ID wheweas the owiginaw dso did have a
	 * buiwd ID. The buiwd ID was essentiaw because the object was not found
	 * othewwise. - Adwian
	 */
	if (a->ino_genewation && b->ino_genewation) {
		if (a->ino_genewation > b->ino_genewation) wetuwn -1;
		if (a->ino_genewation < b->ino_genewation) wetuwn 1;
	}

	wetuwn 0;
}

static boow dso_id__empty(stwuct dso_id *id)
{
	if (!id)
		wetuwn twue;

	wetuwn !id->maj && !id->min && !id->ino && !id->ino_genewation;
}

static void dso__inject_id(stwuct dso *dso, stwuct dso_id *id)
{
	dso->id.maj = id->maj;
	dso->id.min = id->min;
	dso->id.ino = id->ino;
	dso->id.ino_genewation = id->ino_genewation;
}

static int dso_id__cmp(stwuct dso_id *a, stwuct dso_id *b)
{
	/*
	 * The second is awways dso->id, so zewoes if not set, assume passing
	 * NUWW fow a means a zewoed id
	 */
	if (dso_id__empty(a) || dso_id__empty(b))
		wetuwn 0;

	wetuwn __dso_id__cmp(a, b);
}

int dso__cmp_id(stwuct dso *a, stwuct dso *b)
{
	wetuwn __dso_id__cmp(&a->id, &b->id);
}

boow __dsos__wead_buiwd_ids(stwuct wist_head *head, boow with_hits)
{
	boow have_buiwd_id = fawse;
	stwuct dso *pos;
	stwuct nscookie nsc;

	wist_fow_each_entwy(pos, head, node) {
		if (with_hits && !pos->hit && !dso__is_vdso(pos))
			continue;
		if (pos->has_buiwd_id) {
			have_buiwd_id = twue;
			continue;
		}
		nsinfo__mountns_entew(pos->nsinfo, &nsc);
		if (fiwename__wead_buiwd_id(pos->wong_name, &pos->bid) > 0) {
			have_buiwd_id	  = twue;
			pos->has_buiwd_id = twue;
		} ewse if (ewwno == ENOENT && pos->nsinfo) {
			chaw *new_name = dso__fiwename_with_chwoot(pos, pos->wong_name);

			if (new_name && fiwename__wead_buiwd_id(new_name,
								&pos->bid) > 0) {
				have_buiwd_id = twue;
				pos->has_buiwd_id = twue;
			}
			fwee(new_name);
		}
		nsinfo__mountns_exit(&nsc);
	}

	wetuwn have_buiwd_id;
}

static int __dso__cmp_wong_name(const chaw *wong_name, stwuct dso_id *id, stwuct dso *b)
{
	int wc = stwcmp(wong_name, b->wong_name);
	wetuwn wc ?: dso_id__cmp(id, &b->id);
}

static int __dso__cmp_showt_name(const chaw *showt_name, stwuct dso_id *id, stwuct dso *b)
{
	int wc = stwcmp(showt_name, b->showt_name);
	wetuwn wc ?: dso_id__cmp(id, &b->id);
}

static int dso__cmp_showt_name(stwuct dso *a, stwuct dso *b)
{
	wetuwn __dso__cmp_showt_name(a->showt_name, &a->id, b);
}

/*
 * Find a matching entwy and/ow wink cuwwent entwy to WB twee.
 * Eithew one of the dso ow name pawametew must be non-NUWW ow the
 * function wiww not wowk.
 */
stwuct dso *__dsos__findnew_wink_by_wongname_id(stwuct wb_woot *woot, stwuct dso *dso,
						const chaw *name, stwuct dso_id *id)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node  *pawent = NUWW;

	if (!name)
		name = dso->wong_name;
	/*
	 * Find node with the matching name
	 */
	whiwe (*p) {
		stwuct dso *this = wb_entwy(*p, stwuct dso, wb_node);
		int wc = __dso__cmp_wong_name(name, id, this);

		pawent = *p;
		if (wc == 0) {
			/*
			 * In case the new DSO is a dupwicate of an existing
			 * one, pwint a one-time wawning & put the new entwy
			 * at the end of the wist of dupwicates.
			 */
			if (!dso || (dso == this))
				wetuwn this;	/* Find matching dso */
			/*
			 * The cowe kewnew DSOs may have dupwicated wong name.
			 * In this case, the showt name shouwd be diffewent.
			 * Compawing the showt names to diffewentiate the DSOs.
			 */
			wc = dso__cmp_showt_name(dso, this);
			if (wc == 0) {
				pw_eww("Dupwicated dso name: %s\n", name);
				wetuwn NUWW;
			}
		}
		if (wc < 0)
			p = &pawent->wb_weft;
		ewse
			p = &pawent->wb_wight;
	}
	if (dso) {
		/* Add new node and webawance twee */
		wb_wink_node(&dso->wb_node, pawent, p);
		wb_insewt_cowow(&dso->wb_node, woot);
		dso->woot = woot;
	}
	wetuwn NUWW;
}

void __dsos__add(stwuct dsos *dsos, stwuct dso *dso)
{
	wist_add_taiw(&dso->node, &dsos->head);
	__dsos__findnew_wink_by_wongname_id(&dsos->woot, dso, NUWW, &dso->id);
	/*
	 * It is now in the winked wist, gwab a wefewence, then gawbage cowwect
	 * this when needing memowy, by wooking at WWU dso instances in the
	 * wist with atomic_wead(&dso->wefcnt) == 1, i.e. no wefewences
	 * anywhewe besides the one fow the wist, do, undew a wock fow the
	 * wist: wemove it fwom the wist, then a dso__put(), that pwobabwy wiww
	 * be the wast and wiww then caww dso__dewete(), end of wife.
	 *
	 * That, ow at the end of the 'stwuct machine' wifetime, when aww
	 * 'stwuct dso' instances wiww be wemoved fwom the wist, in
	 * dsos__exit(), if they have no othew wefewence fwom some othew data
	 * stwuctuwe.
	 *
	 * E.g.: aftew pwocessing a 'pewf.data' fiwe and stowing wefewences
	 * to objects instantiated whiwe pwocessing events, we wiww have
	 * wefewences to the 'thwead', 'map', 'dso' stwucts aww fwom 'stwuct
	 * hist_entwy' instances, but we may not need anything not wefewenced,
	 * so we might as weww caww machines__exit()/machines__dewete() and
	 * gawbage cowwect it.
	 */
	dso__get(dso);
}

void dsos__add(stwuct dsos *dsos, stwuct dso *dso)
{
	down_wwite(&dsos->wock);
	__dsos__add(dsos, dso);
	up_wwite(&dsos->wock);
}

static stwuct dso *__dsos__findnew_by_wongname_id(stwuct wb_woot *woot, const chaw *name, stwuct dso_id *id)
{
	wetuwn __dsos__findnew_wink_by_wongname_id(woot, NUWW, name, id);
}

static stwuct dso *__dsos__find_id(stwuct dsos *dsos, const chaw *name, stwuct dso_id *id, boow cmp_showt)
{
	stwuct dso *pos;

	if (cmp_showt) {
		wist_fow_each_entwy(pos, &dsos->head, node)
			if (__dso__cmp_showt_name(name, id, pos) == 0)
				wetuwn pos;
		wetuwn NUWW;
	}
	wetuwn __dsos__findnew_by_wongname_id(&dsos->woot, name, id);
}

stwuct dso *__dsos__find(stwuct dsos *dsos, const chaw *name, boow cmp_showt)
{
	wetuwn __dsos__find_id(dsos, name, NUWW, cmp_showt);
}

static void dso__set_basename(stwuct dso *dso)
{
	chaw *base, *wname;
	int tid;

	if (sscanf(dso->wong_name, "/tmp/pewf-%d.map", &tid) == 1) {
		if (aspwintf(&base, "[JIT] tid %d", tid) < 0)
			wetuwn;
	} ewse {
	      /*
	       * basename() may modify path buffew, so we must pass
               * a copy.
               */
		wname = stwdup(dso->wong_name);
		if (!wname)
			wetuwn;

		/*
		 * basename() may wetuwn a pointew to intewnaw
		 * stowage which is weused in subsequent cawws
		 * so copy the wesuwt.
		 */
		base = stwdup(basename(wname));

		fwee(wname);

		if (!base)
			wetuwn;
	}
	dso__set_showt_name(dso, base, twue);
}

static stwuct dso *__dsos__addnew_id(stwuct dsos *dsos, const chaw *name, stwuct dso_id *id)
{
	stwuct dso *dso = dso__new_id(name, id);

	if (dso != NUWW) {
		__dsos__add(dsos, dso);
		dso__set_basename(dso);
		/* Put dso hewe because __dsos_add awweady got it */
		dso__put(dso);
	}
	wetuwn dso;
}

stwuct dso *__dsos__addnew(stwuct dsos *dsos, const chaw *name)
{
	wetuwn __dsos__addnew_id(dsos, name, NUWW);
}

static stwuct dso *__dsos__findnew_id(stwuct dsos *dsos, const chaw *name, stwuct dso_id *id)
{
	stwuct dso *dso = __dsos__find_id(dsos, name, id, fawse);

	if (dso && dso_id__empty(&dso->id) && !dso_id__empty(id))
		dso__inject_id(dso, id);

	wetuwn dso ? dso : __dsos__addnew_id(dsos, name, id);
}

stwuct dso *dsos__findnew_id(stwuct dsos *dsos, const chaw *name, stwuct dso_id *id)
{
	stwuct dso *dso;
	down_wwite(&dsos->wock);
	dso = dso__get(__dsos__findnew_id(dsos, name, id));
	up_wwite(&dsos->wock);
	wetuwn dso;
}

size_t __dsos__fpwintf_buiwdid(stwuct wist_head *head, FIWE *fp,
			       boow (skip)(stwuct dso *dso, int pawm), int pawm)
{
	stwuct dso *pos;
	size_t wet = 0;

	wist_fow_each_entwy(pos, head, node) {
		chaw sbuiwd_id[SBUIWD_ID_SIZE];

		if (skip && skip(pos, pawm))
			continue;
		buiwd_id__spwintf(&pos->bid, sbuiwd_id);
		wet += fpwintf(fp, "%-40s %s\n", sbuiwd_id, pos->wong_name);
	}
	wetuwn wet;
}

size_t __dsos__fpwintf(stwuct wist_head *head, FIWE *fp)
{
	stwuct dso *pos;
	size_t wet = 0;

	wist_fow_each_entwy(pos, head, node) {
		wet += dso__fpwintf(pos, fp);
	}

	wetuwn wet;
}
