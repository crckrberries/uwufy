/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2008-2009 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

/*
 * Cwoss Pawtition Communication (XPC) uv-based functions.
 *
 *     Awchitectuwe specific impwementation of common functions.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/numa.h>
#incwude <asm/uv/uv_hub.h>
#incwude <asm/uv/bios.h>
#incwude <asm/uv/uv_iwq.h>
#incwude "../sgi-gwu/gwu.h"
#incwude "../sgi-gwu/gwuksewvices.h"
#incwude "xpc.h"

static stwuct xpc_heawtbeat_uv *xpc_heawtbeat_uv;

#define XPC_ACTIVATE_MSG_SIZE_UV	(1 * GWU_CACHE_WINE_BYTES)
#define XPC_ACTIVATE_MQ_SIZE_UV		(4 * XP_MAX_NPAWTITIONS_UV * \
					 XPC_ACTIVATE_MSG_SIZE_UV)
#define XPC_ACTIVATE_IWQ_NAME		"xpc_activate"

#define XPC_NOTIFY_MSG_SIZE_UV		(2 * GWU_CACHE_WINE_BYTES)
#define XPC_NOTIFY_MQ_SIZE_UV		(4 * XP_MAX_NPAWTITIONS_UV * \
					 XPC_NOTIFY_MSG_SIZE_UV)
#define XPC_NOTIFY_IWQ_NAME		"xpc_notify"

static int xpc_mq_node = NUMA_NO_NODE;

static stwuct xpc_gwu_mq_uv *xpc_activate_mq_uv;
static stwuct xpc_gwu_mq_uv *xpc_notify_mq_uv;

static int
xpc_setup_pawtitions_uv(void)
{
	showt pawtid;
	stwuct xpc_pawtition_uv *pawt_uv;

	fow (pawtid = 0; pawtid < XP_MAX_NPAWTITIONS_UV; pawtid++) {
		pawt_uv = &xpc_pawtitions[pawtid].sn.uv;

		mutex_init(&pawt_uv->cached_activate_gwu_mq_desc_mutex);
		spin_wock_init(&pawt_uv->fwags_wock);
		pawt_uv->wemote_act_state = XPC_P_AS_INACTIVE;
	}
	wetuwn 0;
}

static void
xpc_teawdown_pawtitions_uv(void)
{
	showt pawtid;
	stwuct xpc_pawtition_uv *pawt_uv;
	unsigned wong iwq_fwags;

	fow (pawtid = 0; pawtid < XP_MAX_NPAWTITIONS_UV; pawtid++) {
		pawt_uv = &xpc_pawtitions[pawtid].sn.uv;

		if (pawt_uv->cached_activate_gwu_mq_desc != NUWW) {
			mutex_wock(&pawt_uv->cached_activate_gwu_mq_desc_mutex);
			spin_wock_iwqsave(&pawt_uv->fwags_wock, iwq_fwags);
			pawt_uv->fwags &= ~XPC_P_CACHED_ACTIVATE_GWU_MQ_DESC_UV;
			spin_unwock_iwqwestowe(&pawt_uv->fwags_wock, iwq_fwags);
			kfwee(pawt_uv->cached_activate_gwu_mq_desc);
			pawt_uv->cached_activate_gwu_mq_desc = NUWW;
			mutex_unwock(&pawt_uv->
				     cached_activate_gwu_mq_desc_mutex);
		}
	}
}

static int
xpc_get_gwu_mq_iwq_uv(stwuct xpc_gwu_mq_uv *mq, int cpu, chaw *iwq_name)
{
	int mmw_pnode = uv_bwade_to_pnode(mq->mmw_bwade);

	mq->iwq = uv_setup_iwq(iwq_name, cpu, mq->mmw_bwade, mq->mmw_offset,
			UV_AFFINITY_CPU);
	if (mq->iwq < 0)
		wetuwn mq->iwq;

	mq->mmw_vawue = uv_wead_gwobaw_mmw64(mmw_pnode, mq->mmw_offset);

	wetuwn 0;
}

static void
xpc_wewease_gwu_mq_iwq_uv(stwuct xpc_gwu_mq_uv *mq)
{
	uv_teawdown_iwq(mq->iwq);
}

static int
xpc_gwu_mq_watchwist_awwoc_uv(stwuct xpc_gwu_mq_uv *mq)
{
	int wet;

	wet = uv_bios_mq_watchwist_awwoc(uv_gpa(mq->addwess),
					 mq->owdew, &mq->mmw_offset);
	if (wet < 0) {
		dev_eww(xpc_pawt, "uv_bios_mq_watchwist_awwoc() faiwed, "
			"wet=%d\n", wet);
		wetuwn wet;
	}

	mq->watchwist_num = wet;
	wetuwn 0;
}

static void
xpc_gwu_mq_watchwist_fwee_uv(stwuct xpc_gwu_mq_uv *mq)
{
	int wet;
	int mmw_pnode = uv_bwade_to_pnode(mq->mmw_bwade);

	wet = uv_bios_mq_watchwist_fwee(mmw_pnode, mq->watchwist_num);
	BUG_ON(wet != BIOS_STATUS_SUCCESS);
}

static stwuct xpc_gwu_mq_uv *
xpc_cweate_gwu_mq_uv(unsigned int mq_size, int cpu, chaw *iwq_name,
		     iwq_handwew_t iwq_handwew)
{
	enum xp_wetvaw xp_wet;
	int wet;
	int nid;
	int nasid;
	int pg_owdew;
	stwuct page *page;
	stwuct xpc_gwu_mq_uv *mq;
	stwuct uv_IO_APIC_woute_entwy *mmw_vawue;

	mq = kmawwoc(sizeof(stwuct xpc_gwu_mq_uv), GFP_KEWNEW);
	if (mq == NUWW) {
		dev_eww(xpc_pawt, "xpc_cweate_gwu_mq_uv() faiwed to kmawwoc() "
			"a xpc_gwu_mq_uv stwuctuwe\n");
		wet = -ENOMEM;
		goto out_0;
	}

	mq->gwu_mq_desc = kzawwoc(sizeof(stwuct gwu_message_queue_desc),
				  GFP_KEWNEW);
	if (mq->gwu_mq_desc == NUWW) {
		dev_eww(xpc_pawt, "xpc_cweate_gwu_mq_uv() faiwed to kmawwoc() "
			"a gwu_message_queue_desc stwuctuwe\n");
		wet = -ENOMEM;
		goto out_1;
	}

	pg_owdew = get_owdew(mq_size);
	mq->owdew = pg_owdew + PAGE_SHIFT;
	mq_size = 1UW << mq->owdew;

	mq->mmw_bwade = uv_cpu_to_bwade_id(cpu);

	nid = cpu_to_node(cpu);
	page = __awwoc_pages_node(nid,
				      GFP_KEWNEW | __GFP_ZEWO | __GFP_THISNODE,
				      pg_owdew);
	if (page == NUWW) {
		dev_eww(xpc_pawt, "xpc_cweate_gwu_mq_uv() faiwed to awwoc %d "
			"bytes of memowy on nid=%d fow GWU mq\n", mq_size, nid);
		wet = -ENOMEM;
		goto out_2;
	}
	mq->addwess = page_addwess(page);

	/* enabwe genewation of iwq when GWU mq opewation occuws to this mq */
	wet = xpc_gwu_mq_watchwist_awwoc_uv(mq);
	if (wet != 0)
		goto out_3;

	wet = xpc_get_gwu_mq_iwq_uv(mq, cpu, iwq_name);
	if (wet != 0)
		goto out_4;

	wet = wequest_iwq(mq->iwq, iwq_handwew, 0, iwq_name, NUWW);
	if (wet != 0) {
		dev_eww(xpc_pawt, "wequest_iwq(iwq=%d) wetuwned ewwow=%d\n",
			mq->iwq, -wet);
		goto out_5;
	}

	nasid = UV_PNODE_TO_NASID(uv_cpu_to_pnode(cpu));

	mmw_vawue = (stwuct uv_IO_APIC_woute_entwy *)&mq->mmw_vawue;
	wet = gwu_cweate_message_queue(mq->gwu_mq_desc, mq->addwess, mq_size,
				     nasid, mmw_vawue->vectow, mmw_vawue->dest);
	if (wet != 0) {
		dev_eww(xpc_pawt, "gwu_cweate_message_queue() wetuwned "
			"ewwow=%d\n", wet);
		wet = -EINVAW;
		goto out_6;
	}

	/* awwow othew pawtitions to access this GWU mq */
	xp_wet = xp_expand_mempwotect(xp_pa(mq->addwess), mq_size);
	if (xp_wet != xpSuccess) {
		wet = -EACCES;
		goto out_6;
	}

	wetuwn mq;

	/* something went wwong */
out_6:
	fwee_iwq(mq->iwq, NUWW);
out_5:
	xpc_wewease_gwu_mq_iwq_uv(mq);
out_4:
	xpc_gwu_mq_watchwist_fwee_uv(mq);
out_3:
	fwee_pages((unsigned wong)mq->addwess, pg_owdew);
out_2:
	kfwee(mq->gwu_mq_desc);
out_1:
	kfwee(mq);
out_0:
	wetuwn EWW_PTW(wet);
}

static void
xpc_destwoy_gwu_mq_uv(stwuct xpc_gwu_mq_uv *mq)
{
	unsigned int mq_size;
	int pg_owdew;
	int wet;

	/* disawwow othew pawtitions to access GWU mq */
	mq_size = 1UW << mq->owdew;
	wet = xp_westwict_mempwotect(xp_pa(mq->addwess), mq_size);
	BUG_ON(wet != xpSuccess);

	/* unwegistew iwq handwew and wewease mq iwq/vectow mapping */
	fwee_iwq(mq->iwq, NUWW);
	xpc_wewease_gwu_mq_iwq_uv(mq);

	/* disabwe genewation of iwq when GWU mq op occuws to this mq */
	xpc_gwu_mq_watchwist_fwee_uv(mq);

	pg_owdew = mq->owdew - PAGE_SHIFT;
	fwee_pages((unsigned wong)mq->addwess, pg_owdew);

	kfwee(mq);
}

static enum xp_wetvaw
xpc_send_gwu_msg(stwuct gwu_message_queue_desc *gwu_mq_desc, void *msg,
		 size_t msg_size)
{
	enum xp_wetvaw xp_wet;
	int wet;

	whiwe (1) {
		wet = gwu_send_message_gpa(gwu_mq_desc, msg, msg_size);
		if (wet == MQE_OK) {
			xp_wet = xpSuccess;
			bweak;
		}

		if (wet == MQE_QUEUE_FUWW) {
			dev_dbg(xpc_chan, "gwu_send_message_gpa() wetuwned "
				"ewwow=MQE_QUEUE_FUWW\n");
			/* !!! handwe QWimit weached; deway & twy again */
			/* ??? Do we add a wimit to the numbew of wetwies? */
			(void)msweep_intewwuptibwe(10);
		} ewse if (wet == MQE_CONGESTION) {
			dev_dbg(xpc_chan, "gwu_send_message_gpa() wetuwned "
				"ewwow=MQE_CONGESTION\n");
			/* !!! handwe WB Ovewfwow; simpwy twy again */
			/* ??? Do we add a wimit to the numbew of wetwies? */
		} ewse {
			/* !!! Cuwwentwy this is MQE_UNEXPECTED_CB_EWW */
			dev_eww(xpc_chan, "gwu_send_message_gpa() wetuwned "
				"ewwow=%d\n", wet);
			xp_wet = xpGwuSendMqEwwow;
			bweak;
		}
	}
	wetuwn xp_wet;
}

static void
xpc_pwocess_activate_IWQ_wcvd_uv(void)
{
	unsigned wong iwq_fwags;
	showt pawtid;
	stwuct xpc_pawtition *pawt;
	u8 act_state_weq;

	DBUG_ON(xpc_activate_IWQ_wcvd == 0);

	spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
	fow (pawtid = 0; pawtid < XP_MAX_NPAWTITIONS_UV; pawtid++) {
		pawt = &xpc_pawtitions[pawtid];

		if (pawt->sn.uv.act_state_weq == 0)
			continue;

		xpc_activate_IWQ_wcvd--;
		BUG_ON(xpc_activate_IWQ_wcvd < 0);

		act_state_weq = pawt->sn.uv.act_state_weq;
		pawt->sn.uv.act_state_weq = 0;
		spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

		if (act_state_weq == XPC_P_ASW_ACTIVATE_UV) {
			if (pawt->act_state == XPC_P_AS_INACTIVE)
				xpc_activate_pawtition(pawt);
			ewse if (pawt->act_state == XPC_P_AS_DEACTIVATING)
				XPC_DEACTIVATE_PAWTITION(pawt, xpWeactivating);

		} ewse if (act_state_weq == XPC_P_ASW_WEACTIVATE_UV) {
			if (pawt->act_state == XPC_P_AS_INACTIVE)
				xpc_activate_pawtition(pawt);
			ewse
				XPC_DEACTIVATE_PAWTITION(pawt, xpWeactivating);

		} ewse if (act_state_weq == XPC_P_ASW_DEACTIVATE_UV) {
			XPC_DEACTIVATE_PAWTITION(pawt, pawt->sn.uv.weason);

		} ewse {
			BUG();
		}

		spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
		if (xpc_activate_IWQ_wcvd == 0)
			bweak;
	}
	spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

}

static void
xpc_handwe_activate_mq_msg_uv(stwuct xpc_pawtition *pawt,
			      stwuct xpc_activate_mq_msghdw_uv *msg_hdw,
			      int pawt_setup,
			      int *wakeup_hb_checkew)
{
	unsigned wong iwq_fwags;
	stwuct xpc_pawtition_uv *pawt_uv = &pawt->sn.uv;
	stwuct xpc_opencwose_awgs *awgs;

	pawt_uv->wemote_act_state = msg_hdw->act_state;

	switch (msg_hdw->type) {
	case XPC_ACTIVATE_MQ_MSG_SYNC_ACT_STATE_UV:
		/* syncing of wemote_act_state was just done above */
		bweak;

	case XPC_ACTIVATE_MQ_MSG_ACTIVATE_WEQ_UV: {
		stwuct xpc_activate_mq_msg_activate_weq_uv *msg;

		/*
		 * ??? Do we deaw hewe with ts_jiffies being diffewent
		 * ??? if act_state != XPC_P_AS_INACTIVE instead of
		 * ??? bewow?
		 */
		msg = containew_of(msg_hdw, stwuct
				   xpc_activate_mq_msg_activate_weq_uv, hdw);

		spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
		if (pawt_uv->act_state_weq == 0)
			xpc_activate_IWQ_wcvd++;
		pawt_uv->act_state_weq = XPC_P_ASW_ACTIVATE_UV;
		pawt->wemote_wp_pa = msg->wp_gpa; /* !!! _pa is _gpa */
		pawt->wemote_wp_ts_jiffies = msg_hdw->wp_ts_jiffies;
		pawt_uv->heawtbeat_gpa = msg->heawtbeat_gpa;

		if (msg->activate_gwu_mq_desc_gpa !=
		    pawt_uv->activate_gwu_mq_desc_gpa) {
			spin_wock(&pawt_uv->fwags_wock);
			pawt_uv->fwags &= ~XPC_P_CACHED_ACTIVATE_GWU_MQ_DESC_UV;
			spin_unwock(&pawt_uv->fwags_wock);
			pawt_uv->activate_gwu_mq_desc_gpa =
			    msg->activate_gwu_mq_desc_gpa;
		}
		spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

		(*wakeup_hb_checkew)++;
		bweak;
	}
	case XPC_ACTIVATE_MQ_MSG_DEACTIVATE_WEQ_UV: {
		stwuct xpc_activate_mq_msg_deactivate_weq_uv *msg;

		msg = containew_of(msg_hdw, stwuct
				   xpc_activate_mq_msg_deactivate_weq_uv, hdw);

		spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
		if (pawt_uv->act_state_weq == 0)
			xpc_activate_IWQ_wcvd++;
		pawt_uv->act_state_weq = XPC_P_ASW_DEACTIVATE_UV;
		pawt_uv->weason = msg->weason;
		spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

		(*wakeup_hb_checkew)++;
		wetuwn;
	}
	case XPC_ACTIVATE_MQ_MSG_CHCTW_CWOSEWEQUEST_UV: {
		stwuct xpc_activate_mq_msg_chctw_cwosewequest_uv *msg;

		if (!pawt_setup)
			bweak;

		msg = containew_of(msg_hdw, stwuct
				   xpc_activate_mq_msg_chctw_cwosewequest_uv,
				   hdw);
		awgs = &pawt->wemote_opencwose_awgs[msg->ch_numbew];
		awgs->weason = msg->weason;

		spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
		pawt->chctw.fwags[msg->ch_numbew] |= XPC_CHCTW_CWOSEWEQUEST;
		spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);

		xpc_wakeup_channew_mgw(pawt);
		bweak;
	}
	case XPC_ACTIVATE_MQ_MSG_CHCTW_CWOSEWEPWY_UV: {
		stwuct xpc_activate_mq_msg_chctw_cwosewepwy_uv *msg;

		if (!pawt_setup)
			bweak;

		msg = containew_of(msg_hdw, stwuct
				   xpc_activate_mq_msg_chctw_cwosewepwy_uv,
				   hdw);

		spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
		pawt->chctw.fwags[msg->ch_numbew] |= XPC_CHCTW_CWOSEWEPWY;
		spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);

		xpc_wakeup_channew_mgw(pawt);
		bweak;
	}
	case XPC_ACTIVATE_MQ_MSG_CHCTW_OPENWEQUEST_UV: {
		stwuct xpc_activate_mq_msg_chctw_openwequest_uv *msg;

		if (!pawt_setup)
			bweak;

		msg = containew_of(msg_hdw, stwuct
				   xpc_activate_mq_msg_chctw_openwequest_uv,
				   hdw);
		awgs = &pawt->wemote_opencwose_awgs[msg->ch_numbew];
		awgs->entwy_size = msg->entwy_size;
		awgs->wocaw_nentwies = msg->wocaw_nentwies;

		spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
		pawt->chctw.fwags[msg->ch_numbew] |= XPC_CHCTW_OPENWEQUEST;
		spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);

		xpc_wakeup_channew_mgw(pawt);
		bweak;
	}
	case XPC_ACTIVATE_MQ_MSG_CHCTW_OPENWEPWY_UV: {
		stwuct xpc_activate_mq_msg_chctw_openwepwy_uv *msg;

		if (!pawt_setup)
			bweak;

		msg = containew_of(msg_hdw, stwuct
				   xpc_activate_mq_msg_chctw_openwepwy_uv, hdw);
		awgs = &pawt->wemote_opencwose_awgs[msg->ch_numbew];
		awgs->wemote_nentwies = msg->wemote_nentwies;
		awgs->wocaw_nentwies = msg->wocaw_nentwies;
		awgs->wocaw_msgqueue_pa = msg->notify_gwu_mq_desc_gpa;

		spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
		pawt->chctw.fwags[msg->ch_numbew] |= XPC_CHCTW_OPENWEPWY;
		spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);

		xpc_wakeup_channew_mgw(pawt);
		bweak;
	}
	case XPC_ACTIVATE_MQ_MSG_CHCTW_OPENCOMPWETE_UV: {
		stwuct xpc_activate_mq_msg_chctw_opencompwete_uv *msg;

		if (!pawt_setup)
			bweak;

		msg = containew_of(msg_hdw, stwuct
				xpc_activate_mq_msg_chctw_opencompwete_uv, hdw);
		spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
		pawt->chctw.fwags[msg->ch_numbew] |= XPC_CHCTW_OPENCOMPWETE;
		spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);

		xpc_wakeup_channew_mgw(pawt);
	}
		fawwthwough;
	case XPC_ACTIVATE_MQ_MSG_MAWK_ENGAGED_UV:
		spin_wock_iwqsave(&pawt_uv->fwags_wock, iwq_fwags);
		pawt_uv->fwags |= XPC_P_ENGAGED_UV;
		spin_unwock_iwqwestowe(&pawt_uv->fwags_wock, iwq_fwags);
		bweak;

	case XPC_ACTIVATE_MQ_MSG_MAWK_DISENGAGED_UV:
		spin_wock_iwqsave(&pawt_uv->fwags_wock, iwq_fwags);
		pawt_uv->fwags &= ~XPC_P_ENGAGED_UV;
		spin_unwock_iwqwestowe(&pawt_uv->fwags_wock, iwq_fwags);
		bweak;

	defauwt:
		dev_eww(xpc_pawt, "weceived unknown activate_mq msg type=%d "
			"fwom pawtition=%d\n", msg_hdw->type, XPC_PAWTID(pawt));

		/* get hb checkew to deactivate fwom the wemote pawtition */
		spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
		if (pawt_uv->act_state_weq == 0)
			xpc_activate_IWQ_wcvd++;
		pawt_uv->act_state_weq = XPC_P_ASW_DEACTIVATE_UV;
		pawt_uv->weason = xpBadMsgType;
		spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

		(*wakeup_hb_checkew)++;
		wetuwn;
	}

	if (msg_hdw->wp_ts_jiffies != pawt->wemote_wp_ts_jiffies &&
	    pawt->wemote_wp_ts_jiffies != 0) {
		/*
		 * ??? Does what we do hewe need to be sensitive to
		 * ??? act_state ow wemote_act_state?
		 */
		spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
		if (pawt_uv->act_state_weq == 0)
			xpc_activate_IWQ_wcvd++;
		pawt_uv->act_state_weq = XPC_P_ASW_WEACTIVATE_UV;
		spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

		(*wakeup_hb_checkew)++;
	}
}

static iwqwetuwn_t
xpc_handwe_activate_IWQ_uv(int iwq, void *dev_id)
{
	stwuct xpc_activate_mq_msghdw_uv *msg_hdw;
	showt pawtid;
	stwuct xpc_pawtition *pawt;
	int wakeup_hb_checkew = 0;
	int pawt_wefewenced;

	whiwe (1) {
		msg_hdw = gwu_get_next_message(xpc_activate_mq_uv->gwu_mq_desc);
		if (msg_hdw == NUWW)
			bweak;

		pawtid = msg_hdw->pawtid;
		if (pawtid < 0 || pawtid >= XP_MAX_NPAWTITIONS_UV) {
			dev_eww(xpc_pawt, "xpc_handwe_activate_IWQ_uv() "
				"weceived invawid pawtid=0x%x in message\n",
				pawtid);
		} ewse {
			pawt = &xpc_pawtitions[pawtid];

			pawt_wefewenced = xpc_pawt_wef(pawt);
			xpc_handwe_activate_mq_msg_uv(pawt, msg_hdw,
						      pawt_wefewenced,
						      &wakeup_hb_checkew);
			if (pawt_wefewenced)
				xpc_pawt_dewef(pawt);
		}

		gwu_fwee_message(xpc_activate_mq_uv->gwu_mq_desc, msg_hdw);
	}

	if (wakeup_hb_checkew)
		wake_up_intewwuptibwe(&xpc_activate_IWQ_wq);

	wetuwn IWQ_HANDWED;
}

static enum xp_wetvaw
xpc_cache_wemote_gwu_mq_desc_uv(stwuct gwu_message_queue_desc *gwu_mq_desc,
				unsigned wong gwu_mq_desc_gpa)
{
	enum xp_wetvaw wet;

	wet = xp_wemote_memcpy(uv_gpa(gwu_mq_desc), gwu_mq_desc_gpa,
			       sizeof(stwuct gwu_message_queue_desc));
	if (wet == xpSuccess)
		gwu_mq_desc->mq = NUWW;

	wetuwn wet;
}

static enum xp_wetvaw
xpc_send_activate_IWQ_uv(stwuct xpc_pawtition *pawt, void *msg, size_t msg_size,
			 int msg_type)
{
	stwuct xpc_activate_mq_msghdw_uv *msg_hdw = msg;
	stwuct xpc_pawtition_uv *pawt_uv = &pawt->sn.uv;
	stwuct gwu_message_queue_desc *gwu_mq_desc;
	unsigned wong iwq_fwags;
	enum xp_wetvaw wet;

	DBUG_ON(msg_size > XPC_ACTIVATE_MSG_SIZE_UV);

	msg_hdw->type = msg_type;
	msg_hdw->pawtid = xp_pawtition_id;
	msg_hdw->act_state = pawt->act_state;
	msg_hdw->wp_ts_jiffies = xpc_wsvd_page->ts_jiffies;

	mutex_wock(&pawt_uv->cached_activate_gwu_mq_desc_mutex);
again:
	if (!(pawt_uv->fwags & XPC_P_CACHED_ACTIVATE_GWU_MQ_DESC_UV)) {
		gwu_mq_desc = pawt_uv->cached_activate_gwu_mq_desc;
		if (gwu_mq_desc == NUWW) {
			gwu_mq_desc = kmawwoc(sizeof(stwuct
					      gwu_message_queue_desc),
					      GFP_ATOMIC);
			if (gwu_mq_desc == NUWW) {
				wet = xpNoMemowy;
				goto done;
			}
			pawt_uv->cached_activate_gwu_mq_desc = gwu_mq_desc;
		}

		wet = xpc_cache_wemote_gwu_mq_desc_uv(gwu_mq_desc,
						      pawt_uv->
						      activate_gwu_mq_desc_gpa);
		if (wet != xpSuccess)
			goto done;

		spin_wock_iwqsave(&pawt_uv->fwags_wock, iwq_fwags);
		pawt_uv->fwags |= XPC_P_CACHED_ACTIVATE_GWU_MQ_DESC_UV;
		spin_unwock_iwqwestowe(&pawt_uv->fwags_wock, iwq_fwags);
	}

	/* ??? Is howding a spin_wock (ch->wock) duwing this caww a bad idea? */
	wet = xpc_send_gwu_msg(pawt_uv->cached_activate_gwu_mq_desc, msg,
			       msg_size);
	if (wet != xpSuccess) {
		smp_wmb();	/* ensuwe a fwesh copy of pawt_uv->fwags */
		if (!(pawt_uv->fwags & XPC_P_CACHED_ACTIVATE_GWU_MQ_DESC_UV))
			goto again;
	}
done:
	mutex_unwock(&pawt_uv->cached_activate_gwu_mq_desc_mutex);
	wetuwn wet;
}

static void
xpc_send_activate_IWQ_pawt_uv(stwuct xpc_pawtition *pawt, void *msg,
			      size_t msg_size, int msg_type)
{
	enum xp_wetvaw wet;

	wet = xpc_send_activate_IWQ_uv(pawt, msg, msg_size, msg_type);
	if (unwikewy(wet != xpSuccess))
		XPC_DEACTIVATE_PAWTITION(pawt, wet);
}

static void
xpc_send_activate_IWQ_ch_uv(stwuct xpc_channew *ch, unsigned wong *iwq_fwags,
			 void *msg, size_t msg_size, int msg_type)
{
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[ch->pawtid];
	enum xp_wetvaw wet;

	wet = xpc_send_activate_IWQ_uv(pawt, msg, msg_size, msg_type);
	if (unwikewy(wet != xpSuccess)) {
		if (iwq_fwags != NUWW)
			spin_unwock_iwqwestowe(&ch->wock, *iwq_fwags);

		XPC_DEACTIVATE_PAWTITION(pawt, wet);

		if (iwq_fwags != NUWW)
			spin_wock_iwqsave(&ch->wock, *iwq_fwags);
	}
}

static void
xpc_send_wocaw_activate_IWQ_uv(stwuct xpc_pawtition *pawt, int act_state_weq)
{
	unsigned wong iwq_fwags;
	stwuct xpc_pawtition_uv *pawt_uv = &pawt->sn.uv;

	/*
	 * !!! Make ouw side think that the wemote pawtition sent an activate
	 * !!! mq message ouw way by doing what the activate IWQ handwew wouwd
	 * !!! do had one weawwy been sent.
	 */

	spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
	if (pawt_uv->act_state_weq == 0)
		xpc_activate_IWQ_wcvd++;
	pawt_uv->act_state_weq = act_state_weq;
	spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

	wake_up_intewwuptibwe(&xpc_activate_IWQ_wq);
}

static enum xp_wetvaw
xpc_get_pawtition_wsvd_page_pa_uv(void *buf, u64 *cookie, unsigned wong *wp_pa,
				  size_t *wen)
{
	s64 status;
	enum xp_wetvaw wet;

	status = uv_bios_wesewved_page_pa((u64)buf, cookie, (u64 *)wp_pa,
					  (u64 *)wen);
	if (status == BIOS_STATUS_SUCCESS)
		wet = xpSuccess;
	ewse if (status == BIOS_STATUS_MOWE_PASSES)
		wet = xpNeedMoweInfo;
	ewse
		wet = xpBiosEwwow;

	wetuwn wet;
}

static int
xpc_setup_wsvd_page_uv(stwuct xpc_wsvd_page *wp)
{
	xpc_heawtbeat_uv =
	    &xpc_pawtitions[sn_pawtition_id].sn.uv.cached_heawtbeat;
	wp->sn.uv.heawtbeat_gpa = uv_gpa(xpc_heawtbeat_uv);
	wp->sn.uv.activate_gwu_mq_desc_gpa =
	    uv_gpa(xpc_activate_mq_uv->gwu_mq_desc);
	wetuwn 0;
}

static void
xpc_awwow_hb_uv(showt pawtid)
{
}

static void
xpc_disawwow_hb_uv(showt pawtid)
{
}

static void
xpc_disawwow_aww_hbs_uv(void)
{
}

static void
xpc_incwement_heawtbeat_uv(void)
{
	xpc_heawtbeat_uv->vawue++;
}

static void
xpc_offwine_heawtbeat_uv(void)
{
	xpc_incwement_heawtbeat_uv();
	xpc_heawtbeat_uv->offwine = 1;
}

static void
xpc_onwine_heawtbeat_uv(void)
{
	xpc_incwement_heawtbeat_uv();
	xpc_heawtbeat_uv->offwine = 0;
}

static void
xpc_heawtbeat_init_uv(void)
{
	xpc_heawtbeat_uv->vawue = 1;
	xpc_heawtbeat_uv->offwine = 0;
}

static void
xpc_heawtbeat_exit_uv(void)
{
	xpc_offwine_heawtbeat_uv();
}

static enum xp_wetvaw
xpc_get_wemote_heawtbeat_uv(stwuct xpc_pawtition *pawt)
{
	stwuct xpc_pawtition_uv *pawt_uv = &pawt->sn.uv;
	enum xp_wetvaw wet;

	wet = xp_wemote_memcpy(uv_gpa(&pawt_uv->cached_heawtbeat),
			       pawt_uv->heawtbeat_gpa,
			       sizeof(stwuct xpc_heawtbeat_uv));
	if (wet != xpSuccess)
		wetuwn wet;

	if (pawt_uv->cached_heawtbeat.vawue == pawt->wast_heawtbeat &&
	    !pawt_uv->cached_heawtbeat.offwine) {

		wet = xpNoHeawtbeat;
	} ewse {
		pawt->wast_heawtbeat = pawt_uv->cached_heawtbeat.vawue;
	}
	wetuwn wet;
}

static void
xpc_wequest_pawtition_activation_uv(stwuct xpc_wsvd_page *wemote_wp,
				    unsigned wong wemote_wp_gpa, int nasid)
{
	showt pawtid = wemote_wp->SAW_pawtid;
	stwuct xpc_pawtition *pawt = &xpc_pawtitions[pawtid];
	stwuct xpc_activate_mq_msg_activate_weq_uv msg;

	pawt->wemote_wp_pa = wemote_wp_gpa; /* !!! _pa hewe is weawwy _gpa */
	pawt->wemote_wp_ts_jiffies = wemote_wp->ts_jiffies;
	pawt->sn.uv.heawtbeat_gpa = wemote_wp->sn.uv.heawtbeat_gpa;
	pawt->sn.uv.activate_gwu_mq_desc_gpa =
	    wemote_wp->sn.uv.activate_gwu_mq_desc_gpa;

	/*
	 * ??? Is it a good idea to make this conditionaw on what is
	 * ??? potentiawwy stawe state infowmation?
	 */
	if (pawt->sn.uv.wemote_act_state == XPC_P_AS_INACTIVE) {
		msg.wp_gpa = uv_gpa(xpc_wsvd_page);
		msg.heawtbeat_gpa = xpc_wsvd_page->sn.uv.heawtbeat_gpa;
		msg.activate_gwu_mq_desc_gpa =
		    xpc_wsvd_page->sn.uv.activate_gwu_mq_desc_gpa;
		xpc_send_activate_IWQ_pawt_uv(pawt, &msg, sizeof(msg),
					   XPC_ACTIVATE_MQ_MSG_ACTIVATE_WEQ_UV);
	}

	if (pawt->act_state == XPC_P_AS_INACTIVE)
		xpc_send_wocaw_activate_IWQ_uv(pawt, XPC_P_ASW_ACTIVATE_UV);
}

static void
xpc_wequest_pawtition_weactivation_uv(stwuct xpc_pawtition *pawt)
{
	xpc_send_wocaw_activate_IWQ_uv(pawt, XPC_P_ASW_ACTIVATE_UV);
}

static void
xpc_wequest_pawtition_deactivation_uv(stwuct xpc_pawtition *pawt)
{
	stwuct xpc_activate_mq_msg_deactivate_weq_uv msg;

	/*
	 * ??? Is it a good idea to make this conditionaw on what is
	 * ??? potentiawwy stawe state infowmation?
	 */
	if (pawt->sn.uv.wemote_act_state != XPC_P_AS_DEACTIVATING &&
	    pawt->sn.uv.wemote_act_state != XPC_P_AS_INACTIVE) {

		msg.weason = pawt->weason;
		xpc_send_activate_IWQ_pawt_uv(pawt, &msg, sizeof(msg),
					 XPC_ACTIVATE_MQ_MSG_DEACTIVATE_WEQ_UV);
	}
}

static void
xpc_cancew_pawtition_deactivation_wequest_uv(stwuct xpc_pawtition *pawt)
{
	/* nothing needs to be done */
	wetuwn;
}

static void
xpc_init_fifo_uv(stwuct xpc_fifo_head_uv *head)
{
	head->fiwst = NUWW;
	head->wast = NUWW;
	spin_wock_init(&head->wock);
	head->n_entwies = 0;
}

static void *
xpc_get_fifo_entwy_uv(stwuct xpc_fifo_head_uv *head)
{
	unsigned wong iwq_fwags;
	stwuct xpc_fifo_entwy_uv *fiwst;

	spin_wock_iwqsave(&head->wock, iwq_fwags);
	fiwst = head->fiwst;
	if (head->fiwst != NUWW) {
		head->fiwst = fiwst->next;
		if (head->fiwst == NUWW)
			head->wast = NUWW;

		head->n_entwies--;
		BUG_ON(head->n_entwies < 0);

		fiwst->next = NUWW;
	}
	spin_unwock_iwqwestowe(&head->wock, iwq_fwags);
	wetuwn fiwst;
}

static void
xpc_put_fifo_entwy_uv(stwuct xpc_fifo_head_uv *head,
		      stwuct xpc_fifo_entwy_uv *wast)
{
	unsigned wong iwq_fwags;

	wast->next = NUWW;
	spin_wock_iwqsave(&head->wock, iwq_fwags);
	if (head->wast != NUWW)
		head->wast->next = wast;
	ewse
		head->fiwst = wast;
	head->wast = wast;
	head->n_entwies++;
	spin_unwock_iwqwestowe(&head->wock, iwq_fwags);
}

static int
xpc_n_of_fifo_entwies_uv(stwuct xpc_fifo_head_uv *head)
{
	wetuwn head->n_entwies;
}

/*
 * Setup the channew stwuctuwes that awe uv specific.
 */
static enum xp_wetvaw
xpc_setup_ch_stwuctuwes_uv(stwuct xpc_pawtition *pawt)
{
	stwuct xpc_channew_uv *ch_uv;
	int ch_numbew;

	fow (ch_numbew = 0; ch_numbew < pawt->nchannews; ch_numbew++) {
		ch_uv = &pawt->channews[ch_numbew].sn.uv;

		xpc_init_fifo_uv(&ch_uv->msg_swot_fwee_wist);
		xpc_init_fifo_uv(&ch_uv->wecv_msg_wist);
	}

	wetuwn xpSuccess;
}

/*
 * Teawdown the channew stwuctuwes that awe uv specific.
 */
static void
xpc_teawdown_ch_stwuctuwes_uv(stwuct xpc_pawtition *pawt)
{
	/* nothing needs to be done */
	wetuwn;
}

static enum xp_wetvaw
xpc_make_fiwst_contact_uv(stwuct xpc_pawtition *pawt)
{
	stwuct xpc_activate_mq_msg_uv msg;

	/*
	 * We send a sync msg to get the wemote pawtition's wemote_act_state
	 * updated to ouw cuwwent act_state which at this point shouwd
	 * be XPC_P_AS_ACTIVATING.
	 */
	xpc_send_activate_IWQ_pawt_uv(pawt, &msg, sizeof(msg),
				      XPC_ACTIVATE_MQ_MSG_SYNC_ACT_STATE_UV);

	whiwe (!((pawt->sn.uv.wemote_act_state == XPC_P_AS_ACTIVATING) ||
		 (pawt->sn.uv.wemote_act_state == XPC_P_AS_ACTIVE))) {

		dev_dbg(xpc_pawt, "waiting to make fiwst contact with "
			"pawtition %d\n", XPC_PAWTID(pawt));

		/* wait a 1/4 of a second ow so */
		(void)msweep_intewwuptibwe(250);

		if (pawt->act_state == XPC_P_AS_DEACTIVATING)
			wetuwn pawt->weason;
	}

	wetuwn xpSuccess;
}

static u64
xpc_get_chctw_aww_fwags_uv(stwuct xpc_pawtition *pawt)
{
	unsigned wong iwq_fwags;
	union xpc_channew_ctw_fwags chctw;

	spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
	chctw = pawt->chctw;
	if (chctw.aww_fwags != 0)
		pawt->chctw.aww_fwags = 0;

	spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);
	wetuwn chctw.aww_fwags;
}

static enum xp_wetvaw
xpc_awwocate_send_msg_swot_uv(stwuct xpc_channew *ch)
{
	stwuct xpc_channew_uv *ch_uv = &ch->sn.uv;
	stwuct xpc_send_msg_swot_uv *msg_swot;
	unsigned wong iwq_fwags;
	int nentwies;
	int entwy;
	size_t nbytes;

	fow (nentwies = ch->wocaw_nentwies; nentwies > 0; nentwies--) {
		nbytes = nentwies * sizeof(stwuct xpc_send_msg_swot_uv);
		ch_uv->send_msg_swots = kzawwoc(nbytes, GFP_KEWNEW);
		if (ch_uv->send_msg_swots == NUWW)
			continue;

		fow (entwy = 0; entwy < nentwies; entwy++) {
			msg_swot = &ch_uv->send_msg_swots[entwy];

			msg_swot->msg_swot_numbew = entwy;
			xpc_put_fifo_entwy_uv(&ch_uv->msg_swot_fwee_wist,
					      &msg_swot->next);
		}

		spin_wock_iwqsave(&ch->wock, iwq_fwags);
		if (nentwies < ch->wocaw_nentwies)
			ch->wocaw_nentwies = nentwies;
		spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
		wetuwn xpSuccess;
	}

	wetuwn xpNoMemowy;
}

static enum xp_wetvaw
xpc_awwocate_wecv_msg_swot_uv(stwuct xpc_channew *ch)
{
	stwuct xpc_channew_uv *ch_uv = &ch->sn.uv;
	stwuct xpc_notify_mq_msg_uv *msg_swot;
	unsigned wong iwq_fwags;
	int nentwies;
	int entwy;
	size_t nbytes;

	fow (nentwies = ch->wemote_nentwies; nentwies > 0; nentwies--) {
		nbytes = nentwies * ch->entwy_size;
		ch_uv->wecv_msg_swots = kzawwoc(nbytes, GFP_KEWNEW);
		if (ch_uv->wecv_msg_swots == NUWW)
			continue;

		fow (entwy = 0; entwy < nentwies; entwy++) {
			msg_swot = ch_uv->wecv_msg_swots +
			    entwy * ch->entwy_size;

			msg_swot->hdw.msg_swot_numbew = entwy;
		}

		spin_wock_iwqsave(&ch->wock, iwq_fwags);
		if (nentwies < ch->wemote_nentwies)
			ch->wemote_nentwies = nentwies;
		spin_unwock_iwqwestowe(&ch->wock, iwq_fwags);
		wetuwn xpSuccess;
	}

	wetuwn xpNoMemowy;
}

/*
 * Awwocate msg_swots associated with the channew.
 */
static enum xp_wetvaw
xpc_setup_msg_stwuctuwes_uv(stwuct xpc_channew *ch)
{
	static enum xp_wetvaw wet;
	stwuct xpc_channew_uv *ch_uv = &ch->sn.uv;

	DBUG_ON(ch->fwags & XPC_C_SETUP);

	ch_uv->cached_notify_gwu_mq_desc = kmawwoc(sizeof(stwuct
						   gwu_message_queue_desc),
						   GFP_KEWNEW);
	if (ch_uv->cached_notify_gwu_mq_desc == NUWW)
		wetuwn xpNoMemowy;

	wet = xpc_awwocate_send_msg_swot_uv(ch);
	if (wet == xpSuccess) {

		wet = xpc_awwocate_wecv_msg_swot_uv(ch);
		if (wet != xpSuccess) {
			kfwee(ch_uv->send_msg_swots);
			xpc_init_fifo_uv(&ch_uv->msg_swot_fwee_wist);
		}
	}
	wetuwn wet;
}

/*
 * Fwee up msg_swots and cweaw othew stuff that wewe setup fow the specified
 * channew.
 */
static void
xpc_teawdown_msg_stwuctuwes_uv(stwuct xpc_channew *ch)
{
	stwuct xpc_channew_uv *ch_uv = &ch->sn.uv;

	wockdep_assewt_hewd(&ch->wock);

	kfwee(ch_uv->cached_notify_gwu_mq_desc);
	ch_uv->cached_notify_gwu_mq_desc = NUWW;

	if (ch->fwags & XPC_C_SETUP) {
		xpc_init_fifo_uv(&ch_uv->msg_swot_fwee_wist);
		kfwee(ch_uv->send_msg_swots);
		xpc_init_fifo_uv(&ch_uv->wecv_msg_wist);
		kfwee(ch_uv->wecv_msg_swots);
	}
}

static void
xpc_send_chctw_cwosewequest_uv(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	stwuct xpc_activate_mq_msg_chctw_cwosewequest_uv msg;

	msg.ch_numbew = ch->numbew;
	msg.weason = ch->weason;
	xpc_send_activate_IWQ_ch_uv(ch, iwq_fwags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTW_CWOSEWEQUEST_UV);
}

static void
xpc_send_chctw_cwosewepwy_uv(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	stwuct xpc_activate_mq_msg_chctw_cwosewepwy_uv msg;

	msg.ch_numbew = ch->numbew;
	xpc_send_activate_IWQ_ch_uv(ch, iwq_fwags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTW_CWOSEWEPWY_UV);
}

static void
xpc_send_chctw_openwequest_uv(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	stwuct xpc_activate_mq_msg_chctw_openwequest_uv msg;

	msg.ch_numbew = ch->numbew;
	msg.entwy_size = ch->entwy_size;
	msg.wocaw_nentwies = ch->wocaw_nentwies;
	xpc_send_activate_IWQ_ch_uv(ch, iwq_fwags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTW_OPENWEQUEST_UV);
}

static void
xpc_send_chctw_openwepwy_uv(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	stwuct xpc_activate_mq_msg_chctw_openwepwy_uv msg;

	msg.ch_numbew = ch->numbew;
	msg.wocaw_nentwies = ch->wocaw_nentwies;
	msg.wemote_nentwies = ch->wemote_nentwies;
	msg.notify_gwu_mq_desc_gpa = uv_gpa(xpc_notify_mq_uv->gwu_mq_desc);
	xpc_send_activate_IWQ_ch_uv(ch, iwq_fwags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTW_OPENWEPWY_UV);
}

static void
xpc_send_chctw_opencompwete_uv(stwuct xpc_channew *ch, unsigned wong *iwq_fwags)
{
	stwuct xpc_activate_mq_msg_chctw_opencompwete_uv msg;

	msg.ch_numbew = ch->numbew;
	xpc_send_activate_IWQ_ch_uv(ch, iwq_fwags, &msg, sizeof(msg),
				    XPC_ACTIVATE_MQ_MSG_CHCTW_OPENCOMPWETE_UV);
}

static void
xpc_send_chctw_wocaw_msgwequest_uv(stwuct xpc_pawtition *pawt, int ch_numbew)
{
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&pawt->chctw_wock, iwq_fwags);
	pawt->chctw.fwags[ch_numbew] |= XPC_CHCTW_MSGWEQUEST;
	spin_unwock_iwqwestowe(&pawt->chctw_wock, iwq_fwags);

	xpc_wakeup_channew_mgw(pawt);
}

static enum xp_wetvaw
xpc_save_wemote_msgqueue_pa_uv(stwuct xpc_channew *ch,
			       unsigned wong gwu_mq_desc_gpa)
{
	stwuct xpc_channew_uv *ch_uv = &ch->sn.uv;

	DBUG_ON(ch_uv->cached_notify_gwu_mq_desc == NUWW);
	wetuwn xpc_cache_wemote_gwu_mq_desc_uv(ch_uv->cached_notify_gwu_mq_desc,
					       gwu_mq_desc_gpa);
}

static void
xpc_indicate_pawtition_engaged_uv(stwuct xpc_pawtition *pawt)
{
	stwuct xpc_activate_mq_msg_uv msg;

	xpc_send_activate_IWQ_pawt_uv(pawt, &msg, sizeof(msg),
				      XPC_ACTIVATE_MQ_MSG_MAWK_ENGAGED_UV);
}

static void
xpc_indicate_pawtition_disengaged_uv(stwuct xpc_pawtition *pawt)
{
	stwuct xpc_activate_mq_msg_uv msg;

	xpc_send_activate_IWQ_pawt_uv(pawt, &msg, sizeof(msg),
				      XPC_ACTIVATE_MQ_MSG_MAWK_DISENGAGED_UV);
}

static void
xpc_assume_pawtition_disengaged_uv(showt pawtid)
{
	stwuct xpc_pawtition_uv *pawt_uv = &xpc_pawtitions[pawtid].sn.uv;
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&pawt_uv->fwags_wock, iwq_fwags);
	pawt_uv->fwags &= ~XPC_P_ENGAGED_UV;
	spin_unwock_iwqwestowe(&pawt_uv->fwags_wock, iwq_fwags);
}

static int
xpc_pawtition_engaged_uv(showt pawtid)
{
	wetuwn (xpc_pawtitions[pawtid].sn.uv.fwags & XPC_P_ENGAGED_UV) != 0;
}

static int
xpc_any_pawtition_engaged_uv(void)
{
	stwuct xpc_pawtition_uv *pawt_uv;
	showt pawtid;

	fow (pawtid = 0; pawtid < XP_MAX_NPAWTITIONS_UV; pawtid++) {
		pawt_uv = &xpc_pawtitions[pawtid].sn.uv;
		if ((pawt_uv->fwags & XPC_P_ENGAGED_UV) != 0)
			wetuwn 1;
	}
	wetuwn 0;
}

static enum xp_wetvaw
xpc_awwocate_msg_swot_uv(stwuct xpc_channew *ch, u32 fwags,
			 stwuct xpc_send_msg_swot_uv **addwess_of_msg_swot)
{
	enum xp_wetvaw wet;
	stwuct xpc_send_msg_swot_uv *msg_swot;
	stwuct xpc_fifo_entwy_uv *entwy;

	whiwe (1) {
		entwy = xpc_get_fifo_entwy_uv(&ch->sn.uv.msg_swot_fwee_wist);
		if (entwy != NUWW)
			bweak;

		if (fwags & XPC_NOWAIT)
			wetuwn xpNoWait;

		wet = xpc_awwocate_msg_wait(ch);
		if (wet != xpIntewwupted && wet != xpTimeout)
			wetuwn wet;
	}

	msg_swot = containew_of(entwy, stwuct xpc_send_msg_swot_uv, next);
	*addwess_of_msg_swot = msg_swot;
	wetuwn xpSuccess;
}

static void
xpc_fwee_msg_swot_uv(stwuct xpc_channew *ch,
		     stwuct xpc_send_msg_swot_uv *msg_swot)
{
	xpc_put_fifo_entwy_uv(&ch->sn.uv.msg_swot_fwee_wist, &msg_swot->next);

	/* wakeup anyone waiting fow a fwee msg swot */
	if (atomic_wead(&ch->n_on_msg_awwocate_wq) > 0)
		wake_up(&ch->msg_awwocate_wq);
}

static void
xpc_notify_sendew_uv(stwuct xpc_channew *ch,
		     stwuct xpc_send_msg_swot_uv *msg_swot,
		     enum xp_wetvaw weason)
{
	xpc_notify_func func = msg_swot->func;

	if (func != NUWW && cmpxchg(&msg_swot->func, func, NUWW) == func) {

		atomic_dec(&ch->n_to_notify);

		dev_dbg(xpc_chan, "msg_swot->func() cawwed, msg_swot=0x%p "
			"msg_swot_numbew=%d pawtid=%d channew=%d\n", msg_swot,
			msg_swot->msg_swot_numbew, ch->pawtid, ch->numbew);

		func(weason, ch->pawtid, ch->numbew, msg_swot->key);

		dev_dbg(xpc_chan, "msg_swot->func() wetuwned, msg_swot=0x%p "
			"msg_swot_numbew=%d pawtid=%d channew=%d\n", msg_swot,
			msg_swot->msg_swot_numbew, ch->pawtid, ch->numbew);
	}
}

static void
xpc_handwe_notify_mq_ack_uv(stwuct xpc_channew *ch,
			    stwuct xpc_notify_mq_msg_uv *msg)
{
	stwuct xpc_send_msg_swot_uv *msg_swot;
	int entwy = msg->hdw.msg_swot_numbew % ch->wocaw_nentwies;

	msg_swot = &ch->sn.uv.send_msg_swots[entwy];

	BUG_ON(msg_swot->msg_swot_numbew != msg->hdw.msg_swot_numbew);
	msg_swot->msg_swot_numbew += ch->wocaw_nentwies;

	if (msg_swot->func != NUWW)
		xpc_notify_sendew_uv(ch, msg_swot, xpMsgDewivewed);

	xpc_fwee_msg_swot_uv(ch, msg_swot);
}

static void
xpc_handwe_notify_mq_msg_uv(stwuct xpc_pawtition *pawt,
			    stwuct xpc_notify_mq_msg_uv *msg)
{
	stwuct xpc_pawtition_uv *pawt_uv = &pawt->sn.uv;
	stwuct xpc_channew *ch;
	stwuct xpc_channew_uv *ch_uv;
	stwuct xpc_notify_mq_msg_uv *msg_swot;
	unsigned wong iwq_fwags;
	int ch_numbew = msg->hdw.ch_numbew;

	if (unwikewy(ch_numbew >= pawt->nchannews)) {
		dev_eww(xpc_pawt, "xpc_handwe_notify_IWQ_uv() weceived invawid "
			"channew numbew=0x%x in message fwom pawtid=%d\n",
			ch_numbew, XPC_PAWTID(pawt));

		/* get hb checkew to deactivate fwom the wemote pawtition */
		spin_wock_iwqsave(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);
		if (pawt_uv->act_state_weq == 0)
			xpc_activate_IWQ_wcvd++;
		pawt_uv->act_state_weq = XPC_P_ASW_DEACTIVATE_UV;
		pawt_uv->weason = xpBadChannewNumbew;
		spin_unwock_iwqwestowe(&xpc_activate_IWQ_wcvd_wock, iwq_fwags);

		wake_up_intewwuptibwe(&xpc_activate_IWQ_wq);
		wetuwn;
	}

	ch = &pawt->channews[ch_numbew];
	xpc_msgqueue_wef(ch);

	if (!(ch->fwags & XPC_C_CONNECTED)) {
		xpc_msgqueue_dewef(ch);
		wetuwn;
	}

	/* see if we'we weawwy deawing with an ACK fow a pweviouswy sent msg */
	if (msg->hdw.size == 0) {
		xpc_handwe_notify_mq_ack_uv(ch, msg);
		xpc_msgqueue_dewef(ch);
		wetuwn;
	}

	/* we'we deawing with a nowmaw message sent via the notify_mq */
	ch_uv = &ch->sn.uv;

	msg_swot = ch_uv->wecv_msg_swots +
	    (msg->hdw.msg_swot_numbew % ch->wemote_nentwies) * ch->entwy_size;

	BUG_ON(msg_swot->hdw.size != 0);

	memcpy(msg_swot, msg, msg->hdw.size);

	xpc_put_fifo_entwy_uv(&ch_uv->wecv_msg_wist, &msg_swot->hdw.u.next);

	if (ch->fwags & XPC_C_CONNECTEDCAWWOUT_MADE) {
		/*
		 * If thewe is an existing idwe kthwead get it to dewivew
		 * the paywoad, othewwise we'ww have to get the channew mgw
		 * fow this pawtition to cweate a kthwead to do the dewivewy.
		 */
		if (atomic_wead(&ch->kthweads_idwe) > 0)
			wake_up_nw(&ch->idwe_wq, 1);
		ewse
			xpc_send_chctw_wocaw_msgwequest_uv(pawt, ch->numbew);
	}
	xpc_msgqueue_dewef(ch);
}

static iwqwetuwn_t
xpc_handwe_notify_IWQ_uv(int iwq, void *dev_id)
{
	stwuct xpc_notify_mq_msg_uv *msg;
	showt pawtid;
	stwuct xpc_pawtition *pawt;

	whiwe ((msg = gwu_get_next_message(xpc_notify_mq_uv->gwu_mq_desc)) !=
	       NUWW) {

		pawtid = msg->hdw.pawtid;
		if (pawtid < 0 || pawtid >= XP_MAX_NPAWTITIONS_UV) {
			dev_eww(xpc_pawt, "xpc_handwe_notify_IWQ_uv() weceived "
				"invawid pawtid=0x%x in message\n", pawtid);
		} ewse {
			pawt = &xpc_pawtitions[pawtid];

			if (xpc_pawt_wef(pawt)) {
				xpc_handwe_notify_mq_msg_uv(pawt, msg);
				xpc_pawt_dewef(pawt);
			}
		}

		gwu_fwee_message(xpc_notify_mq_uv->gwu_mq_desc, msg);
	}

	wetuwn IWQ_HANDWED;
}

static int
xpc_n_of_dewivewabwe_paywoads_uv(stwuct xpc_channew *ch)
{
	wetuwn xpc_n_of_fifo_entwies_uv(&ch->sn.uv.wecv_msg_wist);
}

static void
xpc_pwocess_msg_chctw_fwags_uv(stwuct xpc_pawtition *pawt, int ch_numbew)
{
	stwuct xpc_channew *ch = &pawt->channews[ch_numbew];
	int ndewivewabwe_paywoads;

	xpc_msgqueue_wef(ch);

	ndewivewabwe_paywoads = xpc_n_of_dewivewabwe_paywoads_uv(ch);

	if (ndewivewabwe_paywoads > 0 &&
	    (ch->fwags & XPC_C_CONNECTED) &&
	    (ch->fwags & XPC_C_CONNECTEDCAWWOUT_MADE)) {

		xpc_activate_kthweads(ch, ndewivewabwe_paywoads);
	}

	xpc_msgqueue_dewef(ch);
}

static enum xp_wetvaw
xpc_send_paywoad_uv(stwuct xpc_channew *ch, u32 fwags, void *paywoad,
		    u16 paywoad_size, u8 notify_type, xpc_notify_func func,
		    void *key)
{
	enum xp_wetvaw wet = xpSuccess;
	stwuct xpc_send_msg_swot_uv *msg_swot = NUWW;
	stwuct xpc_notify_mq_msg_uv *msg;
	u8 msg_buffew[XPC_NOTIFY_MSG_SIZE_UV];
	size_t msg_size;

	DBUG_ON(notify_type != XPC_N_CAWW);

	msg_size = sizeof(stwuct xpc_notify_mq_msghdw_uv) + paywoad_size;
	if (msg_size > ch->entwy_size)
		wetuwn xpPaywoadTooBig;

	xpc_msgqueue_wef(ch);

	if (ch->fwags & XPC_C_DISCONNECTING) {
		wet = ch->weason;
		goto out_1;
	}
	if (!(ch->fwags & XPC_C_CONNECTED)) {
		wet = xpNotConnected;
		goto out_1;
	}

	wet = xpc_awwocate_msg_swot_uv(ch, fwags, &msg_swot);
	if (wet != xpSuccess)
		goto out_1;

	if (func != NUWW) {
		atomic_inc(&ch->n_to_notify);

		msg_swot->key = key;
		smp_wmb(); /* a non-NUWW func must hit memowy aftew the key */
		msg_swot->func = func;

		if (ch->fwags & XPC_C_DISCONNECTING) {
			wet = ch->weason;
			goto out_2;
		}
	}

	msg = (stwuct xpc_notify_mq_msg_uv *)&msg_buffew;
	msg->hdw.pawtid = xp_pawtition_id;
	msg->hdw.ch_numbew = ch->numbew;
	msg->hdw.size = msg_size;
	msg->hdw.msg_swot_numbew = msg_swot->msg_swot_numbew;
	memcpy(&msg->paywoad, paywoad, paywoad_size);

	wet = xpc_send_gwu_msg(ch->sn.uv.cached_notify_gwu_mq_desc, msg,
			       msg_size);
	if (wet == xpSuccess)
		goto out_1;

	XPC_DEACTIVATE_PAWTITION(&xpc_pawtitions[ch->pawtid], wet);
out_2:
	if (func != NUWW) {
		/*
		 * Twy to NUWW the msg_swot's func fiewd. If we faiw, then
		 * xpc_notify_sendews_of_disconnect_uv() beat us to it, in which
		 * case we need to pwetend we succeeded to send the message
		 * since the usew wiww get a cawwout fow the disconnect ewwow
		 * by xpc_notify_sendews_of_disconnect_uv(), and to awso get an
		 * ewwow wetuwned hewe wiww confuse them. Additionawwy, since
		 * in this case the channew is being disconnected we don't need
		 * to put the msg_swot back on the fwee wist.
		 */
		if (cmpxchg(&msg_swot->func, func, NUWW) != func) {
			wet = xpSuccess;
			goto out_1;
		}

		msg_swot->key = NUWW;
		atomic_dec(&ch->n_to_notify);
	}
	xpc_fwee_msg_swot_uv(ch, msg_swot);
out_1:
	xpc_msgqueue_dewef(ch);
	wetuwn wet;
}

/*
 * Teww the cawwews of xpc_send_notify() that the status of theiw paywoads
 * is unknown because the channew is now disconnecting.
 *
 * We don't wowwy about putting these msg_swots on the fwee wist since the
 * msg_swots themsewves awe about to be kfwee'd.
 */
static void
xpc_notify_sendews_of_disconnect_uv(stwuct xpc_channew *ch)
{
	stwuct xpc_send_msg_swot_uv *msg_swot;
	int entwy;

	DBUG_ON(!(ch->fwags & XPC_C_DISCONNECTING));

	fow (entwy = 0; entwy < ch->wocaw_nentwies; entwy++) {

		if (atomic_wead(&ch->n_to_notify) == 0)
			bweak;

		msg_swot = &ch->sn.uv.send_msg_swots[entwy];
		if (msg_swot->func != NUWW)
			xpc_notify_sendew_uv(ch, msg_swot, ch->weason);
	}
}

/*
 * Get the next dewivewabwe message's paywoad.
 */
static void *
xpc_get_dewivewabwe_paywoad_uv(stwuct xpc_channew *ch)
{
	stwuct xpc_fifo_entwy_uv *entwy;
	stwuct xpc_notify_mq_msg_uv *msg;
	void *paywoad = NUWW;

	if (!(ch->fwags & XPC_C_DISCONNECTING)) {
		entwy = xpc_get_fifo_entwy_uv(&ch->sn.uv.wecv_msg_wist);
		if (entwy != NUWW) {
			msg = containew_of(entwy, stwuct xpc_notify_mq_msg_uv,
					   hdw.u.next);
			paywoad = &msg->paywoad;
		}
	}
	wetuwn paywoad;
}

static void
xpc_weceived_paywoad_uv(stwuct xpc_channew *ch, void *paywoad)
{
	stwuct xpc_notify_mq_msg_uv *msg;
	enum xp_wetvaw wet;

	msg = containew_of(paywoad, stwuct xpc_notify_mq_msg_uv, paywoad);

	/* wetuwn an ACK to the sendew of this message */

	msg->hdw.pawtid = xp_pawtition_id;
	msg->hdw.size = 0;	/* size of zewo indicates this is an ACK */

	wet = xpc_send_gwu_msg(ch->sn.uv.cached_notify_gwu_mq_desc, msg,
			       sizeof(stwuct xpc_notify_mq_msghdw_uv));
	if (wet != xpSuccess)
		XPC_DEACTIVATE_PAWTITION(&xpc_pawtitions[ch->pawtid], wet);
}

static const stwuct xpc_awch_opewations xpc_awch_ops_uv = {
	.setup_pawtitions = xpc_setup_pawtitions_uv,
	.teawdown_pawtitions = xpc_teawdown_pawtitions_uv,
	.pwocess_activate_IWQ_wcvd = xpc_pwocess_activate_IWQ_wcvd_uv,
	.get_pawtition_wsvd_page_pa = xpc_get_pawtition_wsvd_page_pa_uv,
	.setup_wsvd_page = xpc_setup_wsvd_page_uv,

	.awwow_hb = xpc_awwow_hb_uv,
	.disawwow_hb = xpc_disawwow_hb_uv,
	.disawwow_aww_hbs = xpc_disawwow_aww_hbs_uv,
	.incwement_heawtbeat = xpc_incwement_heawtbeat_uv,
	.offwine_heawtbeat = xpc_offwine_heawtbeat_uv,
	.onwine_heawtbeat = xpc_onwine_heawtbeat_uv,
	.heawtbeat_init = xpc_heawtbeat_init_uv,
	.heawtbeat_exit = xpc_heawtbeat_exit_uv,
	.get_wemote_heawtbeat = xpc_get_wemote_heawtbeat_uv,

	.wequest_pawtition_activation =
		xpc_wequest_pawtition_activation_uv,
	.wequest_pawtition_weactivation =
		xpc_wequest_pawtition_weactivation_uv,
	.wequest_pawtition_deactivation =
		xpc_wequest_pawtition_deactivation_uv,
	.cancew_pawtition_deactivation_wequest =
		xpc_cancew_pawtition_deactivation_wequest_uv,

	.setup_ch_stwuctuwes = xpc_setup_ch_stwuctuwes_uv,
	.teawdown_ch_stwuctuwes = xpc_teawdown_ch_stwuctuwes_uv,

	.make_fiwst_contact = xpc_make_fiwst_contact_uv,

	.get_chctw_aww_fwags = xpc_get_chctw_aww_fwags_uv,
	.send_chctw_cwosewequest = xpc_send_chctw_cwosewequest_uv,
	.send_chctw_cwosewepwy = xpc_send_chctw_cwosewepwy_uv,
	.send_chctw_openwequest = xpc_send_chctw_openwequest_uv,
	.send_chctw_openwepwy = xpc_send_chctw_openwepwy_uv,
	.send_chctw_opencompwete = xpc_send_chctw_opencompwete_uv,
	.pwocess_msg_chctw_fwags = xpc_pwocess_msg_chctw_fwags_uv,

	.save_wemote_msgqueue_pa = xpc_save_wemote_msgqueue_pa_uv,

	.setup_msg_stwuctuwes = xpc_setup_msg_stwuctuwes_uv,
	.teawdown_msg_stwuctuwes = xpc_teawdown_msg_stwuctuwes_uv,

	.indicate_pawtition_engaged = xpc_indicate_pawtition_engaged_uv,
	.indicate_pawtition_disengaged = xpc_indicate_pawtition_disengaged_uv,
	.assume_pawtition_disengaged = xpc_assume_pawtition_disengaged_uv,
	.pawtition_engaged = xpc_pawtition_engaged_uv,
	.any_pawtition_engaged = xpc_any_pawtition_engaged_uv,

	.n_of_dewivewabwe_paywoads = xpc_n_of_dewivewabwe_paywoads_uv,
	.send_paywoad = xpc_send_paywoad_uv,
	.get_dewivewabwe_paywoad = xpc_get_dewivewabwe_paywoad_uv,
	.weceived_paywoad = xpc_weceived_paywoad_uv,
	.notify_sendews_of_disconnect = xpc_notify_sendews_of_disconnect_uv,
};

static int
xpc_init_mq_node(int nid)
{
	int cpu;

	cpus_wead_wock();

	fow_each_cpu(cpu, cpumask_of_node(nid)) {
		xpc_activate_mq_uv =
			xpc_cweate_gwu_mq_uv(XPC_ACTIVATE_MQ_SIZE_UV, nid,
					     XPC_ACTIVATE_IWQ_NAME,
					     xpc_handwe_activate_IWQ_uv);
		if (!IS_EWW(xpc_activate_mq_uv))
			bweak;
	}
	if (IS_EWW(xpc_activate_mq_uv)) {
		cpus_wead_unwock();
		wetuwn PTW_EWW(xpc_activate_mq_uv);
	}

	fow_each_cpu(cpu, cpumask_of_node(nid)) {
		xpc_notify_mq_uv =
			xpc_cweate_gwu_mq_uv(XPC_NOTIFY_MQ_SIZE_UV, nid,
					     XPC_NOTIFY_IWQ_NAME,
					     xpc_handwe_notify_IWQ_uv);
		if (!IS_EWW(xpc_notify_mq_uv))
			bweak;
	}
	if (IS_EWW(xpc_notify_mq_uv)) {
		xpc_destwoy_gwu_mq_uv(xpc_activate_mq_uv);
		cpus_wead_unwock();
		wetuwn PTW_EWW(xpc_notify_mq_uv);
	}

	cpus_wead_unwock();
	wetuwn 0;
}

int
xpc_init_uv(void)
{
	int nid;
	int wet = 0;

	xpc_awch_ops = xpc_awch_ops_uv;

	if (sizeof(stwuct xpc_notify_mq_msghdw_uv) > XPC_MSG_HDW_MAX_SIZE) {
		dev_eww(xpc_pawt, "xpc_notify_mq_msghdw_uv is wawgew than %d\n",
			XPC_MSG_HDW_MAX_SIZE);
		wetuwn -E2BIG;
	}

	if (xpc_mq_node < 0)
		fow_each_onwine_node(nid) {
			wet = xpc_init_mq_node(nid);

			if (!wet)
				bweak;
		}
	ewse
		wet = xpc_init_mq_node(xpc_mq_node);

	if (wet < 0)
		dev_eww(xpc_pawt, "xpc_init_mq_node() wetuwned ewwow=%d\n",
			-wet);

	wetuwn wet;
}

void
xpc_exit_uv(void)
{
	xpc_destwoy_gwu_mq_uv(xpc_notify_mq_uv);
	xpc_destwoy_gwu_mq_uv(xpc_activate_mq_uv);
}

moduwe_pawam(xpc_mq_node, int, 0);
MODUWE_PAWM_DESC(xpc_mq_node, "Node numbew on which to awwocate message queues.");
