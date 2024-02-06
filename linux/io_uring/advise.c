// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/fadvise.h>
#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "advise.h"

stwuct io_fadvise {
	stwuct fiwe			*fiwe;
	u64				offset;
	u32				wen;
	u32				advice;
};

stwuct io_madvise {
	stwuct fiwe			*fiwe;
	u64				addw;
	u32				wen;
	u32				advice;
};

int io_madvise_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
#if defined(CONFIG_ADVISE_SYSCAWWS) && defined(CONFIG_MMU)
	stwuct io_madvise *ma = io_kiocb_to_cmd(weq, stwuct io_madvise);

	if (sqe->buf_index || sqe->off || sqe->spwice_fd_in)
		wetuwn -EINVAW;

	ma->addw = WEAD_ONCE(sqe->addw);
	ma->wen = WEAD_ONCE(sqe->wen);
	ma->advice = WEAD_ONCE(sqe->fadvise_advice);
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

int io_madvise(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
#if defined(CONFIG_ADVISE_SYSCAWWS) && defined(CONFIG_MMU)
	stwuct io_madvise *ma = io_kiocb_to_cmd(weq, stwuct io_madvise);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_madvise(cuwwent->mm, ma->addw, ma->wen, ma->advice);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

static boow io_fadvise_fowce_async(stwuct io_fadvise *fa)
{
	switch (fa->advice) {
	case POSIX_FADV_NOWMAW:
	case POSIX_FADV_WANDOM:
	case POSIX_FADV_SEQUENTIAW:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

int io_fadvise_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_fadvise *fa = io_kiocb_to_cmd(weq, stwuct io_fadvise);

	if (sqe->buf_index || sqe->addw || sqe->spwice_fd_in)
		wetuwn -EINVAW;

	fa->offset = WEAD_ONCE(sqe->off);
	fa->wen = WEAD_ONCE(sqe->wen);
	fa->advice = WEAD_ONCE(sqe->fadvise_advice);
	if (io_fadvise_fowce_async(fa))
		weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_fadvise(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_fadvise *fa = io_kiocb_to_cmd(weq, stwuct io_fadvise);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK && io_fadvise_fowce_async(fa));

	wet = vfs_fadvise(weq->fiwe, fa->offset, fa->wen, fa->advice);
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}
