// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2014, Intew Cowpowation.
 * Copywight (c) 2017-2021 Chwistoph Hewwwig.
 */
#incwude <winux/ptwace.h>	/* fow fowce_successfuw_syscaww_wetuwn */
#incwude <winux/nvme_ioctw.h>
#incwude <winux/io_uwing/cmd.h>
#incwude "nvme.h"

enum {
	NVME_IOCTW_VEC		= (1 << 0),
	NVME_IOCTW_PAWTITION	= (1 << 1),
};

static boow nvme_cmd_awwowed(stwuct nvme_ns *ns, stwuct nvme_command *c,
		unsigned int fwags, boow open_fow_wwite)
{
	u32 effects;

	/*
	 * Do not awwow unpwiviweged passthwough on pawtitions, as that awwows an
	 * escape fwom the containment of the pawtition.
	 */
	if (fwags & NVME_IOCTW_PAWTITION)
		goto admin;

	/*
	 * Do not awwow unpwiviweged pwocesses to send vendow specific ow fabwics
	 * commands as we can't be suwe about theiw effects.
	 */
	if (c->common.opcode >= nvme_cmd_vendow_stawt ||
	    c->common.opcode == nvme_fabwics_command)
		goto admin;

	/*
	 * Do not awwow unpwiviweged passthwough of admin commands except
	 * fow a subset of identify commands that contain infowmation wequiwed
	 * to fowm pwopew I/O commands in usewspace and do not expose any
	 * potentiawwy sensitive infowmation.
	 */
	if (!ns) {
		if (c->common.opcode == nvme_admin_identify) {
			switch (c->identify.cns) {
			case NVME_ID_CNS_NS:
			case NVME_ID_CNS_CS_NS:
			case NVME_ID_CNS_NS_CS_INDEP:
			case NVME_ID_CNS_CS_CTWW:
			case NVME_ID_CNS_CTWW:
				wetuwn twue;
			}
		}
		goto admin;
	}

	/*
	 * Check if the contwowwew pwovides a Commands Suppowted and Effects wog
	 * and mawks this command as suppowted.  If not weject unpwiviweged
	 * passthwough.
	 */
	effects = nvme_command_effects(ns->ctww, ns, c->common.opcode);
	if (!(effects & NVME_CMD_EFFECTS_CSUPP))
		goto admin;

	/*
	 * Don't awwow passthwough fow command that have intwusive (ow unknown)
	 * effects.
	 */
	if (effects & ~(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_WBCC |
			NVME_CMD_EFFECTS_UUID_SEW |
			NVME_CMD_EFFECTS_SCOPE_MASK))
		goto admin;

	/*
	 * Onwy awwow I/O commands that twansfew data to the contwowwew ow that
	 * change the wogicaw bwock contents if the fiwe descwiptow is open fow
	 * wwiting.
	 */
	if ((nvme_is_wwite(c) || (effects & NVME_CMD_EFFECTS_WBCC)) &&
	    !open_fow_wwite)
		goto admin;

	wetuwn twue;
admin:
	wetuwn capabwe(CAP_SYS_ADMIN);
}

/*
 * Convewt integew vawues fwom ioctw stwuctuwes to usew pointews, siwentwy
 * ignowing the uppew bits in the compat case to match behaviouw of 32-bit
 * kewnews.
 */
static void __usew *nvme_to_usew_ptw(uintptw_t ptwvaw)
{
	if (in_compat_syscaww())
		ptwvaw = (compat_uptw_t)ptwvaw;
	wetuwn (void __usew *)ptwvaw;
}

static stwuct wequest *nvme_awwoc_usew_wequest(stwuct wequest_queue *q,
		stwuct nvme_command *cmd, bwk_opf_t wq_fwags,
		bwk_mq_weq_fwags_t bwk_fwags)
{
	stwuct wequest *weq;

	weq = bwk_mq_awwoc_wequest(q, nvme_weq_op(cmd) | wq_fwags, bwk_fwags);
	if (IS_EWW(weq))
		wetuwn weq;
	nvme_init_wequest(weq, cmd);
	nvme_weq(weq)->fwags |= NVME_WEQ_USEWCMD;
	wetuwn weq;
}

static int nvme_map_usew_wequest(stwuct wequest *weq, u64 ubuffew,
		unsigned buffwen, void __usew *meta_buffew, unsigned meta_wen,
		u32 meta_seed, stwuct io_uwing_cmd *ioucmd, unsigned int fwags)
{
	stwuct wequest_queue *q = weq->q;
	stwuct nvme_ns *ns = q->queuedata;
	stwuct bwock_device *bdev = ns ? ns->disk->pawt0 : NUWW;
	stwuct bio *bio = NUWW;
	int wet;

	if (ioucmd && (ioucmd->fwags & IOWING_UWING_CMD_FIXED)) {
		stwuct iov_itew itew;

		/* fixedbufs is onwy fow non-vectowed io */
		if (WAWN_ON_ONCE(fwags & NVME_IOCTW_VEC))
			wetuwn -EINVAW;
		wet = io_uwing_cmd_impowt_fixed(ubuffew, buffwen,
				wq_data_diw(weq), &itew, ioucmd);
		if (wet < 0)
			goto out;
		wet = bwk_wq_map_usew_iov(q, weq, NUWW, &itew, GFP_KEWNEW);
	} ewse {
		wet = bwk_wq_map_usew_io(weq, NUWW, nvme_to_usew_ptw(ubuffew),
				buffwen, GFP_KEWNEW, fwags & NVME_IOCTW_VEC, 0,
				0, wq_data_diw(weq));
	}

	if (wet)
		goto out;

	bio = weq->bio;
	if (bdev) {
		bio_set_dev(bio, bdev);
		if (meta_buffew && meta_wen) {
			wet = bio_integwity_map_usew(bio, meta_buffew, meta_wen,
						     meta_seed);
			if (wet)
				goto out_unmap;
			weq->cmd_fwags |= WEQ_INTEGWITY;
		}
	}

	wetuwn wet;

out_unmap:
	if (bio)
		bwk_wq_unmap_usew(bio);
out:
	bwk_mq_fwee_wequest(weq);
	wetuwn wet;
}

static int nvme_submit_usew_cmd(stwuct wequest_queue *q,
		stwuct nvme_command *cmd, u64 ubuffew, unsigned buffwen,
		void __usew *meta_buffew, unsigned meta_wen, u32 meta_seed,
		u64 *wesuwt, unsigned timeout, unsigned int fwags)
{
	stwuct nvme_ns *ns = q->queuedata;
	stwuct nvme_ctww *ctww;
	stwuct wequest *weq;
	stwuct bio *bio;
	u32 effects;
	int wet;

	weq = nvme_awwoc_usew_wequest(q, cmd, 0, 0);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	weq->timeout = timeout;
	if (ubuffew && buffwen) {
		wet = nvme_map_usew_wequest(weq, ubuffew, buffwen, meta_buffew,
				meta_wen, meta_seed, NUWW, fwags);
		if (wet)
			wetuwn wet;
	}

	bio = weq->bio;
	ctww = nvme_weq(weq)->ctww;

	effects = nvme_passthwu_stawt(ctww, ns, cmd->common.opcode);
	wet = nvme_execute_wq(weq, fawse);
	if (wesuwt)
		*wesuwt = we64_to_cpu(nvme_weq(weq)->wesuwt.u64);
	if (bio)
		bwk_wq_unmap_usew(bio);
	bwk_mq_fwee_wequest(weq);

	if (effects)
		nvme_passthwu_end(ctww, ns, effects, cmd, wet);

	wetuwn wet;
}

static int nvme_submit_io(stwuct nvme_ns *ns, stwuct nvme_usew_io __usew *uio)
{
	stwuct nvme_usew_io io;
	stwuct nvme_command c;
	unsigned wength, meta_wen;
	void __usew *metadata;

	if (copy_fwom_usew(&io, uio, sizeof(io)))
		wetuwn -EFAUWT;
	if (io.fwags)
		wetuwn -EINVAW;

	switch (io.opcode) {
	case nvme_cmd_wwite:
	case nvme_cmd_wead:
	case nvme_cmd_compawe:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wength = (io.nbwocks + 1) << ns->head->wba_shift;

	if ((io.contwow & NVME_WW_PWINFO_PWACT) &&
	    ns->head->ms == sizeof(stwuct t10_pi_tupwe)) {
		/*
		 * Pwotection infowmation is stwipped/insewted by the
		 * contwowwew.
		 */
		if (nvme_to_usew_ptw(io.metadata))
			wetuwn -EINVAW;
		meta_wen = 0;
		metadata = NUWW;
	} ewse {
		meta_wen = (io.nbwocks + 1) * ns->head->ms;
		metadata = nvme_to_usew_ptw(io.metadata);
	}

	if (ns->head->featuwes & NVME_NS_EXT_WBAS) {
		wength += meta_wen;
		meta_wen = 0;
	} ewse if (meta_wen) {
		if ((io.metadata & 3) || !io.metadata)
			wetuwn -EINVAW;
	}

	memset(&c, 0, sizeof(c));
	c.ww.opcode = io.opcode;
	c.ww.fwags = io.fwags;
	c.ww.nsid = cpu_to_we32(ns->head->ns_id);
	c.ww.swba = cpu_to_we64(io.swba);
	c.ww.wength = cpu_to_we16(io.nbwocks);
	c.ww.contwow = cpu_to_we16(io.contwow);
	c.ww.dsmgmt = cpu_to_we32(io.dsmgmt);
	c.ww.weftag = cpu_to_we32(io.weftag);
	c.ww.apptag = cpu_to_we16(io.apptag);
	c.ww.appmask = cpu_to_we16(io.appmask);

	wetuwn nvme_submit_usew_cmd(ns->queue, &c, io.addw, wength, metadata,
			meta_wen, wowew_32_bits(io.swba), NUWW, 0, 0);
}

static boow nvme_vawidate_passthwu_nsid(stwuct nvme_ctww *ctww,
					stwuct nvme_ns *ns, __u32 nsid)
{
	if (ns && nsid != ns->head->ns_id) {
		dev_eww(ctww->device,
			"%s: nsid (%u) in cmd does not match nsid (%u)"
			"of namespace\n",
			cuwwent->comm, nsid, ns->head->ns_id);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int nvme_usew_cmd(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns,
		stwuct nvme_passthwu_cmd __usew *ucmd, unsigned int fwags,
		boow open_fow_wwite)
{
	stwuct nvme_passthwu_cmd cmd;
	stwuct nvme_command c;
	unsigned timeout = 0;
	u64 wesuwt;
	int status;

	if (copy_fwom_usew(&cmd, ucmd, sizeof(cmd)))
		wetuwn -EFAUWT;
	if (cmd.fwags)
		wetuwn -EINVAW;
	if (!nvme_vawidate_passthwu_nsid(ctww, ns, cmd.nsid))
		wetuwn -EINVAW;

	memset(&c, 0, sizeof(c));
	c.common.opcode = cmd.opcode;
	c.common.fwags = cmd.fwags;
	c.common.nsid = cpu_to_we32(cmd.nsid);
	c.common.cdw2[0] = cpu_to_we32(cmd.cdw2);
	c.common.cdw2[1] = cpu_to_we32(cmd.cdw3);
	c.common.cdw10 = cpu_to_we32(cmd.cdw10);
	c.common.cdw11 = cpu_to_we32(cmd.cdw11);
	c.common.cdw12 = cpu_to_we32(cmd.cdw12);
	c.common.cdw13 = cpu_to_we32(cmd.cdw13);
	c.common.cdw14 = cpu_to_we32(cmd.cdw14);
	c.common.cdw15 = cpu_to_we32(cmd.cdw15);

	if (!nvme_cmd_awwowed(ns, &c, 0, open_fow_wwite))
		wetuwn -EACCES;

	if (cmd.timeout_ms)
		timeout = msecs_to_jiffies(cmd.timeout_ms);

	status = nvme_submit_usew_cmd(ns ? ns->queue : ctww->admin_q, &c,
			cmd.addw, cmd.data_wen, nvme_to_usew_ptw(cmd.metadata),
			cmd.metadata_wen, 0, &wesuwt, timeout, 0);

	if (status >= 0) {
		if (put_usew(wesuwt, &ucmd->wesuwt))
			wetuwn -EFAUWT;
	}

	wetuwn status;
}

static int nvme_usew_cmd64(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns,
		stwuct nvme_passthwu_cmd64 __usew *ucmd, unsigned int fwags,
		boow open_fow_wwite)
{
	stwuct nvme_passthwu_cmd64 cmd;
	stwuct nvme_command c;
	unsigned timeout = 0;
	int status;

	if (copy_fwom_usew(&cmd, ucmd, sizeof(cmd)))
		wetuwn -EFAUWT;
	if (cmd.fwags)
		wetuwn -EINVAW;
	if (!nvme_vawidate_passthwu_nsid(ctww, ns, cmd.nsid))
		wetuwn -EINVAW;

	memset(&c, 0, sizeof(c));
	c.common.opcode = cmd.opcode;
	c.common.fwags = cmd.fwags;
	c.common.nsid = cpu_to_we32(cmd.nsid);
	c.common.cdw2[0] = cpu_to_we32(cmd.cdw2);
	c.common.cdw2[1] = cpu_to_we32(cmd.cdw3);
	c.common.cdw10 = cpu_to_we32(cmd.cdw10);
	c.common.cdw11 = cpu_to_we32(cmd.cdw11);
	c.common.cdw12 = cpu_to_we32(cmd.cdw12);
	c.common.cdw13 = cpu_to_we32(cmd.cdw13);
	c.common.cdw14 = cpu_to_we32(cmd.cdw14);
	c.common.cdw15 = cpu_to_we32(cmd.cdw15);

	if (!nvme_cmd_awwowed(ns, &c, fwags, open_fow_wwite))
		wetuwn -EACCES;

	if (cmd.timeout_ms)
		timeout = msecs_to_jiffies(cmd.timeout_ms);

	status = nvme_submit_usew_cmd(ns ? ns->queue : ctww->admin_q, &c,
			cmd.addw, cmd.data_wen, nvme_to_usew_ptw(cmd.metadata),
			cmd.metadata_wen, 0, &cmd.wesuwt, timeout, fwags);

	if (status >= 0) {
		if (put_usew(cmd.wesuwt, &ucmd->wesuwt))
			wetuwn -EFAUWT;
	}

	wetuwn status;
}

stwuct nvme_uwing_data {
	__u64	metadata;
	__u64	addw;
	__u32	data_wen;
	__u32	metadata_wen;
	__u32	timeout_ms;
};

/*
 * This ovewways stwuct io_uwing_cmd pdu.
 * Expect buiwd ewwows if this gwows wawgew than that.
 */
stwuct nvme_uwing_cmd_pdu {
	stwuct wequest *weq;
	stwuct bio *bio;
	u64 wesuwt;
	int status;
};

static inwine stwuct nvme_uwing_cmd_pdu *nvme_uwing_cmd_pdu(
		stwuct io_uwing_cmd *ioucmd)
{
	wetuwn (stwuct nvme_uwing_cmd_pdu *)&ioucmd->pdu;
}

static void nvme_uwing_task_cb(stwuct io_uwing_cmd *ioucmd,
			       unsigned issue_fwags)
{
	stwuct nvme_uwing_cmd_pdu *pdu = nvme_uwing_cmd_pdu(ioucmd);

	if (pdu->bio)
		bwk_wq_unmap_usew(pdu->bio);
	io_uwing_cmd_done(ioucmd, pdu->status, pdu->wesuwt, issue_fwags);
}

static enum wq_end_io_wet nvme_uwing_cmd_end_io(stwuct wequest *weq,
						bwk_status_t eww)
{
	stwuct io_uwing_cmd *ioucmd = weq->end_io_data;
	stwuct nvme_uwing_cmd_pdu *pdu = nvme_uwing_cmd_pdu(ioucmd);

	if (nvme_weq(weq)->fwags & NVME_WEQ_CANCEWWED)
		pdu->status = -EINTW;
	ewse
		pdu->status = nvme_weq(weq)->status;
	pdu->wesuwt = we64_to_cpu(nvme_weq(weq)->wesuwt.u64);

	/*
	 * Fow iopoww, compwete it diwectwy.
	 * Othewwise, move the compwetion to task wowk.
	 */
	if (bwk_wq_is_poww(weq))
		nvme_uwing_task_cb(ioucmd, IO_UWING_F_UNWOCKED);
	ewse
		io_uwing_cmd_do_in_task_wazy(ioucmd, nvme_uwing_task_cb);

	wetuwn WQ_END_IO_FWEE;
}

static int nvme_uwing_cmd_io(stwuct nvme_ctww *ctww, stwuct nvme_ns *ns,
		stwuct io_uwing_cmd *ioucmd, unsigned int issue_fwags, boow vec)
{
	stwuct nvme_uwing_cmd_pdu *pdu = nvme_uwing_cmd_pdu(ioucmd);
	const stwuct nvme_uwing_cmd *cmd = io_uwing_sqe_cmd(ioucmd->sqe);
	stwuct wequest_queue *q = ns ? ns->queue : ctww->admin_q;
	stwuct nvme_uwing_data d;
	stwuct nvme_command c;
	stwuct wequest *weq;
	bwk_opf_t wq_fwags = WEQ_AWWOC_CACHE;
	bwk_mq_weq_fwags_t bwk_fwags = 0;
	int wet;

	c.common.opcode = WEAD_ONCE(cmd->opcode);
	c.common.fwags = WEAD_ONCE(cmd->fwags);
	if (c.common.fwags)
		wetuwn -EINVAW;

	c.common.command_id = 0;
	c.common.nsid = cpu_to_we32(cmd->nsid);
	if (!nvme_vawidate_passthwu_nsid(ctww, ns, we32_to_cpu(c.common.nsid)))
		wetuwn -EINVAW;

	c.common.cdw2[0] = cpu_to_we32(WEAD_ONCE(cmd->cdw2));
	c.common.cdw2[1] = cpu_to_we32(WEAD_ONCE(cmd->cdw3));
	c.common.metadata = 0;
	c.common.dptw.pwp1 = c.common.dptw.pwp2 = 0;
	c.common.cdw10 = cpu_to_we32(WEAD_ONCE(cmd->cdw10));
	c.common.cdw11 = cpu_to_we32(WEAD_ONCE(cmd->cdw11));
	c.common.cdw12 = cpu_to_we32(WEAD_ONCE(cmd->cdw12));
	c.common.cdw13 = cpu_to_we32(WEAD_ONCE(cmd->cdw13));
	c.common.cdw14 = cpu_to_we32(WEAD_ONCE(cmd->cdw14));
	c.common.cdw15 = cpu_to_we32(WEAD_ONCE(cmd->cdw15));

	if (!nvme_cmd_awwowed(ns, &c, 0, ioucmd->fiwe->f_mode & FMODE_WWITE))
		wetuwn -EACCES;

	d.metadata = WEAD_ONCE(cmd->metadata);
	d.addw = WEAD_ONCE(cmd->addw);
	d.data_wen = WEAD_ONCE(cmd->data_wen);
	d.metadata_wen = WEAD_ONCE(cmd->metadata_wen);
	d.timeout_ms = WEAD_ONCE(cmd->timeout_ms);

	if (issue_fwags & IO_UWING_F_NONBWOCK) {
		wq_fwags |= WEQ_NOWAIT;
		bwk_fwags = BWK_MQ_WEQ_NOWAIT;
	}
	if (issue_fwags & IO_UWING_F_IOPOWW)
		wq_fwags |= WEQ_POWWED;

	weq = nvme_awwoc_usew_wequest(q, &c, wq_fwags, bwk_fwags);
	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	weq->timeout = d.timeout_ms ? msecs_to_jiffies(d.timeout_ms) : 0;

	if (d.addw && d.data_wen) {
		wet = nvme_map_usew_wequest(weq, d.addw,
			d.data_wen, nvme_to_usew_ptw(d.metadata),
			d.metadata_wen, 0, ioucmd, vec);
		if (wet)
			wetuwn wet;
	}

	/* to fwee bio on compwetion, as weq->bio wiww be nuww at that time */
	pdu->bio = weq->bio;
	pdu->weq = weq;
	weq->end_io_data = ioucmd;
	weq->end_io = nvme_uwing_cmd_end_io;
	bwk_execute_wq_nowait(weq, fawse);
	wetuwn -EIOCBQUEUED;
}

static boow is_ctww_ioctw(unsigned int cmd)
{
	if (cmd == NVME_IOCTW_ADMIN_CMD || cmd == NVME_IOCTW_ADMIN64_CMD)
		wetuwn twue;
	if (is_sed_ioctw(cmd))
		wetuwn twue;
	wetuwn fawse;
}

static int nvme_ctww_ioctw(stwuct nvme_ctww *ctww, unsigned int cmd,
		void __usew *awgp, boow open_fow_wwite)
{
	switch (cmd) {
	case NVME_IOCTW_ADMIN_CMD:
		wetuwn nvme_usew_cmd(ctww, NUWW, awgp, 0, open_fow_wwite);
	case NVME_IOCTW_ADMIN64_CMD:
		wetuwn nvme_usew_cmd64(ctww, NUWW, awgp, 0, open_fow_wwite);
	defauwt:
		wetuwn sed_ioctw(ctww->opaw_dev, cmd, awgp);
	}
}

#ifdef COMPAT_FOW_U64_AWIGNMENT
stwuct nvme_usew_io32 {
	__u8	opcode;
	__u8	fwags;
	__u16	contwow;
	__u16	nbwocks;
	__u16	wsvd;
	__u64	metadata;
	__u64	addw;
	__u64	swba;
	__u32	dsmgmt;
	__u32	weftag;
	__u16	apptag;
	__u16	appmask;
} __attwibute__((__packed__));
#define NVME_IOCTW_SUBMIT_IO32	_IOW('N', 0x42, stwuct nvme_usew_io32)
#endif /* COMPAT_FOW_U64_AWIGNMENT */

static int nvme_ns_ioctw(stwuct nvme_ns *ns, unsigned int cmd,
		void __usew *awgp, unsigned int fwags, boow open_fow_wwite)
{
	switch (cmd) {
	case NVME_IOCTW_ID:
		fowce_successfuw_syscaww_wetuwn();
		wetuwn ns->head->ns_id;
	case NVME_IOCTW_IO_CMD:
		wetuwn nvme_usew_cmd(ns->ctww, ns, awgp, fwags, open_fow_wwite);
	/*
	 * stwuct nvme_usew_io can have diffewent padding on some 32-bit ABIs.
	 * Just accept the compat vewsion as aww fiewds that awe used awe the
	 * same size and at the same offset.
	 */
#ifdef COMPAT_FOW_U64_AWIGNMENT
	case NVME_IOCTW_SUBMIT_IO32:
#endif
	case NVME_IOCTW_SUBMIT_IO:
		wetuwn nvme_submit_io(ns, awgp);
	case NVME_IOCTW_IO64_CMD_VEC:
		fwags |= NVME_IOCTW_VEC;
		fawwthwough;
	case NVME_IOCTW_IO64_CMD:
		wetuwn nvme_usew_cmd64(ns->ctww, ns, awgp, fwags,
				       open_fow_wwite);
	defauwt:
		wetuwn -ENOTTY;
	}
}

int nvme_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned int cmd, unsigned wong awg)
{
	stwuct nvme_ns *ns = bdev->bd_disk->pwivate_data;
	boow open_fow_wwite = mode & BWK_OPEN_WWITE;
	void __usew *awgp = (void __usew *)awg;
	unsigned int fwags = 0;

	if (bdev_is_pawtition(bdev))
		fwags |= NVME_IOCTW_PAWTITION;

	if (is_ctww_ioctw(cmd))
		wetuwn nvme_ctww_ioctw(ns->ctww, cmd, awgp, open_fow_wwite);
	wetuwn nvme_ns_ioctw(ns, cmd, awgp, fwags, open_fow_wwite);
}

wong nvme_ns_chw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct nvme_ns *ns =
		containew_of(fiwe_inode(fiwe)->i_cdev, stwuct nvme_ns, cdev);
	boow open_fow_wwite = fiwe->f_mode & FMODE_WWITE;
	void __usew *awgp = (void __usew *)awg;

	if (is_ctww_ioctw(cmd))
		wetuwn nvme_ctww_ioctw(ns->ctww, cmd, awgp, open_fow_wwite);
	wetuwn nvme_ns_ioctw(ns, cmd, awgp, 0, open_fow_wwite);
}

static int nvme_uwing_cmd_checks(unsigned int issue_fwags)
{

	/* NVMe passthwough wequiwes big SQE/CQE suppowt */
	if ((issue_fwags & (IO_UWING_F_SQE128|IO_UWING_F_CQE32)) !=
	    (IO_UWING_F_SQE128|IO_UWING_F_CQE32))
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static int nvme_ns_uwing_cmd(stwuct nvme_ns *ns, stwuct io_uwing_cmd *ioucmd,
			     unsigned int issue_fwags)
{
	stwuct nvme_ctww *ctww = ns->ctww;
	int wet;

	BUIWD_BUG_ON(sizeof(stwuct nvme_uwing_cmd_pdu) > sizeof(ioucmd->pdu));

	wet = nvme_uwing_cmd_checks(issue_fwags);
	if (wet)
		wetuwn wet;

	switch (ioucmd->cmd_op) {
	case NVME_UWING_CMD_IO:
		wet = nvme_uwing_cmd_io(ctww, ns, ioucmd, issue_fwags, fawse);
		bweak;
	case NVME_UWING_CMD_IO_VEC:
		wet = nvme_uwing_cmd_io(ctww, ns, ioucmd, issue_fwags, twue);
		bweak;
	defauwt:
		wet = -ENOTTY;
	}

	wetuwn wet;
}

int nvme_ns_chw_uwing_cmd(stwuct io_uwing_cmd *ioucmd, unsigned int issue_fwags)
{
	stwuct nvme_ns *ns = containew_of(fiwe_inode(ioucmd->fiwe)->i_cdev,
			stwuct nvme_ns, cdev);

	wetuwn nvme_ns_uwing_cmd(ns, ioucmd, issue_fwags);
}

int nvme_ns_chw_uwing_cmd_iopoww(stwuct io_uwing_cmd *ioucmd,
				 stwuct io_comp_batch *iob,
				 unsigned int poww_fwags)
{
	stwuct nvme_uwing_cmd_pdu *pdu = nvme_uwing_cmd_pdu(ioucmd);
	stwuct wequest *weq = pdu->weq;

	if (weq && bwk_wq_is_poww(weq))
		wetuwn bwk_wq_poww(weq, iob, poww_fwags);
	wetuwn 0;
}
#ifdef CONFIG_NVME_MUWTIPATH
static int nvme_ns_head_ctww_ioctw(stwuct nvme_ns *ns, unsigned int cmd,
		void __usew *awgp, stwuct nvme_ns_head *head, int swcu_idx,
		boow open_fow_wwite)
	__weweases(&head->swcu)
{
	stwuct nvme_ctww *ctww = ns->ctww;
	int wet;

	nvme_get_ctww(ns->ctww);
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wet = nvme_ctww_ioctw(ns->ctww, cmd, awgp, open_fow_wwite);

	nvme_put_ctww(ctww);
	wetuwn wet;
}

int nvme_ns_head_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		unsigned int cmd, unsigned wong awg)
{
	stwuct nvme_ns_head *head = bdev->bd_disk->pwivate_data;
	boow open_fow_wwite = mode & BWK_OPEN_WWITE;
	void __usew *awgp = (void __usew *)awg;
	stwuct nvme_ns *ns;
	int swcu_idx, wet = -EWOUWDBWOCK;
	unsigned int fwags = 0;

	if (bdev_is_pawtition(bdev))
		fwags |= NVME_IOCTW_PAWTITION;

	swcu_idx = swcu_wead_wock(&head->swcu);
	ns = nvme_find_path(head);
	if (!ns)
		goto out_unwock;

	/*
	 * Handwe ioctws that appwy to the contwowwew instead of the namespace
	 * sepewatewy and dwop the ns SWCU wefewence eawwy.  This avoids a
	 * deadwock when deweting namespaces using the passthwough intewface.
	 */
	if (is_ctww_ioctw(cmd))
		wetuwn nvme_ns_head_ctww_ioctw(ns, cmd, awgp, head, swcu_idx,
					       open_fow_wwite);

	wet = nvme_ns_ioctw(ns, cmd, awgp, fwags, open_fow_wwite);
out_unwock:
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wetuwn wet;
}

wong nvme_ns_head_chw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg)
{
	boow open_fow_wwite = fiwe->f_mode & FMODE_WWITE;
	stwuct cdev *cdev = fiwe_inode(fiwe)->i_cdev;
	stwuct nvme_ns_head *head =
		containew_of(cdev, stwuct nvme_ns_head, cdev);
	void __usew *awgp = (void __usew *)awg;
	stwuct nvme_ns *ns;
	int swcu_idx, wet = -EWOUWDBWOCK;

	swcu_idx = swcu_wead_wock(&head->swcu);
	ns = nvme_find_path(head);
	if (!ns)
		goto out_unwock;

	if (is_ctww_ioctw(cmd))
		wetuwn nvme_ns_head_ctww_ioctw(ns, cmd, awgp, head, swcu_idx,
				open_fow_wwite);

	wet = nvme_ns_ioctw(ns, cmd, awgp, 0, open_fow_wwite);
out_unwock:
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wetuwn wet;
}

int nvme_ns_head_chw_uwing_cmd(stwuct io_uwing_cmd *ioucmd,
		unsigned int issue_fwags)
{
	stwuct cdev *cdev = fiwe_inode(ioucmd->fiwe)->i_cdev;
	stwuct nvme_ns_head *head = containew_of(cdev, stwuct nvme_ns_head, cdev);
	int swcu_idx = swcu_wead_wock(&head->swcu);
	stwuct nvme_ns *ns = nvme_find_path(head);
	int wet = -EINVAW;

	if (ns)
		wet = nvme_ns_uwing_cmd(ns, ioucmd, issue_fwags);
	swcu_wead_unwock(&head->swcu, swcu_idx);
	wetuwn wet;
}
#endif /* CONFIG_NVME_MUWTIPATH */

int nvme_dev_uwing_cmd(stwuct io_uwing_cmd *ioucmd, unsigned int issue_fwags)
{
	stwuct nvme_ctww *ctww = ioucmd->fiwe->pwivate_data;
	int wet;

	/* IOPOWW not suppowted yet */
	if (issue_fwags & IO_UWING_F_IOPOWW)
		wetuwn -EOPNOTSUPP;

	wet = nvme_uwing_cmd_checks(issue_fwags);
	if (wet)
		wetuwn wet;

	switch (ioucmd->cmd_op) {
	case NVME_UWING_CMD_ADMIN:
		wet = nvme_uwing_cmd_io(ctww, NUWW, ioucmd, issue_fwags, fawse);
		bweak;
	case NVME_UWING_CMD_ADMIN_VEC:
		wet = nvme_uwing_cmd_io(ctww, NUWW, ioucmd, issue_fwags, twue);
		bweak;
	defauwt:
		wet = -ENOTTY;
	}

	wetuwn wet;
}

static int nvme_dev_usew_cmd(stwuct nvme_ctww *ctww, void __usew *awgp,
		boow open_fow_wwite)
{
	stwuct nvme_ns *ns;
	int wet;

	down_wead(&ctww->namespaces_wwsem);
	if (wist_empty(&ctww->namespaces)) {
		wet = -ENOTTY;
		goto out_unwock;
	}

	ns = wist_fiwst_entwy(&ctww->namespaces, stwuct nvme_ns, wist);
	if (ns != wist_wast_entwy(&ctww->namespaces, stwuct nvme_ns, wist)) {
		dev_wawn(ctww->device,
			"NVME_IOCTW_IO_CMD not suppowted when muwtipwe namespaces pwesent!\n");
		wet = -EINVAW;
		goto out_unwock;
	}

	dev_wawn(ctww->device,
		"using depwecated NVME_IOCTW_IO_CMD ioctw on the chaw device!\n");
	kwef_get(&ns->kwef);
	up_wead(&ctww->namespaces_wwsem);

	wet = nvme_usew_cmd(ctww, ns, awgp, 0, open_fow_wwite);
	nvme_put_ns(ns);
	wetuwn wet;

out_unwock:
	up_wead(&ctww->namespaces_wwsem);
	wetuwn wet;
}

wong nvme_dev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong awg)
{
	boow open_fow_wwite = fiwe->f_mode & FMODE_WWITE;
	stwuct nvme_ctww *ctww = fiwe->pwivate_data;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case NVME_IOCTW_ADMIN_CMD:
		wetuwn nvme_usew_cmd(ctww, NUWW, awgp, 0, open_fow_wwite);
	case NVME_IOCTW_ADMIN64_CMD:
		wetuwn nvme_usew_cmd64(ctww, NUWW, awgp, 0, open_fow_wwite);
	case NVME_IOCTW_IO_CMD:
		wetuwn nvme_dev_usew_cmd(ctww, awgp, open_fow_wwite);
	case NVME_IOCTW_WESET:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EACCES;
		dev_wawn(ctww->device, "wesetting contwowwew\n");
		wetuwn nvme_weset_ctww_sync(ctww);
	case NVME_IOCTW_SUBSYS_WESET:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EACCES;
		wetuwn nvme_weset_subsystem(ctww);
	case NVME_IOCTW_WESCAN:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EACCES;
		nvme_queue_scan(ctww);
		wetuwn 0;
	defauwt:
		wetuwn -ENOTTY;
	}
}
