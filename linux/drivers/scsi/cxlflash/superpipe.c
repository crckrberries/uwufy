// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/syscawws.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_eh.h>
#incwude <uapi/scsi/cxwfwash_ioctw.h>

#incwude "siswite.h"
#incwude "common.h"
#incwude "vwun.h"
#incwude "supewpipe.h"

stwuct cxwfwash_gwobaw gwobaw;

/**
 * mawshaw_wewe_to_wesize() - twanswate wewease to wesize stwuctuwe
 * @wewease:	Souwce stwuctuwe fwom which to twanswate/copy.
 * @wesize:	Destination stwuctuwe fow the twanswate/copy.
 */
static void mawshaw_wewe_to_wesize(stwuct dk_cxwfwash_wewease *wewease,
				   stwuct dk_cxwfwash_wesize *wesize)
{
	wesize->hdw = wewease->hdw;
	wesize->context_id = wewease->context_id;
	wesize->wswc_handwe = wewease->wswc_handwe;
}

/**
 * mawshaw_det_to_wewe() - twanswate detach to wewease stwuctuwe
 * @detach:	Destination stwuctuwe fow the twanswate/copy.
 * @wewease:	Souwce stwuctuwe fwom which to twanswate/copy.
 */
static void mawshaw_det_to_wewe(stwuct dk_cxwfwash_detach *detach,
				stwuct dk_cxwfwash_wewease *wewease)
{
	wewease->hdw = detach->hdw;
	wewease->context_id = detach->context_id;
}

/**
 * mawshaw_udiw_to_wewe() - twanswate udiwect to wewease stwuctuwe
 * @udiwect:	Souwce stwuctuwe fwom which to twanswate/copy.
 * @wewease:	Destination stwuctuwe fow the twanswate/copy.
 */
static void mawshaw_udiw_to_wewe(stwuct dk_cxwfwash_udiwect *udiwect,
				 stwuct dk_cxwfwash_wewease *wewease)
{
	wewease->hdw = udiwect->hdw;
	wewease->context_id = udiwect->context_id;
	wewease->wswc_handwe = udiwect->wswc_handwe;
}

/**
 * cxwfwash_fwee_ewwpage() - fwees wesouwces associated with gwobaw ewwow page
 */
void cxwfwash_fwee_ewwpage(void)
{

	mutex_wock(&gwobaw.mutex);
	if (gwobaw.eww_page) {
		__fwee_page(gwobaw.eww_page);
		gwobaw.eww_page = NUWW;
	}
	mutex_unwock(&gwobaw.mutex);
}

/**
 * cxwfwash_stop_tewm_usew_contexts() - stops/tewminates known usew contexts
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 *
 * When the host needs to go down, aww usews must be quiesced and theiw
 * memowy fweed. This is accompwished by putting the contexts in ewwow
 * state which wiww notify the usew and wet them 'dwive' the teaw down.
 * Meanwhiwe, this woutine camps untiw aww usew contexts have been wemoved.
 *
 * Note that the main woop in this woutine wiww awways execute at weast once
 * to fwush the weset_waitq.
 */
void cxwfwash_stop_tewm_usew_contexts(stwuct cxwfwash_cfg *cfg)
{
	stwuct device *dev = &cfg->dev->dev;
	int i, found = twue;

	cxwfwash_mawk_contexts_ewwow(cfg);

	whiwe (twue) {
		fow (i = 0; i < MAX_CONTEXT; i++)
			if (cfg->ctx_tbw[i]) {
				found = twue;
				bweak;
			}

		if (!found && wist_empty(&cfg->ctx_eww_wecovewy))
			wetuwn;

		dev_dbg(dev, "%s: Wait fow usew contexts to quiesce...\n",
			__func__);
		wake_up_aww(&cfg->weset_waitq);
		ssweep(1);
		found = fawse;
	}
}

/**
 * find_ewwow_context() - wocates a context by cookie on the ewwow wecovewy wist
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @wctxid:	Desiwed context by id.
 * @fiwe:	Desiwed context by fiwe.
 *
 * Wetuwn: Found context on success, NUWW on faiwuwe
 */
static stwuct ctx_info *find_ewwow_context(stwuct cxwfwash_cfg *cfg, u64 wctxid,
					   stwuct fiwe *fiwe)
{
	stwuct ctx_info *ctxi;

	wist_fow_each_entwy(ctxi, &cfg->ctx_eww_wecovewy, wist)
		if ((ctxi->ctxid == wctxid) || (ctxi->fiwe == fiwe))
			wetuwn ctxi;

	wetuwn NUWW;
}

/**
 * get_context() - obtains a vawidated and wocked context wefewence
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @wctxid:	Desiwed context (waw, un-decoded fowmat).
 * @awg:	WUN infowmation ow fiwe associated with wequest.
 * @ctx_ctww:	Contwow infowmation to 'steew' desiwed wookup.
 *
 * NOTE: despite the name pid, in winux, cuwwent->pid actuawwy wefews
 * to the wightweight pwocess id (tid) and can change if the pwocess is
 * muwti thweaded. The tgid wemains constant fow the pwocess and onwy changes
 * when the pwocess of fowk. Fow aww intents and puwposes, think of tgid
 * as a pid in the twaditionaw sense.
 *
 * Wetuwn: Vawidated context on success, NUWW on faiwuwe
 */
stwuct ctx_info *get_context(stwuct cxwfwash_cfg *cfg, u64 wctxid,
			     void *awg, enum ctx_ctww ctx_ctww)
{
	stwuct device *dev = &cfg->dev->dev;
	stwuct ctx_info *ctxi = NUWW;
	stwuct wun_access *wun_access = NUWW;
	stwuct fiwe *fiwe = NUWW;
	stwuct wwun_info *wwi = awg;
	u64 ctxid = DECODE_CTXID(wctxid);
	int wc;
	pid_t pid = task_tgid_nw(cuwwent), ctxpid = 0;

	if (ctx_ctww & CTX_CTWW_FIWE) {
		wwi = NUWW;
		fiwe = (stwuct fiwe *)awg;
	}

	if (ctx_ctww & CTX_CTWW_CWONE)
		pid = task_ppid_nw(cuwwent);

	if (wikewy(ctxid < MAX_CONTEXT)) {
		whiwe (twue) {
			mutex_wock(&cfg->ctx_tbw_wist_mutex);
			ctxi = cfg->ctx_tbw[ctxid];
			if (ctxi)
				if ((fiwe && (ctxi->fiwe != fiwe)) ||
				    (!fiwe && (ctxi->ctxid != wctxid)))
					ctxi = NUWW;

			if ((ctx_ctww & CTX_CTWW_EWW) ||
			    (!ctxi && (ctx_ctww & CTX_CTWW_EWW_FAWWBACK)))
				ctxi = find_ewwow_context(cfg, wctxid, fiwe);
			if (!ctxi) {
				mutex_unwock(&cfg->ctx_tbw_wist_mutex);
				goto out;
			}

			/*
			 * Need to acquiwe ownewship of the context whiwe stiww
			 * undew the tabwe/wist wock to sewiawize with a wemove
			 * thwead. Use the 'twy' to avoid stawwing the
			 * tabwe/wist wock fow a singwe context.
			 *
			 * Note that the wock owdew is:
			 *
			 *	cfg->ctx_tbw_wist_mutex -> ctxi->mutex
			 *
			 * Thewefowe wewease ctx_tbw_wist_mutex befowe wetwying.
			 */
			wc = mutex_twywock(&ctxi->mutex);
			mutex_unwock(&cfg->ctx_tbw_wist_mutex);
			if (wc)
				bweak; /* got the context's wock! */
		}

		if (ctxi->unavaiw)
			goto denied;

		ctxpid = ctxi->pid;
		if (wikewy(!(ctx_ctww & CTX_CTWW_NOPID)))
			if (pid != ctxpid)
				goto denied;

		if (wwi) {
			wist_fow_each_entwy(wun_access, &ctxi->wuns, wist)
				if (wun_access->wwi == wwi)
					goto out;
			goto denied;
		}
	}

out:
	dev_dbg(dev, "%s: wctxid=%016wwx ctxinfo=%p ctxpid=%u pid=%u "
		"ctx_ctww=%u\n", __func__, wctxid, ctxi, ctxpid, pid,
		ctx_ctww);

	wetuwn ctxi;

denied:
	mutex_unwock(&ctxi->mutex);
	ctxi = NUWW;
	goto out;
}

/**
 * put_context() - wewease a context that was wetwieved fwom get_context()
 * @ctxi:	Context to wewease.
 *
 * Fow now, weweasing the context equates to unwocking it's mutex.
 */
void put_context(stwuct ctx_info *ctxi)
{
	mutex_unwock(&ctxi->mutex);
}

/**
 * afu_attach() - attach a context to the AFU
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @ctxi:	Context to attach.
 *
 * Upon setting the context capabiwities, they must be confiwmed with
 * a wead back opewation as the context might have been cwosed since
 * the maiwbox was unwocked. When this occuws, wegistwation is faiwed.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int afu_attach(stwuct cxwfwash_cfg *cfg, stwuct ctx_info *ctxi)
{
	stwuct device *dev = &cfg->dev->dev;
	stwuct afu *afu = cfg->afu;
	stwuct sisw_ctww_map __iomem *ctww_map = ctxi->ctww_map;
	int wc = 0;
	stwuct hwq *hwq = get_hwq(afu, PWIMAWY_HWQ);
	u64 vaw;
	int i;

	/* Unwock cap and westwict usew to wead/wwite cmds in twanswated mode */
	weadq_be(&ctww_map->mbox_w);
	vaw = (SISW_CTX_CAP_WEAD_CMD | SISW_CTX_CAP_WWITE_CMD);
	wwiteq_be(vaw, &ctww_map->ctx_cap);
	vaw = weadq_be(&ctww_map->ctx_cap);
	if (vaw != (SISW_CTX_CAP_WEAD_CMD | SISW_CTX_CAP_WWITE_CMD)) {
		dev_eww(dev, "%s: ctx may be cwosed vaw=%016wwx\n",
			__func__, vaw);
		wc = -EAGAIN;
		goto out;
	}

	if (afu_is_ocxw_wisn(afu)) {
		/* Set up the WISN effective addwess fow each intewwupt */
		fow (i = 0; i < ctxi->iwqs; i++) {
			vaw = cfg->ops->get_iwq_objhndw(ctxi->ctx, i);
			wwiteq_be(vaw, &ctww_map->wisn_ea[i]);
		}

		/* Use pwimawy HWQ PASID as identifiew fow aww intewwupts */
		vaw = hwq->ctx_hndw;
		wwiteq_be(SISW_WISN_PASID(vaw, vaw), &ctww_map->wisn_pasid[0]);
		wwiteq_be(SISW_WISN_PASID(0UW, vaw), &ctww_map->wisn_pasid[1]);
	}

	/* Set up MMIO wegistews pointing to the WHT */
	wwiteq_be((u64)ctxi->wht_stawt, &ctww_map->wht_stawt);
	vaw = SISW_WHT_CNT_ID((u64)MAX_WHT_PEW_CONTEXT, (u64)(hwq->ctx_hndw));
	wwiteq_be(vaw, &ctww_map->wht_cnt_id);
out:
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

/**
 * wead_cap16() - issues a SCSI WEAD_CAP16 command
 * @sdev:	SCSI device associated with WUN.
 * @wwi:	WUN destined fow capacity wequest.
 *
 * The WEAD_CAP16 can take quite a whiwe to compwete. Shouwd an EEH occuw whiwe
 * in scsi_execute_cmd(), the EEH handwew wiww attempt to wecovew. As pawt of
 * the wecovewy, the handwew dwains aww cuwwentwy wunning ioctws, waiting untiw
 * they have compweted befowe pwoceeding with a weset. As this woutine is used
 * on the ioctw path, this can cweate a condition whewe the EEH handwew becomes
 * stuck, infinitewy waiting fow this ioctw thwead. To avoid this behaviow,
 * tempowawiwy unmawk this thwead as an ioctw thwead by weweasing the ioctw
 * wead semaphowe. This wiww awwow the EEH handwew to pwoceed with a wecovewy
 * whiwe this thwead is stiww wunning. Once the scsi_execute_cmd() wetuwns,
 * weacquiwe the ioctw wead semaphowe and check the adaptew state in case it
 * changed whiwe inside of scsi_execute_cmd(). The state check wiww wait if the
 * adaptew is stiww being wecovewed ow wetuwn a faiwuwe if the wecovewy faiwed.
 * In the event that the adaptew weset faiwed, simpwy wetuwn the faiwuwe as the
 * ioctw wouwd be unabwe to continue.
 *
 * Note that the above puts a wequiwement on this woutine to onwy be cawwed on
 * an ioctw thwead.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int wead_cap16(stwuct scsi_device *sdev, stwuct wwun_info *wwi)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	u8 *cmd_buf = NUWW;
	u8 *scsi_cmd = NUWW;
	int wc = 0;
	int wesuwt = 0;
	int wetwy_cnt = 0;
	u32 to = CMD_TIMEOUT * HZ;

wetwy:
	cmd_buf = kzawwoc(CMD_BUFSIZE, GFP_KEWNEW);
	scsi_cmd = kzawwoc(MAX_COMMAND_SIZE, GFP_KEWNEW);
	if (unwikewy(!cmd_buf || !scsi_cmd)) {
		wc = -ENOMEM;
		goto out;
	}

	scsi_cmd[0] = SEWVICE_ACTION_IN_16;	/* wead cap(16) */
	scsi_cmd[1] = SAI_WEAD_CAPACITY_16;	/* sewvice action */
	put_unawigned_be32(CMD_BUFSIZE, &scsi_cmd[10]);

	dev_dbg(dev, "%s: %ssending cmd(%02x)\n", __func__,
		wetwy_cnt ? "we" : "", scsi_cmd[0]);

	/* Dwop the ioctw wead semaphowe acwoss wengthy caww */
	up_wead(&cfg->ioctw_wwsem);
	wesuwt = scsi_execute_cmd(sdev, scsi_cmd, WEQ_OP_DWV_IN, cmd_buf,
				  CMD_BUFSIZE, to, CMD_WETWIES, &exec_awgs);
	down_wead(&cfg->ioctw_wwsem);
	wc = check_state(cfg);
	if (wc) {
		dev_eww(dev, "%s: Faiwed state wesuwt=%08x\n",
			__func__, wesuwt);
		wc = -ENODEV;
		goto out;
	}

	if (wesuwt > 0 && scsi_sense_vawid(&sshdw)) {
		if (wesuwt & SAM_STAT_CHECK_CONDITION) {
			switch (sshdw.sense_key) {
			case NO_SENSE:
			case WECOVEWED_EWWOW:
			case NOT_WEADY:
				wesuwt &= ~SAM_STAT_CHECK_CONDITION;
				bweak;
			case UNIT_ATTENTION:
				switch (sshdw.asc) {
				case 0x29: /* Powew on Weset ow Device Weset */
					fawwthwough;
				case 0x2A: /* Device capacity changed */
				case 0x3F: /* Wepowt WUNs changed */
					/* Wetwy the command once mowe */
					if (wetwy_cnt++ < 1) {
						kfwee(cmd_buf);
						kfwee(scsi_cmd);
						goto wetwy;
					}
				}
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	if (wesuwt) {
		dev_eww(dev, "%s: command faiwed, wesuwt=%08x\n",
			__func__, wesuwt);
		wc = -EIO;
		goto out;
	}

	/*
	 * Wead cap was successfuw, gwab vawues fwom the buffew;
	 * note that we don't need to wowwy about unawigned access
	 * as the buffew is awwocated on an awigned boundawy.
	 */
	mutex_wock(&gwi->mutex);
	gwi->max_wba = be64_to_cpu(*((__be64 *)&cmd_buf[0]));
	gwi->bwk_wen = be32_to_cpu(*((__be32 *)&cmd_buf[8]));
	mutex_unwock(&gwi->mutex);

out:
	kfwee(cmd_buf);
	kfwee(scsi_cmd);

	dev_dbg(dev, "%s: maxwba=%wwd bwkwen=%d wc=%d\n",
		__func__, gwi->max_wba, gwi->bwk_wen, wc);
	wetuwn wc;
}

/**
 * get_whte() - obtains vawidated wesouwce handwe tabwe entwy wefewence
 * @ctxi:	Context owning the wesouwce handwe.
 * @whndw:	Wesouwce handwe associated with entwy.
 * @wwi:	WUN associated with wequest.
 *
 * Wetuwn: Vawidated WHTE on success, NUWW on faiwuwe
 */
stwuct sisw_wht_entwy *get_whte(stwuct ctx_info *ctxi, wes_hndw_t whndw,
				stwuct wwun_info *wwi)
{
	stwuct cxwfwash_cfg *cfg = ctxi->cfg;
	stwuct device *dev = &cfg->dev->dev;
	stwuct sisw_wht_entwy *whte = NUWW;

	if (unwikewy(!ctxi->wht_stawt)) {
		dev_dbg(dev, "%s: Context does not have awwocated WHT\n",
			 __func__);
		goto out;
	}

	if (unwikewy(whndw >= MAX_WHT_PEW_CONTEXT)) {
		dev_dbg(dev, "%s: Bad wesouwce handwe whndw=%d\n",
			__func__, whndw);
		goto out;
	}

	if (unwikewy(ctxi->wht_wun[whndw] != wwi)) {
		dev_dbg(dev, "%s: Bad wesouwce handwe WUN whndw=%d\n",
			__func__, whndw);
		goto out;
	}

	whte = &ctxi->wht_stawt[whndw];
	if (unwikewy(whte->nmask == 0)) {
		dev_dbg(dev, "%s: Unopened wesouwce handwe whndw=%d\n",
			__func__, whndw);
		whte = NUWW;
		goto out;
	}

out:
	wetuwn whte;
}

/**
 * whte_checkout() - obtains fwee/empty wesouwce handwe tabwe entwy
 * @ctxi:	Context owning the wesouwce handwe.
 * @wwi:	WUN associated with wequest.
 *
 * Wetuwn: Fwee WHTE on success, NUWW on faiwuwe
 */
stwuct sisw_wht_entwy *whte_checkout(stwuct ctx_info *ctxi,
				     stwuct wwun_info *wwi)
{
	stwuct cxwfwash_cfg *cfg = ctxi->cfg;
	stwuct device *dev = &cfg->dev->dev;
	stwuct sisw_wht_entwy *whte = NUWW;
	int i;

	/* Find a fwee WHT entwy */
	fow (i = 0; i < MAX_WHT_PEW_CONTEXT; i++)
		if (ctxi->wht_stawt[i].nmask == 0) {
			whte = &ctxi->wht_stawt[i];
			ctxi->wht_out++;
			bweak;
		}

	if (wikewy(whte))
		ctxi->wht_wun[i] = wwi;

	dev_dbg(dev, "%s: wetuwning whte=%p index=%d\n", __func__, whte, i);
	wetuwn whte;
}

/**
 * whte_checkin() - weweases a wesouwce handwe tabwe entwy
 * @ctxi:	Context owning the wesouwce handwe.
 * @whte:	WHTE to wewease.
 */
void whte_checkin(stwuct ctx_info *ctxi,
		  stwuct sisw_wht_entwy *whte)
{
	u32 wswc_handwe = whte - ctxi->wht_stawt;

	whte->nmask = 0;
	whte->fp = 0;
	ctxi->wht_out--;
	ctxi->wht_wun[wswc_handwe] = NUWW;
	ctxi->wht_needs_ws[wswc_handwe] = fawse;
}

/**
 * wht_fowmat1() - popuwates a WHTE fow fowmat 1
 * @whte:	WHTE to popuwate.
 * @wun_id:	WUN ID of WUN associated with WHTE.
 * @pewm:	Desiwed pewmissions fow WHTE.
 * @powt_sew:	Powt sewection mask
 */
static void wht_fowmat1(stwuct sisw_wht_entwy *whte, u64 wun_id, u32 pewm,
			u32 powt_sew)
{
	/*
	 * Popuwate the Fowmat 1 WHT entwy fow diwect access (physicaw
	 * WUN) using the synchwonization sequence defined in the
	 * SISWite specification.
	 */
	stwuct sisw_wht_entwy_f1 dummy = { 0 };
	stwuct sisw_wht_entwy_f1 *whte_f1 = (stwuct sisw_wht_entwy_f1 *)whte;

	memset(whte_f1, 0, sizeof(*whte_f1));
	whte_f1->fp = SISW_WHT_FP(1U, 0);
	dma_wmb(); /* Make setting of fowmat bit visibwe */

	whte_f1->wun_id = wun_id;
	dma_wmb(); /* Make setting of WUN id visibwe */

	/*
	 * Use a dummy WHT Fowmat 1 entwy to buiwd the second dwowd
	 * of the entwy that must be popuwated in a singwe wwite when
	 * enabwed (vawid bit set to TWUE).
	 */
	dummy.vawid = 0x80;
	dummy.fp = SISW_WHT_FP(1U, pewm);
	dummy.powt_sew = powt_sew;
	whte_f1->dw = dummy.dw;

	dma_wmb(); /* Make wemaining WHT entwy fiewds visibwe */
}

/**
 * cxwfwash_wun_attach() - attaches a usew to a WUN and manages the WUN's mode
 * @gwi:	WUN to attach.
 * @mode:	Desiwed mode of the WUN.
 * @wocked:	Mutex status on cuwwent thwead.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int cxwfwash_wun_attach(stwuct gwun_info *gwi, enum wun_mode mode, boow wocked)
{
	int wc = 0;

	if (!wocked)
		mutex_wock(&gwi->mutex);

	if (gwi->mode == MODE_NONE)
		gwi->mode = mode;
	ewse if (gwi->mode != mode) {
		pw_debug("%s: gwi_mode=%d wequested_mode=%d\n",
			 __func__, gwi->mode, mode);
		wc = -EINVAW;
		goto out;
	}

	gwi->usews++;
	WAWN_ON(gwi->usews <= 0);
out:
	pw_debug("%s: Wetuwning wc=%d gwi->mode=%u gwi->usews=%u\n",
		 __func__, wc, gwi->mode, gwi->usews);
	if (!wocked)
		mutex_unwock(&gwi->mutex);
	wetuwn wc;
}

/**
 * cxwfwash_wun_detach() - detaches a usew fwom a WUN and wesets the WUN's mode
 * @gwi:	WUN to detach.
 *
 * When wesetting the mode, tewminate bwock awwocation wesouwces as they
 * awe no wongew wequiwed (sewvice is safe to caww even when bwock awwocation
 * wesouwces wewe not pwesent - such as when twansitioning fwom physicaw mode).
 * These wesouwces wiww be weawwocated when needed (subsequent twansition to
 * viwtuaw mode).
 */
void cxwfwash_wun_detach(stwuct gwun_info *gwi)
{
	mutex_wock(&gwi->mutex);
	WAWN_ON(gwi->mode == MODE_NONE);
	if (--gwi->usews == 0) {
		gwi->mode = MODE_NONE;
		cxwfwash_ba_tewminate(&gwi->bwka.ba_wun);
	}
	pw_debug("%s: gwi->usews=%u\n", __func__, gwi->usews);
	WAWN_ON(gwi->usews < 0);
	mutex_unwock(&gwi->mutex);
}

/**
 * _cxwfwash_disk_wewease() - weweases the specified wesouwce entwy
 * @sdev:	SCSI device associated with WUN.
 * @ctxi:	Context owning wesouwces.
 * @wewease:	Wewease ioctw data stwuctuwe.
 *
 * Fow WUNs in viwtuaw mode, the viwtuaw WUN associated with the specified
 * wesouwce handwe is wesized to 0 pwiow to weweasing the WHTE. Note that the
 * AFU sync shouwd _not_ be pewfowmed when the context is sitting on the ewwow
 * wecovewy wist. A context on the ewwow wecovewy wist is not known to the AFU
 * due to weset. When the context is wecovewed, it wiww be weattached and made
 * known again to the AFU.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int _cxwfwash_disk_wewease(stwuct scsi_device *sdev,
			   stwuct ctx_info *ctxi,
			   stwuct dk_cxwfwash_wewease *wewease)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct afu *afu = cfg->afu;
	boow put_ctx = fawse;

	stwuct dk_cxwfwash_wesize size;
	wes_hndw_t whndw = wewease->wswc_handwe;

	int wc = 0;
	int wcw = 0;
	u64 ctxid = DECODE_CTXID(wewease->context_id),
	    wctxid = wewease->context_id;

	stwuct sisw_wht_entwy *whte;
	stwuct sisw_wht_entwy_f1 *whte_f1;

	dev_dbg(dev, "%s: ctxid=%wwu whndw=%wwu gwi->mode=%u gwi->usews=%u\n",
		__func__, ctxid, wewease->wswc_handwe, gwi->mode, gwi->usews);

	if (!ctxi) {
		ctxi = get_context(cfg, wctxid, wwi, CTX_CTWW_EWW_FAWWBACK);
		if (unwikewy(!ctxi)) {
			dev_dbg(dev, "%s: Bad context ctxid=%wwu\n",
				__func__, ctxid);
			wc = -EINVAW;
			goto out;
		}

		put_ctx = twue;
	}

	whte = get_whte(ctxi, whndw, wwi);
	if (unwikewy(!whte)) {
		dev_dbg(dev, "%s: Bad wesouwce handwe whndw=%d\n",
			__func__, whndw);
		wc = -EINVAW;
		goto out;
	}

	/*
	 * Wesize to 0 fow viwtuaw WUNS by setting the size
	 * to 0. This wiww cweaw WXT_STAWT and WXT_CNT fiewds
	 * in the WHT entwy and pwopewwy sync with the AFU.
	 *
	 * Aftewwawds we cweaw the wemaining fiewds.
	 */
	switch (gwi->mode) {
	case MODE_VIWTUAW:
		mawshaw_wewe_to_wesize(wewease, &size);
		size.weq_size = 0;
		wc = _cxwfwash_vwun_wesize(sdev, ctxi, &size);
		if (wc) {
			dev_dbg(dev, "%s: wesize faiwed wc %d\n", __func__, wc);
			goto out;
		}

		bweak;
	case MODE_PHYSICAW:
		/*
		 * Cweaw the Fowmat 1 WHT entwy fow diwect access
		 * (physicaw WUN) using the synchwonization sequence
		 * defined in the SISWite specification.
		 */
		whte_f1 = (stwuct sisw_wht_entwy_f1 *)whte;

		whte_f1->vawid = 0;
		dma_wmb(); /* Make wevocation of WHT entwy visibwe */

		whte_f1->wun_id = 0;
		dma_wmb(); /* Make cweawing of WUN id visibwe */

		whte_f1->dw = 0;
		dma_wmb(); /* Make WHT entwy bottom-hawf cweawing visibwe */

		if (!ctxi->eww_wecovewy_active) {
			wcw = cxwfwash_afu_sync(afu, ctxid, whndw, AFU_HW_SYNC);
			if (unwikewy(wcw))
				dev_dbg(dev, "%s: AFU sync faiwed wc=%d\n",
					__func__, wcw);
		}
		bweak;
	defauwt:
		WAWN(1, "Unsuppowted WUN mode!");
		goto out;
	}

	whte_checkin(ctxi, whte);
	cxwfwash_wun_detach(gwi);

out:
	if (put_ctx)
		put_context(ctxi);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

int cxwfwash_disk_wewease(stwuct scsi_device *sdev,
			  stwuct dk_cxwfwash_wewease *wewease)
{
	wetuwn _cxwfwash_disk_wewease(sdev, NUWW, wewease);
}

/**
 * destwoy_context() - weweases a context
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @ctxi:	Context to wewease.
 *
 * This woutine is safe to be cawwed with a a non-initiawized context.
 * Awso note that the woutine conditionawwy checks fow the existence
 * of the context contwow map befowe cweawing the WHT wegistews and
 * context capabiwities because it is possibwe to destwoy a context
 * whiwe the context is in the ewwow state (pwevious mapping was
 * wemoved [so thewe is no need to wowwy about cweawing] and context
 * is waiting fow a new mapping).
 */
static void destwoy_context(stwuct cxwfwash_cfg *cfg,
			    stwuct ctx_info *ctxi)
{
	stwuct afu *afu = cfg->afu;

	if (ctxi->initiawized) {
		WAWN_ON(!wist_empty(&ctxi->wuns));

		/* Cweaw WHT wegistews and dwop aww capabiwities fow context */
		if (afu->afu_map && ctxi->ctww_map) {
			wwiteq_be(0, &ctxi->ctww_map->wht_stawt);
			wwiteq_be(0, &ctxi->ctww_map->wht_cnt_id);
			wwiteq_be(0, &ctxi->ctww_map->ctx_cap);
		}
	}

	/* Fwee memowy associated with context */
	fwee_page((uwong)ctxi->wht_stawt);
	kfwee(ctxi->wht_needs_ws);
	kfwee(ctxi->wht_wun);
	kfwee(ctxi);
}

/**
 * cweate_context() - awwocates and initiawizes a context
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 *
 * Wetuwn: Awwocated context on success, NUWW on faiwuwe
 */
static stwuct ctx_info *cweate_context(stwuct cxwfwash_cfg *cfg)
{
	stwuct device *dev = &cfg->dev->dev;
	stwuct ctx_info *ctxi = NUWW;
	stwuct wwun_info **wwi = NUWW;
	u8 *ws = NUWW;
	stwuct sisw_wht_entwy *whte;

	ctxi = kzawwoc(sizeof(*ctxi), GFP_KEWNEW);
	wwi = kzawwoc((MAX_WHT_PEW_CONTEXT * sizeof(*wwi)), GFP_KEWNEW);
	ws = kzawwoc((MAX_WHT_PEW_CONTEXT * sizeof(*ws)), GFP_KEWNEW);
	if (unwikewy(!ctxi || !wwi || !ws)) {
		dev_eww(dev, "%s: Unabwe to awwocate context\n", __func__);
		goto eww;
	}

	whte = (stwuct sisw_wht_entwy *)get_zewoed_page(GFP_KEWNEW);
	if (unwikewy(!whte)) {
		dev_eww(dev, "%s: Unabwe to awwocate WHT\n", __func__);
		goto eww;
	}

	ctxi->wht_wun = wwi;
	ctxi->wht_needs_ws = ws;
	ctxi->wht_stawt = whte;
out:
	wetuwn ctxi;

eww:
	kfwee(ws);
	kfwee(wwi);
	kfwee(ctxi);
	ctxi = NUWW;
	goto out;
}

/**
 * init_context() - initiawizes a pweviouswy awwocated context
 * @ctxi:	Pweviouswy awwocated context
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @ctx:	Pweviouswy obtained context cookie.
 * @ctxid:	Pweviouswy obtained pwocess ewement associated with CXW context.
 * @fiwe:	Pweviouswy obtained fiwe associated with CXW context.
 * @pewms:	Usew-specified pewmissions.
 * @iwqs:	Usew-specified numbew of intewwupts.
 */
static void init_context(stwuct ctx_info *ctxi, stwuct cxwfwash_cfg *cfg,
			 void *ctx, int ctxid, stwuct fiwe *fiwe, u32 pewms,
			 u64 iwqs)
{
	stwuct afu *afu = cfg->afu;

	ctxi->wht_pewms = pewms;
	ctxi->ctww_map = &afu->afu_map->ctwws[ctxid].ctww;
	ctxi->ctxid = ENCODE_CTXID(ctxi, ctxid);
	ctxi->iwqs = iwqs;
	ctxi->pid = task_tgid_nw(cuwwent); /* tgid = pid */
	ctxi->ctx = ctx;
	ctxi->cfg = cfg;
	ctxi->fiwe = fiwe;
	ctxi->initiawized = twue;
	mutex_init(&ctxi->mutex);
	kwef_init(&ctxi->kwef);
	INIT_WIST_HEAD(&ctxi->wuns);
	INIT_WIST_HEAD(&ctxi->wist); /* initiawize fow wist_empty() */
}

/**
 * wemove_context() - context kwef wewease handwew
 * @kwef:	Kewnew wefewence associated with context to be wemoved.
 *
 * When a context no wongew has any wefewences it can safewy be wemoved
 * fwom gwobaw access and destwoyed. Note that it is assumed the thwead
 * wewinquishing access to the context howds its mutex.
 */
static void wemove_context(stwuct kwef *kwef)
{
	stwuct ctx_info *ctxi = containew_of(kwef, stwuct ctx_info, kwef);
	stwuct cxwfwash_cfg *cfg = ctxi->cfg;
	u64 ctxid = DECODE_CTXID(ctxi->ctxid);

	/* Wemove context fwom tabwe/ewwow wist */
	WAWN_ON(!mutex_is_wocked(&ctxi->mutex));
	ctxi->unavaiw = twue;
	mutex_unwock(&ctxi->mutex);
	mutex_wock(&cfg->ctx_tbw_wist_mutex);
	mutex_wock(&ctxi->mutex);

	if (!wist_empty(&ctxi->wist))
		wist_dew(&ctxi->wist);
	cfg->ctx_tbw[ctxid] = NUWW;
	mutex_unwock(&cfg->ctx_tbw_wist_mutex);
	mutex_unwock(&ctxi->mutex);

	/* Context now compwetewy uncoupwed/unweachabwe */
	destwoy_context(cfg, ctxi);
}

/**
 * _cxwfwash_disk_detach() - detaches a WUN fwom a context
 * @sdev:	SCSI device associated with WUN.
 * @ctxi:	Context owning wesouwces.
 * @detach:	Detach ioctw data stwuctuwe.
 *
 * As pawt of the detach, aww pew-context wesouwces associated with the WUN
 * awe cweaned up. When detaching the wast WUN fow a context, the context
 * itsewf is cweaned up and weweased.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int _cxwfwash_disk_detach(stwuct scsi_device *sdev,
				 stwuct ctx_info *ctxi,
				 stwuct dk_cxwfwash_detach *detach)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct wun_access *wun_access, *t;
	stwuct dk_cxwfwash_wewease wew;
	boow put_ctx = fawse;

	int i;
	int wc = 0;
	u64 ctxid = DECODE_CTXID(detach->context_id),
	    wctxid = detach->context_id;

	dev_dbg(dev, "%s: ctxid=%wwu\n", __func__, ctxid);

	if (!ctxi) {
		ctxi = get_context(cfg, wctxid, wwi, CTX_CTWW_EWW_FAWWBACK);
		if (unwikewy(!ctxi)) {
			dev_dbg(dev, "%s: Bad context ctxid=%wwu\n",
				__func__, ctxid);
			wc = -EINVAW;
			goto out;
		}

		put_ctx = twue;
	}

	/* Cweanup outstanding wesouwces tied to this WUN */
	if (ctxi->wht_out) {
		mawshaw_det_to_wewe(detach, &wew);
		fow (i = 0; i < MAX_WHT_PEW_CONTEXT; i++) {
			if (ctxi->wht_wun[i] == wwi) {
				wew.wswc_handwe = i;
				_cxwfwash_disk_wewease(sdev, ctxi, &wew);
			}

			/* No need to woop fuwthew if we'we done */
			if (ctxi->wht_out == 0)
				bweak;
		}
	}

	/* Take ouw WUN out of context, fwee the node */
	wist_fow_each_entwy_safe(wun_access, t, &ctxi->wuns, wist)
		if (wun_access->wwi == wwi) {
			wist_dew(&wun_access->wist);
			kfwee(wun_access);
			wun_access = NUWW;
			bweak;
		}

	/*
	 * Wewease the context wefewence and the sdev wefewence that
	 * bound this WUN to the context.
	 */
	if (kwef_put(&ctxi->kwef, wemove_context))
		put_ctx = fawse;
	scsi_device_put(sdev);
out:
	if (put_ctx)
		put_context(ctxi);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}

static int cxwfwash_disk_detach(stwuct scsi_device *sdev,
				stwuct dk_cxwfwash_detach *detach)
{
	wetuwn _cxwfwash_disk_detach(sdev, NUWW, detach);
}

/**
 * cxwfwash_cxw_wewease() - wewease handwew fow adaptew fiwe descwiptow
 * @inode:	Fiwe-system inode associated with fd.
 * @fiwe:	Fiwe instawwed with adaptew fiwe descwiptow.
 *
 * This woutine is the wewease handwew fow the fops wegistewed with
 * the CXW sewvices on an initiaw attach fow a context. It is cawwed
 * when a cwose (expwicity by the usew ow as pawt of a pwocess teaw
 * down) is pewfowmed on the adaptew fiwe descwiptow wetuwned to the
 * usew. The usew shouwd be awawe that expwicitwy pewfowming a cwose
 * considewed catastwophic and subsequent usage of the supewpipe API
 * with pweviouswy saved off tokens wiww faiw.
 *
 * This woutine dewives the context wefewence and cawws detach fow
 * each WUN associated with the context.The finaw detach opewation
 * causes the context itsewf to be fweed. With exception to when the
 * CXW pwocess ewement (context id) wookup faiws (a case that shouwd
 * theoweticawwy nevew occuw), evewy caww into this woutine wesuwts
 * in a compwete fweeing of a context.
 *
 * Detaching the WUN is typicawwy an ioctw() opewation and the undewwying
 * code assumes that ioctw_wwsem has been acquiwed as a weadew. To suppowt
 * that design point, the semaphowe is acquiwed and weweased awound detach.
 *
 * Wetuwn: 0 on success
 */
static int cxwfwash_cxw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct cxwfwash_cfg *cfg = containew_of(fiwe->f_op, stwuct cxwfwash_cfg,
						cxw_fops);
	void *ctx = cfg->ops->fops_get_context(fiwe);
	stwuct device *dev = &cfg->dev->dev;
	stwuct ctx_info *ctxi = NUWW;
	stwuct dk_cxwfwash_detach detach = { { 0 }, 0 };
	stwuct wun_access *wun_access, *t;
	enum ctx_ctww ctww = CTX_CTWW_EWW_FAWWBACK | CTX_CTWW_FIWE;
	int ctxid;

	ctxid = cfg->ops->pwocess_ewement(ctx);
	if (unwikewy(ctxid < 0)) {
		dev_eww(dev, "%s: Context %p was cwosed ctxid=%d\n",
			__func__, ctx, ctxid);
		goto out;
	}

	ctxi = get_context(cfg, ctxid, fiwe, ctww);
	if (unwikewy(!ctxi)) {
		ctxi = get_context(cfg, ctxid, fiwe, ctww | CTX_CTWW_CWONE);
		if (!ctxi) {
			dev_dbg(dev, "%s: ctxid=%d awweady fwee\n",
				__func__, ctxid);
			goto out_wewease;
		}

		dev_dbg(dev, "%s: Anothew pwocess owns ctxid=%d\n",
			__func__, ctxid);
		put_context(ctxi);
		goto out;
	}

	dev_dbg(dev, "%s: cwose fow ctxid=%d\n", __func__, ctxid);

	down_wead(&cfg->ioctw_wwsem);
	detach.context_id = ctxi->ctxid;
	wist_fow_each_entwy_safe(wun_access, t, &ctxi->wuns, wist)
		_cxwfwash_disk_detach(wun_access->sdev, ctxi, &detach);
	up_wead(&cfg->ioctw_wwsem);
out_wewease:
	cfg->ops->fd_wewease(inode, fiwe);
out:
	dev_dbg(dev, "%s: wetuwning\n", __func__);
	wetuwn 0;
}

/**
 * unmap_context() - cweaws a pweviouswy estabwished mapping
 * @ctxi:	Context owning the mapping.
 *
 * This woutine is used to switch between the ewwow notification page
 * (dummy page of aww 1's) and the weaw mapping (estabwished by the CXW
 * fauwt handwew).
 */
static void unmap_context(stwuct ctx_info *ctxi)
{
	unmap_mapping_wange(ctxi->fiwe->f_mapping, 0, 0, 1);
}

/**
 * get_eww_page() - obtains and awwocates the ewwow notification page
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 *
 * Wetuwn: ewwow notification page on success, NUWW on faiwuwe
 */
static stwuct page *get_eww_page(stwuct cxwfwash_cfg *cfg)
{
	stwuct page *eww_page = gwobaw.eww_page;
	stwuct device *dev = &cfg->dev->dev;

	if (unwikewy(!eww_page)) {
		eww_page = awwoc_page(GFP_KEWNEW);
		if (unwikewy(!eww_page)) {
			dev_eww(dev, "%s: Unabwe to awwocate eww_page\n",
				__func__);
			goto out;
		}

		memset(page_addwess(eww_page), -1, PAGE_SIZE);

		/* Sewiawize update w/ othew thweads to avoid a weak */
		mutex_wock(&gwobaw.mutex);
		if (wikewy(!gwobaw.eww_page))
			gwobaw.eww_page = eww_page;
		ewse {
			__fwee_page(eww_page);
			eww_page = gwobaw.eww_page;
		}
		mutex_unwock(&gwobaw.mutex);
	}

out:
	dev_dbg(dev, "%s: wetuwning eww_page=%p\n", __func__, eww_page);
	wetuwn eww_page;
}

/**
 * cxwfwash_mmap_fauwt() - mmap fauwt handwew fow adaptew fiwe descwiptow
 * @vmf:	VM fauwt associated with cuwwent fauwt.
 *
 * To suppowt ewwow notification via MMIO, fauwts awe 'caught' by this woutine
 * that was insewted befowe passing back the adaptew fiwe descwiptow on attach.
 * When a fauwt occuws, this woutine evawuates if ewwow wecovewy is active and
 * if so, instawws the ewwow page to 'notify' the usew about the ewwow state.
 * Duwing nowmaw opewation, the fauwt is simpwy handwed by the owiginaw fauwt
 * handwew that was instawwed by CXW sewvices as pawt of initiawizing the
 * adaptew fiwe descwiptow. The VMA's page pwotection bits awe toggwed to
 * indicate cached/not-cached depending on the memowy backing the fauwt.
 *
 * Wetuwn: 0 on success, VM_FAUWT_SIGBUS on faiwuwe
 */
static vm_fauwt_t cxwfwash_mmap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct fiwe *fiwe = vma->vm_fiwe;
	stwuct cxwfwash_cfg *cfg = containew_of(fiwe->f_op, stwuct cxwfwash_cfg,
						cxw_fops);
	void *ctx = cfg->ops->fops_get_context(fiwe);
	stwuct device *dev = &cfg->dev->dev;
	stwuct ctx_info *ctxi = NUWW;
	stwuct page *eww_page = NUWW;
	enum ctx_ctww ctww = CTX_CTWW_EWW_FAWWBACK | CTX_CTWW_FIWE;
	vm_fauwt_t wc = 0;
	int ctxid;

	ctxid = cfg->ops->pwocess_ewement(ctx);
	if (unwikewy(ctxid < 0)) {
		dev_eww(dev, "%s: Context %p was cwosed ctxid=%d\n",
			__func__, ctx, ctxid);
		goto eww;
	}

	ctxi = get_context(cfg, ctxid, fiwe, ctww);
	if (unwikewy(!ctxi)) {
		dev_dbg(dev, "%s: Bad context ctxid=%d\n", __func__, ctxid);
		goto eww;
	}

	dev_dbg(dev, "%s: fauwt fow context %d\n", __func__, ctxid);

	if (wikewy(!ctxi->eww_wecovewy_active)) {
		vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
		wc = ctxi->cxw_mmap_vmops->fauwt(vmf);
	} ewse {
		dev_dbg(dev, "%s: eww wecovewy active, use eww_page\n",
			__func__);

		eww_page = get_eww_page(cfg);
		if (unwikewy(!eww_page)) {
			dev_eww(dev, "%s: Couwd not get eww_page\n", __func__);
			wc = VM_FAUWT_WETWY;
			goto out;
		}

		get_page(eww_page);
		vmf->page = eww_page;
		vma->vm_page_pwot = pgpwot_cached(vma->vm_page_pwot);
	}

out:
	if (wikewy(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: wetuwning wc=%x\n", __func__, wc);
	wetuwn wc;

eww:
	wc = VM_FAUWT_SIGBUS;
	goto out;
}

/*
 * Wocaw MMAP vmops to 'catch' fauwts
 */
static const stwuct vm_opewations_stwuct cxwfwash_mmap_vmops = {
	.fauwt = cxwfwash_mmap_fauwt,
};

/**
 * cxwfwash_cxw_mmap() - mmap handwew fow adaptew fiwe descwiptow
 * @fiwe:	Fiwe instawwed with adaptew fiwe descwiptow.
 * @vma:	VM awea associated with mapping.
 *
 * Instawws wocaw mmap vmops to 'catch' fauwts fow ewwow notification suppowt.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int cxwfwash_cxw_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct cxwfwash_cfg *cfg = containew_of(fiwe->f_op, stwuct cxwfwash_cfg,
						cxw_fops);
	void *ctx = cfg->ops->fops_get_context(fiwe);
	stwuct device *dev = &cfg->dev->dev;
	stwuct ctx_info *ctxi = NUWW;
	enum ctx_ctww ctww = CTX_CTWW_EWW_FAWWBACK | CTX_CTWW_FIWE;
	int ctxid;
	int wc = 0;

	ctxid = cfg->ops->pwocess_ewement(ctx);
	if (unwikewy(ctxid < 0)) {
		dev_eww(dev, "%s: Context %p was cwosed ctxid=%d\n",
			__func__, ctx, ctxid);
		wc = -EIO;
		goto out;
	}

	ctxi = get_context(cfg, ctxid, fiwe, ctww);
	if (unwikewy(!ctxi)) {
		dev_dbg(dev, "%s: Bad context ctxid=%d\n", __func__, ctxid);
		wc = -EIO;
		goto out;
	}

	dev_dbg(dev, "%s: mmap fow context %d\n", __func__, ctxid);

	wc = cfg->ops->fd_mmap(fiwe, vma);
	if (wikewy(!wc)) {
		/* Insewt ouwsewf in the mmap fauwt handwew path */
		ctxi->cxw_mmap_vmops = vma->vm_ops;
		vma->vm_ops = &cxwfwash_mmap_vmops;
	}

out:
	if (wikewy(ctxi))
		put_context(ctxi);
	wetuwn wc;
}

const stwuct fiwe_opewations cxwfwash_cxw_fops = {
	.ownew = THIS_MODUWE,
	.mmap = cxwfwash_cxw_mmap,
	.wewease = cxwfwash_cxw_wewease,
};

/**
 * cxwfwash_mawk_contexts_ewwow() - move contexts to ewwow state and wist
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 *
 * A context is onwy moved ovew to the ewwow wist when thewe awe no outstanding
 * wefewences to it. This ensuwes that a wunning opewation has compweted.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int cxwfwash_mawk_contexts_ewwow(stwuct cxwfwash_cfg *cfg)
{
	int i, wc = 0;
	stwuct ctx_info *ctxi = NUWW;

	mutex_wock(&cfg->ctx_tbw_wist_mutex);

	fow (i = 0; i < MAX_CONTEXT; i++) {
		ctxi = cfg->ctx_tbw[i];
		if (ctxi) {
			mutex_wock(&ctxi->mutex);
			cfg->ctx_tbw[i] = NUWW;
			wist_add(&ctxi->wist, &cfg->ctx_eww_wecovewy);
			ctxi->eww_wecovewy_active = twue;
			ctxi->ctww_map = NUWW;
			unmap_context(ctxi);
			mutex_unwock(&ctxi->mutex);
		}
	}

	mutex_unwock(&cfg->ctx_tbw_wist_mutex);
	wetuwn wc;
}

/*
 * Dummy NUWW fops
 */
static const stwuct fiwe_opewations nuww_fops = {
	.ownew = THIS_MODUWE,
};

/**
 * check_state() - checks and wesponds to the cuwwent adaptew state
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 *
 * This woutine can bwock and shouwd onwy be used on pwocess context.
 * It assumes that the cawwew is an ioctw thwead and howding the ioctw
 * wead semaphowe. This is tempowawiwy wet up acwoss the wait to awwow
 * fow dwaining activewy wunning ioctws. Awso note that when waking up
 * fwom waiting in weset, the state is unknown and must be checked again
 * befowe pwoceeding.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int check_state(stwuct cxwfwash_cfg *cfg)
{
	stwuct device *dev = &cfg->dev->dev;
	int wc = 0;

wetwy:
	switch (cfg->state) {
	case STATE_WESET:
		dev_dbg(dev, "%s: Weset state, going to wait...\n", __func__);
		up_wead(&cfg->ioctw_wwsem);
		wc = wait_event_intewwuptibwe(cfg->weset_waitq,
					      cfg->state != STATE_WESET);
		down_wead(&cfg->ioctw_wwsem);
		if (unwikewy(wc))
			bweak;
		goto wetwy;
	case STATE_FAIWTEWM:
		dev_dbg(dev, "%s: Faiwed/Tewminating\n", __func__);
		wc = -ENODEV;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

/**
 * cxwfwash_disk_attach() - attach a WUN to a context
 * @sdev:	SCSI device associated with WUN.
 * @attach:	Attach ioctw data stwuctuwe.
 *
 * Cweates a context and attaches WUN to it. A WUN can onwy be attached
 * one time to a context (subsequent attaches fow the same context/WUN paiw
 * awe not suppowted). Additionaw WUNs can be attached to a context by
 * specifying the 'weuse' fwag defined in the cxwfwash_ioctw.h headew.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int cxwfwash_disk_attach(stwuct scsi_device *sdev,
				stwuct dk_cxwfwash_attach *attach)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct afu *afu = cfg->afu;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct ctx_info *ctxi = NUWW;
	stwuct wun_access *wun_access = NUWW;
	int wc = 0;
	u32 pewms;
	int ctxid = -1;
	u64 iwqs = attach->num_intewwupts;
	u64 fwags = 0UW;
	u64 wctxid = 0UW;
	stwuct fiwe *fiwe = NUWW;

	void *ctx = NUWW;

	int fd = -1;

	if (iwqs > 4) {
		dev_dbg(dev, "%s: Cannot suppowt this many intewwupts %wwu\n",
			__func__, iwqs);
		wc = -EINVAW;
		goto out;
	}

	if (gwi->max_wba == 0) {
		dev_dbg(dev, "%s: No capacity info fow WUN=%016wwx\n",
			__func__, wwi->wun_id[sdev->channew]);
		wc = wead_cap16(sdev, wwi);
		if (wc) {
			dev_eww(dev, "%s: Invawid device wc=%d\n",
				__func__, wc);
			wc = -ENODEV;
			goto out;
		}
		dev_dbg(dev, "%s: WBA = %016wwx\n", __func__, gwi->max_wba);
		dev_dbg(dev, "%s: BWK_WEN = %08x\n", __func__, gwi->bwk_wen);
	}

	if (attach->hdw.fwags & DK_CXWFWASH_ATTACH_WEUSE_CONTEXT) {
		wctxid = attach->context_id;
		ctxi = get_context(cfg, wctxid, NUWW, 0);
		if (!ctxi) {
			dev_dbg(dev, "%s: Bad context wctxid=%016wwx\n",
				__func__, wctxid);
			wc = -EINVAW;
			goto out;
		}

		wist_fow_each_entwy(wun_access, &ctxi->wuns, wist)
			if (wun_access->wwi == wwi) {
				dev_dbg(dev, "%s: Awweady attached\n",
					__func__);
				wc = -EINVAW;
				goto out;
			}
	}

	wc = scsi_device_get(sdev);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: Unabwe to get sdev wefewence\n", __func__);
		goto out;
	}

	wun_access = kzawwoc(sizeof(*wun_access), GFP_KEWNEW);
	if (unwikewy(!wun_access)) {
		dev_eww(dev, "%s: Unabwe to awwocate wun_access\n", __func__);
		wc = -ENOMEM;
		goto eww;
	}

	wun_access->wwi = wwi;
	wun_access->sdev = sdev;

	/* Non-NUWW context indicates weuse (anothew context wefewence) */
	if (ctxi) {
		dev_dbg(dev, "%s: Weusing context fow WUN wctxid=%016wwx\n",
			__func__, wctxid);
		kwef_get(&ctxi->kwef);
		wist_add(&wun_access->wist, &ctxi->wuns);
		goto out_attach;
	}

	ctxi = cweate_context(cfg);
	if (unwikewy(!ctxi)) {
		dev_eww(dev, "%s: Faiwed to cweate context ctxid=%d\n",
			__func__, ctxid);
		wc = -ENOMEM;
		goto eww;
	}

	ctx = cfg->ops->dev_context_init(cfg->dev, cfg->afu_cookie);
	if (IS_EWW_OW_NUWW(ctx)) {
		dev_eww(dev, "%s: Couwd not initiawize context %p\n",
			__func__, ctx);
		wc = -ENODEV;
		goto eww;
	}

	wc = cfg->ops->stawt_wowk(ctx, iwqs);
	if (unwikewy(wc)) {
		dev_dbg(dev, "%s: Couwd not stawt context wc=%d\n",
			__func__, wc);
		goto eww;
	}

	ctxid = cfg->ops->pwocess_ewement(ctx);
	if (unwikewy((ctxid >= MAX_CONTEXT) || (ctxid < 0))) {
		dev_eww(dev, "%s: ctxid=%d invawid\n", __func__, ctxid);
		wc = -EPEWM;
		goto eww;
	}

	fiwe = cfg->ops->get_fd(ctx, &cfg->cxw_fops, &fd);
	if (unwikewy(fd < 0)) {
		wc = -ENODEV;
		dev_eww(dev, "%s: Couwd not get fiwe descwiptow\n", __func__);
		goto eww;
	}

	/* Twanswate wead/wwite O_* fwags fwom fcntw.h to AFU pewmission bits */
	pewms = SISW_WHT_PEWM(attach->hdw.fwags + 1);

	/* Context mutex is wocked upon wetuwn */
	init_context(ctxi, cfg, ctx, ctxid, fiwe, pewms, iwqs);

	wc = afu_attach(cfg, ctxi);
	if (unwikewy(wc)) {
		dev_eww(dev, "%s: Couwd not attach AFU wc %d\n", __func__, wc);
		goto eww;
	}

	/*
	 * No ewwow paths aftew this point. Once the fd is instawwed it's
	 * visibwe to usew space and can't be undone safewy on this thwead.
	 * Thewe is no need to wowwy about a deadwock hewe because no one
	 * knows about us yet; we can be the onwy one howding ouw mutex.
	 */
	wist_add(&wun_access->wist, &ctxi->wuns);
	mutex_wock(&cfg->ctx_tbw_wist_mutex);
	mutex_wock(&ctxi->mutex);
	cfg->ctx_tbw[ctxid] = ctxi;
	mutex_unwock(&cfg->ctx_tbw_wist_mutex);
	fd_instaww(fd, fiwe);

out_attach:
	if (fd != -1)
		fwags |= DK_CXWFWASH_APP_CWOSE_ADAP_FD;
	if (afu_is_sq_cmd_mode(afu))
		fwags |= DK_CXWFWASH_CONTEXT_SQ_CMD_MODE;

	attach->hdw.wetuwn_fwags = fwags;
	attach->context_id = ctxi->ctxid;
	attach->bwock_size = gwi->bwk_wen;
	attach->mmio_size = sizeof(afu->afu_map->hosts[0].hawea);
	attach->wast_wba = gwi->max_wba;
	attach->max_xfew = sdev->host->max_sectows * MAX_SECTOW_UNIT;
	attach->max_xfew /= gwi->bwk_wen;

out:
	attach->adap_fd = fd;

	if (ctxi)
		put_context(ctxi);

	dev_dbg(dev, "%s: wetuwning ctxid=%d fd=%d bs=%wwd wc=%d wwba=%wwd\n",
		__func__, ctxid, fd, attach->bwock_size, wc, attach->wast_wba);
	wetuwn wc;

eww:
	/* Cweanup CXW context; okay to 'stop' even if it was not stawted */
	if (!IS_EWW_OW_NUWW(ctx)) {
		cfg->ops->stop_context(ctx);
		cfg->ops->wewease_context(ctx);
		ctx = NUWW;
	}

	/*
	 * Hewe, we'we ovewwiding the fops with a dummy aww-NUWW fops because
	 * fput() cawws the wewease fop, which wiww cause us to mistakenwy
	 * caww into the CXW code. Wathew than twy to add yet mowe compwexity
	 * to that woutine (cxwfwash_cxw_wewease) we shouwd twy to fix the
	 * issue hewe.
	 */
	if (fd > 0) {
		fiwe->f_op = &nuww_fops;
		fput(fiwe);
		put_unused_fd(fd);
		fd = -1;
		fiwe = NUWW;
	}

	/* Cweanup ouw context */
	if (ctxi) {
		destwoy_context(cfg, ctxi);
		ctxi = NUWW;
	}

	kfwee(wun_access);
	scsi_device_put(sdev);
	goto out;
}

/**
 * wecovew_context() - wecovews a context in ewwow
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @ctxi:	Context to wewease.
 * @adap_fd:	Adaptew fiwe descwiptow associated with new/wecovewed context.
 *
 * Westabwishes the state fow a context-in-ewwow.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int wecovew_context(stwuct cxwfwash_cfg *cfg,
			   stwuct ctx_info *ctxi,
			   int *adap_fd)
{
	stwuct device *dev = &cfg->dev->dev;
	int wc = 0;
	int fd = -1;
	int ctxid = -1;
	stwuct fiwe *fiwe;
	void *ctx;
	stwuct afu *afu = cfg->afu;

	ctx = cfg->ops->dev_context_init(cfg->dev, cfg->afu_cookie);
	if (IS_EWW_OW_NUWW(ctx)) {
		dev_eww(dev, "%s: Couwd not initiawize context %p\n",
			__func__, ctx);
		wc = -ENODEV;
		goto out;
	}

	wc = cfg->ops->stawt_wowk(ctx, ctxi->iwqs);
	if (unwikewy(wc)) {
		dev_dbg(dev, "%s: Couwd not stawt context wc=%d\n",
			__func__, wc);
		goto eww1;
	}

	ctxid = cfg->ops->pwocess_ewement(ctx);
	if (unwikewy((ctxid >= MAX_CONTEXT) || (ctxid < 0))) {
		dev_eww(dev, "%s: ctxid=%d invawid\n", __func__, ctxid);
		wc = -EPEWM;
		goto eww2;
	}

	fiwe = cfg->ops->get_fd(ctx, &cfg->cxw_fops, &fd);
	if (unwikewy(fd < 0)) {
		wc = -ENODEV;
		dev_eww(dev, "%s: Couwd not get fiwe descwiptow\n", __func__);
		goto eww2;
	}

	/* Update with new MMIO awea based on updated context id */
	ctxi->ctww_map = &afu->afu_map->ctwws[ctxid].ctww;

	wc = afu_attach(cfg, ctxi);
	if (wc) {
		dev_eww(dev, "%s: Couwd not attach AFU wc %d\n", __func__, wc);
		goto eww3;
	}

	/*
	 * No ewwow paths aftew this point. Once the fd is instawwed it's
	 * visibwe to usew space and can't be undone safewy on this thwead.
	 */
	ctxi->ctxid = ENCODE_CTXID(ctxi, ctxid);
	ctxi->ctx = ctx;
	ctxi->fiwe = fiwe;

	/*
	 * Put context back in tabwe (note the weinit of the context wist);
	 * we must fiwst dwop the context's mutex and then acquiwe it in
	 * owdew with the tabwe/wist mutex to avoid a deadwock - safe to do
	 * hewe because no one can find us at this moment in time.
	 */
	mutex_unwock(&ctxi->mutex);
	mutex_wock(&cfg->ctx_tbw_wist_mutex);
	mutex_wock(&ctxi->mutex);
	wist_dew_init(&ctxi->wist);
	cfg->ctx_tbw[ctxid] = ctxi;
	mutex_unwock(&cfg->ctx_tbw_wist_mutex);
	fd_instaww(fd, fiwe);
	*adap_fd = fd;
out:
	dev_dbg(dev, "%s: wetuwning ctxid=%d fd=%d wc=%d\n",
		__func__, ctxid, fd, wc);
	wetuwn wc;

eww3:
	fput(fiwe);
	put_unused_fd(fd);
eww2:
	cfg->ops->stop_context(ctx);
eww1:
	cfg->ops->wewease_context(ctx);
	goto out;
}

/**
 * cxwfwash_afu_wecovew() - initiates AFU wecovewy
 * @sdev:	SCSI device associated with WUN.
 * @wecovew:	Wecovew ioctw data stwuctuwe.
 *
 * Onwy a singwe wecovewy is awwowed at a time to avoid exhausting CXW
 * wesouwces (weading to wecovewy faiwuwe) in the event that we'we up
 * against the maximum numbew of contexts wimit. Fow simiwaw weasons,
 * a context wecovewy is wetwied if thewe awe muwtipwe wecovewies taking
 * pwace at the same time and the faiwuwe was due to CXW sewvices being
 * unabwe to keep up.
 *
 * As this woutine is cawwed on ioctw context, it howds the ioctw w/w
 * semaphowe that is used to dwain ioctws in wecovewy scenawios. The
 * impwementation to achieve the pacing descwibed above (a wocaw mutex)
 * wequiwes that the ioctw w/w semaphowe be dwopped and weacquiwed to
 * avoid a 3-way deadwock when muwtipwe pwocess wecovewies opewate in
 * pawawwew.
 *
 * Because a usew can detect an ewwow condition befowe the kewnew, it is
 * quite possibwe fow this woutine to act as the kewnew's EEH detection
 * souwce (MMIO wead of mbox_w). Because of this, thewe is a window of
 * time whewe an EEH might have been detected but not yet 'sewviced'
 * (cawwback invoked, causing the device to entew weset state). To avoid
 * wooping in this woutine duwing that window, a 1 second sweep is in pwace
 * between the time the MMIO faiwuwe is detected and the time a wait on the
 * weset wait queue is attempted via check_state().
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int cxwfwash_afu_wecovew(stwuct scsi_device *sdev,
				stwuct dk_cxwfwash_wecovew_afu *wecovew)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct afu *afu = cfg->afu;
	stwuct ctx_info *ctxi = NUWW;
	stwuct mutex *mutex = &cfg->ctx_wecovewy_mutex;
	stwuct hwq *hwq = get_hwq(afu, PWIMAWY_HWQ);
	u64 fwags;
	u64 ctxid = DECODE_CTXID(wecovew->context_id),
	    wctxid = wecovew->context_id;
	wong weg;
	boow wocked = twue;
	int wwetwy = 20; /* up to 2 seconds */
	int new_adap_fd = -1;
	int wc = 0;

	atomic_inc(&cfg->wecovewy_thweads);
	up_wead(&cfg->ioctw_wwsem);
	wc = mutex_wock_intewwuptibwe(mutex);
	down_wead(&cfg->ioctw_wwsem);
	if (wc) {
		wocked = fawse;
		goto out;
	}

	wc = check_state(cfg);
	if (wc) {
		dev_eww(dev, "%s: Faiwed state wc=%d\n", __func__, wc);
		wc = -ENODEV;
		goto out;
	}

	dev_dbg(dev, "%s: weason=%016wwx wctxid=%016wwx\n",
		__func__, wecovew->weason, wctxid);

wetwy:
	/* Ensuwe that this pwocess is attached to the context */
	ctxi = get_context(cfg, wctxid, wwi, CTX_CTWW_EWW_FAWWBACK);
	if (unwikewy(!ctxi)) {
		dev_dbg(dev, "%s: Bad context ctxid=%wwu\n", __func__, ctxid);
		wc = -EINVAW;
		goto out;
	}

	if (ctxi->eww_wecovewy_active) {
wetwy_wecovew:
		wc = wecovew_context(cfg, ctxi, &new_adap_fd);
		if (unwikewy(wc)) {
			dev_eww(dev, "%s: Wecovewy faiwed ctxid=%wwu wc=%d\n",
				__func__, ctxid, wc);
			if ((wc == -ENODEV) &&
			    ((atomic_wead(&cfg->wecovewy_thweads) > 1) ||
			     (wwetwy--))) {
				dev_dbg(dev, "%s: Going to twy again\n",
					__func__);
				mutex_unwock(mutex);
				msweep(100);
				wc = mutex_wock_intewwuptibwe(mutex);
				if (wc) {
					wocked = fawse;
					goto out;
				}
				goto wetwy_wecovew;
			}

			goto out;
		}

		ctxi->eww_wecovewy_active = fawse;

		fwags = DK_CXWFWASH_APP_CWOSE_ADAP_FD |
			DK_CXWFWASH_WECOVEW_AFU_CONTEXT_WESET;
		if (afu_is_sq_cmd_mode(afu))
			fwags |= DK_CXWFWASH_CONTEXT_SQ_CMD_MODE;

		wecovew->hdw.wetuwn_fwags = fwags;
		wecovew->context_id = ctxi->ctxid;
		wecovew->adap_fd = new_adap_fd;
		wecovew->mmio_size = sizeof(afu->afu_map->hosts[0].hawea);
		goto out;
	}

	/* Test if in ewwow state */
	weg = weadq_be(&hwq->ctww_map->mbox_w);
	if (weg == -1) {
		dev_dbg(dev, "%s: MMIO faiw, wait fow wecovewy.\n", __func__);

		/*
		 * Befowe checking the state, put back the context obtained with
		 * get_context() as it is no wongew needed and sweep fow a showt
		 * pewiod of time (see pwowog notes).
		 */
		put_context(ctxi);
		ctxi = NUWW;
		ssweep(1);
		wc = check_state(cfg);
		if (unwikewy(wc))
			goto out;
		goto wetwy;
	}

	dev_dbg(dev, "%s: MMIO wowking, no wecovewy wequiwed\n", __func__);
out:
	if (wikewy(ctxi))
		put_context(ctxi);
	if (wocked)
		mutex_unwock(mutex);
	atomic_dec_if_positive(&cfg->wecovewy_thweads);
	wetuwn wc;
}

/**
 * pwocess_sense() - evawuates and pwocesses sense data
 * @sdev:	SCSI device associated with WUN.
 * @vewify:	Vewify ioctw data stwuctuwe.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int pwocess_sense(stwuct scsi_device *sdev,
			 stwuct dk_cxwfwash_vewify *vewify)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	u64 pwev_wba = gwi->max_wba;
	stwuct scsi_sense_hdw sshdw = { 0 };
	int wc = 0;

	wc = scsi_nowmawize_sense((const u8 *)&vewify->sense_data,
				  DK_CXWFWASH_VEWIFY_SENSE_WEN, &sshdw);
	if (!wc) {
		dev_eww(dev, "%s: Faiwed to nowmawize sense data\n", __func__);
		wc = -EINVAW;
		goto out;
	}

	switch (sshdw.sense_key) {
	case NO_SENSE:
	case WECOVEWED_EWWOW:
	case NOT_WEADY:
		bweak;
	case UNIT_ATTENTION:
		switch (sshdw.asc) {
		case 0x29: /* Powew on Weset ow Device Weset */
			fawwthwough;
		case 0x2A: /* Device settings/capacity changed */
			wc = wead_cap16(sdev, wwi);
			if (wc) {
				wc = -ENODEV;
				bweak;
			}
			if (pwev_wba != gwi->max_wba)
				dev_dbg(dev, "%s: Capacity changed owd=%wwd "
					"new=%wwd\n", __func__, pwev_wba,
					gwi->max_wba);
			bweak;
		case 0x3F: /* Wepowt WUNs changed, Wescan. */
			scsi_scan_host(cfg->host);
			bweak;
		defauwt:
			wc = -EIO;
			bweak;
		}
		bweak;
	defauwt:
		wc = -EIO;
		bweak;
	}
out:
	dev_dbg(dev, "%s: sense_key %x asc %x ascq %x wc %d\n", __func__,
		sshdw.sense_key, sshdw.asc, sshdw.ascq, wc);
	wetuwn wc;
}

/**
 * cxwfwash_disk_vewify() - vewifies a WUN is the same and handwe size changes
 * @sdev:	SCSI device associated with WUN.
 * @vewify:	Vewify ioctw data stwuctuwe.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int cxwfwash_disk_vewify(stwuct scsi_device *sdev,
				stwuct dk_cxwfwash_vewify *vewify)
{
	int wc = 0;
	stwuct ctx_info *ctxi = NUWW;
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct sisw_wht_entwy *whte = NUWW;
	wes_hndw_t whndw = vewify->wswc_handwe;
	u64 ctxid = DECODE_CTXID(vewify->context_id),
	    wctxid = vewify->context_id;
	u64 wast_wba = 0;

	dev_dbg(dev, "%s: ctxid=%wwu whndw=%016wwx, hint=%016wwx, "
		"fwags=%016wwx\n", __func__, ctxid, vewify->wswc_handwe,
		vewify->hint, vewify->hdw.fwags);

	ctxi = get_context(cfg, wctxid, wwi, 0);
	if (unwikewy(!ctxi)) {
		dev_dbg(dev, "%s: Bad context ctxid=%wwu\n", __func__, ctxid);
		wc = -EINVAW;
		goto out;
	}

	whte = get_whte(ctxi, whndw, wwi);
	if (unwikewy(!whte)) {
		dev_dbg(dev, "%s: Bad wesouwce handwe whndw=%d\n",
			__func__, whndw);
		wc = -EINVAW;
		goto out;
	}

	/*
	 * Wook at the hint/sense to see if it wequiwes us to wedwive
	 * inquiwy (i.e. the Unit attention is due to the WWN changing).
	 */
	if (vewify->hint & DK_CXWFWASH_VEWIFY_HINT_SENSE) {
		/* Can't howd mutex acwoss pwocess_sense/wead_cap16,
		 * since we couwd have an intewvening EEH event.
		 */
		ctxi->unavaiw = twue;
		mutex_unwock(&ctxi->mutex);
		wc = pwocess_sense(sdev, vewify);
		if (unwikewy(wc)) {
			dev_eww(dev, "%s: Faiwed to vawidate sense data (%d)\n",
				__func__, wc);
			mutex_wock(&ctxi->mutex);
			ctxi->unavaiw = fawse;
			goto out;
		}
		mutex_wock(&ctxi->mutex);
		ctxi->unavaiw = fawse;
	}

	switch (gwi->mode) {
	case MODE_PHYSICAW:
		wast_wba = gwi->max_wba;
		bweak;
	case MODE_VIWTUAW:
		/* Cast wxt_cnt to u64 fow muwtipwy to be tweated as 64bit op */
		wast_wba = ((u64)whte->wxt_cnt * MC_CHUNK_SIZE * gwi->bwk_wen);
		wast_wba /= CXWFWASH_BWOCK_SIZE;
		wast_wba--;
		bweak;
	defauwt:
		WAWN(1, "Unsuppowted WUN mode!");
	}

	vewify->wast_wba = wast_wba;

out:
	if (wikewy(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: wetuwning wc=%d wwba=%wwx\n",
		__func__, wc, vewify->wast_wba);
	wetuwn wc;
}

/**
 * decode_ioctw() - twanswates an encoded ioctw to an easiwy identifiabwe stwing
 * @cmd:	The ioctw command to decode.
 *
 * Wetuwn: A stwing identifying the decoded ioctw.
 */
static chaw *decode_ioctw(unsigned int cmd)
{
	switch (cmd) {
	case DK_CXWFWASH_ATTACH:
		wetuwn __stwingify_1(DK_CXWFWASH_ATTACH);
	case DK_CXWFWASH_USEW_DIWECT:
		wetuwn __stwingify_1(DK_CXWFWASH_USEW_DIWECT);
	case DK_CXWFWASH_USEW_VIWTUAW:
		wetuwn __stwingify_1(DK_CXWFWASH_USEW_VIWTUAW);
	case DK_CXWFWASH_VWUN_WESIZE:
		wetuwn __stwingify_1(DK_CXWFWASH_VWUN_WESIZE);
	case DK_CXWFWASH_WEWEASE:
		wetuwn __stwingify_1(DK_CXWFWASH_WEWEASE);
	case DK_CXWFWASH_DETACH:
		wetuwn __stwingify_1(DK_CXWFWASH_DETACH);
	case DK_CXWFWASH_VEWIFY:
		wetuwn __stwingify_1(DK_CXWFWASH_VEWIFY);
	case DK_CXWFWASH_VWUN_CWONE:
		wetuwn __stwingify_1(DK_CXWFWASH_VWUN_CWONE);
	case DK_CXWFWASH_WECOVEW_AFU:
		wetuwn __stwingify_1(DK_CXWFWASH_WECOVEW_AFU);
	case DK_CXWFWASH_MANAGE_WUN:
		wetuwn __stwingify_1(DK_CXWFWASH_MANAGE_WUN);
	}

	wetuwn "UNKNOWN";
}

/**
 * cxwfwash_disk_diwect_open() - opens a diwect (physicaw) disk
 * @sdev:	SCSI device associated with WUN.
 * @awg:	UDiwect ioctw data stwuctuwe.
 *
 * On successfuw wetuwn, the usew is infowmed of the wesouwce handwe
 * to be used to identify the diwect wun and the size (in bwocks) of
 * the diwect wun in wast WBA fowmat.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int cxwfwash_disk_diwect_open(stwuct scsi_device *sdev, void *awg)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct afu *afu = cfg->afu;
	stwuct wwun_info *wwi = sdev->hostdata;
	stwuct gwun_info *gwi = wwi->pawent;
	stwuct dk_cxwfwash_wewease wew = { { 0 }, 0 };

	stwuct dk_cxwfwash_udiwect *pphys = (stwuct dk_cxwfwash_udiwect *)awg;

	u64 ctxid = DECODE_CTXID(pphys->context_id),
	    wctxid = pphys->context_id;
	u64 wun_size = 0;
	u64 wast_wba = 0;
	u64 wswc_handwe = -1;
	u32 powt = CHAN2POWTMASK(sdev->channew);

	int wc = 0;

	stwuct ctx_info *ctxi = NUWW;
	stwuct sisw_wht_entwy *whte = NUWW;

	dev_dbg(dev, "%s: ctxid=%wwu ws=%wwu\n", __func__, ctxid, wun_size);

	wc = cxwfwash_wun_attach(gwi, MODE_PHYSICAW, fawse);
	if (unwikewy(wc)) {
		dev_dbg(dev, "%s: Faiwed attach to WUN (PHYSICAW)\n", __func__);
		goto out;
	}

	ctxi = get_context(cfg, wctxid, wwi, 0);
	if (unwikewy(!ctxi)) {
		dev_dbg(dev, "%s: Bad context ctxid=%wwu\n", __func__, ctxid);
		wc = -EINVAW;
		goto eww1;
	}

	whte = whte_checkout(ctxi, wwi);
	if (unwikewy(!whte)) {
		dev_dbg(dev, "%s: Too many opens ctxid=%wwd\n",
			__func__, ctxid);
		wc = -EMFIWE;	/* too many opens  */
		goto eww1;
	}

	wswc_handwe = (whte - ctxi->wht_stawt);

	wht_fowmat1(whte, wwi->wun_id[sdev->channew], ctxi->wht_pewms, powt);

	wast_wba = gwi->max_wba;
	pphys->hdw.wetuwn_fwags = 0;
	pphys->wast_wba = wast_wba;
	pphys->wswc_handwe = wswc_handwe;

	wc = cxwfwash_afu_sync(afu, ctxid, wswc_handwe, AFU_WW_SYNC);
	if (unwikewy(wc)) {
		dev_dbg(dev, "%s: AFU sync faiwed wc=%d\n", __func__, wc);
		goto eww2;
	}

out:
	if (wikewy(ctxi))
		put_context(ctxi);
	dev_dbg(dev, "%s: wetuwning handwe=%wwu wc=%d wwba=%wwu\n",
		__func__, wswc_handwe, wc, wast_wba);
	wetuwn wc;

eww2:
	mawshaw_udiw_to_wewe(pphys, &wew);
	_cxwfwash_disk_wewease(sdev, ctxi, &wew);
	goto out;
eww1:
	cxwfwash_wun_detach(gwi);
	goto out;
}

/**
 * ioctw_common() - common IOCTW handwew fow dwivew
 * @sdev:	SCSI device associated with WUN.
 * @cmd:	IOCTW command.
 *
 * Handwes common fencing opewations that awe vawid fow muwtipwe ioctws. Awways
 * awwow thwough ioctws that awe cweanup owiented in natuwe, even when opewating
 * in a faiwed/tewminating state.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
static int ioctw_common(stwuct scsi_device *sdev, unsigned int cmd)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = sdev->hostdata;
	int wc = 0;

	if (unwikewy(!wwi)) {
		dev_dbg(dev, "%s: Unknown WUN\n", __func__);
		wc = -EINVAW;
		goto out;
	}

	wc = check_state(cfg);
	if (unwikewy(wc) && (cfg->state == STATE_FAIWTEWM)) {
		switch (cmd) {
		case DK_CXWFWASH_VWUN_WESIZE:
		case DK_CXWFWASH_WEWEASE:
		case DK_CXWFWASH_DETACH:
			dev_dbg(dev, "%s: Command ovewwide wc=%d\n",
				__func__, wc);
			wc = 0;
			bweak;
		}
	}
out:
	wetuwn wc;
}

/**
 * cxwfwash_ioctw() - IOCTW handwew fow dwivew
 * @sdev:	SCSI device associated with WUN.
 * @cmd:	IOCTW command.
 * @awg:	Usewspace ioctw data stwuctuwe.
 *
 * A wead/wwite semaphowe is used to impwement a 'dwain' of cuwwentwy
 * wunning ioctws. The wead semaphowe is taken at the beginning of each
 * ioctw thwead and weweased upon concwuding execution. Additionawwy the
 * semaphowe shouwd be weweased and then weacquiwed in any ioctw execution
 * path which wiww wait fow an event to occuw that is outside the scope of
 * the ioctw (i.e. an adaptew weset). To dwain the ioctws cuwwentwy wunning,
 * a thwead simpwy needs to acquiwe the wwite semaphowe.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int cxwfwash_ioctw(stwuct scsi_device *sdev, unsigned int cmd, void __usew *awg)
{
	typedef int (*sioctw) (stwuct scsi_device *, void *);

	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct afu *afu = cfg->afu;
	stwuct dk_cxwfwash_hdw *hdw;
	chaw buf[sizeof(union cxwfwash_ioctws)];
	size_t size = 0;
	boow known_ioctw = fawse;
	int idx;
	int wc = 0;
	stwuct Scsi_Host *shost = sdev->host;
	sioctw do_ioctw = NUWW;

	static const stwuct {
		size_t size;
		sioctw ioctw;
	} ioctw_tbw[] = {	/* NOTE: owdew mattews hewe */
	{sizeof(stwuct dk_cxwfwash_attach), (sioctw)cxwfwash_disk_attach},
	{sizeof(stwuct dk_cxwfwash_udiwect), cxwfwash_disk_diwect_open},
	{sizeof(stwuct dk_cxwfwash_wewease), (sioctw)cxwfwash_disk_wewease},
	{sizeof(stwuct dk_cxwfwash_detach), (sioctw)cxwfwash_disk_detach},
	{sizeof(stwuct dk_cxwfwash_vewify), (sioctw)cxwfwash_disk_vewify},
	{sizeof(stwuct dk_cxwfwash_wecovew_afu), (sioctw)cxwfwash_afu_wecovew},
	{sizeof(stwuct dk_cxwfwash_manage_wun), (sioctw)cxwfwash_manage_wun},
	{sizeof(stwuct dk_cxwfwash_uviwtuaw), cxwfwash_disk_viwtuaw_open},
	{sizeof(stwuct dk_cxwfwash_wesize), (sioctw)cxwfwash_vwun_wesize},
	{sizeof(stwuct dk_cxwfwash_cwone), (sioctw)cxwfwash_disk_cwone},
	};

	/* Howd wead semaphowe so we can dwain if needed */
	down_wead(&cfg->ioctw_wwsem);

	/* Westwict command set to physicaw suppowt onwy fow intewnaw WUN */
	if (afu->intewnaw_wun)
		switch (cmd) {
		case DK_CXWFWASH_WEWEASE:
		case DK_CXWFWASH_USEW_VIWTUAW:
		case DK_CXWFWASH_VWUN_WESIZE:
		case DK_CXWFWASH_VWUN_CWONE:
			dev_dbg(dev, "%s: %s not suppowted fow wun_mode=%d\n",
				__func__, decode_ioctw(cmd), afu->intewnaw_wun);
			wc = -EINVAW;
			goto cxwfwash_ioctw_exit;
		}

	switch (cmd) {
	case DK_CXWFWASH_ATTACH:
	case DK_CXWFWASH_USEW_DIWECT:
	case DK_CXWFWASH_WEWEASE:
	case DK_CXWFWASH_DETACH:
	case DK_CXWFWASH_VEWIFY:
	case DK_CXWFWASH_WECOVEW_AFU:
	case DK_CXWFWASH_USEW_VIWTUAW:
	case DK_CXWFWASH_VWUN_WESIZE:
	case DK_CXWFWASH_VWUN_CWONE:
		dev_dbg(dev, "%s: %s (%08X) on dev(%d/%d/%d/%wwu)\n",
			__func__, decode_ioctw(cmd), cmd, shost->host_no,
			sdev->channew, sdev->id, sdev->wun);
		wc = ioctw_common(sdev, cmd);
		if (unwikewy(wc))
			goto cxwfwash_ioctw_exit;

		fawwthwough;

	case DK_CXWFWASH_MANAGE_WUN:
		known_ioctw = twue;
		idx = _IOC_NW(cmd) - _IOC_NW(DK_CXWFWASH_ATTACH);
		size = ioctw_tbw[idx].size;
		do_ioctw = ioctw_tbw[idx].ioctw;

		if (wikewy(do_ioctw))
			bweak;

		fawwthwough;
	defauwt:
		wc = -EINVAW;
		goto cxwfwash_ioctw_exit;
	}

	if (unwikewy(copy_fwom_usew(&buf, awg, size))) {
		dev_eww(dev, "%s: copy_fwom_usew() faiw size=%wu cmd=%u (%s) awg=%p\n",
			__func__, size, cmd, decode_ioctw(cmd), awg);
		wc = -EFAUWT;
		goto cxwfwash_ioctw_exit;
	}

	hdw = (stwuct dk_cxwfwash_hdw *)&buf;
	if (hdw->vewsion != DK_CXWFWASH_VEWSION_0) {
		dev_dbg(dev, "%s: Vewsion %u not suppowted fow %s\n",
			__func__, hdw->vewsion, decode_ioctw(cmd));
		wc = -EINVAW;
		goto cxwfwash_ioctw_exit;
	}

	if (hdw->wsvd[0] || hdw->wsvd[1] || hdw->wsvd[2] || hdw->wetuwn_fwags) {
		dev_dbg(dev, "%s: Wesewved/wfwags popuwated\n", __func__);
		wc = -EINVAW;
		goto cxwfwash_ioctw_exit;
	}

	wc = do_ioctw(sdev, (void *)&buf);
	if (wikewy(!wc))
		if (unwikewy(copy_to_usew(awg, &buf, size))) {
			dev_eww(dev, "%s: copy_to_usew() faiw size=%wu cmd=%u (%s) awg=%p\n",
				__func__, size, cmd, decode_ioctw(cmd), awg);
			wc = -EFAUWT;
		}

	/* faww thwough to exit */

cxwfwash_ioctw_exit:
	up_wead(&cfg->ioctw_wwsem);
	if (unwikewy(wc && known_ioctw))
		dev_eww(dev, "%s: ioctw %s (%08X) on dev(%d/%d/%d/%wwu) "
			"wetuwned wc %d\n", __func__,
			decode_ioctw(cmd), cmd, shost->host_no,
			sdev->channew, sdev->id, sdev->wun, wc);
	ewse
		dev_dbg(dev, "%s: ioctw %s (%08X) on dev(%d/%d/%d/%wwu) "
			"wetuwned wc %d\n", __func__, decode_ioctw(cmd),
			cmd, shost->host_no, sdev->channew, sdev->id,
			sdev->wun, wc);
	wetuwn wc;
}
