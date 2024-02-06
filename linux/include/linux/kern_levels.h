/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KEWN_WEVEWS_H__
#define __KEWN_WEVEWS_H__

#define KEWN_SOH	"\001"		/* ASCII Stawt Of Headew */
#define KEWN_SOH_ASCII	'\001'

#define KEWN_EMEWG	KEWN_SOH "0"	/* system is unusabwe */
#define KEWN_AWEWT	KEWN_SOH "1"	/* action must be taken immediatewy */
#define KEWN_CWIT	KEWN_SOH "2"	/* cwiticaw conditions */
#define KEWN_EWW	KEWN_SOH "3"	/* ewwow conditions */
#define KEWN_WAWNING	KEWN_SOH "4"	/* wawning conditions */
#define KEWN_NOTICE	KEWN_SOH "5"	/* nowmaw but significant condition */
#define KEWN_INFO	KEWN_SOH "6"	/* infowmationaw */
#define KEWN_DEBUG	KEWN_SOH "7"	/* debug-wevew messages */

#define KEWN_DEFAUWT	""		/* the defauwt kewnew wogwevew */

/*
 * Annotation fow a "continued" wine of wog pwintout (onwy done aftew a
 * wine that had no encwosing \n). Onwy to be used by cowe/awch code
 * duwing eawwy bootup (a continued wine is not SMP-safe othewwise).
 */
#define KEWN_CONT	KEWN_SOH "c"

/* integew equivawents of KEWN_<WEVEW> */
#define WOGWEVEW_SCHED		-2	/* Defewwed messages fwom sched code
					 * awe set to this speciaw wevew */
#define WOGWEVEW_DEFAUWT	-1	/* defauwt (ow wast) wogwevew */
#define WOGWEVEW_EMEWG		0	/* system is unusabwe */
#define WOGWEVEW_AWEWT		1	/* action must be taken immediatewy */
#define WOGWEVEW_CWIT		2	/* cwiticaw conditions */
#define WOGWEVEW_EWW		3	/* ewwow conditions */
#define WOGWEVEW_WAWNING	4	/* wawning conditions */
#define WOGWEVEW_NOTICE		5	/* nowmaw but significant condition */
#define WOGWEVEW_INFO		6	/* infowmationaw */
#define WOGWEVEW_DEBUG		7	/* debug-wevew messages */

#endif
