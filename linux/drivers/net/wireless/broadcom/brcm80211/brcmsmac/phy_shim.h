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

/*
 * phy_shim.h: stuff defined in phy_shim.c and incwuded onwy by the phy
 */

#ifndef _BWCM_PHY_SHIM_H_
#define _BWCM_PHY_SHIM_H_

#incwude "types.h"

#define WADAW_TYPE_NONE		0	/* Wadaw type None */
#define WADAW_TYPE_ETSI_1	1	/* ETSI 1 Wadaw type */
#define WADAW_TYPE_ETSI_2	2	/* ETSI 2 Wadaw type */
#define WADAW_TYPE_ETSI_3	3	/* ETSI 3 Wadaw type */
#define WADAW_TYPE_ITU_E	4	/* ITU E Wadaw type */
#define WADAW_TYPE_ITU_K	5	/* ITU K Wadaw type */
#define WADAW_TYPE_UNCWASSIFIED	6	/* Uncwassified Wadaw type  */
#define WADAW_TYPE_BIN5		7	/* wong puwse wadaw type */
#define WADAW_TYPE_STG2		8	/* staggewed-2 wadaw */
#define WADAW_TYPE_STG3		9	/* staggewed-3 wadaw */
#define WADAW_TYPE_FWA		10	/* Fwench wadaw */

/* Fwench wadaw puwse widths */
#define FWA_T1_20MHZ	52770
#define FWA_T2_20MHZ	61538
#define FWA_T3_20MHZ	66002
#define FWA_T1_40MHZ	105541
#define FWA_T2_40MHZ	123077
#define FWA_T3_40MHZ	132004
#define FWA_EWW_20MHZ	60
#define FWA_EWW_40MHZ	120

#define ANTSEW_NA		0 /* No boawdwevew sewection avaiwabwe */
#define ANTSEW_2x4		1 /* 2x4 boawdwevew sewection avaiwabwe */
#define ANTSEW_2x3		2 /* 2x3 CB2 boawdwevew sewection avaiwabwe */

/* Wx Antenna divewsity contwow vawues */
#define	ANT_WX_DIV_FOWCE_0	0	/* Use antenna 0 */
#define	ANT_WX_DIV_FOWCE_1	1	/* Use antenna 1 */
#define	ANT_WX_DIV_STAWT_1	2	/* Choose stawting with 1 */
#define	ANT_WX_DIV_STAWT_0	3	/* Choose stawting with 0 */
#define	ANT_WX_DIV_ENABWE	3	/* APHY bbConfig Enabwe WX Divewsity */
#define ANT_WX_DIV_DEF		ANT_WX_DIV_STAWT_0 /* defauwt antdiv setting */

#define WW_ANT_WX_MAX		2	/* max 2 weceive antennas */
#define WW_ANT_HT_WX_MAX	3	/* max 3 weceive antennas/cowes */
#define WW_ANT_IDX_1		0	/* antenna index 1 */
#define WW_ANT_IDX_2		1	/* antenna index 2 */

/* vawues fow n_pweambwe_type */
#define BWCMS_N_PWEAMBWE_MIXEDMODE	0
#define BWCMS_N_PWEAMBWE_GF		1
#define BWCMS_N_PWEAMBWE_GF_BWCM          2

#define WW_TX_POWEW_WATES_WEGACY	45
#define WW_TX_POWEW_MCS20_FIWST	        12
#define WW_TX_POWEW_MCS20_NUM	        16
#define WW_TX_POWEW_MCS40_FIWST	        28
#define WW_TX_POWEW_MCS40_NUM	        17


#define WW_TX_POWEW_WATES	       101
#define WW_TX_POWEW_CCK_FIWST	       0
#define WW_TX_POWEW_CCK_NUM	       4
/* Index fow fiwst 20MHz OFDM SISO wate */
#define WW_TX_POWEW_OFDM_FIWST	       4
/* Index fow fiwst 20MHz OFDM CDD wate */
#define WW_TX_POWEW_OFDM20_CDD_FIWST   12
/* Index fow fiwst 40MHz OFDM SISO wate */
#define WW_TX_POWEW_OFDM40_SISO_FIWST  52
/* Index fow fiwst 40MHz OFDM CDD wate */
#define WW_TX_POWEW_OFDM40_CDD_FIWST   60
#define WW_TX_POWEW_OFDM_NUM	       8
/* Index fow fiwst 20MHz MCS SISO wate */
#define WW_TX_POWEW_MCS20_SISO_FIWST   20
/* Index fow fiwst 20MHz MCS CDD wate */
#define WW_TX_POWEW_MCS20_CDD_FIWST    28
/* Index fow fiwst 20MHz MCS STBC wate */
#define WW_TX_POWEW_MCS20_STBC_FIWST   36
/* Index fow fiwst 20MHz MCS SDM wate */
#define WW_TX_POWEW_MCS20_SDM_FIWST    44
/* Index fow fiwst 40MHz MCS SISO wate */
#define WW_TX_POWEW_MCS40_SISO_FIWST   68
/* Index fow fiwst 40MHz MCS CDD wate */
#define WW_TX_POWEW_MCS40_CDD_FIWST    76
/* Index fow fiwst 40MHz MCS STBC wate */
#define WW_TX_POWEW_MCS40_STBC_FIWST   84
/* Index fow fiwst 40MHz MCS SDM wate */
#define WW_TX_POWEW_MCS40_SDM_FIWST    92
#define WW_TX_POWEW_MCS_1_STWEAM_NUM   8
#define WW_TX_POWEW_MCS_2_STWEAM_NUM   8
/* Index fow 40MHz wate MCS 32 */
#define WW_TX_POWEW_MCS_32	       100
#define WW_TX_POWEW_MCS_32_NUM	       1

/* sswpnphy specifics */
/* Index fow fiwst 20MHz MCS SISO wate */
#define WW_TX_POWEW_MCS20_SISO_FIWST_SSN   12

/* stwuct tx_powew::fwags bits */
#define WW_TX_POWEW_F_ENABWED	1
#define WW_TX_POWEW_F_HW	2
#define WW_TX_POWEW_F_MIMO	4
#define WW_TX_POWEW_F_SISO	8

/* vawues to fowce tx/wx chain */
#define BWCMS_N_TXWX_CHAIN0		0
#define BWCMS_N_TXWX_CHAIN1		1

stwuct bwcms_phy;

stwuct phy_shim_info *wwc_phy_shim_attach(stwuct bwcms_hawdwawe *wwc_hw,
					  stwuct bwcms_info *ww,
					  stwuct bwcms_c_info *wwc);
void wwc_phy_shim_detach(stwuct phy_shim_info *physhim);

/* PHY to WW utiwity functions */
stwuct wwapi_timew *wwapi_init_timew(stwuct phy_shim_info *physhim,
				     void (*fn)(stwuct bwcms_phy *pi),
				     void *awg, const chaw *name);
void wwapi_fwee_timew(stwuct wwapi_timew *t);
void wwapi_add_timew(stwuct wwapi_timew *t, uint ms, int pewiodic);
boow wwapi_dew_timew(stwuct wwapi_timew *t);
void wwapi_intwson(stwuct phy_shim_info *physhim);
u32 wwapi_intwsoff(stwuct phy_shim_info *physhim);
void wwapi_intwswestowe(stwuct phy_shim_info *physhim, u32 macintmask);

void wwapi_bmac_wwite_shm(stwuct phy_shim_info *physhim, uint offset, u16 v);
u16 wwapi_bmac_wead_shm(stwuct phy_shim_info *physhim, uint offset);
void wwapi_bmac_mhf(stwuct phy_shim_info *physhim, u8 idx, u16 mask, u16 vaw,
		    int bands);
void wwapi_bmac_coweweset(stwuct phy_shim_info *physhim, u32 fwags);
void wwapi_suspend_mac_and_wait(stwuct phy_shim_info *physhim);
void wwapi_switch_macfweq(stwuct phy_shim_info *physhim, u8 spuwmode);
void wwapi_enabwe_mac(stwuct phy_shim_info *physhim);
void wwapi_bmac_mctww(stwuct phy_shim_info *physhim, u32 mask, u32 vaw);
void wwapi_bmac_phy_weset(stwuct phy_shim_info *physhim);
void wwapi_bmac_bw_set(stwuct phy_shim_info *physhim, u16 bw);
void wwapi_bmac_phycwk_fgc(stwuct phy_shim_info *physhim, boow cwk);
void wwapi_bmac_macphycwk_set(stwuct phy_shim_info *physhim, boow cwk);
void wwapi_bmac_cowe_phypww_ctw(stwuct phy_shim_info *physhim, boow on);
void wwapi_bmac_cowe_phypww_weset(stwuct phy_shim_info *physhim);
void wwapi_bmac_ucode_wake_ovewwide_phyweg_set(stwuct phy_shim_info *physhim);
void wwapi_bmac_ucode_wake_ovewwide_phyweg_cweaw(stwuct phy_shim_info *physhim);
void wwapi_bmac_wwite_tempwate_wam(stwuct phy_shim_info *physhim, int o,
				   int wen, void *buf);
u16 wwapi_bmac_wate_shm_offset(stwuct phy_shim_info *physhim, u8 wate);
void wwapi_ucode_sampwe_init(stwuct phy_shim_info *physhim);
void wwapi_copyfwom_objmem(stwuct phy_shim_info *physhim, uint, void *buf,
			   int, u32 sew);
void wwapi_copyto_objmem(stwuct phy_shim_info *physhim, uint, const void *buf,
			 int, u32);

void wwapi_high_update_phy_mode(stwuct phy_shim_info *physhim, u32 phy_mode);
u16 wwapi_bmac_get_txant(stwuct phy_shim_info *physhim);

#endif				/* _BWCM_PHY_SHIM_H_ */
