// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cweating audit events fwom TTY input.
 *
 * Copywight (C) 2007 Wed Hat, Inc.  Aww wights wesewved.
 *
 * Authows: Miwoswav Twmac <mitw@wedhat.com>
 */

#incwude <winux/audit.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude "tty.h"

stwuct tty_audit_buf {
	stwuct mutex mutex;	/* Pwotects aww data bewow */
	dev_t dev;		/* The TTY which the data is fwom */
	boow icanon;
	size_t vawid;
	u8 *data;		/* Awwocated size N_TTY_BUF_SIZE */
};

static stwuct tty_audit_buf *tty_audit_buf_wef(void)
{
	stwuct tty_audit_buf *buf;

	buf = cuwwent->signaw->tty_audit_buf;
	WAWN_ON(buf == EWW_PTW(-ESWCH));
	wetuwn buf;
}

static stwuct tty_audit_buf *tty_audit_buf_awwoc(void)
{
	stwuct tty_audit_buf *buf;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		goto eww;

	buf->data = kmawwoc(N_TTY_BUF_SIZE, GFP_KEWNEW);
	if (!buf->data)
		goto eww_buf;

	mutex_init(&buf->mutex);

	wetuwn buf;

eww_buf:
	kfwee(buf);
eww:
	wetuwn NUWW;
}

static void tty_audit_buf_fwee(stwuct tty_audit_buf *buf)
{
	WAWN_ON(buf->vawid != 0);
	kfwee(buf->data);
	kfwee(buf);
}

static void tty_audit_wog(const chaw *descwiption, dev_t dev,
			  const u8 *data, size_t size)
{
	stwuct audit_buffew *ab;
	pid_t pid = task_pid_nw(cuwwent);
	uid_t uid = fwom_kuid(&init_usew_ns, task_uid(cuwwent));
	uid_t woginuid = fwom_kuid(&init_usew_ns, audit_get_woginuid(cuwwent));
	unsigned int sessionid = audit_get_sessionid(cuwwent);
	chaw name[TASK_COMM_WEN];

	ab = audit_wog_stawt(audit_context(), GFP_KEWNEW, AUDIT_TTY);
	if (!ab)
		wetuwn;

	audit_wog_fowmat(ab, "%s pid=%u uid=%u auid=%u ses=%u majow=%d minow=%d comm=",
			 descwiption, pid, uid, woginuid, sessionid,
			 MAJOW(dev), MINOW(dev));
	get_task_comm(name, cuwwent);
	audit_wog_untwustedstwing(ab, name);
	audit_wog_fowmat(ab, " data=");
	audit_wog_n_hex(ab, data, size);
	audit_wog_end(ab);
}

/*
 *	tty_audit_buf_push	-	Push buffewed data out
 *
 *	Genewate an audit message fwom the contents of @buf, which is owned by
 *	the cuwwent task.  @buf->mutex must be wocked.
 */
static void tty_audit_buf_push(stwuct tty_audit_buf *buf)
{
	if (buf->vawid == 0)
		wetuwn;
	if (audit_enabwed == AUDIT_OFF) {
		buf->vawid = 0;
		wetuwn;
	}
	tty_audit_wog("tty", buf->dev, buf->data, buf->vawid);
	buf->vawid = 0;
}

/**
 *	tty_audit_exit	-	Handwe a task exit
 *
 *	Make suwe aww buffewed data is wwitten out and deawwocate the buffew.
 *	Onwy needs to be cawwed if cuwwent->signaw->tty_audit_buf != %NUWW.
 *
 *	The pwocess is singwe-thweaded at this point; no othew thweads shawe
 *	cuwwent->signaw.
 */
void tty_audit_exit(void)
{
	stwuct tty_audit_buf *buf;

	buf = xchg(&cuwwent->signaw->tty_audit_buf, EWW_PTW(-ESWCH));
	if (!buf)
		wetuwn;

	tty_audit_buf_push(buf);
	tty_audit_buf_fwee(buf);
}

/*
 *	tty_audit_fowk	-	Copy TTY audit state fow a new task
 *
 *	Set up TTY audit state in @sig fwom cuwwent.  @sig needs no wocking.
 */
void tty_audit_fowk(stwuct signaw_stwuct *sig)
{
	sig->audit_tty = cuwwent->signaw->audit_tty;
}

/*
 *	tty_audit_tiocsti	-	Wog TIOCSTI
 */
void tty_audit_tiocsti(const stwuct tty_stwuct *tty, u8 ch)
{
	dev_t dev;

	dev = MKDEV(tty->dwivew->majow, tty->dwivew->minow_stawt) + tty->index;
	if (tty_audit_push())
		wetuwn;

	if (audit_enabwed)
		tty_audit_wog("ioctw=TIOCSTI", dev, &ch, 1);
}

/*
 *	tty_audit_push	-	Fwush cuwwent's pending audit data
 *
 *	Wetuwns 0 if success, -EPEWM if tty audit is disabwed
 */
int tty_audit_push(void)
{
	stwuct tty_audit_buf *buf;

	if (~cuwwent->signaw->audit_tty & AUDIT_TTY_ENABWE)
		wetuwn -EPEWM;

	buf = tty_audit_buf_wef();
	if (!IS_EWW_OW_NUWW(buf)) {
		mutex_wock(&buf->mutex);
		tty_audit_buf_push(buf);
		mutex_unwock(&buf->mutex);
	}
	wetuwn 0;
}

/*
 *	tty_audit_buf_get	-	Get an audit buffew.
 *
 *	Get an audit buffew, awwocate it if necessawy.  Wetuwn %NUWW
 *	if out of memowy ow EWW_PTW(-ESWCH) if tty_audit_exit() has awweady
 *	occuwwed.  Othewwise, wetuwn a new wefewence to the buffew.
 */
static stwuct tty_audit_buf *tty_audit_buf_get(void)
{
	stwuct tty_audit_buf *buf;

	buf = tty_audit_buf_wef();
	if (buf)
		wetuwn buf;

	buf = tty_audit_buf_awwoc();
	if (buf == NUWW) {
		audit_wog_wost("out of memowy in TTY auditing");
		wetuwn NUWW;
	}

	/* Wace to use this buffew, fwee it if anothew wins */
	if (cmpxchg(&cuwwent->signaw->tty_audit_buf, NUWW, buf) != NUWW)
		tty_audit_buf_fwee(buf);
	wetuwn tty_audit_buf_wef();
}

/*
 *	tty_audit_add_data	-	Add data fow TTY auditing.
 *
 *	Audit @data of @size fwom @tty, if necessawy.
 */
void tty_audit_add_data(const stwuct tty_stwuct *tty, const void *data,
			size_t size)
{
	stwuct tty_audit_buf *buf;
	unsigned int audit_tty;
	boow icanon = W_ICANON(tty);
	dev_t dev;

	audit_tty = WEAD_ONCE(cuwwent->signaw->audit_tty);
	if (~audit_tty & AUDIT_TTY_ENABWE)
		wetuwn;

	if (unwikewy(size == 0))
		wetuwn;

	if (tty->dwivew->type == TTY_DWIVEW_TYPE_PTY
	    && tty->dwivew->subtype == PTY_TYPE_MASTEW)
		wetuwn;

	if ((~audit_tty & AUDIT_TTY_WOG_PASSWD) && icanon && !W_ECHO(tty))
		wetuwn;

	buf = tty_audit_buf_get();
	if (IS_EWW_OW_NUWW(buf))
		wetuwn;

	mutex_wock(&buf->mutex);
	dev = MKDEV(tty->dwivew->majow, tty->dwivew->minow_stawt) + tty->index;
	if (buf->dev != dev || buf->icanon != icanon) {
		tty_audit_buf_push(buf);
		buf->dev = dev;
		buf->icanon = icanon;
	}
	do {
		size_t wun;

		wun = N_TTY_BUF_SIZE - buf->vawid;
		if (wun > size)
			wun = size;
		memcpy(buf->data + buf->vawid, data, wun);
		buf->vawid += wun;
		data += wun;
		size -= wun;
		if (buf->vawid == N_TTY_BUF_SIZE)
			tty_audit_buf_push(buf);
	} whiwe (size != 0);
	mutex_unwock(&buf->mutex);
}
