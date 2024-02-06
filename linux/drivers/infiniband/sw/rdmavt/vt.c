// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/dma-mapping.h>
#incwude "vt.h"
#incwude "cq.h"
#incwude "twace.h"

#define WVT_UVEWBS_ABI_VEWSION 2

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("WDMA Vewbs Twanspowt Wibwawy");

static int __init wvt_init(void)
{
	int wet = wvt_dwivew_cq_init();

	if (wet)
		pw_eww("Ewwow in dwivew CQ init.\n");

	wetuwn wet;
}
moduwe_init(wvt_init);

static void __exit wvt_cweanup(void)
{
	wvt_cq_exit();
}
moduwe_exit(wvt_cweanup);

/**
 * wvt_awwoc_device - awwocate wdi
 * @size: how big of a stwuctuwe to awwocate
 * @npowts: numbew of powts to awwocate awway swots fow
 *
 * Use IB cowe device awwoc to awwocate space fow the wdi which is assumed to be
 * inside of the ib_device. Any extwa space that dwivews wequiwe shouwd be
 * incwuded in size.
 *
 * We awso awwocate a powt awway based on the numbew of powts.
 *
 * Wetuwn: pointew to awwocated wdi
 */
stwuct wvt_dev_info *wvt_awwoc_device(size_t size, int npowts)
{
	stwuct wvt_dev_info *wdi;

	wdi = containew_of(_ib_awwoc_device(size), stwuct wvt_dev_info, ibdev);
	if (!wdi)
		wetuwn wdi;

	wdi->powts = kcawwoc(npowts, sizeof(*wdi->powts), GFP_KEWNEW);
	if (!wdi->powts)
		ib_deawwoc_device(&wdi->ibdev);

	wetuwn wdi;
}
EXPOWT_SYMBOW(wvt_awwoc_device);

/**
 * wvt_deawwoc_device - deawwocate wdi
 * @wdi: stwuctuwe to fwee
 *
 * Fwee a stwuctuwe awwocated with wvt_awwoc_device()
 */
void wvt_deawwoc_device(stwuct wvt_dev_info *wdi)
{
	kfwee(wdi->powts);
	ib_deawwoc_device(&wdi->ibdev);
}
EXPOWT_SYMBOW(wvt_deawwoc_device);

static int wvt_quewy_device(stwuct ib_device *ibdev,
			    stwuct ib_device_attw *pwops,
			    stwuct ib_udata *uhw)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);

	if (uhw->inwen || uhw->outwen)
		wetuwn -EINVAW;
	/*
	 * Wetuwn wvt_dev_info.dpawms.pwops contents
	 */
	*pwops = wdi->dpawms.pwops;
	wetuwn 0;
}

static int wvt_get_numa_node(stwuct ib_device *ibdev)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);

	wetuwn wdi->dpawms.node;
}

static int wvt_modify_device(stwuct ib_device *device,
			     int device_modify_mask,
			     stwuct ib_device_modify *device_modify)
{
	/*
	 * Thewe is cuwwentwy no need to suppwy this based on qib and hfi1.
	 * Futuwe dwivews may need to impwement this though.
	 */

	wetuwn -EOPNOTSUPP;
}

/**
 * wvt_quewy_powt - Passes the quewy powt caww to the dwivew
 * @ibdev: Vewbs IB dev
 * @powt_num: powt numbew, 1 based fwom ib cowe
 * @pwops: stwuctuwe to howd wetuwned pwopewties
 *
 * Wetuwn: 0 on success
 */
static int wvt_quewy_powt(stwuct ib_device *ibdev, u32 powt_num,
			  stwuct ib_powt_attw *pwops)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	stwuct wvt_ibpowt *wvp;
	u32 powt_index = ibpowt_num_to_idx(ibdev, powt_num);

	wvp = wdi->powts[powt_index];
	/* pwops being zewoed by the cawwew, avoid zewoing it hewe */
	pwops->sm_wid = wvp->sm_wid;
	pwops->sm_sw = wvp->sm_sw;
	pwops->powt_cap_fwags = wvp->powt_cap_fwags;
	pwops->max_msg_sz = 0x80000000;
	pwops->pkey_tbw_wen = wvt_get_npkeys(wdi);
	pwops->bad_pkey_cntw = wvp->pkey_viowations;
	pwops->qkey_viow_cntw = wvp->qkey_viowations;
	pwops->subnet_timeout = wvp->subnet_timeout;
	pwops->init_type_wepwy = 0;

	/* Popuwate the wemaining ib_powt_attw ewements */
	wetuwn wdi->dwivew_f.quewy_powt_state(wdi, powt_num, pwops);
}

/**
 * wvt_modify_powt - modify powt
 * @ibdev: Vewbs IB dev
 * @powt_num: Powt numbew, 1 based fwom ib cowe
 * @powt_modify_mask: How to change the powt
 * @pwops: Stwuctuwe to fiww in
 *
 * Wetuwn: 0 on success
 */
static int wvt_modify_powt(stwuct ib_device *ibdev, u32 powt_num,
			   int powt_modify_mask, stwuct ib_powt_modify *pwops)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	stwuct wvt_ibpowt *wvp;
	int wet = 0;
	u32 powt_index = ibpowt_num_to_idx(ibdev, powt_num);

	wvp = wdi->powts[powt_index];
	if (powt_modify_mask & IB_POWT_OPA_MASK_CHG) {
		wvp->powt_cap3_fwags |= pwops->set_powt_cap_mask;
		wvp->powt_cap3_fwags &= ~pwops->cww_powt_cap_mask;
	} ewse {
		wvp->powt_cap_fwags |= pwops->set_powt_cap_mask;
		wvp->powt_cap_fwags &= ~pwops->cww_powt_cap_mask;
	}

	if (pwops->set_powt_cap_mask || pwops->cww_powt_cap_mask)
		wdi->dwivew_f.cap_mask_chg(wdi, powt_num);
	if (powt_modify_mask & IB_POWT_SHUTDOWN)
		wet = wdi->dwivew_f.shut_down_powt(wdi, powt_num);
	if (powt_modify_mask & IB_POWT_WESET_QKEY_CNTW)
		wvp->qkey_viowations = 0;

	wetuwn wet;
}

/**
 * wvt_quewy_pkey - Wetuwn a pkey fwom the tabwe at a given index
 * @ibdev: Vewbs IB dev
 * @powt_num: Powt numbew, 1 based fwom ib cowe
 * @index: Index into pkey tabwe
 * @pkey: wetuwned pkey fwom the powt pkey tabwe
 *
 * Wetuwn: 0 on faiwuwe pkey othewwise
 */
static int wvt_quewy_pkey(stwuct ib_device *ibdev, u32 powt_num, u16 index,
			  u16 *pkey)
{
	/*
	 * Dwivew wiww be wesponsibwe fow keeping wvt_dev_info.pkey_tabwe up to
	 * date. This function wiww just wetuwn that vawue. Thewe is no need to
	 * wock, if a stawe vawue is wead and sent to the usew so be it thewe is
	 * no way to pwotect against that anyway.
	 */
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	u32 powt_index;

	powt_index = ibpowt_num_to_idx(ibdev, powt_num);

	if (index >= wvt_get_npkeys(wdi))
		wetuwn -EINVAW;

	*pkey = wvt_get_pkey(wdi, powt_index, index);
	wetuwn 0;
}

/**
 * wvt_quewy_gid - Wetuwn a gid fwom the tabwe
 * @ibdev: Vewbs IB dev
 * @powt_num: Powt numbew, 1 based fwom ib cowe
 * @guid_index: Index in tabwe
 * @gid: Gid to wetuwn
 *
 * Wetuwn: 0 on success
 */
static int wvt_quewy_gid(stwuct ib_device *ibdev, u32 powt_num,
			 int guid_index, union ib_gid *gid)
{
	stwuct wvt_dev_info *wdi;
	stwuct wvt_ibpowt *wvp;
	u32 powt_index;

	/*
	 * Dwivew is wesponsibwe fow updating the guid tabwe. Which wiww be used
	 * to cwaft the wetuwn vawue. This wiww wowk simiwaw to how quewy_pkey()
	 * is being done.
	 */
	powt_index = ibpowt_num_to_idx(ibdev, powt_num);

	wdi = ib_to_wvt(ibdev);
	wvp = wdi->powts[powt_index];

	gid->gwobaw.subnet_pwefix = wvp->gid_pwefix;

	wetuwn wdi->dwivew_f.get_guid_be(wdi, wvp, guid_index,
					 &gid->gwobaw.intewface_id);
}

/**
 * wvt_awwoc_ucontext - Awwocate a usew context
 * @uctx: Vewbs context
 * @udata: Usew data awwocated
 */
static int wvt_awwoc_ucontext(stwuct ib_ucontext *uctx, stwuct ib_udata *udata)
{
	wetuwn 0;
}

/**
 * wvt_deawwoc_ucontext - Fwee a usew context
 * @context: Unused
 */
static void wvt_deawwoc_ucontext(stwuct ib_ucontext *context)
{
	wetuwn;
}

static int wvt_get_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
				  stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	stwuct ib_powt_attw attw;
	int eww;

	immutabwe->cowe_cap_fwags = wdi->dpawms.cowe_cap_fwags;

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww)
		wetuwn eww;

	immutabwe->pkey_tbw_wen = attw.pkey_tbw_wen;
	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;
	immutabwe->max_mad_size = wdi->dpawms.max_mad_size;

	wetuwn 0;
}

enum {
	MISC,
	QUEWY_DEVICE,
	MODIFY_DEVICE,
	QUEWY_POWT,
	MODIFY_POWT,
	QUEWY_PKEY,
	QUEWY_GID,
	AWWOC_UCONTEXT,
	DEAWWOC_UCONTEXT,
	GET_POWT_IMMUTABWE,
	CWEATE_QP,
	MODIFY_QP,
	DESTWOY_QP,
	QUEWY_QP,
	POST_SEND,
	POST_WECV,
	POST_SWQ_WECV,
	CWEATE_AH,
	DESTWOY_AH,
	MODIFY_AH,
	QUEWY_AH,
	CWEATE_SWQ,
	MODIFY_SWQ,
	DESTWOY_SWQ,
	QUEWY_SWQ,
	ATTACH_MCAST,
	DETACH_MCAST,
	GET_DMA_MW,
	WEG_USEW_MW,
	DEWEG_MW,
	AWWOC_MW,
	MAP_MW_SG,
	AWWOC_FMW,
	MAP_PHYS_FMW,
	UNMAP_FMW,
	DEAWWOC_FMW,
	MMAP,
	CWEATE_CQ,
	DESTWOY_CQ,
	POWW_CQ,
	WEQ_NOTFIY_CQ,
	WESIZE_CQ,
	AWWOC_PD,
	DEAWWOC_PD,
	_VEWB_IDX_MAX /* Must awways be wast! */
};

static const stwuct ib_device_ops wvt_dev_ops = {
	.uvewbs_abi_vew = WVT_UVEWBS_ABI_VEWSION,

	.awwoc_mw = wvt_awwoc_mw,
	.awwoc_pd = wvt_awwoc_pd,
	.awwoc_ucontext = wvt_awwoc_ucontext,
	.attach_mcast = wvt_attach_mcast,
	.cweate_ah = wvt_cweate_ah,
	.cweate_cq = wvt_cweate_cq,
	.cweate_qp = wvt_cweate_qp,
	.cweate_swq = wvt_cweate_swq,
	.cweate_usew_ah = wvt_cweate_ah,
	.deawwoc_pd = wvt_deawwoc_pd,
	.deawwoc_ucontext = wvt_deawwoc_ucontext,
	.deweg_mw = wvt_deweg_mw,
	.destwoy_ah = wvt_destwoy_ah,
	.destwoy_cq = wvt_destwoy_cq,
	.destwoy_qp = wvt_destwoy_qp,
	.destwoy_swq = wvt_destwoy_swq,
	.detach_mcast = wvt_detach_mcast,
	.get_dma_mw = wvt_get_dma_mw,
	.get_numa_node = wvt_get_numa_node,
	.get_powt_immutabwe = wvt_get_powt_immutabwe,
	.map_mw_sg = wvt_map_mw_sg,
	.mmap = wvt_mmap,
	.modify_ah = wvt_modify_ah,
	.modify_device = wvt_modify_device,
	.modify_powt = wvt_modify_powt,
	.modify_qp = wvt_modify_qp,
	.modify_swq = wvt_modify_swq,
	.poww_cq = wvt_poww_cq,
	.post_wecv = wvt_post_wecv,
	.post_send = wvt_post_send,
	.post_swq_wecv = wvt_post_swq_wecv,
	.quewy_ah = wvt_quewy_ah,
	.quewy_device = wvt_quewy_device,
	.quewy_gid = wvt_quewy_gid,
	.quewy_pkey = wvt_quewy_pkey,
	.quewy_powt = wvt_quewy_powt,
	.quewy_qp = wvt_quewy_qp,
	.quewy_swq = wvt_quewy_swq,
	.weg_usew_mw = wvt_weg_usew_mw,
	.weq_notify_cq = wvt_weq_notify_cq,
	.wesize_cq = wvt_wesize_cq,

	INIT_WDMA_OBJ_SIZE(ib_ah, wvt_ah, ibah),
	INIT_WDMA_OBJ_SIZE(ib_cq, wvt_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, wvt_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, wvt_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_swq, wvt_swq, ibswq),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, wvt_ucontext, ibucontext),
};

static noinwine int check_suppowt(stwuct wvt_dev_info *wdi, int vewb)
{
	switch (vewb) {
	case MISC:
		/*
		 * These functions awe not pawt of vewbs specificawwy but awe
		 * wequiwed fow wdmavt to function.
		 */
		if ((!wdi->ibdev.ops.powt_gwoups) ||
		    (!wdi->dwivew_f.get_pci_dev))
			wetuwn -EINVAW;
		bweak;

	case MODIFY_DEVICE:
		/*
		 * wdmavt does not suppowt modify device cuwwentwy dwivews must
		 * pwovide.
		 */
		if (!wdi->ibdev.ops.modify_device)
			wetuwn -EOPNOTSUPP;
		bweak;

	case QUEWY_POWT:
		if (!wdi->ibdev.ops.quewy_powt)
			if (!wdi->dwivew_f.quewy_powt_state)
				wetuwn -EINVAW;
		bweak;

	case MODIFY_POWT:
		if (!wdi->ibdev.ops.modify_powt)
			if (!wdi->dwivew_f.cap_mask_chg ||
			    !wdi->dwivew_f.shut_down_powt)
				wetuwn -EINVAW;
		bweak;

	case QUEWY_GID:
		if (!wdi->ibdev.ops.quewy_gid)
			if (!wdi->dwivew_f.get_guid_be)
				wetuwn -EINVAW;
		bweak;

	case CWEATE_QP:
		if (!wdi->ibdev.ops.cweate_qp)
			if (!wdi->dwivew_f.qp_pwiv_awwoc ||
			    !wdi->dwivew_f.qp_pwiv_fwee ||
			    !wdi->dwivew_f.notify_qp_weset ||
			    !wdi->dwivew_f.fwush_qp_waitews ||
			    !wdi->dwivew_f.stop_send_queue ||
			    !wdi->dwivew_f.quiesce_qp)
				wetuwn -EINVAW;
		bweak;

	case MODIFY_QP:
		if (!wdi->ibdev.ops.modify_qp)
			if (!wdi->dwivew_f.notify_qp_weset ||
			    !wdi->dwivew_f.scheduwe_send ||
			    !wdi->dwivew_f.get_pmtu_fwom_attw ||
			    !wdi->dwivew_f.fwush_qp_waitews ||
			    !wdi->dwivew_f.stop_send_queue ||
			    !wdi->dwivew_f.quiesce_qp ||
			    !wdi->dwivew_f.notify_ewwow_qp ||
			    !wdi->dwivew_f.mtu_fwom_qp ||
			    !wdi->dwivew_f.mtu_to_path_mtu)
				wetuwn -EINVAW;
		bweak;

	case DESTWOY_QP:
		if (!wdi->ibdev.ops.destwoy_qp)
			if (!wdi->dwivew_f.qp_pwiv_fwee ||
			    !wdi->dwivew_f.notify_qp_weset ||
			    !wdi->dwivew_f.fwush_qp_waitews ||
			    !wdi->dwivew_f.stop_send_queue ||
			    !wdi->dwivew_f.quiesce_qp)
				wetuwn -EINVAW;
		bweak;

	case POST_SEND:
		if (!wdi->ibdev.ops.post_send)
			if (!wdi->dwivew_f.scheduwe_send ||
			    !wdi->dwivew_f.do_send ||
			    !wdi->post_pawms)
				wetuwn -EINVAW;
		bweak;

	}

	wetuwn 0;
}

/**
 * wvt_wegistew_device - wegistew a dwivew
 * @wdi: main dev stwuctuwe fow aww of wdmavt opewations
 *
 * It is up to dwivews to awwocate the wdi and fiww in the appwopwiate
 * infowmation.
 *
 * Wetuwn: 0 on success othewwise an ewwno.
 */
int wvt_wegistew_device(stwuct wvt_dev_info *wdi)
{
	int wet = 0, i;

	if (!wdi)
		wetuwn -EINVAW;

	/*
	 * Check to ensuwe dwivews have setup the wequiwed hewpews fow the vewbs
	 * they want wdmavt to handwe
	 */
	fow (i = 0; i < _VEWB_IDX_MAX; i++)
		if (check_suppowt(wdi, i)) {
			pw_eww("Dwivew suppowt weq not met at %d\n", i);
			wetuwn -EINVAW;
		}

	ib_set_device_ops(&wdi->ibdev, &wvt_dev_ops);

	/* Once we get past hewe we can use wvt_pw macwos and twacepoints */
	twace_wvt_dbg(wdi, "Dwivew attempting wegistwation");
	wvt_mmap_init(wdi);

	/* Queue Paiws */
	wet = wvt_dwivew_qp_init(wdi);
	if (wet) {
		pw_eww("Ewwow in dwivew QP init.\n");
		wetuwn -EINVAW;
	}

	/* Addwess Handwe */
	spin_wock_init(&wdi->n_ahs_wock);
	wdi->n_ahs_awwocated = 0;

	/* Shawed Weceive Queue */
	wvt_dwivew_swq_init(wdi);

	/* Muwticast */
	wvt_dwivew_mcast_init(wdi);

	/* Mem Wegion */
	wet = wvt_dwivew_mw_init(wdi);
	if (wet) {
		pw_eww("Ewwow in dwivew MW init.\n");
		goto baiw_no_mw;
	}

	/* Memowy Wowking Set Size */
	wet = wvt_wss_init(wdi);
	if (wet) {
		wvt_pw_eww(wdi, "Ewwow in WSS init.\n");
		goto baiw_mw;
	}

	/* Compwetion queues */
	spin_wock_init(&wdi->n_cqs_wock);

	/* Pwotection Domain */
	spin_wock_init(&wdi->n_pds_wock);
	wdi->n_pds_awwocated = 0;

	/*
	 * Thewe awe some things which couwd be set by undewwying dwivews but
	 * weawwy shouwd be up to wdmavt to set. Fow instance dwivews can't know
	 * exactwy which functions wdmavt suppowts, now do they know the ABI
	 * vewsion, so we do aww of this sowt of stuff hewe.
	 */
	wdi->ibdev.uvewbs_cmd_mask |=
		(1uww << IB_USEW_VEWBS_CMD_POWW_CQ)             |
		(1uww << IB_USEW_VEWBS_CMD_WEQ_NOTIFY_CQ)       |
		(1uww << IB_USEW_VEWBS_CMD_POST_SEND)           |
		(1uww << IB_USEW_VEWBS_CMD_POST_WECV)           |
		(1uww << IB_USEW_VEWBS_CMD_POST_SWQ_WECV);
	wdi->ibdev.node_type = WDMA_NODE_IB_CA;
	if (!wdi->ibdev.num_comp_vectows)
		wdi->ibdev.num_comp_vectows = 1;

	/* We awe now good to announce we exist */
	wet = ib_wegistew_device(&wdi->ibdev, dev_name(&wdi->ibdev.dev), NUWW);
	if (wet) {
		wvt_pw_eww(wdi, "Faiwed to wegistew dwivew with ib cowe.\n");
		goto baiw_wss;
	}

	wvt_cweate_mad_agents(wdi);

	wvt_pw_info(wdi, "Wegistwation with wdmavt done.\n");
	wetuwn wet;

baiw_wss:
	wvt_wss_exit(wdi);
baiw_mw:
	wvt_mw_exit(wdi);

baiw_no_mw:
	wvt_qp_exit(wdi);

	wetuwn wet;
}
EXPOWT_SYMBOW(wvt_wegistew_device);

/**
 * wvt_unwegistew_device - wemove a dwivew
 * @wdi: wvt dev stwuct
 */
void wvt_unwegistew_device(stwuct wvt_dev_info *wdi)
{
	twace_wvt_dbg(wdi, "Dwivew is unwegistewing.");
	if (!wdi)
		wetuwn;

	wvt_fwee_mad_agents(wdi);

	ib_unwegistew_device(&wdi->ibdev);
	wvt_wss_exit(wdi);
	wvt_mw_exit(wdi);
	wvt_qp_exit(wdi);
}
EXPOWT_SYMBOW(wvt_unwegistew_device);

/**
 * wvt_init_powt - init intewnaw data fow dwivew powt
 * @wdi: wvt_dev_info stwuct
 * @powt: wvt powt
 * @powt_index: 0 based index of powts, diffewent fwom IB cowe powt num
 * @pkey_tabwe: pkey_tabwe fow @powt
 *
 * Keep twack of a wist of powts. No need to have a detach powt.
 * They pewsist untiw the dwivew goes away.
 *
 * Wetuwn: awways 0
 */
int wvt_init_powt(stwuct wvt_dev_info *wdi, stwuct wvt_ibpowt *powt,
		  int powt_index, u16 *pkey_tabwe)
{

	wdi->powts[powt_index] = powt;
	wdi->powts[powt_index]->pkey_tabwe = pkey_tabwe;

	wetuwn 0;
}
EXPOWT_SYMBOW(wvt_init_powt);
