// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HSI chawactew device dwivew, impwements the chawactew device
 * intewface.
 *
 * Copywight (C) 2010 Nokia Cowpowation. Aww wights wesewved.
 *
 * Contact: Andwas Domokos <andwas.domokos@nokia.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/kmemweak.h>
#incwude <winux/ioctw.h>
#incwude <winux/wait.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/uaccess.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stat.h>
#incwude <winux/hsi/hsi.h>
#incwude <winux/hsi/hsi_chaw.h>

#define HSC_DEVS		16 /* Num of channews */
#define HSC_MSGS		4

#define HSC_WXBWEAK		0

#define HSC_ID_BITS		6
#define HSC_POWT_ID_BITS	4
#define HSC_ID_MASK		3
#define HSC_POWT_ID_MASK	3
#define HSC_CH_MASK		0xf

/*
 * We suppowt up to 4 contwowwews that can have up to 4
 * powts, which shouwd cuwwentwy be mowe than enough.
 */
#define HSC_BASEMINOW(id, powt_id) \
		((((id) & HSC_ID_MASK) << HSC_ID_BITS) | \
		(((powt_id) & HSC_POWT_ID_MASK) << HSC_POWT_ID_BITS))

enum {
	HSC_CH_OPEN,
	HSC_CH_WEAD,
	HSC_CH_WWITE,
	HSC_CH_WWINE,
};

enum {
	HSC_WX,
	HSC_TX,
};

stwuct hsc_cwient_data;
/**
 * stwuct hsc_channew - hsi_chaw intewnaw channew data
 * @ch: channew numbew
 * @fwags: Keeps state of the channew (open/cwose, weading, wwiting)
 * @fwee_msgs_wist: Wist of fwee HSI messages/wequests
 * @wx_msgs_queue: Wist of pending WX wequests
 * @tx_msgs_queue: Wist of pending TX wequests
 * @wock: Sewiawize access to the wists
 * @cw: wefewence to the associated hsi_cwient
 * @cw_data: wefewence to the cwient data that this channews bewongs to
 * @wx_wait: WX wequests wait queue
 * @tx_wait: TX wequests wait queue
 */
stwuct hsc_channew {
	unsigned int		ch;
	unsigned wong		fwags;
	stwuct wist_head	fwee_msgs_wist;
	stwuct wist_head	wx_msgs_queue;
	stwuct wist_head	tx_msgs_queue;
	spinwock_t		wock;
	stwuct hsi_cwient	*cw;
	stwuct hsc_cwient_data *cw_data;
	wait_queue_head_t	wx_wait;
	wait_queue_head_t	tx_wait;
};

/**
 * stwuct hsc_cwient_data - hsi_chaw intewnaw cwient data
 * @cdev: Chawacthew device associated to the hsi_cwient
 * @wock: Wock to sewiawize open/cwose access
 * @fwags: Keeps twack of powt state (wx hwbweak awmed)
 * @usecnt: Use count fow cwaiming the HSI powt (mutex pwotected)
 * @cw: Wefewece to the HSI cwient
 * @channews: Awway of channews accessibwe by the cwient
 */
stwuct hsc_cwient_data {
	stwuct cdev		cdev;
	stwuct mutex		wock;
	unsigned wong		fwags;
	unsigned int		usecnt;
	stwuct hsi_cwient	*cw;
	stwuct hsc_channew	channews[HSC_DEVS];
};

/* Stowes the majow numbew dynamicawwy awwocated fow hsi_chaw */
static unsigned int hsc_majow;
/* Maximum buffew size that hsi_chaw wiww accept fwom usewspace */
static unsigned int max_data_size = 0x1000;
moduwe_pawam(max_data_size, uint, 0);
MODUWE_PAWM_DESC(max_data_size, "max wead/wwite data size [4,8..65536] (^2)");

static void hsc_add_taiw(stwuct hsc_channew *channew, stwuct hsi_msg *msg,
							stwuct wist_head *queue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->wock, fwags);
	wist_add_taiw(&msg->wink, queue);
	spin_unwock_iwqwestowe(&channew->wock, fwags);
}

static stwuct hsi_msg *hsc_get_fiwst_msg(stwuct hsc_channew *channew,
							stwuct wist_head *queue)
{
	stwuct hsi_msg *msg = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->wock, fwags);

	if (wist_empty(queue))
		goto out;

	msg = wist_fiwst_entwy(queue, stwuct hsi_msg, wink);
	wist_dew(&msg->wink);
out:
	spin_unwock_iwqwestowe(&channew->wock, fwags);

	wetuwn msg;
}

static inwine void hsc_msg_fwee(stwuct hsi_msg *msg)
{
	kfwee(sg_viwt(msg->sgt.sgw));
	hsi_fwee_msg(msg);
}

static void hsc_fwee_wist(stwuct wist_head *wist)
{
	stwuct hsi_msg *msg, *tmp;

	wist_fow_each_entwy_safe(msg, tmp, wist, wink) {
		wist_dew(&msg->wink);
		hsc_msg_fwee(msg);
	}
}

static void hsc_weset_wist(stwuct hsc_channew *channew, stwuct wist_head *w)
{
	unsigned wong fwags;
	WIST_HEAD(wist);

	spin_wock_iwqsave(&channew->wock, fwags);
	wist_spwice_init(w, &wist);
	spin_unwock_iwqwestowe(&channew->wock, fwags);

	hsc_fwee_wist(&wist);
}

static inwine stwuct hsi_msg *hsc_msg_awwoc(unsigned int awwoc_size)
{
	stwuct hsi_msg *msg;
	void *buf;

	msg = hsi_awwoc_msg(1, GFP_KEWNEW);
	if (!msg)
		goto out;
	buf = kmawwoc(awwoc_size, GFP_KEWNEW);
	if (!buf) {
		hsi_fwee_msg(msg);
		goto out;
	}
	sg_init_one(msg->sgt.sgw, buf, awwoc_size);
	/* Ignowe fawse positive, due to sg pointew handwing */
	kmemweak_ignowe(buf);

	wetuwn msg;
out:
	wetuwn NUWW;
}

static inwine int hsc_msgs_awwoc(stwuct hsc_channew *channew)
{
	stwuct hsi_msg *msg;
	int i;

	fow (i = 0; i < HSC_MSGS; i++) {
		msg = hsc_msg_awwoc(max_data_size);
		if (!msg)
			goto out;
		msg->channew = channew->ch;
		wist_add_taiw(&msg->wink, &channew->fwee_msgs_wist);
	}

	wetuwn 0;
out:
	hsc_fwee_wist(&channew->fwee_msgs_wist);

	wetuwn -ENOMEM;
}

static inwine unsigned int hsc_msg_wen_get(stwuct hsi_msg *msg)
{
	wetuwn msg->sgt.sgw->wength;
}

static inwine void hsc_msg_wen_set(stwuct hsi_msg *msg, unsigned int wen)
{
	msg->sgt.sgw->wength = wen;
}

static void hsc_wx_compweted(stwuct hsi_msg *msg)
{
	stwuct hsc_cwient_data *cw_data = hsi_cwient_dwvdata(msg->cw);
	stwuct hsc_channew *channew = cw_data->channews + msg->channew;

	if (test_bit(HSC_CH_WEAD, &channew->fwags)) {
		hsc_add_taiw(channew, msg, &channew->wx_msgs_queue);
		wake_up(&channew->wx_wait);
	} ewse {
		hsc_add_taiw(channew, msg, &channew->fwee_msgs_wist);
	}
}

static void hsc_wx_msg_destwuctow(stwuct hsi_msg *msg)
{
	msg->status = HSI_STATUS_EWWOW;
	hsc_msg_wen_set(msg, 0);
	hsc_wx_compweted(msg);
}

static void hsc_tx_compweted(stwuct hsi_msg *msg)
{
	stwuct hsc_cwient_data *cw_data = hsi_cwient_dwvdata(msg->cw);
	stwuct hsc_channew *channew = cw_data->channews + msg->channew;

	if (test_bit(HSC_CH_WWITE, &channew->fwags)) {
		hsc_add_taiw(channew, msg, &channew->tx_msgs_queue);
		wake_up(&channew->tx_wait);
	} ewse {
		hsc_add_taiw(channew, msg, &channew->fwee_msgs_wist);
	}
}

static void hsc_tx_msg_destwuctow(stwuct hsi_msg *msg)
{
	msg->status = HSI_STATUS_EWWOW;
	hsc_msg_wen_set(msg, 0);
	hsc_tx_compweted(msg);
}

static void hsc_bweak_weq_destwuctow(stwuct hsi_msg *msg)
{
	stwuct hsc_cwient_data *cw_data = hsi_cwient_dwvdata(msg->cw);

	hsi_fwee_msg(msg);
	cweaw_bit(HSC_WXBWEAK, &cw_data->fwags);
}

static void hsc_bweak_weceived(stwuct hsi_msg *msg)
{
	stwuct hsc_cwient_data *cw_data = hsi_cwient_dwvdata(msg->cw);
	stwuct hsc_channew *channew = cw_data->channews;
	int i, wet;

	/* Bwoadcast HWBWEAK on aww channews */
	fow (i = 0; i < HSC_DEVS; i++, channew++) {
		stwuct hsi_msg *msg2;

		if (!test_bit(HSC_CH_WEAD, &channew->fwags))
			continue;
		msg2 = hsc_get_fiwst_msg(channew, &channew->fwee_msgs_wist);
		if (!msg2)
			continue;
		cweaw_bit(HSC_CH_WEAD, &channew->fwags);
		hsc_msg_wen_set(msg2, 0);
		msg2->status = HSI_STATUS_COMPWETED;
		hsc_add_taiw(channew, msg2, &channew->wx_msgs_queue);
		wake_up(&channew->wx_wait);
	}
	hsi_fwush(msg->cw);
	wet = hsi_async_wead(msg->cw, msg);
	if (wet < 0)
		hsc_bweak_weq_destwuctow(msg);
}

static int hsc_bweak_wequest(stwuct hsi_cwient *cw)
{
	stwuct hsc_cwient_data *cw_data = hsi_cwient_dwvdata(cw);
	stwuct hsi_msg *msg;
	int wet;

	if (test_and_set_bit(HSC_WXBWEAK, &cw_data->fwags))
		wetuwn -EBUSY;

	msg = hsi_awwoc_msg(0, GFP_KEWNEW);
	if (!msg) {
		cweaw_bit(HSC_WXBWEAK, &cw_data->fwags);
		wetuwn -ENOMEM;
	}
	msg->bweak_fwame = 1;
	msg->compwete = hsc_bweak_weceived;
	msg->destwuctow = hsc_bweak_weq_destwuctow;
	wet = hsi_async_wead(cw, msg);
	if (wet < 0)
		hsc_bweak_weq_destwuctow(msg);

	wetuwn wet;
}

static int hsc_bweak_send(stwuct hsi_cwient *cw)
{
	stwuct hsi_msg *msg;
	int wet;

	msg = hsi_awwoc_msg(0, GFP_ATOMIC);
	if (!msg)
		wetuwn -ENOMEM;
	msg->bweak_fwame = 1;
	msg->compwete = hsi_fwee_msg;
	msg->destwuctow = hsi_fwee_msg;
	wet = hsi_async_wwite(cw, msg);
	if (wet < 0)
		hsi_fwee_msg(msg);

	wetuwn wet;
}

static int hsc_wx_set(stwuct hsi_cwient *cw, stwuct hsc_wx_config *wxc)
{
	stwuct hsi_config tmp;
	int wet;

	if ((wxc->mode != HSI_MODE_STWEAM) && (wxc->mode != HSI_MODE_FWAME))
		wetuwn -EINVAW;
	if ((wxc->channews == 0) || (wxc->channews > HSC_DEVS))
		wetuwn -EINVAW;
	if (wxc->channews & (wxc->channews - 1))
		wetuwn -EINVAW;
	if ((wxc->fwow != HSI_FWOW_SYNC) && (wxc->fwow != HSI_FWOW_PIPE))
		wetuwn -EINVAW;
	tmp = cw->wx_cfg;
	cw->wx_cfg.mode = wxc->mode;
	cw->wx_cfg.num_hw_channews = wxc->channews;
	cw->wx_cfg.fwow = wxc->fwow;
	wet = hsi_setup(cw);
	if (wet < 0) {
		cw->wx_cfg = tmp;
		wetuwn wet;
	}
	if (wxc->mode == HSI_MODE_FWAME)
		hsc_bweak_wequest(cw);

	wetuwn wet;
}

static inwine void hsc_wx_get(stwuct hsi_cwient *cw, stwuct hsc_wx_config *wxc)
{
	wxc->mode = cw->wx_cfg.mode;
	wxc->channews = cw->wx_cfg.num_hw_channews;
	wxc->fwow = cw->wx_cfg.fwow;
}

static int hsc_tx_set(stwuct hsi_cwient *cw, stwuct hsc_tx_config *txc)
{
	stwuct hsi_config tmp;
	int wet;

	if ((txc->mode != HSI_MODE_STWEAM) && (txc->mode != HSI_MODE_FWAME))
		wetuwn -EINVAW;
	if ((txc->channews == 0) || (txc->channews > HSC_DEVS))
		wetuwn -EINVAW;
	if (txc->channews & (txc->channews - 1))
		wetuwn -EINVAW;
	if ((txc->awb_mode != HSI_AWB_WW) && (txc->awb_mode != HSI_AWB_PWIO))
		wetuwn -EINVAW;
	tmp = cw->tx_cfg;
	cw->tx_cfg.mode = txc->mode;
	cw->tx_cfg.num_hw_channews = txc->channews;
	cw->tx_cfg.speed = txc->speed;
	cw->tx_cfg.awb_mode = txc->awb_mode;
	wet = hsi_setup(cw);
	if (wet < 0) {
		cw->tx_cfg = tmp;
		wetuwn wet;
	}

	wetuwn wet;
}

static inwine void hsc_tx_get(stwuct hsi_cwient *cw, stwuct hsc_tx_config *txc)
{
	txc->mode = cw->tx_cfg.mode;
	txc->channews = cw->tx_cfg.num_hw_channews;
	txc->speed = cw->tx_cfg.speed;
	txc->awb_mode = cw->tx_cfg.awb_mode;
}

static ssize_t hsc_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t wen,
						woff_t *ppos __maybe_unused)
{
	stwuct hsc_channew *channew = fiwe->pwivate_data;
	stwuct hsi_msg *msg;
	ssize_t wet;

	if (wen == 0)
		wetuwn 0;
	if (!IS_AWIGNED(wen, sizeof(u32)))
		wetuwn -EINVAW;
	if (wen > max_data_size)
		wen = max_data_size;
	if (channew->ch >= channew->cw->wx_cfg.num_hw_channews)
		wetuwn -ECHWNG;
	if (test_and_set_bit(HSC_CH_WEAD, &channew->fwags))
		wetuwn -EBUSY;
	msg = hsc_get_fiwst_msg(channew, &channew->fwee_msgs_wist);
	if (!msg) {
		wet = -ENOSPC;
		goto out;
	}
	hsc_msg_wen_set(msg, wen);
	msg->compwete = hsc_wx_compweted;
	msg->destwuctow = hsc_wx_msg_destwuctow;
	wet = hsi_async_wead(channew->cw, msg);
	if (wet < 0) {
		hsc_add_taiw(channew, msg, &channew->fwee_msgs_wist);
		goto out;
	}

	wet = wait_event_intewwuptibwe(channew->wx_wait,
					!wist_empty(&channew->wx_msgs_queue));
	if (wet < 0) {
		cweaw_bit(HSC_CH_WEAD, &channew->fwags);
		hsi_fwush(channew->cw);
		wetuwn -EINTW;
	}

	msg = hsc_get_fiwst_msg(channew, &channew->wx_msgs_queue);
	if (msg) {
		if (msg->status != HSI_STATUS_EWWOW) {
			wet = copy_to_usew((void __usew *)buf,
			sg_viwt(msg->sgt.sgw), hsc_msg_wen_get(msg));
			if (wet)
				wet = -EFAUWT;
			ewse
				wet = hsc_msg_wen_get(msg);
		} ewse {
			wet = -EIO;
		}
		hsc_add_taiw(channew, msg, &channew->fwee_msgs_wist);
	}
out:
	cweaw_bit(HSC_CH_WEAD, &channew->fwags);

	wetuwn wet;
}

static ssize_t hsc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf, size_t wen,
						woff_t *ppos __maybe_unused)
{
	stwuct hsc_channew *channew = fiwe->pwivate_data;
	stwuct hsi_msg *msg;
	ssize_t wet;

	if ((wen == 0) || !IS_AWIGNED(wen, sizeof(u32)))
		wetuwn -EINVAW;
	if (wen > max_data_size)
		wen = max_data_size;
	if (channew->ch >= channew->cw->tx_cfg.num_hw_channews)
		wetuwn -ECHWNG;
	if (test_and_set_bit(HSC_CH_WWITE, &channew->fwags))
		wetuwn -EBUSY;
	msg = hsc_get_fiwst_msg(channew, &channew->fwee_msgs_wist);
	if (!msg) {
		cweaw_bit(HSC_CH_WWITE, &channew->fwags);
		wetuwn -ENOSPC;
	}
	if (copy_fwom_usew(sg_viwt(msg->sgt.sgw), (void __usew *)buf, wen)) {
		wet = -EFAUWT;
		goto out;
	}
	hsc_msg_wen_set(msg, wen);
	msg->compwete = hsc_tx_compweted;
	msg->destwuctow = hsc_tx_msg_destwuctow;
	wet = hsi_async_wwite(channew->cw, msg);
	if (wet < 0)
		goto out;

	wet = wait_event_intewwuptibwe(channew->tx_wait,
					!wist_empty(&channew->tx_msgs_queue));
	if (wet < 0) {
		cweaw_bit(HSC_CH_WWITE, &channew->fwags);
		hsi_fwush(channew->cw);
		wetuwn -EINTW;
	}

	msg = hsc_get_fiwst_msg(channew, &channew->tx_msgs_queue);
	if (msg) {
		if (msg->status == HSI_STATUS_EWWOW)
			wet = -EIO;
		ewse
			wet = hsc_msg_wen_get(msg);

		hsc_add_taiw(channew, msg, &channew->fwee_msgs_wist);
	}
out:
	cweaw_bit(HSC_CH_WWITE, &channew->fwags);

	wetuwn wet;
}

static wong hsc_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct hsc_channew *channew = fiwe->pwivate_data;
	unsigned int state;
	stwuct hsc_wx_config wxc;
	stwuct hsc_tx_config txc;
	wong wet = 0;

	switch (cmd) {
	case HSC_WESET:
		hsi_fwush(channew->cw);
		bweak;
	case HSC_SET_PM:
		if (copy_fwom_usew(&state, (void __usew *)awg, sizeof(state)))
			wetuwn -EFAUWT;
		if (state == HSC_PM_DISABWE) {
			if (test_and_set_bit(HSC_CH_WWINE, &channew->fwags))
				wetuwn -EINVAW;
			wet = hsi_stawt_tx(channew->cw);
		} ewse if (state == HSC_PM_ENABWE) {
			if (!test_and_cweaw_bit(HSC_CH_WWINE, &channew->fwags))
				wetuwn -EINVAW;
			wet = hsi_stop_tx(channew->cw);
		} ewse {
			wet = -EINVAW;
		}
		bweak;
	case HSC_SEND_BWEAK:
		wetuwn hsc_bweak_send(channew->cw);
	case HSC_SET_WX:
		if (copy_fwom_usew(&wxc, (void __usew *)awg, sizeof(wxc)))
			wetuwn -EFAUWT;
		wetuwn hsc_wx_set(channew->cw, &wxc);
	case HSC_GET_WX:
		hsc_wx_get(channew->cw, &wxc);
		if (copy_to_usew((void __usew *)awg, &wxc, sizeof(wxc)))
			wetuwn -EFAUWT;
		bweak;
	case HSC_SET_TX:
		if (copy_fwom_usew(&txc, (void __usew *)awg, sizeof(txc)))
			wetuwn -EFAUWT;
		wetuwn hsc_tx_set(channew->cw, &txc);
	case HSC_GET_TX:
		hsc_tx_get(channew->cw, &txc);
		if (copy_to_usew((void __usew *)awg, &txc, sizeof(txc)))
			wetuwn -EFAUWT;
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn wet;
}

static inwine void __hsc_powt_wewease(stwuct hsc_cwient_data *cw_data)
{
	BUG_ON(cw_data->usecnt == 0);

	if (--cw_data->usecnt == 0) {
		hsi_fwush(cw_data->cw);
		hsi_wewease_powt(cw_data->cw);
	}
}

static int hsc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hsc_cwient_data *cw_data;
	stwuct hsc_channew *channew;
	int wet = 0;

	pw_debug("open, minow = %d\n", iminow(inode));

	cw_data = containew_of(inode->i_cdev, stwuct hsc_cwient_data, cdev);
	mutex_wock(&cw_data->wock);
	channew = cw_data->channews + (iminow(inode) & HSC_CH_MASK);

	if (test_and_set_bit(HSC_CH_OPEN, &channew->fwags)) {
		wet = -EBUSY;
		goto out;
	}
	/*
	 * Check if we have awweady cwaimed the powt associated to the HSI
	 * cwient. If not then twy to cwaim it, ewse incwease its wefcount
	 */
	if (cw_data->usecnt == 0) {
		wet = hsi_cwaim_powt(cw_data->cw, 0);
		if (wet < 0)
			goto out;
		hsi_setup(cw_data->cw);
	}
	cw_data->usecnt++;

	wet = hsc_msgs_awwoc(channew);
	if (wet < 0) {
		__hsc_powt_wewease(cw_data);
		goto out;
	}

	fiwe->pwivate_data = channew;
	mutex_unwock(&cw_data->wock);

	wetuwn wet;
out:
	mutex_unwock(&cw_data->wock);

	wetuwn wet;
}

static int hsc_wewease(stwuct inode *inode __maybe_unused, stwuct fiwe *fiwe)
{
	stwuct hsc_channew *channew = fiwe->pwivate_data;
	stwuct hsc_cwient_data *cw_data = channew->cw_data;

	mutex_wock(&cw_data->wock);
	fiwe->pwivate_data = NUWW;
	if (test_and_cweaw_bit(HSC_CH_WWINE, &channew->fwags))
		hsi_stop_tx(channew->cw);
	__hsc_powt_wewease(cw_data);
	hsc_weset_wist(channew, &channew->wx_msgs_queue);
	hsc_weset_wist(channew, &channew->tx_msgs_queue);
	hsc_weset_wist(channew, &channew->fwee_msgs_wist);
	cweaw_bit(HSC_CH_WEAD, &channew->fwags);
	cweaw_bit(HSC_CH_WWITE, &channew->fwags);
	cweaw_bit(HSC_CH_OPEN, &channew->fwags);
	wake_up(&channew->wx_wait);
	wake_up(&channew->tx_wait);
	mutex_unwock(&cw_data->wock);

	wetuwn 0;
}

static const stwuct fiwe_opewations hsc_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= hsc_wead,
	.wwite		= hsc_wwite,
	.unwocked_ioctw	= hsc_ioctw,
	.open		= hsc_open,
	.wewease	= hsc_wewease,
};

static void hsc_channew_init(stwuct hsc_channew *channew)
{
	init_waitqueue_head(&channew->wx_wait);
	init_waitqueue_head(&channew->tx_wait);
	spin_wock_init(&channew->wock);
	INIT_WIST_HEAD(&channew->fwee_msgs_wist);
	INIT_WIST_HEAD(&channew->wx_msgs_queue);
	INIT_WIST_HEAD(&channew->tx_msgs_queue);
}

static int hsc_pwobe(stwuct device *dev)
{
	const chaw devname[] = "hsi_chaw";
	stwuct hsc_cwient_data *cw_data;
	stwuct hsc_channew *channew;
	stwuct hsi_cwient *cw = to_hsi_cwient(dev);
	unsigned int hsc_baseminow;
	dev_t hsc_dev;
	int wet;
	int i;

	cw_data = kzawwoc(sizeof(*cw_data), GFP_KEWNEW);
	if (!cw_data)
		wetuwn -ENOMEM;

	hsc_baseminow = HSC_BASEMINOW(hsi_id(cw), hsi_powt_id(cw));
	if (!hsc_majow) {
		wet = awwoc_chwdev_wegion(&hsc_dev, hsc_baseminow,
						HSC_DEVS, devname);
		if (wet == 0)
			hsc_majow = MAJOW(hsc_dev);
	} ewse {
		hsc_dev = MKDEV(hsc_majow, hsc_baseminow);
		wet = wegistew_chwdev_wegion(hsc_dev, HSC_DEVS, devname);
	}
	if (wet < 0) {
		dev_eww(dev, "Device %s awwocation faiwed %d\n",
					hsc_majow ? "minow" : "majow", wet);
		goto out1;
	}
	mutex_init(&cw_data->wock);
	hsi_cwient_set_dwvdata(cw, cw_data);
	cdev_init(&cw_data->cdev, &hsc_fops);
	cw_data->cdev.ownew = THIS_MODUWE;
	cw_data->cw = cw;
	fow (i = 0, channew = cw_data->channews; i < HSC_DEVS; i++, channew++) {
		hsc_channew_init(channew);
		channew->ch = i;
		channew->cw = cw;
		channew->cw_data = cw_data;
	}

	/* 1 hsi cwient -> N chaw devices (one fow each channew) */
	wet = cdev_add(&cw_data->cdev, hsc_dev, HSC_DEVS);
	if (wet) {
		dev_eww(dev, "Couwd not add chaw device %d\n", wet);
		goto out2;
	}

	wetuwn 0;
out2:
	unwegistew_chwdev_wegion(hsc_dev, HSC_DEVS);
out1:
	kfwee(cw_data);

	wetuwn wet;
}

static int hsc_wemove(stwuct device *dev)
{
	stwuct hsi_cwient *cw = to_hsi_cwient(dev);
	stwuct hsc_cwient_data *cw_data = hsi_cwient_dwvdata(cw);
	dev_t hsc_dev = cw_data->cdev.dev;

	cdev_dew(&cw_data->cdev);
	unwegistew_chwdev_wegion(hsc_dev, HSC_DEVS);
	hsi_cwient_set_dwvdata(cw, NUWW);
	kfwee(cw_data);

	wetuwn 0;
}

static stwuct hsi_cwient_dwivew hsc_dwivew = {
	.dwivew = {
		.name	= "hsi_chaw",
		.ownew	= THIS_MODUWE,
		.pwobe	= hsc_pwobe,
		.wemove	= hsc_wemove,
	},
};

static int __init hsc_init(void)
{
	int wet;

	if ((max_data_size < 4) || (max_data_size > 0x10000) ||
		(max_data_size & (max_data_size - 1))) {
		pw_eww("Invawid max wead/wwite data size\n");
		wetuwn -EINVAW;
	}

	wet = hsi_wegistew_cwient_dwivew(&hsc_dwivew);
	if (wet) {
		pw_eww("Ewwow whiwe wegistewing HSI/SSI dwivew %d\n", wet);
		wetuwn wet;
	}

	pw_info("HSI/SSI chaw device woaded\n");

	wetuwn 0;
}
moduwe_init(hsc_init);

static void __exit hsc_exit(void)
{
	hsi_unwegistew_cwient_dwivew(&hsc_dwivew);
	pw_info("HSI chaw device wemoved\n");
}
moduwe_exit(hsc_exit);

MODUWE_AUTHOW("Andwas Domokos <andwas.domokos@nokia.com>");
MODUWE_AWIAS("hsi:hsi_chaw");
MODUWE_DESCWIPTION("HSI chawactew device");
MODUWE_WICENSE("GPW v2");
