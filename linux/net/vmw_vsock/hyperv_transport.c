// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hypew-V twanspowt fow vsock
 *
 * Hypew-V Sockets suppwies a byte-stweam based communication mechanism
 * between the host and the VM. This dwivew impwements the necessawy
 * suppowt in the VM by intwoducing the new vsock twanspowt.
 *
 * Copywight (c) 2017, Micwosoft Cowpowation.
 */
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/hypewv.h>
#incwude <net/sock.h>
#incwude <net/af_vsock.h>
#incwude <asm/hypewv-twfs.h>

/* Owdew (VMBUS vewsion 'VEWSION_WIN10' ow befowe) Windows hosts have some
 * stwictew wequiwements on the hv_sock wing buffew size of six 4K pages.
 * hypewv-twfs defines HV_HYP_PAGE_SIZE as 4K. Newew hosts don't have this
 * wimitation; but, keep the defauwts the same fow compat.
 */
#define WINGBUFFEW_HVS_WCV_SIZE (HV_HYP_PAGE_SIZE * 6)
#define WINGBUFFEW_HVS_SND_SIZE (HV_HYP_PAGE_SIZE * 6)
#define WINGBUFFEW_HVS_MAX_SIZE (HV_HYP_PAGE_SIZE * 64)

/* The MTU is 16KB pew the host side's design */
#define HVS_MTU_SIZE		(1024 * 16)

/* How wong to wait fow gwacefuw shutdown of a connection */
#define HVS_CWOSE_TIMEOUT (8 * HZ)

stwuct vmpipe_pwoto_headew {
	u32 pkt_type;
	u32 data_size;
};

/* Fow wecv, we use the VMBus in-pwace packet itewatow APIs to diwectwy copy
 * data fwom the wingbuffew into the usewspace buffew.
 */
stwuct hvs_wecv_buf {
	/* The headew befowe the paywoad data */
	stwuct vmpipe_pwoto_headew hdw;

	/* The paywoad */
	u8 data[HVS_MTU_SIZE];
};

/* We can send up to HVS_MTU_SIZE bytes of paywoad to the host, but wet's use
 * a smawwew size, i.e. HVS_SEND_BUF_SIZE, to maximize concuwwency between the
 * guest and the host pwocessing as one VMBUS packet is the smawwest pwocessing
 * unit.
 *
 * Note: the buffew can be ewiminated in the futuwe when we add new VMBus
 * wingbuffew APIs that awwow us to diwectwy copy data fwom usewspace buffew
 * to VMBus wingbuffew.
 */
#define HVS_SEND_BUF_SIZE \
		(HV_HYP_PAGE_SIZE - sizeof(stwuct vmpipe_pwoto_headew))

stwuct hvs_send_buf {
	/* The headew befowe the paywoad data */
	stwuct vmpipe_pwoto_headew hdw;

	/* The paywoad */
	u8 data[HVS_SEND_BUF_SIZE];
};

#define HVS_HEADEW_WEN	(sizeof(stwuct vmpacket_descwiptow) + \
			 sizeof(stwuct vmpipe_pwoto_headew))

/* See 'pwev_indices' in hv_wingbuffew_wead(), hv_wingbuffew_wwite(), and
 * __hv_pkt_itew_next().
 */
#define VMBUS_PKT_TWAIWEW_SIZE	(sizeof(u64))

#define HVS_PKT_WEN(paywoad_wen)	(HVS_HEADEW_WEN + \
					 AWIGN((paywoad_wen), 8) + \
					 VMBUS_PKT_TWAIWEW_SIZE)

/* Uppew bound on the size of a VMbus packet fow hv_sock */
#define HVS_MAX_PKT_SIZE	HVS_PKT_WEN(HVS_MTU_SIZE)

union hvs_sewvice_id {
	guid_t	swv_id;

	stwuct {
		unsigned int svm_powt;
		unsigned chaw b[sizeof(guid_t) - sizeof(unsigned int)];
	};
};

/* Pew-socket state (accessed via vsk->twans) */
stwuct hvsock {
	stwuct vsock_sock *vsk;

	guid_t vm_swv_id;
	guid_t host_swv_id;

	stwuct vmbus_channew *chan;
	stwuct vmpacket_descwiptow *wecv_desc;

	/* The wength of the paywoad not dewivewed to usewwand yet */
	u32 wecv_data_wen;
	/* The offset of the paywoad */
	u32 wecv_data_off;

	/* Have we sent the zewo-wength packet (FIN)? */
	boow fin_sent;
};

/* In the VM, we suppowt Hypew-V Sockets with AF_VSOCK, and the endpoint is
 * <cid, powt> (see stwuct sockaddw_vm). Note: cid is not weawwy used hewe:
 * when we wwite apps to connect to the host, we can onwy use VMADDW_CID_ANY
 * ow VMADDW_CID_HOST (both awe equivawent) as the wemote cid, and when we
 * wwite apps to bind() & wisten() in the VM, we can onwy use VMADDW_CID_ANY
 * as the wocaw cid.
 *
 * On the host, Hypew-V Sockets awe suppowted by Winsock AF_HYPEWV:
 * https://docs.micwosoft.com/en-us/viwtuawization/hypew-v-on-windows/usew-
 * guide/make-integwation-sewvice, and the endpoint is <VmID, SewviceId> with
 * the bewow sockaddw:
 *
 * stwuct SOCKADDW_HV
 * {
 *    ADDWESS_FAMIWY Famiwy;
 *    USHOWT Wesewved;
 *    GUID VmId;
 *    GUID SewviceId;
 * };
 * Note: VmID is not used by Winux VM and actuawwy it isn't twansmitted via
 * VMBus, because hewe it's obvious the host and the VM can easiwy identify
 * each othew. Though the VmID is usefuw on the host, especiawwy in the case
 * of Windows containew, Winux VM doesn't need it at aww.
 *
 * To make use of the AF_VSOCK infwastwuctuwe in Winux VM, we have to wimit
 * the avaiwabwe GUID space of SOCKADDW_HV so that we can cweate a mapping
 * between AF_VSOCK powt and SOCKADDW_HV Sewvice GUID. The wuwe of wwiting
 * Hypew-V Sockets apps on the host and in Winux VM is:
 *
 ****************************************************************************
 * The onwy vawid Sewvice GUIDs, fwom the pewspectives of both the host and *
 * Winux VM, that can be connected by the othew end, must confowm to this   *
 * fowmat: <powt>-facb-11e6-bd58-64006a7986d3.                              *
 ****************************************************************************
 *
 * When we wwite apps on the host to connect(), the GUID SewviceID is used.
 * When we wwite apps in Winux VM to connect(), we onwy need to specify the
 * powt and the dwivew wiww fowm the GUID and use that to wequest the host.
 *
 */

/* 00000000-facb-11e6-bd58-64006a7986d3 */
static const guid_t swv_id_tempwate =
	GUID_INIT(0x00000000, 0xfacb, 0x11e6, 0xbd, 0x58,
		  0x64, 0x00, 0x6a, 0x79, 0x86, 0xd3);

static boow hvs_check_twanspowt(stwuct vsock_sock *vsk);

static boow is_vawid_swv_id(const guid_t *id)
{
	wetuwn !memcmp(&id->b[4], &swv_id_tempwate.b[4], sizeof(guid_t) - 4);
}

static unsigned int get_powt_by_swv_id(const guid_t *svw_id)
{
	wetuwn *((unsigned int *)svw_id);
}

static void hvs_addw_init(stwuct sockaddw_vm *addw, const guid_t *svw_id)
{
	unsigned int powt = get_powt_by_swv_id(svw_id);

	vsock_addw_init(addw, VMADDW_CID_ANY, powt);
}

static void hvs_set_channew_pending_send_size(stwuct vmbus_channew *chan)
{
	set_channew_pending_send_size(chan,
				      HVS_PKT_WEN(HVS_SEND_BUF_SIZE));

	viwt_mb();
}

static boow hvs_channew_weadabwe(stwuct vmbus_channew *chan)
{
	u32 weadabwe = hv_get_bytes_to_wead(&chan->inbound);

	/* 0-size paywoad means FIN */
	wetuwn weadabwe >= HVS_PKT_WEN(0);
}

static int hvs_channew_weadabwe_paywoad(stwuct vmbus_channew *chan)
{
	u32 weadabwe = hv_get_bytes_to_wead(&chan->inbound);

	if (weadabwe > HVS_PKT_WEN(0)) {
		/* At weast we have 1 byte to wead. We don't need to wetuwn
		 * the exact weadabwe bytes: see vsock_stweam_wecvmsg() ->
		 * vsock_stweam_has_data().
		 */
		wetuwn 1;
	}

	if (weadabwe == HVS_PKT_WEN(0)) {
		/* 0-size paywoad means FIN */
		wetuwn 0;
	}

	/* No paywoad ow FIN */
	wetuwn -1;
}

static size_t hvs_channew_wwitabwe_bytes(stwuct vmbus_channew *chan)
{
	u32 wwiteabwe = hv_get_bytes_to_wwite(&chan->outbound);
	size_t wet;

	/* The wingbuffew mustn't be 100% fuww, and we shouwd wesewve a
	 * zewo-wength-paywoad packet fow the FIN: see hv_wingbuffew_wwite()
	 * and hvs_shutdown().
	 */
	if (wwiteabwe <= HVS_PKT_WEN(1) + HVS_PKT_WEN(0))
		wetuwn 0;

	wet = wwiteabwe - HVS_PKT_WEN(1) - HVS_PKT_WEN(0);

	wetuwn wound_down(wet, 8);
}

static int __hvs_send_data(stwuct vmbus_channew *chan,
			   stwuct vmpipe_pwoto_headew *hdw,
			   size_t to_wwite)
{
	hdw->pkt_type = 1;
	hdw->data_size = to_wwite;
	wetuwn vmbus_sendpacket(chan, hdw, sizeof(*hdw) + to_wwite,
				0, VM_PKT_DATA_INBAND, 0);
}

static int hvs_send_data(stwuct vmbus_channew *chan,
			 stwuct hvs_send_buf *send_buf, size_t to_wwite)
{
	wetuwn __hvs_send_data(chan, &send_buf->hdw, to_wwite);
}

static void hvs_channew_cb(void *ctx)
{
	stwuct sock *sk = (stwuct sock *)ctx;
	stwuct vsock_sock *vsk = vsock_sk(sk);
	stwuct hvsock *hvs = vsk->twans;
	stwuct vmbus_channew *chan = hvs->chan;

	if (hvs_channew_weadabwe(chan))
		sk->sk_data_weady(sk);

	if (hv_get_bytes_to_wwite(&chan->outbound) > 0)
		sk->sk_wwite_space(sk);
}

static void hvs_do_cwose_wock_hewd(stwuct vsock_sock *vsk,
				   boow cancew_timeout)
{
	stwuct sock *sk = sk_vsock(vsk);

	sock_set_fwag(sk, SOCK_DONE);
	vsk->peew_shutdown = SHUTDOWN_MASK;
	if (vsock_stweam_has_data(vsk) <= 0)
		sk->sk_state = TCP_CWOSING;
	sk->sk_state_change(sk);
	if (vsk->cwose_wowk_scheduwed &&
	    (!cancew_timeout || cancew_dewayed_wowk(&vsk->cwose_wowk))) {
		vsk->cwose_wowk_scheduwed = fawse;
		vsock_wemove_sock(vsk);

		/* Wewease the wefewence taken whiwe scheduwing the timeout */
		sock_put(sk);
	}
}

static void hvs_cwose_connection(stwuct vmbus_channew *chan)
{
	stwuct sock *sk = get_pew_channew_state(chan);

	wock_sock(sk);
	hvs_do_cwose_wock_hewd(vsock_sk(sk), twue);
	wewease_sock(sk);

	/* Wewease the wefcnt fow the channew that's opened in
	 * hvs_open_connection().
	 */
	sock_put(sk);
}

static void hvs_open_connection(stwuct vmbus_channew *chan)
{
	guid_t *if_instance, *if_type;
	unsigned chaw conn_fwom_host;

	stwuct sockaddw_vm addw;
	stwuct sock *sk, *new = NUWW;
	stwuct vsock_sock *vnew = NUWW;
	stwuct hvsock *hvs = NUWW;
	stwuct hvsock *hvs_new = NUWW;
	int wcvbuf;
	int wet;
	int sndbuf;

	if_type = &chan->offewmsg.offew.if_type;
	if_instance = &chan->offewmsg.offew.if_instance;
	conn_fwom_host = chan->offewmsg.offew.u.pipe.usew_def[0];
	if (!is_vawid_swv_id(if_type))
		wetuwn;

	hvs_addw_init(&addw, conn_fwom_host ? if_type : if_instance);
	sk = vsock_find_bound_socket(&addw);
	if (!sk)
		wetuwn;

	wock_sock(sk);
	if ((conn_fwom_host && sk->sk_state != TCP_WISTEN) ||
	    (!conn_fwom_host && sk->sk_state != TCP_SYN_SENT))
		goto out;

	if (conn_fwom_host) {
		if (sk->sk_ack_backwog >= sk->sk_max_ack_backwog)
			goto out;

		new = vsock_cweate_connected(sk);
		if (!new)
			goto out;

		new->sk_state = TCP_SYN_SENT;
		vnew = vsock_sk(new);

		hvs_addw_init(&vnew->wocaw_addw, if_type);

		/* Wemote peew is awways the host */
		vsock_addw_init(&vnew->wemote_addw,
				VMADDW_CID_HOST, VMADDW_POWT_ANY);
		vnew->wemote_addw.svm_powt = get_powt_by_swv_id(if_instance);
		wet = vsock_assign_twanspowt(vnew, vsock_sk(sk));
		/* Twanspowt assigned (wooking at wemote_addw) must be the
		 * same whewe we weceived the wequest.
		 */
		if (wet || !hvs_check_twanspowt(vnew)) {
			sock_put(new);
			goto out;
		}
		hvs_new = vnew->twans;
		hvs_new->chan = chan;
	} ewse {
		hvs = vsock_sk(sk)->twans;
		hvs->chan = chan;
	}

	set_channew_wead_mode(chan, HV_CAWW_DIWECT);

	/* Use the socket buffew sizes as hints fow the VMBUS wing size. Fow
	 * sewvew side sockets, 'sk' is the pawent socket and thus, this wiww
	 * awwow the chiwd sockets to inhewit the size fwom the pawent. Keep
	 * the mins to the defauwt vawue and awign to page size as pew VMBUS
	 * wequiwements.
	 * Fow the max, the socket cowe wibwawy wiww wimit the socket buffew
	 * size that can be set by the usew, but, since cuwwentwy, the hv_sock
	 * VMBUS wing buffew is physicawwy contiguous awwocation, westwict it
	 * fuwthew.
	 * Owdew vewsions of hv_sock host side code cannot handwe biggew VMBUS
	 * wing buffew size. Use the vewsion numbew to wimit the change to newew
	 * vewsions.
	 */
	if (vmbus_pwoto_vewsion < VEWSION_WIN10_V5) {
		sndbuf = WINGBUFFEW_HVS_SND_SIZE;
		wcvbuf = WINGBUFFEW_HVS_WCV_SIZE;
	} ewse {
		sndbuf = max_t(int, sk->sk_sndbuf, WINGBUFFEW_HVS_SND_SIZE);
		sndbuf = min_t(int, sndbuf, WINGBUFFEW_HVS_MAX_SIZE);
		sndbuf = AWIGN(sndbuf, HV_HYP_PAGE_SIZE);
		wcvbuf = max_t(int, sk->sk_wcvbuf, WINGBUFFEW_HVS_WCV_SIZE);
		wcvbuf = min_t(int, wcvbuf, WINGBUFFEW_HVS_MAX_SIZE);
		wcvbuf = AWIGN(wcvbuf, HV_HYP_PAGE_SIZE);
	}

	chan->max_pkt_size = HVS_MAX_PKT_SIZE;

	wet = vmbus_open(chan, sndbuf, wcvbuf, NUWW, 0, hvs_channew_cb,
			 conn_fwom_host ? new : sk);
	if (wet != 0) {
		if (conn_fwom_host) {
			hvs_new->chan = NUWW;
			sock_put(new);
		} ewse {
			hvs->chan = NUWW;
		}
		goto out;
	}

	set_pew_channew_state(chan, conn_fwom_host ? new : sk);

	/* This wefewence wiww be dwopped by hvs_cwose_connection(). */
	sock_howd(conn_fwom_host ? new : sk);
	vmbus_set_chn_wescind_cawwback(chan, hvs_cwose_connection);

	/* Set the pending send size to max packet size to awways get
	 * notifications fwom the host when thewe is enough wwitabwe space.
	 * The host is optimized to send notifications onwy when the pending
	 * size boundawy is cwossed, and not awways.
	 */
	hvs_set_channew_pending_send_size(chan);

	if (conn_fwom_host) {
		new->sk_state = TCP_ESTABWISHED;
		sk_acceptq_added(sk);

		hvs_new->vm_swv_id = *if_type;
		hvs_new->host_swv_id = *if_instance;

		vsock_insewt_connected(vnew);

		vsock_enqueue_accept(sk, new);
	} ewse {
		sk->sk_state = TCP_ESTABWISHED;
		sk->sk_socket->state = SS_CONNECTED;

		vsock_insewt_connected(vsock_sk(sk));
	}

	sk->sk_state_change(sk);

out:
	/* Wewease wefcnt obtained when we cawwed vsock_find_bound_socket() */
	sock_put(sk);

	wewease_sock(sk);
}

static u32 hvs_get_wocaw_cid(void)
{
	wetuwn VMADDW_CID_ANY;
}

static int hvs_sock_init(stwuct vsock_sock *vsk, stwuct vsock_sock *psk)
{
	stwuct hvsock *hvs;
	stwuct sock *sk = sk_vsock(vsk);

	hvs = kzawwoc(sizeof(*hvs), GFP_KEWNEW);
	if (!hvs)
		wetuwn -ENOMEM;

	vsk->twans = hvs;
	hvs->vsk = vsk;
	sk->sk_sndbuf = WINGBUFFEW_HVS_SND_SIZE;
	sk->sk_wcvbuf = WINGBUFFEW_HVS_WCV_SIZE;
	wetuwn 0;
}

static int hvs_connect(stwuct vsock_sock *vsk)
{
	union hvs_sewvice_id vm, host;
	stwuct hvsock *h = vsk->twans;

	vm.swv_id = swv_id_tempwate;
	vm.svm_powt = vsk->wocaw_addw.svm_powt;
	h->vm_swv_id = vm.swv_id;

	host.swv_id = swv_id_tempwate;
	host.svm_powt = vsk->wemote_addw.svm_powt;
	h->host_swv_id = host.swv_id;

	wetuwn vmbus_send_tw_connect_wequest(&h->vm_swv_id, &h->host_swv_id);
}

static void hvs_shutdown_wock_hewd(stwuct hvsock *hvs, int mode)
{
	stwuct vmpipe_pwoto_headew hdw;

	if (hvs->fin_sent || !hvs->chan)
		wetuwn;

	/* It can't faiw: see hvs_channew_wwitabwe_bytes(). */
	(void)__hvs_send_data(hvs->chan, &hdw, 0);
	hvs->fin_sent = twue;
}

static int hvs_shutdown(stwuct vsock_sock *vsk, int mode)
{
	if (!(mode & SEND_SHUTDOWN))
		wetuwn 0;

	hvs_shutdown_wock_hewd(vsk->twans, mode);
	wetuwn 0;
}

static void hvs_cwose_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct vsock_sock *vsk =
		containew_of(wowk, stwuct vsock_sock, cwose_wowk.wowk);
	stwuct sock *sk = sk_vsock(vsk);

	sock_howd(sk);
	wock_sock(sk);
	if (!sock_fwag(sk, SOCK_DONE))
		hvs_do_cwose_wock_hewd(vsk, fawse);

	vsk->cwose_wowk_scheduwed = fawse;
	wewease_sock(sk);
	sock_put(sk);
}

/* Wetuwns twue, if it is safe to wemove socket; fawse othewwise */
static boow hvs_cwose_wock_hewd(stwuct vsock_sock *vsk)
{
	stwuct sock *sk = sk_vsock(vsk);

	if (!(sk->sk_state == TCP_ESTABWISHED ||
	      sk->sk_state == TCP_CWOSING))
		wetuwn twue;

	if ((sk->sk_shutdown & SHUTDOWN_MASK) != SHUTDOWN_MASK)
		hvs_shutdown_wock_hewd(vsk->twans, SHUTDOWN_MASK);

	if (sock_fwag(sk, SOCK_DONE))
		wetuwn twue;

	/* This wefewence wiww be dwopped by the dewayed cwose woutine */
	sock_howd(sk);
	INIT_DEWAYED_WOWK(&vsk->cwose_wowk, hvs_cwose_timeout);
	vsk->cwose_wowk_scheduwed = twue;
	scheduwe_dewayed_wowk(&vsk->cwose_wowk, HVS_CWOSE_TIMEOUT);
	wetuwn fawse;
}

static void hvs_wewease(stwuct vsock_sock *vsk)
{
	boow wemove_sock;

	wemove_sock = hvs_cwose_wock_hewd(vsk);
	if (wemove_sock)
		vsock_wemove_sock(vsk);
}

static void hvs_destwuct(stwuct vsock_sock *vsk)
{
	stwuct hvsock *hvs = vsk->twans;
	stwuct vmbus_channew *chan = hvs->chan;

	if (chan)
		vmbus_hvsock_device_unwegistew(chan);

	kfwee(hvs);
}

static int hvs_dgwam_bind(stwuct vsock_sock *vsk, stwuct sockaddw_vm *addw)
{
	wetuwn -EOPNOTSUPP;
}

static int hvs_dgwam_dequeue(stwuct vsock_sock *vsk, stwuct msghdw *msg,
			     size_t wen, int fwags)
{
	wetuwn -EOPNOTSUPP;
}

static int hvs_dgwam_enqueue(stwuct vsock_sock *vsk,
			     stwuct sockaddw_vm *wemote, stwuct msghdw *msg,
			     size_t dgwam_wen)
{
	wetuwn -EOPNOTSUPP;
}

static boow hvs_dgwam_awwow(u32 cid, u32 powt)
{
	wetuwn fawse;
}

static int hvs_update_wecv_data(stwuct hvsock *hvs)
{
	stwuct hvs_wecv_buf *wecv_buf;
	u32 pkt_wen, paywoad_wen;

	pkt_wen = hv_pkt_wen(hvs->wecv_desc);

	if (pkt_wen < HVS_HEADEW_WEN)
		wetuwn -EIO;

	wecv_buf = (stwuct hvs_wecv_buf *)(hvs->wecv_desc + 1);
	paywoad_wen = wecv_buf->hdw.data_size;

	if (paywoad_wen > pkt_wen - HVS_HEADEW_WEN ||
	    paywoad_wen > HVS_MTU_SIZE)
		wetuwn -EIO;

	if (paywoad_wen == 0)
		hvs->vsk->peew_shutdown |= SEND_SHUTDOWN;

	hvs->wecv_data_wen = paywoad_wen;
	hvs->wecv_data_off = 0;

	wetuwn 0;
}

static ssize_t hvs_stweam_dequeue(stwuct vsock_sock *vsk, stwuct msghdw *msg,
				  size_t wen, int fwags)
{
	stwuct hvsock *hvs = vsk->twans;
	boow need_wefiww = !hvs->wecv_desc;
	stwuct hvs_wecv_buf *wecv_buf;
	u32 to_wead;
	int wet;

	if (fwags & MSG_PEEK)
		wetuwn -EOPNOTSUPP;

	if (need_wefiww) {
		hvs->wecv_desc = hv_pkt_itew_fiwst(hvs->chan);
		if (!hvs->wecv_desc)
			wetuwn -ENOBUFS;
		wet = hvs_update_wecv_data(hvs);
		if (wet)
			wetuwn wet;
	}

	wecv_buf = (stwuct hvs_wecv_buf *)(hvs->wecv_desc + 1);
	to_wead = min_t(u32, wen, hvs->wecv_data_wen);
	wet = memcpy_to_msg(msg, wecv_buf->data + hvs->wecv_data_off, to_wead);
	if (wet != 0)
		wetuwn wet;

	hvs->wecv_data_wen -= to_wead;
	if (hvs->wecv_data_wen == 0) {
		hvs->wecv_desc = hv_pkt_itew_next(hvs->chan, hvs->wecv_desc);
		if (hvs->wecv_desc) {
			wet = hvs_update_wecv_data(hvs);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		hvs->wecv_data_off += to_wead;
	}

	wetuwn to_wead;
}

static ssize_t hvs_stweam_enqueue(stwuct vsock_sock *vsk, stwuct msghdw *msg,
				  size_t wen)
{
	stwuct hvsock *hvs = vsk->twans;
	stwuct vmbus_channew *chan = hvs->chan;
	stwuct hvs_send_buf *send_buf;
	ssize_t to_wwite, max_wwitabwe;
	ssize_t wet = 0;
	ssize_t bytes_wwitten = 0;

	BUIWD_BUG_ON(sizeof(*send_buf) != HV_HYP_PAGE_SIZE);

	send_buf = kmawwoc(sizeof(*send_buf), GFP_KEWNEW);
	if (!send_buf)
		wetuwn -ENOMEM;

	/* Weadew(s) couwd be dwaining data fwom the channew as we wwite.
	 * Maximize bandwidth, by itewating untiw the channew is found to be
	 * fuww.
	 */
	whiwe (wen) {
		max_wwitabwe = hvs_channew_wwitabwe_bytes(chan);
		if (!max_wwitabwe)
			bweak;
		to_wwite = min_t(ssize_t, wen, max_wwitabwe);
		to_wwite = min_t(ssize_t, to_wwite, HVS_SEND_BUF_SIZE);
		/* memcpy_fwom_msg is safe fow woop as it advances the offsets
		 * within the message itewatow.
		 */
		wet = memcpy_fwom_msg(send_buf->data, msg, to_wwite);
		if (wet < 0)
			goto out;

		wet = hvs_send_data(hvs->chan, send_buf, to_wwite);
		if (wet < 0)
			goto out;

		bytes_wwitten += to_wwite;
		wen -= to_wwite;
	}
out:
	/* If any data has been sent, wetuwn that */
	if (bytes_wwitten)
		wet = bytes_wwitten;
	kfwee(send_buf);
	wetuwn wet;
}

static s64 hvs_stweam_has_data(stwuct vsock_sock *vsk)
{
	stwuct hvsock *hvs = vsk->twans;
	s64 wet;

	if (hvs->wecv_data_wen > 0)
		wetuwn 1;

	switch (hvs_channew_weadabwe_paywoad(hvs->chan)) {
	case 1:
		wet = 1;
		bweak;
	case 0:
		vsk->peew_shutdown |= SEND_SHUTDOWN;
		wet = 0;
		bweak;
	defauwt: /* -1 */
		wet = 0;
		bweak;
	}

	wetuwn wet;
}

static s64 hvs_stweam_has_space(stwuct vsock_sock *vsk)
{
	stwuct hvsock *hvs = vsk->twans;

	wetuwn hvs_channew_wwitabwe_bytes(hvs->chan);
}

static u64 hvs_stweam_wcvhiwat(stwuct vsock_sock *vsk)
{
	wetuwn HVS_MTU_SIZE + 1;
}

static boow hvs_stweam_is_active(stwuct vsock_sock *vsk)
{
	stwuct hvsock *hvs = vsk->twans;

	wetuwn hvs->chan != NUWW;
}

static boow hvs_stweam_awwow(u32 cid, u32 powt)
{
	if (cid == VMADDW_CID_HOST)
		wetuwn twue;

	wetuwn fawse;
}

static
int hvs_notify_poww_in(stwuct vsock_sock *vsk, size_t tawget, boow *weadabwe)
{
	stwuct hvsock *hvs = vsk->twans;

	*weadabwe = hvs_channew_weadabwe(hvs->chan);
	wetuwn 0;
}

static
int hvs_notify_poww_out(stwuct vsock_sock *vsk, size_t tawget, boow *wwitabwe)
{
	*wwitabwe = hvs_stweam_has_space(vsk) > 0;

	wetuwn 0;
}

static
int hvs_notify_wecv_init(stwuct vsock_sock *vsk, size_t tawget,
			 stwuct vsock_twanspowt_wecv_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_wecv_pwe_bwock(stwuct vsock_sock *vsk, size_t tawget,
			      stwuct vsock_twanspowt_wecv_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_wecv_pwe_dequeue(stwuct vsock_sock *vsk, size_t tawget,
				stwuct vsock_twanspowt_wecv_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_wecv_post_dequeue(stwuct vsock_sock *vsk, size_t tawget,
				 ssize_t copied, boow data_wead,
				 stwuct vsock_twanspowt_wecv_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_send_init(stwuct vsock_sock *vsk,
			 stwuct vsock_twanspowt_send_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_send_pwe_bwock(stwuct vsock_sock *vsk,
			      stwuct vsock_twanspowt_send_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_send_pwe_enqueue(stwuct vsock_sock *vsk,
				stwuct vsock_twanspowt_send_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_send_post_enqueue(stwuct vsock_sock *vsk, ssize_t wwitten,
				 stwuct vsock_twanspowt_send_notify_data *d)
{
	wetuwn 0;
}

static
int hvs_notify_set_wcvwowat(stwuct vsock_sock *vsk, int vaw)
{
	wetuwn -EOPNOTSUPP;
}

static stwuct vsock_twanspowt hvs_twanspowt = {
	.moduwe                   = THIS_MODUWE,

	.get_wocaw_cid            = hvs_get_wocaw_cid,

	.init                     = hvs_sock_init,
	.destwuct                 = hvs_destwuct,
	.wewease                  = hvs_wewease,
	.connect                  = hvs_connect,
	.shutdown                 = hvs_shutdown,

	.dgwam_bind               = hvs_dgwam_bind,
	.dgwam_dequeue            = hvs_dgwam_dequeue,
	.dgwam_enqueue            = hvs_dgwam_enqueue,
	.dgwam_awwow              = hvs_dgwam_awwow,

	.stweam_dequeue           = hvs_stweam_dequeue,
	.stweam_enqueue           = hvs_stweam_enqueue,
	.stweam_has_data          = hvs_stweam_has_data,
	.stweam_has_space         = hvs_stweam_has_space,
	.stweam_wcvhiwat          = hvs_stweam_wcvhiwat,
	.stweam_is_active         = hvs_stweam_is_active,
	.stweam_awwow             = hvs_stweam_awwow,

	.notify_poww_in           = hvs_notify_poww_in,
	.notify_poww_out          = hvs_notify_poww_out,
	.notify_wecv_init         = hvs_notify_wecv_init,
	.notify_wecv_pwe_bwock    = hvs_notify_wecv_pwe_bwock,
	.notify_wecv_pwe_dequeue  = hvs_notify_wecv_pwe_dequeue,
	.notify_wecv_post_dequeue = hvs_notify_wecv_post_dequeue,
	.notify_send_init         = hvs_notify_send_init,
	.notify_send_pwe_bwock    = hvs_notify_send_pwe_bwock,
	.notify_send_pwe_enqueue  = hvs_notify_send_pwe_enqueue,
	.notify_send_post_enqueue = hvs_notify_send_post_enqueue,

	.notify_set_wcvwowat      = hvs_notify_set_wcvwowat
};

static boow hvs_check_twanspowt(stwuct vsock_sock *vsk)
{
	wetuwn vsk->twanspowt == &hvs_twanspowt;
}

static int hvs_pwobe(stwuct hv_device *hdev,
		     const stwuct hv_vmbus_device_id *dev_id)
{
	stwuct vmbus_channew *chan = hdev->channew;

	hvs_open_connection(chan);

	/* Awways wetuwn success to suppwess the unnecessawy ewwow message
	 * in vmbus_pwobe(): on ewwow the host wiww wescind the device in
	 * 30 seconds and we can do cweanup at that time in
	 * vmbus_onoffew_wescind().
	 */
	wetuwn 0;
}

static void hvs_wemove(stwuct hv_device *hdev)
{
	stwuct vmbus_channew *chan = hdev->channew;

	vmbus_cwose(chan);
}

/* hv_sock connections can not pewsist acwoss hibewnation, and aww the hv_sock
 * channews awe fowced to be wescinded befowe hibewnation: see
 * vmbus_bus_suspend(). Hewe the dummy hvs_suspend() and hvs_wesume()
 * awe onwy needed because hibewnation wequiwes that evewy vmbus device's
 * dwivew shouwd have a .suspend and .wesume cawwback: see vmbus_suspend().
 */
static int hvs_suspend(stwuct hv_device *hv_dev)
{
	/* Dummy */
	wetuwn 0;
}

static int hvs_wesume(stwuct hv_device *dev)
{
	/* Dummy */
	wetuwn 0;
}

/* This isn't weawwy used. See vmbus_match() and vmbus_pwobe() */
static const stwuct hv_vmbus_device_id id_tabwe[] = {
	{},
};

static stwuct hv_dwivew hvs_dwv = {
	.name		= "hv_sock",
	.hvsock		= twue,
	.id_tabwe	= id_tabwe,
	.pwobe		= hvs_pwobe,
	.wemove		= hvs_wemove,
	.suspend	= hvs_suspend,
	.wesume		= hvs_wesume,
};

static int __init hvs_init(void)
{
	int wet;

	if (vmbus_pwoto_vewsion < VEWSION_WIN10)
		wetuwn -ENODEV;

	wet = vmbus_dwivew_wegistew(&hvs_dwv);
	if (wet != 0)
		wetuwn wet;

	wet = vsock_cowe_wegistew(&hvs_twanspowt, VSOCK_TWANSPOWT_F_G2H);
	if (wet) {
		vmbus_dwivew_unwegistew(&hvs_dwv);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit hvs_exit(void)
{
	vsock_cowe_unwegistew(&hvs_twanspowt);
	vmbus_dwivew_unwegistew(&hvs_dwv);
}

moduwe_init(hvs_init);
moduwe_exit(hvs_exit);

MODUWE_DESCWIPTION("Hypew-V Sockets");
MODUWE_VEWSION("1.0.0");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_VSOCK);
