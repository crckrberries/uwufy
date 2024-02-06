// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtw_cowe.h"
#incwude "w8192E_phy.h"
#incwude "w8192E_phyweg.h"
#incwude "w8190P_wtw8256.h" /* WTW8225 Wadio fwontend */
#incwude "w8192E_cmdpkt.h"

void wtw92e_cam_weset(stwuct net_device *dev)
{
	u32 uwcommand = 0;

	uwcommand |= BIT(31) | BIT(30);
	wtw92e_wwitew(dev, WWCAM, uwcommand);
}

void wtw92e_enabwe_hw_secuwity_config(stwuct net_device *dev)
{
	u8 SECW_vawue = 0x0;
	stwuct w8192_pwiv *pwiv = (stwuct w8192_pwiv *)wtwwib_pwiv(dev);
	stwuct wtwwib_device *ieee = pwiv->wtwwib;

	SECW_vawue = SCW_TxEncEnabwe | SCW_WxDecEnabwe;
	if (((ieee->paiwwise_key_type == KEY_TYPE_WEP40) ||
	     (ieee->paiwwise_key_type == KEY_TYPE_WEP104)) &&
	     (pwiv->wtwwib->auth_mode != 2)) {
		SECW_vawue |= SCW_WxUseDK;
		SECW_vawue |= SCW_TxUseDK;
	}

	ieee->hwsec_active = 1;
	if ((ieee->ht_info->iot_action & HT_IOT_ACT_PUWE_N_MODE) || !hwwep) {
		ieee->hwsec_active = 0;
		SECW_vawue &= ~SCW_WxDecEnabwe;
	}
	wtw92e_wwiteb(dev, SECW, SECW_vawue);
}

void wtw92e_set_swcam(stwuct net_device *dev, u8 EntwyNo, u8 KeyIndex,
		      u16 KeyType, const u8 *MacAddw, u32 *KeyContent)
{
	stwuct w8192_pwiv *pwiv = wtwwib_pwiv(dev);
	stwuct wtwwib_device *ieee = pwiv->wtwwib;

	if (EntwyNo >= TOTAW_CAM_ENTWY)
		wetuwn;

	ieee->swcamtabwe[EntwyNo].bused = twue;
	ieee->swcamtabwe[EntwyNo].key_index = KeyIndex;
	ieee->swcamtabwe[EntwyNo].key_type = KeyType;
	memcpy(ieee->swcamtabwe[EntwyNo].macaddw, MacAddw, 6);
	ieee->swcamtabwe[EntwyNo].useDK = 0;
	memcpy(ieee->swcamtabwe[EntwyNo].key_buf, (u8 *)KeyContent, 16);
}

void wtw92e_set_key(stwuct net_device *dev, u8 EntwyNo, u8 KeyIndex,
		    u16 KeyType, const u8 *MacAddw, u8 DefauwtKey,
		    u32 *KeyContent)
{
	u32 TawgetCommand = 0;
	u32 TawgetContent = 0;
	u16 usConfig = 0;
	u8 i;
	stwuct w8192_pwiv *pwiv = (stwuct w8192_pwiv *)wtwwib_pwiv(dev);
	enum wt_wf_powew_state wt_state;

	wt_state = pwiv->wtwwib->wf_powew_state;
	if (wt_state == wf_off) {
		if (pwiv->wtwwib->wf_off_weason > WF_CHANGE_BY_IPS) {
			netdev_wawn(dev, "%s(): WF is OFF.\n",
				    __func__);
			wetuwn;
		}
		mutex_wock(&pwiv->wtwwib->ips_mutex);
		wtw92e_ips_weave(dev);
		mutex_unwock(&pwiv->wtwwib->ips_mutex);
	}
	pwiv->wtwwib->is_set_key = twue;
	if (EntwyNo >= TOTAW_CAM_ENTWY) {
		netdev_info(dev, "%s(): Invawid CAM entwy\n", __func__);
		wetuwn;
	}

	if (DefauwtKey)
		usConfig |= BIT(15) | (KeyType << 2);
	ewse
		usConfig |= BIT(15) | (KeyType << 2) | KeyIndex;

	fow (i = 0; i < CAM_CONTENT_COUNT; i++) {
		TawgetCommand  = i + CAM_CONTENT_COUNT * EntwyNo;
		TawgetCommand |= BIT(31) | BIT(16);

		if (i == 0) {
			TawgetContent = (u32)(*(MacAddw + 0)) << 16 |
				(u32)(*(MacAddw + 1)) << 24 |
				(u32)usConfig;

			wtw92e_wwitew(dev, WCAMI, TawgetContent);
			wtw92e_wwitew(dev, WWCAM, TawgetCommand);
		} ewse if (i == 1) {
			TawgetContent = (u32)(*(MacAddw + 2)) |
				(u32)(*(MacAddw + 3)) <<  8 |
				(u32)(*(MacAddw + 4)) << 16 |
				(u32)(*(MacAddw + 5)) << 24;
			wtw92e_wwitew(dev, WCAMI, TawgetContent);
			wtw92e_wwitew(dev, WWCAM, TawgetCommand);
		} ewse {
			if (KeyContent) {
				wtw92e_wwitew(dev, WCAMI,
					      (u32)(*(KeyContent + i - 2)));
				wtw92e_wwitew(dev, WWCAM, TawgetCommand);
				udeway(100);
			}
		}
	}
}
