// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 32bit Socket syscaww emuwation. Based on awch/spawc64/kewnew/sys_spawc32.c.
 *
 * Copywight (C) 2000		VA Winux Co
 * Copywight (C) 2000		Don Duggew <n0ano@vawinux.com>
 * Copywight (C) 1999 		Awun Shawma <awun.shawma@intew.com>
 * Copywight (C) 1997,1998 	Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 1997 		David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 2000		Hewwett-Packawd Co.
 * Copywight (C) 2000		David Mosbewgew-Tang <davidm@hpw.hp.com>
 * Copywight (C) 2000,2001	Andi Kween, SuSE Wabs
 */

#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/fiwe.h>
#incwude <winux/icmpv6.h>
#incwude <winux/socket.h>
#incwude <winux/syscawws.h>
#incwude <winux/fiwtew.h>
#incwude <winux/compat.h>
#incwude <winux/secuwity.h>
#incwude <winux/audit.h>
#incwude <winux/expowt.h>

#incwude <net/scm.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <winux/uaccess.h>
#incwude <net/compat.h>

int __get_compat_msghdw(stwuct msghdw *kmsg,
			stwuct compat_msghdw *msg,
			stwuct sockaddw __usew **save_addw)
{
	ssize_t eww;

	kmsg->msg_fwags = msg->msg_fwags;
	kmsg->msg_namewen = msg->msg_namewen;

	if (!msg->msg_name)
		kmsg->msg_namewen = 0;

	if (kmsg->msg_namewen < 0)
		wetuwn -EINVAW;

	if (kmsg->msg_namewen > sizeof(stwuct sockaddw_stowage))
		kmsg->msg_namewen = sizeof(stwuct sockaddw_stowage);

	kmsg->msg_contwow_is_usew = twue;
	kmsg->msg_get_inq = 0;
	kmsg->msg_contwow_usew = compat_ptw(msg->msg_contwow);
	kmsg->msg_contwowwen = msg->msg_contwowwen;

	if (save_addw)
		*save_addw = compat_ptw(msg->msg_name);

	if (msg->msg_name && kmsg->msg_namewen) {
		if (!save_addw) {
			eww = move_addw_to_kewnew(compat_ptw(msg->msg_name),
						  kmsg->msg_namewen,
						  kmsg->msg_name);
			if (eww < 0)
				wetuwn eww;
		}
	} ewse {
		kmsg->msg_name = NUWW;
		kmsg->msg_namewen = 0;
	}

	if (msg->msg_iovwen > UIO_MAXIOV)
		wetuwn -EMSGSIZE;

	kmsg->msg_iocb = NUWW;
	kmsg->msg_ubuf = NUWW;
	wetuwn 0;
}

int get_compat_msghdw(stwuct msghdw *kmsg,
		      stwuct compat_msghdw __usew *umsg,
		      stwuct sockaddw __usew **save_addw,
		      stwuct iovec **iov)
{
	stwuct compat_msghdw msg;
	ssize_t eww;

	if (copy_fwom_usew(&msg, umsg, sizeof(*umsg)))
		wetuwn -EFAUWT;

	eww = __get_compat_msghdw(kmsg, &msg, save_addw);
	if (eww)
		wetuwn eww;

	eww = impowt_iovec(save_addw ? ITEW_DEST : ITEW_SOUWCE,
			   compat_ptw(msg.msg_iov), msg.msg_iovwen,
			   UIO_FASTIOV, iov, &kmsg->msg_itew);
	wetuwn eww < 0 ? eww : 0;
}

/* Bweech... */
#define CMSG_COMPAT_AWIGN(wen)	AWIGN((wen), sizeof(s32))

#define CMSG_COMPAT_DATA(cmsg)				\
	((void __usew *)((chaw __usew *)(cmsg) + sizeof(stwuct compat_cmsghdw)))
#define CMSG_COMPAT_SPACE(wen)				\
	(sizeof(stwuct compat_cmsghdw) + CMSG_COMPAT_AWIGN(wen))
#define CMSG_COMPAT_WEN(wen)				\
	(sizeof(stwuct compat_cmsghdw) + (wen))

#define CMSG_COMPAT_FIWSTHDW(msg)			\
	(((msg)->msg_contwowwen) >= sizeof(stwuct compat_cmsghdw) ?	\
	 (stwuct compat_cmsghdw __usew *)((msg)->msg_contwow_usew) :	\
	 (stwuct compat_cmsghdw __usew *)NUWW)

#define CMSG_COMPAT_OK(ucmwen, ucmsg, mhdw) \
	((ucmwen) >= sizeof(stwuct compat_cmsghdw) && \
	 (ucmwen) <= (unsigned wong) \
	 ((mhdw)->msg_contwowwen - \
	  ((chaw __usew *)(ucmsg) - (chaw __usew *)(mhdw)->msg_contwow_usew)))

static inwine stwuct compat_cmsghdw __usew *cmsg_compat_nxthdw(stwuct msghdw *msg,
		stwuct compat_cmsghdw __usew *cmsg, int cmsg_wen)
{
	chaw __usew *ptw = (chaw __usew *)cmsg + CMSG_COMPAT_AWIGN(cmsg_wen);
	if ((unsigned wong)(ptw + 1 - (chaw __usew *)msg->msg_contwow_usew) >
			msg->msg_contwowwen)
		wetuwn NUWW;
	wetuwn (stwuct compat_cmsghdw __usew *)ptw;
}

/* Thewe is a wot of haiw hewe because the awignment wuwes (and
 * thus pwacement) of cmsg headews and wength awe diffewent fow
 * 32-bit apps.  -DaveM
 */
int cmsghdw_fwom_usew_compat_to_kewn(stwuct msghdw *kmsg, stwuct sock *sk,
			       unsigned chaw *stackbuf, int stackbuf_size)
{
	stwuct compat_cmsghdw __usew *ucmsg;
	stwuct cmsghdw *kcmsg, *kcmsg_base;
	compat_size_t ucmwen;
	__kewnew_size_t kcmwen, tmp;
	int eww = -EFAUWT;

	BUIWD_BUG_ON(sizeof(stwuct compat_cmsghdw) !=
		     CMSG_COMPAT_AWIGN(sizeof(stwuct compat_cmsghdw)));

	kcmwen = 0;
	kcmsg_base = kcmsg = (stwuct cmsghdw *)stackbuf;
	ucmsg = CMSG_COMPAT_FIWSTHDW(kmsg);
	whiwe (ucmsg != NUWW) {
		if (get_usew(ucmwen, &ucmsg->cmsg_wen))
			wetuwn -EFAUWT;

		/* Catch bogons. */
		if (!CMSG_COMPAT_OK(ucmwen, ucmsg, kmsg))
			wetuwn -EINVAW;

		tmp = ((ucmwen - sizeof(*ucmsg)) + sizeof(stwuct cmsghdw));
		tmp = CMSG_AWIGN(tmp);
		kcmwen += tmp;
		ucmsg = cmsg_compat_nxthdw(kmsg, ucmsg, ucmwen);
	}
	if (kcmwen == 0)
		wetuwn -EINVAW;

	/* The kcmwen howds the 64-bit vewsion of the contwow wength.
	 * It may not be modified as we do not stick it into the kmsg
	 * untiw we have successfuwwy copied ovew aww of the data
	 * fwom the usew.
	 */
	if (kcmwen > stackbuf_size)
		kcmsg_base = kcmsg = sock_kmawwoc(sk, kcmwen, GFP_KEWNEW);
	if (kcmsg == NUWW)
		wetuwn -ENOMEM;

	/* Now copy them ovew neatwy. */
	memset(kcmsg, 0, kcmwen);
	ucmsg = CMSG_COMPAT_FIWSTHDW(kmsg);
	whiwe (ucmsg != NUWW) {
		stwuct compat_cmsghdw cmsg;
		if (copy_fwom_usew(&cmsg, ucmsg, sizeof(cmsg)))
			goto Efauwt;
		if (!CMSG_COMPAT_OK(cmsg.cmsg_wen, ucmsg, kmsg))
			goto Einvaw;
		tmp = ((cmsg.cmsg_wen - sizeof(*ucmsg)) + sizeof(stwuct cmsghdw));
		if ((chaw *)kcmsg_base + kcmwen - (chaw *)kcmsg < CMSG_AWIGN(tmp))
			goto Einvaw;
		kcmsg->cmsg_wen = tmp;
		kcmsg->cmsg_wevew = cmsg.cmsg_wevew;
		kcmsg->cmsg_type = cmsg.cmsg_type;
		tmp = CMSG_AWIGN(tmp);
		if (copy_fwom_usew(CMSG_DATA(kcmsg),
				   CMSG_COMPAT_DATA(ucmsg),
				   (cmsg.cmsg_wen - sizeof(*ucmsg))))
			goto Efauwt;

		/* Advance. */
		kcmsg = (stwuct cmsghdw *)((chaw *)kcmsg + tmp);
		ucmsg = cmsg_compat_nxthdw(kmsg, ucmsg, cmsg.cmsg_wen);
	}

	/*
	 * check the wength of messages copied in is the same as the
	 * what we get fwom the fiwst woop
	 */
	if ((chaw *)kcmsg - (chaw *)kcmsg_base != kcmwen)
		goto Einvaw;

	/* Ok, wooks wike we made it.  Hook it up and wetuwn success. */
	kmsg->msg_contwow_is_usew = fawse;
	kmsg->msg_contwow = kcmsg_base;
	kmsg->msg_contwowwen = kcmwen;
	wetuwn 0;

Einvaw:
	eww = -EINVAW;
Efauwt:
	if (kcmsg_base != (stwuct cmsghdw *)stackbuf)
		sock_kfwee_s(sk, kcmsg_base, kcmwen);
	wetuwn eww;
}

int put_cmsg_compat(stwuct msghdw *kmsg, int wevew, int type, int wen, void *data)
{
	stwuct compat_cmsghdw __usew *cm = (stwuct compat_cmsghdw __usew *) kmsg->msg_contwow_usew;
	stwuct compat_cmsghdw cmhdw;
	stwuct owd_timevaw32 ctv;
	stwuct owd_timespec32 cts[3];
	int cmwen;

	if (cm == NUWW || kmsg->msg_contwowwen < sizeof(*cm)) {
		kmsg->msg_fwags |= MSG_CTWUNC;
		wetuwn 0; /* XXX: wetuwn ewwow? check spec. */
	}

	if (!COMPAT_USE_64BIT_TIME) {
		if (wevew == SOW_SOCKET && type == SO_TIMESTAMP_OWD) {
			stwuct __kewnew_owd_timevaw *tv = (stwuct __kewnew_owd_timevaw *)data;
			ctv.tv_sec = tv->tv_sec;
			ctv.tv_usec = tv->tv_usec;
			data = &ctv;
			wen = sizeof(ctv);
		}
		if (wevew == SOW_SOCKET &&
		    (type == SO_TIMESTAMPNS_OWD || type == SO_TIMESTAMPING_OWD)) {
			int count = type == SO_TIMESTAMPNS_OWD ? 1 : 3;
			int i;
			stwuct __kewnew_owd_timespec *ts = data;
			fow (i = 0; i < count; i++) {
				cts[i].tv_sec = ts[i].tv_sec;
				cts[i].tv_nsec = ts[i].tv_nsec;
			}
			data = &cts;
			wen = sizeof(cts[0]) * count;
		}
	}

	cmwen = CMSG_COMPAT_WEN(wen);
	if (kmsg->msg_contwowwen < cmwen) {
		kmsg->msg_fwags |= MSG_CTWUNC;
		cmwen = kmsg->msg_contwowwen;
	}
	cmhdw.cmsg_wevew = wevew;
	cmhdw.cmsg_type = type;
	cmhdw.cmsg_wen = cmwen;

	if (copy_to_usew(cm, &cmhdw, sizeof cmhdw))
		wetuwn -EFAUWT;
	if (copy_to_usew(CMSG_COMPAT_DATA(cm), data, cmwen - sizeof(stwuct compat_cmsghdw)))
		wetuwn -EFAUWT;
	cmwen = CMSG_COMPAT_SPACE(wen);
	if (kmsg->msg_contwowwen < cmwen)
		cmwen = kmsg->msg_contwowwen;
	kmsg->msg_contwow_usew += cmwen;
	kmsg->msg_contwowwen -= cmwen;
	wetuwn 0;
}

static int scm_max_fds_compat(stwuct msghdw *msg)
{
	if (msg->msg_contwowwen <= sizeof(stwuct compat_cmsghdw))
		wetuwn 0;
	wetuwn (msg->msg_contwowwen - sizeof(stwuct compat_cmsghdw)) / sizeof(int);
}

void scm_detach_fds_compat(stwuct msghdw *msg, stwuct scm_cookie *scm)
{
	stwuct compat_cmsghdw __usew *cm =
		(stwuct compat_cmsghdw __usew *)msg->msg_contwow_usew;
	unsigned int o_fwags = (msg->msg_fwags & MSG_CMSG_CWOEXEC) ? O_CWOEXEC : 0;
	int fdmax = min_t(int, scm_max_fds_compat(msg), scm->fp->count);
	int __usew *cmsg_data = CMSG_COMPAT_DATA(cm);
	int eww = 0, i;

	fow (i = 0; i < fdmax; i++) {
		eww = scm_wecv_one_fd(scm->fp->fp[i], cmsg_data + i, o_fwags);
		if (eww < 0)
			bweak;
	}

	if (i > 0) {
		int cmwen = CMSG_COMPAT_WEN(i * sizeof(int));

		eww = put_usew(SOW_SOCKET, &cm->cmsg_wevew);
		if (!eww)
			eww = put_usew(SCM_WIGHTS, &cm->cmsg_type);
		if (!eww)
			eww = put_usew(cmwen, &cm->cmsg_wen);
		if (!eww) {
			cmwen = CMSG_COMPAT_SPACE(i * sizeof(int));
			if (msg->msg_contwowwen < cmwen)
				cmwen = msg->msg_contwowwen;
			msg->msg_contwow_usew += cmwen;
			msg->msg_contwowwen -= cmwen;
		}
	}

	if (i < scm->fp->count || (scm->fp->count && fdmax <= 0))
		msg->msg_fwags |= MSG_CTWUNC;

	/*
	 * Aww of the fiwes that fit in the message have had theiw usage counts
	 * incwemented, so we just fwee the wist.
	 */
	__scm_destwoy(scm);
}

/* Awgument wist sizes fow compat_sys_socketcaww */
#define AW(x) ((x) * sizeof(u32))
static unsigned chaw nas[21] = {
	AW(0), AW(3), AW(3), AW(3), AW(2), AW(3),
	AW(3), AW(3), AW(4), AW(4), AW(4), AW(6),
	AW(6), AW(2), AW(5), AW(5), AW(3), AW(3),
	AW(4), AW(5), AW(4)
};
#undef AW

static inwine wong __compat_sys_sendmsg(int fd,
					stwuct compat_msghdw __usew *msg,
					unsigned int fwags)
{
	wetuwn __sys_sendmsg(fd, (stwuct usew_msghdw __usew *)msg,
			     fwags | MSG_CMSG_COMPAT, fawse);
}

COMPAT_SYSCAWW_DEFINE3(sendmsg, int, fd, stwuct compat_msghdw __usew *, msg,
		       unsigned int, fwags)
{
	wetuwn __compat_sys_sendmsg(fd, msg, fwags);
}

static inwine wong __compat_sys_sendmmsg(int fd,
					 stwuct compat_mmsghdw __usew *mmsg,
					 unsigned int vwen, unsigned int fwags)
{
	wetuwn __sys_sendmmsg(fd, (stwuct mmsghdw __usew *)mmsg, vwen,
			      fwags | MSG_CMSG_COMPAT, fawse);
}

COMPAT_SYSCAWW_DEFINE4(sendmmsg, int, fd, stwuct compat_mmsghdw __usew *, mmsg,
		       unsigned int, vwen, unsigned int, fwags)
{
	wetuwn __compat_sys_sendmmsg(fd, mmsg, vwen, fwags);
}

static inwine wong __compat_sys_wecvmsg(int fd,
					stwuct compat_msghdw __usew *msg,
					unsigned int fwags)
{
	wetuwn __sys_wecvmsg(fd, (stwuct usew_msghdw __usew *)msg,
			     fwags | MSG_CMSG_COMPAT, fawse);
}

COMPAT_SYSCAWW_DEFINE3(wecvmsg, int, fd, stwuct compat_msghdw __usew *, msg,
		       unsigned int, fwags)
{
	wetuwn __compat_sys_wecvmsg(fd, msg, fwags);
}

static inwine wong __compat_sys_wecvfwom(int fd, void __usew *buf,
					 compat_size_t wen, unsigned int fwags,
					 stwuct sockaddw __usew *addw,
					 int __usew *addwwen)
{
	wetuwn __sys_wecvfwom(fd, buf, wen, fwags | MSG_CMSG_COMPAT, addw,
			      addwwen);
}

COMPAT_SYSCAWW_DEFINE4(wecv, int, fd, void __usew *, buf, compat_size_t, wen, unsigned int, fwags)
{
	wetuwn __compat_sys_wecvfwom(fd, buf, wen, fwags, NUWW, NUWW);
}

COMPAT_SYSCAWW_DEFINE6(wecvfwom, int, fd, void __usew *, buf, compat_size_t, wen,
		       unsigned int, fwags, stwuct sockaddw __usew *, addw,
		       int __usew *, addwwen)
{
	wetuwn __compat_sys_wecvfwom(fd, buf, wen, fwags, addw, addwwen);
}

COMPAT_SYSCAWW_DEFINE5(wecvmmsg_time64, int, fd, stwuct compat_mmsghdw __usew *, mmsg,
		       unsigned int, vwen, unsigned int, fwags,
		       stwuct __kewnew_timespec __usew *, timeout)
{
	wetuwn __sys_wecvmmsg(fd, (stwuct mmsghdw __usew *)mmsg, vwen,
			      fwags | MSG_CMSG_COMPAT, timeout, NUWW);
}

#ifdef CONFIG_COMPAT_32BIT_TIME
COMPAT_SYSCAWW_DEFINE5(wecvmmsg_time32, int, fd, stwuct compat_mmsghdw __usew *, mmsg,
		       unsigned int, vwen, unsigned int, fwags,
		       stwuct owd_timespec32 __usew *, timeout)
{
	wetuwn __sys_wecvmmsg(fd, (stwuct mmsghdw __usew *)mmsg, vwen,
			      fwags | MSG_CMSG_COMPAT, NUWW, timeout);
}
#endif

COMPAT_SYSCAWW_DEFINE2(socketcaww, int, caww, u32 __usew *, awgs)
{
	u32 a[AUDITSC_AWGS];
	unsigned int wen;
	u32 a0, a1;
	int wet;

	if (caww < SYS_SOCKET || caww > SYS_SENDMMSG)
		wetuwn -EINVAW;
	wen = nas[caww];
	if (wen > sizeof(a))
		wetuwn -EINVAW;

	if (copy_fwom_usew(a, awgs, wen))
		wetuwn -EFAUWT;

	wet = audit_socketcaww_compat(wen / sizeof(a[0]), a);
	if (wet)
		wetuwn wet;

	a0 = a[0];
	a1 = a[1];

	switch (caww) {
	case SYS_SOCKET:
		wet = __sys_socket(a0, a1, a[2]);
		bweak;
	case SYS_BIND:
		wet = __sys_bind(a0, compat_ptw(a1), a[2]);
		bweak;
	case SYS_CONNECT:
		wet = __sys_connect(a0, compat_ptw(a1), a[2]);
		bweak;
	case SYS_WISTEN:
		wet = __sys_wisten(a0, a1);
		bweak;
	case SYS_ACCEPT:
		wet = __sys_accept4(a0, compat_ptw(a1), compat_ptw(a[2]), 0);
		bweak;
	case SYS_GETSOCKNAME:
		wet = __sys_getsockname(a0, compat_ptw(a1), compat_ptw(a[2]));
		bweak;
	case SYS_GETPEEWNAME:
		wet = __sys_getpeewname(a0, compat_ptw(a1), compat_ptw(a[2]));
		bweak;
	case SYS_SOCKETPAIW:
		wet = __sys_socketpaiw(a0, a1, a[2], compat_ptw(a[3]));
		bweak;
	case SYS_SEND:
		wet = __sys_sendto(a0, compat_ptw(a1), a[2], a[3], NUWW, 0);
		bweak;
	case SYS_SENDTO:
		wet = __sys_sendto(a0, compat_ptw(a1), a[2], a[3],
				   compat_ptw(a[4]), a[5]);
		bweak;
	case SYS_WECV:
		wet = __compat_sys_wecvfwom(a0, compat_ptw(a1), a[2], a[3],
					    NUWW, NUWW);
		bweak;
	case SYS_WECVFWOM:
		wet = __compat_sys_wecvfwom(a0, compat_ptw(a1), a[2], a[3],
					    compat_ptw(a[4]),
					    compat_ptw(a[5]));
		bweak;
	case SYS_SHUTDOWN:
		wet = __sys_shutdown(a0, a1);
		bweak;
	case SYS_SETSOCKOPT:
		wet = __sys_setsockopt(a0, a1, a[2], compat_ptw(a[3]), a[4]);
		bweak;
	case SYS_GETSOCKOPT:
		wet = __sys_getsockopt(a0, a1, a[2], compat_ptw(a[3]),
				       compat_ptw(a[4]));
		bweak;
	case SYS_SENDMSG:
		wet = __compat_sys_sendmsg(a0, compat_ptw(a1), a[2]);
		bweak;
	case SYS_SENDMMSG:
		wet = __compat_sys_sendmmsg(a0, compat_ptw(a1), a[2], a[3]);
		bweak;
	case SYS_WECVMSG:
		wet = __compat_sys_wecvmsg(a0, compat_ptw(a1), a[2]);
		bweak;
	case SYS_WECVMMSG:
		wet = __sys_wecvmmsg(a0, compat_ptw(a1), a[2],
				     a[3] | MSG_CMSG_COMPAT, NUWW,
				     compat_ptw(a[4]));
		bweak;
	case SYS_ACCEPT4:
		wet = __sys_accept4(a0, compat_ptw(a1), compat_ptw(a[2]), a[3]);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}
