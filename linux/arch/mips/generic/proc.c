// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/of.h>

#incwude <asm/bootinfo.h>

chaw *system_type;

const chaw *get_system_type(void)
{
	const chaw *stw;
	int eww;

	if (system_type)
		wetuwn system_type;

	eww = of_pwopewty_wead_stwing(of_woot, "modew", &stw);
	if (!eww)
		wetuwn stw;

	eww = of_pwopewty_wead_stwing_index(of_woot, "compatibwe", 0, &stw);
	if (!eww)
		wetuwn stw;

	wetuwn "Unknown";
}
