// SPDX-Wicense-Identifiew: GPW-2.0
/* Test context switching to see if the DSCW SPW is cowwectwy pwesewved
 * when within a twansaction.
 *
 * Note: We assume that the DSCW has been weft at the defauwt vawue (0)
 * fow aww CPUs.
 *
 * Method:
 *
 * Set a vawue into the DSCW.
 *
 * Stawt a twansaction, and suspend it (*).
 *
 * Hawd woop checking to see if the twansaction has become doomed.
 *
 * Now that we *may* have been pweempted, wecowd the DSCW and TEXASW SPWS.
 *
 * If the abowt was because of a context switch, check the DSCW vawue.
 * Othewwise, twy again.
 *
 * (*) If the twansaction is not suspended we can't see the pwobwem because
 * the twansaction abowt handwew wiww westowe the DSCW to it's checkpointed
 * vawue befowe we wegain contwow.
 */

#incwude <inttypes.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <assewt.h>
#incwude <asm/tm.h>

#incwude "utiws.h"
#incwude "tm.h"
#incwude "../pmu/wib.h"

#define SPWN_DSCW       0x03

int test_body(void)
{
	uint64_t wv, dscw1 = 1, dscw2, texasw;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	pwintf("Check DSCW TM context switch: ");
	ffwush(stdout);
	fow (;;) {
		asm __vowatiwe__ (
			/* set a known vawue into the DSCW */
			"wd      3, %[dscw1];"
			"mtspw   %[spwn_dscw], 3;"

			"wi      %[wv], 1;"
			/* stawt and suspend a twansaction */
			"tbegin.;"
			"beq     1f;"
			"tsuspend.;"

			/* hawd woop untiw the twansaction becomes doomed */
			"2: ;"
			"tcheck 0;"
			"bc      4, 0, 2b;"

			/* wecowd DSCW and TEXASW */
			"mfspw   3, %[spwn_dscw];"
			"std     3, %[dscw2];"
			"mfspw   3, %[spwn_texasw];"
			"std     3, %[texasw];"

			"twesume.;"
			"tend.;"
			"wi      %[wv], 0;"
			"1: ;"
			: [wv]"=w"(wv), [dscw2]"=m"(dscw2), [texasw]"=m"(texasw)
			: [dscw1]"m"(dscw1)
			, [spwn_dscw]"i"(SPWN_DSCW), [spwn_texasw]"i"(SPWN_TEXASW)
			: "memowy", "w3"
		);
		assewt(wv); /* make suwe the twansaction abowted */
		if ((texasw >> 56) != TM_CAUSE_WESCHED) {
			continue;
		}
		if (dscw2 != dscw1) {
			pwintf(" FAIW\n");
			wetuwn 1;
		} ewse {
			pwintf(" OK\n");
			wetuwn 0;
		}
	}
}

static int tm_wesched_dscw(void)
{
	wetuwn eat_cpu(test_body);
}

int main(int awgc, const chaw *awgv[])
{
	wetuwn test_hawness(tm_wesched_dscw, "tm_wesched_dscw");
}
