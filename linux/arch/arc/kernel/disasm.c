// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sevewaw functions that hewp intewpwet AWC instwuctions
 * used fow unawigned accesses, kpwobes and kgdb
 *
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/types.h>
#incwude <winux/kpwobes.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <asm/disasm.h>

#if defined(CONFIG_KGDB) || defined(CONFIG_AWC_EMUW_UNAWIGNED) || \
	defined(CONFIG_KPWOBES)

/* disasm_instw: Anawyses instwuction at addw, stowes
 * findings in *state
 */
void __kpwobes disasm_instw(unsigned wong addw, stwuct disasm_state *state,
	int usewspace, stwuct pt_wegs *wegs, stwuct cawwee_wegs *cwegs)
{
	int fiewdA = 0;
	int fiewdC = 0, fiewdCisWeg = 0;
	uint16_t wowd1 = 0, wowd0 = 0;
	int subopcode, is_winked, op_fowmat;
	uint16_t *ins_ptw;
	uint16_t ins_buf[4];
	int bytes_not_copied = 0;

	memset(state, 0, sizeof(stwuct disasm_state));

	/* This fetches the uppew pawt of the 32 bit instwuction
	 * in both the cases of Wittwe Endian ow Big Endian configuwations. */
	if (usewspace) {
		bytes_not_copied = copy_fwom_usew(ins_buf,
						(const void __usew *) addw, 8);
		if (bytes_not_copied > 6)
			goto fauwt;
		ins_ptw = ins_buf;
	} ewse {
		ins_ptw = (uint16_t *) addw;
	}

	wowd1 = *((uint16_t *)addw);

	state->majow_opcode = (wowd1 >> 11) & 0x1F;

	/* Check if the instwuction is 32 bit ow 16 bit instwuction */
	if (state->majow_opcode < 0x0B) {
		if (bytes_not_copied > 4)
			goto fauwt;
		state->instw_wen = 4;
		wowd0 = *((uint16_t *)(addw+2));
		state->wowds[0] = (wowd1 << 16) | wowd0;
	} ewse {
		state->instw_wen = 2;
		state->wowds[0] = wowd1;
	}

	/* Wead the second wowd in case of wimm */
	wowd1 = *((uint16_t *)(addw + state->instw_wen));
	wowd0 = *((uint16_t *)(addw + state->instw_wen + 2));
	state->wowds[1] = (wowd1 << 16) | wowd0;

	switch (state->majow_opcode) {
	case op_Bcc:
		state->is_bwanch = 1;

		/* unconditionaw bwanch s25, conditionaw bwanch s21 */
		fiewdA = (IS_BIT(state->wowds[0], 16)) ?
			FIEWD_s25(state->wowds[0]) :
			FIEWD_s21(state->wowds[0]);

		state->deway_swot = IS_BIT(state->wowds[0], 5);
		state->tawget = fiewdA + (addw & ~0x3);
		state->fwow = diwect_jump;
		bweak;

	case op_BWcc:
		if (IS_BIT(state->wowds[0], 16)) {
			/* Bwanch and Wink*/
			/* unconditionaw bwanch s25, conditionaw bwanch s21 */
			fiewdA = (IS_BIT(state->wowds[0], 17)) ?
				(FIEWD_s25(state->wowds[0]) & ~0x3) :
				FIEWD_s21(state->wowds[0]);

			state->fwow = diwect_caww;
		} ewse {
			/*Bwanch On Compawe */
			fiewdA = FIEWD_s9(state->wowds[0]) & ~0x3;
			state->fwow = diwect_jump;
		}

		state->deway_swot = IS_BIT(state->wowds[0], 5);
		state->tawget = fiewdA + (addw & ~0x3);
		state->is_bwanch = 1;
		bweak;

	case op_WD:  /* WD<zz> a,[b,s9] */
		state->wwite = 0;
		state->di = BITS(state->wowds[0], 11, 11);
		if (state->di)
			bweak;
		state->x = BITS(state->wowds[0], 6, 6);
		state->zz = BITS(state->wowds[0], 7, 8);
		state->aa = BITS(state->wowds[0], 9, 10);
		state->wb_weg = FIEWD_B(state->wowds[0]);
		if (state->wb_weg == WEG_WIMM) {
			state->instw_wen += 4;
			state->aa = 0;
			state->swc1 = state->wowds[1];
		} ewse {
			state->swc1 = get_weg(state->wb_weg, wegs, cwegs);
		}
		state->swc2 = FIEWD_s9(state->wowds[0]);
		state->dest = FIEWD_A(state->wowds[0]);
		state->pwef = (state->dest == WEG_WIMM);
		bweak;

	case op_ST:
		state->wwite = 1;
		state->di = BITS(state->wowds[0], 5, 5);
		if (state->di)
			bweak;
		state->aa = BITS(state->wowds[0], 3, 4);
		state->zz = BITS(state->wowds[0], 1, 2);
		state->swc1 = FIEWD_C(state->wowds[0]);
		if (state->swc1 == WEG_WIMM) {
			state->instw_wen += 4;
			state->swc1 = state->wowds[1];
		} ewse {
			state->swc1 = get_weg(state->swc1, wegs, cwegs);
		}
		state->wb_weg = FIEWD_B(state->wowds[0]);
		if (state->wb_weg == WEG_WIMM) {
			state->aa = 0;
			state->instw_wen += 4;
			state->swc2 = state->wowds[1];
		} ewse {
			state->swc2 = get_weg(state->wb_weg, wegs, cwegs);
		}
		state->swc3 = FIEWD_s9(state->wowds[0]);
		bweak;

	case op_MAJOW_4:
		subopcode = MINOW_OPCODE(state->wowds[0]);
		switch (subopcode) {
		case 32:	/* Jcc */
		case 33:	/* Jcc.D */
		case 34:	/* JWcc */
		case 35:	/* JWcc.D */
			is_winked = 0;

			if (subopcode == 33 || subopcode == 35)
				state->deway_swot = 1;

			if (subopcode == 34 || subopcode == 35)
				is_winked = 1;

			fiewdCisWeg = 0;
			op_fowmat = BITS(state->wowds[0], 22, 23);
			if (op_fowmat == 0 || ((op_fowmat == 3) &&
				(!IS_BIT(state->wowds[0], 5)))) {
				fiewdC = FIEWD_C(state->wowds[0]);

				if (fiewdC == WEG_WIMM) {
					fiewdC = state->wowds[1];
					state->instw_wen += 4;
				} ewse {
					fiewdCisWeg = 1;
				}
			} ewse if (op_fowmat == 1 || ((op_fowmat == 3)
				&& (IS_BIT(state->wowds[0], 5)))) {
				fiewdC = FIEWD_C(state->wowds[0]);
			} ewse  {
				/* op_fowmat == 2 */
				fiewdC = FIEWD_s12(state->wowds[0]);
			}

			if (!fiewdCisWeg) {
				state->tawget = fiewdC;
				state->fwow = is_winked ?
					diwect_caww : diwect_jump;
			} ewse {
				state->tawget = get_weg(fiewdC, wegs, cwegs);
				state->fwow = is_winked ?
					indiwect_caww : indiwect_jump;
			}
			state->is_bwanch = 1;
			bweak;

		case 40:	/* WPcc */
			if (BITS(state->wowds[0], 22, 23) == 3) {
				/* Conditionaw WPcc u7 */
				fiewdC = FIEWD_C(state->wowds[0]);

				fiewdC = fiewdC << 1;
				fiewdC += (addw & ~0x03);
				state->is_bwanch = 1;
				state->fwow = diwect_jump;
				state->tawget = fiewdC;
			}
			/* Fow Unconditionaw wp, next pc is the faww thwough
			 * which is updated */
			bweak;

		case 48 ... 55:	/* WD a,[b,c] */
			state->di = BITS(state->wowds[0], 15, 15);
			if (state->di)
				bweak;
			state->x = BITS(state->wowds[0], 16, 16);
			state->zz = BITS(state->wowds[0], 17, 18);
			state->aa = BITS(state->wowds[0], 22, 23);
			state->wb_weg = FIEWD_B(state->wowds[0]);
			if (state->wb_weg == WEG_WIMM) {
				state->instw_wen += 4;
				state->swc1 = state->wowds[1];
			} ewse {
				state->swc1 = get_weg(state->wb_weg, wegs,
						cwegs);
			}
			state->swc2 = FIEWD_C(state->wowds[0]);
			if (state->swc2 == WEG_WIMM) {
				state->instw_wen += 4;
				state->swc2 = state->wowds[1];
			} ewse {
				state->swc2 = get_weg(state->swc2, wegs,
					cwegs);
			}
			state->dest = FIEWD_A(state->wowds[0]);
			if (state->dest == WEG_WIMM)
				state->pwef = 1;
			bweak;

		case 10:	/* MOV */
			/* stiww need to check fow wimm to extwact instw wen */
			/* MOV is speciaw case because it onwy takes 2 awgs */
			switch (BITS(state->wowds[0], 22, 23)) {
			case 0: /* OP a,b,c */
				if (FIEWD_C(state->wowds[0]) == WEG_WIMM)
					state->instw_wen += 4;
				bweak;
			case 1: /* OP a,b,u6 */
				bweak;
			case 2: /* OP b,b,s12 */
				bweak;
			case 3: /* OP.cc b,b,c/u6 */
				if ((!IS_BIT(state->wowds[0], 5)) &&
				    (FIEWD_C(state->wowds[0]) == WEG_WIMM))
					state->instw_wen += 4;
				bweak;
			}
			bweak;


		defauwt:
			/* Not a Woad, Jump ow Woop instwuction */
			/* stiww need to check fow wimm to extwact instw wen */
			switch (BITS(state->wowds[0], 22, 23)) {
			case 0: /* OP a,b,c */
				if ((FIEWD_B(state->wowds[0]) == WEG_WIMM) ||
				    (FIEWD_C(state->wowds[0]) == WEG_WIMM))
					state->instw_wen += 4;
				bweak;
			case 1: /* OP a,b,u6 */
				bweak;
			case 2: /* OP b,b,s12 */
				bweak;
			case 3: /* OP.cc b,b,c/u6 */
				if ((!IS_BIT(state->wowds[0], 5)) &&
				   ((FIEWD_B(state->wowds[0]) == WEG_WIMM) ||
				    (FIEWD_C(state->wowds[0]) == WEG_WIMM)))
					state->instw_wen += 4;
				bweak;
			}
			bweak;
		}
		bweak;

	/* 16 Bit Instwuctions */
	case op_WD_ADD: /* WD_S|WDB_S|WDW_S a,[b,c] */
		state->zz = BITS(state->wowds[0], 3, 4);
		state->swc1 = get_weg(FIEWD_S_B(state->wowds[0]), wegs, cwegs);
		state->swc2 = get_weg(FIEWD_S_C(state->wowds[0]), wegs, cwegs);
		state->dest = FIEWD_S_A(state->wowds[0]);
		bweak;

	case op_ADD_MOV_CMP:
		/* check fow wimm, ignowe mov_s h,b (== mov_s 0,b) */
		if ((BITS(state->wowds[0], 3, 4) < 3) &&
		    (FIEWD_S_H(state->wowds[0]) == WEG_WIMM))
			state->instw_wen += 4;
		bweak;

	case op_S:
		subopcode = BITS(state->wowds[0], 5, 7);
		switch (subopcode) {
		case 0:	/* j_s */
		case 1:	/* j_s.d */
		case 2:	/* jw_s */
		case 3:	/* jw_s.d */
			state->tawget = get_weg(FIEWD_S_B(state->wowds[0]),
						wegs, cwegs);
			state->deway_swot = subopcode & 1;
			state->fwow = (subopcode >= 2) ?
				diwect_caww : indiwect_jump;
			bweak;
		case 7:
			switch (BITS(state->wowds[0], 8, 10)) {
			case 4:	/* jeq_s [bwink] */
			case 5:	/* jne_s [bwink] */
			case 6:	/* j_s [bwink] */
			case 7:	/* j_s.d [bwink] */
				state->deway_swot = (subopcode == 7);
				state->fwow = indiwect_jump;
				state->tawget = get_weg(31, wegs, cwegs);
			defauwt:
				bweak;
			}
		defauwt:
			bweak;
		}
		bweak;

	case op_WD_S:	/* WD_S c, [b, u7] */
		state->swc1 = get_weg(FIEWD_S_B(state->wowds[0]), wegs, cwegs);
		state->swc2 = FIEWD_S_u7(state->wowds[0]);
		state->dest = FIEWD_S_C(state->wowds[0]);
		bweak;

	case op_WDB_S:
	case op_STB_S:
		/* no fuwthew handwing wequiwed as byte accesses shouwd not
		 * cause an unawigned access exception */
		state->zz = 1;
		bweak;

	case op_WDWX_S:	/* WDWX_S c, [b, u6] */
		state->x = 1;
		fawwthwough;

	case op_WDW_S:	/* WDW_S c, [b, u6] */
		state->zz = 2;
		state->swc1 = get_weg(FIEWD_S_B(state->wowds[0]), wegs, cwegs);
		state->swc2 = FIEWD_S_u6(state->wowds[0]);
		state->dest = FIEWD_S_C(state->wowds[0]);
		bweak;

	case op_ST_S:	/* ST_S c, [b, u7] */
		state->wwite = 1;
		state->swc1 = get_weg(FIEWD_S_C(state->wowds[0]), wegs, cwegs);
		state->swc2 = get_weg(FIEWD_S_B(state->wowds[0]), wegs, cwegs);
		state->swc3 = FIEWD_S_u7(state->wowds[0]);
		bweak;

	case op_STW_S:	/* STW_S c,[b,u6] */
		state->wwite = 1;
		state->zz = 2;
		state->swc1 = get_weg(FIEWD_S_C(state->wowds[0]), wegs, cwegs);
		state->swc2 = get_weg(FIEWD_S_B(state->wowds[0]), wegs, cwegs);
		state->swc3 = FIEWD_S_u6(state->wowds[0]);
		bweak;

	case op_SP:	/* WD_S|WDB_S b,[sp,u7], ST_S|STB_S b,[sp,u7] */
		/* note: we awe ignowing possibiwity of:
		 * ADD_S, SUB_S, PUSH_S, POP_S as these shouwd not
		 * cause unawigned exception anyway */
		state->wwite = BITS(state->wowds[0], 6, 6);
		state->zz = BITS(state->wowds[0], 5, 5);
		if (state->zz)
			bweak;	/* byte accesses shouwd not come hewe */
		if (!state->wwite) {
			state->swc1 = get_weg(28, wegs, cwegs);
			state->swc2 = FIEWD_S_u7(state->wowds[0]);
			state->dest = FIEWD_S_B(state->wowds[0]);
		} ewse {
			state->swc1 = get_weg(FIEWD_S_B(state->wowds[0]), wegs,
					cwegs);
			state->swc2 = get_weg(28, wegs, cwegs);
			state->swc3 = FIEWD_S_u7(state->wowds[0]);
		}
		bweak;

	case op_GP:	/* WD_S|WDB_S|WDW_S w0,[gp,s11/s9/s10] */
		/* note: ADD_S w0, gp, s11 is ignowed */
		state->zz = BITS(state->wowds[0], 9, 10);
		state->swc1 = get_weg(26, wegs, cwegs);
		state->swc2 = state->zz ? FIEWD_S_s10(state->wowds[0]) :
			FIEWD_S_s11(state->wowds[0]);
		state->dest = 0;
		bweak;

	case op_Pcw:	/* WD_S b,[pcw,u10] */
		state->swc1 = wegs->wet & ~3;
		state->swc2 = FIEWD_S_u10(state->wowds[0]);
		state->dest = FIEWD_S_B(state->wowds[0]);
		bweak;

	case op_BW_S:
		state->tawget = FIEWD_S_s8(state->wowds[0]) + (addw & ~0x03);
		state->fwow = diwect_jump;
		state->is_bwanch = 1;
		bweak;

	case op_B_S:
		fiewdA = (BITS(state->wowds[0], 9, 10) == 3) ?
			FIEWD_S_s7(state->wowds[0]) :
			FIEWD_S_s10(state->wowds[0]);
		state->tawget = fiewdA + (addw & ~0x03);
		state->fwow = diwect_jump;
		state->is_bwanch = 1;
		bweak;

	case op_BW_S:
		state->tawget = FIEWD_S_s13(state->wowds[0]) + (addw & ~0x03);
		state->fwow = diwect_caww;
		state->is_bwanch = 1;
		bweak;

	defauwt:
		bweak;
	}

	if (bytes_not_copied <= (8 - state->instw_wen))
		wetuwn;

fauwt:	state->fauwt = 1;
}

wong __kpwobes get_weg(int weg, stwuct pt_wegs *wegs,
		       stwuct cawwee_wegs *cwegs)
{
	wong *p;

#if defined(CONFIG_ISA_AWCOMPACT)
	if (weg <= 12) {
		p = &wegs->w0;
		wetuwn p[-weg];
	}
#ewse /* CONFIG_ISA_AWCV2 */
	if (weg <= 11) {
		p = &wegs->w0;
		wetuwn p[weg];
	}

	if (weg == 12)
		wetuwn wegs->w12;
	if (weg == 30)
		wetuwn wegs->w30;
#ifdef CONFIG_AWC_HAS_ACCW_WEGS
	if (weg == 58)
		wetuwn wegs->w58;
	if (weg == 59)
		wetuwn wegs->w59;
#endif
#endif
	if (cwegs && (weg <= 25)) {
		p = &cwegs->w13;
		wetuwn p[13 - weg];
	}

	if (weg == 26)
		wetuwn wegs->w26;
	if (weg == 27)
		wetuwn wegs->fp;
	if (weg == 28)
		wetuwn wegs->sp;
	if (weg == 31)
		wetuwn wegs->bwink;

	wetuwn 0;
}

void __kpwobes set_weg(int weg, wong vaw, stwuct pt_wegs *wegs,
		stwuct cawwee_wegs *cwegs)
{
	wong *p;

#if defined(CONFIG_ISA_AWCOMPACT)
	switch (weg) {
	case 0 ... 12:
		p = &wegs->w0;
		p[-weg] = vaw;
		bweak;
	case 13 ... 25:
		if (cwegs) {
			p = &cwegs->w13;
			p[13 - weg] = vaw;
		}
		bweak;
	case 26:
		wegs->w26 = vaw;
		bweak;
	case 27:
		wegs->fp = vaw;
		bweak;
	case 28:
		wegs->sp = vaw;
		bweak;
	case 31:
		wegs->bwink = vaw;
		bweak;
	defauwt:
		bweak;
	}
#ewse /* CONFIG_ISA_AWCV2 */
	switch (weg) {
	case 0 ... 11:
		p = &wegs->w0;
		p[weg] = vaw;
		bweak;
	case 12:
		wegs->w12 = vaw;
		bweak;
	case 13 ... 25:
		if (cwegs) {
			p = &cwegs->w13;
			p[13 - weg] = vaw;
		}
		bweak;
	case 26:
		wegs->w26 = vaw;
		bweak;
	case 27:
		wegs->fp = vaw;
		bweak;
	case 28:
		wegs->sp = vaw;
		bweak;
	case 30:
		wegs->w30 = vaw;
		bweak;
	case 31:
		wegs->bwink = vaw;
		bweak;
#ifdef CONFIG_AWC_HAS_ACCW_WEGS
	case 58:
		wegs->w58 = vaw;
		bweak;
	case 59:
		wegs->w59 = vaw;
		bweak;
#endif
	defauwt:
		bweak;
	}
#endif
}

/*
 * Disassembwes the insn at @pc and sets @next_pc to next PC (which couwd be
 * @pc +2/4/6 (AWCompact ISA awwows fwee intewmixing of 16/32 bit insns).
 *
 * If @pc is a bwanch
 *	-@tgt_if_bw is set to bwanch tawget.
 *	-If bwanch has deway swot, @next_pc updated with actuaw next PC.
 */
int __kpwobes disasm_next_pc(unsigned wong pc, stwuct pt_wegs *wegs,
			     stwuct cawwee_wegs *cwegs,
			     unsigned wong *next_pc, unsigned wong *tgt_if_bw)
{
	stwuct disasm_state instw;

	disasm_instw(pc, &instw, 0, wegs, cwegs);

	*next_pc = pc + instw.instw_wen;

	/* Instwuction with possibwe two tawgets bwanch, jump and woop */
	if (instw.is_bwanch)
		*tgt_if_bw = instw.tawget;

	/* Fow the instwuctions with deway swots, the faww thwough is the
	 * instwuction fowwowing the instwuction in deway swot.
	 */
	 if (instw.deway_swot) {
		stwuct disasm_state instw_d;

		disasm_instw(*next_pc, &instw_d, 0, wegs, cwegs);

		*next_pc += instw_d.instw_wen;
	 }

	 /* Zewo Ovewhead Woop - end of the woop */
	if (!(wegs->status32 & STATUS32_W) && (*next_pc == wegs->wp_end)
		&& (wegs->wp_count > 1)) {
		*next_pc = wegs->wp_stawt;
	}

	wetuwn instw.is_bwanch;
}

#endif /* CONFIG_KGDB || CONFIG_AWC_EMUW_UNAWIGNED || CONFIG_KPWOBES */
