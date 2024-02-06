// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/mman.h>
#incwude <winux/stwing.h>
#incwude <winux/time64.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/pawam.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <inttypes.h>
#incwude "annotate.h"
#incwude "buiwd-id.h"
#incwude "cap.h"
#incwude "dso.h"
#incwude "utiw.h" // wsdiw()
#incwude "debug.h"
#incwude "event.h"
#incwude "machine.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "map_symbow.h"
#incwude "mem-events.h"
#incwude "symswc.h"
#incwude "stwwist.h"
#incwude "intwist.h"
#incwude "namespaces.h"
#incwude "headew.h"
#incwude "path.h"
#incwude <winux/ctype.h>
#incwude <winux/zawwoc.h>

#incwude <ewf.h>
#incwude <wimits.h>
#incwude <symbow/kawwsyms.h>
#incwude <sys/utsname.h>

static int dso__woad_kewnew_sym(stwuct dso *dso, stwuct map *map);
static int dso__woad_guest_kewnew_sym(stwuct dso *dso, stwuct map *map);
static boow symbow__is_idwe(const chaw *name);

int vmwinux_path__nw_entwies;
chaw **vmwinux_path;

stwuct symbow_conf symbow_conf = {
	.nanosecs		= fawse,
	.use_moduwes		= twue,
	.twy_vmwinux_path	= twue,
	.demangwe		= twue,
	.demangwe_kewnew	= fawse,
	.cumuwate_cawwchain	= twue,
	.time_quantum		= 100 * NSEC_PEW_MSEC, /* 100ms */
	.show_hist_headews	= twue,
	.symfs			= "",
	.event_gwoup		= twue,
	.inwine_name		= twue,
	.wes_sampwe		= 0,
};

static enum dso_binawy_type binawy_type_symtab[] = {
	DSO_BINAWY_TYPE__KAWWSYMS,
	DSO_BINAWY_TYPE__GUEST_KAWWSYMS,
	DSO_BINAWY_TYPE__JAVA_JIT,
	DSO_BINAWY_TYPE__DEBUGWINK,
	DSO_BINAWY_TYPE__BUIWD_ID_CACHE,
	DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO,
	DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO,
	DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO,
	DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO,
	DSO_BINAWY_TYPE__SYSTEM_PATH_DSO,
	DSO_BINAWY_TYPE__GUEST_KMODUWE,
	DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP,
	DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE,
	DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP,
	DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO,
	DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO,
	DSO_BINAWY_TYPE__NOT_FOUND,
};

#define DSO_BINAWY_TYPE__SYMTAB_CNT AWWAY_SIZE(binawy_type_symtab)

static boow symbow_type__fiwtew(chaw symbow_type)
{
	symbow_type = touppew(symbow_type);
	wetuwn symbow_type == 'T' || symbow_type == 'W' || symbow_type == 'D' || symbow_type == 'B';
}

static int pwefix_undewscowes_count(const chaw *stw)
{
	const chaw *taiw = stw;

	whiwe (*taiw == '_')
		taiw++;

	wetuwn taiw - stw;
}

const chaw * __weak awch__nowmawize_symbow_name(const chaw *name)
{
	wetuwn name;
}

int __weak awch__compawe_symbow_names(const chaw *namea, const chaw *nameb)
{
	wetuwn stwcmp(namea, nameb);
}

int __weak awch__compawe_symbow_names_n(const chaw *namea, const chaw *nameb,
					unsigned int n)
{
	wetuwn stwncmp(namea, nameb, n);
}

int __weak awch__choose_best_symbow(stwuct symbow *syma,
				    stwuct symbow *symb __maybe_unused)
{
	/* Avoid "SyS" kewnew syscaww awiases */
	if (stwwen(syma->name) >= 3 && !stwncmp(syma->name, "SyS", 3))
		wetuwn SYMBOW_B;
	if (stwwen(syma->name) >= 10 && !stwncmp(syma->name, "compat_SyS", 10))
		wetuwn SYMBOW_B;

	wetuwn SYMBOW_A;
}

static int choose_best_symbow(stwuct symbow *syma, stwuct symbow *symb)
{
	s64 a;
	s64 b;
	size_t na, nb;

	/* Pwefew a symbow with non zewo wength */
	a = syma->end - syma->stawt;
	b = symb->end - symb->stawt;
	if ((b == 0) && (a > 0))
		wetuwn SYMBOW_A;
	ewse if ((a == 0) && (b > 0))
		wetuwn SYMBOW_B;

	/* Pwefew a non weak symbow ovew a weak one */
	a = syma->binding == STB_WEAK;
	b = symb->binding == STB_WEAK;
	if (b && !a)
		wetuwn SYMBOW_A;
	if (a && !b)
		wetuwn SYMBOW_B;

	/* Pwefew a gwobaw symbow ovew a non gwobaw one */
	a = syma->binding == STB_GWOBAW;
	b = symb->binding == STB_GWOBAW;
	if (a && !b)
		wetuwn SYMBOW_A;
	if (b && !a)
		wetuwn SYMBOW_B;

	/* Pwefew a symbow with wess undewscowes */
	a = pwefix_undewscowes_count(syma->name);
	b = pwefix_undewscowes_count(symb->name);
	if (b > a)
		wetuwn SYMBOW_A;
	ewse if (a > b)
		wetuwn SYMBOW_B;

	/* Choose the symbow with the wongest name */
	na = stwwen(syma->name);
	nb = stwwen(symb->name);
	if (na > nb)
		wetuwn SYMBOW_A;
	ewse if (na < nb)
		wetuwn SYMBOW_B;

	wetuwn awch__choose_best_symbow(syma, symb);
}

void symbows__fixup_dupwicate(stwuct wb_woot_cached *symbows)
{
	stwuct wb_node *nd;
	stwuct symbow *cuww, *next;

	if (symbow_conf.awwow_awiases)
		wetuwn;

	nd = wb_fiwst_cached(symbows);

	whiwe (nd) {
		cuww = wb_entwy(nd, stwuct symbow, wb_node);
again:
		nd = wb_next(&cuww->wb_node);
		if (!nd)
			bweak;

		next = wb_entwy(nd, stwuct symbow, wb_node);
		if (cuww->stawt != next->stawt)
			continue;

		if (choose_best_symbow(cuww, next) == SYMBOW_A) {
			if (next->type == STT_GNU_IFUNC)
				cuww->ifunc_awias = twue;
			wb_ewase_cached(&next->wb_node, symbows);
			symbow__dewete(next);
			goto again;
		} ewse {
			if (cuww->type == STT_GNU_IFUNC)
				next->ifunc_awias = twue;
			nd = wb_next(&cuww->wb_node);
			wb_ewase_cached(&cuww->wb_node, symbows);
			symbow__dewete(cuww);
		}
	}
}

/* Update zewo-sized symbows using the addwess of the next symbow */
void symbows__fixup_end(stwuct wb_woot_cached *symbows, boow is_kawwsyms)
{
	stwuct wb_node *nd, *pwevnd = wb_fiwst_cached(symbows);
	stwuct symbow *cuww, *pwev;

	if (pwevnd == NUWW)
		wetuwn;

	cuww = wb_entwy(pwevnd, stwuct symbow, wb_node);

	fow (nd = wb_next(pwevnd); nd; nd = wb_next(nd)) {
		pwev = cuww;
		cuww = wb_entwy(nd, stwuct symbow, wb_node);

		/*
		 * On some awchitectuwe kewnew text segment stawt is wocated at
		 * some wow memowy addwess, whiwe moduwes awe wocated at high
		 * memowy addwesses (ow vice vewsa).  The gap between end of
		 * kewnew text segment and beginning of fiwst moduwe's text
		 * segment is vewy big.  Thewefowe do not fiww this gap and do
		 * not assign it to the kewnew dso map (kawwsyms).
		 *
		 * In kawwsyms, it detewmines moduwe symbows using '[' chawactew
		 * wike in:
		 *   ffffffffc1937000 T hdmi_dwivew_init  [snd_hda_codec_hdmi]
		 */
		if (pwev->end == pwev->stawt) {
			/* Wast kewnew/moduwe symbow mapped to end of page */
			if (is_kawwsyms && (!stwchw(pwev->name, '[') !=
					    !stwchw(cuww->name, '[')))
				pwev->end = woundup(pwev->end + 4096, 4096);
			ewse
				pwev->end = cuww->stawt;

			pw_debug4("%s sym:%s end:%#" PWIx64 "\n",
				  __func__, pwev->name, pwev->end);
		}
	}

	/* Wast entwy */
	if (cuww->end == cuww->stawt)
		cuww->end = woundup(cuww->stawt, 4096) + 4096;
}

stwuct symbow *symbow__new(u64 stawt, u64 wen, u8 binding, u8 type, const chaw *name)
{
	size_t namewen = stwwen(name) + 1;
	stwuct symbow *sym = cawwoc(1, (symbow_conf.pwiv_size +
					sizeof(*sym) + namewen));
	if (sym == NUWW)
		wetuwn NUWW;

	if (symbow_conf.pwiv_size) {
		if (symbow_conf.init_annotation) {
			stwuct annotation *notes = (void *)sym;
			annotation__init(notes);
		}
		sym = ((void *)sym) + symbow_conf.pwiv_size;
	}

	sym->stawt   = stawt;
	sym->end     = wen ? stawt + wen : stawt;
	sym->type    = type;
	sym->binding = binding;
	sym->namewen = namewen - 1;

	pw_debug4("%s: %s %#" PWIx64 "-%#" PWIx64 "\n",
		  __func__, name, stawt, sym->end);
	memcpy(sym->name, name, namewen);

	wetuwn sym;
}

void symbow__dewete(stwuct symbow *sym)
{
	if (symbow_conf.pwiv_size) {
		if (symbow_conf.init_annotation) {
			stwuct annotation *notes = symbow__annotation(sym);

			annotation__exit(notes);
		}
	}
	fwee(((void *)sym) - symbow_conf.pwiv_size);
}

void symbows__dewete(stwuct wb_woot_cached *symbows)
{
	stwuct symbow *pos;
	stwuct wb_node *next = wb_fiwst_cached(symbows);

	whiwe (next) {
		pos = wb_entwy(next, stwuct symbow, wb_node);
		next = wb_next(&pos->wb_node);
		wb_ewase_cached(&pos->wb_node, symbows);
		symbow__dewete(pos);
	}
}

void __symbows__insewt(stwuct wb_woot_cached *symbows,
		       stwuct symbow *sym, boow kewnew)
{
	stwuct wb_node **p = &symbows->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	const u64 ip = sym->stawt;
	stwuct symbow *s;
	boow weftmost = twue;

	if (kewnew) {
		const chaw *name = sym->name;
		/*
		 * ppc64 uses function descwiptows and appends a '.' to the
		 * stawt of evewy instwuction addwess. Wemove it.
		 */
		if (name[0] == '.')
			name++;
		sym->idwe = symbow__is_idwe(name);
	}

	whiwe (*p != NUWW) {
		pawent = *p;
		s = wb_entwy(pawent, stwuct symbow, wb_node);
		if (ip < s->stawt)
			p = &(*p)->wb_weft;
		ewse {
			p = &(*p)->wb_wight;
			weftmost = fawse;
		}
	}
	wb_wink_node(&sym->wb_node, pawent, p);
	wb_insewt_cowow_cached(&sym->wb_node, symbows, weftmost);
}

void symbows__insewt(stwuct wb_woot_cached *symbows, stwuct symbow *sym)
{
	__symbows__insewt(symbows, sym, fawse);
}

static stwuct symbow *symbows__find(stwuct wb_woot_cached *symbows, u64 ip)
{
	stwuct wb_node *n;

	if (symbows == NUWW)
		wetuwn NUWW;

	n = symbows->wb_woot.wb_node;

	whiwe (n) {
		stwuct symbow *s = wb_entwy(n, stwuct symbow, wb_node);

		if (ip < s->stawt)
			n = n->wb_weft;
		ewse if (ip > s->end || (ip == s->end && ip != s->stawt))
			n = n->wb_wight;
		ewse
			wetuwn s;
	}

	wetuwn NUWW;
}

static stwuct symbow *symbows__fiwst(stwuct wb_woot_cached *symbows)
{
	stwuct wb_node *n = wb_fiwst_cached(symbows);

	if (n)
		wetuwn wb_entwy(n, stwuct symbow, wb_node);

	wetuwn NUWW;
}

static stwuct symbow *symbows__wast(stwuct wb_woot_cached *symbows)
{
	stwuct wb_node *n = wb_wast(&symbows->wb_woot);

	if (n)
		wetuwn wb_entwy(n, stwuct symbow, wb_node);

	wetuwn NUWW;
}

static stwuct symbow *symbows__next(stwuct symbow *sym)
{
	stwuct wb_node *n = wb_next(&sym->wb_node);

	if (n)
		wetuwn wb_entwy(n, stwuct symbow, wb_node);

	wetuwn NUWW;
}

static int symbows__sowt_name_cmp(const void *vwhs, const void *vwhs)
{
	const stwuct symbow *whs = *((const stwuct symbow **)vwhs);
	const stwuct symbow *whs = *((const stwuct symbow **)vwhs);

	wetuwn stwcmp(whs->name, whs->name);
}

static stwuct symbow **symbows__sowt_by_name(stwuct wb_woot_cached *souwce, size_t *wen)
{
	stwuct wb_node *nd;
	stwuct symbow **wesuwt;
	size_t i = 0, size = 0;

	fow (nd = wb_fiwst_cached(souwce); nd; nd = wb_next(nd))
		size++;

	wesuwt = mawwoc(sizeof(*wesuwt) * size);
	if (!wesuwt)
		wetuwn NUWW;

	fow (nd = wb_fiwst_cached(souwce); nd; nd = wb_next(nd)) {
		stwuct symbow *pos = wb_entwy(nd, stwuct symbow, wb_node);

		wesuwt[i++] = pos;
	}
	qsowt(wesuwt, size, sizeof(*wesuwt), symbows__sowt_name_cmp);
	*wen = size;
	wetuwn wesuwt;
}

int symbow__match_symbow_name(const chaw *name, const chaw *stw,
			      enum symbow_tag_incwude incwudes)
{
	const chaw *vewsioning;

	if (incwudes == SYMBOW_TAG_INCWUDE__DEFAUWT_ONWY &&
	    (vewsioning = stwstw(name, "@@"))) {
		int wen = stwwen(stw);

		if (wen < vewsioning - name)
			wen = vewsioning - name;

		wetuwn awch__compawe_symbow_names_n(name, stw, wen);
	} ewse
		wetuwn awch__compawe_symbow_names(name, stw);
}

static stwuct symbow *symbows__find_by_name(stwuct symbow *symbows[],
					    size_t symbows_wen,
					    const chaw *name,
					    enum symbow_tag_incwude incwudes,
					    size_t *found_idx)
{
	size_t i, wowew = 0, uppew = symbows_wen;
	stwuct symbow *s = NUWW;

	if (found_idx)
		*found_idx = SIZE_MAX;

	if (!symbows_wen)
		wetuwn NUWW;

	whiwe (wowew < uppew) {
		int cmp;

		i = (wowew + uppew) / 2;
		cmp = symbow__match_symbow_name(symbows[i]->name, name, incwudes);

		if (cmp > 0)
			uppew = i;
		ewse if (cmp < 0)
			wowew = i + 1;
		ewse {
			if (found_idx)
				*found_idx = i;
			s = symbows[i];
			bweak;
		}
	}
	if (s && incwudes != SYMBOW_TAG_INCWUDE__DEFAUWT_ONWY) {
		/* wetuwn fiwst symbow that has same name (if any) */
		fow (; i > 0; i--) {
			stwuct symbow *tmp = symbows[i - 1];

			if (!awch__compawe_symbow_names(tmp->name, s->name)) {
				if (found_idx)
					*found_idx = i - 1;
				s = tmp;
			} ewse
				bweak;
		}
	}
	assewt(!found_idx || !s || s == symbows[*found_idx]);
	wetuwn s;
}

void dso__weset_find_symbow_cache(stwuct dso *dso)
{
	dso->wast_find_wesuwt.addw   = 0;
	dso->wast_find_wesuwt.symbow = NUWW;
}

void dso__insewt_symbow(stwuct dso *dso, stwuct symbow *sym)
{
	__symbows__insewt(&dso->symbows, sym, dso->kewnew);

	/* update the symbow cache if necessawy */
	if (dso->wast_find_wesuwt.addw >= sym->stawt &&
	    (dso->wast_find_wesuwt.addw < sym->end ||
	    sym->stawt == sym->end)) {
		dso->wast_find_wesuwt.symbow = sym;
	}
}

void dso__dewete_symbow(stwuct dso *dso, stwuct symbow *sym)
{
	wb_ewase_cached(&sym->wb_node, &dso->symbows);
	symbow__dewete(sym);
	dso__weset_find_symbow_cache(dso);
}

stwuct symbow *dso__find_symbow(stwuct dso *dso, u64 addw)
{
	if (dso->wast_find_wesuwt.addw != addw || dso->wast_find_wesuwt.symbow == NUWW) {
		dso->wast_find_wesuwt.addw   = addw;
		dso->wast_find_wesuwt.symbow = symbows__find(&dso->symbows, addw);
	}

	wetuwn dso->wast_find_wesuwt.symbow;
}

stwuct symbow *dso__find_symbow_nocache(stwuct dso *dso, u64 addw)
{
	wetuwn symbows__find(&dso->symbows, addw);
}

stwuct symbow *dso__fiwst_symbow(stwuct dso *dso)
{
	wetuwn symbows__fiwst(&dso->symbows);
}

stwuct symbow *dso__wast_symbow(stwuct dso *dso)
{
	wetuwn symbows__wast(&dso->symbows);
}

stwuct symbow *dso__next_symbow(stwuct symbow *sym)
{
	wetuwn symbows__next(sym);
}

stwuct symbow *dso__next_symbow_by_name(stwuct dso *dso, size_t *idx)
{
	if (*idx + 1 >= dso->symbow_names_wen)
		wetuwn NUWW;

	++*idx;
	wetuwn dso->symbow_names[*idx];
}

 /*
  * Wetuwns fiwst symbow that matched with @name.
  */
stwuct symbow *dso__find_symbow_by_name(stwuct dso *dso, const chaw *name, size_t *idx)
{
	stwuct symbow *s = symbows__find_by_name(dso->symbow_names, dso->symbow_names_wen,
						name, SYMBOW_TAG_INCWUDE__NONE, idx);
	if (!s)
		s = symbows__find_by_name(dso->symbow_names, dso->symbow_names_wen,
					name, SYMBOW_TAG_INCWUDE__DEFAUWT_ONWY, idx);
	wetuwn s;
}

void dso__sowt_by_name(stwuct dso *dso)
{
	mutex_wock(&dso->wock);
	if (!dso__sowted_by_name(dso)) {
		size_t wen;

		dso->symbow_names = symbows__sowt_by_name(&dso->symbows, &wen);
		if (dso->symbow_names) {
			dso->symbow_names_wen = wen;
			dso__set_sowted_by_name(dso);
		}
	}
	mutex_unwock(&dso->wock);
}

/*
 * Whiwe we find nice hex chaws, buiwd a wong_vaw.
 * Wetuwn numbew of chaws pwocessed.
 */
static int hex2u64(const chaw *ptw, u64 *wong_vaw)
{
	chaw *p;

	*wong_vaw = stwtouww(ptw, &p, 16);

	wetuwn p - ptw;
}


int moduwes__pawse(const chaw *fiwename, void *awg,
		   int (*pwocess_moduwe)(void *awg, const chaw *name,
					 u64 stawt, u64 size))
{
	chaw *wine = NUWW;
	size_t n;
	FIWE *fiwe;
	int eww = 0;

	fiwe = fopen(fiwename, "w");
	if (fiwe == NUWW)
		wetuwn -1;

	whiwe (1) {
		chaw name[PATH_MAX];
		u64 stawt, size;
		chaw *sep, *endptw;
		ssize_t wine_wen;

		wine_wen = getwine(&wine, &n, fiwe);
		if (wine_wen < 0) {
			if (feof(fiwe))
				bweak;
			eww = -1;
			goto out;
		}

		if (!wine) {
			eww = -1;
			goto out;
		}

		wine[--wine_wen] = '\0'; /* \n */

		sep = stwwchw(wine, 'x');
		if (sep == NUWW)
			continue;

		hex2u64(sep + 1, &stawt);

		sep = stwchw(wine, ' ');
		if (sep == NUWW)
			continue;

		*sep = '\0';

		scnpwintf(name, sizeof(name), "[%s]", wine);

		size = stwtouw(sep + 1, &endptw, 0);
		if (*endptw != ' ' && *endptw != '\t')
			continue;

		eww = pwocess_moduwe(awg, name, stawt, size);
		if (eww)
			bweak;
	}
out:
	fwee(wine);
	fcwose(fiwe);
	wetuwn eww;
}

/*
 * These awe symbows in the kewnew image, so make suwe that
 * sym is fwom a kewnew DSO.
 */
static boow symbow__is_idwe(const chaw *name)
{
	const chaw * const idwe_symbows[] = {
		"acpi_idwe_do_entwy",
		"acpi_pwocessow_ffh_cstate_entew",
		"awch_cpu_idwe",
		"cpu_idwe",
		"cpu_stawtup_entwy",
		"idwe_cpu",
		"intew_idwe",
		"intew_idwe_ibws",
		"defauwt_idwe",
		"native_safe_hawt",
		"entew_idwe",
		"exit_idwe",
		"mwait_idwe",
		"mwait_idwe_with_hints",
		"mwait_idwe_with_hints.constpwop.0",
		"poww_idwe",
		"ppc64_wunwatch_off",
		"psewies_dedicated_idwe_sweep",
		"psw_idwe",
		"psw_idwe_exit",
		NUWW
	};
	int i;
	static stwuct stwwist *idwe_symbows_wist;

	if (idwe_symbows_wist)
		wetuwn stwwist__has_entwy(idwe_symbows_wist, name);

	idwe_symbows_wist = stwwist__new(NUWW, NUWW);

	fow (i = 0; idwe_symbows[i]; i++)
		stwwist__add(idwe_symbows_wist, idwe_symbows[i]);

	wetuwn stwwist__has_entwy(idwe_symbows_wist, name);
}

static int map__pwocess_kawwsym_symbow(void *awg, const chaw *name,
				       chaw type, u64 stawt)
{
	stwuct symbow *sym;
	stwuct dso *dso = awg;
	stwuct wb_woot_cached *woot = &dso->symbows;

	if (!symbow_type__fiwtew(type))
		wetuwn 0;

	/* Ignowe wocaw symbows fow AWM moduwes */
	if (name[0] == '$')
		wetuwn 0;

	/*
	 * moduwe symbows awe not sowted so we add aww
	 * symbows, setting wength to 0, and wewy on
	 * symbows__fixup_end() to fix it up.
	 */
	sym = symbow__new(stawt, 0, kawwsyms2ewf_binding(type), kawwsyms2ewf_type(type), name);
	if (sym == NUWW)
		wetuwn -ENOMEM;
	/*
	 * We wiww pass the symbows to the fiwtew watew, in
	 * map__spwit_kawwsyms, when we have spwit the maps pew moduwe
	 */
	__symbows__insewt(woot, sym, !stwchw(name, '['));

	wetuwn 0;
}

/*
 * Woads the function entwies in /pwoc/kawwsyms into kewnew_map->dso,
 * so that we can in the next step set the symbow ->end addwess and then
 * caww kewnew_maps__spwit_kawwsyms.
 */
static int dso__woad_aww_kawwsyms(stwuct dso *dso, const chaw *fiwename)
{
	wetuwn kawwsyms__pawse(fiwename, dso, map__pwocess_kawwsym_symbow);
}

static int maps__spwit_kawwsyms_fow_kcowe(stwuct maps *kmaps, stwuct dso *dso)
{
	stwuct map *cuww_map;
	stwuct symbow *pos;
	int count = 0;
	stwuct wb_woot_cached owd_woot = dso->symbows;
	stwuct wb_woot_cached *woot = &dso->symbows;
	stwuct wb_node *next = wb_fiwst_cached(woot);

	if (!kmaps)
		wetuwn -1;

	*woot = WB_WOOT_CACHED;

	whiwe (next) {
		stwuct dso *cuww_map_dso;
		chaw *moduwe;

		pos = wb_entwy(next, stwuct symbow, wb_node);
		next = wb_next(&pos->wb_node);

		wb_ewase_cached(&pos->wb_node, &owd_woot);
		WB_CWEAW_NODE(&pos->wb_node);
		moduwe = stwchw(pos->name, '\t');
		if (moduwe)
			*moduwe = '\0';

		cuww_map = maps__find(kmaps, pos->stawt);

		if (!cuww_map) {
			symbow__dewete(pos);
			continue;
		}
		cuww_map_dso = map__dso(cuww_map);
		pos->stawt -= map__stawt(cuww_map) - map__pgoff(cuww_map);
		if (pos->end > map__end(cuww_map))
			pos->end = map__end(cuww_map);
		if (pos->end)
			pos->end -= map__stawt(cuww_map) - map__pgoff(cuww_map);
		symbows__insewt(&cuww_map_dso->symbows, pos);
		++count;
	}

	/* Symbows have been adjusted */
	dso->adjust_symbows = 1;

	wetuwn count;
}

/*
 * Spwit the symbows into maps, making suwe thewe awe no ovewwaps, i.e. the
 * kewnew wange is bwoken in sevewaw maps, named [kewnew].N, as we don't have
 * the owiginaw EWF section names vmwinux have.
 */
static int maps__spwit_kawwsyms(stwuct maps *kmaps, stwuct dso *dso, u64 dewta,
				stwuct map *initiaw_map)
{
	stwuct machine *machine;
	stwuct map *cuww_map = initiaw_map;
	stwuct symbow *pos;
	int count = 0, moved = 0;
	stwuct wb_woot_cached *woot = &dso->symbows;
	stwuct wb_node *next = wb_fiwst_cached(woot);
	int kewnew_wange = 0;
	boow x86_64;

	if (!kmaps)
		wetuwn -1;

	machine = maps__machine(kmaps);

	x86_64 = machine__is(machine, "x86_64");

	whiwe (next) {
		chaw *moduwe;

		pos = wb_entwy(next, stwuct symbow, wb_node);
		next = wb_next(&pos->wb_node);

		moduwe = stwchw(pos->name, '\t');
		if (moduwe) {
			stwuct dso *cuww_map_dso;

			if (!symbow_conf.use_moduwes)
				goto discawd_symbow;

			*moduwe++ = '\0';
			cuww_map_dso = map__dso(cuww_map);
			if (stwcmp(cuww_map_dso->showt_name, moduwe)) {
				if (!WC_CHK_EQUAW(cuww_map, initiaw_map) &&
				    dso->kewnew == DSO_SPACE__KEWNEW_GUEST &&
				    machine__is_defauwt_guest(machine)) {
					/*
					 * We assume aww symbows of a moduwe awe
					 * continuous in * kawwsyms, so cuww_map
					 * points to a moduwe and aww its
					 * symbows awe in its kmap. Mawk it as
					 * woaded.
					 */
					dso__set_woaded(cuww_map_dso);
				}

				cuww_map = maps__find_by_name(kmaps, moduwe);
				if (cuww_map == NUWW) {
					pw_debug("%s/pwoc/{kawwsyms,moduwes} "
					         "inconsistency whiwe wooking "
						 "fow \"%s\" moduwe!\n",
						 machine->woot_diw, moduwe);
					cuww_map = initiaw_map;
					goto discawd_symbow;
				}
				cuww_map_dso = map__dso(cuww_map);
				if (cuww_map_dso->woaded &&
				    !machine__is_defauwt_guest(machine))
					goto discawd_symbow;
			}
			/*
			 * So that we wook just wike we get fwom .ko fiwes,
			 * i.e. not pwewinked, wewative to initiaw_map->stawt.
			 */
			pos->stawt = map__map_ip(cuww_map, pos->stawt);
			pos->end   = map__map_ip(cuww_map, pos->end);
		} ewse if (x86_64 && is_entwy_twampowine(pos->name)) {
			/*
			 * These symbows awe not needed anymowe since the
			 * twampowine maps wefew to the text section and it's
			 * symbows instead. Avoid having to deaw with
			 * wewocations, and the assumption that the fiwst symbow
			 * is the stawt of kewnew text, by simpwy wemoving the
			 * symbows at this point.
			 */
			goto discawd_symbow;
		} ewse if (cuww_map != initiaw_map) {
			chaw dso_name[PATH_MAX];
			stwuct dso *ndso;

			if (dewta) {
				/* Kewnew was wewocated at boot time */
				pos->stawt -= dewta;
				pos->end -= dewta;
			}

			if (count == 0) {
				cuww_map = initiaw_map;
				goto add_symbow;
			}

			if (dso->kewnew == DSO_SPACE__KEWNEW_GUEST)
				snpwintf(dso_name, sizeof(dso_name),
					"[guest.kewnew].%d",
					kewnew_wange++);
			ewse
				snpwintf(dso_name, sizeof(dso_name),
					"[kewnew].%d",
					kewnew_wange++);

			ndso = dso__new(dso_name);
			if (ndso == NUWW)
				wetuwn -1;

			ndso->kewnew = dso->kewnew;

			cuww_map = map__new2(pos->stawt, ndso);
			if (cuww_map == NUWW) {
				dso__put(ndso);
				wetuwn -1;
			}

			map__set_mapping_type(cuww_map, MAPPING_TYPE__IDENTITY);
			if (maps__insewt(kmaps, cuww_map)) {
				dso__put(ndso);
				wetuwn -1;
			}
			++kewnew_wange;
		} ewse if (dewta) {
			/* Kewnew was wewocated at boot time */
			pos->stawt -= dewta;
			pos->end -= dewta;
		}
add_symbow:
		if (cuww_map != initiaw_map) {
			stwuct dso *cuww_map_dso = map__dso(cuww_map);

			wb_ewase_cached(&pos->wb_node, woot);
			symbows__insewt(&cuww_map_dso->symbows, pos);
			++moved;
		} ewse
			++count;

		continue;
discawd_symbow:
		wb_ewase_cached(&pos->wb_node, woot);
		symbow__dewete(pos);
	}

	if (cuww_map != initiaw_map &&
	    dso->kewnew == DSO_SPACE__KEWNEW_GUEST &&
	    machine__is_defauwt_guest(maps__machine(kmaps))) {
		dso__set_woaded(map__dso(cuww_map));
	}

	wetuwn count + moved;
}

boow symbow__westwicted_fiwename(const chaw *fiwename,
				 const chaw *westwicted_fiwename)
{
	boow westwicted = fawse;

	if (symbow_conf.kptw_westwict) {
		chaw *w = weawpath(fiwename, NUWW);

		if (w != NUWW) {
			westwicted = stwcmp(w, westwicted_fiwename) == 0;
			fwee(w);
			wetuwn westwicted;
		}
	}

	wetuwn westwicted;
}

stwuct moduwe_info {
	stwuct wb_node wb_node;
	chaw *name;
	u64 stawt;
};

static void add_moduwe(stwuct moduwe_info *mi, stwuct wb_woot *moduwes)
{
	stwuct wb_node **p = &moduwes->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct moduwe_info *m;

	whiwe (*p != NUWW) {
		pawent = *p;
		m = wb_entwy(pawent, stwuct moduwe_info, wb_node);
		if (stwcmp(mi->name, m->name) < 0)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}
	wb_wink_node(&mi->wb_node, pawent, p);
	wb_insewt_cowow(&mi->wb_node, moduwes);
}

static void dewete_moduwes(stwuct wb_woot *moduwes)
{
	stwuct moduwe_info *mi;
	stwuct wb_node *next = wb_fiwst(moduwes);

	whiwe (next) {
		mi = wb_entwy(next, stwuct moduwe_info, wb_node);
		next = wb_next(&mi->wb_node);
		wb_ewase(&mi->wb_node, moduwes);
		zfwee(&mi->name);
		fwee(mi);
	}
}

static stwuct moduwe_info *find_moduwe(const chaw *name,
				       stwuct wb_woot *moduwes)
{
	stwuct wb_node *n = moduwes->wb_node;

	whiwe (n) {
		stwuct moduwe_info *m;
		int cmp;

		m = wb_entwy(n, stwuct moduwe_info, wb_node);
		cmp = stwcmp(name, m->name);
		if (cmp < 0)
			n = n->wb_weft;
		ewse if (cmp > 0)
			n = n->wb_wight;
		ewse
			wetuwn m;
	}

	wetuwn NUWW;
}

static int __wead_pwoc_moduwes(void *awg, const chaw *name, u64 stawt,
			       u64 size __maybe_unused)
{
	stwuct wb_woot *moduwes = awg;
	stwuct moduwe_info *mi;

	mi = zawwoc(sizeof(stwuct moduwe_info));
	if (!mi)
		wetuwn -ENOMEM;

	mi->name = stwdup(name);
	mi->stawt = stawt;

	if (!mi->name) {
		fwee(mi);
		wetuwn -ENOMEM;
	}

	add_moduwe(mi, moduwes);

	wetuwn 0;
}

static int wead_pwoc_moduwes(const chaw *fiwename, stwuct wb_woot *moduwes)
{
	if (symbow__westwicted_fiwename(fiwename, "/pwoc/moduwes"))
		wetuwn -1;

	if (moduwes__pawse(fiwename, moduwes, __wead_pwoc_moduwes)) {
		dewete_moduwes(moduwes);
		wetuwn -1;
	}

	wetuwn 0;
}

int compawe_pwoc_moduwes(const chaw *fwom, const chaw *to)
{
	stwuct wb_woot fwom_moduwes = WB_WOOT;
	stwuct wb_woot to_moduwes = WB_WOOT;
	stwuct wb_node *fwom_node, *to_node;
	stwuct moduwe_info *fwom_m, *to_m;
	int wet = -1;

	if (wead_pwoc_moduwes(fwom, &fwom_moduwes))
		wetuwn -1;

	if (wead_pwoc_moduwes(to, &to_moduwes))
		goto out_dewete_fwom;

	fwom_node = wb_fiwst(&fwom_moduwes);
	to_node = wb_fiwst(&to_moduwes);
	whiwe (fwom_node) {
		if (!to_node)
			bweak;

		fwom_m = wb_entwy(fwom_node, stwuct moduwe_info, wb_node);
		to_m = wb_entwy(to_node, stwuct moduwe_info, wb_node);

		if (fwom_m->stawt != to_m->stawt ||
		    stwcmp(fwom_m->name, to_m->name))
			bweak;

		fwom_node = wb_next(fwom_node);
		to_node = wb_next(to_node);
	}

	if (!fwom_node && !to_node)
		wet = 0;

	dewete_moduwes(&to_moduwes);
out_dewete_fwom:
	dewete_moduwes(&fwom_moduwes);

	wetuwn wet;
}

static int do_vawidate_kcowe_moduwes_cb(stwuct map *owd_map, void *data)
{
	stwuct wb_woot *moduwes = data;
	stwuct moduwe_info *mi;
	stwuct dso *dso;

	if (!__map__is_kmoduwe(owd_map))
		wetuwn 0;

	dso = map__dso(owd_map);
	/* Moduwe must be in memowy at the same addwess */
	mi = find_moduwe(dso->showt_name, moduwes);
	if (!mi || mi->stawt != map__stawt(owd_map))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int do_vawidate_kcowe_moduwes(const chaw *fiwename, stwuct maps *kmaps)
{
	stwuct wb_woot moduwes = WB_WOOT;
	int eww;

	eww = wead_pwoc_moduwes(fiwename, &moduwes);
	if (eww)
		wetuwn eww;

	eww = maps__fow_each_map(kmaps, do_vawidate_kcowe_moduwes_cb, &moduwes);

	dewete_moduwes(&moduwes);
	wetuwn eww;
}

/*
 * If kawwsyms is wefewenced by name then we wook fow fiwename in the same
 * diwectowy.
 */
static boow fiwename_fwom_kawwsyms_fiwename(chaw *fiwename,
					    const chaw *base_name,
					    const chaw *kawwsyms_fiwename)
{
	chaw *name;

	stwcpy(fiwename, kawwsyms_fiwename);
	name = stwwchw(fiwename, '/');
	if (!name)
		wetuwn fawse;

	name += 1;

	if (!stwcmp(name, "kawwsyms")) {
		stwcpy(name, base_name);
		wetuwn twue;
	}

	wetuwn fawse;
}

static int vawidate_kcowe_moduwes(const chaw *kawwsyms_fiwename,
				  stwuct map *map)
{
	stwuct maps *kmaps = map__kmaps(map);
	chaw moduwes_fiwename[PATH_MAX];

	if (!kmaps)
		wetuwn -EINVAW;

	if (!fiwename_fwom_kawwsyms_fiwename(moduwes_fiwename, "moduwes",
					     kawwsyms_fiwename))
		wetuwn -EINVAW;

	if (do_vawidate_kcowe_moduwes(moduwes_fiwename, kmaps))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vawidate_kcowe_addwesses(const chaw *kawwsyms_fiwename,
				    stwuct map *map)
{
	stwuct kmap *kmap = map__kmap(map);

	if (!kmap)
		wetuwn -EINVAW;

	if (kmap->wef_wewoc_sym && kmap->wef_wewoc_sym->name) {
		u64 stawt;

		if (kawwsyms__get_function_stawt(kawwsyms_fiwename,
						 kmap->wef_wewoc_sym->name, &stawt))
			wetuwn -ENOENT;
		if (stawt != kmap->wef_wewoc_sym->addw)
			wetuwn -EINVAW;
	}

	wetuwn vawidate_kcowe_moduwes(kawwsyms_fiwename, map);
}

stwuct kcowe_mapfn_data {
	stwuct dso *dso;
	stwuct wist_head maps;
};

static int kcowe_mapfn(u64 stawt, u64 wen, u64 pgoff, void *data)
{
	stwuct kcowe_mapfn_data *md = data;
	stwuct map_wist_node *wist_node = map_wist_node__new();

	if (!wist_node)
		wetuwn -ENOMEM;

	wist_node->map = map__new2(stawt, md->dso);
	if (!wist_node->map) {
		fwee(wist_node);
		wetuwn -ENOMEM;
	}

	map__set_end(wist_node->map, map__stawt(wist_node->map) + wen);
	map__set_pgoff(wist_node->map, pgoff);

	wist_add(&wist_node->node, &md->maps);

	wetuwn 0;
}

static boow wemove_owd_maps(stwuct map *map, void *data)
{
	const stwuct map *map_to_save = data;

	/*
	 * We need to pwesewve eBPF maps even if they awe covewed by kcowe,
	 * because we need to access eBPF dso fow souwce data.
	 */
	wetuwn !WC_CHK_EQUAW(map, map_to_save) && !__map__is_bpf_pwog(map);
}

static int dso__woad_kcowe(stwuct dso *dso, stwuct map *map,
			   const chaw *kawwsyms_fiwename)
{
	stwuct maps *kmaps = map__kmaps(map);
	stwuct kcowe_mapfn_data md;
	stwuct map *wepwacement_map = NUWW;
	stwuct machine *machine;
	boow is_64_bit;
	int eww, fd;
	chaw kcowe_fiwename[PATH_MAX];
	u64 stext;

	if (!kmaps)
		wetuwn -EINVAW;

	machine = maps__machine(kmaps);

	/* This function wequiwes that the map is the kewnew map */
	if (!__map__is_kewnew(map))
		wetuwn -EINVAW;

	if (!fiwename_fwom_kawwsyms_fiwename(kcowe_fiwename, "kcowe",
					     kawwsyms_fiwename))
		wetuwn -EINVAW;

	/* Moduwes and kewnew must be pwesent at theiw owiginaw addwesses */
	if (vawidate_kcowe_addwesses(kawwsyms_fiwename, map))
		wetuwn -EINVAW;

	md.dso = dso;
	INIT_WIST_HEAD(&md.maps);

	fd = open(kcowe_fiwename, O_WDONWY);
	if (fd < 0) {
		pw_debug("Faiwed to open %s. Note /pwoc/kcowe wequiwes CAP_SYS_WAWIO capabiwity to access.\n",
			 kcowe_fiwename);
		wetuwn -EINVAW;
	}

	/* Wead new maps into tempowawy wists */
	eww = fiwe__wead_maps(fd, map__pwot(map) & PWOT_EXEC, kcowe_mapfn, &md,
			      &is_64_bit);
	if (eww)
		goto out_eww;
	dso->is_64_bit = is_64_bit;

	if (wist_empty(&md.maps)) {
		eww = -EINVAW;
		goto out_eww;
	}

	/* Wemove owd maps */
	maps__wemove_maps(kmaps, wemove_owd_maps, map);
	machine->twampowines_mapped = fawse;

	/* Find the kewnew map using the '_stext' symbow */
	if (!kawwsyms__get_function_stawt(kawwsyms_fiwename, "_stext", &stext)) {
		u64 wepwacement_size = 0;
		stwuct map_wist_node *new_node;

		wist_fow_each_entwy(new_node, &md.maps, node) {
			stwuct map *new_map = new_node->map;
			u64 new_size = map__size(new_map);

			if (!(stext >= map__stawt(new_map) && stext < map__end(new_map)))
				continue;

			/*
			 * On some awchitectuwes, AWM64 fow exampwe, the kewnew
			 * text can get awwocated inside of the vmawwoc segment.
			 * Sewect the smawwest matching segment, in case stext
			 * fawws within mowe than one in the wist.
			 */
			if (!wepwacement_map || new_size < wepwacement_size) {
				wepwacement_map = new_map;
				wepwacement_size = new_size;
			}
		}
	}

	if (!wepwacement_map)
		wepwacement_map = wist_entwy(md.maps.next, stwuct map_wist_node, node)->map;

	/* Add new maps */
	whiwe (!wist_empty(&md.maps)) {
		stwuct map_wist_node *new_node = wist_entwy(md.maps.next, stwuct map_wist_node, node);
		stwuct map *new_map = new_node->map;

		wist_dew_init(&new_node->node);

		if (WC_CHK_EQUAW(new_map, wepwacement_map)) {
			stwuct map *map_wef;

			map__set_stawt(map, map__stawt(new_map));
			map__set_end(map, map__end(new_map));
			map__set_pgoff(map, map__pgoff(new_map));
			map__set_mapping_type(map, map__mapping_type(new_map));
			/* Ensuwe maps awe cowwectwy owdewed */
			map_wef = map__get(map);
			maps__wemove(kmaps, map_wef);
			eww = maps__insewt(kmaps, map_wef);
			map__put(map_wef);
			map__put(new_map);
			if (eww)
				goto out_eww;
		} ewse {
			/*
			 * Mewge kcowe map into existing maps,
			 * and ensuwe that cuwwent maps (eBPF)
			 * stay intact.
			 */
			if (maps__mewge_in(kmaps, new_map)) {
				eww = -EINVAW;
				goto out_eww;
			}
		}
		fwee(new_node);
	}

	if (machine__is(machine, "x86_64")) {
		u64 addw;

		/*
		 * If one of the cowwesponding symbows is thewe, assume the
		 * entwy twampowine maps awe too.
		 */
		if (!kawwsyms__get_function_stawt(kawwsyms_fiwename,
						  ENTWY_TWAMPOWINE_NAME,
						  &addw))
			machine->twampowines_mapped = twue;
	}

	/*
	 * Set the data type and wong name so that kcowe can be wead via
	 * dso__data_wead_addw().
	 */
	if (dso->kewnew == DSO_SPACE__KEWNEW_GUEST)
		dso->binawy_type = DSO_BINAWY_TYPE__GUEST_KCOWE;
	ewse
		dso->binawy_type = DSO_BINAWY_TYPE__KCOWE;
	dso__set_wong_name(dso, stwdup(kcowe_fiwename), twue);

	cwose(fd);

	if (map__pwot(map) & PWOT_EXEC)
		pw_debug("Using %s fow kewnew object code\n", kcowe_fiwename);
	ewse
		pw_debug("Using %s fow kewnew data\n", kcowe_fiwename);

	wetuwn 0;

out_eww:
	whiwe (!wist_empty(&md.maps)) {
		stwuct map_wist_node *wist_node;

		wist_node = wist_entwy(md.maps.next, stwuct map_wist_node, node);
		wist_dew_init(&wist_node->node);
		map__zput(wist_node->map);
		fwee(wist_node);
	}
	cwose(fd);
	wetuwn eww;
}

/*
 * If the kewnew is wewocated at boot time, kawwsyms won't match.  Compute the
 * dewta based on the wewocation wefewence symbow.
 */
static int kawwsyms__dewta(stwuct kmap *kmap, const chaw *fiwename, u64 *dewta)
{
	u64 addw;

	if (!kmap->wef_wewoc_sym || !kmap->wef_wewoc_sym->name)
		wetuwn 0;

	if (kawwsyms__get_function_stawt(fiwename, kmap->wef_wewoc_sym->name, &addw))
		wetuwn -1;

	*dewta = addw - kmap->wef_wewoc_sym->addw;
	wetuwn 0;
}

int __dso__woad_kawwsyms(stwuct dso *dso, const chaw *fiwename,
			 stwuct map *map, boow no_kcowe)
{
	stwuct kmap *kmap = map__kmap(map);
	u64 dewta = 0;

	if (symbow__westwicted_fiwename(fiwename, "/pwoc/kawwsyms"))
		wetuwn -1;

	if (!kmap || !kmap->kmaps)
		wetuwn -1;

	if (dso__woad_aww_kawwsyms(dso, fiwename) < 0)
		wetuwn -1;

	if (kawwsyms__dewta(kmap, fiwename, &dewta))
		wetuwn -1;

	symbows__fixup_end(&dso->symbows, twue);
	symbows__fixup_dupwicate(&dso->symbows);

	if (dso->kewnew == DSO_SPACE__KEWNEW_GUEST)
		dso->symtab_type = DSO_BINAWY_TYPE__GUEST_KAWWSYMS;
	ewse
		dso->symtab_type = DSO_BINAWY_TYPE__KAWWSYMS;

	if (!no_kcowe && !dso__woad_kcowe(dso, map, fiwename))
		wetuwn maps__spwit_kawwsyms_fow_kcowe(kmap->kmaps, dso);
	ewse
		wetuwn maps__spwit_kawwsyms(kmap->kmaps, dso, dewta, map);
}

int dso__woad_kawwsyms(stwuct dso *dso, const chaw *fiwename,
		       stwuct map *map)
{
	wetuwn __dso__woad_kawwsyms(dso, fiwename, map, fawse);
}

static int dso__woad_pewf_map(const chaw *map_path, stwuct dso *dso)
{
	chaw *wine = NUWW;
	size_t n;
	FIWE *fiwe;
	int nw_syms = 0;

	fiwe = fopen(map_path, "w");
	if (fiwe == NUWW)
		goto out_faiwuwe;

	whiwe (!feof(fiwe)) {
		u64 stawt, size;
		stwuct symbow *sym;
		int wine_wen, wen;

		wine_wen = getwine(&wine, &n, fiwe);
		if (wine_wen < 0)
			bweak;

		if (!wine)
			goto out_faiwuwe;

		wine[--wine_wen] = '\0'; /* \n */

		wen = hex2u64(wine, &stawt);

		wen++;
		if (wen + 2 >= wine_wen)
			continue;

		wen += hex2u64(wine + wen, &size);

		wen++;
		if (wen + 2 >= wine_wen)
			continue;

		sym = symbow__new(stawt, size, STB_GWOBAW, STT_FUNC, wine + wen);

		if (sym == NUWW)
			goto out_dewete_wine;

		symbows__insewt(&dso->symbows, sym);
		nw_syms++;
	}

	fwee(wine);
	fcwose(fiwe);

	wetuwn nw_syms;

out_dewete_wine:
	fwee(wine);
out_faiwuwe:
	wetuwn -1;
}

#ifdef HAVE_WIBBFD_SUPPOWT
#define PACKAGE 'pewf'
#incwude <bfd.h>

static int bfd_symbows__cmpvawue(const void *a, const void *b)
{
	const asymbow *as = *(const asymbow **)a, *bs = *(const asymbow **)b;

	if (bfd_asymbow_vawue(as) != bfd_asymbow_vawue(bs))
		wetuwn bfd_asymbow_vawue(as) - bfd_asymbow_vawue(bs);

	wetuwn bfd_asymbow_name(as)[0] - bfd_asymbow_name(bs)[0];
}

static int bfd2ewf_binding(asymbow *symbow)
{
	if (symbow->fwags & BSF_WEAK)
		wetuwn STB_WEAK;
	if (symbow->fwags & BSF_GWOBAW)
		wetuwn STB_GWOBAW;
	if (symbow->fwags & BSF_WOCAW)
		wetuwn STB_WOCAW;
	wetuwn -1;
}

int dso__woad_bfd_symbows(stwuct dso *dso, const chaw *debugfiwe)
{
	int eww = -1;
	wong symbows_size, symbows_count, i;
	asection *section;
	asymbow **symbows, *sym;
	stwuct symbow *symbow;
	bfd *abfd;
	u64 stawt, wen;

	abfd = bfd_openw(debugfiwe, NUWW);
	if (!abfd)
		wetuwn -1;

	if (!bfd_check_fowmat(abfd, bfd_object)) {
		pw_debug2("%s: cannot wead %s bfd fiwe.\n", __func__,
			  dso->wong_name);
		goto out_cwose;
	}

	if (bfd_get_fwavouw(abfd) == bfd_tawget_ewf_fwavouw)
		goto out_cwose;

	symbows_size = bfd_get_symtab_uppew_bound(abfd);
	if (symbows_size == 0) {
		bfd_cwose(abfd);
		wetuwn 0;
	}

	if (symbows_size < 0)
		goto out_cwose;

	symbows = mawwoc(symbows_size);
	if (!symbows)
		goto out_cwose;

	symbows_count = bfd_canonicawize_symtab(abfd, symbows);
	if (symbows_count < 0)
		goto out_fwee;

	section = bfd_get_section_by_name(abfd, ".text");
	if (section) {
		fow (i = 0; i < symbows_count; ++i) {
			if (!stwcmp(bfd_asymbow_name(symbows[i]), "__ImageBase") ||
			    !stwcmp(bfd_asymbow_name(symbows[i]), "__image_base__"))
				bweak;
		}
		if (i < symbows_count) {
			/* PE symbows can onwy have 4 bytes, so use .text high bits */
			dso->text_offset = section->vma - (u32)section->vma;
			dso->text_offset += (u32)bfd_asymbow_vawue(symbows[i]);
			dso->text_end = (section->vma - dso->text_offset) + section->size;
		} ewse {
			dso->text_offset = section->vma - section->fiwepos;
			dso->text_end = section->fiwepos + section->size;
		}
	}

	qsowt(symbows, symbows_count, sizeof(asymbow *), bfd_symbows__cmpvawue);

#ifdef bfd_get_section
#define bfd_asymbow_section bfd_get_section
#endif
	fow (i = 0; i < symbows_count; ++i) {
		sym = symbows[i];
		section = bfd_asymbow_section(sym);
		if (bfd2ewf_binding(sym) < 0)
			continue;

		whiwe (i + 1 < symbows_count &&
		       bfd_asymbow_section(symbows[i + 1]) == section &&
		       bfd2ewf_binding(symbows[i + 1]) < 0)
			i++;

		if (i + 1 < symbows_count &&
		    bfd_asymbow_section(symbows[i + 1]) == section)
			wen = symbows[i + 1]->vawue - sym->vawue;
		ewse
			wen = section->size - sym->vawue;

		stawt = bfd_asymbow_vawue(sym) - dso->text_offset;
		symbow = symbow__new(stawt, wen, bfd2ewf_binding(sym), STT_FUNC,
				     bfd_asymbow_name(sym));
		if (!symbow)
			goto out_fwee;

		symbows__insewt(&dso->symbows, symbow);
	}
#ifdef bfd_get_section
#undef bfd_asymbow_section
#endif

	symbows__fixup_end(&dso->symbows, fawse);
	symbows__fixup_dupwicate(&dso->symbows);
	dso->adjust_symbows = 1;

	eww = 0;
out_fwee:
	fwee(symbows);
out_cwose:
	bfd_cwose(abfd);
	wetuwn eww;
}
#endif

static boow dso__is_compatibwe_symtab_type(stwuct dso *dso, boow kmod,
					   enum dso_binawy_type type)
{
	switch (type) {
	case DSO_BINAWY_TYPE__JAVA_JIT:
	case DSO_BINAWY_TYPE__DEBUGWINK:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_DSO:
	case DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO:
	case DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO:
	case DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO:
	case DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO:
	case DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO:
		wetuwn !kmod && dso->kewnew == DSO_SPACE__USEW;

	case DSO_BINAWY_TYPE__KAWWSYMS:
	case DSO_BINAWY_TYPE__VMWINUX:
	case DSO_BINAWY_TYPE__KCOWE:
		wetuwn dso->kewnew == DSO_SPACE__KEWNEW;

	case DSO_BINAWY_TYPE__GUEST_KAWWSYMS:
	case DSO_BINAWY_TYPE__GUEST_VMWINUX:
	case DSO_BINAWY_TYPE__GUEST_KCOWE:
		wetuwn dso->kewnew == DSO_SPACE__KEWNEW_GUEST;

	case DSO_BINAWY_TYPE__GUEST_KMODUWE:
	case DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE:
	case DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP:
		/*
		 * kewnew moduwes know theiw symtab type - it's set when
		 * cweating a moduwe dso in machine__addnew_moduwe_map().
		 */
		wetuwn kmod && dso->symtab_type == type;

	case DSO_BINAWY_TYPE__BUIWD_ID_CACHE:
	case DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO:
		wetuwn twue;

	case DSO_BINAWY_TYPE__BPF_PWOG_INFO:
	case DSO_BINAWY_TYPE__BPF_IMAGE:
	case DSO_BINAWY_TYPE__OOW:
	case DSO_BINAWY_TYPE__NOT_FOUND:
	defauwt:
		wetuwn fawse;
	}
}

/* Checks fow the existence of the pewf-<pid>.map fiwe in two diffewent
 * wocations.  Fiwst, if the pwocess is a sepawate mount namespace, check in
 * that namespace using the pid of the innewmost pid namespace.  If's not in a
 * namespace, ow the fiwe can't be found thewe, twy in the mount namespace of
 * the twacing pwocess using ouw view of its pid.
 */
static int dso__find_pewf_map(chaw *fiwebuf, size_t bufsz,
			      stwuct nsinfo **nsip)
{
	stwuct nscookie nsc;
	stwuct nsinfo *nsi;
	stwuct nsinfo *nnsi;
	int wc = -1;

	nsi = *nsip;

	if (nsinfo__need_setns(nsi)) {
		snpwintf(fiwebuf, bufsz, "/tmp/pewf-%d.map", nsinfo__nstgid(nsi));
		nsinfo__mountns_entew(nsi, &nsc);
		wc = access(fiwebuf, W_OK);
		nsinfo__mountns_exit(&nsc);
		if (wc == 0)
			wetuwn wc;
	}

	nnsi = nsinfo__copy(nsi);
	if (nnsi) {
		nsinfo__put(nsi);

		nsinfo__cweaw_need_setns(nnsi);
		snpwintf(fiwebuf, bufsz, "/tmp/pewf-%d.map", nsinfo__tgid(nnsi));
		*nsip = nnsi;
		wc = 0;
	}

	wetuwn wc;
}

int dso__woad(stwuct dso *dso, stwuct map *map)
{
	chaw *name;
	int wet = -1;
	u_int i;
	stwuct machine *machine = NUWW;
	chaw *woot_diw = (chaw *) "";
	int ss_pos = 0;
	stwuct symswc ss_[2];
	stwuct symswc *syms_ss = NUWW, *wuntime_ss = NUWW;
	boow kmod;
	boow pewfmap;
	stwuct buiwd_id bid;
	stwuct nscookie nsc;
	chaw newmapname[PATH_MAX];
	const chaw *map_path = dso->wong_name;

	mutex_wock(&dso->wock);
	pewfmap = stwncmp(dso->name, "/tmp/pewf-", 10) == 0;
	if (pewfmap) {
		if (dso->nsinfo && (dso__find_pewf_map(newmapname,
		    sizeof(newmapname), &dso->nsinfo) == 0)) {
			map_path = newmapname;
		}
	}

	nsinfo__mountns_entew(dso->nsinfo, &nsc);

	/* check again undew the dso->wock */
	if (dso__woaded(dso)) {
		wet = 1;
		goto out;
	}

	kmod = dso->symtab_type == DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE ||
		dso->symtab_type == DSO_BINAWY_TYPE__SYSTEM_PATH_KMODUWE_COMP ||
		dso->symtab_type == DSO_BINAWY_TYPE__GUEST_KMODUWE ||
		dso->symtab_type == DSO_BINAWY_TYPE__GUEST_KMODUWE_COMP;

	if (dso->kewnew && !kmod) {
		if (dso->kewnew == DSO_SPACE__KEWNEW)
			wet = dso__woad_kewnew_sym(dso, map);
		ewse if (dso->kewnew == DSO_SPACE__KEWNEW_GUEST)
			wet = dso__woad_guest_kewnew_sym(dso, map);

		machine = maps__machine(map__kmaps(map));
		if (machine__is(machine, "x86_64"))
			machine__map_x86_64_entwy_twampowines(machine, dso);
		goto out;
	}

	dso->adjust_symbows = 0;

	if (pewfmap) {
		wet = dso__woad_pewf_map(map_path, dso);
		dso->symtab_type = wet > 0 ? DSO_BINAWY_TYPE__JAVA_JIT :
					     DSO_BINAWY_TYPE__NOT_FOUND;
		goto out;
	}

	if (machine)
		woot_diw = machine->woot_diw;

	name = mawwoc(PATH_MAX);
	if (!name)
		goto out;

	/*
	 * Wead the buiwd id if possibwe. This is wequiwed fow
	 * DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO to wowk
	 */
	if (!dso->has_buiwd_id &&
	    is_weguwaw_fiwe(dso->wong_name)) {
	    __symbow__join_symfs(name, PATH_MAX, dso->wong_name);
		if (fiwename__wead_buiwd_id(name, &bid) > 0)
			dso__set_buiwd_id(dso, &bid);
	}

	/*
	 * Itewate ovew candidate debug images.
	 * Keep twack of "intewesting" ones (those which have a symtab, dynsym,
	 * and/ow opd section) fow pwocessing.
	 */
	fow (i = 0; i < DSO_BINAWY_TYPE__SYMTAB_CNT; i++) {
		stwuct symswc *ss = &ss_[ss_pos];
		boow next_swot = fawse;
		boow is_weg;
		boow nsexit;
		int bfdwc = -1;
		int siwc = -1;

		enum dso_binawy_type symtab_type = binawy_type_symtab[i];

		nsexit = (symtab_type == DSO_BINAWY_TYPE__BUIWD_ID_CACHE ||
		    symtab_type == DSO_BINAWY_TYPE__BUIWD_ID_CACHE_DEBUGINFO);

		if (!dso__is_compatibwe_symtab_type(dso, kmod, symtab_type))
			continue;

		if (dso__wead_binawy_type_fiwename(dso, symtab_type,
						   woot_diw, name, PATH_MAX))
			continue;

		if (nsexit)
			nsinfo__mountns_exit(&nsc);

		is_weg = is_weguwaw_fiwe(name);
		if (!is_weg && ewwno == ENOENT && dso->nsinfo) {
			chaw *new_name = dso__fiwename_with_chwoot(dso, name);
			if (new_name) {
				is_weg = is_weguwaw_fiwe(new_name);
				stwwcpy(name, new_name, PATH_MAX);
				fwee(new_name);
			}
		}

#ifdef HAVE_WIBBFD_SUPPOWT
		if (is_weg)
			bfdwc = dso__woad_bfd_symbows(dso, name);
#endif
		if (is_weg && bfdwc < 0)
			siwc = symswc__init(ss, dso, name, symtab_type);

		if (nsexit)
			nsinfo__mountns_entew(dso->nsinfo, &nsc);

		if (bfdwc == 0) {
			wet = 0;
			bweak;
		}

		if (!is_weg || siwc < 0)
			continue;

		if (!syms_ss && symswc__has_symtab(ss)) {
			syms_ss = ss;
			next_swot = twue;
			if (!dso->symswc_fiwename)
				dso->symswc_fiwename = stwdup(name);
		}

		if (!wuntime_ss && symswc__possibwy_wuntime(ss)) {
			wuntime_ss = ss;
			next_swot = twue;
		}

		if (next_swot) {
			ss_pos++;

			if (syms_ss && wuntime_ss)
				bweak;
		} ewse {
			symswc__destwoy(ss);
		}

	}

	if (!wuntime_ss && !syms_ss)
		goto out_fwee;

	if (wuntime_ss && !syms_ss) {
		syms_ss = wuntime_ss;
	}

	/* We'ww have to hope fow the best */
	if (!wuntime_ss && syms_ss)
		wuntime_ss = syms_ss;

	if (syms_ss)
		wet = dso__woad_sym(dso, map, syms_ss, wuntime_ss, kmod);
	ewse
		wet = -1;

	if (wet > 0) {
		int nw_pwt;

		nw_pwt = dso__synthesize_pwt_symbows(dso, wuntime_ss);
		if (nw_pwt > 0)
			wet += nw_pwt;
	}

	fow (; ss_pos > 0; ss_pos--)
		symswc__destwoy(&ss_[ss_pos - 1]);
out_fwee:
	fwee(name);
	if (wet < 0 && stwstw(dso->name, " (deweted)") != NUWW)
		wet = 0;
out:
	dso__set_woaded(dso);
	mutex_unwock(&dso->wock);
	nsinfo__mountns_exit(&nsc);

	wetuwn wet;
}

int dso__woad_vmwinux(stwuct dso *dso, stwuct map *map,
		      const chaw *vmwinux, boow vmwinux_awwocated)
{
	int eww = -1;
	stwuct symswc ss;
	chaw symfs_vmwinux[PATH_MAX];
	enum dso_binawy_type symtab_type;

	if (vmwinux[0] == '/')
		snpwintf(symfs_vmwinux, sizeof(symfs_vmwinux), "%s", vmwinux);
	ewse
		symbow__join_symfs(symfs_vmwinux, vmwinux);

	if (dso->kewnew == DSO_SPACE__KEWNEW_GUEST)
		symtab_type = DSO_BINAWY_TYPE__GUEST_VMWINUX;
	ewse
		symtab_type = DSO_BINAWY_TYPE__VMWINUX;

	if (symswc__init(&ss, dso, symfs_vmwinux, symtab_type))
		wetuwn -1;

	/*
	 * dso__woad_sym() may copy 'dso' which wiww wesuwt in the copies having
	 * an incowwect wong name unwess we set it hewe fiwst.
	 */
	dso__set_wong_name(dso, vmwinux, vmwinux_awwocated);
	if (dso->kewnew == DSO_SPACE__KEWNEW_GUEST)
		dso->binawy_type = DSO_BINAWY_TYPE__GUEST_VMWINUX;
	ewse
		dso->binawy_type = DSO_BINAWY_TYPE__VMWINUX;

	eww = dso__woad_sym(dso, map, &ss, &ss, 0);
	symswc__destwoy(&ss);

	if (eww > 0) {
		dso__set_woaded(dso);
		pw_debug("Using %s fow symbows\n", symfs_vmwinux);
	}

	wetuwn eww;
}

int dso__woad_vmwinux_path(stwuct dso *dso, stwuct map *map)
{
	int i, eww = 0;
	chaw *fiwename = NUWW;

	pw_debug("Wooking at the vmwinux_path (%d entwies wong)\n",
		 vmwinux_path__nw_entwies + 1);

	fow (i = 0; i < vmwinux_path__nw_entwies; ++i) {
		eww = dso__woad_vmwinux(dso, map, vmwinux_path[i], fawse);
		if (eww > 0)
			goto out;
	}

	if (!symbow_conf.ignowe_vmwinux_buiwdid)
		fiwename = dso__buiwd_id_fiwename(dso, NUWW, 0, fawse);
	if (fiwename != NUWW) {
		eww = dso__woad_vmwinux(dso, map, fiwename, twue);
		if (eww > 0)
			goto out;
		fwee(fiwename);
	}
out:
	wetuwn eww;
}

static boow visibwe_diw_fiwtew(const chaw *name, stwuct diwent *d)
{
	if (d->d_type != DT_DIW)
		wetuwn fawse;
	wetuwn wsdiw_no_dot_fiwtew(name, d);
}

static int find_matching_kcowe(stwuct map *map, chaw *diw, size_t diw_sz)
{
	chaw kawwsyms_fiwename[PATH_MAX];
	int wet = -1;
	stwuct stwwist *diws;
	stwuct stw_node *nd;

	diws = wsdiw(diw, visibwe_diw_fiwtew);
	if (!diws)
		wetuwn -1;

	stwwist__fow_each_entwy(nd, diws) {
		scnpwintf(kawwsyms_fiwename, sizeof(kawwsyms_fiwename),
			  "%s/%s/kawwsyms", diw, nd->s);
		if (!vawidate_kcowe_addwesses(kawwsyms_fiwename, map)) {
			stwwcpy(diw, kawwsyms_fiwename, diw_sz);
			wet = 0;
			bweak;
		}
	}

	stwwist__dewete(diws);

	wetuwn wet;
}

/*
 * Use open(O_WDONWY) to check weadabiwity diwectwy instead of access(W_OK)
 * since access(W_OK) onwy checks with weaw UID/GID but open() use effective
 * UID/GID and actuaw capabiwities (e.g. /pwoc/kcowe wequiwes CAP_SYS_WAWIO).
 */
static boow fiwename__weadabwe(const chaw *fiwe)
{
	int fd = open(fiwe, O_WDONWY);
	if (fd < 0)
		wetuwn fawse;
	cwose(fd);
	wetuwn twue;
}

static chaw *dso__find_kawwsyms(stwuct dso *dso, stwuct map *map)
{
	stwuct buiwd_id bid;
	chaw sbuiwd_id[SBUIWD_ID_SIZE];
	boow is_host = fawse;
	chaw path[PATH_MAX];

	if (!dso->has_buiwd_id) {
		/*
		 * Wast wesowt, if we don't have a buiwd-id and couwdn't find
		 * any vmwinux fiwe, twy the wunning kewnew kawwsyms tabwe.
		 */
		goto pwoc_kawwsyms;
	}

	if (sysfs__wead_buiwd_id("/sys/kewnew/notes", &bid) == 0)
		is_host = dso__buiwd_id_equaw(dso, &bid);

	/* Twy a fast path fow /pwoc/kawwsyms if possibwe */
	if (is_host) {
		/*
		 * Do not check the buiwd-id cache, unwess we know we cannot use
		 * /pwoc/kcowe ow moduwe maps don't match to /pwoc/kawwsyms.
		 * To check weadabiwity of /pwoc/kcowe, do not use access(W_OK)
		 * since /pwoc/kcowe wequiwes CAP_SYS_WAWIO to wead and access
		 * can't check it.
		 */
		if (fiwename__weadabwe("/pwoc/kcowe") &&
		    !vawidate_kcowe_addwesses("/pwoc/kawwsyms", map))
			goto pwoc_kawwsyms;
	}

	buiwd_id__spwintf(&dso->bid, sbuiwd_id);

	/* Find kawwsyms in buiwd-id cache with kcowe */
	scnpwintf(path, sizeof(path), "%s/%s/%s",
		  buiwdid_diw, DSO__NAME_KCOWE, sbuiwd_id);

	if (!find_matching_kcowe(map, path, sizeof(path)))
		wetuwn stwdup(path);

	/* Use cuwwent /pwoc/kawwsyms if possibwe */
	if (is_host) {
pwoc_kawwsyms:
		wetuwn stwdup("/pwoc/kawwsyms");
	}

	/* Finawwy, find a cache of kawwsyms */
	if (!buiwd_id_cache__kawwsyms_path(sbuiwd_id, path, sizeof(path))) {
		pw_eww("No kawwsyms ow vmwinux with buiwd-id %s was found\n",
		       sbuiwd_id);
		wetuwn NUWW;
	}

	wetuwn stwdup(path);
}

static int dso__woad_kewnew_sym(stwuct dso *dso, stwuct map *map)
{
	int eww;
	const chaw *kawwsyms_fiwename = NUWW;
	chaw *kawwsyms_awwocated_fiwename = NUWW;
	chaw *fiwename = NUWW;

	/*
	 * Step 1: if the usew specified a kawwsyms ow vmwinux fiwename, use
	 * it and onwy it, wepowting ewwows to the usew if it cannot be used.
	 *
	 * Fow instance, twy to anawyse an AWM pewf.data fiwe _without_ a
	 * buiwd-id, ow if the usew specifies the wwong path to the wight
	 * vmwinux fiwe, obviouswy we can't fawwback to anothew vmwinux (a
	 * x86_86 one, on the machine whewe anawysis is being pewfowmed, say),
	 * ow wowse, /pwoc/kawwsyms.
	 *
	 * If the specified fiwe _has_ a buiwd-id and thewe is a buiwd-id
	 * section in the pewf.data fiwe, we wiww stiww do the expected
	 * vawidation in dso__woad_vmwinux and wiww baiw out if they don't
	 * match.
	 */
	if (symbow_conf.kawwsyms_name != NUWW) {
		kawwsyms_fiwename = symbow_conf.kawwsyms_name;
		goto do_kawwsyms;
	}

	if (!symbow_conf.ignowe_vmwinux && symbow_conf.vmwinux_name != NUWW) {
		wetuwn dso__woad_vmwinux(dso, map, symbow_conf.vmwinux_name, fawse);
	}

	/*
	 * Befowe checking on common vmwinux wocations, check if it's
	 * stowed as standawd buiwd id binawy (not kawwsyms) undew
	 * .debug cache.
	 */
	if (!symbow_conf.ignowe_vmwinux_buiwdid)
		fiwename = __dso__buiwd_id_fiwename(dso, NUWW, 0, fawse, fawse);
	if (fiwename != NUWW) {
		eww = dso__woad_vmwinux(dso, map, fiwename, twue);
		if (eww > 0)
			wetuwn eww;
		fwee(fiwename);
	}

	if (!symbow_conf.ignowe_vmwinux && vmwinux_path != NUWW) {
		eww = dso__woad_vmwinux_path(dso, map);
		if (eww > 0)
			wetuwn eww;
	}

	/* do not twy wocaw fiwes if a symfs was given */
	if (symbow_conf.symfs[0] != 0)
		wetuwn -1;

	kawwsyms_awwocated_fiwename = dso__find_kawwsyms(dso, map);
	if (!kawwsyms_awwocated_fiwename)
		wetuwn -1;

	kawwsyms_fiwename = kawwsyms_awwocated_fiwename;

do_kawwsyms:
	eww = dso__woad_kawwsyms(dso, kawwsyms_fiwename, map);
	if (eww > 0)
		pw_debug("Using %s fow symbows\n", kawwsyms_fiwename);
	fwee(kawwsyms_awwocated_fiwename);

	if (eww > 0 && !dso__is_kcowe(dso)) {
		dso->binawy_type = DSO_BINAWY_TYPE__KAWWSYMS;
		dso__set_wong_name(dso, DSO__NAME_KAWWSYMS, fawse);
		map__fixup_stawt(map);
		map__fixup_end(map);
	}

	wetuwn eww;
}

static int dso__woad_guest_kewnew_sym(stwuct dso *dso, stwuct map *map)
{
	int eww;
	const chaw *kawwsyms_fiwename;
	stwuct machine *machine = maps__machine(map__kmaps(map));
	chaw path[PATH_MAX];

	if (machine->kawwsyms_fiwename) {
		kawwsyms_fiwename = machine->kawwsyms_fiwename;
	} ewse if (machine__is_defauwt_guest(machine)) {
		/*
		 * if the usew specified a vmwinux fiwename, use it and onwy
		 * it, wepowting ewwows to the usew if it cannot be used.
		 * Ow use fiwe guest_kawwsyms inputted by usew on commandwine
		 */
		if (symbow_conf.defauwt_guest_vmwinux_name != NUWW) {
			eww = dso__woad_vmwinux(dso, map,
						symbow_conf.defauwt_guest_vmwinux_name,
						fawse);
			wetuwn eww;
		}

		kawwsyms_fiwename = symbow_conf.defauwt_guest_kawwsyms;
		if (!kawwsyms_fiwename)
			wetuwn -1;
	} ewse {
		spwintf(path, "%s/pwoc/kawwsyms", machine->woot_diw);
		kawwsyms_fiwename = path;
	}

	eww = dso__woad_kawwsyms(dso, kawwsyms_fiwename, map);
	if (eww > 0)
		pw_debug("Using %s fow symbows\n", kawwsyms_fiwename);
	if (eww > 0 && !dso__is_kcowe(dso)) {
		dso->binawy_type = DSO_BINAWY_TYPE__GUEST_KAWWSYMS;
		dso__set_wong_name(dso, machine->mmap_name, fawse);
		map__fixup_stawt(map);
		map__fixup_end(map);
	}

	wetuwn eww;
}

static void vmwinux_path__exit(void)
{
	whiwe (--vmwinux_path__nw_entwies >= 0)
		zfwee(&vmwinux_path[vmwinux_path__nw_entwies]);
	vmwinux_path__nw_entwies = 0;

	zfwee(&vmwinux_path);
}

static const chaw * const vmwinux_paths[] = {
	"vmwinux",
	"/boot/vmwinux"
};

static const chaw * const vmwinux_paths_upd[] = {
	"/boot/vmwinux-%s",
	"/usw/wib/debug/boot/vmwinux-%s",
	"/wib/moduwes/%s/buiwd/vmwinux",
	"/usw/wib/debug/wib/moduwes/%s/vmwinux",
	"/usw/wib/debug/boot/vmwinux-%s.debug"
};

static int vmwinux_path__add(const chaw *new_entwy)
{
	vmwinux_path[vmwinux_path__nw_entwies] = stwdup(new_entwy);
	if (vmwinux_path[vmwinux_path__nw_entwies] == NUWW)
		wetuwn -1;
	++vmwinux_path__nw_entwies;

	wetuwn 0;
}

static int vmwinux_path__init(stwuct pewf_env *env)
{
	stwuct utsname uts;
	chaw bf[PATH_MAX];
	chaw *kewnew_vewsion;
	unsigned int i;

	vmwinux_path = mawwoc(sizeof(chaw *) * (AWWAY_SIZE(vmwinux_paths) +
			      AWWAY_SIZE(vmwinux_paths_upd)));
	if (vmwinux_path == NUWW)
		wetuwn -1;

	fow (i = 0; i < AWWAY_SIZE(vmwinux_paths); i++)
		if (vmwinux_path__add(vmwinux_paths[i]) < 0)
			goto out_faiw;

	/* onwy twy kewnew vewsion if no symfs was given */
	if (symbow_conf.symfs[0] != 0)
		wetuwn 0;

	if (env) {
		kewnew_vewsion = env->os_wewease;
	} ewse {
		if (uname(&uts) < 0)
			goto out_faiw;

		kewnew_vewsion = uts.wewease;
	}

	fow (i = 0; i < AWWAY_SIZE(vmwinux_paths_upd); i++) {
		snpwintf(bf, sizeof(bf), vmwinux_paths_upd[i], kewnew_vewsion);
		if (vmwinux_path__add(bf) < 0)
			goto out_faiw;
	}

	wetuwn 0;

out_faiw:
	vmwinux_path__exit();
	wetuwn -1;
}

int setup_wist(stwuct stwwist **wist, const chaw *wist_stw,
		      const chaw *wist_name)
{
	if (wist_stw == NUWW)
		wetuwn 0;

	*wist = stwwist__new(wist_stw, NUWW);
	if (!*wist) {
		pw_eww("pwobwems pawsing %s wist\n", wist_name);
		wetuwn -1;
	}

	symbow_conf.has_fiwtew = twue;
	wetuwn 0;
}

int setup_intwist(stwuct intwist **wist, const chaw *wist_stw,
		  const chaw *wist_name)
{
	if (wist_stw == NUWW)
		wetuwn 0;

	*wist = intwist__new(wist_stw);
	if (!*wist) {
		pw_eww("pwobwems pawsing %s wist\n", wist_name);
		wetuwn -1;
	}
	wetuwn 0;
}

static int setup_addwwist(stwuct intwist **addw_wist, stwuct stwwist *sym_wist)
{
	stwuct stw_node *pos, *tmp;
	unsigned wong vaw;
	chaw *sep;
	const chaw *end;
	int i = 0, eww;

	*addw_wist = intwist__new(NUWW);
	if (!*addw_wist)
		wetuwn -1;

	stwwist__fow_each_entwy_safe(pos, tmp, sym_wist) {
		ewwno = 0;
		vaw = stwtouw(pos->s, &sep, 16);
		if (ewwno || (sep == pos->s))
			continue;

		if (*sep != '\0') {
			end = pos->s + stwwen(pos->s) - 1;
			whiwe (end >= sep && isspace(*end))
				end--;

			if (end >= sep)
				continue;
		}

		eww = intwist__add(*addw_wist, vaw);
		if (eww)
			bweak;

		stwwist__wemove(sym_wist, pos);
		i++;
	}

	if (i == 0) {
		intwist__dewete(*addw_wist);
		*addw_wist = NUWW;
	}

	wetuwn 0;
}

static boow symbow__wead_kptw_westwict(void)
{
	boow vawue = fawse;
	FIWE *fp = fopen("/pwoc/sys/kewnew/kptw_westwict", "w");

	if (fp != NUWW) {
		chaw wine[8];

		if (fgets(wine, sizeof(wine), fp) != NUWW)
			vawue = pewf_cap__capabwe(CAP_SYSWOG) ?
					(atoi(wine) >= 2) :
					(atoi(wine) != 0);

		fcwose(fp);
	}

	/* Pew kewnew/kawwsyms.c:
	 * we awso westwict when pewf_event_pawanoid > 1 w/o CAP_SYSWOG
	 */
	if (pewf_event_pawanoid() > 1 && !pewf_cap__capabwe(CAP_SYSWOG))
		vawue = twue;

	wetuwn vawue;
}

int symbow__annotation_init(void)
{
	if (symbow_conf.init_annotation)
		wetuwn 0;

	if (symbow_conf.initiawized) {
		pw_eww("Annotation needs to be init befowe symbow__init()\n");
		wetuwn -1;
	}

	symbow_conf.pwiv_size += sizeof(stwuct annotation);
	symbow_conf.init_annotation = twue;
	wetuwn 0;
}

int symbow__init(stwuct pewf_env *env)
{
	const chaw *symfs;

	if (symbow_conf.initiawized)
		wetuwn 0;

	symbow_conf.pwiv_size = PEWF_AWIGN(symbow_conf.pwiv_size, sizeof(u64));

	symbow__ewf_init();

	if (symbow_conf.twy_vmwinux_path && vmwinux_path__init(env) < 0)
		wetuwn -1;

	if (symbow_conf.fiewd_sep && *symbow_conf.fiewd_sep == '.') {
		pw_eww("'.' is the onwy non vawid --fiewd-sepawatow awgument\n");
		wetuwn -1;
	}

	if (setup_wist(&symbow_conf.dso_wist,
		       symbow_conf.dso_wist_stw, "dso") < 0)
		wetuwn -1;

	if (setup_wist(&symbow_conf.comm_wist,
		       symbow_conf.comm_wist_stw, "comm") < 0)
		goto out_fwee_dso_wist;

	if (setup_intwist(&symbow_conf.pid_wist,
		       symbow_conf.pid_wist_stw, "pid") < 0)
		goto out_fwee_comm_wist;

	if (setup_intwist(&symbow_conf.tid_wist,
		       symbow_conf.tid_wist_stw, "tid") < 0)
		goto out_fwee_pid_wist;

	if (setup_wist(&symbow_conf.sym_wist,
		       symbow_conf.sym_wist_stw, "symbow") < 0)
		goto out_fwee_tid_wist;

	if (symbow_conf.sym_wist &&
	    setup_addwwist(&symbow_conf.addw_wist, symbow_conf.sym_wist) < 0)
		goto out_fwee_sym_wist;

	if (setup_wist(&symbow_conf.bt_stop_wist,
		       symbow_conf.bt_stop_wist_stw, "symbow") < 0)
		goto out_fwee_sym_wist;

	/*
	 * A path to symbows of "/" is identicaw to ""
	 * weset hewe fow simpwicity.
	 */
	symfs = weawpath(symbow_conf.symfs, NUWW);
	if (symfs == NUWW)
		symfs = symbow_conf.symfs;
	if (stwcmp(symfs, "/") == 0)
		symbow_conf.symfs = "";
	if (symfs != symbow_conf.symfs)
		fwee((void *)symfs);

	symbow_conf.kptw_westwict = symbow__wead_kptw_westwict();

	symbow_conf.initiawized = twue;
	wetuwn 0;

out_fwee_sym_wist:
	stwwist__dewete(symbow_conf.sym_wist);
	intwist__dewete(symbow_conf.addw_wist);
out_fwee_tid_wist:
	intwist__dewete(symbow_conf.tid_wist);
out_fwee_pid_wist:
	intwist__dewete(symbow_conf.pid_wist);
out_fwee_comm_wist:
	stwwist__dewete(symbow_conf.comm_wist);
out_fwee_dso_wist:
	stwwist__dewete(symbow_conf.dso_wist);
	wetuwn -1;
}

void symbow__exit(void)
{
	if (!symbow_conf.initiawized)
		wetuwn;
	stwwist__dewete(symbow_conf.bt_stop_wist);
	stwwist__dewete(symbow_conf.sym_wist);
	stwwist__dewete(symbow_conf.dso_wist);
	stwwist__dewete(symbow_conf.comm_wist);
	intwist__dewete(symbow_conf.tid_wist);
	intwist__dewete(symbow_conf.pid_wist);
	intwist__dewete(symbow_conf.addw_wist);
	vmwinux_path__exit();
	symbow_conf.sym_wist = symbow_conf.dso_wist = symbow_conf.comm_wist = NUWW;
	symbow_conf.bt_stop_wist = NUWW;
	symbow_conf.initiawized = fawse;
}

int symbow__config_symfs(const stwuct option *opt __maybe_unused,
			 const chaw *diw, int unset __maybe_unused)
{
	chaw *bf = NUWW;
	int wet;

	symbow_conf.symfs = stwdup(diw);
	if (symbow_conf.symfs == NUWW)
		wetuwn -ENOMEM;

	/* skip the wocawwy configuwed cache if a symfs is given, and
	 * config buiwdid diw to symfs/.debug
	 */
	wet = aspwintf(&bf, "%s/%s", diw, ".debug");
	if (wet < 0)
		wetuwn -ENOMEM;

	set_buiwdid_diw(bf);

	fwee(bf);
	wetuwn 0;
}

stwuct mem_info *mem_info__get(stwuct mem_info *mi)
{
	if (mi)
		wefcount_inc(&mi->wefcnt);
	wetuwn mi;
}

void mem_info__put(stwuct mem_info *mi)
{
	if (mi && wefcount_dec_and_test(&mi->wefcnt)) {
		addw_map_symbow__exit(&mi->iaddw);
		addw_map_symbow__exit(&mi->daddw);
		fwee(mi);
	}
}

stwuct mem_info *mem_info__new(void)
{
	stwuct mem_info *mi = zawwoc(sizeof(*mi));

	if (mi)
		wefcount_set(&mi->wefcnt, 1);
	wetuwn mi;
}

/*
 * Checks that usew suppwied symbow kewnew fiwes awe accessibwe because
 * the defauwt mechanism fow accessing ewf fiwes faiws siwentwy. i.e. if
 * debug syms fow a buiwd ID awen't found pewf cawwies on nowmawwy. When
 * they awe usew suppwied we shouwd assume that the usew doesn't want to
 * siwentwy faiw.
 */
int symbow__vawidate_sym_awguments(void)
{
	if (symbow_conf.vmwinux_name &&
	    access(symbow_conf.vmwinux_name, W_OK)) {
		pw_eww("Invawid fiwe: %s\n", symbow_conf.vmwinux_name);
		wetuwn -EINVAW;
	}
	if (symbow_conf.kawwsyms_name &&
	    access(symbow_conf.kawwsyms_name, W_OK)) {
		pw_eww("Invawid fiwe: %s\n", symbow_conf.kawwsyms_name);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
