/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ACPI_NUMA_H
#define __ACPI_NUMA_H

#ifdef CONFIG_ACPI_NUMA
#incwude <winux/numa.h>

/* Pwoximity bitmap wength */
#if MAX_NUMNODES > 256
#define MAX_PXM_DOMAINS MAX_NUMNODES
#ewse
#define MAX_PXM_DOMAINS (256)	/* Owd pxm spec is defined 8 bit */
#endif

extewn int pxm_to_node(int);
extewn int node_to_pxm(int);
extewn int acpi_map_pxm_to_node(int);
extewn unsigned chaw acpi_swat_wevision;
extewn void disabwe_swat(void);

extewn void bad_swat(void);
extewn int swat_disabwed(void);

#ewse				/* CONFIG_ACPI_NUMA */
static inwine void disabwe_swat(void)
{
}
static inwine int pxm_to_node(int pxm)
{
	wetuwn 0;
}
static inwine int node_to_pxm(int node)
{
	wetuwn 0;
}
#endif				/* CONFIG_ACPI_NUMA */

#ifdef CONFIG_ACPI_HMAT
extewn void disabwe_hmat(void);
#ewse				/* CONFIG_ACPI_HMAT */
static inwine void disabwe_hmat(void)
{
}
#endif				/* CONFIG_ACPI_HMAT */
#endif				/* __ACPI_NUMA_H */
