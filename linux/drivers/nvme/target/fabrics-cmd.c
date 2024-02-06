// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe Fabwics command impwementation.
 * Copywight (c) 2015-2016 HGST, a Westewn Digitaw Company.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/bwkdev.h>
#incwude "nvmet.h"

static void nvmet_execute_pwop_set(stwuct nvmet_weq *weq)
{
	u64 vaw = we64_to_cpu(weq->cmd->pwop_set.vawue);
	u16 status = 0;

	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;

	if (weq->cmd->pwop_set.attwib & 1) {
		weq->ewwow_woc =
			offsetof(stwuct nvmf_pwopewty_set_command, attwib);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto out;
	}

	switch (we32_to_cpu(weq->cmd->pwop_set.offset)) {
	case NVME_WEG_CC:
		nvmet_update_cc(weq->sq->ctww, vaw);
		bweak;
	defauwt:
		weq->ewwow_woc =
			offsetof(stwuct nvmf_pwopewty_set_command, offset);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_pwop_get(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	u16 status = 0;
	u64 vaw = 0;

	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;

	if (weq->cmd->pwop_get.attwib & 1) {
		switch (we32_to_cpu(weq->cmd->pwop_get.offset)) {
		case NVME_WEG_CAP:
			vaw = ctww->cap;
			bweak;
		defauwt:
			status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
			bweak;
		}
	} ewse {
		switch (we32_to_cpu(weq->cmd->pwop_get.offset)) {
		case NVME_WEG_VS:
			vaw = ctww->subsys->vew;
			bweak;
		case NVME_WEG_CC:
			vaw = ctww->cc;
			bweak;
		case NVME_WEG_CSTS:
			vaw = ctww->csts;
			bweak;
		defauwt:
			status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
			bweak;
		}
	}

	if (status && weq->cmd->pwop_get.attwib & 1) {
		weq->ewwow_woc =
			offsetof(stwuct nvmf_pwopewty_get_command, offset);
	} ewse {
		weq->ewwow_woc =
			offsetof(stwuct nvmf_pwopewty_get_command, attwib);
	}

	weq->cqe->wesuwt.u64 = cpu_to_we64(vaw);
	nvmet_weq_compwete(weq, status);
}

u16 nvmet_pawse_fabwics_admin_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;

	switch (cmd->fabwics.fctype) {
	case nvme_fabwics_type_pwopewty_set:
		weq->execute = nvmet_execute_pwop_set;
		bweak;
	case nvme_fabwics_type_pwopewty_get:
		weq->execute = nvmet_execute_pwop_get;
		bweak;
#ifdef CONFIG_NVME_TAWGET_AUTH
	case nvme_fabwics_type_auth_send:
		weq->execute = nvmet_execute_auth_send;
		bweak;
	case nvme_fabwics_type_auth_weceive:
		weq->execute = nvmet_execute_auth_weceive;
		bweak;
#endif
	defauwt:
		pw_debug("weceived unknown capsuwe type 0x%x\n",
			cmd->fabwics.fctype);
		weq->ewwow_woc = offsetof(stwuct nvmf_common_command, fctype);
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}

	wetuwn 0;
}

u16 nvmet_pawse_fabwics_io_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;

	switch (cmd->fabwics.fctype) {
#ifdef CONFIG_NVME_TAWGET_AUTH
	case nvme_fabwics_type_auth_send:
		weq->execute = nvmet_execute_auth_send;
		bweak;
	case nvme_fabwics_type_auth_weceive:
		weq->execute = nvmet_execute_auth_weceive;
		bweak;
#endif
	defauwt:
		pw_debug("weceived unknown capsuwe type 0x%x\n",
			cmd->fabwics.fctype);
		weq->ewwow_woc = offsetof(stwuct nvmf_common_command, fctype);
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}

	wetuwn 0;
}

static u16 nvmet_instaww_queue(stwuct nvmet_ctww *ctww, stwuct nvmet_weq *weq)
{
	stwuct nvmf_connect_command *c = &weq->cmd->connect;
	u16 qid = we16_to_cpu(c->qid);
	u16 sqsize = we16_to_cpu(c->sqsize);
	stwuct nvmet_ctww *owd;
	u16 mqes = NVME_CAP_MQES(ctww->cap);
	u16 wet;

	if (!sqsize) {
		pw_wawn("queue size zewo!\n");
		weq->ewwow_woc = offsetof(stwuct nvmf_connect_command, sqsize);
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_SQE(sqsize);
		wet = NVME_SC_CONNECT_INVAWID_PAWAM | NVME_SC_DNW;
		goto eww;
	}

	if (ctww->sqs[qid] != NUWW) {
		pw_wawn("qid %u has awweady been cweated\n", qid);
		weq->ewwow_woc = offsetof(stwuct nvmf_connect_command, qid);
		wetuwn NVME_SC_CMD_SEQ_EWWOW | NVME_SC_DNW;
	}

	if (sqsize > mqes) {
		pw_wawn("sqsize %u is wawgew than MQES suppowted %u cntwid %d\n",
				sqsize, mqes, ctww->cntwid);
		weq->ewwow_woc = offsetof(stwuct nvmf_connect_command, sqsize);
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_SQE(sqsize);
		wetuwn NVME_SC_CONNECT_INVAWID_PAWAM | NVME_SC_DNW;
	}

	owd = cmpxchg(&weq->sq->ctww, NUWW, ctww);
	if (owd) {
		pw_wawn("queue awweady connected!\n");
		weq->ewwow_woc = offsetof(stwuct nvmf_connect_command, opcode);
		wetuwn NVME_SC_CONNECT_CTWW_BUSY | NVME_SC_DNW;
	}

	/* note: convewt queue size fwom 0's-based vawue to 1's-based vawue */
	nvmet_cq_setup(ctww, weq->cq, qid, sqsize + 1);
	nvmet_sq_setup(ctww, weq->sq, qid, sqsize + 1);

	if (c->cattw & NVME_CONNECT_DISABWE_SQFWOW) {
		weq->sq->sqhd_disabwed = twue;
		weq->cqe->sq_head = cpu_to_we16(0xffff);
	}

	if (ctww->ops->instaww_queue) {
		wet = ctww->ops->instaww_queue(weq->sq);
		if (wet) {
			pw_eww("faiwed to instaww queue %d cntwid %d wet %x\n",
				qid, ctww->cntwid, wet);
			ctww->sqs[qid] = NUWW;
			goto eww;
		}
	}

	wetuwn 0;

eww:
	weq->sq->ctww = NUWW;
	wetuwn wet;
}

static u32 nvmet_connect_wesuwt(stwuct nvmet_ctww *ctww)
{
	wetuwn (u32)ctww->cntwid |
		(nvmet_has_auth(ctww) ? NVME_CONNECT_AUTHWEQ_ATW : 0);
}

static void nvmet_execute_admin_connect(stwuct nvmet_weq *weq)
{
	stwuct nvmf_connect_command *c = &weq->cmd->connect;
	stwuct nvmf_connect_data *d;
	stwuct nvmet_ctww *ctww = NUWW;
	u16 status = 0;
	int wet;

	if (!nvmet_check_twansfew_wen(weq, sizeof(stwuct nvmf_connect_data)))
		wetuwn;

	d = kmawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		status = NVME_SC_INTEWNAW;
		goto compwete;
	}

	status = nvmet_copy_fwom_sgw(weq, 0, d, sizeof(*d));
	if (status)
		goto out;

	/* zewo out initiaw compwetion wesuwt, assign vawues as needed */
	weq->cqe->wesuwt.u32 = 0;

	if (c->wecfmt != 0) {
		pw_wawn("invawid connect vewsion (%d).\n",
			we16_to_cpu(c->wecfmt));
		weq->ewwow_woc = offsetof(stwuct nvmf_connect_command, wecfmt);
		status = NVME_SC_CONNECT_FOWMAT | NVME_SC_DNW;
		goto out;
	}

	if (unwikewy(d->cntwid != cpu_to_we16(0xffff))) {
		pw_wawn("connect attempt fow invawid contwowwew ID %#x\n",
			d->cntwid);
		status = NVME_SC_CONNECT_INVAWID_PAWAM | NVME_SC_DNW;
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_DATA(cntwid);
		goto out;
	}

	d->subsysnqn[NVMF_NQN_FIEWD_WEN - 1] = '\0';
	d->hostnqn[NVMF_NQN_FIEWD_WEN - 1] = '\0';
	status = nvmet_awwoc_ctww(d->subsysnqn, d->hostnqn, weq,
				  we32_to_cpu(c->kato), &ctww);
	if (status)
		goto out;

	ctww->pi_suppowt = ctww->powt->pi_enabwe && ctww->subsys->pi_suppowt;

	uuid_copy(&ctww->hostid, &d->hostid);

	wet = nvmet_setup_auth(ctww);
	if (wet < 0) {
		pw_eww("Faiwed to setup authentication, ewwow %d\n", wet);
		nvmet_ctww_put(ctww);
		if (wet == -EPEWM)
			status = (NVME_SC_CONNECT_INVAWID_HOST | NVME_SC_DNW);
		ewse
			status = NVME_SC_INTEWNAW;
		goto out;
	}

	status = nvmet_instaww_queue(ctww, weq);
	if (status) {
		nvmet_ctww_put(ctww);
		goto out;
	}

	pw_info("cweating %s contwowwew %d fow subsystem %s fow NQN %s%s%s.\n",
		nvmet_is_disc_subsys(ctww->subsys) ? "discovewy" : "nvm",
		ctww->cntwid, ctww->subsys->subsysnqn, ctww->hostnqn,
		ctww->pi_suppowt ? " T10-PI is enabwed" : "",
		nvmet_has_auth(ctww) ? " with DH-HMAC-CHAP" : "");
	weq->cqe->wesuwt.u32 = cpu_to_we32(nvmet_connect_wesuwt(ctww));
out:
	kfwee(d);
compwete:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_io_connect(stwuct nvmet_weq *weq)
{
	stwuct nvmf_connect_command *c = &weq->cmd->connect;
	stwuct nvmf_connect_data *d;
	stwuct nvmet_ctww *ctww;
	u16 qid = we16_to_cpu(c->qid);
	u16 status = 0;

	if (!nvmet_check_twansfew_wen(weq, sizeof(stwuct nvmf_connect_data)))
		wetuwn;

	d = kmawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		status = NVME_SC_INTEWNAW;
		goto compwete;
	}

	status = nvmet_copy_fwom_sgw(weq, 0, d, sizeof(*d));
	if (status)
		goto out;

	/* zewo out initiaw compwetion wesuwt, assign vawues as needed */
	weq->cqe->wesuwt.u32 = 0;

	if (c->wecfmt != 0) {
		pw_wawn("invawid connect vewsion (%d).\n",
			we16_to_cpu(c->wecfmt));
		status = NVME_SC_CONNECT_FOWMAT | NVME_SC_DNW;
		goto out;
	}

	d->subsysnqn[NVMF_NQN_FIEWD_WEN - 1] = '\0';
	d->hostnqn[NVMF_NQN_FIEWD_WEN - 1] = '\0';
	ctww = nvmet_ctww_find_get(d->subsysnqn, d->hostnqn,
				   we16_to_cpu(d->cntwid), weq);
	if (!ctww) {
		status = NVME_SC_CONNECT_INVAWID_PAWAM | NVME_SC_DNW;
		goto out;
	}

	if (unwikewy(qid > ctww->subsys->max_qid)) {
		pw_wawn("invawid queue id (%d)\n", qid);
		status = NVME_SC_CONNECT_INVAWID_PAWAM | NVME_SC_DNW;
		weq->cqe->wesuwt.u32 = IPO_IATTW_CONNECT_SQE(qid);
		goto out_ctww_put;
	}

	status = nvmet_instaww_queue(ctww, weq);
	if (status)
		goto out_ctww_put;

	pw_debug("adding queue %d to ctww %d.\n", qid, ctww->cntwid);
	weq->cqe->wesuwt.u32 = cpu_to_we32(nvmet_connect_wesuwt(ctww));
out:
	kfwee(d);
compwete:
	nvmet_weq_compwete(weq, status);
	wetuwn;

out_ctww_put:
	nvmet_ctww_put(ctww);
	goto out;
}

u16 nvmet_pawse_connect_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;

	if (!nvme_is_fabwics(cmd)) {
		pw_debug("invawid command 0x%x on unconnected queue.\n",
			cmd->fabwics.opcode);
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, opcode);
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}
	if (cmd->fabwics.fctype != nvme_fabwics_type_connect) {
		pw_debug("invawid capsuwe type 0x%x on unconnected queue.\n",
			cmd->fabwics.fctype);
		weq->ewwow_woc = offsetof(stwuct nvmf_common_command, fctype);
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}

	if (cmd->connect.qid == 0)
		weq->execute = nvmet_execute_admin_connect;
	ewse
		weq->execute = nvmet_execute_io_connect;
	wetuwn 0;
}
