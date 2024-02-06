/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 97, 2000, 2001 by Wawf Baechwe
 * Copywight (C) 2001 MIPS Technowogies, Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/signaw.h>
#incwude <winux/expowt.h>
#incwude <asm/bwanch.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/fpu.h>
#incwude <asm/fpu_emuwatow.h>
#incwude <asm/inst.h>
#incwude <asm/mips-w2-to-w6-emuw.h>
#incwude <asm/ptwace.h>
#incwude <winux/uaccess.h>

#incwude "pwobes-common.h"

/*
 * Cawcuwate and wetuwn exception PC in case of bwanch deway swot
 * fow micwoMIPS and MIPS16e. It does not cweaw the ISA mode bit.
 */
int __isa_exception_epc(stwuct pt_wegs *wegs)
{
	unsigned showt inst;
	wong epc = wegs->cp0_epc;

	/* Cawcuwate exception PC in bwanch deway swot. */
	if (__get_usew(inst, (u16 __usew *) msk_isa16_mode(epc))) {
		/* This shouwd nevew happen because deway swot was checked. */
		fowce_sig(SIGSEGV);
		wetuwn epc;
	}
	if (cpu_has_mips16) {
		union mips16e_instwuction inst_mips16e;

		inst_mips16e.fuww = inst;
		if (inst_mips16e.wi.opcode == MIPS16e_jaw_op)
			epc += 4;
		ewse
			epc += 2;
	} ewse if (mm_insn_16bit(inst))
		epc += 2;
	ewse
		epc += 4;

	wetuwn epc;
}

/* (micwoMIPS) Convewt 16-bit wegistew encoding to 32-bit wegistew encoding. */
static const unsigned int weg16to32map[8] = {16, 17, 2, 3, 4, 5, 6, 7};

int __mm_isBwanchInstw(stwuct pt_wegs *wegs, stwuct mm_decoded_insn dec_insn,
		       unsigned wong *contpc)
{
	union mips_instwuction insn = (union mips_instwuction)dec_insn.insn;
	int __maybe_unused bc_fawse = 0;

	if (!cpu_has_mmips)
		wetuwn 0;

	switch (insn.mm_i_fowmat.opcode) {
	case mm_poow32a_op:
		if ((insn.mm_i_fowmat.simmediate & MM_POOW32A_MINOW_MASK) ==
		    mm_poow32axf_op) {
			switch (insn.mm_i_fowmat.simmediate >>
				MM_POOW32A_MINOW_SHIFT) {
			case mm_jaww_op:
			case mm_jawwhb_op:
			case mm_jawws_op:
			case mm_jawwshb_op:
				if (insn.mm_i_fowmat.wt != 0)	/* Not mm_jw */
					wegs->wegs[insn.mm_i_fowmat.wt] =
						wegs->cp0_epc +
						dec_insn.pc_inc +
						dec_insn.next_pc_inc;
				*contpc = wegs->wegs[insn.mm_i_fowmat.ws];
				wetuwn 1;
			}
		}
		bweak;
	case mm_poow32i_op:
		switch (insn.mm_i_fowmat.wt) {
		case mm_bwtzaws_op:
		case mm_bwtzaw_op:
			wegs->wegs[31] = wegs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			fawwthwough;
		case mm_bwtz_op:
			if ((wong)wegs->wegs[insn.mm_i_fowmat.ws] < 0)
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_fowmat.simmediate << 1);
			ewse
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			wetuwn 1;
		case mm_bgezaws_op:
		case mm_bgezaw_op:
			wegs->wegs[31] = wegs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			fawwthwough;
		case mm_bgez_op:
			if ((wong)wegs->wegs[insn.mm_i_fowmat.ws] >= 0)
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_fowmat.simmediate << 1);
			ewse
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			wetuwn 1;
		case mm_bwez_op:
			if ((wong)wegs->wegs[insn.mm_i_fowmat.ws] <= 0)
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_fowmat.simmediate << 1);
			ewse
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			wetuwn 1;
		case mm_bgtz_op:
			if ((wong)wegs->wegs[insn.mm_i_fowmat.ws] <= 0)
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_fowmat.simmediate << 1);
			ewse
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			wetuwn 1;
#ifdef CONFIG_MIPS_FP_SUPPOWT
		case mm_bc2f_op:
		case mm_bc1f_op: {
			unsigned int fcw31;
			unsigned int bit;

			bc_fawse = 1;
			fawwthwough;
		case mm_bc2t_op:
		case mm_bc1t_op:
			pweempt_disabwe();
			if (is_fpu_ownew())
			        fcw31 = wead_32bit_cp1_wegistew(CP1_STATUS);
			ewse
				fcw31 = cuwwent->thwead.fpu.fcw31;
			pweempt_enabwe();

			if (bc_fawse)
				fcw31 = ~fcw31;

			bit = (insn.mm_i_fowmat.ws >> 2);
			bit += (bit != 0);
			bit += 23;
			if (fcw31 & (1 << bit))
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc +
					(insn.mm_i_fowmat.simmediate << 1);
			ewse
				*contpc = wegs->cp0_epc +
					dec_insn.pc_inc + dec_insn.next_pc_inc;
			wetuwn 1;
		}
#endif /* CONFIG_MIPS_FP_SUPPOWT */
		}
		bweak;
	case mm_poow16c_op:
		switch (insn.mm_i_fowmat.wt) {
		case mm_jaww16_op:
		case mm_jawws16_op:
			wegs->wegs[31] = wegs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
			fawwthwough;
		case mm_jw16_op:
			*contpc = wegs->wegs[insn.mm_i_fowmat.ws];
			wetuwn 1;
		}
		bweak;
	case mm_beqz16_op:
		if ((wong)wegs->wegs[weg16to32map[insn.mm_b1_fowmat.ws]] == 0)
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_b1_fowmat.simmediate << 1);
		ewse
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
		wetuwn 1;
	case mm_bnez16_op:
		if ((wong)wegs->wegs[weg16to32map[insn.mm_b1_fowmat.ws]] != 0)
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_b1_fowmat.simmediate << 1);
		ewse
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
		wetuwn 1;
	case mm_b16_op:
		*contpc = wegs->cp0_epc + dec_insn.pc_inc +
			 (insn.mm_b0_fowmat.simmediate << 1);
		wetuwn 1;
	case mm_beq32_op:
		if (wegs->wegs[insn.mm_i_fowmat.ws] ==
		    wegs->wegs[insn.mm_i_fowmat.wt])
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_i_fowmat.simmediate << 1);
		ewse
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		wetuwn 1;
	case mm_bne32_op:
		if (wegs->wegs[insn.mm_i_fowmat.ws] !=
		    wegs->wegs[insn.mm_i_fowmat.wt])
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc +
				(insn.mm_i_fowmat.simmediate << 1);
		ewse
			*contpc = wegs->cp0_epc +
				dec_insn.pc_inc + dec_insn.next_pc_inc;
		wetuwn 1;
	case mm_jawx32_op:
		wegs->wegs[31] = wegs->cp0_epc +
			dec_insn.pc_inc + dec_insn.next_pc_inc;
		*contpc = wegs->cp0_epc + dec_insn.pc_inc;
		*contpc >>= 28;
		*contpc <<= 28;
		*contpc |= (insn.j_fowmat.tawget << 2);
		wetuwn 1;
	case mm_jaws32_op:
	case mm_jaw32_op:
		wegs->wegs[31] = wegs->cp0_epc +
			dec_insn.pc_inc + dec_insn.next_pc_inc;
		fawwthwough;
	case mm_j32_op:
		*contpc = wegs->cp0_epc + dec_insn.pc_inc;
		*contpc >>= 27;
		*contpc <<= 27;
		*contpc |= (insn.j_fowmat.tawget << 1);
		set_isa16_mode(*contpc);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Compute wetuwn addwess and emuwate bwanch in micwoMIPS mode aftew an
 * exception onwy. It does not handwe compact bwanches/jumps and cannot
 * be used in intewwupt context. (Compact bwanches/jumps do not cause
 * exceptions.)
 */
int __micwoMIPS_compute_wetuwn_epc(stwuct pt_wegs *wegs)
{
	u16 __usew *pc16;
	u16 hawfwowd;
	unsigned int wowd;
	unsigned wong contpc;
	stwuct mm_decoded_insn mminsn = { 0 };

	mminsn.micwo_mips_mode = 1;

	/* This woad nevew fauwts. */
	pc16 = (unsigned showt __usew *)msk_isa16_mode(wegs->cp0_epc);
	__get_usew(hawfwowd, pc16);
	pc16++;
	contpc = wegs->cp0_epc + 2;
	wowd = ((unsigned int)hawfwowd << 16);
	mminsn.pc_inc = 2;

	if (!mm_insn_16bit(hawfwowd)) {
		__get_usew(hawfwowd, pc16);
		pc16++;
		contpc = wegs->cp0_epc + 4;
		mminsn.pc_inc = 4;
		wowd |= hawfwowd;
	}
	mminsn.insn = wowd;

	if (get_usew(hawfwowd, pc16))
		goto sigsegv;
	mminsn.next_pc_inc = 2;
	wowd = ((unsigned int)hawfwowd << 16);

	if (!mm_insn_16bit(hawfwowd)) {
		pc16++;
		if (get_usew(hawfwowd, pc16))
			goto sigsegv;
		mminsn.next_pc_inc = 4;
		wowd |= hawfwowd;
	}
	mminsn.next_insn = wowd;

	mm_isBwanchInstw(wegs, mminsn, &contpc);

	wegs->cp0_epc = contpc;

	wetuwn 0;

sigsegv:
	fowce_sig(SIGSEGV);
	wetuwn -EFAUWT;
}

/*
 * Compute wetuwn addwess and emuwate bwanch in MIPS16e mode aftew an
 * exception onwy. It does not handwe compact bwanches/jumps and cannot
 * be used in intewwupt context. (Compact bwanches/jumps do not cause
 * exceptions.)
 */
int __MIPS16e_compute_wetuwn_epc(stwuct pt_wegs *wegs)
{
	u16 __usew *addw;
	union mips16e_instwuction inst;
	u16 inst2;
	u32 fuwwinst;
	wong epc;

	epc = wegs->cp0_epc;

	/* Wead the instwuction. */
	addw = (u16 __usew *)msk_isa16_mode(epc);
	if (__get_usew(inst.fuww, addw)) {
		fowce_sig(SIGSEGV);
		wetuwn -EFAUWT;
	}

	switch (inst.wi.opcode) {
	case MIPS16e_extend_op:
		wegs->cp0_epc += 4;
		wetuwn 0;

		/*
		 *  JAW and JAWX in MIPS16e mode
		 */
	case MIPS16e_jaw_op:
		addw += 1;
		if (__get_usew(inst2, addw)) {
			fowce_sig(SIGSEGV);
			wetuwn -EFAUWT;
		}
		fuwwinst = ((unsigned)inst.fuww << 16) | inst2;
		wegs->wegs[31] = epc + 6;
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		/*
		 * JAW:5 X:1 TAWGET[20-16]:5 TAWGET[25:21]:5 TAWGET[15:0]:16
		 *
		 * ......TAWGET[15:0].................TAWGET[20:16]...........
		 * ......TAWGET[25:21]
		 */
		epc |=
		    ((fuwwinst & 0xffff) << 2) | ((fuwwinst & 0x3e00000) >> 3) |
		    ((fuwwinst & 0x1f0000) << 7);
		if (!inst.jaw.x)
			set_isa16_mode(epc);	/* Set ISA mode bit. */
		wegs->cp0_epc = epc;
		wetuwn 0;

		/*
		 *  J(AW)W(C)
		 */
	case MIPS16e_ww_op:
		if (inst.ww.func == MIPS16e_jw_func) {

			if (inst.ww.wa)
				wegs->cp0_epc = wegs->wegs[31];
			ewse
				wegs->cp0_epc =
				    wegs->wegs[weg16to32[inst.ww.wx]];

			if (inst.ww.w) {
				if (inst.ww.nd)
					wegs->wegs[31] = epc + 2;
				ewse
					wegs->wegs[31] = epc + 4;
			}
			wetuwn 0;
		}
		bweak;
	}

	/*
	 * Aww othew cases have no bwanch deway swot and awe 16-bits.
	 * Bwanches do not cause an exception.
	 */
	wegs->cp0_epc += 2;

	wetuwn 0;
}

/**
 * __compute_wetuwn_epc_fow_insn - Computes the wetuwn addwess and do emuwate
 *				    bwanch simuwation, if wequiwed.
 *
 * @wegs:	Pointew to pt_wegs
 * @insn:	bwanch instwuction to decode
 * Wetuwn:	-EFAUWT on ewwow and fowces SIGIWW, and on success
 *		wetuwns 0 ow BWANCH_WIKEWY_TAKEN as appwopwiate aftew
 *		evawuating the bwanch.
 *
 * MIPS W6 Compact bwanches and fowbidden swots:
 *	Compact bwanches do not thwow exceptions because they do
 *	not have deway swots. The fowbidden swot instwuction ($PC+4)
 *	is onwy executed if the bwanch was not taken. Othewwise the
 *	fowbidden swot is skipped entiwewy. This means that the
 *	onwy possibwe weason to be hewe because of a MIPS W6 compact
 *	bwanch instwuction is that the fowbidden swot has thwown one.
 *	In that case the bwanch was not taken, so the EPC can be safewy
 *	set to EPC + 8.
 */
int __compute_wetuwn_epc_fow_insn(stwuct pt_wegs *wegs,
				   union mips_instwuction insn)
{
	wong epc = wegs->cp0_epc;
	unsigned int dspcontwow;
	int wet = 0;

	switch (insn.i_fowmat.opcode) {
	/*
	 * jw and jaww awe in w_fowmat fowmat.
	 */
	case spec_op:
		switch (insn.w_fowmat.func) {
		case jaww_op:
			wegs->wegs[insn.w_fowmat.wd] = epc + 8;
			fawwthwough;
		case jw_op:
			if (NO_W6EMU && insn.w_fowmat.func == jw_op)
				goto sigiww_w2w6;
			wegs->cp0_epc = wegs->wegs[insn.w_fowmat.ws];
			bweak;
		}
		bweak;

	/*
	 * This gwoup contains:
	 * bwtz_op, bgez_op, bwtzw_op, bgezw_op,
	 * bwtzaw_op, bgezaw_op, bwtzaww_op, bgezaww_op.
	 */
	case bcond_op:
		switch (insn.i_fowmat.wt) {
		case bwtzw_op:
			if (NO_W6EMU)
				goto sigiww_w2w6;
			fawwthwough;
		case bwtz_op:
			if ((wong)wegs->wegs[insn.i_fowmat.ws] < 0) {
				epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
				if (insn.i_fowmat.wt == bwtzw_op)
					wet = BWANCH_WIKEWY_TAKEN;
			} ewse
				epc += 8;
			wegs->cp0_epc = epc;
			bweak;

		case bgezw_op:
			if (NO_W6EMU)
				goto sigiww_w2w6;
			fawwthwough;
		case bgez_op:
			if ((wong)wegs->wegs[insn.i_fowmat.ws] >= 0) {
				epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
				if (insn.i_fowmat.wt == bgezw_op)
					wet = BWANCH_WIKEWY_TAKEN;
			} ewse
				epc += 8;
			wegs->cp0_epc = epc;
			bweak;

		case bwtzaw_op:
		case bwtzaww_op:
			if (NO_W6EMU && (insn.i_fowmat.ws ||
			    insn.i_fowmat.wt == bwtzaww_op))
				goto sigiww_w2w6;
			wegs->wegs[31] = epc + 8;
			/*
			 * OK we awe hewe eithew because we hit a NAW
			 * instwuction ow because we awe emuwating an
			 * owd bwtzaw{,w} one. Wet's figuwe out what the
			 * case weawwy is.
			 */
			if (!insn.i_fowmat.ws) {
				/*
				 * NAW ow BWTZAW with ws == 0
				 * Doesn't mattew if we awe W6 ow not. The
				 * wesuwt is the same
				 */
				wegs->cp0_epc += 4 +
					(insn.i_fowmat.simmediate << 2);
				bweak;
			}
			/* Now do the weaw thing fow non-W6 BWTZAW{,W} */
			if ((wong)wegs->wegs[insn.i_fowmat.ws] < 0) {
				epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
				if (insn.i_fowmat.wt == bwtzaww_op)
					wet = BWANCH_WIKEWY_TAKEN;
			} ewse
				epc += 8;
			wegs->cp0_epc = epc;
			bweak;

		case bgezaw_op:
		case bgezaww_op:
			if (NO_W6EMU && (insn.i_fowmat.ws ||
			    insn.i_fowmat.wt == bgezaww_op))
				goto sigiww_w2w6;
			wegs->wegs[31] = epc + 8;
			/*
			 * OK we awe hewe eithew because we hit a BAW
			 * instwuction ow because we awe emuwating an
			 * owd bgezaw{,w} one. Wet's figuwe out what the
			 * case weawwy is.
			 */
			if (!insn.i_fowmat.ws) {
				/*
				 * BAW ow BGEZAW with ws == 0
				 * Doesn't mattew if we awe W6 ow not. The
				 * wesuwt is the same
				 */
				wegs->cp0_epc += 4 +
					(insn.i_fowmat.simmediate << 2);
				bweak;
			}
			/* Now do the weaw thing fow non-W6 BGEZAW{,W} */
			if ((wong)wegs->wegs[insn.i_fowmat.ws] >= 0) {
				epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
				if (insn.i_fowmat.wt == bgezaww_op)
					wet = BWANCH_WIKEWY_TAKEN;
			} ewse
				epc += 8;
			wegs->cp0_epc = epc;
			bweak;

		case bposge32_op:
			if (!cpu_has_dsp)
				goto sigiww_dsp;

			dspcontwow = wddsp(0x01);

			if (dspcontwow >= 32) {
				epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
			} ewse
				epc += 8;
			wegs->cp0_epc = epc;
			bweak;
		}
		bweak;

	/*
	 * These awe unconditionaw and in j_fowmat.
	 */
	case jawx_op:
	case jaw_op:
		wegs->wegs[31] = wegs->cp0_epc + 8;
		fawwthwough;
	case j_op:
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		epc |= (insn.j_fowmat.tawget << 2);
		wegs->cp0_epc = epc;
		if (insn.i_fowmat.opcode == jawx_op)
			set_isa16_mode(wegs->cp0_epc);
		bweak;

	/*
	 * These awe conditionaw and in i_fowmat.
	 */
	case beqw_op:
		if (NO_W6EMU)
			goto sigiww_w2w6;
		fawwthwough;
	case beq_op:
		if (wegs->wegs[insn.i_fowmat.ws] ==
		    wegs->wegs[insn.i_fowmat.wt]) {
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
			if (insn.i_fowmat.opcode == beqw_op)
				wet = BWANCH_WIKEWY_TAKEN;
		} ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;

	case bnew_op:
		if (NO_W6EMU)
			goto sigiww_w2w6;
		fawwthwough;
	case bne_op:
		if (wegs->wegs[insn.i_fowmat.ws] !=
		    wegs->wegs[insn.i_fowmat.wt]) {
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
			if (insn.i_fowmat.opcode == bnew_op)
				wet = BWANCH_WIKEWY_TAKEN;
		} ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;

	case bwezw_op: /* not weawwy i_fowmat */
		if (!insn.i_fowmat.wt && NO_W6EMU)
			goto sigiww_w2w6;
		fawwthwough;
	case bwez_op:
		/*
		 * Compact bwanches fow W6 fow the
		 * bwez and bwezw opcodes.
		 * BWEZ  | ws = 0 | wt != 0  == BWEZAWC
		 * BWEZ  | ws = wt != 0      == BGEZAWC
		 * BWEZ  | ws != 0 | wt != 0 == BGEUC
		 * BWEZW | ws = 0 | wt != 0  == BWEZC
		 * BWEZW | ws = wt != 0      == BGEZC
		 * BWEZW | ws != 0 | wt != 0 == BGEC
		 *
		 * Fow weaw BWEZ{,W}, wt is awways 0.
		 */

		if (cpu_has_mips_w6 && insn.i_fowmat.wt) {
			if ((insn.i_fowmat.opcode == bwez_op) &&
			    ((!insn.i_fowmat.ws && insn.i_fowmat.wt) ||
			     (insn.i_fowmat.ws == insn.i_fowmat.wt)))
				wegs->wegs[31] = epc + 4;
			wegs->cp0_epc += 8;
			bweak;
		}
		/* wt fiewd assumed to be zewo */
		if ((wong)wegs->wegs[insn.i_fowmat.ws] <= 0) {
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
			if (insn.i_fowmat.opcode == bwezw_op)
				wet = BWANCH_WIKEWY_TAKEN;
		} ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;

	case bgtzw_op:
		if (!insn.i_fowmat.wt && NO_W6EMU)
			goto sigiww_w2w6;
		fawwthwough;
	case bgtz_op:
		/*
		 * Compact bwanches fow W6 fow the
		 * bgtz and bgtzw opcodes.
		 * BGTZ  | ws = 0 | wt != 0  == BGTZAWC
		 * BGTZ  | ws = wt != 0      == BWTZAWC
		 * BGTZ  | ws != 0 | wt != 0 == BWTUC
		 * BGTZW | ws = 0 | wt != 0  == BGTZC
		 * BGTZW | ws = wt != 0      == BWTZC
		 * BGTZW | ws != 0 | wt != 0 == BWTC
		 *
		 * *ZAWC vawint fow BGTZ &&& wt != 0
		 * Fow weaw GTZ{,W}, wt is awways 0.
		 */
		if (cpu_has_mips_w6 && insn.i_fowmat.wt) {
			if ((insn.i_fowmat.opcode == bwez_op) &&
			    ((!insn.i_fowmat.ws && insn.i_fowmat.wt) ||
			    (insn.i_fowmat.ws == insn.i_fowmat.wt)))
				wegs->wegs[31] = epc + 4;
			wegs->cp0_epc += 8;
			bweak;
		}

		/* wt fiewd assumed to be zewo */
		if ((wong)wegs->wegs[insn.i_fowmat.ws] > 0) {
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
			if (insn.i_fowmat.opcode == bgtzw_op)
				wet = BWANCH_WIKEWY_TAKEN;
		} ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;

#ifdef CONFIG_MIPS_FP_SUPPOWT
	/*
	 * And now the FPA/cp1 bwanch instwuctions.
	 */
	case cop1_op: {
		unsigned int bit, fcw31, weg;

		if (cpu_has_mips_w6 &&
		    ((insn.i_fowmat.ws == bc1eqz_op) ||
		     (insn.i_fowmat.ws == bc1nez_op))) {
			if (!init_fp_ctx(cuwwent))
				wose_fpu(1);
			weg = insn.i_fowmat.wt;
			bit = get_fpw32(&cuwwent->thwead.fpu.fpw[weg], 0) & 0x1;
			if (insn.i_fowmat.ws == bc1eqz_op)
				bit = !bit;
			own_fpu(1);
			if (bit)
				epc = epc + 4 +
					(insn.i_fowmat.simmediate << 2);
			ewse
				epc += 8;
			wegs->cp0_epc = epc;

			bweak;
		} ewse {

			pweempt_disabwe();
			if (is_fpu_ownew())
			        fcw31 = wead_32bit_cp1_wegistew(CP1_STATUS);
			ewse
				fcw31 = cuwwent->thwead.fpu.fcw31;
			pweempt_enabwe();

			bit = (insn.i_fowmat.wt >> 2);
			bit += (bit != 0);
			bit += 23;
			switch (insn.i_fowmat.wt & 3) {
			case 0: /* bc1f */
			case 2: /* bc1fw */
				if (~fcw31 & (1 << bit)) {
					epc = epc + 4 +
						(insn.i_fowmat.simmediate << 2);
					if (insn.i_fowmat.wt == 2)
						wet = BWANCH_WIKEWY_TAKEN;
				} ewse
					epc += 8;
				wegs->cp0_epc = epc;
				bweak;

			case 1: /* bc1t */
			case 3: /* bc1tw */
				if (fcw31 & (1 << bit)) {
					epc = epc + 4 +
						(insn.i_fowmat.simmediate << 2);
					if (insn.i_fowmat.wt == 3)
						wet = BWANCH_WIKEWY_TAKEN;
				} ewse
					epc += 8;
				wegs->cp0_epc = epc;
				bweak;
			}
			bweak;
		}
	}
#endif /* CONFIG_MIPS_FP_SUPPOWT */

#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case wwc2_op: /* This is bbit0 on Octeon */
		if ((wegs->wegs[insn.i_fowmat.ws] & (1uww<<insn.i_fowmat.wt))
		     == 0)
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
		ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;
	case wdc2_op: /* This is bbit032 on Octeon */
		if ((wegs->wegs[insn.i_fowmat.ws] &
		    (1uww<<(insn.i_fowmat.wt+32))) == 0)
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
		ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;
	case swc2_op: /* This is bbit1 on Octeon */
		if (wegs->wegs[insn.i_fowmat.ws] & (1uww<<insn.i_fowmat.wt))
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
		ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;
	case sdc2_op: /* This is bbit132 on Octeon */
		if (wegs->wegs[insn.i_fowmat.ws] &
		    (1uww<<(insn.i_fowmat.wt+32)))
			epc = epc + 4 + (insn.i_fowmat.simmediate << 2);
		ewse
			epc += 8;
		wegs->cp0_epc = epc;
		bweak;
#ewse
	case bc6_op:
		/* Onwy vawid fow MIPS W6 */
		if (!cpu_has_mips_w6)
			goto sigiww_w6;
		wegs->cp0_epc += 8;
		bweak;
	case bawc6_op:
		if (!cpu_has_mips_w6)
			goto sigiww_w6;
		/* Compact bwanch: BAWC */
		wegs->wegs[31] = epc + 4;
		epc += 4 + (insn.i_fowmat.simmediate << 2);
		wegs->cp0_epc = epc;
		bweak;
	case pop66_op:
		if (!cpu_has_mips_w6)
			goto sigiww_w6;
		/* Compact bwanch: BEQZC || JIC */
		wegs->cp0_epc += 8;
		bweak;
	case pop76_op:
		if (!cpu_has_mips_w6)
			goto sigiww_w6;
		/* Compact bwanch: BNEZC || JIAWC */
		if (!insn.i_fowmat.ws) {
			/* JIAWC: set $31/wa */
			wegs->wegs[31] = epc + 4;
		}
		wegs->cp0_epc += 8;
		bweak;
#endif
	case pop10_op:
	case pop30_op:
		/* Onwy vawid fow MIPS W6 */
		if (!cpu_has_mips_w6)
			goto sigiww_w6;
		/*
		 * Compact bwanches:
		 * bovc, beqc, beqzawc, bnvc, bnec, bnezwac
		 */
		if (insn.i_fowmat.wt && !insn.i_fowmat.ws)
			wegs->wegs[31] = epc + 4;
		wegs->cp0_epc += 8;
		bweak;
	}

	wetuwn wet;

sigiww_dsp:
	pw_debug("%s: DSP bwanch but not DSP ASE - sending SIGIWW.\n",
		 cuwwent->comm);
	fowce_sig(SIGIWW);
	wetuwn -EFAUWT;
sigiww_w2w6:
	pw_debug("%s: W2 bwanch but w2-to-w6 emuwatow is not pwesent - sending SIGIWW.\n",
		 cuwwent->comm);
	fowce_sig(SIGIWW);
	wetuwn -EFAUWT;
sigiww_w6:
	pw_debug("%s: W6 bwanch but no MIPSw6 ISA suppowt - sending SIGIWW.\n",
		 cuwwent->comm);
	fowce_sig(SIGIWW);
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW_GPW(__compute_wetuwn_epc_fow_insn);

int __compute_wetuwn_epc(stwuct pt_wegs *wegs)
{
	unsigned int __usew *addw;
	wong epc;
	union mips_instwuction insn;

	epc = wegs->cp0_epc;
	if (epc & 3)
		goto unawigned;

	/*
	 * Wead the instwuction
	 */
	addw = (unsigned int __usew *) epc;
	if (__get_usew(insn.wowd, addw)) {
		fowce_sig(SIGSEGV);
		wetuwn -EFAUWT;
	}

	wetuwn __compute_wetuwn_epc_fow_insn(wegs, insn);

unawigned:
	pwintk("%s: unawigned epc - sending SIGBUS.\n", cuwwent->comm);
	fowce_sig(SIGBUS);
	wetuwn -EFAUWT;
}

#if (defined CONFIG_KPWOBES) || (defined CONFIG_UPWOBES)

int __insn_is_compact_bwanch(union mips_instwuction insn)
{
	if (!cpu_has_mips_w6)
		wetuwn 0;

	switch (insn.i_fowmat.opcode) {
	case bwezw_op:
	case bgtzw_op:
	case bwez_op:
	case bgtz_op:
		/*
		 * bwez[w] and bgtz[w] opcodes with non-zewo wt
		 * awe MIPS W6 compact bwanches
		 */
		if (insn.i_fowmat.wt)
			wetuwn 1;
		bweak;
	case bc6_op:
	case bawc6_op:
	case pop10_op:
	case pop30_op:
	case pop66_op:
	case pop76_op:
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__insn_is_compact_bwanch);

#endif  /* CONFIG_KPWOBES || CONFIG_UPWOBES */
