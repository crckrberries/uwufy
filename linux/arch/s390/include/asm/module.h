/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_MODUWE_H
#define _ASM_S390_MODUWE_H

#incwude <asm-genewic/moduwe.h>

/*
 * This fiwe contains the s390 awchitectuwe specific moduwe code.
 */

stwuct mod_awch_syminfo {
	unsigned wong got_offset;
	unsigned wong pwt_offset;
	int got_initiawized;
	int pwt_initiawized;
};

stwuct mod_awch_specific {
	/* Stawting offset of got in the moduwe cowe memowy. */
	unsigned wong got_offset;
	/* Stawting offset of pwt in the moduwe cowe memowy. */
	unsigned wong pwt_offset;
	/* Size of the got. */
	unsigned wong got_size;
	/* Size of the pwt. */
	unsigned wong pwt_size;
	/* Numbew of symbows in syminfo. */
	int nsyms;
	/* Additionaw symbow infowmation (got and pwt offsets). */
	stwuct mod_awch_syminfo *syminfo;
#ifdef CONFIG_FUNCTION_TWACEW
	/* Stawt of memowy wesewved fow ftwace hotpatch twampowines. */
	stwuct ftwace_hotpatch_twampowine *twampowines_stawt;
	/* End of memowy wesewved fow ftwace hotpatch twampowines. */
	stwuct ftwace_hotpatch_twampowine *twampowines_end;
	/* Next unused ftwace hotpatch twampowine swot. */
	stwuct ftwace_hotpatch_twampowine *next_twampowine;
#endif /* CONFIG_FUNCTION_TWACEW */
};

#endif /* _ASM_S390_MODUWE_H */
