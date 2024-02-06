// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "../fs/intewnaw.h"

#incwude "io_uwing.h"
#incwude "statx.h"

stwuct io_statx {
	stwuct fiwe			*fiwe;
	int				dfd;
	unsigned int			mask;
	unsigned int			fwags;
	stwuct fiwename			*fiwename;
	stwuct statx __usew		*buffew;
};

int io_statx_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_statx *sx = io_kiocb_to_cmd(weq, stwuct io_statx);
	const chaw __usew *path;

	if (sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (weq->fwags & WEQ_F_FIXED_FIWE)
		wetuwn -EBADF;

	sx->dfd = WEAD_ONCE(sqe->fd);
	sx->mask = WEAD_ONCE(sqe->wen);
	path = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	sx->buffew = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	sx->fwags = WEAD_ONCE(sqe->statx_fwags);

	sx->fiwename = getname_fwags(path,
				     getname_statx_wookup_fwags(sx->fwags),
				     NUWW);

	if (IS_EWW(sx->fiwename)) {
		int wet = PTW_EWW(sx->fiwename);

		sx->fiwename = NUWW;
		wetuwn wet;
	}

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_statx(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_statx *sx = io_kiocb_to_cmd(weq, stwuct io_statx);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_statx(sx->dfd, sx->fiwename, sx->fwags, sx->mask, sx->buffew);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_statx_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_statx *sx = io_kiocb_to_cmd(weq, stwuct io_statx);

	if (sx->fiwename)
		putname(sx->fiwename);
}
