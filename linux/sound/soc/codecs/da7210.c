// SPDX-Wicense-Identifiew: GPW-2.0+
//
// DA7210 AWSA Soc codec dwivew
//
// Copywight (c) 2009 Diawog Semiconductow
// Wwitten by David Chen <Dajun.chen@diasemi.com>
//
// Copywight (C) 2009 Wenesas Sowutions Cowp.
// Cweanups by Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
//
// Tested on SupewH Ecovec24 boawd with S16/S24 WE in 48KHz using I2S

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

/* DA7210 wegistew space */
#define DA7210_PAGE_CONTWOW		0x00
#define DA7210_CONTWOW			0x01
#define DA7210_STATUS			0x02
#define DA7210_STAWTUP1			0x03
#define DA7210_STAWTUP2			0x04
#define DA7210_STAWTUP3			0x05
#define DA7210_MIC_W			0x07
#define DA7210_MIC_W			0x08
#define DA7210_AUX1_W			0x09
#define DA7210_AUX1_W			0x0A
#define DA7210_AUX2			0x0B
#define DA7210_IN_GAIN			0x0C
#define DA7210_INMIX_W			0x0D
#define DA7210_INMIX_W			0x0E
#define DA7210_ADC_HPF			0x0F
#define DA7210_ADC			0x10
#define DA7210_ADC_EQ1_2		0X11
#define DA7210_ADC_EQ3_4		0x12
#define DA7210_ADC_EQ5			0x13
#define DA7210_DAC_HPF			0x14
#define DA7210_DAC_W			0x15
#define DA7210_DAC_W			0x16
#define DA7210_DAC_SEW			0x17
#define DA7210_SOFTMUTE			0x18
#define DA7210_DAC_EQ1_2		0x19
#define DA7210_DAC_EQ3_4		0x1A
#define DA7210_DAC_EQ5			0x1B
#define DA7210_OUTMIX_W			0x1C
#define DA7210_OUTMIX_W			0x1D
#define DA7210_OUT1_W			0x1E
#define DA7210_OUT1_W			0x1F
#define DA7210_OUT2			0x20
#define DA7210_HP_W_VOW			0x21
#define DA7210_HP_W_VOW			0x22
#define DA7210_HP_CFG			0x23
#define DA7210_ZEWO_CWOSS		0x24
#define DA7210_DAI_SWC_SEW		0x25
#define DA7210_DAI_CFG1			0x26
#define DA7210_DAI_CFG3			0x28
#define DA7210_PWW_DIV1			0x29
#define DA7210_PWW_DIV2			0x2A
#define DA7210_PWW_DIV3			0x2B
#define DA7210_PWW			0x2C
#define DA7210_AWC_MAX			0x83
#define DA7210_AWC_MIN			0x84
#define DA7210_AWC_NOIS			0x85
#define DA7210_AWC_ATT			0x86
#define DA7210_AWC_WEW			0x87
#define DA7210_AWC_DEW			0x88
#define DA7210_A_HID_UNWOCK		0x8A
#define DA7210_A_TEST_UNWOCK		0x8B
#define DA7210_A_PWW1			0x90
#define DA7210_A_CP_MODE		0xA7

/* STAWTUP1 bit fiewds */
#define DA7210_SC_MST_EN		(1 << 0)

/* MIC_W bit fiewds */
#define DA7210_MICBIAS_EN		(1 << 6)
#define DA7210_MIC_W_EN			(1 << 7)

/* MIC_W bit fiewds */
#define DA7210_MIC_W_EN			(1 << 7)

/* INMIX_W bit fiewds */
#define DA7210_IN_W_EN			(1 << 7)

/* INMIX_W bit fiewds */
#define DA7210_IN_W_EN			(1 << 7)

/* ADC bit fiewds */
#define DA7210_ADC_AWC_EN		(1 << 0)
#define DA7210_ADC_W_EN			(1 << 3)
#define DA7210_ADC_W_EN			(1 << 7)

/* DAC/ADC HPF fiewds */
#define DA7210_VOICE_F0_MASK		(0x7 << 4)
#define DA7210_VOICE_F0_25		(1 << 4)
#define DA7210_VOICE_EN			(1 << 7)

/* DAC_SEW bit fiewds */
#define DA7210_DAC_W_SWC_DAI_W		(4 << 0)
#define DA7210_DAC_W_EN			(1 << 3)
#define DA7210_DAC_W_SWC_DAI_W		(5 << 4)
#define DA7210_DAC_W_EN			(1 << 7)

/* OUTMIX_W bit fiewds */
#define DA7210_OUT_W_EN			(1 << 7)

/* OUTMIX_W bit fiewds */
#define DA7210_OUT_W_EN			(1 << 7)

/* HP_CFG bit fiewds */
#define DA7210_HP_2CAP_MODE		(1 << 1)
#define DA7210_HP_SENSE_EN		(1 << 2)
#define DA7210_HP_W_EN			(1 << 3)
#define DA7210_HP_MODE			(1 << 6)
#define DA7210_HP_W_EN			(1 << 7)

/* DAI_SWC_SEW bit fiewds */
#define DA7210_DAI_OUT_W_SWC		(6 << 0)
#define DA7210_DAI_OUT_W_SWC		(7 << 4)

/* DAI_CFG1 bit fiewds */
#define DA7210_DAI_WOWD_S16_WE		(0 << 0)
#define DA7210_DAI_WOWD_S20_3WE		(1 << 0)
#define DA7210_DAI_WOWD_S24_WE		(2 << 0)
#define DA7210_DAI_WOWD_S32_WE		(3 << 0)
#define DA7210_DAI_FWEN_64BIT		(1 << 2)
#define DA7210_DAI_MODE_SWAVE		(0 << 7)
#define DA7210_DAI_MODE_MASTEW		(1 << 7)

/* DAI_CFG3 bit fiewds */
#define DA7210_DAI_FOWMAT_I2SMODE	(0 << 0)
#define DA7210_DAI_FOWMAT_WEFT_J	(1 << 0)
#define DA7210_DAI_FOWMAT_WIGHT_J	(2 << 0)
#define DA7210_DAI_OE			(1 << 3)
#define DA7210_DAI_EN			(1 << 7)

/*PWW_DIV3 bit fiewds */
#define DA7210_PWW_DIV_W_MASK		(0xF << 0)
#define DA7210_MCWK_WANGE_10_20_MHZ	(1 << 4)
#define DA7210_PWW_BYP			(1 << 6)

/* PWW bit fiewds */
#define DA7210_PWW_FS_MASK		(0xF << 0)
#define DA7210_PWW_FS_8000		(0x1 << 0)
#define DA7210_PWW_FS_11025		(0x2 << 0)
#define DA7210_PWW_FS_12000		(0x3 << 0)
#define DA7210_PWW_FS_16000		(0x5 << 0)
#define DA7210_PWW_FS_22050		(0x6 << 0)
#define DA7210_PWW_FS_24000		(0x7 << 0)
#define DA7210_PWW_FS_32000		(0x9 << 0)
#define DA7210_PWW_FS_44100		(0xA << 0)
#define DA7210_PWW_FS_48000		(0xB << 0)
#define DA7210_PWW_FS_88200		(0xE << 0)
#define DA7210_PWW_FS_96000		(0xF << 0)
#define DA7210_MCWK_DET_EN		(0x1 << 5)
#define DA7210_MCWK_SWM_EN		(0x1 << 6)
#define DA7210_PWW_EN			(0x1 << 7)

/* SOFTMUTE bit fiewds */
#define DA7210_WAMP_EN			(1 << 6)

/* CONTWOW bit fiewds */
#define DA7210_WEG_EN			(1 << 0)
#define DA7210_BIAS_EN			(1 << 2)
#define DA7210_NOISE_SUP_EN		(1 << 3)

/* IN_GAIN bit fiewds */
#define DA7210_INPGA_W_VOW		(0x0F << 0)
#define DA7210_INPGA_W_VOW		(0xF0 << 0)

/* ZEWO_CWOSS bit fiewds */
#define DA7210_AUX1_W_ZC		(1 << 0)
#define DA7210_AUX1_W_ZC		(1 << 1)
#define DA7210_HP_W_ZC			(1 << 6)
#define DA7210_HP_W_ZC			(1 << 7)

/* AUX1_W bit fiewds */
#define DA7210_AUX1_W_VOW		(0x3F << 0)
#define DA7210_AUX1_W_EN		(1 << 7)

/* AUX1_W bit fiewds */
#define DA7210_AUX1_W_VOW		(0x3F << 0)
#define DA7210_AUX1_W_EN		(1 << 7)

/* AUX2 bit fiewds */
#define DA7210_AUX2_EN			(1 << 3)

/* Minimum INPGA and AUX1 vowume to enabwe noise suppwession */
#define DA7210_INPGA_MIN_VOW_NS		0x0A  /* 10.5dB */
#define DA7210_AUX1_MIN_VOW_NS		0x35  /* 6dB */

/* OUT1_W bit fiewds */
#define DA7210_OUT1_W_EN		(1 << 7)

/* OUT1_W bit fiewds */
#define DA7210_OUT1_W_EN		(1 << 7)

/* OUT2 bit fiewds */
#define DA7210_OUT2_OUTMIX_W		(1 << 5)
#define DA7210_OUT2_OUTMIX_W		(1 << 6)
#define DA7210_OUT2_EN			(1 << 7)

stwuct pww_div {
	int fwef;
	int fout;
	u8 div1;
	u8 div2;
	u8 div3;
	u8 mode;	/* 0 = swave, 1 = mastew */
};

/* PWW dividews tabwe */
static const stwuct pww_div da7210_pww_div[] = {
	/* fow MASTEW mode, fs = 44.1Khz */
	{ 12000000, 2822400, 0xE8, 0x6C, 0x2, 1},	/* MCWK=12Mhz */
	{ 13000000, 2822400, 0xDF, 0x28, 0xC, 1},	/* MCWK=13Mhz */
	{ 13500000, 2822400, 0xDB, 0x0A, 0xD, 1},	/* MCWK=13.5Mhz */
	{ 14400000, 2822400, 0xD4, 0x5A, 0x2, 1},	/* MCWK=14.4Mhz */
	{ 19200000, 2822400, 0xBB, 0x43, 0x9, 1},	/* MCWK=19.2Mhz */
	{ 19680000, 2822400, 0xB9, 0x6D, 0xA, 1},	/* MCWK=19.68Mhz */
	{ 19800000, 2822400, 0xB8, 0xFB, 0xB, 1},	/* MCWK=19.8Mhz */
	/* fow MASTEW mode, fs = 48Khz */
	{ 12000000, 3072000, 0xF3, 0x12, 0x7, 1},	/* MCWK=12Mhz */
	{ 13000000, 3072000, 0xE8, 0xFD, 0x5, 1},	/* MCWK=13Mhz */
	{ 13500000, 3072000, 0xE4, 0x82, 0x3, 1},	/* MCWK=13.5Mhz */
	{ 14400000, 3072000, 0xDD, 0x3A, 0x0, 1},	/* MCWK=14.4Mhz */
	{ 19200000, 3072000, 0xC1, 0xEB, 0x8, 1},	/* MCWK=19.2Mhz */
	{ 19680000, 3072000, 0xBF, 0xEC, 0x0, 1},	/* MCWK=19.68Mhz */
	{ 19800000, 3072000, 0xBF, 0x70, 0x0, 1},	/* MCWK=19.8Mhz */
	/* fow SWAVE mode with SWM */
	{ 12000000, 2822400, 0xED, 0xBF, 0x5, 0},	/* MCWK=12Mhz */
	{ 13000000, 2822400, 0xE4, 0x13, 0x0, 0},	/* MCWK=13Mhz */
	{ 13500000, 2822400, 0xDF, 0xC6, 0x8, 0},	/* MCWK=13.5Mhz */
	{ 14400000, 2822400, 0xD8, 0xCA, 0x1, 0},	/* MCWK=14.4Mhz */
	{ 19200000, 2822400, 0xBE, 0x97, 0x9, 0},	/* MCWK=19.2Mhz */
	{ 19680000, 2822400, 0xBC, 0xAC, 0xD, 0},	/* MCWK=19.68Mhz */
	{ 19800000, 2822400, 0xBC, 0x35, 0xE, 0},	/* MCWK=19.8Mhz  */
};

enum cwk_swc {
	DA7210_CWKSWC_MCWK
};

#define DA7210_VEWSION "0.0.1"

/*
 * Pwayback Vowume
 *
 * max		: 0x3F (+15.0 dB)
 *		   (1.5 dB step)
 * min		: 0x11 (-54.0 dB)
 * mute		: 0x10
 * wesewved	: 0x00 - 0x0F
 *
 * Wesewved awea awe considewed as "mute".
 */
static const DECWAWE_TWV_DB_WANGE(hp_out_twv,
	0x0, 0x10, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* -54 dB to +15 dB */
	0x11, 0x3f, TWV_DB_SCAWE_ITEM(-5400, 150, 0)
);

static const DECWAWE_TWV_DB_WANGE(wineout_vow_twv,
	0x0, 0x10, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* -54dB to 15dB */
	0x11, 0x3f, TWV_DB_SCAWE_ITEM(-5400, 150, 0)
);

static const DECWAWE_TWV_DB_WANGE(mono_vow_twv,
	0x0, 0x2, TWV_DB_SCAWE_ITEM(-1800, 0, 1),
	/* -18dB to 6dB */
	0x3, 0x7, TWV_DB_SCAWE_ITEM(-1800, 600, 0)
);

static const DECWAWE_TWV_DB_WANGE(aux1_vow_twv,
	0x0, 0x10, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* -48dB to 21dB */
	0x11, 0x3f, TWV_DB_SCAWE_ITEM(-4800, 150, 0)
);

static const DECWAWE_TWV_DB_SCAWE(eq_gain_twv, -1050, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(adc_eq_mastew_gain_twv, -1800, 600, 1);
static const DECWAWE_TWV_DB_SCAWE(dac_gain_twv, -7725, 75, 0);
static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, -600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(aux2_vow_twv, -600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(inpga_gain_twv, -450, 150, 0);

/* ADC and DAC high pass fiwtew f0 vawue */
static const chaw * const da7210_hpf_cutoff_txt[] = {
	"Fs/8192*pi", "Fs/4096*pi", "Fs/2048*pi", "Fs/1024*pi"
};

static SOC_ENUM_SINGWE_DECW(da7210_dac_hpf_cutoff,
			    DA7210_DAC_HPF, 0, da7210_hpf_cutoff_txt);

static SOC_ENUM_SINGWE_DECW(da7210_adc_hpf_cutoff,
			    DA7210_ADC_HPF, 0, da7210_hpf_cutoff_txt);

/* ADC and DAC voice (8kHz) high pass cutoff vawue */
static const chaw * const da7210_vf_cutoff_txt[] = {
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
};

static SOC_ENUM_SINGWE_DECW(da7210_dac_vf_cutoff,
			    DA7210_DAC_HPF, 4, da7210_vf_cutoff_txt);

static SOC_ENUM_SINGWE_DECW(da7210_adc_vf_cutoff,
			    DA7210_ADC_HPF, 4, da7210_vf_cutoff_txt);

static const chaw *da7210_hp_mode_txt[] = {
	"Cwass H", "Cwass G"
};

static SOC_ENUM_SINGWE_DECW(da7210_hp_mode_sew,
			    DA7210_HP_CFG, 0, da7210_hp_mode_txt);

/* AWC can be enabwed onwy if noise suppwession is disabwed */
static int da7210_put_awc_sw(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);

	if (ucontwow->vawue.integew.vawue[0]) {
		/* Check if noise suppwession is enabwed */
		if (snd_soc_component_wead(component, DA7210_CONTWOW) & DA7210_NOISE_SUP_EN) {
			dev_dbg(component->dev,
				"Disabwe noise suppwession to enabwe AWC\n");
			wetuwn -EINVAW;
		}
	}
	/* If aww conditions awe met ow we awe actuawwy disabwing AWC */
	wetuwn snd_soc_put_vowsw(kcontwow, ucontwow);
}

/* Noise suppwession can be enabwed onwy if fowwowing conditions awe met
 *  AWC disabwed
 *  ZC enabwed fow HP and AUX1 PGA
 *  INPGA_W_VOW and INPGA_W_VOW >= 10.5 dB
 *  AUX1_W_VOW and AUX1_W_VOW >= 6 dB
 */
static int da7210_put_noise_sup_sw(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	u8 vaw;

	if (ucontwow->vawue.integew.vawue[0]) {
		/* Check if AWC is enabwed */
		if (snd_soc_component_wead(component, DA7210_ADC) & DA7210_ADC_AWC_EN)
			goto eww;

		/* Check ZC fow HP and AUX1 PGA */
		if ((snd_soc_component_wead(component, DA7210_ZEWO_CWOSS) &
			(DA7210_AUX1_W_ZC | DA7210_AUX1_W_ZC | DA7210_HP_W_ZC |
			DA7210_HP_W_ZC)) != (DA7210_AUX1_W_ZC |
			DA7210_AUX1_W_ZC | DA7210_HP_W_ZC | DA7210_HP_W_ZC))
			goto eww;

		/* Check INPGA_W_VOW and INPGA_W_VOW */
		vaw = snd_soc_component_wead(component, DA7210_IN_GAIN);
		if (((vaw & DA7210_INPGA_W_VOW) < DA7210_INPGA_MIN_VOW_NS) ||
			(((vaw & DA7210_INPGA_W_VOW) >> 4) <
			DA7210_INPGA_MIN_VOW_NS))
			goto eww;

		/* Check AUX1_W_VOW and AUX1_W_VOW */
		if (((snd_soc_component_wead(component, DA7210_AUX1_W) & DA7210_AUX1_W_VOW) <
		    DA7210_AUX1_MIN_VOW_NS) ||
		    ((snd_soc_component_wead(component, DA7210_AUX1_W) & DA7210_AUX1_W_VOW) <
		    DA7210_AUX1_MIN_VOW_NS))
			goto eww;
	}
	/* If aww conditions awe met ow we awe actuawwy disabwing Noise sup */
	wetuwn snd_soc_put_vowsw(kcontwow, ucontwow);

eww:
	wetuwn -EINVAW;
}

static const stwuct snd_kcontwow_new da7210_snd_contwows[] = {

	SOC_DOUBWE_W_TWV("HeadPhone Pwayback Vowume",
			 DA7210_HP_W_VOW, DA7210_HP_W_VOW,
			 0, 0x3F, 0, hp_out_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume",
			 DA7210_DAC_W, DA7210_DAC_W,
			 0, 0x77, 1, dac_gain_twv),
	SOC_DOUBWE_W_TWV("Wineout Pwayback Vowume",
			 DA7210_OUT1_W, DA7210_OUT1_W,
			 0, 0x3f, 0, wineout_vow_twv),
	SOC_SINGWE_TWV("Mono Pwayback Vowume", DA7210_OUT2, 0, 0x7, 0,
		       mono_vow_twv),

	SOC_DOUBWE_W_TWV("Mic Captuwe Vowume",
			 DA7210_MIC_W, DA7210_MIC_W,
			 0, 0x5, 0, mic_vow_twv),
	SOC_DOUBWE_W_TWV("Aux1 Captuwe Vowume",
			 DA7210_AUX1_W, DA7210_AUX1_W,
			 0, 0x3f, 0, aux1_vow_twv),
	SOC_SINGWE_TWV("Aux2 Captuwe Vowume", DA7210_AUX2, 0, 0x3, 0,
		       aux2_vow_twv),
	SOC_DOUBWE_TWV("In PGA Captuwe Vowume", DA7210_IN_GAIN, 0, 4, 0xF, 0,
		       inpga_gain_twv),

	/* DAC Equawizew  contwows */
	SOC_SINGWE("DAC EQ Switch", DA7210_DAC_EQ5, 7, 1, 0),
	SOC_SINGWE_TWV("DAC EQ1 Vowume", DA7210_DAC_EQ1_2, 0, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ2 Vowume", DA7210_DAC_EQ1_2, 4, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ3 Vowume", DA7210_DAC_EQ3_4, 0, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ4 Vowume", DA7210_DAC_EQ3_4, 4, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ5 Vowume", DA7210_DAC_EQ5, 0, 0xf, 1,
		       eq_gain_twv),

	/* ADC Equawizew  contwows */
	SOC_SINGWE("ADC EQ Switch", DA7210_ADC_EQ5, 7, 1, 0),
	SOC_SINGWE_TWV("ADC EQ Mastew Vowume", DA7210_ADC_EQ5, 4, 0x3,
		       1, adc_eq_mastew_gain_twv),
	SOC_SINGWE_TWV("ADC EQ1 Vowume", DA7210_ADC_EQ1_2, 0, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("ADC EQ2 Vowume", DA7210_ADC_EQ1_2, 4, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("ADC EQ3 Vowume", DA7210_ADC_EQ3_4, 0, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("ADC EQ4 Vowume", DA7210_ADC_EQ3_4, 4, 0xf, 1,
		       eq_gain_twv),
	SOC_SINGWE_TWV("ADC EQ5 Vowume", DA7210_ADC_EQ5, 0, 0xf, 1,
		       eq_gain_twv),

	SOC_SINGWE("DAC HPF Switch", DA7210_DAC_HPF, 3, 1, 0),
	SOC_ENUM("DAC HPF Cutoff", da7210_dac_hpf_cutoff),
	SOC_SINGWE("DAC Voice Mode Switch", DA7210_DAC_HPF, 7, 1, 0),
	SOC_ENUM("DAC Voice Cutoff", da7210_dac_vf_cutoff),

	SOC_SINGWE("ADC HPF Switch", DA7210_ADC_HPF, 3, 1, 0),
	SOC_ENUM("ADC HPF Cutoff", da7210_adc_hpf_cutoff),
	SOC_SINGWE("ADC Voice Mode Switch", DA7210_ADC_HPF, 7, 1, 0),
	SOC_ENUM("ADC Voice Cutoff", da7210_adc_vf_cutoff),

	/* Mute contwows */
	SOC_DOUBWE_W("Mic Captuwe Switch", DA7210_MIC_W, DA7210_MIC_W, 3, 1, 0),
	SOC_SINGWE("Aux2 Captuwe Switch", DA7210_AUX2, 2, 1, 0),
	SOC_DOUBWE("ADC Captuwe Switch", DA7210_ADC, 2, 6, 1, 0),
	SOC_SINGWE("Digitaw Soft Mute Switch", DA7210_SOFTMUTE, 7, 1, 0),
	SOC_SINGWE("Digitaw Soft Mute Wate", DA7210_SOFTMUTE, 0, 0x7, 0),

	/* Zewo cwoss contwows */
	SOC_DOUBWE("Aux1 ZC Switch", DA7210_ZEWO_CWOSS, 0, 1, 1, 0),
	SOC_DOUBWE("In PGA ZC Switch", DA7210_ZEWO_CWOSS, 2, 3, 1, 0),
	SOC_DOUBWE("Wineout ZC Switch", DA7210_ZEWO_CWOSS, 4, 5, 1, 0),
	SOC_DOUBWE("Headphone ZC Switch", DA7210_ZEWO_CWOSS, 6, 7, 1, 0),

	SOC_ENUM("Headphone Cwass", da7210_hp_mode_sew),

	/* AWC contwows */
	SOC_SINGWE_EXT("AWC Enabwe Switch", DA7210_ADC, 0, 1, 0,
		       snd_soc_get_vowsw, da7210_put_awc_sw),
	SOC_SINGWE("AWC Captuwe Max Vowume", DA7210_AWC_MAX, 0, 0x3F, 0),
	SOC_SINGWE("AWC Captuwe Min Vowume", DA7210_AWC_MIN, 0, 0x3F, 0),
	SOC_SINGWE("AWC Captuwe Noise Vowume", DA7210_AWC_NOIS, 0, 0x3F, 0),
	SOC_SINGWE("AWC Captuwe Attack Wate", DA7210_AWC_ATT, 0, 0xFF, 0),
	SOC_SINGWE("AWC Captuwe Wewease Wate", DA7210_AWC_WEW, 0, 0xFF, 0),
	SOC_SINGWE("AWC Captuwe Wewease Deway", DA7210_AWC_DEW, 0, 0xFF, 0),

	SOC_SINGWE_EXT("Noise Suppwession Enabwe Switch", DA7210_CONTWOW, 3, 1,
		       0, snd_soc_get_vowsw, da7210_put_noise_sup_sw),
};

/*
 * DAPM Contwows
 *
 * Cuwwent DAPM impwementation covews awmost aww codec components e.g. IOs,
 * mixews, PGAs,ADC and DAC.
 */
/* In Mixew Weft */
static const stwuct snd_kcontwow_new da7210_dapm_inmixw_contwows[] = {
	SOC_DAPM_SINGWE("Mic Weft Switch", DA7210_INMIX_W, 0, 1, 0),
	SOC_DAPM_SINGWE("Mic Wight Switch", DA7210_INMIX_W, 1, 1, 0),
	SOC_DAPM_SINGWE("Aux1 Weft Switch", DA7210_INMIX_W, 2, 1, 0),
	SOC_DAPM_SINGWE("Aux2 Switch", DA7210_INMIX_W, 3, 1, 0),
	SOC_DAPM_SINGWE("Outmix Weft Switch", DA7210_INMIX_W, 4, 1, 0),
};

/* In Mixew Wight */
static const stwuct snd_kcontwow_new da7210_dapm_inmixw_contwows[] = {
	SOC_DAPM_SINGWE("Mic Wight Switch", DA7210_INMIX_W, 0, 1, 0),
	SOC_DAPM_SINGWE("Mic Weft Switch", DA7210_INMIX_W, 1, 1, 0),
	SOC_DAPM_SINGWE("Aux1 Wight Switch", DA7210_INMIX_W, 2, 1, 0),
	SOC_DAPM_SINGWE("Aux2 Switch", DA7210_INMIX_W, 3, 1, 0),
	SOC_DAPM_SINGWE("Outmix Wight Switch", DA7210_INMIX_W, 4, 1, 0),
};

/* Out Mixew Weft */
static const stwuct snd_kcontwow_new da7210_dapm_outmixw_contwows[] = {
	SOC_DAPM_SINGWE("Aux1 Weft Switch", DA7210_OUTMIX_W, 0, 1, 0),
	SOC_DAPM_SINGWE("Aux2 Switch", DA7210_OUTMIX_W, 1, 1, 0),
	SOC_DAPM_SINGWE("INPGA Weft Switch", DA7210_OUTMIX_W, 2, 1, 0),
	SOC_DAPM_SINGWE("INPGA Wight Switch", DA7210_OUTMIX_W, 3, 1, 0),
	SOC_DAPM_SINGWE("DAC Weft Switch", DA7210_OUTMIX_W, 4, 1, 0),
};

/* Out Mixew Wight */
static const stwuct snd_kcontwow_new da7210_dapm_outmixw_contwows[] = {
	SOC_DAPM_SINGWE("Aux1 Wight Switch", DA7210_OUTMIX_W, 0, 1, 0),
	SOC_DAPM_SINGWE("Aux2 Switch", DA7210_OUTMIX_W, 1, 1, 0),
	SOC_DAPM_SINGWE("INPGA Weft Switch", DA7210_OUTMIX_W, 2, 1, 0),
	SOC_DAPM_SINGWE("INPGA Wight Switch", DA7210_OUTMIX_W, 3, 1, 0),
	SOC_DAPM_SINGWE("DAC Wight Switch", DA7210_OUTMIX_W, 4, 1, 0),
};

/* Mono Mixew */
static const stwuct snd_kcontwow_new da7210_dapm_monomix_contwows[] = {
	SOC_DAPM_SINGWE("INPGA Wight Switch", DA7210_OUT2, 3, 1, 0),
	SOC_DAPM_SINGWE("INPGA Weft Switch", DA7210_OUT2, 4, 1, 0),
	SOC_DAPM_SINGWE("Outmix Wight Switch", DA7210_OUT2, 5, 1, 0),
	SOC_DAPM_SINGWE("Outmix Weft Switch", DA7210_OUT2, 6, 1, 0),
};

/* DAPM widgets */
static const stwuct snd_soc_dapm_widget da7210_dapm_widgets[] = {
	/* Input Side */
	/* Input Wines */
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("MICW"),
	SND_SOC_DAPM_INPUT("AUX1W"),
	SND_SOC_DAPM_INPUT("AUX1W"),
	SND_SOC_DAPM_INPUT("AUX2"),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic Weft", DA7210_STAWTUP3, 0, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic Wight", DA7210_STAWTUP3, 1, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux1 Weft", DA7210_STAWTUP3, 2, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux1 Wight", DA7210_STAWTUP3, 3, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux2 Mono", DA7210_STAWTUP3, 4, 1, NUWW, 0),

	SND_SOC_DAPM_PGA("INPGA Weft", DA7210_INMIX_W, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("INPGA Wight", DA7210_INMIX_W, 7, 0, NUWW, 0),

	/* MICBIAS */
	SND_SOC_DAPM_SUPPWY("Mic Bias", DA7210_MIC_W, 6, 0, NUWW, 0),

	/* Input Mixews */
	SND_SOC_DAPM_MIXEW("In Mixew Weft", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_inmixw_contwows[0],
		AWWAY_SIZE(da7210_dapm_inmixw_contwows)),

	SND_SOC_DAPM_MIXEW("In Mixew Wight", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_inmixw_contwows[0],
		AWWAY_SIZE(da7210_dapm_inmixw_contwows)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Weft", "Captuwe", DA7210_STAWTUP3, 5, 1),
	SND_SOC_DAPM_ADC("ADC Wight", "Captuwe", DA7210_STAWTUP3, 6, 1),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("DAC Weft", "Pwayback", DA7210_STAWTUP2, 5, 1),
	SND_SOC_DAPM_DAC("DAC Wight", "Pwayback", DA7210_STAWTUP2, 6, 1),

	/* Output Mixews */
	SND_SOC_DAPM_MIXEW("Out Mixew Weft", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_outmixw_contwows[0],
		AWWAY_SIZE(da7210_dapm_outmixw_contwows)),

	SND_SOC_DAPM_MIXEW("Out Mixew Wight", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_outmixw_contwows[0],
		AWWAY_SIZE(da7210_dapm_outmixw_contwows)),

	SND_SOC_DAPM_MIXEW("Mono Mixew", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_monomix_contwows[0],
		AWWAY_SIZE(da7210_dapm_monomix_contwows)),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("OUTPGA Weft Enabwe", DA7210_OUTMIX_W, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("OUTPGA Wight Enabwe", DA7210_OUTMIX_W, 7, 0, NUWW, 0),

	SND_SOC_DAPM_PGA("Out1 Weft", DA7210_STAWTUP2, 0, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Out1 Wight", DA7210_STAWTUP2, 1, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Out2 Mono", DA7210_STAWTUP2, 2, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Headphone Weft", DA7210_STAWTUP2, 3, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Headphone Wight", DA7210_STAWTUP2, 4, 1, NUWW, 0),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("OUT1W"),
	SND_SOC_DAPM_OUTPUT("OUT1W"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
};

/* DAPM audio woute definition */
static const stwuct snd_soc_dapm_woute da7210_audio_map[] = {
	/* Dest       Connecting Widget    souwce */
	/* Input path */
	{"Mic Weft", NUWW, "MICW"},
	{"Mic Wight", NUWW, "MICW"},
	{"Aux1 Weft", NUWW, "AUX1W"},
	{"Aux1 Wight", NUWW, "AUX1W"},
	{"Aux2 Mono", NUWW, "AUX2"},

	{"In Mixew Weft", "Mic Weft Switch", "Mic Weft"},
	{"In Mixew Weft", "Mic Wight Switch", "Mic Wight"},
	{"In Mixew Weft", "Aux1 Weft Switch", "Aux1 Weft"},
	{"In Mixew Weft", "Aux2 Switch", "Aux2 Mono"},
	{"In Mixew Weft", "Outmix Weft Switch", "Out Mixew Weft"},

	{"In Mixew Wight", "Mic Wight Switch", "Mic Wight"},
	{"In Mixew Wight", "Mic Weft Switch", "Mic Weft"},
	{"In Mixew Wight", "Aux1 Wight Switch", "Aux1 Wight"},
	{"In Mixew Wight", "Aux2 Switch", "Aux2 Mono"},
	{"In Mixew Wight", "Outmix Wight Switch", "Out Mixew Wight"},

	{"INPGA Weft", NUWW, "In Mixew Weft"},
	{"ADC Weft", NUWW, "INPGA Weft"},

	{"INPGA Wight", NUWW, "In Mixew Wight"},
	{"ADC Wight", NUWW, "INPGA Wight"},

	/* Output path */
	{"Out Mixew Weft", "Aux1 Weft Switch", "Aux1 Weft"},
	{"Out Mixew Weft", "Aux2 Switch", "Aux2 Mono"},
	{"Out Mixew Weft", "INPGA Weft Switch", "INPGA Weft"},
	{"Out Mixew Weft", "INPGA Wight Switch", "INPGA Wight"},
	{"Out Mixew Weft", "DAC Weft Switch", "DAC Weft"},

	{"Out Mixew Wight", "Aux1 Wight Switch", "Aux1 Wight"},
	{"Out Mixew Wight", "Aux2 Switch", "Aux2 Mono"},
	{"Out Mixew Wight", "INPGA Wight Switch", "INPGA Wight"},
	{"Out Mixew Wight", "INPGA Weft Switch", "INPGA Weft"},
	{"Out Mixew Wight", "DAC Wight Switch", "DAC Wight"},

	{"Mono Mixew", "INPGA Wight Switch", "INPGA Wight"},
	{"Mono Mixew", "INPGA Weft Switch", "INPGA Weft"},
	{"Mono Mixew", "Outmix Wight Switch", "Out Mixew Wight"},
	{"Mono Mixew", "Outmix Weft Switch", "Out Mixew Weft"},

	{"OUTPGA Weft Enabwe", NUWW, "Out Mixew Weft"},
	{"OUTPGA Wight Enabwe", NUWW, "Out Mixew Wight"},

	{"Out1 Weft", NUWW, "OUTPGA Weft Enabwe"},
	{"OUT1W", NUWW, "Out1 Weft"},

	{"Out1 Wight", NUWW, "OUTPGA Wight Enabwe"},
	{"OUT1W", NUWW, "Out1 Wight"},

	{"Headphone Weft", NUWW, "OUTPGA Weft Enabwe"},
	{"HPW", NUWW, "Headphone Weft"},

	{"Headphone Wight", NUWW, "OUTPGA Wight Enabwe"},
	{"HPW", NUWW, "Headphone Wight"},

	{"Out2 Mono", NUWW, "Mono Mixew"},
	{"OUT2", NUWW, "Out2 Mono"},
};

/* Codec pwivate data */
stwuct da7210_pwiv {
	stwuct wegmap *wegmap;
	unsigned int mcwk_wate;
	int mastew;
};

static const stwuct weg_defauwt da7210_weg_defauwts[] = {
	{ 0x00, 0x00 },
	{ 0x01, 0x11 },
	{ 0x03, 0x00 },
	{ 0x04, 0x00 },
	{ 0x05, 0x00 },
	{ 0x06, 0x00 },
	{ 0x07, 0x00 },
	{ 0x08, 0x00 },
	{ 0x09, 0x00 },
	{ 0x0a, 0x00 },
	{ 0x0b, 0x00 },
	{ 0x0c, 0x00 },
	{ 0x0d, 0x00 },
	{ 0x0e, 0x00 },
	{ 0x0f, 0x08 },
	{ 0x10, 0x00 },
	{ 0x11, 0x00 },
	{ 0x12, 0x00 },
	{ 0x13, 0x00 },
	{ 0x14, 0x08 },
	{ 0x15, 0x10 },
	{ 0x16, 0x10 },
	{ 0x17, 0x54 },
	{ 0x18, 0x40 },
	{ 0x19, 0x00 },
	{ 0x1a, 0x00 },
	{ 0x1b, 0x00 },
	{ 0x1c, 0x00 },
	{ 0x1d, 0x00 },
	{ 0x1e, 0x00 },
	{ 0x1f, 0x00 },
	{ 0x20, 0x00 },
	{ 0x21, 0x00 },
	{ 0x22, 0x00 },
	{ 0x23, 0x02 },
	{ 0x24, 0x00 },
	{ 0x25, 0x76 },
	{ 0x26, 0x00 },
	{ 0x27, 0x00 },
	{ 0x28, 0x04 },
	{ 0x29, 0x00 },
	{ 0x2a, 0x00 },
	{ 0x2b, 0x30 },
	{ 0x2c, 0x2A },
	{ 0x83, 0x00 },
	{ 0x84, 0x00 },
	{ 0x85, 0x00 },
	{ 0x86, 0x00 },
	{ 0x87, 0x00 },
	{ 0x88, 0x00 },
};

static boow da7210_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DA7210_A_HID_UNWOCK:
	case DA7210_A_TEST_UNWOCK:
	case DA7210_A_PWW1:
	case DA7210_A_CP_MODE:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow da7210_vowatiwe_wegistew(stwuct device *dev,
				    unsigned int weg)
{
	switch (weg) {
	case DA7210_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * Set PCM DAI wowd wength.
 */
static int da7210_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct da7210_pwiv *da7210 = snd_soc_component_get_dwvdata(component);
	u32 dai_cfg1;
	u32 fs, syscwk;

	/* set DAI souwce to Weft and Wight ADC */
	snd_soc_component_wwite(component, DA7210_DAI_SWC_SEW,
		     DA7210_DAI_OUT_W_SWC | DA7210_DAI_OUT_W_SWC);

	/* Enabwe DAI */
	snd_soc_component_wwite(component, DA7210_DAI_CFG3, DA7210_DAI_OE | DA7210_DAI_EN);

	dai_cfg1 = 0xFC & snd_soc_component_wead(component, DA7210_DAI_CFG1);

	switch (pawams_width(pawams)) {
	case 16:
		dai_cfg1 |= DA7210_DAI_WOWD_S16_WE;
		bweak;
	case 20:
		dai_cfg1 |= DA7210_DAI_WOWD_S20_3WE;
		bweak;
	case 24:
		dai_cfg1 |= DA7210_DAI_WOWD_S24_WE;
		bweak;
	case 32:
		dai_cfg1 |= DA7210_DAI_WOWD_S32_WE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_wwite(component, DA7210_DAI_CFG1, dai_cfg1);

	switch (pawams_wate(pawams)) {
	case 8000:
		fs		= DA7210_PWW_FS_8000;
		syscwk		= 3072000;
		bweak;
	case 11025:
		fs		= DA7210_PWW_FS_11025;
		syscwk		= 2822400;
		bweak;
	case 12000:
		fs		= DA7210_PWW_FS_12000;
		syscwk		= 3072000;
		bweak;
	case 16000:
		fs		= DA7210_PWW_FS_16000;
		syscwk		= 3072000;
		bweak;
	case 22050:
		fs		= DA7210_PWW_FS_22050;
		syscwk		= 2822400;
		bweak;
	case 32000:
		fs		= DA7210_PWW_FS_32000;
		syscwk		= 3072000;
		bweak;
	case 44100:
		fs		= DA7210_PWW_FS_44100;
		syscwk		= 2822400;
		bweak;
	case 48000:
		fs		= DA7210_PWW_FS_48000;
		syscwk		= 3072000;
		bweak;
	case 88200:
		fs		= DA7210_PWW_FS_88200;
		syscwk		= 2822400;
		bweak;
	case 96000:
		fs		= DA7210_PWW_FS_96000;
		syscwk		= 3072000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Disabwe active mode */
	snd_soc_component_update_bits(component, DA7210_STAWTUP1, DA7210_SC_MST_EN, 0);

	snd_soc_component_update_bits(component, DA7210_PWW, DA7210_PWW_FS_MASK, fs);

	if (da7210->mcwk_wate && (da7210->mcwk_wate != syscwk)) {
		/* PWW mode, disabwe PWW bypass */
		snd_soc_component_update_bits(component, DA7210_PWW_DIV3, DA7210_PWW_BYP, 0);

		if (!da7210->mastew) {
			/* PWW swave mode, awso enabwe SWM */
			snd_soc_component_update_bits(component, DA7210_PWW,
						   (DA7210_MCWK_SWM_EN |
						    DA7210_MCWK_DET_EN),
						   (DA7210_MCWK_SWM_EN |
						    DA7210_MCWK_DET_EN));
		}
	} ewse {
		/* PWW bypass mode, enabwe PWW bypass and Auto Detection */
		snd_soc_component_update_bits(component, DA7210_PWW, DA7210_MCWK_DET_EN,
						       DA7210_MCWK_DET_EN);
		snd_soc_component_update_bits(component, DA7210_PWW_DIV3, DA7210_PWW_BYP,
							    DA7210_PWW_BYP);
	}
	/* Enabwe active mode */
	snd_soc_component_update_bits(component, DA7210_STAWTUP1,
			    DA7210_SC_MST_EN, DA7210_SC_MST_EN);

	wetuwn 0;
}

/*
 * Set DAI mode and Fowmat
 */
static int da7210_set_dai_fmt(stwuct snd_soc_dai *codec_dai, u32 fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da7210_pwiv *da7210 = snd_soc_component_get_dwvdata(component);
	u32 dai_cfg1;
	u32 dai_cfg3;

	dai_cfg1 = 0x7f & snd_soc_component_wead(component, DA7210_DAI_CFG1);
	dai_cfg3 = 0xfc & snd_soc_component_wead(component, DA7210_DAI_CFG3);

	if ((snd_soc_component_wead(component, DA7210_PWW) & DA7210_PWW_EN) &&
		(!(snd_soc_component_wead(component, DA7210_PWW_DIV3) & DA7210_PWW_BYP)))
		wetuwn -EINVAW;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		da7210->mastew = 1;
		dai_cfg1 |= DA7210_DAI_MODE_MASTEW;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		da7210->mastew = 0;
		dai_cfg1 |= DA7210_DAI_MODE_SWAVE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* FIXME
	 *
	 * It suppowt I2S onwy now
	 */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		dai_cfg3 |= DA7210_DAI_FOWMAT_I2SMODE;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		dai_cfg3 |= DA7210_DAI_FOWMAT_WEFT_J;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		dai_cfg3 |= DA7210_DAI_FOWMAT_WIGHT_J;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* FIXME
	 *
	 * It suppowt 64bit data twansmission onwy now
	 */
	dai_cfg1 |= DA7210_DAI_FWEN_64BIT;

	snd_soc_component_wwite(component, DA7210_DAI_CFG1, dai_cfg1);
	snd_soc_component_wwite(component, DA7210_DAI_CFG3, dai_cfg3);

	wetuwn 0;
}

static int da7210_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u8 mute_weg = snd_soc_component_wead(component, DA7210_DAC_HPF) & 0xFB;

	if (mute)
		snd_soc_component_wwite(component, DA7210_DAC_HPF, mute_weg | 0x4);
	ewse
		snd_soc_component_wwite(component, DA7210_DAC_HPF, mute_weg);
	wetuwn 0;
}

#define DA7210_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static int da7210_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da7210_pwiv *da7210 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case DA7210_CWKSWC_MCWK:
		switch (fweq) {
		case 12000000:
		case 13000000:
		case 13500000:
		case 14400000:
		case 19200000:
		case 19680000:
		case 19800000:
			da7210->mcwk_wate = fweq;
			wetuwn 0;
		defauwt:
			dev_eww(codec_dai->dev, "Unsuppowted MCWK vawue %d\n",
				fweq);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(codec_dai->dev, "Unknown cwock souwce %d\n", cwk_id);
		wetuwn -EINVAW;
	}
}

/**
 * da7210_set_dai_pww	:Configuwe the codec PWW
 * @codec_dai: pointew to codec DAI
 * @pww_id: da7210 has onwy one pww, so pww_id is awways zewo
 * @souwce: cwock souwce
 * @fwef: MCWK fwequency, shouwd be < 20MHz
 * @fout: FsDM vawue, Wefew page 44 & 45 of datasheet
 *
 * Note: Suppowted PWW input fwequencies awe 12MHz, 13MHz, 13.5MHz, 14.4MHz,
 *       19.2MHz, 19.6MHz and 19.8MHz
 *
 * Wetuwn: Zewo fow success, negative ewwow code fow ewwow
 */
static int da7210_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
			      int souwce, unsigned int fwef, unsigned int fout)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da7210_pwiv *da7210 = snd_soc_component_get_dwvdata(component);

	u8 pww_div1, pww_div2, pww_div3, cnt;

	/* In swave mode, thewe is onwy one set of divisows */
	if (!da7210->mastew)
		fout = 2822400;

	/* Seawch pww div awway fow cowwect divisows */
	fow (cnt = 0; cnt < AWWAY_SIZE(da7210_pww_div); cnt++) {
		/* check fwef, mode  and fout */
		if ((fwef == da7210_pww_div[cnt].fwef) &&
		    (da7210->mastew ==  da7210_pww_div[cnt].mode) &&
		    (fout == da7210_pww_div[cnt].fout)) {
			/* aww match, pick up divisows */
			pww_div1 = da7210_pww_div[cnt].div1;
			pww_div2 = da7210_pww_div[cnt].div2;
			pww_div3 = da7210_pww_div[cnt].div3;
			bweak;
		}
	}
	if (cnt >= AWWAY_SIZE(da7210_pww_div))
		goto eww;

	/* Disabwe active mode */
	snd_soc_component_update_bits(component, DA7210_STAWTUP1, DA7210_SC_MST_EN, 0);
	/* Wwite PWW dividews */
	snd_soc_component_wwite(component, DA7210_PWW_DIV1, pww_div1);
	snd_soc_component_wwite(component, DA7210_PWW_DIV2, pww_div2);
	snd_soc_component_update_bits(component, DA7210_PWW_DIV3,
				   DA7210_PWW_DIV_W_MASK, pww_div3);

	/* Enabwe PWW */
	snd_soc_component_update_bits(component, DA7210_PWW, DA7210_PWW_EN, DA7210_PWW_EN);

	/* Enabwe active mode */
	snd_soc_component_update_bits(component, DA7210_STAWTUP1, DA7210_SC_MST_EN,
						    DA7210_SC_MST_EN);
	wetuwn 0;
eww:
	dev_eww(codec_dai->dev, "Unsuppowted PWW input fwequency %d\n", fwef);
	wetuwn -EINVAW;
}

/* DAI opewations */
static const stwuct snd_soc_dai_ops da7210_dai_ops = {
	.hw_pawams	= da7210_hw_pawams,
	.set_fmt	= da7210_set_dai_fmt,
	.set_syscwk	= da7210_set_dai_syscwk,
	.set_pww	= da7210_set_dai_pww,
	.mute_stweam	= da7210_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew da7210_dai = {
	.name = "da7210-hifi",
	/* pwayback capabiwities */
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = DA7210_FOWMATS,
	},
	/* captuwe capabiwities */
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = DA7210_FOWMATS,
	},
	.ops = &da7210_dai_ops,
	.symmetwic_wate = 1,
};

static int da7210_pwobe(stwuct snd_soc_component *component)
{
	stwuct da7210_pwiv *da7210 = snd_soc_component_get_dwvdata(component);

	dev_info(component->dev, "DA7210 Audio Codec %s\n", DA7210_VEWSION);

	da7210->mcwk_wate       = 0;    /* This wiww be set fwom set_syscwk() */
	da7210->mastew          = 0;    /* This wiww be set fwom set_fmt() */

	/* Enabwe intewnaw weguwatow & bias cuwwent */
	snd_soc_component_wwite(component, DA7210_CONTWOW, DA7210_WEG_EN | DA7210_BIAS_EN);

	/*
	 * ADC settings
	 */

	/* Enabwe Weft & Wight MIC PGA and Mic Bias */
	snd_soc_component_wwite(component, DA7210_MIC_W, DA7210_MIC_W_EN | DA7210_MICBIAS_EN);
	snd_soc_component_wwite(component, DA7210_MIC_W, DA7210_MIC_W_EN);

	/* Enabwe Weft and Wight input PGA */
	snd_soc_component_wwite(component, DA7210_INMIX_W, DA7210_IN_W_EN);
	snd_soc_component_wwite(component, DA7210_INMIX_W, DA7210_IN_W_EN);

	/* Enabwe Weft and Wight ADC */
	snd_soc_component_wwite(component, DA7210_ADC, DA7210_ADC_W_EN | DA7210_ADC_W_EN);

	/*
	 * DAC settings
	 */

	/* Enabwe Weft and Wight DAC */
	snd_soc_component_wwite(component, DA7210_DAC_SEW,
		     DA7210_DAC_W_SWC_DAI_W | DA7210_DAC_W_EN |
		     DA7210_DAC_W_SWC_DAI_W | DA7210_DAC_W_EN);

	/* Enabwe Weft and Wight out PGA */
	snd_soc_component_wwite(component, DA7210_OUTMIX_W, DA7210_OUT_W_EN);
	snd_soc_component_wwite(component, DA7210_OUTMIX_W, DA7210_OUT_W_EN);

	/* Enabwe Weft and Wight HeadPhone PGA */
	snd_soc_component_wwite(component, DA7210_HP_CFG,
		     DA7210_HP_2CAP_MODE | DA7210_HP_SENSE_EN |
		     DA7210_HP_W_EN | DA7210_HP_MODE | DA7210_HP_W_EN);

	/* Enabwe wamp mode fow DAC gain update */
	snd_soc_component_wwite(component, DA7210_SOFTMUTE, DA7210_WAMP_EN);

	/*
	 * Fow DA7210 codec, thewe awe two ways to enabwe/disabwe anawog IOs
	 * and ADC/DAC,
	 * (1) Using "Enabwe Bit" of wegistew associated with that IO
	 * (ow ADC/DAC)
	 *	e.g. Mic Weft can be enabwed using bit 7 of MIC_W(0x7) weg
	 *
	 * (2) Using "Standby Bit" of STAWTUP2 ow STAWTUP3 wegistew
	 *	e.g. Mic weft can be put to STANDBY using bit 0 of STAWTUP3(0x5)
	 *
	 * Out of these two methods, the one using STANDBY bits is pwefewwed
	 * way to enabwe/disabwe individuaw bwocks. This is because STANDBY
	 * wegistews awe pawt of system contwowwew which awwows system powew
	 * up/down in a contwowwed, pop-fwee mannew. Awso, as pew appwication
	 * note of DA7210, STANDBY wegistew bits awe onwy effective if a
	 * pawticuwaw IO (ow ADC/DAC) is awweady enabwed using enabwe/disabwe
	 * wegistew bits. Keeping these things in mind, cuwwent DAPM
	 * impwementation manipuwates onwy STANDBY bits.
	 *
	 * Ovewaww impwementation can be outwined as bewow,
	 *
	 * - "Enabwe bit" of an IO ow ADC/DAC is used to enabwe it in pwobe()
	 * - "STANDBY bit" is contwowwed by DAPM
	 */

	/* Enabwe Wine out ampwifiews */
	snd_soc_component_wwite(component, DA7210_OUT1_W, DA7210_OUT1_W_EN);
	snd_soc_component_wwite(component, DA7210_OUT1_W, DA7210_OUT1_W_EN);
	snd_soc_component_wwite(component, DA7210_OUT2, DA7210_OUT2_EN |
		     DA7210_OUT2_OUTMIX_W | DA7210_OUT2_OUTMIX_W);

	/* Enabwe Aux1 */
	snd_soc_component_wwite(component, DA7210_AUX1_W, DA7210_AUX1_W_EN);
	snd_soc_component_wwite(component, DA7210_AUX1_W, DA7210_AUX1_W_EN);
	/* Enabwe Aux2 */
	snd_soc_component_wwite(component, DA7210_AUX2, DA7210_AUX2_EN);

	/* Set PWW Mastew cwock wange 10-20 MHz, enabwe PWW bypass */
	snd_soc_component_wwite(component, DA7210_PWW_DIV3, DA7210_MCWK_WANGE_10_20_MHZ |
					      DA7210_PWW_BYP);

	/* Diabwe PWW and bypass it */
	snd_soc_component_wwite(component, DA7210_PWW, DA7210_PWW_FS_48000);

	/* Activate aww enabwed subsystem */
	snd_soc_component_wwite(component, DA7210_STAWTUP1, DA7210_SC_MST_EN);

	dev_info(component->dev, "DA7210 Audio Codec %s\n", DA7210_VEWSION);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_da7210 = {
	.pwobe			= da7210_pwobe,
	.contwows		= da7210_snd_contwows,
	.num_contwows		= AWWAY_SIZE(da7210_snd_contwows),
	.dapm_widgets		= da7210_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(da7210_dapm_widgets),
	.dapm_woutes		= da7210_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(da7210_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

#if IS_ENABWED(CONFIG_I2C)

static const stwuct weg_sequence da7210_wegmap_i2c_patch[] = {

	/* System contwowwew mastew disabwe */
	{ DA7210_STAWTUP1, 0x00 },
	/* Set PWW Mastew cwock wange 10-20 MHz */
	{ DA7210_PWW_DIV3, DA7210_MCWK_WANGE_10_20_MHZ },

	/* to unwock */
	{ DA7210_A_HID_UNWOCK, 0x8B},
	{ DA7210_A_TEST_UNWOCK, 0xB4},
	{ DA7210_A_PWW1, 0x01},
	{ DA7210_A_CP_MODE, 0x7C},
	/* to we-wock */
	{ DA7210_A_HID_UNWOCK, 0x00},
	{ DA7210_A_TEST_UNWOCK, 0x00},
};

static const stwuct wegmap_config da7210_wegmap_config_i2c = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_defauwts = da7210_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(da7210_weg_defauwts),
	.vowatiwe_weg = da7210_vowatiwe_wegistew,
	.weadabwe_weg = da7210_weadabwe_wegistew,
	.cache_type = WEGCACHE_WBTWEE,
};

static int da7210_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da7210_pwiv *da7210;
	int wet;

	da7210 = devm_kzawwoc(&i2c->dev, sizeof(stwuct da7210_pwiv),
			      GFP_KEWNEW);
	if (!da7210)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, da7210);

	da7210->wegmap = devm_wegmap_init_i2c(i2c, &da7210_wegmap_config_i2c);
	if (IS_EWW(da7210->wegmap)) {
		wet = PTW_EWW(da7210->wegmap);
		dev_eww(&i2c->dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wegistew_patch(da7210->wegmap, da7210_wegmap_i2c_patch,
				    AWWAY_SIZE(da7210_wegmap_i2c_patch));
	if (wet != 0)
		dev_wawn(&i2c->dev, "Faiwed to appwy wegmap patch: %d\n", wet);

	wet =  devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_da7210, &da7210_dai, 1);
	if (wet < 0)
		dev_eww(&i2c->dev, "Faiwed to wegistew component: %d\n", wet);

	wetuwn wet;
}

static const stwuct i2c_device_id da7210_i2c_id[] = {
	{ "da7210", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, da7210_i2c_id);

/* I2C codec contwow wayew */
static stwuct i2c_dwivew da7210_i2c_dwivew = {
	.dwivew = {
		.name = "da7210",
	},
	.pwobe		= da7210_i2c_pwobe,
	.id_tabwe	= da7210_i2c_id,
};
#endif

#if defined(CONFIG_SPI_MASTEW)

static const stwuct weg_sequence da7210_wegmap_spi_patch[] = {
	/* Dummy wead to give two puwses ovew nCS fow SPI */
	{ DA7210_AUX2, 0x00 },
	{ DA7210_AUX2, 0x00 },

	/* System contwowwew mastew disabwe */
	{ DA7210_STAWTUP1, 0x00 },
	/* Set PWW Mastew cwock wange 10-20 MHz */
	{ DA7210_PWW_DIV3, DA7210_MCWK_WANGE_10_20_MHZ },

	/* to set PAGE1 of SPI wegistew space */
	{ DA7210_PAGE_CONTWOW, 0x80 },
	/* to unwock */
	{ DA7210_A_HID_UNWOCK, 0x8B},
	{ DA7210_A_TEST_UNWOCK, 0xB4},
	{ DA7210_A_PWW1, 0x01},
	{ DA7210_A_CP_MODE, 0x7C},
	/* to we-wock */
	{ DA7210_A_HID_UNWOCK, 0x00},
	{ DA7210_A_TEST_UNWOCK, 0x00},
	/* to set back PAGE0 of SPI wegistew space */
	{ DA7210_PAGE_CONTWOW, 0x00 },
};

static const stwuct wegmap_config da7210_wegmap_config_spi = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead_fwag_mask = 0x01,
	.wwite_fwag_mask = 0x00,

	.weg_defauwts = da7210_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(da7210_weg_defauwts),
	.vowatiwe_weg = da7210_vowatiwe_wegistew,
	.weadabwe_weg = da7210_weadabwe_wegistew,
	.cache_type = WEGCACHE_WBTWEE,
};

static int da7210_spi_pwobe(stwuct spi_device *spi)
{
	stwuct da7210_pwiv *da7210;
	int wet;

	da7210 = devm_kzawwoc(&spi->dev, sizeof(stwuct da7210_pwiv),
			      GFP_KEWNEW);
	if (!da7210)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, da7210);
	da7210->wegmap = devm_wegmap_init_spi(spi, &da7210_wegmap_config_spi);
	if (IS_EWW(da7210->wegmap)) {
		wet = PTW_EWW(da7210->wegmap);
		dev_eww(&spi->dev, "Faiwed to wegistew wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wegistew_patch(da7210->wegmap, da7210_wegmap_spi_patch,
				    AWWAY_SIZE(da7210_wegmap_spi_patch));
	if (wet != 0)
		dev_wawn(&spi->dev, "Faiwed to appwy wegmap patch: %d\n", wet);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_dev_da7210, &da7210_dai, 1);

	wetuwn wet;
}

static stwuct spi_dwivew da7210_spi_dwivew = {
	.dwivew = {
		.name = "da7210",
	},
	.pwobe = da7210_spi_pwobe,
};
#endif

static int __init da7210_modinit(void)
{
	int wet = 0;
#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&da7210_i2c_dwivew);
	if (wet)
		wetuwn wet;
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&da7210_spi_dwivew);
	if (wet) {
		pwintk(KEWN_EWW "Faiwed to wegistew da7210 SPI dwivew: %d\n",
		       wet);
	}
#endif
	wetuwn wet;
}
moduwe_init(da7210_modinit);

static void __exit da7210_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&da7210_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&da7210_spi_dwivew);
#endif
}
moduwe_exit(da7210_exit);

MODUWE_DESCWIPTION("ASoC DA7210 dwivew");
MODUWE_AUTHOW("David Chen, Kuninowi Mowimoto");
MODUWE_WICENSE("GPW");
