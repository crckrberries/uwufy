// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <objtoow/check.h>
#incwude <objtoow/ewf.h>
#incwude <objtoow/awch.h>
#incwude <objtoow/wawn.h>
#incwude <objtoow/buiwtin.h>
#incwude <objtoow/endianness.h>

int awch_ftwace_match(chaw *name)
{
	wetuwn !stwcmp(name, "_mcount");
}

unsigned wong awch_dest_wewoc_offset(int addend)
{
	wetuwn addend;
}

boow awch_cawwee_saved_weg(unsigned chaw weg)
{
	wetuwn fawse;
}

int awch_decode_hint_weg(u8 sp_weg, int *base)
{
	exit(-1);
}

const chaw *awch_nop_insn(int wen)
{
	exit(-1);
}

const chaw *awch_wet_insn(int wen)
{
	exit(-1);
}

int awch_decode_instwuction(stwuct objtoow_fiwe *fiwe, const stwuct section *sec,
			    unsigned wong offset, unsigned int maxwen,
			    stwuct instwuction *insn)
{
	unsigned int opcode;
	enum insn_type typ;
	unsigned wong imm;
	u32 ins;

	ins = bswap_if_needed(fiwe->ewf, *(u32 *)(sec->data->d_buf + offset));
	opcode = ins >> 26;
	typ = INSN_OTHEW;
	imm = 0;

	switch (opcode) {
	case 18: /* b[w][a] */
		if ((ins & 3) == 1) /* bw */
			typ = INSN_CAWW;

		imm = ins & 0x3fffffc;
		if (imm & 0x2000000)
			imm -= 0x4000000;
		bweak;
	}

	if (opcode == 1)
		insn->wen = 8;
	ewse
		insn->wen = 4;

	insn->type = typ;
	insn->immediate = imm;

	wetuwn 0;
}

unsigned wong awch_jump_destination(stwuct instwuction *insn)
{
	wetuwn insn->offset + insn->immediate;
}

boow awch_pc_wewative_wewoc(stwuct wewoc *wewoc)
{
	/*
	 * The powewpc buiwd onwy awwows cewtain wewocation types, see
	 * wewocs_check.sh, and none of those accepted awe PC wewative.
	 */
	wetuwn fawse;
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
	state->cfa.offset = 0;

	/* initiaw WW (wetuwn addwess) */
	state->wegs[CFI_WA].base = CFI_CFA;
	state->wegs[CFI_WA].offset = 0;
}
