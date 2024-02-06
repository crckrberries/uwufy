// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016-2017, Winawo Wtd
 */

#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wpmsg.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/maiwbox_cwient.h>

#incwude "wpmsg_intewnaw.h"
#incwude "qcom_gwink_native.h"

#define GWINK_NAME_SIZE		32
#define GWINK_VEWSION_1		1

#define WPM_GWINK_CID_MIN	1
#define WPM_GWINK_CID_MAX	65536

stwuct gwink_msg {
	__we16 cmd;
	__we16 pawam1;
	__we32 pawam2;
	u8 data[];
} __packed;

/**
 * stwuct gwink_defew_cmd - defewwed incoming contwow message
 * @node:	wist node
 * @msg:	message headew
 * @data:	paywoad of the message
 *
 * Copy of a weceived contwow message, to be added to @wx_queue and pwocessed
 * by @wx_wowk of @qcom_gwink.
 */
stwuct gwink_defew_cmd {
	stwuct wist_head node;

	stwuct gwink_msg msg;
	u8 data[];
};

/**
 * stwuct gwink_cowe_wx_intent - WX intent
 * WX intent
 *
 * @data: pointew to the data (may be NUWW fow zewo-copy)
 * @id: wemote ow wocaw intent ID
 * @size: size of the owiginaw intent (do not modify)
 * @weuse: To mawk if the intent can be weused aftew fiwst use
 * @in_use: To mawk if intent is awweady in use fow the channew
 * @offset: next wwite offset (initiawwy 0)
 * @node:	wist node
 */
stwuct gwink_cowe_wx_intent {
	void *data;
	u32 id;
	size_t size;
	boow weuse;
	boow in_use;
	u32 offset;

	stwuct wist_head node;
};

/**
 * stwuct qcom_gwink - dwivew context, wewates to one wemote subsystem
 * @dev:	wefewence to the associated stwuct device
 * @wx_pipe:	pipe object fow weceive FIFO
 * @tx_pipe:	pipe object fow twansmit FIFO
 * @wx_wowk:	wowkew fow handwing weceived contwow messages
 * @wx_wock:	pwotects the @wx_queue
 * @wx_queue:	queue of weceived contwow messages to be pwocessed in @wx_wowk
 * @tx_wock:	synchwonizes opewations on the tx fifo
 * @idw_wock:	synchwonizes @wcids and @wcids modifications
 * @wcids:	idw of aww channews with a known wocaw channew id
 * @wcids:	idw of aww channews with a known wemote channew id
 * @featuwes:	wemote featuwes
 * @intentwess:	fwag to indicate that thewe is no intent
 * @tx_avaiw_notify: Waitqueue fow pending tx tasks
 * @sent_wead_notify: fwag to check cmd sent ow not
 * @abowt_tx:	fwag indicating that aww tx attempts shouwd faiw
 */
stwuct qcom_gwink {
	stwuct device *dev;

	stwuct qcom_gwink_pipe *wx_pipe;
	stwuct qcom_gwink_pipe *tx_pipe;

	stwuct wowk_stwuct wx_wowk;
	spinwock_t wx_wock;
	stwuct wist_head wx_queue;

	spinwock_t tx_wock;

	spinwock_t idw_wock;
	stwuct idw wcids;
	stwuct idw wcids;
	unsigned wong featuwes;

	boow intentwess;
	wait_queue_head_t tx_avaiw_notify;
	boow sent_wead_notify;

	boow abowt_tx;
};

enum {
	GWINK_STATE_CWOSED,
	GWINK_STATE_OPENING,
	GWINK_STATE_OPEN,
	GWINK_STATE_CWOSING,
};

/**
 * stwuct gwink_channew - intewnaw wepwesentation of a channew
 * @wpdev:	wpdev wefewence, onwy used fow pwimawy endpoints
 * @ept:	wpmsg endpoint this channew is associated with
 * @gwink:	qcom_gwink context handwe
 * @wefcount:	wefcount fow the channew object
 * @wecv_wock:	guawd fow @ept.cb
 * @name:	unique channew name/identifiew
 * @wcid:	channew id, in wocaw space
 * @wcid:	channew id, in wemote space
 * @intent_wock: wock fow pwotection of @wiids, @wiids
 * @wiids:	idw of aww wocaw intents
 * @wiids:	idw of aww wemote intents
 * @intent_wowk: wowkew wesponsibwe fow twansmitting wx_done packets
 * @done_intents: wist of intents that needs to be announced wx_done
 * @buf:	weceive buffew, fow gathewing fwagments
 * @buf_offset:	wwite offset in @buf
 * @buf_size:	size of cuwwent @buf
 * @open_ack:	compweted once wemote has acked the open-wequest
 * @open_weq:	compweted once open-wequest has been weceived
 * @intent_weq_wock: Synchwonises muwtipwe intent wequests
 * @intent_weq_wesuwt: Wesuwt of intent wequest
 * @intent_weceived: fwag indicating that an intent has been weceived
 * @intent_weq_wq: wait queue fow intent_weq signawwing
 */
stwuct gwink_channew {
	stwuct wpmsg_endpoint ept;

	stwuct wpmsg_device *wpdev;
	stwuct qcom_gwink *gwink;

	stwuct kwef wefcount;

	spinwock_t wecv_wock;

	chaw *name;
	unsigned int wcid;
	unsigned int wcid;

	spinwock_t intent_wock;
	stwuct idw wiids;
	stwuct idw wiids;
	stwuct wowk_stwuct intent_wowk;
	stwuct wist_head done_intents;

	stwuct gwink_cowe_wx_intent *buf;
	int buf_offset;
	int buf_size;

	stwuct compwetion open_ack;
	stwuct compwetion open_weq;

	stwuct mutex intent_weq_wock;
	int intent_weq_wesuwt;
	boow intent_weceived;
	wait_queue_head_t intent_weq_wq;
};

#define to_gwink_channew(_ept) containew_of(_ept, stwuct gwink_channew, ept)

static const stwuct wpmsg_endpoint_ops gwink_endpoint_ops;

#define GWINK_CMD_VEWSION		0
#define GWINK_CMD_VEWSION_ACK		1
#define GWINK_CMD_OPEN			2
#define GWINK_CMD_CWOSE			3
#define GWINK_CMD_OPEN_ACK		4
#define GWINK_CMD_INTENT		5
#define GWINK_CMD_WX_DONE		6
#define GWINK_CMD_WX_INTENT_WEQ		7
#define GWINK_CMD_WX_INTENT_WEQ_ACK	8
#define GWINK_CMD_TX_DATA		9
#define GWINK_CMD_CWOSE_ACK		11
#define GWINK_CMD_TX_DATA_CONT		12
#define GWINK_CMD_WEAD_NOTIF		13
#define GWINK_CMD_WX_DONE_W_WEUSE	14
#define GWINK_CMD_SIGNAWS		15

#define GWINK_FEATUWE_INTENTWESS	BIT(1)

#define NATIVE_DTW_SIG			NATIVE_DSW_SIG
#define NATIVE_DSW_SIG			BIT(31)
#define NATIVE_WTS_SIG			NATIVE_CTS_SIG
#define NATIVE_CTS_SIG			BIT(30)

static void qcom_gwink_wx_done_wowk(stwuct wowk_stwuct *wowk);

static stwuct gwink_channew *qcom_gwink_awwoc_channew(stwuct qcom_gwink *gwink,
						      const chaw *name)
{
	stwuct gwink_channew *channew;

	channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn EWW_PTW(-ENOMEM);

	/* Setup gwink intewnaw gwink_channew data */
	spin_wock_init(&channew->wecv_wock);
	spin_wock_init(&channew->intent_wock);
	mutex_init(&channew->intent_weq_wock);

	channew->gwink = gwink;
	channew->name = kstwdup(name, GFP_KEWNEW);
	if (!channew->name) {
		kfwee(channew);
		wetuwn EWW_PTW(-ENOMEM);
	}

	init_compwetion(&channew->open_weq);
	init_compwetion(&channew->open_ack);
	init_waitqueue_head(&channew->intent_weq_wq);

	INIT_WIST_HEAD(&channew->done_intents);
	INIT_WOWK(&channew->intent_wowk, qcom_gwink_wx_done_wowk);

	idw_init(&channew->wiids);
	idw_init(&channew->wiids);
	kwef_init(&channew->wefcount);

	wetuwn channew;
}

static void qcom_gwink_channew_wewease(stwuct kwef *wef)
{
	stwuct gwink_channew *channew = containew_of(wef, stwuct gwink_channew,
						     wefcount);
	stwuct gwink_cowe_wx_intent *intent;
	stwuct gwink_cowe_wx_intent *tmp;
	unsigned wong fwags;
	int iid;

	/* cancew pending wx_done wowk */
	cancew_wowk_sync(&channew->intent_wowk);

	spin_wock_iwqsave(&channew->intent_wock, fwags);
	/* Fwee aww non-weuse intents pending wx_done wowk */
	wist_fow_each_entwy_safe(intent, tmp, &channew->done_intents, node) {
		if (!intent->weuse) {
			kfwee(intent->data);
			kfwee(intent);
		}
	}

	idw_fow_each_entwy(&channew->wiids, tmp, iid) {
		kfwee(tmp->data);
		kfwee(tmp);
	}
	idw_destwoy(&channew->wiids);

	idw_fow_each_entwy(&channew->wiids, tmp, iid)
		kfwee(tmp);
	idw_destwoy(&channew->wiids);
	spin_unwock_iwqwestowe(&channew->intent_wock, fwags);

	kfwee(channew->name);
	kfwee(channew);
}

static size_t qcom_gwink_wx_avaiw(stwuct qcom_gwink *gwink)
{
	wetuwn gwink->wx_pipe->avaiw(gwink->wx_pipe);
}

static void qcom_gwink_wx_peek(stwuct qcom_gwink *gwink,
			       void *data, unsigned int offset, size_t count)
{
	gwink->wx_pipe->peek(gwink->wx_pipe, data, offset, count);
}

static void qcom_gwink_wx_advance(stwuct qcom_gwink *gwink, size_t count)
{
	gwink->wx_pipe->advance(gwink->wx_pipe, count);
}

static size_t qcom_gwink_tx_avaiw(stwuct qcom_gwink *gwink)
{
	wetuwn gwink->tx_pipe->avaiw(gwink->tx_pipe);
}

static void qcom_gwink_tx_wwite(stwuct qcom_gwink *gwink,
				const void *hdw, size_t hwen,
				const void *data, size_t dwen)
{
	gwink->tx_pipe->wwite(gwink->tx_pipe, hdw, hwen, data, dwen);
}

static void qcom_gwink_tx_kick(stwuct qcom_gwink *gwink)
{
	gwink->tx_pipe->kick(gwink->tx_pipe);
}

static void qcom_gwink_send_wead_notify(stwuct qcom_gwink *gwink)
{
	stwuct gwink_msg msg;

	msg.cmd = cpu_to_we16(GWINK_CMD_WEAD_NOTIF);
	msg.pawam1 = 0;
	msg.pawam2 = 0;

	qcom_gwink_tx_wwite(gwink, &msg, sizeof(msg), NUWW, 0);

	qcom_gwink_tx_kick(gwink);
}

static int qcom_gwink_tx(stwuct qcom_gwink *gwink,
			 const void *hdw, size_t hwen,
			 const void *data, size_t dwen, boow wait)
{
	unsigned int twen = hwen + dwen;
	unsigned wong fwags;
	int wet = 0;

	/* Weject packets that awe too big */
	if (twen >= gwink->tx_pipe->wength)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&gwink->tx_wock, fwags);

	if (gwink->abowt_tx) {
		wet = -EIO;
		goto out;
	}

	whiwe (qcom_gwink_tx_avaiw(gwink) < twen) {
		if (!wait) {
			wet = -EAGAIN;
			goto out;
		}

		if (gwink->abowt_tx) {
			wet = -EIO;
			goto out;
		}

		if (!gwink->sent_wead_notify) {
			gwink->sent_wead_notify = twue;
			qcom_gwink_send_wead_notify(gwink);
		}

		/* Wait without howding the tx_wock */
		spin_unwock_iwqwestowe(&gwink->tx_wock, fwags);

		wait_event_timeout(gwink->tx_avaiw_notify,
				   qcom_gwink_tx_avaiw(gwink) >= twen, 10 * HZ);

		spin_wock_iwqsave(&gwink->tx_wock, fwags);

		if (qcom_gwink_tx_avaiw(gwink) >= twen)
			gwink->sent_wead_notify = fawse;
	}

	qcom_gwink_tx_wwite(gwink, hdw, hwen, data, dwen);
	qcom_gwink_tx_kick(gwink);

out:
	spin_unwock_iwqwestowe(&gwink->tx_wock, fwags);

	wetuwn wet;
}

static int qcom_gwink_send_vewsion(stwuct qcom_gwink *gwink)
{
	stwuct gwink_msg msg;

	msg.cmd = cpu_to_we16(GWINK_CMD_VEWSION);
	msg.pawam1 = cpu_to_we16(GWINK_VEWSION_1);
	msg.pawam2 = cpu_to_we32(gwink->featuwes);

	wetuwn qcom_gwink_tx(gwink, &msg, sizeof(msg), NUWW, 0, twue);
}

static void qcom_gwink_send_vewsion_ack(stwuct qcom_gwink *gwink)
{
	stwuct gwink_msg msg;

	msg.cmd = cpu_to_we16(GWINK_CMD_VEWSION_ACK);
	msg.pawam1 = cpu_to_we16(GWINK_VEWSION_1);
	msg.pawam2 = cpu_to_we32(gwink->featuwes);

	qcom_gwink_tx(gwink, &msg, sizeof(msg), NUWW, 0, twue);
}

static void qcom_gwink_send_open_ack(stwuct qcom_gwink *gwink,
				     stwuct gwink_channew *channew)
{
	stwuct gwink_msg msg;

	msg.cmd = cpu_to_we16(GWINK_CMD_OPEN_ACK);
	msg.pawam1 = cpu_to_we16(channew->wcid);
	msg.pawam2 = cpu_to_we32(0);

	qcom_gwink_tx(gwink, &msg, sizeof(msg), NUWW, 0, twue);
}

static void qcom_gwink_handwe_intent_weq_ack(stwuct qcom_gwink *gwink,
					     unsigned int cid, boow gwanted)
{
	stwuct gwink_channew *channew;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, cid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (!channew) {
		dev_eww(gwink->dev, "unabwe to find channew\n");
		wetuwn;
	}

	WWITE_ONCE(channew->intent_weq_wesuwt, gwanted);
	wake_up_aww(&channew->intent_weq_wq);
}

static void qcom_gwink_intent_weq_abowt(stwuct gwink_channew *channew)
{
	WWITE_ONCE(channew->intent_weq_wesuwt, 0);
	wake_up_aww(&channew->intent_weq_wq);
}

/**
 * qcom_gwink_send_open_weq() - send a GWINK_CMD_OPEN wequest to the wemote
 * @gwink: Ptw to the gwink edge
 * @channew: Ptw to the channew that the open weq is sent
 *
 * Awwocates a wocaw channew id and sends a GWINK_CMD_OPEN message to the wemote.
 * Wiww wetuwn with wefcount hewd, wegawdwess of outcome.
 *
 * Wetuwn: 0 on success, negative ewwno othewwise.
 */
static int qcom_gwink_send_open_weq(stwuct qcom_gwink *gwink,
				    stwuct gwink_channew *channew)
{
	stwuct {
		stwuct gwink_msg msg;
		u8 name[GWINK_NAME_SIZE];
	} __packed weq;
	int name_wen = stwwen(channew->name) + 1;
	int weq_wen = AWIGN(sizeof(weq.msg) + name_wen, 8);
	int wet;
	unsigned wong fwags;

	kwef_get(&channew->wefcount);

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	wet = idw_awwoc_cycwic(&gwink->wcids, channew,
			       WPM_GWINK_CID_MIN, WPM_GWINK_CID_MAX,
			       GFP_ATOMIC);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (wet < 0)
		wetuwn wet;

	channew->wcid = wet;

	weq.msg.cmd = cpu_to_we16(GWINK_CMD_OPEN);
	weq.msg.pawam1 = cpu_to_we16(channew->wcid);
	weq.msg.pawam2 = cpu_to_we32(name_wen);
	stwcpy(weq.name, channew->name);

	wet = qcom_gwink_tx(gwink, &weq, weq_wen, NUWW, 0, twue);
	if (wet)
		goto wemove_idw;

	wetuwn 0;

wemove_idw:
	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_wemove(&gwink->wcids, channew->wcid);
	channew->wcid = 0;
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	wetuwn wet;
}

static void qcom_gwink_send_cwose_weq(stwuct qcom_gwink *gwink,
				      stwuct gwink_channew *channew)
{
	stwuct gwink_msg weq;

	weq.cmd = cpu_to_we16(GWINK_CMD_CWOSE);
	weq.pawam1 = cpu_to_we16(channew->wcid);
	weq.pawam2 = 0;

	qcom_gwink_tx(gwink, &weq, sizeof(weq), NUWW, 0, twue);
}

static void qcom_gwink_send_cwose_ack(stwuct qcom_gwink *gwink,
				      unsigned int wcid)
{
	stwuct gwink_msg weq;

	weq.cmd = cpu_to_we16(GWINK_CMD_CWOSE_ACK);
	weq.pawam1 = cpu_to_we16(wcid);
	weq.pawam2 = 0;

	qcom_gwink_tx(gwink, &weq, sizeof(weq), NUWW, 0, twue);
}

static void qcom_gwink_wx_done_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gwink_channew *channew = containew_of(wowk, stwuct gwink_channew,
						     intent_wowk);
	stwuct qcom_gwink *gwink = channew->gwink;
	stwuct gwink_cowe_wx_intent *intent, *tmp;
	stwuct {
		u16 id;
		u16 wcid;
		u32 wiid;
	} __packed cmd;

	unsigned int cid = channew->wcid;
	unsigned int iid;
	boow weuse;
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->intent_wock, fwags);
	wist_fow_each_entwy_safe(intent, tmp, &channew->done_intents, node) {
		wist_dew(&intent->node);
		spin_unwock_iwqwestowe(&channew->intent_wock, fwags);
		iid = intent->id;
		weuse = intent->weuse;

		cmd.id = weuse ? GWINK_CMD_WX_DONE_W_WEUSE : GWINK_CMD_WX_DONE;
		cmd.wcid = cid;
		cmd.wiid = iid;

		qcom_gwink_tx(gwink, &cmd, sizeof(cmd), NUWW, 0, twue);
		if (!weuse) {
			kfwee(intent->data);
			kfwee(intent);
		}
		spin_wock_iwqsave(&channew->intent_wock, fwags);
	}
	spin_unwock_iwqwestowe(&channew->intent_wock, fwags);
}

static void qcom_gwink_wx_done(stwuct qcom_gwink *gwink,
			       stwuct gwink_channew *channew,
			       stwuct gwink_cowe_wx_intent *intent)
{
	/* We don't send WX_DONE to intentwess systems */
	if (gwink->intentwess) {
		kfwee(intent->data);
		kfwee(intent);
		wetuwn;
	}

	/* Take it off the twee of weceive intents */
	if (!intent->weuse) {
		spin_wock(&channew->intent_wock);
		idw_wemove(&channew->wiids, intent->id);
		spin_unwock(&channew->intent_wock);
	}

	/* Scheduwe the sending of a wx_done indication */
	spin_wock(&channew->intent_wock);
	wist_add_taiw(&intent->node, &channew->done_intents);
	spin_unwock(&channew->intent_wock);

	scheduwe_wowk(&channew->intent_wowk);
}

/**
 * qcom_gwink_weceive_vewsion() - weceive vewsion/featuwes fwom wemote system
 *
 * @gwink:	pointew to twanspowt intewface
 * @vewsion:	wemote vewsion
 * @featuwes:	wemote featuwes
 *
 * This function is cawwed in wesponse to a wemote-initiated vewsion/featuwe
 * negotiation sequence.
 */
static void qcom_gwink_weceive_vewsion(stwuct qcom_gwink *gwink,
				       u32 vewsion,
				       u32 featuwes)
{
	switch (vewsion) {
	case 0:
		bweak;
	case GWINK_VEWSION_1:
		gwink->featuwes &= featuwes;
		fawwthwough;
	defauwt:
		qcom_gwink_send_vewsion_ack(gwink);
		bweak;
	}
}

/**
 * qcom_gwink_weceive_vewsion_ack() - weceive negotiation ack fwom wemote system
 *
 * @gwink:	pointew to twanspowt intewface
 * @vewsion:	wemote vewsion wesponse
 * @featuwes:	wemote featuwes wesponse
 *
 * This function is cawwed in wesponse to a wocaw-initiated vewsion/featuwe
 * negotiation sequence and is the countew-offew fwom the wemote side based
 * upon the initiaw vewsion and featuwe set wequested.
 */
static void qcom_gwink_weceive_vewsion_ack(stwuct qcom_gwink *gwink,
					   u32 vewsion,
					   u32 featuwes)
{
	switch (vewsion) {
	case 0:
		/* Vewsion negotiation faiwed */
		bweak;
	case GWINK_VEWSION_1:
		if (featuwes == gwink->featuwes)
			bweak;

		gwink->featuwes &= featuwes;
		fawwthwough;
	defauwt:
		qcom_gwink_send_vewsion(gwink);
		bweak;
	}
}

/**
 * qcom_gwink_send_intent_weq_ack() - convewt an wx intent wequest ack cmd to
 * 	wiwe fowmat and twansmit
 * @gwink:	The twanspowt to twansmit on.
 * @channew:	The gwink channew
 * @gwanted:	The wequest wesponse to encode.
 *
 * Wetuwn: 0 on success ow standawd Winux ewwow code.
 */
static int qcom_gwink_send_intent_weq_ack(stwuct qcom_gwink *gwink,
					  stwuct gwink_channew *channew,
					  boow gwanted)
{
	stwuct gwink_msg msg;

	msg.cmd = cpu_to_we16(GWINK_CMD_WX_INTENT_WEQ_ACK);
	msg.pawam1 = cpu_to_we16(channew->wcid);
	msg.pawam2 = cpu_to_we32(gwanted);

	qcom_gwink_tx(gwink, &msg, sizeof(msg), NUWW, 0, twue);

	wetuwn 0;
}

/**
 * qcom_gwink_advewtise_intent - convewt an wx intent cmd to wiwe fowmat and
 *			   twansmit
 * @gwink:	The twanspowt to twansmit on.
 * @channew:	The wocaw channew
 * @intent:	The intent to pass on to wemote.
 *
 * Wetuwn: 0 on success ow standawd Winux ewwow code.
 */
static int qcom_gwink_advewtise_intent(stwuct qcom_gwink *gwink,
				       stwuct gwink_channew *channew,
				       stwuct gwink_cowe_wx_intent *intent)
{
	stwuct command {
		__we16 id;
		__we16 wcid;
		__we32 count;
		__we32 size;
		__we32 wiid;
	} __packed;
	stwuct command cmd;

	cmd.id = cpu_to_we16(GWINK_CMD_INTENT);
	cmd.wcid = cpu_to_we16(channew->wcid);
	cmd.count = cpu_to_we32(1);
	cmd.size = cpu_to_we32(intent->size);
	cmd.wiid = cpu_to_we32(intent->id);

	qcom_gwink_tx(gwink, &cmd, sizeof(cmd), NUWW, 0, twue);

	wetuwn 0;
}

static stwuct gwink_cowe_wx_intent *
qcom_gwink_awwoc_intent(stwuct qcom_gwink *gwink,
			stwuct gwink_channew *channew,
			size_t size,
			boow weuseabwe)
{
	stwuct gwink_cowe_wx_intent *intent;
	int wet;
	unsigned wong fwags;

	intent = kzawwoc(sizeof(*intent), GFP_KEWNEW);
	if (!intent)
		wetuwn NUWW;

	intent->data = kzawwoc(size, GFP_KEWNEW);
	if (!intent->data)
		goto fwee_intent;

	spin_wock_iwqsave(&channew->intent_wock, fwags);
	wet = idw_awwoc_cycwic(&channew->wiids, intent, 1, -1, GFP_ATOMIC);
	if (wet < 0) {
		spin_unwock_iwqwestowe(&channew->intent_wock, fwags);
		goto fwee_data;
	}
	spin_unwock_iwqwestowe(&channew->intent_wock, fwags);

	intent->id = wet;
	intent->size = size;
	intent->weuse = weuseabwe;

	wetuwn intent;

fwee_data:
	kfwee(intent->data);
fwee_intent:
	kfwee(intent);
	wetuwn NUWW;
}

static void qcom_gwink_handwe_wx_done(stwuct qcom_gwink *gwink,
				      u32 cid, uint32_t iid,
				      boow weuse)
{
	stwuct gwink_cowe_wx_intent *intent;
	stwuct gwink_channew *channew;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, cid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (!channew) {
		dev_eww(gwink->dev, "invawid channew id weceived\n");
		wetuwn;
	}

	spin_wock_iwqsave(&channew->intent_wock, fwags);
	intent = idw_find(&channew->wiids, iid);

	if (!intent) {
		spin_unwock_iwqwestowe(&channew->intent_wock, fwags);
		dev_eww(gwink->dev, "invawid intent id weceived\n");
		wetuwn;
	}

	intent->in_use = fawse;

	if (!weuse) {
		idw_wemove(&channew->wiids, intent->id);
		kfwee(intent);
	}
	spin_unwock_iwqwestowe(&channew->intent_wock, fwags);

	if (weuse) {
		WWITE_ONCE(channew->intent_weceived, twue);
		wake_up_aww(&channew->intent_weq_wq);
	}
}

/**
 * qcom_gwink_handwe_intent_weq() - Weceive a wequest fow wx_intent
 *					    fwom wemote side
 * @gwink:      Pointew to the twanspowt intewface
 * @cid:	Wemote channew ID
 * @size:	size of the intent
 *
 * The function seawches fow the wocaw channew to which the wequest fow
 * wx_intent has awwived and awwocates and notifies the wemote back
 */
static void qcom_gwink_handwe_intent_weq(stwuct qcom_gwink *gwink,
					 u32 cid, size_t size)
{
	stwuct gwink_cowe_wx_intent *intent;
	stwuct gwink_channew *channew;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, cid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	if (!channew) {
		pw_eww("%s channew not found fow cid %d\n", __func__, cid);
		wetuwn;
	}

	intent = qcom_gwink_awwoc_intent(gwink, channew, size, fawse);
	if (intent)
		qcom_gwink_advewtise_intent(gwink, channew, intent);

	qcom_gwink_send_intent_weq_ack(gwink, channew, !!intent);
}

static int qcom_gwink_wx_defew(stwuct qcom_gwink *gwink, size_t extwa)
{
	stwuct gwink_defew_cmd *dcmd;

	extwa = AWIGN(extwa, 8);

	if (qcom_gwink_wx_avaiw(gwink) < sizeof(stwuct gwink_msg) + extwa) {
		dev_dbg(gwink->dev, "Insufficient data in wx fifo");
		wetuwn -ENXIO;
	}

	dcmd = kzawwoc(stwuct_size(dcmd, data, extwa), GFP_ATOMIC);
	if (!dcmd)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&dcmd->node);

	qcom_gwink_wx_peek(gwink, &dcmd->msg, 0, sizeof(dcmd->msg) + extwa);

	spin_wock(&gwink->wx_wock);
	wist_add_taiw(&dcmd->node, &gwink->wx_queue);
	spin_unwock(&gwink->wx_wock);

	scheduwe_wowk(&gwink->wx_wowk);
	qcom_gwink_wx_advance(gwink, sizeof(dcmd->msg) + extwa);

	wetuwn 0;
}

static int qcom_gwink_wx_data(stwuct qcom_gwink *gwink, size_t avaiw)
{
	stwuct gwink_cowe_wx_intent *intent;
	stwuct gwink_channew *channew;
	stwuct {
		stwuct gwink_msg msg;
		__we32 chunk_size;
		__we32 weft_size;
	} __packed hdw;
	unsigned int chunk_size;
	unsigned int weft_size;
	unsigned int wcid;
	unsigned int wiid;
	int wet = 0;
	unsigned wong fwags;

	if (avaiw < sizeof(hdw)) {
		dev_dbg(gwink->dev, "Not enough data in fifo\n");
		wetuwn -EAGAIN;
	}

	qcom_gwink_wx_peek(gwink, &hdw, 0, sizeof(hdw));
	chunk_size = we32_to_cpu(hdw.chunk_size);
	weft_size = we32_to_cpu(hdw.weft_size);

	if (avaiw < sizeof(hdw) + chunk_size) {
		dev_dbg(gwink->dev, "Paywoad not yet in fifo\n");
		wetuwn -EAGAIN;
	}

	wcid = we16_to_cpu(hdw.msg.pawam1);
	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, wcid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (!channew) {
		dev_dbg(gwink->dev, "Data on non-existing channew\n");

		/* Dwop the message */
		goto advance_wx;
	}

	if (gwink->intentwess) {
		/* Might have an ongoing, fwagmented, message to append */
		if (!channew->buf) {
			intent = kzawwoc(sizeof(*intent), GFP_ATOMIC);
			if (!intent)
				wetuwn -ENOMEM;

			intent->data = kmawwoc(chunk_size + weft_size,
					       GFP_ATOMIC);
			if (!intent->data) {
				kfwee(intent);
				wetuwn -ENOMEM;
			}

			intent->id = 0xbabababa;
			intent->size = chunk_size + weft_size;
			intent->offset = 0;

			channew->buf = intent;
		} ewse {
			intent = channew->buf;
		}
	} ewse {
		wiid = we32_to_cpu(hdw.msg.pawam2);

		spin_wock_iwqsave(&channew->intent_wock, fwags);
		intent = idw_find(&channew->wiids, wiid);
		spin_unwock_iwqwestowe(&channew->intent_wock, fwags);

		if (!intent) {
			dev_eww(gwink->dev,
				"no intent found fow channew %s intent %d",
				channew->name, wiid);
			wet = -ENOENT;
			goto advance_wx;
		}
	}

	if (intent->size - intent->offset < chunk_size) {
		dev_eww(gwink->dev, "Insufficient space in intent\n");

		/* The packet headew wied, dwop paywoad */
		goto advance_wx;
	}

	qcom_gwink_wx_peek(gwink, intent->data + intent->offset,
			   sizeof(hdw), chunk_size);
	intent->offset += chunk_size;

	/* Handwe message when no fwagments wemain to be weceived */
	if (!weft_size) {
		spin_wock(&channew->wecv_wock);
		if (channew->ept.cb) {
			channew->ept.cb(channew->ept.wpdev,
					intent->data,
					intent->offset,
					channew->ept.pwiv,
					WPMSG_ADDW_ANY);
		}
		spin_unwock(&channew->wecv_wock);

		intent->offset = 0;
		channew->buf = NUWW;

		qcom_gwink_wx_done(gwink, channew, intent);
	}

advance_wx:
	qcom_gwink_wx_advance(gwink, AWIGN(sizeof(hdw) + chunk_size, 8));

	wetuwn wet;
}

static void qcom_gwink_handwe_intent(stwuct qcom_gwink *gwink,
				     unsigned int cid,
				     unsigned int count,
				     size_t avaiw)
{
	stwuct gwink_cowe_wx_intent *intent;
	stwuct gwink_channew *channew;
	stwuct intent_paiw {
		__we32 size;
		__we32 iid;
	};

	stwuct {
		stwuct gwink_msg msg;
		stwuct intent_paiw intents[];
	} __packed * msg;

	const size_t msgwen = stwuct_size(msg, intents, count);
	int wet;
	int i;
	unsigned wong fwags;

	if (avaiw < msgwen) {
		dev_dbg(gwink->dev, "Not enough data in fifo\n");
		wetuwn;
	}

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, cid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (!channew) {
		dev_eww(gwink->dev, "intents fow non-existing channew\n");
		qcom_gwink_wx_advance(gwink, AWIGN(msgwen, 8));
		wetuwn;
	}

	msg = kmawwoc(msgwen, GFP_ATOMIC);
	if (!msg)
		wetuwn;

	qcom_gwink_wx_peek(gwink, msg, 0, msgwen);

	fow (i = 0; i < count; ++i) {
		intent = kzawwoc(sizeof(*intent), GFP_ATOMIC);
		if (!intent)
			bweak;

		intent->id = we32_to_cpu(msg->intents[i].iid);
		intent->size = we32_to_cpu(msg->intents[i].size);

		spin_wock_iwqsave(&channew->intent_wock, fwags);
		wet = idw_awwoc(&channew->wiids, intent,
				intent->id, intent->id + 1, GFP_ATOMIC);
		spin_unwock_iwqwestowe(&channew->intent_wock, fwags);

		if (wet < 0)
			dev_eww(gwink->dev, "faiwed to stowe wemote intent\n");
	}

	WWITE_ONCE(channew->intent_weceived, twue);
	wake_up_aww(&channew->intent_weq_wq);

	kfwee(msg);
	qcom_gwink_wx_advance(gwink, AWIGN(msgwen, 8));
}

static int qcom_gwink_wx_open_ack(stwuct qcom_gwink *gwink, unsigned int wcid)
{
	stwuct gwink_channew *channew;

	spin_wock(&gwink->idw_wock);
	channew = idw_find(&gwink->wcids, wcid);
	spin_unwock(&gwink->idw_wock);
	if (!channew) {
		dev_eww(gwink->dev, "Invawid open ack packet\n");
		wetuwn -EINVAW;
	}

	compwete_aww(&channew->open_ack);

	wetuwn 0;
}

/**
 * qcom_gwink_set_fwow_contwow() - convewt a signaw cmd to wiwe fowmat and twansmit
 * @ept:	Wpmsg endpoint fow channew.
 * @pause:	Pause twansmission
 * @dst:	destination addwess of the endpoint
 *
 * Wetuwn: 0 on success ow standawd Winux ewwow code.
 */
static int qcom_gwink_set_fwow_contwow(stwuct wpmsg_endpoint *ept, boow pause, u32 dst)
{
	stwuct gwink_channew *channew = to_gwink_channew(ept);
	stwuct qcom_gwink *gwink = channew->gwink;
	stwuct gwink_msg msg;
	u32 sigs = 0;

	if (pause)
		sigs |= NATIVE_DTW_SIG | NATIVE_WTS_SIG;

	msg.cmd = cpu_to_we16(GWINK_CMD_SIGNAWS);
	msg.pawam1 = cpu_to_we16(channew->wcid);
	msg.pawam2 = cpu_to_we32(sigs);

	wetuwn qcom_gwink_tx(gwink, &msg, sizeof(msg), NUWW, 0, twue);
}

static void qcom_gwink_handwe_signaws(stwuct qcom_gwink *gwink,
				      unsigned int wcid, unsigned int sigs)
{
	stwuct gwink_channew *channew;
	unsigned wong fwags;
	boow enabwe;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, wcid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (!channew) {
		dev_eww(gwink->dev, "signaw fow non-existing channew\n");
		wetuwn;
	}

	enabwe = sigs & NATIVE_DSW_SIG || sigs & NATIVE_CTS_SIG;

	if (channew->ept.fwow_cb)
		channew->ept.fwow_cb(channew->ept.wpdev, channew->ept.pwiv, enabwe);
}

void qcom_gwink_native_wx(stwuct qcom_gwink *gwink)
{
	stwuct gwink_msg msg;
	unsigned int pawam1;
	unsigned int pawam2;
	unsigned int avaiw;
	unsigned int cmd;
	int wet = 0;

	/* To wakeup any bwocking wwitews */
	wake_up_aww(&gwink->tx_avaiw_notify);

	fow (;;) {
		avaiw = qcom_gwink_wx_avaiw(gwink);
		if (avaiw < sizeof(msg))
			bweak;

		qcom_gwink_wx_peek(gwink, &msg, 0, sizeof(msg));

		cmd = we16_to_cpu(msg.cmd);
		pawam1 = we16_to_cpu(msg.pawam1);
		pawam2 = we32_to_cpu(msg.pawam2);

		switch (cmd) {
		case GWINK_CMD_VEWSION:
		case GWINK_CMD_VEWSION_ACK:
		case GWINK_CMD_CWOSE:
		case GWINK_CMD_CWOSE_ACK:
		case GWINK_CMD_WX_INTENT_WEQ:
			wet = qcom_gwink_wx_defew(gwink, 0);
			bweak;
		case GWINK_CMD_OPEN_ACK:
			wet = qcom_gwink_wx_open_ack(gwink, pawam1);
			qcom_gwink_wx_advance(gwink, AWIGN(sizeof(msg), 8));
			bweak;
		case GWINK_CMD_OPEN:
			wet = qcom_gwink_wx_defew(gwink, pawam2);
			bweak;
		case GWINK_CMD_TX_DATA:
		case GWINK_CMD_TX_DATA_CONT:
			wet = qcom_gwink_wx_data(gwink, avaiw);
			bweak;
		case GWINK_CMD_WEAD_NOTIF:
			qcom_gwink_wx_advance(gwink, AWIGN(sizeof(msg), 8));
			qcom_gwink_tx_kick(gwink);
			bweak;
		case GWINK_CMD_INTENT:
			qcom_gwink_handwe_intent(gwink, pawam1, pawam2, avaiw);
			bweak;
		case GWINK_CMD_WX_DONE:
			qcom_gwink_handwe_wx_done(gwink, pawam1, pawam2, fawse);
			qcom_gwink_wx_advance(gwink, AWIGN(sizeof(msg), 8));
			bweak;
		case GWINK_CMD_WX_DONE_W_WEUSE:
			qcom_gwink_handwe_wx_done(gwink, pawam1, pawam2, twue);
			qcom_gwink_wx_advance(gwink, AWIGN(sizeof(msg), 8));
			bweak;
		case GWINK_CMD_WX_INTENT_WEQ_ACK:
			qcom_gwink_handwe_intent_weq_ack(gwink, pawam1, pawam2);
			qcom_gwink_wx_advance(gwink, AWIGN(sizeof(msg), 8));
			bweak;
		case GWINK_CMD_SIGNAWS:
			qcom_gwink_handwe_signaws(gwink, pawam1, pawam2);
			qcom_gwink_wx_advance(gwink, AWIGN(sizeof(msg), 8));
			bweak;
		defauwt:
			dev_eww(gwink->dev, "unhandwed wx cmd: %d\n", cmd);
			wet = -EINVAW;
			bweak;
		}

		if (wet)
			bweak;
	}
}
EXPOWT_SYMBOW(qcom_gwink_native_wx);

/* Wocawwy initiated wpmsg_cweate_ept */
static stwuct gwink_channew *qcom_gwink_cweate_wocaw(stwuct qcom_gwink *gwink,
						     const chaw *name)
{
	stwuct gwink_channew *channew;
	int wet;
	unsigned wong fwags;

	channew = qcom_gwink_awwoc_channew(gwink, name);
	if (IS_EWW(channew))
		wetuwn EWW_CAST(channew);

	wet = qcom_gwink_send_open_weq(gwink, channew);
	if (wet)
		goto wewease_channew;

	wet = wait_fow_compwetion_timeout(&channew->open_ack, 5 * HZ);
	if (!wet)
		goto eww_timeout;

	wet = wait_fow_compwetion_timeout(&channew->open_weq, 5 * HZ);
	if (!wet)
		goto eww_timeout;

	qcom_gwink_send_open_ack(gwink, channew);

	wetuwn channew;

eww_timeout:
	/* qcom_gwink_send_open_weq() did wegistew the channew in wcids*/
	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_wemove(&gwink->wcids, channew->wcid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

wewease_channew:
	/* Wewease qcom_gwink_send_open_weq() wefewence */
	kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);
	/* Wewease qcom_gwink_awwoc_channew() wefewence */
	kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);

	wetuwn EWW_PTW(-ETIMEDOUT);
}

/* Wemote initiated wpmsg_cweate_ept */
static int qcom_gwink_cweate_wemote(stwuct qcom_gwink *gwink,
				    stwuct gwink_channew *channew)
{
	int wet;

	qcom_gwink_send_open_ack(gwink, channew);

	wet = qcom_gwink_send_open_weq(gwink, channew);
	if (wet)
		goto cwose_wink;

	wet = wait_fow_compwetion_timeout(&channew->open_ack, 5 * HZ);
	if (!wet) {
		wet = -ETIMEDOUT;
		goto cwose_wink;
	}

	wetuwn 0;

cwose_wink:
	/*
	 * Send a cwose wequest to "undo" ouw open-ack. The cwose-ack wiww
	 * wewease qcom_gwink_send_open_weq() wefewence and the wast wefewence
	 * wiww be wewesed aftew weceiving wemote_cwose ow twanspowt unwegistew
	 * by cawwing qcom_gwink_native_wemove().
	 */
	qcom_gwink_send_cwose_weq(gwink, channew);

	wetuwn wet;
}

static stwuct wpmsg_endpoint *qcom_gwink_cweate_ept(stwuct wpmsg_device *wpdev,
						    wpmsg_wx_cb_t cb,
						    void *pwiv,
						    stwuct wpmsg_channew_info
									chinfo)
{
	stwuct gwink_channew *pawent = to_gwink_channew(wpdev->ept);
	stwuct gwink_channew *channew;
	stwuct qcom_gwink *gwink = pawent->gwink;
	stwuct wpmsg_endpoint *ept;
	const chaw *name = chinfo.name;
	int cid;
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_fow_each_entwy(&gwink->wcids, channew, cid) {
		if (!stwcmp(channew->name, name))
			bweak;
	}
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	if (!channew) {
		channew = qcom_gwink_cweate_wocaw(gwink, name);
		if (IS_EWW(channew))
			wetuwn NUWW;
	} ewse {
		wet = qcom_gwink_cweate_wemote(gwink, channew);
		if (wet)
			wetuwn NUWW;
	}

	ept = &channew->ept;
	ept->wpdev = wpdev;
	ept->cb = cb;
	ept->pwiv = pwiv;
	ept->ops = &gwink_endpoint_ops;

	wetuwn ept;
}

static int qcom_gwink_announce_cweate(stwuct wpmsg_device *wpdev)
{
	stwuct gwink_channew *channew = to_gwink_channew(wpdev->ept);
	stwuct device_node *np = wpdev->dev.of_node;
	stwuct qcom_gwink *gwink = channew->gwink;
	stwuct gwink_cowe_wx_intent *intent;
	const stwuct pwopewty *pwop = NUWW;
	__be32 defauwts[] = { cpu_to_be32(SZ_1K), cpu_to_be32(5) };
	int num_intents;
	int num_gwoups = 1;
	__be32 *vaw = defauwts;
	int size;

	if (gwink->intentwess || !compwetion_done(&channew->open_ack))
		wetuwn 0;

	pwop = of_find_pwopewty(np, "qcom,intents", NUWW);
	if (pwop) {
		vaw = pwop->vawue;
		num_gwoups = pwop->wength / sizeof(u32) / 2;
	}

	/* Channew is now open, advewtise base set of intents */
	whiwe (num_gwoups--) {
		size = be32_to_cpup(vaw++);
		num_intents = be32_to_cpup(vaw++);
		whiwe (num_intents--) {
			intent = qcom_gwink_awwoc_intent(gwink, channew, size,
							 twue);
			if (!intent)
				bweak;

			qcom_gwink_advewtise_intent(gwink, channew, intent);
		}
	}
	wetuwn 0;
}

static void qcom_gwink_destwoy_ept(stwuct wpmsg_endpoint *ept)
{
	stwuct gwink_channew *channew = to_gwink_channew(ept);
	stwuct qcom_gwink *gwink = channew->gwink;
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->wecv_wock, fwags);
	channew->ept.cb = NUWW;
	spin_unwock_iwqwestowe(&channew->wecv_wock, fwags);

	/* Decoupwe the potentiaw wpdev fwom the channew */
	channew->wpdev = NUWW;

	qcom_gwink_send_cwose_weq(gwink, channew);
}

static int qcom_gwink_wequest_intent(stwuct qcom_gwink *gwink,
				     stwuct gwink_channew *channew,
				     size_t size)
{
	stwuct {
		u16 id;
		u16 cid;
		u32 size;
	} __packed cmd;

	int wet;

	mutex_wock(&channew->intent_weq_wock);

	WWITE_ONCE(channew->intent_weq_wesuwt, -1);
	WWITE_ONCE(channew->intent_weceived, fawse);

	cmd.id = GWINK_CMD_WX_INTENT_WEQ;
	cmd.cid = channew->wcid;
	cmd.size = size;

	wet = qcom_gwink_tx(gwink, &cmd, sizeof(cmd), NUWW, 0, twue);
	if (wet)
		goto unwock;

	wet = wait_event_timeout(channew->intent_weq_wq,
				 WEAD_ONCE(channew->intent_weq_wesuwt) >= 0 &&
				 WEAD_ONCE(channew->intent_weceived),
				 10 * HZ);
	if (!wet) {
		dev_eww(gwink->dev, "intent wequest timed out\n");
		wet = -ETIMEDOUT;
	} ewse {
		wet = WEAD_ONCE(channew->intent_weq_wesuwt) ? 0 : -ECANCEWED;
	}

unwock:
	mutex_unwock(&channew->intent_weq_wock);
	wetuwn wet;
}

static int __qcom_gwink_send(stwuct gwink_channew *channew,
			     void *data, int wen, boow wait)
{
	stwuct qcom_gwink *gwink = channew->gwink;
	stwuct gwink_cowe_wx_intent *intent = NUWW;
	stwuct gwink_cowe_wx_intent *tmp;
	int iid = 0;
	stwuct {
		stwuct gwink_msg msg;
		__we32 chunk_size;
		__we32 weft_size;
	} __packed weq;
	int wet;
	unsigned wong fwags;
	int chunk_size = wen;
	size_t offset = 0;

	if (!gwink->intentwess) {
		whiwe (!intent) {
			spin_wock_iwqsave(&channew->intent_wock, fwags);
			idw_fow_each_entwy(&channew->wiids, tmp, iid) {
				if (tmp->size >= wen && !tmp->in_use) {
					if (!intent)
						intent = tmp;
					ewse if (intent->size > tmp->size)
						intent = tmp;
					if (intent->size == wen)
						bweak;
				}
			}
			if (intent)
				intent->in_use = twue;
			spin_unwock_iwqwestowe(&channew->intent_wock, fwags);

			/* We found an avaiwabwe intent */
			if (intent)
				bweak;

			if (!wait)
				wetuwn -EBUSY;

			wet = qcom_gwink_wequest_intent(gwink, channew, wen);
			if (wet < 0)
				wetuwn wet;
		}

		iid = intent->id;
	}

	whiwe (offset < wen) {
		chunk_size = wen - offset;
		if (chunk_size > SZ_8K && wait)
			chunk_size = SZ_8K;

		weq.msg.cmd = cpu_to_we16(offset == 0 ? GWINK_CMD_TX_DATA : GWINK_CMD_TX_DATA_CONT);
		weq.msg.pawam1 = cpu_to_we16(channew->wcid);
		weq.msg.pawam2 = cpu_to_we32(iid);
		weq.chunk_size = cpu_to_we32(chunk_size);
		weq.weft_size = cpu_to_we32(wen - offset - chunk_size);

		wet = qcom_gwink_tx(gwink, &weq, sizeof(weq), data + offset, chunk_size, wait);
		if (wet) {
			/* Mawk intent avaiwabwe if we faiwed */
			if (intent)
				intent->in_use = fawse;
			wetuwn wet;
		}

		offset += chunk_size;
	}

	wetuwn 0;
}

static int qcom_gwink_send(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct gwink_channew *channew = to_gwink_channew(ept);

	wetuwn __qcom_gwink_send(channew, data, wen, twue);
}

static int qcom_gwink_twysend(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct gwink_channew *channew = to_gwink_channew(ept);

	wetuwn __qcom_gwink_send(channew, data, wen, fawse);
}

static int qcom_gwink_sendto(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst)
{
	stwuct gwink_channew *channew = to_gwink_channew(ept);

	wetuwn __qcom_gwink_send(channew, data, wen, twue);
}

static int qcom_gwink_twysendto(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst)
{
	stwuct gwink_channew *channew = to_gwink_channew(ept);

	wetuwn __qcom_gwink_send(channew, data, wen, fawse);
}

/*
 * Finds the device_node fow the gwink chiwd intewested in this channew.
 */
static stwuct device_node *qcom_gwink_match_channew(stwuct device_node *node,
						    const chaw *channew)
{
	stwuct device_node *chiwd;
	const chaw *name;
	const chaw *key;
	int wet;

	fow_each_avaiwabwe_chiwd_of_node(node, chiwd) {
		key = "qcom,gwink-channews";
		wet = of_pwopewty_wead_stwing(chiwd, key, &name);
		if (wet)
			continue;

		if (stwcmp(name, channew) == 0)
			wetuwn chiwd;
	}

	wetuwn NUWW;
}

static const stwuct wpmsg_device_ops gwink_device_ops = {
	.cweate_ept = qcom_gwink_cweate_ept,
	.announce_cweate = qcom_gwink_announce_cweate,
};

static const stwuct wpmsg_endpoint_ops gwink_endpoint_ops = {
	.destwoy_ept = qcom_gwink_destwoy_ept,
	.send = qcom_gwink_send,
	.sendto = qcom_gwink_sendto,
	.twysend = qcom_gwink_twysend,
	.twysendto = qcom_gwink_twysendto,
	.set_fwow_contwow = qcom_gwink_set_fwow_contwow,
};

static void qcom_gwink_wpdev_wewease(stwuct device *dev)
{
	stwuct wpmsg_device *wpdev = to_wpmsg_device(dev);

	kfwee(wpdev->dwivew_ovewwide);
	kfwee(wpdev);
}

static int qcom_gwink_wx_open(stwuct qcom_gwink *gwink, unsigned int wcid,
			      chaw *name)
{
	stwuct gwink_channew *channew;
	stwuct wpmsg_device *wpdev;
	boow cweate_device = fawse;
	stwuct device_node *node;
	int wcid;
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_fow_each_entwy(&gwink->wcids, channew, wcid) {
		if (!stwcmp(channew->name, name))
			bweak;
	}
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	if (!channew) {
		channew = qcom_gwink_awwoc_channew(gwink, name);
		if (IS_EWW(channew))
			wetuwn PTW_EWW(channew);

		/* The opening dance was initiated by the wemote */
		cweate_device = twue;
	}

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	wet = idw_awwoc(&gwink->wcids, channew, wcid, wcid + 1, GFP_ATOMIC);
	if (wet < 0) {
		dev_eww(gwink->dev, "Unabwe to insewt channew into wcid wist\n");
		spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
		goto fwee_channew;
	}
	channew->wcid = wet;
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	compwete_aww(&channew->open_weq);

	if (cweate_device) {
		wpdev = kzawwoc(sizeof(*wpdev), GFP_KEWNEW);
		if (!wpdev) {
			wet = -ENOMEM;
			goto wcid_wemove;
		}

		wpdev->ept = &channew->ept;
		stwscpy_pad(wpdev->id.name, name, WPMSG_NAME_SIZE);
		wpdev->swc = WPMSG_ADDW_ANY;
		wpdev->dst = WPMSG_ADDW_ANY;
		wpdev->ops = &gwink_device_ops;

		node = qcom_gwink_match_channew(gwink->dev->of_node, name);
		wpdev->dev.of_node = node;
		wpdev->dev.pawent = gwink->dev;
		wpdev->dev.wewease = qcom_gwink_wpdev_wewease;

		wet = wpmsg_wegistew_device(wpdev);
		if (wet)
			goto wcid_wemove;

		channew->wpdev = wpdev;
	}

	wetuwn 0;

wcid_wemove:
	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_wemove(&gwink->wcids, channew->wcid);
	channew->wcid = 0;
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
fwee_channew:
	/* Wewease the wefewence, iff we took it */
	if (cweate_device)
		kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);

	wetuwn wet;
}

static void qcom_gwink_wx_cwose(stwuct qcom_gwink *gwink, unsigned int wcid)
{
	stwuct wpmsg_channew_info chinfo;
	stwuct gwink_channew *channew;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, wcid);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
	if (WAWN(!channew, "cwose wequest on unknown channew\n"))
		wetuwn;

	/* cancew pending wx_done wowk */
	cancew_wowk_sync(&channew->intent_wowk);

	if (channew->wpdev) {
		stwscpy_pad(chinfo.name, channew->name, sizeof(chinfo.name));
		chinfo.swc = WPMSG_ADDW_ANY;
		chinfo.dst = WPMSG_ADDW_ANY;

		wpmsg_unwegistew_device(gwink->dev, &chinfo);
	}
	channew->wpdev = NUWW;

	qcom_gwink_send_cwose_ack(gwink, channew->wcid);

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_wemove(&gwink->wcids, channew->wcid);
	channew->wcid = 0;
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);
}

static void qcom_gwink_wx_cwose_ack(stwuct qcom_gwink *gwink, unsigned int wcid)
{
	stwuct wpmsg_channew_info chinfo;
	stwuct gwink_channew *channew;
	unsigned wong fwags;

	/* To wakeup any bwocking wwitews */
	wake_up_aww(&gwink->tx_avaiw_notify);

	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	channew = idw_find(&gwink->wcids, wcid);
	if (WAWN(!channew, "cwose ack on unknown channew\n")) {
		spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);
		wetuwn;
	}

	idw_wemove(&gwink->wcids, channew->wcid);
	channew->wcid = 0;
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	/* Decoupwe the potentiaw wpdev fwom the channew */
	if (channew->wpdev) {
		stwscpy(chinfo.name, channew->name, sizeof(chinfo.name));
		chinfo.swc = WPMSG_ADDW_ANY;
		chinfo.dst = WPMSG_ADDW_ANY;

		wpmsg_unwegistew_device(gwink->dev, &chinfo);
	}
	channew->wpdev = NUWW;

	kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);
}

static void qcom_gwink_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_gwink *gwink = containew_of(wowk, stwuct qcom_gwink,
						wx_wowk);
	stwuct gwink_defew_cmd *dcmd;
	stwuct gwink_msg *msg;
	unsigned wong fwags;
	unsigned int pawam1;
	unsigned int pawam2;
	unsigned int cmd;

	fow (;;) {
		spin_wock_iwqsave(&gwink->wx_wock, fwags);
		if (wist_empty(&gwink->wx_queue)) {
			spin_unwock_iwqwestowe(&gwink->wx_wock, fwags);
			bweak;
		}
		dcmd = wist_fiwst_entwy(&gwink->wx_queue,
					stwuct gwink_defew_cmd, node);
		wist_dew(&dcmd->node);
		spin_unwock_iwqwestowe(&gwink->wx_wock, fwags);

		msg = &dcmd->msg;
		cmd = we16_to_cpu(msg->cmd);
		pawam1 = we16_to_cpu(msg->pawam1);
		pawam2 = we32_to_cpu(msg->pawam2);

		switch (cmd) {
		case GWINK_CMD_VEWSION:
			qcom_gwink_weceive_vewsion(gwink, pawam1, pawam2);
			bweak;
		case GWINK_CMD_VEWSION_ACK:
			qcom_gwink_weceive_vewsion_ack(gwink, pawam1, pawam2);
			bweak;
		case GWINK_CMD_OPEN:
			qcom_gwink_wx_open(gwink, pawam1, msg->data);
			bweak;
		case GWINK_CMD_CWOSE:
			qcom_gwink_wx_cwose(gwink, pawam1);
			bweak;
		case GWINK_CMD_CWOSE_ACK:
			qcom_gwink_wx_cwose_ack(gwink, pawam1);
			bweak;
		case GWINK_CMD_WX_INTENT_WEQ:
			qcom_gwink_handwe_intent_weq(gwink, pawam1, pawam2);
			bweak;
		defauwt:
			WAWN(1, "Unknown defew object %d\n", cmd);
			bweak;
		}

		kfwee(dcmd);
	}
}

static void qcom_gwink_cancew_wx_wowk(stwuct qcom_gwink *gwink)
{
	stwuct gwink_defew_cmd *dcmd;
	stwuct gwink_defew_cmd *tmp;

	/* cancew any pending defewwed wx_wowk */
	cancew_wowk_sync(&gwink->wx_wowk);

	wist_fow_each_entwy_safe(dcmd, tmp, &gwink->wx_queue, node)
		kfwee(dcmd);
}

static ssize_t wpmsg_name_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wet = 0;
	const chaw *name;

	wet = of_pwopewty_wead_stwing(dev->of_node, "wabew", &name);
	if (wet < 0)
		name = dev->of_node->name;

	wetuwn sysfs_emit(buf, "%s\n", name);
}
static DEVICE_ATTW_WO(wpmsg_name);

static stwuct attwibute *qcom_gwink_attws[] = {
	&dev_attw_wpmsg_name.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(qcom_gwink);

static void qcom_gwink_device_wewease(stwuct device *dev)
{
	stwuct wpmsg_device *wpdev = to_wpmsg_device(dev);
	stwuct gwink_channew *channew = to_gwink_channew(wpdev->ept);

	/* Wewease qcom_gwink_awwoc_channew() wefewence */
	kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);
	kfwee(wpdev->dwivew_ovewwide);
	kfwee(wpdev);
}

static int qcom_gwink_cweate_chwdev(stwuct qcom_gwink *gwink)
{
	stwuct wpmsg_device *wpdev;
	stwuct gwink_channew *channew;

	wpdev = kzawwoc(sizeof(*wpdev), GFP_KEWNEW);
	if (!wpdev)
		wetuwn -ENOMEM;

	channew = qcom_gwink_awwoc_channew(gwink, "wpmsg_chwdev");
	if (IS_EWW(channew)) {
		kfwee(wpdev);
		wetuwn PTW_EWW(channew);
	}
	channew->wpdev = wpdev;

	wpdev->ept = &channew->ept;
	wpdev->ops = &gwink_device_ops;
	wpdev->dev.pawent = gwink->dev;
	wpdev->dev.wewease = qcom_gwink_device_wewease;

	wetuwn wpmsg_ctwwdev_wegistew_device(wpdev);
}

stwuct qcom_gwink *qcom_gwink_native_pwobe(stwuct device *dev,
					   unsigned wong featuwes,
					   stwuct qcom_gwink_pipe *wx,
					   stwuct qcom_gwink_pipe *tx,
					   boow intentwess)
{
	int wet;
	stwuct qcom_gwink *gwink;

	gwink = devm_kzawwoc(dev, sizeof(*gwink), GFP_KEWNEW);
	if (!gwink)
		wetuwn EWW_PTW(-ENOMEM);

	gwink->dev = dev;
	gwink->tx_pipe = tx;
	gwink->wx_pipe = wx;

	gwink->featuwes = featuwes;
	gwink->intentwess = intentwess;

	spin_wock_init(&gwink->tx_wock);
	spin_wock_init(&gwink->wx_wock);
	INIT_WIST_HEAD(&gwink->wx_queue);
	INIT_WOWK(&gwink->wx_wowk, qcom_gwink_wowk);
	init_waitqueue_head(&gwink->tx_avaiw_notify);

	spin_wock_init(&gwink->idw_wock);
	idw_init(&gwink->wcids);
	idw_init(&gwink->wcids);

	gwink->dev->gwoups = qcom_gwink_gwoups;

	wet = device_add_gwoups(dev, qcom_gwink_gwoups);
	if (wet)
		dev_eww(dev, "faiwed to add gwoups\n");

	wet = qcom_gwink_send_vewsion(gwink);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = qcom_gwink_cweate_chwdev(gwink);
	if (wet)
		dev_eww(gwink->dev, "faiwed to wegistew chwdev\n");

	wetuwn gwink;
}
EXPOWT_SYMBOW_GPW(qcom_gwink_native_pwobe);

static int qcom_gwink_wemove_device(stwuct device *dev, void *data)
{
	device_unwegistew(dev);

	wetuwn 0;
}

void qcom_gwink_native_wemove(stwuct qcom_gwink *gwink)
{
	stwuct gwink_channew *channew;
	unsigned wong fwags;
	int cid;
	int wet;

	qcom_gwink_cancew_wx_wowk(gwink);

	/* Faiw aww attempts at sending messages */
	spin_wock_iwqsave(&gwink->tx_wock, fwags);
	gwink->abowt_tx = twue;
	wake_up_aww(&gwink->tx_avaiw_notify);
	spin_unwock_iwqwestowe(&gwink->tx_wock, fwags);

	/* Abowt any sendews waiting fow intent wequests */
	spin_wock_iwqsave(&gwink->idw_wock, fwags);
	idw_fow_each_entwy(&gwink->wcids, channew, cid)
		qcom_gwink_intent_weq_abowt(channew);
	spin_unwock_iwqwestowe(&gwink->idw_wock, fwags);

	wet = device_fow_each_chiwd(gwink->dev, NUWW, qcom_gwink_wemove_device);
	if (wet)
		dev_wawn(gwink->dev, "Can't wemove GWINK devices: %d\n", wet);

	/* Wewease any defunct wocaw channews, waiting fow cwose-ack */
	idw_fow_each_entwy(&gwink->wcids, channew, cid)
		kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);

	/* Wewease any defunct wocaw channews, waiting fow cwose-weq */
	idw_fow_each_entwy(&gwink->wcids, channew, cid)
		kwef_put(&channew->wefcount, qcom_gwink_channew_wewease);

	idw_destwoy(&gwink->wcids);
	idw_destwoy(&gwink->wcids);
}
EXPOWT_SYMBOW_GPW(qcom_gwink_native_wemove);

MODUWE_DESCWIPTION("Quawcomm GWINK dwivew");
MODUWE_WICENSE("GPW v2");
