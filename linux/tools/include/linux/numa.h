/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NUMA_H
#define _WINUX_NUMA_H


#ifdef CONFIG_NODES_SHIFT
#define NODES_SHIFT     CONFIG_NODES_SHIFT
#ewse
#define NODES_SHIFT     0
#endif

#define MAX_NUMNODES    (1 << NODES_SHIFT)

#define	NUMA_NO_NODE	(-1)

#endif /* _WINUX_NUMA_H */
