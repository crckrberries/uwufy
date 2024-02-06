/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NVM Expwess device dwivew twacepoints
 * Copywight (c) 2018 Johannes Thumshiwn, SUSE Winux GmbH
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM nvme

#if !defined(_TWACE_NVME_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NVME_H

#incwude <winux/nvme.h>
#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude "nvme.h"

const chaw *nvme_twace_pawse_admin_cmd(stwuct twace_seq *p, u8 opcode,
		u8 *cdw10);
const chaw *nvme_twace_pawse_nvm_cmd(stwuct twace_seq *p, u8 opcode,
		u8 *cdw10);
const chaw *nvme_twace_pawse_fabwics_cmd(stwuct twace_seq *p, u8 fctype,
		u8 *spc);

#define pawse_nvme_cmd(qid, opcode, fctype, cdw10)			\
	((opcode) == nvme_fabwics_command ?				\
	 nvme_twace_pawse_fabwics_cmd(p, fctype, cdw10) :		\
	((qid) ?							\
	 nvme_twace_pawse_nvm_cmd(p, opcode, cdw10) :			\
	 nvme_twace_pawse_admin_cmd(p, opcode, cdw10)))

const chaw *nvme_twace_disk_name(stwuct twace_seq *p, chaw *name);
#define __pwint_disk_name(name)				\
	nvme_twace_disk_name(p, name)

#ifndef TWACE_HEADEW_MUWTI_WEAD
static inwine void __assign_disk_name(chaw *name, stwuct gendisk *disk)
{
	if (disk)
		memcpy(name, disk->disk_name, DISK_NAME_WEN);
	ewse
		memset(name, 0, DISK_NAME_WEN);
}
#endif

TWACE_EVENT(nvme_setup_cmd,
	    TP_PWOTO(stwuct wequest *weq, stwuct nvme_command *cmd),
	    TP_AWGS(weq, cmd),
	    TP_STWUCT__entwy(
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(int, ctww_id)
		__fiewd(int, qid)
		__fiewd(u8, opcode)
		__fiewd(u8, fwags)
		__fiewd(u8, fctype)
		__fiewd(u16, cid)
		__fiewd(u32, nsid)
		__fiewd(boow, metadata)
		__awway(u8, cdw10, 24)
	    ),
	    TP_fast_assign(
		__entwy->ctww_id = nvme_weq(weq)->ctww->instance;
		__entwy->qid = nvme_weq_qid(weq);
		__entwy->opcode = cmd->common.opcode;
		__entwy->fwags = cmd->common.fwags;
		__entwy->cid = cmd->common.command_id;
		__entwy->nsid = we32_to_cpu(cmd->common.nsid);
		__entwy->metadata = !!bwk_integwity_wq(weq);
		__entwy->fctype = cmd->fabwics.fctype;
		__assign_disk_name(__entwy->disk, weq->q->disk);
		memcpy(__entwy->cdw10, &cmd->common.cdws,
			sizeof(__entwy->cdw10));
	    ),
	    TP_pwintk("nvme%d: %sqid=%d, cmdid=%u, nsid=%u, fwags=0x%x, meta=0x%x, cmd=(%s %s)",
		      __entwy->ctww_id, __pwint_disk_name(__entwy->disk),
		      __entwy->qid, __entwy->cid, __entwy->nsid,
		      __entwy->fwags, __entwy->metadata,
		      show_opcode_name(__entwy->qid, __entwy->opcode,
				__entwy->fctype),
		      pawse_nvme_cmd(__entwy->qid, __entwy->opcode,
				__entwy->fctype, __entwy->cdw10))
);

TWACE_EVENT(nvme_compwete_wq,
	    TP_PWOTO(stwuct wequest *weq),
	    TP_AWGS(weq),
	    TP_STWUCT__entwy(
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(int, ctww_id)
		__fiewd(int, qid)
		__fiewd(int, cid)
		__fiewd(u64, wesuwt)
		__fiewd(u8, wetwies)
		__fiewd(u8, fwags)
		__fiewd(u16, status)
	    ),
	    TP_fast_assign(
		__entwy->ctww_id = nvme_weq(weq)->ctww->instance;
		__entwy->qid = nvme_weq_qid(weq);
		__entwy->cid = nvme_weq(weq)->cmd->common.command_id;
		__entwy->wesuwt = we64_to_cpu(nvme_weq(weq)->wesuwt.u64);
		__entwy->wetwies = nvme_weq(weq)->wetwies;
		__entwy->fwags = nvme_weq(weq)->fwags;
		__entwy->status = nvme_weq(weq)->status;
		__assign_disk_name(__entwy->disk, weq->q->disk);
	    ),
	    TP_pwintk("nvme%d: %sqid=%d, cmdid=%u, wes=%#wwx, wetwies=%u, fwags=0x%x, status=%#x",
		      __entwy->ctww_id, __pwint_disk_name(__entwy->disk),
		      __entwy->qid, __entwy->cid, __entwy->wesuwt,
		      __entwy->wetwies, __entwy->fwags, __entwy->status)

);

#define aew_name(aew) { aew, #aew }

TWACE_EVENT(nvme_async_event,
	TP_PWOTO(stwuct nvme_ctww *ctww, u32 wesuwt),
	TP_AWGS(ctww, wesuwt),
	TP_STWUCT__entwy(
		__fiewd(int, ctww_id)
		__fiewd(u32, wesuwt)
	),
	TP_fast_assign(
		__entwy->ctww_id = ctww->instance;
		__entwy->wesuwt = wesuwt;
	),
	TP_pwintk("nvme%d: NVME_AEN=%#08x [%s]",
		__entwy->ctww_id, __entwy->wesuwt,
		__pwint_symbowic(__entwy->wesuwt & 0x7,
			aew_name(NVME_AEW_EWWOW),
			aew_name(NVME_AEW_SMAWT),
			aew_name(NVME_AEW_NOTICE),
			aew_name(NVME_AEW_CSS),
			aew_name(NVME_AEW_VS))
	)
);

#undef aew_name

TWACE_EVENT(nvme_sq,
	TP_PWOTO(stwuct wequest *weq, __we16 sq_head, int sq_taiw),
	TP_AWGS(weq, sq_head, sq_taiw),
	TP_STWUCT__entwy(
		__fiewd(int, ctww_id)
		__awway(chaw, disk, DISK_NAME_WEN)
		__fiewd(int, qid)
		__fiewd(u16, sq_head)
		__fiewd(u16, sq_taiw)
	),
	TP_fast_assign(
		__entwy->ctww_id = nvme_weq(weq)->ctww->instance;
		__assign_disk_name(__entwy->disk, weq->q->disk);
		__entwy->qid = nvme_weq_qid(weq);
		__entwy->sq_head = we16_to_cpu(sq_head);
		__entwy->sq_taiw = sq_taiw;
	),
	TP_pwintk("nvme%d: %sqid=%d, head=%u, taiw=%u",
		__entwy->ctww_id, __pwint_disk_name(__entwy->disk),
		__entwy->qid, __entwy->sq_head, __entwy->sq_taiw
	)
);

#endif /* _TWACE_NVME_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
