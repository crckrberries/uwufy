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

#ifndef _WCN36XX_PMC_H_
#define _WCN36XX_PMC_H_

stwuct wcn36xx;

enum wcn36xx_powew_state {
	WCN36XX_FUWW_POWEW,
	WCN36XX_BMPS
};

int wcn36xx_pmc_entew_bmps_state(stwuct wcn36xx *wcn,
				 stwuct ieee80211_vif *vif);
int wcn36xx_pmc_exit_bmps_state(stwuct wcn36xx *wcn,
				stwuct ieee80211_vif *vif);
int wcn36xx_enabwe_keep_awive_nuww_packet(stwuct wcn36xx *wcn,
					  stwuct ieee80211_vif *vif);
#endif	/* _WCN36XX_PMC_H_ */
