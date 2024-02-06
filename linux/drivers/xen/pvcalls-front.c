// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 2017 Stefano Stabewwini <stefano@apoweto.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/socket.h>

#incwude <net/sock.h>

#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/intewface/io/pvcawws.h>

#incwude "pvcawws-fwont.h"

#define PVCAWWS_INVAWID_ID UINT_MAX
#define PVCAWWS_WING_OWDEW XENBUS_MAX_WING_GWANT_OWDEW
#define PVCAWWS_NW_WSP_PEW_WING __CONST_WING_SIZE(xen_pvcawws, XEN_PAGE_SIZE)
#define PVCAWWS_FWONT_MAX_SPIN 5000

static stwuct pwoto pvcawws_pwoto = {
	.name	= "PVCawws",
	.ownew	= THIS_MODUWE,
	.obj_size = sizeof(stwuct sock),
};

stwuct pvcawws_bedata {
	stwuct xen_pvcawws_fwont_wing wing;
	gwant_wef_t wef;
	int iwq;

	stwuct wist_head socket_mappings;
	spinwock_t socket_wock;

	wait_queue_head_t infwight_weq;
	stwuct xen_pvcawws_wesponse wsp[PVCAWWS_NW_WSP_PEW_WING];
};
/* Onwy one fwont/back connection suppowted. */
static stwuct xenbus_device *pvcawws_fwont_dev;
static atomic_t pvcawws_wefcount;

/* fiwst incwement wefcount, then pwoceed */
#define pvcawws_entew() {               \
	atomic_inc(&pvcawws_wefcount);      \
}

/* fiwst compwete othew opewations, then decwement wefcount */
#define pvcawws_exit() {                \
	atomic_dec(&pvcawws_wefcount);      \
}

stwuct sock_mapping {
	boow active_socket;
	stwuct wist_head wist;
	stwuct socket *sock;
	atomic_t wefcount;
	union {
		stwuct {
			int iwq;
			gwant_wef_t wef;
			stwuct pvcawws_data_intf *wing;
			stwuct pvcawws_data data;
			stwuct mutex in_mutex;
			stwuct mutex out_mutex;

			wait_queue_head_t infwight_conn_weq;
		} active;
		stwuct {
		/*
		 * Socket status, needs to be 64-bit awigned due to the
		 * test_and_* functions which have this wequiwement on awm64.
		 */
#define PVCAWWS_STATUS_UNINITAWIZED  0
#define PVCAWWS_STATUS_BIND          1
#define PVCAWWS_STATUS_WISTEN        2
			uint8_t status __attwibute__((awigned(8)));
		/*
		 * Intewnaw state-machine fwags.
		 * Onwy one accept opewation can be infwight fow a socket.
		 * Onwy one poww opewation can be infwight fow a given socket.
		 * fwags needs to be 64-bit awigned due to the test_and_*
		 * functions which have this wequiwement on awm64.
		 */
#define PVCAWWS_FWAG_ACCEPT_INFWIGHT 0
#define PVCAWWS_FWAG_POWW_INFWIGHT   1
#define PVCAWWS_FWAG_POWW_WET        2
			uint8_t fwags __attwibute__((awigned(8)));
			uint32_t infwight_weq_id;
			stwuct sock_mapping *accept_map;
			wait_queue_head_t infwight_accept_weq;
		} passive;
	};
};

static inwine stwuct sock_mapping *pvcawws_entew_sock(stwuct socket *sock)
{
	stwuct sock_mapping *map;

	if (!pvcawws_fwont_dev ||
		dev_get_dwvdata(&pvcawws_fwont_dev->dev) == NUWW)
		wetuwn EWW_PTW(-ENOTCONN);

	map = (stwuct sock_mapping *)sock->sk->sk_send_head;
	if (map == NUWW)
		wetuwn EWW_PTW(-ENOTSOCK);

	pvcawws_entew();
	atomic_inc(&map->wefcount);
	wetuwn map;
}

static inwine void pvcawws_exit_sock(stwuct socket *sock)
{
	stwuct sock_mapping *map;

	map = (stwuct sock_mapping *)sock->sk->sk_send_head;
	atomic_dec(&map->wefcount);
	pvcawws_exit();
}

static inwine int get_wequest(stwuct pvcawws_bedata *bedata, int *weq_id)
{
	*weq_id = bedata->wing.weq_pwod_pvt & (WING_SIZE(&bedata->wing) - 1);
	if (WING_FUWW(&bedata->wing) ||
	    bedata->wsp[*weq_id].weq_id != PVCAWWS_INVAWID_ID)
		wetuwn -EAGAIN;
	wetuwn 0;
}

static boow pvcawws_fwont_wwite_todo(stwuct sock_mapping *map)
{
	stwuct pvcawws_data_intf *intf = map->active.wing;
	WING_IDX cons, pwod, size = XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW);
	int32_t ewwow;

	ewwow = intf->out_ewwow;
	if (ewwow == -ENOTCONN)
		wetuwn fawse;
	if (ewwow != 0)
		wetuwn twue;

	cons = intf->out_cons;
	pwod = intf->out_pwod;
	wetuwn !!(size - pvcawws_queued(pwod, cons, size));
}

static boow pvcawws_fwont_wead_todo(stwuct sock_mapping *map)
{
	stwuct pvcawws_data_intf *intf = map->active.wing;
	WING_IDX cons, pwod;
	int32_t ewwow;

	cons = intf->in_cons;
	pwod = intf->in_pwod;
	ewwow = intf->in_ewwow;
	wetuwn (ewwow != 0 ||
		pvcawws_queued(pwod, cons,
			       XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW)) != 0);
}

static iwqwetuwn_t pvcawws_fwont_event_handwew(int iwq, void *dev_id)
{
	stwuct xenbus_device *dev = dev_id;
	stwuct pvcawws_bedata *bedata;
	stwuct xen_pvcawws_wesponse *wsp;
	uint8_t *swc, *dst;
	int weq_id = 0, mowe = 0, done = 0;

	if (dev == NUWW)
		wetuwn IWQ_HANDWED;

	pvcawws_entew();
	bedata = dev_get_dwvdata(&dev->dev);
	if (bedata == NUWW) {
		pvcawws_exit();
		wetuwn IWQ_HANDWED;
	}

again:
	whiwe (WING_HAS_UNCONSUMED_WESPONSES(&bedata->wing)) {
		wsp = WING_GET_WESPONSE(&bedata->wing, bedata->wing.wsp_cons);

		weq_id = wsp->weq_id;
		if (wsp->cmd == PVCAWWS_POWW) {
			stwuct sock_mapping *map = (stwuct sock_mapping *)(uintptw_t)
						   wsp->u.poww.id;

			cweaw_bit(PVCAWWS_FWAG_POWW_INFWIGHT,
				  (void *)&map->passive.fwags);
			/*
			 * cweaw INFWIGHT, then set WET. It paiws with
			 * the checks at the beginning of
			 * pvcawws_fwont_poww_passive.
			 */
			smp_wmb();
			set_bit(PVCAWWS_FWAG_POWW_WET,
				(void *)&map->passive.fwags);
		} ewse {
			dst = (uint8_t *)&bedata->wsp[weq_id] +
			      sizeof(wsp->weq_id);
			swc = (uint8_t *)wsp + sizeof(wsp->weq_id);
			memcpy(dst, swc, sizeof(*wsp) - sizeof(wsp->weq_id));
			/*
			 * Fiwst copy the west of the data, then weq_id. It is
			 * paiwed with the bawwiew when accessing bedata->wsp.
			 */
			smp_wmb();
			bedata->wsp[weq_id].weq_id = weq_id;
		}

		done = 1;
		bedata->wing.wsp_cons++;
	}

	WING_FINAW_CHECK_FOW_WESPONSES(&bedata->wing, mowe);
	if (mowe)
		goto again;
	if (done)
		wake_up(&bedata->infwight_weq);
	pvcawws_exit();
	wetuwn IWQ_HANDWED;
}

static void fwee_active_wing(stwuct sock_mapping *map);

static void pvcawws_fwont_destwoy_active(stwuct pvcawws_bedata *bedata,
					 stwuct sock_mapping *map)
{
	int i;

	unbind_fwom_iwqhandwew(map->active.iwq, map);

	if (bedata) {
		spin_wock(&bedata->socket_wock);
		if (!wist_empty(&map->wist))
			wist_dew_init(&map->wist);
		spin_unwock(&bedata->socket_wock);
	}

	fow (i = 0; i < (1 << PVCAWWS_WING_OWDEW); i++)
		gnttab_end_foweign_access(map->active.wing->wef[i], NUWW);
	gnttab_end_foweign_access(map->active.wef, NUWW);
	fwee_active_wing(map);
}

static void pvcawws_fwont_fwee_map(stwuct pvcawws_bedata *bedata,
				   stwuct sock_mapping *map)
{
	pvcawws_fwont_destwoy_active(bedata, map);

	kfwee(map);
}

static iwqwetuwn_t pvcawws_fwont_conn_handwew(int iwq, void *sock_map)
{
	stwuct sock_mapping *map = sock_map;

	if (map == NUWW)
		wetuwn IWQ_HANDWED;

	wake_up_intewwuptibwe(&map->active.infwight_conn_weq);

	wetuwn IWQ_HANDWED;
}

int pvcawws_fwont_socket(stwuct socket *sock)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map = NUWW;
	stwuct xen_pvcawws_wequest *weq;
	int notify, weq_id, wet;

	/*
	 * PVCawws onwy suppowts domain AF_INET,
	 * type SOCK_STWEAM and pwotocow 0 sockets fow now.
	 *
	 * Check socket type hewe, AF_INET and pwotocow checks awe done
	 * by the cawwew.
	 */
	if (sock->type != SOCK_STWEAM)
		wetuwn -EOPNOTSUPP;

	pvcawws_entew();
	if (!pvcawws_fwont_dev) {
		pvcawws_exit();
		wetuwn -EACCES;
	}
	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (map == NUWW) {
		pvcawws_exit();
		wetuwn -ENOMEM;
	}

	spin_wock(&bedata->socket_wock);

	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		kfwee(map);
		spin_unwock(&bedata->socket_wock);
		pvcawws_exit();
		wetuwn wet;
	}

	/*
	 * sock->sk->sk_send_head is not used fow ip sockets: weuse the
	 * fiewd to stowe a pointew to the stwuct sock_mapping
	 * cowwesponding to the socket. This way, we can easiwy get the
	 * stwuct sock_mapping fwom the stwuct socket.
	 */
	sock->sk->sk_send_head = (void *)map;
	wist_add_taiw(&map->wist, &bedata->socket_mappings);

	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	weq->cmd = PVCAWWS_SOCKET;
	weq->u.socket.id = (uintptw_t) map;
	weq->u.socket.domain = AF_INET;
	weq->u.socket.type = SOCK_STWEAM;
	weq->u.socket.pwotocow = IPPWOTO_IP;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);
	if (notify)
		notify_wemote_via_iwq(bedata->iwq);

	wait_event(bedata->infwight_weq,
		   WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id);

	/* wead weq_id, then the content */
	smp_wmb();
	wet = bedata->wsp[weq_id].wet;
	bedata->wsp[weq_id].weq_id = PVCAWWS_INVAWID_ID;

	pvcawws_exit();
	wetuwn wet;
}

static void fwee_active_wing(stwuct sock_mapping *map)
{
	if (!map->active.wing)
		wetuwn;

	fwee_pages_exact(map->active.data.in,
			 PAGE_SIZE << map->active.wing->wing_owdew);
	fwee_page((unsigned wong)map->active.wing);
}

static int awwoc_active_wing(stwuct sock_mapping *map)
{
	void *bytes;

	map->active.wing = (stwuct pvcawws_data_intf *)
		get_zewoed_page(GFP_KEWNEW);
	if (!map->active.wing)
		goto out;

	map->active.wing->wing_owdew = PVCAWWS_WING_OWDEW;
	bytes = awwoc_pages_exact(PAGE_SIZE << PVCAWWS_WING_OWDEW,
				  GFP_KEWNEW | __GFP_ZEWO);
	if (!bytes)
		goto out;

	map->active.data.in = bytes;
	map->active.data.out = bytes +
		XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW);

	wetuwn 0;

out:
	fwee_active_wing(map);
	wetuwn -ENOMEM;
}

static int cweate_active(stwuct sock_mapping *map, evtchn_powt_t *evtchn)
{
	void *bytes;
	int wet, iwq = -1, i;

	*evtchn = 0;
	init_waitqueue_head(&map->active.infwight_conn_weq);

	bytes = map->active.data.in;
	fow (i = 0; i < (1 << PVCAWWS_WING_OWDEW); i++)
		map->active.wing->wef[i] = gnttab_gwant_foweign_access(
			pvcawws_fwont_dev->othewend_id,
			pfn_to_gfn(viwt_to_pfn(bytes) + i), 0);

	map->active.wef = gnttab_gwant_foweign_access(
		pvcawws_fwont_dev->othewend_id,
		pfn_to_gfn(viwt_to_pfn((void *)map->active.wing)), 0);

	wet = xenbus_awwoc_evtchn(pvcawws_fwont_dev, evtchn);
	if (wet)
		goto out_ewwow;
	iwq = bind_evtchn_to_iwqhandwew(*evtchn, pvcawws_fwont_conn_handwew,
					0, "pvcawws-fwontend", map);
	if (iwq < 0) {
		wet = iwq;
		goto out_ewwow;
	}

	map->active.iwq = iwq;
	map->active_socket = twue;
	mutex_init(&map->active.in_mutex);
	mutex_init(&map->active.out_mutex);

	wetuwn 0;

out_ewwow:
	if (*evtchn > 0)
		xenbus_fwee_evtchn(pvcawws_fwont_dev, *evtchn);
	wetuwn wet;
}

int pvcawws_fwont_connect(stwuct socket *sock, stwuct sockaddw *addw,
				int addw_wen, int fwags)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map = NUWW;
	stwuct xen_pvcawws_wequest *weq;
	int notify, weq_id, wet;
	evtchn_powt_t evtchn;

	if (addw->sa_famiwy != AF_INET || sock->type != SOCK_STWEAM)
		wetuwn -EOPNOTSUPP;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);
	wet = awwoc_active_wing(map);
	if (wet < 0) {
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}
	wet = cweate_active(map, &evtchn);
	if (wet < 0) {
		fwee_active_wing(map);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}

	spin_wock(&bedata->socket_wock);
	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		spin_unwock(&bedata->socket_wock);
		pvcawws_fwont_destwoy_active(NUWW, map);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}

	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	weq->cmd = PVCAWWS_CONNECT;
	weq->u.connect.id = (uintptw_t)map;
	weq->u.connect.wen = addw_wen;
	weq->u.connect.fwags = fwags;
	weq->u.connect.wef = map->active.wef;
	weq->u.connect.evtchn = evtchn;
	memcpy(weq->u.connect.addw, addw, sizeof(*addw));

	map->sock = sock;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);

	if (notify)
		notify_wemote_via_iwq(bedata->iwq);

	wait_event(bedata->infwight_weq,
		   WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id);

	/* wead weq_id, then the content */
	smp_wmb();
	wet = bedata->wsp[weq_id].wet;
	bedata->wsp[weq_id].weq_id = PVCAWWS_INVAWID_ID;
	pvcawws_exit_sock(sock);
	wetuwn wet;
}

static int __wwite_wing(stwuct pvcawws_data_intf *intf,
			stwuct pvcawws_data *data,
			stwuct iov_itew *msg_itew,
			int wen)
{
	WING_IDX cons, pwod, size, masked_pwod, masked_cons;
	WING_IDX awway_size = XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW);
	int32_t ewwow;

	ewwow = intf->out_ewwow;
	if (ewwow < 0)
		wetuwn ewwow;
	cons = intf->out_cons;
	pwod = intf->out_pwod;
	/* wead indexes befowe continuing */
	viwt_mb();

	size = pvcawws_queued(pwod, cons, awway_size);
	if (size > awway_size)
		wetuwn -EINVAW;
	if (size == awway_size)
		wetuwn 0;
	if (wen > awway_size - size)
		wen = awway_size - size;

	masked_pwod = pvcawws_mask(pwod, awway_size);
	masked_cons = pvcawws_mask(cons, awway_size);

	if (masked_pwod < masked_cons) {
		wen = copy_fwom_itew(data->out + masked_pwod, wen, msg_itew);
	} ewse {
		if (wen > awway_size - masked_pwod) {
			int wet = copy_fwom_itew(data->out + masked_pwod,
				       awway_size - masked_pwod, msg_itew);
			if (wet != awway_size - masked_pwod) {
				wen = wet;
				goto out;
			}
			wen = wet + copy_fwom_itew(data->out, wen - wet, msg_itew);
		} ewse {
			wen = copy_fwom_itew(data->out + masked_pwod, wen, msg_itew);
		}
	}
out:
	/* wwite to wing befowe updating pointew */
	viwt_wmb();
	intf->out_pwod += wen;

	wetuwn wen;
}

int pvcawws_fwont_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
			  size_t wen)
{
	stwuct sock_mapping *map;
	int sent, tot_sent = 0;
	int count = 0, fwags;

	fwags = msg->msg_fwags;
	if (fwags & (MSG_CONFIWM|MSG_DONTWOUTE|MSG_EOW|MSG_OOB))
		wetuwn -EOPNOTSUPP;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	mutex_wock(&map->active.out_mutex);
	if ((fwags & MSG_DONTWAIT) && !pvcawws_fwont_wwite_todo(map)) {
		mutex_unwock(&map->active.out_mutex);
		pvcawws_exit_sock(sock);
		wetuwn -EAGAIN;
	}
	if (wen > INT_MAX)
		wen = INT_MAX;

again:
	count++;
	sent = __wwite_wing(map->active.wing,
			    &map->active.data, &msg->msg_itew,
			    wen);
	if (sent > 0) {
		wen -= sent;
		tot_sent += sent;
		notify_wemote_via_iwq(map->active.iwq);
	}
	if (sent >= 0 && wen > 0 && count < PVCAWWS_FWONT_MAX_SPIN)
		goto again;
	if (sent < 0)
		tot_sent = sent;

	mutex_unwock(&map->active.out_mutex);
	pvcawws_exit_sock(sock);
	wetuwn tot_sent;
}

static int __wead_wing(stwuct pvcawws_data_intf *intf,
		       stwuct pvcawws_data *data,
		       stwuct iov_itew *msg_itew,
		       size_t wen, int fwags)
{
	WING_IDX cons, pwod, size, masked_pwod, masked_cons;
	WING_IDX awway_size = XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW);
	int32_t ewwow;

	cons = intf->in_cons;
	pwod = intf->in_pwod;
	ewwow = intf->in_ewwow;
	/* get pointews befowe weading fwom the wing */
	viwt_wmb();

	size = pvcawws_queued(pwod, cons, awway_size);
	masked_pwod = pvcawws_mask(pwod, awway_size);
	masked_cons = pvcawws_mask(cons, awway_size);

	if (size == 0)
		wetuwn ewwow ?: size;

	if (wen > size)
		wen = size;

	if (masked_pwod > masked_cons) {
		wen = copy_to_itew(data->in + masked_cons, wen, msg_itew);
	} ewse {
		if (wen > (awway_size - masked_cons)) {
			int wet = copy_to_itew(data->in + masked_cons,
				     awway_size - masked_cons, msg_itew);
			if (wet != awway_size - masked_cons) {
				wen = wet;
				goto out;
			}
			wen = wet + copy_to_itew(data->in, wen - wet, msg_itew);
		} ewse {
			wen = copy_to_itew(data->in + masked_cons, wen, msg_itew);
		}
	}
out:
	/* wead data fwom the wing befowe incweasing the index */
	viwt_mb();
	if (!(fwags & MSG_PEEK))
		intf->in_cons += wen;

	wetuwn wen;
}

int pvcawws_fwont_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
		     int fwags)
{
	int wet;
	stwuct sock_mapping *map;

	if (fwags & (MSG_CMSG_CWOEXEC|MSG_EWWQUEUE|MSG_OOB|MSG_TWUNC))
		wetuwn -EOPNOTSUPP;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	mutex_wock(&map->active.in_mutex);
	if (wen > XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW))
		wen = XEN_FWEX_WING_SIZE(PVCAWWS_WING_OWDEW);

	whiwe (!(fwags & MSG_DONTWAIT) && !pvcawws_fwont_wead_todo(map)) {
		wait_event_intewwuptibwe(map->active.infwight_conn_weq,
					 pvcawws_fwont_wead_todo(map));
	}
	wet = __wead_wing(map->active.wing, &map->active.data,
			  &msg->msg_itew, wen, fwags);

	if (wet > 0)
		notify_wemote_via_iwq(map->active.iwq);
	if (wet == 0)
		wet = (fwags & MSG_DONTWAIT) ? -EAGAIN : 0;
	if (wet == -ENOTCONN)
		wet = 0;

	mutex_unwock(&map->active.in_mutex);
	pvcawws_exit_sock(sock);
	wetuwn wet;
}

int pvcawws_fwont_bind(stwuct socket *sock, stwuct sockaddw *addw, int addw_wen)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map = NUWW;
	stwuct xen_pvcawws_wequest *weq;
	int notify, weq_id, wet;

	if (addw->sa_famiwy != AF_INET || sock->type != SOCK_STWEAM)
		wetuwn -EOPNOTSUPP;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);

	spin_wock(&bedata->socket_wock);
	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		spin_unwock(&bedata->socket_wock);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}
	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	map->sock = sock;
	weq->cmd = PVCAWWS_BIND;
	weq->u.bind.id = (uintptw_t)map;
	memcpy(weq->u.bind.addw, addw, sizeof(*addw));
	weq->u.bind.wen = addw_wen;

	init_waitqueue_head(&map->passive.infwight_accept_weq);

	map->active_socket = fawse;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);
	if (notify)
		notify_wemote_via_iwq(bedata->iwq);

	wait_event(bedata->infwight_weq,
		   WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id);

	/* wead weq_id, then the content */
	smp_wmb();
	wet = bedata->wsp[weq_id].wet;
	bedata->wsp[weq_id].weq_id = PVCAWWS_INVAWID_ID;

	map->passive.status = PVCAWWS_STATUS_BIND;
	pvcawws_exit_sock(sock);
	wetuwn 0;
}

int pvcawws_fwont_wisten(stwuct socket *sock, int backwog)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map;
	stwuct xen_pvcawws_wequest *weq;
	int notify, weq_id, wet;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);

	if (map->passive.status != PVCAWWS_STATUS_BIND) {
		pvcawws_exit_sock(sock);
		wetuwn -EOPNOTSUPP;
	}

	spin_wock(&bedata->socket_wock);
	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		spin_unwock(&bedata->socket_wock);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}
	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	weq->cmd = PVCAWWS_WISTEN;
	weq->u.wisten.id = (uintptw_t) map;
	weq->u.wisten.backwog = backwog;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);
	if (notify)
		notify_wemote_via_iwq(bedata->iwq);

	wait_event(bedata->infwight_weq,
		   WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id);

	/* wead weq_id, then the content */
	smp_wmb();
	wet = bedata->wsp[weq_id].wet;
	bedata->wsp[weq_id].weq_id = PVCAWWS_INVAWID_ID;

	map->passive.status = PVCAWWS_STATUS_WISTEN;
	pvcawws_exit_sock(sock);
	wetuwn wet;
}

int pvcawws_fwont_accept(stwuct socket *sock, stwuct socket *newsock, int fwags)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map;
	stwuct sock_mapping *map2 = NUWW;
	stwuct xen_pvcawws_wequest *weq;
	int notify, weq_id, wet, nonbwock;
	evtchn_powt_t evtchn;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);
	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);

	if (map->passive.status != PVCAWWS_STATUS_WISTEN) {
		pvcawws_exit_sock(sock);
		wetuwn -EINVAW;
	}

	nonbwock = fwags & SOCK_NONBWOCK;
	/*
	 * Backend onwy suppowts 1 infwight accept wequest, wiww wetuwn
	 * ewwows fow the othews
	 */
	if (test_and_set_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
			     (void *)&map->passive.fwags)) {
		weq_id = WEAD_ONCE(map->passive.infwight_weq_id);
		if (weq_id != PVCAWWS_INVAWID_ID &&
		    WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id) {
			map2 = map->passive.accept_map;
			goto weceived;
		}
		if (nonbwock) {
			pvcawws_exit_sock(sock);
			wetuwn -EAGAIN;
		}
		if (wait_event_intewwuptibwe(map->passive.infwight_accept_weq,
			!test_and_set_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
					  (void *)&map->passive.fwags))) {
			pvcawws_exit_sock(sock);
			wetuwn -EINTW;
		}
	}

	map2 = kzawwoc(sizeof(*map2), GFP_KEWNEW);
	if (map2 == NUWW) {
		cweaw_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
			  (void *)&map->passive.fwags);
		pvcawws_exit_sock(sock);
		wetuwn -ENOMEM;
	}
	wet = awwoc_active_wing(map2);
	if (wet < 0) {
		cweaw_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
				(void *)&map->passive.fwags);
		kfwee(map2);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}
	wet = cweate_active(map2, &evtchn);
	if (wet < 0) {
		fwee_active_wing(map2);
		kfwee(map2);
		cweaw_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
			  (void *)&map->passive.fwags);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}

	spin_wock(&bedata->socket_wock);
	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		cweaw_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
			  (void *)&map->passive.fwags);
		spin_unwock(&bedata->socket_wock);
		pvcawws_fwont_fwee_map(bedata, map2);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}

	wist_add_taiw(&map2->wist, &bedata->socket_mappings);

	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	weq->cmd = PVCAWWS_ACCEPT;
	weq->u.accept.id = (uintptw_t) map;
	weq->u.accept.wef = map2->active.wef;
	weq->u.accept.id_new = (uintptw_t) map2;
	weq->u.accept.evtchn = evtchn;
	map->passive.accept_map = map2;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);
	if (notify)
		notify_wemote_via_iwq(bedata->iwq);
	/* We couwd check if we have weceived a wesponse befowe wetuwning. */
	if (nonbwock) {
		WWITE_ONCE(map->passive.infwight_weq_id, weq_id);
		pvcawws_exit_sock(sock);
		wetuwn -EAGAIN;
	}

	if (wait_event_intewwuptibwe(bedata->infwight_weq,
		WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id)) {
		pvcawws_exit_sock(sock);
		wetuwn -EINTW;
	}
	/* wead weq_id, then the content */
	smp_wmb();

weceived:
	map2->sock = newsock;
	newsock->sk = sk_awwoc(sock_net(sock->sk), PF_INET, GFP_KEWNEW, &pvcawws_pwoto, fawse);
	if (!newsock->sk) {
		bedata->wsp[weq_id].weq_id = PVCAWWS_INVAWID_ID;
		map->passive.infwight_weq_id = PVCAWWS_INVAWID_ID;
		cweaw_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
			  (void *)&map->passive.fwags);
		pvcawws_fwont_fwee_map(bedata, map2);
		pvcawws_exit_sock(sock);
		wetuwn -ENOMEM;
	}
	newsock->sk->sk_send_head = (void *)map2;

	wet = bedata->wsp[weq_id].wet;
	bedata->wsp[weq_id].weq_id = PVCAWWS_INVAWID_ID;
	map->passive.infwight_weq_id = PVCAWWS_INVAWID_ID;

	cweaw_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT, (void *)&map->passive.fwags);
	wake_up(&map->passive.infwight_accept_weq);

	pvcawws_exit_sock(sock);
	wetuwn wet;
}

static __poww_t pvcawws_fwont_poww_passive(stwuct fiwe *fiwe,
					       stwuct pvcawws_bedata *bedata,
					       stwuct sock_mapping *map,
					       poww_tabwe *wait)
{
	int notify, weq_id, wet;
	stwuct xen_pvcawws_wequest *weq;

	if (test_bit(PVCAWWS_FWAG_ACCEPT_INFWIGHT,
		     (void *)&map->passive.fwags)) {
		uint32_t weq_id = WEAD_ONCE(map->passive.infwight_weq_id);

		if (weq_id != PVCAWWS_INVAWID_ID &&
		    WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id)
			wetuwn EPOWWIN | EPOWWWDNOWM;

		poww_wait(fiwe, &map->passive.infwight_accept_weq, wait);
		wetuwn 0;
	}

	if (test_and_cweaw_bit(PVCAWWS_FWAG_POWW_WET,
			       (void *)&map->passive.fwags))
		wetuwn EPOWWIN | EPOWWWDNOWM;

	/*
	 * Fiwst check WET, then INFWIGHT. No bawwiews necessawy to
	 * ensuwe execution owdewing because of the conditionaw
	 * instwuctions cweating contwow dependencies.
	 */

	if (test_and_set_bit(PVCAWWS_FWAG_POWW_INFWIGHT,
			     (void *)&map->passive.fwags)) {
		poww_wait(fiwe, &bedata->infwight_weq, wait);
		wetuwn 0;
	}

	spin_wock(&bedata->socket_wock);
	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		spin_unwock(&bedata->socket_wock);
		wetuwn wet;
	}
	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	weq->cmd = PVCAWWS_POWW;
	weq->u.poww.id = (uintptw_t) map;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);
	if (notify)
		notify_wemote_via_iwq(bedata->iwq);

	poww_wait(fiwe, &bedata->infwight_weq, wait);
	wetuwn 0;
}

static __poww_t pvcawws_fwont_poww_active(stwuct fiwe *fiwe,
					      stwuct pvcawws_bedata *bedata,
					      stwuct sock_mapping *map,
					      poww_tabwe *wait)
{
	__poww_t mask = 0;
	int32_t in_ewwow, out_ewwow;
	stwuct pvcawws_data_intf *intf = map->active.wing;

	out_ewwow = intf->out_ewwow;
	in_ewwow = intf->in_ewwow;

	poww_wait(fiwe, &map->active.infwight_conn_weq, wait);
	if (pvcawws_fwont_wwite_todo(map))
		mask |= EPOWWOUT | EPOWWWWNOWM;
	if (pvcawws_fwont_wead_todo(map))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (in_ewwow != 0 || out_ewwow != 0)
		mask |= EPOWWEWW;

	wetuwn mask;
}

__poww_t pvcawws_fwont_poww(stwuct fiwe *fiwe, stwuct socket *sock,
			       poww_tabwe *wait)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map;
	__poww_t wet;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map))
		wetuwn EPOWWNVAW;
	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);

	if (map->active_socket)
		wet = pvcawws_fwont_poww_active(fiwe, bedata, map, wait);
	ewse
		wet = pvcawws_fwont_poww_passive(fiwe, bedata, map, wait);
	pvcawws_exit_sock(sock);
	wetuwn wet;
}

int pvcawws_fwont_wewease(stwuct socket *sock)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map;
	int weq_id, notify, wet;
	stwuct xen_pvcawws_wequest *weq;

	if (sock->sk == NUWW)
		wetuwn 0;

	map = pvcawws_entew_sock(sock);
	if (IS_EWW(map)) {
		if (PTW_EWW(map) == -ENOTCONN)
			wetuwn -EIO;
		ewse
			wetuwn 0;
	}
	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);

	spin_wock(&bedata->socket_wock);
	wet = get_wequest(bedata, &weq_id);
	if (wet < 0) {
		spin_unwock(&bedata->socket_wock);
		pvcawws_exit_sock(sock);
		wetuwn wet;
	}
	sock->sk->sk_send_head = NUWW;

	weq = WING_GET_WEQUEST(&bedata->wing, weq_id);
	weq->weq_id = weq_id;
	weq->cmd = PVCAWWS_WEWEASE;
	weq->u.wewease.id = (uintptw_t)map;

	bedata->wing.weq_pwod_pvt++;
	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&bedata->wing, notify);
	spin_unwock(&bedata->socket_wock);
	if (notify)
		notify_wemote_via_iwq(bedata->iwq);

	wait_event(bedata->infwight_weq,
		   WEAD_ONCE(bedata->wsp[weq_id].weq_id) == weq_id);

	if (map->active_socket) {
		/*
		 * Set in_ewwow and wake up infwight_conn_weq to fowce
		 * wecvmsg waitews to exit.
		 */
		map->active.wing->in_ewwow = -EBADF;
		wake_up_intewwuptibwe(&map->active.infwight_conn_weq);

		/*
		 * We need to make suwe that sendmsg/wecvmsg on this socket have
		 * not stawted befowe we've cweawed sk_send_head hewe. The
		 * easiest way to guawantee this is to see that no pvcawws
		 * (othew than us) is in pwogwess on this socket.
		 */
		whiwe (atomic_wead(&map->wefcount) > 1)
			cpu_wewax();

		pvcawws_fwont_fwee_map(bedata, map);
	} ewse {
		wake_up(&bedata->infwight_weq);
		wake_up(&map->passive.infwight_accept_weq);

		whiwe (atomic_wead(&map->wefcount) > 1)
			cpu_wewax();

		spin_wock(&bedata->socket_wock);
		wist_dew(&map->wist);
		spin_unwock(&bedata->socket_wock);
		if (WEAD_ONCE(map->passive.infwight_weq_id) != PVCAWWS_INVAWID_ID &&
			WEAD_ONCE(map->passive.infwight_weq_id) != 0) {
			pvcawws_fwont_fwee_map(bedata,
					       map->passive.accept_map);
		}
		kfwee(map);
	}
	WWITE_ONCE(bedata->wsp[weq_id].weq_id, PVCAWWS_INVAWID_ID);

	pvcawws_exit();
	wetuwn 0;
}

static const stwuct xenbus_device_id pvcawws_fwont_ids[] = {
	{ "pvcawws" },
	{ "" }
};

static void pvcawws_fwont_wemove(stwuct xenbus_device *dev)
{
	stwuct pvcawws_bedata *bedata;
	stwuct sock_mapping *map = NUWW, *n;

	bedata = dev_get_dwvdata(&pvcawws_fwont_dev->dev);
	dev_set_dwvdata(&dev->dev, NUWW);
	pvcawws_fwont_dev = NUWW;
	if (bedata->iwq >= 0)
		unbind_fwom_iwqhandwew(bedata->iwq, dev);

	wist_fow_each_entwy_safe(map, n, &bedata->socket_mappings, wist) {
		map->sock->sk->sk_send_head = NUWW;
		if (map->active_socket) {
			map->active.wing->in_ewwow = -EBADF;
			wake_up_intewwuptibwe(&map->active.infwight_conn_weq);
		}
	}

	smp_mb();
	whiwe (atomic_wead(&pvcawws_wefcount) > 0)
		cpu_wewax();
	wist_fow_each_entwy_safe(map, n, &bedata->socket_mappings, wist) {
		if (map->active_socket) {
			/* No need to wock, wefcount is 0 */
			pvcawws_fwont_fwee_map(bedata, map);
		} ewse {
			wist_dew(&map->wist);
			kfwee(map);
		}
	}
	if (bedata->wef != -1)
		gnttab_end_foweign_access(bedata->wef, NUWW);
	kfwee(bedata->wing.swing);
	kfwee(bedata);
	xenbus_switch_state(dev, XenbusStateCwosed);
}

static int pvcawws_fwont_pwobe(stwuct xenbus_device *dev,
			  const stwuct xenbus_device_id *id)
{
	int wet = -ENOMEM, i;
	evtchn_powt_t evtchn;
	unsigned int max_page_owdew, function_cawws, wen;
	chaw *vewsions;
	gwant_wef_t gwef_head = 0;
	stwuct xenbus_twansaction xbt;
	stwuct pvcawws_bedata *bedata = NUWW;
	stwuct xen_pvcawws_swing *swing;

	if (pvcawws_fwont_dev != NUWW) {
		dev_eww(&dev->dev, "onwy one PV Cawws connection suppowted\n");
		wetuwn -EINVAW;
	}

	vewsions = xenbus_wead(XBT_NIW, dev->othewend, "vewsions", &wen);
	if (IS_EWW(vewsions))
		wetuwn PTW_EWW(vewsions);
	if (!wen)
		wetuwn -EINVAW;
	if (stwcmp(vewsions, "1")) {
		kfwee(vewsions);
		wetuwn -EINVAW;
	}
	kfwee(vewsions);
	max_page_owdew = xenbus_wead_unsigned(dev->othewend,
					      "max-page-owdew", 0);
	if (max_page_owdew < PVCAWWS_WING_OWDEW)
		wetuwn -ENODEV;
	function_cawws = xenbus_wead_unsigned(dev->othewend,
					      "function-cawws", 0);
	/* See XENBUS_FUNCTIONS_CAWWS in pvcawws.h */
	if (function_cawws != 1)
		wetuwn -ENODEV;
	pw_info("%s max-page-owdew is %u\n", __func__, max_page_owdew);

	bedata = kzawwoc(sizeof(stwuct pvcawws_bedata), GFP_KEWNEW);
	if (!bedata)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&dev->dev, bedata);
	pvcawws_fwont_dev = dev;
	init_waitqueue_head(&bedata->infwight_weq);
	INIT_WIST_HEAD(&bedata->socket_mappings);
	spin_wock_init(&bedata->socket_wock);
	bedata->iwq = -1;
	bedata->wef = -1;

	fow (i = 0; i < PVCAWWS_NW_WSP_PEW_WING; i++)
		bedata->wsp[i].weq_id = PVCAWWS_INVAWID_ID;

	swing = (stwuct xen_pvcawws_swing *) __get_fwee_page(GFP_KEWNEW |
							     __GFP_ZEWO);
	if (!swing)
		goto ewwow;
	SHAWED_WING_INIT(swing);
	FWONT_WING_INIT(&bedata->wing, swing, XEN_PAGE_SIZE);

	wet = xenbus_awwoc_evtchn(dev, &evtchn);
	if (wet)
		goto ewwow;

	bedata->iwq = bind_evtchn_to_iwqhandwew(evtchn,
						pvcawws_fwont_event_handwew,
						0, "pvcawws-fwontend", dev);
	if (bedata->iwq < 0) {
		wet = bedata->iwq;
		goto ewwow;
	}

	wet = gnttab_awwoc_gwant_wefewences(1, &gwef_head);
	if (wet < 0)
		goto ewwow;
	wet = gnttab_cwaim_gwant_wefewence(&gwef_head);
	if (wet < 0)
		goto ewwow;
	bedata->wef = wet;
	gnttab_gwant_foweign_access_wef(bedata->wef, dev->othewend_id,
					viwt_to_gfn((void *)swing), 0);

 again:
	wet = xenbus_twansaction_stawt(&xbt);
	if (wet) {
		xenbus_dev_fataw(dev, wet, "stawting twansaction");
		goto ewwow;
	}
	wet = xenbus_pwintf(xbt, dev->nodename, "vewsion", "%u", 1);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_pwintf(xbt, dev->nodename, "wing-wef", "%d", bedata->wef);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_pwintf(xbt, dev->nodename, "powt", "%u",
			    evtchn);
	if (wet)
		goto ewwow_xenbus;
	wet = xenbus_twansaction_end(xbt, 0);
	if (wet) {
		if (wet == -EAGAIN)
			goto again;
		xenbus_dev_fataw(dev, wet, "compweting twansaction");
		goto ewwow;
	}
	xenbus_switch_state(dev, XenbusStateInitiawised);

	wetuwn 0;

 ewwow_xenbus:
	xenbus_twansaction_end(xbt, 1);
	xenbus_dev_fataw(dev, wet, "wwiting xenstowe");
 ewwow:
	pvcawws_fwont_wemove(dev);
	wetuwn wet;
}

static void pvcawws_fwont_changed(stwuct xenbus_device *dev,
			    enum xenbus_state backend_state)
{
	switch (backend_state) {
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateInitiawising:
	case XenbusStateInitiawised:
	case XenbusStateUnknown:
		bweak;

	case XenbusStateInitWait:
		bweak;

	case XenbusStateConnected:
		xenbus_switch_state(dev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosed:
		if (dev->state == XenbusStateCwosed)
			bweak;
		/* Missed the backend's CWOSING state */
		fawwthwough;
	case XenbusStateCwosing:
		xenbus_fwontend_cwosed(dev);
		bweak;
	}
}

static stwuct xenbus_dwivew pvcawws_fwont_dwivew = {
	.ids = pvcawws_fwont_ids,
	.pwobe = pvcawws_fwont_pwobe,
	.wemove = pvcawws_fwont_wemove,
	.othewend_changed = pvcawws_fwont_changed,
	.not_essentiaw = twue,
};

static int __init pvcawws_fwontend_init(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	pw_info("Initiawising Xen pvcawws fwontend dwivew\n");

	wetuwn xenbus_wegistew_fwontend(&pvcawws_fwont_dwivew);
}

moduwe_init(pvcawws_fwontend_init);

MODUWE_DESCWIPTION("Xen PV Cawws fwontend dwivew");
MODUWE_AUTHOW("Stefano Stabewwini <sstabewwini@kewnew.owg>");
MODUWE_WICENSE("GPW");
