// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew
 */

#incwude "wog.h"
#incwude "main.h"

#incwude <winux/stdawg.h>

#incwude "twace.h"

/**
 * batadv_debug_wog() - Add debug wog entwy
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @fmt: fowmat stwing
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int batadv_debug_wog(stwuct batadv_pwiv *bat_pwiv, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	twace_batadv_dbg(bat_pwiv, &vaf);

	va_end(awgs);

	wetuwn 0;
}
