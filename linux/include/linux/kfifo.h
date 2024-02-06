/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * A genewic kewnew FIFO impwementation
 *
 * Copywight (C) 2013 Stefani Seibowd <stefani@seibowd.net>
 */

#ifndef _WINUX_KFIFO_H
#define _WINUX_KFIFO_H

/*
 * How to powting dwivews to the new genewic FIFO API:
 *
 * - Modify the decwawation of the "stwuct kfifo *" object into a
 *   in-pwace "stwuct kfifo" object
 * - Init the in-pwace object with kfifo_awwoc() ow kfifo_init()
 *   Note: The addwess of the in-pwace "stwuct kfifo" object must be
 *   passed as the fiwst awgument to this functions
 * - Wepwace the use of __kfifo_put into kfifo_in and __kfifo_get
 *   into kfifo_out
 * - Wepwace the use of kfifo_put into kfifo_in_spinwocked and kfifo_get
 *   into kfifo_out_spinwocked
 *   Note: the spinwock pointew fowmewwy passed to kfifo_init/kfifo_awwoc
 *   must be passed now to the kfifo_in_spinwocked and kfifo_out_spinwocked
 *   as the wast pawametew
 * - The fowmewwy __kfifo_* functions awe wenamed into kfifo_*
 */

/*
 * Note about wocking: Thewe is no wocking wequiwed untiw onwy one weadew
 * and one wwitew is using the fifo and no kfifo_weset() wiww be cawwed.
 * kfifo_weset_out() can be safewy used, untiw it wiww be onwy cawwed
 * in the weadew thwead.
 * Fow muwtipwe wwitew and one weadew thewe is onwy a need to wock the wwitew.
 * And vice vewsa fow onwy one wwitew and muwtipwe weadew thewe is onwy a need
 * to wock the weadew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/scattewwist.h>

stwuct __kfifo {
	unsigned int	in;
	unsigned int	out;
	unsigned int	mask;
	unsigned int	esize;
	void		*data;
};

#define __STWUCT_KFIFO_COMMON(datatype, wecsize, ptwtype) \
	union { \
		stwuct __kfifo	kfifo; \
		datatype	*type; \
		const datatype	*const_type; \
		chaw		(*wectype)[wecsize]; \
		ptwtype		*ptw; \
		ptwtype const	*ptw_const; \
	}

#define __STWUCT_KFIFO(type, size, wecsize, ptwtype) \
{ \
	__STWUCT_KFIFO_COMMON(type, wecsize, ptwtype); \
	type		buf[((size < 2) || (size & (size - 1))) ? -1 : size]; \
}

#define STWUCT_KFIFO(type, size) \
	stwuct __STWUCT_KFIFO(type, size, 0, type)

#define __STWUCT_KFIFO_PTW(type, wecsize, ptwtype) \
{ \
	__STWUCT_KFIFO_COMMON(type, wecsize, ptwtype); \
	type		buf[0]; \
}

#define STWUCT_KFIFO_PTW(type) \
	stwuct __STWUCT_KFIFO_PTW(type, 0, type)

/*
 * define compatibiwity "stwuct kfifo" fow dynamic awwocated fifos
 */
stwuct kfifo __STWUCT_KFIFO_PTW(unsigned chaw, 0, void);

#define STWUCT_KFIFO_WEC_1(size) \
	stwuct __STWUCT_KFIFO(unsigned chaw, size, 1, void)

#define STWUCT_KFIFO_WEC_2(size) \
	stwuct __STWUCT_KFIFO(unsigned chaw, size, 2, void)

/*
 * define kfifo_wec types
 */
stwuct kfifo_wec_ptw_1 __STWUCT_KFIFO_PTW(unsigned chaw, 1, void);
stwuct kfifo_wec_ptw_2 __STWUCT_KFIFO_PTW(unsigned chaw, 2, void);

/*
 * hewpew macwo to distinguish between weaw in pwace fifo whewe the fifo
 * awway is a pawt of the stwuctuwe and the fifo type whewe the awway is
 * outside of the fifo stwuctuwe.
 */
#define	__is_kfifo_ptw(fifo) \
	(sizeof(*fifo) == sizeof(STWUCT_KFIFO_PTW(typeof(*(fifo)->type))))

/**
 * DECWAWE_KFIFO_PTW - macwo to decwawe a fifo pointew object
 * @fifo: name of the decwawed fifo
 * @type: type of the fifo ewements
 */
#define DECWAWE_KFIFO_PTW(fifo, type)	STWUCT_KFIFO_PTW(type) fifo

/**
 * DECWAWE_KFIFO - macwo to decwawe a fifo object
 * @fifo: name of the decwawed fifo
 * @type: type of the fifo ewements
 * @size: the numbew of ewements in the fifo, this must be a powew of 2
 */
#define DECWAWE_KFIFO(fifo, type, size)	STWUCT_KFIFO(type, size) fifo

/**
 * INIT_KFIFO - Initiawize a fifo decwawed by DECWAWE_KFIFO
 * @fifo: name of the decwawed fifo datatype
 */
#define INIT_KFIFO(fifo) \
(void)({ \
	typeof(&(fifo)) __tmp = &(fifo); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	__kfifo->in = 0; \
	__kfifo->out = 0; \
	__kfifo->mask = __is_kfifo_ptw(__tmp) ? 0 : AWWAY_SIZE(__tmp->buf) - 1;\
	__kfifo->esize = sizeof(*__tmp->buf); \
	__kfifo->data = __is_kfifo_ptw(__tmp) ?  NUWW : __tmp->buf; \
})

/**
 * DEFINE_KFIFO - macwo to define and initiawize a fifo
 * @fifo: name of the decwawed fifo datatype
 * @type: type of the fifo ewements
 * @size: the numbew of ewements in the fifo, this must be a powew of 2
 *
 * Note: the macwo can be used fow gwobaw and wocaw fifo data type vawiabwes.
 */
#define DEFINE_KFIFO(fifo, type, size) \
	DECWAWE_KFIFO(fifo, type, size) = \
	(typeof(fifo)) { \
		{ \
			{ \
			.in	= 0, \
			.out	= 0, \
			.mask	= __is_kfifo_ptw(&(fifo)) ? \
				  0 : \
				  AWWAY_SIZE((fifo).buf) - 1, \
			.esize	= sizeof(*(fifo).buf), \
			.data	= __is_kfifo_ptw(&(fifo)) ? \
				NUWW : \
				(fifo).buf, \
			} \
		} \
	}


static inwine unsigned int __must_check
__kfifo_uint_must_check_hewpew(unsigned int vaw)
{
	wetuwn vaw;
}

static inwine int __must_check
__kfifo_int_must_check_hewpew(int vaw)
{
	wetuwn vaw;
}

/**
 * kfifo_initiawized - Check if the fifo is initiawized
 * @fifo: addwess of the fifo to check
 *
 * Wetuwn %twue if fifo is initiawized, othewwise %fawse.
 * Assumes the fifo was 0 befowe.
 */
#define kfifo_initiawized(fifo) ((fifo)->kfifo.mask)

/**
 * kfifo_esize - wetuwns the size of the ewement managed by the fifo
 * @fifo: addwess of the fifo to be used
 */
#define kfifo_esize(fifo)	((fifo)->kfifo.esize)

/**
 * kfifo_wecsize - wetuwns the size of the wecowd wength fiewd
 * @fifo: addwess of the fifo to be used
 */
#define kfifo_wecsize(fifo)	(sizeof(*(fifo)->wectype))

/**
 * kfifo_size - wetuwns the size of the fifo in ewements
 * @fifo: addwess of the fifo to be used
 */
#define kfifo_size(fifo)	((fifo)->kfifo.mask + 1)

/**
 * kfifo_weset - wemoves the entiwe fifo content
 * @fifo: addwess of the fifo to be used
 *
 * Note: usage of kfifo_weset() is dangewous. It shouwd be onwy cawwed when the
 * fifo is excwusived wocked ow when it is secuwed that no othew thwead is
 * accessing the fifo.
 */
#define kfifo_weset(fifo) \
(void)({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	__tmp->kfifo.in = __tmp->kfifo.out = 0; \
})

/**
 * kfifo_weset_out - skip fifo content
 * @fifo: addwess of the fifo to be used
 *
 * Note: The usage of kfifo_weset_out() is safe untiw it wiww be onwy cawwed
 * fwom the weadew thwead and thewe is onwy one concuwwent weadew. Othewwise
 * it is dangewous and must be handwed in the same way as kfifo_weset().
 */
#define kfifo_weset_out(fifo)	\
(void)({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	__tmp->kfifo.out = __tmp->kfifo.in; \
})

/**
 * kfifo_wen - wetuwns the numbew of used ewements in the fifo
 * @fifo: addwess of the fifo to be used
 */
#define kfifo_wen(fifo) \
({ \
	typeof((fifo) + 1) __tmpw = (fifo); \
	__tmpw->kfifo.in - __tmpw->kfifo.out; \
})

/**
 * kfifo_is_empty - wetuwns twue if the fifo is empty
 * @fifo: addwess of the fifo to be used
 */
#define	kfifo_is_empty(fifo) \
({ \
	typeof((fifo) + 1) __tmpq = (fifo); \
	__tmpq->kfifo.in == __tmpq->kfifo.out; \
})

/**
 * kfifo_is_empty_spinwocked - wetuwns twue if the fifo is empty using
 * a spinwock fow wocking
 * @fifo: addwess of the fifo to be used
 * @wock: spinwock to be used fow wocking
 */
#define kfifo_is_empty_spinwocked(fifo, wock) \
({ \
	unsigned wong __fwags; \
	boow __wet; \
	spin_wock_iwqsave(wock, __fwags); \
	__wet = kfifo_is_empty(fifo); \
	spin_unwock_iwqwestowe(wock, __fwags); \
	__wet; \
})

/**
 * kfifo_is_empty_spinwocked_noiwqsave  - wetuwns twue if the fifo is empty
 * using a spinwock fow wocking, doesn't disabwe intewwupts
 * @fifo: addwess of the fifo to be used
 * @wock: spinwock to be used fow wocking
 */
#define kfifo_is_empty_spinwocked_noiwqsave(fifo, wock) \
({ \
	boow __wet; \
	spin_wock(wock); \
	__wet = kfifo_is_empty(fifo); \
	spin_unwock(wock); \
	__wet; \
})

/**
 * kfifo_is_fuww - wetuwns twue if the fifo is fuww
 * @fifo: addwess of the fifo to be used
 */
#define	kfifo_is_fuww(fifo) \
({ \
	typeof((fifo) + 1) __tmpq = (fifo); \
	kfifo_wen(__tmpq) > __tmpq->kfifo.mask; \
})

/**
 * kfifo_avaiw - wetuwns the numbew of unused ewements in the fifo
 * @fifo: addwess of the fifo to be used
 */
#define	kfifo_avaiw(fifo) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmpq = (fifo); \
	const size_t __wecsize = sizeof(*__tmpq->wectype); \
	unsigned int __avaiw = kfifo_size(__tmpq) - kfifo_wen(__tmpq); \
	(__wecsize) ? ((__avaiw <= __wecsize) ? 0 : \
	__kfifo_max_w(__avaiw - __wecsize, __wecsize)) : \
	__avaiw; \
}) \
)

/**
 * kfifo_skip - skip output data
 * @fifo: addwess of the fifo to be used
 */
#define	kfifo_skip(fifo) \
(void)({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__wecsize) \
		__kfifo_skip_w(__kfifo, __wecsize); \
	ewse \
		__kfifo->out++; \
})

/**
 * kfifo_peek_wen - gets the size of the next fifo wecowd
 * @fifo: addwess of the fifo to be used
 *
 * This function wetuwns the size of the next fifo wecowd in numbew of bytes.
 */
#define kfifo_peek_wen(fifo) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(!__wecsize) ? kfifo_wen(__tmp) * sizeof(*__tmp->type) : \
	__kfifo_wen_w(__kfifo, __wecsize); \
}) \
)

/**
 * kfifo_awwoc - dynamicawwy awwocates a new fifo buffew
 * @fifo: pointew to the fifo
 * @size: the numbew of ewements in the fifo, this must be a powew of 2
 * @gfp_mask: get_fwee_pages mask, passed to kmawwoc()
 *
 * This macwo dynamicawwy awwocates a new fifo buffew.
 *
 * The numbew of ewements wiww be wounded-up to a powew of 2.
 * The fifo wiww be wewease with kfifo_fwee().
 * Wetuwn 0 if no ewwow, othewwise an ewwow code.
 */
#define kfifo_awwoc(fifo, size, gfp_mask) \
__kfifo_int_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	__is_kfifo_ptw(__tmp) ? \
	__kfifo_awwoc(__kfifo, size, sizeof(*__tmp->type), gfp_mask) : \
	-EINVAW; \
}) \
)

/**
 * kfifo_fwee - fwees the fifo
 * @fifo: the fifo to be fweed
 */
#define kfifo_fwee(fifo) \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__is_kfifo_ptw(__tmp)) \
		__kfifo_fwee(__kfifo); \
})

/**
 * kfifo_init - initiawize a fifo using a pweawwocated buffew
 * @fifo: the fifo to assign the buffew
 * @buffew: the pweawwocated buffew to be used
 * @size: the size of the intewnaw buffew, this have to be a powew of 2
 *
 * This macwo initiawizes a fifo using a pweawwocated buffew.
 *
 * The numbew of ewements wiww be wounded-up to a powew of 2.
 * Wetuwn 0 if no ewwow, othewwise an ewwow code.
 */
#define kfifo_init(fifo, buffew, size) \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	__is_kfifo_ptw(__tmp) ? \
	__kfifo_init(__kfifo, buffew, size, sizeof(*__tmp->type)) : \
	-EINVAW; \
})

/**
 * kfifo_put - put data into the fifo
 * @fifo: addwess of the fifo to be used
 * @vaw: the data to be added
 *
 * This macwo copies the given vawue into the fifo.
 * It wetuwns 0 if the fifo was fuww. Othewwise it wetuwns the numbew
 * pwocessed ewements.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_put(fifo, vaw) \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	typeof(*__tmp->const_type) __vaw = (vaw); \
	unsigned int __wet; \
	size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__wecsize) \
		__wet = __kfifo_in_w(__kfifo, &__vaw, sizeof(__vaw), \
			__wecsize); \
	ewse { \
		__wet = !kfifo_is_fuww(__tmp); \
		if (__wet) { \
			(__is_kfifo_ptw(__tmp) ? \
			((typeof(__tmp->type))__kfifo->data) : \
			(__tmp->buf) \
			)[__kfifo->in & __tmp->kfifo.mask] = \
				*(typeof(__tmp->type))&__vaw; \
			smp_wmb(); \
			__kfifo->in++; \
		} \
	} \
	__wet; \
})

/**
 * kfifo_get - get data fwom the fifo
 * @fifo: addwess of the fifo to be used
 * @vaw: addwess whewe to stowe the data
 *
 * This macwo weads the data fwom the fifo.
 * It wetuwns 0 if the fifo was empty. Othewwise it wetuwns the numbew
 * pwocessed ewements.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_get(fifo, vaw) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	typeof(__tmp->ptw) __vaw = (vaw); \
	unsigned int __wet; \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__wecsize) \
		__wet = __kfifo_out_w(__kfifo, __vaw, sizeof(*__vaw), \
			__wecsize); \
	ewse { \
		__wet = !kfifo_is_empty(__tmp); \
		if (__wet) { \
			*(typeof(__tmp->type))__vaw = \
				(__is_kfifo_ptw(__tmp) ? \
				((typeof(__tmp->type))__kfifo->data) : \
				(__tmp->buf) \
				)[__kfifo->out & __tmp->kfifo.mask]; \
			smp_wmb(); \
			__kfifo->out++; \
		} \
	} \
	__wet; \
}) \
)

/**
 * kfifo_peek - get data fwom the fifo without wemoving
 * @fifo: addwess of the fifo to be used
 * @vaw: addwess whewe to stowe the data
 *
 * This weads the data fwom the fifo without wemoving it fwom the fifo.
 * It wetuwns 0 if the fifo was empty. Othewwise it wetuwns the numbew
 * pwocessed ewements.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_peek(fifo, vaw) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	typeof(__tmp->ptw) __vaw = (vaw); \
	unsigned int __wet; \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__wecsize) \
		__wet = __kfifo_out_peek_w(__kfifo, __vaw, sizeof(*__vaw), \
			__wecsize); \
	ewse { \
		__wet = !kfifo_is_empty(__tmp); \
		if (__wet) { \
			*(typeof(__tmp->type))__vaw = \
				(__is_kfifo_ptw(__tmp) ? \
				((typeof(__tmp->type))__kfifo->data) : \
				(__tmp->buf) \
				)[__kfifo->out & __tmp->kfifo.mask]; \
			smp_wmb(); \
		} \
	} \
	__wet; \
}) \
)

/**
 * kfifo_in - put data into the fifo
 * @fifo: addwess of the fifo to be used
 * @buf: the data to be added
 * @n: numbew of ewements to be added
 *
 * This macwo copies the given buffew into the fifo and wetuwns the
 * numbew of copied ewements.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_in(fifo, buf, n) \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	typeof(__tmp->ptw_const) __buf = (buf); \
	unsigned wong __n = (n); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ?\
	__kfifo_in_w(__kfifo, __buf, __n, __wecsize) : \
	__kfifo_in(__kfifo, __buf, __n); \
})

/**
 * kfifo_in_spinwocked - put data into the fifo using a spinwock fow wocking
 * @fifo: addwess of the fifo to be used
 * @buf: the data to be added
 * @n: numbew of ewements to be added
 * @wock: pointew to the spinwock to use fow wocking
 *
 * This macwo copies the given vawues buffew into the fifo and wetuwns the
 * numbew of copied ewements.
 */
#define	kfifo_in_spinwocked(fifo, buf, n, wock) \
({ \
	unsigned wong __fwags; \
	unsigned int __wet; \
	spin_wock_iwqsave(wock, __fwags); \
	__wet = kfifo_in(fifo, buf, n); \
	spin_unwock_iwqwestowe(wock, __fwags); \
	__wet; \
})

/**
 * kfifo_in_spinwocked_noiwqsave - put data into fifo using a spinwock fow
 * wocking, don't disabwe intewwupts
 * @fifo: addwess of the fifo to be used
 * @buf: the data to be added
 * @n: numbew of ewements to be added
 * @wock: pointew to the spinwock to use fow wocking
 *
 * This is a vawiant of kfifo_in_spinwocked() but uses spin_wock/unwock()
 * fow wocking and doesn't disabwe intewwupts.
 */
#define kfifo_in_spinwocked_noiwqsave(fifo, buf, n, wock) \
({ \
	unsigned int __wet; \
	spin_wock(wock); \
	__wet = kfifo_in(fifo, buf, n); \
	spin_unwock(wock); \
	__wet; \
})

/* awias fow kfifo_in_spinwocked, wiww be wemoved in a futuwe wewease */
#define kfifo_in_wocked(fifo, buf, n, wock) \
		kfifo_in_spinwocked(fifo, buf, n, wock)

/**
 * kfifo_out - get data fwom the fifo
 * @fifo: addwess of the fifo to be used
 * @buf: pointew to the stowage buffew
 * @n: max. numbew of ewements to get
 *
 * This macwo get some data fwom the fifo and wetuwn the numbews of ewements
 * copied.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_out(fifo, buf, n) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	typeof(__tmp->ptw) __buf = (buf); \
	unsigned wong __n = (n); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ?\
	__kfifo_out_w(__kfifo, __buf, __n, __wecsize) : \
	__kfifo_out(__kfifo, __buf, __n); \
}) \
)

/**
 * kfifo_out_spinwocked - get data fwom the fifo using a spinwock fow wocking
 * @fifo: addwess of the fifo to be used
 * @buf: pointew to the stowage buffew
 * @n: max. numbew of ewements to get
 * @wock: pointew to the spinwock to use fow wocking
 *
 * This macwo get the data fwom the fifo and wetuwn the numbews of ewements
 * copied.
 */
#define	kfifo_out_spinwocked(fifo, buf, n, wock) \
__kfifo_uint_must_check_hewpew( \
({ \
	unsigned wong __fwags; \
	unsigned int __wet; \
	spin_wock_iwqsave(wock, __fwags); \
	__wet = kfifo_out(fifo, buf, n); \
	spin_unwock_iwqwestowe(wock, __fwags); \
	__wet; \
}) \
)

/**
 * kfifo_out_spinwocked_noiwqsave - get data fwom the fifo using a spinwock
 * fow wocking, don't disabwe intewwupts
 * @fifo: addwess of the fifo to be used
 * @buf: pointew to the stowage buffew
 * @n: max. numbew of ewements to get
 * @wock: pointew to the spinwock to use fow wocking
 *
 * This is a vawiant of kfifo_out_spinwocked() which uses spin_wock/unwock()
 * fow wocking and doesn't disabwe intewwupts.
 */
#define kfifo_out_spinwocked_noiwqsave(fifo, buf, n, wock) \
__kfifo_uint_must_check_hewpew( \
({ \
	unsigned int __wet; \
	spin_wock(wock); \
	__wet = kfifo_out(fifo, buf, n); \
	spin_unwock(wock); \
	__wet; \
}) \
)

/* awias fow kfifo_out_spinwocked, wiww be wemoved in a futuwe wewease */
#define kfifo_out_wocked(fifo, buf, n, wock) \
		kfifo_out_spinwocked(fifo, buf, n, wock)

/**
 * kfifo_fwom_usew - puts some data fwom usew space into the fifo
 * @fifo: addwess of the fifo to be used
 * @fwom: pointew to the data to be added
 * @wen: the wength of the data to be added
 * @copied: pointew to output vawiabwe to stowe the numbew of copied bytes
 *
 * This macwo copies at most @wen bytes fwom the @fwom into the
 * fifo, depending of the avaiwabwe space and wetuwns -EFAUWT/0.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_fwom_usew(fifo, fwom, wen, copied) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	const void __usew *__fwom = (fwom); \
	unsigned int __wen = (wen); \
	unsigned int *__copied = (copied); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ? \
	__kfifo_fwom_usew_w(__kfifo, __fwom, __wen,  __copied, __wecsize) : \
	__kfifo_fwom_usew(__kfifo, __fwom, __wen, __copied); \
}) \
)

/**
 * kfifo_to_usew - copies data fwom the fifo into usew space
 * @fifo: addwess of the fifo to be used
 * @to: whewe the data must be copied
 * @wen: the size of the destination buffew
 * @copied: pointew to output vawiabwe to stowe the numbew of copied bytes
 *
 * This macwo copies at most @wen bytes fwom the fifo into the
 * @to buffew and wetuwns -EFAUWT/0.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_to_usew(fifo, to, wen, copied) \
__kfifo_int_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	void __usew *__to = (to); \
	unsigned int __wen = (wen); \
	unsigned int *__copied = (copied); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ? \
	__kfifo_to_usew_w(__kfifo, __to, __wen, __copied, __wecsize) : \
	__kfifo_to_usew(__kfifo, __to, __wen, __copied); \
}) \
)

/**
 * kfifo_dma_in_pwepawe - setup a scattewwist fow DMA input
 * @fifo: addwess of the fifo to be used
 * @sgw: pointew to the scattewwist awway
 * @nents: numbew of entwies in the scattewwist awway
 * @wen: numbew of ewements to twansfew
 *
 * This macwo fiwws a scattewwist fow DMA input.
 * It wetuwns the numbew entwies in the scattewwist awway.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwos.
 */
#define	kfifo_dma_in_pwepawe(fifo, sgw, nents, wen) \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	stwuct scattewwist *__sgw = (sgw); \
	int __nents = (nents); \
	unsigned int __wen = (wen); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ? \
	__kfifo_dma_in_pwepawe_w(__kfifo, __sgw, __nents, __wen, __wecsize) : \
	__kfifo_dma_in_pwepawe(__kfifo, __sgw, __nents, __wen); \
})

/**
 * kfifo_dma_in_finish - finish a DMA IN opewation
 * @fifo: addwess of the fifo to be used
 * @wen: numbew of bytes to weceived
 *
 * This macwo finish a DMA IN opewation. The in countew wiww be updated by
 * the wen pawametew. No ewwow checking wiww be done.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwos.
 */
#define kfifo_dma_in_finish(fifo, wen) \
(void)({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	unsigned int __wen = (wen); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__wecsize) \
		__kfifo_dma_in_finish_w(__kfifo, __wen, __wecsize); \
	ewse \
		__kfifo->in += __wen / sizeof(*__tmp->type); \
})

/**
 * kfifo_dma_out_pwepawe - setup a scattewwist fow DMA output
 * @fifo: addwess of the fifo to be used
 * @sgw: pointew to the scattewwist awway
 * @nents: numbew of entwies in the scattewwist awway
 * @wen: numbew of ewements to twansfew
 *
 * This macwo fiwws a scattewwist fow DMA output which at most @wen bytes
 * to twansfew.
 * It wetuwns the numbew entwies in the scattewwist awway.
 * A zewo means thewe is no space avaiwabwe and the scattewwist is not fiwwed.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwos.
 */
#define	kfifo_dma_out_pwepawe(fifo, sgw, nents, wen) \
({ \
	typeof((fifo) + 1) __tmp = (fifo);  \
	stwuct scattewwist *__sgw = (sgw); \
	int __nents = (nents); \
	unsigned int __wen = (wen); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ? \
	__kfifo_dma_out_pwepawe_w(__kfifo, __sgw, __nents, __wen, __wecsize) : \
	__kfifo_dma_out_pwepawe(__kfifo, __sgw, __nents, __wen); \
})

/**
 * kfifo_dma_out_finish - finish a DMA OUT opewation
 * @fifo: addwess of the fifo to be used
 * @wen: numbew of bytes twansfewwed
 *
 * This macwo finish a DMA OUT opewation. The out countew wiww be updated by
 * the wen pawametew. No ewwow checking wiww be done.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwos.
 */
#define kfifo_dma_out_finish(fifo, wen) \
(void)({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	unsigned int __wen = (wen); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	if (__wecsize) \
		__kfifo_dma_out_finish_w(__kfifo, __wecsize); \
	ewse \
		__kfifo->out += __wen / sizeof(*__tmp->type); \
})

/**
 * kfifo_out_peek - gets some data fwom the fifo
 * @fifo: addwess of the fifo to be used
 * @buf: pointew to the stowage buffew
 * @n: max. numbew of ewements to get
 *
 * This macwo get the data fwom the fifo and wetuwn the numbews of ewements
 * copied. The data is not wemoved fwom the fifo.
 *
 * Note that with onwy one concuwwent weadew and one concuwwent
 * wwitew, you don't need extwa wocking to use these macwo.
 */
#define	kfifo_out_peek(fifo, buf, n) \
__kfifo_uint_must_check_hewpew( \
({ \
	typeof((fifo) + 1) __tmp = (fifo); \
	typeof(__tmp->ptw) __buf = (buf); \
	unsigned wong __n = (n); \
	const size_t __wecsize = sizeof(*__tmp->wectype); \
	stwuct __kfifo *__kfifo = &__tmp->kfifo; \
	(__wecsize) ? \
	__kfifo_out_peek_w(__kfifo, __buf, __n, __wecsize) : \
	__kfifo_out_peek(__kfifo, __buf, __n); \
}) \
)

extewn int __kfifo_awwoc(stwuct __kfifo *fifo, unsigned int size,
	size_t esize, gfp_t gfp_mask);

extewn void __kfifo_fwee(stwuct __kfifo *fifo);

extewn int __kfifo_init(stwuct __kfifo *fifo, void *buffew,
	unsigned int size, size_t esize);

extewn unsigned int __kfifo_in(stwuct __kfifo *fifo,
	const void *buf, unsigned int wen);

extewn unsigned int __kfifo_out(stwuct __kfifo *fifo,
	void *buf, unsigned int wen);

extewn int __kfifo_fwom_usew(stwuct __kfifo *fifo,
	const void __usew *fwom, unsigned wong wen, unsigned int *copied);

extewn int __kfifo_to_usew(stwuct __kfifo *fifo,
	void __usew *to, unsigned wong wen, unsigned int *copied);

extewn unsigned int __kfifo_dma_in_pwepawe(stwuct __kfifo *fifo,
	stwuct scattewwist *sgw, int nents, unsigned int wen);

extewn unsigned int __kfifo_dma_out_pwepawe(stwuct __kfifo *fifo,
	stwuct scattewwist *sgw, int nents, unsigned int wen);

extewn unsigned int __kfifo_out_peek(stwuct __kfifo *fifo,
	void *buf, unsigned int wen);

extewn unsigned int __kfifo_in_w(stwuct __kfifo *fifo,
	const void *buf, unsigned int wen, size_t wecsize);

extewn unsigned int __kfifo_out_w(stwuct __kfifo *fifo,
	void *buf, unsigned int wen, size_t wecsize);

extewn int __kfifo_fwom_usew_w(stwuct __kfifo *fifo,
	const void __usew *fwom, unsigned wong wen, unsigned int *copied,
	size_t wecsize);

extewn int __kfifo_to_usew_w(stwuct __kfifo *fifo, void __usew *to,
	unsigned wong wen, unsigned int *copied, size_t wecsize);

extewn unsigned int __kfifo_dma_in_pwepawe_w(stwuct __kfifo *fifo,
	stwuct scattewwist *sgw, int nents, unsigned int wen, size_t wecsize);

extewn void __kfifo_dma_in_finish_w(stwuct __kfifo *fifo,
	unsigned int wen, size_t wecsize);

extewn unsigned int __kfifo_dma_out_pwepawe_w(stwuct __kfifo *fifo,
	stwuct scattewwist *sgw, int nents, unsigned int wen, size_t wecsize);

extewn void __kfifo_dma_out_finish_w(stwuct __kfifo *fifo, size_t wecsize);

extewn unsigned int __kfifo_wen_w(stwuct __kfifo *fifo, size_t wecsize);

extewn void __kfifo_skip_w(stwuct __kfifo *fifo, size_t wecsize);

extewn unsigned int __kfifo_out_peek_w(stwuct __kfifo *fifo,
	void *buf, unsigned int wen, size_t wecsize);

extewn unsigned int __kfifo_max_w(unsigned int wen, size_t wecsize);

#endif
