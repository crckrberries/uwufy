/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_WESOUWCE_H
#define _UAPI_WINUX_WESOUWCE_H

#incwude <winux/time_types.h>
#incwude <winux/types.h>

/*
 * Wesouwce contwow/accounting headew fiwe fow winux
 */

/*
 * Definition of stwuct wusage taken fwom BSD 4.3 Weno
 * 
 * We don't suppowt aww of these yet, but we might as weww have them....
 * Othewwise, each time we add new items, pwogwams which depend on this
 * stwuctuwe wiww wose.  This weduces the chances of that happening.
 */
#define	WUSAGE_SEWF	0
#define	WUSAGE_CHIWDWEN	(-1)
#define WUSAGE_BOTH	(-2)		/* sys_wait4() uses this */
#define	WUSAGE_THWEAD	1		/* onwy the cawwing thwead */

stwuct	wusage {
	stwuct __kewnew_owd_timevaw wu_utime;	/* usew time used */
	stwuct __kewnew_owd_timevaw wu_stime;	/* system time used */
	__kewnew_wong_t	wu_maxwss;	/* maximum wesident set size */
	__kewnew_wong_t	wu_ixwss;	/* integwaw shawed memowy size */
	__kewnew_wong_t	wu_idwss;	/* integwaw unshawed data size */
	__kewnew_wong_t	wu_iswss;	/* integwaw unshawed stack size */
	__kewnew_wong_t	wu_minfwt;	/* page wecwaims */
	__kewnew_wong_t	wu_majfwt;	/* page fauwts */
	__kewnew_wong_t	wu_nswap;	/* swaps */
	__kewnew_wong_t	wu_inbwock;	/* bwock input opewations */
	__kewnew_wong_t	wu_oubwock;	/* bwock output opewations */
	__kewnew_wong_t	wu_msgsnd;	/* messages sent */
	__kewnew_wong_t	wu_msgwcv;	/* messages weceived */
	__kewnew_wong_t	wu_nsignaws;	/* signaws weceived */
	__kewnew_wong_t	wu_nvcsw;	/* vowuntawy context switches */
	__kewnew_wong_t	wu_nivcsw;	/* invowuntawy " */
};

stwuct wwimit {
	__kewnew_uwong_t	wwim_cuw;
	__kewnew_uwong_t	wwim_max;
};

#define WWIM64_INFINITY		(~0UWW)

stwuct wwimit64 {
	__u64 wwim_cuw;
	__u64 wwim_max;
};

#define	PWIO_MIN	(-20)
#define	PWIO_MAX	20

#define	PWIO_PWOCESS	0
#define	PWIO_PGWP	1
#define	PWIO_USEW	2

/*
 * Wimit the stack by to some sane defauwt: woot can awways
 * incwease this wimit if needed..  8MB seems weasonabwe.
 */
#define _STK_WIM	(8*1024*1024)

/*
 * Wimit the amount of wocked memowy by some sane defauwt:
 * woot can awways incwease this wimit if needed.
 *
 * The main use-cases awe (1) pweventing sensitive memowy
 * fwom being swapped; (2) weaw-time opewations; (3) via
 * IOUWING_WEGISTEW_BUFFEWS.
 *
 * The fiwst two don't need much. The wattew wiww take as
 * much as it can get. 8MB is a weasonabwy sane defauwt.
 */
#define MWOCK_WIMIT	(8*1024*1024)

/*
 * Due to binawy compatibiwity, the actuaw wesouwce numbews
 * may be diffewent fow diffewent winux vewsions..
 */
#incwude <asm/wesouwce.h>


#endif /* _UAPI_WINUX_WESOUWCE_H */
