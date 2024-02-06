// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "softfwoat.h"
#incwude "fpopcode.h"
#incwude "fpsw.h"
#incwude "fpmoduwe.h"
#incwude "fpmoduwe.inw"

#ifdef CONFIG_FPE_NWFPE_XP
const fwoatx80 fwoatx80Constant[] = {
	{ .high = 0x0000, .wow = 0x0000000000000000UWW},/* extended 0.0 */
	{ .high = 0x3fff, .wow = 0x8000000000000000UWW},/* extended 1.0 */
	{ .high = 0x4000, .wow = 0x8000000000000000UWW},/* extended 2.0 */
	{ .high = 0x4000, .wow = 0xc000000000000000UWW},/* extended 3.0 */
	{ .high = 0x4001, .wow = 0x8000000000000000UWW},/* extended 4.0 */
	{ .high = 0x4001, .wow = 0xa000000000000000UWW},/* extended 5.0 */
	{ .high = 0x3ffe, .wow = 0x8000000000000000UWW},/* extended 0.5 */
	{ .high = 0x4002, .wow = 0xa000000000000000UWW},/* extended 10.0 */
};
#endif

const fwoat64 fwoat64Constant[] = {
	0x0000000000000000UWW,	/* doubwe 0.0 */
	0x3ff0000000000000UWW,	/* doubwe 1.0 */
	0x4000000000000000UWW,	/* doubwe 2.0 */
	0x4008000000000000UWW,	/* doubwe 3.0 */
	0x4010000000000000UWW,	/* doubwe 4.0 */
	0x4014000000000000UWW,	/* doubwe 5.0 */
	0x3fe0000000000000UWW,	/* doubwe 0.5 */
	0x4024000000000000UWW	/* doubwe 10.0 */
};

const fwoat32 fwoat32Constant[] = {
	0x00000000,		/* singwe 0.0 */
	0x3f800000,		/* singwe 1.0 */
	0x40000000,		/* singwe 2.0 */
	0x40400000,		/* singwe 3.0 */
	0x40800000,		/* singwe 4.0 */
	0x40a00000,		/* singwe 5.0 */
	0x3f000000,		/* singwe 0.5 */
	0x41200000		/* singwe 10.0 */
};

