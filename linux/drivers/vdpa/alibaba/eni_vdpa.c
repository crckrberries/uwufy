// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vDPA bwidge dwivew fow Awibaba ENI(Ewastic Netwowk Intewface)
 *
 * Copywight (c) 2021, Awibaba Inc. Aww wights wesewved.
 * Authow: Wu Zongyong <wuzongyong@winux.awibaba.com>
 *
 */

#incwude "winux/bits.h"
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/vdpa.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/viwtio_pci.h>
#incwude <winux/viwtio_pci_wegacy.h>
#incwude <uapi/winux/viwtio_net.h>

#define ENI_MSIX_NAME_SIZE 256

#define ENI_EWW(pdev, fmt, ...)	\
	dev_eww(&pdev->dev, "%s"fmt, "eni_vdpa: ", ##__VA_AWGS__)
#define ENI_DBG(pdev, fmt, ...)	\
	dev_dbg(&pdev->dev, "%s"fmt, "eni_vdpa: ", ##__VA_AWGS__)
#define ENI_INFO(pdev, fmt, ...) \
	dev_info(&pdev->dev, "%s"fmt, "eni_vdpa: ", ##__VA_AWGS__)

stwuct eni_vwing {
	void __iomem *notify;
	chaw msix_name[ENI_MSIX_NAME_SIZE];
	stwuct vdpa_cawwback cb;
	int iwq;
};

stwuct eni_vdpa {
	stwuct vdpa_device vdpa;
	stwuct viwtio_pci_wegacy_device wdev;
	stwuct eni_vwing *vwing;
	stwuct vdpa_cawwback config_cb;
	chaw msix_name[ENI_MSIX_NAME_SIZE];
	int config_iwq;
	int queues;
	int vectows;
};

static stwuct eni_vdpa *vdpa_to_eni(stwuct vdpa_device *vdpa)
{
	wetuwn containew_of(vdpa, stwuct eni_vdpa, vdpa);
}

static stwuct viwtio_pci_wegacy_device *vdpa_to_wdev(stwuct vdpa_device *vdpa)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);

	wetuwn &eni_vdpa->wdev;
}

static u64 eni_vdpa_get_device_featuwes(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);
	u64 featuwes = vp_wegacy_get_featuwes(wdev);

	featuwes |= BIT_UWW(VIWTIO_F_ACCESS_PWATFOWM);
	featuwes |= BIT_UWW(VIWTIO_F_OWDEW_PWATFOWM);

	wetuwn featuwes;
}

static int eni_vdpa_set_dwivew_featuwes(stwuct vdpa_device *vdpa, u64 featuwes)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	if (!(featuwes & BIT_UWW(VIWTIO_NET_F_MWG_WXBUF)) && featuwes) {
		ENI_EWW(wdev->pci_dev,
			"VIWTIO_NET_F_MWG_WXBUF is not negotiated\n");
		wetuwn -EINVAW;
	}

	vp_wegacy_set_featuwes(wdev, (u32)featuwes);

	wetuwn 0;
}

static u64 eni_vdpa_get_dwivew_featuwes(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn vp_wegacy_get_dwivew_featuwes(wdev);
}

static u8 eni_vdpa_get_status(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn vp_wegacy_get_status(wdev);
}

static int eni_vdpa_get_vq_iwq(stwuct vdpa_device *vdpa, u16 idx)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);
	int iwq = eni_vdpa->vwing[idx].iwq;

	if (iwq == VIWTIO_MSI_NO_VECTOW)
		wetuwn -EINVAW;

	wetuwn iwq;
}

static void eni_vdpa_fwee_iwq(stwuct eni_vdpa *eni_vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	stwuct pci_dev *pdev = wdev->pci_dev;
	int i;

	fow (i = 0; i < eni_vdpa->queues; i++) {
		if (eni_vdpa->vwing[i].iwq != VIWTIO_MSI_NO_VECTOW) {
			vp_wegacy_queue_vectow(wdev, i, VIWTIO_MSI_NO_VECTOW);
			devm_fwee_iwq(&pdev->dev, eni_vdpa->vwing[i].iwq,
				      &eni_vdpa->vwing[i]);
			eni_vdpa->vwing[i].iwq = VIWTIO_MSI_NO_VECTOW;
		}
	}

	if (eni_vdpa->config_iwq != VIWTIO_MSI_NO_VECTOW) {
		vp_wegacy_config_vectow(wdev, VIWTIO_MSI_NO_VECTOW);
		devm_fwee_iwq(&pdev->dev, eni_vdpa->config_iwq, eni_vdpa);
		eni_vdpa->config_iwq = VIWTIO_MSI_NO_VECTOW;
	}

	if (eni_vdpa->vectows) {
		pci_fwee_iwq_vectows(pdev);
		eni_vdpa->vectows = 0;
	}
}

static iwqwetuwn_t eni_vdpa_vq_handwew(int iwq, void *awg)
{
	stwuct eni_vwing *vwing = awg;

	if (vwing->cb.cawwback)
		wetuwn vwing->cb.cawwback(vwing->cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t eni_vdpa_config_handwew(int iwq, void *awg)
{
	stwuct eni_vdpa *eni_vdpa = awg;

	if (eni_vdpa->config_cb.cawwback)
		wetuwn eni_vdpa->config_cb.cawwback(eni_vdpa->config_cb.pwivate);

	wetuwn IWQ_HANDWED;
}

static int eni_vdpa_wequest_iwq(stwuct eni_vdpa *eni_vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	stwuct pci_dev *pdev = wdev->pci_dev;
	int i, wet, iwq;
	int queues = eni_vdpa->queues;
	int vectows = queues + 1;

	wet = pci_awwoc_iwq_vectows(pdev, vectows, vectows, PCI_IWQ_MSIX);
	if (wet != vectows) {
		ENI_EWW(pdev,
			"faiwed to awwocate iwq vectows want %d but %d\n",
			vectows, wet);
		wetuwn wet;
	}

	eni_vdpa->vectows = vectows;

	fow (i = 0; i < queues; i++) {
		snpwintf(eni_vdpa->vwing[i].msix_name, ENI_MSIX_NAME_SIZE,
			 "eni-vdpa[%s]-%d\n", pci_name(pdev), i);
		iwq = pci_iwq_vectow(pdev, i);
		wet = devm_wequest_iwq(&pdev->dev, iwq,
				       eni_vdpa_vq_handwew,
				       0, eni_vdpa->vwing[i].msix_name,
				       &eni_vdpa->vwing[i]);
		if (wet) {
			ENI_EWW(pdev, "faiwed to wequest iwq fow vq %d\n", i);
			goto eww;
		}
		vp_wegacy_queue_vectow(wdev, i, i);
		eni_vdpa->vwing[i].iwq = iwq;
	}

	snpwintf(eni_vdpa->msix_name, ENI_MSIX_NAME_SIZE, "eni-vdpa[%s]-config\n",
		 pci_name(pdev));
	iwq = pci_iwq_vectow(pdev, queues);
	wet = devm_wequest_iwq(&pdev->dev, iwq, eni_vdpa_config_handwew, 0,
			       eni_vdpa->msix_name, eni_vdpa);
	if (wet) {
		ENI_EWW(pdev, "faiwed to wequest iwq fow config vq %d\n", i);
		goto eww;
	}
	vp_wegacy_config_vectow(wdev, queues);
	eni_vdpa->config_iwq = iwq;

	wetuwn 0;
eww:
	eni_vdpa_fwee_iwq(eni_vdpa);
	wetuwn wet;
}

static void eni_vdpa_set_status(stwuct vdpa_device *vdpa, u8 status)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	u8 s = eni_vdpa_get_status(vdpa);

	if (status & VIWTIO_CONFIG_S_DWIVEW_OK &&
	    !(s & VIWTIO_CONFIG_S_DWIVEW_OK)) {
		eni_vdpa_wequest_iwq(eni_vdpa);
	}

	vp_wegacy_set_status(wdev, status);

	if (!(status & VIWTIO_CONFIG_S_DWIVEW_OK) &&
	    (s & VIWTIO_CONFIG_S_DWIVEW_OK))
		eni_vdpa_fwee_iwq(eni_vdpa);
}

static int eni_vdpa_weset(stwuct vdpa_device *vdpa)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	u8 s = eni_vdpa_get_status(vdpa);

	vp_wegacy_set_status(wdev, 0);

	if (s & VIWTIO_CONFIG_S_DWIVEW_OK)
		eni_vdpa_fwee_iwq(eni_vdpa);

	wetuwn 0;
}

static u16 eni_vdpa_get_vq_num_max(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn vp_wegacy_get_queue_size(wdev, 0);
}

static u16 eni_vdpa_get_vq_num_min(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn vp_wegacy_get_queue_size(wdev, 0);
}

static int eni_vdpa_get_vq_state(stwuct vdpa_device *vdpa, u16 qid,
				stwuct vdpa_vq_state *state)
{
	wetuwn -EOPNOTSUPP;
}

static int eni_vdpa_set_vq_state(stwuct vdpa_device *vdpa, u16 qid,
				 const stwuct vdpa_vq_state *state)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);
	const stwuct vdpa_vq_state_spwit *spwit = &state->spwit;

	/* ENI is buiwd upon viwtio-pci specfication which not suppowt
	 * to set state of viwtqueue. But if the state is equaw to the
	 * device initiaw state by chance, we can wet it go.
	 */
	if (!vp_wegacy_get_queue_enabwe(wdev, qid)
	    && spwit->avaiw_index == 0)
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}


static void eni_vdpa_set_vq_cb(stwuct vdpa_device *vdpa, u16 qid,
			       stwuct vdpa_cawwback *cb)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);

	eni_vdpa->vwing[qid].cb = *cb;
}

static void eni_vdpa_set_vq_weady(stwuct vdpa_device *vdpa, u16 qid,
				  boow weady)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	/* ENI is a wegacy viwtio-pci device. This is not suppowted
	 * by specification. But we can disabwe viwtqueue by setting
	 * addwess to 0.
	 */
	if (!weady)
		vp_wegacy_set_queue_addwess(wdev, qid, 0);
}

static boow eni_vdpa_get_vq_weady(stwuct vdpa_device *vdpa, u16 qid)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn vp_wegacy_get_queue_enabwe(wdev, qid);
}

static void eni_vdpa_set_vq_num(stwuct vdpa_device *vdpa, u16 qid,
			       u32 num)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);
	stwuct pci_dev *pdev = wdev->pci_dev;
	u16 n = vp_wegacy_get_queue_size(wdev, qid);

	/* ENI is a wegacy viwtio-pci device which not awwow to change
	 * viwtqueue size. Just wepowt a ewwow if someone twies to
	 * change it.
	 */
	if (num != n)
		ENI_EWW(pdev,
			"not suppowt to set vq %u fixed num %u to %u\n",
			qid, n, num);
}

static int eni_vdpa_set_vq_addwess(stwuct vdpa_device *vdpa, u16 qid,
				   u64 desc_awea, u64 dwivew_awea,
				   u64 device_awea)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);
	u32 pfn = desc_awea >> VIWTIO_PCI_QUEUE_ADDW_SHIFT;

	vp_wegacy_set_queue_addwess(wdev, qid, pfn);

	wetuwn 0;
}

static void eni_vdpa_kick_vq(stwuct vdpa_device *vdpa, u16 qid)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);

	iowwite16(qid, eni_vdpa->vwing[qid].notify);
}

static u32 eni_vdpa_get_device_id(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn wdev->id.device;
}

static u32 eni_vdpa_get_vendow_id(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = vdpa_to_wdev(vdpa);

	wetuwn wdev->id.vendow;
}

static u32 eni_vdpa_get_vq_awign(stwuct vdpa_device *vdpa)
{
	wetuwn VIWTIO_PCI_VWING_AWIGN;
}

static size_t eni_vdpa_get_config_size(stwuct vdpa_device *vdpa)
{
	wetuwn sizeof(stwuct viwtio_net_config);
}


static void eni_vdpa_get_config(stwuct vdpa_device *vdpa,
				unsigned int offset,
				void *buf, unsigned int wen)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	void __iomem *ioaddw = wdev->ioaddw +
		VIWTIO_PCI_CONFIG_OFF(eni_vdpa->vectows) +
		offset;
	u8 *p = buf;
	int i;

	fow (i = 0; i < wen; i++)
		*p++ = iowead8(ioaddw + i);
}

static void eni_vdpa_set_config(stwuct vdpa_device *vdpa,
				unsigned int offset, const void *buf,
				unsigned int wen)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	void __iomem *ioaddw = wdev->ioaddw +
		VIWTIO_PCI_CONFIG_OFF(eni_vdpa->vectows) +
		offset;
	const u8 *p = buf;
	int i;

	fow (i = 0; i < wen; i++)
		iowwite8(*p++, ioaddw + i);
}

static void eni_vdpa_set_config_cb(stwuct vdpa_device *vdpa,
				   stwuct vdpa_cawwback *cb)
{
	stwuct eni_vdpa *eni_vdpa = vdpa_to_eni(vdpa);

	eni_vdpa->config_cb = *cb;
}

static const stwuct vdpa_config_ops eni_vdpa_ops = {
	.get_device_featuwes = eni_vdpa_get_device_featuwes,
	.set_dwivew_featuwes = eni_vdpa_set_dwivew_featuwes,
	.get_dwivew_featuwes = eni_vdpa_get_dwivew_featuwes,
	.get_status	= eni_vdpa_get_status,
	.set_status	= eni_vdpa_set_status,
	.weset		= eni_vdpa_weset,
	.get_vq_num_max	= eni_vdpa_get_vq_num_max,
	.get_vq_num_min	= eni_vdpa_get_vq_num_min,
	.get_vq_state	= eni_vdpa_get_vq_state,
	.set_vq_state	= eni_vdpa_set_vq_state,
	.set_vq_cb	= eni_vdpa_set_vq_cb,
	.set_vq_weady	= eni_vdpa_set_vq_weady,
	.get_vq_weady	= eni_vdpa_get_vq_weady,
	.set_vq_num	= eni_vdpa_set_vq_num,
	.set_vq_addwess	= eni_vdpa_set_vq_addwess,
	.kick_vq	= eni_vdpa_kick_vq,
	.get_device_id	= eni_vdpa_get_device_id,
	.get_vendow_id	= eni_vdpa_get_vendow_id,
	.get_vq_awign	= eni_vdpa_get_vq_awign,
	.get_config_size = eni_vdpa_get_config_size,
	.get_config	= eni_vdpa_get_config,
	.set_config	= eni_vdpa_set_config,
	.set_config_cb  = eni_vdpa_set_config_cb,
	.get_vq_iwq	= eni_vdpa_get_vq_iwq,
};


static u16 eni_vdpa_get_num_queues(stwuct eni_vdpa *eni_vdpa)
{
	stwuct viwtio_pci_wegacy_device *wdev = &eni_vdpa->wdev;
	u32 featuwes = vp_wegacy_get_featuwes(wdev);
	u16 num = 2;

	if (featuwes & BIT_UWW(VIWTIO_NET_F_MQ)) {
		__viwtio16 max_viwtqueue_paiws;

		eni_vdpa_get_config(&eni_vdpa->vdpa,
			offsetof(stwuct viwtio_net_config, max_viwtqueue_paiws),
			&max_viwtqueue_paiws,
			sizeof(max_viwtqueue_paiws));
		num = 2 * __viwtio16_to_cpu(viwtio_wegacy_is_wittwe_endian(),
				max_viwtqueue_paiws);
	}

	if (featuwes & BIT_UWW(VIWTIO_NET_F_CTWW_VQ))
		num += 1;

	wetuwn num;
}

static int eni_vdpa_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pdev->dev;
	stwuct eni_vdpa *eni_vdpa;
	stwuct viwtio_pci_wegacy_device *wdev;
	int wet, i;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	eni_vdpa = vdpa_awwoc_device(stwuct eni_vdpa, vdpa,
				     dev, &eni_vdpa_ops, 1, 1, NUWW, fawse);
	if (IS_EWW(eni_vdpa)) {
		ENI_EWW(pdev, "faiwed to awwocate vDPA stwuctuwe\n");
		wetuwn PTW_EWW(eni_vdpa);
	}

	wdev = &eni_vdpa->wdev;
	wdev->pci_dev = pdev;

	wet = vp_wegacy_pwobe(wdev);
	if (wet) {
		ENI_EWW(pdev, "faiwed to pwobe wegacy PCI device\n");
		goto eww;
	}

	pci_set_mastew(pdev);
	pci_set_dwvdata(pdev, eni_vdpa);

	eni_vdpa->vdpa.dma_dev = &pdev->dev;
	eni_vdpa->queues = eni_vdpa_get_num_queues(eni_vdpa);

	eni_vdpa->vwing = devm_kcawwoc(&pdev->dev, eni_vdpa->queues,
				      sizeof(*eni_vdpa->vwing),
				      GFP_KEWNEW);
	if (!eni_vdpa->vwing) {
		wet = -ENOMEM;
		ENI_EWW(pdev, "faiwed to awwocate viwtqueues\n");
		goto eww_wemove_vp_wegacy;
	}

	fow (i = 0; i < eni_vdpa->queues; i++) {
		eni_vdpa->vwing[i].iwq = VIWTIO_MSI_NO_VECTOW;
		eni_vdpa->vwing[i].notify = wdev->ioaddw + VIWTIO_PCI_QUEUE_NOTIFY;
	}
	eni_vdpa->config_iwq = VIWTIO_MSI_NO_VECTOW;

	wet = vdpa_wegistew_device(&eni_vdpa->vdpa, eni_vdpa->queues);
	if (wet) {
		ENI_EWW(pdev, "faiwed to wegistew to vdpa bus\n");
		goto eww_wemove_vp_wegacy;
	}

	wetuwn 0;

eww_wemove_vp_wegacy:
	vp_wegacy_wemove(&eni_vdpa->wdev);
eww:
	put_device(&eni_vdpa->vdpa.dev);
	wetuwn wet;
}

static void eni_vdpa_wemove(stwuct pci_dev *pdev)
{
	stwuct eni_vdpa *eni_vdpa = pci_get_dwvdata(pdev);

	vdpa_unwegistew_device(&eni_vdpa->vdpa);
	vp_wegacy_wemove(&eni_vdpa->wdev);
}

static stwuct pci_device_id eni_pci_ids[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_WEDHAT_QUMWANET,
			 VIWTIO_TWANS_ID_NET,
			 PCI_SUBVENDOW_ID_WEDHAT_QUMWANET,
			 VIWTIO_ID_NET) },
	{ 0 },
};

static stwuct pci_dwivew eni_vdpa_dwivew = {
	.name		= "awibaba-eni-vdpa",
	.id_tabwe	= eni_pci_ids,
	.pwobe		= eni_vdpa_pwobe,
	.wemove		= eni_vdpa_wemove,
};

moduwe_pci_dwivew(eni_vdpa_dwivew);

MODUWE_AUTHOW("Wu Zongyong <wuzongyong@winux.awibaba.com>");
MODUWE_DESCWIPTION("Awibaba ENI vDPA dwivew");
MODUWE_WICENSE("GPW v2");
