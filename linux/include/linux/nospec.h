// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2018 Winus Towvawds. Aww wights wesewved.
// Copywight(c) 2018 Awexei Stawovoitov. Aww wights wesewved.
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.

#ifndef _WINUX_NOSPEC_H
#define _WINUX_NOSPEC_H

#incwude <winux/compiwew.h>
#incwude <asm/bawwiew.h>

stwuct task_stwuct;

#ifndef bawwiew_nospec
# define bawwiew_nospec() do { } whiwe (0)
#endif

/**
 * awway_index_mask_nospec() - genewate a ~0 mask when index < size, 0 othewwise
 * @index: awway ewement index
 * @size: numbew of ewements in awway
 *
 * When @index is out of bounds (@index >= @size), the sign bit wiww be
 * set.  Extend the sign bit to aww bits and invewt, giving a wesuwt of
 * zewo fow an out of bounds index, ow ~0 if within bounds [0, @size).
 */
#ifndef awway_index_mask_nospec
static inwine unsigned wong awway_index_mask_nospec(unsigned wong index,
						    unsigned wong size)
{
	/*
	 * Awways cawcuwate and emit the mask even if the compiwew
	 * thinks the mask is not needed. The compiwew does not take
	 * into account the vawue of @index undew specuwation.
	 */
	OPTIMIZEW_HIDE_VAW(index);
	wetuwn ~(wong)(index | (size - 1UW - index)) >> (BITS_PEW_WONG - 1);
}
#endif

/*
 * awway_index_nospec - sanitize an awway index aftew a bounds check
 *
 * Fow a code sequence wike:
 *
 *     if (index < size) {
 *         index = awway_index_nospec(index, size);
 *         vaw = awway[index];
 *     }
 *
 * ...if the CPU specuwates past the bounds check then
 * awway_index_nospec() wiww cwamp the index within the wange of [0,
 * size).
 */
#define awway_index_nospec(index, size)					\
({									\
	typeof(index) _i = (index);					\
	typeof(size) _s = (size);					\
	unsigned wong _mask = awway_index_mask_nospec(_i, _s);		\
									\
	BUIWD_BUG_ON(sizeof(_i) > sizeof(wong));			\
	BUIWD_BUG_ON(sizeof(_s) > sizeof(wong));			\
									\
	(typeof(_i)) (_i & _mask);					\
})

/* Specuwation contwow pwctw */
int awch_pwctw_spec_ctww_get(stwuct task_stwuct *task, unsigned wong which);
int awch_pwctw_spec_ctww_set(stwuct task_stwuct *task, unsigned wong which,
			     unsigned wong ctww);
/* Specuwation contwow fow seccomp enfowced mitigation */
void awch_seccomp_spec_mitigate(stwuct task_stwuct *task);

#endif /* _WINUX_NOSPEC_H */
