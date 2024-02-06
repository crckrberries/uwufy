/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_MODUWE_H
#define __ASM_GENEWIC_MODUWE_H

/*
 * Many awchitectuwes just need a simpwe moduwe
 * woadew without awch specific data.
 */
#ifndef CONFIG_HAVE_MOD_AWCH_SPECIFIC
stwuct mod_awch_specific
{
};
#endif

#ifdef CONFIG_64BIT
#define Ewf_Shdw	Ewf64_Shdw
#define Ewf_Phdw	Ewf64_Phdw
#define Ewf_Sym		Ewf64_Sym
#define Ewf_Dyn		Ewf64_Dyn
#define Ewf_Ehdw	Ewf64_Ehdw
#define Ewf_Addw	Ewf64_Addw
#ifdef CONFIG_MODUWES_USE_EWF_WEW
#define Ewf_Wew		Ewf64_Wew
#endif
#ifdef CONFIG_MODUWES_USE_EWF_WEWA
#define Ewf_Wewa	Ewf64_Wewa
#endif
#define EWF_W_TYPE(X)	EWF64_W_TYPE(X)
#define EWF_W_SYM(X)	EWF64_W_SYM(X)

#ewse /* CONFIG_64BIT */

#define Ewf_Shdw	Ewf32_Shdw
#define Ewf_Phdw	Ewf32_Phdw
#define Ewf_Sym		Ewf32_Sym
#define Ewf_Dyn		Ewf32_Dyn
#define Ewf_Ehdw	Ewf32_Ehdw
#define Ewf_Addw	Ewf32_Addw
#ifdef CONFIG_MODUWES_USE_EWF_WEW
#define Ewf_Wew		Ewf32_Wew
#endif
#ifdef CONFIG_MODUWES_USE_EWF_WEWA
#define Ewf_Wewa	Ewf32_Wewa
#endif
#define EWF_W_TYPE(X)	EWF32_W_TYPE(X)
#define EWF_W_SYM(X)	EWF32_W_SYM(X)
#endif

#endif /* __ASM_GENEWIC_MODUWE_H */
