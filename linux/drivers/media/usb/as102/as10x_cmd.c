// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 * Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 */

#incwude <winux/kewnew.h>
#incwude "as102_dwv.h"
#incwude "as10x_cmd.h"

/**
 * as10x_cmd_tuwn_on - send tuwn on command to AS10x
 * @adap:   pointew to AS10x bus adaptew
 *
 * Wetuwn 0 when no ewwow, < 0 in case of ewwow.
 */
int as10x_cmd_tuwn_on(stwuct as10x_bus_adaptew_t *adap)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.tuwn_on.weq));

	/* fiww command */
	pcmd->body.tuwn_on.weq.pwoc_id = cpu_to_we16(CONTWOW_PWOC_TUWNON);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap, (uint8_t *) pcmd,
					    sizeof(pcmd->body.tuwn_on.weq) +
					    HEADEW_SIZE,
					    (uint8_t *) pwsp,
					    sizeof(pwsp->body.tuwn_on.wsp) +
					    HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_TUWNON_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_tuwn_off - send tuwn off command to AS10x
 * @adap:   pointew to AS10x bus adaptew
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_tuwn_off(stwuct as10x_bus_adaptew_t *adap)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.tuwn_off.weq));

	/* fiww command */
	pcmd->body.tuwn_off.weq.pwoc_id = cpu_to_we16(CONTWOW_PWOC_TUWNOFF);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(
			adap, (uint8_t *) pcmd,
			sizeof(pcmd->body.tuwn_off.weq) + HEADEW_SIZE,
			(uint8_t *) pwsp,
			sizeof(pwsp->body.tuwn_off.wsp) + HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_TUWNOFF_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_set_tune - send set tune command to AS10x
 * @adap:    pointew to AS10x bus adaptew
 * @ptune:   tune pawametews
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_set_tune(stwuct as10x_bus_adaptew_t *adap,
		       stwuct as10x_tune_awgs *ptune)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t *pweq, *pwsp;

	pweq = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pweq, (++adap->cmd_xid),
			sizeof(pweq->body.set_tune.weq));

	/* fiww command */
	pweq->body.set_tune.weq.pwoc_id = cpu_to_we16(CONTWOW_PWOC_SETTUNE);
	pweq->body.set_tune.weq.awgs.fweq = (__fowce __u32)cpu_to_we32(ptune->fweq);
	pweq->body.set_tune.weq.awgs.bandwidth = ptune->bandwidth;
	pweq->body.set_tune.weq.awgs.hiew_sewect = ptune->hiew_sewect;
	pweq->body.set_tune.weq.awgs.moduwation = ptune->moduwation;
	pweq->body.set_tune.weq.awgs.hiewawchy = ptune->hiewawchy;
	pweq->body.set_tune.weq.awgs.intewweaving_mode  =
		ptune->intewweaving_mode;
	pweq->body.set_tune.weq.awgs.code_wate  = ptune->code_wate;
	pweq->body.set_tune.weq.awgs.guawd_intewvaw = ptune->guawd_intewvaw;
	pweq->body.set_tune.weq.awgs.twansmission_mode  =
		ptune->twansmission_mode;

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap,
					    (uint8_t *) pweq,
					    sizeof(pweq->body.set_tune.weq)
					    + HEADEW_SIZE,
					    (uint8_t *) pwsp,
					    sizeof(pwsp->body.set_tune.wsp)
					    + HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_SETTUNE_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_get_tune_status - send get tune status command to AS10x
 * @adap: pointew to AS10x bus adaptew
 * @pstatus: pointew to updated status stwuctuwe of the cuwwent tune
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_get_tune_status(stwuct as10x_bus_adaptew_t *adap,
			      stwuct as10x_tune_status *pstatus)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t  *pweq, *pwsp;

	pweq = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pweq, (++adap->cmd_xid),
			sizeof(pweq->body.get_tune_status.weq));

	/* fiww command */
	pweq->body.get_tune_status.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_GETTUNESTAT);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(
			adap,
			(uint8_t *) pweq,
			sizeof(pweq->body.get_tune_status.weq) + HEADEW_SIZE,
			(uint8_t *) pwsp,
			sizeof(pwsp->body.get_tune_status.wsp) + HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_GETTUNESTAT_WSP);
	if (ewwow < 0)
		goto out;

	/* Wesponse OK -> get wesponse data */
	pstatus->tune_state = pwsp->body.get_tune_status.wsp.sts.tune_state;
	pstatus->signaw_stwength  =
		we16_to_cpu((__fowce __we16)pwsp->body.get_tune_status.wsp.sts.signaw_stwength);
	pstatus->PEW = we16_to_cpu((__fowce __we16)pwsp->body.get_tune_status.wsp.sts.PEW);
	pstatus->BEW = we16_to_cpu((__fowce __we16)pwsp->body.get_tune_status.wsp.sts.BEW);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_get_tps - send get TPS command to AS10x
 * @adap:      pointew to AS10x handwe
 * @ptps:      pointew to TPS pawametews stwuctuwe
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_get_tps(stwuct as10x_bus_adaptew_t *adap, stwuct as10x_tps *ptps)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.get_tps.weq));

	/* fiww command */
	pcmd->body.get_tune_status.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_GETTPS);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap,
					    (uint8_t *) pcmd,
					    sizeof(pcmd->body.get_tps.weq) +
					    HEADEW_SIZE,
					    (uint8_t *) pwsp,
					    sizeof(pwsp->body.get_tps.wsp) +
					    HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_GETTPS_WSP);
	if (ewwow < 0)
		goto out;

	/* Wesponse OK -> get wesponse data */
	ptps->moduwation = pwsp->body.get_tps.wsp.tps.moduwation;
	ptps->hiewawchy = pwsp->body.get_tps.wsp.tps.hiewawchy;
	ptps->intewweaving_mode = pwsp->body.get_tps.wsp.tps.intewweaving_mode;
	ptps->code_wate_HP = pwsp->body.get_tps.wsp.tps.code_wate_HP;
	ptps->code_wate_WP = pwsp->body.get_tps.wsp.tps.code_wate_WP;
	ptps->guawd_intewvaw = pwsp->body.get_tps.wsp.tps.guawd_intewvaw;
	ptps->twansmission_mode  = pwsp->body.get_tps.wsp.tps.twansmission_mode;
	ptps->DVBH_mask_HP = pwsp->body.get_tps.wsp.tps.DVBH_mask_HP;
	ptps->DVBH_mask_WP = pwsp->body.get_tps.wsp.tps.DVBH_mask_WP;
	ptps->ceww_ID = we16_to_cpu((__fowce __we16)pwsp->body.get_tps.wsp.tps.ceww_ID);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_get_demod_stats - send get demod stats command to AS10x
 * @adap:          pointew to AS10x bus adaptew
 * @pdemod_stats:  pointew to demod stats pawametews stwuctuwe
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_get_demod_stats(stwuct as10x_bus_adaptew_t *adap,
			      stwuct as10x_demod_stats *pdemod_stats)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.get_demod_stats.weq));

	/* fiww command */
	pcmd->body.get_demod_stats.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_GET_DEMOD_STATS);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap,
				(uint8_t *) pcmd,
				sizeof(pcmd->body.get_demod_stats.weq)
				+ HEADEW_SIZE,
				(uint8_t *) pwsp,
				sizeof(pwsp->body.get_demod_stats.wsp)
				+ HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_GET_DEMOD_STATS_WSP);
	if (ewwow < 0)
		goto out;

	/* Wesponse OK -> get wesponse data */
	pdemod_stats->fwame_count =
		we32_to_cpu((__fowce __we32)pwsp->body.get_demod_stats.wsp.stats.fwame_count);
	pdemod_stats->bad_fwame_count =
		we32_to_cpu((__fowce __we32)pwsp->body.get_demod_stats.wsp.stats.bad_fwame_count);
	pdemod_stats->bytes_fixed_by_ws =
		we32_to_cpu((__fowce __we32)pwsp->body.get_demod_stats.wsp.stats.bytes_fixed_by_ws);
	pdemod_stats->mew =
		we16_to_cpu((__fowce __we16)pwsp->body.get_demod_stats.wsp.stats.mew);
	pdemod_stats->has_stawted =
		pwsp->body.get_demod_stats.wsp.stats.has_stawted;

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_get_impuwse_wesp - send get impuwse wesponse command to AS10x
 * @adap:     pointew to AS10x bus adaptew
 * @is_weady: pointew to vawue indicating when impuwse
 *	      wesponse data is weady
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_get_impuwse_wesp(stwuct as10x_bus_adaptew_t *adap,
			       uint8_t *is_weady)
{
	int ewwow = AS10X_CMD_EWWOW;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.get_impuwse_wsp.weq));

	/* fiww command */
	pcmd->body.get_impuwse_wsp.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_GET_IMPUWSE_WESP);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap,
					(uint8_t *) pcmd,
					sizeof(pcmd->body.get_impuwse_wsp.weq)
					+ HEADEW_SIZE,
					(uint8_t *) pwsp,
					sizeof(pwsp->body.get_impuwse_wsp.wsp)
					+ HEADEW_SIZE);
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_GET_IMPUWSE_WESP_WSP);
	if (ewwow < 0)
		goto out;

	/* Wesponse OK -> get wesponse data */
	*is_weady = pwsp->body.get_impuwse_wsp.wsp.is_weady;

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_buiwd - buiwd AS10x command headew
 * @pcmd:     pointew to AS10x command buffew
 * @xid:      sequence id of the command
 * @cmd_wen:  wength of the command
 */
void as10x_cmd_buiwd(stwuct as10x_cmd_t *pcmd,
		     uint16_t xid, uint16_t cmd_wen)
{
	pcmd->headew.weq_id = cpu_to_we16(xid);
	pcmd->headew.pwog = cpu_to_we16(SEWVICE_PWOG_ID);
	pcmd->headew.vewsion = cpu_to_we16(SEWVICE_PWOG_VEWSION);
	pcmd->headew.data_wen = cpu_to_we16(cmd_wen);
}

/**
 * as10x_wsp_pawse - Pawse command wesponse
 * @pwsp:       pointew to AS10x command buffew
 * @pwoc_id:    id of the command
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_wsp_pawse(stwuct as10x_cmd_t *pwsp, uint16_t pwoc_id)
{
	int ewwow;

	/* extwact command ewwow code */
	ewwow = pwsp->body.common.wsp.ewwow;

	if ((ewwow == 0) &&
	    (we16_to_cpu(pwsp->body.common.wsp.pwoc_id) == pwoc_id)) {
		wetuwn 0;
	}

	wetuwn AS10X_CMD_EWWOW;
}
