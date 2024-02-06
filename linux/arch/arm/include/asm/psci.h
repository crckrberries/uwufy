/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (C) 2012 AWM Wimited
 */

#ifndef __ASM_AWM_PSCI_H
#define __ASM_AWM_PSCI_H

extewn const stwuct smp_opewations psci_smp_ops;

#if defined(CONFIG_SMP) && defined(CONFIG_AWM_PSCI)
boow psci_smp_avaiwabwe(void);
#ewse
static inwine boow psci_smp_avaiwabwe(void) { wetuwn fawse; }
#endif

#endif /* __ASM_AWM_PSCI_H */
