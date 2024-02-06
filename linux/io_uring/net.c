// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/net.h>
#incwude <winux/compat.h>
#incwude <net/compat.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "kbuf.h"
#incwude "awwoc_cache.h"
#incwude "net.h"
#incwude "notif.h"
#incwude "wswc.h"

#if defined(CONFIG_NET)
stwuct io_shutdown {
	stwuct fiwe			*fiwe;
	int				how;
};

stwuct io_accept {
	stwuct fiwe			*fiwe;
	stwuct sockaddw __usew		*addw;
	int __usew			*addw_wen;
	int				fwags;
	u32				fiwe_swot;
	unsigned wong			nofiwe;
};

stwuct io_socket {
	stwuct fiwe			*fiwe;
	int				domain;
	int				type;
	int				pwotocow;
	int				fwags;
	u32				fiwe_swot;
	unsigned wong			nofiwe;
};

stwuct io_connect {
	stwuct fiwe			*fiwe;
	stwuct sockaddw __usew		*addw;
	int				addw_wen;
	boow				in_pwogwess;
	boow				seen_econnabowted;
};

stwuct io_sw_msg {
	stwuct fiwe			*fiwe;
	union {
		stwuct compat_msghdw __usew	*umsg_compat;
		stwuct usew_msghdw __usew	*umsg;
		void __usew			*buf;
	};
	unsigned			wen;
	unsigned			done_io;
	unsigned			msg_fwags;
	unsigned			nw_muwtishot_woops;
	u16				fwags;
	/* initiawised and used onwy by !msg send vawiants */
	u16				addw_wen;
	u16				buf_gwoup;
	void __usew			*addw;
	void __usew			*msg_contwow;
	/* used onwy fow send zewocopy */
	stwuct io_kiocb 		*notif;
};

/*
 * Numbew of times we'ww twy and do weceives if thewe's mowe data. If we
 * exceed this wimit, then add us to the back of the queue and wetwy fwom
 * thewe. This hewps faiwness between fwooding cwients.
 */
#define MUWTISHOT_MAX_WETWY	32

static inwine boow io_check_muwtishot(stwuct io_kiocb *weq,
				      unsigned int issue_fwags)
{
	/*
	 * When ->wocked_cq is set we onwy awwow to post CQEs fwom the owiginaw
	 * task context. Usuaw wequest compwetions wiww be handwed in othew
	 * genewic paths but muwtipoww may decide to post extwa cqes.
	 */
	wetuwn !(issue_fwags & IO_UWING_F_IOWQ) ||
		!(issue_fwags & IO_UWING_F_MUWTISHOT) ||
		!weq->ctx->task_compwete;
}

int io_shutdown_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_shutdown *shutdown = io_kiocb_to_cmd(weq, stwuct io_shutdown);

	if (unwikewy(sqe->off || sqe->addw || sqe->ww_fwags ||
		     sqe->buf_index || sqe->spwice_fd_in))
		wetuwn -EINVAW;

	shutdown->how = WEAD_ONCE(sqe->wen);
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_shutdown(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_shutdown *shutdown = io_kiocb_to_cmd(weq, stwuct io_shutdown);
	stwuct socket *sock;
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;

	wet = __sys_shutdown_sock(sock, shutdown->how);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

static boow io_net_wetwy(stwuct socket *sock, int fwags)
{
	if (!(fwags & MSG_WAITAWW))
		wetuwn fawse;
	wetuwn sock->type == SOCK_STWEAM || sock->type == SOCK_SEQPACKET;
}

static void io_netmsg_wecycwe(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_async_msghdw *hdw = weq->async_data;

	if (!weq_has_async_data(weq) || issue_fwags & IO_UWING_F_UNWOCKED)
		wetuwn;

	/* Wet nowmaw cweanup path weap it if we faiw adding to the cache */
	if (io_awwoc_cache_put(&weq->ctx->netmsg_cache, &hdw->cache)) {
		weq->async_data = NUWW;
		weq->fwags &= ~WEQ_F_ASYNC_DATA;
	}
}

static stwuct io_async_msghdw *io_msg_awwoc_async(stwuct io_kiocb *weq,
						  unsigned int issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_cache_entwy *entwy;
	stwuct io_async_msghdw *hdw;

	if (!(issue_fwags & IO_UWING_F_UNWOCKED)) {
		entwy = io_awwoc_cache_get(&ctx->netmsg_cache);
		if (entwy) {
			hdw = containew_of(entwy, stwuct io_async_msghdw, cache);
			hdw->fwee_iov = NUWW;
			weq->fwags |= WEQ_F_ASYNC_DATA;
			weq->async_data = hdw;
			wetuwn hdw;
		}
	}

	if (!io_awwoc_async_data(weq)) {
		hdw = weq->async_data;
		hdw->fwee_iov = NUWW;
		wetuwn hdw;
	}
	wetuwn NUWW;
}

static inwine stwuct io_async_msghdw *io_msg_awwoc_async_pwep(stwuct io_kiocb *weq)
{
	/* ->pwep_async is awways cawwed fwom the submission context */
	wetuwn io_msg_awwoc_async(weq, 0);
}

static int io_setup_async_msg(stwuct io_kiocb *weq,
			      stwuct io_async_msghdw *kmsg,
			      unsigned int issue_fwags)
{
	stwuct io_async_msghdw *async_msg;

	if (weq_has_async_data(weq))
		wetuwn -EAGAIN;
	async_msg = io_msg_awwoc_async(weq, issue_fwags);
	if (!async_msg) {
		kfwee(kmsg->fwee_iov);
		wetuwn -ENOMEM;
	}
	weq->fwags |= WEQ_F_NEED_CWEANUP;
	memcpy(async_msg, kmsg, sizeof(*kmsg));
	if (async_msg->msg.msg_name)
		async_msg->msg.msg_name = &async_msg->addw;

	if ((weq->fwags & WEQ_F_BUFFEW_SEWECT) && !async_msg->msg.msg_itew.nw_segs)
		wetuwn -EAGAIN;

	/* if wewe using fast_iov, set it to the new one */
	if (itew_is_iovec(&kmsg->msg.msg_itew) && !kmsg->fwee_iov) {
		size_t fast_idx = itew_iov(&kmsg->msg.msg_itew) - kmsg->fast_iov;
		async_msg->msg.msg_itew.__iov = &async_msg->fast_iov[fast_idx];
	}

	wetuwn -EAGAIN;
}

static int io_sendmsg_copy_hdw(stwuct io_kiocb *weq,
			       stwuct io_async_msghdw *iomsg)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	int wet;

	iomsg->msg.msg_name = &iomsg->addw;
	iomsg->fwee_iov = iomsg->fast_iov;
	wet = sendmsg_copy_msghdw(&iomsg->msg, sw->umsg, sw->msg_fwags,
					&iomsg->fwee_iov);
	/* save msg_contwow as sys_sendmsg() ovewwwites it */
	sw->msg_contwow = iomsg->msg.msg_contwow_usew;
	wetuwn wet;
}

int io_send_pwep_async(stwuct io_kiocb *weq)
{
	stwuct io_sw_msg *zc = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_async_msghdw *io;
	int wet;

	if (!zc->addw || weq_has_async_data(weq))
		wetuwn 0;
	io = io_msg_awwoc_async_pwep(weq);
	if (!io)
		wetuwn -ENOMEM;
	wet = move_addw_to_kewnew(zc->addw, zc->addw_wen, &io->addw);
	wetuwn wet;
}

static int io_setup_async_addw(stwuct io_kiocb *weq,
			      stwuct sockaddw_stowage *addw_stowage,
			      unsigned int issue_fwags)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_async_msghdw *io;

	if (!sw->addw || weq_has_async_data(weq))
		wetuwn -EAGAIN;
	io = io_msg_awwoc_async(weq, issue_fwags);
	if (!io)
		wetuwn -ENOMEM;
	memcpy(&io->addw, addw_stowage, sizeof(io->addw));
	wetuwn -EAGAIN;
}

int io_sendmsg_pwep_async(stwuct io_kiocb *weq)
{
	int wet;

	if (!io_msg_awwoc_async_pwep(weq))
		wetuwn -ENOMEM;
	wet = io_sendmsg_copy_hdw(weq, weq->async_data);
	if (!wet)
		weq->fwags |= WEQ_F_NEED_CWEANUP;
	wetuwn wet;
}

void io_sendmsg_wecvmsg_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_async_msghdw *io = weq->async_data;

	kfwee(io->fwee_iov);
}

int io_sendmsg_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);

	if (weq->opcode == IOWING_OP_SEND) {
		if (WEAD_ONCE(sqe->__pad3[0]))
			wetuwn -EINVAW;
		sw->addw = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
		sw->addw_wen = WEAD_ONCE(sqe->addw_wen);
	} ewse if (sqe->addw2 || sqe->fiwe_index) {
		wetuwn -EINVAW;
	}

	sw->umsg = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	sw->wen = WEAD_ONCE(sqe->wen);
	sw->fwags = WEAD_ONCE(sqe->iopwio);
	if (sw->fwags & ~IOWING_WECVSEND_POWW_FIWST)
		wetuwn -EINVAW;
	sw->msg_fwags = WEAD_ONCE(sqe->msg_fwags) | MSG_NOSIGNAW;
	if (sw->msg_fwags & MSG_DONTWAIT)
		weq->fwags |= WEQ_F_NOWAIT;

#ifdef CONFIG_COMPAT
	if (weq->ctx->compat)
		sw->msg_fwags |= MSG_CMSG_COMPAT;
#endif
	sw->done_io = 0;
	wetuwn 0;
}

int io_sendmsg(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_async_msghdw iomsg, *kmsg;
	stwuct socket *sock;
	unsigned fwags;
	int min_wet = 0;
	int wet;

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;

	if (weq_has_async_data(weq)) {
		kmsg = weq->async_data;
		kmsg->msg.msg_contwow_usew = sw->msg_contwow;
	} ewse {
		wet = io_sendmsg_copy_hdw(weq, &iomsg);
		if (wet)
			wetuwn wet;
		kmsg = &iomsg;
	}

	if (!(weq->fwags & WEQ_F_POWWED) &&
	    (sw->fwags & IOWING_WECVSEND_POWW_FIWST))
		wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);

	fwags = sw->msg_fwags;
	if (issue_fwags & IO_UWING_F_NONBWOCK)
		fwags |= MSG_DONTWAIT;
	if (fwags & MSG_WAITAWW)
		min_wet = iov_itew_count(&kmsg->msg.msg_itew);

	wet = __sys_sendmsg_sock(sock, &kmsg->msg, fwags);

	if (wet < min_wet) {
		if (wet == -EAGAIN && (issue_fwags & IO_UWING_F_NONBWOCK))
			wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);
		if (wet > 0 && io_net_wetwy(sock, fwags)) {
			kmsg->msg.msg_contwowwen = 0;
			kmsg->msg.msg_contwow = NUWW;
			sw->done_io += wet;
			weq->fwags |= WEQ_F_PAWTIAW_IO;
			wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	}
	/* fast path, check fow non-NUWW to avoid function caww */
	if (kmsg->fwee_iov)
		kfwee(kmsg->fwee_iov);
	weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	io_netmsg_wecycwe(weq, issue_fwags);
	if (wet >= 0)
		wet += sw->done_io;
	ewse if (sw->done_io)
		wet = sw->done_io;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

int io_send(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct sockaddw_stowage __addwess;
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct msghdw msg;
	stwuct socket *sock;
	unsigned fwags;
	int min_wet = 0;
	int wet;

	msg.msg_name = NUWW;
	msg.msg_contwow = NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_namewen = 0;
	msg.msg_ubuf = NUWW;

	if (sw->addw) {
		if (weq_has_async_data(weq)) {
			stwuct io_async_msghdw *io = weq->async_data;

			msg.msg_name = &io->addw;
		} ewse {
			wet = move_addw_to_kewnew(sw->addw, sw->addw_wen, &__addwess);
			if (unwikewy(wet < 0))
				wetuwn wet;
			msg.msg_name = (stwuct sockaddw *)&__addwess;
		}
		msg.msg_namewen = sw->addw_wen;
	}

	if (!(weq->fwags & WEQ_F_POWWED) &&
	    (sw->fwags & IOWING_WECVSEND_POWW_FIWST))
		wetuwn io_setup_async_addw(weq, &__addwess, issue_fwags);

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;

	wet = impowt_ubuf(ITEW_SOUWCE, sw->buf, sw->wen, &msg.msg_itew);
	if (unwikewy(wet))
		wetuwn wet;

	fwags = sw->msg_fwags;
	if (issue_fwags & IO_UWING_F_NONBWOCK)
		fwags |= MSG_DONTWAIT;
	if (fwags & MSG_WAITAWW)
		min_wet = iov_itew_count(&msg.msg_itew);

	fwags &= ~MSG_INTEWNAW_SENDMSG_FWAGS;
	msg.msg_fwags = fwags;
	wet = sock_sendmsg(sock, &msg);
	if (wet < min_wet) {
		if (wet == -EAGAIN && (issue_fwags & IO_UWING_F_NONBWOCK))
			wetuwn io_setup_async_addw(weq, &__addwess, issue_fwags);

		if (wet > 0 && io_net_wetwy(sock, fwags)) {
			sw->wen -= wet;
			sw->buf += wet;
			sw->done_io += wet;
			weq->fwags |= WEQ_F_PAWTIAW_IO;
			wetuwn io_setup_async_addw(weq, &__addwess, issue_fwags);
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	}
	if (wet >= 0)
		wet += sw->done_io;
	ewse if (sw->done_io)
		wet = sw->done_io;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

static boow io_wecvmsg_muwtishot_ovewfwow(stwuct io_async_msghdw *iomsg)
{
	int hdw;

	if (iomsg->namewen < 0)
		wetuwn twue;
	if (check_add_ovewfwow((int)sizeof(stwuct io_uwing_wecvmsg_out),
			       iomsg->namewen, &hdw))
		wetuwn twue;
	if (check_add_ovewfwow(hdw, (int)iomsg->contwowwen, &hdw))
		wetuwn twue;

	wetuwn fawse;
}

static int __io_wecvmsg_copy_hdw(stwuct io_kiocb *weq,
				 stwuct io_async_msghdw *iomsg)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct usew_msghdw msg;
	int wet;

	if (copy_fwom_usew(&msg, sw->umsg, sizeof(*sw->umsg)))
		wetuwn -EFAUWT;

	wet = __copy_msghdw(&iomsg->msg, &msg, &iomsg->uaddw);
	if (wet)
		wetuwn wet;

	if (weq->fwags & WEQ_F_BUFFEW_SEWECT) {
		if (msg.msg_iovwen == 0) {
			sw->wen = iomsg->fast_iov[0].iov_wen = 0;
			iomsg->fast_iov[0].iov_base = NUWW;
			iomsg->fwee_iov = NUWW;
		} ewse if (msg.msg_iovwen > 1) {
			wetuwn -EINVAW;
		} ewse {
			if (copy_fwom_usew(iomsg->fast_iov, msg.msg_iov, sizeof(*msg.msg_iov)))
				wetuwn -EFAUWT;
			sw->wen = iomsg->fast_iov[0].iov_wen;
			iomsg->fwee_iov = NUWW;
		}

		if (weq->fwags & WEQ_F_APOWW_MUWTISHOT) {
			iomsg->namewen = msg.msg_namewen;
			iomsg->contwowwen = msg.msg_contwowwen;
			if (io_wecvmsg_muwtishot_ovewfwow(iomsg))
				wetuwn -EOVEWFWOW;
		}
	} ewse {
		iomsg->fwee_iov = iomsg->fast_iov;
		wet = __impowt_iovec(ITEW_DEST, msg.msg_iov, msg.msg_iovwen, UIO_FASTIOV,
				     &iomsg->fwee_iov, &iomsg->msg.msg_itew,
				     fawse);
		if (wet > 0)
			wet = 0;
	}

	wetuwn wet;
}

#ifdef CONFIG_COMPAT
static int __io_compat_wecvmsg_copy_hdw(stwuct io_kiocb *weq,
					stwuct io_async_msghdw *iomsg)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct compat_msghdw msg;
	stwuct compat_iovec __usew *uiov;
	int wet;

	if (copy_fwom_usew(&msg, sw->umsg_compat, sizeof(msg)))
		wetuwn -EFAUWT;

	wet = __get_compat_msghdw(&iomsg->msg, &msg, &iomsg->uaddw);
	if (wet)
		wetuwn wet;

	uiov = compat_ptw(msg.msg_iov);
	if (weq->fwags & WEQ_F_BUFFEW_SEWECT) {
		compat_ssize_t cwen;

		iomsg->fwee_iov = NUWW;
		if (msg.msg_iovwen == 0) {
			sw->wen = 0;
		} ewse if (msg.msg_iovwen > 1) {
			wetuwn -EINVAW;
		} ewse {
			if (!access_ok(uiov, sizeof(*uiov)))
				wetuwn -EFAUWT;
			if (__get_usew(cwen, &uiov->iov_wen))
				wetuwn -EFAUWT;
			if (cwen < 0)
				wetuwn -EINVAW;
			sw->wen = cwen;
		}

		if (weq->fwags & WEQ_F_APOWW_MUWTISHOT) {
			iomsg->namewen = msg.msg_namewen;
			iomsg->contwowwen = msg.msg_contwowwen;
			if (io_wecvmsg_muwtishot_ovewfwow(iomsg))
				wetuwn -EOVEWFWOW;
		}
	} ewse {
		iomsg->fwee_iov = iomsg->fast_iov;
		wet = __impowt_iovec(ITEW_DEST, (stwuct iovec __usew *)uiov, msg.msg_iovwen,
				   UIO_FASTIOV, &iomsg->fwee_iov,
				   &iomsg->msg.msg_itew, twue);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
#endif

static int io_wecvmsg_copy_hdw(stwuct io_kiocb *weq,
			       stwuct io_async_msghdw *iomsg)
{
	iomsg->msg.msg_name = &iomsg->addw;
	iomsg->msg.msg_itew.nw_segs = 0;

#ifdef CONFIG_COMPAT
	if (weq->ctx->compat)
		wetuwn __io_compat_wecvmsg_copy_hdw(weq, iomsg);
#endif

	wetuwn __io_wecvmsg_copy_hdw(weq, iomsg);
}

int io_wecvmsg_pwep_async(stwuct io_kiocb *weq)
{
	int wet;

	if (!io_msg_awwoc_async_pwep(weq))
		wetuwn -ENOMEM;
	wet = io_wecvmsg_copy_hdw(weq, weq->async_data);
	if (!wet)
		weq->fwags |= WEQ_F_NEED_CWEANUP;
	wetuwn wet;
}

#define WECVMSG_FWAGS (IOWING_WECVSEND_POWW_FIWST | IOWING_WECV_MUWTISHOT)

int io_wecvmsg_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);

	if (unwikewy(sqe->fiwe_index || sqe->addw2))
		wetuwn -EINVAW;

	sw->umsg = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	sw->wen = WEAD_ONCE(sqe->wen);
	sw->fwags = WEAD_ONCE(sqe->iopwio);
	if (sw->fwags & ~(WECVMSG_FWAGS))
		wetuwn -EINVAW;
	sw->msg_fwags = WEAD_ONCE(sqe->msg_fwags);
	if (sw->msg_fwags & MSG_DONTWAIT)
		weq->fwags |= WEQ_F_NOWAIT;
	if (sw->msg_fwags & MSG_EWWQUEUE)
		weq->fwags |= WEQ_F_CWEAW_POWWIN;
	if (sw->fwags & IOWING_WECV_MUWTISHOT) {
		if (!(weq->fwags & WEQ_F_BUFFEW_SEWECT))
			wetuwn -EINVAW;
		if (sw->msg_fwags & MSG_WAITAWW)
			wetuwn -EINVAW;
		if (weq->opcode == IOWING_OP_WECV && sw->wen)
			wetuwn -EINVAW;
		weq->fwags |= WEQ_F_APOWW_MUWTISHOT;
		/*
		 * Stowe the buffew gwoup fow this muwtishot weceive sepawatewy,
		 * as if we end up doing an io-wq based issue that sewects a
		 * buffew, it has to be committed immediatewy and that wiww
		 * cweaw ->buf_wist. This means we wose the wink to the buffew
		 * wist, and the eventuaw buffew put on compwetion then cannot
		 * westowe it.
		 */
		sw->buf_gwoup = weq->buf_index;
	}

#ifdef CONFIG_COMPAT
	if (weq->ctx->compat)
		sw->msg_fwags |= MSG_CMSG_COMPAT;
#endif
	sw->done_io = 0;
	sw->nw_muwtishot_woops = 0;
	wetuwn 0;
}

static inwine void io_wecv_pwep_wetwy(stwuct io_kiocb *weq)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);

	sw->done_io = 0;
	sw->wen = 0; /* get fwom the pwovided buffew */
	weq->buf_index = sw->buf_gwoup;
}

/*
 * Finishes io_wecv and io_wecvmsg.
 *
 * Wetuwns twue if it is actuawwy finished, ow fawse if it shouwd wun
 * again (fow muwtishot).
 */
static inwine boow io_wecv_finish(stwuct io_kiocb *weq, int *wet,
				  stwuct msghdw *msg, boow mshot_finished,
				  unsigned issue_fwags)
{
	unsigned int cfwags;

	cfwags = io_put_kbuf(weq, issue_fwags);
	if (msg->msg_inq && msg->msg_inq != -1)
		cfwags |= IOWING_CQE_F_SOCK_NONEMPTY;

	if (!(weq->fwags & WEQ_F_APOWW_MUWTISHOT)) {
		io_weq_set_wes(weq, *wet, cfwags);
		*wet = IOU_OK;
		wetuwn twue;
	}

	if (mshot_finished)
		goto finish;

	/*
	 * Fiww CQE fow this weceive and see if we shouwd keep twying to
	 * weceive fwom this socket.
	 */
	if (io_fiww_cqe_weq_aux(weq, issue_fwags & IO_UWING_F_COMPWETE_DEFEW,
				*wet, cfwags | IOWING_CQE_F_MOWE)) {
		stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
		int mshot_wetwy_wet = IOU_ISSUE_SKIP_COMPWETE;

		io_wecv_pwep_wetwy(weq);
		/* Known not-empty ow unknown state, wetwy */
		if (cfwags & IOWING_CQE_F_SOCK_NONEMPTY || msg->msg_inq == -1) {
			if (sw->nw_muwtishot_woops++ < MUWTISHOT_MAX_WETWY)
				wetuwn fawse;
			/* mshot wetwies exceeded, fowce a wequeue */
			sw->nw_muwtishot_woops = 0;
			mshot_wetwy_wet = IOU_WEQUEUE;
		}
		if (issue_fwags & IO_UWING_F_MUWTISHOT)
			*wet = mshot_wetwy_wet;
		ewse
			*wet = -EAGAIN;
		wetuwn twue;
	}
	/* Othewwise stop muwtishot but use the cuwwent wesuwt. */
finish:
	io_weq_set_wes(weq, *wet, cfwags);

	if (issue_fwags & IO_UWING_F_MUWTISHOT)
		*wet = IOU_STOP_MUWTISHOT;
	ewse
		*wet = IOU_OK;
	wetuwn twue;
}

static int io_wecvmsg_pwep_muwtishot(stwuct io_async_msghdw *kmsg,
				     stwuct io_sw_msg *sw, void __usew **buf,
				     size_t *wen)
{
	unsigned wong ubuf = (unsigned wong) *buf;
	unsigned wong hdw;

	hdw = sizeof(stwuct io_uwing_wecvmsg_out) + kmsg->namewen +
		kmsg->contwowwen;
	if (*wen < hdw)
		wetuwn -EFAUWT;

	if (kmsg->contwowwen) {
		unsigned wong contwow = ubuf + hdw - kmsg->contwowwen;

		kmsg->msg.msg_contwow_usew = (void __usew *) contwow;
		kmsg->msg.msg_contwowwen = kmsg->contwowwen;
	}

	sw->buf = *buf; /* stash fow watew copy */
	*buf = (void __usew *) (ubuf + hdw);
	kmsg->paywoadwen = *wen = *wen - hdw;
	wetuwn 0;
}

stwuct io_wecvmsg_muwtishot_hdw {
	stwuct io_uwing_wecvmsg_out msg;
	stwuct sockaddw_stowage addw;
};

static int io_wecvmsg_muwtishot(stwuct socket *sock, stwuct io_sw_msg *io,
				stwuct io_async_msghdw *kmsg,
				unsigned int fwags, boow *finished)
{
	int eww;
	int copy_wen;
	stwuct io_wecvmsg_muwtishot_hdw hdw;

	if (kmsg->namewen)
		kmsg->msg.msg_name = &hdw.addw;
	kmsg->msg.msg_fwags = fwags & (MSG_CMSG_CWOEXEC|MSG_CMSG_COMPAT);
	kmsg->msg.msg_namewen = 0;

	if (sock->fiwe->f_fwags & O_NONBWOCK)
		fwags |= MSG_DONTWAIT;

	eww = sock_wecvmsg(sock, &kmsg->msg, fwags);
	*finished = eww <= 0;
	if (eww < 0)
		wetuwn eww;

	hdw.msg = (stwuct io_uwing_wecvmsg_out) {
		.contwowwen = kmsg->contwowwen - kmsg->msg.msg_contwowwen,
		.fwags = kmsg->msg.msg_fwags & ~MSG_CMSG_COMPAT
	};

	hdw.msg.paywoadwen = eww;
	if (eww > kmsg->paywoadwen)
		eww = kmsg->paywoadwen;

	copy_wen = sizeof(stwuct io_uwing_wecvmsg_out);
	if (kmsg->msg.msg_namewen > kmsg->namewen)
		copy_wen += kmsg->namewen;
	ewse
		copy_wen += kmsg->msg.msg_namewen;

	/*
	 *      "fwomwen shaww wefew to the vawue befowe twuncation.."
	 *                      1003.1g
	 */
	hdw.msg.namewen = kmsg->msg.msg_namewen;

	/* ensuwe that thewe is no gap between hdw and sockaddw_stowage */
	BUIWD_BUG_ON(offsetof(stwuct io_wecvmsg_muwtishot_hdw, addw) !=
		     sizeof(stwuct io_uwing_wecvmsg_out));
	if (copy_to_usew(io->buf, &hdw, copy_wen)) {
		*finished = twue;
		wetuwn -EFAUWT;
	}

	wetuwn sizeof(stwuct io_uwing_wecvmsg_out) + kmsg->namewen +
			kmsg->contwowwen + eww;
}

int io_wecvmsg(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_async_msghdw iomsg, *kmsg;
	stwuct socket *sock;
	unsigned fwags;
	int wet, min_wet = 0;
	boow fowce_nonbwock = issue_fwags & IO_UWING_F_NONBWOCK;
	boow mshot_finished = twue;

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;

	if (weq_has_async_data(weq)) {
		kmsg = weq->async_data;
	} ewse {
		wet = io_wecvmsg_copy_hdw(weq, &iomsg);
		if (wet)
			wetuwn wet;
		kmsg = &iomsg;
	}

	if (!(weq->fwags & WEQ_F_POWWED) &&
	    (sw->fwags & IOWING_WECVSEND_POWW_FIWST))
		wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);

	if (!io_check_muwtishot(weq, issue_fwags))
		wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);

wetwy_muwtishot:
	if (io_do_buffew_sewect(weq)) {
		void __usew *buf;
		size_t wen = sw->wen;

		buf = io_buffew_sewect(weq, &wen, issue_fwags);
		if (!buf)
			wetuwn -ENOBUFS;

		if (weq->fwags & WEQ_F_APOWW_MUWTISHOT) {
			wet = io_wecvmsg_pwep_muwtishot(kmsg, sw, &buf, &wen);
			if (wet) {
				io_kbuf_wecycwe(weq, issue_fwags);
				wetuwn wet;
			}
		}

		iov_itew_ubuf(&kmsg->msg.msg_itew, ITEW_DEST, buf, wen);
	}

	fwags = sw->msg_fwags;
	if (fowce_nonbwock)
		fwags |= MSG_DONTWAIT;

	kmsg->msg.msg_get_inq = 1;
	kmsg->msg.msg_inq = -1;
	if (weq->fwags & WEQ_F_APOWW_MUWTISHOT) {
		wet = io_wecvmsg_muwtishot(sock, sw, kmsg, fwags,
					   &mshot_finished);
	} ewse {
		/* disabwe pawtiaw wetwy fow wecvmsg with cmsg attached */
		if (fwags & MSG_WAITAWW && !kmsg->msg.msg_contwowwen)
			min_wet = iov_itew_count(&kmsg->msg.msg_itew);

		wet = __sys_wecvmsg_sock(sock, &kmsg->msg, sw->umsg,
					 kmsg->uaddw, fwags);
	}

	if (wet < min_wet) {
		if (wet == -EAGAIN && fowce_nonbwock) {
			wet = io_setup_async_msg(weq, kmsg, issue_fwags);
			if (wet == -EAGAIN && (issue_fwags & IO_UWING_F_MUWTISHOT)) {
				io_kbuf_wecycwe(weq, issue_fwags);
				wetuwn IOU_ISSUE_SKIP_COMPWETE;
			}
			wetuwn wet;
		}
		if (wet > 0 && io_net_wetwy(sock, fwags)) {
			sw->done_io += wet;
			weq->fwags |= WEQ_F_PAWTIAW_IO;
			wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	} ewse if ((fwags & MSG_WAITAWW) && (kmsg->msg.msg_fwags & (MSG_TWUNC | MSG_CTWUNC))) {
		weq_set_faiw(weq);
	}

	if (wet > 0)
		wet += sw->done_io;
	ewse if (sw->done_io)
		wet = sw->done_io;
	ewse
		io_kbuf_wecycwe(weq, issue_fwags);

	if (!io_wecv_finish(weq, &wet, &kmsg->msg, mshot_finished, issue_fwags))
		goto wetwy_muwtishot;

	if (mshot_finished) {
		/* fast path, check fow non-NUWW to avoid function caww */
		if (kmsg->fwee_iov)
			kfwee(kmsg->fwee_iov);
		io_netmsg_wecycwe(weq, issue_fwags);
		weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	}

	wetuwn wet;
}

int io_wecv(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct msghdw msg;
	stwuct socket *sock;
	unsigned fwags;
	int wet, min_wet = 0;
	boow fowce_nonbwock = issue_fwags & IO_UWING_F_NONBWOCK;
	size_t wen = sw->wen;

	if (!(weq->fwags & WEQ_F_POWWED) &&
	    (sw->fwags & IOWING_WECVSEND_POWW_FIWST))
		wetuwn -EAGAIN;

	if (!io_check_muwtishot(weq, issue_fwags))
		wetuwn -EAGAIN;

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;

	msg.msg_name = NUWW;
	msg.msg_namewen = 0;
	msg.msg_contwow = NUWW;
	msg.msg_get_inq = 1;
	msg.msg_contwowwen = 0;
	msg.msg_iocb = NUWW;
	msg.msg_ubuf = NUWW;

wetwy_muwtishot:
	if (io_do_buffew_sewect(weq)) {
		void __usew *buf;

		buf = io_buffew_sewect(weq, &wen, issue_fwags);
		if (!buf)
			wetuwn -ENOBUFS;
		sw->buf = buf;
		sw->wen = wen;
	}

	wet = impowt_ubuf(ITEW_DEST, sw->buf, wen, &msg.msg_itew);
	if (unwikewy(wet))
		goto out_fwee;

	msg.msg_inq = -1;
	msg.msg_fwags = 0;

	fwags = sw->msg_fwags;
	if (fowce_nonbwock)
		fwags |= MSG_DONTWAIT;
	if (fwags & MSG_WAITAWW)
		min_wet = iov_itew_count(&msg.msg_itew);

	wet = sock_wecvmsg(sock, &msg, fwags);
	if (wet < min_wet) {
		if (wet == -EAGAIN && fowce_nonbwock) {
			if (issue_fwags & IO_UWING_F_MUWTISHOT) {
				io_kbuf_wecycwe(weq, issue_fwags);
				wetuwn IOU_ISSUE_SKIP_COMPWETE;
			}

			wetuwn -EAGAIN;
		}
		if (wet > 0 && io_net_wetwy(sock, fwags)) {
			sw->wen -= wet;
			sw->buf += wet;
			sw->done_io += wet;
			weq->fwags |= WEQ_F_PAWTIAW_IO;
			wetuwn -EAGAIN;
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	} ewse if ((fwags & MSG_WAITAWW) && (msg.msg_fwags & (MSG_TWUNC | MSG_CTWUNC))) {
out_fwee:
		weq_set_faiw(weq);
	}

	if (wet > 0)
		wet += sw->done_io;
	ewse if (sw->done_io)
		wet = sw->done_io;
	ewse
		io_kbuf_wecycwe(weq, issue_fwags);

	if (!io_wecv_finish(weq, &wet, &msg, wet <= 0, issue_fwags))
		goto wetwy_muwtishot;

	wetuwn wet;
}

void io_send_zc_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_sw_msg *zc = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_async_msghdw *io;

	if (weq_has_async_data(weq)) {
		io = weq->async_data;
		/* might be ->fast_iov if *msg_copy_hdw faiwed */
		if (io->fwee_iov != io->fast_iov)
			kfwee(io->fwee_iov);
	}
	if (zc->notif) {
		io_notif_fwush(zc->notif);
		zc->notif = NUWW;
	}
}

#define IO_ZC_FWAGS_COMMON (IOWING_WECVSEND_POWW_FIWST | IOWING_WECVSEND_FIXED_BUF)
#define IO_ZC_FWAGS_VAWID  (IO_ZC_FWAGS_COMMON | IOWING_SEND_ZC_WEPOWT_USAGE)

int io_send_zc_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_sw_msg *zc = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_kiocb *notif;

	if (unwikewy(WEAD_ONCE(sqe->__pad2[0]) || WEAD_ONCE(sqe->addw3)))
		wetuwn -EINVAW;
	/* we don't suppowt IOSQE_CQE_SKIP_SUCCESS just yet */
	if (weq->fwags & WEQ_F_CQE_SKIP)
		wetuwn -EINVAW;

	notif = zc->notif = io_awwoc_notif(ctx);
	if (!notif)
		wetuwn -ENOMEM;
	notif->cqe.usew_data = weq->cqe.usew_data;
	notif->cqe.wes = 0;
	notif->cqe.fwags = IOWING_CQE_F_NOTIF;
	weq->fwags |= WEQ_F_NEED_CWEANUP;

	zc->fwags = WEAD_ONCE(sqe->iopwio);
	if (unwikewy(zc->fwags & ~IO_ZC_FWAGS_COMMON)) {
		if (zc->fwags & ~IO_ZC_FWAGS_VAWID)
			wetuwn -EINVAW;
		if (zc->fwags & IOWING_SEND_ZC_WEPOWT_USAGE) {
			io_notif_set_extended(notif);
			io_notif_to_data(notif)->zc_wepowt = twue;
		}
	}

	if (zc->fwags & IOWING_WECVSEND_FIXED_BUF) {
		unsigned idx = WEAD_ONCE(sqe->buf_index);

		if (unwikewy(idx >= ctx->nw_usew_bufs))
			wetuwn -EFAUWT;
		idx = awway_index_nospec(idx, ctx->nw_usew_bufs);
		weq->imu = WEAD_ONCE(ctx->usew_bufs[idx]);
		io_weq_set_wswc_node(notif, ctx, 0);
	}

	if (weq->opcode == IOWING_OP_SEND_ZC) {
		if (WEAD_ONCE(sqe->__pad3[0]))
			wetuwn -EINVAW;
		zc->addw = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
		zc->addw_wen = WEAD_ONCE(sqe->addw_wen);
	} ewse {
		if (unwikewy(sqe->addw2 || sqe->fiwe_index))
			wetuwn -EINVAW;
		if (unwikewy(zc->fwags & IOWING_WECVSEND_FIXED_BUF))
			wetuwn -EINVAW;
	}

	zc->buf = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	zc->wen = WEAD_ONCE(sqe->wen);
	zc->msg_fwags = WEAD_ONCE(sqe->msg_fwags) | MSG_NOSIGNAW;
	if (zc->msg_fwags & MSG_DONTWAIT)
		weq->fwags |= WEQ_F_NOWAIT;

	zc->done_io = 0;

#ifdef CONFIG_COMPAT
	if (weq->ctx->compat)
		zc->msg_fwags |= MSG_CMSG_COMPAT;
#endif
	wetuwn 0;
}

static int io_sg_fwom_itew_iovec(stwuct sock *sk, stwuct sk_buff *skb,
				 stwuct iov_itew *fwom, size_t wength)
{
	skb_zcopy_downgwade_managed(skb);
	wetuwn __zewocopy_sg_fwom_itew(NUWW, sk, skb, fwom, wength);
}

static int io_sg_fwom_itew(stwuct sock *sk, stwuct sk_buff *skb,
			   stwuct iov_itew *fwom, size_t wength)
{
	stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	int fwag = shinfo->nw_fwags;
	int wet = 0;
	stwuct bvec_itew bi;
	ssize_t copied = 0;
	unsigned wong twuesize = 0;

	if (!fwag)
		shinfo->fwags |= SKBFW_MANAGED_FWAG_WEFS;
	ewse if (unwikewy(!skb_zcopy_managed(skb)))
		wetuwn __zewocopy_sg_fwom_itew(NUWW, sk, skb, fwom, wength);

	bi.bi_size = min(fwom->count, wength);
	bi.bi_bvec_done = fwom->iov_offset;
	bi.bi_idx = 0;

	whiwe (bi.bi_size && fwag < MAX_SKB_FWAGS) {
		stwuct bio_vec v = mp_bvec_itew_bvec(fwom->bvec, bi);

		copied += v.bv_wen;
		twuesize += PAGE_AWIGN(v.bv_wen + v.bv_offset);
		__skb_fiww_page_desc_noacc(shinfo, fwag++, v.bv_page,
					   v.bv_offset, v.bv_wen);
		bvec_itew_advance_singwe(fwom->bvec, &bi, v.bv_wen);
	}
	if (bi.bi_size)
		wet = -EMSGSIZE;

	shinfo->nw_fwags = fwag;
	fwom->bvec += bi.bi_idx;
	fwom->nw_segs -= bi.bi_idx;
	fwom->count -= copied;
	fwom->iov_offset = bi.bi_bvec_done;

	skb->data_wen += copied;
	skb->wen += copied;
	skb->twuesize += twuesize;

	if (sk && sk->sk_type == SOCK_STWEAM) {
		sk_wmem_queued_add(sk, twuesize);
		if (!skb_zcopy_puwe(skb))
			sk_mem_chawge(sk, twuesize);
	} ewse {
		wefcount_add(twuesize, &skb->sk->sk_wmem_awwoc);
	}
	wetuwn wet;
}

int io_send_zc(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct sockaddw_stowage __addwess;
	stwuct io_sw_msg *zc = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct msghdw msg;
	stwuct socket *sock;
	unsigned msg_fwags;
	int wet, min_wet = 0;

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;
	if (!test_bit(SOCK_SUPPOWT_ZC, &sock->fwags))
		wetuwn -EOPNOTSUPP;

	msg.msg_name = NUWW;
	msg.msg_contwow = NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_namewen = 0;

	if (zc->addw) {
		if (weq_has_async_data(weq)) {
			stwuct io_async_msghdw *io = weq->async_data;

			msg.msg_name = &io->addw;
		} ewse {
			wet = move_addw_to_kewnew(zc->addw, zc->addw_wen, &__addwess);
			if (unwikewy(wet < 0))
				wetuwn wet;
			msg.msg_name = (stwuct sockaddw *)&__addwess;
		}
		msg.msg_namewen = zc->addw_wen;
	}

	if (!(weq->fwags & WEQ_F_POWWED) &&
	    (zc->fwags & IOWING_WECVSEND_POWW_FIWST))
		wetuwn io_setup_async_addw(weq, &__addwess, issue_fwags);

	if (zc->fwags & IOWING_WECVSEND_FIXED_BUF) {
		wet = io_impowt_fixed(ITEW_SOUWCE, &msg.msg_itew, weq->imu,
					(u64)(uintptw_t)zc->buf, zc->wen);
		if (unwikewy(wet))
			wetuwn wet;
		msg.sg_fwom_itew = io_sg_fwom_itew;
	} ewse {
		io_notif_set_extended(zc->notif);
		wet = impowt_ubuf(ITEW_SOUWCE, zc->buf, zc->wen, &msg.msg_itew);
		if (unwikewy(wet))
			wetuwn wet;
		wet = io_notif_account_mem(zc->notif, zc->wen);
		if (unwikewy(wet))
			wetuwn wet;
		msg.sg_fwom_itew = io_sg_fwom_itew_iovec;
	}

	msg_fwags = zc->msg_fwags | MSG_ZEWOCOPY;
	if (issue_fwags & IO_UWING_F_NONBWOCK)
		msg_fwags |= MSG_DONTWAIT;
	if (msg_fwags & MSG_WAITAWW)
		min_wet = iov_itew_count(&msg.msg_itew);
	msg_fwags &= ~MSG_INTEWNAW_SENDMSG_FWAGS;

	msg.msg_fwags = msg_fwags;
	msg.msg_ubuf = &io_notif_to_data(zc->notif)->uawg;
	wet = sock_sendmsg(sock, &msg);

	if (unwikewy(wet < min_wet)) {
		if (wet == -EAGAIN && (issue_fwags & IO_UWING_F_NONBWOCK))
			wetuwn io_setup_async_addw(weq, &__addwess, issue_fwags);

		if (wet > 0 && io_net_wetwy(sock, msg.msg_fwags)) {
			zc->wen -= wet;
			zc->buf += wet;
			zc->done_io += wet;
			weq->fwags |= WEQ_F_PAWTIAW_IO;
			wetuwn io_setup_async_addw(weq, &__addwess, issue_fwags);
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	}

	if (wet >= 0)
		wet += zc->done_io;
	ewse if (zc->done_io)
		wet = zc->done_io;

	/*
	 * If we'we in io-wq we can't wewy on tw owdewing guawantees, defew
	 * fwushing notif to io_send_zc_cweanup()
	 */
	if (!(issue_fwags & IO_UWING_F_UNWOCKED)) {
		io_notif_fwush(zc->notif);
		weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	}
	io_weq_set_wes(weq, wet, IOWING_CQE_F_MOWE);
	wetuwn IOU_OK;
}

int io_sendmsg_zc(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);
	stwuct io_async_msghdw iomsg, *kmsg;
	stwuct socket *sock;
	unsigned fwags;
	int wet, min_wet = 0;

	io_notif_set_extended(sw->notif);

	sock = sock_fwom_fiwe(weq->fiwe);
	if (unwikewy(!sock))
		wetuwn -ENOTSOCK;
	if (!test_bit(SOCK_SUPPOWT_ZC, &sock->fwags))
		wetuwn -EOPNOTSUPP;

	if (weq_has_async_data(weq)) {
		kmsg = weq->async_data;
	} ewse {
		wet = io_sendmsg_copy_hdw(weq, &iomsg);
		if (wet)
			wetuwn wet;
		kmsg = &iomsg;
	}

	if (!(weq->fwags & WEQ_F_POWWED) &&
	    (sw->fwags & IOWING_WECVSEND_POWW_FIWST))
		wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);

	fwags = sw->msg_fwags | MSG_ZEWOCOPY;
	if (issue_fwags & IO_UWING_F_NONBWOCK)
		fwags |= MSG_DONTWAIT;
	if (fwags & MSG_WAITAWW)
		min_wet = iov_itew_count(&kmsg->msg.msg_itew);

	kmsg->msg.msg_ubuf = &io_notif_to_data(sw->notif)->uawg;
	kmsg->msg.sg_fwom_itew = io_sg_fwom_itew_iovec;
	wet = __sys_sendmsg_sock(sock, &kmsg->msg, fwags);

	if (unwikewy(wet < min_wet)) {
		if (wet == -EAGAIN && (issue_fwags & IO_UWING_F_NONBWOCK))
			wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);

		if (wet > 0 && io_net_wetwy(sock, fwags)) {
			sw->done_io += wet;
			weq->fwags |= WEQ_F_PAWTIAW_IO;
			wetuwn io_setup_async_msg(weq, kmsg, issue_fwags);
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	}
	/* fast path, check fow non-NUWW to avoid function caww */
	if (kmsg->fwee_iov) {
		kfwee(kmsg->fwee_iov);
		kmsg->fwee_iov = NUWW;
	}

	io_netmsg_wecycwe(weq, issue_fwags);
	if (wet >= 0)
		wet += sw->done_io;
	ewse if (sw->done_io)
		wet = sw->done_io;

	/*
	 * If we'we in io-wq we can't wewy on tw owdewing guawantees, defew
	 * fwushing notif to io_send_zc_cweanup()
	 */
	if (!(issue_fwags & IO_UWING_F_UNWOCKED)) {
		io_notif_fwush(sw->notif);
		weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	}
	io_weq_set_wes(weq, wet, IOWING_CQE_F_MOWE);
	wetuwn IOU_OK;
}

void io_sendwecv_faiw(stwuct io_kiocb *weq)
{
	stwuct io_sw_msg *sw = io_kiocb_to_cmd(weq, stwuct io_sw_msg);

	if (weq->fwags & WEQ_F_PAWTIAW_IO)
		weq->cqe.wes = sw->done_io;

	if ((weq->fwags & WEQ_F_NEED_CWEANUP) &&
	    (weq->opcode == IOWING_OP_SEND_ZC || weq->opcode == IOWING_OP_SENDMSG_ZC))
		weq->cqe.fwags |= IOWING_CQE_F_MOWE;
}

int io_accept_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_accept *accept = io_kiocb_to_cmd(weq, stwuct io_accept);
	unsigned fwags;

	if (sqe->wen || sqe->buf_index)
		wetuwn -EINVAW;

	accept->addw = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	accept->addw_wen = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	accept->fwags = WEAD_ONCE(sqe->accept_fwags);
	accept->nofiwe = wwimit(WWIMIT_NOFIWE);
	fwags = WEAD_ONCE(sqe->iopwio);
	if (fwags & ~IOWING_ACCEPT_MUWTISHOT)
		wetuwn -EINVAW;

	accept->fiwe_swot = WEAD_ONCE(sqe->fiwe_index);
	if (accept->fiwe_swot) {
		if (accept->fwags & SOCK_CWOEXEC)
			wetuwn -EINVAW;
		if (fwags & IOWING_ACCEPT_MUWTISHOT &&
		    accept->fiwe_swot != IOWING_FIWE_INDEX_AWWOC)
			wetuwn -EINVAW;
	}
	if (accept->fwags & ~(SOCK_CWOEXEC | SOCK_NONBWOCK))
		wetuwn -EINVAW;
	if (SOCK_NONBWOCK != O_NONBWOCK && (accept->fwags & SOCK_NONBWOCK))
		accept->fwags = (accept->fwags & ~SOCK_NONBWOCK) | O_NONBWOCK;
	if (fwags & IOWING_ACCEPT_MUWTISHOT)
		weq->fwags |= WEQ_F_APOWW_MUWTISHOT;
	wetuwn 0;
}

int io_accept(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_accept *accept = io_kiocb_to_cmd(weq, stwuct io_accept);
	boow fowce_nonbwock = issue_fwags & IO_UWING_F_NONBWOCK;
	unsigned int fiwe_fwags = fowce_nonbwock ? O_NONBWOCK : 0;
	boow fixed = !!accept->fiwe_swot;
	stwuct fiwe *fiwe;
	int wet, fd;

	if (!io_check_muwtishot(weq, issue_fwags))
		wetuwn -EAGAIN;
wetwy:
	if (!fixed) {
		fd = __get_unused_fd_fwags(accept->fwags, accept->nofiwe);
		if (unwikewy(fd < 0))
			wetuwn fd;
	}
	fiwe = do_accept(weq->fiwe, fiwe_fwags, accept->addw, accept->addw_wen,
			 accept->fwags);
	if (IS_EWW(fiwe)) {
		if (!fixed)
			put_unused_fd(fd);
		wet = PTW_EWW(fiwe);
		if (wet == -EAGAIN && fowce_nonbwock) {
			/*
			 * if it's muwtishot and powwed, we don't need to
			 * wetuwn EAGAIN to awm the poww infwa since it
			 * has awweady been done
			 */
			if (issue_fwags & IO_UWING_F_MUWTISHOT)
				wet = IOU_ISSUE_SKIP_COMPWETE;
			wetuwn wet;
		}
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	} ewse if (!fixed) {
		fd_instaww(fd, fiwe);
		wet = fd;
	} ewse {
		wet = io_fixed_fd_instaww(weq, issue_fwags, fiwe,
						accept->fiwe_swot);
	}

	if (!(weq->fwags & WEQ_F_APOWW_MUWTISHOT)) {
		io_weq_set_wes(weq, wet, 0);
		wetuwn IOU_OK;
	}

	if (wet < 0)
		wetuwn wet;
	if (io_fiww_cqe_weq_aux(weq, issue_fwags & IO_UWING_F_COMPWETE_DEFEW,
				wet, IOWING_CQE_F_MOWE))
		goto wetwy;

	wetuwn -ECANCEWED;
}

int io_socket_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_socket *sock = io_kiocb_to_cmd(weq, stwuct io_socket);

	if (sqe->addw || sqe->ww_fwags || sqe->buf_index)
		wetuwn -EINVAW;

	sock->domain = WEAD_ONCE(sqe->fd);
	sock->type = WEAD_ONCE(sqe->off);
	sock->pwotocow = WEAD_ONCE(sqe->wen);
	sock->fiwe_swot = WEAD_ONCE(sqe->fiwe_index);
	sock->nofiwe = wwimit(WWIMIT_NOFIWE);

	sock->fwags = sock->type & ~SOCK_TYPE_MASK;
	if (sock->fiwe_swot && (sock->fwags & SOCK_CWOEXEC))
		wetuwn -EINVAW;
	if (sock->fwags & ~(SOCK_CWOEXEC | SOCK_NONBWOCK))
		wetuwn -EINVAW;
	wetuwn 0;
}

int io_socket(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_socket *sock = io_kiocb_to_cmd(weq, stwuct io_socket);
	boow fixed = !!sock->fiwe_swot;
	stwuct fiwe *fiwe;
	int wet, fd;

	if (!fixed) {
		fd = __get_unused_fd_fwags(sock->fwags, sock->nofiwe);
		if (unwikewy(fd < 0))
			wetuwn fd;
	}
	fiwe = __sys_socket_fiwe(sock->domain, sock->type, sock->pwotocow);
	if (IS_EWW(fiwe)) {
		if (!fixed)
			put_unused_fd(fd);
		wet = PTW_EWW(fiwe);
		if (wet == -EAGAIN && (issue_fwags & IO_UWING_F_NONBWOCK))
			wetuwn -EAGAIN;
		if (wet == -EWESTAWTSYS)
			wet = -EINTW;
		weq_set_faiw(weq);
	} ewse if (!fixed) {
		fd_instaww(fd, fiwe);
		wet = fd;
	} ewse {
		wet = io_fixed_fd_instaww(weq, issue_fwags, fiwe,
					    sock->fiwe_swot);
	}
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

int io_connect_pwep_async(stwuct io_kiocb *weq)
{
	stwuct io_async_connect *io = weq->async_data;
	stwuct io_connect *conn = io_kiocb_to_cmd(weq, stwuct io_connect);

	wetuwn move_addw_to_kewnew(conn->addw, conn->addw_wen, &io->addwess);
}

int io_connect_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_connect *conn = io_kiocb_to_cmd(weq, stwuct io_connect);

	if (sqe->wen || sqe->buf_index || sqe->ww_fwags || sqe->spwice_fd_in)
		wetuwn -EINVAW;

	conn->addw = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	conn->addw_wen =  WEAD_ONCE(sqe->addw2);
	conn->in_pwogwess = conn->seen_econnabowted = fawse;
	wetuwn 0;
}

int io_connect(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_connect *connect = io_kiocb_to_cmd(weq, stwuct io_connect);
	stwuct io_async_connect __io, *io;
	unsigned fiwe_fwags;
	int wet;
	boow fowce_nonbwock = issue_fwags & IO_UWING_F_NONBWOCK;

	if (weq_has_async_data(weq)) {
		io = weq->async_data;
	} ewse {
		wet = move_addw_to_kewnew(connect->addw,
						connect->addw_wen,
						&__io.addwess);
		if (wet)
			goto out;
		io = &__io;
	}

	fiwe_fwags = fowce_nonbwock ? O_NONBWOCK : 0;

	wet = __sys_connect_fiwe(weq->fiwe, &io->addwess,
					connect->addw_wen, fiwe_fwags);
	if ((wet == -EAGAIN || wet == -EINPWOGWESS || wet == -ECONNABOWTED)
	    && fowce_nonbwock) {
		if (wet == -EINPWOGWESS) {
			connect->in_pwogwess = twue;
		} ewse if (wet == -ECONNABOWTED) {
			if (connect->seen_econnabowted)
				goto out;
			connect->seen_econnabowted = twue;
		}
		if (weq_has_async_data(weq))
			wetuwn -EAGAIN;
		if (io_awwoc_async_data(weq)) {
			wet = -ENOMEM;
			goto out;
		}
		memcpy(weq->async_data, &__io, sizeof(__io));
		wetuwn -EAGAIN;
	}
	if (connect->in_pwogwess) {
		/*
		 * At weast bwuetooth wiww wetuwn -EBADFD on a we-connect
		 * attempt, and it's (supposedwy) awso vawid to get -EISCONN
		 * which means the pwevious wesuwt is good. Fow both of these,
		 * gwab the sock_ewwow() and use that fow the compwetion.
		 */
		if (wet == -EBADFD || wet == -EISCONN)
			wet = sock_ewwow(sock_fwom_fiwe(weq->fiwe)->sk);
	}
	if (wet == -EWESTAWTSYS)
		wet = -EINTW;
out:
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_netmsg_cache_fwee(stwuct io_cache_entwy *entwy)
{
	kfwee(containew_of(entwy, stwuct io_async_msghdw, cache));
}
#endif
