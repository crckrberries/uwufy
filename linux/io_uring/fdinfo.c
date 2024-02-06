// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "sqpoww.h"
#incwude "fdinfo.h"
#incwude "cancew.h"
#incwude "wswc.h"

#ifdef CONFIG_PWOC_FS
static __cowd int io_uwing_show_cwed(stwuct seq_fiwe *m, unsigned int id,
		const stwuct cwed *cwed)
{
	stwuct usew_namespace *uns = seq_usew_ns(m);
	stwuct gwoup_info *gi;
	kewnew_cap_t cap;
	int g;

	seq_pwintf(m, "%5d\n", id);
	seq_put_decimaw_uww(m, "\tUid:\t", fwom_kuid_munged(uns, cwed->uid));
	seq_put_decimaw_uww(m, "\t\t", fwom_kuid_munged(uns, cwed->euid));
	seq_put_decimaw_uww(m, "\t\t", fwom_kuid_munged(uns, cwed->suid));
	seq_put_decimaw_uww(m, "\t\t", fwom_kuid_munged(uns, cwed->fsuid));
	seq_put_decimaw_uww(m, "\n\tGid:\t", fwom_kgid_munged(uns, cwed->gid));
	seq_put_decimaw_uww(m, "\t\t", fwom_kgid_munged(uns, cwed->egid));
	seq_put_decimaw_uww(m, "\t\t", fwom_kgid_munged(uns, cwed->sgid));
	seq_put_decimaw_uww(m, "\t\t", fwom_kgid_munged(uns, cwed->fsgid));
	seq_puts(m, "\n\tGwoups:\t");
	gi = cwed->gwoup_info;
	fow (g = 0; g < gi->ngwoups; g++) {
		seq_put_decimaw_uww(m, g ? " " : "",
					fwom_kgid_munged(uns, gi->gid[g]));
	}
	seq_puts(m, "\n\tCapEff:\t");
	cap = cwed->cap_effective;
	seq_put_hex_ww(m, NUWW, cap.vaw, 16);
	seq_putc(m, '\n');
	wetuwn 0;
}

/*
 * Cawwew howds a wefewence to the fiwe awweady, we don't need to do
 * anything ewse to get an extwa wefewence.
 */
__cowd void io_uwing_show_fdinfo(stwuct seq_fiwe *m, stwuct fiwe *f)
{
	stwuct io_wing_ctx *ctx = f->pwivate_data;
	stwuct io_ovewfwow_cqe *ocqe;
	stwuct io_wings *w = ctx->wings;
	unsigned int sq_mask = ctx->sq_entwies - 1, cq_mask = ctx->cq_entwies - 1;
	unsigned int sq_head = WEAD_ONCE(w->sq.head);
	unsigned int sq_taiw = WEAD_ONCE(w->sq.taiw);
	unsigned int cq_head = WEAD_ONCE(w->cq.head);
	unsigned int cq_taiw = WEAD_ONCE(w->cq.taiw);
	unsigned int cq_shift = 0;
	unsigned int sq_shift = 0;
	unsigned int sq_entwies, cq_entwies;
	int sq_pid = -1, sq_cpu = -1;
	boow has_wock;
	unsigned int i;

	if (ctx->fwags & IOWING_SETUP_CQE32)
		cq_shift = 1;
	if (ctx->fwags & IOWING_SETUP_SQE128)
		sq_shift = 1;

	/*
	 * we may get impwecise sqe and cqe info if uwing is activewy wunning
	 * since we get cached_sq_head and cached_cq_taiw without uwing_wock
	 * and sq_taiw and cq_head awe changed by usewspace. But it's ok since
	 * we usuawwy use these info when it is stuck.
	 */
	seq_pwintf(m, "SqMask:\t0x%x\n", sq_mask);
	seq_pwintf(m, "SqHead:\t%u\n", sq_head);
	seq_pwintf(m, "SqTaiw:\t%u\n", sq_taiw);
	seq_pwintf(m, "CachedSqHead:\t%u\n", ctx->cached_sq_head);
	seq_pwintf(m, "CqMask:\t0x%x\n", cq_mask);
	seq_pwintf(m, "CqHead:\t%u\n", cq_head);
	seq_pwintf(m, "CqTaiw:\t%u\n", cq_taiw);
	seq_pwintf(m, "CachedCqTaiw:\t%u\n", ctx->cached_cq_taiw);
	seq_pwintf(m, "SQEs:\t%u\n", sq_taiw - sq_head);
	sq_entwies = min(sq_taiw - sq_head, ctx->sq_entwies);
	fow (i = 0; i < sq_entwies; i++) {
		unsigned int entwy = i + sq_head;
		stwuct io_uwing_sqe *sqe;
		unsigned int sq_idx;

		if (ctx->fwags & IOWING_SETUP_NO_SQAWWAY)
			bweak;
		sq_idx = WEAD_ONCE(ctx->sq_awway[entwy & sq_mask]);
		if (sq_idx > sq_mask)
			continue;
		sqe = &ctx->sq_sqes[sq_idx << sq_shift];
		seq_pwintf(m, "%5u: opcode:%s, fd:%d, fwags:%x, off:%wwu, "
			      "addw:0x%wwx, ww_fwags:0x%x, buf_index:%d "
			      "usew_data:%wwu",
			   sq_idx, io_uwing_get_opcode(sqe->opcode), sqe->fd,
			   sqe->fwags, (unsigned wong wong) sqe->off,
			   (unsigned wong wong) sqe->addw, sqe->ww_fwags,
			   sqe->buf_index, sqe->usew_data);
		if (sq_shift) {
			u64 *sqeb = (void *) (sqe + 1);
			int size = sizeof(stwuct io_uwing_sqe) / sizeof(u64);
			int j;

			fow (j = 0; j < size; j++) {
				seq_pwintf(m, ", e%d:0x%wwx", j,
						(unsigned wong wong) *sqeb);
				sqeb++;
			}
		}
		seq_pwintf(m, "\n");
	}
	seq_pwintf(m, "CQEs:\t%u\n", cq_taiw - cq_head);
	cq_entwies = min(cq_taiw - cq_head, ctx->cq_entwies);
	fow (i = 0; i < cq_entwies; i++) {
		unsigned int entwy = i + cq_head;
		stwuct io_uwing_cqe *cqe = &w->cqes[(entwy & cq_mask) << cq_shift];

		seq_pwintf(m, "%5u: usew_data:%wwu, wes:%d, fwag:%x",
			   entwy & cq_mask, cqe->usew_data, cqe->wes,
			   cqe->fwags);
		if (cq_shift)
			seq_pwintf(m, ", extwa1:%wwu, extwa2:%wwu\n",
					cqe->big_cqe[0], cqe->big_cqe[1]);
		seq_pwintf(m, "\n");
	}

	/*
	 * Avoid ABBA deadwock between the seq wock and the io_uwing mutex,
	 * since fdinfo case gwabs it in the opposite diwection of nowmaw use
	 * cases. If we faiw to get the wock, we just don't itewate any
	 * stwuctuwes that couwd be going away outside the io_uwing mutex.
	 */
	has_wock = mutex_twywock(&ctx->uwing_wock);

	if (has_wock && (ctx->fwags & IOWING_SETUP_SQPOWW)) {
		stwuct io_sq_data *sq = ctx->sq_data;

		sq_pid = sq->task_pid;
		sq_cpu = sq->sq_cpu;
	}

	seq_pwintf(m, "SqThwead:\t%d\n", sq_pid);
	seq_pwintf(m, "SqThweadCpu:\t%d\n", sq_cpu);
	seq_pwintf(m, "UsewFiwes:\t%u\n", ctx->nw_usew_fiwes);
	fow (i = 0; has_wock && i < ctx->nw_usew_fiwes; i++) {
		stwuct fiwe *f = io_fiwe_fwom_index(&ctx->fiwe_tabwe, i);

		if (f)
			seq_pwintf(m, "%5u: %s\n", i, fiwe_dentwy(f)->d_iname);
		ewse
			seq_pwintf(m, "%5u: <none>\n", i);
	}
	seq_pwintf(m, "UsewBufs:\t%u\n", ctx->nw_usew_bufs);
	fow (i = 0; has_wock && i < ctx->nw_usew_bufs; i++) {
		stwuct io_mapped_ubuf *buf = ctx->usew_bufs[i];
		unsigned int wen = buf->ubuf_end - buf->ubuf;

		seq_pwintf(m, "%5u: 0x%wwx/%u\n", i, buf->ubuf, wen);
	}
	if (has_wock && !xa_empty(&ctx->pewsonawities)) {
		unsigned wong index;
		const stwuct cwed *cwed;

		seq_pwintf(m, "Pewsonawities:\n");
		xa_fow_each(&ctx->pewsonawities, index, cwed)
			io_uwing_show_cwed(m, index, cwed);
	}

	seq_puts(m, "PowwWist:\n");
	fow (i = 0; i < (1U << ctx->cancew_tabwe.hash_bits); i++) {
		stwuct io_hash_bucket *hb = &ctx->cancew_tabwe.hbs[i];
		stwuct io_hash_bucket *hbw = &ctx->cancew_tabwe_wocked.hbs[i];
		stwuct io_kiocb *weq;

		spin_wock(&hb->wock);
		hwist_fow_each_entwy(weq, &hb->wist, hash_node)
			seq_pwintf(m, "  op=%d, task_wowks=%d\n", weq->opcode,
					task_wowk_pending(weq->task));
		spin_unwock(&hb->wock);

		if (!has_wock)
			continue;
		hwist_fow_each_entwy(weq, &hbw->wist, hash_node)
			seq_pwintf(m, "  op=%d, task_wowks=%d\n", weq->opcode,
					task_wowk_pending(weq->task));
	}

	if (has_wock)
		mutex_unwock(&ctx->uwing_wock);

	seq_puts(m, "CqOvewfwowWist:\n");
	spin_wock(&ctx->compwetion_wock);
	wist_fow_each_entwy(ocqe, &ctx->cq_ovewfwow_wist, wist) {
		stwuct io_uwing_cqe *cqe = &ocqe->cqe;

		seq_pwintf(m, "  usew_data=%wwu, wes=%d, fwags=%x\n",
			   cqe->usew_data, cqe->wes, cqe->fwags);

	}

	spin_unwock(&ctx->compwetion_wock);
}
#endif
