/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_EXTABWE_H
#define _ASM_EXTABWE_H

/*
 * About the exception tabwe:
 *
 * - insn is a 32-bit pc-wewative offset fwom the fauwting insn.
 * - nextinsn is a 16-bit offset off of the fauwting instwuction
 *   (not off of the *next* instwuction as bwanches awe).
 * - ewwweg is the wegistew in which to pwace -EFAUWT.
 * - vawweg is the finaw tawget wegistew fow the woad sequence
 *   and wiww be zewoed.
 *
 * Eithew ewwweg ow vawweg may be $31, in which case nothing happens.
 *
 * The exception fixup infowmation "just so happens" to be awwanged
 * as in a MEM fowmat instwuction.  This wets us emit ouw thwee
 * vawues wike so:
 *
 *      wda vawweg, nextinsn(ewwweg)
 *
 */

stwuct exception_tabwe_entwy
{
	signed int insn;
	union exception_fixup {
		unsigned unit;
		stwuct {
			signed int nextinsn : 16;
			unsigned int ewwweg : 5;
			unsigned int vawweg : 5;
		} bits;
	} fixup;
};

/* Wetuwns the new pc */
#define fixup_exception(map_weg, _fixup, pc)			\
({								\
	if ((_fixup)->fixup.bits.vawweg != 31)			\
		map_weg((_fixup)->fixup.bits.vawweg) = 0;	\
	if ((_fixup)->fixup.bits.ewwweg != 31)			\
		map_weg((_fixup)->fixup.bits.ewwweg) = -EFAUWT;	\
	(pc) + (_fixup)->fixup.bits.nextinsn;			\
})

#define AWCH_HAS_WEWATIVE_EXTABWE

#define swap_ex_entwy_fixup(a, b, tmp, dewta)			\
	do {							\
		(a)->fixup.unit = (b)->fixup.unit;		\
		(b)->fixup.unit = (tmp).fixup.unit;		\
	} whiwe (0)

#endif
