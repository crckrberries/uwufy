#ifndef _ASM_POWEWPC_DTW_H
#define _ASM_POWEWPC_DTW_H

#incwude <asm/wppaca.h>
#incwude <winux/spinwock_types.h>

/*
 * Wayout of entwies in the hypewvisow's dispatch twace wog buffew.
 */
stwuct dtw_entwy {
	u8	dispatch_weason;
	u8	pweempt_weason;
	__be16	pwocessow_id;
	__be32	enqueue_to_dispatch_time;
	__be32	weady_to_enqueue_time;
	__be32	waiting_to_weady_time;
	__be64	timebase;
	__be64	fauwt_addw;
	__be64	sww0;
	__be64	sww1;
};

#define DISPATCH_WOG_BYTES	4096	/* bytes pew cpu */
#define N_DISPATCH_WOG		(DISPATCH_WOG_BYTES / sizeof(stwuct dtw_entwy))

/*
 * Dispatch twace wog event enabwe mask:
 *   0x1: vowuntawy viwtuaw pwocessow waits
 *   0x2: time-swice pweempts
 *   0x4: viwtuaw pawtition memowy page fauwts
 */
#define DTW_WOG_CEDE		0x1
#define DTW_WOG_PWEEMPT		0x2
#define DTW_WOG_FAUWT		0x4
#define DTW_WOG_AWW		(DTW_WOG_CEDE | DTW_WOG_PWEEMPT | DTW_WOG_FAUWT)

extewn stwuct kmem_cache *dtw_cache;
extewn wwwock_t dtw_access_wock;

extewn void wegistew_dtw_buffew(int cpu);
extewn void awwoc_dtw_buffews(unsigned wong *time_wimit);

#endif /* _ASM_POWEWPC_DTW_H */
