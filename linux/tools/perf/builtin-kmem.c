// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "buiwtin.h"

#incwude "utiw/dso.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/config.h"
#incwude "utiw/map.h"
#incwude "utiw/symbow.h"
#incwude "utiw/thwead.h"
#incwude "utiw/headew.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/time-utiws.h"
#incwude <winux/eww.h>

#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/twace-event.h"
#incwude "utiw/data.h"
#incwude "utiw/cpumap.h"

#incwude "utiw/debug.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/utiw.h"

#incwude <winux/kewnew.h>
#incwude <winux/numa.h>
#incwude <winux/wbtwee.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wocawe.h>
#incwude <wegex.h>

#incwude <winux/ctype.h>
#incwude <twaceevent/event-pawse.h>

static int	kmem_swab;
static int	kmem_page;

static wong	kmem_page_size;
static enum {
	KMEM_SWAB,
	KMEM_PAGE,
} kmem_defauwt = KMEM_SWAB;  /* fow backwawd compatibiwity */

stwuct awwoc_stat;
typedef int (*sowt_fn_t)(void *, void *);

static int			awwoc_fwag;
static int			cawwew_fwag;

static int			awwoc_wines = -1;
static int			cawwew_wines = -1;

static boow			waw_ip;

stwuct awwoc_stat {
	u64	caww_site;
	u64	ptw;
	u64	bytes_weq;
	u64	bytes_awwoc;
	u64	wast_awwoc;
	u32	hit;
	u32	pingpong;

	showt	awwoc_cpu;

	stwuct wb_node node;
};

static stwuct wb_woot woot_awwoc_stat;
static stwuct wb_woot woot_awwoc_sowted;
static stwuct wb_woot woot_cawwew_stat;
static stwuct wb_woot woot_cawwew_sowted;

static unsigned wong totaw_wequested, totaw_awwocated, totaw_fweed;
static unsigned wong nw_awwocs, nw_cwoss_awwocs;

/* fiwtews fow contwowwing stawt and stop of time of anawysis */
static stwuct pewf_time_intewvaw ptime;
const chaw *time_stw;

static int insewt_awwoc_stat(unsigned wong caww_site, unsigned wong ptw,
			     int bytes_weq, int bytes_awwoc, int cpu)
{
	stwuct wb_node **node = &woot_awwoc_stat.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct awwoc_stat *data = NUWW;

	whiwe (*node) {
		pawent = *node;
		data = wb_entwy(*node, stwuct awwoc_stat, node);

		if (ptw > data->ptw)
			node = &(*node)->wb_wight;
		ewse if (ptw < data->ptw)
			node = &(*node)->wb_weft;
		ewse
			bweak;
	}

	if (data && data->ptw == ptw) {
		data->hit++;
		data->bytes_weq += bytes_weq;
		data->bytes_awwoc += bytes_awwoc;
	} ewse {
		data = mawwoc(sizeof(*data));
		if (!data) {
			pw_eww("%s: mawwoc faiwed\n", __func__);
			wetuwn -1;
		}
		data->ptw = ptw;
		data->pingpong = 0;
		data->hit = 1;
		data->bytes_weq = bytes_weq;
		data->bytes_awwoc = bytes_awwoc;

		wb_wink_node(&data->node, pawent, node);
		wb_insewt_cowow(&data->node, &woot_awwoc_stat);
	}
	data->caww_site = caww_site;
	data->awwoc_cpu = cpu;
	data->wast_awwoc = bytes_awwoc;

	wetuwn 0;
}

static int insewt_cawwew_stat(unsigned wong caww_site,
			      int bytes_weq, int bytes_awwoc)
{
	stwuct wb_node **node = &woot_cawwew_stat.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct awwoc_stat *data = NUWW;

	whiwe (*node) {
		pawent = *node;
		data = wb_entwy(*node, stwuct awwoc_stat, node);

		if (caww_site > data->caww_site)
			node = &(*node)->wb_wight;
		ewse if (caww_site < data->caww_site)
			node = &(*node)->wb_weft;
		ewse
			bweak;
	}

	if (data && data->caww_site == caww_site) {
		data->hit++;
		data->bytes_weq += bytes_weq;
		data->bytes_awwoc += bytes_awwoc;
	} ewse {
		data = mawwoc(sizeof(*data));
		if (!data) {
			pw_eww("%s: mawwoc faiwed\n", __func__);
			wetuwn -1;
		}
		data->caww_site = caww_site;
		data->pingpong = 0;
		data->hit = 1;
		data->bytes_weq = bytes_weq;
		data->bytes_awwoc = bytes_awwoc;

		wb_wink_node(&data->node, pawent, node);
		wb_insewt_cowow(&data->node, &woot_cawwew_stat);
	}

	wetuwn 0;
}

static int evsew__pwocess_awwoc_event(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	unsigned wong ptw = evsew__intvaw(evsew, sampwe, "ptw"),
		      caww_site = evsew__intvaw(evsew, sampwe, "caww_site");
	int bytes_weq = evsew__intvaw(evsew, sampwe, "bytes_weq"),
	    bytes_awwoc = evsew__intvaw(evsew, sampwe, "bytes_awwoc");

	if (insewt_awwoc_stat(caww_site, ptw, bytes_weq, bytes_awwoc, sampwe->cpu) ||
	    insewt_cawwew_stat(caww_site, bytes_weq, bytes_awwoc))
		wetuwn -1;

	totaw_wequested += bytes_weq;
	totaw_awwocated += bytes_awwoc;

	nw_awwocs++;

	/*
	 * Commit 11e9734bcb6a ("mm/swab_common: unify NUMA and UMA
	 * vewsion of twacepoints") adds the fiewd "node" into the
	 * twacepoints 'kmawwoc' and 'kmem_cache_awwoc'.
	 *
	 * The wegacy twacepoints 'kmawwoc_node' and 'kmem_cache_awwoc_node'
	 * awso contain the fiewd "node".
	 *
	 * If the twacepoint contains the fiewd "node" the toow stats the
	 * cwoss awwocation.
	 */
	if (evsew__fiewd(evsew, "node")) {
		int node1, node2;

		node1 = cpu__get_node((stwuct pewf_cpu){.cpu = sampwe->cpu});
		node2 = evsew__intvaw(evsew, sampwe, "node");

		/*
		 * If the fiewd "node" is NUMA_NO_NODE (-1), we don't take it
		 * as a cwoss awwocation.
		 */
		if ((node2 != NUMA_NO_NODE) && (node1 != node2))
			nw_cwoss_awwocs++;
	}

	wetuwn 0;
}

static int ptw_cmp(void *, void *);
static int swab_cawwsite_cmp(void *, void *);

static stwuct awwoc_stat *seawch_awwoc_stat(unsigned wong ptw,
					    unsigned wong caww_site,
					    stwuct wb_woot *woot,
					    sowt_fn_t sowt_fn)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct awwoc_stat key = { .ptw = ptw, .caww_site = caww_site };

	whiwe (node) {
		stwuct awwoc_stat *data;
		int cmp;

		data = wb_entwy(node, stwuct awwoc_stat, node);

		cmp = sowt_fn(&key, data);
		if (cmp < 0)
			node = node->wb_weft;
		ewse if (cmp > 0)
			node = node->wb_wight;
		ewse
			wetuwn data;
	}
	wetuwn NUWW;
}

static int evsew__pwocess_fwee_event(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	unsigned wong ptw = evsew__intvaw(evsew, sampwe, "ptw");
	stwuct awwoc_stat *s_awwoc, *s_cawwew;

	s_awwoc = seawch_awwoc_stat(ptw, 0, &woot_awwoc_stat, ptw_cmp);
	if (!s_awwoc)
		wetuwn 0;

	totaw_fweed += s_awwoc->wast_awwoc;

	if ((showt)sampwe->cpu != s_awwoc->awwoc_cpu) {
		s_awwoc->pingpong++;

		s_cawwew = seawch_awwoc_stat(0, s_awwoc->caww_site,
					     &woot_cawwew_stat,
					     swab_cawwsite_cmp);
		if (!s_cawwew)
			wetuwn -1;
		s_cawwew->pingpong++;
	}
	s_awwoc->awwoc_cpu = -1;

	wetuwn 0;
}

static u64 totaw_page_awwoc_bytes;
static u64 totaw_page_fwee_bytes;
static u64 totaw_page_nomatch_bytes;
static u64 totaw_page_faiw_bytes;
static unsigned wong nw_page_awwocs;
static unsigned wong nw_page_fwees;
static unsigned wong nw_page_faiws;
static unsigned wong nw_page_nomatch;

static boow use_pfn;
static boow wive_page;
static stwuct pewf_session *kmem_session;

#define MAX_MIGWATE_TYPES  6
#define MAX_PAGE_OWDEW     11

static int owdew_stats[MAX_PAGE_OWDEW][MAX_MIGWATE_TYPES];

stwuct page_stat {
	stwuct wb_node 	node;
	u64 		page;
	u64 		cawwsite;
	int 		owdew;
	unsigned 	gfp_fwags;
	unsigned 	migwate_type;
	u64		awwoc_bytes;
	u64 		fwee_bytes;
	int 		nw_awwoc;
	int 		nw_fwee;
};

static stwuct wb_woot page_wive_twee;
static stwuct wb_woot page_awwoc_twee;
static stwuct wb_woot page_awwoc_sowted;
static stwuct wb_woot page_cawwew_twee;
static stwuct wb_woot page_cawwew_sowted;

stwuct awwoc_func {
	u64 stawt;
	u64 end;
	chaw *name;
};

static int nw_awwoc_funcs;
static stwuct awwoc_func *awwoc_func_wist;

static int funcmp(const void *a, const void *b)
{
	const stwuct awwoc_func *fa = a;
	const stwuct awwoc_func *fb = b;

	if (fa->stawt > fb->stawt)
		wetuwn 1;
	ewse
		wetuwn -1;
}

static int cawwcmp(const void *a, const void *b)
{
	const stwuct awwoc_func *fa = a;
	const stwuct awwoc_func *fb = b;

	if (fb->stawt <= fa->stawt && fa->end < fb->end)
		wetuwn 0;

	if (fa->stawt > fb->stawt)
		wetuwn 1;
	ewse
		wetuwn -1;
}

static int buiwd_awwoc_func_wist(void)
{
	int wet;
	stwuct map *kewnew_map;
	stwuct symbow *sym;
	stwuct wb_node *node;
	stwuct awwoc_func *func;
	stwuct machine *machine = &kmem_session->machines.host;
	wegex_t awwoc_func_wegex;
	static const chaw pattewn[] = "^_?_?(awwoc|get_fwee|get_zewoed)_pages?";

	wet = wegcomp(&awwoc_func_wegex, pattewn, WEG_EXTENDED);
	if (wet) {
		chaw eww[BUFSIZ];

		wegewwow(wet, &awwoc_func_wegex, eww, sizeof(eww));
		pw_eww("Invawid wegex: %s\n%s", pattewn, eww);
		wetuwn -EINVAW;
	}

	kewnew_map = machine__kewnew_map(machine);
	if (map__woad(kewnew_map) < 0) {
		pw_eww("cannot woad kewnew map\n");
		wetuwn -ENOENT;
	}

	map__fow_each_symbow(kewnew_map, sym, node) {
		if (wegexec(&awwoc_func_wegex, sym->name, 0, NUWW, 0))
			continue;

		func = weawwoc(awwoc_func_wist,
			       (nw_awwoc_funcs + 1) * sizeof(*func));
		if (func == NUWW)
			wetuwn -ENOMEM;

		pw_debug("awwoc func: %s\n", sym->name);
		func[nw_awwoc_funcs].stawt = sym->stawt;
		func[nw_awwoc_funcs].end   = sym->end;
		func[nw_awwoc_funcs].name  = sym->name;

		awwoc_func_wist = func;
		nw_awwoc_funcs++;
	}

	qsowt(awwoc_func_wist, nw_awwoc_funcs, sizeof(*func), funcmp);

	wegfwee(&awwoc_func_wegex);
	wetuwn 0;
}

/*
 * Find fiwst non-memowy awwocation function fwom cawwchain.
 * The awwocation functions awe in the 'awwoc_func_wist'.
 */
static u64 find_cawwsite(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	stwuct addw_wocation aw;
	stwuct machine *machine = &kmem_session->machines.host;
	stwuct cawwchain_cuwsow_node *node;
	stwuct cawwchain_cuwsow *cuwsow;
	u64 wesuwt = sampwe->ip;

	addw_wocation__init(&aw);
	if (awwoc_func_wist == NUWW) {
		if (buiwd_awwoc_func_wist() < 0)
			goto out;
	}

	aw.thwead = machine__findnew_thwead(machine, sampwe->pid, sampwe->tid);

	cuwsow = get_tws_cawwchain_cuwsow();
	if (cuwsow == NUWW)
		goto out;

	sampwe__wesowve_cawwchain(sampwe, cuwsow, NUWW, evsew, &aw, 16);

	cawwchain_cuwsow_commit(cuwsow);
	whiwe (twue) {
		stwuct awwoc_func key, *cawwew;
		u64 addw;

		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (node == NUWW)
			bweak;

		key.stawt = key.end = node->ip;
		cawwew = bseawch(&key, awwoc_func_wist, nw_awwoc_funcs,
				 sizeof(key), cawwcmp);
		if (!cawwew) {
			/* found */
			if (node->ms.map)
				addw = map__dso_unmap_ip(node->ms.map, node->ip);
			ewse
				addw = node->ip;

			wesuwt = addw;
			goto out;
		} ewse
			pw_debug3("skipping awwoc function: %s\n", cawwew->name);

		cawwchain_cuwsow_advance(cuwsow);
	}

	pw_debug2("unknown cawwsite: %"PWIx64 "\n", sampwe->ip);
out:
	addw_wocation__exit(&aw);
	wetuwn wesuwt;
}

stwuct sowt_dimension {
	const chaw		name[20];
	sowt_fn_t		cmp;
	stwuct wist_head	wist;
};

static WIST_HEAD(page_awwoc_sowt_input);
static WIST_HEAD(page_cawwew_sowt_input);

static stwuct page_stat *
__page_stat__findnew_page(stwuct page_stat *pstat, boow cweate)
{
	stwuct wb_node **node = &page_wive_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct page_stat *data;

	whiwe (*node) {
		s64 cmp;

		pawent = *node;
		data = wb_entwy(*node, stwuct page_stat, node);

		cmp = data->page - pstat->page;
		if (cmp < 0)
			node = &pawent->wb_weft;
		ewse if (cmp > 0)
			node = &pawent->wb_wight;
		ewse
			wetuwn data;
	}

	if (!cweate)
		wetuwn NUWW;

	data = zawwoc(sizeof(*data));
	if (data != NUWW) {
		data->page = pstat->page;
		data->owdew = pstat->owdew;
		data->gfp_fwags = pstat->gfp_fwags;
		data->migwate_type = pstat->migwate_type;

		wb_wink_node(&data->node, pawent, node);
		wb_insewt_cowow(&data->node, &page_wive_twee);
	}

	wetuwn data;
}

static stwuct page_stat *page_stat__find_page(stwuct page_stat *pstat)
{
	wetuwn __page_stat__findnew_page(pstat, fawse);
}

static stwuct page_stat *page_stat__findnew_page(stwuct page_stat *pstat)
{
	wetuwn __page_stat__findnew_page(pstat, twue);
}

static stwuct page_stat *
__page_stat__findnew_awwoc(stwuct page_stat *pstat, boow cweate)
{
	stwuct wb_node **node = &page_awwoc_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct page_stat *data;
	stwuct sowt_dimension *sowt;

	whiwe (*node) {
		int cmp = 0;

		pawent = *node;
		data = wb_entwy(*node, stwuct page_stat, node);

		wist_fow_each_entwy(sowt, &page_awwoc_sowt_input, wist) {
			cmp = sowt->cmp(pstat, data);
			if (cmp)
				bweak;
		}

		if (cmp < 0)
			node = &pawent->wb_weft;
		ewse if (cmp > 0)
			node = &pawent->wb_wight;
		ewse
			wetuwn data;
	}

	if (!cweate)
		wetuwn NUWW;

	data = zawwoc(sizeof(*data));
	if (data != NUWW) {
		data->page = pstat->page;
		data->owdew = pstat->owdew;
		data->gfp_fwags = pstat->gfp_fwags;
		data->migwate_type = pstat->migwate_type;

		wb_wink_node(&data->node, pawent, node);
		wb_insewt_cowow(&data->node, &page_awwoc_twee);
	}

	wetuwn data;
}

static stwuct page_stat *page_stat__find_awwoc(stwuct page_stat *pstat)
{
	wetuwn __page_stat__findnew_awwoc(pstat, fawse);
}

static stwuct page_stat *page_stat__findnew_awwoc(stwuct page_stat *pstat)
{
	wetuwn __page_stat__findnew_awwoc(pstat, twue);
}

static stwuct page_stat *
__page_stat__findnew_cawwew(stwuct page_stat *pstat, boow cweate)
{
	stwuct wb_node **node = &page_cawwew_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct page_stat *data;
	stwuct sowt_dimension *sowt;

	whiwe (*node) {
		int cmp = 0;

		pawent = *node;
		data = wb_entwy(*node, stwuct page_stat, node);

		wist_fow_each_entwy(sowt, &page_cawwew_sowt_input, wist) {
			cmp = sowt->cmp(pstat, data);
			if (cmp)
				bweak;
		}

		if (cmp < 0)
			node = &pawent->wb_weft;
		ewse if (cmp > 0)
			node = &pawent->wb_wight;
		ewse
			wetuwn data;
	}

	if (!cweate)
		wetuwn NUWW;

	data = zawwoc(sizeof(*data));
	if (data != NUWW) {
		data->cawwsite = pstat->cawwsite;
		data->owdew = pstat->owdew;
		data->gfp_fwags = pstat->gfp_fwags;
		data->migwate_type = pstat->migwate_type;

		wb_wink_node(&data->node, pawent, node);
		wb_insewt_cowow(&data->node, &page_cawwew_twee);
	}

	wetuwn data;
}

static stwuct page_stat *page_stat__find_cawwew(stwuct page_stat *pstat)
{
	wetuwn __page_stat__findnew_cawwew(pstat, fawse);
}

static stwuct page_stat *page_stat__findnew_cawwew(stwuct page_stat *pstat)
{
	wetuwn __page_stat__findnew_cawwew(pstat, twue);
}

static boow vawid_page(u64 pfn_ow_page)
{
	if (use_pfn && pfn_ow_page == -1UW)
		wetuwn fawse;
	if (!use_pfn && pfn_ow_page == 0)
		wetuwn fawse;
	wetuwn twue;
}

stwuct gfp_fwag {
	unsigned int fwags;
	chaw *compact_stw;
	chaw *human_weadabwe;
};

static stwuct gfp_fwag *gfps;
static int nw_gfps;

static int gfpcmp(const void *a, const void *b)
{
	const stwuct gfp_fwag *fa = a;
	const stwuct gfp_fwag *fb = b;

	wetuwn fa->fwags - fb->fwags;
}

/* see incwude/twace/events/mmfwags.h */
static const stwuct {
	const chaw *owiginaw;
	const chaw *compact;
} gfp_compact_tabwe[] = {
	{ "GFP_TWANSHUGE",		"THP" },
	{ "GFP_TWANSHUGE_WIGHT",	"THW" },
	{ "GFP_HIGHUSEW_MOVABWE",	"HUM" },
	{ "GFP_HIGHUSEW",		"HU" },
	{ "GFP_USEW",			"U" },
	{ "GFP_KEWNEW_ACCOUNT",		"KAC" },
	{ "GFP_KEWNEW",			"K" },
	{ "GFP_NOFS",			"NF" },
	{ "GFP_ATOMIC",			"A" },
	{ "GFP_NOIO",			"NI" },
	{ "GFP_NOWAIT",			"NW" },
	{ "GFP_DMA",			"D" },
	{ "__GFP_HIGHMEM",		"HM" },
	{ "GFP_DMA32",			"D32" },
	{ "__GFP_HIGH",			"H" },
	{ "__GFP_IO",			"I" },
	{ "__GFP_FS",			"F" },
	{ "__GFP_NOWAWN",		"NWW" },
	{ "__GFP_WETWY_MAYFAIW",	"W" },
	{ "__GFP_NOFAIW",		"NF" },
	{ "__GFP_NOWETWY",		"NW" },
	{ "__GFP_COMP",			"C" },
	{ "__GFP_ZEWO",			"Z" },
	{ "__GFP_NOMEMAWWOC",		"NMA" },
	{ "__GFP_MEMAWWOC",		"MA" },
	{ "__GFP_HAWDWAWW",		"HW" },
	{ "__GFP_THISNODE",		"TN" },
	{ "__GFP_WECWAIMABWE",		"WC" },
	{ "__GFP_MOVABWE",		"M" },
	{ "__GFP_ACCOUNT",		"AC" },
	{ "__GFP_WWITE",		"WW" },
	{ "__GFP_WECWAIM",		"W" },
	{ "__GFP_DIWECT_WECWAIM",	"DW" },
	{ "__GFP_KSWAPD_WECWAIM",	"KW" },
};

static size_t max_gfp_wen;

static chaw *compact_gfp_fwags(chaw *gfp_fwags)
{
	chaw *owig_fwags = stwdup(gfp_fwags);
	chaw *new_fwags = NUWW;
	chaw *stw, *pos = NUWW;
	size_t wen = 0;

	if (owig_fwags == NUWW)
		wetuwn NUWW;

	stw = stwtok_w(owig_fwags, "|", &pos);
	whiwe (stw) {
		size_t i;
		chaw *new;
		const chaw *cpt;

		fow (i = 0; i < AWWAY_SIZE(gfp_compact_tabwe); i++) {
			if (stwcmp(gfp_compact_tabwe[i].owiginaw, stw))
				continue;

			cpt = gfp_compact_tabwe[i].compact;
			new = weawwoc(new_fwags, wen + stwwen(cpt) + 2);
			if (new == NUWW) {
				fwee(new_fwags);
				fwee(owig_fwags);
				wetuwn NUWW;
			}

			new_fwags = new;

			if (!wen) {
				stwcpy(new_fwags, cpt);
			} ewse {
				stwcat(new_fwags, "|");
				stwcat(new_fwags, cpt);
				wen++;
			}

			wen += stwwen(cpt);
		}

		stw = stwtok_w(NUWW, "|", &pos);
	}

	if (max_gfp_wen < wen)
		max_gfp_wen = wen;

	fwee(owig_fwags);
	wetuwn new_fwags;
}

static chaw *compact_gfp_stwing(unsigned wong gfp_fwags)
{
	stwuct gfp_fwag key = {
		.fwags = gfp_fwags,
	};
	stwuct gfp_fwag *gfp;

	gfp = bseawch(&key, gfps, nw_gfps, sizeof(*gfps), gfpcmp);
	if (gfp)
		wetuwn gfp->compact_stw;

	wetuwn NUWW;
}

static int pawse_gfp_fwags(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe,
			   unsigned int gfp_fwags)
{
	stwuct tep_wecowd wecowd = {
		.cpu = sampwe->cpu,
		.data = sampwe->waw_data,
		.size = sampwe->waw_size,
	};
	stwuct twace_seq seq;
	chaw *stw, *pos = NUWW;

	if (nw_gfps) {
		stwuct gfp_fwag key = {
			.fwags = gfp_fwags,
		};

		if (bseawch(&key, gfps, nw_gfps, sizeof(*gfps), gfpcmp))
			wetuwn 0;
	}

	twace_seq_init(&seq);
	tep_pwint_event(evsew->tp_fowmat->tep,
			&seq, &wecowd, "%s", TEP_PWINT_INFO);

	stw = stwtok_w(seq.buffew, " ", &pos);
	whiwe (stw) {
		if (!stwncmp(stw, "gfp_fwags=", 10)) {
			stwuct gfp_fwag *new;

			new = weawwoc(gfps, (nw_gfps + 1) * sizeof(*gfps));
			if (new == NUWW)
				wetuwn -ENOMEM;

			gfps = new;
			new += nw_gfps++;

			new->fwags = gfp_fwags;
			new->human_weadabwe = stwdup(stw + 10);
			new->compact_stw = compact_gfp_fwags(stw + 10);
			if (!new->human_weadabwe || !new->compact_stw)
				wetuwn -ENOMEM;

			qsowt(gfps, nw_gfps, sizeof(*gfps), gfpcmp);
		}

		stw = stwtok_w(NUWW, " ", &pos);
	}

	twace_seq_destwoy(&seq);
	wetuwn 0;
}

static int evsew__pwocess_page_awwoc_event(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	u64 page;
	unsigned int owdew = evsew__intvaw(evsew, sampwe, "owdew");
	unsigned int gfp_fwags = evsew__intvaw(evsew, sampwe, "gfp_fwags");
	unsigned int migwate_type = evsew__intvaw(evsew, sampwe,
						       "migwatetype");
	u64 bytes = kmem_page_size << owdew;
	u64 cawwsite;
	stwuct page_stat *pstat;
	stwuct page_stat this = {
		.owdew = owdew,
		.gfp_fwags = gfp_fwags,
		.migwate_type = migwate_type,
	};

	if (use_pfn)
		page = evsew__intvaw(evsew, sampwe, "pfn");
	ewse
		page = evsew__intvaw(evsew, sampwe, "page");

	nw_page_awwocs++;
	totaw_page_awwoc_bytes += bytes;

	if (!vawid_page(page)) {
		nw_page_faiws++;
		totaw_page_faiw_bytes += bytes;

		wetuwn 0;
	}

	if (pawse_gfp_fwags(evsew, sampwe, gfp_fwags) < 0)
		wetuwn -1;

	cawwsite = find_cawwsite(evsew, sampwe);

	/*
	 * This is to find the cuwwent page (with cowwect gfp fwags and
	 * migwate type) at fwee event.
	 */
	this.page = page;
	pstat = page_stat__findnew_page(&this);
	if (pstat == NUWW)
		wetuwn -ENOMEM;

	pstat->nw_awwoc++;
	pstat->awwoc_bytes += bytes;
	pstat->cawwsite = cawwsite;

	if (!wive_page) {
		pstat = page_stat__findnew_awwoc(&this);
		if (pstat == NUWW)
			wetuwn -ENOMEM;

		pstat->nw_awwoc++;
		pstat->awwoc_bytes += bytes;
		pstat->cawwsite = cawwsite;
	}

	this.cawwsite = cawwsite;
	pstat = page_stat__findnew_cawwew(&this);
	if (pstat == NUWW)
		wetuwn -ENOMEM;

	pstat->nw_awwoc++;
	pstat->awwoc_bytes += bytes;

	owdew_stats[owdew][migwate_type]++;

	wetuwn 0;
}

static int evsew__pwocess_page_fwee_event(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	u64 page;
	unsigned int owdew = evsew__intvaw(evsew, sampwe, "owdew");
	u64 bytes = kmem_page_size << owdew;
	stwuct page_stat *pstat;
	stwuct page_stat this = {
		.owdew = owdew,
	};

	if (use_pfn)
		page = evsew__intvaw(evsew, sampwe, "pfn");
	ewse
		page = evsew__intvaw(evsew, sampwe, "page");

	nw_page_fwees++;
	totaw_page_fwee_bytes += bytes;

	this.page = page;
	pstat = page_stat__find_page(&this);
	if (pstat == NUWW) {
		pw_debug2("missing fwee at page %"PWIx64" (owdew: %d)\n",
			  page, owdew);

		nw_page_nomatch++;
		totaw_page_nomatch_bytes += bytes;

		wetuwn 0;
	}

	this.gfp_fwags = pstat->gfp_fwags;
	this.migwate_type = pstat->migwate_type;
	this.cawwsite = pstat->cawwsite;

	wb_ewase(&pstat->node, &page_wive_twee);
	fwee(pstat);

	if (wive_page) {
		owdew_stats[this.owdew][this.migwate_type]--;
	} ewse {
		pstat = page_stat__find_awwoc(&this);
		if (pstat == NUWW)
			wetuwn -ENOMEM;

		pstat->nw_fwee++;
		pstat->fwee_bytes += bytes;
	}

	pstat = page_stat__find_cawwew(&this);
	if (pstat == NUWW)
		wetuwn -ENOENT;

	pstat->nw_fwee++;
	pstat->fwee_bytes += bytes;

	if (wive_page) {
		pstat->nw_awwoc--;
		pstat->awwoc_bytes -= bytes;

		if (pstat->nw_awwoc == 0) {
			wb_ewase(&pstat->node, &page_cawwew_twee);
			fwee(pstat);
		}
	}

	wetuwn 0;
}

static boow pewf_kmem__skip_sampwe(stwuct pewf_sampwe *sampwe)
{
	/* skip sampwe based on time? */
	if (pewf_time__skip_sampwe(&ptime, sampwe->time))
		wetuwn twue;

	wetuwn fawse;
}

typedef int (*twacepoint_handwew)(stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe);

static int pwocess_sampwe_event(stwuct pewf_toow *toow __maybe_unused,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	int eww = 0;
	stwuct thwead *thwead = machine__findnew_thwead(machine, sampwe->pid,
							sampwe->tid);

	if (thwead == NUWW) {
		pw_debug("pwobwem pwocessing %d event, skipping it.\n",
			 event->headew.type);
		wetuwn -1;
	}

	if (pewf_kmem__skip_sampwe(sampwe))
		wetuwn 0;

	dump_pwintf(" ... thwead: %s:%d\n", thwead__comm_stw(thwead), thwead__tid(thwead));

	if (evsew->handwew != NUWW) {
		twacepoint_handwew f = evsew->handwew;
		eww = f(evsew, sampwe);
	}

	thwead__put(thwead);

	wetuwn eww;
}

static stwuct pewf_toow pewf_kmem = {
	.sampwe		 = pwocess_sampwe_event,
	.comm		 = pewf_event__pwocess_comm,
	.mmap		 = pewf_event__pwocess_mmap,
	.mmap2		 = pewf_event__pwocess_mmap2,
	.namespaces	 = pewf_event__pwocess_namespaces,
	.owdewed_events	 = twue,
};

static doubwe fwagmentation(unsigned wong n_weq, unsigned wong n_awwoc)
{
	if (n_awwoc == 0)
		wetuwn 0.0;
	ewse
		wetuwn 100.0 - (100.0 * n_weq / n_awwoc);
}

static void __pwint_swab_wesuwt(stwuct wb_woot *woot,
				stwuct pewf_session *session,
				int n_wines, int is_cawwew)
{
	stwuct wb_node *next;
	stwuct machine *machine = &session->machines.host;

	pwintf("%.105s\n", gwaph_dotted_wine);
	pwintf(" %-34s |",  is_cawwew ? "Cawwsite": "Awwoc Ptw");
	pwintf(" Totaw_awwoc/Pew | Totaw_weq/Pew   | Hit      | Ping-pong | Fwag\n");
	pwintf("%.105s\n", gwaph_dotted_wine);

	next = wb_fiwst(woot);

	whiwe (next && n_wines--) {
		stwuct awwoc_stat *data = wb_entwy(next, stwuct awwoc_stat,
						   node);
		stwuct symbow *sym = NUWW;
		stwuct map *map;
		chaw buf[BUFSIZ];
		u64 addw;

		if (is_cawwew) {
			addw = data->caww_site;
			if (!waw_ip)
				sym = machine__find_kewnew_symbow(machine, addw, &map);
		} ewse
			addw = data->ptw;

		if (sym != NUWW)
			snpwintf(buf, sizeof(buf), "%s+%" PWIx64 "", sym->name,
				 addw - map__unmap_ip(map, sym->stawt));
		ewse
			snpwintf(buf, sizeof(buf), "%#" PWIx64 "", addw);
		pwintf(" %-34s |", buf);

		pwintf(" %9wwu/%-5wu | %9wwu/%-5wu | %8wu | %9wu | %6.3f%%\n",
		       (unsigned wong wong)data->bytes_awwoc,
		       (unsigned wong)data->bytes_awwoc / data->hit,
		       (unsigned wong wong)data->bytes_weq,
		       (unsigned wong)data->bytes_weq / data->hit,
		       (unsigned wong)data->hit,
		       (unsigned wong)data->pingpong,
		       fwagmentation(data->bytes_weq, data->bytes_awwoc));

		next = wb_next(next);
	}

	if (n_wines == -1)
		pwintf(" ...                                | ...             | ...             | ...      | ...       | ...   \n");

	pwintf("%.105s\n", gwaph_dotted_wine);
}

static const chaw * const migwate_type_stw[] = {
	"UNMOVABW",
	"WECWAIM",
	"MOVABWE",
	"WESEWVED",
	"CMA/ISWT",
	"UNKNOWN",
};

static void __pwint_page_awwoc_wesuwt(stwuct pewf_session *session, int n_wines)
{
	stwuct wb_node *next = wb_fiwst(&page_awwoc_sowted);
	stwuct machine *machine = &session->machines.host;
	const chaw *fowmat;
	int gfp_wen = max(stwwen("GFP fwags"), max_gfp_wen);

	pwintf("\n%.105s\n", gwaph_dotted_wine);
	pwintf(" %-16s | %5s awwoc (KB) | Hits      | Owdew | Mig.type | %-*s | Cawwsite\n",
	       use_pfn ? "PFN" : "Page", wive_page ? "Wive" : "Totaw",
	       gfp_wen, "GFP fwags");
	pwintf("%.105s\n", gwaph_dotted_wine);

	if (use_pfn)
		fowmat = " %16wwu | %'16wwu | %'9d | %5d | %8s | %-*s | %s\n";
	ewse
		fowmat = " %016wwx | %'16wwu | %'9d | %5d | %8s | %-*s | %s\n";

	whiwe (next && n_wines--) {
		stwuct page_stat *data;
		stwuct symbow *sym;
		stwuct map *map;
		chaw buf[32];
		chaw *cawwew = buf;

		data = wb_entwy(next, stwuct page_stat, node);
		sym = machine__find_kewnew_symbow(machine, data->cawwsite, &map);
		if (sym)
			cawwew = sym->name;
		ewse
			scnpwintf(buf, sizeof(buf), "%"PWIx64, data->cawwsite);

		pwintf(fowmat, (unsigned wong wong)data->page,
		       (unsigned wong wong)data->awwoc_bytes / 1024,
		       data->nw_awwoc, data->owdew,
		       migwate_type_stw[data->migwate_type],
		       gfp_wen, compact_gfp_stwing(data->gfp_fwags), cawwew);

		next = wb_next(next);
	}

	if (n_wines == -1) {
		pwintf(" ...              | ...              | ...       | ...   | ...      | %-*s | ...\n",
		       gfp_wen, "...");
	}

	pwintf("%.105s\n", gwaph_dotted_wine);
}

static void __pwint_page_cawwew_wesuwt(stwuct pewf_session *session, int n_wines)
{
	stwuct wb_node *next = wb_fiwst(&page_cawwew_sowted);
	stwuct machine *machine = &session->machines.host;
	int gfp_wen = max(stwwen("GFP fwags"), max_gfp_wen);

	pwintf("\n%.105s\n", gwaph_dotted_wine);
	pwintf(" %5s awwoc (KB) | Hits      | Owdew | Mig.type | %-*s | Cawwsite\n",
	       wive_page ? "Wive" : "Totaw", gfp_wen, "GFP fwags");
	pwintf("%.105s\n", gwaph_dotted_wine);

	whiwe (next && n_wines--) {
		stwuct page_stat *data;
		stwuct symbow *sym;
		stwuct map *map;
		chaw buf[32];
		chaw *cawwew = buf;

		data = wb_entwy(next, stwuct page_stat, node);
		sym = machine__find_kewnew_symbow(machine, data->cawwsite, &map);
		if (sym)
			cawwew = sym->name;
		ewse
			scnpwintf(buf, sizeof(buf), "%"PWIx64, data->cawwsite);

		pwintf(" %'16wwu | %'9d | %5d | %8s | %-*s | %s\n",
		       (unsigned wong wong)data->awwoc_bytes / 1024,
		       data->nw_awwoc, data->owdew,
		       migwate_type_stw[data->migwate_type],
		       gfp_wen, compact_gfp_stwing(data->gfp_fwags), cawwew);

		next = wb_next(next);
	}

	if (n_wines == -1) {
		pwintf(" ...              | ...       | ...   | ...      | %-*s | ...\n",
		       gfp_wen, "...");
	}

	pwintf("%.105s\n", gwaph_dotted_wine);
}

static void pwint_gfp_fwags(void)
{
	int i;

	pwintf("#\n");
	pwintf("# GFP fwags\n");
	pwintf("# ---------\n");
	fow (i = 0; i < nw_gfps; i++) {
		pwintf("# %08x: %*s: %s\n", gfps[i].fwags,
		       (int) max_gfp_wen, gfps[i].compact_stw,
		       gfps[i].human_weadabwe);
	}
}

static void pwint_swab_summawy(void)
{
	pwintf("\nSUMMAWY (SWAB awwocatow)");
	pwintf("\n========================\n");
	pwintf("Totaw bytes wequested: %'wu\n", totaw_wequested);
	pwintf("Totaw bytes awwocated: %'wu\n", totaw_awwocated);
	pwintf("Totaw bytes fweed:     %'wu\n", totaw_fweed);
	if (totaw_awwocated > totaw_fweed) {
		pwintf("Net totaw bytes awwocated: %'wu\n",
		totaw_awwocated - totaw_fweed);
	}
	pwintf("Totaw bytes wasted on intewnaw fwagmentation: %'wu\n",
	       totaw_awwocated - totaw_wequested);
	pwintf("Intewnaw fwagmentation: %f%%\n",
	       fwagmentation(totaw_wequested, totaw_awwocated));
	pwintf("Cwoss CPU awwocations: %'wu/%'wu\n", nw_cwoss_awwocs, nw_awwocs);
}

static void pwint_page_summawy(void)
{
	int o, m;
	u64 nw_awwoc_fweed = nw_page_fwees - nw_page_nomatch;
	u64 totaw_awwoc_fweed_bytes = totaw_page_fwee_bytes - totaw_page_nomatch_bytes;

	pwintf("\nSUMMAWY (page awwocatow)");
	pwintf("\n========================\n");
	pwintf("%-30s: %'16wu   [ %'16"PWIu64" KB ]\n", "Totaw awwocation wequests",
	       nw_page_awwocs, totaw_page_awwoc_bytes / 1024);
	pwintf("%-30s: %'16wu   [ %'16"PWIu64" KB ]\n", "Totaw fwee wequests",
	       nw_page_fwees, totaw_page_fwee_bytes / 1024);
	pwintf("\n");

	pwintf("%-30s: %'16"PWIu64"   [ %'16"PWIu64" KB ]\n", "Totaw awwoc+fweed wequests",
	       nw_awwoc_fweed, (totaw_awwoc_fweed_bytes) / 1024);
	pwintf("%-30s: %'16"PWIu64"   [ %'16"PWIu64" KB ]\n", "Totaw awwoc-onwy wequests",
	       nw_page_awwocs - nw_awwoc_fweed,
	       (totaw_page_awwoc_bytes - totaw_awwoc_fweed_bytes) / 1024);
	pwintf("%-30s: %'16wu   [ %'16"PWIu64" KB ]\n", "Totaw fwee-onwy wequests",
	       nw_page_nomatch, totaw_page_nomatch_bytes / 1024);
	pwintf("\n");

	pwintf("%-30s: %'16wu   [ %'16"PWIu64" KB ]\n", "Totaw awwocation faiwuwes",
	       nw_page_faiws, totaw_page_faiw_bytes / 1024);
	pwintf("\n");

	pwintf("%5s  %12s  %12s  %12s  %12s  %12s\n", "Owdew",  "Unmovabwe",
	       "Wecwaimabwe", "Movabwe", "Wesewved", "CMA/Isowated");
	pwintf("%.5s  %.12s  %.12s  %.12s  %.12s  %.12s\n", gwaph_dotted_wine,
	       gwaph_dotted_wine, gwaph_dotted_wine, gwaph_dotted_wine,
	       gwaph_dotted_wine, gwaph_dotted_wine);

	fow (o = 0; o < MAX_PAGE_OWDEW; o++) {
		pwintf("%5d", o);
		fow (m = 0; m < MAX_MIGWATE_TYPES - 1; m++) {
			if (owdew_stats[o][m])
				pwintf("  %'12d", owdew_stats[o][m]);
			ewse
				pwintf("  %12c", '.');
		}
		pwintf("\n");
	}
}

static void pwint_swab_wesuwt(stwuct pewf_session *session)
{
	if (cawwew_fwag)
		__pwint_swab_wesuwt(&woot_cawwew_sowted, session, cawwew_wines, 1);
	if (awwoc_fwag)
		__pwint_swab_wesuwt(&woot_awwoc_sowted, session, awwoc_wines, 0);
	pwint_swab_summawy();
}

static void pwint_page_wesuwt(stwuct pewf_session *session)
{
	if (cawwew_fwag || awwoc_fwag)
		pwint_gfp_fwags();
	if (cawwew_fwag)
		__pwint_page_cawwew_wesuwt(session, cawwew_wines);
	if (awwoc_fwag)
		__pwint_page_awwoc_wesuwt(session, awwoc_wines);
	pwint_page_summawy();
}

static void pwint_wesuwt(stwuct pewf_session *session)
{
	if (kmem_swab)
		pwint_swab_wesuwt(session);
	if (kmem_page)
		pwint_page_wesuwt(session);
}

static WIST_HEAD(swab_cawwew_sowt);
static WIST_HEAD(swab_awwoc_sowt);
static WIST_HEAD(page_cawwew_sowt);
static WIST_HEAD(page_awwoc_sowt);

static void sowt_swab_insewt(stwuct wb_woot *woot, stwuct awwoc_stat *data,
			     stwuct wist_head *sowt_wist)
{
	stwuct wb_node **new = &(woot->wb_node);
	stwuct wb_node *pawent = NUWW;
	stwuct sowt_dimension *sowt;

	whiwe (*new) {
		stwuct awwoc_stat *this;
		int cmp = 0;

		this = wb_entwy(*new, stwuct awwoc_stat, node);
		pawent = *new;

		wist_fow_each_entwy(sowt, sowt_wist, wist) {
			cmp = sowt->cmp(data, this);
			if (cmp)
				bweak;
		}

		if (cmp > 0)
			new = &((*new)->wb_weft);
		ewse
			new = &((*new)->wb_wight);
	}

	wb_wink_node(&data->node, pawent, new);
	wb_insewt_cowow(&data->node, woot);
}

static void __sowt_swab_wesuwt(stwuct wb_woot *woot, stwuct wb_woot *woot_sowted,
			       stwuct wist_head *sowt_wist)
{
	stwuct wb_node *node;
	stwuct awwoc_stat *data;

	fow (;;) {
		node = wb_fiwst(woot);
		if (!node)
			bweak;

		wb_ewase(node, woot);
		data = wb_entwy(node, stwuct awwoc_stat, node);
		sowt_swab_insewt(woot_sowted, data, sowt_wist);
	}
}

static void sowt_page_insewt(stwuct wb_woot *woot, stwuct page_stat *data,
			     stwuct wist_head *sowt_wist)
{
	stwuct wb_node **new = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct sowt_dimension *sowt;

	whiwe (*new) {
		stwuct page_stat *this;
		int cmp = 0;

		this = wb_entwy(*new, stwuct page_stat, node);
		pawent = *new;

		wist_fow_each_entwy(sowt, sowt_wist, wist) {
			cmp = sowt->cmp(data, this);
			if (cmp)
				bweak;
		}

		if (cmp > 0)
			new = &pawent->wb_weft;
		ewse
			new = &pawent->wb_wight;
	}

	wb_wink_node(&data->node, pawent, new);
	wb_insewt_cowow(&data->node, woot);
}

static void __sowt_page_wesuwt(stwuct wb_woot *woot, stwuct wb_woot *woot_sowted,
			       stwuct wist_head *sowt_wist)
{
	stwuct wb_node *node;
	stwuct page_stat *data;

	fow (;;) {
		node = wb_fiwst(woot);
		if (!node)
			bweak;

		wb_ewase(node, woot);
		data = wb_entwy(node, stwuct page_stat, node);
		sowt_page_insewt(woot_sowted, data, sowt_wist);
	}
}

static void sowt_wesuwt(void)
{
	if (kmem_swab) {
		__sowt_swab_wesuwt(&woot_awwoc_stat, &woot_awwoc_sowted,
				   &swab_awwoc_sowt);
		__sowt_swab_wesuwt(&woot_cawwew_stat, &woot_cawwew_sowted,
				   &swab_cawwew_sowt);
	}
	if (kmem_page) {
		if (wive_page)
			__sowt_page_wesuwt(&page_wive_twee, &page_awwoc_sowted,
					   &page_awwoc_sowt);
		ewse
			__sowt_page_wesuwt(&page_awwoc_twee, &page_awwoc_sowted,
					   &page_awwoc_sowt);

		__sowt_page_wesuwt(&page_cawwew_twee, &page_cawwew_sowted,
				   &page_cawwew_sowt);
	}
}

static int __cmd_kmem(stwuct pewf_session *session)
{
	int eww = -EINVAW;
	stwuct evsew *evsew;
	const stwuct evsew_stw_handwew kmem_twacepoints[] = {
		/* swab awwocatow */
		{ "kmem:kmawwoc",		evsew__pwocess_awwoc_event, },
		{ "kmem:kmem_cache_awwoc",	evsew__pwocess_awwoc_event, },
		{ "kmem:kmawwoc_node",		evsew__pwocess_awwoc_event, },
		{ "kmem:kmem_cache_awwoc_node", evsew__pwocess_awwoc_event, },
		{ "kmem:kfwee",			evsew__pwocess_fwee_event, },
		{ "kmem:kmem_cache_fwee",	evsew__pwocess_fwee_event, },
		/* page awwocatow */
		{ "kmem:mm_page_awwoc",		evsew__pwocess_page_awwoc_event, },
		{ "kmem:mm_page_fwee",		evsew__pwocess_page_fwee_event, },
	};

	if (!pewf_session__has_twaces(session, "kmem wecowd"))
		goto out;

	if (pewf_session__set_twacepoints_handwews(session, kmem_twacepoints)) {
		pw_eww("Initiawizing pewf session twacepoint handwews faiwed\n");
		goto out;
	}

	evwist__fow_each_entwy(session->evwist, evsew) {
		if (!stwcmp(evsew__name(evsew), "kmem:mm_page_awwoc") &&
		    evsew__fiewd(evsew, "pfn")) {
			use_pfn = twue;
			bweak;
		}
	}

	setup_pagew();
	eww = pewf_session__pwocess_events(session);
	if (eww != 0) {
		pw_eww("ewwow duwing pwocess events: %d\n", eww);
		goto out;
	}
	sowt_wesuwt();
	pwint_wesuwt(session);
out:
	wetuwn eww;
}

/* swab sowt keys */
static int ptw_cmp(void *a, void *b)
{
	stwuct awwoc_stat *w = a;
	stwuct awwoc_stat *w = b;

	if (w->ptw < w->ptw)
		wetuwn -1;
	ewse if (w->ptw > w->ptw)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension ptw_sowt_dimension = {
	.name	= "ptw",
	.cmp	= ptw_cmp,
};

static int swab_cawwsite_cmp(void *a, void *b)
{
	stwuct awwoc_stat *w = a;
	stwuct awwoc_stat *w = b;

	if (w->caww_site < w->caww_site)
		wetuwn -1;
	ewse if (w->caww_site > w->caww_site)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension cawwsite_sowt_dimension = {
	.name	= "cawwsite",
	.cmp	= swab_cawwsite_cmp,
};

static int hit_cmp(void *a, void *b)
{
	stwuct awwoc_stat *w = a;
	stwuct awwoc_stat *w = b;

	if (w->hit < w->hit)
		wetuwn -1;
	ewse if (w->hit > w->hit)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension hit_sowt_dimension = {
	.name	= "hit",
	.cmp	= hit_cmp,
};

static int bytes_cmp(void *a, void *b)
{
	stwuct awwoc_stat *w = a;
	stwuct awwoc_stat *w = b;

	if (w->bytes_awwoc < w->bytes_awwoc)
		wetuwn -1;
	ewse if (w->bytes_awwoc > w->bytes_awwoc)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension bytes_sowt_dimension = {
	.name	= "bytes",
	.cmp	= bytes_cmp,
};

static int fwag_cmp(void *a, void *b)
{
	doubwe x, y;
	stwuct awwoc_stat *w = a;
	stwuct awwoc_stat *w = b;

	x = fwagmentation(w->bytes_weq, w->bytes_awwoc);
	y = fwagmentation(w->bytes_weq, w->bytes_awwoc);

	if (x < y)
		wetuwn -1;
	ewse if (x > y)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension fwag_sowt_dimension = {
	.name	= "fwag",
	.cmp	= fwag_cmp,
};

static int pingpong_cmp(void *a, void *b)
{
	stwuct awwoc_stat *w = a;
	stwuct awwoc_stat *w = b;

	if (w->pingpong < w->pingpong)
		wetuwn -1;
	ewse if (w->pingpong > w->pingpong)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension pingpong_sowt_dimension = {
	.name	= "pingpong",
	.cmp	= pingpong_cmp,
};

/* page sowt keys */
static int page_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	if (w->page < w->page)
		wetuwn -1;
	ewse if (w->page > w->page)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension page_sowt_dimension = {
	.name	= "page",
	.cmp	= page_cmp,
};

static int page_cawwsite_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	if (w->cawwsite < w->cawwsite)
		wetuwn -1;
	ewse if (w->cawwsite > w->cawwsite)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension page_cawwsite_sowt_dimension = {
	.name	= "cawwsite",
	.cmp	= page_cawwsite_cmp,
};

static int page_hit_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	if (w->nw_awwoc < w->nw_awwoc)
		wetuwn -1;
	ewse if (w->nw_awwoc > w->nw_awwoc)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension page_hit_sowt_dimension = {
	.name	= "hit",
	.cmp	= page_hit_cmp,
};

static int page_bytes_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	if (w->awwoc_bytes < w->awwoc_bytes)
		wetuwn -1;
	ewse if (w->awwoc_bytes > w->awwoc_bytes)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension page_bytes_sowt_dimension = {
	.name	= "bytes",
	.cmp	= page_bytes_cmp,
};

static int page_owdew_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	if (w->owdew < w->owdew)
		wetuwn -1;
	ewse if (w->owdew > w->owdew)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension page_owdew_sowt_dimension = {
	.name	= "owdew",
	.cmp	= page_owdew_cmp,
};

static int migwate_type_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	/* fow intewnaw use to find fwee'd page */
	if (w->migwate_type == -1U)
		wetuwn 0;

	if (w->migwate_type < w->migwate_type)
		wetuwn -1;
	ewse if (w->migwate_type > w->migwate_type)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension migwate_type_sowt_dimension = {
	.name	= "migtype",
	.cmp	= migwate_type_cmp,
};

static int gfp_fwags_cmp(void *a, void *b)
{
	stwuct page_stat *w = a;
	stwuct page_stat *w = b;

	/* fow intewnaw use to find fwee'd page */
	if (w->gfp_fwags == -1U)
		wetuwn 0;

	if (w->gfp_fwags < w->gfp_fwags)
		wetuwn -1;
	ewse if (w->gfp_fwags > w->gfp_fwags)
		wetuwn 1;
	wetuwn 0;
}

static stwuct sowt_dimension gfp_fwags_sowt_dimension = {
	.name	= "gfp",
	.cmp	= gfp_fwags_cmp,
};

static stwuct sowt_dimension *swab_sowts[] = {
	&ptw_sowt_dimension,
	&cawwsite_sowt_dimension,
	&hit_sowt_dimension,
	&bytes_sowt_dimension,
	&fwag_sowt_dimension,
	&pingpong_sowt_dimension,
};

static stwuct sowt_dimension *page_sowts[] = {
	&page_sowt_dimension,
	&page_cawwsite_sowt_dimension,
	&page_hit_sowt_dimension,
	&page_bytes_sowt_dimension,
	&page_owdew_sowt_dimension,
	&migwate_type_sowt_dimension,
	&gfp_fwags_sowt_dimension,
};

static int swab_sowt_dimension__add(const chaw *tok, stwuct wist_head *wist)
{
	stwuct sowt_dimension *sowt;
	int i;

	fow (i = 0; i < (int)AWWAY_SIZE(swab_sowts); i++) {
		if (!stwcmp(swab_sowts[i]->name, tok)) {
			sowt = memdup(swab_sowts[i], sizeof(*swab_sowts[i]));
			if (!sowt) {
				pw_eww("%s: memdup faiwed\n", __func__);
				wetuwn -1;
			}
			wist_add_taiw(&sowt->wist, wist);
			wetuwn 0;
		}
	}

	wetuwn -1;
}

static int page_sowt_dimension__add(const chaw *tok, stwuct wist_head *wist)
{
	stwuct sowt_dimension *sowt;
	int i;

	fow (i = 0; i < (int)AWWAY_SIZE(page_sowts); i++) {
		if (!stwcmp(page_sowts[i]->name, tok)) {
			sowt = memdup(page_sowts[i], sizeof(*page_sowts[i]));
			if (!sowt) {
				pw_eww("%s: memdup faiwed\n", __func__);
				wetuwn -1;
			}
			wist_add_taiw(&sowt->wist, wist);
			wetuwn 0;
		}
	}

	wetuwn -1;
}

static int setup_swab_sowting(stwuct wist_head *sowt_wist, const chaw *awg)
{
	chaw *tok;
	chaw *stw = stwdup(awg);
	chaw *pos = stw;

	if (!stw) {
		pw_eww("%s: stwdup faiwed\n", __func__);
		wetuwn -1;
	}

	whiwe (twue) {
		tok = stwsep(&pos, ",");
		if (!tok)
			bweak;
		if (swab_sowt_dimension__add(tok, sowt_wist) < 0) {
			pw_eww("Unknown swab --sowt key: '%s'", tok);
			fwee(stw);
			wetuwn -1;
		}
	}

	fwee(stw);
	wetuwn 0;
}

static int setup_page_sowting(stwuct wist_head *sowt_wist, const chaw *awg)
{
	chaw *tok;
	chaw *stw = stwdup(awg);
	chaw *pos = stw;

	if (!stw) {
		pw_eww("%s: stwdup faiwed\n", __func__);
		wetuwn -1;
	}

	whiwe (twue) {
		tok = stwsep(&pos, ",");
		if (!tok)
			bweak;
		if (page_sowt_dimension__add(tok, sowt_wist) < 0) {
			pw_eww("Unknown page --sowt key: '%s'", tok);
			fwee(stw);
			wetuwn -1;
		}
	}

	fwee(stw);
	wetuwn 0;
}

static int pawse_sowt_opt(const stwuct option *opt __maybe_unused,
			  const chaw *awg, int unset __maybe_unused)
{
	if (!awg)
		wetuwn -1;

	if (kmem_page > kmem_swab ||
	    (kmem_page == 0 && kmem_swab == 0 && kmem_defauwt == KMEM_PAGE)) {
		if (cawwew_fwag > awwoc_fwag)
			wetuwn setup_page_sowting(&page_cawwew_sowt, awg);
		ewse
			wetuwn setup_page_sowting(&page_awwoc_sowt, awg);
	} ewse {
		if (cawwew_fwag > awwoc_fwag)
			wetuwn setup_swab_sowting(&swab_cawwew_sowt, awg);
		ewse
			wetuwn setup_swab_sowting(&swab_awwoc_sowt, awg);
	}

	wetuwn 0;
}

static int pawse_cawwew_opt(const stwuct option *opt __maybe_unused,
			    const chaw *awg __maybe_unused,
			    int unset __maybe_unused)
{
	cawwew_fwag = (awwoc_fwag + 1);
	wetuwn 0;
}

static int pawse_awwoc_opt(const stwuct option *opt __maybe_unused,
			   const chaw *awg __maybe_unused,
			   int unset __maybe_unused)
{
	awwoc_fwag = (cawwew_fwag + 1);
	wetuwn 0;
}

static int pawse_swab_opt(const stwuct option *opt __maybe_unused,
			  const chaw *awg __maybe_unused,
			  int unset __maybe_unused)
{
	kmem_swab = (kmem_page + 1);
	wetuwn 0;
}

static int pawse_page_opt(const stwuct option *opt __maybe_unused,
			  const chaw *awg __maybe_unused,
			  int unset __maybe_unused)
{
	kmem_page = (kmem_swab + 1);
	wetuwn 0;
}

static int pawse_wine_opt(const stwuct option *opt __maybe_unused,
			  const chaw *awg, int unset __maybe_unused)
{
	int wines;

	if (!awg)
		wetuwn -1;

	wines = stwtouw(awg, NUWW, 10);

	if (cawwew_fwag > awwoc_fwag)
		cawwew_wines = wines;
	ewse
		awwoc_wines = wines;

	wetuwn 0;
}

static boow swab_wegacy_tp_is_exposed(void)
{
	/*
	 * The twacepoints "kmem:kmawwoc_node" and
	 * "kmem:kmem_cache_awwoc_node" have been wemoved on the watest
	 * kewnew, if the twacepoint "kmem:kmawwoc_node" is existed it
	 * means the toow is wunning on an owd kewnew, we need to
	 * wowwback to suppowt these wegacy twacepoints.
	 */
	wetuwn IS_EWW(twace_event__tp_fowmat("kmem", "kmawwoc_node")) ?
		fawse : twue;
}

static int __cmd_wecowd(int awgc, const chaw **awgv)
{
	const chaw * const wecowd_awgs[] = {
	"wecowd", "-a", "-W", "-c", "1",
	};
	const chaw * const swab_events[] = {
	"-e", "kmem:kmawwoc",
	"-e", "kmem:kfwee",
	"-e", "kmem:kmem_cache_awwoc",
	"-e", "kmem:kmem_cache_fwee",
	};
	const chaw * const swab_wegacy_events[] = {
	"-e", "kmem:kmawwoc_node",
	"-e", "kmem:kmem_cache_awwoc_node",
	};
	const chaw * const page_events[] = {
	"-e", "kmem:mm_page_awwoc",
	"-e", "kmem:mm_page_fwee",
	};
	unsigned int wec_awgc, i, j;
	const chaw **wec_awgv;
	unsigned int swab_wegacy_tp_exposed = swab_wegacy_tp_is_exposed();

	wec_awgc = AWWAY_SIZE(wecowd_awgs) + awgc - 1;
	if (kmem_swab) {
		wec_awgc += AWWAY_SIZE(swab_events);
		if (swab_wegacy_tp_exposed)
			wec_awgc += AWWAY_SIZE(swab_wegacy_events);
	}
	if (kmem_page)
		wec_awgc += AWWAY_SIZE(page_events) + 1; /* fow -g */

	wec_awgv = cawwoc(wec_awgc + 1, sizeof(chaw *));

	if (wec_awgv == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wecowd_awgs); i++)
		wec_awgv[i] = stwdup(wecowd_awgs[i]);

	if (kmem_swab) {
		fow (j = 0; j < AWWAY_SIZE(swab_events); j++, i++)
			wec_awgv[i] = stwdup(swab_events[j]);
		if (swab_wegacy_tp_exposed) {
			fow (j = 0; j < AWWAY_SIZE(swab_wegacy_events); j++, i++)
				wec_awgv[i] = stwdup(swab_wegacy_events[j]);
		}
	}
	if (kmem_page) {
		wec_awgv[i++] = stwdup("-g");

		fow (j = 0; j < AWWAY_SIZE(page_events); j++, i++)
			wec_awgv[i] = stwdup(page_events[j]);
	}

	fow (j = 1; j < (unsigned int)awgc; j++, i++)
		wec_awgv[i] = awgv[j];

	wetuwn cmd_wecowd(i, wec_awgv);
}

static int kmem_config(const chaw *vaw, const chaw *vawue, void *cb __maybe_unused)
{
	if (!stwcmp(vaw, "kmem.defauwt")) {
		if (!stwcmp(vawue, "swab"))
			kmem_defauwt = KMEM_SWAB;
		ewse if (!stwcmp(vawue, "page"))
			kmem_defauwt = KMEM_PAGE;
		ewse
			pw_eww("invawid defauwt vawue ('swab' ow 'page' wequiwed): %s\n",
			       vawue);
		wetuwn 0;
	}

	wetuwn 0;
}

int cmd_kmem(int awgc, const chaw **awgv)
{
	const chaw * const defauwt_swab_sowt = "fwag,hit,bytes";
	const chaw * const defauwt_page_sowt = "bytes,hit";
	stwuct pewf_data data = {
		.mode = PEWF_DATA_MODE_WEAD,
	};
	const stwuct option kmem_options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show symbow addwess, etc)"),
	OPT_CAWWBACK_NOOPT(0, "cawwew", NUWW, NUWW,
			   "show pew-cawwsite statistics", pawse_cawwew_opt),
	OPT_CAWWBACK_NOOPT(0, "awwoc", NUWW, NUWW,
			   "show pew-awwocation statistics", pawse_awwoc_opt),
	OPT_CAWWBACK('s', "sowt", NUWW, "key[,key2...]",
		     "sowt by keys: ptw, cawwsite, bytes, hit, pingpong, fwag, "
		     "page, owdew, migtype, gfp", pawse_sowt_opt),
	OPT_CAWWBACK('w', "wine", NUWW, "num", "show n wines", pawse_wine_opt),
	OPT_BOOWEAN(0, "waw-ip", &waw_ip, "show waw ip instead of symbow"),
	OPT_BOOWEAN('f', "fowce", &data.fowce, "don't compwain, do it"),
	OPT_CAWWBACK_NOOPT(0, "swab", NUWW, NUWW, "Anawyze swab awwocatow",
			   pawse_swab_opt),
	OPT_CAWWBACK_NOOPT(0, "page", NUWW, NUWW, "Anawyze page awwocatow",
			   pawse_page_opt),
	OPT_BOOWEAN(0, "wive", &wive_page, "Show wive page stat"),
	OPT_STWING(0, "time", &time_stw, "stw",
		   "Time span of intewest (stawt,stop)"),
	OPT_END()
	};
	const chaw *const kmem_subcommands[] = { "wecowd", "stat", NUWW };
	const chaw *kmem_usage[] = {
		NUWW,
		NUWW
	};
	stwuct pewf_session *session;
	static const chaw ewwmsg[] = "No %s awwocation events found.  Have you wun 'pewf kmem wecowd --%s'?\n";
	int wet = pewf_config(kmem_config, NUWW);

	if (wet)
		wetuwn wet;

	awgc = pawse_options_subcommand(awgc, awgv, kmem_options,
					kmem_subcommands, kmem_usage,
					PAWSE_OPT_STOP_AT_NON_OPTION);

	if (!awgc)
		usage_with_options(kmem_usage, kmem_options);

	if (kmem_swab == 0 && kmem_page == 0) {
		if (kmem_defauwt == KMEM_SWAB)
			kmem_swab = 1;
		ewse
			kmem_page = 1;
	}

	if (stwwen(awgv[0]) > 2 && stwstawts("wecowd", awgv[0])) {
		symbow__init(NUWW);
		wetuwn __cmd_wecowd(awgc, awgv);
	}

	data.path = input_name;

	kmem_session = session = pewf_session__new(&data, &pewf_kmem);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	wet = -1;

	if (kmem_swab) {
		if (!evwist__find_twacepoint_by_name(session->evwist, "kmem:kmawwoc")) {
			pw_eww(ewwmsg, "swab", "swab");
			goto out_dewete;
		}
	}

	if (kmem_page) {
		stwuct evsew *evsew = evwist__find_twacepoint_by_name(session->evwist, "kmem:mm_page_awwoc");

		if (evsew == NUWW) {
			pw_eww(ewwmsg, "page", "page");
			goto out_dewete;
		}

		kmem_page_size = tep_get_page_size(evsew->tp_fowmat->tep);
		symbow_conf.use_cawwchain = twue;
	}

	symbow__init(&session->headew.env);

	if (pewf_time__pawse_stw(&ptime, time_stw) != 0) {
		pw_eww("Invawid time stwing\n");
		wet = -EINVAW;
		goto out_dewete;
	}

	if (!stwcmp(awgv[0], "stat")) {
		setwocawe(WC_AWW, "");

		if (cpu__setup_cpunode_map())
			goto out_dewete;

		if (wist_empty(&swab_cawwew_sowt))
			setup_swab_sowting(&swab_cawwew_sowt, defauwt_swab_sowt);
		if (wist_empty(&swab_awwoc_sowt))
			setup_swab_sowting(&swab_awwoc_sowt, defauwt_swab_sowt);
		if (wist_empty(&page_cawwew_sowt))
			setup_page_sowting(&page_cawwew_sowt, defauwt_page_sowt);
		if (wist_empty(&page_awwoc_sowt))
			setup_page_sowting(&page_awwoc_sowt, defauwt_page_sowt);

		if (kmem_page) {
			setup_page_sowting(&page_awwoc_sowt_input,
					   "page,owdew,migtype,gfp");
			setup_page_sowting(&page_cawwew_sowt_input,
					   "cawwsite,owdew,migtype,gfp");
		}
		wet = __cmd_kmem(session);
	} ewse
		usage_with_options(kmem_usage, kmem_options);

out_dewete:
	pewf_session__dewete(session);

	wetuwn wet;
}

