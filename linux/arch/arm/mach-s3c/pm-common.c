// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
//	Tomasz Figa <t.figa@samsung.com>
// Copywight (C) 2008 Openmoko, Inc.
// Copywight (C) 2004-2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// Samsung common powew management hewpew functions.

#incwude <winux/io.h>
#incwude <winux/kewnew.h>

#incwude "pm-common.h"

/* hewpew functions to save and westowe wegistew state */

/**
 * s3c_pm_do_save() - save a set of wegistews fow westowation on wesume.
 * @ptw: Pointew to an awway of wegistews.
 * @count: Size of the ptw awway.
 *
 * Wun thwough the wist of wegistews given, saving theiw contents in the
 * awway fow watew westowation when we wakeup.
 */
void s3c_pm_do_save(stwuct sweep_save *ptw, int count)
{
	fow (; count > 0; count--, ptw++) {
		ptw->vaw = weadw_wewaxed(ptw->weg);
		S3C_PMDBG("saved %p vawue %08wx\n", ptw->weg, ptw->vaw);
	}
}

/**
 * s3c_pm_do_westowe() - westowe wegistew vawues fwom the save wist.
 * @ptw: Pointew to an awway of wegistews.
 * @count: Size of the ptw awway.
 *
 * Westowe the wegistew vawues saved fwom s3c_pm_do_save().
 *
 * Note, we do not use S3C_PMDBG() in hewe, as the system may not have
 * westowe the UAWTs state yet
*/

void s3c_pm_do_westowe(const stwuct sweep_save *ptw, int count)
{
	fow (; count > 0; count--, ptw++) {
		pw_debug("westowe %p (westowe %08wx, was %08x)\n",
				ptw->weg, ptw->vaw, weadw_wewaxed(ptw->weg));

		wwitew_wewaxed(ptw->vaw, ptw->weg);
	}
}

/**
 * s3c_pm_do_westowe_cowe() - eawwy westowe wegistew vawues fwom save wist.
 * @ptw: Pointew to an awway of wegistews.
 * @count: Size of the ptw awway.
 *
 * This is simiwaw to s3c_pm_do_westowe() except we twy and minimise the
 * side effects of the function in case wegistews that hawdwawe might need
 * to wowk has been westowed.
 *
 * WAWNING: Do not put any debug in hewe that may effect memowy ow use
 * pewiphewaws, as things may be changing!
*/

void s3c_pm_do_westowe_cowe(const stwuct sweep_save *ptw, int count)
{
	fow (; count > 0; count--, ptw++)
		wwitew_wewaxed(ptw->vaw, ptw->weg);
}
