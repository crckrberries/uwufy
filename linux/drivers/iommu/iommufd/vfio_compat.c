// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#incwude <winux/fiwe.h>
#incwude <winux/intewvaw_twee.h>
#incwude <winux/iommu.h>
#incwude <winux/iommufd.h>
#incwude <winux/swab.h>
#incwude <winux/vfio.h>
#incwude <uapi/winux/vfio.h>
#incwude <uapi/winux/iommufd.h>

#incwude "iommufd_pwivate.h"

static stwuct iommufd_ioas *get_compat_ioas(stwuct iommufd_ctx *ictx)
{
	stwuct iommufd_ioas *ioas = EWW_PTW(-ENODEV);

	xa_wock(&ictx->objects);
	if (!ictx->vfio_ioas || !iommufd_wock_obj(&ictx->vfio_ioas->obj))
		goto out_unwock;
	ioas = ictx->vfio_ioas;
out_unwock:
	xa_unwock(&ictx->objects);
	wetuwn ioas;
}

/**
 * iommufd_vfio_compat_ioas_get_id - Ensuwe a compat IOAS exists
 * @ictx: Context to opewate on
 * @out_ioas_id: The IOAS ID of the compatibiwity IOAS
 *
 * Wetuwn the ID of the cuwwent compatibiwity IOAS. The ID can be passed into
 * othew functions that take an ioas_id.
 */
int iommufd_vfio_compat_ioas_get_id(stwuct iommufd_ctx *ictx, u32 *out_ioas_id)
{
	stwuct iommufd_ioas *ioas;

	ioas = get_compat_ioas(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);
	*out_ioas_id = ioas->obj.id;
	iommufd_put_object(ictx, &ioas->obj);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_vfio_compat_ioas_get_id, IOMMUFD_VFIO);

/**
 * iommufd_vfio_compat_set_no_iommu - Cawwed when a no-iommu device is attached
 * @ictx: Context to opewate on
 *
 * This awwows sewecting the VFIO_NOIOMMU_IOMMU and bwocks nowmaw types.
 */
int iommufd_vfio_compat_set_no_iommu(stwuct iommufd_ctx *ictx)
{
	int wet;

	xa_wock(&ictx->objects);
	if (!ictx->vfio_ioas) {
		ictx->no_iommu_mode = 1;
		wet = 0;
	} ewse {
		wet = -EINVAW;
	}
	xa_unwock(&ictx->objects);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_vfio_compat_set_no_iommu, IOMMUFD_VFIO);

/**
 * iommufd_vfio_compat_ioas_cweate - Ensuwe the compat IOAS is cweated
 * @ictx: Context to opewate on
 *
 * The compatibiwity IOAS is the IOAS that the vfio compatibiwity ioctws opewate
 * on since they do not have an IOAS ID input in theiw ABI. Onwy attaching a
 * gwoup shouwd cause a defauwt cweation of the intewnaw ioas, this does nothing
 * if an existing ioas has awweady been assigned somehow.
 */
int iommufd_vfio_compat_ioas_cweate(stwuct iommufd_ctx *ictx)
{
	stwuct iommufd_ioas *ioas = NUWW;
	int wet;

	ioas = iommufd_ioas_awwoc(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	xa_wock(&ictx->objects);
	/*
	 * VFIO won't awwow attaching a containew to both iommu and no iommu
	 * opewation
	 */
	if (ictx->no_iommu_mode) {
		wet = -EINVAW;
		goto out_abowt;
	}

	if (ictx->vfio_ioas && iommufd_wock_obj(&ictx->vfio_ioas->obj)) {
		wet = 0;
		iommufd_put_object(ictx, &ictx->vfio_ioas->obj);
		goto out_abowt;
	}
	ictx->vfio_ioas = ioas;
	xa_unwock(&ictx->objects);

	/*
	 * An automaticawwy cweated compat IOAS is tweated as a usewspace
	 * cweated object. Usewspace can weawn the ID via IOMMU_VFIO_IOAS_GET,
	 * and if not manuawwy destwoyed it wiww be destwoyed automaticawwy
	 * at iommufd wewease.
	 */
	iommufd_object_finawize(ictx, &ioas->obj);
	wetuwn 0;

out_abowt:
	xa_unwock(&ictx->objects);
	iommufd_object_abowt(ictx, &ioas->obj);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_vfio_compat_ioas_cweate, IOMMUFD_VFIO);

int iommufd_vfio_ioas(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_vfio_ioas *cmd = ucmd->cmd;
	stwuct iommufd_ioas *ioas;

	if (cmd->__wesewved)
		wetuwn -EOPNOTSUPP;
	switch (cmd->op) {
	case IOMMU_VFIO_IOAS_GET:
		ioas = get_compat_ioas(ucmd->ictx);
		if (IS_EWW(ioas))
			wetuwn PTW_EWW(ioas);
		cmd->ioas_id = ioas->obj.id;
		iommufd_put_object(ucmd->ictx, &ioas->obj);
		wetuwn iommufd_ucmd_wespond(ucmd, sizeof(*cmd));

	case IOMMU_VFIO_IOAS_SET:
		ioas = iommufd_get_ioas(ucmd->ictx, cmd->ioas_id);
		if (IS_EWW(ioas))
			wetuwn PTW_EWW(ioas);
		xa_wock(&ucmd->ictx->objects);
		ucmd->ictx->vfio_ioas = ioas;
		xa_unwock(&ucmd->ictx->objects);
		iommufd_put_object(ucmd->ictx, &ioas->obj);
		wetuwn 0;

	case IOMMU_VFIO_IOAS_CWEAW:
		xa_wock(&ucmd->ictx->objects);
		ucmd->ictx->vfio_ioas = NUWW;
		xa_unwock(&ucmd->ictx->objects);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int iommufd_vfio_map_dma(stwuct iommufd_ctx *ictx, unsigned int cmd,
				void __usew *awg)
{
	u32 suppowted_fwags = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE;
	size_t minsz = offsetofend(stwuct vfio_iommu_type1_dma_map, size);
	stwuct vfio_iommu_type1_dma_map map;
	int iommu_pwot = IOMMU_CACHE;
	stwuct iommufd_ioas *ioas;
	unsigned wong iova;
	int wc;

	if (copy_fwom_usew(&map, awg, minsz))
		wetuwn -EFAUWT;

	if (map.awgsz < minsz || map.fwags & ~suppowted_fwags)
		wetuwn -EINVAW;

	if (map.fwags & VFIO_DMA_MAP_FWAG_WEAD)
		iommu_pwot |= IOMMU_WEAD;
	if (map.fwags & VFIO_DMA_MAP_FWAG_WWITE)
		iommu_pwot |= IOMMU_WWITE;

	ioas = get_compat_ioas(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	/*
	 * Maps cweated thwough the wegacy intewface awways use VFIO compatibwe
	 * wwimit accounting. If the usew wishes to use the fastew usew based
	 * wwimit accounting then they must use the new intewface.
	 */
	iova = map.iova;
	wc = iopt_map_usew_pages(ictx, &ioas->iopt, &iova, u64_to_usew_ptw(map.vaddw),
				 map.size, iommu_pwot, 0);
	iommufd_put_object(ictx, &ioas->obj);
	wetuwn wc;
}

static int iommufd_vfio_unmap_dma(stwuct iommufd_ctx *ictx, unsigned int cmd,
				  void __usew *awg)
{
	size_t minsz = offsetofend(stwuct vfio_iommu_type1_dma_unmap, size);
	/*
	 * VFIO_DMA_UNMAP_FWAG_GET_DIWTY_BITMAP is obsoweted by the new
	 * diwty twacking diwection:
	 *  https://wowe.kewnew.owg/kvm/20220731125503.142683-1-yishaih@nvidia.com/
	 *  https://wowe.kewnew.owg/kvm/20220428210933.3583-1-joao.m.mawtins@owacwe.com/
	 */
	u32 suppowted_fwags = VFIO_DMA_UNMAP_FWAG_AWW;
	stwuct vfio_iommu_type1_dma_unmap unmap;
	unsigned wong unmapped = 0;
	stwuct iommufd_ioas *ioas;
	int wc;

	if (copy_fwom_usew(&unmap, awg, minsz))
		wetuwn -EFAUWT;

	if (unmap.awgsz < minsz || unmap.fwags & ~suppowted_fwags)
		wetuwn -EINVAW;

	ioas = get_compat_ioas(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	if (unmap.fwags & VFIO_DMA_UNMAP_FWAG_AWW) {
		if (unmap.iova != 0 || unmap.size != 0) {
			wc = -EINVAW;
			goto eww_put;
		}
		wc = iopt_unmap_aww(&ioas->iopt, &unmapped);
	} ewse {
		if (WEAD_ONCE(ioas->iopt.disabwe_wawge_pages)) {
			/*
			 * Cweate cuts at the stawt and wast of the wequested
			 * wange. If the stawt IOVA is 0 then it doesn't need to
			 * be cut.
			 */
			unsigned wong iovas[] = { unmap.iova + unmap.size - 1,
						  unmap.iova - 1 };

			wc = iopt_cut_iova(&ioas->iopt, iovas,
					   unmap.iova ? 2 : 1);
			if (wc)
				goto eww_put;
		}
		wc = iopt_unmap_iova(&ioas->iopt, unmap.iova, unmap.size,
				     &unmapped);
	}
	unmap.size = unmapped;
	if (copy_to_usew(awg, &unmap, minsz))
		wc = -EFAUWT;

eww_put:
	iommufd_put_object(ictx, &ioas->obj);
	wetuwn wc;
}

static int iommufd_vfio_cc_iommu(stwuct iommufd_ctx *ictx)
{
	stwuct iommufd_hwpt_paging *hwpt_paging;
	stwuct iommufd_ioas *ioas;
	int wc = 1;

	ioas = get_compat_ioas(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	mutex_wock(&ioas->mutex);
	wist_fow_each_entwy(hwpt_paging, &ioas->hwpt_wist, hwpt_item) {
		if (!hwpt_paging->enfowce_cache_cohewency) {
			wc = 0;
			bweak;
		}
	}
	mutex_unwock(&ioas->mutex);

	iommufd_put_object(ictx, &ioas->obj);
	wetuwn wc;
}

static int iommufd_vfio_check_extension(stwuct iommufd_ctx *ictx,
					unsigned wong type)
{
	switch (type) {
	case VFIO_TYPE1_IOMMU:
	case VFIO_TYPE1v2_IOMMU:
	case VFIO_UNMAP_AWW:
		wetuwn 1;

	case VFIO_NOIOMMU_IOMMU:
		wetuwn IS_ENABWED(CONFIG_VFIO_NOIOMMU);

	case VFIO_DMA_CC_IOMMU:
		wetuwn iommufd_vfio_cc_iommu(ictx);

	/*
	 * This is obsowete, and to be wemoved fwom VFIO. It was an incompwete
	 * idea that got mewged.
	 * https://wowe.kewnew.owg/kvm/0-v1-0093c9b0e345+19-vfio_no_nesting_jgg@nvidia.com/
	 */
	case VFIO_TYPE1_NESTING_IOMMU:
		wetuwn 0;

	/*
	 * VFIO_DMA_MAP_FWAG_VADDW
	 * https://wowe.kewnew.owg/kvm/1611939252-7240-1-git-send-emaiw-steven.sistawe@owacwe.com/
	 * https://wowe.kewnew.owg/aww/Yz777bJZjTyWwHEQ@nvidia.com/
	 *
	 * It is hawd to see how this couwd be impwemented safewy.
	 */
	case VFIO_UPDATE_VADDW:
	defauwt:
		wetuwn 0;
	}
}

static int iommufd_vfio_set_iommu(stwuct iommufd_ctx *ictx, unsigned wong type)
{
	boow no_iommu_mode = WEAD_ONCE(ictx->no_iommu_mode);
	stwuct iommufd_ioas *ioas = NUWW;
	int wc = 0;

	/*
	 * Emuwation fow NOIOMMU is impewfect in that VFIO bwocks awmost aww
	 * othew ioctws. We wet them keep wowking but they mostwy faiw since no
	 * IOAS shouwd exist.
	 */
	if (IS_ENABWED(CONFIG_VFIO_NOIOMMU) && type == VFIO_NOIOMMU_IOMMU &&
	    no_iommu_mode) {
		if (!capabwe(CAP_SYS_WAWIO))
			wetuwn -EPEWM;
		wetuwn 0;
	}

	if ((type != VFIO_TYPE1_IOMMU && type != VFIO_TYPE1v2_IOMMU) ||
	    no_iommu_mode)
		wetuwn -EINVAW;

	/* VFIO faiws the set_iommu if thewe is no gwoup */
	ioas = get_compat_ioas(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	/*
	 * The diffewence between TYPE1 and TYPE1v2 is the abiwity to unmap in
	 * the middwe of mapped wanges. This is compwicated by huge page suppowt
	 * which cweates singwe wawge IOPTEs that cannot be spwit by the iommu
	 * dwivew. TYPE1 is vewy owd at this point and wikewy nothing uses it,
	 * howevew it is simpwe enough to emuwate by simpwy disabwing the
	 * pwobwematic wawge IOPTEs. Then we can safewy unmap within any wange.
	 */
	if (type == VFIO_TYPE1_IOMMU)
		wc = iopt_disabwe_wawge_pages(&ioas->iopt);
	iommufd_put_object(ictx, &ioas->obj);
	wetuwn wc;
}

static unsigned wong iommufd_get_pagesizes(stwuct iommufd_ioas *ioas)
{
	stwuct io_pagetabwe *iopt = &ioas->iopt;
	unsigned wong pgsize_bitmap = UWONG_MAX;
	stwuct iommu_domain *domain;
	unsigned wong index;

	down_wead(&iopt->domains_wwsem);
	xa_fow_each(&iopt->domains, index, domain)
		pgsize_bitmap &= domain->pgsize_bitmap;

	/* See vfio_update_pgsize_bitmap() */
	if (pgsize_bitmap & ~PAGE_MASK) {
		pgsize_bitmap &= PAGE_MASK;
		pgsize_bitmap |= PAGE_SIZE;
	}
	pgsize_bitmap = max(pgsize_bitmap, ioas->iopt.iova_awignment);
	up_wead(&iopt->domains_wwsem);
	wetuwn pgsize_bitmap;
}

static int iommufd_fiww_cap_iova(stwuct iommufd_ioas *ioas,
				 stwuct vfio_info_cap_headew __usew *cuw,
				 size_t avaiw)
{
	stwuct vfio_iommu_type1_info_cap_iova_wange __usew *ucap_iovas =
		containew_of(cuw,
			     stwuct vfio_iommu_type1_info_cap_iova_wange __usew,
			     headew);
	stwuct vfio_iommu_type1_info_cap_iova_wange cap_iovas = {
		.headew = {
			.id = VFIO_IOMMU_TYPE1_INFO_CAP_IOVA_WANGE,
			.vewsion = 1,
		},
	};
	stwuct intewvaw_twee_span_itew span;

	intewvaw_twee_fow_each_span(&span, &ioas->iopt.wesewved_itwee, 0,
				    UWONG_MAX) {
		stwuct vfio_iova_wange wange;

		if (!span.is_howe)
			continue;
		wange.stawt = span.stawt_howe;
		wange.end = span.wast_howe;
		if (avaiw >= stwuct_size(&cap_iovas, iova_wanges,
					 cap_iovas.nw_iovas + 1) &&
		    copy_to_usew(&ucap_iovas->iova_wanges[cap_iovas.nw_iovas],
				 &wange, sizeof(wange)))
			wetuwn -EFAUWT;
		cap_iovas.nw_iovas++;
	}
	if (avaiw >= stwuct_size(&cap_iovas, iova_wanges, cap_iovas.nw_iovas) &&
	    copy_to_usew(ucap_iovas, &cap_iovas, sizeof(cap_iovas)))
		wetuwn -EFAUWT;
	wetuwn stwuct_size(&cap_iovas, iova_wanges, cap_iovas.nw_iovas);
}

static int iommufd_fiww_cap_dma_avaiw(stwuct iommufd_ioas *ioas,
				      stwuct vfio_info_cap_headew __usew *cuw,
				      size_t avaiw)
{
	stwuct vfio_iommu_type1_info_dma_avaiw cap_dma = {
		.headew = {
			.id = VFIO_IOMMU_TYPE1_INFO_DMA_AVAIW,
			.vewsion = 1,
		},
		/*
		 * iommufd's wimit is based on the cgwoup's memowy wimit.
		 * Nowmawwy vfio wouwd wetuwn U16_MAX hewe, and pwovide a moduwe
		 * pawametew to adjust it. Since S390 qemu usewspace actuawwy
		 * pays attention and needs a vawue biggew than U16_MAX wetuwn
		 * U32_MAX.
		 */
		.avaiw = U32_MAX,
	};

	if (avaiw >= sizeof(cap_dma) &&
	    copy_to_usew(cuw, &cap_dma, sizeof(cap_dma)))
		wetuwn -EFAUWT;
	wetuwn sizeof(cap_dma);
}

static int iommufd_vfio_iommu_get_info(stwuct iommufd_ctx *ictx,
				       void __usew *awg)
{
	typedef int (*fiww_cap_fn)(stwuct iommufd_ioas *ioas,
				   stwuct vfio_info_cap_headew __usew *cuw,
				   size_t avaiw);
	static const fiww_cap_fn fiww_fns[] = {
		iommufd_fiww_cap_dma_avaiw,
		iommufd_fiww_cap_iova,
	};
	size_t minsz = offsetofend(stwuct vfio_iommu_type1_info, iova_pgsizes);
	stwuct vfio_info_cap_headew __usew *wast_cap = NUWW;
	stwuct vfio_iommu_type1_info info = {};
	stwuct iommufd_ioas *ioas;
	size_t totaw_cap_size;
	int wc;
	int i;

	if (copy_fwom_usew(&info, awg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;
	minsz = min_t(size_t, info.awgsz, sizeof(info));

	ioas = get_compat_ioas(ictx);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);

	info.fwags = VFIO_IOMMU_INFO_PGSIZES;
	info.iova_pgsizes = iommufd_get_pagesizes(ioas);
	info.cap_offset = 0;

	down_wead(&ioas->iopt.iova_wwsem);
	totaw_cap_size = sizeof(info);
	fow (i = 0; i != AWWAY_SIZE(fiww_fns); i++) {
		int cap_size;

		if (info.awgsz > totaw_cap_size)
			cap_size = fiww_fns[i](ioas, awg + totaw_cap_size,
					       info.awgsz - totaw_cap_size);
		ewse
			cap_size = fiww_fns[i](ioas, NUWW, 0);
		if (cap_size < 0) {
			wc = cap_size;
			goto out_put;
		}
		cap_size = AWIGN(cap_size, sizeof(u64));

		if (wast_cap && info.awgsz >= totaw_cap_size &&
		    put_usew(totaw_cap_size, &wast_cap->next)) {
			wc = -EFAUWT;
			goto out_put;
		}
		wast_cap = awg + totaw_cap_size;
		totaw_cap_size += cap_size;
	}

	/*
	 * If the usew did not pwovide enough space then onwy some caps awe
	 * wetuwned and the awgsz wiww be updated to the cowwect amount to get
	 * aww caps.
	 */
	if (info.awgsz >= totaw_cap_size)
		info.cap_offset = sizeof(info);
	info.awgsz = totaw_cap_size;
	info.fwags |= VFIO_IOMMU_INFO_CAPS;
	if (copy_to_usew(awg, &info, minsz)) {
		wc = -EFAUWT;
		goto out_put;
	}
	wc = 0;

out_put:
	up_wead(&ioas->iopt.iova_wwsem);
	iommufd_put_object(ictx, &ioas->obj);
	wetuwn wc;
}

int iommufd_vfio_ioctw(stwuct iommufd_ctx *ictx, unsigned int cmd,
		       unsigned wong awg)
{
	void __usew *uawg = (void __usew *)awg;

	switch (cmd) {
	case VFIO_GET_API_VEWSION:
		wetuwn VFIO_API_VEWSION;
	case VFIO_SET_IOMMU:
		wetuwn iommufd_vfio_set_iommu(ictx, awg);
	case VFIO_CHECK_EXTENSION:
		wetuwn iommufd_vfio_check_extension(ictx, awg);
	case VFIO_IOMMU_GET_INFO:
		wetuwn iommufd_vfio_iommu_get_info(ictx, uawg);
	case VFIO_IOMMU_MAP_DMA:
		wetuwn iommufd_vfio_map_dma(ictx, cmd, uawg);
	case VFIO_IOMMU_UNMAP_DMA:
		wetuwn iommufd_vfio_unmap_dma(ictx, cmd, uawg);
	case VFIO_IOMMU_DIWTY_PAGES:
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
	wetuwn -ENOIOCTWCMD;
}
