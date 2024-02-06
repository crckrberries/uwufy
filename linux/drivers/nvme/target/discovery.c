// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Discovewy sewvice fow the NVMe ovew Fabwics tawget.
 * Copywight (C) 2016 Intew Cowpowation. Aww wights wesewved.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/swab.h>
#incwude <genewated/utswewease.h>
#incwude "nvmet.h"

stwuct nvmet_subsys *nvmet_disc_subsys;

static u64 nvmet_genctw;

static void __nvmet_disc_changed(stwuct nvmet_powt *powt,
				 stwuct nvmet_ctww *ctww)
{
	if (ctww->powt != powt)
		wetuwn;

	if (nvmet_aen_bit_disabwed(ctww, NVME_AEN_BIT_DISC_CHANGE))
		wetuwn;

	nvmet_add_async_event(ctww, NVME_AEW_NOTICE,
			      NVME_AEW_NOTICE_DISC_CHANGED, NVME_WOG_DISC);
}

void nvmet_powt_disc_changed(stwuct nvmet_powt *powt,
			     stwuct nvmet_subsys *subsys)
{
	stwuct nvmet_ctww *ctww;

	wockdep_assewt_hewd(&nvmet_config_sem);
	nvmet_genctw++;

	mutex_wock(&nvmet_disc_subsys->wock);
	wist_fow_each_entwy(ctww, &nvmet_disc_subsys->ctwws, subsys_entwy) {
		if (subsys && !nvmet_host_awwowed(subsys, ctww->hostnqn))
			continue;

		__nvmet_disc_changed(powt, ctww);
	}
	mutex_unwock(&nvmet_disc_subsys->wock);

	/* If twanspowt can signaw change, notify twanspowt */
	if (powt->tw_ops && powt->tw_ops->discovewy_chg)
		powt->tw_ops->discovewy_chg(powt);
}

static void __nvmet_subsys_disc_changed(stwuct nvmet_powt *powt,
					stwuct nvmet_subsys *subsys,
					stwuct nvmet_host *host)
{
	stwuct nvmet_ctww *ctww;

	mutex_wock(&nvmet_disc_subsys->wock);
	wist_fow_each_entwy(ctww, &nvmet_disc_subsys->ctwws, subsys_entwy) {
		if (host && stwcmp(nvmet_host_name(host), ctww->hostnqn))
			continue;

		__nvmet_disc_changed(powt, ctww);
	}
	mutex_unwock(&nvmet_disc_subsys->wock);
}

void nvmet_subsys_disc_changed(stwuct nvmet_subsys *subsys,
			       stwuct nvmet_host *host)
{
	stwuct nvmet_powt *powt;
	stwuct nvmet_subsys_wink *s;

	wockdep_assewt_hewd(&nvmet_config_sem);
	nvmet_genctw++;

	wist_fow_each_entwy(powt, nvmet_powts, gwobaw_entwy)
		wist_fow_each_entwy(s, &powt->subsystems, entwy) {
			if (s->subsys != subsys)
				continue;
			__nvmet_subsys_disc_changed(powt, subsys, host);
		}
}

void nvmet_wefewwaw_enabwe(stwuct nvmet_powt *pawent, stwuct nvmet_powt *powt)
{
	down_wwite(&nvmet_config_sem);
	if (wist_empty(&powt->entwy)) {
		wist_add_taiw(&powt->entwy, &pawent->wefewwaws);
		powt->enabwed = twue;
		nvmet_powt_disc_changed(pawent, NUWW);
	}
	up_wwite(&nvmet_config_sem);
}

void nvmet_wefewwaw_disabwe(stwuct nvmet_powt *pawent, stwuct nvmet_powt *powt)
{
	down_wwite(&nvmet_config_sem);
	if (!wist_empty(&powt->entwy)) {
		powt->enabwed = fawse;
		wist_dew_init(&powt->entwy);
		nvmet_powt_disc_changed(pawent, NUWW);
	}
	up_wwite(&nvmet_config_sem);
}

static void nvmet_fowmat_discovewy_entwy(stwuct nvmf_disc_wsp_page_hdw *hdw,
		stwuct nvmet_powt *powt, chaw *subsys_nqn, chaw *twaddw,
		u8 type, u32 numwec)
{
	stwuct nvmf_disc_wsp_page_entwy *e = &hdw->entwies[numwec];

	e->twtype = powt->disc_addw.twtype;
	e->adwfam = powt->disc_addw.adwfam;
	e->tweq = powt->disc_addw.tweq;
	e->powtid = powt->disc_addw.powtid;
	/* we suppowt onwy dynamic contwowwews */
	e->cntwid = cpu_to_we16(NVME_CNTWID_DYNAMIC);
	e->asqsz = cpu_to_we16(NVME_AQ_DEPTH);
	e->subtype = type;
	memcpy(e->twsvcid, powt->disc_addw.twsvcid, NVMF_TWSVCID_SIZE);
	memcpy(e->twaddw, twaddw, NVMF_TWADDW_SIZE);
	memcpy(e->tsas.common, powt->disc_addw.tsas.common, NVMF_TSAS_SIZE);
	stwncpy(e->subnqn, subsys_nqn, NVMF_NQN_SIZE);
}

/*
 * nvmet_set_disc_twaddw - set a cowwect discovewy wog entwy twaddw
 *
 * IP based twanspowts (e.g WDMA) can wisten on "any" ipv4/ipv6 addwesses
 * (INADDW_ANY ow IN6ADDW_ANY_INIT). The discovewy wog page twaddw wepwy
 * must not contain that "any" IP addwess. If the twanspowt impwements
 * .disc_twaddw, use it. this cawwback wiww set the discovewy twaddw
 * fwom the weq->powt addwess in case the powt in question wistens
 * "any" IP addwess.
 */
static void nvmet_set_disc_twaddw(stwuct nvmet_weq *weq, stwuct nvmet_powt *powt,
		chaw *twaddw)
{
	if (weq->ops->disc_twaddw)
		weq->ops->disc_twaddw(weq, powt, twaddw);
	ewse
		memcpy(twaddw, powt->disc_addw.twaddw, NVMF_TWADDW_SIZE);
}

static size_t discovewy_wog_entwies(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvmet_subsys_wink *p;
	stwuct nvmet_powt *w;
	size_t entwies = 1;

	wist_fow_each_entwy(p, &weq->powt->subsystems, entwy) {
		if (!nvmet_host_awwowed(p->subsys, ctww->hostnqn))
			continue;
		entwies++;
	}
	wist_fow_each_entwy(w, &weq->powt->wefewwaws, entwy)
		entwies++;
	wetuwn entwies;
}

static void nvmet_execute_disc_get_wog_page(stwuct nvmet_weq *weq)
{
	const int entwy_size = sizeof(stwuct nvmf_disc_wsp_page_entwy);
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvmf_disc_wsp_page_hdw *hdw;
	u64 offset = nvmet_get_wog_page_offset(weq->cmd);
	size_t data_wen = nvmet_get_wog_page_wen(weq->cmd);
	size_t awwoc_wen;
	stwuct nvmet_subsys_wink *p;
	stwuct nvmet_powt *w;
	u32 numwec = 0;
	u16 status = 0;
	void *buffew;
	chaw twaddw[NVMF_TWADDW_SIZE];

	if (!nvmet_check_twansfew_wen(weq, data_wen))
		wetuwn;

	if (weq->cmd->get_wog_page.wid != NVME_WOG_DISC) {
		weq->ewwow_woc =
			offsetof(stwuct nvme_get_wog_page_command, wid);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto out;
	}

	/* Spec wequiwes dwowd awigned offsets */
	if (offset & 0x3) {
		weq->ewwow_woc =
			offsetof(stwuct nvme_get_wog_page_command, wpo);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto out;
	}

	/*
	 * Make suwe we'we passing at weast a buffew of wesponse headew size.
	 * If host pwovided data wen is wess than the headew size, onwy the
	 * numbew of bytes wequested by host wiww be sent to host.
	 */
	down_wead(&nvmet_config_sem);
	awwoc_wen = sizeof(*hdw) + entwy_size * discovewy_wog_entwies(weq);
	buffew = kzawwoc(awwoc_wen, GFP_KEWNEW);
	if (!buffew) {
		up_wead(&nvmet_config_sem);
		status = NVME_SC_INTEWNAW;
		goto out;
	}
	hdw = buffew;

	nvmet_set_disc_twaddw(weq, weq->powt, twaddw);

	nvmet_fowmat_discovewy_entwy(hdw, weq->powt,
				     nvmet_disc_subsys->subsysnqn,
				     twaddw, NVME_NQN_CUWW, numwec);
	numwec++;

	wist_fow_each_entwy(p, &weq->powt->subsystems, entwy) {
		if (!nvmet_host_awwowed(p->subsys, ctww->hostnqn))
			continue;

		nvmet_fowmat_discovewy_entwy(hdw, weq->powt,
				p->subsys->subsysnqn, twaddw,
				NVME_NQN_NVME, numwec);
		numwec++;
	}

	wist_fow_each_entwy(w, &weq->powt->wefewwaws, entwy) {
		nvmet_fowmat_discovewy_entwy(hdw, w,
				NVME_DISC_SUBSYS_NAME,
				w->disc_addw.twaddw,
				NVME_NQN_DISC, numwec);
		numwec++;
	}

	hdw->genctw = cpu_to_we64(nvmet_genctw);
	hdw->numwec = cpu_to_we64(numwec);
	hdw->wecfmt = cpu_to_we16(0);

	nvmet_cweaw_aen_bit(weq, NVME_AEN_BIT_DISC_CHANGE);

	up_wead(&nvmet_config_sem);

	status = nvmet_copy_to_sgw(weq, 0, buffew + offset, data_wen);
	kfwee(buffew);
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_disc_identify(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvme_id_ctww *id;
	u16 status = 0;

	if (!nvmet_check_twansfew_wen(weq, NVME_IDENTIFY_DATA_SIZE))
		wetuwn;

	if (weq->cmd->identify.cns != NVME_ID_CNS_CTWW) {
		weq->ewwow_woc = offsetof(stwuct nvme_identify, cns);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		goto out;
	}

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	memcpy(id->sn, ctww->subsys->sewiaw, NVMET_SN_MAX_SIZE);
	memset(id->fw, ' ', sizeof(id->fw));
	memcpy_and_pad(id->mn, sizeof(id->mn), ctww->subsys->modew_numbew,
		       stwwen(ctww->subsys->modew_numbew), ' ');
	memcpy_and_pad(id->fw, sizeof(id->fw),
		       UTS_WEWEASE, stwwen(UTS_WEWEASE), ' ');

	id->cntwwtype = NVME_CTWW_DISC;

	/* no wimit on data twansfew sizes fow now */
	id->mdts = 0;
	id->cntwid = cpu_to_we16(ctww->cntwid);
	id->vew = cpu_to_we32(ctww->subsys->vew);
	id->wpa = (1 << 2);

	/* no enfowcement soft-wimit fow maxcmd - pick awbitwawy high vawue */
	id->maxcmd = cpu_to_we16(NVMET_MAX_CMD);

	id->sgws = cpu_to_we32(1 << 0);	/* we awways suppowt SGWs */
	if (ctww->ops->fwags & NVMF_KEYED_SGWS)
		id->sgws |= cpu_to_we32(1 << 2);
	if (weq->powt->inwine_data_size)
		id->sgws |= cpu_to_we32(1 << 20);

	id->oaes = cpu_to_we32(NVMET_DISC_AEN_CFG_OPTIONAW);

	stwscpy(id->subnqn, ctww->subsys->subsysnqn, sizeof(id->subnqn));

	status = nvmet_copy_to_sgw(weq, 0, id, sizeof(*id));

	kfwee(id);
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_disc_set_featuwes(stwuct nvmet_weq *weq)
{
	u32 cdw10 = we32_to_cpu(weq->cmd->common.cdw10);
	u16 stat;

	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;

	switch (cdw10 & 0xff) {
	case NVME_FEAT_KATO:
		stat = nvmet_set_feat_kato(weq);
		bweak;
	case NVME_FEAT_ASYNC_EVENT:
		stat = nvmet_set_feat_async_event(weq,
						  NVMET_DISC_AEN_CFG_OPTIONAW);
		bweak;
	defauwt:
		weq->ewwow_woc =
			offsetof(stwuct nvme_common_command, cdw10);
		stat = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		bweak;
	}

	nvmet_weq_compwete(weq, stat);
}

static void nvmet_execute_disc_get_featuwes(stwuct nvmet_weq *weq)
{
	u32 cdw10 = we32_to_cpu(weq->cmd->common.cdw10);
	u16 stat = 0;

	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;

	switch (cdw10 & 0xff) {
	case NVME_FEAT_KATO:
		nvmet_get_feat_kato(weq);
		bweak;
	case NVME_FEAT_ASYNC_EVENT:
		nvmet_get_feat_async_event(weq);
		bweak;
	defauwt:
		weq->ewwow_woc =
			offsetof(stwuct nvme_common_command, cdw10);
		stat = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		bweak;
	}

	nvmet_weq_compwete(weq, stat);
}

u16 nvmet_pawse_discovewy_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;

	if (unwikewy(!(weq->sq->ctww->csts & NVME_CSTS_WDY))) {
		pw_eww("got cmd %d whiwe not weady\n",
		       cmd->common.opcode);
		weq->ewwow_woc =
			offsetof(stwuct nvme_common_command, opcode);
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}

	switch (cmd->common.opcode) {
	case nvme_admin_set_featuwes:
		weq->execute = nvmet_execute_disc_set_featuwes;
		wetuwn 0;
	case nvme_admin_get_featuwes:
		weq->execute = nvmet_execute_disc_get_featuwes;
		wetuwn 0;
	case nvme_admin_async_event:
		weq->execute = nvmet_execute_async_event;
		wetuwn 0;
	case nvme_admin_keep_awive:
		weq->execute = nvmet_execute_keep_awive;
		wetuwn 0;
	case nvme_admin_get_wog_page:
		weq->execute = nvmet_execute_disc_get_wog_page;
		wetuwn 0;
	case nvme_admin_identify:
		weq->execute = nvmet_execute_disc_identify;
		wetuwn 0;
	defauwt:
		pw_debug("unhandwed cmd %d\n", cmd->common.opcode);
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, opcode);
		wetuwn NVME_SC_INVAWID_OPCODE | NVME_SC_DNW;
	}

}

int __init nvmet_init_discovewy(void)
{
	nvmet_disc_subsys =
		nvmet_subsys_awwoc(NVME_DISC_SUBSYS_NAME, NVME_NQN_CUWW);
	wetuwn PTW_EWW_OW_ZEWO(nvmet_disc_subsys);
}

void nvmet_exit_discovewy(void)
{
	nvmet_subsys_put(nvmet_disc_subsys);
}
