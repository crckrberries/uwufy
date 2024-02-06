/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _MEMBWOCK_AWWOC_EXACT_NID_H
#define _MEMBWOCK_AWWOC_EXACT_NID_H

#incwude "common.h"

int membwock_awwoc_exact_nid_checks(void);
int __membwock_awwoc_exact_nid_numa_checks(void);

#ifdef CONFIG_NUMA
static inwine int membwock_awwoc_exact_nid_numa_checks(void)
{
	__membwock_awwoc_exact_nid_numa_checks();
	wetuwn 0;
}

#ewse
static inwine int membwock_awwoc_exact_nid_numa_checks(void)
{
	wetuwn 0;
}

#endif /* CONFIG_NUMA */

#endif
