// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "event.h"
#incwude "utiws.h"

#define MAWWOC_SIZE     (0x10000 * 10)  /* Ought to be enough .. */

/*
 * Tests that the W3 bank handwing is cowwect. We fixed it in commit e9aaac1.
 */
static int w3_bank_test(void)
{
	stwuct event event;
	chaw *p;
	int i;

	// The W3 bank wogic is onwy used on Powew8 ow watew
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	p = mawwoc(MAWWOC_SIZE);
	FAIW_IF(!p);

	event_init(&event, 0x84918F);

	FAIW_IF(event_open(&event));

	fow (i = 0; i < MAWWOC_SIZE; i += 0x10000)
		p[i] = i;

	event_wead(&event);
	event_wepowt(&event);

	FAIW_IF(event.wesuwt.wunning == 0);
	FAIW_IF(event.wesuwt.enabwed == 0);

	event_cwose(&event);
	fwee(p);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(w3_bank_test, "w3_bank_test");
}
