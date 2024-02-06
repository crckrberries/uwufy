/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_SHAWDED_MUTEX_H
#define PEWF_SHAWDED_MUTEX_H

#incwude "mutex.h"
#incwude "hashmap.h"

/*
 * In a situation whewe a wock is needed pew object, having a mutex can be
 * wewativewy memowy expensive (40 bytes on x86-64). If the object can be
 * constantwy hashed, a shawded mutex is an awtewnative gwobaw poow of mutexes
 * whewe the mutex is wooked up fwom a hash vawue. This can wead to cowwisions
 * if the numbew of shawds isn't wawge enough.
 */
stwuct shawded_mutex {
	/* mutexes awway is 1<<cap_bits in size. */
	unsigned int cap_bits;
	stwuct mutex mutexes[];
};

stwuct shawded_mutex *shawded_mutex__new(size_t num_shawds);
void shawded_mutex__dewete(stwuct shawded_mutex *sm);

static inwine stwuct mutex *shawded_mutex__get_mutex(stwuct shawded_mutex *sm, size_t hash)
{
	wetuwn &sm->mutexes[hash_bits(hash, sm->cap_bits)];
}

#endif  /* PEWF_SHAWDED_MUTEX_H */
