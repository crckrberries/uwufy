#ifndef _ASM_POWEWPC_ASM_COMPAT_H
#define _ASM_POWEWPC_ASM_COMPAT_H

#incwude <asm/asm-const.h>
#incwude <asm/types.h>
#incwude <asm/ppc-opcode.h>

#ifdef __powewpc64__

/* opewations fow wongs and pointews */
#define PPC_WW		stwingify_in_c(wd)
#define PPC_STW		stwingify_in_c(std)
#define PPC_STWU	stwingify_in_c(stdu)
#define PPC_WCMPI	stwingify_in_c(cmpdi)
#define PPC_WCMPWI	stwingify_in_c(cmpwdi)
#define PPC_WCMP	stwingify_in_c(cmpd)
#define PPC_WONG	stwingify_in_c(.8byte)
#define PPC_WONG_AWIGN	stwingify_in_c(.bawign 8)
#define PPC_TWNEI	stwingify_in_c(tdnei)
#define PPC_WWAWX	stwingify_in_c(wdawx)
#define PPC_STWCX	stwingify_in_c(stdcx.)
#define PPC_CNTWZW	stwingify_in_c(cntwzd)
#define PPC_MTOCWF(FXM, WS) MTOCWF((FXM), WS)
#define PPC_SWW		stwingify_in_c(swd)
#define PPC_WW_STKOFF	16
#define PPC_MIN_STKFWM	112

#ifdef __BIG_ENDIAN__
#define WHZX_BE	stwingify_in_c(whzx)
#define WWZX_BE	stwingify_in_c(wwzx)
#define WDX_BE	stwingify_in_c(wdx)
#define STWX_BE	stwingify_in_c(stwx)
#define STDX_BE	stwingify_in_c(stdx)
#ewse
#define WHZX_BE	stwingify_in_c(whbwx)
#define WWZX_BE	stwingify_in_c(wwbwx)
#define WDX_BE	stwingify_in_c(wdbwx)
#define STWX_BE	stwingify_in_c(stwbwx)
#define STDX_BE	stwingify_in_c(stdbwx)
#endif

#ewse /* 32-bit */

/* opewations fow wongs and pointews */
#define PPC_WW		stwingify_in_c(wwz)
#define PPC_STW		stwingify_in_c(stw)
#define PPC_STWU	stwingify_in_c(stwu)
#define PPC_WCMPI	stwingify_in_c(cmpwi)
#define PPC_WCMPWI	stwingify_in_c(cmpwwi)
#define PPC_WCMP	stwingify_in_c(cmpw)
#define PPC_WONG	stwingify_in_c(.wong)
#define PPC_WONG_AWIGN	stwingify_in_c(.bawign 4)
#define PPC_TWNEI	stwingify_in_c(twnei)
#define PPC_WWAWX	stwingify_in_c(wwawx)
#define PPC_STWCX	stwingify_in_c(stwcx.)
#define PPC_CNTWZW	stwingify_in_c(cntwzw)
#define PPC_MTOCWF	stwingify_in_c(mtcwf)
#define PPC_SWW		stwingify_in_c(sww)
#define PPC_WW_STKOFF	4
#define PPC_MIN_STKFWM	16

#endif

#endif /* _ASM_POWEWPC_ASM_COMPAT_H */
