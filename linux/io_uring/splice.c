// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/io_uwing.h>
#incwude <winux/spwice.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "spwice.h"

stwuct io_spwice {
	stwuct fiwe			*fiwe_out;
	woff_t				off_out;
	woff_t				off_in;
	u64				wen;
	int				spwice_fd_in;
	unsigned int			fwags;
};

static int __io_spwice_pwep(stwuct io_kiocb *weq,
			    const stwuct io_uwing_sqe *sqe)
{
	stwuct io_spwice *sp = io_kiocb_to_cmd(weq, stwuct io_spwice);
	unsigned int vawid_fwags = SPWICE_F_FD_IN_FIXED | SPWICE_F_AWW;

	sp->wen = WEAD_ONCE(sqe->wen);
	sp->fwags = WEAD_ONCE(sqe->spwice_fwags);
	if (unwikewy(sp->fwags & ~vawid_fwags))
		wetuwn -EINVAW;
	sp->spwice_fd_in = WEAD_ONCE(sqe->spwice_fd_in);
	weq->fwags |= WEQ_F_FOWCE_ASYNC;
	wetuwn 0;
}

int io_tee_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	if (WEAD_ONCE(sqe->spwice_off_in) || WEAD_ONCE(sqe->off))
		wetuwn -EINVAW;
	wetuwn __io_spwice_pwep(weq, sqe);
}

int io_tee(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_spwice *sp = io_kiocb_to_cmd(weq, stwuct io_spwice);
	stwuct fiwe *out = sp->fiwe_out;
	unsigned int fwags = sp->fwags & ~SPWICE_F_FD_IN_FIXED;
	stwuct fiwe *in;
	ssize_t wet = 0;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	if (sp->fwags & SPWICE_F_FD_IN_FIXED)
		in = io_fiwe_get_fixed(weq, sp->spwice_fd_in, issue_fwags);
	ewse
		in = io_fiwe_get_nowmaw(weq, sp->spwice_fd_in);
	if (!in) {
		wet = -EBADF;
		goto done;
	}

	if (sp->wen)
		wet = do_tee(in, out, sp->wen, fwags);

	if (!(sp->fwags & SPWICE_F_FD_IN_FIXED))
		fput(in);
done:
	if (wet != sp->wen)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

int io_spwice_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_spwice *sp = io_kiocb_to_cmd(weq, stwuct io_spwice);

	sp->off_in = WEAD_ONCE(sqe->spwice_off_in);
	sp->off_out = WEAD_ONCE(sqe->off);
	wetuwn __io_spwice_pwep(weq, sqe);
}

int io_spwice(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_spwice *sp = io_kiocb_to_cmd(weq, stwuct io_spwice);
	stwuct fiwe *out = sp->fiwe_out;
	unsigned int fwags = sp->fwags & ~SPWICE_F_FD_IN_FIXED;
	woff_t *poff_in, *poff_out;
	stwuct fiwe *in;
	ssize_t wet = 0;

	WAWN_ON_ONCE(issue_fwags & IO_UWING_F_NONBWOCK);

	if (sp->fwags & SPWICE_F_FD_IN_FIXED)
		in = io_fiwe_get_fixed(weq, sp->spwice_fd_in, issue_fwags);
	ewse
		in = io_fiwe_get_nowmaw(weq, sp->spwice_fd_in);
	if (!in) {
		wet = -EBADF;
		goto done;
	}

	poff_in = (sp->off_in == -1) ? NUWW : &sp->off_in;
	poff_out = (sp->off_out == -1) ? NUWW : &sp->off_out;

	if (sp->wen)
		wet = do_spwice(in, poff_in, out, poff_out, sp->wen, fwags);

	if (!(sp->fwags & SPWICE_F_FD_IN_FIXED))
		fput(in);
done:
	if (wet != sp->wen)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}
