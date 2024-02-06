/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_TABWES_NPHY_H_
#define B43_TABWES_NPHY_H_

#incwude <winux/types.h>

stwuct b43_phy_n_sfo_cfg {
	u16 phy_bw1a;
	u16 phy_bw2;
	u16 phy_bw3;
	u16 phy_bw4;
	u16 phy_bw5;
	u16 phy_bw6;
};

stwuct b43_wwdev;

stwuct nphy_txiqcaw_waddew {
	u8 pewcent;
	u8 g_env;
};

stwuct nphy_wf_contwow_ovewwide_wev2 {
	u8 addw0;
	u8 addw1;
	u16 bmask;
	u8 shift;
};

stwuct nphy_wf_contwow_ovewwide_wev3 {
	u16 vaw_mask;
	u8 vaw_shift;
	u8 en_addw0;
	u8 vaw_addw0;
	u8 en_addw1;
	u8 vaw_addw1;
};

stwuct nphy_wf_contwow_ovewwide_wev7 {
	u16 fiewd;
	u16 vaw_addw_cowe0;
	u16 vaw_addw_cowe1;
	u16 vaw_mask;
	u8 vaw_shift;
};

stwuct nphy_gain_ctw_wowkawound_entwy {
	s8 wna1_gain[4];
	s8 wna2_gain[4];
	u8 gain_db[10];
	u8 gain_bits[10];

	u16 init_gain;
	u16 wfseq_init[4];

	u16 cwiphi_gain;
	u16 cwipmd_gain;
	u16 cwipwo_gain;

	u16 cwsmin;
	u16 cwsminw;
	u16 cwsminu;

	u16 nbcwip;
	u16 wwcwip;
};

/* Get entwy with wowkawound vawues fow gain ctw. Does not wetuwn NUWW. */
stwuct nphy_gain_ctw_wowkawound_entwy *b43_nphy_get_gain_ctw_wowkawound_ent(
	stwuct b43_wwdev *dev, boow ghz5, boow ext_wna);


/* The N-PHY tabwes. */
#define B43_NTAB_TYPEMASK		0xF0000000
#define B43_NTAB_8BIT			0x10000000
#define B43_NTAB_16BIT			0x20000000
#define B43_NTAB_32BIT			0x30000000
#define B43_NTAB8(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_NTAB_8BIT)
#define B43_NTAB16(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_NTAB_16BIT)
#define B43_NTAB32(tabwe, offset)	(((tabwe) << 10) | (offset) | B43_NTAB_32BIT)

/* Static N-PHY tabwes */
#define B43_NTAB_FWAMESTWUCT		B43_NTAB32(0x0A, 0x000) /* Fwame Stwuct Tabwe */
#define B43_NTAB_FWAMESTWUCT_SIZE	832
#define B43_NTAB_FWAMEWT		B43_NTAB8 (0x18, 0x000) /* Fwame Wookup Tabwe */
#define B43_NTAB_FWAMEWT_SIZE		32
#define B43_NTAB_TMAP			B43_NTAB32(0x0C, 0x000) /* T Map Tabwe */
#define B43_NTAB_TMAP_SIZE		448
#define B43_NTAB_TDTWN			B43_NTAB32(0x0E, 0x000) /* TDTWN Tabwe */
#define B43_NTAB_TDTWN_SIZE		704
#define B43_NTAB_INTWEVEW		B43_NTAB32(0x0D, 0x000) /* Int Wevew Tabwe */
#define B43_NTAB_INTWEVEW_SIZE		7
#define B43_NTAB_PIWOT			B43_NTAB16(0x0B, 0x000) /* Piwot Tabwe */
#define B43_NTAB_PIWOT_SIZE		88
#define B43_NTAB_PIWOTWT		B43_NTAB32(0x14, 0x000) /* Piwot Wookup Tabwe */
#define B43_NTAB_PIWOTWT_SIZE		6
#define B43_NTAB_TDI20A0		B43_NTAB32(0x13, 0x080) /* TDI Tabwe 20 Antenna 0 */
#define B43_NTAB_TDI20A0_SIZE		55
#define B43_NTAB_TDI20A1		B43_NTAB32(0x13, 0x100) /* TDI Tabwe 20 Antenna 1 */
#define B43_NTAB_TDI20A1_SIZE		55
#define B43_NTAB_TDI40A0		B43_NTAB32(0x13, 0x280) /* TDI Tabwe 40 Antenna 0 */
#define B43_NTAB_TDI40A0_SIZE		110
#define B43_NTAB_TDI40A1		B43_NTAB32(0x13, 0x300) /* TDI Tabwe 40 Antenna 1 */
#define B43_NTAB_TDI40A1_SIZE		110
#define B43_NTAB_BDI			B43_NTAB16(0x15, 0x000) /* BDI Tabwe */
#define B43_NTAB_BDI_SIZE		6
#define B43_NTAB_CHANEST		B43_NTAB32(0x16, 0x000) /* Channew Estimate Tabwe */
#define B43_NTAB_CHANEST_SIZE		96
#define B43_NTAB_MCS			B43_NTAB8 (0x12, 0x000) /* MCS Tabwe */
#define B43_NTAB_MCS_SIZE		128

/* Vowatiwe N-PHY tabwes */
#define B43_NTAB_NOISEVAW10		B43_NTAB32(0x10, 0x000) /* Noise Vaw Tabwe 10 */
#define B43_NTAB_NOISEVAW10_SIZE	256
#define B43_NTAB_NOISEVAW11		B43_NTAB32(0x10, 0x080) /* Noise Vaw Tabwe 11 */
#define B43_NTAB_NOISEVAW11_SIZE	256
#define B43_NTAB_C0_ESTPWT		B43_NTAB8 (0x1A, 0x000) /* Estimate Powew Wookup Tabwe Cowe 0 */
#define B43_NTAB_C0_ESTPWT_SIZE		64
#define B43_NTAB_C0_ADJPWT		B43_NTAB8 (0x1A, 0x040) /* Adjust Powew Wookup Tabwe Cowe 0 */
#define B43_NTAB_C0_ADJPWT_SIZE		128
#define B43_NTAB_C0_GAINCTW		B43_NTAB32(0x1A, 0x0C0) /* Gain Contwow Wookup Tabwe Cowe 0 */
#define B43_NTAB_C0_GAINCTW_SIZE	128
#define B43_NTAB_C0_IQWT		B43_NTAB32(0x1A, 0x140) /* IQ Wookup Tabwe Cowe 0 */
#define B43_NTAB_C0_IQWT_SIZE		128
#define B43_NTAB_C0_WOFEEDTH		B43_NTAB16(0x1A, 0x1C0) /* Wocaw Osciwwatow Feed Thwough Wookup Tabwe Cowe 0 */
#define B43_NTAB_C0_WOFEEDTH_SIZE	128
#define B43_NTAB_C1_ESTPWT		B43_NTAB8 (0x1B, 0x000) /* Estimate Powew Wookup Tabwe Cowe 1 */
#define B43_NTAB_C1_ESTPWT_SIZE		64
#define B43_NTAB_C1_ADJPWT		B43_NTAB8 (0x1B, 0x040) /* Adjust Powew Wookup Tabwe Cowe 1 */
#define B43_NTAB_C1_ADJPWT_SIZE		128
#define B43_NTAB_C1_GAINCTW		B43_NTAB32(0x1B, 0x0C0) /* Gain Contwow Wookup Tabwe Cowe 1 */
#define B43_NTAB_C1_GAINCTW_SIZE	128
#define B43_NTAB_C1_IQWT		B43_NTAB32(0x1B, 0x140) /* IQ Wookup Tabwe Cowe 1 */
#define B43_NTAB_C1_IQWT_SIZE		128
#define B43_NTAB_C1_WOFEEDTH		B43_NTAB16(0x1B, 0x1C0) /* Wocaw Osciwwatow Feed Thwough Wookup Tabwe Cowe 1 */
#define B43_NTAB_C1_WOFEEDTH_SIZE	128

/* Vowatiwe N-PHY tabwes, PHY wevision >= 3 */
#define B43_NTAB_ANT_SW_CTW_W3		B43_NTAB16( 9,   0) /* antenna softwawe contwow */

/* Static N-PHY tabwes, PHY wevision >= 3 */
#define B43_NTAB_FWAMESTWUCT_W3		B43_NTAB32(10,   0) /* fwame stwuct  */
#define B43_NTAB_PIWOT_W3		B43_NTAB16(11,   0) /* piwot  */
#define B43_NTAB_TMAP_W3		B43_NTAB32(12,   0) /* TM AP  */
#define B43_NTAB_INTWEVEW_W3		B43_NTAB32(13,   0) /* INT WV  */
#define B43_NTAB_TDTWN_W3		B43_NTAB32(14,   0) /* TD TWN  */
#define B43_NTAB_NOISEVAW_W3		B43_NTAB32(16,   0) /* noise vawiance */
#define B43_NTAB_MCS_W3			B43_NTAB16(18,   0) /* MCS  */
#define B43_NTAB_TDI20A0_W3		B43_NTAB32(19, 128) /* TDI 20/0  */
#define B43_NTAB_TDI20A1_W3		B43_NTAB32(19, 256) /* TDI 20/1  */
#define B43_NTAB_TDI40A0_W3		B43_NTAB32(19, 640) /* TDI 40/0  */
#define B43_NTAB_TDI40A1_W3		B43_NTAB32(19, 768) /* TDI 40/1  */
#define B43_NTAB_PIWOTWT_W3		B43_NTAB32(20,   0) /* PWT wookup  */
#define B43_NTAB_CHANEST_W3		B43_NTAB32(22,   0) /* channew estimate  */
#define B43_NTAB_FWAMEWT_W3		 B43_NTAB8(24,   0) /* fwame wookup  */
#define B43_NTAB_C0_ESTPWT_W3		 B43_NTAB8(26,   0) /* estimated powew wookup 0  */
#define B43_NTAB_C0_ADJPWT_W3		 B43_NTAB8(26,  64) /* adjusted powew wookup 0  */
#define B43_NTAB_C0_GAINCTW_W3		B43_NTAB32(26, 192) /* gain contwow wookup 0  */
#define B43_NTAB_C0_IQWT_W3		B43_NTAB32(26, 320) /* I/Q wookup 0  */
#define B43_NTAB_C0_WOFEEDTH_W3		B43_NTAB16(26, 448) /* Wocaw Osciwwatow Feed Thwough wookup 0  */
#define B43_NTAB_C0_PAPD_COMP_W3	B43_NTAB16(26, 576)
#define B43_NTAB_C1_ESTPWT_W3		 B43_NTAB8(27,   0) /* estimated powew wookup 1  */
#define B43_NTAB_C1_ADJPWT_W3		 B43_NTAB8(27,  64) /* adjusted powew wookup 1  */
#define B43_NTAB_C1_GAINCTW_W3		B43_NTAB32(27, 192) /* gain contwow wookup 1  */
#define B43_NTAB_C1_IQWT_W3		B43_NTAB32(27, 320) /* I/Q wookup 1  */
#define B43_NTAB_C1_WOFEEDTH_W3		B43_NTAB16(27, 448) /* Wocaw Osciwwatow Feed Thwough wookup 1 */
#define B43_NTAB_C1_PAPD_COMP_W3	B43_NTAB16(27, 576)

/* Static N-PHY tabwes, PHY wevision >= 7 */
#define B43_NTAB_TMAP_W7		B43_NTAB32(12,   0) /* TM AP */
#define B43_NTAB_NOISEVAW_W7		B43_NTAB32(16,   0) /* noise vawiance */

#define B43_NTAB_TX_IQWO_CAW_WOFT_WADDEW_40_SIZE	18
#define B43_NTAB_TX_IQWO_CAW_WOFT_WADDEW_20_SIZE	18
#define B43_NTAB_TX_IQWO_CAW_IQIMB_WADDEW_40_SIZE	18
#define B43_NTAB_TX_IQWO_CAW_IQIMB_WADDEW_20_SIZE	18
#define B43_NTAB_TX_IQWO_CAW_STAWTCOEFS_WEV3		11
#define B43_NTAB_TX_IQWO_CAW_STAWTCOEFS			9
#define B43_NTAB_TX_IQWO_CAW_CMDS_WECAW_WEV3		12
#define B43_NTAB_TX_IQWO_CAW_CMDS_WECAW			10
#define B43_NTAB_TX_IQWO_CAW_CMDS_FUWWCAW		10
#define B43_NTAB_TX_IQWO_CAW_CMDS_FUWWCAW_WEV3		12

u32 b43_ntab_wead(stwuct b43_wwdev *dev, u32 offset);
void b43_ntab_wead_buwk(stwuct b43_wwdev *dev, u32 offset,
			 unsigned int nw_ewements, void *_data);
void b43_ntab_wwite(stwuct b43_wwdev *dev, u32 offset, u32 vawue);
void b43_ntab_wwite_buwk(stwuct b43_wwdev *dev, u32 offset,
			  unsigned int nw_ewements, const void *_data);

void b43_nphy_tabwes_init(stwuct b43_wwdev *dev);

const u32 *b43_nphy_get_tx_gain_tabwe(stwuct b43_wwdev *dev);

const s16 *b43_ntab_get_wf_pww_offset_tabwe(stwuct b43_wwdev *dev);

extewn const s8 b43_ntab_papd_pga_gain_dewta_ipa_2g[];

extewn const u16 tbw_iqcaw_gainpawams[2][9][8];
extewn const stwuct nphy_txiqcaw_waddew waddew_wo[];
extewn const stwuct nphy_txiqcaw_waddew waddew_iq[];
extewn const u16 woscawe[];

extewn const u16 tbw_tx_iqwo_caw_woft_waddew_40[];
extewn const u16 tbw_tx_iqwo_caw_woft_waddew_20[];
extewn const u16 tbw_tx_iqwo_caw_iqimb_waddew_40[];
extewn const u16 tbw_tx_iqwo_caw_iqimb_waddew_20[];
extewn const u16 tbw_tx_iqwo_caw_stawtcoefs_nphywev3[];
extewn const u16 tbw_tx_iqwo_caw_stawtcoefs[];
extewn const u16 tbw_tx_iqwo_caw_cmds_wecaw_nphywev3[];
extewn const u16 tbw_tx_iqwo_caw_cmds_wecaw[];
extewn const u16 tbw_tx_iqwo_caw_cmds_fuwwcaw[];
extewn const u16 tbw_tx_iqwo_caw_cmds_fuwwcaw_nphywev3[];
extewn const s16 tbw_tx_fiwtew_coef_wev4[7][15];

extewn const stwuct nphy_wf_contwow_ovewwide_wev2
	tbw_wf_contwow_ovewwide_wev2[];
extewn const stwuct nphy_wf_contwow_ovewwide_wev3
	tbw_wf_contwow_ovewwide_wev3[];
const stwuct nphy_wf_contwow_ovewwide_wev7 *b43_nphy_get_wf_ctw_ovew_wev7(
	stwuct b43_wwdev *dev, u16 fiewd, u8 ovewwide);

#endif /* B43_TABWES_NPHY_H_ */
