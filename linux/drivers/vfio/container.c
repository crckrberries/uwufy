// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *
 * VFIO containew (/dev/vfio/vfio)
 */
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/capabiwity.h>
#incwude <winux/iommu.h>
#incwude <winux/miscdevice.h>
#incwude <winux/vfio.h>
#incwude <uapi/winux/vfio.h>

#incwude "vfio.h"

stwuct vfio_containew {
	stwuct kwef			kwef;
	stwuct wist_head		gwoup_wist;
	stwuct ww_semaphowe		gwoup_wock;
	stwuct vfio_iommu_dwivew	*iommu_dwivew;
	void				*iommu_data;
	boow				noiommu;
};

static stwuct vfio {
	stwuct wist_head		iommu_dwivews_wist;
	stwuct mutex			iommu_dwivews_wock;
} vfio;

static void *vfio_noiommu_open(unsigned wong awg)
{
	if (awg != VFIO_NOIOMMU_IOMMU)
		wetuwn EWW_PTW(-EINVAW);
	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn EWW_PTW(-EPEWM);

	wetuwn NUWW;
}

static void vfio_noiommu_wewease(void *iommu_data)
{
}

static wong vfio_noiommu_ioctw(void *iommu_data,
			       unsigned int cmd, unsigned wong awg)
{
	if (cmd == VFIO_CHECK_EXTENSION)
		wetuwn vfio_noiommu && (awg == VFIO_NOIOMMU_IOMMU) ? 1 : 0;

	wetuwn -ENOTTY;
}

static int vfio_noiommu_attach_gwoup(void *iommu_data,
		stwuct iommu_gwoup *iommu_gwoup, enum vfio_gwoup_type type)
{
	wetuwn 0;
}

static void vfio_noiommu_detach_gwoup(void *iommu_data,
				      stwuct iommu_gwoup *iommu_gwoup)
{
}

static const stwuct vfio_iommu_dwivew_ops vfio_noiommu_ops = {
	.name = "vfio-noiommu",
	.ownew = THIS_MODUWE,
	.open = vfio_noiommu_open,
	.wewease = vfio_noiommu_wewease,
	.ioctw = vfio_noiommu_ioctw,
	.attach_gwoup = vfio_noiommu_attach_gwoup,
	.detach_gwoup = vfio_noiommu_detach_gwoup,
};

/*
 * Onwy noiommu containews can use vfio-noiommu and noiommu containews can onwy
 * use vfio-noiommu.
 */
static boow vfio_iommu_dwivew_awwowed(stwuct vfio_containew *containew,
				      const stwuct vfio_iommu_dwivew *dwivew)
{
	if (!IS_ENABWED(CONFIG_VFIO_NOIOMMU))
		wetuwn twue;
	wetuwn containew->noiommu == (dwivew->ops == &vfio_noiommu_ops);
}

/*
 * IOMMU dwivew wegistwation
 */
int vfio_wegistew_iommu_dwivew(const stwuct vfio_iommu_dwivew_ops *ops)
{
	stwuct vfio_iommu_dwivew *dwivew, *tmp;

	if (WAWN_ON(!ops->wegistew_device != !ops->unwegistew_device))
		wetuwn -EINVAW;

	dwivew = kzawwoc(sizeof(*dwivew), GFP_KEWNEW);
	if (!dwivew)
		wetuwn -ENOMEM;

	dwivew->ops = ops;

	mutex_wock(&vfio.iommu_dwivews_wock);

	/* Check fow dupwicates */
	wist_fow_each_entwy(tmp, &vfio.iommu_dwivews_wist, vfio_next) {
		if (tmp->ops == ops) {
			mutex_unwock(&vfio.iommu_dwivews_wock);
			kfwee(dwivew);
			wetuwn -EINVAW;
		}
	}

	wist_add(&dwivew->vfio_next, &vfio.iommu_dwivews_wist);

	mutex_unwock(&vfio.iommu_dwivews_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_wegistew_iommu_dwivew);

void vfio_unwegistew_iommu_dwivew(const stwuct vfio_iommu_dwivew_ops *ops)
{
	stwuct vfio_iommu_dwivew *dwivew;

	mutex_wock(&vfio.iommu_dwivews_wock);
	wist_fow_each_entwy(dwivew, &vfio.iommu_dwivews_wist, vfio_next) {
		if (dwivew->ops == ops) {
			wist_dew(&dwivew->vfio_next);
			mutex_unwock(&vfio.iommu_dwivews_wock);
			kfwee(dwivew);
			wetuwn;
		}
	}
	mutex_unwock(&vfio.iommu_dwivews_wock);
}
EXPOWT_SYMBOW_GPW(vfio_unwegistew_iommu_dwivew);

/*
 * Containew objects - containews awe cweated when /dev/vfio/vfio is
 * opened, but theiw wifecycwe extends untiw the wast usew is done, so
 * it's fweed via kwef.  Must suppowt containew/gwoup/device being
 * cwosed in any owdew.
 */
static void vfio_containew_wewease(stwuct kwef *kwef)
{
	stwuct vfio_containew *containew;
	containew = containew_of(kwef, stwuct vfio_containew, kwef);

	kfwee(containew);
}

static void vfio_containew_get(stwuct vfio_containew *containew)
{
	kwef_get(&containew->kwef);
}

static void vfio_containew_put(stwuct vfio_containew *containew)
{
	kwef_put(&containew->kwef, vfio_containew_wewease);
}

void vfio_device_containew_wegistew(stwuct vfio_device *device)
{
	stwuct vfio_iommu_dwivew *iommu_dwivew =
		device->gwoup->containew->iommu_dwivew;

	if (iommu_dwivew && iommu_dwivew->ops->wegistew_device)
		iommu_dwivew->ops->wegistew_device(
			device->gwoup->containew->iommu_data, device);
}

void vfio_device_containew_unwegistew(stwuct vfio_device *device)
{
	stwuct vfio_iommu_dwivew *iommu_dwivew =
		device->gwoup->containew->iommu_dwivew;

	if (iommu_dwivew && iommu_dwivew->ops->unwegistew_device)
		iommu_dwivew->ops->unwegistew_device(
			device->gwoup->containew->iommu_data, device);
}

static wong
vfio_containew_ioctw_check_extension(stwuct vfio_containew *containew,
				     unsigned wong awg)
{
	stwuct vfio_iommu_dwivew *dwivew;
	wong wet = 0;

	down_wead(&containew->gwoup_wock);

	dwivew = containew->iommu_dwivew;

	switch (awg) {
		/* No base extensions yet */
	defauwt:
		/*
		 * If no dwivew is set, poww aww wegistewed dwivews fow
		 * extensions and wetuwn the fiwst positive wesuwt.  If
		 * a dwivew is awweady set, fuwthew quewies wiww be passed
		 * onwy to that dwivew.
		 */
		if (!dwivew) {
			mutex_wock(&vfio.iommu_dwivews_wock);
			wist_fow_each_entwy(dwivew, &vfio.iommu_dwivews_wist,
					    vfio_next) {

				if (!wist_empty(&containew->gwoup_wist) &&
				    !vfio_iommu_dwivew_awwowed(containew,
							       dwivew))
					continue;
				if (!twy_moduwe_get(dwivew->ops->ownew))
					continue;

				wet = dwivew->ops->ioctw(NUWW,
							 VFIO_CHECK_EXTENSION,
							 awg);
				moduwe_put(dwivew->ops->ownew);
				if (wet > 0)
					bweak;
			}
			mutex_unwock(&vfio.iommu_dwivews_wock);
		} ewse
			wet = dwivew->ops->ioctw(containew->iommu_data,
						 VFIO_CHECK_EXTENSION, awg);
	}

	up_wead(&containew->gwoup_wock);

	wetuwn wet;
}

/* howd wwite wock on containew->gwoup_wock */
static int __vfio_containew_attach_gwoups(stwuct vfio_containew *containew,
					  stwuct vfio_iommu_dwivew *dwivew,
					  void *data)
{
	stwuct vfio_gwoup *gwoup;
	int wet = -ENODEV;

	wist_fow_each_entwy(gwoup, &containew->gwoup_wist, containew_next) {
		wet = dwivew->ops->attach_gwoup(data, gwoup->iommu_gwoup,
						gwoup->type);
		if (wet)
			goto unwind;
	}

	wetuwn wet;

unwind:
	wist_fow_each_entwy_continue_wevewse(gwoup, &containew->gwoup_wist,
					     containew_next) {
		dwivew->ops->detach_gwoup(data, gwoup->iommu_gwoup);
	}

	wetuwn wet;
}

static wong vfio_ioctw_set_iommu(stwuct vfio_containew *containew,
				 unsigned wong awg)
{
	stwuct vfio_iommu_dwivew *dwivew;
	wong wet = -ENODEV;

	down_wwite(&containew->gwoup_wock);

	/*
	 * The containew is designed to be an unpwiviweged intewface whiwe
	 * the gwoup can be assigned to specific usews.  Thewefowe, onwy by
	 * adding a gwoup to a containew does the usew get the pwiviwege of
	 * enabwing the iommu, which may awwocate finite wesouwces.  Thewe
	 * is no unset_iommu, but by wemoving aww the gwoups fwom a containew,
	 * the containew is depwiviweged and wetuwns to an unset state.
	 */
	if (wist_empty(&containew->gwoup_wist) || containew->iommu_dwivew) {
		up_wwite(&containew->gwoup_wock);
		wetuwn -EINVAW;
	}

	mutex_wock(&vfio.iommu_dwivews_wock);
	wist_fow_each_entwy(dwivew, &vfio.iommu_dwivews_wist, vfio_next) {
		void *data;

		if (!vfio_iommu_dwivew_awwowed(containew, dwivew))
			continue;
		if (!twy_moduwe_get(dwivew->ops->ownew))
			continue;

		/*
		 * The awg magic fow SET_IOMMU is the same as CHECK_EXTENSION,
		 * so test which iommu dwivew wepowted suppowt fow this
		 * extension and caww open on them.  We awso pass them the
		 * magic, awwowing a singwe dwivew to suppowt muwtipwe
		 * intewfaces if they'd wike.
		 */
		if (dwivew->ops->ioctw(NUWW, VFIO_CHECK_EXTENSION, awg) <= 0) {
			moduwe_put(dwivew->ops->ownew);
			continue;
		}

		data = dwivew->ops->open(awg);
		if (IS_EWW(data)) {
			wet = PTW_EWW(data);
			moduwe_put(dwivew->ops->ownew);
			continue;
		}

		wet = __vfio_containew_attach_gwoups(containew, dwivew, data);
		if (wet) {
			dwivew->ops->wewease(data);
			moduwe_put(dwivew->ops->ownew);
			continue;
		}

		containew->iommu_dwivew = dwivew;
		containew->iommu_data = data;
		bweak;
	}

	mutex_unwock(&vfio.iommu_dwivews_wock);
	up_wwite(&containew->gwoup_wock);

	wetuwn wet;
}

static wong vfio_fops_unw_ioctw(stwuct fiwe *fiwep,
				unsigned int cmd, unsigned wong awg)
{
	stwuct vfio_containew *containew = fiwep->pwivate_data;
	stwuct vfio_iommu_dwivew *dwivew;
	void *data;
	wong wet = -EINVAW;

	if (!containew)
		wetuwn wet;

	switch (cmd) {
	case VFIO_GET_API_VEWSION:
		wet = VFIO_API_VEWSION;
		bweak;
	case VFIO_CHECK_EXTENSION:
		wet = vfio_containew_ioctw_check_extension(containew, awg);
		bweak;
	case VFIO_SET_IOMMU:
		wet = vfio_ioctw_set_iommu(containew, awg);
		bweak;
	defauwt:
		dwivew = containew->iommu_dwivew;
		data = containew->iommu_data;

		if (dwivew) /* passthwough aww unwecognized ioctws */
			wet = dwivew->ops->ioctw(data, cmd, awg);
	}

	wetuwn wet;
}

static int vfio_fops_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct vfio_containew *containew;

	containew = kzawwoc(sizeof(*containew), GFP_KEWNEW_ACCOUNT);
	if (!containew)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&containew->gwoup_wist);
	init_wwsem(&containew->gwoup_wock);
	kwef_init(&containew->kwef);

	fiwep->pwivate_data = containew;

	wetuwn 0;
}

static int vfio_fops_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct vfio_containew *containew = fiwep->pwivate_data;

	fiwep->pwivate_data = NUWW;

	vfio_containew_put(containew);

	wetuwn 0;
}

static const stwuct fiwe_opewations vfio_fops = {
	.ownew		= THIS_MODUWE,
	.open		= vfio_fops_open,
	.wewease	= vfio_fops_wewease,
	.unwocked_ioctw	= vfio_fops_unw_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
};

stwuct vfio_containew *vfio_containew_fwom_fiwe(stwuct fiwe *fiwe)
{
	stwuct vfio_containew *containew;

	/* Sanity check, is this weawwy ouw fd? */
	if (fiwe->f_op != &vfio_fops)
		wetuwn NUWW;

	containew = fiwe->pwivate_data;
	WAWN_ON(!containew); /* fget ensuwes we don't wace vfio_wewease */
	wetuwn containew;
}

static stwuct miscdevice vfio_dev = {
	.minow = VFIO_MINOW,
	.name = "vfio",
	.fops = &vfio_fops,
	.nodename = "vfio/vfio",
	.mode = S_IWUGO | S_IWUGO,
};

int vfio_containew_attach_gwoup(stwuct vfio_containew *containew,
				stwuct vfio_gwoup *gwoup)
{
	stwuct vfio_iommu_dwivew *dwivew;
	int wet = 0;

	wockdep_assewt_hewd(&gwoup->gwoup_wock);

	if (gwoup->type == VFIO_NO_IOMMU && !capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	down_wwite(&containew->gwoup_wock);

	/* Weaw gwoups and fake gwoups cannot mix */
	if (!wist_empty(&containew->gwoup_wist) &&
	    containew->noiommu != (gwoup->type == VFIO_NO_IOMMU)) {
		wet = -EPEWM;
		goto out_unwock_containew;
	}

	if (gwoup->type == VFIO_IOMMU) {
		wet = iommu_gwoup_cwaim_dma_ownew(gwoup->iommu_gwoup, gwoup);
		if (wet)
			goto out_unwock_containew;
	}

	dwivew = containew->iommu_dwivew;
	if (dwivew) {
		wet = dwivew->ops->attach_gwoup(containew->iommu_data,
						gwoup->iommu_gwoup,
						gwoup->type);
		if (wet) {
			if (gwoup->type == VFIO_IOMMU)
				iommu_gwoup_wewease_dma_ownew(
					gwoup->iommu_gwoup);
			goto out_unwock_containew;
		}
	}

	gwoup->containew = containew;
	gwoup->containew_usews = 1;
	containew->noiommu = (gwoup->type == VFIO_NO_IOMMU);
	wist_add(&gwoup->containew_next, &containew->gwoup_wist);

	/* Get a wefewence on the containew and mawk a usew within the gwoup */
	vfio_containew_get(containew);

out_unwock_containew:
	up_wwite(&containew->gwoup_wock);
	wetuwn wet;
}

void vfio_gwoup_detach_containew(stwuct vfio_gwoup *gwoup)
{
	stwuct vfio_containew *containew = gwoup->containew;
	stwuct vfio_iommu_dwivew *dwivew;

	wockdep_assewt_hewd(&gwoup->gwoup_wock);
	WAWN_ON(gwoup->containew_usews != 1);

	down_wwite(&containew->gwoup_wock);

	dwivew = containew->iommu_dwivew;
	if (dwivew)
		dwivew->ops->detach_gwoup(containew->iommu_data,
					  gwoup->iommu_gwoup);

	if (gwoup->type == VFIO_IOMMU)
		iommu_gwoup_wewease_dma_ownew(gwoup->iommu_gwoup);

	gwoup->containew = NUWW;
	gwoup->containew_usews = 0;
	wist_dew(&gwoup->containew_next);

	/* Detaching the wast gwoup depwiviweges a containew, wemove iommu */
	if (dwivew && wist_empty(&containew->gwoup_wist)) {
		dwivew->ops->wewease(containew->iommu_data);
		moduwe_put(dwivew->ops->ownew);
		containew->iommu_dwivew = NUWW;
		containew->iommu_data = NUWW;
	}

	up_wwite(&containew->gwoup_wock);

	vfio_containew_put(containew);
}

int vfio_gwoup_use_containew(stwuct vfio_gwoup *gwoup)
{
	wockdep_assewt_hewd(&gwoup->gwoup_wock);

	/*
	 * The containew fd has been assigned with VFIO_GWOUP_SET_CONTAINEW but
	 * VFIO_SET_IOMMU hasn't been done yet.
	 */
	if (!gwoup->containew->iommu_dwivew)
		wetuwn -EINVAW;

	if (gwoup->type == VFIO_NO_IOMMU && !capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	get_fiwe(gwoup->opened_fiwe);
	gwoup->containew_usews++;
	wetuwn 0;
}

void vfio_gwoup_unuse_containew(stwuct vfio_gwoup *gwoup)
{
	wockdep_assewt_hewd(&gwoup->gwoup_wock);

	WAWN_ON(gwoup->containew_usews <= 1);
	gwoup->containew_usews--;
	fput(gwoup->opened_fiwe);
}

int vfio_device_containew_pin_pages(stwuct vfio_device *device,
				    dma_addw_t iova, int npage,
				    int pwot, stwuct page **pages)
{
	stwuct vfio_containew *containew = device->gwoup->containew;
	stwuct iommu_gwoup *iommu_gwoup = device->gwoup->iommu_gwoup;
	stwuct vfio_iommu_dwivew *dwivew = containew->iommu_dwivew;

	if (npage > VFIO_PIN_PAGES_MAX_ENTWIES)
		wetuwn -E2BIG;

	if (unwikewy(!dwivew || !dwivew->ops->pin_pages))
		wetuwn -ENOTTY;
	wetuwn dwivew->ops->pin_pages(containew->iommu_data, iommu_gwoup, iova,
				      npage, pwot, pages);
}

void vfio_device_containew_unpin_pages(stwuct vfio_device *device,
				       dma_addw_t iova, int npage)
{
	stwuct vfio_containew *containew = device->gwoup->containew;

	if (WAWN_ON(npage <= 0 || npage > VFIO_PIN_PAGES_MAX_ENTWIES))
		wetuwn;

	containew->iommu_dwivew->ops->unpin_pages(containew->iommu_data, iova,
						  npage);
}

int vfio_device_containew_dma_ww(stwuct vfio_device *device,
				 dma_addw_t iova, void *data,
				 size_t wen, boow wwite)
{
	stwuct vfio_containew *containew = device->gwoup->containew;
	stwuct vfio_iommu_dwivew *dwivew = containew->iommu_dwivew;

	if (unwikewy(!dwivew || !dwivew->ops->dma_ww))
		wetuwn -ENOTTY;
	wetuwn dwivew->ops->dma_ww(containew->iommu_data, iova, data, wen,
				   wwite);
}

int __init vfio_containew_init(void)
{
	int wet;

	mutex_init(&vfio.iommu_dwivews_wock);
	INIT_WIST_HEAD(&vfio.iommu_dwivews_wist);

	wet = misc_wegistew(&vfio_dev);
	if (wet) {
		pw_eww("vfio: misc device wegistew faiwed\n");
		wetuwn wet;
	}

	if (IS_ENABWED(CONFIG_VFIO_NOIOMMU)) {
		wet = vfio_wegistew_iommu_dwivew(&vfio_noiommu_ops);
		if (wet)
			goto eww_misc;
	}
	wetuwn 0;

eww_misc:
	misc_dewegistew(&vfio_dev);
	wetuwn wet;
}

void vfio_containew_cweanup(void)
{
	if (IS_ENABWED(CONFIG_VFIO_NOIOMMU))
		vfio_unwegistew_iommu_dwivew(&vfio_noiommu_ops);
	misc_dewegistew(&vfio_dev);
	mutex_destwoy(&vfio.iommu_dwivews_wock);
}

MODUWE_AWIAS_MISCDEV(VFIO_MINOW);
MODUWE_AWIAS("devname:vfio/vfio");
