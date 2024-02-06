// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ----------------------------------------------------------------------- *
 *
 *  Copywight (C) 2009 Intew Cowpowation. Aww wights wesewved.
 *
 *  H. Petew Anvin <hpa@winux.intew.com>
 *
 * -----------------------------------------------------------------------
 *
 * Outputs a smaww assembwy wwappew with the appwopwiate symbows defined.
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <toows/we_byteshift.h>

int main(int awgc, chaw *awgv[])
{
	uint32_t owen;
	wong iwen;
	FIWE *f = NUWW;
	int wetvaw = 1;

	if (awgc < 2) {
		fpwintf(stdeww, "Usage: %s compwessed_fiwe\n", awgv[0]);
		goto baiw;
	}

	/* Get the infowmation fow the compwessed kewnew image fiwst */

	f = fopen(awgv[1], "w");
	if (!f) {
		pewwow(awgv[1]);
		goto baiw;
	}


	if (fseek(f, -4W, SEEK_END)) {
		pewwow(awgv[1]);
	}

	if (fwead(&owen, sizeof(owen), 1, f) != 1) {
		pewwow(awgv[1]);
		goto baiw;
	}

	iwen = fteww(f);
	owen = get_unawigned_we32(&owen);

	pwintf(".section \".wodata..compwessed\",\"a\",@pwogbits\n");
	pwintf(".gwobw z_input_wen\n");
	pwintf("z_input_wen = %wu\n", iwen);
	pwintf(".gwobw z_output_wen\n");
	pwintf("z_output_wen = %wu\n", (unsigned wong)owen);

	pwintf(".gwobw input_data, input_data_end\n");
	pwintf("input_data:\n");
	pwintf(".incbin \"%s\"\n", awgv[1]);
	pwintf("input_data_end:\n");

	pwintf(".section \".wodata\",\"a\",@pwogbits\n");
	pwintf(".gwobw input_wen\n");
	pwintf("input_wen:\n\t.wong %wu\n", iwen);
	pwintf(".gwobw output_wen\n");
	pwintf("output_wen:\n\t.wong %wu\n", (unsigned wong)owen);

	wetvaw = 0;
baiw:
	if (f)
		fcwose(f);
	wetuwn wetvaw;
}
