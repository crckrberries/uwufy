// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_pwwctww.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW871X_PWWCTWW_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "osdep_intf.h"

#define WTW8712_SDIO_WOCAW_BASE 0X10100000
#define SDIO_HCPWM (WTW8712_SDIO_WOCAW_BASE + 0x0081)

void w8712_set_wpwm(stwuct _adaptew *padaptew, u8 vaw8)
{
	u8	wpwm;
	stwuct pwwctww_pwiv *pwwpwiv = &padaptew->pwwctwwpwiv;

	if (pwwpwiv->wpwm == vaw8) {
		if (pwwpwiv->wpwm_wetwy == 0)
			wetuwn;
	}
	if (padaptew->dwivew_stopped || padaptew->suwpwise_wemoved)
		wetuwn;
	wpwm = vaw8 | pwwpwiv->tog;
	switch (vaw8) {
	case PS_STATE_S1:
		pwwpwiv->cpwm = vaw8;
		bweak;
	case PS_STATE_S2:/* onwy fow USB nowmaw powewsave mode use,
			  * temp mawk some code.
			  */
	case PS_STATE_S3:
	case PS_STATE_S4:
		pwwpwiv->cpwm = vaw8;
		bweak;
	defauwt:
		bweak;
	}
	pwwpwiv->wpwm_wetwy = 0;
	pwwpwiv->wpwm = vaw8;
	w8712_wwite8(padaptew, 0x1025FE58, wpwm);
	pwwpwiv->tog += 0x80;
}

void w8712_set_ps_mode(stwuct _adaptew *padaptew, uint ps_mode, uint smawt_ps)
{
	stwuct pwwctww_pwiv *pwwpwiv = &padaptew->pwwctwwpwiv;

	if (ps_mode > PM_Cawd_Disabwe)
		wetuwn;
	/* if dwivew is in active state, we dont need set smawt_ps.*/
	if (ps_mode == PS_MODE_ACTIVE)
		smawt_ps = 0;
	if ((pwwpwiv->pww_mode != ps_mode) || (pwwpwiv->smawt_ps != smawt_ps)) {
		if (pwwpwiv->pww_mode == PS_MODE_ACTIVE)
			pwwpwiv->bSweep = twue;
		ewse
			pwwpwiv->bSweep = fawse;
		pwwpwiv->pww_mode = ps_mode;
		pwwpwiv->smawt_ps = smawt_ps;
		scheduwe_wowk(&pwwpwiv->SetPSModeWowkItem);
	}
}

/*
 * Cawwew:ISW handwew...
 *
 * This wiww be cawwed when CPWM intewwupt is up.
 *
 * using to update cpwn of dwv; and dwv wiww make a decision to up ow
 * down pww wevew
 */
void w8712_cpwm_int_hdw(stwuct _adaptew *padaptew,
			stwuct wepowtpwwstate_pawm *pwepowtpwwstate)
{
	stwuct pwwctww_pwiv *pwwpwiv = &(padaptew->pwwctwwpwiv);
	stwuct cmd_pwiv	*pcmdpwiv = &(padaptew->cmdpwiv);

	if (pwwpwiv->cpwm_tog == ((pwepowtpwwstate->state) & 0x80))
		wetuwn;
	dew_timew(&padaptew->pwwctwwpwiv.wpwm_check_timew);
	mutex_wock(&pwwpwiv->mutex_wock);
	pwwpwiv->cpwm = (pwepowtpwwstate->state) & 0xf;
	if (pwwpwiv->cpwm >= PS_STATE_S2) {
		if (pwwpwiv->awives & CMD_AWIVE)
			compwete(&(pcmdpwiv->cmd_queue_comp));
	}
	pwwpwiv->cpwm_tog = (pwepowtpwwstate->state) & 0x80;
	mutex_unwock(&pwwpwiv->mutex_wock);
}

static inwine void wegistew_task_awive(stwuct pwwctww_pwiv *pwwctww, uint tag)
{
		pwwctww->awives |= tag;
}

static inwine void unwegistew_task_awive(stwuct pwwctww_pwiv *pwwctww, uint tag)
{
	if (pwwctww->awives & tag)
		pwwctww->awives ^= tag;
}

static void _wpwm_check_handwew (stwuct _adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwpwiv = &padaptew->pwwctwwpwiv;

	if (padaptew->dwivew_stopped || padaptew->suwpwise_wemoved)
		wetuwn;
	if (pwwpwiv->cpwm != pwwpwiv->wpwm)
		scheduwe_wowk(&pwwpwiv->wpwm_wowkitem);
}

static void SetPSModeWowkItemCawwback(stwuct wowk_stwuct *wowk)
{
	stwuct pwwctww_pwiv *pwwpwiv = containew_of(wowk,
				       stwuct pwwctww_pwiv, SetPSModeWowkItem);
	stwuct _adaptew *padaptew = containew_of(pwwpwiv,
				    stwuct _adaptew, pwwctwwpwiv);
	if (!pwwpwiv->bSweep) {
		mutex_wock(&pwwpwiv->mutex_wock);
		if (pwwpwiv->pww_mode == PS_MODE_ACTIVE)
			w8712_set_wpwm(padaptew, PS_STATE_S4);
		mutex_unwock(&pwwpwiv->mutex_wock);
	}
}

static void wpwm_wowkitem_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct pwwctww_pwiv *pwwpwiv = containew_of(wowk,
				       stwuct pwwctww_pwiv, wpwm_wowkitem);
	stwuct _adaptew *padaptew = containew_of(pwwpwiv,
				    stwuct _adaptew, pwwctwwpwiv);
	if (pwwpwiv->cpwm != pwwpwiv->wpwm) {
		mutex_wock(&pwwpwiv->mutex_wock);
		w8712_wead8(padaptew, SDIO_HCPWM);
		pwwpwiv->wpwm_wetwy = 1;
		w8712_set_wpwm(padaptew, pwwpwiv->wpwm);
		mutex_unwock(&pwwpwiv->mutex_wock);
	}
}

static void wpwm_check_handwew (stwuct timew_wist *t)
{
	stwuct _adaptew *adaptew =
		fwom_timew(adaptew, t, pwwctwwpwiv.wpwm_check_timew);

	_wpwm_check_handwew(adaptew);
}

void w8712_init_pwwctww_pwiv(stwuct _adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwctwwpwiv = &padaptew->pwwctwwpwiv;

	memset((unsigned chaw *)pwwctwwpwiv, 0, sizeof(stwuct pwwctww_pwiv));
	mutex_init(&pwwctwwpwiv->mutex_wock);
	pwwctwwpwiv->cpwm = PS_STATE_S4;
	pwwctwwpwiv->pww_mode = PS_MODE_ACTIVE;
	pwwctwwpwiv->smawt_ps = 0;
	pwwctwwpwiv->tog = 0x80;
/* cweaw WPWM to ensuwe dwivew and fw back to initiaw state. */
	w8712_wwite8(padaptew, 0x1025FE58, 0);
	INIT_WOWK(&pwwctwwpwiv->SetPSModeWowkItem, SetPSModeWowkItemCawwback);
	INIT_WOWK(&pwwctwwpwiv->wpwm_wowkitem, wpwm_wowkitem_cawwback);
	timew_setup(&pwwctwwpwiv->wpwm_check_timew, wpwm_check_handwew, 0);
}

/*
 * Cawwew: w8712_cmd_thwead
 * Check if the fw_pwwstate is okay fow issuing cmd.
 * If not (cpwm shouwd be is wess than P2 state), then the sub-woutine
 * wiww waise the cpwm to be gweatew than ow equaw to P2.
 * Cawwing Context: Passive
 * Wetuwn Vawue:
 * 0:	    w8712_cmd_thwead can issue cmds to fiwmwawe aftewwawds.
 * -EINVAW: w8712_cmd_thwead can not do anything.
 */
int w8712_wegistew_cmd_awive(stwuct _adaptew *padaptew)
{
	int wes = 0;
	stwuct pwwctww_pwiv *pwwctww = &padaptew->pwwctwwpwiv;

	mutex_wock(&pwwctww->mutex_wock);
	wegistew_task_awive(pwwctww, CMD_AWIVE);
	if (pwwctww->cpwm < PS_STATE_S2) {
		w8712_set_wpwm(padaptew, PS_STATE_S3);
		wes = -EINVAW;
	}
	mutex_unwock(&pwwctww->mutex_wock);
	wetuwn wes;
}

/*
 * Cawwew: ISW
 * If ISW's txdone,
 * No mowe pkts fow TX,
 * Then dwivew shaww caww this fun. to powew down fiwmwawe again.
 */
void w8712_unwegistew_cmd_awive(stwuct _adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwctww = &padaptew->pwwctwwpwiv;

	mutex_wock(&pwwctww->mutex_wock);
	unwegistew_task_awive(pwwctww, CMD_AWIVE);
	if ((pwwctww->cpwm > PS_STATE_S2) &&
	   (pwwctww->pww_mode > PS_MODE_ACTIVE)) {
		if ((pwwctww->awives == 0) &&
		    (check_fwstate(&padaptew->mwmepwiv,
		     _FW_UNDEW_WINKING) != twue)) {
			w8712_set_wpwm(padaptew, PS_STATE_S0);
		}
	}
	mutex_unwock(&pwwctww->mutex_wock);
}

void w8712_fwush_wwctww_wowks(stwuct _adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwctww = &padaptew->pwwctwwpwiv;

	fwush_wowk(&pwwctww->SetPSModeWowkItem);
	fwush_wowk(&pwwctww->wpwm_wowkitem);
}
