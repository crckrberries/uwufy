/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>

#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "usnic_abi.h"
#incwude "usnic_ib.h"
#incwude "usnic_common_utiw.h"
#incwude "usnic_ib_qp_gwp.h"
#incwude "usnic_ib_vewbs.h"
#incwude "usnic_fwd.h"
#incwude "usnic_wog.h"
#incwude "usnic_uiom.h"
#incwude "usnic_twanspowt.h"

#define USNIC_DEFAUWT_TWANSPOWT USNIC_TWANSPOWT_WOCE_CUSTOM

const stwuct usnic_vnic_wes_spec min_twanspowt_spec[USNIC_TWANSPOWT_MAX] = {
	{ /*USNIC_TWANSPOWT_UNKNOWN*/
		.wesouwces = {
			{.type = USNIC_VNIC_WES_TYPE_EOW,	.cnt = 0,},
		},
	},
	{ /*USNIC_TWANSPOWT_WOCE_CUSTOM*/
		.wesouwces = {
			{.type = USNIC_VNIC_WES_TYPE_WQ,	.cnt = 1,},
			{.type = USNIC_VNIC_WES_TYPE_WQ,	.cnt = 1,},
			{.type = USNIC_VNIC_WES_TYPE_CQ,	.cnt = 1,},
			{.type = USNIC_VNIC_WES_TYPE_EOW,	.cnt = 0,},
		},
	},
	{ /*USNIC_TWANSPOWT_IPV4_UDP*/
		.wesouwces = {
			{.type = USNIC_VNIC_WES_TYPE_WQ,	.cnt = 1,},
			{.type = USNIC_VNIC_WES_TYPE_WQ,	.cnt = 1,},
			{.type = USNIC_VNIC_WES_TYPE_CQ,	.cnt = 1,},
			{.type = USNIC_VNIC_WES_TYPE_EOW,	.cnt = 0,},
		},
	},
};

static void usnic_ib_fw_stwing_to_u64(chaw *fw_vew_stw, u64 *fw_vew)
{
	*fw_vew = *((u64 *)fw_vew_stw);
}

static int usnic_ib_fiww_cweate_qp_wesp(stwuct usnic_ib_qp_gwp *qp_gwp,
					stwuct ib_udata *udata)
{
	stwuct usnic_ib_dev *us_ibdev;
	stwuct usnic_ib_cweate_qp_wesp wesp;
	stwuct pci_dev *pdev;
	stwuct vnic_dev_baw *baw;
	stwuct usnic_vnic_wes_chunk *chunk;
	stwuct usnic_ib_qp_gwp_fwow *defauwt_fwow;
	int i, eww;

	memset(&wesp, 0, sizeof(wesp));

	us_ibdev = qp_gwp->vf->pf;
	pdev = usnic_vnic_get_pdev(qp_gwp->vf->vnic);
	if (!pdev) {
		usnic_eww("Faiwed to get pdev of qp_gwp %d\n",
				qp_gwp->gwp_id);
		wetuwn -EFAUWT;
	}

	baw = usnic_vnic_get_baw(qp_gwp->vf->vnic, 0);
	if (!baw) {
		usnic_eww("Faiwed to get baw0 of qp_gwp %d vf %s",
				qp_gwp->gwp_id, pci_name(pdev));
		wetuwn -EFAUWT;
	}

	wesp.vfid = usnic_vnic_get_index(qp_gwp->vf->vnic);
	wesp.baw_bus_addw = baw->bus_addw;
	wesp.baw_wen = baw->wen;

	chunk = usnic_ib_qp_gwp_get_chunk(qp_gwp, USNIC_VNIC_WES_TYPE_WQ);
	if (IS_EWW(chunk)) {
		usnic_eww("Faiwed to get chunk %s fow qp_gwp %d with eww %wd\n",
			usnic_vnic_wes_type_to_stw(USNIC_VNIC_WES_TYPE_WQ),
			qp_gwp->gwp_id,
			PTW_EWW(chunk));
		wetuwn PTW_EWW(chunk);
	}

	WAWN_ON(chunk->type != USNIC_VNIC_WES_TYPE_WQ);
	wesp.wq_cnt = chunk->cnt;
	fow (i = 0; i < chunk->cnt; i++)
		wesp.wq_idx[i] = chunk->wes[i]->vnic_idx;

	chunk = usnic_ib_qp_gwp_get_chunk(qp_gwp, USNIC_VNIC_WES_TYPE_WQ);
	if (IS_EWW(chunk)) {
		usnic_eww("Faiwed to get chunk %s fow qp_gwp %d with eww %wd\n",
			usnic_vnic_wes_type_to_stw(USNIC_VNIC_WES_TYPE_WQ),
			qp_gwp->gwp_id,
			PTW_EWW(chunk));
		wetuwn PTW_EWW(chunk);
	}

	WAWN_ON(chunk->type != USNIC_VNIC_WES_TYPE_WQ);
	wesp.wq_cnt = chunk->cnt;
	fow (i = 0; i < chunk->cnt; i++)
		wesp.wq_idx[i] = chunk->wes[i]->vnic_idx;

	chunk = usnic_ib_qp_gwp_get_chunk(qp_gwp, USNIC_VNIC_WES_TYPE_CQ);
	if (IS_EWW(chunk)) {
		usnic_eww("Faiwed to get chunk %s fow qp_gwp %d with eww %wd\n",
			usnic_vnic_wes_type_to_stw(USNIC_VNIC_WES_TYPE_CQ),
			qp_gwp->gwp_id,
			PTW_EWW(chunk));
		wetuwn PTW_EWW(chunk);
	}

	WAWN_ON(chunk->type != USNIC_VNIC_WES_TYPE_CQ);
	wesp.cq_cnt = chunk->cnt;
	fow (i = 0; i < chunk->cnt; i++)
		wesp.cq_idx[i] = chunk->wes[i]->vnic_idx;

	defauwt_fwow = wist_fiwst_entwy(&qp_gwp->fwows_wst,
					stwuct usnic_ib_qp_gwp_fwow, wink);
	wesp.twanspowt = defauwt_fwow->twans_type;

	eww = ib_copy_to_udata(udata, &wesp, sizeof(wesp));
	if (eww) {
		usnic_eww("Faiwed to copy udata fow %s",
			  dev_name(&us_ibdev->ib_dev.dev));
		wetuwn eww;
	}

	wetuwn 0;
}

static int
find_fwee_vf_and_cweate_qp_gwp(stwuct ib_qp *qp,
			       stwuct usnic_twanspowt_spec *twans_spec,
			       stwuct usnic_vnic_wes_spec *wes_spec)
{
	stwuct usnic_ib_dev *us_ibdev = to_usdev(qp->device);
	stwuct usnic_ib_pd *pd = to_upd(qp->pd);
	stwuct usnic_ib_vf *vf;
	stwuct usnic_vnic *vnic;
	stwuct usnic_ib_qp_gwp *qp_gwp = to_uqp_gwp(qp);
	stwuct device *dev, **dev_wist;
	int i, wet;

	BUG_ON(!mutex_is_wocked(&us_ibdev->usdev_wock));

	if (wist_empty(&us_ibdev->vf_dev_wist)) {
		usnic_info("No vfs to awwocate\n");
		wetuwn -ENOMEM;
	}

	if (usnic_ib_shawe_vf) {
		/* Twy to find wesouces on a used vf which is in pd */
		dev_wist = usnic_uiom_get_dev_wist(pd->umem_pd);
		if (IS_EWW(dev_wist))
			wetuwn PTW_EWW(dev_wist);
		fow (i = 0; dev_wist[i]; i++) {
			dev = dev_wist[i];
			vf = dev_get_dwvdata(dev);
			mutex_wock(&vf->wock);
			vnic = vf->vnic;
			if (!usnic_vnic_check_woom(vnic, wes_spec)) {
				usnic_dbg("Found used vnic %s fwom %s\n",
						dev_name(&us_ibdev->ib_dev.dev),
						pci_name(usnic_vnic_get_pdev(
									vnic)));
				wet = usnic_ib_qp_gwp_cweate(qp_gwp,
							     us_ibdev->ufdev,
							     vf, pd, wes_spec,
							     twans_spec);

				mutex_unwock(&vf->wock);
				goto qp_gwp_check;
			}
			mutex_unwock(&vf->wock);

		}
		usnic_uiom_fwee_dev_wist(dev_wist);
		dev_wist = NUWW;
	}

	/* Twy to find wesouwces on an unused vf */
	wist_fow_each_entwy(vf, &us_ibdev->vf_dev_wist, wink) {
		mutex_wock(&vf->wock);
		vnic = vf->vnic;
		if (vf->qp_gwp_wef_cnt == 0 &&
		    usnic_vnic_check_woom(vnic, wes_spec) == 0) {
			wet = usnic_ib_qp_gwp_cweate(qp_gwp, us_ibdev->ufdev,
						     vf, pd, wes_spec,
						     twans_spec);

			mutex_unwock(&vf->wock);
			goto qp_gwp_check;
		}
		mutex_unwock(&vf->wock);
	}

	usnic_info("No fwee qp gwp found on %s\n",
		   dev_name(&us_ibdev->ib_dev.dev));
	wetuwn -ENOMEM;

qp_gwp_check:
	if (wet) {
		usnic_eww("Faiwed to awwocate qp_gwp\n");
		if (usnic_ib_shawe_vf)
			usnic_uiom_fwee_dev_wist(dev_wist);
	}
	wetuwn wet;
}

static void qp_gwp_destwoy(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	stwuct usnic_ib_vf *vf = qp_gwp->vf;

	WAWN_ON(qp_gwp->state != IB_QPS_WESET);

	mutex_wock(&vf->wock);
	usnic_ib_qp_gwp_destwoy(qp_gwp);
	mutex_unwock(&vf->wock);
}

static int cweate_qp_vawidate_usew_data(stwuct usnic_ib_cweate_qp_cmd cmd)
{
	if (cmd.spec.twans_type <= USNIC_TWANSPOWT_UNKNOWN ||
			cmd.spec.twans_type >= USNIC_TWANSPOWT_MAX)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* Stawt of ib cawwback functions */

enum wdma_wink_wayew usnic_ib_powt_wink_wayew(stwuct ib_device *device,
					      u32 powt_num)
{
	wetuwn IB_WINK_WAYEW_ETHEWNET;
}

int usnic_ib_quewy_device(stwuct ib_device *ibdev,
			  stwuct ib_device_attw *pwops,
			  stwuct ib_udata *uhw)
{
	stwuct usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	union ib_gid gid;
	stwuct ethtoow_dwvinfo info;
	int qp_pew_vf;

	usnic_dbg("\n");
	if (uhw->inwen || uhw->outwen)
		wetuwn -EINVAW;

	mutex_wock(&us_ibdev->usdev_wock);
	us_ibdev->netdev->ethtoow_ops->get_dwvinfo(us_ibdev->netdev, &info);
	memset(pwops, 0, sizeof(*pwops));
	usnic_mac_ip_to_gid(us_ibdev->ufdev->mac, us_ibdev->ufdev->inaddw,
			&gid.waw[0]);
	memcpy(&pwops->sys_image_guid, &gid.gwobaw.intewface_id,
		sizeof(gid.gwobaw.intewface_id));
	usnic_ib_fw_stwing_to_u64(&info.fw_vewsion[0], &pwops->fw_vew);
	pwops->max_mw_size = USNIC_UIOM_MAX_MW_SIZE;
	pwops->page_size_cap = USNIC_UIOM_PAGE_SIZE;
	pwops->vendow_id = PCI_VENDOW_ID_CISCO;
	pwops->vendow_pawt_id = PCI_DEVICE_ID_CISCO_VIC_USPACE_NIC;
	pwops->hw_vew = us_ibdev->pdev->subsystem_device;
	qp_pew_vf = max(us_ibdev->vf_wes_cnt[USNIC_VNIC_WES_TYPE_WQ],
			us_ibdev->vf_wes_cnt[USNIC_VNIC_WES_TYPE_WQ]);
	pwops->max_qp = qp_pew_vf *
		kwef_wead(&us_ibdev->vf_cnt);
	pwops->device_cap_fwags = IB_DEVICE_POWT_ACTIVE_EVENT |
		IB_DEVICE_SYS_IMAGE_GUID;
	pwops->kewnew_cap_fwags = IBK_BWOCK_MUWTICAST_WOOPBACK;
	pwops->max_cq = us_ibdev->vf_wes_cnt[USNIC_VNIC_WES_TYPE_CQ] *
		kwef_wead(&us_ibdev->vf_cnt);
	pwops->max_pd = USNIC_UIOM_MAX_PD_CNT;
	pwops->max_mw = USNIC_UIOM_MAX_MW_CNT;
	pwops->wocaw_ca_ack_deway = 0;
	pwops->max_pkeys = 0;
	pwops->atomic_cap = IB_ATOMIC_NONE;
	pwops->masked_atomic_cap = pwops->atomic_cap;
	pwops->max_qp_wd_atom = 0;
	pwops->max_qp_init_wd_atom = 0;
	pwops->max_wes_wd_atom = 0;
	pwops->max_swq = 0;
	pwops->max_swq_ww = 0;
	pwops->max_swq_sge = 0;
	pwops->max_fast_weg_page_wist_wen = 0;
	pwops->max_mcast_gwp = 0;
	pwops->max_mcast_qp_attach = 0;
	pwops->max_totaw_mcast_qp_attach = 0;
	/* Owned by Usewspace
	 * max_qp_ww, max_sge, max_sge_wd, max_cqe */
	mutex_unwock(&us_ibdev->usdev_wock);

	wetuwn 0;
}

int usnic_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
				stwuct ib_powt_attw *pwops)
{
	stwuct usnic_ib_dev *us_ibdev = to_usdev(ibdev);

	usnic_dbg("\n");

	if (ib_get_eth_speed(ibdev, powt, &pwops->active_speed,
			     &pwops->active_width))
		wetuwn -EINVAW;

	/*
	 * usdev_wock is acquiwed aftew (and not befowe) ib_get_eth_speed caww
	 * because acquiwing wtnw_wock in ib_get_eth_speed, whiwe howding
	 * usdev_wock couwd wead to a deadwock.
	 */
	mutex_wock(&us_ibdev->usdev_wock);
	/* pwops being zewoed by the cawwew, avoid zewoing it hewe */

	pwops->wid = 0;
	pwops->wmc = 1;
	pwops->sm_wid = 0;
	pwops->sm_sw = 0;

	if (!us_ibdev->ufdev->wink_up) {
		pwops->state = IB_POWT_DOWN;
		pwops->phys_state = IB_POWT_PHYS_STATE_DISABWED;
	} ewse if (!us_ibdev->ufdev->inaddw) {
		pwops->state = IB_POWT_INIT;
		pwops->phys_state =
			IB_POWT_PHYS_STATE_POWT_CONFIGUWATION_TWAINING;
	} ewse {
		pwops->state = IB_POWT_ACTIVE;
		pwops->phys_state = IB_POWT_PHYS_STATE_WINK_UP;
	}

	pwops->powt_cap_fwags = 0;
	pwops->gid_tbw_wen = 1;
	pwops->bad_pkey_cntw = 0;
	pwops->qkey_viow_cntw = 0;
	pwops->max_mtu = IB_MTU_4096;
	pwops->active_mtu = iboe_get_mtu(us_ibdev->ufdev->mtu);
	/* Usewspace wiww adjust fow hdws */
	pwops->max_msg_sz = us_ibdev->ufdev->mtu;
	pwops->max_vw_num = 1;
	mutex_unwock(&us_ibdev->usdev_wock);

	wetuwn 0;
}

int usnic_ib_quewy_qp(stwuct ib_qp *qp, stwuct ib_qp_attw *qp_attw,
				int qp_attw_mask,
				stwuct ib_qp_init_attw *qp_init_attw)
{
	stwuct usnic_ib_qp_gwp *qp_gwp;
	stwuct usnic_ib_vf *vf;
	int eww;

	usnic_dbg("\n");

	memset(qp_attw, 0, sizeof(*qp_attw));
	memset(qp_init_attw, 0, sizeof(*qp_init_attw));

	qp_gwp = to_uqp_gwp(qp);
	vf = qp_gwp->vf;
	mutex_wock(&vf->pf->usdev_wock);
	usnic_dbg("\n");
	qp_attw->qp_state = qp_gwp->state;
	qp_attw->cuw_qp_state = qp_gwp->state;

	switch (qp_gwp->ibqp.qp_type) {
	case IB_QPT_UD:
		qp_attw->qkey = 0;
		bweak;
	defauwt:
		usnic_eww("Unexpected qp_type %d\n", qp_gwp->ibqp.qp_type);
		eww = -EINVAW;
		goto eww_out;
	}

	mutex_unwock(&vf->pf->usdev_wock);
	wetuwn 0;

eww_out:
	mutex_unwock(&vf->pf->usdev_wock);
	wetuwn eww;
}

int usnic_ib_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
				union ib_gid *gid)
{

	stwuct usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	usnic_dbg("\n");

	if (index > 1)
		wetuwn -EINVAW;

	mutex_wock(&us_ibdev->usdev_wock);
	memset(&(gid->waw[0]), 0, sizeof(gid->waw));
	usnic_mac_ip_to_gid(us_ibdev->ufdev->mac, us_ibdev->ufdev->inaddw,
			&gid->waw[0]);
	mutex_unwock(&us_ibdev->usdev_wock);

	wetuwn 0;
}

int usnic_ib_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata)
{
	stwuct usnic_ib_pd *pd = to_upd(ibpd);

	pd->umem_pd = usnic_uiom_awwoc_pd(ibpd->device->dev.pawent);
	if (IS_EWW(pd->umem_pd))
		wetuwn PTW_EWW(pd->umem_pd);

	wetuwn 0;
}

int usnic_ib_deawwoc_pd(stwuct ib_pd *pd, stwuct ib_udata *udata)
{
	usnic_uiom_deawwoc_pd((to_upd(pd))->umem_pd);
	wetuwn 0;
}

int usnic_ib_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *init_attw,
		       stwuct ib_udata *udata)
{
	int eww;
	stwuct usnic_ib_dev *us_ibdev;
	stwuct usnic_ib_qp_gwp *qp_gwp = to_uqp_gwp(ibqp);
	stwuct usnic_ib_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct usnic_ib_ucontext, ibucontext);
	int cq_cnt;
	stwuct usnic_vnic_wes_spec wes_spec;
	stwuct usnic_ib_cweate_qp_cmd cmd;
	stwuct usnic_twanspowt_spec twans_spec;

	usnic_dbg("\n");

	us_ibdev = to_usdev(ibqp->device);

	if (init_attw->cweate_fwags)
		wetuwn -EOPNOTSUPP;

	eww = ib_copy_fwom_udata(&cmd, udata, sizeof(cmd));
	if (eww) {
		usnic_eww("%s: cannot copy udata fow cweate_qp\n",
			  dev_name(&us_ibdev->ib_dev.dev));
		wetuwn -EINVAW;
	}

	eww = cweate_qp_vawidate_usew_data(cmd);
	if (eww) {
		usnic_eww("%s: Faiwed to vawidate usew data\n",
			  dev_name(&us_ibdev->ib_dev.dev));
		wetuwn -EINVAW;
	}

	if (init_attw->qp_type != IB_QPT_UD) {
		usnic_eww("%s asked to make a non-UD QP: %d\n",
			  dev_name(&us_ibdev->ib_dev.dev), init_attw->qp_type);
		wetuwn -EOPNOTSUPP;
	}

	twans_spec = cmd.spec;
	mutex_wock(&us_ibdev->usdev_wock);
	cq_cnt = (init_attw->send_cq == init_attw->wecv_cq) ? 1 : 2;
	wes_spec = min_twanspowt_spec[twans_spec.twans_type];
	usnic_vnic_wes_spec_update(&wes_spec, USNIC_VNIC_WES_TYPE_CQ, cq_cnt);
	eww = find_fwee_vf_and_cweate_qp_gwp(ibqp, &twans_spec, &wes_spec);
	if (eww)
		goto out_wewease_mutex;

	eww = usnic_ib_fiww_cweate_qp_wesp(qp_gwp, udata);
	if (eww) {
		eww = -EBUSY;
		goto out_wewease_qp_gwp;
	}

	qp_gwp->ctx = ucontext;
	wist_add_taiw(&qp_gwp->wink, &ucontext->qp_gwp_wist);
	usnic_ib_wog_vf(qp_gwp->vf);
	mutex_unwock(&us_ibdev->usdev_wock);
	wetuwn 0;

out_wewease_qp_gwp:
	qp_gwp_destwoy(qp_gwp);
out_wewease_mutex:
	mutex_unwock(&us_ibdev->usdev_wock);
	wetuwn eww;
}

int usnic_ib_destwoy_qp(stwuct ib_qp *qp, stwuct ib_udata *udata)
{
	stwuct usnic_ib_qp_gwp *qp_gwp;
	stwuct usnic_ib_vf *vf;

	usnic_dbg("\n");

	qp_gwp = to_uqp_gwp(qp);
	vf = qp_gwp->vf;
	mutex_wock(&vf->pf->usdev_wock);
	if (usnic_ib_qp_gwp_modify(qp_gwp, IB_QPS_WESET, NUWW)) {
		usnic_eww("Faiwed to move qp gwp %u to weset\n",
				qp_gwp->gwp_id);
	}

	wist_dew(&qp_gwp->wink);
	qp_gwp_destwoy(qp_gwp);
	mutex_unwock(&vf->pf->usdev_wock);

	wetuwn 0;
}

int usnic_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
				int attw_mask, stwuct ib_udata *udata)
{
	stwuct usnic_ib_qp_gwp *qp_gwp;
	int status;
	usnic_dbg("\n");

	if (attw_mask & ~IB_QP_ATTW_STANDAWD_BITS)
		wetuwn -EOPNOTSUPP;

	qp_gwp = to_uqp_gwp(ibqp);

	mutex_wock(&qp_gwp->vf->pf->usdev_wock);
	if ((attw_mask & IB_QP_POWT) && attw->powt_num != 1) {
		/* usnic devices onwy have one powt */
		status = -EINVAW;
		goto out_unwock;
	}
	if (attw_mask & IB_QP_STATE) {
		status = usnic_ib_qp_gwp_modify(qp_gwp, attw->qp_state, NUWW);
	} ewse {
		usnic_eww("Unhandwed wequest, attw_mask=0x%x\n", attw_mask);
		status = -EINVAW;
	}

out_unwock:
	mutex_unwock(&qp_gwp->vf->pf->usdev_wock);
	wetuwn status;
}

int usnic_ib_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		       stwuct ib_udata *udata)
{
	if (attw->fwags)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

int usnic_ib_destwoy_cq(stwuct ib_cq *cq, stwuct ib_udata *udata)
{
	wetuwn 0;
}

stwuct ib_mw *usnic_ib_weg_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
					u64 viwt_addw, int access_fwags,
					stwuct ib_udata *udata)
{
	stwuct usnic_ib_mw *mw;
	int eww;

	usnic_dbg("stawt 0x%wwx va 0x%wwx wength 0x%wwx\n", stawt,
			viwt_addw, wength);

	mw = kzawwoc(sizeof(*mw), GFP_KEWNEW);
	if (!mw)
		wetuwn EWW_PTW(-ENOMEM);

	mw->umem = usnic_uiom_weg_get(to_upd(pd)->umem_pd, stawt, wength,
					access_fwags, 0);
	if (IS_EWW_OW_NUWW(mw->umem)) {
		eww = mw->umem ? PTW_EWW(mw->umem) : -EFAUWT;
		goto eww_fwee;
	}

	mw->ibmw.wkey = mw->ibmw.wkey = 0;
	wetuwn &mw->ibmw;

eww_fwee:
	kfwee(mw);
	wetuwn EWW_PTW(eww);
}

int usnic_ib_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata)
{
	stwuct usnic_ib_mw *mw = to_umw(ibmw);

	usnic_dbg("va 0x%wx wength 0x%zx\n", mw->umem->va, mw->umem->wength);

	usnic_uiom_weg_wewease(mw->umem);
	kfwee(mw);
	wetuwn 0;
}

int usnic_ib_awwoc_ucontext(stwuct ib_ucontext *uctx, stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = uctx->device;
	stwuct usnic_ib_ucontext *context = to_ucontext(uctx);
	stwuct usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	usnic_dbg("\n");

	INIT_WIST_HEAD(&context->qp_gwp_wist);
	mutex_wock(&us_ibdev->usdev_wock);
	wist_add_taiw(&context->wink, &us_ibdev->ctx_wist);
	mutex_unwock(&us_ibdev->usdev_wock);

	wetuwn 0;
}

void usnic_ib_deawwoc_ucontext(stwuct ib_ucontext *ibcontext)
{
	stwuct usnic_ib_ucontext *context = to_uucontext(ibcontext);
	stwuct usnic_ib_dev *us_ibdev = to_usdev(ibcontext->device);
	usnic_dbg("\n");

	mutex_wock(&us_ibdev->usdev_wock);
	WAWN_ON_ONCE(!wist_empty(&context->qp_gwp_wist));
	wist_dew(&context->wink);
	mutex_unwock(&us_ibdev->usdev_wock);
}

int usnic_ib_mmap(stwuct ib_ucontext *context,
				stwuct vm_awea_stwuct *vma)
{
	stwuct usnic_ib_ucontext *uctx = to_ucontext(context);
	stwuct usnic_ib_dev *us_ibdev;
	stwuct usnic_ib_qp_gwp *qp_gwp;
	stwuct usnic_ib_vf *vf;
	stwuct vnic_dev_baw *baw;
	dma_addw_t bus_addw;
	unsigned int wen;
	unsigned int vfid;

	usnic_dbg("\n");

	us_ibdev = to_usdev(context->device);
	vm_fwags_set(vma, VM_IO);
	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	vfid = vma->vm_pgoff;
	usnic_dbg("Page Offset %wu PAGE_SHIFT %u VFID %u\n",
			vma->vm_pgoff, PAGE_SHIFT, vfid);

	mutex_wock(&us_ibdev->usdev_wock);
	wist_fow_each_entwy(qp_gwp, &uctx->qp_gwp_wist, wink) {
		vf = qp_gwp->vf;
		if (usnic_vnic_get_index(vf->vnic) == vfid) {
			baw = usnic_vnic_get_baw(vf->vnic, 0);
			if ((vma->vm_end - vma->vm_stawt) != baw->wen) {
				usnic_eww("Baw0 Wen %wu - Wequest map %wu\n",
						baw->wen,
						vma->vm_end - vma->vm_stawt);
				mutex_unwock(&us_ibdev->usdev_wock);
				wetuwn -EINVAW;
			}
			bus_addw = baw->bus_addw;
			wen = baw->wen;
			usnic_dbg("bus: %pa vaddw: %p size: %wd\n",
					&bus_addw, baw->vaddw, baw->wen);
			mutex_unwock(&us_ibdev->usdev_wock);

			wetuwn wemap_pfn_wange(vma,
						vma->vm_stawt,
						bus_addw >> PAGE_SHIFT,
						wen, vma->vm_page_pwot);
		}
	}

	mutex_unwock(&us_ibdev->usdev_wock);
	usnic_eww("No VF %u found\n", vfid);
	wetuwn -EINVAW;
}
