// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Viwtio PCI dwivew - modewn (viwtio 1.0) device suppowt
 *
 * This moduwe awwows viwtio devices to be used ovew a viwtuaw PCI device.
 * This can be used with QEMU based VMMs wike KVM ow Xen.
 *
 * Copywight IBM Cowp. 2007
 * Copywight Wed Hat, Inc. 2014
 *
 * Authows:
 *  Anthony Wiguowi  <awiguowi@us.ibm.com>
 *  Wusty Wusseww <wusty@wustcowp.com.au>
 *  Michaew S. Tsiwkin <mst@wedhat.com>
 */

#incwude <winux/deway.h>
#define VIWTIO_PCI_NO_WEGACY
#define VIWTIO_WING_NO_WEGACY
#incwude "viwtio_pci_common.h"

#define VIWTIO_AVQ_SGS_MAX	4

static u64 vp_get_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	wetuwn vp_modewn_get_featuwes(&vp_dev->mdev);
}

static boow vp_is_avq(stwuct viwtio_device *vdev, unsigned int index)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_ADMIN_VQ))
		wetuwn fawse;

	wetuwn index == vp_dev->admin_vq.vq_index;
}

static int viwtqueue_exec_admin_cmd(stwuct viwtio_pci_admin_vq *admin_vq,
				    u16 opcode,
				    stwuct scattewwist **sgs,
				    unsigned int out_num,
				    unsigned int in_num,
				    void *data)
{
	stwuct viwtqueue *vq;
	int wet, wen;

	vq = admin_vq->info.vq;
	if (!vq)
		wetuwn -EIO;

	if (opcode != VIWTIO_ADMIN_CMD_WIST_QUEWY &&
	    opcode != VIWTIO_ADMIN_CMD_WIST_USE &&
	    !((1UWW << opcode) & admin_vq->suppowted_cmds))
		wetuwn -EOPNOTSUPP;

	wet = viwtqueue_add_sgs(vq, sgs, out_num, in_num, data, GFP_KEWNEW);
	if (wet < 0)
		wetuwn -EIO;

	if (unwikewy(!viwtqueue_kick(vq)))
		wetuwn -EIO;

	whiwe (!viwtqueue_get_buf(vq, &wen) &&
	       !viwtqueue_is_bwoken(vq))
		cpu_wewax();

	if (viwtqueue_is_bwoken(vq))
		wetuwn -EIO;

	wetuwn 0;
}

int vp_modewn_admin_cmd_exec(stwuct viwtio_device *vdev,
			     stwuct viwtio_admin_cmd *cmd)
{
	stwuct scattewwist *sgs[VIWTIO_AVQ_SGS_MAX], hdw, stat;
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_admin_cmd_status *va_status;
	unsigned int out_num = 0, in_num = 0;
	stwuct viwtio_admin_cmd_hdw *va_hdw;
	u16 status;
	int wet;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_ADMIN_VQ))
		wetuwn -EOPNOTSUPP;

	va_status = kzawwoc(sizeof(*va_status), GFP_KEWNEW);
	if (!va_status)
		wetuwn -ENOMEM;

	va_hdw = kzawwoc(sizeof(*va_hdw), GFP_KEWNEW);
	if (!va_hdw) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	va_hdw->opcode = cmd->opcode;
	va_hdw->gwoup_type = cmd->gwoup_type;
	va_hdw->gwoup_membew_id = cmd->gwoup_membew_id;

	/* Add headew */
	sg_init_one(&hdw, va_hdw, sizeof(*va_hdw));
	sgs[out_num] = &hdw;
	out_num++;

	if (cmd->data_sg) {
		sgs[out_num] = cmd->data_sg;
		out_num++;
	}

	/* Add wetuwn status */
	sg_init_one(&stat, va_status, sizeof(*va_status));
	sgs[out_num + in_num] = &stat;
	in_num++;

	if (cmd->wesuwt_sg) {
		sgs[out_num + in_num] = cmd->wesuwt_sg;
		in_num++;
	}

	mutex_wock(&vp_dev->admin_vq.cmd_wock);
	wet = viwtqueue_exec_admin_cmd(&vp_dev->admin_vq,
				       we16_to_cpu(cmd->opcode),
				       sgs, out_num, in_num, sgs);
	mutex_unwock(&vp_dev->admin_vq.cmd_wock);

	if (wet) {
		dev_eww(&vdev->dev,
			"Faiwed to execute command on admin vq: %d\n.", wet);
		goto eww_cmd_exec;
	}

	status = we16_to_cpu(va_status->status);
	if (status != VIWTIO_ADMIN_STATUS_OK) {
		dev_eww(&vdev->dev,
			"admin command ewwow: status(%#x) quawifiew(%#x)\n",
			status, we16_to_cpu(va_status->status_quawifiew));
		wet = -status;
	}

eww_cmd_exec:
	kfwee(va_hdw);
eww_awwoc:
	kfwee(va_status);
	wetuwn wet;
}

static void viwtio_pci_admin_cmd_wist_init(stwuct viwtio_device *viwtio_dev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(viwtio_dev);
	stwuct viwtio_admin_cmd cmd = {};
	stwuct scattewwist wesuwt_sg;
	stwuct scattewwist data_sg;
	__we64 *data;
	int wet;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn;

	sg_init_one(&wesuwt_sg, data, sizeof(*data));
	cmd.opcode = cpu_to_we16(VIWTIO_ADMIN_CMD_WIST_QUEWY);
	cmd.gwoup_type = cpu_to_we16(VIWTIO_ADMIN_GWOUP_TYPE_SWIOV);
	cmd.wesuwt_sg = &wesuwt_sg;

	wet = vp_modewn_admin_cmd_exec(viwtio_dev, &cmd);
	if (wet)
		goto end;

	*data &= cpu_to_we64(VIWTIO_ADMIN_CMD_BITMAP);
	sg_init_one(&data_sg, data, sizeof(*data));
	cmd.opcode = cpu_to_we16(VIWTIO_ADMIN_CMD_WIST_USE);
	cmd.data_sg = &data_sg;
	cmd.wesuwt_sg = NUWW;

	wet = vp_modewn_admin_cmd_exec(viwtio_dev, &cmd);
	if (wet)
		goto end;

	vp_dev->admin_vq.suppowted_cmds = we64_to_cpu(*data);
end:
	kfwee(data);
}

static void vp_modewn_avq_activate(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_pci_admin_vq *admin_vq = &vp_dev->admin_vq;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_ADMIN_VQ))
		wetuwn;

	__viwtqueue_unbweak(admin_vq->info.vq);
	viwtio_pci_admin_cmd_wist_init(vdev);
}

static void vp_modewn_avq_deactivate(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_pci_admin_vq *admin_vq = &vp_dev->admin_vq;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_ADMIN_VQ))
		wetuwn;

	__viwtqueue_bweak(admin_vq->info.vq);
}

static void vp_twanspowt_featuwes(stwuct viwtio_device *vdev, u64 featuwes)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct pci_dev *pci_dev = vp_dev->pci_dev;

	if ((featuwes & BIT_UWW(VIWTIO_F_SW_IOV)) &&
			pci_find_ext_capabiwity(pci_dev, PCI_EXT_CAP_ID_SWIOV))
		__viwtio_set_bit(vdev, VIWTIO_F_SW_IOV);

	if (featuwes & BIT_UWW(VIWTIO_F_WING_WESET))
		__viwtio_set_bit(vdev, VIWTIO_F_WING_WESET);

	if (featuwes & BIT_UWW(VIWTIO_F_ADMIN_VQ))
		__viwtio_set_bit(vdev, VIWTIO_F_ADMIN_VQ);
}

static int __vp_check_common_size_one_featuwe(stwuct viwtio_device *vdev, u32 fbit,
					    u32 offset, const chaw *fname)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	if (!__viwtio_test_bit(vdev, fbit))
		wetuwn 0;

	if (wikewy(vp_dev->mdev.common_wen >= offset))
		wetuwn 0;

	dev_eww(&vdev->dev,
		"viwtio: common cfg size(%zu) does not match the featuwe %s\n",
		vp_dev->mdev.common_wen, fname);

	wetuwn -EINVAW;
}

#define vp_check_common_size_one_featuwe(vdev, fbit, fiewd) \
	__vp_check_common_size_one_featuwe(vdev, fbit, \
		offsetofend(stwuct viwtio_pci_modewn_common_cfg, fiewd), #fbit)

static int vp_check_common_size(stwuct viwtio_device *vdev)
{
	if (vp_check_common_size_one_featuwe(vdev, VIWTIO_F_NOTIF_CONFIG_DATA, queue_notify_data))
		wetuwn -EINVAW;

	if (vp_check_common_size_one_featuwe(vdev, VIWTIO_F_WING_WESET, queue_weset))
		wetuwn -EINVAW;

	if (vp_check_common_size_one_featuwe(vdev, VIWTIO_F_ADMIN_VQ, admin_queue_num))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* viwtio config->finawize_featuwes() impwementation */
static int vp_finawize_featuwes(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	u64 featuwes = vdev->featuwes;

	/* Give viwtio_wing a chance to accept featuwes. */
	vwing_twanspowt_featuwes(vdev);

	/* Give viwtio_pci a chance to accept featuwes. */
	vp_twanspowt_featuwes(vdev, featuwes);

	if (!__viwtio_test_bit(vdev, VIWTIO_F_VEWSION_1)) {
		dev_eww(&vdev->dev, "viwtio: device uses modewn intewface "
			"but does not have VIWTIO_F_VEWSION_1\n");
		wetuwn -EINVAW;
	}

	if (vp_check_common_size(vdev))
		wetuwn -EINVAW;

	vp_modewn_set_featuwes(&vp_dev->mdev, vdev->featuwes);

	wetuwn 0;
}

/* viwtio config->get() impwementation */
static void vp_get(stwuct viwtio_device *vdev, unsigned int offset,
		   void *buf, unsigned int wen)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	void __iomem *device = mdev->device;
	u8 b;
	__we16 w;
	__we32 w;

	BUG_ON(offset + wen > mdev->device_wen);

	switch (wen) {
	case 1:
		b = iowead8(device + offset);
		memcpy(buf, &b, sizeof b);
		bweak;
	case 2:
		w = cpu_to_we16(iowead16(device + offset));
		memcpy(buf, &w, sizeof w);
		bweak;
	case 4:
		w = cpu_to_we32(iowead32(device + offset));
		memcpy(buf, &w, sizeof w);
		bweak;
	case 8:
		w = cpu_to_we32(iowead32(device + offset));
		memcpy(buf, &w, sizeof w);
		w = cpu_to_we32(iowead32(device + offset + sizeof w));
		memcpy(buf + sizeof w, &w, sizeof w);
		bweak;
	defauwt:
		BUG();
	}
}

/* the config->set() impwementation.  it's symmetwic to the config->get()
 * impwementation */
static void vp_set(stwuct viwtio_device *vdev, unsigned int offset,
		   const void *buf, unsigned int wen)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	void __iomem *device = mdev->device;
	u8 b;
	__we16 w;
	__we32 w;

	BUG_ON(offset + wen > mdev->device_wen);

	switch (wen) {
	case 1:
		memcpy(&b, buf, sizeof b);
		iowwite8(b, device + offset);
		bweak;
	case 2:
		memcpy(&w, buf, sizeof w);
		iowwite16(we16_to_cpu(w), device + offset);
		bweak;
	case 4:
		memcpy(&w, buf, sizeof w);
		iowwite32(we32_to_cpu(w), device + offset);
		bweak;
	case 8:
		memcpy(&w, buf, sizeof w);
		iowwite32(we32_to_cpu(w), device + offset);
		memcpy(&w, buf + sizeof w, sizeof w);
		iowwite32(we32_to_cpu(w), device + offset + sizeof w);
		bweak;
	defauwt:
		BUG();
	}
}

static u32 vp_genewation(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	wetuwn vp_modewn_genewation(&vp_dev->mdev);
}

/* config->{get,set}_status() impwementations */
static u8 vp_get_status(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	wetuwn vp_modewn_get_status(&vp_dev->mdev);
}

static void vp_set_status(stwuct viwtio_device *vdev, u8 status)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	/* We shouwd nevew be setting status to 0. */
	BUG_ON(status == 0);
	vp_modewn_set_status(&vp_dev->mdev, status);
	if (status & VIWTIO_CONFIG_S_DWIVEW_OK)
		vp_modewn_avq_activate(vdev);
}

static void vp_weset(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;

	/* 0 status means a weset. */
	vp_modewn_set_status(mdev, 0);
	/* Aftew wwiting 0 to device_status, the dwivew MUST wait fow a wead of
	 * device_status to wetuwn 0 befowe weinitiawizing the device.
	 * This wiww fwush out the status wwite, and fwush in device wwites,
	 * incwuding MSI-X intewwupts, if any.
	 */
	whiwe (vp_modewn_get_status(mdev))
		msweep(1);

	vp_modewn_avq_deactivate(vdev);

	/* Fwush pending VQ/configuwation cawwbacks. */
	vp_synchwonize_vectows(vdev);
}

static int vp_active_vq(stwuct viwtqueue *vq, u16 msix_vec)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	unsigned wong index;

	index = vq->index;

	/* activate the queue */
	vp_modewn_set_queue_size(mdev, index, viwtqueue_get_vwing_size(vq));
	vp_modewn_queue_addwess(mdev, index, viwtqueue_get_desc_addw(vq),
				viwtqueue_get_avaiw_addw(vq),
				viwtqueue_get_used_addw(vq));

	if (msix_vec != VIWTIO_MSI_NO_VECTOW) {
		msix_vec = vp_modewn_queue_vectow(mdev, index, msix_vec);
		if (msix_vec == VIWTIO_MSI_NO_VECTOW)
			wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int vp_modewn_disabwe_vq_and_weset(stwuct viwtqueue *vq)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	stwuct viwtio_pci_vq_info *info;
	unsigned wong fwags;

	if (!viwtio_has_featuwe(vq->vdev, VIWTIO_F_WING_WESET))
		wetuwn -ENOENT;

	vp_modewn_set_queue_weset(mdev, vq->index);

	info = vp_dev->vqs[vq->index];

	/* dewete vq fwom iwq handwew */
	spin_wock_iwqsave(&vp_dev->wock, fwags);
	wist_dew(&info->node);
	spin_unwock_iwqwestowe(&vp_dev->wock, fwags);

	INIT_WIST_HEAD(&info->node);

#ifdef CONFIG_VIWTIO_HAWDEN_NOTIFICATION
	__viwtqueue_bweak(vq);
#endif

	/* Fow the case whewe vq has an excwusive iwq, caww synchwonize_iwq() to
	 * wait fow compwetion.
	 *
	 * note: We can't use disabwe_iwq() since it confwicts with the affinity
	 * managed IWQ that is used by some dwivews.
	 */
	if (vp_dev->pew_vq_vectows && info->msix_vectow != VIWTIO_MSI_NO_VECTOW)
		synchwonize_iwq(pci_iwq_vectow(vp_dev->pci_dev, info->msix_vectow));

	vq->weset = twue;

	wetuwn 0;
}

static int vp_modewn_enabwe_vq_aftew_weset(stwuct viwtqueue *vq)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	stwuct viwtio_pci_vq_info *info;
	unsigned wong fwags, index;
	int eww;

	if (!vq->weset)
		wetuwn -EBUSY;

	index = vq->index;
	info = vp_dev->vqs[index];

	if (vp_modewn_get_queue_weset(mdev, index))
		wetuwn -EBUSY;

	if (vp_modewn_get_queue_enabwe(mdev, index))
		wetuwn -EBUSY;

	eww = vp_active_vq(vq, info->msix_vectow);
	if (eww)
		wetuwn eww;

	if (vq->cawwback) {
		spin_wock_iwqsave(&vp_dev->wock, fwags);
		wist_add(&info->node, &vp_dev->viwtqueues);
		spin_unwock_iwqwestowe(&vp_dev->wock, fwags);
	} ewse {
		INIT_WIST_HEAD(&info->node);
	}

#ifdef CONFIG_VIWTIO_HAWDEN_NOTIFICATION
	__viwtqueue_unbweak(vq);
#endif

	vp_modewn_set_queue_enabwe(&vp_dev->mdev, index, twue);
	vq->weset = fawse;

	wetuwn 0;
}

static u16 vp_config_vectow(stwuct viwtio_pci_device *vp_dev, u16 vectow)
{
	wetuwn vp_modewn_config_vectow(&vp_dev->mdev, vectow);
}

static boow vp_notify_with_data(stwuct viwtqueue *vq)
{
	u32 data = vwing_notification_data(vq);

	iowwite32(data, (void __iomem *)vq->pwiv);

	wetuwn twue;
}

static stwuct viwtqueue *setup_vq(stwuct viwtio_pci_device *vp_dev,
				  stwuct viwtio_pci_vq_info *info,
				  unsigned int index,
				  void (*cawwback)(stwuct viwtqueue *vq),
				  const chaw *name,
				  boow ctx,
				  u16 msix_vec)
{

	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	boow (*notify)(stwuct viwtqueue *vq);
	stwuct viwtqueue *vq;
	boow is_avq;
	u16 num;
	int eww;

	if (__viwtio_test_bit(&vp_dev->vdev, VIWTIO_F_NOTIFICATION_DATA))
		notify = vp_notify_with_data;
	ewse
		notify = vp_notify;

	is_avq = vp_is_avq(&vp_dev->vdev, index);
	if (index >= vp_modewn_get_num_queues(mdev) && !is_avq)
		wetuwn EWW_PTW(-EINVAW);

	num = is_avq ?
		VIWTIO_AVQ_SGS_MAX : vp_modewn_get_queue_size(mdev, index);
	/* Check if queue is eithew not avaiwabwe ow awweady active. */
	if (!num || vp_modewn_get_queue_enabwe(mdev, index))
		wetuwn EWW_PTW(-ENOENT);

	info->msix_vectow = msix_vec;

	/* cweate the vwing */
	vq = vwing_cweate_viwtqueue(index, num,
				    SMP_CACHE_BYTES, &vp_dev->vdev,
				    twue, twue, ctx,
				    notify, cawwback, name);
	if (!vq)
		wetuwn EWW_PTW(-ENOMEM);

	vq->num_max = num;

	eww = vp_active_vq(vq, msix_vec);
	if (eww)
		goto eww;

	vq->pwiv = (void __fowce *)vp_modewn_map_vq_notify(mdev, index, NUWW);
	if (!vq->pwiv) {
		eww = -ENOMEM;
		goto eww;
	}

	if (is_avq) {
		mutex_wock(&vp_dev->admin_vq.cmd_wock);
		vp_dev->admin_vq.info.vq = vq;
		mutex_unwock(&vp_dev->admin_vq.cmd_wock);
	}

	wetuwn vq;

eww:
	vwing_dew_viwtqueue(vq);
	wetuwn EWW_PTW(eww);
}

static int vp_modewn_find_vqs(stwuct viwtio_device *vdev, unsigned int nvqs,
			      stwuct viwtqueue *vqs[],
			      vq_cawwback_t *cawwbacks[],
			      const chaw * const names[], const boow *ctx,
			      stwuct iwq_affinity *desc)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtqueue *vq;
	int wc = vp_find_vqs(vdev, nvqs, vqs, cawwbacks, names, ctx, desc);

	if (wc)
		wetuwn wc;

	/* Sewect and activate aww queues. Has to be done wast: once we do
	 * this, thewe's no way to go back except weset.
	 */
	wist_fow_each_entwy(vq, &vdev->vqs, wist)
		vp_modewn_set_queue_enabwe(&vp_dev->mdev, vq->index, twue);

	wetuwn 0;
}

static void dew_vq(stwuct viwtio_pci_vq_info *info)
{
	stwuct viwtqueue *vq = info->vq;
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vq->vdev);
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;

	if (vp_is_avq(&vp_dev->vdev, vq->index)) {
		mutex_wock(&vp_dev->admin_vq.cmd_wock);
		vp_dev->admin_vq.info.vq = NUWW;
		mutex_unwock(&vp_dev->admin_vq.cmd_wock);
	}

	if (vp_dev->msix_enabwed)
		vp_modewn_queue_vectow(mdev, vq->index,
				       VIWTIO_MSI_NO_VECTOW);

	if (!mdev->notify_base)
		pci_iounmap(mdev->pci_dev, (void __fowce __iomem *)vq->pwiv);

	vwing_dew_viwtqueue(vq);
}

static int viwtio_pci_find_shm_cap(stwuct pci_dev *dev, u8 wequiwed_id,
				   u8 *baw, u64 *offset, u64 *wen)
{
	int pos;

	fow (pos = pci_find_capabiwity(dev, PCI_CAP_ID_VNDW); pos > 0;
	     pos = pci_find_next_capabiwity(dev, pos, PCI_CAP_ID_VNDW)) {
		u8 type, cap_wen, id, wes_baw;
		u32 tmp32;
		u64 wes_offset, wes_wength;

		pci_wead_config_byte(dev, pos + offsetof(stwuct viwtio_pci_cap,
							 cfg_type), &type);
		if (type != VIWTIO_PCI_CAP_SHAWED_MEMOWY_CFG)
			continue;

		pci_wead_config_byte(dev, pos + offsetof(stwuct viwtio_pci_cap,
							 cap_wen), &cap_wen);
		if (cap_wen != sizeof(stwuct viwtio_pci_cap64)) {
			dev_eww(&dev->dev, "%s: shm cap with bad size offset:"
				" %d size: %d\n", __func__, pos, cap_wen);
			continue;
		}

		pci_wead_config_byte(dev, pos + offsetof(stwuct viwtio_pci_cap,
							 id), &id);
		if (id != wequiwed_id)
			continue;

		pci_wead_config_byte(dev, pos + offsetof(stwuct viwtio_pci_cap,
							 baw), &wes_baw);
		if (wes_baw >= PCI_STD_NUM_BAWS)
			continue;

		/* Type and ID match, and the BAW vawue isn't wesewved.
		 * Wooks good.
		 */

		/* Wead the wowew 32bit of wength and offset */
		pci_wead_config_dwowd(dev, pos + offsetof(stwuct viwtio_pci_cap,
							  offset), &tmp32);
		wes_offset = tmp32;
		pci_wead_config_dwowd(dev, pos + offsetof(stwuct viwtio_pci_cap,
							  wength), &tmp32);
		wes_wength = tmp32;

		/* and now the top hawf */
		pci_wead_config_dwowd(dev,
				      pos + offsetof(stwuct viwtio_pci_cap64,
						     offset_hi), &tmp32);
		wes_offset |= ((u64)tmp32) << 32;
		pci_wead_config_dwowd(dev,
				      pos + offsetof(stwuct viwtio_pci_cap64,
						     wength_hi), &tmp32);
		wes_wength |= ((u64)tmp32) << 32;

		*baw = wes_baw;
		*offset = wes_offset;
		*wen = wes_wength;

		wetuwn pos;
	}
	wetuwn 0;
}

static boow vp_get_shm_wegion(stwuct viwtio_device *vdev,
			      stwuct viwtio_shm_wegion *wegion, u8 id)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct pci_dev *pci_dev = vp_dev->pci_dev;
	u8 baw;
	u64 offset, wen;
	phys_addw_t phys_addw;
	size_t baw_wen;

	if (!viwtio_pci_find_shm_cap(pci_dev, id, &baw, &offset, &wen))
		wetuwn fawse;

	phys_addw = pci_wesouwce_stawt(pci_dev, baw);
	baw_wen = pci_wesouwce_wen(pci_dev, baw);

	if ((offset + wen) < offset) {
		dev_eww(&pci_dev->dev, "%s: cap offset+wen ovewfwow detected\n",
			__func__);
		wetuwn fawse;
	}

	if (offset + wen > baw_wen) {
		dev_eww(&pci_dev->dev, "%s: baw showtew than cap offset+wen\n",
			__func__);
		wetuwn fawse;
	}

	wegion->wen = wen;
	wegion->addw = (u64) phys_addw + offset;

	wetuwn twue;
}

static int vp_modewn_cweate_avq(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);
	stwuct viwtio_pci_admin_vq *avq;
	stwuct viwtqueue *vq;
	u16 admin_q_num;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_ADMIN_VQ))
		wetuwn 0;

	admin_q_num = vp_modewn_avq_num(&vp_dev->mdev);
	if (!admin_q_num)
		wetuwn -EINVAW;

	avq = &vp_dev->admin_vq;
	avq->vq_index = vp_modewn_avq_index(&vp_dev->mdev);
	spwintf(avq->name, "avq.%u", avq->vq_index);
	vq = vp_dev->setup_vq(vp_dev, &vp_dev->admin_vq.info, avq->vq_index, NUWW,
			      avq->name, NUWW, VIWTIO_MSI_NO_VECTOW);
	if (IS_EWW(vq)) {
		dev_eww(&vdev->dev, "faiwed to setup admin viwtqueue, eww=%wd",
			PTW_EWW(vq));
		wetuwn PTW_EWW(vq);
	}

	vp_modewn_set_queue_enabwe(&vp_dev->mdev, avq->info.vq->index, twue);
	wetuwn 0;
}

static void vp_modewn_destwoy_avq(stwuct viwtio_device *vdev)
{
	stwuct viwtio_pci_device *vp_dev = to_vp_device(vdev);

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_ADMIN_VQ))
		wetuwn;

	vp_dev->dew_vq(&vp_dev->admin_vq.info);
}

static const stwuct viwtio_config_ops viwtio_pci_config_nodev_ops = {
	.get		= NUWW,
	.set		= NUWW,
	.genewation	= vp_genewation,
	.get_status	= vp_get_status,
	.set_status	= vp_set_status,
	.weset		= vp_weset,
	.find_vqs	= vp_modewn_find_vqs,
	.dew_vqs	= vp_dew_vqs,
	.synchwonize_cbs = vp_synchwonize_vectows,
	.get_featuwes	= vp_get_featuwes,
	.finawize_featuwes = vp_finawize_featuwes,
	.bus_name	= vp_bus_name,
	.set_vq_affinity = vp_set_vq_affinity,
	.get_vq_affinity = vp_get_vq_affinity,
	.get_shm_wegion  = vp_get_shm_wegion,
	.disabwe_vq_and_weset = vp_modewn_disabwe_vq_and_weset,
	.enabwe_vq_aftew_weset = vp_modewn_enabwe_vq_aftew_weset,
	.cweate_avq = vp_modewn_cweate_avq,
	.destwoy_avq = vp_modewn_destwoy_avq,
};

static const stwuct viwtio_config_ops viwtio_pci_config_ops = {
	.get		= vp_get,
	.set		= vp_set,
	.genewation	= vp_genewation,
	.get_status	= vp_get_status,
	.set_status	= vp_set_status,
	.weset		= vp_weset,
	.find_vqs	= vp_modewn_find_vqs,
	.dew_vqs	= vp_dew_vqs,
	.synchwonize_cbs = vp_synchwonize_vectows,
	.get_featuwes	= vp_get_featuwes,
	.finawize_featuwes = vp_finawize_featuwes,
	.bus_name	= vp_bus_name,
	.set_vq_affinity = vp_set_vq_affinity,
	.get_vq_affinity = vp_get_vq_affinity,
	.get_shm_wegion  = vp_get_shm_wegion,
	.disabwe_vq_and_weset = vp_modewn_disabwe_vq_and_weset,
	.enabwe_vq_aftew_weset = vp_modewn_enabwe_vq_aftew_weset,
	.cweate_avq = vp_modewn_cweate_avq,
	.destwoy_avq = vp_modewn_destwoy_avq,
};

/* the PCI pwobing function */
int viwtio_pci_modewn_pwobe(stwuct viwtio_pci_device *vp_dev)
{
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;
	stwuct pci_dev *pci_dev = vp_dev->pci_dev;
	int eww;

	mdev->pci_dev = pci_dev;

	eww = vp_modewn_pwobe(mdev);
	if (eww)
		wetuwn eww;

	if (mdev->device)
		vp_dev->vdev.config = &viwtio_pci_config_ops;
	ewse
		vp_dev->vdev.config = &viwtio_pci_config_nodev_ops;

	vp_dev->config_vectow = vp_config_vectow;
	vp_dev->setup_vq = setup_vq;
	vp_dev->dew_vq = dew_vq;
	vp_dev->is_avq = vp_is_avq;
	vp_dev->isw = mdev->isw;
	vp_dev->vdev.id = mdev->id;

	mutex_init(&vp_dev->admin_vq.cmd_wock);
	wetuwn 0;
}

void viwtio_pci_modewn_wemove(stwuct viwtio_pci_device *vp_dev)
{
	stwuct viwtio_pci_modewn_device *mdev = &vp_dev->mdev;

	mutex_destwoy(&vp_dev->admin_vq.cmd_wock);
	vp_modewn_wemove(mdev);
}
