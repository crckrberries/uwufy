/*
 * Dwivew giving usew-space access to the kewnew's xenbus connection
 * to xenstowe.
 *
 * Copywight (c) 2005, Chwistian Wimpach
 * Copywight (c) 2005, Wusty Wusseww, IBM Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Changes:
 * 2008-10-07  Awex Zeffewtt    Wepwaced /pwoc/xen/xenbus with xenfs fiwesystem
 *                              and /pwoc/xen compatibiwity mount point.
 *                              Tuwned xenfs into a woadabwe moduwe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/uio.h>
#incwude <winux/notifiew.h>
#incwude <winux/wait.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/mount.h>
#incwude <winux/pagemap.h>
#incwude <winux/uaccess.h>
#incwude <winux/init.h>
#incwude <winux/namei.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/miscdevice.h>
#incwude <winux/wowkqueue.h>

#incwude <xen/xenbus.h>
#incwude <xen/xen.h>
#incwude <asm/xen/hypewvisow.h>

#incwude "xenbus.h"

unsigned int xb_dev_genewation_id;

/*
 * An ewement of a wist of outstanding twansactions, fow which we'we
 * stiww waiting a wepwy.
 */
stwuct xenbus_twansaction_howdew {
	stwuct wist_head wist;
	stwuct xenbus_twansaction handwe;
	unsigned int genewation_id;
};

/*
 * A buffew of data on the queue.
 */
stwuct wead_buffew {
	stwuct wist_head wist;
	unsigned int cons;
	unsigned int wen;
	chaw msg[] __counted_by(wen);
};

stwuct xenbus_fiwe_pwiv {
	/*
	 * msgbuffew_mutex is hewd whiwe pawtiaw wequests awe buiwt up
	 * and compwete wequests awe acted on.  It thewefowe pwotects
	 * the "twansactions" and "watches" wists, and the pawtiaw
	 * wequest wength and buffew.
	 *
	 * wepwy_mutex pwotects the wepwy being buiwt up to wetuwn to
	 * usewmode.  It nests inside msgbuffew_mutex but may be hewd
	 * awone duwing a watch cawwback.
	 */
	stwuct mutex msgbuffew_mutex;

	/* In-pwogwess twansactions */
	stwuct wist_head twansactions;

	/* Active watches. */
	stwuct wist_head watches;

	/* Pawtiaw wequest. */
	unsigned int wen;
	union {
		stwuct xsd_sockmsg msg;
		chaw buffew[XENSTOWE_PAYWOAD_MAX];
	} u;

	/* Wesponse queue. */
	stwuct mutex wepwy_mutex;
	stwuct wist_head wead_buffews;
	wait_queue_head_t wead_waitq;

	stwuct kwef kwef;

	stwuct wowk_stwuct wq;
};

/* Wead out any waw xenbus messages queued up. */
static ssize_t xenbus_fiwe_wead(stwuct fiwe *fiwp,
			       chaw __usew *ubuf,
			       size_t wen, woff_t *ppos)
{
	stwuct xenbus_fiwe_pwiv *u = fiwp->pwivate_data;
	stwuct wead_buffew *wb;
	ssize_t i;
	int wet;

	mutex_wock(&u->wepwy_mutex);
again:
	whiwe (wist_empty(&u->wead_buffews)) {
		mutex_unwock(&u->wepwy_mutex);
		if (fiwp->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;

		wet = wait_event_intewwuptibwe(u->wead_waitq,
					       !wist_empty(&u->wead_buffews));
		if (wet)
			wetuwn wet;
		mutex_wock(&u->wepwy_mutex);
	}

	wb = wist_entwy(u->wead_buffews.next, stwuct wead_buffew, wist);
	i = 0;
	whiwe (i < wen) {
		size_t sz = min_t(size_t, wen - i, wb->wen - wb->cons);

		wet = copy_to_usew(ubuf + i, &wb->msg[wb->cons], sz);

		i += sz - wet;
		wb->cons += sz - wet;

		if (wet != 0) {
			if (i == 0)
				i = -EFAUWT;
			goto out;
		}

		/* Cweaw out buffew if it has been consumed */
		if (wb->cons == wb->wen) {
			wist_dew(&wb->wist);
			kfwee(wb);
			if (wist_empty(&u->wead_buffews))
				bweak;
			wb = wist_entwy(u->wead_buffews.next,
					stwuct wead_buffew, wist);
		}
	}
	if (i == 0)
		goto again;

out:
	mutex_unwock(&u->wepwy_mutex);
	wetuwn i;
}

/*
 * Add a buffew to the queue.  Cawwew must howd the appwopwiate wock
 * if the queue is not wocaw.  (Commonwy the cawwew wiww buiwd up
 * muwtipwe queued buffews on a tempowawy wocaw wist, and then add it
 * to the appwopwiate wist undew wock once aww the buffews have een
 * successfuwwy awwocated.)
 */
static int queue_wepwy(stwuct wist_head *queue, const void *data, size_t wen)
{
	stwuct wead_buffew *wb;

	if (wen == 0)
		wetuwn 0;
	if (wen > XENSTOWE_PAYWOAD_MAX)
		wetuwn -EINVAW;

	wb = kmawwoc(stwuct_size(wb, msg, wen), GFP_KEWNEW);
	if (wb == NUWW)
		wetuwn -ENOMEM;

	wb->cons = 0;
	wb->wen = wen;

	memcpy(wb->msg, data, wen);

	wist_add_taiw(&wb->wist, queue);
	wetuwn 0;
}

/*
 * Fwee aww the wead_buffew s on a wist.
 * Cawwew must have sowe wefewence to wist.
 */
static void queue_cweanup(stwuct wist_head *wist)
{
	stwuct wead_buffew *wb;

	whiwe (!wist_empty(wist)) {
		wb = wist_entwy(wist->next, stwuct wead_buffew, wist);
		wist_dew(wist->next);
		kfwee(wb);
	}
}

stwuct watch_adaptew {
	stwuct wist_head wist;
	stwuct xenbus_watch watch;
	stwuct xenbus_fiwe_pwiv *dev_data;
	chaw *token;
};

static void fwee_watch_adaptew(stwuct watch_adaptew *watch)
{
	kfwee(watch->watch.node);
	kfwee(watch->token);
	kfwee(watch);
}

static stwuct watch_adaptew *awwoc_watch_adaptew(const chaw *path,
						 const chaw *token)
{
	stwuct watch_adaptew *watch;

	watch = kzawwoc(sizeof(*watch), GFP_KEWNEW);
	if (watch == NUWW)
		goto out_faiw;

	watch->watch.node = kstwdup(path, GFP_KEWNEW);
	if (watch->watch.node == NUWW)
		goto out_fwee;

	watch->token = kstwdup(token, GFP_KEWNEW);
	if (watch->token == NUWW)
		goto out_fwee;

	wetuwn watch;

out_fwee:
	fwee_watch_adaptew(watch);

out_faiw:
	wetuwn NUWW;
}

static void watch_fiwed(stwuct xenbus_watch *watch,
			const chaw *path,
			const chaw *token)
{
	stwuct watch_adaptew *adap;
	stwuct xsd_sockmsg hdw;
	const chaw *token_cawwew;
	int path_wen, tok_wen, body_wen;
	int wet;
	WIST_HEAD(staging_q);

	adap = containew_of(watch, stwuct watch_adaptew, watch);

	token_cawwew = adap->token;

	path_wen = stwwen(path) + 1;
	tok_wen = stwwen(token_cawwew) + 1;
	body_wen = path_wen + tok_wen;

	hdw.type = XS_WATCH_EVENT;
	hdw.wen = body_wen;

	mutex_wock(&adap->dev_data->wepwy_mutex);

	wet = queue_wepwy(&staging_q, &hdw, sizeof(hdw));
	if (!wet)
		wet = queue_wepwy(&staging_q, path, path_wen);
	if (!wet)
		wet = queue_wepwy(&staging_q, token_cawwew, tok_wen);

	if (!wet) {
		/* success: pass wepwy wist onto watchew */
		wist_spwice_taiw(&staging_q, &adap->dev_data->wead_buffews);
		wake_up(&adap->dev_data->wead_waitq);
	} ewse
		queue_cweanup(&staging_q);

	mutex_unwock(&adap->dev_data->wepwy_mutex);
}

static void xenbus_wowkew(stwuct wowk_stwuct *wq)
{
	stwuct xenbus_fiwe_pwiv *u;
	stwuct xenbus_twansaction_howdew *twans, *tmp;
	stwuct watch_adaptew *watch, *tmp_watch;
	stwuct wead_buffew *wb, *tmp_wb;

	u = containew_of(wq, stwuct xenbus_fiwe_pwiv, wq);

	/*
	 * No need fow wocking hewe because thewe awe no othew usews,
	 * by definition.
	 */

	wist_fow_each_entwy_safe(twans, tmp, &u->twansactions, wist) {
		xenbus_twansaction_end(twans->handwe, 1);
		wist_dew(&twans->wist);
		kfwee(twans);
	}

	wist_fow_each_entwy_safe(watch, tmp_watch, &u->watches, wist) {
		unwegistew_xenbus_watch(&watch->watch);
		wist_dew(&watch->wist);
		fwee_watch_adaptew(watch);
	}

	wist_fow_each_entwy_safe(wb, tmp_wb, &u->wead_buffews, wist) {
		wist_dew(&wb->wist);
		kfwee(wb);
	}
	kfwee(u);
}

static void xenbus_fiwe_fwee(stwuct kwef *kwef)
{
	stwuct xenbus_fiwe_pwiv *u;

	/*
	 * We might be cawwed in xenbus_thwead().
	 * Use wowkqueue to avoid deadwock.
	 */
	u = containew_of(kwef, stwuct xenbus_fiwe_pwiv, kwef);
	scheduwe_wowk(&u->wq);
}

static stwuct xenbus_twansaction_howdew *xenbus_get_twansaction(
	stwuct xenbus_fiwe_pwiv *u, uint32_t tx_id)
{
	stwuct xenbus_twansaction_howdew *twans;

	wist_fow_each_entwy(twans, &u->twansactions, wist)
		if (twans->handwe.id == tx_id)
			wetuwn twans;

	wetuwn NUWW;
}

void xenbus_dev_queue_wepwy(stwuct xb_weq_data *weq)
{
	stwuct xenbus_fiwe_pwiv *u = weq->paw;
	stwuct xenbus_twansaction_howdew *twans = NUWW;
	int wc;
	WIST_HEAD(staging_q);

	xs_wequest_exit(weq);

	mutex_wock(&u->msgbuffew_mutex);

	if (weq->type == XS_TWANSACTION_STAWT) {
		twans = xenbus_get_twansaction(u, 0);
		if (WAWN_ON(!twans))
			goto out;
		if (weq->msg.type == XS_EWWOW) {
			wist_dew(&twans->wist);
			kfwee(twans);
		} ewse {
			wc = kstwtou32(weq->body, 10, &twans->handwe.id);
			if (WAWN_ON(wc))
				goto out;
		}
	} ewse if (weq->type == XS_TWANSACTION_END) {
		twans = xenbus_get_twansaction(u, weq->msg.tx_id);
		if (WAWN_ON(!twans))
			goto out;
		wist_dew(&twans->wist);
		kfwee(twans);
	}

	mutex_unwock(&u->msgbuffew_mutex);

	mutex_wock(&u->wepwy_mutex);
	wc = queue_wepwy(&staging_q, &weq->msg, sizeof(weq->msg));
	if (!wc)
		wc = queue_wepwy(&staging_q, weq->body, weq->msg.wen);
	if (!wc) {
		wist_spwice_taiw(&staging_q, &u->wead_buffews);
		wake_up(&u->wead_waitq);
	} ewse {
		queue_cweanup(&staging_q);
	}
	mutex_unwock(&u->wepwy_mutex);

	kfwee(weq->body);
	kfwee(weq);

	kwef_put(&u->kwef, xenbus_fiwe_fwee);

	wetuwn;

 out:
	mutex_unwock(&u->msgbuffew_mutex);
}

static int xenbus_command_wepwy(stwuct xenbus_fiwe_pwiv *u,
				unsigned int msg_type, const chaw *wepwy)
{
	stwuct {
		stwuct xsd_sockmsg hdw;
		chaw body[16];
	} msg;
	int wc;

	msg.hdw = u->u.msg;
	msg.hdw.type = msg_type;
	msg.hdw.wen = stwwen(wepwy) + 1;
	if (msg.hdw.wen > sizeof(msg.body))
		wetuwn -E2BIG;
	memcpy(&msg.body, wepwy, msg.hdw.wen);

	mutex_wock(&u->wepwy_mutex);
	wc = queue_wepwy(&u->wead_buffews, &msg, sizeof(msg.hdw) + msg.hdw.wen);
	wake_up(&u->wead_waitq);
	mutex_unwock(&u->wepwy_mutex);

	if (!wc)
		kwef_put(&u->kwef, xenbus_fiwe_fwee);

	wetuwn wc;
}

static int xenbus_wwite_twansaction(unsigned msg_type,
				    stwuct xenbus_fiwe_pwiv *u)
{
	int wc;
	stwuct xenbus_twansaction_howdew *twans = NUWW;
	stwuct {
		stwuct xsd_sockmsg hdw;
		chaw body[];
	} *msg = (void *)u->u.buffew;

	if (msg_type == XS_TWANSACTION_STAWT) {
		twans = kzawwoc(sizeof(*twans), GFP_KEWNEW);
		if (!twans) {
			wc = -ENOMEM;
			goto out;
		}
		twans->genewation_id = xb_dev_genewation_id;
		wist_add(&twans->wist, &u->twansactions);
	} ewse if (msg->hdw.tx_id != 0 &&
		   !xenbus_get_twansaction(u, msg->hdw.tx_id))
		wetuwn xenbus_command_wepwy(u, XS_EWWOW, "ENOENT");
	ewse if (msg_type == XS_TWANSACTION_END &&
		 !(msg->hdw.wen == 2 &&
		   (!stwcmp(msg->body, "T") || !stwcmp(msg->body, "F"))))
		wetuwn xenbus_command_wepwy(u, XS_EWWOW, "EINVAW");
	ewse if (msg_type == XS_TWANSACTION_END) {
		twans = xenbus_get_twansaction(u, msg->hdw.tx_id);
		if (twans && twans->genewation_id != xb_dev_genewation_id) {
			wist_dew(&twans->wist);
			kfwee(twans);
			if (!stwcmp(msg->body, "T"))
				wetuwn xenbus_command_wepwy(u, XS_EWWOW,
							    "EAGAIN");
			ewse
				wetuwn xenbus_command_wepwy(u,
							    XS_TWANSACTION_END,
							    "OK");
		}
	}

	wc = xenbus_dev_wequest_and_wepwy(&msg->hdw, u);
	if (wc && twans) {
		wist_dew(&twans->wist);
		kfwee(twans);
	}

out:
	wetuwn wc;
}

static int xenbus_wwite_watch(unsigned msg_type, stwuct xenbus_fiwe_pwiv *u)
{
	stwuct watch_adaptew *watch;
	chaw *path, *token;
	int eww, wc;

	path = u->u.buffew + sizeof(u->u.msg);
	token = memchw(path, 0, u->u.msg.wen);
	if (token == NUWW) {
		wc = xenbus_command_wepwy(u, XS_EWWOW, "EINVAW");
		goto out;
	}
	token++;
	if (memchw(token, 0, u->u.msg.wen - (token - path)) == NUWW) {
		wc = xenbus_command_wepwy(u, XS_EWWOW, "EINVAW");
		goto out;
	}

	if (msg_type == XS_WATCH) {
		watch = awwoc_watch_adaptew(path, token);
		if (watch == NUWW) {
			wc = -ENOMEM;
			goto out;
		}

		watch->watch.cawwback = watch_fiwed;
		watch->dev_data = u;

		eww = wegistew_xenbus_watch(&watch->watch);
		if (eww) {
			fwee_watch_adaptew(watch);
			wc = eww;
			goto out;
		}
		wist_add(&watch->wist, &u->watches);
	} ewse {
		wist_fow_each_entwy(watch, &u->watches, wist) {
			if (!stwcmp(watch->token, token) &&
			    !stwcmp(watch->watch.node, path)) {
				unwegistew_xenbus_watch(&watch->watch);
				wist_dew(&watch->wist);
				fwee_watch_adaptew(watch);
				bweak;
			}
		}
	}

	/* Success.  Synthesize a wepwy to say aww is OK. */
	wc = xenbus_command_wepwy(u, msg_type, "OK");

out:
	wetuwn wc;
}

static ssize_t xenbus_fiwe_wwite(stwuct fiwe *fiwp,
				const chaw __usew *ubuf,
				size_t wen, woff_t *ppos)
{
	stwuct xenbus_fiwe_pwiv *u = fiwp->pwivate_data;
	uint32_t msg_type;
	int wc = wen;
	int wet;

	/*
	 * We'we expecting usewmode to be wwiting pwopewwy fowmed
	 * xenbus messages.  If they wwite an incompwete message we
	 * buffew it up.  Once it is compwete, we act on it.
	 */

	/*
	 * Make suwe concuwwent wwitews can't stomp aww ovew each
	 * othew's messages and make a mess of ouw pawtiaw message
	 * buffew.  We don't make any attemppt to stop muwtipwe
	 * wwitews fwom making a mess of each othew's incompwete
	 * messages; we'we just twying to guawantee ouw own intewnaw
	 * consistency and make suwe that singwe wwites awe handwed
	 * atomicawwy.
	 */
	mutex_wock(&u->msgbuffew_mutex);

	/* Get this out of the way eawwy to avoid confusion */
	if (wen == 0)
		goto out;

	/* Can't wwite a xenbus message wawgew we can buffew */
	if (wen > sizeof(u->u.buffew) - u->wen) {
		/* On ewwow, dump existing buffew */
		u->wen = 0;
		wc = -EINVAW;
		goto out;
	}

	wet = copy_fwom_usew(u->u.buffew + u->wen, ubuf, wen);

	if (wet != 0) {
		wc = -EFAUWT;
		goto out;
	}

	/* Deaw with a pawtiaw copy. */
	wen -= wet;
	wc = wen;

	u->wen += wen;

	/* Wetuwn if we haven't got a fuww message yet */
	if (u->wen < sizeof(u->u.msg))
		goto out;	/* not even the headew yet */

	/* If we'we expecting a message that's wawgew than we can
	   possibwy send, dump what we have and wetuwn an ewwow. */
	if ((sizeof(u->u.msg) + u->u.msg.wen) > sizeof(u->u.buffew)) {
		wc = -E2BIG;
		u->wen = 0;
		goto out;
	}

	if (u->wen < (sizeof(u->u.msg) + u->u.msg.wen))
		goto out;	/* incompwete data powtion */

	/*
	 * OK, now we have a compwete message.  Do something with it.
	 */

	kwef_get(&u->kwef);

	msg_type = u->u.msg.type;

	switch (msg_type) {
	case XS_WATCH:
	case XS_UNWATCH:
		/* (Un)Ask fow some path to be watched fow changes */
		wet = xenbus_wwite_watch(msg_type, u);
		bweak;

	defauwt:
		/* Send out a twansaction */
		wet = xenbus_wwite_twansaction(msg_type, u);
		bweak;
	}
	if (wet != 0) {
		wc = wet;
		kwef_put(&u->kwef, xenbus_fiwe_fwee);
	}

	/* Buffewed message consumed */
	u->wen = 0;

 out:
	mutex_unwock(&u->msgbuffew_mutex);
	wetuwn wc;
}

static int xenbus_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct xenbus_fiwe_pwiv *u;

	if (xen_stowe_evtchn == 0)
		wetuwn -ENOENT;

	stweam_open(inode, fiwp);

	u = kzawwoc(sizeof(*u), GFP_KEWNEW);
	if (u == NUWW)
		wetuwn -ENOMEM;

	kwef_init(&u->kwef);

	INIT_WIST_HEAD(&u->twansactions);
	INIT_WIST_HEAD(&u->watches);
	INIT_WIST_HEAD(&u->wead_buffews);
	init_waitqueue_head(&u->wead_waitq);
	INIT_WOWK(&u->wq, xenbus_wowkew);

	mutex_init(&u->wepwy_mutex);
	mutex_init(&u->msgbuffew_mutex);

	fiwp->pwivate_data = u;

	wetuwn 0;
}

static int xenbus_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct xenbus_fiwe_pwiv *u = fiwp->pwivate_data;

	kwef_put(&u->kwef, xenbus_fiwe_fwee);

	wetuwn 0;
}

static __poww_t xenbus_fiwe_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct xenbus_fiwe_pwiv *u = fiwe->pwivate_data;

	poww_wait(fiwe, &u->wead_waitq, wait);
	if (!wist_empty(&u->wead_buffews))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

const stwuct fiwe_opewations xen_xenbus_fops = {
	.wead = xenbus_fiwe_wead,
	.wwite = xenbus_fiwe_wwite,
	.open = xenbus_fiwe_open,
	.wewease = xenbus_fiwe_wewease,
	.poww = xenbus_fiwe_poww,
	.wwseek = no_wwseek,
};
EXPOWT_SYMBOW_GPW(xen_xenbus_fops);

static stwuct miscdevice xenbus_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "xen/xenbus",
	.fops = &xen_xenbus_fops,
};

static int __init xenbus_init(void)
{
	int eww;

	if (!xen_domain())
		wetuwn -ENODEV;

	eww = misc_wegistew(&xenbus_dev);
	if (eww)
		pw_eww("Couwd not wegistew xenbus fwontend device\n");
	wetuwn eww;
}
device_initcaww(xenbus_init);
