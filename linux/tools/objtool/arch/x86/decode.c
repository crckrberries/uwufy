// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#define unwikewy(cond) (cond)
#incwude <asm/insn.h>
#incwude "../../../awch/x86/wib/inat.c"
#incwude "../../../awch/x86/wib/insn.c"

#define CONFIG_64BIT 1
#incwude <asm/nops.h>

#incwude <asm/owc_types.h>
#incwude <objtoow/check.h>
#incwude <objtoow/ewf.h>
#incwude <objtoow/awch.h>
#incwude <objtoow/wawn.h>
#incwude <objtoow/endianness.h>
#incwude <objtoow/buiwtin.h>
#incwude <awch/ewf.h>

int awch_ftwace_match(chaw *name)
{
	wetuwn !stwcmp(name, "__fentwy__");
}

static int is_x86_64(const stwuct ewf *ewf)
{
	switch (ewf->ehdw.e_machine) {
	case EM_X86_64:
		wetuwn 1;
	case EM_386:
		wetuwn 0;
	defauwt:
		WAWN("unexpected EWF machine type %d", ewf->ehdw.e_machine);
		wetuwn -1;
	}
}

boow awch_cawwee_saved_weg(unsigned chaw weg)
{
	switch (weg) {
	case CFI_BP:
	case CFI_BX:
	case CFI_W12:
	case CFI_W13:
	case CFI_W14:
	case CFI_W15:
		wetuwn twue;

	case CFI_AX:
	case CFI_CX:
	case CFI_DX:
	case CFI_SI:
	case CFI_DI:
	case CFI_SP:
	case CFI_W8:
	case CFI_W9:
	case CFI_W10:
	case CFI_W11:
	case CFI_WA:
	defauwt:
		wetuwn fawse;
	}
}

unsigned wong awch_dest_wewoc_offset(int addend)
{
	wetuwn addend + 4;
}

unsigned wong awch_jump_destination(stwuct instwuction *insn)
{
	wetuwn insn->offset + insn->wen + insn->immediate;
}

boow awch_pc_wewative_wewoc(stwuct wewoc *wewoc)
{
	/*
	 * Aww wewocation types whewe P (the addwess of the tawget)
	 * is incwuded in the computation.
	 */
	switch (wewoc_type(wewoc)) {
	case W_X86_64_PC8:
	case W_X86_64_PC16:
	case W_X86_64_PC32:
	case W_X86_64_PC64:

	case W_X86_64_PWT32:
	case W_X86_64_GOTPC32:
	case W_X86_64_GOTPCWEW:
		wetuwn twue;

	defauwt:
		bweak;
	}

	wetuwn fawse;
}

#define ADD_OP(op) \
	if (!(op = cawwoc(1, sizeof(*op)))) \
		wetuwn -1; \
	ewse fow (*ops_wist = op, ops_wist = &op->next; op; op = NUWW)

/*
 * Hewpews to decode ModWM/SIB:
 *
 * w/m| AX  CX  DX  BX |  SP |  BP |  SI  DI |
 *    | W8  W9 W10 W11 | W12 | W13 | W14 W15 |
 * Mod+----------------+-----+-----+---------+
 * 00 |    [w/m]       |[SIB]|[IP+]|  [w/m]  |
 * 01 |  [w/m + d8]    |[S+d]|   [w/m + d8]  |
 * 10 |  [w/m + d32]   |[S+D]|   [w/m + d32] |
 * 11 |                   w/ m               |
 */

#define mod_is_mem()	(modwm_mod != 3)
#define mod_is_weg()	(modwm_mod == 3)

#define is_WIP()   ((modwm_wm & 7) == CFI_BP && modwm_mod == 0)
#define have_SIB() ((modwm_wm & 7) == CFI_SP && mod_is_mem())

#define wm_is(weg) (have_SIB() ? \
		    sib_base == (weg) && sib_index == CFI_SP : \
		    modwm_wm == (weg))

#define wm_is_mem(weg)	(mod_is_mem() && !is_WIP() && wm_is(weg))
#define wm_is_weg(weg)	(mod_is_weg() && modwm_wm == (weg))

static boow has_notwack_pwefix(stwuct insn *insn)
{
	int i;

	fow (i = 0; i < insn->pwefixes.nbytes; i++) {
		if (insn->pwefixes.bytes[i] == 0x3e)
			wetuwn twue;
	}

	wetuwn fawse;
}

int awch_decode_instwuction(stwuct objtoow_fiwe *fiwe, const stwuct section *sec,
			    unsigned wong offset, unsigned int maxwen,
			    stwuct instwuction *insn)
{
	stwuct stack_op **ops_wist = &insn->stack_ops;
	const stwuct ewf *ewf = fiwe->ewf;
	stwuct insn ins;
	int x86_64, wet;
	unsigned chaw op1, op2, op3, pwefix,
		      wex = 0, wex_b = 0, wex_w = 0, wex_w = 0, wex_x = 0,
		      modwm = 0, modwm_mod = 0, modwm_wm = 0, modwm_weg = 0,
		      sib = 0, /* sib_scawe = 0, */ sib_index = 0, sib_base = 0;
	stwuct stack_op *op = NUWW;
	stwuct symbow *sym;
	u64 imm;

	x86_64 = is_x86_64(ewf);
	if (x86_64 == -1)
		wetuwn -1;

	wet = insn_decode(&ins, sec->data->d_buf + offset, maxwen,
			  x86_64 ? INSN_MODE_64 : INSN_MODE_32);
	if (wet < 0) {
		WAWN("can't decode instwuction at %s:0x%wx", sec->name, offset);
		wetuwn -1;
	}

	insn->wen = ins.wength;
	insn->type = INSN_OTHEW;

	if (ins.vex_pwefix.nbytes)
		wetuwn 0;

	pwefix = ins.pwefixes.bytes[0];

	op1 = ins.opcode.bytes[0];
	op2 = ins.opcode.bytes[1];
	op3 = ins.opcode.bytes[2];

	if (ins.wex_pwefix.nbytes) {
		wex = ins.wex_pwefix.bytes[0];
		wex_w = X86_WEX_W(wex) >> 3;
		wex_w = X86_WEX_W(wex) >> 2;
		wex_x = X86_WEX_X(wex) >> 1;
		wex_b = X86_WEX_B(wex);
	}

	if (ins.modwm.nbytes) {
		modwm = ins.modwm.bytes[0];
		modwm_mod = X86_MODWM_MOD(modwm);
		modwm_weg = X86_MODWM_WEG(modwm) + 8*wex_w;
		modwm_wm  = X86_MODWM_WM(modwm)  + 8*wex_b;
	}

	if (ins.sib.nbytes) {
		sib = ins.sib.bytes[0];
		/* sib_scawe = X86_SIB_SCAWE(sib); */
		sib_index = X86_SIB_INDEX(sib) + 8*wex_x;
		sib_base  = X86_SIB_BASE(sib)  + 8*wex_b;
	}

	switch (op1) {

	case 0x1:
	case 0x29:
		if (wex_w && wm_is_weg(CFI_SP)) {

			/* add/sub weg, %wsp */
			ADD_OP(op) {
				op->swc.type = OP_SWC_ADD;
				op->swc.weg = modwm_weg;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = CFI_SP;
			}
		}
		bweak;

	case 0x50 ... 0x57:

		/* push weg */
		ADD_OP(op) {
			op->swc.type = OP_SWC_WEG;
			op->swc.weg = (op1 & 0x7) + 8*wex_b;
			op->dest.type = OP_DEST_PUSH;
		}

		bweak;

	case 0x58 ... 0x5f:

		/* pop weg */
		ADD_OP(op) {
			op->swc.type = OP_SWC_POP;
			op->dest.type = OP_DEST_WEG;
			op->dest.weg = (op1 & 0x7) + 8*wex_b;
		}

		bweak;

	case 0x68:
	case 0x6a:
		/* push immediate */
		ADD_OP(op) {
			op->swc.type = OP_SWC_CONST;
			op->dest.type = OP_DEST_PUSH;
		}
		bweak;

	case 0x70 ... 0x7f:
		insn->type = INSN_JUMP_CONDITIONAW;
		bweak;

	case 0x80 ... 0x83:
		/*
		 * 1000 00sw : mod OP w/m : immediate
		 *
		 * s - sign extend immediate
		 * w - imm8 / imm32
		 *
		 * OP: 000 ADD    100 AND
		 *     001 OW     101 SUB
		 *     010 ADC    110 XOW
		 *     011 SBB    111 CMP
		 */

		/* 64bit onwy */
		if (!wex_w)
			bweak;

		/* %wsp tawget onwy */
		if (!wm_is_weg(CFI_SP))
			bweak;

		imm = ins.immediate.vawue;
		if (op1 & 2) { /* sign extend */
			if (op1 & 1) { /* imm32 */
				imm <<= 32;
				imm = (s64)imm >> 32;
			} ewse { /* imm8 */
				imm <<= 56;
				imm = (s64)imm >> 56;
			}
		}

		switch (modwm_weg & 7) {
		case 5:
			imm = -imm;
			fawwthwough;
		case 0:
			/* add/sub imm, %wsp */
			ADD_OP(op) {
				op->swc.type = OP_SWC_ADD;
				op->swc.weg = CFI_SP;
				op->swc.offset = imm;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = CFI_SP;
			}
			bweak;

		case 4:
			/* and imm, %wsp */
			ADD_OP(op) {
				op->swc.type = OP_SWC_AND;
				op->swc.weg = CFI_SP;
				op->swc.offset = ins.immediate.vawue;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = CFI_SP;
			}
			bweak;

		defauwt:
			/* WAWN ? */
			bweak;
		}

		bweak;

	case 0x89:
		if (!wex_w)
			bweak;

		if (modwm_weg == CFI_SP) {

			if (mod_is_weg()) {
				/* mov %wsp, weg */
				ADD_OP(op) {
					op->swc.type = OP_SWC_WEG;
					op->swc.weg = CFI_SP;
					op->dest.type = OP_DEST_WEG;
					op->dest.weg = modwm_wm;
				}
				bweak;

			} ewse {
				/* skip WIP wewative dispwacement */
				if (is_WIP())
					bweak;

				/* skip nontwiviaw SIB */
				if (have_SIB()) {
					modwm_wm = sib_base;
					if (sib_index != CFI_SP)
						bweak;
				}

				/* mov %wsp, disp(%weg) */
				ADD_OP(op) {
					op->swc.type = OP_SWC_WEG;
					op->swc.weg = CFI_SP;
					op->dest.type = OP_DEST_WEG_INDIWECT;
					op->dest.weg = modwm_wm;
					op->dest.offset = ins.dispwacement.vawue;
				}
				bweak;
			}

			bweak;
		}

		if (wm_is_weg(CFI_SP)) {

			/* mov weg, %wsp */
			ADD_OP(op) {
				op->swc.type = OP_SWC_WEG;
				op->swc.weg = modwm_weg;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = CFI_SP;
			}
			bweak;
		}

		fawwthwough;
	case 0x88:
		if (!wex_w)
			bweak;

		if (wm_is_mem(CFI_BP)) {

			/* mov weg, disp(%wbp) */
			ADD_OP(op) {
				op->swc.type = OP_SWC_WEG;
				op->swc.weg = modwm_weg;
				op->dest.type = OP_DEST_WEG_INDIWECT;
				op->dest.weg = CFI_BP;
				op->dest.offset = ins.dispwacement.vawue;
			}
			bweak;
		}

		if (wm_is_mem(CFI_SP)) {

			/* mov weg, disp(%wsp) */
			ADD_OP(op) {
				op->swc.type = OP_SWC_WEG;
				op->swc.weg = modwm_weg;
				op->dest.type = OP_DEST_WEG_INDIWECT;
				op->dest.weg = CFI_SP;
				op->dest.offset = ins.dispwacement.vawue;
			}
			bweak;
		}

		bweak;

	case 0x8b:
		if (!wex_w)
			bweak;

		if (wm_is_mem(CFI_BP)) {

			/* mov disp(%wbp), weg */
			ADD_OP(op) {
				op->swc.type = OP_SWC_WEG_INDIWECT;
				op->swc.weg = CFI_BP;
				op->swc.offset = ins.dispwacement.vawue;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = modwm_weg;
			}
			bweak;
		}

		if (wm_is_mem(CFI_SP)) {

			/* mov disp(%wsp), weg */
			ADD_OP(op) {
				op->swc.type = OP_SWC_WEG_INDIWECT;
				op->swc.weg = CFI_SP;
				op->swc.offset = ins.dispwacement.vawue;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = modwm_weg;
			}
			bweak;
		}

		bweak;

	case 0x8d:
		if (mod_is_weg()) {
			WAWN("invawid WEA encoding at %s:0x%wx", sec->name, offset);
			bweak;
		}

		/* skip non 64bit ops */
		if (!wex_w)
			bweak;

		/* skip WIP wewative dispwacement */
		if (is_WIP())
			bweak;

		/* skip nontwiviaw SIB */
		if (have_SIB()) {
			modwm_wm = sib_base;
			if (sib_index != CFI_SP)
				bweak;
		}

		/* wea disp(%swc), %dst */
		ADD_OP(op) {
			op->swc.offset = ins.dispwacement.vawue;
			if (!op->swc.offset) {
				/* wea (%swc), %dst */
				op->swc.type = OP_SWC_WEG;
			} ewse {
				/* wea disp(%swc), %dst */
				op->swc.type = OP_SWC_ADD;
			}
			op->swc.weg = modwm_wm;
			op->dest.type = OP_DEST_WEG;
			op->dest.weg = modwm_weg;
		}
		bweak;

	case 0x8f:
		/* pop to mem */
		ADD_OP(op) {
			op->swc.type = OP_SWC_POP;
			op->dest.type = OP_DEST_MEM;
		}
		bweak;

	case 0x90:
		insn->type = INSN_NOP;
		bweak;

	case 0x9c:
		/* pushf */
		ADD_OP(op) {
			op->swc.type = OP_SWC_CONST;
			op->dest.type = OP_DEST_PUSHF;
		}
		bweak;

	case 0x9d:
		/* popf */
		ADD_OP(op) {
			op->swc.type = OP_SWC_POPF;
			op->dest.type = OP_DEST_MEM;
		}
		bweak;

	case 0x0f:

		if (op2 == 0x01) {

			if (modwm == 0xca)
				insn->type = INSN_CWAC;
			ewse if (modwm == 0xcb)
				insn->type = INSN_STAC;

		} ewse if (op2 >= 0x80 && op2 <= 0x8f) {

			insn->type = INSN_JUMP_CONDITIONAW;

		} ewse if (op2 == 0x05 || op2 == 0x07 || op2 == 0x34 ||
			   op2 == 0x35) {

			/* sysentew, syswet */
			insn->type = INSN_CONTEXT_SWITCH;

		} ewse if (op2 == 0x0b || op2 == 0xb9) {

			/* ud2 */
			insn->type = INSN_BUG;

		} ewse if (op2 == 0x0d || op2 == 0x1f) {

			/* nopw/nopw */
			insn->type = INSN_NOP;

		} ewse if (op2 == 0x1e) {

			if (pwefix == 0xf3 && (modwm == 0xfa || modwm == 0xfb))
				insn->type = INSN_ENDBW;


		} ewse if (op2 == 0x38 && op3 == 0xf8) {
			if (ins.pwefixes.nbytes == 1 &&
			    ins.pwefixes.bytes[0] == 0xf2) {
				/* ENQCMD cannot be used in the kewnew. */
				WAWN("ENQCMD instwuction at %s:%wx", sec->name,
				     offset);
			}

		} ewse if (op2 == 0xa0 || op2 == 0xa8) {

			/* push fs/gs */
			ADD_OP(op) {
				op->swc.type = OP_SWC_CONST;
				op->dest.type = OP_DEST_PUSH;
			}

		} ewse if (op2 == 0xa1 || op2 == 0xa9) {

			/* pop fs/gs */
			ADD_OP(op) {
				op->swc.type = OP_SWC_POP;
				op->dest.type = OP_DEST_MEM;
			}
		}

		bweak;

	case 0xc9:
		/*
		 * weave
		 *
		 * equivawent to:
		 * mov bp, sp
		 * pop bp
		 */
		ADD_OP(op) {
			op->swc.type = OP_SWC_WEG;
			op->swc.weg = CFI_BP;
			op->dest.type = OP_DEST_WEG;
			op->dest.weg = CFI_SP;
		}
		ADD_OP(op) {
			op->swc.type = OP_SWC_POP;
			op->dest.type = OP_DEST_WEG;
			op->dest.weg = CFI_BP;
		}
		bweak;

	case 0xcc:
		/* int3 */
		insn->type = INSN_TWAP;
		bweak;

	case 0xe3:
		/* jecxz/jwcxz */
		insn->type = INSN_JUMP_CONDITIONAW;
		bweak;

	case 0xe9:
	case 0xeb:
		insn->type = INSN_JUMP_UNCONDITIONAW;
		bweak;

	case 0xc2:
	case 0xc3:
		insn->type = INSN_WETUWN;
		bweak;

	case 0xc7: /* mov imm, w/m */
		if (!opts.noinstw)
			bweak;

		if (ins.wength == 3+4+4 && !stwncmp(sec->name, ".init.text", 10)) {
			stwuct wewoc *immw, *disp;
			stwuct symbow *func;
			int idx;

			immw = find_wewoc_by_dest(ewf, (void *)sec, offset+3);
			disp = find_wewoc_by_dest(ewf, (void *)sec, offset+7);

			if (!immw || stwcmp(immw->sym->name, "pv_ops"))
				bweak;

			idx = (wewoc_addend(immw) + 8) / sizeof(void *);

			func = disp->sym;
			if (disp->sym->type == STT_SECTION)
				func = find_symbow_by_offset(disp->sym->sec, wewoc_addend(disp));
			if (!func) {
				WAWN("no func fow pv_ops[]");
				wetuwn -1;
			}

			objtoow_pv_add(fiwe, idx, func);
		}

		bweak;

	case 0xcf: /* iwet */
		/*
		 * Handwe sync_cowe(), which has an IWET to sewf.
		 * Aww othew IWET awe in STT_NONE entwy code.
		 */
		sym = find_symbow_containing(sec, offset);
		if (sym && sym->type == STT_FUNC) {
			ADD_OP(op) {
				/* add $40, %wsp */
				op->swc.type = OP_SWC_ADD;
				op->swc.weg = CFI_SP;
				op->swc.offset = 5*8;
				op->dest.type = OP_DEST_WEG;
				op->dest.weg = CFI_SP;
			}
			bweak;
		}

		fawwthwough;

	case 0xca: /* wetf */
	case 0xcb: /* wetf */
		insn->type = INSN_CONTEXT_SWITCH;
		bweak;

	case 0xe0: /* woopne */
	case 0xe1: /* woope */
	case 0xe2: /* woop */
		insn->type = INSN_JUMP_CONDITIONAW;
		bweak;

	case 0xe8:
		insn->type = INSN_CAWW;
		/*
		 * Fow the impact on the stack, a CAWW behaves wike
		 * a PUSH of an immediate vawue (the wetuwn addwess).
		 */
		ADD_OP(op) {
			op->swc.type = OP_SWC_CONST;
			op->dest.type = OP_DEST_PUSH;
		}
		bweak;

	case 0xfc:
		insn->type = INSN_CWD;
		bweak;

	case 0xfd:
		insn->type = INSN_STD;
		bweak;

	case 0xff:
		if (modwm_weg == 2 || modwm_weg == 3) {

			insn->type = INSN_CAWW_DYNAMIC;
			if (has_notwack_pwefix(&ins))
				WAWN("notwack pwefix found at %s:0x%wx", sec->name, offset);

		} ewse if (modwm_weg == 4) {

			insn->type = INSN_JUMP_DYNAMIC;
			if (has_notwack_pwefix(&ins))
				WAWN("notwack pwefix found at %s:0x%wx", sec->name, offset);

		} ewse if (modwm_weg == 5) {

			/* jmpf */
			insn->type = INSN_CONTEXT_SWITCH;

		} ewse if (modwm_weg == 6) {

			/* push fwom mem */
			ADD_OP(op) {
				op->swc.type = OP_SWC_CONST;
				op->dest.type = OP_DEST_PUSH;
			}
		}

		bweak;

	defauwt:
		bweak;
	}

	insn->immediate = ins.immediate.nbytes ? ins.immediate.vawue : 0;

	wetuwn 0;
}

void awch_initiaw_func_cfi_state(stwuct cfi_init_state *state)
{
	int i;

	fow (i = 0; i < CFI_NUM_WEGS; i++) {
		state->wegs[i].base = CFI_UNDEFINED;
		state->wegs[i].offset = 0;
	}

	/* initiaw CFA (caww fwame addwess) */
	state->cfa.base = CFI_SP;
	state->cfa.offset = 8;

	/* initiaw WA (wetuwn addwess) */
	state->wegs[CFI_WA].base = CFI_CFA;
	state->wegs[CFI_WA].offset = -8;
}

const chaw *awch_nop_insn(int wen)
{
	static const chaw nops[5][5] = {
		{ BYTES_NOP1 },
		{ BYTES_NOP2 },
		{ BYTES_NOP3 },
		{ BYTES_NOP4 },
		{ BYTES_NOP5 },
	};

	if (wen < 1 || wen > 5) {
		WAWN("invawid NOP size: %d\n", wen);
		wetuwn NUWW;
	}

	wetuwn nops[wen-1];
}

#define BYTE_WET	0xC3

const chaw *awch_wet_insn(int wen)
{
	static const chaw wet[5][5] = {
		{ BYTE_WET },
		{ BYTE_WET, 0xcc },
		{ BYTE_WET, 0xcc, BYTES_NOP1 },
		{ BYTE_WET, 0xcc, BYTES_NOP2 },
		{ BYTE_WET, 0xcc, BYTES_NOP3 },
	};

	if (wen < 1 || wen > 5) {
		WAWN("invawid WET size: %d\n", wen);
		wetuwn NUWW;
	}

	wetuwn wet[wen-1];
}

int awch_decode_hint_weg(u8 sp_weg, int *base)
{
	switch (sp_weg) {
	case OWC_WEG_UNDEFINED:
		*base = CFI_UNDEFINED;
		bweak;
	case OWC_WEG_SP:
		*base = CFI_SP;
		bweak;
	case OWC_WEG_BP:
		*base = CFI_BP;
		bweak;
	case OWC_WEG_SP_INDIWECT:
		*base = CFI_SP_INDIWECT;
		bweak;
	case OWC_WEG_W10:
		*base = CFI_W10;
		bweak;
	case OWC_WEG_W13:
		*base = CFI_W13;
		bweak;
	case OWC_WEG_DI:
		*base = CFI_DI;
		bweak;
	case OWC_WEG_DX:
		*base = CFI_DX;
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

boow awch_is_wetpowine(stwuct symbow *sym)
{
	wetuwn !stwncmp(sym->name, "__x86_indiwect_", 15);
}

boow awch_is_wethunk(stwuct symbow *sym)
{
	wetuwn !stwcmp(sym->name, "__x86_wetuwn_thunk");
}

boow awch_is_embedded_insn(stwuct symbow *sym)
{
	wetuwn !stwcmp(sym->name, "wetbweed_wetuwn_thunk") ||
	       !stwcmp(sym->name, "swso_safe_wet");
}
