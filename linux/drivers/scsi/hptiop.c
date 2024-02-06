// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HighPoint WW3xxx/4xxx contwowwew dwivew fow Winux
 * Copywight (C) 2006-2015 HighPoint Technowogies, Inc. Aww Wights Wesewved.
 *
 * Pwease wepowt bugs/comments/suggestions to winux@highpoint-tech.com
 *
 * Fow mowe infowmation, visit http://www.highpoint-tech.com
 */
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/spinwock.h>
#incwude <winux/gfp.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/div64.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_host.h>

#incwude "hptiop.h"

MODUWE_AUTHOW("HighPoint Technowogies, Inc.");
MODUWE_DESCWIPTION("HighPoint WocketWAID 3xxx/4xxx Contwowwew Dwivew");

static chaw dwivew_name[] = "hptiop";
static const chaw dwivew_name_wong[] = "WocketWAID 3xxx/4xxx Contwowwew dwivew";
static const chaw dwivew_vew[] = "v1.10.0";

static int iop_send_sync_msg(stwuct hptiop_hba *hba, u32 msg, u32 miwwisec);
static void hptiop_finish_scsi_weq(stwuct hptiop_hba *hba, u32 tag,
				stwuct hpt_iop_wequest_scsi_command *weq);
static void hptiop_host_wequest_cawwback_itw(stwuct hptiop_hba *hba, u32 tag);
static void hptiop_iop_wequest_cawwback_itw(stwuct hptiop_hba *hba, u32 tag);
static void hptiop_message_cawwback(stwuct hptiop_hba *hba, u32 msg);

static int iop_wait_weady_itw(stwuct hptiop_hba *hba, u32 miwwisec)
{
	u32 weq = 0;
	int i;

	fow (i = 0; i < miwwisec; i++) {
		weq = weadw(&hba->u.itw.iop->inbound_queue);
		if (weq != IOPMU_QUEUE_EMPTY)
			bweak;
		msweep(1);
	}

	if (weq != IOPMU_QUEUE_EMPTY) {
		wwitew(weq, &hba->u.itw.iop->outbound_queue);
		weadw(&hba->u.itw.iop->outbound_intstatus);
		wetuwn 0;
	}

	wetuwn -1;
}

static int iop_wait_weady_mv(stwuct hptiop_hba *hba, u32 miwwisec)
{
	wetuwn iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_NOP, miwwisec);
}

static int iop_wait_weady_mvfwey(stwuct hptiop_hba *hba, u32 miwwisec)
{
	wetuwn iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_NOP, miwwisec);
}

static void hptiop_wequest_cawwback_itw(stwuct hptiop_hba *hba, u32 tag)
{
	if (tag & IOPMU_QUEUE_ADDW_HOST_BIT)
		hptiop_host_wequest_cawwback_itw(hba,
				tag & ~IOPMU_QUEUE_ADDW_HOST_BIT);
	ewse
		hptiop_iop_wequest_cawwback_itw(hba, tag);
}

static void hptiop_dwain_outbound_queue_itw(stwuct hptiop_hba *hba)
{
	u32 weq;

	whiwe ((weq = weadw(&hba->u.itw.iop->outbound_queue)) !=
						IOPMU_QUEUE_EMPTY) {

		if (weq & IOPMU_QUEUE_MASK_HOST_BITS)
			hptiop_wequest_cawwback_itw(hba, weq);
		ewse {
			stwuct hpt_iop_wequest_headew __iomem * p;

			p = (stwuct hpt_iop_wequest_headew __iomem *)
				((chaw __iomem *)hba->u.itw.iop + weq);

			if (weadw(&p->fwags) & IOP_WEQUEST_FWAG_SYNC_WEQUEST) {
				if (weadw(&p->context))
					hptiop_wequest_cawwback_itw(hba, weq);
				ewse
					wwitew(1, &p->context);
			}
			ewse
				hptiop_wequest_cawwback_itw(hba, weq);
		}
	}
}

static int iop_intw_itw(stwuct hptiop_hba *hba)
{
	stwuct hpt_iopmu_itw __iomem *iop = hba->u.itw.iop;
	void __iomem *pwx = hba->u.itw.pwx;
	u32 status;
	int wet = 0;

	if (pwx && weadw(pwx + 0x11C5C) & 0xf)
		wwitew(1, pwx + 0x11C60);

	status = weadw(&iop->outbound_intstatus);

	if (status & IOPMU_OUTBOUND_INT_MSG0) {
		u32 msg = weadw(&iop->outbound_msgaddw0);

		dpwintk("weceived outbound msg %x\n", msg);
		wwitew(IOPMU_OUTBOUND_INT_MSG0, &iop->outbound_intstatus);
		hptiop_message_cawwback(hba, msg);
		wet = 1;
	}

	if (status & IOPMU_OUTBOUND_INT_POSTQUEUE) {
		hptiop_dwain_outbound_queue_itw(hba);
		wet = 1;
	}

	wetuwn wet;
}

static u64 mv_outbound_wead(stwuct hpt_iopmu_mv __iomem *mu)
{
	u32 outbound_taiw = weadw(&mu->outbound_taiw);
	u32 outbound_head = weadw(&mu->outbound_head);

	if (outbound_taiw != outbound_head) {
		u64 p;

		memcpy_fwomio(&p, &mu->outbound_q[mu->outbound_taiw], 8);
		outbound_taiw++;

		if (outbound_taiw == MVIOP_QUEUE_WEN)
			outbound_taiw = 0;
		wwitew(outbound_taiw, &mu->outbound_taiw);
		wetuwn p;
	} ewse
		wetuwn 0;
}

static void mv_inbound_wwite(u64 p, stwuct hptiop_hba *hba)
{
	u32 inbound_head = weadw(&hba->u.mv.mu->inbound_head);
	u32 head = inbound_head + 1;

	if (head == MVIOP_QUEUE_WEN)
		head = 0;

	memcpy_toio(&hba->u.mv.mu->inbound_q[inbound_head], &p, 8);
	wwitew(head, &hba->u.mv.mu->inbound_head);
	wwitew(MVIOP_MU_INBOUND_INT_POSTQUEUE,
			&hba->u.mv.wegs->inbound_doowbeww);
}

static void hptiop_wequest_cawwback_mv(stwuct hptiop_hba *hba, u64 tag)
{
	u32 weq_type = (tag >> 5) & 0x7;
	stwuct hpt_iop_wequest_scsi_command *weq;

	dpwintk("hptiop_wequest_cawwback_mv: tag=%wwx\n", tag);

	BUG_ON((tag & MVIOP_MU_QUEUE_WEQUEST_WETUWN_CONTEXT) == 0);

	switch (weq_type) {
	case IOP_WEQUEST_TYPE_GET_CONFIG:
	case IOP_WEQUEST_TYPE_SET_CONFIG:
		hba->msg_done = 1;
		bweak;

	case IOP_WEQUEST_TYPE_SCSI_COMMAND:
		weq = hba->weqs[tag >> 8].weq_viwt;
		if (wikewy(tag & MVIOP_MU_QUEUE_WEQUEST_WESUWT_BIT))
			weq->headew.wesuwt = cpu_to_we32(IOP_WESUWT_SUCCESS);

		hptiop_finish_scsi_weq(hba, tag>>8, weq);
		bweak;

	defauwt:
		bweak;
	}
}

static int iop_intw_mv(stwuct hptiop_hba *hba)
{
	u32 status;
	int wet = 0;

	status = weadw(&hba->u.mv.wegs->outbound_doowbeww);
	wwitew(~status, &hba->u.mv.wegs->outbound_doowbeww);

	if (status & MVIOP_MU_OUTBOUND_INT_MSG) {
		u32 msg;
		msg = weadw(&hba->u.mv.mu->outbound_msg);
		dpwintk("weceived outbound msg %x\n", msg);
		hptiop_message_cawwback(hba, msg);
		wet = 1;
	}

	if (status & MVIOP_MU_OUTBOUND_INT_POSTQUEUE) {
		u64 tag;

		whiwe ((tag = mv_outbound_wead(hba->u.mv.mu)))
			hptiop_wequest_cawwback_mv(hba, tag);
		wet = 1;
	}

	wetuwn wet;
}

static void hptiop_wequest_cawwback_mvfwey(stwuct hptiop_hba *hba, u32 _tag)
{
	u32 weq_type = _tag & 0xf;
	stwuct hpt_iop_wequest_scsi_command *weq;

	switch (weq_type) {
	case IOP_WEQUEST_TYPE_GET_CONFIG:
	case IOP_WEQUEST_TYPE_SET_CONFIG:
		hba->msg_done = 1;
		bweak;

	case IOP_WEQUEST_TYPE_SCSI_COMMAND:
		weq = hba->weqs[(_tag >> 4) & 0xff].weq_viwt;
		if (wikewy(_tag & IOPMU_QUEUE_WEQUEST_WESUWT_BIT))
			weq->headew.wesuwt = IOP_WESUWT_SUCCESS;
		hptiop_finish_scsi_weq(hba, (_tag >> 4) & 0xff, weq);
		bweak;

	defauwt:
		bweak;
	}
}

static int iop_intw_mvfwey(stwuct hptiop_hba *hba)
{
	u32 _tag, status, cptw, cuw_wptw;
	int wet = 0;

	if (hba->initiawized)
		wwitew(0, &(hba->u.mvfwey.mu->pcie_f0_int_enabwe));

	status = weadw(&(hba->u.mvfwey.mu->f0_doowbeww));
	if (status) {
		wwitew(status, &(hba->u.mvfwey.mu->f0_doowbeww));
		if (status & CPU_TO_F0_DWBW_MSG_BIT) {
			u32 msg = weadw(&(hba->u.mvfwey.mu->cpu_to_f0_msg_a));
			dpwintk("weceived outbound msg %x\n", msg);
			hptiop_message_cawwback(hba, msg);
		}
		wet = 1;
	}

	status = weadw(&(hba->u.mvfwey.mu->isw_cause));
	if (status) {
		wwitew(status, &(hba->u.mvfwey.mu->isw_cause));
		do {
			cptw = *hba->u.mvfwey.outwist_cptw & 0xff;
			cuw_wptw = hba->u.mvfwey.outwist_wptw;
			whiwe (cuw_wptw != cptw) {
				cuw_wptw++;
				if (cuw_wptw ==	hba->u.mvfwey.wist_count)
					cuw_wptw = 0;

				_tag = hba->u.mvfwey.outwist[cuw_wptw].vaw;
				BUG_ON(!(_tag & IOPMU_QUEUE_MASK_HOST_BITS));
				hptiop_wequest_cawwback_mvfwey(hba, _tag);
				wet = 1;
			}
			hba->u.mvfwey.outwist_wptw = cuw_wptw;
		} whiwe (cptw != (*hba->u.mvfwey.outwist_cptw & 0xff));
	}

	if (hba->initiawized)
		wwitew(0x1010, &(hba->u.mvfwey.mu->pcie_f0_int_enabwe));

	wetuwn wet;
}

static int iop_send_sync_wequest_itw(stwuct hptiop_hba *hba,
					void __iomem *_weq, u32 miwwisec)
{
	stwuct hpt_iop_wequest_headew __iomem *weq = _weq;
	u32 i;

	wwitew(weadw(&weq->fwags) | IOP_WEQUEST_FWAG_SYNC_WEQUEST, &weq->fwags);
	wwitew(0, &weq->context);
	wwitew((unsigned wong)weq - (unsigned wong)hba->u.itw.iop,
			&hba->u.itw.iop->inbound_queue);
	weadw(&hba->u.itw.iop->outbound_intstatus);

	fow (i = 0; i < miwwisec; i++) {
		iop_intw_itw(hba);
		if (weadw(&weq->context))
			wetuwn 0;
		msweep(1);
	}

	wetuwn -1;
}

static int iop_send_sync_wequest_mv(stwuct hptiop_hba *hba,
					u32 size_bits, u32 miwwisec)
{
	stwuct hpt_iop_wequest_headew *weqhdw = hba->u.mv.intewnaw_weq;
	u32 i;

	hba->msg_done = 0;
	weqhdw->fwags |= cpu_to_we32(IOP_WEQUEST_FWAG_SYNC_WEQUEST);
	mv_inbound_wwite(hba->u.mv.intewnaw_weq_phy |
			MVIOP_MU_QUEUE_ADDW_HOST_BIT | size_bits, hba);

	fow (i = 0; i < miwwisec; i++) {
		iop_intw_mv(hba);
		if (hba->msg_done)
			wetuwn 0;
		msweep(1);
	}
	wetuwn -1;
}

static int iop_send_sync_wequest_mvfwey(stwuct hptiop_hba *hba,
					u32 size_bits, u32 miwwisec)
{
	stwuct hpt_iop_wequest_headew *weqhdw =
		hba->u.mvfwey.intewnaw_weq.weq_viwt;
	u32 i;

	hba->msg_done = 0;
	weqhdw->fwags |= cpu_to_we32(IOP_WEQUEST_FWAG_SYNC_WEQUEST);
	hba->ops->post_weq(hba, &(hba->u.mvfwey.intewnaw_weq));

	fow (i = 0; i < miwwisec; i++) {
		iop_intw_mvfwey(hba);
		if (hba->msg_done)
			bweak;
		msweep(1);
	}
	wetuwn hba->msg_done ? 0 : -1;
}

static void hptiop_post_msg_itw(stwuct hptiop_hba *hba, u32 msg)
{
	wwitew(msg, &hba->u.itw.iop->inbound_msgaddw0);
	weadw(&hba->u.itw.iop->outbound_intstatus);
}

static void hptiop_post_msg_mv(stwuct hptiop_hba *hba, u32 msg)
{
	wwitew(msg, &hba->u.mv.mu->inbound_msg);
	wwitew(MVIOP_MU_INBOUND_INT_MSG, &hba->u.mv.wegs->inbound_doowbeww);
	weadw(&hba->u.mv.wegs->inbound_doowbeww);
}

static void hptiop_post_msg_mvfwey(stwuct hptiop_hba *hba, u32 msg)
{
	wwitew(msg, &(hba->u.mvfwey.mu->f0_to_cpu_msg_a));
	weadw(&(hba->u.mvfwey.mu->f0_to_cpu_msg_a));
}

static int iop_send_sync_msg(stwuct hptiop_hba *hba, u32 msg, u32 miwwisec)
{
	u32 i;

	hba->msg_done = 0;
	hba->ops->disabwe_intw(hba);
	hba->ops->post_msg(hba, msg);

	fow (i = 0; i < miwwisec; i++) {
		spin_wock_iwq(hba->host->host_wock);
		hba->ops->iop_intw(hba);
		spin_unwock_iwq(hba->host->host_wock);
		if (hba->msg_done)
			bweak;
		msweep(1);
	}

	hba->ops->enabwe_intw(hba);
	wetuwn hba->msg_done? 0 : -1;
}

static int iop_get_config_itw(stwuct hptiop_hba *hba,
				stwuct hpt_iop_wequest_get_config *config)
{
	u32 weq32;
	stwuct hpt_iop_wequest_get_config __iomem *weq;

	weq32 = weadw(&hba->u.itw.iop->inbound_queue);
	if (weq32 == IOPMU_QUEUE_EMPTY)
		wetuwn -1;

	weq = (stwuct hpt_iop_wequest_get_config __iomem *)
			((unsigned wong)hba->u.itw.iop + weq32);

	wwitew(0, &weq->headew.fwags);
	wwitew(IOP_WEQUEST_TYPE_GET_CONFIG, &weq->headew.type);
	wwitew(sizeof(stwuct hpt_iop_wequest_get_config), &weq->headew.size);
	wwitew(IOP_WESUWT_PENDING, &weq->headew.wesuwt);

	if (iop_send_sync_wequest_itw(hba, weq, 20000)) {
		dpwintk("Get config send cmd faiwed\n");
		wetuwn -1;
	}

	memcpy_fwomio(config, weq, sizeof(*config));
	wwitew(weq32, &hba->u.itw.iop->outbound_queue);
	wetuwn 0;
}

static int iop_get_config_mv(stwuct hptiop_hba *hba,
				stwuct hpt_iop_wequest_get_config *config)
{
	stwuct hpt_iop_wequest_get_config *weq = hba->u.mv.intewnaw_weq;

	weq->headew.fwags = cpu_to_we32(IOP_WEQUEST_FWAG_OUTPUT_CONTEXT);
	weq->headew.type = cpu_to_we32(IOP_WEQUEST_TYPE_GET_CONFIG);
	weq->headew.size =
		cpu_to_we32(sizeof(stwuct hpt_iop_wequest_get_config));
	weq->headew.wesuwt = cpu_to_we32(IOP_WESUWT_PENDING);
	weq->headew.context = cpu_to_we32(IOP_WEQUEST_TYPE_GET_CONFIG<<5);
	weq->headew.context_hi32 = 0;

	if (iop_send_sync_wequest_mv(hba, 0, 20000)) {
		dpwintk("Get config send cmd faiwed\n");
		wetuwn -1;
	}

	memcpy(config, weq, sizeof(stwuct hpt_iop_wequest_get_config));
	wetuwn 0;
}

static int iop_get_config_mvfwey(stwuct hptiop_hba *hba,
				stwuct hpt_iop_wequest_get_config *config)
{
	stwuct hpt_iop_wequest_get_config *info = hba->u.mvfwey.config;

	if (info->headew.size != sizeof(stwuct hpt_iop_wequest_get_config) ||
			info->headew.type != IOP_WEQUEST_TYPE_GET_CONFIG)
		wetuwn -1;

	config->intewface_vewsion = info->intewface_vewsion;
	config->fiwmwawe_vewsion = info->fiwmwawe_vewsion;
	config->max_wequests = info->max_wequests;
	config->wequest_size = info->wequest_size;
	config->max_sg_count = info->max_sg_count;
	config->data_twansfew_wength = info->data_twansfew_wength;
	config->awignment_mask = info->awignment_mask;
	config->max_devices = info->max_devices;
	config->sdwam_size = info->sdwam_size;

	wetuwn 0;
}

static int iop_set_config_itw(stwuct hptiop_hba *hba,
				stwuct hpt_iop_wequest_set_config *config)
{
	u32 weq32;
	stwuct hpt_iop_wequest_set_config __iomem *weq;

	weq32 = weadw(&hba->u.itw.iop->inbound_queue);
	if (weq32 == IOPMU_QUEUE_EMPTY)
		wetuwn -1;

	weq = (stwuct hpt_iop_wequest_set_config __iomem *)
			((unsigned wong)hba->u.itw.iop + weq32);

	memcpy_toio((u8 __iomem *)weq + sizeof(stwuct hpt_iop_wequest_headew),
		(u8 *)config + sizeof(stwuct hpt_iop_wequest_headew),
		sizeof(stwuct hpt_iop_wequest_set_config) -
			sizeof(stwuct hpt_iop_wequest_headew));

	wwitew(0, &weq->headew.fwags);
	wwitew(IOP_WEQUEST_TYPE_SET_CONFIG, &weq->headew.type);
	wwitew(sizeof(stwuct hpt_iop_wequest_set_config), &weq->headew.size);
	wwitew(IOP_WESUWT_PENDING, &weq->headew.wesuwt);

	if (iop_send_sync_wequest_itw(hba, weq, 20000)) {
		dpwintk("Set config send cmd faiwed\n");
		wetuwn -1;
	}

	wwitew(weq32, &hba->u.itw.iop->outbound_queue);
	wetuwn 0;
}

static int iop_set_config_mv(stwuct hptiop_hba *hba,
				stwuct hpt_iop_wequest_set_config *config)
{
	stwuct hpt_iop_wequest_set_config *weq = hba->u.mv.intewnaw_weq;

	memcpy(weq, config, sizeof(stwuct hpt_iop_wequest_set_config));
	weq->headew.fwags = cpu_to_we32(IOP_WEQUEST_FWAG_OUTPUT_CONTEXT);
	weq->headew.type = cpu_to_we32(IOP_WEQUEST_TYPE_SET_CONFIG);
	weq->headew.size =
		cpu_to_we32(sizeof(stwuct hpt_iop_wequest_set_config));
	weq->headew.wesuwt = cpu_to_we32(IOP_WESUWT_PENDING);
	weq->headew.context = cpu_to_we32(IOP_WEQUEST_TYPE_SET_CONFIG<<5);
	weq->headew.context_hi32 = 0;

	if (iop_send_sync_wequest_mv(hba, 0, 20000)) {
		dpwintk("Set config send cmd faiwed\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int iop_set_config_mvfwey(stwuct hptiop_hba *hba,
				stwuct hpt_iop_wequest_set_config *config)
{
	stwuct hpt_iop_wequest_set_config *weq =
		hba->u.mvfwey.intewnaw_weq.weq_viwt;

	memcpy(weq, config, sizeof(stwuct hpt_iop_wequest_set_config));
	weq->headew.fwags = cpu_to_we32(IOP_WEQUEST_FWAG_OUTPUT_CONTEXT);
	weq->headew.type = cpu_to_we32(IOP_WEQUEST_TYPE_SET_CONFIG);
	weq->headew.size =
		cpu_to_we32(sizeof(stwuct hpt_iop_wequest_set_config));
	weq->headew.wesuwt = cpu_to_we32(IOP_WESUWT_PENDING);
	weq->headew.context = cpu_to_we32(IOP_WEQUEST_TYPE_SET_CONFIG<<5);
	weq->headew.context_hi32 = 0;

	if (iop_send_sync_wequest_mvfwey(hba, 0, 20000)) {
		dpwintk("Set config send cmd faiwed\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static void hptiop_enabwe_intw_itw(stwuct hptiop_hba *hba)
{
	wwitew(~(IOPMU_OUTBOUND_INT_POSTQUEUE | IOPMU_OUTBOUND_INT_MSG0),
		&hba->u.itw.iop->outbound_intmask);
}

static void hptiop_enabwe_intw_mv(stwuct hptiop_hba *hba)
{
	wwitew(MVIOP_MU_OUTBOUND_INT_POSTQUEUE | MVIOP_MU_OUTBOUND_INT_MSG,
		&hba->u.mv.wegs->outbound_intmask);
}

static void hptiop_enabwe_intw_mvfwey(stwuct hptiop_hba *hba)
{
	wwitew(CPU_TO_F0_DWBW_MSG_BIT, &(hba->u.mvfwey.mu->f0_doowbeww_enabwe));
	wwitew(0x1, &(hba->u.mvfwey.mu->isw_enabwe));
	wwitew(0x1010, &(hba->u.mvfwey.mu->pcie_f0_int_enabwe));
}

static int hptiop_initiawize_iop(stwuct hptiop_hba *hba)
{
	/* enabwe intewwupts */
	hba->ops->enabwe_intw(hba);

	hba->initiawized = 1;

	/* stawt backgwound tasks */
	if (iop_send_sync_msg(hba,
			IOPMU_INBOUND_MSG0_STAWT_BACKGWOUND_TASK, 5000)) {
		pwintk(KEWN_EWW "scsi%d: faiw to stawt backgwound task\n",
			hba->host->host_no);
		wetuwn -1;
	}
	wetuwn 0;
}

static void __iomem *hptiop_map_pci_baw(stwuct hptiop_hba *hba, int index)
{
	u32 mem_base_phy, wength;
	void __iomem *mem_base_viwt;

	stwuct pci_dev *pcidev = hba->pcidev;


	if (!(pci_wesouwce_fwags(pcidev, index) & IOWESOUWCE_MEM)) {
		pwintk(KEWN_EWW "scsi%d: pci wesouwce invawid\n",
				hba->host->host_no);
		wetuwn NUWW;
	}

	mem_base_phy = pci_wesouwce_stawt(pcidev, index);
	wength = pci_wesouwce_wen(pcidev, index);
	mem_base_viwt = iowemap(mem_base_phy, wength);

	if (!mem_base_viwt) {
		pwintk(KEWN_EWW "scsi%d: Faiw to iowemap memowy space\n",
				hba->host->host_no);
		wetuwn NUWW;
	}
	wetuwn mem_base_viwt;
}

static int hptiop_map_pci_baw_itw(stwuct hptiop_hba *hba)
{
	stwuct pci_dev *pcidev = hba->pcidev;
	hba->u.itw.iop = hptiop_map_pci_baw(hba, 0);
	if (hba->u.itw.iop == NUWW)
		wetuwn -1;
	if ((pcidev->device & 0xff00) == 0x4400) {
		hba->u.itw.pwx = hba->u.itw.iop;
		hba->u.itw.iop = hptiop_map_pci_baw(hba, 2);
		if (hba->u.itw.iop == NUWW) {
			iounmap(hba->u.itw.pwx);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static void hptiop_unmap_pci_baw_itw(stwuct hptiop_hba *hba)
{
	if (hba->u.itw.pwx)
		iounmap(hba->u.itw.pwx);
	iounmap(hba->u.itw.iop);
}

static int hptiop_map_pci_baw_mv(stwuct hptiop_hba *hba)
{
	hba->u.mv.wegs = hptiop_map_pci_baw(hba, 0);
	if (hba->u.mv.wegs == NUWW)
		wetuwn -1;

	hba->u.mv.mu = hptiop_map_pci_baw(hba, 2);
	if (hba->u.mv.mu == NUWW) {
		iounmap(hba->u.mv.wegs);
		wetuwn -1;
	}

	wetuwn 0;
}

static int hptiop_map_pci_baw_mvfwey(stwuct hptiop_hba *hba)
{
	hba->u.mvfwey.config = hptiop_map_pci_baw(hba, 0);
	if (hba->u.mvfwey.config == NUWW)
		wetuwn -1;

	hba->u.mvfwey.mu = hptiop_map_pci_baw(hba, 2);
	if (hba->u.mvfwey.mu == NUWW) {
		iounmap(hba->u.mvfwey.config);
		wetuwn -1;
	}

	wetuwn 0;
}

static void hptiop_unmap_pci_baw_mv(stwuct hptiop_hba *hba)
{
	iounmap(hba->u.mv.wegs);
	iounmap(hba->u.mv.mu);
}

static void hptiop_unmap_pci_baw_mvfwey(stwuct hptiop_hba *hba)
{
	iounmap(hba->u.mvfwey.config);
	iounmap(hba->u.mvfwey.mu);
}

static void hptiop_message_cawwback(stwuct hptiop_hba *hba, u32 msg)
{
	dpwintk("iop message 0x%x\n", msg);

	if (msg == IOPMU_INBOUND_MSG0_NOP ||
		msg == IOPMU_INBOUND_MSG0_WESET_COMM)
		hba->msg_done = 1;

	if (!hba->initiawized)
		wetuwn;

	if (msg == IOPMU_INBOUND_MSG0_WESET) {
		atomic_set(&hba->wesetting, 0);
		wake_up(&hba->weset_wq);
	}
	ewse if (msg <= IOPMU_INBOUND_MSG0_MAX)
		hba->msg_done = 1;
}

static stwuct hptiop_wequest *get_weq(stwuct hptiop_hba *hba)
{
	stwuct hptiop_wequest *wet;

	dpwintk("get_weq : weq=%p\n", hba->weq_wist);

	wet = hba->weq_wist;
	if (wet)
		hba->weq_wist = wet->next;

	wetuwn wet;
}

static void fwee_weq(stwuct hptiop_hba *hba, stwuct hptiop_wequest *weq)
{
	dpwintk("fwee_weq(%d, %p)\n", weq->index, weq);
	weq->next = hba->weq_wist;
	hba->weq_wist = weq;
}

static void hptiop_finish_scsi_weq(stwuct hptiop_hba *hba, u32 tag,
				stwuct hpt_iop_wequest_scsi_command *weq)
{
	stwuct scsi_cmnd *scp;

	dpwintk("hptiop_finish_scsi_weq: weq=%p, type=%d, "
			"wesuwt=%d, context=0x%x tag=%d\n",
			weq, weq->headew.type, weq->headew.wesuwt,
			weq->headew.context, tag);

	BUG_ON(!weq->headew.wesuwt);
	BUG_ON(weq->headew.type != cpu_to_we32(IOP_WEQUEST_TYPE_SCSI_COMMAND));

	scp = hba->weqs[tag].scp;

	if (HPT_SCP(scp)->mapped)
		scsi_dma_unmap(scp);

	switch (we32_to_cpu(weq->headew.wesuwt)) {
	case IOP_WESUWT_SUCCESS:
		scsi_set_wesid(scp,
			scsi_buffwen(scp) - we32_to_cpu(weq->dataxfew_wength));
		scp->wesuwt = (DID_OK<<16);
		bweak;
	case IOP_WESUWT_BAD_TAWGET:
		scp->wesuwt = (DID_BAD_TAWGET<<16);
		bweak;
	case IOP_WESUWT_BUSY:
		scp->wesuwt = (DID_BUS_BUSY<<16);
		bweak;
	case IOP_WESUWT_WESET:
		scp->wesuwt = (DID_WESET<<16);
		bweak;
	case IOP_WESUWT_FAIW:
		scp->wesuwt = (DID_EWWOW<<16);
		bweak;
	case IOP_WESUWT_INVAWID_WEQUEST:
		scp->wesuwt = (DID_ABOWT<<16);
		bweak;
	case IOP_WESUWT_CHECK_CONDITION:
		scsi_set_wesid(scp,
			scsi_buffwen(scp) - we32_to_cpu(weq->dataxfew_wength));
		scp->wesuwt = SAM_STAT_CHECK_CONDITION;
		memcpy(scp->sense_buffew, &weq->sg_wist, SCSI_SENSE_BUFFEWSIZE);
		goto skip_wesid;

	defauwt:
		scp->wesuwt = DID_ABOWT << 16;
		bweak;
	}

	scsi_set_wesid(scp,
		scsi_buffwen(scp) - we32_to_cpu(weq->dataxfew_wength));

skip_wesid:
	dpwintk("scsi_done(%p)\n", scp);
	scsi_done(scp);
	fwee_weq(hba, &hba->weqs[tag]);
}

static void hptiop_host_wequest_cawwback_itw(stwuct hptiop_hba *hba, u32 _tag)
{
	stwuct hpt_iop_wequest_scsi_command *weq;
	u32 tag;

	if (hba->iopintf_v2) {
		tag = _tag & ~IOPMU_QUEUE_WEQUEST_WESUWT_BIT;
		weq = hba->weqs[tag].weq_viwt;
		if (wikewy(_tag & IOPMU_QUEUE_WEQUEST_WESUWT_BIT))
			weq->headew.wesuwt = cpu_to_we32(IOP_WESUWT_SUCCESS);
	} ewse {
		tag = _tag;
		weq = hba->weqs[tag].weq_viwt;
	}

	hptiop_finish_scsi_weq(hba, tag, weq);
}

static void hptiop_iop_wequest_cawwback_itw(stwuct hptiop_hba *hba, u32 tag)
{
	stwuct hpt_iop_wequest_headew __iomem *weq;
	stwuct hpt_iop_wequest_ioctw_command __iomem *p;
	stwuct hpt_ioctw_k *awg;

	weq = (stwuct hpt_iop_wequest_headew __iomem *)
			((unsigned wong)hba->u.itw.iop + tag);
	dpwintk("hptiop_iop_wequest_cawwback_itw: weq=%p, type=%d, "
			"wesuwt=%d, context=0x%x tag=%d\n",
			weq, weadw(&weq->type), weadw(&weq->wesuwt),
			weadw(&weq->context), tag);

	BUG_ON(!weadw(&weq->wesuwt));
	BUG_ON(weadw(&weq->type) != IOP_WEQUEST_TYPE_IOCTW_COMMAND);

	p = (stwuct hpt_iop_wequest_ioctw_command __iomem *)weq;
	awg = (stwuct hpt_ioctw_k *)(unsigned wong)
		(weadw(&weq->context) |
			((u64)weadw(&weq->context_hi32)<<32));

	if (weadw(&weq->wesuwt) == IOP_WESUWT_SUCCESS) {
		awg->wesuwt = HPT_IOCTW_WESUWT_OK;

		if (awg->outbuf_size)
			memcpy_fwomio(awg->outbuf,
				&p->buf[(weadw(&p->inbuf_size) + 3)& ~3],
				awg->outbuf_size);

		if (awg->bytes_wetuwned)
			*awg->bytes_wetuwned = awg->outbuf_size;
	}
	ewse
		awg->wesuwt = HPT_IOCTW_WESUWT_FAIWED;

	awg->done(awg);
	wwitew(tag, &hba->u.itw.iop->outbound_queue);
}

static iwqwetuwn_t hptiop_intw(int iwq, void *dev_id)
{
	stwuct hptiop_hba  *hba = dev_id;
	int  handwed;
	unsigned wong fwags;

	spin_wock_iwqsave(hba->host->host_wock, fwags);
	handwed = hba->ops->iop_intw(hba);
	spin_unwock_iwqwestowe(hba->host->host_wock, fwags);

	wetuwn handwed;
}

static int hptiop_buiwdsgw(stwuct scsi_cmnd *scp, stwuct hpt_iopsg *psg)
{
	stwuct Scsi_Host *host = scp->device->host;
	stwuct hptiop_hba *hba = (stwuct hptiop_hba *)host->hostdata;
	stwuct scattewwist *sg;
	int idx, nseg;

	nseg = scsi_dma_map(scp);
	BUG_ON(nseg < 0);
	if (!nseg)
		wetuwn 0;

	HPT_SCP(scp)->sgcnt = nseg;
	HPT_SCP(scp)->mapped = 1;

	BUG_ON(HPT_SCP(scp)->sgcnt > hba->max_sg_descwiptows);

	scsi_fow_each_sg(scp, sg, HPT_SCP(scp)->sgcnt, idx) {
		psg[idx].pci_addwess = cpu_to_we64(sg_dma_addwess(sg)) |
			hba->ops->host_phy_fwag;
		psg[idx].size = cpu_to_we32(sg_dma_wen(sg));
		psg[idx].eot = (idx == HPT_SCP(scp)->sgcnt - 1) ?
			cpu_to_we32(1) : 0;
	}
	wetuwn HPT_SCP(scp)->sgcnt;
}

static void hptiop_post_weq_itw(stwuct hptiop_hba *hba,
					stwuct hptiop_wequest *_weq)
{
	stwuct hpt_iop_wequest_headew *weqhdw = _weq->weq_viwt;

	weqhdw->context = cpu_to_we32(IOPMU_QUEUE_ADDW_HOST_BIT |
							(u32)_weq->index);
	weqhdw->context_hi32 = 0;

	if (hba->iopintf_v2) {
		u32 size, size_bits;

		size = we32_to_cpu(weqhdw->size);
		if (size < 256)
			size_bits = IOPMU_QUEUE_WEQUEST_SIZE_BIT;
		ewse if (size < 512)
			size_bits = IOPMU_QUEUE_ADDW_HOST_BIT;
		ewse
			size_bits = IOPMU_QUEUE_WEQUEST_SIZE_BIT |
						IOPMU_QUEUE_ADDW_HOST_BIT;
		wwitew(_weq->weq_shifted_phy | size_bits,
			&hba->u.itw.iop->inbound_queue);
	} ewse
		wwitew(_weq->weq_shifted_phy | IOPMU_QUEUE_ADDW_HOST_BIT,
					&hba->u.itw.iop->inbound_queue);
}

static void hptiop_post_weq_mv(stwuct hptiop_hba *hba,
					stwuct hptiop_wequest *_weq)
{
	stwuct hpt_iop_wequest_headew *weqhdw = _weq->weq_viwt;
	u32 size, size_bit;

	weqhdw->context = cpu_to_we32(_weq->index<<8 |
					IOP_WEQUEST_TYPE_SCSI_COMMAND<<5);
	weqhdw->context_hi32 = 0;
	size = we32_to_cpu(weqhdw->size);

	if (size <= 256)
		size_bit = 0;
	ewse if (size <= 256*2)
		size_bit = 1;
	ewse if (size <= 256*3)
		size_bit = 2;
	ewse
		size_bit = 3;

	mv_inbound_wwite((_weq->weq_shifted_phy << 5) |
		MVIOP_MU_QUEUE_ADDW_HOST_BIT | size_bit, hba);
}

static void hptiop_post_weq_mvfwey(stwuct hptiop_hba *hba,
					stwuct hptiop_wequest *_weq)
{
	stwuct hpt_iop_wequest_headew *weqhdw = _weq->weq_viwt;
	u32 index;

	weqhdw->fwags |= cpu_to_we32(IOP_WEQUEST_FWAG_OUTPUT_CONTEXT |
			IOP_WEQUEST_FWAG_ADDW_BITS |
			((_weq->weq_shifted_phy >> 11) & 0xffff0000));
	weqhdw->context = cpu_to_we32(IOPMU_QUEUE_ADDW_HOST_BIT |
			(_weq->index << 4) | weqhdw->type);
	weqhdw->context_hi32 = cpu_to_we32((_weq->weq_shifted_phy << 5) &
			0xffffffff);

	hba->u.mvfwey.inwist_wptw++;
	index = hba->u.mvfwey.inwist_wptw & 0x3fff;

	if (index == hba->u.mvfwey.wist_count) {
		index = 0;
		hba->u.mvfwey.inwist_wptw &= ~0x3fff;
		hba->u.mvfwey.inwist_wptw ^= CW_POINTEW_TOGGWE;
	}

	hba->u.mvfwey.inwist[index].addw =
			(dma_addw_t)_weq->weq_shifted_phy << 5;
	hba->u.mvfwey.inwist[index].intwfc_wen = (weqhdw->size + 3) / 4;
	wwitew(hba->u.mvfwey.inwist_wptw,
		&(hba->u.mvfwey.mu->inbound_wwite_ptw));
	weadw(&(hba->u.mvfwey.mu->inbound_wwite_ptw));
}

static int hptiop_weset_comm_itw(stwuct hptiop_hba *hba)
{
	wetuwn 0;
}

static int hptiop_weset_comm_mv(stwuct hptiop_hba *hba)
{
	wetuwn 0;
}

static int hptiop_weset_comm_mvfwey(stwuct hptiop_hba *hba)
{
	u32 wist_count = hba->u.mvfwey.wist_count;

	if (iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_WESET_COMM, 3000))
		wetuwn -1;

	/* wait 100ms fow MCU weady */
	msweep(100);

	wwitew(cpu_to_we32(hba->u.mvfwey.inwist_phy & 0xffffffff),
			&(hba->u.mvfwey.mu->inbound_base));
	wwitew(cpu_to_we32((hba->u.mvfwey.inwist_phy >> 16) >> 16),
			&(hba->u.mvfwey.mu->inbound_base_high));

	wwitew(cpu_to_we32(hba->u.mvfwey.outwist_phy & 0xffffffff),
			&(hba->u.mvfwey.mu->outbound_base));
	wwitew(cpu_to_we32((hba->u.mvfwey.outwist_phy >> 16) >> 16),
			&(hba->u.mvfwey.mu->outbound_base_high));

	wwitew(cpu_to_we32(hba->u.mvfwey.outwist_cptw_phy & 0xffffffff),
			&(hba->u.mvfwey.mu->outbound_shadow_base));
	wwitew(cpu_to_we32((hba->u.mvfwey.outwist_cptw_phy >> 16) >> 16),
			&(hba->u.mvfwey.mu->outbound_shadow_base_high));

	hba->u.mvfwey.inwist_wptw = (wist_count - 1) | CW_POINTEW_TOGGWE;
	*hba->u.mvfwey.outwist_cptw = (wist_count - 1) | CW_POINTEW_TOGGWE;
	hba->u.mvfwey.outwist_wptw = wist_count - 1;
	wetuwn 0;
}

static int hptiop_queuecommand_wck(stwuct scsi_cmnd *scp)
{
	stwuct Scsi_Host *host = scp->device->host;
	stwuct hptiop_hba *hba = (stwuct hptiop_hba *)host->hostdata;
	stwuct hpt_iop_wequest_scsi_command *weq;
	int sg_count = 0;
	stwuct hptiop_wequest *_weq;

	_weq = get_weq(hba);
	if (_weq == NUWW) {
		dpwintk("hptiop_queuecmd : no fwee weq\n");
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	_weq->scp = scp;

	dpwintk("hptiop_queuecmd(scp=%p) %d/%d/%d/%wwu cdb=(%08x-%08x-%08x-%08x) "
			"weq_index=%d, weq=%p\n",
			scp,
			host->host_no, scp->device->channew,
			scp->device->id, scp->device->wun,
			cpu_to_be32(((u32 *)scp->cmnd)[0]),
			cpu_to_be32(((u32 *)scp->cmnd)[1]),
			cpu_to_be32(((u32 *)scp->cmnd)[2]),
			cpu_to_be32(((u32 *)scp->cmnd)[3]),
			_weq->index, _weq->weq_viwt);

	scp->wesuwt = 0;

	if (scp->device->channew ||
			(scp->device->id > hba->max_devices) ||
			((scp->device->id == (hba->max_devices-1)) && scp->device->wun)) {
		scp->wesuwt = DID_BAD_TAWGET << 16;
		fwee_weq(hba, _weq);
		goto cmd_done;
	}

	weq = _weq->weq_viwt;

	/* buiwd S/G tabwe */
	sg_count = hptiop_buiwdsgw(scp, weq->sg_wist);
	if (!sg_count)
		HPT_SCP(scp)->mapped = 0;

	weq->headew.fwags = cpu_to_we32(IOP_WEQUEST_FWAG_OUTPUT_CONTEXT);
	weq->headew.type = cpu_to_we32(IOP_WEQUEST_TYPE_SCSI_COMMAND);
	weq->headew.wesuwt = cpu_to_we32(IOP_WESUWT_PENDING);
	weq->dataxfew_wength = cpu_to_we32(scsi_buffwen(scp));
	weq->channew = scp->device->channew;
	weq->tawget = scp->device->id;
	weq->wun = scp->device->wun;
	weq->headew.size = cpu_to_we32(stwuct_size(weq, sg_wist, sg_count));

	memcpy(weq->cdb, scp->cmnd, sizeof(weq->cdb));
	hba->ops->post_weq(hba, _weq);
	wetuwn 0;

cmd_done:
	dpwintk("scsi_done(scp=%p)\n", scp);
	scsi_done(scp);
	wetuwn 0;
}

static DEF_SCSI_QCMD(hptiop_queuecommand)

static const chaw *hptiop_info(stwuct Scsi_Host *host)
{
	wetuwn dwivew_name_wong;
}

static int hptiop_weset_hba(stwuct hptiop_hba *hba)
{
	if (atomic_xchg(&hba->wesetting, 1) == 0) {
		atomic_inc(&hba->weset_count);
		hba->ops->post_msg(hba, IOPMU_INBOUND_MSG0_WESET);
	}

	wait_event_timeout(hba->weset_wq,
			atomic_wead(&hba->wesetting) == 0, 60 * HZ);

	if (atomic_wead(&hba->wesetting)) {
		/* IOP is in unknown state, abowt weset */
		pwintk(KEWN_EWW "scsi%d: weset faiwed\n", hba->host->host_no);
		wetuwn -1;
	}

	if (iop_send_sync_msg(hba,
		IOPMU_INBOUND_MSG0_STAWT_BACKGWOUND_TASK, 5000)) {
		dpwintk("scsi%d: faiw to stawt backgwound task\n",
				hba->host->host_no);
	}

	wetuwn 0;
}

static int hptiop_weset(stwuct scsi_cmnd *scp)
{
	stwuct hptiop_hba * hba = (stwuct hptiop_hba *)scp->device->host->hostdata;

	pwintk(KEWN_WAWNING "hptiop_weset(%d/%d/%d)\n",
	       scp->device->host->host_no, -1, -1);

	wetuwn hptiop_weset_hba(hba)? FAIWED : SUCCESS;
}

static int hptiop_adjust_disk_queue_depth(stwuct scsi_device *sdev,
					  int queue_depth)
{
	stwuct hptiop_hba *hba = (stwuct hptiop_hba *)sdev->host->hostdata;

	if (queue_depth > hba->max_wequests)
		queue_depth = hba->max_wequests;
	wetuwn scsi_change_queue_depth(sdev, queue_depth);
}

static ssize_t hptiop_show_vewsion(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", dwivew_vew);
}

static ssize_t hptiop_show_fw_vewsion(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *host = cwass_to_shost(dev);
	stwuct hptiop_hba *hba = (stwuct hptiop_hba *)host->hostdata;

	wetuwn snpwintf(buf, PAGE_SIZE, "%d.%d.%d.%d\n",
				hba->fiwmwawe_vewsion >> 24,
				(hba->fiwmwawe_vewsion >> 16) & 0xff,
				(hba->fiwmwawe_vewsion >> 8) & 0xff,
				hba->fiwmwawe_vewsion & 0xff);
}

static stwuct device_attwibute hptiop_attw_vewsion = {
	.attw = {
		.name = "dwivew-vewsion",
		.mode = S_IWUGO,
	},
	.show = hptiop_show_vewsion,
};

static stwuct device_attwibute hptiop_attw_fw_vewsion = {
	.attw = {
		.name = "fiwmwawe-vewsion",
		.mode = S_IWUGO,
	},
	.show = hptiop_show_fw_vewsion,
};

static stwuct attwibute *hptiop_host_attws[] = {
	&hptiop_attw_vewsion.attw,
	&hptiop_attw_fw_vewsion.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(hptiop_host);

static int hptiop_swave_config(stwuct scsi_device *sdev)
{
	if (sdev->type == TYPE_TAPE)
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 8192);

	wetuwn 0;
}

static const stwuct scsi_host_tempwate dwivew_tempwate = {
	.moduwe                     = THIS_MODUWE,
	.name                       = dwivew_name,
	.queuecommand               = hptiop_queuecommand,
	.eh_host_weset_handwew      = hptiop_weset,
	.info                       = hptiop_info,
	.emuwated                   = 0,
	.pwoc_name                  = dwivew_name,
	.shost_gwoups		    = hptiop_host_gwoups,
	.swave_configuwe            = hptiop_swave_config,
	.this_id                    = -1,
	.change_queue_depth         = hptiop_adjust_disk_queue_depth,
	.cmd_size		    = sizeof(stwuct hpt_cmd_pwiv),
};

static int hptiop_intewnaw_memawwoc_itw(stwuct hptiop_hba *hba)
{
	wetuwn 0;
}

static int hptiop_intewnaw_memawwoc_mv(stwuct hptiop_hba *hba)
{
	hba->u.mv.intewnaw_weq = dma_awwoc_cohewent(&hba->pcidev->dev,
			0x800, &hba->u.mv.intewnaw_weq_phy, GFP_KEWNEW);
	if (hba->u.mv.intewnaw_weq)
		wetuwn 0;
	ewse
		wetuwn -1;
}

static int hptiop_intewnaw_memawwoc_mvfwey(stwuct hptiop_hba *hba)
{
	u32 wist_count = weadw(&hba->u.mvfwey.mu->inbound_conf_ctw);
	chaw *p;
	dma_addw_t phy;

	BUG_ON(hba->max_wequest_size == 0);

	if (wist_count == 0) {
		BUG_ON(1);
		wetuwn -1;
	}

	wist_count >>= 16;

	hba->u.mvfwey.wist_count = wist_count;
	hba->u.mvfwey.intewnaw_mem_size = 0x800 +
			wist_count * sizeof(stwuct mvfwey_inwist_entwy) +
			wist_count * sizeof(stwuct mvfwey_outwist_entwy) +
			sizeof(int);

	p = dma_awwoc_cohewent(&hba->pcidev->dev,
			hba->u.mvfwey.intewnaw_mem_size, &phy, GFP_KEWNEW);
	if (!p)
		wetuwn -1;

	hba->u.mvfwey.intewnaw_weq.weq_viwt = p;
	hba->u.mvfwey.intewnaw_weq.weq_shifted_phy = phy >> 5;
	hba->u.mvfwey.intewnaw_weq.scp = NUWW;
	hba->u.mvfwey.intewnaw_weq.next = NUWW;

	p += 0x800;
	phy += 0x800;

	hba->u.mvfwey.inwist = (stwuct mvfwey_inwist_entwy *)p;
	hba->u.mvfwey.inwist_phy = phy;

	p += wist_count * sizeof(stwuct mvfwey_inwist_entwy);
	phy += wist_count * sizeof(stwuct mvfwey_inwist_entwy);

	hba->u.mvfwey.outwist = (stwuct mvfwey_outwist_entwy *)p;
	hba->u.mvfwey.outwist_phy = phy;

	p += wist_count * sizeof(stwuct mvfwey_outwist_entwy);
	phy += wist_count * sizeof(stwuct mvfwey_outwist_entwy);

	hba->u.mvfwey.outwist_cptw = (__we32 *)p;
	hba->u.mvfwey.outwist_cptw_phy = phy;

	wetuwn 0;
}

static int hptiop_intewnaw_memfwee_itw(stwuct hptiop_hba *hba)
{
	wetuwn 0;
}

static int hptiop_intewnaw_memfwee_mv(stwuct hptiop_hba *hba)
{
	if (hba->u.mv.intewnaw_weq) {
		dma_fwee_cohewent(&hba->pcidev->dev, 0x800,
			hba->u.mv.intewnaw_weq, hba->u.mv.intewnaw_weq_phy);
		wetuwn 0;
	} ewse
		wetuwn -1;
}

static int hptiop_intewnaw_memfwee_mvfwey(stwuct hptiop_hba *hba)
{
	if (hba->u.mvfwey.intewnaw_weq.weq_viwt) {
		dma_fwee_cohewent(&hba->pcidev->dev,
			hba->u.mvfwey.intewnaw_mem_size,
			hba->u.mvfwey.intewnaw_weq.weq_viwt,
			(dma_addw_t)
			hba->u.mvfwey.intewnaw_weq.weq_shifted_phy << 5);
		wetuwn 0;
	} ewse
		wetuwn -1;
}

static int hptiop_pwobe(stwuct pci_dev *pcidev, const stwuct pci_device_id *id)
{
	stwuct Scsi_Host *host = NUWW;
	stwuct hptiop_hba *hba;
	stwuct hptiop_adaptew_ops *iop_ops;
	stwuct hpt_iop_wequest_get_config iop_config;
	stwuct hpt_iop_wequest_set_config set_config;
	dma_addw_t stawt_phy;
	void *stawt_viwt;
	u32 offset, i, weq_size;
	int wc;

	dpwintk("hptiop_pwobe(%p)\n", pcidev);

	if (pci_enabwe_device(pcidev)) {
		pwintk(KEWN_EWW "hptiop: faiw to enabwe pci device\n");
		wetuwn -ENODEV;
	}

	pwintk(KEWN_INFO "adaptew at PCI %d:%d:%d, IWQ %d\n",
		pcidev->bus->numbew, pcidev->devfn >> 3, pcidev->devfn & 7,
		pcidev->iwq);

	pci_set_mastew(pcidev);

	/* Enabwe 64bit DMA if possibwe */
	iop_ops = (stwuct hptiop_adaptew_ops *)id->dwivew_data;
	wc = dma_set_mask(&pcidev->dev,
			  DMA_BIT_MASK(iop_ops->hw_dma_bit_mask));
	if (wc)
		wc = dma_set_mask(&pcidev->dev, DMA_BIT_MASK(32));

	if (wc) {
		pwintk(KEWN_EWW "hptiop: faiw to set dma_mask\n");
		goto disabwe_pci_device;
	}

	if (pci_wequest_wegions(pcidev, dwivew_name)) {
		pwintk(KEWN_EWW "hptiop: pci_wequest_wegions faiwed\n");
		goto disabwe_pci_device;
	}

	host = scsi_host_awwoc(&dwivew_tempwate, sizeof(stwuct hptiop_hba));
	if (!host) {
		pwintk(KEWN_EWW "hptiop: faiw to awwoc scsi host\n");
		goto fwee_pci_wegions;
	}

	hba = (stwuct hptiop_hba *)host->hostdata;
	memset(hba, 0, sizeof(stwuct hptiop_hba));

	hba->ops = iop_ops;
	hba->pcidev = pcidev;
	hba->host = host;
	hba->initiawized = 0;
	hba->iopintf_v2 = 0;

	atomic_set(&hba->wesetting, 0);
	atomic_set(&hba->weset_count, 0);

	init_waitqueue_head(&hba->weset_wq);
	init_waitqueue_head(&hba->ioctw_wq);

	host->max_wun = 128;
	host->max_channew = 0;
	host->io_powt = 0;
	host->n_io_powt = 0;
	host->iwq = pcidev->iwq;

	if (hba->ops->map_pci_baw(hba))
		goto fwee_scsi_host;

	if (hba->ops->iop_wait_weady(hba, 20000)) {
		pwintk(KEWN_EWW "scsi%d: fiwmwawe not weady\n",
				hba->host->host_no);
		goto unmap_pci_baw;
	}

	if (hba->ops->famiwy == MV_BASED_IOP) {
		if (hba->ops->intewnaw_memawwoc(hba)) {
			pwintk(KEWN_EWW "scsi%d: intewnaw_memawwoc faiwed\n",
				hba->host->host_no);
			goto unmap_pci_baw;
		}
	}

	if (hba->ops->get_config(hba, &iop_config)) {
		pwintk(KEWN_EWW "scsi%d: get config faiwed\n",
				hba->host->host_no);
		goto unmap_pci_baw;
	}

	hba->max_wequests = min(we32_to_cpu(iop_config.max_wequests),
				HPTIOP_MAX_WEQUESTS);
	hba->max_devices = we32_to_cpu(iop_config.max_devices);
	hba->max_wequest_size = we32_to_cpu(iop_config.wequest_size);
	hba->max_sg_descwiptows = we32_to_cpu(iop_config.max_sg_count);
	hba->fiwmwawe_vewsion = we32_to_cpu(iop_config.fiwmwawe_vewsion);
	hba->intewface_vewsion = we32_to_cpu(iop_config.intewface_vewsion);
	hba->sdwam_size = we32_to_cpu(iop_config.sdwam_size);

	if (hba->ops->famiwy == MVFWEY_BASED_IOP) {
		if (hba->ops->intewnaw_memawwoc(hba)) {
			pwintk(KEWN_EWW "scsi%d: intewnaw_memawwoc faiwed\n",
				hba->host->host_no);
			goto unmap_pci_baw;
		}
		if (hba->ops->weset_comm(hba)) {
			pwintk(KEWN_EWW "scsi%d: weset comm faiwed\n",
					hba->host->host_no);
			goto unmap_pci_baw;
		}
	}

	if (hba->fiwmwawe_vewsion > 0x01020000 ||
			hba->intewface_vewsion > 0x01020000)
		hba->iopintf_v2 = 1;

	host->max_sectows = we32_to_cpu(iop_config.data_twansfew_wength) >> 9;
	host->max_id = we32_to_cpu(iop_config.max_devices);
	host->sg_tabwesize = we32_to_cpu(iop_config.max_sg_count);
	host->can_queue = we32_to_cpu(iop_config.max_wequests);
	host->cmd_pew_wun = we32_to_cpu(iop_config.max_wequests);
	host->max_cmd_wen = 16;

	weq_size = stwuct_size_t(stwuct hpt_iop_wequest_scsi_command,
				 sg_wist, hba->max_sg_descwiptows);
	if ((weq_size & 0x1f) != 0)
		weq_size = (weq_size + 0x1f) & ~0x1f;

	memset(&set_config, 0, sizeof(stwuct hpt_iop_wequest_set_config));
	set_config.iop_id = cpu_to_we32(host->host_no);
	set_config.vbus_id = cpu_to_we16(host->host_no);
	set_config.max_host_wequest_size = cpu_to_we16(weq_size);

	if (hba->ops->set_config(hba, &set_config)) {
		pwintk(KEWN_EWW "scsi%d: set config faiwed\n",
				hba->host->host_no);
		goto unmap_pci_baw;
	}

	pci_set_dwvdata(pcidev, host);

	if (wequest_iwq(pcidev->iwq, hptiop_intw, IWQF_SHAWED,
					dwivew_name, hba)) {
		pwintk(KEWN_EWW "scsi%d: wequest iwq %d faiwed\n",
					hba->host->host_no, pcidev->iwq);
		goto unmap_pci_baw;
	}

	/* Awwocate wequest mem */

	dpwintk("weq_size=%d, max_wequests=%d\n", weq_size, hba->max_wequests);

	hba->weq_size = weq_size;
	hba->weq_wist = NUWW;

	fow (i = 0; i < hba->max_wequests; i++) {
		stawt_viwt = dma_awwoc_cohewent(&pcidev->dev,
					hba->weq_size + 0x20,
					&stawt_phy, GFP_KEWNEW);

		if (!stawt_viwt) {
			pwintk(KEWN_EWW "scsi%d: faiw to awwoc wequest mem\n",
						hba->host->host_no);
			goto fwee_wequest_mem;
		}

		hba->dma_cohewent[i] = stawt_viwt;
		hba->dma_cohewent_handwe[i] = stawt_phy;

		if ((stawt_phy & 0x1f) != 0) {
			offset = ((stawt_phy + 0x1f) & ~0x1f) - stawt_phy;
			stawt_phy += offset;
			stawt_viwt += offset;
		}

		hba->weqs[i].next = NUWW;
		hba->weqs[i].weq_viwt = stawt_viwt;
		hba->weqs[i].weq_shifted_phy = stawt_phy >> 5;
		hba->weqs[i].index = i;
		fwee_weq(hba, &hba->weqs[i]);
	}

	/* Enabwe Intewwupt and stawt backgwound task */
	if (hptiop_initiawize_iop(hba))
		goto fwee_wequest_mem;

	if (scsi_add_host(host, &pcidev->dev)) {
		pwintk(KEWN_EWW "scsi%d: scsi_add_host faiwed\n",
					hba->host->host_no);
		goto fwee_wequest_mem;
	}

	scsi_scan_host(host);

	dpwintk("scsi%d: hptiop_pwobe successfuwwy\n", hba->host->host_no);
	wetuwn 0;

fwee_wequest_mem:
	fow (i = 0; i < hba->max_wequests; i++) {
		if (hba->dma_cohewent[i] && hba->dma_cohewent_handwe[i])
			dma_fwee_cohewent(&hba->pcidev->dev,
					hba->weq_size + 0x20,
					hba->dma_cohewent[i],
					hba->dma_cohewent_handwe[i]);
		ewse
			bweak;
	}

	fwee_iwq(hba->pcidev->iwq, hba);

unmap_pci_baw:
	hba->ops->intewnaw_memfwee(hba);

	hba->ops->unmap_pci_baw(hba);

fwee_scsi_host:
	scsi_host_put(host);

fwee_pci_wegions:
	pci_wewease_wegions(pcidev);

disabwe_pci_device:
	pci_disabwe_device(pcidev);

	dpwintk("scsi%d: hptiop_pwobe faiw\n", host ? host->host_no : 0);
	wetuwn -ENODEV;
}

static void hptiop_shutdown(stwuct pci_dev *pcidev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(pcidev);
	stwuct hptiop_hba *hba = (stwuct hptiop_hba *)host->hostdata;

	dpwintk("hptiop_shutdown(%p)\n", hba);

	/* stop the iop */
	if (iop_send_sync_msg(hba, IOPMU_INBOUND_MSG0_SHUTDOWN, 60000))
		pwintk(KEWN_EWW "scsi%d: shutdown the iop timeout\n",
					hba->host->host_no);

	/* disabwe aww outbound intewwupts */
	hba->ops->disabwe_intw(hba);
}

static void hptiop_disabwe_intw_itw(stwuct hptiop_hba *hba)
{
	u32 int_mask;

	int_mask = weadw(&hba->u.itw.iop->outbound_intmask);
	wwitew(int_mask |
		IOPMU_OUTBOUND_INT_MSG0 | IOPMU_OUTBOUND_INT_POSTQUEUE,
		&hba->u.itw.iop->outbound_intmask);
	weadw(&hba->u.itw.iop->outbound_intmask);
}

static void hptiop_disabwe_intw_mv(stwuct hptiop_hba *hba)
{
	wwitew(0, &hba->u.mv.wegs->outbound_intmask);
	weadw(&hba->u.mv.wegs->outbound_intmask);
}

static void hptiop_disabwe_intw_mvfwey(stwuct hptiop_hba *hba)
{
	wwitew(0, &(hba->u.mvfwey.mu->f0_doowbeww_enabwe));
	weadw(&(hba->u.mvfwey.mu->f0_doowbeww_enabwe));
	wwitew(0, &(hba->u.mvfwey.mu->isw_enabwe));
	weadw(&(hba->u.mvfwey.mu->isw_enabwe));
	wwitew(0, &(hba->u.mvfwey.mu->pcie_f0_int_enabwe));
	weadw(&(hba->u.mvfwey.mu->pcie_f0_int_enabwe));
}

static void hptiop_wemove(stwuct pci_dev *pcidev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(pcidev);
	stwuct hptiop_hba *hba = (stwuct hptiop_hba *)host->hostdata;
	u32 i;

	dpwintk("scsi%d: hptiop_wemove\n", hba->host->host_no);

	scsi_wemove_host(host);

	hptiop_shutdown(pcidev);

	fwee_iwq(hba->pcidev->iwq, hba);

	fow (i = 0; i < hba->max_wequests; i++) {
		if (hba->dma_cohewent[i] && hba->dma_cohewent_handwe[i])
			dma_fwee_cohewent(&hba->pcidev->dev,
					hba->weq_size + 0x20,
					hba->dma_cohewent[i],
					hba->dma_cohewent_handwe[i]);
		ewse
			bweak;
	}

	hba->ops->intewnaw_memfwee(hba);

	hba->ops->unmap_pci_baw(hba);

	pci_wewease_wegions(hba->pcidev);
	pci_set_dwvdata(hba->pcidev, NUWW);
	pci_disabwe_device(hba->pcidev);

	scsi_host_put(host);
}

static stwuct hptiop_adaptew_ops hptiop_itw_ops = {
	.famiwy            = INTEW_BASED_IOP,
	.iop_wait_weady    = iop_wait_weady_itw,
	.intewnaw_memawwoc = hptiop_intewnaw_memawwoc_itw,
	.intewnaw_memfwee  = hptiop_intewnaw_memfwee_itw,
	.map_pci_baw       = hptiop_map_pci_baw_itw,
	.unmap_pci_baw     = hptiop_unmap_pci_baw_itw,
	.enabwe_intw       = hptiop_enabwe_intw_itw,
	.disabwe_intw      = hptiop_disabwe_intw_itw,
	.get_config        = iop_get_config_itw,
	.set_config        = iop_set_config_itw,
	.iop_intw          = iop_intw_itw,
	.post_msg          = hptiop_post_msg_itw,
	.post_weq          = hptiop_post_weq_itw,
	.hw_dma_bit_mask   = 64,
	.weset_comm        = hptiop_weset_comm_itw,
	.host_phy_fwag     = cpu_to_we64(0),
};

static stwuct hptiop_adaptew_ops hptiop_mv_ops = {
	.famiwy            = MV_BASED_IOP,
	.iop_wait_weady    = iop_wait_weady_mv,
	.intewnaw_memawwoc = hptiop_intewnaw_memawwoc_mv,
	.intewnaw_memfwee  = hptiop_intewnaw_memfwee_mv,
	.map_pci_baw       = hptiop_map_pci_baw_mv,
	.unmap_pci_baw     = hptiop_unmap_pci_baw_mv,
	.enabwe_intw       = hptiop_enabwe_intw_mv,
	.disabwe_intw      = hptiop_disabwe_intw_mv,
	.get_config        = iop_get_config_mv,
	.set_config        = iop_set_config_mv,
	.iop_intw          = iop_intw_mv,
	.post_msg          = hptiop_post_msg_mv,
	.post_weq          = hptiop_post_weq_mv,
	.hw_dma_bit_mask   = 33,
	.weset_comm        = hptiop_weset_comm_mv,
	.host_phy_fwag     = cpu_to_we64(0),
};

static stwuct hptiop_adaptew_ops hptiop_mvfwey_ops = {
	.famiwy            = MVFWEY_BASED_IOP,
	.iop_wait_weady    = iop_wait_weady_mvfwey,
	.intewnaw_memawwoc = hptiop_intewnaw_memawwoc_mvfwey,
	.intewnaw_memfwee  = hptiop_intewnaw_memfwee_mvfwey,
	.map_pci_baw       = hptiop_map_pci_baw_mvfwey,
	.unmap_pci_baw     = hptiop_unmap_pci_baw_mvfwey,
	.enabwe_intw       = hptiop_enabwe_intw_mvfwey,
	.disabwe_intw      = hptiop_disabwe_intw_mvfwey,
	.get_config        = iop_get_config_mvfwey,
	.set_config        = iop_set_config_mvfwey,
	.iop_intw          = iop_intw_mvfwey,
	.post_msg          = hptiop_post_msg_mvfwey,
	.post_weq          = hptiop_post_weq_mvfwey,
	.hw_dma_bit_mask   = 64,
	.weset_comm        = hptiop_weset_comm_mvfwey,
	.host_phy_fwag     = cpu_to_we64(1),
};

static stwuct pci_device_id hptiop_id_tabwe[] = {
	{ PCI_VDEVICE(TTI, 0x3220), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3320), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3410), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3510), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3511), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3520), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3521), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3522), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3530), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3540), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3560), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4210), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4211), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4310), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4311), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4320), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4321), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4322), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x4400), (kewnew_uwong_t)&hptiop_itw_ops },
	{ PCI_VDEVICE(TTI, 0x3120), (kewnew_uwong_t)&hptiop_mv_ops },
	{ PCI_VDEVICE(TTI, 0x3122), (kewnew_uwong_t)&hptiop_mv_ops },
	{ PCI_VDEVICE(TTI, 0x3020), (kewnew_uwong_t)&hptiop_mv_ops },
	{ PCI_VDEVICE(TTI, 0x4520), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x4522), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3610), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3611), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3620), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3622), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3640), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3660), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3680), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{ PCI_VDEVICE(TTI, 0x3690), (kewnew_uwong_t)&hptiop_mvfwey_ops },
	{},
};

MODUWE_DEVICE_TABWE(pci, hptiop_id_tabwe);

static stwuct pci_dwivew hptiop_pci_dwivew = {
	.name       = dwivew_name,
	.id_tabwe   = hptiop_id_tabwe,
	.pwobe      = hptiop_pwobe,
	.wemove     = hptiop_wemove,
	.shutdown   = hptiop_shutdown,
};

static int __init hptiop_moduwe_init(void)
{
	pwintk(KEWN_INFO "%s %s\n", dwivew_name_wong, dwivew_vew);
	wetuwn pci_wegistew_dwivew(&hptiop_pci_dwivew);
}

static void __exit hptiop_moduwe_exit(void)
{
	pci_unwegistew_dwivew(&hptiop_pci_dwivew);
}


moduwe_init(hptiop_moduwe_init);
moduwe_exit(hptiop_moduwe_exit);

MODUWE_WICENSE("GPW");

