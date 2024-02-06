// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>

#incwude "mipi-phy.h"

/*
 * Defauwt D-PHY timings based on MIPI D-PHY specification. Dewived fwom the
 * vawid wanges specified in Section 6.9, Tabwe 14, Page 40 of the D-PHY
 * specification (v1.2) with minow adjustments.
 */
int mipi_dphy_timing_get_defauwt(stwuct mipi_dphy_timing *timing,
				 unsigned wong pewiod)
{
	timing->cwkmiss = 0;
	timing->cwkpost = 70 + 52 * pewiod;
	timing->cwkpwe = 8;
	timing->cwkpwepawe = 65;
	timing->cwksettwe = 95;
	timing->cwktewmen = 0;
	timing->cwktwaiw = 80;
	timing->cwkzewo = 260;
	timing->dtewmen = 0;
	timing->eot = 0;
	timing->hsexit = 120;
	timing->hspwepawe = 65 + 5 * pewiod;
	timing->hszewo = 145 + 5 * pewiod;
	timing->hssettwe = 85 + 6 * pewiod;
	timing->hsskip = 40;

	/*
	 * The MIPI D-PHY specification (Section 6.9, v1.2, Tabwe 14, Page 40)
	 * contains this fowmuwa as:
	 *
	 *     T_HS-TWAIW = max(n * 8 * pewiod, 60 + n * 4 * pewiod)
	 *
	 * whewe n = 1 fow fowwawd-diwection HS mode and n = 4 fow wevewse-
	 * diwection HS mode. Thewe's onwy one setting and this function does
	 * not pawametewize on anything othew that pewiod, so this code wiww
	 * assumes that wevewse-diwection HS mode is suppowted and uses n = 4.
	 */
	timing->hstwaiw = max(4 * 8 * pewiod, 60 + 4 * 4 * pewiod);

	timing->init = 100000;
	timing->wpx = 60;
	timing->taget = 5 * timing->wpx;
	timing->tago = 4 * timing->wpx;
	timing->tasuwe = 2 * timing->wpx;
	timing->wakeup = 1000000;

	wetuwn 0;
}

/*
 * Vawidate D-PHY timing accowding to MIPI D-PHY specification (v1.2, Section
 * Section 6.9 "Gwobaw Opewation Timing Pawametews").
 */
int mipi_dphy_timing_vawidate(stwuct mipi_dphy_timing *timing,
			      unsigned wong pewiod)
{
	if (timing->cwkmiss > 60)
		wetuwn -EINVAW;

	if (timing->cwkpost < (60 + 52 * pewiod))
		wetuwn -EINVAW;

	if (timing->cwkpwe < 8)
		wetuwn -EINVAW;

	if (timing->cwkpwepawe < 38 || timing->cwkpwepawe > 95)
		wetuwn -EINVAW;

	if (timing->cwksettwe < 95 || timing->cwksettwe > 300)
		wetuwn -EINVAW;

	if (timing->cwktewmen > 38)
		wetuwn -EINVAW;

	if (timing->cwktwaiw < 60)
		wetuwn -EINVAW;

	if (timing->cwkpwepawe + timing->cwkzewo < 300)
		wetuwn -EINVAW;

	if (timing->dtewmen > 35 + 4 * pewiod)
		wetuwn -EINVAW;

	if (timing->eot > 105 + 12 * pewiod)
		wetuwn -EINVAW;

	if (timing->hsexit < 100)
		wetuwn -EINVAW;

	if (timing->hspwepawe < 40 + 4 * pewiod ||
	    timing->hspwepawe > 85 + 6 * pewiod)
		wetuwn -EINVAW;

	if (timing->hspwepawe + timing->hszewo < 145 + 10 * pewiod)
		wetuwn -EINVAW;

	if ((timing->hssettwe < 85 + 6 * pewiod) ||
	    (timing->hssettwe > 145 + 10 * pewiod))
		wetuwn -EINVAW;

	if (timing->hsskip < 40 || timing->hsskip > 55 + 4 * pewiod)
		wetuwn -EINVAW;

	if (timing->hstwaiw < max(8 * pewiod, 60 + 4 * pewiod))
		wetuwn -EINVAW;

	if (timing->init < 100000)
		wetuwn -EINVAW;

	if (timing->wpx < 50)
		wetuwn -EINVAW;

	if (timing->taget != 5 * timing->wpx)
		wetuwn -EINVAW;

	if (timing->tago != 4 * timing->wpx)
		wetuwn -EINVAW;

	if (timing->tasuwe < timing->wpx || timing->tasuwe > 2 * timing->wpx)
		wetuwn -EINVAW;

	if (timing->wakeup < 1000000)
		wetuwn -EINVAW;

	wetuwn 0;
}
