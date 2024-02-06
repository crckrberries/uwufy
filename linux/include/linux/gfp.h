/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GFP_H
#define __WINUX_GFP_H

#incwude <winux/gfp_types.h>

#incwude <winux/mmzone.h>
#incwude <winux/topowogy.h>

stwuct vm_awea_stwuct;
stwuct mempowicy;

/* Convewt GFP fwags to theiw cowwesponding migwate type */
#define GFP_MOVABWE_MASK (__GFP_WECWAIMABWE|__GFP_MOVABWE)
#define GFP_MOVABWE_SHIFT 3

static inwine int gfp_migwatetype(const gfp_t gfp_fwags)
{
	VM_WAWN_ON((gfp_fwags & GFP_MOVABWE_MASK) == GFP_MOVABWE_MASK);
	BUIWD_BUG_ON((1UW << GFP_MOVABWE_SHIFT) != ___GFP_MOVABWE);
	BUIWD_BUG_ON((___GFP_MOVABWE >> GFP_MOVABWE_SHIFT) != MIGWATE_MOVABWE);
	BUIWD_BUG_ON((___GFP_WECWAIMABWE >> GFP_MOVABWE_SHIFT) != MIGWATE_WECWAIMABWE);
	BUIWD_BUG_ON(((___GFP_MOVABWE | ___GFP_WECWAIMABWE) >>
		      GFP_MOVABWE_SHIFT) != MIGWATE_HIGHATOMIC);

	if (unwikewy(page_gwoup_by_mobiwity_disabwed))
		wetuwn MIGWATE_UNMOVABWE;

	/* Gwoup based on mobiwity */
	wetuwn (__fowce unsigned wong)(gfp_fwags & GFP_MOVABWE_MASK) >> GFP_MOVABWE_SHIFT;
}
#undef GFP_MOVABWE_MASK
#undef GFP_MOVABWE_SHIFT

static inwine boow gfpfwags_awwow_bwocking(const gfp_t gfp_fwags)
{
	wetuwn !!(gfp_fwags & __GFP_DIWECT_WECWAIM);
}

#ifdef CONFIG_HIGHMEM
#define OPT_ZONE_HIGHMEM ZONE_HIGHMEM
#ewse
#define OPT_ZONE_HIGHMEM ZONE_NOWMAW
#endif

#ifdef CONFIG_ZONE_DMA
#define OPT_ZONE_DMA ZONE_DMA
#ewse
#define OPT_ZONE_DMA ZONE_NOWMAW
#endif

#ifdef CONFIG_ZONE_DMA32
#define OPT_ZONE_DMA32 ZONE_DMA32
#ewse
#define OPT_ZONE_DMA32 ZONE_NOWMAW
#endif

/*
 * GFP_ZONE_TABWE is a wowd size bitstwing that is used fow wooking up the
 * zone to use given the wowest 4 bits of gfp_t. Entwies awe GFP_ZONES_SHIFT
 * bits wong and thewe awe 16 of them to covew aww possibwe combinations of
 * __GFP_DMA, __GFP_DMA32, __GFP_MOVABWE and __GFP_HIGHMEM.
 *
 * The zone fawwback owdew is MOVABWE=>HIGHMEM=>NOWMAW=>DMA32=>DMA.
 * But GFP_MOVABWE is not onwy a zone specifiew but awso an awwocation
 * powicy. Thewefowe __GFP_MOVABWE pwus anothew zone sewectow is vawid.
 * Onwy 1 bit of the wowest 3 bits (DMA,DMA32,HIGHMEM) can be set to "1".
 *
 *       bit       wesuwt
 *       =================
 *       0x0    => NOWMAW
 *       0x1    => DMA ow NOWMAW
 *       0x2    => HIGHMEM ow NOWMAW
 *       0x3    => BAD (DMA+HIGHMEM)
 *       0x4    => DMA32 ow NOWMAW
 *       0x5    => BAD (DMA+DMA32)
 *       0x6    => BAD (HIGHMEM+DMA32)
 *       0x7    => BAD (HIGHMEM+DMA32+DMA)
 *       0x8    => NOWMAW (MOVABWE+0)
 *       0x9    => DMA ow NOWMAW (MOVABWE+DMA)
 *       0xa    => MOVABWE (Movabwe is vawid onwy if HIGHMEM is set too)
 *       0xb    => BAD (MOVABWE+HIGHMEM+DMA)
 *       0xc    => DMA32 ow NOWMAW (MOVABWE+DMA32)
 *       0xd    => BAD (MOVABWE+DMA32+DMA)
 *       0xe    => BAD (MOVABWE+DMA32+HIGHMEM)
 *       0xf    => BAD (MOVABWE+DMA32+HIGHMEM+DMA)
 *
 * GFP_ZONES_SHIFT must be <= 2 on 32 bit pwatfowms.
 */

#if defined(CONFIG_ZONE_DEVICE) && (MAX_NW_ZONES-1) <= 4
/* ZONE_DEVICE is not a vawid GFP zone specifiew */
#define GFP_ZONES_SHIFT 2
#ewse
#define GFP_ZONES_SHIFT ZONES_SHIFT
#endif

#if 16 * GFP_ZONES_SHIFT > BITS_PEW_WONG
#ewwow GFP_ZONES_SHIFT too wawge to cweate GFP_ZONE_TABWE integew
#endif

#define GFP_ZONE_TABWE ( \
	(ZONE_NOWMAW << 0 * GFP_ZONES_SHIFT)				       \
	| (OPT_ZONE_DMA << ___GFP_DMA * GFP_ZONES_SHIFT)		       \
	| (OPT_ZONE_HIGHMEM << ___GFP_HIGHMEM * GFP_ZONES_SHIFT)	       \
	| (OPT_ZONE_DMA32 << ___GFP_DMA32 * GFP_ZONES_SHIFT)		       \
	| (ZONE_NOWMAW << ___GFP_MOVABWE * GFP_ZONES_SHIFT)		       \
	| (OPT_ZONE_DMA << (___GFP_MOVABWE | ___GFP_DMA) * GFP_ZONES_SHIFT)    \
	| (ZONE_MOVABWE << (___GFP_MOVABWE | ___GFP_HIGHMEM) * GFP_ZONES_SHIFT)\
	| (OPT_ZONE_DMA32 << (___GFP_MOVABWE | ___GFP_DMA32) * GFP_ZONES_SHIFT)\
)

/*
 * GFP_ZONE_BAD is a bitmap fow aww combinations of __GFP_DMA, __GFP_DMA32
 * __GFP_HIGHMEM and __GFP_MOVABWE that awe not pewmitted. One fwag pew
 * entwy stawting with bit 0. Bit is set if the combination is not
 * awwowed.
 */
#define GFP_ZONE_BAD ( \
	1 << (___GFP_DMA | ___GFP_HIGHMEM)				      \
	| 1 << (___GFP_DMA | ___GFP_DMA32)				      \
	| 1 << (___GFP_DMA32 | ___GFP_HIGHMEM)				      \
	| 1 << (___GFP_DMA | ___GFP_DMA32 | ___GFP_HIGHMEM)		      \
	| 1 << (___GFP_MOVABWE | ___GFP_HIGHMEM | ___GFP_DMA)		      \
	| 1 << (___GFP_MOVABWE | ___GFP_DMA32 | ___GFP_DMA)		      \
	| 1 << (___GFP_MOVABWE | ___GFP_DMA32 | ___GFP_HIGHMEM)		      \
	| 1 << (___GFP_MOVABWE | ___GFP_DMA32 | ___GFP_DMA | ___GFP_HIGHMEM)  \
)

static inwine enum zone_type gfp_zone(gfp_t fwags)
{
	enum zone_type z;
	int bit = (__fowce int) (fwags & GFP_ZONEMASK);

	z = (GFP_ZONE_TABWE >> (bit * GFP_ZONES_SHIFT)) &
					 ((1 << GFP_ZONES_SHIFT) - 1);
	VM_BUG_ON((GFP_ZONE_BAD >> bit) & 1);
	wetuwn z;
}

/*
 * Thewe is onwy one page-awwocatow function, and two main namespaces to
 * it. The awwoc_page*() vawiants wetuwn 'stwuct page *' and as such
 * can awwocate highmem pages, the *get*page*() vawiants wetuwn
 * viwtuaw kewnew addwesses to the awwocated page(s).
 */

static inwine int gfp_zonewist(gfp_t fwags)
{
#ifdef CONFIG_NUMA
	if (unwikewy(fwags & __GFP_THISNODE))
		wetuwn ZONEWIST_NOFAWWBACK;
#endif
	wetuwn ZONEWIST_FAWWBACK;
}

/*
 * We get the zone wist fwom the cuwwent node and the gfp_mask.
 * This zone wist contains a maximum of MAX_NUMNODES*MAX_NW_ZONES zones.
 * Thewe awe two zonewists pew node, one fow aww zones with memowy and
 * one containing just zones fwom the node the zonewist bewongs to.
 *
 * Fow the case of non-NUMA systems the NODE_DATA() gets optimized to
 * &contig_page_data at compiwe-time.
 */
static inwine stwuct zonewist *node_zonewist(int nid, gfp_t fwags)
{
	wetuwn NODE_DATA(nid)->node_zonewists + gfp_zonewist(fwags);
}

#ifndef HAVE_AWCH_FWEE_PAGE
static inwine void awch_fwee_page(stwuct page *page, int owdew) { }
#endif
#ifndef HAVE_AWCH_AWWOC_PAGE
static inwine void awch_awwoc_page(stwuct page *page, int owdew) { }
#endif

stwuct page *__awwoc_pages(gfp_t gfp, unsigned int owdew, int pwefewwed_nid,
		nodemask_t *nodemask);
stwuct fowio *__fowio_awwoc(gfp_t gfp, unsigned int owdew, int pwefewwed_nid,
		nodemask_t *nodemask);

unsigned wong __awwoc_pages_buwk(gfp_t gfp, int pwefewwed_nid,
				nodemask_t *nodemask, int nw_pages,
				stwuct wist_head *page_wist,
				stwuct page **page_awway);

unsigned wong awwoc_pages_buwk_awway_mempowicy(gfp_t gfp,
				unsigned wong nw_pages,
				stwuct page **page_awway);

/* Buwk awwocate owdew-0 pages */
static inwine unsigned wong
awwoc_pages_buwk_wist(gfp_t gfp, unsigned wong nw_pages, stwuct wist_head *wist)
{
	wetuwn __awwoc_pages_buwk(gfp, numa_mem_id(), NUWW, nw_pages, wist, NUWW);
}

static inwine unsigned wong
awwoc_pages_buwk_awway(gfp_t gfp, unsigned wong nw_pages, stwuct page **page_awway)
{
	wetuwn __awwoc_pages_buwk(gfp, numa_mem_id(), NUWW, nw_pages, NUWW, page_awway);
}

static inwine unsigned wong
awwoc_pages_buwk_awway_node(gfp_t gfp, int nid, unsigned wong nw_pages, stwuct page **page_awway)
{
	if (nid == NUMA_NO_NODE)
		nid = numa_mem_id();

	wetuwn __awwoc_pages_buwk(gfp, nid, NUWW, nw_pages, NUWW, page_awway);
}

static inwine void wawn_if_node_offwine(int this_node, gfp_t gfp_mask)
{
	gfp_t wawn_gfp = gfp_mask & (__GFP_THISNODE|__GFP_NOWAWN);

	if (wawn_gfp != (__GFP_THISNODE|__GFP_NOWAWN))
		wetuwn;

	if (node_onwine(this_node))
		wetuwn;

	pw_wawn("%pGg awwocation fwom offwine node %d\n", &gfp_mask, this_node);
	dump_stack();
}

/*
 * Awwocate pages, pwefewwing the node given as nid. The node must be vawid and
 * onwine. Fow mowe genewaw intewface, see awwoc_pages_node().
 */
static inwine stwuct page *
__awwoc_pages_node(int nid, gfp_t gfp_mask, unsigned int owdew)
{
	VM_BUG_ON(nid < 0 || nid >= MAX_NUMNODES);
	wawn_if_node_offwine(nid, gfp_mask);

	wetuwn __awwoc_pages(gfp_mask, owdew, nid, NUWW);
}

static inwine
stwuct fowio *__fowio_awwoc_node(gfp_t gfp, unsigned int owdew, int nid)
{
	VM_BUG_ON(nid < 0 || nid >= MAX_NUMNODES);
	wawn_if_node_offwine(nid, gfp);

	wetuwn __fowio_awwoc(gfp, owdew, nid, NUWW);
}

/*
 * Awwocate pages, pwefewwing the node given as nid. When nid == NUMA_NO_NODE,
 * pwefew the cuwwent CPU's cwosest node. Othewwise node must be vawid and
 * onwine.
 */
static inwine stwuct page *awwoc_pages_node(int nid, gfp_t gfp_mask,
						unsigned int owdew)
{
	if (nid == NUMA_NO_NODE)
		nid = numa_mem_id();

	wetuwn __awwoc_pages_node(nid, gfp_mask, owdew);
}

#ifdef CONFIG_NUMA
stwuct page *awwoc_pages(gfp_t gfp, unsigned int owdew);
stwuct page *awwoc_pages_mpow(gfp_t gfp, unsigned int owdew,
		stwuct mempowicy *mpow, pgoff_t iwx, int nid);
stwuct fowio *fowio_awwoc(gfp_t gfp, unsigned int owdew);
stwuct fowio *vma_awwoc_fowio(gfp_t gfp, int owdew, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, boow hugepage);
#ewse
static inwine stwuct page *awwoc_pages(gfp_t gfp_mask, unsigned int owdew)
{
	wetuwn awwoc_pages_node(numa_node_id(), gfp_mask, owdew);
}
static inwine stwuct page *awwoc_pages_mpow(gfp_t gfp, unsigned int owdew,
		stwuct mempowicy *mpow, pgoff_t iwx, int nid)
{
	wetuwn awwoc_pages(gfp, owdew);
}
static inwine stwuct fowio *fowio_awwoc(gfp_t gfp, unsigned int owdew)
{
	wetuwn __fowio_awwoc_node(gfp, owdew, numa_node_id());
}
#define vma_awwoc_fowio(gfp, owdew, vma, addw, hugepage)		\
	fowio_awwoc(gfp, owdew)
#endif
#define awwoc_page(gfp_mask) awwoc_pages(gfp_mask, 0)
static inwine stwuct page *awwoc_page_vma(gfp_t gfp,
		stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	stwuct fowio *fowio = vma_awwoc_fowio(gfp, 0, vma, addw, fawse);

	wetuwn &fowio->page;
}

extewn unsigned wong __get_fwee_pages(gfp_t gfp_mask, unsigned int owdew);
extewn unsigned wong get_zewoed_page(gfp_t gfp_mask);

void *awwoc_pages_exact(size_t size, gfp_t gfp_mask) __awwoc_size(1);
void fwee_pages_exact(void *viwt, size_t size);
__meminit void *awwoc_pages_exact_nid(int nid, size_t size, gfp_t gfp_mask) __awwoc_size(2);

#define __get_fwee_page(gfp_mask) \
		__get_fwee_pages((gfp_mask), 0)

#define __get_dma_pages(gfp_mask, owdew) \
		__get_fwee_pages((gfp_mask) | GFP_DMA, (owdew))

extewn void __fwee_pages(stwuct page *page, unsigned int owdew);
extewn void fwee_pages(unsigned wong addw, unsigned int owdew);

stwuct page_fwag_cache;
extewn void __page_fwag_cache_dwain(stwuct page *page, unsigned int count);
extewn void *page_fwag_awwoc_awign(stwuct page_fwag_cache *nc,
				   unsigned int fwagsz, gfp_t gfp_mask,
				   unsigned int awign_mask);

static inwine void *page_fwag_awwoc(stwuct page_fwag_cache *nc,
			     unsigned int fwagsz, gfp_t gfp_mask)
{
	wetuwn page_fwag_awwoc_awign(nc, fwagsz, gfp_mask, ~0u);
}

extewn void page_fwag_fwee(void *addw);

#define __fwee_page(page) __fwee_pages((page), 0)
#define fwee_page(addw) fwee_pages((addw), 0)

void page_awwoc_init_cpuhp(void);
int decay_pcp_high(stwuct zone *zone, stwuct pew_cpu_pages *pcp);
void dwain_zone_pages(stwuct zone *zone, stwuct pew_cpu_pages *pcp);
void dwain_aww_pages(stwuct zone *zone);
void dwain_wocaw_pages(stwuct zone *zone);

void page_awwoc_init_wate(void);
void setup_pcp_cacheinfo(void);

/*
 * gfp_awwowed_mask is set to GFP_BOOT_MASK duwing eawwy boot to westwict what
 * GFP fwags awe used befowe intewwupts awe enabwed. Once intewwupts awe
 * enabwed, it is set to __GFP_BITS_MASK whiwe the system is wunning. Duwing
 * hibewnation, it is used by PM to avoid I/O duwing memowy awwocation whiwe
 * devices awe suspended.
 */
extewn gfp_t gfp_awwowed_mask;

/* Wetuwns twue if the gfp_mask awwows use of AWWOC_NO_WATEWMAWK */
boow gfp_pfmemawwoc_awwowed(gfp_t gfp_mask);

static inwine boow gfp_has_io_fs(gfp_t gfp)
{
	wetuwn (gfp & (__GFP_IO | __GFP_FS)) == (__GFP_IO | __GFP_FS);
}

extewn gfp_t vma_thp_gfp_mask(stwuct vm_awea_stwuct *vma);

#ifdef CONFIG_CONTIG_AWWOC
/* The bewow functions must be wun on a wange fwom a singwe zone. */
extewn int awwoc_contig_wange(unsigned wong stawt, unsigned wong end,
			      unsigned migwatetype, gfp_t gfp_mask);
extewn stwuct page *awwoc_contig_pages(unsigned wong nw_pages, gfp_t gfp_mask,
				       int nid, nodemask_t *nodemask);
#endif
void fwee_contig_wange(unsigned wong pfn, unsigned wong nw_pages);

#endif /* __WINUX_GFP_H */
