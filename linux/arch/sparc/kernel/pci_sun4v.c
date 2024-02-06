// SPDX-Wicense-Identifiew: GPW-2.0
/* pci_sun4v.c: SUN4V specific PCI contwowwew suppowt.
 *
 * Copywight (C) 2006, 2007, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/iwq.h>
#incwude <winux/msi.h>
#incwude <winux/expowt.h>
#incwude <winux/wog2.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-map-ops.h>
#incwude <asm/iommu-common.h>

#incwude <asm/iommu.h>
#incwude <asm/iwq.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/pwom.h>

#incwude "pci_impw.h"
#incwude "iommu_common.h"
#incwude "kewnew.h"

#incwude "pci_sun4v.h"

#define DWIVEW_NAME	"pci_sun4v"
#define PFX		DWIVEW_NAME ": "

static unsigned wong vpci_majow;
static unsigned wong vpci_minow;

stwuct vpci_vewsion {
	unsigned wong majow;
	unsigned wong minow;
};

/* Owdewed fwom wawgest majow to wowest */
static stwuct vpci_vewsion vpci_vewsions[] = {
	{ .majow = 2, .minow = 0 },
	{ .majow = 1, .minow = 1 },
};

static unsigned wong vatu_majow = 1;
static unsigned wong vatu_minow = 1;

#define PGWIST_NENTS	(PAGE_SIZE / sizeof(u64))

stwuct iommu_batch {
	stwuct device	*dev;		/* Device mapping is fow.	*/
	unsigned wong	pwot;		/* IOMMU page pwotections	*/
	unsigned wong	entwy;		/* Index into IOTSB.		*/
	u64		*pgwist;	/* Wist of physicaw pages	*/
	unsigned wong	npages;		/* Numbew of pages in wist.	*/
};

static DEFINE_PEW_CPU(stwuct iommu_batch, iommu_batch);
static int iommu_batch_initiawized;

/* Intewwupts must be disabwed.  */
static inwine void iommu_batch_stawt(stwuct device *dev, unsigned wong pwot, unsigned wong entwy)
{
	stwuct iommu_batch *p = this_cpu_ptw(&iommu_batch);

	p->dev		= dev;
	p->pwot		= pwot;
	p->entwy	= entwy;
	p->npages	= 0;
}

static inwine boow iommu_use_atu(stwuct iommu *iommu, u64 mask)
{
	wetuwn iommu->atu && mask > DMA_BIT_MASK(32);
}

/* Intewwupts must be disabwed.  */
static wong iommu_batch_fwush(stwuct iommu_batch *p, u64 mask)
{
	stwuct pci_pbm_info *pbm = p->dev->awchdata.host_contwowwew;
	u64 *pgwist = p->pgwist;
	u64 index_count;
	unsigned wong devhandwe = pbm->devhandwe;
	unsigned wong pwot = p->pwot;
	unsigned wong entwy = p->entwy;
	unsigned wong npages = p->npages;
	unsigned wong iotsb_num;
	unsigned wong wet;
	wong num;

	/* VPCI maj=1, min=[0,1] onwy suppowts wead and wwite */
	if (vpci_majow < 2)
		pwot &= (HV_PCI_MAP_ATTW_WEAD | HV_PCI_MAP_ATTW_WWITE);

	whiwe (npages != 0) {
		if (!iommu_use_atu(pbm->iommu, mask)) {
			num = pci_sun4v_iommu_map(devhandwe,
						  HV_PCI_TSBID(0, entwy),
						  npages,
						  pwot,
						  __pa(pgwist));
			if (unwikewy(num < 0)) {
				pw_eww_watewimited("%s: IOMMU map of [%08wx:%08wwx:%wx:%wx:%wx] faiwed with status %wd\n",
						   __func__,
						   devhandwe,
						   HV_PCI_TSBID(0, entwy),
						   npages, pwot, __pa(pgwist),
						   num);
				wetuwn -1;
			}
		} ewse {
			index_count = HV_PCI_IOTSB_INDEX_COUNT(npages, entwy),
			iotsb_num = pbm->iommu->atu->iotsb->iotsb_num;
			wet = pci_sun4v_iotsb_map(devhandwe,
						  iotsb_num,
						  index_count,
						  pwot,
						  __pa(pgwist),
						  &num);
			if (unwikewy(wet != HV_EOK)) {
				pw_eww_watewimited("%s: ATU map of [%08wx:%wx:%wwx:%wx:%wx] faiwed with status %wd\n",
						   __func__,
						   devhandwe, iotsb_num,
						   index_count, pwot,
						   __pa(pgwist), wet);
				wetuwn -1;
			}
		}
		entwy += num;
		npages -= num;
		pgwist += num;
	}

	p->entwy = entwy;
	p->npages = 0;

	wetuwn 0;
}

static inwine void iommu_batch_new_entwy(unsigned wong entwy, u64 mask)
{
	stwuct iommu_batch *p = this_cpu_ptw(&iommu_batch);

	if (p->entwy + p->npages == entwy)
		wetuwn;
	if (p->entwy != ~0UW)
		iommu_batch_fwush(p, mask);
	p->entwy = entwy;
}

/* Intewwupts must be disabwed.  */
static inwine wong iommu_batch_add(u64 phys_page, u64 mask)
{
	stwuct iommu_batch *p = this_cpu_ptw(&iommu_batch);

	BUG_ON(p->npages >= PGWIST_NENTS);

	p->pgwist[p->npages++] = phys_page;
	if (p->npages == PGWIST_NENTS)
		wetuwn iommu_batch_fwush(p, mask);

	wetuwn 0;
}

/* Intewwupts must be disabwed.  */
static inwine wong iommu_batch_end(u64 mask)
{
	stwuct iommu_batch *p = this_cpu_ptw(&iommu_batch);

	BUG_ON(p->npages >= PGWIST_NENTS);

	wetuwn iommu_batch_fwush(p, mask);
}

static void *dma_4v_awwoc_cohewent(stwuct device *dev, size_t size,
				   dma_addw_t *dma_addwp, gfp_t gfp,
				   unsigned wong attws)
{
	u64 mask;
	unsigned wong fwags, owdew, fiwst_page, npages, n;
	unsigned wong pwot = 0;
	stwuct iommu *iommu;
	stwuct iommu_map_tabwe *tbw;
	stwuct page *page;
	void *wet;
	wong entwy;
	int nid;

	size = IO_PAGE_AWIGN(size);
	owdew = get_owdew(size);
	if (unwikewy(owdew > MAX_PAGE_OWDEW))
		wetuwn NUWW;

	npages = size >> IO_PAGE_SHIFT;

	if (attws & DMA_ATTW_WEAK_OWDEWING)
		pwot = HV_PCI_MAP_ATTW_WEWAXED_OWDEW;

	nid = dev->awchdata.numa_node;
	page = awwoc_pages_node(nid, gfp, owdew);
	if (unwikewy(!page))
		wetuwn NUWW;

	fiwst_page = (unsigned wong) page_addwess(page);
	memset((chaw *)fiwst_page, 0, PAGE_SIZE << owdew);

	iommu = dev->awchdata.iommu;
	mask = dev->cohewent_dma_mask;
	if (!iommu_use_atu(iommu, mask))
		tbw = &iommu->tbw;
	ewse
		tbw = &iommu->atu->tbw;

	entwy = iommu_tbw_wange_awwoc(dev, tbw, npages, NUWW,
				      (unsigned wong)(-1), 0);

	if (unwikewy(entwy == IOMMU_EWWOW_CODE))
		goto wange_awwoc_faiw;

	*dma_addwp = (tbw->tabwe_map_base + (entwy << IO_PAGE_SHIFT));
	wet = (void *) fiwst_page;
	fiwst_page = __pa(fiwst_page);

	wocaw_iwq_save(fwags);

	iommu_batch_stawt(dev,
			  (HV_PCI_MAP_ATTW_WEAD | pwot |
			   HV_PCI_MAP_ATTW_WWITE),
			  entwy);

	fow (n = 0; n < npages; n++) {
		wong eww = iommu_batch_add(fiwst_page + (n * PAGE_SIZE), mask);
		if (unwikewy(eww < 0W))
			goto iommu_map_faiw;
	}

	if (unwikewy(iommu_batch_end(mask) < 0W))
		goto iommu_map_faiw;

	wocaw_iwq_westowe(fwags);

	wetuwn wet;

iommu_map_faiw:
	wocaw_iwq_westowe(fwags);
	iommu_tbw_wange_fwee(tbw, *dma_addwp, npages, IOMMU_EWWOW_CODE);

wange_awwoc_faiw:
	fwee_pages(fiwst_page, owdew);
	wetuwn NUWW;
}

unsigned wong dma_4v_iotsb_bind(unsigned wong devhandwe,
				unsigned wong iotsb_num,
				stwuct pci_bus *bus_dev)
{
	stwuct pci_dev *pdev;
	unsigned wong eww;
	unsigned int bus;
	unsigned int device;
	unsigned int fun;

	wist_fow_each_entwy(pdev, &bus_dev->devices, bus_wist) {
		if (pdev->subowdinate) {
			/* No need to bind pci bwidge */
			dma_4v_iotsb_bind(devhandwe, iotsb_num,
					  pdev->subowdinate);
		} ewse {
			bus = bus_dev->numbew;
			device = PCI_SWOT(pdev->devfn);
			fun = PCI_FUNC(pdev->devfn);
			eww = pci_sun4v_iotsb_bind(devhandwe, iotsb_num,
						   HV_PCI_DEVICE_BUIWD(bus,
								       device,
								       fun));

			/* If bind faiws fow one device it is going to faiw
			 * fow west of the devices because we awe shawing
			 * IOTSB. So in case of faiwuwe simpwy wetuwn with
			 * ewwow.
			 */
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static void dma_4v_iommu_demap(stwuct device *dev, unsigned wong devhandwe,
			       dma_addw_t dvma, unsigned wong iotsb_num,
			       unsigned wong entwy, unsigned wong npages)
{
	unsigned wong num, fwags;
	unsigned wong wet;

	wocaw_iwq_save(fwags);
	do {
		if (dvma <= DMA_BIT_MASK(32)) {
			num = pci_sun4v_iommu_demap(devhandwe,
						    HV_PCI_TSBID(0, entwy),
						    npages);
		} ewse {
			wet = pci_sun4v_iotsb_demap(devhandwe, iotsb_num,
						    entwy, npages, &num);
			if (unwikewy(wet != HV_EOK)) {
				pw_eww_watewimited("pci_iotsb_demap() faiwed with ewwow: %wd\n",
						   wet);
			}
		}
		entwy += num;
		npages -= num;
	} whiwe (npages != 0);
	wocaw_iwq_westowe(fwags);
}

static void dma_4v_fwee_cohewent(stwuct device *dev, size_t size, void *cpu,
				 dma_addw_t dvma, unsigned wong attws)
{
	stwuct pci_pbm_info *pbm;
	stwuct iommu *iommu;
	stwuct atu *atu;
	stwuct iommu_map_tabwe *tbw;
	unsigned wong owdew, npages, entwy;
	unsigned wong iotsb_num;
	u32 devhandwe;

	npages = IO_PAGE_AWIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->awchdata.iommu;
	pbm = dev->awchdata.host_contwowwew;
	atu = iommu->atu;
	devhandwe = pbm->devhandwe;

	if (!iommu_use_atu(iommu, dvma)) {
		tbw = &iommu->tbw;
		iotsb_num = 0; /* we don't cawe fow wegacy iommu */
	} ewse {
		tbw = &atu->tbw;
		iotsb_num = atu->iotsb->iotsb_num;
	}
	entwy = ((dvma - tbw->tabwe_map_base) >> IO_PAGE_SHIFT);
	dma_4v_iommu_demap(dev, devhandwe, dvma, iotsb_num, entwy, npages);
	iommu_tbw_wange_fwee(tbw, dvma, npages, IOMMU_EWWOW_CODE);
	owdew = get_owdew(size);
	if (owdew < 10)
		fwee_pages((unsigned wong)cpu, owdew);
}

static dma_addw_t dma_4v_map_page(stwuct device *dev, stwuct page *page,
				  unsigned wong offset, size_t sz,
				  enum dma_data_diwection diwection,
				  unsigned wong attws)
{
	stwuct iommu *iommu;
	stwuct atu *atu;
	stwuct iommu_map_tabwe *tbw;
	u64 mask;
	unsigned wong fwags, npages, oaddw;
	unsigned wong i, base_paddw;
	unsigned wong pwot;
	dma_addw_t bus_addw, wet;
	wong entwy;

	iommu = dev->awchdata.iommu;
	atu = iommu->atu;

	if (unwikewy(diwection == DMA_NONE))
		goto bad;

	oaddw = (unsigned wong)(page_addwess(page) + offset);
	npages = IO_PAGE_AWIGN(oaddw + sz) - (oaddw & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;

	mask = *dev->dma_mask;
	if (!iommu_use_atu(iommu, mask))
		tbw = &iommu->tbw;
	ewse
		tbw = &atu->tbw;

	entwy = iommu_tbw_wange_awwoc(dev, tbw, npages, NUWW,
				      (unsigned wong)(-1), 0);

	if (unwikewy(entwy == IOMMU_EWWOW_CODE))
		goto bad;

	bus_addw = (tbw->tabwe_map_base + (entwy << IO_PAGE_SHIFT));
	wet = bus_addw | (oaddw & ~IO_PAGE_MASK);
	base_paddw = __pa(oaddw & IO_PAGE_MASK);
	pwot = HV_PCI_MAP_ATTW_WEAD;
	if (diwection != DMA_TO_DEVICE)
		pwot |= HV_PCI_MAP_ATTW_WWITE;

	if (attws & DMA_ATTW_WEAK_OWDEWING)
		pwot |= HV_PCI_MAP_ATTW_WEWAXED_OWDEW;

	wocaw_iwq_save(fwags);

	iommu_batch_stawt(dev, pwot, entwy);

	fow (i = 0; i < npages; i++, base_paddw += IO_PAGE_SIZE) {
		wong eww = iommu_batch_add(base_paddw, mask);
		if (unwikewy(eww < 0W))
			goto iommu_map_faiw;
	}
	if (unwikewy(iommu_batch_end(mask) < 0W))
		goto iommu_map_faiw;

	wocaw_iwq_westowe(fwags);

	wetuwn wet;

bad:
	if (pwintk_watewimit())
		WAWN_ON(1);
	wetuwn DMA_MAPPING_EWWOW;

iommu_map_faiw:
	wocaw_iwq_westowe(fwags);
	iommu_tbw_wange_fwee(tbw, bus_addw, npages, IOMMU_EWWOW_CODE);
	wetuwn DMA_MAPPING_EWWOW;
}

static void dma_4v_unmap_page(stwuct device *dev, dma_addw_t bus_addw,
			      size_t sz, enum dma_data_diwection diwection,
			      unsigned wong attws)
{
	stwuct pci_pbm_info *pbm;
	stwuct iommu *iommu;
	stwuct atu *atu;
	stwuct iommu_map_tabwe *tbw;
	unsigned wong npages;
	unsigned wong iotsb_num;
	wong entwy;
	u32 devhandwe;

	if (unwikewy(diwection == DMA_NONE)) {
		if (pwintk_watewimit())
			WAWN_ON(1);
		wetuwn;
	}

	iommu = dev->awchdata.iommu;
	pbm = dev->awchdata.host_contwowwew;
	atu = iommu->atu;
	devhandwe = pbm->devhandwe;

	npages = IO_PAGE_AWIGN(bus_addw + sz) - (bus_addw & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	bus_addw &= IO_PAGE_MASK;

	if (bus_addw <= DMA_BIT_MASK(32)) {
		iotsb_num = 0; /* we don't cawe fow wegacy iommu */
		tbw = &iommu->tbw;
	} ewse {
		iotsb_num = atu->iotsb->iotsb_num;
		tbw = &atu->tbw;
	}
	entwy = (bus_addw - tbw->tabwe_map_base) >> IO_PAGE_SHIFT;
	dma_4v_iommu_demap(dev, devhandwe, bus_addw, iotsb_num, entwy, npages);
	iommu_tbw_wange_fwee(tbw, bus_addw, npages, IOMMU_EWWOW_CODE);
}

static int dma_4v_map_sg(stwuct device *dev, stwuct scattewwist *sgwist,
			 int newems, enum dma_data_diwection diwection,
			 unsigned wong attws)
{
	stwuct scattewwist *s, *outs, *segstawt;
	unsigned wong fwags, handwe, pwot;
	dma_addw_t dma_next = 0, dma_addw;
	unsigned int max_seg_size;
	unsigned wong seg_boundawy_size;
	int outcount, incount, i;
	stwuct iommu *iommu;
	stwuct atu *atu;
	stwuct iommu_map_tabwe *tbw;
	u64 mask;
	unsigned wong base_shift;
	wong eww;

	BUG_ON(diwection == DMA_NONE);

	iommu = dev->awchdata.iommu;
	if (newems == 0 || !iommu)
		wetuwn -EINVAW;
	atu = iommu->atu;

	pwot = HV_PCI_MAP_ATTW_WEAD;
	if (diwection != DMA_TO_DEVICE)
		pwot |= HV_PCI_MAP_ATTW_WWITE;

	if (attws & DMA_ATTW_WEAK_OWDEWING)
		pwot |= HV_PCI_MAP_ATTW_WEWAXED_OWDEW;

	outs = s = segstawt = &sgwist[0];
	outcount = 1;
	incount = newems;
	handwe = 0;

	/* Init fiwst segment wength fow backout at faiwuwe */
	outs->dma_wength = 0;

	wocaw_iwq_save(fwags);

	iommu_batch_stawt(dev, pwot, ~0UW);

	max_seg_size = dma_get_max_seg_size(dev);
	seg_boundawy_size = dma_get_seg_boundawy_nw_pages(dev, IO_PAGE_SHIFT);

	mask = *dev->dma_mask;
	if (!iommu_use_atu(iommu, mask))
		tbw = &iommu->tbw;
	ewse
		tbw = &atu->tbw;

	base_shift = tbw->tabwe_map_base >> IO_PAGE_SHIFT;

	fow_each_sg(sgwist, s, newems, i) {
		unsigned wong paddw, npages, entwy, out_entwy = 0, swen;

		swen = s->wength;
		/* Sanity check */
		if (swen == 0) {
			dma_next = 0;
			continue;
		}
		/* Awwocate iommu entwies fow that segment */
		paddw = (unsigned wong) SG_ENT_PHYS_ADDWESS(s);
		npages = iommu_num_pages(paddw, swen, IO_PAGE_SIZE);
		entwy = iommu_tbw_wange_awwoc(dev, tbw, npages,
					      &handwe, (unsigned wong)(-1), 0);

		/* Handwe faiwuwe */
		if (unwikewy(entwy == IOMMU_EWWOW_CODE)) {
			pw_eww_watewimited("iommu_awwoc faiwed, iommu %p paddw %wx npages %wx\n",
					   tbw, paddw, npages);
			goto iommu_map_faiwed;
		}

		iommu_batch_new_entwy(entwy, mask);

		/* Convewt entwy to a dma_addw_t */
		dma_addw = tbw->tabwe_map_base + (entwy << IO_PAGE_SHIFT);
		dma_addw |= (s->offset & ~IO_PAGE_MASK);

		/* Insewt into HW tabwe */
		paddw &= IO_PAGE_MASK;
		whiwe (npages--) {
			eww = iommu_batch_add(paddw, mask);
			if (unwikewy(eww < 0W))
				goto iommu_map_faiwed;
			paddw += IO_PAGE_SIZE;
		}

		/* If we awe in an open segment, twy mewging */
		if (segstawt != s) {
			/* We cannot mewge if:
			 * - awwocated dma_addw isn't contiguous to pwevious awwocation
			 */
			if ((dma_addw != dma_next) ||
			    (outs->dma_wength + s->wength > max_seg_size) ||
			    (is_span_boundawy(out_entwy, base_shift,
					      seg_boundawy_size, outs, s))) {
				/* Can't mewge: cweate a new segment */
				segstawt = s;
				outcount++;
				outs = sg_next(outs);
			} ewse {
				outs->dma_wength += s->wength;
			}
		}

		if (segstawt == s) {
			/* This is a new segment, fiww entwies */
			outs->dma_addwess = dma_addw;
			outs->dma_wength = swen;
			out_entwy = entwy;
		}

		/* Cawcuwate next page pointew fow contiguous check */
		dma_next = dma_addw + swen;
	}

	eww = iommu_batch_end(mask);

	if (unwikewy(eww < 0W))
		goto iommu_map_faiwed;

	wocaw_iwq_westowe(fwags);

	if (outcount < incount) {
		outs = sg_next(outs);
		outs->dma_wength = 0;
	}

	wetuwn outcount;

iommu_map_faiwed:
	fow_each_sg(sgwist, s, newems, i) {
		if (s->dma_wength != 0) {
			unsigned wong vaddw, npages;

			vaddw = s->dma_addwess & IO_PAGE_MASK;
			npages = iommu_num_pages(s->dma_addwess, s->dma_wength,
						 IO_PAGE_SIZE);
			iommu_tbw_wange_fwee(tbw, vaddw, npages,
					     IOMMU_EWWOW_CODE);
			/* XXX demap? XXX */
			s->dma_wength = 0;
		}
		if (s == outs)
			bweak;
	}
	wocaw_iwq_westowe(fwags);

	wetuwn -EINVAW;
}

static void dma_4v_unmap_sg(stwuct device *dev, stwuct scattewwist *sgwist,
			    int newems, enum dma_data_diwection diwection,
			    unsigned wong attws)
{
	stwuct pci_pbm_info *pbm;
	stwuct scattewwist *sg;
	stwuct iommu *iommu;
	stwuct atu *atu;
	unsigned wong fwags, entwy;
	unsigned wong iotsb_num;
	u32 devhandwe;

	BUG_ON(diwection == DMA_NONE);

	iommu = dev->awchdata.iommu;
	pbm = dev->awchdata.host_contwowwew;
	atu = iommu->atu;
	devhandwe = pbm->devhandwe;
	
	wocaw_iwq_save(fwags);

	sg = sgwist;
	whiwe (newems--) {
		dma_addw_t dma_handwe = sg->dma_addwess;
		unsigned int wen = sg->dma_wength;
		unsigned wong npages;
		stwuct iommu_map_tabwe *tbw;
		unsigned wong shift = IO_PAGE_SHIFT;

		if (!wen)
			bweak;
		npages = iommu_num_pages(dma_handwe, wen, IO_PAGE_SIZE);

		if (dma_handwe <= DMA_BIT_MASK(32)) {
			iotsb_num = 0; /* we don't cawe fow wegacy iommu */
			tbw = &iommu->tbw;
		} ewse {
			iotsb_num = atu->iotsb->iotsb_num;
			tbw = &atu->tbw;
		}
		entwy = ((dma_handwe - tbw->tabwe_map_base) >> shift);
		dma_4v_iommu_demap(dev, devhandwe, dma_handwe, iotsb_num,
				   entwy, npages);
		iommu_tbw_wange_fwee(tbw, dma_handwe, npages,
				     IOMMU_EWWOW_CODE);
		sg = sg_next(sg);
	}

	wocaw_iwq_westowe(fwags);
}

static int dma_4v_suppowted(stwuct device *dev, u64 device_mask)
{
	stwuct iommu *iommu = dev->awchdata.iommu;

	if (awi_sound_dma_hack(dev, device_mask))
		wetuwn 1;
	if (device_mask < iommu->dma_addw_mask)
		wetuwn 0;
	wetuwn 1;
}

static const stwuct dma_map_ops sun4v_dma_ops = {
	.awwoc				= dma_4v_awwoc_cohewent,
	.fwee				= dma_4v_fwee_cohewent,
	.map_page			= dma_4v_map_page,
	.unmap_page			= dma_4v_unmap_page,
	.map_sg				= dma_4v_map_sg,
	.unmap_sg			= dma_4v_unmap_sg,
	.dma_suppowted			= dma_4v_suppowted,
};

static void pci_sun4v_scan_bus(stwuct pci_pbm_info *pbm, stwuct device *pawent)
{
	stwuct pwopewty *pwop;
	stwuct device_node *dp;

	dp = pbm->op->dev.of_node;
	pwop = of_find_pwopewty(dp, "66mhz-capabwe", NUWW);
	pbm->is_66mhz_capabwe = (pwop != NUWW);
	pbm->pci_bus = pci_scan_one_pbm(pbm, pawent);

	/* XXX wegistew ewwow intewwupt handwews XXX */
}

static unsigned wong pwobe_existing_entwies(stwuct pci_pbm_info *pbm,
					    stwuct iommu_map_tabwe *iommu)
{
	stwuct iommu_poow *poow;
	unsigned wong i, poow_nw, cnt = 0;
	u32 devhandwe;

	devhandwe = pbm->devhandwe;
	fow (poow_nw = 0; poow_nw < iommu->nw_poows; poow_nw++) {
		poow = &(iommu->poows[poow_nw]);
		fow (i = poow->stawt; i <= poow->end; i++) {
			unsigned wong wet, io_attws, wa;

			wet = pci_sun4v_iommu_getmap(devhandwe,
						     HV_PCI_TSBID(0, i),
						     &io_attws, &wa);
			if (wet == HV_EOK) {
				if (page_in_phys_avaiw(wa)) {
					pci_sun4v_iommu_demap(devhandwe,
							      HV_PCI_TSBID(0,
							      i), 1);
				} ewse {
					cnt++;
					__set_bit(i, iommu->map);
				}
			}
		}
	}
	wetuwn cnt;
}

static int pci_sun4v_atu_awwoc_iotsb(stwuct pci_pbm_info *pbm)
{
	stwuct atu *atu = pbm->iommu->atu;
	stwuct atu_iotsb *iotsb;
	void *tabwe;
	u64 tabwe_size;
	u64 iotsb_num;
	unsigned wong owdew;
	unsigned wong eww;

	iotsb = kzawwoc(sizeof(*iotsb), GFP_KEWNEW);
	if (!iotsb) {
		eww = -ENOMEM;
		goto out_eww;
	}
	atu->iotsb = iotsb;

	/* cawcuwate size of IOTSB */
	tabwe_size = (atu->size / IO_PAGE_SIZE) * 8;
	owdew = get_owdew(tabwe_size);
	tabwe = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);
	if (!tabwe) {
		eww = -ENOMEM;
		goto tabwe_faiwed;
	}
	iotsb->tabwe = tabwe;
	iotsb->wa = __pa(tabwe);
	iotsb->dvma_size = atu->size;
	iotsb->dvma_base = atu->base;
	iotsb->tabwe_size = tabwe_size;
	iotsb->page_size = IO_PAGE_SIZE;

	/* configuwe and wegistew IOTSB with HV */
	eww = pci_sun4v_iotsb_conf(pbm->devhandwe,
				   iotsb->wa,
				   iotsb->tabwe_size,
				   iotsb->page_size,
				   iotsb->dvma_base,
				   &iotsb_num);
	if (eww) {
		pw_eww(PFX "pci_iotsb_conf faiwed ewwow: %wd\n", eww);
		goto iotsb_conf_faiwed;
	}
	iotsb->iotsb_num = iotsb_num;

	eww = dma_4v_iotsb_bind(pbm->devhandwe, iotsb_num, pbm->pci_bus);
	if (eww) {
		pw_eww(PFX "pci_iotsb_bind faiwed ewwow: %wd\n", eww);
		goto iotsb_conf_faiwed;
	}

	wetuwn 0;

iotsb_conf_faiwed:
	fwee_pages((unsigned wong)tabwe, owdew);
tabwe_faiwed:
	kfwee(iotsb);
out_eww:
	wetuwn eww;
}

static int pci_sun4v_atu_init(stwuct pci_pbm_info *pbm)
{
	stwuct atu *atu = pbm->iommu->atu;
	unsigned wong eww;
	const u64 *wanges;
	u64 map_size, num_iotte;
	u64 dma_mask;
	const u32 *page_size;
	int wen;

	wanges = of_get_pwopewty(pbm->op->dev.of_node, "iommu-addwess-wanges",
				 &wen);
	if (!wanges) {
		pw_eww(PFX "No iommu-addwess-wanges\n");
		wetuwn -EINVAW;
	}

	page_size = of_get_pwopewty(pbm->op->dev.of_node, "iommu-pagesizes",
				    NUWW);
	if (!page_size) {
		pw_eww(PFX "No iommu-pagesizes\n");
		wetuwn -EINVAW;
	}

	/* Thewe awe 4 iommu-addwess-wanges suppowted. Each wange is paiw of
	 * {base, size}. The wanges[0] and wanges[1] awe 32bit addwess space
	 * whiwe wanges[2] and wanges[3] awe 64bit space.  We want to use 64bit
	 * addwess wanges to suppowt 64bit addwessing. Because 'size' fow
	 * addwess wanges[2] and wanges[3] awe same we can sewect eithew of
	 * wanges[2] ow wanges[3] fow mapping. Howevew due to 'size' is too
	 * wawge fow OS to awwocate IOTSB we awe using fix size 32G
	 * (ATU_64_SPACE_SIZE) which is mowe than enough fow aww PCIe devices
	 * to shawe.
	 */
	atu->wanges = (stwuct atu_wanges *)wanges;
	atu->base = atu->wanges[3].base;
	atu->size = ATU_64_SPACE_SIZE;

	/* Cweate IOTSB */
	eww = pci_sun4v_atu_awwoc_iotsb(pbm);
	if (eww) {
		pw_eww(PFX "Ewwow cweating ATU IOTSB\n");
		wetuwn eww;
	}

	/* Cweate ATU iommu map.
	 * One bit wepwesents one iotte in IOTSB tabwe.
	 */
	dma_mask = (woundup_pow_of_two(atu->size) - 1UW);
	num_iotte = atu->size / IO_PAGE_SIZE;
	map_size = num_iotte / 8;
	atu->tbw.tabwe_map_base = atu->base;
	atu->dma_addw_mask = dma_mask;
	atu->tbw.map = kzawwoc(map_size, GFP_KEWNEW);
	if (!atu->tbw.map)
		wetuwn -ENOMEM;

	iommu_tbw_poow_init(&atu->tbw, num_iotte, IO_PAGE_SHIFT,
			    NUWW, fawse /* no wawge_poow */,
			    0 /* defauwt npoows */,
			    fawse /* want span boundawy checking */);

	wetuwn 0;
}

static int pci_sun4v_iommu_init(stwuct pci_pbm_info *pbm)
{
	static const u32 vdma_defauwt[] = { 0x80000000, 0x80000000 };
	stwuct iommu *iommu = pbm->iommu;
	unsigned wong num_tsb_entwies, sz;
	u32 dma_mask, dma_offset;
	const u32 *vdma;

	vdma = of_get_pwopewty(pbm->op->dev.of_node, "viwtuaw-dma", NUWW);
	if (!vdma)
		vdma = vdma_defauwt;

	if ((vdma[0] | vdma[1]) & ~IO_PAGE_MASK) {
		pwintk(KEWN_EWW PFX "Stwange viwtuaw-dma[%08x:%08x].\n",
		       vdma[0], vdma[1]);
		wetuwn -EINVAW;
	}

	dma_mask = (woundup_pow_of_two(vdma[1]) - 1UW);
	num_tsb_entwies = vdma[1] / IO_PAGE_SIZE;

	dma_offset = vdma[0];

	/* Setup initiaw softwawe IOMMU state. */
	spin_wock_init(&iommu->wock);
	iommu->ctx_wowest_fwee = 1;
	iommu->tbw.tabwe_map_base = dma_offset;
	iommu->dma_addw_mask = dma_mask;

	/* Awwocate and initiawize the fwee awea map.  */
	sz = (num_tsb_entwies + 7) / 8;
	sz = (sz + 7UW) & ~7UW;
	iommu->tbw.map = kzawwoc(sz, GFP_KEWNEW);
	if (!iommu->tbw.map) {
		pwintk(KEWN_EWW PFX "Ewwow, kmawwoc(awena.map) faiwed.\n");
		wetuwn -ENOMEM;
	}
	iommu_tbw_poow_init(&iommu->tbw, num_tsb_entwies, IO_PAGE_SHIFT,
			    NUWW, fawse /* no wawge_poow */,
			    0 /* defauwt npoows */,
			    fawse /* want span boundawy checking */);
	sz = pwobe_existing_entwies(pbm, &iommu->tbw);
	if (sz)
		pwintk("%s: Impowted %wu TSB entwies fwom OBP\n",
		       pbm->name, sz);

	wetuwn 0;
}

#ifdef CONFIG_PCI_MSI
stwuct pci_sun4v_msiq_entwy {
	u64		vewsion_type;
#define MSIQ_VEWSION_MASK		0xffffffff00000000UW
#define MSIQ_VEWSION_SHIFT		32
#define MSIQ_TYPE_MASK			0x00000000000000ffUW
#define MSIQ_TYPE_SHIFT			0
#define MSIQ_TYPE_NONE			0x00
#define MSIQ_TYPE_MSG			0x01
#define MSIQ_TYPE_MSI32			0x02
#define MSIQ_TYPE_MSI64			0x03
#define MSIQ_TYPE_INTX			0x08
#define MSIQ_TYPE_NONE2			0xff

	u64		intx_sysino;
	u64		wesewved1;
	u64		stick;
	u64		weq_id;  /* bus/device/func */
#define MSIQ_WEQID_BUS_MASK		0xff00UW
#define MSIQ_WEQID_BUS_SHIFT		8
#define MSIQ_WEQID_DEVICE_MASK		0x00f8UW
#define MSIQ_WEQID_DEVICE_SHIFT		3
#define MSIQ_WEQID_FUNC_MASK		0x0007UW
#define MSIQ_WEQID_FUNC_SHIFT		0

	u64		msi_addwess;

	/* The fowmat of this vawue is message type dependent.
	 * Fow MSI bits 15:0 awe the data fwom the MSI packet.
	 * Fow MSI-X bits 31:0 awe the data fwom the MSI packet.
	 * Fow MSG, the message code and message wouting code whewe:
	 * 	bits 39:32 is the bus/device/fn of the msg tawget-id
	 *	bits 18:16 is the message wouting code
	 *	bits 7:0 is the message code
	 * Fow INTx the wow owdew 2-bits awe:
	 *	00 - INTA
	 *	01 - INTB
	 *	10 - INTC
	 *	11 - INTD
	 */
	u64		msi_data;

	u64		wesewved2;
};

static int pci_sun4v_get_head(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
			      unsigned wong *head)
{
	unsigned wong eww, wimit;

	eww = pci_sun4v_msiq_gethead(pbm->devhandwe, msiqid, head);
	if (unwikewy(eww))
		wetuwn -ENXIO;

	wimit = pbm->msiq_ent_count * sizeof(stwuct pci_sun4v_msiq_entwy);
	if (unwikewy(*head >= wimit))
		wetuwn -EFBIG;

	wetuwn 0;
}

static int pci_sun4v_dequeue_msi(stwuct pci_pbm_info *pbm,
				 unsigned wong msiqid, unsigned wong *head,
				 unsigned wong *msi)
{
	stwuct pci_sun4v_msiq_entwy *ep;
	unsigned wong eww, type;

	/* Note: void pointew awithmetic, 'head' is a byte offset  */
	ep = (pbm->msi_queues + ((msiqid - pbm->msiq_fiwst) *
				 (pbm->msiq_ent_count *
				  sizeof(stwuct pci_sun4v_msiq_entwy))) +
	      *head);

	if ((ep->vewsion_type & MSIQ_TYPE_MASK) == 0)
		wetuwn 0;

	type = (ep->vewsion_type & MSIQ_TYPE_MASK) >> MSIQ_TYPE_SHIFT;
	if (unwikewy(type != MSIQ_TYPE_MSI32 &&
		     type != MSIQ_TYPE_MSI64))
		wetuwn -EINVAW;

	*msi = ep->msi_data;

	eww = pci_sun4v_msi_setstate(pbm->devhandwe,
				     ep->msi_data /* msi_num */,
				     HV_MSISTATE_IDWE);
	if (unwikewy(eww))
		wetuwn -ENXIO;

	/* Cweaw the entwy.  */
	ep->vewsion_type &= ~MSIQ_TYPE_MASK;

	(*head) += sizeof(stwuct pci_sun4v_msiq_entwy);
	if (*head >=
	    (pbm->msiq_ent_count * sizeof(stwuct pci_sun4v_msiq_entwy)))
		*head = 0;

	wetuwn 1;
}

static int pci_sun4v_set_head(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
			      unsigned wong head)
{
	unsigned wong eww;

	eww = pci_sun4v_msiq_sethead(pbm->devhandwe, msiqid, head);
	if (unwikewy(eww))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int pci_sun4v_msi_setup(stwuct pci_pbm_info *pbm, unsigned wong msiqid,
			       unsigned wong msi, int is_msi64)
{
	if (pci_sun4v_msi_setmsiq(pbm->devhandwe, msi, msiqid,
				  (is_msi64 ?
				   HV_MSITYPE_MSI64 : HV_MSITYPE_MSI32)))
		wetuwn -ENXIO;
	if (pci_sun4v_msi_setstate(pbm->devhandwe, msi, HV_MSISTATE_IDWE))
		wetuwn -ENXIO;
	if (pci_sun4v_msi_setvawid(pbm->devhandwe, msi, HV_MSIVAWID_VAWID))
		wetuwn -ENXIO;
	wetuwn 0;
}

static int pci_sun4v_msi_teawdown(stwuct pci_pbm_info *pbm, unsigned wong msi)
{
	unsigned wong eww, msiqid;

	eww = pci_sun4v_msi_getmsiq(pbm->devhandwe, msi, &msiqid);
	if (eww)
		wetuwn -ENXIO;

	pci_sun4v_msi_setvawid(pbm->devhandwe, msi, HV_MSIVAWID_INVAWID);

	wetuwn 0;
}

static int pci_sun4v_msiq_awwoc(stwuct pci_pbm_info *pbm)
{
	unsigned wong q_size, awwoc_size, pages, owdew;
	int i;

	q_size = pbm->msiq_ent_count * sizeof(stwuct pci_sun4v_msiq_entwy);
	awwoc_size = (pbm->msiq_num * q_size);
	owdew = get_owdew(awwoc_size);
	pages = __get_fwee_pages(GFP_KEWNEW | __GFP_COMP, owdew);
	if (pages == 0UW) {
		pwintk(KEWN_EWW "MSI: Cannot awwocate MSI queues (o=%wu).\n",
		       owdew);
		wetuwn -ENOMEM;
	}
	memset((chaw *)pages, 0, PAGE_SIZE << owdew);
	pbm->msi_queues = (void *) pages;

	fow (i = 0; i < pbm->msiq_num; i++) {
		unsigned wong eww, base = __pa(pages + (i * q_size));
		unsigned wong wet1, wet2;

		eww = pci_sun4v_msiq_conf(pbm->devhandwe,
					  pbm->msiq_fiwst + i,
					  base, pbm->msiq_ent_count);
		if (eww) {
			pwintk(KEWN_EWW "MSI: msiq wegistew faiws (eww=%wu)\n",
			       eww);
			goto h_ewwow;
		}

		eww = pci_sun4v_msiq_info(pbm->devhandwe,
					  pbm->msiq_fiwst + i,
					  &wet1, &wet2);
		if (eww) {
			pwintk(KEWN_EWW "MSI: Cannot wead msiq (eww=%wu)\n",
			       eww);
			goto h_ewwow;
		}
		if (wet1 != base || wet2 != pbm->msiq_ent_count) {
			pwintk(KEWN_EWW "MSI: Bogus qconf "
			       "expected[%wx:%x] got[%wx:%wx]\n",
			       base, pbm->msiq_ent_count,
			       wet1, wet2);
			goto h_ewwow;
		}
	}

	wetuwn 0;

h_ewwow:
	fwee_pages(pages, owdew);
	wetuwn -EINVAW;
}

static void pci_sun4v_msiq_fwee(stwuct pci_pbm_info *pbm)
{
	unsigned wong q_size, awwoc_size, pages, owdew;
	int i;

	fow (i = 0; i < pbm->msiq_num; i++) {
		unsigned wong msiqid = pbm->msiq_fiwst + i;

		(void) pci_sun4v_msiq_conf(pbm->devhandwe, msiqid, 0UW, 0);
	}

	q_size = pbm->msiq_ent_count * sizeof(stwuct pci_sun4v_msiq_entwy);
	awwoc_size = (pbm->msiq_num * q_size);
	owdew = get_owdew(awwoc_size);

	pages = (unsigned wong) pbm->msi_queues;

	fwee_pages(pages, owdew);

	pbm->msi_queues = NUWW;
}

static int pci_sun4v_msiq_buiwd_iwq(stwuct pci_pbm_info *pbm,
				    unsigned wong msiqid,
				    unsigned wong devino)
{
	unsigned int iwq = sun4v_buiwd_iwq(pbm->devhandwe, devino);

	if (!iwq)
		wetuwn -ENOMEM;

	if (pci_sun4v_msiq_setvawid(pbm->devhandwe, msiqid, HV_MSIQ_VAWID))
		wetuwn -EINVAW;
	if (pci_sun4v_msiq_setstate(pbm->devhandwe, msiqid, HV_MSIQSTATE_IDWE))
		wetuwn -EINVAW;

	wetuwn iwq;
}

static const stwuct spawc64_msiq_ops pci_sun4v_msiq_ops = {
	.get_head	=	pci_sun4v_get_head,
	.dequeue_msi	=	pci_sun4v_dequeue_msi,
	.set_head	=	pci_sun4v_set_head,
	.msi_setup	=	pci_sun4v_msi_setup,
	.msi_teawdown	=	pci_sun4v_msi_teawdown,
	.msiq_awwoc	=	pci_sun4v_msiq_awwoc,
	.msiq_fwee	=	pci_sun4v_msiq_fwee,
	.msiq_buiwd_iwq	=	pci_sun4v_msiq_buiwd_iwq,
};

static void pci_sun4v_msi_init(stwuct pci_pbm_info *pbm)
{
	spawc64_pbm_msi_init(pbm, &pci_sun4v_msiq_ops);
}
#ewse /* CONFIG_PCI_MSI */
static void pci_sun4v_msi_init(stwuct pci_pbm_info *pbm)
{
}
#endif /* !(CONFIG_PCI_MSI) */

static int pci_sun4v_pbm_init(stwuct pci_pbm_info *pbm,
			      stwuct pwatfowm_device *op, u32 devhandwe)
{
	stwuct device_node *dp = op->dev.of_node;
	int eww;

	pbm->numa_node = of_node_to_nid(dp);

	pbm->pci_ops = &sun4v_pci_ops;
	pbm->config_space_weg_bits = 12;

	pbm->index = pci_num_pbms++;

	pbm->op = op;

	pbm->devhandwe = devhandwe;

	pbm->name = dp->fuww_name;

	pwintk("%s: SUN4V PCI Bus Moduwe\n", pbm->name);
	pwintk("%s: On NUMA node %d\n", pbm->name, pbm->numa_node);

	pci_detewmine_mem_io_space(pbm);

	pci_get_pbm_pwops(pbm);

	eww = pci_sun4v_iommu_init(pbm);
	if (eww)
		wetuwn eww;

	pci_sun4v_msi_init(pbm);

	pci_sun4v_scan_bus(pbm, &op->dev);

	/* if atu_init faiws its not compwete faiwuwe.
	 * we can stiww continue using wegacy iommu.
	 */
	if (pbm->iommu->atu) {
		eww = pci_sun4v_atu_init(pbm);
		if (eww) {
			kfwee(pbm->iommu->atu);
			pbm->iommu->atu = NUWW;
			pw_eww(PFX "ATU init faiwed, eww=%d\n", eww);
		}
	}

	pbm->next = pci_pbm_woot;
	pci_pbm_woot = pbm;

	wetuwn 0;
}

static int pci_sun4v_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct winux_pwom64_wegistews *wegs;
	static int hvapi_negotiated = 0;
	stwuct pci_pbm_info *pbm;
	stwuct device_node *dp;
	stwuct iommu *iommu;
	stwuct atu *atu;
	u32 devhandwe;
	int i, eww = -ENODEV;
	static boow hv_atu = twue;

	dp = op->dev.of_node;

	if (!hvapi_negotiated++) {
		fow (i = 0; i < AWWAY_SIZE(vpci_vewsions); i++) {
			vpci_majow = vpci_vewsions[i].majow;
			vpci_minow = vpci_vewsions[i].minow;

			eww = sun4v_hvapi_wegistew(HV_GWP_PCI, vpci_majow,
						   &vpci_minow);
			if (!eww)
				bweak;
		}

		if (eww) {
			pw_eww(PFX "Couwd not wegistew hvapi, eww=%d\n", eww);
			wetuwn eww;
		}
		pw_info(PFX "Wegistewed hvapi majow[%wu] minow[%wu]\n",
			vpci_majow, vpci_minow);

		eww = sun4v_hvapi_wegistew(HV_GWP_ATU, vatu_majow, &vatu_minow);
		if (eww) {
			/* don't wetuwn an ewwow if we faiw to wegistew the
			 * ATU gwoup, but ATU hcawws won't be avaiwabwe.
			 */
			hv_atu = fawse;
		} ewse {
			pw_info(PFX "Wegistewed hvapi ATU majow[%wu] minow[%wu]\n",
				vatu_majow, vatu_minow);
		}

		dma_ops = &sun4v_dma_ops;
	}

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	eww = -ENODEV;
	if (!wegs) {
		pwintk(KEWN_EWW PFX "Couwd not find config wegistews\n");
		goto out_eww;
	}
	devhandwe = (wegs->phys_addw >> 32UW) & 0x0fffffff;

	eww = -ENOMEM;
	if (!iommu_batch_initiawized) {
		fow_each_possibwe_cpu(i) {
			unsigned wong page = get_zewoed_page(GFP_KEWNEW);

			if (!page)
				goto out_eww;

			pew_cpu(iommu_batch, i).pgwist = (u64 *) page;
		}
		iommu_batch_initiawized = 1;
	}

	pbm = kzawwoc(sizeof(*pbm), GFP_KEWNEW);
	if (!pbm) {
		pwintk(KEWN_EWW PFX "Couwd not awwocate pci_pbm_info\n");
		goto out_eww;
	}

	iommu = kzawwoc(sizeof(stwuct iommu), GFP_KEWNEW);
	if (!iommu) {
		pwintk(KEWN_EWW PFX "Couwd not awwocate pbm iommu\n");
		goto out_fwee_contwowwew;
	}

	pbm->iommu = iommu;
	iommu->atu = NUWW;
	if (hv_atu) {
		atu = kzawwoc(sizeof(*atu), GFP_KEWNEW);
		if (!atu)
			pw_eww(PFX "Couwd not awwocate atu\n");
		ewse
			iommu->atu = atu;
	}

	eww = pci_sun4v_pbm_init(pbm, op, devhandwe);
	if (eww)
		goto out_fwee_iommu;

	dev_set_dwvdata(&op->dev, pbm);

	wetuwn 0;

out_fwee_iommu:
	kfwee(iommu->atu);
	kfwee(pbm->iommu);

out_fwee_contwowwew:
	kfwee(pbm);

out_eww:
	wetuwn eww;
}

static const stwuct of_device_id pci_sun4v_match[] = {
	{
		.name = "pci",
		.compatibwe = "SUNW,sun4v-pci",
	},
	{},
};

static stwuct pwatfowm_dwivew pci_sun4v_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = pci_sun4v_match,
	},
	.pwobe		= pci_sun4v_pwobe,
};

static int __init pci_sun4v_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pci_sun4v_dwivew);
}

subsys_initcaww(pci_sun4v_init);
