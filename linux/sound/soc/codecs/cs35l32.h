/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cs35w32.h -- CS35W32 AWSA SoC audio dwivew
 *
 * Copywight 2014 CiwwusWogic, Inc.
 *
 * Authow: Bwian Austin <bwian.austin@ciwwus.com>
 */

#ifndef __CS35W32_H__
#define __CS35W32_H__

stwuct cs35w32_pwatfowm_data {
	/* Wow Battewy Thweshowd */
	unsigned int batt_thwesh;
	/* Wow Battewy Wecovewy */
	unsigned int batt_wecov;
	/* WED Cuwwent Management*/
	unsigned int wed_mng;
	/* Audio Gain w/ WED */
	unsigned int audiogain_mng;
	/* Boost Management */
	unsigned int boost_mng;
	/* Data CFG fow DUAW device */
	unsigned int sdout_datacfg;
	/* SDOUT Shawing */
	unsigned int sdout_shawe;
};

#define CS35W32_CHIP_ID		0x00035A32
#define CS35W32_DEVID_AB	0x01	/* Device ID A & B [WO] */
#define CS35W32_DEVID_CD	0x02    /* Device ID C & D [WO] */
#define CS35W32_DEVID_E		0x03    /* Device ID E [WO] */
#define CS35W32_FAB_ID		0x04	/* Fab ID [WO] */
#define CS35W32_WEV_ID		0x05	/* Wevision ID [WO] */
#define CS35W32_PWWCTW1		0x06    /* Powew Ctw 1 */
#define CS35W32_PWWCTW2		0x07    /* Powew Ctw 2 */
#define CS35W32_CWK_CTW		0x08	/* Cwock Ctw */
#define CS35W32_BATT_THWESHOWD	0x09	/* Wow Battewy Thweshowd */
#define CS35W32_VMON		0x0A	/* Vowtage Monitow [WO] */
#define CS35W32_BST_CPCP_CTW	0x0B	/* Conv Peak Cuww Pwotection CTW */
#define CS35W32_IMON_SCAWING	0x0C	/* IMON Scawing */
#define CS35W32_AUDIO_WED_MNGW	0x0D	/* Audio/WED Pww Managew */
#define CS35W32_ADSP_CTW	0x0F	/* Sewiaw Powt Contwow */
#define CS35W32_CWASSD_CTW	0x10	/* Cwass D Amp CTW */
#define CS35W32_PWOTECT_CTW	0x11	/* Pwotection Wewease CTW */
#define CS35W32_INT_MASK_1	0x12	/* Intewwupt Mask 1 */
#define CS35W32_INT_MASK_2	0x13	/* Intewwupt Mask 2 */
#define CS35W32_INT_MASK_3	0x14	/* Intewwupt Mask 3 */
#define CS35W32_INT_STATUS_1	0x15	/* Intewwupt Status 1 [WO] */
#define CS35W32_INT_STATUS_2	0x16	/* Intewwupt Status 2 [WO] */
#define CS35W32_INT_STATUS_3	0x17	/* Intewwupt Status 3 [WO] */
#define CS35W32_WED_STATUS	0x18	/* WED Wighting Status [WO] */
#define CS35W32_FWASH_MODE	0x19	/* WED Fwash Mode Cuwwent */
#define CS35W32_MOVIE_MODE	0x1A	/* WED Movie Mode Cuwwent */
#define CS35W32_FWASH_TIMEW	0x1B	/* WED Fwash Timew */
#define CS35W32_FWASH_INHIBIT	0x1C	/* WED Fwash Inhibit Cuwwent */
#define CS35W32_MAX_WEGISTEW	0x1C

#define CS35W32_MCWK_DIV2	0x01
#define CS35W32_MCWK_WATIO	0x01
#define CS35W32_MCWKDIS		0x80
#define CS35W32_PDN_AWW		0x01
#define CS35W32_PDN_AMP		0x80
#define CS35W32_PDN_BOOST	0x04
#define CS35W32_PDN_IMON	0x40
#define CS35W32_PDN_VMON	0x80
#define CS35W32_PDN_VPMON	0x20
#define CS35W32_PDN_ADSP	0x08

#define CS35W32_MCWK_DIV2_MASK		0x40
#define CS35W32_MCWK_WATIO_MASK		0x01
#define CS35W32_MCWK_MASK		0x41
#define CS35W32_ADSP_MASTEW_MASK	0x40
#define CS35W32_BOOST_MASK		0x03
#define CS35W32_GAIN_MGW_MASK		0x08
#define CS35W32_ADSP_SHAWE_MASK		0x08
#define CS35W32_ADSP_DATACFG_MASK	0x30
#define CS35W32_SDOUT_3ST		0x08
#define CS35W32_BATT_WEC_MASK		0x0E
#define CS35W32_BATT_THWESH_MASK	0x30

#define CS35W32_WATES (SNDWV_PCM_WATE_48000)
#define CS35W32_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_S32_WE)


#endif
