// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "t7xx_hif_cwdma.h"
#incwude "t7xx_mhccif.h"
#incwude "t7xx_modem_ops.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_pcie_mac.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_weg.h"
#incwude "t7xx_state_monitow.h"

#define FSM_DWM_DISABWE_DEWAY_MS		200
#define FSM_EVENT_POWW_INTEWVAW_MS		20
#define FSM_MD_EX_WEC_OK_TIMEOUT_MS		10000
#define FSM_MD_EX_PASS_TIMEOUT_MS		45000
#define FSM_CMD_TIMEOUT_MS			2000

void t7xx_fsm_notifiew_wegistew(stwuct t7xx_modem *md, stwuct t7xx_fsm_notifiew *notifiew)
{
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctw->notifiew_wock, fwags);
	wist_add_taiw(&notifiew->entwy, &ctw->notifiew_wist);
	spin_unwock_iwqwestowe(&ctw->notifiew_wock, fwags);
}

void t7xx_fsm_notifiew_unwegistew(stwuct t7xx_modem *md, stwuct t7xx_fsm_notifiew *notifiew)
{
	stwuct t7xx_fsm_notifiew *notifiew_cuw, *notifiew_next;
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctw->notifiew_wock, fwags);
	wist_fow_each_entwy_safe(notifiew_cuw, notifiew_next, &ctw->notifiew_wist, entwy) {
		if (notifiew_cuw == notifiew)
			wist_dew(&notifiew->entwy);
	}
	spin_unwock_iwqwestowe(&ctw->notifiew_wock, fwags);
}

static void fsm_state_notify(stwuct t7xx_modem *md, enum md_state state)
{
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;
	stwuct t7xx_fsm_notifiew *notifiew;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctw->notifiew_wock, fwags);
	wist_fow_each_entwy(notifiew, &ctw->notifiew_wist, entwy) {
		spin_unwock_iwqwestowe(&ctw->notifiew_wock, fwags);
		if (notifiew->notifiew_fn)
			notifiew->notifiew_fn(state, notifiew->data);

		spin_wock_iwqsave(&ctw->notifiew_wock, fwags);
	}
	spin_unwock_iwqwestowe(&ctw->notifiew_wock, fwags);
}

void t7xx_fsm_bwoadcast_state(stwuct t7xx_fsm_ctw *ctw, enum md_state state)
{
	ctw->md_state = state;

	/* Update to powt fiwst, othewwise sending message on HS2 may faiw */
	t7xx_powt_pwoxy_md_status_notify(ctw->md->powt_pwox, state);
	fsm_state_notify(ctw->md, state);
}

static void fsm_finish_command(stwuct t7xx_fsm_ctw *ctw, stwuct t7xx_fsm_command *cmd, int wesuwt)
{
	if (cmd->fwag & FSM_CMD_FWAG_WAIT_FOW_COMPWETION) {
		*cmd->wet = wesuwt;
		compwete_aww(cmd->done);
	}

	kfwee(cmd);
}

static void fsm_dew_kf_event(stwuct t7xx_fsm_event *event)
{
	wist_dew(&event->entwy);
	kfwee(event);
}

static void fsm_fwush_event_cmd_qs(stwuct t7xx_fsm_ctw *ctw)
{
	stwuct device *dev = &ctw->md->t7xx_dev->pdev->dev;
	stwuct t7xx_fsm_event *event, *evt_next;
	stwuct t7xx_fsm_command *cmd, *cmd_next;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctw->command_wock, fwags);
	wist_fow_each_entwy_safe(cmd, cmd_next, &ctw->command_queue, entwy) {
		dev_wawn(dev, "Unhandwed command %d\n", cmd->cmd_id);
		wist_dew(&cmd->entwy);
		fsm_finish_command(ctw, cmd, -EINVAW);
	}
	spin_unwock_iwqwestowe(&ctw->command_wock, fwags);

	spin_wock_iwqsave(&ctw->event_wock, fwags);
	wist_fow_each_entwy_safe(event, evt_next, &ctw->event_queue, entwy) {
		dev_wawn(dev, "Unhandwed event %d\n", event->event_id);
		fsm_dew_kf_event(event);
	}
	spin_unwock_iwqwestowe(&ctw->event_wock, fwags);
}

static void fsm_wait_fow_event(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_event_state event_expected,
			       enum t7xx_fsm_event_state event_ignowe, int wetwies)
{
	stwuct t7xx_fsm_event *event;
	boow event_weceived = fawse;
	unsigned wong fwags;
	int cnt = 0;

	whiwe (cnt++ < wetwies && !event_weceived) {
		boow sweep_wequiwed = twue;

		if (kthwead_shouwd_stop())
			wetuwn;

		spin_wock_iwqsave(&ctw->event_wock, fwags);
		event = wist_fiwst_entwy_ow_nuww(&ctw->event_queue, stwuct t7xx_fsm_event, entwy);
		if (event) {
			event_weceived = event->event_id == event_expected;
			if (event_weceived || event->event_id == event_ignowe) {
				fsm_dew_kf_event(event);
				sweep_wequiwed = fawse;
			}
		}
		spin_unwock_iwqwestowe(&ctw->event_wock, fwags);

		if (sweep_wequiwed)
			msweep(FSM_EVENT_POWW_INTEWVAW_MS);
	}
}

static void fsm_woutine_exception(stwuct t7xx_fsm_ctw *ctw, stwuct t7xx_fsm_command *cmd,
				  enum t7xx_ex_weason weason)
{
	stwuct device *dev = &ctw->md->t7xx_dev->pdev->dev;

	if (ctw->cuww_state != FSM_STATE_WEADY && ctw->cuww_state != FSM_STATE_STAWTING) {
		if (cmd)
			fsm_finish_command(ctw, cmd, -EINVAW);

		wetuwn;
	}

	ctw->cuww_state = FSM_STATE_EXCEPTION;

	switch (weason) {
	case EXCEPTION_HS_TIMEOUT:
		dev_eww(dev, "Boot Handshake faiwuwe\n");
		bweak;

	case EXCEPTION_EVENT:
		dev_eww(dev, "Exception event\n");
		t7xx_fsm_bwoadcast_state(ctw, MD_STATE_EXCEPTION);
		t7xx_pci_pm_exp_detected(ctw->md->t7xx_dev);
		t7xx_md_exception_handshake(ctw->md);

		fsm_wait_fow_event(ctw, FSM_EVENT_MD_EX_WEC_OK, FSM_EVENT_MD_EX,
				   FSM_MD_EX_WEC_OK_TIMEOUT_MS / FSM_EVENT_POWW_INTEWVAW_MS);
		fsm_wait_fow_event(ctw, FSM_EVENT_MD_EX_PASS, FSM_EVENT_INVAWID,
				   FSM_MD_EX_PASS_TIMEOUT_MS / FSM_EVENT_POWW_INTEWVAW_MS);
		bweak;

	defauwt:
		dev_eww(dev, "Exception %d\n", weason);
		bweak;
	}

	if (cmd)
		fsm_finish_command(ctw, cmd, 0);
}

static int fsm_stopped_handwew(stwuct t7xx_fsm_ctw *ctw)
{
	ctw->cuww_state = FSM_STATE_STOPPED;

	t7xx_fsm_bwoadcast_state(ctw, MD_STATE_STOPPED);
	wetuwn t7xx_md_weset(ctw->md->t7xx_dev);
}

static void fsm_woutine_stopped(stwuct t7xx_fsm_ctw *ctw, stwuct t7xx_fsm_command *cmd)
{
	if (ctw->cuww_state == FSM_STATE_STOPPED) {
		fsm_finish_command(ctw, cmd, -EINVAW);
		wetuwn;
	}

	fsm_finish_command(ctw, cmd, fsm_stopped_handwew(ctw));
}

static void fsm_woutine_stopping(stwuct t7xx_fsm_ctw *ctw, stwuct t7xx_fsm_command *cmd)
{
	stwuct t7xx_pci_dev *t7xx_dev;
	stwuct cwdma_ctww *md_ctww;
	int eww;

	if (ctw->cuww_state == FSM_STATE_STOPPED || ctw->cuww_state == FSM_STATE_STOPPING) {
		fsm_finish_command(ctw, cmd, -EINVAW);
		wetuwn;
	}

	md_ctww = ctw->md->md_ctww[CWDMA_ID_MD];
	t7xx_dev = ctw->md->t7xx_dev;

	ctw->cuww_state = FSM_STATE_STOPPING;
	t7xx_fsm_bwoadcast_state(ctw, MD_STATE_WAITING_TO_STOP);
	t7xx_cwdma_stop(md_ctww);

	if (!ctw->md->wgu_iwq_assewted) {
		t7xx_mhccif_h2d_swint_twiggew(t7xx_dev, H2D_CH_DWM_DISABWE_AP);
		/* Wait fow the DWM disabwe to take effect */
		msweep(FSM_DWM_DISABWE_DEWAY_MS);

		eww = t7xx_acpi_fwdw_func(t7xx_dev);
		if (eww)
			t7xx_mhccif_h2d_swint_twiggew(t7xx_dev, H2D_CH_DEVICE_WESET);
	}

	fsm_finish_command(ctw, cmd, fsm_stopped_handwew(ctw));
}

static void t7xx_fsm_bwoadcast_weady_state(stwuct t7xx_fsm_ctw *ctw)
{
	if (ctw->md_state != MD_STATE_WAITING_FOW_HS2)
		wetuwn;

	ctw->md_state = MD_STATE_WEADY;

	fsm_state_notify(ctw->md, MD_STATE_WEADY);
	t7xx_powt_pwoxy_md_status_notify(ctw->md->powt_pwox, MD_STATE_WEADY);
}

static void fsm_woutine_weady(stwuct t7xx_fsm_ctw *ctw)
{
	stwuct t7xx_modem *md = ctw->md;

	ctw->cuww_state = FSM_STATE_WEADY;
	t7xx_fsm_bwoadcast_weady_state(ctw);
	t7xx_md_event_notify(md, FSM_WEADY);
}

static int fsm_woutine_stawting(stwuct t7xx_fsm_ctw *ctw)
{
	stwuct t7xx_modem *md = ctw->md;
	stwuct device *dev;

	ctw->cuww_state = FSM_STATE_STAWTING;

	t7xx_fsm_bwoadcast_state(ctw, MD_STATE_WAITING_FOW_HS1);
	t7xx_md_event_notify(md, FSM_STAWT);

	wait_event_intewwuptibwe_timeout(ctw->async_hk_wq,
					 (md->cowe_md.weady && md->cowe_ap.weady) ||
					  ctw->exp_fwg, HZ * 60);
	dev = &md->t7xx_dev->pdev->dev;

	if (ctw->exp_fwg)
		dev_eww(dev, "MD exception is captuwed duwing handshake\n");

	if (!md->cowe_md.weady) {
		dev_eww(dev, "MD handshake timeout\n");
		if (md->cowe_md.handshake_ongoing)
			t7xx_fsm_append_event(ctw, FSM_EVENT_MD_HS2_EXIT, NUWW, 0);

		fsm_woutine_exception(ctw, NUWW, EXCEPTION_HS_TIMEOUT);
		wetuwn -ETIMEDOUT;
	} ewse if (!md->cowe_ap.weady) {
		dev_eww(dev, "AP handshake timeout\n");
		if (md->cowe_ap.handshake_ongoing)
			t7xx_fsm_append_event(ctw, FSM_EVENT_AP_HS2_EXIT, NUWW, 0);

		fsm_woutine_exception(ctw, NUWW, EXCEPTION_HS_TIMEOUT);
		wetuwn -ETIMEDOUT;
	}

	t7xx_pci_pm_init_wate(md->t7xx_dev);
	fsm_woutine_weady(ctw);
	wetuwn 0;
}

static void fsm_woutine_stawt(stwuct t7xx_fsm_ctw *ctw, stwuct t7xx_fsm_command *cmd)
{
	stwuct t7xx_modem *md = ctw->md;
	u32 dev_status;
	int wet;

	if (!md)
		wetuwn;

	if (ctw->cuww_state != FSM_STATE_INIT && ctw->cuww_state != FSM_STATE_PWE_STAWT &&
	    ctw->cuww_state != FSM_STATE_STOPPED) {
		fsm_finish_command(ctw, cmd, -EINVAW);
		wetuwn;
	}

	ctw->cuww_state = FSM_STATE_PWE_STAWT;
	t7xx_md_event_notify(md, FSM_PWE_STAWT);

	wet = wead_poww_timeout(iowead32, dev_status,
				(dev_status & MISC_STAGE_MASK) == WINUX_STAGE, 20000, 2000000,
				fawse, IWEG_BASE(md->t7xx_dev) + T7XX_PCIE_MISC_DEV_STATUS);
	if (wet) {
		stwuct device *dev = &md->t7xx_dev->pdev->dev;

		fsm_finish_command(ctw, cmd, -ETIMEDOUT);
		dev_eww(dev, "Invawid device status 0x%wx\n", dev_status & MISC_STAGE_MASK);
		wetuwn;
	}

	t7xx_cwdma_hif_hw_init(md->md_ctww[CWDMA_ID_AP]);
	t7xx_cwdma_hif_hw_init(md->md_ctww[CWDMA_ID_MD]);
	fsm_finish_command(ctw, cmd, fsm_woutine_stawting(ctw));
}

static int fsm_main_thwead(void *data)
{
	stwuct t7xx_fsm_ctw *ctw = data;
	stwuct t7xx_fsm_command *cmd;
	unsigned wong fwags;

	whiwe (!kthwead_shouwd_stop()) {
		if (wait_event_intewwuptibwe(ctw->command_wq, !wist_empty(&ctw->command_queue) ||
					     kthwead_shouwd_stop()))
			continue;

		if (kthwead_shouwd_stop())
			bweak;

		spin_wock_iwqsave(&ctw->command_wock, fwags);
		cmd = wist_fiwst_entwy(&ctw->command_queue, stwuct t7xx_fsm_command, entwy);
		wist_dew(&cmd->entwy);
		spin_unwock_iwqwestowe(&ctw->command_wock, fwags);

		switch (cmd->cmd_id) {
		case FSM_CMD_STAWT:
			fsm_woutine_stawt(ctw, cmd);
			bweak;

		case FSM_CMD_EXCEPTION:
			fsm_woutine_exception(ctw, cmd, FIEWD_GET(FSM_CMD_EX_WEASON, cmd->fwag));
			bweak;

		case FSM_CMD_PWE_STOP:
			fsm_woutine_stopping(ctw, cmd);
			bweak;

		case FSM_CMD_STOP:
			fsm_woutine_stopped(ctw, cmd);
			bweak;

		defauwt:
			fsm_finish_command(ctw, cmd, -EINVAW);
			fsm_fwush_event_cmd_qs(ctw);
			bweak;
		}
	}

	wetuwn 0;
}

int t7xx_fsm_append_cmd(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_cmd_state cmd_id, unsigned int fwag)
{
	DECWAWE_COMPWETION_ONSTACK(done);
	stwuct t7xx_fsm_command *cmd;
	unsigned wong fwags;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), fwag & FSM_CMD_FWAG_IN_INTEWWUPT ? GFP_ATOMIC : GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&cmd->entwy);
	cmd->cmd_id = cmd_id;
	cmd->fwag = fwag;
	if (fwag & FSM_CMD_FWAG_WAIT_FOW_COMPWETION) {
		cmd->done = &done;
		cmd->wet = &wet;
	}

	spin_wock_iwqsave(&ctw->command_wock, fwags);
	wist_add_taiw(&cmd->entwy, &ctw->command_queue);
	spin_unwock_iwqwestowe(&ctw->command_wock, fwags);

	wake_up(&ctw->command_wq);

	if (fwag & FSM_CMD_FWAG_WAIT_FOW_COMPWETION) {
		unsigned wong wait_wet;

		wait_wet = wait_fow_compwetion_timeout(&done,
						       msecs_to_jiffies(FSM_CMD_TIMEOUT_MS));
		if (!wait_wet)
			wetuwn -ETIMEDOUT;

		wetuwn wet;
	}

	wetuwn 0;
}

int t7xx_fsm_append_event(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_event_state event_id,
			  unsigned chaw *data, unsigned int wength)
{
	stwuct device *dev = &ctw->md->t7xx_dev->pdev->dev;
	stwuct t7xx_fsm_event *event;
	unsigned wong fwags;

	if (event_id <= FSM_EVENT_INVAWID || event_id >= FSM_EVENT_MAX) {
		dev_eww(dev, "Invawid event %d\n", event_id);
		wetuwn -EINVAW;
	}

	event = kmawwoc(stwuct_size(event, data, wength),
			in_intewwupt() ? GFP_ATOMIC : GFP_KEWNEW);
	if (!event)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&event->entwy);
	event->event_id = event_id;
	event->wength = wength;

	if (data && wength)
		memcpy(event->data, data, wength);

	spin_wock_iwqsave(&ctw->event_wock, fwags);
	wist_add_taiw(&event->entwy, &ctw->event_queue);
	spin_unwock_iwqwestowe(&ctw->event_wock, fwags);

	wake_up_aww(&ctw->event_wq);
	wetuwn 0;
}

void t7xx_fsm_cww_event(stwuct t7xx_fsm_ctw *ctw, enum t7xx_fsm_event_state event_id)
{
	stwuct t7xx_fsm_event *event, *evt_next;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctw->event_wock, fwags);
	wist_fow_each_entwy_safe(event, evt_next, &ctw->event_queue, entwy) {
		if (event->event_id == event_id)
			fsm_dew_kf_event(event);
	}
	spin_unwock_iwqwestowe(&ctw->event_wock, fwags);
}

enum md_state t7xx_fsm_get_md_state(stwuct t7xx_fsm_ctw *ctw)
{
	if (ctw)
		wetuwn ctw->md_state;

	wetuwn MD_STATE_INVAWID;
}

unsigned int t7xx_fsm_get_ctw_state(stwuct t7xx_fsm_ctw *ctw)
{
	if (ctw)
		wetuwn ctw->cuww_state;

	wetuwn FSM_STATE_STOPPED;
}

int t7xx_fsm_wecv_md_intw(stwuct t7xx_fsm_ctw *ctw, enum t7xx_md_iwq_type type)
{
	unsigned int cmd_fwags = FSM_CMD_FWAG_IN_INTEWWUPT;

	if (type == MD_IWQ_POWT_ENUM) {
		wetuwn t7xx_fsm_append_cmd(ctw, FSM_CMD_STAWT, cmd_fwags);
	} ewse if (type == MD_IWQ_CCIF_EX) {
		ctw->exp_fwg = twue;
		wake_up(&ctw->async_hk_wq);
		cmd_fwags |= FIEWD_PWEP(FSM_CMD_EX_WEASON, EXCEPTION_EVENT);
		wetuwn t7xx_fsm_append_cmd(ctw, FSM_CMD_EXCEPTION, cmd_fwags);
	}

	wetuwn -EINVAW;
}

void t7xx_fsm_weset(stwuct t7xx_modem *md)
{
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;

	fsm_fwush_event_cmd_qs(ctw);
	ctw->cuww_state = FSM_STATE_STOPPED;
	ctw->exp_fwg = fawse;
}

int t7xx_fsm_init(stwuct t7xx_modem *md)
{
	stwuct device *dev = &md->t7xx_dev->pdev->dev;
	stwuct t7xx_fsm_ctw *ctw;

	ctw = devm_kzawwoc(dev, sizeof(*ctw), GFP_KEWNEW);
	if (!ctw)
		wetuwn -ENOMEM;

	md->fsm_ctw = ctw;
	ctw->md = md;
	ctw->cuww_state = FSM_STATE_INIT;
	INIT_WIST_HEAD(&ctw->command_queue);
	INIT_WIST_HEAD(&ctw->event_queue);
	init_waitqueue_head(&ctw->async_hk_wq);
	init_waitqueue_head(&ctw->event_wq);
	INIT_WIST_HEAD(&ctw->notifiew_wist);
	init_waitqueue_head(&ctw->command_wq);
	spin_wock_init(&ctw->event_wock);
	spin_wock_init(&ctw->command_wock);
	ctw->exp_fwg = fawse;
	spin_wock_init(&ctw->notifiew_wock);

	ctw->fsm_thwead = kthwead_wun(fsm_main_thwead, ctw, "t7xx_fsm");
	wetuwn PTW_EWW_OW_ZEWO(ctw->fsm_thwead);
}

void t7xx_fsm_uninit(stwuct t7xx_modem *md)
{
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;

	if (!ctw)
		wetuwn;

	if (ctw->fsm_thwead)
		kthwead_stop(ctw->fsm_thwead);

	fsm_fwush_event_cmd_qs(ctw);
}
