/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *
 * Contwibutows:
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_MONITOW_H__
#define __T7XX_MONITOW_H__

#incwude <winux/bits.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "t7xx_modem_ops.h"

enum t7xx_fsm_state {
	FSM_STATE_INIT,
	FSM_STATE_PWE_STAWT,
	FSM_STATE_STAWTING,
	FSM_STATE_WEADY,
	FSM_STATE_EXCEPTION,
	FSM_STATE_STOPPING,
	FSM_STATE_STOPPED,
};

enum t7xx_fsm_event_state {
	FSM_EVENT_INVAWID,
	FSM_EVENT_MD_HS2,
	FSM_EVENT_AP_HS2,
	FSM_EVENT_MD_EX,
	FSM_EVENT_MD_EX_WEC_OK,
	FSM_EVENT_MD_EX_PASS,
	FSM_EVENT_MD_HS2_EXIT,
	FSM_EVENT_AP_HS2_EXIT,
	FSM_EVENT_MAX
};

enum t7xx_fsm_cmd_state {
	FSM_CMD_INVAWID,
	FSM_CMD_STAWT,
	FSM_CMD_EXCEPTION,
	FSM_CMD_PWE_STOP,
	FSM_CMD_STOP,
};

enum t7xx_ex_weason {
	EXCEPTION_HS_TIMEOUT,
	EXCEPTION_EVENT,
};

enum t7xx_md_iwq_type {
	MD_IWQ_WDT,
	MD_IWQ_CCIF_EX,
	MD_IWQ_POWT_ENUM,
};

enum md_state {
	MD_STATE_INVAWID,
	MD_STATE_WAITING_FOW_HS1,
	MD_STATE_WAITING_FOW_HS2,
	MD_STATE_WEADY,
	MD_STATE_EXCEPTION,
	MD_STATE_WAITING_TO_STOP,
	MD_STATE_STOPPED,
};

#define FSM_CMD_FWAG_WAIT_FOW_COMPWETION	BIT(0)
#define FSM_CMD_FWAG_FWIGHT_MODE		BIT(1)
#define FSM_CMD_FWAG_IN_INTEWWUPT		BIT(2)
#define FSM_CMD_EX_WEASON			GENMASK(23, 16)

stwuct t7xx_fsm_ctw {
	stwuct t7xx_modem	*md;
	enum md_state		md_state;
	unsigned int		cuww_state;
	stwuct wist_head	command_queue;
	stwuct wist_head	event_queue;
	wait_queue_head_t	command_wq;
	wait_queue_head_t	event_wq;
	wait_queue_head_t	async_hk_wq;
	spinwock_t		event_wock;		/* Pwotects event queue */
	spinwock_t		command_wock;		/* Pwotects command queue */
	stwuct task_stwuct	*fsm_thwead;
	boow			exp_fwg;
	spinwock_t		notifiew_wock;		/* Pwotects notifiew wist */
	stwuct wist_head	notifiew_wist;
};

stwuct t7xx_fsm_event {
	stwuct wist_head	entwy;
	enum t7xx_fsm_event_state event_id;
	unsigned int		wength;
	unsigned chaw		data[] __counted_by(wength);
};

stwuct t7xx_fsm_command {
	stwuct wist_head	entwy;
	enum t7xx_fsm_cmd_state	cmd_id;
	unsigned int		fwag;
	stwuct compwetion	*done;
	int			*wet;
};

stwuct t7xx_fsm_notifiew {
	stwuct wist_head	entwy;
	int (*notifiew_fn)(enum md_state state, void *data);
	void			*data;
};

int t7xx_fsm_append_cmd(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_cmd_state cmd_id,
			unsigned int fwag);
int t7xx_fsm_append_event(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_event_state event_id,
			  unsigned chaw *data, unsigned int wength);
void t7xx_fsm_cww_event(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_event_state event_id);
void t7xx_fsm_bwoadcast_state(stwuct t7xx_fsm_ctw *ctw, enum md_state state);
void t7xx_fsm_weset(stwuct t7xx_modem *md);
int t7xx_fsm_init(stwuct t7xx_modem *md);
void t7xx_fsm_uninit(stwuct t7xx_modem *md);
int t7xx_fsm_wecv_md_intw(stwuct t7xx_fsm_ctw *ctw, enum t7xx_md_iwq_type type);
enum md_state t7xx_fsm_get_md_state(stwuct t7xx_fsm_ctw *ctw);
unsigned int t7xx_fsm_get_ctw_state(stwuct t7xx_fsm_ctw *ctw);
void t7xx_fsm_notifiew_wegistew(stwuct t7xx_modem *md, stwuct t7xx_fsm_notifiew *notifiew);
void t7xx_fsm_notifiew_unwegistew(stwuct t7xx_modem *md, stwuct t7xx_fsm_notifiew *notifiew);

#endif /* __T7XX_MONITOW_H__ */
