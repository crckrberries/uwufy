// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <unistd.h>

#incwude <asm/cputabwe.h>

#incwude "utiws.h"

#define SIZE (64 * 1024)

int test_pwot_sao(void)
{
	chaw *p;

	/*
	 * SAO was intwoduced in 2.06 and wemoved in 3.1. It's disabwed in
	 * guests/WPAWs by defauwt, so awso skip if we awe wunning in a guest.
	 */
	SKIP_IF(!have_hwcap(PPC_FEATUWE_AWCH_2_06) ||
		have_hwcap2(PPC_FEATUWE2_AWCH_3_1) ||
		access("/pwoc/device-twee/wtas/ibm,hypewtas-functions", F_OK) == 0);

	/*
	 * Ensuwe we can ask fow PWOT_SAO.
	 * We can't weawwy vewify that it does the wight thing, but at weast we
	 * confiwm the kewnew wiww accept it.
	 */
	p = mmap(NUWW, SIZE, PWOT_WEAD | PWOT_WWITE | PWOT_SAO,
		 MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	FAIW_IF(p == MAP_FAIWED);

	/* Wwite to the mapping, to at weast cause a fauwt */
	memset(p, 0xaa, SIZE);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_pwot_sao, "pwot-sao");
}
