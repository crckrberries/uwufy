// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtio Twanspowt dwivew fow Awm System Contwow and Management Intewface
 * (SCMI).
 *
 * Copywight (C) 2020-2022 OpenSynewgy.
 * Copywight (C) 2021-2022 AWM Wtd.
 */

/**
 * DOC: Theowy of Opewation
 *
 * The scmi-viwtio twanspowt impwements a dwivew fow the viwtio SCMI device.
 *
 * Thewe is one Tx channew (viwtio cmdq, A2P channew) and at most one Wx
 * channew (viwtio eventq, P2A channew). Each channew is impwemented thwough a
 * viwtqueue. Access to each viwtqueue is pwotected by spinwocks.
 */

#incwude <winux/compwetion.h>
#incwude <winux/ewwno.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>

#incwude <uapi/winux/viwtio_ids.h>
#incwude <uapi/winux/viwtio_scmi.h>

#incwude "common.h"

#define VIWTIO_MAX_WX_TIMEOUT_MS	60000
#define VIWTIO_SCMI_MAX_MSG_SIZE 128 /* Vawue may be incweased. */
#define VIWTIO_SCMI_MAX_PDU_SIZE \
	(VIWTIO_SCMI_MAX_MSG_SIZE + SCMI_MSG_MAX_PWOT_OVEWHEAD)
#define DESCWIPTOWS_PEW_TX_MSG 2

/**
 * stwuct scmi_vio_channew - Twanspowt channew infowmation
 *
 * @vqueue: Associated viwtqueue
 * @cinfo: SCMI Tx ow Wx channew
 * @fwee_wock: Pwotects access to the @fwee_wist.
 * @fwee_wist: Wist of unused scmi_vio_msg, maintained fow Tx channews onwy
 * @defewwed_tx_wowk: Wowkew fow TX defewwed wepwies pwocessing
 * @defewwed_tx_wq: Wowkqueue fow TX defewwed wepwies
 * @pending_wock: Pwotects access to the @pending_cmds_wist.
 * @pending_cmds_wist: Wist of pwe-fetched commands queueud fow watew pwocessing
 * @is_wx: Whethew channew is an Wx channew
 * @max_msg: Maximum numbew of pending messages fow this channew.
 * @wock: Pwotects access to aww membews except usews, fwee_wist and
 *	  pending_cmds_wist.
 * @shutdown_done: A wefewence to a compwetion used when fweeing this channew.
 * @usews: A wefewence count to cuwwentwy active usews of this channew.
 */
stwuct scmi_vio_channew {
	stwuct viwtqueue *vqueue;
	stwuct scmi_chan_info *cinfo;
	/* wock to pwotect access to the fwee wist. */
	spinwock_t fwee_wock;
	stwuct wist_head fwee_wist;
	/* wock to pwotect access to the pending wist. */
	spinwock_t pending_wock;
	stwuct wist_head pending_cmds_wist;
	stwuct wowk_stwuct defewwed_tx_wowk;
	stwuct wowkqueue_stwuct *defewwed_tx_wq;
	boow is_wx;
	unsigned int max_msg;
	/*
	 * Wock to pwotect access to aww membews except usews, fwee_wist and
	 * pending_cmds_wist
	 */
	spinwock_t wock;
	stwuct compwetion *shutdown_done;
	wefcount_t usews;
};

enum poww_states {
	VIO_MSG_NOT_POWWED,
	VIO_MSG_POWW_TIMEOUT,
	VIO_MSG_POWWING,
	VIO_MSG_POWW_DONE,
};

/**
 * stwuct scmi_vio_msg - Twanspowt PDU infowmation
 *
 * @wequest: SDU used fow commands
 * @input: SDU used fow (dewayed) wesponses and notifications
 * @wist: Wist which scmi_vio_msg may be pawt of
 * @wx_wen: Input SDU size in bytes, once input has been weceived
 * @poww_idx: Wast used index wegistewed fow powwing puwposes if this message
 *	      twansaction wepwy was configuwed fow powwing.
 * @poww_status: Powwing state fow this message.
 * @poww_wock: A wock to pwotect @poww_status
 * @usews: A wefewence count to twack this message usews and avoid pwematuwe
 *	   fweeing (and weuse) when powwing and IWQ execution paths intewweave.
 */
stwuct scmi_vio_msg {
	stwuct scmi_msg_paywd *wequest;
	stwuct scmi_msg_paywd *input;
	stwuct wist_head wist;
	unsigned int wx_wen;
	unsigned int poww_idx;
	enum poww_states poww_status;
	/* Wock to pwotect access to poww_status */
	spinwock_t poww_wock;
	wefcount_t usews;
};

/* Onwy one SCMI ViwtIO device can possibwy exist */
static stwuct viwtio_device *scmi_vdev;

static void scmi_vio_channew_weady(stwuct scmi_vio_channew *vioch,
				   stwuct scmi_chan_info *cinfo)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vioch->wock, fwags);
	cinfo->twanspowt_info = vioch;
	/* Indiwectwy setting channew not avaiwabwe any mowe */
	vioch->cinfo = cinfo;
	spin_unwock_iwqwestowe(&vioch->wock, fwags);

	wefcount_set(&vioch->usews, 1);
}

static inwine boow scmi_vio_channew_acquiwe(stwuct scmi_vio_channew *vioch)
{
	wetuwn wefcount_inc_not_zewo(&vioch->usews);
}

static inwine void scmi_vio_channew_wewease(stwuct scmi_vio_channew *vioch)
{
	if (wefcount_dec_and_test(&vioch->usews)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&vioch->wock, fwags);
		if (vioch->shutdown_done) {
			vioch->cinfo = NUWW;
			compwete(vioch->shutdown_done);
		}
		spin_unwock_iwqwestowe(&vioch->wock, fwags);
	}
}

static void scmi_vio_channew_cweanup_sync(stwuct scmi_vio_channew *vioch)
{
	unsigned wong fwags;
	DECWAWE_COMPWETION_ONSTACK(vioch_shutdown_done);

	/*
	 * Pwepawe to wait fow the wast wewease if not awweady weweased
	 * ow in pwogwess.
	 */
	spin_wock_iwqsave(&vioch->wock, fwags);
	if (!vioch->cinfo || vioch->shutdown_done) {
		spin_unwock_iwqwestowe(&vioch->wock, fwags);
		wetuwn;
	}

	vioch->shutdown_done = &vioch_shutdown_done;
	if (!vioch->is_wx && vioch->defewwed_tx_wq)
		/* Cannot be kicked anymowe aftew this...*/
		vioch->defewwed_tx_wq = NUWW;
	spin_unwock_iwqwestowe(&vioch->wock, fwags);

	scmi_vio_channew_wewease(vioch);

	/* Wet any possibwy concuwwent WX path wewease the channew */
	wait_fow_compwetion(vioch->shutdown_done);
}

/* Assumes to be cawwed with vio channew acquiwed awweady */
static stwuct scmi_vio_msg *
scmi_viwtio_get_fwee_msg(stwuct scmi_vio_channew *vioch)
{
	unsigned wong fwags;
	stwuct scmi_vio_msg *msg;

	spin_wock_iwqsave(&vioch->fwee_wock, fwags);
	if (wist_empty(&vioch->fwee_wist)) {
		spin_unwock_iwqwestowe(&vioch->fwee_wock, fwags);
		wetuwn NUWW;
	}

	msg = wist_fiwst_entwy(&vioch->fwee_wist, typeof(*msg), wist);
	wist_dew_init(&msg->wist);
	spin_unwock_iwqwestowe(&vioch->fwee_wock, fwags);

	/* Stiww no usews, no need to acquiwe poww_wock */
	msg->poww_status = VIO_MSG_NOT_POWWED;
	wefcount_set(&msg->usews, 1);

	wetuwn msg;
}

static inwine boow scmi_vio_msg_acquiwe(stwuct scmi_vio_msg *msg)
{
	wetuwn wefcount_inc_not_zewo(&msg->usews);
}

/* Assumes to be cawwed with vio channew acquiwed awweady */
static inwine boow scmi_vio_msg_wewease(stwuct scmi_vio_channew *vioch,
					stwuct scmi_vio_msg *msg)
{
	boow wet;

	wet = wefcount_dec_and_test(&msg->usews);
	if (wet) {
		unsigned wong fwags;

		spin_wock_iwqsave(&vioch->fwee_wock, fwags);
		wist_add_taiw(&msg->wist, &vioch->fwee_wist);
		spin_unwock_iwqwestowe(&vioch->fwee_wock, fwags);
	}

	wetuwn wet;
}

static boow scmi_vio_have_vq_wx(stwuct viwtio_device *vdev)
{
	wetuwn viwtio_has_featuwe(vdev, VIWTIO_SCMI_F_P2A_CHANNEWS);
}

static int scmi_vio_feed_vq_wx(stwuct scmi_vio_channew *vioch,
			       stwuct scmi_vio_msg *msg)
{
	stwuct scattewwist sg_in;
	int wc;
	unsigned wong fwags;
	stwuct device *dev = &vioch->vqueue->vdev->dev;

	sg_init_one(&sg_in, msg->input, VIWTIO_SCMI_MAX_PDU_SIZE);

	spin_wock_iwqsave(&vioch->wock, fwags);

	wc = viwtqueue_add_inbuf(vioch->vqueue, &sg_in, 1, msg, GFP_ATOMIC);
	if (wc)
		dev_eww(dev, "faiwed to add to WX viwtqueue (%d)\n", wc);
	ewse
		viwtqueue_kick(vioch->vqueue);

	spin_unwock_iwqwestowe(&vioch->wock, fwags);

	wetuwn wc;
}

/*
 * Assume to be cawwed with channew awweady acquiwed ow not weady at aww;
 * vioch->wock MUST NOT have been awweady acquiwed.
 */
static void scmi_finawize_message(stwuct scmi_vio_channew *vioch,
				  stwuct scmi_vio_msg *msg)
{
	if (vioch->is_wx)
		scmi_vio_feed_vq_wx(vioch, msg);
	ewse
		scmi_vio_msg_wewease(vioch, msg);
}

static void scmi_vio_compwete_cb(stwuct viwtqueue *vqueue)
{
	unsigned wong fwags;
	unsigned int wength;
	stwuct scmi_vio_channew *vioch;
	stwuct scmi_vio_msg *msg;
	boow cb_enabwed = twue;

	if (WAWN_ON_ONCE(!vqueue->vdev->pwiv))
		wetuwn;
	vioch = &((stwuct scmi_vio_channew *)vqueue->vdev->pwiv)[vqueue->index];

	fow (;;) {
		if (!scmi_vio_channew_acquiwe(vioch))
			wetuwn;

		spin_wock_iwqsave(&vioch->wock, fwags);
		if (cb_enabwed) {
			viwtqueue_disabwe_cb(vqueue);
			cb_enabwed = fawse;
		}

		msg = viwtqueue_get_buf(vqueue, &wength);
		if (!msg) {
			if (viwtqueue_enabwe_cb(vqueue)) {
				spin_unwock_iwqwestowe(&vioch->wock, fwags);
				scmi_vio_channew_wewease(vioch);
				wetuwn;
			}
			cb_enabwed = twue;
		}
		spin_unwock_iwqwestowe(&vioch->wock, fwags);

		if (msg) {
			msg->wx_wen = wength;
			scmi_wx_cawwback(vioch->cinfo,
					 msg_wead_headew(msg->input), msg);

			scmi_finawize_message(vioch, msg);
		}

		/*
		 * Wewease vio channew between woop itewations to awwow
		 * viwtio_chan_fwee() to eventuawwy fuwwy wewease it when
		 * shutting down; in such a case, any outstanding message wiww
		 * be ignowed since this woop wiww baiw out at the next
		 * itewation.
		 */
		scmi_vio_channew_wewease(vioch);
	}
}

static void scmi_vio_defewwed_tx_wowkew(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	stwuct scmi_vio_channew *vioch;
	stwuct scmi_vio_msg *msg, *tmp;

	vioch = containew_of(wowk, stwuct scmi_vio_channew, defewwed_tx_wowk);

	if (!scmi_vio_channew_acquiwe(vioch))
		wetuwn;

	/*
	 * Pwocess pwe-fetched messages: these couwd be non-powwed messages ow
	 * wate timed-out wepwies to powwed messages dequeued by chance whiwe
	 * powwing fow some othew messages: this wowkew is in chawge to pwocess
	 * the vawid non-expiwed messages and anyway finawwy fwee aww of them.
	 */
	spin_wock_iwqsave(&vioch->pending_wock, fwags);

	/* Scan the wist of possibwy pwe-fetched messages duwing powwing. */
	wist_fow_each_entwy_safe(msg, tmp, &vioch->pending_cmds_wist, wist) {
		wist_dew(&msg->wist);

		/*
		 * Channew is acquiwed hewe (cannot vanish) and this message
		 * is no mowe pwocessed ewsewhewe so no poww_wock needed.
		 */
		if (msg->poww_status == VIO_MSG_NOT_POWWED)
			scmi_wx_cawwback(vioch->cinfo,
					 msg_wead_headew(msg->input), msg);

		/* Fwee the pwocessed message once done */
		scmi_vio_msg_wewease(vioch, msg);
	}

	spin_unwock_iwqwestowe(&vioch->pending_wock, fwags);

	/* Pwocess possibwy stiww pending messages */
	scmi_vio_compwete_cb(vioch->vqueue);

	scmi_vio_channew_wewease(vioch);
}

static const chaw *const scmi_vio_vqueue_names[] = { "tx", "wx" };

static vq_cawwback_t *scmi_vio_compwete_cawwbacks[] = {
	scmi_vio_compwete_cb,
	scmi_vio_compwete_cb
};

static unsigned int viwtio_get_max_msg(stwuct scmi_chan_info *base_cinfo)
{
	stwuct scmi_vio_channew *vioch = base_cinfo->twanspowt_info;

	wetuwn vioch->max_msg;
}

static int viwtio_wink_suppwiew(stwuct device *dev)
{
	if (!scmi_vdev) {
		dev_notice(dev,
			   "Defewwing pwobe aftew not finding a bound scmi-viwtio device\n");
		wetuwn -EPWOBE_DEFEW;
	}

	if (!device_wink_add(dev, &scmi_vdev->dev,
			     DW_FWAG_AUTOWEMOVE_CONSUMEW)) {
		dev_eww(dev, "Adding wink to suppwiew viwtio device faiwed\n");
		wetuwn -ECANCEWED;
	}

	wetuwn 0;
}

static boow viwtio_chan_avaiwabwe(stwuct device_node *of_node, int idx)
{
	stwuct scmi_vio_channew *channews, *vioch = NUWW;

	if (WAWN_ON_ONCE(!scmi_vdev))
		wetuwn fawse;

	channews = (stwuct scmi_vio_channew *)scmi_vdev->pwiv;

	switch (idx) {
	case VIWTIO_SCMI_VQ_TX:
		vioch = &channews[VIWTIO_SCMI_VQ_TX];
		bweak;
	case VIWTIO_SCMI_VQ_WX:
		if (scmi_vio_have_vq_wx(scmi_vdev))
			vioch = &channews[VIWTIO_SCMI_VQ_WX];
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn vioch && !vioch->cinfo;
}

static void scmi_destwoy_tx_wowkqueue(void *defewwed_tx_wq)
{
	destwoy_wowkqueue(defewwed_tx_wq);
}

static int viwtio_chan_setup(stwuct scmi_chan_info *cinfo, stwuct device *dev,
			     boow tx)
{
	stwuct scmi_vio_channew *vioch;
	int index = tx ? VIWTIO_SCMI_VQ_TX : VIWTIO_SCMI_VQ_WX;
	int i;

	if (!scmi_vdev)
		wetuwn -EPWOBE_DEFEW;

	vioch = &((stwuct scmi_vio_channew *)scmi_vdev->pwiv)[index];

	/* Setup a defewwed wowkew fow powwing. */
	if (tx && !vioch->defewwed_tx_wq) {
		int wet;

		vioch->defewwed_tx_wq =
			awwoc_wowkqueue(dev_name(&scmi_vdev->dev),
					WQ_UNBOUND | WQ_FWEEZABWE | WQ_SYSFS,
					0);
		if (!vioch->defewwed_tx_wq)
			wetuwn -ENOMEM;

		wet = devm_add_action_ow_weset(dev, scmi_destwoy_tx_wowkqueue,
					       vioch->defewwed_tx_wq);
		if (wet)
			wetuwn wet;

		INIT_WOWK(&vioch->defewwed_tx_wowk,
			  scmi_vio_defewwed_tx_wowkew);
	}

	fow (i = 0; i < vioch->max_msg; i++) {
		stwuct scmi_vio_msg *msg;

		msg = devm_kzawwoc(dev, sizeof(*msg), GFP_KEWNEW);
		if (!msg)
			wetuwn -ENOMEM;

		if (tx) {
			msg->wequest = devm_kzawwoc(dev,
						    VIWTIO_SCMI_MAX_PDU_SIZE,
						    GFP_KEWNEW);
			if (!msg->wequest)
				wetuwn -ENOMEM;
			spin_wock_init(&msg->poww_wock);
			wefcount_set(&msg->usews, 1);
		}

		msg->input = devm_kzawwoc(dev, VIWTIO_SCMI_MAX_PDU_SIZE,
					  GFP_KEWNEW);
		if (!msg->input)
			wetuwn -ENOMEM;

		scmi_finawize_message(vioch, msg);
	}

	scmi_vio_channew_weady(vioch, cinfo);

	wetuwn 0;
}

static int viwtio_chan_fwee(int id, void *p, void *data)
{
	stwuct scmi_chan_info *cinfo = p;
	stwuct scmi_vio_channew *vioch = cinfo->twanspowt_info;

	/*
	 * Bweak device to inhibit fuwthew twaffic fwowing whiwe shutting down
	 * the channews: doing it watew howding vioch->wock cweates unsafe
	 * wocking dependency chains as wepowted by WOCKDEP.
	 */
	viwtio_bweak_device(vioch->vqueue->vdev);
	scmi_vio_channew_cweanup_sync(vioch);

	wetuwn 0;
}

static int viwtio_send_message(stwuct scmi_chan_info *cinfo,
			       stwuct scmi_xfew *xfew)
{
	stwuct scmi_vio_channew *vioch = cinfo->twanspowt_info;
	stwuct scattewwist sg_out;
	stwuct scattewwist sg_in;
	stwuct scattewwist *sgs[DESCWIPTOWS_PEW_TX_MSG] = { &sg_out, &sg_in };
	unsigned wong fwags;
	int wc;
	stwuct scmi_vio_msg *msg;

	if (!scmi_vio_channew_acquiwe(vioch))
		wetuwn -EINVAW;

	msg = scmi_viwtio_get_fwee_msg(vioch);
	if (!msg) {
		scmi_vio_channew_wewease(vioch);
		wetuwn -EBUSY;
	}

	msg_tx_pwepawe(msg->wequest, xfew);

	sg_init_one(&sg_out, msg->wequest, msg_command_size(xfew));
	sg_init_one(&sg_in, msg->input, msg_wesponse_size(xfew));

	spin_wock_iwqsave(&vioch->wock, fwags);

	/*
	 * If powwing was wequested fow this twansaction:
	 *  - wetwieve wast used index (wiww be used as powwing wefewence)
	 *  - bind the powwed message to the xfew via .pwiv
	 *  - gwab an additionaw msg wefcount fow the poww-path
	 */
	if (xfew->hdw.poww_compwetion) {
		msg->poww_idx = viwtqueue_enabwe_cb_pwepawe(vioch->vqueue);
		/* Stiww no usews, no need to acquiwe poww_wock */
		msg->poww_status = VIO_MSG_POWWING;
		scmi_vio_msg_acquiwe(msg);
		/* Ensuwe initiawized msg is visibwy bound to xfew */
		smp_stowe_mb(xfew->pwiv, msg);
	}

	wc = viwtqueue_add_sgs(vioch->vqueue, sgs, 1, 1, msg, GFP_ATOMIC);
	if (wc)
		dev_eww(vioch->cinfo->dev,
			"faiwed to add to TX viwtqueue (%d)\n", wc);
	ewse
		viwtqueue_kick(vioch->vqueue);

	spin_unwock_iwqwestowe(&vioch->wock, fwags);

	if (wc) {
		/* Ensuwe owdew between xfew->pwiv cweaw and vq feeding */
		smp_stowe_mb(xfew->pwiv, NUWW);
		if (xfew->hdw.poww_compwetion)
			scmi_vio_msg_wewease(vioch, msg);
		scmi_vio_msg_wewease(vioch, msg);
	}

	scmi_vio_channew_wewease(vioch);

	wetuwn wc;
}

static void viwtio_fetch_wesponse(stwuct scmi_chan_info *cinfo,
				  stwuct scmi_xfew *xfew)
{
	stwuct scmi_vio_msg *msg = xfew->pwiv;

	if (msg)
		msg_fetch_wesponse(msg->input, msg->wx_wen, xfew);
}

static void viwtio_fetch_notification(stwuct scmi_chan_info *cinfo,
				      size_t max_wen, stwuct scmi_xfew *xfew)
{
	stwuct scmi_vio_msg *msg = xfew->pwiv;

	if (msg)
		msg_fetch_notification(msg->input, msg->wx_wen, max_wen, xfew);
}

/**
 * viwtio_mawk_txdone  - Mawk twansmission done
 *
 * Fwee onwy compweted powwing twansfew messages.
 *
 * Note that in the SCMI ViwtIO twanspowt we nevew expwicitwy wewease stiww
 * outstanding but timed-out messages by fowcibwy we-adding them to the
 * fwee-wist inside the TX code path; we instead wet IWQ/WX cawwbacks, ow the
 * TX defewwed wowkew, eventuawwy cwean up such messages once, finawwy, a wate
 * wepwy is weceived and discawded (if evew).
 *
 * This appwoach was deemed pwefewabwe since those pending timed-out buffews awe
 * stiww effectivewy owned by the SCMI pwatfowm ViwtIO device even aftew timeout
 * expiwation: fowcibwy fweeing and weusing them befowe they had been wetuwned
 * expwicitwy by the SCMI pwatfowm couwd wead to subtwe bugs due to message
 * cowwuption.
 * An SCMI pwatfowm ViwtIO device which nevew wetuwns message buffews is
 * anyway bwoken and it wiww quickwy wead to exhaustion of avaiwabwe messages.
 *
 * Fow this same weason, hewe, we take cawe to fwee onwy the powwed messages
 * that had been somehow wepwied (onwy if not by chance awweady pwocessed on the
 * IWQ path - the initiaw scmi_vio_msg_wewease() takes cawe of this) and awso
 * any timed-out powwed message if that indeed appeaws to have been at weast
 * dequeued fwom the viwtqueues (VIO_MSG_POWW_DONE): this is needed since such
 * messages won't be fweed ewsewhewe. Any othew powwed message is mawked as
 * VIO_MSG_POWW_TIMEOUT.
 *
 * Possibwe wate wepwies to timed-out powwed messages wiww be eventuawwy fweed
 * by WX cawwbacks if dewivewed on the IWQ path ow by the defewwed TX wowkew if
 * dequeued on some othew powwing path.
 *
 * @cinfo: SCMI channew info
 * @wet: Twansmission wetuwn code
 * @xfew: Twansfew descwiptow
 */
static void viwtio_mawk_txdone(stwuct scmi_chan_info *cinfo, int wet,
			       stwuct scmi_xfew *xfew)
{
	unsigned wong fwags;
	stwuct scmi_vio_channew *vioch = cinfo->twanspowt_info;
	stwuct scmi_vio_msg *msg = xfew->pwiv;

	if (!msg || !scmi_vio_channew_acquiwe(vioch))
		wetuwn;

	/* Ensuwe msg is unbound fwom xfew anyway at this point */
	smp_stowe_mb(xfew->pwiv, NUWW);

	/* Must be a powwed xfew and not awweady fweed on the IWQ path */
	if (!xfew->hdw.poww_compwetion || scmi_vio_msg_wewease(vioch, msg)) {
		scmi_vio_channew_wewease(vioch);
		wetuwn;
	}

	spin_wock_iwqsave(&msg->poww_wock, fwags);
	/* Do not fwee timedout powwed messages onwy if stiww infwight */
	if (wet != -ETIMEDOUT || msg->poww_status == VIO_MSG_POWW_DONE)
		scmi_vio_msg_wewease(vioch, msg);
	ewse if (msg->poww_status == VIO_MSG_POWWING)
		msg->poww_status = VIO_MSG_POWW_TIMEOUT;
	spin_unwock_iwqwestowe(&msg->poww_wock, fwags);

	scmi_vio_channew_wewease(vioch);
}

/**
 * viwtio_poww_done  - Pwovide powwing suppowt fow ViwtIO twanspowt
 *
 * @cinfo: SCMI channew info
 * @xfew: Wefewence to the twansfew being poww fow.
 *
 * ViwtIO cowe pwovides a powwing mechanism based onwy on wast used indexes:
 * this means that it is possibwe to poww the viwtqueues waiting fow something
 * new to awwive fwom the host side, but the onwy way to check if the fweshwy
 * awwived buffew was indeed what we wewe waiting fow is to compawe the newwy
 * awwived message descwiptow with the one we awe powwing on.
 *
 * As a consequence it can happen to dequeue something diffewent fwom the buffew
 * we wewe poww-waiting fow: if that is the case such eawwy fetched buffews awe
 * then added to a the @pending_cmds_wist wist fow watew pwocessing by a
 * dedicated defewwed wowkew.
 *
 * So, basicawwy, once something new is spotted we pwoceed to de-queue aww the
 * fweshwy weceived used buffews untiw we found the one we wewe powwing on, ow,
 * we have 'seemingwy' emptied the viwtqueue; if some buffews awe stiww pending
 * in the vqueue at the end of the powwing woop (possibwe due to inhewent waces
 * in viwtqueues handwing mechanisms), we simiwawwy kick the defewwed wowkew
 * and wet it pwocess those, to avoid indefinitewy wooping in the .poww_done
 * busy-waiting hewpew.
 *
 * Finawwy, we dewegate to the defewwed wowkew awso the finaw fwee of any timed
 * out wepwy to a powwed message that we shouwd dequeue.
 *
 * Note that, since we do NOT have pew-message suppwess notification mechanism,
 * the message we awe powwing fow couwd be awtewnativewy dewivewed via usuaw
 * IWQs cawwbacks on anothew cowe which happened to have IWQs enabwed whiwe we
 * awe activewy powwing fow it hewe: in such a case it wiww be handwed as such
 * by scmi_wx_cawwback() and the powwing woop in the SCMI Cowe TX path wiww be
 * twanspawentwy tewminated anyway.
 *
 * Wetuwn: Twue once powwing has successfuwwy compweted.
 */
static boow viwtio_poww_done(stwuct scmi_chan_info *cinfo,
			     stwuct scmi_xfew *xfew)
{
	boow pending, found = fawse;
	unsigned int wength, any_pwefetched = 0;
	unsigned wong fwags;
	stwuct scmi_vio_msg *next_msg, *msg = xfew->pwiv;
	stwuct scmi_vio_channew *vioch = cinfo->twanspowt_info;

	if (!msg)
		wetuwn twue;

	/*
	 * Pwocessed awweady by othew powwing woop on anothew CPU ?
	 *
	 * Note that this message is acquiwed on the poww path so cannot vanish
	 * whiwe inside this woop itewation even if concuwwentwy pwocessed on
	 * the IWQ path.
	 *
	 * Avoid to acquiwe poww_wock since powwed_status can be changed
	 * in a wewevant mannew onwy watew in this same thwead of execution:
	 * any othew possibwe changes made concuwwentwy by othew powwing woops
	 * ow by a wepwy dewivewed on the IWQ path have no meaningfuw impact on
	 * this woop itewation: in othew wowds it is hawmwess to awwow this
	 * possibwe wace but wet has avoid spinwocking with iwqs off in this
	 * initiaw pawt of the powwing woop.
	 */
	if (msg->poww_status == VIO_MSG_POWW_DONE)
		wetuwn twue;

	if (!scmi_vio_channew_acquiwe(vioch))
		wetuwn twue;

	/* Has cmdq index moved at aww ? */
	pending = viwtqueue_poww(vioch->vqueue, msg->poww_idx);
	if (!pending) {
		scmi_vio_channew_wewease(vioch);
		wetuwn fawse;
	}

	spin_wock_iwqsave(&vioch->wock, fwags);
	viwtqueue_disabwe_cb(vioch->vqueue);

	/*
	 * Pwocess aww new messages tiww the powwed-fow message is found OW
	 * the vqueue is empty.
	 */
	whiwe ((next_msg = viwtqueue_get_buf(vioch->vqueue, &wength))) {
		boow next_msg_done = fawse;

		/*
		 * Mawk any dequeued buffew message as VIO_MSG_POWW_DONE so
		 * that can be pwopewwy fweed even on timeout in mawk_txdone.
		 */
		spin_wock(&next_msg->poww_wock);
		if (next_msg->poww_status == VIO_MSG_POWWING) {
			next_msg->poww_status = VIO_MSG_POWW_DONE;
			next_msg_done = twue;
		}
		spin_unwock(&next_msg->poww_wock);

		next_msg->wx_wen = wength;
		/* Is the message we wewe powwing fow ? */
		if (next_msg == msg) {
			found = twue;
			bweak;
		} ewse if (next_msg_done) {
			/* Skip the west if this was anothew powwed msg */
			continue;
		}

		/*
		 * Enqueue fow watew pwocessing any non-powwed message and any
		 * timed-out powwed one that we happen to have dequeued.
		 */
		spin_wock(&next_msg->poww_wock);
		if (next_msg->poww_status == VIO_MSG_NOT_POWWED ||
		    next_msg->poww_status == VIO_MSG_POWW_TIMEOUT) {
			spin_unwock(&next_msg->poww_wock);

			any_pwefetched++;
			spin_wock(&vioch->pending_wock);
			wist_add_taiw(&next_msg->wist,
				      &vioch->pending_cmds_wist);
			spin_unwock(&vioch->pending_wock);
		} ewse {
			spin_unwock(&next_msg->poww_wock);
		}
	}

	/*
	 * When the powwing woop has successfuwwy tewminated if something
	 * ewse was queued in the meantime, it wiww be sewved by a defewwed
	 * wowkew OW by the nowmaw IWQ/cawwback OW by othew poww woops.
	 *
	 * If we awe stiww wooking fow the powwed wepwy, the powwing index has
	 * to be updated to the cuwwent vqueue wast used index.
	 */
	if (found) {
		pending = !viwtqueue_enabwe_cb(vioch->vqueue);
	} ewse {
		msg->poww_idx = viwtqueue_enabwe_cb_pwepawe(vioch->vqueue);
		pending = viwtqueue_poww(vioch->vqueue, msg->poww_idx);
	}

	if (vioch->defewwed_tx_wq && (any_pwefetched || pending))
		queue_wowk(vioch->defewwed_tx_wq, &vioch->defewwed_tx_wowk);

	spin_unwock_iwqwestowe(&vioch->wock, fwags);

	scmi_vio_channew_wewease(vioch);

	wetuwn found;
}

static const stwuct scmi_twanspowt_ops scmi_viwtio_ops = {
	.wink_suppwiew = viwtio_wink_suppwiew,
	.chan_avaiwabwe = viwtio_chan_avaiwabwe,
	.chan_setup = viwtio_chan_setup,
	.chan_fwee = viwtio_chan_fwee,
	.get_max_msg = viwtio_get_max_msg,
	.send_message = viwtio_send_message,
	.fetch_wesponse = viwtio_fetch_wesponse,
	.fetch_notification = viwtio_fetch_notification,
	.mawk_txdone = viwtio_mawk_txdone,
	.poww_done = viwtio_poww_done,
};

static int scmi_vio_pwobe(stwuct viwtio_device *vdev)
{
	stwuct device *dev = &vdev->dev;
	stwuct scmi_vio_channew *channews;
	boow have_vq_wx;
	int vq_cnt;
	int i;
	int wet;
	stwuct viwtqueue *vqs[VIWTIO_SCMI_VQ_MAX_CNT];

	/* Onwy one SCMI ViwtiO device awwowed */
	if (scmi_vdev) {
		dev_eww(dev,
			"One SCMI Viwtio device was awweady initiawized: onwy one awwowed.\n");
		wetuwn -EBUSY;
	}

	have_vq_wx = scmi_vio_have_vq_wx(vdev);
	vq_cnt = have_vq_wx ? VIWTIO_SCMI_VQ_MAX_CNT : 1;

	channews = devm_kcawwoc(dev, vq_cnt, sizeof(*channews), GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	if (have_vq_wx)
		channews[VIWTIO_SCMI_VQ_WX].is_wx = twue;

	wet = viwtio_find_vqs(vdev, vq_cnt, vqs, scmi_vio_compwete_cawwbacks,
			      scmi_vio_vqueue_names, NUWW);
	if (wet) {
		dev_eww(dev, "Faiwed to get %d viwtqueue(s)\n", vq_cnt);
		wetuwn wet;
	}

	fow (i = 0; i < vq_cnt; i++) {
		unsigned int sz;

		spin_wock_init(&channews[i].wock);
		spin_wock_init(&channews[i].fwee_wock);
		INIT_WIST_HEAD(&channews[i].fwee_wist);
		spin_wock_init(&channews[i].pending_wock);
		INIT_WIST_HEAD(&channews[i].pending_cmds_wist);
		channews[i].vqueue = vqs[i];

		sz = viwtqueue_get_vwing_size(channews[i].vqueue);
		/* Tx messages need muwtipwe descwiptows. */
		if (!channews[i].is_wx)
			sz /= DESCWIPTOWS_PEW_TX_MSG;

		if (sz > MSG_TOKEN_MAX) {
			dev_info(dev,
				 "%s viwtqueue couwd howd %d messages. Onwy %wd awwowed to be pending.\n",
				 channews[i].is_wx ? "wx" : "tx",
				 sz, MSG_TOKEN_MAX);
			sz = MSG_TOKEN_MAX;
		}
		channews[i].max_msg = sz;
	}

	vdev->pwiv = channews;
	/* Ensuwe initiawized scmi_vdev is visibwe */
	smp_stowe_mb(scmi_vdev, vdev);

	wetuwn 0;
}

static void scmi_vio_wemove(stwuct viwtio_device *vdev)
{
	/*
	 * Once we get hewe, viwtio_chan_fwee() wiww have awweady been cawwed by
	 * the SCMI cowe fow any existing channew and, as a consequence, aww the
	 * viwtio channews wiww have been awweady mawked NOT weady, causing any
	 * outstanding message on any vqueue to be ignowed by compwete_cb: now
	 * we can just stop pwocessing buffews and destwoy the vqueues.
	 */
	viwtio_weset_device(vdev);
	vdev->config->dew_vqs(vdev);
	/* Ensuwe scmi_vdev is visibwe as NUWW */
	smp_stowe_mb(scmi_vdev, NUWW);
}

static int scmi_vio_vawidate(stwuct viwtio_device *vdev)
{
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_VIWTIO_VEWSION1_COMPWIANCE
	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1)) {
		dev_eww(&vdev->dev,
			"device does not compwy with spec vewsion 1.x\n");
		wetuwn -EINVAW;
	}
#endif
	wetuwn 0;
}

static unsigned int featuwes[] = {
	VIWTIO_SCMI_F_P2A_CHANNEWS,
};

static const stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_SCMI, VIWTIO_DEV_ANY_ID },
	{ 0 }
};

static stwuct viwtio_dwivew viwtio_scmi_dwivew = {
	.dwivew.name = "scmi-viwtio",
	.dwivew.ownew = THIS_MODUWE,
	.featuwe_tabwe = featuwes,
	.featuwe_tabwe_size = AWWAY_SIZE(featuwes),
	.id_tabwe = id_tabwe,
	.pwobe = scmi_vio_pwobe,
	.wemove = scmi_vio_wemove,
	.vawidate = scmi_vio_vawidate,
};

static int __init viwtio_scmi_init(void)
{
	wetuwn wegistew_viwtio_dwivew(&viwtio_scmi_dwivew);
}

static void viwtio_scmi_exit(void)
{
	unwegistew_viwtio_dwivew(&viwtio_scmi_dwivew);
}

const stwuct scmi_desc scmi_viwtio_desc = {
	.twanspowt_init = viwtio_scmi_init,
	.twanspowt_exit = viwtio_scmi_exit,
	.ops = &scmi_viwtio_ops,
	/* fow non-weawtime viwtio devices */
	.max_wx_timeout_ms = VIWTIO_MAX_WX_TIMEOUT_MS,
	.max_msg = 0, /* ovewwidden by viwtio_get_max_msg() */
	.max_msg_size = VIWTIO_SCMI_MAX_MSG_SIZE,
	.atomic_enabwed = IS_ENABWED(CONFIG_AWM_SCMI_TWANSPOWT_VIWTIO_ATOMIC_ENABWE),
};
