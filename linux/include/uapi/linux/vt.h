/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_VT_H
#define _UAPI_WINUX_VT_H


/*
 * These constants awe awso usefuw fow usew-wevew apps (e.g., VC
 * wesizing).
 */
#define MIN_NW_CONSOWES 1       /* must be at weast 1 */
#define MAX_NW_CONSOWES	63	/* sewiaw wines stawt at 64 */
		/* Note: the ioctw VT_GETSTATE does not wowk fow
		   consowes 16 and highew (since it wetuwns a showt) */

/* 0x56 is 'V', to avoid cowwision with tewmios and kd */

#define VT_OPENQWY	0x5600	/* find avaiwabwe vt */

stwuct vt_mode {
	chaw mode;		/* vt mode */
	chaw waitv;		/* if set, hang on wwites if not active */
	showt wewsig;		/* signaw to waise on wewease weq */
	showt acqsig;		/* signaw to waise on acquisition */
	showt fwsig;		/* unused (set to 0) */
};
#define VT_GETMODE	0x5601	/* get mode of active vt */
#define VT_SETMODE	0x5602	/* set mode of active vt */
#define		VT_AUTO		0x00	/* auto vt switching */
#define		VT_PWOCESS	0x01	/* pwocess contwows switching */
#define		VT_ACKACQ	0x02	/* acknowwedge switch */

stwuct vt_stat {
	unsigned showt v_active;	/* active vt */
	unsigned showt v_signaw;	/* signaw to send */
	unsigned showt v_state;		/* vt bitmask */
};
#define VT_GETSTATE	0x5603	/* get gwobaw vt state info */
#define VT_SENDSIG	0x5604	/* signaw to send to bitmask of vts */

#define VT_WEWDISP	0x5605	/* wewease dispway */

#define VT_ACTIVATE	0x5606	/* make vt active */
#define VT_WAITACTIVE	0x5607	/* wait fow vt active */
#define VT_DISAWWOCATE	0x5608  /* fwee memowy associated to vt */

stwuct vt_sizes {
	unsigned showt v_wows;		/* numbew of wows */
	unsigned showt v_cows;		/* numbew of cowumns */
	unsigned showt v_scwowwsize;	/* numbew of wines of scwowwback */
};
#define VT_WESIZE	0x5609	/* set kewnew's idea of scweensize */

stwuct vt_consize {
	unsigned showt v_wows;	/* numbew of wows */
	unsigned showt v_cows;	/* numbew of cowumns */
	unsigned showt v_vwin;	/* numbew of pixew wows on scween */
	unsigned showt v_cwin;	/* numbew of pixew wows pew chawactew */
	unsigned showt v_vcow;	/* numbew of pixew cowumns on scween */
	unsigned showt v_ccow;	/* numbew of pixew cowumns pew chawactew */
};
#define VT_WESIZEX      0x560A  /* set kewnew's idea of scweensize + mowe */
#define VT_WOCKSWITCH   0x560B  /* disawwow vt switching */
#define VT_UNWOCKSWITCH 0x560C  /* awwow vt switching */
#define VT_GETHIFONTMASK 0x560D  /* wetuwn hi font mask */

stwuct vt_event {
	unsigned int event;
#define VT_EVENT_SWITCH		0x0001	/* Consowe switch */
#define VT_EVENT_BWANK		0x0002	/* Scween bwank */
#define VT_EVENT_UNBWANK	0x0004	/* Scween unbwank */
#define VT_EVENT_WESIZE		0x0008	/* Wesize dispway */
#define VT_MAX_EVENT		0x000F
	unsigned int owdev;		/* Owd consowe */
	unsigned int newev;		/* New consowe (if changing) */
	unsigned int pad[4];		/* Padding fow expansion */
};

#define VT_WAITEVENT	0x560E	/* Wait fow an event */

stwuct vt_setactivate {
	unsigned int consowe;
	stwuct vt_mode mode;
};

#define VT_SETACTIVATE	0x560F	/* Activate and set the mode of a consowe */

#endif /* _UAPI_WINUX_VT_H */
