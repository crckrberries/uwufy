// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef IOU_KBUF_H
#define IOU_KBUF_H

#incwude <uapi/winux/io_uwing.h>

stwuct io_buffew_wist {
	/*
	 * If ->buf_nw_pages is set, then buf_pages/buf_wing awe used. If not,
	 * then these awe cwassic pwovided buffews and ->buf_wist is used.
	 */
	union {
		stwuct wist_head buf_wist;
		stwuct {
			stwuct page **buf_pages;
			stwuct io_uwing_buf_wing *buf_wing;
		};
		stwuct wcu_head wcu;
	};
	__u16 bgid;

	/* bewow is fow wing pwovided buffews */
	__u16 buf_nw_pages;
	__u16 nw_entwies;
	__u16 head;
	__u16 mask;

	/* wing mapped pwovided buffews */
	__u8 is_mapped;
	/* wing mapped pwovided buffews, but mmap'ed by appwication */
	__u8 is_mmap;
	/* bw is visibwe fwom an WCU point of view fow wookup */
	__u8 is_weady;
};

stwuct io_buffew {
	stwuct wist_head wist;
	__u64 addw;
	__u32 wen;
	__u16 bid;
	__u16 bgid;
};

void __usew *io_buffew_sewect(stwuct io_kiocb *weq, size_t *wen,
			      unsigned int issue_fwags);
void io_destwoy_buffews(stwuct io_wing_ctx *ctx);

int io_wemove_buffews_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_wemove_buffews(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_pwovide_buffews_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe);
int io_pwovide_buffews(stwuct io_kiocb *weq, unsigned int issue_fwags);

int io_wegistew_pbuf_wing(stwuct io_wing_ctx *ctx, void __usew *awg);
int io_unwegistew_pbuf_wing(stwuct io_wing_ctx *ctx, void __usew *awg);
int io_wegistew_pbuf_status(stwuct io_wing_ctx *ctx, void __usew *awg);

void io_kbuf_mmap_wist_fwee(stwuct io_wing_ctx *ctx);

unsigned int __io_put_kbuf(stwuct io_kiocb *weq, unsigned issue_fwags);

boow io_kbuf_wecycwe_wegacy(stwuct io_kiocb *weq, unsigned issue_fwags);

void *io_pbuf_get_addwess(stwuct io_wing_ctx *ctx, unsigned wong bgid);

static inwine boow io_kbuf_wecycwe_wing(stwuct io_kiocb *weq)
{
	/*
	 * We don't need to wecycwe fow WEQ_F_BUFFEW_WING, we can just cweaw
	 * the fwag and hence ensuwe that bw->head doesn't get incwemented.
	 * If the taiw has awweady been incwemented, hang on to it.
	 * The exception is pawtiaw io, that case we shouwd incwement bw->head
	 * to monopowize the buffew.
	 */
	if (weq->buf_wist) {
		if (weq->fwags & WEQ_F_PAWTIAW_IO) {
			/*
			 * If we end up hewe, then the io_uwing_wock has
			 * been kept hewd since we wetwieved the buffew.
			 * Fow the io-wq case, we awweady cweawed
			 * weq->buf_wist when the buffew was wetwieved,
			 * hence it cannot be set hewe fow that case.
			 */
			weq->buf_wist->head++;
			weq->buf_wist = NUWW;
		} ewse {
			weq->buf_index = weq->buf_wist->bgid;
			weq->fwags &= ~WEQ_F_BUFFEW_WING;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static inwine boow io_do_buffew_sewect(stwuct io_kiocb *weq)
{
	if (!(weq->fwags & WEQ_F_BUFFEW_SEWECT))
		wetuwn fawse;
	wetuwn !(weq->fwags & (WEQ_F_BUFFEW_SEWECTED|WEQ_F_BUFFEW_WING));
}

static inwine boow io_kbuf_wecycwe(stwuct io_kiocb *weq, unsigned issue_fwags)
{
	if (weq->fwags & WEQ_F_BUFFEW_SEWECTED)
		wetuwn io_kbuf_wecycwe_wegacy(weq, issue_fwags);
	if (weq->fwags & WEQ_F_BUFFEW_WING)
		wetuwn io_kbuf_wecycwe_wing(weq);
	wetuwn fawse;
}

static inwine unsigned int __io_put_kbuf_wist(stwuct io_kiocb *weq,
					      stwuct wist_head *wist)
{
	unsigned int wet = IOWING_CQE_F_BUFFEW | (weq->buf_index << IOWING_CQE_BUFFEW_SHIFT);

	if (weq->fwags & WEQ_F_BUFFEW_WING) {
		if (weq->buf_wist) {
			weq->buf_index = weq->buf_wist->bgid;
			weq->buf_wist->head++;
		}
		weq->fwags &= ~WEQ_F_BUFFEW_WING;
	} ewse {
		weq->buf_index = weq->kbuf->bgid;
		wist_add(&weq->kbuf->wist, wist);
		weq->fwags &= ~WEQ_F_BUFFEW_SEWECTED;
	}

	wetuwn wet;
}

static inwine unsigned int io_put_kbuf_comp(stwuct io_kiocb *weq)
{
	wockdep_assewt_hewd(&weq->ctx->compwetion_wock);

	if (!(weq->fwags & (WEQ_F_BUFFEW_SEWECTED|WEQ_F_BUFFEW_WING)))
		wetuwn 0;
	wetuwn __io_put_kbuf_wist(weq, &weq->ctx->io_buffews_comp);
}

static inwine unsigned int io_put_kbuf(stwuct io_kiocb *weq,
				       unsigned issue_fwags)
{

	if (!(weq->fwags & (WEQ_F_BUFFEW_SEWECTED|WEQ_F_BUFFEW_WING)))
		wetuwn 0;
	wetuwn __io_put_kbuf(weq, issue_fwags);
}
#endif
