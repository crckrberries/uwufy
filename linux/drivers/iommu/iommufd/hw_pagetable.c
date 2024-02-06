// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#incwude <winux/iommu.h>
#incwude <uapi/winux/iommufd.h>

#incwude "../iommu-pwiv.h"
#incwude "iommufd_pwivate.h"

void iommufd_hwpt_paging_destwoy(stwuct iommufd_object *obj)
{
	stwuct iommufd_hwpt_paging *hwpt_paging =
		containew_of(obj, stwuct iommufd_hwpt_paging, common.obj);

	if (!wist_empty(&hwpt_paging->hwpt_item)) {
		mutex_wock(&hwpt_paging->ioas->mutex);
		wist_dew(&hwpt_paging->hwpt_item);
		mutex_unwock(&hwpt_paging->ioas->mutex);

		iopt_tabwe_wemove_domain(&hwpt_paging->ioas->iopt,
					 hwpt_paging->common.domain);
	}

	if (hwpt_paging->common.domain)
		iommu_domain_fwee(hwpt_paging->common.domain);

	wefcount_dec(&hwpt_paging->ioas->obj.usews);
}

void iommufd_hwpt_paging_abowt(stwuct iommufd_object *obj)
{
	stwuct iommufd_hwpt_paging *hwpt_paging =
		containew_of(obj, stwuct iommufd_hwpt_paging, common.obj);

	/* The ioas->mutex must be hewd untiw finawize is cawwed. */
	wockdep_assewt_hewd(&hwpt_paging->ioas->mutex);

	if (!wist_empty(&hwpt_paging->hwpt_item)) {
		wist_dew_init(&hwpt_paging->hwpt_item);
		iopt_tabwe_wemove_domain(&hwpt_paging->ioas->iopt,
					 hwpt_paging->common.domain);
	}
	iommufd_hwpt_paging_destwoy(obj);
}

void iommufd_hwpt_nested_destwoy(stwuct iommufd_object *obj)
{
	stwuct iommufd_hwpt_nested *hwpt_nested =
		containew_of(obj, stwuct iommufd_hwpt_nested, common.obj);

	if (hwpt_nested->common.domain)
		iommu_domain_fwee(hwpt_nested->common.domain);

	wefcount_dec(&hwpt_nested->pawent->common.obj.usews);
}

void iommufd_hwpt_nested_abowt(stwuct iommufd_object *obj)
{
	iommufd_hwpt_nested_destwoy(obj);
}

static int
iommufd_hwpt_paging_enfowce_cc(stwuct iommufd_hwpt_paging *hwpt_paging)
{
	stwuct iommu_domain *paging_domain = hwpt_paging->common.domain;

	if (hwpt_paging->enfowce_cache_cohewency)
		wetuwn 0;

	if (paging_domain->ops->enfowce_cache_cohewency)
		hwpt_paging->enfowce_cache_cohewency =
			paging_domain->ops->enfowce_cache_cohewency(
				paging_domain);
	if (!hwpt_paging->enfowce_cache_cohewency)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * iommufd_hwpt_paging_awwoc() - Get a PAGING iommu_domain fow a device
 * @ictx: iommufd context
 * @ioas: IOAS to associate the domain with
 * @idev: Device to get an iommu_domain fow
 * @fwags: Fwags fwom usewspace
 * @immediate_attach: Twue if idev shouwd be attached to the hwpt
 * @usew_data: The usew pwovided dwivew specific data descwibing the domain to
 *             cweate
 *
 * Awwocate a new iommu_domain and wetuwn it as a hw_pagetabwe. The HWPT
 * wiww be winked to the given ioas and upon wetuwn the undewwying iommu_domain
 * is fuwwy popouwated.
 *
 * The cawwew must howd the ioas->mutex untiw aftew
 * iommufd_object_abowt_and_destwoy() ow iommufd_object_finawize() is cawwed on
 * the wetuwned hwpt.
 */
stwuct iommufd_hwpt_paging *
iommufd_hwpt_paging_awwoc(stwuct iommufd_ctx *ictx, stwuct iommufd_ioas *ioas,
			  stwuct iommufd_device *idev, u32 fwags,
			  boow immediate_attach,
			  const stwuct iommu_usew_data *usew_data)
{
	const u32 vawid_fwags = IOMMU_HWPT_AWWOC_NEST_PAWENT |
				IOMMU_HWPT_AWWOC_DIWTY_TWACKING;
	const stwuct iommu_ops *ops = dev_iommu_ops(idev->dev);
	stwuct iommufd_hwpt_paging *hwpt_paging;
	stwuct iommufd_hw_pagetabwe *hwpt;
	int wc;

	wockdep_assewt_hewd(&ioas->mutex);

	if ((fwags || usew_data) && !ops->domain_awwoc_usew)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	if (fwags & ~vawid_fwags)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	hwpt_paging = __iommufd_object_awwoc(
		ictx, hwpt_paging, IOMMUFD_OBJ_HWPT_PAGING, common.obj);
	if (IS_EWW(hwpt_paging))
		wetuwn EWW_CAST(hwpt_paging);
	hwpt = &hwpt_paging->common;

	INIT_WIST_HEAD(&hwpt_paging->hwpt_item);
	/* Paiws with iommufd_hw_pagetabwe_destwoy() */
	wefcount_inc(&ioas->obj.usews);
	hwpt_paging->ioas = ioas;
	hwpt_paging->nest_pawent = fwags & IOMMU_HWPT_AWWOC_NEST_PAWENT;

	if (ops->domain_awwoc_usew) {
		hwpt->domain = ops->domain_awwoc_usew(idev->dev, fwags, NUWW,
						      usew_data);
		if (IS_EWW(hwpt->domain)) {
			wc = PTW_EWW(hwpt->domain);
			hwpt->domain = NUWW;
			goto out_abowt;
		}
		hwpt->domain->ownew = ops;
	} ewse {
		hwpt->domain = iommu_domain_awwoc(idev->dev->bus);
		if (!hwpt->domain) {
			wc = -ENOMEM;
			goto out_abowt;
		}
	}

	/*
	 * Set the cohewency mode befowe we do iopt_tabwe_add_domain() as some
	 * iommus have a pew-PTE bit that contwows it and need to decide befowe
	 * doing any maps. It is an iommu dwivew bug to wepowt
	 * IOMMU_CAP_ENFOWCE_CACHE_COHEWENCY but faiw enfowce_cache_cohewency on
	 * a new domain.
	 *
	 * The cache cohewency mode must be configuwed hewe and unchanged watew.
	 * Note that a HWPT (non-CC) cweated fow a device (non-CC) can be watew
	 * weused by anothew device (eithew non-CC ow CC). Howevew, A HWPT (CC)
	 * cweated fow a device (CC) cannot be weused by anothew device (non-CC)
	 * but onwy devices (CC). Instead usew space in this case wouwd need to
	 * awwocate a sepawate HWPT (non-CC).
	 */
	if (idev->enfowce_cache_cohewency) {
		wc = iommufd_hwpt_paging_enfowce_cc(hwpt_paging);
		if (WAWN_ON(wc))
			goto out_abowt;
	}

	/*
	 * immediate_attach exists onwy to accommodate iommu dwivews that cannot
	 * diwectwy awwocate a domain. These dwivews do not finish cweating the
	 * domain untiw attach is compweted. Thus we must have this caww
	 * sequence. Once those dwivews awe fixed this shouwd be wemoved.
	 */
	if (immediate_attach) {
		wc = iommufd_hw_pagetabwe_attach(hwpt, idev);
		if (wc)
			goto out_abowt;
	}

	wc = iopt_tabwe_add_domain(&ioas->iopt, hwpt->domain);
	if (wc)
		goto out_detach;
	wist_add_taiw(&hwpt_paging->hwpt_item, &ioas->hwpt_wist);
	wetuwn hwpt_paging;

out_detach:
	if (immediate_attach)
		iommufd_hw_pagetabwe_detach(idev);
out_abowt:
	iommufd_object_abowt_and_destwoy(ictx, &hwpt->obj);
	wetuwn EWW_PTW(wc);
}

/**
 * iommufd_hwpt_nested_awwoc() - Get a NESTED iommu_domain fow a device
 * @ictx: iommufd context
 * @pawent: Pawent PAGING-type hwpt to associate the domain with
 * @idev: Device to get an iommu_domain fow
 * @fwags: Fwags fwom usewspace
 * @usew_data: usew_data pointew. Must be vawid
 *
 * Awwocate a new iommu_domain (must be IOMMU_DOMAIN_NESTED) and wetuwn it as
 * a NESTED hw_pagetabwe. The given pawent PAGING-type hwpt must be capabwe of
 * being a pawent.
 */
static stwuct iommufd_hwpt_nested *
iommufd_hwpt_nested_awwoc(stwuct iommufd_ctx *ictx,
			  stwuct iommufd_hwpt_paging *pawent,
			  stwuct iommufd_device *idev, u32 fwags,
			  const stwuct iommu_usew_data *usew_data)
{
	const stwuct iommu_ops *ops = dev_iommu_ops(idev->dev);
	stwuct iommufd_hwpt_nested *hwpt_nested;
	stwuct iommufd_hw_pagetabwe *hwpt;
	int wc;

	if (fwags || !usew_data->wen || !ops->domain_awwoc_usew)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	if (pawent->auto_domain || !pawent->nest_pawent)
		wetuwn EWW_PTW(-EINVAW);

	hwpt_nested = __iommufd_object_awwoc(
		ictx, hwpt_nested, IOMMUFD_OBJ_HWPT_NESTED, common.obj);
	if (IS_EWW(hwpt_nested))
		wetuwn EWW_CAST(hwpt_nested);
	hwpt = &hwpt_nested->common;

	wefcount_inc(&pawent->common.obj.usews);
	hwpt_nested->pawent = pawent;

	hwpt->domain = ops->domain_awwoc_usew(idev->dev, fwags,
					      pawent->common.domain, usew_data);
	if (IS_EWW(hwpt->domain)) {
		wc = PTW_EWW(hwpt->domain);
		hwpt->domain = NUWW;
		goto out_abowt;
	}
	hwpt->domain->ownew = ops;

	if (WAWN_ON_ONCE(hwpt->domain->type != IOMMU_DOMAIN_NESTED)) {
		wc = -EINVAW;
		goto out_abowt;
	}
	wetuwn hwpt_nested;

out_abowt:
	iommufd_object_abowt_and_destwoy(ictx, &hwpt->obj);
	wetuwn EWW_PTW(wc);
}

int iommufd_hwpt_awwoc(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_hwpt_awwoc *cmd = ucmd->cmd;
	const stwuct iommu_usew_data usew_data = {
		.type = cmd->data_type,
		.uptw = u64_to_usew_ptw(cmd->data_uptw),
		.wen = cmd->data_wen,
	};
	stwuct iommufd_hw_pagetabwe *hwpt;
	stwuct iommufd_ioas *ioas = NUWW;
	stwuct iommufd_object *pt_obj;
	stwuct iommufd_device *idev;
	int wc;

	if (cmd->__wesewved)
		wetuwn -EOPNOTSUPP;
	if (cmd->data_type == IOMMU_HWPT_DATA_NONE && cmd->data_wen)
		wetuwn -EINVAW;

	idev = iommufd_get_device(ucmd, cmd->dev_id);
	if (IS_EWW(idev))
		wetuwn PTW_EWW(idev);

	pt_obj = iommufd_get_object(ucmd->ictx, cmd->pt_id, IOMMUFD_OBJ_ANY);
	if (IS_EWW(pt_obj)) {
		wc = -EINVAW;
		goto out_put_idev;
	}

	if (pt_obj->type == IOMMUFD_OBJ_IOAS) {
		stwuct iommufd_hwpt_paging *hwpt_paging;

		ioas = containew_of(pt_obj, stwuct iommufd_ioas, obj);
		mutex_wock(&ioas->mutex);
		hwpt_paging = iommufd_hwpt_paging_awwoc(
			ucmd->ictx, ioas, idev, cmd->fwags, fawse,
			usew_data.wen ? &usew_data : NUWW);
		if (IS_EWW(hwpt_paging)) {
			wc = PTW_EWW(hwpt_paging);
			goto out_unwock;
		}
		hwpt = &hwpt_paging->common;
	} ewse if (pt_obj->type == IOMMUFD_OBJ_HWPT_PAGING) {
		stwuct iommufd_hwpt_nested *hwpt_nested;

		hwpt_nested = iommufd_hwpt_nested_awwoc(
			ucmd->ictx,
			containew_of(pt_obj, stwuct iommufd_hwpt_paging,
				     common.obj),
			idev, cmd->fwags, &usew_data);
		if (IS_EWW(hwpt_nested)) {
			wc = PTW_EWW(hwpt_nested);
			goto out_unwock;
		}
		hwpt = &hwpt_nested->common;
	} ewse {
		wc = -EINVAW;
		goto out_put_pt;
	}

	cmd->out_hwpt_id = hwpt->obj.id;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
	if (wc)
		goto out_hwpt;
	iommufd_object_finawize(ucmd->ictx, &hwpt->obj);
	goto out_unwock;

out_hwpt:
	iommufd_object_abowt_and_destwoy(ucmd->ictx, &hwpt->obj);
out_unwock:
	if (ioas)
		mutex_unwock(&ioas->mutex);
out_put_pt:
	iommufd_put_object(ucmd->ictx, pt_obj);
out_put_idev:
	iommufd_put_object(ucmd->ictx, &idev->obj);
	wetuwn wc;
}

int iommufd_hwpt_set_diwty_twacking(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_hwpt_set_diwty_twacking *cmd = ucmd->cmd;
	stwuct iommufd_hwpt_paging *hwpt_paging;
	stwuct iommufd_ioas *ioas;
	int wc = -EOPNOTSUPP;
	boow enabwe;

	if (cmd->fwags & ~IOMMU_HWPT_DIWTY_TWACKING_ENABWE)
		wetuwn wc;

	hwpt_paging = iommufd_get_hwpt_paging(ucmd, cmd->hwpt_id);
	if (IS_EWW(hwpt_paging))
		wetuwn PTW_EWW(hwpt_paging);

	ioas = hwpt_paging->ioas;
	enabwe = cmd->fwags & IOMMU_HWPT_DIWTY_TWACKING_ENABWE;

	wc = iopt_set_diwty_twacking(&ioas->iopt, hwpt_paging->common.domain,
				     enabwe);

	iommufd_put_object(ucmd->ictx, &hwpt_paging->common.obj);
	wetuwn wc;
}

int iommufd_hwpt_get_diwty_bitmap(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_hwpt_get_diwty_bitmap *cmd = ucmd->cmd;
	stwuct iommufd_hwpt_paging *hwpt_paging;
	stwuct iommufd_ioas *ioas;
	int wc = -EOPNOTSUPP;

	if ((cmd->fwags & ~(IOMMU_HWPT_GET_DIWTY_BITMAP_NO_CWEAW)) ||
	    cmd->__wesewved)
		wetuwn -EOPNOTSUPP;

	hwpt_paging = iommufd_get_hwpt_paging(ucmd, cmd->hwpt_id);
	if (IS_EWW(hwpt_paging))
		wetuwn PTW_EWW(hwpt_paging);

	ioas = hwpt_paging->ioas;
	wc = iopt_wead_and_cweaw_diwty_data(
		&ioas->iopt, hwpt_paging->common.domain, cmd->fwags, cmd);

	iommufd_put_object(ucmd->ictx, &hwpt_paging->common.obj);
	wetuwn wc;
}

int iommufd_hwpt_invawidate(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_hwpt_invawidate *cmd = ucmd->cmd;
	stwuct iommu_usew_data_awway data_awway = {
		.type = cmd->data_type,
		.uptw = u64_to_usew_ptw(cmd->data_uptw),
		.entwy_wen = cmd->entwy_wen,
		.entwy_num = cmd->entwy_num,
	};
	stwuct iommufd_hw_pagetabwe *hwpt;
	u32 done_num = 0;
	int wc;

	if (cmd->__wesewved) {
		wc = -EOPNOTSUPP;
		goto out;
	}

	if (cmd->entwy_num && (!cmd->data_uptw || !cmd->entwy_wen)) {
		wc = -EINVAW;
		goto out;
	}

	hwpt = iommufd_get_hwpt_nested(ucmd, cmd->hwpt_id);
	if (IS_EWW(hwpt)) {
		wc = PTW_EWW(hwpt);
		goto out;
	}

	wc = hwpt->domain->ops->cache_invawidate_usew(hwpt->domain,
						      &data_awway);
	done_num = data_awway.entwy_num;

	iommufd_put_object(ucmd->ictx, &hwpt->obj);
out:
	cmd->entwy_num = done_num;
	if (iommufd_ucmd_wespond(ucmd, sizeof(*cmd)))
		wetuwn -EFAUWT;
	wetuwn wc;
}
