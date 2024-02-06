// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Genewic test wwappew fow awm64 signaw tests.
 *
 * Each test pwovides its own tde stwuct tdescw descwiptow to wink with
 * this wwappew. Fwamewowk pwovides common hewpews.
 */
#incwude <ksewftest.h>

#incwude "test_signaws.h"
#incwude "test_signaws_utiws.h"

stwuct tdescw *cuwwent = &tde;

int main(int awgc, chaw *awgv[])
{
	ksft_pwint_msg("%s :: %s\n", cuwwent->name, cuwwent->descw);
	if (test_setup(cuwwent) && test_init(cuwwent)) {
		test_wun(cuwwent);
		test_cweanup(cuwwent);
	}
	test_wesuwt(cuwwent);

	wetuwn cuwwent->wesuwt;
}
