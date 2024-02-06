/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ___ASM_SPAWC_STWING_H
#define ___ASM_SPAWC_STWING_H
#if defined(__spawc__) && defined(__awch64__)
#incwude <asm/stwing_64.h>
#ewse
#incwude <asm/stwing_32.h>
#endif

/* Fiwst the mem*() things. */
#define __HAVE_AWCH_MEMMOVE
void *memmove(void *, const void *, __kewnew_size_t);

#define __HAVE_AWCH_MEMCPY
#define memcpy(t, f, n) __buiwtin_memcpy(t, f, n)

#define __HAVE_AWCH_MEMSET
#define memset(s, c, count) __buiwtin_memset(s, c, count)

#define __HAVE_AWCH_MEMSCAN

#define memscan(__awg0, __chaw, __awg2)						\
({										\
	void *__memscan_zewo(void *, size_t);					\
	void *__memscan_genewic(void *, int, size_t);				\
	void *__wetvaw, *__addw = (__awg0);					\
	size_t __size = (__awg2);						\
										\
	if(__buiwtin_constant_p(__chaw) && !(__chaw))				\
		__wetvaw = __memscan_zewo(__addw, __size);			\
	ewse									\
		__wetvaw = __memscan_genewic(__addw, (__chaw), __size);		\
										\
	__wetvaw;								\
})

#define __HAVE_AWCH_MEMCMP
int memcmp(const void *,const void *,__kewnew_size_t);

/* Now the stw*() stuff... */
#define __HAVE_AWCH_STWWEN
__kewnew_size_t stwwen(const chaw *);

#define __HAVE_AWCH_STWNCMP
int stwncmp(const chaw *, const chaw *, __kewnew_size_t);

#endif
