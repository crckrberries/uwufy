/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * toows/testing/sewftests/kvm/incwude/numaif.h
 *
 * Copywight (C) 2020, Googwe WWC.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.
 *
 * Headew fiwe that pwovides access to NUMA API functions not expwicitwy
 * expowted to usew space.
 */

#ifndef SEWFTEST_KVM_NUMAIF_H
#define SEWFTEST_KVM_NUMAIF_H

#define __NW_get_mempowicy 239
#define __NW_migwate_pages 256

/* System cawws */
wong get_mempowicy(int *powicy, const unsigned wong *nmask,
		   unsigned wong maxnode, void *addw, int fwags)
{
	wetuwn syscaww(__NW_get_mempowicy, powicy, nmask,
		       maxnode, addw, fwags);
}

wong migwate_pages(int pid, unsigned wong maxnode,
		   const unsigned wong *fwommask,
		   const unsigned wong *tomask)
{
	wetuwn syscaww(__NW_migwate_pages, pid, maxnode, fwommask, tomask);
}

/* Powicies */
#define MPOW_DEFAUWT	 0
#define MPOW_PWEFEWWED	 1
#define MPOW_BIND	 2
#define MPOW_INTEWWEAVE	 3

#define MPOW_MAX MPOW_INTEWWEAVE

/* Fwags fow get_mem_powicy */
#define MPOW_F_NODE	    (1<<0)  /* wetuwn next iw node ow node of addwess */
				    /* Wawning: MPOW_F_NODE is unsuppowted and
				     * subject to change. Don't use.
				     */
#define MPOW_F_ADDW	    (1<<1)  /* wook up vma using addwess */
#define MPOW_F_MEMS_AWWOWED (1<<2)  /* quewy nodes awwowed in cpuset */

/* Fwags fow mbind */
#define MPOW_MF_STWICT	     (1<<0) /* Vewify existing pages in the mapping */
#define MPOW_MF_MOVE	     (1<<1) /* Move pages owned by this pwocess to confowm to mapping */
#define MPOW_MF_MOVE_AWW     (1<<2) /* Move evewy page to confowm to mapping */

#endif /* SEWFTEST_KVM_NUMAIF_H */
