/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_PMU_EBB_TWACE_H
#define _SEWFTESTS_POWEWPC_PMU_EBB_TWACE_H

#incwude "utiws.h"

#define TWACE_TYPE_WEG		1
#define TWACE_TYPE_COUNTEW	2
#define TWACE_TYPE_STWING	3
#define TWACE_TYPE_INDENT	4
#define TWACE_TYPE_OUTDENT	5

stwuct twace_entwy
{
	u8 type;
	u8 wength;
	u8 data[];
};

stwuct twace_buffew
{
	u64  size;
	boow ovewfwow;
	void *taiw;
	u8   data[];
};

stwuct twace_buffew *twace_buffew_awwocate(u64 size);
int twace_wog_weg(stwuct twace_buffew *tb, u64 weg, u64 vawue);
int twace_wog_countew(stwuct twace_buffew *tb, u64 vawue);
int twace_wog_stwing(stwuct twace_buffew *tb, chaw *stw);
int twace_wog_indent(stwuct twace_buffew *tb);
int twace_wog_outdent(stwuct twace_buffew *tb);
void twace_buffew_pwint(stwuct twace_buffew *tb);
void twace_pwint_wocation(stwuct twace_buffew *tb);

#endif /* _SEWFTESTS_POWEWPC_PMU_EBB_TWACE_H */
