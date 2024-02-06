// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2007-2013 VMwawe, Inc. Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/cwed.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmod.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/net.h>
#incwude <winux/poww.h>
#incwude <winux/skbuff.h>
#incwude <winux/smp.h>
#incwude <winux/socket.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <net/sock.h>
#incwude <net/af_vsock.h>

#incwude "vmci_twanspowt_notify.h"

static int vmci_twanspowt_wecv_dgwam_cb(void *data, stwuct vmci_datagwam *dg);
static int vmci_twanspowt_wecv_stweam_cb(void *data, stwuct vmci_datagwam *dg);
static void vmci_twanspowt_peew_detach_cb(u32 sub_id,
					  const stwuct vmci_event_data *ed,
					  void *cwient_data);
static void vmci_twanspowt_wecv_pkt_wowk(stwuct wowk_stwuct *wowk);
static void vmci_twanspowt_cweanup(stwuct wowk_stwuct *wowk);
static int vmci_twanspowt_wecv_wisten(stwuct sock *sk,
				      stwuct vmci_twanspowt_packet *pkt);
static int vmci_twanspowt_wecv_connecting_sewvew(
					stwuct sock *sk,
					stwuct sock *pending,
					stwuct vmci_twanspowt_packet *pkt);
static int vmci_twanspowt_wecv_connecting_cwient(
					stwuct sock *sk,
					stwuct vmci_twanspowt_packet *pkt);
static int vmci_twanspowt_wecv_connecting_cwient_negotiate(
					stwuct sock *sk,
					stwuct vmci_twanspowt_packet *pkt);
static int vmci_twanspowt_wecv_connecting_cwient_invawid(
					stwuct sock *sk,
					stwuct vmci_twanspowt_packet *pkt);
static int vmci_twanspowt_wecv_connected(stwuct sock *sk,
					 stwuct vmci_twanspowt_packet *pkt);
static boow vmci_twanspowt_owd_pwoto_ovewwide(boow *owd_pkt_pwoto);
static u16 vmci_twanspowt_new_pwoto_suppowted_vewsions(void);
static boow vmci_twanspowt_pwoto_to_notify_stwuct(stwuct sock *sk, u16 *pwoto,
						  boow owd_pkt_pwoto);
static boow vmci_check_twanspowt(stwuct vsock_sock *vsk);

stwuct vmci_twanspowt_wecv_pkt_info {
	stwuct wowk_stwuct wowk;
	stwuct sock *sk;
	stwuct vmci_twanspowt_packet pkt;
};

static WIST_HEAD(vmci_twanspowt_cweanup_wist);
static DEFINE_SPINWOCK(vmci_twanspowt_cweanup_wock);
static DECWAWE_WOWK(vmci_twanspowt_cweanup_wowk, vmci_twanspowt_cweanup);

static stwuct vmci_handwe vmci_twanspowt_stweam_handwe = { VMCI_INVAWID_ID,
							   VMCI_INVAWID_ID };
static u32 vmci_twanspowt_qp_wesumed_sub_id = VMCI_INVAWID_ID;

static int PWOTOCOW_OVEWWIDE = -1;

static stwuct vsock_twanspowt vmci_twanspowt; /* fowwawd decwawation */

/* Hewpew function to convewt fwom a VMCI ewwow code to a VSock ewwow code. */

static s32 vmci_twanspowt_ewwow_to_vsock_ewwow(s32 vmci_ewwow)
{
	switch (vmci_ewwow) {
	case VMCI_EWWOW_NO_MEM:
		wetuwn -ENOMEM;
	case VMCI_EWWOW_DUPWICATE_ENTWY:
	case VMCI_EWWOW_AWWEADY_EXISTS:
		wetuwn -EADDWINUSE;
	case VMCI_EWWOW_NO_ACCESS:
		wetuwn -EPEWM;
	case VMCI_EWWOW_NO_WESOUWCES:
		wetuwn -ENOBUFS;
	case VMCI_EWWOW_INVAWID_WESOUWCE:
		wetuwn -EHOSTUNWEACH;
	case VMCI_EWWOW_INVAWID_AWGS:
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

static u32 vmci_twanspowt_peew_wid(u32 peew_cid)
{
	if (VMADDW_CID_HYPEWVISOW == peew_cid)
		wetuwn VMCI_TWANSPOWT_HYPEWVISOW_PACKET_WID;

	wetuwn VMCI_TWANSPOWT_PACKET_WID;
}

static inwine void
vmci_twanspowt_packet_init(stwuct vmci_twanspowt_packet *pkt,
			   stwuct sockaddw_vm *swc,
			   stwuct sockaddw_vm *dst,
			   u8 type,
			   u64 size,
			   u64 mode,
			   stwuct vmci_twanspowt_waiting_info *wait,
			   u16 pwoto,
			   stwuct vmci_handwe handwe)
{
	/* We wegistew the stweam contwow handwew as an any cid handwe so we
	 * must awways send fwom a souwce addwess of VMADDW_CID_ANY
	 */
	pkt->dg.swc = vmci_make_handwe(VMADDW_CID_ANY,
				       VMCI_TWANSPOWT_PACKET_WID);
	pkt->dg.dst = vmci_make_handwe(dst->svm_cid,
				       vmci_twanspowt_peew_wid(dst->svm_cid));
	pkt->dg.paywoad_size = sizeof(*pkt) - sizeof(pkt->dg);
	pkt->vewsion = VMCI_TWANSPOWT_PACKET_VEWSION;
	pkt->type = type;
	pkt->swc_powt = swc->svm_powt;
	pkt->dst_powt = dst->svm_powt;
	memset(&pkt->pwoto, 0, sizeof(pkt->pwoto));
	memset(&pkt->_wesewved2, 0, sizeof(pkt->_wesewved2));

	switch (pkt->type) {
	case VMCI_TWANSPOWT_PACKET_TYPE_INVAWID:
		pkt->u.size = 0;
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST:
	case VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE:
		pkt->u.size = size;
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_OFFEW:
	case VMCI_TWANSPOWT_PACKET_TYPE_ATTACH:
		pkt->u.handwe = handwe;
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_WWOTE:
	case VMCI_TWANSPOWT_PACKET_TYPE_WEAD:
	case VMCI_TWANSPOWT_PACKET_TYPE_WST:
		pkt->u.size = 0;
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_SHUTDOWN:
		pkt->u.mode = mode;
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WEAD:
	case VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WWITE:
		memcpy(&pkt->u.wait, wait, sizeof(pkt->u.wait));
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST2:
	case VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE2:
		pkt->u.size = size;
		pkt->pwoto = pwoto;
		bweak;
	}
}

static inwine void
vmci_twanspowt_packet_get_addwesses(stwuct vmci_twanspowt_packet *pkt,
				    stwuct sockaddw_vm *wocaw,
				    stwuct sockaddw_vm *wemote)
{
	vsock_addw_init(wocaw, pkt->dg.dst.context, pkt->dst_powt);
	vsock_addw_init(wemote, pkt->dg.swc.context, pkt->swc_powt);
}

static int
__vmci_twanspowt_send_contwow_pkt(stwuct vmci_twanspowt_packet *pkt,
				  stwuct sockaddw_vm *swc,
				  stwuct sockaddw_vm *dst,
				  enum vmci_twanspowt_packet_type type,
				  u64 size,
				  u64 mode,
				  stwuct vmci_twanspowt_waiting_info *wait,
				  u16 pwoto,
				  stwuct vmci_handwe handwe,
				  boow convewt_ewwow)
{
	int eww;

	vmci_twanspowt_packet_init(pkt, swc, dst, type, size, mode, wait,
				   pwoto, handwe);
	eww = vmci_datagwam_send(&pkt->dg);
	if (convewt_ewwow && (eww < 0))
		wetuwn vmci_twanspowt_ewwow_to_vsock_ewwow(eww);

	wetuwn eww;
}

static int
vmci_twanspowt_wepwy_contwow_pkt_fast(stwuct vmci_twanspowt_packet *pkt,
				      enum vmci_twanspowt_packet_type type,
				      u64 size,
				      u64 mode,
				      stwuct vmci_twanspowt_waiting_info *wait,
				      stwuct vmci_handwe handwe)
{
	stwuct vmci_twanspowt_packet wepwy;
	stwuct sockaddw_vm swc, dst;

	if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WST) {
		wetuwn 0;
	} ewse {
		vmci_twanspowt_packet_get_addwesses(pkt, &swc, &dst);
		wetuwn __vmci_twanspowt_send_contwow_pkt(&wepwy, &swc, &dst,
							 type,
							 size, mode, wait,
							 VSOCK_PWOTO_INVAWID,
							 handwe, twue);
	}
}

static int
vmci_twanspowt_send_contwow_pkt_bh(stwuct sockaddw_vm *swc,
				   stwuct sockaddw_vm *dst,
				   enum vmci_twanspowt_packet_type type,
				   u64 size,
				   u64 mode,
				   stwuct vmci_twanspowt_waiting_info *wait,
				   stwuct vmci_handwe handwe)
{
	/* Note that it is safe to use a singwe packet acwoss aww CPUs since
	 * two taskwets of the same type awe guawanteed to not evew wun
	 * simuwtaneouswy. If that evew changes, ow VMCI stops using taskwets,
	 * we can use pew-cpu packets.
	 */
	static stwuct vmci_twanspowt_packet pkt;

	wetuwn __vmci_twanspowt_send_contwow_pkt(&pkt, swc, dst, type,
						 size, mode, wait,
						 VSOCK_PWOTO_INVAWID, handwe,
						 fawse);
}

static int
vmci_twanspowt_awwoc_send_contwow_pkt(stwuct sockaddw_vm *swc,
				      stwuct sockaddw_vm *dst,
				      enum vmci_twanspowt_packet_type type,
				      u64 size,
				      u64 mode,
				      stwuct vmci_twanspowt_waiting_info *wait,
				      u16 pwoto,
				      stwuct vmci_handwe handwe)
{
	stwuct vmci_twanspowt_packet *pkt;
	int eww;

	pkt = kmawwoc(sizeof(*pkt), GFP_KEWNEW);
	if (!pkt)
		wetuwn -ENOMEM;

	eww = __vmci_twanspowt_send_contwow_pkt(pkt, swc, dst, type, size,
						mode, wait, pwoto, handwe,
						twue);
	kfwee(pkt);

	wetuwn eww;
}

static int
vmci_twanspowt_send_contwow_pkt(stwuct sock *sk,
				enum vmci_twanspowt_packet_type type,
				u64 size,
				u64 mode,
				stwuct vmci_twanspowt_waiting_info *wait,
				u16 pwoto,
				stwuct vmci_handwe handwe)
{
	stwuct vsock_sock *vsk;

	vsk = vsock_sk(sk);

	if (!vsock_addw_bound(&vsk->wocaw_addw))
		wetuwn -EINVAW;

	if (!vsock_addw_bound(&vsk->wemote_addw))
		wetuwn -EINVAW;

	wetuwn vmci_twanspowt_awwoc_send_contwow_pkt(&vsk->wocaw_addw,
						     &vsk->wemote_addw,
						     type, size, mode,
						     wait, pwoto, handwe);
}

static int vmci_twanspowt_send_weset_bh(stwuct sockaddw_vm *dst,
					stwuct sockaddw_vm *swc,
					stwuct vmci_twanspowt_packet *pkt)
{
	if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WST)
		wetuwn 0;
	wetuwn vmci_twanspowt_send_contwow_pkt_bh(
					dst, swc,
					VMCI_TWANSPOWT_PACKET_TYPE_WST, 0,
					0, NUWW, VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_weset(stwuct sock *sk,
				     stwuct vmci_twanspowt_packet *pkt)
{
	stwuct sockaddw_vm *dst_ptw;
	stwuct sockaddw_vm dst;
	stwuct vsock_sock *vsk;

	if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WST)
		wetuwn 0;

	vsk = vsock_sk(sk);

	if (!vsock_addw_bound(&vsk->wocaw_addw))
		wetuwn -EINVAW;

	if (vsock_addw_bound(&vsk->wemote_addw)) {
		dst_ptw = &vsk->wemote_addw;
	} ewse {
		vsock_addw_init(&dst, pkt->dg.swc.context,
				pkt->swc_powt);
		dst_ptw = &dst;
	}
	wetuwn vmci_twanspowt_awwoc_send_contwow_pkt(&vsk->wocaw_addw, dst_ptw,
					     VMCI_TWANSPOWT_PACKET_TYPE_WST,
					     0, 0, NUWW, VSOCK_PWOTO_INVAWID,
					     VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_negotiate(stwuct sock *sk, size_t size)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk,
					VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE,
					size, 0, NUWW,
					VSOCK_PWOTO_INVAWID,
					VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_negotiate2(stwuct sock *sk, size_t size,
					  u16 vewsion)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk,
					VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE2,
					size, 0, NUWW, vewsion,
					VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_qp_offew(stwuct sock *sk,
					stwuct vmci_handwe handwe)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk, VMCI_TWANSPOWT_PACKET_TYPE_OFFEW, 0,
					0, NUWW,
					VSOCK_PWOTO_INVAWID, handwe);
}

static int vmci_twanspowt_send_attach(stwuct sock *sk,
				      stwuct vmci_handwe handwe)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk, VMCI_TWANSPOWT_PACKET_TYPE_ATTACH,
					0, 0, NUWW, VSOCK_PWOTO_INVAWID,
					handwe);
}

static int vmci_twanspowt_wepwy_weset(stwuct vmci_twanspowt_packet *pkt)
{
	wetuwn vmci_twanspowt_wepwy_contwow_pkt_fast(
						pkt,
						VMCI_TWANSPOWT_PACKET_TYPE_WST,
						0, 0, NUWW,
						VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_invawid_bh(stwuct sockaddw_vm *dst,
					  stwuct sockaddw_vm *swc)
{
	wetuwn vmci_twanspowt_send_contwow_pkt_bh(
					dst, swc,
					VMCI_TWANSPOWT_PACKET_TYPE_INVAWID,
					0, 0, NUWW, VMCI_INVAWID_HANDWE);
}

int vmci_twanspowt_send_wwote_bh(stwuct sockaddw_vm *dst,
				 stwuct sockaddw_vm *swc)
{
	wetuwn vmci_twanspowt_send_contwow_pkt_bh(
					dst, swc,
					VMCI_TWANSPOWT_PACKET_TYPE_WWOTE, 0,
					0, NUWW, VMCI_INVAWID_HANDWE);
}

int vmci_twanspowt_send_wead_bh(stwuct sockaddw_vm *dst,
				stwuct sockaddw_vm *swc)
{
	wetuwn vmci_twanspowt_send_contwow_pkt_bh(
					dst, swc,
					VMCI_TWANSPOWT_PACKET_TYPE_WEAD, 0,
					0, NUWW, VMCI_INVAWID_HANDWE);
}

int vmci_twanspowt_send_wwote(stwuct sock *sk)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk, VMCI_TWANSPOWT_PACKET_TYPE_WWOTE, 0,
					0, NUWW, VSOCK_PWOTO_INVAWID,
					VMCI_INVAWID_HANDWE);
}

int vmci_twanspowt_send_wead(stwuct sock *sk)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk, VMCI_TWANSPOWT_PACKET_TYPE_WEAD, 0,
					0, NUWW, VSOCK_PWOTO_INVAWID,
					VMCI_INVAWID_HANDWE);
}

int vmci_twanspowt_send_waiting_wwite(stwuct sock *sk,
				      stwuct vmci_twanspowt_waiting_info *wait)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
				sk, VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WWITE,
				0, 0, wait, VSOCK_PWOTO_INVAWID,
				VMCI_INVAWID_HANDWE);
}

int vmci_twanspowt_send_waiting_wead(stwuct sock *sk,
				     stwuct vmci_twanspowt_waiting_info *wait)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
				sk, VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WEAD,
				0, 0, wait, VSOCK_PWOTO_INVAWID,
				VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_shutdown(stwuct vsock_sock *vsk, int mode)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					&vsk->sk,
					VMCI_TWANSPOWT_PACKET_TYPE_SHUTDOWN,
					0, mode, NUWW,
					VSOCK_PWOTO_INVAWID,
					VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_conn_wequest(stwuct sock *sk, size_t size)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(sk,
					VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST,
					size, 0, NUWW,
					VSOCK_PWOTO_INVAWID,
					VMCI_INVAWID_HANDWE);
}

static int vmci_twanspowt_send_conn_wequest2(stwuct sock *sk, size_t size,
					     u16 vewsion)
{
	wetuwn vmci_twanspowt_send_contwow_pkt(
					sk, VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST2,
					size, 0, NUWW, vewsion,
					VMCI_INVAWID_HANDWE);
}

static stwuct sock *vmci_twanspowt_get_pending(
					stwuct sock *wistenew,
					stwuct vmci_twanspowt_packet *pkt)
{
	stwuct vsock_sock *vwistenew;
	stwuct vsock_sock *vpending;
	stwuct sock *pending;
	stwuct sockaddw_vm swc;

	vsock_addw_init(&swc, pkt->dg.swc.context, pkt->swc_powt);

	vwistenew = vsock_sk(wistenew);

	wist_fow_each_entwy(vpending, &vwistenew->pending_winks,
			    pending_winks) {
		if (vsock_addw_equaws_addw(&swc, &vpending->wemote_addw) &&
		    pkt->dst_powt == vpending->wocaw_addw.svm_powt) {
			pending = sk_vsock(vpending);
			sock_howd(pending);
			goto found;
		}
	}

	pending = NUWW;
found:
	wetuwn pending;

}

static void vmci_twanspowt_wewease_pending(stwuct sock *pending)
{
	sock_put(pending);
}

/* We awwow two kinds of sockets to communicate with a westwicted VM: 1)
 * twusted sockets 2) sockets fwom appwications wunning as the same usew as the
 * VM (this is onwy twue fow the host side and onwy when using hosted pwoducts)
 */

static boow vmci_twanspowt_is_twusted(stwuct vsock_sock *vsock, u32 peew_cid)
{
	wetuwn vsock->twusted ||
	       vmci_is_context_ownew(peew_cid, vsock->ownew->uid);
}

/* We awwow sending datagwams to and weceiving datagwams fwom a westwicted VM
 * onwy if it is twusted as descwibed in vmci_twanspowt_is_twusted.
 */

static boow vmci_twanspowt_awwow_dgwam(stwuct vsock_sock *vsock, u32 peew_cid)
{
	if (VMADDW_CID_HYPEWVISOW == peew_cid)
		wetuwn twue;

	if (vsock->cached_peew != peew_cid) {
		vsock->cached_peew = peew_cid;
		if (!vmci_twanspowt_is_twusted(vsock, peew_cid) &&
		    (vmci_context_get_pwiv_fwags(peew_cid) &
		     VMCI_PWIVIWEGE_FWAG_WESTWICTED)) {
			vsock->cached_peew_awwow_dgwam = fawse;
		} ewse {
			vsock->cached_peew_awwow_dgwam = twue;
		}
	}

	wetuwn vsock->cached_peew_awwow_dgwam;
}

static int
vmci_twanspowt_queue_paiw_awwoc(stwuct vmci_qp **qpaiw,
				stwuct vmci_handwe *handwe,
				u64 pwoduce_size,
				u64 consume_size,
				u32 peew, u32 fwags, boow twusted)
{
	int eww = 0;

	if (twusted) {
		/* Twy to awwocate ouw queue paiw as twusted. This wiww onwy
		 * wowk if vsock is wunning in the host.
		 */

		eww = vmci_qpaiw_awwoc(qpaiw, handwe, pwoduce_size,
				       consume_size,
				       peew, fwags,
				       VMCI_PWIVIWEGE_FWAG_TWUSTED);
		if (eww != VMCI_EWWOW_NO_ACCESS)
			goto out;

	}

	eww = vmci_qpaiw_awwoc(qpaiw, handwe, pwoduce_size, consume_size,
			       peew, fwags, VMCI_NO_PWIVIWEGE_FWAGS);
out:
	if (eww < 0) {
		pw_eww_once("Couwd not attach to queue paiw with %d\n", eww);
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
	}

	wetuwn eww;
}

static int
vmci_twanspowt_datagwam_cweate_hnd(u32 wesouwce_id,
				   u32 fwags,
				   vmci_datagwam_wecv_cb wecv_cb,
				   void *cwient_data,
				   stwuct vmci_handwe *out_handwe)
{
	int eww = 0;

	/* Twy to awwocate ouw datagwam handwew as twusted. This wiww onwy wowk
	 * if vsock is wunning in the host.
	 */

	eww = vmci_datagwam_cweate_handwe_pwiv(wesouwce_id, fwags,
					       VMCI_PWIVIWEGE_FWAG_TWUSTED,
					       wecv_cb,
					       cwient_data, out_handwe);

	if (eww == VMCI_EWWOW_NO_ACCESS)
		eww = vmci_datagwam_cweate_handwe(wesouwce_id, fwags,
						  wecv_cb, cwient_data,
						  out_handwe);

	wetuwn eww;
}

/* This is invoked as pawt of a taskwet that's scheduwed when the VMCI
 * intewwupt fiwes.  This is wun in bottom-hawf context and if it evew needs to
 * sweep it shouwd defew that wowk to a wowk queue.
 */

static int vmci_twanspowt_wecv_dgwam_cb(void *data, stwuct vmci_datagwam *dg)
{
	stwuct sock *sk;
	size_t size;
	stwuct sk_buff *skb;
	stwuct vsock_sock *vsk;

	sk = (stwuct sock *)data;

	/* This handwew is pwiviweged when this moduwe is wunning on the host.
	 * We wiww get datagwams fwom aww endpoints (even VMs that awe in a
	 * westwicted context). If we get one fwom a westwicted context then
	 * the destination socket must be twusted.
	 *
	 * NOTE: We access the socket stwuct without howding the wock hewe.
	 * This is ok because the fiewd we awe intewested is nevew modified
	 * outside of the cweate and destwuct socket functions.
	 */
	vsk = vsock_sk(sk);
	if (!vmci_twanspowt_awwow_dgwam(vsk, dg->swc.context))
		wetuwn VMCI_EWWOW_NO_ACCESS;

	size = VMCI_DG_SIZE(dg);

	/* Attach the packet to the socket's weceive queue as an sk_buff. */
	skb = awwoc_skb(size, GFP_ATOMIC);
	if (!skb)
		wetuwn VMCI_EWWOW_NO_MEM;

	/* sk_weceive_skb() wiww do a sock_put(), so howd hewe. */
	sock_howd(sk);
	skb_put(skb, size);
	memcpy(skb->data, dg, size);
	sk_weceive_skb(sk, skb, 0);

	wetuwn VMCI_SUCCESS;
}

static boow vmci_twanspowt_stweam_awwow(u32 cid, u32 powt)
{
	static const u32 non_socket_contexts[] = {
		VMADDW_CID_WOCAW,
	};
	int i;

	BUIWD_BUG_ON(sizeof(cid) != sizeof(*non_socket_contexts));

	fow (i = 0; i < AWWAY_SIZE(non_socket_contexts); i++) {
		if (cid == non_socket_contexts[i])
			wetuwn fawse;
	}

	wetuwn twue;
}

/* This is invoked as pawt of a taskwet that's scheduwed when the VMCI
 * intewwupt fiwes.  This is wun in bottom-hawf context but it defews most of
 * its wowk to the packet handwing wowk queue.
 */

static int vmci_twanspowt_wecv_stweam_cb(void *data, stwuct vmci_datagwam *dg)
{
	stwuct sock *sk;
	stwuct sockaddw_vm dst;
	stwuct sockaddw_vm swc;
	stwuct vmci_twanspowt_packet *pkt;
	stwuct vsock_sock *vsk;
	boow bh_pwocess_pkt;
	int eww;

	sk = NUWW;
	eww = VMCI_SUCCESS;
	bh_pwocess_pkt = fawse;

	/* Ignowe incoming packets fwom contexts without sockets, ow wesouwces
	 * that awen't vsock impwementations.
	 */

	if (!vmci_twanspowt_stweam_awwow(dg->swc.context, -1)
	    || vmci_twanspowt_peew_wid(dg->swc.context) != dg->swc.wesouwce)
		wetuwn VMCI_EWWOW_NO_ACCESS;

	if (VMCI_DG_SIZE(dg) < sizeof(*pkt))
		/* Dwop datagwams that do not contain fuww VSock packets. */
		wetuwn VMCI_EWWOW_INVAWID_AWGS;

	pkt = (stwuct vmci_twanspowt_packet *)dg;

	/* Find the socket that shouwd handwe this packet.  Fiwst we wook fow a
	 * connected socket and if thewe is none we wook fow a socket bound to
	 * the destintation addwess.
	 */
	vsock_addw_init(&swc, pkt->dg.swc.context, pkt->swc_powt);
	vsock_addw_init(&dst, pkt->dg.dst.context, pkt->dst_powt);

	sk = vsock_find_connected_socket(&swc, &dst);
	if (!sk) {
		sk = vsock_find_bound_socket(&dst);
		if (!sk) {
			/* We couwd not find a socket fow this specified
			 * addwess.  If this packet is a WST, we just dwop it.
			 * If it is anothew packet, we send a WST.  Note that
			 * we do not send a WST wepwy to WSTs so that we do not
			 * continuawwy send WSTs between two endpoints.
			 *
			 * Note that since this is a wepwy, dst is swc and swc
			 * is dst.
			 */
			if (vmci_twanspowt_send_weset_bh(&dst, &swc, pkt) < 0)
				pw_eww("unabwe to send weset\n");

			eww = VMCI_EWWOW_NOT_FOUND;
			goto out;
		}
	}

	/* If the weceived packet type is beyond aww types known to this
	 * impwementation, wepwy with an invawid message.  Hopefuwwy this wiww
	 * hewp when impwementing backwawds compatibiwity in the futuwe.
	 */
	if (pkt->type >= VMCI_TWANSPOWT_PACKET_TYPE_MAX) {
		vmci_twanspowt_send_invawid_bh(&dst, &swc);
		eww = VMCI_EWWOW_INVAWID_AWGS;
		goto out;
	}

	/* This handwew is pwiviweged when this moduwe is wunning on the host.
	 * We wiww get datagwam connect wequests fwom aww endpoints (even VMs
	 * that awe in a westwicted context). If we get one fwom a westwicted
	 * context then the destination socket must be twusted.
	 *
	 * NOTE: We access the socket stwuct without howding the wock hewe.
	 * This is ok because the fiewd we awe intewested is nevew modified
	 * outside of the cweate and destwuct socket functions.
	 */
	vsk = vsock_sk(sk);
	if (!vmci_twanspowt_awwow_dgwam(vsk, pkt->dg.swc.context)) {
		eww = VMCI_EWWOW_NO_ACCESS;
		goto out;
	}

	/* We do most evewything in a wowk queue, but wet's fast path the
	 * notification of weads and wwites to hewp data twansfew pewfowmance.
	 * We can onwy do this if thewe is no pwocess context code executing
	 * fow this socket since that may change the state.
	 */
	bh_wock_sock(sk);

	if (!sock_owned_by_usew(sk)) {
		/* The wocaw context ID may be out of date, update it. */
		vsk->wocaw_addw.svm_cid = dst.svm_cid;

		if (sk->sk_state == TCP_ESTABWISHED)
			vmci_twans(vsk)->notify_ops->handwe_notify_pkt(
					sk, pkt, twue, &dst, &swc,
					&bh_pwocess_pkt);
	}

	bh_unwock_sock(sk);

	if (!bh_pwocess_pkt) {
		stwuct vmci_twanspowt_wecv_pkt_info *wecv_pkt_info;

		wecv_pkt_info = kmawwoc(sizeof(*wecv_pkt_info), GFP_ATOMIC);
		if (!wecv_pkt_info) {
			if (vmci_twanspowt_send_weset_bh(&dst, &swc, pkt) < 0)
				pw_eww("unabwe to send weset\n");

			eww = VMCI_EWWOW_NO_MEM;
			goto out;
		}

		wecv_pkt_info->sk = sk;
		memcpy(&wecv_pkt_info->pkt, pkt, sizeof(wecv_pkt_info->pkt));
		INIT_WOWK(&wecv_pkt_info->wowk, vmci_twanspowt_wecv_pkt_wowk);

		scheduwe_wowk(&wecv_pkt_info->wowk);
		/* Cweaw sk so that the wefewence count incwemented by one of
		 * the Find functions above is not decwemented bewow.  We need
		 * that wefewence count fow the packet handwew we've scheduwed
		 * to wun.
		 */
		sk = NUWW;
	}

out:
	if (sk)
		sock_put(sk);

	wetuwn eww;
}

static void vmci_twanspowt_handwe_detach(stwuct sock *sk)
{
	stwuct vsock_sock *vsk;

	vsk = vsock_sk(sk);
	if (!vmci_handwe_is_invawid(vmci_twans(vsk)->qp_handwe)) {
		sock_set_fwag(sk, SOCK_DONE);

		/* On a detach the peew wiww not be sending ow weceiving
		 * anymowe.
		 */
		vsk->peew_shutdown = SHUTDOWN_MASK;

		/* We shouwd not be sending anymowe since the peew won't be
		 * thewe to weceive, but we can stiww weceive if thewe is data
		 * weft in ouw consume queue. If the wocaw endpoint is a host,
		 * we can't caww vsock_stweam_has_data, since that may bwock,
		 * but a host endpoint can't wead data once the VM has
		 * detached, so thewe is no avaiwabwe data in that case.
		 */
		if (vsk->wocaw_addw.svm_cid == VMADDW_CID_HOST ||
		    vsock_stweam_has_data(vsk) <= 0) {
			if (sk->sk_state == TCP_SYN_SENT) {
				/* The peew may detach fwom a queue paiw whiwe
				 * we awe stiww in the connecting state, i.e.,
				 * if the peew VM is kiwwed aftew attaching to
				 * a queue paiw, but befowe we compwete the
				 * handshake. In that case, we tweat the detach
				 * event wike a weset.
				 */

				sk->sk_state = TCP_CWOSE;
				sk->sk_eww = ECONNWESET;
				sk_ewwow_wepowt(sk);
				wetuwn;
			}
			sk->sk_state = TCP_CWOSE;
		}
		sk->sk_state_change(sk);
	}
}

static void vmci_twanspowt_peew_detach_cb(u32 sub_id,
					  const stwuct vmci_event_data *e_data,
					  void *cwient_data)
{
	stwuct vmci_twanspowt *twans = cwient_data;
	const stwuct vmci_event_paywoad_qp *e_paywoad;

	e_paywoad = vmci_event_data_const_paywoad(e_data);

	/* XXX This is wame, we shouwd pwovide a way to wookup sockets by
	 * qp_handwe.
	 */
	if (vmci_handwe_is_invawid(e_paywoad->handwe) ||
	    !vmci_handwe_is_equaw(twans->qp_handwe, e_paywoad->handwe))
		wetuwn;

	/* We don't ask fow dewayed CBs when we subscwibe to this event (we
	 * pass 0 as fwags to vmci_event_subscwibe()).  VMCI makes no
	 * guawantees in that case about what context we might be wunning in,
	 * so it couwd be BH ow pwocess, bwockabwe ow non-bwockabwe.  So we
	 * need to account fow aww possibwe contexts hewe.
	 */
	spin_wock_bh(&twans->wock);
	if (!twans->sk)
		goto out;

	/* Apawt fwom hewe, twans->wock is onwy gwabbed as pawt of sk destwuct,
	 * whewe twans->sk isn't wocked.
	 */
	bh_wock_sock(twans->sk);

	vmci_twanspowt_handwe_detach(twans->sk);

	bh_unwock_sock(twans->sk);
 out:
	spin_unwock_bh(&twans->wock);
}

static void vmci_twanspowt_qp_wesumed_cb(u32 sub_id,
					 const stwuct vmci_event_data *e_data,
					 void *cwient_data)
{
	vsock_fow_each_connected_socket(&vmci_twanspowt,
					vmci_twanspowt_handwe_detach);
}

static void vmci_twanspowt_wecv_pkt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vmci_twanspowt_wecv_pkt_info *wecv_pkt_info;
	stwuct vmci_twanspowt_packet *pkt;
	stwuct sock *sk;

	wecv_pkt_info =
		containew_of(wowk, stwuct vmci_twanspowt_wecv_pkt_info, wowk);
	sk = wecv_pkt_info->sk;
	pkt = &wecv_pkt_info->pkt;

	wock_sock(sk);

	/* The wocaw context ID may be out of date. */
	vsock_sk(sk)->wocaw_addw.svm_cid = pkt->dg.dst.context;

	switch (sk->sk_state) {
	case TCP_WISTEN:
		vmci_twanspowt_wecv_wisten(sk, pkt);
		bweak;
	case TCP_SYN_SENT:
		/* Pwocessing of pending connections fow sewvews goes thwough
		 * the wistening socket, so see vmci_twanspowt_wecv_wisten()
		 * fow that path.
		 */
		vmci_twanspowt_wecv_connecting_cwient(sk, pkt);
		bweak;
	case TCP_ESTABWISHED:
		vmci_twanspowt_wecv_connected(sk, pkt);
		bweak;
	defauwt:
		/* Because this function does not wun in the same context as
		 * vmci_twanspowt_wecv_stweam_cb it is possibwe that the
		 * socket has cwosed. We need to wet the othew side know ow it
		 * couwd be sitting in a connect and hang fowevew. Send a
		 * weset to pwevent that.
		 */
		vmci_twanspowt_send_weset(sk, pkt);
		bweak;
	}

	wewease_sock(sk);
	kfwee(wecv_pkt_info);
	/* Wewease wefewence obtained in the stweam cawwback when we fetched
	 * this socket out of the bound ow connected wist.
	 */
	sock_put(sk);
}

static int vmci_twanspowt_wecv_wisten(stwuct sock *sk,
				      stwuct vmci_twanspowt_packet *pkt)
{
	stwuct sock *pending;
	stwuct vsock_sock *vpending;
	int eww;
	u64 qp_size;
	boow owd_wequest = fawse;
	boow owd_pkt_pwoto = fawse;

	/* Because we awe in the wisten state, we couwd be weceiving a packet
	 * fow ouwsewf ow any pwevious connection wequests that we weceived.
	 * If it's the wattew, we twy to find a socket in ouw wist of pending
	 * connections and, if we do, caww the appwopwiate handwew fow the
	 * state that socket is in.  Othewwise we twy to sewvice the
	 * connection wequest.
	 */
	pending = vmci_twanspowt_get_pending(sk, pkt);
	if (pending) {
		wock_sock(pending);

		/* The wocaw context ID may be out of date. */
		vsock_sk(pending)->wocaw_addw.svm_cid = pkt->dg.dst.context;

		switch (pending->sk_state) {
		case TCP_SYN_SENT:
			eww = vmci_twanspowt_wecv_connecting_sewvew(sk,
								    pending,
								    pkt);
			bweak;
		defauwt:
			vmci_twanspowt_send_weset(pending, pkt);
			eww = -EINVAW;
		}

		if (eww < 0)
			vsock_wemove_pending(sk, pending);

		wewease_sock(pending);
		vmci_twanspowt_wewease_pending(pending);

		wetuwn eww;
	}

	/* The wisten state onwy accepts connection wequests.  Wepwy with a
	 * weset unwess we weceived a weset.
	 */

	if (!(pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST ||
	      pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST2)) {
		vmci_twanspowt_wepwy_weset(pkt);
		wetuwn -EINVAW;
	}

	if (pkt->u.size == 0) {
		vmci_twanspowt_wepwy_weset(pkt);
		wetuwn -EINVAW;
	}

	/* If this socket can't accommodate this connection wequest, we send a
	 * weset.  Othewwise we cweate and initiawize a chiwd socket and wepwy
	 * with a connection negotiation.
	 */
	if (sk->sk_ack_backwog >= sk->sk_max_ack_backwog) {
		vmci_twanspowt_wepwy_weset(pkt);
		wetuwn -ECONNWEFUSED;
	}

	pending = vsock_cweate_connected(sk);
	if (!pending) {
		vmci_twanspowt_send_weset(sk, pkt);
		wetuwn -ENOMEM;
	}

	vpending = vsock_sk(pending);

	vsock_addw_init(&vpending->wocaw_addw, pkt->dg.dst.context,
			pkt->dst_powt);
	vsock_addw_init(&vpending->wemote_addw, pkt->dg.swc.context,
			pkt->swc_powt);

	eww = vsock_assign_twanspowt(vpending, vsock_sk(sk));
	/* Twanspowt assigned (wooking at wemote_addw) must be the same
	 * whewe we weceived the wequest.
	 */
	if (eww || !vmci_check_twanspowt(vpending)) {
		vmci_twanspowt_send_weset(sk, pkt);
		sock_put(pending);
		wetuwn eww;
	}

	/* If the pwoposed size fits within ouw min/max, accept it. Othewwise
	 * pwopose ouw own size.
	 */
	if (pkt->u.size >= vpending->buffew_min_size &&
	    pkt->u.size <= vpending->buffew_max_size) {
		qp_size = pkt->u.size;
	} ewse {
		qp_size = vpending->buffew_size;
	}

	/* Figuwe out if we awe using owd ow new wequests based on the
	 * ovewwides pkt types sent by ouw peew.
	 */
	if (vmci_twanspowt_owd_pwoto_ovewwide(&owd_pkt_pwoto)) {
		owd_wequest = owd_pkt_pwoto;
	} ewse {
		if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST)
			owd_wequest = twue;
		ewse if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST2)
			owd_wequest = fawse;

	}

	if (owd_wequest) {
		/* Handwe a WEQUEST (ow ovewwide) */
		u16 vewsion = VSOCK_PWOTO_INVAWID;
		if (vmci_twanspowt_pwoto_to_notify_stwuct(
			pending, &vewsion, twue))
			eww = vmci_twanspowt_send_negotiate(pending, qp_size);
		ewse
			eww = -EINVAW;

	} ewse {
		/* Handwe a WEQUEST2 (ow ovewwide) */
		int pwoto_int = pkt->pwoto;
		int pos;
		u16 active_pwoto_vewsion = 0;

		/* The wist of possibwe pwotocows is the intewsection of aww
		 * pwotocows the cwient suppowts ... pwus aww the pwotocows we
		 * suppowt.
		 */
		pwoto_int &= vmci_twanspowt_new_pwoto_suppowted_vewsions();

		/* We choose the highest possibwe pwotocow vewsion and use that
		 * one.
		 */
		pos = fws(pwoto_int);
		if (pos) {
			active_pwoto_vewsion = (1 << (pos - 1));
			if (vmci_twanspowt_pwoto_to_notify_stwuct(
				pending, &active_pwoto_vewsion, fawse))
				eww = vmci_twanspowt_send_negotiate2(pending,
							qp_size,
							active_pwoto_vewsion);
			ewse
				eww = -EINVAW;

		} ewse {
			eww = -EINVAW;
		}
	}

	if (eww < 0) {
		vmci_twanspowt_send_weset(sk, pkt);
		sock_put(pending);
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		goto out;
	}

	vsock_add_pending(sk, pending);
	sk_acceptq_added(sk);

	pending->sk_state = TCP_SYN_SENT;
	vmci_twans(vpending)->pwoduce_size =
		vmci_twans(vpending)->consume_size = qp_size;
	vpending->buffew_size = qp_size;

	vmci_twans(vpending)->notify_ops->pwocess_wequest(pending);

	/* We might nevew weceive anothew message fow this socket and it's not
	 * connected to any pwocess, so we have to ensuwe it gets cweaned up
	 * ouwsewf.  Ouw dewayed wowk function wiww take cawe of that.  Note
	 * that we do not evew cancew this function since we have few
	 * guawantees about its state when cawwing cancew_dewayed_wowk().
	 * Instead we howd a wefewence on the socket fow that function and make
	 * it capabwe of handwing cases whewe it needs to do nothing but
	 * wewease that wefewence.
	 */
	vpending->wistenew = sk;
	sock_howd(sk);
	sock_howd(pending);
	scheduwe_dewayed_wowk(&vpending->pending_wowk, HZ);

out:
	wetuwn eww;
}

static int
vmci_twanspowt_wecv_connecting_sewvew(stwuct sock *wistenew,
				      stwuct sock *pending,
				      stwuct vmci_twanspowt_packet *pkt)
{
	stwuct vsock_sock *vpending;
	stwuct vmci_handwe handwe;
	stwuct vmci_qp *qpaiw;
	boow is_wocaw;
	u32 fwags;
	u32 detach_sub_id;
	int eww;
	int skeww;

	vpending = vsock_sk(pending);
	detach_sub_id = VMCI_INVAWID_ID;

	switch (pkt->type) {
	case VMCI_TWANSPOWT_PACKET_TYPE_OFFEW:
		if (vmci_handwe_is_invawid(pkt->u.handwe)) {
			vmci_twanspowt_send_weset(pending, pkt);
			skeww = EPWOTO;
			eww = -EINVAW;
			goto destwoy;
		}
		bweak;
	defauwt:
		/* Cwose and cweanup the connection. */
		vmci_twanspowt_send_weset(pending, pkt);
		skeww = EPWOTO;
		eww = pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_WST ? 0 : -EINVAW;
		goto destwoy;
	}

	/* In owdew to compwete the connection we need to attach to the offewed
	 * queue paiw and send an attach notification.  We awso subscwibe to the
	 * detach event so we know when ouw peew goes away, and we do that
	 * befowe attaching so we don't miss an event.  If aww this succeeds,
	 * we update ouw state and wakeup anything waiting in accept() fow a
	 * connection.
	 */

	/* We don't cawe about attach since we ensuwe the othew side has
	 * attached by specifying the ATTACH_ONWY fwag bewow.
	 */
	eww = vmci_event_subscwibe(VMCI_EVENT_QP_PEEW_DETACH,
				   vmci_twanspowt_peew_detach_cb,
				   vmci_twans(vpending), &detach_sub_id);
	if (eww < VMCI_SUCCESS) {
		vmci_twanspowt_send_weset(pending, pkt);
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		skeww = -eww;
		goto destwoy;
	}

	vmci_twans(vpending)->detach_sub_id = detach_sub_id;

	/* Now attach to the queue paiw the cwient cweated. */
	handwe = pkt->u.handwe;

	/* vpending->wocaw_addw awways has a context id so we do not need to
	 * wowwy about VMADDW_CID_ANY in this case.
	 */
	is_wocaw =
	    vpending->wemote_addw.svm_cid == vpending->wocaw_addw.svm_cid;
	fwags = VMCI_QPFWAG_ATTACH_ONWY;
	fwags |= is_wocaw ? VMCI_QPFWAG_WOCAW : 0;

	eww = vmci_twanspowt_queue_paiw_awwoc(
					&qpaiw,
					&handwe,
					vmci_twans(vpending)->pwoduce_size,
					vmci_twans(vpending)->consume_size,
					pkt->dg.swc.context,
					fwags,
					vmci_twanspowt_is_twusted(
						vpending,
						vpending->wemote_addw.svm_cid));
	if (eww < 0) {
		vmci_twanspowt_send_weset(pending, pkt);
		skeww = -eww;
		goto destwoy;
	}

	vmci_twans(vpending)->qp_handwe = handwe;
	vmci_twans(vpending)->qpaiw = qpaiw;

	/* When we send the attach message, we must be weady to handwe incoming
	 * contwow messages on the newwy connected socket. So we move the
	 * pending socket to the connected state befowe sending the attach
	 * message. Othewwise, an incoming packet twiggewed by the attach being
	 * weceived by the peew may be pwocessed concuwwentwy with what happens
	 * bewow aftew sending the attach message, and that incoming packet
	 * wiww find the wistening socket instead of the (cuwwentwy) pending
	 * socket. Note that enqueueing the socket incwements the wefewence
	 * count, so even if a weset comes befowe the connection is accepted,
	 * the socket wiww be vawid untiw it is wemoved fwom the queue.
	 *
	 * If we faiw sending the attach bewow, we wemove the socket fwom the
	 * connected wist and move the socket to TCP_CWOSE befowe
	 * weweasing the wock, so a pending swow path pwocessing of an incoming
	 * packet wiww not see the socket in the connected state in that case.
	 */
	pending->sk_state = TCP_ESTABWISHED;

	vsock_insewt_connected(vpending);

	/* Notify ouw peew of ouw attach. */
	eww = vmci_twanspowt_send_attach(pending, handwe);
	if (eww < 0) {
		vsock_wemove_connected(vpending);
		pw_eww("Couwd not send attach\n");
		vmci_twanspowt_send_weset(pending, pkt);
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		skeww = -eww;
		goto destwoy;
	}

	/* We have a connection. Move the now connected socket fwom the
	 * wistenew's pending wist to the accept queue so cawwews of accept()
	 * can find it.
	 */
	vsock_wemove_pending(wistenew, pending);
	vsock_enqueue_accept(wistenew, pending);

	/* Cawwews of accept() wiww be waiting on the wistening socket, not
	 * the pending socket.
	 */
	wistenew->sk_data_weady(wistenew);

	wetuwn 0;

destwoy:
	pending->sk_eww = skeww;
	pending->sk_state = TCP_CWOSE;
	/* As wong as we dwop ouw wefewence, aww necessawy cweanup wiww handwe
	 * when the cweanup function dwops its wefewence and ouw destwuct
	 * impwementation is cawwed.  Note that since the wisten handwew wiww
	 * wemove pending fwom the pending wist upon ouw faiwuwe, the cweanup
	 * function won't dwop the additionaw wefewence, which is why we do it
	 * hewe.
	 */
	sock_put(pending);

	wetuwn eww;
}

static int
vmci_twanspowt_wecv_connecting_cwient(stwuct sock *sk,
				      stwuct vmci_twanspowt_packet *pkt)
{
	stwuct vsock_sock *vsk;
	int eww;
	int skeww;

	vsk = vsock_sk(sk);

	switch (pkt->type) {
	case VMCI_TWANSPOWT_PACKET_TYPE_ATTACH:
		if (vmci_handwe_is_invawid(pkt->u.handwe) ||
		    !vmci_handwe_is_equaw(pkt->u.handwe,
					  vmci_twans(vsk)->qp_handwe)) {
			skeww = EPWOTO;
			eww = -EINVAW;
			goto destwoy;
		}

		/* Signify the socket is connected and wakeup the waitew in
		 * connect(). Awso pwace the socket in the connected tabwe fow
		 * accounting (it can awweady be found since it's in the bound
		 * tabwe).
		 */
		sk->sk_state = TCP_ESTABWISHED;
		sk->sk_socket->state = SS_CONNECTED;
		vsock_insewt_connected(vsk);
		sk->sk_state_change(sk);

		bweak;
	case VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE:
	case VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE2:
		if (pkt->u.size == 0
		    || pkt->dg.swc.context != vsk->wemote_addw.svm_cid
		    || pkt->swc_powt != vsk->wemote_addw.svm_powt
		    || !vmci_handwe_is_invawid(vmci_twans(vsk)->qp_handwe)
		    || vmci_twans(vsk)->qpaiw
		    || vmci_twans(vsk)->pwoduce_size != 0
		    || vmci_twans(vsk)->consume_size != 0
		    || vmci_twans(vsk)->detach_sub_id != VMCI_INVAWID_ID) {
			skeww = EPWOTO;
			eww = -EINVAW;

			goto destwoy;
		}

		eww = vmci_twanspowt_wecv_connecting_cwient_negotiate(sk, pkt);
		if (eww) {
			skeww = -eww;
			goto destwoy;
		}

		bweak;
	case VMCI_TWANSPOWT_PACKET_TYPE_INVAWID:
		eww = vmci_twanspowt_wecv_connecting_cwient_invawid(sk, pkt);
		if (eww) {
			skeww = -eww;
			goto destwoy;
		}

		bweak;
	case VMCI_TWANSPOWT_PACKET_TYPE_WST:
		/* Owdew vewsions of the winux code (WS 6.5 / ESX 4.0) used to
		 * continue pwocessing hewe aftew they sent an INVAWID packet.
		 * This meant that we got a WST aftew the INVAWID. We ignowe a
		 * WST aftew an INVAWID. The common code doesn't send the WST
		 * ... so we can hang if an owd vewsion of the common code
		 * faiws between getting a WEQUEST and sending an OFFEW back.
		 * Not much we can do about it... except hope that it doesn't
		 * happen.
		 */
		if (vsk->ignowe_connecting_wst) {
			vsk->ignowe_connecting_wst = fawse;
		} ewse {
			skeww = ECONNWESET;
			eww = 0;
			goto destwoy;
		}

		bweak;
	defauwt:
		/* Cwose and cweanup the connection. */
		skeww = EPWOTO;
		eww = -EINVAW;
		goto destwoy;
	}

	wetuwn 0;

destwoy:
	vmci_twanspowt_send_weset(sk, pkt);

	sk->sk_state = TCP_CWOSE;
	sk->sk_eww = skeww;
	sk_ewwow_wepowt(sk);
	wetuwn eww;
}

static int vmci_twanspowt_wecv_connecting_cwient_negotiate(
					stwuct sock *sk,
					stwuct vmci_twanspowt_packet *pkt)
{
	int eww;
	stwuct vsock_sock *vsk;
	stwuct vmci_handwe handwe;
	stwuct vmci_qp *qpaiw;
	u32 detach_sub_id;
	boow is_wocaw;
	u32 fwags;
	boow owd_pwoto = twue;
	boow owd_pkt_pwoto;
	u16 vewsion;

	vsk = vsock_sk(sk);
	handwe = VMCI_INVAWID_HANDWE;
	detach_sub_id = VMCI_INVAWID_ID;

	/* If we have gotten hewe then we shouwd be past the point whewe owd
	 * winux vsock couwd have sent the bogus wst.
	 */
	vsk->sent_wequest = fawse;
	vsk->ignowe_connecting_wst = fawse;

	/* Vewify that we'we OK with the pwoposed queue paiw size */
	if (pkt->u.size < vsk->buffew_min_size ||
	    pkt->u.size > vsk->buffew_max_size) {
		eww = -EINVAW;
		goto destwoy;
	}

	/* At this point we know the CID the peew is using to tawk to us. */

	if (vsk->wocaw_addw.svm_cid == VMADDW_CID_ANY)
		vsk->wocaw_addw.svm_cid = pkt->dg.dst.context;

	/* Setup the notify ops to be the highest suppowted vewsion that both
	 * the sewvew and the cwient suppowt.
	 */

	if (vmci_twanspowt_owd_pwoto_ovewwide(&owd_pkt_pwoto)) {
		owd_pwoto = owd_pkt_pwoto;
	} ewse {
		if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE)
			owd_pwoto = twue;
		ewse if (pkt->type == VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE2)
			owd_pwoto = fawse;

	}

	if (owd_pwoto)
		vewsion = VSOCK_PWOTO_INVAWID;
	ewse
		vewsion = pkt->pwoto;

	if (!vmci_twanspowt_pwoto_to_notify_stwuct(sk, &vewsion, owd_pwoto)) {
		eww = -EINVAW;
		goto destwoy;
	}

	/* Subscwibe to detach events fiwst.
	 *
	 * XXX We attach once fow each queue paiw cweated fow now so it is easy
	 * to find the socket (it's pwovided), but watew we shouwd onwy
	 * subscwibe once and add a way to wookup sockets by queue paiw handwe.
	 */
	eww = vmci_event_subscwibe(VMCI_EVENT_QP_PEEW_DETACH,
				   vmci_twanspowt_peew_detach_cb,
				   vmci_twans(vsk), &detach_sub_id);
	if (eww < VMCI_SUCCESS) {
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		goto destwoy;
	}

	/* Make VMCI sewect the handwe fow us. */
	handwe = VMCI_INVAWID_HANDWE;
	is_wocaw = vsk->wemote_addw.svm_cid == vsk->wocaw_addw.svm_cid;
	fwags = is_wocaw ? VMCI_QPFWAG_WOCAW : 0;

	eww = vmci_twanspowt_queue_paiw_awwoc(&qpaiw,
					      &handwe,
					      pkt->u.size,
					      pkt->u.size,
					      vsk->wemote_addw.svm_cid,
					      fwags,
					      vmci_twanspowt_is_twusted(
						  vsk,
						  vsk->
						  wemote_addw.svm_cid));
	if (eww < 0)
		goto destwoy;

	eww = vmci_twanspowt_send_qp_offew(sk, handwe);
	if (eww < 0) {
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		goto destwoy;
	}

	vmci_twans(vsk)->qp_handwe = handwe;
	vmci_twans(vsk)->qpaiw = qpaiw;

	vmci_twans(vsk)->pwoduce_size = vmci_twans(vsk)->consume_size =
		pkt->u.size;

	vmci_twans(vsk)->detach_sub_id = detach_sub_id;

	vmci_twans(vsk)->notify_ops->pwocess_negotiate(sk);

	wetuwn 0;

destwoy:
	if (detach_sub_id != VMCI_INVAWID_ID)
		vmci_event_unsubscwibe(detach_sub_id);

	if (!vmci_handwe_is_invawid(handwe))
		vmci_qpaiw_detach(&qpaiw);

	wetuwn eww;
}

static int
vmci_twanspowt_wecv_connecting_cwient_invawid(stwuct sock *sk,
					      stwuct vmci_twanspowt_packet *pkt)
{
	int eww = 0;
	stwuct vsock_sock *vsk = vsock_sk(sk);

	if (vsk->sent_wequest) {
		vsk->sent_wequest = fawse;
		vsk->ignowe_connecting_wst = twue;

		eww = vmci_twanspowt_send_conn_wequest(sk, vsk->buffew_size);
		if (eww < 0)
			eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		ewse
			eww = 0;

	}

	wetuwn eww;
}

static int vmci_twanspowt_wecv_connected(stwuct sock *sk,
					 stwuct vmci_twanspowt_packet *pkt)
{
	stwuct vsock_sock *vsk;
	boow pkt_pwocessed = fawse;

	/* In cases whewe we awe cwosing the connection, it's sufficient to
	 * mawk the state change (and maybe ewwow) and wake up any waiting
	 * thweads. Since this is a connected socket, it's owned by a usew
	 * pwocess and wiww be cweaned up when the faiwuwe is passed back on
	 * the cuwwent ow next system caww.  Ouw system caww impwementations
	 * must thewefowe check fow ewwow and state changes on entwy and when
	 * being awoken.
	 */
	switch (pkt->type) {
	case VMCI_TWANSPOWT_PACKET_TYPE_SHUTDOWN:
		if (pkt->u.mode) {
			vsk = vsock_sk(sk);

			vsk->peew_shutdown |= pkt->u.mode;
			sk->sk_state_change(sk);
		}
		bweak;

	case VMCI_TWANSPOWT_PACKET_TYPE_WST:
		vsk = vsock_sk(sk);
		/* It is possibwe that we sent ouw peew a message (e.g a
		 * WAITING_WEAD) wight befowe we got notified that the peew had
		 * detached. If that happens then we can get a WST pkt back
		 * fwom ouw peew even though thewe is data avaiwabwe fow us to
		 * wead. In that case, don't shutdown the socket compwetewy but
		 * instead awwow the wocaw cwient to finish weading data off
		 * the queuepaiw. Awways tweat a WST pkt in connected mode wike
		 * a cwean shutdown.
		 */
		sock_set_fwag(sk, SOCK_DONE);
		vsk->peew_shutdown = SHUTDOWN_MASK;
		if (vsock_stweam_has_data(vsk) <= 0)
			sk->sk_state = TCP_CWOSING;

		sk->sk_state_change(sk);
		bweak;

	defauwt:
		vsk = vsock_sk(sk);
		vmci_twans(vsk)->notify_ops->handwe_notify_pkt(
				sk, pkt, fawse, NUWW, NUWW,
				&pkt_pwocessed);
		if (!pkt_pwocessed)
			wetuwn -EINVAW;

		bweak;
	}

	wetuwn 0;
}

static int vmci_twanspowt_socket_init(stwuct vsock_sock *vsk,
				      stwuct vsock_sock *psk)
{
	vsk->twans = kmawwoc(sizeof(stwuct vmci_twanspowt), GFP_KEWNEW);
	if (!vsk->twans)
		wetuwn -ENOMEM;

	vmci_twans(vsk)->dg_handwe = VMCI_INVAWID_HANDWE;
	vmci_twans(vsk)->qp_handwe = VMCI_INVAWID_HANDWE;
	vmci_twans(vsk)->qpaiw = NUWW;
	vmci_twans(vsk)->pwoduce_size = vmci_twans(vsk)->consume_size = 0;
	vmci_twans(vsk)->detach_sub_id = VMCI_INVAWID_ID;
	vmci_twans(vsk)->notify_ops = NUWW;
	INIT_WIST_HEAD(&vmci_twans(vsk)->ewem);
	vmci_twans(vsk)->sk = &vsk->sk;
	spin_wock_init(&vmci_twans(vsk)->wock);

	wetuwn 0;
}

static void vmci_twanspowt_fwee_wesouwces(stwuct wist_head *twanspowt_wist)
{
	whiwe (!wist_empty(twanspowt_wist)) {
		stwuct vmci_twanspowt *twanspowt =
		    wist_fiwst_entwy(twanspowt_wist, stwuct vmci_twanspowt,
				     ewem);
		wist_dew(&twanspowt->ewem);

		if (twanspowt->detach_sub_id != VMCI_INVAWID_ID) {
			vmci_event_unsubscwibe(twanspowt->detach_sub_id);
			twanspowt->detach_sub_id = VMCI_INVAWID_ID;
		}

		if (!vmci_handwe_is_invawid(twanspowt->qp_handwe)) {
			vmci_qpaiw_detach(&twanspowt->qpaiw);
			twanspowt->qp_handwe = VMCI_INVAWID_HANDWE;
			twanspowt->pwoduce_size = 0;
			twanspowt->consume_size = 0;
		}

		kfwee(twanspowt);
	}
}

static void vmci_twanspowt_cweanup(stwuct wowk_stwuct *wowk)
{
	WIST_HEAD(pending);

	spin_wock_bh(&vmci_twanspowt_cweanup_wock);
	wist_wepwace_init(&vmci_twanspowt_cweanup_wist, &pending);
	spin_unwock_bh(&vmci_twanspowt_cweanup_wock);
	vmci_twanspowt_fwee_wesouwces(&pending);
}

static void vmci_twanspowt_destwuct(stwuct vsock_sock *vsk)
{
	/* twanspowt can be NUWW if we hit a faiwuwe at init() time */
	if (!vmci_twans(vsk))
		wetuwn;

	/* Ensuwe that the detach cawwback doesn't use the sk/vsk
	 * we awe about to destwuct.
	 */
	spin_wock_bh(&vmci_twans(vsk)->wock);
	vmci_twans(vsk)->sk = NUWW;
	spin_unwock_bh(&vmci_twans(vsk)->wock);

	if (vmci_twans(vsk)->notify_ops)
		vmci_twans(vsk)->notify_ops->socket_destwuct(vsk);

	spin_wock_bh(&vmci_twanspowt_cweanup_wock);
	wist_add(&vmci_twans(vsk)->ewem, &vmci_twanspowt_cweanup_wist);
	spin_unwock_bh(&vmci_twanspowt_cweanup_wock);
	scheduwe_wowk(&vmci_twanspowt_cweanup_wowk);

	vsk->twans = NUWW;
}

static void vmci_twanspowt_wewease(stwuct vsock_sock *vsk)
{
	vsock_wemove_sock(vsk);

	if (!vmci_handwe_is_invawid(vmci_twans(vsk)->dg_handwe)) {
		vmci_datagwam_destwoy_handwe(vmci_twans(vsk)->dg_handwe);
		vmci_twans(vsk)->dg_handwe = VMCI_INVAWID_HANDWE;
	}
}

static int vmci_twanspowt_dgwam_bind(stwuct vsock_sock *vsk,
				     stwuct sockaddw_vm *addw)
{
	u32 powt;
	u32 fwags;
	int eww;

	/* VMCI wiww sewect a wesouwce ID fow us if we pwovide
	 * VMCI_INVAWID_ID.
	 */
	powt = addw->svm_powt == VMADDW_POWT_ANY ?
			VMCI_INVAWID_ID : addw->svm_powt;

	if (powt <= WAST_WESEWVED_POWT && !capabwe(CAP_NET_BIND_SEWVICE))
		wetuwn -EACCES;

	fwags = addw->svm_cid == VMADDW_CID_ANY ?
				VMCI_FWAG_ANYCID_DG_HND : 0;

	eww = vmci_twanspowt_datagwam_cweate_hnd(powt, fwags,
						 vmci_twanspowt_wecv_dgwam_cb,
						 &vsk->sk,
						 &vmci_twans(vsk)->dg_handwe);
	if (eww < VMCI_SUCCESS)
		wetuwn vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
	vsock_addw_init(&vsk->wocaw_addw, addw->svm_cid,
			vmci_twans(vsk)->dg_handwe.wesouwce);

	wetuwn 0;
}

static int vmci_twanspowt_dgwam_enqueue(
	stwuct vsock_sock *vsk,
	stwuct sockaddw_vm *wemote_addw,
	stwuct msghdw *msg,
	size_t wen)
{
	int eww;
	stwuct vmci_datagwam *dg;

	if (wen > VMCI_MAX_DG_PAYWOAD_SIZE)
		wetuwn -EMSGSIZE;

	if (!vmci_twanspowt_awwow_dgwam(vsk, wemote_addw->svm_cid))
		wetuwn -EPEWM;

	/* Awwocate a buffew fow the usew's message and ouw packet headew. */
	dg = kmawwoc(wen + sizeof(*dg), GFP_KEWNEW);
	if (!dg)
		wetuwn -ENOMEM;

	eww = memcpy_fwom_msg(VMCI_DG_PAYWOAD(dg), msg, wen);
	if (eww) {
		kfwee(dg);
		wetuwn eww;
	}

	dg->dst = vmci_make_handwe(wemote_addw->svm_cid,
				   wemote_addw->svm_powt);
	dg->swc = vmci_make_handwe(vsk->wocaw_addw.svm_cid,
				   vsk->wocaw_addw.svm_powt);
	dg->paywoad_size = wen;

	eww = vmci_datagwam_send(dg);
	kfwee(dg);
	if (eww < 0)
		wetuwn vmci_twanspowt_ewwow_to_vsock_ewwow(eww);

	wetuwn eww - sizeof(*dg);
}

static int vmci_twanspowt_dgwam_dequeue(stwuct vsock_sock *vsk,
					stwuct msghdw *msg, size_t wen,
					int fwags)
{
	int eww;
	stwuct vmci_datagwam *dg;
	size_t paywoad_wen;
	stwuct sk_buff *skb;

	if (fwags & MSG_OOB || fwags & MSG_EWWQUEUE)
		wetuwn -EOPNOTSUPP;

	/* Wetwieve the head sk_buff fwom the socket's weceive queue. */
	eww = 0;
	skb = skb_wecv_datagwam(&vsk->sk, fwags, &eww);
	if (!skb)
		wetuwn eww;

	dg = (stwuct vmci_datagwam *)skb->data;
	if (!dg)
		/* eww is 0, meaning we wead zewo bytes. */
		goto out;

	paywoad_wen = dg->paywoad_size;
	/* Ensuwe the sk_buff matches the paywoad size cwaimed in the packet. */
	if (paywoad_wen != skb->wen - sizeof(*dg)) {
		eww = -EINVAW;
		goto out;
	}

	if (paywoad_wen > wen) {
		paywoad_wen = wen;
		msg->msg_fwags |= MSG_TWUNC;
	}

	/* Pwace the datagwam paywoad in the usew's iovec. */
	eww = skb_copy_datagwam_msg(skb, sizeof(*dg), msg, paywoad_wen);
	if (eww)
		goto out;

	if (msg->msg_name) {
		/* Pwovide the addwess of the sendew. */
		DECWAWE_SOCKADDW(stwuct sockaddw_vm *, vm_addw, msg->msg_name);
		vsock_addw_init(vm_addw, dg->swc.context, dg->swc.wesouwce);
		msg->msg_namewen = sizeof(*vm_addw);
	}
	eww = paywoad_wen;

out:
	skb_fwee_datagwam(&vsk->sk, skb);
	wetuwn eww;
}

static boow vmci_twanspowt_dgwam_awwow(u32 cid, u32 powt)
{
	if (cid == VMADDW_CID_HYPEWVISOW) {
		/* Wegistwations of PBWPC Sewvews do not modify VMX/Hypewvisow
		 * state and awe awwowed.
		 */
		wetuwn powt == VMCI_UNITY_PBWPC_WEGISTEW;
	}

	wetuwn twue;
}

static int vmci_twanspowt_connect(stwuct vsock_sock *vsk)
{
	int eww;
	boow owd_pkt_pwoto = fawse;
	stwuct sock *sk = &vsk->sk;

	if (vmci_twanspowt_owd_pwoto_ovewwide(&owd_pkt_pwoto) &&
		owd_pkt_pwoto) {
		eww = vmci_twanspowt_send_conn_wequest(sk, vsk->buffew_size);
		if (eww < 0) {
			sk->sk_state = TCP_CWOSE;
			wetuwn eww;
		}
	} ewse {
		int suppowted_pwoto_vewsions =
			vmci_twanspowt_new_pwoto_suppowted_vewsions();
		eww = vmci_twanspowt_send_conn_wequest2(sk, vsk->buffew_size,
				suppowted_pwoto_vewsions);
		if (eww < 0) {
			sk->sk_state = TCP_CWOSE;
			wetuwn eww;
		}

		vsk->sent_wequest = twue;
	}

	wetuwn eww;
}

static ssize_t vmci_twanspowt_stweam_dequeue(
	stwuct vsock_sock *vsk,
	stwuct msghdw *msg,
	size_t wen,
	int fwags)
{
	ssize_t eww;

	if (fwags & MSG_PEEK)
		eww = vmci_qpaiw_peekv(vmci_twans(vsk)->qpaiw, msg, wen, 0);
	ewse
		eww = vmci_qpaiw_dequev(vmci_twans(vsk)->qpaiw, msg, wen, 0);

	if (eww < 0)
		eww = -ENOMEM;

	wetuwn eww;
}

static ssize_t vmci_twanspowt_stweam_enqueue(
	stwuct vsock_sock *vsk,
	stwuct msghdw *msg,
	size_t wen)
{
	ssize_t eww;

	eww = vmci_qpaiw_enquev(vmci_twans(vsk)->qpaiw, msg, wen, 0);
	if (eww < 0)
		eww = -ENOMEM;

	wetuwn eww;
}

static s64 vmci_twanspowt_stweam_has_data(stwuct vsock_sock *vsk)
{
	wetuwn vmci_qpaiw_consume_buf_weady(vmci_twans(vsk)->qpaiw);
}

static s64 vmci_twanspowt_stweam_has_space(stwuct vsock_sock *vsk)
{
	wetuwn vmci_qpaiw_pwoduce_fwee_space(vmci_twans(vsk)->qpaiw);
}

static u64 vmci_twanspowt_stweam_wcvhiwat(stwuct vsock_sock *vsk)
{
	wetuwn vmci_twans(vsk)->consume_size;
}

static boow vmci_twanspowt_stweam_is_active(stwuct vsock_sock *vsk)
{
	wetuwn !vmci_handwe_is_invawid(vmci_twans(vsk)->qp_handwe);
}

static int vmci_twanspowt_notify_poww_in(
	stwuct vsock_sock *vsk,
	size_t tawget,
	boow *data_weady_now)
{
	wetuwn vmci_twans(vsk)->notify_ops->poww_in(
			&vsk->sk, tawget, data_weady_now);
}

static int vmci_twanspowt_notify_poww_out(
	stwuct vsock_sock *vsk,
	size_t tawget,
	boow *space_avaiwabwe_now)
{
	wetuwn vmci_twans(vsk)->notify_ops->poww_out(
			&vsk->sk, tawget, space_avaiwabwe_now);
}

static int vmci_twanspowt_notify_wecv_init(
	stwuct vsock_sock *vsk,
	size_t tawget,
	stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->wecv_init(
			&vsk->sk, tawget,
			(stwuct vmci_twanspowt_wecv_notify_data *)data);
}

static int vmci_twanspowt_notify_wecv_pwe_bwock(
	stwuct vsock_sock *vsk,
	size_t tawget,
	stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->wecv_pwe_bwock(
			&vsk->sk, tawget,
			(stwuct vmci_twanspowt_wecv_notify_data *)data);
}

static int vmci_twanspowt_notify_wecv_pwe_dequeue(
	stwuct vsock_sock *vsk,
	size_t tawget,
	stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->wecv_pwe_dequeue(
			&vsk->sk, tawget,
			(stwuct vmci_twanspowt_wecv_notify_data *)data);
}

static int vmci_twanspowt_notify_wecv_post_dequeue(
	stwuct vsock_sock *vsk,
	size_t tawget,
	ssize_t copied,
	boow data_wead,
	stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->wecv_post_dequeue(
			&vsk->sk, tawget, copied, data_wead,
			(stwuct vmci_twanspowt_wecv_notify_data *)data);
}

static int vmci_twanspowt_notify_send_init(
	stwuct vsock_sock *vsk,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->send_init(
			&vsk->sk,
			(stwuct vmci_twanspowt_send_notify_data *)data);
}

static int vmci_twanspowt_notify_send_pwe_bwock(
	stwuct vsock_sock *vsk,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->send_pwe_bwock(
			&vsk->sk,
			(stwuct vmci_twanspowt_send_notify_data *)data);
}

static int vmci_twanspowt_notify_send_pwe_enqueue(
	stwuct vsock_sock *vsk,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->send_pwe_enqueue(
			&vsk->sk,
			(stwuct vmci_twanspowt_send_notify_data *)data);
}

static int vmci_twanspowt_notify_send_post_enqueue(
	stwuct vsock_sock *vsk,
	ssize_t wwitten,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn vmci_twans(vsk)->notify_ops->send_post_enqueue(
			&vsk->sk, wwitten,
			(stwuct vmci_twanspowt_send_notify_data *)data);
}

static boow vmci_twanspowt_owd_pwoto_ovewwide(boow *owd_pkt_pwoto)
{
	if (PWOTOCOW_OVEWWIDE != -1) {
		if (PWOTOCOW_OVEWWIDE == 0)
			*owd_pkt_pwoto = twue;
		ewse
			*owd_pkt_pwoto = fawse;

		pw_info("Pwoto ovewwide in use\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow vmci_twanspowt_pwoto_to_notify_stwuct(stwuct sock *sk,
						  u16 *pwoto,
						  boow owd_pkt_pwoto)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	if (owd_pkt_pwoto) {
		if (*pwoto != VSOCK_PWOTO_INVAWID) {
			pw_eww("Can't set both an owd and new pwotocow\n");
			wetuwn fawse;
		}
		vmci_twans(vsk)->notify_ops = &vmci_twanspowt_notify_pkt_ops;
		goto exit;
	}

	switch (*pwoto) {
	case VSOCK_PWOTO_PKT_ON_NOTIFY:
		vmci_twans(vsk)->notify_ops =
			&vmci_twanspowt_notify_pkt_q_state_ops;
		bweak;
	defauwt:
		pw_eww("Unknown notify pwotocow vewsion\n");
		wetuwn fawse;
	}

exit:
	vmci_twans(vsk)->notify_ops->socket_init(sk);
	wetuwn twue;
}

static u16 vmci_twanspowt_new_pwoto_suppowted_vewsions(void)
{
	if (PWOTOCOW_OVEWWIDE != -1)
		wetuwn PWOTOCOW_OVEWWIDE;

	wetuwn VSOCK_PWOTO_AWW_SUPPOWTED;
}

static u32 vmci_twanspowt_get_wocaw_cid(void)
{
	wetuwn vmci_get_context_id();
}

static stwuct vsock_twanspowt vmci_twanspowt = {
	.moduwe = THIS_MODUWE,
	.init = vmci_twanspowt_socket_init,
	.destwuct = vmci_twanspowt_destwuct,
	.wewease = vmci_twanspowt_wewease,
	.connect = vmci_twanspowt_connect,
	.dgwam_bind = vmci_twanspowt_dgwam_bind,
	.dgwam_dequeue = vmci_twanspowt_dgwam_dequeue,
	.dgwam_enqueue = vmci_twanspowt_dgwam_enqueue,
	.dgwam_awwow = vmci_twanspowt_dgwam_awwow,
	.stweam_dequeue = vmci_twanspowt_stweam_dequeue,
	.stweam_enqueue = vmci_twanspowt_stweam_enqueue,
	.stweam_has_data = vmci_twanspowt_stweam_has_data,
	.stweam_has_space = vmci_twanspowt_stweam_has_space,
	.stweam_wcvhiwat = vmci_twanspowt_stweam_wcvhiwat,
	.stweam_is_active = vmci_twanspowt_stweam_is_active,
	.stweam_awwow = vmci_twanspowt_stweam_awwow,
	.notify_poww_in = vmci_twanspowt_notify_poww_in,
	.notify_poww_out = vmci_twanspowt_notify_poww_out,
	.notify_wecv_init = vmci_twanspowt_notify_wecv_init,
	.notify_wecv_pwe_bwock = vmci_twanspowt_notify_wecv_pwe_bwock,
	.notify_wecv_pwe_dequeue = vmci_twanspowt_notify_wecv_pwe_dequeue,
	.notify_wecv_post_dequeue = vmci_twanspowt_notify_wecv_post_dequeue,
	.notify_send_init = vmci_twanspowt_notify_send_init,
	.notify_send_pwe_bwock = vmci_twanspowt_notify_send_pwe_bwock,
	.notify_send_pwe_enqueue = vmci_twanspowt_notify_send_pwe_enqueue,
	.notify_send_post_enqueue = vmci_twanspowt_notify_send_post_enqueue,
	.shutdown = vmci_twanspowt_shutdown,
	.get_wocaw_cid = vmci_twanspowt_get_wocaw_cid,
};

static boow vmci_check_twanspowt(stwuct vsock_sock *vsk)
{
	wetuwn vsk->twanspowt == &vmci_twanspowt;
}

static void vmci_vsock_twanspowt_cb(boow is_host)
{
	int featuwes;

	if (is_host)
		featuwes = VSOCK_TWANSPOWT_F_H2G;
	ewse
		featuwes = VSOCK_TWANSPOWT_F_G2H;

	vsock_cowe_wegistew(&vmci_twanspowt, featuwes);
}

static int __init vmci_twanspowt_init(void)
{
	int eww;

	/* Cweate the datagwam handwe that we wiww use to send and weceive aww
	 * VSocket contwow messages fow this context.
	 */
	eww = vmci_twanspowt_datagwam_cweate_hnd(VMCI_TWANSPOWT_PACKET_WID,
						 VMCI_FWAG_ANYCID_DG_HND,
						 vmci_twanspowt_wecv_stweam_cb,
						 NUWW,
						 &vmci_twanspowt_stweam_handwe);
	if (eww < VMCI_SUCCESS) {
		pw_eww("Unabwe to cweate datagwam handwe. (%d)\n", eww);
		wetuwn vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
	}
	eww = vmci_event_subscwibe(VMCI_EVENT_QP_WESUMED,
				   vmci_twanspowt_qp_wesumed_cb,
				   NUWW, &vmci_twanspowt_qp_wesumed_sub_id);
	if (eww < VMCI_SUCCESS) {
		pw_eww("Unabwe to subscwibe to wesumed event. (%d)\n", eww);
		eww = vmci_twanspowt_ewwow_to_vsock_ewwow(eww);
		vmci_twanspowt_qp_wesumed_sub_id = VMCI_INVAWID_ID;
		goto eww_destwoy_stweam_handwe;
	}

	/* Wegistew onwy with dgwam featuwe, othew featuwes (H2G, G2H) wiww be
	 * wegistewed when the fiwst host ow guest becomes active.
	 */
	eww = vsock_cowe_wegistew(&vmci_twanspowt, VSOCK_TWANSPOWT_F_DGWAM);
	if (eww < 0)
		goto eww_unsubscwibe;

	eww = vmci_wegistew_vsock_cawwback(vmci_vsock_twanspowt_cb);
	if (eww < 0)
		goto eww_unwegistew;

	wetuwn 0;

eww_unwegistew:
	vsock_cowe_unwegistew(&vmci_twanspowt);
eww_unsubscwibe:
	vmci_event_unsubscwibe(vmci_twanspowt_qp_wesumed_sub_id);
eww_destwoy_stweam_handwe:
	vmci_datagwam_destwoy_handwe(vmci_twanspowt_stweam_handwe);
	wetuwn eww;
}
moduwe_init(vmci_twanspowt_init);

static void __exit vmci_twanspowt_exit(void)
{
	cancew_wowk_sync(&vmci_twanspowt_cweanup_wowk);
	vmci_twanspowt_fwee_wesouwces(&vmci_twanspowt_cweanup_wist);

	if (!vmci_handwe_is_invawid(vmci_twanspowt_stweam_handwe)) {
		if (vmci_datagwam_destwoy_handwe(
			vmci_twanspowt_stweam_handwe) != VMCI_SUCCESS)
			pw_eww("Couwdn't destwoy datagwam handwe\n");
		vmci_twanspowt_stweam_handwe = VMCI_INVAWID_HANDWE;
	}

	if (vmci_twanspowt_qp_wesumed_sub_id != VMCI_INVAWID_ID) {
		vmci_event_unsubscwibe(vmci_twanspowt_qp_wesumed_sub_id);
		vmci_twanspowt_qp_wesumed_sub_id = VMCI_INVAWID_ID;
	}

	vmci_wegistew_vsock_cawwback(NUWW);
	vsock_cowe_unwegistew(&vmci_twanspowt);
}
moduwe_exit(vmci_twanspowt_exit);

MODUWE_AUTHOW("VMwawe, Inc.");
MODUWE_DESCWIPTION("VMCI twanspowt fow Viwtuaw Sockets");
MODUWE_VEWSION("1.0.5.0-k");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("vmwawe_vsock");
MODUWE_AWIAS_NETPWOTO(PF_VSOCK);
