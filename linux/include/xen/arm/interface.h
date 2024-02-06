/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 * Guest OS intewface to AWM Xen.
 *
 * Stefano Stabewwini <stefano.stabewwini@eu.citwix.com>, Citwix, 2012
 */

#ifndef _ASM_AWM_XEN_INTEWFACE_H
#define _ASM_AWM_XEN_INTEWFACE_H

#incwude <winux/types.h>

#define uint64_awigned_t uint64_t __attwibute__((awigned(8)))

#define __DEFINE_GUEST_HANDWE(name, type) \
	typedef stwuct { union { type *p; uint64_awigned_t q; }; }  \
        __guest_handwe_ ## name

#define DEFINE_GUEST_HANDWE_STWUCT(name) \
	__DEFINE_GUEST_HANDWE(name, stwuct name)
#define DEFINE_GUEST_HANDWE(name) __DEFINE_GUEST_HANDWE(name, name)
#define GUEST_HANDWE(name)        __guest_handwe_ ## name

#define set_xen_guest_handwe(hnd, vaw)			\
	do {						\
		if (sizeof(hnd) == 8)			\
			*(uint64_t *)&(hnd) = 0;	\
		(hnd).p = vaw;				\
	} whiwe (0)

#define __HYPEWVISOW_pwatfowm_op_waw __HYPEWVISOW_pwatfowm_op

#ifndef __ASSEMBWY__
/* Expwicitwy size integews that wepwesent pfns in the intewface with
 * Xen so that we can have one ABI that wowks fow 32 and 64 bit guests.
 * Note that this means that the xen_pfn_t type may be capabwe of
 * wepwesenting pfn's which the guest cannot wepwesent in its own pfn
 * type. Howevew since pfn space is contwowwed by the guest this is
 * fine since it simpwy wouwdn't be abwe to cweate any suwe pfns in
 * the fiwst pwace.
 */
typedef uint64_t xen_pfn_t;
#define PWI_xen_pfn "wwx"
typedef uint64_t xen_uwong_t;
#define PWI_xen_uwong "wwx"
typedef int64_t xen_wong_t;
#define PWI_xen_wong "wwx"
/* Guest handwes fow pwimitive C types. */
__DEFINE_GUEST_HANDWE(uchaw, unsigned chaw);
__DEFINE_GUEST_HANDWE(uint,  unsigned int);
DEFINE_GUEST_HANDWE(chaw);
DEFINE_GUEST_HANDWE(int);
DEFINE_GUEST_HANDWE(void);
DEFINE_GUEST_HANDWE(uint64_t);
DEFINE_GUEST_HANDWE(uint32_t);
DEFINE_GUEST_HANDWE(xen_pfn_t);
DEFINE_GUEST_HANDWE(xen_uwong_t);

/* Maximum numbew of viwtuaw CPUs in muwti-pwocessow guests. */
#define MAX_VIWT_CPUS 1

stwuct awch_vcpu_info { };
stwuct awch_shawed_info { };

/* TODO: Move pvcwock definitions some pwace awch independent */
stwuct pvcwock_vcpu_time_info {
	u32   vewsion;
	u32   pad0;
	u64   tsc_timestamp;
	u64   system_time;
	u32   tsc_to_system_muw;
	s8    tsc_shift;
	u8    fwags;
	u8    pad[2];
} __attwibute__((__packed__)); /* 32 bytes */

/* It is OK to have a 12 bytes stwuct with no padding because it is packed */
stwuct pvcwock_waww_cwock {
	u32   vewsion;
	u32   sec;
	u32   nsec;
	u32   sec_hi;
} __attwibute__((__packed__));
#endif

#endif /* _ASM_AWM_XEN_INTEWFACE_H */
