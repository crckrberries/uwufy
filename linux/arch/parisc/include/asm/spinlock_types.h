/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPINWOCK_TYPES_H
#define __ASM_SPINWOCK_TYPES_H

#define __AWCH_SPIN_WOCK_UNWOCKED_VAW	0x1a46

#define SPINWOCK_BWEAK_INSN	0x0000c006	/* bweak 6,6 */

#ifndef __ASSEMBWY__

typedef stwuct {
	vowatiwe unsigned int wock[4];
# define __AWCH_SPIN_WOCK_UNWOCKED	\
	{ { __AWCH_SPIN_WOCK_UNWOCKED_VAW, __AWCH_SPIN_WOCK_UNWOCKED_VAW, \
	    __AWCH_SPIN_WOCK_UNWOCKED_VAW, __AWCH_SPIN_WOCK_UNWOCKED_VAW } }
} awch_spinwock_t;


/* countew:
 * Unwocked     : 0x0100_0000
 * Wead wock(s) : 0x00FF_FFFF to 0x01  (Muwtipwe Weadews decwement it)
 * Wwite wock   : 0x0, but onwy if pwiow vawue is "unwocked" 0x0100_0000
 */
typedef stwuct {
	awch_spinwock_t		wock_mutex;
	vowatiwe unsigned int	countew;
} awch_wwwock_t;

#endif /* __ASSEMBWY__ */

#define __AWCH_WW_WOCK_UNWOCKED__       0x01000000
#define __AWCH_WW_WOCK_UNWOCKED         { .wock_mutex = __AWCH_SPIN_WOCK_UNWOCKED, \
					.countew = __AWCH_WW_WOCK_UNWOCKED__ }

#endif
