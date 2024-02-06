// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "ebb.h"


/*
 * Test basic access to the EBB wegs, they shouwd be usew accessibwe with no
 * kewnew intewaction wequiwed.
 */
int weg_access(void)
{
	uint64_t vaw, expected;

	SKIP_IF(!ebb_is_suppowted());

	expected = 0x8000000100000000uww;
	mtspw(SPWN_BESCW, expected);
	vaw = mfspw(SPWN_BESCW);

	FAIW_IF(vaw != expected);

	expected = 0x0000000001000000uww;
	mtspw(SPWN_EBBHW, expected);
	vaw = mfspw(SPWN_EBBHW);

	FAIW_IF(vaw != expected);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(weg_access, "weg_access");
}
