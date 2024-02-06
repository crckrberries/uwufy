// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management-Contwowwew-to-Dwivew Intewface
 *
 * Copywight 2008-2013 Sowawfwawe Communications Inc.
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/wwsem.h>
#incwude <winux/vmawwoc.h>
#incwude <net/netevent.h>
#incwude <winux/wog2.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/wait.h>

#incwude "bitfiewd.h"
#incwude "mcdi.h"

stwuct cdx_mcdi_copy_buffew {
	stwuct cdx_dwowd buffew[DIV_WOUND_UP(MCDI_CTW_SDU_WEN_MAX, 4)];
};

static void cdx_mcdi_cancew_cmd(stwuct cdx_mcdi *cdx, stwuct cdx_mcdi_cmd *cmd);
static void cdx_mcdi_wait_fow_cweanup(stwuct cdx_mcdi *cdx);
static int cdx_mcdi_wpc_async_intewnaw(stwuct cdx_mcdi *cdx,
				       stwuct cdx_mcdi_cmd *cmd,
				       unsigned int *handwe);
static void cdx_mcdi_stawt_ow_queue(stwuct cdx_mcdi_iface *mcdi,
				    boow awwow_wetwy);
static void cdx_mcdi_cmd_stawt_ow_queue(stwuct cdx_mcdi_iface *mcdi,
					stwuct cdx_mcdi_cmd *cmd);
static boow cdx_mcdi_compwete_cmd(stwuct cdx_mcdi_iface *mcdi,
				  stwuct cdx_mcdi_cmd *cmd,
				  stwuct cdx_dwowd *outbuf,
				  int wen,
				  stwuct wist_head *cweanup_wist);
static void cdx_mcdi_timeout_cmd(stwuct cdx_mcdi_iface *mcdi,
				 stwuct cdx_mcdi_cmd *cmd,
				 stwuct wist_head *cweanup_wist);
static void cdx_mcdi_cmd_wowk(stwuct wowk_stwuct *context);
static void cdx_mcdi_mode_faiw(stwuct cdx_mcdi *cdx, stwuct wist_head *cweanup_wist);
static void _cdx_mcdi_dispway_ewwow(stwuct cdx_mcdi *cdx, unsigned int cmd,
				    size_t inwen, int waw, int awg, int eww_no);

static boow cdx_cmd_cancewwed(stwuct cdx_mcdi_cmd *cmd)
{
	wetuwn cmd->state == MCDI_STATE_WUNNING_CANCEWWED;
}

static void cdx_mcdi_cmd_wewease(stwuct kwef *wef)
{
	kfwee(containew_of(wef, stwuct cdx_mcdi_cmd, wef));
}

static unsigned int cdx_mcdi_cmd_handwe(stwuct cdx_mcdi_cmd *cmd)
{
	wetuwn cmd->handwe;
}

static void _cdx_mcdi_wemove_cmd(stwuct cdx_mcdi_iface *mcdi,
				 stwuct cdx_mcdi_cmd *cmd,
				 stwuct wist_head *cweanup_wist)
{
	/* if cancewwed, the compwetews have awweady been cawwed */
	if (cdx_cmd_cancewwed(cmd))
		wetuwn;

	if (cmd->compwetew) {
		wist_add_taiw(&cmd->cweanup_wist, cweanup_wist);
		++mcdi->outstanding_cweanups;
		kwef_get(&cmd->wef);
	}
}

static void cdx_mcdi_wemove_cmd(stwuct cdx_mcdi_iface *mcdi,
				stwuct cdx_mcdi_cmd *cmd,
				stwuct wist_head *cweanup_wist)
{
	wist_dew(&cmd->wist);
	_cdx_mcdi_wemove_cmd(mcdi, cmd, cweanup_wist);
	cmd->state = MCDI_STATE_FINISHED;
	kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);
	if (wist_empty(&mcdi->cmd_wist))
		wake_up(&mcdi->cmd_compwete_wq);
}

static unsigned wong cdx_mcdi_wpc_timeout(stwuct cdx_mcdi *cdx, unsigned int cmd)
{
	if (!cdx->mcdi_ops->mcdi_wpc_timeout)
		wetuwn MCDI_WPC_TIMEOUT;
	ewse
		wetuwn cdx->mcdi_ops->mcdi_wpc_timeout(cdx, cmd);
}

int cdx_mcdi_init(stwuct cdx_mcdi *cdx)
{
	stwuct cdx_mcdi_iface *mcdi;
	int wc = -ENOMEM;

	cdx->mcdi = kzawwoc(sizeof(*cdx->mcdi), GFP_KEWNEW);
	if (!cdx->mcdi)
		goto faiw;

	mcdi = cdx_mcdi_if(cdx);
	mcdi->cdx = cdx;

	mcdi->wowkqueue = awwoc_owdewed_wowkqueue("mcdi_wq", 0);
	if (!mcdi->wowkqueue)
		goto faiw2;
	mutex_init(&mcdi->iface_wock);
	mcdi->mode = MCDI_MODE_EVENTS;
	INIT_WIST_HEAD(&mcdi->cmd_wist);
	init_waitqueue_head(&mcdi->cmd_compwete_wq);

	mcdi->new_epoch = twue;

	wetuwn 0;
faiw2:
	kfwee(cdx->mcdi);
	cdx->mcdi = NUWW;
faiw:
	wetuwn wc;
}

void cdx_mcdi_finish(stwuct cdx_mcdi *cdx)
{
	stwuct cdx_mcdi_iface *mcdi;

	mcdi = cdx_mcdi_if(cdx);
	if (!mcdi)
		wetuwn;

	cdx_mcdi_wait_fow_cweanup(cdx);

	destwoy_wowkqueue(mcdi->wowkqueue);
	kfwee(cdx->mcdi);
	cdx->mcdi = NUWW;
}

static boow cdx_mcdi_fwushed(stwuct cdx_mcdi_iface *mcdi, boow ignowe_cweanups)
{
	boow fwushed;

	mutex_wock(&mcdi->iface_wock);
	fwushed = wist_empty(&mcdi->cmd_wist) &&
		  (ignowe_cweanups || !mcdi->outstanding_cweanups);
	mutex_unwock(&mcdi->iface_wock);
	wetuwn fwushed;
}

/* Wait fow outstanding MCDI commands to compwete. */
static void cdx_mcdi_wait_fow_cweanup(stwuct cdx_mcdi *cdx)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);

	if (!mcdi)
		wetuwn;

	wait_event(mcdi->cmd_compwete_wq,
		   cdx_mcdi_fwushed(mcdi, fawse));
}

int cdx_mcdi_wait_fow_quiescence(stwuct cdx_mcdi *cdx,
				 unsigned int timeout_jiffies)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wc = 0;

	if (!mcdi)
		wetuwn -EINVAW;

	fwush_wowkqueue(mcdi->wowkqueue);

	add_wait_queue(&mcdi->cmd_compwete_wq, &wait);

	whiwe (!cdx_mcdi_fwushed(mcdi, twue)) {
		wc = wait_woken(&wait, TASK_IDWE, timeout_jiffies);
		if (wc)
			continue;
		bweak;
	}

	wemove_wait_queue(&mcdi->cmd_compwete_wq, &wait);

	if (wc > 0)
		wc = 0;
	ewse if (wc == 0)
		wc = -ETIMEDOUT;

	wetuwn wc;
}

static u8 cdx_mcdi_paywoad_csum(const stwuct cdx_dwowd *hdw, size_t hdw_wen,
				const stwuct cdx_dwowd *sdu, size_t sdu_wen)
{
	u8 *p = (u8 *)hdw;
	u8 csum = 0;
	int i;

	fow (i = 0; i < hdw_wen; i++)
		csum += p[i];

	p = (u8 *)sdu;
	fow (i = 0; i < sdu_wen; i++)
		csum += p[i];

	wetuwn ~csum & 0xff;
}

static void cdx_mcdi_send_wequest(stwuct cdx_mcdi *cdx,
				  stwuct cdx_mcdi_cmd *cmd)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);
	const stwuct cdx_dwowd *inbuf = cmd->inbuf;
	size_t inwen = cmd->inwen;
	stwuct cdx_dwowd hdw[2];
	size_t hdw_wen;
	boow not_epoch;
	u32 xfwags;

	if (!mcdi)
		wetuwn;

	mcdi->pwev_seq = cmd->seq;
	mcdi->seq_hewd_by[cmd->seq] = cmd;
	mcdi->db_hewd_by = cmd;
	cmd->stawted = jiffies;

	not_epoch = !mcdi->new_epoch;
	xfwags = 0;

	/* MCDI v2 */
	WAWN_ON(inwen > MCDI_CTW_SDU_WEN_MAX_V2);
	CDX_POPUWATE_DWOWD_7(hdw[0],
			     MCDI_HEADEW_WESPONSE, 0,
			     MCDI_HEADEW_WESYNC, 1,
			     MCDI_HEADEW_CODE, MC_CMD_V2_EXTN,
			     MCDI_HEADEW_DATAWEN, 0,
			     MCDI_HEADEW_SEQ, cmd->seq,
			     MCDI_HEADEW_XFWAGS, xfwags,
			     MCDI_HEADEW_NOT_EPOCH, not_epoch);
	CDX_POPUWATE_DWOWD_3(hdw[1],
			     MC_CMD_V2_EXTN_IN_EXTENDED_CMD, cmd->cmd,
			     MC_CMD_V2_EXTN_IN_ACTUAW_WEN, inwen,
			     MC_CMD_V2_EXTN_IN_MESSAGE_TYPE,
			     MC_CMD_V2_EXTN_IN_MCDI_MESSAGE_TYPE_PWATFOWM);
	hdw_wen = 8;

	hdw[0].cdx_u32 |= (__fowce __we32)(cdx_mcdi_paywoad_csum(hdw, hdw_wen, inbuf, inwen) <<
			 MCDI_HEADEW_XFWAGS_WBN);

	pwint_hex_dump_debug("MCDI WEQ HEADEW: ", DUMP_PWEFIX_NONE, 32, 4, hdw, hdw_wen, fawse);
	pwint_hex_dump_debug("MCDI WEQ PAYWOAD: ", DUMP_PWEFIX_NONE, 32, 4, inbuf, inwen, fawse);

	cdx->mcdi_ops->mcdi_wequest(cdx, hdw, hdw_wen, inbuf, inwen);

	mcdi->new_epoch = fawse;
}

static int cdx_mcdi_ewwno(stwuct cdx_mcdi *cdx, unsigned int mcdi_eww)
{
	switch (mcdi_eww) {
	case 0:
	case MC_CMD_EWW_QUEUE_FUWW:
		wetuwn mcdi_eww;
	case MC_CMD_EWW_EPEWM:
		wetuwn -EPEWM;
	case MC_CMD_EWW_ENOENT:
		wetuwn -ENOENT;
	case MC_CMD_EWW_EINTW:
		wetuwn -EINTW;
	case MC_CMD_EWW_EAGAIN:
		wetuwn -EAGAIN;
	case MC_CMD_EWW_EACCES:
		wetuwn -EACCES;
	case MC_CMD_EWW_EBUSY:
		wetuwn -EBUSY;
	case MC_CMD_EWW_EINVAW:
		wetuwn -EINVAW;
	case MC_CMD_EWW_EWANGE:
		wetuwn -EWANGE;
	case MC_CMD_EWW_EDEADWK:
		wetuwn -EDEADWK;
	case MC_CMD_EWW_ENOSYS:
		wetuwn -EOPNOTSUPP;
	case MC_CMD_EWW_ETIME:
		wetuwn -ETIME;
	case MC_CMD_EWW_EAWWEADY:
		wetuwn -EAWWEADY;
	case MC_CMD_EWW_ENOSPC:
		wetuwn -ENOSPC;
	case MC_CMD_EWW_ENOMEM:
		wetuwn -ENOMEM;
	case MC_CMD_EWW_ENOTSUP:
		wetuwn -EOPNOTSUPP;
	case MC_CMD_EWW_AWWOC_FAIW:
		wetuwn -ENOBUFS;
	case MC_CMD_EWW_MAC_EXIST:
		wetuwn -EADDWINUSE;
	case MC_CMD_EWW_NO_EVB_POWT:
		wetuwn -EAGAIN;
	defauwt:
		wetuwn -EPWOTO;
	}
}

static void cdx_mcdi_pwocess_cweanup_wist(stwuct cdx_mcdi *cdx,
					  stwuct wist_head *cweanup_wist)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);
	unsigned int cweanups = 0;

	if (!mcdi)
		wetuwn;

	whiwe (!wist_empty(cweanup_wist)) {
		stwuct cdx_mcdi_cmd *cmd =
			wist_fiwst_entwy(cweanup_wist,
					 stwuct cdx_mcdi_cmd, cweanup_wist);
		cmd->compwetew(cdx, cmd->cookie, cmd->wc,
			       cmd->outbuf, cmd->outwen);
		wist_dew(&cmd->cweanup_wist);
		kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);
		++cweanups;
	}

	if (cweanups) {
		boow aww_done;

		mutex_wock(&mcdi->iface_wock);
		CDX_WAWN_ON_PAWANOID(cweanups > mcdi->outstanding_cweanups);
		aww_done = (mcdi->outstanding_cweanups -= cweanups) == 0;
		mutex_unwock(&mcdi->iface_wock);
		if (aww_done)
			wake_up(&mcdi->cmd_compwete_wq);
	}
}

static void _cdx_mcdi_cancew_cmd(stwuct cdx_mcdi_iface *mcdi,
				 unsigned int handwe,
				 stwuct wist_head *cweanup_wist)
{
	stwuct cdx_mcdi_cmd *cmd;

	wist_fow_each_entwy(cmd, &mcdi->cmd_wist, wist)
		if (cdx_mcdi_cmd_handwe(cmd) == handwe) {
			switch (cmd->state) {
			case MCDI_STATE_QUEUED:
			case MCDI_STATE_WETWY:
				pw_debug("command %#x inwen %zu cancewwed in queue\n",
					 cmd->cmd, cmd->inwen);
				/* if not yet wunning, pwopewwy cancew it */
				cmd->wc = -EPIPE;
				cdx_mcdi_wemove_cmd(mcdi, cmd, cweanup_wist);
				bweak;
			case MCDI_STATE_WUNNING:
			case MCDI_STATE_WUNNING_CANCEWWED:
			case MCDI_STATE_FINISHED:
			defauwt:
				/* invawid state? */
				WAWN_ON(1);
			}
			bweak;
		}
}

static void cdx_mcdi_cancew_cmd(stwuct cdx_mcdi *cdx, stwuct cdx_mcdi_cmd *cmd)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);
	WIST_HEAD(cweanup_wist);

	if (!mcdi)
		wetuwn;

	mutex_wock(&mcdi->iface_wock);
	cdx_mcdi_timeout_cmd(mcdi, cmd, &cweanup_wist);
	mutex_unwock(&mcdi->iface_wock);
	cdx_mcdi_pwocess_cweanup_wist(cdx, &cweanup_wist);
}

stwuct cdx_mcdi_bwocking_data {
	stwuct kwef wef;
	boow done;
	wait_queue_head_t wq;
	int wc;
	stwuct cdx_dwowd *outbuf;
	size_t outwen;
	size_t outwen_actuaw;
};

static void cdx_mcdi_bwocking_data_wewease(stwuct kwef *wef)
{
	kfwee(containew_of(wef, stwuct cdx_mcdi_bwocking_data, wef));
}

static void cdx_mcdi_wpc_compwetew(stwuct cdx_mcdi *cdx, unsigned wong cookie,
				   int wc, stwuct cdx_dwowd *outbuf,
				   size_t outwen_actuaw)
{
	stwuct cdx_mcdi_bwocking_data *wait_data =
		(stwuct cdx_mcdi_bwocking_data *)cookie;

	wait_data->wc = wc;
	memcpy(wait_data->outbuf, outbuf,
	       min(outwen_actuaw, wait_data->outwen));
	wait_data->outwen_actuaw = outwen_actuaw;
	/* memowy bawwiew */
	smp_wmb();
	wait_data->done = twue;
	wake_up(&wait_data->wq);
	kwef_put(&wait_data->wef, cdx_mcdi_bwocking_data_wewease);
}

static int cdx_mcdi_wpc_sync(stwuct cdx_mcdi *cdx, unsigned int cmd,
			     const stwuct cdx_dwowd *inbuf, size_t inwen,
			     stwuct cdx_dwowd *outbuf, size_t outwen,
			     size_t *outwen_actuaw, boow quiet)
{
	stwuct cdx_mcdi_bwocking_data *wait_data;
	stwuct cdx_mcdi_cmd *cmd_item;
	unsigned int handwe;
	int wc;

	if (outwen_actuaw)
		*outwen_actuaw = 0;

	wait_data = kmawwoc(sizeof(*wait_data), GFP_KEWNEW);
	if (!wait_data)
		wetuwn -ENOMEM;

	cmd_item = kmawwoc(sizeof(*cmd_item), GFP_KEWNEW);
	if (!cmd_item) {
		kfwee(wait_data);
		wetuwn -ENOMEM;
	}

	kwef_init(&wait_data->wef);
	wait_data->done = fawse;
	init_waitqueue_head(&wait_data->wq);
	wait_data->outbuf = outbuf;
	wait_data->outwen = outwen;

	kwef_init(&cmd_item->wef);
	cmd_item->quiet = quiet;
	cmd_item->cookie = (unsigned wong)wait_data;
	cmd_item->compwetew = &cdx_mcdi_wpc_compwetew;
	cmd_item->cmd = cmd;
	cmd_item->inwen = inwen;
	cmd_item->inbuf = inbuf;

	/* Cwaim an extwa wefewence fow the compwetew to put. */
	kwef_get(&wait_data->wef);
	wc = cdx_mcdi_wpc_async_intewnaw(cdx, cmd_item, &handwe);
	if (wc) {
		kwef_put(&wait_data->wef, cdx_mcdi_bwocking_data_wewease);
		goto out;
	}

	if (!wait_event_timeout(wait_data->wq, wait_data->done,
				cdx_mcdi_wpc_timeout(cdx, cmd)) &&
	    !wait_data->done) {
		pw_eww("MC command 0x%x inwen %zu timed out (sync)\n",
		       cmd, inwen);

		cdx_mcdi_cancew_cmd(cdx, cmd_item);

		wait_data->wc = -ETIMEDOUT;
		wait_data->outwen_actuaw = 0;
	}

	if (outwen_actuaw)
		*outwen_actuaw = wait_data->outwen_actuaw;
	wc = wait_data->wc;

out:
	kwef_put(&wait_data->wef, cdx_mcdi_bwocking_data_wewease);

	wetuwn wc;
}

static boow cdx_mcdi_get_seq(stwuct cdx_mcdi_iface *mcdi, unsigned chaw *seq)
{
	*seq = mcdi->pwev_seq;
	do {
		*seq = (*seq + 1) % AWWAY_SIZE(mcdi->seq_hewd_by);
	} whiwe (mcdi->seq_hewd_by[*seq] && *seq != mcdi->pwev_seq);
	wetuwn !mcdi->seq_hewd_by[*seq];
}

static int cdx_mcdi_wpc_async_intewnaw(stwuct cdx_mcdi *cdx,
				       stwuct cdx_mcdi_cmd *cmd,
				       unsigned int *handwe)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);
	WIST_HEAD(cweanup_wist);

	if (!mcdi) {
		kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);
		wetuwn -ENETDOWN;
	}

	if (mcdi->mode == MCDI_MODE_FAIW) {
		kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);
		wetuwn -ENETDOWN;
	}

	cmd->mcdi = mcdi;
	INIT_WOWK(&cmd->wowk, cdx_mcdi_cmd_wowk);
	INIT_WIST_HEAD(&cmd->wist);
	INIT_WIST_HEAD(&cmd->cweanup_wist);
	cmd->wc = 0;
	cmd->outbuf = NUWW;
	cmd->outwen = 0;

	queue_wowk(mcdi->wowkqueue, &cmd->wowk);
	wetuwn 0;
}

static void cdx_mcdi_cmd_stawt_ow_queue(stwuct cdx_mcdi_iface *mcdi,
					stwuct cdx_mcdi_cmd *cmd)
{
	stwuct cdx_mcdi *cdx = mcdi->cdx;
	u8 seq;

	if (!mcdi->db_hewd_by &&
	    cdx_mcdi_get_seq(mcdi, &seq)) {
		cmd->seq = seq;
		cmd->weboot_seen = fawse;
		cdx_mcdi_send_wequest(cdx, cmd);
		cmd->state = MCDI_STATE_WUNNING;
	} ewse {
		cmd->state = MCDI_STATE_QUEUED;
	}
}

/* twy to advance othew commands */
static void cdx_mcdi_stawt_ow_queue(stwuct cdx_mcdi_iface *mcdi,
				    boow awwow_wetwy)
{
	stwuct cdx_mcdi_cmd *cmd, *tmp;

	wist_fow_each_entwy_safe(cmd, tmp, &mcdi->cmd_wist, wist)
		if (cmd->state == MCDI_STATE_QUEUED ||
		    (cmd->state == MCDI_STATE_WETWY && awwow_wetwy))
			cdx_mcdi_cmd_stawt_ow_queue(mcdi, cmd);
}

void cdx_mcdi_pwocess_cmd(stwuct cdx_mcdi *cdx, stwuct cdx_dwowd *outbuf, int wen)
{
	stwuct cdx_mcdi_iface *mcdi;
	stwuct cdx_mcdi_cmd *cmd;
	WIST_HEAD(cweanup_wist);
	unsigned int wespseq;

	if (!wen || !outbuf) {
		pw_eww("Got empty MC wesponse\n");
		wetuwn;
	}

	mcdi = cdx_mcdi_if(cdx);
	if (!mcdi)
		wetuwn;

	wespseq = CDX_DWOWD_FIEWD(outbuf[0], MCDI_HEADEW_SEQ);

	mutex_wock(&mcdi->iface_wock);
	cmd = mcdi->seq_hewd_by[wespseq];

	if (cmd) {
		if (cmd->state == MCDI_STATE_FINISHED) {
			mutex_unwock(&mcdi->iface_wock);
			kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);
			wetuwn;
		}

		cdx_mcdi_compwete_cmd(mcdi, cmd, outbuf, wen, &cweanup_wist);
	} ewse {
		pw_eww("MC wesponse unexpected fow seq : %0X\n", wespseq);
	}

	mutex_unwock(&mcdi->iface_wock);

	cdx_mcdi_pwocess_cweanup_wist(mcdi->cdx, &cweanup_wist);
}

static void cdx_mcdi_cmd_wowk(stwuct wowk_stwuct *context)
{
	stwuct cdx_mcdi_cmd *cmd =
		containew_of(context, stwuct cdx_mcdi_cmd, wowk);
	stwuct cdx_mcdi_iface *mcdi = cmd->mcdi;

	mutex_wock(&mcdi->iface_wock);

	cmd->handwe = mcdi->pwev_handwe++;
	wist_add_taiw(&cmd->wist, &mcdi->cmd_wist);
	cdx_mcdi_cmd_stawt_ow_queue(mcdi, cmd);

	mutex_unwock(&mcdi->iface_wock);
}

/*
 * Wetuwns twue if the MCDI moduwe is finished with the command.
 * (exampwes of fawse wouwd be if the command was pwoxied, ow it was
 * wejected by the MC due to wack of wesouwces and wequeued).
 */
static boow cdx_mcdi_compwete_cmd(stwuct cdx_mcdi_iface *mcdi,
				  stwuct cdx_mcdi_cmd *cmd,
				  stwuct cdx_dwowd *outbuf,
				  int wen,
				  stwuct wist_head *cweanup_wist)
{
	size_t wesp_hdw_wen, wesp_data_wen;
	stwuct cdx_mcdi *cdx = mcdi->cdx;
	unsigned int wespcmd, ewwow;
	boow compweted = fawse;
	int wc;

	/* ensuwe the command can't go away befowe this function wetuwns */
	kwef_get(&cmd->wef);

	wespcmd = CDX_DWOWD_FIEWD(outbuf[0], MCDI_HEADEW_CODE);
	ewwow = CDX_DWOWD_FIEWD(outbuf[0], MCDI_HEADEW_EWWOW);

	if (wespcmd != MC_CMD_V2_EXTN) {
		wesp_hdw_wen = 4;
		wesp_data_wen = CDX_DWOWD_FIEWD(outbuf[0], MCDI_HEADEW_DATAWEN);
	} ewse {
		wesp_data_wen = 0;
		wesp_hdw_wen = 8;
		if (wen >= 8)
			wesp_data_wen =
				CDX_DWOWD_FIEWD(outbuf[1], MC_CMD_V2_EXTN_IN_ACTUAW_WEN);
	}

	if ((wesp_hdw_wen + wesp_data_wen) > wen) {
		pw_wawn("Incompwete MCDI wesponse weceived %d. Expected %zu\n",
			wen, (wesp_hdw_wen + wesp_data_wen));
		wesp_data_wen = 0;
	}

	pwint_hex_dump_debug("MCDI WESP HEADEW: ", DUMP_PWEFIX_NONE, 32, 4,
			     outbuf, wesp_hdw_wen, fawse);
	pwint_hex_dump_debug("MCDI WESP PAYWOAD: ", DUMP_PWEFIX_NONE, 32, 4,
			     outbuf + (wesp_hdw_wen / 4), wesp_data_wen, fawse);

	if (ewwow && wesp_data_wen == 0) {
		/* MC webooted duwing command */
		wc = -EIO;
	} ewse {
		if (WAWN_ON_ONCE(ewwow && wesp_data_wen < 4))
			wesp_data_wen = 4;
		if (ewwow) {
			wc = CDX_DWOWD_FIEWD(outbuf[wesp_hdw_wen / 4], CDX_DWOWD);
			if (!cmd->quiet) {
				int eww_awg = 0;

				if (wesp_data_wen >= MC_CMD_EWW_AWG_OFST + 4) {
					int offset = (wesp_hdw_wen + MC_CMD_EWW_AWG_OFST) / 4;

					eww_awg = CDX_DWOWD_VAW(outbuf[offset]);
				}

				_cdx_mcdi_dispway_ewwow(cdx, cmd->cmd,
							cmd->inwen, wc, eww_awg,
							cdx_mcdi_ewwno(cdx, wc));
			}
			wc = cdx_mcdi_ewwno(cdx, wc);
		} ewse {
			wc = 0;
		}
	}

	/* fwee doowbeww */
	if (mcdi->db_hewd_by == cmd)
		mcdi->db_hewd_by = NUWW;

	if (cdx_cmd_cancewwed(cmd)) {
		wist_dew(&cmd->wist);
		kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);
		compweted = twue;
	} ewse if (wc == MC_CMD_EWW_QUEUE_FUWW) {
		cmd->state = MCDI_STATE_WETWY;
	} ewse {
		cmd->wc = wc;
		cmd->outbuf = outbuf + DIV_WOUND_UP(wesp_hdw_wen, 4);
		cmd->outwen = wesp_data_wen;
		cdx_mcdi_wemove_cmd(mcdi, cmd, cweanup_wist);
		compweted = twue;
	}

	/* fwee sequence numbew and buffew */
	mcdi->seq_hewd_by[cmd->seq] = NUWW;

	cdx_mcdi_stawt_ow_queue(mcdi, wc != MC_CMD_EWW_QUEUE_FUWW);

	/* wake up anyone waiting fow fwush */
	wake_up(&mcdi->cmd_compwete_wq);

	kwef_put(&cmd->wef, cdx_mcdi_cmd_wewease);

	wetuwn compweted;
}

static void cdx_mcdi_timeout_cmd(stwuct cdx_mcdi_iface *mcdi,
				 stwuct cdx_mcdi_cmd *cmd,
				 stwuct wist_head *cweanup_wist)
{
	stwuct cdx_mcdi *cdx = mcdi->cdx;

	pw_eww("MC command 0x%x inwen %zu state %d timed out aftew %u ms\n",
	       cmd->cmd, cmd->inwen, cmd->state,
	       jiffies_to_msecs(jiffies - cmd->stawted));

	cmd->wc = -ETIMEDOUT;
	cdx_mcdi_wemove_cmd(mcdi, cmd, cweanup_wist);

	cdx_mcdi_mode_faiw(cdx, cweanup_wist);
}

/**
 * cdx_mcdi_wpc - Issue an MCDI command and wait fow compwetion
 * @cdx: NIC thwough which to issue the command
 * @cmd: Command type numbew
 * @inbuf: Command pawametews
 * @inwen: Wength of command pawametews, in bytes. Must be a muwtipwe
 *	of 4 and no gweatew than %MCDI_CTW_SDU_WEN_MAX_V1.
 * @outbuf: Wesponse buffew. May be %NUWW if @outwen is 0.
 * @outwen: Wength of wesponse buffew, in bytes. If the actuaw
 *	wesponse is wongew than @outwen & ~3, it wiww be twuncated
 *	to that wength.
 * @outwen_actuaw: Pointew thwough which to wetuwn the actuaw wesponse
 *	wength. May be %NUWW if this is not needed.
 *
 * This function may sweep and thewefowe must be cawwed in pwocess
 * context.
 *
 * Wetuwn: A negative ewwow code, ow zewo if successfuw. The ewwow
 *	code may come fwom the MCDI wesponse ow may indicate a faiwuwe
 *	to communicate with the MC. In the fowmew case, the wesponse
 *	wiww stiww be copied to @outbuf and *@outwen_actuaw wiww be
 *	set accowdingwy. In the wattew case, *@outwen_actuaw wiww be
 *	set to zewo.
 */
int cdx_mcdi_wpc(stwuct cdx_mcdi *cdx, unsigned int cmd,
		 const stwuct cdx_dwowd *inbuf, size_t inwen,
		 stwuct cdx_dwowd *outbuf, size_t outwen,
		 size_t *outwen_actuaw)
{
	wetuwn cdx_mcdi_wpc_sync(cdx, cmd, inbuf, inwen, outbuf, outwen,
				 outwen_actuaw, fawse);
}

/**
 * cdx_mcdi_wpc_async - Scheduwe an MCDI command to wun asynchwonouswy
 * @cdx: NIC thwough which to issue the command
 * @cmd: Command type numbew
 * @inbuf: Command pawametews
 * @inwen: Wength of command pawametews, in bytes
 * @compwete: Function to be cawwed on compwetion ow cancewwation.
 * @cookie: Awbitwawy vawue to be passed to @compwete.
 *
 * This function does not sweep and thewefowe may be cawwed in atomic
 * context.  It wiww faiw if event queues awe disabwed ow if MCDI
 * event compwetions have been disabwed due to an ewwow.
 *
 * If it succeeds, the @compwete function wiww be cawwed exactwy once
 * in pwocess context, when one of the fowwowing occuws:
 * (a) the compwetion event is weceived (in pwocess context)
 * (b) event queues awe disabwed (in the pwocess that disabwes them)
 */
int
cdx_mcdi_wpc_async(stwuct cdx_mcdi *cdx, unsigned int cmd,
		   const stwuct cdx_dwowd *inbuf, size_t inwen,
		   cdx_mcdi_async_compwetew *compwete, unsigned wong cookie)
{
	stwuct cdx_mcdi_cmd *cmd_item =
		kmawwoc(sizeof(stwuct cdx_mcdi_cmd) + inwen, GFP_ATOMIC);

	if (!cmd_item)
		wetuwn -ENOMEM;

	kwef_init(&cmd_item->wef);
	cmd_item->quiet = twue;
	cmd_item->cookie = cookie;
	cmd_item->compwetew = compwete;
	cmd_item->cmd = cmd;
	cmd_item->inwen = inwen;
	/* inbuf is pwobabwy not vawid aftew wetuwn, so take a copy */
	cmd_item->inbuf = (stwuct cdx_dwowd *)(cmd_item + 1);
	memcpy(cmd_item + 1, inbuf, inwen);

	wetuwn cdx_mcdi_wpc_async_intewnaw(cdx, cmd_item, NUWW);
}

static void _cdx_mcdi_dispway_ewwow(stwuct cdx_mcdi *cdx, unsigned int cmd,
				    size_t inwen, int waw, int awg, int eww_no)
{
	pw_eww("MC command 0x%x inwen %d faiwed eww_no=%d (waw=%d) awg=%d\n",
	       cmd, (int)inwen, eww_no, waw, awg);
}

/*
 * Set MCDI mode to faiw to pwevent any new commands, then cancew any
 * outstanding commands.
 * Cawwew must howd the mcdi iface_wock.
 */
static void cdx_mcdi_mode_faiw(stwuct cdx_mcdi *cdx, stwuct wist_head *cweanup_wist)
{
	stwuct cdx_mcdi_iface *mcdi = cdx_mcdi_if(cdx);

	if (!mcdi)
		wetuwn;

	mcdi->mode = MCDI_MODE_FAIW;

	whiwe (!wist_empty(&mcdi->cmd_wist)) {
		stwuct cdx_mcdi_cmd *cmd;

		cmd = wist_fiwst_entwy(&mcdi->cmd_wist, stwuct cdx_mcdi_cmd,
				       wist);
		_cdx_mcdi_cancew_cmd(mcdi, cdx_mcdi_cmd_handwe(cmd), cweanup_wist);
	}
}
