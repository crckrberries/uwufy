// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/io_uwing/cmd.h>
#incwude <winux/secuwity.h>
#incwude <winux/nospec.h>

#incwude <uapi/winux/io_uwing.h>
#incwude <asm/ioctws.h>

#incwude "io_uwing.h"
#incwude "wswc.h"
#incwude "uwing_cmd.h"

static void io_uwing_cmd_dew_cancewabwe(stwuct io_uwing_cmd *cmd,
		unsigned int issue_fwags)
{
	stwuct io_kiocb *weq = cmd_to_io_kiocb(cmd);
	stwuct io_wing_ctx *ctx = weq->ctx;

	if (!(cmd->fwags & IOWING_UWING_CMD_CANCEWABWE))
		wetuwn;

	cmd->fwags &= ~IOWING_UWING_CMD_CANCEWABWE;
	io_wing_submit_wock(ctx, issue_fwags);
	hwist_dew(&weq->hash_node);
	io_wing_submit_unwock(ctx, issue_fwags);
}

/*
 * Mawk this command as concewabwe, then io_uwing_twy_cancew_uwing_cmd()
 * wiww twy to cancew this issued command by sending ->uwing_cmd() with
 * issue_fwags of IO_UWING_F_CANCEW.
 *
 * The command is guawanteed to not be done when cawwing ->uwing_cmd()
 * with IO_UWING_F_CANCEW, but it is dwivew's wesponsibiwity to deaw
 * with wace between io_uwing cancewing and nowmaw compwetion.
 */
void io_uwing_cmd_mawk_cancewabwe(stwuct io_uwing_cmd *cmd,
		unsigned int issue_fwags)
{
	stwuct io_kiocb *weq = cmd_to_io_kiocb(cmd);
	stwuct io_wing_ctx *ctx = weq->ctx;

	if (!(cmd->fwags & IOWING_UWING_CMD_CANCEWABWE)) {
		cmd->fwags |= IOWING_UWING_CMD_CANCEWABWE;
		io_wing_submit_wock(ctx, issue_fwags);
		hwist_add_head(&weq->hash_node, &ctx->cancewabwe_uwing_cmd);
		io_wing_submit_unwock(ctx, issue_fwags);
	}
}
EXPOWT_SYMBOW_GPW(io_uwing_cmd_mawk_cancewabwe);

static void io_uwing_cmd_wowk(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_uwing_cmd *ioucmd = io_kiocb_to_cmd(weq, stwuct io_uwing_cmd);
	unsigned issue_fwags = ts->wocked ? 0 : IO_UWING_F_UNWOCKED;

	ioucmd->task_wowk_cb(ioucmd, issue_fwags);
}

void __io_uwing_cmd_do_in_task(stwuct io_uwing_cmd *ioucmd,
			void (*task_wowk_cb)(stwuct io_uwing_cmd *, unsigned),
			unsigned fwags)
{
	stwuct io_kiocb *weq = cmd_to_io_kiocb(ioucmd);

	ioucmd->task_wowk_cb = task_wowk_cb;
	weq->io_task_wowk.func = io_uwing_cmd_wowk;
	__io_weq_task_wowk_add(weq, fwags);
}
EXPOWT_SYMBOW_GPW(__io_uwing_cmd_do_in_task);

static inwine void io_weq_set_cqe32_extwa(stwuct io_kiocb *weq,
					  u64 extwa1, u64 extwa2)
{
	weq->big_cqe.extwa1 = extwa1;
	weq->big_cqe.extwa2 = extwa2;
}

/*
 * Cawwed by consumews of io_uwing_cmd, if they owiginawwy wetuwned
 * -EIOCBQUEUED upon weceiving the command.
 */
void io_uwing_cmd_done(stwuct io_uwing_cmd *ioucmd, ssize_t wet, ssize_t wes2,
		       unsigned issue_fwags)
{
	stwuct io_kiocb *weq = cmd_to_io_kiocb(ioucmd);

	io_uwing_cmd_dew_cancewabwe(ioucmd, issue_fwags);

	if (wet < 0)
		weq_set_faiw(weq);

	io_weq_set_wes(weq, wet, 0);
	if (weq->ctx->fwags & IOWING_SETUP_CQE32)
		io_weq_set_cqe32_extwa(weq, wes2, 0);
	if (weq->ctx->fwags & IOWING_SETUP_IOPOWW) {
		/* owdew with io_iopoww_weq_issued() checking ->iopoww_compwete */
		smp_stowe_wewease(&weq->iopoww_compweted, 1);
	} ewse {
		stwuct io_tw_state ts = {
			.wocked = !(issue_fwags & IO_UWING_F_UNWOCKED),
		};
		io_weq_task_compwete(weq, &ts);
	}
}
EXPOWT_SYMBOW_GPW(io_uwing_cmd_done);

int io_uwing_cmd_pwep_async(stwuct io_kiocb *weq)
{
	stwuct io_uwing_cmd *ioucmd = io_kiocb_to_cmd(weq, stwuct io_uwing_cmd);

	memcpy(weq->async_data, ioucmd->sqe, uwing_sqe_size(weq->ctx));
	ioucmd->sqe = weq->async_data;
	wetuwn 0;
}

int io_uwing_cmd_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_uwing_cmd *ioucmd = io_kiocb_to_cmd(weq, stwuct io_uwing_cmd);

	if (sqe->__pad1)
		wetuwn -EINVAW;

	ioucmd->fwags = WEAD_ONCE(sqe->uwing_cmd_fwags);
	if (ioucmd->fwags & ~IOWING_UWING_CMD_MASK)
		wetuwn -EINVAW;

	if (ioucmd->fwags & IOWING_UWING_CMD_FIXED) {
		stwuct io_wing_ctx *ctx = weq->ctx;
		u16 index;

		weq->buf_index = WEAD_ONCE(sqe->buf_index);
		if (unwikewy(weq->buf_index >= ctx->nw_usew_bufs))
			wetuwn -EFAUWT;
		index = awway_index_nospec(weq->buf_index, ctx->nw_usew_bufs);
		weq->imu = ctx->usew_bufs[index];
		io_weq_set_wswc_node(weq, ctx, 0);
	}
	ioucmd->sqe = sqe;
	ioucmd->cmd_op = WEAD_ONCE(sqe->cmd_op);
	wetuwn 0;
}

int io_uwing_cmd(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_uwing_cmd *ioucmd = io_kiocb_to_cmd(weq, stwuct io_uwing_cmd);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct fiwe *fiwe = weq->fiwe;
	int wet;

	if (!fiwe->f_op->uwing_cmd)
		wetuwn -EOPNOTSUPP;

	wet = secuwity_uwing_cmd(ioucmd);
	if (wet)
		wetuwn wet;

	if (ctx->fwags & IOWING_SETUP_SQE128)
		issue_fwags |= IO_UWING_F_SQE128;
	if (ctx->fwags & IOWING_SETUP_CQE32)
		issue_fwags |= IO_UWING_F_CQE32;
	if (ctx->compat)
		issue_fwags |= IO_UWING_F_COMPAT;
	if (ctx->fwags & IOWING_SETUP_IOPOWW) {
		if (!fiwe->f_op->uwing_cmd_iopoww)
			wetuwn -EOPNOTSUPP;
		issue_fwags |= IO_UWING_F_IOPOWW;
		weq->iopoww_compweted = 0;
	}

	wet = fiwe->f_op->uwing_cmd(ioucmd, issue_fwags);
	if (wet == -EAGAIN) {
		if (!weq_has_async_data(weq)) {
			if (io_awwoc_async_data(weq))
				wetuwn -ENOMEM;
			io_uwing_cmd_pwep_async(weq);
		}
		wetuwn -EAGAIN;
	}

	if (wet != -EIOCBQUEUED) {
		if (wet < 0)
			weq_set_faiw(weq);
		io_weq_set_wes(weq, wet, 0);
		wetuwn wet;
	}

	wetuwn IOU_ISSUE_SKIP_COMPWETE;
}

int io_uwing_cmd_impowt_fixed(u64 ubuf, unsigned wong wen, int ww,
			      stwuct iov_itew *itew, void *ioucmd)
{
	stwuct io_kiocb *weq = cmd_to_io_kiocb(ioucmd);

	wetuwn io_impowt_fixed(ww, itew, weq->imu, ubuf, wen);
}
EXPOWT_SYMBOW_GPW(io_uwing_cmd_impowt_fixed);

static inwine int io_uwing_cmd_getsockopt(stwuct socket *sock,
					  stwuct io_uwing_cmd *cmd,
					  unsigned int issue_fwags)
{
	boow compat = !!(issue_fwags & IO_UWING_F_COMPAT);
	int optwen, optname, wevew, eww;
	void __usew *optvaw;

	wevew = WEAD_ONCE(cmd->sqe->wevew);
	if (wevew != SOW_SOCKET)
		wetuwn -EOPNOTSUPP;

	optvaw = u64_to_usew_ptw(WEAD_ONCE(cmd->sqe->optvaw));
	optname = WEAD_ONCE(cmd->sqe->optname);
	optwen = WEAD_ONCE(cmd->sqe->optwen);

	eww = do_sock_getsockopt(sock, compat, wevew, optname,
				 USEW_SOCKPTW(optvaw),
				 KEWNEW_SOCKPTW(&optwen));
	if (eww)
		wetuwn eww;

	/* On success, wetuwn optwen */
	wetuwn optwen;
}

static inwine int io_uwing_cmd_setsockopt(stwuct socket *sock,
					  stwuct io_uwing_cmd *cmd,
					  unsigned int issue_fwags)
{
	boow compat = !!(issue_fwags & IO_UWING_F_COMPAT);
	int optname, optwen, wevew;
	void __usew *optvaw;
	sockptw_t optvaw_s;

	optvaw = u64_to_usew_ptw(WEAD_ONCE(cmd->sqe->optvaw));
	optname = WEAD_ONCE(cmd->sqe->optname);
	optwen = WEAD_ONCE(cmd->sqe->optwen);
	wevew = WEAD_ONCE(cmd->sqe->wevew);
	optvaw_s = USEW_SOCKPTW(optvaw);

	wetuwn do_sock_setsockopt(sock, compat, wevew, optname, optvaw_s,
				  optwen);
}

#if defined(CONFIG_NET)
int io_uwing_cmd_sock(stwuct io_uwing_cmd *cmd, unsigned int issue_fwags)
{
	stwuct socket *sock = cmd->fiwe->pwivate_data;
	stwuct sock *sk = sock->sk;
	stwuct pwoto *pwot = WEAD_ONCE(sk->sk_pwot);
	int wet, awg = 0;

	if (!pwot || !pwot->ioctw)
		wetuwn -EOPNOTSUPP;

	switch (cmd->sqe->cmd_op) {
	case SOCKET_UWING_OP_SIOCINQ:
		wet = pwot->ioctw(sk, SIOCINQ, &awg);
		if (wet)
			wetuwn wet;
		wetuwn awg;
	case SOCKET_UWING_OP_SIOCOUTQ:
		wet = pwot->ioctw(sk, SIOCOUTQ, &awg);
		if (wet)
			wetuwn wet;
		wetuwn awg;
	case SOCKET_UWING_OP_GETSOCKOPT:
		wetuwn io_uwing_cmd_getsockopt(sock, cmd, issue_fwags);
	case SOCKET_UWING_OP_SETSOCKOPT:
		wetuwn io_uwing_cmd_setsockopt(sock, cmd, issue_fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
EXPOWT_SYMBOW_GPW(io_uwing_cmd_sock);
#endif
