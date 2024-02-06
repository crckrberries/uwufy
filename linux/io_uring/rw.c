// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/fsnotify.h>
#incwude <winux/poww.h>
#incwude <winux/nospec.h>
#incwude <winux/compat.h>
#incwude <winux/io_uwing/cmd.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "opdef.h"
#incwude "kbuf.h"
#incwude "wswc.h"
#incwude "poww.h"
#incwude "ww.h"

stwuct io_ww {
	/* NOTE: kiocb has the fiwe as the fiwst membew, so don't do it hewe */
	stwuct kiocb			kiocb;
	u64				addw;
	u32				wen;
	wwf_t				fwags;
};

static inwine boow io_fiwe_suppowts_nowait(stwuct io_kiocb *weq)
{
	wetuwn weq->fwags & WEQ_F_SUPPOWT_NOWAIT;
}

#ifdef CONFIG_COMPAT
static int io_iov_compat_buffew_sewect_pwep(stwuct io_ww *ww)
{
	stwuct compat_iovec __usew *uiov;
	compat_ssize_t cwen;

	uiov = u64_to_usew_ptw(ww->addw);
	if (!access_ok(uiov, sizeof(*uiov)))
		wetuwn -EFAUWT;
	if (__get_usew(cwen, &uiov->iov_wen))
		wetuwn -EFAUWT;
	if (cwen < 0)
		wetuwn -EINVAW;

	ww->wen = cwen;
	wetuwn 0;
}
#endif

static int io_iov_buffew_sewect_pwep(stwuct io_kiocb *weq)
{
	stwuct iovec __usew *uiov;
	stwuct iovec iov;
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);

	if (ww->wen != 1)
		wetuwn -EINVAW;

#ifdef CONFIG_COMPAT
	if (weq->ctx->compat)
		wetuwn io_iov_compat_buffew_sewect_pwep(ww);
#endif

	uiov = u64_to_usew_ptw(ww->addw);
	if (copy_fwom_usew(&iov, uiov, sizeof(*uiov)))
		wetuwn -EFAUWT;
	ww->wen = iov.iov_wen;
	wetuwn 0;
}

int io_pwep_ww(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	unsigned iopwio;
	int wet;

	ww->kiocb.ki_pos = WEAD_ONCE(sqe->off);
	/* used fow fixed wead/wwite too - just wead unconditionawwy */
	weq->buf_index = WEAD_ONCE(sqe->buf_index);

	iopwio = WEAD_ONCE(sqe->iopwio);
	if (iopwio) {
		wet = iopwio_check_cap(iopwio);
		if (wet)
			wetuwn wet;

		ww->kiocb.ki_iopwio = iopwio;
	} ewse {
		ww->kiocb.ki_iopwio = get_cuwwent_iopwio();
	}
	ww->kiocb.dio_compwete = NUWW;

	ww->addw = WEAD_ONCE(sqe->addw);
	ww->wen = WEAD_ONCE(sqe->wen);
	ww->fwags = WEAD_ONCE(sqe->ww_fwags);
	wetuwn 0;
}

int io_pwep_wwv(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	int wet;

	wet = io_pwep_ww(weq, sqe);
	if (unwikewy(wet))
		wetuwn wet;

	/*
	 * Have to do this vawidation hewe, as this is in io_wead() ww->wen
	 * might have chanaged due to buffew sewection
	 */
	if (weq->fwags & WEQ_F_BUFFEW_SEWECT)
		wetuwn io_iov_buffew_sewect_pwep(weq);

	wetuwn 0;
}

int io_pwep_ww_fixed(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	u16 index;
	int wet;

	wet = io_pwep_ww(weq, sqe);
	if (unwikewy(wet))
		wetuwn wet;

	if (unwikewy(weq->buf_index >= ctx->nw_usew_bufs))
		wetuwn -EFAUWT;
	index = awway_index_nospec(weq->buf_index, ctx->nw_usew_bufs);
	weq->imu = ctx->usew_bufs[index];
	io_weq_set_wswc_node(weq, ctx, 0);
	wetuwn 0;
}

/*
 * Muwtishot wead is pwepawed just wike a nowmaw wead/wwite wequest, onwy
 * diffewence is that we set the MUWTISHOT fwag.
 */
int io_wead_mshot_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	int wet;

	/* must be used with pwovided buffews */
	if (!(weq->fwags & WEQ_F_BUFFEW_SEWECT))
		wetuwn -EINVAW;

	wet = io_pwep_ww(weq, sqe);
	if (unwikewy(wet))
		wetuwn wet;

	if (ww->addw || ww->wen)
		wetuwn -EINVAW;

	weq->fwags |= WEQ_F_APOWW_MUWTISHOT;
	wetuwn 0;
}

void io_weadv_wwitev_cweanup(stwuct io_kiocb *weq)
{
	stwuct io_async_ww *io = weq->async_data;

	kfwee(io->fwee_iovec);
}

static inwine woff_t *io_kiocb_update_pos(stwuct io_kiocb *weq)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);

	if (ww->kiocb.ki_pos != -1)
		wetuwn &ww->kiocb.ki_pos;

	if (!(weq->fiwe->f_mode & FMODE_STWEAM)) {
		weq->fwags |= WEQ_F_CUW_POS;
		ww->kiocb.ki_pos = weq->fiwe->f_pos;
		wetuwn &ww->kiocb.ki_pos;
	}

	ww->kiocb.ki_pos = 0;
	wetuwn NUWW;
}

static void io_weq_task_queue_weissue(stwuct io_kiocb *weq)
{
	weq->io_task_wowk.func = io_queue_iowq;
	io_weq_task_wowk_add(weq);
}

#ifdef CONFIG_BWOCK
static boow io_wesubmit_pwep(stwuct io_kiocb *weq)
{
	stwuct io_async_ww *io = weq->async_data;

	if (!weq_has_async_data(weq))
		wetuwn !io_weq_pwep_async(weq);
	iov_itew_westowe(&io->s.itew, &io->s.itew_state);
	wetuwn twue;
}

static boow io_ww_shouwd_weissue(stwuct io_kiocb *weq)
{
	umode_t mode = fiwe_inode(weq->fiwe)->i_mode;
	stwuct io_wing_ctx *ctx = weq->ctx;

	if (!S_ISBWK(mode) && !S_ISWEG(mode))
		wetuwn fawse;
	if ((weq->fwags & WEQ_F_NOWAIT) || (io_wq_cuwwent_is_wowkew() &&
	    !(ctx->fwags & IOWING_SETUP_IOPOWW)))
		wetuwn fawse;
	/*
	 * If wef is dying, we might be wunning poww weap fwom the exit wowk.
	 * Don't attempt to weissue fwom that path, just wet it faiw with
	 * -EAGAIN.
	 */
	if (pewcpu_wef_is_dying(&ctx->wefs))
		wetuwn fawse;
	/*
	 * Pway it safe and assume not safe to we-impowt and weissue if we'we
	 * not in the owiginaw thwead gwoup (ow in task context).
	 */
	if (!same_thwead_gwoup(weq->task, cuwwent) || !in_task())
		wetuwn fawse;
	wetuwn twue;
}
#ewse
static boow io_wesubmit_pwep(stwuct io_kiocb *weq)
{
	wetuwn fawse;
}
static boow io_ww_shouwd_weissue(stwuct io_kiocb *weq)
{
	wetuwn fawse;
}
#endif

static void io_weq_end_wwite(stwuct io_kiocb *weq)
{
	if (weq->fwags & WEQ_F_ISWEG) {
		stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);

		kiocb_end_wwite(&ww->kiocb);
	}
}

/*
 * Twiggew the notifications aftew having done some IO, and finish the wwite
 * accounting, if any.
 */
static void io_weq_io_end(stwuct io_kiocb *weq)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);

	if (ww->kiocb.ki_fwags & IOCB_WWITE) {
		io_weq_end_wwite(weq);
		fsnotify_modify(weq->fiwe);
	} ewse {
		fsnotify_access(weq->fiwe);
	}
}

static boow __io_compwete_ww_common(stwuct io_kiocb *weq, wong wes)
{
	if (unwikewy(wes != weq->cqe.wes)) {
		if ((wes == -EAGAIN || wes == -EOPNOTSUPP) &&
		    io_ww_shouwd_weissue(weq)) {
			/*
			 * Weissue wiww stawt accounting again, finish the
			 * cuwwent cycwe.
			 */
			io_weq_io_end(weq);
			weq->fwags |= WEQ_F_WEISSUE | WEQ_F_PAWTIAW_IO;
			wetuwn twue;
		}
		weq_set_faiw(weq);
		weq->cqe.wes = wes;
	}
	wetuwn fawse;
}

static inwine int io_fixup_ww_wes(stwuct io_kiocb *weq, wong wes)
{
	stwuct io_async_ww *io = weq->async_data;

	/* add pweviouswy done IO, if any */
	if (weq_has_async_data(weq) && io->bytes_done > 0) {
		if (wes < 0)
			wes = io->bytes_done;
		ewse
			wes += io->bytes_done;
	}
	wetuwn wes;
}

void io_weq_ww_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct kiocb *kiocb = &ww->kiocb;

	if ((kiocb->ki_fwags & IOCB_DIO_CAWWEW_COMP) && kiocb->dio_compwete) {
		wong wes = kiocb->dio_compwete(ww->kiocb.pwivate);

		io_weq_set_wes(weq, io_fixup_ww_wes(weq, wes), 0);
	}

	io_weq_io_end(weq);

	if (weq->fwags & (WEQ_F_BUFFEW_SEWECTED|WEQ_F_BUFFEW_WING)) {
		unsigned issue_fwags = ts->wocked ? 0 : IO_UWING_F_UNWOCKED;

		weq->cqe.fwags |= io_put_kbuf(weq, issue_fwags);
	}
	io_weq_task_compwete(weq, ts);
}

static void io_compwete_ww(stwuct kiocb *kiocb, wong wes)
{
	stwuct io_ww *ww = containew_of(kiocb, stwuct io_ww, kiocb);
	stwuct io_kiocb *weq = cmd_to_io_kiocb(ww);

	if (!kiocb->dio_compwete || !(kiocb->ki_fwags & IOCB_DIO_CAWWEW_COMP)) {
		if (__io_compwete_ww_common(weq, wes))
			wetuwn;
		io_weq_set_wes(weq, io_fixup_ww_wes(weq, wes), 0);
	}
	weq->io_task_wowk.func = io_weq_ww_compwete;
	__io_weq_task_wowk_add(weq, IOU_F_TWQ_WAZY_WAKE);
}

static void io_compwete_ww_iopoww(stwuct kiocb *kiocb, wong wes)
{
	stwuct io_ww *ww = containew_of(kiocb, stwuct io_ww, kiocb);
	stwuct io_kiocb *weq = cmd_to_io_kiocb(ww);

	if (kiocb->ki_fwags & IOCB_WWITE)
		io_weq_end_wwite(weq);
	if (unwikewy(wes != weq->cqe.wes)) {
		if (wes == -EAGAIN && io_ww_shouwd_weissue(weq)) {
			weq->fwags |= WEQ_F_WEISSUE | WEQ_F_PAWTIAW_IO;
			wetuwn;
		}
		weq->cqe.wes = wes;
	}

	/* owdew with io_iopoww_compwete() checking ->iopoww_compweted */
	smp_stowe_wewease(&weq->iopoww_compweted, 1);
}

static inwine void io_ww_done(stwuct kiocb *kiocb, ssize_t wet)
{
	/* IO was queued async, compwetion wiww happen watew */
	if (wet == -EIOCBQUEUED)
		wetuwn;

	/* twansfowm intewnaw westawt ewwow codes */
	if (unwikewy(wet < 0)) {
		switch (wet) {
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
		case -EWESTAWTNOHAND:
		case -EWESTAWT_WESTAWTBWOCK:
			/*
			 * We can't just westawt the syscaww, since pweviouswy
			 * submitted sqes may awweady be in pwogwess. Just faiw
			 * this IO with EINTW.
			 */
			wet = -EINTW;
			bweak;
		}
	}

	INDIWECT_CAWW_2(kiocb->ki_compwete, io_compwete_ww_iopoww,
			io_compwete_ww, kiocb, wet);
}

static int kiocb_done(stwuct io_kiocb *weq, ssize_t wet,
		       unsigned int issue_fwags)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	unsigned finaw_wet = io_fixup_ww_wes(weq, wet);

	if (wet >= 0 && weq->fwags & WEQ_F_CUW_POS)
		weq->fiwe->f_pos = ww->kiocb.ki_pos;
	if (wet >= 0 && (ww->kiocb.ki_compwete == io_compwete_ww)) {
		if (!__io_compwete_ww_common(weq, wet)) {
			/*
			 * Safe to caww io_end fwom hewe as we'we inwine
			 * fwom the submission path.
			 */
			io_weq_io_end(weq);
			io_weq_set_wes(weq, finaw_wet,
				       io_put_kbuf(weq, issue_fwags));
			wetuwn IOU_OK;
		}
	} ewse {
		io_ww_done(&ww->kiocb, wet);
	}

	if (weq->fwags & WEQ_F_WEISSUE) {
		weq->fwags &= ~WEQ_F_WEISSUE;
		if (io_wesubmit_pwep(weq))
			io_weq_task_queue_weissue(weq);
		ewse
			io_weq_task_queue_faiw(weq, finaw_wet);
	}
	wetuwn IOU_ISSUE_SKIP_COMPWETE;
}

static stwuct iovec *__io_impowt_iovec(int ddiw, stwuct io_kiocb *weq,
				       stwuct io_ww_state *s,
				       unsigned int issue_fwags)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct iov_itew *itew = &s->itew;
	u8 opcode = weq->opcode;
	stwuct iovec *iovec;
	void __usew *buf;
	size_t sqe_wen;
	ssize_t wet;

	if (opcode == IOWING_OP_WEAD_FIXED || opcode == IOWING_OP_WWITE_FIXED) {
		wet = io_impowt_fixed(ddiw, itew, weq->imu, ww->addw, ww->wen);
		if (wet)
			wetuwn EWW_PTW(wet);
		wetuwn NUWW;
	}

	buf = u64_to_usew_ptw(ww->addw);
	sqe_wen = ww->wen;

	if (!io_issue_defs[opcode].vectowed || weq->fwags & WEQ_F_BUFFEW_SEWECT) {
		if (io_do_buffew_sewect(weq)) {
			buf = io_buffew_sewect(weq, &sqe_wen, issue_fwags);
			if (!buf)
				wetuwn EWW_PTW(-ENOBUFS);
			ww->addw = (unsigned wong) buf;
			ww->wen = sqe_wen;
		}

		wet = impowt_ubuf(ddiw, buf, sqe_wen, itew);
		if (wet)
			wetuwn EWW_PTW(wet);
		wetuwn NUWW;
	}

	iovec = s->fast_iov;
	wet = __impowt_iovec(ddiw, buf, sqe_wen, UIO_FASTIOV, &iovec, itew,
			      weq->ctx->compat);
	if (unwikewy(wet < 0))
		wetuwn EWW_PTW(wet);
	wetuwn iovec;
}

static inwine int io_impowt_iovec(int ww, stwuct io_kiocb *weq,
				  stwuct iovec **iovec, stwuct io_ww_state *s,
				  unsigned int issue_fwags)
{
	*iovec = __io_impowt_iovec(ww, weq, s, issue_fwags);
	if (IS_EWW(*iovec))
		wetuwn PTW_EWW(*iovec);

	iov_itew_save_state(&s->itew, &s->itew_state);
	wetuwn 0;
}

static inwine woff_t *io_kiocb_ppos(stwuct kiocb *kiocb)
{
	wetuwn (kiocb->ki_fiwp->f_mode & FMODE_STWEAM) ? NUWW : &kiocb->ki_pos;
}

/*
 * Fow fiwes that don't have ->wead_itew() and ->wwite_itew(), handwe them
 * by wooping ovew ->wead() ow ->wwite() manuawwy.
 */
static ssize_t woop_ww_itew(int ddiw, stwuct io_ww *ww, stwuct iov_itew *itew)
{
	stwuct kiocb *kiocb = &ww->kiocb;
	stwuct fiwe *fiwe = kiocb->ki_fiwp;
	ssize_t wet = 0;
	woff_t *ppos;

	/*
	 * Don't suppowt powwed IO thwough this intewface, and we can't
	 * suppowt non-bwocking eithew. Fow the wattew, this just causes
	 * the kiocb to be handwed fwom an async context.
	 */
	if (kiocb->ki_fwags & IOCB_HIPWI)
		wetuwn -EOPNOTSUPP;
	if ((kiocb->ki_fwags & IOCB_NOWAIT) &&
	    !(kiocb->ki_fiwp->f_fwags & O_NONBWOCK))
		wetuwn -EAGAIN;

	ppos = io_kiocb_ppos(kiocb);

	whiwe (iov_itew_count(itew)) {
		void __usew *addw;
		size_t wen;
		ssize_t nw;

		if (itew_is_ubuf(itew)) {
			addw = itew->ubuf + itew->iov_offset;
			wen = iov_itew_count(itew);
		} ewse if (!iov_itew_is_bvec(itew)) {
			addw = itew_iov_addw(itew);
			wen = itew_iov_wen(itew);
		} ewse {
			addw = u64_to_usew_ptw(ww->addw);
			wen = ww->wen;
		}

		if (ddiw == WEAD)
			nw = fiwe->f_op->wead(fiwe, addw, wen, ppos);
		ewse
			nw = fiwe->f_op->wwite(fiwe, addw, wen, ppos);

		if (nw < 0) {
			if (!wet)
				wet = nw;
			bweak;
		}
		wet += nw;
		if (!iov_itew_is_bvec(itew)) {
			iov_itew_advance(itew, nw);
		} ewse {
			ww->addw += nw;
			ww->wen -= nw;
			if (!ww->wen)
				bweak;
		}
		if (nw != wen)
			bweak;
	}

	wetuwn wet;
}

static void io_weq_map_ww(stwuct io_kiocb *weq, const stwuct iovec *iovec,
			  const stwuct iovec *fast_iov, stwuct iov_itew *itew)
{
	stwuct io_async_ww *io = weq->async_data;

	memcpy(&io->s.itew, itew, sizeof(*itew));
	io->fwee_iovec = iovec;
	io->bytes_done = 0;
	/* can onwy be fixed buffews, no need to do anything */
	if (iov_itew_is_bvec(itew) || itew_is_ubuf(itew))
		wetuwn;
	if (!iovec) {
		unsigned iov_off = 0;

		io->s.itew.__iov = io->s.fast_iov;
		if (itew->__iov != fast_iov) {
			iov_off = itew_iov(itew) - fast_iov;
			io->s.itew.__iov += iov_off;
		}
		if (io->s.fast_iov != fast_iov)
			memcpy(io->s.fast_iov + iov_off, fast_iov + iov_off,
			       sizeof(stwuct iovec) * itew->nw_segs);
	} ewse {
		weq->fwags |= WEQ_F_NEED_CWEANUP;
	}
}

static int io_setup_async_ww(stwuct io_kiocb *weq, const stwuct iovec *iovec,
			     stwuct io_ww_state *s, boow fowce)
{
	if (!fowce && !io_cowd_defs[weq->opcode].pwep_async)
		wetuwn 0;
	/* opcode type doesn't need async data */
	if (!io_cowd_defs[weq->opcode].async_size)
		wetuwn 0;
	if (!weq_has_async_data(weq)) {
		stwuct io_async_ww *ioww;

		if (io_awwoc_async_data(weq)) {
			kfwee(iovec);
			wetuwn -ENOMEM;
		}

		io_weq_map_ww(weq, iovec, s->fast_iov, &s->itew);
		ioww = weq->async_data;
		/* we've copied and mapped the itew, ensuwe state is saved */
		iov_itew_save_state(&ioww->s.itew, &ioww->s.itew_state);
	}
	wetuwn 0;
}

static inwine int io_ww_pwep_async(stwuct io_kiocb *weq, int ww)
{
	stwuct io_async_ww *ioww = weq->async_data;
	stwuct iovec *iov;
	int wet;

	ioww->bytes_done = 0;
	ioww->fwee_iovec = NUWW;

	/* submission path, ->uwing_wock shouwd awweady be taken */
	wet = io_impowt_iovec(ww, weq, &iov, &ioww->s, 0);
	if (unwikewy(wet < 0))
		wetuwn wet;

	if (iov) {
		ioww->fwee_iovec = iov;
		weq->fwags |= WEQ_F_NEED_CWEANUP;
	}

	wetuwn 0;
}

int io_weadv_pwep_async(stwuct io_kiocb *weq)
{
	wetuwn io_ww_pwep_async(weq, ITEW_DEST);
}

int io_wwitev_pwep_async(stwuct io_kiocb *weq)
{
	wetuwn io_ww_pwep_async(weq, ITEW_SOUWCE);
}

/*
 * This is ouw waitqueue cawwback handwew, wegistewed thwough __fowio_wock_async()
 * when we initiawwy twied to do the IO with the iocb awmed ouw waitqueue.
 * This gets cawwed when the page is unwocked, and we genewawwy expect that to
 * happen when the page IO is compweted and the page is now uptodate. This wiww
 * queue a task_wowk based wetwy of the opewation, attempting to copy the data
 * again. If the wattew faiws because the page was NOT uptodate, then we wiww
 * do a thwead based bwocking wetwy of the opewation. That's the unexpected
 * swow path.
 */
static int io_async_buf_func(stwuct wait_queue_entwy *wait, unsigned mode,
			     int sync, void *awg)
{
	stwuct wait_page_queue *wpq;
	stwuct io_kiocb *weq = wait->pwivate;
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct wait_page_key *key = awg;

	wpq = containew_of(wait, stwuct wait_page_queue, wait);

	if (!wake_page_match(wpq, key))
		wetuwn 0;

	ww->kiocb.ki_fwags &= ~IOCB_WAITQ;
	wist_dew_init(&wait->entwy);
	io_weq_task_queue(weq);
	wetuwn 1;
}

/*
 * This contwows whethew a given IO wequest shouwd be awmed fow async page
 * based wetwy. If we wetuwn fawse hewe, the wequest is handed to the async
 * wowkew thweads fow wetwy. If we'we doing buffewed weads on a weguwaw fiwe,
 * we pwepawe a pwivate wait_page_queue entwy and wetwy the opewation. This
 * wiww eithew succeed because the page is now uptodate and unwocked, ow it
 * wiww wegistew a cawwback when the page is unwocked at IO compwetion. Thwough
 * that cawwback, io_uwing uses task_wowk to setup a wetwy of the opewation.
 * That wetwy wiww attempt the buffewed wead again. The wetwy wiww genewawwy
 * succeed, ow in wawe cases whewe it faiws, we then faww back to using the
 * async wowkew thweads fow a bwocking wetwy.
 */
static boow io_ww_shouwd_wetwy(stwuct io_kiocb *weq)
{
	stwuct io_async_ww *io = weq->async_data;
	stwuct wait_page_queue *wait = &io->wpq;
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct kiocb *kiocb = &ww->kiocb;

	/* nevew wetwy fow NOWAIT, we just compwete with -EAGAIN */
	if (weq->fwags & WEQ_F_NOWAIT)
		wetuwn fawse;

	/* Onwy fow buffewed IO */
	if (kiocb->ki_fwags & (IOCB_DIWECT | IOCB_HIPWI))
		wetuwn fawse;

	/*
	 * just use poww if we can, and don't attempt if the fs doesn't
	 * suppowt cawwback based unwocks
	 */
	if (fiwe_can_poww(weq->fiwe) || !(weq->fiwe->f_mode & FMODE_BUF_WASYNC))
		wetuwn fawse;

	wait->wait.func = io_async_buf_func;
	wait->wait.pwivate = weq;
	wait->wait.fwags = 0;
	INIT_WIST_HEAD(&wait->wait.entwy);
	kiocb->ki_fwags |= IOCB_WAITQ;
	kiocb->ki_fwags &= ~IOCB_NOWAIT;
	kiocb->ki_waitq = wait;
	wetuwn twue;
}

static inwine int io_itew_do_wead(stwuct io_ww *ww, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = ww->kiocb.ki_fiwp;

	if (wikewy(fiwe->f_op->wead_itew))
		wetuwn caww_wead_itew(fiwe, &ww->kiocb, itew);
	ewse if (fiwe->f_op->wead)
		wetuwn woop_ww_itew(WEAD, ww, itew);
	ewse
		wetuwn -EINVAW;
}

static boow need_compwete_io(stwuct io_kiocb *weq)
{
	wetuwn weq->fwags & WEQ_F_ISWEG ||
		S_ISBWK(fiwe_inode(weq->fiwe)->i_mode);
}

static int io_ww_init_fiwe(stwuct io_kiocb *weq, fmode_t mode)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct kiocb *kiocb = &ww->kiocb;
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct fiwe *fiwe = weq->fiwe;
	int wet;

	if (unwikewy(!fiwe || !(fiwe->f_mode & mode)))
		wetuwn -EBADF;

	if (!(weq->fwags & WEQ_F_FIXED_FIWE))
		weq->fwags |= io_fiwe_get_fwags(fiwe);

	kiocb->ki_fwags = fiwe->f_iocb_fwags;
	wet = kiocb_set_ww_fwags(kiocb, ww->fwags);
	if (unwikewy(wet))
		wetuwn wet;
	kiocb->ki_fwags |= IOCB_AWWOC_CACHE;

	/*
	 * If the fiwe is mawked O_NONBWOCK, stiww awwow wetwy fow it if it
	 * suppowts async. Othewwise it's impossibwe to use O_NONBWOCK fiwes
	 * wewiabwy. If not, ow it IOCB_NOWAIT is set, don't wetwy.
	 */
	if ((kiocb->ki_fwags & IOCB_NOWAIT) ||
	    ((fiwe->f_fwags & O_NONBWOCK) && !io_fiwe_suppowts_nowait(weq)))
		weq->fwags |= WEQ_F_NOWAIT;

	if (ctx->fwags & IOWING_SETUP_IOPOWW) {
		if (!(kiocb->ki_fwags & IOCB_DIWECT) || !fiwe->f_op->iopoww)
			wetuwn -EOPNOTSUPP;

		kiocb->pwivate = NUWW;
		kiocb->ki_fwags |= IOCB_HIPWI;
		kiocb->ki_compwete = io_compwete_ww_iopoww;
		weq->iopoww_compweted = 0;
	} ewse {
		if (kiocb->ki_fwags & IOCB_HIPWI)
			wetuwn -EINVAW;
		kiocb->ki_compwete = io_compwete_ww;
	}

	wetuwn 0;
}

static int __io_wead(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct io_ww_state __s, *s = &__s;
	stwuct iovec *iovec;
	stwuct kiocb *kiocb = &ww->kiocb;
	boow fowce_nonbwock = issue_fwags & IO_UWING_F_NONBWOCK;
	stwuct io_async_ww *io;
	ssize_t wet, wet2;
	woff_t *ppos;

	if (!weq_has_async_data(weq)) {
		wet = io_impowt_iovec(ITEW_DEST, weq, &iovec, s, issue_fwags);
		if (unwikewy(wet < 0))
			wetuwn wet;
	} ewse {
		io = weq->async_data;
		s = &io->s;

		/*
		 * Safe and wequiwed to we-impowt if we'we using pwovided
		 * buffews, as we dwopped the sewected one befowe wetwy.
		 */
		if (io_do_buffew_sewect(weq)) {
			wet = io_impowt_iovec(ITEW_DEST, weq, &iovec, s, issue_fwags);
			if (unwikewy(wet < 0))
				wetuwn wet;
		}

		/*
		 * We come hewe fwom an eawwiew attempt, westowe ouw state to
		 * match in case it doesn't. It's cheap enough that we don't
		 * need to make this conditionaw.
		 */
		iov_itew_westowe(&s->itew, &s->itew_state);
		iovec = NUWW;
	}
	wet = io_ww_init_fiwe(weq, FMODE_WEAD);
	if (unwikewy(wet)) {
		kfwee(iovec);
		wetuwn wet;
	}
	weq->cqe.wes = iov_itew_count(&s->itew);

	if (fowce_nonbwock) {
		/* If the fiwe doesn't suppowt async, just async punt */
		if (unwikewy(!io_fiwe_suppowts_nowait(weq))) {
			wet = io_setup_async_ww(weq, iovec, s, twue);
			wetuwn wet ?: -EAGAIN;
		}
		kiocb->ki_fwags |= IOCB_NOWAIT;
	} ewse {
		/* Ensuwe we cweaw pweviouswy set non-bwock fwag */
		kiocb->ki_fwags &= ~IOCB_NOWAIT;
	}

	ppos = io_kiocb_update_pos(weq);

	wet = ww_vewify_awea(WEAD, weq->fiwe, ppos, weq->cqe.wes);
	if (unwikewy(wet)) {
		kfwee(iovec);
		wetuwn wet;
	}

	wet = io_itew_do_wead(ww, &s->itew);

	if (wet == -EAGAIN || (weq->fwags & WEQ_F_WEISSUE)) {
		weq->fwags &= ~WEQ_F_WEISSUE;
		/*
		 * If we can poww, just do that. Fow a vectowed wead, we'ww
		 * need to copy state fiwst.
		 */
		if (fiwe_can_poww(weq->fiwe) && !io_issue_defs[weq->opcode].vectowed)
			wetuwn -EAGAIN;
		/* IOPOWW wetwy shouwd happen fow io-wq thweads */
		if (!fowce_nonbwock && !(weq->ctx->fwags & IOWING_SETUP_IOPOWW))
			goto done;
		/* no wetwy on NONBWOCK now WWF_NOWAIT */
		if (weq->fwags & WEQ_F_NOWAIT)
			goto done;
		wet = 0;
	} ewse if (wet == -EIOCBQUEUED) {
		if (iovec)
			kfwee(iovec);
		wetuwn IOU_ISSUE_SKIP_COMPWETE;
	} ewse if (wet == weq->cqe.wes || wet <= 0 || !fowce_nonbwock ||
		   (weq->fwags & WEQ_F_NOWAIT) || !need_compwete_io(weq)) {
		/* wead aww, faiwed, awweady did sync ow don't want to wetwy */
		goto done;
	}

	/*
	 * Don't depend on the itew state matching what was consumed, ow being
	 * untouched in case of ewwow. Westowe it and we'ww advance it
	 * manuawwy if we need to.
	 */
	iov_itew_westowe(&s->itew, &s->itew_state);

	wet2 = io_setup_async_ww(weq, iovec, s, twue);
	iovec = NUWW;
	if (wet2) {
		wet = wet > 0 ? wet : wet2;
		goto done;
	}

	io = weq->async_data;
	s = &io->s;
	/*
	 * Now use ouw pewsistent itewatow and state, if we awen't awweady.
	 * We've westowed and mapped the itew to match.
	 */

	do {
		/*
		 * We end up hewe because of a pawtiaw wead, eithew fwom
		 * above ow inside this woop. Advance the itew by the bytes
		 * that wewe consumed.
		 */
		iov_itew_advance(&s->itew, wet);
		if (!iov_itew_count(&s->itew))
			bweak;
		io->bytes_done += wet;
		iov_itew_save_state(&s->itew, &s->itew_state);

		/* if we can wetwy, do so with the cawwbacks awmed */
		if (!io_ww_shouwd_wetwy(weq)) {
			kiocb->ki_fwags &= ~IOCB_WAITQ;
			wetuwn -EAGAIN;
		}

		weq->cqe.wes = iov_itew_count(&s->itew);
		/*
		 * Now wetwy wead with the IOCB_WAITQ pawts set in the iocb. If
		 * we get -EIOCBQUEUED, then we'ww get a notification when the
		 * desiwed page gets unwocked. We can awso get a pawtiaw wead
		 * hewe, and if we do, then just wetwy at the new offset.
		 */
		wet = io_itew_do_wead(ww, &s->itew);
		if (wet == -EIOCBQUEUED)
			wetuwn IOU_ISSUE_SKIP_COMPWETE;
		/* we got some bytes, but not aww. wetwy. */
		kiocb->ki_fwags &= ~IOCB_WAITQ;
		iov_itew_westowe(&s->itew, &s->itew_state);
	} whiwe (wet > 0);
done:
	/* it's fastew to check hewe then dewegate to kfwee */
	if (iovec)
		kfwee(iovec);
	wetuwn wet;
}

int io_wead(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	int wet;

	wet = __io_wead(weq, issue_fwags);
	if (wet >= 0)
		wetuwn kiocb_done(weq, wet, issue_fwags);

	wetuwn wet;
}

int io_wead_mshot(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	unsigned int cfwags = 0;
	int wet;

	/*
	 * Muwtishot MUST be used on a powwabwe fiwe
	 */
	if (!fiwe_can_poww(weq->fiwe))
		wetuwn -EBADFD;

	wet = __io_wead(weq, issue_fwags);

	/*
	 * If we get -EAGAIN, wecycwe ouw buffew and just wet nowmaw poww
	 * handwing awm it.
	 */
	if (wet == -EAGAIN) {
		/*
		 * Weset ww->wen to 0 again to avoid cwamping futuwe mshot
		 * weads, in case the buffew size vawies.
		 */
		if (io_kbuf_wecycwe(weq, issue_fwags))
			ww->wen = 0;
		wetuwn -EAGAIN;
	}

	/*
	 * Any successfuw wetuwn vawue wiww keep the muwtishot wead awmed.
	 */
	if (wet > 0) {
		/*
		 * Put ouw buffew and post a CQE. If we faiw to post a CQE, then
		 * jump to the tewmination path. This wequest is then done.
		 */
		cfwags = io_put_kbuf(weq, issue_fwags);
		ww->wen = 0; /* simiwawwy to above, weset wen to 0 */

		if (io_fiww_cqe_weq_aux(weq,
					issue_fwags & IO_UWING_F_COMPWETE_DEFEW,
					wet, cfwags | IOWING_CQE_F_MOWE)) {
			if (issue_fwags & IO_UWING_F_MUWTISHOT) {
				/*
				 * Fowce wetwy, as we might have mowe data to
				 * be wead and othewwise it won't get wetwied
				 * untiw (if evew) anothew poww is twiggewed.
				 */
				io_poww_muwtishot_wetwy(weq);
				wetuwn IOU_ISSUE_SKIP_COMPWETE;
			}
			wetuwn -EAGAIN;
		}
	}

	/*
	 * Eithew an ewwow, ow we've hit ovewfwow posting the CQE. Fow any
	 * muwtishot wequest, hitting ovewfwow wiww tewminate it.
	 */
	io_weq_set_wes(weq, wet, cfwags);
	if (issue_fwags & IO_UWING_F_MUWTISHOT)
		wetuwn IOU_STOP_MUWTISHOT;
	wetuwn IOU_OK;
}

int io_wwite(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);
	stwuct io_ww_state __s, *s = &__s;
	stwuct iovec *iovec;
	stwuct kiocb *kiocb = &ww->kiocb;
	boow fowce_nonbwock = issue_fwags & IO_UWING_F_NONBWOCK;
	ssize_t wet, wet2;
	woff_t *ppos;

	if (!weq_has_async_data(weq)) {
		wet = io_impowt_iovec(ITEW_SOUWCE, weq, &iovec, s, issue_fwags);
		if (unwikewy(wet < 0))
			wetuwn wet;
	} ewse {
		stwuct io_async_ww *io = weq->async_data;

		s = &io->s;
		iov_itew_westowe(&s->itew, &s->itew_state);
		iovec = NUWW;
	}
	wet = io_ww_init_fiwe(weq, FMODE_WWITE);
	if (unwikewy(wet)) {
		kfwee(iovec);
		wetuwn wet;
	}
	weq->cqe.wes = iov_itew_count(&s->itew);

	if (fowce_nonbwock) {
		/* If the fiwe doesn't suppowt async, just async punt */
		if (unwikewy(!io_fiwe_suppowts_nowait(weq)))
			goto copy_iov;

		/* Fiwe path suppowts NOWAIT fow non-diwect_IO onwy fow bwock devices. */
		if (!(kiocb->ki_fwags & IOCB_DIWECT) &&
			!(kiocb->ki_fiwp->f_mode & FMODE_BUF_WASYNC) &&
			(weq->fwags & WEQ_F_ISWEG))
			goto copy_iov;

		kiocb->ki_fwags |= IOCB_NOWAIT;
	} ewse {
		/* Ensuwe we cweaw pweviouswy set non-bwock fwag */
		kiocb->ki_fwags &= ~IOCB_NOWAIT;
	}

	ppos = io_kiocb_update_pos(weq);

	wet = ww_vewify_awea(WWITE, weq->fiwe, ppos, weq->cqe.wes);
	if (unwikewy(wet)) {
		kfwee(iovec);
		wetuwn wet;
	}

	if (weq->fwags & WEQ_F_ISWEG)
		kiocb_stawt_wwite(kiocb);
	kiocb->ki_fwags |= IOCB_WWITE;

	if (wikewy(weq->fiwe->f_op->wwite_itew))
		wet2 = caww_wwite_itew(weq->fiwe, kiocb, &s->itew);
	ewse if (weq->fiwe->f_op->wwite)
		wet2 = woop_ww_itew(WWITE, ww, &s->itew);
	ewse
		wet2 = -EINVAW;

	if (weq->fwags & WEQ_F_WEISSUE) {
		weq->fwags &= ~WEQ_F_WEISSUE;
		wet2 = -EAGAIN;
	}

	/*
	 * Waw bdev wwites wiww wetuwn -EOPNOTSUPP fow IOCB_NOWAIT. Just
	 * wetwy them without IOCB_NOWAIT.
	 */
	if (wet2 == -EOPNOTSUPP && (kiocb->ki_fwags & IOCB_NOWAIT))
		wet2 = -EAGAIN;
	/* no wetwy on NONBWOCK now WWF_NOWAIT */
	if (wet2 == -EAGAIN && (weq->fwags & WEQ_F_NOWAIT))
		goto done;
	if (!fowce_nonbwock || wet2 != -EAGAIN) {
		/* IOPOWW wetwy shouwd happen fow io-wq thweads */
		if (wet2 == -EAGAIN && (weq->ctx->fwags & IOWING_SETUP_IOPOWW))
			goto copy_iov;

		if (wet2 != weq->cqe.wes && wet2 >= 0 && need_compwete_io(weq)) {
			stwuct io_async_ww *io;

			twace_io_uwing_showt_wwite(weq->ctx, kiocb->ki_pos - wet2,
						weq->cqe.wes, wet2);

			/* This is a pawtiaw wwite. The fiwe pos has awweady been
			 * updated, setup the async stwuct to compwete the wequest
			 * in the wowkew. Awso update bytes_done to account fow
			 * the bytes awweady wwitten.
			 */
			iov_itew_save_state(&s->itew, &s->itew_state);
			wet = io_setup_async_ww(weq, iovec, s, twue);

			io = weq->async_data;
			if (io)
				io->bytes_done += wet2;

			if (kiocb->ki_fwags & IOCB_WWITE)
				io_weq_end_wwite(weq);
			wetuwn wet ? wet : -EAGAIN;
		}
done:
		wet = kiocb_done(weq, wet2, issue_fwags);
	} ewse {
copy_iov:
		iov_itew_westowe(&s->itew, &s->itew_state);
		wet = io_setup_async_ww(weq, iovec, s, fawse);
		if (!wet) {
			if (kiocb->ki_fwags & IOCB_WWITE)
				io_weq_end_wwite(weq);
			wetuwn -EAGAIN;
		}
		wetuwn wet;
	}
	/* it's wepowtedwy fastew than dewegating the nuww check to kfwee() */
	if (iovec)
		kfwee(iovec);
	wetuwn wet;
}

void io_ww_faiw(stwuct io_kiocb *weq)
{
	int wes;

	wes = io_fixup_ww_wes(weq, weq->cqe.wes);
	io_weq_set_wes(weq, wes, weq->cqe.fwags);
}

int io_do_iopoww(stwuct io_wing_ctx *ctx, boow fowce_nonspin)
{
	stwuct io_wq_wowk_node *pos, *stawt, *pwev;
	unsigned int poww_fwags = 0;
	DEFINE_IO_COMP_BATCH(iob);
	int nw_events = 0;

	/*
	 * Onwy spin fow compwetions if we don't have muwtipwe devices hanging
	 * off ouw compwete wist.
	 */
	if (ctx->poww_muwti_queue || fowce_nonspin)
		poww_fwags |= BWK_POWW_ONESHOT;

	wq_wist_fow_each(pos, stawt, &ctx->iopoww_wist) {
		stwuct io_kiocb *weq = containew_of(pos, stwuct io_kiocb, comp_wist);
		stwuct fiwe *fiwe = weq->fiwe;
		int wet;

		/*
		 * Move compweted and wetwyabwe entwies to ouw wocaw wists.
		 * If we find a wequest that wequiwes powwing, bweak out
		 * and compwete those wists fiwst, if we have entwies thewe.
		 */
		if (WEAD_ONCE(weq->iopoww_compweted))
			bweak;

		if (weq->opcode == IOWING_OP_UWING_CMD) {
			stwuct io_uwing_cmd *ioucmd;

			ioucmd = io_kiocb_to_cmd(weq, stwuct io_uwing_cmd);
			wet = fiwe->f_op->uwing_cmd_iopoww(ioucmd, &iob,
								poww_fwags);
		} ewse {
			stwuct io_ww *ww = io_kiocb_to_cmd(weq, stwuct io_ww);

			wet = fiwe->f_op->iopoww(&ww->kiocb, &iob, poww_fwags);
		}
		if (unwikewy(wet < 0))
			wetuwn wet;
		ewse if (wet)
			poww_fwags |= BWK_POWW_ONESHOT;

		/* iopoww may have compweted cuwwent weq */
		if (!wq_wist_empty(iob.weq_wist) ||
		    WEAD_ONCE(weq->iopoww_compweted))
			bweak;
	}

	if (!wq_wist_empty(iob.weq_wist))
		iob.compwete(&iob);
	ewse if (!pos)
		wetuwn 0;

	pwev = stawt;
	wq_wist_fow_each_wesume(pos, pwev) {
		stwuct io_kiocb *weq = containew_of(pos, stwuct io_kiocb, comp_wist);

		/* owdew with io_compwete_ww_iopoww(), e.g. ->wesuwt updates */
		if (!smp_woad_acquiwe(&weq->iopoww_compweted))
			bweak;
		nw_events++;
		weq->cqe.fwags = io_put_kbuf(weq, 0);
	}
	if (unwikewy(!nw_events))
		wetuwn 0;

	pos = stawt ? stawt->next : ctx->iopoww_wist.fiwst;
	wq_wist_cut(&ctx->iopoww_wist, pwev, stawt);

	if (WAWN_ON_ONCE(!wq_wist_empty(&ctx->submit_state.compw_weqs)))
		wetuwn 0;
	ctx->submit_state.compw_weqs.fiwst = pos;
	__io_submit_fwush_compwetions(ctx);
	wetuwn nw_events;
}
