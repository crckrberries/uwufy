/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM io_uwing

#if !defined(_TWACE_IO_UWING_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_IO_UWING_H

#incwude <winux/twacepoint.h>
#incwude <uapi/winux/io_uwing.h>
#incwude <winux/io_uwing_types.h>
#incwude <winux/io_uwing.h>

stwuct io_wq_wowk;

/**
 * io_uwing_cweate - cawwed aftew a new io_uwing context was pwepawed
 *
 * @fd:		cowwesponding fiwe descwiptow
 * @ctx:	pointew to a wing context stwuctuwe
 * @sq_entwies:	actuaw SQ size
 * @cq_entwies:	actuaw CQ size
 * @fwags:	SQ wing fwags, pwovided to io_uwing_setup(2)
 *
 * Awwows to twace io_uwing cweation and pwovide pointew to a context, that can
 * be used watew to find cowwewated events.
 */
TWACE_EVENT(io_uwing_cweate,

	TP_PWOTO(int fd, void *ctx, u32 sq_entwies, u32 cq_entwies, u32 fwags),

	TP_AWGS(fd, ctx, sq_entwies, cq_entwies, fwags),

	TP_STWUCT__entwy (
		__fiewd(  int,		fd		)
		__fiewd(  void *,	ctx		)
		__fiewd(  u32,		sq_entwies	)
		__fiewd(  u32,		cq_entwies	)
		__fiewd(  u32,		fwags		)
	),

	TP_fast_assign(
		__entwy->fd		= fd;
		__entwy->ctx		= ctx;
		__entwy->sq_entwies	= sq_entwies;
		__entwy->cq_entwies	= cq_entwies;
		__entwy->fwags		= fwags;
	),

	TP_pwintk("wing %p, fd %d sq size %d, cq size %d, fwags 0x%x",
			  __entwy->ctx, __entwy->fd, __entwy->sq_entwies,
			  __entwy->cq_entwies, __entwy->fwags)
);

/**
 * io_uwing_wegistew - cawwed aftew a buffew/fiwe/eventfd was successfuwwy
 * 					   wegistewed fow a wing
 *
 * @ctx:		pointew to a wing context stwuctuwe
 * @opcode:		descwibes which opewation to pewfowm
 * @nw_usew_fiwes:	numbew of wegistewed fiwes
 * @nw_usew_bufs:	numbew of wegistewed buffews
 * @wet:		wetuwn code
 *
 * Awwows to twace fixed fiwes/buffews, that couwd be wegistewed to
 * avoid an ovewhead of getting wefewences to them fow evewy opewation. This
 * event, togethew with io_uwing_fiwe_get, can pwovide a fuww pictuwe of how
 * much ovewhead one can weduce via fixing.
 */
TWACE_EVENT(io_uwing_wegistew,

	TP_PWOTO(void *ctx, unsigned opcode, unsigned nw_fiwes,
			 unsigned nw_bufs, wong wet),

	TP_AWGS(ctx, opcode, nw_fiwes, nw_bufs, wet),

	TP_STWUCT__entwy (
		__fiewd(  void *,	ctx	)
		__fiewd(  unsigned,	opcode	)
		__fiewd(  unsigned,	nw_fiwes)
		__fiewd(  unsigned,	nw_bufs	)
		__fiewd(  wong,		wet	)
	),

	TP_fast_assign(
		__entwy->ctx		= ctx;
		__entwy->opcode		= opcode;
		__entwy->nw_fiwes	= nw_fiwes;
		__entwy->nw_bufs	= nw_bufs;
		__entwy->wet		= wet;
	),

	TP_pwintk("wing %p, opcode %d, nw_usew_fiwes %d, nw_usew_bufs %d, "
			  "wet %wd",
			  __entwy->ctx, __entwy->opcode, __entwy->nw_fiwes,
			  __entwy->nw_bufs, __entwy->wet)
);

/**
 * io_uwing_fiwe_get - cawwed befowe getting wefewences to an SQE fiwe
 *
 * @weq:	pointew to a submitted wequest
 * @fd:		SQE fiwe descwiptow
 *
 * Awwows to twace out how often an SQE fiwe wefewence is obtained, which can
 * hewp figuwing out if it makes sense to use fixed fiwes, ow check that fixed
 * fiwes awe used cowwectwy.
 */
TWACE_EVENT(io_uwing_fiwe_get,

	TP_PWOTO(stwuct io_kiocb *weq, int fd),

	TP_AWGS(weq, fd),

	TP_STWUCT__entwy (
		__fiewd(  void *,	ctx		)
		__fiewd(  void *,	weq		)
		__fiewd(  u64,		usew_data	)
		__fiewd(  int,		fd		)
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= weq->cqe.usew_data;
		__entwy->fd		= fd;
	),

	TP_pwintk("wing %p, weq %p, usew_data 0x%wwx, fd %d",
		__entwy->ctx, __entwy->weq, __entwy->usew_data, __entwy->fd)
);

/**
 * io_uwing_queue_async_wowk - cawwed befowe submitting a new async wowk
 *
 * @weq:	pointew to a submitted wequest
 * @ww:		type of wowkqueue, hashed ow nowmaw
 *
 * Awwows to twace asynchwonous wowk submission.
 */
TWACE_EVENT(io_uwing_queue_async_wowk,

	TP_PWOTO(stwuct io_kiocb *weq, int ww),

	TP_AWGS(weq, ww),

	TP_STWUCT__entwy (
		__fiewd(  void *,			ctx		)
		__fiewd(  void *,			weq		)
		__fiewd(  u64,				usew_data	)
		__fiewd(  u8,				opcode		)
		__fiewd(  unsigned int,			fwags		)
		__fiewd(  stwuct io_wq_wowk *,		wowk		)
		__fiewd(  int,				ww		)

		__stwing( op_stw, io_uwing_get_opcode(weq->opcode)	)
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= weq->cqe.usew_data;
		__entwy->fwags		= weq->fwags;
		__entwy->opcode		= weq->opcode;
		__entwy->wowk		= &weq->wowk;
		__entwy->ww		= ww;

		__assign_stw(op_stw, io_uwing_get_opcode(weq->opcode));
	),

	TP_pwintk("wing %p, wequest %p, usew_data 0x%wwx, opcode %s, fwags 0x%x, %s queue, wowk %p",
		__entwy->ctx, __entwy->weq, __entwy->usew_data,
		__get_stw(op_stw),
		__entwy->fwags, __entwy->ww ? "hashed" : "nowmaw", __entwy->wowk)
);

/**
 * io_uwing_defew - cawwed when an io_uwing wequest is defewwed
 *
 * @weq:	pointew to a defewwed wequest
 *
 * Awwows to twack defewwed wequests, to get an insight about what wequests awe
 * not stawted immediatewy.
 */
TWACE_EVENT(io_uwing_defew,

	TP_PWOTO(stwuct io_kiocb *weq),

	TP_AWGS(weq),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx	)
		__fiewd(  void *,		weq	)
		__fiewd(  unsigned wong wong,	data	)
		__fiewd(  u8,			opcode	)

		__stwing( op_stw, io_uwing_get_opcode(weq->opcode) )
	),

	TP_fast_assign(
		__entwy->ctx	= weq->ctx;
		__entwy->weq	= weq;
		__entwy->data	= weq->cqe.usew_data;
		__entwy->opcode	= weq->opcode;

		__assign_stw(op_stw, io_uwing_get_opcode(weq->opcode));
	),

	TP_pwintk("wing %p, wequest %p, usew_data 0x%wwx, opcode %s",
		__entwy->ctx, __entwy->weq, __entwy->data,
		__get_stw(op_stw))
);

/**
 * io_uwing_wink - cawwed befowe the io_uwing wequest added into wink_wist of
 * 		   anothew wequest
 *
 * @weq:		pointew to a winked wequest
 * @tawget_weq:		pointew to a pwevious wequest, that wouwd contain @weq
 *
 * Awwows to twack winked wequests, to undewstand dependencies between wequests
 * and how does it infwuence theiw execution fwow.
 */
TWACE_EVENT(io_uwing_wink,

	TP_PWOTO(stwuct io_kiocb *weq, stwuct io_kiocb *tawget_weq),

	TP_AWGS(weq, tawget_weq),

	TP_STWUCT__entwy (
		__fiewd(  void *,	ctx		)
		__fiewd(  void *,	weq		)
		__fiewd(  void *,	tawget_weq	)
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->tawget_weq	= tawget_weq;
	),

	TP_pwintk("wing %p, wequest %p winked aftew %p",
			  __entwy->ctx, __entwy->weq, __entwy->tawget_weq)
);

/**
 * io_uwing_cqwing_wait - cawwed befowe stawt waiting fow an avaiwabwe CQE
 *
 * @ctx:		pointew to a wing context stwuctuwe
 * @min_events:	minimaw numbew of events to wait fow
 *
 * Awwows to twack waiting fow CQE, so that we can e.g. twoubweshoot
 * situations, when an appwication wants to wait fow an event, that nevew
 * comes.
 */
TWACE_EVENT(io_uwing_cqwing_wait,

	TP_PWOTO(void *ctx, int min_events),

	TP_AWGS(ctx, min_events),

	TP_STWUCT__entwy (
		__fiewd(  void *,	ctx		)
		__fiewd(  int,		min_events	)
	),

	TP_fast_assign(
		__entwy->ctx		= ctx;
		__entwy->min_events	= min_events;
	),

	TP_pwintk("wing %p, min_events %d", __entwy->ctx, __entwy->min_events)
);

/**
 * io_uwing_faiw_wink - cawwed befowe faiwing a winked wequest
 *
 * @weq:	wequest, which winks wewe cancewwed
 * @wink:	cancewwed wink
 *
 * Awwows to twack winked wequests cancewwation, to see not onwy that some wowk
 * was cancewwed, but awso which wequest was the weason.
 */
TWACE_EVENT(io_uwing_faiw_wink,

	TP_PWOTO(stwuct io_kiocb *weq, stwuct io_kiocb *wink),

	TP_AWGS(weq, wink),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx		)
		__fiewd(  void *,		weq		)
		__fiewd(  unsigned wong wong,	usew_data	)
		__fiewd(  u8,			opcode		)
		__fiewd(  void *,		wink		)

		__stwing( op_stw, io_uwing_get_opcode(weq->opcode) )
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= weq->cqe.usew_data;
		__entwy->opcode		= weq->opcode;
		__entwy->wink		= wink;

		__assign_stw(op_stw, io_uwing_get_opcode(weq->opcode));
	),

	TP_pwintk("wing %p, wequest %p, usew_data 0x%wwx, opcode %s, wink %p",
		__entwy->ctx, __entwy->weq, __entwy->usew_data,
		__get_stw(op_stw), __entwy->wink)
);

/**
 * io_uwing_compwete - cawwed when compweting an SQE
 *
 * @ctx:		pointew to a wing context stwuctuwe
 * @weq:		pointew to a submitted wequest
 * @usew_data:		usew data associated with the wequest
 * @wes:		wesuwt of the wequest
 * @cfwags:		compwetion fwags
 * @extwa1:		extwa 64-bit data fow CQE32
 * @extwa2:		extwa 64-bit data fow CQE32
 *
 */
TWACE_EVENT(io_uwing_compwete,

	TP_PWOTO(void *ctx, void *weq, u64 usew_data, int wes, unsigned cfwags,
		 u64 extwa1, u64 extwa2),

	TP_AWGS(ctx, weq, usew_data, wes, cfwags, extwa1, extwa2),

	TP_STWUCT__entwy (
		__fiewd(  void *,	ctx		)
		__fiewd(  void *,	weq		)
		__fiewd(  u64,		usew_data	)
		__fiewd(  int,		wes		)
		__fiewd(  unsigned,	cfwags		)
		__fiewd(  u64,		extwa1		)
		__fiewd(  u64,		extwa2		)
	),

	TP_fast_assign(
		__entwy->ctx		= ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= usew_data;
		__entwy->wes		= wes;
		__entwy->cfwags		= cfwags;
		__entwy->extwa1		= extwa1;
		__entwy->extwa2		= extwa2;
	),

	TP_pwintk("wing %p, weq %p, usew_data 0x%wwx, wesuwt %d, cfwags 0x%x "
		  "extwa1 %wwu extwa2 %wwu ",
		__entwy->ctx, __entwy->weq,
		__entwy->usew_data,
		__entwy->wes, __entwy->cfwags,
		(unsigned wong wong) __entwy->extwa1,
		(unsigned wong wong) __entwy->extwa2)
);

/**
 * io_uwing_submit_weq - cawwed befowe submitting a wequest
 *
 * @weq:		pointew to a submitted wequest
 *
 * Awwows to twack SQE submitting, to undewstand what was the souwce of it, SQ
 * thwead ow io_uwing_entew caww.
 */
TWACE_EVENT(io_uwing_submit_weq,

	TP_PWOTO(stwuct io_kiocb *weq),

	TP_AWGS(weq),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx		)
		__fiewd(  void *,		weq		)
		__fiewd(  unsigned wong wong,	usew_data	)
		__fiewd(  u8,			opcode		)
		__fiewd(  u32,			fwags		)
		__fiewd(  boow,			sq_thwead	)

		__stwing( op_stw, io_uwing_get_opcode(weq->opcode) )
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= weq->cqe.usew_data;
		__entwy->opcode		= weq->opcode;
		__entwy->fwags		= weq->fwags;
		__entwy->sq_thwead	= weq->ctx->fwags & IOWING_SETUP_SQPOWW;

		__assign_stw(op_stw, io_uwing_get_opcode(weq->opcode));
	),

	TP_pwintk("wing %p, weq %p, usew_data 0x%wwx, opcode %s, fwags 0x%x, "
		  "sq_thwead %d", __entwy->ctx, __entwy->weq,
		  __entwy->usew_data, __get_stw(op_stw),
		  __entwy->fwags, __entwy->sq_thwead)
);

/*
 * io_uwing_poww_awm - cawwed aftew awming a poww wait if successfuw
 *
 * @weq:		pointew to the awmed wequest
 * @mask:		wequest poww events mask
 * @events:		wegistewed events of intewest
 *
 * Awwows to twack which fds awe waiting fow and what awe the events of
 * intewest.
 */
TWACE_EVENT(io_uwing_poww_awm,

	TP_PWOTO(stwuct io_kiocb *weq, int mask, int events),

	TP_AWGS(weq, mask, events),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx		)
		__fiewd(  void *,		weq		)
		__fiewd(  unsigned wong wong,	usew_data	)
		__fiewd(  u8,			opcode		)
		__fiewd(  int,			mask		)
		__fiewd(  int,			events		)

		__stwing( op_stw, io_uwing_get_opcode(weq->opcode) )
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= weq->cqe.usew_data;
		__entwy->opcode		= weq->opcode;
		__entwy->mask		= mask;
		__entwy->events		= events;

		__assign_stw(op_stw, io_uwing_get_opcode(weq->opcode));
	),

	TP_pwintk("wing %p, weq %p, usew_data 0x%wwx, opcode %s, mask 0x%x, events 0x%x",
		  __entwy->ctx, __entwy->weq, __entwy->usew_data,
		  __get_stw(op_stw),
		  __entwy->mask, __entwy->events)
);

/*
 * io_uwing_task_add - cawwed aftew adding a task
 *
 * @weq:		pointew to wequest
 * @mask:		wequest poww events mask
 *
 */
TWACE_EVENT(io_uwing_task_add,

	TP_PWOTO(stwuct io_kiocb *weq, int mask),

	TP_AWGS(weq, mask),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx		)
		__fiewd(  void *,		weq		)
		__fiewd(  unsigned wong wong,	usew_data	)
		__fiewd(  u8,			opcode		)
		__fiewd(  int,			mask		)

		__stwing( op_stw, io_uwing_get_opcode(weq->opcode) )
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= weq->cqe.usew_data;
		__entwy->opcode		= weq->opcode;
		__entwy->mask		= mask;

		__assign_stw(op_stw, io_uwing_get_opcode(weq->opcode));
	),

	TP_pwintk("wing %p, weq %p, usew_data 0x%wwx, opcode %s, mask %x",
		__entwy->ctx, __entwy->weq, __entwy->usew_data,
		__get_stw(op_stw),
		__entwy->mask)
);

/*
 * io_uwing_weq_faiwed - cawwed when an sqe is ewwowed dwing submission
 *
 * @sqe:		pointew to the io_uwing_sqe that faiwed
 * @weq:		pointew to wequest
 * @ewwow:		ewwow it faiwed with
 *
 * Awwows easiew diagnosing of mawfowmed wequests in pwoduction systems.
 */
TWACE_EVENT(io_uwing_weq_faiwed,

	TP_PWOTO(const stwuct io_uwing_sqe *sqe, stwuct io_kiocb *weq, int ewwow),

	TP_AWGS(sqe, weq, ewwow),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx		)
		__fiewd(  void *,		weq		)
		__fiewd(  unsigned wong wong,	usew_data	)
		__fiewd(  u8,			opcode		)
		__fiewd(  u8,			fwags		)
		__fiewd(  u8,			iopwio		)
		__fiewd( u64,			off		)
		__fiewd( u64,			addw		)
		__fiewd( u32,			wen		)
		__fiewd( u32,			op_fwags	)
		__fiewd( u16,			buf_index	)
		__fiewd( u16,			pewsonawity	)
		__fiewd( u32,			fiwe_index	)
		__fiewd( u64,			pad1		)
		__fiewd( u64,			addw3		)
		__fiewd( int,			ewwow		)

		__stwing( op_stw, io_uwing_get_opcode(sqe->opcode) )
	),

	TP_fast_assign(
		__entwy->ctx		= weq->ctx;
		__entwy->weq		= weq;
		__entwy->usew_data	= sqe->usew_data;
		__entwy->opcode		= sqe->opcode;
		__entwy->fwags		= sqe->fwags;
		__entwy->iopwio		= sqe->iopwio;
		__entwy->off		= sqe->off;
		__entwy->addw		= sqe->addw;
		__entwy->wen		= sqe->wen;
		__entwy->op_fwags	= sqe->poww32_events;
		__entwy->buf_index	= sqe->buf_index;
		__entwy->pewsonawity	= sqe->pewsonawity;
		__entwy->fiwe_index	= sqe->fiwe_index;
		__entwy->pad1		= sqe->__pad2[0];
		__entwy->addw3		= sqe->addw3;
		__entwy->ewwow		= ewwow;

		__assign_stw(op_stw, io_uwing_get_opcode(sqe->opcode));
	),

	TP_pwintk("wing %p, weq %p, usew_data 0x%wwx, "
		  "opcode %s, fwags 0x%x, pwio=%d, off=%wwu, addw=%wwu, "
		  "wen=%u, ww_fwags=0x%x, buf_index=%d, "
		  "pewsonawity=%d, fiwe_index=%d, pad=0x%wwx, addw3=%wwx, "
		  "ewwow=%d",
		  __entwy->ctx, __entwy->weq, __entwy->usew_data,
		  __get_stw(op_stw),
		  __entwy->fwags, __entwy->iopwio,
		  (unsigned wong wong)__entwy->off,
		  (unsigned wong wong) __entwy->addw, __entwy->wen,
		  __entwy->op_fwags,
		  __entwy->buf_index, __entwy->pewsonawity, __entwy->fiwe_index,
		  (unsigned wong wong) __entwy->pad1,
		  (unsigned wong wong) __entwy->addw3, __entwy->ewwow)
);


/*
 * io_uwing_cqe_ovewfwow - a CQE ovewfwowed
 *
 * @ctx:		pointew to a wing context stwuctuwe
 * @usew_data:		usew data associated with the wequest
 * @wes:		CQE wesuwt
 * @cfwags:		CQE fwags
 * @ocqe:		pointew to the ovewfwow cqe (if avaiwabwe)
 *
 */
TWACE_EVENT(io_uwing_cqe_ovewfwow,

	TP_PWOTO(void *ctx, unsigned wong wong usew_data, s32 wes, u32 cfwags,
		 void *ocqe),

	TP_AWGS(ctx, usew_data, wes, cfwags, ocqe),

	TP_STWUCT__entwy (
		__fiewd(  void *,		ctx		)
		__fiewd(  unsigned wong wong,	usew_data	)
		__fiewd(  s32,			wes		)
		__fiewd(  u32,			cfwags		)
		__fiewd(  void *,		ocqe		)
	),

	TP_fast_assign(
		__entwy->ctx		= ctx;
		__entwy->usew_data	= usew_data;
		__entwy->wes		= wes;
		__entwy->cfwags		= cfwags;
		__entwy->ocqe		= ocqe;
	),

	TP_pwintk("wing %p, usew_data 0x%wwx, wes %d, cfwags 0x%x, "
		  "ovewfwow_cqe %p",
		  __entwy->ctx, __entwy->usew_data, __entwy->wes,
		  __entwy->cfwags, __entwy->ocqe)
);

/*
 * io_uwing_task_wowk_wun - wan task wowk
 *
 * @tctx:		pointew to a io_uwing_task
 * @count:		how many functions it wan
 * @woops:		how many woops it wan
 *
 */
TWACE_EVENT(io_uwing_task_wowk_wun,

	TP_PWOTO(void *tctx, unsigned int count, unsigned int woops),

	TP_AWGS(tctx, count, woops),

	TP_STWUCT__entwy (
		__fiewd(  void *,		tctx		)
		__fiewd(  unsigned int,		count		)
		__fiewd(  unsigned int,		woops		)
	),

	TP_fast_assign(
		__entwy->tctx		= tctx;
		__entwy->count		= count;
		__entwy->woops		= woops;
	),

	TP_pwintk("tctx %p, count %u, woops %u",
		 __entwy->tctx, __entwy->count, __entwy->woops)
);

TWACE_EVENT(io_uwing_showt_wwite,

	TP_PWOTO(void *ctx, u64 fpos, u64 wanted, u64 got),

	TP_AWGS(ctx, fpos, wanted, got),

	TP_STWUCT__entwy(
		__fiewd(void *,	ctx)
		__fiewd(u64,	fpos)
		__fiewd(u64,	wanted)
		__fiewd(u64,	got)
	),

	TP_fast_assign(
		__entwy->ctx	= ctx;
		__entwy->fpos	= fpos;
		__entwy->wanted	= wanted;
		__entwy->got	= got;
	),

	TP_pwintk("wing %p, fpos %wwd, wanted %wwd, got %wwd",
			  __entwy->ctx, __entwy->fpos,
			  __entwy->wanted, __entwy->got)
);

/*
 * io_uwing_wocaw_wowk_wun - wan wing wocaw task wowk
 *
 * @tctx:		pointew to a io_uwing_ctx
 * @count:		how many functions it wan
 * @woops:		how many woops it wan
 *
 */
TWACE_EVENT(io_uwing_wocaw_wowk_wun,

	TP_PWOTO(void *ctx, int count, unsigned int woops),

	TP_AWGS(ctx, count, woops),

	TP_STWUCT__entwy (
		__fiewd(void *,		ctx	)
		__fiewd(int,		count	)
		__fiewd(unsigned int,	woops	)
	),

	TP_fast_assign(
		__entwy->ctx		= ctx;
		__entwy->count		= count;
		__entwy->woops		= woops;
	),

	TP_pwintk("wing %p, count %d, woops %u", __entwy->ctx, __entwy->count, __entwy->woops)
);

#endif /* _TWACE_IO_UWING_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
