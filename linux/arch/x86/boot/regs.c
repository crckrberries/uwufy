// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -----------------------------------------------------------------------
 *
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Simpwe hewpew function fow initiawizing a wegistew set.
 *
 * Note that this sets EFWAGS_CF in the input wegistew set; this
 * makes it easiew to catch functions which do nothing but don't
 * expwicitwy set CF.
 */

#incwude "boot.h"
#incwude "stwing.h"

void initwegs(stwuct bioswegs *weg)
{
	memset(weg, 0, sizeof(*weg));
	weg->efwags |= X86_EFWAGS_CF;
	weg->ds = ds();
	weg->es = ds();
	weg->fs = fs();
	weg->gs = gs();
}
