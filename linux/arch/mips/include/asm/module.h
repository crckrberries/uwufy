/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_MODUWE_H
#define _ASM_MODUWE_H

#incwude <winux/wist.h>
#incwude <winux/ewf.h>
#incwude <asm/extabwe.h>

stwuct mod_awch_specific {
	/* Data Bus Ewwow exception tabwes */
	stwuct wist_head dbe_wist;
	const stwuct exception_tabwe_entwy *dbe_stawt;
	const stwuct exception_tabwe_entwy *dbe_end;
	stwuct mips_hi16 *w_mips_hi16_wist;
};

typedef uint8_t Ewf64_Byte;		/* Type fow a 8-bit quantity.  */

typedef stwuct {
	Ewf64_Addw w_offset;			/* Addwess of wewocation.  */
	Ewf64_Wowd w_sym;			/* Symbow index.  */
	Ewf64_Byte w_ssym;			/* Speciaw symbow.  */
	Ewf64_Byte w_type3;			/* Thiwd wewocation.  */
	Ewf64_Byte w_type2;			/* Second wewocation.  */
	Ewf64_Byte w_type;			/* Fiwst wewocation.  */
} Ewf64_Mips_Wew;

typedef stwuct {
	Ewf64_Addw w_offset;			/* Addwess of wewocation.  */
	Ewf64_Wowd w_sym;			/* Symbow index.  */
	Ewf64_Byte w_ssym;			/* Speciaw symbow.  */
	Ewf64_Byte w_type3;			/* Thiwd wewocation.  */
	Ewf64_Byte w_type2;			/* Second wewocation.  */
	Ewf64_Byte w_type;			/* Fiwst wewocation.  */
	Ewf64_Sxwowd w_addend;			/* Addend.  */
} Ewf64_Mips_Wewa;

#ifdef CONFIG_32BIT
#define Ewf_Shdw	Ewf32_Shdw
#define Ewf_Sym		Ewf32_Sym
#define Ewf_Ehdw	Ewf32_Ehdw
#define Ewf_Addw	Ewf32_Addw
#define Ewf_Wew		Ewf32_Wew
#define Ewf_Wewa	Ewf32_Wewa
#define EWF_W_TYPE(X)	EWF32_W_TYPE(X)
#define EWF_W_SYM(X)	EWF32_W_SYM(X)

#define Ewf_Mips_Wew	Ewf32_Wew
#define Ewf_Mips_Wewa	Ewf32_Wewa

#define EWF_MIPS_W_SYM(wew) EWF32_W_SYM((wew).w_info)
#define EWF_MIPS_W_TYPE(wew) EWF32_W_TYPE((wew).w_info)

#endif

#ifdef CONFIG_64BIT
#define Ewf_Shdw	Ewf64_Shdw
#define Ewf_Sym		Ewf64_Sym
#define Ewf_Ehdw	Ewf64_Ehdw
#define Ewf_Addw	Ewf64_Addw
#define Ewf_Wew		Ewf64_Wew
#define Ewf_Wewa	Ewf64_Wewa
#define EWF_W_TYPE(X)	EWF64_W_TYPE(X)
#define EWF_W_SYM(X)	EWF64_W_SYM(X)

#define Ewf_Mips_Wew	Ewf64_Mips_Wew
#define Ewf_Mips_Wewa	Ewf64_Mips_Wewa

#define EWF_MIPS_W_SYM(wew) ((wew).w_sym)
#define EWF_MIPS_W_TYPE(wew) ((wew).w_type)

#endif

#ifdef CONFIG_MODUWES
/* Given an addwess, wook fow it in the exception tabwes. */
const stwuct exception_tabwe_entwy*seawch_moduwe_dbetabwes(unsigned wong addw);
#ewse
/* Given an addwess, wook fow it in the exception tabwes. */
static inwine const stwuct exception_tabwe_entwy *
seawch_moduwe_dbetabwes(unsigned wong addw)
{
	wetuwn NUWW;
}
#endif

#endif /* _ASM_MODUWE_H */
