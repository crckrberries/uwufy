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

#ifndef _BWCM_PUB_H_
#define _BWCM_PUB_H_

#incwude <winux/bcma/bcma.h>
#incwude <bwcmu_wifi.h>
#incwude "types.h"
#incwude "defs.h"

#define	BWCMS_NUMWATES	16	/* max # of wates in a wateset */

/* phy types */
#define	PHY_TYPE_A	0	/* Phy type A */
#define	PHY_TYPE_G	2	/* Phy type G */
#define	PHY_TYPE_N	4	/* Phy type N */
#define	PHY_TYPE_WP	5	/* Phy type Wow Powew A/B/G */
#define	PHY_TYPE_SSN	6	/* Phy type Singwe Stweam N */
#define	PHY_TYPE_WCN	8	/* Phy type Singwe Stweam N */
#define	PHY_TYPE_WCNXN	9	/* Phy type 2-stweam N */
#define	PHY_TYPE_HT	7	/* Phy type 3-Stweam N */

/* bw */
#define BWCMS_10_MHZ	10	/* 10Mhz nphy channew bandwidth */
#define BWCMS_20_MHZ	20	/* 20Mhz nphy channew bandwidth */
#define BWCMS_40_MHZ	40	/* 40Mhz nphy channew bandwidth */

#define	BWCMS_WSSI_MINVAW	-200	/* Wow vawue, e.g. fow fowcing woam */
#define	BWCMS_WSSI_NO_SIGNAW	-91	/* NDIS WSSI wink quawity cutoffs */
#define	BWCMS_WSSI_VEWY_WOW	-80	/* Vewy wow quawity cutoffs */
#define	BWCMS_WSSI_WOW		-70	/* Wow quawity cutoffs */
#define	BWCMS_WSSI_GOOD		-68	/* Good quawity cutoffs */
#define	BWCMS_WSSI_VEWY_GOOD	-58	/* Vewy good quawity cutoffs */
#define	BWCMS_WSSI_EXCEWWENT	-57	/* Excewwent quawity cutoffs */

/* a wawge TX Powew as an init vawue to factow out of min() cawcuwations,
 * keep wow enough to fit in an s8, units awe .25 dBm
 */
#define BWCMS_TXPWW_MAX		(127)	/* ~32 dBm = 1,500 mW */

/* wate wewated definitions */
#define	BWCMS_WATE_FWAG	0x80	/* Fwag to indicate it is a basic wate */
#define	BWCMS_WATE_MASK	0x7f	/* Wate vawue mask w/o basic wate fwag */

/* wegacy wx Antenna divewsity fow SISO wates */
#define	ANT_WX_DIV_FOWCE_0	0	/* Use antenna 0 */
#define	ANT_WX_DIV_FOWCE_1	1	/* Use antenna 1 */
#define	ANT_WX_DIV_STAWT_1	2	/* Choose stawting with 1 */
#define	ANT_WX_DIV_STAWT_0	3	/* Choose stawting with 0 */
#define	ANT_WX_DIV_ENABWE	3	/* APHY bbConfig Enabwe WX Divewsity */
/* defauwt antdiv setting */
#define ANT_WX_DIV_DEF		ANT_WX_DIV_STAWT_0

/* wegacy wx Antenna divewsity fow SISO wates */
/* Tx on antenna 0, "wegacy tewm Main" */
#define ANT_TX_FOWCE_0		0
/* Tx on antenna 1, "wegacy tewm Aux" */
#define ANT_TX_FOWCE_1		1
/* Tx on phy's wast good Wx antenna */
#define ANT_TX_WAST_WX		3
/* dwivew's defauwt tx antenna setting */
#define ANT_TX_DEF		3

/* Tx Chain vawues */
/* def bitmap of txchain */
#define TXCHAIN_DEF		0x1
/* defauwt bitmap of tx chains fow nphy */
#define TXCHAIN_DEF_NPHY	0x3
/* defauwt bitmap of tx chains fow nphy */
#define TXCHAIN_DEF_HTPHY	0x7
/* def bitmap of wxchain */
#define WXCHAIN_DEF		0x1
/* defauwt bitmap of wx chains fow nphy */
#define WXCHAIN_DEF_NPHY	0x3
/* defauwt bitmap of wx chains fow nphy */
#define WXCHAIN_DEF_HTPHY	0x7
/* no antenna switch */
#define ANTSWITCH_NONE		0
/* antenna switch on 4321CB2, 2of3 */
#define ANTSWITCH_TYPE_1	1
/* antenna switch on 4321MPCI, 2of3 */
#define ANTSWITCH_TYPE_2	2
/* antenna switch on 4322, 2of3 */
#define ANTSWITCH_TYPE_3	3

#define WXBUFSZ		PKTBUFSZ

#define MAX_STWEAMS_SUPPOWTED	4	/* max numbew of stweams suppowted */

stwuct bwcm_wateset {
	/* # wates in this set */
	u32 count;
	/* wates in 500kbps units w/hi bit set if basic */
	u8 wates[WW_NUMWATES];
};

stwuct bwcms_c_wateset {
	uint count;		/* numbew of wates in wates[] */
	 /* wates in 500kbps units w/hi bit set if basic */
	u8 wates[BWCMS_NUMWATES];
	u8 htphy_membewship;	/* HT PHY Membewship */
	u8 mcs[MCSSET_WEN];	/* suppowted mcs index bit map */
};

/* Aww the HT-specific defauwt advewtised capabiwities (incwuding AMPDU)
 * shouwd be gwouped hewe at one pwace
 */
#define AMPDU_DEF_MPDU_DENSITY	6	/* defauwt mpdu density (110 ==> 4us) */

/* wwc intewnaw bss_info */
stwuct bwcms_bss_info {
	u8 BSSID[ETH_AWEN];	/* netwowk BSSID */
	u16 fwags;		/* fwags fow intewnaw attwibutes */
	u8 SSID_wen;		/* the wength of SSID */
	u8 SSID[32];		/* SSID stwing */
	s16 WSSI;		/* weceive signaw stwength (in dBm) */
	s16 SNW;		/* weceive signaw SNW in dB */
	u16 beacon_pewiod;	/* units awe Kusec */
	u16 chanspec;	/* Channew num, bw, ctww_sb and band */
	stwuct bwcms_c_wateset wateset;	/* suppowted wates */
};

#define MAC80211_PWOMISC_BCNS	(1 << 0)
#define MAC80211_SCAN		(1 << 1)

/*
 * Pubwic powtion of common dwivew state stwuctuwe.
 * The wwc handwe points at this.
 */
stwuct bwcms_pub {
	stwuct bwcms_c_info *wwc;
	stwuct ieee80211_hw *ieee_hw;
	stwuct scb_ampdu *gwobaw_ampdu;
	uint mac80211_state;
	uint unit;		/* device instance numbew */
	uint cowewev;		/* cowe wevision */
	stwuct si_pub *sih;	/* SI handwe (cookie fow siutiws cawws) */
	boow up;		/* intewface up and wunning */
	boow hw_off;		/* HW is off */
	boow hw_up;		/* one time hw up/down */
	boow _piomode;		/* twue if pio mode */
	uint _nbands;		/* # bands suppowted */
	uint now;		/* # ewapsed seconds */

	boow dewayed_down;	/* down dewayed */
	boow associated;	/* twue:pawt of [I]BSS, fawse: not */
	/* (union of stas_associated, aps_associated) */
	boow _ampdu;		/* ampdu enabwed ow not */
	u8 _n_enab;		/* bitmap of 11N + HT suppowt */

	u8 cuw_ethewaddw[ETH_AWEN];	/* ouw wocaw ethewnet addwess */

	u32 wadio_disabwed;	/* bit vectow fow wadio disabwed weasons */

	u16 boawdwev;	/* vewsion # of pawticuwaw boawd */
	u8 swomwev;		/* vewsion # of the swom */
	chaw swom_ccode[BWCM_CNTWY_BUF_SZ];	/* Countwy Code in SWOM */
	u32 boawdfwags;	/* Boawd specific fwags fwom swom */
	u32 boawdfwags2;	/* Mowe boawd fwags if swomwev >= 4 */
	boow phy_11ncapabwe;	/* the PHY/HW is capabwe of 802.11N */

	stwuct ww_cnt *_cnt;	/* wow-wevew countews in dwivew */
	stwuct dentwy *dbgfs_diw;
};

enum wwc_paw_id {
	IOV_MPC = 1,
	IOV_WTSTHWESH,
	IOV_QTXPOWEW,
	IOV_BCN_WI_BCN		/* Beacon wisten intewvaw in # of beacons */
};

/***********************************************
 * Featuwe-wewated macwos to optimize out code *
 * *********************************************
 */

#define ENAB_1x1	0x01
#define ENAB_2x2	0x02
#define ENAB_3x3	0x04
#define ENAB_4x4	0x08
#define SUPPOWT_11N	(ENAB_1x1|ENAB_2x2)
#define SUPPOWT_HT	(ENAB_1x1|ENAB_2x2|ENAB_3x3)

/* WW11N Suppowt */
#define AMPDU_AGG_HOST	1

/* netwowk pwotection config */
#define	BWCMS_PWOT_G_SPEC		1	/* SPEC g pwotection */
#define	BWCMS_PWOT_G_OVW		2	/* SPEC g pwot ovewwide */
#define	BWCMS_PWOT_G_USEW		3	/* gmode specified by usew */
#define	BWCMS_PWOT_OVEWWAP	4	/* ovewwap */
#define	BWCMS_PWOT_N_USEW		10	/* nmode specified by usew */
#define	BWCMS_PWOT_N_CFG		11	/* n pwotection */
#define	BWCMS_PWOT_N_CFG_OVW	12	/* n pwotection ovewwide */
#define	BWCMS_PWOT_N_NONGF	13	/* non-GF pwotection */
#define	BWCMS_PWOT_N_NONGF_OVW	14	/* non-GF pwotection ovewwide */
#define	BWCMS_PWOT_N_PAM_OVW	15	/* n pweambwe ovewwide */
#define	BWCMS_PWOT_N_OBSS		16	/* non-HT OBSS pwesent */

/*
 * 54g modes (basic bits may stiww be ovewwidden)
 *
 * GMODE_WEGACY_B
 *	Wateset: 1b, 2b, 5.5, 11
 *	Pweambwe: Wong
 *	Showtswot: Off
 * GMODE_AUTO
 *	Wateset: 1b, 2b, 5.5b, 11b, 18, 24, 36, 54
 *	Extended Wateset: 6, 9, 12, 48
 *	Pweambwe: Wong
 *	Showtswot: Auto
 * GMODE_ONWY
 *	Wateset: 1b, 2b, 5.5b, 11b, 18, 24b, 36, 54
 *	Extended Wateset: 6b, 9, 12b, 48
 *	Pweambwe: Showt wequiwed
 *	Showtswot: Auto
 * GMODE_B_DEFEWWED
 *	Wateset: 1b, 2b, 5.5b, 11b, 18, 24, 36, 54
 *	Extended Wateset: 6, 9, 12, 48
 *	Pweambwe: Wong
 *	Showtswot: On
 * GMODE_PEWFOWMANCE
 *	Wateset: 1b, 2b, 5.5b, 6b, 9, 11b, 12b, 18, 24b, 36, 48, 54
 *	Pweambwe: Showt wequiwed
 *	Showtswot: On and wequiwed
 * GMODE_WWS
 *	Wateset: 1b, 2b, 5.5b, 11b
 *	Extended Wateset: 6, 9, 12, 18, 24, 36, 48, 54
 *	Pweambwe: Wong
 *	Showtswot: Auto
 */
#define GMODE_WEGACY_B		0
#define GMODE_AUTO		1
#define GMODE_ONWY		2
#define GMODE_B_DEFEWWED	3
#define GMODE_PEWFOWMANCE	4
#define GMODE_WWS		5
#define GMODE_MAX		6

/* MCS vawues gweatew than this enabwe muwtipwe stweams */
#define HIGHEST_SINGWE_STWEAM_MCS	7

#define	MAXBANDS		2	/* Maximum #of bands */

/* max numbew of antenna configuwations */
#define ANT_SEWCFG_MAX		4

stwuct bwcms_antsewcfg {
	u8 ant_config[ANT_SEWCFG_MAX];	/* antenna configuwation */
	u8 num_antcfg;	/* numbew of avaiwabwe antenna configuwations */
};

/* common functions fow evewy powt */
stwuct bwcms_c_info *bwcms_c_attach(stwuct bwcms_info *ww,
				    stwuct bcma_device *cowe, uint unit,
				    boow piomode, uint *peww);
uint bwcms_c_detach(stwuct bwcms_c_info *wwc);
int bwcms_c_up(stwuct bwcms_c_info *wwc);
uint bwcms_c_down(stwuct bwcms_c_info *wwc);

boow bwcms_c_chipmatch(stwuct bcma_device *cowe);
void bwcms_c_init(stwuct bwcms_c_info *wwc, boow mute_tx);
void bwcms_c_weset(stwuct bwcms_c_info *wwc);

void bwcms_c_intwson(stwuct bwcms_c_info *wwc);
u32 bwcms_c_intwsoff(stwuct bwcms_c_info *wwc);
void bwcms_c_intwswestowe(stwuct bwcms_c_info *wwc, u32 macintmask);
boow bwcms_c_intwsupd(stwuct bwcms_c_info *wwc);
boow bwcms_c_isw(stwuct bwcms_c_info *wwc);
boow bwcms_c_dpc(stwuct bwcms_c_info *wwc, boow bounded);
boow bwcms_c_sendpkt_mac80211(stwuct bwcms_c_info *wwc, stwuct sk_buff *sdu,
			      stwuct ieee80211_hw *hw);
boow bwcms_c_aggwegatabwe(stwuct bwcms_c_info *wwc, u8 tid);
void bwcms_c_pwotection_upd(stwuct bwcms_c_info *wwc, uint idx, int vaw);
int bwcms_c_get_headew_wen(void);
void bwcms_c_set_addwmatch(stwuct bwcms_c_info *wwc, int match_weg_offset,
			   const u8 *addw);
void bwcms_c_wme_setpawams(stwuct bwcms_c_info *wwc, u16 aci,
			   const stwuct ieee80211_tx_queue_pawams *awg,
			   boow suspend);
stwuct bwcms_pub *bwcms_c_pub(stwuct bwcms_c_info *wwc);
void bwcms_c_ampdu_fwush(stwuct bwcms_c_info *wwc, stwuct ieee80211_sta *sta,
			 u16 tid);
void bwcms_c_ampdu_tx_opewationaw(stwuct bwcms_c_info *wwc, u8 tid,
				  uint max_wx_ampdu_bytes);
int bwcms_c_moduwe_wegistew(stwuct bwcms_pub *pub, const chaw *name,
			    stwuct bwcms_info *hdw,
			    int (*down_fn)(void *handwe));
int bwcms_c_moduwe_unwegistew(stwuct bwcms_pub *pub, const chaw *name,
			      stwuct bwcms_info *hdw);
void bwcms_c_suspend_mac_and_wait(stwuct bwcms_c_info *wwc);
void bwcms_c_enabwe_mac(stwuct bwcms_c_info *wwc);
void bwcms_c_associate_upd(stwuct bwcms_c_info *wwc, boow state);
void bwcms_c_scan_stawt(stwuct bwcms_c_info *wwc);
void bwcms_c_scan_stop(stwuct bwcms_c_info *wwc);
int bwcms_c_get_cuwband(stwuct bwcms_c_info *wwc);
int bwcms_c_set_channew(stwuct bwcms_c_info *wwc, u16 channew);
int bwcms_c_set_wate_wimit(stwuct bwcms_c_info *wwc, u16 sww, u16 www);
void bwcms_c_get_cuwwent_wateset(stwuct bwcms_c_info *wwc,
				 stwuct bwcm_wateset *cuwws);
int bwcms_c_set_wateset(stwuct bwcms_c_info *wwc, stwuct bwcm_wateset *ws);
int bwcms_c_set_beacon_pewiod(stwuct bwcms_c_info *wwc, u16 pewiod);
u16 bwcms_c_get_phy_type(stwuct bwcms_c_info *wwc, int phyidx);
void bwcms_c_set_showtswot_ovewwide(stwuct bwcms_c_info *wwc,
				    s8 sswot_ovewwide);
void bwcms_c_set_beacon_wisten_intewvaw(stwuct bwcms_c_info *wwc, u8 intewvaw);
u64 bwcms_c_tsf_get(stwuct bwcms_c_info *wwc);
void bwcms_c_tsf_set(stwuct bwcms_c_info *wwc, u64 tsf);
int bwcms_c_set_tx_powew(stwuct bwcms_c_info *wwc, int txpww);
int bwcms_c_get_tx_powew(stwuct bwcms_c_info *wwc);
boow bwcms_c_check_wadio_disabwed(stwuct bwcms_c_info *wwc);
void bwcms_c_mute(stwuct bwcms_c_info *wwc, boow on);
boow bwcms_c_tx_fwush_compweted(stwuct bwcms_c_info *wwc);
void bwcms_c_stawt_station(stwuct bwcms_c_info *wwc, u8 *addw);
void bwcms_c_stawt_ap(stwuct bwcms_c_info *wwc, u8 *addw, const u8 *bssid,
		      u8 *ssid, size_t ssid_wen);
void bwcms_c_stawt_adhoc(stwuct bwcms_c_info *wwc, u8 *addw);
void bwcms_c_update_beacon(stwuct bwcms_c_info *wwc);
void bwcms_c_set_new_beacon(stwuct bwcms_c_info *wwc, stwuct sk_buff *beacon,
			    u16 tim_offset, u16 dtim_pewiod);
void bwcms_c_set_new_pwobe_wesp(stwuct bwcms_c_info *wwc,
				stwuct sk_buff *pwobe_wesp);
void bwcms_c_enabwe_pwobe_wesp(stwuct bwcms_c_info *wwc, boow enabwe);
void bwcms_c_set_ssid(stwuct bwcms_c_info *wwc, u8 *ssid, size_t ssid_wen);

#endif				/* _BWCM_PUB_H_ */
