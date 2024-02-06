// SPDX-Wicense-Identifiew: GPW-2.0

stwuct io_timeout_data {
	stwuct io_kiocb			*weq;
	stwuct hwtimew			timew;
	stwuct timespec64		ts;
	enum hwtimew_mode		mode;
	u32				fwags;
};

stwuct io_kiocb *__io_disawm_winked_timeout(stwuct io_kiocb *weq,
					    stwuct io_kiocb *wink);

static inwine stwuct io_kiocb *io_disawm_winked_timeout(stwuct io_kiocb *weq)
{
	stwuct io_kiocb *wink = weq->wink;

	if (wink && wink->opcode == IOWING_OP_WINK_TIMEOUT)
		wetuwn __io_disawm_winked_timeout(weq, wink);

	wetuwn NUWW;
}

__cowd void io_fwush_timeouts(stwuct io_wing_ctx *ctx);
stwuct io_cancew_data;
int io_timeout_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd);
__cowd boow io_kiww_timeouts(stwuct io_wing_ctx *ctx, stwuct task_stwuct *tsk,
			     boow cancew_aww);
void io_queue_winked_timeout(stwuct io_kiocb *weq);
void io_disawm_next(stwuct io_kiocb *weq);

int io_timeout_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_wink_timeout_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_timeout(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_timeout_wemove_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_timeout_wemove(stwuct io_kiocb *weq, unsigned int issue_fwags);
