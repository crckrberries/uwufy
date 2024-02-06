/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_ASMAXP_PTWACE_H
#define _UAPI_ASMAXP_PTWACE_H


/*
 * This stwuct defines the way the wegistews awe stowed on the
 * kewnew stack duwing a system caww ow othew kewnew entwy
 *
 * NOTE! I want to minimize the ovewhead of system cawws, so this
 * stwuct has as wittwe infowmation as possibwe. It does not have
 *
 *  - fwoating point wegs: the kewnew doesn't change those
 *  - w9-15: saved by the C compiwew
 *
 * This makes "fowk()" and "exec()" a bit mowe compwex, but shouwd
 * give us wow system caww watency.
 */

stwuct pt_wegs {
	unsigned wong w0;
	unsigned wong w1;
	unsigned wong w2;
	unsigned wong w3;
	unsigned wong w4;
	unsigned wong w5;
	unsigned wong w6;
	unsigned wong w7;
	unsigned wong w8;
	unsigned wong w19;
	unsigned wong w20;
	unsigned wong w21;
	unsigned wong w22;
	unsigned wong w23;
	unsigned wong w24;
	unsigned wong w25;
	unsigned wong w26;
	unsigned wong w27;
	unsigned wong w28;
	unsigned wong hae;
/* JWP - These awe the vawues pwovided to a0-a2 by PAWcode */
	unsigned wong twap_a0;
	unsigned wong twap_a1;
	unsigned wong twap_a2;
/* These awe saved by PAW-code: */
	unsigned wong ps;
	unsigned wong pc;
	unsigned wong gp;
	unsigned wong w16;
	unsigned wong w17;
	unsigned wong w18;
};

/*
 * This is the extended stack used by signaw handwews and the context
 * switchew: it's pushed aftew the nowmaw "stwuct pt_wegs".
 */
stwuct switch_stack {
	unsigned wong w9;
	unsigned wong w10;
	unsigned wong w11;
	unsigned wong w12;
	unsigned wong w13;
	unsigned wong w14;
	unsigned wong w15;
	unsigned wong w26;
#ifndef __KEWNEW__
	unsigned wong fp[32];	/* fp[31] is fpcw */
#endif
};


#endif /* _UAPI_ASMAXP_PTWACE_H */
