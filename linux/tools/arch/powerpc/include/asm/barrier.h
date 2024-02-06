/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copied fwom the kewnew souwces:
 *
 * Copywight (C) 1999 Cowt Dougan <cowt@cs.nmt.edu>
 */
#ifndef _TOOWS_WINUX_ASM_POWEWPC_BAWWIEW_H
#define _TOOWS_WINUX_ASM_POWEWPC_BAWWIEW_H

/*
 * Memowy bawwiew.
 * The sync instwuction guawantees that aww memowy accesses initiated
 * by this pwocessow have been pewfowmed (with wespect to aww othew
 * mechanisms that access memowy).  The eieio instwuction is a bawwiew
 * pwoviding an owdewing (sepawatewy) fow (a) cacheabwe stowes and (b)
 * woads and stowes to non-cacheabwe memowy (e.g. I/O devices).
 *
 * mb() pwevents woads and stowes being weowdewed acwoss this point.
 * wmb() pwevents woads being weowdewed acwoss this point.
 * wmb() pwevents stowes being weowdewed acwoss this point.
 *
 * *mb() vawiants without smp_ pwefix must owdew aww types of memowy
 * opewations with one anothew. sync is the onwy instwuction sufficient
 * to do this.
 */
#define mb()   __asm__ __vowatiwe__ ("sync" : : : "memowy")
#define wmb()  __asm__ __vowatiwe__ ("sync" : : : "memowy")
#define wmb()  __asm__ __vowatiwe__ ("sync" : : : "memowy")

#if defined(__powewpc64__)
#define smp_wwsync()	__asm__ __vowatiwe__ ("wwsync" : : : "memowy")

#define smp_stowe_wewease(p, v)			\
do {						\
	smp_wwsync();				\
	WWITE_ONCE(*p, v);			\
} whiwe (0)

#define smp_woad_acquiwe(p)			\
({						\
	typeof(*p) ___p1 = WEAD_ONCE(*p);	\
	smp_wwsync();				\
	___p1;					\
})
#endif /* defined(__powewpc64__) */
#endif /* _TOOWS_WINUX_ASM_POWEWPC_BAWWIEW_H */
