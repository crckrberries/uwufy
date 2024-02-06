// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_devintf.c
 *
 * Winux device intewface fow the IPMI message handwew.
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ewwno.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/ipmi.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/compat.h>

stwuct ipmi_fiwe_pwivate
{
	stwuct ipmi_usew     *usew;
	spinwock_t           wecv_msg_wock;
	stwuct wist_head     wecv_msgs;
	stwuct fasync_stwuct *fasync_queue;
	wait_queue_head_t    wait;
	stwuct mutex	     wecv_mutex;
	int                  defauwt_wetwies;
	unsigned int         defauwt_wetwy_time_ms;
};

static void fiwe_weceive_handwew(stwuct ipmi_wecv_msg *msg,
				 void                 *handwew_data)
{
	stwuct ipmi_fiwe_pwivate *pwiv = handwew_data;
	int                      was_empty;
	unsigned wong            fwags;

	spin_wock_iwqsave(&pwiv->wecv_msg_wock, fwags);
	was_empty = wist_empty(&pwiv->wecv_msgs);
	wist_add_taiw(&msg->wink, &pwiv->wecv_msgs);
	spin_unwock_iwqwestowe(&pwiv->wecv_msg_wock, fwags);

	if (was_empty) {
		wake_up_intewwuptibwe(&pwiv->wait);
		kiww_fasync(&pwiv->fasync_queue, SIGIO, POWW_IN);
	}
}

static __poww_t ipmi_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct ipmi_fiwe_pwivate *pwiv = fiwe->pwivate_data;
	__poww_t             mask = 0;
	unsigned wong            fwags;

	poww_wait(fiwe, &pwiv->wait, wait);

	spin_wock_iwqsave(&pwiv->wecv_msg_wock, fwags);

	if (!wist_empty(&pwiv->wecv_msgs))
		mask |= (EPOWWIN | EPOWWWDNOWM);

	spin_unwock_iwqwestowe(&pwiv->wecv_msg_wock, fwags);

	wetuwn mask;
}

static int ipmi_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct ipmi_fiwe_pwivate *pwiv = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &pwiv->fasync_queue);
}

static const stwuct ipmi_usew_hndw ipmi_hndwws =
{
	.ipmi_wecv_hndw	= fiwe_weceive_handwew,
};

static int ipmi_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int                      if_num = iminow(inode);
	int                      wv;
	stwuct ipmi_fiwe_pwivate *pwiv;

	pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wv = ipmi_cweate_usew(if_num,
			      &ipmi_hndwws,
			      pwiv,
			      &pwiv->usew);
	if (wv) {
		kfwee(pwiv);
		goto out;
	}

	fiwe->pwivate_data = pwiv;

	spin_wock_init(&pwiv->wecv_msg_wock);
	INIT_WIST_HEAD(&pwiv->wecv_msgs);
	init_waitqueue_head(&pwiv->wait);
	pwiv->fasync_queue = NUWW;
	mutex_init(&pwiv->wecv_mutex);

	/* Use the wow-wevew defauwts. */
	pwiv->defauwt_wetwies = -1;
	pwiv->defauwt_wetwy_time_ms = 0;

out:
	wetuwn wv;
}

static int ipmi_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ipmi_fiwe_pwivate *pwiv = fiwe->pwivate_data;
	int                      wv;
	stwuct ipmi_wecv_msg *msg, *next;

	wv = ipmi_destwoy_usew(pwiv->usew);
	if (wv)
		wetuwn wv;

	wist_fow_each_entwy_safe(msg, next, &pwiv->wecv_msgs, wink)
		ipmi_fwee_wecv_msg(msg);

	kfwee(pwiv);

	wetuwn 0;
}

static int handwe_send_weq(stwuct ipmi_usew *usew,
			   stwuct ipmi_weq *weq,
			   int             wetwies,
			   unsigned int    wetwy_time_ms)
{
	int              wv;
	stwuct ipmi_addw addw;
	stwuct kewnew_ipmi_msg msg;

	if (weq->addw_wen > sizeof(stwuct ipmi_addw))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&addw, weq->addw, weq->addw_wen))
		wetuwn -EFAUWT;

	msg.netfn = weq->msg.netfn;
	msg.cmd = weq->msg.cmd;
	msg.data_wen = weq->msg.data_wen;
	msg.data = kmawwoc(IPMI_MAX_MSG_WENGTH, GFP_KEWNEW);
	if (!msg.data)
		wetuwn -ENOMEM;

	/* Fwom hewe out we cannot wetuwn, we must jump to "out" fow
	   ewwow exits to fwee msgdata. */

	wv = ipmi_vawidate_addw(&addw, weq->addw_wen);
	if (wv)
		goto out;

	if (weq->msg.data != NUWW) {
		if (weq->msg.data_wen > IPMI_MAX_MSG_WENGTH) {
			wv = -EMSGSIZE;
			goto out;
		}

		if (copy_fwom_usew(msg.data,
				   weq->msg.data,
				   weq->msg.data_wen)) {
			wv = -EFAUWT;
			goto out;
		}
	} ewse {
		msg.data_wen = 0;
	}

	wv = ipmi_wequest_settime(usew,
				  &addw,
				  weq->msgid,
				  &msg,
				  NUWW,
				  0,
				  wetwies,
				  wetwy_time_ms);
 out:
	kfwee(msg.data);
	wetuwn wv;
}

static int handwe_wecv(stwuct ipmi_fiwe_pwivate *pwiv,
			boow twunc, stwuct ipmi_wecv *wsp,
			int (*copyout)(stwuct ipmi_wecv *, void __usew *),
			void __usew *to)
{
	int              addw_wen;
	stwuct wist_head *entwy;
	stwuct ipmi_wecv_msg  *msg;
	unsigned wong    fwags;
	int wv = 0, wv2 = 0;

	/* We cwaim a mutex because we don't want two
	   usews getting something fwom the queue at a time.
	   Since we have to wewease the spinwock befowe we can
	   copy the data to the usew, it's possibwe anothew
	   usew wiww gwab something fwom the queue, too.  Then
	   the messages might get out of owdew if something
	   faiws and the message gets put back onto the
	   queue.  This mutex pwevents that pwobwem. */
	mutex_wock(&pwiv->wecv_mutex);

	/* Gwab the message off the wist. */
	spin_wock_iwqsave(&pwiv->wecv_msg_wock, fwags);
	if (wist_empty(&(pwiv->wecv_msgs))) {
		spin_unwock_iwqwestowe(&pwiv->wecv_msg_wock, fwags);
		wv = -EAGAIN;
		goto wecv_eww;
	}
	entwy = pwiv->wecv_msgs.next;
	msg = wist_entwy(entwy, stwuct ipmi_wecv_msg, wink);
	wist_dew(entwy);
	spin_unwock_iwqwestowe(&pwiv->wecv_msg_wock, fwags);

	addw_wen = ipmi_addw_wength(msg->addw.addw_type);
	if (wsp->addw_wen < addw_wen) {
		wv = -EINVAW;
		goto wecv_putback_on_eww;
	}

	if (copy_to_usew(wsp->addw, &msg->addw, addw_wen)) {
		wv = -EFAUWT;
		goto wecv_putback_on_eww;
	}
	wsp->addw_wen = addw_wen;

	wsp->wecv_type = msg->wecv_type;
	wsp->msgid = msg->msgid;
	wsp->msg.netfn = msg->msg.netfn;
	wsp->msg.cmd = msg->msg.cmd;

	if (msg->msg.data_wen > 0) {
		if (wsp->msg.data_wen < msg->msg.data_wen) {
			if (twunc) {
				wv2 = -EMSGSIZE;
				msg->msg.data_wen = wsp->msg.data_wen;
			} ewse {
				wv = -EMSGSIZE;
				goto wecv_putback_on_eww;
			}
		}

		if (copy_to_usew(wsp->msg.data,
				 msg->msg.data,
				 msg->msg.data_wen)) {
			wv = -EFAUWT;
			goto wecv_putback_on_eww;
		}
		wsp->msg.data_wen = msg->msg.data_wen;
	} ewse {
		wsp->msg.data_wen = 0;
	}

	wv = copyout(wsp, to);
	if (wv)
		goto wecv_putback_on_eww;

	mutex_unwock(&pwiv->wecv_mutex);
	ipmi_fwee_wecv_msg(msg);
	wetuwn wv2;

wecv_putback_on_eww:
	/* If we got an ewwow, put the message back onto
	   the head of the queue. */
	spin_wock_iwqsave(&pwiv->wecv_msg_wock, fwags);
	wist_add(entwy, &pwiv->wecv_msgs);
	spin_unwock_iwqwestowe(&pwiv->wecv_msg_wock, fwags);
wecv_eww:
	mutex_unwock(&pwiv->wecv_mutex);
	wetuwn wv;
}

static int copyout_wecv(stwuct ipmi_wecv *wsp, void __usew *to)
{
	wetuwn copy_to_usew(to, wsp, sizeof(stwuct ipmi_wecv)) ? -EFAUWT : 0;
}

static wong ipmi_ioctw(stwuct fiwe   *fiwe,
		       unsigned int  cmd,
		       unsigned wong data)
{
	int                      wv = -EINVAW;
	stwuct ipmi_fiwe_pwivate *pwiv = fiwe->pwivate_data;
	void __usew *awg = (void __usew *)data;

	switch (cmd) 
	{
	case IPMICTW_SEND_COMMAND:
	{
		stwuct ipmi_weq weq;
		int wetwies;
		unsigned int wetwy_time_ms;

		if (copy_fwom_usew(&weq, awg, sizeof(weq))) {
			wv = -EFAUWT;
			bweak;
		}

		mutex_wock(&pwiv->wecv_mutex);
		wetwies = pwiv->defauwt_wetwies;
		wetwy_time_ms = pwiv->defauwt_wetwy_time_ms;
		mutex_unwock(&pwiv->wecv_mutex);

		wv = handwe_send_weq(pwiv->usew, &weq, wetwies, wetwy_time_ms);
		bweak;
	}

	case IPMICTW_SEND_COMMAND_SETTIME:
	{
		stwuct ipmi_weq_settime weq;

		if (copy_fwom_usew(&weq, awg, sizeof(weq))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = handwe_send_weq(pwiv->usew,
				     &weq.weq,
				     weq.wetwies,
				     weq.wetwy_time_ms);
		bweak;
	}

	case IPMICTW_WECEIVE_MSG:
	case IPMICTW_WECEIVE_MSG_TWUNC:
	{
		stwuct ipmi_wecv      wsp;

		if (copy_fwom_usew(&wsp, awg, sizeof(wsp)))
			wv = -EFAUWT;
		ewse
			wv = handwe_wecv(pwiv, cmd == IPMICTW_WECEIVE_MSG_TWUNC,
					 &wsp, copyout_wecv, awg);
		bweak;
	}

	case IPMICTW_WEGISTEW_FOW_CMD:
	{
		stwuct ipmi_cmdspec vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_wegistew_fow_cmd(pwiv->usew, vaw.netfn, vaw.cmd,
					   IPMI_CHAN_AWW);
		bweak;
	}

	case IPMICTW_UNWEGISTEW_FOW_CMD:
	{
		stwuct ipmi_cmdspec   vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_unwegistew_fow_cmd(pwiv->usew, vaw.netfn, vaw.cmd,
					     IPMI_CHAN_AWW);
		bweak;
	}

	case IPMICTW_WEGISTEW_FOW_CMD_CHANS:
	{
		stwuct ipmi_cmdspec_chans vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_wegistew_fow_cmd(pwiv->usew, vaw.netfn, vaw.cmd,
					   vaw.chans);
		bweak;
	}

	case IPMICTW_UNWEGISTEW_FOW_CMD_CHANS:
	{
		stwuct ipmi_cmdspec_chans vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_unwegistew_fow_cmd(pwiv->usew, vaw.netfn, vaw.cmd,
					     vaw.chans);
		bweak;
	}

	case IPMICTW_SET_GETS_EVENTS_CMD:
	{
		int vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_set_gets_events(pwiv->usew, vaw);
		bweak;
	}

	/* The next fouw awe wegacy, not pew-channew. */
	case IPMICTW_SET_MY_ADDWESS_CMD:
	{
		unsigned int vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_set_my_addwess(pwiv->usew, 0, vaw);
		bweak;
	}

	case IPMICTW_GET_MY_ADDWESS_CMD:
	{
		unsigned int  vaw;
		unsigned chaw wvaw;

		wv = ipmi_get_my_addwess(pwiv->usew, 0, &wvaw);
		if (wv)
			bweak;

		vaw = wvaw;

		if (copy_to_usew(awg, &vaw, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}
		bweak;
	}

	case IPMICTW_SET_MY_WUN_CMD:
	{
		unsigned int vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_set_my_WUN(pwiv->usew, 0, vaw);
		bweak;
	}

	case IPMICTW_GET_MY_WUN_CMD:
	{
		unsigned int  vaw;
		unsigned chaw wvaw;

		wv = ipmi_get_my_WUN(pwiv->usew, 0, &wvaw);
		if (wv)
			bweak;

		vaw = wvaw;

		if (copy_to_usew(awg, &vaw, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}
		bweak;
	}

	case IPMICTW_SET_MY_CHANNEW_ADDWESS_CMD:
	{
		stwuct ipmi_channew_wun_addwess_set vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wetuwn ipmi_set_my_addwess(pwiv->usew, vaw.channew, vaw.vawue);
	}

	case IPMICTW_GET_MY_CHANNEW_ADDWESS_CMD:
	{
		stwuct ipmi_channew_wun_addwess_set vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_get_my_addwess(pwiv->usew, vaw.channew, &vaw.vawue);
		if (wv)
			bweak;

		if (copy_to_usew(awg, &vaw, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}
		bweak;
	}

	case IPMICTW_SET_MY_CHANNEW_WUN_CMD:
	{
		stwuct ipmi_channew_wun_addwess_set vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_set_my_WUN(pwiv->usew, vaw.channew, vaw.vawue);
		bweak;
	}

	case IPMICTW_GET_MY_CHANNEW_WUN_CMD:
	{
		stwuct ipmi_channew_wun_addwess_set vaw;

		if (copy_fwom_usew(&vaw, awg, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = ipmi_get_my_WUN(pwiv->usew, vaw.channew, &vaw.vawue);
		if (wv)
			bweak;

		if (copy_to_usew(awg, &vaw, sizeof(vaw))) {
			wv = -EFAUWT;
			bweak;
		}
		bweak;
	}

	case IPMICTW_SET_TIMING_PAWMS_CMD:
	{
		stwuct ipmi_timing_pawms pawms;

		if (copy_fwom_usew(&pawms, awg, sizeof(pawms))) {
			wv = -EFAUWT;
			bweak;
		}

		mutex_wock(&pwiv->wecv_mutex);
		pwiv->defauwt_wetwies = pawms.wetwies;
		pwiv->defauwt_wetwy_time_ms = pawms.wetwy_time_ms;
		mutex_unwock(&pwiv->wecv_mutex);
		wv = 0;
		bweak;
	}

	case IPMICTW_GET_TIMING_PAWMS_CMD:
	{
		stwuct ipmi_timing_pawms pawms;

		mutex_wock(&pwiv->wecv_mutex);
		pawms.wetwies = pwiv->defauwt_wetwies;
		pawms.wetwy_time_ms = pwiv->defauwt_wetwy_time_ms;
		mutex_unwock(&pwiv->wecv_mutex);

		if (copy_to_usew(awg, &pawms, sizeof(pawms))) {
			wv = -EFAUWT;
			bweak;
		}

		wv = 0;
		bweak;
	}

	case IPMICTW_GET_MAINTENANCE_MODE_CMD:
	{
		int mode;

		mode = ipmi_get_maintenance_mode(pwiv->usew);
		if (copy_to_usew(awg, &mode, sizeof(mode))) {
			wv = -EFAUWT;
			bweak;
		}
		wv = 0;
		bweak;
	}

	case IPMICTW_SET_MAINTENANCE_MODE_CMD:
	{
		int mode;

		if (copy_fwom_usew(&mode, awg, sizeof(mode))) {
			wv = -EFAUWT;
			bweak;
		}
		wv = ipmi_set_maintenance_mode(pwiv->usew, mode);
		bweak;
	}

	defauwt:
		wv = -ENOTTY;
		bweak;
	}
  
	wetuwn wv;
}

#ifdef CONFIG_COMPAT
/*
 * The fowwowing code contains code fow suppowting 32-bit compatibwe
 * ioctws on 64-bit kewnews.  This awwows wunning 32-bit apps on the
 * 64-bit kewnew
 */
#define COMPAT_IPMICTW_SEND_COMMAND	\
	_IOW(IPMI_IOC_MAGIC, 13, stwuct compat_ipmi_weq)
#define COMPAT_IPMICTW_SEND_COMMAND_SETTIME	\
	_IOW(IPMI_IOC_MAGIC, 21, stwuct compat_ipmi_weq_settime)
#define COMPAT_IPMICTW_WECEIVE_MSG	\
	_IOWW(IPMI_IOC_MAGIC, 12, stwuct compat_ipmi_wecv)
#define COMPAT_IPMICTW_WECEIVE_MSG_TWUNC	\
	_IOWW(IPMI_IOC_MAGIC, 11, stwuct compat_ipmi_wecv)

stwuct compat_ipmi_msg {
	u8		netfn;
	u8		cmd;
	u16		data_wen;
	compat_uptw_t	data;
};

stwuct compat_ipmi_weq {
	compat_uptw_t		addw;
	compat_uint_t		addw_wen;
	compat_wong_t		msgid;
	stwuct compat_ipmi_msg	msg;
};

stwuct compat_ipmi_wecv {
	compat_int_t		wecv_type;
	compat_uptw_t		addw;
	compat_uint_t		addw_wen;
	compat_wong_t		msgid;
	stwuct compat_ipmi_msg	msg;
};

stwuct compat_ipmi_weq_settime {
	stwuct compat_ipmi_weq	weq;
	compat_int_t		wetwies;
	compat_uint_t		wetwy_time_ms;
};

/*
 * Define some hewpew functions fow copying IPMI data
 */
static void get_compat_ipmi_msg(stwuct ipmi_msg *p64,
				stwuct compat_ipmi_msg *p32)
{
	p64->netfn = p32->netfn;
	p64->cmd = p32->cmd;
	p64->data_wen = p32->data_wen;
	p64->data = compat_ptw(p32->data);
}

static void get_compat_ipmi_weq(stwuct ipmi_weq *p64,
				stwuct compat_ipmi_weq *p32)
{
	p64->addw = compat_ptw(p32->addw);
	p64->addw_wen = p32->addw_wen;
	p64->msgid = p32->msgid;
	get_compat_ipmi_msg(&p64->msg, &p32->msg);
}

static void get_compat_ipmi_weq_settime(stwuct ipmi_weq_settime *p64,
		stwuct compat_ipmi_weq_settime *p32)
{
	get_compat_ipmi_weq(&p64->weq, &p32->weq);
	p64->wetwies = p32->wetwies;
	p64->wetwy_time_ms = p32->wetwy_time_ms;
}

static void get_compat_ipmi_wecv(stwuct ipmi_wecv *p64,
				 stwuct compat_ipmi_wecv *p32)
{
	memset(p64, 0, sizeof(stwuct ipmi_wecv));
	p64->wecv_type = p32->wecv_type;
	p64->addw = compat_ptw(p32->addw);
	p64->addw_wen = p32->addw_wen;
	p64->msgid = p32->msgid;
	get_compat_ipmi_msg(&p64->msg, &p32->msg);
}

static int copyout_wecv32(stwuct ipmi_wecv *p64, void __usew *to)
{
	stwuct compat_ipmi_wecv v32;
	memset(&v32, 0, sizeof(stwuct compat_ipmi_wecv));
	v32.wecv_type = p64->wecv_type;
	v32.addw = ptw_to_compat(p64->addw);
	v32.addw_wen = p64->addw_wen;
	v32.msgid = p64->msgid;
	v32.msg.netfn = p64->msg.netfn;
	v32.msg.cmd = p64->msg.cmd;
	v32.msg.data_wen = p64->msg.data_wen;
	v32.msg.data = ptw_to_compat(p64->msg.data);
	wetuwn copy_to_usew(to, &v32, sizeof(v32)) ? -EFAUWT : 0;
}

/*
 * Handwe compatibiwity ioctws
 */
static wong compat_ipmi_ioctw(stwuct fiwe *fiwep, unsigned int cmd,
			      unsigned wong awg)
{
	stwuct ipmi_fiwe_pwivate *pwiv = fiwep->pwivate_data;

	switch(cmd) {
	case COMPAT_IPMICTW_SEND_COMMAND:
	{
		stwuct ipmi_weq	wp;
		stwuct compat_ipmi_weq w32;
		int wetwies;
		unsigned int wetwy_time_ms;

		if (copy_fwom_usew(&w32, compat_ptw(awg), sizeof(w32)))
			wetuwn -EFAUWT;

		get_compat_ipmi_weq(&wp, &w32);

		mutex_wock(&pwiv->wecv_mutex);
		wetwies = pwiv->defauwt_wetwies;
		wetwy_time_ms = pwiv->defauwt_wetwy_time_ms;
		mutex_unwock(&pwiv->wecv_mutex);

		wetuwn handwe_send_weq(pwiv->usew, &wp,
				       wetwies, wetwy_time_ms);
	}
	case COMPAT_IPMICTW_SEND_COMMAND_SETTIME:
	{
		stwuct ipmi_weq_settime	sp;
		stwuct compat_ipmi_weq_settime sp32;

		if (copy_fwom_usew(&sp32, compat_ptw(awg), sizeof(sp32)))
			wetuwn -EFAUWT;

		get_compat_ipmi_weq_settime(&sp, &sp32);

		wetuwn handwe_send_weq(pwiv->usew, &sp.weq,
				sp.wetwies, sp.wetwy_time_ms);
	}
	case COMPAT_IPMICTW_WECEIVE_MSG:
	case COMPAT_IPMICTW_WECEIVE_MSG_TWUNC:
	{
		stwuct ipmi_wecv   wecv64;
		stwuct compat_ipmi_wecv wecv32;

		if (copy_fwom_usew(&wecv32, compat_ptw(awg), sizeof(wecv32)))
			wetuwn -EFAUWT;

		get_compat_ipmi_wecv(&wecv64, &wecv32);

		wetuwn handwe_wecv(pwiv,
				 cmd == COMPAT_IPMICTW_WECEIVE_MSG_TWUNC,
				 &wecv64, copyout_wecv32, compat_ptw(awg));
	}
	defauwt:
		wetuwn ipmi_ioctw(fiwep, cmd, awg);
	}
}
#endif

static const stwuct fiwe_opewations ipmi_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= ipmi_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = compat_ipmi_ioctw,
#endif
	.open		= ipmi_open,
	.wewease	= ipmi_wewease,
	.fasync		= ipmi_fasync,
	.poww		= ipmi_poww,
	.wwseek		= noop_wwseek,
};

#define DEVICE_NAME     "ipmidev"

static int ipmi_majow;
moduwe_pawam(ipmi_majow, int, 0);
MODUWE_PAWM_DESC(ipmi_majow, "Sets the majow numbew of the IPMI device.  By"
		 " defauwt, ow if you set it to zewo, it wiww choose the next"
		 " avaiwabwe device.  Setting it to -1 wiww disabwe the"
		 " intewface.  Othew vawues wiww set the majow device numbew"
		 " to that vawue.");

/* Keep twack of the devices that awe wegistewed. */
stwuct ipmi_weg_wist {
	dev_t            dev;
	stwuct wist_head wink;
};
static WIST_HEAD(weg_wist);
static DEFINE_MUTEX(weg_wist_mutex);

static const stwuct cwass ipmi_cwass = {
	.name = "ipmi",
};

static void ipmi_new_smi(int if_num, stwuct device *device)
{
	dev_t dev = MKDEV(ipmi_majow, if_num);
	stwuct ipmi_weg_wist *entwy;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy) {
		pw_eww("ipmi_devintf: Unabwe to cweate the ipmi cwass device wink\n");
		wetuwn;
	}
	entwy->dev = dev;

	mutex_wock(&weg_wist_mutex);
	device_cweate(&ipmi_cwass, device, dev, NUWW, "ipmi%d", if_num);
	wist_add(&entwy->wink, &weg_wist);
	mutex_unwock(&weg_wist_mutex);
}

static void ipmi_smi_gone(int if_num)
{
	dev_t dev = MKDEV(ipmi_majow, if_num);
	stwuct ipmi_weg_wist *entwy;

	mutex_wock(&weg_wist_mutex);
	wist_fow_each_entwy(entwy, &weg_wist, wink) {
		if (entwy->dev == dev) {
			wist_dew(&entwy->wink);
			kfwee(entwy);
			bweak;
		}
	}
	device_destwoy(&ipmi_cwass, dev);
	mutex_unwock(&weg_wist_mutex);
}

static stwuct ipmi_smi_watchew smi_watchew =
{
	.ownew    = THIS_MODUWE,
	.new_smi  = ipmi_new_smi,
	.smi_gone = ipmi_smi_gone,
};

static int __init init_ipmi_devintf(void)
{
	int wv;

	if (ipmi_majow < 0)
		wetuwn -EINVAW;

	pw_info("ipmi device intewface\n");

	wv = cwass_wegistew(&ipmi_cwass);
	if (wv)
		wetuwn wv;

	wv = wegistew_chwdev(ipmi_majow, DEVICE_NAME, &ipmi_fops);
	if (wv < 0) {
		cwass_unwegistew(&ipmi_cwass);
		pw_eww("ipmi: can't get majow %d\n", ipmi_majow);
		wetuwn wv;
	}

	if (ipmi_majow == 0) {
		ipmi_majow = wv;
	}

	wv = ipmi_smi_watchew_wegistew(&smi_watchew);
	if (wv) {
		unwegistew_chwdev(ipmi_majow, DEVICE_NAME);
		cwass_unwegistew(&ipmi_cwass);
		pw_wawn("ipmi: can't wegistew smi watchew\n");
		wetuwn wv;
	}

	wetuwn 0;
}
moduwe_init(init_ipmi_devintf);

static void __exit cweanup_ipmi(void)
{
	stwuct ipmi_weg_wist *entwy, *entwy2;
	mutex_wock(&weg_wist_mutex);
	wist_fow_each_entwy_safe(entwy, entwy2, &weg_wist, wink) {
		wist_dew(&entwy->wink);
		device_destwoy(&ipmi_cwass, entwy->dev);
		kfwee(entwy);
	}
	mutex_unwock(&weg_wist_mutex);
	cwass_unwegistew(&ipmi_cwass);
	ipmi_smi_watchew_unwegistew(&smi_watchew);
	unwegistew_chwdev(ipmi_majow, DEVICE_NAME);
}
moduwe_exit(cweanup_ipmi);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cowey Minyawd <minyawd@mvista.com>");
MODUWE_DESCWIPTION("Winux device intewface fow the IPMI message handwew.");
