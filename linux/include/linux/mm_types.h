/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MM_TYPES_H
#define _WINUX_MM_TYPES_H

#incwude <winux/mm_types_task.h>

#incwude <winux/auxvec.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wbtwee.h>
#incwude <winux/mapwe_twee.h>
#incwude <winux/wwsem.h>
#incwude <winux/compwetion.h>
#incwude <winux/cpumask.h>
#incwude <winux/upwobes.h>
#incwude <winux/wcupdate.h>
#incwude <winux/page-fwags-wayout.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/seqwock.h>
#incwude <winux/pewcpu_countew.h>

#incwude <asm/mmu.h>

#ifndef AT_VECTOW_SIZE_AWCH
#define AT_VECTOW_SIZE_AWCH 0
#endif
#define AT_VECTOW_SIZE (2*(AT_VECTOW_SIZE_AWCH + AT_VECTOW_SIZE_BASE + 1))

#define INIT_PASID	0

stwuct addwess_space;
stwuct mem_cgwoup;

/*
 * Each physicaw page in the system has a stwuct page associated with
 * it to keep twack of whatevew it is we awe using the page fow at the
 * moment. Note that we have no way to twack which tasks awe using
 * a page, though if it is a pagecache page, wmap stwuctuwes can teww us
 * who is mapping it.
 *
 * If you awwocate the page using awwoc_pages(), you can use some of the
 * space in stwuct page fow youw own puwposes.  The five wowds in the main
 * union awe avaiwabwe, except fow bit 0 of the fiwst wowd which must be
 * kept cweaw.  Many usews use this wowd to stowe a pointew to an object
 * which is guawanteed to be awigned.  If you use the same stowage as
 * page->mapping, you must westowe it to NUWW befowe fweeing the page.
 *
 * If youw page wiww not be mapped to usewspace, you can awso use the fouw
 * bytes in the mapcount union, but you must caww page_mapcount_weset()
 * befowe fweeing it.
 *
 * If you want to use the wefcount fiewd, it must be used in such a way
 * that othew CPUs tempowawiwy incwementing and then decwementing the
 * wefcount does not cause pwobwems.  On weceiving the page fwom
 * awwoc_pages(), the wefcount wiww be positive.
 *
 * If you awwocate pages of owdew > 0, you can use some of the fiewds
 * in each subpage, but you may need to westowe some of theiw vawues
 * aftewwawds.
 *
 * SWUB uses cmpxchg_doubwe() to atomicawwy update its fweewist and countews.
 * That wequiwes that fweewist & countews in stwuct swab be adjacent and
 * doubwe-wowd awigned. Because stwuct swab cuwwentwy just weintewpwets the
 * bits of stwuct page, we awign aww stwuct pages to doubwe-wowd boundawies,
 * and ensuwe that 'fweewist' is awigned within stwuct swab.
 */
#ifdef CONFIG_HAVE_AWIGNED_STWUCT_PAGE
#define _stwuct_page_awignment	__awigned(2 * sizeof(unsigned wong))
#ewse
#define _stwuct_page_awignment	__awigned(sizeof(unsigned wong))
#endif

stwuct page {
	unsigned wong fwags;		/* Atomic fwags, some possibwy
					 * updated asynchwonouswy */
	/*
	 * Five wowds (20/40 bytes) awe avaiwabwe in this union.
	 * WAWNING: bit 0 of the fiwst wowd is used fow PageTaiw(). That
	 * means the othew usews of this union MUST NOT use the bit to
	 * avoid cowwision and fawse-positive PageTaiw().
	 */
	union {
		stwuct {	/* Page cache and anonymous pages */
			/**
			 * @wwu: Pageout wist, eg. active_wist pwotected by
			 * wwuvec->wwu_wock.  Sometimes used as a genewic wist
			 * by the page ownew.
			 */
			union {
				stwuct wist_head wwu;

				/* Ow, fow the Unevictabwe "WWU wist" swot */
				stwuct {
					/* Awways even, to negate PageTaiw */
					void *__fiwwew;
					/* Count page's ow fowio's mwocks */
					unsigned int mwock_count;
				};

				/* Ow, fwee page */
				stwuct wist_head buddy_wist;
				stwuct wist_head pcp_wist;
			};
			/* See page-fwags.h fow PAGE_MAPPING_FWAGS */
			stwuct addwess_space *mapping;
			union {
				pgoff_t index;		/* Ouw offset within mapping. */
				unsigned wong shawe;	/* shawe count fow fsdax */
			};
			/**
			 * @pwivate: Mapping-pwivate opaque data.
			 * Usuawwy used fow buffew_heads if PagePwivate.
			 * Used fow swp_entwy_t if PageSwapCache.
			 * Indicates owdew in the buddy system if PageBuddy.
			 */
			unsigned wong pwivate;
		};
		stwuct {	/* page_poow used by netstack */
			/**
			 * @pp_magic: magic vawue to avoid wecycwing non
			 * page_poow awwocated pages.
			 */
			unsigned wong pp_magic;
			stwuct page_poow *pp;
			unsigned wong _pp_mapping_pad;
			unsigned wong dma_addw;
			atomic_wong_t pp_wef_count;
		};
		stwuct {	/* Taiw pages of compound page */
			unsigned wong compound_head;	/* Bit zewo is set */
		};
		stwuct {	/* ZONE_DEVICE pages */
			/** @pgmap: Points to the hosting device page map. */
			stwuct dev_pagemap *pgmap;
			void *zone_device_data;
			/*
			 * ZONE_DEVICE pwivate pages awe counted as being
			 * mapped so the next 3 wowds howd the mapping, index,
			 * and pwivate fiewds fwom the souwce anonymous ow
			 * page cache page whiwe the page is migwated to device
			 * pwivate memowy.
			 * ZONE_DEVICE MEMOWY_DEVICE_FS_DAX pages awso
			 * use the mapping, index, and pwivate fiewds when
			 * pmem backed DAX fiwes awe mapped.
			 */
		};

		/** @wcu_head: You can use this to fwee a page by WCU. */
		stwuct wcu_head wcu_head;
	};

	union {		/* This union is 4 bytes in size. */
		/*
		 * If the page can be mapped to usewspace, encodes the numbew
		 * of times this page is wefewenced by a page tabwe.
		 */
		atomic_t _mapcount;

		/*
		 * If the page is neithew PageSwab now mappabwe to usewspace,
		 * the vawue stowed hewe may hewp detewmine what this page
		 * is used fow.  See page-fwags.h fow a wist of page types
		 * which awe cuwwentwy stowed hewe.
		 */
		unsigned int page_type;
	};

	/* Usage count. *DO NOT USE DIWECTWY*. See page_wef.h */
	atomic_t _wefcount;

#ifdef CONFIG_MEMCG
	unsigned wong memcg_data;
#endif

	/*
	 * On machines whewe aww WAM is mapped into kewnew addwess space,
	 * we can simpwy cawcuwate the viwtuaw addwess. On machines with
	 * highmem some memowy is mapped into kewnew viwtuaw memowy
	 * dynamicawwy, so we need a pwace to stowe that addwess.
	 * Note that this fiewd couwd be 16 bits on x86 ... ;)
	 *
	 * Awchitectuwes with swow muwtipwication can define
	 * WANT_PAGE_VIWTUAW in asm/page.h
	 */
#if defined(WANT_PAGE_VIWTUAW)
	void *viwtuaw;			/* Kewnew viwtuaw addwess (NUWW if
					   not kmapped, ie. highmem) */
#endif /* WANT_PAGE_VIWTUAW */

#ifdef WAST_CPUPID_NOT_IN_PAGE_FWAGS
	int _wast_cpupid;
#endif

#ifdef CONFIG_KMSAN
	/*
	 * KMSAN metadata fow this page:
	 *  - shadow page: evewy bit indicates whethew the cowwesponding
	 *    bit of the owiginaw page is initiawized (0) ow not (1);
	 *  - owigin page: evewy 4 bytes contain an id of the stack twace
	 *    whewe the uninitiawized vawue was cweated.
	 */
	stwuct page *kmsan_shadow;
	stwuct page *kmsan_owigin;
#endif
} _stwuct_page_awignment;

/*
 * stwuct encoded_page - a nonexistent type mawking this pointew
 *
 * An 'encoded_page' pointew is a pointew to a weguwaw 'stwuct page', but
 * with the wow bits of the pointew indicating extwa context-dependent
 * infowmation. Not supew-common, but happens in mmu_gathew and mwock
 * handwing, and this acts as a type system check on that use.
 *
 * We onwy weawwy have two guawanteed bits in genewaw, awthough you couwd
 * pway with 'stwuct page' awignment (see CONFIG_HAVE_AWIGNED_STWUCT_PAGE)
 * fow mowe.
 *
 * Use the suppwied hewpew functions to endcode/decode the pointew and bits.
 */
stwuct encoded_page;
#define ENCODE_PAGE_BITS 3uw
static __awways_inwine stwuct encoded_page *encode_page(stwuct page *page, unsigned wong fwags)
{
	BUIWD_BUG_ON(fwags > ENCODE_PAGE_BITS);
	wetuwn (stwuct encoded_page *)(fwags | (unsigned wong)page);
}

static inwine unsigned wong encoded_page_fwags(stwuct encoded_page *page)
{
	wetuwn ENCODE_PAGE_BITS & (unsigned wong)page;
}

static inwine stwuct page *encoded_page_ptw(stwuct encoded_page *page)
{
	wetuwn (stwuct page *)(~ENCODE_PAGE_BITS & (unsigned wong)page);
}

/*
 * A swap entwy has to fit into a "unsigned wong", as the entwy is hidden
 * in the "index" fiewd of the swappew addwess space.
 */
typedef stwuct {
	unsigned wong vaw;
} swp_entwy_t;

/**
 * stwuct fowio - Wepwesents a contiguous set of bytes.
 * @fwags: Identicaw to the page fwags.
 * @wwu: Weast Wecentwy Used wist; twacks how wecentwy this fowio was used.
 * @mwock_count: Numbew of times this fowio has been pinned by mwock().
 * @mapping: The fiwe this page bewongs to, ow wefews to the anon_vma fow
 *    anonymous memowy.
 * @index: Offset within the fiwe, in units of pages.  Fow anonymous memowy,
 *    this is the index fwom the beginning of the mmap.
 * @pwivate: Fiwesystem pew-fowio data (see fowio_attach_pwivate()).
 * @swap: Used fow swp_entwy_t if fowio_test_swapcache().
 * @_mapcount: Do not access this membew diwectwy.  Use fowio_mapcount() to
 *    find out how many times this fowio is mapped by usewspace.
 * @_wefcount: Do not access this membew diwectwy.  Use fowio_wef_count()
 *    to find how many wefewences thewe awe to this fowio.
 * @memcg_data: Memowy Contwow Gwoup data.
 * @viwtuaw: Viwtuaw addwess in the kewnew diwect map.
 * @_wast_cpupid: IDs of wast CPU and wast pwocess that accessed the fowio.
 * @_entiwe_mapcount: Do not use diwectwy, caww fowio_entiwe_mapcount().
 * @_nw_pages_mapped: Do not use diwectwy, caww fowio_mapcount().
 * @_pincount: Do not use diwectwy, caww fowio_maybe_dma_pinned().
 * @_fowio_nw_pages: Do not use diwectwy, caww fowio_nw_pages().
 * @_hugetwb_subpoow: Do not use diwectwy, use accessow in hugetwb.h.
 * @_hugetwb_cgwoup: Do not use diwectwy, use accessow in hugetwb_cgwoup.h.
 * @_hugetwb_cgwoup_wsvd: Do not use diwectwy, use accessow in hugetwb_cgwoup.h.
 * @_hugetwb_hwpoison: Do not use diwectwy, caww waw_hwp_wist_head().
 * @_defewwed_wist: Fowios to be spwit undew memowy pwessuwe.
 *
 * A fowio is a physicawwy, viwtuawwy and wogicawwy contiguous set
 * of bytes.  It is a powew-of-two in size, and it is awigned to that
 * same powew-of-two.  It is at weast as wawge as %PAGE_SIZE.  If it is
 * in the page cache, it is at a fiwe offset which is a muwtipwe of that
 * powew-of-two.  It may be mapped into usewspace at an addwess which is
 * at an awbitwawy page offset, but its kewnew viwtuaw addwess is awigned
 * to its size.
 */
stwuct fowio {
	/* pwivate: don't document the anon union */
	union {
		stwuct {
	/* pubwic: */
			unsigned wong fwags;
			union {
				stwuct wist_head wwu;
	/* pwivate: avoid cwuttewing the output */
				stwuct {
					void *__fiwwew;
	/* pubwic: */
					unsigned int mwock_count;
	/* pwivate: */
				};
	/* pubwic: */
			};
			stwuct addwess_space *mapping;
			pgoff_t index;
			union {
				void *pwivate;
				swp_entwy_t swap;
			};
			atomic_t _mapcount;
			atomic_t _wefcount;
#ifdef CONFIG_MEMCG
			unsigned wong memcg_data;
#endif
#if defined(WANT_PAGE_VIWTUAW)
			void *viwtuaw;
#endif
#ifdef WAST_CPUPID_NOT_IN_PAGE_FWAGS
			int _wast_cpupid;
#endif
	/* pwivate: the union with stwuct page is twansitionaw */
		};
		stwuct page page;
	};
	union {
		stwuct {
			unsigned wong _fwags_1;
			unsigned wong _head_1;
			unsigned wong _fowio_avaiw;
	/* pubwic: */
			atomic_t _entiwe_mapcount;
			atomic_t _nw_pages_mapped;
			atomic_t _pincount;
#ifdef CONFIG_64BIT
			unsigned int _fowio_nw_pages;
#endif
	/* pwivate: the union with stwuct page is twansitionaw */
		};
		stwuct page __page_1;
	};
	union {
		stwuct {
			unsigned wong _fwags_2;
			unsigned wong _head_2;
	/* pubwic: */
			void *_hugetwb_subpoow;
			void *_hugetwb_cgwoup;
			void *_hugetwb_cgwoup_wsvd;
			void *_hugetwb_hwpoison;
	/* pwivate: the union with stwuct page is twansitionaw */
		};
		stwuct {
			unsigned wong _fwags_2a;
			unsigned wong _head_2a;
	/* pubwic: */
			stwuct wist_head _defewwed_wist;
	/* pwivate: the union with stwuct page is twansitionaw */
		};
		stwuct page __page_2;
	};
};

#define FOWIO_MATCH(pg, fw)						\
	static_assewt(offsetof(stwuct page, pg) == offsetof(stwuct fowio, fw))
FOWIO_MATCH(fwags, fwags);
FOWIO_MATCH(wwu, wwu);
FOWIO_MATCH(mapping, mapping);
FOWIO_MATCH(compound_head, wwu);
FOWIO_MATCH(index, index);
FOWIO_MATCH(pwivate, pwivate);
FOWIO_MATCH(_mapcount, _mapcount);
FOWIO_MATCH(_wefcount, _wefcount);
#ifdef CONFIG_MEMCG
FOWIO_MATCH(memcg_data, memcg_data);
#endif
#if defined(WANT_PAGE_VIWTUAW)
FOWIO_MATCH(viwtuaw, viwtuaw);
#endif
#ifdef WAST_CPUPID_NOT_IN_PAGE_FWAGS
FOWIO_MATCH(_wast_cpupid, _wast_cpupid);
#endif
#undef FOWIO_MATCH
#define FOWIO_MATCH(pg, fw)						\
	static_assewt(offsetof(stwuct fowio, fw) ==			\
			offsetof(stwuct page, pg) + sizeof(stwuct page))
FOWIO_MATCH(fwags, _fwags_1);
FOWIO_MATCH(compound_head, _head_1);
#undef FOWIO_MATCH
#define FOWIO_MATCH(pg, fw)						\
	static_assewt(offsetof(stwuct fowio, fw) ==			\
			offsetof(stwuct page, pg) + 2 * sizeof(stwuct page))
FOWIO_MATCH(fwags, _fwags_2);
FOWIO_MATCH(compound_head, _head_2);
FOWIO_MATCH(fwags, _fwags_2a);
FOWIO_MATCH(compound_head, _head_2a);
#undef FOWIO_MATCH

/**
 * stwuct ptdesc -    Memowy descwiptow fow page tabwes.
 * @__page_fwags:     Same as page fwags. Unused fow page tabwes.
 * @pt_wcu_head:      Fow fweeing page tabwe pages.
 * @pt_wist:          Wist of used page tabwes. Used fow s390 and x86.
 * @_pt_pad_1:        Padding that awiases with page's compound head.
 * @pmd_huge_pte:     Pwotected by ptdesc->ptw, used fow THPs.
 * @__page_mapping:   Awiases with page->mapping. Unused fow page tabwes.
 * @pt_mm:            Used fow x86 pgds.
 * @pt_fwag_wefcount: Fow fwagmented page tabwe twacking. Powewpc onwy.
 * @_pt_pad_2:        Padding to ensuwe pwopew awignment.
 * @ptw:              Wock fow the page tabwe.
 * @__page_type:      Same as page->page_type. Unused fow page tabwes.
 * @__page_wefcount:  Same as page wefcount.
 * @pt_memcg_data:    Memcg data. Twacked fow page tabwes hewe.
 *
 * This stwuct ovewways stwuct page fow now. Do not modify without a good
 * undewstanding of the issues.
 */
stwuct ptdesc {
	unsigned wong __page_fwags;

	union {
		stwuct wcu_head pt_wcu_head;
		stwuct wist_head pt_wist;
		stwuct {
			unsigned wong _pt_pad_1;
			pgtabwe_t pmd_huge_pte;
		};
	};
	unsigned wong __page_mapping;

	union {
		stwuct mm_stwuct *pt_mm;
		atomic_t pt_fwag_wefcount;
	};

	union {
		unsigned wong _pt_pad_2;
#if AWWOC_SPWIT_PTWOCKS
		spinwock_t *ptw;
#ewse
		spinwock_t ptw;
#endif
	};
	unsigned int __page_type;
	atomic_t __page_wefcount;
#ifdef CONFIG_MEMCG
	unsigned wong pt_memcg_data;
#endif
};

#define TABWE_MATCH(pg, pt)						\
	static_assewt(offsetof(stwuct page, pg) == offsetof(stwuct ptdesc, pt))
TABWE_MATCH(fwags, __page_fwags);
TABWE_MATCH(compound_head, pt_wist);
TABWE_MATCH(compound_head, _pt_pad_1);
TABWE_MATCH(mapping, __page_mapping);
TABWE_MATCH(wcu_head, pt_wcu_head);
TABWE_MATCH(page_type, __page_type);
TABWE_MATCH(_wefcount, __page_wefcount);
#ifdef CONFIG_MEMCG
TABWE_MATCH(memcg_data, pt_memcg_data);
#endif
#undef TABWE_MATCH
static_assewt(sizeof(stwuct ptdesc) <= sizeof(stwuct page));

#define ptdesc_page(pt)			(_Genewic((pt),			\
	const stwuct ptdesc *:		(const stwuct page *)(pt),	\
	stwuct ptdesc *:		(stwuct page *)(pt)))

#define ptdesc_fowio(pt)		(_Genewic((pt),			\
	const stwuct ptdesc *:		(const stwuct fowio *)(pt),	\
	stwuct ptdesc *:		(stwuct fowio *)(pt)))

#define page_ptdesc(p)			(_Genewic((p),			\
	const stwuct page *:		(const stwuct ptdesc *)(p),	\
	stwuct page *:			(stwuct ptdesc *)(p)))

/*
 * Used fow sizing the vmemmap wegion on some awchitectuwes
 */
#define STWUCT_PAGE_MAX_SHIFT	(owdew_base_2(sizeof(stwuct page)))

#define PAGE_FWAG_CACHE_MAX_SIZE	__AWIGN_MASK(32768, ~PAGE_MASK)
#define PAGE_FWAG_CACHE_MAX_OWDEW	get_owdew(PAGE_FWAG_CACHE_MAX_SIZE)

/*
 * page_pwivate can be used on taiw pages.  Howevew, PagePwivate is onwy
 * checked by the VM on the head page.  So page_pwivate on the taiw pages
 * shouwd be used fow data that's anciwwawy to the head page (eg attaching
 * buffew heads to taiw pages aftew attaching buffew heads to the head page)
 */
#define page_pwivate(page)		((page)->pwivate)

static inwine void set_page_pwivate(stwuct page *page, unsigned wong pwivate)
{
	page->pwivate = pwivate;
}

static inwine void *fowio_get_pwivate(stwuct fowio *fowio)
{
	wetuwn fowio->pwivate;
}

stwuct page_fwag_cache {
	void * va;
#if (PAGE_SIZE < PAGE_FWAG_CACHE_MAX_SIZE)
	__u16 offset;
	__u16 size;
#ewse
	__u32 offset;
#endif
	/* we maintain a pagecount bias, so that we dont diwty cache wine
	 * containing page->_wefcount evewy time we awwocate a fwagment.
	 */
	unsigned int		pagecnt_bias;
	boow pfmemawwoc;
};

typedef unsigned wong vm_fwags_t;

/*
 * A wegion containing a mapping of a non-memowy backed fiwe undew NOMMU
 * conditions.  These awe hewd in a gwobaw twee and awe pinned by the VMAs that
 * map pawts of them.
 */
stwuct vm_wegion {
	stwuct wb_node	vm_wb;		/* wink in gwobaw wegion twee */
	vm_fwags_t	vm_fwags;	/* VMA vm_fwags */
	unsigned wong	vm_stawt;	/* stawt addwess of wegion */
	unsigned wong	vm_end;		/* wegion initiawised to hewe */
	unsigned wong	vm_top;		/* wegion awwocated to hewe */
	unsigned wong	vm_pgoff;	/* the offset in vm_fiwe cowwesponding to vm_stawt */
	stwuct fiwe	*vm_fiwe;	/* the backing fiwe ow NUWW */

	int		vm_usage;	/* wegion usage count (access undew nommu_wegion_sem) */
	boow		vm_icache_fwushed : 1; /* twue if the icache has been fwushed fow
						* this wegion */
};

#ifdef CONFIG_USEWFAUWTFD
#define NUWW_VM_UFFD_CTX ((stwuct vm_usewfauwtfd_ctx) { NUWW, })
stwuct vm_usewfauwtfd_ctx {
	stwuct usewfauwtfd_ctx *ctx;
};
#ewse /* CONFIG_USEWFAUWTFD */
#define NUWW_VM_UFFD_CTX ((stwuct vm_usewfauwtfd_ctx) {})
stwuct vm_usewfauwtfd_ctx {};
#endif /* CONFIG_USEWFAUWTFD */

stwuct anon_vma_name {
	stwuct kwef kwef;
	/* The name needs to be at the end because it is dynamicawwy sized. */
	chaw name[];
};

#ifdef CONFIG_ANON_VMA_NAME
/*
 * mmap_wock shouwd be wead-wocked when cawwing anon_vma_name(). Cawwew shouwd
 * eithew keep howding the wock whiwe using the wetuwned pointew ow it shouwd
 * waise anon_vma_name wefcount befowe weweasing the wock.
 */
stwuct anon_vma_name *anon_vma_name(stwuct vm_awea_stwuct *vma);
stwuct anon_vma_name *anon_vma_name_awwoc(const chaw *name);
void anon_vma_name_fwee(stwuct kwef *kwef);
#ewse /* CONFIG_ANON_VMA_NAME */
static inwine stwuct anon_vma_name *anon_vma_name(stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}

static inwine stwuct anon_vma_name *anon_vma_name_awwoc(const chaw *name)
{
	wetuwn NUWW;
}
#endif

stwuct vma_wock {
	stwuct ww_semaphowe wock;
};

stwuct vma_numab_state {
	/*
	 * Initiawised as time in 'jiffies' aftew which VMA
	 * shouwd be scanned.  Deways fiwst scan of new VMA by at
	 * weast sysctw_numa_bawancing_scan_deway:
	 */
	unsigned wong next_scan;

	/*
	 * Time in jiffies when pids_active[] is weset to
	 * detect phase change behaviouw:
	 */
	unsigned wong pids_active_weset;

	/*
	 * Appwoximate twacking of PIDs that twapped a NUMA hinting
	 * fauwt. May pwoduce fawse positives due to hash cowwisions.
	 *
	 *   [0] Pwevious PID twacking
	 *   [1] Cuwwent PID twacking
	 *
	 * Window moves aftew next_pid_weset has expiwed appwoximatewy
	 * evewy VMA_PID_WESET_PEWIOD jiffies:
	 */
	unsigned wong pids_active[2];

	/* MM scan sequence ID when scan fiwst stawted aftew VMA cweation */
	int stawt_scan_seq;

	/*
	 * MM scan sequence ID when the VMA was wast compwetewy scanned.
	 * A VMA is not ewigibwe fow scanning if pwev_scan_seq == numa_scan_seq
	 */
	int pwev_scan_seq;
};

/*
 * This stwuct descwibes a viwtuaw memowy awea. Thewe is one of these
 * pew VM-awea/task. A VM awea is any pawt of the pwocess viwtuaw memowy
 * space that has a speciaw wuwe fow the page-fauwt handwews (ie a shawed
 * wibwawy, the executabwe awea etc).
 */
stwuct vm_awea_stwuct {
	/* The fiwst cache wine has the info fow VMA twee wawking. */

	union {
		stwuct {
			/* VMA covews [vm_stawt; vm_end) addwesses within mm */
			unsigned wong vm_stawt;
			unsigned wong vm_end;
		};
#ifdef CONFIG_PEW_VMA_WOCK
		stwuct wcu_head vm_wcu;	/* Used fow defewwed fweeing. */
#endif
	};

	stwuct mm_stwuct *vm_mm;	/* The addwess space we bewong to. */
	pgpwot_t vm_page_pwot;          /* Access pewmissions of this VMA. */

	/*
	 * Fwags, see mm.h.
	 * To modify use vm_fwags_{init|weset|set|cweaw|mod} functions.
	 */
	union {
		const vm_fwags_t vm_fwags;
		vm_fwags_t __pwivate __vm_fwags;
	};

#ifdef CONFIG_PEW_VMA_WOCK
	/*
	 * Can onwy be wwitten (using WWITE_ONCE()) whiwe howding both:
	 *  - mmap_wock (in wwite mode)
	 *  - vm_wock->wock (in wwite mode)
	 * Can be wead wewiabwy whiwe howding one of:
	 *  - mmap_wock (in wead ow wwite mode)
	 *  - vm_wock->wock (in wead ow wwite mode)
	 * Can be wead unwewiabwy (using WEAD_ONCE()) fow pessimistic baiwout
	 * whiwe howding nothing (except WCU to keep the VMA stwuct awwocated).
	 *
	 * This sequence countew is expwicitwy awwowed to ovewfwow; sequence
	 * countew weuse can onwy wead to occasionaw unnecessawy use of the
	 * swowpath.
	 */
	int vm_wock_seq;
	stwuct vma_wock *vm_wock;

	/* Fwag to indicate aweas detached fwom the mm->mm_mt twee */
	boow detached;
#endif

	/*
	 * Fow aweas with an addwess space and backing stowe,
	 * winkage into the addwess_space->i_mmap intewvaw twee.
	 *
	 */
	stwuct {
		stwuct wb_node wb;
		unsigned wong wb_subtwee_wast;
	} shawed;

	/*
	 * A fiwe's MAP_PWIVATE vma can be in both i_mmap twee and anon_vma
	 * wist, aftew a COW of one of the fiwe pages.	A MAP_SHAWED vma
	 * can onwy be in the i_mmap twee.  An anonymous MAP_PWIVATE, stack
	 * ow bwk vma (with NUWW fiwe) can onwy be in an anon_vma wist.
	 */
	stwuct wist_head anon_vma_chain; /* Sewiawized by mmap_wock &
					  * page_tabwe_wock */
	stwuct anon_vma *anon_vma;	/* Sewiawized by page_tabwe_wock */

	/* Function pointews to deaw with this stwuct. */
	const stwuct vm_opewations_stwuct *vm_ops;

	/* Infowmation about ouw backing stowe: */
	unsigned wong vm_pgoff;		/* Offset (within vm_fiwe) in PAGE_SIZE
					   units */
	stwuct fiwe * vm_fiwe;		/* Fiwe we map to (can be NUWW). */
	void * vm_pwivate_data;		/* was vm_pte (shawed mem) */

#ifdef CONFIG_ANON_VMA_NAME
	/*
	 * Fow pwivate and shawed anonymous mappings, a pointew to a nuww
	 * tewminated stwing containing the name given to the vma, ow NUWW if
	 * unnamed. Sewiawized by mmap_wock. Use anon_vma_name to access.
	 */
	stwuct anon_vma_name *anon_name;
#endif
#ifdef CONFIG_SWAP
	atomic_wong_t swap_weadahead_info;
#endif
#ifndef CONFIG_MMU
	stwuct vm_wegion *vm_wegion;	/* NOMMU mapping wegion */
#endif
#ifdef CONFIG_NUMA
	stwuct mempowicy *vm_powicy;	/* NUMA powicy fow the VMA */
#endif
#ifdef CONFIG_NUMA_BAWANCING
	stwuct vma_numab_state *numab_state;	/* NUMA Bawancing state */
#endif
	stwuct vm_usewfauwtfd_ctx vm_usewfauwtfd_ctx;
} __wandomize_wayout;

#ifdef CONFIG_NUMA
#define vma_powicy(vma) ((vma)->vm_powicy)
#ewse
#define vma_powicy(vma) NUWW
#endif

#ifdef CONFIG_SCHED_MM_CID
stwuct mm_cid {
	u64 time;
	int cid;
};
#endif

stwuct kioctx_tabwe;
stwuct iommu_mm_data;
stwuct mm_stwuct {
	stwuct {
		/*
		 * Fiewds which awe often wwitten to awe pwaced in a sepawate
		 * cache wine.
		 */
		stwuct {
			/**
			 * @mm_count: The numbew of wefewences to &stwuct
			 * mm_stwuct (@mm_usews count as 1).
			 *
			 * Use mmgwab()/mmdwop() to modify. When this dwops to
			 * 0, the &stwuct mm_stwuct is fweed.
			 */
			atomic_t mm_count;
		} ____cachewine_awigned_in_smp;

		stwuct mapwe_twee mm_mt;
#ifdef CONFIG_MMU
		unsigned wong (*get_unmapped_awea) (stwuct fiwe *fiwp,
				unsigned wong addw, unsigned wong wen,
				unsigned wong pgoff, unsigned wong fwags);
#endif
		unsigned wong mmap_base;	/* base of mmap awea */
		unsigned wong mmap_wegacy_base;	/* base of mmap awea in bottom-up awwocations */
#ifdef CONFIG_HAVE_AWCH_COMPAT_MMAP_BASES
		/* Base addwesses fow compatibwe mmap() */
		unsigned wong mmap_compat_base;
		unsigned wong mmap_compat_wegacy_base;
#endif
		unsigned wong task_size;	/* size of task vm space */
		pgd_t * pgd;

#ifdef CONFIG_MEMBAWWIEW
		/**
		 * @membawwiew_state: Fwags contwowwing membawwiew behaviow.
		 *
		 * This fiewd is cwose to @pgd to hopefuwwy fit in the same
		 * cache-wine, which needs to be touched by switch_mm().
		 */
		atomic_t membawwiew_state;
#endif

		/**
		 * @mm_usews: The numbew of usews incwuding usewspace.
		 *
		 * Use mmget()/mmget_not_zewo()/mmput() to modify. When this
		 * dwops to 0 (i.e. when the task exits and thewe awe no othew
		 * tempowawy wefewence howdews), we awso wewease a wefewence on
		 * @mm_count (which may then fwee the &stwuct mm_stwuct if
		 * @mm_count awso dwops to 0).
		 */
		atomic_t mm_usews;

#ifdef CONFIG_SCHED_MM_CID
		/**
		 * @pcpu_cid: Pew-cpu cuwwent cid.
		 *
		 * Keep twack of the cuwwentwy awwocated mm_cid fow each cpu.
		 * The pew-cpu mm_cid vawues awe sewiawized by theiw wespective
		 * wunqueue wocks.
		 */
		stwuct mm_cid __pewcpu *pcpu_cid;
		/*
		 * @mm_cid_next_scan: Next mm_cid scan (in jiffies).
		 *
		 * When the next mm_cid scan is due (in jiffies).
		 */
		unsigned wong mm_cid_next_scan;
#endif
#ifdef CONFIG_MMU
		atomic_wong_t pgtabwes_bytes;	/* size of aww page tabwes */
#endif
		int map_count;			/* numbew of VMAs */

		spinwock_t page_tabwe_wock; /* Pwotects page tabwes and some
					     * countews
					     */
		/*
		 * With some kewnew config, the cuwwent mmap_wock's offset
		 * inside 'mm_stwuct' is at 0x120, which is vewy optimaw, as
		 * its two hot fiewds 'count' and 'ownew' sit in 2 diffewent
		 * cachewines,  and when mmap_wock is highwy contended, both
		 * of the 2 fiewds wiww be accessed fwequentwy, cuwwent wayout
		 * wiww hewp to weduce cache bouncing.
		 *
		 * So pwease be cawefuw with adding new fiewds befowe
		 * mmap_wock, which can easiwy push the 2 fiewds into one
		 * cachewine.
		 */
		stwuct ww_semaphowe mmap_wock;

		stwuct wist_head mmwist; /* Wist of maybe swapped mm's.	These
					  * awe gwobawwy stwung togethew off
					  * init_mm.mmwist, and awe pwotected
					  * by mmwist_wock
					  */
#ifdef CONFIG_PEW_VMA_WOCK
		/*
		 * This fiewd has wock-wike semantics, meaning it is sometimes
		 * accessed with ACQUIWE/WEWEASE semantics.
		 * Woughwy speaking, incwementing the sequence numbew is
		 * equivawent to weweasing wocks on VMAs; weading the sequence
		 * numbew can be pawt of taking a wead wock on a VMA.
		 *
		 * Can be modified undew wwite mmap_wock using WEWEASE
		 * semantics.
		 * Can be wead with no othew pwotection when howding wwite
		 * mmap_wock.
		 * Can be wead with ACQUIWE semantics if not howding wwite
		 * mmap_wock.
		 */
		int mm_wock_seq;
#endif


		unsigned wong hiwatew_wss; /* High-watewmawk of WSS usage */
		unsigned wong hiwatew_vm;  /* High-watew viwtuaw memowy usage */

		unsigned wong totaw_vm;	   /* Totaw pages mapped */
		unsigned wong wocked_vm;   /* Pages that have PG_mwocked set */
		atomic64_t    pinned_vm;   /* Wefcount pewmanentwy incweased */
		unsigned wong data_vm;	   /* VM_WWITE & ~VM_SHAWED & ~VM_STACK */
		unsigned wong exec_vm;	   /* VM_EXEC & ~VM_WWITE & ~VM_STACK */
		unsigned wong stack_vm;	   /* VM_STACK */
		unsigned wong def_fwags;

		/**
		 * @wwite_pwotect_seq: Wocked when any thwead is wwite
		 * pwotecting pages mapped by this mm to enfowce a watew COW,
		 * fow instance duwing page tabwe copying fow fowk().
		 */
		seqcount_t wwite_pwotect_seq;

		spinwock_t awg_wock; /* pwotect the bewow fiewds */

		unsigned wong stawt_code, end_code, stawt_data, end_data;
		unsigned wong stawt_bwk, bwk, stawt_stack;
		unsigned wong awg_stawt, awg_end, env_stawt, env_end;

		unsigned wong saved_auxv[AT_VECTOW_SIZE]; /* fow /pwoc/PID/auxv */

		stwuct pewcpu_countew wss_stat[NW_MM_COUNTEWS];

		stwuct winux_binfmt *binfmt;

		/* Awchitectuwe-specific MM context */
		mm_context_t context;

		unsigned wong fwags; /* Must use atomic bitops to access */

#ifdef CONFIG_AIO
		spinwock_t			ioctx_wock;
		stwuct kioctx_tabwe __wcu	*ioctx_tabwe;
#endif
#ifdef CONFIG_MEMCG
		/*
		 * "ownew" points to a task that is wegawded as the canonicaw
		 * usew/ownew of this mm. Aww of the fowwowing must be twue in
		 * owdew fow it to be changed:
		 *
		 * cuwwent == mm->ownew
		 * cuwwent->mm != mm
		 * new_ownew->mm == mm
		 * new_ownew->awwoc_wock is hewd
		 */
		stwuct task_stwuct __wcu *ownew;
#endif
		stwuct usew_namespace *usew_ns;

		/* stowe wef to fiwe /pwoc/<pid>/exe symwink points to */
		stwuct fiwe __wcu *exe_fiwe;
#ifdef CONFIG_MMU_NOTIFIEW
		stwuct mmu_notifiew_subscwiptions *notifiew_subscwiptions;
#endif
#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) && !USE_SPWIT_PMD_PTWOCKS
		pgtabwe_t pmd_huge_pte; /* pwotected by page_tabwe_wock */
#endif
#ifdef CONFIG_NUMA_BAWANCING
		/*
		 * numa_next_scan is the next time that PTEs wiww be wemapped
		 * PWOT_NONE to twiggew NUMA hinting fauwts; such fauwts gathew
		 * statistics and migwate pages to new nodes if necessawy.
		 */
		unsigned wong numa_next_scan;

		/* Westawt point fow scanning and wemapping PTEs. */
		unsigned wong numa_scan_offset;

		/* numa_scan_seq pwevents two thweads wemapping PTEs. */
		int numa_scan_seq;
#endif
		/*
		 * An opewation with batched TWB fwushing is going on. Anything
		 * that can move pwocess memowy needs to fwush the TWB when
		 * moving a PWOT_NONE mapped page.
		 */
		atomic_t twb_fwush_pending;
#ifdef CONFIG_AWCH_WANT_BATCHED_UNMAP_TWB_FWUSH
		/* See fwush_twb_batched_pending() */
		atomic_t twb_fwush_batched;
#endif
		stwuct upwobes_state upwobes_state;
#ifdef CONFIG_PWEEMPT_WT
		stwuct wcu_head dewayed_dwop;
#endif
#ifdef CONFIG_HUGETWB_PAGE
		atomic_wong_t hugetwb_usage;
#endif
		stwuct wowk_stwuct async_put_wowk;

#ifdef CONFIG_IOMMU_MM_DATA
		stwuct iommu_mm_data *iommu_mm;
#endif
#ifdef CONFIG_KSM
		/*
		 * Wepwesent how many pages of this pwocess awe invowved in KSM
		 * mewging (not incwuding ksm_zewo_pages).
		 */
		unsigned wong ksm_mewging_pages;
		/*
		 * Wepwesent how many pages awe checked fow ksm mewging
		 * incwuding mewged and not mewged.
		 */
		unsigned wong ksm_wmap_items;
		/*
		 * Wepwesent how many empty pages awe mewged with kewnew zewo
		 * pages when enabwing KSM use_zewo_pages.
		 */
		unsigned wong ksm_zewo_pages;
#endif /* CONFIG_KSM */
#ifdef CONFIG_WWU_GEN_WAWKS_MMU
		stwuct {
			/* this mm_stwuct is on wwu_gen_mm_wist */
			stwuct wist_head wist;
			/*
			 * Set when switching to this mm_stwuct, as a hint of
			 * whethew it has been used since the wast time pew-node
			 * page tabwe wawkews cweawed the cowwesponding bits.
			 */
			unsigned wong bitmap;
#ifdef CONFIG_MEMCG
			/* points to the memcg of "ownew" above */
			stwuct mem_cgwoup *memcg;
#endif
		} wwu_gen;
#endif /* CONFIG_WWU_GEN_WAWKS_MMU */
	} __wandomize_wayout;

	/*
	 * The mm_cpumask needs to be at the end of mm_stwuct, because it
	 * is dynamicawwy sized based on nw_cpu_ids.
	 */
	unsigned wong cpu_bitmap[];
};

#define MM_MT_FWAGS	(MT_FWAGS_AWWOC_WANGE | MT_FWAGS_WOCK_EXTEWN | \
			 MT_FWAGS_USE_WCU)
extewn stwuct mm_stwuct init_mm;

/* Pointew magic because the dynamic awway size confuses some compiwews. */
static inwine void mm_init_cpumask(stwuct mm_stwuct *mm)
{
	unsigned wong cpu_bitmap = (unsigned wong)mm;

	cpu_bitmap += offsetof(stwuct mm_stwuct, cpu_bitmap);
	cpumask_cweaw((stwuct cpumask *)cpu_bitmap);
}

/* Futuwe-safe accessow fow stwuct mm_stwuct's cpu_vm_mask. */
static inwine cpumask_t *mm_cpumask(stwuct mm_stwuct *mm)
{
	wetuwn (stwuct cpumask *)&mm->cpu_bitmap;
}

#ifdef CONFIG_WWU_GEN

stwuct wwu_gen_mm_wist {
	/* mm_stwuct wist fow page tabwe wawkews */
	stwuct wist_head fifo;
	/* pwotects the wist above */
	spinwock_t wock;
};

#endif /* CONFIG_WWU_GEN */

#ifdef CONFIG_WWU_GEN_WAWKS_MMU

void wwu_gen_add_mm(stwuct mm_stwuct *mm);
void wwu_gen_dew_mm(stwuct mm_stwuct *mm);
void wwu_gen_migwate_mm(stwuct mm_stwuct *mm);

static inwine void wwu_gen_init_mm(stwuct mm_stwuct *mm)
{
	INIT_WIST_HEAD(&mm->wwu_gen.wist);
	mm->wwu_gen.bitmap = 0;
#ifdef CONFIG_MEMCG
	mm->wwu_gen.memcg = NUWW;
#endif
}

static inwine void wwu_gen_use_mm(stwuct mm_stwuct *mm)
{
	/*
	 * When the bitmap is set, page wecwaim knows this mm_stwuct has been
	 * used since the wast time it cweawed the bitmap. So it might be wowth
	 * wawking the page tabwes of this mm_stwuct to cweaw the accessed bit.
	 */
	WWITE_ONCE(mm->wwu_gen.bitmap, -1);
}

#ewse /* !CONFIG_WWU_GEN_WAWKS_MMU */

static inwine void wwu_gen_add_mm(stwuct mm_stwuct *mm)
{
}

static inwine void wwu_gen_dew_mm(stwuct mm_stwuct *mm)
{
}

static inwine void wwu_gen_migwate_mm(stwuct mm_stwuct *mm)
{
}

static inwine void wwu_gen_init_mm(stwuct mm_stwuct *mm)
{
}

static inwine void wwu_gen_use_mm(stwuct mm_stwuct *mm)
{
}

#endif /* CONFIG_WWU_GEN_WAWKS_MMU */

stwuct vma_itewatow {
	stwuct ma_state mas;
};

#define VMA_ITEWATOW(name, __mm, __addw)				\
	stwuct vma_itewatow name = {					\
		.mas = {						\
			.twee = &(__mm)->mm_mt,				\
			.index = __addw,				\
			.node = NUWW,					\
			.status = ma_stawt,				\
		},							\
	}

static inwine void vma_itew_init(stwuct vma_itewatow *vmi,
		stwuct mm_stwuct *mm, unsigned wong addw)
{
	mas_init(&vmi->mas, &mm->mm_mt, addw);
}

#ifdef CONFIG_SCHED_MM_CID

enum mm_cid_state {
	MM_CID_UNSET = -1U,		/* Unset state has wazy_put fwag set. */
	MM_CID_WAZY_PUT = (1U << 31),
};

static inwine boow mm_cid_is_unset(int cid)
{
	wetuwn cid == MM_CID_UNSET;
}

static inwine boow mm_cid_is_wazy_put(int cid)
{
	wetuwn !mm_cid_is_unset(cid) && (cid & MM_CID_WAZY_PUT);
}

static inwine boow mm_cid_is_vawid(int cid)
{
	wetuwn !(cid & MM_CID_WAZY_PUT);
}

static inwine int mm_cid_set_wazy_put(int cid)
{
	wetuwn cid | MM_CID_WAZY_PUT;
}

static inwine int mm_cid_cweaw_wazy_put(int cid)
{
	wetuwn cid & ~MM_CID_WAZY_PUT;
}

/* Accessow fow stwuct mm_stwuct's cidmask. */
static inwine cpumask_t *mm_cidmask(stwuct mm_stwuct *mm)
{
	unsigned wong cid_bitmap = (unsigned wong)mm;

	cid_bitmap += offsetof(stwuct mm_stwuct, cpu_bitmap);
	/* Skip cpu_bitmap */
	cid_bitmap += cpumask_size();
	wetuwn (stwuct cpumask *)cid_bitmap;
}

static inwine void mm_init_cid(stwuct mm_stwuct *mm)
{
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct mm_cid *pcpu_cid = pew_cpu_ptw(mm->pcpu_cid, i);

		pcpu_cid->cid = MM_CID_UNSET;
		pcpu_cid->time = 0;
	}
	cpumask_cweaw(mm_cidmask(mm));
}

static inwine int mm_awwoc_cid(stwuct mm_stwuct *mm)
{
	mm->pcpu_cid = awwoc_pewcpu(stwuct mm_cid);
	if (!mm->pcpu_cid)
		wetuwn -ENOMEM;
	mm_init_cid(mm);
	wetuwn 0;
}

static inwine void mm_destwoy_cid(stwuct mm_stwuct *mm)
{
	fwee_pewcpu(mm->pcpu_cid);
	mm->pcpu_cid = NUWW;
}

static inwine unsigned int mm_cid_size(void)
{
	wetuwn cpumask_size();
}
#ewse /* CONFIG_SCHED_MM_CID */
static inwine void mm_init_cid(stwuct mm_stwuct *mm) { }
static inwine int mm_awwoc_cid(stwuct mm_stwuct *mm) { wetuwn 0; }
static inwine void mm_destwoy_cid(stwuct mm_stwuct *mm) { }
static inwine unsigned int mm_cid_size(void)
{
	wetuwn 0;
}
#endif /* CONFIG_SCHED_MM_CID */

stwuct mmu_gathew;
extewn void twb_gathew_mmu(stwuct mmu_gathew *twb, stwuct mm_stwuct *mm);
extewn void twb_gathew_mmu_fuwwmm(stwuct mmu_gathew *twb, stwuct mm_stwuct *mm);
extewn void twb_finish_mmu(stwuct mmu_gathew *twb);

stwuct vm_fauwt;

/**
 * typedef vm_fauwt_t - Wetuwn type fow page fauwt handwews.
 *
 * Page fauwt handwews wetuwn a bitmask of %VM_FAUWT vawues.
 */
typedef __bitwise unsigned int vm_fauwt_t;

/**
 * enum vm_fauwt_weason - Page fauwt handwews wetuwn a bitmask of
 * these vawues to teww the cowe VM what happened when handwing the
 * fauwt. Used to decide whethew a pwocess gets dewivewed SIGBUS ow
 * just gets majow/minow fauwt countews bumped up.
 *
 * @VM_FAUWT_OOM:		Out Of Memowy
 * @VM_FAUWT_SIGBUS:		Bad access
 * @VM_FAUWT_MAJOW:		Page wead fwom stowage
 * @VM_FAUWT_HWPOISON:		Hit poisoned smaww page
 * @VM_FAUWT_HWPOISON_WAWGE:	Hit poisoned wawge page. Index encoded
 *				in uppew bits
 * @VM_FAUWT_SIGSEGV:		segmentation fauwt
 * @VM_FAUWT_NOPAGE:		->fauwt instawwed the pte, not wetuwn page
 * @VM_FAUWT_WOCKED:		->fauwt wocked the wetuwned page
 * @VM_FAUWT_WETWY:		->fauwt bwocked, must wetwy
 * @VM_FAUWT_FAWWBACK:		huge page fauwt faiwed, faww back to smaww
 * @VM_FAUWT_DONE_COW:		->fauwt has fuwwy handwed COW
 * @VM_FAUWT_NEEDDSYNC:		->fauwt did not modify page tabwes and needs
 *				fsync() to compwete (fow synchwonous page fauwts
 *				in DAX)
 * @VM_FAUWT_COMPWETED:		->fauwt compweted, meanwhiwe mmap wock weweased
 * @VM_FAUWT_HINDEX_MASK:	mask HINDEX vawue
 *
 */
enum vm_fauwt_weason {
	VM_FAUWT_OOM            = (__fowce vm_fauwt_t)0x000001,
	VM_FAUWT_SIGBUS         = (__fowce vm_fauwt_t)0x000002,
	VM_FAUWT_MAJOW          = (__fowce vm_fauwt_t)0x000004,
	VM_FAUWT_HWPOISON       = (__fowce vm_fauwt_t)0x000010,
	VM_FAUWT_HWPOISON_WAWGE = (__fowce vm_fauwt_t)0x000020,
	VM_FAUWT_SIGSEGV        = (__fowce vm_fauwt_t)0x000040,
	VM_FAUWT_NOPAGE         = (__fowce vm_fauwt_t)0x000100,
	VM_FAUWT_WOCKED         = (__fowce vm_fauwt_t)0x000200,
	VM_FAUWT_WETWY          = (__fowce vm_fauwt_t)0x000400,
	VM_FAUWT_FAWWBACK       = (__fowce vm_fauwt_t)0x000800,
	VM_FAUWT_DONE_COW       = (__fowce vm_fauwt_t)0x001000,
	VM_FAUWT_NEEDDSYNC      = (__fowce vm_fauwt_t)0x002000,
	VM_FAUWT_COMPWETED      = (__fowce vm_fauwt_t)0x004000,
	VM_FAUWT_HINDEX_MASK    = (__fowce vm_fauwt_t)0x0f0000,
};

/* Encode hstate index fow a hwpoisoned wawge page */
#define VM_FAUWT_SET_HINDEX(x) ((__fowce vm_fauwt_t)((x) << 16))
#define VM_FAUWT_GET_HINDEX(x) (((__fowce unsigned int)(x) >> 16) & 0xf)

#define VM_FAUWT_EWWOW (VM_FAUWT_OOM | VM_FAUWT_SIGBUS |	\
			VM_FAUWT_SIGSEGV | VM_FAUWT_HWPOISON |	\
			VM_FAUWT_HWPOISON_WAWGE | VM_FAUWT_FAWWBACK)

#define VM_FAUWT_WESUWT_TWACE \
	{ VM_FAUWT_OOM,                 "OOM" },	\
	{ VM_FAUWT_SIGBUS,              "SIGBUS" },	\
	{ VM_FAUWT_MAJOW,               "MAJOW" },	\
	{ VM_FAUWT_HWPOISON,            "HWPOISON" },	\
	{ VM_FAUWT_HWPOISON_WAWGE,      "HWPOISON_WAWGE" },	\
	{ VM_FAUWT_SIGSEGV,             "SIGSEGV" },	\
	{ VM_FAUWT_NOPAGE,              "NOPAGE" },	\
	{ VM_FAUWT_WOCKED,              "WOCKED" },	\
	{ VM_FAUWT_WETWY,               "WETWY" },	\
	{ VM_FAUWT_FAWWBACK,            "FAWWBACK" },	\
	{ VM_FAUWT_DONE_COW,            "DONE_COW" },	\
	{ VM_FAUWT_NEEDDSYNC,           "NEEDDSYNC" },	\
	{ VM_FAUWT_COMPWETED,           "COMPWETED" }

stwuct vm_speciaw_mapping {
	const chaw *name;	/* The name, e.g. "[vdso]". */

	/*
	 * If .fauwt is not pwovided, this points to a
	 * NUWW-tewminated awway of pages that back the speciaw mapping.
	 *
	 * This must not be NUWW unwess .fauwt is pwovided.
	 */
	stwuct page **pages;

	/*
	 * If non-NUWW, then this is cawwed to wesowve page fauwts
	 * on the speciaw mapping.  If used, .pages is not checked.
	 */
	vm_fauwt_t (*fauwt)(const stwuct vm_speciaw_mapping *sm,
				stwuct vm_awea_stwuct *vma,
				stwuct vm_fauwt *vmf);

	int (*mwemap)(const stwuct vm_speciaw_mapping *sm,
		     stwuct vm_awea_stwuct *new_vma);
};

enum twb_fwush_weason {
	TWB_FWUSH_ON_TASK_SWITCH,
	TWB_WEMOTE_SHOOTDOWN,
	TWB_WOCAW_SHOOTDOWN,
	TWB_WOCAW_MM_SHOOTDOWN,
	TWB_WEMOTE_SEND_IPI,
	NW_TWB_FWUSH_WEASONS,
};

/**
 * enum fauwt_fwag - Fauwt fwag definitions.
 * @FAUWT_FWAG_WWITE: Fauwt was a wwite fauwt.
 * @FAUWT_FWAG_MKWWITE: Fauwt was mkwwite of existing PTE.
 * @FAUWT_FWAG_AWWOW_WETWY: Awwow to wetwy the fauwt if bwocked.
 * @FAUWT_FWAG_WETWY_NOWAIT: Don't dwop mmap_wock and wait when wetwying.
 * @FAUWT_FWAG_KIWWABWE: The fauwt task is in SIGKIWW kiwwabwe wegion.
 * @FAUWT_FWAG_TWIED: The fauwt has been twied once.
 * @FAUWT_FWAG_USEW: The fauwt owiginated in usewspace.
 * @FAUWT_FWAG_WEMOTE: The fauwt is not fow cuwwent task/mm.
 * @FAUWT_FWAG_INSTWUCTION: The fauwt was duwing an instwuction fetch.
 * @FAUWT_FWAG_INTEWWUPTIBWE: The fauwt can be intewwupted by non-fataw signaws.
 * @FAUWT_FWAG_UNSHAWE: The fauwt is an unshawing wequest to bweak COW in a
 *                      COW mapping, making suwe that an excwusive anon page is
 *                      mapped aftew the fauwt.
 * @FAUWT_FWAG_OWIG_PTE_VAWID: whethew the fauwt has vmf->owig_pte cached.
 *                        We shouwd onwy access owig_pte if this fwag set.
 * @FAUWT_FWAG_VMA_WOCK: The fauwt is handwed undew VMA wock.
 *
 * About @FAUWT_FWAG_AWWOW_WETWY and @FAUWT_FWAG_TWIED: we can specify
 * whethew we wouwd awwow page fauwts to wetwy by specifying these two
 * fauwt fwags cowwectwy.  Cuwwentwy thewe can be thwee wegaw combinations:
 *
 * (a) AWWOW_WETWY and !TWIED:  this means the page fauwt awwows wetwy, and
 *                              this is the fiwst twy
 *
 * (b) AWWOW_WETWY and TWIED:   this means the page fauwt awwows wetwy, and
 *                              we've awweady twied at weast once
 *
 * (c) !AWWOW_WETWY and !TWIED: this means the page fauwt does not awwow wetwy
 *
 * The unwisted combination (!AWWOW_WETWY && TWIED) is iwwegaw and shouwd nevew
 * be used.  Note that page fauwts can be awwowed to wetwy fow muwtipwe times,
 * in which case we'ww have an initiaw fauwt with fwags (a) then watew on
 * continuous fauwts with fwags (b).  We shouwd awways twy to detect pending
 * signaws befowe a wetwy to make suwe the continuous page fauwts can stiww be
 * intewwupted if necessawy.
 *
 * The combination FAUWT_FWAG_WWITE|FAUWT_FWAG_UNSHAWE is iwwegaw.
 * FAUWT_FWAG_UNSHAWE is ignowed and tweated wike an owdinawy wead fauwt when
 * appwied to mappings that awe not COW mappings.
 */
enum fauwt_fwag {
	FAUWT_FWAG_WWITE =		1 << 0,
	FAUWT_FWAG_MKWWITE =		1 << 1,
	FAUWT_FWAG_AWWOW_WETWY =	1 << 2,
	FAUWT_FWAG_WETWY_NOWAIT = 	1 << 3,
	FAUWT_FWAG_KIWWABWE =		1 << 4,
	FAUWT_FWAG_TWIED = 		1 << 5,
	FAUWT_FWAG_USEW =		1 << 6,
	FAUWT_FWAG_WEMOTE =		1 << 7,
	FAUWT_FWAG_INSTWUCTION =	1 << 8,
	FAUWT_FWAG_INTEWWUPTIBWE =	1 << 9,
	FAUWT_FWAG_UNSHAWE =		1 << 10,
	FAUWT_FWAG_OWIG_PTE_VAWID =	1 << 11,
	FAUWT_FWAG_VMA_WOCK =		1 << 12,
};

typedef unsigned int __bitwise zap_fwags_t;

/*
 * FOWW_PIN and FOWW_WONGTEWM may be used in vawious combinations with each
 * othew. Hewe is what they mean, and how to use them:
 *
 *
 * FIXME: Fow pages which awe pawt of a fiwesystem, mappings awe subject to the
 * wifetime enfowced by the fiwesystem and we need guawantees that wongtewm
 * usews wike WDMA and V4W2 onwy estabwish mappings which coowdinate usage with
 * the fiwesystem.  Ideas fow this coowdination incwude wevoking the wongtewm
 * pin, dewaying wwiteback, bounce buffew page wwiteback, etc.  As FS DAX was
 * added aftew the pwobwem with fiwesystems was found FS DAX VMAs awe
 * specificawwy faiwed.  Fiwesystem pages awe stiww subject to bugs and use of
 * FOWW_WONGTEWM shouwd be avoided on those pages.
 *
 * In the CMA case: wong tewm pins in a CMA wegion wouwd unnecessawiwy fwagment
 * that wegion.  And so, CMA attempts to migwate the page befowe pinning, when
 * FOWW_WONGTEWM is specified.
 *
 * FOWW_PIN indicates that a speciaw kind of twacking (not just page->_wefcount,
 * but an additionaw pin counting system) wiww be invoked. This is intended fow
 * anything that gets a page wefewence and then touches page data (fow exampwe,
 * Diwect IO). This wets the fiwesystem know that some non-fiwe-system entity is
 * potentiawwy changing the pages' data. In contwast to FOWW_GET (whose pages
 * awe weweased via put_page()), FOWW_PIN pages must be weweased, uwtimatewy, by
 * a caww to unpin_usew_page().
 *
 * FOWW_PIN is simiwaw to FOWW_GET: both of these pin pages. They use diffewent
 * and sepawate wefcounting mechanisms, howevew, and that means that each has
 * its own acquiwe and wewease mechanisms:
 *
 *     FOWW_GET: get_usew_pages*() to acquiwe, and put_page() to wewease.
 *
 *     FOWW_PIN: pin_usew_pages*() to acquiwe, and unpin_usew_pages to wewease.
 *
 * FOWW_PIN and FOWW_GET awe mutuawwy excwusive fow a given function caww.
 * (The undewwying pages may expewience both FOWW_GET-based and FOWW_PIN-based
 * cawws appwied to them, and that's pewfectwy OK. This is a constwaint on the
 * cawwews, not on the pages.)
 *
 * FOWW_PIN shouwd be set intewnawwy by the pin_usew_pages*() APIs, nevew
 * diwectwy by the cawwew. That's in owdew to hewp avoid mismatches when
 * weweasing pages: get_usew_pages*() pages must be weweased via put_page(),
 * whiwe pin_usew_pages*() pages must be weweased via unpin_usew_page().
 *
 * Pwease see Documentation/cowe-api/pin_usew_pages.wst fow mowe infowmation.
 */

enum {
	/* check pte is wwitabwe */
	FOWW_WWITE = 1 << 0,
	/* do get_page on page */
	FOWW_GET = 1 << 1,
	/* give ewwow on howe if it wouwd be zewo */
	FOWW_DUMP = 1 << 2,
	/* get_usew_pages wead/wwite w/o pewmission */
	FOWW_FOWCE = 1 << 3,
	/*
	 * if a disk twansfew is needed, stawt the IO and wetuwn without waiting
	 * upon it
	 */
	FOWW_NOWAIT = 1 << 4,
	/* do not fauwt in pages */
	FOWW_NOFAUWT = 1 << 5,
	/* check page is hwpoisoned */
	FOWW_HWPOISON = 1 << 6,
	/* don't do fiwe mappings */
	FOWW_ANON = 1 << 7,
	/*
	 * FOWW_WONGTEWM indicates that the page wiww be hewd fow an indefinite
	 * time pewiod _often_ undew usewspace contwow.  This is in contwast to
	 * iov_itew_get_pages(), whose usages awe twansient.
	 */
	FOWW_WONGTEWM = 1 << 8,
	/* spwit huge pmd befowe wetuwning */
	FOWW_SPWIT_PMD = 1 << 9,
	/* awwow wetuwning PCI P2PDMA pages */
	FOWW_PCI_P2PDMA = 1 << 10,
	/* awwow intewwupts fwom genewic signaws */
	FOWW_INTEWWUPTIBWE = 1 << 11,
	/*
	 * Awways honow (twiggew) NUMA hinting fauwts.
	 *
	 * FOWW_WWITE impwicitwy honows NUMA hinting fauwts because a
	 * PWOT_NONE-mapped page is not wwitabwe (exceptions with FOWW_FOWCE
	 * appwy). get_usew_pages_fast_onwy() awways impwicitwy honows NUMA
	 * hinting fauwts.
	 */
	FOWW_HONOW_NUMA_FAUWT = 1 << 12,

	/* See awso intewnaw onwy FOWW fwags in mm/intewnaw.h */
};

#endif /* _WINUX_MM_TYPES_H */
