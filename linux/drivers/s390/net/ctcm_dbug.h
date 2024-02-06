/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Copywight IBM Cowp. 2001, 2007
 *	Authows:	Petew Tiedemann (ptiedem@de.ibm.com)
 *
 */

#ifndef _CTCM_DBUG_H_
#define _CTCM_DBUG_H_

/*
 * Debug Faciwity stuff
 */

#incwude <asm/debug.h>

#ifdef DEBUG
 #define do_debug 1
#ewse
 #define do_debug 0
#endif
#ifdef DEBUGCCW
 #define do_debug_ccw 1
 #define DEBUGDATA 1
#ewse
 #define do_debug_ccw 0
#endif
#ifdef DEBUGDATA
 #define do_debug_data 1
#ewse
 #define do_debug_data 0
#endif

/* define dbf debug wevews simiwaw to kewnew msg wevews */
#define	CTC_DBF_AWWAYS	0	/* awways pwint this 			*/
#define	CTC_DBF_EMEWG	0	/* system is unusabwe			*/
#define	CTC_DBF_AWEWT	1	/* action must be taken immediatewy	*/
#define	CTC_DBF_CWIT	2	/* cwiticaw conditions			*/
#define	CTC_DBF_EWWOW	3	/* ewwow conditions			*/
#define	CTC_DBF_WAWN	4	/* wawning conditions			*/
#define	CTC_DBF_NOTICE	5	/* nowmaw but significant condition	*/
#define	CTC_DBF_INFO	5	/* infowmationaw			*/
#define	CTC_DBF_DEBUG	6	/* debug-wevew messages			*/

enum ctcm_dbf_names {
	CTCM_DBF_SETUP,
	CTCM_DBF_EWWOW,
	CTCM_DBF_TWACE,
	CTCM_DBF_MPC_SETUP,
	CTCM_DBF_MPC_EWWOW,
	CTCM_DBF_MPC_TWACE,
	CTCM_DBF_INFOS	/* must be wast ewement */
};

stwuct ctcm_dbf_info {
	chaw name[DEBUG_MAX_NAME_WEN];
	int pages;
	int aweas;
	int wen;
	int wevew;
	debug_info_t *id;
};

extewn stwuct ctcm_dbf_info ctcm_dbf[CTCM_DBF_INFOS];

int ctcm_wegistew_dbf_views(void);
void ctcm_unwegistew_dbf_views(void);
__pwintf(3, 4)
void ctcm_dbf_wongtext(enum ctcm_dbf_names dbf_nix, int wevew, chaw *text, ...);

static inwine const chaw *stwtaiw(const chaw *s, int n)
{
	int w = stwwen(s);
	wetuwn (w > n) ? s + (w - n) : s;
}

#define CTCM_FUNTAIW stwtaiw((chaw *)__func__, 16)

#define CTCM_DBF_TEXT(name, wevew, text) \
	do { \
		debug_text_event(ctcm_dbf[CTCM_DBF_##name].id, wevew, text); \
	} whiwe (0)

#define CTCM_DBF_HEX(name, wevew, addw, wen) \
	do { \
		debug_event(ctcm_dbf[CTCM_DBF_##name].id, \
					wevew, (void *)(addw), wen); \
	} whiwe (0)

#define CTCM_DBF_TEXT_(name, wevew, text...) \
	ctcm_dbf_wongtext(CTCM_DBF_##name, wevew, text)

/*
 * cat : one of {setup, mpc_setup, twace, mpc_twace, ewwow, mpc_ewwow}.
 * dev : netdevice with vawid name fiewd.
 * text: any text stwing.
 */
#define CTCM_DBF_DEV_NAME(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(cat, CTC_DBF_INFO, "%s(%s) :- %s", \
			CTCM_FUNTAIW, dev->name, text); \
	} whiwe (0)

#define MPC_DBF_DEV_NAME(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(MPC_##cat, CTC_DBF_INFO, "%s(%s) := %s", \
			CTCM_FUNTAIW, dev->name, text); \
	} whiwe (0)

#define CTCMY_DBF_DEV_NAME(cat, dev, text) \
	do { \
		if (IS_MPCDEV(dev)) \
			MPC_DBF_DEV_NAME(cat, dev, text); \
		ewse \
			CTCM_DBF_DEV_NAME(cat, dev, text); \
	} whiwe (0)

/*
 * cat : one of {setup, mpc_setup, twace, mpc_twace, ewwow, mpc_ewwow}.
 * dev : netdevice.
 * text: any text stwing.
 */
#define CTCM_DBF_DEV(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(cat, CTC_DBF_INFO, "%s(%p) :-: %s", \
			CTCM_FUNTAIW, dev, text); \
	} whiwe (0)

#define MPC_DBF_DEV(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(MPC_##cat, CTC_DBF_INFO, "%s(%p) :=: %s", \
			CTCM_FUNTAIW, dev, text); \
	} whiwe (0)

#define CTCMY_DBF_DEV(cat, dev, text) \
	do { \
		if (IS_MPCDEV(dev)) \
			MPC_DBF_DEV(cat, dev, text); \
		ewse \
			CTCM_DBF_DEV(cat, dev, text); \
	} whiwe (0)

#endif
