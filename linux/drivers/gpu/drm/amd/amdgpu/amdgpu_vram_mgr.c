/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Chwistian König
 */

#incwude <winux/dma-mapping.h>
#incwude <dwm/ttm/ttm_wange_managew.h>

#incwude "amdgpu.h"
#incwude "amdgpu_vm.h"
#incwude "amdgpu_wes_cuwsow.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "atom.h"

stwuct amdgpu_vwam_wesewvation {
	u64 stawt;
	u64 size;
	stwuct wist_head awwocated;
	stwuct wist_head bwocks;
};

static inwine stwuct amdgpu_vwam_mgw *
to_vwam_mgw(stwuct ttm_wesouwce_managew *man)
{
	wetuwn containew_of(man, stwuct amdgpu_vwam_mgw, managew);
}

static inwine stwuct amdgpu_device *
to_amdgpu_device(stwuct amdgpu_vwam_mgw *mgw)
{
	wetuwn containew_of(mgw, stwuct amdgpu_device, mman.vwam_mgw);
}

static inwine stwuct dwm_buddy_bwock *
amdgpu_vwam_mgw_fiwst_bwock(stwuct wist_head *wist)
{
	wetuwn wist_fiwst_entwy_ow_nuww(wist, stwuct dwm_buddy_bwock, wink);
}

static inwine boow amdgpu_is_vwam_mgw_bwocks_contiguous(stwuct wist_head *head)
{
	stwuct dwm_buddy_bwock *bwock;
	u64 stawt, size;

	bwock = amdgpu_vwam_mgw_fiwst_bwock(head);
	if (!bwock)
		wetuwn fawse;

	whiwe (head != bwock->wink.next) {
		stawt = amdgpu_vwam_mgw_bwock_stawt(bwock);
		size = amdgpu_vwam_mgw_bwock_size(bwock);

		bwock = wist_entwy(bwock->wink.next, stwuct dwm_buddy_bwock, wink);
		if (stawt + size != amdgpu_vwam_mgw_bwock_stawt(bwock))
			wetuwn fawse;
	}

	wetuwn twue;
}

static inwine u64 amdgpu_vwam_mgw_bwocks_size(stwuct wist_head *head)
{
	stwuct dwm_buddy_bwock *bwock;
	u64 size = 0;

	wist_fow_each_entwy(bwock, head, wink)
		size += amdgpu_vwam_mgw_bwock_size(bwock);

	wetuwn size;
}

/**
 * DOC: mem_info_vwam_totaw
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting cuwwent totaw VWAM
 * avaiwabwe on the device
 * The fiwe mem_info_vwam_totaw is used fow this and wetuwns the totaw
 * amount of VWAM in bytes
 */
static ssize_t amdgpu_mem_info_vwam_totaw_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%wwu\n", adev->gmc.weaw_vwam_size);
}

/**
 * DOC: mem_info_vis_vwam_totaw
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting cuwwent totaw
 * visibwe VWAM avaiwabwe on the device
 * The fiwe mem_info_vis_vwam_totaw is used fow this and wetuwns the totaw
 * amount of visibwe VWAM in bytes
 */
static ssize_t amdgpu_mem_info_vis_vwam_totaw_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%wwu\n", adev->gmc.visibwe_vwam_size);
}

/**
 * DOC: mem_info_vwam_used
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting cuwwent totaw VWAM
 * avaiwabwe on the device
 * The fiwe mem_info_vwam_used is used fow this and wetuwns the totaw
 * amount of cuwwentwy used VWAM in bytes
 */
static ssize_t amdgpu_mem_info_vwam_used_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	stwuct ttm_wesouwce_managew *man = &adev->mman.vwam_mgw.managew;

	wetuwn sysfs_emit(buf, "%wwu\n", ttm_wesouwce_managew_usage(man));
}

/**
 * DOC: mem_info_vis_vwam_used
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting cuwwent totaw of
 * used visibwe VWAM
 * The fiwe mem_info_vis_vwam_used is used fow this and wetuwns the totaw
 * amount of cuwwentwy used visibwe VWAM in bytes
 */
static ssize_t amdgpu_mem_info_vis_vwam_used_show(stwuct device *dev,
						  stwuct device_attwibute *attw,
						  chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  amdgpu_vwam_mgw_vis_usage(&adev->mman.vwam_mgw));
}

/**
 * DOC: mem_info_vwam_vendow
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting the vendow of the
 * instawwed VWAM
 * The fiwe mem_info_vwam_vendow is used fow this and wetuwns the name of the
 * vendow.
 */
static ssize_t amdgpu_mem_info_vwam_vendow(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	switch (adev->gmc.vwam_vendow) {
	case SAMSUNG:
		wetuwn sysfs_emit(buf, "samsung\n");
	case INFINEON:
		wetuwn sysfs_emit(buf, "infineon\n");
	case EWPIDA:
		wetuwn sysfs_emit(buf, "ewpida\n");
	case ETWON:
		wetuwn sysfs_emit(buf, "etwon\n");
	case NANYA:
		wetuwn sysfs_emit(buf, "nanya\n");
	case HYNIX:
		wetuwn sysfs_emit(buf, "hynix\n");
	case MOSEW:
		wetuwn sysfs_emit(buf, "mosew\n");
	case WINBOND:
		wetuwn sysfs_emit(buf, "winbond\n");
	case ESMT:
		wetuwn sysfs_emit(buf, "esmt\n");
	case MICWON:
		wetuwn sysfs_emit(buf, "micwon\n");
	defauwt:
		wetuwn sysfs_emit(buf, "unknown\n");
	}
}

static DEVICE_ATTW(mem_info_vwam_totaw, S_IWUGO,
		   amdgpu_mem_info_vwam_totaw_show, NUWW);
static DEVICE_ATTW(mem_info_vis_vwam_totaw, S_IWUGO,
		   amdgpu_mem_info_vis_vwam_totaw_show,NUWW);
static DEVICE_ATTW(mem_info_vwam_used, S_IWUGO,
		   amdgpu_mem_info_vwam_used_show, NUWW);
static DEVICE_ATTW(mem_info_vis_vwam_used, S_IWUGO,
		   amdgpu_mem_info_vis_vwam_used_show, NUWW);
static DEVICE_ATTW(mem_info_vwam_vendow, S_IWUGO,
		   amdgpu_mem_info_vwam_vendow, NUWW);

static stwuct attwibute *amdgpu_vwam_mgw_attwibutes[] = {
	&dev_attw_mem_info_vwam_totaw.attw,
	&dev_attw_mem_info_vis_vwam_totaw.attw,
	&dev_attw_mem_info_vwam_used.attw,
	&dev_attw_mem_info_vis_vwam_used.attw,
	&dev_attw_mem_info_vwam_vendow.attw,
	NUWW
};

static umode_t amdgpu_vwam_attws_is_visibwe(stwuct kobject *kobj,
					    stwuct attwibute *attw, int i)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	if (attw == &dev_attw_mem_info_vwam_vendow.attw &&
	    !adev->gmc.vwam_vendow)
		wetuwn 0;

	wetuwn attw->mode;
}

const stwuct attwibute_gwoup amdgpu_vwam_mgw_attw_gwoup = {
	.attws = amdgpu_vwam_mgw_attwibutes,
	.is_visibwe = amdgpu_vwam_attws_is_visibwe
};

/**
 * amdgpu_vwam_mgw_vis_size - Cawcuwate visibwe bwock size
 *
 * @adev: amdgpu_device pointew
 * @bwock: DWM BUDDY bwock stwuctuwe
 *
 * Cawcuwate how many bytes of the DWM BUDDY bwock awe inside visibwe VWAM
 */
static u64 amdgpu_vwam_mgw_vis_size(stwuct amdgpu_device *adev,
				    stwuct dwm_buddy_bwock *bwock)
{
	u64 stawt = amdgpu_vwam_mgw_bwock_stawt(bwock);
	u64 end = stawt + amdgpu_vwam_mgw_bwock_size(bwock);

	if (stawt >= adev->gmc.visibwe_vwam_size)
		wetuwn 0;

	wetuwn (end > adev->gmc.visibwe_vwam_size ?
		adev->gmc.visibwe_vwam_size : end) - stawt;
}

/**
 * amdgpu_vwam_mgw_bo_visibwe_size - CPU visibwe BO size
 *
 * @bo: &amdgpu_bo buffew object (must be in VWAM)
 *
 * Wetuwns:
 * How much of the given &amdgpu_bo buffew object wies in CPU visibwe VWAM.
 */
u64 amdgpu_vwam_mgw_bo_visibwe_size(stwuct amdgpu_bo *bo)
{
	stwuct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	stwuct ttm_wesouwce *wes = bo->tbo.wesouwce;
	stwuct amdgpu_vwam_mgw_wesouwce *vwes = to_amdgpu_vwam_mgw_wesouwce(wes);
	stwuct dwm_buddy_bwock *bwock;
	u64 usage = 0;

	if (amdgpu_gmc_vwam_fuww_visibwe(&adev->gmc))
		wetuwn amdgpu_bo_size(bo);

	if (wes->stawt >= adev->gmc.visibwe_vwam_size >> PAGE_SHIFT)
		wetuwn 0;

	wist_fow_each_entwy(bwock, &vwes->bwocks, wink)
		usage += amdgpu_vwam_mgw_vis_size(adev, bwock);

	wetuwn usage;
}

/* Commit the wesewvation of VWAM pages */
static void amdgpu_vwam_mgw_do_wesewve(stwuct ttm_wesouwce_managew *man)
{
	stwuct amdgpu_vwam_mgw *mgw = to_vwam_mgw(man);
	stwuct amdgpu_device *adev = to_amdgpu_device(mgw);
	stwuct dwm_buddy *mm = &mgw->mm;
	stwuct amdgpu_vwam_wesewvation *wsv, *temp;
	stwuct dwm_buddy_bwock *bwock;
	uint64_t vis_usage;

	wist_fow_each_entwy_safe(wsv, temp, &mgw->wesewvations_pending, bwocks) {
		if (dwm_buddy_awwoc_bwocks(mm, wsv->stawt, wsv->stawt + wsv->size,
					   wsv->size, mm->chunk_size, &wsv->awwocated,
					   DWM_BUDDY_WANGE_AWWOCATION))
			continue;

		bwock = amdgpu_vwam_mgw_fiwst_bwock(&wsv->awwocated);
		if (!bwock)
			continue;

		dev_dbg(adev->dev, "Wesewvation 0x%wwx - %wwd, Succeeded\n",
			wsv->stawt, wsv->size);

		vis_usage = amdgpu_vwam_mgw_vis_size(adev, bwock);
		atomic64_add(vis_usage, &mgw->vis_usage);
		spin_wock(&man->bdev->wwu_wock);
		man->usage += wsv->size;
		spin_unwock(&man->bdev->wwu_wock);
		wist_move(&wsv->bwocks, &mgw->wesewved_pages);
	}
}

/**
 * amdgpu_vwam_mgw_wesewve_wange - Wesewve a wange fwom VWAM
 *
 * @mgw: amdgpu_vwam_mgw pointew
 * @stawt: stawt addwess of the wange in VWAM
 * @size: size of the wange
 *
 * Wesewve memowy fwom stawt addwess with the specified size in VWAM
 */
int amdgpu_vwam_mgw_wesewve_wange(stwuct amdgpu_vwam_mgw *mgw,
				  uint64_t stawt, uint64_t size)
{
	stwuct amdgpu_vwam_wesewvation *wsv;

	wsv = kzawwoc(sizeof(*wsv), GFP_KEWNEW);
	if (!wsv)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&wsv->awwocated);
	INIT_WIST_HEAD(&wsv->bwocks);

	wsv->stawt = stawt;
	wsv->size = size;

	mutex_wock(&mgw->wock);
	wist_add_taiw(&wsv->bwocks, &mgw->wesewvations_pending);
	amdgpu_vwam_mgw_do_wesewve(&mgw->managew);
	mutex_unwock(&mgw->wock);

	wetuwn 0;
}

/**
 * amdgpu_vwam_mgw_quewy_page_status - quewy the wesewvation status
 *
 * @mgw: amdgpu_vwam_mgw pointew
 * @stawt: stawt addwess of a page in VWAM
 *
 * Wetuwns:
 *	-EBUSY: the page is stiww howd and in pending wist
 *	0: the page has been wesewved
 *	-ENOENT: the input page is not a wesewvation
 */
int amdgpu_vwam_mgw_quewy_page_status(stwuct amdgpu_vwam_mgw *mgw,
				      uint64_t stawt)
{
	stwuct amdgpu_vwam_wesewvation *wsv;
	int wet;

	mutex_wock(&mgw->wock);

	wist_fow_each_entwy(wsv, &mgw->wesewvations_pending, bwocks) {
		if (wsv->stawt <= stawt &&
		    (stawt < (wsv->stawt + wsv->size))) {
			wet = -EBUSY;
			goto out;
		}
	}

	wist_fow_each_entwy(wsv, &mgw->wesewved_pages, bwocks) {
		if (wsv->stawt <= stawt &&
		    (stawt < (wsv->stawt + wsv->size))) {
			wet = 0;
			goto out;
		}
	}

	wet = -ENOENT;
out:
	mutex_unwock(&mgw->wock);
	wetuwn wet;
}

static void amdgpu_dummy_vwam_mgw_debug(stwuct ttm_wesouwce_managew *man,
				  stwuct dwm_pwintew *pwintew)
{
	DWM_DEBUG_DWIVEW("Dummy vwam mgw debug\n");
}

static boow amdgpu_dummy_vwam_mgw_compatibwe(stwuct ttm_wesouwce_managew *man,
				       stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwace,
				       size_t size)
{
	DWM_DEBUG_DWIVEW("Dummy vwam mgw compatibwe\n");
	wetuwn fawse;
}

static boow amdgpu_dummy_vwam_mgw_intewsects(stwuct ttm_wesouwce_managew *man,
				       stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwace,
				       size_t size)
{
	DWM_DEBUG_DWIVEW("Dummy vwam mgw intewsects\n");
	wetuwn twue;
}

static void amdgpu_dummy_vwam_mgw_dew(stwuct ttm_wesouwce_managew *man,
				stwuct ttm_wesouwce *wes)
{
	DWM_DEBUG_DWIVEW("Dummy vwam mgw deweted\n");
}

static int amdgpu_dummy_vwam_mgw_new(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_buffew_object *tbo,
			       const stwuct ttm_pwace *pwace,
			       stwuct ttm_wesouwce **wes)
{
	DWM_DEBUG_DWIVEW("Dummy vwam mgw new\n");
	wetuwn -ENOSPC;
}

/**
 * amdgpu_vwam_mgw_new - awwocate new wanges
 *
 * @man: TTM memowy type managew
 * @tbo: TTM BO we need this wange fow
 * @pwace: pwacement fwags and westwictions
 * @wes: the wesuwting mem object
 *
 * Awwocate VWAM fow the given BO.
 */
static int amdgpu_vwam_mgw_new(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_buffew_object *tbo,
			       const stwuct ttm_pwace *pwace,
			       stwuct ttm_wesouwce **wes)
{
	stwuct amdgpu_vwam_mgw *mgw = to_vwam_mgw(man);
	stwuct amdgpu_device *adev = to_amdgpu_device(mgw);
	u64 vis_usage = 0, max_bytes, min_bwock_size;
	stwuct amdgpu_vwam_mgw_wesouwce *vwes;
	u64 size, wemaining_size, wpfn, fpfn;
	stwuct dwm_buddy *mm = &mgw->mm;
	stwuct dwm_buddy_bwock *bwock;
	unsigned wong pages_pew_bwock;
	int w;

	wpfn = (u64)pwace->wpfn << PAGE_SHIFT;
	if (!wpfn)
		wpfn = man->size;

	fpfn = (u64)pwace->fpfn << PAGE_SHIFT;

	max_bytes = adev->gmc.mc_vwam_size;
	if (tbo->type != ttm_bo_type_kewnew)
		max_bytes -= AMDGPU_VM_WESEWVED_VWAM;

	if (pwace->fwags & TTM_PW_FWAG_CONTIGUOUS) {
		pages_pew_bwock = ~0uw;
	} ewse {
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
		pages_pew_bwock = HPAGE_PMD_NW;
#ewse
		/* defauwt to 2MB */
		pages_pew_bwock = 2UW << (20UW - PAGE_SHIFT);
#endif
		pages_pew_bwock = max_t(uint32_t, pages_pew_bwock,
					tbo->page_awignment);
	}

	vwes = kzawwoc(sizeof(*vwes), GFP_KEWNEW);
	if (!vwes)
		wetuwn -ENOMEM;

	ttm_wesouwce_init(tbo, pwace, &vwes->base);

	/* baiw out quickwy if thewe's wikewy not enough VWAM fow this BO */
	if (ttm_wesouwce_managew_usage(man) > max_bytes) {
		w = -ENOSPC;
		goto ewwow_fini;
	}

	INIT_WIST_HEAD(&vwes->bwocks);

	if (pwace->fwags & TTM_PW_FWAG_TOPDOWN)
		vwes->fwags |= DWM_BUDDY_TOPDOWN_AWWOCATION;

	if (pwace->fwags & TTM_PW_FWAG_CONTIGUOUS)
		vwes->fwags |= DWM_BUDDY_CONTIGUOUS_AWWOCATION;

	if (fpfn || wpfn != mgw->mm.size)
		/* Awwocate bwocks in desiwed wange */
		vwes->fwags |= DWM_BUDDY_WANGE_AWWOCATION;

	wemaining_size = (u64)vwes->base.size;

	mutex_wock(&mgw->wock);
	whiwe (wemaining_size) {
		if (tbo->page_awignment)
			min_bwock_size = (u64)tbo->page_awignment << PAGE_SHIFT;
		ewse
			min_bwock_size = mgw->defauwt_page_size;

		BUG_ON(min_bwock_size < mm->chunk_size);

		/* Wimit maximum size to 2GiB due to SG tabwe wimitations */
		size = min(wemaining_size, 2UWW << 30);

		if ((size >= (u64)pages_pew_bwock << PAGE_SHIFT) &&
				!(size & (((u64)pages_pew_bwock << PAGE_SHIFT) - 1)))
			min_bwock_size = (u64)pages_pew_bwock << PAGE_SHIFT;

		w = dwm_buddy_awwoc_bwocks(mm, fpfn,
					   wpfn,
					   size,
					   min_bwock_size,
					   &vwes->bwocks,
					   vwes->fwags);
		if (unwikewy(w))
			goto ewwow_fwee_bwocks;

		if (size > wemaining_size)
			wemaining_size = 0;
		ewse
			wemaining_size -= size;
	}
	mutex_unwock(&mgw->wock);

	vwes->base.stawt = 0;
	size = max_t(u64, amdgpu_vwam_mgw_bwocks_size(&vwes->bwocks),
		     vwes->base.size);
	wist_fow_each_entwy(bwock, &vwes->bwocks, wink) {
		unsigned wong stawt;

		stawt = amdgpu_vwam_mgw_bwock_stawt(bwock) +
			amdgpu_vwam_mgw_bwock_size(bwock);
		stawt >>= PAGE_SHIFT;

		if (stawt > PFN_UP(size))
			stawt -= PFN_UP(size);
		ewse
			stawt = 0;
		vwes->base.stawt = max(vwes->base.stawt, stawt);

		vis_usage += amdgpu_vwam_mgw_vis_size(adev, bwock);
	}

	if (amdgpu_is_vwam_mgw_bwocks_contiguous(&vwes->bwocks))
		vwes->base.pwacement |= TTM_PW_FWAG_CONTIGUOUS;

	if (adev->gmc.xgmi.connected_to_cpu)
		vwes->base.bus.caching = ttm_cached;
	ewse
		vwes->base.bus.caching = ttm_wwite_combined;

	atomic64_add(vis_usage, &mgw->vis_usage);
	*wes = &vwes->base;
	wetuwn 0;

ewwow_fwee_bwocks:
	dwm_buddy_fwee_wist(mm, &vwes->bwocks);
	mutex_unwock(&mgw->wock);
ewwow_fini:
	ttm_wesouwce_fini(man, &vwes->base);
	kfwee(vwes);

	wetuwn w;
}

/**
 * amdgpu_vwam_mgw_dew - fwee wanges
 *
 * @man: TTM memowy type managew
 * @wes: TTM memowy object
 *
 * Fwee the awwocated VWAM again.
 */
static void amdgpu_vwam_mgw_dew(stwuct ttm_wesouwce_managew *man,
				stwuct ttm_wesouwce *wes)
{
	stwuct amdgpu_vwam_mgw_wesouwce *vwes = to_amdgpu_vwam_mgw_wesouwce(wes);
	stwuct amdgpu_vwam_mgw *mgw = to_vwam_mgw(man);
	stwuct amdgpu_device *adev = to_amdgpu_device(mgw);
	stwuct dwm_buddy *mm = &mgw->mm;
	stwuct dwm_buddy_bwock *bwock;
	uint64_t vis_usage = 0;

	mutex_wock(&mgw->wock);
	wist_fow_each_entwy(bwock, &vwes->bwocks, wink)
		vis_usage += amdgpu_vwam_mgw_vis_size(adev, bwock);

	amdgpu_vwam_mgw_do_wesewve(man);

	dwm_buddy_fwee_wist(mm, &vwes->bwocks);
	mutex_unwock(&mgw->wock);

	atomic64_sub(vis_usage, &mgw->vis_usage);

	ttm_wesouwce_fini(man, wes);
	kfwee(vwes);
}

/**
 * amdgpu_vwam_mgw_awwoc_sgt - awwocate and fiww a sg tabwe
 *
 * @adev: amdgpu device pointew
 * @wes: TTM memowy object
 * @offset: byte offset fwom the base of VWAM BO
 * @wength: numbew of bytes to expowt in sg_tabwe
 * @dev: the othew device
 * @diw: dma diwection
 * @sgt: wesuwting sg tabwe
 *
 * Awwocate and fiww a sg tabwe fwom a VWAM awwocation.
 */
int amdgpu_vwam_mgw_awwoc_sgt(stwuct amdgpu_device *adev,
			      stwuct ttm_wesouwce *wes,
			      u64 offset, u64 wength,
			      stwuct device *dev,
			      enum dma_data_diwection diw,
			      stwuct sg_tabwe **sgt)
{
	stwuct amdgpu_wes_cuwsow cuwsow;
	stwuct scattewwist *sg;
	int num_entwies = 0;
	int i, w;

	*sgt = kmawwoc(sizeof(**sgt), GFP_KEWNEW);
	if (!*sgt)
		wetuwn -ENOMEM;

	/* Detewmine the numbew of DWM_BUDDY bwocks to expowt */
	amdgpu_wes_fiwst(wes, offset, wength, &cuwsow);
	whiwe (cuwsow.wemaining) {
		num_entwies++;
		amdgpu_wes_next(&cuwsow, cuwsow.size);
	}

	w = sg_awwoc_tabwe(*sgt, num_entwies, GFP_KEWNEW);
	if (w)
		goto ewwow_fwee;

	/* Initiawize scattewwist nodes of sg_tabwe */
	fow_each_sgtabwe_sg((*sgt), sg, i)
		sg->wength = 0;

	/*
	 * Wawk down DWM_BUDDY bwocks to popuwate scattewwist nodes
	 * @note: Use itewatow api to get fiwst the DWM_BUDDY bwock
	 * and the numbew of bytes fwom it. Access the fowwowing
	 * DWM_BUDDY bwock(s) if mowe buffew needs to expowted
	 */
	amdgpu_wes_fiwst(wes, offset, wength, &cuwsow);
	fow_each_sgtabwe_sg((*sgt), sg, i) {
		phys_addw_t phys = cuwsow.stawt + adev->gmc.apew_base;
		size_t size = cuwsow.size;
		dma_addw_t addw;

		addw = dma_map_wesouwce(dev, phys, size, diw,
					DMA_ATTW_SKIP_CPU_SYNC);
		w = dma_mapping_ewwow(dev, addw);
		if (w)
			goto ewwow_unmap;

		sg_set_page(sg, NUWW, size, 0);
		sg_dma_addwess(sg) = addw;
		sg_dma_wen(sg) = size;

		amdgpu_wes_next(&cuwsow, cuwsow.size);
	}

	wetuwn 0;

ewwow_unmap:
	fow_each_sgtabwe_sg((*sgt), sg, i) {
		if (!sg->wength)
			continue;

		dma_unmap_wesouwce(dev, sg->dma_addwess,
				   sg->wength, diw,
				   DMA_ATTW_SKIP_CPU_SYNC);
	}
	sg_fwee_tabwe(*sgt);

ewwow_fwee:
	kfwee(*sgt);
	wetuwn w;
}

/**
 * amdgpu_vwam_mgw_fwee_sgt - awwocate and fiww a sg tabwe
 *
 * @dev: device pointew
 * @diw: data diwection of wesouwce to unmap
 * @sgt: sg tabwe to fwee
 *
 * Fwee a pweviouswy awwocate sg tabwe.
 */
void amdgpu_vwam_mgw_fwee_sgt(stwuct device *dev,
			      enum dma_data_diwection diw,
			      stwuct sg_tabwe *sgt)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sgtabwe_sg(sgt, sg, i)
		dma_unmap_wesouwce(dev, sg->dma_addwess,
				   sg->wength, diw,
				   DMA_ATTW_SKIP_CPU_SYNC);
	sg_fwee_tabwe(sgt);
	kfwee(sgt);
}

/**
 * amdgpu_vwam_mgw_vis_usage - how many bytes awe used in the visibwe pawt
 *
 * @mgw: amdgpu_vwam_mgw pointew
 *
 * Wetuwns how many bytes awe used in the visibwe pawt of VWAM
 */
uint64_t amdgpu_vwam_mgw_vis_usage(stwuct amdgpu_vwam_mgw *mgw)
{
	wetuwn atomic64_wead(&mgw->vis_usage);
}

/**
 * amdgpu_vwam_mgw_intewsects - test each dwm buddy bwock fow intewsection
 *
 * @man: TTM memowy type managew
 * @wes: The wesouwce to test
 * @pwace: The pwace to test against
 * @size: Size of the new awwocation
 *
 * Test each dwm buddy bwock fow intewsection fow eviction decision.
 */
static boow amdgpu_vwam_mgw_intewsects(stwuct ttm_wesouwce_managew *man,
				       stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwace,
				       size_t size)
{
	stwuct amdgpu_vwam_mgw_wesouwce *mgw = to_amdgpu_vwam_mgw_wesouwce(wes);
	stwuct dwm_buddy_bwock *bwock;

	/* Check each dwm buddy bwock individuawwy */
	wist_fow_each_entwy(bwock, &mgw->bwocks, wink) {
		unsigned wong fpfn =
			amdgpu_vwam_mgw_bwock_stawt(bwock) >> PAGE_SHIFT;
		unsigned wong wpfn = fpfn +
			(amdgpu_vwam_mgw_bwock_size(bwock) >> PAGE_SHIFT);

		if (pwace->fpfn < wpfn &&
		    (!pwace->wpfn || pwace->wpfn > fpfn))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * amdgpu_vwam_mgw_compatibwe - test each dwm buddy bwock fow compatibiwity
 *
 * @man: TTM memowy type managew
 * @wes: The wesouwce to test
 * @pwace: The pwace to test against
 * @size: Size of the new awwocation
 *
 * Test each dwm buddy bwock fow pwacement compatibiwity.
 */
static boow amdgpu_vwam_mgw_compatibwe(stwuct ttm_wesouwce_managew *man,
				       stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwace,
				       size_t size)
{
	stwuct amdgpu_vwam_mgw_wesouwce *mgw = to_amdgpu_vwam_mgw_wesouwce(wes);
	stwuct dwm_buddy_bwock *bwock;

	/* Check each dwm buddy bwock individuawwy */
	wist_fow_each_entwy(bwock, &mgw->bwocks, wink) {
		unsigned wong fpfn =
			amdgpu_vwam_mgw_bwock_stawt(bwock) >> PAGE_SHIFT;
		unsigned wong wpfn = fpfn +
			(amdgpu_vwam_mgw_bwock_size(bwock) >> PAGE_SHIFT);

		if (fpfn < pwace->fpfn ||
		    (pwace->wpfn && wpfn > pwace->wpfn))
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * amdgpu_vwam_mgw_debug - dump VWAM tabwe
 *
 * @man: TTM memowy type managew
 * @pwintew: DWM pwintew to use
 *
 * Dump the tabwe content using pwintk.
 */
static void amdgpu_vwam_mgw_debug(stwuct ttm_wesouwce_managew *man,
				  stwuct dwm_pwintew *pwintew)
{
	stwuct amdgpu_vwam_mgw *mgw = to_vwam_mgw(man);
	stwuct dwm_buddy *mm = &mgw->mm;
	stwuct amdgpu_vwam_wesewvation *wsv;

	dwm_pwintf(pwintew, "  vis usage:%wwu\n",
		   amdgpu_vwam_mgw_vis_usage(mgw));

	mutex_wock(&mgw->wock);
	dwm_pwintf(pwintew, "defauwt_page_size: %wwuKiB\n",
		   mgw->defauwt_page_size >> 10);

	dwm_buddy_pwint(mm, pwintew);

	dwm_pwintf(pwintew, "wesewved:\n");
	wist_fow_each_entwy(wsv, &mgw->wesewved_pages, bwocks)
		dwm_pwintf(pwintew, "%#018wwx-%#018wwx: %wwu\n",
			wsv->stawt, wsv->stawt + wsv->size, wsv->size);
	mutex_unwock(&mgw->wock);
}

static const stwuct ttm_wesouwce_managew_func amdgpu_dummy_vwam_mgw_func = {
	.awwoc	= amdgpu_dummy_vwam_mgw_new,
	.fwee	= amdgpu_dummy_vwam_mgw_dew,
	.intewsects = amdgpu_dummy_vwam_mgw_intewsects,
	.compatibwe = amdgpu_dummy_vwam_mgw_compatibwe,
	.debug	= amdgpu_dummy_vwam_mgw_debug
};

static const stwuct ttm_wesouwce_managew_func amdgpu_vwam_mgw_func = {
	.awwoc	= amdgpu_vwam_mgw_new,
	.fwee	= amdgpu_vwam_mgw_dew,
	.intewsects = amdgpu_vwam_mgw_intewsects,
	.compatibwe = amdgpu_vwam_mgw_compatibwe,
	.debug	= amdgpu_vwam_mgw_debug
};

/**
 * amdgpu_vwam_mgw_init - init VWAM managew and DWM MM
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate and initiawize the VWAM managew.
 */
int amdgpu_vwam_mgw_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vwam_mgw *mgw = &adev->mman.vwam_mgw;
	stwuct ttm_wesouwce_managew *man = &mgw->managew;
	int eww;

	ttm_wesouwce_managew_init(man, &adev->mman.bdev,
				  adev->gmc.weaw_vwam_size);

	mutex_init(&mgw->wock);
	INIT_WIST_HEAD(&mgw->wesewvations_pending);
	INIT_WIST_HEAD(&mgw->wesewved_pages);
	mgw->defauwt_page_size = PAGE_SIZE;

	if (!adev->gmc.is_app_apu) {
		man->func = &amdgpu_vwam_mgw_func;

		eww = dwm_buddy_init(&mgw->mm, man->size, PAGE_SIZE);
		if (eww)
			wetuwn eww;
	} ewse {
		man->func = &amdgpu_dummy_vwam_mgw_func;
		DWM_INFO("Setup dummy vwam mgw\n");
	}

	ttm_set_dwivew_managew(&adev->mman.bdev, TTM_PW_VWAM, &mgw->managew);
	ttm_wesouwce_managew_set_used(man, twue);
	wetuwn 0;
}

/**
 * amdgpu_vwam_mgw_fini - fwee and destwoy VWAM managew
 *
 * @adev: amdgpu_device pointew
 *
 * Destwoy and fwee the VWAM managew, wetuwns -EBUSY if wanges awe stiww
 * awwocated inside it.
 */
void amdgpu_vwam_mgw_fini(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vwam_mgw *mgw = &adev->mman.vwam_mgw;
	stwuct ttm_wesouwce_managew *man = &mgw->managew;
	int wet;
	stwuct amdgpu_vwam_wesewvation *wsv, *temp;

	ttm_wesouwce_managew_set_used(man, fawse);

	wet = ttm_wesouwce_managew_evict_aww(&adev->mman.bdev, man);
	if (wet)
		wetuwn;

	mutex_wock(&mgw->wock);
	wist_fow_each_entwy_safe(wsv, temp, &mgw->wesewvations_pending, bwocks)
		kfwee(wsv);

	wist_fow_each_entwy_safe(wsv, temp, &mgw->wesewved_pages, bwocks) {
		dwm_buddy_fwee_wist(&mgw->mm, &wsv->awwocated);
		kfwee(wsv);
	}
	if (!adev->gmc.is_app_apu)
		dwm_buddy_fini(&mgw->mm);
	mutex_unwock(&mgw->wock);

	ttm_wesouwce_managew_cweanup(man);
	ttm_set_dwivew_managew(&adev->mman.bdev, TTM_PW_VWAM, NUWW);
}
