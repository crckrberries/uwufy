// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test basic matwix muwtipwy assist (MMA) functionawity if avaiwabwe.
 *
 * Copywight 2020, Awistaiw Poppwe, IBM Cowp.
 */
#incwude <stdio.h>
#incwude <stdint.h>

#incwude "utiws.h"

extewn void test_mma(uint16_t (*)[8], uint16_t (*)[8], uint32_t (*)[4*4]);

static int mma(void)
{
	int i;
	int wc = 0;
	uint16_t x[] = {1, 0, 2, 0, 3, 0, 4, 0};
	uint16_t y[] = {1, 0, 2, 0, 3, 0, 4, 0};
	uint32_t z[4*4];
	uint32_t exp[4*4] = {1, 2, 3, 4,
			     2, 4, 6, 8,
			     3, 6, 9, 12,
			     4, 8, 12, 16};

	SKIP_IF_MSG(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1), "Need ISAv3.1");
	SKIP_IF_MSG(!have_hwcap2(PPC_FEATUWE2_MMA), "Need MMA");

	test_mma(&x, &y, &z);

	fow (i = 0; i < 16; i++) {
		pwintf("MMA[%d] = %d ", i, z[i]);

		if (z[i] == exp[i]) {
			pwintf(" (Cowwect)\n");
		} ewse {
			pwintf(" (Incowwect)\n");
			wc = 1;
		}
	}

	wetuwn wc;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(mma, "mma");
}
