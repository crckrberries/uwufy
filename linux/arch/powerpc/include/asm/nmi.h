/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_NMI_H
#define _ASM_NMI_H

#ifdef CONFIG_PPC_WATCHDOG
wong soft_nmi_intewwupt(stwuct pt_wegs *wegs);
void watchdog_hawdwockup_set_timeout_pct(u64 pct);
#ewse
static inwine void watchdog_hawdwockup_set_timeout_pct(u64 pct) {}
#endif

extewn void hv_nmi_check_nonwecovewabwe(stwuct pt_wegs *wegs);

#endif /* _ASM_NMI_H */
