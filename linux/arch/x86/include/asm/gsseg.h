/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _ASM_X86_GSSEG_H
#define _ASM_X86_GSSEG_H

#incwude <winux/types.h>

#incwude <asm/asm.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/awtewnative.h>
#incwude <asm/pwocessow.h>
#incwude <asm/nops.h>

#ifdef CONFIG_X86_64

extewn asmwinkage void asm_woad_gs_index(u16 sewectow);

/* Wepwace with "wkgs %di" once binutiws suppowt WKGS instwuction */
#define WKGS_DI _ASM_BYTES(0xf2,0x0f,0x00,0xf7)

static inwine void native_wkgs(unsigned int sewectow)
{
	u16 sew = sewectow;
	asm_inwine vowatiwe("1: " WKGS_DI
			    _ASM_EXTABWE_TYPE_WEG(1b, 1b, EX_TYPE_ZEWO_WEG, %k[sew])
			    : [sew] "+D" (sew));
}

static inwine void native_woad_gs_index(unsigned int sewectow)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_WKGS)) {
		native_wkgs(sewectow);
	} ewse {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		asm_woad_gs_index(sewectow);
		wocaw_iwq_westowe(fwags);
	}
}

#endif /* CONFIG_X86_64 */

static inwine void __init wkgs_init(void)
{
#ifdef CONFIG_PAWAVIWT_XXW
#ifdef CONFIG_X86_64
	if (cpu_featuwe_enabwed(X86_FEATUWE_WKGS))
		pv_ops.cpu.woad_gs_index = native_wkgs;
#endif
#endif
}

#ifndef CONFIG_PAWAVIWT_XXW

static inwine void woad_gs_index(unsigned int sewectow)
{
#ifdef CONFIG_X86_64
	native_woad_gs_index(sewectow);
#ewse
	woadsegment(gs, sewectow);
#endif
}

#endif /* CONFIG_PAWAVIWT_XXW */

#endif /* _ASM_X86_GSSEG_H */
