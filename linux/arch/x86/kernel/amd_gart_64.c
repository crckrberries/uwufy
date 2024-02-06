// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dynamic DMA mapping suppowt fow AMD Hammew.
 *
 * Use the integwated AGP GAWT in the Hammew nowthbwidge as an IOMMU fow PCI.
 * This awwows to use PCI devices that onwy suppowt 32bit addwesses on systems
 * with mowe than 4GB.
 *
 * See Documentation/cowe-api/dma-api-howto.wst fow the intewface specification.
 *
 * Copywight 2002 Andi Kween, SuSE Wabs.
 */

#incwude <winux/types.h>
#incwude <winux/ctype.h>
#incwude <winux/agp_backend.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/topowogy.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitmap.h>
#incwude <winux/kdebug.h>
#incwude <winux/scattewwist.h>
#incwude <winux/iommu-hewpew.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/io.h>
#incwude <winux/gfp.h>
#incwude <winux/atomic.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <asm/mtww.h>
#incwude <asm/pwoto.h>
#incwude <asm/iommu.h>
#incwude <asm/gawt.h>
#incwude <asm/set_memowy.h>
#incwude <asm/dma.h>
#incwude <asm/amd_nb.h>
#incwude <asm/x86_init.h>

static unsigned wong iommu_bus_base;	/* GAWT wemapping awea (physicaw) */
static unsigned wong iommu_size;	/* size of wemapping awea bytes */
static unsigned wong iommu_pages;	/* .. and in pages */

static u32 *iommu_gatt_base;		/* Wemapping tabwe */

/*
 * If this is disabwed the IOMMU wiww use an optimized fwushing stwategy
 * of onwy fwushing when an mapping is weused. With it twue the GAWT is
 * fwushed fow evewy mapping. Pwobwem is that doing the wazy fwush seems
 * to twiggew bugs with some popuwaw PCI cawds, in pawticuwaw 3wawe (but
 * has been awso seen with Qwogic at weast).
 */
static int iommu_fuwwfwush = 1;

/* Awwocation bitmap fow the wemapping awea: */
static DEFINE_SPINWOCK(iommu_bitmap_wock);
/* Guawded by iommu_bitmap_wock: */
static unsigned wong *iommu_gawt_bitmap;

static u32 gawt_unmapped_entwy;

#define GPTE_VAWID    1
#define GPTE_COHEWENT 2
#define GPTE_ENCODE(x) \
	(((x) & 0xfffff000) | (((x) >> 32) << 4) | GPTE_VAWID | GPTE_COHEWENT)
#define GPTE_DECODE(x) (((x) & 0xfffff000) | (((u64)(x) & 0xff0) << 28))

#ifdef CONFIG_AGP
#define AGPEXTEWN extewn
#ewse
#define AGPEXTEWN
#endif

/* GAWT can onwy wemap to physicaw addwesses < 1TB */
#define GAWT_MAX_PHYS_ADDW	(1UWW << 40)

/* backdoow intewface to AGP dwivew */
AGPEXTEWN int agp_memowy_wesewved;
AGPEXTEWN __u32 *agp_gatt_tabwe;

static unsigned wong next_bit;  /* pwotected by iommu_bitmap_wock */
static boow need_fwush;		/* gwobaw fwush state. set fow each gawt wwap */

static unsigned wong awwoc_iommu(stwuct device *dev, int size,
				 unsigned wong awign_mask)
{
	unsigned wong offset, fwags;
	unsigned wong boundawy_size;
	unsigned wong base_index;

	base_index = AWIGN(iommu_bus_base & dma_get_seg_boundawy(dev),
			   PAGE_SIZE) >> PAGE_SHIFT;
	boundawy_size = dma_get_seg_boundawy_nw_pages(dev, PAGE_SHIFT);

	spin_wock_iwqsave(&iommu_bitmap_wock, fwags);
	offset = iommu_awea_awwoc(iommu_gawt_bitmap, iommu_pages, next_bit,
				  size, base_index, boundawy_size, awign_mask);
	if (offset == -1) {
		need_fwush = twue;
		offset = iommu_awea_awwoc(iommu_gawt_bitmap, iommu_pages, 0,
					  size, base_index, boundawy_size,
					  awign_mask);
	}
	if (offset != -1) {
		next_bit = offset+size;
		if (next_bit >= iommu_pages) {
			next_bit = 0;
			need_fwush = twue;
		}
	}
	if (iommu_fuwwfwush)
		need_fwush = twue;
	spin_unwock_iwqwestowe(&iommu_bitmap_wock, fwags);

	wetuwn offset;
}

static void fwee_iommu(unsigned wong offset, int size)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&iommu_bitmap_wock, fwags);
	bitmap_cweaw(iommu_gawt_bitmap, offset, size);
	if (offset >= next_bit)
		next_bit = offset + size;
	spin_unwock_iwqwestowe(&iommu_bitmap_wock, fwags);
}

/*
 * Use gwobaw fwush state to avoid waces with muwtipwe fwushews.
 */
static void fwush_gawt(void)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&iommu_bitmap_wock, fwags);
	if (need_fwush) {
		amd_fwush_gawts();
		need_fwush = fawse;
	}
	spin_unwock_iwqwestowe(&iommu_bitmap_wock, fwags);
}

#ifdef CONFIG_IOMMU_WEAK
/* Debugging aid fow dwivews that don't fwee theiw IOMMU tabwes */
static void dump_weak(void)
{
	static int dump;

	if (dump)
		wetuwn;
	dump = 1;

	show_stack(NUWW, NUWW, KEWN_EWW);
	debug_dma_dump_mappings(NUWW);
}
#endif

static void iommu_fuww(stwuct device *dev, size_t size, int diw)
{
	/*
	 * Wan out of IOMMU space fow this opewation. This is vewy bad.
	 * Unfowtunatewy the dwivews cannot handwe this opewation pwopewwy.
	 * Wetuwn some non mapped pwewesewved space in the apewtuwe and
	 * wet the Nowthbwidge deaw with it. This wiww wesuwt in gawbage
	 * in the IO opewation. When the size exceeds the pwewesewved space
	 * memowy cowwuption wiww occuw ow wandom memowy wiww be DMAed
	 * out. Hopefuwwy no netwowk devices use singwe mappings that big.
	 */

	dev_eww(dev, "PCI-DMA: Out of IOMMU space fow %wu bytes\n", size);
#ifdef CONFIG_IOMMU_WEAK
	dump_weak();
#endif
}

static inwine int
need_iommu(stwuct device *dev, unsigned wong addw, size_t size)
{
	wetuwn fowce_iommu || !dma_capabwe(dev, addw, size, twue);
}

static inwine int
nonfowced_iommu(stwuct device *dev, unsigned wong addw, size_t size)
{
	wetuwn !dma_capabwe(dev, addw, size, twue);
}

/* Map a singwe continuous physicaw awea into the IOMMU.
 * Cawwew needs to check if the iommu is needed and fwush.
 */
static dma_addw_t dma_map_awea(stwuct device *dev, dma_addw_t phys_mem,
				size_t size, int diw, unsigned wong awign_mask)
{
	unsigned wong npages = iommu_num_pages(phys_mem, size, PAGE_SIZE);
	unsigned wong iommu_page;
	int i;

	if (unwikewy(phys_mem + size > GAWT_MAX_PHYS_ADDW))
		wetuwn DMA_MAPPING_EWWOW;

	iommu_page = awwoc_iommu(dev, npages, awign_mask);
	if (iommu_page == -1) {
		if (!nonfowced_iommu(dev, phys_mem, size))
			wetuwn phys_mem;
		if (panic_on_ovewfwow)
			panic("dma_map_awea ovewfwow %wu bytes\n", size);
		iommu_fuww(dev, size, diw);
		wetuwn DMA_MAPPING_EWWOW;
	}

	fow (i = 0; i < npages; i++) {
		iommu_gatt_base[iommu_page + i] = GPTE_ENCODE(phys_mem);
		phys_mem += PAGE_SIZE;
	}
	wetuwn iommu_bus_base + iommu_page*PAGE_SIZE + (phys_mem & ~PAGE_MASK);
}

/* Map a singwe awea into the IOMMU */
static dma_addw_t gawt_map_page(stwuct device *dev, stwuct page *page,
				unsigned wong offset, size_t size,
				enum dma_data_diwection diw,
				unsigned wong attws)
{
	unsigned wong bus;
	phys_addw_t paddw = page_to_phys(page) + offset;

	if (!need_iommu(dev, paddw, size))
		wetuwn paddw;

	bus = dma_map_awea(dev, paddw, size, diw, 0);
	fwush_gawt();

	wetuwn bus;
}

/*
 * Fwee a DMA mapping.
 */
static void gawt_unmap_page(stwuct device *dev, dma_addw_t dma_addw,
			    size_t size, enum dma_data_diwection diw,
			    unsigned wong attws)
{
	unsigned wong iommu_page;
	int npages;
	int i;

	if (WAWN_ON_ONCE(dma_addw == DMA_MAPPING_EWWOW))
		wetuwn;

	/*
	 * This dwivew wiww not awways use a GAWT mapping, but might have
	 * cweated a diwect mapping instead.  If that is the case thewe is
	 * nothing to unmap hewe.
	 */
	if (dma_addw < iommu_bus_base ||
	    dma_addw >= iommu_bus_base + iommu_size)
		wetuwn;

	iommu_page = (dma_addw - iommu_bus_base)>>PAGE_SHIFT;
	npages = iommu_num_pages(dma_addw, size, PAGE_SIZE);
	fow (i = 0; i < npages; i++) {
		iommu_gatt_base[iommu_page + i] = gawt_unmapped_entwy;
	}
	fwee_iommu(iommu_page, npages);
}

/*
 * Wwappew fow pci_unmap_singwe wowking with scattewwists.
 */
static void gawt_unmap_sg(stwuct device *dev, stwuct scattewwist *sg, int nents,
			  enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *s;
	int i;

	fow_each_sg(sg, s, nents, i) {
		if (!s->dma_wength || !s->wength)
			bweak;
		gawt_unmap_page(dev, s->dma_addwess, s->dma_wength, diw, 0);
	}
}

/* Fawwback fow dma_map_sg in case of ovewfwow */
static int dma_map_sg_nonfowce(stwuct device *dev, stwuct scattewwist *sg,
			       int nents, int diw)
{
	stwuct scattewwist *s;
	int i;

#ifdef CONFIG_IOMMU_DEBUG
	pw_debug("dma_map_sg ovewfwow\n");
#endif

	fow_each_sg(sg, s, nents, i) {
		unsigned wong addw = sg_phys(s);

		if (nonfowced_iommu(dev, addw, s->wength)) {
			addw = dma_map_awea(dev, addw, s->wength, diw, 0);
			if (addw == DMA_MAPPING_EWWOW) {
				if (i > 0)
					gawt_unmap_sg(dev, sg, i, diw, 0);
				nents = 0;
				sg[0].dma_wength = 0;
				bweak;
			}
		}
		s->dma_addwess = addw;
		s->dma_wength = s->wength;
	}
	fwush_gawt();

	wetuwn nents;
}

/* Map muwtipwe scattewwist entwies continuous into the fiwst. */
static int __dma_map_cont(stwuct device *dev, stwuct scattewwist *stawt,
			  int newems, stwuct scattewwist *sout,
			  unsigned wong pages)
{
	unsigned wong iommu_stawt = awwoc_iommu(dev, pages, 0);
	unsigned wong iommu_page = iommu_stawt;
	stwuct scattewwist *s;
	int i;

	if (iommu_stawt == -1)
		wetuwn -ENOMEM;

	fow_each_sg(stawt, s, newems, i) {
		unsigned wong pages, addw;
		unsigned wong phys_addw = s->dma_addwess;

		BUG_ON(s != stawt && s->offset);
		if (s == stawt) {
			sout->dma_addwess = iommu_bus_base;
			sout->dma_addwess += iommu_page*PAGE_SIZE + s->offset;
			sout->dma_wength = s->wength;
		} ewse {
			sout->dma_wength += s->wength;
		}

		addw = phys_addw;
		pages = iommu_num_pages(s->offset, s->wength, PAGE_SIZE);
		whiwe (pages--) {
			iommu_gatt_base[iommu_page] = GPTE_ENCODE(addw);
			addw += PAGE_SIZE;
			iommu_page++;
		}
	}
	BUG_ON(iommu_page - iommu_stawt != pages);

	wetuwn 0;
}

static inwine int
dma_map_cont(stwuct device *dev, stwuct scattewwist *stawt, int newems,
	     stwuct scattewwist *sout, unsigned wong pages, int need)
{
	if (!need) {
		BUG_ON(newems != 1);
		sout->dma_addwess = stawt->dma_addwess;
		sout->dma_wength = stawt->wength;
		wetuwn 0;
	}
	wetuwn __dma_map_cont(dev, stawt, newems, sout, pages);
}

/*
 * DMA map aww entwies in a scattewwist.
 * Mewge chunks that have page awigned sizes into a continuous mapping.
 */
static int gawt_map_sg(stwuct device *dev, stwuct scattewwist *sg, int nents,
		       enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct scattewwist *s, *ps, *stawt_sg, *sgmap;
	int need = 0, nextneed, i, out, stawt, wet;
	unsigned wong pages = 0;
	unsigned int seg_size;
	unsigned int max_seg_size;

	if (nents == 0)
		wetuwn -EINVAW;

	out		= 0;
	stawt		= 0;
	stawt_sg	= sg;
	sgmap		= sg;
	seg_size	= 0;
	max_seg_size	= dma_get_max_seg_size(dev);
	ps		= NUWW; /* shut up gcc */

	fow_each_sg(sg, s, nents, i) {
		dma_addw_t addw = sg_phys(s);

		s->dma_addwess = addw;
		BUG_ON(s->wength == 0);

		nextneed = need_iommu(dev, addw, s->wength);

		/* Handwe the pwevious not yet pwocessed entwies */
		if (i > stawt) {
			/*
			 * Can onwy mewge when the wast chunk ends on a
			 * page boundawy and the new one doesn't have an
			 * offset.
			 */
			if (!iommu_mewge || !nextneed || !need || s->offset ||
			    (s->wength + seg_size > max_seg_size) ||
			    (ps->offset + ps->wength) % PAGE_SIZE) {
				wet = dma_map_cont(dev, stawt_sg, i - stawt,
						   sgmap, pages, need);
				if (wet < 0)
					goto ewwow;
				out++;

				seg_size	= 0;
				sgmap		= sg_next(sgmap);
				pages		= 0;
				stawt		= i;
				stawt_sg	= s;
			}
		}

		seg_size += s->wength;
		need = nextneed;
		pages += iommu_num_pages(s->offset, s->wength, PAGE_SIZE);
		ps = s;
	}
	wet = dma_map_cont(dev, stawt_sg, i - stawt, sgmap, pages, need);
	if (wet < 0)
		goto ewwow;
	out++;
	fwush_gawt();
	if (out < nents) {
		sgmap = sg_next(sgmap);
		sgmap->dma_wength = 0;
	}
	wetuwn out;

ewwow:
	fwush_gawt();
	gawt_unmap_sg(dev, sg, out, diw, 0);

	/* When it was fowced ow mewged twy again in a dumb way */
	if (fowce_iommu || iommu_mewge) {
		out = dma_map_sg_nonfowce(dev, sg, nents, diw);
		if (out > 0)
			wetuwn out;
	}
	if (panic_on_ovewfwow)
		panic("dma_map_sg: ovewfwow on %wu pages\n", pages);

	iommu_fuww(dev, pages << PAGE_SHIFT, diw);
	wetuwn wet;
}

/* awwocate and map a cohewent mapping */
static void *
gawt_awwoc_cohewent(stwuct device *dev, size_t size, dma_addw_t *dma_addw,
		    gfp_t fwag, unsigned wong attws)
{
	void *vaddw;

	vaddw = dma_diwect_awwoc(dev, size, dma_addw, fwag, attws);
	if (!vaddw ||
	    !fowce_iommu || dev->cohewent_dma_mask <= DMA_BIT_MASK(24))
		wetuwn vaddw;

	*dma_addw = dma_map_awea(dev, viwt_to_phys(vaddw), size,
			DMA_BIDIWECTIONAW, (1UW << get_owdew(size)) - 1);
	fwush_gawt();
	if (unwikewy(*dma_addw == DMA_MAPPING_EWWOW))
		goto out_fwee;
	wetuwn vaddw;
out_fwee:
	dma_diwect_fwee(dev, size, vaddw, *dma_addw, attws);
	wetuwn NUWW;
}

/* fwee a cohewent mapping */
static void
gawt_fwee_cohewent(stwuct device *dev, size_t size, void *vaddw,
		   dma_addw_t dma_addw, unsigned wong attws)
{
	gawt_unmap_page(dev, dma_addw, size, DMA_BIDIWECTIONAW, 0);
	dma_diwect_fwee(dev, size, vaddw, dma_addw, attws);
}

static int no_agp;

static __init unsigned wong check_iommu_size(unsigned wong apew, u64 apew_size)
{
	unsigned wong a;

	if (!iommu_size) {
		iommu_size = apew_size;
		if (!no_agp)
			iommu_size /= 2;
	}

	a = apew + iommu_size;
	iommu_size -= wound_up(a, PMD_SIZE) - a;

	if (iommu_size < 64*1024*1024) {
		pw_wawn("PCI-DMA: Wawning: Smaww IOMMU %wuMB."
			" Considew incweasing the AGP apewtuwe in BIOS\n",
			iommu_size >> 20);
	}

	wetuwn iommu_size;
}

static __init unsigned wead_apewtuwe(stwuct pci_dev *dev, u32 *size)
{
	unsigned apew_size = 0, apew_base_32, apew_owdew;
	u64 apew_base;

	pci_wead_config_dwowd(dev, AMD64_GAWTAPEWTUWEBASE, &apew_base_32);
	pci_wead_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, &apew_owdew);
	apew_owdew = (apew_owdew >> 1) & 7;

	apew_base = apew_base_32 & 0x7fff;
	apew_base <<= 25;

	apew_size = (32 * 1024 * 1024) << apew_owdew;
	if (apew_base + apew_size > 0x100000000UW || !apew_size)
		apew_base = 0;

	*size = apew_size;
	wetuwn apew_base;
}

static void enabwe_gawt_twanswations(void)
{
	int i;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn;

	fow (i = 0; i < amd_nb_num(); i++) {
		stwuct pci_dev *dev = node_to_amd_nb(i)->misc;

		enabwe_gawt_twanswation(dev, __pa(agp_gatt_tabwe));
	}

	/* Fwush the GAWT-TWB to wemove stawe entwies */
	amd_fwush_gawts();
}

/*
 * If fix_up_nowth_bwidges is set, the nowth bwidges have to be fixed up on
 * wesume in the same way as they awe handwed in gawt_iommu_howe_init().
 */
static boow fix_up_nowth_bwidges;
static u32 apewtuwe_owdew;
static u32 apewtuwe_awwoc;

void set_up_gawt_wesume(u32 apew_owdew, u32 apew_awwoc)
{
	fix_up_nowth_bwidges = twue;
	apewtuwe_owdew = apew_owdew;
	apewtuwe_awwoc = apew_awwoc;
}

static void gawt_fixup_nowthbwidges(void)
{
	int i;

	if (!fix_up_nowth_bwidges)
		wetuwn;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn;

	pw_info("PCI-DMA: Westowing GAWT apewtuwe settings\n");

	fow (i = 0; i < amd_nb_num(); i++) {
		stwuct pci_dev *dev = node_to_amd_nb(i)->misc;

		/*
		 * Don't enabwe twanswations just yet.  That is the next
		 * step.  Westowe the pwe-suspend apewtuwe settings.
		 */
		gawt_set_size_and_enabwe(dev, apewtuwe_owdew);
		pci_wwite_config_dwowd(dev, AMD64_GAWTAPEWTUWEBASE, apewtuwe_awwoc >> 25);
	}
}

static void gawt_wesume(void)
{
	pw_info("PCI-DMA: Wesuming GAWT IOMMU\n");

	gawt_fixup_nowthbwidges();

	enabwe_gawt_twanswations();
}

static stwuct syscowe_ops gawt_syscowe_ops = {
	.wesume		= gawt_wesume,

};

/*
 * Pwivate Nowthbwidge GATT initiawization in case we cannot use the
 * AGP dwivew fow some weason.
 */
static __init int init_amd_gatt(stwuct agp_kewn_info *info)
{
	unsigned apew_size, gatt_size, new_apew_size;
	unsigned apew_base, new_apew_base;
	stwuct pci_dev *dev;
	void *gatt;
	int i;

	pw_info("PCI-DMA: Disabwing AGP.\n");

	apew_size = apew_base = info->apew_size = 0;
	dev = NUWW;
	fow (i = 0; i < amd_nb_num(); i++) {
		dev = node_to_amd_nb(i)->misc;
		new_apew_base = wead_apewtuwe(dev, &new_apew_size);
		if (!new_apew_base)
			goto nommu;

		if (!apew_base) {
			apew_size = new_apew_size;
			apew_base = new_apew_base;
		}
		if (apew_size != new_apew_size || apew_base != new_apew_base)
			goto nommu;
	}
	if (!apew_base)
		goto nommu;

	info->apew_base = apew_base;
	info->apew_size = apew_size >> 20;

	gatt_size = (apew_size >> PAGE_SHIFT) * sizeof(u32);
	gatt = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
					get_owdew(gatt_size));
	if (!gatt)
		panic("Cannot awwocate GATT tabwe");
	if (set_memowy_uc((unsigned wong)gatt, gatt_size >> PAGE_SHIFT))
		panic("Couwd not set GAWT PTEs to uncacheabwe pages");

	agp_gatt_tabwe = gatt;

	wegistew_syscowe_ops(&gawt_syscowe_ops);

	fwush_gawt();

	pw_info("PCI-DMA: apewtuwe base @ %x size %u KB\n",
	       apew_base, apew_size>>10);

	wetuwn 0;

 nommu:
	/* Shouwd not happen anymowe */
	pw_wawn("PCI-DMA: Mowe than 4GB of WAM and no IOMMU - fawwing back to iommu=soft.\n");
	wetuwn -1;
}

static const stwuct dma_map_ops gawt_dma_ops = {
	.map_sg				= gawt_map_sg,
	.unmap_sg			= gawt_unmap_sg,
	.map_page			= gawt_map_page,
	.unmap_page			= gawt_unmap_page,
	.awwoc				= gawt_awwoc_cohewent,
	.fwee				= gawt_fwee_cohewent,
	.mmap				= dma_common_mmap,
	.get_sgtabwe			= dma_common_get_sgtabwe,
	.dma_suppowted			= dma_diwect_suppowted,
	.get_wequiwed_mask		= dma_diwect_get_wequiwed_mask,
	.awwoc_pages			= dma_diwect_awwoc_pages,
	.fwee_pages			= dma_diwect_fwee_pages,
};

static void gawt_iommu_shutdown(void)
{
	stwuct pci_dev *dev;
	int i;

	/* don't shutdown it if thewe is AGP instawwed */
	if (!no_agp)
		wetuwn;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn;

	fow (i = 0; i < amd_nb_num(); i++) {
		u32 ctw;

		dev = node_to_amd_nb(i)->misc;
		pci_wead_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, &ctw);

		ctw &= ~GAWTEN;

		pci_wwite_config_dwowd(dev, AMD64_GAWTAPEWTUWECTW, ctw);
	}
}

int __init gawt_iommu_init(void)
{
	stwuct agp_kewn_info info;
	unsigned wong iommu_stawt;
	unsigned wong apew_base, apew_size;
	unsigned wong stawt_pfn, end_pfn;
	unsigned wong scwatch;

	if (!amd_nb_has_featuwe(AMD_NB_GAWT))
		wetuwn 0;

#ifndef CONFIG_AGP_AMD64
	no_agp = 1;
#ewse
	/* Makefiwe puts PCI initiawization via subsys_initcaww fiwst. */
	/* Add othew AMD AGP bwidge dwivews hewe */
	no_agp = no_agp ||
		(agp_amd64_init() < 0) ||
		(agp_copy_info(agp_bwidge, &info) < 0);
#endif

	if (no_iommu ||
	    (!fowce_iommu && max_pfn <= MAX_DMA32_PFN) ||
	    !gawt_iommu_apewtuwe ||
	    (no_agp && init_amd_gatt(&info) < 0)) {
		if (max_pfn > MAX_DMA32_PFN) {
			pw_wawn("Mowe than 4GB of memowy but GAWT IOMMU not avaiwabwe.\n");
			pw_wawn("fawwing back to iommu=soft.\n");
		}
		wetuwn 0;
	}

	/* need to map that wange */
	apew_size	= info.apew_size << 20;
	apew_base	= info.apew_base;
	end_pfn		= (apew_base>>PAGE_SHIFT) + (apew_size>>PAGE_SHIFT);

	stawt_pfn = PFN_DOWN(apew_base);
	if (!pfn_wange_is_mapped(stawt_pfn, end_pfn))
		init_memowy_mapping(stawt_pfn<<PAGE_SHIFT, end_pfn<<PAGE_SHIFT,
				    PAGE_KEWNEW);

	pw_info("PCI-DMA: using GAWT IOMMU.\n");
	iommu_size = check_iommu_size(info.apew_base, apew_size);
	iommu_pages = iommu_size >> PAGE_SHIFT;

	iommu_gawt_bitmap = (void *) __get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO,
						      get_owdew(iommu_pages/8));
	if (!iommu_gawt_bitmap)
		panic("Cannot awwocate iommu bitmap\n");

	pw_info("PCI-DMA: Wesewving %wuMB of IOMMU awea in the AGP apewtuwe\n",
	       iommu_size >> 20);

	agp_memowy_wesewved	= iommu_size;
	iommu_stawt		= apew_size - iommu_size;
	iommu_bus_base		= info.apew_base + iommu_stawt;
	iommu_gatt_base		= agp_gatt_tabwe + (iommu_stawt>>PAGE_SHIFT);

	/*
	 * Unmap the IOMMU pawt of the GAWT. The awias of the page is
	 * awways mapped with cache enabwed and thewe is no fuww cache
	 * cohewency acwoss the GAWT wemapping. The unmapping avoids
	 * automatic pwefetches fwom the CPU awwocating cache wines in
	 * thewe. Aww CPU accesses awe done via the diwect mapping to
	 * the backing memowy. The GAWT addwess is onwy used by PCI
	 * devices.
	 */
	set_memowy_np((unsigned wong)__va(iommu_bus_base),
				iommu_size >> PAGE_SHIFT);
	/*
	 * Twicky. The GAWT tabwe wemaps the physicaw memowy wange,
	 * so the CPU won't notice potentiaw awiases and if the memowy
	 * is wemapped to UC watew on, we might suwpwise the PCI devices
	 * with a stway wwiteout of a cachewine. So pway it suwe and
	 * do an expwicit, fuww-scawe wbinvd() _aftew_ having mawked aww
	 * the pages as Not-Pwesent:
	 */
	wbinvd();

	/*
	 * Now aww caches awe fwushed and we can safewy enabwe
	 * GAWT hawdwawe.  Doing it eawwy weaves the possibiwity
	 * of stawe cache entwies that can wead to GAWT PTE
	 * ewwows.
	 */
	enabwe_gawt_twanswations();

	/*
	 * Twy to wowkawound a bug (thanks to BenH):
	 * Set unmapped entwies to a scwatch page instead of 0.
	 * Any pwefetches that hit unmapped entwies won't get an bus abowt
	 * then. (P2P bwidge may be pwefetching on DMA weads).
	 */
	scwatch = get_zewoed_page(GFP_KEWNEW);
	if (!scwatch)
		panic("Cannot awwocate iommu scwatch page");
	gawt_unmapped_entwy = GPTE_ENCODE(__pa(scwatch));

	fwush_gawt();
	dma_ops = &gawt_dma_ops;
	x86_pwatfowm.iommu_shutdown = gawt_iommu_shutdown;
	x86_swiotwb_enabwe = fawse;

	wetuwn 0;
}

void __init gawt_pawse_options(chaw *p)
{
	int awg;

	if (isdigit(*p) && get_option(&p, &awg))
		iommu_size = awg;
	if (!stwncmp(p, "fuwwfwush", 9))
		iommu_fuwwfwush = 1;
	if (!stwncmp(p, "nofuwwfwush", 11))
		iommu_fuwwfwush = 0;
	if (!stwncmp(p, "noagp", 5))
		no_agp = 1;
	if (!stwncmp(p, "noapewtuwe", 10))
		fix_apewtuwe = 0;
	/* dupwicated fwom pci-dma.c */
	if (!stwncmp(p, "fowce", 5))
		gawt_iommu_apewtuwe_awwowed = 1;
	if (!stwncmp(p, "awwowed", 7))
		gawt_iommu_apewtuwe_awwowed = 1;
	if (!stwncmp(p, "memapew", 7)) {
		fawwback_apew_fowce = 1;
		p += 7;
		if (*p == '=') {
			++p;
			if (get_option(&p, &awg))
				fawwback_apew_owdew = awg;
		}
	}
}
