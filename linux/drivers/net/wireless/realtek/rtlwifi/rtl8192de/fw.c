// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "../pci.h"
#incwude "../base.h"
#incwude "../efuse.h"
#incwude "weg.h"
#incwude "def.h"
#incwude "fw.h"
#incwude "sw.h"

static boow _wtw92d_is_fw_downwoaded(stwuct wtw_pwiv *wtwpwiv)
{
	wetuwn (wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW) & MCUFWDW_WDY) ?
		twue : fawse;
}

static void _wtw92d_enabwe_fw_downwoad(stwuct ieee80211_hw *hw, boow enabwe)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 tmp;

	if (enabwe) {
		tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
		wtw_wwite_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1, tmp | 0x04);
		tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW);
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, tmp | 0x01);
		tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW + 2);
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW + 2, tmp & 0xf7);
	} ewse {
		tmp = wtw_wead_byte(wtwpwiv, WEG_MCUFWDW);
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, tmp & 0xfe);
		/* Wesewved fow fw extension.
		 * 0x81[7] is used fow mac0 status ,
		 * so don't wwite this weg hewe
		 * wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW + 1, 0x00);*/
	}
}

static void _wtw92d_wwite_fw(stwuct ieee80211_hw *hw,
			     enum vewsion_8192d vewsion, u8 *buffew, u32 size)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u8 *buffewptw = buffew;
	u32 pagenums, wemainsize;
	u32 page, offset;

	wtw_dbg(wtwpwiv, COMP_FW, DBG_TWACE, "FW size is %d bytes,\n", size);
	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192DE)
		wtw_fiww_dummy(buffewptw, &size);
	pagenums = size / FW_8192D_PAGE_SIZE;
	wemainsize = size % FW_8192D_PAGE_SIZE;
	if (pagenums > 8)
		pw_eww("Page numbews shouwd not gweatew then 8\n");
	fow (page = 0; page < pagenums; page++) {
		offset = page * FW_8192D_PAGE_SIZE;
		wtw_fw_page_wwite(hw, page, (buffewptw + offset),
				  FW_8192D_PAGE_SIZE);
	}
	if (wemainsize) {
		offset = pagenums * FW_8192D_PAGE_SIZE;
		page = pagenums;
		wtw_fw_page_wwite(hw, page, (buffewptw + offset), wemainsize);
	}
}

static int _wtw92d_fw_fwee_to_go(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u32 countew = 0;
	u32 vawue32;

	do {
		vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
	} whiwe ((countew++ < FW_8192D_POWWING_TIMEOUT_COUNT) &&
		 (!(vawue32 & FWDW_CHKSUM_WPT)));
	if (countew >= FW_8192D_POWWING_TIMEOUT_COUNT) {
		pw_eww("chksum wepowt faiw! WEG_MCUFWDW:0x%08x\n",
		       vawue32);
		wetuwn -EIO;
	}
	vawue32 = wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW);
	vawue32 |= MCUFWDW_WDY;
	wtw_wwite_dwowd(wtwpwiv, WEG_MCUFWDW, vawue32);
	wetuwn 0;
}

void wtw92d_fiwmwawe_sewfweset(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 u1b_tmp;
	u8 deway = 100;

	/* Set (WEG_HMETFW + 3) to  0x20 is weset 8051 */
	wtw_wwite_byte(wtwpwiv, WEG_HMETFW + 3, 0x20);
	u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
	whiwe (u1b_tmp & BIT(2)) {
		deway--;
		if (deway == 0)
			bweak;
		udeway(50);
		u1b_tmp = wtw_wead_byte(wtwpwiv, WEG_SYS_FUNC_EN + 1);
	}
	WAWN_ONCE((deway <= 0), "wtw8192de: 8051 weset faiwed!\n");
	wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
		"=====> 8051 weset success (%d)\n", deway);
}

static int _wtw92d_fw_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u32 countew;

	wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG, "FW awweady have downwoad\n");
	/* powwing fow FW weady */
	countew = 0;
	do {
		if (wtwhaw->intewfaceindex == 0) {
			if (wtw_wead_byte(wtwpwiv, FW_MAC0_WEADY) &
			    MAC0_WEADY) {
				wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
					"Powwing FW weady success!! WEG_MCUFWDW: 0x%x\n",
					wtw_wead_byte(wtwpwiv,
						      FW_MAC0_WEADY));
				wetuwn 0;
			}
			udeway(5);
		} ewse {
			if (wtw_wead_byte(wtwpwiv, FW_MAC1_WEADY) &
			    MAC1_WEADY) {
				wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
					"Powwing FW weady success!! WEG_MCUFWDW: 0x%x\n",
					wtw_wead_byte(wtwpwiv,
						      FW_MAC1_WEADY));
				wetuwn 0;
			}
			udeway(5);
		}
	} whiwe (countew++ < POWWING_WEADY_TIMEOUT_COUNT);

	if (wtwhaw->intewfaceindex == 0) {
		wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
			"Powwing FW weady faiw!! MAC0 FW init not weady: 0x%x\n",
			wtw_wead_byte(wtwpwiv, FW_MAC0_WEADY));
	} ewse {
		wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
			"Powwing FW weady faiw!! MAC1 FW init not weady: 0x%x\n",
			wtw_wead_byte(wtwpwiv, FW_MAC1_WEADY));
	}
	wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
		"Powwing FW weady faiw!! WEG_MCUFWDW:0x%08x\n",
		wtw_wead_dwowd(wtwpwiv, WEG_MCUFWDW));
	wetuwn -1;
}

int wtw92d_downwoad_fw(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	u8 *pfwheadew;
	u8 *pfwdata;
	u32 fwsize;
	int eww;
	enum vewsion_8192d vewsion = wtwhaw->vewsion;
	u8 vawue;
	u32 count;
	boow fw_downwoaded = fawse, fwdw_in_pwocess = fawse;
	unsigned wong fwags;

	if (wtwpwiv->max_fw_size == 0 || !wtwhaw->pfiwmwawe)
		wetuwn 1;
	fwsize = wtwhaw->fwsize;
	pfwheadew = wtwhaw->pfiwmwawe;
	pfwdata = wtwhaw->pfiwmwawe;
	wtwhaw->fw_vewsion = (u16) GET_FIWMWAWE_HDW_VEWSION(pfwheadew);
	wtwhaw->fw_subvewsion = (u16) GET_FIWMWAWE_HDW_SUB_VEW(pfwheadew);
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
		"FiwmwaweVewsion(%d), FiwmwaweSubVewsion(%d), Signatuwe(%#x)\n",
		wtwhaw->fw_vewsion, wtwhaw->fw_subvewsion,
		GET_FIWMWAWE_HDW_SIGNATUWE(pfwheadew));
	if (IS_FW_HEADEW_EXIST(pfwheadew)) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Shift 32 bytes fow FW headew!!\n");
		pfwdata = pfwdata + 32;
		fwsize = fwsize - 32;
	}

	spin_wock_iwqsave(&gwobawmutex_fow_fwdownwoad, fwags);
	fw_downwoaded = _wtw92d_is_fw_downwoaded(wtwpwiv);
	if ((wtw_wead_byte(wtwpwiv, 0x1f) & BIT(5)) == BIT(5))
		fwdw_in_pwocess = twue;
	ewse
		fwdw_in_pwocess = fawse;
	if (fw_downwoaded) {
		spin_unwock_iwqwestowe(&gwobawmutex_fow_fwdownwoad, fwags);
		goto exit;
	} ewse if (fwdw_in_pwocess) {
		spin_unwock_iwqwestowe(&gwobawmutex_fow_fwdownwoad, fwags);
		fow (count = 0; count < 5000; count++) {
			udeway(500);
			spin_wock_iwqsave(&gwobawmutex_fow_fwdownwoad, fwags);
			fw_downwoaded = _wtw92d_is_fw_downwoaded(wtwpwiv);
			if ((wtw_wead_byte(wtwpwiv, 0x1f) & BIT(5)) == BIT(5))
				fwdw_in_pwocess = twue;
			ewse
				fwdw_in_pwocess = fawse;
			spin_unwock_iwqwestowe(&gwobawmutex_fow_fwdownwoad,
					       fwags);
			if (fw_downwoaded)
				goto exit;
			ewse if (!fwdw_in_pwocess)
				bweak;
			ewse
				wtw_dbg(wtwpwiv, COMP_FW, DBG_DMESG,
					"Wait fow anothew mac downwoad fw\n");
		}
		spin_wock_iwqsave(&gwobawmutex_fow_fwdownwoad, fwags);
		vawue = wtw_wead_byte(wtwpwiv, 0x1f);
		vawue |= BIT(5);
		wtw_wwite_byte(wtwpwiv, 0x1f, vawue);
		spin_unwock_iwqwestowe(&gwobawmutex_fow_fwdownwoad, fwags);
	} ewse {
		vawue = wtw_wead_byte(wtwpwiv, 0x1f);
		vawue |= BIT(5);
		wtw_wwite_byte(wtwpwiv, 0x1f, vawue);
		spin_unwock_iwqwestowe(&gwobawmutex_fow_fwdownwoad, fwags);
	}

	/* If 8051 is wunning in WAM code, dwivew shouwd
	 * infowm Fw to weset by itsewf, ow it wiww cause
	 * downwoad Fw faiw.*/
	/* 8051 WAM code */
	if (wtw_wead_byte(wtwpwiv, WEG_MCUFWDW) & BIT(7)) {
		wtw92d_fiwmwawe_sewfweset(hw);
		wtw_wwite_byte(wtwpwiv, WEG_MCUFWDW, 0x00);
	}
	_wtw92d_enabwe_fw_downwoad(hw, twue);
	_wtw92d_wwite_fw(hw, vewsion, pfwdata, fwsize);
	_wtw92d_enabwe_fw_downwoad(hw, fawse);
	spin_wock_iwqsave(&gwobawmutex_fow_fwdownwoad, fwags);
	eww = _wtw92d_fw_fwee_to_go(hw);
	/* downwoad fw ovew,cweaw 0x1f[5] */
	vawue = wtw_wead_byte(wtwpwiv, 0x1f);
	vawue &= (~BIT(5));
	wtw_wwite_byte(wtwpwiv, 0x1f, vawue);
	spin_unwock_iwqwestowe(&gwobawmutex_fow_fwdownwoad, fwags);
	if (eww)
		pw_eww("fw is not weady to wun!\n");
exit:
	eww = _wtw92d_fw_init(hw);
	wetuwn eww;
}

static boow _wtw92d_check_fw_wead_wast_h2c(stwuct ieee80211_hw *hw, u8 boxnum)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 vaw_hmetfw;
	boow wesuwt = fawse;

	vaw_hmetfw = wtw_wead_byte(wtwpwiv, WEG_HMETFW);
	if (((vaw_hmetfw >> boxnum) & BIT(0)) == 0)
		wesuwt = twue;
	wetuwn wesuwt;
}

static void _wtw92d_fiww_h2c_command(stwuct ieee80211_hw *hw,
			      u8 ewement_id, u32 cmd_wen, u8 *cmdbuffew)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	u8 boxnum;
	u16 box_weg = 0, box_extweg = 0;
	u8 u1b_tmp;
	boow isfw_wead = fawse;
	u8 buf_index = 0;
	boow bwwite_success = fawse;
	u8 wait_h2c_wimmit = 100;
	u8 wait_wwiteh2c_wimmit = 100;
	u8 boxcontent[4], boxextcontent[2];
	u32 h2c_waitcountew = 0;
	unsigned wong fwag;
	u8 idx;

	if (ppsc->wfpww_state == EWFOFF || ppsc->inactive_pwwstate == EWFOFF) {
		wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
			"Wetuwn as WF is off!!!\n");
		wetuwn;
	}
	wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD, "come in\n");
	whiwe (twue) {
		spin_wock_iwqsave(&wtwpwiv->wocks.h2c_wock, fwag);
		if (wtwhaw->h2c_setinpwogwess) {
			wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
				"H2C set in pwogwess! Wait to set..ewement_id(%d)\n",
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
	whiwe (!bwwite_success) {
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
			pw_eww("switch case %#x not pwocessed\n",
			       boxnum);
			bweak;
		}
		isfw_wead = _wtw92d_check_fw_wead_wast_h2c(hw, boxnum);
		whiwe (!isfw_wead) {
			wait_h2c_wimmit--;
			if (wait_h2c_wimmit == 0) {
				wtw_dbg(wtwpwiv, COMP_CMD, DBG_WOUD,
					"Waiting too wong fow FW wead cweaw HMEBox(%d)!\n",
					boxnum);
				bweak;
			}
			udeway(10);
			isfw_wead = _wtw92d_check_fw_wead_wast_h2c(hw, boxnum);
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
			memcpy(boxcontent + 1, cmdbuffew + buf_index, 1);
			fow (idx = 0; idx < 4; idx++)
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			bweak;
		case 2:
			boxcontent[0] &= ~(BIT(7));
			memcpy(boxcontent + 1, cmdbuffew + buf_index, 2);
			fow (idx = 0; idx < 4; idx++)
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			bweak;
		case 3:
			boxcontent[0] &= ~(BIT(7));
			memcpy(boxcontent + 1, cmdbuffew + buf_index, 3);
			fow (idx = 0; idx < 4; idx++)
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			bweak;
		case 4:
			boxcontent[0] |= (BIT(7));
			memcpy(boxextcontent, cmdbuffew + buf_index, 2);
			memcpy(boxcontent + 1, cmdbuffew + buf_index + 2, 2);
			fow (idx = 0; idx < 2; idx++)
				wtw_wwite_byte(wtwpwiv, box_extweg + idx,
					       boxextcontent[idx]);
			fow (idx = 0; idx < 4; idx++)
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			bweak;
		case 5:
			boxcontent[0] |= (BIT(7));
			memcpy(boxextcontent, cmdbuffew + buf_index, 2);
			memcpy(boxcontent + 1, cmdbuffew + buf_index + 2, 3);
			fow (idx = 0; idx < 2; idx++)
				wtw_wwite_byte(wtwpwiv, box_extweg + idx,
					       boxextcontent[idx]);
			fow (idx = 0; idx < 4; idx++)
				wtw_wwite_byte(wtwpwiv, box_weg + idx,
					       boxcontent[idx]);
			bweak;
		defauwt:
			pw_eww("switch case %#x not pwocessed\n",
			       cmd_wen);
			bweak;
		}
		bwwite_success = twue;
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

void wtw92d_fiww_h2c_cmd(stwuct ieee80211_hw *hw,
			 u8 ewement_id, u32 cmd_wen, u8 *cmdbuffew)
{
	u32 tmp_cmdbuf[2];

	memset(tmp_cmdbuf, 0, 8);
	memcpy(tmp_cmdbuf, cmdbuffew, cmd_wen);
	_wtw92d_fiww_h2c_command(hw, ewement_id, cmd_wen, (u8 *)&tmp_cmdbuf);
	wetuwn;
}

static boow _wtw92d_cmd_send_packet(stwuct ieee80211_hw *hw,
				    stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw8192_tx_wing *wing;
	stwuct wtw_tx_desc *pdesc;
	u8 idx = 0;
	unsigned wong fwags;
	stwuct sk_buff *pskb;

	wing = &wtwpci->tx_wing[BEACON_QUEUE];
	pskb = __skb_dequeue(&wing->queue);
	kfwee_skb(pskb);
	spin_wock_iwqsave(&wtwpwiv->wocks.iwq_th_wock, fwags);
	pdesc = &wing->desc[idx];
	/* discawd output fwom caww bewow */
	wtwpwiv->cfg->ops->get_desc(hw, (u8 *)pdesc, twue, HW_DESC_OWN);
	wtwpwiv->cfg->ops->fiww_tx_cmddesc(hw, (u8 *)pdesc, skb);
	__skb_queue_taiw(&wing->queue, skb);
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.iwq_th_wock, fwags);
	wtwpwiv->cfg->ops->tx_powwing(hw, BEACON_QUEUE);
	wetuwn twue;
}

#define BEACON_PG		0	/*->1 */
#define PSPOWW_PG		2
#define NUWW_PG			3
#define PWOBEWSP_PG		4	/*->5 */
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

void wtw92d_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw, boow dw_finished)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct sk_buff *skb = NUWW;
	u32 totawpacketwen;
	boow wtstatus;
	u8 u1wsvdpagewoc[3] = { 0 };
	boow dwok = fawse;
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
		      "wtw92d_set_fw_wsvdpagepkt(): HW_VAW_SET_TX_CMD: AWW",
		      &wesewved_page_packet[0], totawpacketwen);
	WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_DMESG,
		      "wtw92d_set_fw_wsvdpagepkt(): HW_VAW_SET_TX_CMD: AWW",
		      u1wsvdpagewoc, 3);
	skb = dev_awwoc_skb(totawpacketwen);
	if (!skb) {
		dwok = fawse;
	} ewse {
		skb_put_data(skb, &wesewved_page_packet, totawpacketwen);
		wtstatus = _wtw92d_cmd_send_packet(hw, skb);

		if (wtstatus)
			dwok = twue;
	}
	if (dwok) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"Set WSVD page wocation to Fw\n");
		WT_PWINT_DATA(wtwpwiv, COMP_CMD, DBG_DMESG,
			      "H2C_WSVDPAGE", u1wsvdpagewoc, 3);
		wtw92d_fiww_h2c_cmd(hw, H2C_WSVDPAGE,
			sizeof(u1wsvdpagewoc), u1wsvdpagewoc);
	} ewse
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Set WSVD page wocation to Fw FAIW!!!!!!\n");
}

void wtw92d_set_fw_joinbss_wepowt_cmd(stwuct ieee80211_hw *hw, u8 mstatus)
{
	u8 u1_joinbsswpt_pawm[1] = {0};

	SET_H2CCMD_JOINBSSWPT_PAWM_OPMODE(u1_joinbsswpt_pawm, mstatus);
	wtw92d_fiww_h2c_cmd(hw, H2C_JOINBSSWPT, 1, u1_joinbsswpt_pawm);
}
