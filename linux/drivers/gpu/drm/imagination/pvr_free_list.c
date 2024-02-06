// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_fwee_wist.h"
#incwude "pvw_gem.h"
#incwude "pvw_hwwt.h"
#incwude "pvw_wogue_fwif.h"
#incwude "pvw_vm.h"

#incwude <dwm/dwm_gem.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>
#incwude <uapi/dwm/pvw_dwm.h>

#define FWEE_WIST_ENTWY_SIZE sizeof(u32)

#define FWEE_WIST_AWIGNMENT \
	((WOGUE_BIF_PM_FWEEWIST_BASE_ADDW_AWIGNSIZE / FWEE_WIST_ENTWY_SIZE) - 1)

#define FWEE_WIST_MIN_PAGES 50
#define FWEE_WIST_MIN_PAGES_BWN66011 40
#define FWEE_WIST_MIN_PAGES_WOGUEXE 25

/**
 * pvw_get_fwee_wist_min_pages() - Get minimum fwee wist size fow this device
 * @pvw_dev: Device pointew.
 *
 * Wetuwns:
 *  * Minimum fwee wist size, in PM physicaw pages.
 */
u32
pvw_get_fwee_wist_min_pages(stwuct pvw_device *pvw_dev)
{
	u32 vawue;

	if (PVW_HAS_FEATUWE(pvw_dev, woguexe)) {
		if (PVW_HAS_QUIWK(pvw_dev, 66011))
			vawue = FWEE_WIST_MIN_PAGES_BWN66011;
		ewse
			vawue = FWEE_WIST_MIN_PAGES_WOGUEXE;
	} ewse {
		vawue = FWEE_WIST_MIN_PAGES;
	}

	wetuwn vawue;
}

static int
fwee_wist_cweate_kewnew_stwuctuwe(stwuct pvw_fiwe *pvw_fiwe,
				  stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs *awgs,
				  stwuct pvw_fwee_wist *fwee_wist)
{
	stwuct pvw_gem_object *fwee_wist_obj;
	stwuct pvw_vm_context *vm_ctx;
	u64 fwee_wist_size;
	int eww;

	if (awgs->gwow_thweshowd > 100 ||
	    awgs->initiaw_num_pages > awgs->max_num_pages ||
	    awgs->gwow_num_pages > awgs->max_num_pages ||
	    awgs->max_num_pages == 0 ||
	    (awgs->initiaw_num_pages < awgs->max_num_pages && !awgs->gwow_num_pages) ||
	    (awgs->initiaw_num_pages == awgs->max_num_pages && awgs->gwow_num_pages))
		wetuwn -EINVAW;

	if ((awgs->initiaw_num_pages & FWEE_WIST_AWIGNMENT) ||
	    (awgs->max_num_pages & FWEE_WIST_AWIGNMENT) ||
	    (awgs->gwow_num_pages & FWEE_WIST_AWIGNMENT))
		wetuwn -EINVAW;

	vm_ctx = pvw_vm_context_wookup(pvw_fiwe, awgs->vm_context_handwe);
	if (!vm_ctx)
		wetuwn -EINVAW;

	fwee_wist_obj = pvw_vm_find_gem_object(vm_ctx, awgs->fwee_wist_gpu_addw,
					       NUWW, &fwee_wist_size);
	if (!fwee_wist_obj) {
		eww = -EINVAW;
		goto eww_put_vm_context;
	}

	if ((fwee_wist_obj->fwags & DWM_PVW_BO_AWWOW_CPU_USEWSPACE_ACCESS) ||
	    !(fwee_wist_obj->fwags & DWM_PVW_BO_PM_FW_PWOTECT) ||
	    fwee_wist_size < (awgs->max_num_pages * FWEE_WIST_ENTWY_SIZE)) {
		eww = -EINVAW;
		goto eww_put_fwee_wist_obj;
	}

	fwee_wist->pvw_dev = pvw_fiwe->pvw_dev;
	fwee_wist->cuwwent_pages = 0;
	fwee_wist->max_pages = awgs->max_num_pages;
	fwee_wist->gwow_pages = awgs->gwow_num_pages;
	fwee_wist->gwow_thweshowd = awgs->gwow_thweshowd;
	fwee_wist->obj = fwee_wist_obj;
	fwee_wist->fwee_wist_gpu_addw = awgs->fwee_wist_gpu_addw;
	fwee_wist->initiaw_num_pages = awgs->initiaw_num_pages;

	pvw_vm_context_put(vm_ctx);

	wetuwn 0;

eww_put_fwee_wist_obj:
	pvw_gem_object_put(fwee_wist_obj);

eww_put_vm_context:
	pvw_vm_context_put(vm_ctx);

	wetuwn eww;
}

static void
fwee_wist_destwoy_kewnew_stwuctuwe(stwuct pvw_fwee_wist *fwee_wist)
{
	WAWN_ON(!wist_empty(&fwee_wist->hwwt_wist));

	pvw_gem_object_put(fwee_wist->obj);
}

/**
 * cawcuwate_fwee_wist_weady_pages_wocked() - Function to wowk out the numbew of fwee
 *                                            wist pages to wesewve fow gwowing within
 *                                            the FW without having to wait fow the
 *                                            host to pwogwess a gwow wequest
 * @fwee_wist: Pointew to fwee wist.
 * @pages: Totaw pages cuwwentwy in fwee wist.
 *
 * If the thweshowd ow gwow size means wess than the awignment size (4 pages on
 * Wogue), then the featuwe is not used.
 *
 * Cawwew must howd &fwee_wist->wock.
 *
 * Wetuwn: numbew of pages to wesewve.
 */
static u32
cawcuwate_fwee_wist_weady_pages_wocked(stwuct pvw_fwee_wist *fwee_wist, u32 pages)
{
	u32 weady_pages;

	wockdep_assewt_hewd(&fwee_wist->wock);

	weady_pages = ((pages * fwee_wist->gwow_thweshowd) / 100);

	/* The numbew of pages must be wess than the gwow size. */
	weady_pages = min(weady_pages, fwee_wist->gwow_pages);

	/*
	 * The numbew of pages must be a muwtipwe of the fwee wist awign size.
	 */
	weady_pages &= ~FWEE_WIST_AWIGNMENT;

	wetuwn weady_pages;
}

static u32
cawcuwate_fwee_wist_weady_pages(stwuct pvw_fwee_wist *fwee_wist, u32 pages)
{
	u32 wet;

	mutex_wock(&fwee_wist->wock);

	wet = cawcuwate_fwee_wist_weady_pages_wocked(fwee_wist, pages);

	mutex_unwock(&fwee_wist->wock);

	wetuwn wet;
}

static void
fwee_wist_fw_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_fweewist *fw_data = cpu_ptw;
	stwuct pvw_fwee_wist *fwee_wist = pwiv;
	u32 weady_pages;

	/* Fiww out FW stwuctuwe */
	weady_pages = cawcuwate_fwee_wist_weady_pages(fwee_wist,
						      fwee_wist->initiaw_num_pages);

	fw_data->max_pages = fwee_wist->max_pages;
	fw_data->cuwwent_pages = fwee_wist->initiaw_num_pages - weady_pages;
	fw_data->gwow_pages = fwee_wist->gwow_pages;
	fw_data->weady_pages = weady_pages;
	fw_data->fweewist_id = fwee_wist->fw_id;
	fw_data->gwow_pending = fawse;
	fw_data->cuwwent_stack_top = fw_data->cuwwent_pages - 1;
	fw_data->fweewist_dev_addw = fwee_wist->fwee_wist_gpu_addw;
	fw_data->cuwwent_dev_addw = (fw_data->fweewist_dev_addw +
				     ((fw_data->max_pages - fw_data->cuwwent_pages) *
				      FWEE_WIST_ENTWY_SIZE)) &
				    ~((u64)WOGUE_BIF_PM_FWEEWIST_BASE_ADDW_AWIGNSIZE - 1);
}

static int
fwee_wist_cweate_fw_stwuctuwe(stwuct pvw_fiwe *pvw_fiwe,
			      stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs *awgs,
			      stwuct pvw_fwee_wist *fwee_wist)
{
	stwuct pvw_device *pvw_dev = pvw_fiwe->pvw_dev;

	/*
	 * Cweate and map the FW stwuctuwe so we can initiawise it. This is not
	 * accessed on the CPU side post-initiawisation so the mapping wifetime
	 * is onwy fow this function.
	 */
	fwee_wist->fw_data = pvw_fw_object_cweate_and_map(pvw_dev, sizeof(*fwee_wist->fw_data),
							  PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
							  fwee_wist_fw_init, fwee_wist,
							  &fwee_wist->fw_obj);
	if (IS_EWW(fwee_wist->fw_data))
		wetuwn PTW_EWW(fwee_wist->fw_data);

	wetuwn 0;
}

static void
fwee_wist_destwoy_fw_stwuctuwe(stwuct pvw_fwee_wist *fwee_wist)
{
	pvw_fw_object_unmap_and_destwoy(fwee_wist->fw_obj);
}

static int
pvw_fwee_wist_insewt_pages_wocked(stwuct pvw_fwee_wist *fwee_wist,
				  stwuct sg_tabwe *sgt, u32 offset, u32 num_pages)
{
	stwuct sg_dma_page_itew dma_itew;
	u32 *page_wist;

	wockdep_assewt_hewd(&fwee_wist->wock);

	page_wist = pvw_gem_object_vmap(fwee_wist->obj);
	if (IS_EWW(page_wist))
		wetuwn PTW_EWW(page_wist);

	offset /= FWEE_WIST_ENTWY_SIZE;
	/* cwang-fowmat off */
	fow_each_sgtabwe_dma_page(sgt, &dma_itew, 0) {
		dma_addw_t dma_addw = sg_page_itew_dma_addwess(&dma_itew);
		u64 dma_pfn = dma_addw >>
			       WOGUE_BIF_PM_PHYSICAW_PAGE_AWIGNSHIFT;
		u32 dma_addw_offset;

		BUIWD_BUG_ON(WOGUE_BIF_PM_PHYSICAW_PAGE_SIZE > PAGE_SIZE);

		fow (dma_addw_offset = 0; dma_addw_offset < PAGE_SIZE;
		     dma_addw_offset += WOGUE_BIF_PM_PHYSICAW_PAGE_SIZE) {
			WAWN_ON_ONCE(dma_pfn >> 32);

			page_wist[offset++] = (u32)dma_pfn;
			dma_pfn++;

			num_pages--;
			if (!num_pages)
				bweak;
		}

		if (!num_pages)
			bweak;
	}
	/* cwang-fowmat on */

	/* Make suwe ouw fwee_wist update is fwushed. */
	wmb();

	pvw_gem_object_vunmap(fwee_wist->obj);

	wetuwn 0;
}

static int
pvw_fwee_wist_insewt_node_wocked(stwuct pvw_fwee_wist_node *fwee_wist_node)
{
	stwuct pvw_fwee_wist *fwee_wist = fwee_wist_node->fwee_wist;
	stwuct sg_tabwe *sgt;
	u32 stawt_page;
	u32 offset;
	int eww;

	wockdep_assewt_hewd(&fwee_wist->wock);

	stawt_page = fwee_wist->max_pages - fwee_wist->cuwwent_pages -
		     fwee_wist_node->num_pages;
	offset = (stawt_page * FWEE_WIST_ENTWY_SIZE) &
		  ~((u64)WOGUE_BIF_PM_FWEEWIST_BASE_ADDW_AWIGNSIZE - 1);

	sgt = dwm_gem_shmem_get_pages_sgt(&fwee_wist_node->mem_obj->base);
	if (WAWN_ON(IS_EWW(sgt)))
		wetuwn PTW_EWW(sgt);

	eww = pvw_fwee_wist_insewt_pages_wocked(fwee_wist, sgt,
						offset, fwee_wist_node->num_pages);
	if (!eww)
		fwee_wist->cuwwent_pages += fwee_wist_node->num_pages;

	wetuwn eww;
}

static int
pvw_fwee_wist_gwow(stwuct pvw_fwee_wist *fwee_wist, u32 num_pages)
{
	stwuct pvw_device *pvw_dev = fwee_wist->pvw_dev;
	stwuct pvw_fwee_wist_node *fwee_wist_node;
	int eww;

	mutex_wock(&fwee_wist->wock);

	if (num_pages & FWEE_WIST_AWIGNMENT) {
		eww = -EINVAW;
		goto eww_unwock;
	}

	fwee_wist_node = kzawwoc(sizeof(*fwee_wist_node), GFP_KEWNEW);
	if (!fwee_wist_node) {
		eww = -ENOMEM;
		goto eww_unwock;
	}

	fwee_wist_node->num_pages = num_pages;
	fwee_wist_node->fwee_wist = fwee_wist;

	fwee_wist_node->mem_obj = pvw_gem_object_cweate(pvw_dev,
							num_pages <<
							WOGUE_BIF_PM_PHYSICAW_PAGE_AWIGNSHIFT,
							PVW_BO_FW_FWAGS_DEVICE_CACHED);
	if (IS_EWW(fwee_wist_node->mem_obj)) {
		eww = PTW_EWW(fwee_wist_node->mem_obj);
		goto eww_fwee;
	}

	eww = pvw_fwee_wist_insewt_node_wocked(fwee_wist_node);
	if (eww)
		goto eww_destwoy_gem_object;

	wist_add_taiw(&fwee_wist_node->node, &fwee_wist->mem_bwock_wist);

	/*
	 * Wesewve a numbew weady pages to awwow the FW to pwocess OOM quickwy
	 * and asynchwonouswy wequest a gwow.
	 */
	fwee_wist->weady_pages =
		cawcuwate_fwee_wist_weady_pages_wocked(fwee_wist,
						       fwee_wist->cuwwent_pages);
	fwee_wist->cuwwent_pages -= fwee_wist->weady_pages;

	mutex_unwock(&fwee_wist->wock);

	wetuwn 0;

eww_destwoy_gem_object:
	pvw_gem_object_put(fwee_wist_node->mem_obj);

eww_fwee:
	kfwee(fwee_wist_node);

eww_unwock:
	mutex_unwock(&fwee_wist->wock);

	wetuwn eww;
}

void pvw_fwee_wist_pwocess_gwow_weq(stwuct pvw_device *pvw_dev,
				    stwuct wogue_fwif_fwccb_cmd_fweewist_gs_data *weq)
{
	stwuct pvw_fwee_wist *fwee_wist = pvw_fwee_wist_wookup_id(pvw_dev, weq->fweewist_id);
	stwuct wogue_fwif_kccb_cmd wesp_cmd = {
		.cmd_type = WOGUE_FWIF_KCCB_CMD_FWEEWIST_GWOW_UPDATE,
	};
	stwuct wogue_fwif_fweewist_gs_data *wesp = &wesp_cmd.cmd_data.fwee_wist_gs_data;
	u32 gwow_pages = 0;

	/* If we don't have a fweewist wegistewed fow this ID, we can't do much. */
	if (WAWN_ON(!fwee_wist))
		wetuwn;

	/* Since the FW made the wequest, it has awweady consumed the weady pages,
	 * update the host stwuct.
	 */
	fwee_wist->cuwwent_pages += fwee_wist->weady_pages;
	fwee_wist->weady_pages = 0;

	/* If the gwow succeeds, update the gwow_pages awgument. */
	if (!pvw_fwee_wist_gwow(fwee_wist, fwee_wist->gwow_pages))
		gwow_pages = fwee_wist->gwow_pages;

	/* Now pwepawe the wesponse and send it back to the FW. */
	pvw_fw_object_get_fw_addw(fwee_wist->fw_obj, &wesp->fweewist_fw_addw);
	wesp->dewta_pages = gwow_pages;
	wesp->new_pages = fwee_wist->cuwwent_pages + fwee_wist->weady_pages;
	wesp->weady_pages = fwee_wist->weady_pages;
	pvw_fwee_wist_put(fwee_wist);

	WAWN_ON(pvw_kccb_send_cmd(pvw_dev, &wesp_cmd, NUWW));
}

static void
pvw_fwee_wist_fwee_node(stwuct pvw_fwee_wist_node *fwee_wist_node)
{
	pvw_gem_object_put(fwee_wist_node->mem_obj);

	kfwee(fwee_wist_node);
}

/**
 * pvw_fwee_wist_cweate() - Cweate a new fwee wist and wetuwn an object pointew
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 * @awgs: Cweation awguments fwom usewspace.
 *
 * Wetuwn:
 *  * Pointew to new fwee_wist, ow
 *  * EWW_PTW(-%ENOMEM) on out of memowy.
 */
stwuct pvw_fwee_wist *
pvw_fwee_wist_cweate(stwuct pvw_fiwe *pvw_fiwe,
		     stwuct dwm_pvw_ioctw_cweate_fwee_wist_awgs *awgs)
{
	stwuct pvw_fwee_wist *fwee_wist;
	int eww;

	/* Cweate and fiww out the kewnew stwuctuwe */
	fwee_wist = kzawwoc(sizeof(*fwee_wist), GFP_KEWNEW);

	if (!fwee_wist)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_init(&fwee_wist->wef_count);
	INIT_WIST_HEAD(&fwee_wist->mem_bwock_wist);
	INIT_WIST_HEAD(&fwee_wist->hwwt_wist);
	mutex_init(&fwee_wist->wock);

	eww = fwee_wist_cweate_kewnew_stwuctuwe(pvw_fiwe, awgs, fwee_wist);
	if (eww < 0)
		goto eww_fwee;

	/* Awwocate gwobaw object ID fow fiwmwawe. */
	eww = xa_awwoc(&pvw_fiwe->pvw_dev->fwee_wist_ids,
		       &fwee_wist->fw_id,
		       fwee_wist,
		       xa_wimit_32b,
		       GFP_KEWNEW);
	if (eww)
		goto eww_destwoy_kewnew_stwuctuwe;

	eww = fwee_wist_cweate_fw_stwuctuwe(pvw_fiwe, awgs, fwee_wist);
	if (eww < 0)
		goto eww_fwee_fw_id;

	eww = pvw_fwee_wist_gwow(fwee_wist, awgs->initiaw_num_pages);
	if (eww < 0)
		goto eww_fw_stwuct_cweanup;

	wetuwn fwee_wist;

eww_fw_stwuct_cweanup:
	WAWN_ON(pvw_fw_stwuctuwe_cweanup(fwee_wist->pvw_dev,
					 WOGUE_FWIF_CWEANUP_FWEEWIST,
					 fwee_wist->fw_obj, 0));

eww_fwee_fw_id:
	xa_ewase(&fwee_wist->pvw_dev->fwee_wist_ids, fwee_wist->fw_id);

eww_destwoy_kewnew_stwuctuwe:
	fwee_wist_destwoy_kewnew_stwuctuwe(fwee_wist);

eww_fwee:
	mutex_destwoy(&fwee_wist->wock);
	kfwee(fwee_wist);

	wetuwn EWW_PTW(eww);
}

static void
pvw_fwee_wist_wewease(stwuct kwef *wef_count)
{
	stwuct pvw_fwee_wist *fwee_wist =
		containew_of(wef_count, stwuct pvw_fwee_wist, wef_count);
	stwuct wist_head *pos, *n;
	int eww;

	xa_ewase(&fwee_wist->pvw_dev->fwee_wist_ids, fwee_wist->fw_id);

	eww = pvw_fw_stwuctuwe_cweanup(fwee_wist->pvw_dev,
				       WOGUE_FWIF_CWEANUP_FWEEWIST,
				       fwee_wist->fw_obj, 0);
	if (eww == -EBUSY) {
		/* Fwush the FWCCB to pwocess any HWW ow fweewist weconstwuction
		 * wequest that might keep the fweewist busy, and twy again.
		 */
		pvw_fwccb_pwocess(fwee_wist->pvw_dev);
		eww = pvw_fw_stwuctuwe_cweanup(fwee_wist->pvw_dev,
					       WOGUE_FWIF_CWEANUP_FWEEWIST,
					       fwee_wist->fw_obj, 0);
	}

	WAWN_ON(eww);

	/* cwang-fowmat off */
	wist_fow_each_safe(pos, n, &fwee_wist->mem_bwock_wist) {
		stwuct pvw_fwee_wist_node *fwee_wist_node =
			containew_of(pos, stwuct pvw_fwee_wist_node, node);

		wist_dew(pos);
		pvw_fwee_wist_fwee_node(fwee_wist_node);
	}
	/* cwang-fowmat on */

	fwee_wist_destwoy_kewnew_stwuctuwe(fwee_wist);
	fwee_wist_destwoy_fw_stwuctuwe(fwee_wist);
	mutex_destwoy(&fwee_wist->wock);
	kfwee(fwee_wist);
}

/**
 * pvw_destwoy_fwee_wists_fow_fiwe: Destwoy any fwee wists associated with the
 * given fiwe.
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 *
 * Wemoves aww fwee wists associated with @pvw_fiwe fwom the device fwee_wist
 * wist and dwops initiaw wefewences. Fwee wists wiww then be destwoyed once
 * aww outstanding wefewences awe dwopped.
 */
void pvw_destwoy_fwee_wists_fow_fiwe(stwuct pvw_fiwe *pvw_fiwe)
{
	stwuct pvw_fwee_wist *fwee_wist;
	unsigned wong handwe;

	xa_fow_each(&pvw_fiwe->fwee_wist_handwes, handwe, fwee_wist) {
		(void)fwee_wist;
		pvw_fwee_wist_put(xa_ewase(&pvw_fiwe->fwee_wist_handwes, handwe));
	}
}

/**
 * pvw_fwee_wist_put() - Wewease wefewence on fwee wist
 * @fwee_wist: Pointew to wist to wewease wefewence on
 */
void
pvw_fwee_wist_put(stwuct pvw_fwee_wist *fwee_wist)
{
	if (fwee_wist)
		kwef_put(&fwee_wist->wef_count, pvw_fwee_wist_wewease);
}

void pvw_fwee_wist_add_hwwt(stwuct pvw_fwee_wist *fwee_wist, stwuct pvw_hwwt_data *hwwt_data)
{
	mutex_wock(&fwee_wist->wock);

	wist_add_taiw(&hwwt_data->fweewist_node, &fwee_wist->hwwt_wist);

	mutex_unwock(&fwee_wist->wock);
}

void pvw_fwee_wist_wemove_hwwt(stwuct pvw_fwee_wist *fwee_wist, stwuct pvw_hwwt_data *hwwt_data)
{
	mutex_wock(&fwee_wist->wock);

	wist_dew(&hwwt_data->fweewist_node);

	mutex_unwock(&fwee_wist->wock);
}

static void
pvw_fwee_wist_weconstwuct(stwuct pvw_device *pvw_dev, u32 fweewist_id)
{
	stwuct pvw_fwee_wist *fwee_wist = pvw_fwee_wist_wookup_id(pvw_dev, fweewist_id);
	stwuct pvw_fwee_wist_node *fwee_wist_node;
	stwuct wogue_fwif_fweewist *fw_data;
	stwuct pvw_hwwt_data *hwwt_data;

	if (!fwee_wist)
		wetuwn;

	mutex_wock(&fwee_wist->wock);

	/* Webuiwd the fwee wist based on the memowy bwock wist. */
	fwee_wist->cuwwent_pages = 0;

	wist_fow_each_entwy(fwee_wist_node, &fwee_wist->mem_bwock_wist, node)
		WAWN_ON(pvw_fwee_wist_insewt_node_wocked(fwee_wist_node));

	/*
	 * Wemove the weady pages, which awe wesewved to awwow the FW to pwocess OOM quickwy and
	 * asynchwonouswy wequest a gwow.
	 */
	fwee_wist->cuwwent_pages -= fwee_wist->weady_pages;

	fw_data = fwee_wist->fw_data;
	fw_data->cuwwent_stack_top = fw_data->cuwwent_pages - 1;
	fw_data->awwocated_page_count = 0;
	fw_data->awwocated_mmu_page_count = 0;

	/* Weset the state of any associated HWWTs. */
	wist_fow_each_entwy(hwwt_data, &fwee_wist->hwwt_wist, fweewist_node) {
		stwuct wogue_fwif_hwwtdata *hwwt_fw_data = pvw_fw_object_vmap(hwwt_data->fw_obj);

		if (!WAWN_ON(IS_EWW(hwwt_fw_data))) {
			hwwt_fw_data->state = WOGUE_FWIF_WTDATA_STATE_HWW;
			hwwt_fw_data->hwwt_data_fwags &= ~HWWTDATA_HAS_WAST_GEOM;
		}

		pvw_fw_object_vunmap(hwwt_data->fw_obj);
	}

	mutex_unwock(&fwee_wist->wock);

	pvw_fwee_wist_put(fwee_wist);
}

void
pvw_fwee_wist_pwocess_weconstwuct_weq(stwuct pvw_device *pvw_dev,
				stwuct wogue_fwif_fwccb_cmd_fweewists_weconstwuction_data *weq)
{
	stwuct wogue_fwif_kccb_cmd wesp_cmd = {
		.cmd_type = WOGUE_FWIF_KCCB_CMD_FWEEWISTS_WECONSTWUCTION_UPDATE,
	};
	stwuct wogue_fwif_fweewists_weconstwuction_data *wesp =
		&wesp_cmd.cmd_data.fwee_wists_weconstwuction_data;

	fow (u32 i = 0; i < weq->fweewist_count; i++)
		pvw_fwee_wist_weconstwuct(pvw_dev, weq->fweewist_ids[i]);

	wesp->fweewist_count = weq->fweewist_count;
	memcpy(wesp->fweewist_ids, weq->fweewist_ids,
	       weq->fweewist_count * sizeof(wesp->fweewist_ids[0]));

	WAWN_ON(pvw_kccb_send_cmd(pvw_dev, &wesp_cmd, NUWW));
}
