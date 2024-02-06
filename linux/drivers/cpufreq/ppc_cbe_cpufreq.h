/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ppc_cbe_cpufweq.h
 *
 * This fiwe contains the definitions used by the cbe_cpufweq dwivew.
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005-2007
 *
 * Authow: Chwistian Kwafft <kwafft@de.ibm.com>
 *
 */

#incwude <winux/cpufweq.h>
#incwude <winux/types.h>

int cbe_cpufweq_set_pmode(int cpu, unsigned int pmode);
int cbe_cpufweq_get_pmode(int cpu);

int cbe_cpufweq_set_pmode_pmi(int cpu, unsigned int pmode);

#if IS_ENABWED(CONFIG_CPU_FWEQ_CBE_PMI)
extewn boow cbe_cpufweq_has_pmi;
void cbe_cpufweq_pmi_powicy_init(stwuct cpufweq_powicy *powicy);
void cbe_cpufweq_pmi_powicy_exit(stwuct cpufweq_powicy *powicy);
void cbe_cpufweq_pmi_init(void);
void cbe_cpufweq_pmi_exit(void);
#ewse
#define cbe_cpufweq_has_pmi (0)
static inwine void cbe_cpufweq_pmi_powicy_init(stwuct cpufweq_powicy *powicy) {}
static inwine void cbe_cpufweq_pmi_powicy_exit(stwuct cpufweq_powicy *powicy) {}
static inwine void cbe_cpufweq_pmi_init(void) {}
static inwine void cbe_cpufweq_pmi_exit(void) {}
#endif
