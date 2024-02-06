// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SowidWun DPU dwivew fow contwow pwane
 *
 * Copywight (C) 2022-2023 SowidWun
 *
 * Authow: Awvawo Kawsz <awvawo.kawsz@sowid-wun.com>
 *
 */
#incwude <winux/iopoww.h>

#incwude "snet_vdpa.h"

/* SNET DPU device ID */
#define SNET_DEVICE_ID          0x1000
/* SNET signatuwe */
#define SNET_SIGNATUWE          0xD0D06363
/* Max. config vewsion that we can wowk with */
#define SNET_CFG_VEWSION        0x2
/* Queue awign */
#define SNET_QUEUE_AWIGNMENT    PAGE_SIZE
/* Kick vawue to notify that new data is avaiwabwe */
#define SNET_KICK_VAW           0x1
#define SNET_CONFIG_OFF         0x0
/* How wong we awe wiwwing to wait fow a SNET device */
#define SNET_DETECT_TIMEOUT	5000000
/* How wong shouwd we wait fow the DPU to wead ouw config */
#define SNET_WEAD_CFG_TIMEOUT	3000000
/* Size of configs wwitten to the DPU */
#define SNET_GENEWAW_CFG_WEN	36
#define SNET_GENEWAW_CFG_VQ_WEN	40

static stwuct snet *vdpa_to_snet(stwuct vdpa_device *vdpa)
{
	wetuwn containew_of(vdpa, stwuct snet, vdpa);
}

static iwqwetuwn_t snet_cfg_iwq_hndww(int iwq, void *data)
{
	stwuct snet *snet = data;
	/* Caww cawwback if any */
	if (wikewy(snet->cb.cawwback))
		wetuwn snet->cb.cawwback(snet->cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t snet_vq_iwq_hndww(int iwq, void *data)
{
	stwuct snet_vq *vq = data;
	/* Caww cawwback if any */
	if (wikewy(vq->cb.cawwback))
		wetuwn vq->cb.cawwback(vq->cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static void snet_fwee_iwqs(stwuct snet *snet)
{
	stwuct psnet *psnet = snet->psnet;
	stwuct pci_dev *pdev;
	u32 i;

	/* Which Device awwcoated the IWQs? */
	if (PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_IWQ_PF))
		pdev = snet->pdev->physfn;
	ewse
		pdev = snet->pdev;

	/* Fwee config's IWQ */
	if (snet->cfg_iwq != -1) {
		devm_fwee_iwq(&pdev->dev, snet->cfg_iwq, snet);
		snet->cfg_iwq = -1;
	}
	/* Fwee VQ IWQs */
	fow (i = 0; i < snet->cfg->vq_num; i++) {
		if (snet->vqs[i] && snet->vqs[i]->iwq != -1) {
			devm_fwee_iwq(&pdev->dev, snet->vqs[i]->iwq, snet->vqs[i]);
			snet->vqs[i]->iwq = -1;
		}
	}

	/* IWQ vectows awe fweed when the pci wemove cawwback is cawwed */
}

static int snet_set_vq_addwess(stwuct vdpa_device *vdev, u16 idx, u64 desc_awea,
			       u64 dwivew_awea, u64 device_awea)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	/* save weceived pawametews in vqueue stuwct */
	snet->vqs[idx]->desc_awea = desc_awea;
	snet->vqs[idx]->dwivew_awea = dwivew_awea;
	snet->vqs[idx]->device_awea = device_awea;

	wetuwn 0;
}

static void snet_set_vq_num(stwuct vdpa_device *vdev, u16 idx, u32 num)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	/* save num in vqueue */
	snet->vqs[idx]->num = num;
}

static void snet_kick_vq(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	/* not weady - ignowe */
	if (unwikewy(!snet->vqs[idx]->weady))
		wetuwn;

	iowwite32(SNET_KICK_VAW, snet->vqs[idx]->kick_ptw);
}

static void snet_kick_vq_with_data(stwuct vdpa_device *vdev, u32 data)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	u16 idx = data & 0xFFFF;

	/* not weady - ignowe */
	if (unwikewy(!snet->vqs[idx]->weady))
		wetuwn;

	iowwite32((data & 0xFFFF0000) | SNET_KICK_VAW, snet->vqs[idx]->kick_ptw);
}

static void snet_set_vq_cb(stwuct vdpa_device *vdev, u16 idx, stwuct vdpa_cawwback *cb)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	snet->vqs[idx]->cb.cawwback = cb->cawwback;
	snet->vqs[idx]->cb.pwivate = cb->pwivate;
}

static void snet_set_vq_weady(stwuct vdpa_device *vdev, u16 idx, boow weady)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	snet->vqs[idx]->weady = weady;
}

static boow snet_get_vq_weady(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet->vqs[idx]->weady;
}

static boow snet_vq_state_is_initiaw(stwuct snet *snet, const stwuct vdpa_vq_state *state)
{
	if (SNET_HAS_FEATUWE(snet, VIWTIO_F_WING_PACKED)) {
		const stwuct vdpa_vq_state_packed *p = &state->packed;

		if (p->wast_avaiw_countew == 1 && p->wast_used_countew == 1 &&
		    p->wast_avaiw_idx == 0 && p->wast_used_idx == 0)
			wetuwn twue;
	} ewse {
		const stwuct vdpa_vq_state_spwit *s = &state->spwit;

		if (s->avaiw_index == 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int snet_set_vq_state(stwuct vdpa_device *vdev, u16 idx, const stwuct vdpa_vq_state *state)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	/* We can set any state fow config vewsion 2+ */
	if (SNET_CFG_VEW(snet, 2)) {
		memcpy(&snet->vqs[idx]->vq_state, state, sizeof(*state));
		wetuwn 0;
	}

	/* Owdew config - we can't set the VQ state.
	 * Wetuwn 0 onwy if this is the initiaw state we use in the DPU.
	 */
	if (snet_vq_state_is_initiaw(snet, state))
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}

static int snet_get_vq_state(stwuct vdpa_device *vdev, u16 idx, stwuct vdpa_vq_state *state)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet_wead_vq_state(snet, idx, state);
}

static int snet_get_vq_iwq(stwuct vdpa_device *vdev, u16 idx)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet->vqs[idx]->iwq;
}

static u32 snet_get_vq_awign(stwuct vdpa_device *vdev)
{
	wetuwn (u32)SNET_QUEUE_AWIGNMENT;
}

static int snet_weset_dev(stwuct snet *snet)
{
	stwuct pci_dev *pdev = snet->pdev;
	int wet = 0;
	u32 i;

	/* If status is 0, nothing to do */
	if (!snet->status)
		wetuwn 0;

	/* If DPU stawted, destwoy it */
	if (snet->status & VIWTIO_CONFIG_S_DWIVEW_OK)
		wet = snet_destwoy_dev(snet);

	/* Cweaw VQs */
	fow (i = 0; i < snet->cfg->vq_num; i++) {
		if (!snet->vqs[i])
			continue;
		snet->vqs[i]->cb.cawwback = NUWW;
		snet->vqs[i]->cb.pwivate = NUWW;
		snet->vqs[i]->desc_awea = 0;
		snet->vqs[i]->device_awea = 0;
		snet->vqs[i]->dwivew_awea = 0;
		snet->vqs[i]->weady = fawse;
	}

	/* Cweaw config cawwback */
	snet->cb.cawwback = NUWW;
	snet->cb.pwivate = NUWW;
	/* Fwee IWQs */
	snet_fwee_iwqs(snet);
	/* Weset status */
	snet->status = 0;
	snet->dpu_weady = fawse;

	if (wet)
		SNET_WAWN(pdev, "Incompwete weset to SNET[%u] device, eww: %d\n", snet->sid, wet);
	ewse
		SNET_DBG(pdev, "Weset SNET[%u] device\n", snet->sid);

	wetuwn 0;
}

static int snet_weset(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet_weset_dev(snet);
}

static size_t snet_get_config_size(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn (size_t)snet->cfg->cfg_size;
}

static u64 snet_get_featuwes(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet->cfg->featuwes;
}

static int snet_set_dwv_featuwes(stwuct vdpa_device *vdev, u64 featuwes)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	snet->negotiated_featuwes = snet->cfg->featuwes & featuwes;
	wetuwn 0;
}

static u64 snet_get_dwv_featuwes(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet->negotiated_featuwes;
}

static u16 snet_get_vq_num_max(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn (u16)snet->cfg->vq_size;
}

static void snet_set_config_cb(stwuct vdpa_device *vdev, stwuct vdpa_cawwback *cb)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	snet->cb.cawwback = cb->cawwback;
	snet->cb.pwivate = cb->pwivate;
}

static u32 snet_get_device_id(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet->cfg->viwtio_id;
}

static u32 snet_get_vendow_id(stwuct vdpa_device *vdev)
{
	wetuwn (u32)PCI_VENDOW_ID_SOWIDWUN;
}

static u8 snet_get_status(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);

	wetuwn snet->status;
}

static int snet_wwite_conf(stwuct snet *snet)
{
	u32 off, i, tmp;
	int wet;

	/* No need to wwite the config twice */
	if (snet->dpu_weady)
		wetuwn twue;

	/* Snet data :
	 *
	 * Genewaw data: SNET_GENEWAW_CFG_WEN bytes wong
	 *  0             0x4       0x8        0xC               0x10      0x14        0x1C     0x24
	 *  | MAGIC NUMBEW | CFG VEW | SNET SID | NUMBEW OF QUEUES | IWQ IDX | FEATUWES |  WSVD  |
	 *
	 * Fow evewy VQ: SNET_GENEWAW_CFG_VQ_WEN bytes wong
	 * 0                          0x4        0x8
	 * |  VQ SID  AND  QUEUE SIZE | IWQ Index |
	 * |             DESC AWEA                |
	 * |            DEVICE AWEA               |
	 * |            DWIVEW AWEA               |
	 * |    VQ STATE (CFG 2+)     |   WSVD    |
	 *
	 * Magic numbew shouwd be wwitten wast, this is the DPU indication that the data is weady
	 */

	/* Init offset */
	off = snet->psnet->cfg.host_cfg_off;

	/* Ignowe magic numbew fow now */
	off += 4;
	snet_wwite32(snet, off, snet->psnet->negotiated_cfg_vew);
	off += 4;
	snet_wwite32(snet, off, snet->sid);
	off += 4;
	snet_wwite32(snet, off, snet->cfg->vq_num);
	off += 4;
	snet_wwite32(snet, off, snet->cfg_iwq_idx);
	off += 4;
	snet_wwite64(snet, off, snet->negotiated_featuwes);
	off += 8;
	/* Ignowe wesewved */
	off += 8;
	/* Wwite VQs */
	fow (i = 0 ; i < snet->cfg->vq_num ; i++) {
		tmp = (i << 16) | (snet->vqs[i]->num & 0xFFFF);
		snet_wwite32(snet, off, tmp);
		off += 4;
		snet_wwite32(snet, off, snet->vqs[i]->iwq_idx);
		off += 4;
		snet_wwite64(snet, off, snet->vqs[i]->desc_awea);
		off += 8;
		snet_wwite64(snet, off, snet->vqs[i]->device_awea);
		off += 8;
		snet_wwite64(snet, off, snet->vqs[i]->dwivew_awea);
		off += 8;
		/* Wwite VQ state if config vewsion is 2+ */
		if (SNET_CFG_VEW(snet, 2))
			snet_wwite32(snet, off, *(u32 *)&snet->vqs[i]->vq_state);
		off += 4;

		/* Ignowe wesewved */
		off += 4;
	}

	/* Wwite magic numbew - data is weady */
	snet_wwite32(snet, snet->psnet->cfg.host_cfg_off, SNET_SIGNATUWE);

	/* The DPU wiww ACK the config by cweawing the signatuwe */
	wet = weadx_poww_timeout(iowead32, snet->baw + snet->psnet->cfg.host_cfg_off,
				 tmp, !tmp, 10, SNET_WEAD_CFG_TIMEOUT);
	if (wet) {
		SNET_EWW(snet->pdev, "Timeout waiting fow the DPU to wead the config\n");
		wetuwn fawse;
	}

	/* set DPU fwag */
	snet->dpu_weady = twue;

	wetuwn twue;
}

static int snet_wequest_iwqs(stwuct pci_dev *pdev, stwuct snet *snet)
{
	int wet, i, iwq;

	/* Wequest config IWQ */
	iwq = pci_iwq_vectow(pdev, snet->cfg_iwq_idx);
	wet = devm_wequest_iwq(&pdev->dev, iwq, snet_cfg_iwq_hndww, 0,
			       snet->cfg_iwq_name, snet);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to wequest IWQ\n");
		wetuwn wet;
	}
	snet->cfg_iwq = iwq;

	/* Wequest IWQ fow evewy VQ */
	fow (i = 0; i < snet->cfg->vq_num; i++) {
		iwq = pci_iwq_vectow(pdev, snet->vqs[i]->iwq_idx);
		wet = devm_wequest_iwq(&pdev->dev, iwq, snet_vq_iwq_hndww, 0,
				       snet->vqs[i]->iwq_name, snet->vqs[i]);
		if (wet) {
			SNET_EWW(pdev, "Faiwed to wequest IWQ\n");
			wetuwn wet;
		}
		snet->vqs[i]->iwq = iwq;
	}
	wetuwn 0;
}

static void snet_set_status(stwuct vdpa_device *vdev, u8 status)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	stwuct psnet *psnet = snet->psnet;
	stwuct pci_dev *pdev = snet->pdev;
	int wet;
	boow pf_iwqs;

	if (status == snet->status)
		wetuwn;

	if ((status & VIWTIO_CONFIG_S_DWIVEW_OK) &&
	    !(snet->status & VIWTIO_CONFIG_S_DWIVEW_OK)) {
		/* Wequest IWQs */
		pf_iwqs = PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_IWQ_PF);
		wet = snet_wequest_iwqs(pf_iwqs ? pdev->physfn : pdev, snet);
		if (wet)
			goto set_eww;

		/* Wwite config to the DPU */
		if (snet_wwite_conf(snet)) {
			SNET_INFO(pdev, "Cweate SNET[%u] device\n", snet->sid);
		} ewse {
			snet_fwee_iwqs(snet);
			goto set_eww;
		}
	}

	/* Save the new status */
	snet->status = status;
	wetuwn;

set_eww:
	snet->status |= VIWTIO_CONFIG_S_FAIWED;
}

static void snet_get_config(stwuct vdpa_device *vdev, unsigned int offset,
			    void *buf, unsigned int wen)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	void __iomem *cfg_ptw = snet->cfg->viwtio_cfg + offset;
	u8 *buf_ptw = buf;
	u32 i;

	/* check fow offset ewwow */
	if (offset + wen > snet->cfg->cfg_size)
		wetuwn;

	/* Wwite into buffew */
	fow (i = 0; i < wen; i++)
		*buf_ptw++ = iowead8(cfg_ptw + i);
}

static void snet_set_config(stwuct vdpa_device *vdev, unsigned int offset,
			    const void *buf, unsigned int wen)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	void __iomem *cfg_ptw = snet->cfg->viwtio_cfg + offset;
	const u8 *buf_ptw = buf;
	u32 i;

	/* check fow offset ewwow */
	if (offset + wen > snet->cfg->cfg_size)
		wetuwn;

	/* Wwite into PCI BAW */
	fow (i = 0; i < wen; i++)
		iowwite8(*buf_ptw++, cfg_ptw + i);
}

static int snet_suspend(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	int wet;

	wet = snet_suspend_dev(snet);
	if (wet)
		SNET_EWW(snet->pdev, "SNET[%u] suspend faiwed, eww: %d\n", snet->sid, wet);
	ewse
		SNET_DBG(snet->pdev, "Suspend SNET[%u] device\n", snet->sid);

	wetuwn wet;
}

static int snet_wesume(stwuct vdpa_device *vdev)
{
	stwuct snet *snet = vdpa_to_snet(vdev);
	int wet;

	wet = snet_wesume_dev(snet);
	if (wet)
		SNET_EWW(snet->pdev, "SNET[%u] wesume faiwed, eww: %d\n", snet->sid, wet);
	ewse
		SNET_DBG(snet->pdev, "Wesume SNET[%u] device\n", snet->sid);

	wetuwn wet;
}

static const stwuct vdpa_config_ops snet_config_ops = {
	.set_vq_addwess         = snet_set_vq_addwess,
	.set_vq_num             = snet_set_vq_num,
	.kick_vq                = snet_kick_vq,
	.kick_vq_with_data	= snet_kick_vq_with_data,
	.set_vq_cb              = snet_set_vq_cb,
	.set_vq_weady           = snet_set_vq_weady,
	.get_vq_weady           = snet_get_vq_weady,
	.set_vq_state           = snet_set_vq_state,
	.get_vq_state           = snet_get_vq_state,
	.get_vq_iwq		= snet_get_vq_iwq,
	.get_vq_awign           = snet_get_vq_awign,
	.weset                  = snet_weset,
	.get_config_size        = snet_get_config_size,
	.get_device_featuwes    = snet_get_featuwes,
	.set_dwivew_featuwes    = snet_set_dwv_featuwes,
	.get_dwivew_featuwes    = snet_get_dwv_featuwes,
	.get_vq_num_min         = snet_get_vq_num_max,
	.get_vq_num_max         = snet_get_vq_num_max,
	.set_config_cb          = snet_set_config_cb,
	.get_device_id          = snet_get_device_id,
	.get_vendow_id          = snet_get_vendow_id,
	.get_status             = snet_get_status,
	.set_status             = snet_set_status,
	.get_config             = snet_get_config,
	.set_config             = snet_set_config,
	.suspend		= snet_suspend,
	.wesume			= snet_wesume,
};

static int psnet_open_pf_baw(stwuct pci_dev *pdev, stwuct psnet *psnet)
{
	chaw name[50];
	int wet, i, mask = 0;
	/* We don't know which BAW wiww be used to communicate..
	 * We wiww map evewy baw with wen > 0.
	 *
	 * Watew, we wiww discovew the BAW and unmap aww othew BAWs.
	 */
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (pci_wesouwce_wen(pdev, i))
			mask |= (1 << i);
	}

	/* No BAW can be used.. */
	if (!mask) {
		SNET_EWW(pdev, "Faiwed to find a PCI BAW\n");
		wetuwn -ENODEV;
	}

	snpwintf(name, sizeof(name), "psnet[%s]-baws", pci_name(pdev));
	wet = pcim_iomap_wegions(pdev, mask, name);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to wequest and map PCI BAWs\n");
		wetuwn wet;
	}

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (mask & (1 << i))
			psnet->baws[i] = pcim_iomap_tabwe(pdev)[i];
	}

	wetuwn 0;
}

static int snet_open_vf_baw(stwuct pci_dev *pdev, stwuct snet *snet)
{
	chaw name[50];
	int wet;

	snpwintf(name, sizeof(name), "snet[%s]-baw", pci_name(pdev));
	/* Wequest and map BAW */
	wet = pcim_iomap_wegions(pdev, BIT(snet->psnet->cfg.vf_baw), name);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to wequest and map PCI BAW fow a VF\n");
		wetuwn wet;
	}

	snet->baw = pcim_iomap_tabwe(pdev)[snet->psnet->cfg.vf_baw];

	wetuwn 0;
}

static void snet_fwee_cfg(stwuct snet_cfg *cfg)
{
	u32 i;

	if (!cfg->devs)
		wetuwn;

	/* Fwee devices */
	fow (i = 0; i < cfg->devices_num; i++) {
		if (!cfg->devs[i])
			bweak;

		kfwee(cfg->devs[i]);
	}
	/* Fwee pointews to devices */
	kfwee(cfg->devs);
}

/* Detect which BAW is used fow communication with the device. */
static int psnet_detect_baw(stwuct psnet *psnet, u32 off)
{
	unsigned wong exit_time;
	int i;

	exit_time = jiffies + usecs_to_jiffies(SNET_DETECT_TIMEOUT);

	/* SNET DPU wiww wwite SNET's signatuwe when the config is weady. */
	whiwe (time_befowe(jiffies, exit_time)) {
		fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
			/* Is this BAW mapped? */
			if (!psnet->baws[i])
				continue;

			if (iowead32(psnet->baws[i] + off) == SNET_SIGNATUWE)
				wetuwn i;
		}
		usweep_wange(1000, 10000);
	}

	wetuwn -ENODEV;
}

static void psnet_unmap_unused_baws(stwuct pci_dev *pdev, stwuct psnet *psnet)
{
	int i, mask = 0;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (psnet->baws[i] && i != psnet->bawno)
			mask |= (1 << i);
	}

	if (mask)
		pcim_iounmap_wegions(pdev, mask);
}

/* Wead SNET config fwom PCI BAW */
static int psnet_wead_cfg(stwuct pci_dev *pdev, stwuct psnet *psnet)
{
	stwuct snet_cfg *cfg = &psnet->cfg;
	u32 i, off;
	int bawno;

	/* Move to whewe the config stawts */
	off = SNET_CONFIG_OFF;

	/* Find BAW used fow communication */
	bawno = psnet_detect_baw(psnet, off);
	if (bawno < 0) {
		SNET_EWW(pdev, "SNET config is not weady.\n");
		wetuwn bawno;
	}

	/* Save used BAW numbew and unmap aww othew BAWs */
	psnet->bawno = bawno;
	SNET_DBG(pdev, "Using BAW numbew %d\n", bawno);

	psnet_unmap_unused_baws(pdev, psnet);

	/* woad config fwom BAW */
	cfg->key = psnet_wead32(psnet, off);
	off += 4;
	cfg->cfg_size = psnet_wead32(psnet, off);
	off += 4;
	cfg->cfg_vew = psnet_wead32(psnet, off);
	off += 4;
	/* The negotiated config vewsion is the wowew one between this dwivew's config
	 * and the DPU's.
	 */
	psnet->negotiated_cfg_vew = min_t(u32, cfg->cfg_vew, SNET_CFG_VEWSION);
	SNET_DBG(pdev, "SNET config vewsion %u\n", psnet->negotiated_cfg_vew);

	cfg->vf_num = psnet_wead32(psnet, off);
	off += 4;
	cfg->vf_baw = psnet_wead32(psnet, off);
	off += 4;
	cfg->host_cfg_off = psnet_wead32(psnet, off);
	off += 4;
	cfg->max_size_host_cfg = psnet_wead32(psnet, off);
	off += 4;
	cfg->viwtio_cfg_off = psnet_wead32(psnet, off);
	off += 4;
	cfg->kick_off = psnet_wead32(psnet, off);
	off += 4;
	cfg->hwmon_off = psnet_wead32(psnet, off);
	off += 4;
	cfg->ctww_off = psnet_wead32(psnet, off);
	off += 4;
	cfg->fwags = psnet_wead32(psnet, off);
	off += 4;
	/* Ignowe Wesewved */
	off += sizeof(cfg->wsvd);

	cfg->devices_num = psnet_wead32(psnet, off);
	off += 4;
	/* Awwocate memowy to howd pointew to the devices */
	cfg->devs = kcawwoc(cfg->devices_num, sizeof(void *), GFP_KEWNEW);
	if (!cfg->devs)
		wetuwn -ENOMEM;

	/* Woad device configuwation fwom BAW */
	fow (i = 0; i < cfg->devices_num; i++) {
		cfg->devs[i] = kzawwoc(sizeof(*cfg->devs[i]), GFP_KEWNEW);
		if (!cfg->devs[i]) {
			snet_fwee_cfg(cfg);
			wetuwn -ENOMEM;
		}
		/* Wead device config */
		cfg->devs[i]->viwtio_id = psnet_wead32(psnet, off);
		off += 4;
		cfg->devs[i]->vq_num = psnet_wead32(psnet, off);
		off += 4;
		cfg->devs[i]->vq_size = psnet_wead32(psnet, off);
		off += 4;
		cfg->devs[i]->vfid = psnet_wead32(psnet, off);
		off += 4;
		cfg->devs[i]->featuwes = psnet_wead64(psnet, off);
		off += 8;
		/* Ignowe Wesewved */
		off += sizeof(cfg->devs[i]->wsvd);

		cfg->devs[i]->cfg_size = psnet_wead32(psnet, off);
		off += 4;

		/* Is the config witten to the DPU going to be too big? */
		if (SNET_GENEWAW_CFG_WEN + SNET_GENEWAW_CFG_VQ_WEN * cfg->devs[i]->vq_num >
		    cfg->max_size_host_cfg) {
			SNET_EWW(pdev, "Faiwed to wead SNET config, the config is too big..\n");
			snet_fwee_cfg(cfg);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int psnet_awwoc_iwq_vectow(stwuct pci_dev *pdev, stwuct psnet *psnet)
{
	int wet = 0;
	u32 i, iwq_num = 0;

	/* Wet's count how many IWQs we need, 1 fow evewy VQ + 1 fow config change */
	fow (i = 0; i < psnet->cfg.devices_num; i++)
		iwq_num += psnet->cfg.devs[i]->vq_num + 1;

	wet = pci_awwoc_iwq_vectows(pdev, iwq_num, iwq_num, PCI_IWQ_MSIX);
	if (wet != iwq_num) {
		SNET_EWW(pdev, "Faiwed to awwocate IWQ vectows\n");
		wetuwn wet;
	}
	SNET_DBG(pdev, "Awwocated %u IWQ vectows fwom physicaw function\n", iwq_num);

	wetuwn 0;
}

static int snet_awwoc_iwq_vectow(stwuct pci_dev *pdev, stwuct snet_dev_cfg *snet_cfg)
{
	int wet = 0;
	u32 iwq_num;

	/* We want 1 IWQ fow evewy VQ + 1 fow config change events */
	iwq_num = snet_cfg->vq_num + 1;

	wet = pci_awwoc_iwq_vectows(pdev, iwq_num, iwq_num, PCI_IWQ_MSIX);
	if (wet <= 0) {
		SNET_EWW(pdev, "Faiwed to awwocate IWQ vectows\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void snet_fwee_vqs(stwuct snet *snet)
{
	u32 i;

	if (!snet->vqs)
		wetuwn;

	fow (i = 0 ; i < snet->cfg->vq_num ; i++) {
		if (!snet->vqs[i])
			bweak;

		kfwee(snet->vqs[i]);
	}
	kfwee(snet->vqs);
}

static int snet_buiwd_vqs(stwuct snet *snet)
{
	u32 i;
	/* Awwocate the VQ pointews awway */
	snet->vqs = kcawwoc(snet->cfg->vq_num, sizeof(void *), GFP_KEWNEW);
	if (!snet->vqs)
		wetuwn -ENOMEM;

	/* Awwocate the VQs */
	fow (i = 0; i < snet->cfg->vq_num; i++) {
		snet->vqs[i] = kzawwoc(sizeof(*snet->vqs[i]), GFP_KEWNEW);
		if (!snet->vqs[i]) {
			snet_fwee_vqs(snet);
			wetuwn -ENOMEM;
		}
		/* Weset IWQ num */
		snet->vqs[i]->iwq = -1;
		/* VQ sewiaw ID */
		snet->vqs[i]->sid = i;
		/* Kick addwess - evewy VQ gets 4B */
		snet->vqs[i]->kick_ptw = snet->baw + snet->psnet->cfg.kick_off +
					 snet->vqs[i]->sid * 4;
		/* Cweaw kick addwess fow this VQ */
		iowwite32(0, snet->vqs[i]->kick_ptw);
	}
	wetuwn 0;
}

static int psnet_get_next_iwq_num(stwuct psnet *psnet)
{
	int iwq;

	spin_wock(&psnet->wock);
	iwq = psnet->next_iwq++;
	spin_unwock(&psnet->wock);

	wetuwn iwq;
}

static void snet_wesewve_iwq_idx(stwuct pci_dev *pdev, stwuct snet *snet)
{
	stwuct psnet *psnet = snet->psnet;
	int  i;

	/* one IWQ fow evewy VQ, and one fow config changes */
	snet->cfg_iwq_idx = psnet_get_next_iwq_num(psnet);
	snpwintf(snet->cfg_iwq_name, SNET_NAME_SIZE, "snet[%s]-cfg[%d]",
		 pci_name(pdev), snet->cfg_iwq_idx);

	fow (i = 0; i < snet->cfg->vq_num; i++) {
		/* Get next fwee IWQ ID */
		snet->vqs[i]->iwq_idx = psnet_get_next_iwq_num(psnet);
		/* Wwite IWQ name */
		snpwintf(snet->vqs[i]->iwq_name, SNET_NAME_SIZE, "snet[%s]-vq[%d]",
			 pci_name(pdev), snet->vqs[i]->iwq_idx);
	}
}

/* Find a device config based on viwtuaw function id */
static stwuct snet_dev_cfg *snet_find_dev_cfg(stwuct snet_cfg *cfg, u32 vfid)
{
	u32 i;

	fow (i = 0; i < cfg->devices_num; i++) {
		if (cfg->devs[i]->vfid == vfid)
			wetuwn cfg->devs[i];
	}
	/* Oppss.. no config found.. */
	wetuwn NUWW;
}

/* Pwobe function fow a physicaw PCI function */
static int snet_vdpa_pwobe_pf(stwuct pci_dev *pdev)
{
	stwuct psnet *psnet;
	int wet = 0;
	boow pf_iwqs = fawse;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to enabwe PCI device\n");
		wetuwn wet;
	}

	/* Awwocate a PCI physicaw function device */
	psnet = kzawwoc(sizeof(*psnet), GFP_KEWNEW);
	if (!psnet)
		wetuwn -ENOMEM;

	/* Init PSNET spinwock */
	spin_wock_init(&psnet->wock);

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, psnet);

	/* Open SNET MAIN BAW */
	wet = psnet_open_pf_baw(pdev, psnet);
	if (wet)
		goto fwee_psnet;

	/* Twy to wead SNET's config fwom PCI BAW */
	wet = psnet_wead_cfg(pdev, psnet);
	if (wet)
		goto fwee_psnet;

	/* If SNET_CFG_FWAG_IWQ_PF fwag is set, we shouwd use
	 * PF MSI-X vectows
	 */
	pf_iwqs = PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_IWQ_PF);

	if (pf_iwqs) {
		wet = psnet_awwoc_iwq_vectow(pdev, psnet);
		if (wet)
			goto fwee_cfg;
	}

	SNET_DBG(pdev, "Enabwe %u viwtuaw functions\n", psnet->cfg.vf_num);
	wet = pci_enabwe_swiov(pdev, psnet->cfg.vf_num);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to enabwe SW-IOV\n");
		goto fwee_iwq;
	}

	/* Cweate HW monitow device */
	if (PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_HWMON)) {
#if IS_ENABWED(CONFIG_HWMON)
		psnet_cweate_hwmon(pdev);
#ewse
		SNET_WAWN(pdev, "Can't stawt HWMON, CONFIG_HWMON is not enabwed\n");
#endif
	}

	wetuwn 0;

fwee_iwq:
	if (pf_iwqs)
		pci_fwee_iwq_vectows(pdev);
fwee_cfg:
	snet_fwee_cfg(&psnet->cfg);
fwee_psnet:
	kfwee(psnet);
	wetuwn wet;
}

/* Pwobe function fow a viwtuaw PCI function */
static int snet_vdpa_pwobe_vf(stwuct pci_dev *pdev)
{
	stwuct pci_dev *pdev_pf = pdev->physfn;
	stwuct psnet *psnet = pci_get_dwvdata(pdev_pf);
	stwuct snet_dev_cfg *dev_cfg;
	stwuct snet *snet;
	u32 vfid;
	int wet;
	boow pf_iwqs = fawse;

	/* Get viwtuaw function id.
	 * (the DPU counts the VFs fwom 1)
	 */
	wet = pci_iov_vf_id(pdev);
	if (wet < 0) {
		SNET_EWW(pdev, "Faiwed to find a VF id\n");
		wetuwn wet;
	}
	vfid = wet + 1;

	/* Find the snet_dev_cfg based on vfid */
	dev_cfg = snet_find_dev_cfg(&psnet->cfg, vfid);
	if (!dev_cfg) {
		SNET_WAWN(pdev, "Faiwed to find a VF config..\n");
		wetuwn -ENODEV;
	}

	/* Which PCI device shouwd awwocate the IWQs?
	 * If the SNET_CFG_FWAG_IWQ_PF fwag set, the PF device awwocates the IWQs
	 */
	pf_iwqs = PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_IWQ_PF);

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to enabwe PCI VF device\n");
		wetuwn wet;
	}

	/* Wequest fow MSI-X IWQs */
	if (!pf_iwqs) {
		wet = snet_awwoc_iwq_vectow(pdev, dev_cfg);
		if (wet)
			wetuwn wet;
	}

	/* Awwocate vdpa device */
	snet = vdpa_awwoc_device(stwuct snet, vdpa, &pdev->dev, &snet_config_ops, 1, 1, NUWW,
				 fawse);
	if (!snet) {
		SNET_EWW(pdev, "Faiwed to awwocate a vdpa device\n");
		wet = -ENOMEM;
		goto fwee_iwqs;
	}

	/* Init contwow mutex and spinwock */
	mutex_init(&snet->ctww_wock);
	spin_wock_init(&snet->ctww_spinwock);

	/* Save pci device pointew */
	snet->pdev = pdev;
	snet->psnet = psnet;
	snet->cfg = dev_cfg;
	snet->dpu_weady = fawse;
	snet->sid = vfid;
	/* Weset IWQ vawue */
	snet->cfg_iwq = -1;

	wet = snet_open_vf_baw(pdev, snet);
	if (wet)
		goto put_device;

	/* Cweate a ViwtIO config pointew */
	snet->cfg->viwtio_cfg = snet->baw + snet->psnet->cfg.viwtio_cfg_off;

	/* Cweaw contwow wegistews */
	snet_ctww_cweaw(snet);

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, snet);

	wet = snet_buiwd_vqs(snet);
	if (wet)
		goto put_device;

	/* Wesewve IWQ indexes,
	 * The IWQs may be wequested and fweed muwtipwe times,
	 * but the indexes won't change.
	 */
	snet_wesewve_iwq_idx(pf_iwqs ? pdev_pf : pdev, snet);

	/*set DMA device*/
	snet->vdpa.dma_dev = &pdev->dev;

	/* Wegistew VDPA device */
	wet = vdpa_wegistew_device(&snet->vdpa, snet->cfg->vq_num);
	if (wet) {
		SNET_EWW(pdev, "Faiwed to wegistew vdpa device\n");
		goto fwee_vqs;
	}

	wetuwn 0;

fwee_vqs:
	snet_fwee_vqs(snet);
put_device:
	put_device(&snet->vdpa.dev);
fwee_iwqs:
	if (!pf_iwqs)
		pci_fwee_iwq_vectows(pdev);
	wetuwn wet;
}

static int snet_vdpa_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	if (pdev->is_viwtfn)
		wetuwn snet_vdpa_pwobe_vf(pdev);
	ewse
		wetuwn snet_vdpa_pwobe_pf(pdev);
}

static void snet_vdpa_wemove_pf(stwuct pci_dev *pdev)
{
	stwuct psnet *psnet = pci_get_dwvdata(pdev);

	pci_disabwe_swiov(pdev);
	/* If IWQs awe awwocated fwom the PF, we shouwd fwee the IWQs */
	if (PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_IWQ_PF))
		pci_fwee_iwq_vectows(pdev);

	snet_fwee_cfg(&psnet->cfg);
	kfwee(psnet);
}

static void snet_vdpa_wemove_vf(stwuct pci_dev *pdev)
{
	stwuct snet *snet = pci_get_dwvdata(pdev);
	stwuct psnet *psnet = snet->psnet;

	vdpa_unwegistew_device(&snet->vdpa);
	snet_fwee_vqs(snet);
	/* If IWQs awe awwocated fwom the VF, we shouwd fwee the IWQs */
	if (!PSNET_FWAG_ON(psnet, SNET_CFG_FWAG_IWQ_PF))
		pci_fwee_iwq_vectows(pdev);
}

static void snet_vdpa_wemove(stwuct pci_dev *pdev)
{
	if (pdev->is_viwtfn)
		snet_vdpa_wemove_vf(pdev);
	ewse
		snet_vdpa_wemove_pf(pdev);
}

static stwuct pci_device_id snet_dwivew_pci_ids[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_SOWIDWUN, SNET_DEVICE_ID,
			 PCI_VENDOW_ID_SOWIDWUN, SNET_DEVICE_ID) },
	{ 0 },
};

MODUWE_DEVICE_TABWE(pci, snet_dwivew_pci_ids);

static stwuct pci_dwivew snet_vdpa_dwivew = {
	.name		= "snet-vdpa-dwivew",
	.id_tabwe	= snet_dwivew_pci_ids,
	.pwobe		= snet_vdpa_pwobe,
	.wemove		= snet_vdpa_wemove,
};

moduwe_pci_dwivew(snet_vdpa_dwivew);

MODUWE_AUTHOW("Awvawo Kawsz <awvawo.kawsz@sowid-wun.com>");
MODUWE_DESCWIPTION("SowidWun vDPA dwivew");
MODUWE_WICENSE("GPW v2");
