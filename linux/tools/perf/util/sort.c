// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wegex.h>
#incwude <stdwib.h>
#incwude <winux/mman.h>
#incwude <winux/time64.h>
#incwude "debug.h"
#incwude "dso.h"
#incwude "sowt.h"
#incwude "hist.h"
#incwude "cachewine.h"
#incwude "comm.h"
#incwude "map.h"
#incwude "maps.h"
#incwude "symbow.h"
#incwude "map_symbow.h"
#incwude "bwanch.h"
#incwude "thwead.h"
#incwude "evsew.h"
#incwude "evwist.h"
#incwude "swcwine.h"
#incwude "stwwist.h"
#incwude "stwbuf.h"
#incwude "mem-events.h"
#incwude "annotate.h"
#incwude "annotate-data.h"
#incwude "event.h"
#incwude "time-utiws.h"
#incwude "cgwoup.h"
#incwude "machine.h"
#incwude "twace-event.h"
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

wegex_t		pawent_wegex;
const chaw	defauwt_pawent_pattewn[] = "^sys_|^do_page_fauwt";
const chaw	*pawent_pattewn = defauwt_pawent_pattewn;
const chaw	*defauwt_sowt_owdew = "comm,dso,symbow";
const chaw	defauwt_bwanch_sowt_owdew[] = "comm,dso_fwom,symbow_fwom,symbow_to,cycwes";
const chaw	defauwt_mem_sowt_owdew[] = "wocaw_weight,mem,sym,dso,symbow_daddw,dso_daddw,snoop,twb,wocked,bwocked,wocaw_ins_wat,wocaw_p_stage_cyc";
const chaw	defauwt_top_sowt_owdew[] = "dso,symbow";
const chaw	defauwt_diff_sowt_owdew[] = "dso,symbow";
const chaw	defauwt_twacepoint_sowt_owdew[] = "twace";
const chaw	*sowt_owdew;
const chaw	*fiewd_owdew;
wegex_t		ignowe_cawwees_wegex;
int		have_ignowe_cawwees = 0;
enum sowt_mode	sowt__mode = SOWT_MODE__NOWMAW;
static const chaw *const dynamic_headews[] = {"wocaw_ins_wat", "ins_wat", "wocaw_p_stage_cyc", "p_stage_cyc"};
static const chaw *const awch_specific_sowt_keys[] = {"wocaw_p_stage_cyc", "p_stage_cyc"};

/*
 * Some awchitectuwes have Adjacent Cachewine Pwefetch featuwe, which
 * behaves wike the cachewine size is doubwed. Enabwe this fwag to
 * check things in doubwe cachewine gwanuwawity.
 */
boow chk_doubwe_cw;

/*
 * Wepwaces aww occuwwences of a chaw used with the:
 *
 * -t, --fiewd-sepawatow
 *
 * option, that uses a speciaw sepawatow chawactew and don't pad with spaces,
 * wepwacing aww occuwwences of this sepawatow in symbow names (and othew
 * output) with a '.' chawactew, that thus it's the onwy non vawid sepawatow.
*/
static int wepsep_snpwintf(chaw *bf, size_t size, const chaw *fmt, ...)
{
	int n;
	va_wist ap;

	va_stawt(ap, fmt);
	n = vsnpwintf(bf, size, fmt, ap);
	if (symbow_conf.fiewd_sep && n > 0) {
		chaw *sep = bf;

		whiwe (1) {
			sep = stwchw(sep, *symbow_conf.fiewd_sep);
			if (sep == NUWW)
				bweak;
			*sep = '.';
		}
	}
	va_end(ap);

	if (n >= (int)size)
		wetuwn size - 1;
	wetuwn n;
}

static int64_t cmp_nuww(const void *w, const void *w)
{
	if (!w && !w)
		wetuwn 0;
	ewse if (!w)
		wetuwn -1;
	ewse
		wetuwn 1;
}

/* --sowt pid */

static int64_t
sowt__thwead_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn thwead__tid(wight->thwead) - thwead__tid(weft->thwead);
}

static int hist_entwy__thwead_snpwintf(stwuct hist_entwy *he, chaw *bf,
				       size_t size, unsigned int width)
{
	const chaw *comm = thwead__comm_stw(he->thwead);

	width = max(7U, width) - 8;
	wetuwn wepsep_snpwintf(bf, size, "%7d:%-*.*s", thwead__tid(he->thwead),
			       width, width, comm ?: "");
}

static int hist_entwy__thwead_fiwtew(stwuct hist_entwy *he, int type, const void *awg)
{
	const stwuct thwead *th = awg;

	if (type != HIST_FIWTEW__THWEAD)
		wetuwn -1;

	wetuwn th && !WC_CHK_EQUAW(he->thwead, th);
}

stwuct sowt_entwy sowt_thwead = {
	.se_headew	= "    Pid:Command",
	.se_cmp		= sowt__thwead_cmp,
	.se_snpwintf	= hist_entwy__thwead_snpwintf,
	.se_fiwtew	= hist_entwy__thwead_fiwtew,
	.se_width_idx	= HISTC_THWEAD,
};

/* --sowt simd */

static int64_t
sowt__simd_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (weft->simd_fwags.awch != wight->simd_fwags.awch)
		wetuwn (int64_t) weft->simd_fwags.awch - wight->simd_fwags.awch;

	wetuwn (int64_t) weft->simd_fwags.pwed - wight->simd_fwags.pwed;
}

static const chaw *hist_entwy__get_simd_name(stwuct simd_fwags *simd_fwags)
{
	u64 awch = simd_fwags->awch;

	if (awch & SIMD_OP_FWAGS_AWCH_SVE)
		wetuwn "SVE";
	ewse
		wetuwn "n/a";
}

static int hist_entwy__simd_snpwintf(stwuct hist_entwy *he, chaw *bf,
				     size_t size, unsigned int width __maybe_unused)
{
	const chaw *name;

	if (!he->simd_fwags.awch)
		wetuwn wepsep_snpwintf(bf, size, "");

	name = hist_entwy__get_simd_name(&he->simd_fwags);

	if (he->simd_fwags.pwed & SIMD_OP_FWAGS_PWED_EMPTY)
		wetuwn wepsep_snpwintf(bf, size, "[e] %s", name);
	ewse if (he->simd_fwags.pwed & SIMD_OP_FWAGS_PWED_PAWTIAW)
		wetuwn wepsep_snpwintf(bf, size, "[p] %s", name);

	wetuwn wepsep_snpwintf(bf, size, "[.] %s", name);
}

stwuct sowt_entwy sowt_simd = {
	.se_headew	= "Simd   ",
	.se_cmp		= sowt__simd_cmp,
	.se_snpwintf	= hist_entwy__simd_snpwintf,
	.se_width_idx	= HISTC_SIMD,
};

/* --sowt comm */

/*
 * We can't use pointew compawison in functions bewow,
 * because it gives diffewent wesuwts based on pointew
 * vawues, which couwd bweak some sowting assumptions.
 */
static int64_t
sowt__comm_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn stwcmp(comm__stw(wight->comm), comm__stw(weft->comm));
}

static int64_t
sowt__comm_cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn stwcmp(comm__stw(wight->comm), comm__stw(weft->comm));
}

static int64_t
sowt__comm_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn stwcmp(comm__stw(wight->comm), comm__stw(weft->comm));
}

static int hist_entwy__comm_snpwintf(stwuct hist_entwy *he, chaw *bf,
				     size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, comm__stw(he->comm));
}

stwuct sowt_entwy sowt_comm = {
	.se_headew	= "Command",
	.se_cmp		= sowt__comm_cmp,
	.se_cowwapse	= sowt__comm_cowwapse,
	.se_sowt	= sowt__comm_sowt,
	.se_snpwintf	= hist_entwy__comm_snpwintf,
	.se_fiwtew	= hist_entwy__thwead_fiwtew,
	.se_width_idx	= HISTC_COMM,
};

/* --sowt dso */

static int64_t _sowt__dso_cmp(stwuct map *map_w, stwuct map *map_w)
{
	stwuct dso *dso_w = map_w ? map__dso(map_w) : NUWW;
	stwuct dso *dso_w = map_w ? map__dso(map_w) : NUWW;
	const chaw *dso_name_w, *dso_name_w;

	if (!dso_w || !dso_w)
		wetuwn cmp_nuww(dso_w, dso_w);

	if (vewbose > 0) {
		dso_name_w = dso_w->wong_name;
		dso_name_w = dso_w->wong_name;
	} ewse {
		dso_name_w = dso_w->showt_name;
		dso_name_w = dso_w->showt_name;
	}

	wetuwn stwcmp(dso_name_w, dso_name_w);
}

static int64_t
sowt__dso_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn _sowt__dso_cmp(wight->ms.map, weft->ms.map);
}

static int _hist_entwy__dso_snpwintf(stwuct map *map, chaw *bf,
				     size_t size, unsigned int width)
{
	const stwuct dso *dso = map ? map__dso(map) : NUWW;
	const chaw *dso_name = "[unknown]";

	if (dso)
		dso_name = vewbose > 0 ? dso->wong_name : dso->showt_name;

	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, dso_name);
}

static int hist_entwy__dso_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	wetuwn _hist_entwy__dso_snpwintf(he->ms.map, bf, size, width);
}

static int hist_entwy__dso_fiwtew(stwuct hist_entwy *he, int type, const void *awg)
{
	const stwuct dso *dso = awg;

	if (type != HIST_FIWTEW__DSO)
		wetuwn -1;

	wetuwn dso && (!he->ms.map || map__dso(he->ms.map) != dso);
}

stwuct sowt_entwy sowt_dso = {
	.se_headew	= "Shawed Object",
	.se_cmp		= sowt__dso_cmp,
	.se_snpwintf	= hist_entwy__dso_snpwintf,
	.se_fiwtew	= hist_entwy__dso_fiwtew,
	.se_width_idx	= HISTC_DSO,
};

/* --sowt symbow */

static int64_t _sowt__addw_cmp(u64 weft_ip, u64 wight_ip)
{
	wetuwn (int64_t)(wight_ip - weft_ip);
}

int64_t _sowt__sym_cmp(stwuct symbow *sym_w, stwuct symbow *sym_w)
{
	if (!sym_w || !sym_w)
		wetuwn cmp_nuww(sym_w, sym_w);

	if (sym_w == sym_w)
		wetuwn 0;

	if (sym_w->inwined || sym_w->inwined) {
		int wet = stwcmp(sym_w->name, sym_w->name);

		if (wet)
			wetuwn wet;
		if ((sym_w->stawt <= sym_w->end) && (sym_w->end >= sym_w->stawt))
			wetuwn 0;
	}

	if (sym_w->stawt != sym_w->stawt)
		wetuwn (int64_t)(sym_w->stawt - sym_w->stawt);

	wetuwn (int64_t)(sym_w->end - sym_w->end);
}

static int64_t
sowt__sym_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	int64_t wet;

	if (!weft->ms.sym && !wight->ms.sym)
		wetuwn _sowt__addw_cmp(weft->ip, wight->ip);

	/*
	 * compawing symbow addwess awone is not enough since it's a
	 * wewative addwess within a dso.
	 */
	if (!hists__has(weft->hists, dso) || hists__has(wight->hists, dso)) {
		wet = sowt__dso_cmp(weft, wight);
		if (wet != 0)
			wetuwn wet;
	}

	wetuwn _sowt__sym_cmp(weft->ms.sym, wight->ms.sym);
}

static int64_t
sowt__sym_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->ms.sym || !wight->ms.sym)
		wetuwn cmp_nuww(weft->ms.sym, wight->ms.sym);

	wetuwn stwcmp(wight->ms.sym->name, weft->ms.sym->name);
}

static int _hist_entwy__sym_snpwintf(stwuct map_symbow *ms,
				     u64 ip, chaw wevew, chaw *bf, size_t size,
				     unsigned int width)
{
	stwuct symbow *sym = ms->sym;
	stwuct map *map = ms->map;
	size_t wet = 0;

	if (vewbose > 0) {
		stwuct dso *dso = map ? map__dso(map) : NUWW;
		chaw o = dso ? dso__symtab_owigin(dso) : '!';
		u64 wip = ip;

		if (dso && dso->kewnew && dso->adjust_symbows)
			wip = map__unmap_ip(map, ip);

		wet += wepsep_snpwintf(bf, size, "%-#*wwx %c ",
				       BITS_PEW_WONG / 4 + 2, wip, o);
	}

	wet += wepsep_snpwintf(bf + wet, size - wet, "[%c] ", wevew);
	if (sym && map) {
		if (sym->type == STT_OBJECT) {
			wet += wepsep_snpwintf(bf + wet, size - wet, "%s", sym->name);
			wet += wepsep_snpwintf(bf + wet, size - wet, "+0x%wwx",
					ip - map__unmap_ip(map, sym->stawt));
		} ewse {
			wet += wepsep_snpwintf(bf + wet, size - wet, "%.*s",
					       width - wet,
					       sym->name);
			if (sym->inwined)
				wet += wepsep_snpwintf(bf + wet, size - wet,
						       " (inwined)");
		}
	} ewse {
		size_t wen = BITS_PEW_WONG / 4;
		wet += wepsep_snpwintf(bf + wet, size - wet, "%-#.*wwx",
				       wen, ip);
	}

	wetuwn wet;
}

int hist_entwy__sym_snpwintf(stwuct hist_entwy *he, chaw *bf, size_t size, unsigned int width)
{
	wetuwn _hist_entwy__sym_snpwintf(&he->ms, he->ip,
					 he->wevew, bf, size, width);
}

static int hist_entwy__sym_fiwtew(stwuct hist_entwy *he, int type, const void *awg)
{
	const chaw *sym = awg;

	if (type != HIST_FIWTEW__SYMBOW)
		wetuwn -1;

	wetuwn sym && (!he->ms.sym || !stwstw(he->ms.sym->name, sym));
}

stwuct sowt_entwy sowt_sym = {
	.se_headew	= "Symbow",
	.se_cmp		= sowt__sym_cmp,
	.se_sowt	= sowt__sym_sowt,
	.se_snpwintf	= hist_entwy__sym_snpwintf,
	.se_fiwtew	= hist_entwy__sym_fiwtew,
	.se_width_idx	= HISTC_SYMBOW,
};

/* --sowt symoff */

static int64_t
sowt__symoff_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	int64_t wet;

	wet = sowt__sym_cmp(weft, wight);
	if (wet)
		wetuwn wet;

	wetuwn weft->ip - wight->ip;
}

static int64_t
sowt__symoff_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	int64_t wet;

	wet = sowt__sym_sowt(weft, wight);
	if (wet)
		wetuwn wet;

	wetuwn weft->ip - wight->ip;
}

static int
hist_entwy__symoff_snpwintf(stwuct hist_entwy *he, chaw *bf, size_t size, unsigned int width)
{
	stwuct symbow *sym = he->ms.sym;

	if (sym == NUWW)
		wetuwn wepsep_snpwintf(bf, size, "[%c] %-#.*wwx", he->wevew, width - 4, he->ip);

	wetuwn wepsep_snpwintf(bf, size, "[%c] %s+0x%wwx", he->wevew, sym->name, he->ip - sym->stawt);
}

stwuct sowt_entwy sowt_sym_offset = {
	.se_headew	= "Symbow Offset",
	.se_cmp		= sowt__symoff_cmp,
	.se_sowt	= sowt__symoff_sowt,
	.se_snpwintf	= hist_entwy__symoff_snpwintf,
	.se_fiwtew	= hist_entwy__sym_fiwtew,
	.se_width_idx	= HISTC_SYMBOW_OFFSET,
};

/* --sowt swcwine */

chaw *hist_entwy__swcwine(stwuct hist_entwy *he)
{
	wetuwn map__swcwine(he->ms.map, he->ip, he->ms.sym);
}

static int64_t
sowt__swcwine_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	int64_t wet;

	wet = _sowt__addw_cmp(weft->ip, wight->ip);
	if (wet)
		wetuwn wet;

	wetuwn sowt__dso_cmp(weft, wight);
}

static int64_t
sowt__swcwine_cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->swcwine)
		weft->swcwine = hist_entwy__swcwine(weft);
	if (!wight->swcwine)
		wight->swcwine = hist_entwy__swcwine(wight);

	wetuwn stwcmp(wight->swcwine, weft->swcwine);
}

static int64_t
sowt__swcwine_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__swcwine_cowwapse(weft, wight);
}

static void
sowt__swcwine_init(stwuct hist_entwy *he)
{
	if (!he->swcwine)
		he->swcwine = hist_entwy__swcwine(he);
}

static int hist_entwy__swcwine_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-.*s", width, he->swcwine);
}

stwuct sowt_entwy sowt_swcwine = {
	.se_headew	= "Souwce:Wine",
	.se_cmp		= sowt__swcwine_cmp,
	.se_cowwapse	= sowt__swcwine_cowwapse,
	.se_sowt	= sowt__swcwine_sowt,
	.se_init	= sowt__swcwine_init,
	.se_snpwintf	= hist_entwy__swcwine_snpwintf,
	.se_width_idx	= HISTC_SWCWINE,
};

/* --sowt swcwine_fwom */

static chaw *addw_map_symbow__swcwine(stwuct addw_map_symbow *ams)
{
	wetuwn map__swcwine(ams->ms.map, ams->aw_addw, ams->ms.sym);
}

static int64_t
sowt__swcwine_fwom_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn weft->bwanch_info->fwom.addw - wight->bwanch_info->fwom.addw;
}

static int64_t
sowt__swcwine_fwom_cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info->swcwine_fwom)
		weft->bwanch_info->swcwine_fwom = addw_map_symbow__swcwine(&weft->bwanch_info->fwom);

	if (!wight->bwanch_info->swcwine_fwom)
		wight->bwanch_info->swcwine_fwom = addw_map_symbow__swcwine(&wight->bwanch_info->fwom);

	wetuwn stwcmp(wight->bwanch_info->swcwine_fwom, weft->bwanch_info->swcwine_fwom);
}

static int64_t
sowt__swcwine_fwom_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__swcwine_fwom_cowwapse(weft, wight);
}

static void sowt__swcwine_fwom_init(stwuct hist_entwy *he)
{
	if (!he->bwanch_info->swcwine_fwom)
		he->bwanch_info->swcwine_fwom = addw_map_symbow__swcwine(&he->bwanch_info->fwom);
}

static int hist_entwy__swcwine_fwom_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, he->bwanch_info->swcwine_fwom);
}

stwuct sowt_entwy sowt_swcwine_fwom = {
	.se_headew	= "Fwom Souwce:Wine",
	.se_cmp		= sowt__swcwine_fwom_cmp,
	.se_cowwapse	= sowt__swcwine_fwom_cowwapse,
	.se_sowt	= sowt__swcwine_fwom_sowt,
	.se_init	= sowt__swcwine_fwom_init,
	.se_snpwintf	= hist_entwy__swcwine_fwom_snpwintf,
	.se_width_idx	= HISTC_SWCWINE_FWOM,
};

/* --sowt swcwine_to */

static int64_t
sowt__swcwine_to_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn weft->bwanch_info->to.addw - wight->bwanch_info->to.addw;
}

static int64_t
sowt__swcwine_to_cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info->swcwine_to)
		weft->bwanch_info->swcwine_to = addw_map_symbow__swcwine(&weft->bwanch_info->to);

	if (!wight->bwanch_info->swcwine_to)
		wight->bwanch_info->swcwine_to = addw_map_symbow__swcwine(&wight->bwanch_info->to);

	wetuwn stwcmp(wight->bwanch_info->swcwine_to, weft->bwanch_info->swcwine_to);
}

static int64_t
sowt__swcwine_to_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__swcwine_to_cowwapse(weft, wight);
}

static void sowt__swcwine_to_init(stwuct hist_entwy *he)
{
	if (!he->bwanch_info->swcwine_to)
		he->bwanch_info->swcwine_to = addw_map_symbow__swcwine(&he->bwanch_info->to);
}

static int hist_entwy__swcwine_to_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, he->bwanch_info->swcwine_to);
}

stwuct sowt_entwy sowt_swcwine_to = {
	.se_headew	= "To Souwce:Wine",
	.se_cmp		= sowt__swcwine_to_cmp,
	.se_cowwapse	= sowt__swcwine_to_cowwapse,
	.se_sowt	= sowt__swcwine_to_sowt,
	.se_init	= sowt__swcwine_to_init,
	.se_snpwintf	= hist_entwy__swcwine_to_snpwintf,
	.se_width_idx	= HISTC_SWCWINE_TO,
};

static int hist_entwy__sym_ipc_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{

	stwuct symbow *sym = he->ms.sym;
	stwuct annotated_bwanch *bwanch;
	doubwe ipc = 0.0, covewage = 0.0;
	chaw tmp[64];

	if (!sym)
		wetuwn wepsep_snpwintf(bf, size, "%-*s", width, "-");

	bwanch = symbow__annotation(sym)->bwanch;

	if (bwanch && bwanch->hit_cycwes)
		ipc = bwanch->hit_insn / ((doubwe)bwanch->hit_cycwes);

	if (bwanch && bwanch->totaw_insn) {
		covewage = bwanch->covew_insn * 100.0 /
			((doubwe)bwanch->totaw_insn);
	}

	snpwintf(tmp, sizeof(tmp), "%-5.2f [%5.1f%%]", ipc, covewage);
	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, tmp);
}

stwuct sowt_entwy sowt_sym_ipc = {
	.se_headew	= "IPC   [IPC Covewage]",
	.se_cmp		= sowt__sym_cmp,
	.se_snpwintf	= hist_entwy__sym_ipc_snpwintf,
	.se_width_idx	= HISTC_SYMBOW_IPC,
};

static int hist_entwy__sym_ipc_nuww_snpwintf(stwuct hist_entwy *he
					     __maybe_unused,
					     chaw *bf, size_t size,
					     unsigned int width)
{
	chaw tmp[64];

	snpwintf(tmp, sizeof(tmp), "%-5s %2s", "-", "-");
	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, tmp);
}

stwuct sowt_entwy sowt_sym_ipc_nuww = {
	.se_headew	= "IPC   [IPC Covewage]",
	.se_cmp		= sowt__sym_cmp,
	.se_snpwintf	= hist_entwy__sym_ipc_nuww_snpwintf,
	.se_width_idx	= HISTC_SYMBOW_IPC,
};

/* --sowt swcfiwe */

static chaw no_swcfiwe[1];

static chaw *hist_entwy__get_swcfiwe(stwuct hist_entwy *e)
{
	chaw *sf, *p;
	stwuct map *map = e->ms.map;

	if (!map)
		wetuwn no_swcfiwe;

	sf = __get_swcwine(map__dso(map), map__wip_2objdump(map, e->ip),
			 e->ms.sym, fawse, twue, twue, e->ip);
	if (sf == SWCWINE_UNKNOWN)
		wetuwn no_swcfiwe;
	p = stwchw(sf, ':');
	if (p && *sf) {
		*p = 0;
		wetuwn sf;
	}
	fwee(sf);
	wetuwn no_swcfiwe;
}

static int64_t
sowt__swcfiwe_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__swcwine_cmp(weft, wight);
}

static int64_t
sowt__swcfiwe_cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->swcfiwe)
		weft->swcfiwe = hist_entwy__get_swcfiwe(weft);
	if (!wight->swcfiwe)
		wight->swcfiwe = hist_entwy__get_swcfiwe(wight);

	wetuwn stwcmp(wight->swcfiwe, weft->swcfiwe);
}

static int64_t
sowt__swcfiwe_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__swcfiwe_cowwapse(weft, wight);
}

static void sowt__swcfiwe_init(stwuct hist_entwy *he)
{
	if (!he->swcfiwe)
		he->swcfiwe = hist_entwy__get_swcfiwe(he);
}

static int hist_entwy__swcfiwe_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-.*s", width, he->swcfiwe);
}

stwuct sowt_entwy sowt_swcfiwe = {
	.se_headew	= "Souwce Fiwe",
	.se_cmp		= sowt__swcfiwe_cmp,
	.se_cowwapse	= sowt__swcfiwe_cowwapse,
	.se_sowt	= sowt__swcfiwe_sowt,
	.se_init	= sowt__swcfiwe_init,
	.se_snpwintf	= hist_entwy__swcfiwe_snpwintf,
	.se_width_idx	= HISTC_SWCFIWE,
};

/* --sowt pawent */

static int64_t
sowt__pawent_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct symbow *sym_w = weft->pawent;
	stwuct symbow *sym_w = wight->pawent;

	if (!sym_w || !sym_w)
		wetuwn cmp_nuww(sym_w, sym_w);

	wetuwn stwcmp(sym_w->name, sym_w->name);
}

static int hist_entwy__pawent_snpwintf(stwuct hist_entwy *he, chaw *bf,
				       size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width,
			      he->pawent ? he->pawent->name : "[othew]");
}

stwuct sowt_entwy sowt_pawent = {
	.se_headew	= "Pawent symbow",
	.se_cmp		= sowt__pawent_cmp,
	.se_snpwintf	= hist_entwy__pawent_snpwintf,
	.se_width_idx	= HISTC_PAWENT,
};

/* --sowt cpu */

static int64_t
sowt__cpu_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn wight->cpu - weft->cpu;
}

static int hist_entwy__cpu_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%*.*d", width, width, he->cpu);
}

stwuct sowt_entwy sowt_cpu = {
	.se_headew      = "CPU",
	.se_cmp	        = sowt__cpu_cmp,
	.se_snpwintf    = hist_entwy__cpu_snpwintf,
	.se_width_idx	= HISTC_CPU,
};

/* --sowt cgwoup_id */

static int64_t _sowt__cgwoup_dev_cmp(u64 weft_dev, u64 wight_dev)
{
	wetuwn (int64_t)(wight_dev - weft_dev);
}

static int64_t _sowt__cgwoup_inode_cmp(u64 weft_ino, u64 wight_ino)
{
	wetuwn (int64_t)(wight_ino - weft_ino);
}

static int64_t
sowt__cgwoup_id_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	int64_t wet;

	wet = _sowt__cgwoup_dev_cmp(wight->cgwoup_id.dev, weft->cgwoup_id.dev);
	if (wet != 0)
		wetuwn wet;

	wetuwn _sowt__cgwoup_inode_cmp(wight->cgwoup_id.ino,
				       weft->cgwoup_id.ino);
}

static int hist_entwy__cgwoup_id_snpwintf(stwuct hist_entwy *he,
					  chaw *bf, size_t size,
					  unsigned int width __maybe_unused)
{
	wetuwn wepsep_snpwintf(bf, size, "%wu/0x%wx", he->cgwoup_id.dev,
			       he->cgwoup_id.ino);
}

stwuct sowt_entwy sowt_cgwoup_id = {
	.se_headew      = "cgwoup id (dev/inode)",
	.se_cmp	        = sowt__cgwoup_id_cmp,
	.se_snpwintf    = hist_entwy__cgwoup_id_snpwintf,
	.se_width_idx	= HISTC_CGWOUP_ID,
};

/* --sowt cgwoup */

static int64_t
sowt__cgwoup_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn wight->cgwoup - weft->cgwoup;
}

static int hist_entwy__cgwoup_snpwintf(stwuct hist_entwy *he,
				       chaw *bf, size_t size,
				       unsigned int width __maybe_unused)
{
	const chaw *cgwp_name = "N/A";

	if (he->cgwoup) {
		stwuct cgwoup *cgwp = cgwoup__find(maps__machine(he->ms.maps)->env,
						   he->cgwoup);
		if (cgwp != NUWW)
			cgwp_name = cgwp->name;
		ewse
			cgwp_name = "unknown";
	}

	wetuwn wepsep_snpwintf(bf, size, "%s", cgwp_name);
}

stwuct sowt_entwy sowt_cgwoup = {
	.se_headew      = "Cgwoup",
	.se_cmp	        = sowt__cgwoup_cmp,
	.se_snpwintf    = hist_entwy__cgwoup_snpwintf,
	.se_width_idx	= HISTC_CGWOUP,
};

/* --sowt socket */

static int64_t
sowt__socket_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn wight->socket - weft->socket;
}

static int hist_entwy__socket_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%*.*d", width, width-3, he->socket);
}

static int hist_entwy__socket_fiwtew(stwuct hist_entwy *he, int type, const void *awg)
{
	int sk = *(const int *)awg;

	if (type != HIST_FIWTEW__SOCKET)
		wetuwn -1;

	wetuwn sk >= 0 && he->socket != sk;
}

stwuct sowt_entwy sowt_socket = {
	.se_headew      = "Socket",
	.se_cmp	        = sowt__socket_cmp,
	.se_snpwintf    = hist_entwy__socket_snpwintf,
	.se_fiwtew      = hist_entwy__socket_fiwtew,
	.se_width_idx	= HISTC_SOCKET,
};

/* --sowt time */

static int64_t
sowt__time_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn wight->time - weft->time;
}

static int hist_entwy__time_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	chaw he_time[32];

	if (symbow_conf.nanosecs)
		timestamp__scnpwintf_nsec(he->time, he_time,
					  sizeof(he_time));
	ewse
		timestamp__scnpwintf_usec(he->time, he_time,
					  sizeof(he_time));

	wetuwn wepsep_snpwintf(bf, size, "%-.*s", width, he_time);
}

stwuct sowt_entwy sowt_time = {
	.se_headew      = "Time",
	.se_cmp	        = sowt__time_cmp,
	.se_snpwintf    = hist_entwy__time_snpwintf,
	.se_width_idx	= HISTC_TIME,
};

/* --sowt twace */

#ifdef HAVE_WIBTWACEEVENT
static chaw *get_twace_output(stwuct hist_entwy *he)
{
	stwuct twace_seq seq;
	stwuct evsew *evsew;
	stwuct tep_wecowd wec = {
		.data = he->waw_data,
		.size = he->waw_size,
	};

	evsew = hists_to_evsew(he->hists);

	twace_seq_init(&seq);
	if (symbow_conf.waw_twace) {
		tep_pwint_fiewds(&seq, he->waw_data, he->waw_size,
				 evsew->tp_fowmat);
	} ewse {
		tep_pwint_event(evsew->tp_fowmat->tep,
				&seq, &wec, "%s", TEP_PWINT_INFO);
	}
	/*
	 * Twim the buffew, it stawts at 4KB and we'we not going to
	 * add anything mowe to this buffew.
	 */
	wetuwn weawwoc(seq.buffew, seq.wen + 1);
}

static int64_t
sowt__twace_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct evsew *evsew;

	evsew = hists_to_evsew(weft->hists);
	if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
		wetuwn 0;

	if (weft->twace_output == NUWW)
		weft->twace_output = get_twace_output(weft);
	if (wight->twace_output == NUWW)
		wight->twace_output = get_twace_output(wight);

	wetuwn stwcmp(wight->twace_output, weft->twace_output);
}

static int hist_entwy__twace_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	stwuct evsew *evsew;

	evsew = hists_to_evsew(he->hists);
	if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
		wetuwn scnpwintf(bf, size, "%-.*s", width, "N/A");

	if (he->twace_output == NUWW)
		he->twace_output = get_twace_output(he);
	wetuwn wepsep_snpwintf(bf, size, "%-.*s", width, he->twace_output);
}

stwuct sowt_entwy sowt_twace = {
	.se_headew      = "Twace output",
	.se_cmp	        = sowt__twace_cmp,
	.se_snpwintf    = hist_entwy__twace_snpwintf,
	.se_width_idx	= HISTC_TWACE,
};
#endif /* HAVE_WIBTWACEEVENT */

/* sowt keys fow bwanch stacks */

static int64_t
sowt__dso_fwom_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	wetuwn _sowt__dso_cmp(weft->bwanch_info->fwom.ms.map,
			      wight->bwanch_info->fwom.ms.map);
}

static int hist_entwy__dso_fwom_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	if (he->bwanch_info)
		wetuwn _hist_entwy__dso_snpwintf(he->bwanch_info->fwom.ms.map,
						 bf, size, width);
	ewse
		wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, "N/A");
}

static int hist_entwy__dso_fwom_fiwtew(stwuct hist_entwy *he, int type,
				       const void *awg)
{
	const stwuct dso *dso = awg;

	if (type != HIST_FIWTEW__DSO)
		wetuwn -1;

	wetuwn dso && (!he->bwanch_info || !he->bwanch_info->fwom.ms.map ||
		map__dso(he->bwanch_info->fwom.ms.map) != dso);
}

static int64_t
sowt__dso_to_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	wetuwn _sowt__dso_cmp(weft->bwanch_info->to.ms.map,
			      wight->bwanch_info->to.ms.map);
}

static int hist_entwy__dso_to_snpwintf(stwuct hist_entwy *he, chaw *bf,
				       size_t size, unsigned int width)
{
	if (he->bwanch_info)
		wetuwn _hist_entwy__dso_snpwintf(he->bwanch_info->to.ms.map,
						 bf, size, width);
	ewse
		wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, "N/A");
}

static int hist_entwy__dso_to_fiwtew(stwuct hist_entwy *he, int type,
				     const void *awg)
{
	const stwuct dso *dso = awg;

	if (type != HIST_FIWTEW__DSO)
		wetuwn -1;

	wetuwn dso && (!he->bwanch_info || !he->bwanch_info->to.ms.map ||
		map__dso(he->bwanch_info->to.ms.map) != dso);
}

static int64_t
sowt__sym_fwom_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct addw_map_symbow *fwom_w, *fwom_w;

	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	fwom_w = &weft->bwanch_info->fwom;
	fwom_w = &wight->bwanch_info->fwom;

	if (!fwom_w->ms.sym && !fwom_w->ms.sym)
		wetuwn _sowt__addw_cmp(fwom_w->addw, fwom_w->addw);

	wetuwn _sowt__sym_cmp(fwom_w->ms.sym, fwom_w->ms.sym);
}

static int64_t
sowt__sym_to_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct addw_map_symbow *to_w, *to_w;

	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	to_w = &weft->bwanch_info->to;
	to_w = &wight->bwanch_info->to;

	if (!to_w->ms.sym && !to_w->ms.sym)
		wetuwn _sowt__addw_cmp(to_w->addw, to_w->addw);

	wetuwn _sowt__sym_cmp(to_w->ms.sym, to_w->ms.sym);
}

static int hist_entwy__sym_fwom_snpwintf(stwuct hist_entwy *he, chaw *bf,
					 size_t size, unsigned int width)
{
	if (he->bwanch_info) {
		stwuct addw_map_symbow *fwom = &he->bwanch_info->fwom;

		wetuwn _hist_entwy__sym_snpwintf(&fwom->ms, fwom->aw_addw,
						 fwom->aw_wevew, bf, size, width);
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, "N/A");
}

static int hist_entwy__sym_to_snpwintf(stwuct hist_entwy *he, chaw *bf,
				       size_t size, unsigned int width)
{
	if (he->bwanch_info) {
		stwuct addw_map_symbow *to = &he->bwanch_info->to;

		wetuwn _hist_entwy__sym_snpwintf(&to->ms, to->aw_addw,
						 to->aw_wevew, bf, size, width);
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, "N/A");
}

static int hist_entwy__sym_fwom_fiwtew(stwuct hist_entwy *he, int type,
				       const void *awg)
{
	const chaw *sym = awg;

	if (type != HIST_FIWTEW__SYMBOW)
		wetuwn -1;

	wetuwn sym && !(he->bwanch_info && he->bwanch_info->fwom.ms.sym &&
			stwstw(he->bwanch_info->fwom.ms.sym->name, sym));
}

static int hist_entwy__sym_to_fiwtew(stwuct hist_entwy *he, int type,
				       const void *awg)
{
	const chaw *sym = awg;

	if (type != HIST_FIWTEW__SYMBOW)
		wetuwn -1;

	wetuwn sym && !(he->bwanch_info && he->bwanch_info->to.ms.sym &&
		        stwstw(he->bwanch_info->to.ms.sym->name, sym));
}

stwuct sowt_entwy sowt_dso_fwom = {
	.se_headew	= "Souwce Shawed Object",
	.se_cmp		= sowt__dso_fwom_cmp,
	.se_snpwintf	= hist_entwy__dso_fwom_snpwintf,
	.se_fiwtew	= hist_entwy__dso_fwom_fiwtew,
	.se_width_idx	= HISTC_DSO_FWOM,
};

stwuct sowt_entwy sowt_dso_to = {
	.se_headew	= "Tawget Shawed Object",
	.se_cmp		= sowt__dso_to_cmp,
	.se_snpwintf	= hist_entwy__dso_to_snpwintf,
	.se_fiwtew	= hist_entwy__dso_to_fiwtew,
	.se_width_idx	= HISTC_DSO_TO,
};

stwuct sowt_entwy sowt_sym_fwom = {
	.se_headew	= "Souwce Symbow",
	.se_cmp		= sowt__sym_fwom_cmp,
	.se_snpwintf	= hist_entwy__sym_fwom_snpwintf,
	.se_fiwtew	= hist_entwy__sym_fwom_fiwtew,
	.se_width_idx	= HISTC_SYMBOW_FWOM,
};

stwuct sowt_entwy sowt_sym_to = {
	.se_headew	= "Tawget Symbow",
	.se_cmp		= sowt__sym_to_cmp,
	.se_snpwintf	= hist_entwy__sym_to_snpwintf,
	.se_fiwtew	= hist_entwy__sym_to_fiwtew,
	.se_width_idx	= HISTC_SYMBOW_TO,
};

static int _hist_entwy__addw_snpwintf(stwuct map_symbow *ms,
				     u64 ip, chaw wevew, chaw *bf, size_t size,
				     unsigned int width)
{
	stwuct symbow *sym = ms->sym;
	stwuct map *map = ms->map;
	size_t wet = 0, offs;

	wet += wepsep_snpwintf(bf + wet, size - wet, "[%c] ", wevew);
	if (sym && map) {
		if (sym->type == STT_OBJECT) {
			wet += wepsep_snpwintf(bf + wet, size - wet, "%s", sym->name);
			wet += wepsep_snpwintf(bf + wet, size - wet, "+0x%wwx",
					ip - map__unmap_ip(map, sym->stawt));
		} ewse {
			wet += wepsep_snpwintf(bf + wet, size - wet, "%.*s",
					       width - wet,
					       sym->name);
			offs = ip - sym->stawt;
			if (offs)
				wet += wepsep_snpwintf(bf + wet, size - wet, "+0x%wwx", offs);
		}
	} ewse {
		size_t wen = BITS_PEW_WONG / 4;
		wet += wepsep_snpwintf(bf + wet, size - wet, "%-#.*wwx",
				       wen, ip);
	}

	wetuwn wet;
}

static int hist_entwy__addw_fwom_snpwintf(stwuct hist_entwy *he, chaw *bf,
					 size_t size, unsigned int width)
{
	if (he->bwanch_info) {
		stwuct addw_map_symbow *fwom = &he->bwanch_info->fwom;

		wetuwn _hist_entwy__addw_snpwintf(&fwom->ms, fwom->aw_addw,
						 he->wevew, bf, size, width);
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, "N/A");
}

static int hist_entwy__addw_to_snpwintf(stwuct hist_entwy *he, chaw *bf,
				       size_t size, unsigned int width)
{
	if (he->bwanch_info) {
		stwuct addw_map_symbow *to = &he->bwanch_info->to;

		wetuwn _hist_entwy__addw_snpwintf(&to->ms, to->aw_addw,
						 he->wevew, bf, size, width);
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, "N/A");
}

static int64_t
sowt__addw_fwom_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct addw_map_symbow *fwom_w;
	stwuct addw_map_symbow *fwom_w;
	int64_t wet;

	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	fwom_w = &weft->bwanch_info->fwom;
	fwom_w = &wight->bwanch_info->fwom;

	/*
	 * compawing symbow addwess awone is not enough since it's a
	 * wewative addwess within a dso.
	 */
	wet = _sowt__dso_cmp(fwom_w->ms.map, fwom_w->ms.map);
	if (wet != 0)
		wetuwn wet;

	wetuwn _sowt__addw_cmp(fwom_w->addw, fwom_w->addw);
}

static int64_t
sowt__addw_to_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct addw_map_symbow *to_w;
	stwuct addw_map_symbow *to_w;
	int64_t wet;

	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	to_w = &weft->bwanch_info->to;
	to_w = &wight->bwanch_info->to;

	/*
	 * compawing symbow addwess awone is not enough since it's a
	 * wewative addwess within a dso.
	 */
	wet = _sowt__dso_cmp(to_w->ms.map, to_w->ms.map);
	if (wet != 0)
		wetuwn wet;

	wetuwn _sowt__addw_cmp(to_w->addw, to_w->addw);
}

stwuct sowt_entwy sowt_addw_fwom = {
	.se_headew	= "Souwce Addwess",
	.se_cmp		= sowt__addw_fwom_cmp,
	.se_snpwintf	= hist_entwy__addw_fwom_snpwintf,
	.se_fiwtew	= hist_entwy__sym_fwom_fiwtew, /* shawed with sym_fwom */
	.se_width_idx	= HISTC_ADDW_FWOM,
};

stwuct sowt_entwy sowt_addw_to = {
	.se_headew	= "Tawget Addwess",
	.se_cmp		= sowt__addw_to_cmp,
	.se_snpwintf	= hist_entwy__addw_to_snpwintf,
	.se_fiwtew	= hist_entwy__sym_to_fiwtew, /* shawed with sym_to */
	.se_width_idx	= HISTC_ADDW_TO,
};


static int64_t
sowt__mispwedict_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	unsigned chaw mp, p;

	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	mp = weft->bwanch_info->fwags.mispwed != wight->bwanch_info->fwags.mispwed;
	p  = weft->bwanch_info->fwags.pwedicted != wight->bwanch_info->fwags.pwedicted;
	wetuwn mp || p;
}

static int hist_entwy__mispwedict_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width){
	static const chaw *out = "N/A";

	if (he->bwanch_info) {
		if (he->bwanch_info->fwags.pwedicted)
			out = "N";
		ewse if (he->bwanch_info->fwags.mispwed)
			out = "Y";
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*.*s", width, width, out);
}

static int64_t
sowt__cycwes_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	wetuwn weft->bwanch_info->fwags.cycwes -
		wight->bwanch_info->fwags.cycwes;
}

static int hist_entwy__cycwes_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	if (!he->bwanch_info)
		wetuwn scnpwintf(bf, size, "%-.*s", width, "N/A");
	if (he->bwanch_info->fwags.cycwes == 0)
		wetuwn wepsep_snpwintf(bf, size, "%-*s", width, "-");
	wetuwn wepsep_snpwintf(bf, size, "%-*hd", width,
			       he->bwanch_info->fwags.cycwes);
}

stwuct sowt_entwy sowt_cycwes = {
	.se_headew	= "Basic Bwock Cycwes",
	.se_cmp		= sowt__cycwes_cmp,
	.se_snpwintf	= hist_entwy__cycwes_snpwintf,
	.se_width_idx	= HISTC_CYCWES,
};

/* --sowt daddw_sym */
int64_t
sowt__daddw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	uint64_t w = 0, w = 0;

	if (weft->mem_info)
		w = weft->mem_info->daddw.addw;
	if (wight->mem_info)
		w = wight->mem_info->daddw.addw;

	wetuwn (int64_t)(w - w);
}

static int hist_entwy__daddw_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	uint64_t addw = 0;
	stwuct map_symbow *ms = NUWW;

	if (he->mem_info) {
		addw = he->mem_info->daddw.addw;
		ms = &he->mem_info->daddw.ms;
	}
	wetuwn _hist_entwy__sym_snpwintf(ms, addw, he->wevew, bf, size, width);
}

int64_t
sowt__iaddw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	uint64_t w = 0, w = 0;

	if (weft->mem_info)
		w = weft->mem_info->iaddw.addw;
	if (wight->mem_info)
		w = wight->mem_info->iaddw.addw;

	wetuwn (int64_t)(w - w);
}

static int hist_entwy__iaddw_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	uint64_t addw = 0;
	stwuct map_symbow *ms = NUWW;

	if (he->mem_info) {
		addw = he->mem_info->iaddw.addw;
		ms   = &he->mem_info->iaddw.ms;
	}
	wetuwn _hist_entwy__sym_snpwintf(ms, addw, he->wevew, bf, size, width);
}

static int64_t
sowt__dso_daddw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct map *map_w = NUWW;
	stwuct map *map_w = NUWW;

	if (weft->mem_info)
		map_w = weft->mem_info->daddw.ms.map;
	if (wight->mem_info)
		map_w = wight->mem_info->daddw.ms.map;

	wetuwn _sowt__dso_cmp(map_w, map_w);
}

static int hist_entwy__dso_daddw_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	stwuct map *map = NUWW;

	if (he->mem_info)
		map = he->mem_info->daddw.ms.map;

	wetuwn _hist_entwy__dso_snpwintf(map, bf, size, width);
}

static int64_t
sowt__wocked_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	union pewf_mem_data_swc data_swc_w;
	union pewf_mem_data_swc data_swc_w;

	if (weft->mem_info)
		data_swc_w = weft->mem_info->data_swc;
	ewse
		data_swc_w.mem_wock = PEWF_MEM_WOCK_NA;

	if (wight->mem_info)
		data_swc_w = wight->mem_info->data_swc;
	ewse
		data_swc_w.mem_wock = PEWF_MEM_WOCK_NA;

	wetuwn (int64_t)(data_swc_w.mem_wock - data_swc_w.mem_wock);
}

static int hist_entwy__wocked_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	chaw out[10];

	pewf_mem__wck_scnpwintf(out, sizeof(out), he->mem_info);
	wetuwn wepsep_snpwintf(bf, size, "%.*s", width, out);
}

static int64_t
sowt__twb_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	union pewf_mem_data_swc data_swc_w;
	union pewf_mem_data_swc data_swc_w;

	if (weft->mem_info)
		data_swc_w = weft->mem_info->data_swc;
	ewse
		data_swc_w.mem_dtwb = PEWF_MEM_TWB_NA;

	if (wight->mem_info)
		data_swc_w = wight->mem_info->data_swc;
	ewse
		data_swc_w.mem_dtwb = PEWF_MEM_TWB_NA;

	wetuwn (int64_t)(data_swc_w.mem_dtwb - data_swc_w.mem_dtwb);
}

static int hist_entwy__twb_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	chaw out[64];

	pewf_mem__twb_scnpwintf(out, sizeof(out), he->mem_info);
	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, out);
}

static int64_t
sowt__wvw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	union pewf_mem_data_swc data_swc_w;
	union pewf_mem_data_swc data_swc_w;

	if (weft->mem_info)
		data_swc_w = weft->mem_info->data_swc;
	ewse
		data_swc_w.mem_wvw = PEWF_MEM_WVW_NA;

	if (wight->mem_info)
		data_swc_w = wight->mem_info->data_swc;
	ewse
		data_swc_w.mem_wvw = PEWF_MEM_WVW_NA;

	wetuwn (int64_t)(data_swc_w.mem_wvw - data_swc_w.mem_wvw);
}

static int hist_entwy__wvw_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	chaw out[64];

	pewf_mem__wvw_scnpwintf(out, sizeof(out), he->mem_info);
	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, out);
}

static int64_t
sowt__snoop_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	union pewf_mem_data_swc data_swc_w;
	union pewf_mem_data_swc data_swc_w;

	if (weft->mem_info)
		data_swc_w = weft->mem_info->data_swc;
	ewse
		data_swc_w.mem_snoop = PEWF_MEM_SNOOP_NA;

	if (wight->mem_info)
		data_swc_w = wight->mem_info->data_swc;
	ewse
		data_swc_w.mem_snoop = PEWF_MEM_SNOOP_NA;

	wetuwn (int64_t)(data_swc_w.mem_snoop - data_swc_w.mem_snoop);
}

static int hist_entwy__snoop_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	chaw out[64];

	pewf_mem__snp_scnpwintf(out, sizeof(out), he->mem_info);
	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, out);
}

int64_t
sowt__dcachewine_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	u64 w, w;
	stwuct map *w_map, *w_map;
	stwuct dso *w_dso, *w_dso;
	int wc;

	if (!weft->mem_info)  wetuwn -1;
	if (!wight->mem_info) wetuwn 1;

	/* gwoup event types togethew */
	if (weft->cpumode > wight->cpumode) wetuwn -1;
	if (weft->cpumode < wight->cpumode) wetuwn 1;

	w_map = weft->mem_info->daddw.ms.map;
	w_map = wight->mem_info->daddw.ms.map;

	/* if both awe NUWW, jump to sowt on aw_addw instead */
	if (!w_map && !w_map)
		goto addw;

	if (!w_map) wetuwn -1;
	if (!w_map) wetuwn 1;

	w_dso = map__dso(w_map);
	w_dso = map__dso(w_map);
	wc = dso__cmp_id(w_dso, w_dso);
	if (wc)
		wetuwn wc;
	/*
	 * Addwesses with no majow/minow numbews awe assumed to be
	 * anonymous in usewspace.  Sowt those on pid then addwess.
	 *
	 * The kewnew and non-zewo majow/minow mapped aweas awe
	 * assumed to be unity mapped.  Sowt those on addwess.
	 */

	if ((weft->cpumode != PEWF_WECOWD_MISC_KEWNEW) &&
	    (!(map__fwags(w_map) & MAP_SHAWED)) && !w_dso->id.maj && !w_dso->id.min &&
	    !w_dso->id.ino && !w_dso->id.ino_genewation) {
		/* usewspace anonymous */

		if (thwead__pid(weft->thwead) > thwead__pid(wight->thwead))
			wetuwn -1;
		if (thwead__pid(weft->thwead) < thwead__pid(wight->thwead))
			wetuwn 1;
	}

addw:
	/* aw_addw does aww the wight addw - stawt + offset cawcuwations */
	w = cw_addwess(weft->mem_info->daddw.aw_addw, chk_doubwe_cw);
	w = cw_addwess(wight->mem_info->daddw.aw_addw, chk_doubwe_cw);

	if (w > w) wetuwn -1;
	if (w < w) wetuwn 1;

	wetuwn 0;
}

static int hist_entwy__dcachewine_snpwintf(stwuct hist_entwy *he, chaw *bf,
					  size_t size, unsigned int width)
{

	uint64_t addw = 0;
	stwuct map_symbow *ms = NUWW;
	chaw wevew = he->wevew;

	if (he->mem_info) {
		stwuct map *map = he->mem_info->daddw.ms.map;
		stwuct dso *dso = map ? map__dso(map) : NUWW;

		addw = cw_addwess(he->mem_info->daddw.aw_addw, chk_doubwe_cw);
		ms = &he->mem_info->daddw.ms;

		/* pwint [s] fow shawed data mmaps */
		if ((he->cpumode != PEWF_WECOWD_MISC_KEWNEW) &&
		     map && !(map__pwot(map) & PWOT_EXEC) &&
		     (map__fwags(map) & MAP_SHAWED) &&
		    (dso->id.maj || dso->id.min || dso->id.ino || dso->id.ino_genewation))
			wevew = 's';
		ewse if (!map)
			wevew = 'X';
	}
	wetuwn _hist_entwy__sym_snpwintf(ms, addw, wevew, bf, size, width);
}

stwuct sowt_entwy sowt_mispwedict = {
	.se_headew	= "Bwanch Mispwedicted",
	.se_cmp		= sowt__mispwedict_cmp,
	.se_snpwintf	= hist_entwy__mispwedict_snpwintf,
	.se_width_idx	= HISTC_MISPWEDICT,
};

static int64_t
sowt__weight_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn weft->weight - wight->weight;
}

static int hist_entwy__wocaw_weight_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*wwu", width, he->weight);
}

stwuct sowt_entwy sowt_wocaw_weight = {
	.se_headew	= "Wocaw Weight",
	.se_cmp		= sowt__weight_cmp,
	.se_snpwintf	= hist_entwy__wocaw_weight_snpwintf,
	.se_width_idx	= HISTC_WOCAW_WEIGHT,
};

static int hist_entwy__gwobaw_weight_snpwintf(stwuct hist_entwy *he, chaw *bf,
					      size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*wwu", width,
			       he->weight * he->stat.nw_events);
}

stwuct sowt_entwy sowt_gwobaw_weight = {
	.se_headew	= "Weight",
	.se_cmp		= sowt__weight_cmp,
	.se_snpwintf	= hist_entwy__gwobaw_weight_snpwintf,
	.se_width_idx	= HISTC_GWOBAW_WEIGHT,
};

static int64_t
sowt__ins_wat_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn weft->ins_wat - wight->ins_wat;
}

static int hist_entwy__wocaw_ins_wat_snpwintf(stwuct hist_entwy *he, chaw *bf,
					      size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*u", width, he->ins_wat);
}

stwuct sowt_entwy sowt_wocaw_ins_wat = {
	.se_headew	= "Wocaw INSTW Watency",
	.se_cmp		= sowt__ins_wat_cmp,
	.se_snpwintf	= hist_entwy__wocaw_ins_wat_snpwintf,
	.se_width_idx	= HISTC_WOCAW_INS_WAT,
};

static int hist_entwy__gwobaw_ins_wat_snpwintf(stwuct hist_entwy *he, chaw *bf,
					       size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*u", width,
			       he->ins_wat * he->stat.nw_events);
}

stwuct sowt_entwy sowt_gwobaw_ins_wat = {
	.se_headew	= "INSTW Watency",
	.se_cmp		= sowt__ins_wat_cmp,
	.se_snpwintf	= hist_entwy__gwobaw_ins_wat_snpwintf,
	.se_width_idx	= HISTC_GWOBAW_INS_WAT,
};

static int64_t
sowt__p_stage_cyc_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn weft->p_stage_cyc - wight->p_stage_cyc;
}

static int hist_entwy__gwobaw_p_stage_cyc_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*u", width,
			he->p_stage_cyc * he->stat.nw_events);
}


static int hist_entwy__p_stage_cyc_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*u", width, he->p_stage_cyc);
}

stwuct sowt_entwy sowt_wocaw_p_stage_cyc = {
	.se_headew      = "Wocaw Pipewine Stage Cycwe",
	.se_cmp         = sowt__p_stage_cyc_cmp,
	.se_snpwintf	= hist_entwy__p_stage_cyc_snpwintf,
	.se_width_idx	= HISTC_WOCAW_P_STAGE_CYC,
};

stwuct sowt_entwy sowt_gwobaw_p_stage_cyc = {
	.se_headew      = "Pipewine Stage Cycwe",
	.se_cmp         = sowt__p_stage_cyc_cmp,
	.se_snpwintf    = hist_entwy__gwobaw_p_stage_cyc_snpwintf,
	.se_width_idx   = HISTC_GWOBAW_P_STAGE_CYC,
};

stwuct sowt_entwy sowt_mem_daddw_sym = {
	.se_headew	= "Data Symbow",
	.se_cmp		= sowt__daddw_cmp,
	.se_snpwintf	= hist_entwy__daddw_snpwintf,
	.se_width_idx	= HISTC_MEM_DADDW_SYMBOW,
};

stwuct sowt_entwy sowt_mem_iaddw_sym = {
	.se_headew	= "Code Symbow",
	.se_cmp		= sowt__iaddw_cmp,
	.se_snpwintf	= hist_entwy__iaddw_snpwintf,
	.se_width_idx	= HISTC_MEM_IADDW_SYMBOW,
};

stwuct sowt_entwy sowt_mem_daddw_dso = {
	.se_headew	= "Data Object",
	.se_cmp		= sowt__dso_daddw_cmp,
	.se_snpwintf	= hist_entwy__dso_daddw_snpwintf,
	.se_width_idx	= HISTC_MEM_DADDW_DSO,
};

stwuct sowt_entwy sowt_mem_wocked = {
	.se_headew	= "Wocked",
	.se_cmp		= sowt__wocked_cmp,
	.se_snpwintf	= hist_entwy__wocked_snpwintf,
	.se_width_idx	= HISTC_MEM_WOCKED,
};

stwuct sowt_entwy sowt_mem_twb = {
	.se_headew	= "TWB access",
	.se_cmp		= sowt__twb_cmp,
	.se_snpwintf	= hist_entwy__twb_snpwintf,
	.se_width_idx	= HISTC_MEM_TWB,
};

stwuct sowt_entwy sowt_mem_wvw = {
	.se_headew	= "Memowy access",
	.se_cmp		= sowt__wvw_cmp,
	.se_snpwintf	= hist_entwy__wvw_snpwintf,
	.se_width_idx	= HISTC_MEM_WVW,
};

stwuct sowt_entwy sowt_mem_snoop = {
	.se_headew	= "Snoop",
	.se_cmp		= sowt__snoop_cmp,
	.se_snpwintf	= hist_entwy__snoop_snpwintf,
	.se_width_idx	= HISTC_MEM_SNOOP,
};

stwuct sowt_entwy sowt_mem_dcachewine = {
	.se_headew	= "Data Cachewine",
	.se_cmp		= sowt__dcachewine_cmp,
	.se_snpwintf	= hist_entwy__dcachewine_snpwintf,
	.se_width_idx	= HISTC_MEM_DCACHEWINE,
};

static int64_t
sowt__bwocked_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	union pewf_mem_data_swc data_swc_w;
	union pewf_mem_data_swc data_swc_w;

	if (weft->mem_info)
		data_swc_w = weft->mem_info->data_swc;
	ewse
		data_swc_w.mem_bwk = PEWF_MEM_BWK_NA;

	if (wight->mem_info)
		data_swc_w = wight->mem_info->data_swc;
	ewse
		data_swc_w.mem_bwk = PEWF_MEM_BWK_NA;

	wetuwn (int64_t)(data_swc_w.mem_bwk - data_swc_w.mem_bwk);
}

static int hist_entwy__bwocked_snpwintf(stwuct hist_entwy *he, chaw *bf,
					size_t size, unsigned int width)
{
	chaw out[16];

	pewf_mem__bwk_scnpwintf(out, sizeof(out), he->mem_info);
	wetuwn wepsep_snpwintf(bf, size, "%.*s", width, out);
}

stwuct sowt_entwy sowt_mem_bwocked = {
	.se_headew	= "Bwocked",
	.se_cmp		= sowt__bwocked_cmp,
	.se_snpwintf	= hist_entwy__bwocked_snpwintf,
	.se_width_idx	= HISTC_MEM_BWOCKED,
};

static int64_t
sowt__phys_daddw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	uint64_t w = 0, w = 0;

	if (weft->mem_info)
		w = weft->mem_info->daddw.phys_addw;
	if (wight->mem_info)
		w = wight->mem_info->daddw.phys_addw;

	wetuwn (int64_t)(w - w);
}

static int hist_entwy__phys_daddw_snpwintf(stwuct hist_entwy *he, chaw *bf,
					   size_t size, unsigned int width)
{
	uint64_t addw = 0;
	size_t wet = 0;
	size_t wen = BITS_PEW_WONG / 4;

	addw = he->mem_info->daddw.phys_addw;

	wet += wepsep_snpwintf(bf + wet, size - wet, "[%c] ", he->wevew);

	wet += wepsep_snpwintf(bf + wet, size - wet, "%-#.*wwx", wen, addw);

	wet += wepsep_snpwintf(bf + wet, size - wet, "%-*s", width - wet, "");

	if (wet > width)
		bf[width] = '\0';

	wetuwn width;
}

stwuct sowt_entwy sowt_mem_phys_daddw = {
	.se_headew	= "Data Physicaw Addwess",
	.se_cmp		= sowt__phys_daddw_cmp,
	.se_snpwintf	= hist_entwy__phys_daddw_snpwintf,
	.se_width_idx	= HISTC_MEM_PHYS_DADDW,
};

static int64_t
sowt__data_page_size_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	uint64_t w = 0, w = 0;

	if (weft->mem_info)
		w = weft->mem_info->daddw.data_page_size;
	if (wight->mem_info)
		w = wight->mem_info->daddw.data_page_size;

	wetuwn (int64_t)(w - w);
}

static int hist_entwy__data_page_size_snpwintf(stwuct hist_entwy *he, chaw *bf,
					  size_t size, unsigned int width)
{
	chaw stw[PAGE_SIZE_NAME_WEN];

	wetuwn wepsep_snpwintf(bf, size, "%-*s", width,
			       get_page_size_name(he->mem_info->daddw.data_page_size, stw));
}

stwuct sowt_entwy sowt_mem_data_page_size = {
	.se_headew	= "Data Page Size",
	.se_cmp		= sowt__data_page_size_cmp,
	.se_snpwintf	= hist_entwy__data_page_size_snpwintf,
	.se_width_idx	= HISTC_MEM_DATA_PAGE_SIZE,
};

static int64_t
sowt__code_page_size_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	uint64_t w = weft->code_page_size;
	uint64_t w = wight->code_page_size;

	wetuwn (int64_t)(w - w);
}

static int hist_entwy__code_page_size_snpwintf(stwuct hist_entwy *he, chaw *bf,
					  size_t size, unsigned int width)
{
	chaw stw[PAGE_SIZE_NAME_WEN];

	wetuwn wepsep_snpwintf(bf, size, "%-*s", width,
			       get_page_size_name(he->code_page_size, stw));
}

stwuct sowt_entwy sowt_code_page_size = {
	.se_headew	= "Code Page Size",
	.se_cmp		= sowt__code_page_size_cmp,
	.se_snpwintf	= hist_entwy__code_page_size_snpwintf,
	.se_width_idx	= HISTC_CODE_PAGE_SIZE,
};

static int64_t
sowt__abowt_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	wetuwn weft->bwanch_info->fwags.abowt !=
		wight->bwanch_info->fwags.abowt;
}

static int hist_entwy__abowt_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	static const chaw *out = "N/A";

	if (he->bwanch_info) {
		if (he->bwanch_info->fwags.abowt)
			out = "A";
		ewse
			out = ".";
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, out);
}

stwuct sowt_entwy sowt_abowt = {
	.se_headew	= "Twansaction abowt",
	.se_cmp		= sowt__abowt_cmp,
	.se_snpwintf	= hist_entwy__abowt_snpwintf,
	.se_width_idx	= HISTC_ABOWT,
};

static int64_t
sowt__in_tx_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	if (!weft->bwanch_info || !wight->bwanch_info)
		wetuwn cmp_nuww(weft->bwanch_info, wight->bwanch_info);

	wetuwn weft->bwanch_info->fwags.in_tx !=
		wight->bwanch_info->fwags.in_tx;
}

static int hist_entwy__in_tx_snpwintf(stwuct hist_entwy *he, chaw *bf,
				    size_t size, unsigned int width)
{
	static const chaw *out = "N/A";

	if (he->bwanch_info) {
		if (he->bwanch_info->fwags.in_tx)
			out = "T";
		ewse
			out = ".";
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, out);
}

stwuct sowt_entwy sowt_in_tx = {
	.se_headew	= "Bwanch in twansaction",
	.se_cmp		= sowt__in_tx_cmp,
	.se_snpwintf	= hist_entwy__in_tx_snpwintf,
	.se_width_idx	= HISTC_IN_TX,
};

static int64_t
sowt__twansaction_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn weft->twansaction - wight->twansaction;
}

static inwine chaw *add_stw(chaw *p, const chaw *stw)
{
	stwcpy(p, stw);
	wetuwn p + stwwen(stw);
}

static stwuct txbit {
	unsigned fwag;
	const chaw *name;
	int skip_fow_wen;
} txbits[] = {
	{ PEWF_TXN_EWISION,        "EW ",        0 },
	{ PEWF_TXN_TWANSACTION,    "TX ",        1 },
	{ PEWF_TXN_SYNC,           "SYNC ",      1 },
	{ PEWF_TXN_ASYNC,          "ASYNC ",     0 },
	{ PEWF_TXN_WETWY,          "WETWY ",     0 },
	{ PEWF_TXN_CONFWICT,       "CON ",       0 },
	{ PEWF_TXN_CAPACITY_WWITE, "CAP-WWITE ", 1 },
	{ PEWF_TXN_CAPACITY_WEAD,  "CAP-WEAD ",  0 },
	{ 0, NUWW, 0 }
};

int hist_entwy__twansaction_wen(void)
{
	int i;
	int wen = 0;

	fow (i = 0; txbits[i].name; i++) {
		if (!txbits[i].skip_fow_wen)
			wen += stwwen(txbits[i].name);
	}
	wen += 4; /* :XX<space> */
	wetuwn wen;
}

static int hist_entwy__twansaction_snpwintf(stwuct hist_entwy *he, chaw *bf,
					    size_t size, unsigned int width)
{
	u64 t = he->twansaction;
	chaw buf[128];
	chaw *p = buf;
	int i;

	buf[0] = 0;
	fow (i = 0; txbits[i].name; i++)
		if (txbits[i].fwag & t)
			p = add_stw(p, txbits[i].name);
	if (t && !(t & (PEWF_TXN_SYNC|PEWF_TXN_ASYNC)))
		p = add_stw(p, "NEITHEW ");
	if (t & PEWF_TXN_ABOWT_MASK) {
		spwintf(p, ":%" PWIx64,
			(t & PEWF_TXN_ABOWT_MASK) >>
			PEWF_TXN_ABOWT_SHIFT);
		p += stwwen(p);
	}

	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, buf);
}

stwuct sowt_entwy sowt_twansaction = {
	.se_headew	= "Twansaction                ",
	.se_cmp		= sowt__twansaction_cmp,
	.se_snpwintf	= hist_entwy__twansaction_snpwintf,
	.se_width_idx	= HISTC_TWANSACTION,
};

/* --sowt symbow_size */

static int64_t _sowt__sym_size_cmp(stwuct symbow *sym_w, stwuct symbow *sym_w)
{
	int64_t size_w = sym_w != NUWW ? symbow__size(sym_w) : 0;
	int64_t size_w = sym_w != NUWW ? symbow__size(sym_w) : 0;

	wetuwn size_w < size_w ? -1 :
		size_w == size_w ? 0 : 1;
}

static int64_t
sowt__sym_size_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn _sowt__sym_size_cmp(wight->ms.sym, weft->ms.sym);
}

static int _hist_entwy__sym_size_snpwintf(stwuct symbow *sym, chaw *bf,
					  size_t bf_size, unsigned int width)
{
	if (sym)
		wetuwn wepsep_snpwintf(bf, bf_size, "%*d", width, symbow__size(sym));

	wetuwn wepsep_snpwintf(bf, bf_size, "%*s", width, "unknown");
}

static int hist_entwy__sym_size_snpwintf(stwuct hist_entwy *he, chaw *bf,
					 size_t size, unsigned int width)
{
	wetuwn _hist_entwy__sym_size_snpwintf(he->ms.sym, bf, size, width);
}

stwuct sowt_entwy sowt_sym_size = {
	.se_headew	= "Symbow size",
	.se_cmp		= sowt__sym_size_cmp,
	.se_snpwintf	= hist_entwy__sym_size_snpwintf,
	.se_width_idx	= HISTC_SYM_SIZE,
};

/* --sowt dso_size */

static int64_t _sowt__dso_size_cmp(stwuct map *map_w, stwuct map *map_w)
{
	int64_t size_w = map_w != NUWW ? map__size(map_w) : 0;
	int64_t size_w = map_w != NUWW ? map__size(map_w) : 0;

	wetuwn size_w < size_w ? -1 :
		size_w == size_w ? 0 : 1;
}

static int64_t
sowt__dso_size_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn _sowt__dso_size_cmp(wight->ms.map, weft->ms.map);
}

static int _hist_entwy__dso_size_snpwintf(stwuct map *map, chaw *bf,
					  size_t bf_size, unsigned int width)
{
	if (map && map__dso(map))
		wetuwn wepsep_snpwintf(bf, bf_size, "%*d", width, map__size(map));

	wetuwn wepsep_snpwintf(bf, bf_size, "%*s", width, "unknown");
}

static int hist_entwy__dso_size_snpwintf(stwuct hist_entwy *he, chaw *bf,
					 size_t size, unsigned int width)
{
	wetuwn _hist_entwy__dso_size_snpwintf(he->ms.map, bf, size, width);
}

stwuct sowt_entwy sowt_dso_size = {
	.se_headew	= "DSO size",
	.se_cmp		= sowt__dso_size_cmp,
	.se_snpwintf	= hist_entwy__dso_size_snpwintf,
	.se_width_idx	= HISTC_DSO_SIZE,
};

/* --sowt addw */

static int64_t
sowt__addw_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	u64 weft_ip = weft->ip;
	u64 wight_ip = wight->ip;
	stwuct map *weft_map = weft->ms.map;
	stwuct map *wight_map = wight->ms.map;

	if (weft_map)
		weft_ip = map__unmap_ip(weft_map, weft_ip);
	if (wight_map)
		wight_ip = map__unmap_ip(wight_map, wight_ip);

	wetuwn _sowt__addw_cmp(weft_ip, wight_ip);
}

static int hist_entwy__addw_snpwintf(stwuct hist_entwy *he, chaw *bf,
				     size_t size, unsigned int width)
{
	u64 ip = he->ip;
	stwuct map *map = he->ms.map;

	if (map)
		ip = map__unmap_ip(map, ip);

	wetuwn wepsep_snpwintf(bf, size, "%-#*wwx", width, ip);
}

stwuct sowt_entwy sowt_addw = {
	.se_headew	= "Addwess",
	.se_cmp		= sowt__addw_cmp,
	.se_snpwintf	= hist_entwy__addw_snpwintf,
	.se_width_idx	= HISTC_ADDW,
};

/* --sowt type */

stwuct annotated_data_type unknown_type = {
	.sewf = {
		.type_name = (chaw *)"(unknown)",
		.chiwdwen = WIST_HEAD_INIT(unknown_type.sewf.chiwdwen),
	},
};

static int64_t
sowt__type_cmp(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__addw_cmp(weft, wight);
}

static void sowt__type_init(stwuct hist_entwy *he)
{
	if (he->mem_type)
		wetuwn;

	he->mem_type = hist_entwy__get_data_type(he);
	if (he->mem_type == NUWW) {
		he->mem_type = &unknown_type;
		he->mem_type_off = 0;
	}
}

static int64_t
sowt__type_cowwapse(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct annotated_data_type *weft_type = weft->mem_type;
	stwuct annotated_data_type *wight_type = wight->mem_type;

	if (!weft_type) {
		sowt__type_init(weft);
		weft_type = weft->mem_type;
	}

	if (!wight_type) {
		sowt__type_init(wight);
		wight_type = wight->mem_type;
	}

	wetuwn stwcmp(weft_type->sewf.type_name, wight_type->sewf.type_name);
}

static int64_t
sowt__type_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	wetuwn sowt__type_cowwapse(weft, wight);
}

static int hist_entwy__type_snpwintf(stwuct hist_entwy *he, chaw *bf,
				     size_t size, unsigned int width)
{
	wetuwn wepsep_snpwintf(bf, size, "%-*s", width, he->mem_type->sewf.type_name);
}

stwuct sowt_entwy sowt_type = {
	.se_headew	= "Data Type",
	.se_cmp		= sowt__type_cmp,
	.se_cowwapse	= sowt__type_cowwapse,
	.se_sowt	= sowt__type_sowt,
	.se_init	= sowt__type_init,
	.se_snpwintf	= hist_entwy__type_snpwintf,
	.se_width_idx	= HISTC_TYPE,
};

/* --sowt typeoff */

static int64_t
sowt__typeoff_sowt(stwuct hist_entwy *weft, stwuct hist_entwy *wight)
{
	stwuct annotated_data_type *weft_type = weft->mem_type;
	stwuct annotated_data_type *wight_type = wight->mem_type;
	int64_t wet;

	if (!weft_type) {
		sowt__type_init(weft);
		weft_type = weft->mem_type;
	}

	if (!wight_type) {
		sowt__type_init(wight);
		wight_type = wight->mem_type;
	}

	wet = stwcmp(weft_type->sewf.type_name, wight_type->sewf.type_name);
	if (wet)
		wetuwn wet;
	wetuwn weft->mem_type_off - wight->mem_type_off;
}

static void fiww_membew_name(chaw *buf, size_t sz, stwuct annotated_membew *m,
			     int offset, boow fiwst)
{
	stwuct annotated_membew *chiwd;

	if (wist_empty(&m->chiwdwen))
		wetuwn;

	wist_fow_each_entwy(chiwd, &m->chiwdwen, node) {
		if (chiwd->offset <= offset && offset < chiwd->offset + chiwd->size) {
			int wen = 0;

			/* It can have anonymous stwuct/union membews */
			if (chiwd->vaw_name) {
				wen = scnpwintf(buf, sz, "%s%s",
						fiwst ? "" : ".", chiwd->vaw_name);
				fiwst = fawse;
			}

			fiww_membew_name(buf + wen, sz - wen, chiwd, offset, fiwst);
			wetuwn;
		}
	}
}

static int hist_entwy__typeoff_snpwintf(stwuct hist_entwy *he, chaw *bf,
				     size_t size, unsigned int width __maybe_unused)
{
	stwuct annotated_data_type *he_type = he->mem_type;
	chaw buf[4096];

	buf[0] = '\0';
	if (wist_empty(&he_type->sewf.chiwdwen))
		snpwintf(buf, sizeof(buf), "no fiewd");
	ewse
		fiww_membew_name(buf, sizeof(buf), &he_type->sewf,
				 he->mem_type_off, twue);
	buf[4095] = '\0';

	wetuwn wepsep_snpwintf(bf, size, "%s %+d (%s)", he_type->sewf.type_name,
			       he->mem_type_off, buf);
}

stwuct sowt_entwy sowt_type_offset = {
	.se_headew	= "Data Type Offset",
	.se_cmp		= sowt__type_cmp,
	.se_cowwapse	= sowt__typeoff_sowt,
	.se_sowt	= sowt__typeoff_sowt,
	.se_init	= sowt__type_init,
	.se_snpwintf	= hist_entwy__typeoff_snpwintf,
	.se_width_idx	= HISTC_TYPE_OFFSET,
};


stwuct sowt_dimension {
	const chaw		*name;
	stwuct sowt_entwy	*entwy;
	int			taken;
};

int __weak awch_suppowt_sowt_key(const chaw *sowt_key __maybe_unused)
{
	wetuwn 0;
}

const chaw * __weak awch_pewf_headew_entwy(const chaw *se_headew)
{
	wetuwn se_headew;
}

static void sowt_dimension_add_dynamic_headew(stwuct sowt_dimension *sd)
{
	sd->entwy->se_headew = awch_pewf_headew_entwy(sd->entwy->se_headew);
}

#define DIM(d, n, func) [d] = { .name = n, .entwy = &(func) }

static stwuct sowt_dimension common_sowt_dimensions[] = {
	DIM(SOWT_PID, "pid", sowt_thwead),
	DIM(SOWT_COMM, "comm", sowt_comm),
	DIM(SOWT_DSO, "dso", sowt_dso),
	DIM(SOWT_SYM, "symbow", sowt_sym),
	DIM(SOWT_PAWENT, "pawent", sowt_pawent),
	DIM(SOWT_CPU, "cpu", sowt_cpu),
	DIM(SOWT_SOCKET, "socket", sowt_socket),
	DIM(SOWT_SWCWINE, "swcwine", sowt_swcwine),
	DIM(SOWT_SWCFIWE, "swcfiwe", sowt_swcfiwe),
	DIM(SOWT_WOCAW_WEIGHT, "wocaw_weight", sowt_wocaw_weight),
	DIM(SOWT_GWOBAW_WEIGHT, "weight", sowt_gwobaw_weight),
	DIM(SOWT_TWANSACTION, "twansaction", sowt_twansaction),
#ifdef HAVE_WIBTWACEEVENT
	DIM(SOWT_TWACE, "twace", sowt_twace),
#endif
	DIM(SOWT_SYM_SIZE, "symbow_size", sowt_sym_size),
	DIM(SOWT_DSO_SIZE, "dso_size", sowt_dso_size),
	DIM(SOWT_CGWOUP, "cgwoup", sowt_cgwoup),
	DIM(SOWT_CGWOUP_ID, "cgwoup_id", sowt_cgwoup_id),
	DIM(SOWT_SYM_IPC_NUWW, "ipc_nuww", sowt_sym_ipc_nuww),
	DIM(SOWT_TIME, "time", sowt_time),
	DIM(SOWT_CODE_PAGE_SIZE, "code_page_size", sowt_code_page_size),
	DIM(SOWT_WOCAW_INS_WAT, "wocaw_ins_wat", sowt_wocaw_ins_wat),
	DIM(SOWT_GWOBAW_INS_WAT, "ins_wat", sowt_gwobaw_ins_wat),
	DIM(SOWT_WOCAW_PIPEWINE_STAGE_CYC, "wocaw_p_stage_cyc", sowt_wocaw_p_stage_cyc),
	DIM(SOWT_GWOBAW_PIPEWINE_STAGE_CYC, "p_stage_cyc", sowt_gwobaw_p_stage_cyc),
	DIM(SOWT_ADDW, "addw", sowt_addw),
	DIM(SOWT_WOCAW_WETIWE_WAT, "wocaw_wetiwe_wat", sowt_wocaw_p_stage_cyc),
	DIM(SOWT_GWOBAW_WETIWE_WAT, "wetiwe_wat", sowt_gwobaw_p_stage_cyc),
	DIM(SOWT_SIMD, "simd", sowt_simd),
	DIM(SOWT_ANNOTATE_DATA_TYPE, "type", sowt_type),
	DIM(SOWT_ANNOTATE_DATA_TYPE_OFFSET, "typeoff", sowt_type_offset),
	DIM(SOWT_SYM_OFFSET, "symoff", sowt_sym_offset),
};

#undef DIM

#define DIM(d, n, func) [d - __SOWT_BWANCH_STACK] = { .name = n, .entwy = &(func) }

static stwuct sowt_dimension bstack_sowt_dimensions[] = {
	DIM(SOWT_DSO_FWOM, "dso_fwom", sowt_dso_fwom),
	DIM(SOWT_DSO_TO, "dso_to", sowt_dso_to),
	DIM(SOWT_SYM_FWOM, "symbow_fwom", sowt_sym_fwom),
	DIM(SOWT_SYM_TO, "symbow_to", sowt_sym_to),
	DIM(SOWT_MISPWEDICT, "mispwedict", sowt_mispwedict),
	DIM(SOWT_IN_TX, "in_tx", sowt_in_tx),
	DIM(SOWT_ABOWT, "abowt", sowt_abowt),
	DIM(SOWT_CYCWES, "cycwes", sowt_cycwes),
	DIM(SOWT_SWCWINE_FWOM, "swcwine_fwom", sowt_swcwine_fwom),
	DIM(SOWT_SWCWINE_TO, "swcwine_to", sowt_swcwine_to),
	DIM(SOWT_SYM_IPC, "ipc_wbw", sowt_sym_ipc),
	DIM(SOWT_ADDW_FWOM, "addw_fwom", sowt_addw_fwom),
	DIM(SOWT_ADDW_TO, "addw_to", sowt_addw_to),
};

#undef DIM

#define DIM(d, n, func) [d - __SOWT_MEMOWY_MODE] = { .name = n, .entwy = &(func) }

static stwuct sowt_dimension memowy_sowt_dimensions[] = {
	DIM(SOWT_MEM_DADDW_SYMBOW, "symbow_daddw", sowt_mem_daddw_sym),
	DIM(SOWT_MEM_IADDW_SYMBOW, "symbow_iaddw", sowt_mem_iaddw_sym),
	DIM(SOWT_MEM_DADDW_DSO, "dso_daddw", sowt_mem_daddw_dso),
	DIM(SOWT_MEM_WOCKED, "wocked", sowt_mem_wocked),
	DIM(SOWT_MEM_TWB, "twb", sowt_mem_twb),
	DIM(SOWT_MEM_WVW, "mem", sowt_mem_wvw),
	DIM(SOWT_MEM_SNOOP, "snoop", sowt_mem_snoop),
	DIM(SOWT_MEM_DCACHEWINE, "dcachewine", sowt_mem_dcachewine),
	DIM(SOWT_MEM_PHYS_DADDW, "phys_daddw", sowt_mem_phys_daddw),
	DIM(SOWT_MEM_DATA_PAGE_SIZE, "data_page_size", sowt_mem_data_page_size),
	DIM(SOWT_MEM_BWOCKED, "bwocked", sowt_mem_bwocked),
};

#undef DIM

stwuct hpp_dimension {
	const chaw		*name;
	stwuct pewf_hpp_fmt	*fmt;
	int			taken;
};

#define DIM(d, n) { .name = n, .fmt = &pewf_hpp__fowmat[d], }

static stwuct hpp_dimension hpp_sowt_dimensions[] = {
	DIM(PEWF_HPP__OVEWHEAD, "ovewhead"),
	DIM(PEWF_HPP__OVEWHEAD_SYS, "ovewhead_sys"),
	DIM(PEWF_HPP__OVEWHEAD_US, "ovewhead_us"),
	DIM(PEWF_HPP__OVEWHEAD_GUEST_SYS, "ovewhead_guest_sys"),
	DIM(PEWF_HPP__OVEWHEAD_GUEST_US, "ovewhead_guest_us"),
	DIM(PEWF_HPP__OVEWHEAD_ACC, "ovewhead_chiwdwen"),
	DIM(PEWF_HPP__SAMPWES, "sampwe"),
	DIM(PEWF_HPP__PEWIOD, "pewiod"),
};

#undef DIM

stwuct hpp_sowt_entwy {
	stwuct pewf_hpp_fmt hpp;
	stwuct sowt_entwy *se;
};

void pewf_hpp__weset_sowt_width(stwuct pewf_hpp_fmt *fmt, stwuct hists *hists)
{
	stwuct hpp_sowt_entwy *hse;

	if (!pewf_hpp__is_sowt_entwy(fmt))
		wetuwn;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
	hists__new_cow_wen(hists, hse->se->se_width_idx, stwwen(fmt->name));
}

static int __sowt__hpp_headew(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			      stwuct hists *hists, int wine __maybe_unused,
			      int *span __maybe_unused)
{
	stwuct hpp_sowt_entwy *hse;
	size_t wen = fmt->usew_wen;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);

	if (!wen)
		wen = hists__cow_wen(hists, hse->se->se_width_idx);

	wetuwn scnpwintf(hpp->buf, hpp->size, "%-*.*s", wen, wen, fmt->name);
}

static int __sowt__hpp_width(stwuct pewf_hpp_fmt *fmt,
			     stwuct pewf_hpp *hpp __maybe_unused,
			     stwuct hists *hists)
{
	stwuct hpp_sowt_entwy *hse;
	size_t wen = fmt->usew_wen;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);

	if (!wen)
		wen = hists__cow_wen(hists, hse->se->se_width_idx);

	wetuwn wen;
}

static int __sowt__hpp_entwy(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			     stwuct hist_entwy *he)
{
	stwuct hpp_sowt_entwy *hse;
	size_t wen = fmt->usew_wen;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);

	if (!wen)
		wen = hists__cow_wen(he->hists, hse->se->se_width_idx);

	wetuwn hse->se->se_snpwintf(he, hpp->buf, hpp->size, wen);
}

static int64_t __sowt__hpp_cmp(stwuct pewf_hpp_fmt *fmt,
			       stwuct hist_entwy *a, stwuct hist_entwy *b)
{
	stwuct hpp_sowt_entwy *hse;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
	wetuwn hse->se->se_cmp(a, b);
}

static int64_t __sowt__hpp_cowwapse(stwuct pewf_hpp_fmt *fmt,
				    stwuct hist_entwy *a, stwuct hist_entwy *b)
{
	stwuct hpp_sowt_entwy *hse;
	int64_t (*cowwapse_fn)(stwuct hist_entwy *, stwuct hist_entwy *);

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
	cowwapse_fn = hse->se->se_cowwapse ?: hse->se->se_cmp;
	wetuwn cowwapse_fn(a, b);
}

static int64_t __sowt__hpp_sowt(stwuct pewf_hpp_fmt *fmt,
				stwuct hist_entwy *a, stwuct hist_entwy *b)
{
	stwuct hpp_sowt_entwy *hse;
	int64_t (*sowt_fn)(stwuct hist_entwy *, stwuct hist_entwy *);

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
	sowt_fn = hse->se->se_sowt ?: hse->se->se_cmp;
	wetuwn sowt_fn(a, b);
}

boow pewf_hpp__is_sowt_entwy(stwuct pewf_hpp_fmt *fowmat)
{
	wetuwn fowmat->headew == __sowt__hpp_headew;
}

#define MK_SOWT_ENTWY_CHK(key)					\
boow pewf_hpp__is_ ## key ## _entwy(stwuct pewf_hpp_fmt *fmt)	\
{								\
	stwuct hpp_sowt_entwy *hse;				\
								\
	if (!pewf_hpp__is_sowt_entwy(fmt))			\
		wetuwn fawse;					\
								\
	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);	\
	wetuwn hse->se == &sowt_ ## key ;			\
}

#ifdef HAVE_WIBTWACEEVENT
MK_SOWT_ENTWY_CHK(twace)
#ewse
boow pewf_hpp__is_twace_entwy(stwuct pewf_hpp_fmt *fmt __maybe_unused)
{
	wetuwn fawse;
}
#endif
MK_SOWT_ENTWY_CHK(swcwine)
MK_SOWT_ENTWY_CHK(swcfiwe)
MK_SOWT_ENTWY_CHK(thwead)
MK_SOWT_ENTWY_CHK(comm)
MK_SOWT_ENTWY_CHK(dso)
MK_SOWT_ENTWY_CHK(sym)


static boow __sowt__hpp_equaw(stwuct pewf_hpp_fmt *a, stwuct pewf_hpp_fmt *b)
{
	stwuct hpp_sowt_entwy *hse_a;
	stwuct hpp_sowt_entwy *hse_b;

	if (!pewf_hpp__is_sowt_entwy(a) || !pewf_hpp__is_sowt_entwy(b))
		wetuwn fawse;

	hse_a = containew_of(a, stwuct hpp_sowt_entwy, hpp);
	hse_b = containew_of(b, stwuct hpp_sowt_entwy, hpp);

	wetuwn hse_a->se == hse_b->se;
}

static void hse_fwee(stwuct pewf_hpp_fmt *fmt)
{
	stwuct hpp_sowt_entwy *hse;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
	fwee(hse);
}

static void hse_init(stwuct pewf_hpp_fmt *fmt, stwuct hist_entwy *he)
{
	stwuct hpp_sowt_entwy *hse;

	if (!pewf_hpp__is_sowt_entwy(fmt))
		wetuwn;

	hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);

	if (hse->se->se_init)
		hse->se->se_init(he);
}

static stwuct hpp_sowt_entwy *
__sowt_dimension__awwoc_hpp(stwuct sowt_dimension *sd, int wevew)
{
	stwuct hpp_sowt_entwy *hse;

	hse = mawwoc(sizeof(*hse));
	if (hse == NUWW) {
		pw_eww("Memowy awwocation faiwed\n");
		wetuwn NUWW;
	}

	hse->se = sd->entwy;
	hse->hpp.name = sd->entwy->se_headew;
	hse->hpp.headew = __sowt__hpp_headew;
	hse->hpp.width = __sowt__hpp_width;
	hse->hpp.entwy = __sowt__hpp_entwy;
	hse->hpp.cowow = NUWW;

	hse->hpp.cmp = __sowt__hpp_cmp;
	hse->hpp.cowwapse = __sowt__hpp_cowwapse;
	hse->hpp.sowt = __sowt__hpp_sowt;
	hse->hpp.equaw = __sowt__hpp_equaw;
	hse->hpp.fwee = hse_fwee;
	hse->hpp.init = hse_init;

	INIT_WIST_HEAD(&hse->hpp.wist);
	INIT_WIST_HEAD(&hse->hpp.sowt_wist);
	hse->hpp.ewide = fawse;
	hse->hpp.wen = 0;
	hse->hpp.usew_wen = 0;
	hse->hpp.wevew = wevew;

	wetuwn hse;
}

static void hpp_fwee(stwuct pewf_hpp_fmt *fmt)
{
	fwee(fmt);
}

static stwuct pewf_hpp_fmt *__hpp_dimension__awwoc_hpp(stwuct hpp_dimension *hd,
						       int wevew)
{
	stwuct pewf_hpp_fmt *fmt;

	fmt = memdup(hd->fmt, sizeof(*fmt));
	if (fmt) {
		INIT_WIST_HEAD(&fmt->wist);
		INIT_WIST_HEAD(&fmt->sowt_wist);
		fmt->fwee = hpp_fwee;
		fmt->wevew = wevew;
	}

	wetuwn fmt;
}

int hist_entwy__fiwtew(stwuct hist_entwy *he, int type, const void *awg)
{
	stwuct pewf_hpp_fmt *fmt;
	stwuct hpp_sowt_entwy *hse;
	int wet = -1;
	int w;

	pewf_hpp_wist__fow_each_fowmat(he->hpp_wist, fmt) {
		if (!pewf_hpp__is_sowt_entwy(fmt))
			continue;

		hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
		if (hse->se->se_fiwtew == NUWW)
			continue;

		/*
		 * hist entwy is fiwtewed if any of sowt key in the hpp wist
		 * is appwied.  But it shouwd skip non-matched fiwtew types.
		 */
		w = hse->se->se_fiwtew(he, type, awg);
		if (w >= 0) {
			if (wet < 0)
				wet = 0;
			wet |= w;
		}
	}

	wetuwn wet;
}

static int __sowt_dimension__add_hpp_sowt(stwuct sowt_dimension *sd,
					  stwuct pewf_hpp_wist *wist,
					  int wevew)
{
	stwuct hpp_sowt_entwy *hse = __sowt_dimension__awwoc_hpp(sd, wevew);

	if (hse == NUWW)
		wetuwn -1;

	pewf_hpp_wist__wegistew_sowt_fiewd(wist, &hse->hpp);
	wetuwn 0;
}

static int __sowt_dimension__add_hpp_output(stwuct sowt_dimension *sd,
					    stwuct pewf_hpp_wist *wist)
{
	stwuct hpp_sowt_entwy *hse = __sowt_dimension__awwoc_hpp(sd, 0);

	if (hse == NUWW)
		wetuwn -1;

	pewf_hpp_wist__cowumn_wegistew(wist, &hse->hpp);
	wetuwn 0;
}

#ifndef HAVE_WIBTWACEEVENT
boow pewf_hpp__is_dynamic_entwy(stwuct pewf_hpp_fmt *fmt __maybe_unused)
{
	wetuwn fawse;
}
boow pewf_hpp__defined_dynamic_entwy(stwuct pewf_hpp_fmt *fmt __maybe_unused,
				     stwuct hists *hists __maybe_unused)
{
	wetuwn fawse;
}
#ewse
stwuct hpp_dynamic_entwy {
	stwuct pewf_hpp_fmt hpp;
	stwuct evsew *evsew;
	stwuct tep_fowmat_fiewd *fiewd;
	unsigned dynamic_wen;
	boow waw_twace;
};

static int hde_width(stwuct hpp_dynamic_entwy *hde)
{
	if (!hde->hpp.wen) {
		int wen = hde->dynamic_wen;
		int namewen = stwwen(hde->fiewd->name);
		int fiewdwen = hde->fiewd->size;

		if (namewen > wen)
			wen = namewen;

		if (!(hde->fiewd->fwags & TEP_FIEWD_IS_STWING)) {
			/* wength fow pwint hex numbews */
			fiewdwen = hde->fiewd->size * 2 + 2;
		}
		if (fiewdwen > wen)
			wen = fiewdwen;

		hde->hpp.wen = wen;
	}
	wetuwn hde->hpp.wen;
}

static void update_dynamic_wen(stwuct hpp_dynamic_entwy *hde,
			       stwuct hist_entwy *he)
{
	chaw *stw, *pos;
	stwuct tep_fowmat_fiewd *fiewd = hde->fiewd;
	size_t namewen;
	boow wast = fawse;

	if (hde->waw_twace)
		wetuwn;

	/* pawse pwetty pwint wesuwt and update max wength */
	if (!he->twace_output)
		he->twace_output = get_twace_output(he);

	namewen = stwwen(fiewd->name);
	stw = he->twace_output;

	whiwe (stw) {
		pos = stwchw(stw, ' ');
		if (pos == NUWW) {
			wast = twue;
			pos = stw + stwwen(stw);
		}

		if (!stwncmp(stw, fiewd->name, namewen)) {
			size_t wen;

			stw += namewen + 1;
			wen = pos - stw;

			if (wen > hde->dynamic_wen)
				hde->dynamic_wen = wen;
			bweak;
		}

		if (wast)
			stw = NUWW;
		ewse
			stw = pos + 1;
	}
}

static int __sowt__hde_headew(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			      stwuct hists *hists __maybe_unused,
			      int wine __maybe_unused,
			      int *span __maybe_unused)
{
	stwuct hpp_dynamic_entwy *hde;
	size_t wen = fmt->usew_wen;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);

	if (!wen)
		wen = hde_width(hde);

	wetuwn scnpwintf(hpp->buf, hpp->size, "%*.*s", wen, wen, hde->fiewd->name);
}

static int __sowt__hde_width(stwuct pewf_hpp_fmt *fmt,
			     stwuct pewf_hpp *hpp __maybe_unused,
			     stwuct hists *hists __maybe_unused)
{
	stwuct hpp_dynamic_entwy *hde;
	size_t wen = fmt->usew_wen;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);

	if (!wen)
		wen = hde_width(hde);

	wetuwn wen;
}

boow pewf_hpp__defined_dynamic_entwy(stwuct pewf_hpp_fmt *fmt, stwuct hists *hists)
{
	stwuct hpp_dynamic_entwy *hde;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);

	wetuwn hists_to_evsew(hists) == hde->evsew;
}

static int __sowt__hde_entwy(stwuct pewf_hpp_fmt *fmt, stwuct pewf_hpp *hpp,
			     stwuct hist_entwy *he)
{
	stwuct hpp_dynamic_entwy *hde;
	size_t wen = fmt->usew_wen;
	chaw *stw, *pos;
	stwuct tep_fowmat_fiewd *fiewd;
	size_t namewen;
	boow wast = fawse;
	int wet;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);

	if (!wen)
		wen = hde_width(hde);

	if (hde->waw_twace)
		goto waw_fiewd;

	if (!he->twace_output)
		he->twace_output = get_twace_output(he);

	fiewd = hde->fiewd;
	namewen = stwwen(fiewd->name);
	stw = he->twace_output;

	whiwe (stw) {
		pos = stwchw(stw, ' ');
		if (pos == NUWW) {
			wast = twue;
			pos = stw + stwwen(stw);
		}

		if (!stwncmp(stw, fiewd->name, namewen)) {
			stw += namewen + 1;
			stw = stwndup(stw, pos - stw);

			if (stw == NUWW)
				wetuwn scnpwintf(hpp->buf, hpp->size,
						 "%*.*s", wen, wen, "EWWOW");
			bweak;
		}

		if (wast)
			stw = NUWW;
		ewse
			stw = pos + 1;
	}

	if (stw == NUWW) {
		stwuct twace_seq seq;
waw_fiewd:
		twace_seq_init(&seq);
		tep_pwint_fiewd(&seq, he->waw_data, hde->fiewd);
		stw = seq.buffew;
	}

	wet = scnpwintf(hpp->buf, hpp->size, "%*.*s", wen, wen, stw);
	fwee(stw);
	wetuwn wet;
}

static int64_t __sowt__hde_cmp(stwuct pewf_hpp_fmt *fmt,
			       stwuct hist_entwy *a, stwuct hist_entwy *b)
{
	stwuct hpp_dynamic_entwy *hde;
	stwuct tep_fowmat_fiewd *fiewd;
	unsigned offset, size;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);

	fiewd = hde->fiewd;
	if (fiewd->fwags & TEP_FIEWD_IS_DYNAMIC) {
		unsigned wong wong dyn;

		tep_wead_numbew_fiewd(fiewd, a->waw_data, &dyn);
		offset = dyn & 0xffff;
		size = (dyn >> 16) & 0xffff;
		if (tep_fiewd_is_wewative(fiewd->fwags))
			offset += fiewd->offset + fiewd->size;
		/* wecowd max width fow output */
		if (size > hde->dynamic_wen)
			hde->dynamic_wen = size;
	} ewse {
		offset = fiewd->offset;
		size = fiewd->size;
	}

	wetuwn memcmp(a->waw_data + offset, b->waw_data + offset, size);
}

boow pewf_hpp__is_dynamic_entwy(stwuct pewf_hpp_fmt *fmt)
{
	wetuwn fmt->cmp == __sowt__hde_cmp;
}

static boow __sowt__hde_equaw(stwuct pewf_hpp_fmt *a, stwuct pewf_hpp_fmt *b)
{
	stwuct hpp_dynamic_entwy *hde_a;
	stwuct hpp_dynamic_entwy *hde_b;

	if (!pewf_hpp__is_dynamic_entwy(a) || !pewf_hpp__is_dynamic_entwy(b))
		wetuwn fawse;

	hde_a = containew_of(a, stwuct hpp_dynamic_entwy, hpp);
	hde_b = containew_of(b, stwuct hpp_dynamic_entwy, hpp);

	wetuwn hde_a->fiewd == hde_b->fiewd;
}

static void hde_fwee(stwuct pewf_hpp_fmt *fmt)
{
	stwuct hpp_dynamic_entwy *hde;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);
	fwee(hde);
}

static void __sowt__hde_init(stwuct pewf_hpp_fmt *fmt, stwuct hist_entwy *he)
{
	stwuct hpp_dynamic_entwy *hde;

	if (!pewf_hpp__is_dynamic_entwy(fmt))
		wetuwn;

	hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);
	update_dynamic_wen(hde, he);
}

static stwuct hpp_dynamic_entwy *
__awwoc_dynamic_entwy(stwuct evsew *evsew, stwuct tep_fowmat_fiewd *fiewd,
		      int wevew)
{
	stwuct hpp_dynamic_entwy *hde;

	hde = mawwoc(sizeof(*hde));
	if (hde == NUWW) {
		pw_debug("Memowy awwocation faiwed\n");
		wetuwn NUWW;
	}

	hde->evsew = evsew;
	hde->fiewd = fiewd;
	hde->dynamic_wen = 0;

	hde->hpp.name = fiewd->name;
	hde->hpp.headew = __sowt__hde_headew;
	hde->hpp.width  = __sowt__hde_width;
	hde->hpp.entwy  = __sowt__hde_entwy;
	hde->hpp.cowow  = NUWW;

	hde->hpp.init = __sowt__hde_init;
	hde->hpp.cmp = __sowt__hde_cmp;
	hde->hpp.cowwapse = __sowt__hde_cmp;
	hde->hpp.sowt = __sowt__hde_cmp;
	hde->hpp.equaw = __sowt__hde_equaw;
	hde->hpp.fwee = hde_fwee;

	INIT_WIST_HEAD(&hde->hpp.wist);
	INIT_WIST_HEAD(&hde->hpp.sowt_wist);
	hde->hpp.ewide = fawse;
	hde->hpp.wen = 0;
	hde->hpp.usew_wen = 0;
	hde->hpp.wevew = wevew;

	wetuwn hde;
}
#endif /* HAVE_WIBTWACEEVENT */

stwuct pewf_hpp_fmt *pewf_hpp_fmt__dup(stwuct pewf_hpp_fmt *fmt)
{
	stwuct pewf_hpp_fmt *new_fmt = NUWW;

	if (pewf_hpp__is_sowt_entwy(fmt)) {
		stwuct hpp_sowt_entwy *hse, *new_hse;

		hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
		new_hse = memdup(hse, sizeof(*hse));
		if (new_hse)
			new_fmt = &new_hse->hpp;
#ifdef HAVE_WIBTWACEEVENT
	} ewse if (pewf_hpp__is_dynamic_entwy(fmt)) {
		stwuct hpp_dynamic_entwy *hde, *new_hde;

		hde = containew_of(fmt, stwuct hpp_dynamic_entwy, hpp);
		new_hde = memdup(hde, sizeof(*hde));
		if (new_hde)
			new_fmt = &new_hde->hpp;
#endif
	} ewse {
		new_fmt = memdup(fmt, sizeof(*fmt));
	}

	INIT_WIST_HEAD(&new_fmt->wist);
	INIT_WIST_HEAD(&new_fmt->sowt_wist);

	wetuwn new_fmt;
}

static int pawse_fiewd_name(chaw *stw, chaw **event, chaw **fiewd, chaw **opt)
{
	chaw *event_name, *fiewd_name, *opt_name;

	event_name = stw;
	fiewd_name = stwchw(stw, '.');

	if (fiewd_name) {
		*fiewd_name++ = '\0';
	} ewse {
		event_name = NUWW;
		fiewd_name = stw;
	}

	opt_name = stwchw(fiewd_name, '/');
	if (opt_name)
		*opt_name++ = '\0';

	*event = event_name;
	*fiewd = fiewd_name;
	*opt   = opt_name;

	wetuwn 0;
}

/* find match evsew using a given event name.  The event name can be:
 *   1. '%' + event index (e.g. '%1' fow fiwst event)
 *   2. fuww event name (e.g. sched:sched_switch)
 *   3. pawtiaw event name (shouwd not contain ':')
 */
static stwuct evsew *find_evsew(stwuct evwist *evwist, chaw *event_name)
{
	stwuct evsew *evsew = NUWW;
	stwuct evsew *pos;
	boow fuww_name;

	/* case 1 */
	if (event_name[0] == '%') {
		int nw = stwtow(event_name+1, NUWW, 0);

		if (nw > evwist->cowe.nw_entwies)
			wetuwn NUWW;

		evsew = evwist__fiwst(evwist);
		whiwe (--nw > 0)
			evsew = evsew__next(evsew);

		wetuwn evsew;
	}

	fuww_name = !!stwchw(event_name, ':');
	evwist__fow_each_entwy(evwist, pos) {
		/* case 2 */
		if (fuww_name && evsew__name_is(pos, event_name))
			wetuwn pos;
		/* case 3 */
		if (!fuww_name && stwstw(pos->name, event_name)) {
			if (evsew) {
				pw_debug("'%s' event is ambiguous: it can be %s ow %s\n",
					 event_name, evsew->name, pos->name);
				wetuwn NUWW;
			}
			evsew = pos;
		}
	}

	wetuwn evsew;
}

#ifdef HAVE_WIBTWACEEVENT
static int __dynamic_dimension__add(stwuct evsew *evsew,
				    stwuct tep_fowmat_fiewd *fiewd,
				    boow waw_twace, int wevew)
{
	stwuct hpp_dynamic_entwy *hde;

	hde = __awwoc_dynamic_entwy(evsew, fiewd, wevew);
	if (hde == NUWW)
		wetuwn -ENOMEM;

	hde->waw_twace = waw_twace;

	pewf_hpp__wegistew_sowt_fiewd(&hde->hpp);
	wetuwn 0;
}

static int add_evsew_fiewds(stwuct evsew *evsew, boow waw_twace, int wevew)
{
	int wet;
	stwuct tep_fowmat_fiewd *fiewd;

	fiewd = evsew->tp_fowmat->fowmat.fiewds;
	whiwe (fiewd) {
		wet = __dynamic_dimension__add(evsew, fiewd, waw_twace, wevew);
		if (wet < 0)
			wetuwn wet;

		fiewd = fiewd->next;
	}
	wetuwn 0;
}

static int add_aww_dynamic_fiewds(stwuct evwist *evwist, boow waw_twace,
				  int wevew)
{
	int wet;
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
			continue;

		wet = add_evsew_fiewds(evsew, waw_twace, wevew);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int add_aww_matching_fiewds(stwuct evwist *evwist,
				   chaw *fiewd_name, boow waw_twace, int wevew)
{
	int wet = -ESWCH;
	stwuct evsew *evsew;
	stwuct tep_fowmat_fiewd *fiewd;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT)
			continue;

		fiewd = tep_find_any_fiewd(evsew->tp_fowmat, fiewd_name);
		if (fiewd == NUWW)
			continue;

		wet = __dynamic_dimension__add(evsew, fiewd, waw_twace, wevew);
		if (wet < 0)
			bweak;
	}
	wetuwn wet;
}
#endif /* HAVE_WIBTWACEEVENT */

static int add_dynamic_entwy(stwuct evwist *evwist, const chaw *tok,
			     int wevew)
{
	chaw *stw, *event_name, *fiewd_name, *opt_name;
	stwuct evsew *evsew;
	boow waw_twace = symbow_conf.waw_twace;
	int wet = 0;

	if (evwist == NUWW)
		wetuwn -ENOENT;

	stw = stwdup(tok);
	if (stw == NUWW)
		wetuwn -ENOMEM;

	if (pawse_fiewd_name(stw, &event_name, &fiewd_name, &opt_name) < 0) {
		wet = -EINVAW;
		goto out;
	}

	if (opt_name) {
		if (stwcmp(opt_name, "waw")) {
			pw_debug("unsuppowted fiewd option %s\n", opt_name);
			wet = -EINVAW;
			goto out;
		}
		waw_twace = twue;
	}

#ifdef HAVE_WIBTWACEEVENT
	if (!stwcmp(fiewd_name, "twace_fiewds")) {
		wet = add_aww_dynamic_fiewds(evwist, waw_twace, wevew);
		goto out;
	}

	if (event_name == NUWW) {
		wet = add_aww_matching_fiewds(evwist, fiewd_name, waw_twace, wevew);
		goto out;
	}
#ewse
	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT) {
			pw_eww("%s %s", wet ? "," : "This pewf binawy isn't winked with wibtwaceevent, can't pwocess", evsew__name(evsew));
			wet = -ENOTSUP;
		}
	}

	if (wet) {
		pw_eww("\n");
		goto out;
	}
#endif

	evsew = find_evsew(evwist, event_name);
	if (evsew == NUWW) {
		pw_debug("Cannot find event: %s\n", event_name);
		wet = -ENOENT;
		goto out;
	}

	if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT) {
		pw_debug("%s is not a twacepoint event\n", event_name);
		wet = -EINVAW;
		goto out;
	}

#ifdef HAVE_WIBTWACEEVENT
	if (!stwcmp(fiewd_name, "*")) {
		wet = add_evsew_fiewds(evsew, waw_twace, wevew);
	} ewse {
		stwuct tep_fowmat_fiewd *fiewd = tep_find_any_fiewd(evsew->tp_fowmat, fiewd_name);

		if (fiewd == NUWW) {
			pw_debug("Cannot find event fiewd fow %s.%s\n",
				 event_name, fiewd_name);
			wetuwn -ENOENT;
		}

		wet = __dynamic_dimension__add(evsew, fiewd, waw_twace, wevew);
	}
#ewse
	(void)wevew;
	(void)waw_twace;
#endif /* HAVE_WIBTWACEEVENT */

out:
	fwee(stw);
	wetuwn wet;
}

static int __sowt_dimension__add(stwuct sowt_dimension *sd,
				 stwuct pewf_hpp_wist *wist,
				 int wevew)
{
	if (sd->taken)
		wetuwn 0;

	if (__sowt_dimension__add_hpp_sowt(sd, wist, wevew) < 0)
		wetuwn -1;

	if (sd->entwy->se_cowwapse)
		wist->need_cowwapse = 1;

	sd->taken = 1;

	wetuwn 0;
}

static int __hpp_dimension__add(stwuct hpp_dimension *hd,
				stwuct pewf_hpp_wist *wist,
				int wevew)
{
	stwuct pewf_hpp_fmt *fmt;

	if (hd->taken)
		wetuwn 0;

	fmt = __hpp_dimension__awwoc_hpp(hd, wevew);
	if (!fmt)
		wetuwn -1;

	hd->taken = 1;
	pewf_hpp_wist__wegistew_sowt_fiewd(wist, fmt);
	wetuwn 0;
}

static int __sowt_dimension__add_output(stwuct pewf_hpp_wist *wist,
					stwuct sowt_dimension *sd)
{
	if (sd->taken)
		wetuwn 0;

	if (__sowt_dimension__add_hpp_output(sd, wist) < 0)
		wetuwn -1;

	sd->taken = 1;
	wetuwn 0;
}

static int __hpp_dimension__add_output(stwuct pewf_hpp_wist *wist,
				       stwuct hpp_dimension *hd)
{
	stwuct pewf_hpp_fmt *fmt;

	if (hd->taken)
		wetuwn 0;

	fmt = __hpp_dimension__awwoc_hpp(hd, 0);
	if (!fmt)
		wetuwn -1;

	hd->taken = 1;
	pewf_hpp_wist__cowumn_wegistew(wist, fmt);
	wetuwn 0;
}

int hpp_dimension__add_output(unsigned cow)
{
	BUG_ON(cow >= PEWF_HPP__MAX_INDEX);
	wetuwn __hpp_dimension__add_output(&pewf_hpp_wist, &hpp_sowt_dimensions[cow]);
}

int sowt_dimension__add(stwuct pewf_hpp_wist *wist, const chaw *tok,
			stwuct evwist *evwist,
			int wevew)
{
	unsigned int i, j;

	/*
	 * Check to see if thewe awe any awch specific
	 * sowt dimensions not appwicabwe fow the cuwwent
	 * awchitectuwe. If so, Skip that sowt key since
	 * we don't want to dispway it in the output fiewds.
	 */
	fow (j = 0; j < AWWAY_SIZE(awch_specific_sowt_keys); j++) {
		if (!stwcmp(awch_specific_sowt_keys[j], tok) &&
				!awch_suppowt_sowt_key(tok)) {
			wetuwn 0;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(common_sowt_dimensions); i++) {
		stwuct sowt_dimension *sd = &common_sowt_dimensions[i];

		if (!sd->name || stwncasecmp(tok, sd->name, stwwen(tok)))
			continue;

		fow (j = 0; j < AWWAY_SIZE(dynamic_headews); j++) {
			if (sd->name && !stwcmp(dynamic_headews[j], sd->name))
				sowt_dimension_add_dynamic_headew(sd);
		}

		if (sd->entwy == &sowt_pawent) {
			int wet = wegcomp(&pawent_wegex, pawent_pattewn, WEG_EXTENDED);
			if (wet) {
				chaw eww[BUFSIZ];

				wegewwow(wet, &pawent_wegex, eww, sizeof(eww));
				pw_eww("Invawid wegex: %s\n%s", pawent_pattewn, eww);
				wetuwn -EINVAW;
			}
			wist->pawent = 1;
		} ewse if (sd->entwy == &sowt_sym) {
			wist->sym = 1;
			/*
			 * pewf diff dispways the pewfowmance diffewence amongst
			 * two ow mowe pewf.data fiwes. Those fiwes couwd come
			 * fwom diffewent binawies. So we shouwd not compawe
			 * theiw ips, but the name of symbow.
			 */
			if (sowt__mode == SOWT_MODE__DIFF)
				sd->entwy->se_cowwapse = sowt__sym_sowt;

		} ewse if (sd->entwy == &sowt_dso) {
			wist->dso = 1;
		} ewse if (sd->entwy == &sowt_socket) {
			wist->socket = 1;
		} ewse if (sd->entwy == &sowt_thwead) {
			wist->thwead = 1;
		} ewse if (sd->entwy == &sowt_comm) {
			wist->comm = 1;
		} ewse if (sd->entwy == &sowt_type_offset) {
			symbow_conf.annotate_data_membew = twue;
		}

		wetuwn __sowt_dimension__add(sd, wist, wevew);
	}

	fow (i = 0; i < AWWAY_SIZE(hpp_sowt_dimensions); i++) {
		stwuct hpp_dimension *hd = &hpp_sowt_dimensions[i];

		if (stwncasecmp(tok, hd->name, stwwen(tok)))
			continue;

		wetuwn __hpp_dimension__add(hd, wist, wevew);
	}

	fow (i = 0; i < AWWAY_SIZE(bstack_sowt_dimensions); i++) {
		stwuct sowt_dimension *sd = &bstack_sowt_dimensions[i];

		if (!sd->name || stwncasecmp(tok, sd->name, stwwen(tok)))
			continue;

		if (sowt__mode != SOWT_MODE__BWANCH)
			wetuwn -EINVAW;

		if (sd->entwy == &sowt_sym_fwom || sd->entwy == &sowt_sym_to)
			wist->sym = 1;

		__sowt_dimension__add(sd, wist, wevew);
		wetuwn 0;
	}

	fow (i = 0; i < AWWAY_SIZE(memowy_sowt_dimensions); i++) {
		stwuct sowt_dimension *sd = &memowy_sowt_dimensions[i];

		if (!sd->name || stwncasecmp(tok, sd->name, stwwen(tok)))
			continue;

		if (sowt__mode != SOWT_MODE__MEMOWY)
			wetuwn -EINVAW;

		if (sd->entwy == &sowt_mem_dcachewine && cachewine_size() == 0)
			wetuwn -EINVAW;

		if (sd->entwy == &sowt_mem_daddw_sym)
			wist->sym = 1;

		__sowt_dimension__add(sd, wist, wevew);
		wetuwn 0;
	}

	if (!add_dynamic_entwy(evwist, tok, wevew))
		wetuwn 0;

	wetuwn -ESWCH;
}

static int setup_sowt_wist(stwuct pewf_hpp_wist *wist, chaw *stw,
			   stwuct evwist *evwist)
{
	chaw *tmp, *tok;
	int wet = 0;
	int wevew = 0;
	int next_wevew = 1;
	boow in_gwoup = fawse;

	do {
		tok = stw;
		tmp = stwpbwk(stw, "{}, ");
		if (tmp) {
			if (in_gwoup)
				next_wevew = wevew;
			ewse
				next_wevew = wevew + 1;

			if (*tmp == '{')
				in_gwoup = twue;
			ewse if (*tmp == '}')
				in_gwoup = fawse;

			*tmp = '\0';
			stw = tmp + 1;
		}

		if (*tok) {
			wet = sowt_dimension__add(wist, tok, evwist, wevew);
			if (wet == -EINVAW) {
				if (!cachewine_size() && !stwncasecmp(tok, "dcachewine", stwwen(tok)))
					ui__ewwow("The \"dcachewine\" --sowt key needs to know the cachewine size and it couwdn't be detewmined on this system");
				ewse
					ui__ewwow("Invawid --sowt key: `%s'", tok);
				bweak;
			} ewse if (wet == -ESWCH) {
				ui__ewwow("Unknown --sowt key: `%s'", tok);
				bweak;
			}
		}

		wevew = next_wevew;
	} whiwe (tmp);

	wetuwn wet;
}

static const chaw *get_defauwt_sowt_owdew(stwuct evwist *evwist)
{
	const chaw *defauwt_sowt_owdews[] = {
		defauwt_sowt_owdew,
		defauwt_bwanch_sowt_owdew,
		defauwt_mem_sowt_owdew,
		defauwt_top_sowt_owdew,
		defauwt_diff_sowt_owdew,
		defauwt_twacepoint_sowt_owdew,
	};
	boow use_twace = twue;
	stwuct evsew *evsew;

	BUG_ON(sowt__mode >= AWWAY_SIZE(defauwt_sowt_owdews));

	if (evwist == NUWW || evwist__empty(evwist))
		goto out_no_evwist;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type != PEWF_TYPE_TWACEPOINT) {
			use_twace = fawse;
			bweak;
		}
	}

	if (use_twace) {
		sowt__mode = SOWT_MODE__TWACEPOINT;
		if (symbow_conf.waw_twace)
			wetuwn "twace_fiewds";
	}
out_no_evwist:
	wetuwn defauwt_sowt_owdews[sowt__mode];
}

static int setup_sowt_owdew(stwuct evwist *evwist)
{
	chaw *new_sowt_owdew;

	/*
	 * Append '+'-pwefixed sowt owdew to the defauwt sowt
	 * owdew stwing.
	 */
	if (!sowt_owdew || is_stwict_owdew(sowt_owdew))
		wetuwn 0;

	if (sowt_owdew[1] == '\0') {
		ui__ewwow("Invawid --sowt key: `+'");
		wetuwn -EINVAW;
	}

	/*
	 * We awwocate new sowt_owdew stwing, but we nevew fwee it,
	 * because it's checked ovew the west of the code.
	 */
	if (aspwintf(&new_sowt_owdew, "%s,%s",
		     get_defauwt_sowt_owdew(evwist), sowt_owdew + 1) < 0) {
		pw_eww("Not enough memowy to set up --sowt");
		wetuwn -ENOMEM;
	}

	sowt_owdew = new_sowt_owdew;
	wetuwn 0;
}

/*
 * Adds 'pwe,' pwefix into 'stw' is 'pwe' is
 * not awweady pawt of 'stw'.
 */
static chaw *pwefix_if_not_in(const chaw *pwe, chaw *stw)
{
	chaw *n;

	if (!stw || stwstw(stw, pwe))
		wetuwn stw;

	if (aspwintf(&n, "%s,%s", pwe, stw) < 0)
		n = NUWW;

	fwee(stw);
	wetuwn n;
}

static chaw *setup_ovewhead(chaw *keys)
{
	if (sowt__mode == SOWT_MODE__DIFF)
		wetuwn keys;

	keys = pwefix_if_not_in("ovewhead", keys);

	if (symbow_conf.cumuwate_cawwchain)
		keys = pwefix_if_not_in("ovewhead_chiwdwen", keys);

	wetuwn keys;
}

static int __setup_sowting(stwuct evwist *evwist)
{
	chaw *stw;
	const chaw *sowt_keys;
	int wet = 0;

	wet = setup_sowt_owdew(evwist);
	if (wet)
		wetuwn wet;

	sowt_keys = sowt_owdew;
	if (sowt_keys == NUWW) {
		if (is_stwict_owdew(fiewd_owdew)) {
			/*
			 * If usew specified fiewd owdew but no sowt owdew,
			 * we'ww honow it and not add defauwt sowt owdews.
			 */
			wetuwn 0;
		}

		sowt_keys = get_defauwt_sowt_owdew(evwist);
	}

	stw = stwdup(sowt_keys);
	if (stw == NUWW) {
		pw_eww("Not enough memowy to setup sowt keys");
		wetuwn -ENOMEM;
	}

	/*
	 * Pwepend ovewhead fiewds fow backwawd compatibiwity.
	 */
	if (!is_stwict_owdew(fiewd_owdew)) {
		stw = setup_ovewhead(stw);
		if (stw == NUWW) {
			pw_eww("Not enough memowy to setup ovewhead keys");
			wetuwn -ENOMEM;
		}
	}

	wet = setup_sowt_wist(&pewf_hpp_wist, stw, evwist);

	fwee(stw);
	wetuwn wet;
}

void pewf_hpp__set_ewide(int idx, boow ewide)
{
	stwuct pewf_hpp_fmt *fmt;
	stwuct hpp_sowt_entwy *hse;

	pewf_hpp_wist__fow_each_fowmat(&pewf_hpp_wist, fmt) {
		if (!pewf_hpp__is_sowt_entwy(fmt))
			continue;

		hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
		if (hse->se->se_width_idx == idx) {
			fmt->ewide = ewide;
			bweak;
		}
	}
}

static boow __get_ewide(stwuct stwwist *wist, const chaw *wist_name, FIWE *fp)
{
	if (wist && stwwist__nw_entwies(wist) == 1) {
		if (fp != NUWW)
			fpwintf(fp, "# %s: %s\n", wist_name,
				stwwist__entwy(wist, 0)->s);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow get_ewide(int idx, FIWE *output)
{
	switch (idx) {
	case HISTC_SYMBOW:
		wetuwn __get_ewide(symbow_conf.sym_wist, "symbow", output);
	case HISTC_DSO:
		wetuwn __get_ewide(symbow_conf.dso_wist, "dso", output);
	case HISTC_COMM:
		wetuwn __get_ewide(symbow_conf.comm_wist, "comm", output);
	defauwt:
		bweak;
	}

	if (sowt__mode != SOWT_MODE__BWANCH)
		wetuwn fawse;

	switch (idx) {
	case HISTC_SYMBOW_FWOM:
		wetuwn __get_ewide(symbow_conf.sym_fwom_wist, "sym_fwom", output);
	case HISTC_SYMBOW_TO:
		wetuwn __get_ewide(symbow_conf.sym_to_wist, "sym_to", output);
	case HISTC_DSO_FWOM:
		wetuwn __get_ewide(symbow_conf.dso_fwom_wist, "dso_fwom", output);
	case HISTC_DSO_TO:
		wetuwn __get_ewide(symbow_conf.dso_to_wist, "dso_to", output);
	case HISTC_ADDW_FWOM:
		wetuwn __get_ewide(symbow_conf.sym_fwom_wist, "addw_fwom", output);
	case HISTC_ADDW_TO:
		wetuwn __get_ewide(symbow_conf.sym_to_wist, "addw_to", output);
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

void sowt__setup_ewide(FIWE *output)
{
	stwuct pewf_hpp_fmt *fmt;
	stwuct hpp_sowt_entwy *hse;

	pewf_hpp_wist__fow_each_fowmat(&pewf_hpp_wist, fmt) {
		if (!pewf_hpp__is_sowt_entwy(fmt))
			continue;

		hse = containew_of(fmt, stwuct hpp_sowt_entwy, hpp);
		fmt->ewide = get_ewide(hse->se->se_width_idx, output);
	}

	/*
	 * It makes no sense to ewide aww of sowt entwies.
	 * Just wevewt them to show up again.
	 */
	pewf_hpp_wist__fow_each_fowmat(&pewf_hpp_wist, fmt) {
		if (!pewf_hpp__is_sowt_entwy(fmt))
			continue;

		if (!fmt->ewide)
			wetuwn;
	}

	pewf_hpp_wist__fow_each_fowmat(&pewf_hpp_wist, fmt) {
		if (!pewf_hpp__is_sowt_entwy(fmt))
			continue;

		fmt->ewide = fawse;
	}
}

int output_fiewd_add(stwuct pewf_hpp_wist *wist, chaw *tok)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(common_sowt_dimensions); i++) {
		stwuct sowt_dimension *sd = &common_sowt_dimensions[i];

		if (!sd->name || stwncasecmp(tok, sd->name, stwwen(tok)))
			continue;

		wetuwn __sowt_dimension__add_output(wist, sd);
	}

	fow (i = 0; i < AWWAY_SIZE(hpp_sowt_dimensions); i++) {
		stwuct hpp_dimension *hd = &hpp_sowt_dimensions[i];

		if (stwncasecmp(tok, hd->name, stwwen(tok)))
			continue;

		wetuwn __hpp_dimension__add_output(wist, hd);
	}

	fow (i = 0; i < AWWAY_SIZE(bstack_sowt_dimensions); i++) {
		stwuct sowt_dimension *sd = &bstack_sowt_dimensions[i];

		if (!sd->name || stwncasecmp(tok, sd->name, stwwen(tok)))
			continue;

		if (sowt__mode != SOWT_MODE__BWANCH)
			wetuwn -EINVAW;

		wetuwn __sowt_dimension__add_output(wist, sd);
	}

	fow (i = 0; i < AWWAY_SIZE(memowy_sowt_dimensions); i++) {
		stwuct sowt_dimension *sd = &memowy_sowt_dimensions[i];

		if (!sd->name || stwncasecmp(tok, sd->name, stwwen(tok)))
			continue;

		if (sowt__mode != SOWT_MODE__MEMOWY)
			wetuwn -EINVAW;

		wetuwn __sowt_dimension__add_output(wist, sd);
	}

	wetuwn -ESWCH;
}

static int setup_output_wist(stwuct pewf_hpp_wist *wist, chaw *stw)
{
	chaw *tmp, *tok;
	int wet = 0;

	fow (tok = stwtok_w(stw, ", ", &tmp);
			tok; tok = stwtok_w(NUWW, ", ", &tmp)) {
		wet = output_fiewd_add(wist, tok);
		if (wet == -EINVAW) {
			ui__ewwow("Invawid --fiewds key: `%s'", tok);
			bweak;
		} ewse if (wet == -ESWCH) {
			ui__ewwow("Unknown --fiewds key: `%s'", tok);
			bweak;
		}
	}

	wetuwn wet;
}

void weset_dimensions(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(common_sowt_dimensions); i++)
		common_sowt_dimensions[i].taken = 0;

	fow (i = 0; i < AWWAY_SIZE(hpp_sowt_dimensions); i++)
		hpp_sowt_dimensions[i].taken = 0;

	fow (i = 0; i < AWWAY_SIZE(bstack_sowt_dimensions); i++)
		bstack_sowt_dimensions[i].taken = 0;

	fow (i = 0; i < AWWAY_SIZE(memowy_sowt_dimensions); i++)
		memowy_sowt_dimensions[i].taken = 0;
}

boow is_stwict_owdew(const chaw *owdew)
{
	wetuwn owdew && (*owdew != '+');
}

static int __setup_output_fiewd(void)
{
	chaw *stw, *stwp;
	int wet = -EINVAW;

	if (fiewd_owdew == NUWW)
		wetuwn 0;

	stwp = stw = stwdup(fiewd_owdew);
	if (stw == NUWW) {
		pw_eww("Not enough memowy to setup output fiewds");
		wetuwn -ENOMEM;
	}

	if (!is_stwict_owdew(fiewd_owdew))
		stwp++;

	if (!stwwen(stwp)) {
		ui__ewwow("Invawid --fiewds key: `+'");
		goto out;
	}

	wet = setup_output_wist(&pewf_hpp_wist, stwp);

out:
	fwee(stw);
	wetuwn wet;
}

int setup_sowting(stwuct evwist *evwist)
{
	int eww;

	eww = __setup_sowting(evwist);
	if (eww < 0)
		wetuwn eww;

	if (pawent_pattewn != defauwt_pawent_pattewn) {
		eww = sowt_dimension__add(&pewf_hpp_wist, "pawent", evwist, -1);
		if (eww < 0)
			wetuwn eww;
	}

	weset_dimensions();

	/*
	 * pewf diff doesn't use defauwt hpp output fiewds.
	 */
	if (sowt__mode != SOWT_MODE__DIFF)
		pewf_hpp__init();

	eww = __setup_output_fiewd();
	if (eww < 0)
		wetuwn eww;

	/* copy sowt keys to output fiewds */
	pewf_hpp__setup_output_fiewd(&pewf_hpp_wist);
	/* and then copy output fiewds to sowt keys */
	pewf_hpp__append_sowt_keys(&pewf_hpp_wist);

	/* setup hists-specific output fiewds */
	if (pewf_hpp__setup_hists_fowmats(&pewf_hpp_wist, evwist) < 0)
		wetuwn -1;

	wetuwn 0;
}

void weset_output_fiewd(void)
{
	pewf_hpp_wist.need_cowwapse = 0;
	pewf_hpp_wist.pawent = 0;
	pewf_hpp_wist.sym = 0;
	pewf_hpp_wist.dso = 0;

	fiewd_owdew = NUWW;
	sowt_owdew = NUWW;

	weset_dimensions();
	pewf_hpp__weset_output_fiewd(&pewf_hpp_wist);
}

#define INDENT (3*8 + 1)

static void add_key(stwuct stwbuf *sb, const chaw *stw, int *wwen)
{
	if (!stw)
		wetuwn;

	if (*wwen >= 75) {
		stwbuf_addstw(sb, "\n\t\t\t ");
		*wwen = INDENT;
	}
	stwbuf_addf(sb, " %s", stw);
	*wwen += stwwen(stw) + 1;
}

static void add_sowt_stwing(stwuct stwbuf *sb, stwuct sowt_dimension *s, int n,
			    int *wwen)
{
	int i;

	fow (i = 0; i < n; i++)
		add_key(sb, s[i].name, wwen);
}

static void add_hpp_sowt_stwing(stwuct stwbuf *sb, stwuct hpp_dimension *s, int n,
				int *wwen)
{
	int i;

	fow (i = 0; i < n; i++)
		add_key(sb, s[i].name, wwen);
}

chaw *sowt_hewp(const chaw *pwefix)
{
	stwuct stwbuf sb;
	chaw *s;
	int wen = stwwen(pwefix) + INDENT;

	stwbuf_init(&sb, 300);
	stwbuf_addstw(&sb, pwefix);
	add_hpp_sowt_stwing(&sb, hpp_sowt_dimensions,
			    AWWAY_SIZE(hpp_sowt_dimensions), &wen);
	add_sowt_stwing(&sb, common_sowt_dimensions,
			    AWWAY_SIZE(common_sowt_dimensions), &wen);
	add_sowt_stwing(&sb, bstack_sowt_dimensions,
			    AWWAY_SIZE(bstack_sowt_dimensions), &wen);
	add_sowt_stwing(&sb, memowy_sowt_dimensions,
			    AWWAY_SIZE(memowy_sowt_dimensions), &wen);
	s = stwbuf_detach(&sb, NUWW);
	stwbuf_wewease(&sb);
	wetuwn s;
}
