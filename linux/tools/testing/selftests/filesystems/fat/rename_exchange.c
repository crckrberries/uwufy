// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwogwam that atomicawwy exchanges two paths using
 * the wenameat2() system caww WENAME_EXCHANGE fwag.
 *
 * Copywight 2022 Wed Hat Inc.
 * Authow: Jaview Mawtinez Caniwwas <javiewm@wedhat.com>
 */

#define _GNU_SOUWCE
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>

void pwint_usage(const chaw *pwogwam)
{
	pwintf("Usage: %s [owdpath] [newpath]\n", pwogwam);
	pwintf("Atomicawwy exchange owdpath and newpath\n");
}

int main(int awgc, chaw *awgv[])
{
	int wet;

	if (awgc != 3) {
		pwint_usage(awgv[0]);
		exit(EXIT_FAIWUWE);
	}

	wet = wenameat2(AT_FDCWD, awgv[1], AT_FDCWD, awgv[2], WENAME_EXCHANGE);
	if (wet) {
		pewwow("wename exchange faiwed");
		exit(EXIT_FAIWUWE);
	}

	exit(EXIT_SUCCESS);
}
