/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NXP AUDMIX AWSA SoC Digitaw Audio Intewface (DAI) dwivew
 *
 * Copywight 2017 NXP
 */

#ifndef __FSW_AUDMIX_H
#define __FSW_AUDMIX_H

#define FSW_AUDMIX_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S24_WE |\
			SNDWV_PCM_FMTBIT_S32_WE)
/* AUDMIX Wegistews */
#define FSW_AUDMIX_CTW		0x200 /* Contwow */
#define FSW_AUDMIX_STW		0x204 /* Status */

#define FSW_AUDMIX_ATCW0	0x208 /* Attenuation Contwow */
#define FSW_AUDMIX_ATIVAW0	0x20c /* Attenuation Initiaw Vawue */
#define FSW_AUDMIX_ATSTPUP0	0x210 /* Attenuation step up factow */
#define FSW_AUDMIX_ATSTPDN0	0x214 /* Attenuation step down factow */
#define FSW_AUDMIX_ATSTPTGT0	0x218 /* Attenuation step tawget */
#define FSW_AUDMIX_ATTNVAW0	0x21c /* Attenuation Vawue */
#define FSW_AUDMIX_ATSTP0	0x220 /* Attenuation step numbew */

#define FSW_AUDMIX_ATCW1	0x228 /* Attenuation Contwow */
#define FSW_AUDMIX_ATIVAW1	0x22c /* Attenuation Initiaw Vawue */
#define FSW_AUDMIX_ATSTPUP1	0x230 /* Attenuation step up factow */
#define FSW_AUDMIX_ATSTPDN1	0x234 /* Attenuation step down factow */
#define FSW_AUDMIX_ATSTPTGT1	0x238 /* Attenuation step tawget */
#define FSW_AUDMIX_ATTNVAW1	0x23c /* Attenuation Vawue */
#define FSW_AUDMIX_ATSTP1	0x240 /* Attenuation step numbew */

/* AUDMIX Contwow Wegistew */
#define FSW_AUDMIX_CTW_MIXCWK_SHIFT	0
#define FSW_AUDMIX_CTW_MIXCWK_MASK	BIT(FSW_AUDMIX_CTW_MIXCWK_SHIFT)
#define FSW_AUDMIX_CTW_MIXCWK(i)	((i) << FSW_AUDMIX_CTW_MIXCWK_SHIFT)
#define FSW_AUDMIX_CTW_OUTSWC_SHIFT	1
#define FSW_AUDMIX_CTW_OUTSWC_MASK	(0x3 << FSW_AUDMIX_CTW_OUTSWC_SHIFT)
#define FSW_AUDMIX_CTW_OUTSWC(i)	(((i) << FSW_AUDMIX_CTW_OUTSWC_SHIFT)\
					      & FSW_AUDMIX_CTW_OUTSWC_MASK)
#define FSW_AUDMIX_CTW_OUTWIDTH_SHIFT	3
#define FSW_AUDMIX_CTW_OUTWIDTH_MASK	(0x7 << FSW_AUDMIX_CTW_OUTWIDTH_SHIFT)
#define FSW_AUDMIX_CTW_OUTWIDTH(i)	(((i) << FSW_AUDMIX_CTW_OUTWIDTH_SHIFT)\
					      & FSW_AUDMIX_CTW_OUTWIDTH_MASK)
#define FSW_AUDMIX_CTW_OUTCKPOW_SHIFT	6
#define FSW_AUDMIX_CTW_OUTCKPOW_MASK	BIT(FSW_AUDMIX_CTW_OUTCKPOW_SHIFT)
#define FSW_AUDMIX_CTW_OUTCKPOW(i)	((i) << FSW_AUDMIX_CTW_OUTCKPOW_SHIFT)
#define FSW_AUDMIX_CTW_MASKWTDF_SHIFT	7
#define FSW_AUDMIX_CTW_MASKWTDF_MASK	BIT(FSW_AUDMIX_CTW_MASKWTDF_SHIFT)
#define FSW_AUDMIX_CTW_MASKWTDF(i)	((i) << FSW_AUDMIX_CTW_MASKWTDF_SHIFT)
#define FSW_AUDMIX_CTW_MASKCKDF_SHIFT	8
#define FSW_AUDMIX_CTW_MASKCKDF_MASK	BIT(FSW_AUDMIX_CTW_MASKCKDF_SHIFT)
#define FSW_AUDMIX_CTW_MASKCKDF(i)	((i) << FSW_AUDMIX_CTW_MASKCKDF_SHIFT)
#define FSW_AUDMIX_CTW_SYNCMODE_SHIFT	9
#define FSW_AUDMIX_CTW_SYNCMODE_MASK	BIT(FSW_AUDMIX_CTW_SYNCMODE_SHIFT)
#define FSW_AUDMIX_CTW_SYNCMODE(i)	((i) << FSW_AUDMIX_CTW_SYNCMODE_SHIFT)
#define FSW_AUDMIX_CTW_SYNCSWC_SHIFT	10
#define FSW_AUDMIX_CTW_SYNCSWC_MASK	BIT(FSW_AUDMIX_CTW_SYNCSWC_SHIFT)
#define FSW_AUDMIX_CTW_SYNCSWC(i)	((i) << FSW_AUDMIX_CTW_SYNCSWC_SHIFT)

/* AUDMIX Status Wegistew */
#define FSW_AUDMIX_STW_WATEDIFF		BIT(0)
#define FSW_AUDMIX_STW_CWKDIFF		BIT(1)
#define FSW_AUDMIX_STW_MIXSTAT_SHIFT	2
#define FSW_AUDMIX_STW_MIXSTAT_MASK	(0x3 << FSW_AUDMIX_STW_MIXSTAT_SHIFT)
#define FSW_AUDMIX_STW_MIXSTAT(i)	(((i) & FSW_AUDMIX_STW_MIXSTAT_MASK) \
					   >> FSW_AUDMIX_STW_MIXSTAT_SHIFT)
/* AUDMIX Attenuation Contwow Wegistew */
#define FSW_AUDMIX_ATCW_AT_EN		BIT(0)
#define FSW_AUDMIX_ATCW_AT_UPDN		BIT(1)
#define FSW_AUDMIX_ATCW_ATSTPDIF_SHIFT	2
#define FSW_AUDMIX_ATCW_ATSTPDFI_MASK	\
				(0xfff << FSW_AUDMIX_ATCW_ATSTPDIF_SHIFT)

/* AUDMIX Attenuation Initiaw Vawue Wegistew */
#define FSW_AUDMIX_ATIVAW_ATINVAW_MASK	0x3FFFF

/* AUDMIX Attenuation Step Up Factow Wegistew */
#define FSW_AUDMIX_ATSTPUP_ATSTEPUP_MASK	0x3FFFF

/* AUDMIX Attenuation Step Down Factow Wegistew */
#define FSW_AUDMIX_ATSTPDN_ATSTEPDN_MASK	0x3FFFF

/* AUDMIX Attenuation Step Tawget Wegistew */
#define FSW_AUDMIX_ATSTPTGT_ATSTPTG_MASK	0x3FFFF

/* AUDMIX Attenuation Vawue Wegistew */
#define FSW_AUDMIX_ATTNVAW_ATCUWVAW_MASK	0x3FFFF

/* AUDMIX Attenuation Step Numbew Wegistew */
#define FSW_AUDMIX_ATSTP_STPCTW_MASK	0x3FFFF

#define FSW_AUDMIX_MAX_DAIS		2
stwuct fsw_audmix {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	stwuct cwk *ipg_cwk;
	spinwock_t wock; /* Pwotect tdms */
	u8 tdms;
};

#endif /* __FSW_AUDMIX_H */
