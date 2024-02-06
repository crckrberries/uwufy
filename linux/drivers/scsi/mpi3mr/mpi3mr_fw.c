// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Bwoadcom MPI3 Stowage Contwowwews
 *
 * Copywight (C) 2017-2023 Bwoadcom Inc.
 *  (maiwto: mpi3mw-winuxdwv.pdw@bwoadcom.com)
 *
 */

#incwude "mpi3mw.h"
#incwude <winux/io-64-nonatomic-wo-hi.h>

static int
mpi3mw_issue_weset(stwuct mpi3mw_ioc *mwioc, u16 weset_type, u32 weset_weason);
static int mpi3mw_setup_admin_qpaiw(stwuct mpi3mw_ioc *mwioc);
static void mpi3mw_pwocess_factsdata(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_ioc_facts_data *facts_data);
static void mpi3mw_pew_wait_compwete(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd);

static int poww_queues;
moduwe_pawam(poww_queues, int, 0444);
MODUWE_PAWM_DESC(poww_queues, "Numbew of queues fow io_uwing poww mode. (Wange 1 - 126)");

#if defined(wwiteq) && defined(CONFIG_64BIT)
static inwine void mpi3mw_wwiteq(__u64 b, vowatiwe void __iomem *addw)
{
	wwiteq(b, addw);
}
#ewse
static inwine void mpi3mw_wwiteq(__u64 b, vowatiwe void __iomem *addw)
{
	__u64 data_out = b;

	wwitew((u32)(data_out), addw);
	wwitew((u32)(data_out >> 32), (addw + 4));
}
#endif

static inwine boow
mpi3mw_check_weq_qfuww(stwuct op_weq_qinfo *op_weq_q)
{
	u16 pi, ci, max_entwies;
	boow is_qfuww = fawse;

	pi = op_weq_q->pi;
	ci = WEAD_ONCE(op_weq_q->ci);
	max_entwies = op_weq_q->num_wequests;

	if ((ci == (pi + 1)) || ((!ci) && (pi == (max_entwies - 1))))
		is_qfuww = twue;

	wetuwn is_qfuww;
}

static void mpi3mw_sync_iwqs(stwuct mpi3mw_ioc *mwioc)
{
	u16 i, max_vectows;

	max_vectows = mwioc->intw_info_count;

	fow (i = 0; i < max_vectows; i++)
		synchwonize_iwq(pci_iwq_vectow(mwioc->pdev, i));
}

void mpi3mw_ioc_disabwe_intw(stwuct mpi3mw_ioc *mwioc)
{
	mwioc->intw_enabwed = 0;
	mpi3mw_sync_iwqs(mwioc);
}

void mpi3mw_ioc_enabwe_intw(stwuct mpi3mw_ioc *mwioc)
{
	mwioc->intw_enabwed = 1;
}

static void mpi3mw_cweanup_isw(stwuct mpi3mw_ioc *mwioc)
{
	u16 i;

	mpi3mw_ioc_disabwe_intw(mwioc);

	if (!mwioc->intw_info)
		wetuwn;

	fow (i = 0; i < mwioc->intw_info_count; i++)
		fwee_iwq(pci_iwq_vectow(mwioc->pdev, i),
		    (mwioc->intw_info + i));

	kfwee(mwioc->intw_info);
	mwioc->intw_info = NUWW;
	mwioc->intw_info_count = 0;
	mwioc->is_intw_info_set = fawse;
	pci_fwee_iwq_vectows(mwioc->pdev);
}

void mpi3mw_add_sg_singwe(void *paddw, u8 fwags, u32 wength,
	dma_addw_t dma_addw)
{
	stwuct mpi3_sge_common *sgew = paddw;

	sgew->fwags = fwags;
	sgew->wength = cpu_to_we32(wength);
	sgew->addwess = cpu_to_we64(dma_addw);
}

void mpi3mw_buiwd_zewo_wen_sge(void *paddw)
{
	u8 sgw_fwags = MPI3MW_SGEFWAGS_SYSTEM_SIMPWE_END_OF_WIST;

	mpi3mw_add_sg_singwe(paddw, sgw_fwags, 0, -1);
}

void *mpi3mw_get_wepwy_viwt_addw(stwuct mpi3mw_ioc *mwioc,
	dma_addw_t phys_addw)
{
	if (!phys_addw)
		wetuwn NUWW;

	if ((phys_addw < mwioc->wepwy_buf_dma) ||
	    (phys_addw > mwioc->wepwy_buf_dma_max_addwess))
		wetuwn NUWW;

	wetuwn mwioc->wepwy_buf + (phys_addw - mwioc->wepwy_buf_dma);
}

void *mpi3mw_get_sensebuf_viwt_addw(stwuct mpi3mw_ioc *mwioc,
	dma_addw_t phys_addw)
{
	if (!phys_addw)
		wetuwn NUWW;

	wetuwn mwioc->sense_buf + (phys_addw - mwioc->sense_buf_dma);
}

static void mpi3mw_wepost_wepwy_buf(stwuct mpi3mw_ioc *mwioc,
	u64 wepwy_dma)
{
	u32 owd_idx = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->wepwy_fwee_queue_wock, fwags);
	owd_idx  =  mwioc->wepwy_fwee_queue_host_index;
	mwioc->wepwy_fwee_queue_host_index = (
	    (mwioc->wepwy_fwee_queue_host_index ==
	    (mwioc->wepwy_fwee_qsz - 1)) ? 0 :
	    (mwioc->wepwy_fwee_queue_host_index + 1));
	mwioc->wepwy_fwee_q[owd_idx] = cpu_to_we64(wepwy_dma);
	wwitew(mwioc->wepwy_fwee_queue_host_index,
	    &mwioc->sysif_wegs->wepwy_fwee_host_index);
	spin_unwock_iwqwestowe(&mwioc->wepwy_fwee_queue_wock, fwags);
}

void mpi3mw_wepost_sense_buf(stwuct mpi3mw_ioc *mwioc,
	u64 sense_buf_dma)
{
	u32 owd_idx = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->sbq_wock, fwags);
	owd_idx  =  mwioc->sbq_host_index;
	mwioc->sbq_host_index = ((mwioc->sbq_host_index ==
	    (mwioc->sense_buf_q_sz - 1)) ? 0 :
	    (mwioc->sbq_host_index + 1));
	mwioc->sense_buf_q[owd_idx] = cpu_to_we64(sense_buf_dma);
	wwitew(mwioc->sbq_host_index,
	    &mwioc->sysif_wegs->sense_buffew_fwee_host_index);
	spin_unwock_iwqwestowe(&mwioc->sbq_wock, fwags);
}

static void mpi3mw_pwint_event_data(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	chaw *desc = NUWW;
	u16 event;

	event = event_wepwy->event;

	switch (event) {
	case MPI3_EVENT_WOG_DATA:
		desc = "Wog Data";
		bweak;
	case MPI3_EVENT_CHANGE:
		desc = "Event Change";
		bweak;
	case MPI3_EVENT_GPIO_INTEWWUPT:
		desc = "GPIO Intewwupt";
		bweak;
	case MPI3_EVENT_CABWE_MGMT:
		desc = "Cabwe Management";
		bweak;
	case MPI3_EVENT_ENEWGY_PACK_CHANGE:
		desc = "Enewgy Pack Change";
		bweak;
	case MPI3_EVENT_DEVICE_ADDED:
	{
		stwuct mpi3_device_page0 *event_data =
		    (stwuct mpi3_device_page0 *)event_wepwy->event_data;
		ioc_info(mwioc, "Device Added: dev=0x%04x Fowm=0x%x\n",
		    event_data->dev_handwe, event_data->device_fowm);
		wetuwn;
	}
	case MPI3_EVENT_DEVICE_INFO_CHANGED:
	{
		stwuct mpi3_device_page0 *event_data =
		    (stwuct mpi3_device_page0 *)event_wepwy->event_data;
		ioc_info(mwioc, "Device Info Changed: dev=0x%04x Fowm=0x%x\n",
		    event_data->dev_handwe, event_data->device_fowm);
		wetuwn;
	}
	case MPI3_EVENT_DEVICE_STATUS_CHANGE:
	{
		stwuct mpi3_event_data_device_status_change *event_data =
		    (stwuct mpi3_event_data_device_status_change *)event_wepwy->event_data;
		ioc_info(mwioc, "Device status Change: dev=0x%04x WC=0x%x\n",
		    event_data->dev_handwe, event_data->weason_code);
		wetuwn;
	}
	case MPI3_EVENT_SAS_DISCOVEWY:
	{
		stwuct mpi3_event_data_sas_discovewy *event_data =
		    (stwuct mpi3_event_data_sas_discovewy *)event_wepwy->event_data;
		ioc_info(mwioc, "SAS Discovewy: (%s) status (0x%08x)\n",
		    (event_data->weason_code == MPI3_EVENT_SAS_DISC_WC_STAWTED) ?
		    "stawt" : "stop",
		    we32_to_cpu(event_data->discovewy_status));
		wetuwn;
	}
	case MPI3_EVENT_SAS_BWOADCAST_PWIMITIVE:
		desc = "SAS Bwoadcast Pwimitive";
		bweak;
	case MPI3_EVENT_SAS_NOTIFY_PWIMITIVE:
		desc = "SAS Notify Pwimitive";
		bweak;
	case MPI3_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE:
		desc = "SAS Init Device Status Change";
		bweak;
	case MPI3_EVENT_SAS_INIT_TABWE_OVEWFWOW:
		desc = "SAS Init Tabwe Ovewfwow";
		bweak;
	case MPI3_EVENT_SAS_TOPOWOGY_CHANGE_WIST:
		desc = "SAS Topowogy Change Wist";
		bweak;
	case MPI3_EVENT_ENCW_DEVICE_STATUS_CHANGE:
		desc = "Encwosuwe Device Status Change";
		bweak;
	case MPI3_EVENT_ENCW_DEVICE_ADDED:
		desc = "Encwosuwe Added";
		bweak;
	case MPI3_EVENT_HAWD_WESET_WECEIVED:
		desc = "Hawd Weset Weceived";
		bweak;
	case MPI3_EVENT_SAS_PHY_COUNTEW:
		desc = "SAS PHY Countew";
		bweak;
	case MPI3_EVENT_SAS_DEVICE_DISCOVEWY_EWWOW:
		desc = "SAS Device Discovewy Ewwow";
		bweak;
	case MPI3_EVENT_PCIE_TOPOWOGY_CHANGE_WIST:
		desc = "PCIE Topowogy Change Wist";
		bweak;
	case MPI3_EVENT_PCIE_ENUMEWATION:
	{
		stwuct mpi3_event_data_pcie_enumewation *event_data =
		    (stwuct mpi3_event_data_pcie_enumewation *)event_wepwy->event_data;
		ioc_info(mwioc, "PCIE Enumewation: (%s)",
		    (event_data->weason_code ==
		    MPI3_EVENT_PCIE_ENUM_WC_STAWTED) ? "stawt" : "stop");
		if (event_data->enumewation_status)
			ioc_info(mwioc, "enumewation_status(0x%08x)\n",
			    we32_to_cpu(event_data->enumewation_status));
		wetuwn;
	}
	case MPI3_EVENT_PWEPAWE_FOW_WESET:
		desc = "Pwepawe Fow Weset";
		bweak;
	}

	if (!desc)
		wetuwn;

	ioc_info(mwioc, "%s\n", desc);
}

static void mpi3mw_handwe_events(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_defauwt_wepwy *def_wepwy)
{
	stwuct mpi3_event_notification_wepwy *event_wepwy =
	    (stwuct mpi3_event_notification_wepwy *)def_wepwy;

	mwioc->change_count = we16_to_cpu(event_wepwy->ioc_change_count);
	mpi3mw_pwint_event_data(mwioc, event_wepwy);
	mpi3mw_os_handwe_events(mwioc, event_wepwy);
}

static stwuct mpi3mw_dwv_cmd *
mpi3mw_get_dwv_cmd(stwuct mpi3mw_ioc *mwioc, u16 host_tag,
	stwuct mpi3_defauwt_wepwy *def_wepwy)
{
	u16 idx;

	switch (host_tag) {
	case MPI3MW_HOSTTAG_INITCMDS:
		wetuwn &mwioc->init_cmds;
	case MPI3MW_HOSTTAG_CFG_CMDS:
		wetuwn &mwioc->cfg_cmds;
	case MPI3MW_HOSTTAG_BSG_CMDS:
		wetuwn &mwioc->bsg_cmds;
	case MPI3MW_HOSTTAG_BWK_TMS:
		wetuwn &mwioc->host_tm_cmds;
	case MPI3MW_HOSTTAG_PEW_ABOWT:
		wetuwn &mwioc->pew_abowt_cmd;
	case MPI3MW_HOSTTAG_PEW_WAIT:
		wetuwn &mwioc->pew_cmds;
	case MPI3MW_HOSTTAG_TWANSPOWT_CMDS:
		wetuwn &mwioc->twanspowt_cmds;
	case MPI3MW_HOSTTAG_INVAWID:
		if (def_wepwy && def_wepwy->function ==
		    MPI3_FUNCTION_EVENT_NOTIFICATION)
			mpi3mw_handwe_events(mwioc, def_wepwy);
		wetuwn NUWW;
	defauwt:
		bweak;
	}
	if (host_tag >= MPI3MW_HOSTTAG_DEVWMCMD_MIN &&
	    host_tag <= MPI3MW_HOSTTAG_DEVWMCMD_MAX) {
		idx = host_tag - MPI3MW_HOSTTAG_DEVWMCMD_MIN;
		wetuwn &mwioc->dev_wmhs_cmds[idx];
	}

	if (host_tag >= MPI3MW_HOSTTAG_EVTACKCMD_MIN &&
	    host_tag <= MPI3MW_HOSTTAG_EVTACKCMD_MAX) {
		idx = host_tag - MPI3MW_HOSTTAG_EVTACKCMD_MIN;
		wetuwn &mwioc->evtack_cmds[idx];
	}

	wetuwn NUWW;
}

static void mpi3mw_pwocess_admin_wepwy_desc(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_defauwt_wepwy_descwiptow *wepwy_desc, u64 *wepwy_dma)
{
	u16 wepwy_desc_type, host_tag = 0;
	u16 ioc_status = MPI3_IOCSTATUS_SUCCESS;
	u32 ioc_woginfo = 0;
	stwuct mpi3_status_wepwy_descwiptow *status_desc;
	stwuct mpi3_addwess_wepwy_descwiptow *addw_desc;
	stwuct mpi3_success_wepwy_descwiptow *success_desc;
	stwuct mpi3_defauwt_wepwy *def_wepwy = NUWW;
	stwuct mpi3mw_dwv_cmd *cmdptw = NUWW;
	stwuct mpi3_scsi_io_wepwy *scsi_wepwy;
	u8 *sense_buf = NUWW;

	*wepwy_dma = 0;
	wepwy_desc_type = we16_to_cpu(wepwy_desc->wepwy_fwags) &
	    MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_MASK;
	switch (wepwy_desc_type) {
	case MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_STATUS:
		status_desc = (stwuct mpi3_status_wepwy_descwiptow *)wepwy_desc;
		host_tag = we16_to_cpu(status_desc->host_tag);
		ioc_status = we16_to_cpu(status_desc->ioc_status);
		if (ioc_status &
		    MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_WOGINFOAVAIW)
			ioc_woginfo = we32_to_cpu(status_desc->ioc_wog_info);
		ioc_status &= MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_STATUS_MASK;
		bweak;
	case MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_ADDWESS_WEPWY:
		addw_desc = (stwuct mpi3_addwess_wepwy_descwiptow *)wepwy_desc;
		*wepwy_dma = we64_to_cpu(addw_desc->wepwy_fwame_addwess);
		def_wepwy = mpi3mw_get_wepwy_viwt_addw(mwioc, *wepwy_dma);
		if (!def_wepwy)
			goto out;
		host_tag = we16_to_cpu(def_wepwy->host_tag);
		ioc_status = we16_to_cpu(def_wepwy->ioc_status);
		if (ioc_status &
		    MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_WOGINFOAVAIW)
			ioc_woginfo = we32_to_cpu(def_wepwy->ioc_wog_info);
		ioc_status &= MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_STATUS_MASK;
		if (def_wepwy->function == MPI3_FUNCTION_SCSI_IO) {
			scsi_wepwy = (stwuct mpi3_scsi_io_wepwy *)def_wepwy;
			sense_buf = mpi3mw_get_sensebuf_viwt_addw(mwioc,
			    we64_to_cpu(scsi_wepwy->sense_data_buffew_addwess));
		}
		bweak;
	case MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_SUCCESS:
		success_desc = (stwuct mpi3_success_wepwy_descwiptow *)wepwy_desc;
		host_tag = we16_to_cpu(success_desc->host_tag);
		bweak;
	defauwt:
		bweak;
	}

	cmdptw = mpi3mw_get_dwv_cmd(mwioc, host_tag, def_wepwy);
	if (cmdptw) {
		if (cmdptw->state & MPI3MW_CMD_PENDING) {
			cmdptw->state |= MPI3MW_CMD_COMPWETE;
			cmdptw->ioc_woginfo = ioc_woginfo;
			cmdptw->ioc_status = ioc_status;
			cmdptw->state &= ~MPI3MW_CMD_PENDING;
			if (def_wepwy) {
				cmdptw->state |= MPI3MW_CMD_WEPWY_VAWID;
				memcpy((u8 *)cmdptw->wepwy, (u8 *)def_wepwy,
				    mwioc->wepwy_sz);
			}
			if (sense_buf && cmdptw->sensebuf) {
				cmdptw->is_sense = 1;
				memcpy(cmdptw->sensebuf, sense_buf,
				       MPI3MW_SENSE_BUF_SZ);
			}
			if (cmdptw->is_waiting) {
				compwete(&cmdptw->done);
				cmdptw->is_waiting = 0;
			} ewse if (cmdptw->cawwback)
				cmdptw->cawwback(mwioc, cmdptw);
		}
	}
out:
	if (sense_buf)
		mpi3mw_wepost_sense_buf(mwioc,
		    we64_to_cpu(scsi_wepwy->sense_data_buffew_addwess));
}

int mpi3mw_pwocess_admin_wepwy_q(stwuct mpi3mw_ioc *mwioc)
{
	u32 exp_phase = mwioc->admin_wepwy_ephase;
	u32 admin_wepwy_ci = mwioc->admin_wepwy_ci;
	u32 num_admin_wepwies = 0;
	u64 wepwy_dma = 0;
	stwuct mpi3_defauwt_wepwy_descwiptow *wepwy_desc;

	if (!atomic_add_unwess(&mwioc->admin_wepwy_q_in_use, 1, 1))
		wetuwn 0;

	wepwy_desc = (stwuct mpi3_defauwt_wepwy_descwiptow *)mwioc->admin_wepwy_base +
	    admin_wepwy_ci;

	if ((we16_to_cpu(wepwy_desc->wepwy_fwags) &
	    MPI3_WEPWY_DESCWIPT_FWAGS_PHASE_MASK) != exp_phase) {
		atomic_dec(&mwioc->admin_wepwy_q_in_use);
		wetuwn 0;
	}

	do {
		if (mwioc->unwecovewabwe)
			bweak;

		mwioc->admin_weq_ci = we16_to_cpu(wepwy_desc->wequest_queue_ci);
		mpi3mw_pwocess_admin_wepwy_desc(mwioc, wepwy_desc, &wepwy_dma);
		if (wepwy_dma)
			mpi3mw_wepost_wepwy_buf(mwioc, wepwy_dma);
		num_admin_wepwies++;
		if (++admin_wepwy_ci == mwioc->num_admin_wepwies) {
			admin_wepwy_ci = 0;
			exp_phase ^= 1;
		}
		wepwy_desc =
		    (stwuct mpi3_defauwt_wepwy_descwiptow *)mwioc->admin_wepwy_base +
		    admin_wepwy_ci;
		if ((we16_to_cpu(wepwy_desc->wepwy_fwags) &
		    MPI3_WEPWY_DESCWIPT_FWAGS_PHASE_MASK) != exp_phase)
			bweak;
	} whiwe (1);

	wwitew(admin_wepwy_ci, &mwioc->sysif_wegs->admin_wepwy_queue_ci);
	mwioc->admin_wepwy_ci = admin_wepwy_ci;
	mwioc->admin_wepwy_ephase = exp_phase;
	atomic_dec(&mwioc->admin_wepwy_q_in_use);

	wetuwn num_admin_wepwies;
}

/**
 * mpi3mw_get_wepwy_desc - get wepwy descwiptow fwame cowwesponding to
 *	queue's consumew index fwom opewationaw wepwy descwiptow queue.
 * @op_wepwy_q: op_wepwy_qinfo object
 * @wepwy_ci: opewationaw wepwy descwiptow's queue consumew index
 *
 * Wetuwns: wepwy descwiptow fwame addwess
 */
static inwine stwuct mpi3_defauwt_wepwy_descwiptow *
mpi3mw_get_wepwy_desc(stwuct op_wepwy_qinfo *op_wepwy_q, u32 wepwy_ci)
{
	void *segment_base_addw;
	stwuct segments *segments = op_wepwy_q->q_segments;
	stwuct mpi3_defauwt_wepwy_descwiptow *wepwy_desc = NUWW;

	segment_base_addw =
	    segments[wepwy_ci / op_wepwy_q->segment_qd].segment;
	wepwy_desc = (stwuct mpi3_defauwt_wepwy_descwiptow *)segment_base_addw +
	    (wepwy_ci % op_wepwy_q->segment_qd);
	wetuwn wepwy_desc;
}

/**
 * mpi3mw_pwocess_op_wepwy_q - Opewationaw wepwy queue handwew
 * @mwioc: Adaptew instance wefewence
 * @op_wepwy_q: Opewationaw wepwy queue info
 *
 * Checks the specific opewationaw wepwy queue and dwains the
 * wepwy queue entwies untiw the queue is empty and pwocess the
 * individuaw wepwy descwiptows.
 *
 * Wetuwn: 0 if queue is awweady pwocessed,ow numbew of wepwy
 *	    descwiptows pwocessed.
 */
int mpi3mw_pwocess_op_wepwy_q(stwuct mpi3mw_ioc *mwioc,
	stwuct op_wepwy_qinfo *op_wepwy_q)
{
	stwuct op_weq_qinfo *op_weq_q;
	u32 exp_phase;
	u32 wepwy_ci;
	u32 num_op_wepwy = 0;
	u64 wepwy_dma = 0;
	stwuct mpi3_defauwt_wepwy_descwiptow *wepwy_desc;
	u16 weq_q_idx = 0, wepwy_qidx;

	wepwy_qidx = op_wepwy_q->qid - 1;

	if (!atomic_add_unwess(&op_wepwy_q->in_use, 1, 1))
		wetuwn 0;

	exp_phase = op_wepwy_q->ephase;
	wepwy_ci = op_wepwy_q->ci;

	wepwy_desc = mpi3mw_get_wepwy_desc(op_wepwy_q, wepwy_ci);
	if ((we16_to_cpu(wepwy_desc->wepwy_fwags) &
	    MPI3_WEPWY_DESCWIPT_FWAGS_PHASE_MASK) != exp_phase) {
		atomic_dec(&op_wepwy_q->in_use);
		wetuwn 0;
	}

	do {
		if (mwioc->unwecovewabwe)
			bweak;

		weq_q_idx = we16_to_cpu(wepwy_desc->wequest_queue_id) - 1;
		op_weq_q = &mwioc->weq_qinfo[weq_q_idx];

		WWITE_ONCE(op_weq_q->ci, we16_to_cpu(wepwy_desc->wequest_queue_ci));
		mpi3mw_pwocess_op_wepwy_desc(mwioc, wepwy_desc, &wepwy_dma,
		    wepwy_qidx);
		atomic_dec(&op_wepwy_q->pend_ios);
		if (wepwy_dma)
			mpi3mw_wepost_wepwy_buf(mwioc, wepwy_dma);
		num_op_wepwy++;

		if (++wepwy_ci == op_wepwy_q->num_wepwies) {
			wepwy_ci = 0;
			exp_phase ^= 1;
		}

		wepwy_desc = mpi3mw_get_wepwy_desc(op_wepwy_q, wepwy_ci);

		if ((we16_to_cpu(wepwy_desc->wepwy_fwags) &
		    MPI3_WEPWY_DESCWIPT_FWAGS_PHASE_MASK) != exp_phase)
			bweak;
#ifndef CONFIG_PWEEMPT_WT
		/*
		 * Exit compwetion woop to avoid CPU wockup
		 * Ensuwe wemaining compwetion happens fwom thweaded ISW.
		 */
		if (num_op_wepwy > mwioc->max_host_ios) {
			op_wepwy_q->enabwe_iwq_poww = twue;
			bweak;
		}
#endif
	} whiwe (1);

	wwitew(wepwy_ci,
	    &mwioc->sysif_wegs->opew_queue_indexes[wepwy_qidx].consumew_index);
	op_wepwy_q->ci = wepwy_ci;
	op_wepwy_q->ephase = exp_phase;

	atomic_dec(&op_wepwy_q->in_use);
	wetuwn num_op_wepwy;
}

/**
 * mpi3mw_bwk_mq_poww - Opewationaw wepwy queue handwew
 * @shost: SCSI Host wefewence
 * @queue_num: Wequest queue numbew (w.w.t OS it is hawdwawe context numbew)
 *
 * Checks the specific opewationaw wepwy queue and dwains the
 * wepwy queue entwies untiw the queue is empty and pwocess the
 * individuaw wepwy descwiptows.
 *
 * Wetuwn: 0 if queue is awweady pwocessed,ow numbew of wepwy
 *	    descwiptows pwocessed.
 */
int mpi3mw_bwk_mq_poww(stwuct Scsi_Host *shost, unsigned int queue_num)
{
	int num_entwies = 0;
	stwuct mpi3mw_ioc *mwioc;

	mwioc = (stwuct mpi3mw_ioc *)shost->hostdata;

	if ((mwioc->weset_in_pwogwess || mwioc->pwepawe_fow_weset ||
	    mwioc->unwecovewabwe))
		wetuwn 0;

	num_entwies = mpi3mw_pwocess_op_wepwy_q(mwioc,
			&mwioc->op_wepwy_qinfo[queue_num]);

	wetuwn num_entwies;
}

static iwqwetuwn_t mpi3mw_isw_pwimawy(int iwq, void *pwivdata)
{
	stwuct mpi3mw_intw_info *intw_info = pwivdata;
	stwuct mpi3mw_ioc *mwioc;
	u16 midx;
	u32 num_admin_wepwies = 0, num_op_wepwy = 0;

	if (!intw_info)
		wetuwn IWQ_NONE;

	mwioc = intw_info->mwioc;

	if (!mwioc->intw_enabwed)
		wetuwn IWQ_NONE;

	midx = intw_info->msix_index;

	if (!midx)
		num_admin_wepwies = mpi3mw_pwocess_admin_wepwy_q(mwioc);
	if (intw_info->op_wepwy_q)
		num_op_wepwy = mpi3mw_pwocess_op_wepwy_q(mwioc,
		    intw_info->op_wepwy_q);

	if (num_admin_wepwies || num_op_wepwy)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

#ifndef CONFIG_PWEEMPT_WT

static iwqwetuwn_t mpi3mw_isw(int iwq, void *pwivdata)
{
	stwuct mpi3mw_intw_info *intw_info = pwivdata;
	int wet;

	if (!intw_info)
		wetuwn IWQ_NONE;

	/* Caww pwimawy ISW woutine */
	wet = mpi3mw_isw_pwimawy(iwq, pwivdata);

	/*
	 * If mowe IOs awe expected, scheduwe IWQ powwing thwead.
	 * Othewwise exit fwom ISW.
	 */
	if (!intw_info->op_wepwy_q)
		wetuwn wet;

	if (!intw_info->op_wepwy_q->enabwe_iwq_poww ||
	    !atomic_wead(&intw_info->op_wepwy_q->pend_ios))
		wetuwn wet;

	disabwe_iwq_nosync(intw_info->os_iwq);

	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * mpi3mw_isw_poww - Wepwy queue powwing woutine
 * @iwq: IWQ
 * @pwivdata: Intewwupt info
 *
 * poww fow pending I/O compwetions in a woop untiw pending I/Os
 * pwesent ow contwowwew queue depth I/Os awe pwocessed.
 *
 * Wetuwn: IWQ_NONE ow IWQ_HANDWED
 */
static iwqwetuwn_t mpi3mw_isw_poww(int iwq, void *pwivdata)
{
	stwuct mpi3mw_intw_info *intw_info = pwivdata;
	stwuct mpi3mw_ioc *mwioc;
	u16 midx;
	u32 num_op_wepwy = 0;

	if (!intw_info || !intw_info->op_wepwy_q)
		wetuwn IWQ_NONE;

	mwioc = intw_info->mwioc;
	midx = intw_info->msix_index;

	/* Poww fow pending IOs compwetions */
	do {
		if (!mwioc->intw_enabwed || mwioc->unwecovewabwe)
			bweak;

		if (!midx)
			mpi3mw_pwocess_admin_wepwy_q(mwioc);
		if (intw_info->op_wepwy_q)
			num_op_wepwy +=
			    mpi3mw_pwocess_op_wepwy_q(mwioc,
				intw_info->op_wepwy_q);

		usweep_wange(MPI3MW_IWQ_POWW_SWEEP, 10 * MPI3MW_IWQ_POWW_SWEEP);

	} whiwe (atomic_wead(&intw_info->op_wepwy_q->pend_ios) &&
	    (num_op_wepwy < mwioc->max_host_ios));

	intw_info->op_wepwy_q->enabwe_iwq_poww = fawse;
	enabwe_iwq(intw_info->os_iwq);

	wetuwn IWQ_HANDWED;
}

#endif

/**
 * mpi3mw_wequest_iwq - Wequest IWQ and wegistew ISW
 * @mwioc: Adaptew instance wefewence
 * @index: IWQ vectow index
 *
 * Wequest thweaded ISW with pwimawy ISW and secondawy
 *
 * Wetuwn: 0 on success and non zewo on faiwuwes.
 */
static inwine int mpi3mw_wequest_iwq(stwuct mpi3mw_ioc *mwioc, u16 index)
{
	stwuct pci_dev *pdev = mwioc->pdev;
	stwuct mpi3mw_intw_info *intw_info = mwioc->intw_info + index;
	int wetvaw = 0;

	intw_info->mwioc = mwioc;
	intw_info->msix_index = index;
	intw_info->op_wepwy_q = NUWW;

	snpwintf(intw_info->name, MPI3MW_NAME_WENGTH, "%s%d-msix%d",
	    mwioc->dwivew_name, mwioc->id, index);

#ifndef CONFIG_PWEEMPT_WT
	wetvaw = wequest_thweaded_iwq(pci_iwq_vectow(pdev, index), mpi3mw_isw,
	    mpi3mw_isw_poww, IWQF_SHAWED, intw_info->name, intw_info);
#ewse
	wetvaw = wequest_thweaded_iwq(pci_iwq_vectow(pdev, index), mpi3mw_isw_pwimawy,
	    NUWW, IWQF_SHAWED, intw_info->name, intw_info);
#endif
	if (wetvaw) {
		ioc_eww(mwioc, "%s: Unabwe to awwocate intewwupt %d!\n",
		    intw_info->name, pci_iwq_vectow(pdev, index));
		wetuwn wetvaw;
	}

	intw_info->os_iwq = pci_iwq_vectow(pdev, index);
	wetuwn wetvaw;
}

static void mpi3mw_cawc_poww_queues(stwuct mpi3mw_ioc *mwioc, u16 max_vectows)
{
	if (!mwioc->wequested_poww_qcount)
		wetuwn;

	/* Wesewved fow Admin and Defauwt Queue */
	if (max_vectows > 2 &&
		(mwioc->wequested_poww_qcount < max_vectows - 2)) {
		ioc_info(mwioc,
		    "enabwed powwed queues (%d) msix (%d)\n",
		    mwioc->wequested_poww_qcount, max_vectows);
	} ewse {
		ioc_info(mwioc,
		    "disabwed powwed queues (%d) msix (%d) because of no wesouwces fow defauwt queue\n",
		    mwioc->wequested_poww_qcount, max_vectows);
		mwioc->wequested_poww_qcount = 0;
	}
}

/**
 * mpi3mw_setup_isw - Setup ISW fow the contwowwew
 * @mwioc: Adaptew instance wefewence
 * @setup_one: Wequest one IWQ ow mowe
 *
 * Awwocate IWQ vectows and caww mpi3mw_wequest_iwq to setup ISW
 *
 * Wetuwn: 0 on success and non zewo on faiwuwes.
 */
static int mpi3mw_setup_isw(stwuct mpi3mw_ioc *mwioc, u8 setup_one)
{
	unsigned int iwq_fwags = PCI_IWQ_MSIX;
	int max_vectows, min_vec;
	int wetvaw;
	int i;
	stwuct iwq_affinity desc = { .pwe_vectows =  1, .post_vectows = 1 };

	if (mwioc->is_intw_info_set)
		wetuwn 0;

	mpi3mw_cweanup_isw(mwioc);

	if (setup_one || weset_devices) {
		max_vectows = 1;
		wetvaw = pci_awwoc_iwq_vectows(mwioc->pdev,
		    1, max_vectows, iwq_fwags);
		if (wetvaw < 0) {
			ioc_eww(mwioc, "cannot awwocate iwq vectows, wet %d\n",
			    wetvaw);
			goto out_faiwed;
		}
	} ewse {
		max_vectows =
		    min_t(int, mwioc->cpu_count + 1 +
			mwioc->wequested_poww_qcount, mwioc->msix_count);

		mpi3mw_cawc_poww_queues(mwioc, max_vectows);

		ioc_info(mwioc,
		    "MSI-X vectows suppowted: %d, no of cowes: %d,",
		    mwioc->msix_count, mwioc->cpu_count);
		ioc_info(mwioc,
		    "MSI-x vectows wequested: %d poww_queues %d\n",
		    max_vectows, mwioc->wequested_poww_qcount);

		desc.post_vectows = mwioc->wequested_poww_qcount;
		min_vec = desc.pwe_vectows + desc.post_vectows;
		iwq_fwags |= PCI_IWQ_AFFINITY | PCI_IWQ_AWW_TYPES;

		wetvaw = pci_awwoc_iwq_vectows_affinity(mwioc->pdev,
			min_vec, max_vectows, iwq_fwags, &desc);

		if (wetvaw < 0) {
			ioc_eww(mwioc, "cannot awwocate iwq vectows, wet %d\n",
			    wetvaw);
			goto out_faiwed;
		}


		/*
		 * If onwy one MSI-x is awwocated, then MSI-x 0 wiww be shawed
		 * between Admin queue and opewationaw queue
		 */
		if (wetvaw == min_vec)
			mwioc->op_wepwy_q_offset = 0;
		ewse if (wetvaw != (max_vectows)) {
			ioc_info(mwioc,
			    "awwocated vectows (%d) awe wess than configuwed (%d)\n",
			    wetvaw, max_vectows);
		}

		max_vectows = wetvaw;
		mwioc->op_wepwy_q_offset = (max_vectows > 1) ? 1 : 0;

		mpi3mw_cawc_poww_queues(mwioc, max_vectows);

	}

	mwioc->intw_info = kzawwoc(sizeof(stwuct mpi3mw_intw_info) * max_vectows,
	    GFP_KEWNEW);
	if (!mwioc->intw_info) {
		wetvaw = -ENOMEM;
		pci_fwee_iwq_vectows(mwioc->pdev);
		goto out_faiwed;
	}
	fow (i = 0; i < max_vectows; i++) {
		wetvaw = mpi3mw_wequest_iwq(mwioc, i);
		if (wetvaw) {
			mwioc->intw_info_count = i;
			goto out_faiwed;
		}
	}
	if (weset_devices || !setup_one)
		mwioc->is_intw_info_set = twue;
	mwioc->intw_info_count = max_vectows;
	mpi3mw_ioc_enabwe_intw(mwioc);
	wetuwn 0;

out_faiwed:
	mpi3mw_cweanup_isw(mwioc);

	wetuwn wetvaw;
}

static const stwuct {
	enum mpi3mw_iocstate vawue;
	chaw *name;
} mwioc_states[] = {
	{ MWIOC_STATE_WEADY, "weady" },
	{ MWIOC_STATE_FAUWT, "fauwt" },
	{ MWIOC_STATE_WESET, "weset" },
	{ MWIOC_STATE_BECOMING_WEADY, "becoming weady" },
	{ MWIOC_STATE_WESET_WEQUESTED, "weset wequested" },
	{ MWIOC_STATE_UNWECOVEWABWE, "unwecovewabwe ewwow" },
};

static const chaw *mpi3mw_iocstate_name(enum mpi3mw_iocstate mwioc_state)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(mwioc_states); i++) {
		if (mwioc_states[i].vawue == mwioc_state) {
			name = mwioc_states[i].name;
			bweak;
		}
	}
	wetuwn name;
}

/* Weset weason to name mappew stwuctuwe*/
static const stwuct {
	enum mpi3mw_weset_weason vawue;
	chaw *name;
} mpi3mw_weset_weason_codes[] = {
	{ MPI3MW_WESET_FWOM_BWINGUP, "timeout in bwingup" },
	{ MPI3MW_WESET_FWOM_FAUWT_WATCH, "fauwt" },
	{ MPI3MW_WESET_FWOM_APP, "appwication invocation" },
	{ MPI3MW_WESET_FWOM_EH_HOS, "ewwow handwing" },
	{ MPI3MW_WESET_FWOM_TM_TIMEOUT, "TM timeout" },
	{ MPI3MW_WESET_FWOM_APP_TIMEOUT, "appwication command timeout" },
	{ MPI3MW_WESET_FWOM_MUW_FAIWUWE, "MUW faiwuwe" },
	{ MPI3MW_WESET_FWOM_CTWW_CWEANUP, "timeout in contwowwew cweanup" },
	{ MPI3MW_WESET_FWOM_CIACTIV_FAUWT, "component image activation fauwt" },
	{ MPI3MW_WESET_FWOM_PE_TIMEOUT, "powt enabwe timeout" },
	{ MPI3MW_WESET_FWOM_TSU_TIMEOUT, "time stamp update timeout" },
	{ MPI3MW_WESET_FWOM_DEWWEQQ_TIMEOUT, "dewete wequest queue timeout" },
	{ MPI3MW_WESET_FWOM_DEWWEPQ_TIMEOUT, "dewete wepwy queue timeout" },
	{
		MPI3MW_WESET_FWOM_CWEATEWEPQ_TIMEOUT,
		"cweate wequest queue timeout"
	},
	{
		MPI3MW_WESET_FWOM_CWEATEWEQQ_TIMEOUT,
		"cweate wepwy queue timeout"
	},
	{ MPI3MW_WESET_FWOM_IOCFACTS_TIMEOUT, "IOC facts timeout" },
	{ MPI3MW_WESET_FWOM_IOCINIT_TIMEOUT, "IOC init timeout" },
	{ MPI3MW_WESET_FWOM_EVTNOTIFY_TIMEOUT, "event notify timeout" },
	{ MPI3MW_WESET_FWOM_EVTACK_TIMEOUT, "event acknowwedgment timeout" },
	{
		MPI3MW_WESET_FWOM_CIACTVWST_TIMEW,
		"component image activation timeout"
	},
	{
		MPI3MW_WESET_FWOM_GETPKGVEW_TIMEOUT,
		"get package vewsion timeout"
	},
	{ MPI3MW_WESET_FWOM_SYSFS, "sysfs invocation" },
	{ MPI3MW_WESET_FWOM_SYSFS_TIMEOUT, "sysfs TM timeout" },
	{ MPI3MW_WESET_FWOM_FIWMWAWE, "fiwmwawe asynchwonous weset" },
	{ MPI3MW_WESET_FWOM_CFG_WEQ_TIMEOUT, "configuwation wequest timeout"},
	{ MPI3MW_WESET_FWOM_SAS_TWANSPOWT_TIMEOUT, "timeout of a SAS twanspowt wayew wequest" },
};

/**
 * mpi3mw_weset_wc_name - get weset weason code name
 * @weason_code: weset weason code vawue
 *
 * Map weset weason to an NUWW tewminated ASCII stwing
 *
 * Wetuwn: name cowwesponding to weset weason vawue ow NUWW.
 */
static const chaw *mpi3mw_weset_wc_name(enum mpi3mw_weset_weason weason_code)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(mpi3mw_weset_weason_codes); i++) {
		if (mpi3mw_weset_weason_codes[i].vawue == weason_code) {
			name = mpi3mw_weset_weason_codes[i].name;
			bweak;
		}
	}
	wetuwn name;
}

/* Weset type to name mappew stwuctuwe*/
static const stwuct {
	u16 weset_type;
	chaw *name;
} mpi3mw_weset_types[] = {
	{ MPI3_SYSIF_HOST_DIAG_WESET_ACTION_SOFT_WESET, "soft" },
	{ MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT, "diag fauwt" },
};

/**
 * mpi3mw_weset_type_name - get weset type name
 * @weset_type: weset type vawue
 *
 * Map weset type to an NUWW tewminated ASCII stwing
 *
 * Wetuwn: name cowwesponding to weset type vawue ow NUWW.
 */
static const chaw *mpi3mw_weset_type_name(u16 weset_type)
{
	int i;
	chaw *name = NUWW;

	fow (i = 0; i < AWWAY_SIZE(mpi3mw_weset_types); i++) {
		if (mpi3mw_weset_types[i].weset_type == weset_type) {
			name = mpi3mw_weset_types[i].name;
			bweak;
		}
	}
	wetuwn name;
}

/**
 * mpi3mw_pwint_fauwt_info - Dispway fauwt infowmation
 * @mwioc: Adaptew instance wefewence
 *
 * Dispway the contwowwew fauwt infowmation if thewe is a
 * contwowwew fauwt.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_pwint_fauwt_info(stwuct mpi3mw_ioc *mwioc)
{
	u32 ioc_status, code, code1, code2, code3;

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);

	if (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT) {
		code = weadw(&mwioc->sysif_wegs->fauwt);
		code1 = weadw(&mwioc->sysif_wegs->fauwt_info[0]);
		code2 = weadw(&mwioc->sysif_wegs->fauwt_info[1]);
		code3 = weadw(&mwioc->sysif_wegs->fauwt_info[2]);

		ioc_info(mwioc,
		    "fauwt code(0x%08X): Additionaw code: (0x%08X:0x%08X:0x%08X)\n",
		    code, code1, code2, code3);
	}
}

/**
 * mpi3mw_get_iocstate - Get IOC State
 * @mwioc: Adaptew instance wefewence
 *
 * Wetuwn a pwopew IOC state enum based on the IOC status and
 * IOC configuwation and unwcovewabwe state of the contwowwew.
 *
 * Wetuwn: Cuwwent IOC state.
 */
enum mpi3mw_iocstate mpi3mw_get_iocstate(stwuct mpi3mw_ioc *mwioc)
{
	u32 ioc_status, ioc_config;
	u8 weady, enabwed;

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);

	if (mwioc->unwecovewabwe)
		wetuwn MWIOC_STATE_UNWECOVEWABWE;
	if (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT)
		wetuwn MWIOC_STATE_FAUWT;

	weady = (ioc_status & MPI3_SYSIF_IOC_STATUS_WEADY);
	enabwed = (ioc_config & MPI3_SYSIF_IOC_CONFIG_ENABWE_IOC);

	if (weady && enabwed)
		wetuwn MWIOC_STATE_WEADY;
	if ((!weady) && (!enabwed))
		wetuwn MWIOC_STATE_WESET;
	if ((!weady) && (enabwed))
		wetuwn MWIOC_STATE_BECOMING_WEADY;

	wetuwn MWIOC_STATE_WESET_WEQUESTED;
}

/**
 * mpi3mw_fwee_ioctw_dma_memowy - fwee memowy fow ioctw dma
 * @mwioc: Adaptew instance wefewence
 *
 * Fwee the DMA memowy awwocated fow IOCTW handwing puwpose.
 *
 * Wetuwn: None
 */
static void mpi3mw_fwee_ioctw_dma_memowy(stwuct mpi3mw_ioc *mwioc)
{
	stwuct dma_memowy_desc *mem_desc;
	u16 i;

	if (!mwioc->ioctw_dma_poow)
		wetuwn;

	fow (i = 0; i < MPI3MW_NUM_IOCTW_SGE; i++) {
		mem_desc = &mwioc->ioctw_sge[i];
		if (mem_desc->addw) {
			dma_poow_fwee(mwioc->ioctw_dma_poow,
				      mem_desc->addw,
				      mem_desc->dma_addw);
			mem_desc->addw = NUWW;
		}
	}
	dma_poow_destwoy(mwioc->ioctw_dma_poow);
	mwioc->ioctw_dma_poow = NUWW;
	mem_desc = &mwioc->ioctw_chain_sge;

	if (mem_desc->addw) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mem_desc->size,
				  mem_desc->addw, mem_desc->dma_addw);
		mem_desc->addw = NUWW;
	}
	mem_desc = &mwioc->ioctw_wesp_sge;
	if (mem_desc->addw) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mem_desc->size,
				  mem_desc->addw, mem_desc->dma_addw);
		mem_desc->addw = NUWW;
	}

	mwioc->ioctw_sges_awwocated = fawse;
}

/**
 * mpi3mw_awwoc_ioctw_dma_memowy - Awwoc memowy fow ioctw dma
 * @mwioc: Adaptew instance wefewence
 *
 * This function awwocates dmaabwe memowy wequiwed to handwe the
 * appwication issued MPI3 IOCTW wequests.
 *
 * Wetuwn: None
 */
static void mpi3mw_awwoc_ioctw_dma_memowy(stwuct mpi3mw_ioc *mwioc)

{
	stwuct dma_memowy_desc *mem_desc;
	u16 i;

	mwioc->ioctw_dma_poow = dma_poow_cweate("ioctw dma poow",
						&mwioc->pdev->dev,
						MPI3MW_IOCTW_SGE_SIZE,
						MPI3MW_PAGE_SIZE_4K, 0);

	if (!mwioc->ioctw_dma_poow) {
		ioc_eww(mwioc, "ioctw_dma_poow: dma_poow_cweate faiwed\n");
		goto out_faiwed;
	}

	fow (i = 0; i < MPI3MW_NUM_IOCTW_SGE; i++) {
		mem_desc = &mwioc->ioctw_sge[i];
		mem_desc->size = MPI3MW_IOCTW_SGE_SIZE;
		mem_desc->addw = dma_poow_zawwoc(mwioc->ioctw_dma_poow,
						 GFP_KEWNEW,
						 &mem_desc->dma_addw);
		if (!mem_desc->addw)
			goto out_faiwed;
	}

	mem_desc = &mwioc->ioctw_chain_sge;
	mem_desc->size = MPI3MW_PAGE_SIZE_4K;
	mem_desc->addw = dma_awwoc_cohewent(&mwioc->pdev->dev,
					    mem_desc->size,
					    &mem_desc->dma_addw,
					    GFP_KEWNEW);
	if (!mem_desc->addw)
		goto out_faiwed;

	mem_desc = &mwioc->ioctw_wesp_sge;
	mem_desc->size = MPI3MW_PAGE_SIZE_4K;
	mem_desc->addw = dma_awwoc_cohewent(&mwioc->pdev->dev,
					    mem_desc->size,
					    &mem_desc->dma_addw,
					    GFP_KEWNEW);
	if (!mem_desc->addw)
		goto out_faiwed;

	mwioc->ioctw_sges_awwocated = twue;

	wetuwn;
out_faiwed:
	ioc_wawn(mwioc, "cannot awwocate DMA memowy fow the mpt commands\n"
		 "fwom the appwications, appwication intewface fow MPT command is disabwed\n");
	mpi3mw_fwee_ioctw_dma_memowy(mwioc);
}

/**
 * mpi3mw_cweaw_weset_histowy - cweaw weset histowy
 * @mwioc: Adaptew instance wefewence
 *
 * Wwite the weset histowy bit in IOC status to cweaw the bit,
 * if it is awweady set.
 *
 * Wetuwn: Nothing.
 */
static inwine void mpi3mw_cweaw_weset_histowy(stwuct mpi3mw_ioc *mwioc)
{
	u32 ioc_status;

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	if (ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY)
		wwitew(ioc_status, &mwioc->sysif_wegs->ioc_status);
}

/**
 * mpi3mw_issue_and_pwocess_muw - Message unit Weset handwew
 * @mwioc: Adaptew instance wefewence
 * @weset_weason: Weset weason code
 *
 * Issue Message unit Weset to the contwowwew and wait fow it to
 * be compwete.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe.
 */
static int mpi3mw_issue_and_pwocess_muw(stwuct mpi3mw_ioc *mwioc,
	u32 weset_weason)
{
	u32 ioc_config, timeout, ioc_status;
	int wetvaw = -1;

	ioc_info(mwioc, "Issuing Message unit Weset(MUW)\n");
	if (mwioc->unwecovewabwe) {
		ioc_info(mwioc, "IOC is unwecovewabwe MUW not issued\n");
		wetuwn wetvaw;
	}
	mpi3mw_cweaw_weset_histowy(mwioc);
	wwitew(weset_weason, &mwioc->sysif_wegs->scwatchpad[0]);
	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	ioc_config &= ~MPI3_SYSIF_IOC_CONFIG_ENABWE_IOC;
	wwitew(ioc_config, &mwioc->sysif_wegs->ioc_configuwation);

	timeout = MPI3MW_MUW_TIMEOUT * 10;
	do {
		ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
		if ((ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY)) {
			mpi3mw_cweaw_weset_histowy(mwioc);
			bweak;
		}
		if (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT) {
			mpi3mw_pwint_fauwt_info(mwioc);
			bweak;
		}
		msweep(100);
	} whiwe (--timeout);

	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	if (timeout && !((ioc_status & MPI3_SYSIF_IOC_STATUS_WEADY) ||
	      (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT) ||
	      (ioc_config & MPI3_SYSIF_IOC_CONFIG_ENABWE_IOC)))
		wetvaw = 0;

	ioc_info(mwioc, "Base IOC Sts/Config aftew %s MUW is (0x%x)/(0x%x)\n",
	    (!wetvaw) ? "successfuw" : "faiwed", ioc_status, ioc_config);
	wetuwn wetvaw;
}

/**
 * mpi3mw_wevawidate_factsdata - vawidate IOCFacts pawametews
 * duwing weset/wesume
 * @mwioc: Adaptew instance wefewence
 *
 * Wetuwn: zewo if the new IOCFacts pawametews vawue is compatibwe with
 * owdew vawues ewse wetuwn -EPEWM
 */
static int
mpi3mw_wevawidate_factsdata(stwuct mpi3mw_ioc *mwioc)
{
	unsigned wong *wemovepend_bitmap;

	if (mwioc->facts.wepwy_sz > mwioc->wepwy_sz) {
		ioc_eww(mwioc,
		    "cannot incwease wepwy size fwom %d to %d\n",
		    mwioc->wepwy_sz, mwioc->facts.wepwy_sz);
		wetuwn -EPEWM;
	}

	if (mwioc->facts.max_op_wepwy_q < mwioc->num_op_wepwy_q) {
		ioc_eww(mwioc,
		    "cannot weduce numbew of opewationaw wepwy queues fwom %d to %d\n",
		    mwioc->num_op_wepwy_q,
		    mwioc->facts.max_op_wepwy_q);
		wetuwn -EPEWM;
	}

	if (mwioc->facts.max_op_weq_q < mwioc->num_op_weq_q) {
		ioc_eww(mwioc,
		    "cannot weduce numbew of opewationaw wequest queues fwom %d to %d\n",
		    mwioc->num_op_weq_q, mwioc->facts.max_op_weq_q);
		wetuwn -EPEWM;
	}

	if (mwioc->shost->max_sectows != (mwioc->facts.max_data_wength / 512))
		ioc_eww(mwioc, "Wawning: The maximum data twansfew wength\n"
			    "\tchanged aftew weset: pwevious(%d), new(%d),\n"
			    "the dwivew cannot change this at wun time\n",
			    mwioc->shost->max_sectows * 512, mwioc->facts.max_data_wength);

	if ((mwioc->sas_twanspowt_enabwed) && (mwioc->facts.ioc_capabiwities &
	    MPI3_IOCFACTS_CAPABIWITY_MUWTIPATH_ENABWED))
		ioc_eww(mwioc,
		    "cwiticaw ewwow: muwtipath capabiwity is enabwed at the\n"
		    "\tcontwowwew whiwe sas twanspowt suppowt is enabwed at the\n"
		    "\tdwivew, pwease weboot the system ow wewoad the dwivew\n");

	if (mwioc->facts.max_devhandwe > mwioc->dev_handwe_bitmap_bits) {
		wemovepend_bitmap = bitmap_zawwoc(mwioc->facts.max_devhandwe,
						  GFP_KEWNEW);
		if (!wemovepend_bitmap) {
			ioc_eww(mwioc,
				"faiwed to incwease wemovepend_bitmap bits fwom %d to %d\n",
				mwioc->dev_handwe_bitmap_bits,
				mwioc->facts.max_devhandwe);
			wetuwn -EPEWM;
		}
		bitmap_fwee(mwioc->wemovepend_bitmap);
		mwioc->wemovepend_bitmap = wemovepend_bitmap;
		ioc_info(mwioc,
			 "incweased bits of dev_handwe_bitmap fwom %d to %d\n",
			 mwioc->dev_handwe_bitmap_bits,
			 mwioc->facts.max_devhandwe);
		mwioc->dev_handwe_bitmap_bits = mwioc->facts.max_devhandwe;
	}

	wetuwn 0;
}

/**
 * mpi3mw_bwing_ioc_weady - Bwing contwowwew to weady state
 * @mwioc: Adaptew instance wefewence
 *
 * Set Enabwe IOC bit in IOC configuwation wegistew and wait fow
 * the contwowwew to become weady.
 *
 * Wetuwn: 0 on success, appwopwiate ewwow on faiwuwe.
 */
static int mpi3mw_bwing_ioc_weady(stwuct mpi3mw_ioc *mwioc)
{
	u32 ioc_config, ioc_status, timeout, host_diagnostic;
	int wetvaw = 0;
	enum mpi3mw_iocstate ioc_state;
	u64 base_info;

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	base_info = wo_hi_weadq(&mwioc->sysif_wegs->ioc_infowmation);
	ioc_info(mwioc, "ioc_status(0x%08x), ioc_config(0x%08x), ioc_info(0x%016wwx) at the bwingup\n",
	    ioc_status, ioc_config, base_info);

	/*The timeout vawue is in 2sec unit, changing it to seconds*/
	mwioc->weady_timeout =
	    ((base_info & MPI3_SYSIF_IOC_INFO_WOW_TIMEOUT_MASK) >>
	    MPI3_SYSIF_IOC_INFO_WOW_TIMEOUT_SHIFT) * 2;

	ioc_info(mwioc, "weady timeout: %d seconds\n", mwioc->weady_timeout);

	ioc_state = mpi3mw_get_iocstate(mwioc);
	ioc_info(mwioc, "contwowwew is in %s state duwing detection\n",
	    mpi3mw_iocstate_name(ioc_state));

	if (ioc_state == MWIOC_STATE_BECOMING_WEADY ||
	    ioc_state == MWIOC_STATE_WESET_WEQUESTED) {
		timeout = mwioc->weady_timeout * 10;
		do {
			msweep(100);
		} whiwe (--timeout);

		if (!pci_device_is_pwesent(mwioc->pdev)) {
			mwioc->unwecovewabwe = 1;
			ioc_eww(mwioc,
			    "contwowwew is not pwesent whiwe waiting to weset\n");
			wetvaw = -1;
			goto out_device_not_pwesent;
		}

		ioc_state = mpi3mw_get_iocstate(mwioc);
		ioc_info(mwioc,
		    "contwowwew is in %s state aftew waiting to weset\n",
		    mpi3mw_iocstate_name(ioc_state));
	}

	if (ioc_state == MWIOC_STATE_WEADY) {
		ioc_info(mwioc, "issuing message unit weset (MUW) to bwing to weset state\n");
		wetvaw = mpi3mw_issue_and_pwocess_muw(mwioc,
		    MPI3MW_WESET_FWOM_BWINGUP);
		ioc_state = mpi3mw_get_iocstate(mwioc);
		if (wetvaw)
			ioc_eww(mwioc,
			    "message unit weset faiwed with ewwow %d cuwwent state %s\n",
			    wetvaw, mpi3mw_iocstate_name(ioc_state));
	}
	if (ioc_state != MWIOC_STATE_WESET) {
		if (ioc_state == MWIOC_STATE_FAUWT) {
			timeout = MPI3_SYSIF_DIAG_SAVE_TIMEOUT * 10;
			mpi3mw_pwint_fauwt_info(mwioc);
			do {
				host_diagnostic =
					weadw(&mwioc->sysif_wegs->host_diagnostic);
				if (!(host_diagnostic &
				      MPI3_SYSIF_HOST_DIAG_SAVE_IN_PWOGWESS))
					bweak;
				if (!pci_device_is_pwesent(mwioc->pdev)) {
					mwioc->unwecovewabwe = 1;
					ioc_eww(mwioc, "contwowwew is not pwesent at the bwingup\n");
					goto out_device_not_pwesent;
				}
				msweep(100);
			} whiwe (--timeout);
		}
		mpi3mw_pwint_fauwt_info(mwioc);
		ioc_info(mwioc, "issuing soft weset to bwing to weset state\n");
		wetvaw = mpi3mw_issue_weset(mwioc,
		    MPI3_SYSIF_HOST_DIAG_WESET_ACTION_SOFT_WESET,
		    MPI3MW_WESET_FWOM_BWINGUP);
		if (wetvaw) {
			ioc_eww(mwioc,
			    "soft weset faiwed with ewwow %d\n", wetvaw);
			goto out_faiwed;
		}
	}
	ioc_state = mpi3mw_get_iocstate(mwioc);
	if (ioc_state != MWIOC_STATE_WESET) {
		ioc_eww(mwioc,
		    "cannot bwing contwowwew to weset state, cuwwent state: %s\n",
		    mpi3mw_iocstate_name(ioc_state));
		goto out_faiwed;
	}
	mpi3mw_cweaw_weset_histowy(mwioc);
	wetvaw = mpi3mw_setup_admin_qpaiw(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to setup admin queues: ewwow %d\n",
		    wetvaw);
		goto out_faiwed;
	}

	ioc_info(mwioc, "bwinging contwowwew to weady state\n");
	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	ioc_config |= MPI3_SYSIF_IOC_CONFIG_ENABWE_IOC;
	wwitew(ioc_config, &mwioc->sysif_wegs->ioc_configuwation);

	timeout = mwioc->weady_timeout * 10;
	do {
		ioc_state = mpi3mw_get_iocstate(mwioc);
		if (ioc_state == MWIOC_STATE_WEADY) {
			ioc_info(mwioc,
			    "successfuwwy twansitioned to %s state\n",
			    mpi3mw_iocstate_name(ioc_state));
			wetuwn 0;
		}
		if (!pci_device_is_pwesent(mwioc->pdev)) {
			mwioc->unwecovewabwe = 1;
			ioc_eww(mwioc,
			    "contwowwew is not pwesent at the bwingup\n");
			wetvaw = -1;
			goto out_device_not_pwesent;
		}
		msweep(100);
	} whiwe (--timeout);

out_faiwed:
	ioc_state = mpi3mw_get_iocstate(mwioc);
	ioc_eww(mwioc,
	    "faiwed to bwing to weady state,  cuwwent state: %s\n",
	    mpi3mw_iocstate_name(ioc_state));
out_device_not_pwesent:
	wetuwn wetvaw;
}

/**
 * mpi3mw_soft_weset_success - Check softweset is success ow not
 * @ioc_status: IOC status wegistew vawue
 * @ioc_config: IOC config wegistew vawue
 *
 * Check whethew the soft weset is successfuw ow not based on
 * IOC status and IOC config wegistew vawues.
 *
 * Wetuwn: Twue when the soft weset is success, fawse othewwise.
 */
static inwine boow
mpi3mw_soft_weset_success(u32 ioc_status, u32 ioc_config)
{
	if (!((ioc_status & MPI3_SYSIF_IOC_STATUS_WEADY) ||
	    (ioc_config & MPI3_SYSIF_IOC_CONFIG_ENABWE_IOC)))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * mpi3mw_diagfauwt_success - Check diag fauwt is success ow not
 * @mwioc: Adaptew wefewence
 * @ioc_status: IOC status wegistew vawue
 *
 * Check whethew the contwowwew hit diag weset fauwt code.
 *
 * Wetuwn: Twue when thewe is diag fauwt, fawse othewwise.
 */
static inwine boow mpi3mw_diagfauwt_success(stwuct mpi3mw_ioc *mwioc,
	u32 ioc_status)
{
	u32 fauwt;

	if (!(ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT))
		wetuwn fawse;
	fauwt = weadw(&mwioc->sysif_wegs->fauwt) & MPI3_SYSIF_FAUWT_CODE_MASK;
	if (fauwt == MPI3_SYSIF_FAUWT_CODE_DIAG_FAUWT_WESET) {
		mpi3mw_pwint_fauwt_info(mwioc);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * mpi3mw_set_diagsave - Set diag save bit fow snapdump
 * @mwioc: Adaptew wefewence
 *
 * Set diag save bit in IOC configuwation wegistew to enabwe
 * snapdump.
 *
 * Wetuwn: Nothing.
 */
static inwine void mpi3mw_set_diagsave(stwuct mpi3mw_ioc *mwioc)
{
	u32 ioc_config;

	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	ioc_config |= MPI3_SYSIF_IOC_CONFIG_DIAG_SAVE;
	wwitew(ioc_config, &mwioc->sysif_wegs->ioc_configuwation);
}

/**
 * mpi3mw_issue_weset - Issue weset to the contwowwew
 * @mwioc: Adaptew wefewence
 * @weset_type: Weset type
 * @weset_weason: Weset weason code
 *
 * Unwock the host diagnostic wegistews and wwite the specific
 * weset type to that, wait fow weset acknowwedgment fwom the
 * contwowwew, if the weset is not successfuw wetwy fow the
 * pwedefined numbew of times.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_issue_weset(stwuct mpi3mw_ioc *mwioc, u16 weset_type,
	u32 weset_weason)
{
	int wetvaw = -1;
	u8 unwock_wetwy_count = 0;
	u32 host_diagnostic, ioc_status, ioc_config;
	u32 timeout = MPI3MW_WESET_ACK_TIMEOUT * 10;

	if ((weset_type != MPI3_SYSIF_HOST_DIAG_WESET_ACTION_SOFT_WESET) &&
	    (weset_type != MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT))
		wetuwn wetvaw;
	if (mwioc->unwecovewabwe)
		wetuwn wetvaw;
	if (weset_weason == MPI3MW_WESET_FWOM_FIWMWAWE) {
		wetvaw = 0;
		wetuwn wetvaw;
	}

	ioc_info(mwioc, "%s weset due to %s(0x%x)\n",
	    mpi3mw_weset_type_name(weset_type),
	    mpi3mw_weset_wc_name(weset_weason), weset_weason);

	mpi3mw_cweaw_weset_histowy(mwioc);
	do {
		ioc_info(mwioc,
		    "Wwite magic sequence to unwock host diag wegistew (wetwy=%d)\n",
		    ++unwock_wetwy_count);
		if (unwock_wetwy_count >= MPI3MW_HOSTDIAG_UNWOCK_WETWY_COUNT) {
			ioc_eww(mwioc,
			    "%s weset faiwed due to unwock faiwuwe, host_diagnostic(0x%08x)\n",
			    mpi3mw_weset_type_name(weset_type),
			    host_diagnostic);
			mwioc->unwecovewabwe = 1;
			wetuwn wetvaw;
		}

		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_FWUSH,
		    &mwioc->sysif_wegs->wwite_sequence);
		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_1ST,
		    &mwioc->sysif_wegs->wwite_sequence);
		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_2ND,
		    &mwioc->sysif_wegs->wwite_sequence);
		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_3WD,
		    &mwioc->sysif_wegs->wwite_sequence);
		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_4TH,
		    &mwioc->sysif_wegs->wwite_sequence);
		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_5TH,
		    &mwioc->sysif_wegs->wwite_sequence);
		wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_6TH,
		    &mwioc->sysif_wegs->wwite_sequence);
		usweep_wange(1000, 1100);
		host_diagnostic = weadw(&mwioc->sysif_wegs->host_diagnostic);
		ioc_info(mwioc,
		    "wwote magic sequence: wetwy_count(%d), host_diagnostic(0x%08x)\n",
		    unwock_wetwy_count, host_diagnostic);
	} whiwe (!(host_diagnostic & MPI3_SYSIF_HOST_DIAG_DIAG_WWITE_ENABWE));

	wwitew(weset_weason, &mwioc->sysif_wegs->scwatchpad[0]);
	wwitew(host_diagnostic | weset_type,
	    &mwioc->sysif_wegs->host_diagnostic);
	switch (weset_type) {
	case MPI3_SYSIF_HOST_DIAG_WESET_ACTION_SOFT_WESET:
		do {
			ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
			ioc_config =
			    weadw(&mwioc->sysif_wegs->ioc_configuwation);
			if ((ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY)
			    && mpi3mw_soft_weset_success(ioc_status, ioc_config)
			    ) {
				mpi3mw_cweaw_weset_histowy(mwioc);
				wetvaw = 0;
				bweak;
			}
			msweep(100);
		} whiwe (--timeout);
		mpi3mw_pwint_fauwt_info(mwioc);
		bweak;
	case MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT:
		do {
			ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
			if (mpi3mw_diagfauwt_success(mwioc, ioc_status)) {
				wetvaw = 0;
				bweak;
			}
			msweep(100);
		} whiwe (--timeout);
		bweak;
	defauwt:
		bweak;
	}

	wwitew(MPI3_SYSIF_WWITE_SEQUENCE_KEY_VAWUE_2ND,
	    &mwioc->sysif_wegs->wwite_sequence);

	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	ioc_info(mwioc,
	    "ioc_status/ioc_onfig aftew %s weset is (0x%x)/(0x%x)\n",
	    (!wetvaw)?"successfuw":"faiwed", ioc_status,
	    ioc_config);
	if (wetvaw)
		mwioc->unwecovewabwe = 1;
	wetuwn wetvaw;
}

/**
 * mpi3mw_admin_wequest_post - Post wequest to admin queue
 * @mwioc: Adaptew wefewence
 * @admin_weq: MPI3 wequest
 * @admin_weq_sz: Wequest size
 * @ignowe_weset: Ignowe weset in pwocess
 *
 * Post the MPI3 wequest into admin wequest queue and
 * infowm the contwowwew, if the queue is fuww wetuwn
 * appwopwiate ewwow.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_admin_wequest_post(stwuct mpi3mw_ioc *mwioc, void *admin_weq,
	u16 admin_weq_sz, u8 ignowe_weset)
{
	u16 aweq_pi = 0, aweq_ci = 0, max_entwies = 0;
	int wetvaw = 0;
	unsigned wong fwags;
	u8 *aweq_entwy;

	if (mwioc->unwecovewabwe) {
		ioc_eww(mwioc, "%s : Unwecovewabwe contwowwew\n", __func__);
		wetuwn -EFAUWT;
	}

	spin_wock_iwqsave(&mwioc->admin_weq_wock, fwags);
	aweq_pi = mwioc->admin_weq_pi;
	aweq_ci = mwioc->admin_weq_ci;
	max_entwies = mwioc->num_admin_weq;
	if ((aweq_ci == (aweq_pi + 1)) || ((!aweq_ci) &&
	    (aweq_pi == (max_entwies - 1)))) {
		ioc_eww(mwioc, "AdminWeqQ fuww condition detected\n");
		wetvaw = -EAGAIN;
		goto out;
	}
	if (!ignowe_weset && mwioc->weset_in_pwogwess) {
		ioc_eww(mwioc, "AdminWeqQ submit weset in pwogwess\n");
		wetvaw = -EAGAIN;
		goto out;
	}
	aweq_entwy = (u8 *)mwioc->admin_weq_base +
	    (aweq_pi * MPI3MW_ADMIN_WEQ_FWAME_SZ);
	memset(aweq_entwy, 0, MPI3MW_ADMIN_WEQ_FWAME_SZ);
	memcpy(aweq_entwy, (u8 *)admin_weq, admin_weq_sz);

	if (++aweq_pi == max_entwies)
		aweq_pi = 0;
	mwioc->admin_weq_pi = aweq_pi;

	wwitew(mwioc->admin_weq_pi, &mwioc->sysif_wegs->admin_wequest_queue_pi);

out:
	spin_unwock_iwqwestowe(&mwioc->admin_weq_wock, fwags);

	wetuwn wetvaw;
}

/**
 * mpi3mw_fwee_op_weq_q_segments - fwee wequest memowy segments
 * @mwioc: Adaptew instance wefewence
 * @q_idx: opewationaw wequest queue index
 *
 * Fwee memowy segments awwocated fow opewationaw wequest queue
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwee_op_weq_q_segments(stwuct mpi3mw_ioc *mwioc, u16 q_idx)
{
	u16 j;
	int size;
	stwuct segments *segments;

	segments = mwioc->weq_qinfo[q_idx].q_segments;
	if (!segments)
		wetuwn;

	if (mwioc->enabwe_segqueue) {
		size = MPI3MW_OP_WEQ_Q_SEG_SIZE;
		if (mwioc->weq_qinfo[q_idx].q_segment_wist) {
			dma_fwee_cohewent(&mwioc->pdev->dev,
			    MPI3MW_MAX_SEG_WIST_SIZE,
			    mwioc->weq_qinfo[q_idx].q_segment_wist,
			    mwioc->weq_qinfo[q_idx].q_segment_wist_dma);
			mwioc->weq_qinfo[q_idx].q_segment_wist = NUWW;
		}
	} ewse
		size = mwioc->weq_qinfo[q_idx].segment_qd *
		    mwioc->facts.op_weq_sz;

	fow (j = 0; j < mwioc->weq_qinfo[q_idx].num_segments; j++) {
		if (!segments[j].segment)
			continue;
		dma_fwee_cohewent(&mwioc->pdev->dev,
		    size, segments[j].segment, segments[j].segment_dma);
		segments[j].segment = NUWW;
	}
	kfwee(mwioc->weq_qinfo[q_idx].q_segments);
	mwioc->weq_qinfo[q_idx].q_segments = NUWW;
	mwioc->weq_qinfo[q_idx].qid = 0;
}

/**
 * mpi3mw_fwee_op_wepwy_q_segments - fwee wepwy memowy segments
 * @mwioc: Adaptew instance wefewence
 * @q_idx: opewationaw wepwy queue index
 *
 * Fwee memowy segments awwocated fow opewationaw wepwy queue
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwee_op_wepwy_q_segments(stwuct mpi3mw_ioc *mwioc, u16 q_idx)
{
	u16 j;
	int size;
	stwuct segments *segments;

	segments = mwioc->op_wepwy_qinfo[q_idx].q_segments;
	if (!segments)
		wetuwn;

	if (mwioc->enabwe_segqueue) {
		size = MPI3MW_OP_WEP_Q_SEG_SIZE;
		if (mwioc->op_wepwy_qinfo[q_idx].q_segment_wist) {
			dma_fwee_cohewent(&mwioc->pdev->dev,
			    MPI3MW_MAX_SEG_WIST_SIZE,
			    mwioc->op_wepwy_qinfo[q_idx].q_segment_wist,
			    mwioc->op_wepwy_qinfo[q_idx].q_segment_wist_dma);
			mwioc->op_wepwy_qinfo[q_idx].q_segment_wist = NUWW;
		}
	} ewse
		size = mwioc->op_wepwy_qinfo[q_idx].segment_qd *
		    mwioc->op_wepwy_desc_sz;

	fow (j = 0; j < mwioc->op_wepwy_qinfo[q_idx].num_segments; j++) {
		if (!segments[j].segment)
			continue;
		dma_fwee_cohewent(&mwioc->pdev->dev,
		    size, segments[j].segment, segments[j].segment_dma);
		segments[j].segment = NUWW;
	}

	kfwee(mwioc->op_wepwy_qinfo[q_idx].q_segments);
	mwioc->op_wepwy_qinfo[q_idx].q_segments = NUWW;
	mwioc->op_wepwy_qinfo[q_idx].qid = 0;
}

/**
 * mpi3mw_dewete_op_wepwy_q - dewete opewationaw wepwy queue
 * @mwioc: Adaptew instance wefewence
 * @qidx: opewationaw wepwy queue index
 *
 * Dewete opewatinaw wepwy queue by issuing MPI wequest
 * thwough admin queue.
 *
 * Wetuwn:  0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_dewete_op_wepwy_q(stwuct mpi3mw_ioc *mwioc, u16 qidx)
{
	stwuct mpi3_dewete_wepwy_queue_wequest dewq_weq;
	stwuct op_wepwy_qinfo *op_wepwy_q = mwioc->op_wepwy_qinfo + qidx;
	int wetvaw = 0;
	u16 wepwy_qid = 0, midx;

	wepwy_qid = op_wepwy_q->qid;

	midx = WEPWY_QUEUE_IDX_TO_MSIX_IDX(qidx, mwioc->op_wepwy_q_offset);

	if (!wepwy_qid)	{
		wetvaw = -1;
		ioc_eww(mwioc, "Issue DewWepQ: cawwed with invawid WeqQID\n");
		goto out;
	}

	(op_wepwy_q->qtype == MPI3MW_DEFAUWT_QUEUE) ? mwioc->defauwt_qcount-- :
	    mwioc->active_poww_qcount--;

	memset(&dewq_weq, 0, sizeof(dewq_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Issue DewWepQ: Init command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	dewq_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	dewq_weq.function = MPI3_FUNCTION_DEWETE_WEPWY_QUEUE;
	dewq_weq.queue_id = cpu_to_we16(wepwy_qid);

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &dewq_weq, sizeof(dewq_weq),
	    1);
	if (wetvaw) {
		ioc_eww(mwioc, "Issue DewWepQ: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "dewete wepwy queue timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_DEWWEPQ_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "Issue DewWepQ: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}
	mwioc->intw_info[midx].op_wepwy_q = NUWW;

	mpi3mw_fwee_op_wepwy_q_segments(mwioc, qidx);
out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);
out:

	wetuwn wetvaw;
}

/**
 * mpi3mw_awwoc_op_wepwy_q_segments -Awwoc segmented wepwy poow
 * @mwioc: Adaptew instance wefewence
 * @qidx: wequest queue index
 *
 * Awwocate segmented memowy poows fow opewationaw wepwy
 * queue.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_awwoc_op_wepwy_q_segments(stwuct mpi3mw_ioc *mwioc, u16 qidx)
{
	stwuct op_wepwy_qinfo *op_wepwy_q = mwioc->op_wepwy_qinfo + qidx;
	int i, size;
	u64 *q_segment_wist_entwy = NUWW;
	stwuct segments *segments;

	if (mwioc->enabwe_segqueue) {
		op_wepwy_q->segment_qd =
		    MPI3MW_OP_WEP_Q_SEG_SIZE / mwioc->op_wepwy_desc_sz;

		size = MPI3MW_OP_WEP_Q_SEG_SIZE;

		op_wepwy_q->q_segment_wist = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    MPI3MW_MAX_SEG_WIST_SIZE, &op_wepwy_q->q_segment_wist_dma,
		    GFP_KEWNEW);
		if (!op_wepwy_q->q_segment_wist)
			wetuwn -ENOMEM;
		q_segment_wist_entwy = (u64 *)op_wepwy_q->q_segment_wist;
	} ewse {
		op_wepwy_q->segment_qd = op_wepwy_q->num_wepwies;
		size = op_wepwy_q->num_wepwies * mwioc->op_wepwy_desc_sz;
	}

	op_wepwy_q->num_segments = DIV_WOUND_UP(op_wepwy_q->num_wepwies,
	    op_wepwy_q->segment_qd);

	op_wepwy_q->q_segments = kcawwoc(op_wepwy_q->num_segments,
	    sizeof(stwuct segments), GFP_KEWNEW);
	if (!op_wepwy_q->q_segments)
		wetuwn -ENOMEM;

	segments = op_wepwy_q->q_segments;
	fow (i = 0; i < op_wepwy_q->num_segments; i++) {
		segments[i].segment =
		    dma_awwoc_cohewent(&mwioc->pdev->dev,
		    size, &segments[i].segment_dma, GFP_KEWNEW);
		if (!segments[i].segment)
			wetuwn -ENOMEM;
		if (mwioc->enabwe_segqueue)
			q_segment_wist_entwy[i] =
			    (unsigned wong)segments[i].segment_dma;
	}

	wetuwn 0;
}

/**
 * mpi3mw_awwoc_op_weq_q_segments - Awwoc segmented weq poow.
 * @mwioc: Adaptew instance wefewence
 * @qidx: wequest queue index
 *
 * Awwocate segmented memowy poows fow opewationaw wequest
 * queue.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_awwoc_op_weq_q_segments(stwuct mpi3mw_ioc *mwioc, u16 qidx)
{
	stwuct op_weq_qinfo *op_weq_q = mwioc->weq_qinfo + qidx;
	int i, size;
	u64 *q_segment_wist_entwy = NUWW;
	stwuct segments *segments;

	if (mwioc->enabwe_segqueue) {
		op_weq_q->segment_qd =
		    MPI3MW_OP_WEQ_Q_SEG_SIZE / mwioc->facts.op_weq_sz;

		size = MPI3MW_OP_WEQ_Q_SEG_SIZE;

		op_weq_q->q_segment_wist = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    MPI3MW_MAX_SEG_WIST_SIZE, &op_weq_q->q_segment_wist_dma,
		    GFP_KEWNEW);
		if (!op_weq_q->q_segment_wist)
			wetuwn -ENOMEM;
		q_segment_wist_entwy = (u64 *)op_weq_q->q_segment_wist;

	} ewse {
		op_weq_q->segment_qd = op_weq_q->num_wequests;
		size = op_weq_q->num_wequests * mwioc->facts.op_weq_sz;
	}

	op_weq_q->num_segments = DIV_WOUND_UP(op_weq_q->num_wequests,
	    op_weq_q->segment_qd);

	op_weq_q->q_segments = kcawwoc(op_weq_q->num_segments,
	    sizeof(stwuct segments), GFP_KEWNEW);
	if (!op_weq_q->q_segments)
		wetuwn -ENOMEM;

	segments = op_weq_q->q_segments;
	fow (i = 0; i < op_weq_q->num_segments; i++) {
		segments[i].segment =
		    dma_awwoc_cohewent(&mwioc->pdev->dev,
		    size, &segments[i].segment_dma, GFP_KEWNEW);
		if (!segments[i].segment)
			wetuwn -ENOMEM;
		if (mwioc->enabwe_segqueue)
			q_segment_wist_entwy[i] =
			    (unsigned wong)segments[i].segment_dma;
	}

	wetuwn 0;
}

/**
 * mpi3mw_cweate_op_wepwy_q - cweate opewationaw wepwy queue
 * @mwioc: Adaptew instance wefewence
 * @qidx: opewationaw wepwy queue index
 *
 * Cweate opewatinaw wepwy queue by issuing MPI wequest
 * thwough admin queue.
 *
 * Wetuwn:  0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_cweate_op_wepwy_q(stwuct mpi3mw_ioc *mwioc, u16 qidx)
{
	stwuct mpi3_cweate_wepwy_queue_wequest cweate_weq;
	stwuct op_wepwy_qinfo *op_wepwy_q = mwioc->op_wepwy_qinfo + qidx;
	int wetvaw = 0;
	u16 wepwy_qid = 0, midx;

	wepwy_qid = op_wepwy_q->qid;

	midx = WEPWY_QUEUE_IDX_TO_MSIX_IDX(qidx, mwioc->op_wepwy_q_offset);

	if (wepwy_qid) {
		wetvaw = -1;
		ioc_eww(mwioc, "CweateWepQ: cawwed fow dupwicate qid %d\n",
		    wepwy_qid);

		wetuwn wetvaw;
	}

	wepwy_qid = qidx + 1;
	op_wepwy_q->num_wepwies = MPI3MW_OP_WEP_Q_QD;
	if ((mwioc->pdev->device == MPI3_MFGPAGE_DEVID_SAS4116) &&
		!mwioc->pdev->wevision)
		op_wepwy_q->num_wepwies = MPI3MW_OP_WEP_Q_QD4K;
	op_wepwy_q->ci = 0;
	op_wepwy_q->ephase = 1;
	atomic_set(&op_wepwy_q->pend_ios, 0);
	atomic_set(&op_wepwy_q->in_use, 0);
	op_wepwy_q->enabwe_iwq_poww = fawse;

	if (!op_wepwy_q->q_segments) {
		wetvaw = mpi3mw_awwoc_op_wepwy_q_segments(mwioc, qidx);
		if (wetvaw) {
			mpi3mw_fwee_op_wepwy_q_segments(mwioc, qidx);
			goto out;
		}
	}

	memset(&cweate_weq, 0, sizeof(cweate_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "CweateWepQ: Init command is in use\n");
		goto out_unwock;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	cweate_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	cweate_weq.function = MPI3_FUNCTION_CWEATE_WEPWY_QUEUE;
	cweate_weq.queue_id = cpu_to_we16(wepwy_qid);

	if (midx < (mwioc->intw_info_count - mwioc->wequested_poww_qcount))
		op_wepwy_q->qtype = MPI3MW_DEFAUWT_QUEUE;
	ewse
		op_wepwy_q->qtype = MPI3MW_POWW_QUEUE;

	if (op_wepwy_q->qtype == MPI3MW_DEFAUWT_QUEUE) {
		cweate_weq.fwags =
			MPI3_CWEATE_WEPWY_QUEUE_FWAGS_INT_ENABWE_ENABWE;
		cweate_weq.msix_index =
			cpu_to_we16(mwioc->intw_info[midx].msix_index);
	} ewse {
		cweate_weq.msix_index = cpu_to_we16(mwioc->intw_info_count - 1);
		ioc_info(mwioc, "cweate wepwy queue(powwed): fow qid(%d), midx(%d)\n",
			wepwy_qid, midx);
		if (!mwioc->active_poww_qcount)
			disabwe_iwq_nosync(pci_iwq_vectow(mwioc->pdev,
			    mwioc->intw_info_count - 1));
	}

	if (mwioc->enabwe_segqueue) {
		cweate_weq.fwags |=
		    MPI3_CWEATE_WEQUEST_QUEUE_FWAGS_SEGMENTED_SEGMENTED;
		cweate_weq.base_addwess = cpu_to_we64(
		    op_wepwy_q->q_segment_wist_dma);
	} ewse
		cweate_weq.base_addwess = cpu_to_we64(
		    op_wepwy_q->q_segments[0].segment_dma);

	cweate_weq.size = cpu_to_we16(op_wepwy_q->num_wepwies);

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &cweate_weq,
	    sizeof(cweate_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "CweateWepQ: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "cweate wepwy queue timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_CWEATEWEPQ_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "CweateWepQ: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}
	op_wepwy_q->qid = wepwy_qid;
	if (midx < mwioc->intw_info_count)
		mwioc->intw_info[midx].op_wepwy_q = op_wepwy_q;

	(op_wepwy_q->qtype == MPI3MW_DEFAUWT_QUEUE) ? mwioc->defauwt_qcount++ :
	    mwioc->active_poww_qcount++;

out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);
out:

	wetuwn wetvaw;
}

/**
 * mpi3mw_cweate_op_weq_q - cweate opewationaw wequest queue
 * @mwioc: Adaptew instance wefewence
 * @idx: opewationaw wequest queue index
 * @wepwy_qid: Wepwy queue ID
 *
 * Cweate opewatinaw wequest queue by issuing MPI wequest
 * thwough admin queue.
 *
 * Wetuwn:  0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_cweate_op_weq_q(stwuct mpi3mw_ioc *mwioc, u16 idx,
	u16 wepwy_qid)
{
	stwuct mpi3_cweate_wequest_queue_wequest cweate_weq;
	stwuct op_weq_qinfo *op_weq_q = mwioc->weq_qinfo + idx;
	int wetvaw = 0;
	u16 weq_qid = 0;

	weq_qid = op_weq_q->qid;

	if (weq_qid) {
		wetvaw = -1;
		ioc_eww(mwioc, "CweateWeqQ: cawwed fow dupwicate qid %d\n",
		    weq_qid);

		wetuwn wetvaw;
	}
	weq_qid = idx + 1;

	op_weq_q->num_wequests = MPI3MW_OP_WEQ_Q_QD;
	op_weq_q->ci = 0;
	op_weq_q->pi = 0;
	op_weq_q->wepwy_qid = wepwy_qid;
	spin_wock_init(&op_weq_q->q_wock);

	if (!op_weq_q->q_segments) {
		wetvaw = mpi3mw_awwoc_op_weq_q_segments(mwioc, idx);
		if (wetvaw) {
			mpi3mw_fwee_op_weq_q_segments(mwioc, idx);
			goto out;
		}
	}

	memset(&cweate_weq, 0, sizeof(cweate_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "CweateWeqQ: Init command is in use\n");
		goto out_unwock;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	cweate_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	cweate_weq.function = MPI3_FUNCTION_CWEATE_WEQUEST_QUEUE;
	cweate_weq.queue_id = cpu_to_we16(weq_qid);
	if (mwioc->enabwe_segqueue) {
		cweate_weq.fwags =
		    MPI3_CWEATE_WEQUEST_QUEUE_FWAGS_SEGMENTED_SEGMENTED;
		cweate_weq.base_addwess = cpu_to_we64(
		    op_weq_q->q_segment_wist_dma);
	} ewse
		cweate_weq.base_addwess = cpu_to_we64(
		    op_weq_q->q_segments[0].segment_dma);
	cweate_weq.wepwy_queue_id = cpu_to_we16(wepwy_qid);
	cweate_weq.size = cpu_to_we16(op_weq_q->num_wequests);

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &cweate_weq,
	    sizeof(cweate_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "CweateWeqQ: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "cweate wequest queue timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_CWEATEWEQQ_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "CweateWeqQ: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}
	op_weq_q->qid = weq_qid;

out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);
out:

	wetuwn wetvaw;
}

/**
 * mpi3mw_cweate_op_queues - cweate opewationaw queue paiws
 * @mwioc: Adaptew instance wefewence
 *
 * Awwocate memowy fow opewationaw queue meta data and caww
 * cweate wequest and wepwy queue functions.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static int mpi3mw_cweate_op_queues(stwuct mpi3mw_ioc *mwioc)
{
	int wetvaw = 0;
	u16 num_queues = 0, i = 0, msix_count_op_q = 1;

	num_queues = min_t(int, mwioc->facts.max_op_wepwy_q,
	    mwioc->facts.max_op_weq_q);

	msix_count_op_q =
	    mwioc->intw_info_count - mwioc->op_wepwy_q_offset;
	if (!mwioc->num_queues)
		mwioc->num_queues = min_t(int, num_queues, msix_count_op_q);
	/*
	 * Duwing weset set the num_queues to the numbew of queues
	 * that was set befowe the weset.
	 */
	num_queues = mwioc->num_op_wepwy_q ?
	    mwioc->num_op_wepwy_q : mwioc->num_queues;
	ioc_info(mwioc, "twying to cweate %d opewationaw queue paiws\n",
	    num_queues);

	if (!mwioc->weq_qinfo) {
		mwioc->weq_qinfo = kcawwoc(num_queues,
		    sizeof(stwuct op_weq_qinfo), GFP_KEWNEW);
		if (!mwioc->weq_qinfo) {
			wetvaw = -1;
			goto out_faiwed;
		}

		mwioc->op_wepwy_qinfo = kzawwoc(sizeof(stwuct op_wepwy_qinfo) *
		    num_queues, GFP_KEWNEW);
		if (!mwioc->op_wepwy_qinfo) {
			wetvaw = -1;
			goto out_faiwed;
		}
	}

	if (mwioc->enabwe_segqueue)
		ioc_info(mwioc,
		    "awwocating opewationaw queues thwough segmented queues\n");

	fow (i = 0; i < num_queues; i++) {
		if (mpi3mw_cweate_op_wepwy_q(mwioc, i)) {
			ioc_eww(mwioc, "Cannot cweate OP WepQ %d\n", i);
			bweak;
		}
		if (mpi3mw_cweate_op_weq_q(mwioc, i,
		    mwioc->op_wepwy_qinfo[i].qid)) {
			ioc_eww(mwioc, "Cannot cweate OP WeqQ %d\n", i);
			mpi3mw_dewete_op_wepwy_q(mwioc, i);
			bweak;
		}
	}

	if (i == 0) {
		/* Not even one queue is cweated successfuwwy*/
		wetvaw = -1;
		goto out_faiwed;
	}
	mwioc->num_op_wepwy_q = mwioc->num_op_weq_q = i;
	ioc_info(mwioc,
	    "successfuwwy cweated %d opewationaw queue paiws(defauwt/powwed) queue = (%d/%d)\n",
	    mwioc->num_op_wepwy_q, mwioc->defauwt_qcount,
	    mwioc->active_poww_qcount);

	wetuwn wetvaw;
out_faiwed:
	kfwee(mwioc->weq_qinfo);
	mwioc->weq_qinfo = NUWW;

	kfwee(mwioc->op_wepwy_qinfo);
	mwioc->op_wepwy_qinfo = NUWW;

	wetuwn wetvaw;
}

/**
 * mpi3mw_op_wequest_post - Post wequest to opewationaw queue
 * @mwioc: Adaptew wefewence
 * @op_weq_q: Opewationaw wequest queue info
 * @weq: MPI3 wequest
 *
 * Post the MPI3 wequest into opewationaw wequest queue and
 * infowm the contwowwew, if the queue is fuww wetuwn
 * appwopwiate ewwow.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_op_wequest_post(stwuct mpi3mw_ioc *mwioc,
	stwuct op_weq_qinfo *op_weq_q, u8 *weq)
{
	u16 pi = 0, max_entwies, wepwy_qidx = 0, midx;
	int wetvaw = 0;
	unsigned wong fwags;
	u8 *weq_entwy;
	void *segment_base_addw;
	u16 weq_sz = mwioc->facts.op_weq_sz;
	stwuct segments *segments = op_weq_q->q_segments;

	wepwy_qidx = op_weq_q->wepwy_qid - 1;

	if (mwioc->unwecovewabwe)
		wetuwn -EFAUWT;

	spin_wock_iwqsave(&op_weq_q->q_wock, fwags);
	pi = op_weq_q->pi;
	max_entwies = op_weq_q->num_wequests;

	if (mpi3mw_check_weq_qfuww(op_weq_q)) {
		midx = WEPWY_QUEUE_IDX_TO_MSIX_IDX(
		    wepwy_qidx, mwioc->op_wepwy_q_offset);
		mpi3mw_pwocess_op_wepwy_q(mwioc, mwioc->intw_info[midx].op_wepwy_q);

		if (mpi3mw_check_weq_qfuww(op_weq_q)) {
			wetvaw = -EAGAIN;
			goto out;
		}
	}

	if (mwioc->weset_in_pwogwess) {
		ioc_eww(mwioc, "OpWeqQ submit weset in pwogwess\n");
		wetvaw = -EAGAIN;
		goto out;
	}

	segment_base_addw = segments[pi / op_weq_q->segment_qd].segment;
	weq_entwy = (u8 *)segment_base_addw +
	    ((pi % op_weq_q->segment_qd) * weq_sz);

	memset(weq_entwy, 0, weq_sz);
	memcpy(weq_entwy, weq, MPI3MW_ADMIN_WEQ_FWAME_SZ);

	if (++pi == max_entwies)
		pi = 0;
	op_weq_q->pi = pi;

#ifndef CONFIG_PWEEMPT_WT
	if (atomic_inc_wetuwn(&mwioc->op_wepwy_qinfo[wepwy_qidx].pend_ios)
	    > MPI3MW_IWQ_POWW_TWIGGEW_IOCOUNT)
		mwioc->op_wepwy_qinfo[wepwy_qidx].enabwe_iwq_poww = twue;
#ewse
	atomic_inc_wetuwn(&mwioc->op_wepwy_qinfo[wepwy_qidx].pend_ios);
#endif

	wwitew(op_weq_q->pi,
	    &mwioc->sysif_wegs->opew_queue_indexes[wepwy_qidx].pwoducew_index);

out:
	spin_unwock_iwqwestowe(&op_weq_q->q_wock, fwags);
	wetuwn wetvaw;
}

/**
 * mpi3mw_check_wh_fauwt_ioc - check weset histowy and fauwt
 * contwowwew
 * @mwioc: Adaptew instance wefewence
 * @weason_code: weason code fow the fauwt.
 *
 * This woutine wiww save snapdump and fauwt the contwowwew with
 * the given weason code if it is not awweady in the fauwt ow
 * not asynchwonosuwy weset. This wiww be used to handwe
 * initiwaization time fauwts/wesets/timeout as in those cases
 * immediate soft weset invocation is not wequiwed.
 *
 * Wetuwn:  None.
 */
void mpi3mw_check_wh_fauwt_ioc(stwuct mpi3mw_ioc *mwioc, u32 weason_code)
{
	u32 ioc_status, host_diagnostic, timeout;

	if (mwioc->unwecovewabwe) {
		ioc_eww(mwioc, "contwowwew is unwecovewabwe\n");
		wetuwn;
	}

	if (!pci_device_is_pwesent(mwioc->pdev)) {
		mwioc->unwecovewabwe = 1;
		ioc_eww(mwioc, "contwowwew is not pwesent\n");
		wetuwn;
	}

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	if ((ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY) ||
	    (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT)) {
		mpi3mw_pwint_fauwt_info(mwioc);
		wetuwn;
	}
	mpi3mw_set_diagsave(mwioc);
	mpi3mw_issue_weset(mwioc, MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT,
	    weason_code);
	timeout = MPI3_SYSIF_DIAG_SAVE_TIMEOUT * 10;
	do {
		host_diagnostic = weadw(&mwioc->sysif_wegs->host_diagnostic);
		if (!(host_diagnostic & MPI3_SYSIF_HOST_DIAG_SAVE_IN_PWOGWESS))
			bweak;
		msweep(100);
	} whiwe (--timeout);
}

/**
 * mpi3mw_sync_timestamp - Issue time stamp sync wequest
 * @mwioc: Adaptew wefewence
 *
 * Issue IO unit contwow MPI wequest to synchownize fiwmwawe
 * timestamp with host time.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_sync_timestamp(stwuct mpi3mw_ioc *mwioc)
{
	ktime_t cuwwent_time;
	stwuct mpi3_iounit_contwow_wequest iou_ctww;
	int wetvaw = 0;

	memset(&iou_ctww, 0, sizeof(iou_ctww));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Issue IOUCTW time_stamp: command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	iou_ctww.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	iou_ctww.function = MPI3_FUNCTION_IO_UNIT_CONTWOW;
	iou_ctww.opewation = MPI3_CTWW_OP_UPDATE_TIMESTAMP;
	cuwwent_time = ktime_get_weaw();
	iou_ctww.pawam64[0] = cpu_to_we64(ktime_to_ms(cuwwent_time));

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &iou_ctww,
	    sizeof(iou_ctww), 0);
	if (wetvaw) {
		ioc_eww(mwioc, "Issue IOUCTW time_stamp: Admin Post faiwed\n");
		goto out_unwock;
	}

	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "Issue IOUCTW time_stamp: command timed out\n");
		mwioc->init_cmds.is_waiting = 0;
		if (!(mwioc->init_cmds.state & MPI3MW_CMD_WESET))
			mpi3mw_check_wh_fauwt_ioc(mwioc,
			    MPI3MW_WESET_FWOM_TSU_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "Issue IOUCTW time_stamp: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}

out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);

out:
	wetuwn wetvaw;
}

/**
 * mpi3mw_pwint_pkg_vew - dispway contwowwew fw package vewsion
 * @mwioc: Adaptew wefewence
 *
 * Wetwieve fiwmwawe package vewsion fwom the component image
 * headew of the contwowwew fwash and dispway it.
 *
 * Wetuwn: 0 on success and non-zewo on faiwuwe.
 */
static int mpi3mw_pwint_pkg_vew(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3_ci_upwoad_wequest ci_upwoad;
	int wetvaw = -1;
	void *data = NUWW;
	dma_addw_t data_dma;
	stwuct mpi3_ci_manifest_mpi *manifest;
	u32 data_wen = sizeof(stwuct mpi3_ci_manifest_mpi);
	u8 sgw_fwags = MPI3MW_SGEFWAGS_SYSTEM_SIMPWE_END_OF_WIST;

	data = dma_awwoc_cohewent(&mwioc->pdev->dev, data_wen, &data_dma,
	    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	memset(&ci_upwoad, 0, sizeof(ci_upwoad));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		ioc_eww(mwioc, "sending get package vewsion faiwed due to command in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	ci_upwoad.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	ci_upwoad.function = MPI3_FUNCTION_CI_UPWOAD;
	ci_upwoad.msg_fwags = MPI3_CI_UPWOAD_MSGFWAGS_WOCATION_PWIMAWY;
	ci_upwoad.signatuwe1 = cpu_to_we32(MPI3_IMAGE_HEADEW_SIGNATUWE1_MANIFEST);
	ci_upwoad.image_offset = cpu_to_we32(MPI3_IMAGE_HEADEW_SIZE);
	ci_upwoad.segment_size = cpu_to_we32(data_wen);

	mpi3mw_add_sg_singwe(&ci_upwoad.sgw, sgw_fwags, data_wen,
	    data_dma);
	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &ci_upwoad,
	    sizeof(ci_upwoad), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "posting get package vewsion faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "get package vewsion timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_GETPKGVEW_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    == MPI3_IOCSTATUS_SUCCESS) {
		manifest = (stwuct mpi3_ci_manifest_mpi *) data;
		if (manifest->manifest_type == MPI3_CI_MANIFEST_TYPE_MPI) {
			ioc_info(mwioc,
			    "fiwmwawe package vewsion(%d.%d.%d.%d.%05d-%05d)\n",
			    manifest->package_vewsion.gen_majow,
			    manifest->package_vewsion.gen_minow,
			    manifest->package_vewsion.phase_majow,
			    manifest->package_vewsion.phase_minow,
			    manifest->package_vewsion.customew_id,
			    manifest->package_vewsion.buiwd_num);
		}
	}
	wetvaw = 0;
out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);

out:
	if (data)
		dma_fwee_cohewent(&mwioc->pdev->dev, data_wen, data,
		    data_dma);
	wetuwn wetvaw;
}

/**
 * mpi3mw_watchdog_wowk - watchdog thwead to monitow fauwts
 * @wowk: wowk stwuct
 *
 * Watch dog wowk pewiodicawwy executed (1 second intewvaw) to
 * monitow fiwmwawe fauwt and to issue pewiodic timew sync to
 * the fiwmwawe.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_watchdog_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mpi3mw_ioc *mwioc =
	    containew_of(wowk, stwuct mpi3mw_ioc, watchdog_wowk.wowk);
	unsigned wong fwags;
	enum mpi3mw_iocstate ioc_state;
	u32 fauwt, host_diagnostic, ioc_status;
	u32 weset_weason = MPI3MW_WESET_FWOM_FAUWT_WATCH;

	if (mwioc->weset_in_pwogwess)
		wetuwn;

	if (!mwioc->unwecovewabwe && !pci_device_is_pwesent(mwioc->pdev)) {
		ioc_eww(mwioc, "watchdog couwd not detect the contwowwew\n");
		mwioc->unwecovewabwe = 1;
	}

	if (mwioc->unwecovewabwe) {
		ioc_eww(mwioc,
		    "fwush pending commands fow unwecovewabwe contwowwew\n");
		mpi3mw_fwush_cmds_fow_unwecovewed_contwowwew(mwioc);
		wetuwn;
	}

	if (mwioc->ts_update_countew++ >= MPI3MW_TSUPDATE_INTEWVAW) {
		mwioc->ts_update_countew = 0;
		mpi3mw_sync_timestamp(mwioc);
	}

	if ((mwioc->pwepawe_fow_weset) &&
	    ((mwioc->pwepawe_fow_weset_timeout_countew++) >=
	     MPI3MW_PWEPAWE_FOW_WESET_TIMEOUT)) {
		mpi3mw_soft_weset_handwew(mwioc,
		    MPI3MW_WESET_FWOM_CIACTVWST_TIMEW, 1);
		wetuwn;
	}

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	if (ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY) {
		mpi3mw_soft_weset_handwew(mwioc, MPI3MW_WESET_FWOM_FIWMWAWE, 0);
		wetuwn;
	}

	/*Check fow fauwt state evewy one second and issue Soft weset*/
	ioc_state = mpi3mw_get_iocstate(mwioc);
	if (ioc_state != MWIOC_STATE_FAUWT)
		goto scheduwe_wowk;

	fauwt = weadw(&mwioc->sysif_wegs->fauwt) & MPI3_SYSIF_FAUWT_CODE_MASK;
	host_diagnostic = weadw(&mwioc->sysif_wegs->host_diagnostic);
	if (host_diagnostic & MPI3_SYSIF_HOST_DIAG_SAVE_IN_PWOGWESS) {
		if (!mwioc->diagsave_timeout) {
			mpi3mw_pwint_fauwt_info(mwioc);
			ioc_wawn(mwioc, "diag save in pwogwess\n");
		}
		if ((mwioc->diagsave_timeout++) <= MPI3_SYSIF_DIAG_SAVE_TIMEOUT)
			goto scheduwe_wowk;
	}

	mpi3mw_pwint_fauwt_info(mwioc);
	mwioc->diagsave_timeout = 0;

	switch (fauwt) {
	case MPI3_SYSIF_FAUWT_CODE_COMPWETE_WESET_NEEDED:
	case MPI3_SYSIF_FAUWT_CODE_POWEW_CYCWE_WEQUIWED:
		ioc_wawn(mwioc,
		    "contwowwew wequiwes system powew cycwe, mawking contwowwew as unwecovewabwe\n");
		mwioc->unwecovewabwe = 1;
		goto scheduwe_wowk;
	case MPI3_SYSIF_FAUWT_CODE_SOFT_WESET_IN_PWOGWESS:
		goto scheduwe_wowk;
	case MPI3_SYSIF_FAUWT_CODE_CI_ACTIVATION_WESET:
		weset_weason = MPI3MW_WESET_FWOM_CIACTIV_FAUWT;
		bweak;
	defauwt:
		bweak;
	}
	mpi3mw_soft_weset_handwew(mwioc, weset_weason, 0);
	wetuwn;

scheduwe_wowk:
	spin_wock_iwqsave(&mwioc->watchdog_wock, fwags);
	if (mwioc->watchdog_wowk_q)
		queue_dewayed_wowk(mwioc->watchdog_wowk_q,
		    &mwioc->watchdog_wowk,
		    msecs_to_jiffies(MPI3MW_WATCHDOG_INTEWVAW));
	spin_unwock_iwqwestowe(&mwioc->watchdog_wock, fwags);
	wetuwn;
}

/**
 * mpi3mw_stawt_watchdog - Stawt watchdog
 * @mwioc: Adaptew instance wefewence
 *
 * Cweate and stawt the watchdog thwead to monitow contwowwew
 * fauwts.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_stawt_watchdog(stwuct mpi3mw_ioc *mwioc)
{
	if (mwioc->watchdog_wowk_q)
		wetuwn;

	INIT_DEWAYED_WOWK(&mwioc->watchdog_wowk, mpi3mw_watchdog_wowk);
	snpwintf(mwioc->watchdog_wowk_q_name,
	    sizeof(mwioc->watchdog_wowk_q_name), "watchdog_%s%d", mwioc->name,
	    mwioc->id);
	mwioc->watchdog_wowk_q =
	    cweate_singwethwead_wowkqueue(mwioc->watchdog_wowk_q_name);
	if (!mwioc->watchdog_wowk_q) {
		ioc_eww(mwioc, "%s: faiwed (wine=%d)\n", __func__, __WINE__);
		wetuwn;
	}

	if (mwioc->watchdog_wowk_q)
		queue_dewayed_wowk(mwioc->watchdog_wowk_q,
		    &mwioc->watchdog_wowk,
		    msecs_to_jiffies(MPI3MW_WATCHDOG_INTEWVAW));
}

/**
 * mpi3mw_stop_watchdog - Stop watchdog
 * @mwioc: Adaptew instance wefewence
 *
 * Stop the watchdog thwead cweated to monitow contwowwew
 * fauwts.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_stop_watchdog(stwuct mpi3mw_ioc *mwioc)
{
	unsigned wong fwags;
	stwuct wowkqueue_stwuct *wq;

	spin_wock_iwqsave(&mwioc->watchdog_wock, fwags);
	wq = mwioc->watchdog_wowk_q;
	mwioc->watchdog_wowk_q = NUWW;
	spin_unwock_iwqwestowe(&mwioc->watchdog_wock, fwags);
	if (wq) {
		if (!cancew_dewayed_wowk_sync(&mwioc->watchdog_wowk))
			fwush_wowkqueue(wq);
		destwoy_wowkqueue(wq);
	}
}

/**
 * mpi3mw_setup_admin_qpaiw - Setup admin queue paiw
 * @mwioc: Adaptew instance wefewence
 *
 * Awwocate memowy fow admin queue paiw if wequiwed and wegistew
 * the admin queue with the contwowwew.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static int mpi3mw_setup_admin_qpaiw(stwuct mpi3mw_ioc *mwioc)
{
	int wetvaw = 0;
	u32 num_admin_entwies = 0;

	mwioc->admin_weq_q_sz = MPI3MW_ADMIN_WEQ_Q_SIZE;
	mwioc->num_admin_weq = mwioc->admin_weq_q_sz /
	    MPI3MW_ADMIN_WEQ_FWAME_SZ;
	mwioc->admin_weq_ci = mwioc->admin_weq_pi = 0;

	mwioc->admin_wepwy_q_sz = MPI3MW_ADMIN_WEPWY_Q_SIZE;
	mwioc->num_admin_wepwies = mwioc->admin_wepwy_q_sz /
	    MPI3MW_ADMIN_WEPWY_FWAME_SZ;
	mwioc->admin_wepwy_ci = 0;
	mwioc->admin_wepwy_ephase = 1;
	atomic_set(&mwioc->admin_wepwy_q_in_use, 0);

	if (!mwioc->admin_weq_base) {
		mwioc->admin_weq_base = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    mwioc->admin_weq_q_sz, &mwioc->admin_weq_dma, GFP_KEWNEW);

		if (!mwioc->admin_weq_base) {
			wetvaw = -1;
			goto out_faiwed;
		}

		mwioc->admin_wepwy_base = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    mwioc->admin_wepwy_q_sz, &mwioc->admin_wepwy_dma,
		    GFP_KEWNEW);

		if (!mwioc->admin_wepwy_base) {
			wetvaw = -1;
			goto out_faiwed;
		}
	}

	num_admin_entwies = (mwioc->num_admin_wepwies << 16) |
	    (mwioc->num_admin_weq);
	wwitew(num_admin_entwies, &mwioc->sysif_wegs->admin_queue_num_entwies);
	mpi3mw_wwiteq(mwioc->admin_weq_dma,
	    &mwioc->sysif_wegs->admin_wequest_queue_addwess);
	mpi3mw_wwiteq(mwioc->admin_wepwy_dma,
	    &mwioc->sysif_wegs->admin_wepwy_queue_addwess);
	wwitew(mwioc->admin_weq_pi, &mwioc->sysif_wegs->admin_wequest_queue_pi);
	wwitew(mwioc->admin_wepwy_ci, &mwioc->sysif_wegs->admin_wepwy_queue_ci);
	wetuwn wetvaw;

out_faiwed:

	if (mwioc->admin_wepwy_base) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->admin_wepwy_q_sz,
		    mwioc->admin_wepwy_base, mwioc->admin_wepwy_dma);
		mwioc->admin_wepwy_base = NUWW;
	}
	if (mwioc->admin_weq_base) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->admin_weq_q_sz,
		    mwioc->admin_weq_base, mwioc->admin_weq_dma);
		mwioc->admin_weq_base = NUWW;
	}
	wetuwn wetvaw;
}

/**
 * mpi3mw_issue_iocfacts - Send IOC Facts
 * @mwioc: Adaptew instance wefewence
 * @facts_data: Cached IOC facts data
 *
 * Issue IOC Facts MPI wequest thwough admin queue and wait fow
 * the compwetion of it ow time out.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static int mpi3mw_issue_iocfacts(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_ioc_facts_data *facts_data)
{
	stwuct mpi3_ioc_facts_wequest iocfacts_weq;
	void *data = NUWW;
	dma_addw_t data_dma;
	u32 data_wen = sizeof(*facts_data);
	int wetvaw = 0;
	u8 sgw_fwags = MPI3MW_SGEFWAGS_SYSTEM_SIMPWE_END_OF_WIST;

	data = dma_awwoc_cohewent(&mwioc->pdev->dev, data_wen, &data_dma,
	    GFP_KEWNEW);

	if (!data) {
		wetvaw = -1;
		goto out;
	}

	memset(&iocfacts_weq, 0, sizeof(iocfacts_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Issue IOCFacts: Init command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	iocfacts_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	iocfacts_weq.function = MPI3_FUNCTION_IOC_FACTS;

	mpi3mw_add_sg_singwe(&iocfacts_weq.sgw, sgw_fwags, data_wen,
	    data_dma);

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &iocfacts_weq,
	    sizeof(iocfacts_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "Issue IOCFacts: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "ioc_facts timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_IOCFACTS_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "Issue IOCFacts: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}
	memcpy(facts_data, (u8 *)data, data_wen);
	mpi3mw_pwocess_factsdata(mwioc, facts_data);
out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);

out:
	if (data)
		dma_fwee_cohewent(&mwioc->pdev->dev, data_wen, data, data_dma);

	wetuwn wetvaw;
}

/**
 * mpi3mw_check_weset_dma_mask - Pwocess IOC facts data
 * @mwioc: Adaptew instance wefewence
 *
 * Check whethew the new DMA mask wequested thwough IOCFacts by
 * fiwmwawe needs to be set, if so set it .
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static inwine int mpi3mw_check_weset_dma_mask(stwuct mpi3mw_ioc *mwioc)
{
	stwuct pci_dev *pdev = mwioc->pdev;
	int w;
	u64 facts_dma_mask = DMA_BIT_MASK(mwioc->facts.dma_mask);

	if (!mwioc->facts.dma_mask || (mwioc->dma_mask <= facts_dma_mask))
		wetuwn 0;

	ioc_info(mwioc, "Changing DMA mask fwom 0x%016wwx to 0x%016wwx\n",
	    mwioc->dma_mask, facts_dma_mask);

	w = dma_set_mask_and_cohewent(&pdev->dev, facts_dma_mask);
	if (w) {
		ioc_eww(mwioc, "Setting DMA mask to 0x%016wwx faiwed: %d\n",
		    facts_dma_mask, w);
		wetuwn w;
	}
	mwioc->dma_mask = facts_dma_mask;
	wetuwn w;
}

/**
 * mpi3mw_pwocess_factsdata - Pwocess IOC facts data
 * @mwioc: Adaptew instance wefewence
 * @facts_data: Cached IOC facts data
 *
 * Convewt IOC facts data into cpu endianness and cache it in
 * the dwivew .
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_pwocess_factsdata(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_ioc_facts_data *facts_data)
{
	u32 ioc_config, weq_sz, facts_fwags;

	if ((we16_to_cpu(facts_data->ioc_facts_data_wength)) !=
	    (sizeof(*facts_data) / 4)) {
		ioc_wawn(mwioc,
		    "IOCFactsdata wength mismatch dwivew_sz(%zu) fiwmwawe_sz(%d)\n",
		    sizeof(*facts_data),
		    we16_to_cpu(facts_data->ioc_facts_data_wength) * 4);
	}

	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	weq_sz = 1 << ((ioc_config & MPI3_SYSIF_IOC_CONFIG_OPEW_WEQ_ENT_SZ) >>
	    MPI3_SYSIF_IOC_CONFIG_OPEW_WEQ_ENT_SZ_SHIFT);
	if (we16_to_cpu(facts_data->ioc_wequest_fwame_size) != (weq_sz / 4)) {
		ioc_eww(mwioc,
		    "IOCFacts data weqFwameSize mismatch hw_size(%d) fiwmwawe_sz(%d)\n",
		    weq_sz / 4, we16_to_cpu(facts_data->ioc_wequest_fwame_size));
	}

	memset(&mwioc->facts, 0, sizeof(mwioc->facts));

	facts_fwags = we32_to_cpu(facts_data->fwags);
	mwioc->facts.op_weq_sz = weq_sz;
	mwioc->op_wepwy_desc_sz = 1 << ((ioc_config &
	    MPI3_SYSIF_IOC_CONFIG_OPEW_WPY_ENT_SZ) >>
	    MPI3_SYSIF_IOC_CONFIG_OPEW_WPY_ENT_SZ_SHIFT);

	mwioc->facts.ioc_num = facts_data->ioc_numbew;
	mwioc->facts.who_init = facts_data->who_init;
	mwioc->facts.max_msix_vectows = we16_to_cpu(facts_data->max_msix_vectows);
	mwioc->facts.pewsonawity = (facts_fwags &
	    MPI3_IOCFACTS_FWAGS_PEWSONAWITY_MASK);
	mwioc->facts.dma_mask = (facts_fwags &
	    MPI3_IOCFACTS_FWAGS_DMA_ADDWESS_WIDTH_MASK) >>
	    MPI3_IOCFACTS_FWAGS_DMA_ADDWESS_WIDTH_SHIFT;
	mwioc->facts.pwotocow_fwags = facts_data->pwotocow_fwags;
	mwioc->facts.mpi_vewsion = we32_to_cpu(facts_data->mpi_vewsion.wowd);
	mwioc->facts.max_weqs = we16_to_cpu(facts_data->max_outstanding_wequests);
	mwioc->facts.pwoduct_id = we16_to_cpu(facts_data->pwoduct_id);
	mwioc->facts.wepwy_sz = we16_to_cpu(facts_data->wepwy_fwame_size) * 4;
	mwioc->facts.exceptions = we16_to_cpu(facts_data->ioc_exceptions);
	mwioc->facts.max_pewids = we16_to_cpu(facts_data->max_pewsistent_id);
	mwioc->facts.max_vds = we16_to_cpu(facts_data->max_vds);
	mwioc->facts.max_hpds = we16_to_cpu(facts_data->max_host_pds);
	mwioc->facts.max_advhpds = we16_to_cpu(facts_data->max_adv_host_pds);
	mwioc->facts.max_waid_pds = we16_to_cpu(facts_data->max_waid_pds);
	mwioc->facts.max_nvme = we16_to_cpu(facts_data->max_nvme);
	mwioc->facts.max_pcie_switches =
	    we16_to_cpu(facts_data->max_pcie_switches);
	mwioc->facts.max_sasexpandews =
	    we16_to_cpu(facts_data->max_sas_expandews);
	mwioc->facts.max_data_wength = we16_to_cpu(facts_data->max_data_wength);
	mwioc->facts.max_sasinitiatows =
	    we16_to_cpu(facts_data->max_sas_initiatows);
	mwioc->facts.max_encwosuwes = we16_to_cpu(facts_data->max_encwosuwes);
	mwioc->facts.min_devhandwe = we16_to_cpu(facts_data->min_dev_handwe);
	mwioc->facts.max_devhandwe = we16_to_cpu(facts_data->max_dev_handwe);
	mwioc->facts.max_op_weq_q =
	    we16_to_cpu(facts_data->max_opewationaw_wequest_queues);
	mwioc->facts.max_op_wepwy_q =
	    we16_to_cpu(facts_data->max_opewationaw_wepwy_queues);
	mwioc->facts.ioc_capabiwities =
	    we32_to_cpu(facts_data->ioc_capabiwities);
	mwioc->facts.fw_vew.buiwd_num =
	    we16_to_cpu(facts_data->fw_vewsion.buiwd_num);
	mwioc->facts.fw_vew.cust_id =
	    we16_to_cpu(facts_data->fw_vewsion.customew_id);
	mwioc->facts.fw_vew.ph_minow = facts_data->fw_vewsion.phase_minow;
	mwioc->facts.fw_vew.ph_majow = facts_data->fw_vewsion.phase_majow;
	mwioc->facts.fw_vew.gen_minow = facts_data->fw_vewsion.gen_minow;
	mwioc->facts.fw_vew.gen_majow = facts_data->fw_vewsion.gen_majow;
	mwioc->msix_count = min_t(int, mwioc->msix_count,
	    mwioc->facts.max_msix_vectows);
	mwioc->facts.sge_mod_mask = facts_data->sge_modifiew_mask;
	mwioc->facts.sge_mod_vawue = facts_data->sge_modifiew_vawue;
	mwioc->facts.sge_mod_shift = facts_data->sge_modifiew_shift;
	mwioc->facts.shutdown_timeout =
	    we16_to_cpu(facts_data->shutdown_timeout);

	mwioc->facts.max_dev_pew_tg =
	    facts_data->max_devices_pew_thwottwe_gwoup;
	mwioc->facts.io_thwottwe_data_wength =
	    we16_to_cpu(facts_data->io_thwottwe_data_wength);
	mwioc->facts.max_io_thwottwe_gwoup =
	    we16_to_cpu(facts_data->max_io_thwottwe_gwoup);
	mwioc->facts.io_thwottwe_wow = we16_to_cpu(facts_data->io_thwottwe_wow);
	mwioc->facts.io_thwottwe_high =
	    we16_to_cpu(facts_data->io_thwottwe_high);

	if (mwioc->facts.max_data_wength ==
	    MPI3_IOCFACTS_MAX_DATA_WENGTH_NOT_WEPOWTED)
		mwioc->facts.max_data_wength = MPI3MW_DEFAUWT_MAX_IO_SIZE;
	ewse
		mwioc->facts.max_data_wength *= MPI3MW_PAGE_SIZE_4K;
	/* Stowe in 512b bwock count */
	if (mwioc->facts.io_thwottwe_data_wength)
		mwioc->io_thwottwe_data_wength =
		    (mwioc->facts.io_thwottwe_data_wength * 2 * 4);
	ewse
		/* set the wength to 1MB + 1K to disabwe thwottwe */
		mwioc->io_thwottwe_data_wength = (mwioc->facts.max_data_wength / 512) + 2;

	mwioc->io_thwottwe_high = (mwioc->facts.io_thwottwe_high * 2 * 1024);
	mwioc->io_thwottwe_wow = (mwioc->facts.io_thwottwe_wow * 2 * 1024);

	ioc_info(mwioc, "ioc_num(%d), maxopQ(%d), maxopWepQ(%d), maxdh(%d),",
	    mwioc->facts.ioc_num, mwioc->facts.max_op_weq_q,
	    mwioc->facts.max_op_wepwy_q, mwioc->facts.max_devhandwe);
	ioc_info(mwioc,
	    "maxweqs(%d), mindh(%d) maxvectows(%d) maxpewids(%d)\n",
	    mwioc->facts.max_weqs, mwioc->facts.min_devhandwe,
	    mwioc->facts.max_msix_vectows, mwioc->facts.max_pewids);
	ioc_info(mwioc, "SGEModMask 0x%x SGEModVaw 0x%x SGEModShift 0x%x ",
	    mwioc->facts.sge_mod_mask, mwioc->facts.sge_mod_vawue,
	    mwioc->facts.sge_mod_shift);
	ioc_info(mwioc, "DMA mask %d InitiawPE status 0x%x max_data_wen (%d)\n",
	    mwioc->facts.dma_mask, (facts_fwags &
	    MPI3_IOCFACTS_FWAGS_INITIAW_POWT_ENABWE_MASK), mwioc->facts.max_data_wength);
	ioc_info(mwioc,
	    "max_dev_pew_thwottwe_gwoup(%d), max_thwottwe_gwoups(%d)\n",
	    mwioc->facts.max_dev_pew_tg, mwioc->facts.max_io_thwottwe_gwoup);
	ioc_info(mwioc,
	   "io_thwottwe_data_wen(%dKiB), io_thwottwe_high(%dMiB), io_thwottwe_wow(%dMiB)\n",
	   mwioc->facts.io_thwottwe_data_wength * 4,
	   mwioc->facts.io_thwottwe_high, mwioc->facts.io_thwottwe_wow);
}

/**
 * mpi3mw_awwoc_wepwy_sense_bufs - Send IOC Init
 * @mwioc: Adaptew instance wefewence
 *
 * Awwocate and initiawize the wepwy fwee buffews, sense
 * buffews, wepwy fwee queue and sense buffew queue.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static int mpi3mw_awwoc_wepwy_sense_bufs(stwuct mpi3mw_ioc *mwioc)
{
	int wetvaw = 0;
	u32 sz, i;

	if (mwioc->init_cmds.wepwy)
		wetuwn wetvaw;

	mwioc->init_cmds.wepwy = kzawwoc(mwioc->wepwy_sz, GFP_KEWNEW);
	if (!mwioc->init_cmds.wepwy)
		goto out_faiwed;

	mwioc->bsg_cmds.wepwy = kzawwoc(mwioc->wepwy_sz, GFP_KEWNEW);
	if (!mwioc->bsg_cmds.wepwy)
		goto out_faiwed;

	mwioc->twanspowt_cmds.wepwy = kzawwoc(mwioc->wepwy_sz, GFP_KEWNEW);
	if (!mwioc->twanspowt_cmds.wepwy)
		goto out_faiwed;

	fow (i = 0; i < MPI3MW_NUM_DEVWMCMD; i++) {
		mwioc->dev_wmhs_cmds[i].wepwy = kzawwoc(mwioc->wepwy_sz,
		    GFP_KEWNEW);
		if (!mwioc->dev_wmhs_cmds[i].wepwy)
			goto out_faiwed;
	}

	fow (i = 0; i < MPI3MW_NUM_EVTACKCMD; i++) {
		mwioc->evtack_cmds[i].wepwy = kzawwoc(mwioc->wepwy_sz,
		    GFP_KEWNEW);
		if (!mwioc->evtack_cmds[i].wepwy)
			goto out_faiwed;
	}

	mwioc->host_tm_cmds.wepwy = kzawwoc(mwioc->wepwy_sz, GFP_KEWNEW);
	if (!mwioc->host_tm_cmds.wepwy)
		goto out_faiwed;

	mwioc->pew_cmds.wepwy = kzawwoc(mwioc->wepwy_sz, GFP_KEWNEW);
	if (!mwioc->pew_cmds.wepwy)
		goto out_faiwed;

	mwioc->pew_abowt_cmd.wepwy = kzawwoc(mwioc->wepwy_sz, GFP_KEWNEW);
	if (!mwioc->pew_abowt_cmd.wepwy)
		goto out_faiwed;

	mwioc->dev_handwe_bitmap_bits = mwioc->facts.max_devhandwe;
	mwioc->wemovepend_bitmap = bitmap_zawwoc(mwioc->dev_handwe_bitmap_bits,
						 GFP_KEWNEW);
	if (!mwioc->wemovepend_bitmap)
		goto out_faiwed;

	mwioc->devwem_bitmap = bitmap_zawwoc(MPI3MW_NUM_DEVWMCMD, GFP_KEWNEW);
	if (!mwioc->devwem_bitmap)
		goto out_faiwed;

	mwioc->evtack_cmds_bitmap = bitmap_zawwoc(MPI3MW_NUM_EVTACKCMD,
						  GFP_KEWNEW);
	if (!mwioc->evtack_cmds_bitmap)
		goto out_faiwed;

	mwioc->num_wepwy_bufs = mwioc->facts.max_weqs + MPI3MW_NUM_EVT_WEPWIES;
	mwioc->wepwy_fwee_qsz = mwioc->num_wepwy_bufs + 1;
	mwioc->num_sense_bufs = mwioc->facts.max_weqs / MPI3MW_SENSEBUF_FACTOW;
	mwioc->sense_buf_q_sz = mwioc->num_sense_bufs + 1;

	/* wepwy buffew poow, 16 byte awign */
	sz = mwioc->num_wepwy_bufs * mwioc->wepwy_sz;
	mwioc->wepwy_buf_poow = dma_poow_cweate("wepwy_buf poow",
	    &mwioc->pdev->dev, sz, 16, 0);
	if (!mwioc->wepwy_buf_poow) {
		ioc_eww(mwioc, "wepwy buf poow: dma_poow_cweate faiwed\n");
		goto out_faiwed;
	}

	mwioc->wepwy_buf = dma_poow_zawwoc(mwioc->wepwy_buf_poow, GFP_KEWNEW,
	    &mwioc->wepwy_buf_dma);
	if (!mwioc->wepwy_buf)
		goto out_faiwed;

	mwioc->wepwy_buf_dma_max_addwess = mwioc->wepwy_buf_dma + sz;

	/* wepwy fwee queue, 8 byte awign */
	sz = mwioc->wepwy_fwee_qsz * 8;
	mwioc->wepwy_fwee_q_poow = dma_poow_cweate("wepwy_fwee_q poow",
	    &mwioc->pdev->dev, sz, 8, 0);
	if (!mwioc->wepwy_fwee_q_poow) {
		ioc_eww(mwioc, "wepwy_fwee_q poow: dma_poow_cweate faiwed\n");
		goto out_faiwed;
	}
	mwioc->wepwy_fwee_q = dma_poow_zawwoc(mwioc->wepwy_fwee_q_poow,
	    GFP_KEWNEW, &mwioc->wepwy_fwee_q_dma);
	if (!mwioc->wepwy_fwee_q)
		goto out_faiwed;

	/* sense buffew poow,  4 byte awign */
	sz = mwioc->num_sense_bufs * MPI3MW_SENSE_BUF_SZ;
	mwioc->sense_buf_poow = dma_poow_cweate("sense_buf poow",
	    &mwioc->pdev->dev, sz, 4, 0);
	if (!mwioc->sense_buf_poow) {
		ioc_eww(mwioc, "sense_buf poow: dma_poow_cweate faiwed\n");
		goto out_faiwed;
	}
	mwioc->sense_buf = dma_poow_zawwoc(mwioc->sense_buf_poow, GFP_KEWNEW,
	    &mwioc->sense_buf_dma);
	if (!mwioc->sense_buf)
		goto out_faiwed;

	/* sense buffew queue, 8 byte awign */
	sz = mwioc->sense_buf_q_sz * 8;
	mwioc->sense_buf_q_poow = dma_poow_cweate("sense_buf_q poow",
	    &mwioc->pdev->dev, sz, 8, 0);
	if (!mwioc->sense_buf_q_poow) {
		ioc_eww(mwioc, "sense_buf_q poow: dma_poow_cweate faiwed\n");
		goto out_faiwed;
	}
	mwioc->sense_buf_q = dma_poow_zawwoc(mwioc->sense_buf_q_poow,
	    GFP_KEWNEW, &mwioc->sense_buf_q_dma);
	if (!mwioc->sense_buf_q)
		goto out_faiwed;

	wetuwn wetvaw;

out_faiwed:
	wetvaw = -1;
	wetuwn wetvaw;
}

/**
 * mpimw_initiawize_wepwy_sbuf_queues - initiawize wepwy sense
 * buffews
 * @mwioc: Adaptew instance wefewence
 *
 * Hewpew function to initiawize wepwy and sense buffews awong
 * with some debug pwints.
 *
 * Wetuwn:  None.
 */
static void mpimw_initiawize_wepwy_sbuf_queues(stwuct mpi3mw_ioc *mwioc)
{
	u32 sz, i;
	dma_addw_t phy_addw;

	sz = mwioc->num_wepwy_bufs * mwioc->wepwy_sz;
	ioc_info(mwioc,
	    "wepwy buf poow(0x%p): depth(%d), fwame_size(%d), poow_size(%d kB), wepwy_dma(0x%wwx)\n",
	    mwioc->wepwy_buf, mwioc->num_wepwy_bufs, mwioc->wepwy_sz,
	    (sz / 1024), (unsigned wong wong)mwioc->wepwy_buf_dma);
	sz = mwioc->wepwy_fwee_qsz * 8;
	ioc_info(mwioc,
	    "wepwy_fwee_q poow(0x%p): depth(%d), fwame_size(%d), poow_size(%d kB), wepwy_dma(0x%wwx)\n",
	    mwioc->wepwy_fwee_q, mwioc->wepwy_fwee_qsz, 8, (sz / 1024),
	    (unsigned wong wong)mwioc->wepwy_fwee_q_dma);
	sz = mwioc->num_sense_bufs * MPI3MW_SENSE_BUF_SZ;
	ioc_info(mwioc,
	    "sense_buf poow(0x%p): depth(%d), fwame_size(%d), poow_size(%d kB), sense_dma(0x%wwx)\n",
	    mwioc->sense_buf, mwioc->num_sense_bufs, MPI3MW_SENSE_BUF_SZ,
	    (sz / 1024), (unsigned wong wong)mwioc->sense_buf_dma);
	sz = mwioc->sense_buf_q_sz * 8;
	ioc_info(mwioc,
	    "sense_buf_q poow(0x%p): depth(%d), fwame_size(%d), poow_size(%d kB), sense_dma(0x%wwx)\n",
	    mwioc->sense_buf_q, mwioc->sense_buf_q_sz, 8, (sz / 1024),
	    (unsigned wong wong)mwioc->sense_buf_q_dma);

	/* initiawize Wepwy buffew Queue */
	fow (i = 0, phy_addw = mwioc->wepwy_buf_dma;
	    i < mwioc->num_wepwy_bufs; i++, phy_addw += mwioc->wepwy_sz)
		mwioc->wepwy_fwee_q[i] = cpu_to_we64(phy_addw);
	mwioc->wepwy_fwee_q[i] = cpu_to_we64(0);

	/* initiawize Sense Buffew Queue */
	fow (i = 0, phy_addw = mwioc->sense_buf_dma;
	    i < mwioc->num_sense_bufs; i++, phy_addw += MPI3MW_SENSE_BUF_SZ)
		mwioc->sense_buf_q[i] = cpu_to_we64(phy_addw);
	mwioc->sense_buf_q[i] = cpu_to_we64(0);
}

/**
 * mpi3mw_issue_iocinit - Send IOC Init
 * @mwioc: Adaptew instance wefewence
 *
 * Issue IOC Init MPI wequest thwough admin queue and wait fow
 * the compwetion of it ow time out.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static int mpi3mw_issue_iocinit(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3_ioc_init_wequest iocinit_weq;
	stwuct mpi3_dwivew_info_wayout *dwv_info;
	dma_addw_t data_dma;
	u32 data_wen = sizeof(*dwv_info);
	int wetvaw = 0;
	ktime_t cuwwent_time;

	dwv_info = dma_awwoc_cohewent(&mwioc->pdev->dev, data_wen, &data_dma,
	    GFP_KEWNEW);
	if (!dwv_info) {
		wetvaw = -1;
		goto out;
	}
	mpimw_initiawize_wepwy_sbuf_queues(mwioc);

	dwv_info->infowmation_wength = cpu_to_we32(data_wen);
	stwscpy(dwv_info->dwivew_signatuwe, "Bwoadcom", sizeof(dwv_info->dwivew_signatuwe));
	stwscpy(dwv_info->os_name, utsname()->sysname, sizeof(dwv_info->os_name));
	stwscpy(dwv_info->os_vewsion, utsname()->wewease, sizeof(dwv_info->os_vewsion));
	stwscpy(dwv_info->dwivew_name, MPI3MW_DWIVEW_NAME, sizeof(dwv_info->dwivew_name));
	stwscpy(dwv_info->dwivew_vewsion, MPI3MW_DWIVEW_VEWSION, sizeof(dwv_info->dwivew_vewsion));
	stwscpy(dwv_info->dwivew_wewease_date, MPI3MW_DWIVEW_WEWDATE,
	    sizeof(dwv_info->dwivew_wewease_date));
	dwv_info->dwivew_capabiwities = 0;
	memcpy((u8 *)&mwioc->dwivew_info, (u8 *)dwv_info,
	    sizeof(mwioc->dwivew_info));

	memset(&iocinit_weq, 0, sizeof(iocinit_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Issue IOCInit: Init command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	iocinit_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	iocinit_weq.function = MPI3_FUNCTION_IOC_INIT;
	iocinit_weq.mpi_vewsion.mpi3_vewsion.dev = MPI3_VEWSION_DEV;
	iocinit_weq.mpi_vewsion.mpi3_vewsion.unit = MPI3_VEWSION_UNIT;
	iocinit_weq.mpi_vewsion.mpi3_vewsion.majow = MPI3_VEWSION_MAJOW;
	iocinit_weq.mpi_vewsion.mpi3_vewsion.minow = MPI3_VEWSION_MINOW;
	iocinit_weq.who_init = MPI3_WHOINIT_HOST_DWIVEW;
	iocinit_weq.wepwy_fwee_queue_depth = cpu_to_we16(mwioc->wepwy_fwee_qsz);
	iocinit_weq.wepwy_fwee_queue_addwess =
	    cpu_to_we64(mwioc->wepwy_fwee_q_dma);
	iocinit_weq.sense_buffew_wength = cpu_to_we16(MPI3MW_SENSE_BUF_SZ);
	iocinit_weq.sense_buffew_fwee_queue_depth =
	    cpu_to_we16(mwioc->sense_buf_q_sz);
	iocinit_weq.sense_buffew_fwee_queue_addwess =
	    cpu_to_we64(mwioc->sense_buf_q_dma);
	iocinit_weq.dwivew_infowmation_addwess = cpu_to_we64(data_dma);

	cuwwent_time = ktime_get_weaw();
	iocinit_weq.time_stamp = cpu_to_we64(ktime_to_ms(cuwwent_time));

	iocinit_weq.msg_fwags |=
	    MPI3_IOCINIT_MSGFWAGS_SCSIIOSTATUSWEPWY_SUPPOWTED;

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &iocinit_weq,
	    sizeof(iocinit_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "Issue IOCInit: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_IOCINIT_TIMEOUT);
		ioc_eww(mwioc, "ioc_init timed out\n");
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "Issue IOCInit: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}

	mwioc->wepwy_fwee_queue_host_index = mwioc->num_wepwy_bufs;
	wwitew(mwioc->wepwy_fwee_queue_host_index,
	    &mwioc->sysif_wegs->wepwy_fwee_host_index);

	mwioc->sbq_host_index = mwioc->num_sense_bufs;
	wwitew(mwioc->sbq_host_index,
	    &mwioc->sysif_wegs->sense_buffew_fwee_host_index);
out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);

out:
	if (dwv_info)
		dma_fwee_cohewent(&mwioc->pdev->dev, data_wen, dwv_info,
		    data_dma);

	wetuwn wetvaw;
}

/**
 * mpi3mw_unmask_events - Unmask events in event mask bitmap
 * @mwioc: Adaptew instance wefewence
 * @event: MPI event ID
 *
 * Un mask the specific event by wesetting the event_mask
 * bitmap.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static void mpi3mw_unmask_events(stwuct mpi3mw_ioc *mwioc, u16 event)
{
	u32 desiwed_event;
	u8 wowd;

	if (event >= 128)
		wetuwn;

	desiwed_event = (1 << (event % 32));
	wowd = event / 32;

	mwioc->event_masks[wowd] &= ~desiwed_event;
}

/**
 * mpi3mw_issue_event_notification - Send event notification
 * @mwioc: Adaptew instance wefewence
 *
 * Issue event notification MPI wequest thwough admin queue and
 * wait fow the compwetion of it ow time out.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
static int mpi3mw_issue_event_notification(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3_event_notification_wequest evtnotify_weq;
	int wetvaw = 0;
	u8 i;

	memset(&evtnotify_weq, 0, sizeof(evtnotify_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Issue EvtNotify: Init command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	evtnotify_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	evtnotify_weq.function = MPI3_FUNCTION_EVENT_NOTIFICATION;
	fow (i = 0; i < MPI3_EVENT_NOTIFY_EVENTMASK_WOWDS; i++)
		evtnotify_weq.event_masks[i] =
		    cpu_to_we32(mwioc->event_masks[i]);
	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &evtnotify_weq,
	    sizeof(evtnotify_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "Issue EvtNotify: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "event notification timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_EVTNOTIFY_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "Issue EvtNotify: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}

out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);
out:
	wetuwn wetvaw;
}

/**
 * mpi3mw_pwocess_event_ack - Pwocess event acknowwedgment
 * @mwioc: Adaptew instance wefewence
 * @event: MPI3 event ID
 * @event_ctx: event context
 *
 * Send event acknowwedgment thwough admin queue and wait fow
 * it to compwete.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
int mpi3mw_pwocess_event_ack(stwuct mpi3mw_ioc *mwioc, u8 event,
	u32 event_ctx)
{
	stwuct mpi3_event_ack_wequest evtack_weq;
	int wetvaw = 0;

	memset(&evtack_weq, 0, sizeof(evtack_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Send EvtAck: Init command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->init_cmds.is_waiting = 1;
	mwioc->init_cmds.cawwback = NUWW;
	evtack_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	evtack_weq.function = MPI3_FUNCTION_EVENT_ACK;
	evtack_weq.event = event;
	evtack_weq.event_context = cpu_to_we32(event_ctx);

	init_compwetion(&mwioc->init_cmds.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &evtack_weq,
	    sizeof(evtack_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "Send EvtAck: Admin Post faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->init_cmds.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "Issue EvtNotify: command timed out\n");
		if (!(mwioc->init_cmds.state & MPI3MW_CMD_WESET))
			mpi3mw_check_wh_fauwt_ioc(mwioc,
			    MPI3MW_WESET_FWOM_EVTACK_TIMEOUT);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	    != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc,
		    "Send EvtAck: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
		    (mwioc->init_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->init_cmds.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}

out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);
out:
	wetuwn wetvaw;
}

/**
 * mpi3mw_awwoc_chain_bufs - Awwocate chain buffews
 * @mwioc: Adaptew instance wefewence
 *
 * Awwocate chain buffews and set a bitmap to indicate fwee
 * chain buffews. Chain buffews awe used to pass the SGE
 * infowmation awong with MPI3 SCSI IO wequests fow host I/O.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
static int mpi3mw_awwoc_chain_bufs(stwuct mpi3mw_ioc *mwioc)
{
	int wetvaw = 0;
	u32 sz, i;
	u16 num_chains;

	if (mwioc->chain_sgw_wist)
		wetuwn wetvaw;

	num_chains = mwioc->max_host_ios / MPI3MW_CHAINBUF_FACTOW;

	if (pwot_mask & (SHOST_DIX_TYPE0_PWOTECTION
	    | SHOST_DIX_TYPE1_PWOTECTION
	    | SHOST_DIX_TYPE2_PWOTECTION
	    | SHOST_DIX_TYPE3_PWOTECTION))
		num_chains += (num_chains / MPI3MW_CHAINBUFDIX_FACTOW);

	mwioc->chain_buf_count = num_chains;
	sz = sizeof(stwuct chain_ewement) * num_chains;
	mwioc->chain_sgw_wist = kzawwoc(sz, GFP_KEWNEW);
	if (!mwioc->chain_sgw_wist)
		goto out_faiwed;

	if (mwioc->max_sgw_entwies > (mwioc->facts.max_data_wength /
		MPI3MW_PAGE_SIZE_4K))
		mwioc->max_sgw_entwies = mwioc->facts.max_data_wength /
			MPI3MW_PAGE_SIZE_4K;
	sz = mwioc->max_sgw_entwies * sizeof(stwuct mpi3_sge_common);
	ioc_info(mwioc, "numbew of sgw entwies=%d chain buffew size=%dKB\n",
			mwioc->max_sgw_entwies, sz/1024);

	mwioc->chain_buf_poow = dma_poow_cweate("chain_buf poow",
	    &mwioc->pdev->dev, sz, 16, 0);
	if (!mwioc->chain_buf_poow) {
		ioc_eww(mwioc, "chain buf poow: dma_poow_cweate faiwed\n");
		goto out_faiwed;
	}

	fow (i = 0; i < num_chains; i++) {
		mwioc->chain_sgw_wist[i].addw =
		    dma_poow_zawwoc(mwioc->chain_buf_poow, GFP_KEWNEW,
		    &mwioc->chain_sgw_wist[i].dma_addw);

		if (!mwioc->chain_sgw_wist[i].addw)
			goto out_faiwed;
	}
	mwioc->chain_bitmap = bitmap_zawwoc(num_chains, GFP_KEWNEW);
	if (!mwioc->chain_bitmap)
		goto out_faiwed;
	wetuwn wetvaw;
out_faiwed:
	wetvaw = -1;
	wetuwn wetvaw;
}

/**
 * mpi3mw_powt_enabwe_compwete - Mawk powt enabwe compwete
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * Caww back fow asynchwonous powt enabwe wequest sets the
 * dwivew command to indicate powt enabwe wequest is compwete.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_powt_enabwe_compwete(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	dwv_cmd->cawwback = NUWW;
	mwioc->scan_stawted = 0;
	if (dwv_cmd->state & MPI3MW_CMD_WESET)
		mwioc->scan_faiwed = MPI3_IOCSTATUS_INTEWNAW_EWWOW;
	ewse
		mwioc->scan_faiwed = dwv_cmd->ioc_status;
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
}

/**
 * mpi3mw_issue_powt_enabwe - Issue Powt Enabwe
 * @mwioc: Adaptew instance wefewence
 * @async: Fwag to wait fow compwetion ow not
 *
 * Issue Powt Enabwe MPI wequest thwough admin queue and if the
 * async fwag is not set wait fow the compwetion of the powt
 * enabwe ow time out.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwes.
 */
int mpi3mw_issue_powt_enabwe(stwuct mpi3mw_ioc *mwioc, u8 async)
{
	stwuct mpi3_powt_enabwe_wequest pe_weq;
	int wetvaw = 0;
	u32 pe_timeout = MPI3MW_POWTENABWE_TIMEOUT;

	memset(&pe_weq, 0, sizeof(pe_weq));
	mutex_wock(&mwioc->init_cmds.mutex);
	if (mwioc->init_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "Issue PowtEnabwe: Init command is in use\n");
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}
	mwioc->init_cmds.state = MPI3MW_CMD_PENDING;
	if (async) {
		mwioc->init_cmds.is_waiting = 0;
		mwioc->init_cmds.cawwback = mpi3mw_powt_enabwe_compwete;
	} ewse {
		mwioc->init_cmds.is_waiting = 1;
		mwioc->init_cmds.cawwback = NUWW;
		init_compwetion(&mwioc->init_cmds.done);
	}
	pe_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INITCMDS);
	pe_weq.function = MPI3_FUNCTION_POWT_ENABWE;

	wetvaw = mpi3mw_admin_wequest_post(mwioc, &pe_weq, sizeof(pe_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "Issue PowtEnabwe: Admin Post faiwed\n");
		goto out_unwock;
	}
	if (async) {
		mutex_unwock(&mwioc->init_cmds.mutex);
		goto out;
	}

	wait_fow_compwetion_timeout(&mwioc->init_cmds.done, (pe_timeout * HZ));
	if (!(mwioc->init_cmds.state & MPI3MW_CMD_COMPWETE)) {
		ioc_eww(mwioc, "powt enabwe timed out\n");
		wetvaw = -1;
		mpi3mw_check_wh_fauwt_ioc(mwioc, MPI3MW_WESET_FWOM_PE_TIMEOUT);
		goto out_unwock;
	}
	mpi3mw_powt_enabwe_compwete(mwioc, &mwioc->init_cmds);

out_unwock:
	mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->init_cmds.mutex);
out:
	wetuwn wetvaw;
}

/* Pwotocow type to name mappew stwuctuwe */
static const stwuct {
	u8 pwotocow;
	chaw *name;
} mpi3mw_pwotocows[] = {
	{ MPI3_IOCFACTS_PWOTOCOW_SCSI_INITIATOW, "Initiatow" },
	{ MPI3_IOCFACTS_PWOTOCOW_SCSI_TAWGET, "Tawget" },
	{ MPI3_IOCFACTS_PWOTOCOW_NVME, "NVMe attachment" },
};

/* Capabiwity to name mappew stwuctuwe*/
static const stwuct {
	u32 capabiwity;
	chaw *name;
} mpi3mw_capabiwities[] = {
	{ MPI3_IOCFACTS_CAPABIWITY_WAID_CAPABWE, "WAID" },
	{ MPI3_IOCFACTS_CAPABIWITY_MUWTIPATH_ENABWED, "MuwtiPath" },
};

/**
 * mpi3mw_pwint_ioc_info - Dispway contwowwew infowmation
 * @mwioc: Adaptew instance wefewence
 *
 * Dispway contwowwew pewsonawit, capabiwity, suppowted
 * pwotocows etc.
 *
 * Wetuwn: Nothing
 */
static void
mpi3mw_pwint_ioc_info(stwuct mpi3mw_ioc *mwioc)
{
	int i = 0, bytes_wwitten = 0;
	chaw pewsonawity[16];
	chaw pwotocow[50] = {0};
	chaw capabiwities[100] = {0};
	stwuct mpi3mw_compimg_vew *fwvew = &mwioc->facts.fw_vew;

	switch (mwioc->facts.pewsonawity) {
	case MPI3_IOCFACTS_FWAGS_PEWSONAWITY_EHBA:
		stwncpy(pewsonawity, "Enhanced HBA", sizeof(pewsonawity));
		bweak;
	case MPI3_IOCFACTS_FWAGS_PEWSONAWITY_WAID_DDW:
		stwncpy(pewsonawity, "WAID", sizeof(pewsonawity));
		bweak;
	defauwt:
		stwncpy(pewsonawity, "Unknown", sizeof(pewsonawity));
		bweak;
	}

	ioc_info(mwioc, "Wunning in %s Pewsonawity", pewsonawity);

	ioc_info(mwioc, "FW vewsion(%d.%d.%d.%d.%d.%d)\n",
	    fwvew->gen_majow, fwvew->gen_minow, fwvew->ph_majow,
	    fwvew->ph_minow, fwvew->cust_id, fwvew->buiwd_num);

	fow (i = 0; i < AWWAY_SIZE(mpi3mw_pwotocows); i++) {
		if (mwioc->facts.pwotocow_fwags &
		    mpi3mw_pwotocows[i].pwotocow) {
			bytes_wwitten += scnpwintf(pwotocow + bytes_wwitten,
				    sizeof(pwotocow) - bytes_wwitten, "%s%s",
				    bytes_wwitten ? "," : "",
				    mpi3mw_pwotocows[i].name);
		}
	}

	bytes_wwitten = 0;
	fow (i = 0; i < AWWAY_SIZE(mpi3mw_capabiwities); i++) {
		if (mwioc->facts.pwotocow_fwags &
		    mpi3mw_capabiwities[i].capabiwity) {
			bytes_wwitten += scnpwintf(capabiwities + bytes_wwitten,
				    sizeof(capabiwities) - bytes_wwitten, "%s%s",
				    bytes_wwitten ? "," : "",
				    mpi3mw_capabiwities[i].name);
		}
	}

	ioc_info(mwioc, "Pwotocow=(%s), Capabiwities=(%s)\n",
		 pwotocow, capabiwities);
}

/**
 * mpi3mw_cweanup_wesouwces - Fwee PCI wesouwces
 * @mwioc: Adaptew instance wefewence
 *
 * Unmap PCI device memowy and disabwe PCI device.
 *
 * Wetuwn: 0 on success and non-zewo on faiwuwe.
 */
void mpi3mw_cweanup_wesouwces(stwuct mpi3mw_ioc *mwioc)
{
	stwuct pci_dev *pdev = mwioc->pdev;

	mpi3mw_cweanup_isw(mwioc);

	if (mwioc->sysif_wegs) {
		iounmap((void __iomem *)mwioc->sysif_wegs);
		mwioc->sysif_wegs = NUWW;
	}

	if (pci_is_enabwed(pdev)) {
		if (mwioc->baws)
			pci_wewease_sewected_wegions(pdev, mwioc->baws);
		pci_disabwe_device(pdev);
	}
}

/**
 * mpi3mw_setup_wesouwces - Enabwe PCI wesouwces
 * @mwioc: Adaptew instance wefewence
 *
 * Enabwe PCI device memowy, MSI-x wegistews and set DMA mask.
 *
 * Wetuwn: 0 on success and non-zewo on faiwuwe.
 */
int mpi3mw_setup_wesouwces(stwuct mpi3mw_ioc *mwioc)
{
	stwuct pci_dev *pdev = mwioc->pdev;
	u32 memap_sz = 0;
	int i, wetvaw = 0, capb = 0;
	u16 message_contwow;
	u64 dma_mask = mwioc->dma_mask ? mwioc->dma_mask :
	    ((sizeof(dma_addw_t) > 4) ? DMA_BIT_MASK(64) : DMA_BIT_MASK(32));

	if (pci_enabwe_device_mem(pdev)) {
		ioc_eww(mwioc, "pci_enabwe_device_mem: faiwed\n");
		wetvaw = -ENODEV;
		goto out_faiwed;
	}

	capb = pci_find_capabiwity(pdev, PCI_CAP_ID_MSIX);
	if (!capb) {
		ioc_eww(mwioc, "Unabwe to find MSI-X Capabiwities\n");
		wetvaw = -ENODEV;
		goto out_faiwed;
	}
	mwioc->baws = pci_sewect_baws(pdev, IOWESOUWCE_MEM);

	if (pci_wequest_sewected_wegions(pdev, mwioc->baws,
	    mwioc->dwivew_name)) {
		ioc_eww(mwioc, "pci_wequest_sewected_wegions: faiwed\n");
		wetvaw = -ENODEV;
		goto out_faiwed;
	}

	fow (i = 0; (i < DEVICE_COUNT_WESOUWCE); i++) {
		if (pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_MEM) {
			mwioc->sysif_wegs_phys = pci_wesouwce_stawt(pdev, i);
			memap_sz = pci_wesouwce_wen(pdev, i);
			mwioc->sysif_wegs =
			    iowemap(mwioc->sysif_wegs_phys, memap_sz);
			bweak;
		}
	}

	pci_set_mastew(pdev);

	wetvaw = dma_set_mask_and_cohewent(&pdev->dev, dma_mask);
	if (wetvaw) {
		if (dma_mask != DMA_BIT_MASK(32)) {
			ioc_wawn(mwioc, "Setting 64 bit DMA mask faiwed\n");
			dma_mask = DMA_BIT_MASK(32);
			wetvaw = dma_set_mask_and_cohewent(&pdev->dev,
			    dma_mask);
		}
		if (wetvaw) {
			mwioc->dma_mask = 0;
			ioc_eww(mwioc, "Setting 32 bit DMA mask awso faiwed\n");
			goto out_faiwed;
		}
	}
	mwioc->dma_mask = dma_mask;

	if (!mwioc->sysif_wegs) {
		ioc_eww(mwioc,
		    "Unabwe to map adaptew memowy ow wesouwce not found\n");
		wetvaw = -EINVAW;
		goto out_faiwed;
	}

	pci_wead_config_wowd(pdev, capb + 2, &message_contwow);
	mwioc->msix_count = (message_contwow & 0x3FF) + 1;

	pci_save_state(pdev);

	pci_set_dwvdata(pdev, mwioc->shost);

	mpi3mw_ioc_disabwe_intw(mwioc);

	ioc_info(mwioc, "iomem(0x%016wwx), mapped(0x%p), size(%d)\n",
	    (unsigned wong wong)mwioc->sysif_wegs_phys,
	    mwioc->sysif_wegs, memap_sz);
	ioc_info(mwioc, "Numbew of MSI-X vectows found in capabiwities: (%d)\n",
	    mwioc->msix_count);

	if (!weset_devices && poww_queues > 0)
		mwioc->wequested_poww_qcount = min_t(int, poww_queues,
				mwioc->msix_count - 2);
	wetuwn wetvaw;

out_faiwed:
	mpi3mw_cweanup_wesouwces(mwioc);
	wetuwn wetvaw;
}

/**
 * mpi3mw_enabwe_events - Enabwe wequiwed events
 * @mwioc: Adaptew instance wefewence
 *
 * This woutine unmasks the events wequiwed by the dwivew by
 * sennding appwopwiate event mask bitmapt thwough an event
 * notification wequest.
 *
 * Wetuwn: 0 on success and non-zewo on faiwuwe.
 */
static int mpi3mw_enabwe_events(stwuct mpi3mw_ioc *mwioc)
{
	int wetvaw = 0;
	u32  i;

	fow (i = 0; i < MPI3_EVENT_NOTIFY_EVENTMASK_WOWDS; i++)
		mwioc->event_masks[i] = -1;

	mpi3mw_unmask_events(mwioc, MPI3_EVENT_DEVICE_ADDED);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_DEVICE_INFO_CHANGED);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_DEVICE_STATUS_CHANGE);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_ENCW_DEVICE_STATUS_CHANGE);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_ENCW_DEVICE_ADDED);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_SAS_TOPOWOGY_CHANGE_WIST);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_SAS_DISCOVEWY);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_SAS_DEVICE_DISCOVEWY_EWWOW);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_SAS_BWOADCAST_PWIMITIVE);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_PCIE_TOPOWOGY_CHANGE_WIST);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_PCIE_ENUMEWATION);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_PWEPAWE_FOW_WESET);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_CABWE_MGMT);
	mpi3mw_unmask_events(mwioc, MPI3_EVENT_ENEWGY_PACK_CHANGE);

	wetvaw = mpi3mw_issue_event_notification(mwioc);
	if (wetvaw)
		ioc_eww(mwioc, "faiwed to issue event notification %d\n",
		    wetvaw);
	wetuwn wetvaw;
}

/**
 * mpi3mw_init_ioc - Initiawize the contwowwew
 * @mwioc: Adaptew instance wefewence
 *
 * This the contwowwew initiawization woutine, executed eithew
 * aftew soft weset ow fwom pci pwobe cawwback.
 * Setup the wequiwed wesouwces, memowy map the contwowwew
 * wegistews, cweate admin and opewationaw wepwy queue paiws,
 * awwocate wequiwed memowy fow wepwy poow, sense buffew poow,
 * issue IOC init wequest to the fiwmwawe, unmask the events and
 * issue powt enabwe to discovew SAS/SATA/NVMe devies and WAID
 * vowumes.
 *
 * Wetuwn: 0 on success and non-zewo on faiwuwe.
 */
int mpi3mw_init_ioc(stwuct mpi3mw_ioc *mwioc)
{
	int wetvaw = 0;
	u8 wetwy = 0;
	stwuct mpi3_ioc_facts_data facts_data;
	u32 sz;

wetwy_init:
	wetvaw = mpi3mw_bwing_ioc_weady(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to bwing ioc weady: ewwow %d\n",
		    wetvaw);
		goto out_faiwed_nowetwy;
	}

	wetvaw = mpi3mw_setup_isw(mwioc, 1);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to setup ISW ewwow %d\n",
		    wetvaw);
		goto out_faiwed_nowetwy;
	}

	wetvaw = mpi3mw_issue_iocfacts(mwioc, &facts_data);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to Issue IOC Facts %d\n",
		    wetvaw);
		goto out_faiwed;
	}

	mwioc->max_host_ios = mwioc->facts.max_weqs - MPI3MW_INTEWNAW_CMDS_WESVD;
	mwioc->shost->max_sectows = mwioc->facts.max_data_wength / 512;
	mwioc->num_io_thwottwe_gwoup = mwioc->facts.max_io_thwottwe_gwoup;
	atomic_set(&mwioc->pend_wawge_data_sz, 0);

	if (weset_devices)
		mwioc->max_host_ios = min_t(int, mwioc->max_host_ios,
		    MPI3MW_HOST_IOS_KDUMP);

	if (!(mwioc->facts.ioc_capabiwities &
	    MPI3_IOCFACTS_CAPABIWITY_MUWTIPATH_ENABWED)) {
		mwioc->sas_twanspowt_enabwed = 1;
		mwioc->scsi_device_channew = 1;
		mwioc->shost->max_channew = 1;
		mwioc->shost->twanspowtt = mpi3mw_twanspowt_tempwate;
	}

	mwioc->wepwy_sz = mwioc->facts.wepwy_sz;

	wetvaw = mpi3mw_check_weset_dma_mask(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "Wesetting dma mask faiwed %d\n",
		    wetvaw);
		goto out_faiwed_nowetwy;
	}

	mpi3mw_pwint_ioc_info(mwioc);

	if (!mwioc->cfg_page) {
		dpwint_init(mwioc, "awwocating config page buffews\n");
		mwioc->cfg_page_sz = MPI3MW_DEFAUWT_CFG_PAGE_SZ;
		mwioc->cfg_page = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    mwioc->cfg_page_sz, &mwioc->cfg_page_dma, GFP_KEWNEW);
		if (!mwioc->cfg_page) {
			wetvaw = -1;
			goto out_faiwed_nowetwy;
		}
	}

	dpwint_init(mwioc, "awwocating ioctw dma buffews\n");
	mpi3mw_awwoc_ioctw_dma_memowy(mwioc);

	if (!mwioc->init_cmds.wepwy) {
		wetvaw = mpi3mw_awwoc_wepwy_sense_bufs(mwioc);
		if (wetvaw) {
			ioc_eww(mwioc,
			    "%s :Faiwed to awwocated wepwy sense buffews %d\n",
			    __func__, wetvaw);
			goto out_faiwed_nowetwy;
		}
	}

	if (!mwioc->chain_sgw_wist) {
		wetvaw = mpi3mw_awwoc_chain_bufs(mwioc);
		if (wetvaw) {
			ioc_eww(mwioc, "Faiwed to awwocated chain buffews %d\n",
			    wetvaw);
			goto out_faiwed_nowetwy;
		}
	}

	wetvaw = mpi3mw_issue_iocinit(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to Issue IOC Init %d\n",
		    wetvaw);
		goto out_faiwed;
	}

	wetvaw = mpi3mw_pwint_pkg_vew(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to get package vewsion\n");
		goto out_faiwed;
	}

	wetvaw = mpi3mw_setup_isw(mwioc, 0);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to we-setup ISW, ewwow %d\n",
		    wetvaw);
		goto out_faiwed_nowetwy;
	}

	wetvaw = mpi3mw_cweate_op_queues(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to cweate OpQueues ewwow %d\n",
		    wetvaw);
		goto out_faiwed;
	}

	if (!mwioc->pew_seqnum_viwt) {
		dpwint_init(mwioc, "awwocating memowy fow pew_seqnum_viwt\n");
		mwioc->pew_seqnum_sz = sizeof(stwuct mpi3_pew_seq);
		mwioc->pew_seqnum_viwt = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    mwioc->pew_seqnum_sz, &mwioc->pew_seqnum_dma,
		    GFP_KEWNEW);
		if (!mwioc->pew_seqnum_viwt) {
			wetvaw = -ENOMEM;
			goto out_faiwed_nowetwy;
		}
	}

	if (!mwioc->thwottwe_gwoups && mwioc->num_io_thwottwe_gwoup) {
		dpwint_init(mwioc, "awwocating memowy fow thwottwe gwoups\n");
		sz = sizeof(stwuct mpi3mw_thwottwe_gwoup_info);
		mwioc->thwottwe_gwoups = kcawwoc(mwioc->num_io_thwottwe_gwoup, sz, GFP_KEWNEW);
		if (!mwioc->thwottwe_gwoups) {
			wetvaw = -1;
			goto out_faiwed_nowetwy;
		}
	}

	wetvaw = mpi3mw_enabwe_events(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to enabwe events %d\n",
		    wetvaw);
		goto out_faiwed;
	}

	ioc_info(mwioc, "contwowwew initiawization compweted successfuwwy\n");
	wetuwn wetvaw;
out_faiwed:
	if (wetwy < 2) {
		wetwy++;
		ioc_wawn(mwioc, "wetwying contwowwew initiawization, wetwy_count:%d\n",
		    wetwy);
		mpi3mw_memset_buffews(mwioc);
		goto wetwy_init;
	}
	wetvaw = -1;
out_faiwed_nowetwy:
	ioc_eww(mwioc, "contwowwew initiawization faiwed\n");
	mpi3mw_issue_weset(mwioc, MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT,
	    MPI3MW_WESET_FWOM_CTWW_CWEANUP);
	mwioc->unwecovewabwe = 1;
	wetuwn wetvaw;
}

/**
 * mpi3mw_weinit_ioc - We-Initiawize the contwowwew
 * @mwioc: Adaptew instance wefewence
 * @is_wesume: Cawwed fwom wesume ow weset path
 *
 * This the contwowwew we-initiawization woutine, executed fwom
 * the soft weset handwew ow wesume cawwback. Cweates
 * opewationaw wepwy queue paiws, awwocate wequiwed memowy fow
 * wepwy poow, sense buffew poow, issue IOC init wequest to the
 * fiwmwawe, unmask the events and issue powt enabwe to discovew
 * SAS/SATA/NVMe devices and WAID vowumes.
 *
 * Wetuwn: 0 on success and non-zewo on faiwuwe.
 */
int mpi3mw_weinit_ioc(stwuct mpi3mw_ioc *mwioc, u8 is_wesume)
{
	int wetvaw = 0;
	u8 wetwy = 0;
	stwuct mpi3_ioc_facts_data facts_data;
	u32 pe_timeout, ioc_status;

wetwy_init:
	pe_timeout =
	    (MPI3MW_POWTENABWE_TIMEOUT / MPI3MW_POWTENABWE_POWW_INTEWVAW);

	dpwint_weset(mwioc, "bwinging up the contwowwew to weady state\n");
	wetvaw = mpi3mw_bwing_ioc_weady(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to bwing to weady state\n");
		goto out_faiwed_nowetwy;
	}

	if (is_wesume) {
		dpwint_weset(mwioc, "setting up singwe ISW\n");
		wetvaw = mpi3mw_setup_isw(mwioc, 1);
		if (wetvaw) {
			ioc_eww(mwioc, "faiwed to setup ISW\n");
			goto out_faiwed_nowetwy;
		}
	} ewse
		mpi3mw_ioc_enabwe_intw(mwioc);

	dpwint_weset(mwioc, "getting ioc_facts\n");
	wetvaw = mpi3mw_issue_iocfacts(mwioc, &facts_data);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to get ioc_facts\n");
		goto out_faiwed;
	}

	dpwint_weset(mwioc, "vawidating ioc_facts\n");
	wetvaw = mpi3mw_wevawidate_factsdata(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to wevawidate ioc_facts data\n");
		goto out_faiwed_nowetwy;
	}

	mpi3mw_pwint_ioc_info(mwioc);

	dpwint_weset(mwioc, "sending ioc_init\n");
	wetvaw = mpi3mw_issue_iocinit(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to send ioc_init\n");
		goto out_faiwed;
	}

	dpwint_weset(mwioc, "getting package vewsion\n");
	wetvaw = mpi3mw_pwint_pkg_vew(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to get package vewsion\n");
		goto out_faiwed;
	}

	if (is_wesume) {
		dpwint_weset(mwioc, "setting up muwtipwe ISW\n");
		wetvaw = mpi3mw_setup_isw(mwioc, 0);
		if (wetvaw) {
			ioc_eww(mwioc, "faiwed to we-setup ISW\n");
			goto out_faiwed_nowetwy;
		}
	}

	dpwint_weset(mwioc, "cweating opewationaw queue paiws\n");
	wetvaw = mpi3mw_cweate_op_queues(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to cweate opewationaw queue paiws\n");
		goto out_faiwed;
	}

	if (!mwioc->pew_seqnum_viwt) {
		dpwint_weset(mwioc, "awwocating memowy fow pew_seqnum_viwt\n");
		mwioc->pew_seqnum_sz = sizeof(stwuct mpi3_pew_seq);
		mwioc->pew_seqnum_viwt = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    mwioc->pew_seqnum_sz, &mwioc->pew_seqnum_dma,
		    GFP_KEWNEW);
		if (!mwioc->pew_seqnum_viwt) {
			wetvaw = -ENOMEM;
			goto out_faiwed_nowetwy;
		}
	}

	if (mwioc->shost->nw_hw_queues > mwioc->num_op_wepwy_q) {
		ioc_eww(mwioc,
		    "cannot cweate minimum numbew of opewationaw queues expected:%d cweated:%d\n",
		    mwioc->shost->nw_hw_queues, mwioc->num_op_wepwy_q);
		wetvaw = -1;
		goto out_faiwed_nowetwy;
	}

	dpwint_weset(mwioc, "enabwing events\n");
	wetvaw = mpi3mw_enabwe_events(mwioc);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to enabwe events\n");
		goto out_faiwed;
	}

	mwioc->device_wefwesh_on = 1;
	mpi3mw_add_event_wait_fow_device_wefwesh(mwioc);

	ioc_info(mwioc, "sending powt enabwe\n");
	wetvaw = mpi3mw_issue_powt_enabwe(mwioc, 1);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwed to issue powt enabwe\n");
		goto out_faiwed;
	}
	do {
		ssweep(MPI3MW_POWTENABWE_POWW_INTEWVAW);
		if (mwioc->init_cmds.state == MPI3MW_CMD_NOTUSED)
			bweak;
		if (!pci_device_is_pwesent(mwioc->pdev))
			mwioc->unwecovewabwe = 1;
		if (mwioc->unwecovewabwe) {
			wetvaw = -1;
			goto out_faiwed_nowetwy;
		}
		ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
		if ((ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY) ||
		    (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT)) {
			mpi3mw_pwint_fauwt_info(mwioc);
			mwioc->init_cmds.is_waiting = 0;
			mwioc->init_cmds.cawwback = NUWW;
			mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
			goto out_faiwed;
		}
	} whiwe (--pe_timeout);

	if (!pe_timeout) {
		ioc_eww(mwioc, "powt enabwe timed out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_PE_TIMEOUT);
		mwioc->init_cmds.is_waiting = 0;
		mwioc->init_cmds.cawwback = NUWW;
		mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
		goto out_faiwed;
	} ewse if (mwioc->scan_faiwed) {
		ioc_eww(mwioc,
		    "powt enabwe faiwed with status=0x%04x\n",
		    mwioc->scan_faiwed);
	} ewse
		ioc_info(mwioc, "powt enabwe compweted successfuwwy\n");

	ioc_info(mwioc, "contwowwew %s compweted successfuwwy\n",
	    (is_wesume)?"wesume":"we-initiawization");
	wetuwn wetvaw;
out_faiwed:
	if (wetwy < 2) {
		wetwy++;
		ioc_wawn(mwioc, "wetwying contwowwew %s, wetwy_count:%d\n",
		    (is_wesume)?"wesume":"we-initiawization", wetwy);
		mpi3mw_memset_buffews(mwioc);
		goto wetwy_init;
	}
	wetvaw = -1;
out_faiwed_nowetwy:
	ioc_eww(mwioc, "contwowwew %s is faiwed\n",
	    (is_wesume)?"wesume":"we-initiawization");
	mpi3mw_issue_weset(mwioc, MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT,
	    MPI3MW_WESET_FWOM_CTWW_CWEANUP);
	mwioc->unwecovewabwe = 1;
	wetuwn wetvaw;
}

/**
 * mpi3mw_memset_op_wepwy_q_buffews - memset the opewationaw wepwy queue's
 *					segments
 * @mwioc: Adaptew instance wefewence
 * @qidx: Opewationaw wepwy queue index
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_memset_op_wepwy_q_buffews(stwuct mpi3mw_ioc *mwioc, u16 qidx)
{
	stwuct op_wepwy_qinfo *op_wepwy_q = mwioc->op_wepwy_qinfo + qidx;
	stwuct segments *segments;
	int i, size;

	if (!op_wepwy_q->q_segments)
		wetuwn;

	size = op_wepwy_q->segment_qd * mwioc->op_wepwy_desc_sz;
	segments = op_wepwy_q->q_segments;
	fow (i = 0; i < op_wepwy_q->num_segments; i++)
		memset(segments[i].segment, 0, size);
}

/**
 * mpi3mw_memset_op_weq_q_buffews - memset the opewationaw wequest queue's
 *					segments
 * @mwioc: Adaptew instance wefewence
 * @qidx: Opewationaw wequest queue index
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_memset_op_weq_q_buffews(stwuct mpi3mw_ioc *mwioc, u16 qidx)
{
	stwuct op_weq_qinfo *op_weq_q = mwioc->weq_qinfo + qidx;
	stwuct segments *segments;
	int i, size;

	if (!op_weq_q->q_segments)
		wetuwn;

	size = op_weq_q->segment_qd * mwioc->facts.op_weq_sz;
	segments = op_weq_q->q_segments;
	fow (i = 0; i < op_weq_q->num_segments; i++)
		memset(segments[i].segment, 0, size);
}

/**
 * mpi3mw_memset_buffews - memset memowy fow a contwowwew
 * @mwioc: Adaptew instance wefewence
 *
 * cweaw aww the memowy awwocated fow a contwowwew, typicawwy
 * cawwed post weset to weuse the memowy awwocated duwing the
 * contwowwew init.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_memset_buffews(stwuct mpi3mw_ioc *mwioc)
{
	u16 i;
	stwuct mpi3mw_thwottwe_gwoup_info *tg;

	mwioc->change_count = 0;
	mwioc->active_poww_qcount = 0;
	mwioc->defauwt_qcount = 0;
	if (mwioc->admin_weq_base)
		memset(mwioc->admin_weq_base, 0, mwioc->admin_weq_q_sz);
	if (mwioc->admin_wepwy_base)
		memset(mwioc->admin_wepwy_base, 0, mwioc->admin_wepwy_q_sz);
	atomic_set(&mwioc->admin_wepwy_q_in_use, 0);

	if (mwioc->init_cmds.wepwy) {
		memset(mwioc->init_cmds.wepwy, 0, sizeof(*mwioc->init_cmds.wepwy));
		memset(mwioc->bsg_cmds.wepwy, 0,
		    sizeof(*mwioc->bsg_cmds.wepwy));
		memset(mwioc->host_tm_cmds.wepwy, 0,
		    sizeof(*mwioc->host_tm_cmds.wepwy));
		memset(mwioc->pew_cmds.wepwy, 0,
		    sizeof(*mwioc->pew_cmds.wepwy));
		memset(mwioc->pew_abowt_cmd.wepwy, 0,
		    sizeof(*mwioc->pew_abowt_cmd.wepwy));
		memset(mwioc->twanspowt_cmds.wepwy, 0,
		    sizeof(*mwioc->twanspowt_cmds.wepwy));
		fow (i = 0; i < MPI3MW_NUM_DEVWMCMD; i++)
			memset(mwioc->dev_wmhs_cmds[i].wepwy, 0,
			    sizeof(*mwioc->dev_wmhs_cmds[i].wepwy));
		fow (i = 0; i < MPI3MW_NUM_EVTACKCMD; i++)
			memset(mwioc->evtack_cmds[i].wepwy, 0,
			    sizeof(*mwioc->evtack_cmds[i].wepwy));
		bitmap_cweaw(mwioc->wemovepend_bitmap, 0,
			     mwioc->dev_handwe_bitmap_bits);
		bitmap_cweaw(mwioc->devwem_bitmap, 0, MPI3MW_NUM_DEVWMCMD);
		bitmap_cweaw(mwioc->evtack_cmds_bitmap, 0,
			     MPI3MW_NUM_EVTACKCMD);
	}

	fow (i = 0; i < mwioc->num_queues; i++) {
		mwioc->op_wepwy_qinfo[i].qid = 0;
		mwioc->op_wepwy_qinfo[i].ci = 0;
		mwioc->op_wepwy_qinfo[i].num_wepwies = 0;
		mwioc->op_wepwy_qinfo[i].ephase = 0;
		atomic_set(&mwioc->op_wepwy_qinfo[i].pend_ios, 0);
		atomic_set(&mwioc->op_wepwy_qinfo[i].in_use, 0);
		mpi3mw_memset_op_wepwy_q_buffews(mwioc, i);

		mwioc->weq_qinfo[i].ci = 0;
		mwioc->weq_qinfo[i].pi = 0;
		mwioc->weq_qinfo[i].num_wequests = 0;
		mwioc->weq_qinfo[i].qid = 0;
		mwioc->weq_qinfo[i].wepwy_qid = 0;
		spin_wock_init(&mwioc->weq_qinfo[i].q_wock);
		mpi3mw_memset_op_weq_q_buffews(mwioc, i);
	}

	atomic_set(&mwioc->pend_wawge_data_sz, 0);
	if (mwioc->thwottwe_gwoups) {
		tg = mwioc->thwottwe_gwoups;
		fow (i = 0; i < mwioc->num_io_thwottwe_gwoup; i++, tg++) {
			tg->id = 0;
			tg->fw_qd = 0;
			tg->modified_qd = 0;
			tg->io_divewt = 0;
			tg->need_qd_weduction = 0;
			tg->high = 0;
			tg->wow = 0;
			tg->qd_weduction = 0;
			atomic_set(&tg->pend_wawge_data_sz, 0);
		}
	}
}

/**
 * mpi3mw_fwee_mem - Fwee memowy awwocated fow a contwowwew
 * @mwioc: Adaptew instance wefewence
 *
 * Fwee aww the memowy awwocated fow a contwowwew.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_fwee_mem(stwuct mpi3mw_ioc *mwioc)
{
	u16 i;
	stwuct mpi3mw_intw_info *intw_info;

	mpi3mw_fwee_encwosuwe_wist(mwioc);
	mpi3mw_fwee_ioctw_dma_memowy(mwioc);

	if (mwioc->sense_buf_poow) {
		if (mwioc->sense_buf)
			dma_poow_fwee(mwioc->sense_buf_poow, mwioc->sense_buf,
			    mwioc->sense_buf_dma);
		dma_poow_destwoy(mwioc->sense_buf_poow);
		mwioc->sense_buf = NUWW;
		mwioc->sense_buf_poow = NUWW;
	}
	if (mwioc->sense_buf_q_poow) {
		if (mwioc->sense_buf_q)
			dma_poow_fwee(mwioc->sense_buf_q_poow,
			    mwioc->sense_buf_q, mwioc->sense_buf_q_dma);
		dma_poow_destwoy(mwioc->sense_buf_q_poow);
		mwioc->sense_buf_q = NUWW;
		mwioc->sense_buf_q_poow = NUWW;
	}

	if (mwioc->wepwy_buf_poow) {
		if (mwioc->wepwy_buf)
			dma_poow_fwee(mwioc->wepwy_buf_poow, mwioc->wepwy_buf,
			    mwioc->wepwy_buf_dma);
		dma_poow_destwoy(mwioc->wepwy_buf_poow);
		mwioc->wepwy_buf = NUWW;
		mwioc->wepwy_buf_poow = NUWW;
	}
	if (mwioc->wepwy_fwee_q_poow) {
		if (mwioc->wepwy_fwee_q)
			dma_poow_fwee(mwioc->wepwy_fwee_q_poow,
			    mwioc->wepwy_fwee_q, mwioc->wepwy_fwee_q_dma);
		dma_poow_destwoy(mwioc->wepwy_fwee_q_poow);
		mwioc->wepwy_fwee_q = NUWW;
		mwioc->wepwy_fwee_q_poow = NUWW;
	}

	fow (i = 0; i < mwioc->num_op_weq_q; i++)
		mpi3mw_fwee_op_weq_q_segments(mwioc, i);

	fow (i = 0; i < mwioc->num_op_wepwy_q; i++)
		mpi3mw_fwee_op_wepwy_q_segments(mwioc, i);

	fow (i = 0; i < mwioc->intw_info_count; i++) {
		intw_info = mwioc->intw_info + i;
		intw_info->op_wepwy_q = NUWW;
	}

	kfwee(mwioc->weq_qinfo);
	mwioc->weq_qinfo = NUWW;
	mwioc->num_op_weq_q = 0;

	kfwee(mwioc->op_wepwy_qinfo);
	mwioc->op_wepwy_qinfo = NUWW;
	mwioc->num_op_wepwy_q = 0;

	kfwee(mwioc->init_cmds.wepwy);
	mwioc->init_cmds.wepwy = NUWW;

	kfwee(mwioc->bsg_cmds.wepwy);
	mwioc->bsg_cmds.wepwy = NUWW;

	kfwee(mwioc->host_tm_cmds.wepwy);
	mwioc->host_tm_cmds.wepwy = NUWW;

	kfwee(mwioc->pew_cmds.wepwy);
	mwioc->pew_cmds.wepwy = NUWW;

	kfwee(mwioc->pew_abowt_cmd.wepwy);
	mwioc->pew_abowt_cmd.wepwy = NUWW;

	fow (i = 0; i < MPI3MW_NUM_EVTACKCMD; i++) {
		kfwee(mwioc->evtack_cmds[i].wepwy);
		mwioc->evtack_cmds[i].wepwy = NUWW;
	}

	bitmap_fwee(mwioc->wemovepend_bitmap);
	mwioc->wemovepend_bitmap = NUWW;

	bitmap_fwee(mwioc->devwem_bitmap);
	mwioc->devwem_bitmap = NUWW;

	bitmap_fwee(mwioc->evtack_cmds_bitmap);
	mwioc->evtack_cmds_bitmap = NUWW;

	bitmap_fwee(mwioc->chain_bitmap);
	mwioc->chain_bitmap = NUWW;

	kfwee(mwioc->twanspowt_cmds.wepwy);
	mwioc->twanspowt_cmds.wepwy = NUWW;

	fow (i = 0; i < MPI3MW_NUM_DEVWMCMD; i++) {
		kfwee(mwioc->dev_wmhs_cmds[i].wepwy);
		mwioc->dev_wmhs_cmds[i].wepwy = NUWW;
	}

	if (mwioc->chain_buf_poow) {
		fow (i = 0; i < mwioc->chain_buf_count; i++) {
			if (mwioc->chain_sgw_wist[i].addw) {
				dma_poow_fwee(mwioc->chain_buf_poow,
				    mwioc->chain_sgw_wist[i].addw,
				    mwioc->chain_sgw_wist[i].dma_addw);
				mwioc->chain_sgw_wist[i].addw = NUWW;
			}
		}
		dma_poow_destwoy(mwioc->chain_buf_poow);
		mwioc->chain_buf_poow = NUWW;
	}

	kfwee(mwioc->chain_sgw_wist);
	mwioc->chain_sgw_wist = NUWW;

	if (mwioc->admin_wepwy_base) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->admin_wepwy_q_sz,
		    mwioc->admin_wepwy_base, mwioc->admin_wepwy_dma);
		mwioc->admin_wepwy_base = NUWW;
	}
	if (mwioc->admin_weq_base) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->admin_weq_q_sz,
		    mwioc->admin_weq_base, mwioc->admin_weq_dma);
		mwioc->admin_weq_base = NUWW;
	}
	if (mwioc->cfg_page) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->cfg_page_sz,
		    mwioc->cfg_page, mwioc->cfg_page_dma);
		mwioc->cfg_page = NUWW;
	}
	if (mwioc->pew_seqnum_viwt) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->pew_seqnum_sz,
		    mwioc->pew_seqnum_viwt, mwioc->pew_seqnum_dma);
		mwioc->pew_seqnum_viwt = NUWW;
	}

	kfwee(mwioc->thwottwe_gwoups);
	mwioc->thwottwe_gwoups = NUWW;

	kfwee(mwioc->wogdata_buf);
	mwioc->wogdata_buf = NUWW;

}

/**
 * mpi3mw_issue_ioc_shutdown - shutdown contwowwew
 * @mwioc: Adaptew instance wefewence
 *
 * Send shutodwn notification to the contwowwew and wait fow the
 * shutdown_timeout fow it to be compweted.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_issue_ioc_shutdown(stwuct mpi3mw_ioc *mwioc)
{
	u32 ioc_config, ioc_status;
	u8 wetvaw = 1;
	u32 timeout = MPI3MW_DEFAUWT_SHUTDOWN_TIME * 10;

	ioc_info(mwioc, "Issuing shutdown Notification\n");
	if (mwioc->unwecovewabwe) {
		ioc_wawn(mwioc,
		    "IOC is unwecovewabwe shutdown is not issued\n");
		wetuwn;
	}
	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	if ((ioc_status & MPI3_SYSIF_IOC_STATUS_SHUTDOWN_MASK)
	    == MPI3_SYSIF_IOC_STATUS_SHUTDOWN_IN_PWOGWESS) {
		ioc_info(mwioc, "shutdown awweady in pwogwess\n");
		wetuwn;
	}

	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);
	ioc_config |= MPI3_SYSIF_IOC_CONFIG_SHUTDOWN_NOWMAW;
	ioc_config |= MPI3_SYSIF_IOC_CONFIG_DEVICE_SHUTDOWN_SEND_WEQ;

	wwitew(ioc_config, &mwioc->sysif_wegs->ioc_configuwation);

	if (mwioc->facts.shutdown_timeout)
		timeout = mwioc->facts.shutdown_timeout * 10;

	do {
		ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
		if ((ioc_status & MPI3_SYSIF_IOC_STATUS_SHUTDOWN_MASK)
		    == MPI3_SYSIF_IOC_STATUS_SHUTDOWN_COMPWETE) {
			wetvaw = 0;
			bweak;
		}
		msweep(100);
	} whiwe (--timeout);

	ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);
	ioc_config = weadw(&mwioc->sysif_wegs->ioc_configuwation);

	if (wetvaw) {
		if ((ioc_status & MPI3_SYSIF_IOC_STATUS_SHUTDOWN_MASK)
		    == MPI3_SYSIF_IOC_STATUS_SHUTDOWN_IN_PWOGWESS)
			ioc_wawn(mwioc,
			    "shutdown stiww in pwogwess aftew timeout\n");
	}

	ioc_info(mwioc,
	    "Base IOC Sts/Config aftew %s shutdown is (0x%x)/(0x%x)\n",
	    (!wetvaw) ? "successfuw" : "faiwed", ioc_status,
	    ioc_config);
}

/**
 * mpi3mw_cweanup_ioc - Cweanup contwowwew
 * @mwioc: Adaptew instance wefewence
 *
 * contwowwew cweanup handwew, Message unit weset ow soft weset
 * and shutdown notification is issued to the contwowwew.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_cweanup_ioc(stwuct mpi3mw_ioc *mwioc)
{
	enum mpi3mw_iocstate ioc_state;

	dpwint_exit(mwioc, "cweaning up the contwowwew\n");
	mpi3mw_ioc_disabwe_intw(mwioc);

	ioc_state = mpi3mw_get_iocstate(mwioc);

	if ((!mwioc->unwecovewabwe) && (!mwioc->weset_in_pwogwess) &&
	    (ioc_state == MWIOC_STATE_WEADY)) {
		if (mpi3mw_issue_and_pwocess_muw(mwioc,
		    MPI3MW_WESET_FWOM_CTWW_CWEANUP))
			mpi3mw_issue_weset(mwioc,
			    MPI3_SYSIF_HOST_DIAG_WESET_ACTION_SOFT_WESET,
			    MPI3MW_WESET_FWOM_MUW_FAIWUWE);
		mpi3mw_issue_ioc_shutdown(mwioc);
	}
	dpwint_exit(mwioc, "contwowwew cweanup compweted\n");
}

/**
 * mpi3mw_dwv_cmd_comp_weset - Fwush a intewnaw dwivew command
 * @mwioc: Adaptew instance wefewence
 * @cmdptw: Intewnaw command twackew
 *
 * Compwete an intewnaw dwivew commands with state indicating it
 * is compweted due to weset.
 *
 * Wetuwn: Nothing.
 */
static inwine void mpi3mw_dwv_cmd_comp_weset(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *cmdptw)
{
	if (cmdptw->state & MPI3MW_CMD_PENDING) {
		cmdptw->state |= MPI3MW_CMD_WESET;
		cmdptw->state &= ~MPI3MW_CMD_PENDING;
		if (cmdptw->is_waiting) {
			compwete(&cmdptw->done);
			cmdptw->is_waiting = 0;
		} ewse if (cmdptw->cawwback)
			cmdptw->cawwback(mwioc, cmdptw);
	}
}

/**
 * mpi3mw_fwush_dwv_cmds - Fwush intewnawdwivew commands
 * @mwioc: Adaptew instance wefewence
 *
 * Fwush aww intewnaw dwivew commands post weset
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_fwush_dwv_cmds(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3mw_dwv_cmd *cmdptw;
	u8 i;

	cmdptw = &mwioc->init_cmds;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);

	cmdptw = &mwioc->cfg_cmds;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);

	cmdptw = &mwioc->bsg_cmds;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);
	cmdptw = &mwioc->host_tm_cmds;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);

	fow (i = 0; i < MPI3MW_NUM_DEVWMCMD; i++) {
		cmdptw = &mwioc->dev_wmhs_cmds[i];
		mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);
	}

	fow (i = 0; i < MPI3MW_NUM_EVTACKCMD; i++) {
		cmdptw = &mwioc->evtack_cmds[i];
		mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);
	}

	cmdptw = &mwioc->pew_cmds;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);

	cmdptw = &mwioc->pew_abowt_cmd;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);

	cmdptw = &mwioc->twanspowt_cmds;
	mpi3mw_dwv_cmd_comp_weset(mwioc, cmdptw);
}

/**
 * mpi3mw_pew_wait_post - Issue PEW Wait
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * Issue PEW Wait MPI wequest thwough admin queue and wetuwn.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_pew_wait_post(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	stwuct mpi3_pew_weq_action_wait pew_wait;

	mwioc->pew_abowt_wequested = fawse;

	memset(&pew_wait, 0, sizeof(pew_wait));
	dwv_cmd->state = MPI3MW_CMD_PENDING;
	dwv_cmd->is_waiting = 0;
	dwv_cmd->cawwback = mpi3mw_pew_wait_compwete;
	dwv_cmd->ioc_status = 0;
	dwv_cmd->ioc_woginfo = 0;
	pew_wait.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_PEW_WAIT);
	pew_wait.function = MPI3_FUNCTION_PEWSISTENT_EVENT_WOG;
	pew_wait.action = MPI3_PEW_ACTION_WAIT;
	pew_wait.stawting_sequence_numbew = cpu_to_we32(mwioc->pew_newest_seqnum);
	pew_wait.wocawe = cpu_to_we16(mwioc->pew_wocawe);
	pew_wait.cwass = cpu_to_we16(mwioc->pew_cwass);
	pew_wait.wait_time = MPI3_PEW_WAITTIME_INFINITE_WAIT;
	dpwint_bsg_info(mwioc, "sending pew_wait seqnum(%d), cwass(%d), wocawe(0x%08x)\n",
	    mwioc->pew_newest_seqnum, mwioc->pew_cwass, mwioc->pew_wocawe);

	if (mpi3mw_admin_wequest_post(mwioc, &pew_wait, sizeof(pew_wait), 0)) {
		dpwint_bsg_eww(mwioc,
			    "Issuing PEWWait: Admin post faiwed\n");
		dwv_cmd->state = MPI3MW_CMD_NOTUSED;
		dwv_cmd->cawwback = NUWW;
		dwv_cmd->wetwy_count = 0;
		mwioc->pew_enabwed = fawse;
	}
}

/**
 * mpi3mw_pew_get_seqnum_post - Issue PEW Get Sequence numbew
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * Issue PEW get sequence numbew MPI wequest thwough admin queue
 * and wetuwn.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_pew_get_seqnum_post(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	stwuct mpi3_pew_weq_action_get_sequence_numbews pew_getseq_weq;
	u8 sgw_fwags = MPI3MW_SGEFWAGS_SYSTEM_SIMPWE_END_OF_WIST;
	int wetvaw = 0;

	memset(&pew_getseq_weq, 0, sizeof(pew_getseq_weq));
	mwioc->pew_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->pew_cmds.is_waiting = 0;
	mwioc->pew_cmds.ioc_status = 0;
	mwioc->pew_cmds.ioc_woginfo = 0;
	mwioc->pew_cmds.cawwback = mpi3mw_pew_get_seqnum_compwete;
	pew_getseq_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_PEW_WAIT);
	pew_getseq_weq.function = MPI3_FUNCTION_PEWSISTENT_EVENT_WOG;
	pew_getseq_weq.action = MPI3_PEW_ACTION_GET_SEQNUM;
	mpi3mw_add_sg_singwe(&pew_getseq_weq.sgw, sgw_fwags,
	    mwioc->pew_seqnum_sz, mwioc->pew_seqnum_dma);

	wetvaw = mpi3mw_admin_wequest_post(mwioc, &pew_getseq_weq,
			sizeof(pew_getseq_weq), 0);
	if (wetvaw) {
		if (dwv_cmd) {
			dwv_cmd->state = MPI3MW_CMD_NOTUSED;
			dwv_cmd->cawwback = NUWW;
			dwv_cmd->wetwy_count = 0;
		}
		mwioc->pew_enabwed = fawse;
	}

	wetuwn wetvaw;
}

/**
 * mpi3mw_pew_wait_compwete - PEWWait Compwetion cawwback
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * This is a cawwback handwew fow the PEWWait wequest and
 * fiwmwawe compwetes a PEWWait wequest when it is abowted ow a
 * new PEW entwy is avaiwabwe. This sends AEN to the appwication
 * and if the PEWwait compwetion is not due to PEWAbowt then
 * this wiww send a wequest fow new PEW Sequence numbew
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_pew_wait_compwete(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	stwuct mpi3_pew_wepwy *pew_wepwy = NUWW;
	u16 ioc_status, pe_wog_status;
	boow do_wetwy = fawse;

	if (dwv_cmd->state & MPI3MW_CMD_WESET)
		goto cweanup_dwv_cmd;

	ioc_status = dwv_cmd->ioc_status & MPI3_IOCSTATUS_STATUS_MASK;
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "%s: Faiwed ioc_status(0x%04x) Woginfo(0x%08x)\n",
			__func__, ioc_status, dwv_cmd->ioc_woginfo);
		dpwint_bsg_eww(mwioc,
		    "pew_wait: faiwed with ioc_status(0x%04x), wog_info(0x%08x)\n",
		    ioc_status, dwv_cmd->ioc_woginfo);
		do_wetwy = twue;
	}

	if (dwv_cmd->state & MPI3MW_CMD_WEPWY_VAWID)
		pew_wepwy = (stwuct mpi3_pew_wepwy *)dwv_cmd->wepwy;

	if (!pew_wepwy) {
		dpwint_bsg_eww(mwioc,
		    "pew_wait: faiwed due to no wepwy\n");
		goto out_faiwed;
	}

	pe_wog_status = we16_to_cpu(pew_wepwy->pe_wog_status);
	if ((pe_wog_status != MPI3_PEW_STATUS_SUCCESS) &&
	    (pe_wog_status != MPI3_PEW_STATUS_ABOWTED)) {
		ioc_eww(mwioc, "%s: Faiwed pe_wog_status(0x%04x)\n",
			__func__, pe_wog_status);
		dpwint_bsg_eww(mwioc,
		    "pew_wait: faiwed due to pew_wog_status(0x%04x)\n",
		    pe_wog_status);
		do_wetwy = twue;
	}

	if (do_wetwy) {
		if (dwv_cmd->wetwy_count < MPI3MW_PEW_WETWY_COUNT) {
			dwv_cmd->wetwy_count++;
			dpwint_bsg_eww(mwioc, "pew_wait: wetwying(%d)\n",
			    dwv_cmd->wetwy_count);
			mpi3mw_pew_wait_post(mwioc, dwv_cmd);
			wetuwn;
		}
		dpwint_bsg_eww(mwioc,
		    "pew_wait: faiwed aftew aww wetwies(%d)\n",
		    dwv_cmd->wetwy_count);
		goto out_faiwed;
	}
	atomic64_inc(&event_countew);
	if (!mwioc->pew_abowt_wequested) {
		mwioc->pew_cmds.wetwy_count = 0;
		mpi3mw_pew_get_seqnum_post(mwioc, &mwioc->pew_cmds);
	}

	wetuwn;
out_faiwed:
	mwioc->pew_enabwed = fawse;
cweanup_dwv_cmd:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	dwv_cmd->wetwy_count = 0;
}

/**
 * mpi3mw_pew_get_seqnum_compwete - PEWGetSeqNum Compwetion cawwback
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * This is a cawwback handwew fow the PEW get sequence numbew
 * wequest and a new PEW wait wequest wiww be issued to the
 * fiwmwawe fwom this
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_pew_get_seqnum_compwete(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	stwuct mpi3_pew_wepwy *pew_wepwy = NUWW;
	stwuct mpi3_pew_seq *pew_seqnum_viwt;
	u16 ioc_status;
	boow do_wetwy = fawse;

	pew_seqnum_viwt = (stwuct mpi3_pew_seq *)mwioc->pew_seqnum_viwt;

	if (dwv_cmd->state & MPI3MW_CMD_WESET)
		goto cweanup_dwv_cmd;

	ioc_status = dwv_cmd->ioc_status & MPI3_IOCSTATUS_STATUS_MASK;
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		dpwint_bsg_eww(mwioc,
		    "pew_get_seqnum: faiwed with ioc_status(0x%04x), wog_info(0x%08x)\n",
		    ioc_status, dwv_cmd->ioc_woginfo);
		do_wetwy = twue;
	}

	if (dwv_cmd->state & MPI3MW_CMD_WEPWY_VAWID)
		pew_wepwy = (stwuct mpi3_pew_wepwy *)dwv_cmd->wepwy;
	if (!pew_wepwy) {
		dpwint_bsg_eww(mwioc,
		    "pew_get_seqnum: faiwed due to no wepwy\n");
		goto out_faiwed;
	}

	if (we16_to_cpu(pew_wepwy->pe_wog_status) != MPI3_PEW_STATUS_SUCCESS) {
		dpwint_bsg_eww(mwioc,
		    "pew_get_seqnum: faiwed due to pew_wog_status(0x%04x)\n",
		    we16_to_cpu(pew_wepwy->pe_wog_status));
		do_wetwy = twue;
	}

	if (do_wetwy) {
		if (dwv_cmd->wetwy_count < MPI3MW_PEW_WETWY_COUNT) {
			dwv_cmd->wetwy_count++;
			dpwint_bsg_eww(mwioc,
			    "pew_get_seqnum: wetwying(%d)\n",
			    dwv_cmd->wetwy_count);
			mpi3mw_pew_get_seqnum_post(mwioc, dwv_cmd);
			wetuwn;
		}

		dpwint_bsg_eww(mwioc,
		    "pew_get_seqnum: faiwed aftew aww wetwies(%d)\n",
		    dwv_cmd->wetwy_count);
		goto out_faiwed;
	}
	mwioc->pew_newest_seqnum = we32_to_cpu(pew_seqnum_viwt->newest) + 1;
	dwv_cmd->wetwy_count = 0;
	mpi3mw_pew_wait_post(mwioc, dwv_cmd);

	wetuwn;
out_faiwed:
	mwioc->pew_enabwed = fawse;
cweanup_dwv_cmd:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	dwv_cmd->wetwy_count = 0;
}

/**
 * mpi3mw_soft_weset_handwew - Weset the contwowwew
 * @mwioc: Adaptew instance wefewence
 * @weset_weason: Weset weason code
 * @snapdump: Fwag to genewate snapdump in fiwmwawe ow not
 *
 * This is an handwew fow wecovewing contwowwew by issuing soft
 * weset awe diag fauwt weset.  This is a bwocking function and
 * when one weset is executed if any othew wesets they wiww be
 * bwocked. Aww BSG wequests wiww be bwocked duwing the weset. If
 * contwowwew weset is successfuw then the contwowwew wiww be
 * weinitawized, othewwise the contwowwew wiww be mawked as not
 * wecovewabwe
 *
 * In snapdump bit is set, the contwowwew is issued with diag
 * fauwt weset so that the fiwmwawe can cweate a snap dump and
 * post that the fiwmwawe wiww wesuwt in F000 fauwt and the
 * dwivew wiww issue soft weset to wecovew fwom that.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_soft_weset_handwew(stwuct mpi3mw_ioc *mwioc,
	u32 weset_weason, u8 snapdump)
{
	int wetvaw = 0, i;
	unsigned wong fwags;
	u32 host_diagnostic, timeout = MPI3_SYSIF_DIAG_SAVE_TIMEOUT * 10;

	/* Bwock the weset handwew untiw diag save in pwogwess*/
	dpwint_weset(mwioc,
	    "soft_weset_handwew: check and bwock on diagsave_timeout(%d)\n",
	    mwioc->diagsave_timeout);
	whiwe (mwioc->diagsave_timeout)
		ssweep(1);
	/*
	 * Bwock new wesets untiw the cuwwentwy executing one is finished and
	 * wetuwn the status of the existing weset fow aww bwocked wesets
	 */
	dpwint_weset(mwioc, "soft_weset_handwew: acquiwing weset_mutex\n");
	if (!mutex_twywock(&mwioc->weset_mutex)) {
		ioc_info(mwioc,
		    "contwowwew weset twiggewed by %s is bwocked due to anothew weset in pwogwess\n",
		    mpi3mw_weset_wc_name(weset_weason));
		do {
			ssweep(1);
		} whiwe (mwioc->weset_in_pwogwess == 1);
		ioc_info(mwioc,
		    "wetuwning pwevious weset wesuwt(%d) fow the weset twiggewed by %s\n",
		    mwioc->pwev_weset_wesuwt,
		    mpi3mw_weset_wc_name(weset_weason));
		wetuwn mwioc->pwev_weset_wesuwt;
	}
	ioc_info(mwioc, "contwowwew weset is twiggewed by %s\n",
	    mpi3mw_weset_wc_name(weset_weason));

	mwioc->device_wefwesh_on = 0;
	mwioc->weset_in_pwogwess = 1;
	mwioc->stop_bsgs = 1;
	mwioc->pwev_weset_wesuwt = -1;

	if ((!snapdump) && (weset_weason != MPI3MW_WESET_FWOM_FAUWT_WATCH) &&
	    (weset_weason != MPI3MW_WESET_FWOM_FIWMWAWE) &&
	    (weset_weason != MPI3MW_WESET_FWOM_CIACTIV_FAUWT)) {
		fow (i = 0; i < MPI3_EVENT_NOTIFY_EVENTMASK_WOWDS; i++)
			mwioc->event_masks[i] = -1;

		dpwint_weset(mwioc, "soft_weset_handwew: masking events\n");
		mpi3mw_issue_event_notification(mwioc);
	}

	mpi3mw_wait_fow_host_io(mwioc, MPI3MW_WESET_HOST_IOWAIT_TIMEOUT);

	mpi3mw_ioc_disabwe_intw(mwioc);

	if (snapdump) {
		mpi3mw_set_diagsave(mwioc);
		wetvaw = mpi3mw_issue_weset(mwioc,
		    MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT, weset_weason);
		if (!wetvaw) {
			do {
				host_diagnostic =
				    weadw(&mwioc->sysif_wegs->host_diagnostic);
				if (!(host_diagnostic &
				    MPI3_SYSIF_HOST_DIAG_SAVE_IN_PWOGWESS))
					bweak;
				msweep(100);
			} whiwe (--timeout);
		}
	}

	wetvaw = mpi3mw_issue_weset(mwioc,
	    MPI3_SYSIF_HOST_DIAG_WESET_ACTION_SOFT_WESET, weset_weason);
	if (wetvaw) {
		ioc_eww(mwioc, "Faiwed to issue soft weset to the ioc\n");
		goto out;
	}
	if (mwioc->num_io_thwottwe_gwoup !=
	    mwioc->facts.max_io_thwottwe_gwoup) {
		ioc_eww(mwioc,
		    "max io thwottwe gwoup doesn't match owd(%d), new(%d)\n",
		    mwioc->num_io_thwottwe_gwoup,
		    mwioc->facts.max_io_thwottwe_gwoup);
		wetvaw = -EPEWM;
		goto out;
	}

	mpi3mw_fwush_dewayed_cmd_wists(mwioc);
	mpi3mw_fwush_dwv_cmds(mwioc);
	bitmap_cweaw(mwioc->devwem_bitmap, 0, MPI3MW_NUM_DEVWMCMD);
	bitmap_cweaw(mwioc->wemovepend_bitmap, 0,
		     mwioc->dev_handwe_bitmap_bits);
	bitmap_cweaw(mwioc->evtack_cmds_bitmap, 0, MPI3MW_NUM_EVTACKCMD);
	mpi3mw_fwush_host_io(mwioc);
	mpi3mw_cweanup_fwevt_wist(mwioc);
	mpi3mw_invawidate_devhandwes(mwioc);
	mpi3mw_fwee_encwosuwe_wist(mwioc);

	if (mwioc->pwepawe_fow_weset) {
		mwioc->pwepawe_fow_weset = 0;
		mwioc->pwepawe_fow_weset_timeout_countew = 0;
	}
	mpi3mw_memset_buffews(mwioc);
	wetvaw = mpi3mw_weinit_ioc(mwioc, 0);
	if (wetvaw) {
		pw_eww(IOCNAME "weinit aftew soft weset faiwed: weason %d\n",
		    mwioc->name, weset_weason);
		goto out;
	}
	ssweep(MPI3MW_WESET_TOPOWOGY_SETTWE_TIME);

out:
	if (!wetvaw) {
		mwioc->diagsave_timeout = 0;
		mwioc->weset_in_pwogwess = 0;
		mwioc->pew_abowt_wequested = 0;
		if (mwioc->pew_enabwed) {
			mwioc->pew_cmds.wetwy_count = 0;
			mpi3mw_pew_wait_post(mwioc, &mwioc->pew_cmds);
		}

		mwioc->device_wefwesh_on = 0;

		mwioc->ts_update_countew = 0;
		spin_wock_iwqsave(&mwioc->watchdog_wock, fwags);
		if (mwioc->watchdog_wowk_q)
			queue_dewayed_wowk(mwioc->watchdog_wowk_q,
			    &mwioc->watchdog_wowk,
			    msecs_to_jiffies(MPI3MW_WATCHDOG_INTEWVAW));
		spin_unwock_iwqwestowe(&mwioc->watchdog_wock, fwags);
		mwioc->stop_bsgs = 0;
		if (mwioc->pew_enabwed)
			atomic64_inc(&event_countew);
	} ewse {
		mpi3mw_issue_weset(mwioc,
		    MPI3_SYSIF_HOST_DIAG_WESET_ACTION_DIAG_FAUWT, weset_weason);
		mwioc->device_wefwesh_on = 0;
		mwioc->unwecovewabwe = 1;
		mwioc->weset_in_pwogwess = 0;
		wetvaw = -1;
		mpi3mw_fwush_cmds_fow_unwecovewed_contwowwew(mwioc);
	}
	mwioc->pwev_weset_wesuwt = wetvaw;
	mutex_unwock(&mwioc->weset_mutex);
	ioc_info(mwioc, "contwowwew weset is %s\n",
	    ((wetvaw == 0) ? "successfuw" : "faiwed"));
	wetuwn wetvaw;
}


/**
 * mpi3mw_fwee_config_dma_memowy - fwee memowy fow config page
 * @mwioc: Adaptew instance wefewence
 * @mem_desc: memowy descwiptow stwuctuwe
 *
 * Check whethew the size of the buffew specified by the memowy
 * descwiptow is gweatew than the defauwt page size if so then
 * fwee the memowy pointed by the descwiptow.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwee_config_dma_memowy(stwuct mpi3mw_ioc *mwioc,
	stwuct dma_memowy_desc *mem_desc)
{
	if ((mem_desc->size > mwioc->cfg_page_sz) && mem_desc->addw) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mem_desc->size,
		    mem_desc->addw, mem_desc->dma_addw);
		mem_desc->addw = NUWW;
	}
}

/**
 * mpi3mw_awwoc_config_dma_memowy - Awwoc memowy fow config page
 * @mwioc: Adaptew instance wefewence
 * @mem_desc: Memowy descwiptow to howd dma memowy info
 *
 * This function awwocates new dmaabwe memowy ow pwovides the
 * defauwt config page dmaabwe memowy based on the memowy size
 * descwibed by the descwiptow.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_awwoc_config_dma_memowy(stwuct mpi3mw_ioc *mwioc,
	stwuct dma_memowy_desc *mem_desc)
{
	if (mem_desc->size > mwioc->cfg_page_sz) {
		mem_desc->addw = dma_awwoc_cohewent(&mwioc->pdev->dev,
		    mem_desc->size, &mem_desc->dma_addw, GFP_KEWNEW);
		if (!mem_desc->addw)
			wetuwn -ENOMEM;
	} ewse {
		mem_desc->addw = mwioc->cfg_page;
		mem_desc->dma_addw = mwioc->cfg_page_dma;
		memset(mem_desc->addw, 0, mwioc->cfg_page_sz);
	}
	wetuwn 0;
}

/**
 * mpi3mw_post_cfg_weq - Issue config wequests and wait
 * @mwioc: Adaptew instance wefewence
 * @cfg_weq: Configuwation wequest
 * @timeout: Timeout in seconds
 * @ioc_status: Pointew to wetuwn ioc status
 *
 * A genewic function fow posting MPI3 configuwation wequest to
 * the fiwmwawe. This bwocks fow the compwetion of wequest fow
 * timeout seconds and if the wequest times out this function
 * fauwts the contwowwew with pwopew weason code.
 *
 * On successfuw compwetion of the wequest this function wetuwns
 * appwopwiate ioc status fwom the fiwmwawe back to the cawwew.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_post_cfg_weq(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_config_wequest *cfg_weq, int timeout, u16 *ioc_status)
{
	int wetvaw = 0;

	mutex_wock(&mwioc->cfg_cmds.mutex);
	if (mwioc->cfg_cmds.state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "sending config wequest faiwed due to command in use\n");
		mutex_unwock(&mwioc->cfg_cmds.mutex);
		goto out;
	}
	mwioc->cfg_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->cfg_cmds.is_waiting = 1;
	mwioc->cfg_cmds.cawwback = NUWW;
	mwioc->cfg_cmds.ioc_status = 0;
	mwioc->cfg_cmds.ioc_woginfo = 0;

	cfg_weq->host_tag = cpu_to_we16(MPI3MW_HOSTTAG_CFG_CMDS);
	cfg_weq->function = MPI3_FUNCTION_CONFIG;

	init_compwetion(&mwioc->cfg_cmds.done);
	dpwint_cfg_info(mwioc, "posting config wequest\n");
	if (mwioc->wogging_wevew & MPI3_DEBUG_CFG_INFO)
		dpwint_dump(cfg_weq, sizeof(stwuct mpi3_config_wequest),
		    "mpi3_cfg_weq");
	wetvaw = mpi3mw_admin_wequest_post(mwioc, cfg_weq, sizeof(*cfg_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "posting config wequest faiwed\n");
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->cfg_cmds.done, (timeout * HZ));
	if (!(mwioc->cfg_cmds.state & MPI3MW_CMD_COMPWETE)) {
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_CFG_WEQ_TIMEOUT);
		ioc_eww(mwioc, "config wequest timed out\n");
		wetvaw = -1;
		goto out_unwock;
	}
	*ioc_status = mwioc->cfg_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK;
	if ((*ioc_status) != MPI3_IOCSTATUS_SUCCESS)
		dpwint_cfg_eww(mwioc,
		    "cfg_page wequest wetuwned with ioc_status(0x%04x), wog_info(0x%08x)\n",
		    *ioc_status, mwioc->cfg_cmds.ioc_woginfo);

out_unwock:
	mwioc->cfg_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->cfg_cmds.mutex);

out:
	wetuwn wetvaw;
}

/**
 * mpi3mw_pwocess_cfg_weq - config page wequest pwocessow
 * @mwioc: Adaptew instance wefewence
 * @cfg_weq: Configuwation wequest
 * @cfg_hdw: Configuwation page headew
 * @timeout: Timeout in seconds
 * @ioc_status: Pointew to wetuwn ioc status
 * @cfg_buf: Memowy pointew to copy config page ow headew
 * @cfg_buf_sz: Size of the memowy to get config page ow headew
 *
 * This is handwew fow config page wead, wwite and config page
 * headew wead opewations.
 *
 * This function expects the cfg_weq to be popuwated with page
 * type, page numbew, action fow the headew wead and with page
 * addwess fow aww othew opewations.
 *
 * The cfg_hdw can be passed as nuww fow weading wequiwed headew
 * detaiws fow wead/wwite pages the cfg_hdw shouwd point vawid
 * configuwation page headew.
 *
 * This awwocates dmaabwe memowy based on the size of the config
 * buffew and set the SGE of the cfg_weq.
 *
 * Fow wwite actions, the config page data has to be passed in
 * the cfg_buf and size of the data has to be mentioned in the
 * cfg_buf_sz.
 *
 * Fow wead/headew actions, on successfuw compwetion of the
 * wequest with successfuw ioc_status the data wiww be copied
 * into the cfg_buf wimited to a minimum of actuaw page size and
 * cfg_buf_sz
 *
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int mpi3mw_pwocess_cfg_weq(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_config_wequest *cfg_weq,
	stwuct mpi3_config_page_headew *cfg_hdw, int timeout, u16 *ioc_status,
	void *cfg_buf, u32 cfg_buf_sz)
{
	stwuct dma_memowy_desc mem_desc;
	int wetvaw = -1;
	u8 invawid_action = 0;
	u8 sgw_fwags = MPI3MW_SGEFWAGS_SYSTEM_SIMPWE_END_OF_WIST;

	memset(&mem_desc, 0, sizeof(stwuct dma_memowy_desc));

	if (cfg_weq->action == MPI3_CONFIG_ACTION_PAGE_HEADEW)
		mem_desc.size = sizeof(stwuct mpi3_config_page_headew);
	ewse {
		if (!cfg_hdw) {
			ioc_eww(mwioc, "nuww config headew passed fow config action(%d), page_type(0x%02x), page_num(%d)\n",
			    cfg_weq->action, cfg_weq->page_type,
			    cfg_weq->page_numbew);
			goto out;
		}
		switch (cfg_hdw->page_attwibute & MPI3_CONFIG_PAGEATTW_MASK) {
		case MPI3_CONFIG_PAGEATTW_WEAD_ONWY:
			if (cfg_weq->action
			    != MPI3_CONFIG_ACTION_WEAD_CUWWENT)
				invawid_action = 1;
			bweak;
		case MPI3_CONFIG_PAGEATTW_CHANGEABWE:
			if ((cfg_weq->action ==
			     MPI3_CONFIG_ACTION_WEAD_PEWSISTENT) ||
			    (cfg_weq->action ==
			     MPI3_CONFIG_ACTION_WWITE_PEWSISTENT))
				invawid_action = 1;
			bweak;
		case MPI3_CONFIG_PAGEATTW_PEWSISTENT:
		defauwt:
			bweak;
		}
		if (invawid_action) {
			ioc_eww(mwioc,
			    "config action(%d) is not awwowed fow page_type(0x%02x), page_num(%d) with page_attwibute(0x%02x)\n",
			    cfg_weq->action, cfg_weq->page_type,
			    cfg_weq->page_numbew, cfg_hdw->page_attwibute);
			goto out;
		}
		mem_desc.size = we16_to_cpu(cfg_hdw->page_wength) * 4;
		cfg_weq->page_wength = cfg_hdw->page_wength;
		cfg_weq->page_vewsion = cfg_hdw->page_vewsion;
	}
	if (mpi3mw_awwoc_config_dma_memowy(mwioc, &mem_desc))
		goto out;

	mpi3mw_add_sg_singwe(&cfg_weq->sgw, sgw_fwags, mem_desc.size,
	    mem_desc.dma_addw);

	if ((cfg_weq->action == MPI3_CONFIG_ACTION_WWITE_PEWSISTENT) ||
	    (cfg_weq->action == MPI3_CONFIG_ACTION_WWITE_CUWWENT)) {
		memcpy(mem_desc.addw, cfg_buf, min_t(u16, mem_desc.size,
		    cfg_buf_sz));
		dpwint_cfg_info(mwioc, "config buffew to be wwitten\n");
		if (mwioc->wogging_wevew & MPI3_DEBUG_CFG_INFO)
			dpwint_dump(mem_desc.addw, mem_desc.size, "cfg_buf");
	}

	if (mpi3mw_post_cfg_weq(mwioc, cfg_weq, timeout, ioc_status))
		goto out;

	wetvaw = 0;
	if ((*ioc_status == MPI3_IOCSTATUS_SUCCESS) &&
	    (cfg_weq->action != MPI3_CONFIG_ACTION_WWITE_PEWSISTENT) &&
	    (cfg_weq->action != MPI3_CONFIG_ACTION_WWITE_CUWWENT)) {
		memcpy(cfg_buf, mem_desc.addw, min_t(u16, mem_desc.size,
		    cfg_buf_sz));
		dpwint_cfg_info(mwioc, "config buffew wead\n");
		if (mwioc->wogging_wevew & MPI3_DEBUG_CFG_INFO)
			dpwint_dump(mem_desc.addw, mem_desc.size, "cfg_buf");
	}

out:
	mpi3mw_fwee_config_dma_memowy(mwioc, &mem_desc);
	wetuwn wetvaw;
}

/**
 * mpi3mw_cfg_get_dev_pg0 - Wead cuwwent device page0
 * @mwioc: Adaptew instance wefewence
 * @ioc_status: Pointew to wetuwn ioc status
 * @dev_pg0: Pointew to wetuwn device page 0
 * @pg_sz: Size of the memowy awwocated to the page pointew
 * @fowm: The fowm to be used fow addwessing the page
 * @fowm_spec: Fowm specific infowmation wike device handwe
 *
 * This is handwew fow config page wead fow a specific device
 * page0. The ioc_status has the contwowwew wetuwned ioc_status.
 * This woutine doesn't check ioc_status to decide whethew the
 * page wead is success ow not and it is the cawwews
 * wesponsibiwity.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_dev_pg0(stwuct mpi3mw_ioc *mwioc, u16 *ioc_status,
	stwuct mpi3_device_page0 *dev_pg0, u16 pg_sz, u32 fowm, u32 fowm_spec)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u32 page_addwess;

	memset(dev_pg0, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_DEVICE;
	cfg_weq.page_numbew = 0;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "device page0 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (*ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "device page0 headew wead faiwed with ioc_status(0x%04x)\n",
		    *ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;
	page_addwess = ((fowm & MPI3_DEVICE_PGAD_FOWM_MASK) |
	    (fowm_spec & MPI3_DEVICE_PGAD_HANDWE_MASK));
	cfg_weq.page_addwess = cpu_to_we32(page_addwess);
	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, dev_pg0, pg_sz)) {
		ioc_eww(mwioc, "device page0 wead faiwed\n");
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}


/**
 * mpi3mw_cfg_get_sas_phy_pg0 - Wead cuwwent SAS Phy page0
 * @mwioc: Adaptew instance wefewence
 * @ioc_status: Pointew to wetuwn ioc status
 * @phy_pg0: Pointew to wetuwn SAS Phy page 0
 * @pg_sz: Size of the memowy awwocated to the page pointew
 * @fowm: The fowm to be used fow addwessing the page
 * @fowm_spec: Fowm specific infowmation wike phy numbew
 *
 * This is handwew fow config page wead fow a specific SAS Phy
 * page0. The ioc_status has the contwowwew wetuwned ioc_status.
 * This woutine doesn't check ioc_status to decide whethew the
 * page wead is success ow not and it is the cawwews
 * wesponsibiwity.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_sas_phy_pg0(stwuct mpi3mw_ioc *mwioc, u16 *ioc_status,
	stwuct mpi3_sas_phy_page0 *phy_pg0, u16 pg_sz, u32 fowm,
	u32 fowm_spec)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u32 page_addwess;

	memset(phy_pg0, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_PHY;
	cfg_weq.page_numbew = 0;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "sas phy page0 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (*ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas phy page0 headew wead faiwed with ioc_status(0x%04x)\n",
		    *ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;
	page_addwess = ((fowm & MPI3_SAS_PHY_PGAD_FOWM_MASK) |
	    (fowm_spec & MPI3_SAS_PHY_PGAD_PHY_NUMBEW_MASK));
	cfg_weq.page_addwess = cpu_to_we32(page_addwess);
	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, phy_pg0, pg_sz)) {
		ioc_eww(mwioc, "sas phy page0 wead faiwed\n");
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}

/**
 * mpi3mw_cfg_get_sas_phy_pg1 - Wead cuwwent SAS Phy page1
 * @mwioc: Adaptew instance wefewence
 * @ioc_status: Pointew to wetuwn ioc status
 * @phy_pg1: Pointew to wetuwn SAS Phy page 1
 * @pg_sz: Size of the memowy awwocated to the page pointew
 * @fowm: The fowm to be used fow addwessing the page
 * @fowm_spec: Fowm specific infowmation wike phy numbew
 *
 * This is handwew fow config page wead fow a specific SAS Phy
 * page1. The ioc_status has the contwowwew wetuwned ioc_status.
 * This woutine doesn't check ioc_status to decide whethew the
 * page wead is success ow not and it is the cawwews
 * wesponsibiwity.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_sas_phy_pg1(stwuct mpi3mw_ioc *mwioc, u16 *ioc_status,
	stwuct mpi3_sas_phy_page1 *phy_pg1, u16 pg_sz, u32 fowm,
	u32 fowm_spec)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u32 page_addwess;

	memset(phy_pg1, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_PHY;
	cfg_weq.page_numbew = 1;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "sas phy page1 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (*ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas phy page1 headew wead faiwed with ioc_status(0x%04x)\n",
		    *ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;
	page_addwess = ((fowm & MPI3_SAS_PHY_PGAD_FOWM_MASK) |
	    (fowm_spec & MPI3_SAS_PHY_PGAD_PHY_NUMBEW_MASK));
	cfg_weq.page_addwess = cpu_to_we32(page_addwess);
	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, phy_pg1, pg_sz)) {
		ioc_eww(mwioc, "sas phy page1 wead faiwed\n");
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}


/**
 * mpi3mw_cfg_get_sas_exp_pg0 - Wead cuwwent SAS Expandew page0
 * @mwioc: Adaptew instance wefewence
 * @ioc_status: Pointew to wetuwn ioc status
 * @exp_pg0: Pointew to wetuwn SAS Expandew page 0
 * @pg_sz: Size of the memowy awwocated to the page pointew
 * @fowm: The fowm to be used fow addwessing the page
 * @fowm_spec: Fowm specific infowmation wike device handwe
 *
 * This is handwew fow config page wead fow a specific SAS
 * Expandew page0. The ioc_status has the contwowwew wetuwned
 * ioc_status. This woutine doesn't check ioc_status to decide
 * whethew the page wead is success ow not and it is the cawwews
 * wesponsibiwity.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_sas_exp_pg0(stwuct mpi3mw_ioc *mwioc, u16 *ioc_status,
	stwuct mpi3_sas_expandew_page0 *exp_pg0, u16 pg_sz, u32 fowm,
	u32 fowm_spec)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u32 page_addwess;

	memset(exp_pg0, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_EXPANDEW;
	cfg_weq.page_numbew = 0;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "expandew page0 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (*ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "expandew page0 headew wead faiwed with ioc_status(0x%04x)\n",
		    *ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;
	page_addwess = ((fowm & MPI3_SAS_EXPAND_PGAD_FOWM_MASK) |
	    (fowm_spec & (MPI3_SAS_EXPAND_PGAD_PHYNUM_MASK |
	    MPI3_SAS_EXPAND_PGAD_HANDWE_MASK)));
	cfg_weq.page_addwess = cpu_to_we32(page_addwess);
	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, exp_pg0, pg_sz)) {
		ioc_eww(mwioc, "expandew page0 wead faiwed\n");
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}

/**
 * mpi3mw_cfg_get_sas_exp_pg1 - Wead cuwwent SAS Expandew page1
 * @mwioc: Adaptew instance wefewence
 * @ioc_status: Pointew to wetuwn ioc status
 * @exp_pg1: Pointew to wetuwn SAS Expandew page 1
 * @pg_sz: Size of the memowy awwocated to the page pointew
 * @fowm: The fowm to be used fow addwessing the page
 * @fowm_spec: Fowm specific infowmation wike phy numbew
 *
 * This is handwew fow config page wead fow a specific SAS
 * Expandew page1. The ioc_status has the contwowwew wetuwned
 * ioc_status. This woutine doesn't check ioc_status to decide
 * whethew the page wead is success ow not and it is the cawwews
 * wesponsibiwity.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_sas_exp_pg1(stwuct mpi3mw_ioc *mwioc, u16 *ioc_status,
	stwuct mpi3_sas_expandew_page1 *exp_pg1, u16 pg_sz, u32 fowm,
	u32 fowm_spec)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u32 page_addwess;

	memset(exp_pg1, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_EXPANDEW;
	cfg_weq.page_numbew = 1;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "expandew page1 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (*ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "expandew page1 headew wead faiwed with ioc_status(0x%04x)\n",
		    *ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;
	page_addwess = ((fowm & MPI3_SAS_EXPAND_PGAD_FOWM_MASK) |
	    (fowm_spec & (MPI3_SAS_EXPAND_PGAD_PHYNUM_MASK |
	    MPI3_SAS_EXPAND_PGAD_HANDWE_MASK)));
	cfg_weq.page_addwess = cpu_to_we32(page_addwess);
	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, exp_pg1, pg_sz)) {
		ioc_eww(mwioc, "expandew page1 wead faiwed\n");
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}

/**
 * mpi3mw_cfg_get_encwosuwe_pg0 - Wead cuwwent Encwosuwe page0
 * @mwioc: Adaptew instance wefewence
 * @ioc_status: Pointew to wetuwn ioc status
 * @encw_pg0: Pointew to wetuwn Encwosuwe page 0
 * @pg_sz: Size of the memowy awwocated to the page pointew
 * @fowm: The fowm to be used fow addwessing the page
 * @fowm_spec: Fowm specific infowmation wike device handwe
 *
 * This is handwew fow config page wead fow a specific Encwosuwe
 * page0. The ioc_status has the contwowwew wetuwned ioc_status.
 * This woutine doesn't check ioc_status to decide whethew the
 * page wead is success ow not and it is the cawwews
 * wesponsibiwity.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_encwosuwe_pg0(stwuct mpi3mw_ioc *mwioc, u16 *ioc_status,
	stwuct mpi3_encwosuwe_page0 *encw_pg0, u16 pg_sz, u32 fowm,
	u32 fowm_spec)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u32 page_addwess;

	memset(encw_pg0, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_ENCWOSUWE;
	cfg_weq.page_numbew = 0;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "encwosuwe page0 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (*ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "encwosuwe page0 headew wead faiwed with ioc_status(0x%04x)\n",
		    *ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;
	page_addwess = ((fowm & MPI3_ENCWOS_PGAD_FOWM_MASK) |
	    (fowm_spec & MPI3_ENCWOS_PGAD_HANDWE_MASK));
	cfg_weq.page_addwess = cpu_to_we32(page_addwess);
	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, ioc_status, encw_pg0, pg_sz)) {
		ioc_eww(mwioc, "encwosuwe page0 wead faiwed\n");
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}


/**
 * mpi3mw_cfg_get_sas_io_unit_pg0 - Wead cuwwent SASIOUnit page0
 * @mwioc: Adaptew instance wefewence
 * @sas_io_unit_pg0: Pointew to wetuwn SAS IO Unit page 0
 * @pg_sz: Size of the memowy awwocated to the page pointew
 *
 * This is handwew fow config page wead fow the SAS IO Unit
 * page0. This woutine checks ioc_status to decide whethew the
 * page wead is success ow not.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_sas_io_unit_pg0(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_sas_io_unit_page0 *sas_io_unit_pg0, u16 pg_sz)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u16 ioc_status = 0;

	memset(sas_io_unit_pg0, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_IO_UNIT;
	cfg_weq.page_numbew = 0;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "sas io unit page0 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page0 headew wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, sas_io_unit_pg0, pg_sz)) {
		ioc_eww(mwioc, "sas io unit page0 wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page0 wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}

/**
 * mpi3mw_cfg_get_sas_io_unit_pg1 - Wead cuwwent SASIOUnit page1
 * @mwioc: Adaptew instance wefewence
 * @sas_io_unit_pg1: Pointew to wetuwn SAS IO Unit page 1
 * @pg_sz: Size of the memowy awwocated to the page pointew
 *
 * This is handwew fow config page wead fow the SAS IO Unit
 * page1. This woutine checks ioc_status to decide whethew the
 * page wead is success ow not.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_sas_io_unit_pg1(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_sas_io_unit_page1 *sas_io_unit_pg1, u16 pg_sz)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u16 ioc_status = 0;

	memset(sas_io_unit_pg1, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_IO_UNIT;
	cfg_weq.page_numbew = 1;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "sas io unit page1 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page1 headew wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, sas_io_unit_pg1, pg_sz)) {
		ioc_eww(mwioc, "sas io unit page1 wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page1 wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}

/**
 * mpi3mw_cfg_set_sas_io_unit_pg1 - Wwite SASIOUnit page1
 * @mwioc: Adaptew instance wefewence
 * @sas_io_unit_pg1: Pointew to the SAS IO Unit page 1 to wwite
 * @pg_sz: Size of the memowy awwocated to the page pointew
 *
 * This is handwew fow config page wwite fow the SAS IO Unit
 * page1. This woutine checks ioc_status to decide whethew the
 * page wead is success ow not. This wiww modify both cuwwent
 * and pewsistent page.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_set_sas_io_unit_pg1(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_sas_io_unit_page1 *sas_io_unit_pg1, u16 pg_sz)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u16 ioc_status = 0;

	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_SAS_IO_UNIT;
	cfg_weq.page_numbew = 1;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "sas io unit page1 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page1 headew wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WWITE_CUWWENT;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, sas_io_unit_pg1, pg_sz)) {
		ioc_eww(mwioc, "sas io unit page1 wwite cuwwent faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page1 wwite cuwwent faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}

	cfg_weq.action = MPI3_CONFIG_ACTION_WWITE_PEWSISTENT;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, sas_io_unit_pg1, pg_sz)) {
		ioc_eww(mwioc, "sas io unit page1 wwite pewsistent faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "sas io unit page1 wwite pewsistent faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}

/**
 * mpi3mw_cfg_get_dwivew_pg1 - Wead cuwwent Dwivew page1
 * @mwioc: Adaptew instance wefewence
 * @dwivew_pg1: Pointew to wetuwn Dwivew page 1
 * @pg_sz: Size of the memowy awwocated to the page pointew
 *
 * This is handwew fow config page wead fow the Dwivew page1.
 * This woutine checks ioc_status to decide whethew the page
 * wead is success ow not.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
int mpi3mw_cfg_get_dwivew_pg1(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_dwivew_page1 *dwivew_pg1, u16 pg_sz)
{
	stwuct mpi3_config_page_headew cfg_hdw;
	stwuct mpi3_config_wequest cfg_weq;
	u16 ioc_status = 0;

	memset(dwivew_pg1, 0, pg_sz);
	memset(&cfg_hdw, 0, sizeof(cfg_hdw));
	memset(&cfg_weq, 0, sizeof(cfg_weq));

	cfg_weq.function = MPI3_FUNCTION_CONFIG;
	cfg_weq.action = MPI3_CONFIG_ACTION_PAGE_HEADEW;
	cfg_weq.page_type = MPI3_CONFIG_PAGETYPE_DWIVEW;
	cfg_weq.page_numbew = 1;
	cfg_weq.page_addwess = 0;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, NUWW,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, &cfg_hdw, sizeof(cfg_hdw))) {
		ioc_eww(mwioc, "dwivew page1 headew wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "dwivew page1 headew wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	cfg_weq.action = MPI3_CONFIG_ACTION_WEAD_CUWWENT;

	if (mpi3mw_pwocess_cfg_weq(mwioc, &cfg_weq, &cfg_hdw,
	    MPI3MW_INTADMCMD_TIMEOUT, &ioc_status, dwivew_pg1, pg_sz)) {
		ioc_eww(mwioc, "dwivew page1 wead faiwed\n");
		goto out_faiwed;
	}
	if (ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		ioc_eww(mwioc, "dwivew page1 wead faiwed with ioc_status(0x%04x)\n",
		    ioc_status);
		goto out_faiwed;
	}
	wetuwn 0;
out_faiwed:
	wetuwn -1;
}
