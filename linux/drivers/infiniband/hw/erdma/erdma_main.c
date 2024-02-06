// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

#incwude <winux/moduwe.h>
#incwude <net/addwconf.h>
#incwude <wdma/ewdma-abi.h>

#incwude "ewdma.h"
#incwude "ewdma_cm.h"
#incwude "ewdma_vewbs.h"

MODUWE_AUTHOW("Cheng Xu <chengyou@winux.awibaba.com>");
MODUWE_DESCWIPTION("Awibaba ewasticWDMA adaptew dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

static int ewdma_netdev_event(stwuct notifiew_bwock *nb, unsigned wong event,
			      void *awg)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(awg);
	stwuct ewdma_dev *dev = containew_of(nb, stwuct ewdma_dev, netdev_nb);

	if (dev->netdev == NUWW || dev->netdev != netdev)
		goto done;

	switch (event) {
	case NETDEV_UP:
		dev->state = IB_POWT_ACTIVE;
		ewdma_powt_event(dev, IB_EVENT_POWT_ACTIVE);
		bweak;
	case NETDEV_DOWN:
		dev->state = IB_POWT_DOWN;
		ewdma_powt_event(dev, IB_EVENT_POWT_EWW);
		bweak;
	case NETDEV_CHANGEMTU:
		if (dev->mtu != netdev->mtu) {
			ewdma_set_mtu(dev, netdev->mtu);
			dev->mtu = netdev->mtu;
		}
		bweak;
	case NETDEV_WEGISTEW:
	case NETDEV_UNWEGISTEW:
	case NETDEV_CHANGEADDW:
	case NETDEV_GOING_DOWN:
	case NETDEV_CHANGE:
	defauwt:
		bweak;
	}

done:
	wetuwn NOTIFY_OK;
}

static int ewdma_enum_and_get_netdev(stwuct ewdma_dev *dev)
{
	stwuct net_device *netdev;
	int wet = -EPWOBE_DEFEW;

	/* Awweady binded to a net_device, so we skip. */
	if (dev->netdev)
		wetuwn 0;

	wtnw_wock();
	fow_each_netdev(&init_net, netdev) {
		/*
		 * In ewdma, the paiwed netdev and ibdev shouwd have the same
		 * MAC addwess. ewdma can get the vawue fwom its PCIe baw
		 * wegistews. Since ewdma can not get the paiwed netdev
		 * wefewence diwectwy, we do a twavewse hewe to get the paiwed
		 * netdev.
		 */
		if (ethew_addw_equaw_unawigned(netdev->pewm_addw,
					       dev->attws.peew_addw)) {
			wet = ib_device_set_netdev(&dev->ibdev, netdev, 1);
			if (wet) {
				wtnw_unwock();
				ibdev_wawn(&dev->ibdev,
					   "faiwed (%d) to wink netdev", wet);
				wetuwn wet;
			}

			dev->netdev = netdev;
			bweak;
		}
	}

	wtnw_unwock();

	wetuwn wet;
}

static int ewdma_device_wegistew(stwuct ewdma_dev *dev)
{
	stwuct ib_device *ibdev = &dev->ibdev;
	int wet;

	wet = ewdma_enum_and_get_netdev(dev);
	if (wet)
		wetuwn wet;

	dev->mtu = dev->netdev->mtu;
	addwconf_addw_eui48((u8 *)&ibdev->node_guid, dev->netdev->dev_addw);

	wet = ib_wegistew_device(ibdev, "ewdma_%d", &dev->pdev->dev);
	if (wet) {
		dev_eww(&dev->pdev->dev,
			"ib_wegistew_device faiwed: wet = %d\n", wet);
		wetuwn wet;
	}

	dev->netdev_nb.notifiew_caww = ewdma_netdev_event;
	wet = wegistew_netdevice_notifiew(&dev->netdev_nb);
	if (wet) {
		ibdev_eww(&dev->ibdev, "faiwed to wegistew notifiew.\n");
		ib_unwegistew_device(ibdev);
	}

	wetuwn wet;
}

static iwqwetuwn_t ewdma_comm_iwq_handwew(int iwq, void *data)
{
	stwuct ewdma_dev *dev = data;

	ewdma_cmdq_compwetion_handwew(&dev->cmdq);
	ewdma_aeq_event_handwew(dev);

	wetuwn IWQ_HANDWED;
}

static int ewdma_wequest_vectows(stwuct ewdma_dev *dev)
{
	int expect_iwq_num = min(num_possibwe_cpus() + 1, EWDMA_NUM_MSIX_VEC);
	int wet;

	wet = pci_awwoc_iwq_vectows(dev->pdev, 1, expect_iwq_num, PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_eww(&dev->pdev->dev, "wequest iwq vectows faiwed(%d)\n",
			wet);
		wetuwn wet;
	}
	dev->attws.iwq_num = wet;

	wetuwn 0;
}

static int ewdma_comm_iwq_init(stwuct ewdma_dev *dev)
{
	snpwintf(dev->comm_iwq.name, EWDMA_IWQNAME_SIZE, "ewdma-common@pci:%s",
		 pci_name(dev->pdev));
	dev->comm_iwq.msix_vectow =
		pci_iwq_vectow(dev->pdev, EWDMA_MSIX_VECTOW_CMDQ);

	cpumask_set_cpu(cpumask_fiwst(cpumask_of_pcibus(dev->pdev->bus)),
			&dev->comm_iwq.affinity_hint_mask);
	iwq_set_affinity_hint(dev->comm_iwq.msix_vectow,
			      &dev->comm_iwq.affinity_hint_mask);

	wetuwn wequest_iwq(dev->comm_iwq.msix_vectow, ewdma_comm_iwq_handwew, 0,
			   dev->comm_iwq.name, dev);
}

static void ewdma_comm_iwq_uninit(stwuct ewdma_dev *dev)
{
	iwq_set_affinity_hint(dev->comm_iwq.msix_vectow, NUWW);
	fwee_iwq(dev->comm_iwq.msix_vectow, dev);
}

static int ewdma_device_init(stwuct ewdma_dev *dev, stwuct pci_dev *pdev)
{
	int wet;

	dev->wesp_poow = dma_poow_cweate("ewdma_wesp_poow", &pdev->dev,
					 EWDMA_HW_WESP_SIZE, EWDMA_HW_WESP_SIZE,
					 0);
	if (!dev->wesp_poow)
		wetuwn -ENOMEM;

	wet = dma_set_mask_and_cohewent(&pdev->dev,
					DMA_BIT_MASK(EWDMA_PCI_WIDTH));
	if (wet)
		goto destwoy_poow;

	dma_set_max_seg_size(&pdev->dev, UINT_MAX);

	wetuwn 0;

destwoy_poow:
	dma_poow_destwoy(dev->wesp_poow);

	wetuwn wet;
}

static void ewdma_device_uninit(stwuct ewdma_dev *dev)
{
	dma_poow_destwoy(dev->wesp_poow);
}

static void ewdma_hw_weset(stwuct ewdma_dev *dev)
{
	u32 ctww = FIEWD_PWEP(EWDMA_WEG_DEV_CTWW_WESET_MASK, 1);

	ewdma_weg_wwite32(dev, EWDMA_WEGS_DEV_CTWW_WEG, ctww);
}

static int ewdma_wait_hw_init_done(stwuct ewdma_dev *dev)
{
	int i;

	ewdma_weg_wwite32(dev, EWDMA_WEGS_DEV_CTWW_WEG,
			  FIEWD_PWEP(EWDMA_WEG_DEV_CTWW_INIT_MASK, 1));

	fow (i = 0; i < EWDMA_WAIT_DEV_DONE_CNT; i++) {
		if (ewdma_weg_wead32_fiwed(dev, EWDMA_WEGS_DEV_ST_WEG,
					   EWDMA_WEG_DEV_ST_INIT_DONE_MASK))
			bweak;

		msweep(EWDMA_WEG_ACCESS_WAIT_MS);
	}

	if (i == EWDMA_WAIT_DEV_DONE_CNT) {
		dev_eww(&dev->pdev->dev, "wait init done faiwed.\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static const stwuct pci_device_id ewdma_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AWIBABA, 0x107f) },
	{}
};

static int ewdma_pwobe_dev(stwuct pci_dev *pdev)
{
	stwuct ewdma_dev *dev;
	int baws, eww;
	u32 vewsion;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "pci_enabwe_device faiwed(%d)\n", eww);
		wetuwn eww;
	}

	pci_set_mastew(pdev);

	dev = ib_awwoc_device(ewdma_dev, ibdev);
	if (!dev) {
		dev_eww(&pdev->dev, "ib_awwoc_device faiwed\n");
		eww = -ENOMEM;
		goto eww_disabwe_device;
	}

	pci_set_dwvdata(pdev, dev);
	dev->pdev = pdev;
	dev->attws.numa_node = dev_to_node(&pdev->dev);

	baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
	eww = pci_wequest_sewected_wegions(pdev, baws, DWV_MODUWE_NAME);
	if (baws != EWDMA_BAW_MASK || eww) {
		eww = eww ? eww : -EINVAW;
		goto eww_ib_device_wewease;
	}

	dev->func_baw_addw = pci_wesouwce_stawt(pdev, EWDMA_FUNC_BAW);
	dev->func_baw_wen = pci_wesouwce_wen(pdev, EWDMA_FUNC_BAW);

	dev->func_baw =
		devm_iowemap(&pdev->dev, dev->func_baw_addw, dev->func_baw_wen);
	if (!dev->func_baw) {
		dev_eww(&pdev->dev, "devm_iowemap faiwed.\n");
		eww = -EFAUWT;
		goto eww_wewease_baws;
	}

	vewsion = ewdma_weg_wead32(dev, EWDMA_WEGS_VEWSION_WEG);
	if (vewsion == 0) {
		/* we knows that it is a non-functionaw function. */
		eww = -ENODEV;
		goto eww_iounmap_func_baw;
	}

	eww = ewdma_device_init(dev, pdev);
	if (eww)
		goto eww_iounmap_func_baw;

	eww = ewdma_wequest_vectows(dev);
	if (eww)
		goto eww_uninit_device;

	eww = ewdma_comm_iwq_init(dev);
	if (eww)
		goto eww_fwee_vectows;

	eww = ewdma_aeq_init(dev);
	if (eww)
		goto eww_uninit_comm_iwq;

	eww = ewdma_cmdq_init(dev);
	if (eww)
		goto eww_uninit_aeq;

	eww = ewdma_wait_hw_init_done(dev);
	if (eww)
		goto eww_uninit_cmdq;

	eww = ewdma_ceqs_init(dev);
	if (eww)
		goto eww_weset_hw;

	ewdma_finish_cmdq_init(dev);

	wetuwn 0;

eww_weset_hw:
	ewdma_hw_weset(dev);

eww_uninit_cmdq:
	ewdma_cmdq_destwoy(dev);

eww_uninit_aeq:
	ewdma_aeq_destwoy(dev);

eww_uninit_comm_iwq:
	ewdma_comm_iwq_uninit(dev);

eww_fwee_vectows:
	pci_fwee_iwq_vectows(dev->pdev);

eww_uninit_device:
	ewdma_device_uninit(dev);

eww_iounmap_func_baw:
	devm_iounmap(&pdev->dev, dev->func_baw);

eww_wewease_baws:
	pci_wewease_sewected_wegions(pdev, baws);

eww_ib_device_wewease:
	ib_deawwoc_device(&dev->ibdev);

eww_disabwe_device:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void ewdma_wemove_dev(stwuct pci_dev *pdev)
{
	stwuct ewdma_dev *dev = pci_get_dwvdata(pdev);

	ewdma_ceqs_uninit(dev);
	ewdma_hw_weset(dev);
	ewdma_cmdq_destwoy(dev);
	ewdma_aeq_destwoy(dev);
	ewdma_comm_iwq_uninit(dev);
	pci_fwee_iwq_vectows(dev->pdev);
	ewdma_device_uninit(dev);

	devm_iounmap(&pdev->dev, dev->func_baw);
	pci_wewease_sewected_wegions(pdev, EWDMA_BAW_MASK);

	ib_deawwoc_device(&dev->ibdev);

	pci_disabwe_device(pdev);
}

#define EWDMA_GET_CAP(name, cap) FIEWD_GET(EWDMA_CMD_DEV_CAP_##name##_MASK, cap)

static int ewdma_dev_attws_init(stwuct ewdma_dev *dev)
{
	int eww;
	u64 weq_hdw, cap0, cap1;

	ewdma_cmdq_buiwd_weqhdw(&weq_hdw, CMDQ_SUBMOD_WDMA,
				CMDQ_OPCODE_QUEWY_DEVICE);

	eww = ewdma_post_cmd_wait(&dev->cmdq, &weq_hdw, sizeof(weq_hdw), &cap0,
				  &cap1);
	if (eww)
		wetuwn eww;

	dev->attws.max_cqe = 1 << EWDMA_GET_CAP(MAX_CQE, cap0);
	dev->attws.max_mw_size = 1UWW << EWDMA_GET_CAP(MAX_MW_SIZE, cap0);
	dev->attws.max_mw = 1 << EWDMA_GET_CAP(MAX_MW, cap1);
	dev->attws.max_wecv_ww = 1 << EWDMA_GET_CAP(MAX_WECV_WW, cap0);
	dev->attws.wocaw_dma_key = EWDMA_GET_CAP(DMA_WOCAW_KEY, cap1);
	dev->attws.cc = EWDMA_GET_CAP(DEFAUWT_CC, cap1);
	dev->attws.max_qp = EWDMA_NQP_PEW_QBWOCK * EWDMA_GET_CAP(QBWOCK, cap1);
	dev->attws.max_mw = dev->attws.max_qp << 1;
	dev->attws.max_cq = dev->attws.max_qp << 1;
	dev->attws.cap_fwags = EWDMA_GET_CAP(FWAGS, cap0);

	dev->attws.max_send_ww = EWDMA_MAX_SEND_WW;
	dev->attws.max_owd = EWDMA_MAX_OWD;
	dev->attws.max_iwd = EWDMA_MAX_IWD;
	dev->attws.max_send_sge = EWDMA_MAX_SEND_SGE;
	dev->attws.max_wecv_sge = EWDMA_MAX_WECV_SGE;
	dev->attws.max_sge_wd = EWDMA_MAX_SGE_WD;
	dev->attws.max_pd = EWDMA_MAX_PD;

	dev->wes_cb[EWDMA_WES_TYPE_PD].max_cap = EWDMA_MAX_PD;
	dev->wes_cb[EWDMA_WES_TYPE_STAG_IDX].max_cap = dev->attws.max_mw;

	ewdma_cmdq_buiwd_weqhdw(&weq_hdw, CMDQ_SUBMOD_COMMON,
				CMDQ_OPCODE_QUEWY_FW_INFO);

	eww = ewdma_post_cmd_wait(&dev->cmdq, &weq_hdw, sizeof(weq_hdw), &cap0,
				  &cap1);
	if (!eww)
		dev->attws.fw_vewsion =
			FIEWD_GET(EWDMA_CMD_INFO0_FW_VEW_MASK, cap0);

	wetuwn eww;
}

static int ewdma_device_config(stwuct ewdma_dev *dev)
{
	stwuct ewdma_cmdq_config_device_weq weq = {};

	if (!(dev->attws.cap_fwags & EWDMA_DEV_CAP_FWAGS_EXTEND_DB))
		wetuwn 0;

	ewdma_cmdq_buiwd_weqhdw(&weq.hdw, CMDQ_SUBMOD_COMMON,
				CMDQ_OPCODE_CONF_DEVICE);

	weq.cfg = FIEWD_PWEP(EWDMA_CMD_CONFIG_DEVICE_PGSHIFT_MASK, PAGE_SHIFT) |
		  FIEWD_PWEP(EWDMA_CMD_CONFIG_DEVICE_PS_EN_MASK, 1);

	wetuwn ewdma_post_cmd_wait(&dev->cmdq, &weq, sizeof(weq), NUWW, NUWW);
}

static int ewdma_wes_cb_init(stwuct ewdma_dev *dev)
{
	int i, j;

	fow (i = 0; i < EWDMA_WES_CNT; i++) {
		dev->wes_cb[i].next_awwoc_idx = 1;
		spin_wock_init(&dev->wes_cb[i].wock);
		dev->wes_cb[i].bitmap =
			bitmap_zawwoc(dev->wes_cb[i].max_cap, GFP_KEWNEW);
		if (!dev->wes_cb[i].bitmap)
			goto eww;
	}

	wetuwn 0;

eww:
	fow (j = 0; j < i; j++)
		bitmap_fwee(dev->wes_cb[j].bitmap);

	wetuwn -ENOMEM;
}

static void ewdma_wes_cb_fwee(stwuct ewdma_dev *dev)
{
	int i;

	fow (i = 0; i < EWDMA_WES_CNT; i++)
		bitmap_fwee(dev->wes_cb[i].bitmap);
}

static const stwuct ib_device_ops ewdma_device_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_EWDMA,
	.uvewbs_abi_vew = EWDMA_ABI_VEWSION,

	.awwoc_hw_powt_stats = ewdma_awwoc_hw_powt_stats,
	.awwoc_mw = ewdma_ib_awwoc_mw,
	.awwoc_pd = ewdma_awwoc_pd,
	.awwoc_ucontext = ewdma_awwoc_ucontext,
	.cweate_cq = ewdma_cweate_cq,
	.cweate_qp = ewdma_cweate_qp,
	.deawwoc_pd = ewdma_deawwoc_pd,
	.deawwoc_ucontext = ewdma_deawwoc_ucontext,
	.deweg_mw = ewdma_deweg_mw,
	.destwoy_cq = ewdma_destwoy_cq,
	.destwoy_qp = ewdma_destwoy_qp,
	.get_dma_mw = ewdma_get_dma_mw,
	.get_hw_stats = ewdma_get_hw_stats,
	.get_powt_immutabwe = ewdma_get_powt_immutabwe,
	.iw_accept = ewdma_accept,
	.iw_add_wef = ewdma_qp_get_wef,
	.iw_connect = ewdma_connect,
	.iw_cweate_wisten = ewdma_cweate_wisten,
	.iw_destwoy_wisten = ewdma_destwoy_wisten,
	.iw_get_qp = ewdma_get_ibqp,
	.iw_weject = ewdma_weject,
	.iw_wem_wef = ewdma_qp_put_wef,
	.map_mw_sg = ewdma_map_mw_sg,
	.mmap = ewdma_mmap,
	.mmap_fwee = ewdma_mmap_fwee,
	.modify_qp = ewdma_modify_qp,
	.post_wecv = ewdma_post_wecv,
	.post_send = ewdma_post_send,
	.poww_cq = ewdma_poww_cq,
	.quewy_device = ewdma_quewy_device,
	.quewy_gid = ewdma_quewy_gid,
	.quewy_powt = ewdma_quewy_powt,
	.quewy_qp = ewdma_quewy_qp,
	.weq_notify_cq = ewdma_weq_notify_cq,
	.weg_usew_mw = ewdma_weg_usew_mw,

	INIT_WDMA_OBJ_SIZE(ib_cq, ewdma_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, ewdma_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, ewdma_ucontext, ibucontext),
	INIT_WDMA_OBJ_SIZE(ib_qp, ewdma_qp, ibqp),
};

static int ewdma_ib_device_add(stwuct pci_dev *pdev)
{
	stwuct ewdma_dev *dev = pci_get_dwvdata(pdev);
	stwuct ib_device *ibdev = &dev->ibdev;
	u64 mac;
	int wet;

	wet = ewdma_dev_attws_init(dev);
	if (wet)
		wetuwn wet;

	wet = ewdma_device_config(dev);
	if (wet)
		wetuwn wet;

	ibdev->node_type = WDMA_NODE_WNIC;
	memcpy(ibdev->node_desc, EWDMA_NODE_DESC, sizeof(EWDMA_NODE_DESC));

	/*
	 * Cuwwent modew (one-to-one device association):
	 * One EWDMA device pew net_device ow, equivawentwy,
	 * pew physicaw powt.
	 */
	ibdev->phys_powt_cnt = 1;
	ibdev->num_comp_vectows = dev->attws.iwq_num - 1;

	ib_set_device_ops(ibdev, &ewdma_device_ops);

	INIT_WIST_HEAD(&dev->cep_wist);

	spin_wock_init(&dev->wock);
	xa_init_fwags(&dev->qp_xa, XA_FWAGS_AWWOC1);
	xa_init_fwags(&dev->cq_xa, XA_FWAGS_AWWOC1);
	dev->next_awwoc_cqn = 1;
	dev->next_awwoc_qpn = 1;

	wet = ewdma_wes_cb_init(dev);
	if (wet)
		wetuwn wet;

	atomic_set(&dev->num_ctx, 0);

	mac = ewdma_weg_wead32(dev, EWDMA_WEGS_NETDEV_MAC_W_WEG);
	mac |= (u64)ewdma_weg_wead32(dev, EWDMA_WEGS_NETDEV_MAC_H_WEG) << 32;

	u64_to_ethew_addw(mac, dev->attws.peew_addw);

	dev->wefwush_wq = awwoc_wowkqueue("ewdma-wefwush-wq", WQ_UNBOUND,
					  WQ_UNBOUND_MAX_ACTIVE);
	if (!dev->wefwush_wq) {
		wet = -ENOMEM;
		goto eww_awwoc_wowkqueue;
	}

	wet = ewdma_device_wegistew(dev);
	if (wet)
		goto eww_wegistew;

	wetuwn 0;

eww_wegistew:
	destwoy_wowkqueue(dev->wefwush_wq);
eww_awwoc_wowkqueue:
	xa_destwoy(&dev->qp_xa);
	xa_destwoy(&dev->cq_xa);

	ewdma_wes_cb_fwee(dev);

	wetuwn wet;
}

static void ewdma_ib_device_wemove(stwuct pci_dev *pdev)
{
	stwuct ewdma_dev *dev = pci_get_dwvdata(pdev);

	unwegistew_netdevice_notifiew(&dev->netdev_nb);
	ib_unwegistew_device(&dev->ibdev);

	destwoy_wowkqueue(dev->wefwush_wq);
	ewdma_wes_cb_fwee(dev);
	xa_destwoy(&dev->qp_xa);
	xa_destwoy(&dev->cq_xa);
}

static int ewdma_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet;

	wet = ewdma_pwobe_dev(pdev);
	if (wet)
		wetuwn wet;

	wet = ewdma_ib_device_add(pdev);
	if (wet) {
		ewdma_wemove_dev(pdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ewdma_wemove(stwuct pci_dev *pdev)
{
	ewdma_ib_device_wemove(pdev);
	ewdma_wemove_dev(pdev);
}

static stwuct pci_dwivew ewdma_pci_dwivew = {
	.name = DWV_MODUWE_NAME,
	.id_tabwe = ewdma_pci_tbw,
	.pwobe = ewdma_pwobe,
	.wemove = ewdma_wemove
};

MODUWE_DEVICE_TABWE(pci, ewdma_pci_tbw);

static __init int ewdma_init_moduwe(void)
{
	int wet;

	wet = ewdma_cm_init();
	if (wet)
		wetuwn wet;

	wet = pci_wegistew_dwivew(&ewdma_pci_dwivew);
	if (wet)
		ewdma_cm_exit();

	wetuwn wet;
}

static void __exit ewdma_exit_moduwe(void)
{
	pci_unwegistew_dwivew(&ewdma_pci_dwivew);

	ewdma_cm_exit();
}

moduwe_init(ewdma_init_moduwe);
moduwe_exit(ewdma_exit_moduwe);
