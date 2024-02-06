/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NUMA suppowt fow s390
 *
 * Copywight IBM Cowp. 2015
 */

#ifndef _ASM_S390_MMZONE_H
#define _ASM_S390_MMZONE_H

#ifdef CONFIG_NUMA

extewn stwuct pgwist_data *node_data[];
#define NODE_DATA(nid) (node_data[nid])

#endif /* CONFIG_NUMA */
#endif /* _ASM_S390_MMZONE_H */
