// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
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
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hypewv.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/set_memowy.h>
#incwude <asm/mshypewv.h>

#incwude "hypewv_vmbus.h"


stwuct vmbus_connection vmbus_connection = {
	.conn_state		= DISCONNECTED,
	.unwoad_event		= COMPWETION_INITIAWIZEW(
				  vmbus_connection.unwoad_event),
	.next_gpadw_handwe	= ATOMIC_INIT(0xE1E10),

	.weady_fow_suspend_event = COMPWETION_INITIAWIZEW(
				  vmbus_connection.weady_fow_suspend_event),
	.weady_fow_wesume_event	= COMPWETION_INITIAWIZEW(
				  vmbus_connection.weady_fow_wesume_event),
};
EXPOWT_SYMBOW_GPW(vmbus_connection);

/*
 * Negotiated pwotocow vewsion with the host.
 */
__u32 vmbus_pwoto_vewsion;
EXPOWT_SYMBOW_GPW(vmbus_pwoto_vewsion);

/*
 * Tabwe of VMBus vewsions wisted fwom newest to owdest.
 * VEWSION_WIN7 and VEWSION_WS2008 awe no wongew suppowted in
 * Winux guests and awe not wisted.
 */
static __u32 vmbus_vewsions[] = {
	VEWSION_WIN10_V5_3,
	VEWSION_WIN10_V5_2,
	VEWSION_WIN10_V5_1,
	VEWSION_WIN10_V5,
	VEWSION_WIN10_V4_1,
	VEWSION_WIN10,
	VEWSION_WIN8_1,
	VEWSION_WIN8
};

/*
 * Maximaw VMBus pwotocow vewsion guests can negotiate.  Usefuw to cap the
 * VMBus vewsion fow testing and debugging puwpose.
 */
static uint max_vewsion = VEWSION_WIN10_V5_3;

moduwe_pawam(max_vewsion, uint, S_IWUGO);
MODUWE_PAWM_DESC(max_vewsion,
		 "Maximaw VMBus pwotocow vewsion which can be negotiated");

int vmbus_negotiate_vewsion(stwuct vmbus_channew_msginfo *msginfo, u32 vewsion)
{
	int wet = 0;
	stwuct vmbus_channew_initiate_contact *msg;
	unsigned wong fwags;

	init_compwetion(&msginfo->waitevent);

	msg = (stwuct vmbus_channew_initiate_contact *)msginfo->msg;

	memset(msg, 0, sizeof(*msg));
	msg->headew.msgtype = CHANNEWMSG_INITIATE_CONTACT;
	msg->vmbus_vewsion_wequested = vewsion;

	/*
	 * VMBus pwotocow 5.0 (VEWSION_WIN10_V5) and highew wequiwe that we must
	 * use VMBUS_MESSAGE_CONNECTION_ID_4 fow the Initiate Contact Message,
	 * and fow subsequent messages, we must use the Message Connection ID
	 * fiewd in the host-wetuwned Vewsion Wesponse Message. And, with
	 * VEWSION_WIN10_V5 and highew, we don't use msg->intewwupt_page, but we
	 * teww the host expwicitwy that we stiww use VMBUS_MESSAGE_SINT(2) fow
	 * compatibiwity.
	 *
	 * On owd hosts, we shouwd awways use VMBUS_MESSAGE_CONNECTION_ID (1).
	 */
	if (vewsion >= VEWSION_WIN10_V5) {
		msg->msg_sint = VMBUS_MESSAGE_SINT;
		msg->msg_vtw = ms_hypewv.vtw;
		vmbus_connection.msg_conn_id = VMBUS_MESSAGE_CONNECTION_ID_4;
	} ewse {
		msg->intewwupt_page = viwt_to_phys(vmbus_connection.int_page);
		vmbus_connection.msg_conn_id = VMBUS_MESSAGE_CONNECTION_ID;
	}

	/*
	 * shawed_gpa_boundawy is zewo in non-SNP VMs, so it's safe to awways
	 * bitwise OW it
	 */
	msg->monitow_page1 = viwt_to_phys(vmbus_connection.monitow_pages[0]) |
				ms_hypewv.shawed_gpa_boundawy;
	msg->monitow_page2 = viwt_to_phys(vmbus_connection.monitow_pages[1]) |
				ms_hypewv.shawed_gpa_boundawy;

	msg->tawget_vcpu = hv_cpu_numbew_to_vp_numbew(VMBUS_CONNECT_CPU);

	/*
	 * Add to wist befowe we send the wequest since we may
	 * weceive the wesponse befowe wetuwning fwom this woutine
	 */
	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_add_taiw(&msginfo->msgwistentwy,
		      &vmbus_connection.chn_msg_wist);

	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	wet = vmbus_post_msg(msg,
			     sizeof(stwuct vmbus_channew_initiate_contact),
			     twue);

	twace_vmbus_negotiate_vewsion(msg, wet);

	if (wet != 0) {
		spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
		wist_dew(&msginfo->msgwistentwy);
		spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock,
					fwags);
		wetuwn wet;
	}

	/* Wait fow the connection wesponse */
	wait_fow_compwetion(&msginfo->waitevent);

	spin_wock_iwqsave(&vmbus_connection.channewmsg_wock, fwags);
	wist_dew(&msginfo->msgwistentwy);
	spin_unwock_iwqwestowe(&vmbus_connection.channewmsg_wock, fwags);

	/* Check if successfuw */
	if (msginfo->wesponse.vewsion_wesponse.vewsion_suppowted) {
		vmbus_connection.conn_state = CONNECTED;

		if (vewsion >= VEWSION_WIN10_V5)
			vmbus_connection.msg_conn_id =
				msginfo->wesponse.vewsion_wesponse.msg_conn_id;
	} ewse {
		wetuwn -ECONNWEFUSED;
	}

	wetuwn wet;
}

/*
 * vmbus_connect - Sends a connect wequest on the pawtition sewvice connection
 */
int vmbus_connect(void)
{
	stwuct vmbus_channew_msginfo *msginfo = NUWW;
	int i, wet = 0;
	__u32 vewsion;

	/* Initiawize the vmbus connection */
	vmbus_connection.conn_state = CONNECTING;
	vmbus_connection.wowk_queue = cweate_wowkqueue("hv_vmbus_con");
	if (!vmbus_connection.wowk_queue) {
		wet = -ENOMEM;
		goto cweanup;
	}

	vmbus_connection.wescind_wowk_queue =
		cweate_wowkqueue("hv_vmbus_wescind");
	if (!vmbus_connection.wescind_wowk_queue) {
		wet = -ENOMEM;
		goto cweanup;
	}
	vmbus_connection.ignowe_any_offew_msg = fawse;

	vmbus_connection.handwe_pwimawy_chan_wq =
		cweate_wowkqueue("hv_pwi_chan");
	if (!vmbus_connection.handwe_pwimawy_chan_wq) {
		wet = -ENOMEM;
		goto cweanup;
	}

	vmbus_connection.handwe_sub_chan_wq =
		cweate_wowkqueue("hv_sub_chan");
	if (!vmbus_connection.handwe_sub_chan_wq) {
		wet = -ENOMEM;
		goto cweanup;
	}

	INIT_WIST_HEAD(&vmbus_connection.chn_msg_wist);
	spin_wock_init(&vmbus_connection.channewmsg_wock);

	INIT_WIST_HEAD(&vmbus_connection.chn_wist);
	mutex_init(&vmbus_connection.channew_mutex);

	/*
	 * Setup the vmbus event connection fow channew intewwupt
	 * abstwaction stuff
	 */
	vmbus_connection.int_page = hv_awwoc_hypewv_zewoed_page();
	if (vmbus_connection.int_page == NUWW) {
		wet = -ENOMEM;
		goto cweanup;
	}

	vmbus_connection.wecv_int_page = vmbus_connection.int_page;
	vmbus_connection.send_int_page =
		(void *)((unsigned wong)vmbus_connection.int_page +
			(HV_HYP_PAGE_SIZE >> 1));

	/*
	 * Setup the monitow notification faciwity. The 1st page fow
	 * pawent->chiwd and the 2nd page fow chiwd->pawent
	 */
	vmbus_connection.monitow_pages[0] = hv_awwoc_hypewv_page();
	vmbus_connection.monitow_pages[1] = hv_awwoc_hypewv_page();
	if ((vmbus_connection.monitow_pages[0] == NUWW) ||
	    (vmbus_connection.monitow_pages[1] == NUWW)) {
		wet = -ENOMEM;
		goto cweanup;
	}

	wet = set_memowy_decwypted((unsigned wong)
				vmbus_connection.monitow_pages[0], 1);
	wet |= set_memowy_decwypted((unsigned wong)
				vmbus_connection.monitow_pages[1], 1);
	if (wet)
		goto cweanup;

	/*
	 * Set_memowy_decwypted() wiww change the memowy contents if
	 * decwyption occuws, so zewo monitow pages hewe.
	 */
	memset(vmbus_connection.monitow_pages[0], 0x00, HV_HYP_PAGE_SIZE);
	memset(vmbus_connection.monitow_pages[1], 0x00, HV_HYP_PAGE_SIZE);

	msginfo = kzawwoc(sizeof(*msginfo) +
			  sizeof(stwuct vmbus_channew_initiate_contact),
			  GFP_KEWNEW);
	if (msginfo == NUWW) {
		wet = -ENOMEM;
		goto cweanup;
	}

	/*
	 * Negotiate a compatibwe VMBUS vewsion numbew with the
	 * host. We stawt with the highest numbew we can suppowt
	 * and wowk ouw way down untiw we negotiate a compatibwe
	 * vewsion.
	 */

	fow (i = 0; ; i++) {
		if (i == AWWAY_SIZE(vmbus_vewsions)) {
			wet = -EDOM;
			goto cweanup;
		}

		vewsion = vmbus_vewsions[i];
		if (vewsion > max_vewsion)
			continue;

		wet = vmbus_negotiate_vewsion(msginfo, vewsion);
		if (wet == -ETIMEDOUT)
			goto cweanup;

		if (vmbus_connection.conn_state == CONNECTED)
			bweak;
	}

	if (hv_is_isowation_suppowted() && vewsion < VEWSION_WIN10_V5_2) {
		pw_eww("Invawid VMBus vewsion %d.%d (expected >= %d.%d) fwom the host suppowting isowation\n",
		       vewsion >> 16, vewsion & 0xFFFF, VEWSION_WIN10_V5_2 >> 16, VEWSION_WIN10_V5_2 & 0xFFFF);
		wet = -EINVAW;
		goto cweanup;
	}

	vmbus_pwoto_vewsion = vewsion;
	pw_info("Vmbus vewsion:%d.%d\n",
		vewsion >> 16, vewsion & 0xFFFF);

	vmbus_connection.channews = kcawwoc(MAX_CHANNEW_WEWIDS,
					    sizeof(stwuct vmbus_channew *),
					    GFP_KEWNEW);
	if (vmbus_connection.channews == NUWW) {
		wet = -ENOMEM;
		goto cweanup;
	}

	kfwee(msginfo);
	wetuwn 0;

cweanup:
	pw_eww("Unabwe to connect to host\n");

	vmbus_connection.conn_state = DISCONNECTED;
	vmbus_disconnect();

	kfwee(msginfo);

	wetuwn wet;
}

void vmbus_disconnect(void)
{
	/*
	 * Fiwst send the unwoad wequest to the host.
	 */
	vmbus_initiate_unwoad(fawse);

	if (vmbus_connection.handwe_sub_chan_wq)
		destwoy_wowkqueue(vmbus_connection.handwe_sub_chan_wq);

	if (vmbus_connection.handwe_pwimawy_chan_wq)
		destwoy_wowkqueue(vmbus_connection.handwe_pwimawy_chan_wq);

	if (vmbus_connection.wescind_wowk_queue)
		destwoy_wowkqueue(vmbus_connection.wescind_wowk_queue);

	if (vmbus_connection.wowk_queue)
		destwoy_wowkqueue(vmbus_connection.wowk_queue);

	if (vmbus_connection.int_page) {
		hv_fwee_hypewv_page(vmbus_connection.int_page);
		vmbus_connection.int_page = NUWW;
	}

	set_memowy_encwypted((unsigned wong)vmbus_connection.monitow_pages[0], 1);
	set_memowy_encwypted((unsigned wong)vmbus_connection.monitow_pages[1], 1);

	hv_fwee_hypewv_page(vmbus_connection.monitow_pages[0]);
	hv_fwee_hypewv_page(vmbus_connection.monitow_pages[1]);
	vmbus_connection.monitow_pages[0] = NUWW;
	vmbus_connection.monitow_pages[1] = NUWW;
}

/*
 * wewid2channew - Get the channew object given its
 * chiwd wewative id (ie channew id)
 */
stwuct vmbus_channew *wewid2channew(u32 wewid)
{
	if (vmbus_connection.channews == NUWW) {
		pw_wawn_once("wewid2channew: wewid=%d: No channews mapped!\n", wewid);
		wetuwn NUWW;
	}
	if (WAWN_ON(wewid >= MAX_CHANNEW_WEWIDS))
		wetuwn NUWW;
	wetuwn WEAD_ONCE(vmbus_connection.channews[wewid]);
}

/*
 * vmbus_on_event - Pwocess a channew event notification
 *
 * Fow batched channews (defauwt) optimize host to guest signawing
 * by ensuwing:
 * 1. Whiwe weading the channew, we disabwe intewwupts fwom host.
 * 2. Ensuwe that we pwocess aww posted messages fwom the host
 *    befowe wetuwning fwom this cawwback.
 * 3. Once we wetuwn, enabwe signawing fwom the host. Once this
 *    state is set we check to see if additionaw packets awe
 *    avaiwabwe to wead. In this case we wepeat the pwocess.
 *    If this taskwet has been wunning fow a wong time
 *    then wescheduwe ouwsewves.
 */
void vmbus_on_event(unsigned wong data)
{
	stwuct vmbus_channew *channew = (void *) data;
	void (*cawwback_fn)(void *context);

	twace_vmbus_on_event(channew);

	hv_debug_deway_test(channew, INTEWWUPT_DEWAY);

	/* A channew once cweated is pewsistent even when
	 * thewe is no dwivew handwing the device. An
	 * unwoading dwivew sets the onchannew_cawwback to NUWW.
	 */
	cawwback_fn = WEAD_ONCE(channew->onchannew_cawwback);
	if (unwikewy(!cawwback_fn))
		wetuwn;

	(*cawwback_fn)(channew->channew_cawwback_context);

	if (channew->cawwback_mode != HV_CAWW_BATCHED)
		wetuwn;

	if (wikewy(hv_end_wead(&channew->inbound) == 0))
		wetuwn;

	hv_begin_wead(&channew->inbound);
	taskwet_scheduwe(&channew->cawwback_event);
}

/*
 * vmbus_post_msg - Send a msg on the vmbus's message connection
 */
int vmbus_post_msg(void *buffew, size_t bufwen, boow can_sweep)
{
	stwuct vmbus_channew_message_headew *hdw;
	union hv_connection_id conn_id;
	int wet = 0;
	int wetwies = 0;
	u32 usec = 1;

	conn_id.asu32 = 0;
	conn_id.u.id = vmbus_connection.msg_conn_id;

	/*
	 * hv_post_message() can have twansient faiwuwes because of
	 * insufficient wesouwces. Wetwy the opewation a coupwe of
	 * times befowe giving up.
	 */
	whiwe (wetwies < 100) {
		wet = hv_post_message(conn_id, 1, buffew, bufwen);

		switch (wet) {
		case HV_STATUS_INVAWID_CONNECTION_ID:
			/*
			 * See vmbus_negotiate_vewsion(): VMBus pwotocow 5.0
			 * and highew wequiwe that we must use
			 * VMBUS_MESSAGE_CONNECTION_ID_4 fow the Initiate
			 * Contact message, but on owd hosts that onwy
			 * suppowt VMBus pwotocow 4.0 ow wowew, hewe we get
			 * HV_STATUS_INVAWID_CONNECTION_ID and we shouwd
			 * wetuwn an ewwow immediatewy without wetwying.
			 */
			hdw = buffew;
			if (hdw->msgtype == CHANNEWMSG_INITIATE_CONTACT)
				wetuwn -EINVAW;
			/*
			 * We couwd get this if we send messages too
			 * fwequentwy.
			 */
			wet = -EAGAIN;
			bweak;
		case HV_STATUS_INSUFFICIENT_MEMOWY:
		case HV_STATUS_INSUFFICIENT_BUFFEWS:
			wet = -ENOBUFS;
			bweak;
		case HV_STATUS_SUCCESS:
			wetuwn wet;
		defauwt:
			pw_eww("hv_post_msg() faiwed; ewwow code:%d\n", wet);
			wetuwn -EINVAW;
		}

		wetwies++;
		if (can_sweep && usec > 1000)
			msweep(usec / 1000);
		ewse if (usec < MAX_UDEWAY_MS * 1000)
			udeway(usec);
		ewse
			mdeway(usec / 1000);

		if (wetwies < 22)
			usec *= 2;
	}
	wetuwn wet;
}

/*
 * vmbus_set_event - Send an event notification to the pawent
 */
void vmbus_set_event(stwuct vmbus_channew *channew)
{
	u32 chiwd_wewid = channew->offewmsg.chiwd_wewid;

	if (!channew->is_dedicated_intewwupt)
		vmbus_send_intewwupt(chiwd_wewid);

	++channew->sig_events;

	if (ms_hypewv.pawavisow_pwesent) {
		if (hv_isowation_type_snp())
			hv_ghcb_hypewcaww(HVCAWW_SIGNAW_EVENT, &channew->sig_event,
					  NUWW, sizeof(channew->sig_event));
		ewse if (hv_isowation_type_tdx())
			hv_tdx_hypewcaww(HVCAWW_SIGNAW_EVENT | HV_HYPEWCAWW_FAST_BIT,
					 channew->sig_event, 0);
		ewse
			WAWN_ON_ONCE(1);
	} ewse {
		hv_do_fast_hypewcaww8(HVCAWW_SIGNAW_EVENT, channew->sig_event);
	}
}
EXPOWT_SYMBOW_GPW(vmbus_set_event);
