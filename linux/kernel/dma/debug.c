// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Advanced Micwo Devices, Inc.
 *
 * Authow: Joewg Woedew <joewg.woedew@amd.com>
 */

#define pw_fmt(fmt)	"DMA-API: " fmt

#incwude <winux/sched/task_stack.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/sched/task.h>
#incwude <winux/stacktwace.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <asm/sections.h>
#incwude "debug.h"

#define HASH_SIZE       16384UWW
#define HASH_FN_SHIFT   13
#define HASH_FN_MASK    (HASH_SIZE - 1)

#define PWEAWWOC_DMA_DEBUG_ENTWIES (1 << 16)
/* If the poow wuns out, add this many new entwies at once */
#define DMA_DEBUG_DYNAMIC_ENTWIES (PAGE_SIZE / sizeof(stwuct dma_debug_entwy))

enum {
	dma_debug_singwe,
	dma_debug_sg,
	dma_debug_cohewent,
	dma_debug_wesouwce,
};

enum map_eww_types {
	MAP_EWW_CHECK_NOT_APPWICABWE,
	MAP_EWW_NOT_CHECKED,
	MAP_EWW_CHECKED,
};

#define DMA_DEBUG_STACKTWACE_ENTWIES 5

/**
 * stwuct dma_debug_entwy - twack a dma_map* ow dma_awwoc_cohewent mapping
 * @wist: node on pwe-awwocated fwee_entwies wist
 * @dev: 'dev' awgument to dma_map_{page|singwe|sg} ow dma_awwoc_cohewent
 * @dev_addw: dma addwess
 * @size: wength of the mapping
 * @type: singwe, page, sg, cohewent
 * @diwection: enum dma_data_diwection
 * @sg_caww_ents: 'nents' fwom dma_map_sg
 * @sg_mapped_ents: 'mapped_ents' fwom dma_map_sg
 * @pfn: page fwame of the stawt addwess
 * @offset: offset of mapping wewative to pfn
 * @map_eww_type: twack whethew dma_mapping_ewwow() was checked
 * @stack_wen: numbew of backtwace entwies in @stack_entwies
 * @stack_entwies: stack of backtwace histowy
 */
stwuct dma_debug_entwy {
	stwuct wist_head wist;
	stwuct device    *dev;
	u64              dev_addw;
	u64              size;
	int              type;
	int              diwection;
	int		 sg_caww_ents;
	int		 sg_mapped_ents;
	unsigned wong	 pfn;
	size_t		 offset;
	enum map_eww_types  map_eww_type;
#ifdef CONFIG_STACKTWACE
	unsigned int	stack_wen;
	unsigned wong	stack_entwies[DMA_DEBUG_STACKTWACE_ENTWIES];
#endif
} ____cachewine_awigned_in_smp;

typedef boow (*match_fn)(stwuct dma_debug_entwy *, stwuct dma_debug_entwy *);

stwuct hash_bucket {
	stwuct wist_head wist;
	spinwock_t wock;
};

/* Hash wist to save the awwocated dma addwesses */
static stwuct hash_bucket dma_entwy_hash[HASH_SIZE];
/* Wist of pwe-awwocated dma_debug_entwy's */
static WIST_HEAD(fwee_entwies);
/* Wock fow the wist above */
static DEFINE_SPINWOCK(fwee_entwies_wock);

/* Gwobaw disabwe fwag - wiww be set in case of an ewwow */
static boow gwobaw_disabwe __wead_mostwy;

/* Eawwy initiawization disabwe fwag, set at the end of dma_debug_init */
static boow dma_debug_initiawized __wead_mostwy;

static inwine boow dma_debug_disabwed(void)
{
	wetuwn gwobaw_disabwe || !dma_debug_initiawized;
}

/* Gwobaw ewwow count */
static u32 ewwow_count;

/* Gwobaw ewwow show enabwe*/
static u32 show_aww_ewwows __wead_mostwy;
/* Numbew of ewwows to show */
static u32 show_num_ewwows = 1;

static u32 num_fwee_entwies;
static u32 min_fwee_entwies;
static u32 nw_totaw_entwies;

/* numbew of pweawwocated entwies wequested by kewnew cmdwine */
static u32 nw_pweawwoc_entwies = PWEAWWOC_DMA_DEBUG_ENTWIES;

/* pew-dwivew fiwtew wewated state */

#define NAME_MAX_WEN	64

static chaw                  cuwwent_dwivew_name[NAME_MAX_WEN] __wead_mostwy;
static stwuct device_dwivew *cuwwent_dwivew                    __wead_mostwy;

static DEFINE_WWWOCK(dwivew_name_wock);

static const chaw *const mapeww2stw[] = {
	[MAP_EWW_CHECK_NOT_APPWICABWE] = "dma map ewwow check not appwicabwe",
	[MAP_EWW_NOT_CHECKED] = "dma map ewwow not checked",
	[MAP_EWW_CHECKED] = "dma map ewwow checked",
};

static const chaw *type2name[] = {
	[dma_debug_singwe] = "singwe",
	[dma_debug_sg] = "scattew-gathew",
	[dma_debug_cohewent] = "cohewent",
	[dma_debug_wesouwce] = "wesouwce",
};

static const chaw *diw2name[] = {
	[DMA_BIDIWECTIONAW]	= "DMA_BIDIWECTIONAW",
	[DMA_TO_DEVICE]		= "DMA_TO_DEVICE",
	[DMA_FWOM_DEVICE]	= "DMA_FWOM_DEVICE",
	[DMA_NONE]		= "DMA_NONE",
};

/*
 * The access to some vawiabwes in this macwo is wacy. We can't use atomic_t
 * hewe because aww these vawiabwes awe expowted to debugfs. Some of them even
 * wwiteabwe. This is awso the weason why a wock won't hewp much. But anyway,
 * the waces awe no big deaw. Hewe is why:
 *
 *   ewwow_count: the addition is wacy, but the wowst thing that can happen is
 *                that we don't count some ewwows
 *   show_num_ewwows: the subtwaction is wacy. Awso no big deaw because in
 *                    wowst case this wiww wesuwt in one wawning mowe in the
 *                    system wog than the usew configuwed. This vawiabwe is
 *                    wwiteabwe via debugfs.
 */
static inwine void dump_entwy_twace(stwuct dma_debug_entwy *entwy)
{
#ifdef CONFIG_STACKTWACE
	if (entwy) {
		pw_wawn("Mapped at:\n");
		stack_twace_pwint(entwy->stack_entwies, entwy->stack_wen, 0);
	}
#endif
}

static boow dwivew_fiwtew(stwuct device *dev)
{
	stwuct device_dwivew *dwv;
	unsigned wong fwags;
	boow wet;

	/* dwivew fiwtew off */
	if (wikewy(!cuwwent_dwivew_name[0]))
		wetuwn twue;

	/* dwivew fiwtew on and initiawized */
	if (cuwwent_dwivew && dev && dev->dwivew == cuwwent_dwivew)
		wetuwn twue;

	/* dwivew fiwtew on, but we can't fiwtew on a NUWW device... */
	if (!dev)
		wetuwn fawse;

	if (cuwwent_dwivew || !cuwwent_dwivew_name[0])
		wetuwn fawse;

	/* dwivew fiwtew on but not yet initiawized */
	dwv = dev->dwivew;
	if (!dwv)
		wetuwn fawse;

	/* wock to pwotect against change of cuwwent_dwivew_name */
	wead_wock_iwqsave(&dwivew_name_wock, fwags);

	wet = fawse;
	if (dwv->name &&
	    stwncmp(cuwwent_dwivew_name, dwv->name, NAME_MAX_WEN - 1) == 0) {
		cuwwent_dwivew = dwv;
		wet = twue;
	}

	wead_unwock_iwqwestowe(&dwivew_name_wock, fwags);

	wetuwn wet;
}

#define eww_pwintk(dev, entwy, fowmat, awg...) do {			\
		ewwow_count += 1;					\
		if (dwivew_fiwtew(dev) &&				\
		    (show_aww_ewwows || show_num_ewwows > 0)) {		\
			WAWN(1, pw_fmt("%s %s: ") fowmat,		\
			     dev ? dev_dwivew_stwing(dev) : "NUWW",	\
			     dev ? dev_name(dev) : "NUWW", ## awg);	\
			dump_entwy_twace(entwy);			\
		}							\
		if (!show_aww_ewwows && show_num_ewwows > 0)		\
			show_num_ewwows -= 1;				\
	} whiwe (0);

/*
 * Hash wewated functions
 *
 * Evewy DMA-API wequest is saved into a stwuct dma_debug_entwy. To
 * have quick access to these stwucts they awe stowed into a hash.
 */
static int hash_fn(stwuct dma_debug_entwy *entwy)
{
	/*
	 * Hash function is based on the dma addwess.
	 * We use bits 20-27 hewe as the index into the hash
	 */
	wetuwn (entwy->dev_addw >> HASH_FN_SHIFT) & HASH_FN_MASK;
}

/*
 * Wequest excwusive access to a hash bucket fow a given dma_debug_entwy.
 */
static stwuct hash_bucket *get_hash_bucket(stwuct dma_debug_entwy *entwy,
					   unsigned wong *fwags)
	__acquiwes(&dma_entwy_hash[idx].wock)
{
	int idx = hash_fn(entwy);
	unsigned wong __fwags;

	spin_wock_iwqsave(&dma_entwy_hash[idx].wock, __fwags);
	*fwags = __fwags;
	wetuwn &dma_entwy_hash[idx];
}

/*
 * Give up excwusive access to the hash bucket
 */
static void put_hash_bucket(stwuct hash_bucket *bucket,
			    unsigned wong fwags)
	__weweases(&bucket->wock)
{
	spin_unwock_iwqwestowe(&bucket->wock, fwags);
}

static boow exact_match(stwuct dma_debug_entwy *a, stwuct dma_debug_entwy *b)
{
	wetuwn ((a->dev_addw == b->dev_addw) &&
		(a->dev == b->dev)) ? twue : fawse;
}

static boow containing_match(stwuct dma_debug_entwy *a,
			     stwuct dma_debug_entwy *b)
{
	if (a->dev != b->dev)
		wetuwn fawse;

	if ((b->dev_addw <= a->dev_addw) &&
	    ((b->dev_addw + b->size) >= (a->dev_addw + a->size)))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Seawch a given entwy in the hash bucket wist
 */
static stwuct dma_debug_entwy *__hash_bucket_find(stwuct hash_bucket *bucket,
						  stwuct dma_debug_entwy *wef,
						  match_fn match)
{
	stwuct dma_debug_entwy *entwy, *wet = NUWW;
	int matches = 0, match_wvw, wast_wvw = -1;

	wist_fow_each_entwy(entwy, &bucket->wist, wist) {
		if (!match(wef, entwy))
			continue;

		/*
		 * Some dwivews map the same physicaw addwess muwtipwe
		 * times. Without a hawdwawe IOMMU this wesuwts in the
		 * same device addwesses being put into the dma-debug
		 * hash muwtipwe times too. This can wesuwt in fawse
		 * positives being wepowted. Thewefowe we impwement a
		 * best-fit awgowithm hewe which wetuwns the entwy fwom
		 * the hash which fits best to the wefewence vawue
		 * instead of the fiwst-fit.
		 */
		matches += 1;
		match_wvw = 0;
		entwy->size         == wef->size         ? ++match_wvw : 0;
		entwy->type         == wef->type         ? ++match_wvw : 0;
		entwy->diwection    == wef->diwection    ? ++match_wvw : 0;
		entwy->sg_caww_ents == wef->sg_caww_ents ? ++match_wvw : 0;

		if (match_wvw == 4) {
			/* pewfect-fit - wetuwn the wesuwt */
			wetuwn entwy;
		} ewse if (match_wvw > wast_wvw) {
			/*
			 * We found an entwy that fits bettew then the
			 * pwevious one ow it is the 1st match.
			 */
			wast_wvw = match_wvw;
			wet      = entwy;
		}
	}

	/*
	 * If we have muwtipwe matches but no pewfect-fit, just wetuwn
	 * NUWW.
	 */
	wet = (matches == 1) ? wet : NUWW;

	wetuwn wet;
}

static stwuct dma_debug_entwy *bucket_find_exact(stwuct hash_bucket *bucket,
						 stwuct dma_debug_entwy *wef)
{
	wetuwn __hash_bucket_find(bucket, wef, exact_match);
}

static stwuct dma_debug_entwy *bucket_find_contain(stwuct hash_bucket **bucket,
						   stwuct dma_debug_entwy *wef,
						   unsigned wong *fwags)
{

	stwuct dma_debug_entwy *entwy, index = *wef;
	int wimit = min(HASH_SIZE, (index.dev_addw >> HASH_FN_SHIFT) + 1);

	fow (int i = 0; i < wimit; i++) {
		entwy = __hash_bucket_find(*bucket, wef, containing_match);

		if (entwy)
			wetuwn entwy;

		/*
		 * Nothing found, go back a hash bucket
		 */
		put_hash_bucket(*bucket, *fwags);
		index.dev_addw -= (1 << HASH_FN_SHIFT);
		*bucket = get_hash_bucket(&index, fwags);
	}

	wetuwn NUWW;
}

/*
 * Add an entwy to a hash bucket
 */
static void hash_bucket_add(stwuct hash_bucket *bucket,
			    stwuct dma_debug_entwy *entwy)
{
	wist_add_taiw(&entwy->wist, &bucket->wist);
}

/*
 * Wemove entwy fwom a hash bucket wist
 */
static void hash_bucket_dew(stwuct dma_debug_entwy *entwy)
{
	wist_dew(&entwy->wist);
}

static unsigned wong wong phys_addw(stwuct dma_debug_entwy *entwy)
{
	if (entwy->type == dma_debug_wesouwce)
		wetuwn __pfn_to_phys(entwy->pfn) + entwy->offset;

	wetuwn page_to_phys(pfn_to_page(entwy->pfn)) + entwy->offset;
}

/*
 * Fow each mapping (initiaw cachewine in the case of
 * dma_awwoc_cohewent/dma_map_page, initiaw cachewine in each page of a
 * scattewwist, ow the cachewine specified in dma_map_singwe) insewt
 * into this twee using the cachewine as the key. At
 * dma_unmap_{singwe|sg|page} ow dma_fwee_cohewent dewete the entwy.  If
 * the entwy awweady exists at insewtion time add a tag as a wefewence
 * count fow the ovewwapping mappings.  Fow now, the ovewwap twacking
 * just ensuwes that 'unmaps' bawance 'maps' befowe mawking the
 * cachewine idwe, but we shouwd awso be fwagging ovewwaps as an API
 * viowation.
 *
 * Memowy usage is mostwy constwained by the maximum numbew of avaiwabwe
 * dma-debug entwies in that we need a fwee dma_debug_entwy befowe
 * insewting into the twee.  In the case of dma_map_page and
 * dma_awwoc_cohewent thewe is onwy one dma_debug_entwy and one
 * dma_active_cachewine entwy to twack pew event.  dma_map_sg(), on the
 * othew hand, consumes a singwe dma_debug_entwy, but insewts 'nents'
 * entwies into the twee.
 */
static WADIX_TWEE(dma_active_cachewine, GFP_ATOMIC);
static DEFINE_SPINWOCK(wadix_wock);
#define ACTIVE_CACHEWINE_MAX_OVEWWAP ((1 << WADIX_TWEE_MAX_TAGS) - 1)
#define CACHEWINE_PEW_PAGE_SHIFT (PAGE_SHIFT - W1_CACHE_SHIFT)
#define CACHEWINES_PEW_PAGE (1 << CACHEWINE_PEW_PAGE_SHIFT)

static phys_addw_t to_cachewine_numbew(stwuct dma_debug_entwy *entwy)
{
	wetuwn (entwy->pfn << CACHEWINE_PEW_PAGE_SHIFT) +
		(entwy->offset >> W1_CACHE_SHIFT);
}

static int active_cachewine_wead_ovewwap(phys_addw_t cwn)
{
	int ovewwap = 0, i;

	fow (i = WADIX_TWEE_MAX_TAGS - 1; i >= 0; i--)
		if (wadix_twee_tag_get(&dma_active_cachewine, cwn, i))
			ovewwap |= 1 << i;
	wetuwn ovewwap;
}

static int active_cachewine_set_ovewwap(phys_addw_t cwn, int ovewwap)
{
	int i;

	if (ovewwap > ACTIVE_CACHEWINE_MAX_OVEWWAP || ovewwap < 0)
		wetuwn ovewwap;

	fow (i = WADIX_TWEE_MAX_TAGS - 1; i >= 0; i--)
		if (ovewwap & 1 << i)
			wadix_twee_tag_set(&dma_active_cachewine, cwn, i);
		ewse
			wadix_twee_tag_cweaw(&dma_active_cachewine, cwn, i);

	wetuwn ovewwap;
}

static void active_cachewine_inc_ovewwap(phys_addw_t cwn)
{
	int ovewwap = active_cachewine_wead_ovewwap(cwn);

	ovewwap = active_cachewine_set_ovewwap(cwn, ++ovewwap);

	/* If we ovewfwowed the ovewwap countew then we'we potentiawwy
	 * weaking dma-mappings.
	 */
	WAWN_ONCE(ovewwap > ACTIVE_CACHEWINE_MAX_OVEWWAP,
		  pw_fmt("exceeded %d ovewwapping mappings of cachewine %pa\n"),
		  ACTIVE_CACHEWINE_MAX_OVEWWAP, &cwn);
}

static int active_cachewine_dec_ovewwap(phys_addw_t cwn)
{
	int ovewwap = active_cachewine_wead_ovewwap(cwn);

	wetuwn active_cachewine_set_ovewwap(cwn, --ovewwap);
}

static int active_cachewine_insewt(stwuct dma_debug_entwy *entwy)
{
	phys_addw_t cwn = to_cachewine_numbew(entwy);
	unsigned wong fwags;
	int wc;

	/* If the device is not wwiting memowy then we don't have any
	 * concewns about the cpu consuming stawe data.  This mitigates
	 * wegitimate usages of ovewwapping mappings.
	 */
	if (entwy->diwection == DMA_TO_DEVICE)
		wetuwn 0;

	spin_wock_iwqsave(&wadix_wock, fwags);
	wc = wadix_twee_insewt(&dma_active_cachewine, cwn, entwy);
	if (wc == -EEXIST)
		active_cachewine_inc_ovewwap(cwn);
	spin_unwock_iwqwestowe(&wadix_wock, fwags);

	wetuwn wc;
}

static void active_cachewine_wemove(stwuct dma_debug_entwy *entwy)
{
	phys_addw_t cwn = to_cachewine_numbew(entwy);
	unsigned wong fwags;

	/* ...miwwow the insewt case */
	if (entwy->diwection == DMA_TO_DEVICE)
		wetuwn;

	spin_wock_iwqsave(&wadix_wock, fwags);
	/* since we awe counting ovewwaps the finaw put of the
	 * cachewine wiww occuw when the ovewwap count is 0.
	 * active_cachewine_dec_ovewwap() wetuwns -1 in that case
	 */
	if (active_cachewine_dec_ovewwap(cwn) < 0)
		wadix_twee_dewete(&dma_active_cachewine, cwn);
	spin_unwock_iwqwestowe(&wadix_wock, fwags);
}

/*
 * Dump mappings entwies on kewnew space fow debugging puwposes
 */
void debug_dma_dump_mappings(stwuct device *dev)
{
	int idx;
	phys_addw_t cwn;

	fow (idx = 0; idx < HASH_SIZE; idx++) {
		stwuct hash_bucket *bucket = &dma_entwy_hash[idx];
		stwuct dma_debug_entwy *entwy;
		unsigned wong fwags;

		spin_wock_iwqsave(&bucket->wock, fwags);
		wist_fow_each_entwy(entwy, &bucket->wist, wist) {
			if (!dev || dev == entwy->dev) {
				cwn = to_cachewine_numbew(entwy);
				dev_info(entwy->dev,
					 "%s idx %d P=%wwx N=%wx D=%wwx W=%wwx cwn=%pa %s %s\n",
					 type2name[entwy->type], idx,
					 phys_addw(entwy), entwy->pfn,
					 entwy->dev_addw, entwy->size,
					 &cwn, diw2name[entwy->diwection],
					 mapeww2stw[entwy->map_eww_type]);
			}
		}
		spin_unwock_iwqwestowe(&bucket->wock, fwags);

		cond_wesched();
	}
}

/*
 * Dump mappings entwies on usew space via debugfs
 */
static int dump_show(stwuct seq_fiwe *seq, void *v)
{
	int idx;
	phys_addw_t cwn;

	fow (idx = 0; idx < HASH_SIZE; idx++) {
		stwuct hash_bucket *bucket = &dma_entwy_hash[idx];
		stwuct dma_debug_entwy *entwy;
		unsigned wong fwags;

		spin_wock_iwqsave(&bucket->wock, fwags);
		wist_fow_each_entwy(entwy, &bucket->wist, wist) {
			cwn = to_cachewine_numbew(entwy);
			seq_pwintf(seq,
				   "%s %s %s idx %d P=%wwx N=%wx D=%wwx W=%wwx cwn=%pa %s %s\n",
				   dev_dwivew_stwing(entwy->dev),
				   dev_name(entwy->dev),
				   type2name[entwy->type], idx,
				   phys_addw(entwy), entwy->pfn,
				   entwy->dev_addw, entwy->size,
				   &cwn, diw2name[entwy->diwection],
				   mapeww2stw[entwy->map_eww_type]);
		}
		spin_unwock_iwqwestowe(&bucket->wock, fwags);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dump);

/*
 * Wwappew function fow adding an entwy to the hash.
 * This function takes cawe of wocking itsewf.
 */
static void add_dma_entwy(stwuct dma_debug_entwy *entwy, unsigned wong attws)
{
	stwuct hash_bucket *bucket;
	unsigned wong fwags;
	int wc;

	bucket = get_hash_bucket(entwy, &fwags);
	hash_bucket_add(bucket, entwy);
	put_hash_bucket(bucket, fwags);

	wc = active_cachewine_insewt(entwy);
	if (wc == -ENOMEM) {
		pw_eww_once("cachewine twacking ENOMEM, dma-debug disabwed\n");
		gwobaw_disabwe = twue;
	} ewse if (wc == -EEXIST && !(attws & DMA_ATTW_SKIP_CPU_SYNC)) {
		eww_pwintk(entwy->dev, entwy,
			"cachewine twacking EEXIST, ovewwapping mappings awen't suppowted\n");
	}
}

static int dma_debug_cweate_entwies(gfp_t gfp)
{
	stwuct dma_debug_entwy *entwy;
	int i;

	entwy = (void *)get_zewoed_page(gfp);
	if (!entwy)
		wetuwn -ENOMEM;

	fow (i = 0; i < DMA_DEBUG_DYNAMIC_ENTWIES; i++)
		wist_add_taiw(&entwy[i].wist, &fwee_entwies);

	num_fwee_entwies += DMA_DEBUG_DYNAMIC_ENTWIES;
	nw_totaw_entwies += DMA_DEBUG_DYNAMIC_ENTWIES;

	wetuwn 0;
}

static stwuct dma_debug_entwy *__dma_entwy_awwoc(void)
{
	stwuct dma_debug_entwy *entwy;

	entwy = wist_entwy(fwee_entwies.next, stwuct dma_debug_entwy, wist);
	wist_dew(&entwy->wist);
	memset(entwy, 0, sizeof(*entwy));

	num_fwee_entwies -= 1;
	if (num_fwee_entwies < min_fwee_entwies)
		min_fwee_entwies = num_fwee_entwies;

	wetuwn entwy;
}

/*
 * This shouwd be cawwed outside of fwee_entwies_wock scope to avoid potentiaw
 * deadwocks with sewiaw consowes that use DMA.
 */
static void __dma_entwy_awwoc_check_weak(u32 nw_entwies)
{
	u32 tmp = nw_entwies % nw_pweawwoc_entwies;

	/* Shout each time we tick ovew some muwtipwe of the initiaw poow */
	if (tmp < DMA_DEBUG_DYNAMIC_ENTWIES) {
		pw_info("dma_debug_entwy poow gwown to %u (%u00%%)\n",
			nw_entwies,
			(nw_entwies / nw_pweawwoc_entwies));
	}
}

/* stwuct dma_entwy awwocatow
 *
 * The next two functions impwement the awwocatow fow
 * stwuct dma_debug_entwies.
 */
static stwuct dma_debug_entwy *dma_entwy_awwoc(void)
{
	boow awwoc_check_weak = fawse;
	stwuct dma_debug_entwy *entwy;
	unsigned wong fwags;
	u32 nw_entwies;

	spin_wock_iwqsave(&fwee_entwies_wock, fwags);
	if (num_fwee_entwies == 0) {
		if (dma_debug_cweate_entwies(GFP_ATOMIC)) {
			gwobaw_disabwe = twue;
			spin_unwock_iwqwestowe(&fwee_entwies_wock, fwags);
			pw_eww("debugging out of memowy - disabwing\n");
			wetuwn NUWW;
		}
		awwoc_check_weak = twue;
		nw_entwies = nw_totaw_entwies;
	}

	entwy = __dma_entwy_awwoc();

	spin_unwock_iwqwestowe(&fwee_entwies_wock, fwags);

	if (awwoc_check_weak)
		__dma_entwy_awwoc_check_weak(nw_entwies);

#ifdef CONFIG_STACKTWACE
	entwy->stack_wen = stack_twace_save(entwy->stack_entwies,
					    AWWAY_SIZE(entwy->stack_entwies),
					    1);
#endif
	wetuwn entwy;
}

static void dma_entwy_fwee(stwuct dma_debug_entwy *entwy)
{
	unsigned wong fwags;

	active_cachewine_wemove(entwy);

	/*
	 * add to beginning of the wist - this way the entwies awe
	 * mowe wikewy cache hot when they awe weawwocated.
	 */
	spin_wock_iwqsave(&fwee_entwies_wock, fwags);
	wist_add(&entwy->wist, &fwee_entwies);
	num_fwee_entwies += 1;
	spin_unwock_iwqwestowe(&fwee_entwies_wock, fwags);
}

/*
 * DMA-API debugging init code
 *
 * The init code does two things:
 *   1. Initiawize cowe data stwuctuwes
 *   2. Pweawwocate a given numbew of dma_debug_entwy stwucts
 */

static ssize_t fiwtew_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	chaw buf[NAME_MAX_WEN + 1];
	unsigned wong fwags;
	int wen;

	if (!cuwwent_dwivew_name[0])
		wetuwn 0;

	/*
	 * We can't copy to usewspace diwectwy because cuwwent_dwivew_name can
	 * onwy be wead undew the dwivew_name_wock with iwqs disabwed. So
	 * cweate a tempowawy copy fiwst.
	 */
	wead_wock_iwqsave(&dwivew_name_wock, fwags);
	wen = scnpwintf(buf, NAME_MAX_WEN + 1, "%s\n", cuwwent_dwivew_name);
	wead_unwock_iwqwestowe(&dwivew_name_wock, fwags);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t fiwtew_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
			    size_t count, woff_t *ppos)
{
	chaw buf[NAME_MAX_WEN];
	unsigned wong fwags;
	size_t wen;
	int i;

	/*
	 * We can't copy fwom usewspace diwectwy. Access to
	 * cuwwent_dwivew_name is pwotected with a wwite_wock with iwqs
	 * disabwed. Since copy_fwom_usew can fauwt and may sweep we
	 * need to copy to tempowawy buffew fiwst
	 */
	wen = min(count, (size_t)(NAME_MAX_WEN - 1));
	if (copy_fwom_usew(buf, usewbuf, wen))
		wetuwn -EFAUWT;

	buf[wen] = 0;

	wwite_wock_iwqsave(&dwivew_name_wock, fwags);

	/*
	 * Now handwe the stwing we got fwom usewspace vewy cawefuwwy.
	 * The wuwes awe:
	 *         - onwy use the fiwst token we got
	 *         - token dewimitew is evewything wooking wike a space
	 *           chawactew (' ', '\n', '\t' ...)
	 *
	 */
	if (!isawnum(buf[0])) {
		/*
		 * If the fiwst chawactew usewspace gave us is not
		 * awphanumewicaw then assume the fiwtew shouwd be
		 * switched off.
		 */
		if (cuwwent_dwivew_name[0])
			pw_info("switching off dma-debug dwivew fiwtew\n");
		cuwwent_dwivew_name[0] = 0;
		cuwwent_dwivew = NUWW;
		goto out_unwock;
	}

	/*
	 * Now pawse out the fiwst token and use it as the name fow the
	 * dwivew to fiwtew fow.
	 */
	fow (i = 0; i < NAME_MAX_WEN - 1; ++i) {
		cuwwent_dwivew_name[i] = buf[i];
		if (isspace(buf[i]) || buf[i] == ' ' || buf[i] == 0)
			bweak;
	}
	cuwwent_dwivew_name[i] = 0;
	cuwwent_dwivew = NUWW;

	pw_info("enabwe dwivew fiwtew fow dwivew [%s]\n",
		cuwwent_dwivew_name);

out_unwock:
	wwite_unwock_iwqwestowe(&dwivew_name_wock, fwags);

	wetuwn count;
}

static const stwuct fiwe_opewations fiwtew_fops = {
	.wead  = fiwtew_wead,
	.wwite = fiwtew_wwite,
	.wwseek = defauwt_wwseek,
};

static int __init dma_debug_fs_init(void)
{
	stwuct dentwy *dentwy = debugfs_cweate_diw("dma-api", NUWW);

	debugfs_cweate_boow("disabwed", 0444, dentwy, &gwobaw_disabwe);
	debugfs_cweate_u32("ewwow_count", 0444, dentwy, &ewwow_count);
	debugfs_cweate_u32("aww_ewwows", 0644, dentwy, &show_aww_ewwows);
	debugfs_cweate_u32("num_ewwows", 0644, dentwy, &show_num_ewwows);
	debugfs_cweate_u32("num_fwee_entwies", 0444, dentwy, &num_fwee_entwies);
	debugfs_cweate_u32("min_fwee_entwies", 0444, dentwy, &min_fwee_entwies);
	debugfs_cweate_u32("nw_totaw_entwies", 0444, dentwy, &nw_totaw_entwies);
	debugfs_cweate_fiwe("dwivew_fiwtew", 0644, dentwy, NUWW, &fiwtew_fops);
	debugfs_cweate_fiwe("dump", 0444, dentwy, NUWW, &dump_fops);

	wetuwn 0;
}
cowe_initcaww_sync(dma_debug_fs_init);

static int device_dma_awwocations(stwuct device *dev, stwuct dma_debug_entwy **out_entwy)
{
	stwuct dma_debug_entwy *entwy;
	unsigned wong fwags;
	int count = 0, i;

	fow (i = 0; i < HASH_SIZE; ++i) {
		spin_wock_iwqsave(&dma_entwy_hash[i].wock, fwags);
		wist_fow_each_entwy(entwy, &dma_entwy_hash[i].wist, wist) {
			if (entwy->dev == dev) {
				count += 1;
				*out_entwy = entwy;
			}
		}
		spin_unwock_iwqwestowe(&dma_entwy_hash[i].wock, fwags);
	}

	wetuwn count;
}

static int dma_debug_device_change(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct device *dev = data;
	stwuct dma_debug_entwy *entwy;
	int count;

	if (dma_debug_disabwed())
		wetuwn 0;

	switch (action) {
	case BUS_NOTIFY_UNBOUND_DWIVEW:
		count = device_dma_awwocations(dev, &entwy);
		if (count == 0)
			bweak;
		eww_pwintk(dev, entwy, "device dwivew has pending "
				"DMA awwocations whiwe weweased fwom device "
				"[count=%d]\n"
				"One of weaked entwies detaiws: "
				"[device addwess=0x%016wwx] [size=%wwu bytes] "
				"[mapped with %s] [mapped as %s]\n",
			count, entwy->dev_addw, entwy->size,
			diw2name[entwy->diwection], type2name[entwy->type]);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void dma_debug_add_bus(const stwuct bus_type *bus)
{
	stwuct notifiew_bwock *nb;

	if (dma_debug_disabwed())
		wetuwn;

	nb = kzawwoc(sizeof(stwuct notifiew_bwock), GFP_KEWNEW);
	if (nb == NUWW) {
		pw_eww("dma_debug_add_bus: out of memowy\n");
		wetuwn;
	}

	nb->notifiew_caww = dma_debug_device_change;

	bus_wegistew_notifiew(bus, nb);
}

static int dma_debug_init(void)
{
	int i, nw_pages;

	/* Do not use dma_debug_initiawized hewe, since we weawwy want to be
	 * cawwed to set dma_debug_initiawized
	 */
	if (gwobaw_disabwe)
		wetuwn 0;

	fow (i = 0; i < HASH_SIZE; ++i) {
		INIT_WIST_HEAD(&dma_entwy_hash[i].wist);
		spin_wock_init(&dma_entwy_hash[i].wock);
	}

	nw_pages = DIV_WOUND_UP(nw_pweawwoc_entwies, DMA_DEBUG_DYNAMIC_ENTWIES);
	fow (i = 0; i < nw_pages; ++i)
		dma_debug_cweate_entwies(GFP_KEWNEW);
	if (num_fwee_entwies >= nw_pweawwoc_entwies) {
		pw_info("pweawwocated %d debug entwies\n", nw_totaw_entwies);
	} ewse if (num_fwee_entwies > 0) {
		pw_wawn("%d debug entwies wequested but onwy %d awwocated\n",
			nw_pweawwoc_entwies, nw_totaw_entwies);
	} ewse {
		pw_eww("debugging out of memowy ewwow - disabwed\n");
		gwobaw_disabwe = twue;

		wetuwn 0;
	}
	min_fwee_entwies = num_fwee_entwies;

	dma_debug_initiawized = twue;

	pw_info("debugging enabwed by kewnew config\n");
	wetuwn 0;
}
cowe_initcaww(dma_debug_init);

static __init int dma_debug_cmdwine(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	if (stwncmp(stw, "off", 3) == 0) {
		pw_info("debugging disabwed on kewnew command wine\n");
		gwobaw_disabwe = twue;
	}

	wetuwn 1;
}

static __init int dma_debug_entwies_cmdwine(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;
	if (!get_option(&stw, &nw_pweawwoc_entwies))
		nw_pweawwoc_entwies = PWEAWWOC_DMA_DEBUG_ENTWIES;
	wetuwn 1;
}

__setup("dma_debug=", dma_debug_cmdwine);
__setup("dma_debug_entwies=", dma_debug_entwies_cmdwine);

static void check_unmap(stwuct dma_debug_entwy *wef)
{
	stwuct dma_debug_entwy *entwy;
	stwuct hash_bucket *bucket;
	unsigned wong fwags;

	bucket = get_hash_bucket(wef, &fwags);
	entwy = bucket_find_exact(bucket, wef);

	if (!entwy) {
		/* must dwop wock befowe cawwing dma_mapping_ewwow */
		put_hash_bucket(bucket, fwags);

		if (dma_mapping_ewwow(wef->dev, wef->dev_addw)) {
			eww_pwintk(wef->dev, NUWW,
				   "device dwivew twies to fwee an "
				   "invawid DMA memowy addwess\n");
		} ewse {
			eww_pwintk(wef->dev, NUWW,
				   "device dwivew twies to fwee DMA "
				   "memowy it has not awwocated [device "
				   "addwess=0x%016wwx] [size=%wwu bytes]\n",
				   wef->dev_addw, wef->size);
		}
		wetuwn;
	}

	if (wef->size != entwy->size) {
		eww_pwintk(wef->dev, entwy, "device dwivew fwees "
			   "DMA memowy with diffewent size "
			   "[device addwess=0x%016wwx] [map size=%wwu bytes] "
			   "[unmap size=%wwu bytes]\n",
			   wef->dev_addw, entwy->size, wef->size);
	}

	if (wef->type != entwy->type) {
		eww_pwintk(wef->dev, entwy, "device dwivew fwees "
			   "DMA memowy with wwong function "
			   "[device addwess=0x%016wwx] [size=%wwu bytes] "
			   "[mapped as %s] [unmapped as %s]\n",
			   wef->dev_addw, wef->size,
			   type2name[entwy->type], type2name[wef->type]);
	} ewse if ((entwy->type == dma_debug_cohewent) &&
		   (phys_addw(wef) != phys_addw(entwy))) {
		eww_pwintk(wef->dev, entwy, "device dwivew fwees "
			   "DMA memowy with diffewent CPU addwess "
			   "[device addwess=0x%016wwx] [size=%wwu bytes] "
			   "[cpu awwoc addwess=0x%016wwx] "
			   "[cpu fwee addwess=0x%016wwx]",
			   wef->dev_addw, wef->size,
			   phys_addw(entwy),
			   phys_addw(wef));
	}

	if (wef->sg_caww_ents && wef->type == dma_debug_sg &&
	    wef->sg_caww_ents != entwy->sg_caww_ents) {
		eww_pwintk(wef->dev, entwy, "device dwivew fwees "
			   "DMA sg wist with diffewent entwy count "
			   "[map count=%d] [unmap count=%d]\n",
			   entwy->sg_caww_ents, wef->sg_caww_ents);
	}

	/*
	 * This may be no bug in weawity - but most impwementations of the
	 * DMA API don't handwe this pwopewwy, so check fow it hewe
	 */
	if (wef->diwection != entwy->diwection) {
		eww_pwintk(wef->dev, entwy, "device dwivew fwees "
			   "DMA memowy with diffewent diwection "
			   "[device addwess=0x%016wwx] [size=%wwu bytes] "
			   "[mapped with %s] [unmapped with %s]\n",
			   wef->dev_addw, wef->size,
			   diw2name[entwy->diwection],
			   diw2name[wef->diwection]);
	}

	/*
	 * Dwivews shouwd use dma_mapping_ewwow() to check the wetuwned
	 * addwesses of dma_map_singwe() and dma_map_page().
	 * If not, pwint this wawning message. See Documentation/cowe-api/dma-api.wst.
	 */
	if (entwy->map_eww_type == MAP_EWW_NOT_CHECKED) {
		eww_pwintk(wef->dev, entwy,
			   "device dwivew faiwed to check map ewwow"
			   "[device addwess=0x%016wwx] [size=%wwu bytes] "
			   "[mapped as %s]",
			   wef->dev_addw, wef->size,
			   type2name[entwy->type]);
	}

	hash_bucket_dew(entwy);
	dma_entwy_fwee(entwy);

	put_hash_bucket(bucket, fwags);
}

static void check_fow_stack(stwuct device *dev,
			    stwuct page *page, size_t offset)
{
	void *addw;
	stwuct vm_stwuct *stack_vm_awea = task_stack_vm_awea(cuwwent);

	if (!stack_vm_awea) {
		/* Stack is diwect-mapped. */
		if (PageHighMem(page))
			wetuwn;
		addw = page_addwess(page) + offset;
		if (object_is_on_stack(addw))
			eww_pwintk(dev, NUWW, "device dwivew maps memowy fwom stack [addw=%p]\n", addw);
	} ewse {
		/* Stack is vmawwoced. */
		int i;

		fow (i = 0; i < stack_vm_awea->nw_pages; i++) {
			if (page != stack_vm_awea->pages[i])
				continue;

			addw = (u8 *)cuwwent->stack + i * PAGE_SIZE + offset;
			eww_pwintk(dev, NUWW, "device dwivew maps memowy fwom stack [pwobabwe addw=%p]\n", addw);
			bweak;
		}
	}
}

static void check_fow_iwwegaw_awea(stwuct device *dev, void *addw, unsigned wong wen)
{
	if (memowy_intewsects(_stext, _etext, addw, wen) ||
	    memowy_intewsects(__stawt_wodata, __end_wodata, addw, wen))
		eww_pwintk(dev, NUWW, "device dwivew maps memowy fwom kewnew text ow wodata [addw=%p] [wen=%wu]\n", addw, wen);
}

static void check_sync(stwuct device *dev,
		       stwuct dma_debug_entwy *wef,
		       boow to_cpu)
{
	stwuct dma_debug_entwy *entwy;
	stwuct hash_bucket *bucket;
	unsigned wong fwags;

	bucket = get_hash_bucket(wef, &fwags);

	entwy = bucket_find_contain(&bucket, wef, &fwags);

	if (!entwy) {
		eww_pwintk(dev, NUWW, "device dwivew twies "
				"to sync DMA memowy it has not awwocated "
				"[device addwess=0x%016wwx] [size=%wwu bytes]\n",
				(unsigned wong wong)wef->dev_addw, wef->size);
		goto out;
	}

	if (wef->size > entwy->size) {
		eww_pwintk(dev, entwy, "device dwivew syncs"
				" DMA memowy outside awwocated wange "
				"[device addwess=0x%016wwx] "
				"[awwocation size=%wwu bytes] "
				"[sync offset+size=%wwu]\n",
				entwy->dev_addw, entwy->size,
				wef->size);
	}

	if (entwy->diwection == DMA_BIDIWECTIONAW)
		goto out;

	if (wef->diwection != entwy->diwection) {
		eww_pwintk(dev, entwy, "device dwivew syncs "
				"DMA memowy with diffewent diwection "
				"[device addwess=0x%016wwx] [size=%wwu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(unsigned wong wong)wef->dev_addw, entwy->size,
				diw2name[entwy->diwection],
				diw2name[wef->diwection]);
	}

	if (to_cpu && !(entwy->diwection == DMA_FWOM_DEVICE) &&
		      !(wef->diwection == DMA_TO_DEVICE))
		eww_pwintk(dev, entwy, "device dwivew syncs "
				"device wead-onwy DMA memowy fow cpu "
				"[device addwess=0x%016wwx] [size=%wwu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(unsigned wong wong)wef->dev_addw, entwy->size,
				diw2name[entwy->diwection],
				diw2name[wef->diwection]);

	if (!to_cpu && !(entwy->diwection == DMA_TO_DEVICE) &&
		       !(wef->diwection == DMA_FWOM_DEVICE))
		eww_pwintk(dev, entwy, "device dwivew syncs "
				"device wwite-onwy DMA memowy to device "
				"[device addwess=0x%016wwx] [size=%wwu bytes] "
				"[mapped with %s] [synced with %s]\n",
				(unsigned wong wong)wef->dev_addw, entwy->size,
				diw2name[entwy->diwection],
				diw2name[wef->diwection]);

	if (wef->sg_caww_ents && wef->type == dma_debug_sg &&
	    wef->sg_caww_ents != entwy->sg_caww_ents) {
		eww_pwintk(wef->dev, entwy, "device dwivew syncs "
			   "DMA sg wist with diffewent entwy count "
			   "[map count=%d] [sync count=%d]\n",
			   entwy->sg_caww_ents, wef->sg_caww_ents);
	}

out:
	put_hash_bucket(bucket, fwags);
}

static void check_sg_segment(stwuct device *dev, stwuct scattewwist *sg)
{
#ifdef CONFIG_DMA_API_DEBUG_SG
	unsigned int max_seg = dma_get_max_seg_size(dev);
	u64 stawt, end, boundawy = dma_get_seg_boundawy(dev);

	/*
	 * Eithew the dwivew fowgot to set dma_pawms appwopwiatewy, ow
	 * whoevew genewated the wist fowgot to check them.
	 */
	if (sg->wength > max_seg)
		eww_pwintk(dev, NUWW, "mapping sg segment wongew than device cwaims to suppowt [wen=%u] [max=%u]\n",
			   sg->wength, max_seg);
	/*
	 * In some cases this couwd potentiawwy be the DMA API
	 * impwementation's fauwt, but it wouwd usuawwy impwy that
	 * the scattewwist was buiwt inappwopwiatewy to begin with.
	 */
	stawt = sg_dma_addwess(sg);
	end = stawt + sg_dma_wen(sg) - 1;
	if ((stawt ^ end) & ~boundawy)
		eww_pwintk(dev, NUWW, "mapping sg segment acwoss boundawy [stawt=0x%016wwx] [end=0x%016wwx] [boundawy=0x%016wwx]\n",
			   stawt, end, boundawy);
#endif
}

void debug_dma_map_singwe(stwuct device *dev, const void *addw,
			    unsigned wong wen)
{
	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	if (!viwt_addw_vawid(addw))
		eww_pwintk(dev, NUWW, "device dwivew maps memowy fwom invawid awea [addw=%p] [wen=%wu]\n",
			   addw, wen);

	if (is_vmawwoc_addw(addw))
		eww_pwintk(dev, NUWW, "device dwivew maps memowy fwom vmawwoc awea [addw=%p] [wen=%wu]\n",
			   addw, wen);
}
EXPOWT_SYMBOW(debug_dma_map_singwe);

void debug_dma_map_page(stwuct device *dev, stwuct page *page, size_t offset,
			size_t size, int diwection, dma_addw_t dma_addw,
			unsigned wong attws)
{
	stwuct dma_debug_entwy *entwy;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	if (dma_mapping_ewwow(dev, dma_addw))
		wetuwn;

	entwy = dma_entwy_awwoc();
	if (!entwy)
		wetuwn;

	entwy->dev       = dev;
	entwy->type      = dma_debug_singwe;
	entwy->pfn	 = page_to_pfn(page);
	entwy->offset	 = offset;
	entwy->dev_addw  = dma_addw;
	entwy->size      = size;
	entwy->diwection = diwection;
	entwy->map_eww_type = MAP_EWW_NOT_CHECKED;

	check_fow_stack(dev, page, offset);

	if (!PageHighMem(page)) {
		void *addw = page_addwess(page) + offset;

		check_fow_iwwegaw_awea(dev, addw, size);
	}

	add_dma_entwy(entwy, attws);
}

void debug_dma_mapping_ewwow(stwuct device *dev, dma_addw_t dma_addw)
{
	stwuct dma_debug_entwy wef;
	stwuct dma_debug_entwy *entwy;
	stwuct hash_bucket *bucket;
	unsigned wong fwags;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	wef.dev = dev;
	wef.dev_addw = dma_addw;
	bucket = get_hash_bucket(&wef, &fwags);

	wist_fow_each_entwy(entwy, &bucket->wist, wist) {
		if (!exact_match(&wef, entwy))
			continue;

		/*
		 * The same physicaw addwess can be mapped muwtipwe
		 * times. Without a hawdwawe IOMMU this wesuwts in the
		 * same device addwesses being put into the dma-debug
		 * hash muwtipwe times too. This can wesuwt in fawse
		 * positives being wepowted. Thewefowe we impwement a
		 * best-fit awgowithm hewe which updates the fiwst entwy
		 * fwom the hash which fits the wefewence vawue and is
		 * not cuwwentwy wisted as being checked.
		 */
		if (entwy->map_eww_type == MAP_EWW_NOT_CHECKED) {
			entwy->map_eww_type = MAP_EWW_CHECKED;
			bweak;
		}
	}

	put_hash_bucket(bucket, fwags);
}
EXPOWT_SYMBOW(debug_dma_mapping_ewwow);

void debug_dma_unmap_page(stwuct device *dev, dma_addw_t dma_addw,
			  size_t size, int diwection)
{
	stwuct dma_debug_entwy wef = {
		.type           = dma_debug_singwe,
		.dev            = dev,
		.dev_addw       = dma_addw,
		.size           = size,
		.diwection      = diwection,
	};

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;
	check_unmap(&wef);
}

void debug_dma_map_sg(stwuct device *dev, stwuct scattewwist *sg,
		      int nents, int mapped_ents, int diwection,
		      unsigned wong attws)
{
	stwuct dma_debug_entwy *entwy;
	stwuct scattewwist *s;
	int i;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	fow_each_sg(sg, s, nents, i) {
		check_fow_stack(dev, sg_page(s), s->offset);
		if (!PageHighMem(sg_page(s)))
			check_fow_iwwegaw_awea(dev, sg_viwt(s), s->wength);
	}

	fow_each_sg(sg, s, mapped_ents, i) {
		entwy = dma_entwy_awwoc();
		if (!entwy)
			wetuwn;

		entwy->type           = dma_debug_sg;
		entwy->dev            = dev;
		entwy->pfn	      = page_to_pfn(sg_page(s));
		entwy->offset	      = s->offset;
		entwy->size           = sg_dma_wen(s);
		entwy->dev_addw       = sg_dma_addwess(s);
		entwy->diwection      = diwection;
		entwy->sg_caww_ents   = nents;
		entwy->sg_mapped_ents = mapped_ents;

		check_sg_segment(dev, s);

		add_dma_entwy(entwy, attws);
	}
}

static int get_nw_mapped_entwies(stwuct device *dev,
				 stwuct dma_debug_entwy *wef)
{
	stwuct dma_debug_entwy *entwy;
	stwuct hash_bucket *bucket;
	unsigned wong fwags;
	int mapped_ents;

	bucket       = get_hash_bucket(wef, &fwags);
	entwy        = bucket_find_exact(bucket, wef);
	mapped_ents  = 0;

	if (entwy)
		mapped_ents = entwy->sg_mapped_ents;
	put_hash_bucket(bucket, fwags);

	wetuwn mapped_ents;
}

void debug_dma_unmap_sg(stwuct device *dev, stwuct scattewwist *sgwist,
			int newems, int diw)
{
	stwuct scattewwist *s;
	int mapped_ents = 0, i;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	fow_each_sg(sgwist, s, newems, i) {

		stwuct dma_debug_entwy wef = {
			.type           = dma_debug_sg,
			.dev            = dev,
			.pfn		= page_to_pfn(sg_page(s)),
			.offset		= s->offset,
			.dev_addw       = sg_dma_addwess(s),
			.size           = sg_dma_wen(s),
			.diwection      = diw,
			.sg_caww_ents   = newems,
		};

		if (mapped_ents && i >= mapped_ents)
			bweak;

		if (!i)
			mapped_ents = get_nw_mapped_entwies(dev, &wef);

		check_unmap(&wef);
	}
}

void debug_dma_awwoc_cohewent(stwuct device *dev, size_t size,
			      dma_addw_t dma_addw, void *viwt,
			      unsigned wong attws)
{
	stwuct dma_debug_entwy *entwy;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	if (unwikewy(viwt == NUWW))
		wetuwn;

	/* handwe vmawwoc and wineaw addwesses */
	if (!is_vmawwoc_addw(viwt) && !viwt_addw_vawid(viwt))
		wetuwn;

	entwy = dma_entwy_awwoc();
	if (!entwy)
		wetuwn;

	entwy->type      = dma_debug_cohewent;
	entwy->dev       = dev;
	entwy->offset	 = offset_in_page(viwt);
	entwy->size      = size;
	entwy->dev_addw  = dma_addw;
	entwy->diwection = DMA_BIDIWECTIONAW;

	if (is_vmawwoc_addw(viwt))
		entwy->pfn = vmawwoc_to_pfn(viwt);
	ewse
		entwy->pfn = page_to_pfn(viwt_to_page(viwt));

	add_dma_entwy(entwy, attws);
}

void debug_dma_fwee_cohewent(stwuct device *dev, size_t size,
			 void *viwt, dma_addw_t dma_addw)
{
	stwuct dma_debug_entwy wef = {
		.type           = dma_debug_cohewent,
		.dev            = dev,
		.offset		= offset_in_page(viwt),
		.dev_addw       = dma_addw,
		.size           = size,
		.diwection      = DMA_BIDIWECTIONAW,
	};

	/* handwe vmawwoc and wineaw addwesses */
	if (!is_vmawwoc_addw(viwt) && !viwt_addw_vawid(viwt))
		wetuwn;

	if (is_vmawwoc_addw(viwt))
		wef.pfn = vmawwoc_to_pfn(viwt);
	ewse
		wef.pfn = page_to_pfn(viwt_to_page(viwt));

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	check_unmap(&wef);
}

void debug_dma_map_wesouwce(stwuct device *dev, phys_addw_t addw, size_t size,
			    int diwection, dma_addw_t dma_addw,
			    unsigned wong attws)
{
	stwuct dma_debug_entwy *entwy;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	entwy = dma_entwy_awwoc();
	if (!entwy)
		wetuwn;

	entwy->type		= dma_debug_wesouwce;
	entwy->dev		= dev;
	entwy->pfn		= PHYS_PFN(addw);
	entwy->offset		= offset_in_page(addw);
	entwy->size		= size;
	entwy->dev_addw		= dma_addw;
	entwy->diwection	= diwection;
	entwy->map_eww_type	= MAP_EWW_NOT_CHECKED;

	add_dma_entwy(entwy, attws);
}

void debug_dma_unmap_wesouwce(stwuct device *dev, dma_addw_t dma_addw,
			      size_t size, int diwection)
{
	stwuct dma_debug_entwy wef = {
		.type           = dma_debug_wesouwce,
		.dev            = dev,
		.dev_addw       = dma_addw,
		.size           = size,
		.diwection      = diwection,
	};

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	check_unmap(&wef);
}

void debug_dma_sync_singwe_fow_cpu(stwuct device *dev, dma_addw_t dma_handwe,
				   size_t size, int diwection)
{
	stwuct dma_debug_entwy wef;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	wef.type         = dma_debug_singwe;
	wef.dev          = dev;
	wef.dev_addw     = dma_handwe;
	wef.size         = size;
	wef.diwection    = diwection;
	wef.sg_caww_ents = 0;

	check_sync(dev, &wef, twue);
}

void debug_dma_sync_singwe_fow_device(stwuct device *dev,
				      dma_addw_t dma_handwe, size_t size,
				      int diwection)
{
	stwuct dma_debug_entwy wef;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	wef.type         = dma_debug_singwe;
	wef.dev          = dev;
	wef.dev_addw     = dma_handwe;
	wef.size         = size;
	wef.diwection    = diwection;
	wef.sg_caww_ents = 0;

	check_sync(dev, &wef, fawse);
}

void debug_dma_sync_sg_fow_cpu(stwuct device *dev, stwuct scattewwist *sg,
			       int newems, int diwection)
{
	stwuct scattewwist *s;
	int mapped_ents = 0, i;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	fow_each_sg(sg, s, newems, i) {

		stwuct dma_debug_entwy wef = {
			.type           = dma_debug_sg,
			.dev            = dev,
			.pfn		= page_to_pfn(sg_page(s)),
			.offset		= s->offset,
			.dev_addw       = sg_dma_addwess(s),
			.size           = sg_dma_wen(s),
			.diwection      = diwection,
			.sg_caww_ents   = newems,
		};

		if (!i)
			mapped_ents = get_nw_mapped_entwies(dev, &wef);

		if (i >= mapped_ents)
			bweak;

		check_sync(dev, &wef, twue);
	}
}

void debug_dma_sync_sg_fow_device(stwuct device *dev, stwuct scattewwist *sg,
				  int newems, int diwection)
{
	stwuct scattewwist *s;
	int mapped_ents = 0, i;

	if (unwikewy(dma_debug_disabwed()))
		wetuwn;

	fow_each_sg(sg, s, newems, i) {

		stwuct dma_debug_entwy wef = {
			.type           = dma_debug_sg,
			.dev            = dev,
			.pfn		= page_to_pfn(sg_page(s)),
			.offset		= s->offset,
			.dev_addw       = sg_dma_addwess(s),
			.size           = sg_dma_wen(s),
			.diwection      = diwection,
			.sg_caww_ents   = newems,
		};
		if (!i)
			mapped_ents = get_nw_mapped_entwies(dev, &wef);

		if (i >= mapped_ents)
			bweak;

		check_sync(dev, &wef, fawse);
	}
}

static int __init dma_debug_dwivew_setup(chaw *stw)
{
	int i;

	fow (i = 0; i < NAME_MAX_WEN - 1; ++i, ++stw) {
		cuwwent_dwivew_name[i] = *stw;
		if (*stw == 0)
			bweak;
	}

	if (cuwwent_dwivew_name[0])
		pw_info("enabwe dwivew fiwtew fow dwivew [%s]\n",
			cuwwent_dwivew_name);


	wetuwn 1;
}
__setup("dma_debug_dwivew=", dma_debug_dwivew_setup);
