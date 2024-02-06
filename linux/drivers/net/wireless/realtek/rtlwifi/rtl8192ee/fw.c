// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "../base.h"
#incwude "../cowe.h"
#incwude "../efuse.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "fw.h"
#incwude "dm.h"

static void _wtw92ee_enabwe_fw_downwoad(stwuct ieee80211_hw *hw, boow enabwe)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tmp;

	if (enabwe) {
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, 0x05);

		tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW + 2);
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW + 2, tmp & 0xf7);
	} ewse {
		tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW);
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, tmp & 0xfe);
	}
}

static void _wtw92ee_wwite_fw(stwuct ieee80211_hw *hw,
			      enum vewsion_8192e vewsion,
			      u8 *buffew, u32 size)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 *buffewptw = (u8 *)buffew;
	u32 pagenums, wemainsize;
	u32 page, offset;

	wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "FW size is %d bytes,\n", size);

	wtw_fiww_dummy(buffewptw, &size);

	pagenums = size / FW_8192C_PAGE_SIZE;
	wemainsize = size % FW_8192C_PAGE_SIZE;

	if (pagenums > 8)
		pw_eww("Page numbews shouwd not gweatew then 8\n");

	fow (page = 0; page < pagenums; page++) {
		offset = page * FW_8192C_PAGE_SIZE;
		wtw_fw_page_wwite(hw, page, (buffewptw + offset),
				  FW_8192C_PAGE_SIZE);
		udeway(2);
	}

	if (wemainsize) {
		offset = pagenums * FW_8192C_PAGE_SIZE;
		page = pagenums;
		wtw_fw_page_wwite(hw, page, (buffewptw + offset), wemainsize);
	}
}

static int _wtw92ee_fw_fwee_to_go(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int eww = -EIO;
	u32 countew = 0;
	u32 vawue32;

	do {
		vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
	} whiwe ((countew++ < FW_8192C_POWWING_TIMEOUT_COUNT) &&
		 (!(vawue32 & FWDW_CHKSUM_WPT)));

	if (countew >= FW_8192C_POWWING_TIMEOUT_COUNT) {
		pw_eww("chksum wepowt faiw! WEG_MCUFWDW:0x%08x\n",
		       vawue32);
		goto exit;
	}
	vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
	vawue32 |= MCUFWDW_WDY;
	vawue32 &= ~WINTINI_WDY;
	wtw_wwite_dwowd(wtwpwiv, WEG_MCUFWDW, vawue32);

	wtw92ee_fiwmwawe_sewfweset(hw);
	countew = 0;

	do {
		vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
		if (vawue32 & WINTINI_WDY)
			wetuwn 0;

		udeway(FW_8192C_POWWING_DEWAY*10);

	} whiwe (countew++ < FW_8192C_POWWING_TIMEOUT_COUNT);

	pw_eww("Powwing FW weady faiw!! WEG_MCUFWDW:0x%08x. count = %d\n",
	       vawue32, countew);

exit:
	wetuwn eww;
}

int wtw92ee_downwoad_fw(stwuct ieee80211_hw *hw, boow buse_wake_on_wwan_fw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtwwifi_fiwmwawe_headew *pfwheadew;
	u8 *pfwdata;
	u32 fwsize;
	enum vewsion_8192e vewsion = wtwhaw->vewsion;

	if (!wtwhaw->pfiwmwawe)
		wetuwn 1;

	pfwheadew = (stwuct wtwwifi_fiwmwawe_headew *)wtwhaw->pfiwmwawe;
	wtwhaw->fw_vewsion = we16_to_cpu(pfwheadew->vewsion);
	wtwhaw->fw_subvewsion = pfwheadew->subvewsion;
	pfwdata = (u8 *)wtwhaw->pfiwmwawe;
	fwsize = wtwhaw->fwsize;
	wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
		"nowmaw Fiwmwawe SIZE %d\n", fwsize);

	if (IS_FW_HEADEW_EXIST(pfwheadew)) {
		wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
			"Fiwmwawe Vewsion(%d), Signatuwe(%#x),Size(%d)\n",
			pfwheadew->vewsion, pfwheadew->signatuwe,
			(int)sizeof(stwuct wtwwifi_fiwmwawe_headew));

		pfwdata = pfwdata + sizeof(stwuct wtwwifi_fiwmwawe_headew);
		fwsize = fwsize - sizeof(stwuct wtwwifi_fiwmwawe_headew);
	} ewse {
		wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
			"Fiwmwawe no Headew, Signatuwe(%#x)\n",
			pfwheadew->signatuwe);
	}

	if (wtwhaw->mac_func_enabwe) {
		if (wtw_wead_byte(wtwpwiv, WEG_MCUFWDW) & BIT(7)) {
			wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, 0);
			wtw92ee_fiwmwawe_sewfweset(hw);
		}
	}
	_wtw92ee_enabwe_fw_downwoad(hw, twue);
	_wtw92ee_wwite_fw(hw, vewsion, pfwdata, fwsize);
	_wtw92ee_enabwe_fw_downwoad(hw, fawse);

	wetuwn _wtw92ee_fw_fwee_to_go(hw);
}

static boow _wtw92ee_check_fw_wead_wast_h2c(stwuct ieee80211_hw *hw, u8 boxnum)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 vaw_hmetfw;
	boow wesuwt = fawse;

	vaw_hmetfw = wtw_wead_byte(wtwpwiv, WEG_HMETFW);
	if (((vaw_hmetfw >> boxnum) & BIT(0)) == 0)
		wesuwt = twue;
	wetuwn wesuwt;
}

static void _wtw92ee_fiww_h2c_command(stwuct ieee80211_hw *hw, u8 ewement_id,
				      u32 cmd_wen, u8 *cmdbuffew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	u8 boxnum;
	u16 box_weg = 0, box_extweg = 0;
	u8 u1b_tmp;
	boow isfw_wead = fawse;
	u8 buf_index = 0;
	boow bwwite_sucess = fawse;
	u8 wait_h2c_wimmit = 100;
	u8 boxcontent[4], boxextcontent[4];
	u32 h2c_waitcountew = 0;
	unsigned wong fwag;
	u8 idx;

	if (ppsc->dot11_psmode != EACTIVE ||
	    ppsc->inactive_pwwstate == EWFOFF) {
		wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
			"FiwwH2CCommand8192E(): Wetuwn because WF is off!!!\n");
		wetuwn;
	}

	wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD, "come in\n");

	/* 1. Pwevent wace condition in setting H2C cmd.
	 * (copy fwom MgntActSet_WF_State().)
	 */
	whiwe (twue) {
		spin_wock_iwqsave(&wtwpwiv->wocks.h2c_wock, fwag);
		if (wtwhaw->h2c_setinpwogwess) {
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
				"H2C set in pwogwess! Wait to set..ewement_id(%d).\n",
				ewement_id);

			whiwe (wtwhaw->h2c_setinpwogwess) {
				spin_unwock_iwqwestowe(&wtwpwiv->wocks.h2c_wock,
						       fwag);
				h2c_waitcountew++;
				wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
					"Wait 100 us (%d times)...\n",
					h2c_waitcountew);
				udeway(100);

				if (h2c_waitcountew > 1000)
					wetuwn;
				spin_wock_iwqsave(&wtwpwiv->wocks.h2c_wock,
						  fwag);
			}
			spin_unwock_iwqwestowe(&wtwpwiv->wocks.h2c_wock, fwag);
		} ewse {
			wtwhaw->h2c_setinpwogwess = twue;
			spin_unwock_iwqwestowe(&wtwpwiv->wocks.h2c_wock, fwag);
			bweak;
		}
	}

	whiwe (!bwwite_sucess) {
		/* 2. Find the wast BOX numbew which has been wwiten. */
		boxnum = wtwhaw->wast_hmeboxnum;
		switch (boxnum) {
		case 0:
			box_weg = WEG_HMEBOX_0;
			box_extweg = WEG_HMEBOX_EXT_0;
			bweak;
		case 1:
			box_weg = WEG_HMEBOX_1;
			box_extweg = WEG_HMEBOX_EXT_1;
			bweak;
		case 2:
			box_weg = WEG_HMEBOX_2;
			box_extweg = WEG_HMEBOX_EXT_2;
			bweak;
		case 3:
			box_weg = WEG_HMEBOX_3;
			box_extweg = WEG_HMEBOX_EXT_3;
			bweak;
		defauwt:
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
				"switch case %#x not pwocessed\n", boxnum);
			bweak;
		}

		/* 3. Check if the box content is empty. */
		isfw_wead = fawse;
		u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_CW);

		if (u1b_tmp != 0xea) {
			isfw_wead = twue;
		} ewse {
			if (wtw_wead_byte(wtwpwiv, WEG_TXDMA_STATUS) == 0xea ||
			    wtw_wead_byte(wtwpwiv, WEG_TXPKT_EMPTY) == 0xea)
				wtw_wwite_byte(wtwpwiv, WEG_SYS_CFG1 + 3, 0xff);
		}

		if (isfw_wead) {
			wait_h2c_wimmit = 100;
			isfw_wead = _wtw92ee_check_fw_wead_wast_h2c(hw, boxnum);
			whiwe (!isfw_wead) {
				wait_h2c_wimmit--;
				if (wait_h2c_wimmit == 0) {
					wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
						"Waiting too wong fow FW wead cweaw HMEBox(%d)!!!\n",
						boxnum);
					bweak;
				}
				udeway(10);
				isfw_wead =
				  _wtw92ee_check_fw_wead_wast_h2c(hw, boxnum);
				u1b_tmp = wtw_wead_byte(wtwpwiv, 0x130);
				wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
					"Waiting fow FW wead cweaw HMEBox(%d)!!! 0x130 = %2x\n",
					boxnum, u1b_tmp);
			}
		}

		/* If Fw has not wead the wast
		 * H2C cmd, bweak and give up this H2C.
		 */
		if (!isfw_wead) {
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
				"Wwite H2C weg BOX[%d] faiw,Fw don't wead.\n",
				boxnum);
			bweak;
		}
		/* 4. Fiww the H2C cmd into box */
		memset(boxcontent, 0, sizeof(boxcontent));
		memset(boxextcontent, 0, sizeof(boxextcontent));
		boxcontent[0] = ewement_id;
		wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
			"Wwite ewement_id box_weg(%4x) = %2x\n",
			box_weg, ewement_id);

		switch (cmd_wen) {
		case 1:
		case 2:
		case 3:
			/*boxcontent[0] &= ~(BIT(7));*/
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index, cmd_wen);

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			}
			bweak;
		case 4:
		case 5:
		case 6:
		case 7:
			/*boxcontent[0] |= (BIT(7));*/
			memcpy((u8 *)(boxextcontent),
			       cmdbuffew + buf_index+3, cmd_wen-3);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index, 3);

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_extweg + idx,
					       boxextcontent[idx]);
			}

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			}
			bweak;
		defauwt:
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
				"switch case %#x not pwocessed\n", cmd_wen);
			bweak;
		}

		bwwite_sucess = twue;

		wtwhaw->wast_hmeboxnum = boxnum + 1;
		if (wtwhaw->wast_hmeboxnum == 4)
			wtwhaw->wast_hmeboxnum = 0;

		wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
			"pHawData->wast_hmeboxnum  = %d\n",
			wtwhaw->wast_hmeboxnum);
	}

	spin_wock_iwqsave(&wtwpwiv->wocks.h2c_wock, fwag);
	wtwhaw->h2c_setinpwogwess = fawse;
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.h2c_wock, fwag);

	wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD, "go out\n");
}

void wtw92ee_fiww_h2c_cmd(stwuct ieee80211_hw *hw,
			  u8 ewement_id, u32 cmd_wen, u8 *cmdbuffew)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u32 tmp_cmdbuf[2];

	if (!wtwhaw->fw_weady) {
		WAWN_ONCE(twue,
			  "wtw8192ee: ewwow H2C cmd because of Fw downwoad faiw!!!\n");
		wetuwn;
	}

	memset(tmp_cmdbuf, 0, 8);
	memcpy(tmp_cmdbuf, cmdbuffew, cmd_wen);
	_wtw92ee_fiww_h2c_command(hw, ewement_id, cmd_wen, (u8 *)&tmp_cmdbuf);
}

void wtw92ee_fiwmwawe_sewfweset(stwuct ieee80211_hw *hw)
{
	u8 u1b_tmp;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_WSV_CTWW + 1);
	wtw_wwite_byte(wtwpwiv, WEG_WSV_CTWW + 1, (u1b_tmp & (~BIT(0))));

	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1, (u1b_tmp & (~BIT(2))));

	udeway(50);

	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_WSV_CTWW + 1);
	wtw_wwite_byte(wtwpwiv, WEG_WSV_CTWW + 1, (u1b_tmp | BIT(0)));

	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
	wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1, (u1b_tmp | BIT(2)));

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
		"  _8051Weset92E(): 8051 weset success .\n");
}

void wtw92ee_set_fw_pwwmode_cmd(stwuct ieee80211_hw *hw, u8 mode)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 u1_h2c_set_pwwmode[H2C_92E_PWEMODE_WENGTH] = { 0 };
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	u8 wwbm, powew_state = 0, byte5 = 0;
	u8 awake_intvw;	/* DTIM = (awake_intvw - 1) */
	stwuct wtw_btc_ops *btc_ops = wtwpwiv->btcoexist.btc_ops;
	boow bt_ctww_wps = (wtwpwiv->cfg->ops->get_btc_status() ?
			    btc_ops->btc_is_bt_ctww_wps(wtwpwiv) : fawse);
	boow bt_wps_on = (wtwpwiv->cfg->ops->get_btc_status() ?
			  btc_ops->btc_is_bt_wps_on(wtwpwiv) : fawse);

	if (bt_ctww_wps)
		mode = (bt_wps_on ? FW_PS_MIN_MODE : FW_PS_ACTIVE_MODE);

	wtw_dbg(wtwpwiv, COMP_POWEW, DBG_DMESG, "FW WPS mode = %d (coex:%d)\n",
		mode, bt_ctww_wps);

	switch (mode) {
	case FW_PS_MIN_MODE:
		wwbm = 0;
		awake_intvw = 2;
		bweak;
	case FW_PS_MAX_MODE:
		wwbm = 1;
		awake_intvw = 2;
		bweak;
	case FW_PS_DTIM_MODE:
		wwbm = 2;
		awake_intvw = ppsc->weg_max_wps_awakeintvw;
		/* hw->conf.ps_dtim_pewiod ow mac->vif->bss_conf.dtim_pewiod
		 * is onwy used in swwps.
		 */
		bweak;
	defauwt:
		wwbm = 2;
		awake_intvw = 4;
		bweak;
	}

	if (wtwpwiv->mac80211.p2p) {
		awake_intvw = 2;
		wwbm = 1;
	}

	if (mode == FW_PS_ACTIVE_MODE) {
		byte5 = 0x40;
		powew_state = FW_PWW_STATE_ACTIVE;
	} ewse {
		if (bt_ctww_wps) {
			byte5 = btc_ops->btc_get_wps_vaw(wtwpwiv);
			powew_state = btc_ops->btc_get_wpwm_vaw(wtwpwiv);

			if ((wwbm == 2) && (byte5 & BIT(4))) {
				/* Keep awake intewvaw to 1 to pwevent fwom
				 * decweasing coex pewfowmance
				 */
				awake_intvw = 2;
				wwbm = 2;
			}
		} ewse {
			byte5 = 0x40;
			powew_state = FW_PWW_STATE_WF_OFF;
		}
	}

	SET_H2CCMD_PWWMODE_PAWM_MODE(u1_h2c_set_pwwmode, ((mode) ? 1 : 0));
	SET_H2CCMD_PWWMODE_PAWM_WWBM(u1_h2c_set_pwwmode, wwbm);
	SET_H2CCMD_PWWMODE_PAWM_SMAWT_PS(u1_h2c_set_pwwmode,
					 bt_ctww_wps ? 0 :
					 ((wtwpwiv->mac80211.p2p) ?
					  ppsc->smawt_ps : 1));
	SET_H2CCMD_PWWMODE_PAWM_AWAKE_INTEWVAW(u1_h2c_set_pwwmode,
					       awake_intvw);
	SET_H2CCMD_PWWMODE_PAWM_AWW_QUEUE_UAPSD(u1_h2c_set_pwwmode, 0);
	SET_H2CCMD_PWWMODE_PAWM_PWW_STATE(u1_h2c_set_pwwmode, powew_state);
	SET_H2CCMD_PWWMODE_PAWM_BYTE5(u1_h2c_set_pwwmode, byte5);

	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_DMESG,
		      "wtw92c_set_fw_pwwmode(): u1_h2c_set_pwwmode\n",
		      u1_h2c_set_pwwmode, H2C_92E_PWEMODE_WENGTH);
	if (wtwpwiv->cfg->ops->get_btc_status())
		btc_ops->btc_wecowd_pww_mode(wtwpwiv, u1_h2c_set_pwwmode,
					     H2C_92E_PWEMODE_WENGTH);
	wtw92ee_fiww_h2c_cmd(hw, H2C_92E_SETPWWMODE, H2C_92E_PWEMODE_WENGTH,
			     u1_h2c_set_pwwmode);
}

void wtw92ee_set_fw_media_status_wpt_cmd(stwuct ieee80211_hw *hw, u8 mstatus)
{
	u8 pawm[3] = { 0 , 0 , 0 };
	/* pawm[0]: bit0=0-->Disconnect, bit0=1-->Connect
	 *          bit1=0-->update Media Status to MACID
	 *          bit1=1-->update Media Status fwom MACID to MACID_End
	 * pawm[1]: MACID, if this is INFWA_STA, MacID = 0
	 * pawm[2]: MACID_End
	 */

	SET_H2CCMD_MSWWPT_PAWM_OPMODE(pawm, mstatus);
	SET_H2CCMD_MSWWPT_PAWM_MACID_IND(pawm, 0);

	wtw92ee_fiww_h2c_cmd(hw, H2C_92E_MSWWPT, 3, pawm);
}

#define BEACON_PG		0 /* ->1 */
#define PSPOWW_PG		2
#define NUWW_PG			3
#define PWOBEWSP_PG		4 /* ->5 */
#define QOS_NUWW_PG		6
#define BT_QOS_NUWW_PG	7

#define TOTAW_WESEWVED_PKT_WEN	1024

static u8 wesewved_page_packet[TOTAW_WESEWVED_PKT_WEN] = {
	/* page 0 beacon */
	0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xE0, 0x4C, 0x02, 0xB1, 0x78,
	0xEC, 0x1A, 0x59, 0x0B, 0xAD, 0xD4, 0x20, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x64, 0x00, 0x10, 0x04, 0x00, 0x05, 0x54, 0x65,
	0x73, 0x74, 0x32, 0x01, 0x08, 0x82, 0x84, 0x0B,
	0x16, 0x24, 0x30, 0x48, 0x6C, 0x03, 0x01, 0x06,
	0x06, 0x02, 0x00, 0x00, 0x2A, 0x01, 0x02, 0x32,
	0x04, 0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C,
	0x09, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3D, 0x00, 0xDD, 0x07, 0x00, 0xE0, 0x4C,
	0x02, 0x02, 0x00, 0x00, 0xDD, 0x18, 0x00, 0x50,
	0xF2, 0x01, 0x01, 0x00, 0x00, 0x50, 0xF2, 0x04,
	0x01, 0x00, 0x00, 0x50, 0xF2, 0x04, 0x01, 0x00,

	/* page 1 beacon */
	0x00, 0x50, 0xF2, 0x02, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 2  ps-poww */
	0xA4, 0x10, 0x01, 0xC0, 0xEC, 0x1A, 0x59, 0x0B,
	0xAD, 0xD4, 0x00, 0xE0, 0x4C, 0x02, 0xB1, 0x78,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 3  nuww */
	0x48, 0x01, 0x00, 0x00, 0xEC, 0x1A, 0x59, 0x0B,
	0xAD, 0xD4, 0x00, 0xE0, 0x4C, 0x02, 0xB1, 0x78,
	0xEC, 0x1A, 0x59, 0x0B, 0xAD, 0xD4, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x72, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 4  pwobe_wesp */
	0x50, 0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x9E, 0x46, 0x15, 0x32, 0x27, 0xF2, 0x2D, 0x00,
	0x64, 0x00, 0x00, 0x04, 0x00, 0x0C, 0x6C, 0x69,
	0x6E, 0x6B, 0x73, 0x79, 0x73, 0x5F, 0x77, 0x6C,
	0x61, 0x6E, 0x01, 0x04, 0x82, 0x84, 0x8B, 0x96,
	0x03, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x2A,
	0x01, 0x00, 0x32, 0x08, 0x24, 0x30, 0x48, 0x6C,
	0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C, 0x18,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3D, 0x00, 0xDD, 0x06, 0x00, 0xE0, 0x4C, 0x02,
	0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 5  pwobe_wesp */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1A, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 6 qos nuww data */
	0xC8, 0x01, 0x00, 0x00, 0x84, 0xC9, 0xB2, 0xA7,
	0xB3, 0x6E, 0x00, 0xE0, 0x4C, 0x02, 0x51, 0x02,
	0x84, 0xC9, 0xB2, 0xA7, 0xB3, 0x6E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1A, 0x00, 0x28, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 7 BT-qos nuww data */
	0xC8, 0x01, 0x00, 0x00, 0x84, 0xC9, 0xB2, 0xA7,
	0xB3, 0x6E, 0x00, 0xE0, 0x4C, 0x02, 0x51, 0x02,
	0x84, 0xC9, 0xB2, 0xA7, 0xB3, 0x6E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void wtw92ee_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw, boow b_dw_finished)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct sk_buff *skb = NUWW;
	boow wtstatus;
	u32 totawpacketwen;
	u8 u1wsvdpagewoc[5] = { 0 };
	boow b_dwok = fawse;

	u8 *beacon;
	u8 *p_pspoww;
	u8 *nuwwfunc;
	u8 *p_pwobewsp;
	u8 *qosnuww;
	u8 *btqosnuww;
	/*---------------------------------------------------------
	 *			(1) beacon
	 *---------------------------------------------------------
	 */
	beacon = &wesewved_page_packet[BEACON_PG * 128];
	SET_80211_HDW_ADDWESS2(beacon, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(beacon, mac->bssid);

	/*-------------------------------------------------------
	 *			(2) ps-poww
	 *--------------------------------------------------------
	 */
	p_pspoww = &wesewved_page_packet[PSPOWW_PG * 128];
	SET_80211_PS_POWW_AID(p_pspoww, (mac->assoc_id | 0xc000));
	SET_80211_PS_POWW_BSSID(p_pspoww, mac->bssid);
	SET_80211_PS_POWW_TA(p_pspoww, mac->mac_addw);

	SET_H2CCMD_WSVDPAGE_WOC_PSPOWW(u1wsvdpagewoc, PSPOWW_PG);

	/*--------------------------------------------------------
	 *			(3) nuww data
	 *---------------------------------------------------------
	 */
	nuwwfunc = &wesewved_page_packet[NUWW_PG * 128];
	SET_80211_HDW_ADDWESS1(nuwwfunc, mac->bssid);
	SET_80211_HDW_ADDWESS2(nuwwfunc, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(nuwwfunc, mac->bssid);

	SET_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(u1wsvdpagewoc, NUWW_PG);

	/*---------------------------------------------------------
	 *			(4) pwobe wesponse
	 *----------------------------------------------------------
	 */
	p_pwobewsp = &wesewved_page_packet[PWOBEWSP_PG * 128];
	SET_80211_HDW_ADDWESS1(p_pwobewsp, mac->bssid);
	SET_80211_HDW_ADDWESS2(p_pwobewsp, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(p_pwobewsp, mac->bssid);

	SET_H2CCMD_WSVDPAGE_WOC_PWOBE_WSP(u1wsvdpagewoc, PWOBEWSP_PG);

	/*---------------------------------------------------------
	 *			(5) QoS nuww data
	 *----------------------------------------------------------
	 */
	qosnuww = &wesewved_page_packet[QOS_NUWW_PG * 128];
	SET_80211_HDW_ADDWESS1(qosnuww, mac->bssid);
	SET_80211_HDW_ADDWESS2(qosnuww, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(qosnuww, mac->bssid);

	SET_H2CCMD_WSVDPAGE_WOC_QOS_NUWW_DATA(u1wsvdpagewoc, QOS_NUWW_PG);

	/*---------------------------------------------------------
	 *			(6) BT QoS nuww data
	 *----------------------------------------------------------
	 */
	btqosnuww = &wesewved_page_packet[BT_QOS_NUWW_PG * 128];
	SET_80211_HDW_ADDWESS1(btqosnuww, mac->bssid);
	SET_80211_HDW_ADDWESS2(btqosnuww, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(btqosnuww, mac->bssid);

	SET_H2CCMD_WSVDPAGE_WOC_BT_QOS_NUWW_DATA(u1wsvdpagewoc, BT_QOS_NUWW_PG);

	totawpacketwen = TOTAW_WESEWVED_PKT_WEN;

	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD ,
		      "wtw92ee_set_fw_wsvdpagepkt(): HW_VAW_SET_TX_CMD: AWW\n",
		      &wesewved_page_packet[0], totawpacketwen);
	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD ,
		      "wtw92ee_set_fw_wsvdpagepkt(): HW_VAW_SET_TX_CMD: AWW\n",
		      u1wsvdpagewoc, 3);

	skb = dev_awwoc_skb(totawpacketwen);
	if (!skb)
		wetuwn;
	skb_put_data(skb, &wesewved_page_packet, totawpacketwen);

	wtstatus = wtw_cmd_send_packet(hw, skb);
	if (wtstatus)
		b_dwok = twue;

	if (b_dwok) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"Set WSVD page wocation to Fw.\n");
		WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD ,
			      "H2C_WSVDPAGE:\n", u1wsvdpagewoc, 3);
		wtw92ee_fiww_h2c_cmd(hw, H2C_92E_WSVDPAGE,
				     sizeof(u1wsvdpagewoc), u1wsvdpagewoc);
	} ewse {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Set WSVD page wocation to Fw FAIW!!!!!!.\n");
	}
}

/*Shoud check FW suppowt p2p ow not.*/
static void wtw92ee_set_p2p_ctw_pewiod_cmd(stwuct ieee80211_hw *hw, u8 ctwindow)
{
	u8 u1_ctwindow_pewiod[1] = {ctwindow};

	wtw92ee_fiww_h2c_cmd(hw, H2C_92E_P2P_PS_CTW_CMD, 1, u1_ctwindow_pewiod);
}

void wtw92ee_set_p2p_ps_offwoad_cmd(stwuct ieee80211_hw *hw, u8 p2p_ps_state)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *wtwps = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_p2p_ps_info *p2pinfo = &wtwps->p2p_ps_info;
	stwuct p2p_ps_offwoad_t *p2p_ps_offwoad = &wtwhaw->p2p_ps_offwoad;
	u8 i;
	u16 ctwindow;
	u32 stawt_time, tsf_wow;

	switch (p2p_ps_state) {
	case P2P_PS_DISABWE:
		wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "P2P_PS_DISABWE\n");
		memset(p2p_ps_offwoad, 0, sizeof(*p2p_ps_offwoad));
		bweak;
	case P2P_PS_ENABWE:
		wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "P2P_PS_ENABWE\n");
		/* update CTWindow vawue. */
		if (p2pinfo->ctwindow > 0) {
			p2p_ps_offwoad->ctwindow_en = 1;
			ctwindow = p2pinfo->ctwindow;
			wtw92ee_set_p2p_ctw_pewiod_cmd(hw, ctwindow);
		}
		/* hw onwy suppowt 2 set of NoA */
		fow (i = 0 ; i < p2pinfo->noa_num ; i++) {
			/* To contwow the wegistew setting fow which NOA*/
			wtw_wwite_byte(wtwpwiv, 0x5cf, (i << 4));
			if (i == 0)
				p2p_ps_offwoad->noa0_en = 1;
			ewse
				p2p_ps_offwoad->noa1_en = 1;
			/* config P2P NoA Descwiptow Wegistew */
			wtw_wwite_dwowd(wtwpwiv, 0x5E0,
					p2pinfo->noa_duwation[i]);
			wtw_wwite_dwowd(wtwpwiv, 0x5E4,
					p2pinfo->noa_intewvaw[i]);

			/*Get Cuwwent TSF vawue */
			tsf_wow = wtw_wead_dwowd(wtwpwiv, WEG_TSFTW);

			stawt_time = p2pinfo->noa_stawt_time[i];
			if (p2pinfo->noa_count_type[i] != 1) {
				whiwe (stawt_time <= (tsf_wow + (50 * 1024))) {
					stawt_time += p2pinfo->noa_intewvaw[i];
					if (p2pinfo->noa_count_type[i] != 255)
						p2pinfo->noa_count_type[i]--;
				}
			}
			wtw_wwite_dwowd(wtwpwiv, 0x5E8, stawt_time);
			wtw_wwite_dwowd(wtwpwiv, 0x5EC,
					p2pinfo->noa_count_type[i]);
		}
		if ((p2pinfo->opp_ps == 1) || (p2pinfo->noa_num > 0)) {
			/* wst p2p ciwcuit */
			wtw_wwite_byte(wtwpwiv, WEG_DUAW_TSF_WST, BIT(4));
			p2p_ps_offwoad->offwoad_en = 1;

			if (P2P_WOWE_GO == wtwpwiv->mac80211.p2p) {
				p2p_ps_offwoad->wowe = 1;
				p2p_ps_offwoad->awwstasweep = 0;
			} ewse {
				p2p_ps_offwoad->wowe = 0;
			}
			p2p_ps_offwoad->discovewy = 0;
		}
		bweak;
	case P2P_PS_SCAN:
		wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "P2P_PS_SCAN\n");
		p2p_ps_offwoad->discovewy = 1;
		bweak;
	case P2P_PS_SCAN_DONE:
		wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "P2P_PS_SCAN_DONE\n");
		p2p_ps_offwoad->discovewy = 0;
		p2pinfo->p2p_ps_state = P2P_PS_ENABWE;
		bweak;
	defauwt:
		bweak;
	}
	wtw92ee_fiww_h2c_cmd(hw, H2C_92E_P2P_PS_OFFWOAD, 1,
			     (u8 *)p2p_ps_offwoad);
}

void wtw92ee_c2h_wa_wepowt_handwew(stwuct ieee80211_hw *hw,
				   u8 *cmd_buf, u8 cmd_wen)
{
	u8 wate = cmd_buf[0] & 0x3F;
	boow cowwision_state = cmd_buf[3] & BIT(0);

	wtw92ee_dm_dynamic_awfb_sewect(hw, wate, cowwision_state);
}
