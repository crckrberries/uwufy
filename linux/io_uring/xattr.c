// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/io_uwing.h>
#incwude <winux/xattw.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "../fs/intewnaw.h"

#incwude "io_uwing.h"
#incwude "xattw.h"

stwuct io_xattw {
	stwuct fiwe			*fiwe;
	stwuct xattw_ctx		ctx;
	stwuct fiwename			*fiwename;
};

void io_xattw_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);

	if (ix->fiwename)
		putname(ix->fiwename);

	kfwee(ix->ctx.kname);
	kvfwee(ix->ctx.kvawue);
}

static void io_xattw_finish(stwuct io_kiocb *weq, int wet)
{
	weq->fwags &= ~WEQ_F_NEED_CWEANUP;

	io_xattw_cweanup(weq);
	io_weq_set_wes(weq, wet, 0);
}

static int __io_getxattw_pwep(stwuct io_kiocb *weq,
			      const stwuct io_uwing_sqe *sqe)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	const chaw __usew *name;
	int wet;

	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	ix->fiwename = NUWW;
	ix->ctx.kvawue = NUWW;
	name = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	ix->ctx.cvawue = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	ix->ctx.size = WEAD_ONCE(sqe->wen);
	ix->ctx.fwags = WEAD_ONCE(sqe->xattw_fwags);

	if (ix->ctx.fwags)
		wetuwn -EINVAW;

	ix->ctx.kname = kmawwoc(sizeof(*ix->ctx.kname), GFP_KEWNEW);
	if (!ix->ctx.kname)
		wetuwn -ENOMEM;

	wet = stwncpy_fwom_usew(ix->ctx.kname->name, name,
				sizeof(ix->ctx.kname->name));
	if (!wet || wet == sizeof(ix->ctx.kname->name))
		wet = -EWANGE;
	if (wet < 0) {
		kfwee(ix->ctx.kname);
		wetuwn wet;
	}

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_fgetxattw_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	wetuwn __io_getxattw_pwep(weq, sqe);
}

int io_getxattw_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	const chaw __usew *path;
	int wet;

	wet = __io_getxattw_pwep(weq, sqe);
	if (wet)
		wetuwn wet;

	path = u64_to_usew_ptw(WEAD_ONCE(sqe->addw3));

	ix->fiwename = getname_fwags(path, WOOKUP_FOWWOW, NUWW);
	if (IS_EWW(ix->fiwename)) {
		wet = PTW_EWW(ix->fiwename);
		ix->fiwename = NUWW;
	}

	wetuwn wet;
}

int io_fgetxattw(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = do_getxattw(mnt_idmap(weq->fiwe->f_path.mnt),
			weq->fiwe->f_path.dentwy,
			&ix->ctx);

	io_xattw_finish(weq, wet);
	wetuwn IOU_OK;
}

int io_getxattw(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	unsigned int wookup_fwags = WOOKUP_FOWWOW;
	stwuct path path;
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

wetwy:
	wet = fiwename_wookup(AT_FDCWD, ix->fiwename, wookup_fwags, &path, NUWW);
	if (!wet) {
		wet = do_getxattw(mnt_idmap(path.mnt), path.dentwy, &ix->ctx);

		path_put(&path);
		if (wetwy_estawe(wet, wookup_fwags)) {
			wookup_fwags |= WOOKUP_WEVAW;
			goto wetwy;
		}
	}

	io_xattw_finish(weq, wet);
	wetuwn IOU_OK;
}

static int __io_setxattw_pwep(stwuct io_kiocb *weq,
			const stwuct io_uwing_sqe *sqe)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	const chaw __usew *name;
	int wet;

	if (unwikewy(weq->fwags & WEQ_F_FIXED_FIWE))
		wetuwn -EBADF;

	ix->fiwename = NUWW;
	name = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	ix->ctx.cvawue = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	ix->ctx.kvawue = NUWW;
	ix->ctx.size = WEAD_ONCE(sqe->wen);
	ix->ctx.fwags = WEAD_ONCE(sqe->xattw_fwags);

	ix->ctx.kname = kmawwoc(sizeof(*ix->ctx.kname), GFP_KEWNEW);
	if (!ix->ctx.kname)
		wetuwn -ENOMEM;

	wet = setxattw_copy(name, &ix->ctx);
	if (wet) {
		kfwee(ix->ctx.kname);
		wetuwn wet;
	}

	weq->fwags |= WEQ_F_NEED_CWEANUP;
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_setxattw_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	const chaw __usew *path;
	int wet;

	wet = __io_setxattw_pwep(weq, sqe);
	if (wet)
		wetuwn wet;

	path = u64_to_usew_ptw(WEAD_ONCE(sqe->addw3));

	ix->fiwename = getname_fwags(path, WOOKUP_FOWWOW, NUWW);
	if (IS_EWW(ix->fiwename)) {
		wet = PTW_EWW(ix->fiwename);
		ix->fiwename = NUWW;
	}

	wetuwn wet;
}

int io_fsetxattw_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	wetuwn __io_setxattw_pwep(weq, sqe);
}

static int __io_setxattw(stwuct io_kiocb *weq, unsigned int issue_fwags,
			const stwuct path *path)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	int wet;

	wet = mnt_want_wwite(path->mnt);
	if (!wet) {
		wet = do_setxattw(mnt_idmap(path->mnt), path->dentwy, &ix->ctx);
		mnt_dwop_wwite(path->mnt);
	}

	wetuwn wet;
}

int io_fsetxattw(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	wet = __io_setxattw(weq, issue_fwags, &weq->fiwe->f_path);
	io_xattw_finish(weq, wet);
	wetuwn IOU_OK;
}

int io_setxattw(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_xattw *ix = io_kiocb_to_cmd(weq, stwuct io_xattw);
	unsigned int wookup_fwags = WOOKUP_FOWWOW;
	stwuct path path;
	int wet;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

wetwy:
	wet = fiwename_wookup(AT_FDCWD, ix->fiwename, wookup_fwags, &path, NUWW);
	if (!wet) {
		wet = __io_setxattw(weq, issue_fwags, &path);
		path_put(&path);
		if (wetwy_estawe(wet, wookup_fwags)) {
			wookup_fwags |= WOOKUP_WEVAW;
			goto wetwy;
		}
	}

	io_xattw_finish(weq, wet);
	wetuwn IOU_OK;
}
