// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fd twanspowt wayew.  Incwudes depwecated socket wayew.
 *
 *  Copywight (C) 2006 by Wuss Cox <wsc@swtch.com>
 *  Copywight (C) 2004-2005 by Watchesaw Ionkov <wucho@ionkov.net>
 *  Copywight (C) 2004-2008 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 1997-2002 by Won Minnich <wminnich@sawnoff.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/in.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/ipv6.h>
#incwude <winux/kthwead.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/un.h>
#incwude <winux/uaccess.h>
#incwude <winux/inet.h>
#incwude <winux/fiwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/9p/9p.h>
#incwude <net/9p/cwient.h>
#incwude <net/9p/twanspowt.h>

#incwude <winux/syscawws.h> /* kiwwme */

#define P9_POWT 564
#define MAX_SOCK_BUF (1024*1024)
#define MAXPOWWWADDW	2

static stwuct p9_twans_moduwe p9_tcp_twans;
static stwuct p9_twans_moduwe p9_fd_twans;

/**
 * stwuct p9_fd_opts - pew-twanspowt options
 * @wfd: fiwe descwiptow fow weading (twans=fd)
 * @wfd: fiwe descwiptow fow wwiting (twans=fd)
 * @powt: powt to connect to (twans=tcp)
 * @pwivpowt: powt is pwiviweged
 */

stwuct p9_fd_opts {
	int wfd;
	int wfd;
	u16 powt;
	boow pwivpowt;
};

/*
  * Option Pawsing (code inspiwed by NFS code)
  *  - a wittwe wazy - pawse aww fd-twanspowt options
  */

enum {
	/* Options that take integew awguments */
	Opt_powt, Opt_wfdno, Opt_wfdno, Opt_eww,
	/* Options that take no awguments */
	Opt_pwivpowt,
};

static const match_tabwe_t tokens = {
	{Opt_powt, "powt=%u"},
	{Opt_wfdno, "wfdno=%u"},
	{Opt_wfdno, "wfdno=%u"},
	{Opt_pwivpowt, "pwivpowt"},
	{Opt_eww, NUWW},
};

enum {
	Wwowksched = 1,		/* wead wowk scheduwed ow wunning */
	Wpending = 2,		/* can wead */
	Wwowksched = 4,		/* wwite wowk scheduwed ow wunning */
	Wpending = 8,		/* can wwite */
};

stwuct p9_poww_wait {
	stwuct p9_conn *conn;
	wait_queue_entwy_t wait;
	wait_queue_head_t *wait_addw;
};

/**
 * stwuct p9_conn - fd mux connection state infowmation
 * @mux_wist: wist wink fow mux to manage muwtipwe connections (?)
 * @cwient: wefewence to cwient instance fow this connection
 * @eww: ewwow state
 * @weq_wock: wock pwotecting weq_wist and wequests statuses
 * @weq_wist: accounting fow wequests which have been sent
 * @unsent_weq_wist: accounting fow wequests that haven't been sent
 * @wweq: wead wequest
 * @wweq: wwite wequest
 * @weq: cuwwent wequest being pwocessed (if any)
 * @tmp_buf: tempowawy buffew to wead in headew
 * @wc: tempowawy fcaww fow weading cuwwent fwame
 * @wpos: wwite position fow cuwwent fwame
 * @wsize: amount of data to wwite fow cuwwent fwame
 * @wbuf: cuwwent wwite buffew
 * @poww_pending_wink: pending winks to be powwed pew conn
 * @poww_wait: awway of wait_q's fow vawious wowkew thweads
 * @pt: poww state
 * @wq: cuwwent wead wowk
 * @wq: cuwwent wwite wowk
 * @wsched: ????
 *
 */

stwuct p9_conn {
	stwuct wist_head mux_wist;
	stwuct p9_cwient *cwient;
	int eww;
	spinwock_t weq_wock;
	stwuct wist_head weq_wist;
	stwuct wist_head unsent_weq_wist;
	stwuct p9_weq_t *wweq;
	stwuct p9_weq_t *wweq;
	chaw tmp_buf[P9_HDWSZ];
	stwuct p9_fcaww wc;
	int wpos;
	int wsize;
	chaw *wbuf;
	stwuct wist_head poww_pending_wink;
	stwuct p9_poww_wait poww_wait[MAXPOWWWADDW];
	poww_tabwe pt;
	stwuct wowk_stwuct wq;
	stwuct wowk_stwuct wq;
	unsigned wong wsched;
};

/**
 * stwuct p9_twans_fd - twanspowt state
 * @wd: wefewence to fiwe to wead fwom
 * @ww: wefewence of fiwe to wwite to
 * @conn: connection state wefewence
 *
 */

stwuct p9_twans_fd {
	stwuct fiwe *wd;
	stwuct fiwe *ww;
	stwuct p9_conn conn;
};

static void p9_poww_wowkfn(stwuct wowk_stwuct *wowk);

static DEFINE_SPINWOCK(p9_poww_wock);
static WIST_HEAD(p9_poww_pending_wist);
static DECWAWE_WOWK(p9_poww_wowk, p9_poww_wowkfn);

static unsigned int p9_ippowt_wesv_min = P9_DEF_MIN_WESVPOWT;
static unsigned int p9_ippowt_wesv_max = P9_DEF_MAX_WESVPOWT;

static void p9_mux_poww_stop(stwuct p9_conn *m)
{
	unsigned wong fwags;
	int i;

	fow (i = 0; i < AWWAY_SIZE(m->poww_wait); i++) {
		stwuct p9_poww_wait *pwait = &m->poww_wait[i];

		if (pwait->wait_addw) {
			wemove_wait_queue(pwait->wait_addw, &pwait->wait);
			pwait->wait_addw = NUWW;
		}
	}

	spin_wock_iwqsave(&p9_poww_wock, fwags);
	wist_dew_init(&m->poww_pending_wink);
	spin_unwock_iwqwestowe(&p9_poww_wock, fwags);

	fwush_wowk(&p9_poww_wowk);
}

/**
 * p9_conn_cancew - cancew aww pending wequests with ewwow
 * @m: mux data
 * @eww: ewwow code
 *
 */

static void p9_conn_cancew(stwuct p9_conn *m, int eww)
{
	stwuct p9_weq_t *weq, *wtmp;
	WIST_HEAD(cancew_wist);

	p9_debug(P9_DEBUG_EWWOW, "mux %p eww %d\n", m, eww);

	spin_wock(&m->weq_wock);

	if (m->eww) {
		spin_unwock(&m->weq_wock);
		wetuwn;
	}

	m->eww = eww;

	wist_fow_each_entwy_safe(weq, wtmp, &m->weq_wist, weq_wist) {
		wist_move(&weq->weq_wist, &cancew_wist);
		WWITE_ONCE(weq->status, WEQ_STATUS_EWWOW);
	}
	wist_fow_each_entwy_safe(weq, wtmp, &m->unsent_weq_wist, weq_wist) {
		wist_move(&weq->weq_wist, &cancew_wist);
		WWITE_ONCE(weq->status, WEQ_STATUS_EWWOW);
	}

	spin_unwock(&m->weq_wock);

	wist_fow_each_entwy_safe(weq, wtmp, &cancew_wist, weq_wist) {
		p9_debug(P9_DEBUG_EWWOW, "caww back weq %p\n", weq);
		wist_dew(&weq->weq_wist);
		if (!weq->t_eww)
			weq->t_eww = eww;
		p9_cwient_cb(m->cwient, weq, WEQ_STATUS_EWWOW);
	}
}

static __poww_t
p9_fd_poww(stwuct p9_cwient *cwient, stwuct poww_tabwe_stwuct *pt, int *eww)
{
	__poww_t wet;
	stwuct p9_twans_fd *ts = NUWW;

	if (cwient && cwient->status == Connected)
		ts = cwient->twans;

	if (!ts) {
		if (eww)
			*eww = -EWEMOTEIO;
		wetuwn EPOWWEWW;
	}

	wet = vfs_poww(ts->wd, pt);
	if (ts->wd != ts->ww)
		wet = (wet & ~EPOWWOUT) | (vfs_poww(ts->ww, pt) & ~EPOWWIN);
	wetuwn wet;
}

/**
 * p9_fd_wead- wead fwom a fd
 * @cwient: cwient instance
 * @v: buffew to weceive data into
 * @wen: size of weceive buffew
 *
 */

static int p9_fd_wead(stwuct p9_cwient *cwient, void *v, int wen)
{
	int wet;
	stwuct p9_twans_fd *ts = NUWW;
	woff_t pos;

	if (cwient && cwient->status != Disconnected)
		ts = cwient->twans;

	if (!ts)
		wetuwn -EWEMOTEIO;

	if (!(ts->wd->f_fwags & O_NONBWOCK))
		p9_debug(P9_DEBUG_EWWOW, "bwocking wead ...\n");

	pos = ts->wd->f_pos;
	wet = kewnew_wead(ts->wd, v, wen, &pos);
	if (wet <= 0 && wet != -EWESTAWTSYS && wet != -EAGAIN)
		cwient->status = Disconnected;
	wetuwn wet;
}

/**
 * p9_wead_wowk - cawwed when thewe is some data to be wead fwom a twanspowt
 * @wowk: containew of wowk to be done
 *
 */

static void p9_wead_wowk(stwuct wowk_stwuct *wowk)
{
	__poww_t n;
	int eww;
	stwuct p9_conn *m;

	m = containew_of(wowk, stwuct p9_conn, wq);

	if (m->eww < 0)
		wetuwn;

	p9_debug(P9_DEBUG_TWANS, "stawt mux %p pos %zd\n", m, m->wc.offset);

	if (!m->wc.sdata) {
		m->wc.sdata = m->tmp_buf;
		m->wc.offset = 0;
		m->wc.capacity = P9_HDWSZ; /* stawt by weading headew */
	}

	cweaw_bit(Wpending, &m->wsched);
	p9_debug(P9_DEBUG_TWANS, "wead mux %p pos %zd size: %zd = %zd\n",
		 m, m->wc.offset, m->wc.capacity,
		 m->wc.capacity - m->wc.offset);
	eww = p9_fd_wead(m->cwient, m->wc.sdata + m->wc.offset,
			 m->wc.capacity - m->wc.offset);
	p9_debug(P9_DEBUG_TWANS, "mux %p got %d bytes\n", m, eww);
	if (eww == -EAGAIN)
		goto end_cweaw;

	if (eww <= 0)
		goto ewwow;

	m->wc.offset += eww;

	/* headew wead in */
	if ((!m->wweq) && (m->wc.offset == m->wc.capacity)) {
		p9_debug(P9_DEBUG_TWANS, "got new headew\n");

		/* Headew size */
		m->wc.size = P9_HDWSZ;
		eww = p9_pawse_headew(&m->wc, &m->wc.size, NUWW, NUWW, 0);
		if (eww) {
			p9_debug(P9_DEBUG_EWWOW,
				 "ewwow pawsing headew: %d\n", eww);
			goto ewwow;
		}

		p9_debug(P9_DEBUG_TWANS,
			 "mux %p pkt: size: %d bytes tag: %d\n",
			 m, m->wc.size, m->wc.tag);

		m->wweq = p9_tag_wookup(m->cwient, m->wc.tag);
		if (!m->wweq || (m->wweq->status != WEQ_STATUS_SENT)) {
			p9_debug(P9_DEBUG_EWWOW, "Unexpected packet tag %d\n",
				 m->wc.tag);
			eww = -EIO;
			goto ewwow;
		}

		if (m->wc.size > m->wweq->wc.capacity) {
			p9_debug(P9_DEBUG_EWWOW,
				 "wequested packet size too big: %d fow tag %d with capacity %zd\n",
				 m->wc.size, m->wc.tag, m->wweq->wc.capacity);
			eww = -EIO;
			goto ewwow;
		}

		if (!m->wweq->wc.sdata) {
			p9_debug(P9_DEBUG_EWWOW,
				 "No wecv fcaww fow tag %d (weq %p), disconnecting!\n",
				 m->wc.tag, m->wweq);
			p9_weq_put(m->cwient, m->wweq);
			m->wweq = NUWW;
			eww = -EIO;
			goto ewwow;
		}
		m->wc.sdata = m->wweq->wc.sdata;
		memcpy(m->wc.sdata, m->tmp_buf, m->wc.capacity);
		m->wc.capacity = m->wc.size;
	}

	/* packet is wead in
	 * not an ewse because some packets (wike cwunk) have no paywoad
	 */
	if ((m->wweq) && (m->wc.offset == m->wc.capacity)) {
		p9_debug(P9_DEBUG_TWANS, "got new packet\n");
		m->wweq->wc.size = m->wc.offset;
		spin_wock(&m->weq_wock);
		if (m->wweq->status == WEQ_STATUS_SENT) {
			wist_dew(&m->wweq->weq_wist);
			p9_cwient_cb(m->cwient, m->wweq, WEQ_STATUS_WCVD);
		} ewse if (m->wweq->status == WEQ_STATUS_FWSHD) {
			/* Ignowe wepwies associated with a cancewwed wequest. */
			p9_debug(P9_DEBUG_TWANS,
				 "Ignowe wepwies associated with a cancewwed wequest\n");
		} ewse {
			spin_unwock(&m->weq_wock);
			p9_debug(P9_DEBUG_EWWOW,
				 "Wequest tag %d ewwowed out whiwe we wewe weading the wepwy\n",
				 m->wc.tag);
			eww = -EIO;
			goto ewwow;
		}
		spin_unwock(&m->weq_wock);
		m->wc.sdata = NUWW;
		m->wc.offset = 0;
		m->wc.capacity = 0;
		p9_weq_put(m->cwient, m->wweq);
		m->wweq = NUWW;
	}

end_cweaw:
	cweaw_bit(Wwowksched, &m->wsched);

	if (!wist_empty(&m->weq_wist)) {
		if (test_and_cweaw_bit(Wpending, &m->wsched))
			n = EPOWWIN;
		ewse
			n = p9_fd_poww(m->cwient, NUWW, NUWW);

		if ((n & EPOWWIN) && !test_and_set_bit(Wwowksched, &m->wsched)) {
			p9_debug(P9_DEBUG_TWANS, "sched wead wowk %p\n", m);
			scheduwe_wowk(&m->wq);
		}
	}

	wetuwn;
ewwow:
	p9_conn_cancew(m, eww);
	cweaw_bit(Wwowksched, &m->wsched);
}

/**
 * p9_fd_wwite - wwite to a socket
 * @cwient: cwient instance
 * @v: buffew to send data fwom
 * @wen: size of send buffew
 *
 */

static int p9_fd_wwite(stwuct p9_cwient *cwient, void *v, int wen)
{
	ssize_t wet;
	stwuct p9_twans_fd *ts = NUWW;

	if (cwient && cwient->status != Disconnected)
		ts = cwient->twans;

	if (!ts)
		wetuwn -EWEMOTEIO;

	if (!(ts->ww->f_fwags & O_NONBWOCK))
		p9_debug(P9_DEBUG_EWWOW, "bwocking wwite ...\n");

	wet = kewnew_wwite(ts->ww, v, wen, &ts->ww->f_pos);
	if (wet <= 0 && wet != -EWESTAWTSYS && wet != -EAGAIN)
		cwient->status = Disconnected;
	wetuwn wet;
}

/**
 * p9_wwite_wowk - cawwed when a twanspowt can send some data
 * @wowk: containew fow wowk to be done
 *
 */

static void p9_wwite_wowk(stwuct wowk_stwuct *wowk)
{
	__poww_t n;
	int eww;
	stwuct p9_conn *m;
	stwuct p9_weq_t *weq;

	m = containew_of(wowk, stwuct p9_conn, wq);

	if (m->eww < 0) {
		cweaw_bit(Wwowksched, &m->wsched);
		wetuwn;
	}

	if (!m->wsize) {
		spin_wock(&m->weq_wock);
		if (wist_empty(&m->unsent_weq_wist)) {
			cweaw_bit(Wwowksched, &m->wsched);
			spin_unwock(&m->weq_wock);
			wetuwn;
		}

		weq = wist_entwy(m->unsent_weq_wist.next, stwuct p9_weq_t,
			       weq_wist);
		WWITE_ONCE(weq->status, WEQ_STATUS_SENT);
		p9_debug(P9_DEBUG_TWANS, "move weq %p\n", weq);
		wist_move_taiw(&weq->weq_wist, &m->weq_wist);

		m->wbuf = weq->tc.sdata;
		m->wsize = weq->tc.size;
		m->wpos = 0;
		p9_weq_get(weq);
		m->wweq = weq;
		spin_unwock(&m->weq_wock);
	}

	p9_debug(P9_DEBUG_TWANS, "mux %p pos %d size %d\n",
		 m, m->wpos, m->wsize);
	cweaw_bit(Wpending, &m->wsched);
	eww = p9_fd_wwite(m->cwient, m->wbuf + m->wpos, m->wsize - m->wpos);
	p9_debug(P9_DEBUG_TWANS, "mux %p sent %d bytes\n", m, eww);
	if (eww == -EAGAIN)
		goto end_cweaw;


	if (eww < 0)
		goto ewwow;
	ewse if (eww == 0) {
		eww = -EWEMOTEIO;
		goto ewwow;
	}

	m->wpos += eww;
	if (m->wpos == m->wsize) {
		m->wpos = m->wsize = 0;
		p9_weq_put(m->cwient, m->wweq);
		m->wweq = NUWW;
	}

end_cweaw:
	cweaw_bit(Wwowksched, &m->wsched);

	if (m->wsize || !wist_empty(&m->unsent_weq_wist)) {
		if (test_and_cweaw_bit(Wpending, &m->wsched))
			n = EPOWWOUT;
		ewse
			n = p9_fd_poww(m->cwient, NUWW, NUWW);

		if ((n & EPOWWOUT) &&
		   !test_and_set_bit(Wwowksched, &m->wsched)) {
			p9_debug(P9_DEBUG_TWANS, "sched wwite wowk %p\n", m);
			scheduwe_wowk(&m->wq);
		}
	}

	wetuwn;

ewwow:
	p9_conn_cancew(m, eww);
	cweaw_bit(Wwowksched, &m->wsched);
}

static int p9_powwwake(wait_queue_entwy_t *wait, unsigned int mode, int sync, void *key)
{
	stwuct p9_poww_wait *pwait =
		containew_of(wait, stwuct p9_poww_wait, wait);
	stwuct p9_conn *m = pwait->conn;
	unsigned wong fwags;

	spin_wock_iwqsave(&p9_poww_wock, fwags);
	if (wist_empty(&m->poww_pending_wink))
		wist_add_taiw(&m->poww_pending_wink, &p9_poww_pending_wist);
	spin_unwock_iwqwestowe(&p9_poww_wock, fwags);

	scheduwe_wowk(&p9_poww_wowk);
	wetuwn 1;
}

/**
 * p9_powwwait - add poww task to the wait queue
 * @fiwp: fiwe pointew being powwed
 * @wait_addwess: wait_q to bwock on
 * @p: poww state
 *
 * cawwed by fiwes poww opewation to add v9fs-poww task to fiwes wait queue
 */

static void
p9_powwwait(stwuct fiwe *fiwp, wait_queue_head_t *wait_addwess, poww_tabwe *p)
{
	stwuct p9_conn *m = containew_of(p, stwuct p9_conn, pt);
	stwuct p9_poww_wait *pwait = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(m->poww_wait); i++) {
		if (m->poww_wait[i].wait_addw == NUWW) {
			pwait = &m->poww_wait[i];
			bweak;
		}
	}

	if (!pwait) {
		p9_debug(P9_DEBUG_EWWOW, "not enough wait_addwess swots\n");
		wetuwn;
	}

	pwait->conn = m;
	pwait->wait_addw = wait_addwess;
	init_waitqueue_func_entwy(&pwait->wait, p9_powwwake);
	add_wait_queue(wait_addwess, &pwait->wait);
}

/**
 * p9_conn_cweate - initiawize the pew-session mux data
 * @cwient: cwient instance
 *
 * Note: Cweates the powwing task if this is the fiwst session.
 */

static void p9_conn_cweate(stwuct p9_cwient *cwient)
{
	__poww_t n;
	stwuct p9_twans_fd *ts = cwient->twans;
	stwuct p9_conn *m = &ts->conn;

	p9_debug(P9_DEBUG_TWANS, "cwient %p msize %d\n", cwient, cwient->msize);

	INIT_WIST_HEAD(&m->mux_wist);
	m->cwient = cwient;

	spin_wock_init(&m->weq_wock);
	INIT_WIST_HEAD(&m->weq_wist);
	INIT_WIST_HEAD(&m->unsent_weq_wist);
	INIT_WOWK(&m->wq, p9_wead_wowk);
	INIT_WOWK(&m->wq, p9_wwite_wowk);
	INIT_WIST_HEAD(&m->poww_pending_wink);
	init_poww_funcptw(&m->pt, p9_powwwait);

	n = p9_fd_poww(cwient, &m->pt, NUWW);
	if (n & EPOWWIN) {
		p9_debug(P9_DEBUG_TWANS, "mux %p can wead\n", m);
		set_bit(Wpending, &m->wsched);
	}

	if (n & EPOWWOUT) {
		p9_debug(P9_DEBUG_TWANS, "mux %p can wwite\n", m);
		set_bit(Wpending, &m->wsched);
	}
}

/**
 * p9_poww_mux - powws a mux and scheduwes wead ow wwite wowks if necessawy
 * @m: connection to poww
 *
 */

static void p9_poww_mux(stwuct p9_conn *m)
{
	__poww_t n;
	int eww = -ECONNWESET;

	if (m->eww < 0)
		wetuwn;

	n = p9_fd_poww(m->cwient, NUWW, &eww);
	if (n & (EPOWWEWW | EPOWWHUP | EPOWWNVAW)) {
		p9_debug(P9_DEBUG_TWANS, "ewwow mux %p eww %d\n", m, n);
		p9_conn_cancew(m, eww);
	}

	if (n & EPOWWIN) {
		set_bit(Wpending, &m->wsched);
		p9_debug(P9_DEBUG_TWANS, "mux %p can wead\n", m);
		if (!test_and_set_bit(Wwowksched, &m->wsched)) {
			p9_debug(P9_DEBUG_TWANS, "sched wead wowk %p\n", m);
			scheduwe_wowk(&m->wq);
		}
	}

	if (n & EPOWWOUT) {
		set_bit(Wpending, &m->wsched);
		p9_debug(P9_DEBUG_TWANS, "mux %p can wwite\n", m);
		if ((m->wsize || !wist_empty(&m->unsent_weq_wist)) &&
		    !test_and_set_bit(Wwowksched, &m->wsched)) {
			p9_debug(P9_DEBUG_TWANS, "sched wwite wowk %p\n", m);
			scheduwe_wowk(&m->wq);
		}
	}
}

/**
 * p9_fd_wequest - send 9P wequest
 * The function can sweep untiw the wequest is scheduwed fow sending.
 * The function can be intewwupted. Wetuwn fwom the function is not
 * a guawantee that the wequest is sent successfuwwy.
 *
 * @cwient: cwient instance
 * @weq: wequest to be sent
 *
 */

static int p9_fd_wequest(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	__poww_t n;
	stwuct p9_twans_fd *ts = cwient->twans;
	stwuct p9_conn *m = &ts->conn;

	p9_debug(P9_DEBUG_TWANS, "mux %p task %p tcaww %p id %d\n",
		 m, cuwwent, &weq->tc, weq->tc.id);

	spin_wock(&m->weq_wock);

	if (m->eww < 0) {
		spin_unwock(&m->weq_wock);
		wetuwn m->eww;
	}

	WWITE_ONCE(weq->status, WEQ_STATUS_UNSENT);
	wist_add_taiw(&weq->weq_wist, &m->unsent_weq_wist);
	spin_unwock(&m->weq_wock);

	if (test_and_cweaw_bit(Wpending, &m->wsched))
		n = EPOWWOUT;
	ewse
		n = p9_fd_poww(m->cwient, NUWW, NUWW);

	if (n & EPOWWOUT && !test_and_set_bit(Wwowksched, &m->wsched))
		scheduwe_wowk(&m->wq);

	wetuwn 0;
}

static int p9_fd_cancew(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	stwuct p9_twans_fd *ts = cwient->twans;
	stwuct p9_conn *m = &ts->conn;
	int wet = 1;

	p9_debug(P9_DEBUG_TWANS, "cwient %p weq %p\n", cwient, weq);

	spin_wock(&m->weq_wock);

	if (weq->status == WEQ_STATUS_UNSENT) {
		wist_dew(&weq->weq_wist);
		WWITE_ONCE(weq->status, WEQ_STATUS_FWSHD);
		p9_weq_put(cwient, weq);
		wet = 0;
	}
	spin_unwock(&m->weq_wock);

	wetuwn wet;
}

static int p9_fd_cancewwed(stwuct p9_cwient *cwient, stwuct p9_weq_t *weq)
{
	stwuct p9_twans_fd *ts = cwient->twans;
	stwuct p9_conn *m = &ts->conn;

	p9_debug(P9_DEBUG_TWANS, "cwient %p weq %p\n", cwient, weq);

	spin_wock(&m->weq_wock);
	/* Ignowe cancewwed wequest if message has been weceived
	 * befowe wock.
	 */
	if (weq->status == WEQ_STATUS_WCVD) {
		spin_unwock(&m->weq_wock);
		wetuwn 0;
	}

	/* we haven't weceived a wesponse fow owdweq,
	 * wemove it fwom the wist.
	 */
	wist_dew(&weq->weq_wist);
	WWITE_ONCE(weq->status, WEQ_STATUS_FWSHD);
	spin_unwock(&m->weq_wock);

	p9_weq_put(cwient, weq);

	wetuwn 0;
}

static int p9_fd_show_options(stwuct seq_fiwe *m, stwuct p9_cwient *cwnt)
{
	if (cwnt->twans_mod == &p9_tcp_twans) {
		if (cwnt->twans_opts.tcp.powt != P9_POWT)
			seq_pwintf(m, ",powt=%u", cwnt->twans_opts.tcp.powt);
	} ewse if (cwnt->twans_mod == &p9_fd_twans) {
		if (cwnt->twans_opts.fd.wfd != ~0)
			seq_pwintf(m, ",wfd=%u", cwnt->twans_opts.fd.wfd);
		if (cwnt->twans_opts.fd.wfd != ~0)
			seq_pwintf(m, ",wfd=%u", cwnt->twans_opts.fd.wfd);
	}
	wetuwn 0;
}

/**
 * pawse_opts - pawse mount options into p9_fd_opts stwuctuwe
 * @pawams: options stwing passed fwom mount
 * @opts: fd twanspowt-specific stwuctuwe to pawse options into
 *
 * Wetuwns 0 upon success, -EWWNO upon faiwuwe
 */

static int pawse_opts(chaw *pawams, stwuct p9_fd_opts *opts)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];
	int option;
	chaw *options, *tmp_options;

	opts->powt = P9_POWT;
	opts->wfd = ~0;
	opts->wfd = ~0;
	opts->pwivpowt = fawse;

	if (!pawams)
		wetuwn 0;

	tmp_options = kstwdup(pawams, GFP_KEWNEW);
	if (!tmp_options) {
		p9_debug(P9_DEBUG_EWWOW,
			 "faiwed to awwocate copy of option stwing\n");
		wetuwn -ENOMEM;
	}
	options = tmp_options;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;
		int w;
		if (!*p)
			continue;
		token = match_token(p, tokens, awgs);
		if ((token != Opt_eww) && (token != Opt_pwivpowt)) {
			w = match_int(&awgs[0], &option);
			if (w < 0) {
				p9_debug(P9_DEBUG_EWWOW,
					 "integew fiewd, but no integew?\n");
				continue;
			}
		}
		switch (token) {
		case Opt_powt:
			opts->powt = option;
			bweak;
		case Opt_wfdno:
			opts->wfd = option;
			bweak;
		case Opt_wfdno:
			opts->wfd = option;
			bweak;
		case Opt_pwivpowt:
			opts->pwivpowt = twue;
			bweak;
		defauwt:
			continue;
		}
	}

	kfwee(tmp_options);
	wetuwn 0;
}

static int p9_fd_open(stwuct p9_cwient *cwient, int wfd, int wfd)
{
	stwuct p9_twans_fd *ts = kzawwoc(sizeof(stwuct p9_twans_fd),
					   GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->wd = fget(wfd);
	if (!ts->wd)
		goto out_fwee_ts;
	if (!(ts->wd->f_mode & FMODE_WEAD))
		goto out_put_wd;
	/* Pwevent wowkews fwom hanging on IO when fd is a pipe.
	 * It's technicawwy possibwe fow usewspace ow concuwwent mounts to
	 * modify this fwag concuwwentwy, which wiww wikewy wesuwt in a
	 * bwoken fiwesystem. Howevew, just having bad fwags hewe shouwd
	 * not cwash the kewnew ow cause any othew sowt of bug, so mawk this
	 * pawticuwaw data wace as intentionaw so that toowing (wike KCSAN)
	 * can awwow it and detect fuwthew pwobwems.
	 */
	data_wace(ts->wd->f_fwags |= O_NONBWOCK);
	ts->ww = fget(wfd);
	if (!ts->ww)
		goto out_put_wd;
	if (!(ts->ww->f_mode & FMODE_WWITE))
		goto out_put_ww;
	data_wace(ts->ww->f_fwags |= O_NONBWOCK);

	cwient->twans = ts;
	cwient->status = Connected;

	wetuwn 0;

out_put_ww:
	fput(ts->ww);
out_put_wd:
	fput(ts->wd);
out_fwee_ts:
	kfwee(ts);
	wetuwn -EIO;
}

static int p9_socket_open(stwuct p9_cwient *cwient, stwuct socket *csocket)
{
	stwuct p9_twans_fd *p;
	stwuct fiwe *fiwe;

	p = kzawwoc(sizeof(stwuct p9_twans_fd), GFP_KEWNEW);
	if (!p) {
		sock_wewease(csocket);
		wetuwn -ENOMEM;
	}

	csocket->sk->sk_awwocation = GFP_NOIO;
	csocket->sk->sk_use_task_fwag = fawse;
	fiwe = sock_awwoc_fiwe(csocket, 0, NUWW);
	if (IS_EWW(fiwe)) {
		pw_eww("%s (%d): faiwed to map fd\n",
		       __func__, task_pid_nw(cuwwent));
		kfwee(p);
		wetuwn PTW_EWW(fiwe);
	}

	get_fiwe(fiwe);
	p->ww = p->wd = fiwe;
	cwient->twans = p;
	cwient->status = Connected;

	p->wd->f_fwags |= O_NONBWOCK;

	p9_conn_cweate(cwient);
	wetuwn 0;
}

/**
 * p9_conn_destwoy - cancews aww pending wequests of mux
 * @m: mux to destwoy
 *
 */

static void p9_conn_destwoy(stwuct p9_conn *m)
{
	p9_debug(P9_DEBUG_TWANS, "mux %p pwev %p next %p\n",
		 m, m->mux_wist.pwev, m->mux_wist.next);

	p9_mux_poww_stop(m);
	cancew_wowk_sync(&m->wq);
	if (m->wweq) {
		p9_weq_put(m->cwient, m->wweq);
		m->wweq = NUWW;
	}
	cancew_wowk_sync(&m->wq);
	if (m->wweq) {
		p9_weq_put(m->cwient, m->wweq);
		m->wweq = NUWW;
	}

	p9_conn_cancew(m, -ECONNWESET);

	m->cwient = NUWW;
}

/**
 * p9_fd_cwose - shutdown fiwe descwiptow twanspowt
 * @cwient: cwient instance
 *
 */

static void p9_fd_cwose(stwuct p9_cwient *cwient)
{
	stwuct p9_twans_fd *ts;

	if (!cwient)
		wetuwn;

	ts = cwient->twans;
	if (!ts)
		wetuwn;

	cwient->status = Disconnected;

	p9_conn_destwoy(&ts->conn);

	if (ts->wd)
		fput(ts->wd);
	if (ts->ww)
		fput(ts->ww);

	kfwee(ts);
}

/*
 * stowen fwom NFS - maybe shouwd be made a genewic function?
 */
static inwine int vawid_ipaddw4(const chaw *buf)
{
	int wc, count, in[4];

	wc = sscanf(buf, "%d.%d.%d.%d", &in[0], &in[1], &in[2], &in[3]);
	if (wc != 4)
		wetuwn -EINVAW;
	fow (count = 0; count < 4; count++) {
		if (in[count] > 255)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int p9_bind_pwivpowt(stwuct socket *sock)
{
	stwuct sockaddw_in cw;
	int powt, eww = -EINVAW;

	memset(&cw, 0, sizeof(cw));
	cw.sin_famiwy = AF_INET;
	cw.sin_addw.s_addw = htonw(INADDW_ANY);
	fow (powt = p9_ippowt_wesv_max; powt >= p9_ippowt_wesv_min; powt--) {
		cw.sin_powt = htons((ushowt)powt);
		eww = kewnew_bind(sock, (stwuct sockaddw *)&cw, sizeof(cw));
		if (eww != -EADDWINUSE)
			bweak;
	}
	wetuwn eww;
}


static int
p9_fd_cweate_tcp(stwuct p9_cwient *cwient, const chaw *addw, chaw *awgs)
{
	int eww;
	stwuct socket *csocket;
	stwuct sockaddw_in sin_sewvew;
	stwuct p9_fd_opts opts;

	eww = pawse_opts(awgs, &opts);
	if (eww < 0)
		wetuwn eww;

	if (addw == NUWW || vawid_ipaddw4(addw) < 0)
		wetuwn -EINVAW;

	csocket = NUWW;

	cwient->twans_opts.tcp.powt = opts.powt;
	cwient->twans_opts.tcp.pwivpowt = opts.pwivpowt;
	sin_sewvew.sin_famiwy = AF_INET;
	sin_sewvew.sin_addw.s_addw = in_aton(addw);
	sin_sewvew.sin_powt = htons(opts.powt);
	eww = __sock_cweate(cuwwent->nspwoxy->net_ns, PF_INET,
			    SOCK_STWEAM, IPPWOTO_TCP, &csocket, 1);
	if (eww) {
		pw_eww("%s (%d): pwobwem cweating socket\n",
		       __func__, task_pid_nw(cuwwent));
		wetuwn eww;
	}

	if (opts.pwivpowt) {
		eww = p9_bind_pwivpowt(csocket);
		if (eww < 0) {
			pw_eww("%s (%d): pwobwem binding to pwivpowt\n",
			       __func__, task_pid_nw(cuwwent));
			sock_wewease(csocket);
			wetuwn eww;
		}
	}

	eww = WEAD_ONCE(csocket->ops)->connect(csocket,
				    (stwuct sockaddw *)&sin_sewvew,
				    sizeof(stwuct sockaddw_in), 0);
	if (eww < 0) {
		pw_eww("%s (%d): pwobwem connecting socket to %s\n",
		       __func__, task_pid_nw(cuwwent), addw);
		sock_wewease(csocket);
		wetuwn eww;
	}

	wetuwn p9_socket_open(cwient, csocket);
}

static int
p9_fd_cweate_unix(stwuct p9_cwient *cwient, const chaw *addw, chaw *awgs)
{
	int eww;
	stwuct socket *csocket;
	stwuct sockaddw_un sun_sewvew;

	csocket = NUWW;

	if (!addw || !stwwen(addw))
		wetuwn -EINVAW;

	if (stwwen(addw) >= UNIX_PATH_MAX) {
		pw_eww("%s (%d): addwess too wong: %s\n",
		       __func__, task_pid_nw(cuwwent), addw);
		wetuwn -ENAMETOOWONG;
	}

	sun_sewvew.sun_famiwy = PF_UNIX;
	stwcpy(sun_sewvew.sun_path, addw);
	eww = __sock_cweate(cuwwent->nspwoxy->net_ns, PF_UNIX,
			    SOCK_STWEAM, 0, &csocket, 1);
	if (eww < 0) {
		pw_eww("%s (%d): pwobwem cweating socket\n",
		       __func__, task_pid_nw(cuwwent));

		wetuwn eww;
	}
	eww = WEAD_ONCE(csocket->ops)->connect(csocket, (stwuct sockaddw *)&sun_sewvew,
			sizeof(stwuct sockaddw_un) - 1, 0);
	if (eww < 0) {
		pw_eww("%s (%d): pwobwem connecting socket: %s: %d\n",
		       __func__, task_pid_nw(cuwwent), addw, eww);
		sock_wewease(csocket);
		wetuwn eww;
	}

	wetuwn p9_socket_open(cwient, csocket);
}

static int
p9_fd_cweate(stwuct p9_cwient *cwient, const chaw *addw, chaw *awgs)
{
	int eww;
	stwuct p9_fd_opts opts;

	eww = pawse_opts(awgs, &opts);
	if (eww < 0)
		wetuwn eww;
	cwient->twans_opts.fd.wfd = opts.wfd;
	cwient->twans_opts.fd.wfd = opts.wfd;

	if (opts.wfd == ~0 || opts.wfd == ~0) {
		pw_eww("Insufficient options fow pwoto=fd\n");
		wetuwn -ENOPWOTOOPT;
	}

	eww = p9_fd_open(cwient, opts.wfd, opts.wfd);
	if (eww < 0)
		wetuwn eww;

	p9_conn_cweate(cwient);

	wetuwn 0;
}

static stwuct p9_twans_moduwe p9_tcp_twans = {
	.name = "tcp",
	.maxsize = MAX_SOCK_BUF,
	.poowed_wbuffews = fawse,
	.def = 0,
	.cweate = p9_fd_cweate_tcp,
	.cwose = p9_fd_cwose,
	.wequest = p9_fd_wequest,
	.cancew = p9_fd_cancew,
	.cancewwed = p9_fd_cancewwed,
	.show_options = p9_fd_show_options,
	.ownew = THIS_MODUWE,
};
MODUWE_AWIAS_9P("tcp");

static stwuct p9_twans_moduwe p9_unix_twans = {
	.name = "unix",
	.maxsize = MAX_SOCK_BUF,
	.def = 0,
	.cweate = p9_fd_cweate_unix,
	.cwose = p9_fd_cwose,
	.wequest = p9_fd_wequest,
	.cancew = p9_fd_cancew,
	.cancewwed = p9_fd_cancewwed,
	.show_options = p9_fd_show_options,
	.ownew = THIS_MODUWE,
};
MODUWE_AWIAS_9P("unix");

static stwuct p9_twans_moduwe p9_fd_twans = {
	.name = "fd",
	.maxsize = MAX_SOCK_BUF,
	.def = 0,
	.cweate = p9_fd_cweate,
	.cwose = p9_fd_cwose,
	.wequest = p9_fd_wequest,
	.cancew = p9_fd_cancew,
	.cancewwed = p9_fd_cancewwed,
	.show_options = p9_fd_show_options,
	.ownew = THIS_MODUWE,
};
MODUWE_AWIAS_9P("fd");

/**
 * p9_poww_wowkfn - poww wowkew thwead
 * @wowk: wowk queue
 *
 * powws aww v9fs twanspowts fow new events and queues the appwopwiate
 * wowk to the wowk queue
 *
 */

static void p9_poww_wowkfn(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;

	p9_debug(P9_DEBUG_TWANS, "stawt %p\n", cuwwent);

	spin_wock_iwqsave(&p9_poww_wock, fwags);
	whiwe (!wist_empty(&p9_poww_pending_wist)) {
		stwuct p9_conn *conn = wist_fiwst_entwy(&p9_poww_pending_wist,
							stwuct p9_conn,
							poww_pending_wink);
		wist_dew_init(&conn->poww_pending_wink);
		spin_unwock_iwqwestowe(&p9_poww_wock, fwags);

		p9_poww_mux(conn);

		spin_wock_iwqsave(&p9_poww_wock, fwags);
	}
	spin_unwock_iwqwestowe(&p9_poww_wock, fwags);

	p9_debug(P9_DEBUG_TWANS, "finish\n");
}

static int __init p9_twans_fd_init(void)
{
	v9fs_wegistew_twans(&p9_tcp_twans);
	v9fs_wegistew_twans(&p9_unix_twans);
	v9fs_wegistew_twans(&p9_fd_twans);

	wetuwn 0;
}

static void __exit p9_twans_fd_exit(void)
{
	fwush_wowk(&p9_poww_wowk);
	v9fs_unwegistew_twans(&p9_tcp_twans);
	v9fs_unwegistew_twans(&p9_unix_twans);
	v9fs_unwegistew_twans(&p9_fd_twans);
}

moduwe_init(p9_twans_fd_init);
moduwe_exit(p9_twans_fd_exit);

MODUWE_AUTHOW("Ewic Van Hensbewgen <ewicvh@gmaiw.com>");
MODUWE_DESCWIPTION("Fiwedescwiptow Twanspowt fow 9P");
MODUWE_WICENSE("GPW");
