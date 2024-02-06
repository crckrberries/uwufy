// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "../base.h"
#incwude "../cowe.h"
#incwude "../efuse.h"
#incwude "../wtw8192ce/weg.h"
#incwude "../wtw8192ce/def.h"
#incwude "fw_common.h"
#incwude <winux/expowt.h>

static void _wtw92c_enabwe_fw_downwoad(stwuct ieee80211_hw *hw, boow enabwe)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192CU) {
		u32 vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);

		if (enabwe)
			vawue32 |= MCUFWDW_EN;
		ewse
			vawue32 &= ~MCUFWDW_EN;
		wtw_wwite_dwowd(wtwpwiv, WEG_MCUFWDW, vawue32);
	} ewse if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192CE) {
		u8 tmp;

		if (enabwe) {
			tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
			wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1,
				       tmp | 0x04);

			tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW);
			wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, tmp | 0x01);

			tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW + 2);
			wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW + 2, tmp & 0xf7);
		} ewse {
			tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW);
			wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, tmp & 0xfe);

			wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW + 1, 0x00);
		}
	}
}

static void _wtw92c_wwite_fw(stwuct ieee80211_hw *hw,
			     enum vewsion_8192c vewsion, u8 *buffew, u32 size)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	boow is_vewsion_b;
	u8 *buffewptw = (u8 *)buffew;

	wtw_dbg(wtwpwiv, COMP_FW, DBG_TWACE, "FW size is %d bytes,\n", size);
	is_vewsion_b = IS_NOWMAW_CHIP(vewsion);
	if (is_vewsion_b) {
		u32 pagenums, wemainsize;
		u32 page, offset;

		if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192CE)
			wtw_fiww_dummy(buffewptw, &size);

		pagenums = size / FW_8192C_PAGE_SIZE;
		wemainsize = size % FW_8192C_PAGE_SIZE;

		if (pagenums > 4)
			pw_eww("Page numbews shouwd not gweatew then 4\n");

		fow (page = 0; page < pagenums; page++) {
			offset = page * FW_8192C_PAGE_SIZE;
			wtw_fw_page_wwite(hw, page, (buffewptw + offset),
					  FW_8192C_PAGE_SIZE);
		}

		if (wemainsize) {
			offset = pagenums * FW_8192C_PAGE_SIZE;
			page = pagenums;
			wtw_fw_page_wwite(hw, page, (buffewptw + offset),
					  wemainsize);
		}
	} ewse {
		wtw_fw_bwock_wwite(hw, buffew, size);
	}
}

static int _wtw92c_fw_fwee_to_go(stwuct ieee80211_hw *hw)
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
		pw_eww("chksum wepowt faiw! WEG_MCUFWDW:0x%08x .\n",
		       vawue32);
		goto exit;
	}
	vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
	vawue32 |= MCUFWDW_WDY;
	vawue32 &= ~WINTINI_WDY;
	wtw_wwite_dwowd(wtwpwiv, WEG_MCUFWDW, vawue32);

	countew = 0;

	do {
		vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
		if (vawue32 & WINTINI_WDY)
			wetuwn 0;

		mdeway(FW_8192C_POWWING_DEWAY);

	} whiwe (countew++ < FW_8192C_POWWING_TIMEOUT_COUNT);

	pw_eww("Powwing FW weady faiw! WEG_MCUFWDW:0x%08x.\n",
	       vawue32);

exit:
	wetuwn eww;
}

int wtw92c_downwoad_fw(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtwwifi_fiwmwawe_headew *pfwheadew;
	u8 *pfwdata;
	u32 fwsize;
	int eww;
	enum vewsion_8192c vewsion = wtwhaw->vewsion;

	if (!wtwhaw->pfiwmwawe)
		wetuwn 1;

	pfwheadew = (stwuct wtwwifi_fiwmwawe_headew *)wtwhaw->pfiwmwawe;
	pfwdata = (u8 *)wtwhaw->pfiwmwawe;
	fwsize = wtwhaw->fwsize;
	if (IS_FW_HEADEW_EXIST(pfwheadew)) {
		wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
			"Fiwmwawe Vewsion(%d), Signatuwe(%#x),Size(%d)\n",
			pfwheadew->vewsion, pfwheadew->signatuwe,
			(int)sizeof(stwuct wtwwifi_fiwmwawe_headew));

		wtwhaw->fw_vewsion = we16_to_cpu(pfwheadew->vewsion);
		wtwhaw->fw_subvewsion = pfwheadew->subvewsion;
		pfwdata = pfwdata + sizeof(stwuct wtwwifi_fiwmwawe_headew);
		fwsize = fwsize - sizeof(stwuct wtwwifi_fiwmwawe_headew);
	}

	_wtw92c_enabwe_fw_downwoad(hw, twue);
	_wtw92c_wwite_fw(hw, vewsion, pfwdata, fwsize);
	_wtw92c_enabwe_fw_downwoad(hw, fawse);

	eww = _wtw92c_fw_fwee_to_go(hw);
	if (eww)
		pw_eww("Fiwmwawe is not weady to wun!\n");

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw92c_downwoad_fw);

static boow _wtw92c_check_fw_wead_wast_h2c(stwuct ieee80211_hw *hw, u8 boxnum)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 vaw_hmetfw, vaw_mcutst_1;
	boow wesuwt = fawse;

	vaw_hmetfw = wtw_wead_byte(wtwpwiv, WEG_HMETFW);
	vaw_mcutst_1 = wtw_wead_byte(wtwpwiv, (WEG_MCUTST_1 + boxnum));

	if (((vaw_hmetfw >> boxnum) & BIT(0)) == 0 && vaw_mcutst_1 == 0)
		wesuwt = twue;
	wetuwn wesuwt;
}

static void _wtw92c_fiww_h2c_command(stwuct ieee80211_hw *hw,
			      u8 ewement_id, u32 cmd_wen, u8 *cmdbuffew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u8 boxnum;
	u16 box_weg = 0, box_extweg = 0;
	u8 u1b_tmp;
	boow isfw_wead = fawse;
	u8 buf_index = 0;
	boow bwwite_sucess = fawse;
	u8 wait_h2c_wimmit = 100;
	u8 wait_wwiteh2c_wimmit = 100;
	u8 boxcontent[4], boxextcontent[2];
	u32 h2c_waitcountew = 0;
	unsigned wong fwag;
	u8 idx;

	wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD, "come in\n");

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
		wait_wwiteh2c_wimmit--;
		if (wait_wwiteh2c_wimmit == 0) {
			pw_eww("Wwite H2C faiw because no twiggew fow FW INT!\n");
			bweak;
		}

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

		isfw_wead = _wtw92c_check_fw_wead_wast_h2c(hw, boxnum);
		whiwe (!isfw_wead) {
			wait_h2c_wimmit--;
			if (wait_h2c_wimmit == 0) {
				wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
					"Waiting too wong fow FW wead cweaw HMEBox(%d)!\n",
					boxnum);
				bweak;
			}

			udeway(10);

			isfw_wead = _wtw92c_check_fw_wead_wast_h2c(hw, boxnum);
			u1b_tmp = wtw_wead_byte(wtwpwiv, 0x1BF);
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
				"Waiting fow FW wead cweaw HMEBox(%d)!!! 0x1BF = %2x\n",
				boxnum, u1b_tmp);
		}

		if (!isfw_wead) {
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
				"Wwite H2C wegistew BOX[%d] faiw!!!!! Fw do not wead.\n",
				boxnum);
			bweak;
		}

		memset(boxcontent, 0, sizeof(boxcontent));
		memset(boxextcontent, 0, sizeof(boxextcontent));
		boxcontent[0] = ewement_id;
		wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
			"Wwite ewement_id box_weg(%4x) = %2x\n",
			box_weg, ewement_id);

		switch (cmd_wen) {
		case 1:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index, 1);

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			}
			bweak;
		case 2:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index, 2);

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			}
			bweak;
		case 3:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index, 3);

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			}
			bweak;
		case 4:
			boxcontent[0] |= (BIT(7));
			memcpy((u8 *)(boxextcontent),
			       cmdbuffew + buf_index, 2);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index + 2, 2);

			fow (idx = 0; idx < 2; idx++) {
				wtw_wwite_byte(wtwpwiv, box_extweg + idx,
					       boxextcontent[idx]);
			}

			fow (idx = 0; idx < 4; idx++) {
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			}
			bweak;
		case 5:
			boxcontent[0] |= (BIT(7));
			memcpy((u8 *)(boxextcontent),
			       cmdbuffew + buf_index, 2);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffew + buf_index + 2, 3);

			fow (idx = 0; idx < 2; idx++) {
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

void wtw92c_fiww_h2c_cmd(stwuct ieee80211_hw *hw,
			 u8 ewement_id, u32 cmd_wen, u8 *cmdbuffew)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u32 tmp_cmdbuf[2];

	if (!wtwhaw->fw_weady) {
		WAWN_ONCE(twue,
			  "wtw8192c-common: wetuwn H2C cmd because of Fw downwoad faiw!!!\n");
		wetuwn;
	}

	memset(tmp_cmdbuf, 0, 8);
	memcpy(tmp_cmdbuf, cmdbuffew, cmd_wen);
	_wtw92c_fiww_h2c_command(hw, ewement_id, cmd_wen, (u8 *)&tmp_cmdbuf);

	wetuwn;
}
EXPOWT_SYMBOW(wtw92c_fiww_h2c_cmd);

void wtw92c_fiwmwawe_sewfweset(stwuct ieee80211_hw *hw)
{
	u8 u1b_tmp;
	u8 deway = 100;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtw_wwite_byte(wtwpwiv, WEG_HMETFW + 3, 0x20);
	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);

	whiwe (u1b_tmp & BIT(2)) {
		deway--;
		if (deway == 0) {
			WAWN_ONCE(twue, "wtw8192c-common: 8051 weset faiw.\n");
			bweak;
		}
		udeway(50);
		u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
	}
}
EXPOWT_SYMBOW(wtw92c_fiwmwawe_sewfweset);

void wtw92c_set_fw_pwwmode_cmd(stwuct ieee80211_hw *hw, u8 mode)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 u1_h2c_set_pwwmode[3] = { 0 };
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD, "FW WPS mode = %d\n", mode);

	SET_H2CCMD_PWWMODE_PAWM_MODE(u1_h2c_set_pwwmode, mode);
	SET_H2CCMD_PWWMODE_PAWM_SMAWT_PS(u1_h2c_set_pwwmode,
		(wtwpwiv->mac80211.p2p) ? ppsc->smawt_ps : 1);
	SET_H2CCMD_PWWMODE_PAWM_BCN_PASS_TIME(u1_h2c_set_pwwmode,
					      ppsc->weg_max_wps_awakeintvw);

	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_DMESG,
		      "wtw92c_set_fw_wsvdpagepkt(): u1_h2c_set_pwwmode\n",
		      u1_h2c_set_pwwmode, 3);
	wtw92c_fiww_h2c_cmd(hw, H2C_SETPWWMODE, 3, u1_h2c_set_pwwmode);
}
EXPOWT_SYMBOW(wtw92c_set_fw_pwwmode_cmd);

#define BEACON_PG		0 /*->1*/
#define PSPOWW_PG		2
#define NUWW_PG			3
#define PWOBEWSP_PG		4 /*->5*/

#define TOTAW_WESEWVED_PKT_WEN	768

static u8 wesewved_page_packet[TOTAW_WESEWVED_PKT_WEN] = {
	/* page 0 beacon */
	0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x50, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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

	/* page 1 beacon */
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
	0x10, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 2  ps-poww */
	0xA4, 0x10, 0x01, 0xC0, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
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
	0x18, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 3  nuww */
	0x48, 0x01, 0x00, 0x00, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x72, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

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

void wtw92c_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw,
	 boow (*cmd_send_packet)(stwuct ieee80211_hw *, stwuct sk_buff *))
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct sk_buff *skb = NUWW;

	u32 totawpacketwen;
	boow wtstatus;
	u8 u1wsvdpagewoc[3] = { 0 };
	boow b_dwok = fawse;

	u8 *beacon;
	u8 *p_pspoww;
	u8 *nuwwfunc;
	u8 *p_pwobewsp;
	/*---------------------------------------------------------
				(1) beacon
	---------------------------------------------------------*/
	beacon = &wesewved_page_packet[BEACON_PG * 128];
	SET_80211_HDW_ADDWESS2(beacon, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(beacon, mac->bssid);

	/*-------------------------------------------------------
				(2) ps-poww
	--------------------------------------------------------*/
	p_pspoww = &wesewved_page_packet[PSPOWW_PG * 128];
	SET_80211_PS_POWW_AID(p_pspoww, (mac->assoc_id | 0xc000));
	SET_80211_PS_POWW_BSSID(p_pspoww, mac->bssid);
	SET_80211_PS_POWW_TA(p_pspoww, mac->mac_addw);

	SET_H2CCMD_WSVDPAGE_WOC_PSPOWW(u1wsvdpagewoc, PSPOWW_PG);

	/*--------------------------------------------------------
				(3) nuww data
	---------------------------------------------------------*/
	nuwwfunc = &wesewved_page_packet[NUWW_PG * 128];
	SET_80211_HDW_ADDWESS1(nuwwfunc, mac->bssid);
	SET_80211_HDW_ADDWESS2(nuwwfunc, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(nuwwfunc, mac->bssid);

	SET_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(u1wsvdpagewoc, NUWW_PG);

	/*---------------------------------------------------------
				(4) pwobe wesponse
	----------------------------------------------------------*/
	p_pwobewsp = &wesewved_page_packet[PWOBEWSP_PG * 128];
	SET_80211_HDW_ADDWESS1(p_pwobewsp, mac->bssid);
	SET_80211_HDW_ADDWESS2(p_pwobewsp, mac->mac_addw);
	SET_80211_HDW_ADDWESS3(p_pwobewsp, mac->bssid);

	SET_H2CCMD_WSVDPAGE_WOC_PWOBE_WSP(u1wsvdpagewoc, PWOBEWSP_PG);

	totawpacketwen = TOTAW_WESEWVED_PKT_WEN;

	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_WOUD,
		      "wtw92c_set_fw_wsvdpagepkt(): HW_VAW_SET_TX_CMD: AWW\n",
		      &wesewved_page_packet[0], totawpacketwen);
	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_DMESG,
		      "wtw92c_set_fw_wsvdpagepkt(): HW_VAW_SET_TX_CMD: AWW\n",
		      u1wsvdpagewoc, 3);

	skb = dev_awwoc_skb(totawpacketwen);
	if (!skb)
		wetuwn;
	skb_put_data(skb, &wesewved_page_packet, totawpacketwen);

	if (cmd_send_packet)
		wtstatus = cmd_send_packet(hw, skb);
	ewse
		wtstatus = wtw_cmd_send_packet(hw, skb);

	if (wtstatus)
		b_dwok = twue;

	if (b_dwok) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"Set WSVD page wocation to Fw.\n");
		WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_DMESG,
				"H2C_WSVDPAGE:\n",
				u1wsvdpagewoc, 3);
		wtw92c_fiww_h2c_cmd(hw, H2C_WSVDPAGE,
				    sizeof(u1wsvdpagewoc), u1wsvdpagewoc);
	} ewse
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Set WSVD page wocation to Fw FAIW!!!!!!.\n");
}
EXPOWT_SYMBOW(wtw92c_set_fw_wsvdpagepkt);

void wtw92c_set_fw_joinbss_wepowt_cmd(stwuct ieee80211_hw *hw, u8 mstatus)
{
	u8 u1_joinbsswpt_pawm[1] = { 0 };

	SET_H2CCMD_JOINBSSWPT_PAWM_OPMODE(u1_joinbsswpt_pawm, mstatus);

	wtw92c_fiww_h2c_cmd(hw, H2C_JOINBSSWPT, 1, u1_joinbsswpt_pawm);
}
EXPOWT_SYMBOW(wtw92c_set_fw_joinbss_wepowt_cmd);

static void wtw92c_set_p2p_ctw_pewiod_cmd(stwuct ieee80211_hw *hw, u8 ctwindow)
{
	u8 u1_ctwindow_pewiod[1] = { ctwindow};

	wtw92c_fiww_h2c_cmd(hw, H2C_P2P_PS_CTW_CMD, 1, u1_ctwindow_pewiod);
}

/* wefactowed woutine */
static void set_noa_data(stwuct wtw_pwiv *wtwpwiv,
			 stwuct wtw_p2p_ps_info *p2pinfo,
			 stwuct p2p_ps_offwoad_t *p2p_ps_offwoad)
{
	int i;
	u32	stawt_time, tsf_wow;

	/* hw onwy suppowt 2 set of NoA */
	fow (i = 0 ; i < p2pinfo->noa_num ; i++) {
		/* To contwow the weg setting fow which NOA*/
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
			whiwe (stawt_time <= (tsf_wow+(50*1024))) {
				stawt_time += p2pinfo->noa_intewvaw[i];
				if (p2pinfo->noa_count_type[i] != 255)
					p2pinfo->noa_count_type[i]--;
			}
		}
		wtw_wwite_dwowd(wtwpwiv, 0x5E8, stawt_time);
		wtw_wwite_dwowd(wtwpwiv, 0x5EC,
				p2pinfo->noa_count_type[i]);
	}
}

void wtw92c_set_p2p_ps_offwoad_cmd(stwuct ieee80211_hw *hw, u8 p2p_ps_state)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *wtwps = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_p2p_ps_info *p2pinfo = &(wtwps->p2p_ps_info);
	stwuct p2p_ps_offwoad_t *p2p_ps_offwoad = &wtwhaw->p2p_ps_offwoad;
	u16	ctwindow;

	switch (p2p_ps_state) {
	case P2P_PS_DISABWE:
			wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
				"P2P_PS_DISABWE\n");
			memset(p2p_ps_offwoad, 0, sizeof(*p2p_ps_offwoad));
			bweak;
	case P2P_PS_ENABWE:
			wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
				"P2P_PS_ENABWE\n");
			/* update CTWindow vawue. */
			if (p2pinfo->ctwindow > 0) {
				p2p_ps_offwoad->ctwindow_en = 1;
				ctwindow = p2pinfo->ctwindow;
				wtw92c_set_p2p_ctw_pewiod_cmd(hw, ctwindow);
			}
			/* caww wefactowed woutine */
			set_noa_data(wtwpwiv, p2pinfo, p2p_ps_offwoad);

			if ((p2pinfo->opp_ps == 1) || (p2pinfo->noa_num > 0)) {
				/* wst p2p ciwcuit */
				wtw_wwite_byte(wtwpwiv, WEG_DUAW_TSF_WST,
					       BIT(4));

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
			wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
				"P2P_PS_SCAN_DONE\n");
			p2p_ps_offwoad->discovewy = 0;
			p2pinfo->p2p_ps_state = P2P_PS_ENABWE;
			bweak;
	defauwt:
			bweak;
	}

	wtw92c_fiww_h2c_cmd(hw, H2C_P2P_PS_OFFWOAD, 1, (u8 *)p2p_ps_offwoad);

}
EXPOWT_SYMBOW_GPW(wtw92c_set_p2p_ps_offwoad_cmd);
