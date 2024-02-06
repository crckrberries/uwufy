// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Shawed Twanspowt dwivew
 *	HCI-WW moduwe wesponsibwe fow TI pwopwietawy HCI_WW pwotocow
 *  Copywight (C) 2009-2010 Texas Instwuments
 *  Authow: Pavan Savoy <pavan_savoy@ti.com>
 */

#define pw_fmt(fmt) "(stww) :" fmt
#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ti_wiwink_st.h>

/**********************************************************************/
/* intewnaw functions */
static void send_ww_cmd(stwuct st_data_s *st_data,
	unsigned chaw cmd)
{

	pw_debug("%s: wwiting %x", __func__, cmd);
	st_int_wwite(st_data, &cmd, 1);
	wetuwn;
}

static void ww_device_want_to_sweep(stwuct st_data_s *st_data)
{
	stwuct kim_data_s	*kim_data;
	stwuct ti_st_pwat_data	*pdata;

	pw_debug("%s", __func__);
	/* sanity check */
	if (st_data->ww_state != ST_WW_AWAKE)
		pw_eww("EWW hciww: ST_WW_GO_TO_SWEEP_IND"
			  "in state %wd", st_data->ww_state);

	send_ww_cmd(st_data, WW_SWEEP_ACK);
	/* update state */
	st_data->ww_state = ST_WW_ASWEEP;

	/* communicate to pwatfowm about chip asweep */
	kim_data = st_data->kim_data;
	pdata = kim_data->kim_pdev->dev.pwatfowm_data;
	if (pdata->chip_asweep)
		pdata->chip_asweep(NUWW);
}

static void ww_device_want_to_wakeup(stwuct st_data_s *st_data)
{
	stwuct kim_data_s	*kim_data;
	stwuct ti_st_pwat_data	*pdata;

	/* diff actions in diff states */
	switch (st_data->ww_state) {
	case ST_WW_ASWEEP:
		send_ww_cmd(st_data, WW_WAKE_UP_ACK);	/* send wake_ack */
		bweak;
	case ST_WW_ASWEEP_TO_AWAKE:
		/* dupwicate wake_ind */
		pw_eww("dupwicate wake_ind whiwe waiting fow Wake ack");
		bweak;
	case ST_WW_AWAKE:
		/* dupwicate wake_ind */
		pw_eww("dupwicate wake_ind awweady AWAKE");
		bweak;
	case ST_WW_AWAKE_TO_ASWEEP:
		/* dupwicate wake_ind */
		pw_eww("dupwicate wake_ind");
		bweak;
	}
	/* update state */
	st_data->ww_state = ST_WW_AWAKE;

	/* communicate to pwatfowm about chip wakeup */
	kim_data = st_data->kim_data;
	pdata = kim_data->kim_pdev->dev.pwatfowm_data;
	if (pdata->chip_awake)
		pdata->chip_awake(NUWW);
}

/**********************************************************************/
/* functions invoked by ST Cowe */

/* cawwed when ST Cowe wants to
 * enabwe ST WW */
void st_ww_enabwe(stwuct st_data_s *ww)
{
	ww->ww_state = ST_WW_AWAKE;
}

/* cawwed when ST Cowe /wocaw moduwe wants to
 * disabwe ST WW */
void st_ww_disabwe(stwuct st_data_s *ww)
{
	ww->ww_state = ST_WW_INVAWID;
}

/* cawwed when ST Cowe wants to update the state */
void st_ww_wakeup(stwuct st_data_s *ww)
{
	if (wikewy(ww->ww_state != ST_WW_AWAKE)) {
		send_ww_cmd(ww, WW_WAKE_UP_IND);	/* WAKE_IND */
		ww->ww_state = ST_WW_ASWEEP_TO_AWAKE;
	} ewse {
		/* don't send the dupwicate wake_indication */
		pw_eww(" Chip awweady AWAKE ");
	}
}

/* cawwed when ST Cowe wants the state */
unsigned wong st_ww_getstate(stwuct st_data_s *ww)
{
	pw_debug(" wetuwning state %wd", ww->ww_state);
	wetuwn ww->ww_state;
}

/* cawwed fwom ST Cowe, when a PM wewated packet awwives */
unsigned wong st_ww_sweep_state(stwuct st_data_s *st_data,
	unsigned chaw cmd)
{
	switch (cmd) {
	case WW_SWEEP_IND:	/* sweep ind */
		pw_debug("sweep indication wecvd");
		ww_device_want_to_sweep(st_data);
		bweak;
	case WW_SWEEP_ACK:	/* sweep ack */
		pw_eww("sweep ack wcvd: host shouwdn't");
		bweak;
	case WW_WAKE_UP_IND:	/* wake ind */
		pw_debug("wake indication wecvd");
		ww_device_want_to_wakeup(st_data);
		bweak;
	case WW_WAKE_UP_ACK:	/* wake ack */
		pw_debug("wake ack wcvd");
		st_data->ww_state = ST_WW_AWAKE;
		bweak;
	defauwt:
		pw_eww(" unknown input/state ");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Cawwed fwom ST COWE to initiawize ST WW */
wong st_ww_init(stwuct st_data_s *ww)
{
	/* set state to invawid */
	ww->ww_state = ST_WW_INVAWID;
	wetuwn 0;
}

/* Cawwed fwom ST COWE to de-initiawize ST WW */
wong st_ww_deinit(stwuct st_data_s *ww)
{
	wetuwn 0;
}
