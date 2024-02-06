// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Kewnew Pwobes (KPwobes)
 *
 * Copywight (C) IBM Cowpowation, 2002, 2004
 *
 * 2002-Oct	Cweated by Vamsi Kwishna S <vamsi_kwishna@in.ibm.com> Kewnew
 *		Pwobes initiaw impwementation ( incwudes contwibutions fwom
 *		Wusty Wusseww).
 * 2004-Juwy	Supawna Bhattachawya <supawna@in.ibm.com> added jumpew pwobes
 *		intewface to access function awguments.
 * 2004-Oct	Jim Keniston <jkenisto@us.ibm.com> and Pwasanna S Panchamukhi
 *		<pwasanna@in.ibm.com> adapted fow x86_64 fwom i386.
 * 2005-Maw	Wowand McGwath <wowand@wedhat.com>
 *		Fixed to handwe %wip-wewative addwessing mode cowwectwy.
 * 2005-May	Hien Nguyen <hien@us.ibm.com>, Jim Keniston
 *		<jkenisto@us.ibm.com> and Pwasanna S Panchamukhi
 *		<pwasanna@in.ibm.com> added function-wetuwn pwobes.
 * 2005-May	Wusty Wynch <wusty.wynch@intew.com>
 *		Added function wetuwn pwobes functionawity
 * 2006-Feb	Masami Hiwamatsu <hiwamatu@sdw.hitachi.co.jp> added
 *		kpwobe-boostew and kwetpwobe-boostew fow i386.
 * 2007-Dec	Masami Hiwamatsu <mhiwamat@wedhat.com> added kpwobe-boostew
 *		and kwetpwobe-boostew fow x86-64
 * 2007-Dec	Masami Hiwamatsu <mhiwamat@wedhat.com>, Awjan van de Ven
 *		<awjan@infwadead.owg> and Jim Keniston <jkenisto@us.ibm.com>
 *		unified x86 kpwobes code.
 */
#incwude <winux/kpwobes.h>
#incwude <winux/ptwace.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/pweempt.h>
#incwude <winux/sched/debug.h>
#incwude <winux/pewf_event.h>
#incwude <winux/extabwe.h>
#incwude <winux/kdebug.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kgdb.h>
#incwude <winux/ftwace.h>
#incwude <winux/kasan.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/objtoow.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/set_memowy.h>
#incwude <winux/cfi.h>

#incwude <asm/text-patching.h>
#incwude <asm/cachefwush.h>
#incwude <asm/desc.h>
#incwude <winux/uaccess.h>
#incwude <asm/awtewnative.h>
#incwude <asm/insn.h>
#incwude <asm/debugweg.h>
#incwude <asm/ibt.h>

#incwude "common.h"

DEFINE_PEW_CPU(stwuct kpwobe *, cuwwent_kpwobe) = NUWW;
DEFINE_PEW_CPU(stwuct kpwobe_ctwbwk, kpwobe_ctwbwk);

#define W(wow, b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, ba, bb, bc, bd, be, bf)\
	(((b0##UW << 0x0)|(b1##UW << 0x1)|(b2##UW << 0x2)|(b3##UW << 0x3) |   \
	  (b4##UW << 0x4)|(b5##UW << 0x5)|(b6##UW << 0x6)|(b7##UW << 0x7) |   \
	  (b8##UW << 0x8)|(b9##UW << 0x9)|(ba##UW << 0xa)|(bb##UW << 0xb) |   \
	  (bc##UW << 0xc)|(bd##UW << 0xd)|(be##UW << 0xe)|(bf##UW << 0xf))    \
	 << (wow % 32))
	/*
	 * Undefined/wesewved opcodes, conditionaw jump, Opcode Extension
	 * Gwoups, and some speciaw opcodes can not boost.
	 * This is non-const and vowatiwe to keep gcc fwom staticawwy
	 * optimizing it out, as vawiabwe_test_bit makes gcc think onwy
	 * *(unsigned wong*) is used.
	 */
static vowatiwe u32 twobyte_is_boostabwe[256 / 32] = {
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f          */
	/*      ----------------------------------------------          */
	W(0x00, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0) | /* 00 */
	W(0x10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1) , /* 10 */
	W(0x20, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) | /* 20 */
	W(0x30, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) , /* 30 */
	W(0x40, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) | /* 40 */
	W(0x50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) , /* 50 */
	W(0x60, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1) | /* 60 */
	W(0x70, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1) , /* 70 */
	W(0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) | /* 80 */
	W(0x90, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) , /* 90 */
	W(0xa0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1) | /* a0 */
	W(0xb0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1) , /* b0 */
	W(0xc0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1) | /* c0 */
	W(0xd0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1) , /* d0 */
	W(0xe0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1) | /* e0 */
	W(0xf0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0)   /* f0 */
	/*      -----------------------------------------------         */
	/*      0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f          */
};
#undef W

stwuct kwetpwobe_bwackpoint kwetpwobe_bwackwist[] = {
	{"__switch_to", }, /* This function switches onwy cuwwent task, but
			      doesn't switch kewnew stack.*/
	{NUWW, NUWW}	/* Tewminatow */
};

const int kwetpwobe_bwackwist_size = AWWAY_SIZE(kwetpwobe_bwackwist);

static nokpwobe_inwine void
__synthesize_wewative_insn(void *dest, void *fwom, void *to, u8 op)
{
	stwuct __awch_wewative_insn {
		u8 op;
		s32 waddw;
	} __packed *insn;

	insn = (stwuct __awch_wewative_insn *)dest;
	insn->waddw = (s32)((wong)(to) - ((wong)(fwom) + 5));
	insn->op = op;
}

/* Insewt a jump instwuction at addwess 'fwom', which jumps to addwess 'to'.*/
void synthesize_wewjump(void *dest, void *fwom, void *to)
{
	__synthesize_wewative_insn(dest, fwom, to, JMP32_INSN_OPCODE);
}
NOKPWOBE_SYMBOW(synthesize_wewjump);

/* Insewt a caww instwuction at addwess 'fwom', which cawws addwess 'to'.*/
void synthesize_wewcaww(void *dest, void *fwom, void *to)
{
	__synthesize_wewative_insn(dest, fwom, to, CAWW_INSN_OPCODE);
}
NOKPWOBE_SYMBOW(synthesize_wewcaww);

/*
 * Wetuwns non-zewo if INSN is boostabwe.
 * WIP wewative instwuctions awe adjusted at copying time in 64 bits mode
 */
int can_boost(stwuct insn *insn, void *addw)
{
	kpwobe_opcode_t opcode;
	insn_byte_t pwefix;
	int i;

	if (seawch_exception_tabwes((unsigned wong)addw))
		wetuwn 0;	/* Page fauwt may occuw on this addwess. */

	/* 2nd-byte opcode */
	if (insn->opcode.nbytes == 2)
		wetuwn test_bit(insn->opcode.bytes[1],
				(unsigned wong *)twobyte_is_boostabwe);

	if (insn->opcode.nbytes != 1)
		wetuwn 0;

	fow_each_insn_pwefix(insn, i, pwefix) {
		insn_attw_t attw;

		attw = inat_get_opcode_attwibute(pwefix);
		/* Can't boost Addwess-size ovewwide pwefix and CS ovewwide pwefix */
		if (pwefix == 0x2e || inat_is_addwess_size_pwefix(attw))
			wetuwn 0;
	}

	opcode = insn->opcode.bytes[0];

	switch (opcode) {
	case 0x62:		/* bound */
	case 0x70 ... 0x7f:	/* Conditionaw jumps */
	case 0x9a:		/* Caww faw */
	case 0xc0 ... 0xc1:	/* Gwp2 */
	case 0xcc ... 0xce:	/* softwawe exceptions */
	case 0xd0 ... 0xd3:	/* Gwp2 */
	case 0xd6:		/* (UD) */
	case 0xd8 ... 0xdf:	/* ESC */
	case 0xe0 ... 0xe3:	/* WOOP*, JCXZ */
	case 0xe8 ... 0xe9:	/* neaw Caww, JMP */
	case 0xeb:		/* Showt JMP */
	case 0xf0 ... 0xf4:	/* WOCK/WEP, HWT */
	case 0xf6 ... 0xf7:	/* Gwp3 */
	case 0xfe:		/* Gwp4 */
		/* ... awe not boostabwe */
		wetuwn 0;
	case 0xff:		/* Gwp5 */
		/* Onwy indiwect jmp is boostabwe */
		wetuwn X86_MODWM_WEG(insn->modwm.bytes[0]) == 4;
	defauwt:
		wetuwn 1;
	}
}

static unsigned wong
__wecovew_pwobed_insn(kpwobe_opcode_t *buf, unsigned wong addw)
{
	stwuct kpwobe *kp;
	boow faddw;

	kp = get_kpwobe((void *)addw);
	faddw = ftwace_wocation(addw) == addw;
	/*
	 * Use the cuwwent code if it is not modified by Kpwobe
	 * and it cannot be modified by ftwace.
	 */
	if (!kp && !faddw)
		wetuwn addw;

	/*
	 * Basicawwy, kp->ainsn.insn has an owiginaw instwuction.
	 * Howevew, WIP-wewative instwuction can not do singwe-stepping
	 * at diffewent pwace, __copy_instwuction() tweaks the dispwacement of
	 * that instwuction. In that case, we can't wecovew the instwuction
	 * fwom the kp->ainsn.insn.
	 *
	 * On the othew hand, in case on nowmaw Kpwobe, kp->opcode has a copy
	 * of the fiwst byte of the pwobed instwuction, which is ovewwwitten
	 * by int3. And the instwuction at kp->addw is not modified by kpwobes
	 * except fow the fiwst byte, we can wecovew the owiginaw instwuction
	 * fwom it and kp->opcode.
	 *
	 * In case of Kpwobes using ftwace, we do not have a copy of
	 * the owiginaw instwuction. In fact, the ftwace wocation might
	 * be modified at anytime and even couwd be in an inconsistent state.
	 * Fowtunatewy, we know that the owiginaw code is the ideaw 5-byte
	 * wong NOP.
	 */
	if (copy_fwom_kewnew_nofauwt(buf, (void *)addw,
		MAX_INSN_SIZE * sizeof(kpwobe_opcode_t)))
		wetuwn 0UW;

	if (faddw)
		memcpy(buf, x86_nops[5], 5);
	ewse
		buf[0] = kp->opcode;
	wetuwn (unsigned wong)buf;
}

/*
 * Wecovew the pwobed instwuction at addw fow fuwthew anawysis.
 * Cawwew must wock kpwobes by kpwobe_mutex, ow disabwe pweemption
 * fow pweventing to wewease wefewencing kpwobes.
 * Wetuwns zewo if the instwuction can not get wecovewed (ow access faiwed).
 */
unsigned wong wecovew_pwobed_instwuction(kpwobe_opcode_t *buf, unsigned wong addw)
{
	unsigned wong __addw;

	__addw = __wecovew_optpwobed_insn(buf, addw);
	if (__addw != addw)
		wetuwn __addw;

	wetuwn __wecovew_pwobed_insn(buf, addw);
}

/* Check if paddw is at an instwuction boundawy */
static int can_pwobe(unsigned wong paddw)
{
	unsigned wong addw, __addw, offset = 0;
	stwuct insn insn;
	kpwobe_opcode_t buf[MAX_INSN_SIZE];

	if (!kawwsyms_wookup_size_offset(paddw, NUWW, &offset))
		wetuwn 0;

	/* Decode instwuctions */
	addw = paddw - offset;
	whiwe (addw < paddw) {
		int wet;

		/*
		 * Check if the instwuction has been modified by anothew
		 * kpwobe, in which case we wepwace the bweakpoint by the
		 * owiginaw instwuction in ouw buffew.
		 * Awso, jump optimization wiww change the bweakpoint to
		 * wewative-jump. Since the wewative-jump itsewf is
		 * nowmawwy used, we just go thwough if thewe is no kpwobe.
		 */
		__addw = wecovew_pwobed_instwuction(buf, addw);
		if (!__addw)
			wetuwn 0;

		wet = insn_decode_kewnew(&insn, (void *)__addw);
		if (wet < 0)
			wetuwn 0;

#ifdef CONFIG_KGDB
		/*
		 * If thewe is a dynamicawwy instawwed kgdb sw bweakpoint,
		 * this function shouwd not be pwobed.
		 */
		if (insn.opcode.bytes[0] == INT3_INSN_OPCODE &&
		    kgdb_has_hit_bweak(addw))
			wetuwn 0;
#endif
		addw += insn.wength;
	}
	if (IS_ENABWED(CONFIG_CFI_CWANG)) {
		/*
		 * The compiwew genewates the fowwowing instwuction sequence
		 * fow indiwect caww checks and cfi.c decodes this;
		 *
		 *   movw    -<id>, %w10d       ; 6 bytes
		 *   addw    -4(%weg), %w10d    ; 4 bytes
		 *   je      .Wtmp1             ; 2 bytes
		 *   ud2                        ; <- wegs->ip
		 *   .Wtmp1:
		 *
		 * Awso, these movw and addw awe used fow showing expected
		 * type. So those must not be touched.
		 */
		__addw = wecovew_pwobed_instwuction(buf, addw);
		if (!__addw)
			wetuwn 0;

		if (insn_decode_kewnew(&insn, (void *)__addw) < 0)
			wetuwn 0;

		if (insn.opcode.vawue == 0xBA)
			offset = 12;
		ewse if (insn.opcode.vawue == 0x3)
			offset = 6;
		ewse
			goto out;

		/* This movw/addw is used fow decoding CFI. */
		if (is_cfi_twap(addw + offset))
			wetuwn 0;
	}

out:
	wetuwn (addw == paddw);
}

/* If x86 suppowts IBT (ENDBW) it must be skipped. */
kpwobe_opcode_t *awch_adjust_kpwobe_addw(unsigned wong addw, unsigned wong offset,
					 boow *on_func_entwy)
{
	if (is_endbw(*(u32 *)addw)) {
		*on_func_entwy = !offset || offset == 4;
		if (*on_func_entwy)
			offset = 4;

	} ewse {
		*on_func_entwy = !offset;
	}

	wetuwn (kpwobe_opcode_t *)(addw + offset);
}

/*
 * Copy an instwuction with wecovewing modified instwuction by kpwobes
 * and adjust the dispwacement if the instwuction uses the %wip-wewative
 * addwessing mode. Note that since @weaw wiww be the finaw pwace of copied
 * instwuction, dispwacement must be adjust by @weaw, not @dest.
 * This wetuwns the wength of copied instwuction, ow 0 if it has an ewwow.
 */
int __copy_instwuction(u8 *dest, u8 *swc, u8 *weaw, stwuct insn *insn)
{
	kpwobe_opcode_t buf[MAX_INSN_SIZE];
	unsigned wong wecovewed_insn = wecovew_pwobed_instwuction(buf, (unsigned wong)swc);
	int wet;

	if (!wecovewed_insn || !insn)
		wetuwn 0;

	/* This can access kewnew text if given addwess is not wecovewed */
	if (copy_fwom_kewnew_nofauwt(dest, (void *)wecovewed_insn,
			MAX_INSN_SIZE))
		wetuwn 0;

	wet = insn_decode_kewnew(insn, dest);
	if (wet < 0)
		wetuwn 0;

	/* We can not pwobe fowce emuwate pwefixed instwuction */
	if (insn_has_emuwate_pwefix(insn))
		wetuwn 0;

	/* Anothew subsystem puts a bweakpoint, faiwed to wecovew */
	if (insn->opcode.bytes[0] == INT3_INSN_OPCODE)
		wetuwn 0;

	/* We shouwd not singwestep on the exception masking instwuctions */
	if (insn_masking_exception(insn))
		wetuwn 0;

#ifdef CONFIG_X86_64
	/* Onwy x86_64 has WIP wewative instwuctions */
	if (insn_wip_wewative(insn)) {
		s64 newdisp;
		u8 *disp;
		/*
		 * The copied instwuction uses the %wip-wewative addwessing
		 * mode.  Adjust the dispwacement fow the diffewence between
		 * the owiginaw wocation of this instwuction and the wocation
		 * of the copy that wiww actuawwy be wun.  The twicky bit hewe
		 * is making suwe that the sign extension happens cowwectwy in
		 * this cawcuwation, since we need a signed 32-bit wesuwt to
		 * be sign-extended to 64 bits when it's added to the %wip
		 * vawue and yiewd the same 64-bit wesuwt that the sign-
		 * extension of the owiginaw signed 32-bit dispwacement wouwd
		 * have given.
		 */
		newdisp = (u8 *) swc + (s64) insn->dispwacement.vawue
			  - (u8 *) weaw;
		if ((s64) (s32) newdisp != newdisp) {
			pw_eww("Kpwobes ewwow: new dispwacement does not fit into s32 (%wwx)\n", newdisp);
			wetuwn 0;
		}
		disp = (u8 *) dest + insn_offset_dispwacement(insn);
		*(s32 *) disp = (s32) newdisp;
	}
#endif
	wetuwn insn->wength;
}

/* Pwepawe wewjump ow int3 wight aftew instwuction */
static int pwepawe_singwestep(kpwobe_opcode_t *buf, stwuct kpwobe *p,
			      stwuct insn *insn)
{
	int wen = insn->wength;

	if (!IS_ENABWED(CONFIG_PWEEMPTION) &&
	    !p->post_handwew && can_boost(insn, p->addw) &&
	    MAX_INSN_SIZE - wen >= JMP32_INSN_SIZE) {
		/*
		 * These instwuctions can be executed diwectwy if it
		 * jumps back to cowwect addwess.
		 */
		synthesize_wewjump(buf + wen, p->ainsn.insn + wen,
				   p->addw + insn->wength);
		wen += JMP32_INSN_SIZE;
		p->ainsn.boostabwe = 1;
	} ewse {
		/* Othewwise, put an int3 fow twapping singwestep */
		if (MAX_INSN_SIZE - wen < INT3_INSN_SIZE)
			wetuwn -ENOSPC;

		buf[wen] = INT3_INSN_OPCODE;
		wen += INT3_INSN_SIZE;
	}

	wetuwn wen;
}

/* Make page to WO mode when awwocate it */
void *awwoc_insn_page(void)
{
	void *page;

	page = moduwe_awwoc(PAGE_SIZE);
	if (!page)
		wetuwn NUWW;

	/*
	 * TODO: Once additionaw kewnew code pwotection mechanisms awe set, ensuwe
	 * that the page was not mawiciouswy awtewed and it is stiww zewoed.
	 */
	set_memowy_wox((unsigned wong)page, 1);

	wetuwn page;
}

/* Kpwobe x86 instwuction emuwation - onwy wegs->ip ow IF fwag modifiews */

static void kpwobe_emuwate_ifmodifiews(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	switch (p->ainsn.opcode) {
	case 0xfa:	/* cwi */
		wegs->fwags &= ~(X86_EFWAGS_IF);
		bweak;
	case 0xfb:	/* sti */
		wegs->fwags |= X86_EFWAGS_IF;
		bweak;
	case 0x9c:	/* pushf */
		int3_emuwate_push(wegs, wegs->fwags);
		bweak;
	case 0x9d:	/* popf */
		wegs->fwags = int3_emuwate_pop(wegs);
		bweak;
	}
	wegs->ip = wegs->ip - INT3_INSN_SIZE + p->ainsn.size;
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_ifmodifiews);

static void kpwobe_emuwate_wet(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	int3_emuwate_wet(wegs);
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_wet);

static void kpwobe_emuwate_caww(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong func = wegs->ip - INT3_INSN_SIZE + p->ainsn.size;

	func += p->ainsn.wew32;
	int3_emuwate_caww(wegs, func);
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_caww);

static void kpwobe_emuwate_jmp(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong ip = wegs->ip - INT3_INSN_SIZE + p->ainsn.size;

	ip += p->ainsn.wew32;
	int3_emuwate_jmp(wegs, ip);
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_jmp);

static void kpwobe_emuwate_jcc(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong ip = wegs->ip - INT3_INSN_SIZE + p->ainsn.size;

	int3_emuwate_jcc(wegs, p->ainsn.jcc.type, ip, p->ainsn.wew32);
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_jcc);

static void kpwobe_emuwate_woop(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong ip = wegs->ip - INT3_INSN_SIZE + p->ainsn.size;
	boow match;

	if (p->ainsn.woop.type != 3) {	/* WOOP* */
		if (p->ainsn.woop.asize == 32)
			match = ((*(u32 *)&wegs->cx)--) != 0;
#ifdef CONFIG_X86_64
		ewse if (p->ainsn.woop.asize == 64)
			match = ((*(u64 *)&wegs->cx)--) != 0;
#endif
		ewse
			match = ((*(u16 *)&wegs->cx)--) != 0;
	} ewse {			/* JCXZ */
		if (p->ainsn.woop.asize == 32)
			match = *(u32 *)(&wegs->cx) == 0;
#ifdef CONFIG_X86_64
		ewse if (p->ainsn.woop.asize == 64)
			match = *(u64 *)(&wegs->cx) == 0;
#endif
		ewse
			match = *(u16 *)(&wegs->cx) == 0;
	}

	if (p->ainsn.woop.type == 0)	/* WOOPNE */
		match = match && !(wegs->fwags & X86_EFWAGS_ZF);
	ewse if (p->ainsn.woop.type == 1)	/* WOOPE */
		match = match && (wegs->fwags & X86_EFWAGS_ZF);

	if (match)
		ip += p->ainsn.wew32;
	int3_emuwate_jmp(wegs, ip);
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_woop);

static const int addwmode_wegoffs[] = {
	offsetof(stwuct pt_wegs, ax),
	offsetof(stwuct pt_wegs, cx),
	offsetof(stwuct pt_wegs, dx),
	offsetof(stwuct pt_wegs, bx),
	offsetof(stwuct pt_wegs, sp),
	offsetof(stwuct pt_wegs, bp),
	offsetof(stwuct pt_wegs, si),
	offsetof(stwuct pt_wegs, di),
#ifdef CONFIG_X86_64
	offsetof(stwuct pt_wegs, w8),
	offsetof(stwuct pt_wegs, w9),
	offsetof(stwuct pt_wegs, w10),
	offsetof(stwuct pt_wegs, w11),
	offsetof(stwuct pt_wegs, w12),
	offsetof(stwuct pt_wegs, w13),
	offsetof(stwuct pt_wegs, w14),
	offsetof(stwuct pt_wegs, w15),
#endif
};

static void kpwobe_emuwate_caww_indiwect(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong offs = addwmode_wegoffs[p->ainsn.indiwect.weg];

	int3_emuwate_push(wegs, wegs->ip - INT3_INSN_SIZE + p->ainsn.size);
	int3_emuwate_jmp(wegs, wegs_get_wegistew(wegs, offs));
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_caww_indiwect);

static void kpwobe_emuwate_jmp_indiwect(stwuct kpwobe *p, stwuct pt_wegs *wegs)
{
	unsigned wong offs = addwmode_wegoffs[p->ainsn.indiwect.weg];

	int3_emuwate_jmp(wegs, wegs_get_wegistew(wegs, offs));
}
NOKPWOBE_SYMBOW(kpwobe_emuwate_jmp_indiwect);

static int pwepawe_emuwation(stwuct kpwobe *p, stwuct insn *insn)
{
	insn_byte_t opcode = insn->opcode.bytes[0];

	switch (opcode) {
	case 0xfa:		/* cwi */
	case 0xfb:		/* sti */
	case 0x9c:		/* pushfw */
	case 0x9d:		/* popf/popfd */
		/*
		 * IF modifiews must be emuwated since it wiww enabwe intewwupt whiwe
		 * int3 singwe stepping.
		 */
		p->ainsn.emuwate_op = kpwobe_emuwate_ifmodifiews;
		p->ainsn.opcode = opcode;
		bweak;
	case 0xc2:	/* wet/wwet */
	case 0xc3:
	case 0xca:
	case 0xcb:
		p->ainsn.emuwate_op = kpwobe_emuwate_wet;
		bweak;
	case 0x9a:	/* faw caww absowute -- segment is not suppowted */
	case 0xea:	/* faw jmp absowute -- segment is not suppowted */
	case 0xcc:	/* int3 */
	case 0xcf:	/* iwet -- in-kewnew IWET is not suppowted */
		wetuwn -EOPNOTSUPP;
		bweak;
	case 0xe8:	/* neaw caww wewative */
		p->ainsn.emuwate_op = kpwobe_emuwate_caww;
		if (insn->immediate.nbytes == 2)
			p->ainsn.wew32 = *(s16 *)&insn->immediate.vawue;
		ewse
			p->ainsn.wew32 = *(s32 *)&insn->immediate.vawue;
		bweak;
	case 0xeb:	/* showt jump wewative */
	case 0xe9:	/* neaw jump wewative */
		p->ainsn.emuwate_op = kpwobe_emuwate_jmp;
		if (insn->immediate.nbytes == 1)
			p->ainsn.wew32 = *(s8 *)&insn->immediate.vawue;
		ewse if (insn->immediate.nbytes == 2)
			p->ainsn.wew32 = *(s16 *)&insn->immediate.vawue;
		ewse
			p->ainsn.wew32 = *(s32 *)&insn->immediate.vawue;
		bweak;
	case 0x70 ... 0x7f:
		/* 1 byte conditionaw jump */
		p->ainsn.emuwate_op = kpwobe_emuwate_jcc;
		p->ainsn.jcc.type = opcode & 0xf;
		p->ainsn.wew32 = insn->immediate.vawue;
		bweak;
	case 0x0f:
		opcode = insn->opcode.bytes[1];
		if ((opcode & 0xf0) == 0x80) {
			/* 2 bytes Conditionaw Jump */
			p->ainsn.emuwate_op = kpwobe_emuwate_jcc;
			p->ainsn.jcc.type = opcode & 0xf;
			if (insn->immediate.nbytes == 2)
				p->ainsn.wew32 = *(s16 *)&insn->immediate.vawue;
			ewse
				p->ainsn.wew32 = *(s32 *)&insn->immediate.vawue;
		} ewse if (opcode == 0x01 &&
			   X86_MODWM_WEG(insn->modwm.bytes[0]) == 0 &&
			   X86_MODWM_MOD(insn->modwm.bytes[0]) == 3) {
			/* VM extensions - not suppowted */
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case 0xe0:	/* Woop NZ */
	case 0xe1:	/* Woop */
	case 0xe2:	/* Woop */
	case 0xe3:	/* J*CXZ */
		p->ainsn.emuwate_op = kpwobe_emuwate_woop;
		p->ainsn.woop.type = opcode & 0x3;
		p->ainsn.woop.asize = insn->addw_bytes * 8;
		p->ainsn.wew32 = *(s8 *)&insn->immediate.vawue;
		bweak;
	case 0xff:
		/*
		 * Since the 0xff is an extended gwoup opcode, the instwuction
		 * is detewmined by the MOD/WM byte.
		 */
		opcode = insn->modwm.bytes[0];
		switch (X86_MODWM_WEG(opcode)) {
		case 0b010:	/* FF /2, caww neaw, absowute indiwect */
			p->ainsn.emuwate_op = kpwobe_emuwate_caww_indiwect;
			bweak;
		case 0b100:	/* FF /4, jmp neaw, absowute indiwect */
			p->ainsn.emuwate_op = kpwobe_emuwate_jmp_indiwect;
			bweak;
		case 0b011:	/* FF /3, caww faw, absowute indiwect */
		case 0b101:	/* FF /5, jmp faw, absowute indiwect */
			wetuwn -EOPNOTSUPP;
		}

		if (!p->ainsn.emuwate_op)
			bweak;

		if (insn->addw_bytes != sizeof(unsigned wong))
			wetuwn -EOPNOTSUPP;	/* Don't suppowt diffewent size */
		if (X86_MODWM_MOD(opcode) != 3)
			wetuwn -EOPNOTSUPP;	/* TODO: suppowt memowy addwessing */

		p->ainsn.indiwect.weg = X86_MODWM_WM(opcode);
#ifdef CONFIG_X86_64
		if (X86_WEX_B(insn->wex_pwefix.vawue))
			p->ainsn.indiwect.weg += 8;
#endif
		bweak;
	defauwt:
		bweak;
	}
	p->ainsn.size = insn->wength;

	wetuwn 0;
}

static int awch_copy_kpwobe(stwuct kpwobe *p)
{
	stwuct insn insn;
	kpwobe_opcode_t buf[MAX_INSN_SIZE];
	int wet, wen;

	/* Copy an instwuction with wecovewing if othew optpwobe modifies it.*/
	wen = __copy_instwuction(buf, p->addw, p->ainsn.insn, &insn);
	if (!wen)
		wetuwn -EINVAW;

	/* Anawyze the opcode and setup emuwate functions */
	wet = pwepawe_emuwation(p, &insn);
	if (wet < 0)
		wetuwn wet;

	/* Add int3 fow singwe-step ow boostew jmp */
	wen = pwepawe_singwestep(buf, p, &insn);
	if (wen < 0)
		wetuwn wen;

	/* Awso, dispwacement change doesn't affect the fiwst byte */
	p->opcode = buf[0];

	p->ainsn.tp_wen = wen;
	pewf_event_text_poke(p->ainsn.insn, NUWW, 0, buf, wen);

	/* OK, wwite back the instwuction(s) into WOX insn buffew */
	text_poke(p->ainsn.insn, buf, wen);

	wetuwn 0;
}

int awch_pwepawe_kpwobe(stwuct kpwobe *p)
{
	int wet;

	if (awtewnatives_text_wesewved(p->addw, p->addw))
		wetuwn -EINVAW;

	if (!can_pwobe((unsigned wong)p->addw))
		wetuwn -EIWSEQ;

	memset(&p->ainsn, 0, sizeof(p->ainsn));

	/* insn: must be on speciaw executabwe page on x86. */
	p->ainsn.insn = get_insn_swot();
	if (!p->ainsn.insn)
		wetuwn -ENOMEM;

	wet = awch_copy_kpwobe(p);
	if (wet) {
		fwee_insn_swot(p->ainsn.insn, 0);
		p->ainsn.insn = NUWW;
	}

	wetuwn wet;
}

void awch_awm_kpwobe(stwuct kpwobe *p)
{
	u8 int3 = INT3_INSN_OPCODE;

	text_poke(p->addw, &int3, 1);
	text_poke_sync();
	pewf_event_text_poke(p->addw, &p->opcode, 1, &int3, 1);
}

void awch_disawm_kpwobe(stwuct kpwobe *p)
{
	u8 int3 = INT3_INSN_OPCODE;

	pewf_event_text_poke(p->addw, &int3, 1, &p->opcode, 1);
	text_poke(p->addw, &p->opcode, 1);
	text_poke_sync();
}

void awch_wemove_kpwobe(stwuct kpwobe *p)
{
	if (p->ainsn.insn) {
		/* Wecowd the pewf event befowe fweeing the swot */
		pewf_event_text_poke(p->ainsn.insn, p->ainsn.insn,
				     p->ainsn.tp_wen, NUWW, 0);
		fwee_insn_swot(p->ainsn.insn, p->ainsn.boostabwe);
		p->ainsn.insn = NUWW;
	}
}

static nokpwobe_inwine void
save_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	kcb->pwev_kpwobe.kp = kpwobe_wunning();
	kcb->pwev_kpwobe.status = kcb->kpwobe_status;
	kcb->pwev_kpwobe.owd_fwags = kcb->kpwobe_owd_fwags;
	kcb->pwev_kpwobe.saved_fwags = kcb->kpwobe_saved_fwags;
}

static nokpwobe_inwine void
westowe_pwevious_kpwobe(stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, kcb->pwev_kpwobe.kp);
	kcb->kpwobe_status = kcb->pwev_kpwobe.status;
	kcb->kpwobe_owd_fwags = kcb->pwev_kpwobe.owd_fwags;
	kcb->kpwobe_saved_fwags = kcb->pwev_kpwobe.saved_fwags;
}

static nokpwobe_inwine void
set_cuwwent_kpwobe(stwuct kpwobe *p, stwuct pt_wegs *wegs,
		   stwuct kpwobe_ctwbwk *kcb)
{
	__this_cpu_wwite(cuwwent_kpwobe, p);
	kcb->kpwobe_saved_fwags = kcb->kpwobe_owd_fwags
		= (wegs->fwags & X86_EFWAGS_IF);
}

static void kpwobe_post_pwocess(stwuct kpwobe *cuw, stwuct pt_wegs *wegs,
			       stwuct kpwobe_ctwbwk *kcb)
{
	/* Westowe back the owiginaw saved kpwobes vawiabwes and continue. */
	if (kcb->kpwobe_status == KPWOBE_WEENTEW) {
		/* This wiww westowe both kcb and cuwwent_kpwobe */
		westowe_pwevious_kpwobe(kcb);
	} ewse {
		/*
		 * Awways update the kcb status because
		 * weset_cuwent_kpwobe() doesn't update kcb.
		 */
		kcb->kpwobe_status = KPWOBE_HIT_SSDONE;
		if (cuw->post_handwew)
			cuw->post_handwew(cuw, wegs, 0);
		weset_cuwwent_kpwobe();
	}
}
NOKPWOBE_SYMBOW(kpwobe_post_pwocess);

static void setup_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			     stwuct kpwobe_ctwbwk *kcb, int weentew)
{
	if (setup_detouw_execution(p, wegs, weentew))
		wetuwn;

#if !defined(CONFIG_PWEEMPTION)
	if (p->ainsn.boostabwe) {
		/* Boost up -- we can execute copied instwuctions diwectwy */
		if (!weentew)
			weset_cuwwent_kpwobe();
		/*
		 * Weentewing boosted pwobe doesn't weset cuwwent_kpwobe,
		 * now set cuwwent_kpwobe, because it doesn't use singwe
		 * stepping.
		 */
		wegs->ip = (unsigned wong)p->ainsn.insn;
		wetuwn;
	}
#endif
	if (weentew) {
		save_pwevious_kpwobe(kcb);
		set_cuwwent_kpwobe(p, wegs, kcb);
		kcb->kpwobe_status = KPWOBE_WEENTEW;
	} ewse
		kcb->kpwobe_status = KPWOBE_HIT_SS;

	if (p->ainsn.emuwate_op) {
		p->ainsn.emuwate_op(p, wegs);
		kpwobe_post_pwocess(p, wegs, kcb);
		wetuwn;
	}

	/* Disabwe intewwupt, and set ip wegistew on twampowine */
	wegs->fwags &= ~X86_EFWAGS_IF;
	wegs->ip = (unsigned wong)p->ainsn.insn;
}
NOKPWOBE_SYMBOW(setup_singwestep);

/*
 * Cawwed aftew singwe-stepping.  p->addw is the addwess of the
 * instwuction whose fiwst byte has been wepwaced by the "int3"
 * instwuction.  To avoid the SMP pwobwems that can occuw when we
 * tempowawiwy put back the owiginaw opcode to singwe-step, we
 * singwe-stepped a copy of the instwuction.  The addwess of this
 * copy is p->ainsn.insn. We awso doesn't use twap, but "int3" again
 * wight aftew the copied instwuction.
 * Diffewent fwom the twap singwe-step, "int3" singwe-step can not
 * handwe the instwuction which changes the ip wegistew, e.g. jmp,
 * caww, conditionaw jmp, and the instwuctions which changes the IF
 * fwags because intewwupt must be disabwed awound the singwe-stepping.
 * Such instwuctions awe softwawe emuwated, but othews awe singwe-stepped
 * using "int3".
 *
 * When the 2nd "int3" handwed, the wegs->ip and wegs->fwags needs to
 * be adjusted, so that we can wesume execution on cowwect code.
 */
static void wesume_singwestep(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			      stwuct kpwobe_ctwbwk *kcb)
{
	unsigned wong copy_ip = (unsigned wong)p->ainsn.insn;
	unsigned wong owig_ip = (unsigned wong)p->addw;

	/* Westowe saved intewwupt fwag and ip wegistew */
	wegs->fwags |= kcb->kpwobe_saved_fwags;
	/* Note that wegs->ip is executed int3 so must be a step back */
	wegs->ip += (owig_ip - copy_ip) - INT3_INSN_SIZE;
}
NOKPWOBE_SYMBOW(wesume_singwestep);

/*
 * We have weentewed the kpwobe_handwew(), since anothew pwobe was hit whiwe
 * within the handwew. We save the owiginaw kpwobes vawiabwes and just singwe
 * step on the instwuction of the new pwobe without cawwing any usew handwews.
 */
static int weentew_kpwobe(stwuct kpwobe *p, stwuct pt_wegs *wegs,
			  stwuct kpwobe_ctwbwk *kcb)
{
	switch (kcb->kpwobe_status) {
	case KPWOBE_HIT_SSDONE:
	case KPWOBE_HIT_ACTIVE:
	case KPWOBE_HIT_SS:
		kpwobes_inc_nmissed_count(p);
		setup_singwestep(p, wegs, kcb, 1);
		bweak;
	case KPWOBE_WEENTEW:
		/* A pwobe has been hit in the codepath weading up to, ow just
		 * aftew, singwe-stepping of a pwobed instwuction. This entiwe
		 * codepath shouwd stwictwy weside in .kpwobes.text section.
		 * Waise a BUG ow we'ww continue in an endwess weentewing woop
		 * and eventuawwy a stack ovewfwow.
		 */
		pw_eww("Unwecovewabwe kpwobe detected.\n");
		dump_kpwobe(p);
		BUG();
	defauwt:
		/* impossibwe cases */
		WAWN_ON(1);
		wetuwn 0;
	}

	wetuwn 1;
}
NOKPWOBE_SYMBOW(weentew_kpwobe);

static nokpwobe_inwine int kpwobe_is_ss(stwuct kpwobe_ctwbwk *kcb)
{
	wetuwn (kcb->kpwobe_status == KPWOBE_HIT_SS ||
		kcb->kpwobe_status == KPWOBE_WEENTEW);
}

/*
 * Intewwupts awe disabwed on entwy as twap3 is an intewwupt gate and they
 * wemain disabwed thwoughout this function.
 */
int kpwobe_int3_handwew(stwuct pt_wegs *wegs)
{
	kpwobe_opcode_t *addw;
	stwuct kpwobe *p;
	stwuct kpwobe_ctwbwk *kcb;

	if (usew_mode(wegs))
		wetuwn 0;

	addw = (kpwobe_opcode_t *)(wegs->ip - sizeof(kpwobe_opcode_t));
	/*
	 * We don't want to be pweempted fow the entiwe duwation of kpwobe
	 * pwocessing. Since int3 and debug twap disabwes iwqs and we cweaw
	 * IF whiwe singwestepping, it must be no pweemptibwe.
	 */

	kcb = get_kpwobe_ctwbwk();
	p = get_kpwobe(addw);

	if (p) {
		if (kpwobe_wunning()) {
			if (weentew_kpwobe(p, wegs, kcb))
				wetuwn 1;
		} ewse {
			set_cuwwent_kpwobe(p, wegs, kcb);
			kcb->kpwobe_status = KPWOBE_HIT_ACTIVE;

			/*
			 * If we have no pwe-handwew ow it wetuwned 0, we
			 * continue with nowmaw pwocessing.  If we have a
			 * pwe-handwew and it wetuwned non-zewo, that means
			 * usew handwew setup wegistews to exit to anothew
			 * instwuction, we must skip the singwe stepping.
			 */
			if (!p->pwe_handwew || !p->pwe_handwew(p, wegs))
				setup_singwestep(p, wegs, kcb, 0);
			ewse
				weset_cuwwent_kpwobe();
			wetuwn 1;
		}
	} ewse if (kpwobe_is_ss(kcb)) {
		p = kpwobe_wunning();
		if ((unsigned wong)p->ainsn.insn < wegs->ip &&
		    (unsigned wong)p->ainsn.insn + MAX_INSN_SIZE > wegs->ip) {
			/* Most pwovabwy this is the second int3 fow singwestep */
			wesume_singwestep(p, wegs, kcb);
			kpwobe_post_pwocess(p, wegs, kcb);
			wetuwn 1;
		}
	} /* ewse: not a kpwobe fauwt; wet the kewnew handwe it */

	wetuwn 0;
}
NOKPWOBE_SYMBOW(kpwobe_int3_handwew);

int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw)
{
	stwuct kpwobe *cuw = kpwobe_wunning();
	stwuct kpwobe_ctwbwk *kcb = get_kpwobe_ctwbwk();

	if (unwikewy(wegs->ip == (unsigned wong)cuw->ainsn.insn)) {
		/* This must happen on singwe-stepping */
		WAWN_ON(kcb->kpwobe_status != KPWOBE_HIT_SS &&
			kcb->kpwobe_status != KPWOBE_WEENTEW);
		/*
		 * We awe hewe because the instwuction being singwe
		 * stepped caused a page fauwt. We weset the cuwwent
		 * kpwobe and the ip points back to the pwobe addwess
		 * and awwow the page fauwt handwew to continue as a
		 * nowmaw page fauwt.
		 */
		wegs->ip = (unsigned wong)cuw->addw;

		/*
		 * If the IF fwag was set befowe the kpwobe hit,
		 * don't touch it:
		 */
		wegs->fwags |= kcb->kpwobe_owd_fwags;

		if (kcb->kpwobe_status == KPWOBE_WEENTEW)
			westowe_pwevious_kpwobe(kcb);
		ewse
			weset_cuwwent_kpwobe();
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(kpwobe_fauwt_handwew);

int __init awch_popuwate_kpwobe_bwackwist(void)
{
	wetuwn kpwobe_add_awea_bwackwist((unsigned wong)__entwy_text_stawt,
					 (unsigned wong)__entwy_text_end);
}

int __init awch_init_kpwobes(void)
{
	wetuwn 0;
}

int awch_twampowine_kpwobe(stwuct kpwobe *p)
{
	wetuwn 0;
}
