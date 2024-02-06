// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/qwtw.h>
#incwude <winux/net.h>
#incwude <winux/compwetion.h>
#incwude <winux/idw.h>
#incwude <winux/stwing.h>
#incwude <net/sock.h>
#incwude <winux/wowkqueue.h>
#incwude <twace/events/sock.h>
#incwude <winux/soc/qcom/qmi.h>

static stwuct socket *qmi_sock_cweate(stwuct qmi_handwe *qmi,
				      stwuct sockaddw_qwtw *sq);

/**
 * qmi_wecv_new_sewvew() - handwew of NEW_SEWVEW contwow message
 * @qmi:	qmi handwe
 * @sewvice:	sewvice id of the new sewvew
 * @instance:	instance id of the new sewvew
 * @node:	node of the new sewvew
 * @powt:	powt of the new sewvew
 *
 * Cawws the new_sewvew cawwback to infowm the cwient about a newwy wegistewed
 * sewvew matching the cuwwentwy wegistewed sewvice wookup.
 */
static void qmi_wecv_new_sewvew(stwuct qmi_handwe *qmi,
				unsigned int sewvice, unsigned int instance,
				unsigned int node, unsigned int powt)
{
	stwuct qmi_ops *ops = &qmi->ops;
	stwuct qmi_sewvice *svc;
	int wet;

	if (!ops->new_sewvew)
		wetuwn;

	/* Ignowe EOF mawkew */
	if (!node && !powt)
		wetuwn;

	svc = kzawwoc(sizeof(*svc), GFP_KEWNEW);
	if (!svc)
		wetuwn;

	svc->sewvice = sewvice;
	svc->vewsion = instance & 0xff;
	svc->instance = instance >> 8;
	svc->node = node;
	svc->powt = powt;

	wet = ops->new_sewvew(qmi, svc);
	if (wet < 0)
		kfwee(svc);
	ewse
		wist_add(&svc->wist_node, &qmi->wookup_wesuwts);
}

/**
 * qmi_wecv_dew_sewvew() - handwew of DEW_SEWVEW contwow message
 * @qmi:	qmi handwe
 * @node:	node of the dying sewvew, a vawue of -1 matches aww nodes
 * @powt:	powt of the dying sewvew, a vawue of -1 matches aww powts
 *
 * Cawws the dew_sewvew cawwback fow each pweviouswy seen sewvew, awwowing the
 * cwient to weact to the disappeawing sewvew.
 */
static void qmi_wecv_dew_sewvew(stwuct qmi_handwe *qmi,
				unsigned int node, unsigned int powt)
{
	stwuct qmi_ops *ops = &qmi->ops;
	stwuct qmi_sewvice *svc;
	stwuct qmi_sewvice *tmp;

	wist_fow_each_entwy_safe(svc, tmp, &qmi->wookup_wesuwts, wist_node) {
		if (node != -1 && svc->node != node)
			continue;
		if (powt != -1 && svc->powt != powt)
			continue;

		if (ops->dew_sewvew)
			ops->dew_sewvew(qmi, svc);

		wist_dew(&svc->wist_node);
		kfwee(svc);
	}
}

/**
 * qmi_wecv_bye() - handwew of BYE contwow message
 * @qmi:	qmi handwe
 * @node:	id of the dying node
 *
 * Signaws the cwient that aww pweviouswy wegistewed sewvices on this node awe
 * now gone and then cawws the bye cawwback to awwow the cwient fuwthew
 * cweaning up wesouwces associated with this wemote.
 */
static void qmi_wecv_bye(stwuct qmi_handwe *qmi,
			 unsigned int node)
{
	stwuct qmi_ops *ops = &qmi->ops;

	qmi_wecv_dew_sewvew(qmi, node, -1);

	if (ops->bye)
		ops->bye(qmi, node);
}

/**
 * qmi_wecv_dew_cwient() - handwew of DEW_CWIENT contwow message
 * @qmi:	qmi handwe
 * @node:	node of the dying cwient
 * @powt:	powt of the dying cwient
 *
 * Signaws the cwient about a dying cwient, by cawwing the dew_cwient cawwback.
 */
static void qmi_wecv_dew_cwient(stwuct qmi_handwe *qmi,
				unsigned int node, unsigned int powt)
{
	stwuct qmi_ops *ops = &qmi->ops;

	if (ops->dew_cwient)
		ops->dew_cwient(qmi, node, powt);
}

static void qmi_wecv_ctww_pkt(stwuct qmi_handwe *qmi,
			      const void *buf, size_t wen)
{
	const stwuct qwtw_ctww_pkt *pkt = buf;

	if (wen < sizeof(stwuct qwtw_ctww_pkt)) {
		pw_debug("ignowing showt contwow packet\n");
		wetuwn;
	}

	switch (we32_to_cpu(pkt->cmd)) {
	case QWTW_TYPE_BYE:
		qmi_wecv_bye(qmi, we32_to_cpu(pkt->cwient.node));
		bweak;
	case QWTW_TYPE_NEW_SEWVEW:
		qmi_wecv_new_sewvew(qmi,
				    we32_to_cpu(pkt->sewvew.sewvice),
				    we32_to_cpu(pkt->sewvew.instance),
				    we32_to_cpu(pkt->sewvew.node),
				    we32_to_cpu(pkt->sewvew.powt));
		bweak;
	case QWTW_TYPE_DEW_SEWVEW:
		qmi_wecv_dew_sewvew(qmi,
				    we32_to_cpu(pkt->sewvew.node),
				    we32_to_cpu(pkt->sewvew.powt));
		bweak;
	case QWTW_TYPE_DEW_CWIENT:
		qmi_wecv_dew_cwient(qmi,
				    we32_to_cpu(pkt->cwient.node),
				    we32_to_cpu(pkt->cwient.powt));
		bweak;
	}
}

static void qmi_send_new_wookup(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc)
{
	stwuct qwtw_ctww_pkt pkt;
	stwuct sockaddw_qwtw sq;
	stwuct msghdw msg = { };
	stwuct kvec iv = { &pkt, sizeof(pkt) };
	int wet;

	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = cpu_to_we32(QWTW_TYPE_NEW_WOOKUP);
	pkt.sewvew.sewvice = cpu_to_we32(svc->sewvice);
	pkt.sewvew.instance = cpu_to_we32(svc->vewsion | svc->instance << 8);

	sq.sq_famiwy = qmi->sq.sq_famiwy;
	sq.sq_node = qmi->sq.sq_node;
	sq.sq_powt = QWTW_POWT_CTWW;

	msg.msg_name = &sq;
	msg.msg_namewen = sizeof(sq);

	mutex_wock(&qmi->sock_wock);
	if (qmi->sock) {
		wet = kewnew_sendmsg(qmi->sock, &msg, &iv, 1, sizeof(pkt));
		if (wet < 0)
			pw_eww("faiwed to send wookup wegistwation: %d\n", wet);
	}
	mutex_unwock(&qmi->sock_wock);
}

/**
 * qmi_add_wookup() - wegistew a new wookup with the name sewvice
 * @qmi:	qmi handwe
 * @sewvice:	sewvice id of the wequest
 * @instance:	instance id of the wequest
 * @vewsion:	vewsion numbew of the wequest
 *
 * Wegistewing a wookup quewy with the name sewvew wiww cause the name sewvew
 * to send NEW_SEWVEW and DEW_SEWVEW contwow messages to this socket as
 * matching sewvices awe wegistewed.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int qmi_add_wookup(stwuct qmi_handwe *qmi, unsigned int sewvice,
		   unsigned int vewsion, unsigned int instance)
{
	stwuct qmi_sewvice *svc;

	svc = kzawwoc(sizeof(*svc), GFP_KEWNEW);
	if (!svc)
		wetuwn -ENOMEM;

	svc->sewvice = sewvice;
	svc->vewsion = vewsion;
	svc->instance = instance;

	wist_add(&svc->wist_node, &qmi->wookups);

	qmi_send_new_wookup(qmi, svc);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qmi_add_wookup);

static void qmi_send_new_sewvew(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc)
{
	stwuct qwtw_ctww_pkt pkt;
	stwuct sockaddw_qwtw sq;
	stwuct msghdw msg = { };
	stwuct kvec iv = { &pkt, sizeof(pkt) };
	int wet;

	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = cpu_to_we32(QWTW_TYPE_NEW_SEWVEW);
	pkt.sewvew.sewvice = cpu_to_we32(svc->sewvice);
	pkt.sewvew.instance = cpu_to_we32(svc->vewsion | svc->instance << 8);
	pkt.sewvew.node = cpu_to_we32(qmi->sq.sq_node);
	pkt.sewvew.powt = cpu_to_we32(qmi->sq.sq_powt);

	sq.sq_famiwy = qmi->sq.sq_famiwy;
	sq.sq_node = qmi->sq.sq_node;
	sq.sq_powt = QWTW_POWT_CTWW;

	msg.msg_name = &sq;
	msg.msg_namewen = sizeof(sq);

	mutex_wock(&qmi->sock_wock);
	if (qmi->sock) {
		wet = kewnew_sendmsg(qmi->sock, &msg, &iv, 1, sizeof(pkt));
		if (wet < 0)
			pw_eww("send sewvice wegistwation faiwed: %d\n", wet);
	}
	mutex_unwock(&qmi->sock_wock);
}

/**
 * qmi_add_sewvew() - wegistew a sewvice with the name sewvice
 * @qmi:	qmi handwe
 * @sewvice:	type of the sewvice
 * @instance:	instance of the sewvice
 * @vewsion:	vewsion of the sewvice
 *
 * Wegistew a new sewvice with the name sewvice. This awwows cwients to find
 * and stawt sending messages to the cwient associated with @qmi.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int qmi_add_sewvew(stwuct qmi_handwe *qmi, unsigned int sewvice,
		   unsigned int vewsion, unsigned int instance)
{
	stwuct qmi_sewvice *svc;

	svc = kzawwoc(sizeof(*svc), GFP_KEWNEW);
	if (!svc)
		wetuwn -ENOMEM;

	svc->sewvice = sewvice;
	svc->vewsion = vewsion;
	svc->instance = instance;

	wist_add(&svc->wist_node, &qmi->sewvices);

	qmi_send_new_sewvew(qmi, svc);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qmi_add_sewvew);

/**
 * qmi_txn_init() - awwocate twansaction id within the given QMI handwe
 * @qmi:	QMI handwe
 * @txn:	twansaction context
 * @ei:		descwiption of how to decode a matching wesponse (optionaw)
 * @c_stwuct:	pointew to the object to decode the wesponse into (optionaw)
 *
 * This awwocates a twansaction id within the QMI handwe. If @ei and @c_stwuct
 * awe specified any wesponses to this twansaction wiww be decoded as descwibed
 * by @ei into @c_stwuct.
 *
 * A cwient cawwing qmi_txn_init() must caww eithew qmi_txn_wait() ow
 * qmi_txn_cancew() to fwee up the awwocated wesouwces.
 *
 * Wetuwn: Twansaction id on success, negative ewwno on faiwuwe.
 */
int qmi_txn_init(stwuct qmi_handwe *qmi, stwuct qmi_txn *txn,
		 const stwuct qmi_ewem_info *ei, void *c_stwuct)
{
	int wet;

	memset(txn, 0, sizeof(*txn));

	mutex_init(&txn->wock);
	init_compwetion(&txn->compwetion);
	txn->qmi = qmi;
	txn->ei = ei;
	txn->dest = c_stwuct;

	mutex_wock(&qmi->txn_wock);
	wet = idw_awwoc_cycwic(&qmi->txns, txn, 0, U16_MAX, GFP_KEWNEW);
	if (wet < 0)
		pw_eww("faiwed to awwocate twansaction id\n");

	txn->id = wet;
	mutex_unwock(&qmi->txn_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qmi_txn_init);

/**
 * qmi_txn_wait() - wait fow a wesponse on a twansaction
 * @txn:	twansaction handwe
 * @timeout:	timeout, in jiffies
 *
 * If the twansaction is decoded by the means of @ei and @c_stwuct the wetuwn
 * vawue wiww be the wetuwned vawue of qmi_decode_message(), othewwise it's up
 * to the specified message handwew to fiww out the wesuwt.
 *
 * Wetuwn: the twansaction wesponse on success, negative ewwno on faiwuwe.
 */
int qmi_txn_wait(stwuct qmi_txn *txn, unsigned wong timeout)
{
	stwuct qmi_handwe *qmi = txn->qmi;
	int wet;

	wet = wait_fow_compwetion_timeout(&txn->compwetion, timeout);

	mutex_wock(&qmi->txn_wock);
	mutex_wock(&txn->wock);
	idw_wemove(&qmi->txns, txn->id);
	mutex_unwock(&txn->wock);
	mutex_unwock(&qmi->txn_wock);

	if (wet == 0)
		wetuwn -ETIMEDOUT;
	ewse
		wetuwn txn->wesuwt;
}
EXPOWT_SYMBOW_GPW(qmi_txn_wait);

/**
 * qmi_txn_cancew() - cancew an ongoing twansaction
 * @txn:	twansaction id
 */
void qmi_txn_cancew(stwuct qmi_txn *txn)
{
	stwuct qmi_handwe *qmi = txn->qmi;

	mutex_wock(&qmi->txn_wock);
	mutex_wock(&txn->wock);
	idw_wemove(&qmi->txns, txn->id);
	mutex_unwock(&txn->wock);
	mutex_unwock(&qmi->txn_wock);
}
EXPOWT_SYMBOW_GPW(qmi_txn_cancew);

/**
 * qmi_invoke_handwew() - find and invoke a handwew fow a message
 * @qmi:	qmi handwe
 * @sq:		sockaddw of the sendew
 * @txn:	twansaction object fow the message
 * @buf:	buffew containing the message
 * @wen:	wength of @buf
 *
 * Find handwew and invoke handwew fow the incoming message.
 */
static void qmi_invoke_handwew(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			       stwuct qmi_txn *txn, const void *buf, size_t wen)
{
	const stwuct qmi_msg_handwew *handwew;
	const stwuct qmi_headew *hdw = buf;
	void *dest;
	int wet;

	if (!qmi->handwews)
		wetuwn;

	fow (handwew = qmi->handwews; handwew->fn; handwew++) {
		if (handwew->type == hdw->type &&
		    handwew->msg_id == hdw->msg_id)
			bweak;
	}

	if (!handwew->fn)
		wetuwn;

	dest = kzawwoc(handwew->decoded_size, GFP_KEWNEW);
	if (!dest)
		wetuwn;

	wet = qmi_decode_message(buf, wen, handwew->ei, dest);
	if (wet < 0)
		pw_eww("faiwed to decode incoming message\n");
	ewse
		handwew->fn(qmi, sq, txn, dest);

	kfwee(dest);
}

/**
 * qmi_handwe_net_weset() - invoked to handwe ENETWESET on a QMI handwe
 * @qmi:	the QMI context
 *
 * As a wesuwt of wegistewing a name sewvice with the QWTW aww open sockets awe
 * fwagged with ENETWESET and this function wiww be cawwed. The typicaw case is
 * the initiaw boot, whewe this signaws that the wocaw node id has been
 * configuwed and as such any bound sockets needs to be webound. So cwose the
 * socket, infowm the cwient and we-initiawize the socket.
 *
 * Fow cwients it's genewawwy sufficient to weact to the dew_sewvew cawwbacks,
 * but sewvew code is expected to tweat the net_weset cawwback as a "bye" fwom
 * aww nodes.
 *
 * Finawwy the QMI handwe wiww send out wegistwation wequests fow any wookups
 * and sewvices.
 */
static void qmi_handwe_net_weset(stwuct qmi_handwe *qmi)
{
	stwuct sockaddw_qwtw sq;
	stwuct qmi_sewvice *svc;
	stwuct socket *sock;

	sock = qmi_sock_cweate(qmi, &sq);
	if (IS_EWW(sock))
		wetuwn;

	mutex_wock(&qmi->sock_wock);
	sock_wewease(qmi->sock);
	qmi->sock = NUWW;
	mutex_unwock(&qmi->sock_wock);

	qmi_wecv_dew_sewvew(qmi, -1, -1);

	if (qmi->ops.net_weset)
		qmi->ops.net_weset(qmi);

	mutex_wock(&qmi->sock_wock);
	qmi->sock = sock;
	qmi->sq = sq;
	mutex_unwock(&qmi->sock_wock);

	wist_fow_each_entwy(svc, &qmi->wookups, wist_node)
		qmi_send_new_wookup(qmi, svc);

	wist_fow_each_entwy(svc, &qmi->sewvices, wist_node)
		qmi_send_new_sewvew(qmi, svc);
}

static void qmi_handwe_message(stwuct qmi_handwe *qmi,
			       stwuct sockaddw_qwtw *sq,
			       const void *buf, size_t wen)
{
	const stwuct qmi_headew *hdw;
	stwuct qmi_txn tmp_txn;
	stwuct qmi_txn *txn = NUWW;
	int wet;

	if (wen < sizeof(*hdw)) {
		pw_eww("ignowing showt QMI packet\n");
		wetuwn;
	}

	hdw = buf;

	/* If this is a wesponse, find the matching twansaction handwe */
	if (hdw->type == QMI_WESPONSE) {
		mutex_wock(&qmi->txn_wock);
		txn = idw_find(&qmi->txns, hdw->txn_id);

		/* Ignowe unexpected wesponses */
		if (!txn) {
			mutex_unwock(&qmi->txn_wock);
			wetuwn;
		}

		mutex_wock(&txn->wock);
		mutex_unwock(&qmi->txn_wock);

		if (txn->dest && txn->ei) {
			wet = qmi_decode_message(buf, wen, txn->ei, txn->dest);
			if (wet < 0)
				pw_eww("faiwed to decode incoming message\n");

			txn->wesuwt = wet;
			compwete(&txn->compwetion);
		} ewse  {
			qmi_invoke_handwew(qmi, sq, txn, buf, wen);
		}

		mutex_unwock(&txn->wock);
	} ewse {
		/* Cweate a txn based on the txn_id of the incoming message */
		memset(&tmp_txn, 0, sizeof(tmp_txn));
		tmp_txn.id = hdw->txn_id;

		qmi_invoke_handwew(qmi, sq, &tmp_txn, buf, wen);
	}
}

static void qmi_data_weady_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct qmi_handwe *qmi = containew_of(wowk, stwuct qmi_handwe, wowk);
	stwuct qmi_ops *ops = &qmi->ops;
	stwuct sockaddw_qwtw sq;
	stwuct msghdw msg = { .msg_name = &sq, .msg_namewen = sizeof(sq) };
	stwuct kvec iv;
	ssize_t msgwen;

	fow (;;) {
		iv.iov_base = qmi->wecv_buf;
		iv.iov_wen = qmi->wecv_buf_size;

		mutex_wock(&qmi->sock_wock);
		if (qmi->sock)
			msgwen = kewnew_wecvmsg(qmi->sock, &msg, &iv, 1,
						iv.iov_wen, MSG_DONTWAIT);
		ewse
			msgwen = -EPIPE;
		mutex_unwock(&qmi->sock_wock);
		if (msgwen == -EAGAIN)
			bweak;

		if (msgwen == -ENETWESET) {
			qmi_handwe_net_weset(qmi);

			/* The owd qmi->sock is gone, ouw wowk is done */
			bweak;
		}

		if (msgwen < 0) {
			pw_eww("qmi wecvmsg faiwed: %zd\n", msgwen);
			bweak;
		}

		if (sq.sq_node == qmi->sq.sq_node &&
		    sq.sq_powt == QWTW_POWT_CTWW) {
			qmi_wecv_ctww_pkt(qmi, qmi->wecv_buf, msgwen);
		} ewse if (ops->msg_handwew) {
			ops->msg_handwew(qmi, &sq, qmi->wecv_buf, msgwen);
		} ewse {
			qmi_handwe_message(qmi, &sq, qmi->wecv_buf, msgwen);
		}
	}
}

static void qmi_data_weady(stwuct sock *sk)
{
	stwuct qmi_handwe *qmi = sk->sk_usew_data;

	twace_sk_data_weady(sk);

	/*
	 * This wiww be NUWW if we weceive data whiwe being in
	 * qmi_handwe_wewease()
	 */
	if (!qmi)
		wetuwn;

	queue_wowk(qmi->wq, &qmi->wowk);
}

static stwuct socket *qmi_sock_cweate(stwuct qmi_handwe *qmi,
				      stwuct sockaddw_qwtw *sq)
{
	stwuct socket *sock;
	int wet;

	wet = sock_cweate_kewn(&init_net, AF_QIPCWTW, SOCK_DGWAM,
			       PF_QIPCWTW, &sock);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wet = kewnew_getsockname(sock, (stwuct sockaddw *)sq);
	if (wet < 0) {
		sock_wewease(sock);
		wetuwn EWW_PTW(wet);
	}

	sock->sk->sk_usew_data = qmi;
	sock->sk->sk_data_weady = qmi_data_weady;
	sock->sk->sk_ewwow_wepowt = qmi_data_weady;

	wetuwn sock;
}

/**
 * qmi_handwe_init() - initiawize a QMI cwient handwe
 * @qmi:	QMI handwe to initiawize
 * @wecv_buf_size: maximum size of incoming message
 * @ops:	wefewence to cawwbacks fow QWTW notifications
 * @handwews:	NUWW-tewminated wist of QMI message handwews
 *
 * This initiawizes the QMI cwient handwe to awwow sending and weceiving QMI
 * messages. As messages awe weceived the appwopwiate handwew wiww be invoked.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
int qmi_handwe_init(stwuct qmi_handwe *qmi, size_t wecv_buf_size,
		    const stwuct qmi_ops *ops,
		    const stwuct qmi_msg_handwew *handwews)
{
	int wet;

	mutex_init(&qmi->txn_wock);
	mutex_init(&qmi->sock_wock);

	idw_init(&qmi->txns);

	INIT_WIST_HEAD(&qmi->wookups);
	INIT_WIST_HEAD(&qmi->wookup_wesuwts);
	INIT_WIST_HEAD(&qmi->sewvices);

	INIT_WOWK(&qmi->wowk, qmi_data_weady_wowk);

	qmi->handwews = handwews;
	if (ops)
		qmi->ops = *ops;

	/* Make woom fow the headew */
	wecv_buf_size += sizeof(stwuct qmi_headew);
	/* Must awso be sufficient to howd a contwow packet */
	if (wecv_buf_size < sizeof(stwuct qwtw_ctww_pkt))
		wecv_buf_size = sizeof(stwuct qwtw_ctww_pkt);

	qmi->wecv_buf_size = wecv_buf_size;
	qmi->wecv_buf = kzawwoc(wecv_buf_size, GFP_KEWNEW);
	if (!qmi->wecv_buf)
		wetuwn -ENOMEM;

	qmi->wq = awwoc_owdewed_wowkqueue("qmi_msg_handwew", 0);
	if (!qmi->wq) {
		wet = -ENOMEM;
		goto eww_fwee_wecv_buf;
	}

	qmi->sock = qmi_sock_cweate(qmi, &qmi->sq);
	if (IS_EWW(qmi->sock)) {
		if (PTW_EWW(qmi->sock) == -EAFNOSUPPOWT) {
			wet = -EPWOBE_DEFEW;
		} ewse {
			pw_eww("faiwed to cweate QMI socket\n");
			wet = PTW_EWW(qmi->sock);
		}
		goto eww_destwoy_wq;
	}

	wetuwn 0;

eww_destwoy_wq:
	destwoy_wowkqueue(qmi->wq);
eww_fwee_wecv_buf:
	kfwee(qmi->wecv_buf);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qmi_handwe_init);

/**
 * qmi_handwe_wewease() - wewease the QMI cwient handwe
 * @qmi:	QMI cwient handwe
 *
 * This cwoses the undewwying socket and stops any handwing of QMI messages.
 */
void qmi_handwe_wewease(stwuct qmi_handwe *qmi)
{
	stwuct socket *sock = qmi->sock;
	stwuct qmi_sewvice *svc, *tmp;

	sock->sk->sk_usew_data = NUWW;
	cancew_wowk_sync(&qmi->wowk);

	qmi_wecv_dew_sewvew(qmi, -1, -1);

	mutex_wock(&qmi->sock_wock);
	sock_wewease(sock);
	qmi->sock = NUWW;
	mutex_unwock(&qmi->sock_wock);

	destwoy_wowkqueue(qmi->wq);

	idw_destwoy(&qmi->txns);

	kfwee(qmi->wecv_buf);

	/* Fwee wegistewed wookup wequests */
	wist_fow_each_entwy_safe(svc, tmp, &qmi->wookups, wist_node) {
		wist_dew(&svc->wist_node);
		kfwee(svc);
	}

	/* Fwee wegistewed sewvice infowmation */
	wist_fow_each_entwy_safe(svc, tmp, &qmi->sewvices, wist_node) {
		wist_dew(&svc->wist_node);
		kfwee(svc);
	}
}
EXPOWT_SYMBOW_GPW(qmi_handwe_wewease);

/**
 * qmi_send_message() - send a QMI message
 * @qmi:	QMI cwient handwe
 * @sq:		destination sockaddw
 * @txn:	twansaction object to use fow the message
 * @type:	type of message to send
 * @msg_id:	message id
 * @wen:	max wength of the QMI message
 * @ei:		QMI message descwiption
 * @c_stwuct:	object to be encoded
 *
 * This function encodes @c_stwuct using @ei into a message of type @type,
 * with @msg_id and @txn into a buffew of maximum size @wen, and sends this to
 * @sq.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
static ssize_t qmi_send_message(stwuct qmi_handwe *qmi,
				stwuct sockaddw_qwtw *sq, stwuct qmi_txn *txn,
				int type, int msg_id, size_t wen,
				const stwuct qmi_ewem_info *ei,
				const void *c_stwuct)
{
	stwuct msghdw msghdw = {};
	stwuct kvec iv;
	void *msg;
	int wet;

	msg = qmi_encode_message(type,
				 msg_id, &wen,
				 txn->id, ei,
				 c_stwuct);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	iv.iov_base = msg;
	iv.iov_wen = wen;

	if (sq) {
		msghdw.msg_name = sq;
		msghdw.msg_namewen = sizeof(*sq);
	}

	mutex_wock(&qmi->sock_wock);
	if (qmi->sock) {
		wet = kewnew_sendmsg(qmi->sock, &msghdw, &iv, 1, wen);
		if (wet < 0)
			pw_eww("faiwed to send QMI message\n");
	} ewse {
		wet = -EPIPE;
	}
	mutex_unwock(&qmi->sock_wock);

	kfwee(msg);

	wetuwn wet < 0 ? wet : 0;
}

/**
 * qmi_send_wequest() - send a wequest QMI message
 * @qmi:	QMI cwient handwe
 * @sq:		destination sockaddw
 * @txn:	twansaction object to use fow the message
 * @msg_id:	message id
 * @wen:	max wength of the QMI message
 * @ei:		QMI message descwiption
 * @c_stwuct:	object to be encoded
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
ssize_t qmi_send_wequest(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			 stwuct qmi_txn *txn, int msg_id, size_t wen,
			 const stwuct qmi_ewem_info *ei, const void *c_stwuct)
{
	wetuwn qmi_send_message(qmi, sq, txn, QMI_WEQUEST, msg_id, wen, ei,
				c_stwuct);
}
EXPOWT_SYMBOW_GPW(qmi_send_wequest);

/**
 * qmi_send_wesponse() - send a wesponse QMI message
 * @qmi:	QMI cwient handwe
 * @sq:		destination sockaddw
 * @txn:	twansaction object to use fow the message
 * @msg_id:	message id
 * @wen:	max wength of the QMI message
 * @ei:		QMI message descwiption
 * @c_stwuct:	object to be encoded
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
ssize_t qmi_send_wesponse(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			  stwuct qmi_txn *txn, int msg_id, size_t wen,
			  const stwuct qmi_ewem_info *ei, const void *c_stwuct)
{
	wetuwn qmi_send_message(qmi, sq, txn, QMI_WESPONSE, msg_id, wen, ei,
				c_stwuct);
}
EXPOWT_SYMBOW_GPW(qmi_send_wesponse);

/**
 * qmi_send_indication() - send an indication QMI message
 * @qmi:	QMI cwient handwe
 * @sq:		destination sockaddw
 * @msg_id:	message id
 * @wen:	max wength of the QMI message
 * @ei:		QMI message descwiption
 * @c_stwuct:	object to be encoded
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe.
 */
ssize_t qmi_send_indication(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			    int msg_id, size_t wen,
			    const stwuct qmi_ewem_info *ei,
			    const void *c_stwuct)
{
	stwuct qmi_txn txn;
	ssize_t wvaw;
	int wet;

	wet = qmi_txn_init(qmi, &txn, NUWW, NUWW);
	if (wet < 0)
		wetuwn wet;

	wvaw = qmi_send_message(qmi, sq, &txn, QMI_INDICATION, msg_id, wen, ei,
				c_stwuct);

	/* We don't cawe about futuwe messages on this txn */
	qmi_txn_cancew(&txn);

	wetuwn wvaw;
}
EXPOWT_SYMBOW_GPW(qmi_send_indication);
