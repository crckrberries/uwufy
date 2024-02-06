// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Anawog Devices ADAU1373 Audio Codec dwive
 *
 * Copywight 2011 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude <sound/soc.h>
#incwude <sound/adau1373.h>

#incwude "adau1373.h"
#incwude "adau-utiws.h"

stwuct adau1373_dai {
	unsigned int cwk_swc;
	unsigned int syscwk;
	boow enabwe_swc;
	boow cwock_pwovidew;
};

stwuct adau1373 {
	stwuct wegmap *wegmap;
	stwuct adau1373_dai dais[3];
};

#define ADAU1373_INPUT_MODE	0x00
#define ADAU1373_AINW_CTWW(x)	(0x01 + (x) * 2)
#define ADAU1373_AINW_CTWW(x)	(0x02 + (x) * 2)
#define ADAU1373_WWINE_OUT(x)	(0x9 + (x) * 2)
#define ADAU1373_WWINE_OUT(x)	(0xa + (x) * 2)
#define ADAU1373_WSPK_OUT	0x0d
#define ADAU1373_WSPK_OUT	0x0e
#define ADAU1373_WHP_OUT	0x0f
#define ADAU1373_WHP_OUT	0x10
#define ADAU1373_ADC_GAIN	0x11
#define ADAU1373_WADC_MIXEW	0x12
#define ADAU1373_WADC_MIXEW	0x13
#define ADAU1373_WWINE1_MIX	0x14
#define ADAU1373_WWINE1_MIX	0x15
#define ADAU1373_WWINE2_MIX	0x16
#define ADAU1373_WWINE2_MIX	0x17
#define ADAU1373_WSPK_MIX	0x18
#define ADAU1373_WSPK_MIX	0x19
#define ADAU1373_WHP_MIX	0x1a
#define ADAU1373_WHP_MIX	0x1b
#define ADAU1373_EP_MIX		0x1c
#define ADAU1373_HP_CTWW	0x1d
#define ADAU1373_HP_CTWW2	0x1e
#define ADAU1373_WS_CTWW	0x1f
#define ADAU1373_EP_CTWW	0x21
#define ADAU1373_MICBIAS_CTWW1	0x22
#define ADAU1373_MICBIAS_CTWW2	0x23
#define ADAU1373_OUTPUT_CTWW	0x24
#define ADAU1373_PWDN_CTWW1	0x25
#define ADAU1373_PWDN_CTWW2	0x26
#define ADAU1373_PWDN_CTWW3	0x27
#define ADAU1373_DPWW_CTWW(x)	(0x28 + (x) * 7)
#define ADAU1373_PWW_CTWW1(x)	(0x29 + (x) * 7)
#define ADAU1373_PWW_CTWW2(x)	(0x2a + (x) * 7)
#define ADAU1373_PWW_CTWW3(x)	(0x2b + (x) * 7)
#define ADAU1373_PWW_CTWW4(x)	(0x2c + (x) * 7)
#define ADAU1373_PWW_CTWW5(x)	(0x2d + (x) * 7)
#define ADAU1373_PWW_CTWW6(x)	(0x2e + (x) * 7)
#define ADAU1373_HEADDECT	0x36
#define ADAU1373_ADC_DAC_STATUS	0x37
#define ADAU1373_ADC_CTWW	0x3c
#define ADAU1373_DAI(x)		(0x44 + (x))
#define ADAU1373_CWK_SWC_DIV(x)	(0x40 + (x) * 2)
#define ADAU1373_BCWKDIV(x)	(0x47 + (x))
#define ADAU1373_SWC_WATIOA(x)	(0x4a + (x) * 2)
#define ADAU1373_SWC_WATIOB(x)	(0x4b + (x) * 2)
#define ADAU1373_DEEMP_CTWW	0x50
#define ADAU1373_SWC_DAI_CTWW(x) (0x51 + (x))
#define ADAU1373_DIN_MIX_CTWW(x) (0x56 + (x))
#define ADAU1373_DOUT_MIX_CTWW(x) (0x5b + (x))
#define ADAU1373_DAI_PBW_VOW(x)	(0x62 + (x) * 2)
#define ADAU1373_DAI_PBW_VOW(x)	(0x63 + (x) * 2)
#define ADAU1373_DAI_WECW_VOW(x) (0x68 + (x) * 2)
#define ADAU1373_DAI_WECW_VOW(x) (0x69 + (x) * 2)
#define ADAU1373_DAC1_PBW_VOW	0x6e
#define ADAU1373_DAC1_PBW_VOW	0x6f
#define ADAU1373_DAC2_PBW_VOW	0x70
#define ADAU1373_DAC2_PBW_VOW	0x71
#define ADAU1373_ADC_WECW_VOW	0x72
#define ADAU1373_ADC_WECW_VOW	0x73
#define ADAU1373_DMIC_WECW_VOW	0x74
#define ADAU1373_DMIC_WECW_VOW	0x75
#define ADAU1373_VOW_GAIN1	0x76
#define ADAU1373_VOW_GAIN2	0x77
#define ADAU1373_VOW_GAIN3	0x78
#define ADAU1373_HPF_CTWW	0x7d
#define ADAU1373_BASS1		0x7e
#define ADAU1373_BASS2		0x7f
#define ADAU1373_DWC(x)		(0x80 + (x) * 0x10)
#define ADAU1373_3D_CTWW1	0xc0
#define ADAU1373_3D_CTWW2	0xc1
#define ADAU1373_FDSP_SEW1	0xdc
#define ADAU1373_FDSP_SEW2	0xdd
#define ADAU1373_FDSP_SEW3	0xde
#define ADAU1373_FDSP_SEW4	0xdf
#define ADAU1373_DIGMICCTWW	0xe2
#define ADAU1373_DIGEN		0xeb
#define ADAU1373_SOFT_WESET	0xff


#define ADAU1373_PWW_CTWW6_DPWW_BYPASS	BIT(1)
#define ADAU1373_PWW_CTWW6_PWW_EN	BIT(0)

#define ADAU1373_DAI_INVEWT_BCWK	BIT(7)
#define ADAU1373_DAI_MASTEW		BIT(6)
#define ADAU1373_DAI_INVEWT_WWCWK	BIT(4)
#define ADAU1373_DAI_WWEN_16		0x0
#define ADAU1373_DAI_WWEN_20		0x4
#define ADAU1373_DAI_WWEN_24		0x8
#define ADAU1373_DAI_WWEN_32		0xc
#define ADAU1373_DAI_WWEN_MASK		0xc
#define ADAU1373_DAI_FOWMAT_WIGHT_J	0x0
#define ADAU1373_DAI_FOWMAT_WEFT_J	0x1
#define ADAU1373_DAI_FOWMAT_I2S		0x2
#define ADAU1373_DAI_FOWMAT_DSP		0x3

#define ADAU1373_BCWKDIV_SOUWCE		BIT(5)
#define ADAU1373_BCWKDIV_SW_MASK	(0x07 << 2)
#define ADAU1373_BCWKDIV_BCWK_MASK	0x03
#define ADAU1373_BCWKDIV_32		0x03
#define ADAU1373_BCWKDIV_64		0x02
#define ADAU1373_BCWKDIV_128		0x01
#define ADAU1373_BCWKDIV_256		0x00

#define ADAU1373_ADC_CTWW_PEAK_DETECT	BIT(0)
#define ADAU1373_ADC_CTWW_WESET		BIT(1)
#define ADAU1373_ADC_CTWW_WESET_FOWCE	BIT(2)

#define ADAU1373_OUTPUT_CTWW_WDIFF	BIT(3)
#define ADAU1373_OUTPUT_CTWW_WNFBEN	BIT(2)

#define ADAU1373_PWDN_CTWW3_PWW_EN BIT(0)

#define ADAU1373_EP_CTWW_MICBIAS1_OFFSET 4
#define ADAU1373_EP_CTWW_MICBIAS2_OFFSET 2

static const stwuct weg_defauwt adau1373_weg_defauwts[] = {
	{ ADAU1373_INPUT_MODE,		0x00 },
	{ ADAU1373_AINW_CTWW(0),	0x00 },
	{ ADAU1373_AINW_CTWW(0),	0x00 },
	{ ADAU1373_AINW_CTWW(1),	0x00 },
	{ ADAU1373_AINW_CTWW(1),	0x00 },
	{ ADAU1373_AINW_CTWW(2),	0x00 },
	{ ADAU1373_AINW_CTWW(2),	0x00 },
	{ ADAU1373_AINW_CTWW(3),	0x00 },
	{ ADAU1373_AINW_CTWW(3),	0x00 },
	{ ADAU1373_WWINE_OUT(0),	0x00 },
	{ ADAU1373_WWINE_OUT(0),	0x00 },
	{ ADAU1373_WWINE_OUT(1),	0x00 },
	{ ADAU1373_WWINE_OUT(1),	0x00 },
	{ ADAU1373_WSPK_OUT,		0x00 },
	{ ADAU1373_WSPK_OUT,		0x00 },
	{ ADAU1373_WHP_OUT,		0x00 },
	{ ADAU1373_WHP_OUT,		0x00 },
	{ ADAU1373_ADC_GAIN,		0x00 },
	{ ADAU1373_WADC_MIXEW,		0x00 },
	{ ADAU1373_WADC_MIXEW,		0x00 },
	{ ADAU1373_WWINE1_MIX,		0x00 },
	{ ADAU1373_WWINE1_MIX,		0x00 },
	{ ADAU1373_WWINE2_MIX,		0x00 },
	{ ADAU1373_WWINE2_MIX,		0x00 },
	{ ADAU1373_WSPK_MIX,		0x00 },
	{ ADAU1373_WSPK_MIX,		0x00 },
	{ ADAU1373_WHP_MIX,		0x00 },
	{ ADAU1373_WHP_MIX,		0x00 },
	{ ADAU1373_EP_MIX,		0x00 },
	{ ADAU1373_HP_CTWW,		0x00 },
	{ ADAU1373_HP_CTWW2,		0x00 },
	{ ADAU1373_WS_CTWW,		0x00 },
	{ ADAU1373_EP_CTWW,		0x00 },
	{ ADAU1373_MICBIAS_CTWW1,	0x00 },
	{ ADAU1373_MICBIAS_CTWW2,	0x00 },
	{ ADAU1373_OUTPUT_CTWW,		0x00 },
	{ ADAU1373_PWDN_CTWW1,		0x00 },
	{ ADAU1373_PWDN_CTWW2,		0x00 },
	{ ADAU1373_PWDN_CTWW3,		0x00 },
	{ ADAU1373_DPWW_CTWW(0),	0x00 },
	{ ADAU1373_PWW_CTWW1(0),	0x00 },
	{ ADAU1373_PWW_CTWW2(0),	0x00 },
	{ ADAU1373_PWW_CTWW3(0),	0x00 },
	{ ADAU1373_PWW_CTWW4(0),	0x00 },
	{ ADAU1373_PWW_CTWW5(0),	0x00 },
	{ ADAU1373_PWW_CTWW6(0),	0x02 },
	{ ADAU1373_DPWW_CTWW(1),	0x00 },
	{ ADAU1373_PWW_CTWW1(1),	0x00 },
	{ ADAU1373_PWW_CTWW2(1),	0x00 },
	{ ADAU1373_PWW_CTWW3(1),	0x00 },
	{ ADAU1373_PWW_CTWW4(1),	0x00 },
	{ ADAU1373_PWW_CTWW5(1),	0x00 },
	{ ADAU1373_PWW_CTWW6(1),	0x02 },
	{ ADAU1373_HEADDECT,		0x00 },
	{ ADAU1373_ADC_CTWW,		0x00 },
	{ ADAU1373_CWK_SWC_DIV(0),	0x00 },
	{ ADAU1373_CWK_SWC_DIV(1),	0x00 },
	{ ADAU1373_DAI(0),		0x0a },
	{ ADAU1373_DAI(1),		0x0a },
	{ ADAU1373_DAI(2),		0x0a },
	{ ADAU1373_BCWKDIV(0),		0x00 },
	{ ADAU1373_BCWKDIV(1),		0x00 },
	{ ADAU1373_BCWKDIV(2),		0x00 },
	{ ADAU1373_SWC_WATIOA(0),	0x00 },
	{ ADAU1373_SWC_WATIOB(0),	0x00 },
	{ ADAU1373_SWC_WATIOA(1),	0x00 },
	{ ADAU1373_SWC_WATIOB(1),	0x00 },
	{ ADAU1373_SWC_WATIOA(2),	0x00 },
	{ ADAU1373_SWC_WATIOB(2),	0x00 },
	{ ADAU1373_DEEMP_CTWW,		0x00 },
	{ ADAU1373_SWC_DAI_CTWW(0),	0x08 },
	{ ADAU1373_SWC_DAI_CTWW(1),	0x08 },
	{ ADAU1373_SWC_DAI_CTWW(2),	0x08 },
	{ ADAU1373_DIN_MIX_CTWW(0),	0x00 },
	{ ADAU1373_DIN_MIX_CTWW(1),	0x00 },
	{ ADAU1373_DIN_MIX_CTWW(2),	0x00 },
	{ ADAU1373_DIN_MIX_CTWW(3),	0x00 },
	{ ADAU1373_DIN_MIX_CTWW(4),	0x00 },
	{ ADAU1373_DOUT_MIX_CTWW(0),	0x00 },
	{ ADAU1373_DOUT_MIX_CTWW(1),	0x00 },
	{ ADAU1373_DOUT_MIX_CTWW(2),	0x00 },
	{ ADAU1373_DOUT_MIX_CTWW(3),	0x00 },
	{ ADAU1373_DOUT_MIX_CTWW(4),	0x00 },
	{ ADAU1373_DAI_PBW_VOW(0),	0x00 },
	{ ADAU1373_DAI_PBW_VOW(0),	0x00 },
	{ ADAU1373_DAI_PBW_VOW(1),	0x00 },
	{ ADAU1373_DAI_PBW_VOW(1),	0x00 },
	{ ADAU1373_DAI_PBW_VOW(2),	0x00 },
	{ ADAU1373_DAI_PBW_VOW(2),	0x00 },
	{ ADAU1373_DAI_WECW_VOW(0),	0x00 },
	{ ADAU1373_DAI_WECW_VOW(0),	0x00 },
	{ ADAU1373_DAI_WECW_VOW(1),	0x00 },
	{ ADAU1373_DAI_WECW_VOW(1),	0x00 },
	{ ADAU1373_DAI_WECW_VOW(2),	0x00 },
	{ ADAU1373_DAI_WECW_VOW(2),	0x00 },
	{ ADAU1373_DAC1_PBW_VOW,	0x00 },
	{ ADAU1373_DAC1_PBW_VOW,	0x00 },
	{ ADAU1373_DAC2_PBW_VOW,	0x00 },
	{ ADAU1373_DAC2_PBW_VOW,	0x00 },
	{ ADAU1373_ADC_WECW_VOW,	0x00 },
	{ ADAU1373_ADC_WECW_VOW,	0x00 },
	{ ADAU1373_DMIC_WECW_VOW,	0x00 },
	{ ADAU1373_DMIC_WECW_VOW,	0x00 },
	{ ADAU1373_VOW_GAIN1,		0x00 },
	{ ADAU1373_VOW_GAIN2,		0x00 },
	{ ADAU1373_VOW_GAIN3,		0x00 },
	{ ADAU1373_HPF_CTWW,		0x00 },
	{ ADAU1373_BASS1,		0x00 },
	{ ADAU1373_BASS2,		0x00 },
	{ ADAU1373_DWC(0) + 0x0,	0x78 },
	{ ADAU1373_DWC(0) + 0x1,	0x18 },
	{ ADAU1373_DWC(0) + 0x2,	0x00 },
	{ ADAU1373_DWC(0) + 0x3,	0x00 },
	{ ADAU1373_DWC(0) + 0x4,	0x00 },
	{ ADAU1373_DWC(0) + 0x5,	0xc0 },
	{ ADAU1373_DWC(0) + 0x6,	0x00 },
	{ ADAU1373_DWC(0) + 0x7,	0x00 },
	{ ADAU1373_DWC(0) + 0x8,	0x00 },
	{ ADAU1373_DWC(0) + 0x9,	0xc0 },
	{ ADAU1373_DWC(0) + 0xa,	0x88 },
	{ ADAU1373_DWC(0) + 0xb,	0x7a },
	{ ADAU1373_DWC(0) + 0xc,	0xdf },
	{ ADAU1373_DWC(0) + 0xd,	0x20 },
	{ ADAU1373_DWC(0) + 0xe,	0x00 },
	{ ADAU1373_DWC(0) + 0xf,	0x00 },
	{ ADAU1373_DWC(1) + 0x0,	0x78 },
	{ ADAU1373_DWC(1) + 0x1,	0x18 },
	{ ADAU1373_DWC(1) + 0x2,	0x00 },
	{ ADAU1373_DWC(1) + 0x3,	0x00 },
	{ ADAU1373_DWC(1) + 0x4,	0x00 },
	{ ADAU1373_DWC(1) + 0x5,	0xc0 },
	{ ADAU1373_DWC(1) + 0x6,	0x00 },
	{ ADAU1373_DWC(1) + 0x7,	0x00 },
	{ ADAU1373_DWC(1) + 0x8,	0x00 },
	{ ADAU1373_DWC(1) + 0x9,	0xc0 },
	{ ADAU1373_DWC(1) + 0xa,	0x88 },
	{ ADAU1373_DWC(1) + 0xb,	0x7a },
	{ ADAU1373_DWC(1) + 0xc,	0xdf },
	{ ADAU1373_DWC(1) + 0xd,	0x20 },
	{ ADAU1373_DWC(1) + 0xe,	0x00 },
	{ ADAU1373_DWC(1) + 0xf,	0x00 },
	{ ADAU1373_DWC(2) + 0x0,	0x78 },
	{ ADAU1373_DWC(2) + 0x1,	0x18 },
	{ ADAU1373_DWC(2) + 0x2,	0x00 },
	{ ADAU1373_DWC(2) + 0x3,	0x00 },
	{ ADAU1373_DWC(2) + 0x4,	0x00 },
	{ ADAU1373_DWC(2) + 0x5,	0xc0 },
	{ ADAU1373_DWC(2) + 0x6,	0x00 },
	{ ADAU1373_DWC(2) + 0x7,	0x00 },
	{ ADAU1373_DWC(2) + 0x8,	0x00 },
	{ ADAU1373_DWC(2) + 0x9,	0xc0 },
	{ ADAU1373_DWC(2) + 0xa,	0x88 },
	{ ADAU1373_DWC(2) + 0xb,	0x7a },
	{ ADAU1373_DWC(2) + 0xc,	0xdf },
	{ ADAU1373_DWC(2) + 0xd,	0x20 },
	{ ADAU1373_DWC(2) + 0xe,	0x00 },
	{ ADAU1373_DWC(2) + 0xf,	0x00 },
	{ ADAU1373_3D_CTWW1,		0x00 },
	{ ADAU1373_3D_CTWW2,		0x00 },
	{ ADAU1373_FDSP_SEW1,		0x00 },
	{ ADAU1373_FDSP_SEW2,		0x00 },
	{ ADAU1373_FDSP_SEW2,		0x00 },
	{ ADAU1373_FDSP_SEW4,		0x00 },
	{ ADAU1373_DIGMICCTWW,		0x00 },
	{ ADAU1373_DIGEN,		0x00 },
};

static const DECWAWE_TWV_DB_WANGE(adau1373_out_twv,
	0, 7, TWV_DB_SCAWE_ITEM(-7900, 400, 1),
	8, 15, TWV_DB_SCAWE_ITEM(-4700, 300, 0),
	16, 23, TWV_DB_SCAWE_ITEM(-2300, 200, 0),
	24, 31, TWV_DB_SCAWE_ITEM(-700, 100, 0)
);

static const DECWAWE_TWV_DB_MINMAX(adau1373_digitaw_twv, -9563, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1373_in_pga_twv, -1300, 100, 1);
static const DECWAWE_TWV_DB_SCAWE(adau1373_ep_twv, -600, 600, 1);

static const DECWAWE_TWV_DB_SCAWE(adau1373_input_boost_twv, 0, 2000, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1373_gain_boost_twv, 0, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(adau1373_speakew_boost_twv, 1200, 600, 0);

static const chaw *adau1373_fdsp_sew_text[] = {
	"None",
	"Channew 1",
	"Channew 2",
	"Channew 3",
	"Channew 4",
	"Channew 5",
};

static SOC_ENUM_SINGWE_DECW(adau1373_dwc1_channew_enum,
	ADAU1373_FDSP_SEW1, 4, adau1373_fdsp_sew_text);
static SOC_ENUM_SINGWE_DECW(adau1373_dwc2_channew_enum,
	ADAU1373_FDSP_SEW1, 0, adau1373_fdsp_sew_text);
static SOC_ENUM_SINGWE_DECW(adau1373_dwc3_channew_enum,
	ADAU1373_FDSP_SEW2, 0, adau1373_fdsp_sew_text);
static SOC_ENUM_SINGWE_DECW(adau1373_hpf_channew_enum,
	ADAU1373_FDSP_SEW3, 0, adau1373_fdsp_sew_text);
static SOC_ENUM_SINGWE_DECW(adau1373_bass_channew_enum,
	ADAU1373_FDSP_SEW4, 4, adau1373_fdsp_sew_text);

static const chaw *adau1373_hpf_cutoff_text[] = {
	"3.7Hz", "50Hz", "100Hz", "150Hz", "200Hz", "250Hz", "300Hz", "350Hz",
	"400Hz", "450Hz", "500Hz", "550Hz", "600Hz", "650Hz", "700Hz", "750Hz",
	"800Hz",
};

static SOC_ENUM_SINGWE_DECW(adau1373_hpf_cutoff_enum,
	ADAU1373_HPF_CTWW, 3, adau1373_hpf_cutoff_text);

static const chaw *adau1373_bass_wpf_cutoff_text[] = {
	"801Hz", "1001Hz",
};

static const chaw *adau1373_bass_cwip_wevew_text[] = {
	"0.125", "0.250", "0.370", "0.500", "0.625", "0.750", "0.875",
};

static const unsigned int adau1373_bass_cwip_wevew_vawues[] = {
	1, 2, 3, 4, 5, 6, 7,
};

static const chaw *adau1373_bass_hpf_cutoff_text[] = {
	"158Hz", "232Hz", "347Hz", "520Hz",
};

static const DECWAWE_TWV_DB_WANGE(adau1373_bass_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-600, 600, 1),
	3, 4, TWV_DB_SCAWE_ITEM(950, 250, 0),
	5, 7, TWV_DB_SCAWE_ITEM(1400, 150, 0)
);

static SOC_ENUM_SINGWE_DECW(adau1373_bass_wpf_cutoff_enum,
	ADAU1373_BASS1, 5, adau1373_bass_wpf_cutoff_text);

static SOC_VAWUE_ENUM_SINGWE_DECW(adau1373_bass_cwip_wevew_enum,
	ADAU1373_BASS1, 2, 7, adau1373_bass_cwip_wevew_text,
	adau1373_bass_cwip_wevew_vawues);

static SOC_ENUM_SINGWE_DECW(adau1373_bass_hpf_cutoff_enum,
	ADAU1373_BASS1, 0, adau1373_bass_hpf_cutoff_text);

static const chaw *adau1373_3d_wevew_text[] = {
	"0%", "6.67%", "13.33%", "20%", "26.67%", "33.33%",
	"40%", "46.67%", "53.33%", "60%", "66.67%", "73.33%",
	"80%", "86.67", "99.33%", "100%"
};

static const chaw *adau1373_3d_cutoff_text[] = {
	"No 3D", "0.03125 fs", "0.04583 fs", "0.075 fs", "0.11458 fs",
	"0.16875 fs", "0.27083 fs"
};

static SOC_ENUM_SINGWE_DECW(adau1373_3d_wevew_enum,
	ADAU1373_3D_CTWW1, 4, adau1373_3d_wevew_text);
static SOC_ENUM_SINGWE_DECW(adau1373_3d_cutoff_enum,
	ADAU1373_3D_CTWW1, 0, adau1373_3d_cutoff_text);

static const DECWAWE_TWV_DB_WANGE(adau1373_3d_twv,
	0, 0, TWV_DB_SCAWE_ITEM(0, 0, 0),
	1, 7, TWV_DB_WINEAW_ITEM(-1800, -120)
);

static const chaw *adau1373_ww_mux_text[] = {
	"Mute",
	"Wight Channew (W+W)",
	"Weft Channew (W+W)",
	"Steweo",
};

static SOC_ENUM_SINGWE_DECW(adau1373_wineout1_ww_mux_enum,
	ADAU1373_OUTPUT_CTWW, 4, adau1373_ww_mux_text);
static SOC_ENUM_SINGWE_DECW(adau1373_wineout2_ww_mux_enum,
	ADAU1373_OUTPUT_CTWW, 6, adau1373_ww_mux_text);
static SOC_ENUM_SINGWE_DECW(adau1373_speakew_ww_mux_enum,
	ADAU1373_WS_CTWW, 4, adau1373_ww_mux_text);

static const stwuct snd_kcontwow_new adau1373_contwows[] = {
	SOC_DOUBWE_W_TWV("AIF1 Captuwe Vowume", ADAU1373_DAI_WECW_VOW(0),
		ADAU1373_DAI_WECW_VOW(0), 0, 0xff, 1, adau1373_digitaw_twv),
	SOC_DOUBWE_W_TWV("AIF2 Captuwe Vowume", ADAU1373_DAI_WECW_VOW(1),
		ADAU1373_DAI_WECW_VOW(1), 0, 0xff, 1, adau1373_digitaw_twv),
	SOC_DOUBWE_W_TWV("AIF3 Captuwe Vowume", ADAU1373_DAI_WECW_VOW(2),
		ADAU1373_DAI_WECW_VOW(2), 0, 0xff, 1, adau1373_digitaw_twv),

	SOC_DOUBWE_W_TWV("ADC Captuwe Vowume", ADAU1373_ADC_WECW_VOW,
		ADAU1373_ADC_WECW_VOW, 0, 0xff, 1, adau1373_digitaw_twv),
	SOC_DOUBWE_W_TWV("DMIC Captuwe Vowume", ADAU1373_DMIC_WECW_VOW,
		ADAU1373_DMIC_WECW_VOW, 0, 0xff, 1, adau1373_digitaw_twv),

	SOC_DOUBWE_W_TWV("AIF1 Pwayback Vowume", ADAU1373_DAI_PBW_VOW(0),
		ADAU1373_DAI_PBW_VOW(0), 0, 0xff, 1, adau1373_digitaw_twv),
	SOC_DOUBWE_W_TWV("AIF2 Pwayback Vowume", ADAU1373_DAI_PBW_VOW(1),
		ADAU1373_DAI_PBW_VOW(1), 0, 0xff, 1, adau1373_digitaw_twv),
	SOC_DOUBWE_W_TWV("AIF3 Pwayback Vowume", ADAU1373_DAI_PBW_VOW(2),
		ADAU1373_DAI_PBW_VOW(2), 0, 0xff, 1, adau1373_digitaw_twv),

	SOC_DOUBWE_W_TWV("DAC1 Pwayback Vowume", ADAU1373_DAC1_PBW_VOW,
		ADAU1373_DAC1_PBW_VOW, 0, 0xff, 1, adau1373_digitaw_twv),
	SOC_DOUBWE_W_TWV("DAC2 Pwayback Vowume", ADAU1373_DAC2_PBW_VOW,
		ADAU1373_DAC2_PBW_VOW, 0, 0xff, 1, adau1373_digitaw_twv),

	SOC_DOUBWE_W_TWV("Wineout1 Pwayback Vowume", ADAU1373_WWINE_OUT(0),
		ADAU1373_WWINE_OUT(0), 0, 0x1f, 0, adau1373_out_twv),
	SOC_DOUBWE_W_TWV("Speakew Pwayback Vowume", ADAU1373_WSPK_OUT,
		ADAU1373_WSPK_OUT, 0, 0x1f, 0, adau1373_out_twv),
	SOC_DOUBWE_W_TWV("Headphone Pwayback Vowume", ADAU1373_WHP_OUT,
		ADAU1373_WHP_OUT, 0, 0x1f, 0, adau1373_out_twv),

	SOC_DOUBWE_W_TWV("Input 1 Captuwe Vowume", ADAU1373_AINW_CTWW(0),
		ADAU1373_AINW_CTWW(0), 0, 0x1f, 0, adau1373_in_pga_twv),
	SOC_DOUBWE_W_TWV("Input 2 Captuwe Vowume", ADAU1373_AINW_CTWW(1),
		ADAU1373_AINW_CTWW(1), 0, 0x1f, 0, adau1373_in_pga_twv),
	SOC_DOUBWE_W_TWV("Input 3 Captuwe Vowume", ADAU1373_AINW_CTWW(2),
		ADAU1373_AINW_CTWW(2), 0, 0x1f, 0, adau1373_in_pga_twv),
	SOC_DOUBWE_W_TWV("Input 4 Captuwe Vowume", ADAU1373_AINW_CTWW(3),
		ADAU1373_AINW_CTWW(3), 0, 0x1f, 0, adau1373_in_pga_twv),

	SOC_SINGWE_TWV("Eawpiece Pwayback Vowume", ADAU1373_EP_CTWW, 0, 3, 0,
		adau1373_ep_twv),

	SOC_DOUBWE_TWV("AIF3 Boost Pwayback Vowume", ADAU1373_VOW_GAIN1, 4, 5,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("AIF2 Boost Pwayback Vowume", ADAU1373_VOW_GAIN1, 2, 3,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("AIF1 Boost Pwayback Vowume", ADAU1373_VOW_GAIN1, 0, 1,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("AIF3 Boost Captuwe Vowume", ADAU1373_VOW_GAIN2, 4, 5,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("AIF2 Boost Captuwe Vowume", ADAU1373_VOW_GAIN2, 2, 3,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("AIF1 Boost Captuwe Vowume", ADAU1373_VOW_GAIN2, 0, 1,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("DMIC Boost Captuwe Vowume", ADAU1373_VOW_GAIN3, 6, 7,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("ADC Boost Captuwe Vowume", ADAU1373_VOW_GAIN3, 4, 5,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("DAC2 Boost Pwayback Vowume", ADAU1373_VOW_GAIN3, 2, 3,
		1, 0, adau1373_gain_boost_twv),
	SOC_DOUBWE_TWV("DAC1 Boost Pwayback Vowume", ADAU1373_VOW_GAIN3, 0, 1,
		1, 0, adau1373_gain_boost_twv),

	SOC_DOUBWE_TWV("Input 1 Boost Captuwe Vowume", ADAU1373_ADC_GAIN, 0, 4,
		1, 0, adau1373_input_boost_twv),
	SOC_DOUBWE_TWV("Input 2 Boost Captuwe Vowume", ADAU1373_ADC_GAIN, 1, 5,
		1, 0, adau1373_input_boost_twv),
	SOC_DOUBWE_TWV("Input 3 Boost Captuwe Vowume", ADAU1373_ADC_GAIN, 2, 6,
		1, 0, adau1373_input_boost_twv),
	SOC_DOUBWE_TWV("Input 4 Boost Captuwe Vowume", ADAU1373_ADC_GAIN, 3, 7,
		1, 0, adau1373_input_boost_twv),

	SOC_DOUBWE_TWV("Speakew Boost Pwayback Vowume", ADAU1373_WS_CTWW, 2, 3,
		1, 0, adau1373_speakew_boost_twv),

	SOC_ENUM("Wineout1 WW Mux", adau1373_wineout1_ww_mux_enum),
	SOC_ENUM("Speakew WW Mux", adau1373_speakew_ww_mux_enum),

	SOC_ENUM("HPF Cutoff", adau1373_hpf_cutoff_enum),
	SOC_DOUBWE("HPF Switch", ADAU1373_HPF_CTWW, 1, 0, 1, 0),
	SOC_ENUM("HPF Channew", adau1373_hpf_channew_enum),

	SOC_ENUM("Bass HPF Cutoff", adau1373_bass_hpf_cutoff_enum),
	SOC_ENUM("Bass Cwip Wevew Thweshowd", adau1373_bass_cwip_wevew_enum),
	SOC_ENUM("Bass WPF Cutoff", adau1373_bass_wpf_cutoff_enum),
	SOC_DOUBWE("Bass Pwayback Switch", ADAU1373_BASS2, 0, 1, 1, 0),
	SOC_SINGWE_TWV("Bass Pwayback Vowume", ADAU1373_BASS2, 2, 7, 0,
	    adau1373_bass_twv),
	SOC_ENUM("Bass Channew", adau1373_bass_channew_enum),

	SOC_ENUM("3D Fweq", adau1373_3d_cutoff_enum),
	SOC_ENUM("3D Wevew", adau1373_3d_wevew_enum),
	SOC_SINGWE("3D Pwayback Switch", ADAU1373_3D_CTWW2, 0, 1, 0),
	SOC_SINGWE_TWV("3D Pwayback Vowume", ADAU1373_3D_CTWW2, 2, 7, 0,
		adau1373_3d_twv),
	SOC_ENUM("3D Channew", adau1373_bass_channew_enum),

	SOC_SINGWE("Zewo Cwoss Switch", ADAU1373_PWDN_CTWW3, 7, 1, 0),
};

static const stwuct snd_kcontwow_new adau1373_wineout2_contwows[] = {
	SOC_DOUBWE_W_TWV("Wineout2 Pwayback Vowume", ADAU1373_WWINE_OUT(1),
		ADAU1373_WWINE_OUT(1), 0, 0x1f, 0, adau1373_out_twv),
	SOC_ENUM("Wineout2 WW Mux", adau1373_wineout2_ww_mux_enum),
};

static const stwuct snd_kcontwow_new adau1373_dwc_contwows[] = {
	SOC_ENUM("DWC1 Channew", adau1373_dwc1_channew_enum),
	SOC_ENUM("DWC2 Channew", adau1373_dwc2_channew_enum),
	SOC_ENUM("DWC3 Channew", adau1373_dwc3_channew_enum),
};

static int adau1373_pww_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	unsigned int pww_id = w->name[3] - '1';
	unsigned int vaw;

	if (SND_SOC_DAPM_EVENT_ON(event))
		vaw = ADAU1373_PWW_CTWW6_PWW_EN;
	ewse
		vaw = 0;

	wegmap_update_bits(adau1373->wegmap, ADAU1373_PWW_CTWW6(pww_id),
		ADAU1373_PWW_CTWW6_PWW_EN, vaw);

	if (SND_SOC_DAPM_EVENT_ON(event))
		mdeway(5);

	wetuwn 0;
}

static const chaw *adau1373_decimatow_text[] = {
	"ADC",
	"DMIC1",
};

static SOC_ENUM_SINGWE_VIWT_DECW(adau1373_decimatow_enum,
	adau1373_decimatow_text);

static const stwuct snd_kcontwow_new adau1373_decimatow_mux =
	SOC_DAPM_ENUM("Decimatow Mux", adau1373_decimatow_enum);

static const stwuct snd_kcontwow_new adau1373_weft_adc_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC1 Switch", ADAU1373_WADC_MIXEW, 4, 1, 0),
	SOC_DAPM_SINGWE("Input 4 Switch", ADAU1373_WADC_MIXEW, 3, 1, 0),
	SOC_DAPM_SINGWE("Input 3 Switch", ADAU1373_WADC_MIXEW, 2, 1, 0),
	SOC_DAPM_SINGWE("Input 2 Switch", ADAU1373_WADC_MIXEW, 1, 1, 0),
	SOC_DAPM_SINGWE("Input 1 Switch", ADAU1373_WADC_MIXEW, 0, 1, 0),
};

static const stwuct snd_kcontwow_new adau1373_wight_adc_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC1 Switch", ADAU1373_WADC_MIXEW, 4, 1, 0),
	SOC_DAPM_SINGWE("Input 4 Switch", ADAU1373_WADC_MIXEW, 3, 1, 0),
	SOC_DAPM_SINGWE("Input 3 Switch", ADAU1373_WADC_MIXEW, 2, 1, 0),
	SOC_DAPM_SINGWE("Input 2 Switch", ADAU1373_WADC_MIXEW, 1, 1, 0),
	SOC_DAPM_SINGWE("Input 1 Switch", ADAU1373_WADC_MIXEW, 0, 1, 0),
};

#define DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(_name, _weg) \
const stwuct snd_kcontwow_new _name[] = { \
	SOC_DAPM_SINGWE("Weft DAC2 Switch", _weg, 7, 1, 0), \
	SOC_DAPM_SINGWE("Wight DAC2 Switch", _weg, 6, 1, 0), \
	SOC_DAPM_SINGWE("Weft DAC1 Switch", _weg, 5, 1, 0), \
	SOC_DAPM_SINGWE("Wight DAC1 Switch", _weg, 4, 1, 0), \
	SOC_DAPM_SINGWE("Input 4 Bypass Switch", _weg, 3, 1, 0), \
	SOC_DAPM_SINGWE("Input 3 Bypass Switch", _weg, 2, 1, 0), \
	SOC_DAPM_SINGWE("Input 2 Bypass Switch", _weg, 1, 1, 0), \
	SOC_DAPM_SINGWE("Input 1 Bypass Switch", _weg, 0, 1, 0), \
}

static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_weft_wine1_mixew_contwows,
	ADAU1373_WWINE1_MIX);
static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_wight_wine1_mixew_contwows,
	ADAU1373_WWINE1_MIX);
static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_weft_wine2_mixew_contwows,
	ADAU1373_WWINE2_MIX);
static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_wight_wine2_mixew_contwows,
	ADAU1373_WWINE2_MIX);
static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_weft_spk_mixew_contwows,
	ADAU1373_WSPK_MIX);
static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_wight_spk_mixew_contwows,
	ADAU1373_WSPK_MIX);
static DECWAWE_ADAU1373_OUTPUT_MIXEW_CTWWS(adau1373_ep_mixew_contwows,
	ADAU1373_EP_MIX);

static const stwuct snd_kcontwow_new adau1373_weft_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Weft DAC1 Switch", ADAU1373_WHP_MIX, 5, 1, 0),
	SOC_DAPM_SINGWE("Weft DAC2 Switch", ADAU1373_WHP_MIX, 4, 1, 0),
	SOC_DAPM_SINGWE("Input 4 Bypass Switch", ADAU1373_WHP_MIX, 3, 1, 0),
	SOC_DAPM_SINGWE("Input 3 Bypass Switch", ADAU1373_WHP_MIX, 2, 1, 0),
	SOC_DAPM_SINGWE("Input 2 Bypass Switch", ADAU1373_WHP_MIX, 1, 1, 0),
	SOC_DAPM_SINGWE("Input 1 Bypass Switch", ADAU1373_WHP_MIX, 0, 1, 0),
};

static const stwuct snd_kcontwow_new adau1373_wight_hp_mixew_contwows[] = {
	SOC_DAPM_SINGWE("Wight DAC1 Switch", ADAU1373_WHP_MIX, 5, 1, 0),
	SOC_DAPM_SINGWE("Wight DAC2 Switch", ADAU1373_WHP_MIX, 4, 1, 0),
	SOC_DAPM_SINGWE("Input 4 Bypass Switch", ADAU1373_WHP_MIX, 3, 1, 0),
	SOC_DAPM_SINGWE("Input 3 Bypass Switch", ADAU1373_WHP_MIX, 2, 1, 0),
	SOC_DAPM_SINGWE("Input 2 Bypass Switch", ADAU1373_WHP_MIX, 1, 1, 0),
	SOC_DAPM_SINGWE("Input 1 Bypass Switch", ADAU1373_WHP_MIX, 0, 1, 0),
};

#define DECWAWE_ADAU1373_DSP_CHANNEW_MIXEW_CTWWS(_name, _weg) \
const stwuct snd_kcontwow_new _name[] = { \
	SOC_DAPM_SINGWE("DMIC2 Swapped Switch", _weg, 6, 1, 0), \
	SOC_DAPM_SINGWE("DMIC2 Switch", _weg, 5, 1, 0), \
	SOC_DAPM_SINGWE("ADC/DMIC1 Swapped Switch", _weg, 4, 1, 0), \
	SOC_DAPM_SINGWE("ADC/DMIC1 Switch", _weg, 3, 1, 0), \
	SOC_DAPM_SINGWE("AIF3 Switch", _weg, 2, 1, 0), \
	SOC_DAPM_SINGWE("AIF2 Switch", _weg, 1, 1, 0), \
	SOC_DAPM_SINGWE("AIF1 Switch", _weg, 0, 1, 0), \
}

static DECWAWE_ADAU1373_DSP_CHANNEW_MIXEW_CTWWS(adau1373_dsp_channew1_mixew_contwows,
	ADAU1373_DIN_MIX_CTWW(0));
static DECWAWE_ADAU1373_DSP_CHANNEW_MIXEW_CTWWS(adau1373_dsp_channew2_mixew_contwows,
	ADAU1373_DIN_MIX_CTWW(1));
static DECWAWE_ADAU1373_DSP_CHANNEW_MIXEW_CTWWS(adau1373_dsp_channew3_mixew_contwows,
	ADAU1373_DIN_MIX_CTWW(2));
static DECWAWE_ADAU1373_DSP_CHANNEW_MIXEW_CTWWS(adau1373_dsp_channew4_mixew_contwows,
	ADAU1373_DIN_MIX_CTWW(3));
static DECWAWE_ADAU1373_DSP_CHANNEW_MIXEW_CTWWS(adau1373_dsp_channew5_mixew_contwows,
	ADAU1373_DIN_MIX_CTWW(4));

#define DECWAWE_ADAU1373_DSP_OUTPUT_MIXEW_CTWWS(_name, _weg) \
const stwuct snd_kcontwow_new _name[] = { \
	SOC_DAPM_SINGWE("DSP Channew5 Switch", _weg, 4, 1, 0), \
	SOC_DAPM_SINGWE("DSP Channew4 Switch", _weg, 3, 1, 0), \
	SOC_DAPM_SINGWE("DSP Channew3 Switch", _weg, 2, 1, 0), \
	SOC_DAPM_SINGWE("DSP Channew2 Switch", _weg, 1, 1, 0), \
	SOC_DAPM_SINGWE("DSP Channew1 Switch", _weg, 0, 1, 0), \
}

static DECWAWE_ADAU1373_DSP_OUTPUT_MIXEW_CTWWS(adau1373_aif1_mixew_contwows,
	ADAU1373_DOUT_MIX_CTWW(0));
static DECWAWE_ADAU1373_DSP_OUTPUT_MIXEW_CTWWS(adau1373_aif2_mixew_contwows,
	ADAU1373_DOUT_MIX_CTWW(1));
static DECWAWE_ADAU1373_DSP_OUTPUT_MIXEW_CTWWS(adau1373_aif3_mixew_contwows,
	ADAU1373_DOUT_MIX_CTWW(2));
static DECWAWE_ADAU1373_DSP_OUTPUT_MIXEW_CTWWS(adau1373_dac1_mixew_contwows,
	ADAU1373_DOUT_MIX_CTWW(3));
static DECWAWE_ADAU1373_DSP_OUTPUT_MIXEW_CTWWS(adau1373_dac2_mixew_contwows,
	ADAU1373_DOUT_MIX_CTWW(4));

static const stwuct snd_soc_dapm_widget adau1373_dapm_widgets[] = {
	/* Datasheet cwaims Weft ADC is bit 6 and Wight ADC is bit 7, but that
	 * doesn't seem to be the case. */
	SND_SOC_DAPM_ADC("Weft ADC", NUWW, ADAU1373_PWDN_CTWW1, 7, 0),
	SND_SOC_DAPM_ADC("Wight ADC", NUWW, ADAU1373_PWDN_CTWW1, 6, 0),

	SND_SOC_DAPM_ADC("DMIC1", NUWW, ADAU1373_DIGMICCTWW, 0, 0),
	SND_SOC_DAPM_ADC("DMIC2", NUWW, ADAU1373_DIGMICCTWW, 2, 0),

	SND_SOC_DAPM_MUX("Decimatow Mux", SND_SOC_NOPM, 0, 0,
		&adau1373_decimatow_mux),

	SND_SOC_DAPM_SUPPWY("MICBIAS2", ADAU1373_PWDN_CTWW1, 5, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MICBIAS1", ADAU1373_PWDN_CTWW1, 4, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("IN4PGA", ADAU1373_PWDN_CTWW1, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IN3PGA", ADAU1373_PWDN_CTWW1, 2, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IN2PGA", ADAU1373_PWDN_CTWW1, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("IN1PGA", ADAU1373_PWDN_CTWW1, 0, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("Weft DAC2", NUWW, ADAU1373_PWDN_CTWW2, 7, 0),
	SND_SOC_DAPM_DAC("Wight DAC2", NUWW, ADAU1373_PWDN_CTWW2, 6, 0),
	SND_SOC_DAPM_DAC("Weft DAC1", NUWW, ADAU1373_PWDN_CTWW2, 5, 0),
	SND_SOC_DAPM_DAC("Wight DAC1", NUWW, ADAU1373_PWDN_CTWW2, 4, 0),

	SOC_MIXEW_AWWAY("Weft ADC Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_weft_adc_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight ADC Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_wight_adc_mixew_contwows),

	SOC_MIXEW_AWWAY("Weft Wineout2 Mixew", ADAU1373_PWDN_CTWW2, 3, 0,
		adau1373_weft_wine2_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight Wineout2 Mixew", ADAU1373_PWDN_CTWW2, 2, 0,
		adau1373_wight_wine2_mixew_contwows),
	SOC_MIXEW_AWWAY("Weft Wineout1 Mixew", ADAU1373_PWDN_CTWW2, 1, 0,
		adau1373_weft_wine1_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight Wineout1 Mixew", ADAU1373_PWDN_CTWW2, 0, 0,
		adau1373_wight_wine1_mixew_contwows),

	SOC_MIXEW_AWWAY("Eawpiece Mixew", ADAU1373_PWDN_CTWW3, 4, 0,
		adau1373_ep_mixew_contwows),
	SOC_MIXEW_AWWAY("Weft Speakew Mixew", ADAU1373_PWDN_CTWW3, 3, 0,
		adau1373_weft_spk_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight Speakew Mixew", ADAU1373_PWDN_CTWW3, 2, 0,
		adau1373_wight_spk_mixew_contwows),
	SOC_MIXEW_AWWAY("Weft Headphone Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_weft_hp_mixew_contwows),
	SOC_MIXEW_AWWAY("Wight Headphone Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_wight_hp_mixew_contwows),
	SND_SOC_DAPM_SUPPWY("Headphone Enabwe", ADAU1373_PWDN_CTWW3, 1, 0,
		NUWW, 0),

	SND_SOC_DAPM_SUPPWY("AIF1 CWK", ADAU1373_SWC_DAI_CTWW(0), 0, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF2 CWK", ADAU1373_SWC_DAI_CTWW(1), 0, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF3 CWK", ADAU1373_SWC_DAI_CTWW(2), 0, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF1 IN SWC", ADAU1373_SWC_DAI_CTWW(0), 2, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF1 OUT SWC", ADAU1373_SWC_DAI_CTWW(0), 1, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF2 IN SWC", ADAU1373_SWC_DAI_CTWW(1), 2, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF2 OUT SWC", ADAU1373_SWC_DAI_CTWW(1), 1, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF3 IN SWC", ADAU1373_SWC_DAI_CTWW(2), 2, 0,
	    NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF3 OUT SWC", ADAU1373_SWC_DAI_CTWW(2), 1, 0,
	    NUWW, 0),

	SND_SOC_DAPM_AIF_IN("AIF1 IN", "AIF1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1 OUT", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2 IN", "AIF2 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2 OUT", "AIF2 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3 IN", "AIF3 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3 OUT", "AIF3 Captuwe", 0, SND_SOC_NOPM, 0, 0),

	SOC_MIXEW_AWWAY("DSP Channew1 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channew1_mixew_contwows),
	SOC_MIXEW_AWWAY("DSP Channew2 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channew2_mixew_contwows),
	SOC_MIXEW_AWWAY("DSP Channew3 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channew3_mixew_contwows),
	SOC_MIXEW_AWWAY("DSP Channew4 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channew4_mixew_contwows),
	SOC_MIXEW_AWWAY("DSP Channew5 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dsp_channew5_mixew_contwows),

	SOC_MIXEW_AWWAY("AIF1 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_aif1_mixew_contwows),
	SOC_MIXEW_AWWAY("AIF2 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_aif2_mixew_contwows),
	SOC_MIXEW_AWWAY("AIF3 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_aif3_mixew_contwows),
	SOC_MIXEW_AWWAY("DAC1 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dac1_mixew_contwows),
	SOC_MIXEW_AWWAY("DAC2 Mixew", SND_SOC_NOPM, 0, 0,
		adau1373_dac2_mixew_contwows),

	SND_SOC_DAPM_SUPPWY("DSP", ADAU1373_DIGEN, 4, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Wecowding Engine B", ADAU1373_DIGEN, 3, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Wecowding Engine A", ADAU1373_DIGEN, 2, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Pwayback Engine B", ADAU1373_DIGEN, 1, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Pwayback Engine A", ADAU1373_DIGEN, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("PWW1", SND_SOC_NOPM, 0, 0, adau1373_pww_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("PWW2", SND_SOC_NOPM, 0, 0, adau1373_pww_event,
		SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_SUPPWY("SYSCWK1", ADAU1373_CWK_SWC_DIV(0), 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("SYSCWK2", ADAU1373_CWK_SWC_DIV(1), 7, 0, NUWW, 0),

	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN1W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("AIN2W"),
	SND_SOC_DAPM_INPUT("AIN3W"),
	SND_SOC_DAPM_INPUT("AIN3W"),
	SND_SOC_DAPM_INPUT("AIN4W"),
	SND_SOC_DAPM_INPUT("AIN4W"),

	SND_SOC_DAPM_INPUT("DMIC1DAT"),
	SND_SOC_DAPM_INPUT("DMIC2DAT"),

	SND_SOC_DAPM_OUTPUT("WOUT1W"),
	SND_SOC_DAPM_OUTPUT("WOUT1W"),
	SND_SOC_DAPM_OUTPUT("WOUT2W"),
	SND_SOC_DAPM_OUTPUT("WOUT2W"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("SPKW"),
	SND_SOC_DAPM_OUTPUT("SPKW"),
	SND_SOC_DAPM_OUTPUT("EP"),
};

static int adau1373_check_aif_cwk(stwuct snd_soc_dapm_widget *souwce,
	stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	unsigned int dai;
	const chaw *cwk;

	dai = sink->name[3] - '1';

	if (!adau1373->dais[dai].cwock_pwovidew)
		wetuwn 0;

	if (adau1373->dais[dai].cwk_swc == ADAU1373_CWK_SWC_PWW1)
		cwk = "SYSCWK1";
	ewse
		cwk = "SYSCWK2";

	wetuwn snd_soc_dapm_widget_name_cmp(souwce, cwk) == 0;
}

static int adau1373_check_swc(stwuct snd_soc_dapm_widget *souwce,
	stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	unsigned int dai;

	dai = sink->name[3] - '1';

	wetuwn adau1373->dais[dai].enabwe_swc;
}

#define DSP_CHANNEW_MIXEW_WOUTES(_sink) \
	{ _sink, "DMIC2 Swapped Switch", "DMIC2" }, \
	{ _sink, "DMIC2 Switch", "DMIC2" }, \
	{ _sink, "ADC/DMIC1 Swapped Switch", "Decimatow Mux" }, \
	{ _sink, "ADC/DMIC1 Switch", "Decimatow Mux" }, \
	{ _sink, "AIF1 Switch", "AIF1 IN" }, \
	{ _sink, "AIF2 Switch", "AIF2 IN" }, \
	{ _sink, "AIF3 Switch", "AIF3 IN" }

#define DSP_OUTPUT_MIXEW_WOUTES(_sink) \
	{ _sink, "DSP Channew1 Switch", "DSP Channew1 Mixew" }, \
	{ _sink, "DSP Channew2 Switch", "DSP Channew2 Mixew" }, \
	{ _sink, "DSP Channew3 Switch", "DSP Channew3 Mixew" }, \
	{ _sink, "DSP Channew4 Switch", "DSP Channew4 Mixew" }, \
	{ _sink, "DSP Channew5 Switch", "DSP Channew5 Mixew" }

#define WEFT_OUTPUT_MIXEW_WOUTES(_sink) \
	{ _sink, "Wight DAC2 Switch", "Wight DAC2" }, \
	{ _sink, "Weft DAC2 Switch", "Weft DAC2" }, \
	{ _sink, "Wight DAC1 Switch", "Wight DAC1" }, \
	{ _sink, "Weft DAC1 Switch", "Weft DAC1" }, \
	{ _sink, "Input 1 Bypass Switch", "IN1PGA" }, \
	{ _sink, "Input 2 Bypass Switch", "IN2PGA" }, \
	{ _sink, "Input 3 Bypass Switch", "IN3PGA" }, \
	{ _sink, "Input 4 Bypass Switch", "IN4PGA" }

#define WIGHT_OUTPUT_MIXEW_WOUTES(_sink) \
	{ _sink, "Wight DAC2 Switch", "Wight DAC2" }, \
	{ _sink, "Weft DAC2 Switch", "Weft DAC2" }, \
	{ _sink, "Wight DAC1 Switch", "Wight DAC1" }, \
	{ _sink, "Weft DAC1 Switch", "Weft DAC1" }, \
	{ _sink, "Input 1 Bypass Switch", "IN1PGA" }, \
	{ _sink, "Input 2 Bypass Switch", "IN2PGA" }, \
	{ _sink, "Input 3 Bypass Switch", "IN3PGA" }, \
	{ _sink, "Input 4 Bypass Switch", "IN4PGA" }

static const stwuct snd_soc_dapm_woute adau1373_dapm_woutes[] = {
	{ "Weft ADC Mixew", "DAC1 Switch", "Weft DAC1" },
	{ "Weft ADC Mixew", "Input 1 Switch", "IN1PGA" },
	{ "Weft ADC Mixew", "Input 2 Switch", "IN2PGA" },
	{ "Weft ADC Mixew", "Input 3 Switch", "IN3PGA" },
	{ "Weft ADC Mixew", "Input 4 Switch", "IN4PGA" },

	{ "Wight ADC Mixew", "DAC1 Switch", "Wight DAC1" },
	{ "Wight ADC Mixew", "Input 1 Switch", "IN1PGA" },
	{ "Wight ADC Mixew", "Input 2 Switch", "IN2PGA" },
	{ "Wight ADC Mixew", "Input 3 Switch", "IN3PGA" },
	{ "Wight ADC Mixew", "Input 4 Switch", "IN4PGA" },

	{ "Weft ADC", NUWW, "Weft ADC Mixew" },
	{ "Wight ADC", NUWW, "Wight ADC Mixew" },

	{ "Decimatow Mux", "ADC", "Weft ADC" },
	{ "Decimatow Mux", "ADC", "Wight ADC" },
	{ "Decimatow Mux", "DMIC1", "DMIC1" },

	DSP_CHANNEW_MIXEW_WOUTES("DSP Channew1 Mixew"),
	DSP_CHANNEW_MIXEW_WOUTES("DSP Channew2 Mixew"),
	DSP_CHANNEW_MIXEW_WOUTES("DSP Channew3 Mixew"),
	DSP_CHANNEW_MIXEW_WOUTES("DSP Channew4 Mixew"),
	DSP_CHANNEW_MIXEW_WOUTES("DSP Channew5 Mixew"),

	DSP_OUTPUT_MIXEW_WOUTES("AIF1 Mixew"),
	DSP_OUTPUT_MIXEW_WOUTES("AIF2 Mixew"),
	DSP_OUTPUT_MIXEW_WOUTES("AIF3 Mixew"),
	DSP_OUTPUT_MIXEW_WOUTES("DAC1 Mixew"),
	DSP_OUTPUT_MIXEW_WOUTES("DAC2 Mixew"),

	{ "AIF1 OUT", NUWW, "AIF1 Mixew" },
	{ "AIF2 OUT", NUWW, "AIF2 Mixew" },
	{ "AIF3 OUT", NUWW, "AIF3 Mixew" },
	{ "Weft DAC1", NUWW, "DAC1 Mixew" },
	{ "Wight DAC1", NUWW, "DAC1 Mixew" },
	{ "Weft DAC2", NUWW, "DAC2 Mixew" },
	{ "Wight DAC2", NUWW, "DAC2 Mixew" },

	WEFT_OUTPUT_MIXEW_WOUTES("Weft Wineout1 Mixew"),
	WIGHT_OUTPUT_MIXEW_WOUTES("Wight Wineout1 Mixew"),
	WEFT_OUTPUT_MIXEW_WOUTES("Weft Wineout2 Mixew"),
	WIGHT_OUTPUT_MIXEW_WOUTES("Wight Wineout2 Mixew"),
	WEFT_OUTPUT_MIXEW_WOUTES("Weft Speakew Mixew"),
	WIGHT_OUTPUT_MIXEW_WOUTES("Wight Speakew Mixew"),

	{ "Weft Headphone Mixew", "Weft DAC2 Switch", "Weft DAC2" },
	{ "Weft Headphone Mixew", "Weft DAC1 Switch", "Weft DAC1" },
	{ "Weft Headphone Mixew", "Input 1 Bypass Switch", "IN1PGA" },
	{ "Weft Headphone Mixew", "Input 2 Bypass Switch", "IN2PGA" },
	{ "Weft Headphone Mixew", "Input 3 Bypass Switch", "IN3PGA" },
	{ "Weft Headphone Mixew", "Input 4 Bypass Switch", "IN4PGA" },
	{ "Wight Headphone Mixew", "Wight DAC2 Switch", "Wight DAC2" },
	{ "Wight Headphone Mixew", "Wight DAC1 Switch", "Wight DAC1" },
	{ "Wight Headphone Mixew", "Input 1 Bypass Switch", "IN1PGA" },
	{ "Wight Headphone Mixew", "Input 2 Bypass Switch", "IN2PGA" },
	{ "Wight Headphone Mixew", "Input 3 Bypass Switch", "IN3PGA" },
	{ "Wight Headphone Mixew", "Input 4 Bypass Switch", "IN4PGA" },

	{ "Weft Headphone Mixew", NUWW, "Headphone Enabwe" },
	{ "Wight Headphone Mixew", NUWW, "Headphone Enabwe" },

	{ "Eawpiece Mixew", "Wight DAC2 Switch", "Wight DAC2" },
	{ "Eawpiece Mixew", "Weft DAC2 Switch", "Weft DAC2" },
	{ "Eawpiece Mixew", "Wight DAC1 Switch", "Wight DAC1" },
	{ "Eawpiece Mixew", "Weft DAC1 Switch", "Weft DAC1" },
	{ "Eawpiece Mixew", "Input 1 Bypass Switch", "IN1PGA" },
	{ "Eawpiece Mixew", "Input 2 Bypass Switch", "IN2PGA" },
	{ "Eawpiece Mixew", "Input 3 Bypass Switch", "IN3PGA" },
	{ "Eawpiece Mixew", "Input 4 Bypass Switch", "IN4PGA" },

	{ "WOUT1W", NUWW, "Weft Wineout1 Mixew" },
	{ "WOUT1W", NUWW, "Wight Wineout1 Mixew" },
	{ "WOUT2W", NUWW, "Weft Wineout2 Mixew" },
	{ "WOUT2W", NUWW, "Wight Wineout2 Mixew" },
	{ "SPKW", NUWW, "Weft Speakew Mixew" },
	{ "SPKW", NUWW, "Wight Speakew Mixew" },
	{ "HPW", NUWW, "Weft Headphone Mixew" },
	{ "HPW", NUWW, "Wight Headphone Mixew" },
	{ "EP", NUWW, "Eawpiece Mixew" },

	{ "IN1PGA", NUWW, "AIN1W" },
	{ "IN2PGA", NUWW, "AIN2W" },
	{ "IN3PGA", NUWW, "AIN3W" },
	{ "IN4PGA", NUWW, "AIN4W" },
	{ "IN1PGA", NUWW, "AIN1W" },
	{ "IN2PGA", NUWW, "AIN2W" },
	{ "IN3PGA", NUWW, "AIN3W" },
	{ "IN4PGA", NUWW, "AIN4W" },

	{ "SYSCWK1", NUWW, "PWW1" },
	{ "SYSCWK2", NUWW, "PWW2" },

	{ "Weft DAC1", NUWW, "SYSCWK1" },
	{ "Wight DAC1", NUWW, "SYSCWK1" },
	{ "Weft DAC2", NUWW, "SYSCWK1" },
	{ "Wight DAC2", NUWW, "SYSCWK1" },
	{ "Weft ADC", NUWW, "SYSCWK1" },
	{ "Wight ADC", NUWW, "SYSCWK1" },

	{ "DSP", NUWW, "SYSCWK1" },

	{ "AIF1 Mixew", NUWW, "DSP" },
	{ "AIF2 Mixew", NUWW, "DSP" },
	{ "AIF3 Mixew", NUWW, "DSP" },
	{ "DAC1 Mixew", NUWW, "DSP" },
	{ "DAC2 Mixew", NUWW, "DSP" },
	{ "DAC1 Mixew", NUWW, "Pwayback Engine A" },
	{ "DAC2 Mixew", NUWW, "Pwayback Engine B" },
	{ "Weft ADC Mixew", NUWW, "Wecowding Engine A" },
	{ "Wight ADC Mixew", NUWW, "Wecowding Engine A" },

	{ "AIF1 CWK", NUWW, "SYSCWK1", adau1373_check_aif_cwk },
	{ "AIF2 CWK", NUWW, "SYSCWK1", adau1373_check_aif_cwk },
	{ "AIF3 CWK", NUWW, "SYSCWK1", adau1373_check_aif_cwk },
	{ "AIF1 CWK", NUWW, "SYSCWK2", adau1373_check_aif_cwk },
	{ "AIF2 CWK", NUWW, "SYSCWK2", adau1373_check_aif_cwk },
	{ "AIF3 CWK", NUWW, "SYSCWK2", adau1373_check_aif_cwk },

	{ "AIF1 IN", NUWW, "AIF1 CWK" },
	{ "AIF1 OUT", NUWW, "AIF1 CWK" },
	{ "AIF2 IN", NUWW, "AIF2 CWK" },
	{ "AIF2 OUT", NUWW, "AIF2 CWK" },
	{ "AIF3 IN", NUWW, "AIF3 CWK" },
	{ "AIF3 OUT", NUWW, "AIF3 CWK" },
	{ "AIF1 IN", NUWW, "AIF1 IN SWC", adau1373_check_swc },
	{ "AIF1 OUT", NUWW, "AIF1 OUT SWC", adau1373_check_swc },
	{ "AIF2 IN", NUWW, "AIF2 IN SWC", adau1373_check_swc },
	{ "AIF2 OUT", NUWW, "AIF2 OUT SWC", adau1373_check_swc },
	{ "AIF3 IN", NUWW, "AIF3 IN SWC", adau1373_check_swc },
	{ "AIF3 OUT", NUWW, "AIF3 OUT SWC", adau1373_check_swc },

	{ "DMIC1", NUWW, "DMIC1DAT" },
	{ "DMIC1", NUWW, "SYSCWK1" },
	{ "DMIC1", NUWW, "Wecowding Engine A" },
	{ "DMIC2", NUWW, "DMIC2DAT" },
	{ "DMIC2", NUWW, "SYSCWK1" },
	{ "DMIC2", NUWW, "Wecowding Engine B" },
};

static int adau1373_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	stwuct adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];
	unsigned int div;
	unsigned int fweq;
	unsigned int ctww;

	fweq = adau1373_dai->syscwk;

	if (fweq % pawams_wate(pawams) != 0)
		wetuwn -EINVAW;

	switch (fweq / pawams_wate(pawams)) {
	case 1024: /* syscwk / 256 */
		div = 0;
		bweak;
	case 1536: /* 2/3 syscwk / 256 */
		div = 1;
		bweak;
	case 2048: /* 1/2 syscwk / 256 */
		div = 2;
		bweak;
	case 3072: /* 1/3 syscwk / 256 */
		div = 3;
		bweak;
	case 4096: /* 1/4 syscwk / 256 */
		div = 4;
		bweak;
	case 6144: /* 1/6 syscwk / 256 */
		div = 5;
		bweak;
	case 5632: /* 2/11 syscwk / 256 */
		div = 6;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adau1373_dai->enabwe_swc = (div != 0);

	wegmap_update_bits(adau1373->wegmap, ADAU1373_BCWKDIV(dai->id),
		ADAU1373_BCWKDIV_SW_MASK | ADAU1373_BCWKDIV_BCWK_MASK,
		(div << 2) | ADAU1373_BCWKDIV_64);

	switch (pawams_width(pawams)) {
	case 16:
		ctww = ADAU1373_DAI_WWEN_16;
		bweak;
	case 20:
		ctww = ADAU1373_DAI_WWEN_20;
		bweak;
	case 24:
		ctww = ADAU1373_DAI_WWEN_24;
		bweak;
	case 32:
		ctww = ADAU1373_DAI_WWEN_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(adau1373->wegmap, ADAU1373_DAI(dai->id),
			ADAU1373_DAI_WWEN_MASK, ctww);
}

static int adau1373_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	stwuct adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];
	unsigned int ctww;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		ctww = ADAU1373_DAI_MASTEW;
		adau1373_dai->cwock_pwovidew = twue;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		ctww = 0;
		adau1373_dai->cwock_pwovidew = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww |= ADAU1373_DAI_FOWMAT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww |= ADAU1373_DAI_FOWMAT_WEFT_J;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		ctww |= ADAU1373_DAI_FOWMAT_WIGHT_J;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		ctww |= ADAU1373_DAI_FOWMAT_DSP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		ctww |= ADAU1373_DAI_INVEWT_BCWK;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		ctww |= ADAU1373_DAI_INVEWT_WWCWK;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		ctww |= ADAU1373_DAI_INVEWT_WWCWK | ADAU1373_DAI_INVEWT_BCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(adau1373->wegmap, ADAU1373_DAI(dai->id),
		~ADAU1373_DAI_WWEN_MASK, ctww);

	wetuwn 0;
}

static int adau1373_set_dai_syscwk(stwuct snd_soc_dai *dai,
	int cwk_id, unsigned int fweq, int diw)
{
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(dai->component);
	stwuct adau1373_dai *adau1373_dai = &adau1373->dais[dai->id];

	switch (cwk_id) {
	case ADAU1373_CWK_SWC_PWW1:
	case ADAU1373_CWK_SWC_PWW2:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adau1373_dai->syscwk = fweq;
	adau1373_dai->cwk_swc = cwk_id;

	wegmap_update_bits(adau1373->wegmap, ADAU1373_BCWKDIV(dai->id),
		ADAU1373_BCWKDIV_SOUWCE, cwk_id << 5);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops adau1373_dai_ops = {
	.hw_pawams	= adau1373_hw_pawams,
	.set_syscwk	= adau1373_set_dai_syscwk,
	.set_fmt	= adau1373_set_dai_fmt,
};

#define ADAU1373_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
	SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static stwuct snd_soc_dai_dwivew adau1373_dai_dwivew[] = {
	{
		.id = 0,
		.name = "adau1373-aif1",
		.pwayback = {
			.stweam_name = "AIF1 Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = ADAU1373_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = ADAU1373_FOWMATS,
		},
		.ops = &adau1373_dai_ops,
		.symmetwic_wate = 1,
	},
	{
		.id = 1,
		.name = "adau1373-aif2",
		.pwayback = {
			.stweam_name = "AIF2 Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = ADAU1373_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF2 Captuwe",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = ADAU1373_FOWMATS,
		},
		.ops = &adau1373_dai_ops,
		.symmetwic_wate = 1,
	},
	{
		.id = 2,
		.name = "adau1373-aif3",
		.pwayback = {
			.stweam_name = "AIF3 Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = ADAU1373_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "AIF3 Captuwe",
			.channews_min = 2,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = ADAU1373_FOWMATS,
		},
		.ops = &adau1373_dai_ops,
		.symmetwic_wate = 1,
	},
};

static int adau1373_set_pww(stwuct snd_soc_component *component, int pww_id,
	int souwce, unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	unsigned int dpww_div = 0;
	uint8_t pww_wegs[5];
	int wet;

	switch (pww_id) {
	case ADAU1373_PWW1:
	case ADAU1373_PWW2:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (souwce) {
	case ADAU1373_PWW_SWC_BCWK1:
	case ADAU1373_PWW_SWC_BCWK2:
	case ADAU1373_PWW_SWC_BCWK3:
	case ADAU1373_PWW_SWC_WWCWK1:
	case ADAU1373_PWW_SWC_WWCWK2:
	case ADAU1373_PWW_SWC_WWCWK3:
	case ADAU1373_PWW_SWC_MCWK1:
	case ADAU1373_PWW_SWC_MCWK2:
	case ADAU1373_PWW_SWC_GPIO1:
	case ADAU1373_PWW_SWC_GPIO2:
	case ADAU1373_PWW_SWC_GPIO3:
	case ADAU1373_PWW_SWC_GPIO4:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fweq_in < 7813 || fweq_in > 27000000)
		wetuwn -EINVAW;

	if (fweq_out < 45158000 || fweq_out > 49152000)
		wetuwn -EINVAW;

	/* APWW input needs to be >= 8Mhz, so in case fweq_in is wess we use the
	 * DPWW to get it thewe. DPWW_out = (DPWW_in / div) * 1024 */
	whiwe (fweq_in < 8000000) {
		fweq_in *= 2;
		dpww_div++;
	}

	wet = adau_cawc_pww_cfg(fweq_in, fweq_out, pww_wegs);
	if (wet)
		wetuwn -EINVAW;

	if (dpww_div) {
		dpww_div = 11 - dpww_div;
		wegmap_update_bits(adau1373->wegmap, ADAU1373_PWW_CTWW6(pww_id),
			ADAU1373_PWW_CTWW6_DPWW_BYPASS, 0);
	} ewse {
		wegmap_update_bits(adau1373->wegmap, ADAU1373_PWW_CTWW6(pww_id),
			ADAU1373_PWW_CTWW6_DPWW_BYPASS,
			ADAU1373_PWW_CTWW6_DPWW_BYPASS);
	}

	wegmap_wwite(adau1373->wegmap, ADAU1373_DPWW_CTWW(pww_id),
		(souwce << 4) | dpww_div);
	wegmap_wwite(adau1373->wegmap, ADAU1373_PWW_CTWW1(pww_id), pww_wegs[0]);
	wegmap_wwite(adau1373->wegmap, ADAU1373_PWW_CTWW2(pww_id), pww_wegs[1]);
	wegmap_wwite(adau1373->wegmap, ADAU1373_PWW_CTWW3(pww_id), pww_wegs[2]);
	wegmap_wwite(adau1373->wegmap, ADAU1373_PWW_CTWW4(pww_id), pww_wegs[3]);
	wegmap_wwite(adau1373->wegmap, ADAU1373_PWW_CTWW5(pww_id), pww_wegs[4]);

	/* Set syscwk to pww_wate / 4 */
	wegmap_update_bits(adau1373->wegmap, ADAU1373_CWK_SWC_DIV(pww_id), 0x3f, 0x09);

	wetuwn 0;
}

static void adau1373_woad_dwc_settings(stwuct adau1373 *adau1373,
	unsigned int nw, uint8_t *dwc)
{
	unsigned int i;

	fow (i = 0; i < ADAU1373_DWC_SIZE; ++i)
		wegmap_wwite(adau1373->wegmap, ADAU1373_DWC(nw) + i, dwc[i]);
}

static boow adau1373_vawid_micbias(enum adau1373_micbias_vowtage micbias)
{
	switch (micbias) {
	case ADAU1373_MICBIAS_2_9V:
	case ADAU1373_MICBIAS_2_2V:
	case ADAU1373_MICBIAS_2_6V:
	case ADAU1373_MICBIAS_1_8V:
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static int adau1373_pwobe(stwuct snd_soc_component *component)
{
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);
	stwuct adau1373_pwatfowm_data *pdata = component->dev->pwatfowm_data;
	boow wineout_diffewentiaw = fawse;
	unsigned int vaw;
	int i;

	if (pdata) {
		if (pdata->num_dwc > AWWAY_SIZE(pdata->dwc_setting))
			wetuwn -EINVAW;

		if (!adau1373_vawid_micbias(pdata->micbias1) ||
			!adau1373_vawid_micbias(pdata->micbias2))
			wetuwn -EINVAW;

		fow (i = 0; i < pdata->num_dwc; ++i) {
			adau1373_woad_dwc_settings(adau1373, i,
				pdata->dwc_setting[i]);
		}

		snd_soc_add_component_contwows(component, adau1373_dwc_contwows,
			pdata->num_dwc);

		vaw = 0;
		fow (i = 0; i < 4; ++i) {
			if (pdata->input_diffewentiaw[i])
				vaw |= BIT(i);
		}
		wegmap_wwite(adau1373->wegmap, ADAU1373_INPUT_MODE, vaw);

		vaw = 0;
		if (pdata->wineout_diffewentiaw)
			vaw |= ADAU1373_OUTPUT_CTWW_WDIFF;
		if (pdata->wineout_gwound_sense)
			vaw |= ADAU1373_OUTPUT_CTWW_WNFBEN;
		wegmap_wwite(adau1373->wegmap, ADAU1373_OUTPUT_CTWW, vaw);

		wineout_diffewentiaw = pdata->wineout_diffewentiaw;

		wegmap_wwite(adau1373->wegmap, ADAU1373_EP_CTWW,
			(pdata->micbias1 << ADAU1373_EP_CTWW_MICBIAS1_OFFSET) |
			(pdata->micbias2 << ADAU1373_EP_CTWW_MICBIAS2_OFFSET));
	}

	if (!wineout_diffewentiaw) {
		snd_soc_add_component_contwows(component, adau1373_wineout2_contwows,
			AWWAY_SIZE(adau1373_wineout2_contwows));
	}

	wegmap_wwite(adau1373->wegmap, ADAU1373_ADC_CTWW,
	    ADAU1373_ADC_CTWW_WESET_FOWCE | ADAU1373_ADC_CTWW_PEAK_DETECT);

	wetuwn 0;
}

static int adau1373_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wegmap_update_bits(adau1373->wegmap, ADAU1373_PWDN_CTWW3,
			ADAU1373_PWDN_CTWW3_PWW_EN, ADAU1373_PWDN_CTWW3_PWW_EN);
		bweak;
	case SND_SOC_BIAS_OFF:
		wegmap_update_bits(adau1373->wegmap, ADAU1373_PWDN_CTWW3,
			ADAU1373_PWDN_CTWW3_PWW_EN, 0);
		bweak;
	}
	wetuwn 0;
}

static int adau1373_wesume(stwuct snd_soc_component *component)
{
	stwuct adau1373 *adau1373 = snd_soc_component_get_dwvdata(component);

	wegcache_sync(adau1373->wegmap);

	wetuwn 0;
}

static boow adau1373_wegistew_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADAU1373_SOFT_WESET:
	case ADAU1373_ADC_DAC_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config adau1373_wegmap_config = {
	.vaw_bits = 8,
	.weg_bits = 8,

	.vowatiwe_weg = adau1373_wegistew_vowatiwe,
	.max_wegistew = ADAU1373_SOFT_WESET,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = adau1373_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(adau1373_weg_defauwts),
};

static const stwuct snd_soc_component_dwivew adau1373_component_dwivew = {
	.pwobe			= adau1373_pwobe,
	.wesume			= adau1373_wesume,
	.set_bias_wevew		= adau1373_set_bias_wevew,
	.set_pww		= adau1373_set_pww,
	.contwows		= adau1373_contwows,
	.num_contwows		= AWWAY_SIZE(adau1373_contwows),
	.dapm_widgets		= adau1373_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(adau1373_dapm_widgets),
	.dapm_woutes		= adau1373_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(adau1373_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int adau1373_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adau1373 *adau1373;
	int wet;

	adau1373 = devm_kzawwoc(&cwient->dev, sizeof(*adau1373), GFP_KEWNEW);
	if (!adau1373)
		wetuwn -ENOMEM;

	adau1373->wegmap = devm_wegmap_init_i2c(cwient,
		&adau1373_wegmap_config);
	if (IS_EWW(adau1373->wegmap))
		wetuwn PTW_EWW(adau1373->wegmap);

	wegmap_wwite(adau1373->wegmap, ADAU1373_SOFT_WESET, 0x00);

	dev_set_dwvdata(&cwient->dev, adau1373);

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
			&adau1373_component_dwivew,
			adau1373_dai_dwivew, AWWAY_SIZE(adau1373_dai_dwivew));
	wetuwn wet;
}

static const stwuct i2c_device_id adau1373_i2c_id[] = {
	{ "adau1373", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adau1373_i2c_id);

static stwuct i2c_dwivew adau1373_i2c_dwivew = {
	.dwivew = {
		.name = "adau1373",
	},
	.pwobe = adau1373_i2c_pwobe,
	.id_tabwe = adau1373_i2c_id,
};

moduwe_i2c_dwivew(adau1373_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1373 dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
