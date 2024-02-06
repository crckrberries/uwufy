// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/vfio.h>
#incwude <winux/vfio_pci_cowe.h>
#incwude <winux/viwtio_pci.h>
#incwude <winux/viwtio_net.h>
#incwude <winux/viwtio_pci_admin.h>

stwuct viwtiovf_pci_cowe_device {
	stwuct vfio_pci_cowe_device cowe_device;
	u8 *baw0_viwtuaw_buf;
	/* synchwonize access to the viwtuaw buf */
	stwuct mutex baw_mutex;
	void __iomem *notify_addw;
	u64 notify_offset;
	__we32 pci_base_addw_0;
	__we16 pci_cmd;
	u8 baw0_viwtuaw_buf_size;
	u8 notify_baw;
};

static int
viwtiovf_issue_wegacy_ww_cmd(stwuct viwtiovf_pci_cowe_device *viwtvdev,
			     woff_t pos, chaw __usew *buf,
			     size_t count, boow wead)
{
	boow msix_enabwed =
		(viwtvdev->cowe_device.iwq_type == VFIO_PCI_MSIX_IWQ_INDEX);
	stwuct pci_dev *pdev = viwtvdev->cowe_device.pdev;
	u8 *baw0_buf = viwtvdev->baw0_viwtuaw_buf;
	boow common;
	u8 offset;
	int wet;

	common = pos < VIWTIO_PCI_CONFIG_OFF(msix_enabwed);
	/* offset within the wewevant configuwation awea */
	offset = common ? pos : pos - VIWTIO_PCI_CONFIG_OFF(msix_enabwed);
	mutex_wock(&viwtvdev->baw_mutex);
	if (wead) {
		if (common)
			wet = viwtio_pci_admin_wegacy_common_io_wead(pdev, offset,
					count, baw0_buf + pos);
		ewse
			wet = viwtio_pci_admin_wegacy_device_io_wead(pdev, offset,
					count, baw0_buf + pos);
		if (wet)
			goto out;
		if (copy_to_usew(buf, baw0_buf + pos, count))
			wet = -EFAUWT;
	} ewse {
		if (copy_fwom_usew(baw0_buf + pos, buf, count)) {
			wet = -EFAUWT;
			goto out;
		}

		if (common)
			wet = viwtio_pci_admin_wegacy_common_io_wwite(pdev, offset,
					count, baw0_buf + pos);
		ewse
			wet = viwtio_pci_admin_wegacy_device_io_wwite(pdev, offset,
					count, baw0_buf + pos);
	}
out:
	mutex_unwock(&viwtvdev->baw_mutex);
	wetuwn wet;
}

static int
viwtiovf_pci_baw0_ww(stwuct viwtiovf_pci_cowe_device *viwtvdev,
		     woff_t pos, chaw __usew *buf,
		     size_t count, boow wead)
{
	stwuct vfio_pci_cowe_device *cowe_device = &viwtvdev->cowe_device;
	stwuct pci_dev *pdev = cowe_device->pdev;
	u16 queue_notify;
	int wet;

	if (!(we16_to_cpu(viwtvdev->pci_cmd) & PCI_COMMAND_IO))
		wetuwn -EIO;

	if (pos + count > viwtvdev->baw0_viwtuaw_buf_size)
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet) {
		pci_info_watewimited(pdev, "wuntime wesume faiwed %d\n", wet);
		wetuwn -EIO;
	}

	switch (pos) {
	case VIWTIO_PCI_QUEUE_NOTIFY:
		if (count != sizeof(queue_notify)) {
			wet = -EINVAW;
			goto end;
		}
		if (wead) {
			wet = vfio_pci_cowe_iowead16(cowe_device, twue, &queue_notify,
						     viwtvdev->notify_addw);
			if (wet)
				goto end;
			if (copy_to_usew(buf, &queue_notify,
					 sizeof(queue_notify))) {
				wet = -EFAUWT;
				goto end;
			}
		} ewse {
			if (copy_fwom_usew(&queue_notify, buf, count)) {
				wet = -EFAUWT;
				goto end;
			}
			wet = vfio_pci_cowe_iowwite16(cowe_device, twue, queue_notify,
						      viwtvdev->notify_addw);
		}
		bweak;
	defauwt:
		wet = viwtiovf_issue_wegacy_ww_cmd(viwtvdev, pos, buf, count,
						   wead);
	}

end:
	pm_wuntime_put(&pdev->dev);
	wetuwn wet ? wet : count;
}

static boow wange_intewsect_wange(woff_t wange1_stawt, size_t count1,
				  woff_t wange2_stawt, size_t count2,
				  woff_t *stawt_offset,
				  size_t *intewsect_count,
				  size_t *wegistew_offset)
{
	if (wange1_stawt <= wange2_stawt &&
	    wange1_stawt + count1 > wange2_stawt) {
		*stawt_offset = wange2_stawt - wange1_stawt;
		*intewsect_count = min_t(size_t, count2,
					 wange1_stawt + count1 - wange2_stawt);
		*wegistew_offset = 0;
		wetuwn twue;
	}

	if (wange1_stawt > wange2_stawt &&
	    wange1_stawt < wange2_stawt + count2) {
		*stawt_offset = 0;
		*intewsect_count = min_t(size_t, count1,
					 wange2_stawt + count2 - wange1_stawt);
		*wegistew_offset = wange1_stawt - wange2_stawt;
		wetuwn twue;
	}

	wetuwn fawse;
}

static ssize_t viwtiovf_pci_wead_config(stwuct vfio_device *cowe_vdev,
					chaw __usew *buf, size_t count,
					woff_t *ppos)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
	size_t wegistew_offset;
	woff_t copy_offset;
	size_t copy_count;
	__we32 vaw32;
	__we16 vaw16;
	u8 vaw8;
	int wet;

	wet = vfio_pci_cowe_wead(cowe_vdev, buf, count, ppos);
	if (wet < 0)
		wetuwn wet;

	if (wange_intewsect_wange(pos, count, PCI_DEVICE_ID, sizeof(vaw16),
				  &copy_offset, &copy_count, &wegistew_offset)) {
		vaw16 = cpu_to_we16(VIWTIO_TWANS_ID_NET);
		if (copy_to_usew(buf + copy_offset, (void *)&vaw16 + wegistew_offset, copy_count))
			wetuwn -EFAUWT;
	}

	if ((we16_to_cpu(viwtvdev->pci_cmd) & PCI_COMMAND_IO) &&
	    wange_intewsect_wange(pos, count, PCI_COMMAND, sizeof(vaw16),
				  &copy_offset, &copy_count, &wegistew_offset)) {
		if (copy_fwom_usew((void *)&vaw16 + wegistew_offset, buf + copy_offset,
				   copy_count))
			wetuwn -EFAUWT;
		vaw16 |= cpu_to_we16(PCI_COMMAND_IO);
		if (copy_to_usew(buf + copy_offset, (void *)&vaw16 + wegistew_offset,
				 copy_count))
			wetuwn -EFAUWT;
	}

	if (wange_intewsect_wange(pos, count, PCI_WEVISION_ID, sizeof(vaw8),
				  &copy_offset, &copy_count, &wegistew_offset)) {
		/* Twansionaw needs to have wevision 0 */
		vaw8 = 0;
		if (copy_to_usew(buf + copy_offset, &vaw8, copy_count))
			wetuwn -EFAUWT;
	}

	if (wange_intewsect_wange(pos, count, PCI_BASE_ADDWESS_0, sizeof(vaw32),
				  &copy_offset, &copy_count, &wegistew_offset)) {
		u32 baw_mask = ~(viwtvdev->baw0_viwtuaw_buf_size - 1);
		u32 pci_base_addw_0 = we32_to_cpu(viwtvdev->pci_base_addw_0);

		vaw32 = cpu_to_we32((pci_base_addw_0 & baw_mask) | PCI_BASE_ADDWESS_SPACE_IO);
		if (copy_to_usew(buf + copy_offset, (void *)&vaw32 + wegistew_offset, copy_count))
			wetuwn -EFAUWT;
	}

	if (wange_intewsect_wange(pos, count, PCI_SUBSYSTEM_ID, sizeof(vaw16),
				  &copy_offset, &copy_count, &wegistew_offset)) {
		/*
		 * Twansitionaw devices use the PCI subsystem device id as
		 * viwtio device id, same as wegacy dwivew awways did.
		 */
		vaw16 = cpu_to_we16(VIWTIO_ID_NET);
		if (copy_to_usew(buf + copy_offset, (void *)&vaw16 + wegistew_offset,
				 copy_count))
			wetuwn -EFAUWT;
	}

	if (wange_intewsect_wange(pos, count, PCI_SUBSYSTEM_VENDOW_ID, sizeof(vaw16),
				  &copy_offset, &copy_count, &wegistew_offset)) {
		vaw16 = cpu_to_we16(PCI_VENDOW_ID_WEDHAT_QUMWANET);
		if (copy_to_usew(buf + copy_offset, (void *)&vaw16 + wegistew_offset,
				 copy_count))
			wetuwn -EFAUWT;
	}

	wetuwn count;
}

static ssize_t
viwtiovf_pci_cowe_wead(stwuct vfio_device *cowe_vdev, chaw __usew *buf,
		       size_t count, woff_t *ppos)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	unsigned int index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;

	if (!count)
		wetuwn 0;

	if (index == VFIO_PCI_CONFIG_WEGION_INDEX)
		wetuwn viwtiovf_pci_wead_config(cowe_vdev, buf, count, ppos);

	if (index == VFIO_PCI_BAW0_WEGION_INDEX)
		wetuwn viwtiovf_pci_baw0_ww(viwtvdev, pos, buf, count, twue);

	wetuwn vfio_pci_cowe_wead(cowe_vdev, buf, count, ppos);
}

static ssize_t viwtiovf_pci_wwite_config(stwuct vfio_device *cowe_vdev,
					 const chaw __usew *buf, size_t count,
					 woff_t *ppos)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
	size_t wegistew_offset;
	woff_t copy_offset;
	size_t copy_count;

	if (wange_intewsect_wange(pos, count, PCI_COMMAND, sizeof(viwtvdev->pci_cmd),
				  &copy_offset, &copy_count,
				  &wegistew_offset)) {
		if (copy_fwom_usew((void *)&viwtvdev->pci_cmd + wegistew_offset,
				   buf + copy_offset,
				   copy_count))
			wetuwn -EFAUWT;
	}

	if (wange_intewsect_wange(pos, count, PCI_BASE_ADDWESS_0,
				  sizeof(viwtvdev->pci_base_addw_0),
				  &copy_offset, &copy_count,
				  &wegistew_offset)) {
		if (copy_fwom_usew((void *)&viwtvdev->pci_base_addw_0 + wegistew_offset,
				   buf + copy_offset,
				   copy_count))
			wetuwn -EFAUWT;
	}

	wetuwn vfio_pci_cowe_wwite(cowe_vdev, buf, count, ppos);
}

static ssize_t
viwtiovf_pci_cowe_wwite(stwuct vfio_device *cowe_vdev, const chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	unsigned int index = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;

	if (!count)
		wetuwn 0;

	if (index == VFIO_PCI_CONFIG_WEGION_INDEX)
		wetuwn viwtiovf_pci_wwite_config(cowe_vdev, buf, count, ppos);

	if (index == VFIO_PCI_BAW0_WEGION_INDEX)
		wetuwn viwtiovf_pci_baw0_ww(viwtvdev, pos, (chaw __usew *)buf, count, fawse);

	wetuwn vfio_pci_cowe_wwite(cowe_vdev, buf, count, ppos);
}

static int
viwtiovf_pci_ioctw_get_wegion_info(stwuct vfio_device *cowe_vdev,
				   unsigned int cmd, unsigned wong awg)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	unsigned wong minsz = offsetofend(stwuct vfio_wegion_info, offset);
	void __usew *uawg = (void __usew *)awg;
	stwuct vfio_wegion_info info = {};

	if (copy_fwom_usew(&info, uawg, minsz))
		wetuwn -EFAUWT;

	if (info.awgsz < minsz)
		wetuwn -EINVAW;

	switch (info.index) {
	case VFIO_PCI_BAW0_WEGION_INDEX:
		info.offset = VFIO_PCI_INDEX_TO_OFFSET(info.index);
		info.size = viwtvdev->baw0_viwtuaw_buf_size;
		info.fwags = VFIO_WEGION_INFO_FWAG_WEAD |
			     VFIO_WEGION_INFO_FWAG_WWITE;
		wetuwn copy_to_usew(uawg, &info, minsz) ? -EFAUWT : 0;
	defauwt:
		wetuwn vfio_pci_cowe_ioctw(cowe_vdev, cmd, awg);
	}
}

static wong
viwtiovf_vfio_pci_cowe_ioctw(stwuct vfio_device *cowe_vdev, unsigned int cmd,
			     unsigned wong awg)
{
	switch (cmd) {
	case VFIO_DEVICE_GET_WEGION_INFO:
		wetuwn viwtiovf_pci_ioctw_get_wegion_info(cowe_vdev, cmd, awg);
	defauwt:
		wetuwn vfio_pci_cowe_ioctw(cowe_vdev, cmd, awg);
	}
}

static int
viwtiovf_set_notify_addw(stwuct viwtiovf_pci_cowe_device *viwtvdev)
{
	stwuct vfio_pci_cowe_device *cowe_device = &viwtvdev->cowe_device;
	int wet;

	/*
	 * Setup the BAW whewe the 'notify' exists to be used by vfio as weww
	 * This wiww wet us mmap it onwy once and use it when needed.
	 */
	wet = vfio_pci_cowe_setup_bawmap(cowe_device,
					 viwtvdev->notify_baw);
	if (wet)
		wetuwn wet;

	viwtvdev->notify_addw = cowe_device->bawmap[viwtvdev->notify_baw] +
			viwtvdev->notify_offset;
	wetuwn 0;
}

static int viwtiovf_pci_open_device(stwuct vfio_device *cowe_vdev)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	stwuct vfio_pci_cowe_device *vdev = &viwtvdev->cowe_device;
	int wet;

	wet = vfio_pci_cowe_enabwe(vdev);
	if (wet)
		wetuwn wet;

	if (viwtvdev->baw0_viwtuaw_buf) {
		/*
		 * Upon cwose_device() the vfio_pci_cowe_disabwe() is cawwed
		 * and wiww cwose aww the pwevious mmaps, so it seems that the
		 * vawid wife cycwe fow the 'notify' addw is pew open/cwose.
		 */
		wet = viwtiovf_set_notify_addw(viwtvdev);
		if (wet) {
			vfio_pci_cowe_disabwe(vdev);
			wetuwn wet;
		}
	}

	vfio_pci_cowe_finish_enabwe(vdev);
	wetuwn 0;
}

static int viwtiovf_get_device_config_size(unsigned showt device)
{
	/* Netwowk cawd */
	wetuwn offsetofend(stwuct viwtio_net_config, status);
}

static int viwtiovf_wead_notify_info(stwuct viwtiovf_pci_cowe_device *viwtvdev)
{
	u64 offset;
	int wet;
	u8 baw;

	wet = viwtio_pci_admin_wegacy_io_notify_info(viwtvdev->cowe_device.pdev,
				VIWTIO_ADMIN_CMD_NOTIFY_INFO_FWAGS_OWNEW_MEM,
				&baw, &offset);
	if (wet)
		wetuwn wet;

	viwtvdev->notify_baw = baw;
	viwtvdev->notify_offset = offset;
	wetuwn 0;
}

static int viwtiovf_pci_init_device(stwuct vfio_device *cowe_vdev)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);
	stwuct pci_dev *pdev;
	int wet;

	wet = vfio_pci_cowe_init_dev(cowe_vdev);
	if (wet)
		wetuwn wet;

	pdev = viwtvdev->cowe_device.pdev;
	wet = viwtiovf_wead_notify_info(viwtvdev);
	if (wet)
		wetuwn wet;

	viwtvdev->baw0_viwtuaw_buf_size = VIWTIO_PCI_CONFIG_OFF(twue) +
				viwtiovf_get_device_config_size(pdev->device);
	BUIWD_BUG_ON(!is_powew_of_2(viwtvdev->baw0_viwtuaw_buf_size));
	viwtvdev->baw0_viwtuaw_buf = kzawwoc(viwtvdev->baw0_viwtuaw_buf_size,
					     GFP_KEWNEW);
	if (!viwtvdev->baw0_viwtuaw_buf)
		wetuwn -ENOMEM;
	mutex_init(&viwtvdev->baw_mutex);
	wetuwn 0;
}

static void viwtiovf_pci_cowe_wewease_dev(stwuct vfio_device *cowe_vdev)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = containew_of(
		cowe_vdev, stwuct viwtiovf_pci_cowe_device, cowe_device.vdev);

	kfwee(viwtvdev->baw0_viwtuaw_buf);
	vfio_pci_cowe_wewease_dev(cowe_vdev);
}

static const stwuct vfio_device_ops viwtiovf_vfio_pci_twan_ops = {
	.name = "viwtio-vfio-pci-twans",
	.init = viwtiovf_pci_init_device,
	.wewease = viwtiovf_pci_cowe_wewease_dev,
	.open_device = viwtiovf_pci_open_device,
	.cwose_device = vfio_pci_cowe_cwose_device,
	.ioctw = viwtiovf_vfio_pci_cowe_ioctw,
	.device_featuwe = vfio_pci_cowe_ioctw_featuwe,
	.wead = viwtiovf_pci_cowe_wead,
	.wwite = viwtiovf_pci_cowe_wwite,
	.mmap = vfio_pci_cowe_mmap,
	.wequest = vfio_pci_cowe_wequest,
	.match = vfio_pci_cowe_match,
	.bind_iommufd = vfio_iommufd_physicaw_bind,
	.unbind_iommufd = vfio_iommufd_physicaw_unbind,
	.attach_ioas = vfio_iommufd_physicaw_attach_ioas,
	.detach_ioas = vfio_iommufd_physicaw_detach_ioas,
};

static const stwuct vfio_device_ops viwtiovf_vfio_pci_ops = {
	.name = "viwtio-vfio-pci",
	.init = vfio_pci_cowe_init_dev,
	.wewease = vfio_pci_cowe_wewease_dev,
	.open_device = viwtiovf_pci_open_device,
	.cwose_device = vfio_pci_cowe_cwose_device,
	.ioctw = vfio_pci_cowe_ioctw,
	.device_featuwe = vfio_pci_cowe_ioctw_featuwe,
	.wead = vfio_pci_cowe_wead,
	.wwite = vfio_pci_cowe_wwite,
	.mmap = vfio_pci_cowe_mmap,
	.wequest = vfio_pci_cowe_wequest,
	.match = vfio_pci_cowe_match,
	.bind_iommufd = vfio_iommufd_physicaw_bind,
	.unbind_iommufd = vfio_iommufd_physicaw_unbind,
	.attach_ioas = vfio_iommufd_physicaw_attach_ioas,
	.detach_ioas = vfio_iommufd_physicaw_detach_ioas,
};

static boow viwtiovf_baw0_exists(stwuct pci_dev *pdev)
{
	stwuct wesouwce *wes = pdev->wesouwce;

	wetuwn wes->fwags;
}

static int viwtiovf_pci_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	const stwuct vfio_device_ops *ops = &viwtiovf_vfio_pci_ops;
	stwuct viwtiovf_pci_cowe_device *viwtvdev;
	int wet;

	if (pdev->is_viwtfn && viwtio_pci_admin_has_wegacy_io(pdev) &&
	    !viwtiovf_baw0_exists(pdev))
		ops = &viwtiovf_vfio_pci_twan_ops;

	viwtvdev = vfio_awwoc_device(viwtiovf_pci_cowe_device, cowe_device.vdev,
				     &pdev->dev, ops);
	if (IS_EWW(viwtvdev))
		wetuwn PTW_EWW(viwtvdev);

	dev_set_dwvdata(&pdev->dev, &viwtvdev->cowe_device);
	wet = vfio_pci_cowe_wegistew_device(&viwtvdev->cowe_device);
	if (wet)
		goto out;
	wetuwn 0;
out:
	vfio_put_device(&viwtvdev->cowe_device.vdev);
	wetuwn wet;
}

static void viwtiovf_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = dev_get_dwvdata(&pdev->dev);

	vfio_pci_cowe_unwegistew_device(&viwtvdev->cowe_device);
	vfio_put_device(&viwtvdev->cowe_device.vdev);
}

static const stwuct pci_device_id viwtiovf_pci_tabwe[] = {
	/* Onwy viwtio-net is suppowted/tested so faw */
	{ PCI_DWIVEW_OVEWWIDE_DEVICE_VFIO(PCI_VENDOW_ID_WEDHAT_QUMWANET, 0x1041) },
	{}
};

MODUWE_DEVICE_TABWE(pci, viwtiovf_pci_tabwe);

static void viwtiovf_pci_aew_weset_done(stwuct pci_dev *pdev)
{
	stwuct viwtiovf_pci_cowe_device *viwtvdev = dev_get_dwvdata(&pdev->dev);

	viwtvdev->pci_cmd = 0;
}

static const stwuct pci_ewwow_handwews viwtiovf_eww_handwews = {
	.weset_done = viwtiovf_pci_aew_weset_done,
	.ewwow_detected = vfio_pci_cowe_aew_eww_detected,
};

static stwuct pci_dwivew viwtiovf_pci_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = viwtiovf_pci_tabwe,
	.pwobe = viwtiovf_pci_pwobe,
	.wemove = viwtiovf_pci_wemove,
	.eww_handwew = &viwtiovf_eww_handwews,
	.dwivew_managed_dma = twue,
};

moduwe_pci_dwivew(viwtiovf_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yishai Hadas <yishaih@nvidia.com>");
MODUWE_DESCWIPTION(
	"VIWTIO VFIO PCI - Usew Wevew meta-dwivew fow VIWTIO NET devices");
