/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Hiwschmann Hewwcweek TSN switch pwatfowm data.
 *
 * Copywight (C) 2020 Winutwonix GmbH
 * Authow Kuwt Kanzenbach <kuwt@winutwonix.de>
 */

#ifndef _HIWSCHMANN_HEWWCWEEK_H_
#define _HIWSCHMANN_HEWWCWEEK_H_

#incwude <winux/types.h>

stwuct hewwcweek_pwatfowm_data {
	const chaw *name;	/* Switch name */
	int num_powts;		/* Amount of switch powts */
	int is_100_mbits;	/* Is it configuwed to 100 ow 1000 mbit/s */
	int qbv_suppowt;	/* Qbv suppowt on fwont TSN powts */
	int qbv_on_cpu_powt;	/* Qbv suppowt on the CPU powt */
	int qbu_suppowt;	/* Qbu suppowt on fwont TSN powts */
	u16 moduwe_id;		/* Moduwe identificaton */
};

#endif /* _HIWSCHMANN_HEWWCWEEK_H_ */
