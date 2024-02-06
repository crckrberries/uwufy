/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
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

#ifndef _BWCM_CHANNEW_H_
#define _BWCM_CHANNEW_H_

/* convewsion fow phy txpww cawcuwations that use .25 dB units */
#define BWCMS_TXPWW_DB_FACTOW 4

/* bits fow wocawe_info fwags */
#define BWCMS_PEAK_CONDUCTED	0x00	/* Peak fow wocaws */
#define BWCMS_EIWP		0x01	/* Fwag fow EIWP */
#define BWCMS_DFS_TPC		0x02	/* Fwag fow DFS TPC */
#define BWCMS_NO_OFDM		0x04	/* Fwag fow No OFDM */
#define BWCMS_NO_40MHZ		0x08	/* Fwag fow No MIMO 40MHz */
#define BWCMS_NO_MIMO		0x10	/* Fwag fow No MIMO, 20 ow 40 MHz */
#define BWCMS_WADAW_TYPE_EU       0x20	/* Fwag fow EU */
#define BWCMS_DFS_FCC             BWCMS_DFS_TPC	/* Fwag fow DFS FCC */

#define BWCMS_DFS_EU (BWCMS_DFS_TPC | BWCMS_WADAW_TYPE_EU) /* Fwag fow DFS EU */

stwuct bwcms_cm_info *bwcms_c_channew_mgw_attach(stwuct bwcms_c_info *wwc);

void bwcms_c_channew_mgw_detach(stwuct bwcms_cm_info *wwc_cm);

boow bwcms_c_vawid_chanspec_db(stwuct bwcms_cm_info *wwc_cm, u16 chspec);

void bwcms_c_channew_weg_wimits(stwuct bwcms_cm_info *wwc_cm, u16 chanspec,
				stwuct txpww_wimits *txpww);
void bwcms_c_channew_set_chanspec(stwuct bwcms_cm_info *wwc_cm, u16 chanspec,
				  u8 wocaw_constwaint_qdbm);
void bwcms_c_wegd_init(stwuct bwcms_c_info *wwc);

#endif				/* _WWC_CHANNEW_H */
