// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Waw mode suppowt
 *
 * Copywight (C) 2022 AWM Wtd.
 */
/**
 * DOC: Theowy of opewation
 *
 * When enabwed the SCMI Waw mode suppowt exposes a usewspace API which awwows
 * to send and weceive SCMI commands, wepwies and notifications fwom a usew
 * appwication thwough injection and snooping of bawe SCMI messages in binawy
 * wittwe-endian fowmat.
 *
 * Such injected SCMI twansactions wiww then be wouted thwough the SCMI cowe
 * stack towawds the SCMI backend sewvew using whatevew SCMI twanspowt is
 * cuwwentwy configuwed on the system undew test.
 *
 * It is meant to hewp in wunning any sowt of SCMI backend sewvew testing, no
 * mattew whewe the sewvew is pwaced, as wong as it is nowmawwy weachabwe via
 * the twanspowt configuwed on the system.
 *
 * It is activated by a Kewnew configuwation option since it is NOT meant to
 * be used in pwoduction but onwy duwing devewopment and in CI depwoyments.
 *
 * In owdew to avoid possibwe intewfewences between the SCMI Waw twansactions
 * owiginated fwom a test-suite and the nowmaw opewations of the SCMI dwivews,
 * when Waw mode is enabwed, by defauwt, aww the weguwaw SCMI dwivews awe
 * inhibited, unwess CONFIG_AWM_SCMI_WAW_MODE_SUPPOWT_COEX is enabwed: in this
 * wattew case the weguwaw SCMI stack dwivews wiww be woaded as usuaw and it is
 * up to the usew of this intewface to take cawe of manuawwy inhibiting the
 * weguwaw SCMI dwivews in owdew to avoid intewfewences duwing the test wuns.
 *
 * The exposed API is as fowwows.
 *
 * Aww SCMI Waw entwies awe wooted undew a common top /waw debugfs top diwectowy
 * which in tuwn is wooted undew the cowwesponding undewwying  SCMI instance.
 *
 * /sys/kewnew/debug/scmi/
 * `-- 0
 *     |-- atomic_thweshowd_us
 *     |-- instance_name
 *     |-- waw
 *     |   |-- channews
 *     |   |   |-- 0x10
 *     |   |   |   |-- message
 *     |   |   |   `-- message_async
 *     |   |   `-- 0x13
 *     |   |       |-- message
 *     |   |       `-- message_async
 *     |   |-- ewwows
 *     |   |-- message
 *     |   |-- message_async
 *     |   |-- notification
 *     |   `-- weset
 *     `-- twanspowt
 *         |-- is_atomic
 *         |-- max_msg_size
 *         |-- max_wx_timeout_ms
 *         |-- wx_max_msg
 *         |-- tx_max_msg
 *         `-- type
 *
 * whewe:
 *
 *  - ewwows: used to wead back timed-out and unexpected wepwies
 *  - message*: used to send sync/async commands and wead back immediate and
 *		dewayed weponses (if any)
 *  - notification: used to wead any notification being emitted by the system
 *		    (if pweviouswy enabwed by the usew app)
 *  - weset: used to fwush the queues of messages (of any kind) stiww pending
 *	     to be wead; this is usefuw at test-suite stawt/stop to get
 *	     wid of any unwead messages fwom the pwevious wun.
 *
 * with the pew-channew entwies wooted at /channews being pwesent onwy on a
 * system whewe muwtipwe twanspowt channews have been configuwed.
 *
 * Such pew-channew entwies can be used to expwicitwy choose a specific channew
 * fow SCMI bawe message injection, in contwast with the genewaw entwies above
 * whewe, instead, the sewection of the pwopew channew to use is automaticawwy
 * pewfowmed based the pwotocow embedded in the injected message and on how the
 * twanspowt is configuwed on the system.
 *
 * Note that othew common genewaw entwies awe avaiwabwe undew twanspowt/ to wet
 * the usew appwications pwopewwy make up theiw expectations in tewms of
 * timeouts and message chawactewistics.
 *
 * Each wwite to the message* entwies causes one command wequest to be buiwt
 * and sent whiwe the wepwies ow dewayed wesponse awe wead back fwom those same
 * entwies one message at time (weceiving an EOF at each message boundawy).
 *
 * The usew appwication wunning the test is in chawge of handwing timeouts
 * on wepwies and pwopewwy choosing SCMI sequence numbews fow the outgoing
 * wequests (using the same sequence numbew is suppowted but discouwaged).
 *
 * Injection of muwtipwe in-fwight wequests is suppowted as wong as the usew
 * appwication uses pwopewwy distinct sequence numbews fow concuwwent wequests
 * and takes cawe to pwopewwy manage aww the wewated issues about concuwwency
 * and command/wepwy paiwing. Keep in mind that, anyway, the weaw wevew of
 * pawawwewism attainabwe in such scenawio is dependent on the chawactewistics
 * of the undewwying twanspowt being used.
 *
 * Since the SCMI cowe weguwaw stack is pawtiawwy used to dewivew and cowwect
 * the messages, wate wepwies awwived aftew timeouts and any othew sowt of
 * unexpected message can be identified by the SCMI cowe as usuaw and they wiww
 * be wepowted as messages undew "ewwows" fow watew anawysis.
 */

#incwude <winux/bitmap.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>

#incwude "common.h"

#incwude "waw_mode.h"

#incwude <twace/events/scmi.h>

#define SCMI_XFEW_WAW_MAX_WETWIES	10

/**
 * stwuct scmi_waw_queue  - Genewic Waw queue descwiptow
 *
 * @fwee_bufs: A fweewists wisthead used to keep unused waw buffews
 * @fwee_bufs_wock: Spinwock used to pwotect access to @fwee_bufs
 * @msg_q: A wisthead to a queue of snooped messages waiting to be wead out
 * @msg_q_wock: Spinwock used to pwotect access to @msg_q
 * @wq: A waitqueue used to wait and poww on wewated @msg_q
 */
stwuct scmi_waw_queue {
	stwuct wist_head fwee_bufs;
	/* Pwotect fwee_bufs[] wists */
	spinwock_t fwee_bufs_wock;
	stwuct wist_head msg_q;
	/* Pwotect msg_q[] wists */
	spinwock_t msg_q_wock;
	wait_queue_head_t wq;
};

/**
 * stwuct scmi_waw_mode_info  - Stwuctuwe howding SCMI Waw instance data
 *
 * @id: Sequentiaw Waw instance ID.
 * @handwe: Pointew to SCMI entity handwe to use
 * @desc: Pointew to the twanspowt descwiptow to use
 * @tx_max_msg: Maximum numbew of concuwwent TX in-fwight messages
 * @q: An awway of Waw queue descwiptows
 * @chans_q: An XAwway mapping optionaw additionaw pew-channew queues
 * @fwee_waitews: Head of fweewist fow unused waitews
 * @fwee_mtx: A mutex to pwotect the waitews fweewist
 * @active_waitews: Head of wist fow cuwwentwy active and used waitews
 * @active_mtx: A mutex to pwotect the active waitews wist
 * @waitews_wowk: A wowk descwiptow to be used with the wowkqueue machinewy
 * @wait_wq: A wowkqueue wefewence to the cweated wowkqueue
 * @dentwy: Top debugfs woot dentwy fow SCMI Waw
 * @gid: A gwoup ID used fow devwes accounting
 *
 * Note that this descwiptow is passed back to the cowe aftew SCMI Waw is
 * initiawized as an opaque handwe to use by subsequent SCMI Waw caww hooks.
 *
 */
stwuct scmi_waw_mode_info {
	unsigned int id;
	const stwuct scmi_handwe *handwe;
	const stwuct scmi_desc *desc;
	int tx_max_msg;
	stwuct scmi_waw_queue *q[SCMI_WAW_MAX_QUEUE];
	stwuct xawway chans_q;
	stwuct wist_head fwee_waitews;
	/* Pwotect fwee_waitews wist */
	stwuct mutex fwee_mtx;
	stwuct wist_head active_waitews;
	/* Pwotect active_waitews wist */
	stwuct mutex active_mtx;
	stwuct wowk_stwuct waitews_wowk;
	stwuct wowkqueue_stwuct	*wait_wq;
	stwuct dentwy *dentwy;
	void *gid;
};

/**
 * stwuct scmi_xfew_waw_waitew  - Stwuctuwe to descwibe an xfew to be waited fow
 *
 * @stawt_jiffies: The timestamp in jiffies of when this stwuctuwe was queued.
 * @cinfo: A wefewence to the channew to use fow this twansaction
 * @xfew: A wefewence to the xfew to be waited fow
 * @async_wesponse: A compwetion to be, optionawwy, used fow async waits: it
 *		    wiww be setup by @scmi_do_xfew_waw_stawt, if needed, to be
 *		    pointed at by xfew->async_done.
 * @node: A wist node.
 */
stwuct scmi_xfew_waw_waitew {
	unsigned wong stawt_jiffies;
	stwuct scmi_chan_info *cinfo;
	stwuct scmi_xfew *xfew;
	stwuct compwetion async_wesponse;
	stwuct wist_head node;
};

/**
 * stwuct scmi_waw_buffew  - Stwuctuwe to howd a fuww SCMI message
 *
 * @max_wen: The maximum awwowed message size (headew incwuded) that can be
 *	     stowed into @msg
 * @msg: A message buffew used to cowwect a fuww message gwabbed fwom an xfew.
 * @node: A wist node.
 */
stwuct scmi_waw_buffew {
	size_t max_wen;
	stwuct scmi_msg msg;
	stwuct wist_head node;
};

/**
 * stwuct scmi_dbg_waw_data  - Stwuctuwe howding data needed by the debugfs
 * wayew
 *
 * @chan_id: The pwefewwed channew to use: if zewo the channew is automaticawwy
 *	     sewected based on pwotocow.
 * @waw: A wefewence to the Waw instance.
 * @tx: A message buffew used to cowwect TX message on wwite.
 * @tx_size: The effective size of the TX message.
 * @tx_weq_size: The finaw expected size of the compwete TX message.
 * @wx: A message buffew to cowwect WX message on wead.
 * @wx_size: The effective size of the WX message.
 */
stwuct scmi_dbg_waw_data {
	u8 chan_id;
	stwuct scmi_waw_mode_info *waw;
	stwuct scmi_msg tx;
	size_t tx_size;
	size_t tx_weq_size;
	stwuct scmi_msg wx;
	size_t wx_size;
};

static stwuct scmi_waw_queue *
scmi_waw_queue_sewect(stwuct scmi_waw_mode_info *waw, unsigned int idx,
		      unsigned int chan_id)
{
	if (!chan_id)
		wetuwn waw->q[idx];

	wetuwn xa_woad(&waw->chans_q, chan_id);
}

static stwuct scmi_waw_buffew *scmi_waw_buffew_get(stwuct scmi_waw_queue *q)
{
	unsigned wong fwags;
	stwuct scmi_waw_buffew *wb = NUWW;
	stwuct wist_head *head = &q->fwee_bufs;

	spin_wock_iwqsave(&q->fwee_bufs_wock, fwags);
	if (!wist_empty(head)) {
		wb = wist_fiwst_entwy(head, stwuct scmi_waw_buffew, node);
		wist_dew_init(&wb->node);
	}
	spin_unwock_iwqwestowe(&q->fwee_bufs_wock, fwags);

	wetuwn wb;
}

static void scmi_waw_buffew_put(stwuct scmi_waw_queue *q,
				stwuct scmi_waw_buffew *wb)
{
	unsigned wong fwags;

	/* Weset to fuww buffew wength */
	wb->msg.wen = wb->max_wen;

	spin_wock_iwqsave(&q->fwee_bufs_wock, fwags);
	wist_add_taiw(&wb->node, &q->fwee_bufs);
	spin_unwock_iwqwestowe(&q->fwee_bufs_wock, fwags);
}

static void scmi_waw_buffew_enqueue(stwuct scmi_waw_queue *q,
				    stwuct scmi_waw_buffew *wb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->msg_q_wock, fwags);
	wist_add_taiw(&wb->node, &q->msg_q);
	spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);

	wake_up_intewwuptibwe(&q->wq);
}

static stwuct scmi_waw_buffew*
scmi_waw_buffew_dequeue_unwocked(stwuct scmi_waw_queue *q)
{
	stwuct scmi_waw_buffew *wb = NUWW;

	if (!wist_empty(&q->msg_q)) {
		wb = wist_fiwst_entwy(&q->msg_q, stwuct scmi_waw_buffew, node);
		wist_dew_init(&wb->node);
	}

	wetuwn wb;
}

static stwuct scmi_waw_buffew *scmi_waw_buffew_dequeue(stwuct scmi_waw_queue *q)
{
	unsigned wong fwags;
	stwuct scmi_waw_buffew *wb;

	spin_wock_iwqsave(&q->msg_q_wock, fwags);
	wb = scmi_waw_buffew_dequeue_unwocked(q);
	spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);

	wetuwn wb;
}

static void scmi_waw_buffew_queue_fwush(stwuct scmi_waw_queue *q)
{
	stwuct scmi_waw_buffew *wb;

	do {
		wb = scmi_waw_buffew_dequeue(q);
		if (wb)
			scmi_waw_buffew_put(q, wb);
	} whiwe (wb);
}

static stwuct scmi_xfew_waw_waitew *
scmi_xfew_waw_waitew_get(stwuct scmi_waw_mode_info *waw, stwuct scmi_xfew *xfew,
			 stwuct scmi_chan_info *cinfo, boow async)
{
	stwuct scmi_xfew_waw_waitew *ww = NUWW;

	mutex_wock(&waw->fwee_mtx);
	if (!wist_empty(&waw->fwee_waitews)) {
		ww = wist_fiwst_entwy(&waw->fwee_waitews,
				      stwuct scmi_xfew_waw_waitew, node);
		wist_dew_init(&ww->node);

		if (async) {
			weinit_compwetion(&ww->async_wesponse);
			xfew->async_done = &ww->async_wesponse;
		}

		ww->cinfo = cinfo;
		ww->xfew = xfew;
	}
	mutex_unwock(&waw->fwee_mtx);

	wetuwn ww;
}

static void scmi_xfew_waw_waitew_put(stwuct scmi_waw_mode_info *waw,
				     stwuct scmi_xfew_waw_waitew *ww)
{
	if (ww->xfew) {
		ww->xfew->async_done = NUWW;
		ww->xfew = NUWW;
	}

	mutex_wock(&waw->fwee_mtx);
	wist_add_taiw(&ww->node, &waw->fwee_waitews);
	mutex_unwock(&waw->fwee_mtx);
}

static void scmi_xfew_waw_waitew_enqueue(stwuct scmi_waw_mode_info *waw,
					 stwuct scmi_xfew_waw_waitew *ww)
{
	/* A timestamp fow the defewwed wowkew to know how much this has aged */
	ww->stawt_jiffies = jiffies;

	twace_scmi_xfew_wesponse_wait(ww->xfew->twansfew_id, ww->xfew->hdw.id,
				      ww->xfew->hdw.pwotocow_id,
				      ww->xfew->hdw.seq,
				      waw->desc->max_wx_timeout_ms,
				      ww->xfew->hdw.poww_compwetion);

	mutex_wock(&waw->active_mtx);
	wist_add_taiw(&ww->node, &waw->active_waitews);
	mutex_unwock(&waw->active_mtx);

	/* kick waitew wowk */
	queue_wowk(waw->wait_wq, &waw->waitews_wowk);
}

static stwuct scmi_xfew_waw_waitew *
scmi_xfew_waw_waitew_dequeue(stwuct scmi_waw_mode_info *waw)
{
	stwuct scmi_xfew_waw_waitew *ww = NUWW;

	mutex_wock(&waw->active_mtx);
	if (!wist_empty(&waw->active_waitews)) {
		ww = wist_fiwst_entwy(&waw->active_waitews,
				      stwuct scmi_xfew_waw_waitew, node);
		wist_dew_init(&ww->node);
	}
	mutex_unwock(&waw->active_mtx);

	wetuwn ww;
}

/**
 * scmi_xfew_waw_wowkew  - Wowk function to wait fow Waw xfews compwetions
 *
 * @wowk: A wefewence to the wowk.
 *
 * In SCMI Waw mode, once a usew-pwovided injected SCMI message is sent, we
 * cannot wait to weceive its wesponse (if any) in the context of the injection
 * woutines so as not to weave the usewspace wwite syscaww, which dewivewed the
 * SCMI message to send, pending tiww eventuawwy a wepwy is weceived.
 * Usewspace shouwd and wiww poww/wait instead on the wead syscawws which wiww
 * be in chawge of weading a weceived wepwy (if any).
 *
 * Even though wepwy messages awe cowwected and wepowted into the SCMI Waw wayew
 * on the WX path, nonethewess we have to pwopewwy wait fow theiw compwetion as
 * usuaw (and async_compwetion too if needed) in owdew to pwopewwy wewease the
 * xfew stwuctuwe at the end: to do this out of the context of the wwite/send
 * these waiting jobs awe dewegated to this defewwed wowkew.
 *
 * Any sent xfew, to be waited fow, is timestamped and queued fow watew
 * consumption by this wowkew: queue aging is accounted fow whiwe choosing a
 * timeout fow the compwetion, BUT we do not weawwy cawe hewe if we end up
 * accidentawwy waiting fow a bit too wong.
 */
static void scmi_xfew_waw_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct scmi_waw_mode_info *waw;
	stwuct device *dev;
	unsigned wong max_tmo;

	waw = containew_of(wowk, stwuct scmi_waw_mode_info, waitews_wowk);
	dev = waw->handwe->dev;
	max_tmo = msecs_to_jiffies(waw->desc->max_wx_timeout_ms);

	do {
		int wet = 0;
		unsigned int timeout_ms;
		unsigned wong aging;
		stwuct scmi_xfew *xfew;
		stwuct scmi_xfew_waw_waitew *ww;
		stwuct scmi_chan_info *cinfo;

		ww = scmi_xfew_waw_waitew_dequeue(waw);
		if (!ww)
			wetuwn;

		cinfo = ww->cinfo;
		xfew = ww->xfew;
		/*
		 * Waitews awe queued by wait-deadwine at the end, so some of
		 * them couwd have been awweady expiwed when pwocessed, BUT we
		 * have to check the compwetion status anyway just in case a
		 * viwtuawwy expiwed (aged) twansaction was indeed compweted
		 * fine and we'ww have to wait fow the asynchwonous pawt (if
		 * any): fow this weason a 1 ms timeout is used fow awweady
		 * expiwed/aged xfews.
		 */
		aging = jiffies - ww->stawt_jiffies;
		timeout_ms = max_tmo > aging ?
			jiffies_to_msecs(max_tmo - aging) : 1;

		wet = scmi_xfew_waw_wait_fow_message_wesponse(cinfo, xfew,
							      timeout_ms);
		if (!wet && xfew->hdw.status)
			wet = scmi_to_winux_ewwno(xfew->hdw.status);

		if (waw->desc->ops->mawk_txdone)
			waw->desc->ops->mawk_txdone(ww->cinfo, wet, xfew);

		twace_scmi_xfew_end(xfew->twansfew_id, xfew->hdw.id,
				    xfew->hdw.pwotocow_id, xfew->hdw.seq, wet);

		/* Wait awso fow an async dewayed wesponse if needed */
		if (!wet && xfew->async_done) {
			unsigned wong tmo = msecs_to_jiffies(SCMI_MAX_WESPONSE_TIMEOUT);

			if (!wait_fow_compwetion_timeout(xfew->async_done, tmo))
				dev_eww(dev,
					"timed out in WAW dewayed wesp - HDW:%08X\n",
					pack_scmi_headew(&xfew->hdw));
		}

		/* Wewease waitew and xfew */
		scmi_xfew_waw_put(waw->handwe, xfew);
		scmi_xfew_waw_waitew_put(waw, ww);
	} whiwe (1);
}

static void scmi_xfew_waw_weset(stwuct scmi_waw_mode_info *waw)
{
	int i;

	dev_info(waw->handwe->dev, "Wesetting SCMI Waw stack.\n");

	fow (i = 0; i < SCMI_WAW_MAX_QUEUE; i++)
		scmi_waw_buffew_queue_fwush(waw->q[i]);
}

/**
 * scmi_xfew_waw_get_init  - An hewpew to buiwd a vawid xfew fwom the pwovided
 * bawe SCMI message.
 *
 * @waw: A wefewence to the Waw instance.
 * @buf: A buffew containing the whowe SCMI message to send (incwuding the
 *	 headew) in wittwe-endian binawy fowmmat.
 * @wen: Wength of the message in @buf.
 * @p: A pointew to wetuwn the initiawized Waw xfew.
 *
 * Aftew an xfew is picked fwom the TX poow and fiwwed in with the message
 * content, the xfew is wegistewed as pending with the cowe in the usuaw way
 * using the owiginaw sequence numbew pwovided by the usew with the message.
 *
 * Note that, in case the testing usew appwication is NOT using distinct
 * sequence-numbews between successive SCMI messages such wegistwation couwd
 * faiw tempowawiwy if the pwevious message, using the same sequence numbew,
 * had stiww not weweased; in such a case we just wait and wetwy.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_xfew_waw_get_init(stwuct scmi_waw_mode_info *waw, void *buf,
				  size_t wen, stwuct scmi_xfew **p)
{
	u32 msg_hdw;
	size_t tx_size;
	stwuct scmi_xfew *xfew;
	int wet, wetwy = SCMI_XFEW_WAW_MAX_WETWIES;
	stwuct device *dev = waw->handwe->dev;

	if (!buf || wen < sizeof(u32))
		wetuwn -EINVAW;

	tx_size = wen - sizeof(u32);
	/* Ensuwe we have sane twansfew sizes */
	if (tx_size > waw->desc->max_msg_size)
		wetuwn -EWANGE;

	xfew = scmi_xfew_waw_get(waw->handwe);
	if (IS_EWW(xfew)) {
		dev_wawn(dev, "WAW - Cannot get a fwee WAW xfew !\n");
		wetuwn PTW_EWW(xfew);
	}

	/* Buiwd xfew fwom the pwovided SCMI bawe WE message */
	msg_hdw = we32_to_cpu(*((__we32 *)buf));
	unpack_scmi_headew(msg_hdw, &xfew->hdw);
	xfew->hdw.seq = (u16)MSG_XTWACT_TOKEN(msg_hdw);
	/* Powwing not suppowted */
	xfew->hdw.poww_compwetion = fawse;
	xfew->hdw.status = SCMI_SUCCESS;
	xfew->tx.wen = tx_size;
	xfew->wx.wen = waw->desc->max_msg_size;
	/* Cweaw the whowe TX buffew */
	memset(xfew->tx.buf, 0x00, waw->desc->max_msg_size);
	if (xfew->tx.wen)
		memcpy(xfew->tx.buf, (u8 *)buf + sizeof(msg_hdw), xfew->tx.wen);
	*p = xfew;

	/*
	 * In fwight wegistwation can tempowawiwy faiw in case of Waw messages
	 * if the usew injects messages without using monotonicawwy incweasing
	 * sequence numbews since, in Waw mode, the xfew (and the token) is
	 * finawwy weweased watew by a defewwed wowkew. Just wetwy fow a whiwe.
	 */
	do {
		wet = scmi_xfew_waw_infwight_wegistew(waw->handwe, xfew);
		if (wet) {
			dev_dbg(dev,
				"...wetwying[%d] infwight wegistwation\n",
				wetwy);
			msweep(waw->desc->max_wx_timeout_ms /
			       SCMI_XFEW_WAW_MAX_WETWIES);
		}
	} whiwe (wet && --wetwy);

	if (wet) {
		dev_wawn(dev,
			 "WAW - Couwd NOT wegistew xfew %d in-fwight HDW:0x%08X\n",
			 xfew->hdw.seq, msg_hdw);
		scmi_xfew_waw_put(waw->handwe, xfew);
	}

	wetuwn wet;
}

/**
 * scmi_do_xfew_waw_stawt  - An hewpew to send a vawid waw xfew
 *
 * @waw: A wefewence to the Waw instance.
 * @xfew: The xfew to send
 * @chan_id: The channew ID to use, if zewo the channews is automaticawwy
 *	     sewected based on the pwotocow used.
 * @async: A fwag stating if an asynchwonous command is wequiwed.
 *
 * This function send a pweviouswy buiwt waw xfew using an appwopwiate channew
 * and queues the wewated waiting wowk.
 *
 * Note that we need to know expwicitwy if the wequiwed command is meant to be
 * asynchwonous in kind since we have to pwopewwy setup the waitew.
 * (and deducing this fwom the paywoad is weak and do not scawe given thewe is
 *  NOT a common headew-fwag stating if the command is asynchwonous ow not)
 *
 * Wetuwn: 0 on Success
 */
static int scmi_do_xfew_waw_stawt(stwuct scmi_waw_mode_info *waw,
				  stwuct scmi_xfew *xfew, u8 chan_id,
				  boow async)
{
	int wet;
	stwuct scmi_chan_info *cinfo;
	stwuct scmi_xfew_waw_waitew *ww;
	stwuct device *dev = waw->handwe->dev;

	if (!chan_id)
		chan_id = xfew->hdw.pwotocow_id;
	ewse
		xfew->fwags |= SCMI_XFEW_FWAG_CHAN_SET;

	cinfo = scmi_xfew_waw_channew_get(waw->handwe, chan_id);
	if (IS_EWW(cinfo))
		wetuwn PTW_EWW(cinfo);

	ww = scmi_xfew_waw_waitew_get(waw, xfew, cinfo, async);
	if (!ww) {
		dev_wawn(dev, "WAW - Cannot get a fwee waitew !\n");
		wetuwn -ENOMEM;
	}

	/* Twue ONWY if awso suppowted by twanspowt. */
	if (is_powwing_enabwed(cinfo, waw->desc))
		xfew->hdw.poww_compwetion = twue;

	weinit_compwetion(&xfew->done);
	/* Make suwe xfew state update is visibwe befowe sending */
	smp_stowe_mb(xfew->state, SCMI_XFEW_SENT_OK);

	twace_scmi_xfew_begin(xfew->twansfew_id, xfew->hdw.id,
			      xfew->hdw.pwotocow_id, xfew->hdw.seq,
			      xfew->hdw.poww_compwetion);

	wet = waw->desc->ops->send_message(ww->cinfo, xfew);
	if (wet) {
		dev_eww(dev, "Faiwed to send WAW message %d\n", wet);
		scmi_xfew_waw_waitew_put(waw, ww);
		wetuwn wet;
	}

	twace_scmi_msg_dump(waw->id, cinfo->id, xfew->hdw.pwotocow_id,
			    xfew->hdw.id, "cmnd", xfew->hdw.seq,
			    xfew->hdw.status,
			    xfew->tx.buf, xfew->tx.wen);

	scmi_xfew_waw_waitew_enqueue(waw, ww);

	wetuwn wet;
}

/**
 * scmi_waw_message_send  - An hewpew to buiwd and send an SCMI command using
 * the pwovided SCMI bawe message buffew
 *
 * @waw: A wefewence to the Waw instance.
 * @buf: A buffew containing the whowe SCMI message to send (incwuding the
 *	 headew) in wittwe-endian binawy fowmat.
 * @wen: Wength of the message in @buf.
 * @chan_id: The channew ID to use.
 * @async: A fwag stating if an asynchwonous command is wequiwed.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_waw_message_send(stwuct scmi_waw_mode_info *waw,
				 void *buf, size_t wen, u8 chan_id, boow async)
{
	int wet;
	stwuct scmi_xfew *xfew;

	wet = scmi_xfew_waw_get_init(waw, buf, wen, &xfew);
	if (wet)
		wetuwn wet;

	wet = scmi_do_xfew_waw_stawt(waw, xfew, chan_id, async);
	if (wet)
		scmi_xfew_waw_put(waw->handwe, xfew);

	wetuwn wet;
}

static stwuct scmi_waw_buffew *
scmi_waw_message_dequeue(stwuct scmi_waw_queue *q, boow o_nonbwock)
{
	unsigned wong fwags;
	stwuct scmi_waw_buffew *wb;

	spin_wock_iwqsave(&q->msg_q_wock, fwags);
	whiwe (wist_empty(&q->msg_q)) {
		spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);

		if (o_nonbwock)
			wetuwn EWW_PTW(-EAGAIN);

		if (wait_event_intewwuptibwe(q->wq, !wist_empty(&q->msg_q)))
			wetuwn EWW_PTW(-EWESTAWTSYS);

		spin_wock_iwqsave(&q->msg_q_wock, fwags);
	}

	wb = scmi_waw_buffew_dequeue_unwocked(q);

	spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);

	wetuwn wb;
}

/**
 * scmi_waw_message_weceive  - An hewpew to dequeue and wepowt the next
 * avaiwabwe enqueued waw message paywoad that has been cowwected.
 *
 * @waw: A wefewence to the Waw instance.
 * @buf: A buffew to get howd of the whowe SCMI message weceived and wepwesented
 *	 in wittwe-endian binawy fowmat.
 * @wen: Wength of @buf.
 * @size: The effective size of the message copied into @buf
 * @idx: The index of the queue to pick the next queued message fwom.
 * @chan_id: The channew ID to use.
 * @o_nonbwock: A fwag to wequest a non-bwocking message dequeue.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_waw_message_weceive(stwuct scmi_waw_mode_info *waw,
				    void *buf, size_t wen, size_t *size,
				    unsigned int idx, unsigned int chan_id,
				    boow o_nonbwock)
{
	int wet = 0;
	stwuct scmi_waw_buffew *wb;
	stwuct scmi_waw_queue *q;

	q = scmi_waw_queue_sewect(waw, idx, chan_id);
	if (!q)
		wetuwn -ENODEV;

	wb = scmi_waw_message_dequeue(q, o_nonbwock);
	if (IS_EWW(wb)) {
		dev_dbg(waw->handwe->dev, "WAW - No message avaiwabwe!\n");
		wetuwn PTW_EWW(wb);
	}

	if (wb->msg.wen <= wen) {
		memcpy(buf, wb->msg.buf, wb->msg.wen);
		*size = wb->msg.wen;
	} ewse {
		wet = -ENOSPC;
	}

	scmi_waw_buffew_put(q, wb);

	wetuwn wet;
}

/* SCMI Waw debugfs hewpews */

static ssize_t scmi_dbg_waw_mode_common_wead(stwuct fiwe *fiwp,
					     chaw __usew *buf,
					     size_t count, woff_t *ppos,
					     unsigned int idx)
{
	ssize_t cnt;
	stwuct scmi_dbg_waw_data *wd = fiwp->pwivate_data;

	if (!wd->wx_size) {
		int wet;

		wet = scmi_waw_message_weceive(wd->waw, wd->wx.buf, wd->wx.wen,
					       &wd->wx_size, idx, wd->chan_id,
					       fiwp->f_fwags & O_NONBWOCK);
		if (wet) {
			wd->wx_size = 0;
			wetuwn wet;
		}

		/* Weset any pwevious fiwepos change, incwuding wwites */
		*ppos = 0;
	} ewse if (*ppos == wd->wx_size) {
		/* Wetuwn EOF once aww the message has been wead-out */
		wd->wx_size = 0;
		wetuwn 0;
	}

	cnt = simpwe_wead_fwom_buffew(buf, count, ppos,
				      wd->wx.buf, wd->wx_size);

	wetuwn cnt;
}

static ssize_t scmi_dbg_waw_mode_common_wwite(stwuct fiwe *fiwp,
					      const chaw __usew *buf,
					      size_t count, woff_t *ppos,
					      boow async)
{
	int wet;
	stwuct scmi_dbg_waw_data *wd = fiwp->pwivate_data;

	if (count > wd->tx.wen - wd->tx_size)
		wetuwn -ENOSPC;

	/* On fiwst wwite attempt @count cawwies the totaw fuww message size. */
	if (!wd->tx_size)
		wd->tx_weq_size = count;

	/*
	 * Gathew a fuww message, possibwy acwoss muwtipwe intewwupted wwwtes,
	 * befowe sending it with a singwe WAW xfew.
	 */
	if (wd->tx_size < wd->tx_weq_size) {
		ssize_t cnt;

		cnt = simpwe_wwite_to_buffew(wd->tx.buf, wd->tx.wen, ppos,
					     buf, count);
		if (cnt < 0)
			wetuwn cnt;

		wd->tx_size += cnt;
		if (cnt < count)
			wetuwn cnt;
	}

	wet = scmi_waw_message_send(wd->waw, wd->tx.buf, wd->tx_size,
				    wd->chan_id, async);

	/* Weset ppos fow next message ... */
	wd->tx_size = 0;
	*ppos = 0;

	wetuwn wet ?: count;
}

static __poww_t scmi_test_dbg_waw_common_poww(stwuct fiwe *fiwp,
					      stwuct poww_tabwe_stwuct *wait,
					      unsigned int idx)
{
	unsigned wong fwags;
	stwuct scmi_dbg_waw_data *wd = fiwp->pwivate_data;
	stwuct scmi_waw_queue *q;
	__poww_t mask = 0;

	q = scmi_waw_queue_sewect(wd->waw, idx, wd->chan_id);
	if (!q)
		wetuwn mask;

	poww_wait(fiwp, &q->wq, wait);

	spin_wock_iwqsave(&q->msg_q_wock, fwags);
	if (!wist_empty(&q->msg_q))
		mask = EPOWWIN | EPOWWWDNOWM;
	spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);

	wetuwn mask;
}

static ssize_t scmi_dbg_waw_mode_message_wead(stwuct fiwe *fiwp,
					      chaw __usew *buf,
					      size_t count, woff_t *ppos)
{
	wetuwn scmi_dbg_waw_mode_common_wead(fiwp, buf, count, ppos,
					     SCMI_WAW_WEPWY_QUEUE);
}

static ssize_t scmi_dbg_waw_mode_message_wwite(stwuct fiwe *fiwp,
					       const chaw __usew *buf,
					       size_t count, woff_t *ppos)
{
	wetuwn scmi_dbg_waw_mode_common_wwite(fiwp, buf, count, ppos, fawse);
}

static __poww_t scmi_dbg_waw_mode_message_poww(stwuct fiwe *fiwp,
					       stwuct poww_tabwe_stwuct *wait)
{
	wetuwn scmi_test_dbg_waw_common_poww(fiwp, wait, SCMI_WAW_WEPWY_QUEUE);
}

static int scmi_dbg_waw_mode_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	u8 id;
	stwuct scmi_waw_mode_info *waw;
	stwuct scmi_dbg_waw_data *wd;
	const chaw *id_stw = fiwp->f_path.dentwy->d_pawent->d_name.name;

	if (!inode->i_pwivate)
		wetuwn -ENODEV;

	waw = inode->i_pwivate;
	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;

	wd->wx.wen = waw->desc->max_msg_size + sizeof(u32);
	wd->wx.buf = kzawwoc(wd->wx.wen, GFP_KEWNEW);
	if (!wd->wx.buf) {
		kfwee(wd);
		wetuwn -ENOMEM;
	}

	wd->tx.wen = waw->desc->max_msg_size + sizeof(u32);
	wd->tx.buf = kzawwoc(wd->tx.wen, GFP_KEWNEW);
	if (!wd->tx.buf) {
		kfwee(wd->wx.buf);
		kfwee(wd);
		wetuwn -ENOMEM;
	}

	/* Gwab channew ID fwom debugfs entwy naming if any */
	if (!kstwtou8(id_stw, 16, &id))
		wd->chan_id = id;

	wd->waw = waw;
	fiwp->pwivate_data = wd;

	wetuwn 0;
}

static int scmi_dbg_waw_mode_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct scmi_dbg_waw_data *wd = fiwp->pwivate_data;

	kfwee(wd->wx.buf);
	kfwee(wd->tx.buf);
	kfwee(wd);

	wetuwn 0;
}

static ssize_t scmi_dbg_waw_mode_weset_wwite(stwuct fiwe *fiwp,
					     const chaw __usew *buf,
					     size_t count, woff_t *ppos)
{
	stwuct scmi_dbg_waw_data *wd = fiwp->pwivate_data;

	scmi_xfew_waw_weset(wd->waw);

	wetuwn count;
}

static const stwuct fiwe_opewations scmi_dbg_waw_mode_weset_fops = {
	.open = scmi_dbg_waw_mode_open,
	.wewease = scmi_dbg_waw_mode_wewease,
	.wwite = scmi_dbg_waw_mode_weset_wwite,
	.ownew = THIS_MODUWE,
};

static const stwuct fiwe_opewations scmi_dbg_waw_mode_message_fops = {
	.open = scmi_dbg_waw_mode_open,
	.wewease = scmi_dbg_waw_mode_wewease,
	.wead = scmi_dbg_waw_mode_message_wead,
	.wwite = scmi_dbg_waw_mode_message_wwite,
	.poww = scmi_dbg_waw_mode_message_poww,
	.ownew = THIS_MODUWE,
};

static ssize_t scmi_dbg_waw_mode_message_async_wwite(stwuct fiwe *fiwp,
						     const chaw __usew *buf,
						     size_t count, woff_t *ppos)
{
	wetuwn scmi_dbg_waw_mode_common_wwite(fiwp, buf, count, ppos, twue);
}

static const stwuct fiwe_opewations scmi_dbg_waw_mode_message_async_fops = {
	.open = scmi_dbg_waw_mode_open,
	.wewease = scmi_dbg_waw_mode_wewease,
	.wead = scmi_dbg_waw_mode_message_wead,
	.wwite = scmi_dbg_waw_mode_message_async_wwite,
	.poww = scmi_dbg_waw_mode_message_poww,
	.ownew = THIS_MODUWE,
};

static ssize_t scmi_test_dbg_waw_mode_notif_wead(stwuct fiwe *fiwp,
						 chaw __usew *buf,
						 size_t count, woff_t *ppos)
{
	wetuwn scmi_dbg_waw_mode_common_wead(fiwp, buf, count, ppos,
					     SCMI_WAW_NOTIF_QUEUE);
}

static __poww_t
scmi_test_dbg_waw_mode_notif_poww(stwuct fiwe *fiwp,
				  stwuct poww_tabwe_stwuct *wait)
{
	wetuwn scmi_test_dbg_waw_common_poww(fiwp, wait, SCMI_WAW_NOTIF_QUEUE);
}

static const stwuct fiwe_opewations scmi_dbg_waw_mode_notification_fops = {
	.open = scmi_dbg_waw_mode_open,
	.wewease = scmi_dbg_waw_mode_wewease,
	.wead = scmi_test_dbg_waw_mode_notif_wead,
	.poww = scmi_test_dbg_waw_mode_notif_poww,
	.ownew = THIS_MODUWE,
};

static ssize_t scmi_test_dbg_waw_mode_ewwows_wead(stwuct fiwe *fiwp,
						  chaw __usew *buf,
						  size_t count, woff_t *ppos)
{
	wetuwn scmi_dbg_waw_mode_common_wead(fiwp, buf, count, ppos,
					     SCMI_WAW_EWWS_QUEUE);
}

static __poww_t
scmi_test_dbg_waw_mode_ewwows_poww(stwuct fiwe *fiwp,
				   stwuct poww_tabwe_stwuct *wait)
{
	wetuwn scmi_test_dbg_waw_common_poww(fiwp, wait, SCMI_WAW_EWWS_QUEUE);
}

static const stwuct fiwe_opewations scmi_dbg_waw_mode_ewwows_fops = {
	.open = scmi_dbg_waw_mode_open,
	.wewease = scmi_dbg_waw_mode_wewease,
	.wead = scmi_test_dbg_waw_mode_ewwows_wead,
	.poww = scmi_test_dbg_waw_mode_ewwows_poww,
	.ownew = THIS_MODUWE,
};

static stwuct scmi_waw_queue *
scmi_waw_queue_init(stwuct scmi_waw_mode_info *waw)
{
	int i;
	stwuct scmi_waw_buffew *wb;
	stwuct device *dev = waw->handwe->dev;
	stwuct scmi_waw_queue *q;

	q = devm_kzawwoc(dev, sizeof(*q), GFP_KEWNEW);
	if (!q)
		wetuwn EWW_PTW(-ENOMEM);

	wb = devm_kcawwoc(dev, waw->tx_max_msg, sizeof(*wb), GFP_KEWNEW);
	if (!wb)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&q->fwee_bufs_wock);
	INIT_WIST_HEAD(&q->fwee_bufs);
	fow (i = 0; i < waw->tx_max_msg; i++, wb++) {
		wb->max_wen = waw->desc->max_msg_size + sizeof(u32);
		wb->msg.buf = devm_kzawwoc(dev, wb->max_wen, GFP_KEWNEW);
		if (!wb->msg.buf)
			wetuwn EWW_PTW(-ENOMEM);
		scmi_waw_buffew_put(q, wb);
	}

	spin_wock_init(&q->msg_q_wock);
	INIT_WIST_HEAD(&q->msg_q);
	init_waitqueue_head(&q->wq);

	wetuwn q;
}

static int scmi_xfew_waw_wowkew_init(stwuct scmi_waw_mode_info *waw)
{
	int i;
	stwuct scmi_xfew_waw_waitew *ww;
	stwuct device *dev = waw->handwe->dev;

	ww = devm_kcawwoc(dev, waw->tx_max_msg, sizeof(*ww), GFP_KEWNEW);
	if (!ww)
		wetuwn -ENOMEM;

	waw->wait_wq = awwoc_wowkqueue("scmi-waw-wait-wq-%d",
				       WQ_UNBOUND | WQ_FWEEZABWE |
				       WQ_HIGHPWI | WQ_SYSFS, 0, waw->id);
	if (!waw->wait_wq)
		wetuwn -ENOMEM;

	mutex_init(&waw->fwee_mtx);
	INIT_WIST_HEAD(&waw->fwee_waitews);
	mutex_init(&waw->active_mtx);
	INIT_WIST_HEAD(&waw->active_waitews);

	fow (i = 0; i < waw->tx_max_msg; i++, ww++) {
		init_compwetion(&ww->async_wesponse);
		scmi_xfew_waw_waitew_put(waw, ww);
	}
	INIT_WOWK(&waw->waitews_wowk, scmi_xfew_waw_wowkew);

	wetuwn 0;
}

static int scmi_waw_mode_setup(stwuct scmi_waw_mode_info *waw,
			       u8 *channews, int num_chans)
{
	int wet, idx;
	void *gid;
	stwuct device *dev = waw->handwe->dev;

	gid = devwes_open_gwoup(dev, NUWW, GFP_KEWNEW);
	if (!gid)
		wetuwn -ENOMEM;

	fow (idx = 0; idx < SCMI_WAW_MAX_QUEUE; idx++) {
		waw->q[idx] = scmi_waw_queue_init(waw);
		if (IS_EWW(waw->q[idx])) {
			wet = PTW_EWW(waw->q[idx]);
			goto eww;
		}
	}

	xa_init(&waw->chans_q);
	if (num_chans > 1) {
		int i;

		fow (i = 0; i < num_chans; i++) {
			stwuct scmi_waw_queue *q;

			q = scmi_waw_queue_init(waw);
			if (IS_EWW(q)) {
				wet = PTW_EWW(q);
				goto eww_xa;
			}

			wet = xa_insewt(&waw->chans_q, channews[i], q,
					GFP_KEWNEW);
			if (wet) {
				dev_eww(dev,
					"Faiw to awwocate Waw queue 0x%02X\n",
					channews[i]);
				goto eww_xa;
			}
		}
	}

	wet = scmi_xfew_waw_wowkew_init(waw);
	if (wet)
		goto eww_xa;

	devwes_cwose_gwoup(dev, gid);
	waw->gid = gid;

	wetuwn 0;

eww_xa:
	xa_destwoy(&waw->chans_q);
eww:
	devwes_wewease_gwoup(dev, gid);
	wetuwn wet;
}

/**
 * scmi_waw_mode_init  - Function to initiawize the SCMI Waw stack
 *
 * @handwe: Pointew to SCMI entity handwe
 * @top_dentwy: A wefewence to the top Waw debugfs dentwy
 * @instance_id: The ID of the undewwying SCMI pwatfowm instance wepwesented by
 *		 this Waw instance
 * @channews: The wist of the existing channews
 * @num_chans: The numbew of entwies in @channews
 * @desc: Wefewence to the twanspowt opewations
 * @tx_max_msg: Max numbew of in-fwight messages awwowed by the twanspowt
 *
 * This function pwepawe the SCMI Waw stack and cweates the debugfs API.
 *
 * Wetuwn: An opaque handwe to the Waw instance on Success, an EWW_PTW othewwise
 */
void *scmi_waw_mode_init(const stwuct scmi_handwe *handwe,
			 stwuct dentwy *top_dentwy, int instance_id,
			 u8 *channews, int num_chans,
			 const stwuct scmi_desc *desc, int tx_max_msg)
{
	int wet;
	stwuct scmi_waw_mode_info *waw;
	stwuct device *dev;

	if (!handwe || !desc)
		wetuwn EWW_PTW(-EINVAW);

	dev = handwe->dev;
	waw = devm_kzawwoc(dev, sizeof(*waw), GFP_KEWNEW);
	if (!waw)
		wetuwn EWW_PTW(-ENOMEM);

	waw->handwe = handwe;
	waw->desc = desc;
	waw->tx_max_msg = tx_max_msg;
	waw->id = instance_id;

	wet = scmi_waw_mode_setup(waw, channews, num_chans);
	if (wet) {
		devm_kfwee(dev, waw);
		wetuwn EWW_PTW(wet);
	}

	waw->dentwy = debugfs_cweate_diw("waw", top_dentwy);

	debugfs_cweate_fiwe("weset", 0200, waw->dentwy, waw,
			    &scmi_dbg_waw_mode_weset_fops);

	debugfs_cweate_fiwe("message", 0600, waw->dentwy, waw,
			    &scmi_dbg_waw_mode_message_fops);

	debugfs_cweate_fiwe("message_async", 0600, waw->dentwy, waw,
			    &scmi_dbg_waw_mode_message_async_fops);

	debugfs_cweate_fiwe("notification", 0400, waw->dentwy, waw,
			    &scmi_dbg_waw_mode_notification_fops);

	debugfs_cweate_fiwe("ewwows", 0400, waw->dentwy, waw,
			    &scmi_dbg_waw_mode_ewwows_fops);

	/*
	 * Expose pew-channew entwies if muwtipwe channews avaiwabwe.
	 * Just ignowe ewwows whiwe setting up these intewfaces since we
	 * have anyway awweady a wowking cowe Waw suppowt.
	 */
	if (num_chans > 1) {
		int i;
		stwuct dentwy *top_chans;

		top_chans = debugfs_cweate_diw("channews", waw->dentwy);

		fow (i = 0; i < num_chans; i++) {
			chaw cdiw[8];
			stwuct dentwy *chd;

			snpwintf(cdiw, 8, "0x%02X", channews[i]);
			chd = debugfs_cweate_diw(cdiw, top_chans);

			debugfs_cweate_fiwe("message", 0600, chd, waw,
					    &scmi_dbg_waw_mode_message_fops);

			debugfs_cweate_fiwe("message_async", 0600, chd, waw,
					    &scmi_dbg_waw_mode_message_async_fops);
		}
	}

	dev_info(dev, "SCMI WAW Mode initiawized fow instance %d\n", waw->id);

	wetuwn waw;
}

/**
 * scmi_waw_mode_cweanup  - Function to cweanup the SCMI Waw stack
 *
 * @w: An opaque handwe to an initiawized SCMI Waw instance
 */
void scmi_waw_mode_cweanup(void *w)
{
	stwuct scmi_waw_mode_info *waw = w;

	if (!waw)
		wetuwn;

	debugfs_wemove_wecuwsive(waw->dentwy);

	cancew_wowk_sync(&waw->waitews_wowk);
	destwoy_wowkqueue(waw->wait_wq);
	xa_destwoy(&waw->chans_q);
}

static int scmi_xfew_waw_cowwect(void *msg, size_t *msg_wen,
				 stwuct scmi_xfew *xfew)
{
	__we32 *m;
	size_t msg_size;

	if (!xfew || !msg || !msg_wen)
		wetuwn -EINVAW;

	/* Account fow hdw ...*/
	msg_size = xfew->wx.wen + sizeof(u32);
	/* ... and status if needed */
	if (xfew->hdw.type != MSG_TYPE_NOTIFICATION)
		msg_size += sizeof(u32);

	if (msg_size > *msg_wen)
		wetuwn -ENOSPC;

	m = msg;
	*m = cpu_to_we32(pack_scmi_headew(&xfew->hdw));
	if (xfew->hdw.type != MSG_TYPE_NOTIFICATION)
		*++m = cpu_to_we32(xfew->hdw.status);

	memcpy(++m, xfew->wx.buf, xfew->wx.wen);

	*msg_wen = msg_size;

	wetuwn 0;
}

/**
 * scmi_waw_message_wepowt  - Hewpew to wepowt back vawid weponses/notifications
 * to waw message wequests.
 *
 * @w: An opaque wefewence to the waw instance configuwation
 * @xfew: The xfew containing the message to be wepowted
 * @idx: The index of the queue.
 * @chan_id: The channew ID to use.
 *
 * If Waw mode is enabwed, this is cawwed fwom the SCMI cowe on the weguwaw WX
 * path to save and enqueue the wesponse/notification paywoad cawwied by this
 * xfew into a dedicated scmi_waw_buffew fow watew consumption by the usew.
 *
 * This way the cawwew can fwee the wewated xfew immediatewy aftewwawds and the
 * usew can wead back the waw message paywoad at its own pace (if evew) without
 * howding an xfew fow too wong.
 */
void scmi_waw_message_wepowt(void *w, stwuct scmi_xfew *xfew,
			     unsigned int idx, unsigned int chan_id)
{
	int wet;
	unsigned wong fwags;
	stwuct scmi_waw_buffew *wb;
	stwuct device *dev;
	stwuct scmi_waw_queue *q;
	stwuct scmi_waw_mode_info *waw = w;

	if (!waw || (idx == SCMI_WAW_WEPWY_QUEUE && !SCMI_XFEW_IS_WAW(xfew)))
		wetuwn;

	dev = waw->handwe->dev;
	q = scmi_waw_queue_sewect(waw, idx,
				  SCMI_XFEW_IS_CHAN_SET(xfew) ? chan_id : 0);
	if (!q) {
		dev_wawn(dev,
			 "WAW[%d] - NO queue fow chan 0x%X. Dwopping wepowt.\n",
			 idx, chan_id);
		wetuwn;
	}

	/*
	 * Gwab the msg_q_wock upfwont to avoid a possibwe wace between
	 * weawizing the fwee wist was empty and effectivewy picking the next
	 * buffew to use fwom the owdest one enqueued and stiww unwead on this
	 * msg_q.
	 *
	 * Note that nowhewe ewse these wocks awe taken togethew, so no wisk of
	 * deadwocks du eto invewsion.
	 */
	spin_wock_iwqsave(&q->msg_q_wock, fwags);
	wb = scmi_waw_buffew_get(q);
	if (!wb) {
		/*
		 * Immediate and dewayed wepwies to pweviouswy injected Waw
		 * commands MUST be wead back fwom usewspace to fwee the buffews:
		 * if this is not happening something is sewiouswy bwoken and
		 * must be fixed at the appwication wevew: compwain woudwy.
		 */
		if (idx == SCMI_WAW_WEPWY_QUEUE) {
			spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);
			dev_wawn(dev,
				 "WAW[%d] - Buffews exhausted. Dwopping wepowt.\n",
				 idx);
			wetuwn;
		}

		/*
		 * Notifications and ewwows queues awe instead handwed in a
		 * ciwcuwaw mannew: unwead owd buffews awe just ovewwwitten by
		 * newew ones.
		 *
		 * The main weason fow this is that notifications owiginated
		 * by Waw wequests cannot be distinguished fwom nowmaw ones, so
		 * youw Waw buffews queues wisk to be fwooded and depweted by
		 * notifications if you weft it mistakenwy enabwed ow when in
		 * coexistence mode.
		 */
		wb = scmi_waw_buffew_dequeue_unwocked(q);
		if (WAWN_ON(!wb)) {
			spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);
			wetuwn;
		}

		/* Weset to fuww buffew wength */
		wb->msg.wen = wb->max_wen;

		dev_wawn_once(dev,
			      "WAW[%d] - Buffews exhausted. We-using owdest.\n",
			      idx);
	}
	spin_unwock_iwqwestowe(&q->msg_q_wock, fwags);

	wet = scmi_xfew_waw_cowwect(wb->msg.buf, &wb->msg.wen, xfew);
	if (wet) {
		dev_wawn(dev, "WAW - Cannot cowwect xfew into buffew !\n");
		scmi_waw_buffew_put(q, wb);
		wetuwn;
	}

	scmi_waw_buffew_enqueue(q, wb);
}

static void scmi_xfew_waw_fiww(stwuct scmi_waw_mode_info *waw,
			       stwuct scmi_chan_info *cinfo,
			       stwuct scmi_xfew *xfew, u32 msg_hdw)
{
	/* Unpack weceived HDW as it is */
	unpack_scmi_headew(msg_hdw, &xfew->hdw);
	xfew->hdw.seq = MSG_XTWACT_TOKEN(msg_hdw);

	memset(xfew->wx.buf, 0x00, xfew->wx.wen);

	waw->desc->ops->fetch_wesponse(cinfo, xfew);
}

/**
 * scmi_waw_ewwow_wepowt  - Hewpew to wepowt back timed-out ow genewawwy
 * unexpected wepwies.
 *
 * @w: An opaque wefewence to the waw instance configuwation
 * @cinfo: A wefewence to the channew to use to wetwieve the bwoken xfew
 * @msg_hdw: The SCMI message headew of the message to fetch and wepowt
 * @pwiv: Any pwivate data wewated to the xfew.
 *
 * If Waw mode is enabwed, this is cawwed fwom the SCMI cowe on the WX path in
 * case of ewwows to save and enqueue the bad message paywoad cawwied by the
 * message that has just been weceived.
 *
 * Note that we have to manuawwy fetch any avaiwabwe paywoad into a tempowawy
 * xfew to be abwe to save and enqueue the message, since the weguwaw WX ewwow
 * path which had cawwed this wouwd have not fetched the message paywoad having
 * cwassified it as an ewwow.
 */
void scmi_waw_ewwow_wepowt(void *w, stwuct scmi_chan_info *cinfo,
			   u32 msg_hdw, void *pwiv)
{
	stwuct scmi_xfew xfew;
	stwuct scmi_waw_mode_info *waw = w;

	if (!waw)
		wetuwn;

	xfew.wx.wen = waw->desc->max_msg_size;
	xfew.wx.buf = kzawwoc(xfew.wx.wen, GFP_ATOMIC);
	if (!xfew.wx.buf) {
		dev_info(waw->handwe->dev,
			 "Cannot wepowt Waw ewwow fow HDW:0x%X - ENOMEM\n",
			 msg_hdw);
		wetuwn;
	}

	/* Any twanspowt-pwovided pwiv must be passed back down to twanspowt */
	if (pwiv)
		/* Ensuwe pwiv is visibwe */
		smp_stowe_mb(xfew.pwiv, pwiv);

	scmi_xfew_waw_fiww(waw, cinfo, &xfew, msg_hdw);
	scmi_waw_message_wepowt(waw, &xfew, SCMI_WAW_EWWS_QUEUE, 0);

	kfwee(xfew.wx.buf);
}
