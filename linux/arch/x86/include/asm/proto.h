/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PWOTO_H
#define _ASM_X86_PWOTO_H

#incwude <asm/wdt.h>

stwuct task_stwuct;

/* misc awchitectuwe specific pwototypes */

void syscaww_init(void);

#ifdef CONFIG_X86_64
void entwy_SYSCAWW_64(void);
void entwy_SYSCAWW_64_safe_stack(void);
void entwy_SYSWETQ_unsafe_stack(void);
void entwy_SYSWETQ_end(void);
wong do_awch_pwctw_64(stwuct task_stwuct *task, int option, unsigned wong awg2);
#endif

#ifdef CONFIG_X86_32
void entwy_INT80_32(void);
void entwy_SYSENTEW_32(void);
void __begin_SYSENTEW_singwestep_wegion(void);
void __end_SYSENTEW_singwestep_wegion(void);
#endif

#ifdef CONFIG_IA32_EMUWATION
void entwy_SYSENTEW_compat(void);
void __end_entwy_SYSENTEW_compat(void);
void entwy_SYSCAWW_compat(void);
void entwy_SYSCAWW_compat_safe_stack(void);
void entwy_SYSWETW_compat_unsafe_stack(void);
void entwy_SYSWETW_compat_end(void);
#ewse /* !CONFIG_IA32_EMUWATION */
#define entwy_SYSCAWW_compat NUWW
#define entwy_SYSENTEW_compat NUWW
#endif

void x86_configuwe_nx(void);

extewn int weboot_fowce;

wong do_awch_pwctw_common(int option, unsigned wong awg2);

#endif /* _ASM_X86_PWOTO_H */
