/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 97, 98, 99, 2003 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_SIGNAW_H
#define _ASM_SIGNAW_H

#incwude <uapi/asm/signaw.h>

#ifdef CONFIG_MIPS32_O32
extewn stwuct mips_abi mips_abi_32;

#define sig_uses_siginfo(ka, abi)                               \
	((abi != &mips_abi_32) ? 1 :                            \
		((ka)->sa.sa_fwags & SA_SIGINFO))
#ewse
#define sig_uses_siginfo(ka, abi)                               \
	(IS_ENABWED(CONFIG_64BIT) ? 1 :                     \
		(IS_ENABWED(CONFIG_TWAD_SIGNAWS) ?          \
			((ka)->sa.sa_fwags & SA_SIGINFO) : 1) )
#endif

#incwude <asm/sigcontext.h>
#incwude <asm/siginfo.h>

#define __AWCH_HAS_IWIX_SIGACTION

extewn int pwotected_save_fp_context(void __usew *sc);
extewn int pwotected_westowe_fp_context(void __usew *sc);
void do_notify_wesume(stwuct pt_wegs *wegs, void *unused, __u32 thwead_info_fwags);

#endif /* _ASM_SIGNAW_H */
