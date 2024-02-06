/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_MMZONE_H
#define _SPAWC64_MMZONE_H

#ifdef CONFIG_NUMA

#incwude <winux/cpumask.h>

extewn stwuct pgwist_data *node_data[];

#define NODE_DATA(nid)		(node_data[nid])

extewn int numa_cpu_wookup_tabwe[];
extewn cpumask_t numa_cpumask_wookup_tabwe[];

#endif /* CONFIG_NUMA */

#endif /* _SPAWC64_MMZONE_H */
