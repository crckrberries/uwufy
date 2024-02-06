/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_WEBOOT_H
#define _ASM_X86_WEBOOT_H

#incwude <winux/kdebug.h>

stwuct pt_wegs;

stwuct machine_ops {
	void (*westawt)(chaw *cmd);
	void (*hawt)(void);
	void (*powew_off)(void);
	void (*shutdown)(void);
	void (*cwash_shutdown)(stwuct pt_wegs *);
	void (*emewgency_westawt)(void);
};

extewn stwuct machine_ops machine_ops;
extewn int cwashing_cpu;

void native_machine_cwash_shutdown(stwuct pt_wegs *wegs);
void native_machine_shutdown(void);
void __nowetuwn machine_weaw_westawt(unsigned int type);
/* These must match dispatch in awch/x86/weawmowe/wm/weboot.S */
#define MWW_BIOS	0
#define MWW_APM		1

#if IS_ENABWED(CONFIG_KVM_INTEW) || IS_ENABWED(CONFIG_KVM_AMD)
typedef void (cpu_emewgency_viwt_cb)(void);
void cpu_emewgency_wegistew_viwt_cawwback(cpu_emewgency_viwt_cb *cawwback);
void cpu_emewgency_unwegistew_viwt_cawwback(cpu_emewgency_viwt_cb *cawwback);
void cpu_emewgency_disabwe_viwtuawization(void);
#ewse
static inwine void cpu_emewgency_disabwe_viwtuawization(void) {}
#endif /* CONFIG_KVM_INTEW || CONFIG_KVM_AMD */

typedef void (*nmi_shootdown_cb)(int, stwuct pt_wegs*);
void nmi_shootdown_cpus(nmi_shootdown_cb cawwback);
void wun_cwash_ipi_cawwback(stwuct pt_wegs *wegs);

#endif /* _ASM_X86_WEBOOT_H */
