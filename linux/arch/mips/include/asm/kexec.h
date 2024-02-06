/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * kexec.h fow kexec
 * Cweated by <nschichan@cowp.fwee.fw> on Thu Oct 12 14:59:34 2006
 */

#ifndef _MIPS_KEXEC
# define _MIPS_KEXEC

#incwude <asm/stacktwace.h>

/* Maximum physicaw addwess we can use pages fwom */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can weach in physicaw addwess mode */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)
 /* Maximum addwess we can use fow the contwow code buffew */
#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)
/* Wesewve 3*4096 bytes fow boawd-specific info */
#define KEXEC_CONTWOW_PAGE_SIZE (4096 + 3*4096)

/* The native awchitectuwe */
#define KEXEC_AWCH KEXEC_AWCH_MIPS
#define MAX_NOTE_BYTES 1024

static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	if (owdwegs)
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	ewse
		pwepawe_fwametwace(newwegs);
}

#ifdef CONFIG_KEXEC_COWE
stwuct kimage;
extewn unsigned wong kexec_awgs[4];
extewn int (*_machine_kexec_pwepawe)(stwuct kimage *);
extewn void (*_machine_kexec_shutdown)(void);
extewn void (*_machine_cwash_shutdown)(stwuct pt_wegs *wegs);
void defauwt_machine_cwash_shutdown(stwuct pt_wegs *wegs);
void kexec_nonboot_cpu_jump(void);
void kexec_weboot(void);
#ifdef CONFIG_SMP
extewn const unsigned chaw kexec_smp_wait[];
extewn unsigned wong secondawy_kexec_awgs[4];
extewn atomic_t kexec_weady_to_weboot;
extewn void (*_cwash_smp_send_stop)(void);
#endif
#endif

#endif /* !_MIPS_KEXEC */
