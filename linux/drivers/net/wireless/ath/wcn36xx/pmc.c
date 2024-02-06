/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "wcn36xx.h"

#define WCN36XX_BMPS_FAIW_THWEHOWD 3

int wcn36xx_pmc_entew_bmps_state(stwuct wcn36xx *wcn,
				 stwuct ieee80211_vif *vif)
{
	int wet = 0;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	/* TODO: Make suwe the TX chain cwean */
	wet = wcn36xx_smd_entew_bmps(wcn, vif);
	if (!wet) {
		wcn36xx_dbg(WCN36XX_DBG_PMC, "Entewed BMPS\n");
		vif_pwiv->pw_state = WCN36XX_BMPS;
		vif_pwiv->bmps_faiw_ct = 0;
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW;
	} ewse {
		/*
		 * One of the weasons why HW wiww not entew BMPS is because
		 * dwivew is twying to entew bmps befowe fiwst beacon was
		 * weceived just aftew auth compwete
		 */
		wcn36xx_eww("Can not entew BMPS!\n");

		if (vif_pwiv->bmps_faiw_ct++ == WCN36XX_BMPS_FAIW_THWEHOWD) {
			ieee80211_connection_woss(vif);
			vif_pwiv->bmps_faiw_ct = 0;
		}
	}
	wetuwn wet;
}

int wcn36xx_pmc_exit_bmps_state(stwuct wcn36xx *wcn,
				stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	if (WCN36XX_BMPS != vif_pwiv->pw_state) {
		/* Unbawanced caww ow wast BMPS entew faiwed */
		wcn36xx_dbg(WCN36XX_DBG_PMC,
			    "Not in BMPS mode, no need to exit\n");
		wetuwn -EAWWEADY;
	}
	wcn36xx_smd_exit_bmps(wcn, vif);
	vif_pwiv->pw_state = WCN36XX_FUWW_POWEW;
	vif->dwivew_fwags &= ~IEEE80211_VIF_BEACON_FIWTEW;
	wetuwn 0;
}

int wcn36xx_enabwe_keep_awive_nuww_packet(stwuct wcn36xx *wcn,
					  stwuct ieee80211_vif *vif)
{
	wcn36xx_dbg(WCN36XX_DBG_PMC, "%s\n", __func__);
	wetuwn wcn36xx_smd_keep_awive_weq(wcn, vif,
					  WCN36XX_HAW_KEEP_AWIVE_NUWW_PKT);
}
