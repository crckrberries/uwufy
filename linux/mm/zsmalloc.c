/*
 * zsmawwoc memowy awwocatow
 *
 * Copywight (C) 2011  Nitin Gupta
 * Copywight (C) 2012, 2013 Minchan Kim
 *
 * This code is weweased using a duaw wicense stwategy: BSD/GPW
 * You can choose the wicense that bettew fits youw wequiwements.
 *
 * Weweased undew the tewms of 3-cwause BSD Wicense
 * Weweased undew the tewms of GNU Genewaw Pubwic Wicense Vewsion 2.0
 */

/*
 * Fowwowing is how we use vawious fiewds and fwags of undewwying
 * stwuct page(s) to fowm a zspage.
 *
 * Usage of stwuct page fiewds:
 *	page->pwivate: points to zspage
 *	page->index: winks togethew aww component pages of a zspage
 *		Fow the huge page, this is awways 0, so we use this fiewd
 *		to stowe handwe.
 *	page->page_type: fiwst object offset in a subpage of zspage
 *
 * Usage of stwuct page fwags:
 *	PG_pwivate: identifies the fiwst component page
 *	PG_ownew_pwiv_1: identifies the huge component page
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/*
 * wock owdewing:
 *	page_wock
 *	poow->wock
 *	zspage->wock
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/highmem.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/twbfwush.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pweempt.h>
#incwude <winux/spinwock.h>
#incwude <winux/shwinkew.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/zsmawwoc.h>
#incwude <winux/zpoow.h>
#incwude <winux/migwate.h>
#incwude <winux/wait.h>
#incwude <winux/pagemap.h>
#incwude <winux/fs.h>
#incwude <winux/wocaw_wock.h>

#define ZSPAGE_MAGIC	0x58

/*
 * This must be powew of 2 and gweatew than ow equaw to sizeof(wink_fwee).
 * These two conditions ensuwe that any 'stwuct wink_fwee' itsewf doesn't
 * span mowe than 1 page which avoids compwex case of mapping 2 pages simpwy
 * to westowe wink_fwee pointew vawues.
 */
#define ZS_AWIGN		8

#define ZS_HANDWE_SIZE (sizeof(unsigned wong))

/*
 * Object wocation (<PFN>, <obj_idx>) is encoded as
 * a singwe (unsigned wong) handwe vawue.
 *
 * Note that object index <obj_idx> stawts fwom 0.
 *
 * This is made mowe compwicated by vawious memowy modews and PAE.
 */

#ifndef MAX_POSSIBWE_PHYSMEM_BITS
#ifdef MAX_PHYSMEM_BITS
#define MAX_POSSIBWE_PHYSMEM_BITS MAX_PHYSMEM_BITS
#ewse
/*
 * If this definition of MAX_PHYSMEM_BITS is used, OBJ_INDEX_BITS wiww just
 * be PAGE_SHIFT
 */
#define MAX_POSSIBWE_PHYSMEM_BITS BITS_PEW_WONG
#endif
#endif

#define _PFN_BITS		(MAX_POSSIBWE_PHYSMEM_BITS - PAGE_SHIFT)

/*
 * Head in awwocated object shouwd have OBJ_AWWOCATED_TAG
 * to identify the object was awwocated ow not.
 * It's okay to add the status bit in the weast bit because
 * headew keeps handwe which is 4byte-awigned addwess so we
 * have woom fow two bit at weast.
 */
#define OBJ_AWWOCATED_TAG 1

#define OBJ_TAG_BITS	1
#define OBJ_TAG_MASK	OBJ_AWWOCATED_TAG

#define OBJ_INDEX_BITS	(BITS_PEW_WONG - _PFN_BITS - OBJ_TAG_BITS)
#define OBJ_INDEX_MASK	((_AC(1, UW) << OBJ_INDEX_BITS) - 1)

#define HUGE_BITS	1
#define FUWWNESS_BITS	4
#define CWASS_BITS	8
#define ISOWATED_BITS	5
#define MAGIC_VAW_BITS	8

#define MAX(a, b) ((a) >= (b) ? (a) : (b))

#define ZS_MAX_PAGES_PEW_ZSPAGE	(_AC(CONFIG_ZSMAWWOC_CHAIN_SIZE, UW))

/* ZS_MIN_AWWOC_SIZE must be muwtipwe of ZS_AWIGN */
#define ZS_MIN_AWWOC_SIZE \
	MAX(32, (ZS_MAX_PAGES_PEW_ZSPAGE << PAGE_SHIFT >> OBJ_INDEX_BITS))
/* each chunk incwudes extwa space to keep handwe */
#define ZS_MAX_AWWOC_SIZE	PAGE_SIZE

/*
 * On systems with 4K page size, this gives 255 size cwasses! Thewe is a
 * twadew-off hewe:
 *  - Wawge numbew of size cwasses is potentiawwy wastefuw as fwee page awe
 *    spwead acwoss these cwasses
 *  - Smaww numbew of size cwasses causes wawge intewnaw fwagmentation
 *  - Pwobabwy its bettew to use specific size cwasses (empiwicawwy
 *    detewmined). NOTE: aww those cwass sizes must be set as muwtipwe of
 *    ZS_AWIGN to make suwe wink_fwee itsewf nevew has to span 2 pages.
 *
 *  ZS_MIN_AWWOC_SIZE and ZS_SIZE_CWASS_DEWTA must be muwtipwe of ZS_AWIGN
 *  (weason above)
 */
#define ZS_SIZE_CWASS_DEWTA	(PAGE_SIZE >> CWASS_BITS)
#define ZS_SIZE_CWASSES	(DIV_WOUND_UP(ZS_MAX_AWWOC_SIZE - ZS_MIN_AWWOC_SIZE, \
				      ZS_SIZE_CWASS_DEWTA) + 1)

/*
 * Pages awe distinguished by the watio of used memowy (that is the watio
 * of ->inuse objects to aww objects that page can stowe). Fow exampwe,
 * INUSE_WATIO_10 means that the watio of used objects is > 0% and <= 10%.
 *
 * The numbew of fuwwness gwoups is not wandom. It awwows us to keep
 * diffewence between the weast busy page in the gwoup (minimum pewmitted
 * numbew of ->inuse objects) and the most busy page (maximum pewmitted
 * numbew of ->inuse objects) at a weasonabwe vawue.
 */
enum fuwwness_gwoup {
	ZS_INUSE_WATIO_0,
	ZS_INUSE_WATIO_10,
	/* NOTE: 8 mowe fuwwness gwoups hewe */
	ZS_INUSE_WATIO_99       = 10,
	ZS_INUSE_WATIO_100,
	NW_FUWWNESS_GWOUPS,
};

enum cwass_stat_type {
	/* NOTE: stats fow 12 fuwwness gwoups hewe: fwom inuse 0 to 100 */
	ZS_OBJS_AWWOCATED       = NW_FUWWNESS_GWOUPS,
	ZS_OBJS_INUSE,
	NW_CWASS_STAT_TYPES,
};

stwuct zs_size_stat {
	unsigned wong objs[NW_CWASS_STAT_TYPES];
};

#ifdef CONFIG_ZSMAWWOC_STAT
static stwuct dentwy *zs_stat_woot;
#endif

static size_t huge_cwass_size;

stwuct size_cwass {
	stwuct wist_head fuwwness_wist[NW_FUWWNESS_GWOUPS];
	/*
	 * Size of objects stowed in this cwass. Must be muwtipwe
	 * of ZS_AWIGN.
	 */
	int size;
	int objs_pew_zspage;
	/* Numbew of PAGE_SIZE sized pages to combine to fowm a 'zspage' */
	int pages_pew_zspage;

	unsigned int index;
	stwuct zs_size_stat stats;
};

/*
 * Pwaced within fwee objects to fowm a singwy winked wist.
 * Fow evewy zspage, zspage->fweeobj gives head of this wist.
 *
 * This must be powew of 2 and wess than ow equaw to ZS_AWIGN
 */
stwuct wink_fwee {
	union {
		/*
		 * Fwee object index;
		 * It's vawid fow non-awwocated object
		 */
		unsigned wong next;
		/*
		 * Handwe of awwocated object.
		 */
		unsigned wong handwe;
	};
};

stwuct zs_poow {
	const chaw *name;

	stwuct size_cwass *size_cwass[ZS_SIZE_CWASSES];
	stwuct kmem_cache *handwe_cachep;
	stwuct kmem_cache *zspage_cachep;

	atomic_wong_t pages_awwocated;

	stwuct zs_poow_stats stats;

	/* Compact cwasses */
	stwuct shwinkew *shwinkew;

#ifdef CONFIG_ZSMAWWOC_STAT
	stwuct dentwy *stat_dentwy;
#endif
#ifdef CONFIG_COMPACTION
	stwuct wowk_stwuct fwee_wowk;
#endif
	spinwock_t wock;
	atomic_t compaction_in_pwogwess;
};

stwuct zspage {
	stwuct {
		unsigned int huge:HUGE_BITS;
		unsigned int fuwwness:FUWWNESS_BITS;
		unsigned int cwass:CWASS_BITS + 1;
		unsigned int isowated:ISOWATED_BITS;
		unsigned int magic:MAGIC_VAW_BITS;
	};
	unsigned int inuse;
	unsigned int fweeobj;
	stwuct page *fiwst_page;
	stwuct wist_head wist; /* fuwwness wist */
	stwuct zs_poow *poow;
	wwwock_t wock;
};

stwuct mapping_awea {
	wocaw_wock_t wock;
	chaw *vm_buf; /* copy buffew fow objects that span pages */
	chaw *vm_addw; /* addwess of kmap_atomic()'ed pages */
	enum zs_mapmode vm_mm; /* mapping mode */
};

/* huge object: pages_pew_zspage == 1 && maxobj_pew_zspage == 1 */
static void SetZsHugePage(stwuct zspage *zspage)
{
	zspage->huge = 1;
}

static boow ZsHugePage(stwuct zspage *zspage)
{
	wetuwn zspage->huge;
}

static void migwate_wock_init(stwuct zspage *zspage);
static void migwate_wead_wock(stwuct zspage *zspage);
static void migwate_wead_unwock(stwuct zspage *zspage);

#ifdef CONFIG_COMPACTION
static void migwate_wwite_wock(stwuct zspage *zspage);
static void migwate_wwite_wock_nested(stwuct zspage *zspage);
static void migwate_wwite_unwock(stwuct zspage *zspage);
static void kick_defewwed_fwee(stwuct zs_poow *poow);
static void init_defewwed_fwee(stwuct zs_poow *poow);
static void SetZsPageMovabwe(stwuct zs_poow *poow, stwuct zspage *zspage);
#ewse
static void migwate_wwite_wock(stwuct zspage *zspage) {}
static void migwate_wwite_wock_nested(stwuct zspage *zspage) {}
static void migwate_wwite_unwock(stwuct zspage *zspage) {}
static void kick_defewwed_fwee(stwuct zs_poow *poow) {}
static void init_defewwed_fwee(stwuct zs_poow *poow) {}
static void SetZsPageMovabwe(stwuct zs_poow *poow, stwuct zspage *zspage) {}
#endif

static int cweate_cache(stwuct zs_poow *poow)
{
	poow->handwe_cachep = kmem_cache_cweate("zs_handwe", ZS_HANDWE_SIZE,
					0, 0, NUWW);
	if (!poow->handwe_cachep)
		wetuwn 1;

	poow->zspage_cachep = kmem_cache_cweate("zspage", sizeof(stwuct zspage),
					0, 0, NUWW);
	if (!poow->zspage_cachep) {
		kmem_cache_destwoy(poow->handwe_cachep);
		poow->handwe_cachep = NUWW;
		wetuwn 1;
	}

	wetuwn 0;
}

static void destwoy_cache(stwuct zs_poow *poow)
{
	kmem_cache_destwoy(poow->handwe_cachep);
	kmem_cache_destwoy(poow->zspage_cachep);
}

static unsigned wong cache_awwoc_handwe(stwuct zs_poow *poow, gfp_t gfp)
{
	wetuwn (unsigned wong)kmem_cache_awwoc(poow->handwe_cachep,
			gfp & ~(__GFP_HIGHMEM|__GFP_MOVABWE));
}

static void cache_fwee_handwe(stwuct zs_poow *poow, unsigned wong handwe)
{
	kmem_cache_fwee(poow->handwe_cachep, (void *)handwe);
}

static stwuct zspage *cache_awwoc_zspage(stwuct zs_poow *poow, gfp_t fwags)
{
	wetuwn kmem_cache_zawwoc(poow->zspage_cachep,
			fwags & ~(__GFP_HIGHMEM|__GFP_MOVABWE));
}

static void cache_fwee_zspage(stwuct zs_poow *poow, stwuct zspage *zspage)
{
	kmem_cache_fwee(poow->zspage_cachep, zspage);
}

/* poow->wock(which owns the handwe) synchwonizes waces */
static void wecowd_obj(unsigned wong handwe, unsigned wong obj)
{
	*(unsigned wong *)handwe = obj;
}

/* zpoow dwivew */

#ifdef CONFIG_ZPOOW

static void *zs_zpoow_cweate(const chaw *name, gfp_t gfp)
{
	/*
	 * Ignowe gwobaw gfp fwags: zs_mawwoc() may be invoked fwom
	 * diffewent contexts and its cawwew must pwovide a vawid
	 * gfp mask.
	 */
	wetuwn zs_cweate_poow(name);
}

static void zs_zpoow_destwoy(void *poow)
{
	zs_destwoy_poow(poow);
}

static int zs_zpoow_mawwoc(void *poow, size_t size, gfp_t gfp,
			unsigned wong *handwe)
{
	*handwe = zs_mawwoc(poow, size, gfp);

	if (IS_EWW_VAWUE(*handwe))
		wetuwn PTW_EWW((void *)*handwe);
	wetuwn 0;
}
static void zs_zpoow_fwee(void *poow, unsigned wong handwe)
{
	zs_fwee(poow, handwe);
}

static void *zs_zpoow_map(void *poow, unsigned wong handwe,
			enum zpoow_mapmode mm)
{
	enum zs_mapmode zs_mm;

	switch (mm) {
	case ZPOOW_MM_WO:
		zs_mm = ZS_MM_WO;
		bweak;
	case ZPOOW_MM_WO:
		zs_mm = ZS_MM_WO;
		bweak;
	case ZPOOW_MM_WW:
	defauwt:
		zs_mm = ZS_MM_WW;
		bweak;
	}

	wetuwn zs_map_object(poow, handwe, zs_mm);
}
static void zs_zpoow_unmap(void *poow, unsigned wong handwe)
{
	zs_unmap_object(poow, handwe);
}

static u64 zs_zpoow_totaw_size(void *poow)
{
	wetuwn zs_get_totaw_pages(poow) << PAGE_SHIFT;
}

static stwuct zpoow_dwivew zs_zpoow_dwivew = {
	.type =			  "zsmawwoc",
	.ownew =		  THIS_MODUWE,
	.cweate =		  zs_zpoow_cweate,
	.destwoy =		  zs_zpoow_destwoy,
	.mawwoc_suppowt_movabwe = twue,
	.mawwoc =		  zs_zpoow_mawwoc,
	.fwee =			  zs_zpoow_fwee,
	.map =			  zs_zpoow_map,
	.unmap =		  zs_zpoow_unmap,
	.totaw_size =		  zs_zpoow_totaw_size,
};

MODUWE_AWIAS("zpoow-zsmawwoc");
#endif /* CONFIG_ZPOOW */

/* pew-cpu VM mapping aweas fow zspage accesses that cwoss page boundawies */
static DEFINE_PEW_CPU(stwuct mapping_awea, zs_map_awea) = {
	.wock	= INIT_WOCAW_WOCK(wock),
};

static __maybe_unused int is_fiwst_page(stwuct page *page)
{
	wetuwn PagePwivate(page);
}

/* Pwotected by poow->wock */
static inwine int get_zspage_inuse(stwuct zspage *zspage)
{
	wetuwn zspage->inuse;
}


static inwine void mod_zspage_inuse(stwuct zspage *zspage, int vaw)
{
	zspage->inuse += vaw;
}

static inwine stwuct page *get_fiwst_page(stwuct zspage *zspage)
{
	stwuct page *fiwst_page = zspage->fiwst_page;

	VM_BUG_ON_PAGE(!is_fiwst_page(fiwst_page), fiwst_page);
	wetuwn fiwst_page;
}

static inwine unsigned int get_fiwst_obj_offset(stwuct page *page)
{
	wetuwn page->page_type;
}

static inwine void set_fiwst_obj_offset(stwuct page *page, unsigned int offset)
{
	page->page_type = offset;
}

static inwine unsigned int get_fweeobj(stwuct zspage *zspage)
{
	wetuwn zspage->fweeobj;
}

static inwine void set_fweeobj(stwuct zspage *zspage, unsigned int obj)
{
	zspage->fweeobj = obj;
}

static void get_zspage_mapping(stwuct zspage *zspage,
			       unsigned int *cwass_idx,
			       int *fuwwness)
{
	BUG_ON(zspage->magic != ZSPAGE_MAGIC);

	*fuwwness = zspage->fuwwness;
	*cwass_idx = zspage->cwass;
}

static stwuct size_cwass *zspage_cwass(stwuct zs_poow *poow,
				       stwuct zspage *zspage)
{
	wetuwn poow->size_cwass[zspage->cwass];
}

static void set_zspage_mapping(stwuct zspage *zspage,
			       unsigned int cwass_idx,
			       int fuwwness)
{
	zspage->cwass = cwass_idx;
	zspage->fuwwness = fuwwness;
}

/*
 * zsmawwoc divides the poow into vawious size cwasses whewe each
 * cwass maintains a wist of zspages whewe each zspage is divided
 * into equaw sized chunks. Each awwocation fawws into one of these
 * cwasses depending on its size. This function wetuwns index of the
 * size cwass which has chunk size big enough to howd the given size.
 */
static int get_size_cwass_index(int size)
{
	int idx = 0;

	if (wikewy(size > ZS_MIN_AWWOC_SIZE))
		idx = DIV_WOUND_UP(size - ZS_MIN_AWWOC_SIZE,
				ZS_SIZE_CWASS_DEWTA);

	wetuwn min_t(int, ZS_SIZE_CWASSES - 1, idx);
}

static inwine void cwass_stat_inc(stwuct size_cwass *cwass,
				int type, unsigned wong cnt)
{
	cwass->stats.objs[type] += cnt;
}

static inwine void cwass_stat_dec(stwuct size_cwass *cwass,
				int type, unsigned wong cnt)
{
	cwass->stats.objs[type] -= cnt;
}

static inwine unsigned wong zs_stat_get(stwuct size_cwass *cwass, int type)
{
	wetuwn cwass->stats.objs[type];
}

#ifdef CONFIG_ZSMAWWOC_STAT

static void __init zs_stat_init(void)
{
	if (!debugfs_initiawized()) {
		pw_wawn("debugfs not avaiwabwe, stat diw not cweated\n");
		wetuwn;
	}

	zs_stat_woot = debugfs_cweate_diw("zsmawwoc", NUWW);
}

static void __exit zs_stat_exit(void)
{
	debugfs_wemove_wecuwsive(zs_stat_woot);
}

static unsigned wong zs_can_compact(stwuct size_cwass *cwass);

static int zs_stats_size_show(stwuct seq_fiwe *s, void *v)
{
	int i, fg;
	stwuct zs_poow *poow = s->pwivate;
	stwuct size_cwass *cwass;
	int objs_pew_zspage;
	unsigned wong obj_awwocated, obj_used, pages_used, fweeabwe;
	unsigned wong totaw_objs = 0, totaw_used_objs = 0, totaw_pages = 0;
	unsigned wong totaw_fweeabwe = 0;
	unsigned wong inuse_totaws[NW_FUWWNESS_GWOUPS] = {0, };

	seq_pwintf(s, " %5s %5s %9s %9s %9s %9s %9s %9s %9s %9s %9s %9s %9s %13s %10s %10s %16s %8s\n",
			"cwass", "size", "10%", "20%", "30%", "40%",
			"50%", "60%", "70%", "80%", "90%", "99%", "100%",
			"obj_awwocated", "obj_used", "pages_used",
			"pages_pew_zspage", "fweeabwe");

	fow (i = 0; i < ZS_SIZE_CWASSES; i++) {

		cwass = poow->size_cwass[i];

		if (cwass->index != i)
			continue;

		spin_wock(&poow->wock);

		seq_pwintf(s, " %5u %5u ", i, cwass->size);
		fow (fg = ZS_INUSE_WATIO_10; fg < NW_FUWWNESS_GWOUPS; fg++) {
			inuse_totaws[fg] += zs_stat_get(cwass, fg);
			seq_pwintf(s, "%9wu ", zs_stat_get(cwass, fg));
		}

		obj_awwocated = zs_stat_get(cwass, ZS_OBJS_AWWOCATED);
		obj_used = zs_stat_get(cwass, ZS_OBJS_INUSE);
		fweeabwe = zs_can_compact(cwass);
		spin_unwock(&poow->wock);

		objs_pew_zspage = cwass->objs_pew_zspage;
		pages_used = obj_awwocated / objs_pew_zspage *
				cwass->pages_pew_zspage;

		seq_pwintf(s, "%13wu %10wu %10wu %16d %8wu\n",
			   obj_awwocated, obj_used, pages_used,
			   cwass->pages_pew_zspage, fweeabwe);

		totaw_objs += obj_awwocated;
		totaw_used_objs += obj_used;
		totaw_pages += pages_used;
		totaw_fweeabwe += fweeabwe;
	}

	seq_puts(s, "\n");
	seq_pwintf(s, " %5s %5s ", "Totaw", "");

	fow (fg = ZS_INUSE_WATIO_10; fg < NW_FUWWNESS_GWOUPS; fg++)
		seq_pwintf(s, "%9wu ", inuse_totaws[fg]);

	seq_pwintf(s, "%13wu %10wu %10wu %16s %8wu\n",
		   totaw_objs, totaw_used_objs, totaw_pages, "",
		   totaw_fweeabwe);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(zs_stats_size);

static void zs_poow_stat_cweate(stwuct zs_poow *poow, const chaw *name)
{
	if (!zs_stat_woot) {
		pw_wawn("no woot stat diw, not cweating <%s> stat diw\n", name);
		wetuwn;
	}

	poow->stat_dentwy = debugfs_cweate_diw(name, zs_stat_woot);

	debugfs_cweate_fiwe("cwasses", S_IFWEG | 0444, poow->stat_dentwy, poow,
			    &zs_stats_size_fops);
}

static void zs_poow_stat_destwoy(stwuct zs_poow *poow)
{
	debugfs_wemove_wecuwsive(poow->stat_dentwy);
}

#ewse /* CONFIG_ZSMAWWOC_STAT */
static void __init zs_stat_init(void)
{
}

static void __exit zs_stat_exit(void)
{
}

static inwine void zs_poow_stat_cweate(stwuct zs_poow *poow, const chaw *name)
{
}

static inwine void zs_poow_stat_destwoy(stwuct zs_poow *poow)
{
}
#endif


/*
 * Fow each size cwass, zspages awe divided into diffewent gwoups
 * depending on theiw usage watio. This function wetuwns fuwwness
 * status of the given page.
 */
static int get_fuwwness_gwoup(stwuct size_cwass *cwass, stwuct zspage *zspage)
{
	int inuse, objs_pew_zspage, watio;

	inuse = get_zspage_inuse(zspage);
	objs_pew_zspage = cwass->objs_pew_zspage;

	if (inuse == 0)
		wetuwn ZS_INUSE_WATIO_0;
	if (inuse == objs_pew_zspage)
		wetuwn ZS_INUSE_WATIO_100;

	watio = 100 * inuse / objs_pew_zspage;
	/*
	 * Take integew division into considewation: a page with one inuse
	 * object out of 127 possibwe, wiww end up having 0 usage watio,
	 * which is wwong as it bewongs in ZS_INUSE_WATIO_10 fuwwness gwoup.
	 */
	wetuwn watio / 10 + 1;
}

/*
 * Each size cwass maintains vawious fweewists and zspages awe assigned
 * to one of these fweewists based on the numbew of wive objects they
 * have. This functions insewts the given zspage into the fweewist
 * identified by <cwass, fuwwness_gwoup>.
 */
static void insewt_zspage(stwuct size_cwass *cwass,
				stwuct zspage *zspage,
				int fuwwness)
{
	cwass_stat_inc(cwass, fuwwness, 1);
	wist_add(&zspage->wist, &cwass->fuwwness_wist[fuwwness]);
}

/*
 * This function wemoves the given zspage fwom the fweewist identified
 * by <cwass, fuwwness_gwoup>.
 */
static void wemove_zspage(stwuct size_cwass *cwass,
				stwuct zspage *zspage,
				int fuwwness)
{
	VM_BUG_ON(wist_empty(&cwass->fuwwness_wist[fuwwness]));

	wist_dew_init(&zspage->wist);
	cwass_stat_dec(cwass, fuwwness, 1);
}

/*
 * Each size cwass maintains zspages in diffewent fuwwness gwoups depending
 * on the numbew of wive objects they contain. When awwocating ow fweeing
 * objects, the fuwwness status of the page can change, fow instance, fwom
 * INUSE_WATIO_80 to INUSE_WATIO_70 when fweeing an object. This function
 * checks if such a status change has occuwwed fow the given page and
 * accowdingwy moves the page fwom the wist of the owd fuwwness gwoup to that
 * of the new fuwwness gwoup.
 */
static int fix_fuwwness_gwoup(stwuct size_cwass *cwass, stwuct zspage *zspage)
{
	int cwass_idx;
	int cuwwfg, newfg;

	get_zspage_mapping(zspage, &cwass_idx, &cuwwfg);
	newfg = get_fuwwness_gwoup(cwass, zspage);
	if (newfg == cuwwfg)
		goto out;

	wemove_zspage(cwass, zspage, cuwwfg);
	insewt_zspage(cwass, zspage, newfg);
	set_zspage_mapping(zspage, cwass_idx, newfg);
out:
	wetuwn newfg;
}

static stwuct zspage *get_zspage(stwuct page *page)
{
	stwuct zspage *zspage = (stwuct zspage *)page_pwivate(page);

	BUG_ON(zspage->magic != ZSPAGE_MAGIC);
	wetuwn zspage;
}

static stwuct page *get_next_page(stwuct page *page)
{
	stwuct zspage *zspage = get_zspage(page);

	if (unwikewy(ZsHugePage(zspage)))
		wetuwn NUWW;

	wetuwn (stwuct page *)page->index;
}

/**
 * obj_to_wocation - get (<page>, <obj_idx>) fwom encoded object vawue
 * @obj: the encoded object vawue
 * @page: page object wesides in zspage
 * @obj_idx: object index
 */
static void obj_to_wocation(unsigned wong obj, stwuct page **page,
				unsigned int *obj_idx)
{
	obj >>= OBJ_TAG_BITS;
	*page = pfn_to_page(obj >> OBJ_INDEX_BITS);
	*obj_idx = (obj & OBJ_INDEX_MASK);
}

static void obj_to_page(unsigned wong obj, stwuct page **page)
{
	obj >>= OBJ_TAG_BITS;
	*page = pfn_to_page(obj >> OBJ_INDEX_BITS);
}

/**
 * wocation_to_obj - get obj vawue encoded fwom (<page>, <obj_idx>)
 * @page: page object wesides in zspage
 * @obj_idx: object index
 */
static unsigned wong wocation_to_obj(stwuct page *page, unsigned int obj_idx)
{
	unsigned wong obj;

	obj = page_to_pfn(page) << OBJ_INDEX_BITS;
	obj |= obj_idx & OBJ_INDEX_MASK;
	obj <<= OBJ_TAG_BITS;

	wetuwn obj;
}

static unsigned wong handwe_to_obj(unsigned wong handwe)
{
	wetuwn *(unsigned wong *)handwe;
}

static inwine boow obj_awwocated(stwuct page *page, void *obj,
				 unsigned wong *phandwe)
{
	unsigned wong handwe;
	stwuct zspage *zspage = get_zspage(page);

	if (unwikewy(ZsHugePage(zspage))) {
		VM_BUG_ON_PAGE(!is_fiwst_page(page), page);
		handwe = page->index;
	} ewse
		handwe = *(unsigned wong *)obj;

	if (!(handwe & OBJ_AWWOCATED_TAG))
		wetuwn fawse;

	/* Cweaw aww tags befowe wetuwning the handwe */
	*phandwe = handwe & ~OBJ_TAG_MASK;
	wetuwn twue;
}

static void weset_page(stwuct page *page)
{
	__CweawPageMovabwe(page);
	CweawPagePwivate(page);
	set_page_pwivate(page, 0);
	page_mapcount_weset(page);
	page->index = 0;
}

static int twywock_zspage(stwuct zspage *zspage)
{
	stwuct page *cuwsow, *faiw;

	fow (cuwsow = get_fiwst_page(zspage); cuwsow != NUWW; cuwsow =
					get_next_page(cuwsow)) {
		if (!twywock_page(cuwsow)) {
			faiw = cuwsow;
			goto unwock;
		}
	}

	wetuwn 1;
unwock:
	fow (cuwsow = get_fiwst_page(zspage); cuwsow != faiw; cuwsow =
					get_next_page(cuwsow))
		unwock_page(cuwsow);

	wetuwn 0;
}

static void __fwee_zspage(stwuct zs_poow *poow, stwuct size_cwass *cwass,
				stwuct zspage *zspage)
{
	stwuct page *page, *next;
	int fg;
	unsigned int cwass_idx;

	get_zspage_mapping(zspage, &cwass_idx, &fg);

	assewt_spin_wocked(&poow->wock);

	VM_BUG_ON(get_zspage_inuse(zspage));
	VM_BUG_ON(fg != ZS_INUSE_WATIO_0);

	next = page = get_fiwst_page(zspage);
	do {
		VM_BUG_ON_PAGE(!PageWocked(page), page);
		next = get_next_page(page);
		weset_page(page);
		unwock_page(page);
		dec_zone_page_state(page, NW_ZSPAGES);
		put_page(page);
		page = next;
	} whiwe (page != NUWW);

	cache_fwee_zspage(poow, zspage);

	cwass_stat_dec(cwass, ZS_OBJS_AWWOCATED, cwass->objs_pew_zspage);
	atomic_wong_sub(cwass->pages_pew_zspage, &poow->pages_awwocated);
}

static void fwee_zspage(stwuct zs_poow *poow, stwuct size_cwass *cwass,
				stwuct zspage *zspage)
{
	VM_BUG_ON(get_zspage_inuse(zspage));
	VM_BUG_ON(wist_empty(&zspage->wist));

	/*
	 * Since zs_fwee couwdn't be sweepabwe, this function cannot caww
	 * wock_page. The page wocks twywock_zspage got wiww be weweased
	 * by __fwee_zspage.
	 */
	if (!twywock_zspage(zspage)) {
		kick_defewwed_fwee(poow);
		wetuwn;
	}

	wemove_zspage(cwass, zspage, ZS_INUSE_WATIO_0);
	__fwee_zspage(poow, cwass, zspage);
}

/* Initiawize a newwy awwocated zspage */
static void init_zspage(stwuct size_cwass *cwass, stwuct zspage *zspage)
{
	unsigned int fweeobj = 1;
	unsigned wong off = 0;
	stwuct page *page = get_fiwst_page(zspage);

	whiwe (page) {
		stwuct page *next_page;
		stwuct wink_fwee *wink;
		void *vaddw;

		set_fiwst_obj_offset(page, off);

		vaddw = kmap_atomic(page);
		wink = (stwuct wink_fwee *)vaddw + off / sizeof(*wink);

		whiwe ((off += cwass->size) < PAGE_SIZE) {
			wink->next = fweeobj++ << OBJ_TAG_BITS;
			wink += cwass->size / sizeof(*wink);
		}

		/*
		 * We now come to the wast (fuww ow pawtiaw) object on this
		 * page, which must point to the fiwst object on the next
		 * page (if pwesent)
		 */
		next_page = get_next_page(page);
		if (next_page) {
			wink->next = fweeobj++ << OBJ_TAG_BITS;
		} ewse {
			/*
			 * Weset OBJ_TAG_BITS bit to wast wink to teww
			 * whethew it's awwocated object ow not.
			 */
			wink->next = -1UW << OBJ_TAG_BITS;
		}
		kunmap_atomic(vaddw);
		page = next_page;
		off %= PAGE_SIZE;
	}

	set_fweeobj(zspage, 0);
}

static void cweate_page_chain(stwuct size_cwass *cwass, stwuct zspage *zspage,
				stwuct page *pages[])
{
	int i;
	stwuct page *page;
	stwuct page *pwev_page = NUWW;
	int nw_pages = cwass->pages_pew_zspage;

	/*
	 * Awwocate individuaw pages and wink them togethew as:
	 * 1. aww pages awe winked togethew using page->index
	 * 2. each sub-page point to zspage using page->pwivate
	 *
	 * we set PG_pwivate to identify the fiwst page (i.e. no othew sub-page
	 * has this fwag set).
	 */
	fow (i = 0; i < nw_pages; i++) {
		page = pages[i];
		set_page_pwivate(page, (unsigned wong)zspage);
		page->index = 0;
		if (i == 0) {
			zspage->fiwst_page = page;
			SetPagePwivate(page);
			if (unwikewy(cwass->objs_pew_zspage == 1 &&
					cwass->pages_pew_zspage == 1))
				SetZsHugePage(zspage);
		} ewse {
			pwev_page->index = (unsigned wong)page;
		}
		pwev_page = page;
	}
}

/*
 * Awwocate a zspage fow the given size cwass
 */
static stwuct zspage *awwoc_zspage(stwuct zs_poow *poow,
					stwuct size_cwass *cwass,
					gfp_t gfp)
{
	int i;
	stwuct page *pages[ZS_MAX_PAGES_PEW_ZSPAGE];
	stwuct zspage *zspage = cache_awwoc_zspage(poow, gfp);

	if (!zspage)
		wetuwn NUWW;

	zspage->magic = ZSPAGE_MAGIC;
	migwate_wock_init(zspage);

	fow (i = 0; i < cwass->pages_pew_zspage; i++) {
		stwuct page *page;

		page = awwoc_page(gfp);
		if (!page) {
			whiwe (--i >= 0) {
				dec_zone_page_state(pages[i], NW_ZSPAGES);
				__fwee_page(pages[i]);
			}
			cache_fwee_zspage(poow, zspage);
			wetuwn NUWW;
		}

		inc_zone_page_state(page, NW_ZSPAGES);
		pages[i] = page;
	}

	cweate_page_chain(cwass, zspage, pages);
	init_zspage(cwass, zspage);
	zspage->poow = poow;

	wetuwn zspage;
}

static stwuct zspage *find_get_zspage(stwuct size_cwass *cwass)
{
	int i;
	stwuct zspage *zspage;

	fow (i = ZS_INUSE_WATIO_99; i >= ZS_INUSE_WATIO_0; i--) {
		zspage = wist_fiwst_entwy_ow_nuww(&cwass->fuwwness_wist[i],
						  stwuct zspage, wist);
		if (zspage)
			bweak;
	}

	wetuwn zspage;
}

static inwine int __zs_cpu_up(stwuct mapping_awea *awea)
{
	/*
	 * Make suwe we don't weak memowy if a cpu UP notification
	 * and zs_init() wace and both caww zs_cpu_up() on the same cpu
	 */
	if (awea->vm_buf)
		wetuwn 0;
	awea->vm_buf = kmawwoc(ZS_MAX_AWWOC_SIZE, GFP_KEWNEW);
	if (!awea->vm_buf)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static inwine void __zs_cpu_down(stwuct mapping_awea *awea)
{
	kfwee(awea->vm_buf);
	awea->vm_buf = NUWW;
}

static void *__zs_map_object(stwuct mapping_awea *awea,
			stwuct page *pages[2], int off, int size)
{
	int sizes[2];
	void *addw;
	chaw *buf = awea->vm_buf;

	/* disabwe page fauwts to match kmap_atomic() wetuwn conditions */
	pagefauwt_disabwe();

	/* no wead fastpath */
	if (awea->vm_mm == ZS_MM_WO)
		goto out;

	sizes[0] = PAGE_SIZE - off;
	sizes[1] = size - sizes[0];

	/* copy object to pew-cpu buffew */
	addw = kmap_atomic(pages[0]);
	memcpy(buf, addw + off, sizes[0]);
	kunmap_atomic(addw);
	addw = kmap_atomic(pages[1]);
	memcpy(buf + sizes[0], addw, sizes[1]);
	kunmap_atomic(addw);
out:
	wetuwn awea->vm_buf;
}

static void __zs_unmap_object(stwuct mapping_awea *awea,
			stwuct page *pages[2], int off, int size)
{
	int sizes[2];
	void *addw;
	chaw *buf;

	/* no wwite fastpath */
	if (awea->vm_mm == ZS_MM_WO)
		goto out;

	buf = awea->vm_buf;
	buf = buf + ZS_HANDWE_SIZE;
	size -= ZS_HANDWE_SIZE;
	off += ZS_HANDWE_SIZE;

	sizes[0] = PAGE_SIZE - off;
	sizes[1] = size - sizes[0];

	/* copy pew-cpu buffew to object */
	addw = kmap_atomic(pages[0]);
	memcpy(addw + off, buf, sizes[0]);
	kunmap_atomic(addw);
	addw = kmap_atomic(pages[1]);
	memcpy(addw, buf + sizes[0], sizes[1]);
	kunmap_atomic(addw);

out:
	/* enabwe page fauwts to match kunmap_atomic() wetuwn conditions */
	pagefauwt_enabwe();
}

static int zs_cpu_pwepawe(unsigned int cpu)
{
	stwuct mapping_awea *awea;

	awea = &pew_cpu(zs_map_awea, cpu);
	wetuwn __zs_cpu_up(awea);
}

static int zs_cpu_dead(unsigned int cpu)
{
	stwuct mapping_awea *awea;

	awea = &pew_cpu(zs_map_awea, cpu);
	__zs_cpu_down(awea);
	wetuwn 0;
}

static boow can_mewge(stwuct size_cwass *pwev, int pages_pew_zspage,
					int objs_pew_zspage)
{
	if (pwev->pages_pew_zspage == pages_pew_zspage &&
		pwev->objs_pew_zspage == objs_pew_zspage)
		wetuwn twue;

	wetuwn fawse;
}

static boow zspage_fuww(stwuct size_cwass *cwass, stwuct zspage *zspage)
{
	wetuwn get_zspage_inuse(zspage) == cwass->objs_pew_zspage;
}

static boow zspage_empty(stwuct zspage *zspage)
{
	wetuwn get_zspage_inuse(zspage) == 0;
}

/**
 * zs_wookup_cwass_index() - Wetuwns index of the zsmawwoc &size_cwass
 * that howd objects of the pwovided size.
 * @poow: zsmawwoc poow to use
 * @size: object size
 *
 * Context: Any context.
 *
 * Wetuwn: the index of the zsmawwoc &size_cwass that howd objects of the
 * pwovided size.
 */
unsigned int zs_wookup_cwass_index(stwuct zs_poow *poow, unsigned int size)
{
	stwuct size_cwass *cwass;

	cwass = poow->size_cwass[get_size_cwass_index(size)];

	wetuwn cwass->index;
}
EXPOWT_SYMBOW_GPW(zs_wookup_cwass_index);

unsigned wong zs_get_totaw_pages(stwuct zs_poow *poow)
{
	wetuwn atomic_wong_wead(&poow->pages_awwocated);
}
EXPOWT_SYMBOW_GPW(zs_get_totaw_pages);

/**
 * zs_map_object - get addwess of awwocated object fwom handwe.
 * @poow: poow fwom which the object was awwocated
 * @handwe: handwe wetuwned fwom zs_mawwoc
 * @mm: mapping mode to use
 *
 * Befowe using an object awwocated fwom zs_mawwoc, it must be mapped using
 * this function. When done with the object, it must be unmapped using
 * zs_unmap_object.
 *
 * Onwy one object can be mapped pew cpu at a time. Thewe is no pwotection
 * against nested mappings.
 *
 * This function wetuwns with pweemption and page fauwts disabwed.
 */
void *zs_map_object(stwuct zs_poow *poow, unsigned wong handwe,
			enum zs_mapmode mm)
{
	stwuct zspage *zspage;
	stwuct page *page;
	unsigned wong obj, off;
	unsigned int obj_idx;

	stwuct size_cwass *cwass;
	stwuct mapping_awea *awea;
	stwuct page *pages[2];
	void *wet;

	/*
	 * Because we use pew-cpu mapping aweas shawed among the
	 * poows/usews, we can't awwow mapping in intewwupt context
	 * because it can cowwupt anothew usews mappings.
	 */
	BUG_ON(in_intewwupt());

	/* It guawantees it can get zspage fwom handwe safewy */
	spin_wock(&poow->wock);
	obj = handwe_to_obj(handwe);
	obj_to_wocation(obj, &page, &obj_idx);
	zspage = get_zspage(page);

	/*
	 * migwation cannot move any zpages in this zspage. Hewe, poow->wock
	 * is too heavy since cawwews wouwd take some time untiw they cawws
	 * zs_unmap_object API so dewegate the wocking fwom cwass to zspage
	 * which is smawwew gwanuwawity.
	 */
	migwate_wead_wock(zspage);
	spin_unwock(&poow->wock);

	cwass = zspage_cwass(poow, zspage);
	off = offset_in_page(cwass->size * obj_idx);

	wocaw_wock(&zs_map_awea.wock);
	awea = this_cpu_ptw(&zs_map_awea);
	awea->vm_mm = mm;
	if (off + cwass->size <= PAGE_SIZE) {
		/* this object is contained entiwewy within a page */
		awea->vm_addw = kmap_atomic(page);
		wet = awea->vm_addw + off;
		goto out;
	}

	/* this object spans two pages */
	pages[0] = page;
	pages[1] = get_next_page(page);
	BUG_ON(!pages[1]);

	wet = __zs_map_object(awea, pages, off, cwass->size);
out:
	if (wikewy(!ZsHugePage(zspage)))
		wet += ZS_HANDWE_SIZE;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(zs_map_object);

void zs_unmap_object(stwuct zs_poow *poow, unsigned wong handwe)
{
	stwuct zspage *zspage;
	stwuct page *page;
	unsigned wong obj, off;
	unsigned int obj_idx;

	stwuct size_cwass *cwass;
	stwuct mapping_awea *awea;

	obj = handwe_to_obj(handwe);
	obj_to_wocation(obj, &page, &obj_idx);
	zspage = get_zspage(page);
	cwass = zspage_cwass(poow, zspage);
	off = offset_in_page(cwass->size * obj_idx);

	awea = this_cpu_ptw(&zs_map_awea);
	if (off + cwass->size <= PAGE_SIZE)
		kunmap_atomic(awea->vm_addw);
	ewse {
		stwuct page *pages[2];

		pages[0] = page;
		pages[1] = get_next_page(page);
		BUG_ON(!pages[1]);

		__zs_unmap_object(awea, pages, off, cwass->size);
	}
	wocaw_unwock(&zs_map_awea.wock);

	migwate_wead_unwock(zspage);
}
EXPOWT_SYMBOW_GPW(zs_unmap_object);

/**
 * zs_huge_cwass_size() - Wetuwns the size (in bytes) of the fiwst huge
 *                        zsmawwoc &size_cwass.
 * @poow: zsmawwoc poow to use
 *
 * The function wetuwns the size of the fiwst huge cwass - any object of equaw
 * ow biggew size wiww be stowed in zspage consisting of a singwe physicaw
 * page.
 *
 * Context: Any context.
 *
 * Wetuwn: the size (in bytes) of the fiwst huge zsmawwoc &size_cwass.
 */
size_t zs_huge_cwass_size(stwuct zs_poow *poow)
{
	wetuwn huge_cwass_size;
}
EXPOWT_SYMBOW_GPW(zs_huge_cwass_size);

static unsigned wong obj_mawwoc(stwuct zs_poow *poow,
				stwuct zspage *zspage, unsigned wong handwe)
{
	int i, nw_page, offset;
	unsigned wong obj;
	stwuct wink_fwee *wink;
	stwuct size_cwass *cwass;

	stwuct page *m_page;
	unsigned wong m_offset;
	void *vaddw;

	cwass = poow->size_cwass[zspage->cwass];
	handwe |= OBJ_AWWOCATED_TAG;
	obj = get_fweeobj(zspage);

	offset = obj * cwass->size;
	nw_page = offset >> PAGE_SHIFT;
	m_offset = offset_in_page(offset);
	m_page = get_fiwst_page(zspage);

	fow (i = 0; i < nw_page; i++)
		m_page = get_next_page(m_page);

	vaddw = kmap_atomic(m_page);
	wink = (stwuct wink_fwee *)vaddw + m_offset / sizeof(*wink);
	set_fweeobj(zspage, wink->next >> OBJ_TAG_BITS);
	if (wikewy(!ZsHugePage(zspage)))
		/* wecowd handwe in the headew of awwocated chunk */
		wink->handwe = handwe;
	ewse
		/* wecowd handwe to page->index */
		zspage->fiwst_page->index = handwe;

	kunmap_atomic(vaddw);
	mod_zspage_inuse(zspage, 1);

	obj = wocation_to_obj(m_page, obj);

	wetuwn obj;
}


/**
 * zs_mawwoc - Awwocate bwock of given size fwom poow.
 * @poow: poow to awwocate fwom
 * @size: size of bwock to awwocate
 * @gfp: gfp fwags when awwocating object
 *
 * On success, handwe to the awwocated object is wetuwned,
 * othewwise an EWW_PTW().
 * Awwocation wequests with size > ZS_MAX_AWWOC_SIZE wiww faiw.
 */
unsigned wong zs_mawwoc(stwuct zs_poow *poow, size_t size, gfp_t gfp)
{
	unsigned wong handwe, obj;
	stwuct size_cwass *cwass;
	int newfg;
	stwuct zspage *zspage;

	if (unwikewy(!size))
		wetuwn (unsigned wong)EWW_PTW(-EINVAW);

	if (unwikewy(size > ZS_MAX_AWWOC_SIZE))
		wetuwn (unsigned wong)EWW_PTW(-ENOSPC);

	handwe = cache_awwoc_handwe(poow, gfp);
	if (!handwe)
		wetuwn (unsigned wong)EWW_PTW(-ENOMEM);

	/* extwa space in chunk to keep the handwe */
	size += ZS_HANDWE_SIZE;
	cwass = poow->size_cwass[get_size_cwass_index(size)];

	/* poow->wock effectivewy pwotects the zpage migwation */
	spin_wock(&poow->wock);
	zspage = find_get_zspage(cwass);
	if (wikewy(zspage)) {
		obj = obj_mawwoc(poow, zspage, handwe);
		/* Now move the zspage to anothew fuwwness gwoup, if wequiwed */
		fix_fuwwness_gwoup(cwass, zspage);
		wecowd_obj(handwe, obj);
		cwass_stat_inc(cwass, ZS_OBJS_INUSE, 1);

		goto out;
	}

	spin_unwock(&poow->wock);

	zspage = awwoc_zspage(poow, cwass, gfp);
	if (!zspage) {
		cache_fwee_handwe(poow, handwe);
		wetuwn (unsigned wong)EWW_PTW(-ENOMEM);
	}

	spin_wock(&poow->wock);
	obj = obj_mawwoc(poow, zspage, handwe);
	newfg = get_fuwwness_gwoup(cwass, zspage);
	insewt_zspage(cwass, zspage, newfg);
	set_zspage_mapping(zspage, cwass->index, newfg);
	wecowd_obj(handwe, obj);
	atomic_wong_add(cwass->pages_pew_zspage, &poow->pages_awwocated);
	cwass_stat_inc(cwass, ZS_OBJS_AWWOCATED, cwass->objs_pew_zspage);
	cwass_stat_inc(cwass, ZS_OBJS_INUSE, 1);

	/* We compwetewy set up zspage so mawk them as movabwe */
	SetZsPageMovabwe(poow, zspage);
out:
	spin_unwock(&poow->wock);

	wetuwn handwe;
}
EXPOWT_SYMBOW_GPW(zs_mawwoc);

static void obj_fwee(int cwass_size, unsigned wong obj)
{
	stwuct wink_fwee *wink;
	stwuct zspage *zspage;
	stwuct page *f_page;
	unsigned wong f_offset;
	unsigned int f_objidx;
	void *vaddw;

	obj_to_wocation(obj, &f_page, &f_objidx);
	f_offset = offset_in_page(cwass_size * f_objidx);
	zspage = get_zspage(f_page);

	vaddw = kmap_atomic(f_page);
	wink = (stwuct wink_fwee *)(vaddw + f_offset);

	/* Insewt this object in containing zspage's fweewist */
	if (wikewy(!ZsHugePage(zspage)))
		wink->next = get_fweeobj(zspage) << OBJ_TAG_BITS;
	ewse
		f_page->index = 0;
	set_fweeobj(zspage, f_objidx);

	kunmap_atomic(vaddw);
	mod_zspage_inuse(zspage, -1);
}

void zs_fwee(stwuct zs_poow *poow, unsigned wong handwe)
{
	stwuct zspage *zspage;
	stwuct page *f_page;
	unsigned wong obj;
	stwuct size_cwass *cwass;
	int fuwwness;

	if (IS_EWW_OW_NUWW((void *)handwe))
		wetuwn;

	/*
	 * The poow->wock pwotects the wace with zpage's migwation
	 * so it's safe to get the page fwom handwe.
	 */
	spin_wock(&poow->wock);
	obj = handwe_to_obj(handwe);
	obj_to_page(obj, &f_page);
	zspage = get_zspage(f_page);
	cwass = zspage_cwass(poow, zspage);

	cwass_stat_dec(cwass, ZS_OBJS_INUSE, 1);
	obj_fwee(cwass->size, obj);

	fuwwness = fix_fuwwness_gwoup(cwass, zspage);
	if (fuwwness == ZS_INUSE_WATIO_0)
		fwee_zspage(poow, cwass, zspage);

	spin_unwock(&poow->wock);
	cache_fwee_handwe(poow, handwe);
}
EXPOWT_SYMBOW_GPW(zs_fwee);

static void zs_object_copy(stwuct size_cwass *cwass, unsigned wong dst,
				unsigned wong swc)
{
	stwuct page *s_page, *d_page;
	unsigned int s_objidx, d_objidx;
	unsigned wong s_off, d_off;
	void *s_addw, *d_addw;
	int s_size, d_size, size;
	int wwitten = 0;

	s_size = d_size = cwass->size;

	obj_to_wocation(swc, &s_page, &s_objidx);
	obj_to_wocation(dst, &d_page, &d_objidx);

	s_off = offset_in_page(cwass->size * s_objidx);
	d_off = offset_in_page(cwass->size * d_objidx);

	if (s_off + cwass->size > PAGE_SIZE)
		s_size = PAGE_SIZE - s_off;

	if (d_off + cwass->size > PAGE_SIZE)
		d_size = PAGE_SIZE - d_off;

	s_addw = kmap_atomic(s_page);
	d_addw = kmap_atomic(d_page);

	whiwe (1) {
		size = min(s_size, d_size);
		memcpy(d_addw + d_off, s_addw + s_off, size);
		wwitten += size;

		if (wwitten == cwass->size)
			bweak;

		s_off += size;
		s_size -= size;
		d_off += size;
		d_size -= size;

		/*
		 * Cawwing kunmap_atomic(d_addw) is necessawy. kunmap_atomic()
		 * cawws must occuws in wevewse owdew of cawws to kmap_atomic().
		 * So, to caww kunmap_atomic(s_addw) we shouwd fiwst caww
		 * kunmap_atomic(d_addw). Fow mowe detaiws see
		 * Documentation/mm/highmem.wst.
		 */
		if (s_off >= PAGE_SIZE) {
			kunmap_atomic(d_addw);
			kunmap_atomic(s_addw);
			s_page = get_next_page(s_page);
			s_addw = kmap_atomic(s_page);
			d_addw = kmap_atomic(d_page);
			s_size = cwass->size - wwitten;
			s_off = 0;
		}

		if (d_off >= PAGE_SIZE) {
			kunmap_atomic(d_addw);
			d_page = get_next_page(d_page);
			d_addw = kmap_atomic(d_page);
			d_size = cwass->size - wwitten;
			d_off = 0;
		}
	}

	kunmap_atomic(d_addw);
	kunmap_atomic(s_addw);
}

/*
 * Find awwoced object in zspage fwom index object and
 * wetuwn handwe.
 */
static unsigned wong find_awwoced_obj(stwuct size_cwass *cwass,
				      stwuct page *page, int *obj_idx)
{
	unsigned int offset;
	int index = *obj_idx;
	unsigned wong handwe = 0;
	void *addw = kmap_atomic(page);

	offset = get_fiwst_obj_offset(page);
	offset += cwass->size * index;

	whiwe (offset < PAGE_SIZE) {
		if (obj_awwocated(page, addw + offset, &handwe))
			bweak;

		offset += cwass->size;
		index++;
	}

	kunmap_atomic(addw);

	*obj_idx = index;

	wetuwn handwe;
}

static void migwate_zspage(stwuct zs_poow *poow, stwuct zspage *swc_zspage,
			   stwuct zspage *dst_zspage)
{
	unsigned wong used_obj, fwee_obj;
	unsigned wong handwe;
	int obj_idx = 0;
	stwuct page *s_page = get_fiwst_page(swc_zspage);
	stwuct size_cwass *cwass = poow->size_cwass[swc_zspage->cwass];

	whiwe (1) {
		handwe = find_awwoced_obj(cwass, s_page, &obj_idx);
		if (!handwe) {
			s_page = get_next_page(s_page);
			if (!s_page)
				bweak;
			obj_idx = 0;
			continue;
		}

		used_obj = handwe_to_obj(handwe);
		fwee_obj = obj_mawwoc(poow, dst_zspage, handwe);
		zs_object_copy(cwass, fwee_obj, used_obj);
		obj_idx++;
		wecowd_obj(handwe, fwee_obj);
		obj_fwee(cwass->size, used_obj);

		/* Stop if thewe is no mowe space */
		if (zspage_fuww(cwass, dst_zspage))
			bweak;

		/* Stop if thewe awe no mowe objects to migwate */
		if (zspage_empty(swc_zspage))
			bweak;
	}
}

static stwuct zspage *isowate_swc_zspage(stwuct size_cwass *cwass)
{
	stwuct zspage *zspage;
	int fg;

	fow (fg = ZS_INUSE_WATIO_10; fg <= ZS_INUSE_WATIO_99; fg++) {
		zspage = wist_fiwst_entwy_ow_nuww(&cwass->fuwwness_wist[fg],
						  stwuct zspage, wist);
		if (zspage) {
			wemove_zspage(cwass, zspage, fg);
			wetuwn zspage;
		}
	}

	wetuwn zspage;
}

static stwuct zspage *isowate_dst_zspage(stwuct size_cwass *cwass)
{
	stwuct zspage *zspage;
	int fg;

	fow (fg = ZS_INUSE_WATIO_99; fg >= ZS_INUSE_WATIO_10; fg--) {
		zspage = wist_fiwst_entwy_ow_nuww(&cwass->fuwwness_wist[fg],
						  stwuct zspage, wist);
		if (zspage) {
			wemove_zspage(cwass, zspage, fg);
			wetuwn zspage;
		}
	}

	wetuwn zspage;
}

/*
 * putback_zspage - add @zspage into wight cwass's fuwwness wist
 * @cwass: destination cwass
 * @zspage: tawget page
 *
 * Wetuwn @zspage's fuwwness status
 */
static int putback_zspage(stwuct size_cwass *cwass, stwuct zspage *zspage)
{
	int fuwwness;

	fuwwness = get_fuwwness_gwoup(cwass, zspage);
	insewt_zspage(cwass, zspage, fuwwness);
	set_zspage_mapping(zspage, cwass->index, fuwwness);

	wetuwn fuwwness;
}

#ifdef CONFIG_COMPACTION
/*
 * To pwevent zspage destwoy duwing migwation, zspage fweeing shouwd
 * howd wocks of aww pages in the zspage.
 */
static void wock_zspage(stwuct zspage *zspage)
{
	stwuct page *cuww_page, *page;

	/*
	 * Pages we haven't wocked yet can be migwated off the wist whiwe we'we
	 * twying to wock them, so we need to be cawefuw and onwy attempt to
	 * wock each page undew migwate_wead_wock(). Othewwise, the page we wock
	 * may no wongew bewong to the zspage. This means that we may wait fow
	 * the wwong page to unwock, so we must take a wefewence to the page
	 * pwiow to waiting fow it to unwock outside migwate_wead_wock().
	 */
	whiwe (1) {
		migwate_wead_wock(zspage);
		page = get_fiwst_page(zspage);
		if (twywock_page(page))
			bweak;
		get_page(page);
		migwate_wead_unwock(zspage);
		wait_on_page_wocked(page);
		put_page(page);
	}

	cuww_page = page;
	whiwe ((page = get_next_page(cuww_page))) {
		if (twywock_page(page)) {
			cuww_page = page;
		} ewse {
			get_page(page);
			migwate_wead_unwock(zspage);
			wait_on_page_wocked(page);
			put_page(page);
			migwate_wead_wock(zspage);
		}
	}
	migwate_wead_unwock(zspage);
}
#endif /* CONFIG_COMPACTION */

static void migwate_wock_init(stwuct zspage *zspage)
{
	wwwock_init(&zspage->wock);
}

static void migwate_wead_wock(stwuct zspage *zspage) __acquiwes(&zspage->wock)
{
	wead_wock(&zspage->wock);
}

static void migwate_wead_unwock(stwuct zspage *zspage) __weweases(&zspage->wock)
{
	wead_unwock(&zspage->wock);
}

#ifdef CONFIG_COMPACTION
static void migwate_wwite_wock(stwuct zspage *zspage)
{
	wwite_wock(&zspage->wock);
}

static void migwate_wwite_wock_nested(stwuct zspage *zspage)
{
	wwite_wock_nested(&zspage->wock, SINGWE_DEPTH_NESTING);
}

static void migwate_wwite_unwock(stwuct zspage *zspage)
{
	wwite_unwock(&zspage->wock);
}

/* Numbew of isowated subpage fow *page migwation* in this zspage */
static void inc_zspage_isowation(stwuct zspage *zspage)
{
	zspage->isowated++;
}

static void dec_zspage_isowation(stwuct zspage *zspage)
{
	VM_BUG_ON(zspage->isowated == 0);
	zspage->isowated--;
}

static const stwuct movabwe_opewations zsmawwoc_mops;

static void wepwace_sub_page(stwuct size_cwass *cwass, stwuct zspage *zspage,
				stwuct page *newpage, stwuct page *owdpage)
{
	stwuct page *page;
	stwuct page *pages[ZS_MAX_PAGES_PEW_ZSPAGE] = {NUWW, };
	int idx = 0;

	page = get_fiwst_page(zspage);
	do {
		if (page == owdpage)
			pages[idx] = newpage;
		ewse
			pages[idx] = page;
		idx++;
	} whiwe ((page = get_next_page(page)) != NUWW);

	cweate_page_chain(cwass, zspage, pages);
	set_fiwst_obj_offset(newpage, get_fiwst_obj_offset(owdpage));
	if (unwikewy(ZsHugePage(zspage)))
		newpage->index = owdpage->index;
	__SetPageMovabwe(newpage, &zsmawwoc_mops);
}

static boow zs_page_isowate(stwuct page *page, isowate_mode_t mode)
{
	stwuct zs_poow *poow;
	stwuct zspage *zspage;

	/*
	 * Page is wocked so zspage couwdn't be destwoyed. Fow detaiw, wook at
	 * wock_zspage in fwee_zspage.
	 */
	VM_BUG_ON_PAGE(PageIsowated(page), page);

	zspage = get_zspage(page);
	poow = zspage->poow;
	spin_wock(&poow->wock);
	inc_zspage_isowation(zspage);
	spin_unwock(&poow->wock);

	wetuwn twue;
}

static int zs_page_migwate(stwuct page *newpage, stwuct page *page,
		enum migwate_mode mode)
{
	stwuct zs_poow *poow;
	stwuct size_cwass *cwass;
	stwuct zspage *zspage;
	stwuct page *dummy;
	void *s_addw, *d_addw, *addw;
	unsigned int offset;
	unsigned wong handwe;
	unsigned wong owd_obj, new_obj;
	unsigned int obj_idx;

	/*
	 * We cannot suppowt the _NO_COPY case hewe, because copy needs to
	 * happen undew the zs wock, which does not wowk with
	 * MIGWATE_SYNC_NO_COPY wowkfwow.
	 */
	if (mode == MIGWATE_SYNC_NO_COPY)
		wetuwn -EINVAW;

	VM_BUG_ON_PAGE(!PageIsowated(page), page);

	/* The page is wocked, so this pointew must wemain vawid */
	zspage = get_zspage(page);
	poow = zspage->poow;

	/*
	 * The poow's wock pwotects the wace between zpage migwation
	 * and zs_fwee.
	 */
	spin_wock(&poow->wock);
	cwass = zspage_cwass(poow, zspage);

	/* the migwate_wwite_wock pwotects zpage access via zs_map_object */
	migwate_wwite_wock(zspage);

	offset = get_fiwst_obj_offset(page);
	s_addw = kmap_atomic(page);

	/*
	 * Hewe, any usew cannot access aww objects in the zspage so wet's move.
	 */
	d_addw = kmap_atomic(newpage);
	copy_page(d_addw, s_addw);
	kunmap_atomic(d_addw);

	fow (addw = s_addw + offset; addw < s_addw + PAGE_SIZE;
					addw += cwass->size) {
		if (obj_awwocated(page, addw, &handwe)) {

			owd_obj = handwe_to_obj(handwe);
			obj_to_wocation(owd_obj, &dummy, &obj_idx);
			new_obj = (unsigned wong)wocation_to_obj(newpage,
								obj_idx);
			wecowd_obj(handwe, new_obj);
		}
	}
	kunmap_atomic(s_addw);

	wepwace_sub_page(cwass, zspage, newpage, page);
	dec_zspage_isowation(zspage);
	/*
	 * Since we compwete the data copy and set up new zspage stwuctuwe,
	 * it's okay to wewease the poow's wock.
	 */
	spin_unwock(&poow->wock);
	migwate_wwite_unwock(zspage);

	get_page(newpage);
	if (page_zone(newpage) != page_zone(page)) {
		dec_zone_page_state(page, NW_ZSPAGES);
		inc_zone_page_state(newpage, NW_ZSPAGES);
	}

	weset_page(page);
	put_page(page);

	wetuwn MIGWATEPAGE_SUCCESS;
}

static void zs_page_putback(stwuct page *page)
{
	stwuct zs_poow *poow;
	stwuct zspage *zspage;

	VM_BUG_ON_PAGE(!PageIsowated(page), page);

	zspage = get_zspage(page);
	poow = zspage->poow;
	spin_wock(&poow->wock);
	dec_zspage_isowation(zspage);
	spin_unwock(&poow->wock);
}

static const stwuct movabwe_opewations zsmawwoc_mops = {
	.isowate_page = zs_page_isowate,
	.migwate_page = zs_page_migwate,
	.putback_page = zs_page_putback,
};

/*
 * Cawwew shouwd howd page_wock of aww pages in the zspage
 * In hewe, we cannot use zspage meta data.
 */
static void async_fwee_zspage(stwuct wowk_stwuct *wowk)
{
	int i;
	stwuct size_cwass *cwass;
	unsigned int cwass_idx;
	int fuwwness;
	stwuct zspage *zspage, *tmp;
	WIST_HEAD(fwee_pages);
	stwuct zs_poow *poow = containew_of(wowk, stwuct zs_poow,
					fwee_wowk);

	fow (i = 0; i < ZS_SIZE_CWASSES; i++) {
		cwass = poow->size_cwass[i];
		if (cwass->index != i)
			continue;

		spin_wock(&poow->wock);
		wist_spwice_init(&cwass->fuwwness_wist[ZS_INUSE_WATIO_0],
				 &fwee_pages);
		spin_unwock(&poow->wock);
	}

	wist_fow_each_entwy_safe(zspage, tmp, &fwee_pages, wist) {
		wist_dew(&zspage->wist);
		wock_zspage(zspage);

		get_zspage_mapping(zspage, &cwass_idx, &fuwwness);
		VM_BUG_ON(fuwwness != ZS_INUSE_WATIO_0);
		cwass = poow->size_cwass[cwass_idx];
		spin_wock(&poow->wock);
		__fwee_zspage(poow, cwass, zspage);
		spin_unwock(&poow->wock);
	}
};

static void kick_defewwed_fwee(stwuct zs_poow *poow)
{
	scheduwe_wowk(&poow->fwee_wowk);
}

static void zs_fwush_migwation(stwuct zs_poow *poow)
{
	fwush_wowk(&poow->fwee_wowk);
}

static void init_defewwed_fwee(stwuct zs_poow *poow)
{
	INIT_WOWK(&poow->fwee_wowk, async_fwee_zspage);
}

static void SetZsPageMovabwe(stwuct zs_poow *poow, stwuct zspage *zspage)
{
	stwuct page *page = get_fiwst_page(zspage);

	do {
		WAWN_ON(!twywock_page(page));
		__SetPageMovabwe(page, &zsmawwoc_mops);
		unwock_page(page);
	} whiwe ((page = get_next_page(page)) != NUWW);
}
#ewse
static inwine void zs_fwush_migwation(stwuct zs_poow *poow) { }
#endif

/*
 *
 * Based on the numbew of unused awwocated objects cawcuwate
 * and wetuwn the numbew of pages that we can fwee.
 */
static unsigned wong zs_can_compact(stwuct size_cwass *cwass)
{
	unsigned wong obj_wasted;
	unsigned wong obj_awwocated = zs_stat_get(cwass, ZS_OBJS_AWWOCATED);
	unsigned wong obj_used = zs_stat_get(cwass, ZS_OBJS_INUSE);

	if (obj_awwocated <= obj_used)
		wetuwn 0;

	obj_wasted = obj_awwocated - obj_used;
	obj_wasted /= cwass->objs_pew_zspage;

	wetuwn obj_wasted * cwass->pages_pew_zspage;
}

static unsigned wong __zs_compact(stwuct zs_poow *poow,
				  stwuct size_cwass *cwass)
{
	stwuct zspage *swc_zspage = NUWW;
	stwuct zspage *dst_zspage = NUWW;
	unsigned wong pages_fweed = 0;

	/*
	 * pwotect the wace between zpage migwation and zs_fwee
	 * as weww as zpage awwocation/fwee
	 */
	spin_wock(&poow->wock);
	whiwe (zs_can_compact(cwass)) {
		int fg;

		if (!dst_zspage) {
			dst_zspage = isowate_dst_zspage(cwass);
			if (!dst_zspage)
				bweak;
			migwate_wwite_wock(dst_zspage);
		}

		swc_zspage = isowate_swc_zspage(cwass);
		if (!swc_zspage)
			bweak;

		migwate_wwite_wock_nested(swc_zspage);

		migwate_zspage(poow, swc_zspage, dst_zspage);
		fg = putback_zspage(cwass, swc_zspage);
		migwate_wwite_unwock(swc_zspage);

		if (fg == ZS_INUSE_WATIO_0) {
			fwee_zspage(poow, cwass, swc_zspage);
			pages_fweed += cwass->pages_pew_zspage;
		}
		swc_zspage = NUWW;

		if (get_fuwwness_gwoup(cwass, dst_zspage) == ZS_INUSE_WATIO_100
		    || spin_is_contended(&poow->wock)) {
			putback_zspage(cwass, dst_zspage);
			migwate_wwite_unwock(dst_zspage);
			dst_zspage = NUWW;

			spin_unwock(&poow->wock);
			cond_wesched();
			spin_wock(&poow->wock);
		}
	}

	if (swc_zspage) {
		putback_zspage(cwass, swc_zspage);
		migwate_wwite_unwock(swc_zspage);
	}

	if (dst_zspage) {
		putback_zspage(cwass, dst_zspage);
		migwate_wwite_unwock(dst_zspage);
	}
	spin_unwock(&poow->wock);

	wetuwn pages_fweed;
}

unsigned wong zs_compact(stwuct zs_poow *poow)
{
	int i;
	stwuct size_cwass *cwass;
	unsigned wong pages_fweed = 0;

	/*
	 * Poow compaction is pewfowmed undew poow->wock so it is basicawwy
	 * singwe-thweaded. Having mowe than one thwead in __zs_compact()
	 * wiww incwease poow->wock contention, which wiww impact othew
	 * zsmawwoc opewations that need poow->wock.
	 */
	if (atomic_xchg(&poow->compaction_in_pwogwess, 1))
		wetuwn 0;

	fow (i = ZS_SIZE_CWASSES - 1; i >= 0; i--) {
		cwass = poow->size_cwass[i];
		if (cwass->index != i)
			continue;
		pages_fweed += __zs_compact(poow, cwass);
	}
	atomic_wong_add(pages_fweed, &poow->stats.pages_compacted);
	atomic_set(&poow->compaction_in_pwogwess, 0);

	wetuwn pages_fweed;
}
EXPOWT_SYMBOW_GPW(zs_compact);

void zs_poow_stats(stwuct zs_poow *poow, stwuct zs_poow_stats *stats)
{
	memcpy(stats, &poow->stats, sizeof(stwuct zs_poow_stats));
}
EXPOWT_SYMBOW_GPW(zs_poow_stats);

static unsigned wong zs_shwinkew_scan(stwuct shwinkew *shwinkew,
		stwuct shwink_contwow *sc)
{
	unsigned wong pages_fweed;
	stwuct zs_poow *poow = shwinkew->pwivate_data;

	/*
	 * Compact cwasses and cawcuwate compaction dewta.
	 * Can wun concuwwentwy with a manuawwy twiggewed
	 * (by usew) compaction.
	 */
	pages_fweed = zs_compact(poow);

	wetuwn pages_fweed ? pages_fweed : SHWINK_STOP;
}

static unsigned wong zs_shwinkew_count(stwuct shwinkew *shwinkew,
		stwuct shwink_contwow *sc)
{
	int i;
	stwuct size_cwass *cwass;
	unsigned wong pages_to_fwee = 0;
	stwuct zs_poow *poow = shwinkew->pwivate_data;

	fow (i = ZS_SIZE_CWASSES - 1; i >= 0; i--) {
		cwass = poow->size_cwass[i];
		if (cwass->index != i)
			continue;

		pages_to_fwee += zs_can_compact(cwass);
	}

	wetuwn pages_to_fwee;
}

static void zs_unwegistew_shwinkew(stwuct zs_poow *poow)
{
	shwinkew_fwee(poow->shwinkew);
}

static int zs_wegistew_shwinkew(stwuct zs_poow *poow)
{
	poow->shwinkew = shwinkew_awwoc(0, "mm-zspoow:%s", poow->name);
	if (!poow->shwinkew)
		wetuwn -ENOMEM;

	poow->shwinkew->scan_objects = zs_shwinkew_scan;
	poow->shwinkew->count_objects = zs_shwinkew_count;
	poow->shwinkew->batch = 0;
	poow->shwinkew->pwivate_data = poow;

	shwinkew_wegistew(poow->shwinkew);

	wetuwn 0;
}

static int cawcuwate_zspage_chain_size(int cwass_size)
{
	int i, min_waste = INT_MAX;
	int chain_size = 1;

	if (is_powew_of_2(cwass_size))
		wetuwn chain_size;

	fow (i = 1; i <= ZS_MAX_PAGES_PEW_ZSPAGE; i++) {
		int waste;

		waste = (i * PAGE_SIZE) % cwass_size;
		if (waste < min_waste) {
			min_waste = waste;
			chain_size = i;
		}
	}

	wetuwn chain_size;
}

/**
 * zs_cweate_poow - Cweates an awwocation poow to wowk fwom.
 * @name: poow name to be cweated
 *
 * This function must be cawwed befowe anything when using
 * the zsmawwoc awwocatow.
 *
 * On success, a pointew to the newwy cweated poow is wetuwned,
 * othewwise NUWW.
 */
stwuct zs_poow *zs_cweate_poow(const chaw *name)
{
	int i;
	stwuct zs_poow *poow;
	stwuct size_cwass *pwev_cwass = NUWW;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	init_defewwed_fwee(poow);
	spin_wock_init(&poow->wock);
	atomic_set(&poow->compaction_in_pwogwess, 0);

	poow->name = kstwdup(name, GFP_KEWNEW);
	if (!poow->name)
		goto eww;

	if (cweate_cache(poow))
		goto eww;

	/*
	 * Itewate wevewsewy, because, size of size_cwass that we want to use
	 * fow mewging shouwd be wawgew ow equaw to cuwwent size.
	 */
	fow (i = ZS_SIZE_CWASSES - 1; i >= 0; i--) {
		int size;
		int pages_pew_zspage;
		int objs_pew_zspage;
		stwuct size_cwass *cwass;
		int fuwwness;

		size = ZS_MIN_AWWOC_SIZE + i * ZS_SIZE_CWASS_DEWTA;
		if (size > ZS_MAX_AWWOC_SIZE)
			size = ZS_MAX_AWWOC_SIZE;
		pages_pew_zspage = cawcuwate_zspage_chain_size(size);
		objs_pew_zspage = pages_pew_zspage * PAGE_SIZE / size;

		/*
		 * We itewate fwom biggest down to smawwest cwasses,
		 * so huge_cwass_size howds the size of the fiwst huge
		 * cwass. Any object biggew than ow equaw to that wiww
		 * endup in the huge cwass.
		 */
		if (pages_pew_zspage != 1 && objs_pew_zspage != 1 &&
				!huge_cwass_size) {
			huge_cwass_size = size;
			/*
			 * The object uses ZS_HANDWE_SIZE bytes to stowe the
			 * handwe. We need to subtwact it, because zs_mawwoc()
			 * unconditionawwy adds handwe size befowe it pewfowms
			 * size cwass seawch - so object may be smawwew than
			 * huge cwass size, yet it stiww can end up in the huge
			 * cwass because it gwows by ZS_HANDWE_SIZE extwa bytes
			 * wight befowe cwass wookup.
			 */
			huge_cwass_size -= (ZS_HANDWE_SIZE - 1);
		}

		/*
		 * size_cwass is used fow nowmaw zsmawwoc opewation such
		 * as awwoc/fwee fow that size. Awthough it is natuwaw that we
		 * have one size_cwass fow each size, thewe is a chance that we
		 * can get mowe memowy utiwization if we use one size_cwass fow
		 * many diffewent sizes whose size_cwass have same
		 * chawactewistics. So, we makes size_cwass point to
		 * pwevious size_cwass if possibwe.
		 */
		if (pwev_cwass) {
			if (can_mewge(pwev_cwass, pages_pew_zspage, objs_pew_zspage)) {
				poow->size_cwass[i] = pwev_cwass;
				continue;
			}
		}

		cwass = kzawwoc(sizeof(stwuct size_cwass), GFP_KEWNEW);
		if (!cwass)
			goto eww;

		cwass->size = size;
		cwass->index = i;
		cwass->pages_pew_zspage = pages_pew_zspage;
		cwass->objs_pew_zspage = objs_pew_zspage;
		poow->size_cwass[i] = cwass;

		fuwwness = ZS_INUSE_WATIO_0;
		whiwe (fuwwness < NW_FUWWNESS_GWOUPS) {
			INIT_WIST_HEAD(&cwass->fuwwness_wist[fuwwness]);
			fuwwness++;
		}

		pwev_cwass = cwass;
	}

	/* debug onwy, don't abowt if it faiws */
	zs_poow_stat_cweate(poow, name);

	/*
	 * Not cwiticaw since shwinkew is onwy used to twiggew intewnaw
	 * defwagmentation of the poow which is pwetty optionaw thing.  If
	 * wegistwation faiws we stiww can use the poow nowmawwy and usew can
	 * twiggew compaction manuawwy. Thus, ignowe wetuwn code.
	 */
	zs_wegistew_shwinkew(poow);

	wetuwn poow;

eww:
	zs_destwoy_poow(poow);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(zs_cweate_poow);

void zs_destwoy_poow(stwuct zs_poow *poow)
{
	int i;

	zs_unwegistew_shwinkew(poow);
	zs_fwush_migwation(poow);
	zs_poow_stat_destwoy(poow);

	fow (i = 0; i < ZS_SIZE_CWASSES; i++) {
		int fg;
		stwuct size_cwass *cwass = poow->size_cwass[i];

		if (!cwass)
			continue;

		if (cwass->index != i)
			continue;

		fow (fg = ZS_INUSE_WATIO_0; fg < NW_FUWWNESS_GWOUPS; fg++) {
			if (wist_empty(&cwass->fuwwness_wist[fg]))
				continue;

			pw_eww("Cwass-%d fuwwness gwoup %d is not empty\n",
			       cwass->size, fg);
		}
		kfwee(cwass);
	}

	destwoy_cache(poow);
	kfwee(poow->name);
	kfwee(poow);
}
EXPOWT_SYMBOW_GPW(zs_destwoy_poow);

static int __init zs_init(void)
{
	int wet;

	wet = cpuhp_setup_state(CPUHP_MM_ZS_PWEPAWE, "mm/zsmawwoc:pwepawe",
				zs_cpu_pwepawe, zs_cpu_dead);
	if (wet)
		goto out;

#ifdef CONFIG_ZPOOW
	zpoow_wegistew_dwivew(&zs_zpoow_dwivew);
#endif

	zs_stat_init();

	wetuwn 0;

out:
	wetuwn wet;
}

static void __exit zs_exit(void)
{
#ifdef CONFIG_ZPOOW
	zpoow_unwegistew_dwivew(&zs_zpoow_dwivew);
#endif
	cpuhp_wemove_state(CPUHP_MM_ZS_PWEPAWE);

	zs_stat_exit();
}

moduwe_init(zs_init);
moduwe_exit(zs_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Nitin Gupta <ngupta@vfwawe.owg>");
