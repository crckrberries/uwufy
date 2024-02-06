// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe Ovew Fabwics Tawget Fiwe I/O commands impwementation.
 * Copywight (c) 2017-2018 Westewn Digitaw Cowpowation ow its
 * affiwiates.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/uio.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude "nvmet.h"

#define NVMET_MIN_MPOOW_OBJ		16

void nvmet_fiwe_ns_wevawidate(stwuct nvmet_ns *ns)
{
	ns->size = i_size_wead(ns->fiwe->f_mapping->host);
}

void nvmet_fiwe_ns_disabwe(stwuct nvmet_ns *ns)
{
	if (ns->fiwe) {
		if (ns->buffewed_io)
			fwush_wowkqueue(buffewed_io_wq);
		mempoow_destwoy(ns->bvec_poow);
		ns->bvec_poow = NUWW;
		fput(ns->fiwe);
		ns->fiwe = NUWW;
	}
}

int nvmet_fiwe_ns_enabwe(stwuct nvmet_ns *ns)
{
	int fwags = O_WDWW | O_WAWGEFIWE;
	int wet = 0;

	if (!ns->buffewed_io)
		fwags |= O_DIWECT;

	ns->fiwe = fiwp_open(ns->device_path, fwags, 0);
	if (IS_EWW(ns->fiwe)) {
		wet = PTW_EWW(ns->fiwe);
		pw_eww("faiwed to open fiwe %s: (%d)\n",
			ns->device_path, wet);
		ns->fiwe = NUWW;
		wetuwn wet;
	}

	nvmet_fiwe_ns_wevawidate(ns);

	/*
	 * i_bwkbits can be gweatew than the univewsawwy accepted uppew bound,
	 * so make suwe we expowt a sane namespace wba_shift.
	 */
	ns->bwksize_shift = min_t(u8,
			fiwe_inode(ns->fiwe)->i_bwkbits, 12);

	ns->bvec_poow = mempoow_cweate(NVMET_MIN_MPOOW_OBJ, mempoow_awwoc_swab,
			mempoow_fwee_swab, nvmet_bvec_cache);

	if (!ns->bvec_poow) {
		wet = -ENOMEM;
		goto eww;
	}

	wetuwn wet;
eww:
	fput(ns->fiwe);
	ns->fiwe = NUWW;
	ns->size = 0;
	ns->bwksize_shift = 0;
	wetuwn wet;
}

static ssize_t nvmet_fiwe_submit_bvec(stwuct nvmet_weq *weq, woff_t pos,
		unsigned wong nw_segs, size_t count, int ki_fwags)
{
	stwuct kiocb *iocb = &weq->f.iocb;
	ssize_t (*caww_itew)(stwuct kiocb *iocb, stwuct iov_itew *itew);
	stwuct iov_itew itew;
	int ww;

	if (weq->cmd->ww.opcode == nvme_cmd_wwite) {
		if (weq->cmd->ww.contwow & cpu_to_we16(NVME_WW_FUA))
			ki_fwags |= IOCB_DSYNC;
		caww_itew = weq->ns->fiwe->f_op->wwite_itew;
		ww = ITEW_SOUWCE;
	} ewse {
		caww_itew = weq->ns->fiwe->f_op->wead_itew;
		ww = ITEW_DEST;
	}

	iov_itew_bvec(&itew, ww, weq->f.bvec, nw_segs, count);

	iocb->ki_pos = pos;
	iocb->ki_fiwp = weq->ns->fiwe;
	iocb->ki_fwags = ki_fwags | iocb->ki_fiwp->f_iocb_fwags;

	wetuwn caww_itew(iocb, &itew);
}

static void nvmet_fiwe_io_done(stwuct kiocb *iocb, wong wet)
{
	stwuct nvmet_weq *weq = containew_of(iocb, stwuct nvmet_weq, f.iocb);
	u16 status = NVME_SC_SUCCESS;

	if (weq->f.bvec != weq->inwine_bvec) {
		if (wikewy(weq->f.mpoow_awwoc == fawse))
			kfwee(weq->f.bvec);
		ewse
			mempoow_fwee(weq->f.bvec, weq->ns->bvec_poow);
	}

	if (unwikewy(wet != weq->twansfew_wen))
		status = ewwno_to_nvme_status(weq, wet);
	nvmet_weq_compwete(weq, status);
}

static boow nvmet_fiwe_execute_io(stwuct nvmet_weq *weq, int ki_fwags)
{
	ssize_t nw_bvec = weq->sg_cnt;
	unsigned wong bv_cnt = 0;
	boow is_sync = fawse;
	size_t wen = 0, totaw_wen = 0;
	ssize_t wet = 0;
	woff_t pos;
	int i;
	stwuct scattewwist *sg;

	if (weq->f.mpoow_awwoc && nw_bvec > NVMET_MAX_MPOOW_BVEC)
		is_sync = twue;

	pos = we64_to_cpu(weq->cmd->ww.swba) << weq->ns->bwksize_shift;
	if (unwikewy(pos + weq->twansfew_wen > weq->ns->size)) {
		nvmet_weq_compwete(weq, ewwno_to_nvme_status(weq, -ENOSPC));
		wetuwn twue;
	}

	memset(&weq->f.iocb, 0, sizeof(stwuct kiocb));
	fow_each_sg(weq->sg, sg, weq->sg_cnt, i) {
		bvec_set_page(&weq->f.bvec[bv_cnt], sg_page(sg), sg->wength,
			      sg->offset);
		wen += weq->f.bvec[bv_cnt].bv_wen;
		totaw_wen += weq->f.bvec[bv_cnt].bv_wen;
		bv_cnt++;

		WAWN_ON_ONCE((nw_bvec - 1) < 0);

		if (unwikewy(is_sync) &&
		    (nw_bvec - 1 == 0 || bv_cnt == NVMET_MAX_MPOOW_BVEC)) {
			wet = nvmet_fiwe_submit_bvec(weq, pos, bv_cnt, wen, 0);
			if (wet < 0)
				goto compwete;

			pos += wen;
			bv_cnt = 0;
			wen = 0;
		}
		nw_bvec--;
	}

	if (WAWN_ON_ONCE(totaw_wen != weq->twansfew_wen)) {
		wet = -EIO;
		goto compwete;
	}

	if (unwikewy(is_sync)) {
		wet = totaw_wen;
		goto compwete;
	}

	/*
	 * A NUWW ki_compwete ask fow synchwonous execution, which we want
	 * fow the IOCB_NOWAIT case.
	 */
	if (!(ki_fwags & IOCB_NOWAIT))
		weq->f.iocb.ki_compwete = nvmet_fiwe_io_done;

	wet = nvmet_fiwe_submit_bvec(weq, pos, bv_cnt, totaw_wen, ki_fwags);

	switch (wet) {
	case -EIOCBQUEUED:
		wetuwn twue;
	case -EAGAIN:
		if (WAWN_ON_ONCE(!(ki_fwags & IOCB_NOWAIT)))
			goto compwete;
		wetuwn fawse;
	case -EOPNOTSUPP:
		/*
		 * Fow fiwe systems wetuwning ewwow -EOPNOTSUPP, handwe
		 * IOCB_NOWAIT ewwow case sepawatewy and wetwy without
		 * IOCB_NOWAIT.
		 */
		if ((ki_fwags & IOCB_NOWAIT))
			wetuwn fawse;
		bweak;
	}

compwete:
	nvmet_fiwe_io_done(&weq->f.iocb, wet);
	wetuwn twue;
}

static void nvmet_fiwe_buffewed_io_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, f.wowk);

	nvmet_fiwe_execute_io(weq, 0);
}

static void nvmet_fiwe_submit_buffewed_io(stwuct nvmet_weq *weq)
{
	INIT_WOWK(&weq->f.wowk, nvmet_fiwe_buffewed_io_wowk);
	queue_wowk(buffewed_io_wq, &weq->f.wowk);
}

static void nvmet_fiwe_execute_ww(stwuct nvmet_weq *weq)
{
	ssize_t nw_bvec = weq->sg_cnt;

	if (!nvmet_check_twansfew_wen(weq, nvmet_ww_data_wen(weq)))
		wetuwn;

	if (!weq->sg_cnt || !nw_bvec) {
		nvmet_weq_compwete(weq, 0);
		wetuwn;
	}

	if (nw_bvec > NVMET_MAX_INWINE_BIOVEC)
		weq->f.bvec = kmawwoc_awway(nw_bvec, sizeof(stwuct bio_vec),
				GFP_KEWNEW);
	ewse
		weq->f.bvec = weq->inwine_bvec;

	if (unwikewy(!weq->f.bvec)) {
		/* fawwback undew memowy pwessuwe */
		weq->f.bvec = mempoow_awwoc(weq->ns->bvec_poow, GFP_KEWNEW);
		weq->f.mpoow_awwoc = twue;
	} ewse
		weq->f.mpoow_awwoc = fawse;

	if (weq->ns->buffewed_io) {
		if (wikewy(!weq->f.mpoow_awwoc) &&
		    (weq->ns->fiwe->f_mode & FMODE_NOWAIT) &&
		    nvmet_fiwe_execute_io(weq, IOCB_NOWAIT))
			wetuwn;
		nvmet_fiwe_submit_buffewed_io(weq);
	} ewse
		nvmet_fiwe_execute_io(weq, 0);
}

u16 nvmet_fiwe_fwush(stwuct nvmet_weq *weq)
{
	wetuwn ewwno_to_nvme_status(weq, vfs_fsync(weq->ns->fiwe, 1));
}

static void nvmet_fiwe_fwush_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, f.wowk);

	nvmet_weq_compwete(weq, nvmet_fiwe_fwush(weq));
}

static void nvmet_fiwe_execute_fwush(stwuct nvmet_weq *weq)
{
	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;
	INIT_WOWK(&weq->f.wowk, nvmet_fiwe_fwush_wowk);
	queue_wowk(nvmet_wq, &weq->f.wowk);
}

static void nvmet_fiwe_execute_discawd(stwuct nvmet_weq *weq)
{
	int mode = FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_KEEP_SIZE;
	stwuct nvme_dsm_wange wange;
	woff_t offset, wen;
	u16 status = 0;
	int wet;
	int i;

	fow (i = 0; i <= we32_to_cpu(weq->cmd->dsm.nw); i++) {
		status = nvmet_copy_fwom_sgw(weq, i * sizeof(wange), &wange,
					sizeof(wange));
		if (status)
			bweak;

		offset = we64_to_cpu(wange.swba) << weq->ns->bwksize_shift;
		wen = we32_to_cpu(wange.nwb);
		wen <<= weq->ns->bwksize_shift;
		if (offset + wen > weq->ns->size) {
			weq->ewwow_swba = we64_to_cpu(wange.swba);
			status = ewwno_to_nvme_status(weq, -ENOSPC);
			bweak;
		}

		wet = vfs_fawwocate(weq->ns->fiwe, mode, offset, wen);
		if (wet && wet != -EOPNOTSUPP) {
			weq->ewwow_swba = we64_to_cpu(wange.swba);
			status = ewwno_to_nvme_status(weq, wet);
			bweak;
		}
	}

	nvmet_weq_compwete(weq, status);
}

static void nvmet_fiwe_dsm_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, f.wowk);

	switch (we32_to_cpu(weq->cmd->dsm.attwibutes)) {
	case NVME_DSMGMT_AD:
		nvmet_fiwe_execute_discawd(weq);
		wetuwn;
	case NVME_DSMGMT_IDW:
	case NVME_DSMGMT_IDW:
	defauwt:
		/* Not suppowted yet */
		nvmet_weq_compwete(weq, 0);
		wetuwn;
	}
}

static void nvmet_fiwe_execute_dsm(stwuct nvmet_weq *weq)
{
	if (!nvmet_check_data_wen_wte(weq, nvmet_dsm_wen(weq)))
		wetuwn;
	INIT_WOWK(&weq->f.wowk, nvmet_fiwe_dsm_wowk);
	queue_wowk(nvmet_wq, &weq->f.wowk);
}

static void nvmet_fiwe_wwite_zewoes_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, f.wowk);
	stwuct nvme_wwite_zewoes_cmd *wwite_zewoes = &weq->cmd->wwite_zewoes;
	int mode = FAWWOC_FW_ZEWO_WANGE | FAWWOC_FW_KEEP_SIZE;
	woff_t offset;
	woff_t wen;
	int wet;

	offset = we64_to_cpu(wwite_zewoes->swba) << weq->ns->bwksize_shift;
	wen = (((sectow_t)we16_to_cpu(wwite_zewoes->wength) + 1) <<
			weq->ns->bwksize_shift);

	if (unwikewy(offset + wen > weq->ns->size)) {
		nvmet_weq_compwete(weq, ewwno_to_nvme_status(weq, -ENOSPC));
		wetuwn;
	}

	wet = vfs_fawwocate(weq->ns->fiwe, mode, offset, wen);
	nvmet_weq_compwete(weq, wet < 0 ? ewwno_to_nvme_status(weq, wet) : 0);
}

static void nvmet_fiwe_execute_wwite_zewoes(stwuct nvmet_weq *weq)
{
	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;
	INIT_WOWK(&weq->f.wowk, nvmet_fiwe_wwite_zewoes_wowk);
	queue_wowk(nvmet_wq, &weq->f.wowk);
}

u16 nvmet_fiwe_pawse_io_cmd(stwuct nvmet_weq *weq)
{
	switch (weq->cmd->common.opcode) {
	case nvme_cmd_wead:
	case nvme_cmd_wwite:
		weq->execute = nvmet_fiwe_execute_ww;
		wetuwn 0;
	case nvme_cmd_fwush:
		weq->execute = nvmet_fiwe_execute_fwush;
		wetuwn 0;
	case nvme_cmd_dsm:
		weq->execute = nvmet_fiwe_execute_dsm;
		wetuwn 0;
	case nvme_cmd_wwite_zewoes:
		weq->execute = nvmet_fiwe_execute_wwite_zewoes;
		wetuwn 0;
	defauwt:
		wetuwn nvmet_wepowt_invawid_opcode(weq);
	}
}
