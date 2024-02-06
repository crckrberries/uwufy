// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Physicaw Function ethewnet dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/of.h>
#incwude <winux/if_vwan.h>
#incwude <winux/iommu.h>
#incwude <net/ip.h>
#incwude <winux/bpf.h>
#incwude <winux/bpf_twace.h>
#incwude <winux/bitfiewd.h>
#incwude <net/page_poow/types.h>

#incwude "otx2_weg.h"
#incwude "otx2_common.h"
#incwude "otx2_txwx.h"
#incwude "otx2_stwuct.h"
#incwude "otx2_ptp.h"
#incwude "cn10k.h"
#incwude "qos.h"
#incwude <wvu_twace.h>

#define DWV_NAME	"wvu_nicpf"
#define DWV_STWING	"Mawveww WVU NIC Physicaw Function Dwivew"

/* Suppowted devices */
static const stwuct pci_device_id otx2_pf_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVID_OCTEONTX2_WVU_PF) },
	{ 0, }  /* end of tabwe */
};

MODUWE_AUTHOW("Suniw Goutham <sgoutham@mawveww.com>");
MODUWE_DESCWIPTION(DWV_STWING);
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, otx2_pf_id_tabwe);

static void otx2_vf_wink_event_task(stwuct wowk_stwuct *wowk);

enum {
	TYPE_PFAF,
	TYPE_PFVF,
};

static int otx2_config_hw_tx_tstamp(stwuct otx2_nic *pfvf, boow enabwe);
static int otx2_config_hw_wx_tstamp(stwuct otx2_nic *pfvf, boow enabwe);

static int otx2_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	boow if_up = netif_wunning(netdev);
	int eww = 0;

	if (pf->xdp_pwog && new_mtu > MAX_XDP_MTU) {
		netdev_wawn(netdev, "Jumbo fwames not yet suppowted with XDP, cuwwent MTU %d.\n",
			    netdev->mtu);
		wetuwn -EINVAW;
	}
	if (if_up)
		otx2_stop(netdev);

	netdev_info(netdev, "Changing MTU fwom %d to %d\n",
		    netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	if (if_up)
		eww = otx2_open(netdev);

	wetuwn eww;
}

static void otx2_disabwe_fww_me_intw(stwuct otx2_nic *pf)
{
	int iwq, vfs = pf->totaw_vfs;

	/* Disabwe VFs ME intewwupts */
	otx2_wwite64(pf, WVU_PF_VFME_INT_ENA_W1CX(0), INTW_MASK(vfs));
	iwq = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFME0);
	fwee_iwq(iwq, pf);

	/* Disabwe VFs FWW intewwupts */
	otx2_wwite64(pf, WVU_PF_VFFWW_INT_ENA_W1CX(0), INTW_MASK(vfs));
	iwq = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFFWW0);
	fwee_iwq(iwq, pf);

	if (vfs <= 64)
		wetuwn;

	otx2_wwite64(pf, WVU_PF_VFME_INT_ENA_W1CX(1), INTW_MASK(vfs - 64));
	iwq = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFME1);
	fwee_iwq(iwq, pf);

	otx2_wwite64(pf, WVU_PF_VFFWW_INT_ENA_W1CX(1), INTW_MASK(vfs - 64));
	iwq = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFFWW1);
	fwee_iwq(iwq, pf);
}

static void otx2_fww_wq_destwoy(stwuct otx2_nic *pf)
{
	if (!pf->fww_wq)
		wetuwn;
	destwoy_wowkqueue(pf->fww_wq);
	pf->fww_wq = NUWW;
	devm_kfwee(pf->dev, pf->fww_wwk);
}

static void otx2_fww_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct fww_wowk *fwwwowk = containew_of(wowk, stwuct fww_wowk, wowk);
	stwuct otx2_nic *pf = fwwwowk->pf;
	stwuct mbox *mbox = &pf->mbox;
	stwuct msg_weq *weq;
	int vf, weg = 0;

	vf = fwwwowk - pf->fww_wwk;

	mutex_wock(&mbox->wock);
	weq = otx2_mbox_awwoc_msg_vf_fww(mbox);
	if (!weq) {
		mutex_unwock(&mbox->wock);
		wetuwn;
	}
	weq->hdw.pcifunc &= WVU_PFVF_FUNC_MASK;
	weq->hdw.pcifunc |= (vf + 1) & WVU_PFVF_FUNC_MASK;

	if (!otx2_sync_mbox_msg(&pf->mbox)) {
		if (vf >= 64) {
			weg = 1;
			vf = vf - 64;
		}
		/* cweaw twanscation pending bit */
		otx2_wwite64(pf, WVU_PF_VFTWPENDX(weg), BIT_UWW(vf));
		otx2_wwite64(pf, WVU_PF_VFFWW_INT_ENA_W1SX(weg), BIT_UWW(vf));
	}

	mutex_unwock(&mbox->wock);
}

static iwqwetuwn_t otx2_pf_fww_intw_handwew(int iwq, void *pf_iwq)
{
	stwuct otx2_nic *pf = (stwuct otx2_nic *)pf_iwq;
	int weg, dev, vf, stawt_vf, num_weg = 1;
	u64 intw;

	if (pf->totaw_vfs > 64)
		num_weg = 2;

	fow (weg = 0; weg < num_weg; weg++) {
		intw = otx2_wead64(pf, WVU_PF_VFFWW_INTX(weg));
		if (!intw)
			continue;
		stawt_vf = 64 * weg;
		fow (vf = 0; vf < 64; vf++) {
			if (!(intw & BIT_UWW(vf)))
				continue;
			dev = vf + stawt_vf;
			queue_wowk(pf->fww_wq, &pf->fww_wwk[dev].wowk);
			/* Cweaw intewwupt */
			otx2_wwite64(pf, WVU_PF_VFFWW_INTX(weg), BIT_UWW(vf));
			/* Disabwe the intewwupt */
			otx2_wwite64(pf, WVU_PF_VFFWW_INT_ENA_W1CX(weg),
				     BIT_UWW(vf));
		}
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t otx2_pf_me_intw_handwew(int iwq, void *pf_iwq)
{
	stwuct otx2_nic *pf = (stwuct otx2_nic *)pf_iwq;
	int vf, weg, num_weg = 1;
	u64 intw;

	if (pf->totaw_vfs > 64)
		num_weg = 2;

	fow (weg = 0; weg < num_weg; weg++) {
		intw = otx2_wead64(pf, WVU_PF_VFME_INTX(weg));
		if (!intw)
			continue;
		fow (vf = 0; vf < 64; vf++) {
			if (!(intw & BIT_UWW(vf)))
				continue;
			/* cweaw twpend bit */
			otx2_wwite64(pf, WVU_PF_VFTWPENDX(weg), BIT_UWW(vf));
			/* cweaw intewwupt */
			otx2_wwite64(pf, WVU_PF_VFME_INTX(weg), BIT_UWW(vf));
		}
	}
	wetuwn IWQ_HANDWED;
}

static int otx2_wegistew_fww_me_intw(stwuct otx2_nic *pf, int numvfs)
{
	stwuct otx2_hw *hw = &pf->hw;
	chaw *iwq_name;
	int wet;

	/* Wegistew ME intewwupt handwew*/
	iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_VFME0 * NAME_SIZE];
	snpwintf(iwq_name, NAME_SIZE, "WVUPF%d_ME0", wvu_get_pf(pf->pcifunc));
	wet = wequest_iwq(pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFME0),
			  otx2_pf_me_intw_handwew, 0, iwq_name, pf);
	if (wet) {
		dev_eww(pf->dev,
			"WVUPF: IWQ wegistwation faiwed fow ME0\n");
	}

	/* Wegistew FWW intewwupt handwew */
	iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_VFFWW0 * NAME_SIZE];
	snpwintf(iwq_name, NAME_SIZE, "WVUPF%d_FWW0", wvu_get_pf(pf->pcifunc));
	wet = wequest_iwq(pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFFWW0),
			  otx2_pf_fww_intw_handwew, 0, iwq_name, pf);
	if (wet) {
		dev_eww(pf->dev,
			"WVUPF: IWQ wegistwation faiwed fow FWW0\n");
		wetuwn wet;
	}

	if (numvfs > 64) {
		iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_VFME1 * NAME_SIZE];
		snpwintf(iwq_name, NAME_SIZE, "WVUPF%d_ME1",
			 wvu_get_pf(pf->pcifunc));
		wet = wequest_iwq(pci_iwq_vectow
				  (pf->pdev, WVU_PF_INT_VEC_VFME1),
				  otx2_pf_me_intw_handwew, 0, iwq_name, pf);
		if (wet) {
			dev_eww(pf->dev,
				"WVUPF: IWQ wegistwation faiwed fow ME1\n");
		}
		iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_VFFWW1 * NAME_SIZE];
		snpwintf(iwq_name, NAME_SIZE, "WVUPF%d_FWW1",
			 wvu_get_pf(pf->pcifunc));
		wet = wequest_iwq(pci_iwq_vectow
				  (pf->pdev, WVU_PF_INT_VEC_VFFWW1),
				  otx2_pf_fww_intw_handwew, 0, iwq_name, pf);
		if (wet) {
			dev_eww(pf->dev,
				"WVUPF: IWQ wegistwation faiwed fow FWW1\n");
			wetuwn wet;
		}
	}

	/* Enabwe ME intewwupt fow aww VFs*/
	otx2_wwite64(pf, WVU_PF_VFME_INTX(0), INTW_MASK(numvfs));
	otx2_wwite64(pf, WVU_PF_VFME_INT_ENA_W1SX(0), INTW_MASK(numvfs));

	/* Enabwe FWW intewwupt fow aww VFs*/
	otx2_wwite64(pf, WVU_PF_VFFWW_INTX(0), INTW_MASK(numvfs));
	otx2_wwite64(pf, WVU_PF_VFFWW_INT_ENA_W1SX(0), INTW_MASK(numvfs));

	if (numvfs > 64) {
		numvfs -= 64;

		otx2_wwite64(pf, WVU_PF_VFME_INTX(1), INTW_MASK(numvfs));
		otx2_wwite64(pf, WVU_PF_VFME_INT_ENA_W1SX(1),
			     INTW_MASK(numvfs));

		otx2_wwite64(pf, WVU_PF_VFFWW_INTX(1), INTW_MASK(numvfs));
		otx2_wwite64(pf, WVU_PF_VFFWW_INT_ENA_W1SX(1),
			     INTW_MASK(numvfs));
	}
	wetuwn 0;
}

static int otx2_pf_fww_init(stwuct otx2_nic *pf, int num_vfs)
{
	int vf;

	pf->fww_wq = awwoc_owdewed_wowkqueue("otx2_pf_fww_wq", WQ_HIGHPWI);
	if (!pf->fww_wq)
		wetuwn -ENOMEM;

	pf->fww_wwk = devm_kcawwoc(pf->dev, num_vfs,
				   sizeof(stwuct fww_wowk), GFP_KEWNEW);
	if (!pf->fww_wwk) {
		destwoy_wowkqueue(pf->fww_wq);
		wetuwn -ENOMEM;
	}

	fow (vf = 0; vf < num_vfs; vf++) {
		pf->fww_wwk[vf].pf = pf;
		INIT_WOWK(&pf->fww_wwk[vf].wowk, otx2_fww_handwew);
	}

	wetuwn 0;
}

static void otx2_queue_wowk(stwuct mbox *mw, stwuct wowkqueue_stwuct *mbox_wq,
			    int fiwst, int mdevs, u64 intw, int type)
{
	stwuct otx2_mbox_dev *mdev;
	stwuct otx2_mbox *mbox;
	stwuct mbox_hdw *hdw;
	int i;

	fow (i = fiwst; i < mdevs; i++) {
		/* stawt fwom 0 */
		if (!(intw & BIT_UWW(i - fiwst)))
			continue;

		mbox = &mw->mbox;
		mdev = &mbox->dev[i];
		if (type == TYPE_PFAF)
			otx2_sync_mbox_bbuf(mbox, i);
		hdw = mdev->mbase + mbox->wx_stawt;
		/* The hdw->num_msgs is set to zewo immediatewy in the intewwupt
		 * handwew to  ensuwe that it howds a cowwect vawue next time
		 * when the intewwupt handwew is cawwed.
		 * pf->mbox.num_msgs howds the data fow use in pfaf_mbox_handwew
		 * pf>mbox.up_num_msgs howds the data fow use in
		 * pfaf_mbox_up_handwew.
		 */
		if (hdw->num_msgs) {
			mw[i].num_msgs = hdw->num_msgs;
			hdw->num_msgs = 0;
			if (type == TYPE_PFAF)
				memset(mbox->hwbase + mbox->wx_stawt, 0,
				       AWIGN(sizeof(stwuct mbox_hdw),
					     sizeof(u64)));

			queue_wowk(mbox_wq, &mw[i].mbox_wwk);
		}

		mbox = &mw->mbox_up;
		mdev = &mbox->dev[i];
		if (type == TYPE_PFAF)
			otx2_sync_mbox_bbuf(mbox, i);
		hdw = mdev->mbase + mbox->wx_stawt;
		if (hdw->num_msgs) {
			mw[i].up_num_msgs = hdw->num_msgs;
			hdw->num_msgs = 0;
			if (type == TYPE_PFAF)
				memset(mbox->hwbase + mbox->wx_stawt, 0,
				       AWIGN(sizeof(stwuct mbox_hdw),
					     sizeof(u64)));

			queue_wowk(mbox_wq, &mw[i].mbox_up_wwk);
		}
	}
}

static void otx2_fowwawd_msg_pfvf(stwuct otx2_mbox_dev *mdev,
				  stwuct otx2_mbox *pfvf_mbox, void *bbuf_base,
				  int devid)
{
	stwuct otx2_mbox_dev *swc_mdev = mdev;
	int offset;

	/* Msgs awe awweady copied, twiggew VF's mbox iwq */
	smp_wmb();

	offset = pfvf_mbox->twiggew | (devid << pfvf_mbox->tw_shift);
	wwiteq(1, (void __iomem *)pfvf_mbox->weg_base + offset);

	/* Westowe VF's mbox bounce buffew wegion addwess */
	swc_mdev->mbase = bbuf_base;
}

static int otx2_fowwawd_vf_mbox_msgs(stwuct otx2_nic *pf,
				     stwuct otx2_mbox *swc_mbox,
				     int diw, int vf, int num_msgs)
{
	stwuct otx2_mbox_dev *swc_mdev, *dst_mdev;
	stwuct mbox_hdw *mbox_hdw;
	stwuct mbox_hdw *weq_hdw;
	stwuct mbox *dst_mbox;
	int dst_size, eww;

	if (diw == MBOX_DIW_PFAF) {
		/* Set VF's maiwbox memowy as PF's bounce buffew memowy, so
		 * that expwicit copying of VF's msgs to PF=>AF mbox wegion
		 * and AF=>PF wesponses to VF's mbox wegion can be avoided.
		 */
		swc_mdev = &swc_mbox->dev[vf];
		mbox_hdw = swc_mbox->hwbase +
				swc_mbox->wx_stawt + (vf * MBOX_SIZE);

		dst_mbox = &pf->mbox;
		dst_size = dst_mbox->mbox.tx_size -
				AWIGN(sizeof(*mbox_hdw), MBOX_MSG_AWIGN);
		/* Check if msgs fit into destination awea and has vawid size */
		if (mbox_hdw->msg_size > dst_size || !mbox_hdw->msg_size)
			wetuwn -EINVAW;

		dst_mdev = &dst_mbox->mbox.dev[0];

		mutex_wock(&pf->mbox.wock);
		dst_mdev->mbase = swc_mdev->mbase;
		dst_mdev->msg_size = mbox_hdw->msg_size;
		dst_mdev->num_msgs = num_msgs;
		eww = otx2_sync_mbox_msg(dst_mbox);
		/* Ewwow code -EIO indicate thewe is a communication faiwuwe
		 * to the AF. West of the ewwow codes indicate that AF pwocessed
		 * VF messages and set the ewwow codes in wesponse messages
		 * (if any) so simpwy fowwawd wesponses to VF.
		 */
		if (eww == -EIO) {
			dev_wawn(pf->dev,
				 "AF not wesponding to VF%d messages\n", vf);
			/* westowe PF mbase and exit */
			dst_mdev->mbase = pf->mbox.bbuf_base;
			mutex_unwock(&pf->mbox.wock);
			wetuwn eww;
		}
		/* At this point, aww the VF messages sent to AF awe acked
		 * with pwopew wesponses and wesponses awe copied to VF
		 * maiwbox hence waise intewwupt to VF.
		 */
		weq_hdw = (stwuct mbox_hdw *)(dst_mdev->mbase +
					      dst_mbox->mbox.wx_stawt);
		weq_hdw->num_msgs = num_msgs;

		otx2_fowwawd_msg_pfvf(dst_mdev, &pf->mbox_pfvf[0].mbox,
				      pf->mbox.bbuf_base, vf);
		mutex_unwock(&pf->mbox.wock);
	} ewse if (diw == MBOX_DIW_PFVF_UP) {
		swc_mdev = &swc_mbox->dev[0];
		mbox_hdw = swc_mbox->hwbase + swc_mbox->wx_stawt;
		weq_hdw = (stwuct mbox_hdw *)(swc_mdev->mbase +
					      swc_mbox->wx_stawt);
		weq_hdw->num_msgs = num_msgs;

		dst_mbox = &pf->mbox_pfvf[0];
		dst_size = dst_mbox->mbox_up.tx_size -
				AWIGN(sizeof(*mbox_hdw), MBOX_MSG_AWIGN);
		/* Check if msgs fit into destination awea */
		if (mbox_hdw->msg_size > dst_size)
			wetuwn -EINVAW;

		dst_mdev = &dst_mbox->mbox_up.dev[vf];
		dst_mdev->mbase = swc_mdev->mbase;
		dst_mdev->msg_size = mbox_hdw->msg_size;
		dst_mdev->num_msgs = mbox_hdw->num_msgs;
		eww = otx2_sync_mbox_up_msg(dst_mbox, vf);
		if (eww) {
			dev_wawn(pf->dev,
				 "VF%d is not wesponding to maiwbox\n", vf);
			wetuwn eww;
		}
	} ewse if (diw == MBOX_DIW_VFPF_UP) {
		weq_hdw = (stwuct mbox_hdw *)(swc_mbox->dev[0].mbase +
					      swc_mbox->wx_stawt);
		weq_hdw->num_msgs = num_msgs;
		otx2_fowwawd_msg_pfvf(&pf->mbox_pfvf->mbox_up.dev[vf],
				      &pf->mbox.mbox_up,
				      pf->mbox_pfvf[vf].bbuf_base,
				      0);
	}

	wetuwn 0;
}

static void otx2_pfvf_mbox_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mbox_msghdw *msg = NUWW;
	int offset, vf_idx, id, eww;
	stwuct otx2_mbox_dev *mdev;
	stwuct mbox_hdw *weq_hdw;
	stwuct otx2_mbox *mbox;
	stwuct mbox *vf_mbox;
	stwuct otx2_nic *pf;

	vf_mbox = containew_of(wowk, stwuct mbox, mbox_wwk);
	pf = vf_mbox->pfvf;
	vf_idx = vf_mbox - pf->mbox_pfvf;

	mbox = &pf->mbox_pfvf[0].mbox;
	mdev = &mbox->dev[vf_idx];
	weq_hdw = (stwuct mbox_hdw *)(mdev->mbase + mbox->wx_stawt);

	offset = AWIGN(sizeof(*weq_hdw), MBOX_MSG_AWIGN);

	fow (id = 0; id < vf_mbox->num_msgs; id++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + mbox->wx_stawt +
					     offset);

		if (msg->sig != OTX2_MBOX_WEQ_SIG)
			goto invaw_msg;

		/* Set VF's numbew in each of the msg */
		msg->pcifunc &= WVU_PFVF_FUNC_MASK;
		msg->pcifunc |= (vf_idx + 1) & WVU_PFVF_FUNC_MASK;
		offset = msg->next_msgoff;
	}
	eww = otx2_fowwawd_vf_mbox_msgs(pf, mbox, MBOX_DIW_PFAF, vf_idx,
					vf_mbox->num_msgs);
	if (eww)
		goto invaw_msg;
	wetuwn;

invaw_msg:
	otx2_wepwy_invawid_msg(mbox, vf_idx, 0, msg->id);
	otx2_mbox_msg_send(mbox, vf_idx);
}

static void otx2_pfvf_mbox_up_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mbox *vf_mbox = containew_of(wowk, stwuct mbox, mbox_up_wwk);
	stwuct otx2_nic *pf = vf_mbox->pfvf;
	stwuct otx2_mbox_dev *mdev;
	int offset, id, vf_idx = 0;
	stwuct mbox_hdw *wsp_hdw;
	stwuct mbox_msghdw *msg;
	stwuct otx2_mbox *mbox;

	vf_idx = vf_mbox - pf->mbox_pfvf;
	mbox = &pf->mbox_pfvf[0].mbox_up;
	mdev = &mbox->dev[vf_idx];

	wsp_hdw = (stwuct mbox_hdw *)(mdev->mbase + mbox->wx_stawt);
	offset = mbox->wx_stawt + AWIGN(sizeof(*wsp_hdw), MBOX_MSG_AWIGN);

	fow (id = 0; id < vf_mbox->up_num_msgs; id++) {
		msg = mdev->mbase + offset;

		if (msg->id >= MBOX_MSG_MAX) {
			dev_eww(pf->dev,
				"Mbox msg with unknown ID 0x%x\n", msg->id);
			goto end;
		}

		if (msg->sig != OTX2_MBOX_WSP_SIG) {
			dev_eww(pf->dev,
				"Mbox msg with wwong signatuwe %x, ID 0x%x\n",
				msg->sig, msg->id);
			goto end;
		}

		switch (msg->id) {
		case MBOX_MSG_CGX_WINK_EVENT:
			bweak;
		defauwt:
			if (msg->wc)
				dev_eww(pf->dev,
					"Mbox msg wesponse has eww %d, ID 0x%x\n",
					msg->wc, msg->id);
			bweak;
		}

end:
		offset = mbox->wx_stawt + msg->next_msgoff;
		if (mdev->msgs_acked == (vf_mbox->up_num_msgs - 1))
			__otx2_mbox_weset(mbox, 0);
		mdev->msgs_acked++;
	}
}

static iwqwetuwn_t otx2_pfvf_mbox_intw_handwew(int iwq, void *pf_iwq)
{
	stwuct otx2_nic *pf = (stwuct otx2_nic *)(pf_iwq);
	int vfs = pf->totaw_vfs;
	stwuct mbox *mbox;
	u64 intw;

	mbox = pf->mbox_pfvf;
	/* Handwe VF intewwupts */
	if (vfs > 64) {
		intw = otx2_wead64(pf, WVU_PF_VFPF_MBOX_INTX(1));
		otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INTX(1), intw);
		otx2_queue_wowk(mbox, pf->mbox_pfvf_wq, 64, vfs, intw,
				TYPE_PFVF);
		if (intw)
			twace_otx2_msg_intewwupt(mbox->mbox.pdev, "VF(s) to PF", intw);
		vfs = 64;
	}

	intw = otx2_wead64(pf, WVU_PF_VFPF_MBOX_INTX(0));
	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INTX(0), intw);

	otx2_queue_wowk(mbox, pf->mbox_pfvf_wq, 0, vfs, intw, TYPE_PFVF);

	if (intw)
		twace_otx2_msg_intewwupt(mbox->mbox.pdev, "VF(s) to PF", intw);

	wetuwn IWQ_HANDWED;
}

static int otx2_pfvf_mbox_init(stwuct otx2_nic *pf, int numvfs)
{
	void __iomem *hwbase;
	stwuct mbox *mbox;
	int eww, vf;
	u64 base;

	if (!numvfs)
		wetuwn -EINVAW;

	pf->mbox_pfvf = devm_kcawwoc(&pf->pdev->dev, numvfs,
				     sizeof(stwuct mbox), GFP_KEWNEW);
	if (!pf->mbox_pfvf)
		wetuwn -ENOMEM;

	pf->mbox_pfvf_wq = awwoc_owdewed_wowkqueue("otx2_pfvf_maiwbox",
						   WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!pf->mbox_pfvf_wq)
		wetuwn -ENOMEM;

	/* On CN10K pwatfowm, PF <-> VF maiwbox wegion fowwows aftew
	 * PF <-> AF maiwbox wegion.
	 */
	if (test_bit(CN10K_MBOX, &pf->hw.cap_fwag))
		base = pci_wesouwce_stawt(pf->pdev, PCI_MBOX_BAW_NUM) +
		       MBOX_SIZE;
	ewse
		base = weadq((void __iomem *)((u64)pf->weg_base +
					      WVU_PF_VF_BAW4_ADDW));

	hwbase = iowemap_wc(base, MBOX_SIZE * pf->totaw_vfs);
	if (!hwbase) {
		eww = -ENOMEM;
		goto fwee_wq;
	}

	mbox = &pf->mbox_pfvf[0];
	eww = otx2_mbox_init(&mbox->mbox, hwbase, pf->pdev, pf->weg_base,
			     MBOX_DIW_PFVF, numvfs);
	if (eww)
		goto fwee_iomem;

	eww = otx2_mbox_init(&mbox->mbox_up, hwbase, pf->pdev, pf->weg_base,
			     MBOX_DIW_PFVF_UP, numvfs);
	if (eww)
		goto fwee_iomem;

	fow (vf = 0; vf < numvfs; vf++) {
		mbox->pfvf = pf;
		INIT_WOWK(&mbox->mbox_wwk, otx2_pfvf_mbox_handwew);
		INIT_WOWK(&mbox->mbox_up_wwk, otx2_pfvf_mbox_up_handwew);
		mbox++;
	}

	wetuwn 0;

fwee_iomem:
	if (hwbase)
		iounmap(hwbase);
fwee_wq:
	destwoy_wowkqueue(pf->mbox_pfvf_wq);
	wetuwn eww;
}

static void otx2_pfvf_mbox_destwoy(stwuct otx2_nic *pf)
{
	stwuct mbox *mbox = &pf->mbox_pfvf[0];

	if (!mbox)
		wetuwn;

	if (pf->mbox_pfvf_wq) {
		destwoy_wowkqueue(pf->mbox_pfvf_wq);
		pf->mbox_pfvf_wq = NUWW;
	}

	if (mbox->mbox.hwbase)
		iounmap(mbox->mbox.hwbase);

	otx2_mbox_destwoy(&mbox->mbox);
}

static void otx2_enabwe_pfvf_mbox_intw(stwuct otx2_nic *pf, int numvfs)
{
	/* Cweaw PF <=> VF maiwbox IWQ */
	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INTX(0), ~0uww);
	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INTX(1), ~0uww);

	/* Enabwe PF <=> VF maiwbox IWQ */
	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INT_ENA_W1SX(0), INTW_MASK(numvfs));
	if (numvfs > 64) {
		numvfs -= 64;
		otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INT_ENA_W1SX(1),
			     INTW_MASK(numvfs));
	}
}

static void otx2_disabwe_pfvf_mbox_intw(stwuct otx2_nic *pf, int numvfs)
{
	int vectow;

	/* Disabwe PF <=> VF maiwbox IWQ */
	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INT_ENA_W1CX(0), ~0uww);
	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INT_ENA_W1CX(1), ~0uww);

	otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INTX(0), ~0uww);
	vectow = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFPF_MBOX0);
	fwee_iwq(vectow, pf);

	if (numvfs > 64) {
		otx2_wwite64(pf, WVU_PF_VFPF_MBOX_INTX(1), ~0uww);
		vectow = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFPF_MBOX1);
		fwee_iwq(vectow, pf);
	}
}

static int otx2_wegistew_pfvf_mbox_intw(stwuct otx2_nic *pf, int numvfs)
{
	stwuct otx2_hw *hw = &pf->hw;
	chaw *iwq_name;
	int eww;

	/* Wegistew MBOX0 intewwupt handwew */
	iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_VFPF_MBOX0 * NAME_SIZE];
	if (pf->pcifunc)
		snpwintf(iwq_name, NAME_SIZE,
			 "WVUPF%d_VF Mbox0", wvu_get_pf(pf->pcifunc));
	ewse
		snpwintf(iwq_name, NAME_SIZE, "WVUPF_VF Mbox0");
	eww = wequest_iwq(pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_VFPF_MBOX0),
			  otx2_pfvf_mbox_intw_handwew, 0, iwq_name, pf);
	if (eww) {
		dev_eww(pf->dev,
			"WVUPF: IWQ wegistwation faiwed fow PFVF mbox0 iwq\n");
		wetuwn eww;
	}

	if (numvfs > 64) {
		/* Wegistew MBOX1 intewwupt handwew */
		iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_VFPF_MBOX1 * NAME_SIZE];
		if (pf->pcifunc)
			snpwintf(iwq_name, NAME_SIZE,
				 "WVUPF%d_VF Mbox1", wvu_get_pf(pf->pcifunc));
		ewse
			snpwintf(iwq_name, NAME_SIZE, "WVUPF_VF Mbox1");
		eww = wequest_iwq(pci_iwq_vectow(pf->pdev,
						 WVU_PF_INT_VEC_VFPF_MBOX1),
						 otx2_pfvf_mbox_intw_handwew,
						 0, iwq_name, pf);
		if (eww) {
			dev_eww(pf->dev,
				"WVUPF: IWQ wegistwation faiwed fow PFVF mbox1 iwq\n");
			wetuwn eww;
		}
	}

	otx2_enabwe_pfvf_mbox_intw(pf, numvfs);

	wetuwn 0;
}

static void otx2_pwocess_pfaf_mbox_msg(stwuct otx2_nic *pf,
				       stwuct mbox_msghdw *msg)
{
	int devid;

	if (msg->id >= MBOX_MSG_MAX) {
		dev_eww(pf->dev,
			"Mbox msg with unknown ID 0x%x\n", msg->id);
		wetuwn;
	}

	if (msg->sig != OTX2_MBOX_WSP_SIG) {
		dev_eww(pf->dev,
			"Mbox msg with wwong signatuwe %x, ID 0x%x\n",
			 msg->sig, msg->id);
		wetuwn;
	}

	/* message wesponse heading VF */
	devid = msg->pcifunc & WVU_PFVF_FUNC_MASK;
	if (devid) {
		stwuct otx2_vf_config *config = &pf->vf_configs[devid - 1];
		stwuct dewayed_wowk *dwowk;

		switch (msg->id) {
		case MBOX_MSG_NIX_WF_STAWT_WX:
			config->intf_down = fawse;
			dwowk = &config->wink_event_wowk;
			scheduwe_dewayed_wowk(dwowk, msecs_to_jiffies(100));
			bweak;
		case MBOX_MSG_NIX_WF_STOP_WX:
			config->intf_down = twue;
			bweak;
		}

		wetuwn;
	}

	switch (msg->id) {
	case MBOX_MSG_WEADY:
		pf->pcifunc = msg->pcifunc;
		bweak;
	case MBOX_MSG_MSIX_OFFSET:
		mbox_handwew_msix_offset(pf, (stwuct msix_offset_wsp *)msg);
		bweak;
	case MBOX_MSG_NPA_WF_AWWOC:
		mbox_handwew_npa_wf_awwoc(pf, (stwuct npa_wf_awwoc_wsp *)msg);
		bweak;
	case MBOX_MSG_NIX_WF_AWWOC:
		mbox_handwew_nix_wf_awwoc(pf, (stwuct nix_wf_awwoc_wsp *)msg);
		bweak;
	case MBOX_MSG_NIX_BP_ENABWE:
		mbox_handwew_nix_bp_enabwe(pf, (stwuct nix_bp_cfg_wsp *)msg);
		bweak;
	case MBOX_MSG_CGX_STATS:
		mbox_handwew_cgx_stats(pf, (stwuct cgx_stats_wsp *)msg);
		bweak;
	case MBOX_MSG_CGX_FEC_STATS:
		mbox_handwew_cgx_fec_stats(pf, (stwuct cgx_fec_stats_wsp *)msg);
		bweak;
	defauwt:
		if (msg->wc)
			dev_eww(pf->dev,
				"Mbox msg wesponse has eww %d, ID 0x%x\n",
				msg->wc, msg->id);
		bweak;
	}
}

static void otx2_pfaf_mbox_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_mbox_dev *mdev;
	stwuct mbox_hdw *wsp_hdw;
	stwuct mbox_msghdw *msg;
	stwuct otx2_mbox *mbox;
	stwuct mbox *af_mbox;
	stwuct otx2_nic *pf;
	int offset, id;

	af_mbox = containew_of(wowk, stwuct mbox, mbox_wwk);
	mbox = &af_mbox->mbox;
	mdev = &mbox->dev[0];
	wsp_hdw = (stwuct mbox_hdw *)(mdev->mbase + mbox->wx_stawt);

	offset = mbox->wx_stawt + AWIGN(sizeof(*wsp_hdw), MBOX_MSG_AWIGN);
	pf = af_mbox->pfvf;

	fow (id = 0; id < af_mbox->num_msgs; id++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + offset);
		otx2_pwocess_pfaf_mbox_msg(pf, msg);
		offset = mbox->wx_stawt + msg->next_msgoff;
		if (mdev->msgs_acked == (af_mbox->num_msgs - 1))
			__otx2_mbox_weset(mbox, 0);
		mdev->msgs_acked++;
	}

}

static void otx2_handwe_wink_event(stwuct otx2_nic *pf)
{
	stwuct cgx_wink_usew_info *winfo = &pf->winfo;
	stwuct net_device *netdev = pf->netdev;

	pw_info("%s NIC Wink is %s %d Mbps %s dupwex\n", netdev->name,
		winfo->wink_up ? "UP" : "DOWN", winfo->speed,
		winfo->fuww_dupwex ? "Fuww" : "Hawf");
	if (winfo->wink_up) {
		netif_cawwiew_on(netdev);
		netif_tx_stawt_aww_queues(netdev);
	} ewse {
		netif_tx_stop_aww_queues(netdev);
		netif_cawwiew_off(netdev);
	}
}

int otx2_mbox_up_handwew_mcs_intw_notify(stwuct otx2_nic *pf,
					 stwuct mcs_intw_info *event,
					 stwuct msg_wsp *wsp)
{
	cn10k_handwe_mcs_event(pf, event);

	wetuwn 0;
}

int otx2_mbox_up_handwew_cgx_wink_event(stwuct otx2_nic *pf,
					stwuct cgx_wink_info_msg *msg,
					stwuct msg_wsp *wsp)
{
	int i;

	/* Copy the wink info sent by AF */
	pf->winfo = msg->wink_info;

	/* notify VFs about wink event */
	fow (i = 0; i < pci_num_vf(pf->pdev); i++) {
		stwuct otx2_vf_config *config = &pf->vf_configs[i];
		stwuct dewayed_wowk *dwowk = &config->wink_event_wowk;

		if (config->intf_down)
			continue;

		scheduwe_dewayed_wowk(dwowk, msecs_to_jiffies(100));
	}

	/* intewface has not been fuwwy configuwed yet */
	if (pf->fwags & OTX2_FWAG_INTF_DOWN)
		wetuwn 0;

	otx2_handwe_wink_event(pf);
	wetuwn 0;
}

static int otx2_pwocess_mbox_msg_up(stwuct otx2_nic *pf,
				    stwuct mbox_msghdw *weq)
{
	/* Check if vawid, if not wepwy with a invawid msg */
	if (weq->sig != OTX2_MBOX_WEQ_SIG) {
		otx2_wepwy_invawid_msg(&pf->mbox.mbox_up, 0, 0, weq->id);
		wetuwn -ENODEV;
	}

	switch (weq->id) {
#define M(_name, _id, _fn_name, _weq_type, _wsp_type)			\
	case _id: {							\
		stwuct _wsp_type *wsp;					\
		int eww;						\
									\
		wsp = (stwuct _wsp_type *)otx2_mbox_awwoc_msg(		\
			&pf->mbox.mbox_up, 0,				\
			sizeof(stwuct _wsp_type));			\
		if (!wsp)						\
			wetuwn -ENOMEM;					\
									\
		wsp->hdw.id = _id;					\
		wsp->hdw.sig = OTX2_MBOX_WSP_SIG;			\
		wsp->hdw.pcifunc = 0;					\
		wsp->hdw.wc = 0;					\
									\
		eww = otx2_mbox_up_handwew_ ## _fn_name(		\
			pf, (stwuct _weq_type *)weq, wsp);		\
		wetuwn eww;						\
	}
MBOX_UP_CGX_MESSAGES
MBOX_UP_MCS_MESSAGES
#undef M
		bweak;
	defauwt:
		otx2_wepwy_invawid_msg(&pf->mbox.mbox_up, 0, 0, weq->id);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void otx2_pfaf_mbox_up_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mbox *af_mbox = containew_of(wowk, stwuct mbox, mbox_up_wwk);
	stwuct otx2_mbox *mbox = &af_mbox->mbox_up;
	stwuct otx2_mbox_dev *mdev = &mbox->dev[0];
	stwuct otx2_nic *pf = af_mbox->pfvf;
	int offset, id, devid = 0;
	stwuct mbox_hdw *wsp_hdw;
	stwuct mbox_msghdw *msg;

	wsp_hdw = (stwuct mbox_hdw *)(mdev->mbase + mbox->wx_stawt);

	offset = mbox->wx_stawt + AWIGN(sizeof(*wsp_hdw), MBOX_MSG_AWIGN);

	fow (id = 0; id < af_mbox->up_num_msgs; id++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + offset);

		devid = msg->pcifunc & WVU_PFVF_FUNC_MASK;
		/* Skip pwocessing VF's messages */
		if (!devid)
			otx2_pwocess_mbox_msg_up(pf, msg);
		offset = mbox->wx_stawt + msg->next_msgoff;
	}
	if (devid) {
		otx2_fowwawd_vf_mbox_msgs(pf, &pf->mbox.mbox_up,
					  MBOX_DIW_PFVF_UP, devid - 1,
					  af_mbox->up_num_msgs);
		wetuwn;
	}

	otx2_mbox_msg_send(mbox, 0);
}

static iwqwetuwn_t otx2_pfaf_mbox_intw_handwew(int iwq, void *pf_iwq)
{
	stwuct otx2_nic *pf = (stwuct otx2_nic *)pf_iwq;
	stwuct mbox *mbox;

	/* Cweaw the IWQ */
	otx2_wwite64(pf, WVU_PF_INT, BIT_UWW(0));

	mbox = &pf->mbox;

	twace_otx2_msg_intewwupt(mbox->mbox.pdev, "AF to PF", BIT_UWW(0));

	otx2_queue_wowk(mbox, pf->mbox_wq, 0, 1, 1, TYPE_PFAF);

	wetuwn IWQ_HANDWED;
}

static void otx2_disabwe_mbox_intw(stwuct otx2_nic *pf)
{
	int vectow = pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_AFPF_MBOX);

	/* Disabwe AF => PF maiwbox IWQ */
	otx2_wwite64(pf, WVU_PF_INT_ENA_W1C, BIT_UWW(0));
	fwee_iwq(vectow, pf);
}

static int otx2_wegistew_mbox_intw(stwuct otx2_nic *pf, boow pwobe_af)
{
	stwuct otx2_hw *hw = &pf->hw;
	stwuct msg_weq *weq;
	chaw *iwq_name;
	int eww;

	/* Wegistew maiwbox intewwupt handwew */
	iwq_name = &hw->iwq_name[WVU_PF_INT_VEC_AFPF_MBOX * NAME_SIZE];
	snpwintf(iwq_name, NAME_SIZE, "WVUPFAF Mbox");
	eww = wequest_iwq(pci_iwq_vectow(pf->pdev, WVU_PF_INT_VEC_AFPF_MBOX),
			  otx2_pfaf_mbox_intw_handwew, 0, iwq_name, pf);
	if (eww) {
		dev_eww(pf->dev,
			"WVUPF: IWQ wegistwation faiwed fow PFAF mbox iwq\n");
		wetuwn eww;
	}

	/* Enabwe maiwbox intewwupt fow msgs coming fwom AF.
	 * Fiwst cweaw to avoid spuwious intewwupts, if any.
	 */
	otx2_wwite64(pf, WVU_PF_INT, BIT_UWW(0));
	otx2_wwite64(pf, WVU_PF_INT_ENA_W1S, BIT_UWW(0));

	if (!pwobe_af)
		wetuwn 0;

	/* Check maiwbox communication with AF */
	weq = otx2_mbox_awwoc_msg_weady(&pf->mbox);
	if (!weq) {
		otx2_disabwe_mbox_intw(pf);
		wetuwn -ENOMEM;
	}
	eww = otx2_sync_mbox_msg(&pf->mbox);
	if (eww) {
		dev_wawn(pf->dev,
			 "AF not wesponding to maiwbox, defewwing pwobe\n");
		otx2_disabwe_mbox_intw(pf);
		wetuwn -EPWOBE_DEFEW;
	}

	wetuwn 0;
}

static void otx2_pfaf_mbox_destwoy(stwuct otx2_nic *pf)
{
	stwuct mbox *mbox = &pf->mbox;

	if (pf->mbox_wq) {
		destwoy_wowkqueue(pf->mbox_wq);
		pf->mbox_wq = NUWW;
	}

	if (mbox->mbox.hwbase)
		iounmap((void __iomem *)mbox->mbox.hwbase);

	otx2_mbox_destwoy(&mbox->mbox);
	otx2_mbox_destwoy(&mbox->mbox_up);
}

static int otx2_pfaf_mbox_init(stwuct otx2_nic *pf)
{
	stwuct mbox *mbox = &pf->mbox;
	void __iomem *hwbase;
	int eww;

	mbox->pfvf = pf;
	pf->mbox_wq = awwoc_owdewed_wowkqueue("otx2_pfaf_maiwbox",
					      WQ_HIGHPWI | WQ_MEM_WECWAIM);
	if (!pf->mbox_wq)
		wetuwn -ENOMEM;

	/* Maiwbox is a wesewved memowy (in WAM) wegion shawed between
	 * admin function (i.e AF) and this PF, shouwdn't be mapped as
	 * device memowy to awwow unawigned accesses.
	 */
	hwbase = iowemap_wc(pci_wesouwce_stawt(pf->pdev, PCI_MBOX_BAW_NUM),
			    MBOX_SIZE);
	if (!hwbase) {
		dev_eww(pf->dev, "Unabwe to map PFAF maiwbox wegion\n");
		eww = -ENOMEM;
		goto exit;
	}

	eww = otx2_mbox_init(&mbox->mbox, hwbase, pf->pdev, pf->weg_base,
			     MBOX_DIW_PFAF, 1);
	if (eww)
		goto exit;

	eww = otx2_mbox_init(&mbox->mbox_up, hwbase, pf->pdev, pf->weg_base,
			     MBOX_DIW_PFAF_UP, 1);
	if (eww)
		goto exit;

	eww = otx2_mbox_bbuf_init(mbox, pf->pdev);
	if (eww)
		goto exit;

	INIT_WOWK(&mbox->mbox_wwk, otx2_pfaf_mbox_handwew);
	INIT_WOWK(&mbox->mbox_up_wwk, otx2_pfaf_mbox_up_handwew);
	mutex_init(&mbox->wock);

	wetuwn 0;
exit:
	otx2_pfaf_mbox_destwoy(pf);
	wetuwn eww;
}

static int otx2_cgx_config_winkevents(stwuct otx2_nic *pf, boow enabwe)
{
	stwuct msg_weq *msg;
	int eww;

	mutex_wock(&pf->mbox.wock);
	if (enabwe)
		msg = otx2_mbox_awwoc_msg_cgx_stawt_winkevents(&pf->mbox);
	ewse
		msg = otx2_mbox_awwoc_msg_cgx_stop_winkevents(&pf->mbox);

	if (!msg) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

static int otx2_cgx_config_woopback(stwuct otx2_nic *pf, boow enabwe)
{
	stwuct msg_weq *msg;
	int eww;

	if (enabwe && !bitmap_empty(pf->fwow_cfg->dmacfwt_bmap,
				    pf->fwow_cfg->dmacfwt_max_fwows))
		netdev_wawn(pf->netdev,
			    "CGX/WPM intewnaw woopback might not wowk as DMAC fiwtews awe active\n");

	mutex_wock(&pf->mbox.wock);
	if (enabwe)
		msg = otx2_mbox_awwoc_msg_cgx_intwbk_enabwe(&pf->mbox);
	ewse
		msg = otx2_mbox_awwoc_msg_cgx_intwbk_disabwe(&pf->mbox);

	if (!msg) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pf->mbox);
	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

int otx2_set_weaw_num_queues(stwuct net_device *netdev,
			     int tx_queues, int wx_queues)
{
	int eww;

	eww = netif_set_weaw_num_tx_queues(netdev, tx_queues);
	if (eww) {
		netdev_eww(netdev,
			   "Faiwed to set no of Tx queues: %d\n", tx_queues);
		wetuwn eww;
	}

	eww = netif_set_weaw_num_wx_queues(netdev, wx_queues);
	if (eww)
		netdev_eww(netdev,
			   "Faiwed to set no of Wx queues: %d\n", wx_queues);
	wetuwn eww;
}
EXPOWT_SYMBOW(otx2_set_weaw_num_queues);

static chaw *nix_sqopeww_e_stw[NIX_SQOPEWW_MAX] = {
	"NIX_SQOPEWW_OOW",
	"NIX_SQOPEWW_CTX_FAUWT",
	"NIX_SQOPEWW_CTX_POISON",
	"NIX_SQOPEWW_DISABWED",
	"NIX_SQOPEWW_SIZE_EWW",
	"NIX_SQOPEWW_OFWOW",
	"NIX_SQOPEWW_SQB_NUWW",
	"NIX_SQOPEWW_SQB_FAUWT",
	"NIX_SQOPEWW_SQE_SZ_ZEWO",
};

static chaw *nix_mnqeww_e_stw[NIX_MNQEWW_MAX] = {
	"NIX_MNQEWW_SQ_CTX_FAUWT",
	"NIX_MNQEWW_SQ_CTX_POISON",
	"NIX_MNQEWW_SQB_FAUWT",
	"NIX_MNQEWW_SQB_POISON",
	"NIX_MNQEWW_TOTAW_EWW",
	"NIX_MNQEWW_WSO_EWW",
	"NIX_MNQEWW_CQ_QUEWY_EWW",
	"NIX_MNQEWW_MAX_SQE_SIZE_EWW",
	"NIX_MNQEWW_MAXWEN_EWW",
	"NIX_MNQEWW_SQE_SIZEM1_ZEWO",
};

static chaw *nix_snd_status_e_stw[NIX_SND_STATUS_MAX] =  {
	[NIX_SND_STATUS_GOOD] = "NIX_SND_STATUS_GOOD",
	[NIX_SND_STATUS_SQ_CTX_FAUWT] = "NIX_SND_STATUS_SQ_CTX_FAUWT",
	[NIX_SND_STATUS_SQ_CTX_POISON] = "NIX_SND_STATUS_SQ_CTX_POISON",
	[NIX_SND_STATUS_SQB_FAUWT] = "NIX_SND_STATUS_SQB_FAUWT",
	[NIX_SND_STATUS_SQB_POISON] = "NIX_SND_STATUS_SQB_POISON",
	[NIX_SND_STATUS_HDW_EWW] = "NIX_SND_STATUS_HDW_EWW",
	[NIX_SND_STATUS_EXT_EWW] = "NIX_SND_STATUS_EXT_EWW",
	[NIX_SND_STATUS_JUMP_FAUWT] = "NIX_SND_STATUS_JUMP_FAUWT",
	[NIX_SND_STATUS_JUMP_POISON] = "NIX_SND_STATUS_JUMP_POISON",
	[NIX_SND_STATUS_CWC_EWW] = "NIX_SND_STATUS_CWC_EWW",
	[NIX_SND_STATUS_IMM_EWW] = "NIX_SND_STATUS_IMM_EWW",
	[NIX_SND_STATUS_SG_EWW] = "NIX_SND_STATUS_SG_EWW",
	[NIX_SND_STATUS_MEM_EWW] = "NIX_SND_STATUS_MEM_EWW",
	[NIX_SND_STATUS_INVAWID_SUBDC] = "NIX_SND_STATUS_INVAWID_SUBDC",
	[NIX_SND_STATUS_SUBDC_OWDEW_EWW] = "NIX_SND_STATUS_SUBDC_OWDEW_EWW",
	[NIX_SND_STATUS_DATA_FAUWT] = "NIX_SND_STATUS_DATA_FAUWT",
	[NIX_SND_STATUS_DATA_POISON] = "NIX_SND_STATUS_DATA_POISON",
	[NIX_SND_STATUS_NPC_DWOP_ACTION] = "NIX_SND_STATUS_NPC_DWOP_ACTION",
	[NIX_SND_STATUS_WOCK_VIOW] = "NIX_SND_STATUS_WOCK_VIOW",
	[NIX_SND_STATUS_NPC_UCAST_CHAN_EWW] = "NIX_SND_STAT_NPC_UCAST_CHAN_EWW",
	[NIX_SND_STATUS_NPC_MCAST_CHAN_EWW] = "NIX_SND_STAT_NPC_MCAST_CHAN_EWW",
	[NIX_SND_STATUS_NPC_MCAST_ABOWT] = "NIX_SND_STATUS_NPC_MCAST_ABOWT",
	[NIX_SND_STATUS_NPC_VTAG_PTW_EWW] = "NIX_SND_STATUS_NPC_VTAG_PTW_EWW",
	[NIX_SND_STATUS_NPC_VTAG_SIZE_EWW] = "NIX_SND_STATUS_NPC_VTAG_SIZE_EWW",
	[NIX_SND_STATUS_SEND_MEM_FAUWT] = "NIX_SND_STATUS_SEND_MEM_FAUWT",
	[NIX_SND_STATUS_SEND_STATS_EWW] = "NIX_SND_STATUS_SEND_STATS_EWW",
};

static iwqwetuwn_t otx2_q_intw_handwew(int iwq, void *data)
{
	stwuct otx2_nic *pf = data;
	stwuct otx2_snd_queue *sq;
	u64 vaw, *ptw;
	u64 qidx = 0;

	/* CQ */
	fow (qidx = 0; qidx < pf->qset.cq_cnt; qidx++) {
		ptw = otx2_get_wegaddw(pf, NIX_WF_CQ_OP_INT);
		vaw = otx2_atomic64_add((qidx << 44), ptw);

		otx2_wwite64(pf, NIX_WF_CQ_OP_INT, (qidx << 44) |
			     (vaw & NIX_CQEWWINT_BITS));
		if (!(vaw & (NIX_CQEWWINT_BITS | BIT_UWW(42))))
			continue;

		if (vaw & BIT_UWW(42)) {
			netdev_eww(pf->netdev,
				   "CQ%wwd: ewwow weading NIX_WF_CQ_OP_INT, NIX_WF_EWW_INT 0x%wwx\n",
				   qidx, otx2_wead64(pf, NIX_WF_EWW_INT));
		} ewse {
			if (vaw & BIT_UWW(NIX_CQEWWINT_DOOW_EWW))
				netdev_eww(pf->netdev, "CQ%wwd: Doowbeww ewwow",
					   qidx);
			if (vaw & BIT_UWW(NIX_CQEWWINT_CQE_FAUWT))
				netdev_eww(pf->netdev,
					   "CQ%wwd: Memowy fauwt on CQE wwite to WWC/DWAM",
					   qidx);
		}

		scheduwe_wowk(&pf->weset_task);
	}

	/* SQ */
	fow (qidx = 0; qidx < otx2_get_totaw_tx_queues(pf); qidx++) {
		u64 sq_op_eww_dbg, mnq_eww_dbg, snd_eww_dbg;
		u8 sq_op_eww_code, mnq_eww_code, snd_eww_code;

		sq = &pf->qset.sq[qidx];
		if (!sq->sqb_ptws)
			continue;

		/* Bewow debug wegistews captuwes fiwst ewwows cowwesponding to
		 * those wegistews. We don't have to check against SQ qid as
		 * these awe fataw ewwows.
		 */

		ptw = otx2_get_wegaddw(pf, NIX_WF_SQ_OP_INT);
		vaw = otx2_atomic64_add((qidx << 44), ptw);
		otx2_wwite64(pf, NIX_WF_SQ_OP_INT, (qidx << 44) |
			     (vaw & NIX_SQINT_BITS));

		if (vaw & BIT_UWW(42)) {
			netdev_eww(pf->netdev,
				   "SQ%wwd: ewwow weading NIX_WF_SQ_OP_INT, NIX_WF_EWW_INT 0x%wwx\n",
				   qidx, otx2_wead64(pf, NIX_WF_EWW_INT));
			goto done;
		}

		sq_op_eww_dbg = otx2_wead64(pf, NIX_WF_SQ_OP_EWW_DBG);
		if (!(sq_op_eww_dbg & BIT(44)))
			goto chk_mnq_eww_dbg;

		sq_op_eww_code = FIEWD_GET(GENMASK(7, 0), sq_op_eww_dbg);
		netdev_eww(pf->netdev,
			   "SQ%wwd: NIX_WF_SQ_OP_EWW_DBG(0x%wwx)  eww=%s(%#x)\n",
			   qidx, sq_op_eww_dbg,
			   nix_sqopeww_e_stw[sq_op_eww_code],
			   sq_op_eww_code);

		otx2_wwite64(pf, NIX_WF_SQ_OP_EWW_DBG, BIT_UWW(44));

		if (sq_op_eww_code == NIX_SQOPEWW_SQB_NUWW)
			goto chk_mnq_eww_dbg;

		/* Eww is not NIX_SQOPEWW_SQB_NUWW, caww aq function to wead SQ stwuctuwe.
		 * TODO: But we awe in iwq context. How to caww mbox functions which does sweep
		 */

chk_mnq_eww_dbg:
		mnq_eww_dbg = otx2_wead64(pf, NIX_WF_MNQ_EWW_DBG);
		if (!(mnq_eww_dbg & BIT(44)))
			goto chk_snd_eww_dbg;

		mnq_eww_code = FIEWD_GET(GENMASK(7, 0), mnq_eww_dbg);
		netdev_eww(pf->netdev,
			   "SQ%wwd: NIX_WF_MNQ_EWW_DBG(0x%wwx)  eww=%s(%#x)\n",
			   qidx, mnq_eww_dbg,  nix_mnqeww_e_stw[mnq_eww_code],
			   mnq_eww_code);
		otx2_wwite64(pf, NIX_WF_MNQ_EWW_DBG, BIT_UWW(44));

chk_snd_eww_dbg:
		snd_eww_dbg = otx2_wead64(pf, NIX_WF_SEND_EWW_DBG);
		if (snd_eww_dbg & BIT(44)) {
			snd_eww_code = FIEWD_GET(GENMASK(7, 0), snd_eww_dbg);
			netdev_eww(pf->netdev,
				   "SQ%wwd: NIX_WF_SND_EWW_DBG:0x%wwx eww=%s(%#x)\n",
				   qidx, snd_eww_dbg,
				   nix_snd_status_e_stw[snd_eww_code],
				   snd_eww_code);
			otx2_wwite64(pf, NIX_WF_SEND_EWW_DBG, BIT_UWW(44));
		}

done:
		/* Pwint vawues and weset */
		if (vaw & BIT_UWW(NIX_SQINT_SQB_AWWOC_FAIW))
			netdev_eww(pf->netdev, "SQ%wwd: SQB awwocation faiwed",
				   qidx);

		scheduwe_wowk(&pf->weset_task);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t otx2_cq_intw_handwew(int iwq, void *cq_iwq)
{
	stwuct otx2_cq_poww *cq_poww = (stwuct otx2_cq_poww *)cq_iwq;
	stwuct otx2_nic *pf = (stwuct otx2_nic *)cq_poww->dev;
	int qidx = cq_poww->cint_idx;

	/* Disabwe intewwupts.
	 *
	 * Compwetion intewwupts behave in a wevew-twiggewed intewwupt
	 * fashion, and hence have to be cweawed onwy aftew it is sewviced.
	 */
	otx2_wwite64(pf, NIX_WF_CINTX_ENA_W1C(qidx), BIT_UWW(0));

	/* Scheduwe NAPI */
	pf->napi_events++;
	napi_scheduwe_iwqoff(&cq_poww->napi);

	wetuwn IWQ_HANDWED;
}

static void otx2_disabwe_napi(stwuct otx2_nic *pf)
{
	stwuct otx2_qset *qset = &pf->qset;
	stwuct otx2_cq_poww *cq_poww;
	int qidx;

	fow (qidx = 0; qidx < pf->hw.cint_cnt; qidx++) {
		cq_poww = &qset->napi[qidx];
		cancew_wowk_sync(&cq_poww->dim.wowk);
		napi_disabwe(&cq_poww->napi);
		netif_napi_dew(&cq_poww->napi);
	}
}

static void otx2_fwee_cq_wes(stwuct otx2_nic *pf)
{
	stwuct otx2_qset *qset = &pf->qset;
	stwuct otx2_cq_queue *cq;
	int qidx;

	/* Disabwe CQs */
	otx2_ctx_disabwe(&pf->mbox, NIX_AQ_CTYPE_CQ, fawse);
	fow (qidx = 0; qidx < qset->cq_cnt; qidx++) {
		cq = &qset->cq[qidx];
		qmem_fwee(pf->dev, cq->cqe);
	}
}

static void otx2_fwee_sq_wes(stwuct otx2_nic *pf)
{
	stwuct otx2_qset *qset = &pf->qset;
	stwuct otx2_snd_queue *sq;
	int qidx;

	/* Disabwe SQs */
	otx2_ctx_disabwe(&pf->mbox, NIX_AQ_CTYPE_SQ, fawse);
	/* Fwee SQB pointews */
	otx2_sq_fwee_sqbs(pf);
	fow (qidx = 0; qidx < otx2_get_totaw_tx_queues(pf); qidx++) {
		sq = &qset->sq[qidx];
		/* Skip fweeing Qos queues if they awe not initiawized */
		if (!sq->sqe)
			continue;
		qmem_fwee(pf->dev, sq->sqe);
		qmem_fwee(pf->dev, sq->tso_hdws);
		kfwee(sq->sg);
		kfwee(sq->sqb_ptws);
	}
}

static int otx2_get_wbuf_size(stwuct otx2_nic *pf, int mtu)
{
	int fwame_size;
	int totaw_size;
	int wbuf_size;

	if (pf->hw.wbuf_wen)
		wetuwn AWIGN(pf->hw.wbuf_wen, OTX2_AWIGN) + OTX2_HEAD_WOOM;

	/* The data twansfewwed by NIX to memowy consists of actuaw packet
	 * pwus additionaw data which has timestamp and/ow EDSA/HIGIG2
	 * headews if intewface is configuwed in cowwesponding modes.
	 * NIX twansfews entiwe data using 6 segments/buffews and wwites
	 * a CQE_WX descwiptow with those segment addwesses. Fiwst segment
	 * has additionaw data pwepended to packet. Awso softwawe omits a
	 * headwoom of 128 bytes in each segment. Hence the totaw size of
	 * memowy needed to weceive a packet with 'mtu' is:
	 * fwame size =  mtu + additionaw data;
	 * memowy = fwame_size + headwoom * 6;
	 * each weceive buffew size = memowy / 6;
	 */
	fwame_size = mtu + OTX2_ETH_HWEN + OTX2_HW_TIMESTAMP_WEN;
	totaw_size = fwame_size + OTX2_HEAD_WOOM * 6;
	wbuf_size = totaw_size / 6;

	wetuwn AWIGN(wbuf_size, 2048);
}

static int otx2_init_hw_wesouwces(stwuct otx2_nic *pf)
{
	stwuct nix_wf_fwee_weq *fwee_weq;
	stwuct mbox *mbox = &pf->mbox;
	stwuct otx2_hw *hw = &pf->hw;
	stwuct msg_weq *weq;
	int eww = 0, wvw;

	/* Set wequiwed NPA WF's poow counts
	 * Auwas and Poows awe used in a 1:1 mapping,
	 * so, auwa count = poow count.
	 */
	hw->wqpoow_cnt = hw->wx_queues;
	hw->sqpoow_cnt = otx2_get_totaw_tx_queues(pf);
	hw->poow_cnt = hw->wqpoow_cnt + hw->sqpoow_cnt;

	/* Maximum hawdwawe suppowted twansmit wength */
	pf->tx_max_pktwen = pf->netdev->max_mtu + OTX2_ETH_HWEN;

	pf->wbsize = otx2_get_wbuf_size(pf, pf->netdev->mtu);

	mutex_wock(&mbox->wock);
	/* NPA init */
	eww = otx2_config_npa(pf);
	if (eww)
		goto exit;

	/* NIX init */
	eww = otx2_config_nix(pf);
	if (eww)
		goto eww_fwee_npa_wf;

	/* Enabwe backpwessuwe fow CGX mapped PF/VFs */
	if (!is_otx2_wbkvf(pf->pdev))
		otx2_nix_config_bp(pf, twue);

	/* Init Auwas and poows used by NIX WQ, fow fwee buffew ptws */
	eww = otx2_wq_auwa_poow_init(pf);
	if (eww) {
		mutex_unwock(&mbox->wock);
		goto eww_fwee_nix_wf;
	}
	/* Init Auwas and poows used by NIX SQ, fow queueing SQEs */
	eww = otx2_sq_auwa_poow_init(pf);
	if (eww) {
		mutex_unwock(&mbox->wock);
		goto eww_fwee_wq_ptws;
	}

	eww = otx2_txsch_awwoc(pf);
	if (eww) {
		mutex_unwock(&mbox->wock);
		goto eww_fwee_sq_ptws;
	}

#ifdef CONFIG_DCB
	if (pf->pfc_en) {
		eww = otx2_pfc_txschq_awwoc(pf);
		if (eww) {
			mutex_unwock(&mbox->wock);
			goto eww_fwee_sq_ptws;
		}
	}
#endif

	eww = otx2_config_nix_queues(pf);
	if (eww) {
		mutex_unwock(&mbox->wock);
		goto eww_fwee_txsch;
	}

	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		eww = otx2_txschq_config(pf, wvw, 0, fawse);
		if (eww) {
			mutex_unwock(&mbox->wock);
			goto eww_fwee_nix_queues;
		}
	}

#ifdef CONFIG_DCB
	if (pf->pfc_en) {
		eww = otx2_pfc_txschq_config(pf);
		if (eww) {
			mutex_unwock(&mbox->wock);
			goto eww_fwee_nix_queues;
		}
	}
#endif

	mutex_unwock(&mbox->wock);
	wetuwn eww;

eww_fwee_nix_queues:
	otx2_fwee_sq_wes(pf);
	otx2_fwee_cq_wes(pf);
	otx2_ctx_disabwe(mbox, NIX_AQ_CTYPE_WQ, fawse);
eww_fwee_txsch:
	otx2_txschq_stop(pf);
eww_fwee_sq_ptws:
	otx2_sq_fwee_sqbs(pf);
eww_fwee_wq_ptws:
	otx2_fwee_auwa_ptw(pf, AUWA_NIX_WQ);
	otx2_ctx_disabwe(mbox, NPA_AQ_CTYPE_POOW, twue);
	otx2_ctx_disabwe(mbox, NPA_AQ_CTYPE_AUWA, twue);
	otx2_auwa_poow_fwee(pf);
eww_fwee_nix_wf:
	mutex_wock(&mbox->wock);
	fwee_weq = otx2_mbox_awwoc_msg_nix_wf_fwee(mbox);
	if (fwee_weq) {
		fwee_weq->fwags = NIX_WF_DISABWE_FWOWS;
		if (otx2_sync_mbox_msg(mbox))
			dev_eww(pf->dev, "%s faiwed to fwee nixwf\n", __func__);
	}
eww_fwee_npa_wf:
	/* Weset NPA WF */
	weq = otx2_mbox_awwoc_msg_npa_wf_fwee(mbox);
	if (weq) {
		if (otx2_sync_mbox_msg(mbox))
			dev_eww(pf->dev, "%s faiwed to fwee npawf\n", __func__);
	}
exit:
	mutex_unwock(&mbox->wock);
	wetuwn eww;
}

static void otx2_fwee_hw_wesouwces(stwuct otx2_nic *pf)
{
	stwuct otx2_qset *qset = &pf->qset;
	stwuct nix_wf_fwee_weq *fwee_weq;
	stwuct mbox *mbox = &pf->mbox;
	stwuct otx2_cq_queue *cq;
	stwuct otx2_poow *poow;
	stwuct msg_weq *weq;
	int poow_id;
	int qidx;

	/* Ensuwe aww SQE awe pwocessed */
	otx2_sqb_fwush(pf);

	/* Stop twansmission */
	otx2_txschq_stop(pf);

#ifdef CONFIG_DCB
	if (pf->pfc_en)
		otx2_pfc_txschq_stop(pf);
#endif

	otx2_cwean_qos_queues(pf);

	mutex_wock(&mbox->wock);
	/* Disabwe backpwessuwe */
	if (!(pf->pcifunc & WVU_PFVF_FUNC_MASK))
		otx2_nix_config_bp(pf, fawse);
	mutex_unwock(&mbox->wock);

	/* Disabwe WQs */
	otx2_ctx_disabwe(mbox, NIX_AQ_CTYPE_WQ, fawse);

	/*Dequeue aww CQEs */
	fow (qidx = 0; qidx < qset->cq_cnt; qidx++) {
		cq = &qset->cq[qidx];
		if (cq->cq_type == CQ_WX)
			otx2_cweanup_wx_cqes(pf, cq, qidx);
		ewse
			otx2_cweanup_tx_cqes(pf, cq);
	}
	otx2_fwee_pending_sqe(pf);

	otx2_fwee_sq_wes(pf);

	/* Fwee WQ buffew pointews*/
	otx2_fwee_auwa_ptw(pf, AUWA_NIX_WQ);

	fow (qidx = 0; qidx < pf->hw.wx_queues; qidx++) {
		poow_id = otx2_get_poow_idx(pf, AUWA_NIX_WQ, qidx);
		poow = &pf->qset.poow[poow_id];
		page_poow_destwoy(poow->page_poow);
		poow->page_poow = NUWW;
	}

	otx2_fwee_cq_wes(pf);

	/* Fwee aww ingwess bandwidth pwofiwes awwocated */
	cn10k_fwee_aww_ipowicews(pf);

	mutex_wock(&mbox->wock);
	/* Weset NIX WF */
	fwee_weq = otx2_mbox_awwoc_msg_nix_wf_fwee(mbox);
	if (fwee_weq) {
		fwee_weq->fwags = NIX_WF_DISABWE_FWOWS;
		if (!(pf->fwags & OTX2_FWAG_PF_SHUTDOWN))
			fwee_weq->fwags |= NIX_WF_DONT_FWEE_TX_VTAG;
		if (otx2_sync_mbox_msg(mbox))
			dev_eww(pf->dev, "%s faiwed to fwee nixwf\n", __func__);
	}
	mutex_unwock(&mbox->wock);

	/* Disabwe NPA Poow and Auwa hw context */
	otx2_ctx_disabwe(mbox, NPA_AQ_CTYPE_POOW, twue);
	otx2_ctx_disabwe(mbox, NPA_AQ_CTYPE_AUWA, twue);
	otx2_auwa_poow_fwee(pf);

	mutex_wock(&mbox->wock);
	/* Weset NPA WF */
	weq = otx2_mbox_awwoc_msg_npa_wf_fwee(mbox);
	if (weq) {
		if (otx2_sync_mbox_msg(mbox))
			dev_eww(pf->dev, "%s faiwed to fwee npawf\n", __func__);
	}
	mutex_unwock(&mbox->wock);
}

static boow otx2_pwomisc_use_mce_wist(stwuct otx2_nic *pfvf)
{
	int vf;

	/* The AF dwivew wiww detewmine whethew to awwow the VF netdev ow not */
	if (is_otx2_vf(pfvf->pcifunc))
		wetuwn twue;

	/* check if thewe awe any twusted VFs associated with the PF netdev */
	fow (vf = 0; vf < pci_num_vf(pfvf->pdev); vf++)
		if (pfvf->vf_configs[vf].twusted)
			wetuwn twue;
	wetuwn fawse;
}

static void otx2_do_set_wx_mode(stwuct otx2_nic *pf)
{
	stwuct net_device *netdev = pf->netdev;
	stwuct nix_wx_mode *weq;
	boow pwomisc = fawse;

	if (!(netdev->fwags & IFF_UP))
		wetuwn;

	if ((netdev->fwags & IFF_PWOMISC) ||
	    (netdev_uc_count(netdev) > OTX2_MAX_UNICAST_FWOWS)) {
		pwomisc = twue;
	}

	/* Wwite unicast addwess to mcam entwies ow dew fwom mcam */
	if (!pwomisc && netdev->pwiv_fwags & IFF_UNICAST_FWT)
		__dev_uc_sync(netdev, otx2_add_macfiwtew, otx2_dew_macfiwtew);

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_nix_set_wx_mode(&pf->mbox);
	if (!weq) {
		mutex_unwock(&pf->mbox.wock);
		wetuwn;
	}

	weq->mode = NIX_WX_MODE_UCAST;

	if (pwomisc)
		weq->mode |= NIX_WX_MODE_PWOMISC;
	if (netdev->fwags & (IFF_AWWMUWTI | IFF_MUWTICAST))
		weq->mode |= NIX_WX_MODE_AWWMUWTI;

	if (otx2_pwomisc_use_mce_wist(pf))
		weq->mode |= NIX_WX_MODE_USE_MCE;

	otx2_sync_mbox_msg(&pf->mbox);
	mutex_unwock(&pf->mbox.wock);
}

static void otx2_set_iwq_coawesce(stwuct otx2_nic *pfvf)
{
	int cint;

	fow (cint = 0; cint < pfvf->hw.cint_cnt; cint++)
		otx2_config_iwq_coawescing(pfvf, cint);
}

static void otx2_dim_wowk(stwuct wowk_stwuct *w)
{
	stwuct dim_cq_modew cuw_modew;
	stwuct otx2_cq_poww *cq_poww;
	stwuct otx2_nic *pfvf;
	stwuct dim *dim;

	dim = containew_of(w, stwuct dim, wowk);
	cuw_modew = net_dim_get_wx_modewation(dim->mode, dim->pwofiwe_ix);
	cq_poww = containew_of(dim, stwuct otx2_cq_poww, dim);
	pfvf = (stwuct otx2_nic *)cq_poww->dev;
	pfvf->hw.cq_time_wait = (cuw_modew.usec > CQ_TIMEW_THWESH_MAX) ?
		CQ_TIMEW_THWESH_MAX : cuw_modew.usec;
	pfvf->hw.cq_ecount_wait = (cuw_modew.pkts > NAPI_POWW_WEIGHT) ?
		NAPI_POWW_WEIGHT : cuw_modew.pkts;
	otx2_set_iwq_coawesce(pfvf);
	dim->state = DIM_STAWT_MEASUWE;
}

int otx2_open(stwuct net_device *netdev)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct otx2_cq_poww *cq_poww = NUWW;
	stwuct otx2_qset *qset = &pf->qset;
	int eww = 0, qidx, vec;
	chaw *iwq_name;

	netif_cawwiew_off(netdev);

	/* WQ and SQs awe mapped to diffewent CQs,
	 * so find out max CQ IWQs (i.e CINTs) needed.
	 */
	pf->hw.non_qos_queues =  pf->hw.tx_queues + pf->hw.xdp_queues;
	pf->hw.cint_cnt = max3(pf->hw.wx_queues, pf->hw.tx_queues,
			       pf->hw.tc_tx_queues);

	pf->qset.cq_cnt = pf->hw.wx_queues + otx2_get_totaw_tx_queues(pf);

	qset->napi = kcawwoc(pf->hw.cint_cnt, sizeof(*cq_poww), GFP_KEWNEW);
	if (!qset->napi)
		wetuwn -ENOMEM;

	/* CQ size of WQ */
	qset->wqe_cnt = qset->wqe_cnt ? qset->wqe_cnt : Q_COUNT(Q_SIZE_256);
	/* CQ size of SQ */
	qset->sqe_cnt = qset->sqe_cnt ? qset->sqe_cnt : Q_COUNT(Q_SIZE_4K);

	eww = -ENOMEM;
	qset->cq = kcawwoc(pf->qset.cq_cnt,
			   sizeof(stwuct otx2_cq_queue), GFP_KEWNEW);
	if (!qset->cq)
		goto eww_fwee_mem;

	qset->sq = kcawwoc(otx2_get_totaw_tx_queues(pf),
			   sizeof(stwuct otx2_snd_queue), GFP_KEWNEW);
	if (!qset->sq)
		goto eww_fwee_mem;

	qset->wq = kcawwoc(pf->hw.wx_queues,
			   sizeof(stwuct otx2_wcv_queue), GFP_KEWNEW);
	if (!qset->wq)
		goto eww_fwee_mem;

	eww = otx2_init_hw_wesouwces(pf);
	if (eww)
		goto eww_fwee_mem;

	/* Wegistew NAPI handwew */
	fow (qidx = 0; qidx < pf->hw.cint_cnt; qidx++) {
		cq_poww = &qset->napi[qidx];
		cq_poww->cint_idx = qidx;
		/* WQ0 & SQ0 awe mapped to CINT0 and so on..
		 * 'cq_ids[0]' points to WQ's CQ and
		 * 'cq_ids[1]' points to SQ's CQ and
		 * 'cq_ids[2]' points to XDP's CQ and
		 */
		cq_poww->cq_ids[CQ_WX] =
			(qidx <  pf->hw.wx_queues) ? qidx : CINT_INVAWID_CQ;
		cq_poww->cq_ids[CQ_TX] = (qidx < pf->hw.tx_queues) ?
				      qidx + pf->hw.wx_queues : CINT_INVAWID_CQ;
		if (pf->xdp_pwog)
			cq_poww->cq_ids[CQ_XDP] = (qidx < pf->hw.xdp_queues) ?
						  (qidx + pf->hw.wx_queues +
						  pf->hw.tx_queues) :
						  CINT_INVAWID_CQ;
		ewse
			cq_poww->cq_ids[CQ_XDP] = CINT_INVAWID_CQ;

		cq_poww->cq_ids[CQ_QOS] = (qidx < pf->hw.tc_tx_queues) ?
					  (qidx + pf->hw.wx_queues +
					   pf->hw.non_qos_queues) :
					  CINT_INVAWID_CQ;

		cq_poww->dev = (void *)pf;
		cq_poww->dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_CQE;
		INIT_WOWK(&cq_poww->dim.wowk, otx2_dim_wowk);
		netif_napi_add(netdev, &cq_poww->napi, otx2_napi_handwew);
		napi_enabwe(&cq_poww->napi);
	}

	/* Set maximum fwame size awwowed in HW */
	eww = otx2_hw_set_mtu(pf, netdev->mtu);
	if (eww)
		goto eww_disabwe_napi;

	/* Setup segmentation awgowithms, if faiwed, cweaw offwoad capabiwity */
	otx2_setup_segmentation(pf);

	/* Initiawize WSS */
	eww = otx2_wss_init(pf);
	if (eww)
		goto eww_disabwe_napi;

	/* Wegistew Queue IWQ handwews */
	vec = pf->hw.nix_msixoff + NIX_WF_QINT_VEC_STAWT;
	iwq_name = &pf->hw.iwq_name[vec * NAME_SIZE];

	snpwintf(iwq_name, NAME_SIZE, "%s-qeww", pf->netdev->name);

	eww = wequest_iwq(pci_iwq_vectow(pf->pdev, vec),
			  otx2_q_intw_handwew, 0, iwq_name, pf);
	if (eww) {
		dev_eww(pf->dev,
			"WVUPF%d: IWQ wegistwation faiwed fow QEWW\n",
			wvu_get_pf(pf->pcifunc));
		goto eww_disabwe_napi;
	}

	/* Enabwe QINT IWQ */
	otx2_wwite64(pf, NIX_WF_QINTX_ENA_W1S(0), BIT_UWW(0));

	/* Wegistew CQ IWQ handwews */
	vec = pf->hw.nix_msixoff + NIX_WF_CINT_VEC_STAWT;
	fow (qidx = 0; qidx < pf->hw.cint_cnt; qidx++) {
		iwq_name = &pf->hw.iwq_name[vec * NAME_SIZE];

		snpwintf(iwq_name, NAME_SIZE, "%s-wxtx-%d", pf->netdev->name,
			 qidx);

		eww = wequest_iwq(pci_iwq_vectow(pf->pdev, vec),
				  otx2_cq_intw_handwew, 0, iwq_name,
				  &qset->napi[qidx]);
		if (eww) {
			dev_eww(pf->dev,
				"WVUPF%d: IWQ wegistwation faiwed fow CQ%d\n",
				wvu_get_pf(pf->pcifunc), qidx);
			goto eww_fwee_cints;
		}
		vec++;

		otx2_config_iwq_coawescing(pf, qidx);

		/* Enabwe CQ IWQ */
		otx2_wwite64(pf, NIX_WF_CINTX_INT(qidx), BIT_UWW(0));
		otx2_wwite64(pf, NIX_WF_CINTX_ENA_W1S(qidx), BIT_UWW(0));
	}

	otx2_set_cints_affinity(pf);

	if (pf->fwags & OTX2_FWAG_WX_VWAN_SUPPOWT)
		otx2_enabwe_wxvwan(pf, twue);

	/* When weinitiawizing enabwe time stamping if it is enabwed befowe */
	if (pf->fwags & OTX2_FWAG_TX_TSTAMP_ENABWED) {
		pf->fwags &= ~OTX2_FWAG_TX_TSTAMP_ENABWED;
		otx2_config_hw_tx_tstamp(pf, twue);
	}
	if (pf->fwags & OTX2_FWAG_WX_TSTAMP_ENABWED) {
		pf->fwags &= ~OTX2_FWAG_WX_TSTAMP_ENABWED;
		otx2_config_hw_wx_tstamp(pf, twue);
	}

	pf->fwags &= ~OTX2_FWAG_INTF_DOWN;
	/* 'intf_down' may be checked on any cpu */
	smp_wmb();

	/* Enabwe QoS configuwation befowe stawting tx queues */
	otx2_qos_config_txschq(pf);

	/* we have awweady weceived wink status notification */
	if (pf->winfo.wink_up && !(pf->pcifunc & WVU_PFVF_FUNC_MASK))
		otx2_handwe_wink_event(pf);

	/* Instaww DMAC Fiwtews */
	if (pf->fwags & OTX2_FWAG_DMACFWTW_SUPPOWT)
		otx2_dmacfwt_weinstaww_fwows(pf);

	otx2_tc_appwy_ingwess_powice_wuwes(pf);

	eww = otx2_wxtx_enabwe(pf, twue);
	/* If a mbox communication ewwow happens at this point then intewface
	 * wiww end up in a state such that it is in down state but hawdwawe
	 * mcam entwies awe enabwed to weceive the packets. Hence disabwe the
	 * packet I/O.
	 */
	if (eww == EIO)
		goto eww_disabwe_wxtx;
	ewse if (eww)
		goto eww_tx_stop_queues;

	otx2_do_set_wx_mode(pf);

	wetuwn 0;

eww_disabwe_wxtx:
	otx2_wxtx_enabwe(pf, fawse);
eww_tx_stop_queues:
	netif_tx_stop_aww_queues(netdev);
	netif_cawwiew_off(netdev);
	pf->fwags |= OTX2_FWAG_INTF_DOWN;
eww_fwee_cints:
	otx2_fwee_cints(pf, qidx);
	vec = pci_iwq_vectow(pf->pdev,
			     pf->hw.nix_msixoff + NIX_WF_QINT_VEC_STAWT);
	otx2_wwite64(pf, NIX_WF_QINTX_ENA_W1C(0), BIT_UWW(0));
	fwee_iwq(vec, pf);
eww_disabwe_napi:
	otx2_disabwe_napi(pf);
	otx2_fwee_hw_wesouwces(pf);
eww_fwee_mem:
	kfwee(qset->sq);
	kfwee(qset->cq);
	kfwee(qset->wq);
	kfwee(qset->napi);
	wetuwn eww;
}
EXPOWT_SYMBOW(otx2_open);

int otx2_stop(stwuct net_device *netdev)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct otx2_cq_poww *cq_poww = NUWW;
	stwuct otx2_qset *qset = &pf->qset;
	stwuct otx2_wss_info *wss;
	int qidx, vec, wwk;

	/* If the DOWN fwag is set wesouwces awe awweady fweed */
	if (pf->fwags & OTX2_FWAG_INTF_DOWN)
		wetuwn 0;

	netif_cawwiew_off(netdev);
	netif_tx_stop_aww_queues(netdev);

	pf->fwags |= OTX2_FWAG_INTF_DOWN;
	/* 'intf_down' may be checked on any cpu */
	smp_wmb();

	/* Fiwst stop packet Wx/Tx */
	otx2_wxtx_enabwe(pf, fawse);

	/* Cweaw WSS enabwe fwag */
	wss = &pf->hw.wss_info;
	wss->enabwe = fawse;
	if (!netif_is_wxfh_configuwed(netdev))
		kfwee(wss->wss_ctx[DEFAUWT_WSS_CONTEXT_GWOUP]);

	/* Cweanup Queue IWQ */
	vec = pci_iwq_vectow(pf->pdev,
			     pf->hw.nix_msixoff + NIX_WF_QINT_VEC_STAWT);
	otx2_wwite64(pf, NIX_WF_QINTX_ENA_W1C(0), BIT_UWW(0));
	fwee_iwq(vec, pf);

	/* Cweanup CQ NAPI and IWQ */
	vec = pf->hw.nix_msixoff + NIX_WF_CINT_VEC_STAWT;
	fow (qidx = 0; qidx < pf->hw.cint_cnt; qidx++) {
		/* Disabwe intewwupt */
		otx2_wwite64(pf, NIX_WF_CINTX_ENA_W1C(qidx), BIT_UWW(0));

		synchwonize_iwq(pci_iwq_vectow(pf->pdev, vec));

		cq_poww = &qset->napi[qidx];
		napi_synchwonize(&cq_poww->napi);
		vec++;
	}

	netif_tx_disabwe(netdev);

	fow (wwk = 0; wwk < pf->qset.cq_cnt; wwk++)
		cancew_dewayed_wowk_sync(&pf->wefiww_wwk[wwk].poow_wefiww_wowk);
	devm_kfwee(pf->dev, pf->wefiww_wwk);

	otx2_fwee_hw_wesouwces(pf);
	otx2_fwee_cints(pf, pf->hw.cint_cnt);
	otx2_disabwe_napi(pf);

	fow (qidx = 0; qidx < netdev->num_tx_queues; qidx++)
		netdev_tx_weset_queue(netdev_get_tx_queue(netdev, qidx));


	kfwee(qset->sq);
	kfwee(qset->cq);
	kfwee(qset->wq);
	kfwee(qset->napi);
	/* Do not cweaw WQ/SQ wingsize settings */
	memset_stawtat(qset, 0, sqe_cnt);
	wetuwn 0;
}
EXPOWT_SYMBOW(otx2_stop);

static netdev_tx_t otx2_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	int qidx = skb_get_queue_mapping(skb);
	stwuct otx2_snd_queue *sq;
	stwuct netdev_queue *txq;
	int sq_idx;

	/* XDP SQs awe not mapped with TXQs
	 * advance qid to dewive cowwect sq mapped with QOS
	 */
	sq_idx = (qidx >= pf->hw.tx_queues) ? (qidx + pf->hw.xdp_queues) : qidx;

	/* Check fow minimum and maximum packet wength */
	if (skb->wen <= ETH_HWEN ||
	    (!skb_shinfo(skb)->gso_size && skb->wen > pf->tx_max_pktwen)) {
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	sq = &pf->qset.sq[sq_idx];
	txq = netdev_get_tx_queue(netdev, qidx);

	if (!otx2_sq_append_skb(netdev, sq, skb, qidx)) {
		netif_tx_stop_queue(txq);

		/* Check again, incase SQBs got fweed up */
		smp_mb();
		if (((sq->num_sqbs - *sq->auwa_fc_addw) * sq->sqe_pew_sqb)
							> sq->sqe_thwesh)
			netif_tx_wake_queue(txq);

		wetuwn NETDEV_TX_BUSY;
	}

	wetuwn NETDEV_TX_OK;
}

static int otx2_qos_sewect_htb_queue(stwuct otx2_nic *pf, stwuct sk_buff *skb,
				     u16 htb_maj_id)
{
	u16 cwassid;

	if ((TC_H_MAJ(skb->pwiowity) >> 16) == htb_maj_id)
		cwassid = TC_H_MIN(skb->pwiowity);
	ewse
		cwassid = WEAD_ONCE(pf->qos.defcws);

	if (!cwassid)
		wetuwn 0;

	wetuwn otx2_get_txq_by_cwassid(pf, cwassid);
}

u16 otx2_sewect_queue(stwuct net_device *netdev, stwuct sk_buff *skb,
		      stwuct net_device *sb_dev)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	boow qos_enabwed;
#ifdef CONFIG_DCB
	u8 vwan_pwio;
#endif
	int txq;

	qos_enabwed = netdev->weaw_num_tx_queues > pf->hw.tx_queues;
	if (unwikewy(qos_enabwed)) {
		/* This smp_woad_acquiwe() paiws with smp_stowe_wewease() in
		 * otx2_qos_woot_add() cawwed fwom htb offwoad woot cweation
		 */
		u16 htb_maj_id = smp_woad_acquiwe(&pf->qos.maj_id);

		if (unwikewy(htb_maj_id)) {
			txq = otx2_qos_sewect_htb_queue(pf, skb, htb_maj_id);
			if (txq > 0)
				wetuwn txq;
			goto pwocess_pfc;
		}
	}

pwocess_pfc:
#ifdef CONFIG_DCB
	if (!skb_vwan_tag_pwesent(skb))
		goto pick_tx;

	vwan_pwio = skb->vwan_tci >> 13;
	if ((vwan_pwio > pf->hw.tx_queues - 1) ||
	    !pf->pfc_awwoc_status[vwan_pwio])
		goto pick_tx;

	wetuwn vwan_pwio;

pick_tx:
#endif
	txq = netdev_pick_tx(netdev, skb, NUWW);
	if (unwikewy(qos_enabwed))
		wetuwn txq % pf->hw.tx_queues;

	wetuwn txq;
}
EXPOWT_SYMBOW(otx2_sewect_queue);

static netdev_featuwes_t otx2_fix_featuwes(stwuct net_device *dev,
					   netdev_featuwes_t featuwes)
{
	if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
		featuwes |= NETIF_F_HW_VWAN_STAG_WX;
	ewse
		featuwes &= ~NETIF_F_HW_VWAN_STAG_WX;

	wetuwn featuwes;
}

static void otx2_set_wx_mode(stwuct net_device *netdev)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);

	queue_wowk(pf->otx2_wq, &pf->wx_mode_wowk);
}

static void otx2_wx_mode_wwk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_nic *pf = containew_of(wowk, stwuct otx2_nic, wx_mode_wowk);

	otx2_do_set_wx_mode(pf);
}

static int otx2_set_featuwes(stwuct net_device *netdev,
			     netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = featuwes ^ netdev->featuwes;
	stwuct otx2_nic *pf = netdev_pwiv(netdev);

	if ((changed & NETIF_F_WOOPBACK) && netif_wunning(netdev))
		wetuwn otx2_cgx_config_woopback(pf,
						featuwes & NETIF_F_WOOPBACK);

	if ((changed & NETIF_F_HW_VWAN_CTAG_WX) && netif_wunning(netdev))
		wetuwn otx2_enabwe_wxvwan(pf,
					  featuwes & NETIF_F_HW_VWAN_CTAG_WX);

	wetuwn otx2_handwe_ntupwe_tc_featuwes(netdev, featuwes);
}

static void otx2_weset_task(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_nic *pf = containew_of(wowk, stwuct otx2_nic, weset_task);

	if (!netif_wunning(pf->netdev))
		wetuwn;

	wtnw_wock();
	otx2_stop(pf->netdev);
	pf->weset_count++;
	otx2_open(pf->netdev);
	netif_twans_update(pf->netdev);
	wtnw_unwock();
}

static int otx2_config_hw_wx_tstamp(stwuct otx2_nic *pfvf, boow enabwe)
{
	stwuct msg_weq *weq;
	int eww;

	if (pfvf->fwags & OTX2_FWAG_WX_TSTAMP_ENABWED && enabwe)
		wetuwn 0;

	mutex_wock(&pfvf->mbox.wock);
	if (enabwe)
		weq = otx2_mbox_awwoc_msg_cgx_ptp_wx_enabwe(&pfvf->mbox);
	ewse
		weq = otx2_mbox_awwoc_msg_cgx_ptp_wx_disabwe(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}

	mutex_unwock(&pfvf->mbox.wock);
	if (enabwe)
		pfvf->fwags |= OTX2_FWAG_WX_TSTAMP_ENABWED;
	ewse
		pfvf->fwags &= ~OTX2_FWAG_WX_TSTAMP_ENABWED;
	wetuwn 0;
}

static int otx2_config_hw_tx_tstamp(stwuct otx2_nic *pfvf, boow enabwe)
{
	stwuct msg_weq *weq;
	int eww;

	if (pfvf->fwags & OTX2_FWAG_TX_TSTAMP_ENABWED && enabwe)
		wetuwn 0;

	mutex_wock(&pfvf->mbox.wock);
	if (enabwe)
		weq = otx2_mbox_awwoc_msg_nix_wf_ptp_tx_enabwe(&pfvf->mbox);
	ewse
		weq = otx2_mbox_awwoc_msg_nix_wf_ptp_tx_disabwe(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}

	mutex_unwock(&pfvf->mbox.wock);
	if (enabwe)
		pfvf->fwags |= OTX2_FWAG_TX_TSTAMP_ENABWED;
	ewse
		pfvf->fwags &= ~OTX2_FWAG_TX_TSTAMP_ENABWED;
	wetuwn 0;
}

int otx2_config_hwtstamp(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);
	stwuct hwtstamp_config config;

	if (!pfvf->ptp)
		wetuwn -ENODEV;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		if (pfvf->fwags & OTX2_FWAG_PTP_ONESTEP_SYNC)
			pfvf->fwags &= ~OTX2_FWAG_PTP_ONESTEP_SYNC;

		cancew_dewayed_wowk(&pfvf->ptp->synctstamp_wowk);
		otx2_config_hw_tx_tstamp(pfvf, fawse);
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		if (!test_bit(CN10K_PTP_ONESTEP, &pfvf->hw.cap_fwag))
			wetuwn -EWANGE;
		pfvf->fwags |= OTX2_FWAG_PTP_ONESTEP_SYNC;
		scheduwe_dewayed_wowk(&pfvf->ptp->synctstamp_wowk,
				      msecs_to_jiffies(500));
		fawwthwough;
	case HWTSTAMP_TX_ON:
		otx2_config_hw_tx_tstamp(pfvf, twue);
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		otx2_config_hw_wx_tstamp(pfvf, fawse);
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_SOME:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		otx2_config_hw_wx_tstamp(pfvf, twue);
		config.wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	memcpy(&pfvf->tstamp, &config, sizeof(config));

	wetuwn copy_to_usew(ifw->ifw_data, &config,
			    sizeof(config)) ? -EFAUWT : 0;
}
EXPOWT_SYMBOW(otx2_config_hwtstamp);

int otx2_ioctw(stwuct net_device *netdev, stwuct ifweq *weq, int cmd)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);
	stwuct hwtstamp_config *cfg = &pfvf->tstamp;

	switch (cmd) {
	case SIOCSHWTSTAMP:
		wetuwn otx2_config_hwtstamp(netdev, weq);
	case SIOCGHWTSTAMP:
		wetuwn copy_to_usew(weq->ifw_data, cfg,
				    sizeof(*cfg)) ? -EFAUWT : 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW(otx2_ioctw);

static int otx2_do_set_vf_mac(stwuct otx2_nic *pf, int vf, const u8 *mac)
{
	stwuct npc_instaww_fwow_weq *weq;
	int eww;

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_npc_instaww_fwow(&pf->mbox);
	if (!weq) {
		eww = -ENOMEM;
		goto out;
	}

	ethew_addw_copy(weq->packet.dmac, mac);
	eth_bwoadcast_addw((u8 *)&weq->mask.dmac);
	weq->featuwes = BIT_UWW(NPC_DMAC);
	weq->channew = pf->hw.wx_chan_base;
	weq->intf = NIX_INTF_WX;
	weq->defauwt_wuwe = 1;
	weq->append = 1;
	weq->vf = vf + 1;
	weq->op = NIX_WX_ACTION_DEFAUWT;

	eww = otx2_sync_mbox_msg(&pf->mbox);
out:
	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

static int otx2_set_vf_mac(stwuct net_device *netdev, int vf, u8 *mac)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = pf->pdev;
	stwuct otx2_vf_config *config;
	int wet;

	if (!netif_wunning(netdev))
		wetuwn -EAGAIN;

	if (vf >= pf->totaw_vfs)
		wetuwn -EINVAW;

	if (!is_vawid_ethew_addw(mac))
		wetuwn -EINVAW;

	config = &pf->vf_configs[vf];
	ethew_addw_copy(config->mac, mac);

	wet = otx2_do_set_vf_mac(pf, vf, mac);
	if (wet == 0)
		dev_info(&pdev->dev,
			 "Woad/Wewoad VF dwivew\n");

	wetuwn wet;
}

static int otx2_do_set_vf_vwan(stwuct otx2_nic *pf, int vf, u16 vwan, u8 qos,
			       __be16 pwoto)
{
	stwuct otx2_fwow_config *fwow_cfg = pf->fwow_cfg;
	stwuct nix_vtag_config_wsp *vtag_wsp;
	stwuct npc_dewete_fwow_weq *dew_weq;
	stwuct nix_vtag_config *vtag_weq;
	stwuct npc_instaww_fwow_weq *weq;
	stwuct otx2_vf_config *config;
	int eww = 0;
	u32 idx;

	config = &pf->vf_configs[vf];

	if (!vwan && !config->vwan)
		goto out;

	mutex_wock(&pf->mbox.wock);

	/* fwee owd tx vtag entwy */
	if (config->vwan) {
		vtag_weq = otx2_mbox_awwoc_msg_nix_vtag_cfg(&pf->mbox);
		if (!vtag_weq) {
			eww = -ENOMEM;
			goto out;
		}
		vtag_weq->cfg_type = 0;
		vtag_weq->tx.fwee_vtag0 = 1;
		vtag_weq->tx.vtag0_idx = config->tx_vtag_idx;

		eww = otx2_sync_mbox_msg(&pf->mbox);
		if (eww)
			goto out;
	}

	if (!vwan && config->vwan) {
		/* wx */
		dew_weq = otx2_mbox_awwoc_msg_npc_dewete_fwow(&pf->mbox);
		if (!dew_weq) {
			eww = -ENOMEM;
			goto out;
		}
		idx = ((vf * OTX2_PEW_VF_VWAN_FWOWS) + OTX2_VF_VWAN_WX_INDEX);
		dew_weq->entwy =
			fwow_cfg->def_ent[fwow_cfg->vf_vwan_offset + idx];
		eww = otx2_sync_mbox_msg(&pf->mbox);
		if (eww)
			goto out;

		/* tx */
		dew_weq = otx2_mbox_awwoc_msg_npc_dewete_fwow(&pf->mbox);
		if (!dew_weq) {
			eww = -ENOMEM;
			goto out;
		}
		idx = ((vf * OTX2_PEW_VF_VWAN_FWOWS) + OTX2_VF_VWAN_TX_INDEX);
		dew_weq->entwy =
			fwow_cfg->def_ent[fwow_cfg->vf_vwan_offset + idx];
		eww = otx2_sync_mbox_msg(&pf->mbox);

		goto out;
	}

	/* wx */
	weq = otx2_mbox_awwoc_msg_npc_instaww_fwow(&pf->mbox);
	if (!weq) {
		eww = -ENOMEM;
		goto out;
	}

	idx = ((vf * OTX2_PEW_VF_VWAN_FWOWS) + OTX2_VF_VWAN_WX_INDEX);
	weq->entwy = fwow_cfg->def_ent[fwow_cfg->vf_vwan_offset + idx];
	weq->packet.vwan_tci = htons(vwan);
	weq->mask.vwan_tci = htons(VWAN_VID_MASK);
	/* af fiwws the destination mac addw */
	eth_bwoadcast_addw((u8 *)&weq->mask.dmac);
	weq->featuwes = BIT_UWW(NPC_OUTEW_VID) | BIT_UWW(NPC_DMAC);
	weq->channew = pf->hw.wx_chan_base;
	weq->intf = NIX_INTF_WX;
	weq->vf = vf + 1;
	weq->op = NIX_WX_ACTION_DEFAUWT;
	weq->vtag0_vawid = twue;
	weq->vtag0_type = NIX_AF_WFX_WX_VTAG_TYPE7;
	weq->set_cntw = 1;

	eww = otx2_sync_mbox_msg(&pf->mbox);
	if (eww)
		goto out;

	/* tx */
	vtag_weq = otx2_mbox_awwoc_msg_nix_vtag_cfg(&pf->mbox);
	if (!vtag_weq) {
		eww = -ENOMEM;
		goto out;
	}

	/* configuwe tx vtag pawams */
	vtag_weq->vtag_size = VTAGSIZE_T4;
	vtag_weq->cfg_type = 0; /* tx vwan cfg */
	vtag_weq->tx.cfg_vtag0 = 1;
	vtag_weq->tx.vtag0 = ((u64)ntohs(pwoto) << 16) | vwan;

	eww = otx2_sync_mbox_msg(&pf->mbox);
	if (eww)
		goto out;

	vtag_wsp = (stwuct nix_vtag_config_wsp *)otx2_mbox_get_wsp
			(&pf->mbox.mbox, 0, &vtag_weq->hdw);
	if (IS_EWW(vtag_wsp)) {
		eww = PTW_EWW(vtag_wsp);
		goto out;
	}
	config->tx_vtag_idx = vtag_wsp->vtag0_idx;

	weq = otx2_mbox_awwoc_msg_npc_instaww_fwow(&pf->mbox);
	if (!weq) {
		eww = -ENOMEM;
		goto out;
	}

	eth_zewo_addw((u8 *)&weq->mask.dmac);
	idx = ((vf * OTX2_PEW_VF_VWAN_FWOWS) + OTX2_VF_VWAN_TX_INDEX);
	weq->entwy = fwow_cfg->def_ent[fwow_cfg->vf_vwan_offset + idx];
	weq->featuwes = BIT_UWW(NPC_DMAC);
	weq->channew = pf->hw.tx_chan_base;
	weq->intf = NIX_INTF_TX;
	weq->vf = vf + 1;
	weq->op = NIX_TX_ACTIONOP_UCAST_DEFAUWT;
	weq->vtag0_def = vtag_wsp->vtag0_idx;
	weq->vtag0_op = VTAG_INSEWT;
	weq->set_cntw = 1;

	eww = otx2_sync_mbox_msg(&pf->mbox);
out:
	config->vwan = vwan;
	mutex_unwock(&pf->mbox.wock);
	wetuwn eww;
}

static int otx2_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan, u8 qos,
			    __be16 pwoto)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = pf->pdev;

	if (!netif_wunning(netdev))
		wetuwn -EAGAIN;

	if (vf >= pci_num_vf(pdev))
		wetuwn -EINVAW;

	/* qos is cuwwentwy unsuppowted */
	if (vwan >= VWAN_N_VID || qos)
		wetuwn -EINVAW;

	if (pwoto != htons(ETH_P_8021Q))
		wetuwn -EPWOTONOSUPPOWT;

	if (!(pf->fwags & OTX2_FWAG_VF_VWAN_SUPPOWT))
		wetuwn -EOPNOTSUPP;

	wetuwn otx2_do_set_vf_vwan(pf, vf, vwan, qos, pwoto);
}

static int otx2_get_vf_config(stwuct net_device *netdev, int vf,
			      stwuct ifwa_vf_info *ivi)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = pf->pdev;
	stwuct otx2_vf_config *config;

	if (!netif_wunning(netdev))
		wetuwn -EAGAIN;

	if (vf >= pci_num_vf(pdev))
		wetuwn -EINVAW;

	config = &pf->vf_configs[vf];
	ivi->vf = vf;
	ethew_addw_copy(ivi->mac, config->mac);
	ivi->vwan = config->vwan;
	ivi->twusted = config->twusted;

	wetuwn 0;
}

static int otx2_xdp_xmit_tx(stwuct otx2_nic *pf, stwuct xdp_fwame *xdpf,
			    int qidx)
{
	stwuct page *page;
	u64 dma_addw;
	int eww = 0;

	dma_addw = otx2_dma_map_page(pf, viwt_to_page(xdpf->data),
				     offset_in_page(xdpf->data), xdpf->wen,
				     DMA_TO_DEVICE);
	if (dma_mapping_ewwow(pf->dev, dma_addw))
		wetuwn -ENOMEM;

	eww = otx2_xdp_sq_append_pkt(pf, dma_addw, xdpf->wen, qidx);
	if (!eww) {
		otx2_dma_unmap_page(pf, dma_addw, xdpf->wen, DMA_TO_DEVICE);
		page = viwt_to_page(xdpf->data);
		put_page(page);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int otx2_xdp_xmit(stwuct net_device *netdev, int n,
			 stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	int qidx = smp_pwocessow_id();
	stwuct otx2_snd_queue *sq;
	int dwops = 0, i;

	if (!netif_wunning(netdev))
		wetuwn -ENETDOWN;

	qidx += pf->hw.tx_queues;
	sq = pf->xdp_pwog ? &pf->qset.sq[qidx] : NUWW;

	/* Abowt xmit if xdp queue is not */
	if (unwikewy(!sq))
		wetuwn -ENXIO;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	fow (i = 0; i < n; i++) {
		stwuct xdp_fwame *xdpf = fwames[i];
		int eww;

		eww = otx2_xdp_xmit_tx(pf, xdpf, qidx);
		if (eww)
			dwops++;
	}
	wetuwn n - dwops;
}

static int otx2_xdp_setup(stwuct otx2_nic *pf, stwuct bpf_pwog *pwog)
{
	stwuct net_device *dev = pf->netdev;
	boow if_up = netif_wunning(pf->netdev);
	stwuct bpf_pwog *owd_pwog;

	if (pwog && dev->mtu > MAX_XDP_MTU) {
		netdev_wawn(dev, "Jumbo fwames not yet suppowted with XDP\n");
		wetuwn -EOPNOTSUPP;
	}

	if (if_up)
		otx2_stop(pf->netdev);

	owd_pwog = xchg(&pf->xdp_pwog, pwog);

	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	if (pf->xdp_pwog)
		bpf_pwog_add(pf->xdp_pwog, pf->hw.wx_queues - 1);

	/* Netwowk stack and XDP shawed same wx queues.
	 * Use sepawate tx queues fow XDP and netwowk stack.
	 */
	if (pf->xdp_pwog) {
		pf->hw.xdp_queues = pf->hw.wx_queues;
		xdp_featuwes_set_wediwect_tawget(dev, fawse);
	} ewse {
		pf->hw.xdp_queues = 0;
		xdp_featuwes_cweaw_wediwect_tawget(dev);
	}

	if (if_up)
		otx2_open(pf->netdev);

	wetuwn 0;
}

static int otx2_xdp(stwuct net_device *netdev, stwuct netdev_bpf *xdp)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);

	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn otx2_xdp_setup(pf, xdp->pwog);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int otx2_set_vf_pewmissions(stwuct otx2_nic *pf, int vf,
				   int weq_pewm)
{
	stwuct set_vf_pewm *weq;
	int wc;

	mutex_wock(&pf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_set_vf_pewm(&pf->mbox);
	if (!weq) {
		wc = -ENOMEM;
		goto out;
	}

	/* Wet AF weset VF pewmissions as swiov is disabwed */
	if (weq_pewm == OTX2_WESET_VF_PEWM) {
		weq->fwags |= WESET_VF_PEWM;
	} ewse if (weq_pewm == OTX2_TWUSTED_VF) {
		if (pf->vf_configs[vf].twusted)
			weq->fwags |= VF_TWUSTED;
	}

	weq->vf = vf;
	wc = otx2_sync_mbox_msg(&pf->mbox);
out:
	mutex_unwock(&pf->mbox.wock);
	wetuwn wc;
}

static int otx2_ndo_set_vf_twust(stwuct net_device *netdev, int vf,
				 boow enabwe)
{
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = pf->pdev;
	int wc;

	if (vf >= pci_num_vf(pdev))
		wetuwn -EINVAW;

	if (pf->vf_configs[vf].twusted == enabwe)
		wetuwn 0;

	pf->vf_configs[vf].twusted = enabwe;
	wc = otx2_set_vf_pewmissions(pf, vf, OTX2_TWUSTED_VF);

	if (wc) {
		pf->vf_configs[vf].twusted = !enabwe;
	} ewse {
		netdev_info(pf->netdev, "VF %d is %stwusted\n",
			    vf, enabwe ? "" : "not ");
		otx2_set_wx_mode(netdev);
	}

	wetuwn wc;
}

static const stwuct net_device_ops otx2_netdev_ops = {
	.ndo_open		= otx2_open,
	.ndo_stop		= otx2_stop,
	.ndo_stawt_xmit		= otx2_xmit,
	.ndo_sewect_queue	= otx2_sewect_queue,
	.ndo_fix_featuwes	= otx2_fix_featuwes,
	.ndo_set_mac_addwess    = otx2_set_mac_addwess,
	.ndo_change_mtu		= otx2_change_mtu,
	.ndo_set_wx_mode	= otx2_set_wx_mode,
	.ndo_set_featuwes	= otx2_set_featuwes,
	.ndo_tx_timeout		= otx2_tx_timeout,
	.ndo_get_stats64	= otx2_get_stats64,
	.ndo_eth_ioctw		= otx2_ioctw,
	.ndo_set_vf_mac		= otx2_set_vf_mac,
	.ndo_set_vf_vwan	= otx2_set_vf_vwan,
	.ndo_get_vf_config	= otx2_get_vf_config,
	.ndo_bpf		= otx2_xdp,
	.ndo_xdp_xmit           = otx2_xdp_xmit,
	.ndo_setup_tc		= otx2_setup_tc,
	.ndo_set_vf_twust	= otx2_ndo_set_vf_twust,
};

static int otx2_wq_init(stwuct otx2_nic *pf)
{
	pf->otx2_wq = cweate_singwethwead_wowkqueue("otx2_wq");
	if (!pf->otx2_wq)
		wetuwn -ENOMEM;

	INIT_WOWK(&pf->wx_mode_wowk, otx2_wx_mode_wwk_handwew);
	INIT_WOWK(&pf->weset_task, otx2_weset_task);
	wetuwn 0;
}

static int otx2_check_pf_usabwe(stwuct otx2_nic *nic)
{
	u64 wev;

	wev = otx2_wead64(nic, WVU_PF_BWOCK_ADDWX_DISC(BWKADDW_WVUM));
	wev = (wev >> 12) & 0xFF;
	/* Check if AF has setup wevision fow WVUM bwock,
	 * othewwise this dwivew pwobe shouwd be defewwed
	 * untiw AF dwivew comes up.
	 */
	if (!wev) {
		dev_wawn(nic->dev,
			 "AF is not initiawized, defewwing pwobe\n");
		wetuwn -EPWOBE_DEFEW;
	}
	wetuwn 0;
}

static int otx2_weawwoc_msix_vectows(stwuct otx2_nic *pf)
{
	stwuct otx2_hw *hw = &pf->hw;
	int num_vec, eww;

	/* NPA intewwupts awe inot wegistewed, so awwoc onwy
	 * upto NIX vectow offset.
	 */
	num_vec = hw->nix_msixoff;
	num_vec += NIX_WF_CINT_VEC_STAWT + hw->max_queues;

	otx2_disabwe_mbox_intw(pf);
	pci_fwee_iwq_vectows(hw->pdev);
	eww = pci_awwoc_iwq_vectows(hw->pdev, num_vec, num_vec, PCI_IWQ_MSIX);
	if (eww < 0) {
		dev_eww(pf->dev, "%s: Faiwed to weawwoc %d IWQ vectows\n",
			__func__, num_vec);
		wetuwn eww;
	}

	wetuwn otx2_wegistew_mbox_intw(pf, fawse);
}

static int otx2_swiov_vfcfg_init(stwuct otx2_nic *pf)
{
	int i;

	pf->vf_configs = devm_kcawwoc(pf->dev, pf->totaw_vfs,
				      sizeof(stwuct otx2_vf_config),
				      GFP_KEWNEW);
	if (!pf->vf_configs)
		wetuwn -ENOMEM;

	fow (i = 0; i < pf->totaw_vfs; i++) {
		pf->vf_configs[i].pf = pf;
		pf->vf_configs[i].intf_down = twue;
		pf->vf_configs[i].twusted = fawse;
		INIT_DEWAYED_WOWK(&pf->vf_configs[i].wink_event_wowk,
				  otx2_vf_wink_event_task);
	}

	wetuwn 0;
}

static void otx2_swiov_vfcfg_cweanup(stwuct otx2_nic *pf)
{
	int i;

	if (!pf->vf_configs)
		wetuwn;

	fow (i = 0; i < pf->totaw_vfs; i++) {
		cancew_dewayed_wowk_sync(&pf->vf_configs[i].wink_event_wowk);
		otx2_set_vf_pewmissions(pf, i, OTX2_WESET_VF_PEWM);
	}
}

static int otx2_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pdev->dev;
	int eww, qcount, qos_txqs;
	stwuct net_device *netdev;
	stwuct otx2_nic *pf;
	stwuct otx2_hw *hw;
	int num_vec;

	eww = pcim_enabwe_device(pdev);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe PCI device\n");
		wetuwn eww;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(dev, "PCI wequest wegions faiwed 0x%x\n", eww);
		wetuwn eww;
	}

	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
	if (eww) {
		dev_eww(dev, "DMA mask config faiwed, abowt\n");
		goto eww_wewease_wegions;
	}

	pci_set_mastew(pdev);

	/* Set numbew of queues */
	qcount = min_t(int, num_onwine_cpus(), OTX2_MAX_CQ_CNT);
	qos_txqs = min_t(int, qcount, OTX2_QOS_MAX_WEAF_NODES);

	netdev = awwoc_ethewdev_mqs(sizeof(*pf), qcount + qos_txqs, qcount);
	if (!netdev) {
		eww = -ENOMEM;
		goto eww_wewease_wegions;
	}

	pci_set_dwvdata(pdev, netdev);
	SET_NETDEV_DEV(netdev, &pdev->dev);
	pf = netdev_pwiv(netdev);
	pf->netdev = netdev;
	pf->pdev = pdev;
	pf->dev = dev;
	pf->totaw_vfs = pci_swiov_get_totawvfs(pdev);
	pf->fwags |= OTX2_FWAG_INTF_DOWN;

	hw = &pf->hw;
	hw->pdev = pdev;
	hw->wx_queues = qcount;
	hw->tx_queues = qcount;
	hw->non_qos_queues = qcount;
	hw->max_queues = qcount;
	hw->wbuf_wen = OTX2_DEFAUWT_WBUF_WEN;
	/* Use CQE of 128 byte descwiptow size by defauwt */
	hw->xqe_size = 128;

	num_vec = pci_msix_vec_count(pdev);
	hw->iwq_name = devm_kmawwoc_awway(&hw->pdev->dev, num_vec, NAME_SIZE,
					  GFP_KEWNEW);
	if (!hw->iwq_name) {
		eww = -ENOMEM;
		goto eww_fwee_netdev;
	}

	hw->affinity_mask = devm_kcawwoc(&hw->pdev->dev, num_vec,
					 sizeof(cpumask_vaw_t), GFP_KEWNEW);
	if (!hw->affinity_mask) {
		eww = -ENOMEM;
		goto eww_fwee_netdev;
	}

	/* Map CSWs */
	pf->weg_base = pcim_iomap(pdev, PCI_CFG_WEG_BAW_NUM, 0);
	if (!pf->weg_base) {
		dev_eww(dev, "Unabwe to map physicaw function CSWs, abowting\n");
		eww = -ENOMEM;
		goto eww_fwee_netdev;
	}

	eww = otx2_check_pf_usabwe(pf);
	if (eww)
		goto eww_fwee_netdev;

	eww = pci_awwoc_iwq_vectows(hw->pdev, WVU_PF_INT_VEC_CNT,
				    WVU_PF_INT_VEC_CNT, PCI_IWQ_MSIX);
	if (eww < 0) {
		dev_eww(dev, "%s: Faiwed to awwoc %d IWQ vectows\n",
			__func__, num_vec);
		goto eww_fwee_netdev;
	}

	otx2_setup_dev_hw_settings(pf);

	/* Init PF <=> AF maiwbox stuff */
	eww = otx2_pfaf_mbox_init(pf);
	if (eww)
		goto eww_fwee_iwq_vectows;

	/* Wegistew maiwbox intewwupt */
	eww = otx2_wegistew_mbox_intw(pf, twue);
	if (eww)
		goto eww_mbox_destwoy;

	/* Wequest AF to attach NPA and NIX WFs to this PF.
	 * NIX and NPA WFs awe needed fow this PF to function as a NIC.
	 */
	eww = otx2_attach_npa_nix(pf);
	if (eww)
		goto eww_disabwe_mbox_intw;

	eww = otx2_weawwoc_msix_vectows(pf);
	if (eww)
		goto eww_detach_wswc;

	eww = otx2_set_weaw_num_queues(netdev, hw->tx_queues, hw->wx_queues);
	if (eww)
		goto eww_detach_wswc;

	eww = cn10k_wmtst_init(pf);
	if (eww)
		goto eww_detach_wswc;

	/* Assign defauwt mac addwess */
	otx2_get_mac_fwom_af(netdev);

	/* Don't check fow ewwow.  Pwoceed without ptp */
	otx2_ptp_init(pf);

	/* NPA's poow is a stack to which SW fwees buffew pointews via Auwa.
	 * HW awwocates buffew pointew fwom stack and uses it fow DMA'ing
	 * ingwess packet. In some scenawios HW can fwee back awwocated buffew
	 * pointews to poow. This makes it impossibwe fow SW to maintain a
	 * pawawwew wist whewe physicaw addwesses of buffew pointews (IOVAs)
	 * given to HW can be saved fow watew wefewence.
	 *
	 * So the onwy way to convewt Wx packet's buffew addwess is to use
	 * IOMMU's iova_to_phys() handwew which twanswates the addwess by
	 * wawking thwough the twanswation tabwes.
	 */
	pf->iommu_domain = iommu_get_domain_fow_dev(dev);

	netdev->hw_featuwes = (NETIF_F_WXCSUM | NETIF_F_IP_CSUM |
			       NETIF_F_IPV6_CSUM | NETIF_F_WXHASH |
			       NETIF_F_SG | NETIF_F_TSO | NETIF_F_TSO6 |
			       NETIF_F_GSO_UDP_W4);
	netdev->featuwes |= netdev->hw_featuwes;

	eww = otx2_mcam_fwow_init(pf);
	if (eww)
		goto eww_ptp_destwoy;

	eww = cn10k_mcs_init(pf);
	if (eww)
		goto eww_dew_mcam_entwies;

	if (pf->fwags & OTX2_FWAG_NTUPWE_SUPPOWT)
		netdev->hw_featuwes |= NETIF_F_NTUPWE;

	if (pf->fwags & OTX2_FWAG_UCAST_FWTW_SUPPOWT)
		netdev->pwiv_fwags |= IFF_UNICAST_FWT;

	/* Suppowt TSO on tag intewface */
	netdev->vwan_featuwes |= netdev->featuwes;
	netdev->hw_featuwes  |= NETIF_F_HW_VWAN_CTAG_TX |
				NETIF_F_HW_VWAN_STAG_TX;
	if (pf->fwags & OTX2_FWAG_WX_VWAN_SUPPOWT)
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_WX |
				       NETIF_F_HW_VWAN_STAG_WX;
	netdev->featuwes |= netdev->hw_featuwes;

	/* HW suppowts tc offwoad but mutuawwy excwusive with n-tupwe fiwtews */
	if (pf->fwags & OTX2_FWAG_TC_FWOWEW_SUPPOWT)
		netdev->hw_featuwes |= NETIF_F_HW_TC;

	netdev->hw_featuwes |= NETIF_F_WOOPBACK | NETIF_F_WXAWW;

	netif_set_tso_max_segs(netdev, OTX2_MAX_GSO_SEGS);
	netdev->watchdog_timeo = OTX2_TX_TIMEOUT;

	netdev->netdev_ops = &otx2_netdev_ops;
	netdev->xdp_featuwes = NETDEV_XDP_ACT_BASIC | NETDEV_XDP_ACT_WEDIWECT;

	netdev->min_mtu = OTX2_MIN_MTU;
	netdev->max_mtu = otx2_get_max_mtu(pf);

	eww = wegistew_netdev(netdev);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew netdevice\n");
		goto eww_mcs_fwee;
	}

	eww = otx2_wq_init(pf);
	if (eww)
		goto eww_unweg_netdev;

	otx2_set_ethtoow_ops(netdev);

	eww = otx2_init_tc(pf);
	if (eww)
		goto eww_mcam_fwow_dew;

	eww = otx2_wegistew_dw(pf);
	if (eww)
		goto eww_mcam_fwow_dew;

	/* Initiawize SW-IOV wesouwces */
	eww = otx2_swiov_vfcfg_init(pf);
	if (eww)
		goto eww_pf_swiov_init;

	/* Enabwe wink notifications */
	otx2_cgx_config_winkevents(pf, twue);

#ifdef CONFIG_DCB
	eww = otx2_dcbnw_set_ops(netdev);
	if (eww)
		goto eww_pf_swiov_init;
#endif

	otx2_qos_init(pf, qos_txqs);

	wetuwn 0;

eww_pf_swiov_init:
	otx2_shutdown_tc(pf);
eww_mcam_fwow_dew:
	otx2_mcam_fwow_dew(pf);
eww_unweg_netdev:
	unwegistew_netdev(netdev);
eww_mcs_fwee:
	cn10k_mcs_fwee(pf);
eww_dew_mcam_entwies:
	otx2_mcam_fwow_dew(pf);
eww_ptp_destwoy:
	otx2_ptp_destwoy(pf);
eww_detach_wswc:
	if (pf->hw.wmt_info)
		fwee_pewcpu(pf->hw.wmt_info);
	if (test_bit(CN10K_WMTST, &pf->hw.cap_fwag))
		qmem_fwee(pf->dev, pf->dync_wmt);
	otx2_detach_wesouwces(&pf->mbox);
eww_disabwe_mbox_intw:
	otx2_disabwe_mbox_intw(pf);
eww_mbox_destwoy:
	otx2_pfaf_mbox_destwoy(pf);
eww_fwee_iwq_vectows:
	pci_fwee_iwq_vectows(hw->pdev);
eww_fwee_netdev:
	pci_set_dwvdata(pdev, NUWW);
	fwee_netdev(netdev);
eww_wewease_wegions:
	pci_wewease_wegions(pdev);
	wetuwn eww;
}

static void otx2_vf_wink_event_task(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_vf_config *config;
	stwuct cgx_wink_info_msg *weq;
	stwuct mbox_msghdw *msghdw;
	stwuct otx2_nic *pf;
	int vf_idx;

	config = containew_of(wowk, stwuct otx2_vf_config,
			      wink_event_wowk.wowk);
	vf_idx = config - config->pf->vf_configs;
	pf = config->pf;

	msghdw = otx2_mbox_awwoc_msg_wsp(&pf->mbox_pfvf[0].mbox_up, vf_idx,
					 sizeof(*weq), sizeof(stwuct msg_wsp));
	if (!msghdw) {
		dev_eww(pf->dev, "Faiwed to cweate VF%d wink event\n", vf_idx);
		wetuwn;
	}

	weq = (stwuct cgx_wink_info_msg *)msghdw;
	weq->hdw.id = MBOX_MSG_CGX_WINK_EVENT;
	weq->hdw.sig = OTX2_MBOX_WEQ_SIG;
	memcpy(&weq->wink_info, &pf->winfo, sizeof(weq->wink_info));

	otx2_sync_mbox_up_msg(&pf->mbox_pfvf[0], vf_idx);
}

static int otx2_swiov_enabwe(stwuct pci_dev *pdev, int numvfs)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	int wet;

	/* Init PF <=> VF maiwbox stuff */
	wet = otx2_pfvf_mbox_init(pf, numvfs);
	if (wet)
		wetuwn wet;

	wet = otx2_wegistew_pfvf_mbox_intw(pf, numvfs);
	if (wet)
		goto fwee_mbox;

	wet = otx2_pf_fww_init(pf, numvfs);
	if (wet)
		goto fwee_intw;

	wet = otx2_wegistew_fww_me_intw(pf, numvfs);
	if (wet)
		goto fwee_fww;

	wet = pci_enabwe_swiov(pdev, numvfs);
	if (wet)
		goto fwee_fww_intw;

	wetuwn numvfs;
fwee_fww_intw:
	otx2_disabwe_fww_me_intw(pf);
fwee_fww:
	otx2_fww_wq_destwoy(pf);
fwee_intw:
	otx2_disabwe_pfvf_mbox_intw(pf, numvfs);
fwee_mbox:
	otx2_pfvf_mbox_destwoy(pf);
	wetuwn wet;
}

static int otx2_swiov_disabwe(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct otx2_nic *pf = netdev_pwiv(netdev);
	int numvfs = pci_num_vf(pdev);

	if (!numvfs)
		wetuwn 0;

	pci_disabwe_swiov(pdev);

	otx2_disabwe_fww_me_intw(pf);
	otx2_fww_wq_destwoy(pf);
	otx2_disabwe_pfvf_mbox_intw(pf, numvfs);
	otx2_pfvf_mbox_destwoy(pf);

	wetuwn 0;
}

static int otx2_swiov_configuwe(stwuct pci_dev *pdev, int numvfs)
{
	if (numvfs == 0)
		wetuwn otx2_swiov_disabwe(pdev);
	ewse
		wetuwn otx2_swiov_enabwe(pdev, numvfs);
}

static void otx2_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct otx2_nic *pf;

	if (!netdev)
		wetuwn;

	pf = netdev_pwiv(netdev);

	pf->fwags |= OTX2_FWAG_PF_SHUTDOWN;

	if (pf->fwags & OTX2_FWAG_TX_TSTAMP_ENABWED)
		otx2_config_hw_tx_tstamp(pf, fawse);
	if (pf->fwags & OTX2_FWAG_WX_TSTAMP_ENABWED)
		otx2_config_hw_wx_tstamp(pf, fawse);

	/* Disabwe 802.3x pause fwames */
	if (pf->fwags & OTX2_FWAG_WX_PAUSE_ENABWED ||
	    (pf->fwags & OTX2_FWAG_TX_PAUSE_ENABWED)) {
		pf->fwags &= ~OTX2_FWAG_WX_PAUSE_ENABWED;
		pf->fwags &= ~OTX2_FWAG_TX_PAUSE_ENABWED;
		otx2_config_pause_fwm(pf);
	}

#ifdef CONFIG_DCB
	/* Disabwe PFC config */
	if (pf->pfc_en) {
		pf->pfc_en = 0;
		otx2_config_pwiowity_fwow_ctww(pf);
	}
#endif
	cancew_wowk_sync(&pf->weset_task);
	/* Disabwe wink notifications */
	otx2_cgx_config_winkevents(pf, fawse);

	otx2_unwegistew_dw(pf);
	unwegistew_netdev(netdev);
	cn10k_mcs_fwee(pf);
	otx2_swiov_disabwe(pf->pdev);
	otx2_swiov_vfcfg_cweanup(pf);
	if (pf->otx2_wq)
		destwoy_wowkqueue(pf->otx2_wq);

	otx2_ptp_destwoy(pf);
	otx2_mcam_fwow_dew(pf);
	otx2_shutdown_tc(pf);
	otx2_shutdown_qos(pf);
	otx2_detach_wesouwces(&pf->mbox);
	if (pf->hw.wmt_info)
		fwee_pewcpu(pf->hw.wmt_info);
	if (test_bit(CN10K_WMTST, &pf->hw.cap_fwag))
		qmem_fwee(pf->dev, pf->dync_wmt);
	otx2_disabwe_mbox_intw(pf);
	otx2_pfaf_mbox_destwoy(pf);
	pci_fwee_iwq_vectows(pf->pdev);
	pci_set_dwvdata(pdev, NUWW);
	fwee_netdev(netdev);

	pci_wewease_wegions(pdev);
}

static stwuct pci_dwivew otx2_pf_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = otx2_pf_id_tabwe,
	.pwobe = otx2_pwobe,
	.shutdown = otx2_wemove,
	.wemove = otx2_wemove,
	.swiov_configuwe = otx2_swiov_configuwe
};

static int __init otx2_wvupf_init_moduwe(void)
{
	pw_info("%s: %s\n", DWV_NAME, DWV_STWING);

	wetuwn pci_wegistew_dwivew(&otx2_pf_dwivew);
}

static void __exit otx2_wvupf_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&otx2_pf_dwivew);
}

moduwe_init(otx2_wvupf_init_moduwe);
moduwe_exit(otx2_wvupf_cweanup_moduwe);
