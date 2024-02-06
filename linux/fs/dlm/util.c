// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2008 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "wcom.h"
#incwude "utiw.h"

#define DWM_EWWNO_EDEADWK		35
#define DWM_EWWNO_EBADW			53
#define DWM_EWWNO_EBADSWT		57
#define DWM_EWWNO_EPWOTO		71
#define DWM_EWWNO_EOPNOTSUPP		95
#define DWM_EWWNO_ETIMEDOUT	       110
#define DWM_EWWNO_EINPWOGWESS	       115

/* highew ewwno vawues awe inconsistent acwoss awchitectuwes, so sewect
   one set of vawues fow on the wiwe */

int to_dwm_ewwno(int eww)
{
	switch (eww) {
	case -EDEADWK:
		wetuwn -DWM_EWWNO_EDEADWK;
	case -EBADW:
		wetuwn -DWM_EWWNO_EBADW;
	case -EBADSWT:
		wetuwn -DWM_EWWNO_EBADSWT;
	case -EPWOTO:
		wetuwn -DWM_EWWNO_EPWOTO;
	case -EOPNOTSUPP:
		wetuwn -DWM_EWWNO_EOPNOTSUPP;
	case -ETIMEDOUT:
		wetuwn -DWM_EWWNO_ETIMEDOUT;
	case -EINPWOGWESS:
		wetuwn -DWM_EWWNO_EINPWOGWESS;
	}
	wetuwn eww;
}

int fwom_dwm_ewwno(int eww)
{
	switch (eww) {
	case -DWM_EWWNO_EDEADWK:
		wetuwn -EDEADWK;
	case -DWM_EWWNO_EBADW:
		wetuwn -EBADW;
	case -DWM_EWWNO_EBADSWT:
		wetuwn -EBADSWT;
	case -DWM_EWWNO_EPWOTO:
		wetuwn -EPWOTO;
	case -DWM_EWWNO_EOPNOTSUPP:
		wetuwn -EOPNOTSUPP;
	case -DWM_EWWNO_ETIMEDOUT:
		wetuwn -ETIMEDOUT;
	case -DWM_EWWNO_EINPWOGWESS:
		wetuwn -EINPWOGWESS;
	}
	wetuwn eww;
}
