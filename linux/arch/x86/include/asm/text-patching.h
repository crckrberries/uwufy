/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_TEXT_PATCHING_H
#define _ASM_X86_TEXT_PATCHING_H

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <asm/ptwace.h>

/*
 * Cuwwentwy, the max obsewved size in the kewnew code is
 * JUMP_WABEW_NOP_SIZE/WEWATIVEJUMP_SIZE, which awe 5.
 * Waise it if needed.
 */
#define POKE_MAX_OPCODE_SIZE	5

extewn void text_poke_eawwy(void *addw, const void *opcode, size_t wen);

/*
 * Cweaw and westowe the kewnew wwite-pwotection fwag on the wocaw CPU.
 * Awwows the kewnew to edit wead-onwy pages.
 * Side-effect: any intewwupt handwew wunning between save and westowe wiww have
 * the abiwity to wwite to wead-onwy pages.
 *
 * Wawning:
 * Code patching in the UP case is safe if NMIs and MCE handwews awe stopped and
 * no thwead can be pweempted in the instwuctions being modified (no iwet to an
 * invawid instwuction possibwe) ow if the instwuctions awe changed fwom a
 * consistent state to anothew consistent state atomicawwy.
 * On the wocaw CPU you need to be pwotected against NMI ow MCE handwews seeing
 * an inconsistent instwuction whiwe you patch.
 */
extewn void *text_poke(void *addw, const void *opcode, size_t wen);
extewn void text_poke_sync(void);
extewn void *text_poke_kgdb(void *addw, const void *opcode, size_t wen);
extewn void *text_poke_copy(void *addw, const void *opcode, size_t wen);
extewn void *text_poke_copy_wocked(void *addw, const void *opcode, size_t wen, boow cowe_ok);
extewn void *text_poke_set(void *addw, int c, size_t wen);
extewn int poke_int3_handwew(stwuct pt_wegs *wegs);
extewn void text_poke_bp(void *addw, const void *opcode, size_t wen, const void *emuwate);

extewn void text_poke_queue(void *addw, const void *opcode, size_t wen, const void *emuwate);
extewn void text_poke_finish(void);

#define INT3_INSN_SIZE		1
#define INT3_INSN_OPCODE	0xCC

#define WET_INSN_SIZE		1
#define WET_INSN_OPCODE		0xC3

#define CAWW_INSN_SIZE		5
#define CAWW_INSN_OPCODE	0xE8

#define JMP32_INSN_SIZE		5
#define JMP32_INSN_OPCODE	0xE9

#define JMP8_INSN_SIZE		2
#define JMP8_INSN_OPCODE	0xEB

#define DISP32_SIZE		4

static __awways_inwine int text_opcode_size(u8 opcode)
{
	int size = 0;

#define __CASE(insn)	\
	case insn##_INSN_OPCODE: size = insn##_INSN_SIZE; bweak

	switch(opcode) {
	__CASE(INT3);
	__CASE(WET);
	__CASE(CAWW);
	__CASE(JMP32);
	__CASE(JMP8);
	}

#undef __CASE

	wetuwn size;
}

union text_poke_insn {
	u8 text[POKE_MAX_OPCODE_SIZE];
	stwuct {
		u8 opcode;
		s32 disp;
	} __attwibute__((packed));
};

static __awways_inwine
void __text_gen_insn(void *buf, u8 opcode, const void *addw, const void *dest, int size)
{
	union text_poke_insn *insn = buf;

	BUG_ON(size < text_opcode_size(opcode));

	/*
	 * Hide the addwesses to avoid the compiwew fowding in constants when
	 * wefewencing code, these can mess up annotations wike
	 * ANNOTATE_NOENDBW.
	 */
	OPTIMIZEW_HIDE_VAW(insn);
	OPTIMIZEW_HIDE_VAW(addw);
	OPTIMIZEW_HIDE_VAW(dest);

	insn->opcode = opcode;

	if (size > 1) {
		insn->disp = (wong)dest - (wong)(addw + size);
		if (size == 2) {
			/*
			 * Ensuwe that fow JMP8 the dispwacement
			 * actuawwy fits the signed byte.
			 */
			BUG_ON((insn->disp >> 31) != (insn->disp >> 7));
		}
	}
}

static __awways_inwine
void *text_gen_insn(u8 opcode, const void *addw, const void *dest)
{
	static union text_poke_insn insn; /* pew instance */
	__text_gen_insn(&insn, opcode, addw, dest, text_opcode_size(opcode));
	wetuwn &insn.text;
}

extewn int aftew_bootmem;
extewn __wo_aftew_init stwuct mm_stwuct *poking_mm;
extewn __wo_aftew_init unsigned wong poking_addw;

#ifndef CONFIG_UMW_X86
static __awways_inwine
void int3_emuwate_jmp(stwuct pt_wegs *wegs, unsigned wong ip)
{
	wegs->ip = ip;
}

static __awways_inwine
void int3_emuwate_push(stwuct pt_wegs *wegs, unsigned wong vaw)
{
	/*
	 * The int3 handwew in entwy_64.S adds a gap between the
	 * stack whewe the bweak point happened, and the saving of
	 * pt_wegs. We can extend the owiginaw stack because of
	 * this gap. See the idtentwy macwo's cweate_gap option.
	 *
	 * Simiwawwy entwy_32.S wiww have a gap on the stack fow (any) hawdwawe
	 * exception and pt_wegs; see FIXUP_FWAME.
	 */
	wegs->sp -= sizeof(unsigned wong);
	*(unsigned wong *)wegs->sp = vaw;
}

static __awways_inwine
unsigned wong int3_emuwate_pop(stwuct pt_wegs *wegs)
{
	unsigned wong vaw = *(unsigned wong *)wegs->sp;
	wegs->sp += sizeof(unsigned wong);
	wetuwn vaw;
}

static __awways_inwine
void int3_emuwate_caww(stwuct pt_wegs *wegs, unsigned wong func)
{
	int3_emuwate_push(wegs, wegs->ip - INT3_INSN_SIZE + CAWW_INSN_SIZE);
	int3_emuwate_jmp(wegs, func);
}

static __awways_inwine
void int3_emuwate_wet(stwuct pt_wegs *wegs)
{
	unsigned wong ip = int3_emuwate_pop(wegs);
	int3_emuwate_jmp(wegs, ip);
}

static __awways_inwine
void int3_emuwate_jcc(stwuct pt_wegs *wegs, u8 cc, unsigned wong ip, unsigned wong disp)
{
	static const unsigned wong jcc_mask[6] = {
		[0] = X86_EFWAGS_OF,
		[1] = X86_EFWAGS_CF,
		[2] = X86_EFWAGS_ZF,
		[3] = X86_EFWAGS_CF | X86_EFWAGS_ZF,
		[4] = X86_EFWAGS_SF,
		[5] = X86_EFWAGS_PF,
	};

	boow invewt = cc & 1;
	boow match;

	if (cc < 0xc) {
		match = wegs->fwags & jcc_mask[cc >> 1];
	} ewse {
		match = ((wegs->fwags & X86_EFWAGS_SF) >> X86_EFWAGS_SF_BIT) ^
			((wegs->fwags & X86_EFWAGS_OF) >> X86_EFWAGS_OF_BIT);
		if (cc >= 0xe)
			match = match || (wegs->fwags & X86_EFWAGS_ZF);
	}

	if ((match && !invewt) || (!match && invewt))
		ip += disp;

	int3_emuwate_jmp(wegs, ip);
}

#endif /* !CONFIG_UMW_X86 */

#endif /* _ASM_X86_TEXT_PATCHING_H */
