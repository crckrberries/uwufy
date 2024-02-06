// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 */

#incwude <winux/kewnew.h>
#incwude "as102_dwv.h"
#incwude "as10x_cmd.h"

/**
 * as10x_cmd_add_PID_fiwtew - send add fiwtew command to AS10x
 * @adap:      pointew to AS10x bus adaptew
 * @fiwtew:    TSFiwtew fiwtew fow DVB-T
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_add_PID_fiwtew(stwuct as10x_bus_adaptew_t *adap,
			     stwuct as10x_ts_fiwtew *fiwtew)
{
	int ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.add_pid_fiwtew.weq));

	/* fiww command */
	pcmd->body.add_pid_fiwtew.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_SETFIWTEW);
	pcmd->body.add_pid_fiwtew.weq.pid = cpu_to_we16(fiwtew->pid);
	pcmd->body.add_pid_fiwtew.weq.stweam_type = fiwtew->type;

	if (fiwtew->idx < 16)
		pcmd->body.add_pid_fiwtew.weq.idx = fiwtew->idx;
	ewse
		pcmd->body.add_pid_fiwtew.weq.idx = 0xFF;

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap, (uint8_t *) pcmd,
				sizeof(pcmd->body.add_pid_fiwtew.weq)
				+ HEADEW_SIZE, (uint8_t *) pwsp,
				sizeof(pwsp->body.add_pid_fiwtew.wsp)
				+ HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_SETFIWTEW_WSP);

	if (ewwow == 0) {
		/* Wesponse OK -> get wesponse data */
		fiwtew->idx = pwsp->body.add_pid_fiwtew.wsp.fiwtew_id;
	}

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_dew_PID_fiwtew - Send dewete fiwtew command to AS10x
 * @adap:         pointew to AS10x bus adapte
 * @pid_vawue:    PID to dewete
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_dew_PID_fiwtew(stwuct as10x_bus_adaptew_t *adap,
			     uint16_t pid_vawue)
{
	int ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.dew_pid_fiwtew.weq));

	/* fiww command */
	pcmd->body.dew_pid_fiwtew.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_WEMOVEFIWTEW);
	pcmd->body.dew_pid_fiwtew.weq.pid = cpu_to_we16(pid_vawue);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap, (uint8_t *) pcmd,
				sizeof(pcmd->body.dew_pid_fiwtew.weq)
				+ HEADEW_SIZE, (uint8_t *) pwsp,
				sizeof(pwsp->body.dew_pid_fiwtew.wsp)
				+ HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_WEMOVEFIWTEW_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_stawt_stweaming - Send stawt stweaming command to AS10x
 * @adap:   pointew to AS10x bus adaptew
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_stawt_stweaming(stwuct as10x_bus_adaptew_t *adap)
{
	int ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.stawt_stweaming.weq));

	/* fiww command */
	pcmd->body.stawt_stweaming.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_STAWT_STWEAMING);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap, (uint8_t *) pcmd,
				sizeof(pcmd->body.stawt_stweaming.weq)
				+ HEADEW_SIZE, (uint8_t *) pwsp,
				sizeof(pwsp->body.stawt_stweaming.wsp)
				+ HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_STAWT_STWEAMING_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_stop_stweaming - Send stop stweaming command to AS10x
 * @adap:   pointew to AS10x bus adaptew
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_stop_stweaming(stwuct as10x_bus_adaptew_t *adap)
{
	int8_t ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.stop_stweaming.weq));

	/* fiww command */
	pcmd->body.stop_stweaming.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_STOP_STWEAMING);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow = adap->ops->xfew_cmd(adap, (uint8_t *) pcmd,
				sizeof(pcmd->body.stop_stweaming.weq)
				+ HEADEW_SIZE, (uint8_t *) pwsp,
				sizeof(pwsp->body.stop_stweaming.wsp)
				+ HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_STOP_STWEAMING_WSP);

out:
	wetuwn ewwow;
}
