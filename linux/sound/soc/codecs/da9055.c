// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DA9055 AWSA Soc codec dwivew
 *
 * Copywight (c) 2012 Diawog Semiconductow
 *
 * Tested on (Samsung SMDK6410 boawd + DA9055 EVB) using I2S and I2C
 * Wwitten by David Chen <david.chen@diasemi.com> and
 * Ashish Chavan <ashish.chavan@kpitcummins.com>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>
#incwude <sound/da9055.h>

/* DA9055 wegistew space */

/* Status Wegistews */
#define DA9055_STATUS1			0x02
#define DA9055_PWW_STATUS		0x03
#define DA9055_AUX_W_GAIN_STATUS	0x04
#define DA9055_AUX_W_GAIN_STATUS	0x05
#define DA9055_MIC_W_GAIN_STATUS	0x06
#define DA9055_MIC_W_GAIN_STATUS	0x07
#define DA9055_MIXIN_W_GAIN_STATUS	0x08
#define DA9055_MIXIN_W_GAIN_STATUS	0x09
#define DA9055_ADC_W_GAIN_STATUS	0x0A
#define DA9055_ADC_W_GAIN_STATUS	0x0B
#define DA9055_DAC_W_GAIN_STATUS	0x0C
#define DA9055_DAC_W_GAIN_STATUS	0x0D
#define DA9055_HP_W_GAIN_STATUS		0x0E
#define DA9055_HP_W_GAIN_STATUS		0x0F
#define DA9055_WINE_GAIN_STATUS		0x10

/* System Initiawisation Wegistews */
#define DA9055_CIF_CTWW			0x20
#define DA9055_DIG_WOUTING_AIF		0X21
#define DA9055_SW			0x22
#define DA9055_WEFEWENCES		0x23
#define DA9055_PWW_FWAC_TOP		0x24
#define DA9055_PWW_FWAC_BOT		0x25
#define DA9055_PWW_INTEGEW		0x26
#define DA9055_PWW_CTWW			0x27
#define DA9055_AIF_CWK_MODE		0x28
#define DA9055_AIF_CTWW			0x29
#define DA9055_DIG_WOUTING_DAC		0x2A
#define DA9055_AWC_CTWW1		0x2B

/* Input - Gain, Sewect and Fiwtew Wegistews */
#define DA9055_AUX_W_GAIN		0x30
#define DA9055_AUX_W_GAIN		0x31
#define DA9055_MIXIN_W_SEWECT		0x32
#define DA9055_MIXIN_W_SEWECT		0x33
#define DA9055_MIXIN_W_GAIN		0x34
#define DA9055_MIXIN_W_GAIN		0x35
#define DA9055_ADC_W_GAIN		0x36
#define DA9055_ADC_W_GAIN		0x37
#define DA9055_ADC_FIWTEWS1		0x38
#define DA9055_MIC_W_GAIN		0x39
#define DA9055_MIC_W_GAIN		0x3A

/* Output - Gain, Sewect and Fiwtew Wegistews */
#define DA9055_DAC_FIWTEWS5		0x40
#define DA9055_DAC_FIWTEWS2		0x41
#define DA9055_DAC_FIWTEWS3		0x42
#define DA9055_DAC_FIWTEWS4		0x43
#define DA9055_DAC_FIWTEWS1		0x44
#define DA9055_DAC_W_GAIN		0x45
#define DA9055_DAC_W_GAIN		0x46
#define DA9055_CP_CTWW			0x47
#define DA9055_HP_W_GAIN		0x48
#define DA9055_HP_W_GAIN		0x49
#define DA9055_WINE_GAIN		0x4A
#define DA9055_MIXOUT_W_SEWECT		0x4B
#define DA9055_MIXOUT_W_SEWECT		0x4C

/* System Contwowwew Wegistews */
#define DA9055_SYSTEM_MODES_INPUT	0x50
#define DA9055_SYSTEM_MODES_OUTPUT	0x51

/* Contwow Wegistews */
#define DA9055_AUX_W_CTWW		0x60
#define DA9055_AUX_W_CTWW		0x61
#define DA9055_MIC_BIAS_CTWW		0x62
#define DA9055_MIC_W_CTWW		0x63
#define DA9055_MIC_W_CTWW		0x64
#define DA9055_MIXIN_W_CTWW		0x65
#define DA9055_MIXIN_W_CTWW		0x66
#define DA9055_ADC_W_CTWW		0x67
#define DA9055_ADC_W_CTWW		0x68
#define DA9055_DAC_W_CTWW		0x69
#define DA9055_DAC_W_CTWW		0x6A
#define DA9055_HP_W_CTWW		0x6B
#define DA9055_HP_W_CTWW		0x6C
#define DA9055_WINE_CTWW		0x6D
#define DA9055_MIXOUT_W_CTWW		0x6E
#define DA9055_MIXOUT_W_CTWW		0x6F

/* Configuwation Wegistews */
#define DA9055_WDO_CTWW			0x90
#define DA9055_IO_CTWW			0x91
#define DA9055_GAIN_WAMP_CTWW		0x92
#define DA9055_MIC_CONFIG		0x93
#define DA9055_PC_COUNT			0x94
#define DA9055_CP_VOW_THWESHOWD1	0x95
#define DA9055_CP_DEWAY			0x96
#define DA9055_CP_DETECTOW		0x97
#define DA9055_AIF_OFFSET		0x98
#define DA9055_DIG_CTWW			0x99
#define DA9055_AWC_CTWW2		0x9A
#define DA9055_AWC_CTWW3		0x9B
#define DA9055_AWC_NOISE		0x9C
#define DA9055_AWC_TAWGET_MIN		0x9D
#define DA9055_AWC_TAWGET_MAX		0x9E
#define DA9055_AWC_GAIN_WIMITS		0x9F
#define DA9055_AWC_ANA_GAIN_WIMITS	0xA0
#define DA9055_AWC_ANTICWIP_CTWW	0xA1
#define DA9055_AWC_ANTICWIP_WEVEW	0xA2
#define DA9055_AWC_OFFSET_OP2M_W	0xA6
#define DA9055_AWC_OFFSET_OP2U_W	0xA7
#define DA9055_AWC_OFFSET_OP2M_W	0xAB
#define DA9055_AWC_OFFSET_OP2U_W	0xAC
#define DA9055_AWC_CIC_OP_WVW_CTWW	0xAD
#define DA9055_AWC_CIC_OP_WVW_DATA	0xAE
#define DA9055_DAC_NG_SETUP_TIME	0xAF
#define DA9055_DAC_NG_OFF_THWESHOWD	0xB0
#define DA9055_DAC_NG_ON_THWESHOWD	0xB1
#define DA9055_DAC_NG_CTWW		0xB2

/* SW bit fiewds */
#define DA9055_SW_8000			(0x1 << 0)
#define DA9055_SW_11025			(0x2 << 0)
#define DA9055_SW_12000			(0x3 << 0)
#define DA9055_SW_16000			(0x5 << 0)
#define DA9055_SW_22050			(0x6 << 0)
#define DA9055_SW_24000			(0x7 << 0)
#define DA9055_SW_32000			(0x9 << 0)
#define DA9055_SW_44100			(0xA << 0)
#define DA9055_SW_48000			(0xB << 0)
#define DA9055_SW_88200			(0xE << 0)
#define DA9055_SW_96000			(0xF << 0)

/* WEFEWENCES bit fiewds */
#define DA9055_BIAS_EN			(1 << 3)
#define DA9055_VMID_EN			(1 << 7)

/* PWW_CTWW bit fiewds */
#define DA9055_PWW_INDIV_10_20_MHZ	(1 << 2)
#define DA9055_PWW_SWM_EN		(1 << 6)
#define DA9055_PWW_EN			(1 << 7)

/* AIF_CWK_MODE bit fiewds */
#define DA9055_AIF_BCWKS_PEW_WCWK_32	(0 << 0)
#define DA9055_AIF_BCWKS_PEW_WCWK_64	(1 << 0)
#define DA9055_AIF_BCWKS_PEW_WCWK_128	(2 << 0)
#define DA9055_AIF_BCWKS_PEW_WCWK_256	(3 << 0)
#define DA9055_AIF_CWK_EN_SWAVE_MODE	(0 << 7)
#define DA9055_AIF_CWK_EN_MASTEW_MODE	(1 << 7)

/* AIF_CTWW bit fiewds */
#define DA9055_AIF_FOWMAT_I2S_MODE	(0 << 0)
#define DA9055_AIF_FOWMAT_WEFT_J	(1 << 0)
#define DA9055_AIF_FOWMAT_WIGHT_J	(2 << 0)
#define DA9055_AIF_FOWMAT_DSP		(3 << 0)
#define DA9055_AIF_WOWD_S16_WE		(0 << 2)
#define DA9055_AIF_WOWD_S20_3WE		(1 << 2)
#define DA9055_AIF_WOWD_S24_WE		(2 << 2)
#define DA9055_AIF_WOWD_S32_WE		(3 << 2)

/* MIC_W_CTWW bit fiewds */
#define DA9055_MIC_W_MUTE_EN		(1 << 6)

/* MIC_W_CTWW bit fiewds */
#define DA9055_MIC_W_MUTE_EN		(1 << 6)

/* MIXIN_W_CTWW bit fiewds */
#define DA9055_MIXIN_W_MIX_EN		(1 << 3)

/* MIXIN_W_CTWW bit fiewds */
#define DA9055_MIXIN_W_MIX_EN		(1 << 3)

/* ADC_W_CTWW bit fiewds */
#define DA9055_ADC_W_EN			(1 << 7)

/* ADC_W_CTWW bit fiewds */
#define DA9055_ADC_W_EN			(1 << 7)

/* DAC_W_CTWW bit fiewds */
#define DA9055_DAC_W_MUTE_EN		(1 << 6)

/* DAC_W_CTWW bit fiewds */
#define DA9055_DAC_W_MUTE_EN		(1 << 6)

/* HP_W_CTWW bit fiewds */
#define DA9055_HP_W_AMP_OE		(1 << 3)

/* HP_W_CTWW bit fiewds */
#define DA9055_HP_W_AMP_OE		(1 << 3)

/* WINE_CTWW bit fiewds */
#define DA9055_WINE_AMP_OE		(1 << 3)

/* MIXOUT_W_CTWW bit fiewds */
#define DA9055_MIXOUT_W_MIX_EN		(1 << 3)

/* MIXOUT_W_CTWW bit fiewds */
#define DA9055_MIXOUT_W_MIX_EN		(1 << 3)

/* MIC bias sewect bit fiewds */
#define DA9055_MICBIAS2_EN		(1 << 6)

/* AWC_CIC_OP_WEVEW_CTWW bit fiewds */
#define DA9055_AWC_DATA_MIDDWE		(2 << 0)
#define DA9055_AWC_DATA_TOP		(3 << 0)
#define DA9055_AWC_CIC_OP_CHANNEW_WEFT	(0 << 7)
#define DA9055_AWC_CIC_OP_CHANNEW_WIGHT	(1 << 7)

#define DA9055_AIF_BCWK_MASK		(3 << 0)
#define DA9055_AIF_CWK_MODE_MASK	(1 << 7)
#define DA9055_AIF_FOWMAT_MASK		(3 << 0)
#define DA9055_AIF_WOWD_WENGTH_MASK	(3 << 2)
#define DA9055_GAIN_WAMPING_EN		(1 << 5)
#define DA9055_MICBIAS_WEVEW_MASK	(3 << 4)

#define DA9055_AWC_OFFSET_15_8		0x00FF00
#define DA9055_AWC_OFFSET_17_16		0x030000
#define DA9055_AWC_AVG_ITEWATIONS	5

stwuct pww_div {
	int fwef;
	int fout;
	u8 fwac_top;
	u8 fwac_bot;
	u8 integew;
	u8 mode;	/* 0 = swave, 1 = mastew */
};

/* PWW divisow tabwe */
static const stwuct pww_div da9055_pww_div[] = {
	/* fow MASTEW mode, fs = 44.1Khz and its hawmonics */
	{11289600, 2822400, 0x00, 0x00, 0x20, 1},	/* MCWK=11.2896Mhz */
	{12000000, 2822400, 0x03, 0x61, 0x1E, 1},	/* MCWK=12Mhz */
	{12288000, 2822400, 0x0C, 0xCC, 0x1D, 1},	/* MCWK=12.288Mhz */
	{13000000, 2822400, 0x19, 0x45, 0x1B, 1},	/* MCWK=13Mhz */
	{13500000, 2822400, 0x18, 0x56, 0x1A, 1},	/* MCWK=13.5Mhz */
	{14400000, 2822400, 0x02, 0xD0, 0x19, 1},	/* MCWK=14.4Mhz */
	{19200000, 2822400, 0x1A, 0x1C, 0x12, 1},	/* MCWK=19.2Mhz */
	{19680000, 2822400, 0x0B, 0x6D, 0x12, 1},	/* MCWK=19.68Mhz */
	{19800000, 2822400, 0x07, 0xDD, 0x12, 1},	/* MCWK=19.8Mhz */
	/* fow MASTEW mode, fs = 48Khz and its hawmonics */
	{11289600, 3072000, 0x1A, 0x8E, 0x22, 1},	/* MCWK=11.2896Mhz */
	{12000000, 3072000, 0x18, 0x93, 0x20, 1},	/* MCWK=12Mhz */
	{12288000, 3072000, 0x00, 0x00, 0x20, 1},	/* MCWK=12.288Mhz */
	{13000000, 3072000, 0x07, 0xEA, 0x1E, 1},	/* MCWK=13Mhz */
	{13500000, 3072000, 0x04, 0x11, 0x1D, 1},	/* MCWK=13.5Mhz */
	{14400000, 3072000, 0x09, 0xD0, 0x1B, 1},	/* MCWK=14.4Mhz */
	{19200000, 3072000, 0x0F, 0x5C, 0x14, 1},	/* MCWK=19.2Mhz */
	{19680000, 3072000, 0x1F, 0x60, 0x13, 1},	/* MCWK=19.68Mhz */
	{19800000, 3072000, 0x1B, 0x80, 0x13, 1},	/* MCWK=19.8Mhz */
	/* fow SWAVE mode with SWM */
	{11289600, 2822400, 0x0D, 0x47, 0x21, 0},	/* MCWK=11.2896Mhz */
	{12000000, 2822400, 0x0D, 0xFA, 0x1F, 0},	/* MCWK=12Mhz */
	{12288000, 2822400, 0x16, 0x66, 0x1E, 0},	/* MCWK=12.288Mhz */
	{13000000, 2822400, 0x00, 0x98, 0x1D, 0},	/* MCWK=13Mhz */
	{13500000, 2822400, 0x1E, 0x33, 0x1B, 0},	/* MCWK=13.5Mhz */
	{14400000, 2822400, 0x06, 0x50, 0x1A, 0},	/* MCWK=14.4Mhz */
	{19200000, 2822400, 0x14, 0xBC, 0x13, 0},	/* MCWK=19.2Mhz */
	{19680000, 2822400, 0x05, 0x66, 0x13, 0},	/* MCWK=19.68Mhz */
	{19800000, 2822400, 0x01, 0xAE, 0x13, 0},	/* MCWK=19.8Mhz  */
};

enum cwk_swc {
	DA9055_CWKSWC_MCWK
};

/* Gain and Vowume */

static const DECWAWE_TWV_DB_WANGE(aux_vow_twv,
	0x0, 0x10, TWV_DB_SCAWE_ITEM(-5400, 0, 0),
	/* -54dB to 15dB */
	0x11, 0x3f, TWV_DB_SCAWE_ITEM(-5400, 150, 0)
);

static const DECWAWE_TWV_DB_WANGE(digitaw_gain_twv,
	0x0, 0x07, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* -78dB to 12dB */
	0x08, 0x7f, TWV_DB_SCAWE_ITEM(-7800, 75, 0)
);

static const DECWAWE_TWV_DB_WANGE(awc_anawog_gain_twv,
	0x0, 0x0, TWV_DB_SCAWE_ITEM(TWV_DB_GAIN_MUTE, 0, 1),
	/* 0dB to 36dB */
	0x01, 0x07, TWV_DB_SCAWE_ITEM(0, 600, 0)
);

static const DECWAWE_TWV_DB_SCAWE(mic_vow_twv, -600, 600, 0);
static const DECWAWE_TWV_DB_SCAWE(mixin_gain_twv, -450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(eq_gain_twv, -1050, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(hp_vow_twv, -5700, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(wineout_vow_twv, -4800, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_thweshowd_twv, -9450, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(awc_gain_twv, 0, 600, 0);

/* ADC and DAC high pass fiwtew cutoff vawue */
static const chaw * const da9055_hpf_cutoff_txt[] = {
	"Fs/24000", "Fs/12000", "Fs/6000", "Fs/3000"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_hpf_cutoff,
			    DA9055_DAC_FIWTEWS1, 4, da9055_hpf_cutoff_txt);

static SOC_ENUM_SINGWE_DECW(da9055_adc_hpf_cutoff,
			    DA9055_ADC_FIWTEWS1, 4, da9055_hpf_cutoff_txt);

/* ADC and DAC voice mode (8kHz) high pass cutoff vawue */
static const chaw * const da9055_vf_cutoff_txt[] = {
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_vf_cutoff,
			    DA9055_DAC_FIWTEWS1, 0, da9055_vf_cutoff_txt);

static SOC_ENUM_SINGWE_DECW(da9055_adc_vf_cutoff,
			    DA9055_ADC_FIWTEWS1, 0, da9055_vf_cutoff_txt);

/* Gain wamping wate vawue */
static const chaw * const da9055_gain_wamping_txt[] = {
	"nominaw wate", "nominaw wate * 4", "nominaw wate * 8",
	"nominaw wate / 8"
};

static SOC_ENUM_SINGWE_DECW(da9055_gain_wamping_wate,
			    DA9055_GAIN_WAMP_CTWW, 0, da9055_gain_wamping_txt);

/* DAC noise gate setup time vawue */
static const chaw * const da9055_dac_ng_setup_time_txt[] = {
	"256 sampwes", "512 sampwes", "1024 sampwes", "2048 sampwes"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_ng_setup_time,
			    DA9055_DAC_NG_SETUP_TIME, 0,
			    da9055_dac_ng_setup_time_txt);

/* DAC noise gate wampup wate vawue */
static const chaw * const da9055_dac_ng_wampup_txt[] = {
	"0.02 ms/dB", "0.16 ms/dB"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_ng_wampup_wate,
			    DA9055_DAC_NG_SETUP_TIME, 2,
			    da9055_dac_ng_wampup_txt);

/* DAC noise gate wampdown wate vawue */
static const chaw * const da9055_dac_ng_wampdown_txt[] = {
	"0.64 ms/dB", "20.48 ms/dB"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_ng_wampdown_wate,
			    DA9055_DAC_NG_SETUP_TIME, 3,
			    da9055_dac_ng_wampdown_txt);

/* DAC soft mute wate vawue */
static const chaw * const da9055_dac_soft_mute_wate_txt[] = {
	"1", "2", "4", "8", "16", "32", "64"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_soft_mute_wate,
			    DA9055_DAC_FIWTEWS5, 4,
			    da9055_dac_soft_mute_wate_txt);

/* DAC wouting sewect */
static const chaw * const da9055_dac_swc_txt[] = {
	"ADC output weft", "ADC output wight", "AIF input weft",
	"AIF input wight"
};

static SOC_ENUM_SINGWE_DECW(da9055_dac_w_swc,
			    DA9055_DIG_WOUTING_DAC, 0, da9055_dac_swc_txt);

static SOC_ENUM_SINGWE_DECW(da9055_dac_w_swc,
			    DA9055_DIG_WOUTING_DAC, 4, da9055_dac_swc_txt);

/* MIC PGA Weft souwce sewect */
static const chaw * const da9055_mic_w_swc_txt[] = {
	"MIC1_P_N", "MIC1_P", "MIC1_N", "MIC2_W"
};

static SOC_ENUM_SINGWE_DECW(da9055_mic_w_swc,
			    DA9055_MIXIN_W_SEWECT, 4, da9055_mic_w_swc_txt);

/* MIC PGA Wight souwce sewect */
static const chaw * const da9055_mic_w_swc_txt[] = {
	"MIC2_W_W", "MIC2_W", "MIC2_W"
};

static SOC_ENUM_SINGWE_DECW(da9055_mic_w_swc,
			    DA9055_MIXIN_W_SEWECT, 4, da9055_mic_w_swc_txt);

/* AWC Input Signaw Twacking wate sewect */
static const chaw * const da9055_signaw_twacking_wate_txt[] = {
	"1/4", "1/16", "1/256", "1/65536"
};

static SOC_ENUM_SINGWE_DECW(da9055_integ_attack_wate,
			    DA9055_AWC_CTWW3, 4,
			    da9055_signaw_twacking_wate_txt);

static SOC_ENUM_SINGWE_DECW(da9055_integ_wewease_wate,
			    DA9055_AWC_CTWW3, 6,
			    da9055_signaw_twacking_wate_txt);

/* AWC Attack Wate sewect */
static const chaw * const da9055_attack_wate_txt[] = {
	"44/fs", "88/fs", "176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs",
	"5632/fs", "11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
};

static SOC_ENUM_SINGWE_DECW(da9055_attack_wate,
			    DA9055_AWC_CTWW2, 0, da9055_attack_wate_txt);

/* AWC Wewease Wate sewect */
static const chaw * const da9055_wewease_wate_txt[] = {
	"176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs", "5632/fs",
	"11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
};

static SOC_ENUM_SINGWE_DECW(da9055_wewease_wate,
			    DA9055_AWC_CTWW2, 4, da9055_wewease_wate_txt);

/* AWC Howd Time sewect */
static const chaw * const da9055_howd_time_txt[] = {
	"62/fs", "124/fs", "248/fs", "496/fs", "992/fs", "1984/fs", "3968/fs",
	"7936/fs", "15872/fs", "31744/fs", "63488/fs", "126976/fs",
	"253952/fs", "507904/fs", "1015808/fs", "2031616/fs"
};

static SOC_ENUM_SINGWE_DECW(da9055_howd_time,
			    DA9055_AWC_CTWW3, 0, da9055_howd_time_txt);

static int da9055_get_awc_data(stwuct snd_soc_component *component, u8 weg_vaw)
{
	int mid_data, top_data;
	int sum = 0;
	u8 itewation;

	fow (itewation = 0; itewation < DA9055_AWC_AVG_ITEWATIONS;
	     itewation++) {
		/* Sewect the weft ow wight channew and captuwe data */
		snd_soc_component_wwite(component, DA9055_AWC_CIC_OP_WVW_CTWW, weg_vaw);

		/* Sewect middwe 8 bits fow wead back fwom data wegistew */
		snd_soc_component_wwite(component, DA9055_AWC_CIC_OP_WVW_CTWW,
			      weg_vaw | DA9055_AWC_DATA_MIDDWE);
		mid_data = snd_soc_component_wead(component, DA9055_AWC_CIC_OP_WVW_DATA);

		/* Sewect top 8 bits fow wead back fwom data wegistew */
		snd_soc_component_wwite(component, DA9055_AWC_CIC_OP_WVW_CTWW,
			      weg_vaw | DA9055_AWC_DATA_TOP);
		top_data = snd_soc_component_wead(component, DA9055_AWC_CIC_OP_WVW_DATA);

		sum += ((mid_data << 8) | (top_data << 16));
	}

	wetuwn sum / DA9055_AWC_AVG_ITEWATIONS;
}

static int da9055_put_awc_sw(stwuct snd_kcontwow *kcontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	u8 weg_vaw, adc_weft, adc_wight, mic_weft, mic_wight;
	int avg_weft_data, avg_wight_data, offset_w, offset_w;

	if (ucontwow->vawue.integew.vawue[0]) {
		/*
		 * Whiwe enabwing AWC (ow AWC sync mode), cawibwation of the DC
		 * offsets must be done fiwst
		 */

		/* Save cuwwent vawues fwom Mic contwow wegistews */
		mic_weft = snd_soc_component_wead(component, DA9055_MIC_W_CTWW);
		mic_wight = snd_soc_component_wead(component, DA9055_MIC_W_CTWW);

		/* Mute Mic PGA Weft and Wight */
		snd_soc_component_update_bits(component, DA9055_MIC_W_CTWW,
				    DA9055_MIC_W_MUTE_EN, DA9055_MIC_W_MUTE_EN);
		snd_soc_component_update_bits(component, DA9055_MIC_W_CTWW,
				    DA9055_MIC_W_MUTE_EN, DA9055_MIC_W_MUTE_EN);

		/* Save cuwwent vawues fwom ADC contwow wegistews */
		adc_weft = snd_soc_component_wead(component, DA9055_ADC_W_CTWW);
		adc_wight = snd_soc_component_wead(component, DA9055_ADC_W_CTWW);

		/* Enabwe ADC Weft and Wight */
		snd_soc_component_update_bits(component, DA9055_ADC_W_CTWW,
				    DA9055_ADC_W_EN, DA9055_ADC_W_EN);
		snd_soc_component_update_bits(component, DA9055_ADC_W_CTWW,
				    DA9055_ADC_W_EN, DA9055_ADC_W_EN);

		/* Cawcuwate avewage fow Weft and Wight data */
		/* Weft Data */
		avg_weft_data = da9055_get_awc_data(component,
				DA9055_AWC_CIC_OP_CHANNEW_WEFT);
		/* Wight Data */
		avg_wight_data = da9055_get_awc_data(component,
				 DA9055_AWC_CIC_OP_CHANNEW_WIGHT);

		/* Cawcuwate DC offset */
		offset_w = -avg_weft_data;
		offset_w = -avg_wight_data;

		weg_vaw = (offset_w & DA9055_AWC_OFFSET_15_8) >> 8;
		snd_soc_component_wwite(component, DA9055_AWC_OFFSET_OP2M_W, weg_vaw);
		weg_vaw = (offset_w & DA9055_AWC_OFFSET_17_16) >> 16;
		snd_soc_component_wwite(component, DA9055_AWC_OFFSET_OP2U_W, weg_vaw);

		weg_vaw = (offset_w & DA9055_AWC_OFFSET_15_8) >> 8;
		snd_soc_component_wwite(component, DA9055_AWC_OFFSET_OP2M_W, weg_vaw);
		weg_vaw = (offset_w & DA9055_AWC_OFFSET_17_16) >> 16;
		snd_soc_component_wwite(component, DA9055_AWC_OFFSET_OP2U_W, weg_vaw);

		/* Westowe owiginaw vawues of ADC contwow wegistews */
		snd_soc_component_wwite(component, DA9055_ADC_W_CTWW, adc_weft);
		snd_soc_component_wwite(component, DA9055_ADC_W_CTWW, adc_wight);

		/* Westowe owiginaw vawues of Mic contwow wegistews */
		snd_soc_component_wwite(component, DA9055_MIC_W_CTWW, mic_weft);
		snd_soc_component_wwite(component, DA9055_MIC_W_CTWW, mic_wight);
	}

	wetuwn snd_soc_put_vowsw(kcontwow, ucontwow);
}

static const stwuct snd_kcontwow_new da9055_snd_contwows[] = {

	/* Vowume contwows */
	SOC_DOUBWE_W_TWV("Mic Vowume",
			 DA9055_MIC_W_GAIN, DA9055_MIC_W_GAIN,
			 0, 0x7, 0, mic_vow_twv),
	SOC_DOUBWE_W_TWV("Aux Vowume",
			 DA9055_AUX_W_GAIN, DA9055_AUX_W_GAIN,
			 0, 0x3f, 0, aux_vow_twv),
	SOC_DOUBWE_W_TWV("Mixin PGA Vowume",
			 DA9055_MIXIN_W_GAIN, DA9055_MIXIN_W_GAIN,
			 0, 0xf, 0, mixin_gain_twv),
	SOC_DOUBWE_W_TWV("ADC Vowume",
			 DA9055_ADC_W_GAIN, DA9055_ADC_W_GAIN,
			 0, 0x7f, 0, digitaw_gain_twv),

	SOC_DOUBWE_W_TWV("DAC Vowume",
			 DA9055_DAC_W_GAIN, DA9055_DAC_W_GAIN,
			 0, 0x7f, 0, digitaw_gain_twv),
	SOC_DOUBWE_W_TWV("Headphone Vowume",
			 DA9055_HP_W_GAIN, DA9055_HP_W_GAIN,
			 0, 0x3f, 0, hp_vow_twv),
	SOC_SINGWE_TWV("Wineout Vowume", DA9055_WINE_GAIN, 0, 0x3f, 0,
		       wineout_vow_twv),

	/* DAC Equawizew contwows */
	SOC_SINGWE("DAC EQ Switch", DA9055_DAC_FIWTEWS4, 7, 1, 0),
	SOC_SINGWE_TWV("DAC EQ1 Vowume", DA9055_DAC_FIWTEWS2, 0, 0xf, 0,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ2 Vowume", DA9055_DAC_FIWTEWS2, 4, 0xf, 0,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ3 Vowume", DA9055_DAC_FIWTEWS3, 0, 0xf, 0,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ4 Vowume", DA9055_DAC_FIWTEWS3, 4, 0xf, 0,
		       eq_gain_twv),
	SOC_SINGWE_TWV("DAC EQ5 Vowume", DA9055_DAC_FIWTEWS4, 0, 0xf, 0,
		       eq_gain_twv),

	/* High Pass Fiwtew and Voice Mode contwows */
	SOC_SINGWE("ADC HPF Switch", DA9055_ADC_FIWTEWS1, 7, 1, 0),
	SOC_ENUM("ADC HPF Cutoff", da9055_adc_hpf_cutoff),
	SOC_SINGWE("ADC Voice Mode Switch", DA9055_ADC_FIWTEWS1, 3, 1, 0),
	SOC_ENUM("ADC Voice Cutoff", da9055_adc_vf_cutoff),

	SOC_SINGWE("DAC HPF Switch", DA9055_DAC_FIWTEWS1, 7, 1, 0),
	SOC_ENUM("DAC HPF Cutoff", da9055_dac_hpf_cutoff),
	SOC_SINGWE("DAC Voice Mode Switch", DA9055_DAC_FIWTEWS1, 3, 1, 0),
	SOC_ENUM("DAC Voice Cutoff", da9055_dac_vf_cutoff),

	/* Mute contwows */
	SOC_DOUBWE_W("Mic Switch", DA9055_MIC_W_CTWW,
		     DA9055_MIC_W_CTWW, 6, 1, 0),
	SOC_DOUBWE_W("Aux Switch", DA9055_AUX_W_CTWW,
		     DA9055_AUX_W_CTWW, 6, 1, 0),
	SOC_DOUBWE_W("Mixin PGA Switch", DA9055_MIXIN_W_CTWW,
		     DA9055_MIXIN_W_CTWW, 6, 1, 0),
	SOC_DOUBWE_W("ADC Switch", DA9055_ADC_W_CTWW,
		     DA9055_ADC_W_CTWW, 6, 1, 0),
	SOC_DOUBWE_W("Headphone Switch", DA9055_HP_W_CTWW,
		     DA9055_HP_W_CTWW, 6, 1, 0),
	SOC_SINGWE("Wineout Switch", DA9055_WINE_CTWW, 6, 1, 0),
	SOC_SINGWE("DAC Soft Mute Switch", DA9055_DAC_FIWTEWS5, 7, 1, 0),
	SOC_ENUM("DAC Soft Mute Wate", da9055_dac_soft_mute_wate),

	/* Zewo Cwoss contwows */
	SOC_DOUBWE_W("Aux ZC Switch", DA9055_AUX_W_CTWW,
		     DA9055_AUX_W_CTWW, 4, 1, 0),
	SOC_DOUBWE_W("Mixin PGA ZC Switch", DA9055_MIXIN_W_CTWW,
		     DA9055_MIXIN_W_CTWW, 4, 1, 0),
	SOC_DOUBWE_W("Headphone ZC Switch", DA9055_HP_W_CTWW,
		     DA9055_HP_W_CTWW, 4, 1, 0),
	SOC_SINGWE("Wineout ZC Switch", DA9055_WINE_CTWW, 4, 1, 0),

	/* Gain Wamping contwows */
	SOC_DOUBWE_W("Aux Gain Wamping Switch", DA9055_AUX_W_CTWW,
		     DA9055_AUX_W_CTWW, 5, 1, 0),
	SOC_DOUBWE_W("Mixin Gain Wamping Switch", DA9055_MIXIN_W_CTWW,
		     DA9055_MIXIN_W_CTWW, 5, 1, 0),
	SOC_DOUBWE_W("ADC Gain Wamping Switch", DA9055_ADC_W_CTWW,
		     DA9055_ADC_W_CTWW, 5, 1, 0),
	SOC_DOUBWE_W("DAC Gain Wamping Switch", DA9055_DAC_W_CTWW,
		     DA9055_DAC_W_CTWW, 5, 1, 0),
	SOC_DOUBWE_W("Headphone Gain Wamping Switch", DA9055_HP_W_CTWW,
		     DA9055_HP_W_CTWW, 5, 1, 0),
	SOC_SINGWE("Wineout Gain Wamping Switch", DA9055_WINE_CTWW, 5, 1, 0),
	SOC_ENUM("Gain Wamping Wate", da9055_gain_wamping_wate),

	/* DAC Noise Gate contwows */
	SOC_SINGWE("DAC NG Switch", DA9055_DAC_NG_CTWW, 7, 1, 0),
	SOC_SINGWE("DAC NG ON Thweshowd", DA9055_DAC_NG_ON_THWESHOWD,
		   0, 0x7, 0),
	SOC_SINGWE("DAC NG OFF Thweshowd", DA9055_DAC_NG_OFF_THWESHOWD,
		   0, 0x7, 0),
	SOC_ENUM("DAC NG Setup Time", da9055_dac_ng_setup_time),
	SOC_ENUM("DAC NG Wampup Wate", da9055_dac_ng_wampup_wate),
	SOC_ENUM("DAC NG Wampdown Wate", da9055_dac_ng_wampdown_wate),

	/* DAC Invewtion contwow */
	SOC_SINGWE("DAC Weft Invewt", DA9055_DIG_CTWW, 3, 1, 0),
	SOC_SINGWE("DAC Wight Invewt", DA9055_DIG_CTWW, 7, 1, 0),

	/* DMIC contwows */
	SOC_DOUBWE_W("DMIC Switch", DA9055_MIXIN_W_SEWECT,
		     DA9055_MIXIN_W_SEWECT, 7, 1, 0),

	/* AWC Contwows */
	SOC_DOUBWE_EXT("AWC Switch", DA9055_AWC_CTWW1, 3, 7, 1, 0,
		       snd_soc_get_vowsw, da9055_put_awc_sw),
	SOC_SINGWE_EXT("AWC Sync Mode Switch", DA9055_AWC_CTWW1, 1, 1, 0,
		       snd_soc_get_vowsw, da9055_put_awc_sw),
	SOC_SINGWE("AWC Offset Switch", DA9055_AWC_CTWW1, 0, 1, 0),
	SOC_SINGWE("AWC Anticwip Mode Switch", DA9055_AWC_ANTICWIP_CTWW,
		   7, 1, 0),
	SOC_SINGWE("AWC Anticwip Wevew", DA9055_AWC_ANTICWIP_WEVEW,
		   0, 0x7f, 0),
	SOC_SINGWE_TWV("AWC Min Thweshowd Vowume", DA9055_AWC_TAWGET_MIN,
		       0, 0x3f, 1, awc_thweshowd_twv),
	SOC_SINGWE_TWV("AWC Max Thweshowd Vowume", DA9055_AWC_TAWGET_MAX,
		       0, 0x3f, 1, awc_thweshowd_twv),
	SOC_SINGWE_TWV("AWC Noise Thweshowd Vowume", DA9055_AWC_NOISE,
		       0, 0x3f, 1, awc_thweshowd_twv),
	SOC_SINGWE_TWV("AWC Max Gain Vowume", DA9055_AWC_GAIN_WIMITS,
		       4, 0xf, 0, awc_gain_twv),
	SOC_SINGWE_TWV("AWC Max Attenuation Vowume", DA9055_AWC_GAIN_WIMITS,
		       0, 0xf, 0, awc_gain_twv),
	SOC_SINGWE_TWV("AWC Min Anawog Gain Vowume",
		       DA9055_AWC_ANA_GAIN_WIMITS,
		       0, 0x7, 0, awc_anawog_gain_twv),
	SOC_SINGWE_TWV("AWC Max Anawog Gain Vowume",
		       DA9055_AWC_ANA_GAIN_WIMITS,
		       4, 0x7, 0, awc_anawog_gain_twv),
	SOC_ENUM("AWC Attack Wate", da9055_attack_wate),
	SOC_ENUM("AWC Wewease Wate", da9055_wewease_wate),
	SOC_ENUM("AWC Howd Time", da9055_howd_time),
	/*
	 * Wate at which input signaw envewope is twacked as the signaw gets
	 * wawgew
	 */
	SOC_ENUM("AWC Integ Attack Wate", da9055_integ_attack_wate),
	/*
	 * Wate at which input signaw envewope is twacked as the signaw gets
	 * smawwew
	 */
	SOC_ENUM("AWC Integ Wewease Wate", da9055_integ_wewease_wate),
};

/* DAPM Contwows */

/* Mic PGA Weft Souwce */
static const stwuct snd_kcontwow_new da9055_mic_w_mux_contwows =
SOC_DAPM_ENUM("Woute", da9055_mic_w_swc);

/* Mic PGA Wight Souwce */
static const stwuct snd_kcontwow_new da9055_mic_w_mux_contwows =
SOC_DAPM_ENUM("Woute", da9055_mic_w_swc);

/* In Mixew Weft */
static const stwuct snd_kcontwow_new da9055_dapm_mixinw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Weft Switch", DA9055_MIXIN_W_SEWECT, 0, 1, 0),
	SOC_DAPM_SINGWE("Mic Weft Switch", DA9055_MIXIN_W_SEWECT, 1, 1, 0),
	SOC_DAPM_SINGWE("Mic Wight Switch", DA9055_MIXIN_W_SEWECT, 2, 1, 0),
};

/* In Mixew Wight */
static const stwuct snd_kcontwow_new da9055_dapm_mixinw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Wight Switch", DA9055_MIXIN_W_SEWECT, 0, 1, 0),
	SOC_DAPM_SINGWE("Mic Wight Switch", DA9055_MIXIN_W_SEWECT, 1, 1, 0),
	SOC_DAPM_SINGWE("Mic Weft Switch", DA9055_MIXIN_W_SEWECT, 2, 1, 0),
	SOC_DAPM_SINGWE("Mixin Weft Switch", DA9055_MIXIN_W_SEWECT, 3, 1, 0),
};

/* DAC Weft Souwce */
static const stwuct snd_kcontwow_new da9055_dac_w_mux_contwows =
SOC_DAPM_ENUM("Woute", da9055_dac_w_swc);

/* DAC Wight Souwce */
static const stwuct snd_kcontwow_new da9055_dac_w_mux_contwows =
SOC_DAPM_ENUM("Woute", da9055_dac_w_swc);

/* Out Mixew Weft */
static const stwuct snd_kcontwow_new da9055_dapm_mixoutw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Weft Switch", DA9055_MIXOUT_W_SEWECT, 0, 1, 0),
	SOC_DAPM_SINGWE("Mixin Weft Switch", DA9055_MIXOUT_W_SEWECT, 1, 1, 0),
	SOC_DAPM_SINGWE("Mixin Wight Switch", DA9055_MIXOUT_W_SEWECT, 2, 1, 0),
	SOC_DAPM_SINGWE("DAC Weft Switch", DA9055_MIXOUT_W_SEWECT, 3, 1, 0),
	SOC_DAPM_SINGWE("Aux Weft Invewt Switch", DA9055_MIXOUT_W_SEWECT,
			4, 1, 0),
	SOC_DAPM_SINGWE("Mixin Weft Invewt Switch", DA9055_MIXOUT_W_SEWECT,
			5, 1, 0),
	SOC_DAPM_SINGWE("Mixin Wight Invewt Switch", DA9055_MIXOUT_W_SEWECT,
			6, 1, 0),
};

/* Out Mixew Wight */
static const stwuct snd_kcontwow_new da9055_dapm_mixoutw_contwows[] = {
	SOC_DAPM_SINGWE("Aux Wight Switch", DA9055_MIXOUT_W_SEWECT, 0, 1, 0),
	SOC_DAPM_SINGWE("Mixin Wight Switch", DA9055_MIXOUT_W_SEWECT, 1, 1, 0),
	SOC_DAPM_SINGWE("Mixin Weft Switch", DA9055_MIXOUT_W_SEWECT, 2, 1, 0),
	SOC_DAPM_SINGWE("DAC Wight Switch", DA9055_MIXOUT_W_SEWECT, 3, 1, 0),
	SOC_DAPM_SINGWE("Aux Wight Invewt Switch", DA9055_MIXOUT_W_SEWECT,
			4, 1, 0),
	SOC_DAPM_SINGWE("Mixin Wight Invewt Switch", DA9055_MIXOUT_W_SEWECT,
			5, 1, 0),
	SOC_DAPM_SINGWE("Mixin Weft Invewt Switch", DA9055_MIXOUT_W_SEWECT,
			6, 1, 0),
};

/* Headphone Output Enabwe */
static const stwuct snd_kcontwow_new da9055_dapm_hp_w_contwow =
SOC_DAPM_SINGWE("Switch", DA9055_HP_W_CTWW, 3, 1, 0);

static const stwuct snd_kcontwow_new da9055_dapm_hp_w_contwow =
SOC_DAPM_SINGWE("Switch", DA9055_HP_W_CTWW, 3, 1, 0);

/* Wineout Output Enabwe */
static const stwuct snd_kcontwow_new da9055_dapm_wineout_contwow =
SOC_DAPM_SINGWE("Switch", DA9055_WINE_CTWW, 3, 1, 0);

/* DAPM widgets */
static const stwuct snd_soc_dapm_widget da9055_dapm_widgets[] = {
	/* Input Side */

	/* Input Wines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("AUXW"),
	SND_SOC_DAPM_INPUT("AUXW"),

	/* MUXs fow Mic PGA souwce sewection */
	SND_SOC_DAPM_MUX("Mic Weft Souwce", SND_SOC_NOPM, 0, 0,
			 &da9055_mic_w_mux_contwows),
	SND_SOC_DAPM_MUX("Mic Wight Souwce", SND_SOC_NOPM, 0, 0,
			 &da9055_mic_w_mux_contwows),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic Weft", DA9055_MIC_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic Wight", DA9055_MIC_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux Weft", DA9055_AUX_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Aux Wight", DA9055_AUX_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MIXIN Weft", DA9055_MIXIN_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MIXIN Wight", DA9055_MIXIN_W_CTWW, 7, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Mic Bias", DA9055_MIC_BIAS_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("AIF", DA9055_AIF_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("Chawge Pump", DA9055_CP_CTWW, 7, 0, NUWW, 0),

	/* Input Mixews */
	SND_SOC_DAPM_MIXEW("In Mixew Weft", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixinw_contwows[0],
			   AWWAY_SIZE(da9055_dapm_mixinw_contwows)),
	SND_SOC_DAPM_MIXEW("In Mixew Wight", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixinw_contwows[0],
			   AWWAY_SIZE(da9055_dapm_mixinw_contwows)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Weft", "Captuwe", DA9055_ADC_W_CTWW, 7, 0),
	SND_SOC_DAPM_ADC("ADC Wight", "Captuwe", DA9055_ADC_W_CTWW, 7, 0),

	/* Output Side */

	/* MUXs fow DAC souwce sewection */
	SND_SOC_DAPM_MUX("DAC Weft Souwce", SND_SOC_NOPM, 0, 0,
			 &da9055_dac_w_mux_contwows),
	SND_SOC_DAPM_MUX("DAC Wight Souwce", SND_SOC_NOPM, 0, 0,
			 &da9055_dac_w_mux_contwows),

	/* AIF input */
	SND_SOC_DAPM_AIF_IN("AIFIN Weft", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFIN Wight", "Pwayback", 0, SND_SOC_NOPM, 0, 0),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC Weft", "Pwayback", DA9055_DAC_W_CTWW, 7, 0),
	SND_SOC_DAPM_DAC("DAC Wight", "Pwayback", DA9055_DAC_W_CTWW, 7, 0),

	/* Output Mixews */
	SND_SOC_DAPM_MIXEW("Out Mixew Weft", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixoutw_contwows[0],
			   AWWAY_SIZE(da9055_dapm_mixoutw_contwows)),
	SND_SOC_DAPM_MIXEW("Out Mixew Wight", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixoutw_contwows[0],
			   AWWAY_SIZE(da9055_dapm_mixoutw_contwows)),

	/* Output Enabwe Switches */
	SND_SOC_DAPM_SWITCH("Headphone Weft Enabwe", SND_SOC_NOPM, 0, 0,
			    &da9055_dapm_hp_w_contwow),
	SND_SOC_DAPM_SWITCH("Headphone Wight Enabwe", SND_SOC_NOPM, 0, 0,
			    &da9055_dapm_hp_w_contwow),
	SND_SOC_DAPM_SWITCH("Wineout Enabwe", SND_SOC_NOPM, 0, 0,
			    &da9055_dapm_wineout_contwow),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("MIXOUT Weft", DA9055_MIXOUT_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("MIXOUT Wight", DA9055_MIXOUT_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wineout", DA9055_WINE_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Headphone Weft", DA9055_HP_W_CTWW, 7, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Headphone Wight", DA9055_HP_W_CTWW, 7, 0, NUWW, 0),

	/* Output Wines */
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("WINE"),
};

/* DAPM audio woute definition */
static const stwuct snd_soc_dapm_woute da9055_audio_map[] = {
	/* Dest       Connecting Widget    souwce */

	/* Input path */
	{"Mic Weft Souwce", "MIC1_P_N", "MIC1"},
	{"Mic Weft Souwce", "MIC1_P", "MIC1"},
	{"Mic Weft Souwce", "MIC1_N", "MIC1"},
	{"Mic Weft Souwce", "MIC2_W", "MIC2"},

	{"Mic Wight Souwce", "MIC2_W_W", "MIC2"},
	{"Mic Wight Souwce", "MIC2_W", "MIC2"},
	{"Mic Wight Souwce", "MIC2_W", "MIC2"},

	{"Mic Weft", NUWW, "Mic Weft Souwce"},
	{"Mic Wight", NUWW, "Mic Wight Souwce"},

	{"Aux Weft", NUWW, "AUXW"},
	{"Aux Wight", NUWW, "AUXW"},

	{"In Mixew Weft", "Mic Weft Switch", "Mic Weft"},
	{"In Mixew Weft", "Mic Wight Switch", "Mic Wight"},
	{"In Mixew Weft", "Aux Weft Switch", "Aux Weft"},

	{"In Mixew Wight", "Mic Wight Switch", "Mic Wight"},
	{"In Mixew Wight", "Mic Weft Switch", "Mic Weft"},
	{"In Mixew Wight", "Aux Wight Switch", "Aux Wight"},
	{"In Mixew Wight", "Mixin Weft Switch", "MIXIN Weft"},

	{"MIXIN Weft", NUWW, "In Mixew Weft"},
	{"ADC Weft", NUWW, "MIXIN Weft"},

	{"MIXIN Wight", NUWW, "In Mixew Wight"},
	{"ADC Wight", NUWW, "MIXIN Wight"},

	{"ADC Weft", NUWW, "AIF"},
	{"ADC Wight", NUWW, "AIF"},

	/* Output path */
	{"AIFIN Weft", NUWW, "AIF"},
	{"AIFIN Wight", NUWW, "AIF"},

	{"DAC Weft Souwce", "ADC output weft", "ADC Weft"},
	{"DAC Weft Souwce", "ADC output wight", "ADC Wight"},
	{"DAC Weft Souwce", "AIF input weft", "AIFIN Weft"},
	{"DAC Weft Souwce", "AIF input wight", "AIFIN Wight"},

	{"DAC Wight Souwce", "ADC output weft", "ADC Weft"},
	{"DAC Wight Souwce", "ADC output wight", "ADC Wight"},
	{"DAC Wight Souwce", "AIF input weft", "AIFIN Weft"},
	{"DAC Wight Souwce", "AIF input wight", "AIFIN Wight"},

	{"DAC Weft", NUWW, "DAC Weft Souwce"},
	{"DAC Wight", NUWW, "DAC Wight Souwce"},

	{"Out Mixew Weft", "Aux Weft Switch", "Aux Weft"},
	{"Out Mixew Weft", "Mixin Weft Switch", "MIXIN Weft"},
	{"Out Mixew Weft", "Mixin Wight Switch", "MIXIN Wight"},
	{"Out Mixew Weft", "Aux Weft Invewt Switch", "Aux Weft"},
	{"Out Mixew Weft", "Mixin Weft Invewt Switch", "MIXIN Weft"},
	{"Out Mixew Weft", "Mixin Wight Invewt Switch", "MIXIN Wight"},
	{"Out Mixew Weft", "DAC Weft Switch", "DAC Weft"},

	{"Out Mixew Wight", "Aux Wight Switch", "Aux Wight"},
	{"Out Mixew Wight", "Mixin Wight Switch", "MIXIN Wight"},
	{"Out Mixew Wight", "Mixin Weft Switch", "MIXIN Weft"},
	{"Out Mixew Wight", "Aux Wight Invewt Switch", "Aux Wight"},
	{"Out Mixew Wight", "Mixin Wight Invewt Switch", "MIXIN Wight"},
	{"Out Mixew Wight", "Mixin Weft Invewt Switch", "MIXIN Weft"},
	{"Out Mixew Wight", "DAC Wight Switch", "DAC Wight"},

	{"MIXOUT Weft", NUWW, "Out Mixew Weft"},
	{"Headphone Weft Enabwe", "Switch", "MIXOUT Weft"},
	{"Headphone Weft", NUWW, "Headphone Weft Enabwe"},
	{"Headphone Weft", NUWW, "Chawge Pump"},
	{"HPW", NUWW, "Headphone Weft"},

	{"MIXOUT Wight", NUWW, "Out Mixew Wight"},
	{"Headphone Wight Enabwe", "Switch", "MIXOUT Wight"},
	{"Headphone Wight", NUWW, "Headphone Wight Enabwe"},
	{"Headphone Wight", NUWW, "Chawge Pump"},
	{"HPW", NUWW, "Headphone Wight"},

	{"MIXOUT Wight", NUWW, "Out Mixew Wight"},
	{"Wineout Enabwe", "Switch", "MIXOUT Wight"},
	{"Wineout", NUWW, "Wineout Enabwe"},
	{"WINE", NUWW, "Wineout"},
};

/* Codec pwivate data */
stwuct da9055_pwiv {
	stwuct wegmap *wegmap;
	unsigned int mcwk_wate;
	int mastew;
	stwuct da9055_pwatfowm_data *pdata;
};

static const stwuct weg_defauwt da9055_weg_defauwts[] = {
	{ 0x21, 0x10 },
	{ 0x22, 0x0A },
	{ 0x23, 0x00 },
	{ 0x24, 0x00 },
	{ 0x25, 0x00 },
	{ 0x26, 0x00 },
	{ 0x27, 0x0C },
	{ 0x28, 0x01 },
	{ 0x29, 0x08 },
	{ 0x2A, 0x32 },
	{ 0x2B, 0x00 },
	{ 0x30, 0x35 },
	{ 0x31, 0x35 },
	{ 0x32, 0x00 },
	{ 0x33, 0x00 },
	{ 0x34, 0x03 },
	{ 0x35, 0x03 },
	{ 0x36, 0x6F },
	{ 0x37, 0x6F },
	{ 0x38, 0x80 },
	{ 0x39, 0x01 },
	{ 0x3A, 0x01 },
	{ 0x40, 0x00 },
	{ 0x41, 0x88 },
	{ 0x42, 0x88 },
	{ 0x43, 0x08 },
	{ 0x44, 0x80 },
	{ 0x45, 0x6F },
	{ 0x46, 0x6F },
	{ 0x47, 0x61 },
	{ 0x48, 0x35 },
	{ 0x49, 0x35 },
	{ 0x4A, 0x35 },
	{ 0x4B, 0x00 },
	{ 0x4C, 0x00 },
	{ 0x60, 0x44 },
	{ 0x61, 0x44 },
	{ 0x62, 0x00 },
	{ 0x63, 0x40 },
	{ 0x64, 0x40 },
	{ 0x65, 0x40 },
	{ 0x66, 0x40 },
	{ 0x67, 0x40 },
	{ 0x68, 0x40 },
	{ 0x69, 0x48 },
	{ 0x6A, 0x40 },
	{ 0x6B, 0x41 },
	{ 0x6C, 0x40 },
	{ 0x6D, 0x40 },
	{ 0x6E, 0x10 },
	{ 0x6F, 0x10 },
	{ 0x90, 0x80 },
	{ 0x92, 0x02 },
	{ 0x93, 0x00 },
	{ 0x99, 0x00 },
	{ 0x9A, 0x00 },
	{ 0x9B, 0x00 },
	{ 0x9C, 0x3F },
	{ 0x9D, 0x00 },
	{ 0x9E, 0x3F },
	{ 0x9F, 0xFF },
	{ 0xA0, 0x71 },
	{ 0xA1, 0x00 },
	{ 0xA2, 0x00 },
	{ 0xA6, 0x00 },
	{ 0xA7, 0x00 },
	{ 0xAB, 0x00 },
	{ 0xAC, 0x00 },
	{ 0xAD, 0x00 },
	{ 0xAF, 0x08 },
	{ 0xB0, 0x00 },
	{ 0xB1, 0x00 },
	{ 0xB2, 0x00 },
};

static boow da9055_vowatiwe_wegistew(stwuct device *dev,
				     unsigned int weg)
{
	switch (weg) {
	case DA9055_STATUS1:
	case DA9055_PWW_STATUS:
	case DA9055_AUX_W_GAIN_STATUS:
	case DA9055_AUX_W_GAIN_STATUS:
	case DA9055_MIC_W_GAIN_STATUS:
	case DA9055_MIC_W_GAIN_STATUS:
	case DA9055_MIXIN_W_GAIN_STATUS:
	case DA9055_MIXIN_W_GAIN_STATUS:
	case DA9055_ADC_W_GAIN_STATUS:
	case DA9055_ADC_W_GAIN_STATUS:
	case DA9055_DAC_W_GAIN_STATUS:
	case DA9055_DAC_W_GAIN_STATUS:
	case DA9055_HP_W_GAIN_STATUS:
	case DA9055_HP_W_GAIN_STATUS:
	case DA9055_WINE_GAIN_STATUS:
	case DA9055_AWC_CIC_OP_WVW_DATA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* Set DAI wowd wength */
static int da9055_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct da9055_pwiv *da9055 = snd_soc_component_get_dwvdata(component);
	u8 aif_ctww, fs;
	u32 syscwk;

	switch (pawams_width(pawams)) {
	case 16:
		aif_ctww = DA9055_AIF_WOWD_S16_WE;
		bweak;
	case 20:
		aif_ctww = DA9055_AIF_WOWD_S20_3WE;
		bweak;
	case 24:
		aif_ctww = DA9055_AIF_WOWD_S24_WE;
		bweak;
	case 32:
		aif_ctww = DA9055_AIF_WOWD_S32_WE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set AIF fowmat */
	snd_soc_component_update_bits(component, DA9055_AIF_CTWW, DA9055_AIF_WOWD_WENGTH_MASK,
			    aif_ctww);

	switch (pawams_wate(pawams)) {
	case 8000:
		fs		= DA9055_SW_8000;
		syscwk		= 3072000;
		bweak;
	case 11025:
		fs		= DA9055_SW_11025;
		syscwk		= 2822400;
		bweak;
	case 12000:
		fs		= DA9055_SW_12000;
		syscwk		= 3072000;
		bweak;
	case 16000:
		fs		= DA9055_SW_16000;
		syscwk		= 3072000;
		bweak;
	case 22050:
		fs		= DA9055_SW_22050;
		syscwk		= 2822400;
		bweak;
	case 32000:
		fs		= DA9055_SW_32000;
		syscwk		= 3072000;
		bweak;
	case 44100:
		fs		= DA9055_SW_44100;
		syscwk		= 2822400;
		bweak;
	case 48000:
		fs		= DA9055_SW_48000;
		syscwk		= 3072000;
		bweak;
	case 88200:
		fs		= DA9055_SW_88200;
		syscwk		= 2822400;
		bweak;
	case 96000:
		fs		= DA9055_SW_96000;
		syscwk		= 3072000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (da9055->mcwk_wate) {
		/* PWW Mode, Wwite actuaw FS */
		snd_soc_component_wwite(component, DA9055_SW, fs);
	} ewse {
		/*
		 * Non-PWW Mode
		 * When PWW is bypassed, chip assumes constant MCWK of
		 * 12.288MHz and uses sampwe wate vawue to divide this MCWK
		 * to dewive its sys cwk. As sys cwk has to be 256 * Fs, we
		 * need to wwite constant sampwe wate i.e. 48KHz.
		 */
		snd_soc_component_wwite(component, DA9055_SW, DA9055_SW_48000);
	}

	if (da9055->mcwk_wate && (da9055->mcwk_wate != syscwk)) {
		/* PWW Mode */
		if (!da9055->mastew) {
			/* PWW swave mode, enabwe PWW and awso SWM */
			snd_soc_component_update_bits(component, DA9055_PWW_CTWW,
					    DA9055_PWW_EN | DA9055_PWW_SWM_EN,
					    DA9055_PWW_EN | DA9055_PWW_SWM_EN);
		} ewse {
			/* PWW mastew mode, onwy enabwe PWW */
			snd_soc_component_update_bits(component, DA9055_PWW_CTWW,
					    DA9055_PWW_EN, DA9055_PWW_EN);
		}
	} ewse {
		/* Non PWW Mode, disabwe PWW */
		snd_soc_component_update_bits(component, DA9055_PWW_CTWW, DA9055_PWW_EN, 0);
	}

	wetuwn 0;
}

/* Set DAI mode and Fowmat */
static int da9055_set_dai_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da9055_pwiv *da9055 = snd_soc_component_get_dwvdata(component);
	u8 aif_cwk_mode, aif_ctww, mode;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		/* DA9055 in I2S Mastew Mode */
		mode = 1;
		aif_cwk_mode = DA9055_AIF_CWK_EN_MASTEW_MODE;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		/* DA9055 in I2S Swave Mode */
		mode = 0;
		aif_cwk_mode = DA9055_AIF_CWK_EN_SWAVE_MODE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Don't awwow change of mode if PWW is enabwed */
	if ((snd_soc_component_wead(component, DA9055_PWW_CTWW) & DA9055_PWW_EN) &&
	    (da9055->mastew != mode))
		wetuwn -EINVAW;

	da9055->mastew = mode;

	/* Onwy I2S is suppowted */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		aif_ctww = DA9055_AIF_FOWMAT_I2S_MODE;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		aif_ctww = DA9055_AIF_FOWMAT_WEFT_J;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		aif_ctww = DA9055_AIF_FOWMAT_WIGHT_J;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		aif_ctww = DA9055_AIF_FOWMAT_DSP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* By defauwt onwy 32 BCWK pew WCWK is suppowted */
	aif_cwk_mode |= DA9055_AIF_BCWKS_PEW_WCWK_32;

	snd_soc_component_update_bits(component, DA9055_AIF_CWK_MODE,
			    (DA9055_AIF_CWK_MODE_MASK | DA9055_AIF_BCWK_MASK),
			    aif_cwk_mode);
	snd_soc_component_update_bits(component, DA9055_AIF_CTWW, DA9055_AIF_FOWMAT_MASK,
			    aif_ctww);
	wetuwn 0;
}

static int da9055_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;

	if (mute) {
		snd_soc_component_update_bits(component, DA9055_DAC_W_CTWW,
				    DA9055_DAC_W_MUTE_EN, DA9055_DAC_W_MUTE_EN);
		snd_soc_component_update_bits(component, DA9055_DAC_W_CTWW,
				    DA9055_DAC_W_MUTE_EN, DA9055_DAC_W_MUTE_EN);
	} ewse {
		snd_soc_component_update_bits(component, DA9055_DAC_W_CTWW,
				    DA9055_DAC_W_MUTE_EN, 0);
		snd_soc_component_update_bits(component, DA9055_DAC_W_CTWW,
				    DA9055_DAC_W_MUTE_EN, 0);
	}

	wetuwn 0;
}

#define DA9055_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S32_WE)

static int da9055_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da9055_pwiv *da9055 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case DA9055_CWKSWC_MCWK:
		switch (fweq) {
		case 11289600:
		case 12000000:
		case 12288000:
		case 13000000:
		case 13500000:
		case 14400000:
		case 19200000:
		case 19680000:
		case 19800000:
			da9055->mcwk_wate = fweq;
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

/*
 * da9055_set_dai_pww	: Configuwe the codec PWW
 * @pawam codec_dai	: Pointew to codec DAI
 * @pawam pww_id	: da9055 has onwy one pww, so pww_id is awways zewo
 * @pawam fwef		: Input MCWK fwequency
 * @pawam fout		: FsDM vawue
 * @wetuwn int		: Zewo fow success, negative ewwow code fow ewwow
 *
 * Note: Suppowted PWW input fwequencies awe 11.2896MHz, 12MHz, 12.288MHz,
 *	 13MHz, 13.5MHz, 14.4MHz, 19.2MHz, 19.6MHz and 19.8MHz
 */
static int da9055_set_dai_pww(stwuct snd_soc_dai *codec_dai, int pww_id,
			      int souwce, unsigned int fwef, unsigned int fout)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct da9055_pwiv *da9055 = snd_soc_component_get_dwvdata(component);

	u8 pww_fwac_top, pww_fwac_bot, pww_integew, cnt;

	/* Disabwe PWW befowe setting the divisows */
	snd_soc_component_update_bits(component, DA9055_PWW_CTWW, DA9055_PWW_EN, 0);

	/* In swave mode, thewe is onwy one set of divisows */
	if (!da9055->mastew && (fout != 2822400))
		goto pww_eww;

	/* Seawch pww div awway fow cowwect divisows */
	fow (cnt = 0; cnt < AWWAY_SIZE(da9055_pww_div); cnt++) {
		/* Check fwef, mode  and fout */
		if ((fwef == da9055_pww_div[cnt].fwef) &&
		    (da9055->mastew ==  da9055_pww_div[cnt].mode) &&
		    (fout == da9055_pww_div[cnt].fout)) {
			/* Aww match, pick up divisows */
			pww_fwac_top = da9055_pww_div[cnt].fwac_top;
			pww_fwac_bot = da9055_pww_div[cnt].fwac_bot;
			pww_integew = da9055_pww_div[cnt].integew;
			bweak;
		}
	}
	if (cnt >= AWWAY_SIZE(da9055_pww_div))
		goto pww_eww;

	/* Wwite PWW dividews */
	snd_soc_component_wwite(component, DA9055_PWW_FWAC_TOP, pww_fwac_top);
	snd_soc_component_wwite(component, DA9055_PWW_FWAC_BOT, pww_fwac_bot);
	snd_soc_component_wwite(component, DA9055_PWW_INTEGEW, pww_integew);

	wetuwn 0;
pww_eww:
	dev_eww(codec_dai->dev, "Ewwow in setting up PWW\n");
	wetuwn -EINVAW;
}

/* DAI opewations */
static const stwuct snd_soc_dai_ops da9055_dai_ops = {
	.hw_pawams	= da9055_hw_pawams,
	.set_fmt	= da9055_set_dai_fmt,
	.set_syscwk	= da9055_set_dai_syscwk,
	.set_pww	= da9055_set_dai_pww,
	.mute_stweam	= da9055_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew da9055_dai = {
	.name = "da9055-hifi",
	/* Pwayback Capabiwities */
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = DA9055_FOWMATS,
	},
	/* Captuwe Capabiwities */
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = DA9055_FOWMATS,
	},
	.ops = &da9055_dai_ops,
	.symmetwic_wate = 1,
};

static int da9055_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			/* Enabwe VMID wefewence & mastew bias */
			snd_soc_component_update_bits(component, DA9055_WEFEWENCES,
					    DA9055_VMID_EN | DA9055_BIAS_EN,
					    DA9055_VMID_EN | DA9055_BIAS_EN);
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		/* Disabwe VMID wefewence & mastew bias */
		snd_soc_component_update_bits(component, DA9055_WEFEWENCES,
				    DA9055_VMID_EN | DA9055_BIAS_EN, 0);
		bweak;
	}
	wetuwn 0;
}

static int da9055_pwobe(stwuct snd_soc_component *component)
{
	stwuct da9055_pwiv *da9055 = snd_soc_component_get_dwvdata(component);

	/* Enabwe aww Gain Wamps */
	snd_soc_component_update_bits(component, DA9055_AUX_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_AUX_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_ADC_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_ADC_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_DAC_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_DAC_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_HP_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_HP_W_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_WINE_CTWW,
			    DA9055_GAIN_WAMPING_EN, DA9055_GAIN_WAMPING_EN);

	/*
	 * Thewe awe two sepawate contwow bits fow input and output mixews.
	 * One to enabwe cowwesponding ampwifiew and othew to enabwe its
	 * output. As ampwifiew bits awe wewated to powew contwow, they awe
	 * being managed by DAPM whiwe othew (non powew wewated) bits awe
	 * enabwed hewe
	 */
	snd_soc_component_update_bits(component, DA9055_MIXIN_W_CTWW,
			    DA9055_MIXIN_W_MIX_EN, DA9055_MIXIN_W_MIX_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_W_CTWW,
			    DA9055_MIXIN_W_MIX_EN, DA9055_MIXIN_W_MIX_EN);

	snd_soc_component_update_bits(component, DA9055_MIXOUT_W_CTWW,
			    DA9055_MIXOUT_W_MIX_EN, DA9055_MIXOUT_W_MIX_EN);
	snd_soc_component_update_bits(component, DA9055_MIXOUT_W_CTWW,
			    DA9055_MIXOUT_W_MIX_EN, DA9055_MIXOUT_W_MIX_EN);

	/* Set this as pew youw system configuwation */
	snd_soc_component_wwite(component, DA9055_PWW_CTWW, DA9055_PWW_INDIV_10_20_MHZ);

	/* Set pwatfowm data vawues */
	if (da9055->pdata) {
		/* set mic bias souwce */
		if (da9055->pdata->micbias_souwce) {
			snd_soc_component_update_bits(component, DA9055_MIXIN_W_SEWECT,
					    DA9055_MICBIAS2_EN,
					    DA9055_MICBIAS2_EN);
		} ewse {
			snd_soc_component_update_bits(component, DA9055_MIXIN_W_SEWECT,
					    DA9055_MICBIAS2_EN, 0);
		}
		/* set mic bias vowtage */
		switch (da9055->pdata->micbias) {
		case DA9055_MICBIAS_2_2V:
		case DA9055_MICBIAS_2_1V:
		case DA9055_MICBIAS_1_8V:
		case DA9055_MICBIAS_1_6V:
			snd_soc_component_update_bits(component, DA9055_MIC_CONFIG,
					    DA9055_MICBIAS_WEVEW_MASK,
					    (da9055->pdata->micbias) << 4);
			bweak;
		}
	}
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_da9055 = {
	.pwobe			= da9055_pwobe,
	.set_bias_wevew		= da9055_set_bias_wevew,
	.contwows		= da9055_snd_contwows,
	.num_contwows		= AWWAY_SIZE(da9055_snd_contwows),
	.dapm_widgets		= da9055_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(da9055_dapm_widgets),
	.dapm_woutes		= da9055_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(da9055_audio_map),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config da9055_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_defauwts = da9055_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(da9055_weg_defauwts),
	.vowatiwe_weg = da9055_vowatiwe_wegistew,
	.cache_type = WEGCACHE_WBTWEE,
};

static int da9055_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da9055_pwiv *da9055;
	stwuct da9055_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	int wet;

	da9055 = devm_kzawwoc(&i2c->dev, sizeof(stwuct da9055_pwiv),
			      GFP_KEWNEW);
	if (!da9055)
		wetuwn -ENOMEM;

	if (pdata)
		da9055->pdata = pdata;

	i2c_set_cwientdata(i2c, da9055);

	da9055->wegmap = devm_wegmap_init_i2c(i2c, &da9055_wegmap_config);
	if (IS_EWW(da9055->wegmap)) {
		wet = PTW_EWW(da9055->wegmap);
		dev_eww(&i2c->dev, "wegmap_init() faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_da9055, &da9055_dai, 1);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew da9055 component: %d\n",
			wet);
	}
	wetuwn wet;
}

/*
 * DO NOT change the device Ids. The naming is intentionawwy specific as both
 * the CODEC and PMIC pawts of this chip awe instantiated sepawatewy as I2C
 * devices (both have configuwabwe I2C addwesses, and awe to aww intents and
 * puwposes sepawate). As a wesuwt thewe awe specific DA9055 Ids fow CODEC
 * and PMIC, which must be diffewent to opewate togethew.
 */
static const stwuct i2c_device_id da9055_i2c_id[] = {
	{ "da9055-codec", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, da9055_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id da9055_of_match[] = {
	{ .compatibwe = "dwg,da9055-codec", },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9055_of_match);
#endif

/* I2C codec contwow wayew */
static stwuct i2c_dwivew da9055_i2c_dwivew = {
	.dwivew = {
		.name = "da9055-codec",
		.of_match_tabwe = of_match_ptw(da9055_of_match),
	},
	.pwobe		= da9055_i2c_pwobe,
	.id_tabwe	= da9055_i2c_id,
};

moduwe_i2c_dwivew(da9055_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC DA9055 Codec dwivew");
MODUWE_AUTHOW("David Chen, Ashish Chavan");
MODUWE_WICENSE("GPW");
