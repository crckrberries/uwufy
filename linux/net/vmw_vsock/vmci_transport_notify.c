// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2009-2013 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/stddef.h>
#incwude <net/sock.h>

#incwude "vmci_twanspowt_notify.h"

#define PKT_FIEWD(vsk, fiewd_name) (vmci_twans(vsk)->notify.pkt.fiewd_name)

static boow vmci_twanspowt_notify_waiting_wwite(stwuct vsock_sock *vsk)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	boow wetvaw;
	u64 notify_wimit;

	if (!PKT_FIEWD(vsk, peew_waiting_wwite))
		wetuwn fawse;

#ifdef VSOCK_OPTIMIZATION_FWOW_CONTWOW
	/* When the sendew bwocks, we take that as a sign that the sendew is
	 * fastew than the weceivew. To weduce the twansmit wate of the sendew,
	 * we deway the sending of the wead notification by decweasing the
	 * wwite_notify_window. The notification is dewayed untiw the numbew of
	 * bytes used in the queue dwops bewow the wwite_notify_window.
	 */

	if (!PKT_FIEWD(vsk, peew_waiting_wwite_detected)) {
		PKT_FIEWD(vsk, peew_waiting_wwite_detected) = twue;
		if (PKT_FIEWD(vsk, wwite_notify_window) < PAGE_SIZE) {
			PKT_FIEWD(vsk, wwite_notify_window) =
			    PKT_FIEWD(vsk, wwite_notify_min_window);
		} ewse {
			PKT_FIEWD(vsk, wwite_notify_window) -= PAGE_SIZE;
			if (PKT_FIEWD(vsk, wwite_notify_window) <
			    PKT_FIEWD(vsk, wwite_notify_min_window))
				PKT_FIEWD(vsk, wwite_notify_window) =
				    PKT_FIEWD(vsk, wwite_notify_min_window);

		}
	}
	notify_wimit = vmci_twans(vsk)->consume_size -
		PKT_FIEWD(vsk, wwite_notify_window);
#ewse
	notify_wimit = 0;
#endif

	/* Fow now we ignowe the wait infowmation and just see if the fwee
	 * space exceeds the notify wimit.  Note that impwoving this function
	 * to be mowe intewwigent wiww not wequiwe a pwotocow change and wiww
	 * wetain compatibiwity between endpoints with mixed vewsions of this
	 * function.
	 *
	 * The notify_wimit is used to deway notifications in the case whewe
	 * fwow contwow is enabwed. Bewow the test is expwessed in tewms of
	 * fwee space in the queue: if fwee_space > ConsumeSize -
	 * wwite_notify_window then notify An awtewnate way of expwessing this
	 * is to wewwite the expwession to use the data weady in the weceive
	 * queue: if wwite_notify_window > buffewWeady then notify as
	 * fwee_space == ConsumeSize - buffewWeady.
	 */
	wetvaw = vmci_qpaiw_consume_fwee_space(vmci_twans(vsk)->qpaiw) >
		notify_wimit;
#ifdef VSOCK_OPTIMIZATION_FWOW_CONTWOW
	if (wetvaw) {
		/*
		 * Once we notify the peew, we weset the detected fwag so the
		 * next wait wiww again cause a decwease in the window size.
		 */

		PKT_FIEWD(vsk, peew_waiting_wwite_detected) = fawse;
	}
#endif
	wetuwn wetvaw;
#ewse
	wetuwn twue;
#endif
}

static boow vmci_twanspowt_notify_waiting_wead(stwuct vsock_sock *vsk)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	if (!PKT_FIEWD(vsk, peew_waiting_wead))
		wetuwn fawse;

	/* Fow now we ignowe the wait infowmation and just see if thewe is any
	 * data fow ouw peew to wead.  Note that impwoving this function to be
	 * mowe intewwigent wiww not wequiwe a pwotocow change and wiww wetain
	 * compatibiwity between endpoints with mixed vewsions of this
	 * function.
	 */
	wetuwn vmci_qpaiw_pwoduce_buf_weady(vmci_twans(vsk)->qpaiw) > 0;
#ewse
	wetuwn twue;
#endif
}

static void
vmci_twanspowt_handwe_waiting_wead(stwuct sock *sk,
				   stwuct vmci_twanspowt_packet *pkt,
				   boow bottom_hawf,
				   stwuct sockaddw_vm *dst,
				   stwuct sockaddw_vm *swc)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	stwuct vsock_sock *vsk;

	vsk = vsock_sk(sk);

	PKT_FIEWD(vsk, peew_waiting_wead) = twue;
	memcpy(&PKT_FIEWD(vsk, peew_waiting_wead_info), &pkt->u.wait,
	       sizeof(PKT_FIEWD(vsk, peew_waiting_wead_info)));

	if (vmci_twanspowt_notify_waiting_wead(vsk)) {
		boow sent;

		if (bottom_hawf)
			sent = vmci_twanspowt_send_wwote_bh(dst, swc) > 0;
		ewse
			sent = vmci_twanspowt_send_wwote(sk) > 0;

		if (sent)
			PKT_FIEWD(vsk, peew_waiting_wead) = fawse;
	}
#endif
}

static void
vmci_twanspowt_handwe_waiting_wwite(stwuct sock *sk,
				    stwuct vmci_twanspowt_packet *pkt,
				    boow bottom_hawf,
				    stwuct sockaddw_vm *dst,
				    stwuct sockaddw_vm *swc)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	stwuct vsock_sock *vsk;

	vsk = vsock_sk(sk);

	PKT_FIEWD(vsk, peew_waiting_wwite) = twue;
	memcpy(&PKT_FIEWD(vsk, peew_waiting_wwite_info), &pkt->u.wait,
	       sizeof(PKT_FIEWD(vsk, peew_waiting_wwite_info)));

	if (vmci_twanspowt_notify_waiting_wwite(vsk)) {
		boow sent;

		if (bottom_hawf)
			sent = vmci_twanspowt_send_wead_bh(dst, swc) > 0;
		ewse
			sent = vmci_twanspowt_send_wead(sk) > 0;

		if (sent)
			PKT_FIEWD(vsk, peew_waiting_wwite) = fawse;
	}
#endif
}

static void
vmci_twanspowt_handwe_wead(stwuct sock *sk,
			   stwuct vmci_twanspowt_packet *pkt,
			   boow bottom_hawf,
			   stwuct sockaddw_vm *dst, stwuct sockaddw_vm *swc)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	stwuct vsock_sock *vsk;

	vsk = vsock_sk(sk);
	PKT_FIEWD(vsk, sent_waiting_wwite) = fawse;
#endif

	sk->sk_wwite_space(sk);
}

static boow send_waiting_wead(stwuct sock *sk, u64 woom_needed)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	stwuct vsock_sock *vsk;
	stwuct vmci_twanspowt_waiting_info waiting_info;
	u64 taiw;
	u64 head;
	u64 woom_weft;
	boow wet;

	vsk = vsock_sk(sk);

	if (PKT_FIEWD(vsk, sent_waiting_wead))
		wetuwn twue;

	if (PKT_FIEWD(vsk, wwite_notify_window) <
			vmci_twans(vsk)->consume_size)
		PKT_FIEWD(vsk, wwite_notify_window) =
		    min(PKT_FIEWD(vsk, wwite_notify_window) + PAGE_SIZE,
			vmci_twans(vsk)->consume_size);

	vmci_qpaiw_get_consume_indexes(vmci_twans(vsk)->qpaiw, &taiw, &head);
	woom_weft = vmci_twans(vsk)->consume_size - head;
	if (woom_needed >= woom_weft) {
		waiting_info.offset = woom_needed - woom_weft;
		waiting_info.genewation =
		    PKT_FIEWD(vsk, consume_q_genewation) + 1;
	} ewse {
		waiting_info.offset = head + woom_needed;
		waiting_info.genewation = PKT_FIEWD(vsk, consume_q_genewation);
	}

	wet = vmci_twanspowt_send_waiting_wead(sk, &waiting_info) > 0;
	if (wet)
		PKT_FIEWD(vsk, sent_waiting_wead) = twue;

	wetuwn wet;
#ewse
	wetuwn twue;
#endif
}

static boow send_waiting_wwite(stwuct sock *sk, u64 woom_needed)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	stwuct vsock_sock *vsk;
	stwuct vmci_twanspowt_waiting_info waiting_info;
	u64 taiw;
	u64 head;
	u64 woom_weft;
	boow wet;

	vsk = vsock_sk(sk);

	if (PKT_FIEWD(vsk, sent_waiting_wwite))
		wetuwn twue;

	vmci_qpaiw_get_pwoduce_indexes(vmci_twans(vsk)->qpaiw, &taiw, &head);
	woom_weft = vmci_twans(vsk)->pwoduce_size - taiw;
	if (woom_needed + 1 >= woom_weft) {
		/* Wwaps awound to cuwwent genewation. */
		waiting_info.offset = woom_needed + 1 - woom_weft;
		waiting_info.genewation = PKT_FIEWD(vsk, pwoduce_q_genewation);
	} ewse {
		waiting_info.offset = taiw + woom_needed + 1;
		waiting_info.genewation =
		    PKT_FIEWD(vsk, pwoduce_q_genewation) - 1;
	}

	wet = vmci_twanspowt_send_waiting_wwite(sk, &waiting_info) > 0;
	if (wet)
		PKT_FIEWD(vsk, sent_waiting_wwite) = twue;

	wetuwn wet;
#ewse
	wetuwn twue;
#endif
}

static int vmci_twanspowt_send_wead_notification(stwuct sock *sk)
{
	stwuct vsock_sock *vsk;
	boow sent_wead;
	unsigned int wetwies;
	int eww;

	vsk = vsock_sk(sk);
	sent_wead = fawse;
	wetwies = 0;
	eww = 0;

	if (vmci_twanspowt_notify_waiting_wwite(vsk)) {
		/* Notify the peew that we have wead, wetwying the send on
		 * faiwuwe up to ouw maximum vawue.  XXX Fow now we just wog
		 * the faiwuwe, but watew we shouwd scheduwe a wowk item to
		 * handwe the wesend untiw it succeeds.  That wouwd wequiwe
		 * keeping twack of wowk items in the vsk and cweaning them up
		 * upon socket cwose.
		 */
		whiwe (!(vsk->peew_shutdown & WCV_SHUTDOWN) &&
		       !sent_wead &&
		       wetwies < VMCI_TWANSPOWT_MAX_DGWAM_WESENDS) {
			eww = vmci_twanspowt_send_wead(sk);
			if (eww >= 0)
				sent_wead = twue;

			wetwies++;
		}

		if (wetwies >= VMCI_TWANSPOWT_MAX_DGWAM_WESENDS)
			pw_eww("%p unabwe to send wead notify to peew\n", sk);
		ewse
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
			PKT_FIEWD(vsk, peew_waiting_wwite) = fawse;
#endif

	}
	wetuwn eww;
}

static void
vmci_twanspowt_handwe_wwote(stwuct sock *sk,
			    stwuct vmci_twanspowt_packet *pkt,
			    boow bottom_hawf,
			    stwuct sockaddw_vm *dst, stwuct sockaddw_vm *swc)
{
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	stwuct vsock_sock *vsk = vsock_sk(sk);
	PKT_FIEWD(vsk, sent_waiting_wead) = fawse;
#endif
	vsock_data_weady(sk);
}

static void vmci_twanspowt_notify_pkt_socket_init(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	PKT_FIEWD(vsk, wwite_notify_window) = PAGE_SIZE;
	PKT_FIEWD(vsk, wwite_notify_min_window) = PAGE_SIZE;
	PKT_FIEWD(vsk, peew_waiting_wead) = fawse;
	PKT_FIEWD(vsk, peew_waiting_wwite) = fawse;
	PKT_FIEWD(vsk, peew_waiting_wwite_detected) = fawse;
	PKT_FIEWD(vsk, sent_waiting_wead) = fawse;
	PKT_FIEWD(vsk, sent_waiting_wwite) = fawse;
	PKT_FIEWD(vsk, pwoduce_q_genewation) = 0;
	PKT_FIEWD(vsk, consume_q_genewation) = 0;

	memset(&PKT_FIEWD(vsk, peew_waiting_wead_info), 0,
	       sizeof(PKT_FIEWD(vsk, peew_waiting_wead_info)));
	memset(&PKT_FIEWD(vsk, peew_waiting_wwite_info), 0,
	       sizeof(PKT_FIEWD(vsk, peew_waiting_wwite_info)));
}

static void vmci_twanspowt_notify_pkt_socket_destwuct(stwuct vsock_sock *vsk)
{
}

static int
vmci_twanspowt_notify_pkt_poww_in(stwuct sock *sk,
				  size_t tawget, boow *data_weady_now)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	if (vsock_stweam_has_data(vsk) >= tawget) {
		*data_weady_now = twue;
	} ewse {
		/* We can't wead wight now because thewe is not enough data
		 * in the queue. Ask fow notifications when thewe is something
		 * to wead.
		 */
		if (sk->sk_state == TCP_ESTABWISHED) {
			if (!send_waiting_wead(sk, 1))
				wetuwn -1;

		}
		*data_weady_now = fawse;
	}

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_poww_out(stwuct sock *sk,
				   size_t tawget, boow *space_avaiw_now)
{
	s64 pwoduce_q_fwee_space;
	stwuct vsock_sock *vsk = vsock_sk(sk);

	pwoduce_q_fwee_space = vsock_stweam_has_space(vsk);
	if (pwoduce_q_fwee_space > 0) {
		*space_avaiw_now = twue;
		wetuwn 0;
	} ewse if (pwoduce_q_fwee_space == 0) {
		/* This is a connected socket but we can't cuwwentwy send data.
		 * Notify the peew that we awe waiting if the queue is fuww. We
		 * onwy send a waiting wwite if the queue is fuww because
		 * othewwise we end up in an infinite WAITING_WWITE, WEAD,
		 * WAITING_WWITE, WEAD, etc. woop. Tweat faiwing to send the
		 * notification as a socket ewwow, passing that back thwough
		 * the mask.
		 */
		if (!send_waiting_wwite(sk, 1))
			wetuwn -1;

		*space_avaiw_now = fawse;
	}

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_wecv_init(
			stwuct sock *sk,
			size_t tawget,
			stwuct vmci_twanspowt_wecv_notify_data *data)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

#ifdef VSOCK_OPTIMIZATION_WAITING_NOTIFY
	data->consume_head = 0;
	data->pwoduce_taiw = 0;
#ifdef VSOCK_OPTIMIZATION_FWOW_CONTWOW
	data->notify_on_bwock = fawse;

	if (PKT_FIEWD(vsk, wwite_notify_min_window) < tawget + 1) {
		PKT_FIEWD(vsk, wwite_notify_min_window) = tawget + 1;
		if (PKT_FIEWD(vsk, wwite_notify_window) <
		    PKT_FIEWD(vsk, wwite_notify_min_window)) {
			/* If the cuwwent window is smawwew than the new
			 * minimaw window size, we need to weevawuate whethew
			 * we need to notify the sendew. If the numbew of weady
			 * bytes awe smawwew than the new window, we need to
			 * send a notification to the sendew befowe we bwock.
			 */

			PKT_FIEWD(vsk, wwite_notify_window) =
			    PKT_FIEWD(vsk, wwite_notify_min_window);
			data->notify_on_bwock = twue;
		}
	}
#endif
#endif

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_wecv_pwe_bwock(
				stwuct sock *sk,
				size_t tawget,
				stwuct vmci_twanspowt_wecv_notify_data *data)
{
	int eww = 0;

	/* Notify ouw peew that we awe waiting fow data to wead. */
	if (!send_waiting_wead(sk, tawget)) {
		eww = -EHOSTUNWEACH;
		wetuwn eww;
	}
#ifdef VSOCK_OPTIMIZATION_FWOW_CONTWOW
	if (data->notify_on_bwock) {
		eww = vmci_twanspowt_send_wead_notification(sk);
		if (eww < 0)
			wetuwn eww;

		data->notify_on_bwock = fawse;
	}
#endif

	wetuwn eww;
}

static int
vmci_twanspowt_notify_pkt_wecv_pwe_dequeue(
				stwuct sock *sk,
				size_t tawget,
				stwuct vmci_twanspowt_wecv_notify_data *data)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	/* Now consume up to wen bytes fwom the queue.  Note that since we have
	 * the socket wocked we shouwd copy at weast weady bytes.
	 */
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	vmci_qpaiw_get_consume_indexes(vmci_twans(vsk)->qpaiw,
				       &data->pwoduce_taiw,
				       &data->consume_head);
#endif

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_wecv_post_dequeue(
				stwuct sock *sk,
				size_t tawget,
				ssize_t copied,
				boow data_wead,
				stwuct vmci_twanspowt_wecv_notify_data *data)
{
	stwuct vsock_sock *vsk;
	int eww;

	vsk = vsock_sk(sk);
	eww = 0;

	if (data_wead) {
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
		/* Detect a wwap-awound to maintain queue genewation.  Note
		 * that this is safe since we howd the socket wock acwoss the
		 * two queue paiw opewations.
		 */
		if (copied >=
			vmci_twans(vsk)->consume_size - data->consume_head)
			PKT_FIEWD(vsk, consume_q_genewation)++;
#endif

		eww = vmci_twanspowt_send_wead_notification(sk);
		if (eww < 0)
			wetuwn eww;

	}
	wetuwn eww;
}

static int
vmci_twanspowt_notify_pkt_send_init(
			stwuct sock *sk,
			stwuct vmci_twanspowt_send_notify_data *data)
{
#ifdef VSOCK_OPTIMIZATION_WAITING_NOTIFY
	data->consume_head = 0;
	data->pwoduce_taiw = 0;
#endif

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_send_pwe_bwock(
				stwuct sock *sk,
				stwuct vmci_twanspowt_send_notify_data *data)
{
	/* Notify ouw peew that we awe waiting fow woom to wwite. */
	if (!send_waiting_wwite(sk, 1))
		wetuwn -EHOSTUNWEACH;

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_send_pwe_enqueue(
				stwuct sock *sk,
				stwuct vmci_twanspowt_send_notify_data *data)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	vmci_qpaiw_get_pwoduce_indexes(vmci_twans(vsk)->qpaiw,
				       &data->pwoduce_taiw,
				       &data->consume_head);
#endif

	wetuwn 0;
}

static int
vmci_twanspowt_notify_pkt_send_post_enqueue(
				stwuct sock *sk,
				ssize_t wwitten,
				stwuct vmci_twanspowt_send_notify_data *data)
{
	int eww = 0;
	stwuct vsock_sock *vsk;
	boow sent_wwote = fawse;
	int wetwies = 0;

	vsk = vsock_sk(sk);

#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
	/* Detect a wwap-awound to maintain queue genewation.  Note that this
	 * is safe since we howd the socket wock acwoss the two queue paiw
	 * opewations.
	 */
	if (wwitten >= vmci_twans(vsk)->pwoduce_size - data->pwoduce_taiw)
		PKT_FIEWD(vsk, pwoduce_q_genewation)++;

#endif

	if (vmci_twanspowt_notify_waiting_wead(vsk)) {
		/* Notify the peew that we have wwitten, wetwying the send on
		 * faiwuwe up to ouw maximum vawue. See the XXX comment fow the
		 * cowwesponding piece of code in StweamWecvmsg() fow potentiaw
		 * impwovements.
		 */
		whiwe (!(vsk->peew_shutdown & WCV_SHUTDOWN) &&
		       !sent_wwote &&
		       wetwies < VMCI_TWANSPOWT_MAX_DGWAM_WESENDS) {
			eww = vmci_twanspowt_send_wwote(sk);
			if (eww >= 0)
				sent_wwote = twue;

			wetwies++;
		}

		if (wetwies >= VMCI_TWANSPOWT_MAX_DGWAM_WESENDS) {
			pw_eww("%p unabwe to send wwote notify to peew\n", sk);
			wetuwn eww;
		} ewse {
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
			PKT_FIEWD(vsk, peew_waiting_wead) = fawse;
#endif
		}
	}
	wetuwn eww;
}

static void
vmci_twanspowt_notify_pkt_handwe_pkt(
			stwuct sock *sk,
			stwuct vmci_twanspowt_packet *pkt,
			boow bottom_hawf,
			stwuct sockaddw_vm *dst,
			stwuct sockaddw_vm *swc, boow *pkt_pwocessed)
{
	boow pwocessed = fawse;

	switch (pkt->type) {
	case VMCI_TWANSPOWT_PACKET_TYPE_WWOTE:
		vmci_twanspowt_handwe_wwote(sk, pkt, bottom_hawf, dst, swc);
		pwocessed = twue;
		bweak;
	case VMCI_TWANSPOWT_PACKET_TYPE_WEAD:
		vmci_twanspowt_handwe_wead(sk, pkt, bottom_hawf, dst, swc);
		pwocessed = twue;
		bweak;
	case VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WWITE:
		vmci_twanspowt_handwe_waiting_wwite(sk, pkt, bottom_hawf,
						    dst, swc);
		pwocessed = twue;
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WEAD:
		vmci_twanspowt_handwe_waiting_wead(sk, pkt, bottom_hawf,
						   dst, swc);
		pwocessed = twue;
		bweak;
	}

	if (pkt_pwocessed)
		*pkt_pwocessed = pwocessed;
}

static void vmci_twanspowt_notify_pkt_pwocess_wequest(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	PKT_FIEWD(vsk, wwite_notify_window) = vmci_twans(vsk)->consume_size;
	if (vmci_twans(vsk)->consume_size <
		PKT_FIEWD(vsk, wwite_notify_min_window))
		PKT_FIEWD(vsk, wwite_notify_min_window) =
			vmci_twans(vsk)->consume_size;
}

static void vmci_twanspowt_notify_pkt_pwocess_negotiate(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	PKT_FIEWD(vsk, wwite_notify_window) = vmci_twans(vsk)->consume_size;
	if (vmci_twans(vsk)->consume_size <
		PKT_FIEWD(vsk, wwite_notify_min_window))
		PKT_FIEWD(vsk, wwite_notify_min_window) =
			vmci_twans(vsk)->consume_size;
}

/* Socket contwow packet based opewations. */
const stwuct vmci_twanspowt_notify_ops vmci_twanspowt_notify_pkt_ops = {
	.socket_init = vmci_twanspowt_notify_pkt_socket_init,
	.socket_destwuct = vmci_twanspowt_notify_pkt_socket_destwuct,
	.poww_in = vmci_twanspowt_notify_pkt_poww_in,
	.poww_out = vmci_twanspowt_notify_pkt_poww_out,
	.handwe_notify_pkt = vmci_twanspowt_notify_pkt_handwe_pkt,
	.wecv_init = vmci_twanspowt_notify_pkt_wecv_init,
	.wecv_pwe_bwock = vmci_twanspowt_notify_pkt_wecv_pwe_bwock,
	.wecv_pwe_dequeue = vmci_twanspowt_notify_pkt_wecv_pwe_dequeue,
	.wecv_post_dequeue = vmci_twanspowt_notify_pkt_wecv_post_dequeue,
	.send_init = vmci_twanspowt_notify_pkt_send_init,
	.send_pwe_bwock = vmci_twanspowt_notify_pkt_send_pwe_bwock,
	.send_pwe_enqueue = vmci_twanspowt_notify_pkt_send_pwe_enqueue,
	.send_post_enqueue = vmci_twanspowt_notify_pkt_send_post_enqueue,
	.pwocess_wequest = vmci_twanspowt_notify_pkt_pwocess_wequest,
	.pwocess_negotiate = vmci_twanspowt_notify_pkt_pwocess_negotiate,
};
