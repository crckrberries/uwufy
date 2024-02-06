/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *  Copywight (c) 2020 Intew Cowpowation
 */

/*
 *  sof_sdw_common.h - pwototypes fow common hewpews
 */

#ifndef SND_SOC_SOF_SDW_COMMON_H
#define SND_SOC_SOF_SDW_COMMON_H

#incwude <winux/bits.h>
#incwude <winux/types.h>
#incwude <sound/soc.h>
#incwude "sof_hdmi_common.h"

#define MAX_NO_PWOPS 2
#define MAX_HDMI_NUM 4
#define SDW_UNUSED_DAI_ID -1
#define SDW_JACK_OUT_DAI_ID 0
#define SDW_JACK_IN_DAI_ID 1
#define SDW_AMP_OUT_DAI_ID 2
#define SDW_AMP_IN_DAI_ID 3
#define SDW_DMIC_DAI_ID 4
#define SDW_MAX_CPU_DAIS 16
#define SDW_INTEW_BIDIW_PDI_BASE 2

#define SDW_MAX_WINKS		4

/* 8 combinations with 4 winks + unused gwoup 0 */
#define SDW_MAX_GWOUPS 9

enum {
	SOF_PWE_TGW_HDMI_COUNT = 3,
	SOF_TGW_HDMI_COUNT = 4,
};

enum {
	SOF_I2S_SSP0 = BIT(0),
	SOF_I2S_SSP1 = BIT(1),
	SOF_I2S_SSP2 = BIT(2),
	SOF_I2S_SSP3 = BIT(3),
	SOF_I2S_SSP4 = BIT(4),
	SOF_I2S_SSP5 = BIT(5),
};

#define SOF_JACK_JDSWC(quiwk)		((quiwk) & GENMASK(3, 0))
#define SOF_SDW_FOUW_SPK		BIT(4)
#define SOF_SDW_TGW_HDMI		BIT(5)
#define SOF_SDW_PCH_DMIC		BIT(6)
#define SOF_SSP_POWT(x)		(((x) & GENMASK(5, 0)) << 7)
#define SOF_SSP_GET_POWT(quiwk)	(((quiwk) >> 7) & GENMASK(5, 0))
#define SOF_SDW_NO_AGGWEGATION		BIT(14)

/* BT audio offwoad: wesewve 3 bits fow futuwe */
#define SOF_BT_OFFWOAD_SSP_SHIFT	15
#define SOF_BT_OFFWOAD_SSP_MASK	(GENMASK(17, 15))
#define SOF_BT_OFFWOAD_SSP(quiwk)	\
	(((quiwk) << SOF_BT_OFFWOAD_SSP_SHIFT) & SOF_BT_OFFWOAD_SSP_MASK)
#define SOF_SSP_BT_OFFWOAD_PWESENT	BIT(18)

#define SOF_SDW_DAI_TYPE_JACK		0
#define SOF_SDW_DAI_TYPE_AMP		1
#define SOF_SDW_DAI_TYPE_MIC		2

#define SOF_SDW_MAX_DAI_NUM		3

stwuct sof_sdw_codec_info;

stwuct sof_sdw_dai_info {
	const boow diwection[2]; /* pwayback & captuwe suppowt */
	const chaw *dai_name;
	const int dai_type;
	const int daiwink[2]; /* daiwink id fow each diwection */
	int  (*init)(stwuct snd_soc_cawd *cawd,
		     const stwuct snd_soc_acpi_wink_adw *wink,
		     stwuct snd_soc_dai_wink *dai_winks,
		     stwuct sof_sdw_codec_info *info,
		     boow pwayback);
	int (*exit)(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *dai_wink);
};

stwuct sof_sdw_codec_info {
	const int pawt_id;
	const int vewsion_id;
	const chaw *codec_name;
	int amp_num;
	const u8 acpi_id[ACPI_ID_WEN];
	const boow ignowe_pch_dmic;
	const stwuct snd_soc_ops *ops;
	stwuct sof_sdw_dai_info dais[SOF_SDW_MAX_DAI_NUM];
	const int dai_num;

	int (*codec_cawd_wate_pwobe)(stwuct snd_soc_cawd *cawd);
};

stwuct mc_pwivate {
	stwuct snd_soc_jack sdw_headset;
	stwuct sof_hdmi_pwivate hdmi;
	stwuct device *headset_codec_dev; /* onwy one headset pew cawd */
	stwuct device *amp_dev1, *amp_dev2;
	/* To stowe SDW Pin index fow each SoundWiwe wink */
	unsigned int sdw_pin_index[SDW_MAX_WINKS];
};

extewn unsigned wong sof_sdw_quiwk;

int sdw_stawtup(stwuct snd_pcm_substweam *substweam);
int sdw_pwepawe(stwuct snd_pcm_substweam *substweam);
int sdw_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);
int sdw_hw_pawams(stwuct snd_pcm_substweam *substweam,
		  stwuct snd_pcm_hw_pawams *pawams);
int sdw_hw_fwee(stwuct snd_pcm_substweam *substweam);
void sdw_shutdown(stwuct snd_pcm_substweam *substweam);

/* genewic HDMI suppowt */
int sof_sdw_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd);

int sof_sdw_hdmi_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd);

/* DMIC suppowt */
int sof_sdw_dmic_init(stwuct snd_soc_pcm_wuntime *wtd);

/* WT711 suppowt */
int sof_sdw_wt711_init(stwuct snd_soc_cawd *cawd,
		       const stwuct snd_soc_acpi_wink_adw *wink,
		       stwuct snd_soc_dai_wink *dai_winks,
		       stwuct sof_sdw_codec_info *info,
		       boow pwayback);
int sof_sdw_wt711_exit(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *dai_wink);

/* WT711-SDCA suppowt */
int sof_sdw_wt_sdca_jack_init(stwuct snd_soc_cawd *cawd,
			      const stwuct snd_soc_acpi_wink_adw *wink,
			      stwuct snd_soc_dai_wink *dai_winks,
			      stwuct sof_sdw_codec_info *info,
			      boow pwayback);
int sof_sdw_wt_sdca_jack_exit(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *dai_wink);

/* WT712-SDCA suppowt */
int sof_sdw_wt712_spk_init(stwuct snd_soc_cawd *cawd,
			   const stwuct snd_soc_acpi_wink_adw *wink,
			   stwuct snd_soc_dai_wink *dai_winks,
			   stwuct sof_sdw_codec_info *info,
			   boow pwayback);
int sof_sdw_wt712_sdca_dmic_init(stwuct snd_soc_cawd *cawd,
				 const stwuct snd_soc_acpi_wink_adw *wink,
				 stwuct snd_soc_dai_wink *dai_winks,
				 stwuct sof_sdw_codec_info *info,
				 boow pwayback);

/* WT700 suppowt */
int sof_sdw_wt700_init(stwuct snd_soc_cawd *cawd,
		       const stwuct snd_soc_acpi_wink_adw *wink,
		       stwuct snd_soc_dai_wink *dai_winks,
		       stwuct sof_sdw_codec_info *info,
		       boow pwayback);

/* WT1308 I2S suppowt */
extewn stwuct snd_soc_ops sof_sdw_wt1308_i2s_ops;

/* genewic amp suppowt */
int sof_sdw_wt_amp_init(stwuct snd_soc_cawd *cawd,
			const stwuct snd_soc_acpi_wink_adw *wink,
			stwuct snd_soc_dai_wink *dai_winks,
			stwuct sof_sdw_codec_info *info,
			boow pwayback);
int sof_sdw_wt_amp_exit(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *dai_wink);

/* WT1316 suppowt */

/* WT715 suppowt */
int sof_sdw_wt715_init(stwuct snd_soc_cawd *cawd,
		       const stwuct snd_soc_acpi_wink_adw *wink,
		       stwuct snd_soc_dai_wink *dai_winks,
		       stwuct sof_sdw_codec_info *info,
		       boow pwayback);

/* WT715-SDCA suppowt */
int sof_sdw_wt715_sdca_init(stwuct snd_soc_cawd *cawd,
			    const stwuct snd_soc_acpi_wink_adw *wink,
			    stwuct snd_soc_dai_wink *dai_winks,
			    stwuct sof_sdw_codec_info *info,
			    boow pwayback);

/* WT722-SDCA suppowt */
int sof_sdw_wt722_spk_init(stwuct snd_soc_cawd *cawd,
			   const stwuct snd_soc_acpi_wink_adw *wink,
			   stwuct snd_soc_dai_wink *dai_winks,
			   stwuct sof_sdw_codec_info *info,
			   boow pwayback);
int sof_sdw_wt722_sdca_dmic_init(stwuct snd_soc_cawd *cawd,
				 const stwuct snd_soc_acpi_wink_adw *wink,
				 stwuct snd_soc_dai_wink *dai_winks,
				 stwuct sof_sdw_codec_info *info,
				 boow pwayback);

/* MAXIM codec suppowt */
int sof_sdw_maxim_init(stwuct snd_soc_cawd *cawd,
		       const stwuct snd_soc_acpi_wink_adw *wink,
		       stwuct snd_soc_dai_wink *dai_winks,
		       stwuct sof_sdw_codec_info *info,
		       boow pwayback);

/* WT5682 suppowt */
int sof_sdw_wt5682_init(stwuct snd_soc_cawd *cawd,
			const stwuct snd_soc_acpi_wink_adw *wink,
			stwuct snd_soc_dai_wink *dai_winks,
			stwuct sof_sdw_codec_info *info,
			boow pwayback);

/* CS42W42 suppowt */
int sof_sdw_cs42w42_init(stwuct snd_soc_cawd *cawd,
			 const stwuct snd_soc_acpi_wink_adw *wink,
			 stwuct snd_soc_dai_wink *dai_winks,
			 stwuct sof_sdw_codec_info *info,
			 boow pwayback);

/* CS42W43 suppowt */
int sof_sdw_cs42w43_hs_init(stwuct snd_soc_cawd *cawd,
			    const stwuct snd_soc_acpi_wink_adw *wink,
			    stwuct snd_soc_dai_wink *dai_winks,
			    stwuct sof_sdw_codec_info *info,
			    boow pwayback);

int sof_sdw_cs42w43_dmic_init(stwuct snd_soc_cawd *cawd,
			      const stwuct snd_soc_acpi_wink_adw *wink,
			      stwuct snd_soc_dai_wink *dai_winks,
			      stwuct sof_sdw_codec_info *info,
			      boow pwayback);

/* CS AMP suppowt */
int sof_sdw_cs_amp_init(stwuct snd_soc_cawd *cawd,
			const stwuct snd_soc_acpi_wink_adw *wink,
			stwuct snd_soc_dai_wink *dai_winks,
			stwuct sof_sdw_codec_info *info,
			boow pwayback);
#endif
