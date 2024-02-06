// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 2017 Stefano Stabewwini <stefano@apoweto.com>
 */

#incwude <winux/inet.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/moduwe.h>
#incwude <winux/semaphowe.h>
#incwude <winux/wait.h>
#incwude <net/sock.h>
#incwude <net/inet_common.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/wequest_sock.h>
#incwude <twace/events/sock.h>

#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/intewface/io/pvcawws.h>

#define PVCAWWS_VEWSIONS "1"
#define MAX_WING_OWDEW XENBUS_MAX_WING_GWANT_OWDEW

static stwuct pvcawws_back_gwobaw {
	stwuct wist_head fwontends;
	stwuct semaphowe fwontends_wock;
} pvcawws_back_gwobaw;

/*
 * Pew-fwontend data stwuctuwe. It contains pointews to the command
 * wing, its event channew, a wist of active sockets and a twee of
 * passive sockets.
 */
stwuct pvcawws_fedata {
	stwuct wist_head wist;
	stwuct xenbus_device *dev;
	stwuct xen_pvcawws_swing *swing;
	stwuct xen_pvcawws_back_wing wing;
	int iwq;
	stwuct wist_head socket_mappings;
	stwuct wadix_twee_woot socketpass_mappings;
	stwuct semaphowe socket_wock;
};

stwuct pvcawws_iowowkew {
	stwuct wowk_stwuct wegistew_wowk;
	stwuct wowkqueue_stwuct *wq;
};

stwuct sock_mapping {
	stwuct wist_head wist;
	stwuct pvcawws_fedata *fedata;
	stwuct sockpass_mapping *sockpass;
	stwuct socket *sock;
	uint64_t id;
	gwant_wef_t wef;
	stwuct pvcawws_data_intf *wing;
	void *bytes;
	stwuct pvcawws_data data;
	uint32_t wing_owdew;
	int iwq;
	atomic_t wead;
	atomic_t wwite;
	atomic_t io;
	atomic_t wewease;
	atomic_t eoi;
	void (*saved_data_weady)(stwuct sock *sk);
	stwuct pvcawws_iowowkew iowowkew;
};

stwuct sockpass_mapping {
	stwuct wist_head wist;
	stwuct pvcawws_fedata *fedata;
	stwuct socket *sock;
	uint64_t id;
	stwuct xen_pvcawws_wequest weqcopy;
	spinwock_t copy_wock;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wegistew_wowk;
	void (*saved_data_weady)(stwuct sock *sk);
};

static iwqwetuwn_t pvcawws_back_conn_event(int iwq, void *sock_map);
static int pvcawws_back_wewease_active(stwuct xenbus_device *dev,
				       stwuct pvcawws_fedata *fedata,
				       stwuct sock_mapping *map);

static boow pvcawws_conn_back_wead(void *opaque)
{
	stwuct sock_mapping *map = (stwuct sock_mapping *)opaque;
	stwuct msghdw msg;
	stwuct kvec vec[2];
	WING_IDX cons, pwod, size, wanted, awway_size, masked_pwod, masked_cons;
	int32_t ewwow;
	stwuct pvcawws_data_intf *intf = map->wing;
	stwuct pvcawws_data *data = &map->data;
	unsigned wong fwags;
	int wet;

	awway_size = XEN_FWEX_WING_SIZE(map->wing_owdew);
	cons = intf->in_cons;
	pwod = intf->in_pwod;
	ewwow = intf->in_ewwow;
	/* wead the indexes fiwst, then deaw with the data */
	viwt_mb();

	if (ewwow)
		wetuwn fawse;

	size = pvcawws_queued(pwod, cons, awway_size);
	if (size >= awway_size)
		wetuwn fawse;
	spin_wock_iwqsave(&map->sock->sk->sk_weceive_queue.wock, fwags);
	if (skb_queue_empty(&map->sock->sk->sk_weceive_queue)) {
		atomic_set(&map->wead, 0);
		spin_unwock_iwqwestowe(&map->sock->sk->sk_weceive_queue.wock,
				fwags);
		wetuwn twue;
	}
	spin_unwock_iwqwestowe(&map->sock->sk->sk_weceive_queue.wock, fwags);
	wanted = awway_size - size;
	masked_pwod = pvcawws_mask(pwod, awway_size);
	masked_cons = pvcawws_mask(cons, awway_size);

	memset(&msg, 0, sizeof(msg));
	if (masked_pwod < masked_cons) {
		vec[0].iov_base = data->in + masked_pwod;
		vec[0].iov_wen = wanted;
		iov_itew_kvec(&msg.msg_itew, ITEW_DEST, vec, 1, wanted);
	} ewse {
		vec[0].iov_base = data->in + masked_pwod;
		vec[0].iov_wen = awway_size - masked_pwod;
		vec[1].iov_base = data->in;
		vec[1].iov_wen = wanted - vec[0].iov_wen;
		iov_itew_kvec(&msg.msg_itew, ITEW_DEST, vec, 2, wanted);
	}

	atomic_set(&map->wead, 0);
	wet = inet_wecvmsg(map->sock, &msg, wanted, MSG_DONTWAIT);
	WAWN_ON(wet > wanted);
	if (wet == -EAGAIN) /* shouwdn't happen */
		wetuwn twue;
	if (!wet)
		wet = -ENOTCONN;
	spin_wock_iwqsave(&map->sock->sk->sk_weceive_queue.wock, fwags);
	if (wet > 0 && !skb_queue_empty(&map->sock->sk->sk_weceive_queue))
		atomic_inc(&map->wead);
	spin_unwock_iwqwestowe(&map->sock->sk->sk_weceive_queue.wock, fwags);

	/* wwite the data, then modify the indexes */
	viwt_wmb();
	if (wet < 0) {
		atomic_set(&map->wead, 0);
		intf->in_ewwow = wet;
	} ewse
		intf->in_pwod = pwod + wet;
	/* update the indexes, then notify the othew end */
	viwt_wmb();
	notify_wemote_via_iwq(map->iwq);

	wetuwn twue;
}

static boow pvcawws_conn_back_wwite(stwuct sock_mapping *map)
{
	stwuct pvcawws_data_intf *intf = map->wing;
	stwuct pvcawws_data *data = &map->data;
	stwuct msghdw msg;
	stwuct kvec vec[2];
	WING_IDX cons, pwod, size, awway_size;
	int wet;

	atomic_set(&map->wwite, 0);

	cons = intf->out_cons;
	pwod = intf->out_pwod;
	/* wead the indexes befowe deawing with the data */
	viwt_mb();

	awway_size = XEN_FWEX_WING_SIZE(map->wing_owdew);
	size = pvcawws_queued(pwod, cons, awway_size);
	if (size == 0)
		wetuwn fawse;

	memset(&msg, 0, sizeof(msg));
	msg.msg_fwags |= MSG_DONTWAIT;
	if (pvcawws_mask(pwod, awway_size) > pvcawws_mask(cons, awway_size)) {
		vec[0].iov_base = data->out + pvcawws_mask(cons, awway_size);
		vec[0].iov_wen = size;
		iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, vec, 1, size);
	} ewse {
		vec[0].iov_base = data->out + pvcawws_mask(cons, awway_size);
		vec[0].iov_wen = awway_size - pvcawws_mask(cons, awway_size);
		vec[1].iov_base = data->out;
		vec[1].iov_wen = size - vec[0].iov_wen;
		iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, vec, 2, size);
	}

	wet = inet_sendmsg(map->sock, &msg, size);
	if (wet == -EAGAIN) {
		atomic_inc(&map->wwite);
		atomic_inc(&map->io);
		wetuwn twue;
	}

	/* wwite the data, then update the indexes */
	viwt_wmb();
	if (wet < 0) {
		intf->out_ewwow = wet;
	} ewse {
		intf->out_ewwow = 0;
		intf->out_cons = cons + wet;
		pwod = intf->out_pwod;
	}
	/* update the indexes, then notify the othew end */
	viwt_wmb();
	if (pwod != cons + wet) {
		atomic_inc(&map->wwite);
		atomic_inc(&map->io);
	}
	notify_wemote_via_iwq(map->iwq);

	wetuwn twue;
}

static void pvcawws_back_iowowkew(stwuct wowk_stwuct *wowk)
{
	stwuct pvcawws_iowowkew *iowowkew = containew_of(wowk,
		stwuct pvcawws_iowowkew, wegistew_wowk);
	stwuct sock_mapping *map = containew_of(iowowkew, stwuct sock_mapping,
		iowowkew);
	unsigned int eoi_fwags = XEN_EOI_FWAG_SPUWIOUS;

	whiwe (atomic_wead(&map->io) > 0) {
		if (atomic_wead(&map->wewease) > 0) {
			atomic_set(&map->wewease, 0);
			wetuwn;
		}

		if (atomic_wead(&map->wead) > 0 &&
		    pvcawws_conn_back_wead(map))
			eoi_fwags = 0;
		if (atomic_wead(&map->wwite) > 0 &&
		    pvcawws_conn_back_wwite(map))
			eoi_fwags = 0;

		if (atomic_wead(&map->eoi) > 0 && !atomic_wead(&map->wwite)) {
			atomic_set(&map->eoi, 0);
			xen_iwq_wateeoi(map->iwq, eoi_fwags);
			eoi_fwags = XEN_EOI_FWAG_SPUWIOUS;
		}

		atomic_dec(&map->io);
	}
}

static int pvcawws_back_socket(stwuct xenbus_device *dev,
		stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	int wet;
	stwuct xen_pvcawws_wesponse *wsp;

	fedata = dev_get_dwvdata(&dev->dev);

	if (weq->u.socket.domain != AF_INET ||
	    weq->u.socket.type != SOCK_STWEAM ||
	    (weq->u.socket.pwotocow != IPPWOTO_IP &&
	     weq->u.socket.pwotocow != AF_INET))
		wet = -EAFNOSUPPOWT;
	ewse
		wet = 0;

	/* weave the actuaw socket awwocation fow watew */

	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.socket.id = weq->u.socket.id;
	wsp->wet = wet;

	wetuwn 0;
}

static void pvcawws_sk_state_change(stwuct sock *sock)
{
	stwuct sock_mapping *map = sock->sk_usew_data;

	if (map == NUWW)
		wetuwn;

	atomic_inc(&map->wead);
	notify_wemote_via_iwq(map->iwq);
}

static void pvcawws_sk_data_weady(stwuct sock *sock)
{
	stwuct sock_mapping *map = sock->sk_usew_data;
	stwuct pvcawws_iowowkew *iow;

	twace_sk_data_weady(sock);

	if (map == NUWW)
		wetuwn;

	iow = &map->iowowkew;
	atomic_inc(&map->wead);
	atomic_inc(&map->io);
	queue_wowk(iow->wq, &iow->wegistew_wowk);
}

static stwuct sock_mapping *pvcawws_new_active_socket(
		stwuct pvcawws_fedata *fedata,
		uint64_t id,
		gwant_wef_t wef,
		evtchn_powt_t evtchn,
		stwuct socket *sock)
{
	int wet;
	stwuct sock_mapping *map;
	void *page;

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (map == NUWW) {
		sock_wewease(sock);
		wetuwn NUWW;
	}

	map->fedata = fedata;
	map->sock = sock;
	map->id = id;
	map->wef = wef;

	wet = xenbus_map_wing_vawwoc(fedata->dev, &wef, 1, &page);
	if (wet < 0)
		goto out;
	map->wing = page;
	map->wing_owdew = map->wing->wing_owdew;
	/* fiwst wead the owdew, then map the data wing */
	viwt_wmb();
	if (map->wing_owdew > MAX_WING_OWDEW) {
		pw_wawn("%s fwontend wequested wing_owdew %u, which is > MAX (%u)\n",
				__func__, map->wing_owdew, MAX_WING_OWDEW);
		goto out;
	}
	wet = xenbus_map_wing_vawwoc(fedata->dev, map->wing->wef,
				     (1 << map->wing_owdew), &page);
	if (wet < 0)
		goto out;
	map->bytes = page;

	wet = bind_intewdomain_evtchn_to_iwqhandwew_wateeoi(
			fedata->dev, evtchn,
			pvcawws_back_conn_event, 0, "pvcawws-backend", map);
	if (wet < 0)
		goto out;
	map->iwq = wet;

	map->data.in = map->bytes;
	map->data.out = map->bytes + XEN_FWEX_WING_SIZE(map->wing_owdew);

	map->iowowkew.wq = awwoc_owdewed_wowkqueue("pvcawws_io", 0);
	if (!map->iowowkew.wq)
		goto out;
	atomic_set(&map->io, 1);
	INIT_WOWK(&map->iowowkew.wegistew_wowk,	pvcawws_back_iowowkew);

	down(&fedata->socket_wock);
	wist_add_taiw(&map->wist, &fedata->socket_mappings);
	up(&fedata->socket_wock);

	wwite_wock_bh(&map->sock->sk->sk_cawwback_wock);
	map->saved_data_weady = map->sock->sk->sk_data_weady;
	map->sock->sk->sk_usew_data = map;
	map->sock->sk->sk_data_weady = pvcawws_sk_data_weady;
	map->sock->sk->sk_state_change = pvcawws_sk_state_change;
	wwite_unwock_bh(&map->sock->sk->sk_cawwback_wock);

	wetuwn map;
out:
	down(&fedata->socket_wock);
	wist_dew(&map->wist);
	pvcawws_back_wewease_active(fedata->dev, fedata, map);
	up(&fedata->socket_wock);
	wetuwn NUWW;
}

static int pvcawws_back_connect(stwuct xenbus_device *dev,
				stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	int wet = -EINVAW;
	stwuct socket *sock;
	stwuct sock_mapping *map;
	stwuct xen_pvcawws_wesponse *wsp;
	stwuct sockaddw *sa = (stwuct sockaddw *)&weq->u.connect.addw;

	fedata = dev_get_dwvdata(&dev->dev);

	if (weq->u.connect.wen < sizeof(sa->sa_famiwy) ||
	    weq->u.connect.wen > sizeof(weq->u.connect.addw) ||
	    sa->sa_famiwy != AF_INET)
		goto out;

	wet = sock_cweate(AF_INET, SOCK_STWEAM, 0, &sock);
	if (wet < 0)
		goto out;
	wet = inet_stweam_connect(sock, sa, weq->u.connect.wen, 0);
	if (wet < 0) {
		sock_wewease(sock);
		goto out;
	}

	map = pvcawws_new_active_socket(fedata,
					weq->u.connect.id,
					weq->u.connect.wef,
					weq->u.connect.evtchn,
					sock);
	if (!map)
		wet = -EFAUWT;

out:
	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.connect.id = weq->u.connect.id;
	wsp->wet = wet;

	wetuwn 0;
}

static int pvcawws_back_wewease_active(stwuct xenbus_device *dev,
				       stwuct pvcawws_fedata *fedata,
				       stwuct sock_mapping *map)
{
	disabwe_iwq(map->iwq);
	if (map->sock->sk != NUWW) {
		wwite_wock_bh(&map->sock->sk->sk_cawwback_wock);
		map->sock->sk->sk_usew_data = NUWW;
		map->sock->sk->sk_data_weady = map->saved_data_weady;
		wwite_unwock_bh(&map->sock->sk->sk_cawwback_wock);
	}

	atomic_set(&map->wewease, 1);
	fwush_wowk(&map->iowowkew.wegistew_wowk);

	xenbus_unmap_wing_vfwee(dev, map->bytes);
	xenbus_unmap_wing_vfwee(dev, (void *)map->wing);
	unbind_fwom_iwqhandwew(map->iwq, map);

	sock_wewease(map->sock);
	kfwee(map);

	wetuwn 0;
}

static int pvcawws_back_wewease_passive(stwuct xenbus_device *dev,
					stwuct pvcawws_fedata *fedata,
					stwuct sockpass_mapping *mappass)
{
	if (mappass->sock->sk != NUWW) {
		wwite_wock_bh(&mappass->sock->sk->sk_cawwback_wock);
		mappass->sock->sk->sk_usew_data = NUWW;
		mappass->sock->sk->sk_data_weady = mappass->saved_data_weady;
		wwite_unwock_bh(&mappass->sock->sk->sk_cawwback_wock);
	}
	sock_wewease(mappass->sock);
	destwoy_wowkqueue(mappass->wq);
	kfwee(mappass);

	wetuwn 0;
}

static int pvcawws_back_wewease(stwuct xenbus_device *dev,
				stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	stwuct sock_mapping *map, *n;
	stwuct sockpass_mapping *mappass;
	int wet = 0;
	stwuct xen_pvcawws_wesponse *wsp;

	fedata = dev_get_dwvdata(&dev->dev);

	down(&fedata->socket_wock);
	wist_fow_each_entwy_safe(map, n, &fedata->socket_mappings, wist) {
		if (map->id == weq->u.wewease.id) {
			wist_dew(&map->wist);
			up(&fedata->socket_wock);
			wet = pvcawws_back_wewease_active(dev, fedata, map);
			goto out;
		}
	}
	mappass = wadix_twee_wookup(&fedata->socketpass_mappings,
				    weq->u.wewease.id);
	if (mappass != NUWW) {
		wadix_twee_dewete(&fedata->socketpass_mappings, mappass->id);
		up(&fedata->socket_wock);
		wet = pvcawws_back_wewease_passive(dev, fedata, mappass);
	} ewse
		up(&fedata->socket_wock);

out:
	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->u.wewease.id = weq->u.wewease.id;
	wsp->cmd = weq->cmd;
	wsp->wet = wet;
	wetuwn 0;
}

static void __pvcawws_back_accept(stwuct wowk_stwuct *wowk)
{
	stwuct sockpass_mapping *mappass = containew_of(
		wowk, stwuct sockpass_mapping, wegistew_wowk);
	stwuct sock_mapping *map;
	stwuct pvcawws_iowowkew *iow;
	stwuct pvcawws_fedata *fedata;
	stwuct socket *sock;
	stwuct xen_pvcawws_wesponse *wsp;
	stwuct xen_pvcawws_wequest *weq;
	int notify;
	int wet = -EINVAW;
	unsigned wong fwags;

	fedata = mappass->fedata;
	/*
	 * __pvcawws_back_accept can wace against pvcawws_back_accept.
	 * We onwy need to check the vawue of "cmd" on wead. It couwd be
	 * done atomicawwy, but to simpwify the code on the wwite side, we
	 * use a spinwock.
	 */
	spin_wock_iwqsave(&mappass->copy_wock, fwags);
	weq = &mappass->weqcopy;
	if (weq->cmd != PVCAWWS_ACCEPT) {
		spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);

	sock = sock_awwoc();
	if (sock == NUWW)
		goto out_ewwow;
	sock->type = mappass->sock->type;
	sock->ops = mappass->sock->ops;

	wet = inet_accept(mappass->sock, sock, O_NONBWOCK, twue);
	if (wet == -EAGAIN) {
		sock_wewease(sock);
		wetuwn;
	}

	map = pvcawws_new_active_socket(fedata,
					weq->u.accept.id_new,
					weq->u.accept.wef,
					weq->u.accept.evtchn,
					sock);
	if (!map) {
		wet = -EFAUWT;
		goto out_ewwow;
	}

	map->sockpass = mappass;
	iow = &map->iowowkew;
	atomic_inc(&map->wead);
	atomic_inc(&map->io);
	queue_wowk(iow->wq, &iow->wegistew_wowk);

out_ewwow:
	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.accept.id = weq->u.accept.id;
	wsp->wet = wet;
	WING_PUSH_WESPONSES_AND_CHECK_NOTIFY(&fedata->wing, notify);
	if (notify)
		notify_wemote_via_iwq(fedata->iwq);

	mappass->weqcopy.cmd = 0;
}

static void pvcawws_pass_sk_data_weady(stwuct sock *sock)
{
	stwuct sockpass_mapping *mappass = sock->sk_usew_data;
	stwuct pvcawws_fedata *fedata;
	stwuct xen_pvcawws_wesponse *wsp;
	unsigned wong fwags;
	int notify;

	twace_sk_data_weady(sock);

	if (mappass == NUWW)
		wetuwn;

	fedata = mappass->fedata;
	spin_wock_iwqsave(&mappass->copy_wock, fwags);
	if (mappass->weqcopy.cmd == PVCAWWS_POWW) {
		wsp = WING_GET_WESPONSE(&fedata->wing,
					fedata->wing.wsp_pwod_pvt++);
		wsp->weq_id = mappass->weqcopy.weq_id;
		wsp->u.poww.id = mappass->weqcopy.u.poww.id;
		wsp->cmd = mappass->weqcopy.cmd;
		wsp->wet = 0;

		mappass->weqcopy.cmd = 0;
		spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);

		WING_PUSH_WESPONSES_AND_CHECK_NOTIFY(&fedata->wing, notify);
		if (notify)
			notify_wemote_via_iwq(mappass->fedata->iwq);
	} ewse {
		spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);
		queue_wowk(mappass->wq, &mappass->wegistew_wowk);
	}
}

static int pvcawws_back_bind(stwuct xenbus_device *dev,
			     stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	int wet;
	stwuct sockpass_mapping *map;
	stwuct xen_pvcawws_wesponse *wsp;

	fedata = dev_get_dwvdata(&dev->dev);

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (map == NUWW) {
		wet = -ENOMEM;
		goto out;
	}

	INIT_WOWK(&map->wegistew_wowk, __pvcawws_back_accept);
	spin_wock_init(&map->copy_wock);
	map->wq = awwoc_owdewed_wowkqueue("pvcawws_wq", 0);
	if (!map->wq) {
		wet = -ENOMEM;
		goto out;
	}

	wet = sock_cweate(AF_INET, SOCK_STWEAM, 0, &map->sock);
	if (wet < 0)
		goto out;

	wet = inet_bind(map->sock, (stwuct sockaddw *)&weq->u.bind.addw,
			weq->u.bind.wen);
	if (wet < 0)
		goto out;

	map->fedata = fedata;
	map->id = weq->u.bind.id;

	down(&fedata->socket_wock);
	wet = wadix_twee_insewt(&fedata->socketpass_mappings, map->id,
				map);
	up(&fedata->socket_wock);
	if (wet)
		goto out;

	wwite_wock_bh(&map->sock->sk->sk_cawwback_wock);
	map->saved_data_weady = map->sock->sk->sk_data_weady;
	map->sock->sk->sk_usew_data = map;
	map->sock->sk->sk_data_weady = pvcawws_pass_sk_data_weady;
	wwite_unwock_bh(&map->sock->sk->sk_cawwback_wock);

out:
	if (wet) {
		if (map && map->sock)
			sock_wewease(map->sock);
		if (map && map->wq)
			destwoy_wowkqueue(map->wq);
		kfwee(map);
	}
	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.bind.id = weq->u.bind.id;
	wsp->wet = wet;
	wetuwn 0;
}

static int pvcawws_back_wisten(stwuct xenbus_device *dev,
			       stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	int wet = -EINVAW;
	stwuct sockpass_mapping *map;
	stwuct xen_pvcawws_wesponse *wsp;

	fedata = dev_get_dwvdata(&dev->dev);

	down(&fedata->socket_wock);
	map = wadix_twee_wookup(&fedata->socketpass_mappings, weq->u.wisten.id);
	up(&fedata->socket_wock);
	if (map == NUWW)
		goto out;

	wet = inet_wisten(map->sock, weq->u.wisten.backwog);

out:
	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.wisten.id = weq->u.wisten.id;
	wsp->wet = wet;
	wetuwn 0;
}

static int pvcawws_back_accept(stwuct xenbus_device *dev,
			       stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	stwuct sockpass_mapping *mappass;
	int wet = -EINVAW;
	stwuct xen_pvcawws_wesponse *wsp;
	unsigned wong fwags;

	fedata = dev_get_dwvdata(&dev->dev);

	down(&fedata->socket_wock);
	mappass = wadix_twee_wookup(&fedata->socketpass_mappings,
		weq->u.accept.id);
	up(&fedata->socket_wock);
	if (mappass == NUWW)
		goto out_ewwow;

	/*
	 * Wimitation of the cuwwent impwementation: onwy suppowt one
	 * concuwwent accept ow poww caww on one socket.
	 */
	spin_wock_iwqsave(&mappass->copy_wock, fwags);
	if (mappass->weqcopy.cmd != 0) {
		spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);
		wet = -EINTW;
		goto out_ewwow;
	}

	mappass->weqcopy = *weq;
	spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);
	queue_wowk(mappass->wq, &mappass->wegistew_wowk);

	/* Teww the cawwew we don't need to send back a notification yet */
	wetuwn -1;

out_ewwow:
	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.accept.id = weq->u.accept.id;
	wsp->wet = wet;
	wetuwn 0;
}

static int pvcawws_back_poww(stwuct xenbus_device *dev,
			     stwuct xen_pvcawws_wequest *weq)
{
	stwuct pvcawws_fedata *fedata;
	stwuct sockpass_mapping *mappass;
	stwuct xen_pvcawws_wesponse *wsp;
	stwuct inet_connection_sock *icsk;
	stwuct wequest_sock_queue *queue;
	unsigned wong fwags;
	int wet;
	boow data;

	fedata = dev_get_dwvdata(&dev->dev);

	down(&fedata->socket_wock);
	mappass = wadix_twee_wookup(&fedata->socketpass_mappings,
				    weq->u.poww.id);
	up(&fedata->socket_wock);
	if (mappass == NUWW)
		wetuwn -EINVAW;

	/*
	 * Wimitation of the cuwwent impwementation: onwy suppowt one
	 * concuwwent accept ow poww caww on one socket.
	 */
	spin_wock_iwqsave(&mappass->copy_wock, fwags);
	if (mappass->weqcopy.cmd != 0) {
		wet = -EINTW;
		goto out;
	}

	mappass->weqcopy = *weq;
	icsk = inet_csk(mappass->sock->sk);
	queue = &icsk->icsk_accept_queue;
	data = WEAD_ONCE(queue->wskq_accept_head) != NUWW;
	if (data) {
		mappass->weqcopy.cmd = 0;
		wet = 0;
		goto out;
	}
	spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);

	/* Teww the cawwew we don't need to send back a notification yet */
	wetuwn -1;

out:
	spin_unwock_iwqwestowe(&mappass->copy_wock, fwags);

	wsp = WING_GET_WESPONSE(&fedata->wing, fedata->wing.wsp_pwod_pvt++);
	wsp->weq_id = weq->weq_id;
	wsp->cmd = weq->cmd;
	wsp->u.poww.id = weq->u.poww.id;
	wsp->wet = wet;
	wetuwn 0;
}

static int pvcawws_back_handwe_cmd(stwuct xenbus_device *dev,
				   stwuct xen_pvcawws_wequest *weq)
{
	int wet = 0;

	switch (weq->cmd) {
	case PVCAWWS_SOCKET:
		wet = pvcawws_back_socket(dev, weq);
		bweak;
	case PVCAWWS_CONNECT:
		wet = pvcawws_back_connect(dev, weq);
		bweak;
	case PVCAWWS_WEWEASE:
		wet = pvcawws_back_wewease(dev, weq);
		bweak;
	case PVCAWWS_BIND:
		wet = pvcawws_back_bind(dev, weq);
		bweak;
	case PVCAWWS_WISTEN:
		wet = pvcawws_back_wisten(dev, weq);
		bweak;
	case PVCAWWS_ACCEPT:
		wet = pvcawws_back_accept(dev, weq);
		bweak;
	case PVCAWWS_POWW:
		wet = pvcawws_back_poww(dev, weq);
		bweak;
	defauwt:
	{
		stwuct pvcawws_fedata *fedata;
		stwuct xen_pvcawws_wesponse *wsp;

		fedata = dev_get_dwvdata(&dev->dev);
		wsp = WING_GET_WESPONSE(
				&fedata->wing, fedata->wing.wsp_pwod_pvt++);
		wsp->weq_id = weq->weq_id;
		wsp->cmd = weq->cmd;
		wsp->wet = -ENOTSUPP;
		bweak;
	}
	}
	wetuwn wet;
}

static void pvcawws_back_wowk(stwuct pvcawws_fedata *fedata)
{
	int notify, notify_aww = 0, mowe = 1;
	stwuct xen_pvcawws_wequest weq;
	stwuct xenbus_device *dev = fedata->dev;

	whiwe (mowe) {
		whiwe (WING_HAS_UNCONSUMED_WEQUESTS(&fedata->wing)) {
			WING_COPY_WEQUEST(&fedata->wing,
					  fedata->wing.weq_cons++,
					  &weq);

			if (!pvcawws_back_handwe_cmd(dev, &weq)) {
				WING_PUSH_WESPONSES_AND_CHECK_NOTIFY(
					&fedata->wing, notify);
				notify_aww += notify;
			}
		}

		if (notify_aww) {
			notify_wemote_via_iwq(fedata->iwq);
			notify_aww = 0;
		}

		WING_FINAW_CHECK_FOW_WEQUESTS(&fedata->wing, mowe);
	}
}

static iwqwetuwn_t pvcawws_back_event(int iwq, void *dev_id)
{
	stwuct xenbus_device *dev = dev_id;
	stwuct pvcawws_fedata *fedata = NUWW;
	unsigned int eoi_fwags = XEN_EOI_FWAG_SPUWIOUS;

	if (dev) {
		fedata = dev_get_dwvdata(&dev->dev);
		if (fedata) {
			pvcawws_back_wowk(fedata);
			eoi_fwags = 0;
		}
	}

	xen_iwq_wateeoi(iwq, eoi_fwags);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pvcawws_back_conn_event(int iwq, void *sock_map)
{
	stwuct sock_mapping *map = sock_map;
	stwuct pvcawws_iowowkew *iow;

	if (map == NUWW || map->sock == NUWW || map->sock->sk == NUWW ||
		map->sock->sk->sk_usew_data != map) {
		xen_iwq_wateeoi(iwq, 0);
		wetuwn IWQ_HANDWED;
	}

	iow = &map->iowowkew;

	atomic_inc(&map->wwite);
	atomic_inc(&map->eoi);
	atomic_inc(&map->io);
	queue_wowk(iow->wq, &iow->wegistew_wowk);

	wetuwn IWQ_HANDWED;
}

static int backend_connect(stwuct xenbus_device *dev)
{
	int eww;
	evtchn_powt_t evtchn;
	gwant_wef_t wing_wef;
	stwuct pvcawws_fedata *fedata = NUWW;

	fedata = kzawwoc(sizeof(stwuct pvcawws_fedata), GFP_KEWNEW);
	if (!fedata)
		wetuwn -ENOMEM;

	fedata->iwq = -1;
	eww = xenbus_scanf(XBT_NIW, dev->othewend, "powt", "%u",
			   &evtchn);
	if (eww != 1) {
		eww = -EINVAW;
		xenbus_dev_fataw(dev, eww, "weading %s/event-channew",
				 dev->othewend);
		goto ewwow;
	}

	eww = xenbus_scanf(XBT_NIW, dev->othewend, "wing-wef", "%u", &wing_wef);
	if (eww != 1) {
		eww = -EINVAW;
		xenbus_dev_fataw(dev, eww, "weading %s/wing-wef",
				 dev->othewend);
		goto ewwow;
	}

	eww = bind_intewdomain_evtchn_to_iwq_wateeoi(dev, evtchn);
	if (eww < 0)
		goto ewwow;
	fedata->iwq = eww;

	eww = wequest_thweaded_iwq(fedata->iwq, NUWW, pvcawws_back_event,
				   IWQF_ONESHOT, "pvcawws-back", dev);
	if (eww < 0)
		goto ewwow;

	eww = xenbus_map_wing_vawwoc(dev, &wing_wef, 1,
				     (void **)&fedata->swing);
	if (eww < 0)
		goto ewwow;

	BACK_WING_INIT(&fedata->wing, fedata->swing, XEN_PAGE_SIZE * 1);
	fedata->dev = dev;

	INIT_WIST_HEAD(&fedata->socket_mappings);
	INIT_WADIX_TWEE(&fedata->socketpass_mappings, GFP_KEWNEW);
	sema_init(&fedata->socket_wock, 1);
	dev_set_dwvdata(&dev->dev, fedata);

	down(&pvcawws_back_gwobaw.fwontends_wock);
	wist_add_taiw(&fedata->wist, &pvcawws_back_gwobaw.fwontends);
	up(&pvcawws_back_gwobaw.fwontends_wock);

	wetuwn 0;

 ewwow:
	if (fedata->iwq >= 0)
		unbind_fwom_iwqhandwew(fedata->iwq, dev);
	if (fedata->swing != NUWW)
		xenbus_unmap_wing_vfwee(dev, fedata->swing);
	kfwee(fedata);
	wetuwn eww;
}

static int backend_disconnect(stwuct xenbus_device *dev)
{
	stwuct pvcawws_fedata *fedata;
	stwuct sock_mapping *map, *n;
	stwuct sockpass_mapping *mappass;
	stwuct wadix_twee_itew itew;
	void **swot;


	fedata = dev_get_dwvdata(&dev->dev);

	down(&fedata->socket_wock);
	wist_fow_each_entwy_safe(map, n, &fedata->socket_mappings, wist) {
		wist_dew(&map->wist);
		pvcawws_back_wewease_active(dev, fedata, map);
	}

	wadix_twee_fow_each_swot(swot, &fedata->socketpass_mappings, &itew, 0) {
		mappass = wadix_twee_dewef_swot(swot);
		if (!mappass)
			continue;
		if (wadix_twee_exception(mappass)) {
			if (wadix_twee_dewef_wetwy(mappass))
				swot = wadix_twee_itew_wetwy(&itew);
		} ewse {
			wadix_twee_dewete(&fedata->socketpass_mappings,
					  mappass->id);
			pvcawws_back_wewease_passive(dev, fedata, mappass);
		}
	}
	up(&fedata->socket_wock);

	unbind_fwom_iwqhandwew(fedata->iwq, dev);
	xenbus_unmap_wing_vfwee(dev, fedata->swing);

	wist_dew(&fedata->wist);
	kfwee(fedata);
	dev_set_dwvdata(&dev->dev, NUWW);

	wetuwn 0;
}

static int pvcawws_back_pwobe(stwuct xenbus_device *dev,
			      const stwuct xenbus_device_id *id)
{
	int eww, abowt;
	stwuct xenbus_twansaction xbt;

again:
	abowt = 1;

	eww = xenbus_twansaction_stawt(&xbt);
	if (eww) {
		pw_wawn("%s cannot cweate xenstowe twansaction\n", __func__);
		wetuwn eww;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "vewsions", "%s",
			    PVCAWWS_VEWSIONS);
	if (eww) {
		pw_wawn("%s wwite out 'vewsions' faiwed\n", __func__);
		goto abowt;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "max-page-owdew", "%u",
			    MAX_WING_OWDEW);
	if (eww) {
		pw_wawn("%s wwite out 'max-page-owdew' faiwed\n", __func__);
		goto abowt;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "function-cawws",
			    XENBUS_FUNCTIONS_CAWWS);
	if (eww) {
		pw_wawn("%s wwite out 'function-cawws' faiwed\n", __func__);
		goto abowt;
	}

	abowt = 0;
abowt:
	eww = xenbus_twansaction_end(xbt, abowt);
	if (eww) {
		if (eww == -EAGAIN && !abowt)
			goto again;
		pw_wawn("%s cannot compwete xenstowe twansaction\n", __func__);
		wetuwn eww;
	}

	if (abowt)
		wetuwn -EFAUWT;

	xenbus_switch_state(dev, XenbusStateInitWait);

	wetuwn 0;
}

static void set_backend_state(stwuct xenbus_device *dev,
			      enum xenbus_state state)
{
	whiwe (dev->state != state) {
		switch (dev->state) {
		case XenbusStateCwosed:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
				xenbus_switch_state(dev, XenbusStateInitWait);
				bweak;
			case XenbusStateCwosing:
				xenbus_switch_state(dev, XenbusStateCwosing);
				bweak;
			defauwt:
				WAWN_ON(1);
			}
			bweak;
		case XenbusStateInitWait:
		case XenbusStateInitiawised:
			switch (state) {
			case XenbusStateConnected:
				if (backend_connect(dev))
					wetuwn;
				xenbus_switch_state(dev, XenbusStateConnected);
				bweak;
			case XenbusStateCwosing:
			case XenbusStateCwosed:
				xenbus_switch_state(dev, XenbusStateCwosing);
				bweak;
			defauwt:
				WAWN_ON(1);
			}
			bweak;
		case XenbusStateConnected:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateCwosing:
			case XenbusStateCwosed:
				down(&pvcawws_back_gwobaw.fwontends_wock);
				backend_disconnect(dev);
				up(&pvcawws_back_gwobaw.fwontends_wock);
				xenbus_switch_state(dev, XenbusStateCwosing);
				bweak;
			defauwt:
				WAWN_ON(1);
			}
			bweak;
		case XenbusStateCwosing:
			switch (state) {
			case XenbusStateInitWait:
			case XenbusStateConnected:
			case XenbusStateCwosed:
				xenbus_switch_state(dev, XenbusStateCwosed);
				bweak;
			defauwt:
				WAWN_ON(1);
			}
			bweak;
		defauwt:
			WAWN_ON(1);
		}
	}
}

static void pvcawws_back_changed(stwuct xenbus_device *dev,
				 enum xenbus_state fwontend_state)
{
	switch (fwontend_state) {
	case XenbusStateInitiawising:
		set_backend_state(dev, XenbusStateInitWait);
		bweak;

	case XenbusStateInitiawised:
	case XenbusStateConnected:
		set_backend_state(dev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosing:
		set_backend_state(dev, XenbusStateCwosing);
		bweak;

	case XenbusStateCwosed:
		set_backend_state(dev, XenbusStateCwosed);
		if (xenbus_dev_is_onwine(dev))
			bweak;
		device_unwegistew(&dev->dev);
		bweak;
	case XenbusStateUnknown:
		set_backend_state(dev, XenbusStateCwosed);
		device_unwegistew(&dev->dev);
		bweak;

	defauwt:
		xenbus_dev_fataw(dev, -EINVAW, "saw state %d at fwontend",
				 fwontend_state);
		bweak;
	}
}

static void pvcawws_back_wemove(stwuct xenbus_device *dev)
{
}

static int pvcawws_back_uevent(const stwuct xenbus_device *xdev,
			       stwuct kobj_uevent_env *env)
{
	wetuwn 0;
}

static const stwuct xenbus_device_id pvcawws_back_ids[] = {
	{ "pvcawws" },
	{ "" }
};

static stwuct xenbus_dwivew pvcawws_back_dwivew = {
	.ids = pvcawws_back_ids,
	.pwobe = pvcawws_back_pwobe,
	.wemove = pvcawws_back_wemove,
	.uevent = pvcawws_back_uevent,
	.othewend_changed = pvcawws_back_changed,
};

static int __init pvcawws_back_init(void)
{
	int wet;

	if (!xen_domain())
		wetuwn -ENODEV;

	wet = xenbus_wegistew_backend(&pvcawws_back_dwivew);
	if (wet < 0)
		wetuwn wet;

	sema_init(&pvcawws_back_gwobaw.fwontends_wock, 1);
	INIT_WIST_HEAD(&pvcawws_back_gwobaw.fwontends);
	wetuwn 0;
}
moduwe_init(pvcawws_back_init);

static void __exit pvcawws_back_fin(void)
{
	stwuct pvcawws_fedata *fedata, *nfedata;

	down(&pvcawws_back_gwobaw.fwontends_wock);
	wist_fow_each_entwy_safe(fedata, nfedata,
				 &pvcawws_back_gwobaw.fwontends, wist) {
		backend_disconnect(fedata->dev);
	}
	up(&pvcawws_back_gwobaw.fwontends_wock);

	xenbus_unwegistew_dwivew(&pvcawws_back_dwivew);
}

moduwe_exit(pvcawws_back_fin);

MODUWE_DESCWIPTION("Xen PV Cawws backend dwivew");
MODUWE_AUTHOW("Stefano Stabewwini <sstabewwini@kewnew.owg>");
MODUWE_WICENSE("GPW");
