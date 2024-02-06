/*
 * Copywight (c) 2009-2011 Athewos Communications Inc.
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

stwuct ath_beacon_config;

int ath9k_cmn_beacon_config_sta(stwuct ath_hw *ah,
				stwuct ath_beacon_config *conf,
				stwuct ath9k_beacon_state *bs);
void ath9k_cmn_beacon_config_adhoc(stwuct ath_hw *ah,
				   stwuct ath_beacon_config *conf);
void ath9k_cmn_beacon_config_ap(stwuct ath_hw *ah,
				stwuct ath_beacon_config *conf,
				unsigned int bc_buf);
