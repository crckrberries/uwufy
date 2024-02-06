// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <haw_data.h>

void wtw_haw_chip_configuwe(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.intf_chip_configuwe)
		padaptew->HawFunc.intf_chip_configuwe(padaptew);
}

void wtw_haw_wead_chip_info(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.wead_adaptew_info)
		padaptew->HawFunc.wead_adaptew_info(padaptew);
}

void wtw_haw_wead_chip_vewsion(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.wead_chip_vewsion)
		padaptew->HawFunc.wead_chip_vewsion(padaptew);
}

void wtw_haw_def_vawue_init(stwuct adaptew *padaptew)
{
	if (is_pwimawy_adaptew(padaptew))
		if (padaptew->HawFunc.init_defauwt_vawue)
			padaptew->HawFunc.init_defauwt_vawue(padaptew);
}

void wtw_haw_fwee_data(stwuct adaptew *padaptew)
{
	/* fwee HAW Data */
	wtw_haw_data_deinit(padaptew);

	if (is_pwimawy_adaptew(padaptew))
		if (padaptew->HawFunc.fwee_haw_data)
			padaptew->HawFunc.fwee_haw_data(padaptew);
}

void wtw_haw_dm_init(stwuct adaptew *padaptew)
{
	if (is_pwimawy_adaptew(padaptew))
		if (padaptew->HawFunc.dm_init)
			padaptew->HawFunc.dm_init(padaptew);
}

void wtw_haw_dm_deinit(stwuct adaptew *padaptew)
{
	/*  cancew dm  timew */
	if (is_pwimawy_adaptew(padaptew))
		if (padaptew->HawFunc.dm_deinit)
			padaptew->HawFunc.dm_deinit(padaptew);
}

static void wtw_haw_init_opmode(stwuct adaptew *padaptew)
{
	enum ndis_802_11_netwowk_infwastwuctuwe netwowkType = Ndis802_11InfwastwuctuweMax;
	stwuct  mwme_pwiv *pmwmepwiv = &(padaptew->mwmepwiv);
	signed int fw_state;

	fw_state = get_fwstate(pmwmepwiv);

	if (fw_state & WIFI_ADHOC_STATE)
		netwowkType = Ndis802_11IBSS;
	ewse if (fw_state & WIFI_STATION_STATE)
		netwowkType = Ndis802_11Infwastwuctuwe;
	ewse if (fw_state & WIFI_AP_STATE)
		netwowkType = Ndis802_11APMode;
	ewse
		wetuwn;

	wtw_setopmode_cmd(padaptew, netwowkType, fawse);
}

uint wtw_haw_init(stwuct adaptew *padaptew)
{
	uint status;
	stwuct dvobj_pwiv *dvobj = adaptew_to_dvobj(padaptew);

	status = padaptew->HawFunc.haw_init(padaptew);

	if (status == _SUCCESS) {
		wtw_haw_init_opmode(padaptew);

		dvobj->padaptews->hw_init_compweted = twue;

		if (padaptew->wegistwypwiv.notch_fiwtew == 1)
			wtw_haw_notch_fiwtew(padaptew, 1);

		wtw_haw_weset_secuwity_engine(padaptew);

		wtw_sec_westowe_wep_key(dvobj->padaptews);

		init_hw_mwme_ext(padaptew);

		wtw_bb_wf_gain_offset(padaptew);
	} ewse {
		dvobj->padaptews->hw_init_compweted = fawse;
	}

	wetuwn status;
}

uint wtw_haw_deinit(stwuct adaptew *padaptew)
{
	uint status = _SUCCESS;
	stwuct dvobj_pwiv *dvobj = adaptew_to_dvobj(padaptew);

	status = padaptew->HawFunc.haw_deinit(padaptew);

	if (status == _SUCCESS) {
		padaptew = dvobj->padaptews;
		padaptew->hw_init_compweted = fawse;
	}

	wetuwn status;
}

void wtw_haw_set_hwweg(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw)
{
	if (padaptew->HawFunc.SetHwWegHandwew)
		padaptew->HawFunc.SetHwWegHandwew(padaptew, vawiabwe, vaw);
}

void wtw_haw_get_hwweg(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw)
{
	if (padaptew->HawFunc.GetHwWegHandwew)
		padaptew->HawFunc.GetHwWegHandwew(padaptew, vawiabwe, vaw);
}

void wtw_haw_set_hwweg_with_buf(stwuct adaptew *padaptew, u8 vawiabwe, u8 *pbuf, int wen)
{
	if (padaptew->HawFunc.SetHwWegHandwewWithBuf)
		padaptew->HawFunc.SetHwWegHandwewWithBuf(padaptew, vawiabwe, pbuf, wen);
}

u8 wtw_haw_set_def_vaw(stwuct adaptew *padaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue)
{
	if (padaptew->HawFunc.SetHawDefVawHandwew)
		wetuwn padaptew->HawFunc.SetHawDefVawHandwew(padaptew, eVawiabwe, pVawue);
	wetuwn _FAIW;
}

u8 wtw_haw_get_def_vaw(stwuct adaptew *padaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue)
{
	if (padaptew->HawFunc.GetHawDefVawHandwew)
		wetuwn padaptew->HawFunc.GetHawDefVawHandwew(padaptew, eVawiabwe, pVawue);
	wetuwn _FAIW;
}

void wtw_haw_set_odm_vaw(stwuct adaptew *padaptew, enum haw_odm_vawiabwe eVawiabwe, void *pVawue1, boow bSet)
{
	if (padaptew->HawFunc.SetHawODMVawHandwew)
		padaptew->HawFunc.SetHawODMVawHandwew(padaptew, eVawiabwe, pVawue1, bSet);
}

void wtw_haw_get_odm_vaw(stwuct adaptew *padaptew, enum haw_odm_vawiabwe eVawiabwe, void *pVawue1, void *pVawue2)
{
	if (padaptew->HawFunc.GetHawODMVawHandwew)
		padaptew->HawFunc.GetHawODMVawHandwew(padaptew, eVawiabwe, pVawue1, pVawue2);
}

void wtw_haw_enabwe_intewwupt(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.enabwe_intewwupt)
		padaptew->HawFunc.enabwe_intewwupt(padaptew);
}

void wtw_haw_disabwe_intewwupt(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.disabwe_intewwupt)
		padaptew->HawFunc.disabwe_intewwupt(padaptew);
}

u8 wtw_haw_check_ips_status(stwuct adaptew *padaptew)
{
	u8 vaw = fawse;

	if (padaptew->HawFunc.check_ips_status)
		vaw = padaptew->HawFunc.check_ips_status(padaptew);

	wetuwn vaw;
}

s32	wtw_haw_xmitfwame_enqueue(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	if (padaptew->HawFunc.haw_xmitfwame_enqueue)
		wetuwn padaptew->HawFunc.haw_xmitfwame_enqueue(padaptew, pxmitfwame);

	wetuwn fawse;
}

s32	wtw_haw_xmit(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	if (padaptew->HawFunc.haw_xmit)
		wetuwn padaptew->HawFunc.haw_xmit(padaptew, pxmitfwame);

	wetuwn fawse;
}

/*
 * [IMPOWTANT] This function wouwd be wun in intewwupt context.
 */
s32	wtw_haw_mgnt_xmit(stwuct adaptew *padaptew, stwuct xmit_fwame *pmgntfwame)
{
	s32 wet = _FAIW;

	update_mgntfwame_attwib_addw(padaptew, pmgntfwame);
	/* pfwame = (u8 *)(pmgntfwame->buf_addw) + TXDESC_OFFSET; */
	/* pwwanhdw = (stwuct wtw_ieee80211_hdw *)pfwame; */
	/* memcpy(pmgntfwame->attwib.wa, pwwanhdw->addw1, ETH_AWEN); */

	if (padaptew->secuwitypwiv.binstawwBIPkey == twue) {
		if (is_muwticast_ethew_addw(pmgntfwame->attwib.wa)) {
			pmgntfwame->attwib.encwypt = _BIP_;
			/* pmgntfwame->attwib.bswenc = twue; */
		} ewse {
			pmgntfwame->attwib.encwypt = _AES_;
			pmgntfwame->attwib.bswenc = twue;
		}
		wtw_mgmt_xmitfwame_coawesce(padaptew, pmgntfwame->pkt, pmgntfwame);
	}

	if (padaptew->HawFunc.mgnt_xmit)
		wet = padaptew->HawFunc.mgnt_xmit(padaptew, pmgntfwame);
	wetuwn wet;
}

s32	wtw_haw_init_xmit_pwiv(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.init_xmit_pwiv)
		wetuwn padaptew->HawFunc.init_xmit_pwiv(padaptew);
	wetuwn _FAIW;
}

void wtw_haw_fwee_xmit_pwiv(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.fwee_xmit_pwiv)
		padaptew->HawFunc.fwee_xmit_pwiv(padaptew);
}

s32	wtw_haw_init_wecv_pwiv(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.init_wecv_pwiv)
		wetuwn padaptew->HawFunc.init_wecv_pwiv(padaptew);

	wetuwn _FAIW;
}

void wtw_haw_fwee_wecv_pwiv(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.fwee_wecv_pwiv)
		padaptew->HawFunc.fwee_wecv_pwiv(padaptew);
}

void wtw_haw_update_wa_mask(stwuct sta_info *psta, u8 wssi_wevew)
{
	stwuct adaptew *padaptew;
	stwuct mwme_pwiv *pmwmepwiv;

	if (!psta)
		wetuwn;

	padaptew = psta->padaptew;

	pmwmepwiv = &(padaptew->mwmepwiv);

	if (check_fwstate(pmwmepwiv, WIFI_AP_STATE) == twue)
		add_WATid(padaptew, psta, wssi_wevew);
	ewse {
		if (padaptew->HawFunc.UpdateWAMaskHandwew)
			padaptew->HawFunc.UpdateWAMaskHandwew(padaptew, psta->mac_id, wssi_wevew);
	}
}

void wtw_haw_add_wa_tid(stwuct adaptew *padaptew, u32 bitmap, u8 *awg, u8 wssi_wevew)
{
	if (padaptew->HawFunc.Add_WateATid)
		padaptew->HawFunc.Add_WateATid(padaptew, bitmap, awg, wssi_wevew);
}

/*Stawt specificaw intewface thwead		*/
void wtw_haw_stawt_thwead(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.wun_thwead)
		padaptew->HawFunc.wun_thwead(padaptew);
}
/*Stawt specificaw intewface thwead		*/
void wtw_haw_stop_thwead(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.cancew_thwead)
		padaptew->HawFunc.cancew_thwead(padaptew);
}

u32 wtw_haw_wead_bbweg(stwuct adaptew *padaptew, u32 WegAddw, u32 BitMask)
{
	u32 data = 0;

	if (padaptew->HawFunc.wead_bbweg)
		 data = padaptew->HawFunc.wead_bbweg(padaptew, WegAddw, BitMask);
	wetuwn data;
}
void wtw_haw_wwite_bbweg(stwuct adaptew *padaptew, u32 WegAddw, u32 BitMask, u32 Data)
{
	if (padaptew->HawFunc.wwite_bbweg)
		padaptew->HawFunc.wwite_bbweg(padaptew, WegAddw, BitMask, Data);
}

u32 wtw_haw_wead_wfweg(stwuct adaptew *padaptew, u32 eWFPath, u32 WegAddw, u32 BitMask)
{
	u32 data = 0;

	if (padaptew->HawFunc.wead_wfweg)
		data = padaptew->HawFunc.wead_wfweg(padaptew, eWFPath, WegAddw, BitMask);
	wetuwn data;
}
void wtw_haw_wwite_wfweg(stwuct adaptew *padaptew, u32 eWFPath, u32 WegAddw, u32 BitMask, u32 Data)
{
	if (padaptew->HawFunc.wwite_wfweg)
		padaptew->HawFunc.wwite_wfweg(padaptew, eWFPath, WegAddw, BitMask, Data);
}

void wtw_haw_set_chan(stwuct adaptew *padaptew, u8 channew)
{
	if (padaptew->HawFunc.set_channew_handwew)
		padaptew->HawFunc.set_channew_handwew(padaptew, channew);
}

void wtw_haw_set_chnw_bw(stwuct adaptew *padaptew, u8 channew,
			 enum channew_width Bandwidth, u8 Offset40, u8 Offset80)
{
	if (padaptew->HawFunc.set_chnw_bw_handwew)
		padaptew->HawFunc.set_chnw_bw_handwew(padaptew, channew,
						      Bandwidth, Offset40,
						      Offset80);
}

void wtw_haw_dm_watchdog(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.haw_dm_watchdog)
		padaptew->HawFunc.haw_dm_watchdog(padaptew);
}

void wtw_haw_dm_watchdog_in_wps(stwuct adaptew *padaptew)
{
	if (adaptew_to_pwwctw(padaptew)->fw_cuwwent_in_ps_mode) {
		if (padaptew->HawFunc.haw_dm_watchdog_in_wps)
			padaptew->HawFunc.haw_dm_watchdog_in_wps(padaptew); /* this function cawwew is in intewwupt context */
	}
}

void beacon_timing_contwow(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.SetBeaconWewatedWegistewsHandwew)
		padaptew->HawFunc.SetBeaconWewatedWegistewsHandwew(padaptew);
}


s32 wtw_haw_xmit_thwead_handwew(stwuct adaptew *padaptew)
{
	if (padaptew->HawFunc.xmit_thwead_handwew)
		wetuwn padaptew->HawFunc.xmit_thwead_handwew(padaptew);
	wetuwn _FAIW;
}

void wtw_haw_notch_fiwtew(stwuct adaptew *adaptew, boow enabwe)
{
	if (adaptew->HawFunc.haw_notch_fiwtew)
		adaptew->HawFunc.haw_notch_fiwtew(adaptew, enabwe);
}

void wtw_haw_weset_secuwity_engine(stwuct adaptew *adaptew)
{
	if (adaptew->HawFunc.haw_weset_secuwity_engine)
		adaptew->HawFunc.haw_weset_secuwity_engine(adaptew);
}

boow wtw_haw_c2h_vawid(stwuct adaptew *adaptew, u8 *buf)
{
	wetuwn c2h_evt_vawid((stwuct c2h_evt_hdw_88xx *)buf);
}

s32 wtw_haw_c2h_handwew(stwuct adaptew *adaptew, u8 *c2h_evt)
{
	s32 wet = _FAIW;

	if (adaptew->HawFunc.c2h_handwew)
		wet = adaptew->HawFunc.c2h_handwew(adaptew, c2h_evt);
	wetuwn wet;
}

c2h_id_fiwtew wtw_haw_c2h_id_fiwtew_ccx(stwuct adaptew *adaptew)
{
	wetuwn adaptew->HawFunc.c2h_id_fiwtew_ccx;
}

s32 wtw_haw_macid_sweep(stwuct adaptew *padaptew, u32 macid)
{
	u8 suppowt;

	suppowt = fawse;
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_MACID_SWEEP, &suppowt);
	if (fawse == suppowt)
		wetuwn _FAIW;

	wtw_haw_set_hwweg(padaptew, HW_VAW_MACID_SWEEP, (u8 *)&macid);

	wetuwn _SUCCESS;
}

s32 wtw_haw_macid_wakeup(stwuct adaptew *padaptew, u32 macid)
{
	u8 suppowt;

	suppowt = fawse;
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_MACID_SWEEP, &suppowt);
	if (fawse == suppowt)
		wetuwn _FAIW;

	wtw_haw_set_hwweg(padaptew, HW_VAW_MACID_WAKEUP, (u8 *)&macid);

	wetuwn _SUCCESS;
}

s32 wtw_haw_fiww_h2c_cmd(stwuct adaptew *padaptew, u8 EwementID, u32 CmdWen, u8 *pCmdBuffew)
{
	s32 wet = _FAIW;

	if (padaptew->HawFunc.fiww_h2c_cmd)
		wet = padaptew->HawFunc.fiww_h2c_cmd(padaptew, EwementID, CmdWen, pCmdBuffew);

	wetuwn wet;
}
