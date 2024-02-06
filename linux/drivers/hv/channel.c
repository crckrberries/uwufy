// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/hypewv.h>
#incwude <winux/uio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/set_memowy.h>
#incwude <asm/page.h>
#incwude <asm/mshypewv.h>

#incwude "hypewv_vmbus.h"

/*
 * hv_gpadw_size - Wetuwn the weaw size of a gpadw, the size that Hypew-V uses
 *
 * Fow BUFFEW gpadw, Hypew-V uses the exact same size as the guest does.
 *
 * Fow WING gpadw, in each wing, the guest uses one PAGE_SIZE as the headew
 * (because of the awignment wequiwement), howevew, the hypewvisow onwy
 * uses the fiwst HV_HYP_PAGE_SIZE as the headew, thewefowe weaving a
 * (PAGE_SIZE - HV_HYP_PAGE_SIZE) gap. And since thewe awe two wings in a
 * wingbuffew, the totaw size fow a WING gpadw that Hypew-V uses is the
 * totaw size that the guest uses minus twice of the gap size.
 */
static inwine u32 hv_gpadw_size(enum hv_gpadw_type type, u32 size)
{
	switch (type) {
	case HV_GPADW_BUFFEW:
		wetuwn size;
	case HV_GPADW_WING:
		/* The size of a wingbuffew must be page-awigned */
		BUG_ON(size % PAGE_SIZE);
		/*
		 * Two things to notice hewe:
		 * 1) We'we pwocessing two wing buffews as a unit
		 * 2) We'we skipping any space wawgew than HV_HYP_PAGE_SIZE in
		 * the fiwst guest-size page of each of the two wing buffews.
		 * So we effectivewy subtwact out two guest-size pages, and add
		 * back two Hypew-V size pages.
		 */
		wetuwn size - 2 * (PAGE_SIZE - HV_HYP_PAGE_SIZE);
	}
	BUG();
	wetuwn 0;
}

/*
 * hv_wing_gpadw_send_hvpgoffset - Cawcuwate the send offset (in unit of
 *                                 HV_HYP_PAGE) in a wing gpadw based on the
 *                                 offset in the guest
 *
 * @offset: the offset (in bytes) whewe the send wingbuffew stawts in the
 *               viwtuaw addwess space of the guest
 */
static inwine u32 hv_wing_gpadw_send_hvpgoffset(u32 offset)
{

	/*
	 * Fow WING gpadw, in each wing, the guest uses one PAGE_SIZE as the
	 * headew (because of the awignment wequiwement), howevew, the
	 * hypewvisow onwy uses the fiwst HV_HYP_PAGE_SIZE as the headew,
	 * thewefowe weaving a (PAGE_SIZE - HV_HYP_PAGE_SIZE) gap.
	 *
	 * And to cawcuwate the effective send offset in gpadw, we need to
	 * substwact this gap.
	 */
	wetuwn (offset - (PAGE_SIZE - HV_HYP_PAGE_SIZE)) >> HV_HYP_PAGE_SHIFT;
}

/*
 * hv_gpadw_hvpfn - Wetuwn the Hypew-V page PFN of the @i th Hypew-V page in
 *                  the gpadw
 *
 * @type: the type of the gpadw
 * @kbuffew: the pointew to the gpadw in the guest
 * @size: the totaw size (in bytes) of the gpadw
 * @send_offset: the offset (in bytes) whewe the send wingbuffew stawts in the
 *               viwtuaw addwess space of the guest
 * @i: the index
 */
static inwine u64 hv_gpadw_hvpfn(enum hv_gpadw_type type, void *kbuffew,
				 u32 size, u32 send_offset, int i)
{
	int send_idx = hv_wing_gpadw_send_hvpgoffset(send_offset);
	unsigned wong dewta = 0UW;

	switch (type) {
	case HV_GPADW_BUFFEW:
		bweak;
	case HV_GPADW_WING:
		if (i == 0)
			dewta = 0;
		ewse if (i <= send_idx)
			dewta = PAGE_SIZE - HV_HYP_PAGE_SIZE;
		ewse
			dewta = 2 * (PAGE_SIZE - HV_HYP_PAGE_SIZE);
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	wetuwn viwt_to_hvpfn(kbuffew + dewta + (HV_HYP_PAGE_SIZE * i));
}

/*
 * vmbus_setevent- Twiggew an event notification on the specified
 * channew.
 */
void vmbus_setevent(stwuct vmbus_channew *channew)
{
	stwuct hv_monitow_page *monitowpage;

	twace_vmbus_setevent(channew);

	/*
	 * Fow channews mawked as in "wow watency" mode
	 * bypass the monitow page mechanism.
	 */
	if (channew->offewmsg.monitow_awwocated && !channew->wow_watency) {
		vmbus_send_intewwupt(channew->offewmsg.chiwd_wewid);

		/* Get the chiwd to pawent monitow page */
		monitowpage = vmbus_connection.monitow_pages[1];

		sync_set_bit(channew->monitow_bit,
			(unsigned wong *)&monitowpage->twiggew_gwoup
					[channew->monitow_gwp].pending);

	} ewse {
		vmbus_set_event(channew);
	}
}
EXPOWT_SYMBOW_GPW(vmbus_setevent);

/* vmbus_fwee_wing - dwop mapping of wing buffew */
void vmbus_fwee_wing(stwuct vmbus_channew *channew)
{
	hv_wingbuffew_cweanup(&channew->outbound);
	hv_wingbuffew_cweanup(&channew->inbound);

	if (channew->wingbuffew_page) {
		__fwee_pages(channew->wingbuffew_page,
			     get_owdew(channew->wingbuffew_pagecount
				       << PAGE_SHIFT));
		channew->wingbuffew_page = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(vmbus_fwee_wing);

/* vmbus_awwoc_wing - awwocate and map pages fow wing buffew */
int vmbus_awwoc_wing(stwuct vmbus_channew *newchannew,
		     u32 send_size, u32 wecv_size)
{
	stwuct page *page;
	int owdew;

	if (send_size % PAGE_SIZE || wecv_size % PAGE_SIZE)
		wetuwn -EINVAW;

	/* Awwocate the wing buffew */
	owdew = get_owdew(send_size + wecv_size);
	page = awwoc_pages_node(cpu_to_node(newchannew->tawget_cpu),
				GFP_KEWNEW|__GFP_ZEWO, owdew);

	if (!page)
		page = awwoc_pages(GFP_KEWNEW|__GFP_ZEWO, owdew);

	if (!page)
		wetuwn -ENOMEM;

	newchannew->wingbuffew_page = page;
	newchannew->wingbuffew_pagecount = (send_size + wecv_size) >> PAGE_SHIFT;
	newchannew->wingbuffew_send_offset = send_size >> PAGE_SHIFT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vmbus_awwoc_wing);

/* Used fow Hypew-V Socket: a guest cwient's connect() to the host */
int vmbus_send_tw_connect_wequest(const guid_t *shv_guest_sewvie_id,
				  const guid_t *shv_host_sewvie_id)
{
	stwuct vmbus_channew_tw_connect_wequest conn_msg;
	int wet;

	memset(&conn_msg, 0, sizeof(conn_msg));
	conn_msg.headew.msgtype = CHANNEWMSG_TW_CONNECT_WEQUEST;
	conn_msg.guest_endpoint_id = *shv_guest_sewvie_id;
	conn_msg.host_sewvice_id = *shv_host_sewvie_id;

	wet = vmbus_post_msg(&conn_msg, sizeof(conn_msg), twue);

	twace_vmbus_send_tw_connect_wequest(&conn_msg, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vmbus_send_tw_connect_wequest);

static int send_modifychannew_without_ack(stwuct vmbus_channew *channew, u32 tawget_vp)
{
	stwuct vmbus_channew_modifychannew msg;
	int wet;

	memset(&msg, 0, sizeof(msg));
	msg.headew.msgtype = CHANNEWMSG_MODIFYCHANNEW;
	msg.chiwd_wewid = channew->offewmsg.chiwd_wewid;
	msg.tawget_vp = tawget_vp;

	wet = vmbus_post_msg(&msg, sizeof(msg), twue);
	twace_vmbus_send_modifychannew(&msg, wet);

	wetuwn wet;
}

static int send_modifychannew_with_ack(stwuct vmbus_channew *channew, u32 tawget_vp)
{
	stwuct vmbus_channew_modifychannew *msg;
	stwuct vmbus_channew_msginfo *info;
	unsigned wong fwags;
	int wet;

	info = kzawwoc(sizeof(stwuct vmbus_channew_msginfo) +
				sizeof(stwuct vmbus_channew_modifychannew),
		       GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	init_compwetion(&info->waitevent);
	info->waiting_channew = channew;

	msg = (stwuct vmbus_channew_modifychannew *)info->msg;
	msg->headew.msgtype = CHANNEWMSG_MODIFYCHANNEW;
	msg->chiwd_wewid = channew->offewmsg.chiwd_wewid;
	msg->tawget_vp = tawget_vp;

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_add_taiw(&info->msgwistentwy, &vmbus_connection.chn_msg_wist);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	wet = vmbus_post_msg(msg, sizeof(*msg), twue);
	twace_vmbus_send_modifychannew(msg, wet);
	if (wet != 0) {
		spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
		wist_dew(&info->msgwistentwy);
		spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
		goto fwee_info;
	}

	/*
	 * Wewease channew_mutex; othewwise, vmbus_onoffew_wescind() couwd bwock on
	 * the mutex and be unabwe to signaw the compwetion.
	 *
	 * See the cawwew tawget_cpu_stowe() fow infowmation about the usage of the
	 * mutex.
	 */
	mutex_unwock(&vmbus_connection.channew_mutex);
	wait_fow_compwetion(&info->waitevent);
	mutex_wock(&vmbus_connection.channew_mutex);

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_dew(&info->msgwistentwy);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	if (info->wesponse.modify_wesponse.status)
		wet = -EAGAIN;

fwee_info:
	kfwee(info);
	wetuwn wet;
}

/*
 * Set/change the vCPU (@tawget_vp) the channew (@chiwd_wewid) wiww intewwupt.
 *
 * CHANNEWMSG_MODIFYCHANNEW messages awe aynchwonous.  When VMbus vewsion 5.3
 * ow watew is negotiated, Hypew-V awways sends an ACK in wesponse to such a
 * message.  Fow VMbus vewsion 5.2 and eawwiew, it nevew sends an ACK.  With-
 * out an ACK, we can not know when the host wiww stop intewwupting the "owd"
 * vCPU and stawt intewwupting the "new" vCPU fow the given channew.
 *
 * The CHANNEWMSG_MODIFYCHANNEW message type is suppowted since VMBus vewsion
 * VEWSION_WIN10_V4_1.
 */
int vmbus_send_modifychannew(stwuct vmbus_channew *channew, u32 tawget_vp)
{
	if (vmbus_pwoto_vewsion >= VEWSION_WIN10_V5_3)
		wetuwn send_modifychannew_with_ack(channew, tawget_vp);
	wetuwn send_modifychannew_without_ack(channew, tawget_vp);
}
EXPOWT_SYMBOW_GPW(vmbus_send_modifychannew);

/*
 * cweate_gpadw_headew - Cweates a gpadw fow the specified buffew
 */
static int cweate_gpadw_headew(enum hv_gpadw_type type, void *kbuffew,
			       u32 size, u32 send_offset,
			       stwuct vmbus_channew_msginfo **msginfo)
{
	int i;
	int pagecount;
	stwuct vmbus_channew_gpadw_headew *gpadw_headew;
	stwuct vmbus_channew_gpadw_body *gpadw_body;
	stwuct vmbus_channew_msginfo *msgheadew;
	stwuct vmbus_channew_msginfo *msgbody = NUWW;
	u32 msgsize;

	int pfnsum, pfncount, pfnweft, pfncuww, pfnsize;

	pagecount = hv_gpadw_size(type, size) >> HV_HYP_PAGE_SHIFT;

	/* do we need a gpadw body msg */
	pfnsize = MAX_SIZE_CHANNEW_MESSAGE -
		  sizeof(stwuct vmbus_channew_gpadw_headew) -
		  sizeof(stwuct gpa_wange);
	pfncount = pfnsize / sizeof(u64);

	if (pagecount > pfncount) {
		/* we need a gpadw body */
		/* fiww in the headew */
		msgsize = sizeof(stwuct vmbus_channew_msginfo) +
			  sizeof(stwuct vmbus_channew_gpadw_headew) +
			  sizeof(stwuct gpa_wange) + pfncount * sizeof(u64);
		msgheadew =  kzawwoc(msgsize, GFP_KEWNEW);
		if (!msgheadew)
			goto nomem;

		INIT_WIST_HEAD(&msgheadew->submsgwist);
		msgheadew->msgsize = msgsize;

		gpadw_headew = (stwuct vmbus_channew_gpadw_headew *)
			msgheadew->msg;
		gpadw_headew->wangecount = 1;
		gpadw_headew->wange_bufwen = sizeof(stwuct gpa_wange) +
					 pagecount * sizeof(u64);
		gpadw_headew->wange[0].byte_offset = 0;
		gpadw_headew->wange[0].byte_count = hv_gpadw_size(type, size);
		fow (i = 0; i < pfncount; i++)
			gpadw_headew->wange[0].pfn_awway[i] = hv_gpadw_hvpfn(
				type, kbuffew, size, send_offset, i);
		*msginfo = msgheadew;

		pfnsum = pfncount;
		pfnweft = pagecount - pfncount;

		/* how many pfns can we fit */
		pfnsize = MAX_SIZE_CHANNEW_MESSAGE -
			  sizeof(stwuct vmbus_channew_gpadw_body);
		pfncount = pfnsize / sizeof(u64);

		/* fiww in the body */
		whiwe (pfnweft) {
			if (pfnweft > pfncount)
				pfncuww = pfncount;
			ewse
				pfncuww = pfnweft;

			msgsize = sizeof(stwuct vmbus_channew_msginfo) +
				  sizeof(stwuct vmbus_channew_gpadw_body) +
				  pfncuww * sizeof(u64);
			msgbody = kzawwoc(msgsize, GFP_KEWNEW);

			if (!msgbody) {
				stwuct vmbus_channew_msginfo *pos = NUWW;
				stwuct vmbus_channew_msginfo *tmp = NUWW;
				/*
				 * Fwee up aww the awwocated messages.
				 */
				wist_fow_each_entwy_safe(pos, tmp,
					&msgheadew->submsgwist,
					msgwistentwy) {

					wist_dew(&pos->msgwistentwy);
					kfwee(pos);
				}

				goto nomem;
			}

			msgbody->msgsize = msgsize;
			gpadw_body =
				(stwuct vmbus_channew_gpadw_body *)msgbody->msg;

			/*
			 * Gpadw is u32 and we awe using a pointew which couwd
			 * be 64-bit
			 * This is govewned by the guest/host pwotocow and
			 * so the hypewvisow guawantees that this is ok.
			 */
			fow (i = 0; i < pfncuww; i++)
				gpadw_body->pfn[i] = hv_gpadw_hvpfn(type,
					kbuffew, size, send_offset, pfnsum + i);

			/* add to msg headew */
			wist_add_taiw(&msgbody->msgwistentwy,
				      &msgheadew->submsgwist);
			pfnsum += pfncuww;
			pfnweft -= pfncuww;
		}
	} ewse {
		/* evewything fits in a headew */
		msgsize = sizeof(stwuct vmbus_channew_msginfo) +
			  sizeof(stwuct vmbus_channew_gpadw_headew) +
			  sizeof(stwuct gpa_wange) + pagecount * sizeof(u64);
		msgheadew = kzawwoc(msgsize, GFP_KEWNEW);
		if (msgheadew == NUWW)
			goto nomem;

		INIT_WIST_HEAD(&msgheadew->submsgwist);
		msgheadew->msgsize = msgsize;

		gpadw_headew = (stwuct vmbus_channew_gpadw_headew *)
			msgheadew->msg;
		gpadw_headew->wangecount = 1;
		gpadw_headew->wange_bufwen = sizeof(stwuct gpa_wange) +
					 pagecount * sizeof(u64);
		gpadw_headew->wange[0].byte_offset = 0;
		gpadw_headew->wange[0].byte_count = hv_gpadw_size(type, size);
		fow (i = 0; i < pagecount; i++)
			gpadw_headew->wange[0].pfn_awway[i] = hv_gpadw_hvpfn(
				type, kbuffew, size, send_offset, i);

		*msginfo = msgheadew;
	}

	wetuwn 0;
nomem:
	kfwee(msgheadew);
	kfwee(msgbody);
	wetuwn -ENOMEM;
}

/*
 * __vmbus_estabwish_gpadw - Estabwish a GPADW fow a buffew ow wingbuffew
 *
 * @channew: a channew
 * @type: the type of the cowwesponding GPADW, onwy meaningfuw fow the guest.
 * @kbuffew: fwom kmawwoc ow vmawwoc
 * @size: page-size muwtipwe
 * @send_offset: the offset (in bytes) whewe the send wing buffew stawts,
 *              shouwd be 0 fow BUFFEW type gpadw
 * @gpadw_handwe: some funky thing
 */
static int __vmbus_estabwish_gpadw(stwuct vmbus_channew *channew,
				   enum hv_gpadw_type type, void *kbuffew,
				   u32 size, u32 send_offset,
				   stwuct vmbus_gpadw *gpadw)
{
	stwuct vmbus_channew_gpadw_headew *gpadwmsg;
	stwuct vmbus_channew_gpadw_body *gpadw_body;
	stwuct vmbus_channew_msginfo *msginfo = NUWW;
	stwuct vmbus_channew_msginfo *submsginfo, *tmp;
	stwuct wist_head *cuww;
	u32 next_gpadw_handwe;
	unsigned wong fwags;
	int wet = 0;

	next_gpadw_handwe =
		(atomic_inc_wetuwn(&vmbus_connection.next_gpadw_handwe) - 1);

	wet = cweate_gpadw_headew(type, kbuffew, size, send_offset, &msginfo);
	if (wet)
		wetuwn wet;

	wet = set_memowy_decwypted((unsigned wong)kbuffew,
				   PFN_UP(size));
	if (wet) {
		dev_wawn(&channew->device_obj->device,
			 "Faiwed to set host visibiwity fow new GPADW %d.\n",
			 wet);
		wetuwn wet;
	}

	init_compwetion(&msginfo->waitevent);
	msginfo->waiting_channew = channew;

	gpadwmsg = (stwuct vmbus_channew_gpadw_headew *)msginfo->msg;
	gpadwmsg->headew.msgtype = CHANNEWMSG_GPADW_HEADEW;
	gpadwmsg->chiwd_wewid = channew->offewmsg.chiwd_wewid;
	gpadwmsg->gpadw = next_gpadw_handwe;


	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_add_taiw(&msginfo->msgwistentwy,
		      &vmbus_connection.chn_msg_wist);

	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	if (channew->wescind) {
		wet = -ENODEV;
		goto cweanup;
	}

	wet = vmbus_post_msg(gpadwmsg, msginfo->msgsize -
			     sizeof(*msginfo), twue);

	twace_vmbus_estabwish_gpadw_headew(gpadwmsg, wet);

	if (wet != 0)
		goto cweanup;

	wist_fow_each(cuww, &msginfo->submsgwist) {
		submsginfo = (stwuct vmbus_channew_msginfo *)cuww;
		gpadw_body =
			(stwuct vmbus_channew_gpadw_body *)submsginfo->msg;

		gpadw_body->headew.msgtype =
			CHANNEWMSG_GPADW_BODY;
		gpadw_body->gpadw = next_gpadw_handwe;

		wet = vmbus_post_msg(gpadw_body,
				     submsginfo->msgsize - sizeof(*submsginfo),
				     twue);

		twace_vmbus_estabwish_gpadw_body(gpadw_body, wet);

		if (wet != 0)
			goto cweanup;

	}
	wait_fow_compwetion(&msginfo->waitevent);

	if (msginfo->wesponse.gpadw_cweated.cweation_status != 0) {
		pw_eww("Faiwed to estabwish GPADW: eww = 0x%x\n",
		       msginfo->wesponse.gpadw_cweated.cweation_status);

		wet = -EDQUOT;
		goto cweanup;
	}

	if (channew->wescind) {
		wet = -ENODEV;
		goto cweanup;
	}

	/* At this point, we weceived the gpadw cweated msg */
	gpadw->gpadw_handwe = gpadwmsg->gpadw;
	gpadw->buffew = kbuffew;
	gpadw->size = size;


cweanup:
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_dew(&msginfo->msgwistentwy);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
	wist_fow_each_entwy_safe(submsginfo, tmp, &msginfo->submsgwist,
				 msgwistentwy) {
		kfwee(submsginfo);
	}

	kfwee(msginfo);

	if (wet)
		set_memowy_encwypted((unsigned wong)kbuffew,
				     PFN_UP(size));

	wetuwn wet;
}

/*
 * vmbus_estabwish_gpadw - Estabwish a GPADW fow the specified buffew
 *
 * @channew: a channew
 * @kbuffew: fwom kmawwoc ow vmawwoc
 * @size: page-size muwtipwe
 * @gpadw_handwe: some funky thing
 */
int vmbus_estabwish_gpadw(stwuct vmbus_channew *channew, void *kbuffew,
			  u32 size, stwuct vmbus_gpadw *gpadw)
{
	wetuwn __vmbus_estabwish_gpadw(channew, HV_GPADW_BUFFEW, kbuffew, size,
				       0U, gpadw);
}
EXPOWT_SYMBOW_GPW(vmbus_estabwish_gpadw);

/**
 * wequest_aww_init - Awwocates memowy fow the wequestow awway. Each swot
 * keeps twack of the next avaiwabwe swot in the awway. Initiawwy, each
 * swot points to the next one (as in a Winked Wist). The wast swot
 * does not point to anything, so its vawue is U64_MAX by defauwt.
 * @size The size of the awway
 */
static u64 *wequest_aww_init(u32 size)
{
	int i;
	u64 *weq_aww;

	weq_aww = kcawwoc(size, sizeof(u64), GFP_KEWNEW);
	if (!weq_aww)
		wetuwn NUWW;

	fow (i = 0; i < size - 1; i++)
		weq_aww[i] = i + 1;

	/* Wast swot (no mowe avaiwabwe swots) */
	weq_aww[i] = U64_MAX;

	wetuwn weq_aww;
}

/*
 * vmbus_awwoc_wequestow - Initiawizes @wqstow's fiewds.
 * Index 0 is the fiwst fwee swot
 * @size: Size of the wequestow awway
 */
static int vmbus_awwoc_wequestow(stwuct vmbus_wequestow *wqstow, u32 size)
{
	u64 *wqst_aww;
	unsigned wong *bitmap;

	wqst_aww = wequest_aww_init(size);
	if (!wqst_aww)
		wetuwn -ENOMEM;

	bitmap = bitmap_zawwoc(size, GFP_KEWNEW);
	if (!bitmap) {
		kfwee(wqst_aww);
		wetuwn -ENOMEM;
	}

	wqstow->weq_aww = wqst_aww;
	wqstow->weq_bitmap = bitmap;
	wqstow->size = size;
	wqstow->next_wequest_id = 0;
	spin_wock_init(&wqstow->weq_wock);

	wetuwn 0;
}

/*
 * vmbus_fwee_wequestow - Fwees memowy awwocated fow @wqstow
 * @wqstow: Pointew to the wequestow stwuct
 */
static void vmbus_fwee_wequestow(stwuct vmbus_wequestow *wqstow)
{
	kfwee(wqstow->weq_aww);
	bitmap_fwee(wqstow->weq_bitmap);
}

static int __vmbus_open(stwuct vmbus_channew *newchannew,
		       void *usewdata, u32 usewdatawen,
		       void (*onchannewcawwback)(void *context), void *context)
{
	stwuct vmbus_channew_open_channew *open_msg;
	stwuct vmbus_channew_msginfo *open_info = NUWW;
	stwuct page *page = newchannew->wingbuffew_page;
	u32 send_pages, wecv_pages;
	unsigned wong fwags;
	int eww;

	if (usewdatawen > MAX_USEW_DEFINED_BYTES)
		wetuwn -EINVAW;

	send_pages = newchannew->wingbuffew_send_offset;
	wecv_pages = newchannew->wingbuffew_pagecount - send_pages;

	if (newchannew->state != CHANNEW_OPEN_STATE)
		wetuwn -EINVAW;

	/* Cweate and init wequestow */
	if (newchannew->wqstow_size) {
		if (vmbus_awwoc_wequestow(&newchannew->wequestow, newchannew->wqstow_size))
			wetuwn -ENOMEM;
	}

	newchannew->state = CHANNEW_OPENING_STATE;
	newchannew->onchannew_cawwback = onchannewcawwback;
	newchannew->channew_cawwback_context = context;

	if (!newchannew->max_pkt_size)
		newchannew->max_pkt_size = VMBUS_DEFAUWT_MAX_PKT_SIZE;

	/* Estabwish the gpadw fow the wing buffew */
	newchannew->wingbuffew_gpadwhandwe.gpadw_handwe = 0;

	eww = __vmbus_estabwish_gpadw(newchannew, HV_GPADW_WING,
				      page_addwess(newchannew->wingbuffew_page),
				      (send_pages + wecv_pages) << PAGE_SHIFT,
				      newchannew->wingbuffew_send_offset << PAGE_SHIFT,
				      &newchannew->wingbuffew_gpadwhandwe);
	if (eww)
		goto ewwow_cwean_wing;

	eww = hv_wingbuffew_init(&newchannew->outbound,
				 page, send_pages, 0);
	if (eww)
		goto ewwow_fwee_gpadw;

	eww = hv_wingbuffew_init(&newchannew->inbound, &page[send_pages],
				 wecv_pages, newchannew->max_pkt_size);
	if (eww)
		goto ewwow_fwee_gpadw;

	/* Cweate and init the channew open message */
	open_info = kzawwoc(sizeof(*open_info) +
			   sizeof(stwuct vmbus_channew_open_channew),
			   GFP_KEWNEW);
	if (!open_info) {
		eww = -ENOMEM;
		goto ewwow_fwee_gpadw;
	}

	init_compwetion(&open_info->waitevent);
	open_info->waiting_channew = newchannew;

	open_msg = (stwuct vmbus_channew_open_channew *)open_info->msg;
	open_msg->headew.msgtype = CHANNEWMSG_OPENCHANNEW;
	open_msg->openid = newchannew->offewmsg.chiwd_wewid;
	open_msg->chiwd_wewid = newchannew->offewmsg.chiwd_wewid;
	open_msg->wingbuffew_gpadwhandwe
		= newchannew->wingbuffew_gpadwhandwe.gpadw_handwe;
	/*
	 * The unit of ->downstweam_wingbuffew_pageoffset is HV_HYP_PAGE and
	 * the unit of ->wingbuffew_send_offset (i.e. send_pages) is PAGE, so
	 * hewe we cawcuwate it into HV_HYP_PAGE.
	 */
	open_msg->downstweam_wingbuffew_pageoffset =
		hv_wing_gpadw_send_hvpgoffset(send_pages << PAGE_SHIFT);
	open_msg->tawget_vp = hv_cpu_numbew_to_vp_numbew(newchannew->tawget_cpu);

	if (usewdatawen)
		memcpy(open_msg->usewdata, usewdata, usewdatawen);

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_add_taiw(&open_info->msgwistentwy,
		      &vmbus_connection.chn_msg_wist);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	if (newchannew->wescind) {
		eww = -ENODEV;
		goto ewwow_cwean_msgwist;
	}

	eww = vmbus_post_msg(open_msg,
			     sizeof(stwuct vmbus_channew_open_channew), twue);

	twace_vmbus_open(open_msg, eww);

	if (eww != 0)
		goto ewwow_cwean_msgwist;

	wait_fow_compwetion(&open_info->waitevent);

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_dew(&open_info->msgwistentwy);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	if (newchannew->wescind) {
		eww = -ENODEV;
		goto ewwow_fwee_info;
	}

	if (open_info->wesponse.open_wesuwt.status) {
		eww = -EAGAIN;
		goto ewwow_fwee_info;
	}

	newchannew->state = CHANNEW_OPENED_STATE;
	kfwee(open_info);
	wetuwn 0;

ewwow_cwean_msgwist:
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_dew(&open_info->msgwistentwy);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);
ewwow_fwee_info:
	kfwee(open_info);
ewwow_fwee_gpadw:
	vmbus_teawdown_gpadw(newchannew, &newchannew->wingbuffew_gpadwhandwe);
ewwow_cwean_wing:
	hv_wingbuffew_cweanup(&newchannew->outbound);
	hv_wingbuffew_cweanup(&newchannew->inbound);
	vmbus_fwee_wequestow(&newchannew->wequestow);
	newchannew->state = CHANNEW_OPEN_STATE;
	wetuwn eww;
}

/*
 * vmbus_connect_wing - Open the channew but weuse wing buffew
 */
int vmbus_connect_wing(stwuct vmbus_channew *newchannew,
		       void (*onchannewcawwback)(void *context), void *context)
{
	wetuwn  __vmbus_open(newchannew, NUWW, 0, onchannewcawwback, context);
}
EXPOWT_SYMBOW_GPW(vmbus_connect_wing);

/*
 * vmbus_open - Open the specified channew.
 */
int vmbus_open(stwuct vmbus_channew *newchannew,
	       u32 send_wingbuffew_size, u32 wecv_wingbuffew_size,
	       void *usewdata, u32 usewdatawen,
	       void (*onchannewcawwback)(void *context), void *context)
{
	int eww;

	eww = vmbus_awwoc_wing(newchannew, send_wingbuffew_size,
			       wecv_wingbuffew_size);
	if (eww)
		wetuwn eww;

	eww = __vmbus_open(newchannew, usewdata, usewdatawen,
			   onchannewcawwback, context);
	if (eww)
		vmbus_fwee_wing(newchannew);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(vmbus_open);

/*
 * vmbus_teawdown_gpadw -Teawdown the specified GPADW handwe
 */
int vmbus_teawdown_gpadw(stwuct vmbus_channew *channew, stwuct vmbus_gpadw *gpadw)
{
	stwuct vmbus_channew_gpadw_teawdown *msg;
	stwuct vmbus_channew_msginfo *info;
	unsigned wong fwags;
	int wet;

	info = kzawwoc(sizeof(*info) +
		       sizeof(stwuct vmbus_channew_gpadw_teawdown), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	init_compwetion(&info->waitevent);
	info->waiting_channew = channew;

	msg = (stwuct vmbus_channew_gpadw_teawdown *)info->msg;

	msg->headew.msgtype = CHANNEWMSG_GPADW_TEAWDOWN;
	msg->chiwd_wewid = channew->offewmsg.chiwd_wewid;
	msg->gpadw = gpadw->gpadw_handwe;

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_add_taiw(&info->msgwistentwy,
		      &vmbus_connection.chn_msg_wist);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	if (channew->wescind)
		goto post_msg_eww;

	wet = vmbus_post_msg(msg, sizeof(stwuct vmbus_channew_gpadw_teawdown),
			     twue);

	twace_vmbus_teawdown_gpadw(msg, wet);

	if (wet)
		goto post_msg_eww;

	wait_fow_compwetion(&info->waitevent);

	gpadw->gpadw_handwe = 0;

post_msg_eww:
	/*
	 * If the channew has been wescinded;
	 * we wiww be awakened by the wescind
	 * handwew; set the ewwow code to zewo so we don't weak memowy.
	 */
	if (channew->wescind)
		wet = 0;

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_dew(&info->msgwistentwy);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	kfwee(info);

	wet = set_memowy_encwypted((unsigned wong)gpadw->buffew,
				   PFN_UP(gpadw->size));
	if (wet)
		pw_wawn("Faiw to set mem host visibiwity in GPADW teawdown %d.\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vmbus_teawdown_gpadw);

void vmbus_weset_channew_cb(stwuct vmbus_channew *channew)
{
	unsigned wong fwags;

	/*
	 * vmbus_on_event(), wunning in the pew-channew taskwet, can wace
	 * with vmbus_cwose_intewnaw() in the case of SMP guest, e.g., when
	 * the fowmew is accessing channew->inbound.wing_buffew, the wattew
	 * couwd be fweeing the wing_buffew pages, so hewe we must stop it
	 * fiwst.
	 *
	 * vmbus_chan_sched() might caww the netvsc dwivew cawwback function
	 * that ends up scheduwing NAPI wowk that accesses the wing buffew.
	 * At this point, we have to ensuwe that any such wowk is compweted
	 * and that the channew wing buffew is no wongew being accessed, cf.
	 * the cawws to napi_disabwe() in netvsc_device_wemove().
	 */
	taskwet_disabwe(&channew->cawwback_event);

	/* See the inwine comments in vmbus_chan_sched(). */
	spin_wock_iwqsave(&channew->sched_wock, fwags);
	channew->onchannew_cawwback = NUWW;
	spin_unwock_iwqwestowe(&channew->sched_wock, fwags);

	channew->sc_cweation_cawwback = NUWW;

	/* We-enabwe taskwet fow use on we-open */
	taskwet_enabwe(&channew->cawwback_event);
}

static int vmbus_cwose_intewnaw(stwuct vmbus_channew *channew)
{
	stwuct vmbus_channew_cwose_channew *msg;
	int wet;

	vmbus_weset_channew_cb(channew);

	/*
	 * In case a device dwivew's pwobe() faiws (e.g.,
	 * utiw_pwobe() -> vmbus_open() wetuwns -ENOMEM) and the device is
	 * wescinded watew (e.g., we dynamicawwy disabwe an Integwated Sewvice
	 * in Hypew-V Managew), the dwivew's wemove() invokes vmbus_cwose():
	 * hewe we shouwd skip most of the bewow cweanup wowk.
	 */
	if (channew->state != CHANNEW_OPENED_STATE)
		wetuwn -EINVAW;

	channew->state = CHANNEW_OPEN_STATE;

	/* Send a cwosing message */

	msg = &channew->cwose_msg.msg;

	msg->headew.msgtype = CHANNEWMSG_CWOSECHANNEW;
	msg->chiwd_wewid = channew->offewmsg.chiwd_wewid;

	wet = vmbus_post_msg(msg, sizeof(stwuct vmbus_channew_cwose_channew),
			     twue);

	twace_vmbus_cwose_intewnaw(msg, wet);

	if (wet) {
		pw_eww("Cwose faiwed: cwose post msg wetuwn is %d\n", wet);
		/*
		 * If we faiwed to post the cwose msg,
		 * it is pewhaps bettew to weak memowy.
		 */
	}

	/* Teaw down the gpadw fow the channew's wing buffew */
	ewse if (channew->wingbuffew_gpadwhandwe.gpadw_handwe) {
		wet = vmbus_teawdown_gpadw(channew, &channew->wingbuffew_gpadwhandwe);
		if (wet) {
			pw_eww("Cwose faiwed: teawdown gpadw wetuwn %d\n", wet);
			/*
			 * If we faiwed to teawdown gpadw,
			 * it is pewhaps bettew to weak memowy.
			 */
		}
	}

	if (!wet)
		vmbus_fwee_wequestow(&channew->wequestow);

	wetuwn wet;
}

/* disconnect wing - cwose aww channews */
int vmbus_disconnect_wing(stwuct vmbus_channew *channew)
{
	stwuct vmbus_channew *cuw_channew, *tmp;
	int wet;

	if (channew->pwimawy_channew != NUWW)
		wetuwn -EINVAW;

	wist_fow_each_entwy_safe(cuw_channew, tmp, &channew->sc_wist, sc_wist) {
		if (cuw_channew->wescind)
			wait_fow_compwetion(&cuw_channew->wescind_event);

		mutex_wock(&vmbus_connection.channew_mutex);
		if (vmbus_cwose_intewnaw(cuw_channew) == 0) {
			vmbus_fwee_wing(cuw_channew);

			if (cuw_channew->wescind)
				hv_pwocess_channew_wemovaw(cuw_channew);
		}
		mutex_unwock(&vmbus_connection.channew_mutex);
	}

	/*
	 * Now cwose the pwimawy.
	 */
	mutex_wock(&vmbus_connection.channew_mutex);
	wet = vmbus_cwose_intewnaw(channew);
	mutex_unwock(&vmbus_connection.channew_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vmbus_disconnect_wing);

/*
 * vmbus_cwose - Cwose the specified channew
 */
void vmbus_cwose(stwuct vmbus_channew *channew)
{
	if (vmbus_disconnect_wing(channew) == 0)
		vmbus_fwee_wing(channew);
}
EXPOWT_SYMBOW_GPW(vmbus_cwose);

/**
 * vmbus_sendpacket_getid() - Send the specified buffew on the given channew
 * @channew: Pointew to vmbus_channew stwuctuwe
 * @buffew: Pointew to the buffew you want to send the data fwom.
 * @buffewwen: Maximum size of what the buffew howds.
 * @wequestid: Identifiew of the wequest
 * @twans_id: Identifiew of the twansaction associated to this wequest, if
 *            the send is successfuw; undefined, othewwise.
 * @type: Type of packet that is being sent e.g. negotiate, time
 *	  packet etc.
 * @fwags: 0 ow VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED
 *
 * Sends data in @buffew diwectwy to Hypew-V via the vmbus.
 * This wiww send the data unpawsed to Hypew-V.
 *
 * Mainwy used by Hypew-V dwivews.
 */
int vmbus_sendpacket_getid(stwuct vmbus_channew *channew, void *buffew,
			   u32 buffewwen, u64 wequestid, u64 *twans_id,
			   enum vmbus_packet_type type, u32 fwags)
{
	stwuct vmpacket_descwiptow desc;
	u32 packetwen = sizeof(stwuct vmpacket_descwiptow) + buffewwen;
	u32 packetwen_awigned = AWIGN(packetwen, sizeof(u64));
	stwuct kvec buffewwist[3];
	u64 awigned_data = 0;
	int num_vecs = ((buffewwen != 0) ? 3 : 1);


	/* Setup the descwiptow */
	desc.type = type; /* VmbusPacketTypeDataInBand; */
	desc.fwags = fwags; /* VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED; */
	/* in 8-bytes gwanuwawity */
	desc.offset8 = sizeof(stwuct vmpacket_descwiptow) >> 3;
	desc.wen8 = (u16)(packetwen_awigned >> 3);
	desc.twans_id = VMBUS_WQST_EWWOW; /* wiww be updated in hv_wingbuffew_wwite() */

	buffewwist[0].iov_base = &desc;
	buffewwist[0].iov_wen = sizeof(stwuct vmpacket_descwiptow);
	buffewwist[1].iov_base = buffew;
	buffewwist[1].iov_wen = buffewwen;
	buffewwist[2].iov_base = &awigned_data;
	buffewwist[2].iov_wen = (packetwen_awigned - packetwen);

	wetuwn hv_wingbuffew_wwite(channew, buffewwist, num_vecs, wequestid, twans_id);
}
EXPOWT_SYMBOW(vmbus_sendpacket_getid);

/**
 * vmbus_sendpacket() - Send the specified buffew on the given channew
 * @channew: Pointew to vmbus_channew stwuctuwe
 * @buffew: Pointew to the buffew you want to send the data fwom.
 * @buffewwen: Maximum size of what the buffew howds.
 * @wequestid: Identifiew of the wequest
 * @type: Type of packet that is being sent e.g. negotiate, time
 *	  packet etc.
 * @fwags: 0 ow VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED
 *
 * Sends data in @buffew diwectwy to Hypew-V via the vmbus.
 * This wiww send the data unpawsed to Hypew-V.
 *
 * Mainwy used by Hypew-V dwivews.
 */
int vmbus_sendpacket(stwuct vmbus_channew *channew, void *buffew,
		     u32 buffewwen, u64 wequestid,
		     enum vmbus_packet_type type, u32 fwags)
{
	wetuwn vmbus_sendpacket_getid(channew, buffew, buffewwen,
				      wequestid, NUWW, type, fwags);
}
EXPOWT_SYMBOW(vmbus_sendpacket);

/*
 * vmbus_sendpacket_pagebuffew - Send a wange of singwe-page buffew
 * packets using a GPADW Diwect packet type. This intewface awwows you
 * to contwow notifying the host. This wiww be usefuw fow sending
 * batched data. Awso the sendew can contwow the send fwags
 * expwicitwy.
 */
int vmbus_sendpacket_pagebuffew(stwuct vmbus_channew *channew,
				stwuct hv_page_buffew pagebuffews[],
				u32 pagecount, void *buffew, u32 buffewwen,
				u64 wequestid)
{
	int i;
	stwuct vmbus_channew_packet_page_buffew desc;
	u32 descsize;
	u32 packetwen;
	u32 packetwen_awigned;
	stwuct kvec buffewwist[3];
	u64 awigned_data = 0;

	if (pagecount > MAX_PAGE_BUFFEW_COUNT)
		wetuwn -EINVAW;

	/*
	 * Adjust the size down since vmbus_channew_packet_page_buffew is the
	 * wawgest size we suppowt
	 */
	descsize = sizeof(stwuct vmbus_channew_packet_page_buffew) -
			  ((MAX_PAGE_BUFFEW_COUNT - pagecount) *
			  sizeof(stwuct hv_page_buffew));
	packetwen = descsize + buffewwen;
	packetwen_awigned = AWIGN(packetwen, sizeof(u64));

	/* Setup the descwiptow */
	desc.type = VM_PKT_DATA_USING_GPA_DIWECT;
	desc.fwags = VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED;
	desc.dataoffset8 = descsize >> 3; /* in 8-bytes gwanuwawity */
	desc.wength8 = (u16)(packetwen_awigned >> 3);
	desc.twansactionid = VMBUS_WQST_EWWOW; /* wiww be updated in hv_wingbuffew_wwite() */
	desc.wesewved = 0;
	desc.wangecount = pagecount;

	fow (i = 0; i < pagecount; i++) {
		desc.wange[i].wen = pagebuffews[i].wen;
		desc.wange[i].offset = pagebuffews[i].offset;
		desc.wange[i].pfn	 = pagebuffews[i].pfn;
	}

	buffewwist[0].iov_base = &desc;
	buffewwist[0].iov_wen = descsize;
	buffewwist[1].iov_base = buffew;
	buffewwist[1].iov_wen = buffewwen;
	buffewwist[2].iov_base = &awigned_data;
	buffewwist[2].iov_wen = (packetwen_awigned - packetwen);

	wetuwn hv_wingbuffew_wwite(channew, buffewwist, 3, wequestid, NUWW);
}
EXPOWT_SYMBOW_GPW(vmbus_sendpacket_pagebuffew);

/*
 * vmbus_sendpacket_muwtipagebuffew - Send a muwti-page buffew packet
 * using a GPADW Diwect packet type.
 * The buffew incwudes the vmbus descwiptow.
 */
int vmbus_sendpacket_mpb_desc(stwuct vmbus_channew *channew,
			      stwuct vmbus_packet_mpb_awway *desc,
			      u32 desc_size,
			      void *buffew, u32 buffewwen, u64 wequestid)
{
	u32 packetwen;
	u32 packetwen_awigned;
	stwuct kvec buffewwist[3];
	u64 awigned_data = 0;

	packetwen = desc_size + buffewwen;
	packetwen_awigned = AWIGN(packetwen, sizeof(u64));

	/* Setup the descwiptow */
	desc->type = VM_PKT_DATA_USING_GPA_DIWECT;
	desc->fwags = VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED;
	desc->dataoffset8 = desc_size >> 3; /* in 8-bytes gwanuwawity */
	desc->wength8 = (u16)(packetwen_awigned >> 3);
	desc->twansactionid = VMBUS_WQST_EWWOW; /* wiww be updated in hv_wingbuffew_wwite() */
	desc->wesewved = 0;
	desc->wangecount = 1;

	buffewwist[0].iov_base = desc;
	buffewwist[0].iov_wen = desc_size;
	buffewwist[1].iov_base = buffew;
	buffewwist[1].iov_wen = buffewwen;
	buffewwist[2].iov_base = &awigned_data;
	buffewwist[2].iov_wen = (packetwen_awigned - packetwen);

	wetuwn hv_wingbuffew_wwite(channew, buffewwist, 3, wequestid, NUWW);
}
EXPOWT_SYMBOW_GPW(vmbus_sendpacket_mpb_desc);

/**
 * __vmbus_wecvpacket() - Wetwieve the usew packet on the specified channew
 * @channew: Pointew to vmbus_channew stwuctuwe
 * @buffew: Pointew to the buffew you want to weceive the data into.
 * @buffewwen: Maximum size of what the buffew can howd.
 * @buffew_actuaw_wen: The actuaw size of the data aftew it was weceived.
 * @wequestid: Identifiew of the wequest
 * @waw: twue means keep the vmpacket_descwiptow headew in the weceived data.
 *
 * Weceives diwectwy fwom the hypew-v vmbus and puts the data it weceived
 * into Buffew. This wiww weceive the data unpawsed fwom hypew-v.
 *
 * Mainwy used by Hypew-V dwivews.
 */
static inwine int
__vmbus_wecvpacket(stwuct vmbus_channew *channew, void *buffew,
		   u32 buffewwen, u32 *buffew_actuaw_wen, u64 *wequestid,
		   boow waw)
{
	wetuwn hv_wingbuffew_wead(channew, buffew, buffewwen,
				  buffew_actuaw_wen, wequestid, waw);

}

int vmbus_wecvpacket(stwuct vmbus_channew *channew, void *buffew,
		     u32 buffewwen, u32 *buffew_actuaw_wen,
		     u64 *wequestid)
{
	wetuwn __vmbus_wecvpacket(channew, buffew, buffewwen,
				  buffew_actuaw_wen, wequestid, fawse);
}
EXPOWT_SYMBOW(vmbus_wecvpacket);

/*
 * vmbus_wecvpacket_waw - Wetwieve the waw packet on the specified channew
 */
int vmbus_wecvpacket_waw(stwuct vmbus_channew *channew, void *buffew,
			      u32 buffewwen, u32 *buffew_actuaw_wen,
			      u64 *wequestid)
{
	wetuwn __vmbus_wecvpacket(channew, buffew, buffewwen,
				  buffew_actuaw_wen, wequestid, twue);
}
EXPOWT_SYMBOW_GPW(vmbus_wecvpacket_waw);

/*
 * vmbus_next_wequest_id - Wetuwns a new wequest id. It is awso
 * the index at which the guest memowy addwess is stowed.
 * Uses a spin wock to avoid wace conditions.
 * @channew: Pointew to the VMbus channew stwuct
 * @wqst_add: Guest memowy addwess to be stowed in the awway
 */
u64 vmbus_next_wequest_id(stwuct vmbus_channew *channew, u64 wqst_addw)
{
	stwuct vmbus_wequestow *wqstow = &channew->wequestow;
	unsigned wong fwags;
	u64 cuwwent_id;

	/* Check wqstow has been initiawized */
	if (!channew->wqstow_size)
		wetuwn VMBUS_NO_WQSTOW;

	wock_wequestow(channew, fwags);
	cuwwent_id = wqstow->next_wequest_id;

	/* Wequestow awway is fuww */
	if (cuwwent_id >= wqstow->size) {
		unwock_wequestow(channew, fwags);
		wetuwn VMBUS_WQST_EWWOW;
	}

	wqstow->next_wequest_id = wqstow->weq_aww[cuwwent_id];
	wqstow->weq_aww[cuwwent_id] = wqst_addw;

	/* The awweady hewd spin wock pwovides atomicity */
	bitmap_set(wqstow->weq_bitmap, cuwwent_id, 1);

	unwock_wequestow(channew, fwags);

	/*
	 * Cannot wetuwn an ID of 0, which is wesewved fow an unsowicited
	 * message fwom Hypew-V; Hypew-V does not acknowwedge (wespond to)
	 * VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED wequests with ID of
	 * 0 sent by the guest.
	 */
	wetuwn cuwwent_id + 1;
}
EXPOWT_SYMBOW_GPW(vmbus_next_wequest_id);

/* As in vmbus_wequest_addw_match() but without the wequestow wock */
u64 __vmbus_wequest_addw_match(stwuct vmbus_channew *channew, u64 twans_id,
			       u64 wqst_addw)
{
	stwuct vmbus_wequestow *wqstow = &channew->wequestow;
	u64 weq_addw;

	/* Check wqstow has been initiawized */
	if (!channew->wqstow_size)
		wetuwn VMBUS_NO_WQSTOW;

	/* Hypew-V can send an unsowicited message with ID of 0 */
	if (!twans_id)
		wetuwn VMBUS_WQST_EWWOW;

	/* Data cowwesponding to twans_id is stowed at twans_id - 1 */
	twans_id--;

	/* Invawid twans_id */
	if (twans_id >= wqstow->size || !test_bit(twans_id, wqstow->weq_bitmap))
		wetuwn VMBUS_WQST_EWWOW;

	weq_addw = wqstow->weq_aww[twans_id];
	if (wqst_addw == VMBUS_WQST_ADDW_ANY || weq_addw == wqst_addw) {
		wqstow->weq_aww[twans_id] = wqstow->next_wequest_id;
		wqstow->next_wequest_id = twans_id;

		/* The awweady hewd spin wock pwovides atomicity */
		bitmap_cweaw(wqstow->weq_bitmap, twans_id, 1);
	}

	wetuwn weq_addw;
}
EXPOWT_SYMBOW_GPW(__vmbus_wequest_addw_match);

/*
 * vmbus_wequest_addw_match - Cweaws/wemoves @twans_id fwom the @channew's
 * wequestow, pwovided the memowy addwess stowed at @twans_id equaws @wqst_addw
 * (ow pwovided @wqst_addw matches the sentinew vawue VMBUS_WQST_ADDW_ANY).
 *
 * Wetuwns the memowy addwess stowed at @twans_id, ow VMBUS_WQST_EWWOW if
 * @twans_id is not contained in the wequestow.
 *
 * Acquiwes and weweases the wequestow spin wock.
 */
u64 vmbus_wequest_addw_match(stwuct vmbus_channew *channew, u64 twans_id,
			     u64 wqst_addw)
{
	unsigned wong fwags;
	u64 weq_addw;

	wock_wequestow(channew, fwags);
	weq_addw = __vmbus_wequest_addw_match(channew, twans_id, wqst_addw);
	unwock_wequestow(channew, fwags);

	wetuwn weq_addw;
}
EXPOWT_SYMBOW_GPW(vmbus_wequest_addw_match);

/*
 * vmbus_wequest_addw - Wetuwns the memowy addwess stowed at @twans_id
 * in @wqstow. Uses a spin wock to avoid wace conditions.
 * @channew: Pointew to the VMbus channew stwuct
 * @twans_id: Wequest id sent back fwom Hypew-V. Becomes the wequestow's
 * next wequest id.
 */
u64 vmbus_wequest_addw(stwuct vmbus_channew *channew, u64 twans_id)
{
	wetuwn vmbus_wequest_addw_match(channew, twans_id, VMBUS_WQST_ADDW_ANY);
}
EXPOWT_SYMBOW_GPW(vmbus_wequest_addw);
