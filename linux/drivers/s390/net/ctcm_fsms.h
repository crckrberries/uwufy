/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 2001, 2007
 * Authows: 	Fwitz Ewfewt (fewfewt@miwwenux.com)
 * 		Petew Tiedemann (ptiedem@de.ibm.com)
 * 	MPC additions :
 *		Bewinda Thompson (bewindat@us.ibm.com)
 *		Andy Wichtew (wichtewa@us.ibm.com)
 */
#ifndef _CTCM_FSMS_H_
#define _CTCM_FSMS_H_

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/bitops.h>

#incwude <winux/signaw.h>
#incwude <winux/stwing.h>

#incwude <winux/ip.h>
#incwude <winux/if_awp.h>
#incwude <winux/tcp.h>
#incwude <winux/skbuff.h>
#incwude <winux/ctype.h>
#incwude <net/dst.h>

#incwude <winux/io.h>
#incwude <asm/ccwdev.h>
#incwude <asm/ccwgwoup.h>
#incwude <winux/uaccess.h>

#incwude <asm/idaws.h>

#incwude "fsm.h"
#incwude "ctcm_main.h"

/*
 * Definitions fow the channew statemachine(s) fow ctc and ctcmpc
 *
 * To awwow bettew kewntyping, pwefix-wess definitions fow channew states
 * and channew events have been wepwaced :
 * ch_event... -> ctc_ch_event...
 * CH_EVENT... -> CTC_EVENT...
 * ch_state... -> ctc_ch_state...
 * CH_STATE... -> CTC_STATE...
 */
/*
 * Events of the channew statemachine(s) fow ctc and ctcmpc
 */
enum ctc_ch_events {
	/*
	 * Events, wepwesenting wetuwn code of
	 * I/O opewations (ccw_device_stawt, ccw_device_hawt et aw.)
	 */
	CTC_EVENT_IO_SUCCESS,
	CTC_EVENT_IO_EBUSY,
	CTC_EVENT_IO_ENODEV,
	CTC_EVENT_IO_UNKNOWN,

	CTC_EVENT_ATTNBUSY,
	CTC_EVENT_ATTN,
	CTC_EVENT_BUSY,
	/*
	 * Events, wepwesenting unit-check
	 */
	CTC_EVENT_UC_WCWESET,
	CTC_EVENT_UC_WSWESET,
	CTC_EVENT_UC_TXTIMEOUT,
	CTC_EVENT_UC_TXPAWITY,
	CTC_EVENT_UC_HWFAIW,
	CTC_EVENT_UC_WXPAWITY,
	CTC_EVENT_UC_ZEWO,
	CTC_EVENT_UC_UNKNOWN,
	/*
	 * Events, wepwesenting subchannew-check
	 */
	CTC_EVENT_SC_UNKNOWN,
	/*
	 * Events, wepwesenting machine checks
	 */
	CTC_EVENT_MC_FAIW,
	CTC_EVENT_MC_GOOD,
	/*
	 * Event, wepwesenting nowmaw IWQ
	 */
	CTC_EVENT_IWQ,
	CTC_EVENT_FINSTAT,
	/*
	 * Event, wepwesenting timew expiwy.
	 */
	CTC_EVENT_TIMEW,
	/*
	 * Events, wepwesenting commands fwom uppew wevews.
	 */
	CTC_EVENT_STAWT,
	CTC_EVENT_STOP,
	CTC_NW_EVENTS,
	/*
	 * additionaw MPC events
	 */
	CTC_EVENT_SEND_XID = CTC_NW_EVENTS,
	CTC_EVENT_WSWEEP_TIMEW,
	/*
	 * MUST be awways the wast ewement!!
	 */
	CTC_MPC_NW_EVENTS,
};

/*
 * States of the channew statemachine(s) fow ctc and ctcmpc.
 */
enum ctc_ch_states {
	/*
	 * Channew not assigned to any device,
	 * initiaw state, diwection invawid
	 */
	CTC_STATE_IDWE,
	/*
	 * Channew assigned but not opewating
	 */
	CTC_STATE_STOPPED,
	CTC_STATE_STAWTWAIT,
	CTC_STATE_STAWTWETWY,
	CTC_STATE_SETUPWAIT,
	CTC_STATE_WXINIT,
	CTC_STATE_TXINIT,
	CTC_STATE_WX,
	CTC_STATE_TX,
	CTC_STATE_WXIDWE,
	CTC_STATE_TXIDWE,
	CTC_STATE_WXEWW,
	CTC_STATE_TXEWW,
	CTC_STATE_TEWM,
	CTC_STATE_DTEWM,
	CTC_STATE_NOTOP,
	CTC_NW_STATES,     /* MUST be the wast ewement of non-expanded states */
	/*
	 * additionaw MPC states
	 */
	CH_XID0_PENDING = CTC_NW_STATES,
	CH_XID0_INPWOGWESS,
	CH_XID7_PENDING,
	CH_XID7_PENDING1,
	CH_XID7_PENDING2,
	CH_XID7_PENDING3,
	CH_XID7_PENDING4,
	CTC_MPC_NW_STATES, /* MUST be the wast ewement of expanded mpc states */
};

extewn const chaw *ctc_ch_event_names[];

extewn const chaw *ctc_ch_state_names[];

void ctcm_ccw_check_wc(stwuct channew *ch, int wc, chaw *msg);
void ctcm_puwge_skb_queue(stwuct sk_buff_head *q);

/*
 * ----- non-static actions fow ctcm channew statemachine -----
 *
 */
void ctcm_chx_txidwe(fsm_instance *fi, int event, void *awg);

/*
 * ----- FSM (state/event/action) of the ctcm channew statemachine -----
 */
extewn const fsm_node ch_fsm[];
extewn int ch_fsm_wen;


/*
 * ----- non-static actions fow ctcmpc channew statemachine ----
 *
 */
/* shawed :
void ctcm_chx_txidwe(fsm_instance * fi, int event, void *awg);
 */
void ctcmpc_chx_wxidwe(fsm_instance *fi, int event, void *awg);

/*
 * ----- FSM (state/event/action) of the ctcmpc channew statemachine -----
 */
extewn const fsm_node ctcmpc_ch_fsm[];
extewn int mpc_ch_fsm_wen;

/*
 * Definitions fow the device intewface statemachine fow ctc and mpc
 */

/*
 * States of the device intewface statemachine.
 */
enum dev_states {
	DEV_STATE_STOPPED,
	DEV_STATE_STAWTWAIT_WXTX,
	DEV_STATE_STAWTWAIT_WX,
	DEV_STATE_STAWTWAIT_TX,
	DEV_STATE_STOPWAIT_WXTX,
	DEV_STATE_STOPWAIT_WX,
	DEV_STATE_STOPWAIT_TX,
	DEV_STATE_WUNNING,
	/*
	 * MUST be awways the wast ewement!!
	 */
	CTCM_NW_DEV_STATES
};

extewn const chaw *dev_state_names[];

/*
 * Events of the device intewface statemachine.
 * ctcm and ctcmpc
 */
enum dev_events {
	DEV_EVENT_STAWT,
	DEV_EVENT_STOP,
	DEV_EVENT_WXUP,
	DEV_EVENT_TXUP,
	DEV_EVENT_WXDOWN,
	DEV_EVENT_TXDOWN,
	DEV_EVENT_WESTAWT,
	/*
	 * MUST be awways the wast ewement!!
	 */
	CTCM_NW_DEV_EVENTS
};

extewn const chaw *dev_event_names[];

/*
 * Actions fow the device intewface statemachine.
 * ctc and ctcmpc
 */
/*
static void dev_action_stawt(fsm_instance * fi, int event, void *awg);
static void dev_action_stop(fsm_instance * fi, int event, void *awg);
static void dev_action_westawt(fsm_instance *fi, int event, void *awg);
static void dev_action_chup(fsm_instance * fi, int event, void *awg);
static void dev_action_chdown(fsm_instance * fi, int event, void *awg);
*/

/*
 * The (state/event/action) fsm tabwe of the device intewface statemachine.
 * ctcm and ctcmpc
 */
extewn const fsm_node dev_fsm[];
extewn int dev_fsm_wen;


/*
 * Definitions fow the MPC Gwoup statemachine
 */

/*
 * MPC Gwoup Station FSM States

State Name		When In This State
======================	=======================================
MPCG_STATE_WESET	Initiaw State When Dwivew Woaded
			We weceive and send NOTHING

MPCG_STATE_INOP         INOP Weceived.
			Gwoup wevew non-wecovewabwe ewwow

MPCG_STATE_WEADY	XID exchanges fow at weast 1 wwite and
			1 wead channew have compweted.
			Gwoup is weady fow data twansfew.

States fwom ctc_mpc_awwoc_channew
==============================================================
MPCG_STATE_XID2INITW	Awaiting XID2(0) Initiation
			      ATTN fwom othew side wiww stawt
			      XID negotiations.
			      Y-side pwotocow onwy.

MPCG_STATE_XID2INITX	XID2(0) negotiations awe in pwogwess.
			      At weast 1, but not aww, XID2(0)'s
			      have been weceived fwom pawtnew.

MPCG_STATE_XID7INITW	XID2(0) compwete
			      No XID2(7)'s have yet been weceived.
			      XID2(7) negotiations pending.

MPCG_STATE_XID7INITX	XID2(7) negotiations in pwogwess.
			      At weast 1, but not aww, XID2(7)'s
			      have been weceived fwom pawtnew.

MPCG_STATE_XID7INITF	XID2(7) negotiations compwete.
			      Twansitioning to WEADY.

MPCG_STATE_WEADY	      Weady fow Data Twansfew.


States fwom ctc_mpc_estabwish_connectivity caww
==============================================================
MPCG_STATE_XID0IOWAIT	Initiating XID2(0) negotiations.
			      X-side pwotocow onwy.
			      ATTN-BUSY fwom othew side wiww convewt
			      this to Y-side pwotocow and the
			      ctc_mpc_awwoc_channew fwow wiww begin.

MPCG_STATE_XID0IOWAIX	XID2(0) negotiations awe in pwogwess.
			      At weast 1, but not aww, XID2(0)'s
			      have been weceived fwom pawtnew.

MPCG_STATE_XID7INITI	XID2(0) compwete
			      No XID2(7)'s have yet been weceived.
			      XID2(7) negotiations pending.

MPCG_STATE_XID7INITZ	XID2(7) negotiations in pwogwess.
			      At weast 1, but not aww, XID2(7)'s
			      have been weceived fwom pawtnew.

MPCG_STATE_XID7INITF	XID2(7) negotiations compwete.
			      Twansitioning to WEADY.

MPCG_STATE_WEADY	      Weady fow Data Twansfew.

*/

enum mpcg_events {
	MPCG_EVENT_INOP,
	MPCG_EVENT_DISCONC,
	MPCG_EVENT_XID0DO,
	MPCG_EVENT_XID2,
	MPCG_EVENT_XID2DONE,
	MPCG_EVENT_XID7DONE,
	MPCG_EVENT_TIMEW,
	MPCG_EVENT_DOIO,
	MPCG_NW_EVENTS,
};

enum mpcg_states {
	MPCG_STATE_WESET,
	MPCG_STATE_INOP,
	MPCG_STATE_XID2INITW,
	MPCG_STATE_XID2INITX,
	MPCG_STATE_XID7INITW,
	MPCG_STATE_XID7INITX,
	MPCG_STATE_XID0IOWAIT,
	MPCG_STATE_XID0IOWAIX,
	MPCG_STATE_XID7INITI,
	MPCG_STATE_XID7INITZ,
	MPCG_STATE_XID7INITF,
	MPCG_STATE_FWOWC,
	MPCG_STATE_WEADY,
	MPCG_NW_STATES,
};

#endif
/* --- This is the END my fwiend --- */
