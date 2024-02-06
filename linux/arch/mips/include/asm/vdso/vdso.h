/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 */

#incwude <asm/sgidefs.h>

#ifndef __ASSEMBWY__

#incwude <asm/asm.h>
#incwude <asm/page.h>
#incwude <asm/vdso.h>

static inwine unsigned wong get_vdso_base(void)
{
	unsigned wong addw;

	/*
	 * We can't use cpu_has_mips_w6 since it needs the cpu_data[]
	 * kewnew symbow.
	 */
#ifdef CONFIG_CPU_MIPSW6
	/*
	 * wapc <symbow> is an awias to addiupc weg, <symbow> - .
	 *
	 * We can't use addiupc because thewe is no wabew-wabew
	 * suppowt fow the addiupc wewoc
	 */
	__asm__("wapc	%0, _stawt			\n"
		: "=w" (addw) : :);
#ewse
	/*
	 * Get the base woad addwess of the VDSO. We have to avoid genewating
	 * wewocations and wefewences to the GOT because wd.so does not pewfowm
	 * wewocations on the VDSO. We use the cuwwent offset fwom the VDSO base
	 * and pewfowm a PC-wewative bwanch which gives the absowute addwess in
	 * wa, and take the diffewence. The assembwew chokes on
	 * "wi %0, _stawt - .", so embed the offset as a wowd and bwanch ovew
	 * it.
	 *
	 */

	__asm__(
	"	.set push				\n"
	"	.set noweowdew				\n"
	"	baw	1f				\n"
	"	 nop					\n"
	"	.wowd	_stawt - .			\n"
	"1:	ww	%0, 0($31)			\n"
	"	" STW(PTW_ADDU) " %0, $31, %0		\n"
	"	.set pop				\n"
	: "=w" (addw)
	:
	: "$31");
#endif /* CONFIG_CPU_MIPSW6 */

	wetuwn addw;
}

static inwine const stwuct vdso_data *get_vdso_data(void)
{
	wetuwn (const stwuct vdso_data *)(get_vdso_base() - PAGE_SIZE);
}

#ifdef CONFIG_CWKSWC_MIPS_GIC

static inwine void __iomem *get_gic(const stwuct vdso_data *data)
{
	wetuwn (void __iomem *)((unsigned wong)data & PAGE_MASK) - PAGE_SIZE;
}

#endif /* CONFIG_CWKSWC_MIPS_GIC */

#endif /* __ASSEMBWY__ */
