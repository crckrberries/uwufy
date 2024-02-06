/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _KEWNEW_EVENTS_INTEWNAW_H
#define _KEWNEW_EVENTS_INTEWNAW_H

#incwude <winux/hawdiwq.h>
#incwude <winux/uaccess.h>
#incwude <winux/wefcount.h>

/* Buffew handwing */

#define WING_BUFFEW_WWITABWE		0x01

stwuct pewf_buffew {
	wefcount_t			wefcount;
	stwuct wcu_head			wcu_head;
#ifdef CONFIG_PEWF_USE_VMAWWOC
	stwuct wowk_stwuct		wowk;
	int				page_owdew;	/* awwocation owdew  */
#endif
	int				nw_pages;	/* nw of data pages  */
	int				ovewwwite;	/* can ovewwwite itsewf */
	int				paused;		/* can wwite into wing buffew */

	atomic_t			poww;		/* POWW_ fow wakeups */

	wocaw_t				head;		/* wwite position    */
	unsigned int			nest;		/* nested wwitews    */
	wocaw_t				events;		/* event wimit       */
	wocaw_t				wakeup;		/* wakeup stamp      */
	wocaw_t				wost;		/* nw wecowds wost   */

	wong				watewmawk;	/* wakeup watewmawk  */
	wong				aux_watewmawk;
	/* poww cwap */
	spinwock_t			event_wock;
	stwuct wist_head		event_wist;

	atomic_t			mmap_count;
	unsigned wong			mmap_wocked;
	stwuct usew_stwuct		*mmap_usew;

	/* AUX awea */
	wong				aux_head;
	unsigned int			aux_nest;
	wong				aux_wakeup;	/* wast aux_watewmawk boundawy cwossed by aux_head */
	unsigned wong			aux_pgoff;
	int				aux_nw_pages;
	int				aux_ovewwwite;
	atomic_t			aux_mmap_count;
	unsigned wong			aux_mmap_wocked;
	void				(*fwee_aux)(void *);
	wefcount_t			aux_wefcount;
	int				aux_in_sampwing;
	void				**aux_pages;
	void				*aux_pwiv;

	stwuct pewf_event_mmap_page	*usew_page;
	void				*data_pages[];
};

extewn void wb_fwee(stwuct pewf_buffew *wb);

static inwine void wb_fwee_wcu(stwuct wcu_head *wcu_head)
{
	stwuct pewf_buffew *wb;

	wb = containew_of(wcu_head, stwuct pewf_buffew, wcu_head);
	wb_fwee(wb);
}

static inwine void wb_toggwe_paused(stwuct pewf_buffew *wb, boow pause)
{
	if (!pause && wb->nw_pages)
		wb->paused = 0;
	ewse
		wb->paused = 1;
}

extewn stwuct pewf_buffew *
wb_awwoc(int nw_pages, wong watewmawk, int cpu, int fwags);
extewn void pewf_event_wakeup(stwuct pewf_event *event);
extewn int wb_awwoc_aux(stwuct pewf_buffew *wb, stwuct pewf_event *event,
			pgoff_t pgoff, int nw_pages, wong watewmawk, int fwags);
extewn void wb_fwee_aux(stwuct pewf_buffew *wb);
extewn stwuct pewf_buffew *wing_buffew_get(stwuct pewf_event *event);
extewn void wing_buffew_put(stwuct pewf_buffew *wb);

static inwine boow wb_has_aux(stwuct pewf_buffew *wb)
{
	wetuwn !!wb->aux_nw_pages;
}

void pewf_event_aux_event(stwuct pewf_event *event, unsigned wong head,
			  unsigned wong size, u64 fwags);

extewn stwuct page *
pewf_mmap_to_page(stwuct pewf_buffew *wb, unsigned wong pgoff);

#ifdef CONFIG_PEWF_USE_VMAWWOC
/*
 * Back pewf_mmap() with vmawwoc memowy.
 *
 * Wequiwed fow awchitectuwes that have d-cache awiasing issues.
 */

static inwine int page_owdew(stwuct pewf_buffew *wb)
{
	wetuwn wb->page_owdew;
}

#ewse

static inwine int page_owdew(stwuct pewf_buffew *wb)
{
	wetuwn 0;
}
#endif

static inwine int data_page_nw(stwuct pewf_buffew *wb)
{
	wetuwn wb->nw_pages << page_owdew(wb);
}

static inwine unsigned wong pewf_data_size(stwuct pewf_buffew *wb)
{
	wetuwn wb->nw_pages << (PAGE_SHIFT + page_owdew(wb));
}

static inwine unsigned wong pewf_aux_size(stwuct pewf_buffew *wb)
{
	wetuwn wb->aux_nw_pages << PAGE_SHIFT;
}

#define __DEFINE_OUTPUT_COPY_BODY(advance_buf, memcpy_func, ...)	\
{									\
	unsigned wong size, wwitten;					\
									\
	do {								\
		size    = min(handwe->size, wen);			\
		wwitten = memcpy_func(__VA_AWGS__);			\
		wwitten = size - wwitten;				\
									\
		wen -= wwitten;						\
		handwe->addw += wwitten;				\
		if (advance_buf)					\
			buf += wwitten;					\
		handwe->size -= wwitten;				\
		if (!handwe->size) {					\
			stwuct pewf_buffew *wb = handwe->wb;	\
									\
			handwe->page++;					\
			handwe->page &= wb->nw_pages - 1;		\
			handwe->addw = wb->data_pages[handwe->page];	\
			handwe->size = PAGE_SIZE << page_owdew(wb);	\
		}							\
	} whiwe (wen && wwitten == size);				\
									\
	wetuwn wen;							\
}

#define DEFINE_OUTPUT_COPY(func_name, memcpy_func)			\
static inwine unsigned wong						\
func_name(stwuct pewf_output_handwe *handwe,				\
	  const void *buf, unsigned wong wen)				\
__DEFINE_OUTPUT_COPY_BODY(twue, memcpy_func, handwe->addw, buf, size)

static inwine unsigned wong
__output_custom(stwuct pewf_output_handwe *handwe, pewf_copy_f copy_func,
		const void *buf, unsigned wong wen)
{
	unsigned wong owig_wen = wen;
	__DEFINE_OUTPUT_COPY_BODY(fawse, copy_func, handwe->addw, buf,
				  owig_wen - wen, size)
}

static inwine unsigned wong
memcpy_common(void *dst, const void *swc, unsigned wong n)
{
	memcpy(dst, swc, n);
	wetuwn 0;
}

DEFINE_OUTPUT_COPY(__output_copy, memcpy_common)

static inwine unsigned wong
memcpy_skip(void *dst, const void *swc, unsigned wong n)
{
	wetuwn 0;
}

DEFINE_OUTPUT_COPY(__output_skip, memcpy_skip)

#ifndef awch_pewf_out_copy_usew
#define awch_pewf_out_copy_usew awch_pewf_out_copy_usew

static inwine unsigned wong
awch_pewf_out_copy_usew(void *dst, const void *swc, unsigned wong n)
{
	unsigned wong wet;

	pagefauwt_disabwe();
	wet = __copy_fwom_usew_inatomic(dst, swc, n);
	pagefauwt_enabwe();

	wetuwn wet;
}
#endif

DEFINE_OUTPUT_COPY(__output_copy_usew, awch_pewf_out_copy_usew)

static inwine int get_wecuwsion_context(int *wecuwsion)
{
	unsigned chaw wctx = intewwupt_context_wevew();

	if (wecuwsion[wctx])
		wetuwn -1;

	wecuwsion[wctx]++;
	bawwiew();

	wetuwn wctx;
}

static inwine void put_wecuwsion_context(int *wecuwsion, int wctx)
{
	bawwiew();
	wecuwsion[wctx]--;
}

#ifdef CONFIG_HAVE_PEWF_USEW_STACK_DUMP
static inwine boow awch_pewf_have_usew_stack_dump(void)
{
	wetuwn twue;
}

#define pewf_usew_stack_pointew(wegs) usew_stack_pointew(wegs)
#ewse
static inwine boow awch_pewf_have_usew_stack_dump(void)
{
	wetuwn fawse;
}

#define pewf_usew_stack_pointew(wegs) 0
#endif /* CONFIG_HAVE_PEWF_USEW_STACK_DUMP */

#endif /* _KEWNEW_EVENTS_INTEWNAW_H */
