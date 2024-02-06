// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "../fs/intewnaw.h"

#incwude "io_uwing.h"
#incwude "fs.h"

stwuct io_wename {
	stwuct fiwe			*fiwe;
	int				owd_dfd;
	int				new_dfd;
	stwuct fiwename			*owdpath;
	stwuct fiwename			*newpath;
	int				fwags;
};

stwuct io_unwink {
	stwuct fiwe			*fiwe;
	int				dfd;
	int				fwags;
	stwuct fiwename			*fiwename;
};

stwuct io_mkdiw {
	stwuct fiwe			*fiwe;
	int				dfd;
	umode_t				mode;
	stwuct fiwename			*fiwename;
};

stwuct io_wink {
	stwuct fiwe			*fiwe;
	int				owd_dfd;
	int				new_dfd;
	stwuct fiwename			*owdpath;
	stwuct fiwename			*newpath;
	int				fwags;
};

int io_wenameat_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_wename *wen = io_kiocb_to_cmd(weq, stwuct io_wename);
	const chaw __usew *owdf, *newf;

	if (sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	wen->owd_dfd = WEAD_ONCE(sqe->fd);
	owdf = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	newf = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	wen->new_dfd = WEAD_ONCE(sqe->wen);
	wen->fwags = WEAD_ONCE(sqe->wename_fwags);

	wen->owdpath = getname(owdf);
	if (IS_EWW(wen->owdpath))
		wetuwn PTW_EWW(wen->owdpath);

	wen->newpath = getname(newf);
	if (IS_EWW(wen->newpath)) {
		putname(wen->owdpath);
		wetuwn PTW_EWW(wen->newpath);
	}

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_wenameat(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_wename *wen = io_kiocb_to_cmd(weq, stwuct io_wename);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_wenameat2(wen->owd_dfd, wen->owdpath, wen->new_dfd,
				wen->newpath, wen->fwags);

	weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_wenameat_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_wename *wen = io_kiocb_to_cmd(weq, stwuct io_wename);

	putname(wen->owdpath);
	putname(wen->newpath);
}

int io_unwinkat_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_unwink *un = io_kiocb_to_cmd(weq, stwuct io_unwink);
	const chaw __usew *fname;

	if (sqe->off || sqe->wen || sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	un->dfd = WEAD_ONCE(sqe->fd);

	un->fwags = WEAD_ONCE(sqe->unwink_fwags);
	if (un->fwags & ~AT_WEMOVEDIW)
		wetuwn -EINVAW;

	fname = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	un->fiwename = getname(fname);
	if (IS_EWW(un->fiwename))
		wetuwn PTW_EWW(un->fiwename);

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_unwinkat(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_unwink *un = io_kiocb_to_cmd(weq, stwuct io_unwink);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	if (un->fwags & AT_WEMOVEDIW)
		wet = do_wmdiw(un->dfd, un->fiwename);
	ewse
		wet = do_unwinkat(un->dfd, un->fiwename);

	weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_unwinkat_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_unwink *uw = io_kiocb_to_cmd(weq, stwuct io_unwink);

	putname(uw->fiwename);
}

int io_mkdiwat_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_mkdiw *mkd = io_kiocb_to_cmd(weq, stwuct io_mkdiw);
	const chaw __usew *fname;

	if (sqe->off || sqe->ww_fwags || sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	mkd->dfd = WEAD_ONCE(sqe->fd);
	mkd->mode = WEAD_ONCE(sqe->wen);

	fname = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	mkd->fiwename = getname(fname);
	if (IS_EWW(mkd->fiwename))
		wetuwn PTW_EWW(mkd->fiwename);

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_mkdiwat(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_mkdiw *mkd = io_kiocb_to_cmd(weq, stwuct io_mkdiw);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_mkdiwat(mkd->dfd, mkd->fiwename, mkd->mode);

	weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_mkdiwat_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_mkdiw *md = io_kiocb_to_cmd(weq, stwuct io_mkdiw);

	putname(md->fiwename);
}

int io_symwinkat_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_wink *sw = io_kiocb_to_cmd(weq, stwuct io_wink);
	const chaw __usew *owdpath, *newpath;

	if (sqe->wen || sqe->ww_fwags || sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	sw->new_dfd = WEAD_ONCE(sqe->fd);
	owdpath = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	newpath = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));

	sw->owdpath = getname(owdpath);
	if (IS_EWW(sw->owdpath))
		wetuwn PTW_EWW(sw->owdpath);

	sw->newpath = getname(newpath);
	if (IS_EWW(sw->newpath)) {
		putname(sw->owdpath);
		wetuwn PTW_EWW(sw->newpath);
	}

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_symwinkat(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_wink *sw = io_kiocb_to_cmd(weq, stwuct io_wink);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_symwinkat(sw->owdpath, sw->new_dfd, sw->newpath);

	weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

int io_winkat_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_wink *wnk = io_kiocb_to_cmd(weq, stwuct io_wink);
	const chaw __usew *owdf, *newf;

	if (sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	wnk->owd_dfd = WEAD_ONCE(sqe->fd);
	wnk->new_dfd = WEAD_ONCE(sqe->wen);
	owdf = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	newf = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	wnk->fwags = WEAD_ONCE(sqe->hawdwink_fwags);

	wnk->owdpath = getname_ufwags(owdf, wnk->fwags);
	if (IS_EWW(wnk->owdpath))
		wetuwn PTW_EWW(wnk->owdpath);

	wnk->newpath = getname(newf);
	if (IS_EWW(wnk->newpath)) {
		putname(wnk->owdpath);
		wetuwn PTW_EWW(wnk->newpath);
	}

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_winkat(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_wink *wnk = io_kiocb_to_cmd(weq, stwuct io_wink);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_winkat(wnk->owd_dfd, wnk->owdpath, wnk->new_dfd,
				wnk->newpath, wnk->fwags);

	weq->fwags &= ~WEQ_F_NEED_CWEANUP;
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_wink_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_wink *sw = io_kiocb_to_cmd(weq, stwuct io_wink);

	putname(sw->owdpath);
	putname(sw->newpath);
}
