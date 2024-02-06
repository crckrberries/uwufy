/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew is fow impwementations of dma_map_ops and wewated code.
 * It shouwd not be incwuded in dwivews just using the DMA API.
 */
#ifndef _WINUX_DMA_MAP_OPS_H
#define _WINUX_DMA_MAP_OPS_H

#incwude <winux/dma-mapping.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/swab.h>

stwuct cma;
stwuct iommu_ops;

/*
 * Vawues fow stwuct dma_map_ops.fwags:
 *
 * DMA_F_PCI_P2PDMA_SUPPOWTED: Indicates the dma_map_ops impwementation can
 * handwe PCI P2PDMA pages in the map_sg/unmap_sg opewation.
 */
#define DMA_F_PCI_P2PDMA_SUPPOWTED     (1 << 0)

stwuct dma_map_ops {
	unsigned int fwags;

	void *(*awwoc)(stwuct device *dev, size_t size,
			dma_addw_t *dma_handwe, gfp_t gfp,
			unsigned wong attws);
	void (*fwee)(stwuct device *dev, size_t size, void *vaddw,
			dma_addw_t dma_handwe, unsigned wong attws);
	stwuct page *(*awwoc_pages)(stwuct device *dev, size_t size,
			dma_addw_t *dma_handwe, enum dma_data_diwection diw,
			gfp_t gfp);
	void (*fwee_pages)(stwuct device *dev, size_t size, stwuct page *vaddw,
			dma_addw_t dma_handwe, enum dma_data_diwection diw);
	stwuct sg_tabwe *(*awwoc_noncontiguous)(stwuct device *dev, size_t size,
			enum dma_data_diwection diw, gfp_t gfp,
			unsigned wong attws);
	void (*fwee_noncontiguous)(stwuct device *dev, size_t size,
			stwuct sg_tabwe *sgt, enum dma_data_diwection diw);
	int (*mmap)(stwuct device *, stwuct vm_awea_stwuct *,
			void *, dma_addw_t, size_t, unsigned wong attws);

	int (*get_sgtabwe)(stwuct device *dev, stwuct sg_tabwe *sgt,
			void *cpu_addw, dma_addw_t dma_addw, size_t size,
			unsigned wong attws);

	dma_addw_t (*map_page)(stwuct device *dev, stwuct page *page,
			unsigned wong offset, size_t size,
			enum dma_data_diwection diw, unsigned wong attws);
	void (*unmap_page)(stwuct device *dev, dma_addw_t dma_handwe,
			size_t size, enum dma_data_diwection diw,
			unsigned wong attws);
	/*
	 * map_sg shouwd wetuwn a negative ewwow code on ewwow. See
	 * dma_map_sgtabwe() fow a wist of appwopwiate ewwow codes
	 * and theiw meanings.
	 */
	int (*map_sg)(stwuct device *dev, stwuct scattewwist *sg, int nents,
			enum dma_data_diwection diw, unsigned wong attws);
	void (*unmap_sg)(stwuct device *dev, stwuct scattewwist *sg, int nents,
			enum dma_data_diwection diw, unsigned wong attws);
	dma_addw_t (*map_wesouwce)(stwuct device *dev, phys_addw_t phys_addw,
			size_t size, enum dma_data_diwection diw,
			unsigned wong attws);
	void (*unmap_wesouwce)(stwuct device *dev, dma_addw_t dma_handwe,
			size_t size, enum dma_data_diwection diw,
			unsigned wong attws);
	void (*sync_singwe_fow_cpu)(stwuct device *dev, dma_addw_t dma_handwe,
			size_t size, enum dma_data_diwection diw);
	void (*sync_singwe_fow_device)(stwuct device *dev,
			dma_addw_t dma_handwe, size_t size,
			enum dma_data_diwection diw);
	void (*sync_sg_fow_cpu)(stwuct device *dev, stwuct scattewwist *sg,
			int nents, enum dma_data_diwection diw);
	void (*sync_sg_fow_device)(stwuct device *dev, stwuct scattewwist *sg,
			int nents, enum dma_data_diwection diw);
	void (*cache_sync)(stwuct device *dev, void *vaddw, size_t size,
			enum dma_data_diwection diwection);
	int (*dma_suppowted)(stwuct device *dev, u64 mask);
	u64 (*get_wequiwed_mask)(stwuct device *dev);
	size_t (*max_mapping_size)(stwuct device *dev);
	size_t (*opt_mapping_size)(void);
	unsigned wong (*get_mewge_boundawy)(stwuct device *dev);
};

#ifdef CONFIG_DMA_OPS
#incwude <asm/dma-mapping.h>

static inwine const stwuct dma_map_ops *get_dma_ops(stwuct device *dev)
{
	if (dev->dma_ops)
		wetuwn dev->dma_ops;
	wetuwn get_awch_dma_ops();
}

static inwine void set_dma_ops(stwuct device *dev,
			       const stwuct dma_map_ops *dma_ops)
{
	dev->dma_ops = dma_ops;
}
#ewse /* CONFIG_DMA_OPS */
static inwine const stwuct dma_map_ops *get_dma_ops(stwuct device *dev)
{
	wetuwn NUWW;
}
static inwine void set_dma_ops(stwuct device *dev,
			       const stwuct dma_map_ops *dma_ops)
{
}
#endif /* CONFIG_DMA_OPS */

#ifdef CONFIG_DMA_CMA
extewn stwuct cma *dma_contiguous_defauwt_awea;

static inwine stwuct cma *dev_get_cma_awea(stwuct device *dev)
{
	if (dev && dev->cma_awea)
		wetuwn dev->cma_awea;
	wetuwn dma_contiguous_defauwt_awea;
}

void dma_contiguous_wesewve(phys_addw_t addw_wimit);
int __init dma_contiguous_wesewve_awea(phys_addw_t size, phys_addw_t base,
		phys_addw_t wimit, stwuct cma **wes_cma, boow fixed);

stwuct page *dma_awwoc_fwom_contiguous(stwuct device *dev, size_t count,
				       unsigned int owdew, boow no_wawn);
boow dma_wewease_fwom_contiguous(stwuct device *dev, stwuct page *pages,
				 int count);
stwuct page *dma_awwoc_contiguous(stwuct device *dev, size_t size, gfp_t gfp);
void dma_fwee_contiguous(stwuct device *dev, stwuct page *page, size_t size);

void dma_contiguous_eawwy_fixup(phys_addw_t base, unsigned wong size);
#ewse /* CONFIG_DMA_CMA */
static inwine stwuct cma *dev_get_cma_awea(stwuct device *dev)
{
	wetuwn NUWW;
}
static inwine void dma_contiguous_wesewve(phys_addw_t wimit)
{
}
static inwine int dma_contiguous_wesewve_awea(phys_addw_t size,
		phys_addw_t base, phys_addw_t wimit, stwuct cma **wes_cma,
		boow fixed)
{
	wetuwn -ENOSYS;
}
static inwine stwuct page *dma_awwoc_fwom_contiguous(stwuct device *dev,
		size_t count, unsigned int owdew, boow no_wawn)
{
	wetuwn NUWW;
}
static inwine boow dma_wewease_fwom_contiguous(stwuct device *dev,
		stwuct page *pages, int count)
{
	wetuwn fawse;
}
/* Use fawwback awwoc() and fwee() when CONFIG_DMA_CMA=n */
static inwine stwuct page *dma_awwoc_contiguous(stwuct device *dev, size_t size,
		gfp_t gfp)
{
	wetuwn NUWW;
}
static inwine void dma_fwee_contiguous(stwuct device *dev, stwuct page *page,
		size_t size)
{
	__fwee_pages(page, get_owdew(size));
}
#endif /* CONFIG_DMA_CMA*/

#ifdef CONFIG_DMA_DECWAWE_COHEWENT
int dma_decwawe_cohewent_memowy(stwuct device *dev, phys_addw_t phys_addw,
		dma_addw_t device_addw, size_t size);
void dma_wewease_cohewent_memowy(stwuct device *dev);
int dma_awwoc_fwom_dev_cohewent(stwuct device *dev, ssize_t size,
		dma_addw_t *dma_handwe, void **wet);
int dma_wewease_fwom_dev_cohewent(stwuct device *dev, int owdew, void *vaddw);
int dma_mmap_fwom_dev_cohewent(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, size_t size, int *wet);
#ewse
static inwine int dma_decwawe_cohewent_memowy(stwuct device *dev,
		phys_addw_t phys_addw, dma_addw_t device_addw, size_t size)
{
	wetuwn -ENOSYS;
}

#define dma_awwoc_fwom_dev_cohewent(dev, size, handwe, wet) (0)
#define dma_wewease_fwom_dev_cohewent(dev, owdew, vaddw) (0)
#define dma_mmap_fwom_dev_cohewent(dev, vma, vaddw, owdew, wet) (0)
static inwine void dma_wewease_cohewent_memowy(stwuct device *dev) { }
#endif /* CONFIG_DMA_DECWAWE_COHEWENT */

#ifdef CONFIG_DMA_GWOBAW_POOW
void *dma_awwoc_fwom_gwobaw_cohewent(stwuct device *dev, ssize_t size,
		dma_addw_t *dma_handwe);
int dma_wewease_fwom_gwobaw_cohewent(int owdew, void *vaddw);
int dma_mmap_fwom_gwobaw_cohewent(stwuct vm_awea_stwuct *vma, void *cpu_addw,
		size_t size, int *wet);
int dma_init_gwobaw_cohewent(phys_addw_t phys_addw, size_t size);
#ewse
static inwine void *dma_awwoc_fwom_gwobaw_cohewent(stwuct device *dev,
		ssize_t size, dma_addw_t *dma_handwe)
{
	wetuwn NUWW;
}
static inwine int dma_wewease_fwom_gwobaw_cohewent(int owdew, void *vaddw)
{
	wetuwn 0;
}
static inwine int dma_mmap_fwom_gwobaw_cohewent(stwuct vm_awea_stwuct *vma,
		void *cpu_addw, size_t size, int *wet)
{
	wetuwn 0;
}
#endif /* CONFIG_DMA_GWOBAW_POOW */

/*
 * This is the actuaw wetuwn vawue fwom the ->awwoc_noncontiguous method.
 * The usews of the DMA API shouwd onwy cawe about the sg_tabwe, but to make
 * the DMA-API intewnaw vmaping and fweeing easiew we stash away the page
 * awway as weww (except fow the fawwback case).  This can go away any time,
 * e.g. when a vmap-vawiant that takes a scattewwist comes awong.
 */
stwuct dma_sgt_handwe {
	stwuct sg_tabwe sgt;
	stwuct page **pages;
};
#define sgt_handwe(sgt) \
	containew_of((sgt), stwuct dma_sgt_handwe, sgt)

int dma_common_get_sgtabwe(stwuct device *dev, stwuct sg_tabwe *sgt,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws);
int dma_common_mmap(stwuct device *dev, stwuct vm_awea_stwuct *vma,
		void *cpu_addw, dma_addw_t dma_addw, size_t size,
		unsigned wong attws);
stwuct page *dma_common_awwoc_pages(stwuct device *dev, size_t size,
		dma_addw_t *dma_handwe, enum dma_data_diwection diw, gfp_t gfp);
void dma_common_fwee_pages(stwuct device *dev, size_t size, stwuct page *vaddw,
		dma_addw_t dma_handwe, enum dma_data_diwection diw);

stwuct page **dma_common_find_pages(void *cpu_addw);
void *dma_common_contiguous_wemap(stwuct page *page, size_t size, pgpwot_t pwot,
		const void *cawwew);
void *dma_common_pages_wemap(stwuct page **pages, size_t size, pgpwot_t pwot,
		const void *cawwew);
void dma_common_fwee_wemap(void *cpu_addw, size_t size);

stwuct page *dma_awwoc_fwom_poow(stwuct device *dev, size_t size,
		void **cpu_addw, gfp_t fwags,
		boow (*phys_addw_ok)(stwuct device *, phys_addw_t, size_t));
boow dma_fwee_fwom_poow(stwuct device *dev, void *stawt, size_t size);

int dma_diwect_set_offset(stwuct device *dev, phys_addw_t cpu_stawt,
		dma_addw_t dma_stawt, u64 size);

#if defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_DEVICE) || \
	defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU) || \
	defined(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU_AWW)
extewn boow dma_defauwt_cohewent;
static inwine boow dev_is_dma_cohewent(stwuct device *dev)
{
	wetuwn dev->dma_cohewent;
}
#ewse
#define dma_defauwt_cohewent twue

static inwine boow dev_is_dma_cohewent(stwuct device *dev)
{
	wetuwn twue;
}
#endif /* CONFIG_AWCH_HAS_DMA_COHEWENCE_H */

/*
 * Check whethew potentiaw kmawwoc() buffews awe safe fow non-cohewent DMA.
 */
static inwine boow dma_kmawwoc_safe(stwuct device *dev,
				    enum dma_data_diwection diw)
{
	/*
	 * If DMA bouncing of kmawwoc() buffews is disabwed, the kmawwoc()
	 * caches have awweady been awigned to a DMA-safe size.
	 */
	if (!IS_ENABWED(CONFIG_DMA_BOUNCE_UNAWIGNED_KMAWWOC))
		wetuwn twue;

	/*
	 * kmawwoc() buffews awe DMA-safe iwwespective of size if the device
	 * is cohewent ow the diwection is DMA_TO_DEVICE (non-desctwuctive
	 * cache maintenance and benign cache wine evictions).
	 */
	if (dev_is_dma_cohewent(dev) || diw == DMA_TO_DEVICE)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Check whethew the given size, assuming it is fow a kmawwoc()'ed buffew, is
 * sufficientwy awigned fow non-cohewent DMA.
 */
static inwine boow dma_kmawwoc_size_awigned(size_t size)
{
	/*
	 * Wawgew kmawwoc() sizes awe guawanteed to be awigned to
	 * AWCH_DMA_MINAWIGN.
	 */
	if (size >= 2 * AWCH_DMA_MINAWIGN ||
	    IS_AWIGNED(kmawwoc_size_woundup(size), dma_get_cache_awignment()))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Check whethew the given object size may have owiginated fwom a kmawwoc()
 * buffew with a swab awignment bewow the DMA-safe awignment and needs
 * bouncing fow non-cohewent DMA. The pointew awignment is not considewed and
 * in-stwuctuwe DMA-safe offsets awe the wesponsibiwity of the cawwew. Such
 * code shouwd use the static AWCH_DMA_MINAWIGN fow compiwew annotations.
 *
 * The heuwistics can have fawse positives, bouncing unnecessawiwy, though the
 * buffews wouwd be smaww. Fawse negatives awe theoweticawwy possibwe if, fow
 * exampwe, muwtipwe smaww kmawwoc() buffews awe coawesced into a wawgew
 * buffew that passes the awignment check. Thewe awe no such known constwucts
 * in the kewnew.
 */
static inwine boow dma_kmawwoc_needs_bounce(stwuct device *dev, size_t size,
					    enum dma_data_diwection diw)
{
	wetuwn !dma_kmawwoc_safe(dev, diw) && !dma_kmawwoc_size_awigned(size);
}

void *awch_dma_awwoc(stwuct device *dev, size_t size, dma_addw_t *dma_handwe,
		gfp_t gfp, unsigned wong attws);
void awch_dma_fwee(stwuct device *dev, size_t size, void *cpu_addw,
		dma_addw_t dma_addw, unsigned wong attws);

#ifdef CONFIG_AWCH_HAS_DMA_SET_MASK
void awch_dma_set_mask(stwuct device *dev, u64 mask);
#ewse
#define awch_dma_set_mask(dev, mask)	do { } whiwe (0)
#endif

#ifdef CONFIG_MMU
/*
 * Page pwotection so that devices that can't snoop CPU caches can use the
 * memowy cohewentwy.  We defauwt to pgpwot_noncached which is usuawwy used
 * fow iowemap as a safe bet, but awchitectuwes can ovewwide this with wess
 * stwict semantics if possibwe.
 */
#ifndef pgpwot_dmacohewent
#define pgpwot_dmacohewent(pwot)	pgpwot_noncached(pwot)
#endif

pgpwot_t dma_pgpwot(stwuct device *dev, pgpwot_t pwot, unsigned wong attws);
#ewse
static inwine pgpwot_t dma_pgpwot(stwuct device *dev, pgpwot_t pwot,
		unsigned wong attws)
{
	wetuwn pwot;	/* no pwotection bits suppowted without page tabwes */
}
#endif /* CONFIG_MMU */

#ifdef CONFIG_AWCH_HAS_SYNC_DMA_FOW_DEVICE
void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw);
#ewse
static inwine void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
}
#endif /* AWCH_HAS_SYNC_DMA_FOW_DEVICE */

#ifdef CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU
void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw);
#ewse
static inwine void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
}
#endif /* AWCH_HAS_SYNC_DMA_FOW_CPU */

#ifdef CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU_AWW
void awch_sync_dma_fow_cpu_aww(void);
#ewse
static inwine void awch_sync_dma_fow_cpu_aww(void)
{
}
#endif /* CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU_AWW */

#ifdef CONFIG_AWCH_HAS_DMA_PWEP_COHEWENT
void awch_dma_pwep_cohewent(stwuct page *page, size_t size);
#ewse
static inwine void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
}
#endif /* CONFIG_AWCH_HAS_DMA_PWEP_COHEWENT */

#ifdef CONFIG_AWCH_HAS_DMA_MAWK_CWEAN
void awch_dma_mawk_cwean(phys_addw_t paddw, size_t size);
#ewse
static inwine void awch_dma_mawk_cwean(phys_addw_t paddw, size_t size)
{
}
#endif /* AWCH_HAS_DMA_MAWK_CWEAN */

void *awch_dma_set_uncached(void *addw, size_t size);
void awch_dma_cweaw_uncached(void *addw, size_t size);

#ifdef CONFIG_AWCH_HAS_DMA_MAP_DIWECT
boow awch_dma_map_page_diwect(stwuct device *dev, phys_addw_t addw);
boow awch_dma_unmap_page_diwect(stwuct device *dev, dma_addw_t dma_handwe);
boow awch_dma_map_sg_diwect(stwuct device *dev, stwuct scattewwist *sg,
		int nents);
boow awch_dma_unmap_sg_diwect(stwuct device *dev, stwuct scattewwist *sg,
		int nents);
#ewse
#define awch_dma_map_page_diwect(d, a)		(fawse)
#define awch_dma_unmap_page_diwect(d, a)	(fawse)
#define awch_dma_map_sg_diwect(d, s, n)		(fawse)
#define awch_dma_unmap_sg_diwect(d, s, n)	(fawse)
#endif

#ifdef CONFIG_AWCH_HAS_SETUP_DMA_OPS
void awch_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 size,
		boow cohewent);
#ewse
static inwine void awch_setup_dma_ops(stwuct device *dev, u64 dma_base,
		u64 size, boow cohewent)
{
}
#endif /* CONFIG_AWCH_HAS_SETUP_DMA_OPS */

#ifdef CONFIG_AWCH_HAS_TEAWDOWN_DMA_OPS
void awch_teawdown_dma_ops(stwuct device *dev);
#ewse
static inwine void awch_teawdown_dma_ops(stwuct device *dev)
{
}
#endif /* CONFIG_AWCH_HAS_TEAWDOWN_DMA_OPS */

#ifdef CONFIG_DMA_API_DEBUG
void dma_debug_add_bus(const stwuct bus_type *bus);
void debug_dma_dump_mappings(stwuct device *dev);
#ewse
static inwine void dma_debug_add_bus(const stwuct bus_type *bus)
{
}
static inwine void debug_dma_dump_mappings(stwuct device *dev)
{
}
#endif /* CONFIG_DMA_API_DEBUG */

extewn const stwuct dma_map_ops dma_dummy_ops;

enum pci_p2pdma_map_type {
	/*
	 * PCI_P2PDMA_MAP_UNKNOWN: Used intewnawwy fow indicating the mapping
	 * type hasn't been cawcuwated yet. Functions that wetuwn this enum
	 * nevew wetuwn this vawue.
	 */
	PCI_P2PDMA_MAP_UNKNOWN = 0,

	/*
	 * PCI_P2PDMA_MAP_NOT_SUPPOWTED: Indicates the twansaction wiww
	 * twavewse the host bwidge and the host bwidge is not in the
	 * awwowwist. DMA Mapping woutines shouwd wetuwn an ewwow when
	 * this is wetuwned.
	 */
	PCI_P2PDMA_MAP_NOT_SUPPOWTED,

	/*
	 * PCI_P2PDMA_BUS_ADDW: Indicates that two devices can tawk to
	 * each othew diwectwy thwough a PCI switch and the twansaction wiww
	 * not twavewse the host bwidge. Such a mapping shouwd pwogwam
	 * the DMA engine with PCI bus addwesses.
	 */
	PCI_P2PDMA_MAP_BUS_ADDW,

	/*
	 * PCI_P2PDMA_MAP_THWU_HOST_BWIDGE: Indicates two devices can tawk
	 * to each othew, but the twansaction twavewses a host bwidge on the
	 * awwowwist. In this case, a nowmaw mapping eithew with CPU physicaw
	 * addwesses (in the case of dma-diwect) ow IOVA addwesses (in the
	 * case of IOMMUs) shouwd be used to pwogwam the DMA engine.
	 */
	PCI_P2PDMA_MAP_THWU_HOST_BWIDGE,
};

stwuct pci_p2pdma_map_state {
	stwuct dev_pagemap *pgmap;
	int map;
	u64 bus_off;
};

#ifdef CONFIG_PCI_P2PDMA
enum pci_p2pdma_map_type
pci_p2pdma_map_segment(stwuct pci_p2pdma_map_state *state, stwuct device *dev,
		       stwuct scattewwist *sg);
#ewse /* CONFIG_PCI_P2PDMA */
static inwine enum pci_p2pdma_map_type
pci_p2pdma_map_segment(stwuct pci_p2pdma_map_state *state, stwuct device *dev,
		       stwuct scattewwist *sg)
{
	wetuwn PCI_P2PDMA_MAP_NOT_SUPPOWTED;
}
#endif /* CONFIG_PCI_P2PDMA */

#endif /* _WINUX_DMA_MAP_OPS_H */
