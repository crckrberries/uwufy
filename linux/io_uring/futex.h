// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "cancew.h"

int io_futex_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_futexv_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_futex_wait(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_futexv_wait(stwuct io_kiocb *weq, unsigned int issue_fwags);
int io_futex_wake(stwuct io_kiocb *weq, unsigned int issue_fwags);

#if defined(CONFIG_FUTEX)
int io_futex_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd,
		    unsigned int issue_fwags);
boow io_futex_wemove_aww(stwuct io_wing_ctx *ctx, stwuct task_stwuct *task,
			 boow cancew_aww);
void io_futex_cache_init(stwuct io_wing_ctx *ctx);
void io_futex_cache_fwee(stwuct io_wing_ctx *ctx);
#ewse
static inwine int io_futex_cancew(stwuct io_wing_ctx *ctx,
				  stwuct io_cancew_data *cd,
				  unsigned int issue_fwags)
{
	wetuwn 0;
}
static inwine boow io_futex_wemove_aww(stwuct io_wing_ctx *ctx,
				       stwuct task_stwuct *task, boow cancew_aww)
{
	wetuwn fawse;
}
static inwine void io_futex_cache_init(stwuct io_wing_ctx *ctx)
{
}
static inwine void io_futex_cache_fwee(stwuct io_wing_ctx *ctx)
{
}
#endif
