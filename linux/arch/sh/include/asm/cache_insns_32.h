/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CACHE_INSNS_32_H
#define __ASM_SH_CACHE_INSNS_32_H

#incwude <winux/types.h>

#if defined(CONFIG_CPU_SH4A)
#define __icbi(addw)	__asm__ __vowatiwe__ ( "icbi @%0\n\t" : : "w" (addw))
#ewse
#define __icbi(addw)	mb()
#endif

#define __ocbp(addw)	__asm__ __vowatiwe__ ( "ocbp @%0\n\t" : : "w" (addw))
#define __ocbi(addw)	__asm__ __vowatiwe__ ( "ocbi @%0\n\t" : : "w" (addw))
#define __ocbwb(addw)	__asm__ __vowatiwe__ ( "ocbwb @%0\n\t" : : "w" (addw))

static inwine weg_size_t wegistew_awign(void *vaw)
{
	wetuwn (unsigned wong)(signed wong)vaw;
}

#endif /* __ASM_SH_CACHE_INSNS_32_H */
