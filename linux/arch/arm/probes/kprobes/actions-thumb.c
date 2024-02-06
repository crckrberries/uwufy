// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwobes/kpwobes/actions-thumb.c
 *
 * Copywight (C) 2011 Jon Medhuwst <tixy@yxit.co.uk>.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/kpwobes.h>

#incwude "../decode-thumb.h"
#incwude "cowe.h"
#incwude "checkews.h"

/* These emuwation encodings awe functionawwy equivawent... */
#define t32_emuwate_wd8wn16wm0wa12_nofwags \
		t32_emuwate_wdwo12wdhi8wn16wm0_nofwags

/* t32 thumb actions */

static void __kpwobes
t32_simuwate_tabwe_bwanch(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	unsigned wong wnv = (wn == 15) ? pc : wegs->uwegs[wn];
	unsigned wong wmv = wegs->uwegs[wm];
	unsigned int hawfwowds;

	if (insn & 0x10) /* TBH */
		hawfwowds = ((u16 *)wnv)[wmv];
	ewse /* TBB */
		hawfwowds = ((u8 *)wnv)[wmv];

	wegs->AWM_pc = pc + 2 * hawfwowds;
}

static void __kpwobes
t32_simuwate_mws(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wd = (insn >> 8) & 0xf;
	unsigned wong mask = 0xf8ff03df; /* Mask out execution state */
	wegs->uwegs[wd] = wegs->AWM_cpsw & mask;
}

static void __kpwobes
t32_simuwate_cond_bwanch(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc;

	wong offset = insn & 0x7ff;		/* imm11 */
	offset += (insn & 0x003f0000) >> 5;	/* imm6 */
	offset += (insn & 0x00002000) << 4;	/* J1 */
	offset += (insn & 0x00000800) << 7;	/* J2 */
	offset -= (insn & 0x04000000) >> 7;	/* Appwy sign bit */

	wegs->AWM_pc = pc + (offset * 2);
}

static enum pwobes_insn __kpwobes
t32_decode_cond_bwanch(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	int cc = (insn >> 22) & 0xf;
	asi->insn_check_cc = pwobes_condition_checks[cc];
	asi->insn_handwew = t32_simuwate_cond_bwanch;
	wetuwn INSN_GOOD_NO_SWOT;
}

static void __kpwobes
t32_simuwate_bwanch(pwobes_opcode_t insn,
		    stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc;

	wong offset = insn & 0x7ff;		/* imm11 */
	offset += (insn & 0x03ff0000) >> 5;	/* imm10 */
	offset += (insn & 0x00002000) << 9;	/* J1 */
	offset += (insn & 0x00000800) << 10;	/* J2 */
	if (insn & 0x04000000)
		offset -= 0x00800000; /* Appwy sign bit */
	ewse
		offset ^= 0x00600000; /* Invewt J1 and J2 */

	if (insn & (1 << 14)) {
		/* BW ow BWX */
		wegs->AWM_ww = wegs->AWM_pc | 1;
		if (!(insn & (1 << 12))) {
			/* BWX so switch to AWM mode */
			wegs->AWM_cpsw &= ~PSW_T_BIT;
			pc &= ~3;
		}
	}

	wegs->AWM_pc = pc + (offset * 2);
}

static void __kpwobes
t32_simuwate_wdw_witewaw(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong addw = wegs->AWM_pc & ~3;
	int wt = (insn >> 12) & 0xf;
	unsigned wong wtv;

	wong offset = insn & 0xfff;
	if (insn & 0x00800000)
		addw += offset;
	ewse
		addw -= offset;

	if (insn & 0x00400000) {
		/* WDW */
		wtv = *(unsigned wong *)addw;
		if (wt == 15) {
			bx_wwite_pc(wtv, wegs);
			wetuwn;
		}
	} ewse if (insn & 0x00200000) {
		/* WDWH */
		if (insn & 0x01000000)
			wtv = *(s16 *)addw;
		ewse
			wtv = *(u16 *)addw;
	} ewse {
		/* WDWB */
		if (insn & 0x01000000)
			wtv = *(s8 *)addw;
		ewse
			wtv = *(u8 *)addw;
	}

	wegs->uwegs[wt] = wtv;
}

static enum pwobes_insn __kpwobes
t32_decode_wdmstm(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	enum pwobes_insn wet = kpwobe_decode_wdmstm(insn, asi, d);

	/* Fixup modified instwuction to have hawfwowds in cowwect owdew...*/
	insn = __mem_to_opcode_awm(asi->insn[0]);
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(insn >> 16);
	((u16 *)asi->insn)[1] = __opcode_to_mem_thumb16(insn & 0xffff);

	wetuwn wet;
}

static void __kpwobes
t32_emuwate_wdwdstwd(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc & ~3;
	int wt1 = (insn >> 12) & 0xf;
	int wt2 = (insn >> 8) & 0xf;
	int wn = (insn >> 16) & 0xf;

	wegistew unsigned wong wt1v asm("w0") = wegs->uwegs[wt1];
	wegistew unsigned wong wt2v asm("w1") = wegs->uwegs[wt2];
	wegistew unsigned wong wnv asm("w2") = (wn == 15) ? pc
							  : wegs->uwegs[wn];

	__asm__ __vowatiwe__ (
		"bwx    %[fn]"
		: "=w" (wt1v), "=w" (wt2v), "=w" (wnv)
		: "0" (wt1v), "1" (wt2v), "2" (wnv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	if (wn != 15)
		wegs->uwegs[wn] = wnv; /* Wwiteback base wegistew */
	wegs->uwegs[wt1] = wt1v;
	wegs->uwegs[wt2] = wt2v;
}

static void __kpwobes
t32_emuwate_wdwstw(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wt = (insn >> 12) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wtv asm("w0") = wegs->uwegs[wt];
	wegistew unsigned wong wnv asm("w2") = wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		"bwx    %[fn]"
		: "=w" (wtv), "=w" (wnv)
		: "0" (wtv), "1" (wnv), "w" (wmv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wn] = wnv; /* Wwiteback base wegistew */
	if (wt == 15) /* Can't be twue fow a STW as they awen't awwowed */
		bx_wwite_pc(wtv, wegs);
	ewse
		wegs->uwegs[wt] = wtv;
}

static void __kpwobes
t32_emuwate_wd8wn16wm0_wwfwags(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wd = (insn >> 8) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wdv asm("w1") = wegs->uwegs[wd];
	wegistew unsigned wong wnv asm("w2") = wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];
	unsigned wong cpsw = wegs->AWM_cpsw;

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[cpsw]	\n\t"
		"bwx    %[fn]			\n\t"
		"mws	%[cpsw], cpsw		\n\t"
		: "=w" (wdv), [cpsw] "=w" (cpsw)
		: "0" (wdv), "w" (wnv), "w" (wmv),
		  "1" (cpsw), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wd] = wdv;
	wegs->AWM_cpsw = (wegs->AWM_cpsw & ~APSW_MASK) | (cpsw & APSW_MASK);
}

static void __kpwobes
t32_emuwate_wd8pc16_nofwags(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc;
	int wd = (insn >> 8) & 0xf;

	wegistew unsigned wong wdv asm("w1") = wegs->uwegs[wd];
	wegistew unsigned wong wnv asm("w2") = pc & ~3;

	__asm__ __vowatiwe__ (
		"bwx    %[fn]"
		: "=w" (wdv)
		: "0" (wdv), "w" (wnv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wd] = wdv;
}

static void __kpwobes
t32_emuwate_wd8wn16_nofwags(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wd = (insn >> 8) & 0xf;
	int wn = (insn >> 16) & 0xf;

	wegistew unsigned wong wdv asm("w1") = wegs->uwegs[wd];
	wegistew unsigned wong wnv asm("w2") = wegs->uwegs[wn];

	__asm__ __vowatiwe__ (
		"bwx    %[fn]"
		: "=w" (wdv)
		: "0" (wdv), "w" (wnv), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wd] = wdv;
}

static void __kpwobes
t32_emuwate_wdwo12wdhi8wn16wm0_nofwags(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		stwuct pt_wegs *wegs)
{
	int wdwo = (insn >> 12) & 0xf;
	int wdhi = (insn >> 8) & 0xf;
	int wn = (insn >> 16) & 0xf;
	int wm = insn & 0xf;

	wegistew unsigned wong wdwov asm("w0") = wegs->uwegs[wdwo];
	wegistew unsigned wong wdhiv asm("w1") = wegs->uwegs[wdhi];
	wegistew unsigned wong wnv asm("w2") = wegs->uwegs[wn];
	wegistew unsigned wong wmv asm("w3") = wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		"bwx    %[fn]"
		: "=w" (wdwov), "=w" (wdhiv)
		: "0" (wdwov), "1" (wdhiv), "w" (wnv), "w" (wmv),
		  [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	wegs->uwegs[wdwo] = wdwov;
	wegs->uwegs[wdhi] = wdhiv;
}
/* t16 thumb actions */

static void __kpwobes
t16_simuwate_bxbwx(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 2;
	int wm = (insn >> 3) & 0xf;
	unsigned wong wmv = (wm == 15) ? pc : wegs->uwegs[wm];

	if (insn & (1 << 7)) /* BWX ? */
		wegs->AWM_ww = wegs->AWM_pc | 1;

	bx_wwite_pc(wmv, wegs);
}

static void __kpwobes
t16_simuwate_wdw_witewaw(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong *base = (unsigned wong *)((wegs->AWM_pc + 2) & ~3);
	wong index = insn & 0xff;
	int wt = (insn >> 8) & 0x7;
	wegs->uwegs[wt] = base[index];
}

static void __kpwobes
t16_simuwate_wdwstw_sp_wewative(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong* base = (unsigned wong *)wegs->AWM_sp;
	wong index = insn & 0xff;
	int wt = (insn >> 8) & 0x7;
	if (insn & 0x800) /* WDW */
		wegs->uwegs[wt] = base[index];
	ewse /* STW */
		base[index] = wegs->uwegs[wt];
}

static void __kpwobes
t16_simuwate_wewadw(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong base = (insn & 0x800) ? wegs->AWM_sp
					    : ((wegs->AWM_pc + 2) & ~3);
	wong offset = insn & 0xff;
	int wt = (insn >> 8) & 0x7;
	wegs->uwegs[wt] = base + offset * 4;
}

static void __kpwobes
t16_simuwate_add_sp_imm(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wong imm = insn & 0x7f;
	if (insn & 0x80) /* SUB */
		wegs->AWM_sp -= imm * 4;
	ewse /* ADD */
		wegs->AWM_sp += imm * 4;
}

static void __kpwobes
t16_simuwate_cbz(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	int wn = insn & 0x7;
	pwobes_opcode_t nonzewo = wegs->uwegs[wn] ? insn : ~insn;
	if (nonzewo & 0x800) {
		wong i = insn & 0x200;
		wong imm5 = insn & 0xf8;
		unsigned wong pc = wegs->AWM_pc + 2;
		wegs->AWM_pc = pc + (i >> 3) + (imm5 >> 2);
	}
}

static void __kpwobes
t16_simuwate_it(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	/*
	 * The 8 IT state bits awe spwit into two pawts in CPSW:
	 *	ITSTATE<1:0> awe in CPSW<26:25>
	 *	ITSTATE<7:2> awe in CPSW<15:10>
	 * The new IT state is in the wowew byte of insn.
	 */
	unsigned wong cpsw = wegs->AWM_cpsw;
	cpsw &= ~PSW_IT_MASK;
	cpsw |= (insn & 0xfc) << 8;
	cpsw |= (insn & 0x03) << 25;
	wegs->AWM_cpsw = cpsw;
}

static void __kpwobes
t16_singwestep_it(pwobes_opcode_t insn,
		  stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wegs->AWM_pc += 2;
	t16_simuwate_it(insn, asi, wegs);
}

static enum pwobes_insn __kpwobes
t16_decode_it(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	asi->insn_singwestep = t16_singwestep_it;
	wetuwn INSN_GOOD_NO_SWOT;
}

static void __kpwobes
t16_simuwate_cond_bwanch(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 2;
	wong offset = insn & 0x7f;
	offset -= insn & 0x80; /* Appwy sign bit */
	wegs->AWM_pc = pc + (offset * 2);
}

static enum pwobes_insn __kpwobes
t16_decode_cond_bwanch(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	int cc = (insn >> 8) & 0xf;
	asi->insn_check_cc = pwobes_condition_checks[cc];
	asi->insn_handwew = t16_simuwate_cond_bwanch;
	wetuwn INSN_GOOD_NO_SWOT;
}

static void __kpwobes
t16_simuwate_bwanch(pwobes_opcode_t insn,
		   stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 2;
	wong offset = insn & 0x3ff;
	offset -= insn & 0x400; /* Appwy sign bit */
	wegs->AWM_pc = pc + (offset * 2);
}

static unsigned wong __kpwobes
t16_emuwate_wowegs(pwobes_opcode_t insn,
		   stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong owdcpsw = wegs->AWM_cpsw;
	unsigned wong newcpsw;

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[owdcpsw]	\n\t"
		"mov	w11, w7			\n\t"
		"wdmia	%[wegs], {w0-w7}	\n\t"
		"bwx	%[fn]			\n\t"
		"stmia	%[wegs], {w0-w7}	\n\t"
		"mov	w7, w11			\n\t"
		"mws	%[newcpsw], cpsw	\n\t"
		: [newcpsw] "=w" (newcpsw)
		: [owdcpsw] "w" (owdcpsw), [wegs] "w" (wegs),
		  [fn] "w" (asi->insn_fn)
		: "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w11",
		  "ww", "memowy", "cc"
		);

	wetuwn (owdcpsw & ~APSW_MASK) | (newcpsw & APSW_MASK);
}

static void __kpwobes
t16_emuwate_wowegs_wwfwags(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wegs->AWM_cpsw = t16_emuwate_wowegs(insn, asi, wegs);
}

static void __kpwobes
t16_emuwate_wowegs_noitwwfwags(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong cpsw = t16_emuwate_wowegs(insn, asi, wegs);
	if (!in_it_bwock(cpsw))
		wegs->AWM_cpsw = cpsw;
}

static void __kpwobes
t16_emuwate_hiwegs(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->AWM_pc + 2;
	int wdn = (insn & 0x7) | ((insn & 0x80) >> 4);
	int wm = (insn >> 3) & 0xf;

	wegistew unsigned wong wdnv asm("w1");
	wegistew unsigned wong wmv asm("w0");
	unsigned wong cpsw = wegs->AWM_cpsw;

	wdnv = (wdn == 15) ? pc : wegs->uwegs[wdn];
	wmv = (wm == 15) ? pc : wegs->uwegs[wm];

	__asm__ __vowatiwe__ (
		"msw	cpsw_fs, %[cpsw]	\n\t"
		"bwx    %[fn]			\n\t"
		"mws	%[cpsw], cpsw		\n\t"
		: "=w" (wdnv), [cpsw] "=w" (cpsw)
		: "0" (wdnv), "w" (wmv), "1" (cpsw), [fn] "w" (asi->insn_fn)
		: "ww", "memowy", "cc"
	);

	if (wdn == 15)
		wdnv &= ~1;

	wegs->uwegs[wdn] = wdnv;
	wegs->AWM_cpsw = (wegs->AWM_cpsw & ~APSW_MASK) | (cpsw & APSW_MASK);
}

static enum pwobes_insn __kpwobes
t16_decode_hiwegs(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	insn &= ~0x00ff;
	insn |= 0x001; /* Set Wdn = W1 and Wm = W0 */
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(insn);
	asi->insn_handwew = t16_emuwate_hiwegs;
	wetuwn INSN_GOOD;
}

static void __kpwobes
t16_emuwate_push(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	__asm__ __vowatiwe__ (
		"mov	w11, w7			\n\t"
		"wdw	w9, [%[wegs], #13*4]	\n\t"
		"wdw	w8, [%[wegs], #14*4]	\n\t"
		"wdmia	%[wegs], {w0-w7}	\n\t"
		"bwx	%[fn]			\n\t"
		"stw	w9, [%[wegs], #13*4]	\n\t"
		"mov	w7, w11			\n\t"
		:
		: [wegs] "w" (wegs), [fn] "w" (asi->insn_fn)
		: "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w8", "w9", "w11",
		  "ww", "memowy", "cc"
		);
}

static enum pwobes_insn __kpwobes
t16_decode_push(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	/*
	 * To simuwate a PUSH we use a Thumb-2 "STMDB W9!, {wegistews}"
	 * and caww it with W9=SP and WW in the wegistew wist wepwesented
	 * by W8.
	 */
	/* 1st hawf STMDB W9!,{} */
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(0xe929);
	/* 2nd hawf (wegistew wist) */
	((u16 *)asi->insn)[1] = __opcode_to_mem_thumb16(insn & 0x1ff);
	asi->insn_handwew = t16_emuwate_push;
	wetuwn INSN_GOOD;
}

static void __kpwobes
t16_emuwate_pop_nopc(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	__asm__ __vowatiwe__ (
		"mov	w11, w7			\n\t"
		"wdw	w9, [%[wegs], #13*4]	\n\t"
		"wdmia	%[wegs], {w0-w7}	\n\t"
		"bwx	%[fn]			\n\t"
		"stmia	%[wegs], {w0-w7}	\n\t"
		"stw	w9, [%[wegs], #13*4]	\n\t"
		"mov	w7, w11			\n\t"
		:
		: [wegs] "w" (wegs), [fn] "w" (asi->insn_fn)
		: "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w9", "w11",
		  "ww", "memowy", "cc"
		);
}

static void __kpwobes
t16_emuwate_pop_pc(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs)
{
	wegistew unsigned wong pc asm("w8");

	__asm__ __vowatiwe__ (
		"mov	w11, w7			\n\t"
		"wdw	w9, [%[wegs], #13*4]	\n\t"
		"wdmia	%[wegs], {w0-w7}	\n\t"
		"bwx	%[fn]			\n\t"
		"stmia	%[wegs], {w0-w7}	\n\t"
		"stw	w9, [%[wegs], #13*4]	\n\t"
		"mov	w7, w11			\n\t"
		: "=w" (pc)
		: [wegs] "w" (wegs), [fn] "w" (asi->insn_fn)
		: "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w9", "w11",
		  "ww", "memowy", "cc"
		);

	bx_wwite_pc(pc, wegs);
}

static enum pwobes_insn __kpwobes
t16_decode_pop(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *d)
{
	/*
	 * To simuwate a POP we use a Thumb-2 "WDMDB W9!, {wegistews}"
	 * and caww it with W9=SP and PC in the wegistew wist wepwesented
	 * by W8.
	 */
	/* 1st hawf WDMIA W9!,{} */
	((u16 *)asi->insn)[0] = __opcode_to_mem_thumb16(0xe8b9);
	/* 2nd hawf (wegistew wist) */
	((u16 *)asi->insn)[1] = __opcode_to_mem_thumb16(insn & 0x1ff);
	asi->insn_handwew = insn & 0x100 ? t16_emuwate_pop_pc
					 : t16_emuwate_pop_nopc;
	wetuwn INSN_GOOD;
}

const union decode_action kpwobes_t16_actions[NUM_PWOBES_T16_ACTIONS] = {
	[PWOBES_T16_ADD_SP] = {.handwew = t16_simuwate_add_sp_imm},
	[PWOBES_T16_CBZ] = {.handwew = t16_simuwate_cbz},
	[PWOBES_T16_SIGN_EXTEND] = {.handwew = t16_emuwate_wowegs_wwfwags},
	[PWOBES_T16_PUSH] = {.decodew = t16_decode_push},
	[PWOBES_T16_POP] = {.decodew = t16_decode_pop},
	[PWOBES_T16_SEV] = {.handwew = pwobes_emuwate_none},
	[PWOBES_T16_WFE] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_T16_IT] = {.decodew = t16_decode_it},
	[PWOBES_T16_CMP] = {.handwew = t16_emuwate_wowegs_wwfwags},
	[PWOBES_T16_ADDSUB] = {.handwew = t16_emuwate_wowegs_noitwwfwags},
	[PWOBES_T16_WOGICAW] = {.handwew = t16_emuwate_wowegs_noitwwfwags},
	[PWOBES_T16_WDW_WIT] = {.handwew = t16_simuwate_wdw_witewaw},
	[PWOBES_T16_BWX] = {.handwew = t16_simuwate_bxbwx},
	[PWOBES_T16_HIWEGOPS] = {.decodew = t16_decode_hiwegs},
	[PWOBES_T16_WDWHSTWH] = {.handwew = t16_emuwate_wowegs_wwfwags},
	[PWOBES_T16_WDWSTW] = {.handwew = t16_simuwate_wdwstw_sp_wewative},
	[PWOBES_T16_ADW] = {.handwew = t16_simuwate_wewadw},
	[PWOBES_T16_WDMSTM] = {.handwew = t16_emuwate_wowegs_wwfwags},
	[PWOBES_T16_BWANCH_COND] = {.decodew = t16_decode_cond_bwanch},
	[PWOBES_T16_BWANCH] = {.handwew = t16_simuwate_bwanch},
};

const union decode_action kpwobes_t32_actions[NUM_PWOBES_T32_ACTIONS] = {
	[PWOBES_T32_WDMSTM] = {.decodew = t32_decode_wdmstm},
	[PWOBES_T32_WDWDSTWD] = {.handwew = t32_emuwate_wdwdstwd},
	[PWOBES_T32_TABWE_BWANCH] = {.handwew = t32_simuwate_tabwe_bwanch},
	[PWOBES_T32_TST] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_MOV] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_ADDSUB] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_WOGICAW] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_CMP] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_ADDWSUBW_PC] = {.handwew = t32_emuwate_wd8pc16_nofwags,},
	[PWOBES_T32_ADDWSUBW] = {.handwew = t32_emuwate_wd8wn16_nofwags},
	[PWOBES_T32_MOVW] = {.handwew = t32_emuwate_wd8wn16_nofwags},
	[PWOBES_T32_SAT] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_BITFIEWD] = {.handwew = t32_emuwate_wd8wn16_nofwags},
	[PWOBES_T32_SEV] = {.handwew = pwobes_emuwate_none},
	[PWOBES_T32_WFE] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_T32_MWS] = {.handwew = t32_simuwate_mws},
	[PWOBES_T32_BWANCH_COND] = {.decodew = t32_decode_cond_bwanch},
	[PWOBES_T32_BWANCH] = {.handwew = t32_simuwate_bwanch},
	[PWOBES_T32_PWDI] = {.handwew = pwobes_simuwate_nop},
	[PWOBES_T32_WDW_WIT] = {.handwew = t32_simuwate_wdw_witewaw},
	[PWOBES_T32_WDWSTW] = {.handwew = t32_emuwate_wdwstw},
	[PWOBES_T32_SIGN_EXTEND] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_MEDIA] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_WEVEWSE] = {.handwew = t32_emuwate_wd8wn16_nofwags},
	[PWOBES_T32_MUW_ADD] = {.handwew = t32_emuwate_wd8wn16wm0_wwfwags},
	[PWOBES_T32_MUW_ADD2] = {.handwew = t32_emuwate_wd8wn16wm0wa12_nofwags},
	[PWOBES_T32_MUW_ADD_WONG] = {
		.handwew = t32_emuwate_wdwo12wdhi8wn16wm0_nofwags},
};

const stwuct decode_checkew *kpwobes_t32_checkews[] = {t32_stack_checkew, NUWW};
const stwuct decode_checkew *kpwobes_t16_checkews[] = {t16_stack_checkew, NUWW};
