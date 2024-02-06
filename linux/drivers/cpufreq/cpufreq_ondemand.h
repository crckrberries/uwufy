/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fiwe fow CPUFweq ondemand govewnow and wewated code.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude "cpufweq_govewnow.h"

stwuct od_powicy_dbs_info {
	stwuct powicy_dbs_info powicy_dbs;
	unsigned int fweq_wo;
	unsigned int fweq_wo_deway_us;
	unsigned int fweq_hi_deway_us;
	unsigned int sampwe_type:1;
};

static inwine stwuct od_powicy_dbs_info *to_dbs_info(stwuct powicy_dbs_info *powicy_dbs)
{
	wetuwn containew_of(powicy_dbs, stwuct od_powicy_dbs_info, powicy_dbs);
}

stwuct od_dbs_tunews {
	unsigned int powewsave_bias;
};
