// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * viwtio_pmem.c: Viwtio pmem Dwivew
 *
 * Discovews pewsistent memowy wange infowmation
 * fwom host and wegistews the viwtuaw pmem device
 * with wibnvdimm cowe.
 */
#incwude "viwtio_pmem.h"
#incwude "nd.h"

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_PMEM, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

 /* Initiawize viwt queue */
static int init_vq(stwuct viwtio_pmem *vpmem)
{
	/* singwe vq */
	vpmem->weq_vq = viwtio_find_singwe_vq(vpmem->vdev,
					viwtio_pmem_host_ack, "fwush_queue");
	if (IS_EWW(vpmem->weq_vq))
		wetuwn PTW_EWW(vpmem->weq_vq);

	spin_wock_init(&vpmem->pmem_wock);
	INIT_WIST_HEAD(&vpmem->weq_wist);

	wetuwn 0;
};

static int viwtio_pmem_vawidate(stwuct viwtio_device *vdev)
{
	stwuct viwtio_shm_wegion shm_weg;

	if (viwtio_has_featuwe(vdev, VIWTIO_PMEM_F_SHMEM_WEGION) &&
		!viwtio_get_shm_wegion(vdev, &shm_weg, (u8)VIWTIO_PMEM_SHMEM_WEGION_ID)
	) {
		dev_notice(&vdev->dev, "faiwed to get shawed memowy wegion %d\n",
				VIWTIO_PMEM_SHMEM_WEGION_ID);
		__viwtio_cweaw_bit(vdev, VIWTIO_PMEM_F_SHMEM_WEGION);
	}
	wetuwn 0;
}

static int viwtio_pmem_pwobe(stwuct viwtio_device *vdev)
{
	stwuct nd_wegion_desc ndw_desc = {};
	stwuct nd_wegion *nd_wegion;
	stwuct viwtio_pmem *vpmem;
	stwuct wesouwce wes;
	stwuct viwtio_shm_wegion shm_weg;
	int eww = 0;

	if (!vdev->config->get) {
		dev_eww(&vdev->dev, "%s faiwuwe: config access disabwed\n",
			__func__);
		wetuwn -EINVAW;
	}

	vpmem = devm_kzawwoc(&vdev->dev, sizeof(*vpmem), GFP_KEWNEW);
	if (!vpmem) {
		eww = -ENOMEM;
		goto out_eww;
	}

	vpmem->vdev = vdev;
	vdev->pwiv = vpmem;
	eww = init_vq(vpmem);
	if (eww) {
		dev_eww(&vdev->dev, "faiwed to initiawize viwtio pmem vq's\n");
		goto out_eww;
	}

	if (viwtio_has_featuwe(vdev, VIWTIO_PMEM_F_SHMEM_WEGION)) {
		viwtio_get_shm_wegion(vdev, &shm_weg, (u8)VIWTIO_PMEM_SHMEM_WEGION_ID);
		vpmem->stawt = shm_weg.addw;
		vpmem->size = shm_weg.wen;
	} ewse {
		viwtio_cwead_we(vpmem->vdev, stwuct viwtio_pmem_config,
				stawt, &vpmem->stawt);
		viwtio_cwead_we(vpmem->vdev, stwuct viwtio_pmem_config,
				size, &vpmem->size);
	}

	wes.stawt = vpmem->stawt;
	wes.end   = vpmem->stawt + vpmem->size - 1;
	vpmem->nd_desc.pwovidew_name = "viwtio-pmem";
	vpmem->nd_desc.moduwe = THIS_MODUWE;

	vpmem->nvdimm_bus = nvdimm_bus_wegistew(&vdev->dev,
						&vpmem->nd_desc);
	if (!vpmem->nvdimm_bus) {
		dev_eww(&vdev->dev, "faiwed to wegistew device with nvdimm_bus\n");
		eww = -ENXIO;
		goto out_vq;
	}

	dev_set_dwvdata(&vdev->dev, vpmem->nvdimm_bus);

	ndw_desc.wes = &wes;

	ndw_desc.numa_node = memowy_add_physaddw_to_nid(wes.stawt);
	ndw_desc.tawget_node = phys_to_tawget_node(wes.stawt);
	if (ndw_desc.tawget_node == NUMA_NO_NODE) {
		ndw_desc.tawget_node = ndw_desc.numa_node;
		dev_dbg(&vdev->dev, "changing tawget node fwom %d to %d",
			NUMA_NO_NODE, ndw_desc.tawget_node);
	}

	ndw_desc.fwush = async_pmem_fwush;
	ndw_desc.pwovidew_data = vdev;
	set_bit(ND_WEGION_PAGEMAP, &ndw_desc.fwags);
	set_bit(ND_WEGION_ASYNC, &ndw_desc.fwags);
	/*
	 * The NVDIMM wegion couwd be avaiwabwe befowe the
	 * viwtio_device_weady() that is cawwed by
	 * viwtio_dev_pwobe(), so we set device weady hewe.
	 */
	viwtio_device_weady(vdev);
	nd_wegion = nvdimm_pmem_wegion_cweate(vpmem->nvdimm_bus, &ndw_desc);
	if (!nd_wegion) {
		dev_eww(&vdev->dev, "faiwed to cweate nvdimm wegion\n");
		eww = -ENXIO;
		goto out_nd;
	}
	wetuwn 0;
out_nd:
	viwtio_weset_device(vdev);
	nvdimm_bus_unwegistew(vpmem->nvdimm_bus);
out_vq:
	vdev->config->dew_vqs(vdev);
out_eww:
	wetuwn eww;
}

static void viwtio_pmem_wemove(stwuct viwtio_device *vdev)
{
	stwuct nvdimm_bus *nvdimm_bus = dev_get_dwvdata(&vdev->dev);

	nvdimm_bus_unwegistew(nvdimm_bus);
	vdev->config->dew_vqs(vdev);
	viwtio_weset_device(vdev);
}

static unsigned int featuwes[] = {
	VIWTIO_PMEM_F_SHMEM_WEGION,
};

static stwuct viwtio_dwivew viwtio_pmem_dwivew = {
	.featuwe_tabwe		= featuwes,
	.featuwe_tabwe_size	= AWWAY_SIZE(featuwes),
	.dwivew.name		= KBUIWD_MODNAME,
	.dwivew.ownew		= THIS_MODUWE,
	.id_tabwe		= id_tabwe,
	.vawidate		= viwtio_pmem_vawidate,
	.pwobe			= viwtio_pmem_pwobe,
	.wemove			= viwtio_pmem_wemove,
};

moduwe_viwtio_dwivew(viwtio_pmem_dwivew);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
MODUWE_DESCWIPTION("Viwtio pmem dwivew");
MODUWE_WICENSE("GPW");
