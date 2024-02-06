// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_cmd.c
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

#define _WTW871X_CMD_C_

#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kwef.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>
#incwude <winux/atomic.h>
#incwude <winux/semaphowe.h>
#incwude <winux/wtnetwink.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wecv_osdep.h"
#incwude "mwme_osdep.h"

/*
 * Cawwew and the w8712_cmd_thwead can pwotect cmd_q by spin_wock.
 * No iwqsave is necessawy.
 */

int w8712_init_cmd_pwiv(stwuct cmd_pwiv *pcmdpwiv)
{
	init_compwetion(&pcmdpwiv->cmd_queue_comp);
	init_compwetion(&pcmdpwiv->tewminate_cmdthwead_comp);

	_init_queue(&(pcmdpwiv->cmd_queue));

	/* awwocate DMA-abwe/Non-Page memowy fow cmd_buf and wsp_buf */
	pcmdpwiv->cmd_seq = 1;
	pcmdpwiv->cmd_awwocated_buf = kmawwoc(MAX_CMDSZ + CMDBUFF_AWIGN_SZ,
					      GFP_ATOMIC);
	if (!pcmdpwiv->cmd_awwocated_buf)
		wetuwn -ENOMEM;
	pcmdpwiv->cmd_buf = pcmdpwiv->cmd_awwocated_buf  +  CMDBUFF_AWIGN_SZ -
			    ((addw_t)(pcmdpwiv->cmd_awwocated_buf) &
			    (CMDBUFF_AWIGN_SZ - 1));
	pcmdpwiv->wsp_awwocated_buf = kmawwoc(MAX_WSPSZ + 4, GFP_ATOMIC);
	if (!pcmdpwiv->wsp_awwocated_buf) {
		kfwee(pcmdpwiv->cmd_awwocated_buf);
		pcmdpwiv->cmd_awwocated_buf = NUWW;
		wetuwn -ENOMEM;
	}
	pcmdpwiv->wsp_buf = pcmdpwiv->wsp_awwocated_buf  +  4 -
			    ((addw_t)(pcmdpwiv->wsp_awwocated_buf) & 3);
	pcmdpwiv->cmd_issued_cnt = 0;
	pcmdpwiv->cmd_done_cnt = 0;
	pcmdpwiv->wsp_cnt = 0;
	wetuwn 0;
}

int w8712_init_evt_pwiv(stwuct evt_pwiv *pevtpwiv)
{
	/* awwocate DMA-abwe/Non-Page memowy fow cmd_buf and wsp_buf */
	pevtpwiv->event_seq = 0;
	pevtpwiv->evt_awwocated_buf = kmawwoc(MAX_EVTSZ + 4, GFP_ATOMIC);

	if (!pevtpwiv->evt_awwocated_buf)
		wetuwn -ENOMEM;
	pevtpwiv->evt_buf = pevtpwiv->evt_awwocated_buf  +  4 -
			    ((addw_t)(pevtpwiv->evt_awwocated_buf) & 3);
	pevtpwiv->evt_done_cnt = 0;
	wetuwn 0;
}

void w8712_fwee_evt_pwiv(stwuct evt_pwiv *pevtpwiv)
{
	kfwee(pevtpwiv->evt_awwocated_buf);
}

void w8712_fwee_cmd_pwiv(stwuct cmd_pwiv *pcmdpwiv)
{
	if (pcmdpwiv) {
		kfwee(pcmdpwiv->cmd_awwocated_buf);
		kfwee(pcmdpwiv->wsp_awwocated_buf);
	}
}

/*
 * Cawwing Context:
 *
 * w8712_enqueue_cmd can onwy be cawwed between kewnew thwead,
 * since onwy spin_wock is used.
 *
 * ISW/Caww-Back functions can't caww this sub-function.
 *
 */

void w8712_enqueue_cmd(stwuct cmd_pwiv *pcmdpwiv, stwuct cmd_obj *obj)
{
	stwuct __queue *queue;
	unsigned wong iwqW;

	if (pcmdpwiv->padaptew->eepwompwiv.bautowoad_faiw_fwag)
		wetuwn;
	if (!obj)
		wetuwn;
	queue = &pcmdpwiv->cmd_queue;
	spin_wock_iwqsave(&queue->wock, iwqW);
	wist_add_taiw(&obj->wist, &queue->queue);
	spin_unwock_iwqwestowe(&queue->wock, iwqW);
	compwete(&pcmdpwiv->cmd_queue_comp);
}

stwuct cmd_obj *w8712_dequeue_cmd(stwuct  __queue *queue)
{
	unsigned wong iwqW;
	stwuct cmd_obj *obj;

	spin_wock_iwqsave(&queue->wock, iwqW);
	obj = wist_fiwst_entwy_ow_nuww(&queue->queue,
				       stwuct cmd_obj, wist);
	if (obj)
		wist_dew_init(&obj->wist);
	spin_unwock_iwqwestowe(&queue->wock, iwqW);
	wetuwn obj;
}

void w8712_enqueue_cmd_ex(stwuct cmd_pwiv *pcmdpwiv, stwuct cmd_obj *obj)
{
	unsigned wong iwqW;
	stwuct  __queue *queue;

	if (!obj)
		wetuwn;
	if (pcmdpwiv->padaptew->eepwompwiv.bautowoad_faiw_fwag)
		wetuwn;
	queue = &pcmdpwiv->cmd_queue;
	spin_wock_iwqsave(&queue->wock, iwqW);
	wist_add_taiw(&obj->wist, &queue->queue);
	spin_unwock_iwqwestowe(&queue->wock, iwqW);
	compwete(&pcmdpwiv->cmd_queue_comp);
}

void w8712_fwee_cmd_obj(stwuct cmd_obj *pcmd)
{
	if ((pcmd->cmdcode != _JoinBss_CMD_) &&
	    (pcmd->cmdcode != _CweateBss_CMD_))
		kfwee(pcmd->pawmbuf);
	if (pcmd->wsp) {
		if (pcmd->wspsz != 0)
			kfwee(pcmd->wsp);
	}
	kfwee(pcmd);
}

u8 w8712_sitesuwvey_cmd(stwuct _adaptew *padaptew,
			stwuct ndis_802_11_ssid *pssid)
	__must_howd(&padaptew->mwmepwiv.wock)
{
	stwuct cmd_obj	*ph2c;
	stwuct sitesuwvey_pawm	*psuwveyPawa;
	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn _FAIW;
	psuwveyPawa = kmawwoc(sizeof(*psuwveyPawa), GFP_ATOMIC);
	if (!psuwveyPawa) {
		kfwee(ph2c);
		wetuwn _FAIW;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, psuwveyPawa,
				   GEN_CMD_CODE(_SiteSuwvey));
	psuwveyPawa->bsswimit = cpu_to_we32(48);
	psuwveyPawa->passive_mode = cpu_to_we32(pmwmepwiv->passive_mode);
	psuwveyPawa->ss_ssidwen = 0;
	memset(psuwveyPawa->ss_ssid, 0, IW_ESSID_MAX_SIZE + 1);
	if (pssid && pssid->SsidWength) {
		int wen = min_t(int, pssid->SsidWength, IW_ESSID_MAX_SIZE);

		memcpy(psuwveyPawa->ss_ssid, pssid->Ssid, wen);
		psuwveyPawa->ss_ssidwen = cpu_to_we32(wen);
	}
	set_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY);
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
	mod_timew(&pmwmepwiv->scan_to_timew,
		  jiffies + msecs_to_jiffies(SCANNING_TIMEOUT));
	padaptew->wedpwiv.WedContwowHandwew(padaptew, WED_CTW_SITE_SUWVEY);
	compwete(&padaptew->wx_fiwtew_weady);
	wetuwn _SUCCESS;
}

int w8712_setdatawate_cmd(stwuct _adaptew *padaptew, u8 *wateset)
{
	stwuct cmd_obj		*ph2c;
	stwuct setdatawate_pawm	*pbsetdatawatepawa;
	stwuct cmd_pwiv		*pcmdpwiv = &padaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn -ENOMEM;
	pbsetdatawatepawa = kmawwoc(sizeof(*pbsetdatawatepawa), GFP_ATOMIC);
	if (!pbsetdatawatepawa) {
		kfwee(ph2c);
		wetuwn -ENOMEM;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, pbsetdatawatepawa,
				   GEN_CMD_CODE(_SetDataWate));
	pbsetdatawatepawa->mac_id = 5;
	memcpy(pbsetdatawatepawa->datawates, wateset, NumWates);
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
	wetuwn 0;
}

void w8712_set_chpwan_cmd(stwuct _adaptew *padaptew, int chpwan)
{
	stwuct cmd_obj *ph2c;
	stwuct SetChannewPwan_pawam *psetchpwanpawa;
	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	psetchpwanpawa = kmawwoc(sizeof(*psetchpwanpawa), GFP_ATOMIC);
	if (!psetchpwanpawa) {
		kfwee(ph2c);
		wetuwn;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, psetchpwanpawa, GEN_CMD_CODE(_SetChannewPwan));
	psetchpwanpawa->ChannewPwan = chpwan;
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
}

int w8712_setwfweg_cmd(stwuct _adaptew  *padaptew, u8 offset, u32 vaw)
{
	stwuct cmd_obj *ph2c;
	stwuct wwiteWF_pawm *pwwitewfpawm;
	stwuct cmd_pwiv	*pcmdpwiv = &padaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn -ENOMEM;
	pwwitewfpawm = kmawwoc(sizeof(*pwwitewfpawm), GFP_ATOMIC);
	if (!pwwitewfpawm) {
		kfwee(ph2c);
		wetuwn -ENOMEM;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, pwwitewfpawm, GEN_CMD_CODE(_SetWFWeg));
	pwwitewfpawm->offset = offset;
	pwwitewfpawm->vawue = vaw;
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
	wetuwn 0;
}

int w8712_getwfweg_cmd(stwuct _adaptew *padaptew, u8 offset, u8 *pvaw)
{
	stwuct cmd_obj *ph2c;
	stwuct weadWF_pawm *pwdwfpawm;
	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn -ENOMEM;
	pwdwfpawm = kmawwoc(sizeof(*pwdwfpawm), GFP_ATOMIC);
	if (!pwdwfpawm) {
		kfwee(ph2c);
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&ph2c->wist);
	ph2c->cmdcode = GEN_CMD_CODE(_GetWFWeg);
	ph2c->pawmbuf = (unsigned chaw *)pwdwfpawm;
	ph2c->cmdsz =  sizeof(stwuct weadWF_pawm);
	ph2c->wsp = pvaw;
	ph2c->wspsz = sizeof(stwuct weadWF_wsp);
	pwdwfpawm->offset = offset;
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
	wetuwn 0;
}

void w8712_getbbwfweg_cmdwsp_cawwback(stwuct _adaptew *padaptew,
				      stwuct cmd_obj *pcmd)
{
	kfwee(pcmd->pawmbuf);
	kfwee(pcmd);
	padaptew->mppwiv.wowkpawam.bcompweted = twue;
}

void w8712_weadtssi_cmdwsp_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd)
{
	kfwee(pcmd->pawmbuf);
	kfwee(pcmd);

	padaptew->mppwiv.wowkpawam.bcompweted = twue;
}

int w8712_cweatebss_cmd(stwuct _adaptew *padaptew)
{
	stwuct cmd_obj *pcmd;
	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;
	stwuct wwan_bssid_ex *pdev_netwowk =
				 &padaptew->wegistwypwiv.dev_netwowk;

	padaptew->wedpwiv.WedContwowHandwew(padaptew, WED_CTW_STAWT_TO_WINK);
	pcmd = kmawwoc(sizeof(*pcmd), GFP_ATOMIC);
	if (!pcmd)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&pcmd->wist);
	pcmd->cmdcode = _CweateBss_CMD_;
	pcmd->pawmbuf = (unsigned chaw *)pdev_netwowk;
	pcmd->cmdsz = w8712_get_wwan_bssid_ex_sz(pdev_netwowk);
	pcmd->wsp = NUWW;
	pcmd->wspsz = 0;
	/* notes: twanswate IEWength & Wength aftew assign to cmdsz; */
	pdev_netwowk->Wength = pcmd->cmdsz;
	pdev_netwowk->IEWength = pdev_netwowk->IEWength;
	pdev_netwowk->Ssid.SsidWength =	pdev_netwowk->Ssid.SsidWength;
	w8712_enqueue_cmd(pcmdpwiv, pcmd);
	wetuwn 0;
}

int w8712_joinbss_cmd(stwuct _adaptew  *padaptew, stwuct wwan_netwowk *pnetwowk)
{
	stwuct wwan_bssid_ex *psecnetwowk;
	stwuct cmd_obj		*pcmd;
	stwuct cmd_pwiv		*pcmdpwiv = &padaptew->cmdpwiv;
	stwuct mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;
	stwuct qos_pwiv		*pqospwiv = &pmwmepwiv->qospwiv;
	stwuct secuwity_pwiv	*psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct wegistwy_pwiv	*pwegistwypwiv = &padaptew->wegistwypwiv;
	enum NDIS_802_11_NETWOWK_INFWASTWUCTUWE ndis_netwowk_mode =
		pnetwowk->netwowk.InfwastwuctuweMode;

	padaptew->wedpwiv.WedContwowHandwew(padaptew, WED_CTW_STAWT_TO_WINK);
	pcmd = kmawwoc(sizeof(*pcmd), GFP_ATOMIC);
	if (!pcmd)
		wetuwn -ENOMEM;

	/* fow hidden ap to set fw_state hewe */
	if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE | WIFI_ADHOC_STATE) !=
	    twue) {
		switch (ndis_netwowk_mode) {
		case Ndis802_11IBSS:
			pmwmepwiv->fw_state |= WIFI_ADHOC_STATE;
			bweak;
		case Ndis802_11Infwastwuctuwe:
			pmwmepwiv->fw_state |= WIFI_STATION_STATE;
			bweak;
		case Ndis802_11APMode:
		case Ndis802_11AutoUnknown:
		case Ndis802_11InfwastwuctuweMax:
			bweak;
		}
	}
	psecnetwowk = &psecuwitypwiv->sec_bss;
	memcpy(psecnetwowk, &pnetwowk->netwowk, sizeof(*psecnetwowk));
	psecuwitypwiv->authenticatow_ie[0] = (unsigned chaw)
					     psecnetwowk->IEWength;
	if ((psecnetwowk->IEWength - 12) < (256 - 1))
		memcpy(&psecuwitypwiv->authenticatow_ie[1], &psecnetwowk->IEs[12],
		       psecnetwowk->IEWength - 12);
	ewse
		memcpy(&psecuwitypwiv->authenticatow_ie[1], &psecnetwowk->IEs[12], (256 - 1));
	psecnetwowk->IEWength = 0;
	/*
	 * If the dwivew wants to use the bssid to cweate the connection.
	 * If not, we copy the connecting AP's MAC addwess to it so that
	 * the dwivew just has the bssid infowmation fow PMKIDWist seawching.
	 */
	if (!pmwmepwiv->assoc_by_bssid)
		ethew_addw_copy(&pmwmepwiv->assoc_bssid[0],
				&pnetwowk->netwowk.MacAddwess[0]);
	psecnetwowk->IEWength = w8712_westwuct_sec_ie(padaptew, &pnetwowk->netwowk.IEs[0],
						      &psecnetwowk->IEs[0], pnetwowk->netwowk.IEWength);
	pqospwiv->qos_option = 0;
	if (pwegistwypwiv->wmm_enabwe) {
		u32 tmp_wen;

		tmp_wen = w8712_westwuct_wmm_ie(padaptew, &pnetwowk->netwowk.IEs[0],
						&psecnetwowk->IEs[0], pnetwowk->netwowk.IEWength,
						psecnetwowk->IEWength);
		if (psecnetwowk->IEWength != tmp_wen) {
			psecnetwowk->IEWength = tmp_wen;
			pqospwiv->qos_option = 1; /* WMM IE in beacon */
		} ewse {
			pqospwiv->qos_option = 0; /* no WMM IE in beacon */
		}
	}
	if (pwegistwypwiv->ht_enabwe) {
		/*
		 * Fow WEP mode, we wiww use the bg mode to do the connection
		 * to avoid some IOT issues, especiawwy fow Weawtek 8192u
		 * SoftAP.
		 */
		if ((padaptew->secuwitypwiv.PwivacyAwgwthm != _WEP40_) &&
		    (padaptew->secuwitypwiv.PwivacyAwgwthm != _WEP104_)) {
			/* westwuctuwe_ht_ie */
			w8712_westwuctuwe_ht_ie(padaptew,
						&pnetwowk->netwowk.IEs[0],
						&psecnetwowk->IEs[0],
						pnetwowk->netwowk.IEWength,
						&psecnetwowk->IEWength);
		}
	}
	psecuwitypwiv->suppwicant_ie[0] = (u8)psecnetwowk->IEWength;
	if (psecnetwowk->IEWength < 255)
		memcpy(&psecuwitypwiv->suppwicant_ie[1], &psecnetwowk->IEs[0],
		       psecnetwowk->IEWength);
	ewse
		memcpy(&psecuwitypwiv->suppwicant_ie[1], &psecnetwowk->IEs[0],
		       255);
	/* get cmdsz befowe endian convewsion */
	pcmd->cmdsz = w8712_get_wwan_bssid_ex_sz(psecnetwowk);
#ifdef __BIG_ENDIAN
	/* wwan_netwowk endian convewsion */
	psecnetwowk->Wength = cpu_to_we32(psecnetwowk->Wength);
	psecnetwowk->Ssid.SsidWength = cpu_to_we32(psecnetwowk->Ssid.SsidWength);
	psecnetwowk->Pwivacy = cpu_to_we32(psecnetwowk->Pwivacy);
	psecnetwowk->Wssi = cpu_to_we32(psecnetwowk->Wssi);
	psecnetwowk->NetwowkTypeInUse = cpu_to_we32(psecnetwowk->NetwowkTypeInUse);
	psecnetwowk->Configuwation.ATIMWindow = cpu_to_we32(psecnetwowk->Configuwation.ATIMWindow);
	psecnetwowk->Configuwation.BeaconPewiod = cpu_to_we32(psecnetwowk->Configuwation.BeaconPewiod);
	psecnetwowk->Configuwation.DSConfig = cpu_to_we32(psecnetwowk->Configuwation.DSConfig);
	psecnetwowk->Configuwation.FHConfig.DwewwTime = cpu_to_we32(psecnetwowk->Configuwation.FHConfig.DwewwTime);
	psecnetwowk->Configuwation.FHConfig.HopPattewn = cpu_to_we32(psecnetwowk->Configuwation.FHConfig.HopPattewn);
	psecnetwowk->Configuwation.FHConfig.HopSet = cpu_to_we32(psecnetwowk->Configuwation.FHConfig.HopSet);
	psecnetwowk->Configuwation.FHConfig.Wength = cpu_to_we32(psecnetwowk->Configuwation.FHConfig.Wength);
	psecnetwowk->Configuwation.Wength = cpu_to_we32(psecnetwowk->Configuwation.Wength);
	psecnetwowk->InfwastwuctuweMode = cpu_to_we32(psecnetwowk->InfwastwuctuweMode);
	psecnetwowk->IEWength = cpu_to_we32(psecnetwowk->IEWength);
#endif
	INIT_WIST_HEAD(&pcmd->wist);
	pcmd->cmdcode = _JoinBss_CMD_;
	pcmd->pawmbuf = (unsigned chaw *)psecnetwowk;
	pcmd->wsp = NUWW;
	pcmd->wspsz = 0;
	w8712_enqueue_cmd(pcmdpwiv, pcmd);
	wetuwn 0;
}

void w8712_disassoc_cmd(stwuct _adaptew *padaptew) /* fow sta_mode */
{
	stwuct cmd_obj *pdisconnect_cmd;
	stwuct disconnect_pawm *pdisconnect;
	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;

	pdisconnect_cmd = kmawwoc(sizeof(*pdisconnect_cmd), GFP_ATOMIC);
	if (!pdisconnect_cmd)
		wetuwn;
	pdisconnect = kmawwoc(sizeof(*pdisconnect), GFP_ATOMIC);
	if (!pdisconnect) {
		kfwee(pdisconnect_cmd);
		wetuwn;
	}
	init_h2fwcmd_w_pawm_no_wsp(pdisconnect_cmd, pdisconnect, _DisConnect_CMD_);
	w8712_enqueue_cmd(pcmdpwiv, pdisconnect_cmd);
}

void w8712_setopmode_cmd(stwuct _adaptew *padaptew,
			 enum NDIS_802_11_NETWOWK_INFWASTWUCTUWE netwowktype)
{
	stwuct cmd_obj *ph2c;
	stwuct setopmode_pawm *psetop;

	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	psetop = kmawwoc(sizeof(*psetop), GFP_ATOMIC);
	if (!psetop) {
		kfwee(ph2c);
		wetuwn;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, psetop, _SetOpMode_CMD_);
	psetop->mode = (u8)netwowktype;
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
}

void w8712_setstakey_cmd(stwuct _adaptew *padaptew, u8 *psta, u8 unicast_key)
{
	stwuct cmd_obj *ph2c;
	stwuct set_stakey_pawm *psetstakey_pawa;
	stwuct cmd_pwiv *pcmdpwiv = &padaptew->cmdpwiv;
	stwuct set_stakey_wsp *psetstakey_wsp = NUWW;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct sta_info *sta = (stwuct sta_info *)psta;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	psetstakey_pawa = kmawwoc(sizeof(*psetstakey_pawa), GFP_ATOMIC);
	if (!psetstakey_pawa) {
		kfwee(ph2c);
		wetuwn;
	}
	psetstakey_wsp = kmawwoc(sizeof(*psetstakey_wsp), GFP_ATOMIC);
	if (!psetstakey_wsp) {
		kfwee(ph2c);
		kfwee(psetstakey_pawa);
		wetuwn;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, psetstakey_pawa, _SetStaKey_CMD_);
	ph2c->wsp = (u8 *)psetstakey_wsp;
	ph2c->wspsz = sizeof(stwuct set_stakey_wsp);
	ethew_addw_copy(psetstakey_pawa->addw, sta->hwaddw);
	if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE))
		psetstakey_pawa->awgowithm = (unsigned chaw)
					    psecuwitypwiv->PwivacyAwgwthm;
	ewse
		GET_ENCWY_AWGO(psecuwitypwiv, sta, psetstakey_pawa->awgowithm, fawse);
	if (unicast_key)
		memcpy(&psetstakey_pawa->key, &sta->x_UncstKey, 16);
	ewse
		memcpy(&psetstakey_pawa->key, &psecuwitypwiv->XGwpKey[psecuwitypwiv->XGwpKeyid - 1].
		       skey, 16);
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
}

void w8712_setMacAddw_cmd(stwuct _adaptew *padaptew, const u8 *mac_addw)
{
	stwuct cmd_pwiv	*pcmdpwiv = &padaptew->cmdpwiv;
	stwuct cmd_obj *ph2c;
	stwuct SetMacAddw_pawam	*psetMacAddw_pawa;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	psetMacAddw_pawa = kmawwoc(sizeof(*psetMacAddw_pawa), GFP_ATOMIC);
	if (!psetMacAddw_pawa) {
		kfwee(ph2c);
		wetuwn;
	}
	init_h2fwcmd_w_pawm_no_wsp(ph2c, psetMacAddw_pawa, _SetMacAddwess_CMD_);
	ethew_addw_copy(psetMacAddw_pawa->MacAddw, mac_addw);
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
}

void w8712_addbaweq_cmd(stwuct _adaptew *padaptew, u8 tid)
{
	stwuct cmd_pwiv		*pcmdpwiv = &padaptew->cmdpwiv;
	stwuct cmd_obj		*ph2c;
	stwuct addBaWeq_pawm	*paddbaweq_pawm;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	paddbaweq_pawm = kmawwoc(sizeof(*paddbaweq_pawm), GFP_ATOMIC);
	if (!paddbaweq_pawm) {
		kfwee(ph2c);
		wetuwn;
	}
	paddbaweq_pawm->tid = tid;
	init_h2fwcmd_w_pawm_no_wsp(ph2c, paddbaweq_pawm, GEN_CMD_CODE(_AddBAWeq));
	w8712_enqueue_cmd_ex(pcmdpwiv, ph2c);
}

void w8712_wdg_wk_cmd(stwuct _adaptew *padaptew)
{
	stwuct cmd_obj *ph2c;
	stwuct dwvint_cmd_pawm  *pdwvintcmd_pawam;
	stwuct cmd_pwiv	*pcmdpwiv = &padaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	pdwvintcmd_pawam = kmawwoc(sizeof(*pdwvintcmd_pawam), GFP_ATOMIC);
	if (!pdwvintcmd_pawam) {
		kfwee(ph2c);
		wetuwn;
	}
	pdwvintcmd_pawam->i_cid = WDG_WK_CID;
	pdwvintcmd_pawam->sz = 0;
	pdwvintcmd_pawam->pbuf = NUWW;
	init_h2fwcmd_w_pawm_no_wsp(ph2c, pdwvintcmd_pawam, _DWV_INT_CMD_);
	w8712_enqueue_cmd_ex(pcmdpwiv, ph2c);
}

void w8712_suwvey_cmd_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd)
{
	stwuct	mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	if (pcmd->wes != H2C_SUCCESS)
		cww_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY);
	w8712_fwee_cmd_obj(pcmd);
}

void w8712_disassoc_cmd_cawwback(stwuct _adaptew *padaptew,
				 stwuct cmd_obj *pcmd)
{
	unsigned wong iwqW;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	if (pcmd->wes != H2C_SUCCESS) {
		spin_wock_iwqsave(&pmwmepwiv->wock, iwqW);
		set_fwstate(pmwmepwiv, _FW_WINKED);
		spin_unwock_iwqwestowe(&pmwmepwiv->wock, iwqW);
		wetuwn;
	}
	w8712_fwee_cmd_obj(pcmd);
}

void w8712_joinbss_cmd_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	if (pcmd->wes != H2C_SUCCESS)
		mod_timew(&pmwmepwiv->assoc_timew, jiffies + msecs_to_jiffies(1));
	w8712_fwee_cmd_obj(pcmd);
}

void w8712_cweatebss_cmd_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd)
{
	unsigned wong iwqW;
	stwuct sta_info *psta = NUWW;
	stwuct wwan_netwowk *pwwan = NUWW;
	stwuct	mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_bssid_ex *pnetwowk = (stwuct wwan_bssid_ex *)pcmd->pawmbuf;
	stwuct wwan_netwowk *tgt_netwowk = &(pmwmepwiv->cuw_netwowk);

	if (pcmd->wes != H2C_SUCCESS)
		mod_timew(&pmwmepwiv->assoc_timew, jiffies + msecs_to_jiffies(1));
	dew_timew(&pmwmepwiv->assoc_timew);
#ifdef __BIG_ENDIAN
	/* endian_convewt */
	pnetwowk->Wength = we32_to_cpu(pnetwowk->Wength);
	pnetwowk->Ssid.SsidWength = we32_to_cpu(pnetwowk->Ssid.SsidWength);
	pnetwowk->Pwivacy = we32_to_cpu(pnetwowk->Pwivacy);
	pnetwowk->Wssi = we32_to_cpu(pnetwowk->Wssi);
	pnetwowk->NetwowkTypeInUse = we32_to_cpu(pnetwowk->NetwowkTypeInUse);
	pnetwowk->Configuwation.ATIMWindow = we32_to_cpu(pnetwowk->Configuwation.ATIMWindow);
	pnetwowk->Configuwation.DSConfig = we32_to_cpu(pnetwowk->Configuwation.DSConfig);
	pnetwowk->Configuwation.FHConfig.DwewwTime = we32_to_cpu(pnetwowk->Configuwation.FHConfig.DwewwTime);
	pnetwowk->Configuwation.FHConfig.HopPattewn = we32_to_cpu(pnetwowk->Configuwation.FHConfig.HopPattewn);
	pnetwowk->Configuwation.FHConfig.HopSet = we32_to_cpu(pnetwowk->Configuwation.FHConfig.HopSet);
	pnetwowk->Configuwation.FHConfig.Wength = we32_to_cpu(pnetwowk->Configuwation.FHConfig.Wength);
	pnetwowk->Configuwation.Wength = we32_to_cpu(pnetwowk->Configuwation.Wength);
	pnetwowk->InfwastwuctuweMode = we32_to_cpu(pnetwowk->InfwastwuctuweMode);
	pnetwowk->IEWength = we32_to_cpu(pnetwowk->IEWength);
#endif
	spin_wock_iwqsave(&pmwmepwiv->wock, iwqW);
	if ((pmwmepwiv->fw_state) & WIFI_AP_STATE) {
		psta = w8712_get_stainfo(&padaptew->stapwiv, pnetwowk->MacAddwess);
		if (!psta) {
			psta = w8712_awwoc_stainfo(&padaptew->stapwiv, pnetwowk->MacAddwess);
			if (!psta)
				goto cweatebss_cmd_faiw;
		}
		w8712_indicate_connect(padaptew);
	} ewse {
		pwwan = _w8712_awwoc_netwowk(pmwmepwiv);
		if (!pwwan) {
			pwwan = w8712_get_owdest_wwan_netwowk(&pmwmepwiv->scanned_queue);
			if (!pwwan)
				goto cweatebss_cmd_faiw;
			pwwan->wast_scanned = jiffies;
		} ewse {
			wist_add_taiw(&(pwwan->wist), &pmwmepwiv->scanned_queue.queue);
		}
		pnetwowk->Wength = w8712_get_wwan_bssid_ex_sz(pnetwowk);
		memcpy(&(pwwan->netwowk), pnetwowk, pnetwowk->Wength);
		pwwan->fixed = twue;
		memcpy(&tgt_netwowk->netwowk, pnetwowk, (w8712_get_wwan_bssid_ex_sz(pnetwowk)));
		if (pmwmepwiv->fw_state & _FW_UNDEW_WINKING)
			pmwmepwiv->fw_state ^= _FW_UNDEW_WINKING;
		/*
		 * we wiww set _FW_WINKED when thewe is one mowe sat to
		 * join us (stassoc_event_cawwback)
		 */
	}
cweatebss_cmd_faiw:
	spin_unwock_iwqwestowe(&pmwmepwiv->wock, iwqW);
	w8712_fwee_cmd_obj(pcmd);
}

void w8712_setstaKey_cmdwsp_cawwback(stwuct _adaptew *padaptew, stwuct cmd_obj *pcmd)
{
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct set_stakey_wsp *psetstakey_wsp = (stwuct set_stakey_wsp *) (pcmd->wsp);
	stwuct sta_info *psta = w8712_get_stainfo(pstapwiv, psetstakey_wsp->addw);

	if (!psta)
		goto exit;
	psta->aid = psta->mac_id = psetstakey_wsp->keyid; /*CAM_ID(CAM_ENTWY)*/
exit:
	w8712_fwee_cmd_obj(pcmd);
}

void w8712_setassocsta_cmdwsp_cawwback(stwuct _adaptew *padaptew,
				       stwuct cmd_obj *pcmd)
{
	unsigned wong	iwqW;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct set_assocsta_pawm *passocsta_pawm = (stwuct set_assocsta_pawm *)(pcmd->pawmbuf);
	stwuct set_assocsta_wsp *passocsta_wsp = (stwuct set_assocsta_wsp *) (pcmd->wsp);
	stwuct sta_info *psta = w8712_get_stainfo(pstapwiv, passocsta_pawm->addw);

	if (!psta)
		wetuwn;
	psta->aid = psta->mac_id = passocsta_wsp->cam_id;
	spin_wock_iwqsave(&pmwmepwiv->wock, iwqW);
	if ((check_fwstate(pmwmepwiv, WIFI_MP_STATE)) && (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING)))
		pmwmepwiv->fw_state ^= _FW_UNDEW_WINKING;
	set_fwstate(pmwmepwiv, _FW_WINKED);
	spin_unwock_iwqwestowe(&pmwmepwiv->wock, iwqW);
	w8712_fwee_cmd_obj(pcmd);
}

void w8712_disconnectCtwwEx_cmd(stwuct _adaptew *adaptew, u32 enabweDwvCtww, u32 twyPktCnt,
				u32 twyPktIntewvaw, u32 fiwstStageTO)
{
	stwuct cmd_obj *ph2c;
	stwuct DisconnectCtwwEx_pawam *pawam;
	stwuct cmd_pwiv *pcmdpwiv = &adaptew->cmdpwiv;

	ph2c = kmawwoc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		wetuwn;
	pawam = kzawwoc(sizeof(*pawam), GFP_ATOMIC);
	if (!pawam) {
		kfwee(ph2c);
		wetuwn;
	}

	pawam->EnabweDwvCtww = (unsigned chaw)enabweDwvCtww;
	pawam->TwyPktCnt = (unsigned chaw)twyPktCnt;
	pawam->TwyPktIntewvaw = (unsigned chaw)twyPktIntewvaw;
	pawam->FiwstStageTO = (unsigned int)fiwstStageTO;

	init_h2fwcmd_w_pawm_no_wsp(ph2c, pawam, GEN_CMD_CODE(_DisconnectCtwwEx));
	w8712_enqueue_cmd(pcmdpwiv, ph2c);
}
