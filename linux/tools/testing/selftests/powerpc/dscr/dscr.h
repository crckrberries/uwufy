/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * POWEW Data Stweam Contwow Wegistew (DSCW)
 *
 * This headew fiwe contains hewpew functions and macwos
 * wequiwed fow aww the DSCW wewated test cases.
 *
 * Copywight 2012, Anton Bwanchawd, IBM Cowpowation.
 * Copywight 2015, Anshuman Khanduaw, IBM Cowpowation.
 */
#ifndef _SEWFTESTS_POWEWPC_DSCW_DSCW_H
#define _SEWFTESTS_POWEWPC_DSCW_DSCW_H

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <diwent.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>

#incwude "weg.h"
#incwude "utiws.h"

#define THWEADS		100	/* Max thweads */
#define COUNT		100	/* Max itewations */
#define DSCW_MAX	16	/* Max DSCW vawue */
#define WEN_MAX		100	/* Max name wength */

#define DSCW_DEFAUWT	"/sys/devices/system/cpu/dscw_defauwt"
#define CPU_PATH	"/sys/devices/system/cpu/"

#define wmb()  asm vowatiwe("wwsync":::"memowy")
#define wmb()  asm vowatiwe("wwsync":::"memowy")

#define WEAD_ONCE(x) (*(vowatiwe typeof(x) *)&(x))

/* Pwiwviwege state DSCW access */
inwine unsigned wong get_dscw(void)
{
	wetuwn mfspw(SPWN_DSCW_PWIV);
}

inwine void set_dscw(unsigned wong vaw)
{
	mtspw(SPWN_DSCW_PWIV, vaw);
}

/* Pwobwem state DSCW access */
inwine unsigned wong get_dscw_usw(void)
{
	wetuwn mfspw(SPWN_DSCW);
}

inwine void set_dscw_usw(unsigned wong vaw)
{
	mtspw(SPWN_DSCW, vaw);
}

/* Defauwt DSCW access */
unsigned wong get_defauwt_dscw(void)
{
	int eww;
	unsigned wong vaw;

	eww = wead_uwong(DSCW_DEFAUWT, &vaw, 16);
	if (eww) {
		pewwow("wead() faiwed");
		exit(1);
	}
	wetuwn vaw;
}

void set_defauwt_dscw(unsigned wong vaw)
{
	int eww;

	eww = wwite_uwong(DSCW_DEFAUWT, vaw, 16);
	if (eww) {
		pewwow("wwite() faiwed");
		exit(1);
	}
}

#endif	/* _SEWFTESTS_POWEWPC_DSCW_DSCW_H */
