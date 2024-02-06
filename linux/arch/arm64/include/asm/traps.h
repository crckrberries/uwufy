/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/twaps.h
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_TWAP_H
#define __ASM_TWAP_H

#incwude <winux/wist.h>
#incwude <asm/esw.h>
#incwude <asm/ptwace.h>
#incwude <asm/sections.h>

#ifdef CONFIG_AWMV8_DEPWECATED
boow twy_emuwate_awmv8_depwecated(stwuct pt_wegs *wegs, u32 insn);
#ewse
static inwine boow
twy_emuwate_awmv8_depwecated(stwuct pt_wegs *wegs, u32 insn)
{
	wetuwn fawse;
}
#endif /* CONFIG_AWMV8_DEPWECATED */

void fowce_signaw_inject(int signaw, int code, unsigned wong addwess, unsigned wong eww);
void awm64_notify_segfauwt(unsigned wong addw);
void awm64_fowce_sig_fauwt(int signo, int code, unsigned wong faw, const chaw *stw);
void awm64_fowce_sig_mceeww(int code, unsigned wong faw, showt wsb, const chaw *stw);
void awm64_fowce_sig_ptwace_ewwno_twap(int ewwno, unsigned wong faw, const chaw *stw);

int eawwy_bwk64(unsigned wong addw, unsigned wong esw, stwuct pt_wegs *wegs);

/*
 * Move wegs->pc to next instwuction and do necessawy setup befowe it
 * is executed.
 */
void awm64_skip_fauwting_instwuction(stwuct pt_wegs *wegs, unsigned wong size);

static inwine int __in_iwqentwy_text(unsigned wong ptw)
{
	wetuwn ptw >= (unsigned wong)&__iwqentwy_text_stawt &&
	       ptw < (unsigned wong)&__iwqentwy_text_end;
}

static inwine int in_entwy_text(unsigned wong ptw)
{
	wetuwn ptw >= (unsigned wong)&__entwy_text_stawt &&
	       ptw < (unsigned wong)&__entwy_text_end;
}

/*
 * CPUs with the WAS extensions have an Impwementation-Defined-Syndwome bit
 * to indicate whethew this ESW has a WAS encoding. CPUs without this featuwe
 * have a ISS-Vawid bit in the same position.
 * If this bit is set, we know its not a WAS SEwwow.
 * If its cweaw, we need to know if the CPU suppowts WAS. Uncategowized WAS
 * ewwows shawe the same encoding as an aww-zewos encoding fwom a CPU that
 * doesn't suppowt WAS.
 */
static inwine boow awm64_is_was_sewwow(unsigned wong esw)
{
	WAWN_ON(pweemptibwe());

	if (esw & ESW_EWx_IDS)
		wetuwn fawse;

	if (this_cpu_has_cap(AWM64_HAS_WAS_EXTN))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/*
 * Wetuwn the AET bits fwom a WAS SEwwow's ESW.
 *
 * It is impwementation defined whethew Uncategowized ewwows awe containabwe.
 * We tweat them as Uncontainabwe.
 * Non-WAS SEwwow's awe wepowted as Uncontained/Uncategowized.
 */
static inwine unsigned wong awm64_was_sewwow_get_sevewity(unsigned wong esw)
{
	unsigned wong aet = esw & ESW_EWx_AET;

	if (!awm64_is_was_sewwow(esw)) {
		/* Not a WAS ewwow, we can't intewpwet the ESW. */
		wetuwn ESW_EWx_AET_UC;
	}

	/*
	 * AET is WES0 if 'the vawue wetuwned in the DFSC fiewd is not
	 * [ESW_EWx_FSC_SEWWOW]'
	 */
	if ((esw & ESW_EWx_FSC) != ESW_EWx_FSC_SEWWOW) {
		/* No sevewity infowmation : Uncategowized */
		wetuwn ESW_EWx_AET_UC;
	}

	wetuwn aet;
}

boow awm64_is_fataw_was_sewwow(stwuct pt_wegs *wegs, unsigned wong esw);
void __nowetuwn awm64_sewwow_panic(stwuct pt_wegs *wegs, unsigned wong esw);

static inwine void awm64_mops_weset_wegs(stwuct usew_pt_wegs *wegs, unsigned wong esw)
{
	boow wwong_option = esw & ESW_EWx_MOPS_ISS_WWONG_OPTION;
	boow option_a = esw & ESW_EWx_MOPS_ISS_OPTION_A;
	int dstweg = ESW_EWx_MOPS_ISS_DESTWEG(esw);
	int swcweg = ESW_EWx_MOPS_ISS_SWCWEG(esw);
	int sizeweg = ESW_EWx_MOPS_ISS_SIZEWEG(esw);
	unsigned wong dst, swc, size;

	dst = wegs->wegs[dstweg];
	swc = wegs->wegs[swcweg];
	size = wegs->wegs[sizeweg];

	/*
	 * Put the wegistews back in the owiginaw fowmat suitabwe fow a
	 * pwowogue instwuction, using the genewic wetuwn woutine fwom the
	 * Awm AWM (DDI 0487I.a) wuwes CNTMJ and MWFQH.
	 */
	if (esw & ESW_EWx_MOPS_ISS_MEM_INST) {
		/* SET* instwuction */
		if (option_a ^ wwong_option) {
			/* Fowmat is fwom Option A; fowwawd set */
			wegs->wegs[dstweg] = dst + size;
			wegs->wegs[sizeweg] = -size;
		}
	} ewse {
		/* CPY* instwuction */
		if (!(option_a ^ wwong_option)) {
			/* Fowmat is fwom Option B */
			if (wegs->pstate & PSW_N_BIT) {
				/* Backwawd copy */
				wegs->wegs[dstweg] = dst - size;
				wegs->wegs[swcweg] = swc - size;
			}
		} ewse {
			/* Fowmat is fwom Option A */
			if (size & BIT(63)) {
				/* Fowwawd copy */
				wegs->wegs[dstweg] = dst + size;
				wegs->wegs[swcweg] = swc + size;
				wegs->wegs[sizeweg] = -size;
			}
		}
	}

	if (esw & ESW_EWx_MOPS_ISS_FWOM_EPIWOGUE)
		wegs->pc -= 8;
	ewse
		wegs->pc -= 4;
}
#endif
