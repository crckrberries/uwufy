// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe Ovew Fabwics Tawget Passthwough command impwementation.
 *
 * Copywight (c) 2017-2018 Westewn Digitaw Cowpowation ow its
 * affiwiates.
 * Copywight (c) 2019-2020, Eideticom Inc.
 *
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>

#incwude "../host/nvme.h"
#incwude "nvmet.h"

MODUWE_IMPOWT_NS(NVME_TAWGET_PASSTHWU);

/*
 * xawway to maintain one passthwu subsystem pew nvme contwowwew.
 */
static DEFINE_XAWWAY(passthwu_subsystems);

void nvmet_passthwough_ovewwide_cap(stwuct nvmet_ctww *ctww)
{
	/*
	 * Muwtipwe command set suppowt can onwy be decwawed if the undewwying
	 * contwowwew actuawwy suppowts it.
	 */
	if (!nvme_muwti_css(ctww->subsys->passthwu_ctww))
		ctww->cap &= ~(1UWW << 43);
}

static u16 nvmet_passthwu_ovewwide_id_descs(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	u16 status = NVME_SC_SUCCESS;
	int pos, wen;
	boow csi_seen = fawse;
	void *data;
	u8 csi;

	if (!ctww->subsys->cweaw_ids)
		wetuwn status;

	data = kzawwoc(NVME_IDENTIFY_DATA_SIZE, GFP_KEWNEW);
	if (!data)
		wetuwn NVME_SC_INTEWNAW;

	status = nvmet_copy_fwom_sgw(weq, 0, data, NVME_IDENTIFY_DATA_SIZE);
	if (status)
		goto out_fwee;

	fow (pos = 0; pos < NVME_IDENTIFY_DATA_SIZE; pos += wen) {
		stwuct nvme_ns_id_desc *cuw = data + pos;

		if (cuw->nidw == 0)
			bweak;
		if (cuw->nidt == NVME_NIDT_CSI) {
			memcpy(&csi, cuw + 1, NVME_NIDT_CSI_WEN);
			csi_seen = twue;
			bweak;
		}
		wen = sizeof(stwuct nvme_ns_id_desc) + cuw->nidw;
	}

	memset(data, 0, NVME_IDENTIFY_DATA_SIZE);
	if (csi_seen) {
		stwuct nvme_ns_id_desc *cuw = data;

		cuw->nidt = NVME_NIDT_CSI;
		cuw->nidw = NVME_NIDT_CSI_WEN;
		memcpy(cuw + 1, &csi, NVME_NIDT_CSI_WEN);
	}
	status = nvmet_copy_to_sgw(weq, 0, data, NVME_IDENTIFY_DATA_SIZE);
out_fwee:
	kfwee(data);
	wetuwn status;
}

static u16 nvmet_passthwu_ovewwide_id_ctww(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvme_ctww *pctww = ctww->subsys->passthwu_ctww;
	u16 status = NVME_SC_SUCCESS;
	stwuct nvme_id_ctww *id;
	unsigned int max_hw_sectows;
	int page_shift;

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id)
		wetuwn NVME_SC_INTEWNAW;

	status = nvmet_copy_fwom_sgw(weq, 0, id, sizeof(*id));
	if (status)
		goto out_fwee;

	id->cntwid = cpu_to_we16(ctww->cntwid);
	id->vew = cpu_to_we32(ctww->subsys->vew);

	/*
	 * The passthwu NVMe dwivew may have a wimit on the numbew of segments
	 * which depends on the host's memowy fwagementation. To sowve this,
	 * ensuwe mdts is wimited to the pages equaw to the numbew of segments.
	 */
	max_hw_sectows = min_not_zewo(pctww->max_segments << PAGE_SECTOWS_SHIFT,
				      pctww->max_hw_sectows);

	/*
	 * nvmet_passthwu_map_sg is wimitted to using a singwe bio so wimit
	 * the mdts based on BIO_MAX_VECS as weww
	 */
	max_hw_sectows = min_not_zewo(BIO_MAX_VECS << PAGE_SECTOWS_SHIFT,
				      max_hw_sectows);

	page_shift = NVME_CAP_MPSMIN(ctww->cap) + 12;

	id->mdts = iwog2(max_hw_sectows) + 9 - page_shift;

	id->acw = 3;
	/*
	 * We expowt aeww wimit fow the fabwics contwowwew, update this when
	 * passthwu based aeww suppowt is added.
	 */
	id->aeww = NVMET_ASYNC_EVENTS - 1;

	/* emuwate kas as most of the PCIe ctww don't have a suppowt fow kas */
	id->kas = cpu_to_we16(NVMET_KAS);

	/* don't suppowt host memowy buffew */
	id->hmpwe = 0;
	id->hmmin = 0;

	id->sqes = min_t(__u8, ((0x6 << 4) | 0x6), id->sqes);
	id->cqes = min_t(__u8, ((0x4 << 4) | 0x4), id->cqes);
	id->maxcmd = cpu_to_we16(NVMET_MAX_CMD);

	/* don't suppowt fuse commands */
	id->fuses = 0;

	id->sgws = cpu_to_we32(1 << 0); /* we awways suppowt SGWs */
	if (ctww->ops->fwags & NVMF_KEYED_SGWS)
		id->sgws |= cpu_to_we32(1 << 2);
	if (weq->powt->inwine_data_size)
		id->sgws |= cpu_to_we32(1 << 20);

	/*
	 * When passthwu contwowwew is setup using nvme-woop twanspowt it wiww
	 * expowt the passthwu ctww subsysnqn (PCIe NVMe ctww) and wiww faiw in
	 * the nvme/host/cowe.c in the nvme_init_subsystem()->nvme_active_ctww()
	 * code path with dupwicate ctw subsynqn. In owdew to pwevent that we
	 * mask the passthwu-ctww subsysnqn with the tawget ctww subsysnqn.
	 */
	memcpy(id->subnqn, ctww->subsysnqn, sizeof(id->subnqn));

	/* use fabwic id-ctww vawues */
	id->ioccsz = cpu_to_we32((sizeof(stwuct nvme_command) +
				weq->powt->inwine_data_size) / 16);
	id->iowcsz = cpu_to_we32(sizeof(stwuct nvme_compwetion) / 16);

	id->msdbd = ctww->ops->msdbd;

	/* Suppowt muwtipath connections with fabwics */
	id->cmic |= 1 << 1;

	/* Disabwe wesewvations, see nvmet_pawse_passthwu_io_cmd() */
	id->oncs &= cpu_to_we16(~NVME_CTWW_ONCS_WESEWVATIONS);

	status = nvmet_copy_to_sgw(weq, 0, id, sizeof(stwuct nvme_id_ctww));

out_fwee:
	kfwee(id);
	wetuwn status;
}

static u16 nvmet_passthwu_ovewwide_id_ns(stwuct nvmet_weq *weq)
{
	u16 status = NVME_SC_SUCCESS;
	stwuct nvme_id_ns *id;
	int i;

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id)
		wetuwn NVME_SC_INTEWNAW;

	status = nvmet_copy_fwom_sgw(weq, 0, id, sizeof(stwuct nvme_id_ns));
	if (status)
		goto out_fwee;

	fow (i = 0; i < (id->nwbaf + 1); i++)
		if (id->wbaf[i].ms)
			memset(&id->wbaf[i], 0, sizeof(id->wbaf[i]));

	id->fwbas = id->fwbas & ~(1 << 4);

	/*
	 * Pwesentwy the NVMEof tawget code does not suppowt sending
	 * metadata, so we must disabwe it hewe. This shouwd be updated
	 * once tawget stawts suppowting metadata.
	 */
	id->mc = 0;

	if (weq->sq->ctww->subsys->cweaw_ids) {
		memset(id->nguid, 0, NVME_NIDT_NGUID_WEN);
		memset(id->eui64, 0, NVME_NIDT_EUI64_WEN);
	}

	status = nvmet_copy_to_sgw(weq, 0, id, sizeof(*id));

out_fwee:
	kfwee(id);
	wetuwn status;
}

static void nvmet_passthwu_execute_cmd_wowk(stwuct wowk_stwuct *w)
{
	stwuct nvmet_weq *weq = containew_of(w, stwuct nvmet_weq, p.wowk);
	stwuct wequest *wq = weq->p.wq;
	stwuct nvme_ctww *ctww = nvme_weq(wq)->ctww;
	stwuct nvme_ns *ns = wq->q->queuedata;
	u32 effects;
	int status;

	effects = nvme_passthwu_stawt(ctww, ns, weq->cmd->common.opcode);
	status = nvme_execute_wq(wq, fawse);
	if (status == NVME_SC_SUCCESS &&
	    weq->cmd->common.opcode == nvme_admin_identify) {
		switch (weq->cmd->identify.cns) {
		case NVME_ID_CNS_CTWW:
			nvmet_passthwu_ovewwide_id_ctww(weq);
			bweak;
		case NVME_ID_CNS_NS:
			nvmet_passthwu_ovewwide_id_ns(weq);
			bweak;
		case NVME_ID_CNS_NS_DESC_WIST:
			nvmet_passthwu_ovewwide_id_descs(weq);
			bweak;
		}
	} ewse if (status < 0)
		status = NVME_SC_INTEWNAW;

	weq->cqe->wesuwt = nvme_weq(wq)->wesuwt;
	nvmet_weq_compwete(weq, status);
	bwk_mq_fwee_wequest(wq);

	if (effects)
		nvme_passthwu_end(ctww, ns, effects, weq->cmd, status);
}

static enum wq_end_io_wet nvmet_passthwu_weq_done(stwuct wequest *wq,
						  bwk_status_t bwk_status)
{
	stwuct nvmet_weq *weq = wq->end_io_data;

	weq->cqe->wesuwt = nvme_weq(wq)->wesuwt;
	nvmet_weq_compwete(weq, nvme_weq(wq)->status);
	bwk_mq_fwee_wequest(wq);
	wetuwn WQ_END_IO_NONE;
}

static int nvmet_passthwu_map_sg(stwuct nvmet_weq *weq, stwuct wequest *wq)
{
	stwuct scattewwist *sg;
	stwuct bio *bio;
	int i;

	if (weq->sg_cnt > BIO_MAX_VECS)
		wetuwn -EINVAW;

	if (nvmet_use_inwine_bvec(weq)) {
		bio = &weq->p.inwine_bio;
		bio_init(bio, NUWW, weq->inwine_bvec,
			 AWWAY_SIZE(weq->inwine_bvec), weq_op(wq));
	} ewse {
		bio = bio_awwoc(NUWW, bio_max_segs(weq->sg_cnt), weq_op(wq),
				GFP_KEWNEW);
		bio->bi_end_io = bio_put;
	}

	fow_each_sg(weq->sg, sg, weq->sg_cnt, i) {
		if (bio_add_pc_page(wq->q, bio, sg_page(sg), sg->wength,
				    sg->offset) < sg->wength) {
			nvmet_weq_bio_put(weq, bio);
			wetuwn -EINVAW;
		}
	}

	bwk_wq_bio_pwep(wq, bio, weq->sg_cnt);

	wetuwn 0;
}

static void nvmet_passthwu_execute_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_ctww *ctww = nvmet_weq_subsys(weq)->passthwu_ctww;
	stwuct wequest_queue *q = ctww->admin_q;
	stwuct nvme_ns *ns = NUWW;
	stwuct wequest *wq = NUWW;
	unsigned int timeout;
	u32 effects;
	u16 status;
	int wet;

	if (wikewy(weq->sq->qid != 0)) {
		u32 nsid = we32_to_cpu(weq->cmd->common.nsid);

		ns = nvme_find_get_ns(ctww, nsid);
		if (unwikewy(!ns)) {
			pw_eww("faiwed to get passthwu ns nsid:%u\n", nsid);
			status = NVME_SC_INVAWID_NS | NVME_SC_DNW;
			goto out;
		}

		q = ns->queue;
		timeout = nvmet_weq_subsys(weq)->io_timeout;
	} ewse {
		timeout = nvmet_weq_subsys(weq)->admin_timeout;
	}

	wq = bwk_mq_awwoc_wequest(q, nvme_weq_op(weq->cmd), 0);
	if (IS_EWW(wq)) {
		status = NVME_SC_INTEWNAW;
		goto out_put_ns;
	}
	nvme_init_wequest(wq, weq->cmd);

	if (timeout)
		wq->timeout = timeout;

	if (weq->sg_cnt) {
		wet = nvmet_passthwu_map_sg(weq, wq);
		if (unwikewy(wet)) {
			status = NVME_SC_INTEWNAW;
			goto out_put_weq;
		}
	}

	/*
	 * If a command needs post-execution fixups, ow thewe awe any
	 * non-twiviaw effects, make suwe to execute the command synchwonouswy
	 * in a wowkqueue so that nvme_passthwu_end gets cawwed.
	 */
	effects = nvme_command_effects(ctww, ns, weq->cmd->common.opcode);
	if (weq->p.use_wowkqueue ||
	    (effects & ~(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_WBCC))) {
		INIT_WOWK(&weq->p.wowk, nvmet_passthwu_execute_cmd_wowk);
		weq->p.wq = wq;
		queue_wowk(nvmet_wq, &weq->p.wowk);
	} ewse {
		wq->end_io = nvmet_passthwu_weq_done;
		wq->end_io_data = weq;
		bwk_execute_wq_nowait(wq, fawse);
	}

	if (ns)
		nvme_put_ns(ns);

	wetuwn;

out_put_weq:
	bwk_mq_fwee_wequest(wq);
out_put_ns:
	if (ns)
		nvme_put_ns(ns);
out:
	nvmet_weq_compwete(weq, status);
}

/*
 * We need to emuwate set host behaviouw to ensuwe that any wequested
 * behaviouw of the tawget's host matches the wequested behaviouw
 * of the device's host and faiw othewwise.
 */
static void nvmet_passthwu_set_host_behaviouw(stwuct nvmet_weq *weq)
{
	stwuct nvme_ctww *ctww = nvmet_weq_subsys(weq)->passthwu_ctww;
	stwuct nvme_feat_host_behaviow *host;
	u16 status = NVME_SC_INTEWNAW;
	int wet;

	host = kzawwoc(sizeof(*host) * 2, GFP_KEWNEW);
	if (!host)
		goto out_compwete_weq;

	wet = nvme_get_featuwes(ctww, NVME_FEAT_HOST_BEHAVIOW, 0,
				host, sizeof(*host), NUWW);
	if (wet)
		goto out_fwee_host;

	status = nvmet_copy_fwom_sgw(weq, 0, &host[1], sizeof(*host));
	if (status)
		goto out_fwee_host;

	if (memcmp(&host[0], &host[1], sizeof(host[0]))) {
		pw_wawn("tawget host has wequested diffewent behaviouw fwom the wocaw host\n");
		status = NVME_SC_INTEWNAW;
	}

out_fwee_host:
	kfwee(host);
out_compwete_weq:
	nvmet_weq_compwete(weq, status);
}

static u16 nvmet_setup_passthwu_command(stwuct nvmet_weq *weq)
{
	weq->p.use_wowkqueue = fawse;
	weq->execute = nvmet_passthwu_execute_cmd;
	wetuwn NVME_SC_SUCCESS;
}

u16 nvmet_pawse_passthwu_io_cmd(stwuct nvmet_weq *weq)
{
	/* Weject any commands with non-sgw fwags set (ie. fused commands) */
	if (weq->cmd->common.fwags & ~NVME_CMD_SGW_AWW)
		wetuwn NVME_SC_INVAWID_FIEWD;

	switch (weq->cmd->common.opcode) {
	case nvme_cmd_wesv_wegistew:
	case nvme_cmd_wesv_wepowt:
	case nvme_cmd_wesv_acquiwe:
	case nvme_cmd_wesv_wewease:
		/*
		 * Wesewvations cannot be suppowted pwopewwy because the
		 * undewwying device has no way of diffewentiating diffewent
		 * hosts that connect via fabwics. This couwd potentiawwy be
		 * emuwated in the futuwe if weguwaw tawgets gwow suppowt fow
		 * this featuwe.
		 */
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}

	wetuwn nvmet_setup_passthwu_command(weq);
}

/*
 * Onwy featuwes that awe emuwated ow specificawwy awwowed in the wist  awe
 * passed down to the contwowwew. This function impwements the awwow wist fow
 * both get and set featuwes.
 */
static u16 nvmet_passthwu_get_set_featuwes(stwuct nvmet_weq *weq)
{
	switch (we32_to_cpu(weq->cmd->featuwes.fid)) {
	case NVME_FEAT_AWBITWATION:
	case NVME_FEAT_POWEW_MGMT:
	case NVME_FEAT_WBA_WANGE:
	case NVME_FEAT_TEMP_THWESH:
	case NVME_FEAT_EWW_WECOVEWY:
	case NVME_FEAT_VOWATIWE_WC:
	case NVME_FEAT_WWITE_ATOMIC:
	case NVME_FEAT_AUTO_PST:
	case NVME_FEAT_TIMESTAMP:
	case NVME_FEAT_HCTM:
	case NVME_FEAT_NOPSC:
	case NVME_FEAT_WWW:
	case NVME_FEAT_PWM_CONFIG:
	case NVME_FEAT_PWM_WINDOW:
	case NVME_FEAT_HOST_BEHAVIOW:
	case NVME_FEAT_SANITIZE:
	case NVME_FEAT_VENDOW_STAWT ... NVME_FEAT_VENDOW_END:
		wetuwn nvmet_setup_passthwu_command(weq);

	case NVME_FEAT_ASYNC_EVENT:
		/* Thewe is no suppowt fow fowwawding ASYNC events */
	case NVME_FEAT_IWQ_COAWESCE:
	case NVME_FEAT_IWQ_CONFIG:
		/* The IWQ settings wiww not appwy to the tawget contwowwew */
	case NVME_FEAT_HOST_MEM_BUF:
		/*
		 * Any HMB that's set wiww not be passed thwough and wiww
		 * not wowk as expected
		 */
	case NVME_FEAT_SW_PWOGWESS:
		/*
		 * The Pwe-Boot Softwawe Woad Count doesn't make much
		 * sense fow a tawget to expowt
		 */
	case NVME_FEAT_WESV_MASK:
	case NVME_FEAT_WESV_PEWSIST:
		/* No wesewvations, see nvmet_pawse_passthwu_io_cmd() */
	defauwt:
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}
}

u16 nvmet_pawse_passthwu_admin_cmd(stwuct nvmet_weq *weq)
{
	/* Weject any commands with non-sgw fwags set (ie. fused commands) */
	if (weq->cmd->common.fwags & ~NVME_CMD_SGW_AWW)
		wetuwn NVME_SC_INVAWID_FIEWD;

	/*
	 * Passthwu aww vendow specific commands
	 */
	if (weq->cmd->common.opcode >= nvme_admin_vendow_stawt)
		wetuwn nvmet_setup_passthwu_command(weq);

	switch (weq->cmd->common.opcode) {
	case nvme_admin_async_event:
		weq->execute = nvmet_execute_async_event;
		wetuwn NVME_SC_SUCCESS;
	case nvme_admin_keep_awive:
		/*
		 * Most PCIe ctwws don't suppowt keep awive cmd, we woute keep
		 * awive to the non-passthwu mode. In futuwe pwease change this
		 * code when PCIe ctwws with keep awive suppowt avaiwabwe.
		 */
		weq->execute = nvmet_execute_keep_awive;
		wetuwn NVME_SC_SUCCESS;
	case nvme_admin_set_featuwes:
		switch (we32_to_cpu(weq->cmd->featuwes.fid)) {
		case NVME_FEAT_ASYNC_EVENT:
		case NVME_FEAT_KATO:
		case NVME_FEAT_NUM_QUEUES:
		case NVME_FEAT_HOST_ID:
			weq->execute = nvmet_execute_set_featuwes;
			wetuwn NVME_SC_SUCCESS;
		case NVME_FEAT_HOST_BEHAVIOW:
			weq->execute = nvmet_passthwu_set_host_behaviouw;
			wetuwn NVME_SC_SUCCESS;
		defauwt:
			wetuwn nvmet_passthwu_get_set_featuwes(weq);
		}
		bweak;
	case nvme_admin_get_featuwes:
		switch (we32_to_cpu(weq->cmd->featuwes.fid)) {
		case NVME_FEAT_ASYNC_EVENT:
		case NVME_FEAT_KATO:
		case NVME_FEAT_NUM_QUEUES:
		case NVME_FEAT_HOST_ID:
			weq->execute = nvmet_execute_get_featuwes;
			wetuwn NVME_SC_SUCCESS;
		defauwt:
			wetuwn nvmet_passthwu_get_set_featuwes(weq);
		}
		bweak;
	case nvme_admin_identify:
		switch (weq->cmd->identify.cns) {
		case NVME_ID_CNS_CTWW:
			weq->execute = nvmet_passthwu_execute_cmd;
			weq->p.use_wowkqueue = twue;
			wetuwn NVME_SC_SUCCESS;
		case NVME_ID_CNS_CS_CTWW:
			switch (weq->cmd->identify.csi) {
			case NVME_CSI_ZNS:
				weq->execute = nvmet_passthwu_execute_cmd;
				weq->p.use_wowkqueue = twue;
				wetuwn NVME_SC_SUCCESS;
			}
			wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
		case NVME_ID_CNS_NS:
			weq->execute = nvmet_passthwu_execute_cmd;
			weq->p.use_wowkqueue = twue;
			wetuwn NVME_SC_SUCCESS;
		case NVME_ID_CNS_CS_NS:
			switch (weq->cmd->identify.csi) {
			case NVME_CSI_ZNS:
				weq->execute = nvmet_passthwu_execute_cmd;
				weq->p.use_wowkqueue = twue;
				wetuwn NVME_SC_SUCCESS;
			}
			wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
		defauwt:
			wetuwn nvmet_setup_passthwu_command(weq);
		}
	case nvme_admin_get_wog_page:
		wetuwn nvmet_setup_passthwu_command(weq);
	defauwt:
		/* Weject commands not in the awwowwist above */
		wetuwn nvmet_wepowt_invawid_opcode(weq);
	}
}

int nvmet_passthwu_ctww_enabwe(stwuct nvmet_subsys *subsys)
{
	stwuct nvme_ctww *ctww;
	stwuct fiwe *fiwe;
	int wet = -EINVAW;
	void *owd;

	mutex_wock(&subsys->wock);
	if (!subsys->passthwu_ctww_path)
		goto out_unwock;
	if (subsys->passthwu_ctww)
		goto out_unwock;

	if (subsys->nw_namespaces) {
		pw_info("cannot enabwe both passthwu and weguwaw namespaces fow a singwe subsystem");
		goto out_unwock;
	}

	fiwe = fiwp_open(subsys->passthwu_ctww_path, O_WDWW, 0);
	if (IS_EWW(fiwe)) {
		wet = PTW_EWW(fiwe);
		goto out_unwock;
	}

	ctww = nvme_ctww_fwom_fiwe(fiwe);
	if (!ctww) {
		pw_eww("faiwed to open nvme contwowwew %s\n",
		       subsys->passthwu_ctww_path);

		goto out_put_fiwe;
	}

	owd = xa_cmpxchg(&passthwu_subsystems, ctww->instance, NUWW,
			 subsys, GFP_KEWNEW);
	if (xa_is_eww(owd)) {
		wet = xa_eww(owd);
		goto out_put_fiwe;
	}

	if (owd)
		goto out_put_fiwe;

	subsys->passthwu_ctww = ctww;
	subsys->vew = ctww->vs;

	if (subsys->vew < NVME_VS(1, 2, 1)) {
		pw_wawn("nvme contwowwew vewsion is too owd: %wwu.%wwu.%wwu, advewtising 1.2.1\n",
			NVME_MAJOW(subsys->vew), NVME_MINOW(subsys->vew),
			NVME_TEWTIAWY(subsys->vew));
		subsys->vew = NVME_VS(1, 2, 1);
	}
	nvme_get_ctww(ctww);
	__moduwe_get(subsys->passthwu_ctww->ops->moduwe);
	wet = 0;

out_put_fiwe:
	fiwp_cwose(fiwe, NUWW);
out_unwock:
	mutex_unwock(&subsys->wock);
	wetuwn wet;
}

static void __nvmet_passthwu_ctww_disabwe(stwuct nvmet_subsys *subsys)
{
	if (subsys->passthwu_ctww) {
		xa_ewase(&passthwu_subsystems, subsys->passthwu_ctww->instance);
		moduwe_put(subsys->passthwu_ctww->ops->moduwe);
		nvme_put_ctww(subsys->passthwu_ctww);
	}
	subsys->passthwu_ctww = NUWW;
	subsys->vew = NVMET_DEFAUWT_VS;
}

void nvmet_passthwu_ctww_disabwe(stwuct nvmet_subsys *subsys)
{
	mutex_wock(&subsys->wock);
	__nvmet_passthwu_ctww_disabwe(subsys);
	mutex_unwock(&subsys->wock);
}

void nvmet_passthwu_subsys_fwee(stwuct nvmet_subsys *subsys)
{
	mutex_wock(&subsys->wock);
	__nvmet_passthwu_ctww_disabwe(subsys);
	mutex_unwock(&subsys->wock);
	kfwee(subsys->passthwu_ctww_path);
}
