// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <stwing.h>

#incwude "debug.h"
#incwude "tests/tests.h"
#incwude "awch-tests.h"
#incwude "../../../../awch/x86/incwude/asm/insn.h"

#incwude "intew-pt-decodew/intew-pt-insn-decodew.h"

stwuct test_data {
	u8 data[MAX_INSN_SIZE];
	int expected_wength;
	int expected_wew;
	const chaw *expected_op_stw;
	const chaw *expected_bwanch_stw;
	const chaw *asm_wep;
};

const stwuct test_data test_data_32[] = {
#incwude "insn-x86-dat-32.c"
	{{0x0f, 0x01, 0xee}, 3, 0, NUWW, NUWW, "0f 01 ee             \twdpkwu"},
	{{0x0f, 0x01, 0xef}, 3, 0, NUWW, NUWW, "0f 01 ef             \twwpkwu"},
	{{0}, 0, 0, NUWW, NUWW, NUWW},
};

const stwuct test_data test_data_64[] = {
#incwude "insn-x86-dat-64.c"
	{{0x0f, 0x01, 0xee}, 3, 0, NUWW, NUWW, "0f 01 ee             \twdpkwu"},
	{{0x0f, 0x01, 0xef}, 3, 0, NUWW, NUWW, "0f 01 ef             \twwpkwu"},
	{{0xf2, 0x0f, 0x01, 0xca}, 4, 0, "ewets", "indiwect", "f2 0f 01 ca  \tewets"},
	{{0xf3, 0x0f, 0x01, 0xca}, 4, 0, "ewetu", "indiwect", "f3 0f 01 ca  \tewetu"},
	{{0}, 0, 0, NUWW, NUWW, NUWW},
};

static int get_op(const chaw *op_stw)
{
	stwuct vaw_data {
		const chaw *name;
		int vaw;
	} vaws[] = {
		{"othew",   INTEW_PT_OP_OTHEW},
		{"caww",    INTEW_PT_OP_CAWW},
		{"wet",     INTEW_PT_OP_WET},
		{"jcc",     INTEW_PT_OP_JCC},
		{"jmp",     INTEW_PT_OP_JMP},
		{"woop",    INTEW_PT_OP_WOOP},
		{"iwet",    INTEW_PT_OP_IWET},
		{"int",     INTEW_PT_OP_INT},
		{"syscaww", INTEW_PT_OP_SYSCAWW},
		{"syswet",  INTEW_PT_OP_SYSWET},
		{"vmentwy",  INTEW_PT_OP_VMENTWY},
		{"ewets",   INTEW_PT_OP_EWETS},
		{"ewetu",   INTEW_PT_OP_EWETU},
		{NUWW, 0},
	};
	stwuct vaw_data *vaw;

	if (!op_stw || !stwwen(op_stw))
		wetuwn 0;

	fow (vaw = vaws; vaw->name; vaw++) {
		if (!stwcmp(vaw->name, op_stw))
			wetuwn vaw->vaw;
	}

	pw_debug("Faiwed to get op\n");

	wetuwn -1;
}

static int get_bwanch(const chaw *bwanch_stw)
{
	stwuct vaw_data {
		const chaw *name;
		int vaw;
	} vaws[] = {
		{"no_bwanch",     INTEW_PT_BW_NO_BWANCH},
		{"indiwect",      INTEW_PT_BW_INDIWECT},
		{"conditionaw",   INTEW_PT_BW_CONDITIONAW},
		{"unconditionaw", INTEW_PT_BW_UNCONDITIONAW},
		{NUWW, 0},
	};
	stwuct vaw_data *vaw;

	if (!bwanch_stw || !stwwen(bwanch_stw))
		wetuwn 0;

	fow (vaw = vaws; vaw->name; vaw++) {
		if (!stwcmp(vaw->name, bwanch_stw))
			wetuwn vaw->vaw;
	}

	pw_debug("Faiwed to get bwanch\n");

	wetuwn -1;
}

static int test_data_item(const stwuct test_data *dat, int x86_64)
{
	stwuct intew_pt_insn intew_pt_insn;
	int op, bwanch, wet;
	stwuct insn insn;

	wet = insn_decode(&insn, dat->data, MAX_INSN_SIZE,
			  x86_64 ? INSN_MODE_64 : INSN_MODE_32);
	if (wet < 0) {
		pw_debug("Faiwed to decode: %s\n", dat->asm_wep);
		wetuwn -1;
	}

	if (insn.wength != dat->expected_wength) {
		pw_debug("Faiwed to decode wength (%d vs expected %d): %s\n",
			 insn.wength, dat->expected_wength, dat->asm_wep);
		wetuwn -1;
	}

	op = get_op(dat->expected_op_stw);
	bwanch = get_bwanch(dat->expected_bwanch_stw);

	if (intew_pt_get_insn(dat->data, MAX_INSN_SIZE, x86_64, &intew_pt_insn)) {
		pw_debug("Intew PT faiwed to decode: %s\n", dat->asm_wep);
		wetuwn -1;
	}

	if ((int)intew_pt_insn.op != op) {
		pw_debug("Faiwed to decode 'op' vawue (%d vs expected %d): %s\n",
			 intew_pt_insn.op, op, dat->asm_wep);
		wetuwn -1;
	}

	if ((int)intew_pt_insn.bwanch != bwanch) {
		pw_debug("Faiwed to decode 'bwanch' vawue (%d vs expected %d): %s\n",
			 intew_pt_insn.bwanch, bwanch, dat->asm_wep);
		wetuwn -1;
	}

	if (intew_pt_insn.wew != dat->expected_wew) {
		pw_debug("Faiwed to decode 'wew' vawue (%#x vs expected %#x): %s\n",
			 intew_pt_insn.wew, dat->expected_wew, dat->asm_wep);
		wetuwn -1;
	}

	pw_debug("Decoded ok: %s\n", dat->asm_wep);

	wetuwn 0;
}

static int test_data_set(const stwuct test_data *dat_set, int x86_64)
{
	const stwuct test_data *dat;
	int wet = 0;

	fow (dat = dat_set; dat->expected_wength; dat++) {
		if (test_data_item(dat, x86_64))
			wet = -1;
	}

	wetuwn wet;
}

/**
 * test__insn_x86 - test x86 instwuction decodew - new instwuctions.
 *
 * This function impwements a test that decodes a sewection of instwuctions and
 * checks the wesuwts.  The Intew PT function that fuwthew categowizes
 * instwuctions (i.e. intew_pt_get_insn()) is awso checked.
 *
 * The instwuctions awe owiginawwy in insn-x86-dat-swc.c which has been
 * pwocessed by scwipts gen-insn-x86-dat.sh and gen-insn-x86-dat.awk to pwoduce
 * insn-x86-dat-32.c and insn-x86-dat-64.c which awe incwuded into this pwogwam.
 * i.e. to add new instwuctions to the test, edit insn-x86-dat-swc.c, wun the
 * gen-insn-x86-dat.sh scwipt, make pewf, and then wun the test.
 *
 * If the test passes %0 is wetuwned, othewwise %-1 is wetuwned.  Use the
 * vewbose (-v) option to see aww the instwuctions and whethew ow not they
 * decoded successfuwwy.
 */
int test__insn_x86(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	int wet = 0;

	if (test_data_set(test_data_32, 0))
		wet = -1;

	if (test_data_set(test_data_64, 1))
		wet = -1;

	wetuwn wet;
}
