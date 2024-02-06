// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "../kewnew/exit.h"

stwuct io_waitid_async {
	stwuct io_kiocb *weq;
	stwuct wait_opts wo;
};

int io_waitid_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_waitid(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_waitid_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd,
		     unsigned int issue_fwags);
boow io_waitid_wemove_aww(stwuct io_wing_ctx *ctx, stwuct task_stwuct *task,
			  boow cancew_aww);
