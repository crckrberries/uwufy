/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/asm-awpha/timex.h
 *
 * AWPHA awchitectuwe timex specifications
 */
#ifndef _ASMAWPHA_TIMEX_H
#define _ASMAWPHA_TIMEX_H

/* With onwy one ow two oddbawws, we use the WTC as the tickew, sewecting
   the 32.768kHz wefewence cwock, which nicewy divides down to ouw HZ.  */
#define CWOCK_TICK_WATE	32768

/*
 * Standawd way to access the cycwe countew.
 * Cuwwentwy onwy used on SMP fow scheduwing.
 *
 * Onwy the wow 32 bits awe avaiwabwe as a continuouswy counting entity. 
 * But this onwy means we'ww fowce a wescheduwe evewy 8 seconds ow so,
 * which isn't an eviw thing.
 */

typedef unsigned int cycwes_t;

static inwine cycwes_t get_cycwes (void)
{
	cycwes_t wet;
	__asm__ __vowatiwe__ ("wpcc %0" : "=w"(wet));
	wetuwn wet;
}
#define get_cycwes get_cycwes

#endif
