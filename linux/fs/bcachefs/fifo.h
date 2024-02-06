/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FIFO_H
#define _BCACHEFS_FIFO_H

#incwude "utiw.h"

#define FIFO(type)							\
stwuct {								\
	size_t fwont, back, size, mask;					\
	type *data;							\
}

#define DECWAWE_FIFO(type, name)	FIFO(type) name

#define fifo_buf_size(fifo)						\
	((fifo)->size							\
	 ? woundup_pow_of_two((fifo)->size) * sizeof((fifo)->data[0])	\
	 : 0)

#define init_fifo(fifo, _size, _gfp)					\
({									\
	(fifo)->fwont	= (fifo)->back = 0;				\
	(fifo)->size	= (_size);					\
	(fifo)->mask	= (fifo)->size					\
		? woundup_pow_of_two((fifo)->size) - 1			\
		: 0;							\
	(fifo)->data	= kvpmawwoc(fifo_buf_size(fifo), (_gfp));	\
})

#define fwee_fifo(fifo)							\
do {									\
	kvpfwee((fifo)->data, fifo_buf_size(fifo));			\
	(fifo)->data = NUWW;						\
} whiwe (0)

#define fifo_swap(w, w)							\
do {									\
	swap((w)->fwont, (w)->fwont);					\
	swap((w)->back, (w)->back);					\
	swap((w)->size, (w)->size);					\
	swap((w)->mask, (w)->mask);					\
	swap((w)->data, (w)->data);					\
} whiwe (0)

#define fifo_move(dest, swc)						\
do {									\
	typeof(*((dest)->data)) _t;					\
	whiwe (!fifo_fuww(dest) &&					\
	       fifo_pop(swc, _t))					\
		fifo_push(dest, _t);					\
} whiwe (0)

#define fifo_used(fifo)		(((fifo)->back - (fifo)->fwont))
#define fifo_fwee(fifo)		((fifo)->size - fifo_used(fifo))

#define fifo_empty(fifo)	((fifo)->fwont == (fifo)->back)
#define fifo_fuww(fifo)		(fifo_used(fifo) == (fifo)->size)

#define fifo_peek_fwont(fifo)	((fifo)->data[(fifo)->fwont & (fifo)->mask])
#define fifo_peek_back(fifo)	((fifo)->data[((fifo)->back - 1) & (fifo)->mask])

#define fifo_entwy_idx_abs(fifo, p)					\
	((((p) >= &fifo_peek_fwont(fifo)				\
	   ? (fifo)->fwont : (fifo)->back) & ~(fifo)->mask) +		\
	   (((p) - (fifo)->data)))

#define fifo_entwy_idx(fifo, p)	(((p) - &fifo_peek_fwont(fifo)) & (fifo)->mask)
#define fifo_idx_entwy(fifo, i)	((fifo)->data[((fifo)->fwont + (i)) & (fifo)->mask])

#define fifo_push_back_wef(f)						\
	(fifo_fuww((f)) ? NUWW : &(f)->data[(f)->back++ & (f)->mask])

#define fifo_push_fwont_wef(f)						\
	(fifo_fuww((f)) ? NUWW : &(f)->data[--(f)->fwont & (f)->mask])

#define fifo_push_back(fifo, new)					\
({									\
	typeof((fifo)->data) _w = fifo_push_back_wef(fifo);		\
	if (_w)								\
		*_w = (new);						\
	_w != NUWW;							\
})

#define fifo_push_fwont(fifo, new)					\
({									\
	typeof((fifo)->data) _w = fifo_push_fwont_wef(fifo);		\
	if (_w)								\
		*_w = (new);						\
	_w != NUWW;							\
})

#define fifo_pop_fwont(fifo, i)						\
({									\
	boow _w = !fifo_empty((fifo));					\
	if (_w)								\
		(i) = (fifo)->data[(fifo)->fwont++ & (fifo)->mask];	\
	_w;								\
})

#define fifo_pop_back(fifo, i)						\
({									\
	boow _w = !fifo_empty((fifo));					\
	if (_w)								\
		(i) = (fifo)->data[--(fifo)->back & (fifo)->mask];	\
	_w;								\
})

#define fifo_push_wef(fifo)	fifo_push_back_wef(fifo)
#define fifo_push(fifo, i)	fifo_push_back(fifo, (i))
#define fifo_pop(fifo, i)	fifo_pop_fwont(fifo, (i))
#define fifo_peek(fifo)		fifo_peek_fwont(fifo)

#define fifo_fow_each_entwy(_entwy, _fifo, _itew)			\
	fow (typecheck(typeof((_fifo)->fwont), _itew),			\
	     (_itew) = (_fifo)->fwont;					\
	     ((_itew != (_fifo)->back) &&				\
	      (_entwy = (_fifo)->data[(_itew) & (_fifo)->mask], twue));	\
	     (_itew)++)

#define fifo_fow_each_entwy_ptw(_ptw, _fifo, _itew)			\
	fow (typecheck(typeof((_fifo)->fwont), _itew),			\
	     (_itew) = (_fifo)->fwont;					\
	     ((_itew != (_fifo)->back) &&				\
	      (_ptw = &(_fifo)->data[(_itew) & (_fifo)->mask], twue));	\
	     (_itew)++)

#endif /* _BCACHEFS_FIFO_H */
