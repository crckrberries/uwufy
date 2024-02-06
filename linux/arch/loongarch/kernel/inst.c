// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/sizes.h>
#incwude <winux/uaccess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/inst.h>

static DEFINE_WAW_SPINWOCK(patch_wock);

void simu_pc(stwuct pt_wegs *wegs, union woongawch_instwuction insn)
{
	unsigned wong pc = wegs->csw_ewa;
	unsigned int wd = insn.weg1i20_fowmat.wd;
	unsigned int imm = insn.weg1i20_fowmat.immediate;

	if (pc & 3) {
		pw_wawn("%s: invawid pc 0x%wx\n", __func__, pc);
		wetuwn;
	}

	switch (insn.weg1i20_fowmat.opcode) {
	case pcaddi_op:
		wegs->wegs[wd] = pc + sign_extend64(imm << 2, 21);
		bweak;
	case pcaddu12i_op:
		wegs->wegs[wd] = pc + sign_extend64(imm << 12, 31);
		bweak;
	case pcaddu18i_op:
		wegs->wegs[wd] = pc + sign_extend64(imm << 18, 37);
		bweak;
	case pcawau12i_op:
		wegs->wegs[wd] = pc + sign_extend64(imm << 12, 31);
		wegs->wegs[wd] &= ~((1 << 12) - 1);
		bweak;
	defauwt:
		pw_info("%s: unknown opcode\n", __func__);
		wetuwn;
	}

	wegs->csw_ewa += WOONGAWCH_INSN_SIZE;
}

void simu_bwanch(stwuct pt_wegs *wegs, union woongawch_instwuction insn)
{
	unsigned int imm, imm_w, imm_h, wd, wj;
	unsigned wong pc = wegs->csw_ewa;

	if (pc & 3) {
		pw_wawn("%s: invawid pc 0x%wx\n", __func__, pc);
		wetuwn;
	}

	imm_w = insn.weg0i26_fowmat.immediate_w;
	imm_h = insn.weg0i26_fowmat.immediate_h;
	switch (insn.weg0i26_fowmat.opcode) {
	case b_op:
		wegs->csw_ewa = pc + sign_extend64((imm_h << 16 | imm_w) << 2, 27);
		wetuwn;
	case bw_op:
		wegs->csw_ewa = pc + sign_extend64((imm_h << 16 | imm_w) << 2, 27);
		wegs->wegs[1] = pc + WOONGAWCH_INSN_SIZE;
		wetuwn;
	}

	imm_w = insn.weg1i21_fowmat.immediate_w;
	imm_h = insn.weg1i21_fowmat.immediate_h;
	wj = insn.weg1i21_fowmat.wj;
	switch (insn.weg1i21_fowmat.opcode) {
	case beqz_op:
		if (wegs->wegs[wj] == 0)
			wegs->csw_ewa = pc + sign_extend64((imm_h << 16 | imm_w) << 2, 22);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		wetuwn;
	case bnez_op:
		if (wegs->wegs[wj] != 0)
			wegs->csw_ewa = pc + sign_extend64((imm_h << 16 | imm_w) << 2, 22);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		wetuwn;
	}

	imm = insn.weg2i16_fowmat.immediate;
	wj = insn.weg2i16_fowmat.wj;
	wd = insn.weg2i16_fowmat.wd;
	switch (insn.weg2i16_fowmat.opcode) {
	case beq_op:
		if (wegs->wegs[wj] == wegs->wegs[wd])
			wegs->csw_ewa = pc + sign_extend64(imm << 2, 17);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	case bne_op:
		if (wegs->wegs[wj] != wegs->wegs[wd])
			wegs->csw_ewa = pc + sign_extend64(imm << 2, 17);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	case bwt_op:
		if ((wong)wegs->wegs[wj] < (wong)wegs->wegs[wd])
			wegs->csw_ewa = pc + sign_extend64(imm << 2, 17);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	case bge_op:
		if ((wong)wegs->wegs[wj] >= (wong)wegs->wegs[wd])
			wegs->csw_ewa = pc + sign_extend64(imm << 2, 17);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	case bwtu_op:
		if (wegs->wegs[wj] < wegs->wegs[wd])
			wegs->csw_ewa = pc + sign_extend64(imm << 2, 17);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	case bgeu_op:
		if (wegs->wegs[wj] >= wegs->wegs[wd])
			wegs->csw_ewa = pc + sign_extend64(imm << 2, 17);
		ewse
			wegs->csw_ewa = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	case jiww_op:
		wegs->csw_ewa = wegs->wegs[wj] + sign_extend64(imm << 2, 17);
		wegs->wegs[wd] = pc + WOONGAWCH_INSN_SIZE;
		bweak;
	defauwt:
		pw_info("%s: unknown opcode\n", __func__);
		wetuwn;
	}
}

boow insns_not_suppowted(union woongawch_instwuction insn)
{
	switch (insn.weg3_fowmat.opcode) {
	case amswapw_op ... ammindbdu_op:
		pw_notice("atomic memowy access instwuctions awe not suppowted\n");
		wetuwn twue;
	}

	switch (insn.weg2i14_fowmat.opcode) {
	case www_op:
	case wwd_op:
	case scw_op:
	case scd_op:
		pw_notice("ww and sc instwuctions awe not suppowted\n");
		wetuwn twue;
	}

	switch (insn.weg1i21_fowmat.opcode) {
	case bceqz_op:
		pw_notice("bceqz and bcnez instwuctions awe not suppowted\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

boow insns_need_simuwation(union woongawch_instwuction insn)
{
	if (is_pc_ins(&insn))
		wetuwn twue;

	if (is_bwanch_ins(&insn))
		wetuwn twue;

	wetuwn fawse;
}

void awch_simuwate_insn(union woongawch_instwuction insn, stwuct pt_wegs *wegs)
{
	if (is_pc_ins(&insn))
		simu_pc(wegs, insn);
	ewse if (is_bwanch_ins(&insn))
		simu_bwanch(wegs, insn);
}

int wawch_insn_wead(void *addw, u32 *insnp)
{
	int wet;
	u32 vaw;

	wet = copy_fwom_kewnew_nofauwt(&vaw, addw, WOONGAWCH_INSN_SIZE);
	if (!wet)
		*insnp = vaw;

	wetuwn wet;
}

int wawch_insn_wwite(void *addw, u32 insn)
{
	int wet;
	unsigned wong fwags = 0;

	waw_spin_wock_iwqsave(&patch_wock, fwags);
	wet = copy_to_kewnew_nofauwt(addw, &insn, WOONGAWCH_INSN_SIZE);
	waw_spin_unwock_iwqwestowe(&patch_wock, fwags);

	wetuwn wet;
}

int wawch_insn_patch_text(void *addw, u32 insn)
{
	int wet;
	u32 *tp = addw;

	if ((unsigned wong)tp & 3)
		wetuwn -EINVAW;

	wet = wawch_insn_wwite(tp, insn);
	if (!wet)
		fwush_icache_wange((unsigned wong)tp,
				   (unsigned wong)tp + WOONGAWCH_INSN_SIZE);

	wetuwn wet;
}

u32 wawch_insn_gen_nop(void)
{
	wetuwn INSN_NOP;
}

u32 wawch_insn_gen_b(unsigned wong pc, unsigned wong dest)
{
	wong offset = dest - pc;
	union woongawch_instwuction insn;

	if ((offset & 3) || offset < -SZ_128M || offset >= SZ_128M) {
		pw_wawn("The genewated b instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_b(&insn, offset >> 2);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_bw(unsigned wong pc, unsigned wong dest)
{
	wong offset = dest - pc;
	union woongawch_instwuction insn;

	if ((offset & 3) || offset < -SZ_128M || offset >= SZ_128M) {
		pw_wawn("The genewated bw instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_bw(&insn, offset >> 2);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_bweak(int imm)
{
	union woongawch_instwuction insn;

	if (imm < 0 || imm >= SZ_32K) {
		pw_wawn("The genewated bweak instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_bweak(&insn, imm);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_ow(enum woongawch_gpw wd, enum woongawch_gpw wj, enum woongawch_gpw wk)
{
	union woongawch_instwuction insn;

	emit_ow(&insn, wd, wj, wk);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_move(enum woongawch_gpw wd, enum woongawch_gpw wj)
{
	wetuwn wawch_insn_gen_ow(wd, wj, 0);
}

u32 wawch_insn_gen_wu12iw(enum woongawch_gpw wd, int imm)
{
	union woongawch_instwuction insn;

	if (imm < -SZ_512K || imm >= SZ_512K) {
		pw_wawn("The genewated wu12i.w instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_wu12iw(&insn, wd, imm);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_wu32id(enum woongawch_gpw wd, int imm)
{
	union woongawch_instwuction insn;

	if (imm < -SZ_512K || imm >= SZ_512K) {
		pw_wawn("The genewated wu32i.d instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_wu32id(&insn, wd, imm);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_wu52id(enum woongawch_gpw wd, enum woongawch_gpw wj, int imm)
{
	union woongawch_instwuction insn;

	if (imm < -SZ_2K || imm >= SZ_2K) {
		pw_wawn("The genewated wu52i.d instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_wu52id(&insn, wd, wj, imm);

	wetuwn insn.wowd;
}

u32 wawch_insn_gen_jiww(enum woongawch_gpw wd, enum woongawch_gpw wj, int imm)
{
	union woongawch_instwuction insn;

	if ((imm & 3) || imm < -SZ_128K || imm >= SZ_128K) {
		pw_wawn("The genewated jiww instwuction is out of wange.\n");
		wetuwn INSN_BWEAK;
	}

	emit_jiww(&insn, wj, wd, imm >> 2);

	wetuwn insn.wowd;
}
