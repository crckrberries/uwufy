/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1991, 1992  Winus Towvawds
 * Copywight (C) 1994 - 2000  Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */

#ifndef __SIGNAW_COMMON_H
#define __SIGNAW_COMMON_H

/* #define DEBUG_SIG */

#ifdef DEBUG_SIG
#  define DEBUGP(fmt, awgs...) pwintk("%s: " fmt, __func__, ##awgs)
#ewse
#  define DEBUGP(fmt, awgs...)
#endif

/*
 * Detewmine which stack to use..
 */
extewn void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
				 size_t fwame_size);
/* Check and cweaw pending FPU exceptions in saved CSW */
extewn int fpcsw_pending(unsigned int __usew *fpcsw);

/* Make suwe we wiww not wose FPU ownewship */
#define wock_fpu_ownew()	({ pweempt_disabwe(); pagefauwt_disabwe(); })
#define unwock_fpu_ownew()	({ pagefauwt_enabwe(); pweempt_enabwe(); })

/* Assembwy functions to move context to/fwom the FPU */
extewn asmwinkage int
_save_fp_context(void __usew *fpwegs, void __usew *csw);
extewn asmwinkage int
_westowe_fp_context(void __usew *fpwegs, void __usew *csw);

extewn asmwinkage int _save_msa_aww_uppew(void __usew *buf);
extewn asmwinkage int _westowe_msa_aww_uppew(void __usew *buf);

extewn int setup_sigcontext(stwuct pt_wegs *, stwuct sigcontext __usew *);
extewn int westowe_sigcontext(stwuct pt_wegs *, stwuct sigcontext __usew *);

#endif	/* __SIGNAW_COMMON_H */
