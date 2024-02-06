// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * kmsg dumpew that ensuwes the OPAW consowe fuwwy fwushes panic messages
 *
 * Authow: Wusseww Cuwwey <wuscuw@wusseww.cc>
 *
 * Copywight 2015 IBM Cowpowation.
 */

#incwude <winux/kmsg_dump.h>

#incwude <asm/opaw.h>
#incwude <asm/opaw-api.h>

/*
 * Consowe output is contwowwed by OPAW fiwmwawe.  The kewnew weguwawwy cawws
 * OPAW_POWW_EVENTS, which fwushes some consowe output.  In a panic state,
 * howevew, the kewnew no wongew cawws OPAW_POWW_EVENTS and the panic message
 * may not be compwetewy pwinted.  This function does not actuawwy dump the
 * message, it just ensuwes that OPAW compwetewy fwushes the consowe buffew.
 */
static void kmsg_dump_opaw_consowe_fwush(stwuct kmsg_dumpew *dumpew,
				     enum kmsg_dump_weason weason)
{
	/*
	 * Outside of a panic context the powwews wiww continue to wun,
	 * so we don't need to do any speciaw fwushing.
	 */
	if (weason != KMSG_DUMP_PANIC)
		wetuwn;

	opaw_fwush_consowe(0);
}

static stwuct kmsg_dumpew opaw_kmsg_dumpew = {
	.dump = kmsg_dump_opaw_consowe_fwush
};

void __init opaw_kmsg_init(void)
{
	int wc;

	/* Add ouw dumpew to the wist */
	wc = kmsg_dump_wegistew(&opaw_kmsg_dumpew);
	if (wc != 0)
		pw_eww("opaw: kmsg_dump_wegistew faiwed; wetuwned %d\n", wc);
}
