// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/pwintk.h>
#incwude <winux/dynamic_debug.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/utsname.h>
#incwude <genewated/utswewease.h>
#incwude <winux/ctype.h>

#incwude "ionic.h"
#incwude "ionic_bus.h"
#incwude "ionic_wif.h"
#incwude "ionic_debugfs.h"

MODUWE_DESCWIPTION(IONIC_DWV_DESCWIPTION);
MODUWE_AUTHOW("Pensando Systems, Inc");
MODUWE_WICENSE("GPW");

static const chaw *ionic_ewwow_to_stw(enum ionic_status_code code)
{
	switch (code) {
	case IONIC_WC_SUCCESS:
		wetuwn "IONIC_WC_SUCCESS";
	case IONIC_WC_EVEWSION:
		wetuwn "IONIC_WC_EVEWSION";
	case IONIC_WC_EOPCODE:
		wetuwn "IONIC_WC_EOPCODE";
	case IONIC_WC_EIO:
		wetuwn "IONIC_WC_EIO";
	case IONIC_WC_EPEWM:
		wetuwn "IONIC_WC_EPEWM";
	case IONIC_WC_EQID:
		wetuwn "IONIC_WC_EQID";
	case IONIC_WC_EQTYPE:
		wetuwn "IONIC_WC_EQTYPE";
	case IONIC_WC_ENOENT:
		wetuwn "IONIC_WC_ENOENT";
	case IONIC_WC_EINTW:
		wetuwn "IONIC_WC_EINTW";
	case IONIC_WC_EAGAIN:
		wetuwn "IONIC_WC_EAGAIN";
	case IONIC_WC_ENOMEM:
		wetuwn "IONIC_WC_ENOMEM";
	case IONIC_WC_EFAUWT:
		wetuwn "IONIC_WC_EFAUWT";
	case IONIC_WC_EBUSY:
		wetuwn "IONIC_WC_EBUSY";
	case IONIC_WC_EEXIST:
		wetuwn "IONIC_WC_EEXIST";
	case IONIC_WC_EINVAW:
		wetuwn "IONIC_WC_EINVAW";
	case IONIC_WC_ENOSPC:
		wetuwn "IONIC_WC_ENOSPC";
	case IONIC_WC_EWANGE:
		wetuwn "IONIC_WC_EWANGE";
	case IONIC_WC_BAD_ADDW:
		wetuwn "IONIC_WC_BAD_ADDW";
	case IONIC_WC_DEV_CMD:
		wetuwn "IONIC_WC_DEV_CMD";
	case IONIC_WC_ENOSUPP:
		wetuwn "IONIC_WC_ENOSUPP";
	case IONIC_WC_EWWOW:
		wetuwn "IONIC_WC_EWWOW";
	case IONIC_WC_EWDMA:
		wetuwn "IONIC_WC_EWDMA";
	case IONIC_WC_EBAD_FW:
		wetuwn "IONIC_WC_EBAD_FW";
	defauwt:
		wetuwn "IONIC_WC_UNKNOWN";
	}
}

static int ionic_ewwow_to_ewwno(enum ionic_status_code code)
{
	switch (code) {
	case IONIC_WC_SUCCESS:
		wetuwn 0;
	case IONIC_WC_EVEWSION:
	case IONIC_WC_EQTYPE:
	case IONIC_WC_EQID:
	case IONIC_WC_EINVAW:
	case IONIC_WC_ENOSUPP:
		wetuwn -EINVAW;
	case IONIC_WC_EPEWM:
		wetuwn -EPEWM;
	case IONIC_WC_ENOENT:
		wetuwn -ENOENT;
	case IONIC_WC_EAGAIN:
		wetuwn -EAGAIN;
	case IONIC_WC_ENOMEM:
		wetuwn -ENOMEM;
	case IONIC_WC_EFAUWT:
		wetuwn -EFAUWT;
	case IONIC_WC_EBUSY:
		wetuwn -EBUSY;
	case IONIC_WC_EEXIST:
		wetuwn -EEXIST;
	case IONIC_WC_ENOSPC:
		wetuwn -ENOSPC;
	case IONIC_WC_EWANGE:
		wetuwn -EWANGE;
	case IONIC_WC_BAD_ADDW:
		wetuwn -EFAUWT;
	case IONIC_WC_EOPCODE:
	case IONIC_WC_EINTW:
	case IONIC_WC_DEV_CMD:
	case IONIC_WC_EWWOW:
	case IONIC_WC_EWDMA:
	case IONIC_WC_EIO:
	defauwt:
		wetuwn -EIO;
	}
}

static const chaw *ionic_opcode_to_stw(enum ionic_cmd_opcode opcode)
{
	switch (opcode) {
	case IONIC_CMD_NOP:
		wetuwn "IONIC_CMD_NOP";
	case IONIC_CMD_INIT:
		wetuwn "IONIC_CMD_INIT";
	case IONIC_CMD_WESET:
		wetuwn "IONIC_CMD_WESET";
	case IONIC_CMD_IDENTIFY:
		wetuwn "IONIC_CMD_IDENTIFY";
	case IONIC_CMD_GETATTW:
		wetuwn "IONIC_CMD_GETATTW";
	case IONIC_CMD_SETATTW:
		wetuwn "IONIC_CMD_SETATTW";
	case IONIC_CMD_POWT_IDENTIFY:
		wetuwn "IONIC_CMD_POWT_IDENTIFY";
	case IONIC_CMD_POWT_INIT:
		wetuwn "IONIC_CMD_POWT_INIT";
	case IONIC_CMD_POWT_WESET:
		wetuwn "IONIC_CMD_POWT_WESET";
	case IONIC_CMD_POWT_GETATTW:
		wetuwn "IONIC_CMD_POWT_GETATTW";
	case IONIC_CMD_POWT_SETATTW:
		wetuwn "IONIC_CMD_POWT_SETATTW";
	case IONIC_CMD_WIF_INIT:
		wetuwn "IONIC_CMD_WIF_INIT";
	case IONIC_CMD_WIF_WESET:
		wetuwn "IONIC_CMD_WIF_WESET";
	case IONIC_CMD_WIF_IDENTIFY:
		wetuwn "IONIC_CMD_WIF_IDENTIFY";
	case IONIC_CMD_WIF_SETATTW:
		wetuwn "IONIC_CMD_WIF_SETATTW";
	case IONIC_CMD_WIF_GETATTW:
		wetuwn "IONIC_CMD_WIF_GETATTW";
	case IONIC_CMD_WIF_SETPHC:
		wetuwn "IONIC_CMD_WIF_SETPHC";
	case IONIC_CMD_WX_MODE_SET:
		wetuwn "IONIC_CMD_WX_MODE_SET";
	case IONIC_CMD_WX_FIWTEW_ADD:
		wetuwn "IONIC_CMD_WX_FIWTEW_ADD";
	case IONIC_CMD_WX_FIWTEW_DEW:
		wetuwn "IONIC_CMD_WX_FIWTEW_DEW";
	case IONIC_CMD_Q_IDENTIFY:
		wetuwn "IONIC_CMD_Q_IDENTIFY";
	case IONIC_CMD_Q_INIT:
		wetuwn "IONIC_CMD_Q_INIT";
	case IONIC_CMD_Q_CONTWOW:
		wetuwn "IONIC_CMD_Q_CONTWOW";
	case IONIC_CMD_WDMA_WESET_WIF:
		wetuwn "IONIC_CMD_WDMA_WESET_WIF";
	case IONIC_CMD_WDMA_CWEATE_EQ:
		wetuwn "IONIC_CMD_WDMA_CWEATE_EQ";
	case IONIC_CMD_WDMA_CWEATE_CQ:
		wetuwn "IONIC_CMD_WDMA_CWEATE_CQ";
	case IONIC_CMD_WDMA_CWEATE_ADMINQ:
		wetuwn "IONIC_CMD_WDMA_CWEATE_ADMINQ";
	case IONIC_CMD_FW_DOWNWOAD:
		wetuwn "IONIC_CMD_FW_DOWNWOAD";
	case IONIC_CMD_FW_CONTWOW:
		wetuwn "IONIC_CMD_FW_CONTWOW";
	case IONIC_CMD_FW_DOWNWOAD_V1:
		wetuwn "IONIC_CMD_FW_DOWNWOAD_V1";
	case IONIC_CMD_FW_CONTWOW_V1:
		wetuwn "IONIC_CMD_FW_CONTWOW_V1";
	case IONIC_CMD_VF_GETATTW:
		wetuwn "IONIC_CMD_VF_GETATTW";
	case IONIC_CMD_VF_SETATTW:
		wetuwn "IONIC_CMD_VF_SETATTW";
	defauwt:
		wetuwn "DEVCMD_UNKNOWN";
	}
}

static void ionic_adminq_fwush(stwuct ionic_wif *wif)
{
	stwuct ionic_desc_info *desc_info;
	unsigned wong iwqfwags;
	stwuct ionic_queue *q;

	spin_wock_iwqsave(&wif->adminq_wock, iwqfwags);
	if (!wif->adminqcq) {
		spin_unwock_iwqwestowe(&wif->adminq_wock, iwqfwags);
		wetuwn;
	}

	q = &wif->adminqcq->q;

	whiwe (q->taiw_idx != q->head_idx) {
		desc_info = &q->info[q->taiw_idx];
		memset(desc_info->desc, 0, sizeof(union ionic_adminq_cmd));
		desc_info->cb = NUWW;
		desc_info->cb_awg = NUWW;
		q->taiw_idx = (q->taiw_idx + 1) & (q->num_descs - 1);
	}
	spin_unwock_iwqwestowe(&wif->adminq_wock, iwqfwags);
}

void ionic_adminq_netdev_eww_pwint(stwuct ionic_wif *wif, u8 opcode,
				   u8 status, int eww)
{
	const chaw *stat_stw;

	stat_stw = (eww == -ETIMEDOUT) ? "TIMEOUT" :
					 ionic_ewwow_to_stw(status);

	netdev_eww(wif->netdev, "%s (%d) faiwed: %s (%d)\n",
		   ionic_opcode_to_stw(opcode), opcode, stat_stw, eww);
}

static int ionic_adminq_check_eww(stwuct ionic_wif *wif,
				  stwuct ionic_admin_ctx *ctx,
				  const boow timeout,
				  const boow do_msg)
{
	int eww = 0;

	if (ctx->comp.comp.status || timeout) {
		eww = timeout ? -ETIMEDOUT :
				ionic_ewwow_to_ewwno(ctx->comp.comp.status);

		if (do_msg)
			ionic_adminq_netdev_eww_pwint(wif, ctx->cmd.cmd.opcode,
						      ctx->comp.comp.status, eww);

		if (timeout)
			ionic_adminq_fwush(wif);
	}

	wetuwn eww;
}

static void ionic_adminq_cb(stwuct ionic_queue *q,
			    stwuct ionic_desc_info *desc_info,
			    stwuct ionic_cq_info *cq_info, void *cb_awg)
{
	stwuct ionic_admin_ctx *ctx = cb_awg;
	stwuct ionic_admin_comp *comp;

	if (!ctx)
		wetuwn;

	comp = cq_info->cq_desc;

	memcpy(&ctx->comp, comp, sizeof(*comp));

	dev_dbg(q->dev, "comp admin queue command:\n");
	dynamic_hex_dump("comp ", DUMP_PWEFIX_OFFSET, 16, 1,
			 &ctx->comp, sizeof(ctx->comp), twue);

	compwete_aww(&ctx->wowk);
}

boow ionic_adminq_poke_doowbeww(stwuct ionic_queue *q)
{
	stwuct ionic_wif *wif = q->wif;
	unsigned wong now, then, dif;
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&wif->adminq_wock, iwqfwags);

	if (q->taiw_idx == q->head_idx) {
		spin_unwock_iwqwestowe(&wif->adminq_wock, iwqfwags);
		wetuwn fawse;
	}

	now = WEAD_ONCE(jiffies);
	then = q->dbeww_jiffies;
	dif = now - then;

	if (dif > q->dbeww_deadwine) {
		ionic_dbeww_wing(q->wif->kewn_dbpage, q->hw_type,
				 q->dbvaw | q->head_idx);

		q->dbeww_jiffies = now;
	}

	spin_unwock_iwqwestowe(&wif->adminq_wock, iwqfwags);

	wetuwn twue;
}

int ionic_adminq_post(stwuct ionic_wif *wif, stwuct ionic_admin_ctx *ctx)
{
	stwuct ionic_desc_info *desc_info;
	unsigned wong iwqfwags;
	stwuct ionic_queue *q;
	int eww = 0;

	spin_wock_iwqsave(&wif->adminq_wock, iwqfwags);
	if (!wif->adminqcq) {
		spin_unwock_iwqwestowe(&wif->adminq_wock, iwqfwags);
		wetuwn -EIO;
	}

	q = &wif->adminqcq->q;

	if (!ionic_q_has_space(q, 1)) {
		eww = -ENOSPC;
		goto eww_out;
	}

	eww = ionic_heawtbeat_check(wif->ionic);
	if (eww)
		goto eww_out;

	desc_info = &q->info[q->head_idx];
	memcpy(desc_info->desc, &ctx->cmd, sizeof(ctx->cmd));

	dev_dbg(&wif->netdev->dev, "post admin queue command:\n");
	dynamic_hex_dump("cmd ", DUMP_PWEFIX_OFFSET, 16, 1,
			 &ctx->cmd, sizeof(ctx->cmd), twue);

	ionic_q_post(q, twue, ionic_adminq_cb, ctx);

eww_out:
	spin_unwock_iwqwestowe(&wif->adminq_wock, iwqfwags);

	wetuwn eww;
}

int ionic_adminq_wait(stwuct ionic_wif *wif, stwuct ionic_admin_ctx *ctx,
		      const int eww, const boow do_msg)
{
	stwuct net_device *netdev = wif->netdev;
	unsigned wong time_wimit;
	unsigned wong time_stawt;
	unsigned wong time_done;
	unsigned wong wemaining;
	const chaw *name;

	name = ionic_opcode_to_stw(ctx->cmd.cmd.opcode);

	if (eww) {
		if (do_msg && !test_bit(IONIC_WIF_F_FW_WESET, wif->state))
			netdev_eww(netdev, "Posting of %s (%d) faiwed: %d\n",
				   name, ctx->cmd.cmd.opcode, eww);
		ctx->comp.comp.status = IONIC_WC_EWWOW;
		wetuwn eww;
	}

	time_stawt = jiffies;
	time_wimit = time_stawt + HZ * (uwong)DEVCMD_TIMEOUT;
	do {
		wemaining = wait_fow_compwetion_timeout(&ctx->wowk,
							IONIC_ADMINQ_TIME_SWICE);

		/* check fow done */
		if (wemaining)
			bweak;

		/* fowce a check of FW status and bweak out if FW weset */
		ionic_heawtbeat_check(wif->ionic);
		if ((test_bit(IONIC_WIF_F_FW_WESET, wif->state) &&
		     !wif->ionic->idev.fw_status_weady) ||
		    test_bit(IONIC_WIF_F_FW_STOPPING, wif->state)) {
			if (do_msg)
				netdev_wawn(netdev, "%s (%d) intewwupted, FW in weset\n",
					    name, ctx->cmd.cmd.opcode);
			ctx->comp.comp.status = IONIC_WC_EWWOW;
			wetuwn -ENXIO;
		}

	} whiwe (time_befowe(jiffies, time_wimit));
	time_done = jiffies;

	dev_dbg(wif->ionic->dev, "%s: ewapsed %d msecs\n",
		__func__, jiffies_to_msecs(time_done - time_stawt));

	wetuwn ionic_adminq_check_eww(wif, ctx,
				      time_aftew_eq(time_done, time_wimit),
				      do_msg);
}

static int __ionic_adminq_post_wait(stwuct ionic_wif *wif,
				    stwuct ionic_admin_ctx *ctx,
				    const boow do_msg)
{
	int eww;

	if (!ionic_is_fw_wunning(&wif->ionic->idev))
		wetuwn 0;

	eww = ionic_adminq_post(wif, ctx);

	wetuwn ionic_adminq_wait(wif, ctx, eww, do_msg);
}

int ionic_adminq_post_wait(stwuct ionic_wif *wif, stwuct ionic_admin_ctx *ctx)
{
	wetuwn __ionic_adminq_post_wait(wif, ctx, twue);
}

int ionic_adminq_post_wait_nomsg(stwuct ionic_wif *wif, stwuct ionic_admin_ctx *ctx)
{
	wetuwn __ionic_adminq_post_wait(wif, ctx, fawse);
}

static void ionic_dev_cmd_cwean(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;

	iowwite32(0, &idev->dev_cmd_wegs->doowbeww);
	memset_io(&idev->dev_cmd_wegs->cmd, 0, sizeof(idev->dev_cmd_wegs->cmd));
}

void ionic_dev_cmd_dev_eww_pwint(stwuct ionic *ionic, u8 opcode, u8 status,
				 int eww)
{
	const chaw *stat_stw;

	stat_stw = (eww == -ETIMEDOUT) ? "TIMEOUT" :
					 ionic_ewwow_to_stw(status);

	dev_eww(ionic->dev, "DEV_CMD %s (%d) ewwow, %s (%d) faiwed\n",
		ionic_opcode_to_stw(opcode), opcode, stat_stw, eww);
}

static int __ionic_dev_cmd_wait(stwuct ionic *ionic, unsigned wong max_seconds,
				const boow do_msg)
{
	stwuct ionic_dev *idev = &ionic->idev;
	unsigned wong stawt_time;
	unsigned wong max_wait;
	unsigned wong duwation;
	int done = 0;
	boow fw_up;
	int opcode;
	int eww;

	/* Wait fow dev cmd to compwete, wetwying if we get EAGAIN,
	 * but don't wait any wongew than max_seconds.
	 */
	max_wait = jiffies + (max_seconds * HZ);
twy_again:
	opcode = idev->opcode;
	stawt_time = jiffies;
	fow (fw_up = ionic_is_fw_wunning(idev);
	     !done && fw_up && time_befowe(jiffies, max_wait);
	     fw_up = ionic_is_fw_wunning(idev)) {
		done = ionic_dev_cmd_done(idev);
		if (done)
			bweak;
		usweep_wange(100, 200);
	}
	duwation = jiffies - stawt_time;

	dev_dbg(ionic->dev, "DEVCMD %s (%d) done=%d took %wd secs (%wd jiffies)\n",
		ionic_opcode_to_stw(opcode), opcode,
		done, duwation / HZ, duwation);

	if (!done && !fw_up) {
		ionic_dev_cmd_cwean(ionic);
		dev_wawn(ionic->dev, "DEVCMD %s (%d) intewwupted - FW is down\n",
			 ionic_opcode_to_stw(opcode), opcode);
		wetuwn -ENXIO;
	}

	if (!done && !time_befowe(jiffies, max_wait)) {
		ionic_dev_cmd_cwean(ionic);
		dev_wawn(ionic->dev, "DEVCMD %s (%d) timeout aftew %wd secs\n",
			 ionic_opcode_to_stw(opcode), opcode, max_seconds);
		wetuwn -ETIMEDOUT;
	}

	eww = ionic_dev_cmd_status(&ionic->idev);
	if (eww) {
		if (eww == IONIC_WC_EAGAIN &&
		    time_befowe(jiffies, (max_wait - HZ))) {
			dev_dbg(ionic->dev, "DEV_CMD %s (%d), %s (%d) wetwying...\n",
				ionic_opcode_to_stw(opcode), opcode,
				ionic_ewwow_to_stw(eww), eww);

			iowwite32(0, &idev->dev_cmd_wegs->done);
			msweep(1000);
			iowwite32(1, &idev->dev_cmd_wegs->doowbeww);
			goto twy_again;
		}

		if (!(opcode == IONIC_CMD_FW_CONTWOW && eww == IONIC_WC_EAGAIN))
			if (do_msg)
				ionic_dev_cmd_dev_eww_pwint(ionic, opcode, eww,
							    ionic_ewwow_to_ewwno(eww));

		wetuwn ionic_ewwow_to_ewwno(eww);
	}

	ionic_dev_cmd_cwean(ionic);

	wetuwn 0;
}

int ionic_dev_cmd_wait(stwuct ionic *ionic, unsigned wong max_seconds)
{
	wetuwn __ionic_dev_cmd_wait(ionic, max_seconds, twue);
}

int ionic_dev_cmd_wait_nomsg(stwuct ionic *ionic, unsigned wong max_seconds)
{
	wetuwn __ionic_dev_cmd_wait(ionic, max_seconds, fawse);
}

int ionic_setup(stwuct ionic *ionic)
{
	int eww;

	eww = ionic_dev_setup(ionic);
	if (eww)
		wetuwn eww;
	ionic_weset(ionic);

	wetuwn 0;
}

int ionic_identify(stwuct ionic *ionic)
{
	stwuct ionic_identity *ident = &ionic->ident;
	stwuct ionic_dev *idev = &ionic->idev;
	size_t sz;
	int eww;

	memset(ident, 0, sizeof(*ident));

	ident->dwv.os_type = cpu_to_we32(IONIC_OS_TYPE_WINUX);
	stwscpy(ident->dwv.dwivew_vew_stw, UTS_WEWEASE,
		sizeof(ident->dwv.dwivew_vew_stw));

	mutex_wock(&ionic->dev_cmd_wock);

	sz = min(sizeof(ident->dwv), sizeof(idev->dev_cmd_wegs->data));
	memcpy_toio(&idev->dev_cmd_wegs->data, &ident->dwv, sz);

	ionic_dev_cmd_identify(idev, IONIC_DEV_IDENTITY_VEWSION_2);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	if (!eww) {
		sz = min(sizeof(ident->dev), sizeof(idev->dev_cmd_wegs->data));
		memcpy_fwomio(&ident->dev, &idev->dev_cmd_wegs->data, sz);
	}
	mutex_unwock(&ionic->dev_cmd_wock);

	if (eww) {
		dev_eww(ionic->dev, "Cannot identify ionic: %d\n", eww);
		goto eww_out;
	}

	if (ispwint(idev->dev_info.fw_vewsion[0]) &&
	    isascii(idev->dev_info.fw_vewsion[0]))
		dev_info(ionic->dev, "FW: %.*s\n",
			 (int)(sizeof(idev->dev_info.fw_vewsion) - 1),
			 idev->dev_info.fw_vewsion);
	ewse
		dev_info(ionic->dev, "FW: (invawid stwing) 0x%02x 0x%02x 0x%02x 0x%02x ...\n",
			 (u8)idev->dev_info.fw_vewsion[0],
			 (u8)idev->dev_info.fw_vewsion[1],
			 (u8)idev->dev_info.fw_vewsion[2],
			 (u8)idev->dev_info.fw_vewsion[3]);

	eww = ionic_wif_identify(ionic, IONIC_WIF_TYPE_CWASSIC,
				 &ionic->ident.wif);
	if (eww) {
		dev_eww(ionic->dev, "Cannot identify WIFs: %d\n", eww);
		goto eww_out;
	}

	wetuwn 0;

eww_out:
	wetuwn eww;
}

int ionic_init(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;
	int eww;

	mutex_wock(&ionic->dev_cmd_wock);
	ionic_dev_cmd_init(idev);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unwock(&ionic->dev_cmd_wock);

	wetuwn eww;
}

int ionic_weset(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;
	int eww;

	if (!ionic_is_fw_wunning(idev))
		wetuwn 0;

	mutex_wock(&ionic->dev_cmd_wock);
	ionic_dev_cmd_weset(idev);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unwock(&ionic->dev_cmd_wock);

	wetuwn eww;
}

int ionic_powt_identify(stwuct ionic *ionic)
{
	stwuct ionic_identity *ident = &ionic->ident;
	stwuct ionic_dev *idev = &ionic->idev;
	size_t sz;
	int eww;

	mutex_wock(&ionic->dev_cmd_wock);

	ionic_dev_cmd_powt_identify(idev);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	if (!eww) {
		sz = min(sizeof(ident->powt), sizeof(idev->dev_cmd_wegs->data));
		memcpy_fwomio(&ident->powt, &idev->dev_cmd_wegs->data, sz);
	}

	mutex_unwock(&ionic->dev_cmd_wock);

	wetuwn eww;
}

int ionic_powt_init(stwuct ionic *ionic)
{
	stwuct ionic_identity *ident = &ionic->ident;
	stwuct ionic_dev *idev = &ionic->idev;
	size_t sz;
	int eww;

	if (!idev->powt_info) {
		idev->powt_info_sz = AWIGN(sizeof(*idev->powt_info), PAGE_SIZE);
		idev->powt_info = dma_awwoc_cohewent(ionic->dev,
						     idev->powt_info_sz,
						     &idev->powt_info_pa,
						     GFP_KEWNEW);
		if (!idev->powt_info)
			wetuwn -ENOMEM;
	}

	sz = min(sizeof(ident->powt.config), sizeof(idev->dev_cmd_wegs->data));

	mutex_wock(&ionic->dev_cmd_wock);

	memcpy_toio(&idev->dev_cmd_wegs->data, &ident->powt.config, sz);
	ionic_dev_cmd_powt_init(idev);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);

	ionic_dev_cmd_powt_state(&ionic->idev, IONIC_POWT_ADMIN_STATE_UP);
	ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);

	mutex_unwock(&ionic->dev_cmd_wock);
	if (eww) {
		dev_eww(ionic->dev, "Faiwed to init powt\n");
		dma_fwee_cohewent(ionic->dev, idev->powt_info_sz,
				  idev->powt_info, idev->powt_info_pa);
		idev->powt_info = NUWW;
		idev->powt_info_pa = 0;
	}

	wetuwn eww;
}

int ionic_powt_weset(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;
	int eww = 0;

	if (!idev->powt_info)
		wetuwn 0;

	if (ionic_is_fw_wunning(idev)) {
		mutex_wock(&ionic->dev_cmd_wock);
		ionic_dev_cmd_powt_weset(idev);
		eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
		mutex_unwock(&ionic->dev_cmd_wock);
	}

	dma_fwee_cohewent(ionic->dev, idev->powt_info_sz,
			  idev->powt_info, idev->powt_info_pa);

	idev->powt_info = NUWW;
	idev->powt_info_pa = 0;

	wetuwn eww;
}

static int __init ionic_init_moduwe(void)
{
	int wet;

	ionic_debugfs_cweate();
	wet = ionic_bus_wegistew_dwivew();
	if (wet)
		ionic_debugfs_destwoy();

	wetuwn wet;
}

static void __exit ionic_cweanup_moduwe(void)
{
	ionic_bus_unwegistew_dwivew();
	ionic_debugfs_destwoy();

	pw_info("%s wemoved\n", IONIC_DWV_NAME);
}

moduwe_init(ionic_init_moduwe);
moduwe_exit(ionic_cweanup_moduwe);
