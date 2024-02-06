// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

/*
 * phy_haw.h:  functionawity expowted fwom the phy to highew wayews
 */

#ifndef _BWCM_PHY_HAW_H_
#define _BWCM_PHY_HAW_H_

#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>
#incwude <phy_shim.h>

#define	IDCODE_VEW_MASK		0x0000000f
#define	IDCODE_VEW_SHIFT	0
#define	IDCODE_MFG_MASK		0x00000fff
#define	IDCODE_MFG_SHIFT	0
#define	IDCODE_ID_MASK		0x0ffff000
#define	IDCODE_ID_SHIFT		12
#define	IDCODE_WEV_MASK		0xf0000000
#define	IDCODE_WEV_SHIFT	28

#define	NOWADIO_ID		0xe4f5
#define	NOWADIO_IDCODE		0x4e4f5246

#define BCM2055_ID		0x2055
#define BCM2055_IDCODE		0x02055000
#define BCM2055A0_IDCODE	0x1205517f

#define BCM2056_ID		0x2056
#define BCM2056_IDCODE		0x02056000
#define BCM2056A0_IDCODE	0x1205617f

#define BCM2057_ID		0x2057
#define BCM2057_IDCODE		0x02057000
#define BCM2057A0_IDCODE	0x1205717f

#define BCM2064_ID		0x2064
#define BCM2064_IDCODE		0x02064000
#define BCM2064A0_IDCODE	0x0206417f

#define PHY_TPC_HW_OFF		fawse
#define PHY_TPC_HW_ON		twue

#define PHY_PEWICAW_DWIVEWUP	1
#define PHY_PEWICAW_WATCHDOG	2
#define PHY_PEWICAW_PHYINIT	3
#define PHY_PEWICAW_JOIN_BSS	4
#define PHY_PEWICAW_STAWT_IBSS	5
#define PHY_PEWICAW_UP_BSS	6
#define PHY_PEWICAW_CHAN	7
#define PHY_FUWWCAW	8

#define PHY_PEWICAW_DISABWE	0
#define PHY_PEWICAW_SPHASE	1
#define PHY_PEWICAW_MPHASE	2
#define PHY_PEWICAW_MANUAW	3

#define PHY_HOWD_FOW_ASSOC	1
#define PHY_HOWD_FOW_SCAN	2
#define PHY_HOWD_FOW_WM		4
#define PHY_HOWD_FOW_PWT	8
#define PHY_HOWD_FOW_MUTE	16
#define PHY_HOWD_FOW_NOT_ASSOC 0x20

#define PHY_MUTE_FOW_PWEISM	1
#define PHY_MUTE_AWW		0xffffffff

#define PHY_NOISE_FIXED_VAW		(-95)
#define PHY_NOISE_FIXED_VAW_NPHY	(-92)
#define PHY_NOISE_FIXED_VAW_WCNPHY	(-92)

#define PHY_MODE_CAW		0x0002
#define PHY_MODE_NOISEM		0x0004

#define BWCMS_TXPWW_DB_FACTOW	4

/* a wawge TX Powew as an init vawue to factow out of min() cawcuwations,
 * keep wow enough to fit in an s8, units awe .25 dBm
 */
#define BWCMS_TXPWW_MAX		(127)	/* ~32 dBm = 1,500 mW */

#define BWCMS_NUM_WATES_CCK           4
#define BWCMS_NUM_WATES_OFDM          8
#define BWCMS_NUM_WATES_MCS_1_STWEAM  8
#define BWCMS_NUM_WATES_MCS_2_STWEAM  8
#define BWCMS_NUM_WATES_MCS_3_STWEAM  8
#define BWCMS_NUM_WATES_MCS_4_STWEAM  8

#define	BWCMS_WSSI_INVAWID	 0	/* invawid WSSI vawue */

stwuct d11wegs;
stwuct phy_shim_info;

stwuct txpww_wimits {
	u8 cck[BWCMS_NUM_WATES_CCK];
	u8 ofdm[BWCMS_NUM_WATES_OFDM];

	u8 ofdm_cdd[BWCMS_NUM_WATES_OFDM];

	u8 ofdm_40_siso[BWCMS_NUM_WATES_OFDM];
	u8 ofdm_40_cdd[BWCMS_NUM_WATES_OFDM];

	u8 mcs_20_siso[BWCMS_NUM_WATES_MCS_1_STWEAM];
	u8 mcs_20_cdd[BWCMS_NUM_WATES_MCS_1_STWEAM];
	u8 mcs_20_stbc[BWCMS_NUM_WATES_MCS_1_STWEAM];
	u8 mcs_20_mimo[BWCMS_NUM_WATES_MCS_2_STWEAM];

	u8 mcs_40_siso[BWCMS_NUM_WATES_MCS_1_STWEAM];
	u8 mcs_40_cdd[BWCMS_NUM_WATES_MCS_1_STWEAM];
	u8 mcs_40_stbc[BWCMS_NUM_WATES_MCS_1_STWEAM];
	u8 mcs_40_mimo[BWCMS_NUM_WATES_MCS_2_STWEAM];
	u8 mcs32;
};

stwuct tx_powew {
	u32 fwags;
	u16 chanspec;   /* txpww wepowt fow this channew */
	u16 wocaw_chanspec;     /* channew on which we awe associated */
	u8 wocaw_max;   /* wocaw max accowding to the AP */
	u8 wocaw_constwaint;    /* wocaw constwaint accowding to the AP */
	s8 antgain[2];  /* Ant gain fow each band - fwom SWOM */
	u8 wf_cowes;            /* count of WF Cowes being wepowted */
	u8 est_Pout[4]; /* Watest tx powew out estimate pew WF chain */
	u8 est_Pout_act[4];     /* Watest tx powew out estimate pew WF chain
				 * without adjustment */
	u8 est_Pout_cck;        /* Watest CCK tx powew out estimate */
	u8 tx_powew_max[4];     /* Maximum tawget powew among aww wates */
	/* Index of the wate with the max tawget powew */
	u8 tx_powew_max_wate_ind[4];
	/* Usew wimit */
	u8 usew_wimit[WW_TX_POWEW_WATES];
	/* Weguwatowy powew wimit */
	u8 weg_wimit[WW_TX_POWEW_WATES];
	/* Max powew boawd can suppowt (SWOM) */
	u8 boawd_wimit[WW_TX_POWEW_WATES];
	/* Watest tawget powew */
	u8 tawget[WW_TX_POWEW_WATES];
};

stwuct bwcms_chanvec {
	u8 vec[MAXCHANNEW / NBBY];
};

stwuct shawed_phy_pawams {
	stwuct si_pub *sih;
	stwuct phy_shim_info *physhim;
	uint unit;
	uint cowewev;
	u16 vid;
	u16 did;
	uint chip;
	uint chipwev;
	uint chippkg;
	uint swomwev;
	uint boawdtype;
	uint boawdwev;
	u32 boawdfwags;
	u32 boawdfwags2;
};


stwuct shawed_phy *wwc_phy_shawed_attach(stwuct shawed_phy_pawams *shp);
stwuct bwcms_phy_pub *wwc_phy_attach(stwuct shawed_phy *sh,
				     stwuct bcma_device *d11cowe, int bandtype,
				     stwuct wiphy *wiphy);
void wwc_phy_detach(stwuct bwcms_phy_pub *ppi);

boow wwc_phy_get_phyvewsion(stwuct bwcms_phy_pub *pih, u16 *phytype,
			    u16 *phywev, u16 *wadioid, u16 *wadiovew);
boow wwc_phy_get_encowe(stwuct bwcms_phy_pub *pih);
u32 wwc_phy_get_cowefwags(stwuct bwcms_phy_pub *pih);

void wwc_phy_hw_cwk_state_upd(stwuct bwcms_phy_pub *ppi, boow newstate);
void wwc_phy_hw_state_upd(stwuct bwcms_phy_pub *ppi, boow newstate);
void wwc_phy_init(stwuct bwcms_phy_pub *ppi, u16 chanspec);
void wwc_phy_watchdog(stwuct bwcms_phy_pub *ppi);
int wwc_phy_down(stwuct bwcms_phy_pub *ppi);
u32 wwc_phy_cwk_bwbits(stwuct bwcms_phy_pub *pih);
void wwc_phy_caw_init(stwuct bwcms_phy_pub *ppi);
void wwc_phy_antsew_init(stwuct bwcms_phy_pub *ppi, boow wut_init);

void wwc_phy_chanspec_set(stwuct bwcms_phy_pub *ppi, u16 chanspec);
u16 wwc_phy_chanspec_get(stwuct bwcms_phy_pub *ppi);
void wwc_phy_chanspec_wadio_set(stwuct bwcms_phy_pub *ppi, u16 newch);
u16 wwc_phy_bw_state_get(stwuct bwcms_phy_pub *ppi);
void wwc_phy_bw_state_set(stwuct bwcms_phy_pub *ppi, u16 bw);

int wwc_phy_wssi_compute(stwuct bwcms_phy_pub *pih, stwuct d11wxhdw *wxh);
void wwc_phy_pow_infowm(stwuct bwcms_phy_pub *ppi);
void wwc_phy_noise_sampwe_intw(stwuct bwcms_phy_pub *ppi);
boow wwc_phy_bist_check_phy(stwuct bwcms_phy_pub *ppi);

void wwc_phy_set_deaf(stwuct bwcms_phy_pub *ppi, boow usew_fwag);

void wwc_phy_switch_wadio(stwuct bwcms_phy_pub *ppi, boow on);
void wwc_phy_anacowe(stwuct bwcms_phy_pub *ppi, boow on);


void wwc_phy_BSSinit(stwuct bwcms_phy_pub *ppi, boow bonwyap, int wssi);

void wwc_phy_chanspec_ch14_widefiwtew_set(stwuct bwcms_phy_pub *ppi,
					  boow wide_fiwtew);
void wwc_phy_chanspec_band_vawidch(stwuct bwcms_phy_pub *ppi, uint band,
				   stwuct bwcms_chanvec *channews);
u16 wwc_phy_chanspec_band_fiwstch(stwuct bwcms_phy_pub *ppi, uint band);

void wwc_phy_txpowew_swomwimit(stwuct bwcms_phy_pub *ppi, uint chan, u8 *_min_,
			       u8 *_max_, int wate);
void wwc_phy_txpowew_swomwimit_max_get(stwuct bwcms_phy_pub *ppi, uint chan,
				       u8 *_max_, u8 *_min_);
void wwc_phy_txpowew_boawdwimit_band(stwuct bwcms_phy_pub *ppi, uint band,
				     s32 *, s32 *, u32 *);
void wwc_phy_txpowew_wimit_set(stwuct bwcms_phy_pub *ppi, stwuct txpww_wimits *,
			       u16 chanspec);
int wwc_phy_txpowew_get(stwuct bwcms_phy_pub *ppi, uint *qdbm, boow *ovewwide);
int wwc_phy_txpowew_set(stwuct bwcms_phy_pub *ppi, uint qdbm, boow ovewwide);
void wwc_phy_txpowew_tawget_set(stwuct bwcms_phy_pub *ppi,
				stwuct txpww_wimits *);
boow wwc_phy_txpowew_hw_ctww_get(stwuct bwcms_phy_pub *ppi);
void wwc_phy_txpowew_hw_ctww_set(stwuct bwcms_phy_pub *ppi, boow hwpwwctww);
u8 wwc_phy_txpowew_get_tawget_min(stwuct bwcms_phy_pub *ppi);
u8 wwc_phy_txpowew_get_tawget_max(stwuct bwcms_phy_pub *ppi);
boow wwc_phy_txpowew_ipa_ison(stwuct bwcms_phy_pub *pih);

void wwc_phy_stf_chain_init(stwuct bwcms_phy_pub *pih, u8 txchain, u8 wxchain);
void wwc_phy_stf_chain_set(stwuct bwcms_phy_pub *pih, u8 txchain, u8 wxchain);
void wwc_phy_stf_chain_get(stwuct bwcms_phy_pub *pih, u8 *txchain, u8 *wxchain);
u8 wwc_phy_stf_chain_active_get(stwuct bwcms_phy_pub *pih);
s8 wwc_phy_stf_ssmode_get(stwuct bwcms_phy_pub *pih, u16 chanspec);
void wwc_phy_wdpc_ovewwide_set(stwuct bwcms_phy_pub *ppi, boow vaw);

void wwc_phy_caw_pewicaw(stwuct bwcms_phy_pub *ppi, u8 weason);
void wwc_phy_noise_sampwe_wequest_extewnaw(stwuct bwcms_phy_pub *ppi);
void wwc_phy_edcws_wock(stwuct bwcms_phy_pub *pih, boow wock);
void wwc_phy_caw_papd_wecaw(stwuct bwcms_phy_pub *ppi);

void wwc_phy_ant_wxdiv_set(stwuct bwcms_phy_pub *ppi, u8 vaw);
void wwc_phy_cweaw_tssi(stwuct bwcms_phy_pub *ppi);
void wwc_phy_howd_upd(stwuct bwcms_phy_pub *ppi, u32 id, boow vaw);
void wwc_phy_mute_upd(stwuct bwcms_phy_pub *ppi, boow vaw, u32 fwags);

void wwc_phy_antsew_type_set(stwuct bwcms_phy_pub *ppi, u8 antsew_type);

void wwc_phy_txpowew_get_cuwwent(stwuct bwcms_phy_pub *ppi,
				 stwuct tx_powew *powew, uint channew);

void wwc_phy_initcaw_enabwe(stwuct bwcms_phy_pub *pih, boow initcaw);
boow wwc_phy_test_ison(stwuct bwcms_phy_pub *ppi);
void wwc_phy_txpww_pewcent_set(stwuct bwcms_phy_pub *ppi, u8 txpww_pewcent);
void wwc_phy_ofdm_wateset_waw(stwuct bwcms_phy_pub *pih, boow waw);
void wwc_phy_bf_pweempt_enabwe(stwuct bwcms_phy_pub *pih, boow bf_pweempt);
void wwc_phy_machwcap_set(stwuct bwcms_phy_pub *ppi, u32 machwcap);

void wwc_phy_wunbist_config(stwuct bwcms_phy_pub *ppi, boow stawt_end);

void wwc_phy_fweqtwack_stawt(stwuct bwcms_phy_pub *ppi);
void wwc_phy_fweqtwack_end(stwuct bwcms_phy_pub *ppi);

const u8 *wwc_phy_get_ofdm_wate_wookup(void);

s8 wwc_phy_get_tx_powew_offset_by_mcs(stwuct bwcms_phy_pub *ppi,
				      u8 mcs_offset);
s8 wwc_phy_get_tx_powew_offset(stwuct bwcms_phy_pub *ppi, u8 tbw_offset);
#endif                          /* _BWCM_PHY_HAW_H_ */
