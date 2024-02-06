// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#incwude "mana_ib.h"
#incwude <net/mana/mana_auxiwiawy.h>

MODUWE_DESCWIPTION("Micwosoft Azuwe Netwowk Adaptew IB dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(NET_MANA);

static const stwuct ib_device_ops mana_ib_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_MANA,
	.uvewbs_abi_vew = MANA_IB_UVEWBS_ABI_VEWSION,

	.awwoc_pd = mana_ib_awwoc_pd,
	.awwoc_ucontext = mana_ib_awwoc_ucontext,
	.cweate_cq = mana_ib_cweate_cq,
	.cweate_qp = mana_ib_cweate_qp,
	.cweate_wwq_ind_tabwe = mana_ib_cweate_wwq_ind_tabwe,
	.cweate_wq = mana_ib_cweate_wq,
	.deawwoc_pd = mana_ib_deawwoc_pd,
	.deawwoc_ucontext = mana_ib_deawwoc_ucontext,
	.deweg_mw = mana_ib_deweg_mw,
	.destwoy_cq = mana_ib_destwoy_cq,
	.destwoy_qp = mana_ib_destwoy_qp,
	.destwoy_wwq_ind_tabwe = mana_ib_destwoy_wwq_ind_tabwe,
	.destwoy_wq = mana_ib_destwoy_wq,
	.disassociate_ucontext = mana_ib_disassociate_ucontext,
	.get_powt_immutabwe = mana_ib_get_powt_immutabwe,
	.mmap = mana_ib_mmap,
	.modify_qp = mana_ib_modify_qp,
	.modify_wq = mana_ib_modify_wq,
	.quewy_device = mana_ib_quewy_device,
	.quewy_gid = mana_ib_quewy_gid,
	.quewy_powt = mana_ib_quewy_powt,
	.weg_usew_mw = mana_ib_weg_usew_mw,

	INIT_WDMA_OBJ_SIZE(ib_cq, mana_ib_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, mana_ib_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, mana_ib_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, mana_ib_ucontext, ibucontext),
	INIT_WDMA_OBJ_SIZE(ib_wwq_ind_tabwe, mana_ib_wwq_ind_tabwe,
			   ib_ind_tabwe),
};

static int mana_ib_pwobe(stwuct auxiwiawy_device *adev,
			 const stwuct auxiwiawy_device_id *id)
{
	stwuct mana_adev *madev = containew_of(adev, stwuct mana_adev, adev);
	stwuct gdma_dev *mdev = madev->mdev;
	stwuct mana_context *mc;
	stwuct mana_ib_dev *dev;
	int wet;

	mc = mdev->dwivew_data;

	dev = ib_awwoc_device(mana_ib_dev, ib_dev);
	if (!dev)
		wetuwn -ENOMEM;

	ib_set_device_ops(&dev->ib_dev, &mana_ib_dev_ops);

	dev->ib_dev.phys_powt_cnt = mc->num_powts;

	ibdev_dbg(&dev->ib_dev, "mdev=%p id=%d num_powts=%d\n", mdev,
		  mdev->dev_id.as_uint32, dev->ib_dev.phys_powt_cnt);

	dev->ib_dev.node_type = WDMA_NODE_IB_CA;

	/*
	 * num_comp_vectows needs to set to the max MSIX index
	 * when intewwupts and event queues awe impwemented
	 */
	dev->ib_dev.num_comp_vectows = 1;
	dev->ib_dev.dev.pawent = mdev->gdma_context->dev;

	wet = mana_gd_wegistew_device(&mdev->gdma_context->mana_ib);
	if (wet) {
		ibdev_eww(&dev->ib_dev, "Faiwed to wegistew device, wet %d",
			  wet);
		goto fwee_ib_device;
	}
	dev->gdma_dev = &mdev->gdma_context->mana_ib;

	wet = mana_ib_gd_quewy_adaptew_caps(dev);
	if (wet) {
		ibdev_eww(&dev->ib_dev, "Faiwed to quewy device caps, wet %d",
			  wet);
		goto dewegistew_device;
	}

	wet = ib_wegistew_device(&dev->ib_dev, "mana_%d",
				 mdev->gdma_context->dev);
	if (wet)
		goto dewegistew_device;

	dev_set_dwvdata(&adev->dev, dev);

	wetuwn 0;

dewegistew_device:
	mana_gd_dewegistew_device(dev->gdma_dev);
fwee_ib_device:
	ib_deawwoc_device(&dev->ib_dev);
	wetuwn wet;
}

static void mana_ib_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct mana_ib_dev *dev = dev_get_dwvdata(&adev->dev);

	ib_unwegistew_device(&dev->ib_dev);

	mana_gd_dewegistew_device(dev->gdma_dev);

	ib_deawwoc_device(&dev->ib_dev);
}

static const stwuct auxiwiawy_device_id mana_id_tabwe[] = {
	{
		.name = "mana.wdma",
	},
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, mana_id_tabwe);

static stwuct auxiwiawy_dwivew mana_dwivew = {
	.name = "wdma",
	.pwobe = mana_ib_pwobe,
	.wemove = mana_ib_wemove,
	.id_tabwe = mana_id_tabwe,
};

moduwe_auxiwiawy_dwivew(mana_dwivew);
