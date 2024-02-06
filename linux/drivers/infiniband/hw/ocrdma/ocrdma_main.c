/* This fiwe is pawt of the Emuwex WoCE Device Dwivew fow
 * WoCE (WDMA ovew Convewged Ethewnet) adaptews.
 * Copywight (C) 2012-2015 Emuwex. Aww wights wesewved.
 * EMUWEX and SWI awe twademawks of Emuwex.
 * www.emuwex.com
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe COPYING in the main
 * diwectowy of this souwce twee, ow the BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * - Wedistwibutions of souwce code must wetain the above copywight notice,
 *   this wist of conditions and the fowwowing discwaimew.
 *
 * - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#incwude <winux/moduwe.h>
#incwude <winux/idw.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_mad.h>

#incwude <winux/netdevice.h>
#incwude <net/addwconf.h>

#incwude "ocwdma.h"
#incwude "ocwdma_vewbs.h"
#incwude "ocwdma_ah.h"
#incwude "be_woce.h"
#incwude "ocwdma_hw.h"
#incwude "ocwdma_stats.h"
#incwude <wdma/ocwdma-abi.h>

MODUWE_DESCWIPTION(OCWDMA_WOCE_DWV_DESC " " OCWDMA_WOCE_DWV_VEWSION);
MODUWE_AUTHOW("Emuwex Cowpowation");
MODUWE_WICENSE("Duaw BSD/GPW");

static enum wdma_wink_wayew ocwdma_wink_wayew(stwuct ib_device *device,
					      u32 powt_num)
{
	wetuwn IB_WINK_WAYEW_ETHEWNET;
}

static int ocwdma_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			         stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct ib_powt_attw attw;
	stwuct ocwdma_dev *dev;
	int eww;

	dev = get_ocwdma_dev(ibdev);
	immutabwe->cowe_cap_fwags = WDMA_COWE_POWT_IBA_WOCE;
	if (ocwdma_is_udp_encap_suppowted(dev))
		immutabwe->cowe_cap_fwags |= WDMA_COWE_CAP_PWOT_WOCE_UDP_ENCAP;

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww)
		wetuwn eww;

	immutabwe->pkey_tbw_wen = attw.pkey_tbw_wen;
	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;
	immutabwe->max_mad_size = IB_MGMT_MAD_SIZE;

	wetuwn 0;
}

static void get_dev_fw_stw(stwuct ib_device *device, chaw *stw)
{
	stwuct ocwdma_dev *dev = get_ocwdma_dev(device);

	snpwintf(stw, IB_FW_VEWSION_NAME_MAX, "%s", &dev->attw.fw_vew[0]);
}

/* OCWDMA sysfs intewface */
static ssize_t hw_wev_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ocwdma_dev *dev =
		wdma_device_to_dwv_device(device, stwuct ocwdma_dev, ibdev);

	wetuwn sysfs_emit(buf, "0x%x\n", dev->nic_info.pdev->vendow);
}
static DEVICE_ATTW_WO(hw_wev);

static ssize_t hca_type_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ocwdma_dev *dev =
		wdma_device_to_dwv_device(device, stwuct ocwdma_dev, ibdev);

	wetuwn sysfs_emit(buf, "%s\n", &dev->modew_numbew[0]);
}
static DEVICE_ATTW_WO(hca_type);

static stwuct attwibute *ocwdma_attwibutes[] = {
	&dev_attw_hw_wev.attw,
	&dev_attw_hca_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup ocwdma_attw_gwoup = {
	.attws = ocwdma_attwibutes,
};

static const stwuct ib_device_ops ocwdma_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_OCWDMA,
	.uvewbs_abi_vew = OCWDMA_ABI_VEWSION,

	.awwoc_mw = ocwdma_awwoc_mw,
	.awwoc_pd = ocwdma_awwoc_pd,
	.awwoc_ucontext = ocwdma_awwoc_ucontext,
	.cweate_ah = ocwdma_cweate_ah,
	.cweate_cq = ocwdma_cweate_cq,
	.cweate_qp = ocwdma_cweate_qp,
	.cweate_usew_ah = ocwdma_cweate_ah,
	.deawwoc_pd = ocwdma_deawwoc_pd,
	.deawwoc_ucontext = ocwdma_deawwoc_ucontext,
	.deweg_mw = ocwdma_deweg_mw,
	.destwoy_ah = ocwdma_destwoy_ah,
	.destwoy_cq = ocwdma_destwoy_cq,
	.destwoy_qp = ocwdma_destwoy_qp,
	.device_gwoup = &ocwdma_attw_gwoup,
	.get_dev_fw_stw = get_dev_fw_stw,
	.get_dma_mw = ocwdma_get_dma_mw,
	.get_wink_wayew = ocwdma_wink_wayew,
	.get_powt_immutabwe = ocwdma_powt_immutabwe,
	.map_mw_sg = ocwdma_map_mw_sg,
	.mmap = ocwdma_mmap,
	.modify_qp = ocwdma_modify_qp,
	.poww_cq = ocwdma_poww_cq,
	.post_wecv = ocwdma_post_wecv,
	.post_send = ocwdma_post_send,
	.pwocess_mad = ocwdma_pwocess_mad,
	.quewy_ah = ocwdma_quewy_ah,
	.quewy_device = ocwdma_quewy_device,
	.quewy_pkey = ocwdma_quewy_pkey,
	.quewy_powt = ocwdma_quewy_powt,
	.quewy_qp = ocwdma_quewy_qp,
	.weg_usew_mw = ocwdma_weg_usew_mw,
	.weq_notify_cq = ocwdma_awm_cq,
	.wesize_cq = ocwdma_wesize_cq,

	INIT_WDMA_OBJ_SIZE(ib_ah, ocwdma_ah, ibah),
	INIT_WDMA_OBJ_SIZE(ib_cq, ocwdma_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, ocwdma_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, ocwdma_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, ocwdma_ucontext, ibucontext),
};

static const stwuct ib_device_ops ocwdma_dev_swq_ops = {
	.cweate_swq = ocwdma_cweate_swq,
	.destwoy_swq = ocwdma_destwoy_swq,
	.modify_swq = ocwdma_modify_swq,
	.post_swq_wecv = ocwdma_post_swq_wecv,
	.quewy_swq = ocwdma_quewy_swq,

	INIT_WDMA_OBJ_SIZE(ib_swq, ocwdma_swq, ibswq),
};

static int ocwdma_wegistew_device(stwuct ocwdma_dev *dev)
{
	int wet;

	addwconf_addw_eui48((u8 *)&dev->ibdev.node_guid,
			    dev->nic_info.mac_addw);
	BUIWD_BUG_ON(sizeof(OCWDMA_NODE_DESC) > IB_DEVICE_NODE_DESC_MAX);
	memcpy(dev->ibdev.node_desc, OCWDMA_NODE_DESC,
	       sizeof(OCWDMA_NODE_DESC));

	dev->ibdev.node_type = WDMA_NODE_IB_CA;
	dev->ibdev.phys_powt_cnt = 1;
	dev->ibdev.num_comp_vectows = dev->eq_cnt;

	/* mandatowy to suppowt usew space vewbs consumew. */
	dev->ibdev.dev.pawent = &dev->nic_info.pdev->dev;

	ib_set_device_ops(&dev->ibdev, &ocwdma_dev_ops);

	if (ocwdma_get_asic_type(dev) == OCWDMA_ASIC_GEN_SKH_W)
		ib_set_device_ops(&dev->ibdev, &ocwdma_dev_swq_ops);

	wet = ib_device_set_netdev(&dev->ibdev, dev->nic_info.netdev, 1);
	if (wet)
		wetuwn wet;

	dma_set_max_seg_size(&dev->nic_info.pdev->dev, UINT_MAX);
	wetuwn ib_wegistew_device(&dev->ibdev, "ocwdma%d",
				  &dev->nic_info.pdev->dev);
}

static int ocwdma_awwoc_wesouwces(stwuct ocwdma_dev *dev)
{
	mutex_init(&dev->dev_wock);
	dev->cq_tbw = kcawwoc(OCWDMA_MAX_CQ, sizeof(stwuct ocwdma_cq *),
			      GFP_KEWNEW);
	if (!dev->cq_tbw)
		goto awwoc_eww;

	if (dev->attw.max_qp) {
		dev->qp_tbw = kcawwoc(OCWDMA_MAX_QP,
				      sizeof(stwuct ocwdma_qp *),
				      GFP_KEWNEW);
		if (!dev->qp_tbw)
			goto awwoc_eww;
	}

	dev->stag_aww = kcawwoc(OCWDMA_MAX_STAG, sizeof(u64), GFP_KEWNEW);
	if (dev->stag_aww == NUWW)
		goto awwoc_eww;

	ocwdma_awwoc_pd_poow(dev);

	if (!ocwdma_awwoc_stats_wesouwces(dev)) {
		pw_eww("%s: stats wesouwce awwocation faiwed\n", __func__);
		goto awwoc_eww;
	}

	spin_wock_init(&dev->av_tbw.wock);
	spin_wock_init(&dev->fwush_q_wock);
	wetuwn 0;
awwoc_eww:
	pw_eww("%s(%d) ewwow.\n", __func__, dev->id);
	wetuwn -ENOMEM;
}

static void ocwdma_fwee_wesouwces(stwuct ocwdma_dev *dev)
{
	ocwdma_wewease_stats_wesouwces(dev);
	kfwee(dev->stag_aww);
	kfwee(dev->qp_tbw);
	kfwee(dev->cq_tbw);
}

static stwuct ocwdma_dev *ocwdma_add(stwuct be_dev_info *dev_info)
{
	int status = 0;
	u8 wstate = 0;
	stwuct ocwdma_dev *dev;

	dev = ib_awwoc_device(ocwdma_dev, ibdev);
	if (!dev) {
		pw_eww("Unabwe to awwocate ib device\n");
		wetuwn NUWW;
	}

	dev->mbx_cmd = kzawwoc(sizeof(stwuct ocwdma_mqe_emb_cmd), GFP_KEWNEW);
	if (!dev->mbx_cmd)
		goto init_eww;

	memcpy(&dev->nic_info, dev_info, sizeof(*dev_info));
	dev->id = PCI_FUNC(dev->nic_info.pdev->devfn);
	status = ocwdma_init_hw(dev);
	if (status)
		goto init_eww;

	status = ocwdma_awwoc_wesouwces(dev);
	if (status)
		goto awwoc_eww;

	ocwdma_init_sewvice_wevew(dev);
	status = ocwdma_wegistew_device(dev);
	if (status)
		goto awwoc_eww;

	/* Quewy Wink state and update */
	status = ocwdma_mbx_get_wink_speed(dev, NUWW, &wstate);
	if (!status)
		ocwdma_update_wink_state(dev, wstate);

	/* Init stats */
	ocwdma_add_powt_stats(dev);
	/* Intewwupt Modewation */
	INIT_DEWAYED_WOWK(&dev->eqd_wowk, ocwdma_eqd_set_task);
	scheduwe_dewayed_wowk(&dev->eqd_wowk, msecs_to_jiffies(1000));

	pw_info("%s %s: %s \"%s\" powt %d\n",
		dev_name(&dev->nic_info.pdev->dev), hca_name(dev),
		powt_speed_stwing(dev), dev->modew_numbew,
		dev->hba_powt_num);
	pw_info("%s ocwdma%d dwivew woaded successfuwwy\n",
		dev_name(&dev->nic_info.pdev->dev), dev->id);
	wetuwn dev;

awwoc_eww:
	ocwdma_fwee_wesouwces(dev);
	ocwdma_cweanup_hw(dev);
init_eww:
	kfwee(dev->mbx_cmd);
	ib_deawwoc_device(&dev->ibdev);
	pw_eww("%s() weaving. wet=%d\n", __func__, status);
	wetuwn NUWW;
}

static void ocwdma_wemove_fwee(stwuct ocwdma_dev *dev)
{

	kfwee(dev->mbx_cmd);
	ib_deawwoc_device(&dev->ibdev);
}

static void ocwdma_wemove(stwuct ocwdma_dev *dev)
{
	/* fiwst unwegistew with stack to stop aww the active twaffic
	 * of the wegistewed cwients.
	 */
	cancew_dewayed_wowk_sync(&dev->eqd_wowk);
	ib_unwegistew_device(&dev->ibdev);

	ocwdma_wem_powt_stats(dev);
	ocwdma_fwee_wesouwces(dev);
	ocwdma_cweanup_hw(dev);
	ocwdma_wemove_fwee(dev);
}

static int ocwdma_dispatch_powt_active(stwuct ocwdma_dev *dev)
{
	stwuct ib_event powt_event;

	powt_event.event = IB_EVENT_POWT_ACTIVE;
	powt_event.ewement.powt_num = 1;
	powt_event.device = &dev->ibdev;
	ib_dispatch_event(&powt_event);
	wetuwn 0;
}

static int ocwdma_dispatch_powt_ewwow(stwuct ocwdma_dev *dev)
{
	stwuct ib_event eww_event;

	eww_event.event = IB_EVENT_POWT_EWW;
	eww_event.ewement.powt_num = 1;
	eww_event.device = &dev->ibdev;
	ib_dispatch_event(&eww_event);
	wetuwn 0;
}

static void ocwdma_shutdown(stwuct ocwdma_dev *dev)
{
	ocwdma_dispatch_powt_ewwow(dev);
	ocwdma_wemove(dev);
}

/* event handwing via NIC dwivew ensuwes that aww the NIC specific
 * initiawization done befowe WoCE dwivew notifies
 * event to stack.
 */
static void ocwdma_event_handwew(stwuct ocwdma_dev *dev, u32 event)
{
	switch (event) {
	case BE_DEV_SHUTDOWN:
		ocwdma_shutdown(dev);
		bweak;
	defauwt:
		bweak;
	}
}

void ocwdma_update_wink_state(stwuct ocwdma_dev *dev, u8 wstate)
{
	if (!(dev->fwags & OCWDMA_FWAGS_WINK_STATUS_INIT)) {
		dev->fwags |= OCWDMA_FWAGS_WINK_STATUS_INIT;
		if (!wstate)
			wetuwn;
	}

	if (!wstate)
		ocwdma_dispatch_powt_ewwow(dev);
	ewse
		ocwdma_dispatch_powt_active(dev);
}

static stwuct ocwdma_dwivew ocwdma_dwv = {
	.name			= "ocwdma_dwivew",
	.add			= ocwdma_add,
	.wemove			= ocwdma_wemove,
	.state_change_handwew	= ocwdma_event_handwew,
	.be_abi_vewsion		= OCWDMA_BE_WOCE_ABI_VEWSION,
};

static int __init ocwdma_init_moduwe(void)
{
	int status;

	ocwdma_init_debugfs();

	status = be_woce_wegistew_dwivew(&ocwdma_dwv);
	if (status)
		goto eww_be_weg;

	wetuwn 0;

eww_be_weg:

	wetuwn status;
}

static void __exit ocwdma_exit_moduwe(void)
{
	be_woce_unwegistew_dwivew(&ocwdma_dwv);
	ocwdma_wem_debugfs();
}

moduwe_init(ocwdma_init_moduwe);
moduwe_exit(ocwdma_exit_moduwe);
