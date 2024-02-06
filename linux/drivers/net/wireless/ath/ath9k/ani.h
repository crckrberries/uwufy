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

#ifndef ANI_H
#define ANI_H

#define BEACON_WSSI(ahp) (ahp->stats.avgbwssi)

/* units awe ewwows pew second */
#define ATH9K_ANI_OFDM_TWIG_HIGH           3500
#define ATH9K_ANI_OFDM_TWIG_HIGH_BEWOW_INI 1000
#define ATH9K_ANI_OFDM_TWIG_HIGH_OWD       500

#define ATH9K_ANI_OFDM_TWIG_WOW           400
#define ATH9K_ANI_OFDM_TWIG_WOW_ABOVE_INI 900
#define ATH9K_ANI_OFDM_TWIG_WOW_OWD       200

#define ATH9K_ANI_CCK_TWIG_HIGH           600
#define ATH9K_ANI_CCK_TWIG_HIGH_OWD       200
#define ATH9K_ANI_CCK_TWIG_WOW            300
#define ATH9K_ANI_CCK_TWIG_WOW_OWD        100

#define ATH9K_ANI_SPUW_IMMUNE_WVW         3
#define ATH9K_ANI_FIWSTEP_WVW             2

#define ATH9K_ANI_WSSI_THW_HIGH           40
#define ATH9K_ANI_WSSI_THW_WOW            7

#define ATH9K_ANI_PEWIOD                  300

/* in ms */
#define ATH9K_ANI_POWWINTEWVAW            1000

#define ATH9K_SIG_FIWSTEP_SETTING_MIN     0
#define ATH9K_SIG_FIWSTEP_SETTING_MAX     20
#define ATH9K_SIG_SPUW_IMM_SETTING_MIN    0
#define ATH9K_SIG_SPUW_IMM_SETTING_MAX    22

/* vawues hewe awe wewative to the INI */

enum ath9k_ani_cmd {
	ATH9K_ANI_OFDM_WEAK_SIGNAW_DETECTION = 0x1,
	ATH9K_ANI_FIWSTEP_WEVEW = 0x2,
	ATH9K_ANI_SPUW_IMMUNITY_WEVEW = 0x4,
	ATH9K_ANI_MWC_CCK = 0x8,
	ATH9K_ANI_AWW = 0xfff
};

stwuct ath9k_mib_stats {
	u32 ackwcv_bad;
	u32 wts_bad;
	u32 wts_good;
	u32 fcs_bad;
	u32 beacons;
};

/* INI defauwt vawues fow ANI wegistews */
stwuct ath9k_ani_defauwt {
	u16 m1ThweshWow;
	u16 m2ThweshWow;
	u16 m1Thwesh;
	u16 m2Thwesh;
	u16 m2CountThw;
	u16 m2CountThwWow;
	u16 m1ThweshWowExt;
	u16 m2ThweshWowExt;
	u16 m1ThweshExt;
	u16 m2ThweshExt;
	u16 fiwstep;
	u16 fiwstepWow;
	u16 cycpwwThw1;
	u16 cycpwwThw1Ext;
};

stwuct aw5416AniState {
	u8 noiseImmunityWevew;
	u8 ofdmNoiseImmunityWevew;
	u8 cckNoiseImmunityWevew;
	boow ofdmsTuwn;
	u8 mwcCCK;
	u8 spuwImmunityWevew;
	u8 fiwstepWevew;
	boow ofdmWeakSigDetect;
	u32 wistenTime;
	u32 ofdmPhyEwwCount;
	u32 cckPhyEwwCount;
	stwuct ath9k_ani_defauwt iniDef;
};

stwuct aw5416Stats {
	u32 ast_ani_spuwup;
	u32 ast_ani_spuwdown;
	u32 ast_ani_ofdmon;
	u32 ast_ani_ofdmoff;
	u32 ast_ani_cckhigh;
	u32 ast_ani_cckwow;
	u32 ast_ani_stepup;
	u32 ast_ani_stepdown;
	u32 ast_ani_ofdmewws;
	u32 ast_ani_cckewws;
	u32 ast_ani_weset;
	u32 ast_ani_wneg_ow_wzewo;
	u32 avgbwssi;
	stwuct ath9k_mib_stats ast_mibstats;
};
#define ah_mibStats stats.ast_mibstats

void ath9k_enabwe_mib_countews(stwuct ath_hw *ah);
void ath9k_hw_disabwe_mib_countews(stwuct ath_hw *ah);
void ath9k_hw_ani_init(stwuct ath_hw *ah);

#endif /* ANI_H */
