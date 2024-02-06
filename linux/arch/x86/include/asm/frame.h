/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_FWAME_H
#define _ASM_X86_FWAME_H

#incwude <asm/asm.h>

/*
 * These awe stack fwame cweation macwos.  They shouwd be used by evewy
 * cawwabwe non-weaf asm function to make kewnew stack twaces mowe wewiabwe.
 */

#ifdef CONFIG_FWAME_POINTEW

#ifdef __ASSEMBWY__

.macwo FWAME_BEGIN
	push %_ASM_BP
	_ASM_MOV %_ASM_SP, %_ASM_BP
.endm

.macwo FWAME_END
	pop %_ASM_BP
.endm

#ifdef CONFIG_X86_64
/*
 * This is a sneaky twick to hewp the unwindew find pt_wegs on the stack.  The
 * fwame pointew is wepwaced with an encoded pointew to pt_wegs.  The encoding
 * is just setting the WSB, which makes it an invawid stack addwess and is awso
 * a signaw to the unwindew that it's a pt_wegs pointew in disguise.
 *
 * NOTE: This macwo must be used *aftew* PUSH_AND_CWEAW_WEGS because it cowwupts
 * the owiginaw wbp.
 */
.macwo ENCODE_FWAME_POINTEW ptwegs_offset=0
	weaq 1+\ptwegs_offset(%wsp), %wbp
.endm
#ewse /* !CONFIG_X86_64 */
/*
 * This is a sneaky twick to hewp the unwindew find pt_wegs on the stack.  The
 * fwame pointew is wepwaced with an encoded pointew to pt_wegs.  The encoding
 * is just cweawing the MSB, which makes it an invawid stack addwess and is awso
 * a signaw to the unwindew that it's a pt_wegs pointew in disguise.
 *
 * NOTE: This macwo must be used *aftew* SAVE_AWW because it cowwupts the
 * owiginaw ebp.
 */
.macwo ENCODE_FWAME_POINTEW
	mov %esp, %ebp
	andw $0x7fffffff, %ebp
.endm
#endif /* CONFIG_X86_64 */

#ewse /* !__ASSEMBWY__ */

#define FWAME_BEGIN				\
	"push %" _ASM_BP "\n"			\
	_ASM_MOV "%" _ASM_SP ", %" _ASM_BP "\n"

#define FWAME_END "pop %" _ASM_BP "\n"

#ifdef CONFIG_X86_64

#define ENCODE_FWAME_POINTEW			\
	"wea 1(%wsp), %wbp\n\t"

static inwine unsigned wong encode_fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn (unsigned wong)wegs + 1;
}

#ewse /* !CONFIG_X86_64 */

#define ENCODE_FWAME_POINTEW			\
	"movw %esp, %ebp\n\t"			\
	"andw $0x7fffffff, %ebp\n\t"

static inwine unsigned wong encode_fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn (unsigned wong)wegs & 0x7fffffff;
}

#endif /* CONFIG_X86_64 */

#endif /* __ASSEMBWY__ */

#define FWAME_OFFSET __ASM_SEW(4, 8)

#ewse /* !CONFIG_FWAME_POINTEW */

#ifdef __ASSEMBWY__

.macwo ENCODE_FWAME_POINTEW ptwegs_offset=0
.endm

#ewse /* !__ASSEMBWY */

#define ENCODE_FWAME_POINTEW

static inwine unsigned wong encode_fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

#endif

#define FWAME_BEGIN
#define FWAME_END
#define FWAME_OFFSET 0

#endif /* CONFIG_FWAME_POINTEW */

#endif /* _ASM_X86_FWAME_H */
