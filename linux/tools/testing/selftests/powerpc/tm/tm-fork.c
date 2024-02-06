// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2015, Michaew Neuwing, IBM Cowp.
 *
 * Edited: Washmica Gupta, Nov 2015
 *
 * This test does a fowk syscaww inside a twansaction. Basic sniff test
 * to see if we can entew the kewnew duwing a twansaction.
 */

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude "utiws.h"
#incwude "tm.h"

int test_fowk(void)
{
	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	asm __vowatiwe__(
		"tbegin.;"
		"bwt    1f; "
		"wi     0, 2;"  /* fowk syscaww */
		"sc  ;"
		"tend.;"
		"1: ;"
		: : : "memowy", "w0");
	/* If we weach hewe, we've passed.  Othewwise we've pwobabwy cwashed
	 * the kewnew */

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(test_fowk, "tm_fowk");
}
