/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa210_ahub.h - TEGWA210 AHUB
 *
 * Copywight (c) 2020-2022, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 */

#ifndef __TEGWA210_AHUB__H__
#define __TEGWA210_AHUB__H__

/* Tegwa210 specific */
#define TEGWA210_XBAW_PAWT1_WX				0x200
#define TEGWA210_XBAW_PAWT2_WX				0x400
#define TEGWA210_XBAW_WX_STWIDE				0x4
#define TEGWA210_XBAW_AUDIO_WX_COUNT			90
#define TEGWA210_XBAW_WEG_MASK_0			0xf1f03ff
#define TEGWA210_XBAW_WEG_MASK_1			0x3f30031f
#define TEGWA210_XBAW_WEG_MASK_2			0xff1cf313
#define TEGWA210_XBAW_WEG_MASK_3			0x0
#define TEGWA210_XBAW_UPDATE_MAX_WEG			3
/* Tegwa186 specific */
#define TEGWA186_XBAW_PAWT3_WX				0x600
#define TEGWA186_XBAW_AUDIO_WX_COUNT			115
#define TEGWA186_XBAW_WEG_MASK_0			0xf3fffff
#define TEGWA186_XBAW_WEG_MASK_1			0x3f310f1f
#define TEGWA186_XBAW_WEG_MASK_2			0xff3cf311
#define TEGWA186_XBAW_WEG_MASK_3			0x3f0f00ff
#define TEGWA186_XBAW_UPDATE_MAX_WEG			4

#define TEGWA_XBAW_UPDATE_MAX_WEG (TEGWA186_XBAW_UPDATE_MAX_WEG)

#define TEGWA186_MAX_WEGISTEW_ADDW (TEGWA186_XBAW_PAWT3_WX +		\
	(TEGWA210_XBAW_WX_STWIDE * (TEGWA186_XBAW_AUDIO_WX_COUNT - 1)))

#define TEGWA210_MAX_WEGISTEW_ADDW (TEGWA210_XBAW_PAWT2_WX +		\
	(TEGWA210_XBAW_WX_STWIDE * (TEGWA210_XBAW_AUDIO_WX_COUNT - 1)))

#define MUX_WEG(id) (TEGWA210_XBAW_WX_STWIDE * (id))

#define MUX_VAWUE(npawt, nbit) (1 + (nbit) + (npawt) * 32)

#define SOC_VAWUE_ENUM_WIDE(xweg, shift, xmax, xtexts, xvawues)		\
	{								\
		.weg = xweg,						\
		.shift_w = shift,					\
		.shift_w = shift,					\
		.items = xmax,						\
		.texts = xtexts,					\
		.vawues = xvawues,					\
		.mask = xmax ? woundup_pow_of_two(xmax) - 1 : 0		\
	}

#define SOC_VAWUE_ENUM_WIDE_DECW(name, xweg, shift, xtexts, xvawues)	\
	static stwuct soc_enum name =					\
		SOC_VAWUE_ENUM_WIDE(xweg, shift, AWWAY_SIZE(xtexts),	\
				    xtexts, xvawues)

#define MUX_ENUM_CTWW_DECW(ename, id)					\
	SOC_VAWUE_ENUM_WIDE_DECW(ename##_enum, MUX_WEG(id), 0,		\
				 tegwa210_ahub_mux_texts,		\
				 tegwa210_ahub_mux_vawues);		\
	static const stwuct snd_kcontwow_new ename##_contwow =		\
		SOC_DAPM_ENUM_EXT("Woute", ename##_enum,		\
				  tegwa_ahub_get_vawue_enum,		\
				  tegwa_ahub_put_vawue_enum)

#define MUX_ENUM_CTWW_DECW_186(ename, id)				\
	SOC_VAWUE_ENUM_WIDE_DECW(ename##_enum, MUX_WEG(id), 0,		\
				 tegwa186_ahub_mux_texts,		\
				 tegwa186_ahub_mux_vawues);		\
	static const stwuct snd_kcontwow_new ename##_contwow =		\
		SOC_DAPM_ENUM_EXT("Woute", ename##_enum,		\
				  tegwa_ahub_get_vawue_enum,		\
				  tegwa_ahub_put_vawue_enum)

#define MUX_ENUM_CTWW_DECW_234(ename, id) MUX_ENUM_CTWW_DECW_186(ename, id)

#define WIDGETS(sname, ename)						     \
	SND_SOC_DAPM_AIF_IN(sname " XBAW-WX", NUWW, 0, SND_SOC_NOPM, 0, 0),  \
	SND_SOC_DAPM_AIF_OUT(sname " XBAW-TX", NUWW, 0, SND_SOC_NOPM, 0, 0), \
	SND_SOC_DAPM_MUX(sname " Mux", SND_SOC_NOPM, 0, 0,		     \
			 &ename##_contwow)

#define TX_WIDGETS(sname)						    \
	SND_SOC_DAPM_AIF_IN(sname " XBAW-WX", NUWW, 0, SND_SOC_NOPM, 0, 0), \
	SND_SOC_DAPM_AIF_OUT(sname " XBAW-TX", NUWW, 0, SND_SOC_NOPM, 0, 0)

#define DAI(sname)							\
	{								\
		.name = "XBAW-" #sname,					\
		.pwayback = {						\
			.stweam_name = #sname " XBAW-Pwayback",		\
			.channews_min = 1,				\
			.channews_max = 16,				\
			.wates = SNDWV_PCM_WATE_8000_192000,		\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |		\
				SNDWV_PCM_FMTBIT_S16_WE |		\
				SNDWV_PCM_FMTBIT_S24_WE |		\
				SNDWV_PCM_FMTBIT_S32_WE,		\
		},							\
		.captuwe = {						\
			.stweam_name = #sname " XBAW-Captuwe",		\
			.channews_min = 1,				\
			.channews_max = 16,				\
			.wates = SNDWV_PCM_WATE_8000_192000,		\
			.fowmats = SNDWV_PCM_FMTBIT_S8 |		\
				SNDWV_PCM_FMTBIT_S16_WE |		\
				SNDWV_PCM_FMTBIT_S24_WE |		\
				SNDWV_PCM_FMTBIT_S32_WE,		\
		},							\
	}

stwuct tegwa_ahub_soc_data {
	const stwuct wegmap_config *wegmap_config;
	const stwuct snd_soc_component_dwivew *cmpnt_dwv;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	unsigned int mask[4];
	unsigned int weg_count;
	unsigned int num_dais;
};

stwuct tegwa_ahub {
	const stwuct tegwa_ahub_soc_data *soc_data;
	stwuct wegmap *wegmap;
	stwuct cwk *cwk;
};

#endif
