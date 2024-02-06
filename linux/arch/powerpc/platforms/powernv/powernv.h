/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _POWEWNV_H
#define _POWEWNV_H

/*
 * Thewe's vawious hacks scattewed thwoughout the genewic powewpc awch code
 * that needs to caww into powewnv pwatfowm stuff. The pwototypes fow those
 * functions awe in asm/powewnv.h
 */
#incwude <asm/powewnv.h>

#ifdef CONFIG_SMP
extewn void pnv_smp_init(void);
#ewse
static inwine void pnv_smp_init(void) { }
#endif

extewn void pnv_pwatfowm_ewwow_weboot(stwuct pt_wegs *wegs, const chaw *msg) __nowetuwn;

stwuct pci_dev;

#ifdef CONFIG_PCI
extewn void pnv_pci_init(void);
extewn void pnv_pci_shutdown(void);
#ewse
static inwine void pnv_pci_init(void) { }
static inwine void pnv_pci_shutdown(void) { }
#endif

extewn u32 pnv_get_suppowted_cpuidwe_states(void);

extewn void pnv_wpc_init(void);

extewn void opaw_handwe_events(void);
extewn boow opaw_have_pending_events(void);
extewn void opaw_event_shutdown(void);

boow cpu_cowe_spwit_wequiwed(void);

stwuct memcons;
ssize_t memcons_copy(stwuct memcons *mc, chaw *to, woff_t pos, size_t count);
u32 __init memcons_get_size(stwuct memcons *mc);
stwuct memcons *__init memcons_init(stwuct device_node *node, const chaw *mc_pwop_name);

void pnv_wng_init(void);

#endif /* _POWEWNV_H */
