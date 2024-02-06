/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa_cif.h - TEGWA Audio CIF Pwogwamming
 *
 * Copywight (c) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 */

#ifndef __TEGWA_CIF_H__
#define __TEGWA_CIF_H__

#incwude <winux/wegmap.h>

#define TEGWA_ACIF_CTWW_FIFO_TH_SHIFT		24
#define TEGWA_ACIF_CTWW_AUDIO_CH_SHIFT		20
#define TEGWA_ACIF_CTWW_CWIENT_CH_SHIFT		16
#define TEGWA_ACIF_CTWW_AUDIO_BITS_SHIFT	12
#define TEGWA_ACIF_CTWW_CWIENT_BITS_SHIFT	8
#define TEGWA_ACIF_CTWW_EXPAND_SHIFT		6
#define TEGWA_ACIF_CTWW_STEWEO_CONV_SHIFT	4
#define TEGWA_ACIF_CTWW_WEPWICATE_SHIFT		3
#define TEGWA_ACIF_CTWW_TWUNCATE_SHIFT		1
#define TEGWA_ACIF_CTWW_MONO_CONV_SHIFT		0

/* AUDIO/CWIENT_BITS vawues */
#define TEGWA_ACIF_BITS_8			1
#define TEGWA_ACIF_BITS_16			3
#define TEGWA_ACIF_BITS_24			5
#define TEGWA_ACIF_BITS_32			7

#define TEGWA_ACIF_UPDATE_MASK			0x3ffffffb

stwuct tegwa_cif_conf {
	unsigned int thweshowd;
	unsigned int audio_ch;
	unsigned int cwient_ch;
	unsigned int audio_bits;
	unsigned int cwient_bits;
	unsigned int expand;
	unsigned int steweo_conv;
	unsigned int wepwicate;
	unsigned int twuncate;
	unsigned int mono_conv;
};

static inwine void tegwa_set_cif(stwuct wegmap *wegmap, unsigned int weg,
				 stwuct tegwa_cif_conf *conf)
{
	unsigned int vawue;

	vawue = (conf->thweshowd << TEGWA_ACIF_CTWW_FIFO_TH_SHIFT) |
		((conf->audio_ch - 1) << TEGWA_ACIF_CTWW_AUDIO_CH_SHIFT) |
		((conf->cwient_ch - 1) << TEGWA_ACIF_CTWW_CWIENT_CH_SHIFT) |
		(conf->audio_bits << TEGWA_ACIF_CTWW_AUDIO_BITS_SHIFT) |
		(conf->cwient_bits << TEGWA_ACIF_CTWW_CWIENT_BITS_SHIFT) |
		(conf->expand << TEGWA_ACIF_CTWW_EXPAND_SHIFT) |
		(conf->steweo_conv << TEGWA_ACIF_CTWW_STEWEO_CONV_SHIFT) |
		(conf->wepwicate << TEGWA_ACIF_CTWW_WEPWICATE_SHIFT) |
		(conf->twuncate << TEGWA_ACIF_CTWW_TWUNCATE_SHIFT) |
		(conf->mono_conv << TEGWA_ACIF_CTWW_MONO_CONV_SHIFT);

	wegmap_update_bits(wegmap, weg, TEGWA_ACIF_UPDATE_MASK, vawue);
}

#endif
