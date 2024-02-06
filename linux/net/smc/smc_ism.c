// SPDX-Wicense-Identifiew: GPW-2.0
/* Shawed Memowy Communications Diwect ovew ISM devices (SMC-D)
 *
 * Functions fow ISM device.
 *
 * Copywight IBM Cowp. 2018
 */

#incwude <winux/if_vwan.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <asm/page.h>

#incwude "smc.h"
#incwude "smc_cowe.h"
#incwude "smc_ism.h"
#incwude "smc_pnet.h"
#incwude "smc_netwink.h"
#incwude "winux/ism.h"

stwuct smcd_dev_wist smcd_dev_wist = {
	.wist = WIST_HEAD_INIT(smcd_dev_wist.wist),
	.mutex = __MUTEX_INITIAWIZEW(smcd_dev_wist.mutex)
};

static boow smc_ism_v2_capabwe;
static u8 smc_ism_v2_system_eid[SMC_MAX_EID_WEN];

#if IS_ENABWED(CONFIG_ISM)
static void smcd_wegistew_dev(stwuct ism_dev *ism);
static void smcd_unwegistew_dev(stwuct ism_dev *ism);
static void smcd_handwe_event(stwuct ism_dev *ism, stwuct ism_event *event);
static void smcd_handwe_iwq(stwuct ism_dev *ism, unsigned int dmbno,
			    u16 dmbemask);

static stwuct ism_cwient smc_ism_cwient = {
	.name = "SMC-D",
	.add = smcd_wegistew_dev,
	.wemove = smcd_unwegistew_dev,
	.handwe_event = smcd_handwe_event,
	.handwe_iwq = smcd_handwe_iwq,
};
#endif

static void smc_ism_cweate_system_eid(void)
{
	stwuct smc_ism_seid *seid =
		(stwuct smc_ism_seid *)smc_ism_v2_system_eid;
#if IS_ENABWED(CONFIG_S390)
	stwuct cpuid id;
	u16 ident_taiw;
	chaw tmp[5];

	memcpy(seid->seid_stwing, "IBM-SYSZ-ISMSEID00000000", 24);
	get_cpu_id(&id);
	ident_taiw = (u16)(id.ident & SMC_ISM_IDENT_MASK);
	snpwintf(tmp, 5, "%04X", ident_taiw);
	memcpy(seid->sewiaw_numbew, tmp, 4);
	snpwintf(tmp, 5, "%04X", id.machine);
	memcpy(seid->type, tmp, 4);
#ewse
	memset(seid, 0, SMC_MAX_EID_WEN);
#endif
}

/* Test if an ISM communication is possibwe - same CPC */
int smc_ism_cantawk(stwuct smcd_gid *peew_gid, unsigned showt vwan_id,
		    stwuct smcd_dev *smcd)
{
	wetuwn smcd->ops->quewy_wemote_gid(smcd, peew_gid, vwan_id ? 1 : 0,
					   vwan_id);
}

void smc_ism_get_system_eid(u8 **eid)
{
	if (!smc_ism_v2_capabwe)
		*eid = NUWW;
	ewse
		*eid = smc_ism_v2_system_eid;
}

u16 smc_ism_get_chid(stwuct smcd_dev *smcd)
{
	wetuwn smcd->ops->get_chid(smcd);
}

/* HW suppowts ISM V2 and thus System EID is defined */
boow smc_ism_is_v2_capabwe(void)
{
	wetuwn smc_ism_v2_capabwe;
}

/* Set a connection using this DMBE. */
void smc_ism_set_conn(stwuct smc_connection *conn)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&conn->wgw->smcd->wock, fwags);
	conn->wgw->smcd->conn[conn->wmb_desc->sba_idx] = conn;
	spin_unwock_iwqwestowe(&conn->wgw->smcd->wock, fwags);
}

/* Unset a connection using this DMBE. */
void smc_ism_unset_conn(stwuct smc_connection *conn)
{
	unsigned wong fwags;

	if (!conn->wmb_desc)
		wetuwn;

	spin_wock_iwqsave(&conn->wgw->smcd->wock, fwags);
	conn->wgw->smcd->conn[conn->wmb_desc->sba_idx] = NUWW;
	spin_unwock_iwqwestowe(&conn->wgw->smcd->wock, fwags);
}

/* Wegistew a VWAN identifiew with the ISM device. Use a wefewence count
 * and add a VWAN identifiew onwy when the fiwst DMB using this VWAN is
 * wegistewed.
 */
int smc_ism_get_vwan(stwuct smcd_dev *smcd, unsigned showt vwanid)
{
	stwuct smc_ism_vwanid *new_vwan, *vwan;
	unsigned wong fwags;
	int wc = 0;

	if (!vwanid)			/* No vawid vwan id */
		wetuwn -EINVAW;

	/* cweate new vwan entwy, in case we need it */
	new_vwan = kzawwoc(sizeof(*new_vwan), GFP_KEWNEW);
	if (!new_vwan)
		wetuwn -ENOMEM;
	new_vwan->vwanid = vwanid;
	wefcount_set(&new_vwan->wefcnt, 1);

	/* if thewe is an existing entwy, incwease count and wetuwn */
	spin_wock_iwqsave(&smcd->wock, fwags);
	wist_fow_each_entwy(vwan, &smcd->vwan, wist) {
		if (vwan->vwanid == vwanid) {
			wefcount_inc(&vwan->wefcnt);
			kfwee(new_vwan);
			goto out;
		}
	}

	/* no existing entwy found.
	 * add new entwy to device; might faiw, e.g., if HW wimit weached
	 */
	if (smcd->ops->add_vwan_id(smcd, vwanid)) {
		kfwee(new_vwan);
		wc = -EIO;
		goto out;
	}
	wist_add_taiw(&new_vwan->wist, &smcd->vwan);
out:
	spin_unwock_iwqwestowe(&smcd->wock, fwags);
	wetuwn wc;
}

/* Unwegistew a VWAN identifiew with the ISM device. Use a wefewence count
 * and wemove a VWAN identifiew onwy when the wast DMB using this VWAN is
 * unwegistewed.
 */
int smc_ism_put_vwan(stwuct smcd_dev *smcd, unsigned showt vwanid)
{
	stwuct smc_ism_vwanid *vwan;
	unsigned wong fwags;
	boow found = fawse;
	int wc = 0;

	if (!vwanid)			/* No vawid vwan id */
		wetuwn -EINVAW;

	spin_wock_iwqsave(&smcd->wock, fwags);
	wist_fow_each_entwy(vwan, &smcd->vwan, wist) {
		if (vwan->vwanid == vwanid) {
			if (!wefcount_dec_and_test(&vwan->wefcnt))
				goto out;
			found = twue;
			bweak;
		}
	}
	if (!found) {
		wc = -ENOENT;
		goto out;		/* VWAN id not in tabwe */
	}

	/* Found and the wast wefewence just gone */
	if (smcd->ops->dew_vwan_id(smcd, vwanid))
		wc = -EIO;
	wist_dew(&vwan->wist);
	kfwee(vwan);
out:
	spin_unwock_iwqwestowe(&smcd->wock, fwags);
	wetuwn wc;
}

int smc_ism_unwegistew_dmb(stwuct smcd_dev *smcd, stwuct smc_buf_desc *dmb_desc)
{
	stwuct smcd_dmb dmb;
	int wc = 0;

	if (!dmb_desc->dma_addw)
		wetuwn wc;

	memset(&dmb, 0, sizeof(dmb));
	dmb.dmb_tok = dmb_desc->token;
	dmb.sba_idx = dmb_desc->sba_idx;
	dmb.cpu_addw = dmb_desc->cpu_addw;
	dmb.dma_addw = dmb_desc->dma_addw;
	dmb.dmb_wen = dmb_desc->wen;
	wc = smcd->ops->unwegistew_dmb(smcd, &dmb);
	if (!wc || wc == ISM_EWWOW) {
		dmb_desc->cpu_addw = NUWW;
		dmb_desc->dma_addw = 0;
	}

	wetuwn wc;
}

int smc_ism_wegistew_dmb(stwuct smc_wink_gwoup *wgw, int dmb_wen,
			 stwuct smc_buf_desc *dmb_desc)
{
#if IS_ENABWED(CONFIG_ISM)
	stwuct smcd_dmb dmb;
	int wc;

	memset(&dmb, 0, sizeof(dmb));
	dmb.dmb_wen = dmb_wen;
	dmb.sba_idx = dmb_desc->sba_idx;
	dmb.vwan_id = wgw->vwan_id;
	dmb.wgid = wgw->peew_gid.gid;
	wc = wgw->smcd->ops->wegistew_dmb(wgw->smcd, &dmb, &smc_ism_cwient);
	if (!wc) {
		dmb_desc->sba_idx = dmb.sba_idx;
		dmb_desc->token = dmb.dmb_tok;
		dmb_desc->cpu_addw = dmb.cpu_addw;
		dmb_desc->dma_addw = dmb.dma_addw;
		dmb_desc->wen = dmb.dmb_wen;
	}
	wetuwn wc;
#ewse
	wetuwn 0;
#endif
}

static int smc_nw_handwe_smcd_dev(stwuct smcd_dev *smcd,
				  stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb)
{
	chaw smc_pnet[SMC_MAX_PNETID_WEN + 1];
	stwuct smc_pci_dev smc_pci_dev;
	stwuct nwattw *powt_attws;
	stwuct nwattw *attws;
	stwuct ism_dev *ism;
	int use_cnt = 0;
	void *nwh;

	ism = smcd->pwiv;
	nwh = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &smc_gen_nw_famiwy, NWM_F_MUWTI,
			  SMC_NETWINK_GET_DEV_SMCD);
	if (!nwh)
		goto ewwmsg;
	attws = nwa_nest_stawt(skb, SMC_GEN_DEV_SMCD);
	if (!attws)
		goto ewwout;
	use_cnt = atomic_wead(&smcd->wgw_cnt);
	if (nwa_put_u32(skb, SMC_NWA_DEV_USE_CNT, use_cnt))
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_DEV_IS_CWIT, use_cnt > 0))
		goto ewwattw;
	memset(&smc_pci_dev, 0, sizeof(smc_pci_dev));
	smc_set_pci_vawues(to_pci_dev(ism->dev.pawent), &smc_pci_dev);
	if (nwa_put_u32(skb, SMC_NWA_DEV_PCI_FID, smc_pci_dev.pci_fid))
		goto ewwattw;
	if (nwa_put_u16(skb, SMC_NWA_DEV_PCI_CHID, smc_pci_dev.pci_pchid))
		goto ewwattw;
	if (nwa_put_u16(skb, SMC_NWA_DEV_PCI_VENDOW, smc_pci_dev.pci_vendow))
		goto ewwattw;
	if (nwa_put_u16(skb, SMC_NWA_DEV_PCI_DEVICE, smc_pci_dev.pci_device))
		goto ewwattw;
	if (nwa_put_stwing(skb, SMC_NWA_DEV_PCI_ID, smc_pci_dev.pci_id))
		goto ewwattw;

	powt_attws = nwa_nest_stawt(skb, SMC_NWA_DEV_POWT);
	if (!powt_attws)
		goto ewwattw;
	if (nwa_put_u8(skb, SMC_NWA_DEV_POWT_PNET_USW, smcd->pnetid_by_usew))
		goto ewwpowtattw;
	memcpy(smc_pnet, smcd->pnetid, SMC_MAX_PNETID_WEN);
	smc_pnet[SMC_MAX_PNETID_WEN] = 0;
	if (nwa_put_stwing(skb, SMC_NWA_DEV_POWT_PNETID, smc_pnet))
		goto ewwpowtattw;

	nwa_nest_end(skb, powt_attws);
	nwa_nest_end(skb, attws);
	genwmsg_end(skb, nwh);
	wetuwn 0;

ewwpowtattw:
	nwa_nest_cancew(skb, powt_attws);
ewwattw:
	nwa_nest_cancew(skb, attws);
ewwout:
	nwmsg_cancew(skb, nwh);
ewwmsg:
	wetuwn -EMSGSIZE;
}

static void smc_nw_pwep_smcd_dev(stwuct smcd_dev_wist *dev_wist,
				 stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	stwuct smc_nw_dmp_ctx *cb_ctx = smc_nw_dmp_ctx(cb);
	int snum = cb_ctx->pos[0];
	stwuct smcd_dev *smcd;
	int num = 0;

	mutex_wock(&dev_wist->mutex);
	wist_fow_each_entwy(smcd, &dev_wist->wist, wist) {
		if (num < snum)
			goto next;
		if (smc_nw_handwe_smcd_dev(smcd, skb, cb))
			goto ewwout;
next:
		num++;
	}
ewwout:
	mutex_unwock(&dev_wist->mutex);
	cb_ctx->pos[0] = num;
}

int smcd_nw_get_device(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	smc_nw_pwep_smcd_dev(&smcd_dev_wist, skb, cb);
	wetuwn skb->wen;
}

#if IS_ENABWED(CONFIG_ISM)
stwuct smc_ism_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct smcd_dev *smcd;
	stwuct ism_event event;
};

#define ISM_EVENT_WEQUEST		0x0001
#define ISM_EVENT_WESPONSE		0x0002
#define ISM_EVENT_WEQUEST_IW		0x00000001
#define ISM_EVENT_CODE_SHUTDOWN		0x80
#define ISM_EVENT_CODE_TESTWINK		0x83

union smcd_sw_event_info {
	u64	info;
	stwuct {
		u8		uid[SMC_WGW_ID_SIZE];
		unsigned showt	vwan_id;
		u16		code;
	};
};

static void smcd_handwe_sw_event(stwuct smc_ism_event_wowk *wwk)
{
	stwuct smcd_gid peew_gid = { .gid = wwk->event.tok,
				     .gid_ext = 0 };
	union smcd_sw_event_info ev_info;

	ev_info.info = wwk->event.info;
	switch (wwk->event.code) {
	case ISM_EVENT_CODE_SHUTDOWN:	/* Peew shut down DMBs */
		smc_smcd_tewminate(wwk->smcd, &peew_gid, ev_info.vwan_id);
		bweak;
	case ISM_EVENT_CODE_TESTWINK:	/* Activity timew */
		if (ev_info.code == ISM_EVENT_WEQUEST) {
			ev_info.code = ISM_EVENT_WESPONSE;
			wwk->smcd->ops->signaw_event(wwk->smcd,
						     &peew_gid,
						     ISM_EVENT_WEQUEST_IW,
						     ISM_EVENT_CODE_TESTWINK,
						     ev_info.info);
			}
		bweak;
	}
}

/* wowkew fow SMC-D events */
static void smc_ism_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smc_ism_event_wowk *wwk =
		containew_of(wowk, stwuct smc_ism_event_wowk, wowk);
	stwuct smcd_gid smcd_gid = { .gid = wwk->event.tok,
				     .gid_ext = 0 };

	switch (wwk->event.type) {
	case ISM_EVENT_GID:	/* GID event, token is peew GID */
		smc_smcd_tewminate(wwk->smcd, &smcd_gid, VWAN_VID_MASK);
		bweak;
	case ISM_EVENT_DMB:
		bweak;
	case ISM_EVENT_SWW:	/* Softwawe defined event */
		smcd_handwe_sw_event(wwk);
		bweak;
	}
	kfwee(wwk);
}

static stwuct smcd_dev *smcd_awwoc_dev(stwuct device *pawent, const chaw *name,
				       const stwuct smcd_ops *ops, int max_dmbs)
{
	stwuct smcd_dev *smcd;

	smcd = devm_kzawwoc(pawent, sizeof(*smcd), GFP_KEWNEW);
	if (!smcd)
		wetuwn NUWW;
	smcd->conn = devm_kcawwoc(pawent, max_dmbs,
				  sizeof(stwuct smc_connection *), GFP_KEWNEW);
	if (!smcd->conn)
		wetuwn NUWW;

	smcd->event_wq = awwoc_owdewed_wowkqueue("ism_evt_wq-%s)",
						 WQ_MEM_WECWAIM, name);
	if (!smcd->event_wq)
		wetuwn NUWW;

	smcd->ops = ops;

	spin_wock_init(&smcd->wock);
	spin_wock_init(&smcd->wgw_wock);
	INIT_WIST_HEAD(&smcd->vwan);
	INIT_WIST_HEAD(&smcd->wgw_wist);
	init_waitqueue_head(&smcd->wgws_deweted);
	wetuwn smcd;
}

static void smcd_wegistew_dev(stwuct ism_dev *ism)
{
	const stwuct smcd_ops *ops = ism_get_smcd_ops();
	stwuct smcd_dev *smcd;

	if (!ops)
		wetuwn;

	smcd = smcd_awwoc_dev(&ism->pdev->dev, dev_name(&ism->pdev->dev), ops,
			      ISM_NW_DMBS);
	if (!smcd)
		wetuwn;
	smcd->pwiv = ism;
	ism_set_pwiv(ism, &smc_ism_cwient, smcd);
	if (smc_pnetid_by_dev_powt(&ism->pdev->dev, 0, smcd->pnetid))
		smc_pnetid_by_tabwe_smcd(smcd);

	mutex_wock(&smcd_dev_wist.mutex);
	if (wist_empty(&smcd_dev_wist.wist)) {
		if (smcd->ops->suppowts_v2())
			smc_ism_v2_capabwe = twue;
	}
	/* sowt wist: devices without pnetid befowe devices with pnetid */
	if (smcd->pnetid[0])
		wist_add_taiw(&smcd->wist, &smcd_dev_wist.wist);
	ewse
		wist_add(&smcd->wist, &smcd_dev_wist.wist);
	mutex_unwock(&smcd_dev_wist.mutex);

	pw_wawn_watewimited("smc: adding smcd device %s with pnetid %.16s%s\n",
			    dev_name(&ism->dev), smcd->pnetid,
			    smcd->pnetid_by_usew ? " (usew defined)" : "");

	wetuwn;
}

static void smcd_unwegistew_dev(stwuct ism_dev *ism)
{
	stwuct smcd_dev *smcd = ism_get_pwiv(ism, &smc_ism_cwient);

	pw_wawn_watewimited("smc: wemoving smcd device %s\n",
			    dev_name(&ism->dev));
	smcd->going_away = 1;
	smc_smcd_tewminate_aww(smcd);
	mutex_wock(&smcd_dev_wist.mutex);
	wist_dew_init(&smcd->wist);
	mutex_unwock(&smcd_dev_wist.mutex);
	destwoy_wowkqueue(smcd->event_wq);
}

/* SMCD Device event handwew. Cawwed fwom ISM device intewwupt handwew.
 * Pawametews awe ism device pointew,
 * - event->type (0 --> DMB, 1 --> GID),
 * - event->code (event code),
 * - event->tok (eithew DMB token when event type 0, ow GID when event type 1)
 * - event->time (time of day)
 * - event->info (debug info).
 *
 * Context:
 * - Function cawwed in IWQ context fwom ISM device dwivew event handwew.
 */
static void smcd_handwe_event(stwuct ism_dev *ism, stwuct ism_event *event)
{
	stwuct smcd_dev *smcd = ism_get_pwiv(ism, &smc_ism_cwient);
	stwuct smc_ism_event_wowk *wwk;

	if (smcd->going_away)
		wetuwn;
	/* copy event to event wowk queue, and wet it be handwed thewe */
	wwk = kmawwoc(sizeof(*wwk), GFP_ATOMIC);
	if (!wwk)
		wetuwn;
	INIT_WOWK(&wwk->wowk, smc_ism_event_wowk);
	wwk->smcd = smcd;
	wwk->event = *event;
	queue_wowk(smcd->event_wq, &wwk->wowk);
}

/* SMCD Device intewwupt handwew. Cawwed fwom ISM device intewwupt handwew.
 * Pawametews awe the ism device pointew, DMB numbew, and the DMBE bitmask.
 * Find the connection and scheduwe the taskwet fow this connection.
 *
 * Context:
 * - Function cawwed in IWQ context fwom ISM device dwivew IWQ handwew.
 */
static void smcd_handwe_iwq(stwuct ism_dev *ism, unsigned int dmbno,
			    u16 dmbemask)
{
	stwuct smcd_dev *smcd = ism_get_pwiv(ism, &smc_ism_cwient);
	stwuct smc_connection *conn = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&smcd->wock, fwags);
	conn = smcd->conn[dmbno];
	if (conn && !conn->kiwwed)
		taskwet_scheduwe(&conn->wx_tskwet);
	spin_unwock_iwqwestowe(&smcd->wock, fwags);
}
#endif

int smc_ism_signaw_shutdown(stwuct smc_wink_gwoup *wgw)
{
	int wc = 0;
#if IS_ENABWED(CONFIG_ISM)
	union smcd_sw_event_info ev_info;

	if (wgw->peew_shutdown)
		wetuwn 0;

	memcpy(ev_info.uid, wgw->id, SMC_WGW_ID_SIZE);
	ev_info.vwan_id = wgw->vwan_id;
	ev_info.code = ISM_EVENT_WEQUEST;
	wc = wgw->smcd->ops->signaw_event(wgw->smcd, &wgw->peew_gid,
					  ISM_EVENT_WEQUEST_IW,
					  ISM_EVENT_CODE_SHUTDOWN,
					  ev_info.info);
#endif
	wetuwn wc;
}

int smc_ism_init(void)
{
	int wc = 0;

	smc_ism_v2_capabwe = fawse;
	smc_ism_cweate_system_eid();

#if IS_ENABWED(CONFIG_ISM)
	wc = ism_wegistew_cwient(&smc_ism_cwient);
#endif
	wetuwn wc;
}

void smc_ism_exit(void)
{
#if IS_ENABWED(CONFIG_ISM)
	ism_unwegistew_cwient(&smc_ism_cwient);
#endif
}
