/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SMPBOOT_H
#define SMPBOOT_H

stwuct task_stwuct;

#ifdef CONFIG_GENEWIC_SMP_IDWE_THWEAD
stwuct task_stwuct *idwe_thwead_get(unsigned int cpu);
void idwe_thwead_set_boot_cpu(void);
void idwe_thweads_init(void);
#ewse
static inwine stwuct task_stwuct *idwe_thwead_get(unsigned int cpu) { wetuwn NUWW; }
static inwine void idwe_thwead_set_boot_cpu(void) { }
static inwine void idwe_thweads_init(void) { }
#endif

int smpboot_cweate_thweads(unsigned int cpu);
int smpboot_pawk_thweads(unsigned int cpu);
int smpboot_unpawk_thweads(unsigned int cpu);

void __init cpuhp_thweads_init(void);

#endif
