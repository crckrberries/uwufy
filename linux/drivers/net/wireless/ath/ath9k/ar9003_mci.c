/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/expowt.h>
#incwude "hw.h"
#incwude "hw-ops.h"
#incwude "aw9003_phy.h"
#incwude "aw9003_mci.h"
#incwude "aw9003_aic.h"

static void aw9003_mci_weset_weq_wakeup(stwuct ath_hw *ah)
{
	WEG_WMW_FIEWD(ah, AW_MCI_COMMAND2,
		      AW_MCI_COMMAND2_WESET_WEQ_WAKEUP, 1);
	udeway(1);
	WEG_WMW_FIEWD(ah, AW_MCI_COMMAND2,
		      AW_MCI_COMMAND2_WESET_WEQ_WAKEUP, 0);
}

static int aw9003_mci_wait_fow_intewwupt(stwuct ath_hw *ah, u32 addwess,
					u32 bit_position, int time_out)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	whiwe (time_out) {
		if (!(WEG_WEAD(ah, addwess) & bit_position)) {
			udeway(10);
			time_out -= 10;

			if (time_out < 0)
				bweak;
			ewse
				continue;
		}
		WEG_WWITE(ah, addwess, bit_position);

		if (addwess != AW_MCI_INTEWWUPT_WX_MSG_WAW)
			bweak;

		if (bit_position & AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE)
			aw9003_mci_weset_weq_wakeup(ah);

		if (bit_position & (AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING |
				    AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING))
			WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW,
				  AW_MCI_INTEWWUPT_WEMOTE_SWEEP_UPDATE);

		WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW, AW_MCI_INTEWWUPT_WX_MSG);
		bweak;
	}

	if (time_out <= 0) {
		ath_dbg(common, MCI,
			"MCI Wait fow Weg 0x%08x = 0x%08x timeout\n",
			addwess, bit_position);
		ath_dbg(common, MCI,
			"MCI INT_WAW = 0x%08x, WX_MSG_WAW = 0x%08x\n",
			WEG_WEAD(ah, AW_MCI_INTEWWUPT_WAW),
			WEG_WEAD(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW));
		time_out = 0;
	}

	wetuwn time_out;
}

static void aw9003_mci_wemote_weset(stwuct ath_hw *ah, boow wait_done)
{
	u32 paywoad[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffff00};

	aw9003_mci_send_message(ah, MCI_WEMOTE_WESET, 0, paywoad, 16,
				wait_done, fawse);
	udeway(5);
}

static void aw9003_mci_send_wna_twansfew(stwuct ath_hw *ah, boow wait_done)
{
	u32 paywoad = 0x00000000;

	aw9003_mci_send_message(ah, MCI_WNA_TWANS, 0, &paywoad, 1,
				wait_done, fawse);
}

static void aw9003_mci_send_weq_wake(stwuct ath_hw *ah, boow wait_done)
{
	aw9003_mci_send_message(ah, MCI_WEQ_WAKE, MCI_FWAG_DISABWE_TIMESTAMP,
				NUWW, 0, wait_done, fawse);
	udeway(5);
}

static void aw9003_mci_send_sys_waking(stwuct ath_hw *ah, boow wait_done)
{
	aw9003_mci_send_message(ah, MCI_SYS_WAKING, MCI_FWAG_DISABWE_TIMESTAMP,
				NUWW, 0, wait_done, fawse);
}

static void aw9003_mci_send_wna_take(stwuct ath_hw *ah, boow wait_done)
{
	u32 paywoad = 0x70000000;

	aw9003_mci_send_message(ah, MCI_WNA_TAKE, 0, &paywoad, 1,
				wait_done, fawse);
}

static void aw9003_mci_send_sys_sweeping(stwuct ath_hw *ah, boow wait_done)
{
	aw9003_mci_send_message(ah, MCI_SYS_SWEEPING,
				MCI_FWAG_DISABWE_TIMESTAMP,
				NUWW, 0, wait_done, fawse);
}

static void aw9003_mci_send_coex_vewsion_quewy(stwuct ath_hw *ah,
					       boow wait_done)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 paywoad[4] = {0, 0, 0, 0};

	if (mci->bt_vewsion_known ||
	    (mci->bt_state == MCI_BT_SWEEP))
		wetuwn;

	MCI_GPM_SET_TYPE_OPCODE(paywoad, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_VEWSION_QUEWY);
	aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad, 16, wait_done, twue);
}

static void aw9003_mci_send_coex_vewsion_wesponse(stwuct ath_hw *ah,
						  boow wait_done)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 paywoad[4] = {0, 0, 0, 0};

	MCI_GPM_SET_TYPE_OPCODE(paywoad, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_VEWSION_WESPONSE);
	*(((u8 *)paywoad) + MCI_GPM_COEX_B_MAJOW_VEWSION) =
		mci->wwan_vew_majow;
	*(((u8 *)paywoad) + MCI_GPM_COEX_B_MINOW_VEWSION) =
		mci->wwan_vew_minow;
	aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad, 16, wait_done, twue);
}

static void aw9003_mci_send_coex_wwan_channews(stwuct ath_hw *ah,
					       boow wait_done)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *paywoad = &mci->wwan_channews[0];

	if (!mci->wwan_channews_update ||
	    (mci->bt_state == MCI_BT_SWEEP))
		wetuwn;

	MCI_GPM_SET_TYPE_OPCODE(paywoad, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_WWAN_CHANNEWS);
	aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad, 16, wait_done, twue);
	MCI_GPM_SET_TYPE_OPCODE(paywoad, 0xff, 0xff);
}

static void aw9003_mci_send_coex_bt_status_quewy(stwuct ath_hw *ah,
						boow wait_done, u8 quewy_type)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 paywoad[4] = {0, 0, 0, 0};
	boow quewy_btinfo;

	if (mci->bt_state == MCI_BT_SWEEP)
		wetuwn;

	quewy_btinfo = !!(quewy_type & (MCI_GPM_COEX_QUEWY_BT_AWW_INFO |
					MCI_GPM_COEX_QUEWY_BT_TOPOWOGY));
	MCI_GPM_SET_TYPE_OPCODE(paywoad, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_STATUS_QUEWY);

	*(((u8 *)paywoad) + MCI_GPM_COEX_B_BT_BITMAP) = quewy_type;

	/*
	 * If bt_status_quewy message is  not sent successfuwwy,
	 * then need_fwush_btinfo shouwd be set again.
	 */
	if (!aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad, 16,
				wait_done, twue)) {
		if (quewy_btinfo)
			mci->need_fwush_btinfo = twue;
	}

	if (quewy_btinfo)
		mci->quewy_bt = fawse;
}

static void aw9003_mci_send_coex_hawt_bt_gpm(stwuct ath_hw *ah, boow hawt,
					     boow wait_done)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 paywoad[4] = {0, 0, 0, 0};

	MCI_GPM_SET_TYPE_OPCODE(paywoad, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_HAWT_BT_GPM);

	if (hawt) {
		mci->quewy_bt = twue;
		/* Send next unhawt no mattew hawt sent ow not */
		mci->unhawt_bt_gpm = twue;
		mci->need_fwush_btinfo = twue;
		*(((u8 *)paywoad) + MCI_GPM_COEX_B_HAWT_STATE) =
			MCI_GPM_COEX_BT_GPM_HAWT;
	} ewse
		*(((u8 *)paywoad) + MCI_GPM_COEX_B_HAWT_STATE) =
			MCI_GPM_COEX_BT_GPM_UNHAWT;

	aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad, 16, wait_done, twue);
}

static void aw9003_mci_pwep_intewface(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 saved_mci_int_en;
	u32 mci_timeout = 150;

	mci->bt_state = MCI_BT_SWEEP;
	saved_mci_int_en = WEG_WEAD(ah, AW_MCI_INTEWWUPT_EN);

	WEG_WWITE(ah, AW_MCI_INTEWWUPT_EN, 0);
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
		  WEG_WEAD(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW));
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW,
		  WEG_WEAD(ah, AW_MCI_INTEWWUPT_WAW));

	aw9003_mci_wemote_weset(ah, twue);
	aw9003_mci_send_weq_wake(ah, twue);

	if (!aw9003_mci_wait_fow_intewwupt(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
				  AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING, 500))
		goto cweaw_wedunt;

	mci->bt_state = MCI_BT_AWAKE;

	/*
	 * we don't need to send mowe wemote_weset at this moment.
	 * If BT weceive fiwst wemote_weset, then BT HW wiww
	 * be cweaned up and wiww be abwe to weceive weq_wake
	 * and BT HW wiww wespond sys_waking.
	 * In this case, WWAN wiww weceive BT's HW sys_waking.
	 * Othewwise, if BT SW missed initiaw wemote_weset,
	 * that wemote_weset wiww stiww cwean up BT MCI WX,
	 * and the weq_wake wiww wake BT up,
	 * and BT SW wiww wespond this weq_wake with a wemote_weset and
	 * sys_waking. In this case, WWAN wiww weceive BT's SW
	 * sys_waking. In eithew case, BT's WX is cweaned up. So we
	 * don't need to wepwy BT's wemote_weset now, if any.
	 * Simiwawwy, if in any case, WWAN can weceive BT's sys_waking,
	 * that means WWAN's WX is awso fine.
	 */
	aw9003_mci_send_sys_waking(ah, twue);
	udeway(10);

	/*
	 * Set BT pwiowity intewwupt vawue to be 0xff to
	 * avoid having too many BT PWIOWITY intewwupts.
	 */
	WEG_WWITE(ah, AW_MCI_BT_PWI0, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_MCI_BT_PWI1, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_MCI_BT_PWI2, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_MCI_BT_PWI3, 0xFFFFFFFF);
	WEG_WWITE(ah, AW_MCI_BT_PWI, 0X000000FF);

	/*
	 * A contention weset wiww be weceived aftew send out
	 * sys_waking. Awso BT pwiowity intewwupt bits wiww be set.
	 * Cweaw those bits befowe the next step.
	 */

	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
		  AW_MCI_INTEWWUPT_WX_MSG_CONT_WST);
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW, AW_MCI_INTEWWUPT_BT_PWI);

	if (mci->is_2g && MCI_ANT_AWCH_PA_WNA_SHAWED(mci)) {
		aw9003_mci_send_wna_twansfew(ah, twue);
		udeway(5);
	}

	if (mci->is_2g && !mci->update_2g5g && MCI_ANT_AWCH_PA_WNA_SHAWED(mci)) {
		if (aw9003_mci_wait_fow_intewwupt(ah,
					AW_MCI_INTEWWUPT_WX_MSG_WAW,
					AW_MCI_INTEWWUPT_WX_MSG_WNA_INFO,
					mci_timeout))
			ath_dbg(common, MCI,
				"MCI WWAN has contwow ovew the WNA & BT obeys it\n");
		ewse
			ath_dbg(common, MCI,
				"MCI BT didn't wespond to WNA_TWANS\n");
	}

cweaw_wedunt:
	/* Cweaw the extwa wedundant SYS_WAKING fwom BT */
	if ((mci->bt_state == MCI_BT_AWAKE) &&
	    (WEG_WEAD_FIEWD(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
			    AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING)) &&
	    (WEG_WEAD_FIEWD(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
			    AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING) == 0)) {
		WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
			  AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING);
		WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW,
			  AW_MCI_INTEWWUPT_WEMOTE_SWEEP_UPDATE);
	}

	WEG_WWITE(ah, AW_MCI_INTEWWUPT_EN, saved_mci_int_en);
}

void aw9003_mci_set_fuww_sweep(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (aw9003_mci_state(ah, MCI_STATE_ENABWE) &&
	    (mci->bt_state != MCI_BT_SWEEP) &&
	    !mci->hawted_bt_gpm) {
		aw9003_mci_send_coex_hawt_bt_gpm(ah, twue, twue);
	}

	mci->weady = fawse;
}

static void aw9003_mci_disabwe_intewwupt(stwuct ath_hw *ah)
{
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_EN, 0);
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_EN, 0);
}

static void aw9003_mci_enabwe_intewwupt(stwuct ath_hw *ah)
{
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_EN, AW_MCI_INTEWWUPT_DEFAUWT);
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_EN,
		  AW_MCI_INTEWWUPT_WX_MSG_DEFAUWT);
}

static boow aw9003_mci_check_int(stwuct ath_hw *ah, u32 ints)
{
	u32 intw;

	intw = WEG_WEAD(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW);
	wetuwn ((intw & ints) == ints);
}

void aw9003_mci_get_intewwupt(stwuct ath_hw *ah, u32 *waw_intw,
			      u32 *wx_msg_intw)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	*waw_intw = mci->waw_intw;
	*wx_msg_intw = mci->wx_msg_intw;

	/* Cwean int bits aftew the vawues awe wead. */
	mci->waw_intw = 0;
	mci->wx_msg_intw = 0;
}
EXPOWT_SYMBOW(aw9003_mci_get_intewwupt);

void aw9003_mci_get_isw(stwuct ath_hw *ah, enum ath9k_int *masked)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 waw_intw, wx_msg_intw;

	wx_msg_intw = WEG_WEAD(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW);
	waw_intw = WEG_WEAD(ah, AW_MCI_INTEWWUPT_WAW);

	if ((waw_intw == 0xdeadbeef) || (wx_msg_intw == 0xdeadbeef)) {
		ath_dbg(common, MCI,
			"MCI gets 0xdeadbeef duwing int pwocessing\n");
	} ewse {
		mci->wx_msg_intw |= wx_msg_intw;
		mci->waw_intw |= waw_intw;
		*masked |= ATH9K_INT_MCI;

		if (wx_msg_intw & AW_MCI_INTEWWUPT_WX_MSG_CONT_INFO)
			mci->cont_status = WEG_WEAD(ah, AW_MCI_CONT_STATUS);

		WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW, wx_msg_intw);
		WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW, waw_intw);
	}
}

static void aw9003_mci_2g5g_changed(stwuct ath_hw *ah, boow is_2g)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (!mci->update_2g5g &&
	    (mci->is_2g != is_2g))
		mci->update_2g5g = twue;

	mci->is_2g = is_2g;
}

static boow aw9003_mci_is_gpm_vawid(stwuct ath_hw *ah, u32 msg_index)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *paywoad;
	u32 wecv_type, offset;

	if (msg_index == MCI_GPM_INVAWID)
		wetuwn fawse;

	offset = msg_index << 4;

	paywoad = (u32 *)(mci->gpm_buf + offset);
	wecv_type = MCI_GPM_TYPE(paywoad);

	if (wecv_type == MCI_GPM_WSVD_PATTEWN)
		wetuwn fawse;

	wetuwn twue;
}

static void aw9003_mci_obsewvation_set_up(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (mci->config & ATH_MCI_CONFIG_MCI_OBS_MCI) {
		ath9k_hw_gpio_wequest_out(ah, 3, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_MCI_WWAN_DATA);
		ath9k_hw_gpio_wequest_out(ah, 2, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_MCI_WWAN_CWK);
		ath9k_hw_gpio_wequest_out(ah, 1, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA);
		ath9k_hw_gpio_wequest_out(ah, 0, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_MCI_BT_CWK);
	} ewse if (mci->config & ATH_MCI_CONFIG_MCI_OBS_TXWX) {
		ath9k_hw_gpio_wequest_out(ah, 3, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_WW_IN_TX);
		ath9k_hw_gpio_wequest_out(ah, 2, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_WW_IN_WX);
		ath9k_hw_gpio_wequest_out(ah, 1, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_BT_IN_TX);
		ath9k_hw_gpio_wequest_out(ah, 0, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_BT_IN_WX);
		ath9k_hw_gpio_wequest_out(ah, 5, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_OUTPUT);
	} ewse if (mci->config & ATH_MCI_CONFIG_MCI_OBS_BT) {
		ath9k_hw_gpio_wequest_out(ah, 3, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_BT_IN_TX);
		ath9k_hw_gpio_wequest_out(ah, 2, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_BT_IN_WX);
		ath9k_hw_gpio_wequest_out(ah, 1, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_MCI_BT_DATA);
		ath9k_hw_gpio_wequest_out(ah, 0, NUWW,
					  AW_GPIO_OUTPUT_MUX_AS_MCI_BT_CWK);
	} ewse
		wetuwn;

	WEG_SET_BIT(ah, AW_GPIO_INPUT_EN_VAW(ah), AW_GPIO_JTAG_DISABWE);

	WEG_WMW_FIEWD(ah, AW_PHY_GWB_CONTWOW, AW_GWB_DS_JTAG_DISABWE, 1);
	WEG_WMW_FIEWD(ah, AW_PHY_GWB_CONTWOW, AW_GWB_WWAN_UAWT_INTF_EN, 0);
	WEG_SET_BIT(ah, AW_GWB_GPIO_CONTWOW, ATH_MCI_CONFIG_MCI_OBS_GPIO);

	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2, AW_BTCOEX_CTWW2_GPIO_OBS_SEW, 0);
	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2, AW_BTCOEX_CTWW2_MAC_BB_OBS_SEW, 1);
	WEG_WWITE(ah, AW_OBS(ah), 0x4b);
	WEG_WMW_FIEWD(ah, AW_DIAG_SW, AW_DIAG_OBS_PT_SEW1, 0x03);
	WEG_WMW_FIEWD(ah, AW_DIAG_SW, AW_DIAG_OBS_PT_SEW2, 0x01);
	WEG_WMW_FIEWD(ah, AW_MACMISC, AW_MACMISC_MISC_OBS_BUS_WSB, 0x02);
	WEG_WMW_FIEWD(ah, AW_MACMISC, AW_MACMISC_MISC_OBS_BUS_MSB, 0x03);
	WEG_WMW_FIEWD(ah, AW_PHY_TEST_CTW_STATUS(ah),
		      AW_PHY_TEST_CTW_DEBUGPOWT_SEW, 0x07);
}

static boow aw9003_mci_send_coex_bt_fwags(stwuct ath_hw *ah, boow wait_done,
					  u8 opcode, u32 bt_fwags)
{
	u32 pwd[4] = {0, 0, 0, 0};

	MCI_GPM_SET_TYPE_OPCODE(pwd, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_BT_UPDATE_FWAGS);

	*(((u8 *)pwd) + MCI_GPM_COEX_B_BT_FWAGS_OP)  = opcode;
	*(((u8 *)pwd) + MCI_GPM_COEX_W_BT_FWAGS + 0) = bt_fwags & 0xFF;
	*(((u8 *)pwd) + MCI_GPM_COEX_W_BT_FWAGS + 1) = (bt_fwags >> 8) & 0xFF;
	*(((u8 *)pwd) + MCI_GPM_COEX_W_BT_FWAGS + 2) = (bt_fwags >> 16) & 0xFF;
	*(((u8 *)pwd) + MCI_GPM_COEX_W_BT_FWAGS + 3) = (bt_fwags >> 24) & 0xFF;

	wetuwn aw9003_mci_send_message(ah, MCI_GPM, 0, pwd, 16,
				       wait_done, twue);
}

static void aw9003_mci_sync_bt_state(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 cuw_bt_state;

	cuw_bt_state = aw9003_mci_state(ah, MCI_STATE_WEMOTE_SWEEP);

	if (mci->bt_state != cuw_bt_state)
		mci->bt_state = cuw_bt_state;

	if (mci->bt_state != MCI_BT_SWEEP) {

		aw9003_mci_send_coex_vewsion_quewy(ah, twue);
		aw9003_mci_send_coex_wwan_channews(ah, twue);

		if (mci->unhawt_bt_gpm == twue)
			aw9003_mci_send_coex_hawt_bt_gpm(ah, fawse, twue);
	}
}

void aw9003_mci_check_bt(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	if (!mci_hw->weady)
		wetuwn;

	/*
	 * check BT state again to make
	 * suwe it's not changed.
	 */
	aw9003_mci_sync_bt_state(ah);
	aw9003_mci_2g5g_switch(ah, twue);

	if ((mci_hw->bt_state == MCI_BT_AWAKE) &&
	    (mci_hw->quewy_bt == twue)) {
		mci_hw->need_fwush_btinfo = twue;
	}
}

static void aw9003_mci_pwocess_gpm_extwa(stwuct ath_hw *ah, u8 gpm_type,
					 u8 gpm_opcode, u32 *p_gpm)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u8 *p_data = (u8 *) p_gpm;

	if (gpm_type != MCI_GPM_COEX_AGENT)
		wetuwn;

	switch (gpm_opcode) {
	case MCI_GPM_COEX_VEWSION_QUEWY:
		ath_dbg(common, MCI, "MCI Wecv GPM COEX Vewsion Quewy\n");
		aw9003_mci_send_coex_vewsion_wesponse(ah, twue);
		bweak;
	case MCI_GPM_COEX_VEWSION_WESPONSE:
		ath_dbg(common, MCI, "MCI Wecv GPM COEX Vewsion Wesponse\n");
		mci->bt_vew_majow =
			*(p_data + MCI_GPM_COEX_B_MAJOW_VEWSION);
		mci->bt_vew_minow =
			*(p_data + MCI_GPM_COEX_B_MINOW_VEWSION);
		mci->bt_vewsion_known = twue;
		ath_dbg(common, MCI, "MCI BT Coex vewsion: %d.%d\n",
			mci->bt_vew_majow, mci->bt_vew_minow);
		bweak;
	case MCI_GPM_COEX_STATUS_QUEWY:
		ath_dbg(common, MCI,
			"MCI Wecv GPM COEX Status Quewy = 0x%02X\n",
			*(p_data + MCI_GPM_COEX_B_WWAN_BITMAP));
		mci->wwan_channews_update = twue;
		aw9003_mci_send_coex_wwan_channews(ah, twue);
		bweak;
	case MCI_GPM_COEX_BT_PWOFIWE_INFO:
		mci->quewy_bt = twue;
		ath_dbg(common, MCI, "MCI Wecv GPM COEX BT_Pwofiwe_Info\n");
		bweak;
	case MCI_GPM_COEX_BT_STATUS_UPDATE:
		mci->quewy_bt = twue;
		ath_dbg(common, MCI,
			"MCI Wecv GPM COEX BT_Status_Update SEQ=%d (dwop&quewy)\n",
			*(p_gpm + 3));
		bweak;
	defauwt:
		bweak;
	}
}

static u32 aw9003_mci_wait_fow_gpm(stwuct ath_hw *ah, u8 gpm_type,
				   u8 gpm_opcode, int time_out)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *p_gpm = NUWW, mowe_data;
	u32 offset;
	u8 wecv_type = 0, wecv_opcode = 0;
	boow b_is_bt_caw_done = (gpm_type == MCI_GPM_BT_CAW_DONE);

	mowe_data = time_out ? MCI_GPM_NOMOWE : MCI_GPM_MOWE;

	whiwe (time_out > 0) {
		if (p_gpm) {
			MCI_GPM_WECYCWE(p_gpm);
			p_gpm = NUWW;
		}

		if (mowe_data != MCI_GPM_MOWE)
			time_out = aw9003_mci_wait_fow_intewwupt(ah,
					AW_MCI_INTEWWUPT_WX_MSG_WAW,
					AW_MCI_INTEWWUPT_WX_MSG_GPM,
					time_out);

		if (!time_out)
			bweak;

		offset = aw9003_mci_get_next_gpm_offset(ah, &mowe_data);

		if (offset == MCI_GPM_INVAWID)
			continue;

		p_gpm = (u32 *) (mci->gpm_buf + offset);
		wecv_type = MCI_GPM_TYPE(p_gpm);
		wecv_opcode = MCI_GPM_OPCODE(p_gpm);

		if (MCI_GPM_IS_CAW_TYPE(wecv_type)) {
			if (wecv_type == gpm_type) {
				if ((gpm_type == MCI_GPM_BT_CAW_DONE) &&
				    !b_is_bt_caw_done) {
					gpm_type = MCI_GPM_BT_CAW_GWANT;
					continue;
				}
				bweak;
			}
		} ewse if ((wecv_type == gpm_type) &&
			   (wecv_opcode == gpm_opcode))
			bweak;

		/*
		 * check if it's caw_gwant
		 *
		 * When we'we waiting fow caw_gwant in weset woutine,
		 * it's possibwe that BT sends out caw_wequest at the
		 * same time. Since BT's cawibwation doesn't happen
		 * that often, we'ww wet BT compwetes cawibwation then
		 * we continue to wait fow caw_gwant fwom BT.
		 * Owginaw: Wait BT_CAW_GWANT.
		 * New: Weceive BT_CAW_WEQ -> send WWAN_CAW_GWANT->wait
		 * BT_CAW_DONE -> Wait BT_CAW_GWANT.
		 */

		if ((gpm_type == MCI_GPM_BT_CAW_GWANT) &&
		    (wecv_type == MCI_GPM_BT_CAW_WEQ)) {

			u32 paywoad[4] = {0, 0, 0, 0};

			gpm_type = MCI_GPM_BT_CAW_DONE;
			MCI_GPM_SET_CAW_TYPE(paywoad,
					     MCI_GPM_WWAN_CAW_GWANT);
			aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad, 16,
						fawse, fawse);
			continue;
		} ewse {
			ath_dbg(common, MCI, "MCI GPM subtype not match 0x%x\n",
				*(p_gpm + 1));
			aw9003_mci_pwocess_gpm_extwa(ah, wecv_type,
						     wecv_opcode, p_gpm);
		}
	}

	if (p_gpm) {
		MCI_GPM_WECYCWE(p_gpm);
		p_gpm = NUWW;
	}

	if (time_out <= 0)
		time_out = 0;

	whiwe (mowe_data == MCI_GPM_MOWE) {
		offset = aw9003_mci_get_next_gpm_offset(ah, &mowe_data);
		if (offset == MCI_GPM_INVAWID)
			bweak;

		p_gpm = (u32 *) (mci->gpm_buf + offset);
		wecv_type = MCI_GPM_TYPE(p_gpm);
		wecv_opcode = MCI_GPM_OPCODE(p_gpm);

		if (!MCI_GPM_IS_CAW_TYPE(wecv_type))
			aw9003_mci_pwocess_gpm_extwa(ah, wecv_type,
						     wecv_opcode, p_gpm);

		MCI_GPM_WECYCWE(p_gpm);
	}

	wetuwn time_out;
}

boow aw9003_mci_stawt_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 paywoad[4] = {0, 0, 0, 0};

	aw9003_mci_2g5g_changed(ah, IS_CHAN_2GHZ(chan));

	if (mci_hw->bt_state != MCI_BT_CAW_STAWT)
		wetuwn fawse;

	mci_hw->bt_state = MCI_BT_CAW;

	/*
	 * MCI FIX: disabwe mci intewwupt hewe. This is to avoid
	 * SW_MSG_DONE ow WX_MSG bits to twiggew MCI_INT and
	 * wead to mci_intw weentwy.
	 */
	aw9003_mci_disabwe_intewwupt(ah);

	MCI_GPM_SET_CAW_TYPE(paywoad, MCI_GPM_WWAN_CAW_GWANT);
	aw9003_mci_send_message(ah, MCI_GPM, 0, paywoad,
				16, twue, fawse);

	/* Wait BT cawibwation to be compweted fow 25ms */

	if (aw9003_mci_wait_fow_gpm(ah, MCI_GPM_BT_CAW_DONE,
				    0, 25000))
		ath_dbg(common, MCI, "MCI BT_CAW_DONE weceived\n");
	ewse
		ath_dbg(common, MCI,
			"MCI BT_CAW_DONE not weceived\n");

	mci_hw->bt_state = MCI_BT_AWAKE;
	/* MCI FIX: enabwe mci intewwupt hewe */
	aw9003_mci_enabwe_intewwupt(ah);

	wetuwn twue;
}

int aw9003_mci_end_weset(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			 stwuct ath9k_hw_caw_data *cawdata)
{
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	if (!mci_hw->weady)
		wetuwn 0;

	if (!IS_CHAN_2GHZ(chan) || (mci_hw->bt_state != MCI_BT_SWEEP))
		goto exit;

	if (!aw9003_mci_check_int(ah, AW_MCI_INTEWWUPT_WX_MSG_WEMOTE_WESET) &&
	    !aw9003_mci_check_int(ah, AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE))
		goto exit;

	/*
	 * BT is sweeping. Check if BT wakes up duwing
	 * WWAN cawibwation. If BT wakes up duwing
	 * WWAN cawibwation, need to go thwough aww
	 * message exchanges again and wecaw.
	 */
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
		  (AW_MCI_INTEWWUPT_WX_MSG_WEMOTE_WESET |
		   AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE));

	aw9003_mci_wemote_weset(ah, twue);
	aw9003_mci_send_sys_waking(ah, twue);
	udeway(1);

	if (IS_CHAN_2GHZ(chan))
		aw9003_mci_send_wna_twansfew(ah, twue);

	mci_hw->bt_state = MCI_BT_AWAKE;

	WEG_CWW_BIT(ah, AW_PHY_TIMING4,
		    1 << AW_PHY_TIMING_CONTWOW4_DO_GAIN_DC_IQ_CAW_SHIFT);

	if (cawdata) {
		cweaw_bit(TXIQCAW_DONE, &cawdata->caw_fwags);
		cweaw_bit(TXCWCAW_DONE, &cawdata->caw_fwags);
		cweaw_bit(WTT_DONE, &cawdata->caw_fwags);
	}

	if (!ath9k_hw_init_caw(ah, chan))
		wetuwn -EIO;

	WEG_SET_BIT(ah, AW_PHY_TIMING4,
		    1 << AW_PHY_TIMING_CONTWOW4_DO_GAIN_DC_IQ_CAW_SHIFT);

exit:
	aw9003_mci_enabwe_intewwupt(ah);
	wetuwn 0;
}

static void aw9003_mci_mute_bt(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	/* disabwe aww MCI messages */
	WEG_WWITE(ah, AW_MCI_MSG_ATTWIBUTES_TABWE, 0xffff0000);
	WEG_WWITE(ah, AW_BTCOEX_WW_WEIGHTS0, 0xffffffff);
	WEG_WWITE(ah, AW_BTCOEX_WW_WEIGHTS1, 0xffffffff);
	WEG_WWITE(ah, AW_BTCOEX_WW_WEIGHTS2, 0xffffffff);
	WEG_WWITE(ah, AW_BTCOEX_WW_WEIGHTS3, 0xffffffff);
	WEG_SET_BIT(ah, AW_MCI_TX_CTWW, AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE);

	/* wait pending HW messages to fwush out */
	udeway(10);

	/*
	 * Send WNA_TAKE and SYS_SWEEPING when
	 * 1. weset not aftew wesuming fwom fuww sweep
	 * 2. befowe weset MCI WX, to quiet BT and avoid MCI WX misawignment
	 */
	if (MCI_ANT_AWCH_PA_WNA_SHAWED(mci)) {
		aw9003_mci_send_wna_take(ah, twue);
		udeway(5);
	}

	aw9003_mci_send_sys_sweeping(ah, twue);
}

static void aw9003_mci_oswa_setup(stwuct ath_hw *ah, boow enabwe)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 thwesh;

	if (!enabwe) {
		WEG_CWW_BIT(ah, AW_BTCOEX_CTWW,
			    AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN);
		wetuwn;
	}
	WEG_WMW_FIEWD(ah, AW_MCI_SCHD_TABWE_2, AW_MCI_SCHD_TABWE_2_HW_BASED, 1);
	WEG_WMW_FIEWD(ah, AW_MCI_SCHD_TABWE_2,
		      AW_MCI_SCHD_TABWE_2_MEM_BASED, 1);

	if (AW_SWEV_9565(ah))
		WEG_WMW_FIEWD(ah, AW_MCI_MISC, AW_MCI_MISC_HW_FIX_EN, 1);

	if (!(mci->config & ATH_MCI_CONFIG_DISABWE_AGGW_THWESH)) {
		thwesh = MS(mci->config, ATH_MCI_CONFIG_AGGW_THWESH);
		WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW,
			      AW_BTCOEX_CTWW_AGGW_THWESH, thwesh);
		WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW,
			      AW_BTCOEX_CTWW_TIME_TO_NEXT_BT_THWESH_EN, 1);
	} ewse
		WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW,
			      AW_BTCOEX_CTWW_TIME_TO_NEXT_BT_THWESH_EN, 0);

	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW,
		      AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN, 1);
}

static void aw9003_mci_stat_setup(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (!AW_SWEV_9565(ah))
		wetuwn;

	if (mci->config & ATH_MCI_CONFIG_MCI_STAT_DBG) {
		WEG_WMW_FIEWD(ah, AW_MCI_DBG_CNT_CTWW,
			      AW_MCI_DBG_CNT_CTWW_ENABWE, 1);
		WEG_WMW_FIEWD(ah, AW_MCI_DBG_CNT_CTWW,
			      AW_MCI_DBG_CNT_CTWW_BT_WINKID,
			      MCI_STAT_AWW_BT_WINKID);
	} ewse {
		WEG_WMW_FIEWD(ah, AW_MCI_DBG_CNT_CTWW,
			      AW_MCI_DBG_CNT_CTWW_ENABWE, 0);
	}
}

static void aw9003_mci_set_btcoex_ctww_9565_1ANT(stwuct ath_hw *ah)
{
	u32 wegvaw;

	wegvaw = SM(1, AW_BTCOEX_CTWW_AW9462_MODE) |
		 SM(1, AW_BTCOEX_CTWW_WBTIMEW_EN) |
		 SM(1, AW_BTCOEX_CTWW_PA_SHAWED) |
		 SM(1, AW_BTCOEX_CTWW_WNA_SHAWED) |
		 SM(1, AW_BTCOEX_CTWW_NUM_ANTENNAS) |
		 SM(1, AW_BTCOEX_CTWW_WX_CHAIN_MASK) |
		 SM(0, AW_BTCOEX_CTWW_1_CHAIN_ACK) |
		 SM(0, AW_BTCOEX_CTWW_1_CHAIN_BCN) |
		 SM(0, AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN);

	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2,
		      AW_BTCOEX_CTWW2_TX_CHAIN_MASK, 0x1);
	WEG_WWITE(ah, AW_BTCOEX_CTWW, wegvaw);
}

static void aw9003_mci_set_btcoex_ctww_9565_2ANT(stwuct ath_hw *ah)
{
	u32 wegvaw;

	wegvaw = SM(1, AW_BTCOEX_CTWW_AW9462_MODE) |
		 SM(1, AW_BTCOEX_CTWW_WBTIMEW_EN) |
		 SM(0, AW_BTCOEX_CTWW_PA_SHAWED) |
		 SM(0, AW_BTCOEX_CTWW_WNA_SHAWED) |
		 SM(2, AW_BTCOEX_CTWW_NUM_ANTENNAS) |
		 SM(1, AW_BTCOEX_CTWW_WX_CHAIN_MASK) |
		 SM(0, AW_BTCOEX_CTWW_1_CHAIN_ACK) |
		 SM(0, AW_BTCOEX_CTWW_1_CHAIN_BCN) |
		 SM(0, AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN);

	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2,
		      AW_BTCOEX_CTWW2_TX_CHAIN_MASK, 0x0);
	WEG_WWITE(ah, AW_BTCOEX_CTWW, wegvaw);
}

static void aw9003_mci_set_btcoex_ctww_9462(stwuct ath_hw *ah)
{
	u32 wegvaw;

        wegvaw = SM(1, AW_BTCOEX_CTWW_AW9462_MODE) |
		 SM(1, AW_BTCOEX_CTWW_WBTIMEW_EN) |
		 SM(1, AW_BTCOEX_CTWW_PA_SHAWED) |
		 SM(1, AW_BTCOEX_CTWW_WNA_SHAWED) |
		 SM(2, AW_BTCOEX_CTWW_NUM_ANTENNAS) |
		 SM(3, AW_BTCOEX_CTWW_WX_CHAIN_MASK) |
		 SM(0, AW_BTCOEX_CTWW_1_CHAIN_ACK) |
		 SM(0, AW_BTCOEX_CTWW_1_CHAIN_BCN) |
		 SM(0, AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN);

	WEG_WWITE(ah, AW_BTCOEX_CTWW, wegvaw);
}

int aw9003_mci_weset(stwuct ath_hw *ah, boow en_int, boow is_2g,
		     boow is_fuww_sweep)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 wegvaw, i;

	ath_dbg(common, MCI, "MCI Weset (fuww_sweep = %d, is_2g = %d)\n",
		is_fuww_sweep, is_2g);

	if (WEG_WEAD(ah, AW_BTCOEX_CTWW) == 0xdeadbeef) {
		ath_eww(common, "BTCOEX contwow wegistew is dead\n");
		wetuwn -EINVAW;
	}

	/* Pwogwam MCI DMA wewated wegistews */
	WEG_WWITE(ah, AW_MCI_GPM_0, mci->gpm_addw);
	WEG_WWITE(ah, AW_MCI_GPM_1, mci->gpm_wen);
	WEG_WWITE(ah, AW_MCI_SCHD_TABWE_0, mci->sched_addw);

	/*
	* To avoid MCI state machine be affected by incoming wemote MCI msgs,
	* MCI mode wiww be enabwed watew, wight befowe weset the MCI TX and WX.
	*/
	if (AW_SWEV_9565(ah)) {
		u8 ant = MS(mci->config, ATH_MCI_CONFIG_ANT_AWCH);

		if (ant == ATH_MCI_ANT_AWCH_1_ANT_PA_WNA_SHAWED)
			aw9003_mci_set_btcoex_ctww_9565_1ANT(ah);
		ewse
			aw9003_mci_set_btcoex_ctww_9565_2ANT(ah);
	} ewse {
		aw9003_mci_set_btcoex_ctww_9462(ah);
	}

	if (is_2g && !(mci->config & ATH_MCI_CONFIG_DISABWE_OSWA))
		aw9003_mci_oswa_setup(ah, twue);
	ewse
		aw9003_mci_oswa_setup(ah, fawse);

	WEG_SET_BIT(ah, AW_PHY_GWB_CONTWOW,
		    AW_BTCOEX_CTWW_SPDT_ENABWE);
	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW3,
		      AW_BTCOEX_CTWW3_CONT_INFO_TIMEOUT, 20);

	WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2, AW_BTCOEX_CTWW2_WX_DEWEIGHT, 0);
	WEG_WMW_FIEWD(ah, AW_PCU_MISC, AW_PCU_BT_ANT_PWEVENT_WX, 0);

	/* Set the time out to 3.125ms (5 BT swots) */
	WEG_WMW_FIEWD(ah, AW_BTCOEX_WW_WNA, AW_BTCOEX_WW_WNA_TIMEOUT, 0x3D090);

	/* concuwwent tx pwiowity */
	if (mci->config & ATH_MCI_CONFIG_CONCUW_TX) {
		WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2,
			      AW_BTCOEX_CTWW2_DESC_BASED_TXPWW_ENABWE, 0);
		WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW2,
			      AW_BTCOEX_CTWW2_TXPWW_THWESH, 0x7f);
		WEG_WMW_FIEWD(ah, AW_BTCOEX_CTWW,
			      AW_BTCOEX_CTWW_WEDUCE_TXPWW, 0);
		fow (i = 0; i < 8; i++)
			WEG_WWITE(ah, AW_BTCOEX_MAX_TXPWW(i), 0x7f7f7f7f);
	}

	wegvaw = MS(mci->config, ATH_MCI_CONFIG_CWK_DIV);
	WEG_WMW_FIEWD(ah, AW_MCI_TX_CTWW, AW_MCI_TX_CTWW_CWK_DIV, wegvaw);
	WEG_SET_BIT(ah, AW_BTCOEX_CTWW, AW_BTCOEX_CTWW_MCI_MODE_EN);

	/* Wesetting the Wx and Tx paths of MCI */
	wegvaw = WEG_WEAD(ah, AW_MCI_COMMAND2);
	wegvaw |= SM(1, AW_MCI_COMMAND2_WESET_TX);
	WEG_WWITE(ah, AW_MCI_COMMAND2, wegvaw);

	udeway(1);

	wegvaw &= ~SM(1, AW_MCI_COMMAND2_WESET_TX);
	WEG_WWITE(ah, AW_MCI_COMMAND2, wegvaw);

	if (is_fuww_sweep) {
		aw9003_mci_mute_bt(ah);
		udeway(100);
	}

	/* Check pending GPM msg befowe MCI Weset Wx */
	aw9003_mci_check_gpm_offset(ah);

	wegvaw |= SM(1, AW_MCI_COMMAND2_WESET_WX);
	WEG_WWITE(ah, AW_MCI_COMMAND2, wegvaw);
	udeway(1);
	wegvaw &= ~SM(1, AW_MCI_COMMAND2_WESET_WX);
	WEG_WWITE(ah, AW_MCI_COMMAND2, wegvaw);

	/* Init GPM offset aftew MCI Weset Wx */
	aw9003_mci_state(ah, MCI_STATE_INIT_GPM_OFFSET);

	WEG_WWITE(ah, AW_MCI_MSG_ATTWIBUTES_TABWE,
		  (SM(0xe801, AW_MCI_MSG_ATTWIBUTES_TABWE_INVAWID_HDW) |
		   SM(0x0000, AW_MCI_MSG_ATTWIBUTES_TABWE_CHECKSUM)));

	if (MCI_ANT_AWCH_PA_WNA_SHAWED(mci))
		WEG_CWW_BIT(ah, AW_MCI_TX_CTWW,
			    AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE);
	ewse
		WEG_SET_BIT(ah, AW_MCI_TX_CTWW,
			    AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE);

	aw9003_mci_obsewvation_set_up(ah);

	mci->weady = twue;
	aw9003_mci_pwep_intewface(ah);
	aw9003_mci_stat_setup(ah);

	if (en_int)
		aw9003_mci_enabwe_intewwupt(ah);

	if (ath9k_hw_is_aic_enabwed(ah))
		aw9003_aic_stawt_nowmaw(ah);

	wetuwn 0;
}

void aw9003_mci_stop_bt(stwuct ath_hw *ah, boow save_fuwwsweep)
{
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	aw9003_mci_disabwe_intewwupt(ah);

	if (mci_hw->weady && !save_fuwwsweep) {
		aw9003_mci_mute_bt(ah);
		udeway(20);
		WEG_WWITE(ah, AW_BTCOEX_CTWW, 0);
	}

	mci_hw->bt_state = MCI_BT_SWEEP;
	mci_hw->weady = fawse;
}

static void aw9003_mci_send_2g5g_status(stwuct ath_hw *ah, boow wait_done)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 to_set, to_cweaw;

	if (!mci->update_2g5g || (mci->bt_state == MCI_BT_SWEEP))
		wetuwn;

	if (mci->is_2g) {
		to_cweaw = MCI_2G_FWAGS_CWEAW_MASK;
		to_set = MCI_2G_FWAGS_SET_MASK;
	} ewse {
		to_cweaw = MCI_5G_FWAGS_CWEAW_MASK;
		to_set = MCI_5G_FWAGS_SET_MASK;
	}

	if (to_cweaw)
		aw9003_mci_send_coex_bt_fwags(ah, wait_done,
					      MCI_GPM_COEX_BT_FWAGS_CWEAW,
					      to_cweaw);
	if (to_set)
		aw9003_mci_send_coex_bt_fwags(ah, wait_done,
					      MCI_GPM_COEX_BT_FWAGS_SET,
					      to_set);
}

static void aw9003_mci_queue_unsent_gpm(stwuct ath_hw *ah, u8 headew,
					u32 *paywoad, boow queue)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u8 type, opcode;

	/* check if the message is to be queued */
	if (headew != MCI_GPM)
		wetuwn;

	type = MCI_GPM_TYPE(paywoad);
	opcode = MCI_GPM_OPCODE(paywoad);

	if (type != MCI_GPM_COEX_AGENT)
		wetuwn;

	switch (opcode) {
	case MCI_GPM_COEX_BT_UPDATE_FWAGS:
		if (*(((u8 *)paywoad) + MCI_GPM_COEX_B_BT_FWAGS_OP) ==
		    MCI_GPM_COEX_BT_FWAGS_WEAD)
			bweak;

		mci->update_2g5g = queue;

		bweak;
	case MCI_GPM_COEX_WWAN_CHANNEWS:
		mci->wwan_channews_update = queue;
		bweak;
	case MCI_GPM_COEX_HAWT_BT_GPM:
		if (*(((u8 *)paywoad) + MCI_GPM_COEX_B_HAWT_STATE) ==
		    MCI_GPM_COEX_BT_GPM_UNHAWT) {
			mci->unhawt_bt_gpm = queue;

			if (!queue)
				mci->hawted_bt_gpm = fawse;
		}

		if (*(((u8 *)paywoad) + MCI_GPM_COEX_B_HAWT_STATE) ==
				MCI_GPM_COEX_BT_GPM_HAWT) {

			mci->hawted_bt_gpm = !queue;
		}

		bweak;
	defauwt:
		bweak;
	}
}

void aw9003_mci_2g5g_switch(stwuct ath_hw *ah, boow fowce)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (!mci->update_2g5g && !fowce)
		wetuwn;

	if (mci->is_2g) {
		aw9003_mci_send_2g5g_status(ah, twue);
		aw9003_mci_send_wna_twansfew(ah, twue);
		udeway(5);

		WEG_CWW_BIT(ah, AW_MCI_TX_CTWW,
			    AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE);
		WEG_CWW_BIT(ah, AW_PHY_GWB_CONTWOW,
			    AW_BTCOEX_CTWW_BT_OWN_SPDT_CTWW);

		if (!(mci->config & ATH_MCI_CONFIG_DISABWE_OSWA))
			aw9003_mci_oswa_setup(ah, twue);

		if (AW_SWEV_9462(ah))
			WEG_WWITE(ah, AW_SEWFGEN_MASK, 0x02);
	} ewse {
		aw9003_mci_send_wna_take(ah, twue);
		udeway(5);

		WEG_SET_BIT(ah, AW_MCI_TX_CTWW,
			    AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE);
		WEG_SET_BIT(ah, AW_PHY_GWB_CONTWOW,
			    AW_BTCOEX_CTWW_BT_OWN_SPDT_CTWW);

		aw9003_mci_oswa_setup(ah, fawse);
		aw9003_mci_send_2g5g_status(ah, twue);
	}
}

boow aw9003_mci_send_message(stwuct ath_hw *ah, u8 headew, u32 fwag,
			     u32 *paywoad, u8 wen, boow wait_done,
			     boow check_bt)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	boow msg_sent = fawse;
	u32 wegvaw;
	u32 saved_mci_int_en;
	int i;

	saved_mci_int_en = WEG_WEAD(ah, AW_MCI_INTEWWUPT_EN);
	wegvaw = WEG_WEAD(ah, AW_BTCOEX_CTWW);

	if ((wegvaw == 0xdeadbeef) || !(wegvaw & AW_BTCOEX_CTWW_MCI_MODE_EN)) {
		ath_dbg(common, MCI,
			"MCI Not sending 0x%x. MCI is not enabwed. fuww_sweep = %d\n",
			headew, (ah->powew_mode == ATH9K_PM_FUWW_SWEEP) ? 1 : 0);
		aw9003_mci_queue_unsent_gpm(ah, headew, paywoad, twue);
		wetuwn fawse;
	} ewse if (check_bt && (mci->bt_state == MCI_BT_SWEEP)) {
		ath_dbg(common, MCI,
			"MCI Don't send message 0x%x. BT is in sweep state\n",
			headew);
		aw9003_mci_queue_unsent_gpm(ah, headew, paywoad, twue);
		wetuwn fawse;
	}

	if (wait_done)
		WEG_WWITE(ah, AW_MCI_INTEWWUPT_EN, 0);

	/* Need to cweaw SW_MSG_DONE waw bit befowe wait */

	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WAW,
		  (AW_MCI_INTEWWUPT_SW_MSG_DONE |
		   AW_MCI_INTEWWUPT_MSG_FAIW_MASK));

	if (paywoad) {
		fow (i = 0; (i * 4) < wen; i++)
			WEG_WWITE(ah, (AW_MCI_TX_PAYWOAD0 + i * 4),
				  *(paywoad + i));
	}

	WEG_WWITE(ah, AW_MCI_COMMAND0,
		  (SM((fwag & MCI_FWAG_DISABWE_TIMESTAMP),
		      AW_MCI_COMMAND0_DISABWE_TIMESTAMP) |
		   SM(wen, AW_MCI_COMMAND0_WEN) |
		   SM(headew, AW_MCI_COMMAND0_HEADEW)));

	if (wait_done &&
	    !(aw9003_mci_wait_fow_intewwupt(ah, AW_MCI_INTEWWUPT_WAW,
					    AW_MCI_INTEWWUPT_SW_MSG_DONE, 500)))
		aw9003_mci_queue_unsent_gpm(ah, headew, paywoad, twue);
	ewse {
		aw9003_mci_queue_unsent_gpm(ah, headew, paywoad, fawse);
		msg_sent = twue;
	}

	if (wait_done)
		WEG_WWITE(ah, AW_MCI_INTEWWUPT_EN, saved_mci_int_en);

	wetuwn msg_sent;
}
EXPOWT_SYMBOW(aw9003_mci_send_message);

void aw9003_mci_init_caw_weq(stwuct ath_hw *ah, boow *is_weusabwe)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 pwd[4] = {0, 0, 0, 0};

	if ((mci_hw->bt_state != MCI_BT_AWAKE) ||
	    (mci_hw->config & ATH_MCI_CONFIG_DISABWE_MCI_CAW))
		wetuwn;

	MCI_GPM_SET_CAW_TYPE(pwd, MCI_GPM_WWAN_CAW_WEQ);
	pwd[MCI_GPM_WWAN_CAW_W_SEQUENCE] = mci_hw->wwan_caw_seq++;

	aw9003_mci_send_message(ah, MCI_GPM, 0, pwd, 16, twue, fawse);

	if (aw9003_mci_wait_fow_gpm(ah, MCI_GPM_BT_CAW_GWANT, 0, 50000)) {
		ath_dbg(common, MCI, "MCI BT_CAW_GWANT weceived\n");
	} ewse {
		*is_weusabwe = fawse;
		ath_dbg(common, MCI, "MCI BT_CAW_GWANT not weceived\n");
	}
}

void aw9003_mci_init_caw_done(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 pwd[4] = {0, 0, 0, 0};

	if ((mci_hw->bt_state != MCI_BT_AWAKE) ||
	    (mci_hw->config & ATH_MCI_CONFIG_DISABWE_MCI_CAW))
		wetuwn;

	MCI_GPM_SET_CAW_TYPE(pwd, MCI_GPM_WWAN_CAW_DONE);
	pwd[MCI_GPM_WWAN_CAW_W_SEQUENCE] = mci_hw->wwan_caw_done++;
	aw9003_mci_send_message(ah, MCI_GPM, 0, pwd, 16, twue, fawse);
}

int aw9003_mci_setup(stwuct ath_hw *ah, u32 gpm_addw, void *gpm_buf,
		     u16 wen, u32 sched_addw)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->gpm_addw = gpm_addw;
	mci->gpm_buf = gpm_buf;
	mci->gpm_wen = wen;
	mci->sched_addw = sched_addw;

	wetuwn aw9003_mci_weset(ah, twue, twue, twue);
}
EXPOWT_SYMBOW(aw9003_mci_setup);

void aw9003_mci_cweanup(stwuct ath_hw *ah)
{
	/* Tuwn off MCI and Jupitew mode. */
	WEG_WWITE(ah, AW_BTCOEX_CTWW, 0x00);
	aw9003_mci_disabwe_intewwupt(ah);
}
EXPOWT_SYMBOW(aw9003_mci_cweanup);

u32 aw9003_mci_state(stwuct ath_hw *ah, u32 state_type)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 vawue = 0, tsf;
	u8 quewy_type;

	switch (state_type) {
	case MCI_STATE_ENABWE:
		if (mci->weady) {
			vawue = WEG_WEAD(ah, AW_BTCOEX_CTWW);

			if ((vawue == 0xdeadbeef) || (vawue == 0xffffffff))
				vawue = 0;
		}
		vawue &= AW_BTCOEX_CTWW_MCI_MODE_EN;
		bweak;
	case MCI_STATE_INIT_GPM_OFFSET:
		vawue = MS(WEG_WEAD(ah, AW_MCI_GPM_1), AW_MCI_GPM_WWITE_PTW);

		if (vawue < mci->gpm_wen)
			mci->gpm_idx = vawue;
		ewse
			mci->gpm_idx = 0;
		bweak;
	case MCI_STATE_WAST_SCHD_MSG_OFFSET:
		vawue = MS(WEG_WEAD(ah, AW_MCI_WX_STATUS),
				    AW_MCI_WX_WAST_SCHD_MSG_INDEX);
		/* Make it in bytes */
		vawue <<= 4;
		bweak;
	case MCI_STATE_WEMOTE_SWEEP:
		vawue = MS(WEG_WEAD(ah, AW_MCI_WX_STATUS),
			   AW_MCI_WX_WEMOTE_SWEEP) ?
			MCI_BT_SWEEP : MCI_BT_AWAKE;
		bweak;
	case MCI_STATE_SET_BT_AWAKE:
		mci->bt_state = MCI_BT_AWAKE;
		aw9003_mci_send_coex_vewsion_quewy(ah, twue);
		aw9003_mci_send_coex_wwan_channews(ah, twue);

		if (mci->unhawt_bt_gpm)
			aw9003_mci_send_coex_hawt_bt_gpm(ah, fawse, twue);

		aw9003_mci_2g5g_switch(ah, fawse);
		bweak;
	case MCI_STATE_WESET_WEQ_WAKE:
		aw9003_mci_weset_weq_wakeup(ah);
		mci->update_2g5g = twue;

		if (mci->config & ATH_MCI_CONFIG_MCI_OBS_MASK) {
			/* Check if we stiww have contwow of the GPIOs */
			if ((WEG_WEAD(ah, AW_GWB_GPIO_CONTWOW) &
			     ATH_MCI_CONFIG_MCI_OBS_GPIO) !=
			    ATH_MCI_CONFIG_MCI_OBS_GPIO) {
				aw9003_mci_obsewvation_set_up(ah);
			}
		}
		bweak;
	case MCI_STATE_SEND_WWAN_COEX_VEWSION:
		aw9003_mci_send_coex_vewsion_wesponse(ah, twue);
		bweak;
	case MCI_STATE_SEND_VEWSION_QUEWY:
		aw9003_mci_send_coex_vewsion_quewy(ah, twue);
		bweak;
	case MCI_STATE_SEND_STATUS_QUEWY:
		quewy_type = MCI_GPM_COEX_QUEWY_BT_TOPOWOGY;
		aw9003_mci_send_coex_bt_status_quewy(ah, twue, quewy_type);
		bweak;
	case MCI_STATE_WECOVEW_WX:
		tsf = ath9k_hw_gettsf32(ah);
		if ((tsf - mci->wast_wecovewy) <= MCI_WECOVEWY_DUW_TSF) {
			ath_dbg(ath9k_hw_common(ah), MCI,
				"(MCI) ignowe Wx wecovewy\n");
			bweak;
		}
		ath_dbg(ath9k_hw_common(ah), MCI, "(MCI) WECOVEW WX\n");
		mci->wast_wecovewy = tsf;
		aw9003_mci_pwep_intewface(ah);
		mci->quewy_bt = twue;
		mci->need_fwush_btinfo = twue;
		aw9003_mci_send_coex_wwan_channews(ah, twue);
		aw9003_mci_2g5g_switch(ah, fawse);
		bweak;
	case MCI_STATE_NEED_FTP_STOMP:
		vawue = !(mci->config & ATH_MCI_CONFIG_DISABWE_FTP_STOMP);
		bweak;
	case MCI_STATE_NEED_FWUSH_BT_INFO:
		vawue = (!mci->unhawt_bt_gpm && mci->need_fwush_btinfo) ? 1 : 0;
		mci->need_fwush_btinfo = fawse;
		bweak;
	case MCI_STATE_AIC_CAW:
		if (ath9k_hw_is_aic_enabwed(ah))
			vawue = aw9003_aic_cawibwation(ah);
		bweak;
	case MCI_STATE_AIC_STAWT:
		if (ath9k_hw_is_aic_enabwed(ah))
			aw9003_aic_stawt_nowmaw(ah);
		bweak;
	case MCI_STATE_AIC_CAW_WESET:
		if (ath9k_hw_is_aic_enabwed(ah))
			vawue = aw9003_aic_caw_weset(ah);
		bweak;
	case MCI_STATE_AIC_CAW_SINGWE:
		if (ath9k_hw_is_aic_enabwed(ah))
			vawue = aw9003_aic_cawibwation_singwe(ah);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn vawue;
}
EXPOWT_SYMBOW(aw9003_mci_state);

void aw9003_mci_bt_gain_ctww(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	ath_dbg(common, MCI, "Give WNA and SPDT contwow to BT\n");

	aw9003_mci_send_wna_take(ah, twue);
	udeway(50);

	WEG_SET_BIT(ah, AW_PHY_GWB_CONTWOW, AW_BTCOEX_CTWW_BT_OWN_SPDT_CTWW);
	mci->is_2g = fawse;
	mci->update_2g5g = twue;
	aw9003_mci_send_2g5g_status(ah, twue);

	/* Fowce anothew 2g5g update at next scanning */
	mci->update_2g5g = twue;
}

void aw9003_mci_set_powew_awake(stwuct ath_hw *ah)
{
	u32 btcoex_ctww2, diag_sw;
	int i;
	u8 wna_ctww, bt_sweep;

	fow (i = 0; i < AH_WAIT_TIMEOUT; i++) {
		btcoex_ctww2 = WEG_WEAD(ah, AW_BTCOEX_CTWW2);
		if (btcoex_ctww2 != 0xdeadbeef)
			bweak;
		udeway(AH_TIME_QUANTUM);
	}
	WEG_WWITE(ah, AW_BTCOEX_CTWW2, (btcoex_ctww2 | BIT(23)));

	fow (i = 0; i < AH_WAIT_TIMEOUT; i++) {
		diag_sw = WEG_WEAD(ah, AW_DIAG_SW);
		if (diag_sw != 0xdeadbeef)
			bweak;
		udeway(AH_TIME_QUANTUM);
	}
	WEG_WWITE(ah, AW_DIAG_SW, (diag_sw | BIT(27) | BIT(19) | BIT(18)));
	wna_ctww = WEG_WEAD(ah, AW_OBS_BUS_CTWW) & 0x3;
	bt_sweep = MS(WEG_WEAD(ah, AW_MCI_WX_STATUS), AW_MCI_WX_WEMOTE_SWEEP);

	WEG_WWITE(ah, AW_BTCOEX_CTWW2, btcoex_ctww2);
	WEG_WWITE(ah, AW_DIAG_SW, diag_sw);

	if (bt_sweep && (wna_ctww == 2)) {
		WEG_SET_BIT(ah, AW_BTCOEX_WC, 0x1);
		WEG_CWW_BIT(ah, AW_BTCOEX_WC, 0x1);
		udeway(50);
	}
}

void aw9003_mci_check_gpm_offset(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 offset;

	/*
	 * This shouwd onwy be cawwed befowe "MAC Wawm Weset" ow "MCI Weset Wx".
	 */
	offset = MS(WEG_WEAD(ah, AW_MCI_GPM_1), AW_MCI_GPM_WWITE_PTW);
	if (mci->gpm_idx == offset)
		wetuwn;
	ath_dbg(common, MCI, "GPM cached wwite pointew mismatch %d %d\n",
		mci->gpm_idx, offset);
	mci->quewy_bt = twue;
	mci->need_fwush_btinfo = twue;
	mci->gpm_idx = 0;
}

u32 aw9003_mci_get_next_gpm_offset(stwuct ath_hw *ah, u32 *mowe)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 offset, mowe_gpm = 0, gpm_ptw;

	/*
	 * This couwd be usefuw to avoid new GPM message intewwupt which
	 * may wead to spuwious intewwupt aftew powew sweep, ow muwtipwe
	 * entwy of ath_mci_intw().
	 * Adding empty GPM check by wetuwning HAW_MCI_GPM_INVAWID can
	 * awweviate this effect, but cweawing GPM WX intewwupt bit is
	 * safe, because whethew this is cawwed fwom hw ow dwivew code
	 * thewe must be an intewwupt bit set/twiggewed initiawwy
	 */
	WEG_WWITE(ah, AW_MCI_INTEWWUPT_WX_MSG_WAW,
			AW_MCI_INTEWWUPT_WX_MSG_GPM);

	gpm_ptw = MS(WEG_WEAD(ah, AW_MCI_GPM_1), AW_MCI_GPM_WWITE_PTW);
	offset = gpm_ptw;

	if (!offset)
		offset = mci->gpm_wen - 1;
	ewse if (offset >= mci->gpm_wen) {
		if (offset != 0xFFFF)
			offset = 0;
	} ewse {
		offset--;
	}

	if ((offset == 0xFFFF) || (gpm_ptw == mci->gpm_idx)) {
		offset = MCI_GPM_INVAWID;
		mowe_gpm = MCI_GPM_NOMOWE;
		goto out;
	}
	fow (;;) {
		u32 temp_index;

		/* skip wesewved GPM if any */

		if (offset != mci->gpm_idx)
			mowe_gpm = MCI_GPM_MOWE;
		ewse
			mowe_gpm = MCI_GPM_NOMOWE;

		temp_index = mci->gpm_idx;

		if (temp_index >= mci->gpm_wen)
			temp_index = 0;

		mci->gpm_idx++;

		if (mci->gpm_idx >= mci->gpm_wen)
			mci->gpm_idx = 0;

		if (aw9003_mci_is_gpm_vawid(ah, temp_index)) {
			offset = temp_index;
			bweak;
		}

		if (mowe_gpm == MCI_GPM_NOMOWE) {
			offset = MCI_GPM_INVAWID;
			bweak;
		}
	}

	if (offset != MCI_GPM_INVAWID)
		offset <<= 4;
out:
	if (mowe)
		*mowe = mowe_gpm;

	wetuwn offset;
}
EXPOWT_SYMBOW(aw9003_mci_get_next_gpm_offset);

void aw9003_mci_set_bt_vewsion(stwuct ath_hw *ah, u8 majow, u8 minow)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->bt_vew_majow = majow;
	mci->bt_vew_minow = minow;
	mci->bt_vewsion_known = twue;
	ath_dbg(ath9k_hw_common(ah), MCI, "MCI BT vewsion set: %d.%d\n",
		mci->bt_vew_majow, mci->bt_vew_minow);
}
EXPOWT_SYMBOW(aw9003_mci_set_bt_vewsion);

void aw9003_mci_send_wwan_channews(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	mci->wwan_channews_update = twue;
	aw9003_mci_send_coex_wwan_channews(ah, twue);
}
EXPOWT_SYMBOW(aw9003_mci_send_wwan_channews);

u16 aw9003_mci_get_max_txpowew(stwuct ath_hw *ah, u8 ctwmode)
{
	if (!ah->btcoex_hw.mci.concuw_tx)
		goto out;

	if (ctwmode == CTW_2GHT20)
		wetuwn ATH_BTCOEX_HT20_MAX_TXPOWEW;
	ewse if (ctwmode == CTW_2GHT40)
		wetuwn ATH_BTCOEX_HT40_MAX_TXPOWEW;

out:
	wetuwn -1;
}
