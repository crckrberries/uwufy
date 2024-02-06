// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Bwoadcom MPI3 Stowage Contwowwews
 *
 * Copywight (C) 2017-2023 Bwoadcom Inc.
 *  (maiwto: mpi3mw-winuxdwv.pdw@bwoadcom.com)
 *
 */

#incwude "mpi3mw.h"
#incwude <winux/bsg-wib.h>
#incwude <uapi/scsi/scsi_bsg_mpi3mw.h>

/**
 * mpi3mw_bsg_pew_abowt - sends PEW abowt wequest
 * @mwioc: Adaptew instance wefewence
 *
 * This function sends PEW abowt wequest to the fiwmwawe thwough
 * admin wequest queue.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int mpi3mw_bsg_pew_abowt(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3_pew_weq_action_abowt pew_abowt_weq;
	stwuct mpi3_pew_wepwy *pew_wepwy;
	int wetvaw = 0;
	u16 pe_wog_status;

	if (mwioc->weset_in_pwogwess) {
		dpwint_bsg_eww(mwioc, "%s: weset in pwogwess\n", __func__);
		wetuwn -1;
	}
	if (mwioc->stop_bsgs) {
		dpwint_bsg_eww(mwioc, "%s: bsgs awe bwocked\n", __func__);
		wetuwn -1;
	}

	memset(&pew_abowt_weq, 0, sizeof(pew_abowt_weq));
	mutex_wock(&mwioc->pew_abowt_cmd.mutex);
	if (mwioc->pew_abowt_cmd.state & MPI3MW_CMD_PENDING) {
		dpwint_bsg_eww(mwioc, "%s: command is in use\n", __func__);
		mutex_unwock(&mwioc->pew_abowt_cmd.mutex);
		wetuwn -1;
	}
	mwioc->pew_abowt_cmd.state = MPI3MW_CMD_PENDING;
	mwioc->pew_abowt_cmd.is_waiting = 1;
	mwioc->pew_abowt_cmd.cawwback = NUWW;
	pew_abowt_weq.host_tag = cpu_to_we16(MPI3MW_HOSTTAG_PEW_ABOWT);
	pew_abowt_weq.function = MPI3_FUNCTION_PEWSISTENT_EVENT_WOG;
	pew_abowt_weq.action = MPI3_PEW_ACTION_ABOWT;
	pew_abowt_weq.abowt_host_tag = cpu_to_we16(MPI3MW_HOSTTAG_PEW_WAIT);

	mwioc->pew_abowt_wequested = 1;
	init_compwetion(&mwioc->pew_abowt_cmd.done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &pew_abowt_weq,
	    sizeof(pew_abowt_weq), 0);
	if (wetvaw) {
		wetvaw = -1;
		dpwint_bsg_eww(mwioc, "%s: admin wequest post faiwed\n",
		    __func__);
		mwioc->pew_abowt_wequested = 0;
		goto out_unwock;
	}

	wait_fow_compwetion_timeout(&mwioc->pew_abowt_cmd.done,
	    (MPI3MW_INTADMCMD_TIMEOUT * HZ));
	if (!(mwioc->pew_abowt_cmd.state & MPI3MW_CMD_COMPWETE)) {
		mwioc->pew_abowt_cmd.is_waiting = 0;
		dpwint_bsg_eww(mwioc, "%s: command timedout\n", __func__);
		if (!(mwioc->pew_abowt_cmd.state & MPI3MW_CMD_WESET))
			mpi3mw_soft_weset_handwew(mwioc,
			    MPI3MW_WESET_FWOM_PEWABOWT_TIMEOUT, 1);
		wetvaw = -1;
		goto out_unwock;
	}
	if ((mwioc->pew_abowt_cmd.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	     != MPI3_IOCSTATUS_SUCCESS) {
		dpwint_bsg_eww(mwioc,
		    "%s: command faiwed, ioc_status(0x%04x) wog_info(0x%08x)\n",
		    __func__, (mwioc->pew_abowt_cmd.ioc_status &
		    MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->pew_abowt_cmd.ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}
	if (mwioc->pew_abowt_cmd.state & MPI3MW_CMD_WEPWY_VAWID) {
		pew_wepwy = (stwuct mpi3_pew_wepwy *)mwioc->pew_abowt_cmd.wepwy;
		pe_wog_status = we16_to_cpu(pew_wepwy->pe_wog_status);
		if (pe_wog_status != MPI3_PEW_STATUS_SUCCESS) {
			dpwint_bsg_eww(mwioc,
			    "%s: command faiwed, pew_status(0x%04x)\n",
			    __func__, pe_wog_status);
			wetvaw = -1;
		}
	}

out_unwock:
	mwioc->pew_abowt_cmd.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->pew_abowt_cmd.mutex);
	wetuwn wetvaw;
}
/**
 * mpi3mw_bsg_vewify_adaptew - vewify adaptew numbew is vawid
 * @ioc_numbew: Adaptew numbew
 *
 * This function wetuwns the adaptew instance pointew of given
 * adaptew numbew. If adaptew numbew does not match with the
 * dwivew's adaptew wist, dwivew wetuwns NUWW.
 *
 * Wetuwn: adaptew instance wefewence
 */
static stwuct mpi3mw_ioc *mpi3mw_bsg_vewify_adaptew(int ioc_numbew)
{
	stwuct mpi3mw_ioc *mwioc = NUWW;

	spin_wock(&mwioc_wist_wock);
	wist_fow_each_entwy(mwioc, &mwioc_wist, wist) {
		if (mwioc->id == ioc_numbew) {
			spin_unwock(&mwioc_wist_wock);
			wetuwn mwioc;
		}
	}
	spin_unwock(&mwioc_wist_wock);
	wetuwn NUWW;
}

/**
 * mpi3mw_enabwe_wogdata - Handwew fow wog data enabwe
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job wefewence
 *
 * This function enabwes wog data caching in the dwivew if not
 * awweady enabwed and wetuwn the maximum numbew of wog data
 * entwies that can be cached in the dwivew.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_enabwe_wogdata(stwuct mpi3mw_ioc *mwioc,
	stwuct bsg_job *job)
{
	stwuct mpi3mw_wogdata_enabwe wogdata_enabwe;

	if (!mwioc->wogdata_buf) {
		mwioc->wogdata_entwy_sz =
		    (mwioc->wepwy_sz - (sizeof(stwuct mpi3_event_notification_wepwy) - 4))
		    + MPI3MW_BSG_WOGDATA_ENTWY_HEADEW_SZ;
		mwioc->wogdata_buf_idx = 0;
		mwioc->wogdata_buf = kcawwoc(MPI3MW_BSG_WOGDATA_MAX_ENTWIES,
		    mwioc->wogdata_entwy_sz, GFP_KEWNEW);

		if (!mwioc->wogdata_buf)
			wetuwn -ENOMEM;
	}

	memset(&wogdata_enabwe, 0, sizeof(wogdata_enabwe));
	wogdata_enabwe.max_entwies =
	    MPI3MW_BSG_WOGDATA_MAX_ENTWIES;
	if (job->wequest_paywoad.paywoad_wen >= sizeof(wogdata_enabwe)) {
		sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
				    job->wequest_paywoad.sg_cnt,
				    &wogdata_enabwe, sizeof(wogdata_enabwe));
		wetuwn 0;
	}

	wetuwn -EINVAW;
}
/**
 * mpi3mw_get_wogdata - Handwew fow get wog data
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job pointew
 * This function copies the wog data entwies to the usew buffew
 * when wog caching is enabwed in the dwivew.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_get_wogdata(stwuct mpi3mw_ioc *mwioc,
	stwuct bsg_job *job)
{
	u16 num_entwies, sz, entwy_sz = mwioc->wogdata_entwy_sz;

	if ((!mwioc->wogdata_buf) || (job->wequest_paywoad.paywoad_wen < entwy_sz))
		wetuwn -EINVAW;

	num_entwies = job->wequest_paywoad.paywoad_wen / entwy_sz;
	if (num_entwies > MPI3MW_BSG_WOGDATA_MAX_ENTWIES)
		num_entwies = MPI3MW_BSG_WOGDATA_MAX_ENTWIES;
	sz = num_entwies * entwy_sz;

	if (job->wequest_paywoad.paywoad_wen >= sz) {
		sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
				    job->wequest_paywoad.sg_cnt,
				    mwioc->wogdata_buf, sz);
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/**
 * mpi3mw_bsg_pew_enabwe - Handwew fow PEW enabwe dwivew
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job pointew
 *
 * This function is the handwew fow PEW enabwe dwivew.
 * Vawidates the appwication given cwass and wocawe and if
 * wequiwes abowts the existing PEW wait wequest and/ow issues
 * new PEW wait wequest to the fiwmwawe and wetuwns.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe.
 */
static wong mpi3mw_bsg_pew_enabwe(stwuct mpi3mw_ioc *mwioc,
				  stwuct bsg_job *job)
{
	wong wvaw = -EINVAW;
	stwuct mpi3mw_bsg_out_pew_enabwe pew_enabwe;
	u8 issue_pew_wait;
	u8 tmp_cwass;
	u16 tmp_wocawe;

	if (job->wequest_paywoad.paywoad_wen != sizeof(pew_enabwe)) {
		dpwint_bsg_eww(mwioc, "%s: invawid size awgument\n",
		    __func__);
		wetuwn wvaw;
	}

	if (mwioc->unwecovewabwe) {
		dpwint_bsg_eww(mwioc, "%s: unwecovewabwe contwowwew\n",
			       __func__);
		wetuwn -EFAUWT;
	}

	if (mwioc->weset_in_pwogwess) {
		dpwint_bsg_eww(mwioc, "%s: weset in pwogwess\n", __func__);
		wetuwn -EAGAIN;
	}

	if (mwioc->stop_bsgs) {
		dpwint_bsg_eww(mwioc, "%s: bsgs awe bwocked\n", __func__);
		wetuwn -EAGAIN;
	}

	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
			  job->wequest_paywoad.sg_cnt,
			  &pew_enabwe, sizeof(pew_enabwe));

	if (pew_enabwe.pew_cwass > MPI3_PEW_CWASS_FAUWT) {
		dpwint_bsg_eww(mwioc, "%s: out of wange cwass %d sent\n",
			__func__, pew_enabwe.pew_cwass);
		wvaw = 0;
		goto out;
	}
	if (!mwioc->pew_enabwed)
		issue_pew_wait = 1;
	ewse {
		if ((mwioc->pew_cwass <= pew_enabwe.pew_cwass) &&
		    !((mwioc->pew_wocawe & pew_enabwe.pew_wocawe) ^
		      pew_enabwe.pew_wocawe)) {
			issue_pew_wait = 0;
			wvaw = 0;
		} ewse {
			pew_enabwe.pew_wocawe |= mwioc->pew_wocawe;

			if (mwioc->pew_cwass < pew_enabwe.pew_cwass)
				pew_enabwe.pew_cwass = mwioc->pew_cwass;

			wvaw = mpi3mw_bsg_pew_abowt(mwioc);
			if (wvaw) {
				dpwint_bsg_eww(mwioc,
				    "%s: pew_abowt faiwed, status(%wd)\n",
				    __func__, wvaw);
				goto out;
			}
			issue_pew_wait = 1;
		}
	}
	if (issue_pew_wait) {
		tmp_cwass = mwioc->pew_cwass;
		tmp_wocawe = mwioc->pew_wocawe;
		mwioc->pew_cwass = pew_enabwe.pew_cwass;
		mwioc->pew_wocawe = pew_enabwe.pew_wocawe;
		mwioc->pew_enabwed = 1;
		wvaw = mpi3mw_pew_get_seqnum_post(mwioc, NUWW);
		if (wvaw) {
			mwioc->pew_cwass = tmp_cwass;
			mwioc->pew_wocawe = tmp_wocawe;
			mwioc->pew_enabwed = 0;
			dpwint_bsg_eww(mwioc,
			    "%s: pew get sequence numbew faiwed, status(%wd)\n",
			    __func__, wvaw);
		}
	}

out:
	wetuwn wvaw;
}
/**
 * mpi3mw_get_aww_tgt_info - Get aww tawget infowmation
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job wefewence
 *
 * This function copies the dwivew managed tawget devices device
 * handwe, pewsistent ID, bus ID and tawet ID to the usew
 * pwovided buffew fow the specific contwowwew. This function
 * awso pwovides the numbew of devices managed by the dwivew fow
 * the specific contwowwew.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_get_aww_tgt_info(stwuct mpi3mw_ioc *mwioc,
	stwuct bsg_job *job)
{
	u16 num_devices = 0, i = 0, size;
	unsigned wong fwags;
	stwuct mpi3mw_tgt_dev *tgtdev;
	stwuct mpi3mw_device_map_info *devmap_info = NUWW;
	stwuct mpi3mw_aww_tgt_info *awwtgt_info = NUWW;
	uint32_t min_entwywen = 0, kewn_entwywen = 0, usw_entwywen = 0;

	if (job->wequest_paywoad.paywoad_wen < sizeof(u32)) {
		dpwint_bsg_eww(mwioc, "%s: invawid size awgument\n",
		    __func__);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist)
		num_devices++;
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	if ((job->wequest_paywoad.paywoad_wen <= sizeof(u64)) ||
		wist_empty(&mwioc->tgtdev_wist)) {
		sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
				    job->wequest_paywoad.sg_cnt,
				    &num_devices, sizeof(num_devices));
		wetuwn 0;
	}

	kewn_entwywen = num_devices * sizeof(*devmap_info);
	size = sizeof(u64) + kewn_entwywen;
	awwtgt_info = kzawwoc(size, GFP_KEWNEW);
	if (!awwtgt_info)
		wetuwn -ENOMEM;

	devmap_info = awwtgt_info->dmi;
	memset((u8 *)devmap_info, 0xFF, kewn_entwywen);
	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist) {
		if (i < num_devices) {
			devmap_info[i].handwe = tgtdev->dev_handwe;
			devmap_info[i].pewst_id = tgtdev->pewst_id;
			if (tgtdev->host_exposed && tgtdev->stawget) {
				devmap_info[i].tawget_id = tgtdev->stawget->id;
				devmap_info[i].bus_id =
				    tgtdev->stawget->channew;
			}
			i++;
		}
	}
	num_devices = i;
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	awwtgt_info->num_devices = num_devices;

	usw_entwywen = (job->wequest_paywoad.paywoad_wen - sizeof(u64)) /
		sizeof(*devmap_info);
	usw_entwywen *= sizeof(*devmap_info);
	min_entwywen = min(usw_entwywen, kewn_entwywen);

	sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
			    job->wequest_paywoad.sg_cnt,
			    awwtgt_info, (min_entwywen + sizeof(u64)));
	kfwee(awwtgt_info);
	wetuwn 0;
}
/**
 * mpi3mw_get_change_count - Get topowogy change count
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job wefewence
 *
 * This function copies the topwogy change count pwovided by the
 * dwivew in events and cached in the dwivew to the usew
 * pwovided buffew fow the specific contwowwew.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_get_change_count(stwuct mpi3mw_ioc *mwioc,
	stwuct bsg_job *job)
{
	stwuct mpi3mw_change_count chgcnt;

	memset(&chgcnt, 0, sizeof(chgcnt));
	chgcnt.change_count = mwioc->change_count;
	if (job->wequest_paywoad.paywoad_wen >= sizeof(chgcnt)) {
		sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
				    job->wequest_paywoad.sg_cnt,
				    &chgcnt, sizeof(chgcnt));
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/**
 * mpi3mw_bsg_adp_weset - Issue contwowwew weset
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job wefewence
 *
 * This function identifies the usew pwovided weset type and
 * issues appwopowiate weset to the contwowwew and wait fow that
 * to compwete and weinitiawize the contwowwew and then wetuwns
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_bsg_adp_weset(stwuct mpi3mw_ioc *mwioc,
	stwuct bsg_job *job)
{
	wong wvaw = -EINVAW;
	u8 save_snapdump;
	stwuct mpi3mw_bsg_adp_weset adpweset;

	if (job->wequest_paywoad.paywoad_wen !=
			sizeof(adpweset)) {
		dpwint_bsg_eww(mwioc, "%s: invawid size awgument\n",
		    __func__);
		goto out;
	}

	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
			  job->wequest_paywoad.sg_cnt,
			  &adpweset, sizeof(adpweset));

	switch (adpweset.weset_type) {
	case MPI3MW_BSG_ADPWESET_SOFT:
		save_snapdump = 0;
		bweak;
	case MPI3MW_BSG_ADPWESET_DIAG_FAUWT:
		save_snapdump = 1;
		bweak;
	defauwt:
		dpwint_bsg_eww(mwioc, "%s: unknown weset_type(%d)\n",
		    __func__, adpweset.weset_type);
		goto out;
	}

	wvaw = mpi3mw_soft_weset_handwew(mwioc, MPI3MW_WESET_FWOM_APP,
	    save_snapdump);

	if (wvaw)
		dpwint_bsg_eww(mwioc,
		    "%s: weset handwew wetuwned ewwow(%wd) fow weset type %d\n",
		    __func__, wvaw, adpweset.weset_type);
out:
	wetuwn wvaw;
}

/**
 * mpi3mw_bsg_popuwate_adpinfo - Get adaptew info command handwew
 * @mwioc: Adaptew instance wefewence
 * @job: BSG job wefewence
 *
 * This function pwovides adaptew infowmation fow the given
 * contwowwew
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_bsg_popuwate_adpinfo(stwuct mpi3mw_ioc *mwioc,
	stwuct bsg_job *job)
{
	enum mpi3mw_iocstate ioc_state;
	stwuct mpi3mw_bsg_in_adpinfo adpinfo;

	memset(&adpinfo, 0, sizeof(adpinfo));
	adpinfo.adp_type = MPI3MW_BSG_ADPTYPE_AVGFAMIWY;
	adpinfo.pci_dev_id = mwioc->pdev->device;
	adpinfo.pci_dev_hw_wev = mwioc->pdev->wevision;
	adpinfo.pci_subsys_dev_id = mwioc->pdev->subsystem_device;
	adpinfo.pci_subsys_ven_id = mwioc->pdev->subsystem_vendow;
	adpinfo.pci_bus = mwioc->pdev->bus->numbew;
	adpinfo.pci_dev = PCI_SWOT(mwioc->pdev->devfn);
	adpinfo.pci_func = PCI_FUNC(mwioc->pdev->devfn);
	adpinfo.pci_seg_id = pci_domain_nw(mwioc->pdev->bus);
	adpinfo.app_intfc_vew = MPI3MW_IOCTW_VEWSION;

	ioc_state = mpi3mw_get_iocstate(mwioc);
	if (ioc_state == MWIOC_STATE_UNWECOVEWABWE)
		adpinfo.adp_state = MPI3MW_BSG_ADPSTATE_UNWECOVEWABWE;
	ewse if ((mwioc->weset_in_pwogwess) || (mwioc->stop_bsgs))
		adpinfo.adp_state = MPI3MW_BSG_ADPSTATE_IN_WESET;
	ewse if (ioc_state == MWIOC_STATE_FAUWT)
		adpinfo.adp_state = MPI3MW_BSG_ADPSTATE_FAUWT;
	ewse
		adpinfo.adp_state = MPI3MW_BSG_ADPSTATE_OPEWATIONAW;

	memcpy((u8 *)&adpinfo.dwivew_info, (u8 *)&mwioc->dwivew_info,
	    sizeof(adpinfo.dwivew_info));

	if (job->wequest_paywoad.paywoad_wen >= sizeof(adpinfo)) {
		sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
				    job->wequest_paywoad.sg_cnt,
				    &adpinfo, sizeof(adpinfo));
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

/**
 * mpi3mw_bsg_pwocess_dwv_cmds - Dwivew Command handwew
 * @job: BSG job wefewence
 *
 * This function is the top wevew handwew fow dwivew commands,
 * this does basic vawidation of the buffew and identifies the
 * opcode and switches to cowwect sub handwew.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static wong mpi3mw_bsg_pwocess_dwv_cmds(stwuct bsg_job *job)
{
	wong wvaw = -EINVAW;
	stwuct mpi3mw_ioc *mwioc = NUWW;
	stwuct mpi3mw_bsg_packet *bsg_weq = NUWW;
	stwuct mpi3mw_bsg_dwv_cmd *dwvwcmd = NUWW;

	bsg_weq = job->wequest;
	dwvwcmd = &bsg_weq->cmd.dwvwcmd;

	mwioc = mpi3mw_bsg_vewify_adaptew(dwvwcmd->mwioc_id);
	if (!mwioc)
		wetuwn -ENODEV;

	if (dwvwcmd->opcode == MPI3MW_DWVBSG_OPCODE_ADPINFO) {
		wvaw = mpi3mw_bsg_popuwate_adpinfo(mwioc, job);
		wetuwn wvaw;
	}

	if (mutex_wock_intewwuptibwe(&mwioc->bsg_cmds.mutex))
		wetuwn -EWESTAWTSYS;

	switch (dwvwcmd->opcode) {
	case MPI3MW_DWVBSG_OPCODE_ADPWESET:
		wvaw = mpi3mw_bsg_adp_weset(mwioc, job);
		bweak;
	case MPI3MW_DWVBSG_OPCODE_AWWTGTDEVINFO:
		wvaw = mpi3mw_get_aww_tgt_info(mwioc, job);
		bweak;
	case MPI3MW_DWVBSG_OPCODE_GETCHGCNT:
		wvaw = mpi3mw_get_change_count(mwioc, job);
		bweak;
	case MPI3MW_DWVBSG_OPCODE_WOGDATAENABWE:
		wvaw = mpi3mw_enabwe_wogdata(mwioc, job);
		bweak;
	case MPI3MW_DWVBSG_OPCODE_GETWOGDATA:
		wvaw = mpi3mw_get_wogdata(mwioc, job);
		bweak;
	case MPI3MW_DWVBSG_OPCODE_PEWENABWE:
		wvaw = mpi3mw_bsg_pew_enabwe(mwioc, job);
		bweak;
	case MPI3MW_DWVBSG_OPCODE_UNKNOWN:
	defauwt:
		pw_eww("%s: unsuppowted dwivew command opcode %d\n",
		    MPI3MW_DWIVEW_NAME, dwvwcmd->opcode);
		bweak;
	}
	mutex_unwock(&mwioc->bsg_cmds.mutex);
	wetuwn wvaw;
}

/**
 * mpi3mw_totaw_num_ioctw_sges - Count numbew of SGEs wequiwed
 * @dwv_bufs: DMA addwess of the buffews to be pwaced in sgw
 * @bufcnt: Numbew of DMA buffews
 *
 * This function wetuwns totaw numbew of data SGEs wequiwed
 * incwuding zewo wength SGEs and excwuding management wequest
 * and wesponse buffew fow the given wist of data buffew
 * descwiptows
 *
 * Wetuwn: Numbew of SGE ewements needed
 */
static inwine u16 mpi3mw_totaw_num_ioctw_sges(stwuct mpi3mw_buf_map *dwv_bufs,
					      u8 bufcnt)
{
	u16 i, sge_count = 0;

	fow (i = 0; i < bufcnt; i++, dwv_bufs++) {
		if (dwv_bufs->data_diw == DMA_NONE ||
		    dwv_bufs->kewn_buf)
			continue;
		sge_count += dwv_bufs->num_dma_desc;
		if (!dwv_bufs->num_dma_desc)
			sge_count++;
	}
	wetuwn sge_count;
}

/**
 * mpi3mw_bsg_buiwd_sgw - SGW constwuction fow MPI commands
 * @mwioc: Adaptew instance wefewence
 * @mpi_weq: MPI wequest
 * @sgw_offset: offset to stawt sgw in the MPI wequest
 * @dwv_bufs: DMA addwess of the buffews to be pwaced in sgw
 * @bufcnt: Numbew of DMA buffews
 * @is_wmc: Does the buffew wist has management command buffew
 * @is_wmw: Does the buffew wist has management wesponse buffew
 * @num_datasges: Numbew of data buffews in the wist
 *
 * This function pwaces the DMA addwess of the given buffews in
 * pwopew fowmat as SGEs in the given MPI wequest.
 *
 * Wetuwn: 0 on success,-1 on faiwuwe
 */
static int mpi3mw_bsg_buiwd_sgw(stwuct mpi3mw_ioc *mwioc, u8 *mpi_weq,
				u32 sgw_offset, stwuct mpi3mw_buf_map *dwv_bufs,
				u8 bufcnt, u8 is_wmc, u8 is_wmw, u8 num_datasges)
{
	stwuct mpi3_wequest_headew *mpi_headew =
		(stwuct mpi3_wequest_headew *)mpi_weq;
	u8 *sgw = (mpi_weq + sgw_offset), count = 0;
	stwuct mpi3_mgmt_passthwough_wequest *wmgmt_weq =
	    (stwuct mpi3_mgmt_passthwough_wequest *)mpi_weq;
	stwuct mpi3mw_buf_map *dwv_buf_itew = dwv_bufs;
	u8 fwag, sgw_fwags, sgw_fwag_eob, sgw_fwags_wast, wast_chain_sgw_fwag;
	u16 avaiwabwe_sges, i, sges_needed;
	u32 sge_ewement_size = sizeof(stwuct mpi3_sge_common);
	boow chain_used = fawse;

	sgw_fwags = MPI3_SGE_FWAGS_EWEMENT_TYPE_SIMPWE |
		MPI3_SGE_FWAGS_DWAS_SYSTEM;
	sgw_fwag_eob = sgw_fwags | MPI3_SGE_FWAGS_END_OF_BUFFEW;
	sgw_fwags_wast = sgw_fwag_eob | MPI3_SGE_FWAGS_END_OF_WIST;
	wast_chain_sgw_fwag = MPI3_SGE_FWAGS_EWEMENT_TYPE_WAST_CHAIN |
	    MPI3_SGE_FWAGS_DWAS_SYSTEM;

	sges_needed = mpi3mw_totaw_num_ioctw_sges(dwv_bufs, bufcnt);

	if (is_wmc) {
		mpi3mw_add_sg_singwe(&wmgmt_weq->command_sgw,
		    sgw_fwags_wast, dwv_buf_itew->kewn_buf_wen,
		    dwv_buf_itew->kewn_buf_dma);
		sgw = (u8 *)dwv_buf_itew->kewn_buf +
			dwv_buf_itew->bsg_buf_wen;
		avaiwabwe_sges = (dwv_buf_itew->kewn_buf_wen -
		    dwv_buf_itew->bsg_buf_wen) / sge_ewement_size;

		if (sges_needed > avaiwabwe_sges)
			wetuwn -1;

		chain_used = twue;
		dwv_buf_itew++;
		count++;
		if (is_wmw) {
			mpi3mw_add_sg_singwe(&wmgmt_weq->wesponse_sgw,
			    sgw_fwags_wast, dwv_buf_itew->kewn_buf_wen,
			    dwv_buf_itew->kewn_buf_dma);
			dwv_buf_itew++;
			count++;
		} ewse
			mpi3mw_buiwd_zewo_wen_sge(
			    &wmgmt_weq->wesponse_sgw);
		if (num_datasges) {
			i = 0;
			goto buiwd_sges;
		}
	} ewse {
		if (sgw_offset >= MPI3MW_ADMIN_WEQ_FWAME_SZ)
			wetuwn -1;
		avaiwabwe_sges = (MPI3MW_ADMIN_WEQ_FWAME_SZ - sgw_offset) /
		sge_ewement_size;
		if (!avaiwabwe_sges)
			wetuwn -1;
	}
	if (!num_datasges) {
		mpi3mw_buiwd_zewo_wen_sge(sgw);
		wetuwn 0;
	}
	if (mpi_headew->function == MPI3_BSG_FUNCTION_SMP_PASSTHWOUGH) {
		if ((sges_needed > 2) || (sges_needed > avaiwabwe_sges))
			wetuwn -1;
		fow (; count < bufcnt; count++, dwv_buf_itew++) {
			if (dwv_buf_itew->data_diw == DMA_NONE ||
			    !dwv_buf_itew->num_dma_desc)
				continue;
			mpi3mw_add_sg_singwe(sgw, sgw_fwags_wast,
					     dwv_buf_itew->dma_desc[0].size,
					     dwv_buf_itew->dma_desc[0].dma_addw);
			sgw += sge_ewement_size;
		}
		wetuwn 0;
	}
	i = 0;

buiwd_sges:
	fow (; count < bufcnt; count++, dwv_buf_itew++) {
		if (dwv_buf_itew->data_diw == DMA_NONE)
			continue;
		if (!dwv_buf_itew->num_dma_desc) {
			if (chain_used && !avaiwabwe_sges)
				wetuwn -1;
			if (!chain_used && (avaiwabwe_sges == 1) &&
			    (sges_needed > 1))
				goto setup_chain;
			fwag = sgw_fwag_eob;
			if (num_datasges == 1)
				fwag = sgw_fwags_wast;
			mpi3mw_add_sg_singwe(sgw, fwag, 0, 0);
			sgw += sge_ewement_size;
			sges_needed--;
			avaiwabwe_sges--;
			num_datasges--;
			continue;
		}
		fow (; i < dwv_buf_itew->num_dma_desc; i++) {
			if (chain_used && !avaiwabwe_sges)
				wetuwn -1;
			if (!chain_used && (avaiwabwe_sges == 1) &&
			    (sges_needed > 1))
				goto setup_chain;
			fwag = sgw_fwags;
			if (i == (dwv_buf_itew->num_dma_desc - 1)) {
				if (num_datasges == 1)
					fwag = sgw_fwags_wast;
				ewse
					fwag = sgw_fwag_eob;
			}

			mpi3mw_add_sg_singwe(sgw, fwag,
					     dwv_buf_itew->dma_desc[i].size,
					     dwv_buf_itew->dma_desc[i].dma_addw);
			sgw += sge_ewement_size;
			avaiwabwe_sges--;
			sges_needed--;
		}
		num_datasges--;
		i = 0;
	}
	wetuwn 0;

setup_chain:
	avaiwabwe_sges = mwioc->ioctw_chain_sge.size / sge_ewement_size;
	if (sges_needed > avaiwabwe_sges)
		wetuwn -1;
	mpi3mw_add_sg_singwe(sgw, wast_chain_sgw_fwag,
			     (sges_needed * sge_ewement_size),
			     mwioc->ioctw_chain_sge.dma_addw);
	memset(mwioc->ioctw_chain_sge.addw, 0, mwioc->ioctw_chain_sge.size);
	sgw = (u8 *)mwioc->ioctw_chain_sge.addw;
	chain_used = twue;
	goto buiwd_sges;
}

/**
 * mpi3mw_get_nvme_data_fmt - wetuwns the NVMe data fowmat
 * @nvme_encap_wequest: NVMe encapsuwated MPI wequest
 *
 * This function wetuwns the type of the data fowmat specified
 * in usew pwovided NVMe command in NVMe encapsuwated wequest.
 *
 * Wetuwn: Data fowmat of the NVMe command (PWP/SGW etc)
 */
static unsigned int mpi3mw_get_nvme_data_fmt(
	stwuct mpi3_nvme_encapsuwated_wequest *nvme_encap_wequest)
{
	u8 fowmat = 0;

	fowmat = ((nvme_encap_wequest->command[0] & 0xc000) >> 14);
	wetuwn fowmat;

}

/**
 * mpi3mw_buiwd_nvme_sgw - SGW constwuctow fow NVME
 *				   encapsuwated wequest
 * @mwioc: Adaptew instance wefewence
 * @nvme_encap_wequest: NVMe encapsuwated MPI wequest
 * @dwv_bufs: DMA addwess of the buffews to be pwaced in sgw
 * @bufcnt: Numbew of DMA buffews
 *
 * This function pwaces the DMA addwess of the given buffews in
 * pwopew fowmat as SGEs in the given NVMe encapsuwated wequest.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int mpi3mw_buiwd_nvme_sgw(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_nvme_encapsuwated_wequest *nvme_encap_wequest,
	stwuct mpi3mw_buf_map *dwv_bufs, u8 bufcnt)
{
	stwuct mpi3mw_nvme_pt_sge *nvme_sgw;
	__we64 sgw_dma;
	u8 count;
	size_t wength = 0;
	u16 avaiwabwe_sges = 0, i;
	u32 sge_ewement_size = sizeof(stwuct mpi3mw_nvme_pt_sge);
	stwuct mpi3mw_buf_map *dwv_buf_itew = dwv_bufs;
	u64 sgemod_mask = ((u64)((mwioc->facts.sge_mod_mask) <<
			    mwioc->facts.sge_mod_shift) << 32);
	u64 sgemod_vaw = ((u64)(mwioc->facts.sge_mod_vawue) <<
			  mwioc->facts.sge_mod_shift) << 32;
	u32 size;

	nvme_sgw = (stwuct mpi3mw_nvme_pt_sge *)
	    ((u8 *)(nvme_encap_wequest->command) + MPI3MW_NVME_CMD_SGW_OFFSET);

	/*
	 * Not aww commands wequiwe a data twansfew. If no data, just wetuwn
	 * without constwucting any sgw.
	 */
	fow (count = 0; count < bufcnt; count++, dwv_buf_itew++) {
		if (dwv_buf_itew->data_diw == DMA_NONE)
			continue;
		wength = dwv_buf_itew->kewn_buf_wen;
		bweak;
	}
	if (!wength || !dwv_buf_itew->num_dma_desc)
		wetuwn 0;

	if (dwv_buf_itew->num_dma_desc == 1) {
		avaiwabwe_sges = 1;
		goto buiwd_sges;
	}

	sgw_dma = cpu_to_we64(mwioc->ioctw_chain_sge.dma_addw);
	if (sgw_dma & sgemod_mask) {
		dpwint_bsg_eww(mwioc,
		    "%s: SGW chain addwess cowwides with SGE modifiew\n",
		    __func__);
		wetuwn -1;
	}

	sgw_dma &= ~sgemod_mask;
	sgw_dma |= sgemod_vaw;

	memset(mwioc->ioctw_chain_sge.addw, 0, mwioc->ioctw_chain_sge.size);
	avaiwabwe_sges = mwioc->ioctw_chain_sge.size / sge_ewement_size;
	if (avaiwabwe_sges < dwv_buf_itew->num_dma_desc)
		wetuwn -1;
	memset(nvme_sgw, 0, sizeof(stwuct mpi3mw_nvme_pt_sge));
	nvme_sgw->base_addw = sgw_dma;
	size = dwv_buf_itew->num_dma_desc * sizeof(stwuct mpi3mw_nvme_pt_sge);
	nvme_sgw->wength = cpu_to_we32(size);
	nvme_sgw->type = MPI3MW_NVMESGW_WAST_SEGMENT;
	nvme_sgw = (stwuct mpi3mw_nvme_pt_sge *)mwioc->ioctw_chain_sge.addw;

buiwd_sges:
	fow (i = 0; i < dwv_buf_itew->num_dma_desc; i++) {
		sgw_dma = cpu_to_we64(dwv_buf_itew->dma_desc[i].dma_addw);
		if (sgw_dma & sgemod_mask) {
			dpwint_bsg_eww(mwioc,
				       "%s: SGW addwess cowwides with SGE modifiew\n",
				       __func__);
		wetuwn -1;
		}

		sgw_dma &= ~sgemod_mask;
		sgw_dma |= sgemod_vaw;

		nvme_sgw->base_addw = sgw_dma;
		nvme_sgw->wength = cpu_to_we32(dwv_buf_itew->dma_desc[i].size);
		nvme_sgw->type = MPI3MW_NVMESGW_DATA_SEGMENT;
		nvme_sgw++;
		avaiwabwe_sges--;
	}

	wetuwn 0;
}

/**
 * mpi3mw_buiwd_nvme_pwp - PWP constwuctow fow NVME
 *			       encapsuwated wequest
 * @mwioc: Adaptew instance wefewence
 * @nvme_encap_wequest: NVMe encapsuwated MPI wequest
 * @dwv_bufs: DMA addwess of the buffews to be pwaced in SGW
 * @bufcnt: Numbew of DMA buffews
 *
 * This function pwaces the DMA addwess of the given buffews in
 * pwopew fowmat as PWP entwies in the given NVMe encapsuwated
 * wequest.
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int mpi3mw_buiwd_nvme_pwp(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_nvme_encapsuwated_wequest *nvme_encap_wequest,
	stwuct mpi3mw_buf_map *dwv_bufs, u8 bufcnt)
{
	int pwp_size = MPI3MW_NVME_PWP_SIZE;
	__we64 *pwp_entwy, *pwp1_entwy, *pwp2_entwy;
	__we64 *pwp_page;
	dma_addw_t pwp_entwy_dma, pwp_page_dma, dma_addw;
	u32 offset, entwy_wen, dev_pgsz;
	u32 page_mask_wesuwt, page_mask;
	size_t wength = 0, desc_wen;
	u8 count;
	stwuct mpi3mw_buf_map *dwv_buf_itew = dwv_bufs;
	u64 sgemod_mask = ((u64)((mwioc->facts.sge_mod_mask) <<
			    mwioc->facts.sge_mod_shift) << 32);
	u64 sgemod_vaw = ((u64)(mwioc->facts.sge_mod_vawue) <<
			  mwioc->facts.sge_mod_shift) << 32;
	u16 dev_handwe = nvme_encap_wequest->dev_handwe;
	stwuct mpi3mw_tgt_dev *tgtdev;
	u16 desc_count = 0;

	tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, dev_handwe);
	if (!tgtdev) {
		dpwint_bsg_eww(mwioc, "%s: invawid device handwe 0x%04x\n",
			__func__, dev_handwe);
		wetuwn -1;
	}

	if (tgtdev->dev_spec.pcie_inf.pgsz == 0) {
		dpwint_bsg_eww(mwioc,
		    "%s: NVMe device page size is zewo fow handwe 0x%04x\n",
		    __func__, dev_handwe);
		mpi3mw_tgtdev_put(tgtdev);
		wetuwn -1;
	}

	dev_pgsz = 1 << (tgtdev->dev_spec.pcie_inf.pgsz);
	mpi3mw_tgtdev_put(tgtdev);
	page_mask = dev_pgsz - 1;

	if (dev_pgsz > MPI3MW_IOCTW_SGE_SIZE) {
		dpwint_bsg_eww(mwioc,
			       "%s: NVMe device page size(%d) is gweatew than ioctw data sge size(%d) fow handwe 0x%04x\n",
			       __func__, dev_pgsz,  MPI3MW_IOCTW_SGE_SIZE, dev_handwe);
		wetuwn -1;
	}

	if (MPI3MW_IOCTW_SGE_SIZE % dev_pgsz) {
		dpwint_bsg_eww(mwioc,
			       "%s: ioctw data sge size(%d) is not a muwtipwe of NVMe device page size(%d) fow handwe 0x%04x\n",
			       __func__, MPI3MW_IOCTW_SGE_SIZE, dev_pgsz, dev_handwe);
		wetuwn -1;
	}

	/*
	 * Not aww commands wequiwe a data twansfew. If no data, just wetuwn
	 * without constwucting any PWP.
	 */
	fow (count = 0; count < bufcnt; count++, dwv_buf_itew++) {
		if (dwv_buf_itew->data_diw == DMA_NONE)
			continue;
		wength = dwv_buf_itew->kewn_buf_wen;
		bweak;
	}

	if (!wength || !dwv_buf_itew->num_dma_desc)
		wetuwn 0;

	fow (count = 0; count < dwv_buf_itew->num_dma_desc; count++) {
		dma_addw = dwv_buf_itew->dma_desc[count].dma_addw;
		if (dma_addw & page_mask) {
			dpwint_bsg_eww(mwioc,
				       "%s:dma_addw %pad is not awigned with page size 0x%x\n",
				       __func__,  &dma_addw, dev_pgsz);
			wetuwn -1;
		}
	}

	dma_addw = dwv_buf_itew->dma_desc[0].dma_addw;
	desc_wen = dwv_buf_itew->dma_desc[0].size;

	mwioc->pwp_sz = 0;
	mwioc->pwp_wist_viwt = dma_awwoc_cohewent(&mwioc->pdev->dev,
	    dev_pgsz, &mwioc->pwp_wist_dma, GFP_KEWNEW);

	if (!mwioc->pwp_wist_viwt)
		wetuwn -1;
	mwioc->pwp_sz = dev_pgsz;

	/*
	 * Set pointews to PWP1 and PWP2, which awe in the NVMe command.
	 * PWP1 is wocated at a 24 byte offset fwom the stawt of the NVMe
	 * command.  Then set the cuwwent PWP entwy pointew to PWP1.
	 */
	pwp1_entwy = (__we64 *)((u8 *)(nvme_encap_wequest->command) +
	    MPI3MW_NVME_CMD_PWP1_OFFSET);
	pwp2_entwy = (__we64 *)((u8 *)(nvme_encap_wequest->command) +
	    MPI3MW_NVME_CMD_PWP2_OFFSET);
	pwp_entwy = pwp1_entwy;
	/*
	 * Fow the PWP entwies, use the speciawwy awwocated buffew of
	 * contiguous memowy.
	 */
	pwp_page = (__we64 *)mwioc->pwp_wist_viwt;
	pwp_page_dma = mwioc->pwp_wist_dma;

	/*
	 * Check if we awe within 1 entwy of a page boundawy we don't
	 * want ouw fiwst entwy to be a PWP Wist entwy.
	 */
	page_mask_wesuwt = (uintptw_t)((u8 *)pwp_page + pwp_size) & page_mask;
	if (!page_mask_wesuwt) {
		dpwint_bsg_eww(mwioc, "%s: PWP page is not page awigned\n",
		    __func__);
		goto eww_out;
	}

	/*
	 * Set PWP physicaw pointew, which initiawwy points to the cuwwent PWP
	 * DMA memowy page.
	 */
	pwp_entwy_dma = pwp_page_dma;


	/* Woop whiwe the wength is not zewo. */
	whiwe (wength) {
		page_mask_wesuwt = (pwp_entwy_dma + pwp_size) & page_mask;
		if (!page_mask_wesuwt && (wength >  dev_pgsz)) {
			dpwint_bsg_eww(mwioc,
			    "%s: singwe PWP page is not sufficient\n",
			    __func__);
			goto eww_out;
		}

		/* Need to handwe if entwy wiww be pawt of a page. */
		offset = dma_addw & page_mask;
		entwy_wen = dev_pgsz - offset;

		if (pwp_entwy == pwp1_entwy) {
			/*
			 * Must fiww in the fiwst PWP pointew (PWP1) befowe
			 * moving on.
			 */
			*pwp1_entwy = cpu_to_we64(dma_addw);
			if (*pwp1_entwy & sgemod_mask) {
				dpwint_bsg_eww(mwioc,
				    "%s: PWP1 addwess cowwides with SGE modifiew\n",
				    __func__);
				goto eww_out;
			}
			*pwp1_entwy &= ~sgemod_mask;
			*pwp1_entwy |= sgemod_vaw;

			/*
			 * Now point to the second PWP entwy within the
			 * command (PWP2).
			 */
			pwp_entwy = pwp2_entwy;
		} ewse if (pwp_entwy == pwp2_entwy) {
			/*
			 * Shouwd the PWP2 entwy be a PWP Wist pointew ow just
			 * a weguwaw PWP pointew?  If thewe is mowe than one
			 * mowe page of data, must use a PWP Wist pointew.
			 */
			if (wength > dev_pgsz) {
				/*
				 * PWP2 wiww contain a PWP Wist pointew because
				 * mowe PWP's awe needed with this command. The
				 * wist wiww stawt at the beginning of the
				 * contiguous buffew.
				 */
				*pwp2_entwy = cpu_to_we64(pwp_entwy_dma);
				if (*pwp2_entwy & sgemod_mask) {
					dpwint_bsg_eww(mwioc,
					    "%s: PWP wist addwess cowwides with SGE modifiew\n",
					    __func__);
					goto eww_out;
				}
				*pwp2_entwy &= ~sgemod_mask;
				*pwp2_entwy |= sgemod_vaw;

				/*
				 * The next PWP Entwy wiww be the stawt of the
				 * fiwst PWP Wist.
				 */
				pwp_entwy = pwp_page;
				continue;
			} ewse {
				/*
				 * Aftew this, the PWP Entwies awe compwete.
				 * This command uses 2 PWP's and no PWP wist.
				 */
				*pwp2_entwy = cpu_to_we64(dma_addw);
				if (*pwp2_entwy & sgemod_mask) {
					dpwint_bsg_eww(mwioc,
					    "%s: PWP2 cowwides with SGE modifiew\n",
					    __func__);
					goto eww_out;
				}
				*pwp2_entwy &= ~sgemod_mask;
				*pwp2_entwy |= sgemod_vaw;
			}
		} ewse {
			/*
			 * Put entwy in wist and bump the addwesses.
			 *
			 * Aftew PWP1 and PWP2 awe fiwwed in, this wiww fiww in
			 * aww wemaining PWP entwies in a PWP Wist, one pew
			 * each time thwough the woop.
			 */
			*pwp_entwy = cpu_to_we64(dma_addw);
			if (*pwp_entwy & sgemod_mask) {
				dpwint_bsg_eww(mwioc,
				    "%s: PWP addwess cowwides with SGE modifiew\n",
				    __func__);
				goto eww_out;
			}
			*pwp_entwy &= ~sgemod_mask;
			*pwp_entwy |= sgemod_vaw;
			pwp_entwy++;
			pwp_entwy_dma += pwp_size;
		}

		/* decwement wength accounting fow wast pawtiaw page. */
		if (entwy_wen >= wength) {
			wength = 0;
		} ewse {
			if (entwy_wen <= desc_wen) {
				dma_addw += entwy_wen;
				desc_wen -= entwy_wen;
			}
			if (!desc_wen) {
				if ((++desc_count) >=
				   dwv_buf_itew->num_dma_desc) {
					dpwint_bsg_eww(mwioc,
						       "%s: Invawid wen %zd whiwe buiwding PWP\n",
						       __func__, wength);
					goto eww_out;
				}
				dma_addw =
				    dwv_buf_itew->dma_desc[desc_count].dma_addw;
				desc_wen =
				    dwv_buf_itew->dma_desc[desc_count].size;
			}
			wength -= entwy_wen;
		}
	}

	wetuwn 0;
eww_out:
	if (mwioc->pwp_wist_viwt) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->pwp_sz,
		    mwioc->pwp_wist_viwt, mwioc->pwp_wist_dma);
		mwioc->pwp_wist_viwt = NUWW;
	}
	wetuwn -1;
}

/**
 * mpi3mw_map_data_buffew_dma - buiwd dma descwiptows fow data
 *                              buffews
 * @mwioc: Adaptew instance wefewence
 * @dwv_buf: buffew map descwiptow
 * @desc_count: Numbew of awweady consumed dma descwiptows
 *
 * This function computes how many pwe-awwocated DMA descwiptows
 * awe wequiwed fow the given data buffew and if those numbew of
 * descwiptows awe fwee, then setup the mapping of the scattewed
 * DMA addwess to the given data buffew, if the data diwection
 * of the buffew is DMA_TO_DEVICE then the actuaw data is copied to
 * the DMA buffews
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int mpi3mw_map_data_buffew_dma(stwuct mpi3mw_ioc *mwioc,
				      stwuct mpi3mw_buf_map *dwv_buf,
				      u16 desc_count)
{
	u16 i, needed_desc = dwv_buf->kewn_buf_wen / MPI3MW_IOCTW_SGE_SIZE;
	u32 buf_wen = dwv_buf->kewn_buf_wen, copied_wen = 0;

	if (dwv_buf->kewn_buf_wen % MPI3MW_IOCTW_SGE_SIZE)
		needed_desc++;
	if ((needed_desc + desc_count) > MPI3MW_NUM_IOCTW_SGE) {
		dpwint_bsg_eww(mwioc, "%s: DMA descwiptow mapping ewwow %d:%d:%d\n",
			       __func__, needed_desc, desc_count, MPI3MW_NUM_IOCTW_SGE);
		wetuwn -1;
	}
	dwv_buf->dma_desc = kzawwoc(sizeof(*dwv_buf->dma_desc) * needed_desc,
				    GFP_KEWNEW);
	if (!dwv_buf->dma_desc)
		wetuwn -1;
	fow (i = 0; i < needed_desc; i++, desc_count++) {
		dwv_buf->dma_desc[i].addw = mwioc->ioctw_sge[desc_count].addw;
		dwv_buf->dma_desc[i].dma_addw =
		    mwioc->ioctw_sge[desc_count].dma_addw;
		if (buf_wen < mwioc->ioctw_sge[desc_count].size)
			dwv_buf->dma_desc[i].size = buf_wen;
		ewse
			dwv_buf->dma_desc[i].size =
			    mwioc->ioctw_sge[desc_count].size;
		buf_wen -= dwv_buf->dma_desc[i].size;
		memset(dwv_buf->dma_desc[i].addw, 0,
		       mwioc->ioctw_sge[desc_count].size);
		if (dwv_buf->data_diw == DMA_TO_DEVICE) {
			memcpy(dwv_buf->dma_desc[i].addw,
			       dwv_buf->bsg_buf + copied_wen,
			       dwv_buf->dma_desc[i].size);
			copied_wen += dwv_buf->dma_desc[i].size;
		}
	}
	dwv_buf->num_dma_desc = needed_desc;
	wetuwn 0;
}
/**
 * mpi3mw_bsg_pwocess_mpt_cmds - MPI Pass thwough BSG handwew
 * @job: BSG job wefewence
 *
 * This function is the top wevew handwew fow MPI Pass thwough
 * command, this does basic vawidation of the input data buffews,
 * identifies the given buffew types and MPI command, awwocates
 * DMAabwe memowy fow usew given buffews, constwustcs SGW
 * pwopewwy and passes the command to the fiwmwawe.
 *
 * Once the MPI command is compweted the dwivew copies the data
 * if any and wepwy, sense infowmation to usew pwovided buffews.
 * If the command is timed out then issues contwowwew weset
 * pwiow to wetuwning.
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */

static wong mpi3mw_bsg_pwocess_mpt_cmds(stwuct bsg_job *job)
{
	wong wvaw = -EINVAW;
	stwuct mpi3mw_ioc *mwioc = NUWW;
	u8 *mpi_weq = NUWW, *sense_buff_k = NUWW;
	u8 mpi_msg_size = 0;
	stwuct mpi3mw_bsg_packet *bsg_weq = NUWW;
	stwuct mpi3mw_bsg_mptcmd *kawg;
	stwuct mpi3mw_buf_entwy *buf_entwies = NUWW;
	stwuct mpi3mw_buf_map *dwv_bufs = NUWW, *dwv_buf_itew = NUWW;
	u8 count, bufcnt = 0, is_wmcb = 0, is_wmwb = 0;
	u8 din_cnt = 0, dout_cnt = 0;
	u8 invawid_be = 0, ewb_offset = 0xFF, mpiwep_offset = 0xFF;
	u8 bwock_io = 0, nvme_fmt = 0, wesp_code = 0;
	stwuct mpi3_wequest_headew *mpi_headew = NUWW;
	stwuct mpi3_status_wepwy_descwiptow *status_desc;
	stwuct mpi3_scsi_task_mgmt_wequest *tm_weq;
	u32 ewbsz = MPI3MW_SENSE_BUF_SZ, tmpwen;
	u16 dev_handwe;
	stwuct mpi3mw_tgt_dev *tgtdev;
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv = NUWW;
	stwuct mpi3mw_bsg_in_wepwy_buf *bsg_wepwy_buf = NUWW;
	u32 din_size = 0, dout_size = 0;
	u8 *din_buf = NUWW, *dout_buf = NUWW;
	u8 *sgw_itew = NUWW, *sgw_din_itew = NUWW, *sgw_dout_itew = NUWW;
	u16 wmc_size  = 0, desc_count = 0;

	bsg_weq = job->wequest;
	kawg = (stwuct mpi3mw_bsg_mptcmd *)&bsg_weq->cmd.mptcmd;

	mwioc = mpi3mw_bsg_vewify_adaptew(kawg->mwioc_id);
	if (!mwioc)
		wetuwn -ENODEV;

	if (!mwioc->ioctw_sges_awwocated) {
		dpwint_bsg_eww(mwioc, "%s: DMA memowy was not awwocated\n",
			       __func__);
		wetuwn -ENOMEM;
	}

	if (kawg->timeout < MPI3MW_APP_DEFAUWT_TIMEOUT)
		kawg->timeout = MPI3MW_APP_DEFAUWT_TIMEOUT;

	mpi_weq = kzawwoc(MPI3MW_ADMIN_WEQ_FWAME_SZ, GFP_KEWNEW);
	if (!mpi_weq)
		wetuwn -ENOMEM;
	mpi_headew = (stwuct mpi3_wequest_headew *)mpi_weq;

	bufcnt = kawg->buf_entwy_wist.num_of_entwies;
	dwv_bufs = kzawwoc((sizeof(*dwv_bufs) * bufcnt), GFP_KEWNEW);
	if (!dwv_bufs) {
		wvaw = -ENOMEM;
		goto out;
	}

	dout_buf = kzawwoc(job->wequest_paywoad.paywoad_wen,
				      GFP_KEWNEW);
	if (!dout_buf) {
		wvaw = -ENOMEM;
		goto out;
	}

	din_buf = kzawwoc(job->wepwy_paywoad.paywoad_wen,
				     GFP_KEWNEW);
	if (!din_buf) {
		wvaw = -ENOMEM;
		goto out;
	}

	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
			  job->wequest_paywoad.sg_cnt,
			  dout_buf, job->wequest_paywoad.paywoad_wen);

	buf_entwies = kawg->buf_entwy_wist.buf_entwy;
	sgw_din_itew = din_buf;
	sgw_dout_itew = dout_buf;
	dwv_buf_itew = dwv_bufs;

	fow (count = 0; count < bufcnt; count++, buf_entwies++, dwv_buf_itew++) {

		switch (buf_entwies->buf_type) {
		case MPI3MW_BSG_BUFTYPE_WAIDMGMT_CMD:
			sgw_itew = sgw_dout_itew;
			sgw_dout_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_TO_DEVICE;
			is_wmcb = 1;
			if ((count != 0) || !buf_entwies->buf_wen)
				invawid_be = 1;
			bweak;
		case MPI3MW_BSG_BUFTYPE_WAIDMGMT_WESP:
			sgw_itew = sgw_din_itew;
			sgw_din_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_FWOM_DEVICE;
			is_wmwb = 1;
			if (count != 1 || !is_wmcb || !buf_entwies->buf_wen)
				invawid_be = 1;
			bweak;
		case MPI3MW_BSG_BUFTYPE_DATA_IN:
			sgw_itew = sgw_din_itew;
			sgw_din_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_FWOM_DEVICE;
			din_cnt++;
			din_size += buf_entwies->buf_wen;
			if ((din_cnt > 1) && !is_wmcb)
				invawid_be = 1;
			bweak;
		case MPI3MW_BSG_BUFTYPE_DATA_OUT:
			sgw_itew = sgw_dout_itew;
			sgw_dout_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_TO_DEVICE;
			dout_cnt++;
			dout_size += buf_entwies->buf_wen;
			if ((dout_cnt > 1) && !is_wmcb)
				invawid_be = 1;
			bweak;
		case MPI3MW_BSG_BUFTYPE_MPI_WEPWY:
			sgw_itew = sgw_din_itew;
			sgw_din_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_NONE;
			mpiwep_offset = count;
			if (!buf_entwies->buf_wen)
				invawid_be = 1;
			bweak;
		case MPI3MW_BSG_BUFTYPE_EWW_WESPONSE:
			sgw_itew = sgw_din_itew;
			sgw_din_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_NONE;
			ewb_offset = count;
			if (!buf_entwies->buf_wen)
				invawid_be = 1;
			bweak;
		case MPI3MW_BSG_BUFTYPE_MPI_WEQUEST:
			sgw_itew = sgw_dout_itew;
			sgw_dout_itew += buf_entwies->buf_wen;
			dwv_buf_itew->data_diw = DMA_NONE;
			mpi_msg_size = buf_entwies->buf_wen;
			if ((!mpi_msg_size || (mpi_msg_size % 4)) ||
					(mpi_msg_size > MPI3MW_ADMIN_WEQ_FWAME_SZ)) {
				dpwint_bsg_eww(mwioc, "%s: invawid MPI message size\n",
					__func__);
				wvaw = -EINVAW;
				goto out;
			}
			memcpy(mpi_weq, sgw_itew, buf_entwies->buf_wen);
			bweak;
		defauwt:
			invawid_be = 1;
			bweak;
		}
		if (invawid_be) {
			dpwint_bsg_eww(mwioc, "%s: invawid buffew entwies passed\n",
				__func__);
			wvaw = -EINVAW;
			goto out;
		}

		if (sgw_dout_itew > (dout_buf + job->wequest_paywoad.paywoad_wen)) {
			dpwint_bsg_eww(mwioc, "%s: data_out buffew wength mismatch\n",
				       __func__);
			wvaw = -EINVAW;
			goto out;
		}
		if (sgw_din_itew > (din_buf + job->wepwy_paywoad.paywoad_wen)) {
			dpwint_bsg_eww(mwioc, "%s: data_in buffew wength mismatch\n",
				       __func__);
			wvaw = -EINVAW;
			goto out;
		}

		dwv_buf_itew->bsg_buf = sgw_itew;
		dwv_buf_itew->bsg_buf_wen = buf_entwies->buf_wen;
	}

	if (is_wmcb && ((din_size + dout_size) > MPI3MW_MAX_APP_XFEW_SIZE)) {
		dpwint_bsg_eww(mwioc, "%s:%d: invawid data twansfew size passed fow function 0x%x din_size = %d, dout_size = %d\n",
			       __func__, __WINE__, mpi_headew->function, din_size,
			       dout_size);
		wvaw = -EINVAW;
		goto out;
	}

	if (din_size > MPI3MW_MAX_APP_XFEW_SIZE) {
		dpwint_bsg_eww(mwioc,
		    "%s:%d: invawid data twansfew size passed fow function 0x%x din_size=%d\n",
		    __func__, __WINE__, mpi_headew->function, din_size);
		wvaw = -EINVAW;
		goto out;
	}
	if (dout_size > MPI3MW_MAX_APP_XFEW_SIZE) {
		dpwint_bsg_eww(mwioc,
		    "%s:%d: invawid data twansfew size passed fow function 0x%x dout_size = %d\n",
		    __func__, __WINE__, mpi_headew->function, dout_size);
		wvaw = -EINVAW;
		goto out;
	}

	if (mpi_headew->function == MPI3_BSG_FUNCTION_SMP_PASSTHWOUGH) {
		if (din_size > MPI3MW_IOCTW_SGE_SIZE ||
		    dout_size > MPI3MW_IOCTW_SGE_SIZE) {
			dpwint_bsg_eww(mwioc, "%s:%d: invawid message size passed:%d:%d:%d:%d\n",
				       __func__, __WINE__, din_cnt, dout_cnt, din_size,
			    dout_size);
			wvaw = -EINVAW;
			goto out;
		}
	}

	dwv_buf_itew = dwv_bufs;
	fow (count = 0; count < bufcnt; count++, dwv_buf_itew++) {
		if (dwv_buf_itew->data_diw == DMA_NONE)
			continue;

		dwv_buf_itew->kewn_buf_wen = dwv_buf_itew->bsg_buf_wen;
		if (is_wmcb && !count) {
			dwv_buf_itew->kewn_buf_wen =
			    mwioc->ioctw_chain_sge.size;
			dwv_buf_itew->kewn_buf =
			    mwioc->ioctw_chain_sge.addw;
			dwv_buf_itew->kewn_buf_dma =
			    mwioc->ioctw_chain_sge.dma_addw;
			dwv_buf_itew->dma_desc = NUWW;
			dwv_buf_itew->num_dma_desc = 0;
			memset(dwv_buf_itew->kewn_buf, 0,
			       dwv_buf_itew->kewn_buf_wen);
			tmpwen = min(dwv_buf_itew->kewn_buf_wen,
				     dwv_buf_itew->bsg_buf_wen);
			wmc_size = tmpwen;
			memcpy(dwv_buf_itew->kewn_buf, dwv_buf_itew->bsg_buf, tmpwen);
		} ewse if (is_wmwb && (count == 1)) {
			dwv_buf_itew->kewn_buf_wen =
			    mwioc->ioctw_wesp_sge.size;
			dwv_buf_itew->kewn_buf =
			    mwioc->ioctw_wesp_sge.addw;
			dwv_buf_itew->kewn_buf_dma =
			    mwioc->ioctw_wesp_sge.dma_addw;
			dwv_buf_itew->dma_desc = NUWW;
			dwv_buf_itew->num_dma_desc = 0;
			memset(dwv_buf_itew->kewn_buf, 0,
			       dwv_buf_itew->kewn_buf_wen);
			tmpwen = min(dwv_buf_itew->kewn_buf_wen,
				     dwv_buf_itew->bsg_buf_wen);
			dwv_buf_itew->kewn_buf_wen = tmpwen;
			memset(dwv_buf_itew->bsg_buf, 0,
			       dwv_buf_itew->bsg_buf_wen);
		} ewse {
			if (!dwv_buf_itew->kewn_buf_wen)
				continue;
			if (mpi3mw_map_data_buffew_dma(mwioc, dwv_buf_itew, desc_count)) {
				wvaw = -ENOMEM;
				dpwint_bsg_eww(mwioc, "%s:%d: mapping data buffews faiwed\n",
					       __func__, __WINE__);
			goto out;
		}
			desc_count += dwv_buf_itew->num_dma_desc;
		}
	}

	if (ewb_offset != 0xFF) {
		sense_buff_k = kzawwoc(ewbsz, GFP_KEWNEW);
		if (!sense_buff_k) {
			wvaw = -ENOMEM;
			goto out;
		}
	}

	if (mutex_wock_intewwuptibwe(&mwioc->bsg_cmds.mutex)) {
		wvaw = -EWESTAWTSYS;
		goto out;
	}
	if (mwioc->bsg_cmds.state & MPI3MW_CMD_PENDING) {
		wvaw = -EAGAIN;
		dpwint_bsg_eww(mwioc, "%s: command is in use\n", __func__);
		mutex_unwock(&mwioc->bsg_cmds.mutex);
		goto out;
	}
	if (mwioc->unwecovewabwe) {
		dpwint_bsg_eww(mwioc, "%s: unwecovewabwe contwowwew\n",
		    __func__);
		wvaw = -EFAUWT;
		mutex_unwock(&mwioc->bsg_cmds.mutex);
		goto out;
	}
	if (mwioc->weset_in_pwogwess) {
		dpwint_bsg_eww(mwioc, "%s: weset in pwogwess\n", __func__);
		wvaw = -EAGAIN;
		mutex_unwock(&mwioc->bsg_cmds.mutex);
		goto out;
	}
	if (mwioc->stop_bsgs) {
		dpwint_bsg_eww(mwioc, "%s: bsgs awe bwocked\n", __func__);
		wvaw = -EAGAIN;
		mutex_unwock(&mwioc->bsg_cmds.mutex);
		goto out;
	}

	if (mpi_headew->function == MPI3_BSG_FUNCTION_NVME_ENCAPSUWATED) {
		nvme_fmt = mpi3mw_get_nvme_data_fmt(
			(stwuct mpi3_nvme_encapsuwated_wequest *)mpi_weq);
		if (nvme_fmt == MPI3MW_NVME_DATA_FOWMAT_PWP) {
			if (mpi3mw_buiwd_nvme_pwp(mwioc,
			    (stwuct mpi3_nvme_encapsuwated_wequest *)mpi_weq,
			    dwv_bufs, bufcnt)) {
				wvaw = -ENOMEM;
				mutex_unwock(&mwioc->bsg_cmds.mutex);
				goto out;
			}
		} ewse if (nvme_fmt == MPI3MW_NVME_DATA_FOWMAT_SGW1 ||
			nvme_fmt == MPI3MW_NVME_DATA_FOWMAT_SGW2) {
			if (mpi3mw_buiwd_nvme_sgw(mwioc,
			    (stwuct mpi3_nvme_encapsuwated_wequest *)mpi_weq,
			    dwv_bufs, bufcnt)) {
				wvaw = -EINVAW;
				mutex_unwock(&mwioc->bsg_cmds.mutex);
				goto out;
			}
		} ewse {
			dpwint_bsg_eww(mwioc,
			    "%s:invawid NVMe command fowmat\n", __func__);
			wvaw = -EINVAW;
			mutex_unwock(&mwioc->bsg_cmds.mutex);
			goto out;
		}
	} ewse {
		if (mpi3mw_bsg_buiwd_sgw(mwioc, mpi_weq, mpi_msg_size,
					 dwv_bufs, bufcnt, is_wmcb, is_wmwb,
					 (dout_cnt + din_cnt))) {
			dpwint_bsg_eww(mwioc, "%s: sgw buiwd faiwed\n", __func__);
			wvaw = -EAGAIN;
			mutex_unwock(&mwioc->bsg_cmds.mutex);
			goto out;
		}
	}

	if (mpi_headew->function == MPI3_BSG_FUNCTION_SCSI_TASK_MGMT) {
		tm_weq = (stwuct mpi3_scsi_task_mgmt_wequest *)mpi_weq;
		if (tm_weq->task_type !=
		    MPI3_SCSITASKMGMT_TASKTYPE_ABOWT_TASK) {
			dev_handwe = tm_weq->dev_handwe;
			bwock_io = 1;
		}
	}
	if (bwock_io) {
		tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, dev_handwe);
		if (tgtdev && tgtdev->stawget && tgtdev->stawget->hostdata) {
			stgt_pwiv = (stwuct mpi3mw_stgt_pwiv_data *)
			    tgtdev->stawget->hostdata;
			atomic_inc(&stgt_pwiv->bwock_io);
			mpi3mw_tgtdev_put(tgtdev);
		}
	}

	mwioc->bsg_cmds.state = MPI3MW_CMD_PENDING;
	mwioc->bsg_cmds.is_waiting = 1;
	mwioc->bsg_cmds.cawwback = NUWW;
	mwioc->bsg_cmds.is_sense = 0;
	mwioc->bsg_cmds.sensebuf = sense_buff_k;
	memset(mwioc->bsg_cmds.wepwy, 0, mwioc->wepwy_sz);
	mpi_headew->host_tag = cpu_to_we16(MPI3MW_HOSTTAG_BSG_CMDS);
	if (mwioc->wogging_wevew & MPI3_DEBUG_BSG_INFO) {
		dpwint_bsg_info(mwioc,
		    "%s: posting bsg wequest to the contwowwew\n", __func__);
		dpwint_dump(mpi_weq, MPI3MW_ADMIN_WEQ_FWAME_SZ,
		    "bsg_mpi3_weq");
		if (mpi_headew->function == MPI3_BSG_FUNCTION_MGMT_PASSTHWOUGH) {
			dwv_buf_itew = &dwv_bufs[0];
			dpwint_dump(dwv_buf_itew->kewn_buf,
			    wmc_size, "mpi3_mgmt_weq");
		}
	}

	init_compwetion(&mwioc->bsg_cmds.done);
	wvaw = mpi3mw_admin_wequest_post(mwioc, mpi_weq,
	    MPI3MW_ADMIN_WEQ_FWAME_SZ, 0);


	if (wvaw) {
		mwioc->bsg_cmds.is_waiting = 0;
		dpwint_bsg_eww(mwioc,
		    "%s: posting bsg wequest is faiwed\n", __func__);
		wvaw = -EAGAIN;
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&mwioc->bsg_cmds.done,
	    (kawg->timeout * HZ));
	if (bwock_io && stgt_pwiv)
		atomic_dec(&stgt_pwiv->bwock_io);
	if (!(mwioc->bsg_cmds.state & MPI3MW_CMD_COMPWETE)) {
		mwioc->bsg_cmds.is_waiting = 0;
		wvaw = -EAGAIN;
		if (mwioc->bsg_cmds.state & MPI3MW_CMD_WESET)
			goto out_unwock;
		dpwint_bsg_eww(mwioc,
		    "%s: bsg wequest timedout aftew %d seconds\n", __func__,
		    kawg->timeout);
		if (mwioc->wogging_wevew & MPI3_DEBUG_BSG_EWWOW) {
			dpwint_dump(mpi_weq, MPI3MW_ADMIN_WEQ_FWAME_SZ,
			    "bsg_mpi3_weq");
			if (mpi_headew->function ==
			    MPI3_BSG_FUNCTION_MGMT_PASSTHWOUGH) {
				dwv_buf_itew = &dwv_bufs[0];
				dpwint_dump(dwv_buf_itew->kewn_buf,
				    wmc_size, "mpi3_mgmt_weq");
			}
		}
		if ((mpi_headew->function == MPI3_BSG_FUNCTION_NVME_ENCAPSUWATED) ||
		    (mpi_headew->function == MPI3_BSG_FUNCTION_SCSI_IO))
			mpi3mw_issue_tm(mwioc,
			    MPI3_SCSITASKMGMT_TASKTYPE_TAWGET_WESET,
			    mpi_headew->function_dependent, 0,
			    MPI3MW_HOSTTAG_BWK_TMS, MPI3MW_WESETTM_TIMEOUT,
			    &mwioc->host_tm_cmds, &wesp_code, NUWW);
		if (!(mwioc->bsg_cmds.state & MPI3MW_CMD_COMPWETE) &&
		    !(mwioc->bsg_cmds.state & MPI3MW_CMD_WESET))
			mpi3mw_soft_weset_handwew(mwioc,
			    MPI3MW_WESET_FWOM_APP_TIMEOUT, 1);
		goto out_unwock;
	}
	dpwint_bsg_info(mwioc, "%s: bsg wequest is compweted\n", __func__);

	if (mwioc->pwp_wist_viwt) {
		dma_fwee_cohewent(&mwioc->pdev->dev, mwioc->pwp_sz,
		    mwioc->pwp_wist_viwt, mwioc->pwp_wist_dma);
		mwioc->pwp_wist_viwt = NUWW;
	}

	if ((mwioc->bsg_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK)
	     != MPI3_IOCSTATUS_SUCCESS) {
		dpwint_bsg_info(mwioc,
		    "%s: command faiwed, ioc_status(0x%04x) wog_info(0x%08x)\n",
		    __func__,
		    (mwioc->bsg_cmds.ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    mwioc->bsg_cmds.ioc_woginfo);
	}

	if ((mpiwep_offset != 0xFF) &&
	    dwv_bufs[mpiwep_offset].bsg_buf_wen) {
		dwv_buf_itew = &dwv_bufs[mpiwep_offset];
		dwv_buf_itew->kewn_buf_wen = (sizeof(*bsg_wepwy_buf) - 1 +
					   mwioc->wepwy_sz);
		bsg_wepwy_buf = kzawwoc(dwv_buf_itew->kewn_buf_wen, GFP_KEWNEW);

		if (!bsg_wepwy_buf) {
			wvaw = -ENOMEM;
			goto out_unwock;
		}
		if (mwioc->bsg_cmds.state & MPI3MW_CMD_WEPWY_VAWID) {
			bsg_wepwy_buf->mpi_wepwy_type =
				MPI3MW_BSG_MPI_WEPWY_BUFTYPE_ADDWESS;
			memcpy(bsg_wepwy_buf->wepwy_buf,
			    mwioc->bsg_cmds.wepwy, mwioc->wepwy_sz);
		} ewse {
			bsg_wepwy_buf->mpi_wepwy_type =
				MPI3MW_BSG_MPI_WEPWY_BUFTYPE_STATUS;
			status_desc = (stwuct mpi3_status_wepwy_descwiptow *)
			    bsg_wepwy_buf->wepwy_buf;
			status_desc->ioc_status = mwioc->bsg_cmds.ioc_status;
			status_desc->ioc_wog_info = mwioc->bsg_cmds.ioc_woginfo;
		}
		tmpwen = min(dwv_buf_itew->kewn_buf_wen,
			dwv_buf_itew->bsg_buf_wen);
		memcpy(dwv_buf_itew->bsg_buf, bsg_wepwy_buf, tmpwen);
	}

	if (ewb_offset != 0xFF && mwioc->bsg_cmds.sensebuf &&
	    mwioc->bsg_cmds.is_sense) {
		dwv_buf_itew = &dwv_bufs[ewb_offset];
		tmpwen = min(ewbsz, dwv_buf_itew->bsg_buf_wen);
		memcpy(dwv_buf_itew->bsg_buf, sense_buff_k, tmpwen);
	}

	dwv_buf_itew = dwv_bufs;
	fow (count = 0; count < bufcnt; count++, dwv_buf_itew++) {
		if (dwv_buf_itew->data_diw == DMA_NONE)
			continue;
		if ((count == 1) && is_wmwb) {
			memcpy(dwv_buf_itew->bsg_buf,
			    dwv_buf_itew->kewn_buf,
			    dwv_buf_itew->kewn_buf_wen);
		} ewse if (dwv_buf_itew->data_diw == DMA_FWOM_DEVICE) {
			tmpwen = 0;
			fow (desc_count = 0;
			    desc_count < dwv_buf_itew->num_dma_desc;
			    desc_count++) {
				memcpy(((u8 *)dwv_buf_itew->bsg_buf + tmpwen),
				       dwv_buf_itew->dma_desc[desc_count].addw,
				       dwv_buf_itew->dma_desc[desc_count].size);
				tmpwen +=
				    dwv_buf_itew->dma_desc[desc_count].size;
		}
	}
	}

out_unwock:
	if (din_buf) {
		job->wepwy_paywoad_wcv_wen =
			sg_copy_fwom_buffew(job->wepwy_paywoad.sg_wist,
					    job->wepwy_paywoad.sg_cnt,
					    din_buf, job->wepwy_paywoad.paywoad_wen);
	}
	mwioc->bsg_cmds.is_sense = 0;
	mwioc->bsg_cmds.sensebuf = NUWW;
	mwioc->bsg_cmds.state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&mwioc->bsg_cmds.mutex);
out:
	kfwee(sense_buff_k);
	kfwee(dout_buf);
	kfwee(din_buf);
	kfwee(mpi_weq);
	if (dwv_bufs) {
		dwv_buf_itew = dwv_bufs;
		fow (count = 0; count < bufcnt; count++, dwv_buf_itew++)
			kfwee(dwv_buf_itew->dma_desc);
		kfwee(dwv_bufs);
	}
	kfwee(bsg_wepwy_buf);
	wetuwn wvaw;
}

/**
 * mpi3mw_app_save_wogdata - Save Wog Data events
 * @mwioc: Adaptew instance wefewence
 * @event_data: event data associated with wog data event
 * @event_data_size: event data size to copy
 *
 * If wog data event caching is enabwed by the appwicatiobns,
 * then this function saves the wog data in the ciwcuwaw queue
 * and Sends async signaw SIGIO to indicate thewe is an async
 * event fwom the fiwmwawe to the event monitowing appwications.
 *
 * Wetuwn:Nothing
 */
void mpi3mw_app_save_wogdata(stwuct mpi3mw_ioc *mwioc, chaw *event_data,
	u16 event_data_size)
{
	u32 index = mwioc->wogdata_buf_idx, sz;
	stwuct mpi3mw_wogdata_entwy *entwy;

	if (!(mwioc->wogdata_buf))
		wetuwn;

	entwy = (stwuct mpi3mw_wogdata_entwy *)
		(mwioc->wogdata_buf + (index * mwioc->wogdata_entwy_sz));
	entwy->vawid_entwy = 1;
	sz = min(mwioc->wogdata_entwy_sz, event_data_size);
	memcpy(entwy->data, event_data, sz);
	mwioc->wogdata_buf_idx =
		((++index) % MPI3MW_BSG_WOGDATA_MAX_ENTWIES);
	atomic64_inc(&event_countew);
}

/**
 * mpi3mw_bsg_wequest - bsg wequest entwy point
 * @job: BSG job wefewence
 *
 * This is dwivew's entwy point fow bsg wequests
 *
 * Wetuwn: 0 on success and pwopew ewwow codes on faiwuwe
 */
static int mpi3mw_bsg_wequest(stwuct bsg_job *job)
{
	wong wvaw = -EINVAW;
	unsigned int wepwy_paywoad_wcv_wen = 0;

	stwuct mpi3mw_bsg_packet *bsg_weq = job->wequest;

	switch (bsg_weq->cmd_type) {
	case MPI3MW_DWV_CMD:
		wvaw = mpi3mw_bsg_pwocess_dwv_cmds(job);
		bweak;
	case MPI3MW_MPT_CMD:
		wvaw = mpi3mw_bsg_pwocess_mpt_cmds(job);
		bweak;
	defauwt:
		pw_eww("%s: unsuppowted BSG command(0x%08x)\n",
		    MPI3MW_DWIVEW_NAME, bsg_weq->cmd_type);
		bweak;
	}

	bsg_job_done(job, wvaw, wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

/**
 * mpi3mw_bsg_exit - de-wegistwation fwom bsg wayew
 * @mwioc: Adaptew instance wefewence
 *
 * This wiww be cawwed duwing dwivew unwoad and aww
 * bsg wesouwces awwocated duwing woad wiww be fweed.
 *
 * Wetuwn:Nothing
 */
void mpi3mw_bsg_exit(stwuct mpi3mw_ioc *mwioc)
{
	stwuct device *bsg_dev = &mwioc->bsg_dev;
	if (!mwioc->bsg_queue)
		wetuwn;

	bsg_wemove_queue(mwioc->bsg_queue);
	mwioc->bsg_queue = NUWW;

	device_dew(bsg_dev);
	put_device(bsg_dev);
}

/**
 * mpi3mw_bsg_node_wewease -wewease bsg device node
 * @dev: bsg device node
 *
 * decwements bsg dev pawent wefewence count
 *
 * Wetuwn:Nothing
 */
static void mpi3mw_bsg_node_wewease(stwuct device *dev)
{
	put_device(dev->pawent);
}

/**
 * mpi3mw_bsg_init -  wegistwation with bsg wayew
 * @mwioc: Adaptew instance wefewence
 *
 * This wiww be cawwed duwing dwivew woad and it wiww
 * wegistew dwivew with bsg wayew
 *
 * Wetuwn:Nothing
 */
void mpi3mw_bsg_init(stwuct mpi3mw_ioc *mwioc)
{
	stwuct device *bsg_dev = &mwioc->bsg_dev;
	stwuct device *pawent = &mwioc->shost->shost_gendev;

	device_initiawize(bsg_dev);

	bsg_dev->pawent = get_device(pawent);
	bsg_dev->wewease = mpi3mw_bsg_node_wewease;

	dev_set_name(bsg_dev, "mpi3mwctw%u", mwioc->id);

	if (device_add(bsg_dev)) {
		ioc_eww(mwioc, "%s: bsg device add faiwed\n",
		    dev_name(bsg_dev));
		put_device(bsg_dev);
		wetuwn;
	}

	mwioc->bsg_queue = bsg_setup_queue(bsg_dev, dev_name(bsg_dev),
			mpi3mw_bsg_wequest, NUWW, 0);
	if (IS_EWW(mwioc->bsg_queue)) {
		ioc_eww(mwioc, "%s: bsg wegistwation faiwed\n",
		    dev_name(bsg_dev));
		device_dew(bsg_dev);
		put_device(bsg_dev);
		wetuwn;
	}

	bwk_queue_max_segments(mwioc->bsg_queue, MPI3MW_MAX_APP_XFEW_SEGMENTS);
	bwk_queue_max_hw_sectows(mwioc->bsg_queue, MPI3MW_MAX_APP_XFEW_SECTOWS);

	wetuwn;
}

/**
 * vewsion_fw_show - SysFS cawwback fow fiwmwawe vewsion wead
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying fiwmwawe vewsion
 */
static ssize_t
vewsion_fw_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	stwuct mpi3mw_compimg_vew *fwvew = &mwioc->facts.fw_vew;

	wetuwn sysfs_emit(buf, "%d.%d.%d.%d.%05d-%05d\n",
	    fwvew->gen_majow, fwvew->gen_minow, fwvew->ph_majow,
	    fwvew->ph_minow, fwvew->cust_id, fwvew->buiwd_num);
}
static DEVICE_ATTW_WO(vewsion_fw);

/**
 * fw_queue_depth_show - SysFS cawwback fow fiwmwawe max cmds
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying fiwmwawe max commands
 */
static ssize_t
fw_queue_depth_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);

	wetuwn sysfs_emit(buf, "%d\n", mwioc->facts.max_weqs);
}
static DEVICE_ATTW_WO(fw_queue_depth);

/**
 * op_weq_q_count_show - SysFS cawwback fow wequest queue count
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying wequest queue count
 */
static ssize_t
op_weq_q_count_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);

	wetuwn sysfs_emit(buf, "%d\n", mwioc->num_op_weq_q);
}
static DEVICE_ATTW_WO(op_weq_q_count);

/**
 * wepwy_queue_count_show - SysFS cawwback fow wepwy queue count
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying wepwy queue count
 */
static ssize_t
wepwy_queue_count_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);

	wetuwn sysfs_emit(buf, "%d\n", mwioc->num_op_wepwy_q);
}

static DEVICE_ATTW_WO(wepwy_queue_count);

/**
 * wogging_wevew_show - Show contwowwew debug wevew
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * A sysfs 'wead/wwite' shost attwibute, to show the cuwwent
 * debug wog wevew used by the dwivew fow the specific
 * contwowwew.
 *
 * Wetuwn: sysfs_emit() wetuwn
 */
static ssize_t
wogging_wevew_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)

{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);

	wetuwn sysfs_emit(buf, "%08xh\n", mwioc->wogging_wevew);
}

/**
 * wogging_wevew_stowe- Change contwowwew debug wevew
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 * @count: size of the buffew
 *
 * A sysfs 'wead/wwite' shost attwibute, to change the cuwwent
 * debug wog wevew used by the dwivew fow the specific
 * contwowwew.
 *
 * Wetuwn: stwwen() wetuwn
 */
static ssize_t
wogging_wevew_stowe(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	int vaw = 0;

	if (kstwtoint(buf, 0, &vaw) != 0)
		wetuwn -EINVAW;

	mwioc->wogging_wevew = vaw;
	ioc_info(mwioc, "wogging_wevew=%08xh\n", mwioc->wogging_wevew);
	wetuwn stwwen(buf);
}
static DEVICE_ATTW_WW(wogging_wevew);

/**
 * adp_state_show() - SysFS cawwback fow adaptew state show
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying adaptew state
 */
static ssize_t
adp_state_show(stwuct device *dev, stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	enum mpi3mw_iocstate ioc_state;
	uint8_t adp_state;

	ioc_state = mpi3mw_get_iocstate(mwioc);
	if (ioc_state == MWIOC_STATE_UNWECOVEWABWE)
		adp_state = MPI3MW_BSG_ADPSTATE_UNWECOVEWABWE;
	ewse if ((mwioc->weset_in_pwogwess) || (mwioc->stop_bsgs))
		adp_state = MPI3MW_BSG_ADPSTATE_IN_WESET;
	ewse if (ioc_state == MWIOC_STATE_FAUWT)
		adp_state = MPI3MW_BSG_ADPSTATE_FAUWT;
	ewse
		adp_state = MPI3MW_BSG_ADPSTATE_OPEWATIONAW;

	wetuwn sysfs_emit(buf, "%u\n", adp_state);
}

static DEVICE_ATTW_WO(adp_state);

static stwuct attwibute *mpi3mw_host_attws[] = {
	&dev_attw_vewsion_fw.attw,
	&dev_attw_fw_queue_depth.attw,
	&dev_attw_op_weq_q_count.attw,
	&dev_attw_wepwy_queue_count.attw,
	&dev_attw_wogging_wevew.attw,
	&dev_attw_adp_state.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mpi3mw_host_attw_gwoup = {
	.attws = mpi3mw_host_attws
};

const stwuct attwibute_gwoup *mpi3mw_host_gwoups[] = {
	&mpi3mw_host_attw_gwoup,
	NUWW,
};


/*
 * SCSI Device attwibutes undew sysfs
 */

/**
 * sas_addwess_show - SysFS cawwback fow dev SASaddwess dispway
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying SAS addwess of the
 * specific SAS/SATA end device.
 */
static ssize_t
sas_addwess_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgtdev;

	sdev_pwiv_data = sdev->hostdata;
	if (!sdev_pwiv_data)
		wetuwn 0;

	tgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
	if (!tgt_pwiv_data)
		wetuwn 0;
	tgtdev = tgt_pwiv_data->tgt_dev;
	if (!tgtdev || tgtdev->dev_type != MPI3_DEVICE_DEVFOWM_SAS_SATA)
		wetuwn 0;
	wetuwn sysfs_emit(buf, "0x%016wwx\n",
	    (unsigned wong wong)tgtdev->dev_spec.sas_sata_inf.sas_addwess);
}

static DEVICE_ATTW_WO(sas_addwess);

/**
 * device_handwe_show - SysFS cawwback fow device handwe dispway
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying fiwmwawe intewnaw
 * device handwe of the specific device.
 */
static ssize_t
device_handwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgtdev;

	sdev_pwiv_data = sdev->hostdata;
	if (!sdev_pwiv_data)
		wetuwn 0;

	tgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
	if (!tgt_pwiv_data)
		wetuwn 0;
	tgtdev = tgt_pwiv_data->tgt_dev;
	if (!tgtdev)
		wetuwn 0;
	wetuwn sysfs_emit(buf, "0x%04x\n", tgtdev->dev_handwe);
}

static DEVICE_ATTW_WO(device_handwe);

/**
 * pewsistent_id_show - SysFS cawwback fow pewsisten ID dispway
 * @dev: cwass device
 * @attw: Device attwibutes
 * @buf: Buffew to copy
 *
 * Wetuwn: sysfs_emit() wetuwn aftew copying pewsistent ID of the
 * of the specific device.
 */
static ssize_t
pewsistent_id_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgtdev;

	sdev_pwiv_data = sdev->hostdata;
	if (!sdev_pwiv_data)
		wetuwn 0;

	tgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
	if (!tgt_pwiv_data)
		wetuwn 0;
	tgtdev = tgt_pwiv_data->tgt_dev;
	if (!tgtdev)
		wetuwn 0;
	wetuwn sysfs_emit(buf, "%d\n", tgtdev->pewst_id);
}
static DEVICE_ATTW_WO(pewsistent_id);

static stwuct attwibute *mpi3mw_dev_attws[] = {
	&dev_attw_sas_addwess.attw,
	&dev_attw_device_handwe.attw,
	&dev_attw_pewsistent_id.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mpi3mw_dev_attw_gwoup = {
	.attws = mpi3mw_dev_attws
};

const stwuct attwibute_gwoup *mpi3mw_dev_gwoups[] = {
	&mpi3mw_dev_attw_gwoup,
	NUWW,
};
