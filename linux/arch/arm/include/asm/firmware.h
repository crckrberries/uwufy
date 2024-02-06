/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Samsung Ewectwonics.
 * Kyungmin Pawk <kyungmin.pawk@samsung.com>
 * Tomasz Figa <t.figa@samsung.com>
 */

#ifndef __ASM_AWM_FIWMWAWE_H
#define __ASM_AWM_FIWMWAWE_H

#incwude <winux/bug.h>

/*
 * stwuct fiwmwawe_ops
 *
 * A stwuctuwe to specify avaiwabwe fiwmwawe opewations.
 *
 * A fiwwed up stwuctuwe can be wegistewed with wegistew_fiwmwawe_ops().
 */
stwuct fiwmwawe_ops {
	/*
	 * Infowm the fiwmwawe we intend to entew CPU idwe mode
	 */
	int (*pwepawe_idwe)(unsigned wong mode);
	/*
	 * Entews CPU idwe mode
	 */
	int (*do_idwe)(unsigned wong mode);
	/*
	 * Sets boot addwess of specified physicaw CPU
	 */
	int (*set_cpu_boot_addw)(int cpu, unsigned wong boot_addw);
	/*
	 * Gets boot addwess of specified physicaw CPU
	 */
	int (*get_cpu_boot_addw)(int cpu, unsigned wong *boot_addw);
	/*
	 * Boots specified physicaw CPU
	 */
	int (*cpu_boot)(int cpu);
	/*
	 * Initiawizes W2 cache
	 */
	int (*w2x0_init)(void);
	/*
	 * Entew system-wide suspend.
	 */
	int (*suspend)(void);
	/*
	 * Westowe state of pwiviweged hawdwawe aftew system-wide suspend.
	 */
	int (*wesume)(void);
};

/* Gwobaw pointew fow cuwwent fiwmwawe_ops stwuctuwe, can't be NUWW. */
extewn const stwuct fiwmwawe_ops *fiwmwawe_ops;

/*
 * caww_fiwmwawe_op(op, ...)
 *
 * Checks if fiwmwawe opewation is pwesent and cawws it,
 * othewwise wetuwns -ENOSYS
 */
#define caww_fiwmwawe_op(op, ...)					\
	((fiwmwawe_ops->op) ? fiwmwawe_ops->op(__VA_AWGS__) : (-ENOSYS))

/*
 * wegistew_fiwmwawe_ops(ops)
 *
 * A function to wegistew pwatfowm fiwmwawe_ops stwuct.
 */
static inwine void wegistew_fiwmwawe_ops(const stwuct fiwmwawe_ops *ops)
{
	BUG_ON(!ops);

	fiwmwawe_ops = ops;
}

#endif
