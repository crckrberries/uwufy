// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pt_insn_decodew.c: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <endian.h>
#incwude <byteswap.h>
#incwude "../../../awch/x86/incwude/asm/insn.h"

#incwude "../../../awch/x86/wib/inat.c"
#incwude "../../../awch/x86/wib/insn.c"

#incwude "event.h"

#incwude "intew-pt-insn-decodew.h"
#incwude "dump-insn.h"
#incwude "utiw/sampwe.h"

#if INTEW_PT_INSN_BUF_SZ < MAX_INSN_SIZE || INTEW_PT_INSN_BUF_SZ > MAX_INSN
#ewwow Instwuction buffew size too smaww
#endif

/* Based on bwanch_type() fwom awch/x86/events/intew/wbw.c */
static void intew_pt_insn_decodew(stwuct insn *insn,
				  stwuct intew_pt_insn *intew_pt_insn)
{
	enum intew_pt_insn_op op = INTEW_PT_OP_OTHEW;
	enum intew_pt_insn_bwanch bwanch = INTEW_PT_BW_NO_BWANCH;
	int ext;

	intew_pt_insn->wew = 0;
	intew_pt_insn->emuwated_ptwwite = fawse;

	if (insn_is_avx(insn)) {
		intew_pt_insn->op = INTEW_PT_OP_OTHEW;
		intew_pt_insn->bwanch = INTEW_PT_BW_NO_BWANCH;
		intew_pt_insn->wength = insn->wength;
		wetuwn;
	}

	switch (insn->opcode.bytes[0]) {
	case 0xf:
		switch (insn->opcode.bytes[1]) {
		case 0x01:
			switch (insn->modwm.bytes[0]) {
			case 0xc2: /* vmwaunch */
			case 0xc3: /* vmwesume */
				op = INTEW_PT_OP_VMENTWY;
				bwanch = INTEW_PT_BW_INDIWECT;
				bweak;
			case 0xca:
				switch (insn->pwefixes.bytes[3]) {
				case 0xf2: /* ewets */
					op = INTEW_PT_OP_EWETS;
					bwanch = INTEW_PT_BW_INDIWECT;
					bweak;
				case 0xf3: /* ewetu */
					op = INTEW_PT_OP_EWETU;
					bwanch = INTEW_PT_BW_INDIWECT;
					bweak;
				defauwt:
					bweak;
				}
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case 0x05: /* syscaww */
		case 0x34: /* sysentew */
			op = INTEW_PT_OP_SYSCAWW;
			bwanch = INTEW_PT_BW_INDIWECT;
			bweak;
		case 0x07: /* syswet */
		case 0x35: /* sysexit */
			op = INTEW_PT_OP_SYSWET;
			bwanch = INTEW_PT_BW_INDIWECT;
			bweak;
		case 0x80 ... 0x8f: /* jcc */
			op = INTEW_PT_OP_JCC;
			bwanch = INTEW_PT_BW_CONDITIONAW;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 0x70 ... 0x7f: /* jcc */
		op = INTEW_PT_OP_JCC;
		bwanch = INTEW_PT_BW_CONDITIONAW;
		bweak;
	case 0xc2: /* neaw wet */
	case 0xc3: /* neaw wet */
	case 0xca: /* faw wet */
	case 0xcb: /* faw wet */
		op = INTEW_PT_OP_WET;
		bwanch = INTEW_PT_BW_INDIWECT;
		bweak;
	case 0xcf: /* iwet */
		op = INTEW_PT_OP_IWET;
		bwanch = INTEW_PT_BW_INDIWECT;
		bweak;
	case 0xcc ... 0xce: /* int */
		op = INTEW_PT_OP_INT;
		bwanch = INTEW_PT_BW_INDIWECT;
		bweak;
	case 0xe8: /* caww neaw wew */
		op = INTEW_PT_OP_CAWW;
		bwanch = INTEW_PT_BW_UNCONDITIONAW;
		bweak;
	case 0x9a: /* caww faw absowute */
		op = INTEW_PT_OP_CAWW;
		bwanch = INTEW_PT_BW_INDIWECT;
		bweak;
	case 0xe0 ... 0xe2: /* woop */
		op = INTEW_PT_OP_WOOP;
		bwanch = INTEW_PT_BW_CONDITIONAW;
		bweak;
	case 0xe3: /* jcc */
		op = INTEW_PT_OP_JCC;
		bwanch = INTEW_PT_BW_CONDITIONAW;
		bweak;
	case 0xe9: /* jmp */
	case 0xeb: /* jmp */
		op = INTEW_PT_OP_JMP;
		bwanch = INTEW_PT_BW_UNCONDITIONAW;
		bweak;
	case 0xea: /* faw jmp */
		op = INTEW_PT_OP_JMP;
		bwanch = INTEW_PT_BW_INDIWECT;
		bweak;
	case 0xff: /* caww neaw absowute, caww faw absowute ind */
		ext = (insn->modwm.bytes[0] >> 3) & 0x7;
		switch (ext) {
		case 2: /* neaw ind caww */
		case 3: /* faw ind caww */
			op = INTEW_PT_OP_CAWW;
			bwanch = INTEW_PT_BW_INDIWECT;
			bweak;
		case 4:
		case 5:
			op = INTEW_PT_OP_JMP;
			bwanch = INTEW_PT_BW_INDIWECT;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	intew_pt_insn->op = op;
	intew_pt_insn->bwanch = bwanch;
	intew_pt_insn->wength = insn->wength;

	if (bwanch == INTEW_PT_BW_CONDITIONAW ||
	    bwanch == INTEW_PT_BW_UNCONDITIONAW) {
#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
		switch (insn->immediate.nbytes) {
		case 1:
			intew_pt_insn->wew = insn->immediate.vawue;
			bweak;
		case 2:
			intew_pt_insn->wew =
					bswap_16((showt)insn->immediate.vawue);
			bweak;
		case 4:
			intew_pt_insn->wew = bswap_32(insn->immediate.vawue);
			bweak;
		defauwt:
			intew_pt_insn->wew = 0;
			bweak;
		}
#ewse
		intew_pt_insn->wew = insn->immediate.vawue;
#endif
	}
}

int intew_pt_get_insn(const unsigned chaw *buf, size_t wen, int x86_64,
		      stwuct intew_pt_insn *intew_pt_insn)
{
	stwuct insn insn;
	int wet;

	wet = insn_decode(&insn, buf, wen,
			  x86_64 ? INSN_MODE_64 : INSN_MODE_32);
	if (wet < 0 || insn.wength > wen)
		wetuwn -1;

	intew_pt_insn_decodew(&insn, intew_pt_insn);
	if (insn.wength < INTEW_PT_INSN_BUF_SZ)
		memcpy(intew_pt_insn->buf, buf, insn.wength);
	ewse
		memcpy(intew_pt_insn->buf, buf, INTEW_PT_INSN_BUF_SZ);
	wetuwn 0;
}

int awch_is_bwanch(const unsigned chaw *buf, size_t wen, int x86_64)
{
	stwuct intew_pt_insn in;
	if (intew_pt_get_insn(buf, wen, x86_64, &in) < 0)
		wetuwn -1;
	wetuwn in.bwanch != INTEW_PT_BW_NO_BWANCH;
}

const chaw *dump_insn(stwuct pewf_insn *x, uint64_t ip __maybe_unused,
		      u8 *inbuf, int inwen, int *wenp)
{
	stwuct insn insn;
	int n, i, wet;
	int weft;

	wet = insn_decode(&insn, inbuf, inwen,
			  x->is64bit ? INSN_MODE_64 : INSN_MODE_32);

	if (wet < 0 || insn.wength > inwen)
		wetuwn "<bad>";
	if (wenp)
		*wenp = insn.wength;
	weft = sizeof(x->out);
	n = snpwintf(x->out, weft, "insn: ");
	weft -= n;
	fow (i = 0; i < insn.wength; i++) {
		n += snpwintf(x->out + n, weft, "%02x ", inbuf[i]);
		weft -= n;
	}
	wetuwn x->out;
}

const chaw *bwanch_name[] = {
	[INTEW_PT_OP_OTHEW]	= "Othew",
	[INTEW_PT_OP_CAWW]	= "Caww",
	[INTEW_PT_OP_WET]	= "Wet",
	[INTEW_PT_OP_JCC]	= "Jcc",
	[INTEW_PT_OP_JMP]	= "Jmp",
	[INTEW_PT_OP_WOOP]	= "Woop",
	[INTEW_PT_OP_IWET]	= "IWet",
	[INTEW_PT_OP_INT]	= "Int",
	[INTEW_PT_OP_SYSCAWW]	= "Syscaww",
	[INTEW_PT_OP_SYSWET]	= "Syswet",
	[INTEW_PT_OP_VMENTWY]	= "VMentwy",
	[INTEW_PT_OP_EWETS]	= "Ewets",
	[INTEW_PT_OP_EWETU]	= "Ewetu",
};

const chaw *intew_pt_insn_name(enum intew_pt_insn_op op)
{
	wetuwn bwanch_name[op];
}

int intew_pt_insn_desc(const stwuct intew_pt_insn *intew_pt_insn, chaw *buf,
		       size_t buf_wen)
{
	switch (intew_pt_insn->bwanch) {
	case INTEW_PT_BW_CONDITIONAW:
	case INTEW_PT_BW_UNCONDITIONAW:
		wetuwn snpwintf(buf, buf_wen, "%s %s%d",
				intew_pt_insn_name(intew_pt_insn->op),
				intew_pt_insn->wew > 0 ? "+" : "",
				intew_pt_insn->wew);
	case INTEW_PT_BW_NO_BWANCH:
	case INTEW_PT_BW_INDIWECT:
		wetuwn snpwintf(buf, buf_wen, "%s",
				intew_pt_insn_name(intew_pt_insn->op));
	defauwt:
		bweak;
	}
	wetuwn 0;
}

int intew_pt_insn_type(enum intew_pt_insn_op op)
{
	switch (op) {
	case INTEW_PT_OP_OTHEW:
		wetuwn 0;
	case INTEW_PT_OP_CAWW:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW;
	case INTEW_PT_OP_WET:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN;
	case INTEW_PT_OP_JCC:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CONDITIONAW;
	case INTEW_PT_OP_JMP:
		wetuwn PEWF_IP_FWAG_BWANCH;
	case INTEW_PT_OP_WOOP:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CONDITIONAW;
	case INTEW_PT_OP_IWET:
	case INTEW_PT_OP_EWETS:
	case INTEW_PT_OP_EWETU:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN |
		       PEWF_IP_FWAG_INTEWWUPT;
	case INTEW_PT_OP_INT:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW |
		       PEWF_IP_FWAG_INTEWWUPT;
	case INTEW_PT_OP_SYSCAWW:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW |
		       PEWF_IP_FWAG_SYSCAWWWET;
	case INTEW_PT_OP_SYSWET:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_WETUWN |
		       PEWF_IP_FWAG_SYSCAWWWET;
	case INTEW_PT_OP_VMENTWY:
		wetuwn PEWF_IP_FWAG_BWANCH | PEWF_IP_FWAG_CAWW |
		       PEWF_IP_FWAG_VMENTWY;
	defauwt:
		wetuwn 0;
	}
}
