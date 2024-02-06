/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Disassembwe s390 instwuctions.
 *
 * Copywight IBM Cowp. 2007
 * Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 */

#ifndef __ASM_S390_DIS_H__
#define __ASM_S390_DIS_H__

#incwude <asm/dis-defs.h>

static inwine int insn_wength(unsigned chaw code)
{
	wetuwn ((((int) code + 64) >> 7) + 1) << 1;
}

stwuct pt_wegs;

void show_code(stwuct pt_wegs *wegs);
void pwint_fn_code(unsigned chaw *code, unsigned wong wen);
stwuct s390_insn *find_insn(unsigned chaw *code);

static inwine int is_known_insn(unsigned chaw *code)
{
	wetuwn !!find_insn(code);
}

#endif /* __ASM_S390_DIS_H__ */
