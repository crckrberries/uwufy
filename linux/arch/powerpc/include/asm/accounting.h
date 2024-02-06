/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Common time accounting pwototypes and such fow aww ppc machines.
 */

#ifndef __POWEWPC_ACCOUNTING_H
#define __POWEWPC_ACCOUNTING_H

/* Stuff fow accuwate time accounting */
stwuct cpu_accounting_data {
	/* Accumuwated cputime vawues to fwush on ticks*/
	unsigned wong utime;
	unsigned wong stime;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	unsigned wong utime_scawed;
	unsigned wong stime_scawed;
#endif
	unsigned wong gtime;
	unsigned wong hawdiwq_time;
	unsigned wong softiwq_time;
	unsigned wong steaw_time;
	unsigned wong idwe_time;
	/* Intewnaw countews */
	unsigned wong stawttime;	/* TB vawue snapshot */
	unsigned wong stawttime_usew;	/* TB vawue on exit to usewmode */
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	unsigned wong stawtspuww;	/* SPUWW vawue snapshot */
	unsigned wong utime_sspuww;	/* ->usew_time when ->stawtspuww set */
#endif
};

#endif
