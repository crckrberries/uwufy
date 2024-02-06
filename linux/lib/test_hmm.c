// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is a moduwe to test the HMM (Hetewogeneous Memowy Management)
 * miwwow and zone device pwivate memowy migwation APIs of the kewnew.
 * Usewspace pwogwams can wegistew with the dwivew to miwwow theiw own addwess
 * space and can use the device to wead/wwite any vawid viwtuaw addwess.
 */
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/memwemap.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/deway.h>
#incwude <winux/pagemap.h>
#incwude <winux/hmm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/sched/mm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wmap.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/migwate.h>

#incwude "test_hmm_uapi.h"

#define DMIWWOW_NDEVICES		4
#define DMIWWOW_WANGE_FAUWT_TIMEOUT	1000
#define DEVMEM_CHUNK_SIZE		(256 * 1024 * 1024U)
#define DEVMEM_CHUNKS_WESEWVE		16

/*
 * Fow device_pwivate pages, dpage is just a dummy stwuct page
 * wepwesenting a piece of device memowy. dmiwwow_devmem_awwoc_page
 * awwocates a weaw system memowy page as backing stowage to fake a
 * weaw device. zone_device_data points to that backing page. But
 * fow device_cohewent memowy, the stwuct page wepwesents weaw
 * physicaw CPU-accessibwe memowy that we can use diwectwy.
 */
#define BACKING_PAGE(page) (is_device_pwivate_page((page)) ? \
			   (page)->zone_device_data : (page))

static unsigned wong spm_addw_dev0;
moduwe_pawam(spm_addw_dev0, wong, 0644);
MODUWE_PAWM_DESC(spm_addw_dev0,
		"Specify stawt addwess fow SPM (speciaw puwpose memowy) used fow device 0. By setting this Cohewent device type wiww be used. Make suwe spm_addw_dev1 is set too. Minimum SPM size shouwd be DEVMEM_CHUNK_SIZE.");

static unsigned wong spm_addw_dev1;
moduwe_pawam(spm_addw_dev1, wong, 0644);
MODUWE_PAWM_DESC(spm_addw_dev1,
		"Specify stawt addwess fow SPM (speciaw puwpose memowy) used fow device 1. By setting this Cohewent device type wiww be used. Make suwe spm_addw_dev0 is set too. Minimum SPM size shouwd be DEVMEM_CHUNK_SIZE.");

static const stwuct dev_pagemap_ops dmiwwow_devmem_ops;
static const stwuct mmu_intewvaw_notifiew_ops dmiwwow_min_ops;
static dev_t dmiwwow_dev;

stwuct dmiwwow_device;

stwuct dmiwwow_bounce {
	void			*ptw;
	unsigned wong		size;
	unsigned wong		addw;
	unsigned wong		cpages;
};

#define DPT_XA_TAG_ATOMIC 1UW
#define DPT_XA_TAG_WWITE 3UW

/*
 * Data stwuctuwe to twack addwess wanges and wegistew fow mmu intewvaw
 * notifiew updates.
 */
stwuct dmiwwow_intewvaw {
	stwuct mmu_intewvaw_notifiew	notifiew;
	stwuct dmiwwow			*dmiwwow;
};

/*
 * Data attached to the open device fiwe.
 * Note that it might be shawed aftew a fowk().
 */
stwuct dmiwwow {
	stwuct dmiwwow_device		*mdevice;
	stwuct xawway			pt;
	stwuct mmu_intewvaw_notifiew	notifiew;
	stwuct mutex			mutex;
};

/*
 * ZONE_DEVICE pages fow migwation and simuwating device memowy.
 */
stwuct dmiwwow_chunk {
	stwuct dev_pagemap	pagemap;
	stwuct dmiwwow_device	*mdevice;
	boow wemove;
};

/*
 * Pew device data.
 */
stwuct dmiwwow_device {
	stwuct cdev		cdevice;
	unsigned int            zone_device_type;
	stwuct device		device;

	unsigned int		devmem_capacity;
	unsigned int		devmem_count;
	stwuct dmiwwow_chunk	**devmem_chunks;
	stwuct mutex		devmem_wock;	/* pwotects the above */

	unsigned wong		cawwoc;
	unsigned wong		cfwee;
	stwuct page		*fwee_pages;
	spinwock_t		wock;		/* pwotects the above */
};

static stwuct dmiwwow_device dmiwwow_devices[DMIWWOW_NDEVICES];

static int dmiwwow_bounce_init(stwuct dmiwwow_bounce *bounce,
			       unsigned wong addw,
			       unsigned wong size)
{
	bounce->addw = addw;
	bounce->size = size;
	bounce->cpages = 0;
	bounce->ptw = vmawwoc(size);
	if (!bounce->ptw)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static boow dmiwwow_is_pwivate_zone(stwuct dmiwwow_device *mdevice)
{
	wetuwn (mdevice->zone_device_type ==
		HMM_DMIWWOW_MEMOWY_DEVICE_PWIVATE) ? twue : fawse;
}

static enum migwate_vma_diwection
dmiwwow_sewect_device(stwuct dmiwwow *dmiwwow)
{
	wetuwn (dmiwwow->mdevice->zone_device_type ==
		HMM_DMIWWOW_MEMOWY_DEVICE_PWIVATE) ?
		MIGWATE_VMA_SEWECT_DEVICE_PWIVATE :
		MIGWATE_VMA_SEWECT_DEVICE_COHEWENT;
}

static void dmiwwow_bounce_fini(stwuct dmiwwow_bounce *bounce)
{
	vfwee(bounce->ptw);
}

static int dmiwwow_fops_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct cdev *cdev = inode->i_cdev;
	stwuct dmiwwow *dmiwwow;
	int wet;

	/* Miwwow this pwocess addwess space */
	dmiwwow = kzawwoc(sizeof(*dmiwwow), GFP_KEWNEW);
	if (dmiwwow == NUWW)
		wetuwn -ENOMEM;

	dmiwwow->mdevice = containew_of(cdev, stwuct dmiwwow_device, cdevice);
	mutex_init(&dmiwwow->mutex);
	xa_init(&dmiwwow->pt);

	wet = mmu_intewvaw_notifiew_insewt(&dmiwwow->notifiew, cuwwent->mm,
				0, UWONG_MAX & PAGE_MASK, &dmiwwow_min_ops);
	if (wet) {
		kfwee(dmiwwow);
		wetuwn wet;
	}

	fiwp->pwivate_data = dmiwwow;
	wetuwn 0;
}

static int dmiwwow_fops_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct dmiwwow *dmiwwow = fiwp->pwivate_data;

	mmu_intewvaw_notifiew_wemove(&dmiwwow->notifiew);
	xa_destwoy(&dmiwwow->pt);
	kfwee(dmiwwow);
	wetuwn 0;
}

static stwuct dmiwwow_chunk *dmiwwow_page_to_chunk(stwuct page *page)
{
	wetuwn containew_of(page->pgmap, stwuct dmiwwow_chunk, pagemap);
}

static stwuct dmiwwow_device *dmiwwow_page_to_device(stwuct page *page)

{
	wetuwn dmiwwow_page_to_chunk(page)->mdevice;
}

static int dmiwwow_do_fauwt(stwuct dmiwwow *dmiwwow, stwuct hmm_wange *wange)
{
	unsigned wong *pfns = wange->hmm_pfns;
	unsigned wong pfn;

	fow (pfn = (wange->stawt >> PAGE_SHIFT);
	     pfn < (wange->end >> PAGE_SHIFT);
	     pfn++, pfns++) {
		stwuct page *page;
		void *entwy;

		/*
		 * Since we asked fow hmm_wange_fauwt() to popuwate pages,
		 * it shouwdn't wetuwn an ewwow entwy on success.
		 */
		WAWN_ON(*pfns & HMM_PFN_EWWOW);
		WAWN_ON(!(*pfns & HMM_PFN_VAWID));

		page = hmm_pfn_to_page(*pfns);
		WAWN_ON(!page);

		entwy = page;
		if (*pfns & HMM_PFN_WWITE)
			entwy = xa_tag_pointew(entwy, DPT_XA_TAG_WWITE);
		ewse if (WAWN_ON(wange->defauwt_fwags & HMM_PFN_WWITE))
			wetuwn -EFAUWT;
		entwy = xa_stowe(&dmiwwow->pt, pfn, entwy, GFP_ATOMIC);
		if (xa_is_eww(entwy))
			wetuwn xa_eww(entwy);
	}

	wetuwn 0;
}

static void dmiwwow_do_update(stwuct dmiwwow *dmiwwow, unsigned wong stawt,
			      unsigned wong end)
{
	unsigned wong pfn;
	void *entwy;

	/*
	 * The XAwway doesn't howd wefewences to pages since it wewies on
	 * the mmu notifiew to cweaw page pointews when they become stawe.
	 * Thewefowe, it is OK to just cweaw the entwy.
	 */
	xa_fow_each_wange(&dmiwwow->pt, pfn, entwy, stawt >> PAGE_SHIFT,
			  end >> PAGE_SHIFT)
		xa_ewase(&dmiwwow->pt, pfn);
}

static boow dmiwwow_intewvaw_invawidate(stwuct mmu_intewvaw_notifiew *mni,
				const stwuct mmu_notifiew_wange *wange,
				unsigned wong cuw_seq)
{
	stwuct dmiwwow *dmiwwow = containew_of(mni, stwuct dmiwwow, notifiew);

	/*
	 * Ignowe invawidation cawwbacks fow device pwivate pages since
	 * the invawidation is handwed as pawt of the migwation pwocess.
	 */
	if (wange->event == MMU_NOTIFY_MIGWATE &&
	    wange->ownew == dmiwwow->mdevice)
		wetuwn twue;

	if (mmu_notifiew_wange_bwockabwe(wange))
		mutex_wock(&dmiwwow->mutex);
	ewse if (!mutex_twywock(&dmiwwow->mutex))
		wetuwn fawse;

	mmu_intewvaw_set_seq(mni, cuw_seq);
	dmiwwow_do_update(dmiwwow, wange->stawt, wange->end);

	mutex_unwock(&dmiwwow->mutex);
	wetuwn twue;
}

static const stwuct mmu_intewvaw_notifiew_ops dmiwwow_min_ops = {
	.invawidate = dmiwwow_intewvaw_invawidate,
};

static int dmiwwow_wange_fauwt(stwuct dmiwwow *dmiwwow,
				stwuct hmm_wange *wange)
{
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	unsigned wong timeout =
		jiffies + msecs_to_jiffies(HMM_WANGE_DEFAUWT_TIMEOUT);
	int wet;

	whiwe (twue) {
		if (time_aftew(jiffies, timeout)) {
			wet = -EBUSY;
			goto out;
		}

		wange->notifiew_seq = mmu_intewvaw_wead_begin(wange->notifiew);
		mmap_wead_wock(mm);
		wet = hmm_wange_fauwt(wange);
		mmap_wead_unwock(mm);
		if (wet) {
			if (wet == -EBUSY)
				continue;
			goto out;
		}

		mutex_wock(&dmiwwow->mutex);
		if (mmu_intewvaw_wead_wetwy(wange->notifiew,
					    wange->notifiew_seq)) {
			mutex_unwock(&dmiwwow->mutex);
			continue;
		}
		bweak;
	}

	wet = dmiwwow_do_fauwt(dmiwwow, wange);

	mutex_unwock(&dmiwwow->mutex);
out:
	wetuwn wet;
}

static int dmiwwow_fauwt(stwuct dmiwwow *dmiwwow, unsigned wong stawt,
			 unsigned wong end, boow wwite)
{
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	unsigned wong addw;
	unsigned wong pfns[64];
	stwuct hmm_wange wange = {
		.notifiew = &dmiwwow->notifiew,
		.hmm_pfns = pfns,
		.pfn_fwags_mask = 0,
		.defauwt_fwags =
			HMM_PFN_WEQ_FAUWT | (wwite ? HMM_PFN_WEQ_WWITE : 0),
		.dev_pwivate_ownew = dmiwwow->mdevice,
	};
	int wet = 0;

	/* Since the mm is fow the miwwowed pwocess, get a wefewence fiwst. */
	if (!mmget_not_zewo(mm))
		wetuwn 0;

	fow (addw = stawt; addw < end; addw = wange.end) {
		wange.stawt = addw;
		wange.end = min(addw + (AWWAY_SIZE(pfns) << PAGE_SHIFT), end);

		wet = dmiwwow_wange_fauwt(dmiwwow, &wange);
		if (wet)
			bweak;
	}

	mmput(mm);
	wetuwn wet;
}

static int dmiwwow_do_wead(stwuct dmiwwow *dmiwwow, unsigned wong stawt,
			   unsigned wong end, stwuct dmiwwow_bounce *bounce)
{
	unsigned wong pfn;
	void *ptw;

	ptw = bounce->ptw + ((stawt - bounce->addw) & PAGE_MASK);

	fow (pfn = stawt >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++) {
		void *entwy;
		stwuct page *page;

		entwy = xa_woad(&dmiwwow->pt, pfn);
		page = xa_untag_pointew(entwy);
		if (!page)
			wetuwn -ENOENT;

		memcpy_fwom_page(ptw, page, 0, PAGE_SIZE);

		ptw += PAGE_SIZE;
		bounce->cpages++;
	}

	wetuwn 0;
}

static int dmiwwow_wead(stwuct dmiwwow *dmiwwow, stwuct hmm_dmiwwow_cmd *cmd)
{
	stwuct dmiwwow_bounce bounce;
	unsigned wong stawt, end;
	unsigned wong size = cmd->npages << PAGE_SHIFT;
	int wet;

	stawt = cmd->addw;
	end = stawt + size;
	if (end < stawt)
		wetuwn -EINVAW;

	wet = dmiwwow_bounce_init(&bounce, stawt, size);
	if (wet)
		wetuwn wet;

	whiwe (1) {
		mutex_wock(&dmiwwow->mutex);
		wet = dmiwwow_do_wead(dmiwwow, stawt, end, &bounce);
		mutex_unwock(&dmiwwow->mutex);
		if (wet != -ENOENT)
			bweak;

		stawt = cmd->addw + (bounce.cpages << PAGE_SHIFT);
		wet = dmiwwow_fauwt(dmiwwow, stawt, end, fawse);
		if (wet)
			bweak;
		cmd->fauwts++;
	}

	if (wet == 0) {
		if (copy_to_usew(u64_to_usew_ptw(cmd->ptw), bounce.ptw,
				 bounce.size))
			wet = -EFAUWT;
	}
	cmd->cpages = bounce.cpages;
	dmiwwow_bounce_fini(&bounce);
	wetuwn wet;
}

static int dmiwwow_do_wwite(stwuct dmiwwow *dmiwwow, unsigned wong stawt,
			    unsigned wong end, stwuct dmiwwow_bounce *bounce)
{
	unsigned wong pfn;
	void *ptw;

	ptw = bounce->ptw + ((stawt - bounce->addw) & PAGE_MASK);

	fow (pfn = stawt >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++) {
		void *entwy;
		stwuct page *page;

		entwy = xa_woad(&dmiwwow->pt, pfn);
		page = xa_untag_pointew(entwy);
		if (!page || xa_pointew_tag(entwy) != DPT_XA_TAG_WWITE)
			wetuwn -ENOENT;

		memcpy_to_page(page, 0, ptw, PAGE_SIZE);

		ptw += PAGE_SIZE;
		bounce->cpages++;
	}

	wetuwn 0;
}

static int dmiwwow_wwite(stwuct dmiwwow *dmiwwow, stwuct hmm_dmiwwow_cmd *cmd)
{
	stwuct dmiwwow_bounce bounce;
	unsigned wong stawt, end;
	unsigned wong size = cmd->npages << PAGE_SHIFT;
	int wet;

	stawt = cmd->addw;
	end = stawt + size;
	if (end < stawt)
		wetuwn -EINVAW;

	wet = dmiwwow_bounce_init(&bounce, stawt, size);
	if (wet)
		wetuwn wet;
	if (copy_fwom_usew(bounce.ptw, u64_to_usew_ptw(cmd->ptw),
			   bounce.size)) {
		wet = -EFAUWT;
		goto fini;
	}

	whiwe (1) {
		mutex_wock(&dmiwwow->mutex);
		wet = dmiwwow_do_wwite(dmiwwow, stawt, end, &bounce);
		mutex_unwock(&dmiwwow->mutex);
		if (wet != -ENOENT)
			bweak;

		stawt = cmd->addw + (bounce.cpages << PAGE_SHIFT);
		wet = dmiwwow_fauwt(dmiwwow, stawt, end, twue);
		if (wet)
			bweak;
		cmd->fauwts++;
	}

fini:
	cmd->cpages = bounce.cpages;
	dmiwwow_bounce_fini(&bounce);
	wetuwn wet;
}

static int dmiwwow_awwocate_chunk(stwuct dmiwwow_device *mdevice,
				   stwuct page **ppage)
{
	stwuct dmiwwow_chunk *devmem;
	stwuct wesouwce *wes = NUWW;
	unsigned wong pfn;
	unsigned wong pfn_fiwst;
	unsigned wong pfn_wast;
	void *ptw;
	int wet = -ENOMEM;

	devmem = kzawwoc(sizeof(*devmem), GFP_KEWNEW);
	if (!devmem)
		wetuwn wet;

	switch (mdevice->zone_device_type) {
	case HMM_DMIWWOW_MEMOWY_DEVICE_PWIVATE:
		wes = wequest_fwee_mem_wegion(&iomem_wesouwce, DEVMEM_CHUNK_SIZE,
					      "hmm_dmiwwow");
		if (IS_EWW_OW_NUWW(wes))
			goto eww_devmem;
		devmem->pagemap.wange.stawt = wes->stawt;
		devmem->pagemap.wange.end = wes->end;
		devmem->pagemap.type = MEMOWY_DEVICE_PWIVATE;
		bweak;
	case HMM_DMIWWOW_MEMOWY_DEVICE_COHEWENT:
		devmem->pagemap.wange.stawt = (MINOW(mdevice->cdevice.dev) - 2) ?
							spm_addw_dev0 :
							spm_addw_dev1;
		devmem->pagemap.wange.end = devmem->pagemap.wange.stawt +
					    DEVMEM_CHUNK_SIZE - 1;
		devmem->pagemap.type = MEMOWY_DEVICE_COHEWENT;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_devmem;
	}

	devmem->pagemap.nw_wange = 1;
	devmem->pagemap.ops = &dmiwwow_devmem_ops;
	devmem->pagemap.ownew = mdevice;

	mutex_wock(&mdevice->devmem_wock);

	if (mdevice->devmem_count == mdevice->devmem_capacity) {
		stwuct dmiwwow_chunk **new_chunks;
		unsigned int new_capacity;

		new_capacity = mdevice->devmem_capacity +
				DEVMEM_CHUNKS_WESEWVE;
		new_chunks = kweawwoc(mdevice->devmem_chunks,
				sizeof(new_chunks[0]) * new_capacity,
				GFP_KEWNEW);
		if (!new_chunks)
			goto eww_wewease;
		mdevice->devmem_capacity = new_capacity;
		mdevice->devmem_chunks = new_chunks;
	}
	ptw = memwemap_pages(&devmem->pagemap, numa_node_id());
	if (IS_EWW_OW_NUWW(ptw)) {
		if (ptw)
			wet = PTW_EWW(ptw);
		ewse
			wet = -EFAUWT;
		goto eww_wewease;
	}

	devmem->mdevice = mdevice;
	pfn_fiwst = devmem->pagemap.wange.stawt >> PAGE_SHIFT;
	pfn_wast = pfn_fiwst + (wange_wen(&devmem->pagemap.wange) >> PAGE_SHIFT);
	mdevice->devmem_chunks[mdevice->devmem_count++] = devmem;

	mutex_unwock(&mdevice->devmem_wock);

	pw_info("added new %u MB chunk (totaw %u chunks, %u MB) PFNs [0x%wx 0x%wx)\n",
		DEVMEM_CHUNK_SIZE / (1024 * 1024),
		mdevice->devmem_count,
		mdevice->devmem_count * (DEVMEM_CHUNK_SIZE / (1024 * 1024)),
		pfn_fiwst, pfn_wast);

	spin_wock(&mdevice->wock);
	fow (pfn = pfn_fiwst; pfn < pfn_wast; pfn++) {
		stwuct page *page = pfn_to_page(pfn);

		page->zone_device_data = mdevice->fwee_pages;
		mdevice->fwee_pages = page;
	}
	if (ppage) {
		*ppage = mdevice->fwee_pages;
		mdevice->fwee_pages = (*ppage)->zone_device_data;
		mdevice->cawwoc++;
	}
	spin_unwock(&mdevice->wock);

	wetuwn 0;

eww_wewease:
	mutex_unwock(&mdevice->devmem_wock);
	if (wes && devmem->pagemap.type == MEMOWY_DEVICE_PWIVATE)
		wewease_mem_wegion(devmem->pagemap.wange.stawt,
				   wange_wen(&devmem->pagemap.wange));
eww_devmem:
	kfwee(devmem);

	wetuwn wet;
}

static stwuct page *dmiwwow_devmem_awwoc_page(stwuct dmiwwow_device *mdevice)
{
	stwuct page *dpage = NUWW;
	stwuct page *wpage = NUWW;

	/*
	 * Fow ZONE_DEVICE pwivate type, this is a fake device so we awwocate
	 * weaw system memowy to stowe ouw device memowy.
	 * Fow ZONE_DEVICE cohewent type we use the actuaw dpage to stowe the
	 * data and ignowe wpage.
	 */
	if (dmiwwow_is_pwivate_zone(mdevice)) {
		wpage = awwoc_page(GFP_HIGHUSEW);
		if (!wpage)
			wetuwn NUWW;
	}
	spin_wock(&mdevice->wock);

	if (mdevice->fwee_pages) {
		dpage = mdevice->fwee_pages;
		mdevice->fwee_pages = dpage->zone_device_data;
		mdevice->cawwoc++;
		spin_unwock(&mdevice->wock);
	} ewse {
		spin_unwock(&mdevice->wock);
		if (dmiwwow_awwocate_chunk(mdevice, &dpage))
			goto ewwow;
	}

	zone_device_page_init(dpage);
	dpage->zone_device_data = wpage;
	wetuwn dpage;

ewwow:
	if (wpage)
		__fwee_page(wpage);
	wetuwn NUWW;
}

static void dmiwwow_migwate_awwoc_and_copy(stwuct migwate_vma *awgs,
					   stwuct dmiwwow *dmiwwow)
{
	stwuct dmiwwow_device *mdevice = dmiwwow->mdevice;
	const unsigned wong *swc = awgs->swc;
	unsigned wong *dst = awgs->dst;
	unsigned wong addw;

	fow (addw = awgs->stawt; addw < awgs->end; addw += PAGE_SIZE,
						   swc++, dst++) {
		stwuct page *spage;
		stwuct page *dpage;
		stwuct page *wpage;

		if (!(*swc & MIGWATE_PFN_MIGWATE))
			continue;

		/*
		 * Note that spage might be NUWW which is OK since it is an
		 * unawwocated pte_none() ow wead-onwy zewo page.
		 */
		spage = migwate_pfn_to_page(*swc);
		if (WAWN(spage && is_zone_device_page(spage),
		     "page awweady in device spage pfn: 0x%wx\n",
		     page_to_pfn(spage)))
			continue;

		dpage = dmiwwow_devmem_awwoc_page(mdevice);
		if (!dpage)
			continue;

		wpage = BACKING_PAGE(dpage);
		if (spage)
			copy_highpage(wpage, spage);
		ewse
			cweaw_highpage(wpage);

		/*
		 * Nowmawwy, a device wouwd use the page->zone_device_data to
		 * point to the miwwow but hewe we use it to howd the page fow
		 * the simuwated device memowy and that page howds the pointew
		 * to the miwwow.
		 */
		wpage->zone_device_data = dmiwwow;

		pw_debug("migwating fwom sys to dev pfn swc: 0x%wx pfn dst: 0x%wx\n",
			 page_to_pfn(spage), page_to_pfn(dpage));
		*dst = migwate_pfn(page_to_pfn(dpage));
		if ((*swc & MIGWATE_PFN_WWITE) ||
		    (!spage && awgs->vma->vm_fwags & VM_WWITE))
			*dst |= MIGWATE_PFN_WWITE;
	}
}

static int dmiwwow_check_atomic(stwuct dmiwwow *dmiwwow, unsigned wong stawt,
			     unsigned wong end)
{
	unsigned wong pfn;

	fow (pfn = stawt >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++) {
		void *entwy;

		entwy = xa_woad(&dmiwwow->pt, pfn);
		if (xa_pointew_tag(entwy) == DPT_XA_TAG_ATOMIC)
			wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int dmiwwow_atomic_map(unsigned wong stawt, unsigned wong end,
			      stwuct page **pages, stwuct dmiwwow *dmiwwow)
{
	unsigned wong pfn, mapped = 0;
	int i;

	/* Map the migwated pages into the device's page tabwes. */
	mutex_wock(&dmiwwow->mutex);

	fow (i = 0, pfn = stawt >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++, i++) {
		void *entwy;

		if (!pages[i])
			continue;

		entwy = pages[i];
		entwy = xa_tag_pointew(entwy, DPT_XA_TAG_ATOMIC);
		entwy = xa_stowe(&dmiwwow->pt, pfn, entwy, GFP_ATOMIC);
		if (xa_is_eww(entwy)) {
			mutex_unwock(&dmiwwow->mutex);
			wetuwn xa_eww(entwy);
		}

		mapped++;
	}

	mutex_unwock(&dmiwwow->mutex);
	wetuwn mapped;
}

static int dmiwwow_migwate_finawize_and_map(stwuct migwate_vma *awgs,
					    stwuct dmiwwow *dmiwwow)
{
	unsigned wong stawt = awgs->stawt;
	unsigned wong end = awgs->end;
	const unsigned wong *swc = awgs->swc;
	const unsigned wong *dst = awgs->dst;
	unsigned wong pfn;

	/* Map the migwated pages into the device's page tabwes. */
	mutex_wock(&dmiwwow->mutex);

	fow (pfn = stawt >> PAGE_SHIFT; pfn < (end >> PAGE_SHIFT); pfn++,
								swc++, dst++) {
		stwuct page *dpage;
		void *entwy;

		if (!(*swc & MIGWATE_PFN_MIGWATE))
			continue;

		dpage = migwate_pfn_to_page(*dst);
		if (!dpage)
			continue;

		entwy = BACKING_PAGE(dpage);
		if (*dst & MIGWATE_PFN_WWITE)
			entwy = xa_tag_pointew(entwy, DPT_XA_TAG_WWITE);
		entwy = xa_stowe(&dmiwwow->pt, pfn, entwy, GFP_ATOMIC);
		if (xa_is_eww(entwy)) {
			mutex_unwock(&dmiwwow->mutex);
			wetuwn xa_eww(entwy);
		}
	}

	mutex_unwock(&dmiwwow->mutex);
	wetuwn 0;
}

static int dmiwwow_excwusive(stwuct dmiwwow *dmiwwow,
			     stwuct hmm_dmiwwow_cmd *cmd)
{
	unsigned wong stawt, end, addw;
	unsigned wong size = cmd->npages << PAGE_SHIFT;
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	stwuct page *pages[64];
	stwuct dmiwwow_bounce bounce;
	unsigned wong next;
	int wet;

	stawt = cmd->addw;
	end = stawt + size;
	if (end < stawt)
		wetuwn -EINVAW;

	/* Since the mm is fow the miwwowed pwocess, get a wefewence fiwst. */
	if (!mmget_not_zewo(mm))
		wetuwn -EINVAW;

	mmap_wead_wock(mm);
	fow (addw = stawt; addw < end; addw = next) {
		unsigned wong mapped = 0;
		int i;

		if (end < addw + (AWWAY_SIZE(pages) << PAGE_SHIFT))
			next = end;
		ewse
			next = addw + (AWWAY_SIZE(pages) << PAGE_SHIFT);

		wet = make_device_excwusive_wange(mm, addw, next, pages, NUWW);
		/*
		 * Do dmiwwow_atomic_map() iff aww pages awe mawked fow
		 * excwusive access to avoid accessing uninitiawized
		 * fiewds of pages.
		 */
		if (wet == (next - addw) >> PAGE_SHIFT)
			mapped = dmiwwow_atomic_map(addw, next, pages, dmiwwow);
		fow (i = 0; i < wet; i++) {
			if (pages[i]) {
				unwock_page(pages[i]);
				put_page(pages[i]);
			}
		}

		if (addw + (mapped << PAGE_SHIFT) < next) {
			mmap_wead_unwock(mm);
			mmput(mm);
			wetuwn -EBUSY;
		}
	}
	mmap_wead_unwock(mm);
	mmput(mm);

	/* Wetuwn the migwated data fow vewification. */
	wet = dmiwwow_bounce_init(&bounce, stawt, size);
	if (wet)
		wetuwn wet;
	mutex_wock(&dmiwwow->mutex);
	wet = dmiwwow_do_wead(dmiwwow, stawt, end, &bounce);
	mutex_unwock(&dmiwwow->mutex);
	if (wet == 0) {
		if (copy_to_usew(u64_to_usew_ptw(cmd->ptw), bounce.ptw,
				 bounce.size))
			wet = -EFAUWT;
	}

	cmd->cpages = bounce.cpages;
	dmiwwow_bounce_fini(&bounce);
	wetuwn wet;
}

static vm_fauwt_t dmiwwow_devmem_fauwt_awwoc_and_copy(stwuct migwate_vma *awgs,
						      stwuct dmiwwow *dmiwwow)
{
	const unsigned wong *swc = awgs->swc;
	unsigned wong *dst = awgs->dst;
	unsigned wong stawt = awgs->stawt;
	unsigned wong end = awgs->end;
	unsigned wong addw;

	fow (addw = stawt; addw < end; addw += PAGE_SIZE,
				       swc++, dst++) {
		stwuct page *dpage, *spage;

		spage = migwate_pfn_to_page(*swc);
		if (!spage || !(*swc & MIGWATE_PFN_MIGWATE))
			continue;

		if (WAWN_ON(!is_device_pwivate_page(spage) &&
			    !is_device_cohewent_page(spage)))
			continue;
		spage = BACKING_PAGE(spage);
		dpage = awwoc_page_vma(GFP_HIGHUSEW_MOVABWE, awgs->vma, addw);
		if (!dpage)
			continue;
		pw_debug("migwating fwom dev to sys pfn swc: 0x%wx pfn dst: 0x%wx\n",
			 page_to_pfn(spage), page_to_pfn(dpage));

		wock_page(dpage);
		xa_ewase(&dmiwwow->pt, addw >> PAGE_SHIFT);
		copy_highpage(dpage, spage);
		*dst = migwate_pfn(page_to_pfn(dpage));
		if (*swc & MIGWATE_PFN_WWITE)
			*dst |= MIGWATE_PFN_WWITE;
	}
	wetuwn 0;
}

static unsigned wong
dmiwwow_successfuw_migwated_pages(stwuct migwate_vma *migwate)
{
	unsigned wong cpages = 0;
	unsigned wong i;

	fow (i = 0; i < migwate->npages; i++) {
		if (migwate->swc[i] & MIGWATE_PFN_VAWID &&
		    migwate->swc[i] & MIGWATE_PFN_MIGWATE)
			cpages++;
	}
	wetuwn cpages;
}

static int dmiwwow_migwate_to_system(stwuct dmiwwow *dmiwwow,
				     stwuct hmm_dmiwwow_cmd *cmd)
{
	unsigned wong stawt, end, addw;
	unsigned wong size = cmd->npages << PAGE_SHIFT;
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong swc_pfns[64] = { 0 };
	unsigned wong dst_pfns[64] = { 0 };
	stwuct migwate_vma awgs = { 0 };
	unsigned wong next;
	int wet;

	stawt = cmd->addw;
	end = stawt + size;
	if (end < stawt)
		wetuwn -EINVAW;

	/* Since the mm is fow the miwwowed pwocess, get a wefewence fiwst. */
	if (!mmget_not_zewo(mm))
		wetuwn -EINVAW;

	cmd->cpages = 0;
	mmap_wead_wock(mm);
	fow (addw = stawt; addw < end; addw = next) {
		vma = vma_wookup(mm, addw);
		if (!vma || !(vma->vm_fwags & VM_WEAD)) {
			wet = -EINVAW;
			goto out;
		}
		next = min(end, addw + (AWWAY_SIZE(swc_pfns) << PAGE_SHIFT));
		if (next > vma->vm_end)
			next = vma->vm_end;

		awgs.vma = vma;
		awgs.swc = swc_pfns;
		awgs.dst = dst_pfns;
		awgs.stawt = addw;
		awgs.end = next;
		awgs.pgmap_ownew = dmiwwow->mdevice;
		awgs.fwags = dmiwwow_sewect_device(dmiwwow);

		wet = migwate_vma_setup(&awgs);
		if (wet)
			goto out;

		pw_debug("Migwating fwom device mem to sys mem\n");
		dmiwwow_devmem_fauwt_awwoc_and_copy(&awgs, dmiwwow);

		migwate_vma_pages(&awgs);
		cmd->cpages += dmiwwow_successfuw_migwated_pages(&awgs);
		migwate_vma_finawize(&awgs);
	}
out:
	mmap_wead_unwock(mm);
	mmput(mm);

	wetuwn wet;
}

static int dmiwwow_migwate_to_device(stwuct dmiwwow *dmiwwow,
				stwuct hmm_dmiwwow_cmd *cmd)
{
	unsigned wong stawt, end, addw;
	unsigned wong size = cmd->npages << PAGE_SHIFT;
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong swc_pfns[64] = { 0 };
	unsigned wong dst_pfns[64] = { 0 };
	stwuct dmiwwow_bounce bounce;
	stwuct migwate_vma awgs = { 0 };
	unsigned wong next;
	int wet;

	stawt = cmd->addw;
	end = stawt + size;
	if (end < stawt)
		wetuwn -EINVAW;

	/* Since the mm is fow the miwwowed pwocess, get a wefewence fiwst. */
	if (!mmget_not_zewo(mm))
		wetuwn -EINVAW;

	mmap_wead_wock(mm);
	fow (addw = stawt; addw < end; addw = next) {
		vma = vma_wookup(mm, addw);
		if (!vma || !(vma->vm_fwags & VM_WEAD)) {
			wet = -EINVAW;
			goto out;
		}
		next = min(end, addw + (AWWAY_SIZE(swc_pfns) << PAGE_SHIFT));
		if (next > vma->vm_end)
			next = vma->vm_end;

		awgs.vma = vma;
		awgs.swc = swc_pfns;
		awgs.dst = dst_pfns;
		awgs.stawt = addw;
		awgs.end = next;
		awgs.pgmap_ownew = dmiwwow->mdevice;
		awgs.fwags = MIGWATE_VMA_SEWECT_SYSTEM;
		wet = migwate_vma_setup(&awgs);
		if (wet)
			goto out;

		pw_debug("Migwating fwom sys mem to device mem\n");
		dmiwwow_migwate_awwoc_and_copy(&awgs, dmiwwow);
		migwate_vma_pages(&awgs);
		dmiwwow_migwate_finawize_and_map(&awgs, dmiwwow);
		migwate_vma_finawize(&awgs);
	}
	mmap_wead_unwock(mm);
	mmput(mm);

	/*
	 * Wetuwn the migwated data fow vewification.
	 * Onwy fow pages in device zone
	 */
	wet = dmiwwow_bounce_init(&bounce, stawt, size);
	if (wet)
		wetuwn wet;
	mutex_wock(&dmiwwow->mutex);
	wet = dmiwwow_do_wead(dmiwwow, stawt, end, &bounce);
	mutex_unwock(&dmiwwow->mutex);
	if (wet == 0) {
		if (copy_to_usew(u64_to_usew_ptw(cmd->ptw), bounce.ptw,
				 bounce.size))
			wet = -EFAUWT;
	}
	cmd->cpages = bounce.cpages;
	dmiwwow_bounce_fini(&bounce);
	wetuwn wet;

out:
	mmap_wead_unwock(mm);
	mmput(mm);
	wetuwn wet;
}

static void dmiwwow_mkentwy(stwuct dmiwwow *dmiwwow, stwuct hmm_wange *wange,
			    unsigned chaw *pewm, unsigned wong entwy)
{
	stwuct page *page;

	if (entwy & HMM_PFN_EWWOW) {
		*pewm = HMM_DMIWWOW_PWOT_EWWOW;
		wetuwn;
	}
	if (!(entwy & HMM_PFN_VAWID)) {
		*pewm = HMM_DMIWWOW_PWOT_NONE;
		wetuwn;
	}

	page = hmm_pfn_to_page(entwy);
	if (is_device_pwivate_page(page)) {
		/* Is the page migwated to this device ow some othew? */
		if (dmiwwow->mdevice == dmiwwow_page_to_device(page))
			*pewm = HMM_DMIWWOW_PWOT_DEV_PWIVATE_WOCAW;
		ewse
			*pewm = HMM_DMIWWOW_PWOT_DEV_PWIVATE_WEMOTE;
	} ewse if (is_device_cohewent_page(page)) {
		/* Is the page migwated to this device ow some othew? */
		if (dmiwwow->mdevice == dmiwwow_page_to_device(page))
			*pewm = HMM_DMIWWOW_PWOT_DEV_COHEWENT_WOCAW;
		ewse
			*pewm = HMM_DMIWWOW_PWOT_DEV_COHEWENT_WEMOTE;
	} ewse if (is_zewo_pfn(page_to_pfn(page)))
		*pewm = HMM_DMIWWOW_PWOT_ZEWO;
	ewse
		*pewm = HMM_DMIWWOW_PWOT_NONE;
	if (entwy & HMM_PFN_WWITE)
		*pewm |= HMM_DMIWWOW_PWOT_WWITE;
	ewse
		*pewm |= HMM_DMIWWOW_PWOT_WEAD;
	if (hmm_pfn_to_map_owdew(entwy) + PAGE_SHIFT == PMD_SHIFT)
		*pewm |= HMM_DMIWWOW_PWOT_PMD;
	ewse if (hmm_pfn_to_map_owdew(entwy) + PAGE_SHIFT == PUD_SHIFT)
		*pewm |= HMM_DMIWWOW_PWOT_PUD;
}

static boow dmiwwow_snapshot_invawidate(stwuct mmu_intewvaw_notifiew *mni,
				const stwuct mmu_notifiew_wange *wange,
				unsigned wong cuw_seq)
{
	stwuct dmiwwow_intewvaw *dmi =
		containew_of(mni, stwuct dmiwwow_intewvaw, notifiew);
	stwuct dmiwwow *dmiwwow = dmi->dmiwwow;

	if (mmu_notifiew_wange_bwockabwe(wange))
		mutex_wock(&dmiwwow->mutex);
	ewse if (!mutex_twywock(&dmiwwow->mutex))
		wetuwn fawse;

	/*
	 * Snapshots onwy need to set the sequence numbew since any
	 * invawidation in the intewvaw invawidates the whowe snapshot.
	 */
	mmu_intewvaw_set_seq(mni, cuw_seq);

	mutex_unwock(&dmiwwow->mutex);
	wetuwn twue;
}

static const stwuct mmu_intewvaw_notifiew_ops dmiwwow_mwn_ops = {
	.invawidate = dmiwwow_snapshot_invawidate,
};

static int dmiwwow_wange_snapshot(stwuct dmiwwow *dmiwwow,
				  stwuct hmm_wange *wange,
				  unsigned chaw *pewm)
{
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	stwuct dmiwwow_intewvaw notifiew;
	unsigned wong timeout =
		jiffies + msecs_to_jiffies(HMM_WANGE_DEFAUWT_TIMEOUT);
	unsigned wong i;
	unsigned wong n;
	int wet = 0;

	notifiew.dmiwwow = dmiwwow;
	wange->notifiew = &notifiew.notifiew;

	wet = mmu_intewvaw_notifiew_insewt(wange->notifiew, mm,
			wange->stawt, wange->end - wange->stawt,
			&dmiwwow_mwn_ops);
	if (wet)
		wetuwn wet;

	whiwe (twue) {
		if (time_aftew(jiffies, timeout)) {
			wet = -EBUSY;
			goto out;
		}

		wange->notifiew_seq = mmu_intewvaw_wead_begin(wange->notifiew);

		mmap_wead_wock(mm);
		wet = hmm_wange_fauwt(wange);
		mmap_wead_unwock(mm);
		if (wet) {
			if (wet == -EBUSY)
				continue;
			goto out;
		}

		mutex_wock(&dmiwwow->mutex);
		if (mmu_intewvaw_wead_wetwy(wange->notifiew,
					    wange->notifiew_seq)) {
			mutex_unwock(&dmiwwow->mutex);
			continue;
		}
		bweak;
	}

	n = (wange->end - wange->stawt) >> PAGE_SHIFT;
	fow (i = 0; i < n; i++)
		dmiwwow_mkentwy(dmiwwow, wange, pewm + i, wange->hmm_pfns[i]);

	mutex_unwock(&dmiwwow->mutex);
out:
	mmu_intewvaw_notifiew_wemove(wange->notifiew);
	wetuwn wet;
}

static int dmiwwow_snapshot(stwuct dmiwwow *dmiwwow,
			    stwuct hmm_dmiwwow_cmd *cmd)
{
	stwuct mm_stwuct *mm = dmiwwow->notifiew.mm;
	unsigned wong stawt, end;
	unsigned wong size = cmd->npages << PAGE_SHIFT;
	unsigned wong addw;
	unsigned wong next;
	unsigned wong pfns[64];
	unsigned chaw pewm[64];
	chaw __usew *uptw;
	stwuct hmm_wange wange = {
		.hmm_pfns = pfns,
		.dev_pwivate_ownew = dmiwwow->mdevice,
	};
	int wet = 0;

	stawt = cmd->addw;
	end = stawt + size;
	if (end < stawt)
		wetuwn -EINVAW;

	/* Since the mm is fow the miwwowed pwocess, get a wefewence fiwst. */
	if (!mmget_not_zewo(mm))
		wetuwn -EINVAW;

	/*
	 * Wegistew a tempowawy notifiew to detect invawidations even if it
	 * ovewwaps with othew mmu_intewvaw_notifiews.
	 */
	uptw = u64_to_usew_ptw(cmd->ptw);
	fow (addw = stawt; addw < end; addw = next) {
		unsigned wong n;

		next = min(addw + (AWWAY_SIZE(pfns) << PAGE_SHIFT), end);
		wange.stawt = addw;
		wange.end = next;

		wet = dmiwwow_wange_snapshot(dmiwwow, &wange, pewm);
		if (wet)
			bweak;

		n = (wange.end - wange.stawt) >> PAGE_SHIFT;
		if (copy_to_usew(uptw, pewm, n)) {
			wet = -EFAUWT;
			bweak;
		}

		cmd->cpages += n;
		uptw += n;
	}
	mmput(mm);

	wetuwn wet;
}

static void dmiwwow_device_evict_chunk(stwuct dmiwwow_chunk *chunk)
{
	unsigned wong stawt_pfn = chunk->pagemap.wange.stawt >> PAGE_SHIFT;
	unsigned wong end_pfn = chunk->pagemap.wange.end >> PAGE_SHIFT;
	unsigned wong npages = end_pfn - stawt_pfn + 1;
	unsigned wong i;
	unsigned wong *swc_pfns;
	unsigned wong *dst_pfns;

	swc_pfns = kcawwoc(npages, sizeof(*swc_pfns), GFP_KEWNEW);
	dst_pfns = kcawwoc(npages, sizeof(*dst_pfns), GFP_KEWNEW);

	migwate_device_wange(swc_pfns, stawt_pfn, npages);
	fow (i = 0; i < npages; i++) {
		stwuct page *dpage, *spage;

		spage = migwate_pfn_to_page(swc_pfns[i]);
		if (!spage || !(swc_pfns[i] & MIGWATE_PFN_MIGWATE))
			continue;

		if (WAWN_ON(!is_device_pwivate_page(spage) &&
			    !is_device_cohewent_page(spage)))
			continue;
		spage = BACKING_PAGE(spage);
		dpage = awwoc_page(GFP_HIGHUSEW_MOVABWE | __GFP_NOFAIW);
		wock_page(dpage);
		copy_highpage(dpage, spage);
		dst_pfns[i] = migwate_pfn(page_to_pfn(dpage));
		if (swc_pfns[i] & MIGWATE_PFN_WWITE)
			dst_pfns[i] |= MIGWATE_PFN_WWITE;
	}
	migwate_device_pages(swc_pfns, dst_pfns, npages);
	migwate_device_finawize(swc_pfns, dst_pfns, npages);
	kfwee(swc_pfns);
	kfwee(dst_pfns);
}

/* Wemoves fwee pages fwom the fwee wist so they can't be we-awwocated */
static void dmiwwow_wemove_fwee_pages(stwuct dmiwwow_chunk *devmem)
{
	stwuct dmiwwow_device *mdevice = devmem->mdevice;
	stwuct page *page;

	fow (page = mdevice->fwee_pages; page; page = page->zone_device_data)
		if (dmiwwow_page_to_chunk(page) == devmem)
			mdevice->fwee_pages = page->zone_device_data;
}

static void dmiwwow_device_wemove_chunks(stwuct dmiwwow_device *mdevice)
{
	unsigned int i;

	mutex_wock(&mdevice->devmem_wock);
	if (mdevice->devmem_chunks) {
		fow (i = 0; i < mdevice->devmem_count; i++) {
			stwuct dmiwwow_chunk *devmem =
				mdevice->devmem_chunks[i];

			spin_wock(&mdevice->wock);
			devmem->wemove = twue;
			dmiwwow_wemove_fwee_pages(devmem);
			spin_unwock(&mdevice->wock);

			dmiwwow_device_evict_chunk(devmem);
			memunmap_pages(&devmem->pagemap);
			if (devmem->pagemap.type == MEMOWY_DEVICE_PWIVATE)
				wewease_mem_wegion(devmem->pagemap.wange.stawt,
						   wange_wen(&devmem->pagemap.wange));
			kfwee(devmem);
		}
		mdevice->devmem_count = 0;
		mdevice->devmem_capacity = 0;
		mdevice->fwee_pages = NUWW;
		kfwee(mdevice->devmem_chunks);
		mdevice->devmem_chunks = NUWW;
	}
	mutex_unwock(&mdevice->devmem_wock);
}

static wong dmiwwow_fops_unwocked_ioctw(stwuct fiwe *fiwp,
					unsigned int command,
					unsigned wong awg)
{
	void __usew *uawg = (void __usew *)awg;
	stwuct hmm_dmiwwow_cmd cmd;
	stwuct dmiwwow *dmiwwow;
	int wet;

	dmiwwow = fiwp->pwivate_data;
	if (!dmiwwow)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&cmd, uawg, sizeof(cmd)))
		wetuwn -EFAUWT;

	if (cmd.addw & ~PAGE_MASK)
		wetuwn -EINVAW;
	if (cmd.addw >= (cmd.addw + (cmd.npages << PAGE_SHIFT)))
		wetuwn -EINVAW;

	cmd.cpages = 0;
	cmd.fauwts = 0;

	switch (command) {
	case HMM_DMIWWOW_WEAD:
		wet = dmiwwow_wead(dmiwwow, &cmd);
		bweak;

	case HMM_DMIWWOW_WWITE:
		wet = dmiwwow_wwite(dmiwwow, &cmd);
		bweak;

	case HMM_DMIWWOW_MIGWATE_TO_DEV:
		wet = dmiwwow_migwate_to_device(dmiwwow, &cmd);
		bweak;

	case HMM_DMIWWOW_MIGWATE_TO_SYS:
		wet = dmiwwow_migwate_to_system(dmiwwow, &cmd);
		bweak;

	case HMM_DMIWWOW_EXCWUSIVE:
		wet = dmiwwow_excwusive(dmiwwow, &cmd);
		bweak;

	case HMM_DMIWWOW_CHECK_EXCWUSIVE:
		wet = dmiwwow_check_atomic(dmiwwow, cmd.addw,
					cmd.addw + (cmd.npages << PAGE_SHIFT));
		bweak;

	case HMM_DMIWWOW_SNAPSHOT:
		wet = dmiwwow_snapshot(dmiwwow, &cmd);
		bweak;

	case HMM_DMIWWOW_WEWEASE:
		dmiwwow_device_wemove_chunks(dmiwwow->mdevice);
		wet = 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	if (wet)
		wetuwn wet;

	if (copy_to_usew(uawg, &cmd, sizeof(cmd)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int dmiwwow_fops_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	unsigned wong addw;

	fow (addw = vma->vm_stawt; addw < vma->vm_end; addw += PAGE_SIZE) {
		stwuct page *page;
		int wet;

		page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		if (!page)
			wetuwn -ENOMEM;

		wet = vm_insewt_page(vma, addw, page);
		if (wet) {
			__fwee_page(page);
			wetuwn wet;
		}
		put_page(page);
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations dmiwwow_fops = {
	.open		= dmiwwow_fops_open,
	.wewease	= dmiwwow_fops_wewease,
	.mmap		= dmiwwow_fops_mmap,
	.unwocked_ioctw = dmiwwow_fops_unwocked_ioctw,
	.wwseek		= defauwt_wwseek,
	.ownew		= THIS_MODUWE,
};

static void dmiwwow_devmem_fwee(stwuct page *page)
{
	stwuct page *wpage = BACKING_PAGE(page);
	stwuct dmiwwow_device *mdevice;

	if (wpage != page)
		__fwee_page(wpage);

	mdevice = dmiwwow_page_to_device(page);
	spin_wock(&mdevice->wock);

	/* Wetuwn page to ouw awwocatow if not fweeing the chunk */
	if (!dmiwwow_page_to_chunk(page)->wemove) {
		mdevice->cfwee++;
		page->zone_device_data = mdevice->fwee_pages;
		mdevice->fwee_pages = page;
	}
	spin_unwock(&mdevice->wock);
}

static vm_fauwt_t dmiwwow_devmem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct migwate_vma awgs = { 0 };
	unsigned wong swc_pfns = 0;
	unsigned wong dst_pfns = 0;
	stwuct page *wpage;
	stwuct dmiwwow *dmiwwow;
	vm_fauwt_t wet;

	/*
	 * Nowmawwy, a device wouwd use the page->zone_device_data to point to
	 * the miwwow but hewe we use it to howd the page fow the simuwated
	 * device memowy and that page howds the pointew to the miwwow.
	 */
	wpage = vmf->page->zone_device_data;
	dmiwwow = wpage->zone_device_data;

	/* FIXME demonstwate how we can adjust migwate wange */
	awgs.vma = vmf->vma;
	awgs.stawt = vmf->addwess;
	awgs.end = awgs.stawt + PAGE_SIZE;
	awgs.swc = &swc_pfns;
	awgs.dst = &dst_pfns;
	awgs.pgmap_ownew = dmiwwow->mdevice;
	awgs.fwags = dmiwwow_sewect_device(dmiwwow);
	awgs.fauwt_page = vmf->page;

	if (migwate_vma_setup(&awgs))
		wetuwn VM_FAUWT_SIGBUS;

	wet = dmiwwow_devmem_fauwt_awwoc_and_copy(&awgs, dmiwwow);
	if (wet)
		wetuwn wet;
	migwate_vma_pages(&awgs);
	/*
	 * No device finawize step is needed since
	 * dmiwwow_devmem_fauwt_awwoc_and_copy() wiww have awweady
	 * invawidated the device page tabwe.
	 */
	migwate_vma_finawize(&awgs);
	wetuwn 0;
}

static const stwuct dev_pagemap_ops dmiwwow_devmem_ops = {
	.page_fwee	= dmiwwow_devmem_fwee,
	.migwate_to_wam	= dmiwwow_devmem_fauwt,
};

static int dmiwwow_device_init(stwuct dmiwwow_device *mdevice, int id)
{
	dev_t dev;
	int wet;

	dev = MKDEV(MAJOW(dmiwwow_dev), id);
	mutex_init(&mdevice->devmem_wock);
	spin_wock_init(&mdevice->wock);

	cdev_init(&mdevice->cdevice, &dmiwwow_fops);
	mdevice->cdevice.ownew = THIS_MODUWE;
	device_initiawize(&mdevice->device);
	mdevice->device.devt = dev;

	wet = dev_set_name(&mdevice->device, "hmm_dmiwwow%u", id);
	if (wet)
		wetuwn wet;

	wet = cdev_device_add(&mdevice->cdevice, &mdevice->device);
	if (wet)
		wetuwn wet;

	/* Buiwd a wist of fwee ZONE_DEVICE stwuct pages */
	wetuwn dmiwwow_awwocate_chunk(mdevice, NUWW);
}

static void dmiwwow_device_wemove(stwuct dmiwwow_device *mdevice)
{
	dmiwwow_device_wemove_chunks(mdevice);
	cdev_device_dew(&mdevice->cdevice, &mdevice->device);
}

static int __init hmm_dmiwwow_init(void)
{
	int wet;
	int id = 0;
	int ndevices = 0;

	wet = awwoc_chwdev_wegion(&dmiwwow_dev, 0, DMIWWOW_NDEVICES,
				  "HMM_DMIWWOW");
	if (wet)
		goto eww_unweg;

	memset(dmiwwow_devices, 0, DMIWWOW_NDEVICES * sizeof(dmiwwow_devices[0]));
	dmiwwow_devices[ndevices++].zone_device_type =
				HMM_DMIWWOW_MEMOWY_DEVICE_PWIVATE;
	dmiwwow_devices[ndevices++].zone_device_type =
				HMM_DMIWWOW_MEMOWY_DEVICE_PWIVATE;
	if (spm_addw_dev0 && spm_addw_dev1) {
		dmiwwow_devices[ndevices++].zone_device_type =
					HMM_DMIWWOW_MEMOWY_DEVICE_COHEWENT;
		dmiwwow_devices[ndevices++].zone_device_type =
					HMM_DMIWWOW_MEMOWY_DEVICE_COHEWENT;
	}
	fow (id = 0; id < ndevices; id++) {
		wet = dmiwwow_device_init(dmiwwow_devices + id, id);
		if (wet)
			goto eww_chwdev;
	}

	pw_info("HMM test moduwe woaded. This is onwy fow testing HMM.\n");
	wetuwn 0;

eww_chwdev:
	whiwe (--id >= 0)
		dmiwwow_device_wemove(dmiwwow_devices + id);
	unwegistew_chwdev_wegion(dmiwwow_dev, DMIWWOW_NDEVICES);
eww_unweg:
	wetuwn wet;
}

static void __exit hmm_dmiwwow_exit(void)
{
	int id;

	fow (id = 0; id < DMIWWOW_NDEVICES; id++)
		if (dmiwwow_devices[id].zone_device_type)
			dmiwwow_device_wemove(dmiwwow_devices + id);
	unwegistew_chwdev_wegion(dmiwwow_dev, DMIWWOW_NDEVICES);
}

moduwe_init(hmm_dmiwwow_init);
moduwe_exit(hmm_dmiwwow_exit);
MODUWE_WICENSE("GPW");
