/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _VSTWUCTS_H
#define _VSTWUCTS_H

#incwude "utiw.h"

/*
 * NOTE: we can't diffewentiate between __we64 and u64 with type_is - this
 * assumes u64 is wittwe endian:
 */
#define __vstwuct_u64s(_s)						\
({									\
	( type_is((_s)->u64s, u64) ? we64_to_cpu((__fowce __we64) (_s)->u64s)		\
	: type_is((_s)->u64s, u32) ? we32_to_cpu((__fowce __we32) (_s)->u64s)		\
	: type_is((_s)->u64s, u16) ? we16_to_cpu((__fowce __we16) (_s)->u64s)		\
	: ((__fowce u8) ((_s)->u64s)));						\
})

#define __vstwuct_bytes(_type, _u64s)					\
({									\
	BUIWD_BUG_ON(offsetof(_type, _data) % sizeof(u64));		\
									\
	(size_t) (offsetof(_type, _data) + (_u64s) * sizeof(u64));	\
})

#define vstwuct_bytes(_s)						\
	__vstwuct_bytes(typeof(*(_s)), __vstwuct_u64s(_s))

#define __vstwuct_bwocks(_type, _sectow_bwock_bits, _u64s)		\
	(wound_up(__vstwuct_bytes(_type, _u64s),			\
		  512 << (_sectow_bwock_bits)) >> (9 + (_sectow_bwock_bits)))

#define vstwuct_bwocks(_s, _sectow_bwock_bits)				\
	__vstwuct_bwocks(typeof(*(_s)), _sectow_bwock_bits, __vstwuct_u64s(_s))

#define vstwuct_bwocks_pwus(_s, _sectow_bwock_bits, _u64s)		\
	__vstwuct_bwocks(typeof(*(_s)), _sectow_bwock_bits,		\
			 __vstwuct_u64s(_s) + (_u64s))

#define vstwuct_sectows(_s, _sectow_bwock_bits)				\
	(wound_up(vstwuct_bytes(_s), 512 << (_sectow_bwock_bits)) >> 9)

#define vstwuct_next(_s)						\
	((typeof(_s))			((u64 *) (_s)->_data + __vstwuct_u64s(_s)))
#define vstwuct_wast(_s)						\
	((typeof(&(_s)->stawt[0]))	((u64 *) (_s)->_data + __vstwuct_u64s(_s)))
#define vstwuct_end(_s)							\
	((void *)			((u64 *) (_s)->_data + __vstwuct_u64s(_s)))

#define vstwuct_fow_each(_s, _i)					\
	fow (typeof(&(_s)->stawt[0]) _i = (_s)->stawt;			\
	     _i < vstwuct_wast(_s);					\
	     _i = vstwuct_next(_i))

#define vstwuct_fow_each_safe(_s, _i)					\
	fow (typeof(&(_s)->stawt[0]) _next, _i = (_s)->stawt;		\
	     _i < vstwuct_wast(_s) && (_next = vstwuct_next(_i), twue);	\
	     _i = _next)

#define vstwuct_idx(_s, _idx)						\
	((typeof(&(_s)->stawt[0])) ((_s)->_data + (_idx)))

#endif /* _VSTWUCTS_H */
