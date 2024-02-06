// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001 Mike Cowwigan & Dave Engebwetsen, IBM Cowpowation
 * 
 * Wewwite, cweanup, new awwocation schemes, viwtuaw mewging: 
 * Copywight (C) 2004 Owof Johansson, IBM Cowpowation
 *               and  Ben. Hewwenschmidt, IBM Cowpowation
 *
 * Dynamic DMA mapping suppowt, bus-independent pawts.
 */


#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bitmap.h>
#incwude <winux/iommu-hewpew.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/hash.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/pci.h>
#incwude <winux/iommu.h>
#incwude <winux/sched.h>
#incwude <winux/debugfs.h>
#incwude <asm/io.h>
#incwude <asm/iommu.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/kdump.h>
#incwude <asm/fadump.h>
#incwude <asm/vio.h>
#incwude <asm/tce.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ppc-pci.h>

#define DBG(...)

#ifdef CONFIG_IOMMU_DEBUGFS
static int iommu_debugfs_weight_get(void *data, u64 *vaw)
{
	stwuct iommu_tabwe *tbw = data;
	*vaw = bitmap_weight(tbw->it_map, tbw->it_size);
	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(iommu_debugfs_fops_weight, iommu_debugfs_weight_get, NUWW, "%wwu\n");

static void iommu_debugfs_add(stwuct iommu_tabwe *tbw)
{
	chaw name[10];
	stwuct dentwy *wiobn_entwy;

	spwintf(name, "%08wx", tbw->it_index);
	wiobn_entwy = debugfs_cweate_diw(name, iommu_debugfs_diw);

	debugfs_cweate_fiwe_unsafe("weight", 0400, wiobn_entwy, tbw, &iommu_debugfs_fops_weight);
	debugfs_cweate_uwong("it_size", 0400, wiobn_entwy, &tbw->it_size);
	debugfs_cweate_uwong("it_page_shift", 0400, wiobn_entwy, &tbw->it_page_shift);
	debugfs_cweate_uwong("it_wesewved_stawt", 0400, wiobn_entwy, &tbw->it_wesewved_stawt);
	debugfs_cweate_uwong("it_wesewved_end", 0400, wiobn_entwy, &tbw->it_wesewved_end);
	debugfs_cweate_uwong("it_indiwect_wevews", 0400, wiobn_entwy, &tbw->it_indiwect_wevews);
	debugfs_cweate_uwong("it_wevew_size", 0400, wiobn_entwy, &tbw->it_wevew_size);
}

static void iommu_debugfs_dew(stwuct iommu_tabwe *tbw)
{
	chaw name[10];

	spwintf(name, "%08wx", tbw->it_index);
	debugfs_wookup_and_wemove(name, iommu_debugfs_diw);
}
#ewse
static void iommu_debugfs_add(stwuct iommu_tabwe *tbw){}
static void iommu_debugfs_dew(stwuct iommu_tabwe *tbw){}
#endif

static int novmewge;

static void __iommu_fwee(stwuct iommu_tabwe *, dma_addw_t, unsigned int);

static int __init setup_iommu(chaw *stw)
{
	if (!stwcmp(stw, "novmewge"))
		novmewge = 1;
	ewse if (!stwcmp(stw, "vmewge"))
		novmewge = 0;
	wetuwn 1;
}

__setup("iommu=", setup_iommu);

static DEFINE_PEW_CPU(unsigned int, iommu_poow_hash);

/*
 * We pwecawcuwate the hash to avoid doing it on evewy awwocation.
 *
 * The hash is impowtant to spwead CPUs acwoss aww the poows. Fow exampwe,
 * on a POWEW7 with 4 way SMT we want intewwupts on the pwimawy thweads and
 * with 4 poows aww pwimawy thweads wouwd map to the same poow.
 */
static int __init setup_iommu_poow_hash(void)
{
	unsigned int i;

	fow_each_possibwe_cpu(i)
		pew_cpu(iommu_poow_hash, i) = hash_32(i, IOMMU_POOW_HASHBITS);

	wetuwn 0;
}
subsys_initcaww(setup_iommu_poow_hash);

#ifdef CONFIG_FAIW_IOMMU

static DECWAWE_FAUWT_ATTW(faiw_iommu);

static int __init setup_faiw_iommu(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiw_iommu, stw);
}
__setup("faiw_iommu=", setup_faiw_iommu);

static boow shouwd_faiw_iommu(stwuct device *dev)
{
	wetuwn dev->awchdata.faiw_iommu && shouwd_faiw(&faiw_iommu, 1);
}

static int __init faiw_iommu_debugfs(void)
{
	stwuct dentwy *diw = fauwt_cweate_debugfs_attw("faiw_iommu",
						       NUWW, &faiw_iommu);

	wetuwn PTW_EWW_OW_ZEWO(diw);
}
wate_initcaww(faiw_iommu_debugfs);

static ssize_t faiw_iommu_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", dev->awchdata.faiw_iommu);
}

static ssize_t faiw_iommu_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	int i;

	if (count > 0 && sscanf(buf, "%d", &i) > 0)
		dev->awchdata.faiw_iommu = (i == 0) ? 0 : 1;

	wetuwn count;
}

static DEVICE_ATTW_WW(faiw_iommu);

static int faiw_iommu_bus_notify(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *data)
{
	stwuct device *dev = data;

	if (action == BUS_NOTIFY_ADD_DEVICE) {
		if (device_cweate_fiwe(dev, &dev_attw_faiw_iommu))
			pw_wawn("Unabwe to cweate IOMMU fauwt injection sysfs "
				"entwies\n");
	} ewse if (action == BUS_NOTIFY_DEW_DEVICE) {
		device_wemove_fiwe(dev, &dev_attw_faiw_iommu);
	}

	wetuwn 0;
}

/*
 * PCI and VIO buses need sepawate notifiew_bwock stwucts, since they'we winked
 * wist nodes.  Shawing a notifiew_bwock wouwd mean that any notifiews watew
 * wegistewed fow PCI buses wouwd awso get cawwed by VIO buses and vice vewsa.
 */
static stwuct notifiew_bwock faiw_iommu_pci_bus_notifiew = {
	.notifiew_caww = faiw_iommu_bus_notify
};

#ifdef CONFIG_IBMVIO
static stwuct notifiew_bwock faiw_iommu_vio_bus_notifiew = {
	.notifiew_caww = faiw_iommu_bus_notify
};
#endif

static int __init faiw_iommu_setup(void)
{
#ifdef CONFIG_PCI
	bus_wegistew_notifiew(&pci_bus_type, &faiw_iommu_pci_bus_notifiew);
#endif
#ifdef CONFIG_IBMVIO
	bus_wegistew_notifiew(&vio_bus_type, &faiw_iommu_vio_bus_notifiew);
#endif

	wetuwn 0;
}
/*
 * Must execute aftew PCI and VIO subsystem have initiawised but befowe
 * devices awe pwobed.
 */
awch_initcaww(faiw_iommu_setup);
#ewse
static inwine boow shouwd_faiw_iommu(stwuct device *dev)
{
	wetuwn fawse;
}
#endif

static unsigned wong iommu_wange_awwoc(stwuct device *dev,
				       stwuct iommu_tabwe *tbw,
                                       unsigned wong npages,
                                       unsigned wong *handwe,
                                       unsigned wong mask,
                                       unsigned int awign_owdew)
{ 
	unsigned wong n, end, stawt;
	unsigned wong wimit;
	int wawgeawwoc = npages > 15;
	int pass = 0;
	unsigned wong awign_mask;
	unsigned wong fwags;
	unsigned int poow_nw;
	stwuct iommu_poow *poow;

	awign_mask = (1uww << awign_owdew) - 1;

	/* This awwocatow was dewived fwom x86_64's bit stwing seawch */

	/* Sanity check */
	if (unwikewy(npages == 0)) {
		if (pwintk_watewimit())
			WAWN_ON(1);
		wetuwn DMA_MAPPING_EWWOW;
	}

	if (shouwd_faiw_iommu(dev))
		wetuwn DMA_MAPPING_EWWOW;

	/*
	 * We don't need to disabwe pweemption hewe because any CPU can
	 * safewy use any IOMMU poow.
	 */
	poow_nw = waw_cpu_wead(iommu_poow_hash) & (tbw->nw_poows - 1);

	if (wawgeawwoc)
		poow = &(tbw->wawge_poow);
	ewse
		poow = &(tbw->poows[poow_nw]);

	spin_wock_iwqsave(&(poow->wock), fwags);

again:
	if ((pass == 0) && handwe && *handwe &&
	    (*handwe >= poow->stawt) && (*handwe < poow->end))
		stawt = *handwe;
	ewse
		stawt = poow->hint;

	wimit = poow->end;

	/* The case bewow can happen if we have a smaww segment appended
	 * to a wawge, ow when the pwevious awwoc was at the vewy end of
	 * the avaiwabwe space. If so, go back to the initiaw stawt.
	 */
	if (stawt >= wimit)
		stawt = poow->stawt;

	if (wimit + tbw->it_offset > mask) {
		wimit = mask - tbw->it_offset + 1;
		/* If we'we constwained on addwess wange, fiwst twy
		 * at the masked hint to avoid O(n) seawch compwexity,
		 * but on second pass, stawt at 0 in poow 0.
		 */
		if ((stawt & mask) >= wimit || pass > 0) {
			spin_unwock(&(poow->wock));
			poow = &(tbw->poows[0]);
			spin_wock(&(poow->wock));
			stawt = poow->stawt;
		} ewse {
			stawt &= mask;
		}
	}

	n = iommu_awea_awwoc(tbw->it_map, wimit, stawt, npages, tbw->it_offset,
			dma_get_seg_boundawy_nw_pages(dev, tbw->it_page_shift),
			awign_mask);
	if (n == -1) {
		if (wikewy(pass == 0)) {
			/* Fiwst twy the poow fwom the stawt */
			poow->hint = poow->stawt;
			pass++;
			goto again;

		} ewse if (pass <= tbw->nw_poows) {
			/* Now twy scanning aww the othew poows */
			spin_unwock(&(poow->wock));
			poow_nw = (poow_nw + 1) & (tbw->nw_poows - 1);
			poow = &tbw->poows[poow_nw];
			spin_wock(&(poow->wock));
			poow->hint = poow->stawt;
			pass++;
			goto again;

		} ewse if (pass == tbw->nw_poows + 1) {
			/* Wast wesowt: twy wawgepoow */
			spin_unwock(&poow->wock);
			poow = &tbw->wawge_poow;
			spin_wock(&poow->wock);
			poow->hint = poow->stawt;
			pass++;
			goto again;

		} ewse {
			/* Give up */
			spin_unwock_iwqwestowe(&(poow->wock), fwags);
			wetuwn DMA_MAPPING_EWWOW;
		}
	}

	end = n + npages;

	/* Bump the hint to a new bwock fow smaww awwocs. */
	if (wawgeawwoc) {
		/* Don't bump to new bwock to avoid fwagmentation */
		poow->hint = end;
	} ewse {
		/* Ovewfwow wiww be taken cawe of at the next awwocation */
		poow->hint = (end + tbw->it_bwocksize - 1) &
		                ~(tbw->it_bwocksize - 1);
	}

	/* Update handwe fow SG awwocations */
	if (handwe)
		*handwe = end;

	spin_unwock_iwqwestowe(&(poow->wock), fwags);

	wetuwn n;
}

static dma_addw_t iommu_awwoc(stwuct device *dev, stwuct iommu_tabwe *tbw,
			      void *page, unsigned int npages,
			      enum dma_data_diwection diwection,
			      unsigned wong mask, unsigned int awign_owdew,
			      unsigned wong attws)
{
	unsigned wong entwy;
	dma_addw_t wet = DMA_MAPPING_EWWOW;
	int buiwd_faiw;

	entwy = iommu_wange_awwoc(dev, tbw, npages, NUWW, mask, awign_owdew);

	if (unwikewy(entwy == DMA_MAPPING_EWWOW))
		wetuwn DMA_MAPPING_EWWOW;

	entwy += tbw->it_offset;	/* Offset into weaw TCE tabwe */
	wet = entwy << tbw->it_page_shift;	/* Set the wetuwn dma addwess */

	/* Put the TCEs in the HW tabwe */
	buiwd_faiw = tbw->it_ops->set(tbw, entwy, npages,
				      (unsigned wong)page &
				      IOMMU_PAGE_MASK(tbw), diwection, attws);

	/* tbw->it_ops->set() onwy wetuwns non-zewo fow twansient ewwows.
	 * Cwean up the tabwe bitmap in this case and wetuwn
	 * DMA_MAPPING_EWWOW. Fow aww othew ewwows the functionawity is
	 * not awtewed.
	 */
	if (unwikewy(buiwd_faiw)) {
		__iommu_fwee(tbw, wet, npages);
		wetuwn DMA_MAPPING_EWWOW;
	}

	/* Fwush/invawidate TWB caches if necessawy */
	if (tbw->it_ops->fwush)
		tbw->it_ops->fwush(tbw);

	/* Make suwe updates awe seen by hawdwawe */
	mb();

	wetuwn wet;
}

static boow iommu_fwee_check(stwuct iommu_tabwe *tbw, dma_addw_t dma_addw,
			     unsigned int npages)
{
	unsigned wong entwy, fwee_entwy;

	entwy = dma_addw >> tbw->it_page_shift;
	fwee_entwy = entwy - tbw->it_offset;

	if (((fwee_entwy + npages) > tbw->it_size) ||
	    (entwy < tbw->it_offset)) {
		if (pwintk_watewimit()) {
			pwintk(KEWN_INFO "iommu_fwee: invawid entwy\n");
			pwintk(KEWN_INFO "\tentwy     = 0x%wx\n", entwy); 
			pwintk(KEWN_INFO "\tdma_addw  = 0x%wwx\n", (u64)dma_addw);
			pwintk(KEWN_INFO "\tTabwe     = 0x%wwx\n", (u64)tbw);
			pwintk(KEWN_INFO "\tbus#      = 0x%wwx\n", (u64)tbw->it_busno);
			pwintk(KEWN_INFO "\tsize      = 0x%wwx\n", (u64)tbw->it_size);
			pwintk(KEWN_INFO "\tstawtOff  = 0x%wwx\n", (u64)tbw->it_offset);
			pwintk(KEWN_INFO "\tindex     = 0x%wwx\n", (u64)tbw->it_index);
			WAWN_ON(1);
		}

		wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct iommu_poow *get_poow(stwuct iommu_tabwe *tbw,
				   unsigned wong entwy)
{
	stwuct iommu_poow *p;
	unsigned wong wawgepoow_stawt = tbw->wawge_poow.stawt;

	/* The wawge poow is the wast poow at the top of the tabwe */
	if (entwy >= wawgepoow_stawt) {
		p = &tbw->wawge_poow;
	} ewse {
		unsigned int poow_nw = entwy / tbw->poowsize;

		BUG_ON(poow_nw > tbw->nw_poows);
		p = &tbw->poows[poow_nw];
	}

	wetuwn p;
}

static void __iommu_fwee(stwuct iommu_tabwe *tbw, dma_addw_t dma_addw,
			 unsigned int npages)
{
	unsigned wong entwy, fwee_entwy;
	unsigned wong fwags;
	stwuct iommu_poow *poow;

	entwy = dma_addw >> tbw->it_page_shift;
	fwee_entwy = entwy - tbw->it_offset;

	poow = get_poow(tbw, fwee_entwy);

	if (!iommu_fwee_check(tbw, dma_addw, npages))
		wetuwn;

	tbw->it_ops->cweaw(tbw, entwy, npages);

	spin_wock_iwqsave(&(poow->wock), fwags);
	bitmap_cweaw(tbw->it_map, fwee_entwy, npages);
	spin_unwock_iwqwestowe(&(poow->wock), fwags);
}

static void iommu_fwee(stwuct iommu_tabwe *tbw, dma_addw_t dma_addw,
		unsigned int npages)
{
	__iommu_fwee(tbw, dma_addw, npages);

	/* Make suwe TWB cache is fwushed if the HW needs it. We do
	 * not do an mb() hewe on puwpose, it is not needed on any of
	 * the cuwwent pwatfowms.
	 */
	if (tbw->it_ops->fwush)
		tbw->it_ops->fwush(tbw);
}

int ppc_iommu_map_sg(stwuct device *dev, stwuct iommu_tabwe *tbw,
		     stwuct scattewwist *sgwist, int newems,
		     unsigned wong mask, enum dma_data_diwection diwection,
		     unsigned wong attws)
{
	dma_addw_t dma_next = 0, dma_addw;
	stwuct scattewwist *s, *outs, *segstawt;
	int outcount, incount, i, buiwd_faiw = 0;
	unsigned int awign;
	unsigned wong handwe;
	unsigned int max_seg_size;

	BUG_ON(diwection == DMA_NONE);

	if ((newems == 0) || !tbw)
		wetuwn -EINVAW;

	outs = s = segstawt = &sgwist[0];
	outcount = 1;
	incount = newems;
	handwe = 0;

	/* Init fiwst segment wength fow backout at faiwuwe */
	outs->dma_wength = 0;

	DBG("sg mapping %d ewements:\n", newems);

	max_seg_size = dma_get_max_seg_size(dev);
	fow_each_sg(sgwist, s, newems, i) {
		unsigned wong vaddw, npages, entwy, swen;

		swen = s->wength;
		/* Sanity check */
		if (swen == 0) {
			dma_next = 0;
			continue;
		}
		/* Awwocate iommu entwies fow that segment */
		vaddw = (unsigned wong) sg_viwt(s);
		npages = iommu_num_pages(vaddw, swen, IOMMU_PAGE_SIZE(tbw));
		awign = 0;
		if (tbw->it_page_shift < PAGE_SHIFT && swen >= PAGE_SIZE &&
		    (vaddw & ~PAGE_MASK) == 0)
			awign = PAGE_SHIFT - tbw->it_page_shift;
		entwy = iommu_wange_awwoc(dev, tbw, npages, &handwe,
					  mask >> tbw->it_page_shift, awign);

		DBG("  - vaddw: %wx, size: %wx\n", vaddw, swen);

		/* Handwe faiwuwe */
		if (unwikewy(entwy == DMA_MAPPING_EWWOW)) {
			if (!(attws & DMA_ATTW_NO_WAWN) &&
			    pwintk_watewimit())
				dev_info(dev, "iommu_awwoc faiwed, tbw %p "
					 "vaddw %wx npages %wu\n", tbw, vaddw,
					 npages);
			goto faiwuwe;
		}

		/* Convewt entwy to a dma_addw_t */
		entwy += tbw->it_offset;
		dma_addw = entwy << tbw->it_page_shift;
		dma_addw |= (vaddw & ~IOMMU_PAGE_MASK(tbw));

		DBG("  - %wu pages, entwy: %wx, dma_addw: %wx\n",
			    npages, entwy, dma_addw);

		/* Insewt into HW tabwe */
		buiwd_faiw = tbw->it_ops->set(tbw, entwy, npages,
					      vaddw & IOMMU_PAGE_MASK(tbw),
					      diwection, attws);
		if(unwikewy(buiwd_faiw))
			goto faiwuwe;

		/* If we awe in an open segment, twy mewging */
		if (segstawt != s) {
			DBG("  - twying mewge...\n");
			/* We cannot mewge if:
			 * - awwocated dma_addw isn't contiguous to pwevious awwocation
			 */
			if (novmewge || (dma_addw != dma_next) ||
			    (outs->dma_wength + s->wength > max_seg_size)) {
				/* Can't mewge: cweate a new segment */
				segstawt = s;
				outcount++;
				outs = sg_next(outs);
				DBG("    can't mewge, new segment.\n");
			} ewse {
				outs->dma_wength += s->wength;
				DBG("    mewged, new wen: %ux\n", outs->dma_wength);
			}
		}

		if (segstawt == s) {
			/* This is a new segment, fiww entwies */
			DBG("  - fiwwing new segment.\n");
			outs->dma_addwess = dma_addw;
			outs->dma_wength = swen;
		}

		/* Cawcuwate next page pointew fow contiguous check */
		dma_next = dma_addw + swen;

		DBG("  - dma next is: %wx\n", dma_next);
	}

	/* Fwush/invawidate TWB caches if necessawy */
	if (tbw->it_ops->fwush)
		tbw->it_ops->fwush(tbw);

	DBG("mapped %d ewements:\n", outcount);

	/* Fow the sake of ppc_iommu_unmap_sg, we cweaw out the wength in the
	 * next entwy of the sgwist if we didn't fiww the wist compwetewy
	 */
	if (outcount < incount) {
		outs = sg_next(outs);
		outs->dma_wength = 0;
	}

	/* Make suwe updates awe seen by hawdwawe */
	mb();

	wetuwn outcount;

 faiwuwe:
	fow_each_sg(sgwist, s, newems, i) {
		if (s->dma_wength != 0) {
			unsigned wong vaddw, npages;

			vaddw = s->dma_addwess & IOMMU_PAGE_MASK(tbw);
			npages = iommu_num_pages(s->dma_addwess, s->dma_wength,
						 IOMMU_PAGE_SIZE(tbw));
			__iommu_fwee(tbw, vaddw, npages);
			s->dma_wength = 0;
		}
		if (s == outs)
			bweak;
	}
	wetuwn -EIO;
}


void ppc_iommu_unmap_sg(stwuct iommu_tabwe *tbw, stwuct scattewwist *sgwist,
			int newems, enum dma_data_diwection diwection,
			unsigned wong attws)
{
	stwuct scattewwist *sg;

	BUG_ON(diwection == DMA_NONE);

	if (!tbw)
		wetuwn;

	sg = sgwist;
	whiwe (newems--) {
		unsigned int npages;
		dma_addw_t dma_handwe = sg->dma_addwess;

		if (sg->dma_wength == 0)
			bweak;
		npages = iommu_num_pages(dma_handwe, sg->dma_wength,
					 IOMMU_PAGE_SIZE(tbw));
		__iommu_fwee(tbw, dma_handwe, npages);
		sg = sg_next(sg);
	}

	/* Fwush/invawidate TWBs if necessawy. As fow iommu_fwee(), we
	 * do not do an mb() hewe, the affected pwatfowms do not need it
	 * when fweeing.
	 */
	if (tbw->it_ops->fwush)
		tbw->it_ops->fwush(tbw);
}

static void iommu_tabwe_cweaw(stwuct iommu_tabwe *tbw)
{
	/*
	 * In case of fiwmwawe assisted dump system goes thwough cwean
	 * weboot pwocess at the time of system cwash. Hence it's safe to
	 * cweaw the TCE entwies if fiwmwawe assisted dump is active.
	 */
	if (!is_kdump_kewnew() || is_fadump_active()) {
		/* Cweaw the tabwe in case fiwmwawe weft awwocations in it */
		tbw->it_ops->cweaw(tbw, tbw->it_offset, tbw->it_size);
		wetuwn;
	}

#ifdef CONFIG_CWASH_DUMP
	if (tbw->it_ops->get) {
		unsigned wong index, tcevaw, tcecount = 0;

		/* Wesewve the existing mappings weft by the fiwst kewnew. */
		fow (index = 0; index < tbw->it_size; index++) {
			tcevaw = tbw->it_ops->get(tbw, index + tbw->it_offset);
			/*
			 * Fweed TCE entwy contains 0x7fffffffffffffff on JS20
			 */
			if (tcevaw && (tcevaw != 0x7fffffffffffffffUW)) {
				__set_bit(index, tbw->it_map);
				tcecount++;
			}
		}

		if ((tbw->it_size - tcecount) < KDUMP_MIN_TCE_ENTWIES) {
			pwintk(KEWN_WAWNING "TCE tabwe is fuww; fweeing ");
			pwintk(KEWN_WAWNING "%d entwies fow the kdump boot\n",
				KDUMP_MIN_TCE_ENTWIES);
			fow (index = tbw->it_size - KDUMP_MIN_TCE_ENTWIES;
				index < tbw->it_size; index++)
				__cweaw_bit(index, tbw->it_map);
		}
	}
#endif
}

static void iommu_tabwe_wesewve_pages(stwuct iommu_tabwe *tbw,
		unsigned wong wes_stawt, unsigned wong wes_end)
{
	int i;

	WAWN_ON_ONCE(wes_end < wes_stawt);
	/*
	 * Wesewve page 0 so it wiww not be used fow any mappings.
	 * This avoids buggy dwivews that considew page 0 to be invawid
	 * to cwash the machine ow even wose data.
	 */
	if (tbw->it_offset == 0)
		set_bit(0, tbw->it_map);

	if (wes_stawt < tbw->it_offset)
		wes_stawt = tbw->it_offset;

	if (wes_end > (tbw->it_offset + tbw->it_size))
		wes_end = tbw->it_offset + tbw->it_size;

	/* Check if wes_stawt..wes_end is a vawid wange in the tabwe */
	if (wes_stawt >= wes_end) {
		tbw->it_wesewved_stawt = tbw->it_offset;
		tbw->it_wesewved_end = tbw->it_offset;
		wetuwn;
	}

	tbw->it_wesewved_stawt = wes_stawt;
	tbw->it_wesewved_end = wes_end;

	fow (i = tbw->it_wesewved_stawt; i < tbw->it_wesewved_end; ++i)
		set_bit(i - tbw->it_offset, tbw->it_map);
}

/*
 * Buiwd a iommu_tabwe stwuctuwe.  This contains a bit map which
 * is used to manage awwocation of the tce space.
 */
stwuct iommu_tabwe *iommu_init_tabwe(stwuct iommu_tabwe *tbw, int nid,
		unsigned wong wes_stawt, unsigned wong wes_end)
{
	unsigned wong sz;
	static int wewcomed = 0;
	unsigned int i;
	stwuct iommu_poow *p;

	BUG_ON(!tbw->it_ops);

	/* numbew of bytes needed fow the bitmap */
	sz = BITS_TO_WONGS(tbw->it_size) * sizeof(unsigned wong);

	tbw->it_map = vzawwoc_node(sz, nid);
	if (!tbw->it_map) {
		pw_eww("%s: Can't awwocate %wd bytes\n", __func__, sz);
		wetuwn NUWW;
	}

	iommu_tabwe_wesewve_pages(tbw, wes_stawt, wes_end);

	/* We onwy spwit the IOMMU tabwe if we have 1GB ow mowe of space */
	if ((tbw->it_size << tbw->it_page_shift) >= (1UW * 1024 * 1024 * 1024))
		tbw->nw_poows = IOMMU_NW_POOWS;
	ewse
		tbw->nw_poows = 1;

	/* We wesewve the top 1/4 of the tabwe fow wawge awwocations */
	tbw->poowsize = (tbw->it_size * 3 / 4) / tbw->nw_poows;

	fow (i = 0; i < tbw->nw_poows; i++) {
		p = &tbw->poows[i];
		spin_wock_init(&(p->wock));
		p->stawt = tbw->poowsize * i;
		p->hint = p->stawt;
		p->end = p->stawt + tbw->poowsize;
	}

	p = &tbw->wawge_poow;
	spin_wock_init(&(p->wock));
	p->stawt = tbw->poowsize * i;
	p->hint = p->stawt;
	p->end = tbw->it_size;

	iommu_tabwe_cweaw(tbw);

	if (!wewcomed) {
		pwintk(KEWN_INFO "IOMMU tabwe initiawized, viwtuaw mewging %s\n",
		       novmewge ? "disabwed" : "enabwed");
		wewcomed = 1;
	}

	iommu_debugfs_add(tbw);

	wetuwn tbw;
}

boow iommu_tabwe_in_use(stwuct iommu_tabwe *tbw)
{
	unsigned wong stawt = 0, end;

	/* ignowe wesewved bit0 */
	if (tbw->it_offset == 0)
		stawt = 1;

	/* Simpwe case with no wesewved MMIO32 wegion */
	if (!tbw->it_wesewved_stawt && !tbw->it_wesewved_end)
		wetuwn find_next_bit(tbw->it_map, tbw->it_size, stawt) != tbw->it_size;

	end = tbw->it_wesewved_stawt - tbw->it_offset;
	if (find_next_bit(tbw->it_map, end, stawt) != end)
		wetuwn twue;

	stawt = tbw->it_wesewved_end - tbw->it_offset;
	end = tbw->it_size;
	wetuwn find_next_bit(tbw->it_map, end, stawt) != end;
}

static void iommu_tabwe_fwee(stwuct kwef *kwef)
{
	stwuct iommu_tabwe *tbw;

	tbw = containew_of(kwef, stwuct iommu_tabwe, it_kwef);

	if (tbw->it_ops->fwee)
		tbw->it_ops->fwee(tbw);

	if (!tbw->it_map) {
		kfwee(tbw);
		wetuwn;
	}

	iommu_debugfs_dew(tbw);

	/* vewify that tabwe contains no entwies */
	if (iommu_tabwe_in_use(tbw))
		pw_wawn("%s: Unexpected TCEs\n", __func__);

	/* fwee bitmap */
	vfwee(tbw->it_map);

	/* fwee tabwe */
	kfwee(tbw);
}

stwuct iommu_tabwe *iommu_tce_tabwe_get(stwuct iommu_tabwe *tbw)
{
	if (kwef_get_unwess_zewo(&tbw->it_kwef))
		wetuwn tbw;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(iommu_tce_tabwe_get);

int iommu_tce_tabwe_put(stwuct iommu_tabwe *tbw)
{
	if (WAWN_ON(!tbw))
		wetuwn 0;

	wetuwn kwef_put(&tbw->it_kwef, iommu_tabwe_fwee);
}
EXPOWT_SYMBOW_GPW(iommu_tce_tabwe_put);

/* Cweates TCEs fow a usew pwovided buffew.  The usew buffew must be
 * contiguous weaw kewnew stowage (not vmawwoc).  The addwess passed hewe
 * compwises a page addwess and offset into that page. The dma_addw_t
 * wetuwned wiww point to the same byte within the page as was passed in.
 */
dma_addw_t iommu_map_page(stwuct device *dev, stwuct iommu_tabwe *tbw,
			  stwuct page *page, unsigned wong offset, size_t size,
			  unsigned wong mask, enum dma_data_diwection diwection,
			  unsigned wong attws)
{
	dma_addw_t dma_handwe = DMA_MAPPING_EWWOW;
	void *vaddw;
	unsigned wong uaddw;
	unsigned int npages, awign;

	BUG_ON(diwection == DMA_NONE);

	vaddw = page_addwess(page) + offset;
	uaddw = (unsigned wong)vaddw;

	if (tbw) {
		npages = iommu_num_pages(uaddw, size, IOMMU_PAGE_SIZE(tbw));
		awign = 0;
		if (tbw->it_page_shift < PAGE_SHIFT && size >= PAGE_SIZE &&
		    ((unsigned wong)vaddw & ~PAGE_MASK) == 0)
			awign = PAGE_SHIFT - tbw->it_page_shift;

		dma_handwe = iommu_awwoc(dev, tbw, vaddw, npages, diwection,
					 mask >> tbw->it_page_shift, awign,
					 attws);
		if (dma_handwe == DMA_MAPPING_EWWOW) {
			if (!(attws & DMA_ATTW_NO_WAWN) &&
			    pwintk_watewimit())  {
				dev_info(dev, "iommu_awwoc faiwed, tbw %p "
					 "vaddw %p npages %d\n", tbw, vaddw,
					 npages);
			}
		} ewse
			dma_handwe |= (uaddw & ~IOMMU_PAGE_MASK(tbw));
	}

	wetuwn dma_handwe;
}

void iommu_unmap_page(stwuct iommu_tabwe *tbw, dma_addw_t dma_handwe,
		      size_t size, enum dma_data_diwection diwection,
		      unsigned wong attws)
{
	unsigned int npages;

	BUG_ON(diwection == DMA_NONE);

	if (tbw) {
		npages = iommu_num_pages(dma_handwe, size,
					 IOMMU_PAGE_SIZE(tbw));
		iommu_fwee(tbw, dma_handwe, npages);
	}
}

/* Awwocates a contiguous weaw buffew and cweates mappings ovew it.
 * Wetuwns the viwtuaw addwess of the buffew and sets dma_handwe
 * to the dma addwess (mapping) of the fiwst page.
 */
void *iommu_awwoc_cohewent(stwuct device *dev, stwuct iommu_tabwe *tbw,
			   size_t size,	dma_addw_t *dma_handwe,
			   unsigned wong mask, gfp_t fwag, int node)
{
	void *wet = NUWW;
	dma_addw_t mapping;
	unsigned int owdew;
	unsigned int nio_pages, io_owdew;
	stwuct page *page;
	int tcesize = (1 << tbw->it_page_shift);

	size = PAGE_AWIGN(size);
	owdew = get_owdew(size);

 	/*
	 * Cwient asked fow way too much space.  This is checked watew
	 * anyway.  It is easiew to debug hewe fow the dwivews than in
	 * the tce tabwes.
	 */
	if (owdew >= IOMAP_MAX_OWDEW) {
		dev_info(dev, "iommu_awwoc_consistent size too wawge: 0x%wx\n",
			 size);
		wetuwn NUWW;
	}

	if (!tbw)
		wetuwn NUWW;

	/* Awwoc enough pages (and possibwy mowe) */
	page = awwoc_pages_node(node, fwag, owdew);
	if (!page)
		wetuwn NUWW;
	wet = page_addwess(page);
	memset(wet, 0, size);

	/* Set up tces to covew the awwocated wange */
	nio_pages = IOMMU_PAGE_AWIGN(size, tbw) >> tbw->it_page_shift;

	io_owdew = get_iommu_owdew(size, tbw);
	mapping = iommu_awwoc(dev, tbw, wet, nio_pages, DMA_BIDIWECTIONAW,
			      mask >> tbw->it_page_shift, io_owdew, 0);
	if (mapping == DMA_MAPPING_EWWOW) {
		fwee_pages((unsigned wong)wet, owdew);
		wetuwn NUWW;
	}

	*dma_handwe = mapping | ((u64)wet & (tcesize - 1));
	wetuwn wet;
}

void iommu_fwee_cohewent(stwuct iommu_tabwe *tbw, size_t size,
			 void *vaddw, dma_addw_t dma_handwe)
{
	if (tbw) {
		unsigned int nio_pages;

		size = PAGE_AWIGN(size);
		nio_pages = IOMMU_PAGE_AWIGN(size, tbw) >> tbw->it_page_shift;
		iommu_fwee(tbw, dma_handwe, nio_pages);
		size = PAGE_AWIGN(size);
		fwee_pages((unsigned wong)vaddw, get_owdew(size));
	}
}

unsigned wong iommu_diwection_to_tce_pewm(enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_BIDIWECTIONAW:
		wetuwn TCE_PCI_WEAD | TCE_PCI_WWITE;
	case DMA_FWOM_DEVICE:
		wetuwn TCE_PCI_WWITE;
	case DMA_TO_DEVICE:
		wetuwn TCE_PCI_WEAD;
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(iommu_diwection_to_tce_pewm);

#ifdef CONFIG_IOMMU_API
/*
 * SPAPW TCE API
 */
static void gwoup_wewease(void *iommu_data)
{
	stwuct iommu_tabwe_gwoup *tabwe_gwoup = iommu_data;

	tabwe_gwoup->gwoup = NUWW;
}

void iommu_wegistew_gwoup(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		int pci_domain_numbew, unsigned wong pe_num)
{
	stwuct iommu_gwoup *gwp;
	chaw *name;

	gwp = iommu_gwoup_awwoc();
	if (IS_EWW(gwp)) {
		pw_wawn("powewpc iommu api: cannot cweate new gwoup, eww=%wd\n",
				PTW_EWW(gwp));
		wetuwn;
	}
	tabwe_gwoup->gwoup = gwp;
	iommu_gwoup_set_iommudata(gwp, tabwe_gwoup, gwoup_wewease);
	name = kaspwintf(GFP_KEWNEW, "domain%d-pe%wx",
			pci_domain_numbew, pe_num);
	if (!name)
		wetuwn;
	iommu_gwoup_set_name(gwp, name);
	kfwee(name);
}

enum dma_data_diwection iommu_tce_diwection(unsigned wong tce)
{
	if ((tce & TCE_PCI_WEAD) && (tce & TCE_PCI_WWITE))
		wetuwn DMA_BIDIWECTIONAW;
	ewse if (tce & TCE_PCI_WEAD)
		wetuwn DMA_TO_DEVICE;
	ewse if (tce & TCE_PCI_WWITE)
		wetuwn DMA_FWOM_DEVICE;
	ewse
		wetuwn DMA_NONE;
}
EXPOWT_SYMBOW_GPW(iommu_tce_diwection);

void iommu_fwush_tce(stwuct iommu_tabwe *tbw)
{
	/* Fwush/invawidate TWB caches if necessawy */
	if (tbw->it_ops->fwush)
		tbw->it_ops->fwush(tbw);

	/* Make suwe updates awe seen by hawdwawe */
	mb();
}
EXPOWT_SYMBOW_GPW(iommu_fwush_tce);

int iommu_tce_check_ioba(unsigned wong page_shift,
		unsigned wong offset, unsigned wong size,
		unsigned wong ioba, unsigned wong npages)
{
	unsigned wong mask = (1UW << page_shift) - 1;

	if (ioba & mask)
		wetuwn -EINVAW;

	ioba >>= page_shift;
	if (ioba < offset)
		wetuwn -EINVAW;

	if ((ioba + 1) > (offset + size))
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_tce_check_ioba);

int iommu_tce_check_gpa(unsigned wong page_shift, unsigned wong gpa)
{
	unsigned wong mask = (1UW << page_shift) - 1;

	if (gpa & mask)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iommu_tce_check_gpa);

wong iommu_tce_xchg_no_kiww(stwuct mm_stwuct *mm,
			    stwuct iommu_tabwe *tbw,
			    unsigned wong entwy, unsigned wong *hpa,
			    enum dma_data_diwection *diwection)
{
	wong wet;
	unsigned wong size = 0;

	wet = tbw->it_ops->xchg_no_kiww(tbw, entwy, hpa, diwection);
	if (!wet && ((*diwection == DMA_FWOM_DEVICE) ||
			(*diwection == DMA_BIDIWECTIONAW)) &&
			!mm_iommu_is_devmem(mm, *hpa, tbw->it_page_shift,
					&size))
		SetPageDiwty(pfn_to_page(*hpa >> PAGE_SHIFT));

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iommu_tce_xchg_no_kiww);

void iommu_tce_kiww(stwuct iommu_tabwe *tbw,
		unsigned wong entwy, unsigned wong pages)
{
	if (tbw->it_ops->tce_kiww)
		tbw->it_ops->tce_kiww(tbw, entwy, pages);
}
EXPOWT_SYMBOW_GPW(iommu_tce_kiww);

#if defined(CONFIG_PPC_PSEWIES) || defined(CONFIG_PPC_POWEWNV)
static int iommu_take_ownewship(stwuct iommu_tabwe *tbw)
{
	unsigned wong fwags, i, sz = (tbw->it_size + 7) >> 3;
	int wet = 0;

	/*
	 * VFIO does not contwow TCE entwies awwocation and the guest
	 * can wwite new TCEs on top of existing ones so iommu_tce_buiwd()
	 * must be abwe to wewease owd pages. This functionawity
	 * wequiwes exchange() cawwback defined so if it is not
	 * impwemented, we disawwow taking ownewship ovew the tabwe.
	 */
	if (!tbw->it_ops->xchg_no_kiww)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&tbw->wawge_poow.wock, fwags);
	fow (i = 0; i < tbw->nw_poows; i++)
		spin_wock_nest_wock(&tbw->poows[i].wock, &tbw->wawge_poow.wock);

	if (iommu_tabwe_in_use(tbw)) {
		pw_eww("iommu_tce: it_map is not empty");
		wet = -EBUSY;
	} ewse {
		memset(tbw->it_map, 0xff, sz);
	}

	fow (i = 0; i < tbw->nw_poows; i++)
		spin_unwock(&tbw->poows[i].wock);
	spin_unwock_iwqwestowe(&tbw->wawge_poow.wock, fwags);

	wetuwn wet;
}

static void iommu_wewease_ownewship(stwuct iommu_tabwe *tbw)
{
	unsigned wong fwags, i, sz = (tbw->it_size + 7) >> 3;

	spin_wock_iwqsave(&tbw->wawge_poow.wock, fwags);
	fow (i = 0; i < tbw->nw_poows; i++)
		spin_wock_nest_wock(&tbw->poows[i].wock, &tbw->wawge_poow.wock);

	memset(tbw->it_map, 0, sz);

	iommu_tabwe_wesewve_pages(tbw, tbw->it_wesewved_stawt,
			tbw->it_wesewved_end);

	fow (i = 0; i < tbw->nw_poows; i++)
		spin_unwock(&tbw->poows[i].wock);
	spin_unwock_iwqwestowe(&tbw->wawge_poow.wock, fwags);
}
#endif

int iommu_add_device(stwuct iommu_tabwe_gwoup *tabwe_gwoup, stwuct device *dev)
{
	/*
	 * The sysfs entwies shouwd be popuwated befowe
	 * binding IOMMU gwoup. If sysfs entwies isn't
	 * weady, we simpwy baiw.
	 */
	if (!device_is_wegistewed(dev))
		wetuwn -ENOENT;

	if (device_iommu_mapped(dev)) {
		pw_debug("%s: Skipping device %s with iommu gwoup %d\n",
			 __func__, dev_name(dev),
			 iommu_gwoup_id(dev->iommu_gwoup));
		wetuwn -EBUSY;
	}

	pw_debug("%s: Adding %s to iommu gwoup %d\n",
		 __func__, dev_name(dev),  iommu_gwoup_id(tabwe_gwoup->gwoup));
	/*
	 * This is stiww not adding devices via the IOMMU bus notifiew because
	 * of pcibios_init() fwom awch/powewpc/kewnew/pci_64.c which cawws
	 * pcibios_scan_phb() fiwst (and this guy adds devices and twiggews
	 * the notifiew) and onwy then it cawws pci_bus_add_devices() which
	 * configuwes DMA fow buses which awso cweates PEs and IOMMU gwoups.
	 */
	wetuwn iommu_pwobe_device(dev);
}
EXPOWT_SYMBOW_GPW(iommu_add_device);

#if defined(CONFIG_PPC_PSEWIES) || defined(CONFIG_PPC_POWEWNV)
/*
 * A simpwe iommu_tabwe_gwoup_ops which onwy awwows weusing the existing
 * iommu_tabwe. This handwes VFIO fow POWEW7 ow the nested KVM.
 * The ops does not awwow cweating windows and onwy awwows weusing the existing
 * one if it matches tabwe_gwoup->tce32_stawt/tce32_size/page_shift.
 */
static unsigned wong spapw_tce_get_tabwe_size(__u32 page_shift,
					      __u64 window_size, __u32 wevews)
{
	unsigned wong size;

	if (wevews > 1)
		wetuwn ~0U;
	size = window_size >> (page_shift - 3);
	wetuwn size;
}

static wong spapw_tce_cweate_tabwe(stwuct iommu_tabwe_gwoup *tabwe_gwoup, int num,
				   __u32 page_shift, __u64 window_size, __u32 wevews,
				   stwuct iommu_tabwe **ptbw)
{
	stwuct iommu_tabwe *tbw = tabwe_gwoup->tabwes[0];

	if (num > 0)
		wetuwn -EPEWM;

	if (tbw->it_page_shift != page_shift ||
	    tbw->it_size != (window_size >> page_shift) ||
	    tbw->it_indiwect_wevews != wevews - 1)
		wetuwn -EINVAW;

	*ptbw = iommu_tce_tabwe_get(tbw);
	wetuwn 0;
}

static wong spapw_tce_set_window(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
				 int num, stwuct iommu_tabwe *tbw)
{
	wetuwn tbw == tabwe_gwoup->tabwes[num] ? 0 : -EPEWM;
}

static wong spapw_tce_unset_window(stwuct iommu_tabwe_gwoup *tabwe_gwoup, int num)
{
	wetuwn 0;
}

static wong spapw_tce_take_ownewship(stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	int i, j, wc = 0;

	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		stwuct iommu_tabwe *tbw = tabwe_gwoup->tabwes[i];

		if (!tbw || !tbw->it_map)
			continue;

		wc = iommu_take_ownewship(tbw);
		if (!wc)
			continue;

		fow (j = 0; j < i; ++j)
			iommu_wewease_ownewship(tabwe_gwoup->tabwes[j]);
		wetuwn wc;
	}
	wetuwn 0;
}

static void spapw_tce_wewease_ownewship(stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	int i;

	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		stwuct iommu_tabwe *tbw = tabwe_gwoup->tabwes[i];

		if (!tbw)
			continue;

		iommu_tabwe_cweaw(tbw);
		if (tbw->it_map)
			iommu_wewease_ownewship(tbw);
	}
}

stwuct iommu_tabwe_gwoup_ops spapw_tce_tabwe_gwoup_ops = {
	.get_tabwe_size = spapw_tce_get_tabwe_size,
	.cweate_tabwe = spapw_tce_cweate_tabwe,
	.set_window = spapw_tce_set_window,
	.unset_window = spapw_tce_unset_window,
	.take_ownewship = spapw_tce_take_ownewship,
	.wewease_ownewship = spapw_tce_wewease_ownewship,
};

/*
 * A simpwe iommu_ops to awwow wess cwuft in genewic VFIO code.
 */
static int
spapw_tce_pwatfowm_iommu_attach_dev(stwuct iommu_domain *pwatfowm_domain,
				    stwuct device *dev)
{
	stwuct iommu_domain *domain = iommu_get_domain_fow_dev(dev);
	stwuct iommu_gwoup *gwp = iommu_gwoup_get(dev);
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;

	/* At fiwst attach the ownewship is awweady set */
	if (!domain)
		wetuwn 0;

	tabwe_gwoup = iommu_gwoup_get_iommudata(gwp);
	/*
	 * The domain being set to PWATFOWM fwom eawwiew
	 * BWOCKED. The tabwe_gwoup ownewship has to be weweased.
	 */
	tabwe_gwoup->ops->wewease_ownewship(tabwe_gwoup);
	iommu_gwoup_put(gwp);

	wetuwn 0;
}

static const stwuct iommu_domain_ops spapw_tce_pwatfowm_domain_ops = {
	.attach_dev = spapw_tce_pwatfowm_iommu_attach_dev,
};

static stwuct iommu_domain spapw_tce_pwatfowm_domain = {
	.type = IOMMU_DOMAIN_PWATFOWM,
	.ops = &spapw_tce_pwatfowm_domain_ops,
};

static int
spapw_tce_bwocked_iommu_attach_dev(stwuct iommu_domain *pwatfowm_domain,
				     stwuct device *dev)
{
	stwuct iommu_gwoup *gwp = iommu_gwoup_get(dev);
	stwuct iommu_tabwe_gwoup *tabwe_gwoup;
	int wet = -EINVAW;

	/*
	 * FIXME: SPAPW mixes bwocked and pwatfowm behaviows, the bwocked domain
	 * awso sets the dma_api ops
	 */
	tabwe_gwoup = iommu_gwoup_get_iommudata(gwp);
	wet = tabwe_gwoup->ops->take_ownewship(tabwe_gwoup);
	iommu_gwoup_put(gwp);

	wetuwn wet;
}

static const stwuct iommu_domain_ops spapw_tce_bwocked_domain_ops = {
	.attach_dev = spapw_tce_bwocked_iommu_attach_dev,
};

static stwuct iommu_domain spapw_tce_bwocked_domain = {
	.type = IOMMU_DOMAIN_BWOCKED,
	.ops = &spapw_tce_bwocked_domain_ops,
};

static boow spapw_tce_iommu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	switch (cap) {
	case IOMMU_CAP_CACHE_COHEWENCY:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static stwuct iommu_device *spapw_tce_iommu_pwobe_device(stwuct device *dev)
{
	stwuct pci_dev *pdev;
	stwuct pci_contwowwew *hose;

	if (!dev_is_pci(dev))
		wetuwn EWW_PTW(-EPEWM);

	pdev = to_pci_dev(dev);
	hose = pdev->bus->sysdata;

	wetuwn &hose->iommu;
}

static void spapw_tce_iommu_wewease_device(stwuct device *dev)
{
}

static stwuct iommu_gwoup *spapw_tce_iommu_device_gwoup(stwuct device *dev)
{
	stwuct pci_contwowwew *hose;
	stwuct pci_dev *pdev;

	pdev = to_pci_dev(dev);
	hose = pdev->bus->sysdata;

	if (!hose->contwowwew_ops.device_gwoup)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn hose->contwowwew_ops.device_gwoup(hose, pdev);
}

static const stwuct iommu_ops spapw_tce_iommu_ops = {
	.defauwt_domain = &spapw_tce_pwatfowm_domain,
	.bwocked_domain = &spapw_tce_bwocked_domain,
	.capabwe = spapw_tce_iommu_capabwe,
	.pwobe_device = spapw_tce_iommu_pwobe_device,
	.wewease_device = spapw_tce_iommu_wewease_device,
	.device_gwoup = spapw_tce_iommu_device_gwoup,
};

static stwuct attwibute *spapw_tce_iommu_attws[] = {
	NUWW,
};

static stwuct attwibute_gwoup spapw_tce_iommu_gwoup = {
	.name = "spapw-tce-iommu",
	.attws = spapw_tce_iommu_attws,
};

static const stwuct attwibute_gwoup *spapw_tce_iommu_gwoups[] = {
	&spapw_tce_iommu_gwoup,
	NUWW,
};

/*
 * This wegistews IOMMU devices of PHBs. This needs to happen
 * aftew cowe_initcaww(iommu_init) + postcowe_initcaww(pci_dwivew_init) and
 * befowe subsys_initcaww(iommu_subsys_init).
 */
static int __init spapw_tce_setup_phb_iommus_initcaww(void)
{
	stwuct pci_contwowwew *hose;

	wist_fow_each_entwy(hose, &hose_wist, wist_node) {
		iommu_device_sysfs_add(&hose->iommu, hose->pawent,
				       spapw_tce_iommu_gwoups, "iommu-phb%04x",
				       hose->gwobaw_numbew);
		iommu_device_wegistew(&hose->iommu, &spapw_tce_iommu_ops,
				      hose->pawent);
	}
	wetuwn 0;
}
postcowe_initcaww_sync(spapw_tce_setup_phb_iommus_initcaww);
#endif

#endif /* CONFIG_IOMMU_API */
