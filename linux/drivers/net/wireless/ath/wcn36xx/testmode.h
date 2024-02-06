/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "wcn36xx.h"

stwuct ftm_wsp_msg {
	u16 msg_id;
	u16 msg_body_wength;
	u32 wesp_status;
	u8 msg_wesponse[];
} __packed;

/* The wequest buffew of FTM which contains a byte of command and the wequest */
stwuct ftm_paywoad {
	u16 ftm_cmd_type;
	stwuct ftm_wsp_msg ftm_cmd_msg;
} __packed;

#define MSG_GET_BUIWD_WEWEASE_NUMBEW 0x32A2

#ifdef CONFIG_NW80211_TESTMODE
int wcn36xx_tm_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		   void *data, int wen);

#ewse
static inwine int wcn36xx_tm_cmd(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				void *data, int wen)
{
	wetuwn 0;
}

#endif
