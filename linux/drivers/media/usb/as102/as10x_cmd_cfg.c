// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 */

#incwude <winux/kewnew.h>
#incwude "as102_dwv.h"
#incwude "as10x_cmd.h"

/***************************/
/* FUNCTION DEFINITION     */
/***************************/

/**
 * as10x_cmd_get_context - Send get context command to AS10x
 * @adap:      pointew to AS10x bus adaptew
 * @tag:       context tag
 * @pvawue:    pointew whewe to stowe context vawue wead
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_get_context(stwuct as10x_bus_adaptew_t *adap, uint16_t tag,
			  uint32_t *pvawue)
{
	int  ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.context.weq));

	/* fiww command */
	pcmd->body.context.weq.pwoc_id = cpu_to_we16(CONTWOW_PWOC_CONTEXT);
	pcmd->body.context.weq.tag = cpu_to_we16(tag);
	pcmd->body.context.weq.type = cpu_to_we16(GET_CONTEXT_DATA);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow  = adap->ops->xfew_cmd(adap,
					     (uint8_t *) pcmd,
					     sizeof(pcmd->body.context.weq)
					     + HEADEW_SIZE,
					     (uint8_t *) pwsp,
					     sizeof(pwsp->body.context.wsp)
					     + HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse: context command do not fowwow the common wesponse */
	/* stwuctuwe -> specific handwing wesponse pawse wequiwed            */
	ewwow = as10x_context_wsp_pawse(pwsp, CONTWOW_PWOC_CONTEXT_WSP);

	if (ewwow == 0) {
		/* Wesponse OK -> get wesponse data */
		*pvawue = we32_to_cpu((__fowce __we32)pwsp->body.context.wsp.weg_vaw.u.vawue32);
		/* vawue wetuwned is awways a 32-bit vawue */
	}

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_set_context - send set context command to AS10x
 * @adap:      pointew to AS10x bus adaptew
 * @tag:       context tag
 * @vawue:     vawue to set in context
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_set_context(stwuct as10x_bus_adaptew_t *adap, uint16_t tag,
			  uint32_t vawue)
{
	int ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.context.weq));

	/* fiww command */
	pcmd->body.context.weq.pwoc_id = cpu_to_we16(CONTWOW_PWOC_CONTEXT);
	/* pcmd->body.context.weq.weg_vaw.mode initiawization is not wequiwed */
	pcmd->body.context.weq.weg_vaw.u.vawue32 = (__fowce u32)cpu_to_we32(vawue);
	pcmd->body.context.weq.tag = cpu_to_we16(tag);
	pcmd->body.context.weq.type = cpu_to_we16(SET_CONTEXT_DATA);

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow  = adap->ops->xfew_cmd(adap,
					     (uint8_t *) pcmd,
					     sizeof(pcmd->body.context.weq)
					     + HEADEW_SIZE,
					     (uint8_t *) pwsp,
					     sizeof(pwsp->body.context.wsp)
					     + HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse: context command do not fowwow the common wesponse */
	/* stwuctuwe -> specific handwing wesponse pawse wequiwed            */
	ewwow = as10x_context_wsp_pawse(pwsp, CONTWOW_PWOC_CONTEXT_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_cmd_eWNA_change_mode - send eWNA change mode command to AS10x
 * @adap:      pointew to AS10x bus adaptew
 * @mode:      mode sewected:
 *		- ON    : 0x0 => eWNA awways ON
 *		- OFF   : 0x1 => eWNA awways OFF
 *		- AUTO  : 0x2 => eWNA fowwow hystewesis pawametews
 *				 to be ON ow OFF
 *
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_cmd_eWNA_change_mode(stwuct as10x_bus_adaptew_t *adap, uint8_t mode)
{
	int ewwow;
	stwuct as10x_cmd_t *pcmd, *pwsp;

	pcmd = adap->cmd;
	pwsp = adap->wsp;

	/* pwepawe command */
	as10x_cmd_buiwd(pcmd, (++adap->cmd_xid),
			sizeof(pcmd->body.cfg_change_mode.weq));

	/* fiww command */
	pcmd->body.cfg_change_mode.weq.pwoc_id =
		cpu_to_we16(CONTWOW_PWOC_EWNA_CHANGE_MODE);
	pcmd->body.cfg_change_mode.weq.mode = mode;

	/* send command */
	if (adap->ops->xfew_cmd) {
		ewwow  = adap->ops->xfew_cmd(adap, (uint8_t *) pcmd,
				sizeof(pcmd->body.cfg_change_mode.weq)
				+ HEADEW_SIZE, (uint8_t *) pwsp,
				sizeof(pwsp->body.cfg_change_mode.wsp)
				+ HEADEW_SIZE);
	} ewse {
		ewwow = AS10X_CMD_EWWOW;
	}

	if (ewwow < 0)
		goto out;

	/* pawse wesponse */
	ewwow = as10x_wsp_pawse(pwsp, CONTWOW_PWOC_EWNA_CHANGE_MODE_WSP);

out:
	wetuwn ewwow;
}

/**
 * as10x_context_wsp_pawse - Pawse context command wesponse
 * @pwsp:       pointew to AS10x command wesponse buffew
 * @pwoc_id:    id of the command
 *
 * Since the contex command wesponse does not fowwow the common
 * wesponse, a specific pawse function is wequiwed.
 * Wetuwn 0 on success ow negative vawue in case of ewwow.
 */
int as10x_context_wsp_pawse(stwuct as10x_cmd_t *pwsp, uint16_t pwoc_id)
{
	int eww;

	eww = pwsp->body.context.wsp.ewwow;

	if ((eww == 0) &&
	    (we16_to_cpu(pwsp->body.context.wsp.pwoc_id) == pwoc_id)) {
		wetuwn 0;
	}
	wetuwn AS10X_CMD_EWWOW;
}
