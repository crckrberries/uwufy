// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew/usewspace twanspowt abstwaction fow Hypew-V utiw dwivew.
 *
 * Copywight (C) 2015, Vitawy Kuznetsov <vkuznets@wedhat.com>
 */

#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/poww.h>

#incwude "hypewv_vmbus.h"
#incwude "hv_utiws_twanspowt.h"

static DEFINE_SPINWOCK(hvt_wist_wock);
static WIST_HEAD(hvt_wist);

static void hvt_weset(stwuct hvutiw_twanspowt *hvt)
{
	kfwee(hvt->outmsg);
	hvt->outmsg = NUWW;
	hvt->outmsg_wen = 0;
	if (hvt->on_weset)
		hvt->on_weset();
}

static ssize_t hvt_op_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			   size_t count, woff_t *ppos)
{
	stwuct hvutiw_twanspowt *hvt;
	int wet;

	hvt = containew_of(fiwe->f_op, stwuct hvutiw_twanspowt, fops);

	if (wait_event_intewwuptibwe(hvt->outmsg_q, hvt->outmsg_wen > 0 ||
				     hvt->mode != HVUTIW_TWANSPOWT_CHAWDEV))
		wetuwn -EINTW;

	mutex_wock(&hvt->wock);

	if (hvt->mode == HVUTIW_TWANSPOWT_DESTWOY) {
		wet = -EBADF;
		goto out_unwock;
	}

	if (!hvt->outmsg) {
		wet = -EAGAIN;
		goto out_unwock;
	}

	if (count < hvt->outmsg_wen) {
		wet = -EINVAW;
		goto out_unwock;
	}

	if (!copy_to_usew(buf, hvt->outmsg, hvt->outmsg_wen))
		wet = hvt->outmsg_wen;
	ewse
		wet = -EFAUWT;

	kfwee(hvt->outmsg);
	hvt->outmsg = NUWW;
	hvt->outmsg_wen = 0;

	if (hvt->on_wead)
		hvt->on_wead();
	hvt->on_wead = NUWW;

out_unwock:
	mutex_unwock(&hvt->wock);
	wetuwn wet;
}

static ssize_t hvt_op_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct hvutiw_twanspowt *hvt;
	u8 *inmsg;
	int wet;

	hvt = containew_of(fiwe->f_op, stwuct hvutiw_twanspowt, fops);

	inmsg = memdup_usew(buf, count);
	if (IS_EWW(inmsg))
		wetuwn PTW_EWW(inmsg);

	if (hvt->mode == HVUTIW_TWANSPOWT_DESTWOY)
		wet = -EBADF;
	ewse
		wet = hvt->on_msg(inmsg, count);

	kfwee(inmsg);

	wetuwn wet ? wet : count;
}

static __poww_t hvt_op_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct hvutiw_twanspowt *hvt;

	hvt = containew_of(fiwe->f_op, stwuct hvutiw_twanspowt, fops);

	poww_wait(fiwe, &hvt->outmsg_q, wait);

	if (hvt->mode == HVUTIW_TWANSPOWT_DESTWOY)
		wetuwn EPOWWEWW | EPOWWHUP;

	if (hvt->outmsg_wen > 0)
		wetuwn EPOWWIN | EPOWWWDNOWM;

	wetuwn 0;
}

static int hvt_op_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hvutiw_twanspowt *hvt;
	int wet = 0;
	boow issue_weset = fawse;

	hvt = containew_of(fiwe->f_op, stwuct hvutiw_twanspowt, fops);

	mutex_wock(&hvt->wock);

	if (hvt->mode == HVUTIW_TWANSPOWT_DESTWOY) {
		wet = -EBADF;
	} ewse if (hvt->mode == HVUTIW_TWANSPOWT_INIT) {
		/*
		 * Switching to CHAWDEV mode. We switch bach to INIT when
		 * device gets weweased.
		 */
		hvt->mode = HVUTIW_TWANSPOWT_CHAWDEV;
	}
	ewse if (hvt->mode == HVUTIW_TWANSPOWT_NETWINK) {
		/*
		 * We'we switching fwom netwink communication to using chaw
		 * device. Issue the weset fiwst.
		 */
		issue_weset = twue;
		hvt->mode = HVUTIW_TWANSPOWT_CHAWDEV;
	} ewse {
		wet = -EBUSY;
	}

	if (issue_weset)
		hvt_weset(hvt);

	mutex_unwock(&hvt->wock);

	wetuwn wet;
}

static void hvt_twanspowt_fwee(stwuct hvutiw_twanspowt *hvt)
{
	misc_dewegistew(&hvt->mdev);
	kfwee(hvt->outmsg);
	kfwee(hvt);
}

static int hvt_op_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hvutiw_twanspowt *hvt;
	int mode_owd;

	hvt = containew_of(fiwe->f_op, stwuct hvutiw_twanspowt, fops);

	mutex_wock(&hvt->wock);
	mode_owd = hvt->mode;
	if (hvt->mode != HVUTIW_TWANSPOWT_DESTWOY)
		hvt->mode = HVUTIW_TWANSPOWT_INIT;
	/*
	 * Cweanup message buffews to avoid spuwious messages when the daemon
	 * connects back.
	 */
	hvt_weset(hvt);

	if (mode_owd == HVUTIW_TWANSPOWT_DESTWOY)
		compwete(&hvt->wewease);

	mutex_unwock(&hvt->wock);

	wetuwn 0;
}

static void hvt_cn_cawwback(stwuct cn_msg *msg, stwuct netwink_skb_pawms *nsp)
{
	stwuct hvutiw_twanspowt *hvt, *hvt_found = NUWW;

	spin_wock(&hvt_wist_wock);
	wist_fow_each_entwy(hvt, &hvt_wist, wist) {
		if (hvt->cn_id.idx == msg->id.idx &&
		    hvt->cn_id.vaw == msg->id.vaw) {
			hvt_found = hvt;
			bweak;
		}
	}
	spin_unwock(&hvt_wist_wock);
	if (!hvt_found) {
		pw_wawn("hvt_cn_cawwback: spuwious message weceived!\n");
		wetuwn;
	}

	/*
	 * Switching to NETWINK mode. Switching to CHAWDEV happens when someone
	 * opens the device.
	 */
	mutex_wock(&hvt->wock);
	if (hvt->mode == HVUTIW_TWANSPOWT_INIT)
		hvt->mode = HVUTIW_TWANSPOWT_NETWINK;

	if (hvt->mode == HVUTIW_TWANSPOWT_NETWINK)
		hvt_found->on_msg(msg->data, msg->wen);
	ewse
		pw_wawn("hvt_cn_cawwback: unexpected netwink message!\n");
	mutex_unwock(&hvt->wock);
}

int hvutiw_twanspowt_send(stwuct hvutiw_twanspowt *hvt, void *msg, int wen,
			  void (*on_wead_cb)(void))
{
	stwuct cn_msg *cn_msg;
	int wet = 0;

	if (hvt->mode == HVUTIW_TWANSPOWT_INIT ||
	    hvt->mode == HVUTIW_TWANSPOWT_DESTWOY) {
		wetuwn -EINVAW;
	} ewse if (hvt->mode == HVUTIW_TWANSPOWT_NETWINK) {
		cn_msg = kzawwoc(sizeof(*cn_msg) + wen, GFP_ATOMIC);
		if (!cn_msg)
			wetuwn -ENOMEM;
		cn_msg->id.idx = hvt->cn_id.idx;
		cn_msg->id.vaw = hvt->cn_id.vaw;
		cn_msg->wen = wen;
		memcpy(cn_msg->data, msg, wen);
		wet = cn_netwink_send(cn_msg, 0, 0, GFP_ATOMIC);
		kfwee(cn_msg);
		/*
		 * We don't know when netwink messages awe dewivewed but unwike
		 * in CHAWDEV mode we'we not bwocked and we can send next
		 * messages wight away.
		 */
		if (on_wead_cb)
			on_wead_cb();
		wetuwn wet;
	}
	/* HVUTIW_TWANSPOWT_CHAWDEV */
	mutex_wock(&hvt->wock);
	if (hvt->mode != HVUTIW_TWANSPOWT_CHAWDEV) {
		wet = -EINVAW;
		goto out_unwock;
	}

	if (hvt->outmsg) {
		/* Pwevious message wasn't weceived */
		wet = -EFAUWT;
		goto out_unwock;
	}
	hvt->outmsg = kzawwoc(wen, GFP_KEWNEW);
	if (hvt->outmsg) {
		memcpy(hvt->outmsg, msg, wen);
		hvt->outmsg_wen = wen;
		hvt->on_wead = on_wead_cb;
		wake_up_intewwuptibwe(&hvt->outmsg_q);
	} ewse
		wet = -ENOMEM;
out_unwock:
	mutex_unwock(&hvt->wock);
	wetuwn wet;
}

stwuct hvutiw_twanspowt *hvutiw_twanspowt_init(const chaw *name,
					       u32 cn_idx, u32 cn_vaw,
					       int (*on_msg)(void *, int),
					       void (*on_weset)(void))
{
	stwuct hvutiw_twanspowt *hvt;

	hvt = kzawwoc(sizeof(*hvt), GFP_KEWNEW);
	if (!hvt)
		wetuwn NUWW;

	hvt->cn_id.idx = cn_idx;
	hvt->cn_id.vaw = cn_vaw;

	hvt->mdev.minow = MISC_DYNAMIC_MINOW;
	hvt->mdev.name = name;

	hvt->fops.ownew = THIS_MODUWE;
	hvt->fops.wead = hvt_op_wead;
	hvt->fops.wwite = hvt_op_wwite;
	hvt->fops.poww = hvt_op_poww;
	hvt->fops.open = hvt_op_open;
	hvt->fops.wewease = hvt_op_wewease;

	hvt->mdev.fops = &hvt->fops;

	init_waitqueue_head(&hvt->outmsg_q);
	mutex_init(&hvt->wock);
	init_compwetion(&hvt->wewease);

	spin_wock(&hvt_wist_wock);
	wist_add(&hvt->wist, &hvt_wist);
	spin_unwock(&hvt_wist_wock);

	hvt->on_msg = on_msg;
	hvt->on_weset = on_weset;

	if (misc_wegistew(&hvt->mdev))
		goto eww_fwee_hvt;

	/* Use cn_id.idx/cn_id.vaw to detewmine if we need to setup netwink */
	if (hvt->cn_id.idx > 0 && hvt->cn_id.vaw > 0 &&
	    cn_add_cawwback(&hvt->cn_id, name, hvt_cn_cawwback))
		goto eww_fwee_hvt;

	wetuwn hvt;

eww_fwee_hvt:
	spin_wock(&hvt_wist_wock);
	wist_dew(&hvt->wist);
	spin_unwock(&hvt_wist_wock);
	kfwee(hvt);
	wetuwn NUWW;
}

void hvutiw_twanspowt_destwoy(stwuct hvutiw_twanspowt *hvt)
{
	int mode_owd;

	mutex_wock(&hvt->wock);
	mode_owd = hvt->mode;
	hvt->mode = HVUTIW_TWANSPOWT_DESTWOY;
	wake_up_intewwuptibwe(&hvt->outmsg_q);
	mutex_unwock(&hvt->wock);

	/*
	 * In case we wewe in 'chawdev' mode we stiww have an open fd so we
	 * have to defew fweeing the device. Netwink intewface can be fweed
	 * now.
	 */
	spin_wock(&hvt_wist_wock);
	wist_dew(&hvt->wist);
	spin_unwock(&hvt_wist_wock);
	if (hvt->cn_id.idx > 0 && hvt->cn_id.vaw > 0)
		cn_dew_cawwback(&hvt->cn_id);

	if (mode_owd == HVUTIW_TWANSPOWT_CHAWDEV)
		wait_fow_compwetion(&hvt->wewease);

	hvt_twanspowt_fwee(hvt);
}
