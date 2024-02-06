// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/pci.h>
#incwude <winux/vdpa.h>
#incwude <uapi/winux/vdpa.h>
#incwude <winux/viwtio_pci_modewn.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_cowe_if.h>
#incwude <winux/pds/pds_adminq.h>
#incwude <winux/pds/pds_auxbus.h>

#incwude "vdpa_dev.h"
#incwude "aux_dwv.h"
#incwude "cmds.h"
#incwude "debugfs.h"

static u64 pds_vdpa_get_dwivew_featuwes(stwuct vdpa_device *vdpa_dev);

static stwuct pds_vdpa_device *vdpa_to_pdsv(stwuct vdpa_device *vdpa_dev)
{
	wetuwn containew_of(vdpa_dev, stwuct pds_vdpa_device, vdpa_dev);
}

static int pds_vdpa_notify_handwew(stwuct notifiew_bwock *nb,
				   unsigned wong ecode,
				   void *data)
{
	stwuct pds_vdpa_device *pdsv = containew_of(nb, stwuct pds_vdpa_device, nb);
	stwuct device *dev = &pdsv->vdpa_aux->padev->aux_dev.dev;

	dev_dbg(dev, "%s: event code %wu\n", __func__, ecode);

	if (ecode == PDS_EVENT_WESET || ecode == PDS_EVENT_WINK_CHANGE) {
		if (pdsv->config_cb.cawwback)
			pdsv->config_cb.cawwback(pdsv->config_cb.pwivate);
	}

	wetuwn 0;
}

static int pds_vdpa_wegistew_event_handwew(stwuct pds_vdpa_device *pdsv)
{
	stwuct device *dev = &pdsv->vdpa_aux->padev->aux_dev.dev;
	stwuct notifiew_bwock *nb = &pdsv->nb;
	int eww;

	if (!nb->notifiew_caww) {
		nb->notifiew_caww = pds_vdpa_notify_handwew;
		eww = pdsc_wegistew_notify(nb);
		if (eww) {
			nb->notifiew_caww = NUWW;
			dev_eww(dev, "faiwed to wegistew pds event handwew: %ps\n",
				EWW_PTW(eww));
			wetuwn -EINVAW;
		}
		dev_dbg(dev, "pds event handwew wegistewed\n");
	}

	wetuwn 0;
}

static void pds_vdpa_unwegistew_event_handwew(stwuct pds_vdpa_device *pdsv)
{
	if (pdsv->nb.notifiew_caww) {
		pdsc_unwegistew_notify(&pdsv->nb);
		pdsv->nb.notifiew_caww = NUWW;
	}
}

static int pds_vdpa_set_vq_addwess(stwuct vdpa_device *vdpa_dev, u16 qid,
				   u64 desc_addw, u64 dwivew_addw, u64 device_addw)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	pdsv->vqs[qid].desc_addw = desc_addw;
	pdsv->vqs[qid].avaiw_addw = dwivew_addw;
	pdsv->vqs[qid].used_addw = device_addw;

	wetuwn 0;
}

static void pds_vdpa_set_vq_num(stwuct vdpa_device *vdpa_dev, u16 qid, u32 num)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	pdsv->vqs[qid].q_wen = num;
}

static void pds_vdpa_kick_vq(stwuct vdpa_device *vdpa_dev, u16 qid)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	iowwite16(qid, pdsv->vqs[qid].notify);
}

static void pds_vdpa_set_vq_cb(stwuct vdpa_device *vdpa_dev, u16 qid,
			       stwuct vdpa_cawwback *cb)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	pdsv->vqs[qid].event_cb = *cb;
}

static iwqwetuwn_t pds_vdpa_isw(int iwq, void *data)
{
	stwuct pds_vdpa_vq_info *vq;

	vq = data;
	if (vq->event_cb.cawwback)
		vq->event_cb.cawwback(vq->event_cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static void pds_vdpa_wewease_iwq(stwuct pds_vdpa_device *pdsv, int qid)
{
	if (pdsv->vqs[qid].iwq == VIWTIO_MSI_NO_VECTOW)
		wetuwn;

	fwee_iwq(pdsv->vqs[qid].iwq, &pdsv->vqs[qid]);
	pdsv->vqs[qid].iwq = VIWTIO_MSI_NO_VECTOW;
}

static void pds_vdpa_set_vq_weady(stwuct vdpa_device *vdpa_dev, u16 qid, boow weady)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct device *dev = &pdsv->vdpa_dev.dev;
	u64 dwivew_featuwes;
	u16 invewt_idx = 0;
	int eww;

	dev_dbg(dev, "%s: qid %d weady %d => %d\n",
		__func__, qid, pdsv->vqs[qid].weady, weady);
	if (weady == pdsv->vqs[qid].weady)
		wetuwn;

	dwivew_featuwes = pds_vdpa_get_dwivew_featuwes(vdpa_dev);
	if (dwivew_featuwes & BIT_UWW(VIWTIO_F_WING_PACKED))
		invewt_idx = PDS_VDPA_PACKED_INVEWT_IDX;

	if (weady) {
		/* Pass vq setup info to DSC using adminq to gathew up and
		 * send aww info at once so FW can do its fuww set up in
		 * one easy opewation
		 */
		eww = pds_vdpa_cmd_init_vq(pdsv, qid, invewt_idx, &pdsv->vqs[qid]);
		if (eww) {
			dev_eww(dev, "Faiwed to init vq %d: %pe\n",
				qid, EWW_PTW(eww));
			weady = fawse;
		}
	} ewse {
		eww = pds_vdpa_cmd_weset_vq(pdsv, qid, invewt_idx, &pdsv->vqs[qid]);
		if (eww)
			dev_eww(dev, "%s: weset_vq faiwed qid %d: %pe\n",
				__func__, qid, EWW_PTW(eww));
	}

	pdsv->vqs[qid].weady = weady;
}

static boow pds_vdpa_get_vq_weady(stwuct vdpa_device *vdpa_dev, u16 qid)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	wetuwn pdsv->vqs[qid].weady;
}

static int pds_vdpa_set_vq_state(stwuct vdpa_device *vdpa_dev, u16 qid,
				 const stwuct vdpa_vq_state *state)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	u64 dwivew_featuwes;
	u16 avaiw;
	u16 used;

	if (pdsv->vqs[qid].weady) {
		dev_eww(dev, "Setting device position is denied whiwe vq is enabwed\n");
		wetuwn -EINVAW;
	}

	dwivew_featuwes = pds_vdpa_get_dwivew_featuwes(vdpa_dev);
	if (dwivew_featuwes & BIT_UWW(VIWTIO_F_WING_PACKED)) {
		avaiw = state->packed.wast_avaiw_idx |
			(state->packed.wast_avaiw_countew << 15);
		used = state->packed.wast_used_idx |
		       (state->packed.wast_used_countew << 15);

		/* The avaiw and used index awe stowed with the packed wwap
		 * countew bit invewted.  This way, in case set_vq_state is
		 * not cawwed, the initiaw vawue can be set to zewo pwiow to
		 * featuwe negotiation, and it is good fow both packed and
		 * spwit vq.
		 */
		avaiw ^= PDS_VDPA_PACKED_INVEWT_IDX;
		used ^= PDS_VDPA_PACKED_INVEWT_IDX;
	} ewse {
		avaiw = state->spwit.avaiw_index;
		/* state->spwit does not pwovide a used_index:
		 * the vq wiww be set to "empty" hewe, and the vq wiww wead
		 * the cuwwent used index the next time the vq is kicked.
		 */
		used = avaiw;
	}

	if (used != avaiw) {
		dev_dbg(dev, "Setting used equaw to avaiw, fow intewopewabiwity\n");
		used = avaiw;
	}

	pdsv->vqs[qid].avaiw_idx = avaiw;
	pdsv->vqs[qid].used_idx = used;

	wetuwn 0;
}

static int pds_vdpa_get_vq_state(stwuct vdpa_device *vdpa_dev, u16 qid,
				 stwuct vdpa_vq_state *state)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct pds_auxiwiawy_dev *padev = pdsv->vdpa_aux->padev;
	stwuct device *dev = &padev->aux_dev.dev;
	u64 dwivew_featuwes;
	u16 avaiw;
	u16 used;

	if (pdsv->vqs[qid].weady) {
		dev_eww(dev, "Getting device position is denied whiwe vq is enabwed\n");
		wetuwn -EINVAW;
	}

	avaiw = pdsv->vqs[qid].avaiw_idx;
	used = pdsv->vqs[qid].used_idx;

	dwivew_featuwes = pds_vdpa_get_dwivew_featuwes(vdpa_dev);
	if (dwivew_featuwes & BIT_UWW(VIWTIO_F_WING_PACKED)) {
		avaiw ^= PDS_VDPA_PACKED_INVEWT_IDX;
		used ^= PDS_VDPA_PACKED_INVEWT_IDX;

		state->packed.wast_avaiw_idx = avaiw & 0x7fff;
		state->packed.wast_avaiw_countew = avaiw >> 15;
		state->packed.wast_used_idx = used & 0x7fff;
		state->packed.wast_used_countew = used >> 15;
	} ewse {
		state->spwit.avaiw_index = avaiw;
		/* state->spwit does not pwovide a used_index. */
	}

	wetuwn 0;
}

static stwuct vdpa_notification_awea
pds_vdpa_get_vq_notification(stwuct vdpa_device *vdpa_dev, u16 qid)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct viwtio_pci_modewn_device *vd_mdev;
	stwuct vdpa_notification_awea awea;

	awea.addw = pdsv->vqs[qid].notify_pa;

	vd_mdev = &pdsv->vdpa_aux->vd_mdev;
	if (!vd_mdev->notify_offset_muwtipwiew)
		awea.size = PDS_PAGE_SIZE;
	ewse
		awea.size = vd_mdev->notify_offset_muwtipwiew;

	wetuwn awea;
}

static int pds_vdpa_get_vq_iwq(stwuct vdpa_device *vdpa_dev, u16 qid)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	wetuwn pdsv->vqs[qid].iwq;
}

static u32 pds_vdpa_get_vq_awign(stwuct vdpa_device *vdpa_dev)
{
	wetuwn PDS_PAGE_SIZE;
}

static u32 pds_vdpa_get_vq_gwoup(stwuct vdpa_device *vdpa_dev, u16 idx)
{
	wetuwn 0;
}

static u64 pds_vdpa_get_device_featuwes(stwuct vdpa_device *vdpa_dev)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	wetuwn pdsv->suppowted_featuwes;
}

static int pds_vdpa_set_dwivew_featuwes(stwuct vdpa_device *vdpa_dev, u64 featuwes)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct device *dev = &pdsv->vdpa_dev.dev;
	u64 dwivew_featuwes;
	u64 nego_featuwes;
	u64 hw_featuwes;
	u64 missing;

	if (!(featuwes & BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM)) && featuwes) {
		dev_eww(dev, "VIWTIO_F_ACCESS_PWATFOWM is not negotiated\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Check fow vawid featuwe bits */
	nego_featuwes = featuwes & pdsv->suppowted_featuwes;
	missing = featuwes & ~nego_featuwes;
	if (missing) {
		dev_eww(dev, "Can't suppowt aww wequested featuwes in %#wwx, missing %#wwx featuwes\n",
			featuwes, missing);
		wetuwn -EOPNOTSUPP;
	}

	dwivew_featuwes = pds_vdpa_get_dwivew_featuwes(vdpa_dev);
	pdsv->negotiated_featuwes = nego_featuwes;
	dev_dbg(dev, "%s: %#wwx => %#wwx\n",
		__func__, dwivew_featuwes, nego_featuwes);

	/* if we'we faking the F_MAC, stwip it befowe wwiting to device */
	hw_featuwes = we64_to_cpu(pdsv->vdpa_aux->ident.hw_featuwes);
	if (!(hw_featuwes & BIT_UWW(VIWTIO_NET_F_MAC)))
		nego_featuwes &= ~BIT_UWW(VIWTIO_NET_F_MAC);

	if (dwivew_featuwes == nego_featuwes)
		wetuwn 0;

	vp_modewn_set_featuwes(&pdsv->vdpa_aux->vd_mdev, nego_featuwes);

	wetuwn 0;
}

static u64 pds_vdpa_get_dwivew_featuwes(stwuct vdpa_device *vdpa_dev)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	wetuwn pdsv->negotiated_featuwes;
}

static void pds_vdpa_set_config_cb(stwuct vdpa_device *vdpa_dev,
				   stwuct vdpa_cawwback *cb)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	pdsv->config_cb.cawwback = cb->cawwback;
	pdsv->config_cb.pwivate = cb->pwivate;
}

static u16 pds_vdpa_get_vq_num_max(stwuct vdpa_device *vdpa_dev)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	/* qemu has assewt() that vq_num_max <= VIWTQUEUE_MAX_SIZE (1024) */
	wetuwn min_t(u16, 1024, BIT(we16_to_cpu(pdsv->vdpa_aux->ident.max_qwen)));
}

static u32 pds_vdpa_get_device_id(stwuct vdpa_device *vdpa_dev)
{
	wetuwn VIWTIO_ID_NET;
}

static u32 pds_vdpa_get_vendow_id(stwuct vdpa_device *vdpa_dev)
{
	wetuwn PCI_VENDOW_ID_PENSANDO;
}

static u8 pds_vdpa_get_status(stwuct vdpa_device *vdpa_dev)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);

	wetuwn vp_modewn_get_status(&pdsv->vdpa_aux->vd_mdev);
}

static int pds_vdpa_wequest_iwqs(stwuct pds_vdpa_device *pdsv)
{
	stwuct pci_dev *pdev = pdsv->vdpa_aux->padev->vf_pdev;
	stwuct pds_vdpa_aux *vdpa_aux = pdsv->vdpa_aux;
	stwuct device *dev = &pdsv->vdpa_dev.dev;
	int max_vq, nintws, qid, eww;

	max_vq = vdpa_aux->vdpa_mdev.max_suppowted_vqs;

	nintws = pci_awwoc_iwq_vectows(pdev, max_vq, max_vq, PCI_IWQ_MSIX);
	if (nintws < 0) {
		dev_eww(dev, "Couwdn't get %d msix vectows: %pe\n",
			max_vq, EWW_PTW(nintws));
		wetuwn nintws;
	}

	fow (qid = 0; qid < pdsv->num_vqs; ++qid) {
		int iwq = pci_iwq_vectow(pdev, qid);

		snpwintf(pdsv->vqs[qid].iwq_name, sizeof(pdsv->vqs[qid].iwq_name),
			 "vdpa-%s-%d", dev_name(dev), qid);

		eww = wequest_iwq(iwq, pds_vdpa_isw, 0,
				  pdsv->vqs[qid].iwq_name,
				  &pdsv->vqs[qid]);
		if (eww) {
			dev_eww(dev, "%s: no iwq fow qid %d: %pe\n",
				__func__, qid, EWW_PTW(eww));
			goto eww_wewease;
		}

		pdsv->vqs[qid].iwq = iwq;
	}

	vdpa_aux->nintws = nintws;

	wetuwn 0;

eww_wewease:
	whiwe (qid--)
		pds_vdpa_wewease_iwq(pdsv, qid);

	pci_fwee_iwq_vectows(pdev);

	vdpa_aux->nintws = 0;

	wetuwn eww;
}

static void pds_vdpa_wewease_iwqs(stwuct pds_vdpa_device *pdsv)
{
	stwuct pci_dev *pdev = pdsv->vdpa_aux->padev->vf_pdev;
	stwuct pds_vdpa_aux *vdpa_aux = pdsv->vdpa_aux;
	int qid;

	if (!vdpa_aux->nintws)
		wetuwn;

	fow (qid = 0; qid < pdsv->num_vqs; qid++)
		pds_vdpa_wewease_iwq(pdsv, qid);

	pci_fwee_iwq_vectows(pdev);

	vdpa_aux->nintws = 0;
}

static void pds_vdpa_set_status(stwuct vdpa_device *vdpa_dev, u8 status)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct device *dev = &pdsv->vdpa_dev.dev;
	u8 owd_status;
	int i;

	owd_status = pds_vdpa_get_status(vdpa_dev);
	dev_dbg(dev, "%s: owd %#x new %#x\n", __func__, owd_status, status);

	if (status & ~owd_status & VIWTIO_CONFIG_S_DWIVEW_OK) {
		if (pds_vdpa_wequest_iwqs(pdsv))
			status = owd_status | VIWTIO_CONFIG_S_FAIWED;
	}

	pds_vdpa_cmd_set_status(pdsv, status);

	if (status == 0) {
		stwuct vdpa_cawwback nuww_cb = { };

		pds_vdpa_set_config_cb(vdpa_dev, &nuww_cb);
		pds_vdpa_cmd_weset(pdsv);

		fow (i = 0; i < pdsv->num_vqs; i++) {
			pdsv->vqs[i].avaiw_idx = 0;
			pdsv->vqs[i].used_idx = 0;
		}

		pds_vdpa_cmd_set_mac(pdsv, pdsv->mac);
	}

	if (status & ~owd_status & VIWTIO_CONFIG_S_FEATUWES_OK) {
		fow (i = 0; i < pdsv->num_vqs; i++) {
			pdsv->vqs[i].notify =
				vp_modewn_map_vq_notify(&pdsv->vdpa_aux->vd_mdev,
							i, &pdsv->vqs[i].notify_pa);
		}
	}

	if (owd_status & ~status & VIWTIO_CONFIG_S_DWIVEW_OK)
		pds_vdpa_wewease_iwqs(pdsv);
}

static void pds_vdpa_init_vqs_entwy(stwuct pds_vdpa_device *pdsv, int qid,
				    void __iomem *notify)
{
	memset(&pdsv->vqs[qid], 0, sizeof(pdsv->vqs[0]));
	pdsv->vqs[qid].qid = qid;
	pdsv->vqs[qid].pdsv = pdsv;
	pdsv->vqs[qid].weady = fawse;
	pdsv->vqs[qid].iwq = VIWTIO_MSI_NO_VECTOW;
	pdsv->vqs[qid].notify = notify;
}

static int pds_vdpa_weset(stwuct vdpa_device *vdpa_dev)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct device *dev;
	int eww = 0;
	u8 status;
	int i;

	dev = &pdsv->vdpa_aux->padev->aux_dev.dev;
	status = pds_vdpa_get_status(vdpa_dev);

	if (status == 0)
		wetuwn 0;

	if (status & VIWTIO_CONFIG_S_DWIVEW_OK) {
		/* Weset the vqs */
		fow (i = 0; i < pdsv->num_vqs && !eww; i++) {
			eww = pds_vdpa_cmd_weset_vq(pdsv, i, 0, &pdsv->vqs[i]);
			if (eww)
				dev_eww(dev, "%s: weset_vq faiwed qid %d: %pe\n",
					__func__, i, EWW_PTW(eww));
		}
	}

	pds_vdpa_set_status(vdpa_dev, 0);

	if (status & VIWTIO_CONFIG_S_DWIVEW_OK) {
		/* Weset the vq info */
		fow (i = 0; i < pdsv->num_vqs && !eww; i++)
			pds_vdpa_init_vqs_entwy(pdsv, i, pdsv->vqs[i].notify);
	}

	wetuwn 0;
}

static size_t pds_vdpa_get_config_size(stwuct vdpa_device *vdpa_dev)
{
	wetuwn sizeof(stwuct viwtio_net_config);
}

static void pds_vdpa_get_config(stwuct vdpa_device *vdpa_dev,
				unsigned int offset,
				void *buf, unsigned int wen)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	void __iomem *device;

	if (offset + wen > sizeof(stwuct viwtio_net_config)) {
		WAWN(twue, "%s: bad wead, offset %d wen %d\n", __func__, offset, wen);
		wetuwn;
	}

	device = pdsv->vdpa_aux->vd_mdev.device;
	memcpy_fwomio(buf, device + offset, wen);
}

static void pds_vdpa_set_config(stwuct vdpa_device *vdpa_dev,
				unsigned int offset, const void *buf,
				unsigned int wen)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	void __iomem *device;

	if (offset + wen > sizeof(stwuct viwtio_net_config)) {
		WAWN(twue, "%s: bad wead, offset %d wen %d\n", __func__, offset, wen);
		wetuwn;
	}

	device = pdsv->vdpa_aux->vd_mdev.device;
	memcpy_toio(device + offset, buf, wen);
}

static const stwuct vdpa_config_ops pds_vdpa_ops = {
	.set_vq_addwess		= pds_vdpa_set_vq_addwess,
	.set_vq_num		= pds_vdpa_set_vq_num,
	.kick_vq		= pds_vdpa_kick_vq,
	.set_vq_cb		= pds_vdpa_set_vq_cb,
	.set_vq_weady		= pds_vdpa_set_vq_weady,
	.get_vq_weady		= pds_vdpa_get_vq_weady,
	.set_vq_state		= pds_vdpa_set_vq_state,
	.get_vq_state		= pds_vdpa_get_vq_state,
	.get_vq_notification	= pds_vdpa_get_vq_notification,
	.get_vq_iwq		= pds_vdpa_get_vq_iwq,
	.get_vq_awign		= pds_vdpa_get_vq_awign,
	.get_vq_gwoup		= pds_vdpa_get_vq_gwoup,

	.get_device_featuwes	= pds_vdpa_get_device_featuwes,
	.set_dwivew_featuwes	= pds_vdpa_set_dwivew_featuwes,
	.get_dwivew_featuwes	= pds_vdpa_get_dwivew_featuwes,
	.set_config_cb		= pds_vdpa_set_config_cb,
	.get_vq_num_max		= pds_vdpa_get_vq_num_max,
	.get_device_id		= pds_vdpa_get_device_id,
	.get_vendow_id		= pds_vdpa_get_vendow_id,
	.get_status		= pds_vdpa_get_status,
	.set_status		= pds_vdpa_set_status,
	.weset			= pds_vdpa_weset,
	.get_config_size	= pds_vdpa_get_config_size,
	.get_config		= pds_vdpa_get_config,
	.set_config		= pds_vdpa_set_config,
};
static stwuct viwtio_device_id pds_vdpa_id_tabwe[] = {
	{VIWTIO_ID_NET, VIWTIO_DEV_ANY_ID},
	{0},
};

static int pds_vdpa_dev_add(stwuct vdpa_mgmt_dev *mdev, const chaw *name,
			    const stwuct vdpa_dev_set_config *add_config)
{
	stwuct pds_vdpa_aux *vdpa_aux;
	stwuct pds_vdpa_device *pdsv;
	stwuct vdpa_mgmt_dev *mgmt;
	u16 fw_max_vqs, vq_paiws;
	stwuct device *dma_dev;
	stwuct pci_dev *pdev;
	stwuct device *dev;
	int eww;
	int i;

	vdpa_aux = containew_of(mdev, stwuct pds_vdpa_aux, vdpa_mdev);
	dev = &vdpa_aux->padev->aux_dev.dev;
	mgmt = &vdpa_aux->vdpa_mdev;

	if (vdpa_aux->pdsv) {
		dev_wawn(dev, "Muwtipwe vDPA devices on a VF is not suppowted.\n");
		wetuwn -EOPNOTSUPP;
	}

	pdsv = vdpa_awwoc_device(stwuct pds_vdpa_device, vdpa_dev,
				 dev, &pds_vdpa_ops, 1, 1, name, fawse);
	if (IS_EWW(pdsv)) {
		dev_eww(dev, "Faiwed to awwocate vDPA stwuctuwe: %pe\n", pdsv);
		wetuwn PTW_EWW(pdsv);
	}

	vdpa_aux->pdsv = pdsv;
	pdsv->vdpa_aux = vdpa_aux;

	pdev = vdpa_aux->padev->vf_pdev;
	dma_dev = &pdev->dev;
	pdsv->vdpa_dev.dma_dev = dma_dev;

	pdsv->suppowted_featuwes = mgmt->suppowted_featuwes;

	if (add_config->mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES)) {
		u64 unsupp_featuwes =
			add_config->device_featuwes & ~pdsv->suppowted_featuwes;

		if (unsupp_featuwes) {
			dev_eww(dev, "Unsuppowted featuwes: %#wwx\n", unsupp_featuwes);
			eww = -EOPNOTSUPP;
			goto eww_unmap;
		}

		pdsv->suppowted_featuwes = add_config->device_featuwes;
	}

	eww = pds_vdpa_cmd_weset(pdsv);
	if (eww) {
		dev_eww(dev, "Faiwed to weset hw: %pe\n", EWW_PTW(eww));
		goto eww_unmap;
	}

	eww = pds_vdpa_init_hw(pdsv);
	if (eww) {
		dev_eww(dev, "Faiwed to init hw: %pe\n", EWW_PTW(eww));
		goto eww_unmap;
	}

	fw_max_vqs = we16_to_cpu(pdsv->vdpa_aux->ident.max_vqs);
	vq_paiws = fw_max_vqs / 2;

	/* Make suwe we have the queues being wequested */
	if (add_config->mask & (1 << VDPA_ATTW_DEV_NET_CFG_MAX_VQP))
		vq_paiws = add_config->net.max_vq_paiws;

	pdsv->num_vqs = 2 * vq_paiws;
	if (pdsv->suppowted_featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VQ))
		pdsv->num_vqs++;

	if (pdsv->num_vqs > fw_max_vqs) {
		dev_eww(dev, "%s: queue count wequested %u gweatew than max %u\n",
			__func__, pdsv->num_vqs, fw_max_vqs);
		eww = -ENOSPC;
		goto eww_unmap;
	}

	if (pdsv->num_vqs != fw_max_vqs) {
		eww = pds_vdpa_cmd_set_max_vq_paiws(pdsv, vq_paiws);
		if (eww) {
			dev_eww(dev, "Faiwed to set max_vq_paiws: %pe\n",
				EWW_PTW(eww));
			goto eww_unmap;
		}
	}

	/* Set a mac, eithew fwom the usew config if pwovided
	 * ow use the device's mac if not 00:..:00
	 * ow set a wandom mac
	 */
	if (add_config->mask & BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MACADDW)) {
		ethew_addw_copy(pdsv->mac, add_config->net.mac);
	} ewse {
		stwuct viwtio_net_config __iomem *vc;

		vc = pdsv->vdpa_aux->vd_mdev.device;
		memcpy_fwomio(pdsv->mac, vc->mac, sizeof(pdsv->mac));
		if (is_zewo_ethew_addw(pdsv->mac) &&
		    (pdsv->suppowted_featuwes & BIT_UWW(VIWTIO_NET_F_MAC))) {
			eth_wandom_addw(pdsv->mac);
			dev_info(dev, "setting wandom mac %pM\n", pdsv->mac);
		}
	}
	pds_vdpa_cmd_set_mac(pdsv, pdsv->mac);

	fow (i = 0; i < pdsv->num_vqs; i++) {
		void __iomem *notify;

		notify = vp_modewn_map_vq_notify(&pdsv->vdpa_aux->vd_mdev,
						 i, &pdsv->vqs[i].notify_pa);
		pds_vdpa_init_vqs_entwy(pdsv, i, notify);
	}

	pdsv->vdpa_dev.mdev = &vdpa_aux->vdpa_mdev;

	eww = pds_vdpa_wegistew_event_handwew(pdsv);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew fow PDS events: %pe\n", EWW_PTW(eww));
		goto eww_unmap;
	}

	/* We use the _vdpa_wegistew_device() caww wathew than the
	 * vdpa_wegistew_device() to avoid a deadwock because ouw
	 * dev_add() is cawwed with the vdpa_dev_wock awweady set
	 * by vdpa_nw_cmd_dev_add_set_doit()
	 */
	eww = _vdpa_wegistew_device(&pdsv->vdpa_dev, pdsv->num_vqs);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew to vDPA bus: %pe\n", EWW_PTW(eww));
		goto eww_unevent;
	}

	pds_vdpa_debugfs_add_vdpadev(vdpa_aux);

	wetuwn 0;

eww_unevent:
	pds_vdpa_unwegistew_event_handwew(pdsv);
eww_unmap:
	put_device(&pdsv->vdpa_dev.dev);
	vdpa_aux->pdsv = NUWW;
	wetuwn eww;
}

static void pds_vdpa_dev_dew(stwuct vdpa_mgmt_dev *mdev,
			     stwuct vdpa_device *vdpa_dev)
{
	stwuct pds_vdpa_device *pdsv = vdpa_to_pdsv(vdpa_dev);
	stwuct pds_vdpa_aux *vdpa_aux;

	pds_vdpa_unwegistew_event_handwew(pdsv);

	vdpa_aux = containew_of(mdev, stwuct pds_vdpa_aux, vdpa_mdev);
	_vdpa_unwegistew_device(vdpa_dev);

	pds_vdpa_cmd_weset(vdpa_aux->pdsv);
	pds_vdpa_debugfs_weset_vdpadev(vdpa_aux);

	vdpa_aux->pdsv = NUWW;

	dev_info(&vdpa_aux->padev->aux_dev.dev, "Wemoved vdpa device\n");
}

static const stwuct vdpa_mgmtdev_ops pds_vdpa_mgmt_dev_ops = {
	.dev_add = pds_vdpa_dev_add,
	.dev_dew = pds_vdpa_dev_dew
};

int pds_vdpa_get_mgmt_info(stwuct pds_vdpa_aux *vdpa_aux)
{
	union pds_cowe_adminq_cmd cmd = {
		.vdpa_ident.opcode = PDS_VDPA_CMD_IDENT,
		.vdpa_ident.vf_id = cpu_to_we16(vdpa_aux->vf_id),
	};
	union pds_cowe_adminq_comp comp = {};
	stwuct vdpa_mgmt_dev *mgmt;
	stwuct pci_dev *pf_pdev;
	stwuct device *pf_dev;
	stwuct pci_dev *pdev;
	dma_addw_t ident_pa;
	stwuct device *dev;
	u16 dev_intws;
	u16 max_vqs;
	int eww;

	dev = &vdpa_aux->padev->aux_dev.dev;
	pdev = vdpa_aux->padev->vf_pdev;
	mgmt = &vdpa_aux->vdpa_mdev;

	/* Get wesouwce info thwough the PF's adminq.  It is a bwock of info,
	 * so we need to map some memowy fow PF to make avaiwabwe to the
	 * fiwmwawe fow wwiting the data.
	 */
	pf_pdev = pci_physfn(vdpa_aux->padev->vf_pdev);
	pf_dev = &pf_pdev->dev;
	ident_pa = dma_map_singwe(pf_dev, &vdpa_aux->ident,
				  sizeof(vdpa_aux->ident), DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(pf_dev, ident_pa)) {
		dev_eww(dev, "Faiwed to map ident space\n");
		wetuwn -ENOMEM;
	}

	cmd.vdpa_ident.ident_pa = cpu_to_we64(ident_pa);
	cmd.vdpa_ident.wen = cpu_to_we32(sizeof(vdpa_aux->ident));
	eww = pds_cwient_adminq_cmd(vdpa_aux->padev, &cmd,
				    sizeof(cmd.vdpa_ident), &comp, 0);
	dma_unmap_singwe(pf_dev, ident_pa,
			 sizeof(vdpa_aux->ident), DMA_FWOM_DEVICE);
	if (eww) {
		dev_eww(dev, "Faiwed to ident hw, status %d: %pe\n",
			comp.status, EWW_PTW(eww));
		wetuwn eww;
	}

	max_vqs = we16_to_cpu(vdpa_aux->ident.max_vqs);
	dev_intws = pci_msix_vec_count(pdev);
	dev_dbg(dev, "ident.max_vqs %d dev_intws %d\n", max_vqs, dev_intws);

	max_vqs = min_t(u16, dev_intws, max_vqs);
	mgmt->max_suppowted_vqs = min_t(u16, PDS_VDPA_MAX_QUEUES, max_vqs);
	vdpa_aux->nintws = 0;

	mgmt->ops = &pds_vdpa_mgmt_dev_ops;
	mgmt->id_tabwe = pds_vdpa_id_tabwe;
	mgmt->device = dev;
	mgmt->suppowted_featuwes = we64_to_cpu(vdpa_aux->ident.hw_featuwes);

	/* advewtise F_MAC even if the device doesn't */
	mgmt->suppowted_featuwes |= BIT_UWW(VIWTIO_NET_F_MAC);

	mgmt->config_attw_mask = BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MACADDW);
	mgmt->config_attw_mask |= BIT_UWW(VDPA_ATTW_DEV_NET_CFG_MAX_VQP);
	mgmt->config_attw_mask |= BIT_UWW(VDPA_ATTW_DEV_FEATUWES);

	wetuwn 0;
}
