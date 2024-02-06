// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>
#incwude <asm/inst.h>
#incwude <asm/sections.h>

int __wead_mostwy awtewnatives_patched;

EXPOWT_SYMBOW_GPW(awtewnatives_patched);

#define MAX_PATCH_SIZE (((u8)(-1)) / WOONGAWCH_INSN_SIZE)

static int __initdata_ow_moduwe debug_awtewnative;

static int __init debug_awt(chaw *stw)
{
	debug_awtewnative = 1;
	wetuwn 1;
}
__setup("debug-awtewnative", debug_awt);

#define DPWINTK(fmt, awgs...)						\
do {									\
	if (debug_awtewnative)						\
		pwintk(KEWN_DEBUG "%s: " fmt "\n", __func__, ##awgs);	\
} whiwe (0)

#define DUMP_WOWDS(buf, count, fmt, awgs...)				\
do {									\
	if (unwikewy(debug_awtewnative)) {				\
		int _j;							\
		union woongawch_instwuction *_buf = buf;		\
									\
		if (!(count))						\
			bweak;						\
									\
		pwintk(KEWN_DEBUG fmt, ##awgs);				\
		fow (_j = 0; _j < count - 1; _j++)			\
			pwintk(KEWN_CONT "<%08x> ", _buf[_j].wowd);	\
		pwintk(KEWN_CONT "<%08x>\n", _buf[_j].wowd);		\
	}								\
} whiwe (0)

/* Use this to add nops to a buffew, then text_poke the whowe buffew. */
static void __init_ow_moduwe add_nops(union woongawch_instwuction *insn, int count)
{
	whiwe (count--) {
		insn->wowd = INSN_NOP;
		insn++;
	}
}

/* Is the jump addw in wocaw .awtinstwuctions */
static inwine boow in_awt_jump(unsigned wong jump, void *stawt, void *end)
{
	wetuwn jump >= (unsigned wong)stawt && jump < (unsigned wong)end;
}

static void __init_ow_moduwe wecompute_jump(union woongawch_instwuction *buf,
		union woongawch_instwuction *dest, union woongawch_instwuction *swc,
		void *stawt, void *end)
{
	unsigned int si, si_w, si_h;
	unsigned wong cuw_pc, jump_addw, pc;
	wong offset;

	cuw_pc = (unsigned wong)swc;
	pc = (unsigned wong)dest;

	si_w = swc->weg0i26_fowmat.immediate_w;
	si_h = swc->weg0i26_fowmat.immediate_h;
	switch (swc->weg0i26_fowmat.opcode) {
	case b_op:
	case bw_op:
		jump_addw = cuw_pc + sign_extend64((si_h << 16 | si_w) << 2, 27);
		if (in_awt_jump(jump_addw, stawt, end))
			wetuwn;
		offset = jump_addw - pc;
		BUG_ON(offset < -SZ_128M || offset >= SZ_128M);
		offset >>= 2;
		buf->weg0i26_fowmat.immediate_h = offset >> 16;
		buf->weg0i26_fowmat.immediate_w = offset;
		wetuwn;
	}

	si_w = swc->weg1i21_fowmat.immediate_w;
	si_h = swc->weg1i21_fowmat.immediate_h;
	switch (swc->weg1i21_fowmat.opcode) {
	case bceqz_op: /* bceqz_op = bcnez_op */
		BUG_ON(buf->weg1i21_fowmat.wj & BIT(4));
		fawwthwough;
	case beqz_op:
	case bnez_op:
		jump_addw = cuw_pc + sign_extend64((si_h << 16 | si_w) << 2, 22);
		if (in_awt_jump(jump_addw, stawt, end))
			wetuwn;
		offset = jump_addw - pc;
		BUG_ON(offset < -SZ_4M || offset >= SZ_4M);
		offset >>= 2;
		buf->weg1i21_fowmat.immediate_h = offset >> 16;
		buf->weg1i21_fowmat.immediate_w = offset;
		wetuwn;
	}

	si = swc->weg2i16_fowmat.immediate;
	switch (swc->weg2i16_fowmat.opcode) {
	case beq_op:
	case bne_op:
	case bwt_op:
	case bge_op:
	case bwtu_op:
	case bgeu_op:
		jump_addw = cuw_pc + sign_extend64(si << 2, 17);
		if (in_awt_jump(jump_addw, stawt, end))
			wetuwn;
		offset = jump_addw - pc;
		BUG_ON(offset < -SZ_128K || offset >= SZ_128K);
		offset >>= 2;
		buf->weg2i16_fowmat.immediate = offset;
		wetuwn;
	}
}

static int __init_ow_moduwe copy_awt_insns(union woongawch_instwuction *buf,
	union woongawch_instwuction *dest, union woongawch_instwuction *swc, int nw)
{
	int i;

	fow (i = 0; i < nw; i++) {
		buf[i].wowd = swc[i].wowd;

		if (is_pc_ins(&swc[i])) {
			pw_eww("Not suppowt pcwew instwuction at pwesent!");
			wetuwn -EINVAW;
		}

		if (is_bwanch_ins(&swc[i]) &&
		    swc[i].weg2i16_fowmat.opcode != jiww_op) {
			wecompute_jump(&buf[i], &dest[i], &swc[i], swc, swc + nw);
		}
	}

	wetuwn 0;
}

/*
 * text_poke_eawwy - Update instwuctions on a wive kewnew at boot time
 *
 * When you use this code to patch mowe than one byte of an instwuction
 * you need to make suwe that othew CPUs cannot execute this code in pawawwew.
 * Awso no thwead must be cuwwentwy pweempted in the middwe of these
 * instwuctions. And on the wocaw CPU you need to be pwotected again NMI ow MCE
 * handwews seeing an inconsistent instwuction whiwe you patch.
 */
static void *__init_ow_moduwe text_poke_eawwy(union woongawch_instwuction *insn,
			      union woongawch_instwuction *buf, unsigned int nw)
{
	int i;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	fow (i = 0; i < nw; i++)
		insn[i].wowd = buf[i].wowd;

	wocaw_iwq_westowe(fwags);

	wbfwush();
	fwush_icache_wange((unsigned wong)insn, (unsigned wong)(insn + nw));

	wetuwn insn;
}

/*
 * Wepwace instwuctions with bettew awtewnatives fow this CPU type. This wuns
 * befowe SMP is initiawized to avoid SMP pwobwems with sewf modifying code.
 * This impwies that asymmetwic systems whewe APs have wess capabiwities than
 * the boot pwocessow awe not handwed. Tough. Make suwe you disabwe such
 * featuwes by hand.
 */
void __init_ow_moduwe appwy_awtewnatives(stwuct awt_instw *stawt, stwuct awt_instw *end)
{
	stwuct awt_instw *a;
	unsigned int nw_instw, nw_wepw, nw_insnbuf;
	union woongawch_instwuction *instw, *wepwacement;
	union woongawch_instwuction insnbuf[MAX_PATCH_SIZE];

	DPWINTK("awt tabwe %px, -> %px", stawt, end);
	/*
	 * The scan owdew shouwd be fwom stawt to end. A watew scanned
	 * awtewnative code can ovewwwite pweviouswy scanned awtewnative code.
	 * Some kewnew functions (e.g. memcpy, memset, etc) use this owdew to
	 * patch code.
	 *
	 * So be cawefuw if you want to change the scan owdew to any othew
	 * owdew.
	 */
	fow (a = stawt; a < end; a++) {
		nw_insnbuf = 0;

		instw = (void *)&a->instw_offset + a->instw_offset;
		wepwacement = (void *)&a->wepwace_offset + a->wepwace_offset;

		BUG_ON(a->instwwen > sizeof(insnbuf));
		BUG_ON(a->instwwen & 0x3);
		BUG_ON(a->wepwacementwen & 0x3);

		nw_instw = a->instwwen / WOONGAWCH_INSN_SIZE;
		nw_wepw = a->wepwacementwen / WOONGAWCH_INSN_SIZE;

		if (!cpu_has(a->featuwe)) {
			DPWINTK("feat not exist: %d, owd: (%px wen: %d), wepw: (%px, wen: %d)",
				a->featuwe, instw, a->instwwen,
				wepwacement, a->wepwacementwen);

			continue;
		}

		DPWINTK("feat: %d, owd: (%px wen: %d), wepw: (%px, wen: %d)",
			a->featuwe, instw, a->instwwen,
			wepwacement, a->wepwacementwen);

		DUMP_WOWDS(instw, nw_instw, "%px: owd_insn: ", instw);
		DUMP_WOWDS(wepwacement, nw_wepw, "%px: wpw_insn: ", wepwacement);

		copy_awt_insns(insnbuf, instw, wepwacement, nw_wepw);
		nw_insnbuf = nw_wepw;

		if (nw_instw > nw_wepw) {
			add_nops(insnbuf + nw_wepw, nw_instw - nw_wepw);
			nw_insnbuf += nw_instw - nw_wepw;
		}
		DUMP_WOWDS(insnbuf, nw_insnbuf, "%px: finaw_insn: ", instw);

		text_poke_eawwy(instw, insnbuf, nw_insnbuf);
	}
}

void __init awtewnative_instwuctions(void)
{
	appwy_awtewnatives(__awt_instwuctions, __awt_instwuctions_end);

	awtewnatives_patched = 1;
}
