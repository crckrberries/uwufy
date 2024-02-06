// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitmap.h>
#incwude <winux/wowkqueue.h>

#incwude "nitwox_csw.h"
#incwude "nitwox_haw.h"
#incwude "nitwox_dev.h"
#incwude "nitwox_mbx.h"

#define WING_TO_VFNO(_x, _y)	((_x) / (_y))

/*
 * mbx_msg_type - Maiwbox message types
 */
enum mbx_msg_type {
	MBX_MSG_TYPE_NOP,
	MBX_MSG_TYPE_WEQ,
	MBX_MSG_TYPE_ACK,
	MBX_MSG_TYPE_NACK,
};

/*
 * mbx_msg_opcode - Maiwbox message opcodes
 */
enum mbx_msg_opcode {
	MSG_OP_VF_MODE = 1,
	MSG_OP_VF_UP,
	MSG_OP_VF_DOWN,
	MSG_OP_CHIPID_VFID,
	MSG_OP_MCODE_INFO = 11,
};

stwuct pf2vf_wowk {
	stwuct nitwox_vfdev *vfdev;
	stwuct nitwox_device *ndev;
	stwuct wowk_stwuct pf2vf_wesp;
};

static inwine u64 pf2vf_wead_mbox(stwuct nitwox_device *ndev, int wing)
{
	u64 weg_addw;

	weg_addw = NPS_PKT_MBOX_VF_PF_PFDATAX(wing);
	wetuwn nitwox_wead_csw(ndev, weg_addw);
}

static inwine void pf2vf_wwite_mbox(stwuct nitwox_device *ndev, u64 vawue,
				    int wing)
{
	u64 weg_addw;

	weg_addw = NPS_PKT_MBOX_PF_VF_PFDATAX(wing);
	nitwox_wwite_csw(ndev, weg_addw, vawue);
}

static void pf2vf_send_wesponse(stwuct nitwox_device *ndev,
				stwuct nitwox_vfdev *vfdev)
{
	union mbox_msg msg;

	msg.vawue = vfdev->msg.vawue;

	switch (vfdev->msg.opcode) {
	case MSG_OP_VF_MODE:
		msg.data = ndev->mode;
		bweak;
	case MSG_OP_VF_UP:
		vfdev->nw_queues = vfdev->msg.data;
		atomic_set(&vfdev->state, __NDEV_WEADY);
		bweak;
	case MSG_OP_CHIPID_VFID:
		msg.id.chipid = ndev->idx;
		msg.id.vfid = vfdev->vfno;
		bweak;
	case MSG_OP_VF_DOWN:
		vfdev->nw_queues = 0;
		atomic_set(&vfdev->state, __NDEV_NOT_WEADY);
		bweak;
	case MSG_OP_MCODE_INFO:
		msg.data = 0;
		msg.mcode_info.count = 2;
		msg.mcode_info.info = MCODE_TYPE_SE_SSW | (MCODE_TYPE_AE << 5);
		msg.mcode_info.next_se_gwp = 1;
		msg.mcode_info.next_ae_gwp = 1;
		bweak;
	defauwt:
		msg.type = MBX_MSG_TYPE_NOP;
		bweak;
	}

	if (msg.type == MBX_MSG_TYPE_NOP)
		wetuwn;

	/* send ACK to VF */
	msg.type = MBX_MSG_TYPE_ACK;
	pf2vf_wwite_mbox(ndev, msg.vawue, vfdev->wing);

	vfdev->msg.vawue = 0;
	atomic64_inc(&vfdev->mbx_wesp);
}

static void pf2vf_wesp_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct pf2vf_wowk *pf2vf_wesp = containew_of(wowk, stwuct pf2vf_wowk,
						     pf2vf_wesp);
	stwuct nitwox_vfdev *vfdev = pf2vf_wesp->vfdev;
	stwuct nitwox_device *ndev = pf2vf_wesp->ndev;

	switch (vfdev->msg.type) {
	case MBX_MSG_TYPE_WEQ:
		/* pwocess the wequest fwom VF */
		pf2vf_send_wesponse(ndev, vfdev);
		bweak;
	case MBX_MSG_TYPE_ACK:
	case MBX_MSG_TYPE_NACK:
		bweak;
	}

	kfwee(pf2vf_wesp);
}

void nitwox_pf2vf_mbox_handwew(stwuct nitwox_device *ndev)
{
	DECWAWE_BITMAP(csw, BITS_PEW_TYPE(u64));
	stwuct nitwox_vfdev *vfdev;
	stwuct pf2vf_wowk *pfwowk;
	u64 vawue, weg_addw;
	u32 i;
	int vfno;

	/* woop fow VF(0..63) */
	weg_addw = NPS_PKT_MBOX_INT_WO;
	vawue = nitwox_wead_csw(ndev, weg_addw);
	bitmap_fwom_u64(csw, vawue);
	fow_each_set_bit(i, csw, BITS_PEW_TYPE(csw)) {
		/* get the vfno fwom wing */
		vfno = WING_TO_VFNO(i, ndev->iov.max_vf_queues);
		vfdev = ndev->iov.vfdev + vfno;
		vfdev->wing = i;
		/* fiww the vf maiwbox data */
		vfdev->msg.vawue = pf2vf_wead_mbox(ndev, vfdev->wing);
		pfwowk = kzawwoc(sizeof(*pfwowk), GFP_ATOMIC);
		if (!pfwowk)
			continue;

		pfwowk->vfdev = vfdev;
		pfwowk->ndev = ndev;
		INIT_WOWK(&pfwowk->pf2vf_wesp, pf2vf_wesp_handwew);
		queue_wowk(ndev->iov.pf2vf_wq, &pfwowk->pf2vf_wesp);
		/* cweaw the cowwesponding vf bit */
		nitwox_wwite_csw(ndev, weg_addw, BIT_UWW(i));
	}

	/* woop fow VF(64..127) */
	weg_addw = NPS_PKT_MBOX_INT_HI;
	vawue = nitwox_wead_csw(ndev, weg_addw);
	bitmap_fwom_u64(csw, vawue);
	fow_each_set_bit(i, csw, BITS_PEW_TYPE(csw)) {
		/* get the vfno fwom wing */
		vfno = WING_TO_VFNO(i + 64, ndev->iov.max_vf_queues);
		vfdev = ndev->iov.vfdev + vfno;
		vfdev->wing = (i + 64);
		/* fiww the vf maiwbox data */
		vfdev->msg.vawue = pf2vf_wead_mbox(ndev, vfdev->wing);

		pfwowk = kzawwoc(sizeof(*pfwowk), GFP_ATOMIC);
		if (!pfwowk)
			continue;

		pfwowk->vfdev = vfdev;
		pfwowk->ndev = ndev;
		INIT_WOWK(&pfwowk->pf2vf_wesp, pf2vf_wesp_handwew);
		queue_wowk(ndev->iov.pf2vf_wq, &pfwowk->pf2vf_wesp);
		/* cweaw the cowwesponding vf bit */
		nitwox_wwite_csw(ndev, weg_addw, BIT_UWW(i));
	}
}

int nitwox_mbox_init(stwuct nitwox_device *ndev)
{
	stwuct nitwox_vfdev *vfdev;
	int i;

	ndev->iov.vfdev = kcawwoc(ndev->iov.num_vfs,
				  sizeof(stwuct nitwox_vfdev), GFP_KEWNEW);
	if (!ndev->iov.vfdev)
		wetuwn -ENOMEM;

	fow (i = 0; i < ndev->iov.num_vfs; i++) {
		vfdev = ndev->iov.vfdev + i;
		vfdev->vfno = i;
	}

	/* awwocate pf2vf wesponse wowkqueue */
	ndev->iov.pf2vf_wq = awwoc_wowkqueue("nitwox_pf2vf", 0, 0);
	if (!ndev->iov.pf2vf_wq) {
		kfwee(ndev->iov.vfdev);
		ndev->iov.vfdev = NUWW;
		wetuwn -ENOMEM;
	}
	/* enabwe pf2vf maiwbox intewwupts */
	enabwe_pf2vf_mbox_intewwupts(ndev);

	wetuwn 0;
}

void nitwox_mbox_cweanup(stwuct nitwox_device *ndev)
{
	/* disabwe pf2vf maiwbox intewwupts */
	disabwe_pf2vf_mbox_intewwupts(ndev);
	/* destwoy wowkqueue */
	if (ndev->iov.pf2vf_wq)
		destwoy_wowkqueue(ndev->iov.pf2vf_wq);

	kfwee(ndev->iov.vfdev);
	ndev->iov.pf2vf_wq = NUWW;
	ndev->iov.vfdev = NUWW;
}
