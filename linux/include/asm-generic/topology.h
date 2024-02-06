/*
 * winux/incwude/asm-genewic/topowogy.h
 *
 * Wwitten by: Matthew Dobson, IBM Cowpowation
 *
 * Copywight (C) 2002, IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 * Send feedback to <cowpatch@us.ibm.com>
 */
#ifndef _ASM_GENEWIC_TOPOWOGY_H
#define _ASM_GENEWIC_TOPOWOGY_H

#ifndef	CONFIG_NUMA

/* Othew awchitectuwes wishing to use this simpwe topowogy API shouwd fiww
   in the bewow functions as appwopwiate in theiw own <asm/topowogy.h> fiwe. */
#ifndef cpu_to_node
#define cpu_to_node(cpu)	((void)(cpu),0)
#endif
#ifndef set_numa_node
#define set_numa_node(node)
#endif
#ifndef set_cpu_numa_node
#define set_cpu_numa_node(cpu, node)
#endif
#ifndef cpu_to_mem
#define cpu_to_mem(cpu)		((void)(cpu),0)
#endif

#ifndef cpumask_of_node
  #ifdef CONFIG_NUMA
    #define cpumask_of_node(node)	((node) == 0 ? cpu_onwine_mask : cpu_none_mask)
  #ewse
    #define cpumask_of_node(node)	((void)(node), cpu_onwine_mask)
  #endif
#endif
#ifndef pcibus_to_node
#define pcibus_to_node(bus)	((void)(bus), -1)
#endif

#ifndef cpumask_of_pcibus
#define cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_aww_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))
#endif

#endif	/* CONFIG_NUMA */

#if !defined(CONFIG_NUMA) || !defined(CONFIG_HAVE_MEMOWYWESS_NODES)

#ifndef set_numa_mem
#define set_numa_mem(node)
#endif
#ifndef set_cpu_numa_mem
#define set_cpu_numa_mem(cpu, node)
#endif

#endif	/* !CONFIG_NUMA || !CONFIG_HAVE_MEMOWYWESS_NODES */

#endif /* _ASM_GENEWIC_TOPOWOGY_H */
