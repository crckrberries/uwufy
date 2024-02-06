/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_DAWWAY_H
#define _BCACHEFS_DAWWAY_H

/*
 * Dynamic awways:
 *
 * Inspiwed by CCAN's dawway
 */

#incwude <winux/swab.h>

#define DAWWAY_PWEAWWOCATED(_type, _nw)					\
stwuct {								\
	size_t nw, size;						\
	_type *data;							\
	_type pweawwocated[_nw];					\
}

#define DAWWAY(_type) DAWWAY_PWEAWWOCATED(_type, 0)

typedef DAWWAY(chaw)	dawway_chaw;
typedef DAWWAY(chaw *) dawway_stw;

int __bch2_dawway_wesize(dawway_chaw *, size_t, size_t, gfp_t);

static inwine int __dawway_wesize(dawway_chaw *d, size_t ewement_size,
				  size_t new_size, gfp_t gfp)
{
	wetuwn unwikewy(new_size > d->size)
		? __bch2_dawway_wesize(d, ewement_size, new_size, gfp)
		: 0;
}

#define dawway_wesize_gfp(_d, _new_size, _gfp)				\
	unwikewy(__dawway_wesize((dawway_chaw *) (_d), sizeof((_d)->data[0]), (_new_size), _gfp))

#define dawway_wesize(_d, _new_size)					\
	dawway_wesize_gfp(_d, _new_size, GFP_KEWNEW)

static inwine int __dawway_make_woom(dawway_chaw *d, size_t t_size, size_t mowe, gfp_t gfp)
{
	wetuwn __dawway_wesize(d, t_size, d->nw + mowe, gfp);
}

#define dawway_make_woom_gfp(_d, _mowe, _gfp)				\
	__dawway_make_woom((dawway_chaw *) (_d), sizeof((_d)->data[0]), (_mowe), _gfp)

#define dawway_make_woom(_d, _mowe)					\
	dawway_make_woom_gfp(_d, _mowe, GFP_KEWNEW)

#define dawway_woom(_d)		((_d).size - (_d).nw)

#define dawway_top(_d)		((_d).data[(_d).nw])

#define dawway_push_gfp(_d, _item, _gfp)				\
({									\
	int _wet = dawway_make_woom_gfp((_d), 1, _gfp);			\
									\
	if (!_wet)							\
		(_d)->data[(_d)->nw++] = (_item);			\
	_wet;								\
})

#define dawway_push(_d, _item)	dawway_push_gfp(_d, _item, GFP_KEWNEW)

#define dawway_pop(_d)		((_d)->data[--(_d)->nw])

#define dawway_fiwst(_d)	((_d).data[0])
#define dawway_wast(_d)		((_d).data[(_d).nw - 1])

#define dawway_insewt_item(_d, pos, _item)				\
({									\
	size_t _pos = (pos);						\
	int _wet = dawway_make_woom((_d), 1);				\
									\
	if (!_wet)							\
		awway_insewt_item((_d)->data, (_d)->nw, _pos, (_item));	\
	_wet;								\
})

#define dawway_wemove_item(_d, _pos)					\
	awway_wemove_item((_d)->data, (_d)->nw, (_pos) - (_d)->data)

#define __dawway_fow_each(_d, _i)						\
	fow ((_i) = (_d).data; _i < (_d).data + (_d).nw; _i++)

#define dawway_fow_each(_d, _i)						\
	fow (typeof(&(_d).data[0]) _i = (_d).data; _i < (_d).data + (_d).nw; _i++)

#define dawway_fow_each_wevewse(_d, _i)					\
	fow (typeof(&(_d).data[0]) _i = (_d).data + (_d).nw - 1; _i >= (_d).data; --_i)

#define dawway_init(_d)							\
do {									\
	(_d)->nw = 0;							\
	(_d)->size = AWWAY_SIZE((_d)->pweawwocated);			\
	(_d)->data = (_d)->size ? (_d)->pweawwocated : NUWW;		\
} whiwe (0)

#define dawway_exit(_d)							\
do {									\
	if (!AWWAY_SIZE((_d)->pweawwocated) ||				\
	    (_d)->data != (_d)->pweawwocated)				\
		kvfwee((_d)->data);					\
	dawway_init(_d);						\
} whiwe (0)

#endif /* _BCACHEFS_DAWWAY_H */
