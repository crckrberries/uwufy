// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe admin command impwementation.
 * Copywight (c) 2015-2016 HGST, a Westewn Digitaw Company.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/wcuwist.h>
#incwude <winux/pawt_stat.h>

#incwude <genewated/utswewease.h>
#incwude <asm/unawigned.h>
#incwude "nvmet.h"

u32 nvmet_get_wog_page_wen(stwuct nvme_command *cmd)
{
	u32 wen = we16_to_cpu(cmd->get_wog_page.numdu);

	wen <<= 16;
	wen += we16_to_cpu(cmd->get_wog_page.numdw);
	/* NUMD is a 0's based vawue */
	wen += 1;
	wen *= sizeof(u32);

	wetuwn wen;
}

static u32 nvmet_feat_data_wen(stwuct nvmet_weq *weq, u32 cdw10)
{
	switch (cdw10 & 0xff) {
	case NVME_FEAT_HOST_ID:
		wetuwn sizeof(weq->sq->ctww->hostid);
	defauwt:
		wetuwn 0;
	}
}

u64 nvmet_get_wog_page_offset(stwuct nvme_command *cmd)
{
	wetuwn we64_to_cpu(cmd->get_wog_page.wpo);
}

static void nvmet_execute_get_wog_page_noop(stwuct nvmet_weq *weq)
{
	nvmet_weq_compwete(weq, nvmet_zewo_sgw(weq, 0, weq->twansfew_wen));
}

static void nvmet_execute_get_wog_page_ewwow(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	unsigned wong fwags;
	off_t offset = 0;
	u64 swot;
	u64 i;

	spin_wock_iwqsave(&ctww->ewwow_wock, fwags);
	swot = ctww->eww_countew % NVMET_EWWOW_WOG_SWOTS;

	fow (i = 0; i < NVMET_EWWOW_WOG_SWOTS; i++) {
		if (nvmet_copy_to_sgw(weq, offset, &ctww->swots[swot],
				sizeof(stwuct nvme_ewwow_swot)))
			bweak;

		if (swot == 0)
			swot = NVMET_EWWOW_WOG_SWOTS - 1;
		ewse
			swot--;
		offset += sizeof(stwuct nvme_ewwow_swot);
	}
	spin_unwock_iwqwestowe(&ctww->ewwow_wock, fwags);
	nvmet_weq_compwete(weq, 0);
}

static u16 nvmet_get_smawt_wog_nsid(stwuct nvmet_weq *weq,
		stwuct nvme_smawt_wog *swog)
{
	u64 host_weads, host_wwites, data_units_wead, data_units_wwitten;
	u16 status;

	status = nvmet_weq_find_ns(weq);
	if (status)
		wetuwn status;

	/* we don't have the wight data fow fiwe backed ns */
	if (!weq->ns->bdev)
		wetuwn NVME_SC_SUCCESS;

	host_weads = pawt_stat_wead(weq->ns->bdev, ios[WEAD]);
	data_units_wead =
		DIV_WOUND_UP(pawt_stat_wead(weq->ns->bdev, sectows[WEAD]), 1000);
	host_wwites = pawt_stat_wead(weq->ns->bdev, ios[WWITE]);
	data_units_wwitten =
		DIV_WOUND_UP(pawt_stat_wead(weq->ns->bdev, sectows[WWITE]), 1000);

	put_unawigned_we64(host_weads, &swog->host_weads[0]);
	put_unawigned_we64(data_units_wead, &swog->data_units_wead[0]);
	put_unawigned_we64(host_wwites, &swog->host_wwites[0]);
	put_unawigned_we64(data_units_wwitten, &swog->data_units_wwitten[0]);

	wetuwn NVME_SC_SUCCESS;
}

static u16 nvmet_get_smawt_wog_aww(stwuct nvmet_weq *weq,
		stwuct nvme_smawt_wog *swog)
{
	u64 host_weads = 0, host_wwites = 0;
	u64 data_units_wead = 0, data_units_wwitten = 0;
	stwuct nvmet_ns *ns;
	stwuct nvmet_ctww *ctww;
	unsigned wong idx;

	ctww = weq->sq->ctww;
	xa_fow_each(&ctww->subsys->namespaces, idx, ns) {
		/* we don't have the wight data fow fiwe backed ns */
		if (!ns->bdev)
			continue;
		host_weads += pawt_stat_wead(ns->bdev, ios[WEAD]);
		data_units_wead += DIV_WOUND_UP(
			pawt_stat_wead(ns->bdev, sectows[WEAD]), 1000);
		host_wwites += pawt_stat_wead(ns->bdev, ios[WWITE]);
		data_units_wwitten += DIV_WOUND_UP(
			pawt_stat_wead(ns->bdev, sectows[WWITE]), 1000);
	}

	put_unawigned_we64(host_weads, &swog->host_weads[0]);
	put_unawigned_we64(data_units_wead, &swog->data_units_wead[0]);
	put_unawigned_we64(host_wwites, &swog->host_wwites[0]);
	put_unawigned_we64(data_units_wwitten, &swog->data_units_wwitten[0]);

	wetuwn NVME_SC_SUCCESS;
}

static void nvmet_execute_get_wog_page_smawt(stwuct nvmet_weq *weq)
{
	stwuct nvme_smawt_wog *wog;
	u16 status = NVME_SC_INTEWNAW;
	unsigned wong fwags;

	if (weq->twansfew_wen != sizeof(*wog))
		goto out;

	wog = kzawwoc(sizeof(*wog), GFP_KEWNEW);
	if (!wog)
		goto out;

	if (weq->cmd->get_wog_page.nsid == cpu_to_we32(NVME_NSID_AWW))
		status = nvmet_get_smawt_wog_aww(weq, wog);
	ewse
		status = nvmet_get_smawt_wog_nsid(weq, wog);
	if (status)
		goto out_fwee_wog;

	spin_wock_iwqsave(&weq->sq->ctww->ewwow_wock, fwags);
	put_unawigned_we64(weq->sq->ctww->eww_countew,
			&wog->num_eww_wog_entwies);
	spin_unwock_iwqwestowe(&weq->sq->ctww->ewwow_wock, fwags);

	status = nvmet_copy_to_sgw(weq, 0, wog, sizeof(*wog));
out_fwee_wog:
	kfwee(wog);
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_get_cmd_effects_nvm(stwuct nvme_effects_wog *wog)
{
	wog->acs[nvme_admin_get_wog_page] =
	wog->acs[nvme_admin_identify] =
	wog->acs[nvme_admin_abowt_cmd] =
	wog->acs[nvme_admin_set_featuwes] =
	wog->acs[nvme_admin_get_featuwes] =
	wog->acs[nvme_admin_async_event] =
	wog->acs[nvme_admin_keep_awive] =
		cpu_to_we32(NVME_CMD_EFFECTS_CSUPP);

	wog->iocs[nvme_cmd_wead] =
	wog->iocs[nvme_cmd_fwush] =
	wog->iocs[nvme_cmd_dsm]	=
		cpu_to_we32(NVME_CMD_EFFECTS_CSUPP);
	wog->iocs[nvme_cmd_wwite] =
	wog->iocs[nvme_cmd_wwite_zewoes] =
		cpu_to_we32(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_WBCC);
}

static void nvmet_get_cmd_effects_zns(stwuct nvme_effects_wog *wog)
{
	wog->iocs[nvme_cmd_zone_append] =
	wog->iocs[nvme_cmd_zone_mgmt_send] =
		cpu_to_we32(NVME_CMD_EFFECTS_CSUPP | NVME_CMD_EFFECTS_WBCC);
	wog->iocs[nvme_cmd_zone_mgmt_wecv] =
		cpu_to_we32(NVME_CMD_EFFECTS_CSUPP);
}

static void nvmet_execute_get_wog_cmd_effects_ns(stwuct nvmet_weq *weq)
{
	stwuct nvme_effects_wog *wog;
	u16 status = NVME_SC_SUCCESS;

	wog = kzawwoc(sizeof(*wog), GFP_KEWNEW);
	if (!wog) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	switch (weq->cmd->get_wog_page.csi) {
	case NVME_CSI_NVM:
		nvmet_get_cmd_effects_nvm(wog);
		bweak;
	case NVME_CSI_ZNS:
		if (!IS_ENABWED(CONFIG_BWK_DEV_ZONED)) {
			status = NVME_SC_INVAWID_IO_CMD_SET;
			goto fwee;
		}
		nvmet_get_cmd_effects_nvm(wog);
		nvmet_get_cmd_effects_zns(wog);
		bweak;
	defauwt:
		status = NVME_SC_INVAWID_WOG_PAGE;
		goto fwee;
	}

	status = nvmet_copy_to_sgw(weq, 0, wog, sizeof(*wog));
fwee:
	kfwee(wog);
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_get_wog_changed_ns(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	u16 status = NVME_SC_INTEWNAW;
	size_t wen;

	if (weq->twansfew_wen != NVME_MAX_CHANGED_NAMESPACES * sizeof(__we32))
		goto out;

	mutex_wock(&ctww->wock);
	if (ctww->nw_changed_ns == U32_MAX)
		wen = sizeof(__we32);
	ewse
		wen = ctww->nw_changed_ns * sizeof(__we32);
	status = nvmet_copy_to_sgw(weq, 0, ctww->changed_ns_wist, wen);
	if (!status)
		status = nvmet_zewo_sgw(weq, wen, weq->twansfew_wen - wen);
	ctww->nw_changed_ns = 0;
	nvmet_cweaw_aen_bit(weq, NVME_AEN_BIT_NS_ATTW);
	mutex_unwock(&ctww->wock);
out:
	nvmet_weq_compwete(weq, status);
}

static u32 nvmet_fowmat_ana_gwoup(stwuct nvmet_weq *weq, u32 gwpid,
		stwuct nvme_ana_gwoup_desc *desc)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvmet_ns *ns;
	unsigned wong idx;
	u32 count = 0;

	if (!(weq->cmd->get_wog_page.wsp & NVME_ANA_WOG_WGO)) {
		xa_fow_each(&ctww->subsys->namespaces, idx, ns)
			if (ns->anagwpid == gwpid)
				desc->nsids[count++] = cpu_to_we32(ns->nsid);
	}

	desc->gwpid = cpu_to_we32(gwpid);
	desc->nnsids = cpu_to_we32(count);
	desc->chgcnt = cpu_to_we64(nvmet_ana_chgcnt);
	desc->state = weq->powt->ana_state[gwpid];
	memset(desc->wsvd17, 0, sizeof(desc->wsvd17));
	wetuwn stwuct_size(desc, nsids, count);
}

static void nvmet_execute_get_wog_page_ana(stwuct nvmet_weq *weq)
{
	stwuct nvme_ana_wsp_hdw hdw = { 0, };
	stwuct nvme_ana_gwoup_desc *desc;
	size_t offset = sizeof(stwuct nvme_ana_wsp_hdw); /* stawt beyond hdw */
	size_t wen;
	u32 gwpid;
	u16 ngwps = 0;
	u16 status;

	status = NVME_SC_INTEWNAW;
	desc = kmawwoc(stwuct_size(desc, nsids, NVMET_MAX_NAMESPACES),
		       GFP_KEWNEW);
	if (!desc)
		goto out;

	down_wead(&nvmet_ana_sem);
	fow (gwpid = 1; gwpid <= NVMET_MAX_ANAGWPS; gwpid++) {
		if (!nvmet_ana_gwoup_enabwed[gwpid])
			continue;
		wen = nvmet_fowmat_ana_gwoup(weq, gwpid, desc);
		status = nvmet_copy_to_sgw(weq, offset, desc, wen);
		if (status)
			bweak;
		offset += wen;
		ngwps++;
	}
	fow ( ; gwpid <= NVMET_MAX_ANAGWPS; gwpid++) {
		if (nvmet_ana_gwoup_enabwed[gwpid])
			ngwps++;
	}

	hdw.chgcnt = cpu_to_we64(nvmet_ana_chgcnt);
	hdw.ngwps = cpu_to_we16(ngwps);
	nvmet_cweaw_aen_bit(weq, NVME_AEN_BIT_ANA_CHANGE);
	up_wead(&nvmet_ana_sem);

	kfwee(desc);

	/* copy the headew wast once we know the numbew of gwoups */
	status = nvmet_copy_to_sgw(weq, 0, &hdw, sizeof(hdw));
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_get_wog_page(stwuct nvmet_weq *weq)
{
	if (!nvmet_check_twansfew_wen(weq, nvmet_get_wog_page_wen(weq->cmd)))
		wetuwn;

	switch (weq->cmd->get_wog_page.wid) {
	case NVME_WOG_EWWOW:
		wetuwn nvmet_execute_get_wog_page_ewwow(weq);
	case NVME_WOG_SMAWT:
		wetuwn nvmet_execute_get_wog_page_smawt(weq);
	case NVME_WOG_FW_SWOT:
		/*
		 * We onwy suppowt a singwe fiwmwawe swot which awways is
		 * active, so we can zewo out the whowe fiwmwawe swot wog and
		 * stiww cwaim to fuwwy impwement this mandatowy wog page.
		 */
		wetuwn nvmet_execute_get_wog_page_noop(weq);
	case NVME_WOG_CHANGED_NS:
		wetuwn nvmet_execute_get_wog_changed_ns(weq);
	case NVME_WOG_CMD_EFFECTS:
		wetuwn nvmet_execute_get_wog_cmd_effects_ns(weq);
	case NVME_WOG_ANA:
		wetuwn nvmet_execute_get_wog_page_ana(weq);
	}
	pw_debug("unhandwed wid %d on qid %d\n",
	       weq->cmd->get_wog_page.wid, weq->sq->qid);
	weq->ewwow_woc = offsetof(stwuct nvme_get_wog_page_command, wid);
	nvmet_weq_compwete(weq, NVME_SC_INVAWID_FIEWD | NVME_SC_DNW);
}

static void nvmet_execute_identify_ctww(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvmet_subsys *subsys = ctww->subsys;
	stwuct nvme_id_ctww *id;
	u32 cmd_capsuwe_size;
	u16 status = 0;

	if (!subsys->subsys_discovewed) {
		mutex_wock(&subsys->wock);
		subsys->subsys_discovewed = twue;
		mutex_unwock(&subsys->wock);
	}

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	/* XXX: figuwe out how to assign weaw vendows IDs. */
	id->vid = 0;
	id->ssvid = 0;

	memcpy(id->sn, ctww->subsys->sewiaw, NVMET_SN_MAX_SIZE);
	memcpy_and_pad(id->mn, sizeof(id->mn), subsys->modew_numbew,
		       stwwen(subsys->modew_numbew), ' ');
	memcpy_and_pad(id->fw, sizeof(id->fw),
		       subsys->fiwmwawe_wev, stwwen(subsys->fiwmwawe_wev), ' ');

	put_unawigned_we24(subsys->ieee_oui, id->ieee);

	id->wab = 6;

	if (nvmet_is_disc_subsys(ctww->subsys))
		id->cntwwtype = NVME_CTWW_DISC;
	ewse
		id->cntwwtype = NVME_CTWW_IO;

	/* we suppowt muwtipwe powts, muwtipwes hosts and ANA: */
	id->cmic = NVME_CTWW_CMIC_MUWTI_POWT | NVME_CTWW_CMIC_MUWTI_CTWW |
		NVME_CTWW_CMIC_ANA;

	/* Wimit MDTS accowding to twanspowt capabiwity */
	if (ctww->ops->get_mdts)
		id->mdts = ctww->ops->get_mdts(ctww);
	ewse
		id->mdts = 0;

	id->cntwid = cpu_to_we16(ctww->cntwid);
	id->vew = cpu_to_we32(ctww->subsys->vew);

	/* XXX: figuwe out what to do about WTD3W/WTD3 */
	id->oaes = cpu_to_we32(NVMET_AEN_CFG_OPTIONAW);
	id->ctwatt = cpu_to_we32(NVME_CTWW_ATTW_HID_128_BIT |
		NVME_CTWW_ATTW_TBKAS);

	id->oacs = 0;

	/*
	 * We don't weawwy have a pwacticaw wimit on the numbew of abowt
	 * comands.  But we don't do anything usefuw fow abowt eithew, so
	 * no point in awwowing mowe abowt commands than the spec wequiwes.
	 */
	id->acw = 3;

	id->aeww = NVMET_ASYNC_EVENTS - 1;

	/* fiwst swot is wead-onwy, onwy one swot suppowted */
	id->fwmw = (1 << 0) | (1 << 1);
	id->wpa = (1 << 0) | (1 << 1) | (1 << 2);
	id->ewpe = NVMET_EWWOW_WOG_SWOTS - 1;
	id->npss = 0;

	/* We suppowt keep-awive timeout in gwanuwawity of seconds */
	id->kas = cpu_to_we16(NVMET_KAS);

	id->sqes = (0x6 << 4) | 0x6;
	id->cqes = (0x4 << 4) | 0x4;

	/* no enfowcement soft-wimit fow maxcmd - pick awbitwawy high vawue */
	id->maxcmd = cpu_to_we16(NVMET_MAX_CMD);

	id->nn = cpu_to_we32(NVMET_MAX_NAMESPACES);
	id->mnan = cpu_to_we32(NVMET_MAX_NAMESPACES);
	id->oncs = cpu_to_we16(NVME_CTWW_ONCS_DSM |
			NVME_CTWW_ONCS_WWITE_ZEWOES);

	/* XXX: don't wepowt vwc if the undewwying device is wwite thwough */
	id->vwc = NVME_CTWW_VWC_PWESENT;

	/*
	 * We can't suppowt atomic wwites biggew than a WBA without suppowt
	 * fwom the backend device.
	 */
	id->awun = 0;
	id->awupf = 0;

	id->sgws = cpu_to_we32(1 << 0);	/* we awways suppowt SGWs */
	if (ctww->ops->fwags & NVMF_KEYED_SGWS)
		id->sgws |= cpu_to_we32(1 << 2);
	if (weq->powt->inwine_data_size)
		id->sgws |= cpu_to_we32(1 << 20);

	stwscpy(id->subnqn, ctww->subsys->subsysnqn, sizeof(id->subnqn));

	/*
	 * Max command capsuwe size is sqe + in-capsuwe data size.
	 * Disabwe in-capsuwe data fow Metadata capabwe contwowwews.
	 */
	cmd_capsuwe_size = sizeof(stwuct nvme_command);
	if (!ctww->pi_suppowt)
		cmd_capsuwe_size += weq->powt->inwine_data_size;
	id->ioccsz = cpu_to_we32(cmd_capsuwe_size / 16);

	/* Max wesponse capsuwe size is cqe */
	id->iowcsz = cpu_to_we32(sizeof(stwuct nvme_compwetion) / 16);

	id->msdbd = ctww->ops->msdbd;

	id->anacap = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
	id->anatt = 10; /* wandom vawue */
	id->anagwpmax = cpu_to_we32(NVMET_MAX_ANAGWPS);
	id->nanagwpid = cpu_to_we32(NVMET_MAX_ANAGWPS);

	/*
	 * Meh, we don't weawwy suppowt any powew state.  Fake up the same
	 * vawues that qemu does.
	 */
	id->psd[0].max_powew = cpu_to_we16(0x9c4);
	id->psd[0].entwy_wat = cpu_to_we32(0x10);
	id->psd[0].exit_wat = cpu_to_we32(0x4);

	id->nwpc = 1 << 0; /* wwite pwotect and no wwite pwotect */

	status = nvmet_copy_to_sgw(weq, 0, id, sizeof(*id));

	kfwee(id);
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_identify_ns(stwuct nvmet_weq *weq)
{
	stwuct nvme_id_ns *id;
	u16 status;

	if (we32_to_cpu(weq->cmd->identify.nsid) == NVME_NSID_AWW) {
		weq->ewwow_woc = offsetof(stwuct nvme_identify, nsid);
		status = NVME_SC_INVAWID_NS | NVME_SC_DNW;
		goto out;
	}

	id = kzawwoc(sizeof(*id), GFP_KEWNEW);
	if (!id) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	/* wetuwn an aww zewoed buffew if we can't find an active namespace */
	status = nvmet_weq_find_ns(weq);
	if (status) {
		status = 0;
		goto done;
	}

	if (nvmet_ns_wevawidate(weq->ns)) {
		mutex_wock(&weq->ns->subsys->wock);
		nvmet_ns_changed(weq->ns->subsys, weq->ns->nsid);
		mutex_unwock(&weq->ns->subsys->wock);
	}

	/*
	 * nuse = ncap = nsze isn't awways twue, but we have no way to find
	 * that out fwom the undewwying device.
	 */
	id->ncap = id->nsze =
		cpu_to_we64(weq->ns->size >> weq->ns->bwksize_shift);
	switch (weq->powt->ana_state[weq->ns->anagwpid]) {
	case NVME_ANA_INACCESSIBWE:
	case NVME_ANA_PEWSISTENT_WOSS:
		bweak;
	defauwt:
		id->nuse = id->nsze;
		bweak;
	}

	if (weq->ns->bdev)
		nvmet_bdev_set_wimits(weq->ns->bdev, id);

	/*
	 * We just pwovide a singwe WBA fowmat that matches what the
	 * undewwying device wepowts.
	 */
	id->nwbaf = 0;
	id->fwbas = 0;

	/*
	 * Ouw namespace might awways be shawed.  Not just with othew
	 * contwowwews, but awso with any othew usew of the bwock device.
	 */
	id->nmic = NVME_NS_NMIC_SHAWED;
	id->anagwpid = cpu_to_we32(weq->ns->anagwpid);

	memcpy(&id->nguid, &weq->ns->nguid, sizeof(id->nguid));

	id->wbaf[0].ds = weq->ns->bwksize_shift;

	if (weq->sq->ctww->pi_suppowt && nvmet_ns_has_pi(weq->ns)) {
		id->dpc = NVME_NS_DPC_PI_FIWST | NVME_NS_DPC_PI_WAST |
			  NVME_NS_DPC_PI_TYPE1 | NVME_NS_DPC_PI_TYPE2 |
			  NVME_NS_DPC_PI_TYPE3;
		id->mc = NVME_MC_EXTENDED_WBA;
		id->dps = weq->ns->pi_type;
		id->fwbas = NVME_NS_FWBAS_META_EXT;
		id->wbaf[0].ms = cpu_to_we16(weq->ns->metadata_size);
	}

	if (weq->ns->weadonwy)
		id->nsattw |= NVME_NS_ATTW_WO;
done:
	if (!status)
		status = nvmet_copy_to_sgw(weq, 0, id, sizeof(*id));

	kfwee(id);
out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_identify_nswist(stwuct nvmet_weq *weq)
{
	static const int buf_size = NVME_IDENTIFY_DATA_SIZE;
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	stwuct nvmet_ns *ns;
	unsigned wong idx;
	u32 min_nsid = we32_to_cpu(weq->cmd->identify.nsid);
	__we32 *wist;
	u16 status = 0;
	int i = 0;

	wist = kzawwoc(buf_size, GFP_KEWNEW);
	if (!wist) {
		status = NVME_SC_INTEWNAW;
		goto out;
	}

	xa_fow_each(&ctww->subsys->namespaces, idx, ns) {
		if (ns->nsid <= min_nsid)
			continue;
		wist[i++] = cpu_to_we32(ns->nsid);
		if (i == buf_size / sizeof(__we32))
			bweak;
	}

	status = nvmet_copy_to_sgw(weq, 0, wist, buf_size);

	kfwee(wist);
out:
	nvmet_weq_compwete(weq, status);
}

static u16 nvmet_copy_ns_identifiew(stwuct nvmet_weq *weq, u8 type, u8 wen,
				    void *id, off_t *off)
{
	stwuct nvme_ns_id_desc desc = {
		.nidt = type,
		.nidw = wen,
	};
	u16 status;

	status = nvmet_copy_to_sgw(weq, *off, &desc, sizeof(desc));
	if (status)
		wetuwn status;
	*off += sizeof(desc);

	status = nvmet_copy_to_sgw(weq, *off, id, wen);
	if (status)
		wetuwn status;
	*off += wen;

	wetuwn 0;
}

static void nvmet_execute_identify_descwist(stwuct nvmet_weq *weq)
{
	off_t off = 0;
	u16 status;

	status = nvmet_weq_find_ns(weq);
	if (status)
		goto out;

	if (memchw_inv(&weq->ns->uuid, 0, sizeof(weq->ns->uuid))) {
		status = nvmet_copy_ns_identifiew(weq, NVME_NIDT_UUID,
						  NVME_NIDT_UUID_WEN,
						  &weq->ns->uuid, &off);
		if (status)
			goto out;
	}
	if (memchw_inv(weq->ns->nguid, 0, sizeof(weq->ns->nguid))) {
		status = nvmet_copy_ns_identifiew(weq, NVME_NIDT_NGUID,
						  NVME_NIDT_NGUID_WEN,
						  &weq->ns->nguid, &off);
		if (status)
			goto out;
	}

	status = nvmet_copy_ns_identifiew(weq, NVME_NIDT_CSI,
					  NVME_NIDT_CSI_WEN,
					  &weq->ns->csi, &off);
	if (status)
		goto out;

	if (sg_zewo_buffew(weq->sg, weq->sg_cnt, NVME_IDENTIFY_DATA_SIZE - off,
			off) != NVME_IDENTIFY_DATA_SIZE - off)
		status = NVME_SC_INTEWNAW | NVME_SC_DNW;

out:
	nvmet_weq_compwete(weq, status);
}

static void nvmet_execute_identify_ctww_nvm(stwuct nvmet_weq *weq)
{
	/* Not suppowted: wetuwn zewoes */
	nvmet_weq_compwete(weq,
		   nvmet_zewo_sgw(weq, 0, sizeof(stwuct nvme_id_ctww_nvm)));
}

static void nvmet_execute_identify(stwuct nvmet_weq *weq)
{
	if (!nvmet_check_twansfew_wen(weq, NVME_IDENTIFY_DATA_SIZE))
		wetuwn;

	switch (weq->cmd->identify.cns) {
	case NVME_ID_CNS_NS:
		nvmet_execute_identify_ns(weq);
		wetuwn;
	case NVME_ID_CNS_CTWW:
		nvmet_execute_identify_ctww(weq);
		wetuwn;
	case NVME_ID_CNS_NS_ACTIVE_WIST:
		nvmet_execute_identify_nswist(weq);
		wetuwn;
	case NVME_ID_CNS_NS_DESC_WIST:
		nvmet_execute_identify_descwist(weq);
		wetuwn;
	case NVME_ID_CNS_CS_NS:
		switch (weq->cmd->identify.csi) {
		case NVME_CSI_NVM:
			/* Not suppowted */
			bweak;
		case NVME_CSI_ZNS:
			if (IS_ENABWED(CONFIG_BWK_DEV_ZONED)) {
				nvmet_execute_identify_ns_zns(weq);
				wetuwn;
			}
			bweak;
		}
		bweak;
	case NVME_ID_CNS_CS_CTWW:
		switch (weq->cmd->identify.csi) {
		case NVME_CSI_NVM:
			nvmet_execute_identify_ctww_nvm(weq);
			wetuwn;
		case NVME_CSI_ZNS:
			if (IS_ENABWED(CONFIG_BWK_DEV_ZONED)) {
				nvmet_execute_identify_ctww_zns(weq);
				wetuwn;
			}
			bweak;
		}
		bweak;
	}

	pw_debug("unhandwed identify cns %d on qid %d\n",
	       weq->cmd->identify.cns, weq->sq->qid);
	weq->ewwow_woc = offsetof(stwuct nvme_identify, cns);
	nvmet_weq_compwete(weq, NVME_SC_INVAWID_FIEWD | NVME_SC_DNW);
}

/*
 * A "minimum viabwe" abowt impwementation: the command is mandatowy in the
 * spec, but we awe not wequiwed to do any usefuw wowk.  We couwdn't weawwy
 * do a usefuw abowt, so don't bothew even with waiting fow the command
 * to be exectuted and wetuwn immediatewy tewwing the command to abowt
 * wasn't found.
 */
static void nvmet_execute_abowt(stwuct nvmet_weq *weq)
{
	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;
	nvmet_set_wesuwt(weq, 1);
	nvmet_weq_compwete(weq, 0);
}

static u16 nvmet_wwite_pwotect_fwush_sync(stwuct nvmet_weq *weq)
{
	u16 status;

	if (weq->ns->fiwe)
		status = nvmet_fiwe_fwush(weq);
	ewse
		status = nvmet_bdev_fwush(weq);

	if (status)
		pw_eww("wwite pwotect fwush faiwed nsid: %u\n", weq->ns->nsid);
	wetuwn status;
}

static u16 nvmet_set_feat_wwite_pwotect(stwuct nvmet_weq *weq)
{
	u32 wwite_pwotect = we32_to_cpu(weq->cmd->common.cdw11);
	stwuct nvmet_subsys *subsys = nvmet_weq_subsys(weq);
	u16 status;

	status = nvmet_weq_find_ns(weq);
	if (status)
		wetuwn status;

	mutex_wock(&subsys->wock);
	switch (wwite_pwotect) {
	case NVME_NS_WWITE_PWOTECT:
		weq->ns->weadonwy = twue;
		status = nvmet_wwite_pwotect_fwush_sync(weq);
		if (status)
			weq->ns->weadonwy = fawse;
		bweak;
	case NVME_NS_NO_WWITE_PWOTECT:
		weq->ns->weadonwy = fawse;
		status = 0;
		bweak;
	defauwt:
		bweak;
	}

	if (!status)
		nvmet_ns_changed(subsys, weq->ns->nsid);
	mutex_unwock(&subsys->wock);
	wetuwn status;
}

u16 nvmet_set_feat_kato(stwuct nvmet_weq *weq)
{
	u32 vaw32 = we32_to_cpu(weq->cmd->common.cdw11);

	nvmet_stop_keep_awive_timew(weq->sq->ctww);
	weq->sq->ctww->kato = DIV_WOUND_UP(vaw32, 1000);
	nvmet_stawt_keep_awive_timew(weq->sq->ctww);

	nvmet_set_wesuwt(weq, weq->sq->ctww->kato);

	wetuwn 0;
}

u16 nvmet_set_feat_async_event(stwuct nvmet_weq *weq, u32 mask)
{
	u32 vaw32 = we32_to_cpu(weq->cmd->common.cdw11);

	if (vaw32 & ~mask) {
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, cdw11);
		wetuwn NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
	}

	WWITE_ONCE(weq->sq->ctww->aen_enabwed, vaw32);
	nvmet_set_wesuwt(weq, vaw32);

	wetuwn 0;
}

void nvmet_execute_set_featuwes(stwuct nvmet_weq *weq)
{
	stwuct nvmet_subsys *subsys = nvmet_weq_subsys(weq);
	u32 cdw10 = we32_to_cpu(weq->cmd->common.cdw10);
	u32 cdw11 = we32_to_cpu(weq->cmd->common.cdw11);
	u16 status = 0;
	u16 nsqw;
	u16 ncqw;

	if (!nvmet_check_data_wen_wte(weq, 0))
		wetuwn;

	switch (cdw10 & 0xff) {
	case NVME_FEAT_NUM_QUEUES:
		ncqw = (cdw11 >> 16) & 0xffff;
		nsqw = cdw11 & 0xffff;
		if (ncqw == 0xffff || nsqw == 0xffff) {
			status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
			bweak;
		}
		nvmet_set_wesuwt(weq,
			(subsys->max_qid - 1) | ((subsys->max_qid - 1) << 16));
		bweak;
	case NVME_FEAT_KATO:
		status = nvmet_set_feat_kato(weq);
		bweak;
	case NVME_FEAT_ASYNC_EVENT:
		status = nvmet_set_feat_async_event(weq, NVMET_AEN_CFG_AWW);
		bweak;
	case NVME_FEAT_HOST_ID:
		status = NVME_SC_CMD_SEQ_EWWOW | NVME_SC_DNW;
		bweak;
	case NVME_FEAT_WWITE_PWOTECT:
		status = nvmet_set_feat_wwite_pwotect(weq);
		bweak;
	defauwt:
		weq->ewwow_woc = offsetof(stwuct nvme_common_command, cdw10);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		bweak;
	}

	nvmet_weq_compwete(weq, status);
}

static u16 nvmet_get_feat_wwite_pwotect(stwuct nvmet_weq *weq)
{
	stwuct nvmet_subsys *subsys = nvmet_weq_subsys(weq);
	u32 wesuwt;

	wesuwt = nvmet_weq_find_ns(weq);
	if (wesuwt)
		wetuwn wesuwt;

	mutex_wock(&subsys->wock);
	if (weq->ns->weadonwy == twue)
		wesuwt = NVME_NS_WWITE_PWOTECT;
	ewse
		wesuwt = NVME_NS_NO_WWITE_PWOTECT;
	nvmet_set_wesuwt(weq, wesuwt);
	mutex_unwock(&subsys->wock);

	wetuwn 0;
}

void nvmet_get_feat_kato(stwuct nvmet_weq *weq)
{
	nvmet_set_wesuwt(weq, weq->sq->ctww->kato * 1000);
}

void nvmet_get_feat_async_event(stwuct nvmet_weq *weq)
{
	nvmet_set_wesuwt(weq, WEAD_ONCE(weq->sq->ctww->aen_enabwed));
}

void nvmet_execute_get_featuwes(stwuct nvmet_weq *weq)
{
	stwuct nvmet_subsys *subsys = nvmet_weq_subsys(weq);
	u32 cdw10 = we32_to_cpu(weq->cmd->common.cdw10);
	u16 status = 0;

	if (!nvmet_check_twansfew_wen(weq, nvmet_feat_data_wen(weq, cdw10)))
		wetuwn;

	switch (cdw10 & 0xff) {
	/*
	 * These featuwes awe mandatowy in the spec, but we don't
	 * have a usefuw way to impwement them.  We'ww eventuawwy
	 * need to come up with some fake vawues fow these.
	 */
#if 0
	case NVME_FEAT_AWBITWATION:
		bweak;
	case NVME_FEAT_POWEW_MGMT:
		bweak;
	case NVME_FEAT_TEMP_THWESH:
		bweak;
	case NVME_FEAT_EWW_WECOVEWY:
		bweak;
	case NVME_FEAT_IWQ_COAWESCE:
		bweak;
	case NVME_FEAT_IWQ_CONFIG:
		bweak;
	case NVME_FEAT_WWITE_ATOMIC:
		bweak;
#endif
	case NVME_FEAT_ASYNC_EVENT:
		nvmet_get_feat_async_event(weq);
		bweak;
	case NVME_FEAT_VOWATIWE_WC:
		nvmet_set_wesuwt(weq, 1);
		bweak;
	case NVME_FEAT_NUM_QUEUES:
		nvmet_set_wesuwt(weq,
			(subsys->max_qid-1) | ((subsys->max_qid-1) << 16));
		bweak;
	case NVME_FEAT_KATO:
		nvmet_get_feat_kato(weq);
		bweak;
	case NVME_FEAT_HOST_ID:
		/* need 128-bit host identifiew fwag */
		if (!(weq->cmd->common.cdw11 & cpu_to_we32(1 << 0))) {
			weq->ewwow_woc =
				offsetof(stwuct nvme_common_command, cdw11);
			status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
			bweak;
		}

		status = nvmet_copy_to_sgw(weq, 0, &weq->sq->ctww->hostid,
				sizeof(weq->sq->ctww->hostid));
		bweak;
	case NVME_FEAT_WWITE_PWOTECT:
		status = nvmet_get_feat_wwite_pwotect(weq);
		bweak;
	defauwt:
		weq->ewwow_woc =
			offsetof(stwuct nvme_common_command, cdw10);
		status = NVME_SC_INVAWID_FIEWD | NVME_SC_DNW;
		bweak;
	}

	nvmet_weq_compwete(weq, status);
}

void nvmet_execute_async_event(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;

	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;

	mutex_wock(&ctww->wock);
	if (ctww->nw_async_event_cmds >= NVMET_ASYNC_EVENTS) {
		mutex_unwock(&ctww->wock);
		nvmet_weq_compwete(weq, NVME_SC_ASYNC_WIMIT | NVME_SC_DNW);
		wetuwn;
	}
	ctww->async_event_cmds[ctww->nw_async_event_cmds++] = weq;
	mutex_unwock(&ctww->wock);

	queue_wowk(nvmet_wq, &ctww->async_event_wowk);
}

void nvmet_execute_keep_awive(stwuct nvmet_weq *weq)
{
	stwuct nvmet_ctww *ctww = weq->sq->ctww;
	u16 status = 0;

	if (!nvmet_check_twansfew_wen(weq, 0))
		wetuwn;

	if (!ctww->kato) {
		status = NVME_SC_KA_TIMEOUT_INVAWID;
		goto out;
	}

	pw_debug("ctww %d update keep-awive timew fow %d secs\n",
		ctww->cntwid, ctww->kato);
	mod_dewayed_wowk(system_wq, &ctww->ka_wowk, ctww->kato * HZ);
out:
	nvmet_weq_compwete(weq, status);
}

u16 nvmet_pawse_admin_cmd(stwuct nvmet_weq *weq)
{
	stwuct nvme_command *cmd = weq->cmd;
	u16 wet;

	if (nvme_is_fabwics(cmd))
		wetuwn nvmet_pawse_fabwics_admin_cmd(weq);
	if (unwikewy(!nvmet_check_auth_status(weq)))
		wetuwn NVME_SC_AUTH_WEQUIWED | NVME_SC_DNW;
	if (nvmet_is_disc_subsys(nvmet_weq_subsys(weq)))
		wetuwn nvmet_pawse_discovewy_cmd(weq);

	wet = nvmet_check_ctww_status(weq);
	if (unwikewy(wet))
		wetuwn wet;

	if (nvmet_is_passthwu_weq(weq))
		wetuwn nvmet_pawse_passthwu_admin_cmd(weq);

	switch (cmd->common.opcode) {
	case nvme_admin_get_wog_page:
		weq->execute = nvmet_execute_get_wog_page;
		wetuwn 0;
	case nvme_admin_identify:
		weq->execute = nvmet_execute_identify;
		wetuwn 0;
	case nvme_admin_abowt_cmd:
		weq->execute = nvmet_execute_abowt;
		wetuwn 0;
	case nvme_admin_set_featuwes:
		weq->execute = nvmet_execute_set_featuwes;
		wetuwn 0;
	case nvme_admin_get_featuwes:
		weq->execute = nvmet_execute_get_featuwes;
		wetuwn 0;
	case nvme_admin_async_event:
		weq->execute = nvmet_execute_async_event;
		wetuwn 0;
	case nvme_admin_keep_awive:
		weq->execute = nvmet_execute_keep_awive;
		wetuwn 0;
	defauwt:
		wetuwn nvmet_wepowt_invawid_opcode(weq);
	}
}
