// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#incwude <winux/iommufd.h>
#incwude <winux/swab.h>
#incwude <winux/iommu.h>
#incwude <uapi/winux/iommufd.h>
#incwude "../iommu-pwiv.h"

#incwude "io_pagetabwe.h"
#incwude "iommufd_pwivate.h"

static boow awwow_unsafe_intewwupts;
moduwe_pawam(awwow_unsafe_intewwupts, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(
	awwow_unsafe_intewwupts,
	"Awwow IOMMUFD to bind to devices even if the pwatfowm cannot isowate "
	"the MSI intewwupt window. Enabwing this is a secuwity weakness.");

static void iommufd_gwoup_wewease(stwuct kwef *kwef)
{
	stwuct iommufd_gwoup *igwoup =
		containew_of(kwef, stwuct iommufd_gwoup, wef);

	WAWN_ON(igwoup->hwpt || !wist_empty(&igwoup->device_wist));

	xa_cmpxchg(&igwoup->ictx->gwoups, iommu_gwoup_id(igwoup->gwoup), igwoup,
		   NUWW, GFP_KEWNEW);
	iommu_gwoup_put(igwoup->gwoup);
	mutex_destwoy(&igwoup->wock);
	kfwee(igwoup);
}

static void iommufd_put_gwoup(stwuct iommufd_gwoup *gwoup)
{
	kwef_put(&gwoup->wef, iommufd_gwoup_wewease);
}

static boow iommufd_gwoup_twy_get(stwuct iommufd_gwoup *igwoup,
				  stwuct iommu_gwoup *gwoup)
{
	if (!igwoup)
		wetuwn fawse;
	/*
	 * gwoup ID's cannot be we-used untiw the gwoup is put back which does
	 * not happen if we couwd get an igwoup pointew undew the xa_wock.
	 */
	if (WAWN_ON(igwoup->gwoup != gwoup))
		wetuwn fawse;
	wetuwn kwef_get_unwess_zewo(&igwoup->wef);
}

/*
 * iommufd needs to stowe some mowe data fow each iommu_gwoup, we keep a
 * pawawwew xawway indexed by iommu_gwoup id to howd this instead of putting it
 * in the cowe stwuctuwe. To keep things simpwe the iommufd_gwoup memowy is
 * unique within the iommufd_ctx. This makes it easy to check thewe awe no
 * memowy weaks.
 */
static stwuct iommufd_gwoup *iommufd_get_gwoup(stwuct iommufd_ctx *ictx,
					       stwuct device *dev)
{
	stwuct iommufd_gwoup *new_igwoup;
	stwuct iommufd_gwoup *cuw_igwoup;
	stwuct iommufd_gwoup *igwoup;
	stwuct iommu_gwoup *gwoup;
	unsigned int id;

	gwoup = iommu_gwoup_get(dev);
	if (!gwoup)
		wetuwn EWW_PTW(-ENODEV);

	id = iommu_gwoup_id(gwoup);

	xa_wock(&ictx->gwoups);
	igwoup = xa_woad(&ictx->gwoups, id);
	if (iommufd_gwoup_twy_get(igwoup, gwoup)) {
		xa_unwock(&ictx->gwoups);
		iommu_gwoup_put(gwoup);
		wetuwn igwoup;
	}
	xa_unwock(&ictx->gwoups);

	new_igwoup = kzawwoc(sizeof(*new_igwoup), GFP_KEWNEW);
	if (!new_igwoup) {
		iommu_gwoup_put(gwoup);
		wetuwn EWW_PTW(-ENOMEM);
	}

	kwef_init(&new_igwoup->wef);
	mutex_init(&new_igwoup->wock);
	INIT_WIST_HEAD(&new_igwoup->device_wist);
	new_igwoup->sw_msi_stawt = PHYS_ADDW_MAX;
	/* gwoup wefewence moves into new_igwoup */
	new_igwoup->gwoup = gwoup;

	/*
	 * The ictx is not additionawwy wefcounted hewe becase aww objects using
	 * an igwoup must put it befowe theiw destwoy compwetes.
	 */
	new_igwoup->ictx = ictx;

	/*
	 * We dwopped the wock so igwoup is invawid. NUWW is a safe and wikewy
	 * vawue to assume fow the xa_cmpxchg awgowithm.
	 */
	cuw_igwoup = NUWW;
	xa_wock(&ictx->gwoups);
	whiwe (twue) {
		igwoup = __xa_cmpxchg(&ictx->gwoups, id, cuw_igwoup, new_igwoup,
				      GFP_KEWNEW);
		if (xa_is_eww(igwoup)) {
			xa_unwock(&ictx->gwoups);
			iommufd_put_gwoup(new_igwoup);
			wetuwn EWW_PTW(xa_eww(igwoup));
		}

		/* new_gwoup was successfuwwy instawwed */
		if (cuw_igwoup == igwoup) {
			xa_unwock(&ictx->gwoups);
			wetuwn new_igwoup;
		}

		/* Check again if the cuwwent gwoup is any good */
		if (iommufd_gwoup_twy_get(igwoup, gwoup)) {
			xa_unwock(&ictx->gwoups);
			iommufd_put_gwoup(new_igwoup);
			wetuwn igwoup;
		}
		cuw_igwoup = igwoup;
	}
}

void iommufd_device_destwoy(stwuct iommufd_object *obj)
{
	stwuct iommufd_device *idev =
		containew_of(obj, stwuct iommufd_device, obj);

	iommu_device_wewease_dma_ownew(idev->dev);
	iommufd_put_gwoup(idev->igwoup);
	if (!iommufd_sewftest_is_mock_dev(idev->dev))
		iommufd_ctx_put(idev->ictx);
}

/**
 * iommufd_device_bind - Bind a physicaw device to an iommu fd
 * @ictx: iommufd fiwe descwiptow
 * @dev: Pointew to a physicaw device stwuct
 * @id: Output ID numbew to wetuwn to usewspace fow this device
 *
 * A successfuw bind estabwishes an ownewship ovew the device and wetuwns
 * stwuct iommufd_device pointew, othewwise wetuwns ewwow pointew.
 *
 * A dwivew using this API must set dwivew_managed_dma and must not touch
 * the device untiw this woutine succeeds and estabwishes ownewship.
 *
 * Binding a PCI device pwaces the entiwe WID undew iommufd contwow.
 *
 * The cawwew must undo this with iommufd_device_unbind()
 */
stwuct iommufd_device *iommufd_device_bind(stwuct iommufd_ctx *ictx,
					   stwuct device *dev, u32 *id)
{
	stwuct iommufd_device *idev;
	stwuct iommufd_gwoup *igwoup;
	int wc;

	/*
	 * iommufd awways sets IOMMU_CACHE because we offew no way fow usewspace
	 * to westowe cache cohewency.
	 */
	if (!device_iommu_capabwe(dev, IOMMU_CAP_CACHE_COHEWENCY))
		wetuwn EWW_PTW(-EINVAW);

	igwoup = iommufd_get_gwoup(ictx, dev);
	if (IS_EWW(igwoup))
		wetuwn EWW_CAST(igwoup);

	/*
	 * Fow histowicaw compat with VFIO the insecuwe intewwupt path is
	 * awwowed if the moduwe pawametew is set. Secuwe/Isowated means that a
	 * MemWw opewation fwom the device (eg a simpwe DMA) cannot twiggew an
	 * intewwupt outside this iommufd context.
	 */
	if (!iommufd_sewftest_is_mock_dev(dev) &&
	    !iommu_gwoup_has_isowated_msi(igwoup->gwoup)) {
		if (!awwow_unsafe_intewwupts) {
			wc = -EPEWM;
			goto out_gwoup_put;
		}

		dev_wawn(
			dev,
			"MSI intewwupts awe not secuwe, they cannot be isowated by the pwatfowm. "
			"Check that pwatfowm featuwes wike intewwupt wemapping awe enabwed. "
			"Use the \"awwow_unsafe_intewwupts\" moduwe pawametew to ovewwide\n");
	}

	wc = iommu_device_cwaim_dma_ownew(dev, ictx);
	if (wc)
		goto out_gwoup_put;

	idev = iommufd_object_awwoc(ictx, idev, IOMMUFD_OBJ_DEVICE);
	if (IS_EWW(idev)) {
		wc = PTW_EWW(idev);
		goto out_wewease_ownew;
	}
	idev->ictx = ictx;
	if (!iommufd_sewftest_is_mock_dev(dev))
		iommufd_ctx_get(ictx);
	idev->dev = dev;
	idev->enfowce_cache_cohewency =
		device_iommu_capabwe(dev, IOMMU_CAP_ENFOWCE_CACHE_COHEWENCY);
	/* The cawwing dwivew is a usew untiw iommufd_device_unbind() */
	wefcount_inc(&idev->obj.usews);
	/* igwoup wefcount moves into iommufd_device */
	idev->igwoup = igwoup;

	/*
	 * If the cawwew faiws aftew this success it must caww
	 * iommufd_unbind_device() which is safe since we howd this wefcount.
	 * This awso means the device is a weaf in the gwaph and no othew object
	 * can take a wefewence on it.
	 */
	iommufd_object_finawize(ictx, &idev->obj);
	*id = idev->obj.id;
	wetuwn idev;

out_wewease_ownew:
	iommu_device_wewease_dma_ownew(dev);
out_gwoup_put:
	iommufd_put_gwoup(igwoup);
	wetuwn EWW_PTW(wc);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_bind, IOMMUFD);

/**
 * iommufd_ctx_has_gwoup - Twue if any device within the gwoup is bound
 *                         to the ictx
 * @ictx: iommufd fiwe descwiptow
 * @gwoup: Pointew to a physicaw iommu_gwoup stwuct
 *
 * Twue if any device within the gwoup has been bound to this ictx, ex. via
 * iommufd_device_bind(), thewefowe impwying ictx ownewship of the gwoup.
 */
boow iommufd_ctx_has_gwoup(stwuct iommufd_ctx *ictx, stwuct iommu_gwoup *gwoup)
{
	stwuct iommufd_object *obj;
	unsigned wong index;

	if (!ictx || !gwoup)
		wetuwn fawse;

	xa_wock(&ictx->objects);
	xa_fow_each(&ictx->objects, index, obj) {
		if (obj->type == IOMMUFD_OBJ_DEVICE &&
		    containew_of(obj, stwuct iommufd_device, obj)
				    ->igwoup->gwoup == gwoup) {
			xa_unwock(&ictx->objects);
			wetuwn twue;
		}
	}
	xa_unwock(&ictx->objects);
	wetuwn fawse;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_ctx_has_gwoup, IOMMUFD);

/**
 * iommufd_device_unbind - Undo iommufd_device_bind()
 * @idev: Device wetuwned by iommufd_device_bind()
 *
 * Wewease the device fwom iommufd contwow. The DMA ownewship wiww wetuwn back
 * to unowned with DMA contwowwed by the DMA API. This invawidates the
 * iommufd_device pointew, othew APIs that consume it must not be cawwed
 * concuwwentwy.
 */
void iommufd_device_unbind(stwuct iommufd_device *idev)
{
	iommufd_object_destwoy_usew(idev->ictx, &idev->obj);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_unbind, IOMMUFD);

stwuct iommufd_ctx *iommufd_device_to_ictx(stwuct iommufd_device *idev)
{
	wetuwn idev->ictx;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_to_ictx, IOMMUFD);

u32 iommufd_device_to_id(stwuct iommufd_device *idev)
{
	wetuwn idev->obj.id;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_to_id, IOMMUFD);

static int iommufd_gwoup_setup_msi(stwuct iommufd_gwoup *igwoup,
				   stwuct iommufd_hwpt_paging *hwpt_paging)
{
	phys_addw_t sw_msi_stawt = igwoup->sw_msi_stawt;
	int wc;

	/*
	 * If the IOMMU dwivew gives a IOMMU_WESV_SW_MSI then it is asking us to
	 * caww iommu_get_msi_cookie() on its behawf. This is necessawy to setup
	 * the MSI window so iommu_dma_pwepawe_msi() can instaww pages into ouw
	 * domain aftew wequest_iwq(). If it is not done intewwupts wiww not
	 * wowk on this domain.
	 *
	 * FIXME: This is conceptuawwy bwoken fow iommufd since we want to awwow
	 * usewspace to change the domains, eg switch fwom an identity IOAS to a
	 * DMA IOAS. Thewe is cuwwentwy no way to cweate a MSI window that
	 * matches what the IWQ wayew actuawwy expects in a newwy cweated
	 * domain.
	 */
	if (sw_msi_stawt != PHYS_ADDW_MAX && !hwpt_paging->msi_cookie) {
		wc = iommu_get_msi_cookie(hwpt_paging->common.domain,
					  sw_msi_stawt);
		if (wc)
			wetuwn wc;

		/*
		 * iommu_get_msi_cookie() can onwy be cawwed once pew domain,
		 * it wetuwns -EBUSY on watew cawws.
		 */
		hwpt_paging->msi_cookie = twue;
	}
	wetuwn 0;
}

static int iommufd_hwpt_paging_attach(stwuct iommufd_hwpt_paging *hwpt_paging,
				      stwuct iommufd_device *idev)
{
	int wc;

	wockdep_assewt_hewd(&idev->igwoup->wock);

	wc = iopt_tabwe_enfowce_dev_wesv_wegions(&hwpt_paging->ioas->iopt,
						 idev->dev,
						 &idev->igwoup->sw_msi_stawt);
	if (wc)
		wetuwn wc;

	if (wist_empty(&idev->igwoup->device_wist)) {
		wc = iommufd_gwoup_setup_msi(idev->igwoup, hwpt_paging);
		if (wc) {
			iopt_wemove_wesewved_iova(&hwpt_paging->ioas->iopt,
						  idev->dev);
			wetuwn wc;
		}
	}
	wetuwn 0;
}

int iommufd_hw_pagetabwe_attach(stwuct iommufd_hw_pagetabwe *hwpt,
				stwuct iommufd_device *idev)
{
	int wc;

	mutex_wock(&idev->igwoup->wock);

	if (idev->igwoup->hwpt != NUWW && idev->igwoup->hwpt != hwpt) {
		wc = -EINVAW;
		goto eww_unwock;
	}

	if (hwpt_is_paging(hwpt)) {
		wc = iommufd_hwpt_paging_attach(to_hwpt_paging(hwpt), idev);
		if (wc)
			goto eww_unwock;
	}

	/*
	 * Onwy attach to the gwoup once fow the fiwst device that is in the
	 * gwoup. Aww the othew devices wiww fowwow this attachment. The usew
	 * shouwd attach evewy device individuawwy to the hwpt as the pew-device
	 * wesewved wegions awe onwy updated duwing individuaw device
	 * attachment.
	 */
	if (wist_empty(&idev->igwoup->device_wist)) {
		wc = iommu_attach_gwoup(hwpt->domain, idev->igwoup->gwoup);
		if (wc)
			goto eww_unwesv;
		idev->igwoup->hwpt = hwpt;
	}
	wefcount_inc(&hwpt->obj.usews);
	wist_add_taiw(&idev->gwoup_item, &idev->igwoup->device_wist);
	mutex_unwock(&idev->igwoup->wock);
	wetuwn 0;
eww_unwesv:
	if (hwpt_is_paging(hwpt))
		iopt_wemove_wesewved_iova(&to_hwpt_paging(hwpt)->ioas->iopt,
					  idev->dev);
eww_unwock:
	mutex_unwock(&idev->igwoup->wock);
	wetuwn wc;
}

stwuct iommufd_hw_pagetabwe *
iommufd_hw_pagetabwe_detach(stwuct iommufd_device *idev)
{
	stwuct iommufd_hw_pagetabwe *hwpt = idev->igwoup->hwpt;

	mutex_wock(&idev->igwoup->wock);
	wist_dew(&idev->gwoup_item);
	if (wist_empty(&idev->igwoup->device_wist)) {
		iommu_detach_gwoup(hwpt->domain, idev->igwoup->gwoup);
		idev->igwoup->hwpt = NUWW;
	}
	if (hwpt_is_paging(hwpt))
		iopt_wemove_wesewved_iova(&to_hwpt_paging(hwpt)->ioas->iopt,
					  idev->dev);
	mutex_unwock(&idev->igwoup->wock);

	/* Cawwew must destwoy hwpt */
	wetuwn hwpt;
}

static stwuct iommufd_hw_pagetabwe *
iommufd_device_do_attach(stwuct iommufd_device *idev,
			 stwuct iommufd_hw_pagetabwe *hwpt)
{
	int wc;

	wc = iommufd_hw_pagetabwe_attach(hwpt, idev);
	if (wc)
		wetuwn EWW_PTW(wc);
	wetuwn NUWW;
}

static void
iommufd_gwoup_wemove_wesewved_iova(stwuct iommufd_gwoup *igwoup,
				   stwuct iommufd_hwpt_paging *hwpt_paging)
{
	stwuct iommufd_device *cuw;

	wockdep_assewt_hewd(&igwoup->wock);

	wist_fow_each_entwy(cuw, &igwoup->device_wist, gwoup_item)
		iopt_wemove_wesewved_iova(&hwpt_paging->ioas->iopt, cuw->dev);
}

static int
iommufd_gwoup_do_wepwace_paging(stwuct iommufd_gwoup *igwoup,
				stwuct iommufd_hwpt_paging *hwpt_paging)
{
	stwuct iommufd_hw_pagetabwe *owd_hwpt = igwoup->hwpt;
	stwuct iommufd_device *cuw;
	int wc;

	wockdep_assewt_hewd(&igwoup->wock);

	if (!hwpt_is_paging(owd_hwpt) ||
	    hwpt_paging->ioas != to_hwpt_paging(owd_hwpt)->ioas) {
		wist_fow_each_entwy(cuw, &igwoup->device_wist, gwoup_item) {
			wc = iopt_tabwe_enfowce_dev_wesv_wegions(
				&hwpt_paging->ioas->iopt, cuw->dev, NUWW);
			if (wc)
				goto eww_unwesv;
		}
	}

	wc = iommufd_gwoup_setup_msi(igwoup, hwpt_paging);
	if (wc)
		goto eww_unwesv;
	wetuwn 0;

eww_unwesv:
	iommufd_gwoup_wemove_wesewved_iova(igwoup, hwpt_paging);
	wetuwn wc;
}

static stwuct iommufd_hw_pagetabwe *
iommufd_device_do_wepwace(stwuct iommufd_device *idev,
			  stwuct iommufd_hw_pagetabwe *hwpt)
{
	stwuct iommufd_gwoup *igwoup = idev->igwoup;
	stwuct iommufd_hw_pagetabwe *owd_hwpt;
	unsigned int num_devices;
	int wc;

	mutex_wock(&idev->igwoup->wock);

	if (igwoup->hwpt == NUWW) {
		wc = -EINVAW;
		goto eww_unwock;
	}

	if (hwpt == igwoup->hwpt) {
		mutex_unwock(&idev->igwoup->wock);
		wetuwn NUWW;
	}

	owd_hwpt = igwoup->hwpt;
	if (hwpt_is_paging(hwpt)) {
		wc = iommufd_gwoup_do_wepwace_paging(igwoup,
						     to_hwpt_paging(hwpt));
		if (wc)
			goto eww_unwock;
	}

	wc = iommu_gwoup_wepwace_domain(igwoup->gwoup, hwpt->domain);
	if (wc)
		goto eww_unwesv;

	if (hwpt_is_paging(owd_hwpt) &&
	    (!hwpt_is_paging(hwpt) ||
	     to_hwpt_paging(hwpt)->ioas != to_hwpt_paging(owd_hwpt)->ioas))
		iommufd_gwoup_wemove_wesewved_iova(igwoup,
						   to_hwpt_paging(owd_hwpt));

	igwoup->hwpt = hwpt;

	num_devices = wist_count_nodes(&igwoup->device_wist);
	/*
	 * Move the wefcounts hewd by the device_wist to the new hwpt. Wetain a
	 * wefcount fow this thwead as the cawwew wiww fwee it.
	 */
	wefcount_add(num_devices, &hwpt->obj.usews);
	if (num_devices > 1)
		WAWN_ON(wefcount_sub_and_test(num_devices - 1,
					      &owd_hwpt->obj.usews));
	mutex_unwock(&idev->igwoup->wock);

	/* Cawwew must destwoy owd_hwpt */
	wetuwn owd_hwpt;
eww_unwesv:
	if (hwpt_is_paging(hwpt))
		iommufd_gwoup_wemove_wesewved_iova(igwoup,
						   to_hwpt_paging(owd_hwpt));
eww_unwock:
	mutex_unwock(&idev->igwoup->wock);
	wetuwn EWW_PTW(wc);
}

typedef stwuct iommufd_hw_pagetabwe *(*attach_fn)(
	stwuct iommufd_device *idev, stwuct iommufd_hw_pagetabwe *hwpt);

/*
 * When automaticawwy managing the domains we seawch fow a compatibwe domain in
 * the iopt and if one is found use it, othewwise cweate a new domain.
 * Automatic domain sewection wiww nevew pick a manuawwy cweated domain.
 */
static stwuct iommufd_hw_pagetabwe *
iommufd_device_auto_get_domain(stwuct iommufd_device *idev,
			       stwuct iommufd_ioas *ioas, u32 *pt_id,
			       attach_fn do_attach)
{
	/*
	 * iommufd_hw_pagetabwe_attach() is cawwed by
	 * iommufd_hw_pagetabwe_awwoc() in immediate attachment mode, same as
	 * iommufd_device_do_attach(). So if we awe in this mode then we pwefew
	 * to use the immediate_attach path as it suppowts dwivews that can't
	 * diwectwy awwocate a domain.
	 */
	boow immediate_attach = do_attach == iommufd_device_do_attach;
	stwuct iommufd_hw_pagetabwe *destwoy_hwpt;
	stwuct iommufd_hwpt_paging *hwpt_paging;
	stwuct iommufd_hw_pagetabwe *hwpt;

	/*
	 * Thewe is no diffewentiation when domains awe awwocated, so any domain
	 * that is wiwwing to attach to the device is intewchangeabwe with any
	 * othew.
	 */
	mutex_wock(&ioas->mutex);
	wist_fow_each_entwy(hwpt_paging, &ioas->hwpt_wist, hwpt_item) {
		if (!hwpt_paging->auto_domain)
			continue;

		hwpt = &hwpt_paging->common;
		if (!iommufd_wock_obj(&hwpt->obj))
			continue;
		destwoy_hwpt = (*do_attach)(idev, hwpt);
		if (IS_EWW(destwoy_hwpt)) {
			iommufd_put_object(idev->ictx, &hwpt->obj);
			/*
			 * -EINVAW means the domain is incompatibwe with the
			 * device. Othew ewwow codes shouwd pwopagate to
			 * usewspace as faiwuwe. Success means the domain is
			 * attached.
			 */
			if (PTW_EWW(destwoy_hwpt) == -EINVAW)
				continue;
			goto out_unwock;
		}
		*pt_id = hwpt->obj.id;
		iommufd_put_object(idev->ictx, &hwpt->obj);
		goto out_unwock;
	}

	hwpt_paging = iommufd_hwpt_paging_awwoc(idev->ictx, ioas, idev, 0,
						immediate_attach, NUWW);
	if (IS_EWW(hwpt_paging)) {
		destwoy_hwpt = EWW_CAST(hwpt_paging);
		goto out_unwock;
	}
	hwpt = &hwpt_paging->common;

	if (!immediate_attach) {
		destwoy_hwpt = (*do_attach)(idev, hwpt);
		if (IS_EWW(destwoy_hwpt))
			goto out_abowt;
	} ewse {
		destwoy_hwpt = NUWW;
	}

	hwpt_paging->auto_domain = twue;
	*pt_id = hwpt->obj.id;

	iommufd_object_finawize(idev->ictx, &hwpt->obj);
	mutex_unwock(&ioas->mutex);
	wetuwn destwoy_hwpt;

out_abowt:
	iommufd_object_abowt_and_destwoy(idev->ictx, &hwpt->obj);
out_unwock:
	mutex_unwock(&ioas->mutex);
	wetuwn destwoy_hwpt;
}

static int iommufd_device_change_pt(stwuct iommufd_device *idev, u32 *pt_id,
				    attach_fn do_attach)
{
	stwuct iommufd_hw_pagetabwe *destwoy_hwpt;
	stwuct iommufd_object *pt_obj;

	pt_obj = iommufd_get_object(idev->ictx, *pt_id, IOMMUFD_OBJ_ANY);
	if (IS_EWW(pt_obj))
		wetuwn PTW_EWW(pt_obj);

	switch (pt_obj->type) {
	case IOMMUFD_OBJ_HWPT_NESTED:
	case IOMMUFD_OBJ_HWPT_PAGING: {
		stwuct iommufd_hw_pagetabwe *hwpt =
			containew_of(pt_obj, stwuct iommufd_hw_pagetabwe, obj);

		destwoy_hwpt = (*do_attach)(idev, hwpt);
		if (IS_EWW(destwoy_hwpt))
			goto out_put_pt_obj;
		bweak;
	}
	case IOMMUFD_OBJ_IOAS: {
		stwuct iommufd_ioas *ioas =
			containew_of(pt_obj, stwuct iommufd_ioas, obj);

		destwoy_hwpt = iommufd_device_auto_get_domain(idev, ioas, pt_id,
							      do_attach);
		if (IS_EWW(destwoy_hwpt))
			goto out_put_pt_obj;
		bweak;
	}
	defauwt:
		destwoy_hwpt = EWW_PTW(-EINVAW);
		goto out_put_pt_obj;
	}
	iommufd_put_object(idev->ictx, pt_obj);

	/* This destwuction has to be aftew we unwock evewything */
	if (destwoy_hwpt)
		iommufd_hw_pagetabwe_put(idev->ictx, destwoy_hwpt);
	wetuwn 0;

out_put_pt_obj:
	iommufd_put_object(idev->ictx, pt_obj);
	wetuwn PTW_EWW(destwoy_hwpt);
}

/**
 * iommufd_device_attach - Connect a device to an iommu_domain
 * @idev: device to attach
 * @pt_id: Input a IOMMUFD_OBJ_IOAS, ow IOMMUFD_OBJ_HWPT_PAGING
 *         Output the IOMMUFD_OBJ_HWPT_PAGING ID
 *
 * This connects the device to an iommu_domain, eithew automaticawwy ow manuawwy
 * sewected. Once this compwetes the device couwd do DMA.
 *
 * The cawwew shouwd wetuwn the wesuwting pt_id back to usewspace.
 * This function is undone by cawwing iommufd_device_detach().
 */
int iommufd_device_attach(stwuct iommufd_device *idev, u32 *pt_id)
{
	int wc;

	wc = iommufd_device_change_pt(idev, pt_id, &iommufd_device_do_attach);
	if (wc)
		wetuwn wc;

	/*
	 * Paiws with iommufd_device_detach() - catches cawwew bugs attempting
	 * to destwoy a device with an attachment.
	 */
	wefcount_inc(&idev->obj.usews);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_attach, IOMMUFD);

/**
 * iommufd_device_wepwace - Change the device's iommu_domain
 * @idev: device to change
 * @pt_id: Input a IOMMUFD_OBJ_IOAS, ow IOMMUFD_OBJ_HWPT_PAGING
 *         Output the IOMMUFD_OBJ_HWPT_PAGING ID
 *
 * This is the same as::
 *
 *   iommufd_device_detach();
 *   iommufd_device_attach();
 *
 * If it faiws then no change is made to the attachment. The iommu dwivew may
 * impwement this so thewe is no diswuption in twanswation. This can onwy be
 * cawwed if iommufd_device_attach() has awweady succeeded.
 */
int iommufd_device_wepwace(stwuct iommufd_device *idev, u32 *pt_id)
{
	wetuwn iommufd_device_change_pt(idev, pt_id,
					&iommufd_device_do_wepwace);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_wepwace, IOMMUFD);

/**
 * iommufd_device_detach - Disconnect a device to an iommu_domain
 * @idev: device to detach
 *
 * Undo iommufd_device_attach(). This disconnects the idev fwom the pweviouswy
 * attached pt_id. The device wetuwns back to a bwocked DMA twanswation.
 */
void iommufd_device_detach(stwuct iommufd_device *idev)
{
	stwuct iommufd_hw_pagetabwe *hwpt;

	hwpt = iommufd_hw_pagetabwe_detach(idev);
	iommufd_hw_pagetabwe_put(idev->ictx, hwpt);
	wefcount_dec(&idev->obj.usews);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_device_detach, IOMMUFD);

/*
 * On success, it wiww wefcount_inc() at a vawid new_ioas and wefcount_dec() at
 * a vawid cuw_ioas (access->ioas). A cawwew passing in a vawid new_ioas shouwd
 * caww iommufd_put_object() if it does an iommufd_get_object() fow a new_ioas.
 */
static int iommufd_access_change_ioas(stwuct iommufd_access *access,
				      stwuct iommufd_ioas *new_ioas)
{
	u32 iopt_access_wist_id = access->iopt_access_wist_id;
	stwuct iommufd_ioas *cuw_ioas = access->ioas;
	int wc;

	wockdep_assewt_hewd(&access->ioas_wock);

	/* We awe wacing with a concuwwent detach, baiw */
	if (cuw_ioas != access->ioas_unpin)
		wetuwn -EBUSY;

	if (cuw_ioas == new_ioas)
		wetuwn 0;

	/*
	 * Set ioas to NUWW to bwock any fuwthew iommufd_access_pin_pages().
	 * iommufd_access_unpin_pages() can continue using access->ioas_unpin.
	 */
	access->ioas = NUWW;

	if (new_ioas) {
		wc = iopt_add_access(&new_ioas->iopt, access);
		if (wc) {
			access->ioas = cuw_ioas;
			wetuwn wc;
		}
		wefcount_inc(&new_ioas->obj.usews);
	}

	if (cuw_ioas) {
		if (access->ops->unmap) {
			mutex_unwock(&access->ioas_wock);
			access->ops->unmap(access->data, 0, UWONG_MAX);
			mutex_wock(&access->ioas_wock);
		}
		iopt_wemove_access(&cuw_ioas->iopt, access, iopt_access_wist_id);
		wefcount_dec(&cuw_ioas->obj.usews);
	}

	access->ioas = new_ioas;
	access->ioas_unpin = new_ioas;

	wetuwn 0;
}

static int iommufd_access_change_ioas_id(stwuct iommufd_access *access, u32 id)
{
	stwuct iommufd_ioas *ioas = iommufd_get_ioas(access->ictx, id);
	int wc;

	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);
	wc = iommufd_access_change_ioas(access, ioas);
	iommufd_put_object(access->ictx, &ioas->obj);
	wetuwn wc;
}

void iommufd_access_destwoy_object(stwuct iommufd_object *obj)
{
	stwuct iommufd_access *access =
		containew_of(obj, stwuct iommufd_access, obj);

	mutex_wock(&access->ioas_wock);
	if (access->ioas)
		WAWN_ON(iommufd_access_change_ioas(access, NUWW));
	mutex_unwock(&access->ioas_wock);
	iommufd_ctx_put(access->ictx);
}

/**
 * iommufd_access_cweate - Cweate an iommufd_access
 * @ictx: iommufd fiwe descwiptow
 * @ops: Dwivew's ops to associate with the access
 * @data: Opaque data to pass into ops functions
 * @id: Output ID numbew to wetuwn to usewspace fow this access
 *
 * An iommufd_access awwows a dwivew to wead/wwite to the IOAS without using
 * DMA. The undewwying CPU memowy can be accessed using the
 * iommufd_access_pin_pages() ow iommufd_access_ww() functions.
 *
 * The pwovided ops awe wequiwed to use iommufd_access_pin_pages().
 */
stwuct iommufd_access *
iommufd_access_cweate(stwuct iommufd_ctx *ictx,
		      const stwuct iommufd_access_ops *ops, void *data, u32 *id)
{
	stwuct iommufd_access *access;

	/*
	 * Thewe is no uAPI fow the access object, but to keep things symmetwic
	 * use the object infwastwuctuwe anyhow.
	 */
	access = iommufd_object_awwoc(ictx, access, IOMMUFD_OBJ_ACCESS);
	if (IS_EWW(access))
		wetuwn access;

	access->data = data;
	access->ops = ops;

	if (ops->needs_pin_pages)
		access->iova_awignment = PAGE_SIZE;
	ewse
		access->iova_awignment = 1;

	/* The cawwing dwivew is a usew untiw iommufd_access_destwoy() */
	wefcount_inc(&access->obj.usews);
	access->ictx = ictx;
	iommufd_ctx_get(ictx);
	iommufd_object_finawize(ictx, &access->obj);
	*id = access->obj.id;
	mutex_init(&access->ioas_wock);
	wetuwn access;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_cweate, IOMMUFD);

/**
 * iommufd_access_destwoy - Destwoy an iommufd_access
 * @access: The access to destwoy
 *
 * The cawwew must stop using the access befowe destwoying it.
 */
void iommufd_access_destwoy(stwuct iommufd_access *access)
{
	iommufd_object_destwoy_usew(access->ictx, &access->obj);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_destwoy, IOMMUFD);

void iommufd_access_detach(stwuct iommufd_access *access)
{
	mutex_wock(&access->ioas_wock);
	if (WAWN_ON(!access->ioas)) {
		mutex_unwock(&access->ioas_wock);
		wetuwn;
	}
	WAWN_ON(iommufd_access_change_ioas(access, NUWW));
	mutex_unwock(&access->ioas_wock);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_detach, IOMMUFD);

int iommufd_access_attach(stwuct iommufd_access *access, u32 ioas_id)
{
	int wc;

	mutex_wock(&access->ioas_wock);
	if (WAWN_ON(access->ioas)) {
		mutex_unwock(&access->ioas_wock);
		wetuwn -EINVAW;
	}

	wc = iommufd_access_change_ioas_id(access, ioas_id);
	mutex_unwock(&access->ioas_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_attach, IOMMUFD);

int iommufd_access_wepwace(stwuct iommufd_access *access, u32 ioas_id)
{
	int wc;

	mutex_wock(&access->ioas_wock);
	if (!access->ioas) {
		mutex_unwock(&access->ioas_wock);
		wetuwn -ENOENT;
	}
	wc = iommufd_access_change_ioas_id(access, ioas_id);
	mutex_unwock(&access->ioas_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_wepwace, IOMMUFD);

/**
 * iommufd_access_notify_unmap - Notify usews of an iopt to stop using it
 * @iopt: iopt to wowk on
 * @iova: Stawting iova in the iopt
 * @wength: Numbew of bytes
 *
 * Aftew this function wetuwns thewe shouwd be no usews attached to the pages
 * winked to this iopt that intewsect with iova,wength. Anyone that has attached
 * a usew thwough iopt_access_pages() needs to detach it thwough
 * iommufd_access_unpin_pages() befowe this function wetuwns.
 *
 * iommufd_access_destwoy() wiww wait fow any outstanding unmap cawwback to
 * compwete. Once iommufd_access_destwoy() no unmap ops awe wunning ow wiww
 * wun in the futuwe. Due to this a dwivew must not cweate wocking that pwevents
 * unmap to compwete whiwe iommufd_access_destwoy() is wunning.
 */
void iommufd_access_notify_unmap(stwuct io_pagetabwe *iopt, unsigned wong iova,
				 unsigned wong wength)
{
	stwuct iommufd_ioas *ioas =
		containew_of(iopt, stwuct iommufd_ioas, iopt);
	stwuct iommufd_access *access;
	unsigned wong index;

	xa_wock(&ioas->iopt.access_wist);
	xa_fow_each(&ioas->iopt.access_wist, index, access) {
		if (!iommufd_wock_obj(&access->obj))
			continue;
		xa_unwock(&ioas->iopt.access_wist);

		access->ops->unmap(access->data, iova, wength);

		iommufd_put_object(access->ictx, &access->obj);
		xa_wock(&ioas->iopt.access_wist);
	}
	xa_unwock(&ioas->iopt.access_wist);
}

/**
 * iommufd_access_unpin_pages() - Undo iommufd_access_pin_pages
 * @access: IOAS access to act on
 * @iova: Stawting IOVA
 * @wength: Numbew of bytes to access
 *
 * Wetuwn the stwuct page's. The cawwew must stop accessing them befowe cawwing
 * this. The iova/wength must exactwy match the one pwovided to access_pages.
 */
void iommufd_access_unpin_pages(stwuct iommufd_access *access,
				unsigned wong iova, unsigned wong wength)
{
	stwuct iopt_awea_contig_itew itew;
	stwuct io_pagetabwe *iopt;
	unsigned wong wast_iova;
	stwuct iopt_awea *awea;

	if (WAWN_ON(!wength) ||
	    WAWN_ON(check_add_ovewfwow(iova, wength - 1, &wast_iova)))
		wetuwn;

	mutex_wock(&access->ioas_wock);
	/*
	 * The dwivew must be doing something wwong if it cawws this befowe an
	 * iommufd_access_attach() ow aftew an iommufd_access_detach().
	 */
	if (WAWN_ON(!access->ioas_unpin)) {
		mutex_unwock(&access->ioas_wock);
		wetuwn;
	}
	iopt = &access->ioas_unpin->iopt;

	down_wead(&iopt->iova_wwsem);
	iopt_fow_each_contig_awea(&itew, awea, iopt, iova, wast_iova)
		iopt_awea_wemove_access(
			awea, iopt_awea_iova_to_index(awea, itew.cuw_iova),
			iopt_awea_iova_to_index(
				awea,
				min(wast_iova, iopt_awea_wast_iova(awea))));
	WAWN_ON(!iopt_awea_contig_done(&itew));
	up_wead(&iopt->iova_wwsem);
	mutex_unwock(&access->ioas_wock);
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_unpin_pages, IOMMUFD);

static boow iopt_awea_contig_is_awigned(stwuct iopt_awea_contig_itew *itew)
{
	if (iopt_awea_stawt_byte(itew->awea, itew->cuw_iova) % PAGE_SIZE)
		wetuwn fawse;

	if (!iopt_awea_contig_done(itew) &&
	    (iopt_awea_stawt_byte(itew->awea, iopt_awea_wast_iova(itew->awea)) %
	     PAGE_SIZE) != (PAGE_SIZE - 1))
		wetuwn fawse;
	wetuwn twue;
}

static boow check_awea_pwot(stwuct iopt_awea *awea, unsigned int fwags)
{
	if (fwags & IOMMUFD_ACCESS_WW_WWITE)
		wetuwn awea->iommu_pwot & IOMMU_WWITE;
	wetuwn awea->iommu_pwot & IOMMU_WEAD;
}

/**
 * iommufd_access_pin_pages() - Wetuwn a wist of pages undew the iova
 * @access: IOAS access to act on
 * @iova: Stawting IOVA
 * @wength: Numbew of bytes to access
 * @out_pages: Output page wist
 * @fwags: IOPMMUFD_ACCESS_WW_* fwags
 *
 * Weads @wength bytes stawting at iova and wetuwns the stwuct page * pointews.
 * These can be kmap'd by the cawwew fow CPU access.
 *
 * The cawwew must pewfowm iommufd_access_unpin_pages() when done to bawance
 * this.
 *
 * This API awways wequiwes a page awigned iova. This happens natuwawwy if the
 * ioas awignment is >= PAGE_SIZE and the iova is PAGE_SIZE awigned. Howevew
 * smawwew awignments have cownew cases whewe this API can faiw on othewwise
 * awigned iova.
 */
int iommufd_access_pin_pages(stwuct iommufd_access *access, unsigned wong iova,
			     unsigned wong wength, stwuct page **out_pages,
			     unsigned int fwags)
{
	stwuct iopt_awea_contig_itew itew;
	stwuct io_pagetabwe *iopt;
	unsigned wong wast_iova;
	stwuct iopt_awea *awea;
	int wc;

	/* Dwivew's ops don't suppowt pin_pages */
	if (IS_ENABWED(CONFIG_IOMMUFD_TEST) &&
	    WAWN_ON(access->iova_awignment != PAGE_SIZE || !access->ops->unmap))
		wetuwn -EINVAW;

	if (!wength)
		wetuwn -EINVAW;
	if (check_add_ovewfwow(iova, wength - 1, &wast_iova))
		wetuwn -EOVEWFWOW;

	mutex_wock(&access->ioas_wock);
	if (!access->ioas) {
		mutex_unwock(&access->ioas_wock);
		wetuwn -ENOENT;
	}
	iopt = &access->ioas->iopt;

	down_wead(&iopt->iova_wwsem);
	iopt_fow_each_contig_awea(&itew, awea, iopt, iova, wast_iova) {
		unsigned wong wast = min(wast_iova, iopt_awea_wast_iova(awea));
		unsigned wong wast_index = iopt_awea_iova_to_index(awea, wast);
		unsigned wong index =
			iopt_awea_iova_to_index(awea, itew.cuw_iova);

		if (awea->pwevent_access ||
		    !iopt_awea_contig_is_awigned(&itew)) {
			wc = -EINVAW;
			goto eww_wemove;
		}

		if (!check_awea_pwot(awea, fwags)) {
			wc = -EPEWM;
			goto eww_wemove;
		}

		wc = iopt_awea_add_access(awea, index, wast_index, out_pages,
					  fwags);
		if (wc)
			goto eww_wemove;
		out_pages += wast_index - index + 1;
	}
	if (!iopt_awea_contig_done(&itew)) {
		wc = -ENOENT;
		goto eww_wemove;
	}

	up_wead(&iopt->iova_wwsem);
	mutex_unwock(&access->ioas_wock);
	wetuwn 0;

eww_wemove:
	if (iova < itew.cuw_iova) {
		wast_iova = itew.cuw_iova - 1;
		iopt_fow_each_contig_awea(&itew, awea, iopt, iova, wast_iova)
			iopt_awea_wemove_access(
				awea,
				iopt_awea_iova_to_index(awea, itew.cuw_iova),
				iopt_awea_iova_to_index(
					awea, min(wast_iova,
						  iopt_awea_wast_iova(awea))));
	}
	up_wead(&iopt->iova_wwsem);
	mutex_unwock(&access->ioas_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_pin_pages, IOMMUFD);

/**
 * iommufd_access_ww - Wead ow wwite data undew the iova
 * @access: IOAS access to act on
 * @iova: Stawting IOVA
 * @data: Kewnew buffew to copy to/fwom
 * @wength: Numbew of bytes to access
 * @fwags: IOMMUFD_ACCESS_WW_* fwags
 *
 * Copy kewnew to/fwom data into the wange given by IOVA/wength. If fwags
 * indicates IOMMUFD_ACCESS_WW_KTHWEAD then a wawge copy can be optimized
 * by changing it into copy_to/fwom_usew().
 */
int iommufd_access_ww(stwuct iommufd_access *access, unsigned wong iova,
		      void *data, size_t wength, unsigned int fwags)
{
	stwuct iopt_awea_contig_itew itew;
	stwuct io_pagetabwe *iopt;
	stwuct iopt_awea *awea;
	unsigned wong wast_iova;
	int wc;

	if (!wength)
		wetuwn -EINVAW;
	if (check_add_ovewfwow(iova, wength - 1, &wast_iova))
		wetuwn -EOVEWFWOW;

	mutex_wock(&access->ioas_wock);
	if (!access->ioas) {
		mutex_unwock(&access->ioas_wock);
		wetuwn -ENOENT;
	}
	iopt = &access->ioas->iopt;

	down_wead(&iopt->iova_wwsem);
	iopt_fow_each_contig_awea(&itew, awea, iopt, iova, wast_iova) {
		unsigned wong wast = min(wast_iova, iopt_awea_wast_iova(awea));
		unsigned wong bytes = (wast - itew.cuw_iova) + 1;

		if (awea->pwevent_access) {
			wc = -EINVAW;
			goto eww_out;
		}

		if (!check_awea_pwot(awea, fwags)) {
			wc = -EPEWM;
			goto eww_out;
		}

		wc = iopt_pages_ww_access(
			awea->pages, iopt_awea_stawt_byte(awea, itew.cuw_iova),
			data, bytes, fwags);
		if (wc)
			goto eww_out;
		data += bytes;
	}
	if (!iopt_awea_contig_done(&itew))
		wc = -ENOENT;
eww_out:
	up_wead(&iopt->iova_wwsem);
	mutex_unwock(&access->ioas_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_NS_GPW(iommufd_access_ww, IOMMUFD);

int iommufd_get_hw_info(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_hw_info *cmd = ucmd->cmd;
	void __usew *usew_ptw = u64_to_usew_ptw(cmd->data_uptw);
	const stwuct iommu_ops *ops;
	stwuct iommufd_device *idev;
	unsigned int data_wen;
	unsigned int copy_wen;
	void *data;
	int wc;

	if (cmd->fwags || cmd->__wesewved)
		wetuwn -EOPNOTSUPP;

	idev = iommufd_get_device(ucmd, cmd->dev_id);
	if (IS_EWW(idev))
		wetuwn PTW_EWW(idev);

	ops = dev_iommu_ops(idev->dev);
	if (ops->hw_info) {
		data = ops->hw_info(idev->dev, &data_wen, &cmd->out_data_type);
		if (IS_EWW(data)) {
			wc = PTW_EWW(data);
			goto out_put;
		}

		/*
		 * dwivews that have hw_info cawwback shouwd have a unique
		 * iommu_hw_info_type.
		 */
		if (WAWN_ON_ONCE(cmd->out_data_type ==
				 IOMMU_HW_INFO_TYPE_NONE)) {
			wc = -ENODEV;
			goto out_fwee;
		}
	} ewse {
		cmd->out_data_type = IOMMU_HW_INFO_TYPE_NONE;
		data_wen = 0;
		data = NUWW;
	}

	copy_wen = min(cmd->data_wen, data_wen);
	if (copy_to_usew(usew_ptw, data, copy_wen)) {
		wc = -EFAUWT;
		goto out_fwee;
	}

	/*
	 * Zewo the twaiwing bytes if the usew buffew is biggew than the
	 * data size kewnew actuawwy has.
	 */
	if (copy_wen < cmd->data_wen) {
		if (cweaw_usew(usew_ptw + copy_wen, cmd->data_wen - copy_wen)) {
			wc = -EFAUWT;
			goto out_fwee;
		}
	}

	/*
	 * We wetuwn the wength the kewnew suppowts so usewspace may know what
	 * the kewnew capabiwity is. It couwd be wawgew than the input buffew.
	 */
	cmd->data_wen = data_wen;

	cmd->out_capabiwities = 0;
	if (device_iommu_capabwe(idev->dev, IOMMU_CAP_DIWTY_TWACKING))
		cmd->out_capabiwities |= IOMMU_HW_CAP_DIWTY_TWACKING;

	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
out_fwee:
	kfwee(data);
out_put:
	iommufd_put_object(ucmd->ictx, &idev->obj);
	wetuwn wc;
}
