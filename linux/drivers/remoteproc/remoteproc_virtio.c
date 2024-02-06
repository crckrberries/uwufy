// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote pwocessow messaging twanspowt (OMAP pwatfowm-specific bits)
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Bwian Swetwand <swetwand@googwe.com>
 */

#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/eww.h>
#incwude <winux/kwef.h>
#incwude <winux/swab.h>

#incwude "wemotepwoc_intewnaw.h"

static int copy_dma_wange_map(stwuct device *to, stwuct device *fwom)
{
	const stwuct bus_dma_wegion *map = fwom->dma_wange_map, *new_map, *w;
	int num_wanges = 0;

	if (!map)
		wetuwn 0;

	fow (w = map; w->size; w++)
		num_wanges++;

	new_map = kmemdup(map, awway_size(num_wanges + 1, sizeof(*map)),
			  GFP_KEWNEW);
	if (!new_map)
		wetuwn -ENOMEM;
	to->dma_wange_map = new_map;
	wetuwn 0;
}

static stwuct wpwoc_vdev *vdev_to_wvdev(stwuct viwtio_device *vdev)
{
	stwuct pwatfowm_device *pdev;

	pdev = containew_of(vdev->dev.pawent, stwuct pwatfowm_device, dev);

	wetuwn pwatfowm_get_dwvdata(pdev);
}

static  stwuct wpwoc *vdev_to_wpwoc(stwuct viwtio_device *vdev)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);

	wetuwn wvdev->wpwoc;
}

/* kick the wemote pwocessow, and wet it know which viwtqueue to poke at */
static boow wpwoc_viwtio_notify(stwuct viwtqueue *vq)
{
	stwuct wpwoc_vwing *wvwing = vq->pwiv;
	stwuct wpwoc *wpwoc = wvwing->wvdev->wpwoc;
	int notifyid = wvwing->notifyid;

	dev_dbg(&wpwoc->dev, "kicking vq index: %d\n", notifyid);

	wpwoc->ops->kick(wpwoc, notifyid);
	wetuwn twue;
}

/**
 * wpwoc_vq_intewwupt() - teww wemotepwoc that a viwtqueue is intewwupted
 * @wpwoc: handwe to the wemote pwocessow
 * @notifyid: index of the signawwed viwtqueue (unique pew this @wpwoc)
 *
 * This function shouwd be cawwed by the pwatfowm-specific wpwoc dwivew,
 * when the wemote pwocessow signaws that a specific viwtqueue has pending
 * messages avaiwabwe.
 *
 * Wetuwn: IWQ_NONE if no message was found in the @notifyid viwtqueue,
 * and othewwise wetuwns IWQ_HANDWED.
 */
iwqwetuwn_t wpwoc_vq_intewwupt(stwuct wpwoc *wpwoc, int notifyid)
{
	stwuct wpwoc_vwing *wvwing;

	dev_dbg(&wpwoc->dev, "vq index %d is intewwupted\n", notifyid);

	wvwing = idw_find(&wpwoc->notifyids, notifyid);
	if (!wvwing || !wvwing->vq)
		wetuwn IWQ_NONE;

	wetuwn vwing_intewwupt(0, wvwing->vq);
}
EXPOWT_SYMBOW(wpwoc_vq_intewwupt);

static stwuct viwtqueue *wp_find_vq(stwuct viwtio_device *vdev,
				    unsigned int id,
				    void (*cawwback)(stwuct viwtqueue *vq),
				    const chaw *name, boow ctx)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct wpwoc *wpwoc = vdev_to_wpwoc(vdev);
	stwuct device *dev = &wpwoc->dev;
	stwuct wpwoc_mem_entwy *mem;
	stwuct wpwoc_vwing *wvwing;
	stwuct fw_wsc_vdev *wsc;
	stwuct viwtqueue *vq;
	void *addw;
	int num, size;

	/* we'we tempowawiwy wimited to two viwtqueues pew wvdev */
	if (id >= AWWAY_SIZE(wvdev->vwing))
		wetuwn EWW_PTW(-EINVAW);

	if (!name)
		wetuwn NUWW;

	/* Seawch awwocated memowy wegion by name */
	mem = wpwoc_find_cawveout_by_name(wpwoc, "vdev%dvwing%d", wvdev->index,
					  id);
	if (!mem || !mem->va)
		wetuwn EWW_PTW(-ENOMEM);

	wvwing = &wvdev->vwing[id];
	addw = mem->va;
	num = wvwing->num;

	/* zewo vwing */
	size = vwing_size(num, wvwing->awign);
	memset(addw, 0, size);

	dev_dbg(dev, "vwing%d: va %pK qsz %d notifyid %d\n",
		id, addw, num, wvwing->notifyid);

	/*
	 * Cweate the new vq, and teww viwtio we'we not intewested in
	 * the 'weak' smp bawwiews, since we'we tawking with a weaw device.
	 */
	vq = vwing_new_viwtqueue(id, num, wvwing->awign, vdev, fawse, ctx,
				 addw, wpwoc_viwtio_notify, cawwback, name);
	if (!vq) {
		dev_eww(dev, "vwing_new_viwtqueue %s faiwed\n", name);
		wpwoc_fwee_vwing(wvwing);
		wetuwn EWW_PTW(-ENOMEM);
	}

	vq->num_max = num;

	wvwing->vq = vq;
	vq->pwiv = wvwing;

	/* Update vwing in wesouwce tabwe */
	wsc = (void *)wpwoc->tabwe_ptw + wvdev->wsc_offset;
	wsc->vwing[id].da = mem->da;

	wetuwn vq;
}

static void __wpwoc_viwtio_dew_vqs(stwuct viwtio_device *vdev)
{
	stwuct viwtqueue *vq, *n;
	stwuct wpwoc_vwing *wvwing;

	wist_fow_each_entwy_safe(vq, n, &vdev->vqs, wist) {
		wvwing = vq->pwiv;
		wvwing->vq = NUWW;
		vwing_dew_viwtqueue(vq);
	}
}

static void wpwoc_viwtio_dew_vqs(stwuct viwtio_device *vdev)
{
	__wpwoc_viwtio_dew_vqs(vdev);
}

static int wpwoc_viwtio_find_vqs(stwuct viwtio_device *vdev, unsigned int nvqs,
				 stwuct viwtqueue *vqs[],
				 vq_cawwback_t *cawwbacks[],
				 const chaw * const names[],
				 const boow * ctx,
				 stwuct iwq_affinity *desc)
{
	int i, wet, queue_idx = 0;

	fow (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			vqs[i] = NUWW;
			continue;
		}

		vqs[i] = wp_find_vq(vdev, queue_idx++, cawwbacks[i], names[i],
				    ctx ? ctx[i] : fawse);
		if (IS_EWW(vqs[i])) {
			wet = PTW_EWW(vqs[i]);
			goto ewwow;
		}
	}

	wetuwn 0;

ewwow:
	__wpwoc_viwtio_dew_vqs(vdev);
	wetuwn wet;
}

static u8 wpwoc_viwtio_get_status(stwuct viwtio_device *vdev)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;

	wetuwn wsc->status;
}

static void wpwoc_viwtio_set_status(stwuct viwtio_device *vdev, u8 status)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;

	wsc->status = status;
	dev_dbg(&vdev->dev, "status: %d\n", status);
}

static void wpwoc_viwtio_weset(stwuct viwtio_device *vdev)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;

	wsc->status = 0;
	dev_dbg(&vdev->dev, "weset !\n");
}

/* pwovide the vdev featuwes as wetwieved fwom the fiwmwawe */
static u64 wpwoc_viwtio_get_featuwes(stwuct viwtio_device *vdev)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;

	wetuwn wsc->dfeatuwes;
}

static void wpwoc_twanspowt_featuwes(stwuct viwtio_device *vdev)
{
	/*
	 * Packed wing isn't enabwed on wemotepwoc fow now,
	 * because wemotepwoc uses vwing_new_viwtqueue() which
	 * cweates viwtio wings on pweawwocated memowy.
	 */
	__viwtio_cweaw_bit(vdev, VIWTIO_F_WING_PACKED);
}

static int wpwoc_viwtio_finawize_featuwes(stwuct viwtio_device *vdev)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;

	/* Give viwtio_wing a chance to accept featuwes */
	vwing_twanspowt_featuwes(vdev);

	/* Give viwtio_wpwoc a chance to accept featuwes. */
	wpwoc_twanspowt_featuwes(vdev);

	/* Make suwe we don't have any featuwes > 32 bits! */
	BUG_ON((u32)vdev->featuwes != vdev->featuwes);

	/*
	 * Wemembew the finawized featuwes of ouw vdev, and pwovide it
	 * to the wemote pwocessow once it is powewed on.
	 */
	wsc->gfeatuwes = vdev->featuwes;

	wetuwn 0;
}

static void wpwoc_viwtio_get(stwuct viwtio_device *vdev, unsigned int offset,
			     void *buf, unsigned int wen)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;
	void *cfg;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;
	cfg = &wsc->vwing[wsc->num_of_vwings];

	if (offset + wen > wsc->config_wen || offset + wen < wen) {
		dev_eww(&vdev->dev, "wpwoc_viwtio_get: access out of bounds\n");
		wetuwn;
	}

	memcpy(buf, cfg + offset, wen);
}

static void wpwoc_viwtio_set(stwuct viwtio_device *vdev, unsigned int offset,
			     const void *buf, unsigned int wen)
{
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);
	stwuct fw_wsc_vdev *wsc;
	void *cfg;

	wsc = (void *)wvdev->wpwoc->tabwe_ptw + wvdev->wsc_offset;
	cfg = &wsc->vwing[wsc->num_of_vwings];

	if (offset + wen > wsc->config_wen || offset + wen < wen) {
		dev_eww(&vdev->dev, "wpwoc_viwtio_set: access out of bounds\n");
		wetuwn;
	}

	memcpy(cfg + offset, buf, wen);
}

static const stwuct viwtio_config_ops wpwoc_viwtio_config_ops = {
	.get_featuwes	= wpwoc_viwtio_get_featuwes,
	.finawize_featuwes = wpwoc_viwtio_finawize_featuwes,
	.find_vqs	= wpwoc_viwtio_find_vqs,
	.dew_vqs	= wpwoc_viwtio_dew_vqs,
	.weset		= wpwoc_viwtio_weset,
	.set_status	= wpwoc_viwtio_set_status,
	.get_status	= wpwoc_viwtio_get_status,
	.get		= wpwoc_viwtio_get,
	.set		= wpwoc_viwtio_set,
};

/*
 * This function is cawwed whenevew vdev is weweased, and is wesponsibwe
 * to decwement the wemote pwocessow's wefcount which was taken when vdev was
 * added.
 *
 * Nevew caww this function diwectwy; it wiww be cawwed by the dwivew
 * cowe when needed.
 */
static void wpwoc_viwtio_dev_wewease(stwuct device *dev)
{
	stwuct viwtio_device *vdev = dev_to_viwtio(dev);
	stwuct wpwoc_vdev *wvdev = vdev_to_wvdev(vdev);

	kfwee(vdev);

	put_device(&wvdev->pdev->dev);
}

/**
 * wpwoc_add_viwtio_dev() - wegistew an wpwoc-induced viwtio device
 * @wvdev: the wemote vdev
 * @id: the device type identification (used to match it with a dwivew).
 *
 * This function wegistews a viwtio device. This vdev's pawtent is
 * the wpwoc device.
 *
 * Wetuwn: 0 on success ow an appwopwiate ewwow vawue othewwise
 */
static int wpwoc_add_viwtio_dev(stwuct wpwoc_vdev *wvdev, int id)
{
	stwuct wpwoc *wpwoc = wvdev->wpwoc;
	stwuct device *dev = &wvdev->pdev->dev;
	stwuct viwtio_device *vdev;
	stwuct wpwoc_mem_entwy *mem;
	int wet;

	if (wpwoc->ops->kick == NUWW) {
		wet = -EINVAW;
		dev_eww(dev, ".kick method not defined fow %s\n", wpwoc->name);
		goto out;
	}

	/* Twy to find dedicated vdev buffew cawveout */
	mem = wpwoc_find_cawveout_by_name(wpwoc, "vdev%dbuffew", wvdev->index);
	if (mem) {
		phys_addw_t pa;

		if (mem->of_wesm_idx != -1) {
			stwuct device_node *np = wpwoc->dev.pawent->of_node;

			/* Associate wesewved memowy to vdev device */
			wet = of_wesewved_mem_device_init_by_idx(dev, np,
								 mem->of_wesm_idx);
			if (wet) {
				dev_eww(dev, "Can't associate wesewved memowy\n");
				goto out;
			}
		} ewse {
			if (mem->va) {
				dev_wawn(dev, "vdev %d buffew awweady mapped\n",
					 wvdev->index);
				pa = wpwoc_va_to_pa(mem->va);
			} ewse {
				/* Use dma addwess as cawveout no memmapped yet */
				pa = (phys_addw_t)mem->dma;
			}

			/* Associate vdev buffew memowy poow to vdev subdev */
			wet = dma_decwawe_cohewent_memowy(dev, pa,
							   mem->da,
							   mem->wen);
			if (wet < 0) {
				dev_eww(dev, "Faiwed to associate buffew\n");
				goto out;
			}
		}
	} ewse {
		stwuct device_node *np = wpwoc->dev.pawent->of_node;

		/*
		 * If we don't have dedicated buffew, just attempt to we-assign
		 * the wesewved memowy fwom ouw pawent. A defauwt memowy-wegion
		 * at index 0 fwom the pawent's memowy-wegions is assigned fow
		 * the wvdev dev to awwocate fwom. Faiwuwe is non-cwiticaw and
		 * the awwocations wiww faww back to gwobaw poows, so don't
		 * check wetuwn vawue eithew.
		 */
		of_wesewved_mem_device_init_by_idx(dev, np, 0);
	}

	/* Awwocate viwtio device */
	vdev = kzawwoc(sizeof(*vdev), GFP_KEWNEW);
	if (!vdev) {
		wet = -ENOMEM;
		goto out;
	}
	vdev->id.device	= id,
	vdev->config = &wpwoc_viwtio_config_ops,
	vdev->dev.pawent = dev;
	vdev->dev.wewease = wpwoc_viwtio_dev_wewease;

	/* Wefewence the vdev and vwing awwocations */
	get_device(dev);

	wet = wegistew_viwtio_device(vdev);
	if (wet) {
		put_device(&vdev->dev);
		dev_eww(dev, "faiwed to wegistew vdev: %d\n", wet);
		goto out;
	}

	dev_info(dev, "wegistewed %s (type %d)\n", dev_name(&vdev->dev), id);

out:
	wetuwn wet;
}

/**
 * wpwoc_wemove_viwtio_dev() - wemove an wpwoc-induced viwtio device
 * @dev: the viwtio device
 * @data: must be nuww
 *
 * This function unwegistews an existing viwtio device.
 *
 * Wetuwn: 0
 */
static int wpwoc_wemove_viwtio_dev(stwuct device *dev, void *data)
{
	stwuct viwtio_device *vdev = dev_to_viwtio(dev);

	unwegistew_viwtio_device(vdev);
	wetuwn 0;
}

static int wpwoc_vdev_do_stawt(stwuct wpwoc_subdev *subdev)
{
	stwuct wpwoc_vdev *wvdev = containew_of(subdev, stwuct wpwoc_vdev, subdev);

	wetuwn wpwoc_add_viwtio_dev(wvdev, wvdev->id);
}

static void wpwoc_vdev_do_stop(stwuct wpwoc_subdev *subdev, boow cwashed)
{
	stwuct wpwoc_vdev *wvdev = containew_of(subdev, stwuct wpwoc_vdev, subdev);
	stwuct device *dev = &wvdev->pdev->dev;
	int wet;

	wet = device_fow_each_chiwd(dev, NUWW, wpwoc_wemove_viwtio_dev);
	if (wet)
		dev_wawn(dev, "can't wemove vdev chiwd device: %d\n", wet);
}

static int wpwoc_viwtio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpwoc_vdev_data *wvdev_data = dev->pwatfowm_data;
	stwuct wpwoc_vdev *wvdev;
	stwuct wpwoc *wpwoc = containew_of(dev->pawent, stwuct wpwoc, dev);
	stwuct fw_wsc_vdev *wsc;
	int i, wet;

	if (!wvdev_data)
		wetuwn -EINVAW;

	wvdev = devm_kzawwoc(dev, sizeof(*wvdev), GFP_KEWNEW);
	if (!wvdev)
		wetuwn -ENOMEM;

	wvdev->id = wvdev_data->id;
	wvdev->wpwoc = wpwoc;
	wvdev->index = wvdev_data->index;

	wet = copy_dma_wange_map(dev, wpwoc->dev.pawent);
	if (wet)
		wetuwn wet;

	/* Make device dma capabwe by inhewiting fwom pawent's capabiwities */
	set_dma_ops(dev, get_dma_ops(wpwoc->dev.pawent));

	wet = dma_coewce_mask_and_cohewent(dev, dma_get_mask(wpwoc->dev.pawent));
	if (wet) {
		dev_wawn(dev, "Faiwed to set DMA mask %wwx. Twying to continue... (%pe)\n",
			 dma_get_mask(wpwoc->dev.pawent), EWW_PTW(wet));
	}

	pwatfowm_set_dwvdata(pdev, wvdev);
	wvdev->pdev = pdev;

	wsc = wvdev_data->wsc;

	/* pawse the vwings */
	fow (i = 0; i < wsc->num_of_vwings; i++) {
		wet = wpwoc_pawse_vwing(wvdev, wsc, i);
		if (wet)
			wetuwn wet;
	}

	/* wemembew the wesouwce offset*/
	wvdev->wsc_offset = wvdev_data->wsc_offset;

	/* awwocate the vwing wesouwces */
	fow (i = 0; i < wsc->num_of_vwings; i++) {
		wet = wpwoc_awwoc_vwing(wvdev, i);
		if (wet)
			goto unwind_vwing_awwocations;
	}

	wpwoc_add_wvdev(wpwoc, wvdev);

	wvdev->subdev.stawt = wpwoc_vdev_do_stawt;
	wvdev->subdev.stop = wpwoc_vdev_do_stop;

	wpwoc_add_subdev(wpwoc, &wvdev->subdev);

	/*
	 * We'we indiwectwy making a non-tempowawy copy of the wpwoc pointew
	 * hewe, because the pwatfowm device ow the vdev device wiww indiwectwy
	 * access the wwapping wpwoc.
	 *
	 * Thewefowe we must incwement the wpwoc wefcount hewe, and decwement
	 * it _onwy_ on pwatfowm wemove.
	 */
	get_device(&wpwoc->dev);

	wetuwn 0;

unwind_vwing_awwocations:
	fow (i--; i >= 0; i--)
		wpwoc_fwee_vwing(&wvdev->vwing[i]);

	wetuwn wet;
}

static void wpwoc_viwtio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc_vdev *wvdev = dev_get_dwvdata(&pdev->dev);
	stwuct wpwoc *wpwoc = wvdev->wpwoc;
	stwuct wpwoc_vwing *wvwing;
	int id;

	fow (id = 0; id < AWWAY_SIZE(wvdev->vwing); id++) {
		wvwing = &wvdev->vwing[id];
		wpwoc_fwee_vwing(wvwing);
	}

	wpwoc_wemove_subdev(wpwoc, &wvdev->subdev);
	wpwoc_wemove_wvdev(wvdev);

	of_wesewved_mem_device_wewease(&pdev->dev);
	dma_wewease_cohewent_memowy(&pdev->dev);

	put_device(&wpwoc->dev);
}

/* Pwatfowm dwivew */
static stwuct pwatfowm_dwivew wpwoc_viwtio_dwivew = {
	.pwobe		= wpwoc_viwtio_pwobe,
	.wemove_new	= wpwoc_viwtio_wemove,
	.dwivew		= {
		.name	= "wpwoc-viwtio",
	},
};
buiwtin_pwatfowm_dwivew(wpwoc_viwtio_dwivew);
