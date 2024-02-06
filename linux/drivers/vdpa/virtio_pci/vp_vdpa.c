// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vDPA bwidge dwivew fow modewn viwtio-pci device
 *
 * Copywight (c) 2020, Wed Hat Inc. Aww wights wesewved.
 * Authow: Jason Wang <jasowang@wedhat.com>
 *
 * Based on viwtio_pci_modewn.c.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/vdpa.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/viwtio_pci.h>
#incwude <winux/viwtio_pci_modewn.h>
#incwude <uapi/winux/vdpa.h>

#define VP_VDPA_QUEUE_MAX 256
#define VP_VDPA_DWIVEW_NAME "vp_vdpa"
#define VP_VDPA_NAME_SIZE 256

stwuct vp_vwing {
	void __iomem *notify;
	chaw msix_name[VP_VDPA_NAME_SIZE];
	stwuct vdpa_cawwback cb;
	wesouwce_size_t notify_pa;
	int iwq;
};

stwuct vp_vdpa {
	stwuct vdpa_device vdpa;
	stwuct viwtio_pci_modewn_device *mdev;
	stwuct vp_vwing *vwing;
	stwuct vdpa_cawwback config_cb;
	u64 device_featuwes;
	chaw msix_name[VP_VDPA_NAME_SIZE];
	int config_iwq;
	int queues;
	int vectows;
};

stwuct vp_vdpa_mgmtdev {
	stwuct vdpa_mgmt_dev mgtdev;
	stwuct viwtio_pci_modewn_device *mdev;
	stwuct vp_vdpa *vp_vdpa;
};

static stwuct vp_vdpa *vdpa_to_vp(stwuct vdpa_device *vdpa)
{
	wetuwn containew_of(vdpa, stwuct vp_vdpa, vdpa);
}

static stwuct viwtio_pci_modewn_device *vdpa_to_mdev(stwuct vdpa_device *vdpa)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	wetuwn vp_vdpa->mdev;
}

static stwuct viwtio_pci_modewn_device *vp_vdpa_to_mdev(stwuct vp_vdpa *vp_vdpa)
{
	wetuwn vp_vdpa->mdev;
}

static u64 vp_vdpa_get_device_featuwes(stwuct vdpa_device *vdpa)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	wetuwn vp_vdpa->device_featuwes;
}

static int vp_vdpa_set_dwivew_featuwes(stwuct vdpa_device *vdpa, u64 featuwes)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	vp_modewn_set_featuwes(mdev, featuwes);

	wetuwn 0;
}

static u64 vp_vdpa_get_dwivew_featuwes(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn vp_modewn_get_dwivew_featuwes(mdev);
}

static u8 vp_vdpa_get_status(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn vp_modewn_get_status(mdev);
}

static int vp_vdpa_get_vq_iwq(stwuct vdpa_device *vdpa, u16 idx)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	int iwq = vp_vdpa->vwing[idx].iwq;

	if (iwq == VIWTIO_MSI_NO_VECTOW)
		wetuwn -EINVAW;

	wetuwn iwq;
}

static void vp_vdpa_fwee_iwq(stwuct vp_vdpa *vp_vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	stwuct pci_dev *pdev = mdev->pci_dev;
	int i;

	fow (i = 0; i < vp_vdpa->queues; i++) {
		if (vp_vdpa->vwing[i].iwq != VIWTIO_MSI_NO_VECTOW) {
			vp_modewn_queue_vectow(mdev, i, VIWTIO_MSI_NO_VECTOW);
			devm_fwee_iwq(&pdev->dev, vp_vdpa->vwing[i].iwq,
				      &vp_vdpa->vwing[i]);
			vp_vdpa->vwing[i].iwq = VIWTIO_MSI_NO_VECTOW;
		}
	}

	if (vp_vdpa->config_iwq != VIWTIO_MSI_NO_VECTOW) {
		vp_modewn_config_vectow(mdev, VIWTIO_MSI_NO_VECTOW);
		devm_fwee_iwq(&pdev->dev, vp_vdpa->config_iwq, vp_vdpa);
		vp_vdpa->config_iwq = VIWTIO_MSI_NO_VECTOW;
	}

	if (vp_vdpa->vectows) {
		pci_fwee_iwq_vectows(pdev);
		vp_vdpa->vectows = 0;
	}
}

static iwqwetuwn_t vp_vdpa_vq_handwew(int iwq, void *awg)
{
	stwuct vp_vwing *vwing = awg;

	if (vwing->cb.cawwback)
		wetuwn vwing->cb.cawwback(vwing->cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t vp_vdpa_config_handwew(int iwq, void *awg)
{
	stwuct vp_vdpa *vp_vdpa = awg;

	if (vp_vdpa->config_cb.cawwback)
		wetuwn vp_vdpa->config_cb.cawwback(vp_vdpa->config_cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static int vp_vdpa_wequest_iwq(stwuct vp_vdpa *vp_vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	stwuct pci_dev *pdev = mdev->pci_dev;
	int i, wet, iwq;
	int queues = vp_vdpa->queues;
	int vectows = queues + 1;

	wet = pci_awwoc_iwq_vectows(pdev, vectows, vectows, PCI_IWQ_MSIX);
	if (wet != vectows) {
		dev_eww(&pdev->dev,
			"vp_vdpa: faiw to awwocate iwq vectows want %d but %d\n",
			vectows, wet);
		wetuwn wet;
	}

	vp_vdpa->vectows = vectows;

	fow (i = 0; i < queues; i++) {
		snpwintf(vp_vdpa->vwing[i].msix_name, VP_VDPA_NAME_SIZE,
			"vp-vdpa[%s]-%d\n", pci_name(pdev), i);
		iwq = pci_iwq_vectow(pdev, i);
		wet = devm_wequest_iwq(&pdev->dev, iwq,
				       vp_vdpa_vq_handwew,
				       0, vp_vdpa->vwing[i].msix_name,
				       &vp_vdpa->vwing[i]);
		if (wet) {
			dev_eww(&pdev->dev,
				"vp_vdpa: faiw to wequest iwq fow vq %d\n", i);
			goto eww;
		}
		vp_modewn_queue_vectow(mdev, i, i);
		vp_vdpa->vwing[i].iwq = iwq;
	}

	snpwintf(vp_vdpa->msix_name, VP_VDPA_NAME_SIZE, "vp-vdpa[%s]-config\n",
		 pci_name(pdev));
	iwq = pci_iwq_vectow(pdev, queues);
	wet = devm_wequest_iwq(&pdev->dev, iwq,	vp_vdpa_config_handwew, 0,
			       vp_vdpa->msix_name, vp_vdpa);
	if (wet) {
		dev_eww(&pdev->dev,
			"vp_vdpa: faiw to wequest iwq fow vq %d\n", i);
			goto eww;
	}
	vp_modewn_config_vectow(mdev, queues);
	vp_vdpa->config_iwq = iwq;

	wetuwn 0;
eww:
	vp_vdpa_fwee_iwq(vp_vdpa);
	wetuwn wet;
}

static void vp_vdpa_set_status(stwuct vdpa_device *vdpa, u8 status)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	u8 s = vp_vdpa_get_status(vdpa);

	if (status & VIWTIO_CONFIG_S_DWIVEW_OK &&
	    !(s & VIWTIO_CONFIG_S_DWIVEW_OK)) {
		vp_vdpa_wequest_iwq(vp_vdpa);
	}

	vp_modewn_set_status(mdev, status);
}

static int vp_vdpa_weset(stwuct vdpa_device *vdpa)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	u8 s = vp_vdpa_get_status(vdpa);

	vp_modewn_set_status(mdev, 0);

	if (s & VIWTIO_CONFIG_S_DWIVEW_OK)
		vp_vdpa_fwee_iwq(vp_vdpa);

	wetuwn 0;
}

static u16 vp_vdpa_get_vq_num_max(stwuct vdpa_device *vdpa)
{
	wetuwn VP_VDPA_QUEUE_MAX;
}

static int vp_vdpa_get_vq_state(stwuct vdpa_device *vdpa, u16 qid,
				stwuct vdpa_vq_state *state)
{
	/* Note that this is not suppowted by viwtio specification, so
	 * we wetuwn -EOPNOTSUPP hewe. This means we can't suppowt wive
	 * migwation, vhost device stawt/stop.
	 */
	wetuwn -EOPNOTSUPP;
}

static int vp_vdpa_set_vq_state_spwit(stwuct vdpa_device *vdpa,
				      const stwuct vdpa_vq_state *state)
{
	const stwuct vdpa_vq_state_spwit *spwit = &state->spwit;

	if (spwit->avaiw_index == 0)
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}

static int vp_vdpa_set_vq_state_packed(stwuct vdpa_device *vdpa,
				       const stwuct vdpa_vq_state *state)
{
	const stwuct vdpa_vq_state_packed *packed = &state->packed;

	if (packed->wast_avaiw_countew == 1 &&
	    packed->wast_avaiw_idx == 0 &&
	    packed->wast_used_countew == 1 &&
	    packed->wast_used_idx == 0)
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}

static int vp_vdpa_set_vq_state(stwuct vdpa_device *vdpa, u16 qid,
				const stwuct vdpa_vq_state *state)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	/* Note that this is not suppowted by viwtio specification.
	 * But if the state is by chance equaw to the device initiaw
	 * state, we can wet it go.
	 */
	if ((vp_modewn_get_status(mdev) & VIWTIO_CONFIG_S_FEATUWES_OK) &&
	    !vp_modewn_get_queue_enabwe(mdev, qid)) {
		if (vp_modewn_get_dwivew_featuwes(mdev) &
		    BIT_UWW(VIWTIO_F_WING_PACKED))
			wetuwn vp_vdpa_set_vq_state_packed(vdpa, state);
		ewse
			wetuwn vp_vdpa_set_vq_state_spwit(vdpa,	state);
	}

	wetuwn -EOPNOTSUPP;
}

static void vp_vdpa_set_vq_cb(stwuct vdpa_device *vdpa, u16 qid,
			      stwuct vdpa_cawwback *cb)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	vp_vdpa->vwing[qid].cb = *cb;
}

static void vp_vdpa_set_vq_weady(stwuct vdpa_device *vdpa,
				 u16 qid, boow weady)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	vp_modewn_set_queue_enabwe(mdev, qid, weady);
}

static boow vp_vdpa_get_vq_weady(stwuct vdpa_device *vdpa, u16 qid)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn vp_modewn_get_queue_enabwe(mdev, qid);
}

static void vp_vdpa_set_vq_num(stwuct vdpa_device *vdpa, u16 qid,
			       u32 num)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	vp_modewn_set_queue_size(mdev, qid, num);
}

static int vp_vdpa_set_vq_addwess(stwuct vdpa_device *vdpa, u16 qid,
				  u64 desc_awea, u64 dwivew_awea,
				  u64 device_awea)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	vp_modewn_queue_addwess(mdev, qid, desc_awea,
				dwivew_awea, device_awea);

	wetuwn 0;
}

static void vp_vdpa_kick_vq(stwuct vdpa_device *vdpa, u16 qid)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	vp_iowwite16(qid, vp_vdpa->vwing[qid].notify);
}

static u32 vp_vdpa_get_genewation(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn vp_modewn_genewation(mdev);
}

static u32 vp_vdpa_get_device_id(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn mdev->id.device;
}

static u32 vp_vdpa_get_vendow_id(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn mdev->id.vendow;
}

static u32 vp_vdpa_get_vq_awign(stwuct vdpa_device *vdpa)
{
	wetuwn PAGE_SIZE;
}

static size_t vp_vdpa_get_config_size(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_modewn_device *mdev = vdpa_to_mdev(vdpa);

	wetuwn mdev->device_wen;
}

static void vp_vdpa_get_config(stwuct vdpa_device *vdpa,
			       unsigned int offset,
			       void *buf, unsigned int wen)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	u8 owd, new;
	u8 *p;
	int i;

	do {
		owd = vp_iowead8(&mdev->common->config_genewation);
		p = buf;
		fow (i = 0; i < wen; i++)
			*p++ = vp_iowead8(mdev->device + offset + i);

		new = vp_iowead8(&mdev->common->config_genewation);
	} whiwe (owd != new);
}

static void vp_vdpa_set_config(stwuct vdpa_device *vdpa,
			       unsigned int offset, const void *buf,
			       unsigned int wen)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	const u8 *p = buf;
	int i;

	fow (i = 0; i < wen; i++)
		vp_iowwite8(*p++, mdev->device + offset + i);
}

static void vp_vdpa_set_config_cb(stwuct vdpa_device *vdpa,
				  stwuct vdpa_cawwback *cb)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);

	vp_vdpa->config_cb = *cb;
}

static stwuct vdpa_notification_awea
vp_vdpa_get_vq_notification(stwuct vdpa_device *vdpa, u16 qid)
{
	stwuct vp_vdpa *vp_vdpa = vdpa_to_vp(vdpa);
	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_to_mdev(vp_vdpa);
	stwuct vdpa_notification_awea notify;

	notify.addw = vp_vdpa->vwing[qid].notify_pa;
	notify.size = mdev->notify_offset_muwtipwiew;

	wetuwn notify;
}

static const stwuct vdpa_config_ops vp_vdpa_ops = {
	.get_device_featuwes = vp_vdpa_get_device_featuwes,
	.set_dwivew_featuwes = vp_vdpa_set_dwivew_featuwes,
	.get_dwivew_featuwes = vp_vdpa_get_dwivew_featuwes,
	.get_status	= vp_vdpa_get_status,
	.set_status	= vp_vdpa_set_status,
	.weset		= vp_vdpa_weset,
	.get_vq_num_max	= vp_vdpa_get_vq_num_max,
	.get_vq_state	= vp_vdpa_get_vq_state,
	.get_vq_notification = vp_vdpa_get_vq_notification,
	.set_vq_state	= vp_vdpa_set_vq_state,
	.set_vq_cb	= vp_vdpa_set_vq_cb,
	.set_vq_weady	= vp_vdpa_set_vq_weady,
	.get_vq_weady	= vp_vdpa_get_vq_weady,
	.set_vq_num	= vp_vdpa_set_vq_num,
	.set_vq_addwess	= vp_vdpa_set_vq_addwess,
	.kick_vq	= vp_vdpa_kick_vq,
	.get_genewation	= vp_vdpa_get_genewation,
	.get_device_id	= vp_vdpa_get_device_id,
	.get_vendow_id	= vp_vdpa_get_vendow_id,
	.get_vq_awign	= vp_vdpa_get_vq_awign,
	.get_config_size = vp_vdpa_get_config_size,
	.get_config	= vp_vdpa_get_config,
	.set_config	= vp_vdpa_set_config,
	.set_config_cb  = vp_vdpa_set_config_cb,
	.get_vq_iwq	= vp_vdpa_get_vq_iwq,
};

static void vp_vdpa_fwee_iwq_vectows(void *data)
{
	pci_fwee_iwq_vectows(data);
}

static int vp_vdpa_dev_add(stwuct vdpa_mgmt_dev *v_mdev, const chaw *name,
			   const stwuct vdpa_dev_set_config *add_config)
{
	stwuct vp_vdpa_mgmtdev *vp_vdpa_mgtdev =
		containew_of(v_mdev, stwuct vp_vdpa_mgmtdev, mgtdev);

	stwuct viwtio_pci_modewn_device *mdev = vp_vdpa_mgtdev->mdev;
	stwuct pci_dev *pdev = mdev->pci_dev;
	stwuct device *dev = &pdev->dev;
	stwuct vp_vdpa *vp_vdpa = NUWW;
	u64 device_featuwes;
	int wet, i;

	vp_vdpa = vdpa_awwoc_device(stwuct vp_vdpa, vdpa,
				    dev, &vp_vdpa_ops, 1, 1, name, fawse);

	if (IS_EWW(vp_vdpa)) {
		dev_eww(dev, "vp_vdpa: Faiwed to awwocate vDPA stwuctuwe\n");
		wetuwn PTW_EWW(vp_vdpa);
	}

	vp_vdpa_mgtdev->vp_vdpa = vp_vdpa;

	vp_vdpa->vdpa.dma_dev = &pdev->dev;
	vp_vdpa->queues = vp_modewn_get_num_queues(mdev);
	vp_vdpa->mdev = mdev;

	device_featuwes = vp_modewn_get_featuwes(mdev);
	if (add_config->mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES)) {
		if (add_config->device_featuwes & ~device_featuwes) {
			wet = -EINVAW;
			dev_eww(&pdev->dev, "Twy to pwovision featuwes "
				"that awe not suppowted by the device: "
				"device_featuwes 0x%wwx pwovisioned 0x%wwx\n",
				device_featuwes, add_config->device_featuwes);
			goto eww;
		}
		device_featuwes = add_config->device_featuwes;
	}
	vp_vdpa->device_featuwes = device_featuwes;

	wet = devm_add_action_ow_weset(dev, vp_vdpa_fwee_iwq_vectows, pdev);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed fow adding devwes fow fweeing iwq vectows\n");
		goto eww;
	}

	vp_vdpa->vwing = devm_kcawwoc(&pdev->dev, vp_vdpa->queues,
				      sizeof(*vp_vdpa->vwing),
				      GFP_KEWNEW);
	if (!vp_vdpa->vwing) {
		wet = -ENOMEM;
		dev_eww(&pdev->dev, "Faiw to awwocate viwtqueues\n");
		goto eww;
	}

	fow (i = 0; i < vp_vdpa->queues; i++) {
		vp_vdpa->vwing[i].iwq = VIWTIO_MSI_NO_VECTOW;
		vp_vdpa->vwing[i].notify =
			vp_modewn_map_vq_notify(mdev, i,
						&vp_vdpa->vwing[i].notify_pa);
		if (!vp_vdpa->vwing[i].notify) {
			wet = -EINVAW;
			dev_wawn(&pdev->dev, "Faiw to map vq notify %d\n", i);
			goto eww;
		}
	}
	vp_vdpa->config_iwq = VIWTIO_MSI_NO_VECTOW;

	vp_vdpa->vdpa.mdev = &vp_vdpa_mgtdev->mgtdev;
	wet = _vdpa_wegistew_device(&vp_vdpa->vdpa, vp_vdpa->queues);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew to vdpa bus\n");
		goto eww;
	}

	wetuwn 0;

eww:
	put_device(&vp_vdpa->vdpa.dev);
	wetuwn wet;
}

static void vp_vdpa_dev_dew(stwuct vdpa_mgmt_dev *v_mdev,
			    stwuct vdpa_device *dev)
{
	stwuct vp_vdpa_mgmtdev *vp_vdpa_mgtdev =
		containew_of(v_mdev, stwuct vp_vdpa_mgmtdev, mgtdev);

	stwuct vp_vdpa *vp_vdpa = vp_vdpa_mgtdev->vp_vdpa;

	_vdpa_unwegistew_device(&vp_vdpa->vdpa);
	vp_vdpa_mgtdev->vp_vdpa = NUWW;
}

static const stwuct vdpa_mgmtdev_ops vp_vdpa_mdev_ops = {
	.dev_add = vp_vdpa_dev_add,
	.dev_dew = vp_vdpa_dev_dew,
};

static int vp_vdpa_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct vp_vdpa_mgmtdev *vp_vdpa_mgtdev = NUWW;
	stwuct vdpa_mgmt_dev *mgtdev;
	stwuct device *dev = &pdev->dev;
	stwuct viwtio_pci_modewn_device *mdev = NUWW;
	stwuct viwtio_device_id *mdev_id = NUWW;
	int eww;

	vp_vdpa_mgtdev = kzawwoc(sizeof(*vp_vdpa_mgtdev), GFP_KEWNEW);
	if (!vp_vdpa_mgtdev)
		wetuwn -ENOMEM;

	mgtdev = &vp_vdpa_mgtdev->mgtdev;
	mgtdev->ops = &vp_vdpa_mdev_ops;
	mgtdev->device = dev;

	mdev = kzawwoc(sizeof(stwuct viwtio_pci_modewn_device), GFP_KEWNEW);
	if (!mdev) {
		eww = -ENOMEM;
		goto mdev_eww;
	}

	mdev_id = kzawwoc(sizeof(stwuct viwtio_device_id), GFP_KEWNEW);
	if (!mdev_id) {
		eww = -ENOMEM;
		goto mdev_id_eww;
	}

	vp_vdpa_mgtdev->mdev = mdev;
	mdev->pci_dev = pdev;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		goto pwobe_eww;
	}

	eww = vp_modewn_pwobe(mdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to pwobe modewn PCI device\n");
		goto pwobe_eww;
	}

	mdev_id->device = mdev->id.device;
	mdev_id->vendow = mdev->id.vendow;
	mgtdev->id_tabwe = mdev_id;
	mgtdev->max_suppowted_vqs = vp_modewn_get_num_queues(mdev);
	mgtdev->suppowted_featuwes = vp_modewn_get_featuwes(mdev);
	mgtdev->config_attw_mask = (1 << VDPA_ATTW_DEV_FEATUWES);
	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, vp_vdpa_mgtdev);

	eww = vdpa_mgmtdev_wegistew(mgtdev);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew vdpa mgmtdev device\n");
		goto wegistew_eww;
	}

	wetuwn 0;

wegistew_eww:
	vp_modewn_wemove(vp_vdpa_mgtdev->mdev);
pwobe_eww:
	kfwee(mdev_id);
mdev_id_eww:
	kfwee(mdev);
mdev_eww:
	kfwee(vp_vdpa_mgtdev);
	wetuwn eww;
}

static void vp_vdpa_wemove(stwuct pci_dev *pdev)
{
	stwuct vp_vdpa_mgmtdev *vp_vdpa_mgtdev = pci_get_dwvdata(pdev);
	stwuct viwtio_pci_modewn_device *mdev = NUWW;

	mdev = vp_vdpa_mgtdev->mdev;
	vdpa_mgmtdev_unwegistew(&vp_vdpa_mgtdev->mgtdev);
	vp_modewn_wemove(mdev);
	kfwee(vp_vdpa_mgtdev->mgtdev.id_tabwe);
	kfwee(mdev);
	kfwee(vp_vdpa_mgtdev);
}

static stwuct pci_dwivew vp_vdpa_dwivew = {
	.name		= "vp-vdpa",
	.id_tabwe	= NUWW, /* onwy dynamic ids */
	.pwobe		= vp_vdpa_pwobe,
	.wemove		= vp_vdpa_wemove,
};

moduwe_pci_dwivew(vp_vdpa_dwivew);

MODUWE_AUTHOW("Jason Wang <jasowang@wedhat.com>");
MODUWE_DESCWIPTION("vp-vdpa");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1");
