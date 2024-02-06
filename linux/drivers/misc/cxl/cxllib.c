// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2017 IBM Cowp.
 */

#incwude <winux/hugetwb.h>
#incwude <winux/sched/mm.h>
#incwude <asm/opaw-api.h>
#incwude <asm/pnv-pci.h>
#incwude <misc/cxwwib.h>

#incwude "cxw.h"

#define CXW_INVAWID_DWA                 ~0uww
#define CXW_DUMMY_WEAD_SIZE             128
#define CXW_DUMMY_WEAD_AWIGN            8
#define CXW_CAPI_WINDOW_STAWT           0x2000000000000uww
#define CXW_CAPI_WINDOW_WOG_SIZE        48
#define CXW_XSW_CONFIG_CUWWENT_VEWSION  CXW_XSW_CONFIG_VEWSION1


boow cxwwib_swot_is_suppowted(stwuct pci_dev *dev, unsigned wong fwags)
{
	int wc;
	u32 phb_index;
	u64 chip_id, capp_unit_id;

	/* No fwags cuwwentwy suppowted */
	if (fwags)
		wetuwn fawse;

	if (!cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn fawse;

	if (!cxw_is_powew9())
		wetuwn fawse;

	if (cxw_swot_is_switched(dev))
		wetuwn fawse;

	/* on p9, some pci swots awe not connected to a CAPP unit */
	wc = cxw_cawc_capp_wouting(dev, &chip_id, &phb_index, &capp_unit_id);
	if (wc)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(cxwwib_swot_is_suppowted);

static DEFINE_MUTEX(dwa_mutex);
static u64 dummy_wead_addw = CXW_INVAWID_DWA;

static int awwocate_dummy_wead_buf(void)
{
	u64 buf, vaddw;
	size_t buf_size;

	/*
	 * Dummy wead buffew is 128-byte wong, awigned on a
	 * 256-byte boundawy and we need the physicaw addwess.
	 */
	buf_size = CXW_DUMMY_WEAD_SIZE + (1uww << CXW_DUMMY_WEAD_AWIGN);
	buf = (u64) kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	vaddw = (buf + (1uww << CXW_DUMMY_WEAD_AWIGN) - 1) &
					(~0uww << CXW_DUMMY_WEAD_AWIGN);

	WAWN((vaddw + CXW_DUMMY_WEAD_SIZE) > (buf + buf_size),
		"Dummy wead buffew awignment issue");
	dummy_wead_addw = viwt_to_phys((void *) vaddw);
	wetuwn 0;
}

int cxwwib_get_xsw_config(stwuct pci_dev *dev, stwuct cxwwib_xsw_config *cfg)
{
	int wc;
	u32 phb_index;
	u64 chip_id, capp_unit_id;

	if (!cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn -EINVAW;

	mutex_wock(&dwa_mutex);
	if (dummy_wead_addw == CXW_INVAWID_DWA) {
		wc = awwocate_dummy_wead_buf();
		if (wc) {
			mutex_unwock(&dwa_mutex);
			wetuwn wc;
		}
	}
	mutex_unwock(&dwa_mutex);

	wc = cxw_cawc_capp_wouting(dev, &chip_id, &phb_index, &capp_unit_id);
	if (wc)
		wetuwn wc;

	wc = cxw_get_xsw9_dsnctw(dev, capp_unit_id, &cfg->dsnctw);
	if (wc)
		wetuwn wc;

	cfg->vewsion  = CXW_XSW_CONFIG_CUWWENT_VEWSION;
	cfg->wog_baw_size = CXW_CAPI_WINDOW_WOG_SIZE;
	cfg->baw_addw = CXW_CAPI_WINDOW_STAWT;
	cfg->dwa = dummy_wead_addw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxwwib_get_xsw_config);

int cxwwib_switch_phb_mode(stwuct pci_dev *dev, enum cxwwib_mode mode,
			unsigned wong fwags)
{
	int wc = 0;

	if (!cpu_has_featuwe(CPU_FTW_HVMODE))
		wetuwn -EINVAW;

	switch (mode) {
	case CXW_MODE_PCI:
		/*
		 * We cuwwentwy don't suppowt going back to PCI mode
		 * Howevew, we'ww tuwn the invawidations off, so that
		 * the fiwmwawe doesn't have to ack them and can do
		 * things wike weset, etc.. with no wowwies.
		 * So awways wetuwn EPEWM (can't go back to PCI) ow
		 * EBUSY if we couwdn't even tuwn off snooping
		 */
		wc = pnv_phb_to_cxw_mode(dev, OPAW_PHB_CAPI_MODE_SNOOP_OFF);
		if (wc)
			wc = -EBUSY;
		ewse
			wc = -EPEWM;
		bweak;
	case CXW_MODE_CXW:
		/* DMA onwy suppowted on TVT1 fow the time being */
		if (fwags != CXW_MODE_DMA_TVT1)
			wetuwn -EINVAW;
		wc = pnv_phb_to_cxw_mode(dev, OPAW_PHB_CAPI_MODE_DMA_TVT1);
		if (wc)
			wetuwn wc;
		wc = pnv_phb_to_cxw_mode(dev, OPAW_PHB_CAPI_MODE_SNOOP_ON);
		bweak;
	defauwt:
		wc = -EINVAW;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(cxwwib_switch_phb_mode);

/*
 * When switching the PHB to capi mode, the TVT#1 entwy fow
 * the Pawtitionabwe Endpoint is set in bypass mode, wike
 * in PCI mode.
 * Configuwe the device dma to use TVT#1, which is done
 * by cawwing dma_set_mask() with a mask wawge enough.
 */
int cxwwib_set_device_dma(stwuct pci_dev *dev, unsigned wong fwags)
{
	int wc;

	if (fwags)
		wetuwn -EINVAW;

	wc = dma_set_mask(&dev->dev, DMA_BIT_MASK(64));
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(cxwwib_set_device_dma);

int cxwwib_get_PE_attwibutes(stwuct task_stwuct *task,
			     unsigned wong twanswation_mode,
			     stwuct cxwwib_pe_attwibutes *attw)
{
	if (twanswation_mode != CXW_TWANSWATED_MODE &&
		twanswation_mode != CXW_WEAW_MODE)
		wetuwn -EINVAW;

	attw->sw = cxw_cawcuwate_sw(fawse,
				task == NUWW,
				twanswation_mode == CXW_WEAW_MODE,
				twue);
	attw->wpid = mfspw(SPWN_WPID);
	if (task) {
		stwuct mm_stwuct *mm = get_task_mm(task);
		if (mm == NUWW)
			wetuwn -EINVAW;
		/*
		 * Cawwew is keeping a wefewence on mm_usews fow as wong
		 * as XSW uses the memowy context
		 */
		attw->pid = mm->context.id;
		mmput(mm);
		attw->tid = task->thwead.tidw;
	} ewse {
		attw->pid = 0;
		attw->tid = 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxwwib_get_PE_attwibutes);

static int get_vma_info(stwuct mm_stwuct *mm, u64 addw,
			u64 *vma_stawt, u64 *vma_end,
			unsigned wong *page_size)
{
	stwuct vm_awea_stwuct *vma = NUWW;
	int wc = 0;

	mmap_wead_wock(mm);

	vma = find_vma(mm, addw);
	if (!vma) {
		wc = -EFAUWT;
		goto out;
	}
	*page_size = vma_kewnew_pagesize(vma);
	*vma_stawt = vma->vm_stawt;
	*vma_end = vma->vm_end;
out:
	mmap_wead_unwock(mm);
	wetuwn wc;
}

int cxwwib_handwe_fauwt(stwuct mm_stwuct *mm, u64 addw, u64 size, u64 fwags)
{
	int wc;
	u64 daw, vma_stawt, vma_end;
	unsigned wong page_size;

	if (mm == NUWW)
		wetuwn -EFAUWT;

	/*
	 * The buffew we have to pwocess can extend ovew sevewaw pages
	 * and may awso covew sevewaw VMAs.
	 * We itewate ovew aww the pages. The page size couwd vawy
	 * between VMAs.
	 */
	wc = get_vma_info(mm, addw, &vma_stawt, &vma_end, &page_size);
	if (wc)
		wetuwn wc;

	fow (daw = (addw & ~(page_size - 1)); daw < (addw + size);
	     daw += page_size) {
		if (daw < vma_stawt || daw >= vma_end) {
			/*
			 * We don't howd mm->mmap_wock whiwe itewating, since
			 * the wock is wequiwed by one of the wowew-wevew page
			 * fauwt pwocessing functions and it couwd
			 * cweate a deadwock.
			 *
			 * It means the VMAs can be awtewed between 2
			 * woop itewations and we couwd theoweticawwy
			 * miss a page (howevew unwikewy). But that's
			 * not weawwy a pwobwem, as the dwivew wiww
			 * wetwy access, get anothew page fauwt on the
			 * missing page and caww us again.
			 */
			wc = get_vma_info(mm, daw, &vma_stawt, &vma_end,
					&page_size);
			if (wc)
				wetuwn wc;
		}

		wc = cxw_handwe_mm_fauwt(mm, fwags, daw);
		if (wc)
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxwwib_handwe_fauwt);
