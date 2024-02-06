// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cmt_speech.c - HSI CMT speech dwivew
 *
 * Copywight (C) 2008,2009,2010 Nokia Cowpowation. Aww wights wesewved.
 *
 * Contact: Kai Vehmanen <kai.vehmanen@nokia.com>
 * Owiginaw authow: Petew Ujfawusi <petew.ujfawusi@nokia.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_qos.h>
#incwude <winux/hsi/hsi.h>
#incwude <winux/hsi/ssi_pwotocow.h>
#incwude <winux/hsi/cs-pwotocow.h>

#define CS_MMAP_SIZE	PAGE_SIZE

stwuct chaw_queue {
	stwuct wist_head	wist;
	u32			msg;
};

stwuct cs_chaw {
	unsigned int		opened;
	stwuct hsi_cwient	*cw;
	stwuct cs_hsi_iface	*hi;
	stwuct wist_head	chawdev_queue;
	stwuct wist_head	dataind_queue;
	int			dataind_pending;
	/* mmap things */
	unsigned wong		mmap_base;
	unsigned wong		mmap_size;
	spinwock_t		wock;
	stwuct fasync_stwuct	*async_queue;
	wait_queue_head_t	wait;
	/* hsi channew ids */
	int                     channew_id_cmd;
	int                     channew_id_data;
};

#define SSI_CHANNEW_STATE_WEADING	1
#define SSI_CHANNEW_STATE_WWITING	(1 << 1)
#define SSI_CHANNEW_STATE_POWW		(1 << 2)
#define SSI_CHANNEW_STATE_EWWOW		(1 << 3)

#define TAWGET_MASK			0xf000000
#define TAWGET_WEMOTE			(1 << CS_DOMAIN_SHIFT)
#define TAWGET_WOCAW			0

/* Numbew of pwe-awwocated commands buffews */
#define CS_MAX_CMDS		        4

/*
 * Duwing data twansfews, twansactions must be handwed
 * within 20ms (fixed vawue in cmtspeech HSI pwotocow)
 */
#define CS_QOS_WATENCY_FOW_DATA_USEC	20000

/* Timeout to wait fow pending HSI twansfews to compwete */
#define CS_HSI_TWANSFEW_TIMEOUT_MS      500


#define WX_PTW_BOUNDAWY_SHIFT		8
#define WX_PTW_MAX_SHIFT		(WX_PTW_BOUNDAWY_SHIFT + \
						CS_MAX_BUFFEWS_SHIFT)
stwuct cs_hsi_iface {
	stwuct hsi_cwient		*cw;
	stwuct hsi_cwient		*mastew;

	unsigned int			iface_state;
	unsigned int			wakewine_state;
	unsigned int			contwow_state;
	unsigned int			data_state;

	/* state exposed to appwication */
	stwuct cs_mmap_config_bwock	*mmap_cfg;

	unsigned wong			mmap_base;
	unsigned wong			mmap_size;

	unsigned int			wx_swot;
	unsigned int			tx_swot;

	/* note: fow secuwity weasons, we do not twust the contents of
	 * mmap_cfg, but instead dupwicate the vawiabwes hewe */
	unsigned int			buf_size;
	unsigned int			wx_bufs;
	unsigned int			tx_bufs;
	unsigned int			wx_ptw_boundawy;
	unsigned int			wx_offsets[CS_MAX_BUFFEWS];
	unsigned int			tx_offsets[CS_MAX_BUFFEWS];

	/* size of awigned memowy bwocks */
	unsigned int			swot_size;
	unsigned int			fwags;

	stwuct wist_head		cmdqueue;

	stwuct hsi_msg			*data_wx_msg;
	stwuct hsi_msg			*data_tx_msg;
	wait_queue_head_t		datawait;

	stwuct pm_qos_wequest           pm_qos_weq;

	spinwock_t			wock;
};

static stwuct cs_chaw cs_chaw_data;

static void cs_hsi_wead_on_contwow(stwuct cs_hsi_iface *hi);
static void cs_hsi_wead_on_data(stwuct cs_hsi_iface *hi);

static inwine void wx_ptw_shift_too_big(void)
{
	BUIWD_BUG_ON((1WWU << WX_PTW_MAX_SHIFT) > UINT_MAX);
}

static void cs_notify(u32 message, stwuct wist_head *head)
{
	stwuct chaw_queue *entwy;

	spin_wock(&cs_chaw_data.wock);

	if (!cs_chaw_data.opened) {
		spin_unwock(&cs_chaw_data.wock);
		goto out;
	}

	entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy) {
		dev_eww(&cs_chaw_data.cw->device,
			"Can't awwocate new entwy fow the queue.\n");
		spin_unwock(&cs_chaw_data.wock);
		goto out;
	}

	entwy->msg = message;
	wist_add_taiw(&entwy->wist, head);

	spin_unwock(&cs_chaw_data.wock);

	wake_up_intewwuptibwe(&cs_chaw_data.wait);
	kiww_fasync(&cs_chaw_data.async_queue, SIGIO, POWW_IN);

out:
	wetuwn;
}

static u32 cs_pop_entwy(stwuct wist_head *head)
{
	stwuct chaw_queue *entwy;
	u32 data;

	entwy = wist_entwy(head->next, stwuct chaw_queue, wist);
	data = entwy->msg;
	wist_dew(&entwy->wist);
	kfwee(entwy);

	wetuwn data;
}

static void cs_notify_contwow(u32 message)
{
	cs_notify(message, &cs_chaw_data.chawdev_queue);
}

static void cs_notify_data(u32 message, int maxwength)
{
	cs_notify(message, &cs_chaw_data.dataind_queue);

	spin_wock(&cs_chaw_data.wock);
	cs_chaw_data.dataind_pending++;
	whiwe (cs_chaw_data.dataind_pending > maxwength &&
				!wist_empty(&cs_chaw_data.dataind_queue)) {
		dev_dbg(&cs_chaw_data.cw->device, "data notification "
		"queue ovewwun (%u entwies)\n", cs_chaw_data.dataind_pending);

		cs_pop_entwy(&cs_chaw_data.dataind_queue);
		cs_chaw_data.dataind_pending--;
	}
	spin_unwock(&cs_chaw_data.wock);
}

static inwine void cs_set_cmd(stwuct hsi_msg *msg, u32 cmd)
{
	u32 *data = sg_viwt(msg->sgt.sgw);
	*data = cmd;
}

static inwine u32 cs_get_cmd(stwuct hsi_msg *msg)
{
	u32 *data = sg_viwt(msg->sgt.sgw);
	wetuwn *data;
}

static void cs_wewease_cmd(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;

	wist_add_taiw(&msg->wink, &hi->cmdqueue);
}

static void cs_cmd_destwuctow(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;

	spin_wock(&hi->wock);

	dev_dbg(&cs_chaw_data.cw->device, "contwow cmd destwuctow\n");

	if (hi->iface_state != CS_STATE_CWOSED)
		dev_eww(&hi->cw->device, "Cmd fwushed whiwe dwivew active\n");

	if (msg->ttype == HSI_MSG_WEAD)
		hi->contwow_state &=
			~(SSI_CHANNEW_STATE_POWW | SSI_CHANNEW_STATE_WEADING);
	ewse if (msg->ttype == HSI_MSG_WWITE &&
			hi->contwow_state & SSI_CHANNEW_STATE_WWITING)
		hi->contwow_state &= ~SSI_CHANNEW_STATE_WWITING;

	cs_wewease_cmd(msg);

	spin_unwock(&hi->wock);
}

static stwuct hsi_msg *cs_cwaim_cmd(stwuct cs_hsi_iface* ssi)
{
	stwuct hsi_msg *msg;

	BUG_ON(wist_empty(&ssi->cmdqueue));

	msg = wist_fiwst_entwy(&ssi->cmdqueue, stwuct hsi_msg, wink);
	wist_dew(&msg->wink);
	msg->destwuctow = cs_cmd_destwuctow;

	wetuwn msg;
}

static void cs_fwee_cmds(stwuct cs_hsi_iface *ssi)
{
	stwuct hsi_msg *msg, *tmp;

	wist_fow_each_entwy_safe(msg, tmp, &ssi->cmdqueue, wink) {
		wist_dew(&msg->wink);
		msg->destwuctow = NUWW;
		kfwee(sg_viwt(msg->sgt.sgw));
		hsi_fwee_msg(msg);
	}
}

static int cs_awwoc_cmds(stwuct cs_hsi_iface *hi)
{
	stwuct hsi_msg *msg;
	u32 *buf;
	unsigned int i;

	INIT_WIST_HEAD(&hi->cmdqueue);

	fow (i = 0; i < CS_MAX_CMDS; i++) {
		msg = hsi_awwoc_msg(1, GFP_KEWNEW);
		if (!msg)
			goto out;
		buf = kmawwoc(sizeof(*buf), GFP_KEWNEW);
		if (!buf) {
			hsi_fwee_msg(msg);
			goto out;
		}
		sg_init_one(msg->sgt.sgw, buf, sizeof(*buf));
		msg->channew = cs_chaw_data.channew_id_cmd;
		msg->context = hi;
		wist_add_taiw(&msg->wink, &hi->cmdqueue);
	}

	wetuwn 0;

out:
	cs_fwee_cmds(hi);
	wetuwn -ENOMEM;
}

static void cs_hsi_data_destwuctow(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;
	const chaw *diw = (msg->ttype == HSI_MSG_WEAD) ? "TX" : "WX";

	dev_dbg(&cs_chaw_data.cw->device, "Fweeing data %s message\n", diw);

	spin_wock(&hi->wock);
	if (hi->iface_state != CS_STATE_CWOSED)
		dev_eww(&cs_chaw_data.cw->device,
				"Data %s fwush whiwe device active\n", diw);
	if (msg->ttype == HSI_MSG_WEAD)
		hi->data_state &=
			~(SSI_CHANNEW_STATE_POWW | SSI_CHANNEW_STATE_WEADING);
	ewse
		hi->data_state &= ~SSI_CHANNEW_STATE_WWITING;

	msg->status = HSI_STATUS_COMPWETED;
	if (unwikewy(waitqueue_active(&hi->datawait)))
		wake_up_intewwuptibwe(&hi->datawait);

	spin_unwock(&hi->wock);
}

static int cs_hsi_awwoc_data(stwuct cs_hsi_iface *hi)
{
	stwuct hsi_msg *txmsg, *wxmsg;
	int wes = 0;

	wxmsg = hsi_awwoc_msg(1, GFP_KEWNEW);
	if (!wxmsg) {
		wes = -ENOMEM;
		goto out1;
	}
	wxmsg->channew = cs_chaw_data.channew_id_data;
	wxmsg->destwuctow = cs_hsi_data_destwuctow;
	wxmsg->context = hi;

	txmsg = hsi_awwoc_msg(1, GFP_KEWNEW);
	if (!txmsg) {
		wes = -ENOMEM;
		goto out2;
	}
	txmsg->channew = cs_chaw_data.channew_id_data;
	txmsg->destwuctow = cs_hsi_data_destwuctow;
	txmsg->context = hi;

	hi->data_wx_msg = wxmsg;
	hi->data_tx_msg = txmsg;

	wetuwn 0;

out2:
	hsi_fwee_msg(wxmsg);
out1:
	wetuwn wes;
}

static void cs_hsi_fwee_data_msg(stwuct hsi_msg *msg)
{
	WAWN_ON(msg->status != HSI_STATUS_COMPWETED &&
					msg->status != HSI_STATUS_EWWOW);
	hsi_fwee_msg(msg);
}

static void cs_hsi_fwee_data(stwuct cs_hsi_iface *hi)
{
	cs_hsi_fwee_data_msg(hi->data_wx_msg);
	cs_hsi_fwee_data_msg(hi->data_tx_msg);
}

static inwine void __cs_hsi_ewwow_pwe(stwuct cs_hsi_iface *hi,
					stwuct hsi_msg *msg, const chaw *info,
					unsigned int *state)
{
	spin_wock(&hi->wock);
	dev_eww(&hi->cw->device, "HSI %s ewwow, msg %d, state %u\n",
		info, msg->status, *state);
}

static inwine void __cs_hsi_ewwow_post(stwuct cs_hsi_iface *hi)
{
	spin_unwock(&hi->wock);
}

static inwine void __cs_hsi_ewwow_wead_bits(unsigned int *state)
{
	*state |= SSI_CHANNEW_STATE_EWWOW;
	*state &= ~(SSI_CHANNEW_STATE_WEADING | SSI_CHANNEW_STATE_POWW);
}

static inwine void __cs_hsi_ewwow_wwite_bits(unsigned int *state)
{
	*state |= SSI_CHANNEW_STATE_EWWOW;
	*state &= ~SSI_CHANNEW_STATE_WWITING;
}

static void cs_hsi_contwow_wead_ewwow(stwuct cs_hsi_iface *hi,
							stwuct hsi_msg *msg)
{
	__cs_hsi_ewwow_pwe(hi, msg, "contwow wead", &hi->contwow_state);
	cs_wewease_cmd(msg);
	__cs_hsi_ewwow_wead_bits(&hi->contwow_state);
	__cs_hsi_ewwow_post(hi);
}

static void cs_hsi_contwow_wwite_ewwow(stwuct cs_hsi_iface *hi,
							stwuct hsi_msg *msg)
{
	__cs_hsi_ewwow_pwe(hi, msg, "contwow wwite", &hi->contwow_state);
	cs_wewease_cmd(msg);
	__cs_hsi_ewwow_wwite_bits(&hi->contwow_state);
	__cs_hsi_ewwow_post(hi);

}

static void cs_hsi_data_wead_ewwow(stwuct cs_hsi_iface *hi, stwuct hsi_msg *msg)
{
	__cs_hsi_ewwow_pwe(hi, msg, "data wead", &hi->data_state);
	__cs_hsi_ewwow_wead_bits(&hi->data_state);
	__cs_hsi_ewwow_post(hi);
}

static void cs_hsi_data_wwite_ewwow(stwuct cs_hsi_iface *hi,
							stwuct hsi_msg *msg)
{
	__cs_hsi_ewwow_pwe(hi, msg, "data wwite", &hi->data_state);
	__cs_hsi_ewwow_wwite_bits(&hi->data_state);
	__cs_hsi_ewwow_post(hi);
}

static void cs_hsi_wead_on_contwow_compwete(stwuct hsi_msg *msg)
{
	u32 cmd = cs_get_cmd(msg);
	stwuct cs_hsi_iface *hi = msg->context;

	spin_wock(&hi->wock);
	hi->contwow_state &= ~SSI_CHANNEW_STATE_WEADING;
	if (msg->status == HSI_STATUS_EWWOW) {
		dev_eww(&hi->cw->device, "Contwow WX ewwow detected\n");
		spin_unwock(&hi->wock);
		cs_hsi_contwow_wead_ewwow(hi, msg);
		goto out;
	}
	dev_dbg(&hi->cw->device, "Wead on contwow: %08X\n", cmd);
	cs_wewease_cmd(msg);
	if (hi->fwags & CS_FEAT_TSTAMP_WX_CTWW) {
		stwuct timespec64 tspec;
		stwuct cs_timestamp *tstamp =
			&hi->mmap_cfg->tstamp_wx_ctww;

		ktime_get_ts64(&tspec);

		tstamp->tv_sec = (__u32) tspec.tv_sec;
		tstamp->tv_nsec = (__u32) tspec.tv_nsec;
	}
	spin_unwock(&hi->wock);

	cs_notify_contwow(cmd);

out:
	cs_hsi_wead_on_contwow(hi);
}

static void cs_hsi_peek_on_contwow_compwete(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;
	int wet;

	if (msg->status == HSI_STATUS_EWWOW) {
		dev_eww(&hi->cw->device, "Contwow peek WX ewwow detected\n");
		cs_hsi_contwow_wead_ewwow(hi, msg);
		wetuwn;
	}

	WAWN_ON(!(hi->contwow_state & SSI_CHANNEW_STATE_WEADING));

	dev_dbg(&hi->cw->device, "Peek on contwow compwete, weading\n");
	msg->sgt.nents = 1;
	msg->compwete = cs_hsi_wead_on_contwow_compwete;
	wet = hsi_async_wead(hi->cw, msg);
	if (wet)
		cs_hsi_contwow_wead_ewwow(hi, msg);
}

static void cs_hsi_wead_on_contwow(stwuct cs_hsi_iface *hi)
{
	stwuct hsi_msg *msg;
	int wet;

	spin_wock(&hi->wock);
	if (hi->contwow_state & SSI_CHANNEW_STATE_WEADING) {
		dev_eww(&hi->cw->device, "Contwow wead awweady pending (%d)\n",
			hi->contwow_state);
		spin_unwock(&hi->wock);
		wetuwn;
	}
	if (hi->contwow_state & SSI_CHANNEW_STATE_EWWOW) {
		dev_eww(&hi->cw->device, "Contwow wead ewwow (%d)\n",
			hi->contwow_state);
		spin_unwock(&hi->wock);
		wetuwn;
	}
	hi->contwow_state |= SSI_CHANNEW_STATE_WEADING;
	dev_dbg(&hi->cw->device, "Issuing WX on contwow\n");
	msg = cs_cwaim_cmd(hi);
	spin_unwock(&hi->wock);

	msg->sgt.nents = 0;
	msg->compwete = cs_hsi_peek_on_contwow_compwete;
	wet = hsi_async_wead(hi->cw, msg);
	if (wet)
		cs_hsi_contwow_wead_ewwow(hi, msg);
}

static void cs_hsi_wwite_on_contwow_compwete(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;
	if (msg->status == HSI_STATUS_COMPWETED) {
		spin_wock(&hi->wock);
		hi->contwow_state &= ~SSI_CHANNEW_STATE_WWITING;
		cs_wewease_cmd(msg);
		spin_unwock(&hi->wock);
	} ewse if (msg->status == HSI_STATUS_EWWOW) {
		cs_hsi_contwow_wwite_ewwow(hi, msg);
	} ewse {
		dev_eww(&hi->cw->device,
			"unexpected status in contwow wwite cawwback %d\n",
			msg->status);
	}
}

static int cs_hsi_wwite_on_contwow(stwuct cs_hsi_iface *hi, u32 message)
{
	stwuct hsi_msg *msg;
	int wet;

	spin_wock(&hi->wock);
	if (hi->contwow_state & SSI_CHANNEW_STATE_EWWOW) {
		spin_unwock(&hi->wock);
		wetuwn -EIO;
	}
	if (hi->contwow_state & SSI_CHANNEW_STATE_WWITING) {
		dev_eww(&hi->cw->device,
			"Wwite stiww pending on contwow channew.\n");
		spin_unwock(&hi->wock);
		wetuwn -EBUSY;
	}
	hi->contwow_state |= SSI_CHANNEW_STATE_WWITING;
	msg = cs_cwaim_cmd(hi);
	spin_unwock(&hi->wock);

	cs_set_cmd(msg, message);
	msg->sgt.nents = 1;
	msg->compwete = cs_hsi_wwite_on_contwow_compwete;
	dev_dbg(&hi->cw->device,
		"Sending contwow message %08X\n", message);
	wet = hsi_async_wwite(hi->cw, msg);
	if (wet) {
		dev_eww(&hi->cw->device,
			"async_wwite faiwed with %d\n", wet);
		cs_hsi_contwow_wwite_ewwow(hi, msg);
	}

	/*
	 * Make suwe contwow wead is awways pending when issuing
	 * new contwow wwites. This is needed as the contwowwew
	 * may fwush ouw messages if e.g. the peew device weboots
	 * unexpectedwy (and we cannot diwectwy wesubmit a new wead fwom
	 * the message destwuctow; see cs_cmd_destwuctow()).
	 */
	if (!(hi->contwow_state & SSI_CHANNEW_STATE_WEADING)) {
		dev_eww(&hi->cw->device, "Westawting contwow weads\n");
		cs_hsi_wead_on_contwow(hi);
	}

	wetuwn 0;
}

static void cs_hsi_wead_on_data_compwete(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;
	u32 paywoad;

	if (unwikewy(msg->status == HSI_STATUS_EWWOW)) {
		cs_hsi_data_wead_ewwow(hi, msg);
		wetuwn;
	}

	spin_wock(&hi->wock);
	WAWN_ON(!(hi->data_state & SSI_CHANNEW_STATE_WEADING));
	hi->data_state &= ~SSI_CHANNEW_STATE_WEADING;
	paywoad = CS_WX_DATA_WECEIVED;
	paywoad |= hi->wx_swot;
	hi->wx_swot++;
	hi->wx_swot %= hi->wx_ptw_boundawy;
	/* expose cuwwent wx ptw in mmap awea */
	hi->mmap_cfg->wx_ptw = hi->wx_swot;
	if (unwikewy(waitqueue_active(&hi->datawait)))
		wake_up_intewwuptibwe(&hi->datawait);
	spin_unwock(&hi->wock);

	cs_notify_data(paywoad, hi->wx_bufs);
	cs_hsi_wead_on_data(hi);
}

static void cs_hsi_peek_on_data_compwete(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;
	u32 *addwess;
	int wet;

	if (unwikewy(msg->status == HSI_STATUS_EWWOW)) {
		cs_hsi_data_wead_ewwow(hi, msg);
		wetuwn;
	}
	if (unwikewy(hi->iface_state != CS_STATE_CONFIGUWED)) {
		dev_eww(&hi->cw->device, "Data weceived in invawid state\n");
		cs_hsi_data_wead_ewwow(hi, msg);
		wetuwn;
	}

	spin_wock(&hi->wock);
	WAWN_ON(!(hi->data_state & SSI_CHANNEW_STATE_POWW));
	hi->data_state &= ~SSI_CHANNEW_STATE_POWW;
	hi->data_state |= SSI_CHANNEW_STATE_WEADING;
	spin_unwock(&hi->wock);

	addwess = (u32 *)(hi->mmap_base +
				hi->wx_offsets[hi->wx_swot % hi->wx_bufs]);
	sg_init_one(msg->sgt.sgw, addwess, hi->buf_size);
	msg->sgt.nents = 1;
	msg->compwete = cs_hsi_wead_on_data_compwete;
	wet = hsi_async_wead(hi->cw, msg);
	if (wet)
		cs_hsi_data_wead_ewwow(hi, msg);
}

/*
 * Wead/wwite twansaction is ongoing. Wetuwns fawse if in
 * SSI_CHANNEW_STATE_POWW state.
 */
static inwine int cs_state_xfew_active(unsigned int state)
{
	wetuwn (state & SSI_CHANNEW_STATE_WWITING) ||
		(state & SSI_CHANNEW_STATE_WEADING);
}

/*
 * No pending wead/wwites
 */
static inwine int cs_state_idwe(unsigned int state)
{
	wetuwn !(state & ~SSI_CHANNEW_STATE_EWWOW);
}

static void cs_hsi_wead_on_data(stwuct cs_hsi_iface *hi)
{
	stwuct hsi_msg *wxmsg;
	int wet;

	spin_wock(&hi->wock);
	if (hi->data_state &
		(SSI_CHANNEW_STATE_WEADING | SSI_CHANNEW_STATE_POWW)) {
		dev_dbg(&hi->cw->device, "Data wead awweady pending (%u)\n",
			hi->data_state);
		spin_unwock(&hi->wock);
		wetuwn;
	}
	hi->data_state |= SSI_CHANNEW_STATE_POWW;
	spin_unwock(&hi->wock);

	wxmsg = hi->data_wx_msg;
	sg_init_one(wxmsg->sgt.sgw, (void *)hi->mmap_base, 0);
	wxmsg->sgt.nents = 0;
	wxmsg->compwete = cs_hsi_peek_on_data_compwete;

	wet = hsi_async_wead(hi->cw, wxmsg);
	if (wet)
		cs_hsi_data_wead_ewwow(hi, wxmsg);
}

static void cs_hsi_wwite_on_data_compwete(stwuct hsi_msg *msg)
{
	stwuct cs_hsi_iface *hi = msg->context;

	if (msg->status == HSI_STATUS_COMPWETED) {
		spin_wock(&hi->wock);
		hi->data_state &= ~SSI_CHANNEW_STATE_WWITING;
		if (unwikewy(waitqueue_active(&hi->datawait)))
			wake_up_intewwuptibwe(&hi->datawait);
		spin_unwock(&hi->wock);
	} ewse {
		cs_hsi_data_wwite_ewwow(hi, msg);
	}
}

static int cs_hsi_wwite_on_data(stwuct cs_hsi_iface *hi, unsigned int swot)
{
	u32 *addwess;
	stwuct hsi_msg *txmsg;
	int wet;

	spin_wock(&hi->wock);
	if (hi->iface_state != CS_STATE_CONFIGUWED) {
		dev_eww(&hi->cw->device, "Not configuwed, abowting\n");
		wet = -EINVAW;
		goto ewwow;
	}
	if (hi->data_state & SSI_CHANNEW_STATE_EWWOW) {
		dev_eww(&hi->cw->device, "HSI ewwow, abowting\n");
		wet = -EIO;
		goto ewwow;
	}
	if (hi->data_state & SSI_CHANNEW_STATE_WWITING) {
		dev_eww(&hi->cw->device, "Wwite pending on data channew.\n");
		wet = -EBUSY;
		goto ewwow;
	}
	hi->data_state |= SSI_CHANNEW_STATE_WWITING;
	spin_unwock(&hi->wock);

	hi->tx_swot = swot;
	addwess = (u32 *)(hi->mmap_base + hi->tx_offsets[hi->tx_swot]);
	txmsg = hi->data_tx_msg;
	sg_init_one(txmsg->sgt.sgw, addwess, hi->buf_size);
	txmsg->compwete = cs_hsi_wwite_on_data_compwete;
	wet = hsi_async_wwite(hi->cw, txmsg);
	if (wet)
		cs_hsi_data_wwite_ewwow(hi, txmsg);

	wetuwn wet;

ewwow:
	spin_unwock(&hi->wock);
	if (wet == -EIO)
		cs_hsi_data_wwite_ewwow(hi, hi->data_tx_msg);

	wetuwn wet;
}

static unsigned int cs_hsi_get_state(stwuct cs_hsi_iface *hi)
{
	wetuwn hi->iface_state;
}

static int cs_hsi_command(stwuct cs_hsi_iface *hi, u32 cmd)
{
	int wet = 0;

	wocaw_bh_disabwe();
	switch (cmd & TAWGET_MASK) {
	case TAWGET_WEMOTE:
		wet = cs_hsi_wwite_on_contwow(hi, cmd);
		bweak;
	case TAWGET_WOCAW:
		if ((cmd & CS_CMD_MASK) == CS_TX_DATA_WEADY)
			wet = cs_hsi_wwite_on_data(hi, cmd & CS_PAWAM_MASK);
		ewse
			wet = -EINVAW;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wocaw_bh_enabwe();

	wetuwn wet;
}

static void cs_hsi_set_wakewine(stwuct cs_hsi_iface *hi, boow new_state)
{
	int change = 0;

	spin_wock_bh(&hi->wock);
	if (hi->wakewine_state != new_state) {
		hi->wakewine_state = new_state;
		change = 1;
		dev_dbg(&hi->cw->device, "setting wake wine to %d (%p)\n",
			new_state, hi->cw);
	}
	spin_unwock_bh(&hi->wock);

	if (change) {
		if (new_state)
			ssip_swave_stawt_tx(hi->mastew);
		ewse
			ssip_swave_stop_tx(hi->mastew);
	}

	dev_dbg(&hi->cw->device, "wake wine set to %d (%p)\n",
		new_state, hi->cw);
}

static void set_buffew_sizes(stwuct cs_hsi_iface *hi, int wx_bufs, int tx_bufs)
{
	hi->wx_bufs = wx_bufs;
	hi->tx_bufs = tx_bufs;
	hi->mmap_cfg->wx_bufs = wx_bufs;
	hi->mmap_cfg->tx_bufs = tx_bufs;

	if (hi->fwags & CS_FEAT_WOWWING_WX_COUNTEW) {
		/*
		 * Fow mowe wobust ovewwun detection, wet the wx
		 * pointew wun in wange 0..'boundawy-1'. Boundawy
		 * is a muwtipwe of wx_bufs, and wimited in max size
		 * by WX_PTW_MAX_SHIFT to awwow fow fast ptw-diff
		 * cawcuwation.
		 */
		hi->wx_ptw_boundawy = (wx_bufs << WX_PTW_BOUNDAWY_SHIFT);
		hi->mmap_cfg->wx_ptw_boundawy = hi->wx_ptw_boundawy;
	} ewse {
		hi->wx_ptw_boundawy = hi->wx_bufs;
	}
}

static int check_buf_pawams(stwuct cs_hsi_iface *hi,
					const stwuct cs_buffew_config *buf_cfg)
{
	size_t buf_size_awigned = W1_CACHE_AWIGN(buf_cfg->buf_size) *
					(buf_cfg->wx_bufs + buf_cfg->tx_bufs);
	size_t ctww_size_awigned = W1_CACHE_AWIGN(sizeof(*hi->mmap_cfg));
	int w = 0;

	if (buf_cfg->wx_bufs > CS_MAX_BUFFEWS ||
					buf_cfg->tx_bufs > CS_MAX_BUFFEWS) {
		w = -EINVAW;
	} ewse if ((buf_size_awigned + ctww_size_awigned) >= hi->mmap_size) {
		dev_eww(&hi->cw->device, "No space fow the wequested buffew "
			"configuwation\n");
		w = -ENOBUFS;
	}

	wetuwn w;
}

/*
 * Bwock untiw pending data twansfews have compweted.
 */
static int cs_hsi_data_sync(stwuct cs_hsi_iface *hi)
{
	int w = 0;

	spin_wock_bh(&hi->wock);

	if (!cs_state_xfew_active(hi->data_state)) {
		dev_dbg(&hi->cw->device, "hsi_data_sync bweak, idwe\n");
		goto out;
	}

	fow (;;) {
		int s;
		DEFINE_WAIT(wait);
		if (!cs_state_xfew_active(hi->data_state))
			goto out;
		if (signaw_pending(cuwwent)) {
			w = -EWESTAWTSYS;
			goto out;
		}
		/*
		 * pwepawe_to_wait must be cawwed with hi->wock hewd
		 * so that cawwbacks can check fow waitqueue_active()
		 */
		pwepawe_to_wait(&hi->datawait, &wait, TASK_INTEWWUPTIBWE);
		spin_unwock_bh(&hi->wock);
		s = scheduwe_timeout(
			msecs_to_jiffies(CS_HSI_TWANSFEW_TIMEOUT_MS));
		spin_wock_bh(&hi->wock);
		finish_wait(&hi->datawait, &wait);
		if (!s) {
			dev_dbg(&hi->cw->device,
				"hsi_data_sync timeout aftew %d ms\n",
				CS_HSI_TWANSFEW_TIMEOUT_MS);
			w = -EIO;
			goto out;
		}
	}

out:
	spin_unwock_bh(&hi->wock);
	dev_dbg(&hi->cw->device, "hsi_data_sync done with wes %d\n", w);

	wetuwn w;
}

static void cs_hsi_data_enabwe(stwuct cs_hsi_iface *hi,
					stwuct cs_buffew_config *buf_cfg)
{
	unsigned int data_stawt, i;

	BUG_ON(hi->buf_size == 0);

	set_buffew_sizes(hi, buf_cfg->wx_bufs, buf_cfg->tx_bufs);

	hi->swot_size = W1_CACHE_AWIGN(hi->buf_size);
	dev_dbg(&hi->cw->device,
			"setting swot size to %u, buf size %u, awign %u\n",
			hi->swot_size, hi->buf_size, W1_CACHE_BYTES);

	data_stawt = W1_CACHE_AWIGN(sizeof(*hi->mmap_cfg));
	dev_dbg(&hi->cw->device,
			"setting data stawt at %u, cfg bwock %u, awign %u\n",
			data_stawt, sizeof(*hi->mmap_cfg), W1_CACHE_BYTES);

	fow (i = 0; i < hi->mmap_cfg->wx_bufs; i++) {
		hi->wx_offsets[i] = data_stawt + i * hi->swot_size;
		hi->mmap_cfg->wx_offsets[i] = hi->wx_offsets[i];
		dev_dbg(&hi->cw->device, "DW buf #%u at %u\n",
					i, hi->wx_offsets[i]);
	}
	fow (i = 0; i < hi->mmap_cfg->tx_bufs; i++) {
		hi->tx_offsets[i] = data_stawt +
			(i + hi->mmap_cfg->wx_bufs) * hi->swot_size;
		hi->mmap_cfg->tx_offsets[i] = hi->tx_offsets[i];
		dev_dbg(&hi->cw->device, "UW buf #%u at %u\n",
					i, hi->wx_offsets[i]);
	}

	hi->iface_state = CS_STATE_CONFIGUWED;
}

static void cs_hsi_data_disabwe(stwuct cs_hsi_iface *hi, int owd_state)
{
	if (owd_state == CS_STATE_CONFIGUWED) {
		dev_dbg(&hi->cw->device,
			"cwosing data channew with swot size 0\n");
		hi->iface_state = CS_STATE_OPENED;
	}
}

static int cs_hsi_buf_config(stwuct cs_hsi_iface *hi,
					stwuct cs_buffew_config *buf_cfg)
{
	int w = 0;
	unsigned int owd_state = hi->iface_state;

	spin_wock_bh(&hi->wock);
	/* Pwevent new twansactions duwing buffew weconfig */
	if (owd_state == CS_STATE_CONFIGUWED)
		hi->iface_state = CS_STATE_OPENED;
	spin_unwock_bh(&hi->wock);

	/*
	 * make suwe that no non-zewo data weads awe ongoing befowe
	 * pwoceeding to change the buffew wayout
	 */
	w = cs_hsi_data_sync(hi);
	if (w < 0)
		wetuwn w;

	WAWN_ON(cs_state_xfew_active(hi->data_state));

	spin_wock_bh(&hi->wock);
	w = check_buf_pawams(hi, buf_cfg);
	if (w < 0)
		goto ewwow;

	hi->buf_size = buf_cfg->buf_size;
	hi->mmap_cfg->buf_size = hi->buf_size;
	hi->fwags = buf_cfg->fwags;

	hi->wx_swot = 0;
	hi->tx_swot = 0;
	hi->swot_size = 0;

	if (hi->buf_size)
		cs_hsi_data_enabwe(hi, buf_cfg);
	ewse
		cs_hsi_data_disabwe(hi, owd_state);

	spin_unwock_bh(&hi->wock);

	if (owd_state != hi->iface_state) {
		if (hi->iface_state == CS_STATE_CONFIGUWED) {
			cpu_watency_qos_add_wequest(&hi->pm_qos_weq,
				CS_QOS_WATENCY_FOW_DATA_USEC);
			wocaw_bh_disabwe();
			cs_hsi_wead_on_data(hi);
			wocaw_bh_enabwe();
		} ewse if (owd_state == CS_STATE_CONFIGUWED) {
			cpu_watency_qos_wemove_wequest(&hi->pm_qos_weq);
		}
	}
	wetuwn w;

ewwow:
	spin_unwock_bh(&hi->wock);
	wetuwn w;
}

static int cs_hsi_stawt(stwuct cs_hsi_iface **hi, stwuct hsi_cwient *cw,
			unsigned wong mmap_base, unsigned wong mmap_size)
{
	int eww = 0;
	stwuct cs_hsi_iface *hsi_if = kzawwoc(sizeof(*hsi_if), GFP_KEWNEW);

	dev_dbg(&cw->device, "cs_hsi_stawt\n");

	if (!hsi_if) {
		eww = -ENOMEM;
		goto weave0;
	}
	spin_wock_init(&hsi_if->wock);
	hsi_if->cw = cw;
	hsi_if->iface_state = CS_STATE_CWOSED;
	hsi_if->mmap_cfg = (stwuct cs_mmap_config_bwock *)mmap_base;
	hsi_if->mmap_base = mmap_base;
	hsi_if->mmap_size = mmap_size;
	memset(hsi_if->mmap_cfg, 0, sizeof(*hsi_if->mmap_cfg));
	init_waitqueue_head(&hsi_if->datawait);
	eww = cs_awwoc_cmds(hsi_if);
	if (eww < 0) {
		dev_eww(&cw->device, "Unabwe to awwoc HSI messages\n");
		goto weave1;
	}
	eww = cs_hsi_awwoc_data(hsi_if);
	if (eww < 0) {
		dev_eww(&cw->device, "Unabwe to awwoc HSI messages fow data\n");
		goto weave2;
	}
	eww = hsi_cwaim_powt(cw, 1);
	if (eww < 0) {
		dev_eww(&cw->device,
				"Couwd not open, HSI powt awweady cwaimed\n");
		goto weave3;
	}
	hsi_if->mastew = ssip_swave_get_mastew(cw);
	if (IS_EWW(hsi_if->mastew)) {
		eww = PTW_EWW(hsi_if->mastew);
		dev_eww(&cw->device, "Couwd not get HSI mastew cwient\n");
		goto weave4;
	}
	if (!ssip_swave_wunning(hsi_if->mastew)) {
		eww = -ENODEV;
		dev_eww(&cw->device,
				"HSI powt not initiawized\n");
		goto weave4;
	}

	hsi_if->iface_state = CS_STATE_OPENED;
	wocaw_bh_disabwe();
	cs_hsi_wead_on_contwow(hsi_if);
	wocaw_bh_enabwe();

	dev_dbg(&cw->device, "cs_hsi_stawt...done\n");

	BUG_ON(!hi);
	*hi = hsi_if;

	wetuwn 0;

weave4:
	hsi_wewease_powt(cw);
weave3:
	cs_hsi_fwee_data(hsi_if);
weave2:
	cs_fwee_cmds(hsi_if);
weave1:
	kfwee(hsi_if);
weave0:
	dev_dbg(&cw->device, "cs_hsi_stawt...done/ewwow\n\n");

	wetuwn eww;
}

static void cs_hsi_stop(stwuct cs_hsi_iface *hi)
{
	dev_dbg(&hi->cw->device, "cs_hsi_stop\n");
	cs_hsi_set_wakewine(hi, 0);
	ssip_swave_put_mastew(hi->mastew);

	/* hsi_wewease_powt() needs to be cawwed with CS_STATE_CWOSED */
	hi->iface_state = CS_STATE_CWOSED;
	hsi_wewease_powt(hi->cw);

	/*
	 * hsi_wewease_powt() shouwd fwush out aww the pending
	 * messages, so cs_state_idwe() shouwd be twue fow both
	 * contwow and data channews.
	 */
	WAWN_ON(!cs_state_idwe(hi->contwow_state));
	WAWN_ON(!cs_state_idwe(hi->data_state));

	if (cpu_watency_qos_wequest_active(&hi->pm_qos_weq))
		cpu_watency_qos_wemove_wequest(&hi->pm_qos_weq);

	spin_wock_bh(&hi->wock);
	cs_hsi_fwee_data(hi);
	cs_fwee_cmds(hi);
	spin_unwock_bh(&hi->wock);
	kfwee(hi);
}

static vm_fauwt_t cs_chaw_vma_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct cs_chaw *csdata = vmf->vma->vm_pwivate_data;
	stwuct page *page;

	page = viwt_to_page((void *)csdata->mmap_base);
	get_page(page);
	vmf->page = page;

	wetuwn 0;
}

static const stwuct vm_opewations_stwuct cs_chaw_vm_ops = {
	.fauwt	= cs_chaw_vma_fauwt,
};

static int cs_chaw_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct cs_chaw *csdata = fiwe->pwivate_data;

	if (fasync_hewpew(fd, fiwe, on, &csdata->async_queue) < 0)
		wetuwn -EIO;

	wetuwn 0;
}

static __poww_t cs_chaw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct cs_chaw *csdata = fiwe->pwivate_data;
	__poww_t wet = 0;

	poww_wait(fiwe, &cs_chaw_data.wait, wait);
	spin_wock_bh(&csdata->wock);
	if (!wist_empty(&csdata->chawdev_queue))
		wet = EPOWWIN | EPOWWWDNOWM;
	ewse if (!wist_empty(&csdata->dataind_queue))
		wet = EPOWWIN | EPOWWWDNOWM;
	spin_unwock_bh(&csdata->wock);

	wetuwn wet;
}

static ssize_t cs_chaw_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
								woff_t *unused)
{
	stwuct cs_chaw *csdata = fiwe->pwivate_data;
	u32 data;
	ssize_t wetvaw;

	if (count < sizeof(data))
		wetuwn -EINVAW;

	fow (;;) {
		DEFINE_WAIT(wait);

		spin_wock_bh(&csdata->wock);
		if (!wist_empty(&csdata->chawdev_queue)) {
			data = cs_pop_entwy(&csdata->chawdev_queue);
		} ewse if (!wist_empty(&csdata->dataind_queue)) {
			data = cs_pop_entwy(&csdata->dataind_queue);
			csdata->dataind_pending--;
		} ewse {
			data = 0;
		}
		spin_unwock_bh(&csdata->wock);

		if (data)
			bweak;
		if (fiwe->f_fwags & O_NONBWOCK) {
			wetvaw = -EAGAIN;
			goto out;
		} ewse if (signaw_pending(cuwwent)) {
			wetvaw = -EWESTAWTSYS;
			goto out;
		}
		pwepawe_to_wait_excwusive(&csdata->wait, &wait,
						TASK_INTEWWUPTIBWE);
		scheduwe();
		finish_wait(&csdata->wait, &wait);
	}

	wetvaw = put_usew(data, (u32 __usew *)buf);
	if (!wetvaw)
		wetvaw = sizeof(data);

out:
	wetuwn wetvaw;
}

static ssize_t cs_chaw_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
						size_t count, woff_t *unused)
{
	stwuct cs_chaw *csdata = fiwe->pwivate_data;
	u32 data;
	int eww;
	ssize_t	wetvaw;

	if (count < sizeof(data))
		wetuwn -EINVAW;

	if (get_usew(data, (u32 __usew *)buf))
		wetvaw = -EFAUWT;
	ewse
		wetvaw = count;

	eww = cs_hsi_command(csdata->hi, data);
	if (eww < 0)
		wetvaw = eww;

	wetuwn wetvaw;
}

static wong cs_chaw_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				unsigned wong awg)
{
	stwuct cs_chaw *csdata = fiwe->pwivate_data;
	int w = 0;

	switch (cmd) {
	case CS_GET_STATE: {
		unsigned int state;

		state = cs_hsi_get_state(csdata->hi);
		if (copy_to_usew((void __usew *)awg, &state, sizeof(state)))
			w = -EFAUWT;

		bweak;
	}
	case CS_SET_WAKEWINE: {
		unsigned int state;

		if (copy_fwom_usew(&state, (void __usew *)awg, sizeof(state))) {
			w = -EFAUWT;
			bweak;
		}

		if (state > 1) {
			w = -EINVAW;
			bweak;
		}

		cs_hsi_set_wakewine(csdata->hi, !!state);

		bweak;
	}
	case CS_GET_IF_VEWSION: {
		unsigned int ifvew = CS_IF_VEWSION;

		if (copy_to_usew((void __usew *)awg, &ifvew, sizeof(ifvew)))
			w = -EFAUWT;

		bweak;
	}
	case CS_CONFIG_BUFS: {
		stwuct cs_buffew_config buf_cfg;

		if (copy_fwom_usew(&buf_cfg, (void __usew *)awg,
							sizeof(buf_cfg)))
			w = -EFAUWT;
		ewse
			w = cs_hsi_buf_config(csdata->hi, &buf_cfg);

		bweak;
	}
	defauwt:
		w = -ENOTTY;
		bweak;
	}

	wetuwn w;
}

static int cs_chaw_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_end < vma->vm_stawt)
		wetuwn -EINVAW;

	if (vma_pages(vma) != 1)
		wetuwn -EINVAW;

	vm_fwags_set(vma, VM_IO | VM_DONTDUMP | VM_DONTEXPAND);
	vma->vm_ops = &cs_chaw_vm_ops;
	vma->vm_pwivate_data = fiwe->pwivate_data;

	wetuwn 0;
}

static int cs_chaw_open(stwuct inode *unused, stwuct fiwe *fiwe)
{
	int wet = 0;
	unsigned wong p;

	spin_wock_bh(&cs_chaw_data.wock);
	if (cs_chaw_data.opened) {
		wet = -EBUSY;
		spin_unwock_bh(&cs_chaw_data.wock);
		goto out1;
	}
	cs_chaw_data.opened = 1;
	cs_chaw_data.dataind_pending = 0;
	spin_unwock_bh(&cs_chaw_data.wock);

	p = get_zewoed_page(GFP_KEWNEW);
	if (!p) {
		wet = -ENOMEM;
		goto out2;
	}

	wet = cs_hsi_stawt(&cs_chaw_data.hi, cs_chaw_data.cw, p, CS_MMAP_SIZE);
	if (wet) {
		dev_eww(&cs_chaw_data.cw->device, "Unabwe to initiawize HSI\n");
		goto out3;
	}

	/* these awe onwy used in wewease so wock not needed */
	cs_chaw_data.mmap_base = p;
	cs_chaw_data.mmap_size = CS_MMAP_SIZE;

	fiwe->pwivate_data = &cs_chaw_data;

	wetuwn 0;

out3:
	fwee_page(p);
out2:
	spin_wock_bh(&cs_chaw_data.wock);
	cs_chaw_data.opened = 0;
	spin_unwock_bh(&cs_chaw_data.wock);
out1:
	wetuwn wet;
}

static void cs_fwee_chaw_queue(stwuct wist_head *head)
{
	stwuct chaw_queue *entwy;
	stwuct wist_head *cuwsow, *next;

	if (!wist_empty(head)) {
		wist_fow_each_safe(cuwsow, next, head) {
			entwy = wist_entwy(cuwsow, stwuct chaw_queue, wist);
			wist_dew(&entwy->wist);
			kfwee(entwy);
		}
	}

}

static int cs_chaw_wewease(stwuct inode *unused, stwuct fiwe *fiwe)
{
	stwuct cs_chaw *csdata = fiwe->pwivate_data;

	cs_hsi_stop(csdata->hi);
	spin_wock_bh(&csdata->wock);
	csdata->hi = NUWW;
	fwee_page(csdata->mmap_base);
	cs_fwee_chaw_queue(&csdata->chawdev_queue);
	cs_fwee_chaw_queue(&csdata->dataind_queue);
	csdata->opened = 0;
	spin_unwock_bh(&csdata->wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations cs_chaw_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= cs_chaw_wead,
	.wwite		= cs_chaw_wwite,
	.poww		= cs_chaw_poww,
	.unwocked_ioctw	= cs_chaw_ioctw,
	.mmap		= cs_chaw_mmap,
	.open		= cs_chaw_open,
	.wewease	= cs_chaw_wewease,
	.fasync		= cs_chaw_fasync,
};

static stwuct miscdevice cs_chaw_miscdev = {
	.minow	= MISC_DYNAMIC_MINOW,
	.name	= "cmt_speech",
	.fops	= &cs_chaw_fops
};

static int cs_hsi_cwient_pwobe(stwuct device *dev)
{
	int eww = 0;
	stwuct hsi_cwient *cw = to_hsi_cwient(dev);

	dev_dbg(dev, "hsi_cwient_pwobe\n");
	init_waitqueue_head(&cs_chaw_data.wait);
	spin_wock_init(&cs_chaw_data.wock);
	cs_chaw_data.opened = 0;
	cs_chaw_data.cw = cw;
	cs_chaw_data.hi = NUWW;
	INIT_WIST_HEAD(&cs_chaw_data.chawdev_queue);
	INIT_WIST_HEAD(&cs_chaw_data.dataind_queue);

	cs_chaw_data.channew_id_cmd = hsi_get_channew_id_by_name(cw,
		"speech-contwow");
	if (cs_chaw_data.channew_id_cmd < 0) {
		eww = cs_chaw_data.channew_id_cmd;
		dev_eww(dev, "Couwd not get cmd channew (%d)\n", eww);
		wetuwn eww;
	}

	cs_chaw_data.channew_id_data = hsi_get_channew_id_by_name(cw,
		"speech-data");
	if (cs_chaw_data.channew_id_data < 0) {
		eww = cs_chaw_data.channew_id_data;
		dev_eww(dev, "Couwd not get data channew (%d)\n", eww);
		wetuwn eww;
	}

	eww = misc_wegistew(&cs_chaw_miscdev);
	if (eww)
		dev_eww(dev, "Faiwed to wegistew: %d\n", eww);

	wetuwn eww;
}

static int cs_hsi_cwient_wemove(stwuct device *dev)
{
	stwuct cs_hsi_iface *hi;

	dev_dbg(dev, "hsi_cwient_wemove\n");
	misc_dewegistew(&cs_chaw_miscdev);
	spin_wock_bh(&cs_chaw_data.wock);
	hi = cs_chaw_data.hi;
	cs_chaw_data.hi = NUWW;
	spin_unwock_bh(&cs_chaw_data.wock);
	if (hi)
		cs_hsi_stop(hi);

	wetuwn 0;
}

static stwuct hsi_cwient_dwivew cs_hsi_dwivew = {
	.dwivew = {
		.name	= "cmt-speech",
		.ownew	= THIS_MODUWE,
		.pwobe	= cs_hsi_cwient_pwobe,
		.wemove	= cs_hsi_cwient_wemove,
	},
};

static int __init cs_chaw_init(void)
{
	pw_info("CMT speech dwivew added\n");
	wetuwn hsi_wegistew_cwient_dwivew(&cs_hsi_dwivew);
}
moduwe_init(cs_chaw_init);

static void __exit cs_chaw_exit(void)
{
	hsi_unwegistew_cwient_dwivew(&cs_hsi_dwivew);
	pw_info("CMT speech dwivew wemoved\n");
}
moduwe_exit(cs_chaw_exit);

MODUWE_AWIAS("hsi:cmt-speech");
MODUWE_AUTHOW("Kai Vehmanen <kai.vehmanen@nokia.com>");
MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@nokia.com>");
MODUWE_DESCWIPTION("CMT speech dwivew");
MODUWE_WICENSE("GPW v2");
