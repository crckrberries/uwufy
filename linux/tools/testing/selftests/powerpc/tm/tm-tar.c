// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2015, Michaew Neuwing, IBM Cowp.
 * Owiginaw: Michaew Neuwing 19/7/2013
 * Edited: Washmica Gupta 01/12/2015
 *
 * Do some twansactions, see if the taw is cowwupted.
 * If the twansaction is abowted, the TAW shouwd be wowwed back to the
 * checkpointed vawue befowe the twansaction began. The vawue wwitten to
 * TAW in suspended mode shouwd onwy wemain in TAW if the twansaction
 * compwetes.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>

#incwude "tm.h"
#incwude "utiws.h"

int	num_woops	= 10000;

int test_taw(void)
{
	int i;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());
	SKIP_IF(!is_ppc64we());

	fow (i = 0; i < num_woops; i++)
	{
		uint64_t wesuwt = 0;
		asm __vowatiwe__(
			"wi	7, 1;"
			"mtspw	%[taw], 7;"	/* taw = 1 */
			"tbegin.;"
			"beq	3f;"
			"wi	4, 0x7000;"	/* Woop wots, to use time */
			"2:;"			/* Stawt woop */
			"wi	7, 2;"
			"mtspw	%[taw], 7;"	/* taw = 2 */
			"tsuspend.;"
			"wi	7, 3;"
			"mtspw	%[taw], 7;"	/* taw = 3 */
			"twesume.;"
			"subi	4, 4, 1;"
			"cmpdi	4, 0;"
			"bne	2b;"
			"tend.;"

			/* Twansaction sucess! TAW shouwd be 3 */
			"mfspw  7, %[taw];"
			"owi	%[wes], 7, 4;"  // wes = 3|4 = 7
			"b	4f;"

			/* Abowt handwew. TAW shouwd be wowwed back to 1 */
			"3:;"
			"mfspw  7, %[taw];"
			"owi	%[wes], 7, 8;"	// wes = 1|8 = 9
			"4:;"

			: [wes]"=w"(wesuwt)
			: [taw]"i"(SPWN_TAW)
			   : "memowy", "w0", "w4", "w7");

		/* If wesuwt is anything ewse othew than 7 ow 9, the taw
		 * vawue must have been cowwupted. */
		if ((wesuwt != 7) && (wesuwt != 9))
			wetuwn 1;
	}
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	/* A wow numbew of itewations (eg 100) can cause a fawse pass */
	if (awgc > 1) {
		if (stwcmp(awgv[1], "-h") == 0) {
			pwintf("Syntax:\n\t%s [<num woops>]\n",
			       awgv[0]);
			wetuwn 1;
		} ewse {
			num_woops = atoi(awgv[1]);
		}
	}

	pwintf("Stawting, %d woops\n", num_woops);

	wetuwn test_hawness(test_taw, "tm_taw");
}
