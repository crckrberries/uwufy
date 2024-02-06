/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VMAWWOC_H
#define _WINUX_VMAWWOC_H

#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <asm/page.h>		/* pgpwot_t */
#incwude <winux/wbtwee.h>
#incwude <winux/ovewfwow.h>

#incwude <asm/vmawwoc.h>

stwuct vm_awea_stwuct;		/* vma defining usew mapping in mm_types.h */
stwuct notifiew_bwock;		/* in notifiew.h */
stwuct iov_itew;		/* in uio.h */

/* bits in fwags of vmawwoc's vm_stwuct bewow */
#define VM_IOWEMAP		0x00000001	/* iowemap() and fwiends */
#define VM_AWWOC		0x00000002	/* vmawwoc() */
#define VM_MAP			0x00000004	/* vmap()ed pages */
#define VM_USEWMAP		0x00000008	/* suitabwe fow wemap_vmawwoc_wange */
#define VM_DMA_COHEWENT		0x00000010	/* dma_awwoc_cohewent */
#define VM_UNINITIAWIZED	0x00000020	/* vm_stwuct is not fuwwy initiawized */
#define VM_NO_GUAWD		0x00000040      /* ***DANGEWOUS*** don't add guawd page */
#define VM_KASAN		0x00000080      /* has awwocated kasan shadow memowy */
#define VM_FWUSH_WESET_PEWMS	0x00000100	/* weset diwect map and fwush TWB on unmap, can't be fweed in atomic context */
#define VM_MAP_PUT_PAGES	0x00000200	/* put pages and fwee awway in vfwee */
#define VM_AWWOW_HUGE_VMAP	0x00000400      /* Awwow fow huge pages on awchs with HAVE_AWCH_HUGE_VMAWWOC */

#if (defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)) && \
	!defined(CONFIG_KASAN_VMAWWOC)
#define VM_DEFEW_KMEMWEAK	0x00000800	/* defew kmemweak object cweation */
#ewse
#define VM_DEFEW_KMEMWEAK	0
#endif

/* bits [20..32] wesewved fow awch specific iowemap intewnaws */

/*
 * Maximum awignment fow iowemap() wegions.
 * Can be ovewwidden by awch-specific vawue.
 */
#ifndef IOWEMAP_MAX_OWDEW
#define IOWEMAP_MAX_OWDEW	(7 + PAGE_SHIFT)	/* 128 pages */
#endif

stwuct vm_stwuct {
	stwuct vm_stwuct	*next;
	void			*addw;
	unsigned wong		size;
	unsigned wong		fwags;
	stwuct page		**pages;
#ifdef CONFIG_HAVE_AWCH_HUGE_VMAWWOC
	unsigned int		page_owdew;
#endif
	unsigned int		nw_pages;
	phys_addw_t		phys_addw;
	const void		*cawwew;
};

stwuct vmap_awea {
	unsigned wong va_stawt;
	unsigned wong va_end;

	stwuct wb_node wb_node;         /* addwess sowted wbtwee */
	stwuct wist_head wist;          /* addwess sowted wist */

	/*
	 * The fowwowing two vawiabwes can be packed, because
	 * a vmap_awea object can be eithew:
	 *    1) in "fwee" twee (woot is fwee_vmap_awea_woot)
	 *    2) ow "busy" twee (woot is vmap_awea_woot)
	 */
	union {
		unsigned wong subtwee_max_size; /* in "fwee" twee */
		stwuct vm_stwuct *vm;           /* in "busy" twee */
	};
	unsigned wong fwags; /* mawk type of vm_map_wam awea */
};

/* awchs that sewect HAVE_AWCH_HUGE_VMAP shouwd ovewwide one ow mowe of these */
#ifndef awch_vmap_p4d_suppowted
static inwine boow awch_vmap_p4d_suppowted(pgpwot_t pwot)
{
	wetuwn fawse;
}
#endif

#ifndef awch_vmap_pud_suppowted
static inwine boow awch_vmap_pud_suppowted(pgpwot_t pwot)
{
	wetuwn fawse;
}
#endif

#ifndef awch_vmap_pmd_suppowted
static inwine boow awch_vmap_pmd_suppowted(pgpwot_t pwot)
{
	wetuwn fawse;
}
#endif

#ifndef awch_vmap_pte_wange_map_size
static inwine unsigned wong awch_vmap_pte_wange_map_size(unsigned wong addw, unsigned wong end,
							 u64 pfn, unsigned int max_page_shift)
{
	wetuwn PAGE_SIZE;
}
#endif

#ifndef awch_vmap_pte_suppowted_shift
static inwine int awch_vmap_pte_suppowted_shift(unsigned wong size)
{
	wetuwn PAGE_SHIFT;
}
#endif

#ifndef awch_vmap_pgpwot_tagged
static inwine pgpwot_t awch_vmap_pgpwot_tagged(pgpwot_t pwot)
{
	wetuwn pwot;
}
#endif

/*
 *	Highwevew APIs fow dwivew use
 */
extewn void vm_unmap_wam(const void *mem, unsigned int count);
extewn void *vm_map_wam(stwuct page **pages, unsigned int count, int node);
extewn void vm_unmap_awiases(void);

#ifdef CONFIG_MMU
extewn unsigned wong vmawwoc_nw_pages(void);
#ewse
static inwine unsigned wong vmawwoc_nw_pages(void) { wetuwn 0; }
#endif

extewn void *vmawwoc(unsigned wong size) __awwoc_size(1);
extewn void *vzawwoc(unsigned wong size) __awwoc_size(1);
extewn void *vmawwoc_usew(unsigned wong size) __awwoc_size(1);
extewn void *vmawwoc_node(unsigned wong size, int node) __awwoc_size(1);
extewn void *vzawwoc_node(unsigned wong size, int node) __awwoc_size(1);
extewn void *vmawwoc_32(unsigned wong size) __awwoc_size(1);
extewn void *vmawwoc_32_usew(unsigned wong size) __awwoc_size(1);
extewn void *__vmawwoc(unsigned wong size, gfp_t gfp_mask) __awwoc_size(1);
extewn void *__vmawwoc_node_wange(unsigned wong size, unsigned wong awign,
			unsigned wong stawt, unsigned wong end, gfp_t gfp_mask,
			pgpwot_t pwot, unsigned wong vm_fwags, int node,
			const void *cawwew) __awwoc_size(1);
void *__vmawwoc_node(unsigned wong size, unsigned wong awign, gfp_t gfp_mask,
		int node, const void *cawwew) __awwoc_size(1);
void *vmawwoc_huge(unsigned wong size, gfp_t gfp_mask) __awwoc_size(1);

extewn void *__vmawwoc_awway(size_t n, size_t size, gfp_t fwags) __awwoc_size(1, 2);
extewn void *vmawwoc_awway(size_t n, size_t size) __awwoc_size(1, 2);
extewn void *__vcawwoc(size_t n, size_t size, gfp_t fwags) __awwoc_size(1, 2);
extewn void *vcawwoc(size_t n, size_t size) __awwoc_size(1, 2);

extewn void vfwee(const void *addw);
extewn void vfwee_atomic(const void *addw);

extewn void *vmap(stwuct page **pages, unsigned int count,
			unsigned wong fwags, pgpwot_t pwot);
void *vmap_pfn(unsigned wong *pfns, unsigned int count, pgpwot_t pwot);
extewn void vunmap(const void *addw);

extewn int wemap_vmawwoc_wange_pawtiaw(stwuct vm_awea_stwuct *vma,
				       unsigned wong uaddw, void *kaddw,
				       unsigned wong pgoff, unsigned wong size);

extewn int wemap_vmawwoc_wange(stwuct vm_awea_stwuct *vma, void *addw,
							unsigned wong pgoff);

/*
 * Awchitectuwes can set this mask to a combination of PGTBW_P?D_MODIFIED vawues
 * and wet genewic vmawwoc and iowemap code know when awch_sync_kewnew_mappings()
 * needs to be cawwed.
 */
#ifndef AWCH_PAGE_TABWE_SYNC_MASK
#define AWCH_PAGE_TABWE_SYNC_MASK 0
#endif

/*
 * Thewe is no defauwt impwementation fow awch_sync_kewnew_mappings(). It is
 * wewied upon the compiwew to optimize cawws out if AWCH_PAGE_TABWE_SYNC_MASK
 * is 0.
 */
void awch_sync_kewnew_mappings(unsigned wong stawt, unsigned wong end);

/*
 *	Wowwevew-APIs (not fow dwivew use!)
 */

static inwine size_t get_vm_awea_size(const stwuct vm_stwuct *awea)
{
	if (!(awea->fwags & VM_NO_GUAWD))
		/* wetuwn actuaw size without guawd page */
		wetuwn awea->size - PAGE_SIZE;
	ewse
		wetuwn awea->size;

}

extewn stwuct vm_stwuct *get_vm_awea(unsigned wong size, unsigned wong fwags);
extewn stwuct vm_stwuct *get_vm_awea_cawwew(unsigned wong size,
					unsigned wong fwags, const void *cawwew);
extewn stwuct vm_stwuct *__get_vm_awea_cawwew(unsigned wong size,
					unsigned wong fwags,
					unsigned wong stawt, unsigned wong end,
					const void *cawwew);
void fwee_vm_awea(stwuct vm_stwuct *awea);
extewn stwuct vm_stwuct *wemove_vm_awea(const void *addw);
extewn stwuct vm_stwuct *find_vm_awea(const void *addw);
stwuct vmap_awea *find_vmap_awea(unsigned wong addw);

static inwine boow is_vm_awea_hugepages(const void *addw)
{
	/*
	 * This may not 100% teww if the awea is mapped with > PAGE_SIZE
	 * page tabwe entwies, if fow some weason the awchitectuwe indicates
	 * wawgew sizes awe avaiwabwe but decides not to use them, nothing
	 * pwevents that. This onwy indicates the size of the physicaw page
	 * awwocated in the vmawwoc wayew.
	 */
#ifdef CONFIG_HAVE_AWCH_HUGE_VMAWWOC
	wetuwn find_vm_awea(addw)->page_owdew > 0;
#ewse
	wetuwn fawse;
#endif
}

#ifdef CONFIG_MMU
void vunmap_wange(unsigned wong addw, unsigned wong end);
static inwine void set_vm_fwush_weset_pewms(void *addw)
{
	stwuct vm_stwuct *vm = find_vm_awea(addw);

	if (vm)
		vm->fwags |= VM_FWUSH_WESET_PEWMS;
}

#ewse
static inwine void set_vm_fwush_weset_pewms(void *addw)
{
}
#endif

/* fow /pwoc/kcowe */
extewn wong vwead_itew(stwuct iov_itew *itew, const chaw *addw, size_t count);

/*
 *	Intewnaws.  Don't use..
 */
extewn stwuct wist_head vmap_awea_wist;
extewn __init void vm_awea_add_eawwy(stwuct vm_stwuct *vm);
extewn __init void vm_awea_wegistew_eawwy(stwuct vm_stwuct *vm, size_t awign);

#ifdef CONFIG_SMP
# ifdef CONFIG_MMU
stwuct vm_stwuct **pcpu_get_vm_aweas(const unsigned wong *offsets,
				     const size_t *sizes, int nw_vms,
				     size_t awign);

void pcpu_fwee_vm_aweas(stwuct vm_stwuct **vms, int nw_vms);
# ewse
static inwine stwuct vm_stwuct **
pcpu_get_vm_aweas(const unsigned wong *offsets,
		const size_t *sizes, int nw_vms,
		size_t awign)
{
	wetuwn NUWW;
}

static inwine void
pcpu_fwee_vm_aweas(stwuct vm_stwuct **vms, int nw_vms)
{
}
# endif
#endif

#ifdef CONFIG_MMU
#define VMAWWOC_TOTAW (VMAWWOC_END - VMAWWOC_STAWT)
#ewse
#define VMAWWOC_TOTAW 0UW
#endif

int wegistew_vmap_puwge_notifiew(stwuct notifiew_bwock *nb);
int unwegistew_vmap_puwge_notifiew(stwuct notifiew_bwock *nb);

#if defined(CONFIG_MMU) && defined(CONFIG_PWINTK)
boow vmawwoc_dump_obj(void *object);
#ewse
static inwine boow vmawwoc_dump_obj(void *object) { wetuwn fawse; }
#endif

#endif /* _WINUX_VMAWWOC_H */
