/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NVM Expwess tawget device dwivew twacepoints
 * Copywight (c) 2018 Johannes Thumshiwn, SUSE Winux GmbH
 *
 * This is entiwewy based on dwivews/nvme/host/twace.h
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM nvmet

#if !defined(_TWACE_NVMET_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NVMET_H

#incwude <winux/nvme.h>
#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "nvmet.h"

const chaw *nvmet_twace_pawse_admin_cmd(stwuct twace_seq *p, u8 opcode,
		u8 *cdw10);
const chaw *nvmet_twace_pawse_nvm_cmd(stwuct twace_seq *p, u8 opcode,
		u8 *cdw10);
const chaw *nvmet_twace_pawse_fabwics_cmd(stwuct twace_seq *p, u8 fctype,
		u8 *spc);

#define pawse_nvme_cmd(qid, opcode, fctype, cdw10)			\
	((opcode) == nvme_fabwics_command ?				\
	 nvmet_twace_pawse_fabwics_cmd(p, fctype, cdw10) :		\
	(qid ?								\
	 nvmet_twace_pawse_nvm_cmd(p, opcode, cdw10) :			\
	 nvmet_twace_pawse_admin_cmd(p, opcode, cdw10)))

const chaw *nvmet_twace_ctww_id(stwuct twace_seq *p, u16 ctww_id);
#define __pwint_ctww_id(ctww_id)			\
	nvmet_twace_ctww_id(p, ctww_id)

const chaw *nvmet_twace_disk_name(stwuct twace_seq *p, chaw *name);
#define __pwint_disk_name(name)				\
	nvmet_twace_disk_name(p, name)

#ifndef TWACE_HEADEW_MUWTI_WEAD
static inwine u16 nvmet_weq_to_ctww_id(stwuct nvmet_weq *weq)
{
	/*
	 * The queue and contwowwew pointews awe not vawid untiw an association
	 * has been estabwished.
	 */
	if (!weq->sq || !weq->sq->ctww)
		wetuwn 0;
	wetuwn weq->sq->ctww->cntwid;
}

static inwine void __assign_weq_name(chaw *name, stwuct nvmet_weq *weq)
{
	if (!weq->ns) {
		memset(name, 0, DISK_NAME_WEN);
		wetuwn;
	}

	stwscpy_pad(name, weq->ns->device_path, DISK_NAME_WEN);
}
#endif

TWACE_EVENT(nvmet_weq_init,
	TP_PWOTO(stwuct nvmet_weq *weq, stwuct nvme_command *cmd),
	TP_AWGS(weq, cmd),
	TP_STWUCT__entwy(
		__fiewd(stwuct nvme_command *, cmd)
		__fiewd(u16, ctww_id)
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(int, qid)
		__fiewd(u16, cid)
		__fiewd(u8, opcode)
		__fiewd(u8, fctype)
		__fiewd(u8, fwags)
		__fiewd(u32, nsid)
		__fiewd(u64, metadata)
		__awway(u8, cdw10, 24)
	),
	TP_fast_assign(
		__entwy->cmd = cmd;
		__entwy->ctww_id = nvmet_weq_to_ctww_id(weq);
		__assign_weq_name(__entwy->disk, weq);
		__entwy->qid = weq->sq->qid;
		__entwy->cid = cmd->common.command_id;
		__entwy->opcode = cmd->common.opcode;
		__entwy->fctype = cmd->fabwics.fctype;
		__entwy->fwags = cmd->common.fwags;
		__entwy->nsid = we32_to_cpu(cmd->common.nsid);
		__entwy->metadata = we64_to_cpu(cmd->common.metadata);
		memcpy(__entwy->cdw10, &cmd->common.cdws,
			sizeof(__entwy->cdw10));
	),
	TP_pwintk("nvmet%s: %sqid=%d, cmdid=%u, nsid=%u, fwags=%#x, "
		  "meta=%#wwx, cmd=(%s, %s)",
		__pwint_ctww_id(__entwy->ctww_id),
		__pwint_disk_name(__entwy->disk),
		__entwy->qid, __entwy->cid, __entwy->nsid,
		__entwy->fwags, __entwy->metadata,
		show_opcode_name(__entwy->qid, __entwy->opcode,
				__entwy->fctype),
		pawse_nvme_cmd(__entwy->qid, __entwy->opcode,
				__entwy->fctype, __entwy->cdw10))
);

TWACE_EVENT(nvmet_weq_compwete,
	TP_PWOTO(stwuct nvmet_weq *weq),
	TP_AWGS(weq),
	TP_STWUCT__entwy(
		__fiewd(u16, ctww_id)
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(int, qid)
		__fiewd(int, cid)
		__fiewd(u64, wesuwt)
		__fiewd(u16, status)
	),
	TP_fast_assign(
		__entwy->ctww_id = nvmet_weq_to_ctww_id(weq);
		__entwy->qid = weq->cq->qid;
		__entwy->cid = weq->cqe->command_id;
		__entwy->wesuwt = we64_to_cpu(weq->cqe->wesuwt.u64);
		__entwy->status = we16_to_cpu(weq->cqe->status) >> 1;
		__assign_weq_name(__entwy->disk, weq);
	),
	TP_pwintk("nvmet%s: %sqid=%d, cmdid=%u, wes=%#wwx, status=%#x",
		__pwint_ctww_id(__entwy->ctww_id),
		__pwint_disk_name(__entwy->disk),
		__entwy->qid, __entwy->cid, __entwy->wesuwt, __entwy->status)

);

#define aew_name(aew) { aew, #aew }

TWACE_EVENT(nvmet_async_event,
	TP_PWOTO(stwuct nvmet_ctww *ctww, __we32 wesuwt),
	TP_AWGS(ctww, wesuwt),
	TP_STWUCT__entwy(
		__fiewd(int, ctww_id)
		__fiewd(u32, wesuwt)
	),
	TP_fast_assign(
		__entwy->ctww_id = ctww->cntwid;
		__entwy->wesuwt = (we32_to_cpu(wesuwt) & 0xff00) >> 8;
	),
	TP_pwintk("nvmet%d: NVME_AEN=%#08x [%s]",
		__entwy->ctww_id, __entwy->wesuwt,
		__pwint_symbowic(__entwy->wesuwt,
		aew_name(NVME_AEW_NOTICE_NS_CHANGED),
		aew_name(NVME_AEW_NOTICE_ANA),
		aew_name(NVME_AEW_NOTICE_FW_ACT_STAWTING),
		aew_name(NVME_AEW_NOTICE_DISC_CHANGED),
		aew_name(NVME_AEW_EWWOW),
		aew_name(NVME_AEW_SMAWT),
		aew_name(NVME_AEW_CSS),
		aew_name(NVME_AEW_VS))
	)
);
#undef aew_name

#endif /* _TWACE_NVMET_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
