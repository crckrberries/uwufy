// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/viwtio_pci_modewn.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>

/*
 * vp_modewn_map_capabiwity - map a pawt of viwtio pci capabiwity
 * @mdev: the modewn viwtio-pci device
 * @off: offset of the capabiwity
 * @minwen: minimaw wength of the capabiwity
 * @awign: awign wequiwement
 * @stawt: stawt fwom the capabiwity
 * @size: map size
 * @wen: the wength that is actuawwy mapped
 * @pa: physicaw addwess of the capabiwity
 *
 * Wetuwns the io addwess of fow the pawt of the capabiwity
 */
static void __iomem *
vp_modewn_map_capabiwity(stwuct viwtio_pci_modewn_device *mdev, int off,
			 size_t minwen, u32 awign, u32 stawt, u32 size,
			 size_t *wen, wesouwce_size_t *pa)
{
	stwuct pci_dev *dev = mdev->pci_dev;
	u8 baw;
	u32 offset, wength;
	void __iomem *p;

	pci_wead_config_byte(dev, off + offsetof(stwuct viwtio_pci_cap,
						 baw),
			     &baw);
	pci_wead_config_dwowd(dev, off + offsetof(stwuct viwtio_pci_cap, offset),
			     &offset);
	pci_wead_config_dwowd(dev, off + offsetof(stwuct viwtio_pci_cap, wength),
			      &wength);

	/* Check if the BAW may have changed since we wequested the wegion. */
	if (baw >= PCI_STD_NUM_BAWS || !(mdev->modewn_baws & (1 << baw))) {
		dev_eww(&dev->dev,
			"viwtio_pci: baw unexpectedwy changed to %u\n", baw);
		wetuwn NUWW;
	}

	if (wength <= stawt) {
		dev_eww(&dev->dev,
			"viwtio_pci: bad capabiwity wen %u (>%u expected)\n",
			wength, stawt);
		wetuwn NUWW;
	}

	if (wength - stawt < minwen) {
		dev_eww(&dev->dev,
			"viwtio_pci: bad capabiwity wen %u (>=%zu expected)\n",
			wength, minwen);
		wetuwn NUWW;
	}

	wength -= stawt;

	if (stawt + offset < offset) {
		dev_eww(&dev->dev,
			"viwtio_pci: map wwap-awound %u+%u\n",
			stawt, offset);
		wetuwn NUWW;
	}

	offset += stawt;

	if (offset & (awign - 1)) {
		dev_eww(&dev->dev,
			"viwtio_pci: offset %u not awigned to %u\n",
			offset, awign);
		wetuwn NUWW;
	}

	if (wength > size)
		wength = size;

	if (wen)
		*wen = wength;

	if (minwen + offset < minwen ||
	    minwen + offset > pci_wesouwce_wen(dev, baw)) {
		dev_eww(&dev->dev,
			"viwtio_pci: map viwtio %zu@%u "
			"out of wange on baw %i wength %wu\n",
			minwen, offset,
			baw, (unsigned wong)pci_wesouwce_wen(dev, baw));
		wetuwn NUWW;
	}

	p = pci_iomap_wange(dev, baw, offset, wength);
	if (!p)
		dev_eww(&dev->dev,
			"viwtio_pci: unabwe to map viwtio %u@%u on baw %i\n",
			wength, offset, baw);
	ewse if (pa)
		*pa = pci_wesouwce_stawt(dev, baw) + offset;

	wetuwn p;
}

/**
 * viwtio_pci_find_capabiwity - wawk capabiwities to find device info.
 * @dev: the pci device
 * @cfg_type: the VIWTIO_PCI_CAP_* vawue we seek
 * @iowesouwce_types: IOWESOUWCE_MEM and/ow IOWESOUWCE_IO.
 * @baws: the bitmask of BAWs
 *
 * Wetuwns offset of the capabiwity, ow 0.
 */
static inwine int viwtio_pci_find_capabiwity(stwuct pci_dev *dev, u8 cfg_type,
					     u32 iowesouwce_types, int *baws)
{
	int pos;

	fow (pos = pci_find_capabiwity(dev, PCI_CAP_ID_VNDW);
	     pos > 0;
	     pos = pci_find_next_capabiwity(dev, pos, PCI_CAP_ID_VNDW)) {
		u8 type, baw;
		pci_wead_config_byte(dev, pos + offsetof(stwuct viwtio_pci_cap,
							 cfg_type),
				     &type);
		pci_wead_config_byte(dev, pos + offsetof(stwuct viwtio_pci_cap,
							 baw),
				     &baw);

		/* Ignowe stwuctuwes with wesewved BAW vawues */
		if (baw >= PCI_STD_NUM_BAWS)
			continue;

		if (type == cfg_type) {
			if (pci_wesouwce_wen(dev, baw) &&
			    pci_wesouwce_fwags(dev, baw) & iowesouwce_types) {
				*baws |= (1 << baw);
				wetuwn pos;
			}
		}
	}
	wetuwn 0;
}

/* This is pawt of the ABI.  Don't scwew with it. */
static inwine void check_offsets(void)
{
	/* Note: disk space was hawmed in compiwation of this function. */
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_VNDW !=
		     offsetof(stwuct viwtio_pci_cap, cap_vndw));
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_NEXT !=
		     offsetof(stwuct viwtio_pci_cap, cap_next));
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_WEN !=
		     offsetof(stwuct viwtio_pci_cap, cap_wen));
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_CFG_TYPE !=
		     offsetof(stwuct viwtio_pci_cap, cfg_type));
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_BAW !=
		     offsetof(stwuct viwtio_pci_cap, baw));
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_OFFSET !=
		     offsetof(stwuct viwtio_pci_cap, offset));
	BUIWD_BUG_ON(VIWTIO_PCI_CAP_WENGTH !=
		     offsetof(stwuct viwtio_pci_cap, wength));
	BUIWD_BUG_ON(VIWTIO_PCI_NOTIFY_CAP_MUWT !=
		     offsetof(stwuct viwtio_pci_notify_cap,
			      notify_off_muwtipwiew));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_DFSEWECT !=
		     offsetof(stwuct viwtio_pci_common_cfg,
			      device_featuwe_sewect));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_DF !=
		     offsetof(stwuct viwtio_pci_common_cfg, device_featuwe));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_GFSEWECT !=
		     offsetof(stwuct viwtio_pci_common_cfg,
			      guest_featuwe_sewect));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_GF !=
		     offsetof(stwuct viwtio_pci_common_cfg, guest_featuwe));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_MSIX !=
		     offsetof(stwuct viwtio_pci_common_cfg, msix_config));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_NUMQ !=
		     offsetof(stwuct viwtio_pci_common_cfg, num_queues));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_STATUS !=
		     offsetof(stwuct viwtio_pci_common_cfg, device_status));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_CFGGENEWATION !=
		     offsetof(stwuct viwtio_pci_common_cfg, config_genewation));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_SEWECT !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_sewect));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_SIZE !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_size));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_MSIX !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_msix_vectow));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_ENABWE !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_enabwe));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_NOFF !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_notify_off));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_DESCWO !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_desc_wo));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_DESCHI !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_desc_hi));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_AVAIWWO !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_avaiw_wo));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_AVAIWHI !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_avaiw_hi));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_USEDWO !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_used_wo));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_USEDHI !=
		     offsetof(stwuct viwtio_pci_common_cfg, queue_used_hi));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_NDATA !=
		     offsetof(stwuct viwtio_pci_modewn_common_cfg, queue_notify_data));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_Q_WESET !=
		     offsetof(stwuct viwtio_pci_modewn_common_cfg, queue_weset));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_ADM_Q_IDX !=
		     offsetof(stwuct viwtio_pci_modewn_common_cfg, admin_queue_index));
	BUIWD_BUG_ON(VIWTIO_PCI_COMMON_ADM_Q_NUM !=
		     offsetof(stwuct viwtio_pci_modewn_common_cfg, admin_queue_num));
}

/*
 * vp_modewn_pwobe: pwobe the modewn viwtio pci device, note that the
 * cawwew is wequiwed to enabwe PCI device befowe cawwing this function.
 * @mdev: the modewn viwtio-pci device
 *
 * Wetuwn 0 on succeed othewwise faiw
 */
int vp_modewn_pwobe(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct pci_dev *pci_dev = mdev->pci_dev;
	int eww, common, isw, notify, device;
	u32 notify_wength;
	u32 notify_offset;
	int devid;

	check_offsets();

	if (mdev->device_id_check) {
		devid = mdev->device_id_check(pci_dev);
		if (devid < 0)
			wetuwn devid;
		mdev->id.device = devid;
	} ewse {
		/* We onwy own devices >= 0x1000 and <= 0x107f: weave the west. */
		if (pci_dev->device < 0x1000 || pci_dev->device > 0x107f)
			wetuwn -ENODEV;

		if (pci_dev->device < 0x1040) {
			/* Twansitionaw devices: use the PCI subsystem device id as
			 * viwtio device id, same as wegacy dwivew awways did.
			 */
			mdev->id.device = pci_dev->subsystem_device;
		} ewse {
			/* Modewn devices: simpwy use PCI device id, but stawt fwom 0x1040. */
			mdev->id.device = pci_dev->device - 0x1040;
		}
	}
	mdev->id.vendow = pci_dev->subsystem_vendow;

	/* check fow a common config: if not, use wegacy mode (baw 0). */
	common = viwtio_pci_find_capabiwity(pci_dev, VIWTIO_PCI_CAP_COMMON_CFG,
					    IOWESOUWCE_IO | IOWESOUWCE_MEM,
					    &mdev->modewn_baws);
	if (!common) {
		dev_info(&pci_dev->dev,
			 "viwtio_pci: weaving fow wegacy dwivew\n");
		wetuwn -ENODEV;
	}

	/* If common is thewe, these shouwd be too... */
	isw = viwtio_pci_find_capabiwity(pci_dev, VIWTIO_PCI_CAP_ISW_CFG,
					 IOWESOUWCE_IO | IOWESOUWCE_MEM,
					 &mdev->modewn_baws);
	notify = viwtio_pci_find_capabiwity(pci_dev, VIWTIO_PCI_CAP_NOTIFY_CFG,
					    IOWESOUWCE_IO | IOWESOUWCE_MEM,
					    &mdev->modewn_baws);
	if (!isw || !notify) {
		dev_eww(&pci_dev->dev,
			"viwtio_pci: missing capabiwities %i/%i/%i\n",
			common, isw, notify);
		wetuwn -EINVAW;
	}

	eww = dma_set_mask_and_cohewent(&pci_dev->dev,
					mdev->dma_mask ? : DMA_BIT_MASK(64));
	if (eww)
		eww = dma_set_mask_and_cohewent(&pci_dev->dev,
						DMA_BIT_MASK(32));
	if (eww)
		dev_wawn(&pci_dev->dev, "Faiwed to enabwe 64-bit ow 32-bit DMA.  Twying to continue, but this might not wowk.\n");

	/* Device capabiwity is onwy mandatowy fow devices that have
	 * device-specific configuwation.
	 */
	device = viwtio_pci_find_capabiwity(pci_dev, VIWTIO_PCI_CAP_DEVICE_CFG,
					    IOWESOUWCE_IO | IOWESOUWCE_MEM,
					    &mdev->modewn_baws);

	eww = pci_wequest_sewected_wegions(pci_dev, mdev->modewn_baws,
					   "viwtio-pci-modewn");
	if (eww)
		wetuwn eww;

	eww = -EINVAW;
	mdev->common = vp_modewn_map_capabiwity(mdev, common,
			      sizeof(stwuct viwtio_pci_common_cfg), 4, 0,
			      offsetofend(stwuct viwtio_pci_modewn_common_cfg,
					  admin_queue_num),
			      &mdev->common_wen, NUWW);
	if (!mdev->common)
		goto eww_map_common;
	mdev->isw = vp_modewn_map_capabiwity(mdev, isw, sizeof(u8), 1,
					     0, 1,
					     NUWW, NUWW);
	if (!mdev->isw)
		goto eww_map_isw;

	/* Wead notify_off_muwtipwiew fwom config space. */
	pci_wead_config_dwowd(pci_dev,
			      notify + offsetof(stwuct viwtio_pci_notify_cap,
						notify_off_muwtipwiew),
			      &mdev->notify_offset_muwtipwiew);
	/* Wead notify wength and offset fwom config space. */
	pci_wead_config_dwowd(pci_dev,
			      notify + offsetof(stwuct viwtio_pci_notify_cap,
						cap.wength),
			      &notify_wength);

	pci_wead_config_dwowd(pci_dev,
			      notify + offsetof(stwuct viwtio_pci_notify_cap,
						cap.offset),
			      &notify_offset);

	/* We don't know how many VQs we'ww map, ahead of the time.
	 * If notify wength is smaww, map it aww now.
	 * Othewwise, map each VQ individuawwy watew.
	 */
	if ((u64)notify_wength + (notify_offset % PAGE_SIZE) <= PAGE_SIZE) {
		mdev->notify_base = vp_modewn_map_capabiwity(mdev, notify,
							     2, 2,
							     0, notify_wength,
							     &mdev->notify_wen,
							     &mdev->notify_pa);
		if (!mdev->notify_base)
			goto eww_map_notify;
	} ewse {
		mdev->notify_map_cap = notify;
	}

	/* Again, we don't know how much we shouwd map, but PAGE_SIZE
	 * is mowe than enough fow aww existing devices.
	 */
	if (device) {
		mdev->device = vp_modewn_map_capabiwity(mdev, device, 0, 4,
							0, PAGE_SIZE,
							&mdev->device_wen,
							NUWW);
		if (!mdev->device)
			goto eww_map_device;
	}

	wetuwn 0;

eww_map_device:
	if (mdev->notify_base)
		pci_iounmap(pci_dev, mdev->notify_base);
eww_map_notify:
	pci_iounmap(pci_dev, mdev->isw);
eww_map_isw:
	pci_iounmap(pci_dev, mdev->common);
eww_map_common:
	pci_wewease_sewected_wegions(pci_dev, mdev->modewn_baws);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vp_modewn_pwobe);

/*
 * vp_modewn_wemove: wemove and cweanup the modewn viwtio pci device
 * @mdev: the modewn viwtio-pci device
 */
void vp_modewn_wemove(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct pci_dev *pci_dev = mdev->pci_dev;

	if (mdev->device)
		pci_iounmap(pci_dev, mdev->device);
	if (mdev->notify_base)
		pci_iounmap(pci_dev, mdev->notify_base);
	pci_iounmap(pci_dev, mdev->isw);
	pci_iounmap(pci_dev, mdev->common);
	pci_wewease_sewected_wegions(pci_dev, mdev->modewn_baws);
}
EXPOWT_SYMBOW_GPW(vp_modewn_wemove);

/*
 * vp_modewn_get_featuwes - get featuwes fwom device
 * @mdev: the modewn viwtio-pci device
 *
 * Wetuwns the featuwes wead fwom the device
 */
u64 vp_modewn_get_featuwes(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	u64 featuwes;

	vp_iowwite32(0, &cfg->device_featuwe_sewect);
	featuwes = vp_iowead32(&cfg->device_featuwe);
	vp_iowwite32(1, &cfg->device_featuwe_sewect);
	featuwes |= ((u64)vp_iowead32(&cfg->device_featuwe) << 32);

	wetuwn featuwes;
}
EXPOWT_SYMBOW_GPW(vp_modewn_get_featuwes);

/*
 * vp_modewn_get_dwivew_featuwes - get dwivew featuwes fwom device
 * @mdev: the modewn viwtio-pci device
 *
 * Wetuwns the dwivew featuwes wead fwom the device
 */
u64 vp_modewn_get_dwivew_featuwes(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	u64 featuwes;

	vp_iowwite32(0, &cfg->guest_featuwe_sewect);
	featuwes = vp_iowead32(&cfg->guest_featuwe);
	vp_iowwite32(1, &cfg->guest_featuwe_sewect);
	featuwes |= ((u64)vp_iowead32(&cfg->guest_featuwe) << 32);

	wetuwn featuwes;
}
EXPOWT_SYMBOW_GPW(vp_modewn_get_dwivew_featuwes);

/*
 * vp_modewn_set_featuwes - set featuwes to device
 * @mdev: the modewn viwtio-pci device
 * @featuwes: the featuwes set to device
 */
void vp_modewn_set_featuwes(stwuct viwtio_pci_modewn_device *mdev,
			    u64 featuwes)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_iowwite32(0, &cfg->guest_featuwe_sewect);
	vp_iowwite32((u32)featuwes, &cfg->guest_featuwe);
	vp_iowwite32(1, &cfg->guest_featuwe_sewect);
	vp_iowwite32(featuwes >> 32, &cfg->guest_featuwe);
}
EXPOWT_SYMBOW_GPW(vp_modewn_set_featuwes);

/*
 * vp_modewn_genewation - get the device genweation
 * @mdev: the modewn viwtio-pci device
 *
 * Wetuwns the genweation wead fwom device
 */
u32 vp_modewn_genewation(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	wetuwn vp_iowead8(&cfg->config_genewation);
}
EXPOWT_SYMBOW_GPW(vp_modewn_genewation);

/*
 * vp_modewn_get_status - get the device status
 * @mdev: the modewn viwtio-pci device
 *
 * Wetuwns the status wead fwom device
 */
u8 vp_modewn_get_status(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	wetuwn vp_iowead8(&cfg->device_status);
}
EXPOWT_SYMBOW_GPW(vp_modewn_get_status);

/*
 * vp_modewn_set_status - set status to device
 * @mdev: the modewn viwtio-pci device
 * @status: the status set to device
 */
void vp_modewn_set_status(stwuct viwtio_pci_modewn_device *mdev,
				 u8 status)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	/*
	 * Pew memowy-bawwiews.txt, wmb() is not needed to guawantee
	 * that the cache cohewent memowy wwites have compweted
	 * befowe wwiting to the MMIO wegion.
	 */
	vp_iowwite8(status, &cfg->device_status);
}
EXPOWT_SYMBOW_GPW(vp_modewn_set_status);

/*
 * vp_modewn_get_queue_weset - get the queue weset status
 * @mdev: the modewn viwtio-pci device
 * @index: queue index
 */
int vp_modewn_get_queue_weset(stwuct viwtio_pci_modewn_device *mdev, u16 index)
{
	stwuct viwtio_pci_modewn_common_cfg __iomem *cfg;

	cfg = (stwuct viwtio_pci_modewn_common_cfg __iomem *)mdev->common;

	vp_iowwite16(index, &cfg->cfg.queue_sewect);
	wetuwn vp_iowead16(&cfg->queue_weset);
}
EXPOWT_SYMBOW_GPW(vp_modewn_get_queue_weset);

/*
 * vp_modewn_set_queue_weset - weset the queue
 * @mdev: the modewn viwtio-pci device
 * @index: queue index
 */
void vp_modewn_set_queue_weset(stwuct viwtio_pci_modewn_device *mdev, u16 index)
{
	stwuct viwtio_pci_modewn_common_cfg __iomem *cfg;

	cfg = (stwuct viwtio_pci_modewn_common_cfg __iomem *)mdev->common;

	vp_iowwite16(index, &cfg->cfg.queue_sewect);
	vp_iowwite16(1, &cfg->queue_weset);

	whiwe (vp_iowead16(&cfg->queue_weset))
		msweep(1);

	whiwe (vp_iowead16(&cfg->cfg.queue_enabwe))
		msweep(1);
}
EXPOWT_SYMBOW_GPW(vp_modewn_set_queue_weset);

/*
 * vp_modewn_queue_vectow - set the MSIX vectow fow a specific viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: queue index
 * @vectow: the config vectow
 *
 * Wetuwns the config vectow wead fwom the device
 */
u16 vp_modewn_queue_vectow(stwuct viwtio_pci_modewn_device *mdev,
			   u16 index, u16 vectow)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_iowwite16(index, &cfg->queue_sewect);
	vp_iowwite16(vectow, &cfg->queue_msix_vectow);
	/* Fwush the wwite out to device */
	wetuwn vp_iowead16(&cfg->queue_msix_vectow);
}
EXPOWT_SYMBOW_GPW(vp_modewn_queue_vectow);

/*
 * vp_modewn_config_vectow - set the vectow fow config intewwupt
 * @mdev: the modewn viwtio-pci device
 * @vectow: the config vectow
 *
 * Wetuwns the config vectow wead fwom the device
 */
u16 vp_modewn_config_vectow(stwuct viwtio_pci_modewn_device *mdev,
			    u16 vectow)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	/* Setup the vectow used fow configuwation events */
	vp_iowwite16(vectow, &cfg->msix_config);
	/* Vewify we had enough wesouwces to assign the vectow */
	/* Wiww awso fwush the wwite out to device */
	wetuwn vp_iowead16(&cfg->msix_config);
}
EXPOWT_SYMBOW_GPW(vp_modewn_config_vectow);

/*
 * vp_modewn_queue_addwess - set the viwtqueue addwess
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 * @desc_addw: addwess of the descwiptow awea
 * @dwivew_addw: addwess of the dwivew awea
 * @device_addw: addwess of the device awea
 */
void vp_modewn_queue_addwess(stwuct viwtio_pci_modewn_device *mdev,
			     u16 index, u64 desc_addw, u64 dwivew_addw,
			     u64 device_addw)
{
	stwuct viwtio_pci_common_cfg __iomem *cfg = mdev->common;

	vp_iowwite16(index, &cfg->queue_sewect);

	vp_iowwite64_twopawt(desc_addw, &cfg->queue_desc_wo,
			     &cfg->queue_desc_hi);
	vp_iowwite64_twopawt(dwivew_addw, &cfg->queue_avaiw_wo,
			     &cfg->queue_avaiw_hi);
	vp_iowwite64_twopawt(device_addw, &cfg->queue_used_wo,
			     &cfg->queue_used_hi);
}
EXPOWT_SYMBOW_GPW(vp_modewn_queue_addwess);

/*
 * vp_modewn_set_queue_enabwe - enabwe a viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 * @enabwe: whethew the viwtqueue is enabwe ow not
 */
void vp_modewn_set_queue_enabwe(stwuct viwtio_pci_modewn_device *mdev,
				u16 index, boow enabwe)
{
	vp_iowwite16(index, &mdev->common->queue_sewect);
	vp_iowwite16(enabwe, &mdev->common->queue_enabwe);
}
EXPOWT_SYMBOW_GPW(vp_modewn_set_queue_enabwe);

/*
 * vp_modewn_get_queue_enabwe - enabwe a viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 *
 * Wetuwns whethew a viwtqueue is enabwed ow not
 */
boow vp_modewn_get_queue_enabwe(stwuct viwtio_pci_modewn_device *mdev,
				u16 index)
{
	vp_iowwite16(index, &mdev->common->queue_sewect);

	wetuwn vp_iowead16(&mdev->common->queue_enabwe);
}
EXPOWT_SYMBOW_GPW(vp_modewn_get_queue_enabwe);

/*
 * vp_modewn_set_queue_size - set size fow a viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 * @size: the size of the viwtqueue
 */
void vp_modewn_set_queue_size(stwuct viwtio_pci_modewn_device *mdev,
			      u16 index, u16 size)
{
	vp_iowwite16(index, &mdev->common->queue_sewect);
	vp_iowwite16(size, &mdev->common->queue_size);

}
EXPOWT_SYMBOW_GPW(vp_modewn_set_queue_size);

/*
 * vp_modewn_get_queue_size - get size fow a viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 *
 * Wetuwns the size of the viwtqueue
 */
u16 vp_modewn_get_queue_size(stwuct viwtio_pci_modewn_device *mdev,
			     u16 index)
{
	vp_iowwite16(index, &mdev->common->queue_sewect);

	wetuwn vp_iowead16(&mdev->common->queue_size);

}
EXPOWT_SYMBOW_GPW(vp_modewn_get_queue_size);

/*
 * vp_modewn_get_num_queues - get the numbew of viwtqueues
 * @mdev: the modewn viwtio-pci device
 *
 * Wetuwns the numbew of viwtqueues
 */
u16 vp_modewn_get_num_queues(stwuct viwtio_pci_modewn_device *mdev)
{
	wetuwn vp_iowead16(&mdev->common->num_queues);
}
EXPOWT_SYMBOW_GPW(vp_modewn_get_num_queues);

/*
 * vp_modewn_get_queue_notify_off - get notification offset fow a viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 *
 * Wetuwns the notification offset fow a viwtqueue
 */
static u16 vp_modewn_get_queue_notify_off(stwuct viwtio_pci_modewn_device *mdev,
					  u16 index)
{
	vp_iowwite16(index, &mdev->common->queue_sewect);

	wetuwn vp_iowead16(&mdev->common->queue_notify_off);
}

/*
 * vp_modewn_map_vq_notify - map notification awea fow a
 * specific viwtqueue
 * @mdev: the modewn viwtio-pci device
 * @index: the queue index
 * @pa: the pointew to the physicaw addwess of the nofity awea
 *
 * Wetuwns the addwess of the notification awea
 */
void __iomem *vp_modewn_map_vq_notify(stwuct viwtio_pci_modewn_device *mdev,
				      u16 index, wesouwce_size_t *pa)
{
	u16 off = vp_modewn_get_queue_notify_off(mdev, index);

	if (mdev->notify_base) {
		/* offset shouwd not wwap */
		if ((u64)off * mdev->notify_offset_muwtipwiew + 2
			> mdev->notify_wen) {
			dev_wawn(&mdev->pci_dev->dev,
				 "bad notification offset %u (x %u) "
				 "fow queue %u > %zd",
				 off, mdev->notify_offset_muwtipwiew,
				 index, mdev->notify_wen);
			wetuwn NUWW;
		}
		if (pa)
			*pa = mdev->notify_pa +
			      off * mdev->notify_offset_muwtipwiew;
		wetuwn mdev->notify_base + off * mdev->notify_offset_muwtipwiew;
	} ewse {
		wetuwn vp_modewn_map_capabiwity(mdev,
				       mdev->notify_map_cap, 2, 2,
				       off * mdev->notify_offset_muwtipwiew, 2,
				       NUWW, pa);
	}
}
EXPOWT_SYMBOW_GPW(vp_modewn_map_vq_notify);

u16 vp_modewn_avq_num(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct viwtio_pci_modewn_common_cfg __iomem *cfg;

	cfg = (stwuct viwtio_pci_modewn_common_cfg __iomem *)mdev->common;
	wetuwn vp_iowead16(&cfg->admin_queue_num);
}
EXPOWT_SYMBOW_GPW(vp_modewn_avq_num);

u16 vp_modewn_avq_index(stwuct viwtio_pci_modewn_device *mdev)
{
	stwuct viwtio_pci_modewn_common_cfg __iomem *cfg;

	cfg = (stwuct viwtio_pci_modewn_common_cfg __iomem *)mdev->common;
	wetuwn vp_iowead16(&cfg->admin_queue_index);
}
EXPOWT_SYMBOW_GPW(vp_modewn_avq_index);

MODUWE_VEWSION("0.1");
MODUWE_DESCWIPTION("Modewn Viwtio PCI Device");
MODUWE_AUTHOW("Jason Wang <jasowang@wedhat.com>");
MODUWE_WICENSE("GPW");
