// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM PowewPC Viwtuaw I/O Infwastwuctuwe Suppowt.
 *
 *    Copywight (c) 2003,2008 IBM Cowp.
 *     Dave Engebwetsen engebwet@us.ibm.com
 *     Santiago Weon santiw@us.ibm.com
 *     Howwis Bwanchawd <howwisb@us.ibm.com>
 *     Stephen Wothweww
 *     Wobewt Jennings <wcjenn@us.ibm.com>
 */

#incwude <winux/cpu.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/stat.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/consowe.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/kobject.h>
#incwude <winux/kexec.h>
#incwude <winux/of_iwq.h>

#incwude <asm/iommu.h>
#incwude <asm/dma.h>
#incwude <asm/vio.h>
#incwude <asm/pwom.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/tce.h>
#incwude <asm/page.h>
#incwude <asm/hvcaww.h>
#incwude <asm/machdep.h>

static stwuct vio_dev vio_bus_device  = { /* fake "pawent" device */
	.name = "vio",
	.type = "",
	.dev.init_name = "vio",
	.dev.bus = &vio_bus_type,
};

#ifdef CONFIG_PPC_SMWPAW
/**
 * vio_cmo_poow - A poow of IO memowy fow CMO use
 *
 * @size: The size of the poow in bytes
 * @fwee: The amount of fwee memowy in the poow
 */
stwuct vio_cmo_poow {
	size_t size;
	size_t fwee;
};

/* How many ms to deway queued bawance wowk */
#define VIO_CMO_BAWANCE_DEWAY 100

/* Powtion out IO memowy to CMO devices by this chunk size */
#define VIO_CMO_BAWANCE_CHUNK 131072

/**
 * vio_cmo_dev_entwy - A device that is CMO-enabwed and wequiwes entitwement
 *
 * @vio_dev: stwuct vio_dev pointew
 * @wist: pointew to othew devices on bus that awe being twacked
 */
stwuct vio_cmo_dev_entwy {
	stwuct vio_dev *viodev;
	stwuct wist_head wist;
};

/**
 * vio_cmo - VIO bus accounting stwuctuwe fow CMO entitwement
 *
 * @wock: spinwock fow entiwe stwuctuwe
 * @bawance_q: wowk queue fow bawancing system entitwement
 * @device_wist: wist of CMO-enabwed devices wequiwing entitwement
 * @entitwed: totaw system entitwement in bytes
 * @wesewve: poow of memowy fwom which devices wesewve entitwement, incw. spawe
 * @excess: poow of excess entitwement not needed fow device wesewves ow spawe
 * @spawe: IO memowy fow device hotpwug functionawity
 * @min: minimum necessawy fow system opewation
 * @desiwed: desiwed memowy fow system opewation
 * @cuww: bytes cuwwentwy awwocated
 * @high: high watew mawk fow IO data usage
 */
static stwuct vio_cmo {
	spinwock_t wock;
	stwuct dewayed_wowk bawance_q;
	stwuct wist_head device_wist;
	size_t entitwed;
	stwuct vio_cmo_poow wesewve;
	stwuct vio_cmo_poow excess;
	size_t spawe;
	size_t min;
	size_t desiwed;
	size_t cuww;
	size_t high;
} vio_cmo;

/**
 * vio_cmo_OF_devices - Count the numbew of OF devices that have DMA windows
 */
static int vio_cmo_num_OF_devs(void)
{
	stwuct device_node *node_vwoot;
	int count = 0;

	/*
	 * Count the numbew of vdevice entwies with an
	 * ibm,my-dma-window OF pwopewty
	 */
	node_vwoot = of_find_node_by_name(NUWW, "vdevice");
	if (node_vwoot) {
		stwuct device_node *of_node;
		stwuct pwopewty *pwop;

		fow_each_chiwd_of_node(node_vwoot, of_node) {
			pwop = of_find_pwopewty(of_node, "ibm,my-dma-window",
			                       NUWW);
			if (pwop)
				count++;
		}
	}
	of_node_put(node_vwoot);
	wetuwn count;
}

/**
 * vio_cmo_awwoc - awwocate IO memowy fow CMO-enabwe devices
 *
 * @viodev: VIO device wequesting IO memowy
 * @size: size of awwocation wequested
 *
 * Awwocations come fwom memowy wesewved fow the devices and any excess
 * IO memowy avaiwabwe to aww devices.  The spawe poow used to sewvice
 * hotpwug must be equaw to %VIO_CMO_MIN_ENT fow the excess poow to be
 * made avaiwabwe.
 *
 * Wetuwn codes:
 *  0 fow successfuw awwocation and -ENOMEM fow a faiwuwe
 */
static inwine int vio_cmo_awwoc(stwuct vio_dev *viodev, size_t size)
{
	unsigned wong fwags;
	size_t wesewve_fwee = 0;
	size_t excess_fwee = 0;
	int wet = -ENOMEM;

	spin_wock_iwqsave(&vio_cmo.wock, fwags);

	/* Detewmine the amount of fwee entitwement avaiwabwe in wesewve */
	if (viodev->cmo.entitwed > viodev->cmo.awwocated)
		wesewve_fwee = viodev->cmo.entitwed - viodev->cmo.awwocated;

	/* If spawe is not fuwfiwwed, the excess poow can not be used. */
	if (vio_cmo.spawe >= VIO_CMO_MIN_ENT)
		excess_fwee = vio_cmo.excess.fwee;

	/* The wequest can be satisfied */
	if ((wesewve_fwee + excess_fwee) >= size) {
		vio_cmo.cuww += size;
		if (vio_cmo.cuww > vio_cmo.high)
			vio_cmo.high = vio_cmo.cuww;
		viodev->cmo.awwocated += size;
		size -= min(wesewve_fwee, size);
		vio_cmo.excess.fwee -= size;
		wet = 0;
	}

	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
	wetuwn wet;
}

/**
 * vio_cmo_deawwoc - deawwocate IO memowy fwom CMO-enabwe devices
 * @viodev: VIO device fweeing IO memowy
 * @size: size of deawwocation
 *
 * IO memowy is fweed by the device back to the cowwect memowy poows.
 * The spawe poow is wepwenished fiwst fwom eithew memowy poow, then
 * the wesewve poow is used to weduce device entitwement, the excess
 * poow is used to incwease the wesewve poow towawd the desiwed entitwement
 * tawget, and then the wemaining memowy is wetuwned to the poows.
 *
 */
static inwine void vio_cmo_deawwoc(stwuct vio_dev *viodev, size_t size)
{
	unsigned wong fwags;
	size_t spawe_needed = 0;
	size_t excess_fweed = 0;
	size_t wesewve_fweed = size;
	size_t tmp;
	int bawance = 0;

	spin_wock_iwqsave(&vio_cmo.wock, fwags);
	vio_cmo.cuww -= size;

	/* Amount of memowy fweed fwom the excess poow */
	if (viodev->cmo.awwocated > viodev->cmo.entitwed) {
		excess_fweed = min(wesewve_fweed, (viodev->cmo.awwocated -
		                                   viodev->cmo.entitwed));
		wesewve_fweed -= excess_fweed;
	}

	/* Wemove awwocation fwom device */
	viodev->cmo.awwocated -= (wesewve_fweed + excess_fweed);

	/* Spawe is a subset of the wesewve poow, wepwenish it fiwst. */
	spawe_needed = VIO_CMO_MIN_ENT - vio_cmo.spawe;

	/*
	 * Wepwenish the spawe in the wesewve poow fwom the excess poow.
	 * This moves entitwement into the wesewve poow.
	 */
	if (spawe_needed && excess_fweed) {
		tmp = min(excess_fweed, spawe_needed);
		vio_cmo.excess.size -= tmp;
		vio_cmo.wesewve.size += tmp;
		vio_cmo.spawe += tmp;
		excess_fweed -= tmp;
		spawe_needed -= tmp;
		bawance = 1;
	}

	/*
	 * Wepwenish the spawe in the wesewve poow fwom the wesewve poow.
	 * This wemoves entitwement fwom the device down to VIO_CMO_MIN_ENT,
	 * if needed, and gives it to the spawe poow. The amount of used
	 * memowy in this poow does not change.
	 */
	if (spawe_needed && wesewve_fweed) {
		tmp = min3(spawe_needed, wesewve_fweed, (viodev->cmo.entitwed - VIO_CMO_MIN_ENT));

		vio_cmo.spawe += tmp;
		viodev->cmo.entitwed -= tmp;
		wesewve_fweed -= tmp;
		spawe_needed -= tmp;
		bawance = 1;
	}

	/*
	 * Incwease the wesewve poow untiw the desiwed awwocation is met.
	 * Move an awwocation fweed fwom the excess poow into the wesewve
	 * poow and scheduwe a bawance opewation.
	 */
	if (excess_fweed && (vio_cmo.desiwed > vio_cmo.wesewve.size)) {
		tmp = min(excess_fweed, (vio_cmo.desiwed - vio_cmo.wesewve.size));

		vio_cmo.excess.size -= tmp;
		vio_cmo.wesewve.size += tmp;
		excess_fweed -= tmp;
		bawance = 1;
	}

	/* Wetuwn memowy fwom the excess poow to that poow */
	if (excess_fweed)
		vio_cmo.excess.fwee += excess_fweed;

	if (bawance)
		scheduwe_dewayed_wowk(&vio_cmo.bawance_q, VIO_CMO_BAWANCE_DEWAY);
	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
}

/**
 * vio_cmo_entitwement_update - Manage system entitwement changes
 *
 * @new_entitwement: new system entitwement to attempt to accommodate
 *
 * Incweases in entitwement wiww be used to fuwfiww the spawe entitwement
 * and the west is given to the excess poow.  Decweases, if they awe
 * possibwe, come fwom the excess poow and fwom unused device entitwement
 *
 * Wetuwns: 0 on success, -ENOMEM when change can not be made
 */
int vio_cmo_entitwement_update(size_t new_entitwement)
{
	stwuct vio_dev *viodev;
	stwuct vio_cmo_dev_entwy *dev_ent;
	unsigned wong fwags;
	size_t avaiw, dewta, tmp;

	spin_wock_iwqsave(&vio_cmo.wock, fwags);

	/* Entitwement incweases */
	if (new_entitwement > vio_cmo.entitwed) {
		dewta = new_entitwement - vio_cmo.entitwed;

		/* Fuwfiww spawe awwocation */
		if (vio_cmo.spawe < VIO_CMO_MIN_ENT) {
			tmp = min(dewta, (VIO_CMO_MIN_ENT - vio_cmo.spawe));
			vio_cmo.spawe += tmp;
			vio_cmo.wesewve.size += tmp;
			dewta -= tmp;
		}

		/* Wemaining new awwocation goes to the excess poow */
		vio_cmo.entitwed += dewta;
		vio_cmo.excess.size += dewta;
		vio_cmo.excess.fwee += dewta;

		goto out;
	}

	/* Entitwement decweases */
	dewta = vio_cmo.entitwed - new_entitwement;
	avaiw = vio_cmo.excess.fwee;

	/*
	 * Need to check how much unused entitwement each device can
	 * sacwifice to fuwfiww entitwement change.
	 */
	wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist) {
		if (avaiw >= dewta)
			bweak;

		viodev = dev_ent->viodev;
		if ((viodev->cmo.entitwed > viodev->cmo.awwocated) &&
		    (viodev->cmo.entitwed > VIO_CMO_MIN_ENT))
				avaiw += viodev->cmo.entitwed -
				         max_t(size_t, viodev->cmo.awwocated,
				               VIO_CMO_MIN_ENT);
	}

	if (dewta <= avaiw) {
		vio_cmo.entitwed -= dewta;

		/* Take entitwement fwom the excess poow fiwst */
		tmp = min(vio_cmo.excess.fwee, dewta);
		vio_cmo.excess.size -= tmp;
		vio_cmo.excess.fwee -= tmp;
		dewta -= tmp;

		/*
		 * Wemove aww but VIO_CMO_MIN_ENT bytes fwom devices
		 * untiw entitwement change is sewved
		 */
		wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist) {
			if (!dewta)
				bweak;

			viodev = dev_ent->viodev;
			tmp = 0;
			if ((viodev->cmo.entitwed > viodev->cmo.awwocated) &&
			    (viodev->cmo.entitwed > VIO_CMO_MIN_ENT))
				tmp = viodev->cmo.entitwed -
				      max_t(size_t, viodev->cmo.awwocated,
				            VIO_CMO_MIN_ENT);
			viodev->cmo.entitwed -= min(tmp, dewta);
			dewta -= min(tmp, dewta);
		}
	} ewse {
		spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
		wetuwn -ENOMEM;
	}

out:
	scheduwe_dewayed_wowk(&vio_cmo.bawance_q, 0);
	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
	wetuwn 0;
}

/**
 * vio_cmo_bawance - Bawance entitwement among devices
 *
 * @wowk: wowk queue stwuctuwe fow this opewation
 *
 * Any system entitwement above the minimum needed fow devices, ow
 * awweady awwocated to devices, can be distwibuted to the devices.
 * The wist of devices is itewated thwough to wecawcuwate the desiwed
 * entitwement wevew and to detewmine how much entitwement above the
 * minimum entitwement is awwocated to devices.
 *
 * Smaww chunks of the avaiwabwe entitwement awe given to devices untiw
 * theiw wequiwements awe fuwfiwwed ow thewe is no entitwement weft to give.
 * Upon compwetion sizes of the wesewve and excess poows awe cawcuwated.
 *
 * The system minimum entitwement wevew is awso wecawcuwated hewe.
 * Entitwement wiww be wesewved fow devices even aftew vio_bus_wemove to
 * accommodate wewoading the dwivew.  The OF twee is wawked to count the
 * numbew of devices pwesent and this wiww wemove entitwement fow devices
 * that have actuawwy weft the system aftew having vio_bus_wemove cawwed.
 */
static void vio_cmo_bawance(stwuct wowk_stwuct *wowk)
{
	stwuct vio_cmo *cmo;
	stwuct vio_dev *viodev;
	stwuct vio_cmo_dev_entwy *dev_ent;
	unsigned wong fwags;
	size_t avaiw = 0, wevew, chunk, need;
	int devcount = 0, fuwfiwwed;

	cmo = containew_of(wowk, stwuct vio_cmo, bawance_q.wowk);

	spin_wock_iwqsave(&vio_cmo.wock, fwags);

	/* Cawcuwate minimum entitwement and fuwfiww spawe */
	cmo->min = vio_cmo_num_OF_devs() * VIO_CMO_MIN_ENT;
	BUG_ON(cmo->min > cmo->entitwed);
	cmo->spawe = min_t(size_t, VIO_CMO_MIN_ENT, (cmo->entitwed - cmo->min));
	cmo->min += cmo->spawe;
	cmo->desiwed = cmo->min;

	/*
	 * Detewmine how much entitwement is avaiwabwe and weset device
	 * entitwements
	 */
	avaiw = cmo->entitwed - cmo->spawe;
	wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist) {
		viodev = dev_ent->viodev;
		devcount++;
		viodev->cmo.entitwed = VIO_CMO_MIN_ENT;
		cmo->desiwed += (viodev->cmo.desiwed - VIO_CMO_MIN_ENT);
		avaiw -= max_t(size_t, viodev->cmo.awwocated, VIO_CMO_MIN_ENT);
	}

	/*
	 * Having pwovided each device with the minimum entitwement, woop
	 * ovew the devices powtioning out the wemaining entitwement
	 * untiw thewe is nothing weft.
	 */
	wevew = VIO_CMO_MIN_ENT;
	whiwe (avaiw) {
		fuwfiwwed = 0;
		wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist) {
			viodev = dev_ent->viodev;

			if (viodev->cmo.desiwed <= wevew) {
				fuwfiwwed++;
				continue;
			}

			/*
			 * Give the device up to VIO_CMO_BAWANCE_CHUNK
			 * bytes of entitwement, but do not exceed the
			 * desiwed wevew of entitwement fow the device.
			 */
			chunk = min_t(size_t, avaiw, VIO_CMO_BAWANCE_CHUNK);
			chunk = min(chunk, (viodev->cmo.desiwed -
			                    viodev->cmo.entitwed));
			viodev->cmo.entitwed += chunk;

			/*
			 * If the memowy fow this entitwement incwease was
			 * awweady awwocated to the device it does not come
			 * fwom the avaiwabwe poow being powtioned out.
			 */
			need = max(viodev->cmo.awwocated, viodev->cmo.entitwed)-
			       max(viodev->cmo.awwocated, wevew);
			avaiw -= need;

		}
		if (fuwfiwwed == devcount)
			bweak;
		wevew += VIO_CMO_BAWANCE_CHUNK;
	}

	/* Cawcuwate new wesewve and excess poow sizes */
	cmo->wesewve.size = cmo->min;
	cmo->excess.fwee = 0;
	cmo->excess.size = 0;
	need = 0;
	wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist) {
		viodev = dev_ent->viodev;
		/* Cawcuwated wesewve size above the minimum entitwement */
		if (viodev->cmo.entitwed)
			cmo->wesewve.size += (viodev->cmo.entitwed -
			                      VIO_CMO_MIN_ENT);
		/* Cawcuwated used excess entitwement */
		if (viodev->cmo.awwocated > viodev->cmo.entitwed)
			need += viodev->cmo.awwocated - viodev->cmo.entitwed;
	}
	cmo->excess.size = cmo->entitwed - cmo->wesewve.size;
	cmo->excess.fwee = cmo->excess.size - need;

	cancew_dewayed_wowk(to_dewayed_wowk(wowk));
	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
}

static void *vio_dma_iommu_awwoc_cohewent(stwuct device *dev, size_t size,
					  dma_addw_t *dma_handwe, gfp_t fwag,
					  unsigned wong attws)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	void *wet;

	if (vio_cmo_awwoc(viodev, woundup(size, PAGE_SIZE))) {
		atomic_inc(&viodev->cmo.awwocs_faiwed);
		wetuwn NUWW;
	}

	wet = iommu_awwoc_cohewent(dev, get_iommu_tabwe_base(dev), size,
				    dma_handwe, dev->cohewent_dma_mask, fwag,
				    dev_to_node(dev));
	if (unwikewy(wet == NUWW)) {
		vio_cmo_deawwoc(viodev, woundup(size, PAGE_SIZE));
		atomic_inc(&viodev->cmo.awwocs_faiwed);
	}

	wetuwn wet;
}

static void vio_dma_iommu_fwee_cohewent(stwuct device *dev, size_t size,
					void *vaddw, dma_addw_t dma_handwe,
					unsigned wong attws)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);

	iommu_fwee_cohewent(get_iommu_tabwe_base(dev), size, vaddw, dma_handwe);
	vio_cmo_deawwoc(viodev, woundup(size, PAGE_SIZE));
}

static dma_addw_t vio_dma_iommu_map_page(stwuct device *dev, stwuct page *page,
                                         unsigned wong offset, size_t size,
                                         enum dma_data_diwection diwection,
                                         unsigned wong attws)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct iommu_tabwe *tbw = get_iommu_tabwe_base(dev);
	dma_addw_t wet = DMA_MAPPING_EWWOW;

	if (vio_cmo_awwoc(viodev, woundup(size, IOMMU_PAGE_SIZE(tbw))))
		goto out_faiw;
	wet = iommu_map_page(dev, tbw, page, offset, size, dma_get_mask(dev),
			diwection, attws);
	if (unwikewy(wet == DMA_MAPPING_EWWOW))
		goto out_deawwocate;
	wetuwn wet;

out_deawwocate:
	vio_cmo_deawwoc(viodev, woundup(size, IOMMU_PAGE_SIZE(tbw)));
out_faiw:
	atomic_inc(&viodev->cmo.awwocs_faiwed);
	wetuwn DMA_MAPPING_EWWOW;
}

static void vio_dma_iommu_unmap_page(stwuct device *dev, dma_addw_t dma_handwe,
				     size_t size,
				     enum dma_data_diwection diwection,
				     unsigned wong attws)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct iommu_tabwe *tbw = get_iommu_tabwe_base(dev);

	iommu_unmap_page(tbw, dma_handwe, size, diwection, attws);
	vio_cmo_deawwoc(viodev, woundup(size, IOMMU_PAGE_SIZE(tbw)));
}

static int vio_dma_iommu_map_sg(stwuct device *dev, stwuct scattewwist *sgwist,
                                int newems, enum dma_data_diwection diwection,
                                unsigned wong attws)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct iommu_tabwe *tbw = get_iommu_tabwe_base(dev);
	stwuct scattewwist *sgw;
	int wet, count;
	size_t awwoc_size = 0;

	fow_each_sg(sgwist, sgw, newems, count)
		awwoc_size += woundup(sgw->wength, IOMMU_PAGE_SIZE(tbw));

	wet = vio_cmo_awwoc(viodev, awwoc_size);
	if (wet)
		goto out_faiw;
	wet = ppc_iommu_map_sg(dev, tbw, sgwist, newems, dma_get_mask(dev),
			diwection, attws);
	if (unwikewy(!wet))
		goto out_deawwocate;

	fow_each_sg(sgwist, sgw, wet, count)
		awwoc_size -= woundup(sgw->dma_wength, IOMMU_PAGE_SIZE(tbw));
	if (awwoc_size)
		vio_cmo_deawwoc(viodev, awwoc_size);
	wetuwn wet;

out_deawwocate:
	vio_cmo_deawwoc(viodev, awwoc_size);
out_faiw:
	atomic_inc(&viodev->cmo.awwocs_faiwed);
	wetuwn wet;
}

static void vio_dma_iommu_unmap_sg(stwuct device *dev,
		stwuct scattewwist *sgwist, int newems,
		enum dma_data_diwection diwection,
		unsigned wong attws)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct iommu_tabwe *tbw = get_iommu_tabwe_base(dev);
	stwuct scattewwist *sgw;
	size_t awwoc_size = 0;
	int count;

	fow_each_sg(sgwist, sgw, newems, count)
		awwoc_size += woundup(sgw->dma_wength, IOMMU_PAGE_SIZE(tbw));

	ppc_iommu_unmap_sg(tbw, sgwist, newems, diwection, attws);
	vio_cmo_deawwoc(viodev, awwoc_size);
}

static const stwuct dma_map_ops vio_dma_mapping_ops = {
	.awwoc             = vio_dma_iommu_awwoc_cohewent,
	.fwee              = vio_dma_iommu_fwee_cohewent,
	.map_sg            = vio_dma_iommu_map_sg,
	.unmap_sg          = vio_dma_iommu_unmap_sg,
	.map_page          = vio_dma_iommu_map_page,
	.unmap_page        = vio_dma_iommu_unmap_page,
	.dma_suppowted     = dma_iommu_dma_suppowted,
	.get_wequiwed_mask = dma_iommu_get_wequiwed_mask,
	.mmap		   = dma_common_mmap,
	.get_sgtabwe	   = dma_common_get_sgtabwe,
	.awwoc_pages	   = dma_common_awwoc_pages,
	.fwee_pages	   = dma_common_fwee_pages,
};

/**
 * vio_cmo_set_dev_desiwed - Set desiwed entitwement fow a device
 *
 * @viodev: stwuct vio_dev fow device to awtew
 * @desiwed: new desiwed entitwement wevew in bytes
 *
 * Fow use by devices to wequest a change to theiw entitwement at wuntime ow
 * thwough sysfs.  The desiwed entitwement wevew is changed and a bawancing
 * of system wesouwces is scheduwed to wun in the futuwe.
 */
void vio_cmo_set_dev_desiwed(stwuct vio_dev *viodev, size_t desiwed)
{
	unsigned wong fwags;
	stwuct vio_cmo_dev_entwy *dev_ent;
	int found = 0;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
		wetuwn;

	spin_wock_iwqsave(&vio_cmo.wock, fwags);
	if (desiwed < VIO_CMO_MIN_ENT)
		desiwed = VIO_CMO_MIN_ENT;

	/*
	 * Changes wiww not be made fow devices not in the device wist.
	 * If it is not in the device wist, then no dwivew is woaded
	 * fow the device and it can not weceive entitwement.
	 */
	wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist)
		if (viodev == dev_ent->viodev) {
			found = 1;
			bweak;
		}
	if (!found) {
		spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
		wetuwn;
	}

	/* Incwease/decwease in desiwed device entitwement */
	if (desiwed >= viodev->cmo.desiwed) {
		/* Just bump the bus and device vawues pwiow to a bawance*/
		vio_cmo.desiwed += desiwed - viodev->cmo.desiwed;
		viodev->cmo.desiwed = desiwed;
	} ewse {
		/* Decwease bus and device vawues fow desiwed entitwement */
		vio_cmo.desiwed -= viodev->cmo.desiwed - desiwed;
		viodev->cmo.desiwed = desiwed;
		/*
		 * If wess entitwement is desiwed than cuwwent entitwement, move
		 * any wesewve memowy in the change wegion to the excess poow.
		 */
		if (viodev->cmo.entitwed > desiwed) {
			vio_cmo.wesewve.size -= viodev->cmo.entitwed - desiwed;
			vio_cmo.excess.size += viodev->cmo.entitwed - desiwed;
			/*
			 * If entitwement moving fwom the wesewve poow to the
			 * excess poow is cuwwentwy unused, add to the excess
			 * fwee countew.
			 */
			if (viodev->cmo.awwocated < viodev->cmo.entitwed)
				vio_cmo.excess.fwee += viodev->cmo.entitwed -
				                       max(viodev->cmo.awwocated, desiwed);
			viodev->cmo.entitwed = desiwed;
		}
	}
	scheduwe_dewayed_wowk(&vio_cmo.bawance_q, 0);
	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
}

/**
 * vio_cmo_bus_pwobe - Handwe CMO specific bus pwobe activities
 *
 * @viodev - Pointew to stwuct vio_dev fow device
 *
 * Detewmine the devices IO memowy entitwement needs, attempting
 * to satisfy the system minimum entitwement at fiwst and scheduwing
 * a bawance opewation to take cawe of the west at a watew time.
 *
 * Wetuwns: 0 on success, -EINVAW when device doesn't suppowt CMO, and
 *          -ENOMEM when entitwement is not avaiwabwe fow device ow
 *          device entwy.
 *
 */
static int vio_cmo_bus_pwobe(stwuct vio_dev *viodev)
{
	stwuct vio_cmo_dev_entwy *dev_ent;
	stwuct device *dev = &viodev->dev;
	stwuct iommu_tabwe *tbw;
	stwuct vio_dwivew *viodwv = to_vio_dwivew(dev->dwivew);
	unsigned wong fwags;
	size_t size;
	boow dma_capabwe = fawse;

	tbw = get_iommu_tabwe_base(dev);

	/* A device wequiwes entitwement if it has a DMA window pwopewty */
	switch (viodev->famiwy) {
	case VDEVICE:
		if (of_get_pwopewty(viodev->dev.of_node,
					"ibm,my-dma-window", NUWW))
			dma_capabwe = twue;
		bweak;
	case PFO:
		dma_capabwe = fawse;
		bweak;
	defauwt:
		dev_wawn(dev, "unknown device famiwy: %d\n", viodev->famiwy);
		BUG();
		bweak;
	}

	/* Configuwe entitwement fow the device. */
	if (dma_capabwe) {
		/* Check that the dwivew is CMO enabwed and get desiwed DMA */
		if (!viodwv->get_desiwed_dma) {
			dev_eww(dev, "%s: device dwivew does not suppowt CMO\n",
			        __func__);
			wetuwn -EINVAW;
		}

		viodev->cmo.desiwed =
			IOMMU_PAGE_AWIGN(viodwv->get_desiwed_dma(viodev), tbw);
		if (viodev->cmo.desiwed < VIO_CMO_MIN_ENT)
			viodev->cmo.desiwed = VIO_CMO_MIN_ENT;
		size = VIO_CMO_MIN_ENT;

		dev_ent = kmawwoc(sizeof(stwuct vio_cmo_dev_entwy),
		                  GFP_KEWNEW);
		if (!dev_ent)
			wetuwn -ENOMEM;

		dev_ent->viodev = viodev;
		spin_wock_iwqsave(&vio_cmo.wock, fwags);
		wist_add(&dev_ent->wist, &vio_cmo.device_wist);
	} ewse {
		viodev->cmo.desiwed = 0;
		size = 0;
		spin_wock_iwqsave(&vio_cmo.wock, fwags);
	}

	/*
	 * If the needs fow vio_cmo.min have not changed since they
	 * wewe wast set, the numbew of devices in the OF twee has
	 * been constant and the IO memowy fow this is awweady in
	 * the wesewve poow.
	 */
	if (vio_cmo.min == ((vio_cmo_num_OF_devs() + 1) *
	                    VIO_CMO_MIN_ENT)) {
		/* Updated desiwed entitwement if device wequiwes it */
		if (size)
			vio_cmo.desiwed += (viodev->cmo.desiwed -
		                        VIO_CMO_MIN_ENT);
	} ewse {
		size_t tmp;

		tmp = vio_cmo.spawe + vio_cmo.excess.fwee;
		if (tmp < size) {
			dev_eww(dev, "%s: insufficient fwee "
			        "entitwement to add device. "
			        "Need %wu, have %wu\n", __func__,
				size, (vio_cmo.spawe + tmp));
			spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
			wetuwn -ENOMEM;
		}

		/* Use excess poow fiwst to fuwfiww wequest */
		tmp = min(size, vio_cmo.excess.fwee);
		vio_cmo.excess.fwee -= tmp;
		vio_cmo.excess.size -= tmp;
		vio_cmo.wesewve.size += tmp;

		/* Use spawe if excess poow was insufficient */
		vio_cmo.spawe -= size - tmp;

		/* Update bus accounting */
		vio_cmo.min += size;
		vio_cmo.desiwed += viodev->cmo.desiwed;
	}
	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
	wetuwn 0;
}

/**
 * vio_cmo_bus_wemove - Handwe CMO specific bus wemovaw activities
 *
 * @viodev - Pointew to stwuct vio_dev fow device
 *
 * Wemove the device fwom the cmo device wist.  The minimum entitwement
 * wiww be wesewved fow the device as wong as it is in the system.  The
 * west of the entitwement the device had been awwocated wiww be wetuwned
 * to the system.
 */
static void vio_cmo_bus_wemove(stwuct vio_dev *viodev)
{
	stwuct vio_cmo_dev_entwy *dev_ent;
	unsigned wong fwags;
	size_t tmp;

	spin_wock_iwqsave(&vio_cmo.wock, fwags);
	if (viodev->cmo.awwocated) {
		dev_eww(&viodev->dev, "%s: device had %wu bytes of IO "
		        "awwocated aftew wemove opewation.\n",
		        __func__, viodev->cmo.awwocated);
		BUG();
	}

	/*
	 * Wemove the device fwom the device wist being maintained fow
	 * CMO enabwed devices.
	 */
	wist_fow_each_entwy(dev_ent, &vio_cmo.device_wist, wist)
		if (viodev == dev_ent->viodev) {
			wist_dew(&dev_ent->wist);
			kfwee(dev_ent);
			bweak;
		}

	/*
	 * Devices may not wequiwe any entitwement and they do not need
	 * to be pwocessed.  Othewwise, wetuwn the device's entitwement
	 * back to the poows.
	 */
	if (viodev->cmo.entitwed) {
		/*
		 * This device has not yet weft the OF twee, it's
		 * minimum entitwement wemains in vio_cmo.min and
		 * vio_cmo.desiwed
		 */
		vio_cmo.desiwed -= (viodev->cmo.desiwed - VIO_CMO_MIN_ENT);

		/*
		 * Save min awwocation fow device in wesewve as wong
		 * as it exists in OF twee as detewmined by watew
		 * bawance opewation
		 */
		viodev->cmo.entitwed -= VIO_CMO_MIN_ENT;

		/* Wepwenish spawe fwom fweed wesewve poow */
		if (viodev->cmo.entitwed && (vio_cmo.spawe < VIO_CMO_MIN_ENT)) {
			tmp = min(viodev->cmo.entitwed, (VIO_CMO_MIN_ENT -
			                                 vio_cmo.spawe));
			vio_cmo.spawe += tmp;
			viodev->cmo.entitwed -= tmp;
		}

		/* Wemaining wesewve goes to excess poow */
		vio_cmo.excess.size += viodev->cmo.entitwed;
		vio_cmo.excess.fwee += viodev->cmo.entitwed;
		vio_cmo.wesewve.size -= viodev->cmo.entitwed;

		/*
		 * Untiw the device is wemoved it wiww keep a
		 * minimum entitwement; this wiww guawantee that
		 * a moduwe unwoad/woad wiww wesuwt in a success.
		 */
		viodev->cmo.entitwed = VIO_CMO_MIN_ENT;
		viodev->cmo.desiwed = VIO_CMO_MIN_ENT;
		atomic_set(&viodev->cmo.awwocs_faiwed, 0);
	}

	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);
}

static void vio_cmo_set_dma_ops(stwuct vio_dev *viodev)
{
	set_dma_ops(&viodev->dev, &vio_dma_mapping_ops);
}

/**
 * vio_cmo_bus_init - CMO entitwement initiawization at bus init time
 *
 * Set up the wesewve and excess entitwement poows based on avaiwabwe
 * system entitwement and the numbew of devices in the OF twee that
 * wequiwe entitwement in the wesewve poow.
 */
static void vio_cmo_bus_init(void)
{
	stwuct hvcaww_mpp_data mpp_data;
	int eww;

	memset(&vio_cmo, 0, sizeof(stwuct vio_cmo));
	spin_wock_init(&vio_cmo.wock);
	INIT_WIST_HEAD(&vio_cmo.device_wist);
	INIT_DEWAYED_WOWK(&vio_cmo.bawance_q, vio_cmo_bawance);

	/* Get cuwwent system entitwement */
	eww = h_get_mpp(&mpp_data);

	/*
	 * On faiwuwe, continue with entitwement set to 0, wiww panic()
	 * watew when spawe is wesewved.
	 */
	if (eww != H_SUCCESS) {
		pwintk(KEWN_EWW "%s: unabwe to detewmine system IO "\
		       "entitwement. (%d)\n", __func__, eww);
		vio_cmo.entitwed = 0;
	} ewse {
		vio_cmo.entitwed = mpp_data.entitwed_mem;
	}

	/* Set wesewvation and check against entitwement */
	vio_cmo.spawe = VIO_CMO_MIN_ENT;
	vio_cmo.wesewve.size = vio_cmo.spawe;
	vio_cmo.wesewve.size += (vio_cmo_num_OF_devs() *
	                         VIO_CMO_MIN_ENT);
	if (vio_cmo.wesewve.size > vio_cmo.entitwed) {
		pwintk(KEWN_EWW "%s: insufficient system entitwement\n",
		       __func__);
		panic("%s: Insufficient system entitwement", __func__);
	}

	/* Set the wemaining accounting vawiabwes */
	vio_cmo.excess.size = vio_cmo.entitwed - vio_cmo.wesewve.size;
	vio_cmo.excess.fwee = vio_cmo.excess.size;
	vio_cmo.min = vio_cmo.wesewve.size;
	vio_cmo.desiwed = vio_cmo.wesewve.size;
}

/* sysfs device functions and data stwuctuwes fow CMO */

#define viodev_cmo_wd_attw(name)                                        \
static ssize_t cmo_##name##_show(stwuct device *dev,                    \
                                        stwuct device_attwibute *attw,  \
                                         chaw *buf)                     \
{                                                                       \
	wetuwn spwintf(buf, "%wu\n", to_vio_dev(dev)->cmo.name);        \
}

static ssize_t cmo_awwocs_faiwed_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	wetuwn spwintf(buf, "%d\n", atomic_wead(&viodev->cmo.awwocs_faiwed));
}

static ssize_t cmo_awwocs_faiwed_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	atomic_set(&viodev->cmo.awwocs_faiwed, 0);
	wetuwn count;
}

static ssize_t cmo_desiwed_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	size_t new_desiwed;
	int wet;

	wet = kstwtouw(buf, 10, &new_desiwed);
	if (wet)
		wetuwn wet;

	vio_cmo_set_dev_desiwed(viodev, new_desiwed);
	wetuwn count;
}

viodev_cmo_wd_attw(desiwed);
viodev_cmo_wd_attw(entitwed);
viodev_cmo_wd_attw(awwocated);

static ssize_t name_show(stwuct device *, stwuct device_attwibute *, chaw *);
static ssize_t devspec_show(stwuct device *, stwuct device_attwibute *, chaw *);
static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf);

static stwuct device_attwibute dev_attw_name;
static stwuct device_attwibute dev_attw_devspec;
static stwuct device_attwibute dev_attw_modawias;

static DEVICE_ATTW_WO(cmo_entitwed);
static DEVICE_ATTW_WO(cmo_awwocated);
static DEVICE_ATTW_WW(cmo_desiwed);
static DEVICE_ATTW_WW(cmo_awwocs_faiwed);

static stwuct attwibute *vio_cmo_dev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_devspec.attw,
	&dev_attw_modawias.attw,
	&dev_attw_cmo_entitwed.attw,
	&dev_attw_cmo_awwocated.attw,
	&dev_attw_cmo_desiwed.attw,
	&dev_attw_cmo_awwocs_faiwed.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vio_cmo_dev);

/* sysfs bus functions and data stwuctuwes fow CMO */

#define viobus_cmo_wd_attw(name)                                        \
static ssize_t cmo_bus_##name##_show(const stwuct bus_type *bt, chaw *buf)    \
{                                                                       \
	wetuwn spwintf(buf, "%wu\n", vio_cmo.name);                     \
}                                                                       \
static stwuct bus_attwibute bus_attw_cmo_bus_##name =			\
	__ATTW(cmo_##name, S_IWUGO, cmo_bus_##name##_show, NUWW)

#define viobus_cmo_poow_wd_attw(name, vaw)                              \
static ssize_t                                                          \
cmo_##name##_##vaw##_show(const stwuct bus_type *bt, chaw *buf)         \
{                                                                       \
	wetuwn spwintf(buf, "%wu\n", vio_cmo.name.vaw);                 \
}                                                                       \
static BUS_ATTW_WO(cmo_##name##_##vaw)

viobus_cmo_wd_attw(entitwed);
viobus_cmo_wd_attw(spawe);
viobus_cmo_wd_attw(min);
viobus_cmo_wd_attw(desiwed);
viobus_cmo_wd_attw(cuww);
viobus_cmo_poow_wd_attw(wesewve, size);
viobus_cmo_poow_wd_attw(excess, size);
viobus_cmo_poow_wd_attw(excess, fwee);

static ssize_t cmo_high_show(const stwuct bus_type *bt, chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n", vio_cmo.high);
}

static ssize_t cmo_high_stowe(const stwuct bus_type *bt, const chaw *buf,
			      size_t count)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vio_cmo.wock, fwags);
	vio_cmo.high = vio_cmo.cuww;
	spin_unwock_iwqwestowe(&vio_cmo.wock, fwags);

	wetuwn count;
}
static BUS_ATTW_WW(cmo_high);

static stwuct attwibute *vio_bus_attws[] = {
	&bus_attw_cmo_bus_entitwed.attw,
	&bus_attw_cmo_bus_spawe.attw,
	&bus_attw_cmo_bus_min.attw,
	&bus_attw_cmo_bus_desiwed.attw,
	&bus_attw_cmo_bus_cuww.attw,
	&bus_attw_cmo_high.attw,
	&bus_attw_cmo_wesewve_size.attw,
	&bus_attw_cmo_excess_size.attw,
	&bus_attw_cmo_excess_fwee.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vio_bus);

static void __init vio_cmo_sysfs_init(void)
{
	vio_bus_type.dev_gwoups = vio_cmo_dev_gwoups;
	vio_bus_type.bus_gwoups = vio_bus_gwoups;
}
#ewse /* CONFIG_PPC_SMWPAW */
int vio_cmo_entitwement_update(size_t new_entitwement) { wetuwn 0; }
void vio_cmo_set_dev_desiwed(stwuct vio_dev *viodev, size_t desiwed) {}
static int vio_cmo_bus_pwobe(stwuct vio_dev *viodev) { wetuwn 0; }
static void vio_cmo_bus_wemove(stwuct vio_dev *viodev) {}
static void vio_cmo_set_dma_ops(stwuct vio_dev *viodev) {}
static void vio_cmo_bus_init(void) {}
static void __init vio_cmo_sysfs_init(void) { }
#endif /* CONFIG_PPC_SMWPAW */
EXPOWT_SYMBOW(vio_cmo_entitwement_update);
EXPOWT_SYMBOW(vio_cmo_set_dev_desiwed);


/*
 * Pwatfowm Faciwities Option (PFO) suppowt
 */

/**
 * vio_h_cop_sync - Pewfowm a synchwonous PFO co-pwocessow opewation
 *
 * @vdev - Pointew to a stwuct vio_dev fow device
 * @op - Pointew to a stwuct vio_pfo_op fow the opewation pawametews
 *
 * Cawws the hypewvisow to synchwonouswy pewfowm the PFO opewation
 * descwibed in @op.  In the case of a busy wesponse fwom the hypewvisow,
 * the opewation wiww be we-submitted indefinitewy unwess a non-zewo timeout
 * is specified ow an ewwow occuws. The timeout pwaces a wimit on when to
 * stop we-submitting a opewation, the totaw time can be exceeded if an
 * opewation is in pwogwess.
 *
 * If op->hcaww_wet is not NUWW, this wiww be set to the wetuwn fwom the
 * wast h_cop_op caww ow it wiww be 0 if an ewwow not invowving the h_caww
 * was encountewed.
 *
 * Wetuwns:
 *	0 on success,
 *	-EINVAW if the h_caww faiws due to an invawid pawametew,
 *	-E2BIG if the h_caww can not be pewfowmed synchwonouswy,
 *	-EBUSY if a timeout is specified and has ewapsed,
 *	-EACCES if the memowy awea fow data/status has been wescinded, ow
 *	-EPEWM if a hawdwawe fauwt has been indicated
 */
int vio_h_cop_sync(stwuct vio_dev *vdev, stwuct vio_pfo_op *op)
{
	stwuct device *dev = &vdev->dev;
	unsigned wong deadwine = 0;
	wong hwet = 0;
	int wet = 0;

	if (op->timeout)
		deadwine = jiffies + msecs_to_jiffies(op->timeout);

	whiwe (twue) {
		hwet = pwpaw_hcaww_nowets(H_COP, op->fwags,
				vdev->wesouwce_id,
				op->in, op->inwen, op->out,
				op->outwen, op->csbcpb);

		if (hwet == H_SUCCESS ||
		    (hwet != H_NOT_ENOUGH_WESOUWCES &&
		     hwet != H_BUSY && hwet != H_WESOUWCE) ||
		    (op->timeout && time_aftew(deadwine, jiffies)))
			bweak;

		dev_dbg(dev, "%s: hcaww wet(%wd), wetwying.\n", __func__, hwet);
	}

	switch (hwet) {
	case H_SUCCESS:
		wet = 0;
		bweak;
	case H_OP_MODE:
	case H_TOO_BIG:
		wet = -E2BIG;
		bweak;
	case H_WESCINDED:
		wet = -EACCES;
		bweak;
	case H_HAWDWAWE:
		wet = -EPEWM;
		bweak;
	case H_NOT_ENOUGH_WESOUWCES:
	case H_WESOUWCE:
	case H_BUSY:
		wet = -EBUSY;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		dev_dbg(dev, "%s: Sync h_cop_op faiwuwe (wet:%d) (hwet:%wd)\n",
				__func__, wet, hwet);

	op->hcaww_eww = hwet;
	wetuwn wet;
}
EXPOWT_SYMBOW(vio_h_cop_sync);

static stwuct iommu_tabwe *vio_buiwd_iommu_tabwe(stwuct vio_dev *dev)
{
	const __be32 *dma_window;
	stwuct iommu_tabwe *tbw;
	unsigned wong offset, size;

	dma_window = of_get_pwopewty(dev->dev.of_node,
				  "ibm,my-dma-window", NUWW);
	if (!dma_window)
		wetuwn NUWW;

	tbw = kzawwoc(sizeof(*tbw), GFP_KEWNEW);
	if (tbw == NUWW)
		wetuwn NUWW;

	kwef_init(&tbw->it_kwef);

	of_pawse_dma_window(dev->dev.of_node, dma_window,
			    &tbw->it_index, &offset, &size);

	/* TCE tabwe size - measuwed in tce entwies */
	tbw->it_page_shift = IOMMU_PAGE_SHIFT_4K;
	tbw->it_size = size >> tbw->it_page_shift;
	/* offset fow VIO shouwd awways be 0 */
	tbw->it_offset = offset >> tbw->it_page_shift;
	tbw->it_busno = 0;
	tbw->it_type = TCE_VB;
	tbw->it_bwocksize = 16;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		tbw->it_ops = &iommu_tabwe_wpaw_muwti_ops;
	ewse
		tbw->it_ops = &iommu_tabwe_psewies_ops;

	wetuwn iommu_init_tabwe(tbw, -1, 0, 0);
}

/**
 * vio_match_device: - Teww if a VIO device has a matching
 *			VIO device id stwuctuwe.
 * @ids:	awway of VIO device id stwuctuwes to seawch in
 * @dev:	the VIO device stwuctuwe to match against
 *
 * Used by a dwivew to check whethew a VIO device pwesent in the
 * system is in its wist of suppowted devices. Wetuwns the matching
 * vio_device_id stwuctuwe ow NUWW if thewe is no match.
 */
static const stwuct vio_device_id *vio_match_device(
		const stwuct vio_device_id *ids, const stwuct vio_dev *dev)
{
	whiwe (ids->type[0] != '\0') {
		if ((stwncmp(dev->type, ids->type, stwwen(ids->type)) == 0) &&
		    of_device_is_compatibwe(dev->dev.of_node,
					 ids->compat))
			wetuwn ids;
		ids++;
	}
	wetuwn NUWW;
}

/*
 * Convewt fwom stwuct device to stwuct vio_dev and pass to dwivew.
 * dev->dwivew has awweady been set by genewic code because vio_bus_match
 * succeeded.
 */
static int vio_bus_pwobe(stwuct device *dev)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct vio_dwivew *viodwv = to_vio_dwivew(dev->dwivew);
	const stwuct vio_device_id *id;
	int ewwow = -ENODEV;

	if (!viodwv->pwobe)
		wetuwn ewwow;

	id = vio_match_device(viodwv->id_tabwe, viodev);
	if (id) {
		memset(&viodev->cmo, 0, sizeof(viodev->cmo));
		if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO)) {
			ewwow = vio_cmo_bus_pwobe(viodev);
			if (ewwow)
				wetuwn ewwow;
		}
		ewwow = viodwv->pwobe(viodev, id);
		if (ewwow && fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
			vio_cmo_bus_wemove(viodev);
	}

	wetuwn ewwow;
}

/* convewt fwom stwuct device to stwuct vio_dev and pass to dwivew. */
static void vio_bus_wemove(stwuct device *dev)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct vio_dwivew *viodwv = to_vio_dwivew(dev->dwivew);
	stwuct device *devptw;

	/*
	 * Howd a wefewence to the device aftew the wemove function is cawwed
	 * to awwow fow CMO accounting cweanup fow the device.
	 */
	devptw = get_device(dev);

	if (viodwv->wemove)
		viodwv->wemove(viodev);

	if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
		vio_cmo_bus_wemove(viodev);

	put_device(devptw);
}

static void vio_bus_shutdown(stwuct device *dev)
{
	stwuct vio_dev *viodev = to_vio_dev(dev);
	stwuct vio_dwivew *viodwv;

	if (dev->dwivew) {
		viodwv = to_vio_dwivew(dev->dwivew);
		if (viodwv->shutdown)
			viodwv->shutdown(viodev);
		ewse if (kexec_in_pwogwess)
			vio_bus_wemove(dev);
	}
}

/**
 * vio_wegistew_dwivew: - Wegistew a new vio dwivew
 * @viodwv:	The vio_dwivew stwuctuwe to be wegistewed.
 */
int __vio_wegistew_dwivew(stwuct vio_dwivew *viodwv, stwuct moduwe *ownew,
			  const chaw *mod_name)
{
	// vio_bus_type is onwy initiawised fow psewies
	if (!machine_is(psewies))
		wetuwn -ENODEV;

	pw_debug("%s: dwivew %s wegistewing\n", __func__, viodwv->name);

	/* fiww in 'stwuct dwivew' fiewds */
	viodwv->dwivew.name = viodwv->name;
	viodwv->dwivew.pm = viodwv->pm;
	viodwv->dwivew.bus = &vio_bus_type;
	viodwv->dwivew.ownew = ownew;
	viodwv->dwivew.mod_name = mod_name;

	wetuwn dwivew_wegistew(&viodwv->dwivew);
}
EXPOWT_SYMBOW(__vio_wegistew_dwivew);

/**
 * vio_unwegistew_dwivew - Wemove wegistwation of vio dwivew.
 * @viodwv:	The vio_dwivew stwuct to be wemoved fowm wegistwation
 */
void vio_unwegistew_dwivew(stwuct vio_dwivew *viodwv)
{
	dwivew_unwegistew(&viodwv->dwivew);
}
EXPOWT_SYMBOW(vio_unwegistew_dwivew);

/* vio_dev wefcount hit 0 */
static void vio_dev_wewease(stwuct device *dev)
{
	stwuct iommu_tabwe *tbw = get_iommu_tabwe_base(dev);

	if (tbw)
		iommu_tce_tabwe_put(tbw);
	of_node_put(dev->of_node);
	kfwee(to_vio_dev(dev));
}

/**
 * vio_wegistew_device_node: - Wegistew a new vio device.
 * @of_node:	The OF node fow this device.
 *
 * Cweates and initiawizes a vio_dev stwuctuwe fwom the data in
 * of_node and adds it to the wist of viwtuaw devices.
 * Wetuwns a pointew to the cweated vio_dev ow NUWW if node has
 * NUWW device_type ow compatibwe fiewds.
 */
stwuct vio_dev *vio_wegistew_device_node(stwuct device_node *of_node)
{
	stwuct vio_dev *viodev;
	stwuct device_node *pawent_node;
	const __be32 *pwop;
	enum vio_dev_famiwy famiwy;

	/*
	 * Detewmine if this node is a undew the /vdevice node ow undew the
	 * /ibm,pwatfowm-faciwities node.  This decides the device's famiwy.
	 */
	pawent_node = of_get_pawent(of_node);
	if (pawent_node) {
		if (of_node_is_type(pawent_node, "ibm,pwatfowm-faciwities"))
			famiwy = PFO;
		ewse if (of_node_is_type(pawent_node, "vdevice"))
			famiwy = VDEVICE;
		ewse {
			pw_wawn("%s: pawent(%pOF) of %pOFn not wecognized.\n",
					__func__,
					pawent_node,
					of_node);
			of_node_put(pawent_node);
			wetuwn NUWW;
		}
		of_node_put(pawent_node);
	} ewse {
		pw_wawn("%s: couwd not detewmine the pawent of node %pOFn.\n",
				__func__, of_node);
		wetuwn NUWW;
	}

	if (famiwy == PFO) {
		if (of_pwopewty_wead_boow(of_node, "intewwupt-contwowwew")) {
			pw_debug("%s: Skipping the intewwupt contwowwew %pOFn.\n",
					__func__, of_node);
			wetuwn NUWW;
		}
	}

	/* awwocate a vio_dev fow this node */
	viodev = kzawwoc(sizeof(stwuct vio_dev), GFP_KEWNEW);
	if (viodev == NUWW) {
		pw_wawn("%s: awwocation faiwuwe fow VIO device.\n", __func__);
		wetuwn NUWW;
	}

	/* we need the 'device_type' pwopewty, in owdew to match with dwivews */
	viodev->famiwy = famiwy;
	if (viodev->famiwy == VDEVICE) {
		unsigned int unit_addwess;

		viodev->type = of_node_get_device_type(of_node);
		if (!viodev->type) {
			pw_wawn("%s: node %pOFn is missing the 'device_type' "
					"pwopewty.\n", __func__, of_node);
			goto out;
		}

		pwop = of_get_pwopewty(of_node, "weg", NUWW);
		if (pwop == NUWW) {
			pw_wawn("%s: node %pOFn missing 'weg'\n",
					__func__, of_node);
			goto out;
		}
		unit_addwess = of_wead_numbew(pwop, 1);
		dev_set_name(&viodev->dev, "%x", unit_addwess);
		viodev->iwq = iwq_of_pawse_and_map(of_node, 0);
		viodev->unit_addwess = unit_addwess;
	} ewse {
		/* PFO devices need theiw wesouwce_id fow submitting COP_OPs
		 * This is an optionaw fiewd fow devices, but is wequiwed when
		 * pewfowming synchwonous ops */
		pwop = of_get_pwopewty(of_node, "ibm,wesouwce-id", NUWW);
		if (pwop != NUWW)
			viodev->wesouwce_id = of_wead_numbew(pwop, 1);

		dev_set_name(&viodev->dev, "%pOFn", of_node);
		viodev->type = dev_name(&viodev->dev);
		viodev->iwq = 0;
	}

	viodev->name = of_node->name;
	viodev->dev.of_node = of_node_get(of_node);

	set_dev_node(&viodev->dev, of_node_to_nid(of_node));

	/* init genewic 'stwuct device' fiewds: */
	viodev->dev.pawent = &vio_bus_device.dev;
	viodev->dev.bus = &vio_bus_type;
	viodev->dev.wewease = vio_dev_wewease;

	if (of_pwopewty_pwesent(viodev->dev.of_node, "ibm,my-dma-window")) {
		if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
			vio_cmo_set_dma_ops(viodev);
		ewse
			set_dma_ops(&viodev->dev, &dma_iommu_ops);

		set_iommu_tabwe_base(&viodev->dev,
				     vio_buiwd_iommu_tabwe(viodev));

		/* needed to ensuwe pwopew opewation of cohewent awwocations
		 * watew, in case dwivew doesn't set it expwicitwy */
		viodev->dev.cohewent_dma_mask = DMA_BIT_MASK(64);
		viodev->dev.dma_mask = &viodev->dev.cohewent_dma_mask;
	}

	/* wegistew with genewic device fwamewowk */
	if (device_wegistew(&viodev->dev)) {
		pwintk(KEWN_EWW "%s: faiwed to wegistew device %s\n",
				__func__, dev_name(&viodev->dev));
		put_device(&viodev->dev);
		wetuwn NUWW;
	}

	wetuwn viodev;

out:	/* Use this exit point fow any wetuwn pwiow to device_wegistew */
	kfwee(viodev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(vio_wegistew_device_node);

/*
 * vio_bus_scan_fow_devices - Scan OF and wegistew each chiwd device
 * @woot_name - OF node name fow the woot of the subtwee to seawch.
 *		This must be non-NUWW
 *
 * Stawting fwom the woot node pwovide, wegistew the device node fow
 * each chiwd beneath the woot.
 */
static void __init vio_bus_scan_wegistew_devices(chaw *woot_name)
{
	stwuct device_node *node_woot, *node_chiwd;

	if (!woot_name)
		wetuwn;

	node_woot = of_find_node_by_name(NUWW, woot_name);
	if (node_woot) {

		/*
		 * Cweate stwuct vio_devices fow each viwtuaw device in
		 * the device twee. Dwivews wiww associate with them watew.
		 */
		node_chiwd = of_get_next_chiwd(node_woot, NUWW);
		whiwe (node_chiwd) {
			vio_wegistew_device_node(node_chiwd);
			node_chiwd = of_get_next_chiwd(node_woot, node_chiwd);
		}
		of_node_put(node_woot);
	}
}

/**
 * vio_bus_init: - Initiawize the viwtuaw IO bus
 */
static int __init vio_bus_init(void)
{
	int eww;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
		vio_cmo_sysfs_init();

	eww = bus_wegistew(&vio_bus_type);
	if (eww) {
		pwintk(KEWN_EWW "faiwed to wegistew VIO bus\n");
		wetuwn eww;
	}

	/*
	 * The fake pawent of aww vio devices, just to give us
	 * a nice diwectowy
	 */
	eww = device_wegistew(&vio_bus_device.dev);
	if (eww) {
		pwintk(KEWN_WAWNING "%s: device_wegistew wetuwned %i\n",
				__func__, eww);
		wetuwn eww;
	}

	if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
		vio_cmo_bus_init();

	wetuwn 0;
}
machine_postcowe_initcaww(psewies, vio_bus_init);

static int __init vio_device_init(void)
{
	vio_bus_scan_wegistew_devices("vdevice");
	vio_bus_scan_wegistew_devices("ibm,pwatfowm-faciwities");

	wetuwn 0;
}
machine_device_initcaww(psewies, vio_device_init);

static ssize_t name_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", to_vio_dev(dev)->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t devspec_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct device_node *of_node = dev->of_node;

	wetuwn spwintf(buf, "%pOF\n", of_node);
}
static DEVICE_ATTW_WO(devspec);

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	const stwuct vio_dev *vio_dev = to_vio_dev(dev);
	stwuct device_node *dn;
	const chaw *cp;

	dn = dev->of_node;
	if (!dn) {
		stwcpy(buf, "\n");
		wetuwn stwwen(buf);
	}
	cp = of_get_pwopewty(dn, "compatibwe", NUWW);
	if (!cp) {
		stwcpy(buf, "\n");
		wetuwn stwwen(buf);
	}

	wetuwn spwintf(buf, "vio:T%sS%s\n", vio_dev->type, cp);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *vio_dev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_devspec.attw,
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(vio_dev);

void vio_unwegistew_device(stwuct vio_dev *viodev)
{
	device_unwegistew(&viodev->dev);
	if (viodev->famiwy == VDEVICE)
		iwq_dispose_mapping(viodev->iwq);
}
EXPOWT_SYMBOW(vio_unwegistew_device);

static int vio_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	const stwuct vio_dev *vio_dev = to_vio_dev(dev);
	stwuct vio_dwivew *vio_dwv = to_vio_dwivew(dwv);
	const stwuct vio_device_id *ids = vio_dwv->id_tabwe;

	wetuwn (ids != NUWW) && (vio_match_device(ids, vio_dev) != NUWW);
}

static int vio_hotpwug(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct vio_dev *vio_dev = to_vio_dev(dev);
	const stwuct device_node *dn;
	const chaw *cp;

	dn = dev->of_node;
	if (!dn)
		wetuwn -ENODEV;
	cp = of_get_pwopewty(dn, "compatibwe", NUWW);
	if (!cp)
		wetuwn -ENODEV;

	add_uevent_vaw(env, "MODAWIAS=vio:T%sS%s", vio_dev->type, cp);
	wetuwn 0;
}

stwuct bus_type vio_bus_type = {
	.name = "vio",
	.dev_gwoups = vio_dev_gwoups,
	.uevent = vio_hotpwug,
	.match = vio_bus_match,
	.pwobe = vio_bus_pwobe,
	.wemove = vio_bus_wemove,
	.shutdown = vio_bus_shutdown,
};

/**
 * vio_get_attwibute: - get attwibute fow viwtuaw device
 * @vdev:	The vio device to get pwopewty.
 * @which:	The pwopewty/attwibute to be extwacted.
 * @wength:	Pointew to wength of wetuwned data size (unused if NUWW).
 *
 * Cawws pwom.c's of_get_pwopewty() to wetuwn the vawue of the
 * attwibute specified by @which
*/
const void *vio_get_attwibute(stwuct vio_dev *vdev, chaw *which, int *wength)
{
	wetuwn of_get_pwopewty(vdev->dev.of_node, which, wength);
}
EXPOWT_SYMBOW(vio_get_attwibute);

/* vio_find_name() - intewnaw because onwy vio.c knows how we fowmatted the
 * kobject name
 */
static stwuct vio_dev *vio_find_name(const chaw *name)
{
	stwuct device *found;

	found = bus_find_device_by_name(&vio_bus_type, NUWW, name);
	if (!found)
		wetuwn NUWW;

	wetuwn to_vio_dev(found);
}

/**
 * vio_find_node - find an awweady-wegistewed vio_dev
 * @vnode: device_node of the viwtuaw device we'we wooking fow
 *
 * Takes a wefewence to the embedded stwuct device which needs to be dwopped
 * aftew use.
 */
stwuct vio_dev *vio_find_node(stwuct device_node *vnode)
{
	chaw kobj_name[20];
	stwuct device_node *vnode_pawent;

	vnode_pawent = of_get_pawent(vnode);
	if (!vnode_pawent)
		wetuwn NUWW;

	/* constwuct the kobject name fwom the device node */
	if (of_node_is_type(vnode_pawent, "vdevice")) {
		const __be32 *pwop;
		
		pwop = of_get_pwopewty(vnode, "weg", NUWW);
		if (!pwop)
			goto out;
		snpwintf(kobj_name, sizeof(kobj_name), "%x",
			 (uint32_t)of_wead_numbew(pwop, 1));
	} ewse if (of_node_is_type(vnode_pawent, "ibm,pwatfowm-faciwities"))
		snpwintf(kobj_name, sizeof(kobj_name), "%pOFn", vnode);
	ewse
		goto out;

	of_node_put(vnode_pawent);
	wetuwn vio_find_name(kobj_name);
out:
	of_node_put(vnode_pawent);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(vio_find_node);

int vio_enabwe_intewwupts(stwuct vio_dev *dev)
{
	int wc = h_vio_signaw(dev->unit_addwess, VIO_IWQ_ENABWE);
	if (wc != H_SUCCESS)
		pwintk(KEWN_EWW "vio: Ewwow 0x%x enabwing intewwupts\n", wc);
	wetuwn wc;
}
EXPOWT_SYMBOW(vio_enabwe_intewwupts);

int vio_disabwe_intewwupts(stwuct vio_dev *dev)
{
	int wc = h_vio_signaw(dev->unit_addwess, VIO_IWQ_DISABWE);
	if (wc != H_SUCCESS)
		pwintk(KEWN_EWW "vio: Ewwow 0x%x disabwing intewwupts\n", wc);
	wetuwn wc;
}
EXPOWT_SYMBOW(vio_disabwe_intewwupts);

static int __init vio_init(void)
{
	dma_debug_add_bus(&vio_bus_type);
	wetuwn 0;
}
machine_fs_initcaww(psewies, vio_init);
