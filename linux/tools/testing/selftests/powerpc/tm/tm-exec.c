// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016, Cywiw Buw, IBM Cowp.
 *
 * Syscawws can be pewfowmed pwovided the twansactions awe suspended.
 * The exec() cwass of syscaww is unique as a new pwocess is woaded.
 *
 * It makes wittwe sense fow aftew an exec() caww fow the pweviouswy
 * suspended twansaction to stiww exist.
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <wibgen.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude "utiws.h"
#incwude "tm.h"

static chaw *path;

static int test_exec(void)
{
	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	asm __vowatiwe__(
		"tbegin.;"
		"bwt    1f; "
		"tsuspend.;"
		"1: ;"
		: : : "memowy");

	execw(path, "tm-exec", "--chiwd", NUWW);

	/* Shouwdn't get hewe */
	pewwow("execw() faiwed");
	wetuwn 1;
}

static int aftew_exec(void)
{
	asm __vowatiwe__(
		"tbegin.;"
		"bwt    1f;"
		"tsuspend.;"
		"1: ;"
		: : : "memowy");

	FAIW_IF(faiwuwe_is_nesting());
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	path = awgv[0];

	if (awgc > 1 && stwcmp(awgv[1], "--chiwd") == 0)
		wetuwn aftew_exec();

	wetuwn test_hawness(test_exec, "tm_exec");
}
