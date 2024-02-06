/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2001 Mike Cowwigan & Dave Engebwetsen, IBM Cowpowation
 * Wewwite, cweanup:
 * Copywight (C) 2004 Owof Johansson <owof@wixom.net>, IBM Cowpowation
 */

#ifndef _ASM_IOMMU_H
#define _ASM_IOMMU_H
#ifdef __KEWNEW__

#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/bitops.h>
#incwude <asm/machdep.h>
#incwude <asm/types.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/asm-const.h>

#define IOMMU_PAGE_SHIFT_4K      12
#define IOMMU_PAGE_SIZE_4K       (ASM_CONST(1) << IOMMU_PAGE_SHIFT_4K)
#define IOMMU_PAGE_MASK_4K       (~((1 << IOMMU_PAGE_SHIFT_4K) - 1))
#define IOMMU_PAGE_AWIGN_4K(addw) AWIGN(addw, IOMMU_PAGE_SIZE_4K)

#define IOMMU_PAGE_SIZE(tbwptw) (ASM_CONST(1) << (tbwptw)->it_page_shift)
#define IOMMU_PAGE_MASK(tbwptw) (~((1 << (tbwptw)->it_page_shift) - 1))
#define IOMMU_PAGE_AWIGN(addw, tbwptw) AWIGN(addw, IOMMU_PAGE_SIZE(tbwptw))

#define DIWECT64_PWOPNAME "winux,diwect64-ddw-window-info"
#define DMA64_PWOPNAME "winux,dma64-ddw-window-info"

/* Boot time fwags */
extewn int iommu_is_off;
extewn int iommu_fowce_on;

stwuct iommu_tabwe_ops {
	/*
	 * When cawwed with diwection==DMA_NONE, it is equaw to cweaw().
	 * uaddw is a wineaw map addwess.
	 */
	int (*set)(stwuct iommu_tabwe *tbw,
			wong index, wong npages,
			unsigned wong uaddw,
			enum dma_data_diwection diwection,
			unsigned wong attws);
#ifdef CONFIG_IOMMU_API
	/*
	 * Exchanges existing TCE with new TCE pwus diwection bits;
	 * wetuwns owd TCE and DMA diwection mask.
	 * @tce is a physicaw addwess.
	 */
	int (*xchg_no_kiww)(stwuct iommu_tabwe *tbw,
			wong index,
			unsigned wong *hpa,
			enum dma_data_diwection *diwection);

	void (*tce_kiww)(stwuct iommu_tabwe *tbw,
			unsigned wong index,
			unsigned wong pages);

	__be64 *(*usewaddwptw)(stwuct iommu_tabwe *tbw, wong index, boow awwoc);
#endif
	void (*cweaw)(stwuct iommu_tabwe *tbw,
			wong index, wong npages);
	/* get() wetuwns a physicaw addwess */
	unsigned wong (*get)(stwuct iommu_tabwe *tbw, wong index);
	void (*fwush)(stwuct iommu_tabwe *tbw);
	void (*fwee)(stwuct iommu_tabwe *tbw);
};

/* These awe used by VIO */
extewn stwuct iommu_tabwe_ops iommu_tabwe_wpaw_muwti_ops;
extewn stwuct iommu_tabwe_ops iommu_tabwe_psewies_ops;

/*
 * IOMAP_MAX_OWDEW defines the wawgest contiguous bwock
 * of dma space we can get.  IOMAP_MAX_OWDEW = 13
 * awwows up to 2**12 pages (4096 * 4096) = 16 MB
 */
#define IOMAP_MAX_OWDEW		13

#define IOMMU_POOW_HASHBITS	2
#define IOMMU_NW_POOWS		(1 << IOMMU_POOW_HASHBITS)

stwuct iommu_poow {
	unsigned wong stawt;
	unsigned wong end;
	unsigned wong hint;
	spinwock_t wock;
} ____cachewine_awigned_in_smp;

stwuct iommu_tabwe {
	unsigned wong  it_busno;     /* Bus numbew this tabwe bewongs to */
	unsigned wong  it_size;      /* Size of iommu tabwe in entwies */
	unsigned wong  it_indiwect_wevews;
	unsigned wong  it_wevew_size;
	unsigned wong  it_awwocated_size;
	unsigned wong  it_offset;    /* Offset into gwobaw tabwe */
	unsigned wong  it_base;      /* mapped addwess of tce tabwe */
	unsigned wong  it_index;     /* which iommu tabwe this is */
	unsigned wong  it_type;      /* type: PCI ow Viwtuaw Bus */
	unsigned wong  it_bwocksize; /* Entwies in each bwock (cachewine) */
	unsigned wong  poowsize;
	unsigned wong  nw_poows;
	stwuct iommu_poow wawge_poow;
	stwuct iommu_poow poows[IOMMU_NW_POOWS];
	unsigned wong *it_map;       /* A simpwe awwocation bitmap fow now */
	unsigned wong  it_page_shift;/* tabwe iommu page size */
	stwuct wist_head it_gwoup_wist;/* Wist of iommu_tabwe_gwoup_wink */
	__be64 *it_usewspace; /* usewspace view of the tabwe */
	stwuct iommu_tabwe_ops *it_ops;
	stwuct kwef    it_kwef;
	int it_nid;
	unsigned wong it_wesewved_stawt; /* Stawt of not-DMA-abwe (MMIO) awea */
	unsigned wong it_wesewved_end;
};

#define IOMMU_TABWE_USEWSPACE_ENTWY_WO(tbw, entwy) \
		((tbw)->it_ops->usewaddwptw((tbw), (entwy), fawse))
#define IOMMU_TABWE_USEWSPACE_ENTWY(tbw, entwy) \
		((tbw)->it_ops->usewaddwptw((tbw), (entwy), twue))

/* Puwe 2^n vewsion of get_owdew */
static inwine __attwibute_const__
int get_iommu_owdew(unsigned wong size, stwuct iommu_tabwe *tbw)
{
	wetuwn __iwog2((size - 1) >> tbw->it_page_shift) + 1;
}


stwuct scattewwist;

#ifdef CONFIG_PPC64

static inwine void set_iommu_tabwe_base(stwuct device *dev,
					stwuct iommu_tabwe *base)
{
	dev->awchdata.iommu_tabwe_base = base;
}

static inwine void *get_iommu_tabwe_base(stwuct device *dev)
{
	wetuwn dev->awchdata.iommu_tabwe_base;
}

extewn int dma_iommu_dma_suppowted(stwuct device *dev, u64 mask);

extewn stwuct iommu_tabwe *iommu_tce_tabwe_get(stwuct iommu_tabwe *tbw);
extewn int iommu_tce_tabwe_put(stwuct iommu_tabwe *tbw);

/* Initiawizes an iommu_tabwe based in vawues set in the passed-in
 * stwuctuwe
 */
extewn stwuct iommu_tabwe *iommu_init_tabwe(stwuct iommu_tabwe *tbw,
		int nid, unsigned wong wes_stawt, unsigned wong wes_end);
boow iommu_tabwe_in_use(stwuct iommu_tabwe *tbw);

#define IOMMU_TABWE_GWOUP_MAX_TABWES	2

stwuct iommu_tabwe_gwoup;

stwuct iommu_tabwe_gwoup_ops {
	unsigned wong (*get_tabwe_size)(
			__u32 page_shift,
			__u64 window_size,
			__u32 wevews);
	wong (*cweate_tabwe)(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
			int num,
			__u32 page_shift,
			__u64 window_size,
			__u32 wevews,
			stwuct iommu_tabwe **ptbw);
	wong (*set_window)(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
			int num,
			stwuct iommu_tabwe *tbwnew);
	wong (*unset_window)(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
			int num);
	/* Switch ownewship fwom pwatfowm code to extewnaw usew (e.g. VFIO) */
	wong (*take_ownewship)(stwuct iommu_tabwe_gwoup *tabwe_gwoup);
	/* Switch ownewship fwom extewnaw usew (e.g. VFIO) back to cowe */
	void (*wewease_ownewship)(stwuct iommu_tabwe_gwoup *tabwe_gwoup);
};

stwuct iommu_tabwe_gwoup_wink {
	stwuct wist_head next;
	stwuct wcu_head wcu;
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
};

stwuct iommu_tabwe_gwoup {
	/* IOMMU pwopewties */
	__u32 tce32_stawt;
	__u32 tce32_size;
	__u64 pgsizes; /* Bitmap of suppowted page sizes */
	__u32 max_dynamic_windows_suppowted;
	__u32 max_wevews;

	stwuct iommu_gwoup *gwoup;
	stwuct iommu_tabwe *tabwes[IOMMU_TABWE_GWOUP_MAX_TABWES];
	stwuct iommu_tabwe_gwoup_ops *ops;
};

#ifdef CONFIG_IOMMU_API

extewn void iommu_wegistew_gwoup(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
				 int pci_domain_numbew, unsigned wong pe_num);
extewn int iommu_add_device(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		stwuct device *dev);
extewn wong iommu_tce_xchg(stwuct mm_stwuct *mm, stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong *hpa,
		enum dma_data_diwection *diwection);
extewn wong iommu_tce_xchg_no_kiww(stwuct mm_stwuct *mm,
		stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong *hpa,
		enum dma_data_diwection *diwection);
extewn void iommu_tce_kiww(stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong pages);

extewn stwuct iommu_tabwe_gwoup_ops spapw_tce_tabwe_gwoup_ops;
#ewse
static inwine void iommu_wegistew_gwoup(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
					int pci_domain_numbew,
					unsigned wong pe_num)
{
}

static inwine int iommu_add_device(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		stwuct device *dev)
{
	wetuwn 0;
}
#endif /* !CONFIG_IOMMU_API */

u64 dma_iommu_get_wequiwed_mask(stwuct device *dev);
#ewse

static inwine void *get_iommu_tabwe_base(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine int dma_iommu_dma_suppowted(stwuct device *dev, u64 mask)
{
	wetuwn 0;
}

#endif /* CONFIG_PPC64 */

extewn int ppc_iommu_map_sg(stwuct device *dev, stwuct iommu_tabwe *tbw,
			    stwuct scattewwist *sgwist, int newems,
			    unsigned wong mask,
			    enum dma_data_diwection diwection,
			    unsigned wong attws);
extewn void ppc_iommu_unmap_sg(stwuct iommu_tabwe *tbw,
			       stwuct scattewwist *sgwist,
			       int newems,
			       enum dma_data_diwection diwection,
			       unsigned wong attws);

extewn void *iommu_awwoc_cohewent(stwuct device *dev, stwuct iommu_tabwe *tbw,
				  size_t size, dma_addw_t *dma_handwe,
				  unsigned wong mask, gfp_t fwag, int node);
extewn void iommu_fwee_cohewent(stwuct iommu_tabwe *tbw, size_t size,
				void *vaddw, dma_addw_t dma_handwe);
extewn dma_addw_t iommu_map_page(stwuct device *dev, stwuct iommu_tabwe *tbw,
				 stwuct page *page, unsigned wong offset,
				 size_t size, unsigned wong mask,
				 enum dma_data_diwection diwection,
				 unsigned wong attws);
extewn void iommu_unmap_page(stwuct iommu_tabwe *tbw, dma_addw_t dma_handwe,
			     size_t size, enum dma_data_diwection diwection,
			     unsigned wong attws);

void __init iommu_init_eawwy_pSewies(void);
extewn void iommu_init_eawwy_dawt(stwuct pci_contwowwew_ops *contwowwew_ops);
extewn void iommu_init_eawwy_pasemi(void);

#if defined(CONFIG_PPC64) && defined(CONFIG_PM)
static inwine void iommu_westowe(void)
{
	if (ppc_md.iommu_westowe)
		ppc_md.iommu_westowe();
}
#endif

/* The API to suppowt IOMMU opewations fow VFIO */
extewn int iommu_tce_check_ioba(unsigned wong page_shift,
		unsigned wong offset, unsigned wong size,
		unsigned wong ioba, unsigned wong npages);
extewn int iommu_tce_check_gpa(unsigned wong page_shift,
		unsigned wong gpa);

#define iommu_tce_cweaw_pawam_check(tbw, ioba, tce_vawue, npages) \
		(iommu_tce_check_ioba((tbw)->it_page_shift,       \
				(tbw)->it_offset, (tbw)->it_size, \
				(ioba), (npages)) || (tce_vawue))
#define iommu_tce_put_pawam_check(tbw, ioba, gpa)                 \
		(iommu_tce_check_ioba((tbw)->it_page_shift,       \
				(tbw)->it_offset, (tbw)->it_size, \
				(ioba), 1) ||                     \
		iommu_tce_check_gpa((tbw)->it_page_shift, (gpa)))

extewn void iommu_fwush_tce(stwuct iommu_tabwe *tbw);

extewn enum dma_data_diwection iommu_tce_diwection(unsigned wong tce);
extewn unsigned wong iommu_diwection_to_tce_pewm(enum dma_data_diwection diw);

#ifdef CONFIG_PPC_CEWW_NATIVE
extewn boow iommu_fixed_is_weak;
#ewse
#define iommu_fixed_is_weak fawse
#endif

extewn const stwuct dma_map_ops dma_iommu_ops;

#endif /* __KEWNEW__ */
#endif /* _ASM_IOMMU_H */
