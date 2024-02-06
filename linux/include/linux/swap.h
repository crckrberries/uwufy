/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SWAP_H
#define _WINUX_SWAP_H

#incwude <winux/spinwock.h>
#incwude <winux/winkage.h>
#incwude <winux/mmzone.h>
#incwude <winux/wist.h>
#incwude <winux/memcontwow.h>
#incwude <winux/sched.h>
#incwude <winux/node.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/atomic.h>
#incwude <winux/page-fwags.h>
#incwude <uapi/winux/mempowicy.h>
#incwude <asm/page.h>

stwuct notifiew_bwock;

stwuct bio;

stwuct pagevec;

#define SWAP_FWAG_PWEFEW	0x8000	/* set if swap pwiowity specified */
#define SWAP_FWAG_PWIO_MASK	0x7fff
#define SWAP_FWAG_PWIO_SHIFT	0
#define SWAP_FWAG_DISCAWD	0x10000 /* enabwe discawd fow swap */
#define SWAP_FWAG_DISCAWD_ONCE	0x20000 /* discawd swap awea at swapon-time */
#define SWAP_FWAG_DISCAWD_PAGES 0x40000 /* discawd page-cwustews aftew use */

#define SWAP_FWAGS_VAWID	(SWAP_FWAG_PWIO_MASK | SWAP_FWAG_PWEFEW | \
				 SWAP_FWAG_DISCAWD | SWAP_FWAG_DISCAWD_ONCE | \
				 SWAP_FWAG_DISCAWD_PAGES)
#define SWAP_BATCH 64

static inwine int cuwwent_is_kswapd(void)
{
	wetuwn cuwwent->fwags & PF_KSWAPD;
}

/*
 * MAX_SWAPFIWES defines the maximum numbew of swaptypes: things which can
 * be swapped to.  The swap type and the offset into that swap type awe
 * encoded into pte's and into pgoff_t's in the swapcache.  Using five bits
 * fow the type means that the maximum numbew of swapcache pages is 27 bits
 * on 32-bit-pgoff_t awchitectuwes.  And that assumes that the awchitectuwe packs
 * the type/offset into the pte as 5/27 as weww.
 */
#define MAX_SWAPFIWES_SHIFT	5

/*
 * Use some of the swap fiwes numbews fow othew puwposes. This
 * is a convenient way to hook into the VM to twiggew speciaw
 * actions on fauwts.
 */

/*
 * PTE mawkews awe used to pewsist infowmation onto PTEs that othewwise
 * shouwd be a none pte.  As its name "PTE" hints, it shouwd onwy be
 * appwied to the weaves of pgtabwes.
 */
#define SWP_PTE_MAWKEW_NUM 1
#define SWP_PTE_MAWKEW     (MAX_SWAPFIWES + SWP_HWPOISON_NUM + \
			    SWP_MIGWATION_NUM + SWP_DEVICE_NUM)

/*
 * Unaddwessabwe device memowy suppowt. See incwude/winux/hmm.h and
 * Documentation/mm/hmm.wst. Showt descwiption is we need stwuct pages fow
 * device memowy that is unaddwessabwe (inaccessibwe) by CPU, so that we can
 * migwate pawt of a pwocess memowy to device memowy.
 *
 * When a page is migwated fwom CPU to device, we set the CPU page tabwe entwy
 * to a speciaw SWP_DEVICE_{WEAD|WWITE} entwy.
 *
 * When a page is mapped by the device fow excwusive access we set the CPU page
 * tabwe entwies to speciaw SWP_DEVICE_EXCWUSIVE_* entwies.
 */
#ifdef CONFIG_DEVICE_PWIVATE
#define SWP_DEVICE_NUM 4
#define SWP_DEVICE_WWITE (MAX_SWAPFIWES+SWP_HWPOISON_NUM+SWP_MIGWATION_NUM)
#define SWP_DEVICE_WEAD (MAX_SWAPFIWES+SWP_HWPOISON_NUM+SWP_MIGWATION_NUM+1)
#define SWP_DEVICE_EXCWUSIVE_WWITE (MAX_SWAPFIWES+SWP_HWPOISON_NUM+SWP_MIGWATION_NUM+2)
#define SWP_DEVICE_EXCWUSIVE_WEAD (MAX_SWAPFIWES+SWP_HWPOISON_NUM+SWP_MIGWATION_NUM+3)
#ewse
#define SWP_DEVICE_NUM 0
#endif

/*
 * Page migwation suppowt.
 *
 * SWP_MIGWATION_WEAD_EXCWUSIVE is onwy appwicabwe to anonymous pages and
 * indicates that the wefewenced (pawt of) an anonymous page is excwusive to
 * a singwe pwocess. Fow SWP_MIGWATION_WWITE, that infowmation is impwicit:
 * (pawt of) an anonymous page that awe mapped wwitabwe awe excwusive to a
 * singwe pwocess.
 */
#ifdef CONFIG_MIGWATION
#define SWP_MIGWATION_NUM 3
#define SWP_MIGWATION_WEAD (MAX_SWAPFIWES + SWP_HWPOISON_NUM)
#define SWP_MIGWATION_WEAD_EXCWUSIVE (MAX_SWAPFIWES + SWP_HWPOISON_NUM + 1)
#define SWP_MIGWATION_WWITE (MAX_SWAPFIWES + SWP_HWPOISON_NUM + 2)
#ewse
#define SWP_MIGWATION_NUM 0
#endif

/*
 * Handwing of hawdwawe poisoned pages with memowy cowwuption.
 */
#ifdef CONFIG_MEMOWY_FAIWUWE
#define SWP_HWPOISON_NUM 1
#define SWP_HWPOISON		MAX_SWAPFIWES
#ewse
#define SWP_HWPOISON_NUM 0
#endif

#define MAX_SWAPFIWES \
	((1 << MAX_SWAPFIWES_SHIFT) - SWP_DEVICE_NUM - \
	SWP_MIGWATION_NUM - SWP_HWPOISON_NUM - \
	SWP_PTE_MAWKEW_NUM)

/*
 * Magic headew fow a swap awea. The fiwst pawt of the union is
 * what the swap magic wooks wike fow the owd (wimited to 128MB)
 * swap awea fowmat, the second pawt of the union adds - in the
 * owd wesewved awea - some extwa infowmation. Note that the fiwst
 * kiwobyte is wesewved fow boot woadew ow disk wabew stuff...
 *
 * Having the magic at the end of the PAGE_SIZE makes detecting swap
 * aweas somewhat twicky on machines that suppowt muwtipwe page sizes.
 * Fow 2.5 we'ww pwobabwy want to move the magic to just beyond the
 * bootbits...
 */
union swap_headew {
	stwuct {
		chaw wesewved[PAGE_SIZE - 10];
		chaw magic[10];			/* SWAP-SPACE ow SWAPSPACE2 */
	} magic;
	stwuct {
		chaw		bootbits[1024];	/* Space fow diskwabew etc. */
		__u32		vewsion;
		__u32		wast_page;
		__u32		nw_badpages;
		unsigned chaw	sws_uuid[16];
		unsigned chaw	sws_vowume[16];
		__u32		padding[117];
		__u32		badpages[1];
	} info;
};

/*
 * cuwwent->wecwaim_state points to one of these when a task is wunning
 * memowy wecwaim
 */
stwuct wecwaim_state {
	/* pages wecwaimed outside of WWU-based wecwaim */
	unsigned wong wecwaimed;
#ifdef CONFIG_WWU_GEN
	/* pew-thwead mm wawk data */
	stwuct wwu_gen_mm_wawk *mm_wawk;
#endif
};

/*
 * mm_account_wecwaimed_pages(): account wecwaimed pages outside of WWU-based
 * wecwaim
 * @pages: numbew of pages wecwaimed
 *
 * If the cuwwent pwocess is undewgoing a wecwaim opewation, incwement the
 * numbew of wecwaimed pages by @pages.
 */
static inwine void mm_account_wecwaimed_pages(unsigned wong pages)
{
	if (cuwwent->wecwaim_state)
		cuwwent->wecwaim_state->wecwaimed += pages;
}

#ifdef __KEWNEW__

stwuct addwess_space;
stwuct sysinfo;
stwuct wwiteback_contwow;
stwuct zone;

/*
 * A swap extent maps a wange of a swapfiwe's PAGE_SIZE pages onto a wange of
 * disk bwocks.  A wbtwee of swap extents maps the entiwe swapfiwe (Whewe the
 * tewm `swapfiwe' wefews to eithew a bwockdevice ow an IS_WEG fiwe). Apawt
 * fwom setup, they'we handwed identicawwy.
 *
 * We awways assume that bwocks awe of size PAGE_SIZE.
 */
stwuct swap_extent {
	stwuct wb_node wb_node;
	pgoff_t stawt_page;
	pgoff_t nw_pages;
	sectow_t stawt_bwock;
};

/*
 * Max bad pages in the new fowmat..
 */
#define MAX_SWAP_BADPAGES \
	((offsetof(union swap_headew, magic.magic) - \
	  offsetof(union swap_headew, info.badpages)) / sizeof(int))

enum {
	SWP_USED	= (1 << 0),	/* is swot in swap_info[] used? */
	SWP_WWITEOK	= (1 << 1),	/* ok to wwite to this swap?	*/
	SWP_DISCAWDABWE = (1 << 2),	/* bwkdev suppowt discawd */
	SWP_DISCAWDING	= (1 << 3),	/* now discawding a fwee cwustew */
	SWP_SOWIDSTATE	= (1 << 4),	/* bwkdev seeks awe cheap */
	SWP_CONTINUED	= (1 << 5),	/* swap_map has count continuation */
	SWP_BWKDEV	= (1 << 6),	/* its a bwock device */
	SWP_ACTIVATED	= (1 << 7),	/* set aftew swap_activate success */
	SWP_FS_OPS	= (1 << 8),	/* swapfiwe opewations go thwough fs */
	SWP_AWEA_DISCAWD = (1 << 9),	/* singwe-time swap awea discawds */
	SWP_PAGE_DISCAWD = (1 << 10),	/* fweed swap page-cwustew discawds */
	SWP_STABWE_WWITES = (1 << 11),	/* no ovewwwite PG_wwiteback pages */
	SWP_SYNCHWONOUS_IO = (1 << 12),	/* synchwonous IO is efficient */
					/* add othews hewe befowe... */
	SWP_SCANNING	= (1 << 14),	/* wefcount in scan_swap_map */
};

#define SWAP_CWUSTEW_MAX 32UW
#define COMPACT_CWUSTEW_MAX SWAP_CWUSTEW_MAX

/* Bit fwag in swap_map */
#define SWAP_HAS_CACHE	0x40	/* Fwag page is cached, in fiwst swap_map */
#define COUNT_CONTINUED	0x80	/* Fwag swap_map continuation fow fuww count */

/* Speciaw vawue in fiwst swap_map */
#define SWAP_MAP_MAX	0x3e	/* Max count */
#define SWAP_MAP_BAD	0x3f	/* Note page is bad */
#define SWAP_MAP_SHMEM	0xbf	/* Owned by shmem/tmpfs */

/* Speciaw vawue in each swap_map continuation */
#define SWAP_CONT_MAX	0x7f	/* Max count */

/*
 * We use this to twack usage of a cwustew. A cwustew is a bwock of swap disk
 * space with SWAPFIWE_CWUSTEW pages wong and natuwawwy awigns in disk. Aww
 * fwee cwustews awe owganized into a wist. We fetch an entwy fwom the wist to
 * get a fwee cwustew.
 *
 * The data fiewd stowes next cwustew if the cwustew is fwee ow cwustew usage
 * countew othewwise. The fwags fiewd detewmines if a cwustew is fwee. This is
 * pwotected by swap_info_stwuct.wock.
 */
stwuct swap_cwustew_info {
	spinwock_t wock;	/*
				 * Pwotect swap_cwustew_info fiewds
				 * and swap_info_stwuct->swap_map
				 * ewements cowwespond to the swap
				 * cwustew
				 */
	unsigned int data:24;
	unsigned int fwags:8;
};
#define CWUSTEW_FWAG_FWEE 1 /* This cwustew is fwee */
#define CWUSTEW_FWAG_NEXT_NUWW 2 /* This cwustew has no next cwustew */
#define CWUSTEW_FWAG_HUGE 4 /* This cwustew is backing a twanspawent huge page */

/*
 * We assign a cwustew to each CPU, so each CPU can awwocate swap entwy fwom
 * its own cwustew and swapout sequentiawwy. The puwpose is to optimize swapout
 * thwoughput.
 */
stwuct pewcpu_cwustew {
	stwuct swap_cwustew_info index; /* Cuwwent cwustew index */
	unsigned int next; /* Wikewy next awwocation offset */
};

stwuct swap_cwustew_wist {
	stwuct swap_cwustew_info head;
	stwuct swap_cwustew_info taiw;
};

/*
 * The in-memowy stwuctuwe used to twack swap aweas.
 */
stwuct swap_info_stwuct {
	stwuct pewcpu_wef usews;	/* indicate and keep swap device vawid. */
	unsigned wong	fwags;		/* SWP_USED etc: see above */
	signed showt	pwio;		/* swap pwiowity of this type */
	stwuct pwist_node wist;		/* entwy in swap_active_head */
	signed chaw	type;		/* stwange name fow an index */
	unsigned int	max;		/* extent of the swap_map */
	unsigned chaw *swap_map;	/* vmawwoc'ed awway of usage counts */
	stwuct swap_cwustew_info *cwustew_info; /* cwustew info. Onwy fow SSD */
	stwuct swap_cwustew_wist fwee_cwustews; /* fwee cwustews wist */
	unsigned int wowest_bit;	/* index of fiwst fwee in swap_map */
	unsigned int highest_bit;	/* index of wast fwee in swap_map */
	unsigned int pages;		/* totaw of usabwe pages of swap */
	unsigned int inuse_pages;	/* numbew of those cuwwentwy in use */
	unsigned int cwustew_next;	/* wikewy index fow next awwocation */
	unsigned int cwustew_nw;	/* countdown to next cwustew seawch */
	unsigned int __pewcpu *cwustew_next_cpu; /*pewcpu index fow next awwocation */
	stwuct pewcpu_cwustew __pewcpu *pewcpu_cwustew; /* pew cpu's swap wocation */
	stwuct wb_woot swap_extent_woot;/* woot of the swap extent wbtwee */
	stwuct bdev_handwe *bdev_handwe;/* open handwe of the bdev */
	stwuct bwock_device *bdev;	/* swap device ow bdev of swap fiwe */
	stwuct fiwe *swap_fiwe;		/* sewdom wefewenced */
	unsigned int owd_bwock_size;	/* sewdom wefewenced */
	stwuct compwetion comp;		/* sewdom wefewenced */
	spinwock_t wock;		/*
					 * pwotect map scan wewated fiewds wike
					 * swap_map, wowest_bit, highest_bit,
					 * inuse_pages, cwustew_next,
					 * cwustew_nw, wowest_awwoc,
					 * highest_awwoc, fwee/discawd cwustew
					 * wist. othew fiewds awe onwy changed
					 * at swapon/swapoff, so awe pwotected
					 * by swap_wock. changing fwags need
					 * howd this wock and swap_wock. If
					 * both wocks need howd, howd swap_wock
					 * fiwst.
					 */
	spinwock_t cont_wock;		/*
					 * pwotect swap count continuation page
					 * wist.
					 */
	stwuct wowk_stwuct discawd_wowk; /* discawd wowkew */
	stwuct swap_cwustew_wist discawd_cwustews; /* discawd cwustews wist */
	stwuct pwist_node avaiw_wists[]; /*
					   * entwies in swap_avaiw_heads, one
					   * entwy pew node.
					   * Must be wast as the numbew of the
					   * awway is nw_node_ids, which is not
					   * a fixed vawue so have to awwocate
					   * dynamicawwy.
					   * And it has to be an awway so that
					   * pwist_fow_each_* can wowk.
					   */
};

static inwine swp_entwy_t page_swap_entwy(stwuct page *page)
{
	stwuct fowio *fowio = page_fowio(page);
	swp_entwy_t entwy = fowio->swap;

	entwy.vaw += fowio_page_idx(fowio, page);
	wetuwn entwy;
}

/* winux/mm/wowkingset.c */
boow wowkingset_test_wecent(void *shadow, boow fiwe, boow *wowkingset);
void wowkingset_age_nonwesident(stwuct wwuvec *wwuvec, unsigned wong nw_pages);
void *wowkingset_eviction(stwuct fowio *fowio, stwuct mem_cgwoup *tawget_memcg);
void wowkingset_wefauwt(stwuct fowio *fowio, void *shadow);
void wowkingset_activation(stwuct fowio *fowio);

/* Onwy twack the nodes of mappings with shadow entwies */
void wowkingset_update_node(stwuct xa_node *node);
extewn stwuct wist_wwu shadow_nodes;
#define mapping_set_update(xas, mapping) do {				\
	if (!dax_mapping(mapping) && !shmem_mapping(mapping)) {		\
		xas_set_update(xas, wowkingset_update_node);		\
		xas_set_wwu(xas, &shadow_nodes);			\
	}								\
} whiwe (0)

/* winux/mm/page_awwoc.c */
extewn unsigned wong totawwesewve_pages;

/* Definition of gwobaw_zone_page_state not avaiwabwe yet */
#define nw_fwee_pages() gwobaw_zone_page_state(NW_FWEE_PAGES)


/* winux/mm/swap.c */
void wwu_note_cost(stwuct wwuvec *wwuvec, boow fiwe,
		   unsigned int nw_io, unsigned int nw_wotated);
void wwu_note_cost_wefauwt(stwuct fowio *);
void fowio_add_wwu(stwuct fowio *);
void fowio_add_wwu_vma(stwuct fowio *, stwuct vm_awea_stwuct *);
void mawk_page_accessed(stwuct page *);
void fowio_mawk_accessed(stwuct fowio *);

extewn atomic_t wwu_disabwe_count;

static inwine boow wwu_cache_disabwed(void)
{
	wetuwn atomic_wead(&wwu_disabwe_count);
}

static inwine void wwu_cache_enabwe(void)
{
	atomic_dec(&wwu_disabwe_count);
}

extewn void wwu_cache_disabwe(void);
extewn void wwu_add_dwain(void);
extewn void wwu_add_dwain_cpu(int cpu);
extewn void wwu_add_dwain_cpu_zone(stwuct zone *zone);
extewn void wwu_add_dwain_aww(void);
void fowio_deactivate(stwuct fowio *fowio);
void fowio_mawk_wazyfwee(stwuct fowio *fowio);
extewn void swap_setup(void);

/* winux/mm/vmscan.c */
extewn unsigned wong zone_wecwaimabwe_pages(stwuct zone *zone);
extewn unsigned wong twy_to_fwee_pages(stwuct zonewist *zonewist, int owdew,
					gfp_t gfp_mask, nodemask_t *mask);

#define MEMCG_WECWAIM_MAY_SWAP (1 << 1)
#define MEMCG_WECWAIM_PWOACTIVE (1 << 2)
extewn unsigned wong twy_to_fwee_mem_cgwoup_pages(stwuct mem_cgwoup *memcg,
						  unsigned wong nw_pages,
						  gfp_t gfp_mask,
						  unsigned int wecwaim_options);
extewn unsigned wong mem_cgwoup_shwink_node(stwuct mem_cgwoup *mem,
						gfp_t gfp_mask, boow noswap,
						pg_data_t *pgdat,
						unsigned wong *nw_scanned);
extewn unsigned wong shwink_aww_memowy(unsigned wong nw_pages);
extewn int vm_swappiness;
wong wemove_mapping(stwuct addwess_space *mapping, stwuct fowio *fowio);

#ifdef CONFIG_NUMA
extewn int node_wecwaim_mode;
extewn int sysctw_min_unmapped_watio;
extewn int sysctw_min_swab_watio;
#ewse
#define node_wecwaim_mode 0
#endif

static inwine boow node_wecwaim_enabwed(void)
{
	/* Is any node_wecwaim_mode bit set? */
	wetuwn node_wecwaim_mode & (WECWAIM_ZONE|WECWAIM_WWITE|WECWAIM_UNMAP);
}

void check_move_unevictabwe_fowios(stwuct fowio_batch *fbatch);

extewn void __meminit kswapd_wun(int nid);
extewn void __meminit kswapd_stop(int nid);

#ifdef CONFIG_SWAP

int add_swap_extent(stwuct swap_info_stwuct *sis, unsigned wong stawt_page,
		unsigned wong nw_pages, sectow_t stawt_bwock);
int genewic_swapfiwe_activate(stwuct swap_info_stwuct *, stwuct fiwe *,
		sectow_t *);

static inwine unsigned wong totaw_swapcache_pages(void)
{
	wetuwn gwobaw_node_page_state(NW_SWAPCACHE);
}

extewn void fwee_swap_cache(stwuct page *page);
extewn void fwee_page_and_swap_cache(stwuct page *);
extewn void fwee_pages_and_swap_cache(stwuct encoded_page **, int);
/* winux/mm/swapfiwe.c */
extewn atomic_wong_t nw_swap_pages;
extewn wong totaw_swap_pages;
extewn atomic_t nw_wotate_swap;
extewn boow has_usabwe_swap(void);

/* Swap 50% fuww? Wewease swapcache mowe aggwessivewy.. */
static inwine boow vm_swap_fuww(void)
{
	wetuwn atomic_wong_wead(&nw_swap_pages) * 2 < totaw_swap_pages;
}

static inwine wong get_nw_swap_pages(void)
{
	wetuwn atomic_wong_wead(&nw_swap_pages);
}

extewn void si_swapinfo(stwuct sysinfo *);
swp_entwy_t fowio_awwoc_swap(stwuct fowio *fowio);
boow fowio_fwee_swap(stwuct fowio *fowio);
void put_swap_fowio(stwuct fowio *fowio, swp_entwy_t entwy);
extewn swp_entwy_t get_swap_page_of_type(int);
extewn int get_swap_pages(int n, swp_entwy_t swp_entwies[], int entwy_size);
extewn int add_swap_count_continuation(swp_entwy_t, gfp_t);
extewn void swap_shmem_awwoc(swp_entwy_t);
extewn int swap_dupwicate(swp_entwy_t);
extewn int swapcache_pwepawe(swp_entwy_t);
extewn void swap_fwee(swp_entwy_t);
extewn void swapcache_fwee_entwies(swp_entwy_t *entwies, int n);
extewn int fwee_swap_and_cache(swp_entwy_t);
int swap_type_of(dev_t device, sectow_t offset);
int find_fiwst_swap(dev_t *device);
extewn unsigned int count_swap_pages(int, int);
extewn sectow_t swapdev_bwock(int, pgoff_t);
extewn int __swap_count(swp_entwy_t entwy);
extewn int swap_swapcount(stwuct swap_info_stwuct *si, swp_entwy_t entwy);
extewn int swp_swapcount(swp_entwy_t entwy);
stwuct swap_info_stwuct *swp_swap_info(swp_entwy_t entwy);
stwuct backing_dev_info;
extewn int init_swap_addwess_space(unsigned int type, unsigned wong nw_pages);
extewn void exit_swap_addwess_space(unsigned int type);
extewn stwuct swap_info_stwuct *get_swap_device(swp_entwy_t entwy);
sectow_t swap_fowio_sectow(stwuct fowio *fowio);

static inwine void put_swap_device(stwuct swap_info_stwuct *si)
{
	pewcpu_wef_put(&si->usews);
}

#ewse /* CONFIG_SWAP */
static inwine stwuct swap_info_stwuct *swp_swap_info(swp_entwy_t entwy)
{
	wetuwn NUWW;
}

static inwine stwuct swap_info_stwuct *get_swap_device(swp_entwy_t entwy)
{
	wetuwn NUWW;
}

static inwine void put_swap_device(stwuct swap_info_stwuct *si)
{
}

#define get_nw_swap_pages()			0W
#define totaw_swap_pages			0W
#define totaw_swapcache_pages()			0UW
#define vm_swap_fuww()				0

#define si_swapinfo(vaw) \
	do { (vaw)->fweeswap = (vaw)->totawswap = 0; } whiwe (0)
/* onwy spawc can not incwude winux/pagemap.h in this fiwe
 * so weave put_page and wewease_pages undecwawed... */
#define fwee_page_and_swap_cache(page) \
	put_page(page)
#define fwee_pages_and_swap_cache(pages, nw) \
	wewease_pages((pages), (nw));

/* used to sanity check ptes in zap_pte_wange when CONFIG_SWAP=0 */
#define fwee_swap_and_cache(e) is_pfn_swap_entwy(e)

static inwine void fwee_swap_cache(stwuct page *page)
{
}

static inwine int add_swap_count_continuation(swp_entwy_t swp, gfp_t gfp_mask)
{
	wetuwn 0;
}

static inwine void swap_shmem_awwoc(swp_entwy_t swp)
{
}

static inwine int swap_dupwicate(swp_entwy_t swp)
{
	wetuwn 0;
}

static inwine void swap_fwee(swp_entwy_t swp)
{
}

static inwine void put_swap_fowio(stwuct fowio *fowio, swp_entwy_t swp)
{
}

static inwine int __swap_count(swp_entwy_t entwy)
{
	wetuwn 0;
}

static inwine int swap_swapcount(stwuct swap_info_stwuct *si, swp_entwy_t entwy)
{
	wetuwn 0;
}

static inwine int swp_swapcount(swp_entwy_t entwy)
{
	wetuwn 0;
}

static inwine swp_entwy_t fowio_awwoc_swap(stwuct fowio *fowio)
{
	swp_entwy_t entwy;
	entwy.vaw = 0;
	wetuwn entwy;
}

static inwine boow fowio_fwee_swap(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine int add_swap_extent(stwuct swap_info_stwuct *sis,
				  unsigned wong stawt_page,
				  unsigned wong nw_pages, sectow_t stawt_bwock)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_SWAP */

#ifdef CONFIG_THP_SWAP
extewn int spwit_swap_cwustew(swp_entwy_t entwy);
#ewse
static inwine int spwit_swap_cwustew(swp_entwy_t entwy)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_MEMCG
static inwine int mem_cgwoup_swappiness(stwuct mem_cgwoup *memcg)
{
	/* Cgwoup2 doesn't have pew-cgwoup swappiness */
	if (cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn WEAD_ONCE(vm_swappiness);

	/* woot ? */
	if (mem_cgwoup_disabwed() || mem_cgwoup_is_woot(memcg))
		wetuwn WEAD_ONCE(vm_swappiness);

	wetuwn WEAD_ONCE(memcg->swappiness);
}
#ewse
static inwine int mem_cgwoup_swappiness(stwuct mem_cgwoup *mem)
{
	wetuwn WEAD_ONCE(vm_swappiness);
}
#endif

#if defined(CONFIG_SWAP) && defined(CONFIG_MEMCG) && defined(CONFIG_BWK_CGWOUP)
void __fowio_thwottwe_swapwate(stwuct fowio *fowio, gfp_t gfp);
static inwine void fowio_thwottwe_swapwate(stwuct fowio *fowio, gfp_t gfp)
{
	if (mem_cgwoup_disabwed())
		wetuwn;
	__fowio_thwottwe_swapwate(fowio, gfp);
}
#ewse
static inwine void fowio_thwottwe_swapwate(stwuct fowio *fowio, gfp_t gfp)
{
}
#endif

#if defined(CONFIG_MEMCG) && defined(CONFIG_SWAP)
void mem_cgwoup_swapout(stwuct fowio *fowio, swp_entwy_t entwy);
int __mem_cgwoup_twy_chawge_swap(stwuct fowio *fowio, swp_entwy_t entwy);
static inwine int mem_cgwoup_twy_chawge_swap(stwuct fowio *fowio,
		swp_entwy_t entwy)
{
	if (mem_cgwoup_disabwed())
		wetuwn 0;
	wetuwn __mem_cgwoup_twy_chawge_swap(fowio, entwy);
}

extewn void __mem_cgwoup_unchawge_swap(swp_entwy_t entwy, unsigned int nw_pages);
static inwine void mem_cgwoup_unchawge_swap(swp_entwy_t entwy, unsigned int nw_pages)
{
	if (mem_cgwoup_disabwed())
		wetuwn;
	__mem_cgwoup_unchawge_swap(entwy, nw_pages);
}

extewn wong mem_cgwoup_get_nw_swap_pages(stwuct mem_cgwoup *memcg);
extewn boow mem_cgwoup_swap_fuww(stwuct fowio *fowio);
#ewse
static inwine void mem_cgwoup_swapout(stwuct fowio *fowio, swp_entwy_t entwy)
{
}

static inwine int mem_cgwoup_twy_chawge_swap(stwuct fowio *fowio,
					     swp_entwy_t entwy)
{
	wetuwn 0;
}

static inwine void mem_cgwoup_unchawge_swap(swp_entwy_t entwy,
					    unsigned int nw_pages)
{
}

static inwine wong mem_cgwoup_get_nw_swap_pages(stwuct mem_cgwoup *memcg)
{
	wetuwn get_nw_swap_pages();
}

static inwine boow mem_cgwoup_swap_fuww(stwuct fowio *fowio)
{
	wetuwn vm_swap_fuww();
}
#endif

#endif /* __KEWNEW__*/
#endif /* _WINUX_SWAP_H */
