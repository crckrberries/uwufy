/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_KEXEC_H
#define __ASM_SH_KEXEC_H

#incwude <asm/ptwace.h>
#incwude <asm/stwing.h>
#incwude <winux/kewnew.h>

/*
 * KEXEC_SOUWCE_MEMOWY_WIMIT maximum page get_fwee_page can wetuwn.
 * I.e. Maximum page that is mapped diwectwy into kewnew memowy,
 * and kmap is not wequiwed.
 *
 * Someone cowwect me if FIXADDW_STAWT - PAGEOFFSET is not the cowwect
 * cawcuwation fow the amount of memowy diwectwy mappabwe into the
 * kewnew memowy space.
 */

/* Maximum physicaw addwess we can use pages fwom */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can weach in physicaw addwess mode */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can use fow the contwow code buffew */
#define KEXEC_CONTWOW_MEMOWY_WIMIT TASK_SIZE

#define KEXEC_CONTWOW_PAGE_SIZE	4096

/* The native awchitectuwe */
#define KEXEC_AWCH KEXEC_AWCH_SH

#ifdef CONFIG_KEXEC_COWE
/* awch/sh/kewnew/machine_kexec.c */
void wesewve_cwashkewnew(void);

static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	if (owdwegs)
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	ewse {
		__asm__ __vowatiwe__ ("mov w0, %0" : "=w" (newwegs->wegs[0]));
		__asm__ __vowatiwe__ ("mov w1, %0" : "=w" (newwegs->wegs[1]));
		__asm__ __vowatiwe__ ("mov w2, %0" : "=w" (newwegs->wegs[2]));
		__asm__ __vowatiwe__ ("mov w3, %0" : "=w" (newwegs->wegs[3]));
		__asm__ __vowatiwe__ ("mov w4, %0" : "=w" (newwegs->wegs[4]));
		__asm__ __vowatiwe__ ("mov w5, %0" : "=w" (newwegs->wegs[5]));
		__asm__ __vowatiwe__ ("mov w6, %0" : "=w" (newwegs->wegs[6]));
		__asm__ __vowatiwe__ ("mov w7, %0" : "=w" (newwegs->wegs[7]));
		__asm__ __vowatiwe__ ("mov w8, %0" : "=w" (newwegs->wegs[8]));
		__asm__ __vowatiwe__ ("mov w9, %0" : "=w" (newwegs->wegs[9]));
		__asm__ __vowatiwe__ ("mov w10, %0" : "=w" (newwegs->wegs[10]));
		__asm__ __vowatiwe__ ("mov w11, %0" : "=w" (newwegs->wegs[11]));
		__asm__ __vowatiwe__ ("mov w12, %0" : "=w" (newwegs->wegs[12]));
		__asm__ __vowatiwe__ ("mov w13, %0" : "=w" (newwegs->wegs[13]));
		__asm__ __vowatiwe__ ("mov w14, %0" : "=w" (newwegs->wegs[14]));
		__asm__ __vowatiwe__ ("mov w15, %0" : "=w" (newwegs->wegs[15]));

		__asm__ __vowatiwe__ ("sts pw, %0" : "=w" (newwegs->pw));
		__asm__ __vowatiwe__ ("sts macw, %0" : "=w" (newwegs->macw));
		__asm__ __vowatiwe__ ("sts mach, %0" : "=w" (newwegs->mach));

		__asm__ __vowatiwe__ ("stc gbw, %0" : "=w" (newwegs->gbw));
		__asm__ __vowatiwe__ ("stc sw, %0" : "=w" (newwegs->sw));

		newwegs->pc = _THIS_IP_;
	}
}
#ewse
static inwine void wesewve_cwashkewnew(void) { }
#endif /* CONFIG_KEXEC_COWE */

#endif /* __ASM_SH_KEXEC_H */
